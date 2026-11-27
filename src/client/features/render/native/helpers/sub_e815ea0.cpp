// LIFT 0xe815ea0 size 0x11f 1.26.62.01 sub_e815ea0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e815ea0.h"
#include "client/features/render/native/helpers/sub_e83abb0.h"
#include "client/features/render/native/bgfx/sub_bc5f110.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

LIFT_FN(sub_e815ea0, "sub_e815ea0", 0xe815ea0, sub_e815ea0, nullptr);

// High 64 bits of a * b (the exe's `mul rdx` produces rdx:rax). No __int128:
// the cppsyntax gate targets an architecture without the __int128 keyword.
namespace {
uint64_t mulhi_u64(uint64_t a, uint64_t b) noexcept {
    const uint64_t a_lo = static_cast<uint64_t>(static_cast<uint32_t>(a));
    const uint64_t a_hi = a >> 32;
    const uint64_t b_lo = static_cast<uint64_t>(static_cast<uint32_t>(b));
    const uint64_t b_hi = b >> 32;
    const uint64_t p0 = a_lo * b_lo;
    const uint64_t p1 = a_lo * b_hi;
    const uint64_t p2 = a_hi * b_lo;
    const uint64_t p3 = a_hi * b_hi;
    const uint64_t p12 = p1 + p2;
    const uint64_t carry_p12 = (p12 < p1) ? 1ULL : 0ULL;
    const uint64_t sum_lo = p0 + (p12 << 32);
    const uint64_t carry_lo = (sum_lo < p0) ? 1ULL : 0ULL;
    return p3 + (p12 >> 32) + carry_p12 + carry_lo;
}
} // namespace

static_assert(offsetof(sub_e815ea0_rcx, fbde178) == 0xbde178, "sub_0xe815ea0 rcx+0xbde178 field");
static_assert(offsetof(sub_e815ea0_rcx, fc96178) == 0xc96178, "sub_0xe815ea0 rcx+0xc96178 field");
static_assert(offsetof(sub_e815ea0_rcx, fc96190) == 0xc96190, "sub_0xe815ea0 rcx+0xc96190 field");
static_assert(sizeof(sub_e815ea0_rcx) >= 0xc96191, "sub_0xe815ea0 rcx sizeof lower bound");

static_assert(offsetof(sub_e815ea0_r8, f0) == 0x0, "sub_0xe815ea0 r8+0x0 field");
static_assert(offsetof(sub_e815ea0_r8, fb8000) == 0xb8000, "sub_0xe815ea0 r8+0xb8000 field");
static_assert(sizeof(sub_e815ea0_r8) >= 0xb8008, "sub_0xe815ea0 r8 sizeof lower bound");

static_assert(offsetof(sub_e815ea0_rax, f0) == 0x0, "sub_0xe815ea0 rax+0x0 field");
static_assert(sizeof(sub_e815ea0_rax) >= 0x8, "sub_0xe815ea0 rax sizeof lower bound");

static_assert(offsetof(sub_e815ea0_rsi, fb8000) == 0xb8000, "sub_0xe815ea0 rsi+0xb8000 field");
static_assert(sizeof(sub_e815ea0_rsi) >= 0xb8008, "sub_0xe815ea0 rsi sizeof lower bound");

uintptr_t sub_e80f290(void* pointer);

// Verbatim call instructions from the disassembly of [0xe815ea0, 0xe815fbf) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xe815eba  call 0xE83ABB0
0xe815ed9  call 0xBC5F110
#endif

// Tail-call target of the final `jmp 0xE80F290` at 0xe815fba: a native symbol
// of the exe outside this lift set. RCX receives the pointer computed by this
// lift; the return value of sub_e80f290 is forwarded to this function's caller.
uintptr_t sub_e80f290(void* pointer);

