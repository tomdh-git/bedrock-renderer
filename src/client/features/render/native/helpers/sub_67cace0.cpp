// LIFT 0x67cace0 size 0xf3 1.26.62.01 sub_67cace0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67cace0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Forward declaration of lift-set callee sub_e935700 (0xE935700, tail jump to sub_392960).
// ABI: argument in RCX, result in RAX.
namespace native {
    void* sub_e935700(void* a0);
}

namespace native::helpers {

LIFT_FN(sub_67cace0, "sub_67cace0", 0x67cace0, sub_67cace0, nullptr);

// Verbatim call instructions from the disassembly of [0x67cace0, 0x67cadd3) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
#if 0
0x67cad10  call 0xE935700
0x67cad9e  call 0xE935700
0x67cadcc  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x67cace0, 0x67cadd3) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_67cace0(void* self) {
    auto* state = static_cast<sub_67cace0_state*>(self);

    // 0x67cace0..0x67cacf3: basic block 0
    // 0x67cace0  push rsi
    // 0x67cace1  push rdi
    // 0x67cace2  push rbx
    // 0x67cace3  sub rsp,0x30
    // 0x67cace7  mov rdi,[rcx]
    // 0x67cacea  test rdi,rdi
    // 0x67caced  je 0x67CADB1
    // -> if state->base == 0 goto L_0x67cadb1 (return)
    // -> if state->base != 0 goto L_0x67cacf3
    uint8_t* base = state->base;
    if (base == nullptr) {
        return 0;
    }

    // 0x67cacf3..0x67cacff: basic block 1
    // 0x67cacf3  mov rsi,rcx
    // 0x67cacf6  mov rbx,[rcx+8]
    // 0x67cacfa  cmp rdi,rbx
    // 0x67cacfd  jne short 0x67CAD32
    // -> if state->base != state->end goto L_0x67cad32 (walk blocks)
    // -> if state->base == state->end goto L_0x67cacff (flush directly)
    uint8_t* end = state->end;
    if (base != end) {
        // 0x67cad32..0x67cad38: basic block 7 entry (from jne)
        // 0x67cad32  cmp byte ptr [rdi+0x40],6
        // 0x67cad36  jne short 0x67CAD29
        // -> if block->type != 6 goto L_0x67cad29 (next block)
        // -> if block->type == 6 goto L_0x67cad38
        // 0x67cad29..0x67cad32: basic block 6 (loop increment, reached after reset or type != 6)
        // 0x67cad29  add rdi,0x50
        // 0x67cad2d  cmp rdi,rbx
        // 0x67cad30  je short 0x67CAD70
        // -> if next block == state->end goto L_0x67cad70 (flush after walk)
        // -> if next block != state->end goto L_0x67cad32 (continue loop)
        auto* block = reinterpret_cast<sub_67cace0_block*>(base);
        while (true) {
            // 0x67cad32..0x67cad38: basic block 7
            // 0x67cad32  cmp byte ptr [rdi+0x40],6
            // 0x67cad36  jne short 0x67CAD29
            if (block->type != 6) {
                // 0x67cad29..0x67cad32: basic block 6 (next block)
                block = reinterpret_cast<sub_67cace0_block*>(reinterpret_cast<uint8_t*>(block) + 0x50);
                if (reinterpret_cast<uint8_t*>(block) == end) {
                    goto L_0x67cad70;
                }
                continue;
            }

            // 0x67cad38..0x67cad42: basic block 8
            // 0x67cad38  mov rax,[rdi+0x30]
            // 0x67cad3c  cmp rax,0x10
            // 0x67cad40  jb short 0x67CAD15
            // -> if block->size < 0x10 goto L_0x67cad15 (reset block)
            // -> if block->size >= 0x10 goto L_0x67cad42
            std::uint64_t size = block->size;
            if (size < 0x10) {
                // 0x67cad15..0x67cad29: basic block 5
                // 0x67cad15  mov qword ptr [rdi+0x28],0
                // 0x67cad1d  mov qword ptr [rdi+0x30],0xF
                // 0x67cad25  mov byte ptr [rdi+0x18],0
                block->flags = 0;
                block->size = 0xF;
                block->data = nullptr;

                // 0x67cad29..0x67cad32: basic block 6 (fallthrough from reset)
                block = reinterpret_cast<sub_67cace0_block*>(reinterpret_cast<uint8_t*>(block) + 0x50);
                if (reinterpret_cast<uint8_t*>(block) == end) {
                    goto L_0x67cad70;
                }
                continue;
            }

            // 0x67cad42..0x67cad53: basic block 9
            // 0x67cad42  mov rcx,[rdi+0x18]
            // 0x67cad46  lea rdx,[rax+1]
            // 0x67cad4a  cmp rdx,0x1000
            // 0x67cad51  jb short 0x67CAD10
            // -> if size+1 < 0x1000 goto L_0x67cad10 (call sub_e935700 with data pointer)
            // -> if size+1 >= 0x1000 goto L_0x67cad53
            void* data = block->data;
            std::uint64_t count = size + 1;
            if (count < 0x1000) {
                // 0x67cad10..0x67cad15: basic block 4
                // 0x67cad10  call 0xE935700
                native::sub_e935700(data);
            } else {
                // 0x67cad53..0x67cad64: basic block 10
                // 0x67cad53  mov r8,[rcx-8]
                // 0x67cad57  add rcx,0xFFFFFFFFFFFFFFF8
                // 0x67cad5b  sub rcx,r8
                // 0x67cad5e  cmp rcx,0x20
                // 0x67cad62  jae short 0x67CADB9
                // -> if (data - 8 - chunk_header) >= 0x20 goto L_0x67cadb9 (boundary call + int3)
                // -> if (data - 8 - chunk_header) < 0x20 goto L_0x67cad64
                std::uint64_t chunk_header = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(data) - 8);
                std::uint64_t avail = (reinterpret_cast<std::uintptr_t>(data) - 8) - chunk_header;
                if (avail >= 0x20) {
                    // 0x67cadb9..0x67cadd3: basic block 18
                    // 0x67cadb9  mov qword ptr [rsp+0x20],0
                    // 0x67cadc2  xor ecx,ecx
                    // 0x67cadc4  xor edx,edx
                    // 0x67cadc6  xor r8d,r8d
                    // 0x67cadc9  xor r9d,r9d
                    // 0x67cadcc  call qword ptr [0xF9A8C78]
                    // 0x67cadd2  int3
                    auto fp = *reinterpret_cast<void**>(0xF9A8C78);
                    using Fn = void(__fastcall*)(uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t);
                    reinterpret_cast<Fn>(fp)(0, 0, 0, 0, 0);
                    __debugbreak(); // unreachable: matches int3
                }

                // 0x67cad64..0x67cad70: basic block 11
                // 0x67cad64  add rax,0x28
                // 0x67cad68  mov rdx,rax
                // 0x67cad6b  mov rcx,r8
                // 0x67cad6e  jmp short 0x67CAD10
                count = size + 0x28;
                // fallthrough to sub_e935700 call with chunk_header in rcx
                native::sub_e935700(reinterpret_cast<void*>(chunk_header));
            }

            // 0x67cad29..0x67cad32: basic block 6 (next block after processing type==6)
            block = reinterpret_cast<sub_67cace0_block*>(reinterpret_cast<uint8_t*>(block) + 0x50);
            if (reinterpret_cast<uint8_t*>(block) == end) {
                break;
            }
        }
    }

