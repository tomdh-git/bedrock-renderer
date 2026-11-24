// LIFT 0xe83ace0 size 0x1e8 1.26.62.01 sub_e83ace0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e83ace0.h"

#include <cstdint>
#include <cstddef>
#include <cstring>

namespace native::d3d12 {

static_assert(sizeof(void*) == 8, "x64");

#if 0
0xe83ace0  push r15
0xe83ace2  push r14
0xe83ace4  push r13
0xe83ace6  push r12
0xe83ace8  push rsi
0xe83ace9  push rdi
0xe83acea  push rbx
0xe83aceb  sub rsp,0x30
0xe83acef  mov r8,rdx
0xe83acf2  mov rsi,rcx
0xe83acf5  cmp rdx,0x1001
0xe83acfc  jb 0xE83AE9C
0xe83ad02  mov rax,[rsi+0xB8010]
0xe83ad09  shr rax,3
0xe83ad0d  mov rbx,0x1642C8590B21642D
0xe83ad17  mul rbx
0xe83ad1a  shr rdx,1
0xe83ad1d  cmp r8,rdx
0xe83ad20  jbe 0xE83AE9C
0xe83ad26  imul r14,r8,0xB8
0xe83ad2d  mov rax,[rsi+0xB8000]
0xe83ad34  add r14,0xFFFFFFFFFFF48000
0xe83ad3b  je 0xE83AE71
0xe83ad41  test rax,rax
0xe83ad44  jne short 0xE83AD91
0xe83ad46  mov rcx,[0x12ADF800]
0xe83ad4d  mov rax,[rcx]
0xe83ad50  mov rax,[rax+8]
0xe83ad54  lea rdx,[0xF7CC762]
0xe83ad5b  mov [rsp+0x20],rdx
0xe83ad60  mov dword ptr [rsp+0x28],0
0xe83ad68  mov r8d,0x18
0xe83ad6e  mov r9d,8
0xe83ad74  xor edx,edx
0xe83ad76  call qword ptr [0xF99FFA0]
0xe83ad7c  xorps xmm0,xmm0
0xe83ad7f  movups [rax],xmm0
0xe83ad82  mov qword ptr [rax+0x10],0
0xe83ad8a  mov [rsi+0xB8000],rax
0xe83ad91  mov rcx,[rax+0x10]
0xe83ad95  sub r14,rcx
0xe83ad98  jbe 0xE83AE85
0xe83ad9e  mov rcx,[rax+8]
0xe83ada2  add rax,8
0xe83ada6  lea r15,[rcx+0xB8000]
0xe83adad  test rcx,rcx
0xe83adb0  cmove r15,rax
0xe83adb4  lea r12,[0xF7CC762]
0xe83adbb  mov r13d,0xB8000
0xe83adc1  cmp qword ptr [r15],0
0xe83adc5  jne 0xE83AE50
0xe83adcb  nop [rax+rax]
0xe83add0  mov rcx,[0x12ADF800]
0xe83add7  mov rax,[rcx]
0xe83adda  mov rax,[rax+8]
0xe83adde  mov [rsp+0x20],r12
0xe83ade3  mov dword ptr [rsp+0x28],0
0xe83adeb  mov r8d,0xB8008
0xe83adf1  mov r9d,8
0xe83adf7  xor edx,edx
0xe83adf9  call qword ptr [0xF99FFA0]
0xe83adff  mov rdi,rax
0xe83ae02  mov r8d,0xB8008
0xe83ae08  mov rcx,rax
0xe83ae0b  xor edx,edx
0xe83ae0d  call 0xEEC6ED0
0xe83ae12  mov [r15],rdi
0xe83ae15  mov rax,[rsi+0xB8000]
0xe83ae1c  mov [rax+8],rdi
0xe83ae20  mov rax,[rsi+0xB8000]
0xe83ae27  add qword ptr [rax+0x10],0xB8000
0xe83ae2f  mov rax,[rsi+0xB8000]
0xe83ae36  cmp qword ptr [rax],0
0xe83ae3a  jne short 0xE83AE50
0xe83ae3c  mov rcx,[r15]
0xe83ae3f  mov [rax],rcx
0xe83ae42  nop [rax+rax]
0xe83ae50  cmp r14,0xB8001
0xe83ae57  jb short 0xE83AE7A
0xe83ae59  mov r15,[r15]
0xe83ae5c  add r15,r13
0xe83ae5f  add r14,0xFFFFFFFFFFF48000
0xe83ae66  cmp qword ptr [r15],0
0xe83ae6a  jne short 0xE83AE50
0xe83ae6c  jmp 0xE83ADD0
0xe83ae71  test rax,rax
0xe83ae74  jne short 0xE83AE81
0xe83ae76  xor ecx,ecx
0xe83ae78  jmp short 0xE83AE85
0xe83ae7a  mov rax,[rsi+0xB8000]
0xe83ae81  mov rcx,[rax+0x10]
0xe83ae85  shr rcx,3
0xe83ae89  mov rax,rcx
0xe83ae8c  mul rbx
0xe83ae8f  mov r8,rdx
0xe83ae92  shr r8,1
0xe83ae95  add r8,0x1000
0xe83ae9c  imul rax,r8,0xB8
0xe83aea3  mov rcx,[rsi+0xB8010]
0xe83aeaa  cmp rcx,rax
0xe83aead  cmova rax,rcx
0xe83aeb1  mov [rsi+0xB8010],rax
0xe83aeb8  add rsp,0x30
0xe83aebc  pop rbx
0xe83aebd  pop rdi
0xe83aebe  pop rsi
0xe83aebf  pop r12
0xe83aec1  pop r13
0xe83aec3  pop r14
0xe83aec5  pop r15
0xe83aec7  ret
#endif

std::size_t sub_e83ace0(void* a0, std::size_t a1) {
    unsigned char* rsi = reinterpret_cast<unsigned char*>(a0);
    std::size_t r8 = a1;

    if (r8 < 0x1001) goto L_end;

    {
        std::uint64_t rax = *reinterpret_cast<std::uint64_t*>(rsi + 0xB8010);
        rax >>= 3;
        unsigned __int128 prod = (unsigned __int128)rax * 0x1642C8590B21642DULL;
        std::uint64_t rdx = (std::uint64_t)(prod >> 64);
        rdx >>= 1;
        if (r8 <= rdx) goto L_end;
    }

    std::uintptr_t r14 = r8 * 0xB8;
    void* raxp = *reinterpret_cast<void**>(rsi + 0xB8000);
    r14 += 0xFFFFFFFFFFF48000ULL;
    if (r14 == 0) goto L_ae71;

    if (raxp == nullptr) {
        void* g = *reinterpret_cast<void**>(0x12ADF800ULL);
        using AllocFn = void* (*)(void*, std::uint64_t, std::uint32_t, std::uint32_t, const char*, std::uint32_t);
        AllocFn alloc = *reinterpret_cast<AllocFn*>(0xF99FFA0ULL);
        void* block = alloc(g, 0, 0x18, 8, "NOFILE", 0);
        std::memset(block, 0, 0x18);
        *reinterpret_cast<void**>(rsi + 0xB8000) = block;
        raxp = block;
    }

    // L_ad91
    {
        std::uint64_t rcx_used = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<unsigned char*>(raxp) + 0x10);
        r14 -= rcx_used;
        if (r14 <= rcx_used) goto L_ae85_from_ad91;
        void* rcurrent = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(raxp) + 0x8);
        void* rax8 = reinterpret_cast<unsigned char*>(raxp) + 0x8;
        void* r15 = rcurrent ? (unsigned char*)rcurrent + 0xB8000 : rax8;
        const char* r12 = "NOFILE";
        std::uintptr_t r13 = 0xB8000;
        if (*reinterpret_cast<void**>(r15) != nullptr) goto L_ae50;

