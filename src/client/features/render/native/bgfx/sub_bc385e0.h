#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout recovered from the disassembly of sub_bc385e0 [0xbc385e0, 0xbc3892b),
// size 0x34b, 1.26.62.01. Every offset below is read or written by that function
// at the stated offset [V]; role names are inferred from the access pattern [I].
// The function builds an output object (a0/rcx) from three inputs (a1/rdx, a2/r8,
// a3/r9) and returns a0.

// a0/a3 object: class with vptr at +0x00 and many fields copied from a3.
struct Bc385e0State {
    void* vptr;                                  // +0x00  = data_f440770
    std::uint8_t pad_0x08[0x20];                 // +0x08..0x27  zeroed (2x movups)
    std::uint64_t f28;                           // +0x28  = 0xF
    std::uint64_t f30;                           // +0x30  = 0
    void* f38;                                   // +0x38  address taken, passed to vcall
    std::uint8_t pad_0x40[0x30];                 // +0x40..0x6F  untouched
    std::uint64_t f70;                           // +0x70  = 0, then [a1+0x38] or vcall result
    void* f78;                                   // +0x78  = [a3+0x00]
    std::uint64_t f80;                           // +0x80  = 0 then [a3+0x08]
    std::uint64_t f88;                           // +0x88  = [a3+0x10]
    std::uint8_t pad_0x90[0x10];                 // +0x90..0x9F  zeroed
    std::uint64_t fA0;                           // +0xA0  = 0
    std::uint8_t fA8;                            // +0xA8  = byte [a3+0x30]
    std::uint8_t pad_0xA9[0x0F];                 // +0xA9..0xB7
    std::uint64_t fB0;                           // +0xB0  = [a3+0x38] (conditional)
    std::uint8_t pad_0xB8[0x10];                 // +0xB8..0xC7  = [a3+0x40] (16 bytes)
    std::uint8_t pad_0xC8[0x10];                 // +0xC8..0xD7  = [a3+0x50] (16 bytes)
    std::uint8_t fD8;                            // +0xD8  = 0, then 1 (conditional)
    std::uint8_t pad_0xD9[0x07];                 // +0xD9..0xDF
    std::uint8_t pad_0xE0[0x10];                 // +0xE0..0xEF  = [a3+0x68] (16 bytes)
    std::uint8_t pad_0xF0[0x124];                // +0xF0..0x213 = memcpy(a3+0x78, 0x124)
    std::uint8_t pad_0x214[0x10];                // +0x214..0x223 = [a3+0x19C] (16 bytes)
    std::uint8_t pad_0x224[0x10];                // +0x224..0x233 = [a3+0x1AC] (16 bytes)
    std::uint8_t f234;                           // +0x234 = byte [a3+0x1BC] (conditional)
    float f238;                                  // +0x238 = float [a3+0x1C0] (conditional)
    float f23C;                                  // +0x23C = float [a3+0x1C4] (conditional)
    float f240;                                  // +0x240 = float [a3+0x1C8] (conditional)
    float f244;                                  // +0x244 = float [a3+0x1CC] (conditional)
    std::uint8_t f248;                           // +0x248 = 0 then 1 (conditional)
    std::uint8_t pad_0x249[0x03];                // +0x249..0x24B
    std::uint8_t pad_0x24C[0x10];                // +0x24C..0x25B = [a3+0x1D4] (16 bytes)
    std::uint8_t pad_0x25C[0x10];                // +0x25C..0x26B = [a3+0x1E4] (16 bytes)
    std::uint8_t pad_0x26C[0x10];                // +0x26C..0x279 = [a3+0x1F4] (16 bytes)
    std::uint8_t pad_0x27A[0x10];                // +0x27A..0x289 = [a3+0x202] (16 bytes)
    std::uint8_t f28C;                           // +0x28C = 0 then 1
    std::uint8_t pad_0x28D[0x03];                // +0x28D..0x28F
    void* f290;                                  // +0x290  small-string buffer ptr (heap) or SSO base
    std::uint64_t f298;                          // +0x298
    std::uint64_t f2A0;                          // +0x2A0  size (SSO only)
    std::uint64_t f2A8;                          // +0x2A8  capacity (SSO only)
};
static_assert(offsetof(Bc385e0State, vptr) == 0x00, "bc385e0: vptr at +0x00");
static_assert(offsetof(Bc385e0State, f28) == 0x28, "bc385e0: f28 at +0x28");
static_assert(offsetof(Bc385e0State, f30) == 0x30, "bc385e0: f30 at +0x30");
static_assert(offsetof(Bc385e0State, f38) == 0x38, "bc385e0: f38 at +0x38");
static_assert(offsetof(Bc385e0State, f70) == 0x70, "bc385e0: f70 at +0x70");
static_assert(offsetof(Bc385e0State, f78) == 0x78, "bc385e0: f78 at +0x78");
static_assert(offsetof(Bc385e0State, f80) == 0x80, "bc385e0: f80 at +0x80");
static_assert(offsetof(Bc385e0State, f88) == 0x88, "bc385e0: f88 at +0x88");
static_assert(offsetof(Bc385e0State, pad_0x90) == 0x90, "bc385e0: pad_0x90 at +0x90");
static_assert(offsetof(Bc385e0State, fA0) == 0xA0, "bc385e0: fA0 at +0xA0");
static_assert(offsetof(Bc385e0State, fA8) == 0xA8, "bc385e0: fA8 at +0xA8");
static_assert(offsetof(Bc385e0State, fB0) == 0xB0, "bc385e0: fB0 at +0xB0");
static_assert(offsetof(Bc385e0State, pad_0xB8) == 0xB8, "bc385e0: pad_0xB8 at +0xB8");
static_assert(offsetof(Bc385e0State, pad_0xC8) == 0xC8, "bc385e0: pad_0xC8 at +0xC8");
static_assert(offsetof(Bc385e0State, fD8) == 0xD8, "bc385e0: fD8 at +0xD8");
static_assert(offsetof(Bc385e0State, pad_0xE0) == 0xE0, "bc385e0: pad_0xE0 at +0xE0");
static_assert(offsetof(Bc385e0State, pad_0xF0) == 0xF0, "bc385e0: pad_0xF0 at +0xF0");
static_assert(offsetof(Bc385e0State, pad_0x214) == 0x214, "bc385e0: pad_0x214 at +0x214");
static_assert(offsetof(Bc385e0State, pad_0x224) == 0x224, "bc385e0: pad_0x224 at +0x224");
static_assert(offsetof(Bc385e0State, f234) == 0x234, "bc385e0: f234 at +0x234");
static_assert(offsetof(Bc385e0State, f238) == 0x238, "bc385e0: f238 at +0x238");
static_assert(offsetof(Bc385e0State, f23C) == 0x23C, "bc385e0: f23C at +0x23C");
static_assert(offsetof(Bc385e0State, f240) == 0x240, "bc385e0: f240 at +0x240");
static_assert(offsetof(Bc385e0State, f244) == 0x244, "bc385e0: f244 at +0x244");
static_assert(offsetof(Bc385e0State, f248) == 0x248, "bc385e0: f248 at +0x248");
static_assert(offsetof(Bc385e0State, pad_0x24C) == 0x24C, "bc385e0: pad_0x24C at +0x24C");
static_assert(offsetof(Bc385e0State, pad_0x25C) == 0x25C, "bc385e0: pad_0x25C at +0x25C");
static_assert(offsetof(Bc385e0State, pad_0x26C) == 0x26C, "bc385e0: pad_0x26C at +0x26C");
static_assert(offsetof(Bc385e0State, pad_0x27A) == 0x27A, "bc385e0: pad_0x27A at +0x27A");
static_assert(offsetof(Bc385e0State, f28C) == 0x28C, "bc385e0: f28C at +0x28C");
static_assert(offsetof(Bc385e0State, f290) == 0x290, "bc385e0: f290 at +0x290");
static_assert(offsetof(Bc385e0State, f298) == 0x298, "bc385e0: f298 at +0x298");
static_assert(offsetof(Bc385e0State, f2A0) == 0x2A0, "bc385e0: f2A0 at +0x2A0");
static_assert(offsetof(Bc385e0State, f2A8) == 0x2A8, "bc385e0: f2A8 at +0x2A8");
static_assert(sizeof(Bc385e0State) == 0x2B0, "bc385e0: state size 0x2B0");

// a2: small-string-like { char* data @ +0x00, uint64_t size @ +0x08 }.
struct Bc385e0SmallString {
    void* data;                                  // +0x00
    std::uint64_t size;                          // +0x08
};
static_assert(offsetof(Bc385e0SmallString, data) == 0x00, "bc385e0: small-string data at +0x00");
static_assert(offsetof(Bc385e0SmallString, size) == 0x08, "bc385e0: small-string size at +0x08");
static_assert(sizeof(Bc385e0SmallString) == 0x10, "bc385e0: small-string size 0x10");

// x64 Microsoft ABI: rcx = a0 (out), rdx = a1, r8 = a2 (small string), r9 = a3 (source object).
// Returns a0 in rax.
extern "C" void* sub_bc385e0(void* a0, void* a1, void* a2, void* a3);

} // namespace native::bgfx
