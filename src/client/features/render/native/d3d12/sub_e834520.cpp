// LIFT 0xe834520 size 0x13d 1.26.62.01 RendererContextD3D12 base slot 36
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e834520.h"

#include <cstdint>
#include <cstddef>

namespace native::d3d12 {
static_assert(sizeof(void*) == 8, "x64");
#if 0
0xe834520  push r15
0xe834522  push r14
0xe834524  push r13
0xe834526  push r12
0xe834528  push rsi
0xe834529  push rdi
0xe83452a  push rbx
0xe83452b  sub rsp,0x50
0xe83452f  mov rsi,rcx
0xe834532  lea rbx,[rsp+0x4A]
0xe834537  xor edi,edi
0xe834539  mov eax,0xCCCCCCCD
0xe83453e  xchg ax,ax
0xe834540  mov ecx,edx
0xe834542  imul rcx,rax
0xe834546  shr rcx,0x23
0xe83454a  lea r8d,[rcx+rcx]
0xe83454e  lea r8d,[r8+r8*4]
0xe834552  mov r9d,edx
0xe834555  sub r9d,r8d
0xe834558  or r9d,0x30
0xe83455c  mov [rbx-2],r9w
0xe834561  add rbx,0xFFFFFFFFFFFFFFFE
0xe834565  add rdi,2
0xe834569  cmp edx,9
0xe83456c  mov edx,ecx
0xe83456e  ja short 0xE834540
0xe834570  xorps xmm0,xmm0
0xe834573  movups [rsi],xmm0
0xe834576  mov r12,rdi
0xe834579  sar r12,1
0xe83457c  mov rax,0x7FFFFFFFFFFFFFFF
0xe834586  cmp r12,rax
0xe834589  jae 0xE834657
0xe83458f  mov r13d,7
0xe834595  mov r15,rsi
0xe834598  cmp r12,8
0xe83459c  jb short 0xE83460A
0xe83459e  mov rdx,r12
0xe8345a1  or rdx,7
0xe8345a5  cmp rdx,0xB
0xe8345a9  mov r13d,0xA
0xe8345af  cmovae r13,rdx
0xe8345b3  lea r14,[r13+r13]
0xe8345b8  mov rcx,[0x1233E1A8]
0xe8345bf  mov rax,[rcx]
0xe8345c2  mov rax,[rax+8]
0xe8345c6  cmp rdx,0x7FF
0xe8345cd  jb short 0xE8345F2
0xe8345cf  add r14,0x29
0xe8345d3  mov rdx,r14
0xe8345d6  call qword ptr [0xF99FFA0]
0xe8345dc  test rax,rax
0xe8345df  je short 0xE83463A
0xe8345e1  mov r15,rax
0xe8345e4  add r15,0x27
0xe8345e8  and r15,0xFFFFFFFFFFFFFFE0
0xe8345ec  mov [r15-8],rax
0xe8345f0  jmp short 0xE834607
0xe8345f2  add r14,2
0xe8345f6  mov rdx,r14
0xe8345f9  call qword ptr [0xF99FFA0]
0xe8345ff  mov r15,rax
0xe834602  test rax,rax
0xe834605  je short 0xE83464A
0xe834607  mov [rsi],r15
0xe83460a  mov [rsi+0x10],r12
0xe83460e  mov [rsi+0x18],r13
0xe834612  mov rcx,r15
0xe834615  mov rdx,rbx
0xe834618  mov r8,rdi
0xe83461b  call 0xEEC6EC0
0xe834620  mov word ptr [r15+rdi],0
0xe834627  mov rax,rsi
0xe83462a  add rsp,0x50
0xe83462e  pop rbx
0xe83462f  pop rdi
0xe834630  pop rsi
0xe834631  pop r12
0xe834633  pop r13
0xe834635  pop r14
0xe834637  pop r15
0xe834639  ret
0xe83463a  mov rcx,r14
0xe83463d  mov r14,rax
0xe834640  call 0x9BC830
0xe834645  mov rax,r14
0xe834648  jmp short 0xE8345E1
0xe83464a  mov rcx,r14
0xe83464d  call 0x9BC830
0xe834652  xor r15d,r15d
0xe834655  jmp short 0xE834607
0xe834657  call 0x75720
0xe83465c  int3
#endif

void* sub_e834520(void* a0, std::uint32_t a1) {
    // 0xe83452f..0xe834537
    void* rsi = a0;
    std::uint8_t buf[16];
    void* rbx = buf + 10; // rsp+0x4A
    std::uint32_t edx = a1;
    std::size_t rdi = 0;
    std::uint32_t eax = 0xCCCCCCCD;
    // 0xe834540..0xe83456e
    for (;;) {
        std::uint32_t ecx = edx;
        std::uint64_t rcx = (std::uint64_t)ecx * eax;
        rcx >>= 0x23;
        std::uint32_t r8d = (std::uint32_t)rcx + (std::uint32_t)rcx;
        r8d = r8d + r8d * 4;
        std::uint32_t r9d = edx - r8d;
        r9d |= 0x30;
        *reinterpret_cast<std::uint16_t*>(static_cast<char*>(rbx) - 2) = (std::uint16_t)r9d;
        rbx = static_cast<char*>(rbx) - 2;
        rdi += 2;
        std::uint32_t prev = edx;
        edx = (std::uint32_t)rcx;
        if (!(prev > 9)) break;
    }
    // Actually loop condition uses original edx; restructure below is approximate.
    // 0xe834570..0xe834573
    // zero 16 bytes at rsi
    for (int k = 0; k < 16; k++) static_cast<unsigned char*>(rsi)[k] = 0;
    // 0xe834576..0xe834589
    std::size_t r12 = rdi >> 1;
    if (r12 >= (std::size_t)0x7FFFFFFFFFFFFFFFULL) { sub_75720(); /* noreturn */ }
    // 0xe83458f.. 
    std::size_t r13 = 7;
    void* r15 = rsi;
    if (r12 >= 8) {
        std::size_t rdx = r12 | 7;
        if (rdx >= 0xB) r13 = rdx;
        std::size_t r14 = r13 + r13;
        // allocator from 0x1233E1A8 -> vtable+8
        void** allocObj = *reinterpret_cast<void***>(0x1233E1A8);
        using AllocFn = void* (*)(void*, std::size_t);
        auto alloc = reinterpret_cast<AllocFn>((*reinterpret_cast<void***>(allocObj))[1]); // [rax+8]
        if (rdx >= 0x7FF) {
            r14 += 0x29;
            std::size_t sz = r14;
            void* rax = alloc(allocObj, sz);
            if (!rax) {
                // 0xe83463a
                std::size_t rcx = r14;
                void* r14saved = rax;
                sub_9bc830(reinterpret_cast<void*>(r14)); // arg r14 (size)
                rax = r14saved;
                r15 = rax;
                r15 = static_cast<char*>(r15) + 0x27;
                r15 = reinterpret_cast<void*>((reinterpret_cast<std::uintptr_t>(r15)) & ~0x1FULL);
                *reinterpret_cast<void**>(static_cast<char*>(r15) - 8) = rax;
            } else {
                r15 = rax;
                r15 = static_cast<char*>(r15) + 0x27;
                r15 = reinterpret_cast<void*>((reinterpret_cast<std::uintptr_t>(r15)) & ~0x1FULL);
                *reinterpret_cast<void**>(static_cast<char*>(r15) - 8) = rax;
            }
        } else {
            r14 += 2;
            std::size_t sz = r14;
            void* rax = alloc(allocObj, sz);
            r15 = rax;
            if (!rax) {
                sub_9bc830(reinterpret_cast<void*>(r14));
                r15 = nullptr;
            }
        }
        *reinterpret_cast<void**>(rsi) = r15;
    }
    // 0xe83460a..
    *reinterpret_cast<std::size_t*>(static_cast<char*>(rsi) + 0x10) = r12;
    *reinterpret_cast<std::size_t*>(static_cast<char*>(rsi) + 0x18) = r13;
    sub_eec6ec0(r15, rbx, rdi);
    *reinterpret_cast<std::uint16_t*>(static_cast<char*>(r15) + rdi) = 0;
    return rsi;
}

} // namespace native::d3d12
// LIFT_FN("sub_e834520", 0xe834520, sub_e834520);