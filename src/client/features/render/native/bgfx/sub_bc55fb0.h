#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the output record written by 0xbc55fb0 (size 0x1b8 bytes).
// Every offset below is read or written by that function at the stated offset [V] (disassembly
// range [0xbc55fb0, 0xbc56168)). Field roles describe the access pattern observed in the
// disassembly; they are not proven type information.
struct FrameGraphOutput {
    std::uint64_t f00;                    // +0x000 qword = -1
    std::uint8_t  pad08[0x10];            // +0x008..0x017 zero (movups)
    float         f18;                    // +0x018 float 1.0f
    std::uint8_t  pad1c[0x10];            // +0x01C..0x02B zero (movups)
    float         f2c;                    // +0x02C float 1.0f
    std::uint8_t  pad30[0x10];            // +0x030..0x03F zero (movups)
    float         f40;                    // +0x040 float 1.0f
    std::uint8_t  pad44[0x10];            // +0x044..0x053 zero (movups)
    double        f54;                    // +0x054 double from [0xEFD3400]
    std::uint8_t  pad5c[0x10];            // +0x05C..0x06B zero (movups)
    float         f6c;                    // +0x06C float 1.0f
    std::uint8_t  pad70[0x10];            // +0x070..0x07F zero (movups)
    float         f80;                    // +0x080 float 1.0f
    std::uint8_t  pad84[0x10];            // +0x084..0x093 zero (movups)
    float         f94;                    // +0x094 float 1.0f
    std::uint8_t  pad98[0x10];            // +0x098..0x0A7 zero (movups)
    std::uint32_t fa8;                    // +0x0A8 dword 0
    double        fac;                    // +0x0AC double from [0xEFD32D0] (movups 16B)
    double        fbc;                    // +0x0BC double from [0xEFD32F0] (movups 16B)
    double        fcc;                    // +0x0CC double from [0xF0EC830]
    float         fd4;                    // +0x0D4 float 1.0f
    std::uint16_t fd8;                    // +0x0D8 word 7
    std::uint8_t  padda[6];               // +0x0DA..0x0DB padding
    std::uint64_t fdc;                    // +0x0DC qword 0x3F800000FFFFFFFF
    std::uint8_t  pade8[0x30];            // +0x0E8..0x117 zero (three movups)
};

// Read-only data constants read by the function (absolute addresses in the 1.26.62.01 image [V]):
static constexpr std::uintptr_t kDataEFD3400 = 0xEFD3400;   // 0xbc5601d movsd xmm1,[0xEFD3400]
static constexpr std::uintptr_t kDataEFD32D0 = 0xEFD32D0;   // 0xbc56065 movsd xmm0,[0xEFD32D0]
static constexpr std::uintptr_t kDataEFD32F0 = 0xEFD32F0;   // 0xbc56074 movsd xmm0,[0xEFD32F0]
static constexpr std::uintptr_t kDataF0EC830 = 0xF0EC830;   // 0xbc56083 movsd xmm0,[0xF0EC830]
static constexpr std::uintptr_t kDataF4412A0 = 0xF4412A0;   // 0xbc560e4 lea rax,[0xF4412A0]

// Layout constants for the offsets used by 0xbc55fb0 [V]:
static constexpr std::size_t kOutF00Offset = 0x00;
static constexpr std::size_t kOutF18Offset = 0x18;
static constexpr std::size_t kOutF2COffset = 0x2C;
static constexpr std::size_t kOutF40Offset = 0x40;
static constexpr std::size_t kOutF54Offset = 0x54;
static constexpr std::size_t kOutF6COffset = 0x6C;
static constexpr std::size_t kOutF80Offset = 0x80;
static constexpr std::size_t kOutF94Offset = 0x94;
static constexpr std::size_t kOutFA8Offset = 0xA8;
static constexpr std::size_t kOutFACOffset = 0xAC;
static constexpr std::size_t kOutFBCOffset = 0xBC;
static constexpr std::size_t kOutFCCOffset = 0xCC;
static constexpr std::size_t kOutFD4Offset = 0xD4;
static constexpr std::size_t kOutFD8Offset = 0xD8;
static constexpr std::size_t kOutFDCOffset = 0xDC;

