// LIFT 0x56aeff0 size 0xff 1.26.62.01 sub_56aeff0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56aeff0.h"
#include "client/features/render/native/helpers/sub_56aea80.h"
#include "client/features/render/rewrite/RewriteRegistry.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// 0xE935700, lift set: tail jump to sub_392960; the argument arrives in rcx and
// the size in rdx is dead inside the callee (declared in sub_e935700.h).
namespace native {
void* sub_e935700(void* a0);
}

namespace native::helpers {

static_assert(offsetof(sub_56aeff0_rcx, count) == 0x20, "0x56aeff0: layout rcx+0x20");
static_assert(offsetof(sub_56aeff0_r8, dispatch_state) == 0x58, "0x56aeff0: layout r8+0x58");

LIFT_FN(sub_56aeff0, "sub_56aeff0", 0x56aeff0, sub_56aeff0, nullptr);

// Verbatim call instructions from the disassembly of [0x56aeff0, 0x56af0ef) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56af037  call 0x56AEA80
0x56af08b  call 0xE935700
0x56af0c2  call 0xE935700
0x56af0e8  call qword ptr [0xF9A8C78]
#endif

// 0x56af0d5..0x56af0ef: validation-failure path. [rsp+0x20] = 0 (5th argument),
// ecx = edx = r8d = r9d = 0, then the loader-patched invalid-parameter handler in
// data slot 0xF9A8C78 is called; the call is followed by int3, so it is noreturn.
[[noreturn]] static void sub_56aeff0_invalid_parameter() {
    // 0x56af0d5  mov qword ptr [rsp+0x20],0
    // 0x56af0de  xor ecx,ecx
    // 0x56af0e0  xor edx,edx
    // 0x56af0e2  xor r8d,r8d
    // 0x56af0e5  xor r9d,r9d
    // 0x56af0e8  call qword ptr [0xF9A8C78]
    // 0x56af0ee  int3
    using handler_fn = std::uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*,
                                                const wchar_t*, unsigned int,
                                                std::uintptr_t);
    reinterpret_cast<handler_fn>(*reinterpret_cast<std::uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78))(nullptr, nullptr, nullptr, 0, 0);
    __assume(false);
}

