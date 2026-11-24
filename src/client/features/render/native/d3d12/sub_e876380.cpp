// LIFT 0xe876380 size 0x92 1.26.62.01 BgfxFrameBuilder slot 16
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e876380.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

static_assert(offsetof(native::d3d12::sub_e876380_state, field_0x08) == 0x08);
static_assert(offsetof(native::d3d12::sub_e876380_state, field_0x18) == 0x18);
static_assert(offsetof(native::d3d12::sub_e876380_state, field_0x20) == 0x20);
static_assert(sizeof(native::d3d12::sub_e876380_state) >= 0x28);

// Boundary callees (class stl / crt per docs/data/native_boundary.tsv)
namespace native::boundary {
    extern "C" void sub_1f5ef50(void* a1, void* a2, void* a3);      // 0x1f5ef50 (stl)
    extern "C" void sub_e935700(void* a1);                        // 0xe935700 (lift, jmp 0x392960)
    extern "C" void sub_f9a8c78();                                  // 0xf9a8c78 (crt - _invoke_watson)
}

// Verbatim call instructions from the disassembly of [0xe876380, 0xe876412).
// Targets: 0x1F5EF50 (stl boundary), 0xE935700 (lift-set, forward-declared),
// qword ptr [0xF9A8C78] (crt _invoke_watson IAT slot). No lift-set callees.
// 0xe876397  call 0x1F5EF50
// 0xe8763a5  call 0xE935700
// 0xe8763df  call 0xE935700
// 0xe87640b  call qword ptr [0xF9A8C78]

namespace native::d3d12 {

void sub_e876380(void* a0) {
    // 0xe876380..0xe876397
    unsigned char* rsi = reinterpret_cast<unsigned char*>(a0);
    void* rax = *reinterpret_cast<void**>(rsi + 0x20);
    void* r8 = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(rax) + 0x8);
    void* rcx = rsi + 0x20;
    void* rdx = rcx;
    native::boundary::sub_1f5ef50(rcx, rdx, r8);
    // 0xe87639c..0xe8763a5
    void* rcx2 = *reinterpret_cast<void**>(rsi + 0x20);
    native::boundary::sub_e935700(rcx2, reinterpret_cast<void*>(0x50));
    // 0xe8763aa..0xe8763b1
    void* rcx3 = *reinterpret_cast<void**>(rsi + 0x8);
    if (rcx3 == nullptr) {
        // 0xe8763f2..0xe8763f7
        return;
    }
    // 0xe8763b3..0xe8763db
    void* rdx2 = *reinterpret_cast<void**>(rsi + 0x18);
    std::uintptr_t diff = reinterpret_cast<std::uintptr_t>(rdx2) - reinterpret_cast<std::uintptr_t>(rcx3);
    if (diff >= 0x1000) {
        // 0xe8763c3..0xe8763d8
        void* rax2 = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(rcx3) - 0x8);
        void* rcx4 = reinterpret_cast<unsigned char*>(rcx3) - 0x8;
        std::uintptr_t rcxv = reinterpret_cast<std::uintptr_t>(rcx4) - reinterpret_cast<std::uintptr_t>(rax2);
        if (rcxv >= 0x20) {
            // 0xe8763f8..0xe876411
            *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(__builtin_alloca(0)) + 0x20) = nullptr;
            using Watson = uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
            reinterpret_cast<Watson>(*reinterpret_cast<uintptr_t*>(0x14F9A8C78))(nullptr, nullptr, nullptr, 0, 0);
            __debugbreak();
        }
        diff += 0x27;
        rcx3 = rax2;
    }
    rsi += 0x8;
    native::boundary::sub_e935700(rcx3, reinterpret_cast<void*>(diff), nullptr);
    // 0xe8763e4..0xe8763ea
    *reinterpret_cast<unsigned long long*>(rsi) = 0;
    *reinterpret_cast<unsigned long long*>(rsi + 0x8) = 0;
    *reinterpret_cast<std::uint64_t*>(rsi + 0x10) = 0;
    // 0xe8763f2..0xe8763f7
}

} // namespace native::d3d12

// LIFT_FN registration placeholder
// LIFT_FN("sub_e876380", 0xe876380, sub_e876380);