L_0x67cad70:
    // 0x67cad70..0x67cad73: basic block 12
    // 0x67cad70  mov rdi,[rsi]
    // reload base from state (rdi = state->base)
    base = state->base;

L_0x67cad73:
    // 0x67cad73..0x67cad83: basic block 13
    // 0x67cad73  mov rdx,[rsi+0x10]
    // 0x67cad77  sub rdx,rdi
    // 0x67cad7a  cmp rdx,0x1000
    // 0x67cad81  jb short 0x67CAD9B
    // -> if (state->cursor - state->base) < 0x1000 goto L_0x67cad9b
    // -> if (state->cursor - state->base) >= 0x1000 goto L_0x67cad83
    std::uintptr_t pending = state->cursor - base;
    if (pending < 0x1000) {
        // 0x67cad9b..0x67cadb1: basic block 16
        // 0x67cad9b  mov rcx,rdi
        // 0x67cad9e  call 0xE935700
        // 0x67cada3  xorps xmm0,xmm0
        // 0x67cada6  movups [rsi],xmm0
        // 0x67cada9  mov qword ptr [rsi+0x10],0
        uintptr_t result = reinterpret_cast<uintptr_t>(native::sub_e935700(base));
        state->base = nullptr;
        state->cursor = nullptr;
        return result;
    } else {
        // 0x67cad83..0x67cad94: basic block 14
        // 0x67cad83  mov rax,[rdi-8]
        // 0x67cad87  add rdi,0xFFFFFFFFFFFFFFF8
        // 0x67cad8b  sub rdi,rax
        // 0x67cad8e  cmp rdi,0x20
        // 0x67cad92  jae short 0x67CADB9
        // -> if (state->base - 8 - chunk_header) >= 0x20 goto L_0x67cadb9 (boundary call + int3)
        // -> if (state->base - 8 - chunk_header) < 0x20 goto L_0x67cad94
        std::uint64_t chunk_header = *reinterpret_cast<std::uint64_t*>(base - 8);
        std::uint64_t avail = (reinterpret_cast<std::uintptr_t>(base) - 8) - chunk_header;
        if (avail >= 0x20) {
            // 0x67cadb9..0x67cadd3: basic block 18
            auto fp = *reinterpret_cast<void**>(0xF9A8C78);
            using Fn = void(__fastcall*)(uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t);
            reinterpret_cast<Fn>(fp)(0, 0, 0, 0, 0);
            __debugbreak(); // unreachable: matches int3
        }

        // 0x67cad94..0x67cad9b: basic block 15
        // 0x67cad94  add rdx,0x27
        // 0x67cad98  mov rdi,rax
        pending += 0x27;

        // 0x67cad9b..0x67cadb1: basic block 16
        // 0x67cad9b  mov rcx,rdi
        // 0x67cad9e  call 0xE935700
        // 0x67cada3  xorps xmm0,xmm0
        // 0x67cada6  movups [rsi],xmm0
        // 0x67cada9  mov qword ptr [rsi+0x10],0
        uintptr_t result = reinterpret_cast<uintptr_t>(native::sub_e935700(reinterpret_cast<void*>(chunk_header)));
        state->base = nullptr;
        state->cursor = nullptr;
        return result;
    }

    // 0x67cadb1..0x67cadb9: basic block 17 (return)
    // 0x67cadb1  add rsp,0x30
    // 0x67cadb5  pop rbx
    // 0x67cadb6  pop rdi
    // 0x67cadb7  pop rsi
    // 0x67cadb8  ret
    // Not reached; all paths return above.
    return 0;
}

} // namespace native::helpers