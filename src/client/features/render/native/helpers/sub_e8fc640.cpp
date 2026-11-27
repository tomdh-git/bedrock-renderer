// LIFT 0xe8fc640 size 0x11f 1.26.62.01 sub_e8fc640
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e8fc640.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Layout assertions mirrored from the header so the compiled source carries them too.
static_assert(offsetof(native::helpers::sub_e8fc640_list, vtable) == 0x0, "sub_0xe8fc640 list+0x0 field");
static_assert(offsetof(native::helpers::sub_e8fc640_list, state) == 0x8, "sub_0xe8fc640 list+0x8 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, f0) == 0x0, "sub_0xe8fc640 rcx+0x0 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, stringData) == 0x58, "sub_0xe8fc640 rcx+0x58 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, stringSize) == 0x68, "sub_0xe8fc640 rcx+0x68 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, stringCapacity) == 0x70, "sub_0xe8fc640 rcx+0x70 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, list) == 0xa0, "sub_0xe8fc640 rcx+0xa0 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, bufferBegin) == 0xb0, "sub_0xe8fc640 rcx+0xb0 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, bufferEnd) == 0xc0, "sub_0xe8fc640 rcx+0xc0 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rcx, child) == 0xe8, "sub_0xe8fc640 rcx+0xe8 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rax, slot0) == 0x0, "sub_0xe8fc640 rax+0x0 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rdi, clearedWords) == 0x0, "sub_0xe8fc640 rdi+0x0 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rdi, clearedTail) == 0x10, "sub_0xe8fc640 rdi+0x10 field");
static_assert(offsetof(native::helpers::sub_e8fc640_rsp, fifthArgumentHome) == 0x20, "sub_0xe8fc640 rsp+0x20 field");

