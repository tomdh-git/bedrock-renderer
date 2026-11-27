// LIFT 0xbcbe100 size 0x140 1.26.62.01 sub_bcbe100

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcbe100.h"
#include "client/features/render/native/bgfx/sub_bcbe410.h"

#include <cstdint>
#include <intrin.h>

static_assert(sizeof(void*) == 8, "x64 ABI");

namespace native::bgfx {

void sub_bcbe100(uint32_t* out, const void* a1) {
    // 0xbcbe100..0xbcbe110

    // 0xbcbe100  push r15

    // 0xbcbe102  push r14

    // 0xbcbe104  push r13

    // 0xbcbe106  push r12

    // 0xbcbe108  push rsi

    // 0xbcbe109  push rdi

    // 0xbcbe10a  push rbp

    // 0xbcbe10b  push rbx

    // 0xbcbe10c  sub rsp,0x28

    const unsigned char* src = reinterpret_cast<const unsigned char*>(a1);
    // r9 = [a1+0x10]

    uint64_t r9 = *reinterpret_cast<const uint64_t*>(static_cast<const unsigned char*>(a1) + 0x10);
    // rdx pointer selection

    const unsigned char* rdx;
    if (*reinterpret_cast<const uint64_t*>(static_cast<const unsigned char*>(a1) + 0x18) >= 0x10) {
        // 0xbcbe11e  mov rdx,[rdx]

        rdx = *reinterpret_cast<const unsigned char* const*>(a1);
    } else {
        rdx = static_cast<const unsigned char*>(a1);
    }
    // 0xbcbe121  cmp r9,0xF

    if (r9 >= 0xF) {
        // 0xbcbe127  mov ecx,0xE

        uint64_t rcx = 0xE;
        // 0xbcbe130 loop

        for (; rcx < r9; ++rcx) {
            // 0xbcbe130  movzx r8d,byte ptr [rdx+rcx]

            unsigned char r8b = rdx[rcx];
            // 0xbcbe135  and r8b,0xFE

            r8b &= 0xFE;
            // 0xbcbe139  cmp r8b,0x30

            if (r8b != 0x30) {
                // 0xbcbe23a  call 0xBCBE410

    // 0xbcbe23f  int3

                native::bgfx::sub_bcbe410();
                __debugbreak();
                return;
            }
        }
        r9 = 0xE;
    } else if (r9 == 0) {
        // 0xbcbe223  xor r11d,r11d

        *out = 0;
        return;
    }
    // 0xbcbe15c

    const unsigned char* rdi = rdx + r9;
    const unsigned char* rsi = rdx + r9 - 1;
    uint64_t r10 = 0;
    uint32_t ebx = 0;
    // 0xbcbe16a loop

    while (true) {
        const unsigned char* r14 = rdi - 0x20;
        uint64_t r15 = r9 - 1;
        const unsigned char* r12 = rsi;
        uint64_t r8 = 0;
        uint32_t r11d = 0;
        // 0xbcbe180 loop

        while (true) {
            // 0xbcbe180  movzx r13d,byte ptr [r12]

            unsigned char r13b = *r12;
            uint32_t ebp = 0;
            // 0xbcbe187  cmp r13b,0x31

            if (r13b == 0x31) ebp = 1;
            // 0xbcbe192  shl ebp,cl  (cl = r8)

            ebp <<= (unsigned char)r8;
            // 0xbcbe194  and r13b,0xFE

            r13b &= 0xFE;
            // 0xbcbe198  cmp r13b,0x30

            if (r13b != 0x30) {
                native::bgfx::sub_bcbe410();
                __debugbreak();
                return;
            }
            r11d |= ebp;
            // 0xbcbe1a5  cmp r15,r8

            if (r15 == r8) {
                // 0xbcbe20c  mov r11d,ebp

                r11d = ebp;
                break;
            }
            // 0xbcbe1aa  movzx r13d,byte ptr [r12-1]

            r13b = r12[-1];
            uint32_t tmp = 0;
            if (r13b == 0x31) tmp = 1;
            // 0xbcbe1bb  lea ecx,[r8+1]

            unsigned char sh = (unsigned char)(r8 + 1);
            // 0xbcbe1bf  shl r11d,cl  (r11d here is tmp)

            tmp <<= sh;
            r13b &= 0xFE;
            if (r13b != 0x30) {
                native::bgfx::sub_bcbe410();
                __debugbreak();
                return;
            }
            r11d = tmp | (r11d & ~0u); // or r11d,ebp already done above? 

            // Actually: or r11d,ebp was: r11d |= ebp before; then r11d = (tmp<<sh) | ebp

            // redo carefully:

            r11d = tmp | ebp;
            // 0xbcbe1cf  cmp r8,0x1E

            if (r8 == 0x1E) {
                // 0xbcbe1f0

                ++r10;
                rsi -= 0x20;
                r9 -= 0x20;
                ebx = r11d;
                rdi = r14;
                if (rdx == r14) {
                    goto done;
                }
                break; // to outer while

            }
            r8 += 2;
            r12 -= 2;
            if (r9 == r8) {
                // 0xbcbe1e2  jmp short 0xBCBE20F

                break;
            }
        }
        // 0xbcbe20f

        uint32_t ecx = (rdi != rdx) ? 1 : 0;
        if (rdi == rdx) r11d = ebx;
        r10 += ecx;
        // 0xbcbe21e

        if (r10 != 0) break;
        // 0xbcbe223

        r11d = 0;
        break;
    }
done:
    // 0xbcbe226  mov [rax],r11d

    *out = r11d;
}

} // namespace native::bgfx


LIFT_FN(sub_bcbe100, "sub_bcbe100", 0xbcbe100, sub_bcbe100, nullptr);