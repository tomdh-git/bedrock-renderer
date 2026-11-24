// LIFT 0xbc5e120 size 0xc1 1.26.62.01 sub_bc5e120
#include "client/features/render/native/bgfx/sub_bc5e120.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Boundary wrappers for the two classified callees (docs/data/native_boundary.tsv, class crt).
// 0x78ed0 is a noreturn thunk: `sub rsp,0x28 / call qword ptr [0xF9A8CF0]`, then int3 padding,
// no ret. Reached from 0xbc5e1d6 with rcx = entry->dataPtr == 0.
// 0x1166e0 is statically present at 0xbc5e1db but unreachable (0x78ed0 never returns); it reads
// none of its register arguments (rcx is overwritten at 0x11670e before any use), so it is not
// called from the lifted code; its call remains quoted verbatim below.
native::Boundary<void, std::uintptr_t> sub_78ed0("sub_78ed0");

static native::Footprint sub_bc5e120Footprint(const View* /*view*/, LookupResult* out,
                                              const LookupKey* /*key*/) {
    return {{out, sizeof(LookupResult)}}; // the function only writes out->value0, out->value1,
                                          // out->found [V]
}

extern "C" LookupResult* sub_bc5e120(const View* view, LookupResult* out,
                                     const LookupKey* key) {
    // 0xbc5e120..0xbc5e135 — prologue (sub rsp,0x28 is home space); load the entry range
    // *(view + 0x08) and bail out when it is empty.
    const auto* first = view->range->begin;                  // 0xbc5e124 mov rcx,[rcx+8]
                                                             // 0xbc5e128 mov rax,[rcx+8]
    const auto* last = view->range->end;                     // 0xbc5e12c mov rcx,[rcx+0x10]
    if (first == last) goto notFound;                        // 0xbc5e130 cmp rax,rcx
                                                             // 0xbc5e133 je short 0xBC5E17F

    const std::uint8_t version = key->version;               // 0xbc5e135 movzx r9d,byte ptr [r8+8]
    if (version == 0xFF) goto wildcard;                      // 0xbc5e13a cmp r9b,0xFF
                                                             // 0xbc5e13e je short 0xBC5E179
    const std::uint64_t id = key->id;                        // 0xbc5e140 mov r8,[r8]
    goto scan;                                               // 0xbc5e143 jmp short 0xBC5E159
                                                             // 0xbc5e145 nop [rax+rax] (10-byte pad)

scan:                                                        // 0xbc5e159..0xbc5e167
    if (first->version != version) goto nextEntry;           // 0xbc5e159 cmp [rax+8],r9b
                                                             // 0xbc5e15d jne short 0xBC5E150
    if (first->id != id) goto nextEntry;                     // 0xbc5e15f cmp [rax],r8
                                                             // 0xbc5e162 jne short 0xBC5E150
    goto found;                                              // 0xbc5e164 jmp short 0xBC5E17F
                                                             // 0xbc5e166 nop [rax+rax] (10-byte pad)
nextEntry:                                                   // 0xbc5e150..0xbc5e15a
    first = reinterpret_cast<const Entry*>(
        reinterpret_cast<const std::uint8_t*>(first) + 0x48); // 0xbc5e150 add rax,0x48
    if (first != last) goto scan;                             // 0xbc5e154 cmp rax,rcx
                                                              // 0xbc5e157 je short 0xBC5E1A8
    goto notFound;                                            // 0xbc5e157 je taken -> 0xBC5E1A8

wildcard:                                                    // 0xbc5e170..0xbc5e17f
    if (first->version != 0xFF) goto wildcardNext;           // 0xbc5e179 cmp byte ptr [rax+8],0xFF
                                                             // 0xbc5e17d jne short 0xBC5E170
    goto found;                                              // 0xbc5e17d not taken -> 0xBC5E17F
wildcardNext:                                                // (0xbc5e170..0xbc5e17f)
    first = reinterpret_cast<const Entry*>(
        reinterpret_cast<const std::uint8_t*>(first) + 0x48); // 0xbc5e170 add rax,0x48
    if (first != last) goto wildcard;                         // 0xbc5e174 cmp rax,rcx
                                                              // 0xbc5e177 je short 0xBC5E1A8
    goto notFound;                                            // je taken -> 0xBC5E1A8

found:                                                        // 0xbc5e17f..0xbc5e1a5
    if (first == last) goto notFound;                         // 0xbc5e17f cmp rax,rcx
                                                              // 0xbc5e182 je short 0xBC5E1A8
    const std::uint8_t kind = first->kind;                    // 0xbc5e184 movzx r8d,byte ptr [rax+0x30]
    if (kind > 6) {                                           // 0xbc5e189 cmp r8,6
                                                              // 0xbc5e18d ja short 0xBC5E1DB
        // 0xbc5e1db  call 0x1166E0   ; noreturn; sub_1166e0 reads none of its register arguments
        // `0xbc5e1db  call 0x1166E0`
        return out;                                             // unreachable: 0xbc5e1e0 is int3 padding (end of function)
    }
    switch (kind) {                                             // 0xbc5e197 lea r9,[0xF441354]
                                                              // 0xbc5e19e movsxd r8,[r9+r8*4]
                                                              // 0xbc5e1a2 add r8,r9
                                                              // 0xbc5e1a5 jmp r8
    case 0:
    case 1:
    case 2:
        goto doPair;                                            // jump-table indices 0..2 -> 0xBC5E1B5
    default:
        goto notFound;                                          // jump-table indices 3..6 -> 0xBC5E1A8
    }

doPair:                                                         // 0xbc5e1b5..0xbc5e1c7
    if (first->dataPtr == 0 && first->dataEnd == 0) {           // test rcx,rcx / setne r8b
                                                              // test rax,rax / sete r9b
                                                              // or r9b,r8b / je short 0xBC5E1D6
// 0xbc5e1d6..0xbc5e1e1 — call 0x78ED0, call 0x1166E0, int3 end of function
        // 0xbc5e1d6  call 0x78ED0   ; noreturn; rcx = entry->dataPtr == 0
        // `0xbc5e1d6  call 0x78ED0`
        sub_78ed0(0);
        // 0xbc5e1db  call 0x1166E0   ; statically present but unreachable (0x78ed0 never returns)
        // `0xbc5e1db  call 0x1166E0`
        return out;                                             // unreachable: 0xbc5e1e0 is int3 padding (end of function)
    }
    // 0xbc5e1c8..0xbc5e1d5
    out->value0 = first->dataEnd - first->dataPtr;              // 0xbc5e1c8 sub rax,rcx
                                                              // 0xbc5e1cb mov [rdx],rax
    out->value1 = first->dataPtr;                               // 0xbc5e1ce mov [rdx+8],rcx
    out->found = 1;                                             // 0xbc5e1d2 mov al,1
                                                              // 0xbc5e1d4 jmp short 0xBC5E1AA
                                                              // 0xbc5e1aa mov [rdx+0x10],al
    return out;                                                 // 0xbc5e1ad mov rax,rdx
                                                              // 0xbc5e1b0 add rsp,0x28
                                                              // 0xbc5e1b4 ret

notFound:                                                       // 0xbc5e1a8..0xbc5e1b4
    out->found = 0;                                             // 0xbc5e1a8 xor eax,eax
                                                              // 0xbc5e1aa mov [rdx+0x10],al
    return out;                                                 // 0xbc5e1ad mov rax,rdx
                                                              // 0xbc5e1b0 add rsp,0x28
                                                              // 0xbc5e1b4 ret
}