static_assert(offsetof(FrameGraphOutput, f00) == kOutF00Offset, "FrameGraphOutput::f00 must be at +0x00");
static_assert(offsetof(FrameGraphOutput, f18) == kOutF18Offset, "FrameGraphOutput::f18 must be at +0x18");
static_assert(offsetof(FrameGraphOutput, f2c) == kOutF2COffset, "FrameGraphOutput::f2c must be at +0x2C");
static_assert(offsetof(FrameGraphOutput, f40) == kOutF40Offset, "FrameGraphOutput::f40 must be at +0x40");
static_assert(offsetof(FrameGraphOutput, f54) == kOutF54Offset, "FrameGraphOutput::f54 must be at +0x54");
static_assert(offsetof(FrameGraphOutput, f6c) == kOutF6COffset, "FrameGraphOutput::f6c must be at +0x6C");
static_assert(offsetof(FrameGraphOutput, f80) == kOutF80Offset, "FrameGraphOutput::f80 must be at +0x80");
static_assert(offsetof(FrameGraphOutput, f94) == kOutF94Offset, "FrameGraphOutput::f94 must be at +0x94");
static_assert(offsetof(FrameGraphOutput, fa8) == kOutFA8Offset, "FrameGraphOutput::fa8 must be at +0xA8");
static_assert(offsetof(FrameGraphOutput, fac) == kOutFACOffset, "FrameGraphOutput::fac must be at +0xAC");
static_assert(offsetof(FrameGraphOutput, fbc) == kOutFBCOffset, "FrameGraphOutput::fbc must be at +0xBC");
static_assert(offsetof(FrameGraphOutput, fcc) == kOutFCCOffset, "FrameGraphOutput::fcc must be at +0xCC");
static_assert(offsetof(FrameGraphOutput, fd4) == kOutFD4Offset, "FrameGraphOutput::fd4 must be at +0xD4");
static_assert(offsetof(FrameGraphOutput, fd8) == kOutFD8Offset, "FrameGraphOutput::fd8 must be at +0xD8");
static_assert(offsetof(FrameGraphOutput, fdc) == kOutFDCOffset, "FrameGraphOutput::fdc must be at +0xDC");
static_assert(sizeof(FrameGraphOutput) == 0x118, "FrameGraphOutput must be 0x118 bytes (0x00..0x117)");

// Stack arguments passed to sub_bc56190
struct Q9 {
    std::uint64_t f0;
    std::uint32_t f8;
};

// 0xbc55fb0, size 0x1b8, returns void* (the out pointer).
// x64 Microsoft ABI: rcx = out, rdx = qptr1, r8 = qptr2, r9 = a3;
// stack arguments (in order): arg5 (float), arg6 (float), arg7 (uint64_t), arg8 (uint8_t), arg9 (uint64_t), arg10 (uint64_t).
extern "C" void* sub_bc55fb0(
    FrameGraphOutput* out,
    const void* qptr1,
    const void* qptr2,
    const float* a3,
    float arg5,
    float arg6,
    std::uint64_t arg7,
    std::uint8_t arg8,
    std::uint64_t arg9,
    std::uint64_t arg10
);

// 0xbc56190 (lift-set callee, already lifted). Called at 0xbc56101.
// x64 ABI: rcx = out, rdx = qptr1, r8 = qptr2, r9 = a3 (ptr to float[3]);
// stack: b (float*), a (float*), m16 (float*), flagptr (void*), q9 (Q9*).
extern "C" void sub_bc56190(
    FrameGraphOutput* out,
    const void* qptr1,
    const void* qptr2,
    const float* a3,
    const float* b,
    const float* a,
    const float* m16,
    const void* flagptr,
    const Q9* q9
);

// 0xebcd900 (boundary, class crt). Called at 0xbc56157.
// Exact signature from disassembly: rcx = out+0x18, rdx = a3, xmm1 = a3[0], xmm2 = a3[2]+a3[0],
// xmm3 = a3[3]+a3[1], xmm4 = arg5, xmm5 = a3[1], stack args: arg6, arg5, a3[1], 0, flag.
// Returns void.
using boundary_ebcd900_fn = void(__cdecl*)(
    void* out18,
    const float* a3,
    float xmm2,   // a3[2]+a3[0]
    float xmm3,   // a3[3]+a3[1]
    float xmm0,   // arg6
    float xmm1,   // a3[0]
    float xmm4,   // arg5
    float xmm5,   // a3[1]
    float stack_a3_1,
    float stack_arg5,
    float stack_arg6,
    std::uint32_t stack_zero,
    std::uint8_t flag
);

} // namespace native