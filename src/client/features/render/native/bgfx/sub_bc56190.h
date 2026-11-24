#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the output record written by 0xbc56190 ("VV frame-graph builder", size 0x477 bytes).
// Every offset below is read or written by that function at the stated offset [V] (disassembly
// range [0xbc56190, 0xbc56607)). Field roles describe the access pattern observed in the
// disassembly; they are not proven type information.
struct FrameOutput {
    std::uint8_t  pad00[0x08];          // +0x00
    std::uintptr_t f08;                  // +0x08  qword stored from *arg2 (rdx)
    std::uintptr_t f10;                  // +0x10  qword stored from *arg3 (r8)
    std::uint8_t  pad18[0x40];          // +0x18 .. 0x57
    float         f58;                   // +0x58
    float         f5c;                   // +0x5C
    float         f60;                   // +0x60  (xorps mask value)
    std::uint32_t f64;                   // +0x64 (constant 0)
    float         f68;                   // +0x68
    float         f6c;                   // +0x6C
    float         f70;                   // +0x70  (xorps mask value)
    std::uint32_t f74;                   // +0x74 (constant 0)
    float         f78;                   // +0x78
    float         f7c;                   // +0x7C
    float         f80;                   // +0x80  (xorps mask value)
    std::uint32_t f84;                   // +0x84 (constant 0)
    float         f88;                   // +0x88 (movlps lo)
    float         f8c;                   // +0x8C (movlps hi)
    float         f90;                   // +0x90
    std::uint32_t f94;                   // +0x94 (constant 0x3F800000 = 1.0f)
    float         f98;                   // +0x98  a3+0x0
    float         f9c;                   // +0x9C  a3+0x4
    float         fa0;                   // +0xA0  a3+0x8
    float         fa4;                   // +0xA4  arg5+0x0
    float         fa8;                   // +0xA8  arg5+0x4
    float         fac;                   // +0xAC  arg5+0x8
    float         fb0;                   // +0xB0 (movlps lo)
    float         fb4;                   // +0xB4 (movlps hi)
    float         fb8;                   // +0xB8
    float         fbc;                   // +0xBC  arg6+0x0
    float         fc0;                   // +0xC0  arg6+0x4
    float         fc4;                   // +0xC4  arg6+0x8
    float         fc8;                   // +0xC8
    float         fcc;                   // +0xCC (movlps lo)
    float         fcd;                   // +0xD0 (movlps hi)
    float         fd4;                   // +0xD4
    float         fd8[4];                // +0xD8  16-byte copy of arg7 (movups)
    std::uintptr_t f_e8;                 // +0xE8  pointer read as qword, passed to sub_3bafdc0
    std::uint8_t  padf0[8];             // +0xF0 (zeroed together with f_e8 on one path)
    std::uint64_t f_f8;                  // +0xF8  (zeroed together with f_e8 on one path; read before the zero)
    std::uint8_t  f_100;                 // +0x100 flag byte
    std::uint8_t  pad101[7];            // +0x101 .. 0x107
    std::uint64_t f_108;                // +0x108 q9->f0
    std::uint32_t f_110;                // +0x110 q9->f8
    std::uint8_t  pad114[4];            // +0x114 .. 0x117
};

// Stack-passed argument 9 of 0xbc56190: { qword f0, dword f8 } copied to out+0x108 / out+0x110.
struct Q9 {
    std::uint64_t f0;
    std::uint32_t f8;
};

// Read-only data constants read by the function (absolute addresses in the 1.26.62.01 image [V]):
static constexpr std::uintptr_t kRecipNumeratorAddr = 0xEEC8060;  // 0xbc56296 movss xmm0,[0xEEC8060]
static constexpr std::uintptr_t kSignMaskAddr = 0xEF3F050;        // 0xbc56424 movaps xmm10,[0xEF3F050]
static constexpr std::uintptr_t kFailSlotAddr = 0xF9A8C78;        // 0xbc56600 call qword ptr [0xF9A8C78] (import slot)