// Layout assertions used by this function (mirrored in sub_bc5e120.h).
static_assert(offsetof(View, range) == 0x08, "sub_bc5e120 reads view+0x08 as the entry range");
static_assert(offsetof(EntryRange, begin) == 0x08 && offsetof(EntryRange, end) == 0x10,
              "sub_bc5e120 walks range->begin (+0x08) and range->end (+0x10)");
static_assert(offsetof(Entry, id) == 0x00 && offsetof(Entry, version) == 0x08,
              "sub_bc5e120 matches entry id (+0x00) and version (+0x08)");
static_assert(offsetof(Entry, dataPtr) == 0x18 && offsetof(Entry, dataEnd) == 0x20 &&
                  offsetof(Entry, kind) == 0x30,
              "sub_bc5e120 reads entry dataPtr (+0x18), dataEnd (+0x20), kind (+0x30)");
static_assert(offsetof(LookupKey, id) == 0x00 && offsetof(LookupKey, version) == 0x08,
              "sub_bc5e120 reads key id (+0x00) and version (+0x08)");
static_assert(offsetof(LookupResult, value0) == 0x00 && offsetof(LookupResult, value1) == 0x08 &&
                  offsetof(LookupResult, found) == 0x10,
              "sub_bc5e120 writes out->value0 (+0x00), value1 (+0x08), found (+0x10)");
static_assert(sizeof(Entry) == 0x48, "sub_bc5e120 steps entries by 0x48");
static_assert(sizeof(LookupResult) == 0x18, "sub_bc5e120 writes within LookupResult");

LIFT_FN(sub_bc5e120, "sub_bc5e120", 0xbc5e120, sub_bc5e120, sub_bc5e120Footprint);

} // namespace native::bgfx
