// LIFT 0xbc8c890 size 0x435 1.26.62.01 sub_bc8c890
#include "client/features/render/native/bgfx/sub_bc8c890.h"
#include <cstring>

// Layout assertions anchoring this file to the lifted function's header
// (the full set of offset static_asserts lives in sub_bc8c890.h).
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField20) == 0x20, "sub_bc8c890 copies src+0x20 -> dst+0x20");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField28) == 0x28, "sub_bc8c890 switch copies dst+0x28");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField30) == 0x30, "sub_bc8c890 refcount object pointer at dst+0x30");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField38) == 0x38, "sub_bc8c890 tag byte at dst+0x38");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField50) == 0x50, "sub_bc8c890 copies dst+0x50");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField58) == 0x58, "sub_bc8c890 moves dst+0x58");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mBlock60) == 0x60, "sub_bc8c890 callee block at dst+0x60");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mBlock184) == 0x184, "sub_bc8c890 block at dst+0x184");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField194) == 0x194, "sub_bc8c890 dword at dst+0x194");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField198) == 0x198, "sub_bc8c890 byte at dst+0x198");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField1DC) == 0x1DC, "sub_bc8c890 qword at dst+0x1DC");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField1EC) == 0x1EC, "sub_bc8c890 qword at dst+0x1EC");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mField1FC) == 0x1FC, "sub_bc8c890 word at dst+0x1FC");
static_assert(offsetof(native::bgfx::VvFrameGraphBuilder, mBlock200) == 0x200, "sub_bc8c890 float block at dst+0x200");

// Verbatim call instructions from the disassembly of [0xbc8c890, 0xbc8ccc5).
// 0xbc8c959  call 0x5669770    ; -> sub_5669770  (lift; forward-declared in sub_bc8c890.h)

