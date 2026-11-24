// LIFT 0xbc55fb0 size 0x1b8 1.26.62.01 sub_bc55fb0
#include "client/features/render/native/bgfx/sub_bc55fb0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

// Layout assertions for FrameGraphOutput are in sub_bc55fb0.h (static_assert for all offsets and sizeof)

namespace native {

// Bit-exact model of xorps between two floats: bit-copy both operands, XOR the bit patterns,
// reinterpret as float. Matches `xorps xmm12,xmm10`, `xorps xmm5,xmm10` where xmm10 holds the
// 16-byte mask loaded at 0xEF3F050 (only lane 0 of each stored result is observable).
static inline float xorps_bits(float a, float b) {
    std::uint32_t ua = 0, ub = 0, ur;
    std::memcpy(&ua, &a, sizeof(ua));
    std::memcpy(&ub, &b, sizeof(ub));
    ur = ua ^ ub;
    float r = 0.0f;
    std::memcpy(&r, &ur, sizeof(r));
    return r;
}

// x64 Microsoft ABI: rcx = out, rdx = qptr1, r8 = qptr2, r9 = a3;
// stack arguments (in order): arg5 (float), arg6 (float), arg7 (uint64_t), arg8 (uint8_t), arg9 (uint64_t), arg10 (uint64_t).
// Returns void* (the out pointer).
// 0xbc55fb0..0xbc55fc3: prologue
// push rbp; push rsi; sub rsp,0x78; lea rbp,[rsp+0x70]
// mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
// mov rsi,r9                  // save a3 to rsi
// 0xbc55fc6..0xbc55fce: load stack args
// mov rax,[rbp+0x50]          // arg7
// mov r11,[rbp+0x60]          // arg9
// mov r9,[rbp+0x68]           // arg10
extern "C" void* sub_bc55fb0(
    FrameGraphOutput* out,
    const void* qptr1,
    const void* qptr2,
    const float* a3,
    float arg5,
    float arg6,
    std::uint64_t arg7,
    std::uint8_t arg8,
    std::uint64_t arg9,
    std::uint64_t arg10
) {
    // 0xbc55fd2..0xbc560b0: initialize output struct
    // xorps xmm0,xmm0
    const __m128 zero = _mm_setzero_ps();

    // 0xbc55fd5  movups [rcx+0x108],xmm0   // +0x108..0x117 = 0
    // 0xbc55fdc  movups [rcx+0xF8],xmm0    // +0xF8..0x107 = 0
    // 0xbc55fe3  movups [rcx+0xE8],xmm0    // +0xE8..0xF7 = 0
    // 0xbc55fea  movups [rcx+0xD8],xmm0    // +0xD8..0xE7 = 0
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x108/4, zero);
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0xF8/4, zero);
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0xE8/4, zero);
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0xD8/4, zero);

    // 0xbc55ff1  mov qword ptr [rcx],-1    // +0x000 = -1
    out->f00 = static_cast<std::uint64_t>(-1);

    // 0xbc55ff8  movups [rcx+8],xmm0       // +0x008..0x017 = 0
    // 0xbc55ffc  mov dword ptr [rcx+0x18],0x3F800000  // +0x18 = 1.0f
    // 0xbc56003  movups [rcx+0x1C],xmm0    // +0x1C..0x2B = 0
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x08/4, zero);
    out->f18 = 1.0f;
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x1C/4, zero);

    // 0xbc56007  mov dword ptr [rcx+0x2C],0x3F800000  // +0x2C = 1.0f
    // 0xbc5600e  movups [rcx+0x30],xmm0    // +0x30..0x3F = 0
    // 0xbc56012  mov dword ptr [rcx+0x40],0x3F800000  // +0x40 = 1.0f
    // 0xbc56019  movups [rcx+0x44],xmm0    // +0x44..0x53 = 0
    out->f2c = 1.0f;
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x30/4, zero);
    out->f40 = 1.0f;
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x44/4, zero);

    // 0xbc5601d  movsd xmm1,[0xEFD3400]
    // 0xbc56025  movsd [rcx+0x54],xmm1     // +0x54 = double from [0xEFD3400]
    // 0xbc5602a  movups [rcx+0x5C],xmm0    // +0x5C..0x6B = 0
    out->f54 = *reinterpret_cast<const double*>(kDataEFD3400);
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x5C/4, zero);

    // 0xbc5602e  mov dword ptr [rcx+0x6C],0x3F800000  // +0x6C = 1.0f
    // 0xbc56035  movups [rcx+0x70],xmm0    // +0x70..0x7F = 0
    // 0xbc56039  mov dword ptr [rcx+0x80],0x3F800000  // +0x80 = 1.0f
    // 0xbc56043  movups [rcx+0x84],xmm0    // +0x84..0x93 = 0
    out->f6c = 1.0f;
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x70/4, zero);
    out->f80 = 1.0f;
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x84/4, zero);

    // 0xbc5604a  mov dword ptr [rcx+0x94],0x3F800000  // +0x94 = 1.0f
    // 0xbc56054  movups [rcx+0x98],xmm0    // +0x98..0xA7 = 0
    // 0xbc5605b  mov dword ptr [rcx+0xA8],0  // +0xA8 = 0
    out->f94 = 1.0f;
    _mm_storeu_ps(reinterpret_cast<float*>(out) + 0x98/4, zero);
    out->fa8 = 0;

    // 0xbc56065  movsd xmm0,[0xEFD32D0]
    // 0xbc5606d  movups [rcx+0xAC],xmm0    // +0xAC..0xBB = double from [0xEFD32D0]
    // 0xbc56074  movsd xmm0,[0xEFD32F0]
    // 0xbc5607c  movups [rcx+0xBC],xmm0    // +0xBC..0xCB = double from [0xEFD32F0]
    // 0xbc56083  movsd xmm0,[0xF0EC830]
    // 0xbc5608b  movsd [rcx+0xCC],xmm0     // +0xCC = double from [0xF0EC830]
    out->fac = *reinterpret_cast<const double*>(kDataEFD32D0);
    out->fbc = *reinterpret_cast<const double*>(kDataEFD32F0);
    out->fcc = *reinterpret_cast<const double*>(kDataF0EC830);

    // 0xbc56093  mov dword ptr [rcx+0xD4],0x3F800000  // +0xD4 = 1.0f
    // 0xbc5609d  mov word ptr [rcx+0xD8],7  // +0xD8 = 7 (word)
    // 0xbc560a6  mov r10,0x3F800000FFFFFFFF
    // 0xbc560b0  mov [rcx+0xDC],r10        // +0xDC = 0x3F800000FFFFFFFF
    out->fd4 = 1.0f;
    out->fd8 = 7;
    out->fdc = 0x3F800000FFFFFFFFull;

    // 0xbc560b7..0xbc560ce: setup locals
    // mov qword ptr [rbp-0x28],0
    // mov dword ptr [rbp-0x20],0xBF800000  // -1.0f
    // mov qword ptr [rbp-0x18],0
    // mov dword ptr [rbp-0x10],0
    float local_b = 0.0f;               // rbp-0x28
    float local_b_dummy = -1.0f;        // rbp-0x20 (padding, not directly used as float in call)
    std::uint64_t local_a3 = 0;         // rbp-0x18
    std::uint32_t local_zero = 0;       // rbp-0x10

    // 0xbc560d5..0xbc56101: prepare and call sub_bc56190
    // mov [rsp+0x40],r9          // stack arg9 = arg10
    // mov [rsp+0x38],r11         // stack arg8 = arg9
    // mov [rsp+0x30],rax         // stack arg7 = arg7
    // lea rax,[0xF4412A0]
    // mov [rsp+0x28],rax         // stack arg6 = 0xF4412A0
    // lea rax,[rbp-0x28]
    // mov [rsp+0x20],rax         // stack arg5 = &local1 (rbp-0x28)
    // lea r9,[rbp-0x18]          // r9 = &local2 (rbp-0x18)
    // mov [rbp-8],rcx            // save out
    // call 0xBC56190             // sub_bc56190(out, qptr1, qptr2, &local2, &local1, 0xF4412A0, arg7, arg9, arg10)
    Q9 q9{arg9, static_cast<std::uint32_t>(arg10)};

    // 0xbc56101  call 0xBC56190
    sub_bc56190(out, qptr1, qptr2, &local_b, &local_b, &local_a3,
                reinterpret_cast<const float*>(kDataF4412A0), nullptr, &q9);

    // 0xbc56106  nop
    // 0xbc56107..0xbc56157: prepare and call sub_ebcd900
    // movss xmm0,[rbp+0x48]      // xmm0 = arg6
    // movss xmm4,[rbp+0x40]      // xmm4 = arg5
    // mov rax,[rbp-8]            // rax = out
    // lea rcx,[rax+0x18]         // rcx = out+0x18
    // movss xmm1,[rsi]           // xmm1 = a3[0]
    // movss xmm5,[rsi+4]         // xmm5 = a3[1]
    // movss xmm3,[rsi+0xC]       // xmm3 = a3[3]
    // addss xmm3,xmm5            // xmm3 = a3[3]+a3[1]
    // movss xmm2,[rsi+8]         // xmm2 = a3[2]
    // addss xmm2,xmm1            // xmm2 = a3[2]+a3[0]
    // cmp byte ptr [rbp+0x58],0  // test arg8 flag
    // sete [rsp+0x40]            // [rsp+0x40] = (arg8 == 0)
    // movss [rsp+0x30],xmm0      // stack arg = arg6
    // movss [rsp+0x28],xmm4      // stack arg = arg5
    // movss [rsp+0x20],xmm5      // stack arg = a3[1]
    // mov dword [rsp+0x38],0     // stack arg = 0
    // call 0xEBCD900             // sub_ebcd900(out+0x18, a3, xmm2, xmm3, xmm0, xmm1, xmm4, xmm5, a3[1], arg5, arg6, 0, flag)

    const float a3_0 = a3[0];
    const float a3_1 = a3[1];
    const float a3_2 = a3[2];
    const float a3_3 = a3[3];
    const float xmm2 = a3_2 + a3_0;  // a3[2]+a3[0]
    const float xmm3 = a3_3 + a3_1;  // a3[3]+a3[1]
    const std::uint8_t flag = (arg8 == 0) ? 1 : 0;  // sete logic inverted

    // 0xbc56157  call 0xEBCD900
    // 0xbc5615c  nop
    boundary_ebcd900_fn ebcd900_fn = reinterpret_cast<boundary_ebcd900_fn>(
        SigManager::get("sub_ebcd900")
    );
    ebcd900_fn(
        reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(out) + 0x18),
        a3,
        xmm2,
        xmm3,
        arg6,
        a3_0,
        arg5,
        a3_1,
        a3_1,
        arg5,
        arg6,
        0,
        flag
    );

    // 0xbc5615d..0xbc56167: epilogue
    // mov rax,[rbp-8]            // rax = out
    // add rsp,0x78
    // pop rsi
    // pop rbp
    // ret
    return out;
}

static native::Footprint sub_bc55fb0Footprint(FrameGraphOutput* out, const void*, const void*,
    const float*, float, float, std::uint64_t, std::uint8_t, std::uint64_t, std::uint64_t) {
    return {{out, sizeof(FrameGraphOutput)}};
}

// Verbatim log of every call instruction in [0xbc55fb0, 0xbc56168) (rdis dis output,
// two spaces after each address):
#if 0
0xbc56101  call 0xBC56190        ; -> sub_bc56190 (lift-set callee)
0xbc56157  call 0xEBCD900        ; -> sub_ebcd900 (boundary, class crt)
#endif
// UNRESOLVED CALL = none: sub_bc56190 is lifted, sub_ebcd900 is boundary (crt).

LIFT_FN(sub_bc55fb0, "native::sub_bc55fb0", 0xbc55fb0, sub_bc55fb0, sub_bc55fb0Footprint);

} // namespace native