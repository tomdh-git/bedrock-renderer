// LIFT 0xbcc1910 size 0x119 1.26.62.01 RenderStateDesc -> bgfx state bits
#include "client/features/render/native/bgfx/sub_bcc1910.h"

#include <cstdint>

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e86d770.h"

namespace native::bgfx {

static_assert(sizeof(void*) == 8, "x64");

extern "C" void* sub_bcc1910(void* a0, void* a1)
{
    // 0xbcc1910..0xbcc1917  prologue
    void* rsi = a0;
    void* rdi = a1;

    // 0xbcc1918..0xbcc192b  init output +0x18/+0x30
    //   0xbcc191e  mov rax,0x100000000000000
    //   0xbcc1928  mov [rcx+0x18],rax
    //   0xbcc192c  mov qword ptr [rcx+0x30],0
    *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x18) = 0x100000000000000ULL;
    *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x30) = 0ULL;

    // 0xbcc1934..0xbcc194a  table lookup from a1+0
    //   0xbcc1934  mov eax,[rdx]
    //   0xbcc1936  dec eax
    //   0xbcc1938  cmp eax,0xA
    //   0xbcc193b  ja short 0xBCC194C
    //   0xbcc193d  mov eax,eax
    //   0xbcc193f  lea rcx,[0xF44BEE0]
    //   0xbcc1946  mov rax,[rcx+rax*8]
    //   0xbcc194a  jmp short 0xBCC194E
    // 0xbcc194c  xor eax,eax
    {
        uint32_t v = *reinterpret_cast<uint32_t*>(static_cast<char*>(rdi));
        uint64_t rax;
        if (v - 1u <= 0xAu) {
            rax = *reinterpret_cast<uint64_t*>(0xF44BEE0 + (v - 1u) * 8);
        } else {
            rax = 0;
        }
        *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x00) = rax;
    }

    // 0xbcc1951..0xbcc1971  blend flags from a1+8
    //   0xbcc1951  mov eax,[rdi+8]
    //   0xbcc1954  xor ecx,ecx
    //   0xbcc1956  cmp eax,1
    //   0xbcc1959  sete cl
    //   0xbcc195c  shl rcx,0x24
    //   0xbcc1960  cmp eax,2
    //   0xbcc1963  mov rax,0x2000000000
    //   0xbcc196d  cmovne rax,rcx
    //   0xbcc1971  mov [rsi+8],rax
    {
        uint32_t eax = *reinterpret_cast<uint32_t*>(static_cast<char*>(rdi) + 0x8);
        uint64_t rcx = (eax == 1) ? (1ULL << 0x24) : 0ULL;
        uint64_t rax = (eax == 2) ? 0x2000000000ULL : rcx;
        *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x8) = rax;
    }

    // 0xbcc1975..0xbcc1997  cull mode table from a1+0xC/+0xE
    //   0xbcc1975  cmp byte ptr [rdi+0xC],1
    //   ...
    {
        uint64_t rax;
        if (*reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0xC) == 1) {
            unsigned char al = *reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0xE);
            al--;
            if (al <= 7) {
                rax = *reinterpret_cast<uint64_t*>(0xF44BF38 + al * 8);
            } else {
                rax = 0;
            }
        } else {
            rax = 0;
        }
        *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x10) = rax;
    }

    // 0xbcc199b..0xbcc19b6  primitive type table from a1+0x10
    {
        uint32_t eax = *reinterpret_cast<uint32_t*>(static_cast<char*>(rdi) + 0x10);
        uint64_t rax;
        eax--;
        if (eax <= 2u) {
            rax = *reinterpret_cast<uint64_t*>(0xF44BF78 + eax * 8);
        } else {
            rax = 0;
        }
        *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x20) = rax;
    }

    // 0xbcc19ba..0xbcc19cc  write mask bits
    //   0xbcc19ba  movzx eax,byte ptr [rdi+0xD]
    //   0xbcc19be  movzx ecx,byte ptr [rdi+4]
    //   0xbcc19c2  and ecx,0xF
    //   0xbcc19c5  shl rax,0x26
    //   0xbcc19c9  or rax,rcx
    //   0xbcc19cc  mov [rsi+0x28],rax
    {
        uint64_t rax = (*reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0xD));
        rax <<= 0x26;
        uint64_t rcx = *reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0x4) & 0xF;
        *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x28) = rax | rcx;
    }

    // 0xbcc19d0..0xbcc19fd  stencil (conditional)
    //   0xbcc19d0  cmp byte ptr [rdi+0x54],1
    //   0xbcc19d4  jne short 0xBCC1A00
    //   0xbcc19d6  movzx ebx,byte ptr [rdi+0x55]
    //   0xbcc19da  movzx ebp,byte ptr [rdi+0x56]
    //   0xbcc19de  lea rcx,[rdi+0x34]
    //   0xbcc19e2  mov edx,ebx
    //   0xbcc19e4  mov r8d,ebp
    //   0xbcc19e7  call 0xE86D770
    //   0xbcc19ec  mov [rsi+0x34],eax
    //   0xbcc19ef  lea rcx,[rdi+0x44]
    //   0xbcc19f3  mov edx,ebx
    //   0xbcc19f5  mov r8d,ebp
    //   0xbcc19f8  call 0xE86D770
    //   0xbcc19fd  mov [rsi+0x30],eax
    if (*reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0x54) == 1) {
        unsigned char ebx = *reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0x55);
        unsigned char ebp = *reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0x56);
        uint32_t r = native::d3d12::sub_e86d770(
            static_cast<char*>(rdi) + 0x34, ebx, ebp);
        *reinterpret_cast<uint32_t*>(static_cast<char*>(rsi) + 0x34) = r;
        uint32_t r2 = native::d3d12::sub_e86d770(
            static_cast<char*>(rdi) + 0x44, ebx, ebp);
        *reinterpret_cast<uint32_t*>(static_cast<char*>(rsi) + 0x30) = r2;
    }

    // 0xbcc1a00..0xbcc1a1a  trailing copies
    //   0xbcc1a00  movzx eax,byte ptr [rdi+0x14]
    //   0xbcc1a04  mov [rsi+0x38],al
    //   0xbcc1a07  movups xmm0,[rdi+0x18]
    //   0xbcc1a0b  movups [rsi+0x3C],xmm0
    //   0xbcc1a0f  mov rax,[rdi+0x28]
    //   0xbcc1a13  mov [rsi+0x4C],rax
    //   0xbcc1a17  mov eax,[rdi+0x30]
    //   0xbcc1a1a  mov [rsi+0x54],eax
    *reinterpret_cast<unsigned char*>(static_cast<char*>(rsi) + 0x38) =
        *reinterpret_cast<unsigned char*>(static_cast<char*>(rdi) + 0x14);
    // movups 16 bytes
    for (int i = 0; i < 16; i++)
        static_cast<char*>(rsi)[0x3C + i] = static_cast<char*>(rdi)[0x18 + i];
    *reinterpret_cast<uint64_t*>(static_cast<char*>(rsi) + 0x4C) =
        *reinterpret_cast<uint64_t*>(static_cast<char*>(rdi) + 0x28);
    *reinterpret_cast<uint32_t*>(static_cast<char*>(rsi) + 0x54) =
        *reinterpret_cast<uint32_t*>(static_cast<char*>(rdi) + 0x30);

    // 0xbcc1a1d..0xbcc1a28  epilogue
    //   0xbcc1a1d  mov rax,rsi
    //   0xbcc1a20  add rsp,0x28
    //   0xbcc1a24  pop rbx
    //   0xbcc1a25  pop rbp
    //   0xbcc1a26  pop rdi
    //   0xbcc1a27  pop rsi
    //   0xbcc1a28  ret
    return rsi;
}

LIFT_FN(sub_bcc1910, "RenderStateDesc -> bgfx state bits", 0xbcc1910, sub_bcc1910, nullptr);

} // namespace native::bgfx
