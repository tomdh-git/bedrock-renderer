#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_6639bc0 (0x6639bc0, size 0x24, 1.26.62.01, "BgfxFrameBuilder slot 87").
//
//   0x6639bc0  push rsi
//   0x6639bc1  sub rsp,0x20
//   0x6639bc5  mov rsi,rdx
//   0x6639bc8  lea rcx,[0x12AE0E90]          ; [data_12ae0e90]
//   0x6639bcf  mov [rdx],rcx                 ; W out+0x0
//   0x6639bd2  call 0xEEC7570                ; -> sub_eec7570 = CRT strlen thunk, jmp qword ptr [0xF9A9048] [V]
//   0x6639bd7  mov [rsi+8],rax               ; W out+0x8
//   0x6639bdb  mov rax,rsi
//   0x6639bde  add rsp,0x20
//   0x6639be2  pop rsi
//   0x6639be3  ret
//
// x64 Microsoft ABI: RCX = entry argument 1 (dead: the lea at 0x6639bc8 overwrites it
// before any read), RDX = out (pointer to the 16-byte slot object), return RAX = out.
// The function reads nothing, writes out+0x0 (8-byte pointer) and out+0x8 (size_t
// length), and has no branches; no null guard or SEH exists in the original (none added
// here).
//
// Layout of the object written at *out, observed from the two stores:
//   out+0x0 (W, 8 bytes): const char* ptr       = &data_12ae0e90
//   out+0x8 (W, 8 bytes): size_t    length      = strlen(out->ptr)
//   out+0x0..0x10 is fully written; no field of the object is read before being written.
//
// data_12ae0e90 (RVA 0x12AE0E90): global char buffer referenced by
//   0x6639bc8  lea rcx,[0x12AE0E90]          ; [data_12ae0e90]
// and by 0xE83EF68 in another function, annotated "log buffer"
// [V] docs/progress/oc_U-A12d.md:402. Runtime address = imageBase + 0x12AE0E90; declared
// here as extern so the lifted code takes its address exactly as the lea does. The buffer
// contents are only ever passed to strlen, whose result is stored; the buffer itself is
// not read by this function.
extern const char data_12ae0e90[];

static constexpr std::size_t kSlot87OffsetPtr = 0x0;
static constexpr std::size_t kSlot87OffsetLength = 0x8;
static constexpr std::size_t kSlot87Size = 0x10;

struct FrameBuilderSlot87 {
    const char* ptr;
    std::size_t length;
};
static_assert(offsetof(FrameBuilderSlot87, ptr) == kSlot87OffsetPtr,
              "sub_6639bc0: slot+0x0 is the pointer field (W, &data_12ae0e90)");
static_assert(offsetof(FrameBuilderSlot87, length) == kSlot87OffsetLength,
              "sub_6639bc0: slot+0x8 is the length field (W, strlen result)");
static_assert(sizeof(FrameBuilderSlot87) == kSlot87Size,
              "sub_6639bc0: slot object is 16 bytes");

namespace native {

// Signature of sub_6639bc0: exact x64 Microsoft ABI mirror of the original.
// RCX (1st entry argument) is dead on entry; RDX is the out pointer; RAX returns out.
void* sub_6639bc0(void* dead_rcx, FrameBuilderSlot87* out);

} // namespace native
