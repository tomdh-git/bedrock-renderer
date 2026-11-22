#include "client/features/render/rewrite/RewriteMaterialSwap.h"


#include "client/core/diagnostics/Log.h"
#include "client/features/render/rewrite/RewriteFunctions.h"
#include "client/features/render/rewrite/RewriteRegistry.h"

// Q?: L7h material swap hook. Control point (proven [V] by oc_U-EL7h r1/r2/r3/r4/r5; every quoted line
// below is verbatim from the exe and re-checked by verify_oc.py):
//   tag-7 handler 0x6646dc2 (BGFX_MAP.md 6cj): BST over the FNV-1 64 material-name hash —
//     split 0x416AE22CAB22EA36 @ 0x6646dde (`jg 0x6647449` @ 0x6646deb);
//     leaves 0xD8EF928BC853553A @ 0x6646df1 and 0x2C8B246FD3EDDC59 (cracks_overlay_tile_entity.skinning)
//     @ 0x6646e00 (`jne 0x66475BB` @ 0x6646e0d);
//     right subtree 0x6647449: 0x4B8EDB299C93ABB3 (selection_overlay_block_entity.skinning) @ 0x6647449,
//     0x416AE22CAB22EA37 (selection_overlay_block_entity.skinning_color) @ 0x6647458
//     (`jne 0x66475BB` @ 0x6647465); miss -> 0x66475bb/0x66475de (forwarder 0x4DF6E80) -> 0x664CB91.
//   on a match the item visitor builds the pass-name "CracksBlockEntity" (0x6646e6c, len 0x11 @ 0x6646e7a)
//     as a string_view at [rbp+0x5A0]/[rbp+0x5A8] (0x6646e73/0x6646e7a) and calls the resolver at
//     0x6646eab: rcx = cache = frameCtx+0x68 (0x6646e5c), rdx = out {holder, control} (0x6646ea4),
//     r8 = 16-byte key (static per-call-site data @ 0x6646e9d — NOT the pass name), r9 = loader
//     = frameCtx+0x40 (0x6646e58), stack [rsp+0x20] = pointer to string_view {ptr, size} (0x6646e98),
//     stack [rsp+0x28] = pointer to defines span {0, 0} (0x6646e8c).
//   resolver body 0x675e440 (BGFX_MAP.md 6gs): this -> r14 (0x675e46d), rbx = key arg (0x675e467),
//     mutex cache+0x98 locked via 0xEEC59F0 (0x675e489/0x675e493), FNV-1 64 over the key with basis
//     0xCBF29CE484222325 (0x675e4c6) and prime 0x100000001B3 (0x675e4d3).
//
// The per-item material identity is get()'s 5th argument: a pointer to a {ptr, size} string_view
// (docs/functions/675e440.md: get(this rcx, out rdx, key r8 [16 bytes], loader r9, name [5th],
// defines [6th]); the view itself is {ptr at [rbp+0x5A0], size at [rbp+0x5A8] per 0x6646e73/0x6646e7a).
// The detour (rwCacheDetour in RewriteResourceCache.cpp — see below) hashes that view with FNV-1a,
// basis kFnvBasis = 0xCBF29CE484222325 (RewriteFunctions.h:10, the resolver's basis at 0x675e4c6)
// and swaps in the replacement name from the MaterialSwap table.
//
// Registration: RewriteResourceCache.cpp owns the single Detour at 0x675E440
// (sCacheEntry/sCacheReg, sig "ResourceCache::get", knownRva 0x675E440 — src/sdk/Sigs.json:92;
// no Sigs.json entry is added here and no HookManager.cpp/CMake edit is needed: CMake GLOB_RECURSEs
// src/*.cpp at CMakeLists.txt:138). This file registers a HOSTED entry ("MaterialSwap", same sig and
// RVA, detour nullptr): record() + reg run at static init, install() skips Detour creation for
// hosted entries (RewriteRegistry.cpp:77-82), so NO second detour is ever created on the same RVA.
// The entry is only the mode switch (BS_REWRITE="MaterialSwap=on") and the report() row; the swap
// itself runs inside rwCacheDetour, which queries MaterialSwap::swapEnabled() before each original call.
//
// Mode contract:
//   Off      pure pass-through: the original runs with the original arguments (one atomic read of
//            the entry mode).
//   On       the detour looks up the pass-name hash; on a swap it calls the original with the
//            replacement string_view substituted, otherwise calls the original unchanged.
//   Shadow / Verify not applicable: the entry is hosted — it has no detour of its own and nothing
//            to compare. (ResourceCache::get is also impure: it takes the recursive mutex at
//            cache+0x98 (0x675e489/0x675e493), bumps the holder refcount at control+8 and marks the
//            entry used at node+0x30, so it cannot be run twice for a snapshot comparison; and the
//            swap deliberately changes the name input, so a different holder is the intended result,
//            not a divergence.) The practical enablement is BS_REWRITE="ResourceCache::get=on,MaterialSwap=on":
//            ResourceCache::get=on installs rwCacheDetour, MaterialSwap=on switches the substitution on.

