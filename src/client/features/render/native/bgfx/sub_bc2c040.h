#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the object initialised by sub_0xbc2c040 (self = rcx), reverse-engineered
// from the disassembly of [0xbc2c040, 0xbc2c205), Minecraft Windows 1.26.62.01.
// Only offsets the function itself touches are declared; the rest is padding.
// Packed so offsetof matches the disassembly offsets exactly.
#pragma pack(push, 1)
struct sub_bc2c040_state {
    uint64_t vtable;              // +0x00  written 0x14F43F9C0 (vtable ptr)   // 0xbc2c086  mov [rcx],rax
    uint8_t  f0x08[0x10];         // +0x08  16-byte zero store               // 0xbc2c06b  movups [rcx+8],xmm0
    uint8_t  f0x18[0x10];         // +0x18  16-byte zero store               // 0xbc2c067  movups [rcx+0x18],xmm0
    uint64_t f0x28;               // +0x28  written 0xF                     // 0xbc2c06f  mov qword ptr [rcx+0x28],0xF
    uint64_t f0x30;               // +0x30  written 0                       // 0xbc2c077  mov qword ptr [rcx+0x30],0
    uint8_t  f0x38[0x38];         // +0x38  opaque region [0x38,0x70); its address is passed
                                   //        as arg2 (rdx) to the two vtable calls        // 0xbc2c089  lea r15,[rcx+0x38]
    uint64_t f0x70;               // +0x70  written 0, then the result of the first
                                   //        vtable call                               // 0xbc2c08d / 0xbc2c0bc
    sub_bc2be20_state be20;       // +0x78  sub-object copied by sub_0xbc2be20 (0x2A0 bytes)
                                   //        0x78 + 0x2A0 = 0x318                     // 0xbc2c0f6  call 0xBC2BE20
    uint8_t*  buf;                // +0x318 buffer pointer (16-byte zeroed, then assigned)
                                   //                                        // 0xbc2c10b / 0xbc2c1a5
    uint64_t size;                // +0x328 written with a2->field_8                  // 0xbc2c1af  mov [r14+0x328],rsi
    uint64_t cap;                 // +0x330 written with the capacity (r12)            // 0xbc2c1b6  mov [r14+0x330],r12
};
#pragma pack(pop)

// Layout constants (one per offset the function touches) with static_asserts.
static constexpr size_t kOff0x00  = 0x00;
static constexpr size_t kOff0x08  = 0x08;
static constexpr size_t kOff0x18  = 0x18;
static constexpr size_t kOff0x28  = 0x28;
static constexpr size_t kOff0x30  = 0x30;
static constexpr size_t kOff0x38  = 0x38;
static constexpr size_t kOff0x70  = 0x70;
static constexpr size_t kOff0x78  = 0x78;
static constexpr size_t kOff0x318 = 0x318;
static constexpr size_t kOff0x328 = 0x328;
static constexpr size_t kOff0x330 = 0x330;

static_assert(offsetof(sub_bc2c040_state, vtable)  == kOff0x00,  "sub_0xbc2c040 touches self+0x00");
static_assert(offsetof(sub_bc2c040_state, f0x08)  == kOff0x08,  "sub_0xbc2c040 touches self+0x08");
static_assert(offsetof(sub_bc2c040_state, f0x18)  == kOff0x18,  "sub_0xbc2c040 touches self+0x18");
static_assert(offsetof(sub_bc2c040_state, f0x28)  == kOff0x28,  "sub_0xbc2c040 touches self+0x28");
static_assert(offsetof(sub_bc2c040_state, f0x30)  == kOff0x30,  "sub_0xbc2c040 touches self+0x30");
static_assert(offsetof(sub_bc2c040_state, f0x38)  == kOff0x38,  "sub_0xbc2c040 takes the address of self+0x38");
static_assert(offsetof(sub_bc2c040_state, f0x70)  == kOff0x70,  "sub_0xbc2c040 touches self+0x70");
static_assert(offsetof(sub_bc2c040_state, be20)   == kOff0x78,  "sub_0xbc2c040 passes &self+0x78 to sub_bc2be20");
static_assert(offsetof(sub_bc2c040_state, buf)    == kOff0x318, "sub_0xbc2c040 touches self+0x318");
static_assert(offsetof(sub_bc2c040_state, size)   == kOff0x328, "sub_0xbc2c040 touches self+0x328");
static_assert(offsetof(sub_bc2c040_state, cap)    == kOff0x330, "sub_0xbc2c040 touches self+0x330");
static_assert(sizeof(sub_bc2c040_state) >= 0x338, "sub_0xbc2c040 object spans at least [0x00,0x338)");

// sub_0xbc2c040(sub_bc2c040_state* a0 = rcx, void* a1 = rdx, void* a2 = r8, void* a3 = r9)
//   -> void* (rax = a0).
// Minecraft Windows 1.26.62.01, function [0xbc2c040, 0xbc2c205), size 0x1c5.
void* sub_bc2c040(sub_bc2c040_state* a0, void* a1, void* a2, void* a3);

} // namespace native::bgfx