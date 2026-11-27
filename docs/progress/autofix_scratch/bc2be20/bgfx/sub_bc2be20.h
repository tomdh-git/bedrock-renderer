#pragma once
#include <cstddef>
#include <cstdint>
// Forward declarations (autofix)
struct sub_bc2be20_state;


namespace native::bgfx {

// Layout of the object copied by sub_0xbc2be20 (dst = rcx, src = rdx), reverse-engineered

// from the disassembly of [0xbc2be20, 0xbc2c00c), Minecraft Windows 1.26.62.01. Only offsets

// the function touches are declared; the rest is padding. The struct is packed so offsetof

// matches the disassembly offsets exactly (field_0x283 is read/written by movups at an

// unaligned offset).

#pragma pack(push, 1)
struct sub_bc2be20_state {
    uint64_t field_0x00;          // +0x00  qword copy src->dst

    uint64_t field_0x08;          // +0x08  qword copy src->dst; then src+0x8 zeroed

    uint64_t field_0x10;          // +0x10  qword copy src->dst

    uint8_t  field_0x18[0x10];    // +0x18  16-byte zero store to dst; [0x18,0x28)

    uint64_t field_0x28;          // +0x28  dst written 0

    uint8_t  pad_0x2C[4];         // +0x2C

    uint8_t  field_0x30;          // +0x30  byte copy src->dst (switch tag at +0x70 is separate)

    uint8_t  pad_0x31[7];         // +0x31

    uint8_t  field_0x38[16];      // +0x38  16-byte copy src->dst

    uint8_t  field_0x48[16];      // +0x48  16-byte copy src->dst; then src+0x48 zeroed

    uint64_t field_0x58;          // +0x58  qword copy src->dst

    uint64_t field_0x60;          // +0x60  pointer field: switch on byte +0x70 copies it

    uint64_t field_0x68;          // +0x68  pointer field; its pointee+8 is addref'd

    uint8_t  field_0x70;          // +0x70  u8 switch tag; dst+0x70 = tag (<=3) else 0xFF

    uint8_t  pad_0x71[7];         // +0x71

    uint8_t  field_0x78[16];      // +0x78  16-byte copy src->dst

    uint64_t field_0x88;          // +0x88  qword copy src->dst

    uint64_t field_0x90;          // +0x90  qword copy src->dst

    uint8_t  field_0x98[0x18];    // +0x98  sub_e869ff0(&dst+0x98, &src+0x98) operates here

    uint64_t field_0x110;         // +0x110 qword move src->dst, then src+0x110 = 0

    uint8_t  field_0x118[0x124];  // +0x118 sub_5669770(&dst+0x118, &src+0x118) operates here

    uint8_t  field_0x23C[16];     // +0x23C 16-byte copy src->dst

    uint32_t field_0x24C;         // +0x24C dword copy src->dst

    uint8_t  field_0x250;         // +0x250 byte copy src->dst

    uint8_t  pad_0x251[3];        // +0x251

    float    field_0x254;         // +0x254 float (movss) copy src->dst

    float    field_0x258;         // +0x258 float copy src->dst

    float    field_0x25C;         // +0x25C float copy src->dst

    float    field_0x260;         // +0x260 float copy src->dst

    uint8_t  field_0x264[16];     // +0x264 16-byte copy src->dst

    uint8_t  field_0x274[15];     // +0x274 [0x274,0x283) of the 16-byte copy src->dst

    uint8_t  field_0x283[16];     // +0x283 [0x283,0x293) 16-byte copy src->dst (overlaps +0x274 tail)

    uint8_t  pad_0x293[1];        // +0x293

