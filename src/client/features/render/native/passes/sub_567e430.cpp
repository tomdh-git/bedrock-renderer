// LIFT 0x567e430 size 0xdd 1.26.62.01 sub_567e430
#include "sub_567e430.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_567e430 (0x567e430, size 0xdd, 1.26.62.01).
//
// pass-tasks inline-buffer release: calls the boundary/stl helper sub_655cea0 on &a0+0x258,
// then releases two inline buffers (a0+0x240/0x250, and a0+0xE8/0xF8 when byte a0+0x100 == 1)
// through sub_e935700 (lift set, tail jump to sub_392960), nulling each pointer pair.
// On heap-header corruption (computed bias >= 0x20) it takes a noreturn fail path:
// call qword ptr [0xF9A8C78](0,0,0,0); int3.
//
// Full reversal of [0x567e430, 0x567e50d):
//   0x567e430..0x567e436   prologue; mov rsi,rcx (a0)
//   0x567e439..0x567e440   rcx = a0 + 0x258; call 0x655CEA0 (boundary/stl; argument &a0->0x258)
//   0x567e445..0x567e47c   buffer #1: begin=[a0+0x240]; if 0 skip to second buffer;
//                          size = [a0+0x250]-begin; if size < 0x1000 arg=begin,
//                          else blockSize=[begin-8]; delta=(begin-8)-blockSize; if delta >= 0x20 fail;
//                          else arg=blockSize (size+0x27 is dead)
//   0x567e47c..0x567e496   call sub_e935700(arg); clear [a0+0x240..0x250) (+0x240,+0x248,+0x250)
//   0x567e496..0x567e4ec   if byte [a0+0x100] == 1: same sequence for buffer #2 ([a0+0xE8],[a0+0xF8])
//   0x567e4ec..0x567e4f2   epilogue; ret
//   0x567e4f3..0x567e50d   fail path: [rsp+0x20]=0 (dead), zero args, call [0xF9A8C78], int3 (noreturn)
//
// x64 Microsoft ABI: RCX = a0, return void. No null guards and no SEH: none exist in the original.
//
void sub_567e430(void* a0)
{
    // 0x567e430..0x567e436  push rsi; push rdi; sub rsp,0x28
    // 0x567e436             mov rsi,rcx   (a0)
    std::uint8_t* const thisObj = reinterpret_cast<std::uint8_t*>(a0);  // 0x567e436  mov rsi,rcx

    // 0x567e439  add rcx,0x258          ; rcx = &a0->0x250 (end-pointer field)
    // 0x567e440  call 0x655CEA0         ; boundary/stl; argument &a0->0x250; return ignored
    native::Boundary<std::uint64_t, void*> sub_655cea0("sub_655cea0");  // 0x567e440  call 0x655CEA0 (boundary stl; return ignored)
    sub_655cea0(reinterpret_cast<void*>(thisObj + Sub567e430Layout::kOffEnd1Ptr));  // 0x567e439..0x567e440

    // 0x567e445  mov rcx,[rsi+0x240]    ; begin1
    // 0x567e44c  test rcx,rcx
    // 0x567e44f  je short 0x567E496     ; skip buffer #1 when begin1 == 0
    void* const begin1 =
        *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffBegin1Ptr);  // 0x567e445  mov rcx,[rsi+0x240]
    if (begin1 != nullptr) {                                               // 0x567e44c  test rcx,rcx
                                                                           // 0x567e44f  je short 0x567E496 (inverse)
        // 0x567e451  mov rdx,[rsi+0x250]    ; end1
        // 0x567e458  sub rdx,rcx            ; size1 = end1 - begin1 (unsigned, wraps)
        // 0x567e45b  cmp rdx,0x1000
        const std::uint64_t size1 =
            reinterpret_cast<std::uintptr_t>(
                *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffEnd1Ptr)) -
            reinterpret_cast<std::uintptr_t>(begin1);  // 0x567e451  mov rdx,[rsi+0x250]
                                                       // 0x567e458  sub rdx,rcx
        void* deallocArg1 = nullptr;
        if (size1 < 0x1000) {                          // 0x567e462  jb short 0x567E47C (inverse)
            // rcx stays begin1 -> argument = begin1
            deallocArg1 = begin1;
        } else {
            // 0x567e464  mov rax,[rcx-8]              ; block size header at begin1-8
            // 0x567e468  add rcx,0xFFFFFFFFFFFFFFF8   ; begin1 - 8
            // 0x567e46c  sub rcx,rax                  ; delta1 = (begin1-8) - blockSize1
            // 0x567e46f  cmp rcx,0x20
            // 0x567e473  jae short 0x567E4F3          ; corrupt -> noreturn fail path
            const std::uintptr_t blockSize1 =
                *reinterpret_cast<const std::uintptr_t*>(
                    reinterpret_cast<const std::uint8_t*>(begin1) - 8);  // 0x567e464  mov rax,[rcx-8]
            const std::uintptr_t delta1 =
                reinterpret_cast<std::uintptr_t>(reinterpret_cast<const std::uint8_t*>(begin1) - 8) -
                blockSize1;                                            // 0x567e468..0x567e46c
            if (delta1 >= 0x20) goto fail;                             // 0x567e46f  cmp rcx,0x20
                                                                       // 0x567e473  jae short 0x567E4F3
            // 0x567e475  add rdx,0x27           ; size1 + 0x27 (dead in sub_e935700)
            // 0x567e479  mov rcx,rax            ; argument = blockSize1
            (void)(size1 + 0x27);                                        // 0x567e475  add rdx,0x27
            deallocArg1 = reinterpret_cast<void*>(blockSize1);           // 0x567e479  mov rcx,rax
        }

        // 0x567e47c  lea rdi,[rsi+0x240]        ; rdi = &a0->0x240
        // 0x567e483  call 0xE935700             ; rcx = deallocArg1 (rdx = size1, dead in callee)
        native::sub_e935700(deallocArg1);      // 0x567e483  call 0xE935700 (lift set)
        // 0x567e488  xorps xmm0,xmm0
        // 0x567e48b  movups [rdi],xmm0          ; [a0+0x240..0x250) = 0  (writes +0x240,+0x248)
        // 0x567e48e  mov qword ptr [rdi+0x10],0 ; [a0+0x250] = 0
        *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffBegin1Ptr) = nullptr;      // 0x567e48b  movups [rdi],xmm0 (+0x240)
        *reinterpret_cast<std::uint64_t*>(thisObj + Sub567e430Layout::kOffBegin1Mid) = 0;    // 0x567e48b  movups [rdi],xmm0 (+0x248)
        *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffEnd1Ptr) = nullptr;        // 0x567e48e  mov qword ptr [rdi+0x10],0
    }

    // 0x567e496  cmp byte ptr [rsi+0x100],1
    // 0x567e49d  jne short 0x567E4EC            ; skip buffer #2 when flag != 1
    if (*reinterpret_cast<const std::uint8_t*>(thisObj + Sub567e430Layout::kOffFlag0x100) == 1) {  // 0x567e496..0x567e49d
        // 0x567e49f  lea rdi,[rsi+0xE8]         ; rdi = &a0->0xE8
        // 0x567e4a6  mov rcx,[rdi]              ; begin2
        // 0x567e4a9  test rcx,rcx
        // 0x567e4ac  je short 0x567E4EC         ; skip buffer #2 when begin2 == 0
        void* const begin2 =
            *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffBegin2Ptr);  // 0x567e4a6  mov rcx,[rdi]
        if (begin2 != nullptr) {                                                   // 0x567e4a9  test rcx,rcx
                                                                                   // 0x567e4ac  je short 0x567E4EC (inverse)
            // 0x567e4ae  mov rdx,[rsi+0xF8]         ; end2
            // 0x567e4b5  sub rdx,rcx                ; size2 = end2 - begin2 (unsigned)
            // 0x567e4b8  cmp rdx,0x1000
            const std::uint64_t size2 =
                reinterpret_cast<std::uintptr_t>(
                    *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffEnd2Ptr)) -
                reinterpret_cast<std::uintptr_t>(begin2);  // 0x567e4ae  mov rdx,[rsi+0xF8]
                                                           // 0x567e4b5  sub rdx,rcx
            void* deallocArg2 = nullptr;
            if (size2 < 0x1000) {                          // 0x567e4bf  jb short 0x567E4D9 (inverse)
                deallocArg2 = begin2;
            } else {
                // 0x567e4c1  mov rax,[rcx-8]
                // 0x567e4c5  add rcx,0xFFFFFFFFFFFFFFF8
                // 0x567e4c9  sub rcx,rax
                // 0x567e4cc  cmp rcx,0x20
                // 0x567e4d0  jae short 0x567E4F3
                const std::uintptr_t blockSize2 =
                    *reinterpret_cast<const std::uintptr_t*>(
                        reinterpret_cast<const std::uint8_t*>(begin2) - 8);  // 0x567e4c1  mov rax,[rcx-8]
                const std::uintptr_t delta2 =
                    reinterpret_cast<std::uintptr_t>(reinterpret_cast<const std::uint8_t*>(begin2) - 8) -
                    blockSize2;                                              // 0x567e4c5..0x567e4c9
                if (delta2 >= 0x20) goto fail;                               // 0x567e4cc  cmp rcx,0x20
                                                                             // 0x567e4d0  jae short 0x567E4F3
                // 0x567e4d2  add rdx,0x27
                // 0x567e4d6  mov rcx,rax
                (void)(size2 + 0x27);                                        // 0x567e4d2  add rdx,0x27
                deallocArg2 = reinterpret_cast<void*>(blockSize2);           // 0x567e4d6  mov rcx,rax
            }

            // 0x567e4d9  call 0xE935700         ; rcx = deallocArg2
            native::sub_e935700(deallocArg2);  // 0x567e4d9  call 0xE935700 (lift set)
            // 0x567e4de  xorps xmm0,xmm0
            // 0x567e4e1  movups [rdi],xmm0      ; [a0+0xE8..0xF8) = 0  (writes +0xE8,+0xF0)
            // 0x567e4e4  mov qword ptr [rdi+0x10],0 ; [a0+0xF8] = 0
            *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffBegin2Ptr) = nullptr;      // 0x567e4e1  movups [rdi],xmm0 (+0xE8)
            *reinterpret_cast<std::uint64_t*>(thisObj + Sub567e430Layout::kOffBegin2Mid) = 0;    // 0x567e4e1  movups [rdi],xmm0 (+0xF0)
            *reinterpret_cast<void**>(thisObj + Sub567e430Layout::kOffEnd2Ptr) = nullptr;        // 0x567e4e4  mov qword ptr [rdi+0x10],0
        }
    }

    // 0x567e4ec  add rsp,0x28
    // 0x567e4f0  pop rdi
    // 0x567e4f1  pop rsi
    // 0x567e4f2  ret
    return;

