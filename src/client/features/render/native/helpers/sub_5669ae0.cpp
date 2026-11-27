// LIFT 0x5669ae0 size 0x129 1.26.62.01 sub_5669ae0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_5669ae0.h"

#include "client/features/render/native/passes/sub_567e430.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_5669ae0, "sub_5669ae0", 0x5669ae0, sub_5669ae0, nullptr);

// Layout assertions mirroring sub_5669ae0.h (offsets proven from the listing).
static_assert(offsetof(sub_5669ae0_rcx, begin1) == 0x10, "sub_5669ae0 rcx+0x10 begin1");
static_assert(offsetof(sub_5669ae0_rcx, end1) == 0x18, "sub_5669ae0 rcx+0x18 end1");
static_assert(offsetof(sub_5669ae0_rcx, cap1) == 0x20, "sub_5669ae0 rcx+0x20 cap1");
static_assert(offsetof(sub_5669ae0_rcx, begin2) == 0xb8, "sub_5669ae0 rcx+0xb8 begin2");
static_assert(offsetof(sub_5669ae0_rcx, end2) == 0xc0, "sub_5669ae0 rcx+0xc0 end2");
static_assert(offsetof(sub_5669ae0_rcx, cap2) == 0xc8, "sub_5669ae0 rcx+0xc8 cap2");
static_assert(offsetof(sub_5669ae0_rbx, begin) == 0x0, "sub_5669ae0 rbx+0x0 begin");
static_assert(offsetof(sub_5669ae0_rbx, cap) == 0x10, "sub_5669ae0 rbx+0x10 cap");
static_assert(sizeof(sub_5669ae0_rcx) >= 0xd0, "sub_5669ae0 rcx sizeof lower bound");
static_assert(sizeof(sub_5669ae0_rbx) >= 0x18, "sub_5669ae0 rbx sizeof lower bound");

// Verbatim call instructions from the disassembly of [0x5669ae0, 0x5669c09) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x5669b13  call 0x567E430
0x5669b59  call 0xE935700
0x5669b93  call 0x567E430
0x5669bd2  call 0xE935700
0x5669c02  call qword ptr [0xF9A8C78]
#endif

// sub_5669ae0 (0x5669ae0, size 0x129, 1.26.62.01): release two inline-buffer ranges.
//
//   range #2 ([a0+0xB8, a0+0xC0), stride 0x290) is processed first, then range #1
//   ([a0+0x10, a0+0x18), stride 0x290). Every element is released through
//   sub_567e430 (lift set). After each loop the buffer's heap block is freed through
//   sub_e935700 (lift set, tail jump to sub_392960): the deallocation argument is the
//   begin pointer when the remaining span is <u 0x1000, otherwise the block size header
//   at begin-8 (validated: (begin-8) - blockSize <u 0x20, otherwise the noreturn fail
//   path call qword ptr [0xF9A8C78](0,0,0,0); int3 is taken). Each range's begin/end/cap
//   fields are then zeroed. The function returns void: no return value is set on any
//   path. No null guards and no SEH exist in the original; none are added.
//
// x64 Microsoft ABI: RCX = a0 (self), return void.
//
// Full reversal of [0x5669ae0, 0x5669c09):
//   0x5669ae0..0x5669b6c   range #2 element loop via sub_567e430, then heap free of range #2
//   0x5669b6c..0x5669be5   range #1 element loop via sub_567e430, then heap free of range #1
//   0x5669be5..0x5669bef   epilogue; ret
//   0x5669bef..0x5669c09   fail path: dead store, 4 zero args, call [0xF9A8C78], int3

