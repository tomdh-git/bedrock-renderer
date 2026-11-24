// LIFT 0xbc6ee00 size 0x122 1.26.62.01 sub_bc6ee00
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc6ee00.h"

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace native::bgfx {

// Callees sub_ebdbf10 / sub_eec6ec0 / sub_ebdbf20: forward-declared in
// sub_bc6ee00.h (namespace native); all `lift` in docs/data/native_boundary.tsv
// (X0b5), called directly like the original calls (hard rule 66).

// Layout assertions (full set in sub_bc6ee00.h; repeated here so liftcheck
// sees them next to the lifted source).
static_assert(offsetof(A0, p_0x1C0) == 0x1C0, "sub_0xbc6ee00: A0::p_0x1C0 at +0x1C0");
static_assert(offsetof(A0, r14_0x1CFD0C8) == 0x1CFD0C8, "sub_0xbc6ee00: A0::r14_0x1CFD0C8 at +0x1CFD0C8");
static_assert(offsetof(A0, w_0x1DDD308) == 0x1DDD308, "sub_0xbc6ee00: A0::w_0x1DDD308 at +0x1DDD308");
static_assert(offsetof(A0, w_0x1DE1348) == 0x1DE1348, "sub_0xbc6ee00: A0::w_0x1DE1348 at +0x1DE1348");
static_assert(offsetof(A0, w_0x1DFB48C) == 0x1DFB48C, "sub_0xbc6ee00: A0::w_0x1DFB48C at +0x1DFB48C");
static_assert(offsetof(A0, w_0x1DE534C) == 0x1DE534C, "sub_0xbc6ee00: A0::w_0x1DE534C at +0x1DE534C");
static_assert(offsetof(A0, w_0x1DFBE94) == 0x1DFBE94, "sub_0xbc6ee00: A0::w_0x1DFBE94 at +0x1DFBE94");
static_assert(offsetof(A0, w_0x1DF145C) == 0x1DF145C, "sub_0xbc6ee00: A0::w_0x1DF145C at +0x1DF145C");
static_assert(offsetof(A0, w_0x1DED458) == 0x1DED458, "sub_0xbc6ee00: A0::w_0x1DED458 at +0x1DED458");
static_assert(offsetof(A0, w_0x1DF7478) == 0x1DF7478, "sub_0xbc6ee00: A0::w_0x1DF7478 at +0x1DF7478");
static_assert(offsetof(A0, w_0x1DFB690) == 0x1DFB690, "sub_0xbc6ee00: A0::w_0x1DFB690 at +0x1DFB690");
static_assert(offsetof(A0, w_0x1DE9454) == 0x1DE9454, "sub_0xbc6ee00: A0::w_0x1DE9454 at +0x1DE9454");
static_assert(offsetof(A0, w_0x1DE9350) == 0x1DE9350, "sub_0xbc6ee00: A0::w_0x1DE9350 at +0x1DE9350");
static_assert(offsetof(A0, block_0x1EBF1D8) == 0x1EBF1D8, "sub_0xbc6ee00: A0::block_0x1EBF1D8 at +0x1EBF1D8");
static_assert(offsetof(R14, v_0xDC5808) == 0xDC5808, "sub_0xbc6ee00: R14::v_0xDC5808 at +0xDC5808");
static_assert(offsetof(R14, p_0xE60DE0) == 0xE60DE0, "sub_0xbc6ee00: R14::p_0xE60DE0 at +0xE60DE0");
static_assert(offsetof(R14, src_0xE60DE8) == 0xE60DE8, "sub_0xbc6ee00: R14::src_0xE60DE8 at +0xE60DE8");
static_assert(offsetof(A1, w_0x74) == 0x74, "sub_0xbc6ee00: A1::w_0x74 at +0x74");
static_assert(offsetof(A1, w_0x76) == 0x76, "sub_0xbc6ee00: A1::w_0x76 at +0x76");
static_assert(offsetof(A1, w_0x78) == 0x78, "sub_0xbc6ee00: A1::w_0x78 at +0x78");
static_assert(offsetof(A1, w_0x7A) == 0x7A, "sub_0xbc6ee00: A1::w_0x7A at +0x7A");
static_assert(offsetof(A1, w_0x7C) == 0x7C, "sub_0xbc6ee00: A1::w_0x7C at +0x7C");
static_assert(offsetof(A1, w_0x7E) == 0x7E, "sub_0xbc6ee00: A1::w_0x7E at +0x7E");
static_assert(offsetof(A1, w_0x80) == 0x80, "sub_0xbc6ee00: A1::w_0x80 at +0x80");
static_assert(offsetof(A1, w_0x82) == 0x82, "sub_0xbc6ee00: A1::w_0x82 at +0x82");
static_assert(offsetof(A1, w_0x84) == 0x84, "sub_0xbc6ee00: A1::w_0x84 at +0x84");
static_assert(offsetof(A1, w_0x86) == 0x86, "sub_0xbc6ee00: A1::w_0x86 at +0x86");
static_assert(offsetof(A1, w_0x88) == 0x88, "sub_0xbc6ee00: A1::w_0x88 at +0x88");
static_assert(offsetof(A1, block_0x90) == 0x90, "sub_0xbc6ee00: A1::block_0x90 at +0x90");
static_assert(offsetof(A1, shuffle_0xD0) == 0xD0, "sub_0xbc6ee00: A1::shuffle_0xD0 at +0xD0");
static_assert(offsetof(A1, d_0xD4) == 0xD4, "sub_0xbc6ee00: A1::d_0xD4 at +0xD4");

void* sub_bc6ee00(uint8_t* a0, void* a1) {
    // 0xbc6ee00..0xbc6ee16: prologue — push rbp, r14, rsi, rdi, rbx; sub rsp,0x30;
    //                       lea rbp,[rsp+0x30]; [rbp-8] = -2 (EH state slot,
    //                       never read by this function; no /GS cookie, no SEH)
    //   0xbc6ee00  push rbp
    //   0xbc6ee01  push r14
    //   0xbc6ee03  push rsi
    //   0xbc6ee04  push rdi
    //   0xbc6ee05  push rbx
    //   0xbc6ee06  sub rsp,0x30
    //   0xbc6ee0a  lea rbp,[rsp+0x30]
    //   0xbc6ee0f  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // (all frame slots dead on exit: nothing to materialize)

    // 0xbc6ee17..0xbc6ee23: rsi = rdx (= a1); rbx = rcx (= a0); rdi = rcx + 0x1C0
    //   0xbc6ee17  mov rsi,rdx
    //   0xbc6ee1a  mov rbx,rcx
    //   0xbc6ee1d  lea rdi,[rcx+0x1C0]
    void* rsi = a1;
    uint8_t* rbx = a0;
    void* rdi = reinterpret_cast<void*>(a0 + kA0_0x1C0);

    // 0xbc6ee24..0xbc6ee2b: sub_ebdbf10(a0 + 0x1C0); its return value in rax is dead
    //   0xbc6ee24  mov rcx,rdi
    //   0xbc6ee27  call 0xEBDBF10
    sub_ebdbf10(rdi);

    // 0xbc6ee2c..0xbc6ee39: r14 = *(uint8_t**)(a0 + 0x1CFD0C8);
    //                       rdx = r14 + 0xE60DE8; r8d = 0xD0
    //   0xbc6ee2c  mov r14,[rbx+0x1CFD0C8]
    //   0xbc6ee33  lea rdx,[r14+0xE60DE8]
    //   0xbc6ee3a  mov r8d,0xD0
    uint8_t* r14 = *reinterpret_cast<uint8_t**>(rbx + kA0_0x1CFD0C8);
    void* rdx = r14 + kR14_0xE60DE8;
    std::uint32_t r8d = 0xD0u;

    // 0xbc6ee40: rcx = rsi (= a1), then the sub_eec6ec0 call below
    //   0xbc6ee40  mov rcx,rsi
    //   0xbc6ee43  call 0xEEC6EC0
    sub_eec6ec0(rsi, rdx, r8d);

    // 0xbc6ee48..0xbc6ee56: xmm0 = movq [r14+0xDC5808] (8 bytes);
    //                      pshuflw xmm0,xmm0,0xE8 keeps words {w0,w2,w3,w3};
    //                      a1+0xD0 = low dword of xmm0 = {w0, w2} (4 bytes)
    //   0xbc6ee48  movq xmm0,[r14+0xDC5808]
    //   0xbc6ee51  pshuflw xmm0,xmm0,0xE8
    //   0xbc6ee56  movd [rsi+0xD0],xmm0
    std::uint16_t loaded[4];
    std::memcpy(loaded, r14 + kR14_0xDC5808, sizeof(loaded));
    std::uint16_t shuffle[2] = {loaded[0], loaded[2]};
    std::memcpy(reinterpret_cast<uint8_t*>(a1) + kA1_0xD0, shuffle, sizeof(shuffle));

    // 0xbc6ee5e..0xbc6ee68: p = *(uint8_t**)(r14 + 0xE60DE0);
    //                       a1+0xD4 = *(uint32_t*)(p + 0xC)
    //   0xbc6ee5e  mov rax,[r14+0xE60DE0]
    //   0xbc6ee65  mov eax,[rax+0xC]
    //   0xbc6ee68  mov [rsi+0xD4],eax
    uint8_t* p = *reinterpret_cast<uint8_t**>(r14 + kR14_0xE60DE0);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0xD4) =
        *reinterpret_cast<std::uint32_t*>(p + 0xC);

    // 0xbc6ee6e..0xbc6ee99: a1+0x74..0x7A = words from a0+0x1DDD308,
    //                       a0+0x1DE1348, a0+0x1DFB48C, a0+0x1DE534C (in order)
    //   0xbc6ee6e  movzx eax,word ptr [rbx+0x1DDD308]
    //   0xbc6ee75  mov [rsi+0x74],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x74) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DDD308);
    //   0xbc6ee79  movzx eax,word ptr [rbx+0x1DE1348]
    //   0xbc6ee80  mov [rsi+0x76],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x76) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DE1348);
    //   0xbc6ee84  movzx eax,word ptr [rbx+0x1DFB48C]
    //   0xbc6ee8b  mov [rsi+0x78],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x78) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DFB48C);
    //   0xbc6ee8f  movzx eax,word ptr [rbx+0x1DE534C]
    //   0xbc6ee96  mov [rsi+0x7A],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x7A) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DE534C);

    // 0xbc6ee9a..0xbc6eebd: a1+0x7C..0x82 = words from a0+0x1DFBE94,
    //                       a0+0x1DF145C, a0+0x1DED458, a0+0x1DF7478 (in order)
    //   0xbc6ee9a  movzx eax,word ptr [rbx+0x1DFBE94]
    //   0xbc6eea1  mov [rsi+0x7C],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x7C) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DFBE94);
    //   0xbc6eea5  movzx eax,word ptr [rbx+0x1DF145C]
    //   0xbc6eeac  mov [rsi+0x7E],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x7E) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DF145C);
    //   0xbc6eeb0  movzx eax,word ptr [rbx+0x1DED458]
    //   0xbc6eeb7  mov [rsi+0x80],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x80) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DED458);
    //   0xbc6eebe  movzx eax,word ptr [rbx+0x1DF7478]
    //   0xbc6eec5  mov [rsi+0x82],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x82) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DF7478);

    // 0xbc6eecc..0xbc6eef5: a1+0x84..0x88 = words from a0+0x1DFB690,
    //                       a0+0x1DE9454, a0+0x1DE9350 (in order)
    //   0xbc6eecc  movzx eax,word ptr [rbx+0x1DFB690]
    //   0xbc6eed3  mov [rsi+0x84],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x84) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DFB690);
    //   0xbc6eeda  movzx eax,word ptr [rbx+0x1DE9454]
    //   0xbc6eee1  mov [rsi+0x86],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x86) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DE9454);
    //   0xbc6eee8  movzx eax,word ptr [rbx+0x1DE9350]
    //   0xbc6eeef  mov [rsi+0x88],ax
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<uint8_t*>(a1) + kA1_0x88) =
        *reinterpret_cast<std::uint16_t*>(rbx + kA0_0x1DE9350);

    // 0xbc6eef6..0xbc6ef03: xmm0 = movdqu [a0+0x1EBF1D8] (16 bytes);
    //                      pshufd xmm0,xmm0,0x4E = {d2, d3, d0, d1};
    //                      a1+0x90 = all 16 bytes (rotate by 8 bytes)
    //   0xbc6eef6  movdqu xmm0,[rbx+0x1EBF1D8]
    //   0xbc6eefe  pshufd xmm0,xmm0,0x4E
    //   0xbc6ef03  movdqu [rsi+0x90],xmm0
    std::uint32_t block[4];
    std::memcpy(block, rbx + kA0_0x1EBF1D8, sizeof(block));
    std::uint32_t rotated[4] = {block[2], block[3], block[0], block[1]};
    std::memcpy(reinterpret_cast<uint8_t*>(a1) + kA1_0x90, rotated, sizeof(rotated));

    // 0xbc6ef0b..0xbc6ef0e: sub_ebdbf20(a0 + 0x1C0); its return value in rax
    //                       is dead because mov rax,rsi follows
    //   0xbc6ef0b  mov rcx,rdi
    //   0xbc6ef0e  call 0xEBDBF20
    sub_ebdbf20(rdi);

    // 0xbc6ef13..0xbc6ef21: nop; rax = rsi (= a1); epilogue; ret
    //   0xbc6ef13  nop
    //   0xbc6ef14  mov rax,rsi
    //   0xbc6ef17  add rsp,0x30
    //   0xbc6ef1b  pop rbx
    //   0xbc6ef1c  pop rdi
    //   0xbc6ef1d  pop rsi
    //   0xbc6ef1e  pop r14
    //   0xbc6ef20  pop rbp
    //   0xbc6ef21  ret
    return rsi;
}

LIFT_FN(sub_bc6ee00, "sub_bc6ee00", 0xbc6ee00, sub_bc6ee00, nullptr);

} // namespace native::bgfx