namespace native::helpers {

// Verbatim call instructions from the disassembly of [0xe8fc640, 0xe8fc75f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xe8fc66b  call qword ptr [0xF99FFA0]
0xe8fc688  call qword ptr [0xF99FFA0]
0xe8fc6d0  call 0xE935700
0xe8fc6ea  call 0x2462890
0xe8fc725  call 0xE935700
0xe8fc758  call qword ptr [0xF9A8C78]
#endif

// [0xF99FFA0] is the control-flow-guard dispatch slot (`jmp rax`): the target is the
// function pointer loaded from the child vtable slot 0 before each call. [0xF9A8C78]
// is the process failure handler (_invoke_watson); its absolute address is
// image base 0x140000000 + RVA 0xF9A8C78.
constexpr std::uintptr_t kFailureSlot = 0x14F9A8C78ULL;

void sub_e8fc640(void* self) {
    auto* const obj = static_cast<sub_e8fc640_rcx*>(self);

    // 0xe8fc640..0xe8fc660: basic block 0 (detach the +0xE8 child)
    // 0xe8fc640  push rsi
    // 0xe8fc641  push rdi
    // 0xe8fc642  sub rsp,0x28
    // 0xe8fc646  mov rsi,rcx
    // 0xe8fc649  mov rcx,[rcx+0xE8]
    // 0xe8fc650  mov qword ptr [rsi+0xE8],0
    // 0xe8fc65b  test rcx,rcx
    // 0xe8fc65e  je short 0xE8FC68E
    void* child = obj->child;
    obj->child = nullptr;
    if (child != nullptr) {
        // 0xe8fc660..0xe8fc67d: basic block 1 (release the detached child)
        // 0xe8fc660  mov rax,[rcx]
        // 0xe8fc663  mov rax,[rax]
        // 0xe8fc666  mov edx,1
        // 0xe8fc66b  call qword ptr [0xF99FFA0]
        // 0xe8fc671  mov rcx,[rsi+0xE8]
        // 0xe8fc678  test rcx,rcx
        // 0xe8fc67b  je short 0xE8FC68E
        using Slot0Fn = void (*)(void*, std::uint32_t);
        void* const childVtable = *reinterpret_cast<void* const volatile*>(child);
        auto* const slots = reinterpret_cast<sub_e8fc640_rax*>(childVtable);
        reinterpret_cast<Slot0Fn>(slots->slot0)(child, 1);

        // 0xe8fc67d..0xe8fc68e: basic block 2 (release the child the slot-0 call installed)
        // 0xe8fc67d  mov rax,[rcx]
        // 0xe8fc680  mov rax,[rax]
        // 0xe8fc683  mov edx,1
        // 0xe8fc688  call qword ptr [0xF99FFA0]
        child = obj->child;
        if (child != nullptr) {
            void* const childVtable2 = *reinterpret_cast<void* const volatile*>(child);
            auto* const slots2 = reinterpret_cast<sub_e8fc640_rax*>(childVtable2);
            reinterpret_cast<Slot0Fn>(slots2->slot0)(child, 1);
        }
    }

    // 0xe8fc68e..0xe8fc69a: basic block 3 (the +0xB0 allocation)
    // 0xe8fc68e  mov rcx,[rsi+0xB0]
    // 0xe8fc695  test rcx,rcx
    // 0xe8fc698  je short 0xE8FC6E3
    {
        auto* const buffer = static_cast<std::uint8_t*>(obj->bufferBegin);
        if (buffer != nullptr) {
            // 0xe8fc69a..0xe8fc6ad: basic block 4 (allocation size)
            // 0xe8fc69a  mov rdx,[rsi+0xC0]
            // 0xe8fc6a1  sub rdx,rcx
            // 0xe8fc6a4  cmp rdx,0x1000
            // 0xe8fc6ab  jb short 0xE8FC6C9
            std::uintptr_t const bytes =
                reinterpret_cast<std::uintptr_t>(obj->bufferEnd) -
                reinterpret_cast<std::uintptr_t>(buffer);
            void* chunk = buffer;
            if (bytes >= 0x1000) {
                // 0xe8fc6ad..0xe8fc6c2: basic block 5 (recover the aligned-allocation header)
                // 0xe8fc6ad  mov rax,[rcx-8]
                // 0xe8fc6b1  add rcx,0xFFFFFFFFFFFFFFF8
                // 0xe8fc6b5  sub rcx,rax
                // 0xe8fc6b8  cmp rcx,0x20
                // 0xe8fc6bc  jae 0xE8FC745
                std::uintptr_t const header = *reinterpret_cast<std::uintptr_t const volatile*>(buffer - 8);
                if ((reinterpret_cast<std::uintptr_t>(buffer) - 8) - header >= 0x20) goto invalid_parameter;
                // 0xe8fc6c2..0xe8fc6c9: basic block 6 (free the header base, size + 0x27)
                // 0xe8fc6c2  add rdx,0x27
                // 0xe8fc6c6  mov rcx,rax
                chunk = reinterpret_cast<void*>(header);
            }
            // 0xe8fc6c9..0xe8fc6e3: basic block 7 (free and clear the +0xB0 span)
            // 0xe8fc6c9  lea rdi,[rsi+0xB0]
            // 0xe8fc6d0  call 0xE935700
            // 0xe8fc6d5  xorps xmm0,xmm0
            // 0xe8fc6d8  movups [rdi],xmm0
            // 0xe8fc6db  mov qword ptr [rdi+0x10],0
            sub_e935700(chunk);
            auto* const cleared = reinterpret_cast<sub_e8fc640_rdi*>(&obj->bufferBegin);
            cleared->clearedWords[0] = 0;
            cleared->clearedWords[1] = 0;
            cleared->clearedTail = 0;
        }
    }

    // 0xe8fc6e3..0xe8fc6f9: basic block 8 (release the +0xA0 sub-object, then the string)
    // 0xe8fc6e3  lea rcx,[rsi+0xA0]
    // 0xe8fc6ea  call 0x2462890
    // 0xe8fc6ef  mov rax,[rsi+0x70]
    // 0xe8fc6f3  cmp rax,0x10
    // 0xe8fc6f7  jb short 0xE8FC72A
    {
        sub_2462890(&obj->list);
        std::uint64_t const capacity = obj->stringCapacity;
        if (capacity >= 0x10) {
            // 0xe8fc6f9..0xe8fc70a: basic block 9 (heap-backed string buffer)
            // 0xe8fc6f9  mov rcx,[rsi+0x58]
            // 0xe8fc6fd  lea rdx,[rax+1]
            // 0xe8fc701  cmp rdx,0x1000
            // 0xe8fc708  jb short 0xE8FC725
            auto* const text = static_cast<std::uint8_t*>(obj->stringData);
            void* chunk = text;
            if (capacity + 1 >= 0x1000) {
                // 0xe8fc70a..0xe8fc71b: basic block 10 (recover the aligned-allocation header)
                // 0xe8fc70a  mov r8,[rcx-8]
                // 0xe8fc70e  add rcx,0xFFFFFFFFFFFFFFF8
                // 0xe8fc712  sub rcx,r8
                // 0xe8fc715  cmp rcx,0x20
                // 0xe8fc719  jae short 0xE8FC745
                std::uintptr_t const header = *reinterpret_cast<std::uintptr_t const volatile*>(text - 8);
                if ((reinterpret_cast<std::uintptr_t>(text) - 8) - header >= 0x20) goto invalid_parameter;
                // 0xe8fc71b..0xe8fc725: basic block 11 (free the header base, size + 0x28)
                // 0xe8fc71b  add rax,0x28
                // 0xe8fc71f  mov rdx,rax
                // 0xe8fc722  mov rcx,r8
                chunk = reinterpret_cast<void*>(header);
            }
            // 0xe8fc725..0xe8fc72a: basic block 12 (free the string buffer)
            // 0xe8fc725  call 0xE935700
            sub_e935700(chunk);
        }
    }

    // 0xe8fc72a..0xe8fc745: basic block 13 (reset the string to its empty inline state)
    // 0xe8fc72a  mov qword ptr [rsi+0x68],0
    // 0xe8fc732  mov qword ptr [rsi+0x70],0xF
    // 0xe8fc73a  mov byte ptr [rsi+0x58],0
    // 0xe8fc73e  add rsp,0x28
    // 0xe8fc742  pop rdi
    // 0xe8fc743  pop rsi
    // 0xe8fc744  ret
    obj->stringSize = 0;
    obj->stringCapacity = 0xF;
    *reinterpret_cast<std::uint8_t*>(&obj->stringData) = 0;
    return;

invalid_parameter:
    // 0xe8fc745..0xe8fc75f: basic block 14 (allocation-corruption failure handler)
    // 0xe8fc745  mov qword ptr [rsp+0x20],0
    // 0xe8fc74e  xor ecx,ecx
    // 0xe8fc750  xor edx,edx
    // 0xe8fc752  xor r8d,r8d
    // 0xe8fc755  xor r9d,r9d
    // 0xe8fc758  call qword ptr [0xF9A8C78]
    // 0xe8fc75e  int3
    {
        std::uintptr_t home5 = 0;   // [rsp+0x20] fifth argument home of the failure call
        (void)home5;
        using FailFn = void (__cdecl*)(void*, void*, void*, std::uint32_t, std::uintptr_t);
        FailFn const failFn = reinterpret_cast<FailFn>(
            *reinterpret_cast<std::uintptr_t const volatile*>(kFailureSlot));
        failFn(nullptr, nullptr, nullptr, 0, 0);
        __assume(false);
    }
}

LIFT_FN(sub_e8fc640, "sub_e8fc640", 0xe8fc640, sub_e8fc640, nullptr);

} // namespace native::helpers