    L_add0:
        {
            void* g = *reinterpret_cast<void**>(0x12ADF800ULL);
            using AllocFn = void* (*)(void*, std::uint64_t, std::uint32_t, std::uint32_t, const char*, std::uint32_t);
            AllocFn alloc = *reinterpret_cast<AllocFn*>(0xF99FFA0ULL);
            void* rdi = alloc(g, 0, 0xB8008, 8, r12, 0);
            std::memset(rdi, 0, 0xB8008);
            *reinterpret_cast<void**>(r15) = rdi;
            void* ctrl = *reinterpret_cast<void**>(rsi + 0xB8000);
            *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(ctrl) + 0x8) = rdi;
            *reinterpret_cast<std::uint64_t*>(reinterpret_cast<unsigned char*>(ctrl) + 0x10) += 0xB8000;
            void* ctrl2 = *reinterpret_cast<void**>(rsi + 0xB8000);
            if (*reinterpret_cast<void**>(ctrl2) == nullptr) {
                void* rcx2 = *reinterpret_cast<void**>(r15);
                *reinterpret_cast<void**>(ctrl2) = rcx2;
            }
        }

    L_ae50:
        if (r14 < 0xB8001) goto L_ae7a;
        r15 = *reinterpret_cast<void**>(r15);
        r15 = (unsigned char*)r15 + r13;
        r14 -= 0xB8000;
        if (*reinterpret_cast<void**>(r15) == nullptr) goto L_add0;
        goto L_ae50;
    }

