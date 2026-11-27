#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_6639b70 (0x6639b70, size 0x42, 1.26.62.01, "BgfxFrameBuilder slot 86").
//
//   0x6639b70  push rsi
//   0x6639b71  sub rsp,0x20
//   0x6639b75  mov rsi,rcx
//   0x6639b78  mov rax,[rcx]                ; rax = *this (vfptr)                   [R this+0x0]
//   0x6639b7b  mov rax,[rax+0x298]          ; rax = vfptr[0x54] (slot 84)          [R *(this+0x0)+0x298]
//   0x6639b82  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040 (vendor boundary thunk: jmp rax)
//   0x6639b88  movss xmm0,[0xEEC8060]       ; xmm0 = data_eec8060 (default float)   [R data_eec8060]
//   0x6639b90  test al,al
//   0x6639b92  je short 0x6639BAC
//   0x6639b94  mov eax,[rsi+0x6F8]          ; eax = this->field_0x6F8              [R this+0x6F8]
//   0x6639b9a  cmp rax,4
//   0x6639b9e  ja short 0x6639BAC
//   0x6639ba0  lea rcx,[0xF2BF170]          ; rcx = &data_f2bf170 (float[5])        [R data_f2bf170]
//   0x6639ba7  movss xmm0,[rcx+rax*4]       ; xmm0 = data_f2bf170[eax]              [R data_f2bf170+rax*4]
//   0x6639bac  add rsp,0x20
//   0x6639bb0  pop rsi
//   0x6639bb1  ret
//
// x64 Microsoft ABI: RCX = this, return float in XMM0.
// The function reads the vfptr at this+0x0, then vfptr[0x54] (slot 84), and calls it via the
// vendor boundary thunk sub_eea6040 (data slot 0xF99FFA0). The thunk tail-jumps to RAX (the
// vtable target). The boolean result in AL gates reading this+0x6F8 (uint32) and indexing
// into data_f2bf170[0..4]. Default return is data_eec8060.
//
// Layout of fields in 'this' read by this function (all [V]):
//   this+0x0      (R, 8 bytes): vfptr (pointer to vtable)
//   this+0x6F8    (R, 4 bytes): uint32_t index (used as index into data_f2bf170[5])
//   vfptr+0x298   (R, 8 bytes): vtable slot 0x54 (slot 84), the virtual method pointer

static constexpr std::size_t kSlot86OffsetVfptr = 0x0;
static constexpr std::size_t kSlot86OffsetIndex = 0x6F8;
static constexpr std::size_t kVtableSlot54Offset = 0x298;

// Global data referenced by this function (RVAs relative to image base).
// data_eec8060: single float, default return value.
// data_f2bf170: array of 5 floats, indexed by this+0x6F8 (0..4).
extern const float data_eec8060;
extern const float data_f2bf170[5];

namespace native {

// Signature of sub_6639b70: exact x64 Microsoft ABI mirror of the original.
// RCX = this (BgfxFrameBuilder*), return float in XMM0.
float sub_6639b70(void* thisPtr);

} // namespace native