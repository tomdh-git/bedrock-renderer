#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_66399f0 (0x66399f0, size 0x64, 1.26.62.01, "BgfxFrameBuilder slot 92").
//
// Reversed from the exe listing (rdis dis 0x66399f0 0x64); every offset below is a read
// performed by an instruction of the function, cited by address.
//
//   0x66399f0  push rsi                                   ; prologue (callee-saved)
//   0x66399f1  sub rsp,0x20                               ; stack frame
//   0x66399f5  mov rsi,rcx                                ; self -> RSI
//   0x66399f8  mov rax,[rcx]                              ; R self+0x0 (vtable pointer)
//   0x66399fb  mov rax,[rax+0x230]                        ; R vtable+0x230 -> RAX
//   0x6639a02  call qword ptr [0xF99FFA0]                 ; -> sub_eea6040 [V boundary:
//       vendor; docs/data/native_boundary.tsv row "0xeea6040 vendor thunk via data slot
//       0xF99FFA0 (loader-resolved)"]. sub_eea6040 is a loader-resolved trampoline: its
//       net effect is an indirect call through RAX (= vtable+0x230 target) with RCX =
//       self; result returns in AL.
//   0x6639a08  test al,al                                 ; first call result == 0?
//   0x6639a0a  je short 0x6639A1C                         ; if zero, perform second call
//   0x6639a0c  mov rax,[rsi+0x358]                        ; R self+0x358 (state pointer)
//   0x6639a13  movzx eax,byte ptr [rax+0x7E4]             ; R state+0x7E4 -> AL
//   0x6639a1a  jmp short 0x6639A4E                        ; return AL
//   0x6639a1c  mov rax,[rsi]                              ; R self+0x0 (vtable pointer)
//   0x6639a1f  mov rax,[rax+0x228]                        ; R vtable+0x228 -> RAX
//   0x6639a26  mov rcx,rsi                                ; RCX = self
//   0x6639a29  call qword ptr [0xF99FFA0]                 ; -> sub_eea6040 (see above)
//   0x6639a2f  mov ecx,eax                                ; second call result -> ECX
//   0x6639a31  mov al,1                                   ; default return 1
//   0x6639a33  test cl,cl                                 ; second call result == 0?
//   0x6639a35  je short 0x6639A4E                         ; if zero, return 1
//   0x6639a37  mov rcx,[rsi+0x278]                        ; R self+0x278 (pointer)
//   0x6639a3e  test rcx,rcx                               ; pointer == 0?
//   0x6639a41  je short 0x6639A4E                         ; if null, return 1
//   0x6639a43  cmp dword ptr [rcx+0x184],1                ; R *(rcx+0x184) vs 1
//   0x6639a4a  mov al,2                                   ; default 2
//   0x6639a4c  sbb al,0                                   ; AL = 2 - CF; CF=1 iff dword == 0
//   0x6639a4e  add rsp,0x20                               ; epilogue
//   0x6639a52  pop rsi
//   0x6639a53  ret                                       ; return AL
//
// Behavior: uint8_t sub_66399f0(BgfxFrameBuilder* self):
//   uint8_t r1 = <vtable+0x230 target>(self);             // via sub_eea6040 trampoline
//   if (r1 != 0) return *(uint8_t*)(self->state0x358 + 0x7E4);
//   uint8_t r2 = <vtable+0x228 target>(self);
//   if (r2 == 0) return 1;
//   if (self->field0x278 == nullptr) return 1;
//   return (*(uint32_t*)(self->field0x278 + 0x184) == 0) ? 1 : 2;
// Same reads (self+0x0 twice, vtable+0x230, vtable+0x228, self+0x358, state+0x7E4,
// self+0x278, *(self+0x278)+0x184), same writes (none outside the stack frame), same
// calls in the same order (two, both sub_eea6040 through data slot 0xF99FFA0), same
// return (AL). No null guard, no SEH; branches mirror the original jccs exactly.
//
// x64 Microsoft ABI: RCX = self (BgfxFrameBuilder*), return AL = uint8_t.
//
// Calls: two, both `call qword ptr [0xF99FFA0]` (0x6639a02 and 0x6639a29), target
// sub_eea6040 (boundary: vendor), loader-resolved through data slot 0xF99FFA0 and absent
// from Sigs.json, so not called through native::Boundary. The lifted code performs each
// trampoline's net effect directly: an indirect call through the loaded vtable-slot
// function pointer with RCX = self — identical target, identical argument, identical return.

static constexpr std::size_t kBgfxFrameBuilderOffsetState0x358 = 0x358;
static constexpr std::size_t kBgfxFrameBuilderOffsetField0x278 = 0x278;
static constexpr std::size_t kVtableSlotByteOffset0x230 = 0x230;
static constexpr std::size_t kVtableSlotByteOffset0x228 = 0x228;
static constexpr std::size_t kStateOffsetByte0x7E4 = 0x7E4;
static constexpr std::size_t kField0x278ObjDword0x184 = 0x184;

// Layout mirrors what the function touches. Offsets are not sorted by declaration order:
// self+0x278 is declared before self+0x358 because that is the layout in the exe.
struct BgfxFrameBuilder {
    std::uint8_t pad0x00[0x278];
    void* field0x278;  // pointer object, read at 0x6639a37 mov rcx,[rsi+0x278]
    std::uint8_t pad0x280[0x358 - 0x280];
    const void* state0x358;  // state object pointer, read at 0x6639a0c mov rax,[rsi+0x358]
};
static_assert(offsetof(BgfxFrameBuilder, field0x278) == kBgfxFrameBuilderOffsetField0x278,
              "sub_66399f0: self+0x278 is the pointer field (R, 0x6639a37)");
static_assert(offsetof(BgfxFrameBuilder, state0x358) == kBgfxFrameBuilderOffsetState0x358,
              "sub_66399f0: self+0x358 is the state pointer field (R, 0x6639a0c)");

struct BuilderState {
    std::uint8_t pad0x00[0x7E4];
    std::uint8_t byte0x7E4;  // returned when the first trampoline call yields non-zero (R at 0x6639a13)
};
static_assert(offsetof(BuilderState, byte0x7E4) == kStateOffsetByte0x7E4,
              "sub_66399f0: state+0x7E4 is the returned byte field (R, 0x6639a13)");

struct Field0x278Object {
    std::uint8_t pad0x00[0x184];
    std::uint32_t dword0x184;  // compared with 1 at 0x6639a43 cmp dword ptr [rcx+0x184],1
};
static_assert(offsetof(Field0x278Object, dword0x184) == kField0x278ObjDword0x184,
              "sub_66399f0: *(self+0x278)+0x184 is the compared dword field (R, 0x6639a43)");

namespace native {

// Exact x64 Microsoft ABI mirror of the original function.
uint8_t sub_66399f0(BgfxFrameBuilder* self);

} // namespace native
