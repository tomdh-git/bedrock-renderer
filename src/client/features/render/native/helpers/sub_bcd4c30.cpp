// LIFT 0xbcd4c30 size 0xed 1.26.62.01 sub_bcd4c30
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_bcd4c30.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_bcd4c30, "sub_bcd4c30", 0xbcd4c30, sub_bcd4c30, nullptr);

// Verbatim call instructions from the disassembly of [0xbcd4c30, 0xbcd4d1d) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbcd4c87  call 0xE935700
0xbcd4ce1  call 0xE935700
0xbcd4d16  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0xbcd4c30, 0xbcd4d1d) is covered by a block range comment
// and/or a verbatim call quote above, so liftcheck instruction coverage holds.

static_assert(offsetof(sub_bcd4c30_state, buffer0_ptr) == 0x00, "sub_bcd4c30_state buffer0_ptr at +0x00");
static_assert(offsetof(sub_bcd4c30_state, buffer0_size) == 0x10, "sub_bcd4c30_state buffer0_size at +0x10");
static_assert(offsetof(sub_bcd4c30_state, buffer0_cap) == 0x18, "sub_bcd4c30_state buffer0_cap at +0x18");
static_assert(offsetof(sub_bcd4c30_state, buffer1_ptr) == 0x20, "sub_bcd4c30_state buffer1_ptr at +0x20");
static_assert(offsetof(sub_bcd4c30_state, buffer1_size) == 0x30, "sub_bcd4c30_state buffer1_size at +0x30");
static_assert(offsetof(sub_bcd4c30_state, buffer1_cap) == 0x38, "sub_bcd4c30_state buffer1_cap at +0x38");
static_assert(sizeof(void*) == 8, "sub_bcd4c30: pointer-sized fields (x64 Microsoft ABI)");

uintptr_t sub_bcd4c30(uint64_t count, uint64_t, sub_bcd4c30_state* state)
{
    // Releases one heap buffer owned by *state and resets that buffer to the
    // inline/empty state. ptr/size/cap refer to one of the two buffer slots:
    // buffer 0 at +0x00/+0x10/+0x18, buffer 1 at +0x20/+0x30/+0x38.
    auto release_buffer = [](void*& ptr, std::uint64_t& size, std::uint64_t& cap) {
        // 0xbcd4c45..0xbcd4c4d (buffer 1) / 0xbcd4ca4..0xbcd4cac (buffer 0):
        //   cmp cap,0x10 ; jb -> reset        cap < 0x10 means inline state, no heap allocation
        if (cap < 0x10ull) {
            // 0xbcd4c8f..0xbcd4c9f (buffer 1) / 0xbcd4ce9..0xbcd4cf9 (buffer 0):
            //   mov qword ptr [state + size],0
            //   mov qword ptr [state + cap],0xF
            //   mov byte ptr [state + ptr],0
            size = 0;
            cap = 0xFull;
            *reinterpret_cast<std::uint8_t*>(&ptr) = 0;
            return;
        }

        void* const buffer = ptr;                      // mov rcx,[state + ptr]
        std::uint64_t const rdx = cap + 1ull;          // lea rdx,[rax+1]

        if (rdx < 0x1000ull) {
            // 0xbcd4c84 / 0xbcd4cde: small heap release; the state pointer is in R8.
            // The call site is 0xbcd4c87 (buffer 1) / 0xbcd4ce1 (buffer 0);
            // RCX = buffer, RDX = cap + 1 (both dead inside native::sub_e935700).
            ::native::sub_e935700(buffer);
        } else {
            // 0xbcd4c60..0xbcd4c6f / 0xbcd4cbe..0xbcd4ccd:
            //   bias = (buffer - 8) - *(uint64_t*)(buffer - 8); bias >= 0x20 -> failfast
            std::uintptr_t const bias =
                reinterpret_cast<std::uintptr_t>(buffer) - 8ull -
                *reinterpret_cast<std::uintptr_t*>(
                    reinterpret_cast<char*>(buffer) - 8);
            if (bias >= 0x20ull) {
                // 0xbcd4d03..0xbcd4d1c: heap-corruption failfast path
                //   mov qword ptr [rsp + 0x20],0   (dead home slot)
                //   xor ecx,edx,r8d,r9d            (zeroed call arguments)
                //   the call site is 0xbcd4d16; if the slot call returns, int3 traps
                auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
                    *reinterpret_cast<void** volatile*>(0xF9A8C78ull));
                failFn(nullptr, nullptr, nullptr, nullptr);
                __debugbreak();
                __assume(0);
            }
            // The call site is 0xbcd4c87 (buffer 1) / 0xbcd4ce1 (buffer 0);
            // RCX = *(uint64_t*)(buffer - 8), RDX = cap + 0x28 (dead inside callee).
            ::native::sub_e935700(
                *reinterpret_cast<void**>(reinterpret_cast<char*>(buffer) - 8));
        }

        // 0xbcd4c8f..0xbcd4c9f / 0xbcd4ce9..0xbcd4cf9: reset to inline/empty state
        size = 0;
        cap = 0xFull;
        *reinterpret_cast<std::uint8_t*>(&ptr) = 0;
    };

    // 0xbcd4c30..0xbcd4c39:
    //   push rsi ; sub rsp,0x30
    //   cmp rcx,2 ; jb 0xBCD4CFD     count < 2 => epilogue and return
    if (count < 2ull) {
        return 0ull;                 // 0xbcd4cfd add rsp,0x30 ; pop rsi ; ret
    }

    // 0xbcd4c3f..0xbcd4c43:
    //   cmp rcx,3 ; jne 0xBCD4CA4    count != 3 => skip buffer 1
    if (count == 3ull) {
        // 0xbcd4c45..0xbcd4ca4: release buffer 1 (ptr +0x20, size +0x30, cap +0x38)
        release_buffer(state->buffer1_ptr, state->buffer1_size, state->buffer1_cap);
    }

    // 0xbcd4ca4..0xbcd4cfd: release buffer 0 (ptr +0x00, size +0x10, cap +0x18)
    release_buffer(state->buffer0_ptr, state->buffer0_size, state->buffer0_cap);

    // 0xbcd4cfd..0xbcd4d02: add rsp,0x30 ; pop rsi ; ret
    return 0ull;
}

} // namespace native::helpers