// Layout constants for the offsets used by 0xbc56190 [V]:
static constexpr std::size_t kOutF08Offset = 0x08;
static constexpr std::size_t kOutF10Offset = 0x10;
static constexpr std::size_t kOutF58Offset = 0x58;
static constexpr std::size_t kOutF5COffset = 0x5C;
static constexpr std::size_t kOutF60Offset = 0x60;
static constexpr std::size_t kOutF64Offset = 0x64;
static constexpr std::size_t kOutF68Offset = 0x68;
static constexpr std::size_t kOutF6COffset = 0x6C;
static constexpr std::size_t kOutF70Offset = 0x70;
static constexpr std::size_t kOutF74Offset = 0x74;
static constexpr std::size_t kOutF78Offset = 0x78;
static constexpr std::size_t kOutF7COffset = 0x7C;
static constexpr std::size_t kOutF80Offset = 0x80;
static constexpr std::size_t kOutF84Offset = 0x84;
static constexpr std::size_t kOutF88Offset = 0x88;
static constexpr std::size_t kOutF8COffset = 0x8C;
static constexpr std::size_t kOutF90Offset = 0x90;
static constexpr std::size_t kOutF94Offset = 0x94;
static constexpr std::size_t kOutF98Offset = 0x98;
static constexpr std::size_t kOutF9COffset = 0x9C;
static constexpr std::size_t kOutFA0Offset = 0xA0;
static constexpr std::size_t kOutFA4Offset = 0xA4;
static constexpr std::size_t kOutFA8Offset = 0xA8;
static constexpr std::size_t kOutFACOffset = 0xAC;
static constexpr std::size_t kOutFB0Offset = 0xB0;
static constexpr std::size_t kOutFB4Offset = 0xB4;
static constexpr std::size_t kOutFB8Offset = 0xB8;
static constexpr std::size_t kOutFBCOffset = 0xBC;
static constexpr std::size_t kOutFC0Offset = 0xC0;
static constexpr std::size_t kOutFC4Offset = 0xC4;
static constexpr std::size_t kOutFC8Offset = 0xC8;
static constexpr std::size_t kOutFCCOffset = 0xCC;
static constexpr std::size_t kOutFCDOffset = 0xD0;
static constexpr std::size_t kOutFD4Offset = 0xD4;
static constexpr std::size_t kOutFD8Offset = 0xD8;
static constexpr std::size_t kOutFE8Offset = 0xE8;
static constexpr std::size_t kOutFF8Offset = 0xF8;
static constexpr std::size_t kOutF100Offset = 0x100;
static constexpr std::size_t kOutF108Offset = 0x108;
static constexpr std::size_t kOutF110Offset = 0x110;