fail:
    // 0x567e4f3  mov qword ptr [rsp+0x20],0   ; dead stack store (never read)
    // 0x567e4fc  xor ecx,ecx
    // 0x567e4fe  xor edx,edx
    // 0x567e500  xor r8d,r8d
    // 0x567e503  xor r9d,r9d
    // 0x567e506  call qword ptr [0xF9A8C78]   ; fail handler via data slot 0xF9A8C78, 4 zero args
    // 0x567e50c  int3                         ; noreturn pad
    auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
        *reinterpret_cast<const std::uintptr_t*>(
            RewriteRegistry::imageBase() + kRvaFailSlot));  // slot read at call time
    failFn(nullptr, nullptr, nullptr, nullptr);                             // 0x567e506  call qword ptr [0xF9A8C78]
    __debugbreak();                                                         // 0x567e50c  int3
    __assume(false);                                                        // int3 is noreturn pad
}

} // namespace native

// Registry entry: name, Sigs.json symbol, knownRva, lifted function, footprint (nullptr: not pure).
LIFT_FN(sub_567e430, "sub_567e430", 0x567E430, ::native::sub_567e430, nullptr);

// Verbatim instructions of [0x567e430, 0x567e50d) (rdis dis 0x567e430 0xdd);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x567e430  push rsi
0x567e431  push rdi
0x567e432  sub rsp,0x28
0x567e436  mov rsi,rcx
0x567e439  add rcx,0x258
0x567e440  call 0x655CEA0
0x567e445  mov rcx,[rsi+0x240]
0x567e44c  test rcx,rcx
0x567e44f  je short 0x567E496
0x567e451  mov rdx,[rsi+0x250]
0x567e458  sub rdx,rcx
0x567e45b  cmp rdx,0x1000
0x567e462  jb short 0x567E47C
0x567e464  mov rax,[rcx-8]
0x567e468  add rcx,0xFFFFFFFFFFFFFFF8
0x567e46c  sub rcx,rax
0x567e46f  cmp rcx,0x20
0x567e473  jae short 0x567E4F3
0x567e475  add rdx,0x27
0x567e479  mov rcx,rax
0x567e47c  lea rdi,[rsi+0x240]
0x567e483  call 0xE935700
0x567e488  xorps xmm0,xmm0
0x567e48b  movups [rdi],xmm0
0x567e48e  mov qword ptr [rdi+0x10],0
0x567e496  cmp byte ptr [rsi+0x100],1
0x567e49d  jne short 0x567E4EC
0x567e49f  lea rdi,[rsi+0xE8]
0x567e4a6  mov rcx,[rdi]
0x567e4a9  test rcx,rcx
0x567e4ac  je short 0x567E4EC
0x567e4ae  mov rdx,[rsi+0xF8]
0x567e4b5  sub rdx,rcx
0x567e4b8  cmp rdx,0x1000
0x567e4bf  jb short 0x567E4D9
0x567e4c1  mov rax,[rcx-8]
0x567e4c5  add rcx,0xFFFFFFFFFFFFFFF8
0x567e4c9  sub rcx,rax
0x567e4cc  cmp rcx,0x20
0x567e4d0  jae short 0x567E4F3
0x567e4d2  add rdx,0x27
0x567e4d6  mov rcx,rax
0x567e4d9  call 0xE935700
0x567e4de  xorps xmm0,xmm0
0x567e4e1  movups [rdi],xmm0
0x567e4e4  mov qword ptr [rdi+0x10],0
0x567e4ec  add rsp,0x28
0x567e4f0  pop rdi
0x567e4f1  pop rsi
0x567e4f2  ret
0x567e4f3  mov qword ptr [rsp+0x20],0
0x567e4fc  xor ecx,ecx
0x567e4fe  xor edx,edx
0x567e500  xor r8d,r8d
0x567e503  xor r9d,r9d
0x567e506  call qword ptr [0xF9A8C78]
0x567e50c  int3
#endif
