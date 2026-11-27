// LIFT 0x66397e0 size 0x6d 1.26.62.01 BgfxFrameBuilder slot 74
#include "sub_66397e0.h"

#include <atomic>
#include <cstdint>

static_assert(sizeof(void*) == 8, "sub_66397e0: x64 ABI, pointer-sized address space");

namespace native {

// sub_66397e0 (0x66397e0, size 0x6d, 1.26.62.01, "BgfxFrameBuilder slot 74").
//
// Whole function: // 0x66397e0..0x663984c  (every instruction lies inside this range).
// Phase 1   // 0x66397e0..0x66397ef  prologue: RSI = out (RDX), RDI = self (RCX);
//          RAX = *(self + 0x000) vtable pointer; RAX = *(RAX + 0x228) = BgfxFrameBuilder vtable
//          slot 74 target, left in RAX as the out-of-ABI argument the trampoline below expects.
// Phase 2   // 0x66397f6  call qword ptr [0xF99FFA0]  ->  native::boundary::g_eea6040_thunk
//          (sub_eea6040, boundary/vendor); enters with RAX = target, RCX = self, RDX = out;
//          body `jmp rax` tails to *RAX(RCX, RDX); result in AL.
// Phase 3   // 0x66397fc..0x66397fe  test al,al / je short 0x6639832  -> AL == 0: zero path.
// Phase 4   // 0x6639800..0x663980a  mov rax,[rdi+0x288] / test rax,rax / je short 0x6639832
//          -> null: same zero path.
// Phase 5   // 0x663980c..0x663980f  xorps xmm0,xmm0 / movups [rsi],xmm0  -> out = {0,0}.
// Phase 6   // 0x6639812..0x663981c  mov rcx,[rdi+0x290] / test rcx,rcx / je short 0x663983a
//          -> null: refObject stored as 0 below.
// Phase 7   // 0x663981e  lock inc dword ptr [rcx+8]  -> refcount of self->field0x290 + 1.
// Phase 8   // 0x6639822..0x6639830  re-read self+0x288 and self+0x290.
// Phase 9   // 0x663983c..0x663983f  mov [rsi],rax / mov [rsi+8],rcx  -> out = {self+0x288, self+0x290}.
// Phase 10  // 0x6639843..0x663984c  mov rax,rsi / add rsp,0x28 / pop rdi / pop rsi / ret  -> return out.
void* sub_66397e0(void* selfArg /*RCX: self = BgfxFrameBuilder*/,
                  FrameBuilderSlot74* outArg /*RDX: out*/) {
    void* const self = selfArg;               // 0x66397e9 mov rdi,rcx
    FrameBuilderSlot74* const out = outArg;   // 0x66397e6 mov rsi,rdx
    const BgfxFrameBuilderPartial74* const fb =
        reinterpret_cast<const BgfxFrameBuilderPartial74*>(self);

    // 0x66397e0..0x66397ef
    //   0x66397e0  push rsi
    //   0x66397e1  push rdi
    //   0x66397e2  sub rsp,0x28
    //   0x66397e6  mov rsi,rdx
    //   0x66397e9  mov rdi,rcx
    //   0x66397ec  mov rax,[rcx]                         ; R self+0x000: vtable pointer
    //   0x66397ef  mov rax,[rax+0x228]                   ; R *(self+0x000)+0x228: vtable slot 74 -> RAX
    const void* const vtable = *reinterpret_cast<const void* const*>(self);
    const void* const trampolineTarget =
        *reinterpret_cast<const void* const*>(
            reinterpret_cast<const std::uint8_t*>(vtable) + kFbVtableSlotByteOffset0x228);
    // trampolineTarget is the value the original left in RAX before the call: sub_eea6040's body is
    // `jmp rax`, so RAX is an out-of-ABI argument (the trampoline target) and still holds it at
    // call entry because nothing between the load above and the call below touches RAX.
    (void)trampolineTarget;  // read kept to mirror the load at 0x66397ef

    // 0x66397f6  call qword ptr [0xF99FFA0]   ->  native::boundary::g_eea6040_thunk (sub_eea6040,
    //          boundary/vendor; body `jmp rax` -> tails to the vtable-slot-74 target).
    const std::uint8_t callResult = native::boundary::g_eea6040_thunk(self, out);

    // 0x66397fc  test al,al
    // 0x66397fe  je short 0x6639832          ; AL == 0 -> zero path
    if (callResult == 0) {
        // 0x6639832..0x6639838 : out = {0,0}; return out
        out->ptr = nullptr;
        out->refObject = nullptr;
        return out;          // 0x6639838 jmp short 0x6639843; 0x6639843 mov rax,rsi; ret
    }

    // 0x6639800  mov rax,[rdi+0x288]   ; R self+0x288
    // 0x6639807  test rax,rax
    // 0x663980a  je short 0x6639832   ; null -> zero path
    void* ptrValue = fb->field0x288;
    if (ptrValue == nullptr) {
        out->ptr = nullptr;
        out->refObject = nullptr;
        return out;
    }

    // 0x663980c  xorps xmm0,xmm0
    // 0x663980f  movups [rsi],xmm0     ; W out+0x0..0x10 = {0,0}
    out->ptr = nullptr;
    out->refObject = nullptr;

    // 0x6639812  mov rcx,[rdi+0x290]   ; R self+0x290
    // 0x6639819  test rcx,rcx
    // 0x663981c  je short 0x663983a   ; null -> refObject stored as 0 below
    void* refObj = fb->field0x290;
    if (refObj != nullptr) {
        // 0x663981e  lock inc dword ptr [rcx+8]   ; W *(self->field0x290 + 0x8): refcount +1
        std::atomic<std::uint32_t>* const refCount =
            reinterpret_cast<std::atomic<std::uint32_t>*>(
                reinterpret_cast<std::uint8_t*>(refObj) + kRefcountOffset0x8);
        refCount->fetch_add(1u, std::memory_order_relaxed);
    }

    // 0x6639822  mov rax,[rdi+0x288]   ; R self+0x288 (re-read)
    // 0x6639829  mov rcx,[rdi+0x290]   ; R self+0x290 (re-read)
    // 0x6639830  jmp short 0x663983c
    // 0x663983c  mov [rsi],rax         ; W out+0x0
    // 0x663983f  mov [rsi+8],rcx       ; W out+0x8
    ptrValue = fb->field0x288;         // re-read, matches 0x6639822
    refObj = fb->field0x290;           // re-read, matches 0x6639829
    out->ptr = ptrValue;
    out->refObject = refObj;

    // 0x6639843..0x663984c : mov rax,rsi; add rsp,0x28; pop rdi; pop rsi; ret   ; return out
    return out;
}

} // namespace native