static_assert(offsetof(FrameOutput, f08) == kOutF08Offset, "FrameOutput::f08 must be at +0x08");
static_assert(offsetof(FrameOutput, f10) == kOutF10Offset, "FrameOutput::f10 must be at +0x10");
static_assert(offsetof(FrameOutput, f58) == kOutF58Offset, "FrameOutput::f58 must be at +0x58");
static_assert(offsetof(FrameOutput, f5c) == kOutF5COffset, "FrameOutput::f5c must be at +0x5C");
static_assert(offsetof(FrameOutput, f60) == kOutF60Offset, "FrameOutput::f60 must be at +0x60");
static_assert(offsetof(FrameOutput, f64) == kOutF64Offset, "FrameOutput::f64 must be at +0x64");
static_assert(offsetof(FrameOutput, f68) == kOutF68Offset, "FrameOutput::f68 must be at +0x68");
static_assert(offsetof(FrameOutput, f6c) == kOutF6COffset, "FrameOutput::f6c must be at +0x6C");
static_assert(offsetof(FrameOutput, f70) == kOutF70Offset, "FrameOutput::f70 must be at +0x70");
static_assert(offsetof(FrameOutput, f74) == kOutF74Offset, "FrameOutput::f74 must be at +0x74");
static_assert(offsetof(FrameOutput, f78) == kOutF78Offset, "FrameOutput::f78 must be at +0x78");
static_assert(offsetof(FrameOutput, f7c) == kOutF7COffset, "FrameOutput::f7c must be at +0x7C");
static_assert(offsetof(FrameOutput, f80) == kOutF80Offset, "FrameOutput::f80 must be at +0x80");
static_assert(offsetof(FrameOutput, f84) == kOutF84Offset, "FrameOutput::f84 must be at +0x84");
static_assert(offsetof(FrameOutput, f88) == kOutF88Offset, "FrameOutput::f88 must be at +0x88");
static_assert(offsetof(FrameOutput, f8c) == kOutF8COffset, "FrameOutput::f8c must be at +0x8C");
static_assert(offsetof(FrameOutput, f90) == kOutF90Offset, "FrameOutput::f90 must be at +0x90");
static_assert(offsetof(FrameOutput, f94) == kOutF94Offset, "FrameOutput::f94 must be at +0x94");
static_assert(offsetof(FrameOutput, f98) == kOutF98Offset, "FrameOutput::f98 must be at +0x98");
static_assert(offsetof(FrameOutput, f9c) == kOutF9COffset, "FrameOutput::f9c must be at +0x9C");
static_assert(offsetof(FrameOutput, fa0) == kOutFA0Offset, "FrameOutput::fa0 must be at +0xA0");
static_assert(offsetof(FrameOutput, fa4) == kOutFA4Offset, "FrameOutput::fa4 must be at +0xA4");
static_assert(offsetof(FrameOutput, fa8) == kOutFA8Offset, "FrameOutput::fa8 must be at +0xA8");
static_assert(offsetof(FrameOutput, fac) == kOutFACOffset, "FrameOutput::fac must be at +0xAC");
static_assert(offsetof(FrameOutput, fb0) == kOutFB0Offset, "FrameOutput::fb0 must be at +0xB0");
static_assert(offsetof(FrameOutput, fb4) == kOutFB4Offset, "FrameOutput::fb4 must be at +0xB4");
static_assert(offsetof(FrameOutput, fb8) == kOutFB8Offset, "FrameOutput::fb8 must be at +0xB8");
static_assert(offsetof(FrameOutput, fbc) == kOutFBCOffset, "FrameOutput::fbc must be at +0xBC");
static_assert(offsetof(FrameOutput, fc0) == kOutFC0Offset, "FrameOutput::fc0 must be at +0xC0");
static_assert(offsetof(FrameOutput, fc4) == kOutFC4Offset, "FrameOutput::fc4 must be at +0xC4");
static_assert(offsetof(FrameOutput, fc8) == kOutFC8Offset, "FrameOutput::fc8 must be at +0xC8");
static_assert(offsetof(FrameOutput, fcc) == kOutFCCOffset, "FrameOutput::fcc must be at +0xCC");
static_assert(offsetof(FrameOutput, fcd) == kOutFCDOffset, "FrameOutput::fcd must be at +0xD0");
static_assert(offsetof(FrameOutput, fd4) == kOutFD4Offset, "FrameOutput::fd4 must be at +0xD4");
static_assert(offsetof(FrameOutput, fd8) == kOutFD8Offset, "FrameOutput::fd8 must be at +0xD8");
static_assert(offsetof(FrameOutput, f_e8) == kOutFE8Offset, "FrameOutput::f_e8 must be at +0xE8");
static_assert(offsetof(FrameOutput, f_f8) == kOutFF8Offset, "FrameOutput::f_f8 must be at +0xF8");
static_assert(offsetof(FrameOutput, f_100) == kOutF100Offset, "FrameOutput::f_100 must be at +0x100");
static_assert(offsetof(FrameOutput, f_108) == kOutF108Offset, "FrameOutput::f_108 must be at +0x108");
static_assert(offsetof(FrameOutput, f_110) == kOutF110Offset, "FrameOutput::f_110 must be at +0x110");
static_assert(sizeof(FrameOutput) == 0x118, "FrameOutput must be 0x118 bytes");
static_assert(sizeof(Q9) == 0x10, "Q9 must be 0x10 bytes");

// 0xbc56190, size 0x477, returns void.
// x64 Microsoft ABI: rcx = out, rdx = qptr1, r8 = qptr2, r9 = a3; stack arguments (in order): b,
// a, m16, flagptr, q9.
extern "C" void sub_bc56190(FrameOutput* out, const void* qptr1, const void* qptr2,
    const float* a3, const float* b, const float* a, const float* m16,
    const void* flagptr, const Q9* q9);

// 0xe935700 (size 0x5): `jmp 0x392960` forwarder. Classified lift in
// docs/data/native_boundary.tsv (class lift, auto-unresolved->lift). Called at 0xbc56577 with
// rcx/rdx set per path; return value unused here. Forward-declared per the lift rules: called
// like any lifted function, no boundary wrapper.
extern "C" void sub_e935700(std::uintptr_t a1, std::uintptr_t a2);

} // namespace native
