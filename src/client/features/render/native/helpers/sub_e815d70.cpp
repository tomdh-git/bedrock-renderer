// LIFT 0xe815d70 size 0x12b 1.26.62.01 sub_e815d70
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e815d70.h"
#include "client/features/render/native/helpers/sub_e83abb0.h"
#include "client/features/render/native/bgfx/sub_bc5f110.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

LIFT_FN(sub_e815d70, "sub_e815d70", 0xe815d70, sub_e815d70, nullptr);

// Verbatim call instructions from the disassembly of [0xe815d70, 0xe815e9b)
// (rdis `fn` output). Plain lines, two spaces after the address: parseable by
// tools/sigs/verify_oc.py. Preprocessor-excluded below so the skeleton stays
// valid C++.
#if 0
0xe815d91  call 0xE83ABB0
0xe815db0  call 0xBC5F110
#endif

// High half (bits 64..127) of a 64x64->128 unsigned multiply, used to reproduce
// the `mul rdx; mov eax,edx` magic-division sequence exactly.
static inline std::uint64_t mulhi_u64(std::uint64_t a, std::uint64_t b) {
    std::uint64_t a_lo = a & 0xFFFFFFFFull, a_hi = a >> 32;
    std::uint64_t b_lo = b & 0xFFFFFFFFull, b_hi = b >> 32;
    std::uint64_t p0 = a_lo * b_lo;
    std::uint64_t p1 = a_lo * b_hi;
    std::uint64_t p2 = a_hi * b_lo;
    std::uint64_t p3 = a_hi * b_hi;
    std::uint64_t mid = p1 + p2;
    std::uint64_t carry = (mid < p1) ? 1ull : 0ull;
    std::uint64_t low = p0 + (mid << 32);
    if (low < p0) carry += 1ull;
    std::uint64_t high = p3 + (mid >> 32) + carry;
    return high;
}

