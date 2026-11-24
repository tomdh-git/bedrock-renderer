// LIFT 0xe86d770 size 0x7d 1.26.62.01 sub_e86d770
#include "sub_e86d770.h"
static_assert(sizeof(void*) == 8, "ptr");

#if 0
0xe86d770  push rsi
0xe86d771  movzx eax,byte ptr [rcx]
0xe86d774  dec al
0xe86d776  xor r9d,r9d
0xe86d779  mov r10d,0
0xe86d77f  cmp al,7
0xe86d781  ja short 0xE86D791
0xe86d783  movzx eax,al
0xe86d786  lea r10,[0xF491060]
0xe86d78d  mov r10d,[r10+rax*4]
0xe86d791  mov eax,[rcx+0xC]
0xe86d794  cmp rax,7
0xe86d798  ja short 0xE86D7A5
0xe86d79a  lea r9,[0xF4F0120]
0xe86d7a1  mov r9d,[r9+rax*4]
0xe86d7a5  mov esi,[rcx+4]
0xe86d7a8  xor r11d,r11d
0xe86d7ab  mov eax,0
0xe86d7b0  cmp rsi,7
0xe86d7b4  ja short 0xE86D7C0
0xe86d7b6  lea rax,[0xF4F0140]
0xe86d7bd  mov eax,[rax+rsi*4]
0xe86d7c0  mov ecx,[rcx+8]
0xe86d7c3  cmp rcx,7
0xe86d7c7  ja short 0xE86D7D4
0xe86d7c9  lea r11,[0xF4F0160]
0xe86d7d0  mov r11d,[r11+rcx*4]
0xe86d7d4  movzx ecx,r8b
0xe86d7d8  shl ecx,8
0xe86d7db  movzx edx,dl
0xe86d7de  or edx,ecx
0xe86d7e0  or r9d,r10d
0xe86d7e3  or eax,r9d
0xe86d7e6  or eax,edx
0xe86d7e8  or eax,r11d
0xe86d7eb  pop rsi
0xe86d7ec  ret
#endif

namespace native::d3d12 {

extern "C" std::uint32_t sub_e86d770(const StencilFaceDesc* desc, std::uint8_t a2, std::uint8_t a3) {
    // 0xe86d770..0xe86d774
    std::uint8_t al = desc->op0;
    al -= 1;
    // 0xe86d776..0xe86d779
    std::uint32_t r9d = 0;
    std::uint32_t r10d = 0;
    // 0xe86d77f..0xe86d791
    if (al <= 7) {
        r10d = *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const char*>(0xF491060) + (std::uint32_t)al * 4);
    }
    // 0xe86d791..0xe86d7a5
    std::uint32_t v3 = desc->v3;
    if (v3 <= 7) {
        r9d = *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const char*>(0xF4F0120) + v3 * 4);
    }
    // 0xe86d7a5..0xe86d7c0
    std::uint32_t v1 = desc->v1;
    std::uint32_t r11d = 0;
    std::uint32_t eax = 0;
    if (v1 <= 7) {
        eax = *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const char*>(0xF4F0140) + v1 * 4);
    }
    // 0xe86d7c0..0xe86d7d4
    std::uint32_t v2 = desc->v2;
    if (v2 <= 7) {
        r11d = *reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const char*>(0xF4F0160) + v2 * 4);
    }
    // 0xe86d7d4..0xe86d7ec
    std::uint32_t ecx = a3;
    ecx <<= 8;
    std::uint32_t edx = a2;
    edx |= ecx;
    r9d |= r10d;
    eax |= r9d;
    eax |= edx;
    eax |= r11d;
    return eax;
}

// Calls out of lifted code: none. 0xe86d770..0xe86d7ec has zero call instructions.
// UNRESOLVED CALL = none

LIFT_FN(sub_e86d770, "sub_e86d770", 0xe86d770, sub_e86d770, nullptr);

} // namespace native::d3d12