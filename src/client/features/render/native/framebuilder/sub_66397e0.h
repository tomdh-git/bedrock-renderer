#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_66397e0 (0x66397e0, size 0x6d, 1.26.62.01, "BgfxFrameBuilder slot 74").
//
//   0x66397e0  push rsi                              ; prologue (callee-saved)
//   0x66397e1  push rdi                              ; prologue (callee-saved)
//   0x66397e2  sub rsp,0x28                          ; prologue (scratch frame)
//   0x66397e6  mov rsi,rdx                           ; out = RDX
//   0x66397e9  mov rdi,rcx                           ; self = RCX
//   0x66397ec  mov rax,[rcx]                         ; R self+0x000: vtable pointer
//   0x66397ef  mov rax,[rax+0x228]                   ; R *(self+0x000)+0x228: vtable slot 74 target -> RAX
//   0x66397f6  call qword ptr [0xF99FFA0]            ; -> sub_eea6040 (boundary/vendor thunk via data slot 0xF99FFA0)
//   0x66397fc  test al,al                            ; result in AL
//   0x66397fe  je short 0x6639832                    ; AL == 0 -> out = {0,0}; return out
//   0x6639800  mov rax,[rdi+0x288]                   ; R self+0x288
//   0x6639807  test rax,rax
//   0x663980a  je short 0x6639832                    ; null -> out = {0,0}; return out
//   0x663980c  xorps xmm0,xmm0                       ; out = {0,0}
//   0x663980f  movups [rsi],xmm0                     ; W out+0x0..0x10
//   0x6639812  mov rcx,[rdi+0x290]                   ; R self+0x290
//   0x6639819  test rcx,rcx
//   0x663981c  je short 0x663983a                    ; null -> refObject stored as 0
//   0x663981e  lock inc dword ptr [rcx+8]            ; W *(self->field0x290 + 0x8): refcount +1
//   0x6639822  mov rax,[rdi+0x288]                   ; R self+0x288 (re-read)
//   0x6639829  mov rcx,[rdi+0x290]                   ; R self+0x290 (re-read)
//   0x6639830  jmp short 0x663983c
//   0x663983c  mov [rsi],rax                         ; W out+0x0 = self->field0x288
//   0x663983f  mov [rsi+8],rcx                       ; W out+0x8 = self->field0x290
//   0x6639843  mov rax,rsi                           ; return out (RAX = RDX)
//   0x6639846  add rsp,0x28                          ; epilogue
//   0x663984a  pop rdi                               ; epilogue
//   0x663984b  pop rsi                               ; epilogue
//   0x663984c  ret
//
// x64 Microsoft ABI: RCX = self, RDX = out, return RAX = out.
// Reads [V]: self+0x000 (vtable pointer); *(self+0x000)+0x228 (vtable slot 74, trampoline target);
//          self+0x288 (read twice: before and after the *out zeroing); self+0x290 (read twice).
// Writes [V]: out+0x000 (8 bytes) and out+0x008 (8 bytes); *(self->field0x290 + 0x8) (lock inc).
// Calls [V]: exactly one, 0x66397f6 `call qword ptr [0xF99FFA0]` -> sub_eea6040
//          (boundary/vendor, native_boundary.tsv row 0xeea6040 "thunk via data slot 0xF99FFA0
//          (loader-resolved)"); sub_eea6040 body is `jmp rax`, so the net effect is a call through
//          the BgfxFrameBuilder vtable slot at byte offset 0x228 (index 73, "slot 74") with
//          RCX = self, RDX = out; AL is tested.
// Branches [V]: three conditional (je at 0x66397fe, 0x663980a, 0x663981c) and one unconditional
//          jmp (0x6639830); no loops, no jump tables, no SEH, and no null guard other than the
//          original's own tests (none added in the lift).
//
// Layout constants: every offset the function uses is a named constant, asserted below.

static constexpr std::size_t kFbVtableSlotByteOffset0x228 = 0x228;   // BgfxFrameBuilder vtable slot 74 (byte offset)
static constexpr std::size_t kFbField0x288 = 0x288;                  // self+0x288: pointer returned as out->ptr
static constexpr std::size_t kFbField0x290 = 0x290;                  // self+0x290: refcounted object returned as out->refObject
static constexpr std::size_t kRefcountOffset0x8 = 0x8;               // refcount dword at (self->field0x290 + 0x8)
static constexpr std::size_t kSlotOutOffsetPtr = 0x0;                // out+0x0
static constexpr std::size_t kSlotOutOffsetRefObject = 0x8;          // out+0x8
static constexpr std::size_t kSlotOutSize = 0x10;                    // the out slot object is 16 bytes

// The 16-byte out slot written by this function.
struct FrameBuilderSlot74 {
    void* ptr;            // +0x00 W: self->field0x288, or 0 on the zero paths
    void* refObject;      // +0x08 W: self->field0x290, or 0 on the zero paths (refcount inc'd when non-null)
};
// Partial view of self: exactly the fields this function reads (nothing else is assumed).
struct BgfxFrameBuilderPartial74 {
    std::uint8_t pad0x000[kFbField0x288];
    void* field0x288;     // +0x288 R
    void* field0x290;     // +0x290 R
};
static_assert(offsetof(FrameBuilderSlot74, ptr) == kSlotOutOffsetPtr,
              "sub_66397e0: slot+0x0 is the pointer field (W)");
static_assert(offsetof(FrameBuilderSlot74, refObject) == kSlotOutOffsetRefObject,
              "sub_66397e0: slot+0x8 is the refcounted-object field (W)");
static_assert(sizeof(FrameBuilderSlot74) == kSlotOutSize,
              "sub_66397e0: slot object is 16 bytes");
static_assert(offsetof(BgfxFrameBuilderPartial74, field0x288) == kFbField0x288,
              "sub_66397e0: self+0x288 field offset");
static_assert(offsetof(BgfxFrameBuilderPartial74, field0x290) == kFbField0x290,
              "sub_66397e0: self+0x290 field offset");
static_assert(sizeof(BgfxFrameBuilderPartial74) == kFbField0x290 + sizeof(void*),
              "sub_66397e0: partial view size through the last read field");

namespace native {
namespace boundary {

// sub_eea6040 (boundary/vendor): entered by `call qword ptr [0xF99FFA0]` with
// RCX = self, RDX = out, RAX = caller-loaded trampoline target (out-of-ABI argument, not a
// Microsoft-ABI register argument); body `jmp rax` tails to *RAX(RCX, RDX). Result delivered in AL.
using eea6040_fn = std::uint8_t (*)(void* rcx, void* rdx);
extern eea6040_fn g_eea6040_thunk;   // resolved from Sigs.json at install; see native_boundary.tsv row 0xeea6040

} // namespace boundary

// Signature of sub_66397e0: exact x64 Microsoft ABI mirror of the original.
// RCX (1st entry argument) = self (BgfxFrameBuilder*); RDX (2nd entry argument) = out;
// RAX returns out. The function never returns null (out is returned unchanged).
void* sub_66397e0(void* selfArg /*RCX: self = BgfxFrameBuilder*/,
                  FrameBuilderSlot74* outArg /*RDX: out*/);

} // namespace native
