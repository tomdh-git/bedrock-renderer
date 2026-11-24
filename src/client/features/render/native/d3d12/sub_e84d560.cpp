// LIFT 0xe84d560 size 0xfa 1.26.62.01 sub_e84d560
#include "client/features/render/native/d3d12/sub_e84d560.h"
#include <cstdint>

namespace native::d3d12 {

#if 0
0xe84d5ef  call r10
0xe84d630  jmp 0xE935700
0xe84d653  call qword ptr [0xF9A8C78]
#endif

// LIFT_FN(0xe84d560, sub_e84d560)
// static_assert(sizeof(void*) == 8, "abi");


void sub_e84d560(void* self) {
    // 0xe84d560..0xe84d576
    // 0xe84d577..0xe84d581
    auto* rsi = reinterpret_cast<unsigned char*>(self);
    void* rcx = *reinterpret_cast<void**>(rsi + 0x8);
    if (rcx == nullptr) {
        // 0xe84d635..0xe84d63f
        return;
    }
    // 0xe84d587..0xe84d592
    // 0xe84d59d..0xe84d59d
    // 0xe84d594..0xe84d59b
    auto* rdi = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(rsi + 0x18));
    auto* rbx = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(rsi + 0x20));
    if (rdi == rbx) goto tail;
    // 0xe84d594..0xe84d59b
    void* r14 = reinterpret_cast<void*>(0xF847A07);
    // loop
    while (true) {
        // 0xe84d5b4..0xe84d5b8
        if (*reinterpret_cast<std::uint32_t*>(rdi + 0x28) == 0) {
            // 0xe84d5ab path fallthrough to add
        } else {
            // 0xe84d5ba..0xe84d5f2
            void* slot = *reinterpret_cast<void**>(0x12ADF800);
            if (slot != nullptr) {
                void* rdx = *reinterpret_cast<void**>(rdi + 0x20);
                using Fn = void(*)(void*, void*, void*, void*, std::uint64_t, std::uint64_t);
                Fn f = *reinterpret_cast<Fn*>(*reinterpret_cast<void**>(slot) + 8); // vtable[1]
                // call through data slot resolved pointer r10 = 0xF99FFA0
                void (*r10)(void*, void*, void*, void*, std::uint64_t, std::uint64_t) =
                    *reinterpret_cast<void(**)(void*,void*,void*,void*,std::uint64_t,std::uint64_t)>(0xF99FFA0);
                r10(slot, rdx, nullptr, nullptr, 0, 0);
            }
        }
        // 0xe84d5a0..0xe84d5a4
        *reinterpret_cast<void**>(rdi + 0x20) = r14;
        *reinterpret_cast<std::uint32_t*>(rdi + 0x28) = 0;
        // 0xe84d5ab..0xe84d5b2
        // 0xe84d5f3..0xe84d5f3
        rdi += 0x30;
        if (rdi == rbx) break;
    }
tail:
    // 0xe84d5f5..0xe84d5f9
    rcx = *reinterpret_cast<void**>(rsi + 0x8);
    // 0xe84d5f9..0xe84d623
    std::uint64_t rax = *reinterpret_cast<std::uint64_t*>(rsi + 0x10);
    rax <<= 4;
    std::uint64_t rdx2 = rax + rax * 2; // *3
    if (rdx2 < 0x1000) {
        // 0xe84d626
    } else {
        void* alloc = *reinterpret_cast<void**>(rcx - 8);
        rcx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rcx) - 8);
        std::uint64_t diff = reinterpret_cast<std::uintptr_t>(rcx) - reinterpret_cast<std::uintptr_t>(alloc);
        if (diff < 0x20) {
            // 0xe84d61f
            rdx2 += 0x27;
            rcx = alloc;
        } else {
            // 0xe84d640..0xe84d659 unreachable abort
            return;
        }
    }
    // 0xe84d626..0xe84d630 tail call
    using TailFn = void(*)(void*, std::uint64_t);
    auto tailfn = reinterpret_cast<TailFn>(0xE935700);
    tailfn(rcx, rdx2);
}

} // namespace native::d3d12
