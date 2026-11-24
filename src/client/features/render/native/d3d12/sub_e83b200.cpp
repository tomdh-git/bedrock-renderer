// LIFT 0xe83b200 size 0x1c5 1.26.62.01 sub_e83b200
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e83b200.h"

#include <cstdint>
#include <cstring>

namespace native {
namespace d3d12 {

#if 0
0xe83b200  push r15
0xe83b202  push r14
0xe83b204  push r12
0xe83b206  push rsi
0xe83b207  push rdi
0xe83b208  push rbx
0xe83b209  sub rsp,0x38
0xe83b20d  mov rsi,rcx
0xe83b210  cmp rdx,0x1001
0xe83b217  jb 0xE83B39F
0xe83b21d  mov rax,[rsi+0x2010]
0xe83b224  shr rax,1
0xe83b227  cmp rdx,rax
0xe83b22a  jbe 0xE83B39F
0xe83b230  add rdx,rdx
0xe83b233  mov rbx,rdx
0xe83b236  mov rax,[rsi+0x2000]
0xe83b23d  add rbx,0xFFFFFFFFFFFFE000
0xe83b244  je 0xE83B381
0xe83b24a  test rax,rax
0xe83b24d  jne short 0xE83B29A
0xe83b24f  mov rcx,[0x12ADF800]
0xe83b256  mov rax,[rcx]
0xe83b259  mov rax,[rax+8]
0xe83b25d  lea rdx,[0xF7CC762]
0xe83b264  mov [rsp+0x20],rdx
0xe83b269  mov dword ptr [rsp+0x28],0
0xe83b271  mov r8d,0x18
0xe83b277  mov r9d,8
0xe83b27d  xor edx,edx
0xe83b27f  call qword ptr [0xF99FFA0]
0xe83b285  xorps xmm0,xmm0
0xe83b288  movups [rax],xmm0
0xe83b28b  mov qword ptr [rax+0x10],0
0xe83b293  mov [rsi+0x2000],rax
0xe83b29a  mov rdx,[rax+0x10]
0xe83b29e  sub rbx,rdx
0xe83b2a1  jbe 0xE83B395
0xe83b2a7  mov rcx,[rax+8]
0xe83b2ab  add rax,8
0xe83b2af  lea r14,[rcx+0x2000]
0xe83b2b6  test rcx,rcx
0xe83b2b9  cmove r14,rax
0xe83b2bd  lea r15,[0xF7CC762]
0xe83b2c4  mov r12d,0x2000
0xe83b2ca  cmp qword ptr [r14],0
0xe83b2ce  jne 0xE83B360
0xe83b2d4  nop [rax+rax]
0xe83b2e0  mov rcx,[0x12ADF800]
0xe83b2e7  mov rax,[rcx]
0xe83b2ea  mov rax,[rax+8]
0xe83b2ee  mov [rsp+0x20],r15
0xe83b2f3  mov dword ptr [rsp+0x28],0
0xe83b2fb  mov r8d,0x2008
0xe83b301  mov r9d,8
0xe83b307  xor edx,edx
0xe83b309  call qword ptr [0xF99FFA0]
0xe83b30f  mov rdi,rax
0xe83b312  mov r8d,0x2008
0xe83b318  mov rcx,rax
0xe83b31b  xor edx,edx
0xe83b31d  call 0xEEC6ED0
0xe83b322  mov [r14],rdi
0xe83b325  mov rax,[rsi+0x2000]
0xe83b32c  mov [rax+8],rdi
0xe83b330  mov rax,[rsi+0x2000]
0xe83b337  add qword ptr [rax+0x10],0x2000
0xe83b33f  mov rax,[rsi+0x2000]
0xe83b346  cmp qword ptr [rax],0
0xe83b34a  jne short 0xE83B360
0xe83b34c  mov rcx,[r14]
0xe83b34f  mov [rax],rcx
0xe83b352  nop [rax+rax]
0xe83b360  cmp rbx,0x2001
0xe83b367  jb short 0xE83B38A
0xe83b369  mov r14,[r14]
0xe83b36c  add r14,r12
0xe83b36f  add rbx,0xFFFFFFFFFFFFE000
0xe83b376  cmp qword ptr [r14],0
0xe83b37a  jne short 0xE83B360
0xe83b37c  jmp 0xE83B2E0
0xe83b381  test rax,rax
0xe83b384  jne short 0xE83B391
0xe83b386  xor edx,edx
0xe83b388  jmp short 0xE83B395
0xe83b38a  mov rax,[rsi+0x2000]
0xe83b391  mov rdx,[rax+0x10]
0xe83b395  shr rdx,1
0xe83b398  add rdx,0x1000
0xe83b39f  add rdx,rdx
0xe83b3a2  mov rax,[rsi+0x2010]
0xe83b3a9  cmp rax,rdx
0xe83b3ac  cmova rdx,rax
0xe83b3b0  mov [rsi+0x2010],rdx
0xe83b3b7  add rsp,0x38
0xe83b3bb  pop rbx
0xe83b3bc  pop rdi
0xe83b3bd  pop rsi
0xe83b3be  pop r12
0xe83b3c0  pop r14
0xe83b3c2  pop r15
0xe83b3c4  ret
#endif

static_assert(sizeof(void*) == 8, "x64");


std::uint64_t sub_e83b200(void* a0, std::uint64_t count) {
    auto* base = reinterpret_cast<unsigned char*>(a0);
    auto* hdrSlot = reinterpret_cast<std::uint64_t*>(base + 0x2000);
    auto* capSlot = reinterpret_cast<std::uint64_t*>(base + 0x2010);

    // 0xe83b210..0xe83b22a
    if (count >= 0x1001u) {
        std::uint64_t cap = *capSlot;
        if (count > (cap >> 1)) {
            // 0xe83b230..0xe83b244
            std::uint64_t bytes = count * 2u;
            std::uint64_t rbx = bytes - 0x2000u;
            std::uint64_t hdr = *hdrSlot;

            if (rbx == 0u) {
                // 0xe83b381..0xe83b388
                if (hdr == 0u) {
                    // rdx = 0
                } else {
                    // 0xe83b38a..0xe83b391
                    // rdx = hdr->used (handled below via used)
                }
            } else {
                if (hdr == 0u) {
                    // 0xe83b24f..0xe83b293
                    void* g = *reinterpret_cast<void**>(0x12ADF800u);
                    void* rax = native::d3d12::boundary::thunk_f99ffa0(g, 0u, 0x18u, 8u,
                        reinterpret_cast<const void*>(0xF7CC762u), 0u);
                    std::memset(rax, 0, 0x18);
                    *reinterpret_cast<std::uint64_t*>(static_cast<unsigned char*>(rax) + 0x10) = 0u;
                    hdr = reinterpret_cast<std::uint64_t>(rax);
                    *hdrSlot = hdr;
                }
                // 0xe83b29a..0xe83b2a1
                std::uint64_t used = *reinterpret_cast<std::uint64_t*>(hdr + 0x10);
                rbx -= used;
                if (rbx > 0u) {
                    // 0xe83b2a7..0xe83b2bd
                    std::uint64_t cur = *reinterpret_cast<std::uint64_t*>(hdr + 0x08);
                    std::uint64_t* r14p = reinterpret_cast<std::uint64_t*>(cur ? cur + 0x2000u : hdr + 0x08);
                    const void* r15 = reinterpret_cast<const void*>(0xF7CC762u);
                    std::uint32_t r12 = 0x2000u;

                    auto allocBlock = [&]() {
                        void* g2 = *reinterpret_cast<void**>(0x12ADF800u);
                        void* blk = native::d3d12::boundary::thunk_f99ffa0(g2, 0u, 0x2008u, 8u, r15, 0u);
                        native::d3d12::boundary::sub_eec6ed0(blk, 0u, 0x2008u);
                        *r14p = reinterpret_cast<std::uint64_t>(blk);
                        hdr = *hdrSlot;
                        *reinterpret_cast<std::uint64_t*>(hdr + 0x08) = reinterpret_cast<std::uint64_t>(blk);
                        *reinterpret_cast<std::uint64_t*>(hdr + 0x10) += 0x2000u;
                        hdr = *hdrSlot;
                        if (*reinterpret_cast<std::uint64_t*>(hdr + 0x00) == 0u) {
                            *reinterpret_cast<std::uint64_t*>(hdr + 0x00) = *r14p;
                        }
                    };

                    if (*r14p == 0u) allocBlock();

                    // 0xe83b360..0xe83b37c
                    while (rbx >= 0x2001u) {
                        std::uint64_t nxt = *r14p;
                        r14p = reinterpret_cast<std::uint64_t*>(nxt + r12);
                        rbx -= 0x2000u;
                        if (*r14p == 0u) allocBlock();
                    }
                }
                // reload used
                hdr = *hdrSlot;
            }

            // 0xe83b38a..0xe83b398 (used = hdr?->used or 0)
            std::uint64_t usedFinal;
            if (hdr == 0u) usedFinal = 0u;
            else usedFinal = *reinterpret_cast<std::uint64_t*>(hdr + 0x10);
            std::uint64_t rdxv = (usedFinal >> 1) + 0x1000u;
            // 0xe83b39f..0xe83b3b0
            std::uint64_t oldcap = *capSlot;
            rdxv = rdxv * 2u;
            if (oldcap > rdxv) rdxv = oldcap;
            *capSlot = rdxv;
            return oldcap;
        }
    }

    // tail
    {
        std::uint64_t oldcap = *capSlot;
        std::uint64_t rdxv = count * 2u;
        if (oldcap > rdxv) rdxv = oldcap;
        *capSlot = rdxv;
        return oldcap;
    }
}

} // namespace d3d12
} // namespace native

// LIFT_FN registration placeholder
// LIFT_FN("sub_e83b200", 0xe83b200, sub_e83b200);
