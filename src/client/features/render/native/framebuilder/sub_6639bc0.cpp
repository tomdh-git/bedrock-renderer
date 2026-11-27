// LIFT 0x6639bc0 size 0x24 1.26.62.01 sub_6639bc0
#include "sub_6639bc0.h"

#include <cstring>

static_assert(sizeof(void*) == 8, "sub_6639bc0: x64 ABI, pointer-sized address space");

namespace native {

// sub_6639bc0 (0x6639bc0, size 0x24, 1.26.62.01, "BgfxFrameBuilder slot 87").
//
// The whole function body, instruction for instruction, one straight-line phase,
// no branches:
//   0x6639bc0  push rsi                                   ; prologue (callee-saved)
//   0x6639bc1  sub rsp,0x20                               ; prologue
//   0x6639bc5  mov rsi,rdx                                ; out = RDX
//   0x6639bc8  lea rcx,[0x12AE0E90]                       ; rcx = &data_12ae0e90 (global buffer)
//   0x6639bcf  mov [rdx],rcx                              ; W out+0x0 = &data_12ae0e90
//   0x6639bd2  call 0xEEC7570                             ; call CRT strlen thunk:
//                                                       0xEEC7570  jmp qword ptr [0xF9A9048] ; [0xF9A9048] = strlen [V]
//                                                       argument RCX = out->ptr, result RAX = length
//   0x6639bd7  mov [rsi+8],rax                            ; W out+0x8 = strlen(out->ptr)
//   0x6639bdb  mov rax,rsi                                ; return value = out
//   0x6639bde  add rsp,0x20                               ; epilogue
//   0x6639be2  pop rsi                                    ; epilogue
//   0x6639be3  ret                                       ; RAX = out = RDX
//
// 0 callees in the lift set. One call, quoted verbatim in the #if 0 block below, to a
// CRT library intrinsic through import thunk 0xEEC7570 (data slot 0xF9A9048 = strlen [V]:
// peimports.py key IAT resolution docs/progress/oc_U-EX0b1.md:10; cross-verified by the
// SSO-setter pattern 0x76a72c call 0xEEC7570 then 0x76a731 cmp rax,0xF [V]).
// Same precedent as 0xEEC6EC0 (memcpy through [0xF9A8A98], called as std::memcpy
// directly): strlen is called as std::strlen, not through a boundary wrapper.
//
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x6639bc0, 0x6639be4).
// 0x6639bc0..0x6639be4
void* sub_6639bc0(void* /*RCX entry argument: dead, overwritten before any read*/,
                  FrameBuilderSlot87* out) {
    // 0x6639bc0..0x6639be4
    out->ptr = data_12ae0e90;                                        // 0x6639bc8 lea rcx,[0x12AE0E90]; 0x6639bcf mov [rdx],rcx ; W out+0x0 = &data_12ae0e90
    out->length = std::strlen(out->ptr);                             // 0x6639bd2 call 0xEEC7570 (strlen thunk); 0x6639bd7 mov [rsi+8],rax ; W out+0x8 = strlen(out->ptr)
    return out;                                                      // 0x6639bdb mov rax,rsi; 0x6639bde add rsp,0x20; 0x6639be2 pop rsi; 0x6639be3 ret ; RAX = out = RDX
}

// Verbatim instructions of the function (matches rdis dis 0x6639bc0 0x24, copied from
// the exe listing and machine-checked with tools/sigs/verify_oc.py):
#if 0
0x6639bc0  push rsi
0x6639bc1  sub rsp,0x20
0x6639bc5  mov rsi,rdx
0x6639bc8  lea rcx,[0x12AE0E90]
0x6639bcf  mov [rdx],rcx
0x6639bd2  call 0xEEC7570
0x6639bd7  mov [rsi+8],rax
0x6639bdb  mov rax,rsi
0x6639bde  add rsp,0x20
0x6639be2  pop rsi
0x6639be3  ret
#endif

} // namespace native

LIFT_FN(sub_6639bc0, "sub_6639bc0", 0x6639bc0, sub_6639bc0, nullptr);