uintptr_t sub_e815ea0(void* self, std::uint16_t index, std::uintptr_t r8_in, std::uintptr_t r9_in) {
    // 0xe815ea0..0xe815ec7: basic block 0
    // 0xe815ea0  push rsi
    // 0xe815ea1  push rdi
    // 0xe815ea2  push rbx
    // 0xe815ea3  sub rsp,0x20
    // 0xe815ea7  mov rdi,rcx
    // 0xe815eaa  lea rsi,[rcx+0xBDE178]                        ; R a0+0xBDE178
    // 0xe815eb1  movzx ebx,dx
    // 0xe815eb4  mov rcx,rsi
    // 0xe815eb7  mov rdx,rbx
    // 0xe815eba  call 0xE83ABB0                                ; -> sub_e83abb0
    // 0xe815ebf  cmp ebx,0x1000
    // 0xe815ec5  jb short 0xE815EE7                            ; -> loc_e815ee7
    // -> if u32(u32(u16(a1))) <u 0x1000 goto L_0xe815ee7
    // -> if u32(u32(u16(a1))) >=u 0x1000 goto L_0xe815ec7
    uintptr_t rdi = reinterpret_cast<uintptr_t>(self);
    uint8_t* rsi = reinterpret_cast<uint8_t*>(self) + 0xBDE178;
    uint64_t rbx = static_cast<uint64_t>(index);
    uint64_t r8 = 0;
    uintptr_t rax = 0;
    uintptr_t rcx = 0;
    uintptr_t rdx = 0;
    uint32_t eax = 0;
    sub_e83abb0(reinterpret_cast<void*>(rsi), rbx);
    if (rbx < 0x1000ULL) goto L_0xe815ee7;

    // 0xe815ec7..0xe815ed0: basic block 1
    // 0xe815ec7  cmp byte ptr [rdi+0xC96190],0                 ; R a0+0xC96190
    // 0xe815ece  je short 0xE815EE7                            ; -> loc_e815ee7
    // -> if *u8(a0+0xC96190) == 0x0 goto L_0xe815ee7
    // -> if *u8(a0+0xC96190) != 0x0 goto L_0xe815ed0
    if (reinterpret_cast<uint8_t*>(rdi)[0xC96190] == 0) goto L_0xe815ee7;

    // 0xe815ed0..0xe815ee7: basic block 2
    // 0xe815ed0  lea rdx,[0xF7F68E3]                           ; [data_f7f68e3] "FAILED: accessing a guarded paged heap backed array out of bounds."
    // 0xe815ed7  xor ecx,ecx
    // 0xe815ed9  call 0xBC5F110                                ; -> sub_bc5f110
    // 0xe815ede  imul r8,rbx,0xB8
    // 0xe815ee5  jmp short 0xE815EFA                           ; -> loc_e815efa
    // -> if jmp goto L_0xe815efa
    native::bgfx::sub_bc5f110(0, "FAILED: accessing a guarded paged heap backed array out of bounds.", r8_in, r9_in);
    r8 = rbx * 0xB8ULL;
    goto L_0xe815efa;

L_0xe815ee7:
    // 0xe815ee7..0xe815efa: basic block 3
    // 0xe815ee7  imul r8,rbx,0xB8
    // 0xe815eee  cmp ebx,0xFFF
    // 0xe815ef4  jbe 0xE815FAD                                 ; -> loc_e815fad
    // -> if u32(u32(u16(a1))) <=u 0xFFF goto L_0xe815fad
    // -> if u32(u32(u16(a1))) >u 0xFFF goto L_0xe815efa
    r8 = rbx * 0xB8ULL;
    if (rbx <= 0xFFFULL) goto L_0xe815fad;
    goto L_0xe815efa;

L_0xe815efa:
    // 0xe815efa..0xe815f18: basic block 4
    // 0xe815efa  lea rsi,[r8-0xB8000]
    // 0xe815f01  mov rax,[rdi+0xC96178]
    // 0xe815f08  mov rcx,[rax]
    // 0xe815f0b  cmp rsi,0xB8000
    // 0xe815f12  jb 0xE815FA8                                  ; -> loc_e815fa8
    // -> if (u32(u16(a1)) * 0xB8)-0xB8000 <u 0xB8000 goto L_0xe815fa8
    // -> if (u32(u16(a1)) * 0xB8)-0xB8000 >=u 0xB8000 goto L_0xe815f18
    rsi = reinterpret_cast<uint8_t*>(r8 - 0xB8000ULL);
    rax = *reinterpret_cast<uintptr_t*>(rdi + 0xC96178);
    rcx = *reinterpret_cast<uintptr_t*>(rax);
    if (reinterpret_cast<uintptr_t>(rsi) < 0xB8000ULL) goto L_0xe815fa8;
    goto L_0xe815f18;

L_0xe815f18:
    // 0xe815f18..0xe815f3b: basic block 5
    // 0xe815f18  add r8,0xFFFFFFFFFFE90000
    // 0xe815f1f  mov rax,r8
    // 0xe815f22  shr rax,0xF
    // 0xe815f26  mov rdx,0xB21642C8590B217
    // 0xe815f30  mul rdx
    // 0xe815f33  mov eax,edx
    // 0xe815f35  not eax
    // 0xe815f37  test al,7
    // 0xe815f39  je short 0xE815F53                            ; -> loc_e815f53
    // -> if (? & 0x7) == 0 goto L_0xe815f53
    // -> if (? & 0x7) != 0 goto L_0xe815f3b
    r8 += 0xFFFFFFFFFFE90000ULL;
    rax = r8;
    rax >>= 0xF;
    rdx = 0xB21642C8590B217ULL;
    rdx = mulhi_u64(rax, rdx);
    eax = static_cast<uint32_t>(rdx) ^ 0xFFFFFFFFu;
    if ((eax & 7u) == 0u) goto L_0xe815f53;
    goto L_0xe815f3b;

L_0xe815f3b:
    // 0xe815f3b..0xe815f40: basic block 6
    // 0xe815f3b  inc edx
    // 0xe815f3d  and edx,7
    // -> if fallthrough goto L_0xe815f40
    // 32-bit inc/and on the low half of rdx; the upper 32 bits of rdx are preserved.
    rdx = (rdx & ~0xFFFFFFFFULL) | static_cast<uint64_t>((static_cast<uint32_t>(rdx) + 1u) & 7u);
    goto L_0xe815f40;

L_0xe815f40:
    // 0xe815f40..0xe815f53: basic block 7
    // 0xe815f40  add rsi,0xFFFFFFFFFFF48000
    // 0xe815f47  mov rcx,[rcx+0xB8000]
    // 0xe815f4e  dec rdx
    // 0xe815f51  jne short 0xE815F40                           ; -> loc_e815f40
    // -> if (Dec rdx) != 0 goto L_0xe815f40
    // -> if (Dec rdx) == 0 goto L_0xe815f53
    rsi = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rsi) - 0xB8000ULL);
    rcx = *reinterpret_cast<uintptr_t*>(rcx + 0xB8000);
    if (--rdx != 0ULL) goto L_0xe815f40;
    goto L_0xe815f53;

