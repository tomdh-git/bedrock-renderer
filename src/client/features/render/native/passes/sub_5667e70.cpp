// LIFT 0x5667e70 size 0xe6 1.26.62.01 sub_5667e70
#include "sub_5667e70.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_5667e70 (0x5667e70, size 0xe6, 1.26.62.01).
//
// Full reversal of [0x5667e70, 0x5667f56):
//   0x5667e70..0x5667e76   prologue; mov rsi,rcx (a0)
//   0x5667e79..0x5667e89   if byte[a0+0x168] == 1: call sub_655cea0(&a0+0x130) (boundary/stl)
//   0x5667e8e..0x5667ed7   buffer #1 at a0+0x118/0x128: if begin1 != 0, release via sub_e935700,
//                         clear [a0+0x118..0x128) (16 bytes) and end1
//   0x5667edf..0x5667f2d   if byte[a0+0x100] == 1: same sequence for buffer #2 (a0+0xE8/0xF8)
//   0x5667f35..0x5667f3b   epilogue; ret
//   0x5667f3c..0x5667f55   fail path (heap corruption): [rsp+0x20]=0 (dead), zero args,
//                         call qword ptr [0xF9A8C78], int3 (noreturn)
//
// x64 Microsoft ABI: RCX = a0, return void. No null guards and no SEH: none exist in the original.
//
void sub_5667e70(void* a0)
{
    // 0x5667e70..0x5667e76  push rsi; push rdi; sub rsp,0x28
    // 0x5667e76             mov rsi,rcx   (a0)
    std::uint8_t* const thisObj = reinterpret_cast<std::uint8_t*>(a0);  // 0x5667e76  mov rsi,rcx

    // 0x5667e79  cmp byte ptr [rcx+0x168],1
    // 0x5667e80  jne short 0x5667E8E        ; skip sub_655cea0 when flag != 1
    if (*reinterpret_cast<const std::uint8_t*>(thisObj + Sub5667e70Layout::kOffFlag0x168) == 1) {  // 0x5667e79..0x5667e80
        // 0x5667e82  lea rcx,[rsi+0x130]    ; rcx = &a0->0x130
        // 0x5667e89  call 0x655CEA0         ; boundary/stl; argument &a0->0x130; return ignored
        native::Boundary<std::uint64_t, void*> sub_655cea0("sub_655cea0");  // 0x5667e89  call 0x655CEA0 (boundary stl; return ignored)
        sub_655cea0(reinterpret_cast<void*>(thisObj + Sub5667e70Layout::kOffStlArg));  // 0x5667e82..0x5667e89
    }

    // 0x5667e8e  mov rcx,[rsi+0x118]    ; begin1
    // 0x5667e95  test rcx,rcx
    // 0x5667e98  je short 0x5667EDF     ; skip buffer #1 when begin1 == 0
    void* const begin1 =
        *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffBegin1Ptr);  // 0x5667e8e  mov rcx,[rsi+0x118]
    if (begin1 != nullptr) {                                                   // 0x5667e95  test rcx,rcx
                                                                                 // 0x5667e98  je short 0x5667EDF (inverse)
        // 0x5667e9a  mov rdx,[rsi+0x128]    ; end1
        // 0x5667ea1  sub rdx,rcx            ; size1 = end1 - begin1 (unsigned, wraps)
        // 0x5667ea4  cmp rdx,0x1000
        const std::uint64_t size1 =
            reinterpret_cast<std::uintptr_t>(
                *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffEnd1Ptr)) -
            reinterpret_cast<std::uintptr_t>(begin1);  // 0x5667e9a  mov rdx,[rsi+0x128]
                                                       // 0x5667ea1  sub rdx,rcx
        void* deallocArg1 = nullptr;
        if (size1 < 0x1000) {                          // 0x5667eab  jb short 0x5667EC5 (inverse)
            // rcx stays begin1 -> argument = begin1
            deallocArg1 = begin1;
        } else {
            // 0x5667ead  mov rax,[rcx-8]              ; block size header at begin1-8
            // 0x5667eb1  add rcx,0xFFFFFFFFFFFFFFF8   ; begin1 - 8
            // 0x5667eb5  sub rcx,rax                  ; delta1 = (begin1-8) - blockSize1
            // 0x5667eb8  cmp rcx,0x20
            // 0x5667ebc  jae short 0x5667F3C          ; corrupt -> noreturn fail path
            const std::uintptr_t blockSize1 =
                *reinterpret_cast<const std::uintptr_t*>(
                    reinterpret_cast<const std::uint8_t*>(begin1) - 8);  // 0x5667ead  mov rax,[rcx-8]
            const std::uintptr_t delta1 =
                reinterpret_cast<std::uintptr_t>(reinterpret_cast<const std::uint8_t*>(begin1) - 8) -
                blockSize1;                                            // 0x5667eb1..0x5667eb5
            if (delta1 >= 0x20) goto fail;                             // 0x5667eb8  cmp rcx,0x20
                                                                         // 0x5667ebc  jae short 0x5667F3C
            // 0x5667ebe  add rdx,0x27           ; size1 + 0x27 (dead in sub_e935700)
            // 0x5667ec2  mov rcx,rax            ; argument = blockSize1
            (void)(size1 + 0x27);                                        // 0x5667ebe  add rdx,0x27
            deallocArg1 = reinterpret_cast<void*>(blockSize1);           // 0x5667ec2  mov rcx,rax
        }

        // 0x5667ec5  lea rdi,[rsi+0x118]        ; rdi = &a0->0x118
        // 0x5667ecc  call 0xE935700             ; rcx = deallocArg1 (rdx = size1, dead in callee)
        native::sub_e935700(deallocArg1);      // 0x5667ecc  call 0xE935700 (lift set)
        // 0x5667ed1  xorps xmm0,xmm0
        // 0x5667ed4  movups [rdi],xmm0          ; [a0+0x118..0x128) = 0  (writes +0x118,+0x120)
        // 0x5667ed7  mov qword ptr [rdi+0x10],0 ; [a0+0x128] = 0
        *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffBegin1Ptr) = nullptr;      // 0x5667ed4  movups [rdi],xmm0 (+0x118)
        *reinterpret_cast<std::uint64_t*>(thisObj + Sub5667e70Layout::kOffBegin1Mid) = 0;    // 0x5667ed4  movups [rdi],xmm0 (+0x120)
        *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffEnd1Ptr) = nullptr;        // 0x5667ed7  mov qword ptr [rdi+0x10],0
    }

    // 0x5667edf  cmp byte ptr [rsi+0x100],1
    // 0x5667ee6  jne short 0x5667F35            ; skip buffer #2 when flag != 1
    if (*reinterpret_cast<const std::uint8_t*>(thisObj + Sub5667e70Layout::kOffFlag0x100) == 1) {  // 0x5667edf..0x5667ee6
        // 0x5667ee8  lea rdi,[rsi+0xE8]         ; rdi = &a0->0xE8
        // 0x5667eef  mov rcx,[rdi]              ; begin2
        // 0x5667ef2  test rcx,rcx
        // 0x5667ef5  je short 0x5667F35         ; skip buffer #2 when begin2 == 0
        void* const begin2 =
            *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffBegin2Ptr);  // 0x5667eef  mov rcx,[rdi]
        if (begin2 != nullptr) {                                                   // 0x5667ef2  test rcx,rcx
                                                                                     // 0x5667ef5  je short 0x5667F35 (inverse)
            // 0x5667ef7  mov rdx,[rsi+0xF8]         ; end2
            // 0x5667efe  sub rdx,rcx                ; size2 = end2 - begin2 (unsigned)
            // 0x5667f01  cmp rdx,0x1000
            const std::uint64_t size2 =
                reinterpret_cast<std::uintptr_t>(
                    *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffEnd2Ptr)) -
                reinterpret_cast<std::uintptr_t>(begin2);  // 0x5667ef7  mov rdx,[rsi+0xF8]
                                                           // 0x5667efe  sub rdx,rcx
            void* deallocArg2 = nullptr;
            if (size2 < 0x1000) {                          // 0x5667f08  jb short 0x5667F22 (inverse)
                deallocArg2 = begin2;
            } else {
                // 0x5667f0a  mov rax,[rcx-8]
                // 0x5667f0e  add rcx,0xFFFFFFFFFFFFFFF8
                // 0x5667f12  sub rcx,rax
                // 0x5667f15  cmp rcx,0x20
                // 0x5667f19  jae short 0x5667F3C
                const std::uintptr_t blockSize2 =
                    *reinterpret_cast<const std::uintptr_t*>(
                        reinterpret_cast<const std::uint8_t*>(begin2) - 8);  // 0x5667f0a  mov rax,[rcx-8]
                const std::uintptr_t delta2 =
                    reinterpret_cast<std::uintptr_t>(reinterpret_cast<const std::uint8_t*>(begin2) - 8) -
                    blockSize2;                                              // 0x5667f0e..0x5667f12
                if (delta2 >= 0x20) goto fail;                               // 0x5667f15  cmp rcx,0x20
                                                                               // 0x5667f19  jae short 0x5667F3C
                // 0x5667f1b  add rdx,0x27
                // 0x5667f1f  mov rcx,rax
                (void)(size2 + 0x27);                                        // 0x5667f1b  add rdx,0x27
                deallocArg2 = reinterpret_cast<void*>(blockSize2);           // 0x5667f1f  mov rcx,rax
            }

            // 0x5667f22  call 0xE935700         ; rcx = deallocArg2
            native::sub_e935700(deallocArg2);  // 0x5667f22  call 0xE935700 (lift set)
            // 0x5667f27  xorps xmm0,xmm0
            // 0x5667f2a  movups [rdi],xmm0      ; [a0+0xE8..0xF8) = 0  (writes +0xE8,+0xF0)
            // 0x5667f2d  mov qword ptr [rdi+0x10],0 ; [a0+0xF8] = 0
            *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffBegin2Ptr) = nullptr;      // 0x5667f2a  movups [rdi],xmm0 (+0xE8)
            *reinterpret_cast<std::uint64_t*>(thisObj + Sub5667e70Layout::kOffBegin2Mid) = 0;    // 0x5667f2a  movups [rdi],xmm0 (+0xF0)
            *reinterpret_cast<void**>(thisObj + Sub5667e70Layout::kOffEnd2Ptr) = nullptr;        // 0x5667f2d  mov qword ptr [rdi+0x10],0
        }
    }

    // 0x5667f35  add rsp,0x28
    // 0x5667f39  pop rdi
    // 0x5667f3a  pop rsi
    // 0x5667f3b  ret
    return;

