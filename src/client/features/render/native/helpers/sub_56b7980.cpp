// LIFT 0x56b7980 size 0xfc 1.26.62.01 sub_56b7980
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56b7980.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {
// sub_e935700 (0xe935700): tail jump to sub_392960 (lift set).
// Argument in RCX (ptr), size in RDX; result in RAX (dead on the dealloc paths here).
void* sub_e935700(void* ptr, std::uintptr_t size);
} // namespace native

namespace native::helpers {

// 0x56b7a62: validation-failure path.
//   0x56b7a62  mov qword ptr [rsp+0x20],0
//   0x56b7a6b  xor ecx,ecx
//   0x56b7a6d  xor edx,edx
//   0x56b7a6f  xor r8d,r8d
//   0x56b7a72  xor r9d,r9d
//   0x56b7a75  call qword ptr [0xF9A8C78]   ; loader-resolved fail handler via data slot, noreturn
//   0x56b7a7b  int3
[[noreturn]] static void reportFail() {
    using FailFn = void(__cdecl*)(void*, void*, void*, void*);
    reinterpret_cast<FailFn>(*reinterpret_cast<std::uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78))(nullptr, nullptr, nullptr, nullptr);
    __assume(false);
}

uintptr_t sub_56b7980(sub_56b7980_state* self) {
    // 0x56b7980..0x56b799a: basic block 0 (prologue + null test of mFirst)
    // 0x56b7980  push r14
    // 0x56b7982  push rsi
    // 0x56b7983  push rdi
    // 0x56b7984  push rbx
    // 0x56b7985  sub rsp,0x48
    // 0x56b7989  movaps [rsp+0x30],xmm6
    // 0x56b798e  mov rdi,[rcx]           ; rdi = self->mFirst (+0x00)
    // 0x56b7991  test rdi,rdi
    // 0x56b7994  je 0x56B7A53            ; if mFirst == 0 goto L_0x56b7a53
    std::uintptr_t rdi = reinterpret_cast<std::uintptr_t>(self->mFirst);
    if (rdi == 0) {
        // 0x56b7a53..0x56b7a62: basic block 16 (epilogue + ret)
        // 0x56b7a53  movaps xmm6,[rsp+0x30]
        // 0x56b7a58  add rsp,0x48
        // 0x56b7a5c  pop rbx
        // 0x56b7a5d  pop rdi
        // 0x56b7a5e  pop rsi
        // 0x56b7a5f  pop r14
        // 0x56b7a61  ret
        // rax is undefined on this path in the original; lift returns 0.
        return 0;
    }

    // 0x56b799a..0x56b79a6: basic block 1
    // 0x56b799a  mov rsi,rcx              ; rsi = self
    // 0x56b799d  mov rbx,[rcx+8]          ; rbx = self->mLimit (+0x08)
    // 0x56b79a1  cmp rdi,rbx
    // 0x56b79a4  je short 0x56B7A15      ; if mFirst == mLimit goto L_0x56b7a15
    std::uintptr_t const rbx = reinterpret_cast<std::uintptr_t>(self->mLimit);
    std::uintptr_t result = 0;
    if (rdi != rbx) {
        // 0x56b79a6..0x56b79ab: basic block 2 + 3
        // 0x56b79a6  xorps xmm6,xmm6      ; xmm6 = 0
        // 0x56b79a9  jmp short 0x56B79CD  ; goto L_0x56b79cd
        // 0x56b79ab  nop [rax+rax]

        // 0x56b79cd..0x56b7a12: sub-buffer descriptor loop (blocks 4..11)
        while (true) {
            // 0x56b79cd..0x56b79d6: basic block 6
            // 0x56b79cd  cmp byte ptr [rdi+0x100],1   ; elem->mFlag (+0x100)
            // 0x56b79d4  jne short 0x56B79C1          ; if mFlag != 1 goto advance
            BufferElement* const elem = reinterpret_cast<BufferElement*>(
                reinterpret_cast<void*>(rdi));
            if (elem->mFlag == 1) {
                // 0x56b79d6..0x56b79e5: basic block 7
                // 0x56b79d6  lea r14,[rdi+0xE8]       ; r14 = &elem->mBegin
                // 0x56b79dd  mov rcx,[r14]            ; rcx = elem->mBegin (+0xe8)
                // 0x56b79e0  test rcx,rcx
                // 0x56b79e3  je short 0x56B79C1       ; if mBegin == 0 goto advance
                std::uintptr_t const rcx =
                    reinterpret_cast<std::uintptr_t>(elem->mBegin);
                if (rcx != 0) {
                    // 0x56b79e5..0x56b79f8: basic block 8
                    // 0x56b79e5  mov rdx,[rdi+0xF8]   ; rdx = elem->mEnd (+0xf8)
                    // 0x56b79ec  sub rdx,rcx          ; rdx = mEnd - mBegin (size)
                    // 0x56b79ef  cmp rdx,0x1000
                    // 0x56b79f6  jb short 0x56B79B0   ; if size <u 0x1000 goto dealloc_small
                    std::uintptr_t const size =
                        reinterpret_cast<std::uintptr_t>(elem->mEnd) - rcx;
                    if (size < 0x1000ull) {
                        // 0x56b79b0..0x56b79c1: basic block 4 (dealloc, small)
                        // 0x56b79b0  call 0xE935700            ; sub_e935700(mBegin, size)
                        // 0x56b79b5  movups [r14],xmm6       ; mBegin = 0
                        // 0x56b79b9  mov qword ptr [r14+0x10],0  ; mEnd = 0
                        result = reinterpret_cast<std::uintptr_t>(
                            native::sub_e935700(reinterpret_cast<void*>(rcx),
                                                size));
                        elem->mBegin = nullptr;
                        elem->mEnd = nullptr;
                    } else {
                        // 0x56b79f8..0x56b7a09: basic block 9 + 10 (dealloc, large)
                        // 0x56b79f8  mov rax,[rcx-8]              ; rax = *(mBegin - 8)
                        // 0x56b79fc  add rcx,0xFFFFFFFFFFFFFFF8   ; rcx = mBegin - 8
                        // 0x56b7a00  sub rcx,rax                  ; rcx = (mBegin-8) - hdr
                        // 0x56b7a03  cmp rcx,0x20
                        // 0x56b7a07  jae short 0x56B7A62          ; if >=u 0x20 goto fail
                        std::uintptr_t const hdr =
                            *reinterpret_cast<const std::uintptr_t*>(
                                reinterpret_cast<const std::uint8_t*>(rcx) - 8);
                        std::uintptr_t const delta = rcx - 8 - hdr;
                        if (delta >= 0x20ull) {
                            reportFail();  // 0x56b7a62: fail handler (noreturn)
                            __assume(false);
                        }
                        // 0x56b7a09  add rdx,0x27                 ; size + 0x27
                        // 0x56b7a0d  mov rcx,rax                  ; rcx = hdr
                        // 0x56b7a10  jmp short 0x56B79B0          ; dealloc
                        result = reinterpret_cast<std::uintptr_t>(
                            native::sub_e935700(reinterpret_cast<void*>(hdr),
                                                size + 0x27));
                        elem->mBegin = nullptr;
                        elem->mEnd = nullptr;
                    }
                }
            }

            // 0x56b79c1..0x56b79cd: basic block 5 (advance)
            // 0x56b79c1  add rdi,0x140
            // 0x56b79c8  cmp rdi,rbx
            // 0x56b79cb  je short 0x56B7A12   ; if rdi == mLimit goto exit loop
            rdi += 0x140;
            if (rdi == rbx) break;
        }
    }

    // 0x56b7a12..0x56b7a15: basic block 11
    // 0x56b7a12  mov rdi,[rsi]            ; rdi = self->mFirst (+0x00)
    rdi = reinterpret_cast<std::uintptr_t>(self->mFirst);

    // 0x56b7a15..0x56b7a3d: basic blocks 12-14 (main buffer dealloc)
    // 0x56b7a15  mov rdx,[rsi+0x10]       ; rdx = self->mMainEnd (+0x10)
    // 0x56b7a19  sub rdx,rdi              ; rdx = mMainEnd - mFirst (size)
    // 0x56b7a1c  cmp rdx,0x1000
    // 0x56b7a23  jb short 0x56B7A3D       ; if size <u 0x1000 goto dealloc_main_small
    std::uintptr_t const mainSize =
        reinterpret_cast<std::uintptr_t>(self->mMainEnd) - rdi;
    if (mainSize < 0x1000ull) {
        // 0x56b7a3d..0x56b7a53: basic block 15 (dealloc main, small)
        // 0x56b7a3d  mov rcx,rdi          ; rcx = mFirst
        // 0x56b7a40  call 0xE935700       ; sub_e935700(mFirst, size)
        result = reinterpret_cast<std::uintptr_t>(
            native::sub_e935700(reinterpret_cast<void*>(rdi),
                                mainSize));
    } else {
        // 0x56b7a25..0x56b7a3d: basic blocks 13-14 (dealloc main, large)
        // 0x56b7a25  mov rax,[rdi-8]              ; rax = *(mFirst - 8)
        // 0x56b7a29  add rdi,0xFFFFFFFFFFFFFFF8   ; rdi = mFirst - 8
        // 0x56b7a2d  sub rdi,rax                  ; rdi = (mFirst-8) - hdr
        // 0x56b7a30  cmp rdi,0x20
        // 0x56b7a34  jae short 0x56B7A62          ; if >=u 0x20 goto fail
        std::uintptr_t const hdr =
            *reinterpret_cast<const std::uintptr_t*>(
                reinterpret_cast<const std::uint8_t*>(rdi) - 8);
        std::uintptr_t const delta = rdi - 8 - hdr;
        if (delta >= 0x20ull) {
            reportFail();  // 0x56b7a62: fail handler (noreturn)
            __assume(false);
        }
        // 0x56b7a36  or rdx,0x27            ; size | 0x27
        // 0x56b7a3a  mov rdi,rax            ; rdi = hdr
        // 0x56b7a3d  mov rcx,rdi            ; rcx = hdr
        // 0x56b7a40  call 0xE935700         ; sub_e935700(hdr, size | 0x27)
        result = reinterpret_cast<std::uintptr_t>(
            native::sub_e935700(reinterpret_cast<void*>(hdr),
                                mainSize | 0x27));
    }

    // 0x56b7a45..0x56b7a53: basic block 15 tail
    // 0x56b7a45  xorps xmm0,xmm0
    // 0x56b7a48  movups [rsi],xmm0          ; self->mFirst = 0
    // 0x56b7a4b  mov qword ptr [rsi+0x10],0 ; self->mMainEnd = 0
    self->mFirst = nullptr;
    self->mMainEnd = nullptr;

    // 0x56b7a53..0x56b7a62: basic block 16 (epilogue + ret)
    // 0x56b7a53  movaps xmm6,[rsp+0x30]
    // 0x56b7a58  add rsp,0x48
    // 0x56b7a5c  pop rbx
    // 0x56b7a5d  pop rdi
    // 0x56b7a5e  pop rsi
    // 0x56b7a5f  pop r14
    // 0x56b7a61  ret
    return result;
}

LIFT_FN(sub_56b7980, "sub_56b7980", 0x56b7980, sub_56b7980, nullptr);

// Verbatim call instructions from the disassembly of [0x56b7980, 0x56b7a7c) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56b79b0  call 0xE935700
0x56b7a40  call 0xE935700
0x56b7a75  call qword ptr [0xF9A8C78]
#endif

} // namespace native::helpers
