#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_66399b0 (0x66399b0, size 0x34, 1.26.62.01, "BgfxFrameBuilder slot 91").
//
// Reversed from the exe listing (rdis dis 0x66399b0 0x34); every offset below is a read
// performed by an instruction of the function, cited by address.
//
//   0x66399b8  mov rax,[rcx]           ; R self+0x0  (vtable pointer)
//   0x66399bb  mov rax,[rax+0x230]     ; R vtable+0x230 (function pointer, ends up in RAX)
//   0x66399c2  call qword ptr [0xF99FFA0]  ; -> sub_eea6040 [V boundary: vendor,
//       docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0
//       (loader-resolved)"]. sub_eea6040 body [V]: `0xEEA6040  jmp rax` — tail-calls RAX
//       (= vtable+0x230 target) with RCX = self; result returns in AL.
//   0x66399c8  mov ecx,eax             ; call result -> ECX
//   0x66399ca  mov al,2                ; default return value
//   0x66399cc  test cl,cl              ; call result == 0?
//   0x66399ce  je short 0x66399DE      ; if zero: return 2
//   0x66399d0  mov rax,[rsi+0x358]     ; R self+0x358 (state object pointer, RSI = self)
//   0x66399d7  movzx eax,byte ptr [rax+0x7E6]  ; R state+0x7E6 -> AL
//   0x66399de  add rsp,0x20            ; epilogue
//   0x66399e2  pop rsi
//   0x66399e3  ret                    ; return AL
//
// Behavior: uint8_t sub_66399b0(BgfxFrameBuilder* self):
//   if (vtable[0x230](self) != 0) return *(uint8_t*)(self->state0x358 + 0x7E6);
//   return 2;
// Same reads (vtable pointer, vtable+0x230, self+0x358, state+0x7E6), same writes (none),
// same calls in the same order (one), same return (AL). No null guard, no SEH, one branch;
// none added here.
//
// x64 Microsoft ABI: RCX = self (BgfxFrameBuilder*), return AL = uint8_t.
//
// Calls: one call, at 0x66399c2 `call qword ptr [0xF99FFA0]`, target sub_eea6040
// (boundary: vendor), resolved through data slot 0xF99FFA0; sub_eea6040 is loader-resolved
// and absent from Sigs.json, so it is not called through native::Boundary. The lifted code
// performs the trampoline's net effect directly: an indirect call through the vtable+0x230
// function pointer with RCX = self — identical target, identical argument, identical return.

static constexpr std::size_t kBgfxFrameBuilderOffsetState0x358 = 0x358;
static constexpr std::size_t kVtableSlotByteOffset0x230 = 0x230;
static constexpr std::size_t kStateOffsetByte0x7E6 = 0x7E6;

// Layout mirrors what the function touches. Only offsets used by the function are members;
// everything before self+0x358 is padding (offset 0 is the vtable pointer, read raw).
struct BgfxFrameBuilder {
    std::uint8_t pad0x00[0x358];
    const void* state0x358;  // state object pointer (R at 0x66399d0 mov rax,[rsi+0x358])
};
static_assert(offsetof(BgfxFrameBuilder, state0x358) == kBgfxFrameBuilderOffsetState0x358,
              "sub_66399b0: self+0x358 is the state pointer field (R, 0x66399d0)");

struct BuilderState {
    std::uint8_t pad0x00[0x7E6];
    std::uint8_t byte0x7E6;  // returned when the trampoline call yields non-zero (R at 0x66399d7)
};
static_assert(offsetof(BuilderState, byte0x7E6) == kStateOffsetByte0x7E6,
              "sub_66399b0: state+0x7E6 is the returned byte field (R, 0x66399d7)");

namespace native {

// Exact x64 Microsoft ABI mirror of the original function.
uint8_t sub_66399b0(BgfxFrameBuilder* self);

} // namespace native
