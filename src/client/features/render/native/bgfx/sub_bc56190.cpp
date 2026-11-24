// LIFT 0xbc56190 size 0x477 1.26.62.01 sub_bc56190
#include "client/features/render/native/bgfx/sub_bc56190.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

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

// x64 Microsoft ABI: rcx = out, rdx = qptr1, r8 = qptr2, r9 = a3; stack arguments
// (in order): b, a, m16, flagptr, q9. Returns void.
// 0xbc56190..0xbc561d0: prologue (push rsi/rdi, sub rsp,0xB8, save xmm6-xmm13) - no visible side effect.
extern "C" void sub_bc56190(FrameOutput* out, const void* qptr1, const void* qptr2,
    const float* a3, const float* b, const float* a, const float* m16,
    const void* flagptr, const Q9* q9)
{
    // 0xbc561d3..0xbc56266: copy the three input vectors into the output record.
    out->f98 = a3[0];                                     // 0xbc561fe  movss [rsi+0x98],xmm2
    out->f9c = a3[1];                                     // 0xbc5620c  movss [rsi+0x9C],xmm2
    out->fa0 = a3[2];                                     // 0xbc5621a  movss [rsi+0xA0],xmm2
    out->fa4 = b[0];                                      // 0xbc56226  movss [rsi+0xA4],xmm2
    out->fa8 = b[1];                                      // 0xbc56233  movss [rsi+0xA8],xmm2
    out->fac = b[2];                                      // 0xbc56240  movss [rsi+0xAC],xmm2
    out->fbc = a[0];                                      // 0xbc5624c  movss [rsi+0xBC],xmm4
    out->fc0 = a[1];                                      // 0xbc56259  movss [rsi+0xC0],xmm2
    out->fc4 = a[2];                                      // 0xbc56266  movss [rsi+0xC4],xmm3

    // 0xbc5626e..0xbc562ef: len1 = sqrt(d0*d0 + e0*e0 + d1*d1), inv1 = *0xEEC8060 / len1
    const float d0 = b[0] - a3[0];                        // 0xbc561fa  subss xmm1,xmm2
    const float e0 = b[1] - a3[1];                        // 0xbc561f7  subps xmm0,xmm3 (low dword)
    const float d1 = b[2] - a3[2];                        // 0xbc56326  subps xmm1,xmm4 (low dword)
    const float len1s = d0 * d0 + e0 * e0;                // 0xbc5627c-0xbc5628b (mulps/mulss/addss)
    const float num = *reinterpret_cast<const float*>(native::kRecipNumeratorAddr);  // 0xbc56296  movss xmm0,[0xEEC8060]
    const float len1 = sqrtf(d1 * d1 + len1s);            // 0xbc56287-0xbc56292 (shufps/addss/sqrtss)
    const float inv1 = num / len1;                        // 0xbc562a1  divss xmm7,xmm6
    const float t2 = num / len1;                          // 0xbc56354-0xbc5635c (divss/shufps; same value as inv1)
    const float v1 = d0 * inv1;                           // 0xbc562b2-0xbc562b6 (shufps-broadcast of lane 1)

    out->fc8 = d0 * inv1;                                 // 0xbc562b6  movss [rsi+0xC8],xmm7
    out->fcc = e0 * inv1;                                 // 0xbc562be  movlps [rsi+0xCC],xmm5 (lo dword)
    out->fcd = d1 * inv1;                                 // 0xbc562be  movlps [rsi+0xCC],xmm5 (hi dword)
    out->fb8 = d0 * inv1 * a[1] - e0 * inv1 * a[0];       // 0xbc562c5-0xbc562d6
    out->fb0 = a[2] * e0 * inv1 - a[1] * d1 * inv1;       // 0xbc562cf-0xbc562dd (lo dword of the movlps pair)
    out->fb4 = a[0] * d1 * inv1 - a[2] * d0 * inv1;       // 0xbc562cf-0xbc562dd (hi dword)
    out->fd4 = len1;                                      // 0xbc562ef  movss [rsi+0xD4],xmm6

    // 0xbc562f7..0xbc563c9: second pass - A = inv1*(a[0]*d1 - a[2]), B = inv1*(a[1]*d0 - a[0]),
    // C = inv1*(a[2] - a[1]*d1), len3 = sqrt(C*C + A*A + B*B), t3 = *0xEEC8060 / len3
    const float A = inv1 * (a[0] * d1 - a[2]);            // 0xbc5636a-0xbc56379 (lane 0 of the subps pair)
    const float B = inv1 * (a[1] * d0 - a[0]);            // 0xbc5636a-0xbc56379 (lane 1)
    const float C = inv1 * (a[2] - a[1] * d1);            // 0xbc56384-0xbc56391
    const float len3 = sqrtf(C * C + A * A + B * B);      // 0xbc56399-0xbc563bc ((C*C + A*A) + B*B)
    const float t3 = num / len3;                          // 0xbc563c1  divss xmm0,xmm6

    // 0xbc563c9..0xbc564de: store pass-2 results (xorps mask lane 0 loaded at 0xEF3F050)
    const float mask0 = *reinterpret_cast<const float*>(native::kSignMaskAddr);  // 0xbc56424  movaps xmm10,[0xEF3F050]

    out->f58 = t3 * C;                                    // 0xbc5642c  movss [rsi+0x58],xmm0
    out->f5c = (d1 * inv1 * A * t3) - (t2 * t3 * B);     // 0xbc56408-0xbc5641f
    out->f60 = xorps_bits(v1, mask0);                     // 0xbc56431-0xbc5643f
    out->f64 = 0u;                                        // 0xbc56449  mov dword ptr [rsi+0x64],0
    out->f68 = A * t3;                                    // 0xbc56450  movss [rsi+0x68],xmm7
    out->f6c = (v1 * t3 * B) - (d1 * inv1 * t3 * C);      // 0xbc5643f-0xbc56455
    out->f70 = xorps_bits(t2, mask0);                     // 0xbc56445-0xbc5645b
    out->f74 = 0u;                                        // 0xbc56460  mov dword ptr [rsi+0x74],0
    out->f78 = B * t3;                                    // 0xbc56467  movss [rsi+0x78],xmm13
    out->f7c = (t2 * t3 * C) - (v1 * A * t3);             // 0xbc563e5-0xbc56477
    out->f80 = xorps_bits(d1 * inv1, mask0);              // 0xbc564b1  xorps xmm5,xmm10
    out->f84 = 0u;                                        // 0xbc564cd  mov dword ptr [rsi+0x84],0
    out->f88 = xorps_bits(e0 * A * t3 + t3 * C * d0 + t3 * a[2], mask0);  // 0xbc564aa-0xbc564b5
    out->f8c = xorps_bits(d0 * (d1 * inv1 * A * t3 - t2 * t3 * B)
        + e0 * (v1 * t3 * B - d1 * inv1 * t3 * C)
        + t3 * a[2], mask0);                              // 0xbc564ad-0xbc564b5
    out->f90 = v1 * d0 + t2 * e0 + d1 * inv1 * a[2];      // 0xbc564bd-0xbc564e6
    out->f94 = 0x3F800000u;                               // 0xbc564ee  mov dword ptr [rsi+0x94],0x3F800000

    // 0xbc564de..0xbc56509: pointer stores and the 16-byte copy of arg7 (m16)
    out->f08 = *reinterpret_cast<const std::uintptr_t*>(qptr1);   // 0xbc564fb  mov [rsi+8],rcx
    out->f10 = *reinterpret_cast<const std::uintptr_t*>(qptr2);   // 0xbc56502  mov [rsi+0x10],rcx
    std::memcpy(out->fd8, m16, 16);                               // 0xbc56509  movups [rsi+0xD8],xmm0

    // 0xbc56510..0xbc5652a: flag dispatch; *(uint8*)(flagptr+0x18)==1 -> boundary call, skip the f_100 reset.
    if (*reinterpret_cast<const std::uint8_t*>(
            reinterpret_cast<const std::uint8_t*>(flagptr) + 0x18) == 1u) {
        // 0xbc56525  call 0x3BAFDC0   ; boundary (stl) sub_3bafdc0; rcx=&out->f_e8, rdx=flagptr, r8=qptr2, r9=a3
        Boundary<void, void*, void*, void*, void*>{"sub_3bafdc0"}(
            &out->f_e8, flagptr, qptr2, reinterpret_cast<const void*>(a3));
        goto done;                                              // 0xbc5652a  jmp short 0xBC56591
    }

    // 0xbc5652c..0xbc5658a: out->f_100 == 1 path (heap-block span check)
    if (out->f_100 == 1u) {                                     // 0xbc5652c  cmp byte ptr [rsi+0x100],1 ; jne -> epilogue
        const std::uintptr_t rax = reinterpret_cast<std::uintptr_t>(out->f_e8);  // 0xbc56535  mov rax,[rcx]
        if (rax != 0u) {                                        // 0xbc56538  test rax,rax ; je -> reset f_100 only
            const std::uintptr_t diff =
                reinterpret_cast<std::uintptr_t>(out->f_f8) - rax;  // 0xbc5653d  mov rdx,[rsi+0xF8] ; 0xbc56544  sub rdx,rax
            if (diff >= 0x1000u) {                              // 0xbc56547  cmp rdx,0x1000 ; jb -> below-0x1000 path
                const std::uintptr_t blockSize =
                    *reinterpret_cast<const std::uintptr_t*>(rax - 8);  // 0xbc56550  mov r8,[rax-8] (heap block size)
                const std::uintptr_t blockStart = rax - 8 - blockSize;  // 0xbc56554-0xbc56558
                if (blockStart >= 0x20u) {                      // 0xbc5655b  cmp rax,0x20 ; jae -> fail path
                    // 0xbc56600  call qword ptr [0xF9A8C78]   ; import slot, then 0xbc56606 int3
                    using fail_fn = void(__cdecl*)(std::uintptr_t, std::uintptr_t, std::uintptr_t, std::uintptr_t, std::uintptr_t);
                    reinterpret_cast<fail_fn>(*reinterpret_cast<void**>(native::kFailSlotAddr))(0, 0, 0, 0, 0);
                    __debugbreak();                             // 0xbc56606  int3
                    __assume(false);                            // noreturn: the original never continues past the int3
                }
                // 0xbc56577  call 0xE935700   ; rcx=blockSize, rdx=diff+0x27
                native::sub_e935700(blockSize, diff + 0x27u);
            } else {
                // 0xbc56577  call 0xE935700   ; rcx=out->f_e8, rdx=diff
                native::sub_e935700(rax, diff);
            }
            // 0xbc5657c  xorps xmm0,xmm0 ; 0xbc5657f  movups [rdi],xmm0 ; 0xbc56582  mov qword ptr [rdi+0x10],0
            std::memset(&out->f_e8, 0, 24);
        }
        // 0xbc5658a  mov byte ptr [rsi+0x100],0
        out->f_100 = 0u;
    }

done:
    // 0xbc56591..0xbc565ec: epilogue (restore xmm6-xmm13, add rsp,0xB8, pop rdi/rsi, ret)
    out->f_110 = q9->f8;                                        // 0xbc5659c  mov [rsi+0x110],ecx
    out->f_108 = q9->f0;                                        // 0xbc565a5  mov [rsi+0x108],rax
    return;                                                     // 0xbc565ec  ret
}

static native::Footprint sub_bc56190Footprint(FrameOutput* out, const void*, const void*,
    const float*, const float*, const float*, const float*, const void*, const void*) {
    return {{out, sizeof(FrameOutput)}};
}

// Verbatim log of every call instruction in [0xbc56190, 0xbc56607) (rdis dis output,
// two spaces after each address):
#if 0
0xbc56525  call 0x3BAFDC0          ; -> sub_3bafdc0 (boundary, class stl)
0xbc56577  call 0xE935700          ; -> sub_e935700 (lift-set callee, size 0x5, forwarder jmp 0x392960)
0xbc56600  call qword ptr [0xF9A8C78]   ; [data_f9a8c78] import-slot indirect call
#endif
// UNRESOLVED CALL = none: sub_3bafdc0 is a boundary wrapper (stl), sub_e935700 is a lift-set
// callee (forwarder jmp 0x392960), and 0xF9A8C78 is an import slot called through a function
// pointer (data-slot indirect call, hard rule).

LIFT_FN(sub_bc56190, "native::sub_bc56190", 0xbc56190, sub_bc56190, sub_bc56190Footprint);

} // namespace native