L_ae7a:
    raxp = *reinterpret_cast<void**>(rsi + 0xB8000);
    // fall through to ae81

L_ae81:
    {
        std::uint64_t rcx = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<unsigned char*>(raxp) + 0x10);
        rcx >>= 3;
        unsigned __int128 prod = (unsigned __int128)rcx * 0x1642C8590B21642DULL;
        std::uint64_t rdx = (std::uint64_t)(prod >> 64);
        r8 = (rdx >> 1) + 0x1000;
        goto L_end;
    }

L_ae85_from_ad91:
    // rcx_used is ctrl->used; r8 stays? need r8 for L_end compute from used
    {
        std::uint64_t rcx = rcx_used;
        rcx >>= 3;
        unsigned __int128 prod = (unsigned __int128)rcx * 0x1642C8590B21642DULL;
        std::uint64_t rdx = (std::uint64_t)(prod >> 64);
        r8 = (rdx >> 1) + 0x1000;
        goto L_end;
    }

L_ae71:
    if (raxp != nullptr) goto L_ae81_ae71;
    {
        std::uint64_t rcx = 0;
        rcx >>= 3;
        unsigned __int128 prod = (unsigned __int128)rcx * 0x1642C8590B21642DULL;
        std::uint64_t rdx = (std::uint64_t)(prod >> 64);
        r8 = (rdx >> 1) + 0x1000;
        goto L_end;
    }
L_ae81_ae71:
    {
        std::uint64_t rcx = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<unsigned char*>(raxp) + 0x10);
        rcx >>= 3;
        unsigned __int128 prod = (unsigned __int128)rcx * 0x1642C8590B21642DULL;
        std::uint64_t rdx = (std::uint64_t)(prod >> 64);
        r8 = (rdx >> 1) + 0x1000;
        goto L_end;
    }

L_end:
    {
        std::uint64_t raxv = r8 * 0xB8;
        std::uint64_t rcx = *reinterpret_cast<std::uint64_t*>(rsi + 0xB8010);
        if (rcx > raxv) raxv = rcx;
        *reinterpret_cast<std::uint64_t*>(rsi + 0xB8010) = raxv;
        return raxv;
    }
}

} // namespace native::d3d12

// LIFT_FN("sub_e83ace0", 0xe83ace0, sub_e83ace0);
