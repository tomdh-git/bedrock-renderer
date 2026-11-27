#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/native/helpers/sub_4dfb570.h"

// sub_668eb10 (0x668eb10, size 0xce, 1.26.62.01): RenderCubemapDescription ctor (texture ref, mat4, u16, u8).
// Body [0x668eb10, 0x668ebde):
//   0x668eb10  push rsi
//   0x668eb11  push rdi
//   0x668eb12  push rbp
//   0x668eb13  push rbx
//   0x668eb14  sub rsp,0x28
//   0x668eb18  mov esi,r9d                    ; a3 = u16
//   0x668eb1b  mov rbx,r8                     ; a2 = mat4 ptr (const float[16])
//   0x668eb1e  mov rdi,rcx                    ; a0 = RenderCubemapDescription* (this / out slot)
//   0x668eb21  movzx ebp,byte ptr [rsp+0x70]  ; a4 = u8 (5th stack arg)
//   0x668eb26  call 0x4DFB570                 ; resolve texture: rcx=a0 (out slot), rdx=a1 (handle)
//   0x668eb2b..0x668ebc5   16x movss [rdi+0x10..0x4C] = [rbx+0x00..0x3C]  ; copy mat4
//   0x668ebca  mov [rdi+0x50],si              ; write u16 a3
//   0x668ebce  mov [rdi+0x52],bpl             ; write u8 a4
//   0x668ebd2  mov rax,rdi                    ; return a0
//   0x668ebd5  add rsp,0x28
//   0x668ebd9  pop rbx
//   0x668ebda  pop rbp
//   0x668ebdb  pop rdi
//   0x668ebdc  pop rsi
//   0x668ebdd  ret
// Calls: 0x4DFB570 sub_4dfb570 (lift set, native::helpers::sub_4dfb570). [V: rdis dis 0x668eb10 0xce]
//
// Layout of the RenderCubemapDescription object as walked by this function:
//   +0x00 void*  texture ptr      (written by sub_4dfb570 via the out slot)
//   +0x08 void*  texture ctrl     (written by sub_4dfb570 via the out slot)
//   +0x10 float  mat4[0]
//   +0x14 float  mat4[1]
//   ...
//   +0x4C float  mat4[15]
//   +0x50 u16    field
//   +0x52 u8     field
namespace native {

struct sub_668eb10Layout {
    // Out slot written by sub_4dfb570: [a0+0x00] texture ptr  [V: sub_4dfb570 writes out+0x00 ptr]
    static constexpr std::size_t kTexPtrOff = 0x00;
    // Out slot written by sub_4dfb570: [a0+0x08] texture ctrl  [V: sub_4dfb570 writes out+0x08 ctrl]
    static constexpr std::size_t kTexCtrlOff = 0x08;
    // Mat4 first element: [rdi+0x10]  [V: 0x668eb2b movss [rdi+0x10],xmm0]
    static constexpr std::size_t kMat4Off = 0x10;
    // u16 field: [rdi+0x50]  [V: 0x668ebca mov [rdi+0x50],si]
    static constexpr std::size_t kU16Off = 0x50;
    // u8 field: [rdi+0x52]  [V: 0x668ebce mov [rdi+0x52],bpl]
    static constexpr std::size_t kU8Off = 0x52;

    static_assert(kTexPtrOff == 0x00, "sub_668eb10: out slot ptr at +0x00");
    static_assert(kTexCtrlOff == 0x08, "sub_668eb10: out slot ctrl at +0x08");
    static_assert(kMat4Off == 0x10, "sub_668eb10: mat4 at +0x10");
    static_assert(kU16Off == 0x50, "sub_668eb10: u16 at +0x50");
    static_assert(kU8Off == 0x52, "sub_668eb10: u8 at +0x52");
    static_assert(sizeof(void*) == 8, "sub_668eb10: x64 ABI");
};

// Signature of the original: x64 Microsoft ABI.
//   rcx = a0 RenderCubemapDescription* (this / out slot passed to sub_4dfb570)
//   rdx = a1 const sub_4dfb570_handle* (texture ref/handle)
//   r8  = a2 const float* (mat4, 16 floats)
//   r9d = a3 std::uint16_t
//   [rsp+0x70] = a4 std::uint8_t (5th stack argument)
// Return: rax = a0 (RenderCubemapDescription*)
class RenderCubemapDescription;

RenderCubemapDescription* sub_668eb10(RenderCubemapDescription* a0,
                                      const native::helpers::sub_4dfb570_handle* a1,
                                      const float* a2,
                                      std::uint16_t a3,
                                      std::uint8_t a4);

} // namespace native