namespace native::bgfx {

VvFrameGraphBuilder* sub_bc8c890(VvFrameGraphBuilder* dst, VvFrameGraphBuilder* src) {
    // 0xbc8c890..0xbc8c8a6: prologue; dst = rcx (a0), src = rdx (a1)

    // 0xbc8c8a9..0xbc8c8ce: read both source blocks into temporaries, zero src+0x8 and src+0x10,
    // then write both destination blocks (xmm0/xmm1 hold the values read above, so the src
    // zeroing cannot corrupt the dst copies).
    uint8_t tmp0[16];
    uint8_t tmp1[16];
    std::memcpy(tmp0, &src->mBlock00, 16);          // 0xbc8c8a9  movups xmm0,[rdx]       ; R src+0x00 (16B)
    std::memcpy(tmp1, &src->mBlock10, 16);          // 0xbc8c8ac  movups xmm1,[rdx+0x10]  ; R src+0x10 (16B)
    {
        uint64_t zero = 0;
        std::memcpy(&src->mBlock00[8], &zero, 8);   // 0xbc8c8b0  mov qword ptr [rdx+8],0 ; W src+0x08 = 0
    }
    std::memset(&src->mBlock10, 0, 16);             // 0xbc8c8bb  movups [rdx+0x10],xmm2  ; W src+0x10 = 0
    std::memcpy(&dst->mBlock00, tmp0, 16);          // 0xbc8c8bf  movups [rcx],xmm0       ; W dst+0x00 = src+0x00
    std::memcpy(&dst->mBlock10, tmp1, 16);          // 0xbc8c8c2  movups [rcx+0x10],xmm1  ; W dst+0x10 = src+0x10
    dst->mField20 = src->mField20;                 // 0xbc8c8c6..0xbc8c8ca              ; R/W src+0x20 -> dst+0x20
    dst->mField38 = 0xFF;                          // 0xbc8c8ce                         ; W dst+0x38 = 0xFF (provisional tag)

    // 0xbc8c8d2..0xbc8c8f2: switch dispatch on src+0x38 through jump table at 0xF44B320
    // (tag 0 -> 0xbc8c928, tag 1 -> 0xbc8c8f5, tag 2 -> 0xbc8c8fd, tag 3 -> 0xbc8c905;
    //  tag > 3 falls through to 0xbc8c92c and dst+0x38 keeps 0xFF).
    uint8_t tag = src->mField38;                   // 0xbc8c8d2  movzx eax,byte ptr [rdx+0x38]
    if (tag <= 3u) {                               // 0xbc8c8d6  cmp rax,3 ; 0xbc8c8da  ja short 0xBC8C92C
        switch (tag) {                             // 0xbc8c8dc..0xbc8c8f2  lea/jmp r9 via jump table
        case 0:                                    // 0xbc8c928: nothing copied at +0x28
            break;
        case 1:                                    // 0xbc8c8f5..0xbc8c8fb
            dst->mField28 = src->mField28;         // 0xbc8c8f5  mov rdx,[rdx]  ; R *(src+0x28)
                                                   // 0xbc8c8f8  mov [rcx],rdx  ; W dst+0x28
            break;
        case 2:                                    // 0xbc8c8fd..0xbc8c903
            std::memcpy(&dst->mField28, &src->mField28, 16);  // 0xbc8c8fd  movups xmm0,[rdx] ; R 16B at src+0x28
                                                              // 0xbc8c900  movups [rcx],xmm0 ; W 16B at dst+0x28
            break;
        case 3:                                    // 0xbc8c905..0xbc8c924
            std::memset(&dst->mField28, 0, 16);    // 0xbc8c905  xorps xmm0,xmm0
                                                   // 0xbc8c908  movups [rcx],xmm0         ; W dst+0x28 (16B) = 0
            if (uintptr_t obj = src->mField30) {   // 0xbc8c90b  mov rcx,[rsi+0x30]
                                                   // 0xbc8c90f  test rcx,rcx
                                                   // 0xbc8c912  je short 0xBC8C918
                ++(*reinterpret_cast<uint32_t*>(obj + 8));  // 0xbc8c914  lock inc dword ptr [rcx+8] ; W *(src+0x30)+8
            }
            dst->mField28 = src->mField28;         // 0xbc8c918  mov rcx,[rsi+0x28] ; R
                                                   // 0xbc8c91c  mov [r10+0x28],rcx ; W dst+0x28
            dst->mField30 = src->mField30;         // 0xbc8c920  mov rcx,[rsi+0x30] ; R
                                                   // 0xbc8c924  mov [r10+0x30],rcx ; W dst+0x30
            break;
        }
        dst->mField38 = tag;                       // 0xbc8c928  mov [r10+0x38],al ; W dst+0x38 = tag
    }

    // 0xbc8c92c..0xbc8c949: dst+0x50, dst+0x40, then move dst+0x58 (read src, zero src, write dst)
    dst->mField50 = src->mField50;                 // 0xbc8c92c  mov rax,[rsi+0x50]
                                                   // 0xbc8c930  mov [r10+0x50],rax
    std::memcpy(&dst->mBlock40, &src->mBlock40, 16); // 0xbc8c934  movups xmm0,[rsi+0x40]
                                                   // 0xbc8c938  movups [r10+0x40],xmm0
    {
        uint64_t tmp = src->mField58;              // 0xbc8c93d  mov rax,[rsi+0x58]
        src->mField58 = 0;                         // 0xbc8c941  mov qword ptr [rsi+0x58],0
        dst->mField58 = tmp;                       // 0xbc8c949  mov [r10+0x58],rax
    }

    // 0xbc8c959  call 0x5669770    ; -> sub_5669770  (copies [src+0x60, src+0x184) to [dst+0x60, dst+0x184); result unused)
    sub_5669770(static_cast<void*>(&dst->mBlock60), static_cast<const void*>(&src->mBlock60));
    // 0xbc8c95e  nop

    // 0xbc8c95f..0xbc8c9ed: dst+0x194, dst+0x184, dst+0x198, floats 0x19C..0x1A8, blocks 0x1AC..0x1DB
    dst->mField194 = src->mField194;               // 0xbc8c95f  mov ecx,[rsi+0x194]
                                                   // 0xbc8c965  mov rax,[rbp-8]   ; rax = dst restored after the call
                                                   // 0xbc8c969  mov [rax+0x194],ecx
    std::memcpy(&dst->mBlock184, &src->mBlock184, 16); // 0xbc8c96f  movups xmm0,[rsi+0x184]
                                                   // 0xbc8c976  movups [rax+0x184],xmm0
    dst->mField198 = src->mField198;               // 0xbc8c97d  movzx ecx,byte ptr [rsi+0x198]
                                                   // 0xbc8c984  mov [rax+0x198],cl
    dst->mField19C = src->mField19C;               // 0xbc8c98a  movss xmm0,[rsi+0x19C]
    dst->mField1A0 = src->mField1A0;               // 0xbc8c99a  movss xmm0,[rsi+0x1A0]
    dst->mField1A4 = src->mField1A4;               // 0xbc8c9aa  movss xmm0,[rsi+0x1A4]
    dst->mField1A8 = src->mField1A8;               // 0xbc8c9ba  movss xmm0,[rsi+0x1A8]
    std::memcpy(&dst->mBlock1AC, &src->mBlock1AC, 16); // 0xbc8c9ca  movups xmm0,[rsi+0x1AC]
    std::memcpy(&dst->mBlock1BC, &src->mBlock1BC, 16); // 0xbc8c9d1  movups xmm1,[rsi+0x1BC]
    std::memcpy(&dst->mBlock1CB, &src->mBlock1CB, 16); // 0xbc8c9d8  movups xmm2,[rsi+0x1CB]

    // 0xbc8c9f4..0xbc8ca57: qword 0x1DC, floats 0x1E4/0x1E8, qword 0x1EC, floats 0x1F4/0x1F8, word 0x1FC
    dst->mField1DC = src->mField1DC;               // 0xbc8c9f4  mov rcx,[rsi+0x1DC]
                                                   // 0xbc8c9fb  mov [rax+0x1DC],rcx
    dst->mField1E4 = src->mField1E4;               // 0xbc8ca02  movss xmm0,[rsi+0x1E4]
    dst->mField1E8 = src->mField1E8;               // 0xbc8ca12  movss xmm0,[rsi+0x1E8]
    dst->mField1EC = src->mField1EC;               // 0xbc8ca22  mov rcx,[rsi+0x1EC]
                                                   // 0xbc8ca29  mov [rax+0x1EC],rcx
    dst->mField1F4 = src->mField1F4;               // 0xbc8ca30  movss xmm0,[rsi+0x1F4]
    dst->mField1F8 = src->mField1F8;               // 0xbc8ca40  movss xmm0,[rsi+0x1F8]
    dst->mField1FC = src->mField1FC;               // 0xbc8ca50  movzx ecx,word ptr [rsi+0x1FC]
                                                   // 0xbc8ca57  mov [rax+0x1FC],cx

    // 0xbc8ca5e..0xbc8ccb6: floats 0x200..0x294 (38 stores)
    std::memcpy(&dst->mBlock200, &src->mBlock200, 0x98); // 0xbc8ca5e..0xbc8ccb6  movss pairs rsi+0x200..0x294 -> rax+0x200..0x294

    // 0xbc8ccbe..0xbc8ccc4: epilogue; rax = dst
    return dst;                                    // 0xbc8ccc4  ret
}

LIFT_FN(SubBc8c890, "sub_bc8c890", 0xbc8c890, sub_bc8c890, nullptr);

} // namespace native::bgfx
