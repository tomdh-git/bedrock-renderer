// LIFT 0xbcab880 size 0x6a 1.26.62.01 sub_bcab880
#include "client/features/render/native/bgfx/sub_bcab880.h"

#include <cstdint>

namespace native::bgfx {

namespace {

// Both indirect calls of the original read their target from data slot
// 0xF99FFA0 at call time (exactly what 0xbcab8b5 and 0xbcab8cb do:
// call qword ptr [0xF99FFA0]). rdis resolves the slot to sub_eea6040 and
// docs/data/native_boundary.tsv lists 0xeea6040 as class vendor (loader-
// resolved thunk via data slot 0xF99FFA0). The original passes rcx = the
// refCnt object and ignores the return value, so the thunk's signature is
// void(RefCnt*).
void callReleaseThunk(RefCnt* rc) {
    // 0xbcab8b5 / 0xbcab8cb  call qword ptr [0xF99FFA0]
    using Fn = void (*)(RefCnt*);
    reinterpret_cast<Fn>(
        *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0))(rc);
}

} // namespace

native::Footprint sub_bcab880_footprint(GroupEntry* entry) {
    native::Footprint fp;
    if (entry != nullptr) {
        fp.push_back({entry, sizeof(GroupEntry)});
        if (entry->refCnt != nullptr) {
            fp.push_back({entry->refCnt, sizeof(RefCnt)});
        }
    }
    return fp;
}

bool sub_bcab880(GroupEntry* entry) {
    // 0xbcab880..0xbcab882: prologue push rsi / push rdi / sub rsp,0x28
    // 0xbcab886  mov rax,[rcx+8]
    RefCnt* const rc1 = entry->refCnt;
    // 0xbcab88a  test rax,rax
    // 0xbcab88d  je short 0xBCAB8D3   -> skips the addref when refCnt == 0
    if (rc1 != nullptr) {
        // 0xbcab88f  lock inc dword ptr [rax+8]
        rc1->strong.fetch_add(1u, std::memory_order_seq_cst);
    }

    // 0xbcab893  mov rax,[rcx]
    void* const uiObject = entry->uiObject;
    // 0xbcab896  mov rsi,[rcx+8]
    RefCnt* const rc2 = entry->refCnt;
    // 0xbcab89a  mov rax,[rax+0x18]
    UiObject* const next = reinterpret_cast<UiObject*>(uiObject)->next;
    // 0xbcab89e  mov rdi,[rax]
    const uintptr_t retSlot0 = *reinterpret_cast<uintptr_t*>(next);

    // 0xbcab8a1  test rsi,rsi
    // 0xbcab8a4  je short 0xBCAB8DD   -> skips both release stages when refCnt == 0
    if (rc2 != nullptr) {
        // 0xbcab8a6  lock dec dword ptr [rsi+8]
        // 0xbcab8aa  jne short 0xBCAB8DD -> when strong != 0 skip both stages
        if (rc2->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            // 0xbcab8ac  mov rax,[rsi]     (dead read of the vptr)
            // 0xbcab8af  mov rax,[rax]     (dead read of vtable slot 0)
            void* const vt1 = *reinterpret_cast<void* const volatile*>(rc2);
            (void)*reinterpret_cast<uintptr_t volatile*>(vt1);
            // 0xbcab8b2  mov rcx,rsi
            // 0xbcab8b5  call qword ptr [0xF99FFA0]
            // `0xbcab8b5  call qword ptr [0xF99FFA0]`   target = sub_eea6040 via data slot 0xF99FFA0 (vendor boundary); this = rc2; return ignored
            callReleaseThunk(rc2);
            // 0xbcab8bb  lock dec dword ptr [rsi+0xC]
            // 0xbcab8bf  jne short 0xBCAB8DD -> when weak != 0 skip the final call
            if (rc2->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                // 0xbcab8c1  mov rax,[rsi]     (dead read of the vptr)
                // 0xbcab8c4  mov rax,[rax+8]  (dead read of vtable slot 1)
                void* const vt2 = *reinterpret_cast<void* const volatile*>(rc2);
                (void)*reinterpret_cast<uintptr_t volatile*>(
                    reinterpret_cast<char*>(vt2) + 8);
                // 0xbcab8c8  mov rcx,rsi
                // 0xbcab8cb  call qword ptr [0xF99FFA0]
                // `0xbcab8cb  call qword ptr [0xF99FFA0]`   target = sub_eea6040 via data slot 0xF99FFA0 (vendor boundary); this = rc2; return ignored
                callReleaseThunk(rc2);
            }
            // 0xbcab8d1  jmp short 0xBCAB8DD   (fall through either way)
        }
        // 0xbcab8aa / 0xbcab8bf  jne short 0xBCAB8DD   landing pad
    }

    // 0xbcab8d3..0xbcab8da: on the refCnt == 0 entry path the original
    // recomputes rdi = *(uintptr_t*)next identically; it is computed above
    // and still live, so no code is needed here.
    // 0xbcab8dd  test rdi,rdi
    // 0xbcab8e0  setne al             return value = (retSlot0 != 0)
    // 0xbcab8e3  add rsp,0x28
    // 0xbcab8e7  pop rdi
    // 0xbcab8e8  pop rsi
    // 0xbcab8e9  ret
    return retSlot0 != 0;
}

LIFT_FN(sub_bcab880, "group insert UI", 0xbcab880, sub_bcab880,
        sub_bcab880_footprint);

} // namespace native::bgfx