uintptr_t sub_e815d70(void* self, std::uint16_t index) {
    std::uintptr_t rdi = 0;
    std::uintptr_t rsi = 0;
    std::uintptr_t rbx = 0;
    std::uintptr_t r8 = 0;
    std::uintptr_t rax = 0;
    std::uintptr_t rcx = 0;
    std::uintptr_t rdx2 = 0;
    std::uintptr_t rax2 = 0;
    std::uintptr_t high64 = 0;
    std::uint32_t eax = 0;

    // 0xe815d70..0xe815d9e: basic block 0
    // 0xe815d70  push rsi
    // 0xe815d71  push rdi
    // 0xe815d72  push rbx
    // 0xe815d73  sub rsp,0x20
    // 0xe815d77  mov rdi,rcx
    // 0xe815d7a  mov byte ptr [0x12AE1750],1
    // 0xe815d81  lea rsi,[rcx+0xBDE178]
    // 0xe815d88  movzx ebx,dx
    // 0xe815d8b  mov rcx,rsi
    // 0xe815d8e  mov rdx,rbx
    // 0xe815d91  call 0xE83ABB0
    // 0xe815d96  cmp ebx,0x1000
    // 0xe815d9c  jb short 0xE815DBE
    rdi = reinterpret_cast<std::uintptr_t>(self);
    *reinterpret_cast<std::uint8_t*>(0x12AE1750) = 1u;
    rsi = rdi + 0xBDE178;
    rbx = static_cast<std::uintptr_t>(index);
    (void)sub_e83abb0(reinterpret_cast<void*>(rsi), rbx);
    if (rbx < 0x1000ull) goto L_0xe815dbe;
    goto L_0xe815d9e;

    // 0xe815d9e..0xe815da7: basic block 1
    // 0xe815d9e  cmp byte ptr [rdi+0xC96190],0
    // 0xe815da5  je short 0xE815DBE
L_0xe815d9e:
    if (*reinterpret_cast<std::uint8_t*>(rdi + 0xC96190) == 0u) goto L_0xe815dbe;
    goto L_0xe815da7;

    // 0xe815da7..0xe815dbe: basic block 2
    // 0xe815da7  lea rdx,[0xF7F68E3]
    // 0xe815dae  xor ecx,ecx
    // 0xe815db0  call 0xBC5F110
    // 0xe815db5  imul r8,rbx,0xB8
    // 0xe815dbc  jmp short 0xE815DD1
L_0xe815da7:
    native::bgfx::sub_bc5f110(0, reinterpret_cast<const char*>(0xF7F68E3), 0, 0);
    r8 = rbx * 0xB8ull;
    goto L_0xe815dd1;

    // 0xe815dbe..0xe815dd1: basic block 3
    // 0xe815dbe  imul r8,rbx,0xB8
    // 0xe815dc5  cmp ebx,0xFFF
    // 0xe815dcb  jbe 0xE815E8D
L_0xe815dbe:
    r8 = rbx * 0xB8ull;
    if (rbx <= 0xFFFull) goto L_0xe815e8d;
    goto L_0xe815dd1;

    // 0xe815dd1..0xe815def: basic block 4
    // 0xe815dd1  lea rsi,[r8-0xB8000]
    // 0xe815dd8  mov rax,[rdi+0xC96178]
    // 0xe815ddf  mov rcx,[rax]
    // 0xe815de2  cmp rsi,0xB8000
    // 0xe815de9  jb 0xE815E88
L_0xe815dd1:
    rsi = r8 - 0xB8000ull;
    rax = reinterpret_cast<std::uintptr_t>(
        reinterpret_cast<sub_e815d70_ctx*>(rdi)->fC96178);
    rcx = *reinterpret_cast<std::uintptr_t*>(rax);
    if (rsi < 0xB8000ull) goto L_0xe815e88;
    goto L_0xe815def;

    // 0xe815def..0xe815e12: basic block 5
    // 0xe815def  add r8,0xFFFFFFFFFFE90000
    // 0xe815df6  mov rax,r8
    // 0xe815df9  shr rax,0xF
    // 0xe815dfd  mov rdx,0xB21642C8590B217
    // 0xe815e07  mul rdx
    // 0xe815e0a  mov eax,edx
    // 0xe815e0c  not eax
    // 0xe815e0e  test al,7
    // 0xe815e10  je short 0xE815E33
L_0xe815def:
    r8 += 0xFFFFFFFFFFE90000ull;
    rax2 = r8;
    rax2 >>= 0xF;
    high64 = mulhi_u64(rax2, 0xB21642C8590B217ull);
    rdx2 = high64 & 0xFFFFFFFFull;
    eax = static_cast<std::uint32_t>(high64);
    eax = ~eax;
    if ((eax & 7u) == 0u) goto L_0xe815e33;
    goto L_0xe815e12;

    // 0xe815e12..0xe815e20: basic block 6
    // 0xe815e12  inc edx
    // 0xe815e14  and edx,7
    // 0xe815e17  nop [rax+rax]
L_0xe815e12:
    rdx2 = (rdx2 + 1ull) & 7ull;
    goto L_0xe815e20;

    // 0xe815e20..0xe815e33: basic block 7
    // 0xe815e20  add rsi,0xFFFFFFFFFFF48000
    // 0xe815e27  mov rcx,[rcx+0xB8000]
    // 0xe815e2e  dec rdx
    // 0xe815e31  jne short 0xE815E20
L_0xe815e20:
    rsi += 0xFFFFFFFFFFF48000ull;
    rcx = *reinterpret_cast<std::uintptr_t*>(rcx + 0xB8000ull);
    rdx2 -= 1ull;
    if (rdx2 != 0ull) goto L_0xe815e20;
    goto L_0xe815e33;

    // 0xe815e33..0xe815e3c: basic block 8
    // 0xe815e33  cmp r8d,0x508000
    // 0xe815e3a  jb short 0xE815E88
L_0xe815e33:
    if (static_cast<std::uint32_t>(r8) < 0x508000ull) goto L_0xe815e88;
    goto L_0xe815e40;

    // 0xe815e3c..0xe815e40: basic block 9
    // 0xe815e3c  nop [rax]
L_0xe815e3c:
    goto L_0xe815e40;

    // 0xe815e40..0xe815e88: basic block 10
    // 0xe815e40  mov rax,[rcx+0xB8000]
    // 0xe815e47  mov rax,[rax+0xB8000]
    // 0xe815e4e  mov rax,[rax+0xB8000]
    // 0xe815e55  mov rax,[rax+0xB8000]
    // 0xe815e5c  mov rax,[rax+0xB8000]
    // 0xe815e63  mov rax,[rax+0xB8000]
    // 0xe815e6a  mov rax,[rax+0xB8000]
    // 0xe815e71  add rsi,0xFFFFFFFFFFA40000
    // 0xe815e78  mov rcx,[rax+0xB8000]
    // 0xe815e7f  cmp rsi,0xB7FFF
    // 0xe815e86  ja short 0xE815E40
L_0xe815e40:
    rax = *reinterpret_cast<std::uintptr_t*>(rcx + 0xB8000ull);
    rax = *reinterpret_cast<std::uintptr_t*>(rax + 0xB8000ull);
    rax = *reinterpret_cast<std::uintptr_t*>(rax + 0xB8000ull);
    rax = *reinterpret_cast<std::uintptr_t*>(rax + 0xB8000ull);
    rax = *reinterpret_cast<std::uintptr_t*>(rax + 0xB8000ull);
    rax = *reinterpret_cast<std::uintptr_t*>(rax + 0xB8000ull);
    rax = *reinterpret_cast<std::uintptr_t*>(rax + 0xB8000ull);
    rsi += 0xFFFFFFFFFFA40000ull;
    rcx = *reinterpret_cast<std::uintptr_t*>(rax + 0xB8000ull);
    if (rsi > 0xB7FFFull) goto L_0xe815e40;
    goto L_0xe815e88;

    // 0xe815e88..0xe815e8d: basic block 11
    // 0xe815e88  add rsi,rcx
    // 0xe815e8b  jmp short 0xE815E90
L_0xe815e88:
    rsi += rcx;
    goto L_0xe815e90;

    // 0xe815e8d..0xe815e90: basic block 12
    // 0xe815e8d  add rsi,r8
L_0xe815e8d:
    rsi += r8;
    goto L_0xe815e90;

    // 0xe815e90..0xe815e9b: basic block 13
    // 0xe815e90  mov rax,[rsi]
    // 0xe815e93  add rsp,0x20
    // 0xe815e97  pop rbx
    // 0xe815e98  pop rdi
    // 0xe815e99  pop rsi
    // 0xe815e9a  ret
L_0xe815e90:
    rax = *reinterpret_cast<std::uintptr_t*>(rsi);
    return rax;
}

// Layout assertions for every struct field read or written by the lift.
static_assert(offsetof(sub_e815d70_ctx, fBDE178) == 0xBDE178, "sub_e815d70 ctx fBDE178 offset");
static_assert(offsetof(sub_e815d70_ctx, fC96178) == 0xC96178, "sub_e815d70 ctx fC96178 offset");
static_assert(offsetof(sub_e815d70_ctx, fC96190) == 0xC96190, "sub_e815d70 ctx fC96190 offset");
static_assert(sizeof(sub_e815d70_ctx) >= 0xC96191, "sub_e815d70 ctx sizeof lower bound");
static_assert(offsetof(sub_e815d70_heap, f0) == 0x00, "sub_e815d70 heap f0 offset");
static_assert(sizeof(sub_e815d70_heap) >= 0x08, "sub_e815d70 heap sizeof lower bound");
static_assert(offsetof(sub_e815d70_page, fB8000) == 0xB8000, "sub_e815d70 page fB8000 offset");
static_assert(sizeof(sub_e815d70_page) >= 0xB8008, "sub_e815d70 page sizeof lower bound");

} // namespace native::helpers