void sub_56aeff0(void* self) {
    auto* map = reinterpret_cast<sub_56aeff0_rcx*>(self);

    // 0x56aeff0..0x56af003: basic block 0 (prologue, live-count test)
    // 0x56aeff0  push rsi
    // 0x56aeff1  push rdi
    // 0x56aeff2  push rbx
    // 0x56aeff3  sub rsp,0x30
    // 0x56aeff7  mov rsi,rcx
    // 0x56aeffa  mov rax,[rcx+0x20]
    // 0x56aeffe  test rax,rax
    // 0x56af001  je short 0x56AF051
    std::uint8_t out_byte;                     // rsp+0x2F, address handed over in rdx
    std::uint64_t count = map->count;
    if (count != 0) {
        // 0x56af003..0x56af010: basic block 1
        // 0x56af003  lea rdi,[rsp+0x2F]
        // 0x56af008  nop [rax+rax]
        std::uint8_t* out_ptr = &out_byte;

        do {
            // 0x56af010..0x56af049: basic block 2 (release one live element per iteration)
            // 0x56af010  mov rcx,[rsi+0x18]
            // 0x56af014  add rax,rcx
            // 0x56af017  dec rax
            std::uint64_t index = count + map->hash_bias - 1;
            // 0x56af01a  mov rcx,[rsi+8]
            // 0x56af01e  mov rdx,[rsi+0x10]
            // 0x56af022  dec rdx
            // 0x56af025  and rdx,rax
            index &= map->capacity - 1;
            // 0x56af028  mov r8,[rcx+rdx*8]
            sub_56aeff0_r8* element = map->elements[index];
            // 0x56af02c  movsx rcx,byte ptr [r8+0x58]
            // 0x56af031  inc rcx
            std::uint64_t selector = static_cast<std::uint64_t>(
                static_cast<std::int64_t>(element->dispatch_state) + 1);
            // 0x56af034  mov rdx,rdi
            // 0x56af037  call 0x56AEA80
            (void)sub_56aea80(selector, out_ptr, element);
            // 0x56af03c  mov rax,[rsi+0x20]
            // 0x56af040  dec rax
            // 0x56af043  mov [rsi+0x20],rax
            count = map->count - 1;
            map->count = count;
            // 0x56af047  jne short 0x56AF010
        } while (count != 0);

        // 0x56af049..0x56af051: basic block 3
        // 0x56af049  mov qword ptr [rsi+0x18],0
        map->hash_bias = 0;
    }

    // 0x56af051..0x56af05a: basic block 4
    // 0x56af051  mov rcx,[rsi+8]
    // 0x56af055  test rcx,rcx
    // 0x56af058  je short 0x56AF0CD
    if (map->elements == nullptr) {
        // 0x56af0cd..0x56af0d5: basic block 16 (epilogue)
        // 0x56af0cd  add rsp,0x30
        // 0x56af0d1  pop rbx
        // 0x56af0d2  pop rdi
        // 0x56af0d3  pop rsi
        // 0x56af0d4  ret
        return;
    }

    // 0x56af05a..0x56af067: basic block 5
    // 0x56af05a  lea rbx,[rsi+8]
    // 0x56af05e  mov rdi,[rsi+0x10]
    // 0x56af062  test rdi,rdi
    // 0x56af065  jle short 0x56AF09A
    std::int64_t slot = static_cast<std::int64_t>(map->capacity);
    if (slot > 0) {
        // 0x56af067..0x56af06c: basic block 6
        // 0x56af067  inc rdi
        // 0x56af06a  jmp short 0x56AF079
        ++slot;
        for (;;) {
            // 0x56af079..0x56af086: basic block 9
            // 0x56af079  mov rax,[rbx]
            // 0x56af07c  mov rcx,[rax+rdi*8-0x10]
            // 0x56af081  test rcx,rcx
            // 0x56af084  je short 0x56AF070
            sub_56aeff0_r8* element = map->elements[slot - 2];
            if (element != nullptr) {
                // 0x56af086..0x56af092: basic block 10
                // 0x56af086  mov edx,0x60
                // 0x56af08b  call 0xE935700
                // 0x56af090  jmp short 0x56AF070
                (void)native::sub_e935700(element);
            }

            // 0x56af06c..0x56af070: basic block 7 (nop padding)
            // 0x56af06c  nop [rax]
            // 0x56af070..0x56af079: basic block 8
            // 0x56af070  dec rdi
            // 0x56af073  cmp rdi,1
            // 0x56af077  jbe short 0x56AF092
            --slot;
            if (slot <= 1) break;
        }
    }

    // 0x56af092..0x56af09a: basic block 11
    // 0x56af092  mov rcx,[rsi+8]
    // 0x56af096  mov rdi,[rsi+0x10]
    void* block = map->elements;
    // 0x56af09a..0x56af0a7: basic block 12
    // 0x56af09a  shl rdi,3
    // 0x56af09e  cmp rdi,0x1000
    // 0x56af0a5  jb short 0x56AF0BF
    std::uint64_t size = static_cast<std::uint64_t>(map->capacity) << 3;
    if (size >= 0x1000) {
        // 0x56af0a7..0x56af0b8: basic block 13 (validate the size-prefixed allocation)
        // 0x56af0a7  mov rax,[rcx-8]
        // 0x56af0ab  add rcx,0xFFFFFFFFFFFFFFF8
        // 0x56af0af  sub rcx,rax
        // 0x56af0b2  cmp rcx,0x20
        // 0x56af0b6  jae short 0x56AF0D5
        std::uint64_t header = *reinterpret_cast<std::uint64_t*>(
            static_cast<std::uint8_t*>(block) - 8);
        std::uintptr_t delta = reinterpret_cast<std::uintptr_t>(block) - 8 - header;
        if (delta >= 0x20) {
            // 0x56af0d5..0x56af0ef: basic block 17 (noreturn failure path)
            sub_56aeff0_invalid_parameter();
        }

        // 0x56af0b8..0x56af0bf: basic block 14
        // 0x56af0b8  add rdi,0x27
        // 0x56af0bc  mov rcx,rax
        size += 0x27;
        block = reinterpret_cast<void*>(header);
    }

    // 0x56af0bf..0x56af0cd: basic block 15
    // 0x56af0bf  mov rdx,rdi
    // 0x56af0c2  call 0xE935700
    // 0x56af0c7  xorps xmm0,xmm0
    // 0x56af0ca  movups [rbx],xmm0
    (void)native::sub_e935700(block);
    map->elements = nullptr;
    map->capacity = 0;

    // 0x56af0cd..0x56af0d5: basic block 16 (epilogue)
    // 0x56af0cd  add rsp,0x30
    // 0x56af0d1  pop rbx
    // 0x56af0d2  pop rdi
    // 0x56af0d3  pop rsi
    // 0x56af0d4  ret
}

} // namespace native::helpers
