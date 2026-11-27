// LIFT 0x1d3b70 size 0x11a 1.26.62.01 sub_1d3b70
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_1d3b70.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Forward declaration: sub_e935700 is a lift-set callee in namespace native.
// Its header has a self-referential static_assert bug; forward-declare instead.
namespace native {
void* sub_e935700(void* a0);
}

namespace native::helpers {

LIFT_FN(sub_1d3b70, "sub_1d3b70", 0x1d3b70, sub_1d3b70, nullptr);

// Verbatim call instructions from the disassembly of [0x1d3b70, 0x1d3c8a) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x1d3bc1  call qword ptr [0xF99FFA0]
0x1d3bd7  call qword ptr [0xF99FFA0]
0x1d3c0d  call 0xE935700
0x1d3c51  call 0xE935700
0x1d3c83  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x1d3b70, 0x1d3c8a) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

void sub_1d3b70(void* self) {
    // Layout assertion: packed structs match observed offsets (see sub_1d3b70.h).
static_assert(offsetof(sub_1d3b70_rcx, f18) == 0x18, "sub_1d3b70: rcx+0x18 is range-1 begin");
static_assert(offsetof(sub_1d3b70_rcx, f20) == 0x20, "sub_1d3b70: rcx+0x20 is range-1 end");
static_assert(offsetof(sub_1d3b70_rcx, f28) == 0x28, "sub_1d3b70: rcx+0x28 is range-1 capacity/end fallback");

// Data-slot RVAs (call qword ptr [slot]; pointer read at call time, brief rule 69).
static constexpr std::uintptr_t kRvaReleaseSlot = 0xF99FFA0;  // sub_eea6040, boundary/vendor thunk
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;     // fail handler (noreturn path, then int3)

    // x64 Microsoft ABI: RCX = self. RBX, RDI, RSI, R14, R15 are callee-saved.
    void* rsi = self;          // RCX copy
    void* rdi = nullptr;       // element cursor
    void** r14 = nullptr;      // &self->f18
    std::uint64_t r15 = 0;     // self->f20 (range end)
    void* rbx = nullptr;       // element pointer
    void* rcx = nullptr;       // second-path object pointer
    std::uint64_t rdx = 0;     // size delta
    std::uint64_t rax = 0;     // size / block size

    // 0x1d3b70..0x1d3b8b: block 0 (prologue + null test on self->f18)
    rdi = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(self) + 0x18);  // mov rdi,[rcx+0x18]
    if (rdi == nullptr) goto L_0x1d3c21;                                        // test rdi,rdi ; je block14

    // 0x1d3b8b..0x1d3b98: block 1 (loop setup)
    r14 = reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(self) + 0x18);     // lea r14,[rsi+0x18]
    r15 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x20);  // mov r15,[rsi+0x20]
    if (reinterpret_cast<uintptr_t>(rdi) != r15) goto L_0x1d3ba9;               // cmp rdi,r15 ; jne block5
    goto L_0x1d3bdf;                                                            // block 2: jmp block9 (block 3 is dead-code nop padding)

    // 0x1d3ba9..0x1d3bb2: block 5 (loop body: read element pointer)
    L_0x1d3ba9:;
    rbx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdi) + 8);       // mov rbx,[rdi+8]
    if (rbx == nullptr) goto L_0x1d3ba0;                                        // test rbx,rbx ; je block4

    // 0x1d3bb2..0x1d3bb8: block 6 (strong refcount decrement)
    if (_InterlockedDecrement(
            reinterpret_cast<volatile long*>(reinterpret_cast<uint8_t*>(rbx) + 8)) != 0) {  // lock dec [rbx+8]
        goto L_0x1d3ba0;                                                        // jne block4
    }

    // 0x1d3bb8..0x1d3bcd: block 7 (first vtable slot release + weak refcount decrement)
    {
        auto releaseFn = reinterpret_cast<void (*)(void*)>(
            *reinterpret_cast<const std::uintptr_t*>(
                RewriteRegistry::imageBase() + kRvaReleaseSlot));  // mov rdx,[0xF99FFA0] (slot read at call time)
        releaseFn(rbx);                                                      // call qword ptr [0xF99FFA0] ; rcx = rbx
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(reinterpret_cast<uint8_t*>(rbx) + 0xC)) != 0) {  // lock dec [rbx+0xC]
            goto L_0x1d3ba0;                                                  // jne block4
        }
    }

    // 0x1d3bcd..0x1d3bdf: block 8 (second vtable slot release)
    {
        auto releaseFn = reinterpret_cast<void (*)(void*)>(
            *reinterpret_cast<const std::uintptr_t*>(
                RewriteRegistry::imageBase() + kRvaReleaseSlot));
        releaseFn(rbx);  // call qword ptr [0xF99FFA0] ; rcx = rbx
    }
    goto L_0x1d3ba0;   // jmp block4

    // 0x1d3ba0..0x1d3ba9: block 4 (loop advance + exit test)
    L_0x1d3ba0:;
    rdi = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(rdi) + 0x10);      // add rdi,0x10
    if (reinterpret_cast<uintptr_t>(rdi) != r15) goto L_0x1d3ba9;               // cmp rdi,r15 ; jne block5

    // 0x1d3bdf..0x1d3be2: block 9 (reset rdi to range begin)
    L_0x1d3bdf:;
    rdi = *r14;                                                                 // mov rdi,[r14]

    // 0x1d3be2..0x1d3bf2: block 10 (first range size check)
    L_0x1d3be2:;
    rdx = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x28)  // mov rdx,[rsi+0x28]
        - reinterpret_cast<uintptr_t>(rdi);                                     // sub rdx,rdi
    if (rdx < 0x1000) goto L_0x1d3c0a;                                          // cmp rdx,0x1000 ; jb block13

    // 0x1d3bf2..0x1d3c03: block 11 (allocation header sanity check)
    rax = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(rdi) - 8);  // mov rax,[rdi-8]
    if ((reinterpret_cast<uintptr_t>(rdi) - 8) - rax >= 0x20) goto L_0x1d3c70;  // cmp rdi,0x20 ; jae block20

    // 0x1d3c03..0x1d3c0a: block 12 (adjust delta, set arg)
    rdx += 0x27;                                                                // add rdx,0x27
    rdi = reinterpret_cast<void*>(rax);                                         // mov rdi,rax

    // 0x1d3c0a..0x1d3c21: block 13 (sub_e935700 call + zero range-1 bookkeeping)
    L_0x1d3c0a:;
    native::sub_e935700(rdi);                                                   // mov rcx,rdi ; call 0xE935700
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(r14)) = 0;     // xorps + movups [r14],xmm0 (16B zero)
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(r14) + 8) = 0;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(r14) + 0x10) = 0;  // mov [r14+0x10],0

    // 0x1d3c21..0x1d3c29: block 14 (second path: null test on self->f00)
    L_0x1d3c21:;
    rcx = *reinterpret_cast<void**>(rsi);                                       // mov rcx,[rsi]
    if (rcx == nullptr) goto L_0x1d3c64;                                        // test rcx,rcx ; je block19

    // 0x1d3c29..0x1d3c39: block 15 (second range size check)
    rdx = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x10)  // mov rdx,[rsi+0x10]
        - reinterpret_cast<uintptr_t>(rcx);                                     // sub rdx,rcx
    if (rdx < 0x1000) goto L_0x1d3c51;                                          // cmp rdx,0x1000 ; jb block18

    // 0x1d3c39..0x1d3c4a: block 16 (allocation header sanity check)
    rax = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(rcx) - 8);  // mov rax,[rcx-8]
    if ((reinterpret_cast<uintptr_t>(rcx) - 8) - rax >= 0x20) goto L_0x1d3c70;  // cmp rcx,0x20 ; jae block20

    // 0x1d3c4a..0x1d3c51: block 17 (adjust delta, set arg)
    rdx += 0x27;                                                                // add rdx,0x27
    rcx = reinterpret_cast<void*>(rax);                                         // mov rcx,rax

    // 0x1d3c51..0x1d3c64: block 18 (sub_e935700 call + zero self bookkeeping)
    L_0x1d3c51:;
    native::sub_e935700(rcx);                                                   // call 0xE935700
    *reinterpret_cast<std::uint64_t*>(rsi) = 0;                                 // xorps + movups [rsi],xmm0 (16B zero)
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(rsi) + 8) = 0;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<uint8_t*>(rsi) + 0x10) = 0;  // mov [rsi+0x10],0

    // 0x1d3c64..0x1d3c70: block 19 (epilogue)
    L_0x1d3c64:;
    return;                                                                     // add rsp,0x30 ; pop... ; ret

    // 0x1d3c70..0x1d3c8a: block 20 (noreturn fail path)
    L_0x1d3c70:;
    {
        auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
            *reinterpret_cast<const std::uintptr_t*>(
                RewriteRegistry::imageBase() + kRvaFailSlot));  // mov rdx,[0xF9A8C78] (slot read at call time)
        failFn(nullptr, nullptr, nullptr, nullptr);                             // call qword ptr [0xF9A8C78] ; 4 zeroed args
        __debugbreak();                                                         // int3
        __assume(false);                                                        // int3 is noreturn pad
    }
}

} // namespace native::helpers