L_0xe815f53:
    // 0xe815f53..0xe815f5c: basic block 8
    // 0xe815f53  cmp r8d,0x508000
    // 0xe815f5a  jb short 0xE815FA8                            ; -> loc_e815fa8
    // -> if u32((u32(u16(a1)) * 0xB8)-0x170000) <u 0x508000 goto L_0xe815fa8
    // -> if u32((u32(u16(a1)) * 0xB8)-0x170000) >=u 0x508000 goto L_0xe815f5c
    if (static_cast<uint32_t>(r8) < 0x508000ULL) goto L_0xe815fa8;
    goto L_0xe815f60;

    // 0xe815f5c..0xe815f60: basic block 9
    // 0xe815f5c  nop [rax]
    // -> if fallthrough goto L_0xe815f60

L_0xe815f60:
    // 0xe815f60..0xe815fa8: basic block 10
    // 0xe815f60  mov rax,[rcx+0xB8000]
    // 0xe815f67  mov rax,[rax+0xB8000]
    // 0xe815f6e  mov rax,[rax+0xB8000]
    // 0xe815f75  mov rax,[rax+0xB8000]
    // 0xe815f7c  mov rax,[rax+0xB8000]
    // 0xe815f83  mov rax,[rax+0xB8000]
    // 0xe815f8a  mov rax,[rax+0xB8000]
    // 0xe815f91  add rsi,0xFFFFFFFFFFA40000
    // 0xe815f98  mov rcx,[rax+0xB8000]
    // 0xe815f9f  cmp rsi,0xB7FFF
    // 0xe815fa6  ja short 0xE815F60                            ; -> loc_e815f60
    // -> if ? >u 0xB7FFF goto L_0xe815f60
    // -> if ? <=u 0xB7FFF goto L_0xe815fa8
    rax = *reinterpret_cast<uintptr_t*>(rcx + 0xB8000);
    rax = *reinterpret_cast<uintptr_t*>(rax + 0xB8000);
    rax = *reinterpret_cast<uintptr_t*>(rax + 0xB8000);
    rax = *reinterpret_cast<uintptr_t*>(rax + 0xB8000);
    rax = *reinterpret_cast<uintptr_t*>(rax + 0xB8000);
    rax = *reinterpret_cast<uintptr_t*>(rax + 0xB8000);
    rax = *reinterpret_cast<uintptr_t*>(rax + 0xB8000);
    rsi = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rsi) - 0x5C0000ULL);
    rcx = *reinterpret_cast<uintptr_t*>(rax + 0xB8000);
    if (reinterpret_cast<uintptr_t>(rsi) > 0xB7FFFULL) goto L_0xe815f60;
    goto L_0xe815fa8;

L_0xe815fa8:
    // 0xe815fa8..0xe815fad: basic block 11
    // 0xe815fa8  add rsi,rcx
    // 0xe815fab  jmp short 0xE815FB0                           ; -> loc_e815fb0
    // -> if jmp goto L_0xe815fb0
    rsi = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rsi) + rcx);
    goto L_0xe815fb0;

L_0xe815fad:
    // 0xe815fad..0xe815fb0: basic block 12
    // 0xe815fad  add rsi,r8
    // -> if fallthrough goto L_0xe815fb0
    rsi = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rsi) + r8);
    goto L_0xe815fb0;

L_0xe815fb0:
    // 0xe815fb0..0xe815fbf: basic block 13
    // 0xe815fb0  mov rcx,rsi
    // 0xe815fb3  add rsp,0x20
    // 0xe815fb7  pop rbx
    // 0xe815fb8  pop rdi
    // 0xe815fb9  pop rsi
    // 0xe815fba  jmp 0xE80F290                                 ; -> sub_e80f290
    // -> (fall-through / ret / end)
    return sub_e80f290(reinterpret_cast<void*>(rsi));
}

} // namespace native::helpers