    uint64_t field_0x294;         // +0x294 qword copy src->dst

};                                // sizeof == 0x2A0

#pragma pack(pop)

// Layout constants (one per offset the function touches) with static_asserts.

static constexpr size_t kOff0x00  = 0x00;
static constexpr size_t kOff0x08  = 0x08;
static constexpr size_t kOff0x10  = 0x10;
static constexpr size_t kOff0x18  = 0x18;
static constexpr size_t kOff0x28  = 0x28;
static constexpr size_t kOff0x30  = 0x30;
static constexpr size_t kOff0x38  = 0x38;
static constexpr size_t kOff0x40  = 0x40;
static constexpr size_t kOff0x48  = 0x48;
static constexpr size_t kOff0x58  = 0x58;
static constexpr size_t kOff0x60  = 0x60;
static constexpr size_t kOff0x68  = 0x68;
static constexpr size_t kOff0x70  = 0x70;
static constexpr size_t kOff0x78  = 0x78;
static constexpr size_t kOff0x88  = 0x88;
static constexpr size_t kOff0x90  = 0x90;
static constexpr size_t kOff0x98  = 0x98;
static constexpr size_t kOff0x110 = 0x110;
static constexpr size_t kOff0x118 = 0x118;
static constexpr size_t kOff0x23C = 0x23C;
static constexpr size_t kOff0x24C = 0x24C;
static constexpr size_t kOff0x250 = 0x250;
static constexpr size_t kOff0x254 = 0x254;
static constexpr size_t kOff0x258 = 0x258;
static constexpr size_t kOff0x25C = 0x25C;
static constexpr size_t kOff0x260 = 0x260;
static constexpr size_t kOff0x264 = 0x264;
static constexpr size_t kOff0x274 = 0x274;
static constexpr size_t kOff0x283 = 0x283;
static constexpr size_t kOff0x294 = 0x294;

static_assert(offsetof(sub_bc2be20_state, field_0x00)  == kOff0x00,  "sub_0xbc2be20 touches self+0x00");
static_assert(offsetof(sub_bc2be20_state, field_0x08)  == kOff0x08,  "sub_0xbc2be20 touches self+0x08");
static_assert(offsetof(sub_bc2be20_state, field_0x10)  == kOff0x10,  "sub_0xbc2be20 touches self+0x10");
static_assert(offsetof(sub_bc2be20_state, field_0x18)  == kOff0x18,  "sub_0xbc2be20 touches self+0x18");
static_assert(offsetof(sub_bc2be20_state, field_0x28)  == kOff0x28,  "sub_0xbc2be20 touches self+0x28");
static_assert(offsetof(sub_bc2be20_state, field_0x30)  == kOff0x30,  "sub_0xbc2be20 touches self+0x30");
static_assert(offsetof(sub_bc2be20_state, field_0x38)  == kOff0x38,  "sub_0xbc2be20 touches self+0x38");
static_assert(offsetof(sub_bc2be20_state, field_0x40)  == kOff0x40,  "sub_0xbc2be20 touches self+0x40");
static_assert(offsetof(sub_bc2be20_state, field_0x48)  == kOff0x48,  "sub_0xbc2be20 touches self+0x48");
static_assert(offsetof(sub_bc2be20_state, field_0x58)  == kOff0x58,  "sub_0xbc2be20 touches self+0x58");
static_assert(offsetof(sub_bc2be20_state, field_0x60)  == kOff0x60,  "sub_0xbc2be20 touches self+0x60");
static_assert(offsetof(sub_bc2be20_state, field_0x68)  == kOff0x68,  "sub_0xbc2be20 touches self+0x68");
static_assert(offsetof(sub_bc2be20_state, field_0x70)  == kOff0x70,  "sub_0xbc2be20 touches self+0x70");
static_assert(offsetof(sub_bc2be20_state, field_0x78)  == kOff0x78,  "sub_0xbc2be20 touches self+0x78");
static_assert(offsetof(sub_bc2be20_state, field_0x88)  == kOff0x88,  "sub_0xbc2be20 touches self+0x88");
static_assert(offsetof(sub_bc2be20_state, field_0x90)  == kOff0x90,  "sub_0xbc2be20 touches self+0x90");
static_assert(offsetof(sub_bc2be20_state, field_0x98)  == kOff0x98,  "sub_0xbc2be20 passes &self+0x98 to sub_e869ff0");
static_assert(offsetof(sub_bc2be20_state, field_0x110) == kOff0x110, "sub_0xbc2be20 touches self+0x110");
static_assert(offsetof(sub_bc2be20_state, field_0x118) == kOff0x118, "sub_0xbc2be20 passes &self+0x118 to sub_5669770");
static_assert(offsetof(sub_bc2be20_state, field_0x23C) == kOff0x23C, "sub_0xbc2be20 touches self+0x23C");
static_assert(offsetof(sub_bc2be20_state, field_0x24C) == kOff0x24C, "sub_0xbc2be20 touches self+0x24C");
static_assert(offsetof(sub_bc2be20_state, field_0x250) == kOff0x250, "sub_0xbc2be20 touches self+0x250");
static_assert(offsetof(sub_bc2be20_state, field_0x254) == kOff0x254, "sub_0xbc2be20 touches self+0x254");
static_assert(offsetof(sub_bc2be20_state, field_0x258) == kOff0x258, "sub_0xbc2be20 touches self+0x258");
static_assert(offsetof(sub_bc2be20_state, field_0x25C) == kOff0x25C, "sub_0xbc2be20 touches self+0x25C");
static_assert(offsetof(sub_bc2be20_state, field_0x260) == kOff0x260, "sub_0xbc2be20 touches self+0x260");
static_assert(offsetof(sub_bc2be20_state, field_0x264) == kOff0x264, "sub_0xbc2be20 touches self+0x264");
static_assert(offsetof(sub_bc2be20_state, field_0x274) == kOff0x274, "sub_0xbc2be20 touches self+0x274");
static_assert(offsetof(sub_bc2be20_state, field_0x283) == kOff0x283, "sub_0xbc2be20 touches self+0x283");
static_assert(offsetof(sub_bc2be20_state, field_0x294) == kOff0x294, "sub_0xbc2be20 touches self+0x294");
static_assert(sizeof(sub_bc2be20_state) == 0x2A0, "sub_0xbc2be20 object size");

// sub_0xbc2be20(sub_bc2be20_state* dst = rcx, sub_bc2be20_state* src = rdx) -> sub_bc2be20_state* (rax = dst).

sub_bc2be20_state* sub_bc2be20(sub_bc2be20_state* dst, sub_bc2be20_state* src);

// Both callees of sub_0xbc2be20 are class `lift` in docs/data/native_boundary.tsv

// (not boundary): they are called through their native symbols and linked at the

// milestone gate. Forward declarations per repository convention.

namespace native {
void sub_5669770(void* dst, const void* src);
void sub_e869ff0(void* dst, const void* src);
}

} // namespace native::bgfx

