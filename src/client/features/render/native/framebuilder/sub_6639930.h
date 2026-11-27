#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_6639930 (0x6639930, size 0x72, 1.26.62.01, "BgfxFrameBuilder slot 90").
//
// Reversed from the exe listing (rdis fn 0x6639930; [0x6639930, 0x66399a2), 0x72 bytes,
// 33 instructions); every offset below is a read performed by an instruction of the
// function, cited by address.
//
//   0x6639938  mov rax,[rcx]           ; R self+0x0 (vtable pointer) -- before call #1
//   0x663993b  mov rax,[rax+0x230]     ; R vtable+0x230 (slot 70 function pointer) -> RAX
//   0x6639942  call qword ptr [0xF99FFA0]  ; call #1 -> sub_eea6040 via data slot 0xF99FFA0;
//   0xEEA6040  jmp rax                   ; tail-calls RAX (= vtable+0x230 target), RCX = self
//   0x6639948  test al,al              ; call #1 result low byte == 0?
//   0x663994a  je short 0x663995C      ; if zero: call #2 path
//   0x663994c  mov rax,[rsi+0x358]     ; R self+0x358 (state object pointer, RSI = self)
//   0x6639953  movzx eax,byte ptr [rax+0x7E5]  ; R state+0x7E5 -> AL, zero-extended
//   0x663995a  jmp short 0x663999C     ; return AL
//
//   0x663995c  mov rax,[rsi]           ; R self+0x0 (vtable pointer, reloaded) -- before call #2
//   0x663995f  mov rax,[rax+0x228]     ; R vtable+0x228 (slot 69 function pointer) -> RAX
//   0x6639966  mov rcx,rsi             ; RCX = self (call #2 argument)
//   0x6639969  call qword ptr [0xF99FFA0]  ; call #2 -> sub_eea6040 via data slot 0xF99FFA0;
//   0xEEA6040  jmp rax                   ; tail-calls RAX (= vtable+0x228 target), RCX = self
//   0x663996f  mov ecx,eax             ; ECX = full call #2 result
//   0x6639971  mov al,3                ; default return (EAX upper bits preserved)
//   0x6639973  test cl,cl              ; call #2 result low byte == 0?
//   0x6639975  je short 0x663999C      ; if zero: return EAX
//   0x6639977  mov rcx,[rsi+0x278]     ; R self+0x278 (pointer)
//   0x663997e  test rcx,rcx
//   0x6639981  je short 0x663999C      ; if null: return EAX
//   0x6639983  mov ecx,[rcx+0x180]     ; R pointee+0x180 (int32_t)
//   0x6639989  xor eax,eax
//   0x663998b  cmp ecx,2
//   0x663998e  sete al                 ; AL = (v == 2)
//   0x6639991  lea eax,[rax+rax*2]     ; EAX = AL*3
//   0x6639994  add eax,3               ; EAX = AL*3+3 (v==2 -> 6, else 3)
//   0x6639997  test ecx,ecx
//   0x6639999  cmove eax,ecx           ; if v == 0: EAX = ECX = 0
//   0x663999c  add rsp,0x20            ; epilogue
//   0x66399a0  pop rsi
//   0x66399a1  ret                    ; return EAX
//
// Behavior: int32_t sub_6639930(BgfxFrameBuilder* self):
//   r1 = (*self->vtable+0x230)(self);         [call #1 via sub_eea6040 trampoline]
//   if ((r1 & 0xFF) != 0) return *(uint8_t*)(self->state0x358 + 0x7E5);
//   r2 = (*self->vtable+0x228)(self);         [call #2 via sub_eea6040 trampoline]
//   eax = (r2 & ~0xFF) | 3;
//   if ((r2 & 0xFF) == 0) return eax;
//   p = self->field0x278;  if (p == 0) return eax;
//   v = *(int32_t*)(p + 0x180);
//   return v == 0 ? 0 : (v == 2 ? 6 : 3);
// Same reads (self+0x0 twice, vtable+0x230, vtable+0x228, self+0x358, state+0x7E5,
// self+0x278, pointee+0x180), same writes (none), same calls in the same order (two,
// both through data slot 0xF99FFA0 -> sub_eea6040, modeled as the jmp-rax trampoline's
// net effect: indirect calls through the vtable pointers loaded just before each call,
// with RCX = self -- identical target, argument, return), same return (EAX). No null
// guard, no SEH in the original; none added here. Callee vtable targets are not
// statically known [I] (virtual calls) -- same as sibling unit sub_66399b0.
//
// x64 Microsoft ABI: RCX = self (BgfxFrameBuilder*), return EAX = int32_t.
//
// Calls: two calls, both `call qword ptr [0xF99FFA0]` (0x6639942 and 0x6639969),
// target sub_eea6040 (boundary: vendor) [V: docs/data/native_boundary.tsv line 506],
// loader-resolved thunk `jmp rax` [V: dis 0xeea6040]. Absent from Sigs.json; the lifted
// code performs each call's net effect directly (same convention as sub_66399b0).

static constexpr std::size_t kBgfxFrameBuilderOffsetField0x278 = 0x278;
static constexpr std::size_t kBgfxFrameBuilderOffsetState0x358 = 0x358;
static constexpr std::size_t kVtableSlotByteOffset0x230 = 0x230;
static constexpr std::size_t kVtableSlotByteOffset0x228 = 0x228;
static constexpr std::size_t kStateOffsetByte0x7E5 = 0x7E5;
static constexpr std::size_t kField0x278PointeeOffsetValue0x180 = 0x180;

// Layout mirrors what the function touches. Everything before self+0x278 is padding;
// offset 0 is the vtable pointer, read raw.
struct BgfxFrameBuilder {
    std::uint8_t pad0x00[0x278];
    const void* field0x278;  // pointer read at 0x6639977 mov rcx,[rsi+0x278]
    std::uint8_t pad0x280[0x358 - 0x280];
    const void* state0x358;  // state object pointer (R at 0x663994c mov rax,[rsi+0x358])
};
static_assert(offsetof(BgfxFrameBuilder, field0x278) == kBgfxFrameBuilderOffsetField0x278,
              "sub_6639930: self+0x278 is the pointer field (R, 0x6639977)");
static_assert(offsetof(BgfxFrameBuilder, state0x358) == kBgfxFrameBuilderOffsetState0x358,
              "sub_6639930: self+0x358 is the state pointer field (R, 0x663994c)");

// Pointee of self+0x278: int32_t field at +0x180, read at 0x6639983 mov ecx,[rcx+0x180].
struct Field0x278Pointee {
    std::uint8_t pad0x00[0x180];
    std::int32_t value0x180;
};
static_assert(offsetof(Field0x278Pointee, value0x180) == kField0x278PointeeOffsetValue0x180,
              "sub_6639930: pointee+0x180 is the int32_t selector field (R, 0x6639983)");

// State object pointed to by self+0x358: byte at +0x7E5, read at
// 0x6639953 movzx eax,byte ptr [rax+0x7E5].
struct BuilderState {
    std::uint8_t pad0x00[0x7E5];
    std::uint8_t byte0x7E5;
};
static_assert(offsetof(BuilderState, byte0x7E5) == kStateOffsetByte0x7E5,
              "sub_6639930: state+0x7E5 is the returned byte field (R, 0x6639953)");

namespace native {

// Exact x64 Microsoft ABI mirror of the original function.
int32_t sub_6639930(BgfxFrameBuilder* self);

} // namespace native