fail:
    // 0x5667f3c  mov qword ptr [rsp+0x20],0   ; dead stack store (never read)
    // 0x5667f45  xor ecx,ecx
    // 0x5667f47  xor edx,edx
    // 0x5667f49  xor r8d,r8d
    // 0x5667f4c  xor r9d,r9d
    // 0x5667f4f  call qword ptr [0xF9A8C78]   ; fail handler via data slot 0xF9A8C78, 4 zero args
    // 0x5667f55  int3                         ; noreturn pad
    auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
        *reinterpret_cast<const std::uintptr_t*>(0xF9A8C78ULL));  // slot read at call time
    failFn(nullptr, nullptr, nullptr, nullptr);                    // 0x5667f4f  call qword ptr [0xF9A8C78]
    __assume(false);                                               // 0x5667f55  int3  (noreturn)
}

} // namespace native

// Registry entry: name, Sigs.json symbol, knownRva, lifted function, footprint (nullptr: not pure).
LIFT_FN(sub_5667e70, "sub_5667e70", 0x5667E70, ::native::sub_5667e70, nullptr);

// Verbatim instructions of [0x5667e70, 0x5667f56) (rdis dis 0x5667e70 0xe6);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x5667e70  push rsi
0x5667e71  push rdi
0x5667e72  sub rsp,0x28
0x5667e76  mov rsi,rcx
0x5667e79  cmp byte ptr [rcx+0x168],1
0x5667e80  jne short 0x5667E8E
0x5667e82  lea rcx,[rsi+0x130]
0x5667e89  call 0x655CEA0
0x5667e8e  mov rcx,[rsi+0x118]
0x5667e95  test rcx,rcx
0x5667e98  je short 0x5667EDF
0x5667e9a  mov rdx,[rsi+0x128]
0x5667ea1  sub rdx,rcx
0x5667ea4  cmp rdx,0x1000
0x5667eab  jb short 0x5667EC5
0x5667ead  mov rax,[rcx-8]
0x5667eb1  add rcx,0xFFFFFFFFFFFFFFF8
0x5667eb5  sub rcx,rax
0x5667eb8  cmp rcx,0x20
0x5667ebc  jae short 0x5667F3C
0x5667ebe  add rdx,0x27
0x5667ec2  mov rcx,rax
0x5667ec5  lea rdi,[rsi+0x118]
0x5667ecc  call 0xE935700
0x5667ed1  xorps xmm0,xmm0
0x5667ed4  movups [rdi],xmm0
0x5667ed7  mov qword ptr [rdi+0x10],0
0x5667edf  cmp byte ptr [rsi+0x100],1
0x5667ee6  jne short 0x5667F35
0x5667ee8  lea rdi,[rsi+0xE8]
0x5667eef  mov rcx,[rdi]
0x5667ef2  test rcx,rcx
0x5667ef5  je short 0x5667F35
0x5667ef7  mov rdx,[rsi+0xF8]
0x5667efe  sub rdx,rcx
0x5667f01  cmp rdx,0x1000
0x5667f08  jb short 0x5667F22
0x5667f0a  mov rax,[rcx-8]
0x5667f0e  add rcx,0xFFFFFFFFFFFFFFF8
0x5667f12  sub rcx,rax
0x5667f15  cmp rcx,0x20
0x5667f19  jae short 0x5667F3C
0x5667f1b  add rdx,0x27
0x5667f1f  mov rcx,rax
0x5667f22  call 0xE935700
0x5667f27  xorps xmm0,xmm0
0x5667f2a  movups [rdi],xmm0
0x5667f2d  mov qword ptr [rdi+0x10],0
0x5667f35  add rsp,0x28
0x5667f39  pop rdi
0x5667f3a  pop rsi
0x5667f3b  ret
0x5667f3c  mov qword ptr [rsp+0x20],0
0x5667f45  xor ecx,ecx
0x5667f47  xor edx,edx
0x5667f49  xor r8d,r8d
0x5667f4c  xor r9d,r9d
0x5667f4f  call qword ptr [0xF9A8C78]
0x5667f55  int3
#endif
