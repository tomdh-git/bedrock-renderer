// LIFT 0xbc7c4e0 size 0x95 1.26.62.01 sub_bc7c4e0
#include "client/features/render/native/bgfx/sub_bc7c4e0.h"
#include "client/features/render/native/Lift.h"

#include <atomic>
#include <cstddef>
#include <cstdint>

static_assert(offsetof(native::FrameSlot, raw) == native::kFrameSlotRawOffset, "FrameSlot::raw layout");
static_assert(offsetof(native::FrameSlot, ref) == native::kFrameSlotRefOffset, "FrameSlot::ref layout");
static_assert(offsetof(native::FrameSlot, flag) == native::kFrameSlotFlagOffset, "FrameSlot::flag layout");
static_assert(sizeof(native::FrameSlot) == native::kFrameSlotSize, "FrameSlot size");

namespace native {

namespace {

// The object's virtual destroy/dealloc are reached exactly as in sub_bc55ea0:
// the code loads a vtable entry into rax then executes
//   0xbc7c54e  call qword ptr [0xF99FFA0]
// where data slot 0xF99FFA0 holds sub_eea6040, a `jmp rax` gadget
// (native_boundary.tsv: 0xeea6040 vendor, thunk via data slot 0xF99FFA0,
// loader-resolved) [V]. The net effect of each pair is a virtual call through
// the just-loaded vtable entry with rcx = the RefCounted*.
using VoidFn = void (*)(RefCounted*);

inline VoidFn vtableDestroy(RefCounted* r) {   // rax = r->vptr; rax = [rax]   (vtable[0])
    void** vt = reinterpret_cast<void**>(r->vptr);
    return reinterpret_cast<VoidFn>(vt[0]);    // vtable[0]: destroy, run when the strong count reaches 0
}
inline VoidFn vtableDealloc(RefCounted* r) {   // rax = r->vptr; rax = [rax+8] (vtable[1])
    void** vt = reinterpret_cast<void**>(r->vptr);
    return reinterpret_cast<VoidFn>(vt[1]);    // vtable[1]: dealloc, run when the weak count reaches 0
}

} // namespace

// x64 Microsoft ABI: rcx = a0 (FrameSlot*), rdx = a1 (FrameSlot*). Returns void.
//
// Moves the refcounted resource held by the slot whose flag is nonzero into the
// slot whose flag is zero. When both flags are equal and nonzero the function
// tails into sub_bc55ea0 (Slot::swap); when both are zero it is a no-op.
extern "C" void sub_bc7c4e0(FrameSlot* a0, FrameSlot* a1) {
    // 0xbc7c4e0  push rsi
    // 0xbc7c4e1  push rdi
    // 0xbc7c4e2  sub rsp,0x28
    // 0xbc7c4e6  movzx eax,byte ptr [rcx+0x10]
    std::uint8_t f0 = a0->flag;
    // 0xbc7c4ea  cmp al,[rdx+0x10]
    if (f0 == a1->flag) {
        // 0xbc7c4ed  jne short 0xBC7C4FE
        // 0xbc7c4ef  test al,al
        if (f0 == 0) {
            // 0xbc7c4f1  je short 0xBC7C56E
            // 0xbc7c56e  add rsp,0x28
            // 0xbc7c572  pop rdi
            // 0xbc7c573  pop rsi
            // 0xbc7c574  ret
            return;
        }
        // 0xbc7c4f3  add rsp,0x28
        // 0xbc7c4f7  pop rdi
        // 0xbc7c4f8  pop rsi
        // 0xbc7c4f9  jmp 0xBC55EA0
        return native::sub_bc55ea0(
            reinterpret_cast<Slot*>(a0),
            reinterpret_cast<Slot*>(a1));
    }
    // 0xbc7c4fe  test al,al
    // 0xbc7c500  mov rdi,rdx
    // 0xbc7c503  cmovne rdi,rcx
    // 0xbc7c507  cmovne rcx,rdx
    FrameSlot* src = f0 != 0 ? a0 : a1;
    FrameSlot* dst = f0 != 0 ? a1 : a0;
    // 0xbc7c50b  xorps xmm0,xmm0
    // 0xbc7c50e  movups [rcx],xmm0
    dst->raw = nullptr;
    dst->ref = nullptr;
    // 0xbc7c511  mov rax,[rdi+8]
    // 0xbc7c515  test rax,rax
    if (src->ref != nullptr) {
        // 0xbc7c518  je short 0xBC7C51E
        // 0xbc7c51a  lock inc dword ptr [rax+8]
        src->ref->strong.fetch_add(1u, std::memory_order_seq_cst);
    }
    // 0xbc7c51e  mov rax,[rdi]
    // 0xbc7c521  mov [rcx],rax
    dst->raw = src->raw;
    // 0xbc7c524  mov rax,[rdi+8]
    // 0xbc7c528  mov [rcx+8],rax
    dst->ref = src->ref;
    // 0xbc7c52c  mov byte ptr [rcx+0x10],1
    dst->flag = 1;
    // 0xbc7c530  cmp byte ptr [rdi+0x10],1
    if (src->flag == 1) {
        // 0xbc7c534  jne short 0xBC7C56E
        // 0xbc7c536  mov rsi,[rdi+8]
        RefCounted* rsi = src->ref;
        // 0xbc7c53a  test rsi,rsi
        if (rsi != nullptr) {
            // 0xbc7c53d  je short 0xBC7C56A
            // 0xbc7c53f  lock dec dword ptr [rsi+8]
            if (rsi->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                // 0xbc7c543  jne short 0xBC7C56A
                // 0xbc7c545  mov rax,[rsi]
                // 0xbc7c548  mov rax,[rax]   (vtable[0])
                VoidFn destroy = vtableDestroy(rsi);
                // 0xbc7c54b  mov rcx,rsi
                // 0xbc7c54e  call qword ptr [0xF99FFA0]
                destroy(rsi);
                // 0xbc7c554  lock dec dword ptr [rsi+0xC]
                if (rsi->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                    // 0xbc7c558  jne short 0xBC7C56A
                    // 0xbc7c55a  mov rax,[rsi]
                    // 0xbc7c55d  mov rax,[rax+8]   (vtable[1])
                    VoidFn dealloc = vtableDealloc(rsi);
                    // 0xbc7c561  mov rcx,rsi
                    // 0xbc7c564  call qword ptr [0xF99FFA0]
                    dealloc(rsi);
                }
            }
        }
        // 0xbc7c56a  mov byte ptr [rdi+0x10],0
        src->flag = 0;
    }
    // 0xbc7c56e  add rsp,0x28
    // 0xbc7c572  pop rdi
    // 0xbc7c573  pop rsi
    // 0xbc7c574  ret
    return;
}

static native::Footprint sub_bc7c4e0Footprint(FrameSlot* a0, FrameSlot* a1) {
    return {{a0, sizeof(FrameSlot)}, {a1, sizeof(FrameSlot)}};
}

LIFT_FN(sub_bc7c4e0, "native::sub_bc7c4e0", 0xbc7c4e0, sub_bc7c4e0, sub_bc7c4e0Footprint);

} // namespace native
