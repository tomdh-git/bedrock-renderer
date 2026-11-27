#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_a14e0 (0xa14e0, size 0xd1, 1.26.62.01): see sub_a14e0.cpp for the reversed source (complete).
//
// Object layout observed in sub_a14e0 (rcx = a0) [V: rdis dis 0xa14e0]:
//   +0x18 void*        (R: pointer read; W: qword 0 through the pointer)
//   +0x20 void*        (R; W: qword 0 through the pointer)
//   +0x38 void*        (R; W: qword 0 through the pointer)
//   +0x40 void*        (R: pointer read + deref; W: qword 0 through the pointer)
//   +0x50 void*        (R: index base and pointer; W: dword 0 through the pointer)
//   +0x58 void*        (R: index base, pointer and return value; W: dword 0 through the pointer)
//   +0x68 void*        (W: qword 0)
//   +0x70 uint8_t      (R: bit 0 test; W: and 0xFE)
//
// The index used at 0xa150b is +0x58 when *(void**)(a0+0x40) != 0, otherwise +0x50.
struct A14e0This {
    std::uint8_t pad0x00[0x18];
    void* f18;                       // +0x18 [R/W]
    void* f20;                       // +0x20 [R/W]
    std::uint8_t pad0x28[0x38 - 0x28];
    void* f38;                       // +0x38 [R/W]
    void* f40;                       // +0x40 [R/W]
    std::uint8_t pad0x48[0x50 - 0x48];
    void* f50;                       // +0x50 [R/W]
    void* f58;                       // +0x58 [R/W]
    std::uint8_t pad0x60[0x68 - 0x60];
    void* f68;                       // +0x68 [W]
    std::uint8_t f70;                // +0x70 [R/W]
};                                   // sizeof == 0x78

struct A14e0Layout {
    static_assert(offsetof(A14e0This, f18) == 0x18, "sub_a14e0: f18 at +0x18");
    static_assert(offsetof(A14e0This, f20) == 0x20, "sub_a14e0: f20 at +0x20");
    static_assert(offsetof(A14e0This, f38) == 0x38, "sub_a14e0: f38 at +0x38");
    static_assert(offsetof(A14e0This, f40) == 0x40, "sub_a14e0: f40 at +0x40");
    static_assert(offsetof(A14e0This, f50) == 0x50, "sub_a14e0: f50 at +0x50");
    static_assert(offsetof(A14e0This, f58) == 0x58, "sub_a14e0: f58 at +0x58");
    static_assert(offsetof(A14e0This, f68) == 0x68, "sub_a14e0: f68 at +0x68");
    static_assert(offsetof(A14e0This, f70) == 0x70, "sub_a14e0: f70 at +0x70");
    static_assert(sizeof(A14e0This) == 0x78, "sub_a14e0: object mirror size 0x78");
    static_assert(sizeof(void*) == 8, "sub_a14e0: x64 pointers are 8 bytes");
};

// Data slot (brief rule 68/69, not a callee): RVA 0xF9A8C78 (VA = imageBase() + 0xF9A8C78),
// read at call time by 0xa15aa call qword ptr [0xF9A8C78]; five zero arguments;
// block ends in int3 (noreturn).
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;

// sub_e935700 (0xe935700, size 0x5): lift-classified callee (native_boundary.tsv class 'lift',
// lifted by unit X7.e935700); tail jump to sub_392960. Argument in RCX, result in RAX.
// Called directly through its native symbol, never through a boundary wrapper (brief rule 66).
// Full declaration with layout lives in helpers/sub_e935700.h; forward-declared here so the
// header alone can document the call contract.
void* sub_e935700(void* a0);

// sub_a14e0: exact x64 Microsoft ABI signature of the original.
// RCX = a0; return value in RAX = *(void**)(a0 + 0x58) (the value loaded at 0xa157b).
// No null guards and no SEH: none exist in the original (fail fast).
void* sub_a14e0(void* a0);

} // namespace native