// FNV-1a 64 over the pass-name bytes with basis kFnvBasis = 0xCBF29CE484222325 — the resolver's own
// basis (0x675e4c6 `mov rdx,0xCBF29CE484222325`, `xor rdx,rcx` @ 0x675e4d0, prime @ 0x675e4d3).
static uint64_t hashPassName(const char* ptr, size_t size) {
    return RewriteHash::fnv1a(reinterpret_cast<const uint8_t*>(ptr), size);
}


MaterialSwap::Entry MaterialSwap::sTable[MaterialSwap::kMaxEntries]{};
std::mutex MaterialSwap::sMutex;

void MaterialSwap::set(const char* passName, const char* replacement) {
    BS_CHECK(passName != nullptr && replacement != nullptr);
    const size_t nameLen = std::strlen(passName);
    BS_CHECK(nameLen > 0);
    const size_t replLen = std::strlen(replacement);
    BS_CHECK(replLen > 0 && replLen < kMaxReplacement);
    const uint64_t nameHash = hashPassName(passName, nameLen);
    std::lock_guard<std::mutex> lock(sMutex);
    for (Entry& e : sTable) {
        if (!e.used) {
            e.nameHash = nameHash;
            std::memcpy(e.replacement, replacement, replLen + 1); // with terminating NUL
            e.replacementSize = static_cast<uint8_t>(replLen);
            e.used = true;
            return;
        }
        if (e.nameHash == nameHash) { // re-set replaces the replacement (same hash bucket)
            std::memcpy(e.replacement, replacement, replLen + 1);
            e.replacementSize = static_cast<uint8_t>(replLen);
            return;
        }
    }
    Logger::fatal("[rewrite] MaterialSwap table is full: {} entries, max {}", kMaxEntries, kMaxEntries);
}

void MaterialSwap::clear() {
    std::lock_guard<std::mutex> lock(sMutex);
    for (Entry& e : sTable)
        e = Entry{};
}

bool MaterialSwap::lookup(const char* ptr, size_t size, char out[kMaxReplacement], size_t& outSize) {
    if (ptr == nullptr || size == 0 || size > kMaxReplacement)
        return false;
    const uint64_t nameHash = hashPassName(ptr, size);
    std::lock_guard<std::mutex> lock(sMutex);
    for (const Entry& e : sTable) {
        if (e.used && e.nameHash == nameHash) {
            outSize = e.replacementSize;
            std::memcpy(out, e.replacement, outSize);
            return true;
        }
    }
    return false;
}

// The detour lives in RewriteResourceCache.cpp (the installed Detour on 0x675E440). This entry is
// hosted: detour is nullptr, install() skips Detour creation (RewriteRegistry.cpp:77-82). Kept so the
// mode can be switched (BS_REWRITE) and the entry shows in report().
static RewriteEntry sSwapEntry("MaterialSwap", "ResourceCache::get", 0x675E440, nullptr, true /* hosted */);
static const RewriteReg sSwapReg(sSwapEntry);

bool MaterialSwap::swapEnabled() {
    return sSwapEntry.current() == RewriteMode::On;
}
