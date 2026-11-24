// LIFT 0xe869ff0 size 0xd1 1.26.62.01 sub_e869ff0
#include "sub_e869ff0.h"

#if 0
0xe869ff0  mov rax,rcx
0xe869ff3  mov rcx,[rdx]
0xe869ff6  mov [rax],rcx
0xe869ff9  movups xmm0,[rdx+8]
0xe869ffd  movups [rax+8],xmm0
0xe86a001  mov rcx,[rdx+0x18]
0xe86a005  mov [rax+0x18],rcx
0xe86a009  movups xmm0,[rdx+0x20]
0xe86a00d  movups [rax+0x20],xmm0
0xe86a011  mov rcx,[rdx+0x30]
0xe86a015  mov [rax+0x30],rcx
0xe86a019  movzx ecx,word ptr [rdx+0x38]
0xe86a01d  mov [rax+0x38],cx
0xe86a021  movzx ecx,word ptr [rdx+0x3A]
0xe86a025  mov [rax+0x3A],cx
0xe86a029  mov qword ptr [rdx+0x30],0
0xe86a031  mov dword ptr [rdx+0x38],0
0xe86a038  mov rcx,[rdx+0x40]
0xe86a03c  mov [rax+0x40],rcx
0xe86a040  movzx ecx,word ptr [rdx+0x48]
0xe86a044  mov [rax+0x48],cx
0xe86a048  movzx ecx,word ptr [rdx+0x4A]
0xe86a04c  mov [rax+0x4A],cx
0xe86a050  mov qword ptr [rdx+0x40],0
0xe86a058  mov dword ptr [rdx+0x48],0
0xe86a05f  mov rcx,[rdx+0x50]
0xe86a063  mov [rax+0x50],rcx
0xe86a067  movzx ecx,word ptr [rdx+0x58]
0xe86a06b  mov [rax+0x58],cx
0xe86a06f  movzx ecx,word ptr [rdx+0x5A]
0xe86a073  mov [rax+0x5A],cx
0xe86a077  mov qword ptr [rdx+0x50],0
0xe86a07f  mov dword ptr [rdx+0x58],0
0xe86a086  mov rcx,[rdx+0x60]
0xe86a08a  mov [rax+0x60],rcx
0xe86a08e  movzx ecx,word ptr [rdx+0x68]
0xe86a092  mov [rax+0x68],cx
0xe86a096  movzx ecx,word ptr [rdx+0x6A]
0xe86a09a  mov [rax+0x6A],cx
0xe86a09e  mov qword ptr [rdx+0x60],0
0xe86a0a6  mov dword ptr [rdx+0x68],0
0xe86a0ad  mov rcx,[rdx+0x70]
0xe86a0b1  mov [rax+0x70],rcx
0xe86a0b5  xorps xmm0,xmm0
0xe86a0b8  movups [rdx+8],xmm0
0xe86a0bc  movups [rdx+0x20],xmm0
0xe86a0c0  ret
#endif

namespace native { namespace d3d12 {

static_assert(sizeof(MoveStruct) == 0x78, "MoveStruct size");

// 0xe869ff0..0xe86a0c0
MoveStruct* sub_e869ff0(MoveStruct* dst, const MoveStruct* src) {
    // 0xe869ff0..0xe869ff6
    dst->f00 = src->f00;
    // 0xe869ff9..0xe869ffd
    dst->f08[0] = src->f08[0];
    dst->f08[1] = src->f08[1];
    // 0xe86a001..0xe86a005
    dst->f18 = src->f18;
    // 0xe86a009..0xe86a00d
    dst->f20[0] = src->f20[0];
    dst->f20[1] = src->f20[1];
    // 0xe86a011..0xe86a015
    dst->f30 = src->f30;
    // 0xe86a019..0xe86a01d
    dst->f38 = src->f38;
    // 0xe86a021..0xe86a025
    dst->f3a = src->f3a;
    // 0xe86a029..0xe86a031
    const_cast<MoveStruct*>(src)->f30 = 0;
    const_cast<MoveStruct*>(src)->f38 = 0;
    const_cast<MoveStruct*>(src)->f3a = 0;
    // 0xe86a038..0xe86a03c
    dst->f40 = src->f40;
    // 0xe86a040..0xe86a044
    dst->f48 = src->f48;
    // 0xe86a048..0xe86a04c
    dst->f4a = src->f4a;
    // 0xe86a050..0xe86a058
    const_cast<MoveStruct*>(src)->f40 = 0;
    const_cast<MoveStruct*>(src)->f48 = 0;
    const_cast<MoveStruct*>(src)->f4a = 0;
    // 0xe86a05f..0xe86a063
    dst->f50 = src->f50;
    // 0xe86a067..0xe86a06b
    dst->f58 = src->f58;
    // 0xe86a06f..0xe86a073
    dst->f5a = src->f5a;
    // 0xe86a077..0xe86a07f
    const_cast<MoveStruct*>(src)->f50 = 0;
    const_cast<MoveStruct*>(src)->f58 = 0;
    const_cast<MoveStruct*>(src)->f5a = 0;
    // 0xe86a086..0xe86a08a
    dst->f60 = src->f60;
    // 0xe86a08e..0xe86a092
    dst->f68 = src->f68;
    // 0xe86a096..0xe86a09a
    dst->f6a = src->f6a;
    // 0xe86a09e..0xe86a0a6
    const_cast<MoveStruct*>(src)->f60 = 0;
    const_cast<MoveStruct*>(src)->f68 = 0;
    const_cast<MoveStruct*>(src)->f6a = 0;
    // 0xe86a0ad..0xe86a0b1
    dst->f70 = src->f70;
    // 0xe86a0b5..0xe86a0bc
    const_cast<MoveStruct*>(src)->f08[0] = 0;
    const_cast<MoveStruct*>(src)->f08[1] = 0;
    const_cast<MoveStruct*>(src)->f20[0] = 0;
    const_cast<MoveStruct*>(src)->f20[1] = 0;
    // 0xe86a0c0  ret
    return dst;
}

LIFT_FN(sub_e869ff0, 0xe869ff0)

} } // namespace
