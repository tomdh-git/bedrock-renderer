// LIFT 0xbc56610 size 0x18e 1.26.62.01 BgfxFrameBuilder slot 52
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc56610.h"

#include <cstdint>
#include <cstring>

namespace {

// Boundary callee: sub_ebcd900 (crt, docs/data/native_boundary.tsv)
native::Boundary<void, void*, float, float, float, float, float, uint32_t, uint8_t> sub_ebcd900("sub_ebcd900");

} // namespace

namespace native::bgfx {

void sub_bc56610(FrameOutput* out, float* b, float* a, const float* m16,
    float val1, float val2, const void* qptr1, std::uint8_t flag, const void* qptr2,
    const Q9* q9) {

    // 0xbc56610..0xbc56636: prologue; save incoming stack args
    // 0xbc56636..0xbc56639: xorps xmm1,xmm1
    // 0xbc56639..0xbc56655: zero out [out+0xD8..out+0x110] (4 movups)
    // 0xbc56655..0xbc5665c: out->f00 = -1 (0xFFFFFFFFFFFFFFFF)
    // 0xbc5665c..0xbc56660: out->f08 = 0 (via xmm1)
    // 0xbc56660..0xbc56667: out->f18 = 1.0f (0x3F800000)
    // 0xbc56667..0xbc5666b: out->f1C..f28 = 0 (via xmm1)
    // 0xbc5666b..0xbc56672: out->f2C = 1.0f
    // 0xbc56672..0xbc56676: out->f30..f3C = 0
    // 0xbc56676..0xbc5667d: out->f40 = 1.0f
    // 0xbc5667d..0xbc56681: out->f44..f50 = 0
    // 0xbc56681..0xbc56689: out->f54 = [data_efd3400] (double as movsd)
    // 0xbc5668e..0xbc56692: out->f5C..f68 = 0
    // 0xbc56692..0xbc56699: out->f6C = 1.0f
    // 0xbc56699..0xbc5669d: out->f70..f7C = 0
    // 0xbc5669d..0xbc566a7: out->f80 = 1.0f
    // 0xbc566a7..0xbc566ae: out->f84..f90 = 0
    // 0xbc566ae..0xbc566b8: out->f94 = 1.0f
    // 0xbc566b8..0xbc566bf: out->f98..fA4 = 0
    // 0xbc566bf..0xbc566c9: out->fA8 = 0
    // 0xbc566c9..0xbc566d1: out->fAC..fB4 = [data_efd32d0]
    // 0xbc566d8..0xbc566e0: out->fBC..fC8 = [data_efd32f0]
    // 0xbc566e7..0xbc566ef: out->fCC..fD0 = [data_f0ec830]
    // 0xbc566f7..0xbc56701: out->fD4 = 1.0f
    // 0xbc56701..0xbc5670a: out->fD8 = 7 (word)
    // 0xbc5670a..0xbc5671b: out->fDC = 0x3F800000FFFFFFFF (qword)
    // 0xbc5671b..0xbc5672f: setup call to sub_bc56190
    // 0xbc56733  call 0xBC56190                                ; -> sub_bc56190
    native::sub_bc56190(out, qptr1, qptr2, reinterpret_cast<const float*>(q9), b, a,
        m16, reinterpret_cast<const void*>(qptr2), q9);

    // 0xbc56738..0xbc56739: nop
    // 0xbc56739..0xbc56743: xmm0 = val2, xmm4 = val1
    // 0xbc56743..0xbc56747: rax = m16
    // 0xbc56747..0xbc5674b: rcx = out
    // 0xbc5674b..0xbc5674f: rcx = out + 0x18
    // 0xbc5674f..0xbc56753: xmm1 = m16[0]
    // 0xbc56753..0xbc56758: xmm5 = m16[1]
    // 0xbc56758..0xbc5675d: xmm3 = m16[3]
    // 0xbc5675d..0xbc56761: xmm3 += xmm5
    // 0xbc56761..0xbc56766: xmm2 = m16[2]
    // 0xbc56766..0xbc5676a: xmm2 += xmm1
    // 0xbc5676a..0xbc5676e: compare flag byte with 0
    // 0xbc5676e..0xbc56773: [rsp+0x40] = (flag == 0)
    // 0xbc56773..0xbc56779: [rsp+0x30] = val2
    // 0xbc56779..0xbc5677f: [rsp+0x28] = val1
    // 0xbc5677f..0xbc56785: [rsp+0x20] = xmm5 (m16[1])
    // 0xbc56785..0xbc5678d: [rsp+0x38] = 0
    // 0xbc5678d  call 0xEBCD900                                ; -> sub_ebcd900
    sub_ebcd900(out + 0x18,
        m16[0], m16[1], m16[2] + m16[0], m16[3] + m16[1],
        val1, val2, 0, (flag == 0) ? 1 : 0);

    // 0xbc56792..0xbc56793: nop
    // 0xbc56793..0xbc56797: rax = out
    // 0xbc56797..0xbc5679b: add rsp,0x58
    // 0xbc5679b..0xbc5679c: pop rsi
    // 0xbc5679c..0xbc5679d: pop rbp
    // 0xbc5679d: ret
}

static_assert(sizeof(FrameOutput) == 0x118, "FrameOutput must be 0x118 bytes");

LIFT_FN(sub_bc56610, "sub_bc56610", 0xbc56610, sub_bc56610, nullptr);

} // namespace native::bgfx