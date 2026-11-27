// LIFT 0x668eb10 size 0xce 1.26.62.01 RenderCubemapDescription ctor (texture ref, mat4, u16, u8)
#include "sub_668eb10.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

// Layout assertions (constants defined in sub_668eb10.h):
static_assert(native::sub_668eb10Layout::kTexPtrOff == 0x00, "sub_668eb10: tex ptr at +0x00");
static_assert(native::sub_668eb10Layout::kTexCtrlOff == 0x08, "sub_668eb10: tex ctrl at +0x08");
static_assert(native::sub_668eb10Layout::kMat4Off == 0x10, "sub_668eb10: mat4 at +0x10");
static_assert(native::sub_668eb10Layout::kU16Off == 0x50, "sub_668eb10: u16 at +0x50");
static_assert(native::sub_668eb10Layout::kU8Off == 0x52, "sub_668eb10: u8 at +0x52");

#if 0
// Verbatim instructions of sub_668eb10 ([0x668eb10, 0x668ebde), size 0xce):
0x668eb10  push rsi
0x668eb11  push rdi
0x668eb12  push rbp
0x668eb13  push rbx
0x668eb14  sub rsp,0x28
0x668eb18  mov esi,r9d
0x668eb1b  mov rbx,r8
0x668eb1e  mov rdi,rcx
0x668eb21  movzx ebp,byte ptr [rsp+0x70]
0x668eb26  call 0x4DFB570
0x668eb2b  movss xmm0,[rbx]
0x668eb2f  movss [rdi+0x10],xmm0
0x668eb34  movss xmm0,[rbx+4]
0x668eb39  movss [rdi+0x14],xmm0
0x668eb3e  movss xmm0,[rbx+8]
0x668eb43  movss [rdi+0x18],xmm0
0x668eb48  movss xmm0,[rbx+0xC]
0x668eb4d  movss [rdi+0x1C],xmm0
0x668eb52  movss xmm0,[rbx+0x10]
0x668eb57  movss [rdi+0x20],xmm0
0x668eb5c  movss xmm0,[rbx+0x14]
0x668eb61  movss [rdi+0x24],xmm0
0x668eb66  movss xmm0,[rbx+0x18]
0x668eb6b  movss [rdi+0x28],xmm0
0x668eb70  movss xmm0,[rbx+0x1C]
0x668eb75  movss [rdi+0x2C],xmm0
0x668eb7a  movss xmm0,[rbx+0x20]
0x668eb7f  movss [rdi+0x30],xmm0
0x668eb84  movss xmm0,[rbx+0x24]
0x668eb89  movss [rdi+0x34],xmm0
0x668eb8e  movss xmm0,[rbx+0x28]
0x668eb93  movss [rdi+0x38],xmm0
0x668eb98  movss xmm0,[rbx+0x2C]
0x668eb9d  movss [rdi+0x3C],xmm0
0x668eba2  movss xmm0,[rbx+0x30]
0x668eba7  movss [rdi+0x40],xmm0
0x668ebac  movss xmm0,[rbx+0x34]
0x668ebb1  movss [rdi+0x44],xmm0
0x668ebb6  movss xmm0,[rbx+0x38]
0x668ebbb  movss [rdi+0x48],xmm0
0x668ebc0  movss xmm0,[rbx+0x3C]
0x668ebc5  movss [rdi+0x4C],xmm0
0x668ebca  mov [rdi+0x50],si
0x668ebce  mov [rdi+0x52],bpl
0x668ebd2  mov rax,rdi
0x668ebd5  add rsp,0x28
0x668ebd9  pop rbx
0x668ebda  pop rbp
0x668ebdb  pop rdi
0x668ebdc  pop rsi
0x668ebdd  ret
#endif

