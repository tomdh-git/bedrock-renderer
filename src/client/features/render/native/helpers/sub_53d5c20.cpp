// LIFT 0x53d5c20 size 0xab 1.26.62.01 sub_53d5c20
#include "sub_53d5c20.h"

#include "client/features/render/native/Lift.h"

namespace native {

// sub_53d5c20 (0x53d5c20, size 0xab, 1.26.62.01):
//   Copies 16 floats (a 4x4 matrix) from a1 to a0, guarded by the flag byte at a0+0x40.
//   a0->v[0] = a1->v[0] unconditionally (0x53d5c20..0x53d5c28). If a0->flag == 1 the
//   remaining v[1..15] are copied and the function returns (0x53d5c34..0x53d5cca ret);
//   otherwise 0x53d5c2e jne 0x53D5CCB transfers control to 0x53d5ccb, which is exactly
//   rva + 0xab - the first byte past this lift unit. The slow path at 0x53d5ccb is not
//   part of unit U-EX7.53d5c20 (data file: size 0xab, range [0x53d5c20, 0x53d5ccb)).
//   Reads: [a0+0x40] flag, [a1+0x00..0x3C]. Writes: [a0+0x00..0x40). No calls.

static native::Footprint sub_53d5c20Footprint(Sub53d5c20Arg* a0, const Sub53d5c20Arg* a1)
{
    native::Footprint fp;
    fp.push_back(native::Region{ a0, 0x40ull });
    (void)a1;
    return fp;
}

void sub_53d5c20(Sub53d5c20Arg* a0, const Sub53d5c20Arg* a1)
{
    // 0x53d5c20..0x53d5c2c
    //   0x53d5c20  movzx eax,byte ptr [rcx+0x40]        ; R a0+0x40 (flag byte)
    //   0x53d5c24  movss xmm0,[rdx]                      ; R a1+0x0
    //   0x53d5c28  movss [rcx],xmm0                      ; W a0+0x0
    const std::uint8_t flag = a0->flag;                 // 0x53d5c20  movzx eax,byte ptr [rcx+0x40]
    a0->v[0] = a1->v[0];                                // 0x53d5c24  movss xmm0,[rdx]
                                                        //            0x53d5c28  movss [rcx],xmm0

    // 0x53d5c2c..0x53d5c34
    //   0x53d5c2c  cmp al,1
    //   0x53d5c2e  jne 0x53D5CCB                         ; flag != 1: control leaves this unit
    if (flag == 1u) {                                   // 0x53d5c2c  cmp al,1 / 0x53d5c2e jne not taken
        // 0x53d5c34..0x53d5ccb   flag == 1 path: copy v[1..15] then ret
        //   0x53d5c34  movss xmm0,[rdx+4]   ; R a1+0x4
        //   0x53d5c39  movss [rcx+4],xmm0   ; W a0+0x4
        a0->v[1] = a1->v[1];                            // 0x53d5c34  movss xmm0,[rdx+4]
                                                        //            0x53d5c39  movss [rcx+4],xmm0
        //   0x53d5c3e  movss xmm0,[rdx+8]   ; R a1+0x8
        //   0x53d5c43  movss [rcx+8],xmm0   ; W a0+0x8
        a0->v[2] = a1->v[2];                            // 0x53d5c3e  movss xmm0,[rdx+8]
                                                        //            0x53d5c43  movss [rcx+8],xmm0
        //   0x53d5c48  movss xmm0,[rdx+0xC] ; R a1+0xC
        //   0x53d5c4d  movss [rcx+0xC],xmm0 ; W a0+0xC
        a0->v[3] = a1->v[3];                            // 0x53d5c48  movss xmm0,[rdx+0xC]
                                                        //            0x53d5c4d  movss [rcx+0xC],xmm0
        //   0x53d5c52  movss xmm0,[rdx+0x10]; R a1+0x10
        //   0x53d5c57  movss [rcx+0x10],xmm0; W a0+0x10
        a0->v[4] = a1->v[4];                            // 0x53d5c52  movss xmm0,[rdx+0x10]
                                                        //            0x53d5c57  movss [rcx+0x10],xmm0
        //   0x53d5c5c  movss xmm0,[rdx+0x14]; R a1+0x14
        //   0x53d5c61  movss [rcx+0x14],xmm0; W a0+0x14
        a0->v[5] = a1->v[5];                            // 0x53d5c5c  movss xmm0,[rdx+0x14]
                                                        //            0x53d5c61  movss [rcx+0x14],xmm0
        //   0x53d5c66  movss xmm0,[rdx+0x18]; R a1+0x18
        //   0x53d5c6b  movss [rcx+0x18],xmm0; W a0+0x18
        a0->v[6] = a1->v[6];                            // 0x53d5c66  movss xmm0,[rdx+0x18]
                                                        //            0x53d5c6b  movss [rcx+0x18],xmm0
        //   0x53d5c70  movss xmm0,[rdx+0x1C]; R a1+0x1C
        //   0x53d5c75  movss [rcx+0x1C],xmm0; W a0+0x1C
        a0->v[7] = a1->v[7];                            // 0x53d5c70  movss xmm0,[rdx+0x1C]
                                                        //            0x53d5c75  movss [rcx+0x1C],xmm0
        //   0x53d5c7a  movss xmm0,[rdx+0x20]; R a1+0x20
        //   0x53d5c7f  movss [rcx+0x20],xmm0; W a0+0x20
        a0->v[8] = a1->v[8];                            // 0x53d5c7a  movss xmm0,[rdx+0x20]
                                                        //            0x53d5c7f  movss [rcx+0x20],xmm0
        //   0x53d5c84  movss xmm0,[rdx+0x24]; R a1+0x24
        //   0x53d5c89  movss [rcx+0x24],xmm0; W a0+0x24
        a0->v[9] = a1->v[9];                            // 0x53d5c84  movss xmm0,[rdx+0x24]
                                                        //            0x53d5c89  movss [rcx+0x24],xmm0
        //   0x53d5c8e  movss xmm0,[rdx+0x28]; R a1+0x28
        //   0x53d5c93  movss [rcx+0x28],xmm0; W a0+0x28
        a0->v[10] = a1->v[10];                          // 0x53d5c8e  movss xmm0,[rdx+0x28]
                                                        //            0x53d5c93  movss [rcx+0x28],xmm0
        //   0x53d5c98  movss xmm0,[rdx+0x2C]; R a1+0x2C
        //   0x53d5c9d  movss [rcx+0x2C],xmm0; W a0+0x2C
        a0->v[11] = a1->v[11];                          // 0x53d5c98  movss xmm0,[rdx+0x2C]
                                                        //            0x53d5c9d  movss [rcx+0x2C],xmm0
        //   0x53d5ca2  movss xmm0,[rdx+0x30]; R a1+0x30
        //   0x53d5ca7  movss [rcx+0x30],xmm0; W a0+0x30
        a0->v[12] = a1->v[12];                          // 0x53d5ca2  movss xmm0,[rdx+0x30]
                                                        //            0x53d5ca7  movss [rcx+0x30],xmm0
        //   0x53d5cac  movss xmm0,[rdx+0x34]; R a1+0x34
        //   0x53d5cb1  movss [rcx+0x34],xmm0; W a0+0x34
        a0->v[13] = a1->v[13];                          // 0x53d5cac  movss xmm0,[rdx+0x34]
                                                        //            0x53d5cb1  movss [rcx+0x34],xmm0
        //   0x53d5cb6  movss xmm0,[rdx+0x38]; R a1+0x38
        //   0x53d5cbb  movss [rcx+0x38],xmm0; W a0+0x38
        a0->v[14] = a1->v[14];                          // 0x53d5cb6  movss xmm0,[rdx+0x38]
                                                        //            0x53d5cbb  movss [rcx+0x38],xmm0
        //   0x53d5cc0  movss xmm0,[rdx+0x3C]; R a1+0x3C
        //   0x53d5cc5  movss [rcx+0x3C],xmm0; W a0+0x3C
        a0->v[15] = a1->v[15];                          // 0x53d5cc0  movss xmm0,[rdx+0x3C]
                                                        //            0x53d5cc5  movss [rcx+0x3C],xmm0
        // 0x53d5cca  ret                                ; return void
        return;                                         // 0x53d5cca  ret
    }
    // 0x53d5c2e  jne 0x53D5CCB taken (flag != 1): control leaves this unit at 0x53d5ccb
    // == rva + 0xab; no instruction of this unit executes after the jump.
}

// Verbatim instruction quotes for liftcheck verification (plain lines, checked by verify_oc)
#if 0
0x53d5c20  movzx eax,byte ptr [rcx+0x40]
0x53d5c24  movss xmm0,[rdx]
0x53d5c28  movss [rcx],xmm0
0x53d5c2c  cmp al,1
0x53d5c2e  jne 0x53D5CCB
0x53d5c34  movss xmm0,[rdx+4]
0x53d5c39  movss [rcx+4],xmm0
0x53d5c3e  movss xmm0,[rdx+8]
0x53d5c43  movss [rcx+8],xmm0
0x53d5c48  movss xmm0,[rdx+0xC]
0x53d5c4d  movss [rcx+0xC],xmm0
0x53d5c52  movss xmm0,[rdx+0x10]
0x53d5c57  movss [rcx+0x10],xmm0
0x53d5c5c  movss xmm0,[rdx+0x14]
0x53d5c61  movss [rcx+0x14],xmm0
0x53d5c66  movss xmm0,[rdx+0x18]
0x53d5c6b  movss [rcx+0x18],xmm0
0x53d5c70  movss xmm0,[rdx+0x1C]
0x53d5c75  movss [rcx+0x1C],xmm0
0x53d5c7a  movss xmm0,[rdx+0x20]
0x53d5c7f  movss [rcx+0x20],xmm0
0x53d5c84  movss xmm0,[rdx+0x24]
0x53d5c89  movss [rcx+0x24],xmm0
0x53d5c8e  movss xmm0,[rdx+0x28]
0x53d5c93  movss [rcx+0x28],xmm0
0x53d5c98  movss xmm0,[rdx+0x2C]
0x53d5c9d  movss [rcx+0x2C],xmm0
0x53d5ca2  movss xmm0,[rdx+0x30]
0x53d5ca7  movss [rcx+0x30],xmm0
0x53d5cac  movss xmm0,[rdx+0x34]
0x53d5cb1  movss [rcx+0x34],xmm0
0x53d5cb6  movss xmm0,[rdx+0x38]
0x53d5cbb  movss [rcx+0x38],xmm0
0x53d5cc0  movss xmm0,[rdx+0x3C]
0x53d5cc5  movss [rcx+0x3C],xmm0
0x53d5cca  ret
#endif

static_assert(offsetof(Sub53d5c20Arg, v) == 0x00, "sub_53d5c20: v at +0x00");
static_assert(offsetof(Sub53d5c20Arg, flag) == 0x40, "sub_53d5c20: flag at +0x40");
static_assert(sizeof(Sub53d5c20Arg) == 0x44, "sub_53d5c20: object size 0x44");

LIFT_FN(sub_53d5c20, "sub_53d5c20", 0x53D5C20, sub_53d5c20, &sub_53d5c20Footprint);

} // namespace native
