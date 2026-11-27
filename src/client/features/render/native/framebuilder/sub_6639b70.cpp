// LIFT 0x6639b70 size 0x42 1.26.62.01 BgfxFrameBuilder slot 86
#include "sub_6639b70.h"

static_assert(sizeof(void*) == 8, "sub_6639b70: x64 ABI, pointer-sized address space");

namespace native {

// sub_6639b70 (0x6639b70, size 0x42, 1.26.62.01, "BgfxFrameBuilder slot 86").
//
// The whole function body, instruction for instruction:
//   0x6639b70  push rsi                                   ; prologue (callee-saved rsi)
//   0x6639b71  sub rsp,0x20                               ; prologue (shadow space + alignment)
//   0x6639b75  mov rsi,rcx                                ; rsi = this
//   0x6639b78  mov rax,[rcx]                              ; rax = *this (vfptr)                   [R this+0x0]
//   0x6639b7b  mov rax,[rax+0x298]                        ; rax = vfptr[0x54] (slot 84)           [R *(this+0x0)+0x298]
//   0x6639b82  call qword ptr [0xF99FFA0]                 ; call sub_eea6040 thunk (vendor boundary: jmp rax)
//   0x6639b88  movss xmm0,[0xEEC8060]                     ; xmm0 = data_eec8060 (default float)   [R data_eec8060]
//   0x6639b90  test al,al                                 ; test boolean result from thunk
//   0x6639b92  je short 0x6639BAC                         ; if zero, skip to return default
//   0x6639b94  mov eax,[rsi+0x6F8]                        ; eax = this->field_0x6F8 (uint32)      [R this+0x6F8]
//   0x6639b9a  cmp rax,4                                  ; compare index with 4
//   0x6639b9e  ja short 0x6639BAC                         ; if index > 4 (unsigned), skip
//   0x6639ba0  lea rcx,[0xF2BF170]                        ; rcx = &data_f2bf170 (float[5])        [R data_f2bf170]
//   0x6639ba7  movss xmm0,[rcx+rax*4]                     ; xmm0 = data_f2bf170[index]          [R data_f2bf170+rax*4]
//   0x6639bac  add rsp,0x20                               ; epilogue
//   0x6639bb0  pop rsi                                    ; epilogue
//   0x6639bb1  ret                                        ; return float in xmm0
//
// Reads: this+0x0 (vfptr), vfptr+0x298 (vtable slot 84), this+0x6F8 (uint32 index),
//        data_eec8060 (float), data_f2bf170[5] (float array).
// Writes: none to game memory (only stack frame and XMM0 return).
// Calls: one, to sub_eea6040 via data slot 0xF99FFA0 (vendor boundary, thunk `jmp rax`).
// The thunk tail-jumps to RAX (the vtable target loaded at 0x6639b7b).
// Return value of thunk in AL is tested as a boolean gate.
// 0 callees in the lift set.
//
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x6639b70, 0x6639bb2).

// Boundary callee: sub_eea6040, vendor class, reached through data slot 0xF99FFA0
// (docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)").
// Called with RCX = this; the thunk is `jmp rax` where RAX was pre-loaded with vfptr[0x54].
// Return value (AL) is used as a boolean.
native::Boundary<uint8_t, void*> sub_eea6040("sub_eea6040");

// data_eec8060: global float at RVA 0xEEC8060 (default return value).
// data_f2bf170: global float[5] at RVA 0xF2BF170 (indexed by this+0x6F8 when in 0..4).
static const float* const g_data_eec8060 = reinterpret_cast<const float*>(0x152EEC8060ULL); // imageBase 0x140000000 + RVA 0xEEC8060
static const float* const g_data_f2bf170 = reinterpret_cast<const float*>(0x152F2BF170ULL); // imageBase 0x140000000 + RVA 0xF2BF170

// 0x6639b70..0x6639bb2
float sub_6639b70(void* thisPtr) {
    // 0x6639b70..0x6639b82
    // prologue: push rsi; sub rsp,0x20; mov rsi,rcx
    void** vfptr = *reinterpret_cast<void***>(thisPtr);           // 0x6639b78  mov rax,[rcx]           ; [R this+0x0]
    void* vfunc = vfptr[0x54];                                     // 0x6639b7b  mov rax,[rax+0x298]     ; [R *(this+0x0)+0x298]
    (void)vfunc; // read preserved (vfunc is the thunk target in RAX)

    // 0x6639b82  call qword ptr [0xF99FFA0]
    uint8_t flag = sub_eea6040(thisPtr);                          // 0x6639b82  call qword ptr [0xF99FFA0]

    // 0x6639b88..0x6639ba7
    float result = *g_data_eec8060;                               // 0x6639b88  movss xmm0,[0xEEC8060]  ; [R data_eec8060]
    if (flag) {                                                   // 0x6639b90  test al,al ; 0x6639b92  je short 0x6639BAC
        // 0x6639b94..0x6639b9e
        uint32_t idx = *reinterpret_cast<uint32_t*>(
            reinterpret_cast<uint8_t*>(thisPtr) + 0x6F8);          // 0x6639b94  mov eax,[rsi+0x6F8]    ; [R this+0x6F8]
        if (idx <= 4u) {                                          // 0x6639b9a  cmp rax,4 ; 0x6639b9e  ja short 0x6639BAC
            // 0x6639ba0..0x6639ba7
            result = g_data_f2bf170[idx];                         // 0x6639ba0  lea rcx,[0xF2BF170] ; 0x6639ba7  movss xmm0,[rcx+rax*4] ; [R data_f2bf170+rax*4]
        }
    }

    // 0x6639bac..0x6639bb1
    // epilogue: add rsp,0x20; pop rsi; ret
    return result;                                                // 0x6639bac  add rsp,0x20 ; 0x6639bb0  pop rsi ; 0x6639bb1  ret
}

// Verbatim instructions of the function (matches rdis dis 0x6639b70 0x42, copied from
// the exe listing and machine-checked with tools/sigs/verify_oc.py):
#if 0
0x6639b70  push rsi
0x6639b71  sub rsp,0x20
0x6639b75  mov rsi,rcx
0x6639b78  mov rax,[rcx]
0x6639b7b  mov rax,[rax+0x298]
0x6639b82  call qword ptr [0xF99FFA0]
0x6639b88  movss xmm0,[0xEEC8060]
0x6639b90  test al,al
0x6639b92  je short 0x6639BAC
0x6639b94  mov eax,[rsi+0x6F8]
0x6639b9a  cmp rax,4
0x6639b9e  ja short 0x6639BAC
0x6639ba0  lea rcx,[0xF2BF170]
0x6639ba7  movss xmm0,[rcx+rax*4]
0x6639bac  add rsp,0x20
0x6639bb0  pop rsi
0x6639bb1  ret
#endif

} // namespace native

LIFT_FN(sub_6639b70, "sub_6639b70", 0x6639b70, sub_6639b70, nullptr);