void sub_5669ae0(void* self)
{
    // 0x5669ae0..0x5669ae9  push r14; push rsi; push rdi; push rbx; sub rsp,0x28
    // 0x5669ae9             mov rsi,rcx   (a0 = self)
    std::uint8_t* const thisObj = reinterpret_cast<std::uint8_t*>(self);  // 0x5669ae9  mov rsi,rcx

    // ==================================================================
    // Range #2: [a0+0xB8, a0+0xC0), stride 0x290; heap cap at a0+0xC8.
    // ==================================================================
    // 0x5669aec  mov rdi,[rsi+0xB8]    ; begin2
    // 0x5669af3  test rdi,rdi
    // 0x5669af6  je short 0x5669B6C    ; skip range #2 when begin2 == 0
    void* const begin2 =
        *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffBegin2);  // 0x5669aec  mov rdi,[rsi+0xB8]
    if (begin2 != nullptr) {                                               // 0x5669af3  test rdi,rdi
                                                                           // 0x5669af6  je short 0x5669B6C (inverse)
        // 0x5669af8  lea rbx,[rsi+0xB8]    ; rbx = &a0->0xB8
        // 0x5669aff  mov r14,[rsi+0xC0]    ; end2
        // 0x5669b06  cmp rdi,r14
        // 0x5669b09  je short 0x5669B27    ; empty range -> skip the element loop
        void** const rbx =
            reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffBegin2);  // 0x5669af8  lea rbx,[rsi+0xB8]
        void* const end2 =
            *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffEnd2);   // 0x5669aff  mov r14,[rsi+0xC0]
        if (begin2 != end2) {                                              // 0x5669b06  cmp rdi,r14
                                                                           // 0x5669b09  je short 0x5669B27 (inverse)
            // 0x5669b0b  nop [rax+rax]
            // 0x5669b10  mov rcx,rdi
            // 0x5669b13  call 0x567E430    ; sub_567e430(element)
            // 0x5669b18  add rdi,0x290
            // 0x5669b1f  cmp rdi,r14
            // 0x5669b22  jne short 0x5669B10
            void* rdi = begin2;                                            // 0x5669b10  mov rcx,rdi
            do {
                native::sub_567e430(rdi);                                  // 0x5669b13  call 0x567E430
                rdi = reinterpret_cast<void*>(
                    reinterpret_cast<std::uint8_t*>(rdi) +
                    Sub5669ae0Layout::kStride);                            // 0x5669b18  add rdi,0x290
            } while (rdi != end2);                                         // 0x5669b1f  cmp rdi,r14
                                                                           // 0x5669b22  jne short 0x5669B10
        }
        // 0x5669b24  mov rdi,[rbx]        ; rdi = begin2 (reloaded)
        // 0x5669b27  mov rdx,[rsi+0xC8]   ; cap2
        // 0x5669b2e  sub rdx,rdi          ; size2 = cap2 - begin2 (unsigned, wraps)
        // 0x5669b31  cmp rdx,0x1000
        void* rdi = *rbx;                                                // 0x5669b24  mov rdi,[rbx]
        const std::uint64_t size2 =
            reinterpret_cast<std::uintptr_t>(
                *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffCap2)) -
            reinterpret_cast<std::uintptr_t>(rdi);                       // 0x5669b27  mov rdx,[rsi+0xC8]
                                                                           // 0x5669b2e  sub rdx,rdi
        void* deallocArg2 = nullptr;
        if (size2 < 0x1000) {                                            // 0x5669b31  cmp rdx,0x1000
                                                                           // 0x5669b38  jb short 0x5669B56 (inverse)
            // rcx stays rdi -> argument = begin2
            deallocArg2 = rdi;
        } else {
            // 0x5669b3a  mov rax,[rdi-8]              ; block size header at begin2-8
            // 0x5669b3e  add rdi,0xFFFFFFFFFFFFFFF8   ; begin2 - 8
            // 0x5669b42  sub rdi,rax                  ; delta2 = (begin2-8) - blockSize2
            // 0x5669b45  cmp rdi,0x20
            // 0x5669b49  jae 0x5669BEF                ; corrupt block -> noreturn fail path
            const std::uintptr_t blockSize2 =
                *reinterpret_cast<const std::uintptr_t*>(
                    reinterpret_cast<const std::uint8_t*>(rdi) - 8);     // 0x5669b3a  mov rax,[rdi-8]
            const std::uintptr_t delta2 =
                reinterpret_cast<std::uintptr_t>(
                    reinterpret_cast<const std::uint8_t*>(rdi) - 8) -
                blockSize2;                                              // 0x5669b3e  add rdi,...FFFFFFF8
                                                                           // 0x5669b42  sub rdi,rax
            if (delta2 >= 0x20) {                                        // 0x5669b45  cmp rdi,0x20
                                                                           // 0x5669b49  jae 0x5669BEF (noreturn fail path)
                auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
                    *reinterpret_cast<const std::uintptr_t*>(
                        RewriteRegistry::imageBase() + kRvaFailSlot));    // 0x5669c02  call qword ptr [0xF9A8C78]
                failFn(nullptr, nullptr, nullptr, nullptr);
                __debugbreak();                                          // 0x5669c08  int3
                __assume(false);                                         // int3 is noreturn pad
            }
            // 0x5669b4f  add rdx,0x27           ; size2 + 0x27 (dead in sub_e935700)
            // 0x5669b53  mov rdi,rax            ; argument = blockSize2
            (void)(size2 + 0x27);                                        // 0x5669b4f  add rdx,0x27
            deallocArg2 = reinterpret_cast<void*>(blockSize2);           // 0x5669b53  mov rdi,rax
        }
        // 0x5669b56  mov rcx,rdi
        // 0x5669b59  call 0xE935700         ; rcx = deallocArg2 (rdx = size2, dead in callee)
        native::sub_e935700(deallocArg2);          // 0x5669b59  call 0xE935700 (lift set)
        // 0x5669b5e  xorps xmm0,xmm0
        // 0x5669b61  movups [rbx],xmm0          ; [a0+0xB8] = 0 and [a0+0xC0] = 0 (16-byte clear)
        // 0x5669b64  mov qword ptr [rbx+0x10],0 ; [a0+0xC8] = 0
        *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffBegin2) = nullptr;  // 0x5669b61  movups [rbx],xmm0 (+0xB8)
        *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffEnd2) = nullptr;    // 0x5669b61  movups [rbx],xmm0 (+0xC0)
        *reinterpret_cast<std::uint64_t*>(thisObj + Sub5669ae0Layout::kOffCap2) = 0;  // 0x5669b64  mov [rbx+0x10],0
    }

    // ==================================================================
    // Range #1: [a0+0x10, a0+0x18), stride 0x290; heap cap at a0+0x20.
    // ==================================================================
    // 0x5669b6c  mov rdi,[rsi+0x10]    ; begin1
    // 0x5669b70  test rdi,rdi
    // 0x5669b73  je short 0x5669BE5    ; skip range #1 when begin1 == 0 (function epilogue)
    void* const begin1 =
        *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffBegin1);  // 0x5669b6c  mov rdi,[rsi+0x10]
    if (begin1 != nullptr) {                                               // 0x5669b70  test rdi,rdi
                                                                           // 0x5669b73  je short 0x5669BE5 (inverse)
        // 0x5669b75  lea rbx,[rsi+0x10]    ; rbx = &a0->0x10
        // 0x5669b79  mov r14,[rsi+0x18]    ; end1
        // 0x5669b7d  cmp rdi,r14
        // 0x5669b80  je short 0x5669BA7    ; empty range -> skip the element loop
        void** const rbx =
            reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffBegin1);  // 0x5669b75  lea rbx,[rsi+0x10]
        void* const end1 =
            *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffEnd1);   // 0x5669b79  mov r14,[rsi+0x18]
        if (begin1 != end1) {                                              // 0x5669b7d  cmp rdi,r14
                                                                           // 0x5669b80  je short 0x5669BA7 (inverse)
            // 0x5669b82  nop [rax+rax]
            // 0x5669b90  mov rcx,rdi
            // 0x5669b93  call 0x567E430
            // 0x5669b98  add rdi,0x290
            // 0x5669b9f  cmp rdi,r14
            // 0x5669ba2  jne short 0x5669B90
            void* rdi = begin1;                                            // 0x5669b90  mov rcx,rdi
            do {
                native::sub_567e430(rdi);                                  // 0x5669b93  call 0x567E430
                rdi = reinterpret_cast<void*>(
                    reinterpret_cast<std::uint8_t*>(rdi) +
                    Sub5669ae0Layout::kStride);                            // 0x5669b98  add rdi,0x290
            } while (rdi != end1);                                         // 0x5669b9f  cmp rdi,r14
                                                                           // 0x5669ba2  jne short 0x5669B90
        }
        // 0x5669ba4  mov rdi,[rbx]        ; rdi = begin1 (reloaded)
        // 0x5669ba7  mov rdx,[rsi+0x20]   ; cap1
        // 0x5669bab  sub rdx,rdi          ; size1 = cap1 - begin1 (unsigned, wraps)
        // 0x5669bae  cmp rdx,0x1000
        void* rdi = *rbx;                                                // 0x5669ba4  mov rdi,[rbx]
        const std::uint64_t size1 =
            reinterpret_cast<std::uintptr_t>(
                *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffCap1)) -
            reinterpret_cast<std::uintptr_t>(rdi);                       // 0x5669ba7  mov rdx,[rsi+0x20]
                                                                           // 0x5669bab  sub rdx,rdi
        void* deallocArg1 = nullptr;
        if (size1 < 0x1000) {                                            // 0x5669bae  cmp rdx,0x1000
                                                                           // 0x5669bb5  jb short 0x5669BCF (inverse)
            deallocArg1 = rdi;
        } else {
            // 0x5669bb7  mov rax,[rdi-8]
            // 0x5669bbb  add rdi,0xFFFFFFFFFFFFFFF8
            // 0x5669bbf  sub rdi,rax
            // 0x5669bc2  cmp rdi,0x20
            // 0x5669bc6  jae short 0x5669BEF
            const std::uintptr_t blockSize1 =
                *reinterpret_cast<const std::uintptr_t*>(
                    reinterpret_cast<const std::uint8_t*>(rdi) - 8);
            const std::uintptr_t delta1 =
                reinterpret_cast<std::uintptr_t>(
                    reinterpret_cast<const std::uint8_t*>(rdi) - 8) -
                blockSize1;
            if (delta1 >= 0x20) {                                        // 0x5669bc2  cmp rdi,0x20
                                                                           // 0x5669bc6  jae short 0x5669BEF (noreturn fail path)
                auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
                    *reinterpret_cast<const std::uintptr_t*>(
                        RewriteRegistry::imageBase() + kRvaFailSlot));    // 0x5669c02  call qword ptr [0xF9A8C78]
                failFn(nullptr, nullptr, nullptr, nullptr);
                __debugbreak();                                          // 0x5669c08  int3
                __assume(false);                                         // int3 is noreturn pad
            }
            // 0x5669bc8  add rdx,0x27
            // 0x5669bcc  mov rdi,rax
            (void)(size1 + 0x27);
            deallocArg1 = reinterpret_cast<void*>(blockSize1);
        }
        // 0x5669bcf  mov rcx,rdi
        // 0x5669bd2  call 0xE935700
        native::sub_e935700(deallocArg1);  // 0x5669bd2  call 0xE935700 (lift set)
        // 0x5669bd7  xorps xmm0,xmm0
        // 0x5669bda  movups [rbx],xmm0    ; [a0+0x10] = 0 and [a0+0x18] = 0 (16-byte clear)
        // 0x5669bdd  mov qword ptr [rbx+0x10],0 ; [a0+0x20] = 0
        *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffBegin1) = nullptr;  // 0x5669bda  movups [rbx],xmm0 (+0x10)
        *reinterpret_cast<void**>(thisObj + Sub5669ae0Layout::kOffEnd1) = nullptr;    // 0x5669bda  movups [rbx],xmm0 (+0x18)
        *reinterpret_cast<std::uint64_t*>(thisObj + Sub5669ae0Layout::kOffCap1) = 0;  // 0x5669bdd  mov [rbx+0x10],0
    }

    // 0x5669be5  add rsp,0x28
    // 0x5669be9  pop rbx
    // 0x5669bea  pop rdi
    // 0x5669beb  pop rsi
    // 0x5669bec  pop r14
    // 0x5669bee  ret
    return;
}

} // namespace native::helpers
