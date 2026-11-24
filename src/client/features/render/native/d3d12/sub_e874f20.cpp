// LIFT 0xe874f20 size 0x127 1.26.62.01 BgfxFrameBuilder slot 16
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e874f20.h"

#include <cstdint>

namespace native::d3d12 {

namespace {

// Callees in lift set: none
// Callees outside lift set (boundary): none

} // namespace

// Forward declaration for callee at 0x53d5c20 (not in lift set, not in native_boundary.tsv)
extern "C" void sub_53d5c20(float* dst, const float* src);

// 0xe874f20..0xe875047
void sub_e874f20(FrameSlot16* dst, const FrameSlot16* src) {
    // 0xe874f20..0xe874f26
    // push rsi
    // push rdi
    // sub rsp, 0x28
    // mov rax, rcx
    // cmp byte ptr [rcx+0x4C], 3
    // jne short 0xE874F5E
    if (dst->field_4C == 3) {
        // 0xe874f2f..0xe874f33
        // mov ecx, [rdx]
        // mov [rax], ecx
        dst->field_00 = src->field_00;
        
        // 0xe874f33..0xe874f37
        // cmp byte ptr [rdx+0x44], 1
        // jne 0xE87502D
        if (src->field_44 == 1) {
            // 0xe874f3d..0xe874f4e
            // lea rcx, [rax+4]
            // lea r8, [rdx+4]
            // mov rsi, rdx
            // mov rdx, r8
            // mov rdi, rax
            // 0xe874f4e  call 0x53D5C20
            sub_53d5c20(&dst->field_04[0], &src->field_04[0]);
            
            // 0xe874f53..0xe874f59
            // mov rdx, rsi
            // mov rax, rdi
            // jmp 0xE875031
        } else {
            // 0xe87502d..0xe875031
            // mov byte ptr [rax+0x44], 0
            // jmp 0xE875031
            dst->field_44 = 0;
        }
        
        // 0xe875031..0xe87503c
        // movzx ecx, byte ptr [rdx+0x4A]
        // mov [rax+0x4A], cl
        // movzx ecx, word ptr [rdx+0x48]
        // mov [rax+0x48], cx
        dst->field_4A = src->field_4A;
        dst->field_48 = src->field_48;
    } else {
        // 0xe874f5e..0xe874f66
        // mov byte ptr [rax+0x4C], 0xFF
        // mov ecx, [rdx]
        // mov [rax], ecx
        // mov byte ptr [rax+0x44], 0
        dst->field_4C = 0xFF;
        dst->field_00 = src->field_00;
        dst->field_44 = 0;
        
        // 0xe874f6a..0xe874f6e
        // cmp byte ptr [rdx+0x44], 1
        // jne 0xE875018
        if (src->field_44 == 1) {
            // 0xe874f74..0xe875014
            // 16x movss copy of field_04[0..15]
            // 0xe874f74  movss xmm0,[rdx+4]       ; 0xe874f79  movss [rax+4],xmm0
            dst->field_04[0] = src->field_04[0];
            // 0xe874f7e  movss xmm0,[rdx+8]       ; 0xe874f83  movss [rax+8],xmm0
            dst->field_04[1] = src->field_04[1];
            // 0xe874f88  movss xmm0,[rdx+0xC]     ; 0xe874f8d  movss [rax+0xC],xmm0
            dst->field_04[2] = src->field_04[2];
            // 0xe874f92  movss xmm0,[rdx+0x10]    ; 0xe874f97  movss [rax+0x10],xmm0
            dst->field_04[3] = src->field_04[3];
            // 0xe874f9c  movss xmm0,[rdx+0x14]    ; 0xe874fa1  movss [rax+0x14],xmm0
            dst->field_04[4] = src->field_04[4];
            // 0xe874fa6  movss xmm0,[rdx+0x18]    ; 0xe874fab  movss [rax+0x18],xmm0
            dst->field_04[5] = src->field_04[5];
            // 0xe874fb0  movss xmm0,[rdx+0x1C]    ; 0xe874fb5  movss [rax+0x1C],xmm0
            dst->field_04[6] = src->field_04[6];
            // 0xe874fba  movss xmm0,[rdx+0x20]    ; 0xe874fbf  movss [rax+0x20],xmm0
            dst->field_04[7] = src->field_04[7];
            // 0xe874fc4  movss xmm0,[rdx+0x24]    ; 0xe874fc9  movss [rax+0x24],xmm0
            dst->field_04[8] = src->field_04[8];
            // 0xe874fce  movss xmm0,[rdx+0x28]    ; 0xe874fd3  movss [rax+0x28],xmm0
            dst->field_04[9] = src->field_04[9];
            // 0xe874fd8  movss xmm0,[rdx+0x2C]    ; 0xe874fdd  movss [rax+0x2C],xmm0
            dst->field_04[10] = src->field_04[10];
            // 0xe874fe2  movss xmm0,[rdx+0x30]    ; 0xe874fe7  movss [rax+0x30],xmm0
            dst->field_04[11] = src->field_04[11];
            // 0xe874fec  movss xmm0,[rdx+0x34]    ; 0xe874ff1  movss [rax+0x34],xmm0
            dst->field_04[12] = src->field_04[12];
            // 0xe874ff6  movss xmm0,[rdx+0x38]    ; 0xe874ffb  movss [rax+0x38],xmm0
            dst->field_04[13] = src->field_04[13];
            // 0xe875000  movss xmm0,[rdx+0x3C]    ; 0xe875005  movss [rax+0x3C],xmm0
            dst->field_04[14] = src->field_04[14];
            // 0xe87500a  movss xmm0,[rdx+0x40]    ; 0xe87500f  movss [rax+0x40],xmm0
            dst->field_04[15] = src->field_04[15];
            
            // 0xe875014
            // mov byte ptr [rax+0x44], 1
            dst->field_44 = 1;
        }
        
        // 0xe875018..0xe87502b
        // movzx ecx, byte ptr [rdx+0x4A]
        // mov [rax+0x4A], cl
        // movzx ecx, word ptr [rdx+0x48]
        // mov [rax+0x48], cx
        // mov byte ptr [rax+0x4C], 3
        // jmp short 0xE875040
        dst->field_4A = src->field_4A;
        dst->field_48 = src->field_48;
        dst->field_4C = 3;
    }
    
    // 0xe875040..0xe875047
    // add rsp, 0x28
    // pop rdi
    // pop rsi
    // ret
}

// Layout assertions (verified in sub_e874f20.h)
static_assert(sizeof(FrameSlot16) == 0x50, "FrameSlot16 size mismatch");
static_assert(offsetof(FrameSlot16, field_00) == 0x00, "FrameSlot16::field_00 offset mismatch");
static_assert(offsetof(FrameSlot16, field_04) == 0x04, "FrameSlot16::field_04 offset mismatch");
static_assert(offsetof(FrameSlot16, field_44) == 0x44, "FrameSlot16::field_44 offset mismatch");
static_assert(offsetof(FrameSlot16, field_48) == 0x48, "FrameSlot16::field_48 offset mismatch");
static_assert(offsetof(FrameSlot16, field_4A) == 0x4A, "FrameSlot16::field_4A offset mismatch");
static_assert(offsetof(FrameSlot16, field_4C) == 0x4C, "FrameSlot16::field_4C offset mismatch");

// Verbatim log of every call instruction in [0xe874f20, 0xe875047) (rdis dis output, two spaces after address):
#if 0
0xe874f4e  call 0x53D5C20                                ; -> sub_53d5c20
#endif

// Calls out of lifted code:
//   sub_53d5c20 (0x53d5c20) - not in lift set, not in native_boundary.tsv

LIFT_FN(sub_e874f20, "sub_e874f20", 0xe874f20, sub_e874f20, nullptr);

} // namespace native::d3d12