LIFT_FN(sub_66397e0, "BgfxFrameBuilder slot 74", 0x66397e0, sub_66397e0, nullptr);

#if 0
// Verbatim instructions of the function (rdis dis 0x66397e0 0x6d); machine-checked by
// tools/sigs/verify_oc.py against the exe.
0x66397e0  push rsi
0x66397e1  push rdi
0x66397e2  sub rsp,0x28
0x66397e6  mov rsi,rdx
0x66397e9  mov rdi,rcx
0x66397ec  mov rax,[rcx]
0x66397ef  mov rax,[rax+0x228]
0x66397f6  call qword ptr [0xF99FFA0]
0x66397fc  test al,al
0x66397fe  je short 0x6639832
0x6639800  mov rax,[rdi+0x288]
0x6639807  test rax,rax
0x663980a  je short 0x6639832
0x663980c  xorps xmm0,xmm0
0x663980f  movups [rsi],xmm0
0x6639812  mov rcx,[rdi+0x290]
0x6639819  test rcx,rcx
0x663981c  je short 0x663983a
0x663981e  lock inc dword ptr [rcx+8]
0x6639822  mov rax,[rdi+0x288]
0x6639829  mov rcx,[rdi+0x290]
0x6639830  jmp short 0x663983c
0x6639832  xorps xmm0,xmm0
0x6639835  movups [rsi],xmm0
0x6639838  jmp short 0x6639843
0x663983a  xor ecx,ecx
0x663983c  mov [rsi],rax
0x663983f  mov [rsi+8],rcx
0x6639843  mov rax,rsi
0x6639846  add rsp,0x28
0x663984a  pop rdi
0x663984b  pop rsi
0x663984c  ret
#endif