namespace native {

// Forward declaration: sub_4dfb570 is in the lift set (lifted by its own unit,
// docs/data/native_boundary.tsv line 246: class=lift).
//   sub_4dfb570_out* sub_4dfb570(sub_4dfb570_out* out, const sub_4dfb570_handle* h);
//   Called here with rcx = a0 (out slot), rdx = a1 (handle); return value ignored
//   because the caller returns a0 itself. [V: rdis dis 0x668eb10 0xce]

RenderCubemapDescription* sub_668eb10(RenderCubemapDescription* a0,
                                      const native::helpers::sub_4dfb570_handle* a1,
                                      const float* a2,
                                      std::uint16_t a3,
                                      std::uint8_t a4)
{
    // 0x668eb10..0x668eb18: prologue (push rsi,rdi,rbp,rbx; sub rsp,0x28)
    // 0x668eb18..0x668eb1b: mov esi,r9d        (a3 -> esi)
    // 0x668eb1b..0x668eb1e: mov rbx,r8         (a2 -> rbx)
    // 0x668eb1e..0x668eb21: mov rdi,rcx        (a0 -> rdi)
    // 0x668eb21..0x668eb26: movzx ebp,byte ptr [rsp+0x70]  (a4 -> bpl)
    // 0x668eb26  call 0x4DFB570
    native::helpers::sub_4dfb570(reinterpret_cast<native::helpers::sub_4dfb570_out*>(a0), a1);
    // 0x668eb2b..0x668eb2f: movss xmm0,[rbx]        ;  0x668eb2b  movss xmm0,[rbx]
    // 0x668eb2f..0x668eb34: movss [rdi+0x10],xmm0   ;  0x668eb2f  movss [rdi+0x10],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off)[0] = a2[0];
    // 0x668eb34..0x668eb39: movss xmm0,[rbx+4]      ;  0x668eb34  movss xmm0,[rbx+4]
    // 0x668eb39..0x668eb3e: movss [rdi+0x14],xmm0   ;  0x668eb39  movss [rdi+0x14],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 4)[0] = a2[1];
    // 0x668eb3e..0x668eb43: movss xmm0,[rbx+8]      ;  0x668eb3e  movss xmm0,[rbx+8]
    // 0x668eb43..0x668eb48: movss [rdi+0x18],xmm0   ;  0x668eb43  movss [rdi+0x18],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 8)[0] = a2[2];
    // 0x668eb48..0x668eb4d: movss xmm0,[rbx+0xC]    ;  0x668eb48  movss xmm0,[rbx+0xC]
    // 0x668eb4d..0x668eb52: movss [rdi+0x1C],xmm0   ;  0x668eb4d  movss [rdi+0x1C],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0xC)[0] = a2[3];
    // 0x668eb52..0x668eb57: movss xmm0,[rbx+0x10]   ;  0x668eb52  movss xmm0,[rbx+0x10]
    // 0x668eb57..0x668eb5c: movss [rdi+0x20],xmm0   ;  0x668eb57  movss [rdi+0x20],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x10)[0] = a2[4];
    // 0x668eb5c..0x668eb61: movss xmm0,[rbx+0x14]   ;  0x668eb5c  movss xmm0,[rbx+0x14]
    // 0x668eb61..0x668eb66: movss [rdi+0x24],xmm0   ;  0x668eb61  movss [rdi+0x24],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x14)[0] = a2[5];
    // 0x668eb66..0x668eb6b: movss xmm0,[rbx+0x18]   ;  0x668eb66  movss xmm0,[rbx+0x18]
    // 0x668eb6b..0x668eb70: movss [rdi+0x28],xmm0   ;  0x668eb6b  movss [rdi+0x28],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x18)[0] = a2[6];
    // 0x668eb70..0x668eb75: movss xmm0,[rbx+0x1C]   ;  0x668eb70  movss xmm0,[rbx+0x1C]
    // 0x668eb75..0x668eb7a: movss [rdi+0x2C],xmm0   ;  0x668eb75  movss [rdi+0x2C],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x1C)[0] = a2[7];
    // 0x668eb7a..0x668eb7f: movss xmm0,[rbx+0x20]   ;  0x668eb7a  movss xmm0,[rbx+0x20]
    // 0x668eb7f..0x668eb84: movss [rdi+0x30],xmm0   ;  0x668eb7f  movss [rdi+0x30],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x20)[0] = a2[8];
    // 0x668eb84..0x668eb89: movss xmm0,[rbx+0x24]   ;  0x668eb84  movss xmm0,[rbx+0x24]
    // 0x668eb89..0x668eb8e: movss [rdi+0x34],xmm0   ;  0x668eb89  movss [rdi+0x34],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x24)[0] = a2[9];
    // 0x668eb8e..0x668eb93: movss xmm0,[rbx+0x28]   ;  0x668eb8e  movss xmm0,[rbx+0x28]
    // 0x668eb93..0x668eb98: movss [rdi+0x38],xmm0   ;  0x668eb93  movss [rdi+0x38],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x28)[0] = a2[10];
    // 0x668eb98..0x668eb9d: movss xmm0,[rbx+0x2C]   ;  0x668eb98  movss xmm0,[rbx+0x2C]
    // 0x668eb9d..0x668eba2: movss [rdi+0x3C],xmm0   ;  0x668eb9d  movss [rdi+0x3C],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x2C)[0] = a2[11];
    // 0x668eba2..0x668eba7: movss xmm0,[rbx+0x30]   ;  0x668eba2  movss xmm0,[rbx+0x30]
    // 0x668eba7..0x668ebac: movss [rdi+0x40],xmm0   ;  0x668eba7  movss [rdi+0x40],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x30)[0] = a2[12];
    // 0x668ebac..0x668ebb1: movss xmm0,[rbx+0x34]   ;  0x668ebac  movss xmm0,[rbx+0x34]
    // 0x668ebb1..0x668ebb6: movss [rdi+0x44],xmm0   ;  0x668ebb1  movss [rdi+0x44],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x34)[0] = a2[13];
    // 0x668ebb6..0x668ebbb: movss xmm0,[rbx+0x38]   ;  0x668ebb6  movss xmm0,[rbx+0x38]
    // 0x668ebbb..0x668ebc0: movss [rdi+0x48],xmm0   ;  0x668ebbb  movss [rdi+0x48],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x38)[0] = a2[14];
    // 0x668ebc0..0x668ebc5: movss xmm0,[rbx+0x3C]   ;  0x668ebc0  movss xmm0,[rbx+0x3C]
    // 0x668ebc5..0x668ebca: movss [rdi+0x4C],xmm0   ;  0x668ebc5  movss [rdi+0x4C],xmm0
    reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kMat4Off + 0x3C)[0] = a2[15];
    // 0x668ebca..0x668ebce: mov [rdi+0x50],si       ;  0x668ebca  mov [rdi+0x50],si
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kU16Off) = a3;
    // 0x668ebce..0x668ebd2: mov [rdi+0x52],bpl      ;  0x668ebce  mov [rdi+0x52],bpl
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(a0) + sub_668eb10Layout::kU8Off) = a4;
    // 0x668ebd2..0x668ebd5: mov rax,rdi             ;  0x668ebd2  mov rax,rdi
    // 0x668ebd5..0x668ebdd: epilogue + ret
    return a0;
}

LIFT_FN(sub_668eb10, "RenderCubemapDescription ctor", 0x668eb10, native::sub_668eb10, nullptr);

} // namespace native
