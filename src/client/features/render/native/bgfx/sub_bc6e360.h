#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the object passed to sub_0xbc6e360 in rcx (this), reverse-engineered from the
// disassembly of [0xbc6e360, 0xbc6e54b), Minecraft Windows 1.26.62.01. Only offsets the
// function touches are declared; the rest is padding. Verified against the disassembly.
struct sub_bc6e360_state {
    uint8_t pad_0x000[0x14A];                    // +0x000
    uint16_t field_0x14A;                        // +0x14A  word array base; element (u8)idx is at +0x14A+idx*0x14 (word@0, byte@9)
    uint8_t pad_0x14C[0x153 - 0x14C];            // +0x14C..0x152
    uint8_t field_0x153;                         // +0x153  byte array base; element (u8)idx is at +0x153+idx*0x14
    uint8_t pad_0x154[0x680 - 0x154];            // +0x154..0x67F
    void* field_0x680;                           // +0x680  entry-array pointer: entry = {void* ptr; u32 count} at stride 0x10; u32 counter at array base + 0x410
    uint8_t field_0x688;                         // +0x688  u8 flag, written 1 just before return
    uint8_t pad_0x689[1];                        // +0x689
};                                               // sizeof == 0x68A

// Entry layout at field_0x680 + idx*0x10.
struct sub_bc6e360_entry {
    void* field_0x00;                            // +0x00  item buffer pointer
    uint32_t field_0x08;                         // +0x08  item count
};                                               // sizeof == 0x10

// Item layout within the entry buffer, stride 0x14.
struct sub_bc6e360_item {
    uint32_t field_0x00;                         // +0x00  dword: a4[a5*k], forced to 0x20000000 when bit 0x20000000 is set
    uint8_t pad_0x04[0x6];                       // +0x04..0x09
    uint16_t field_0x0A;                         // +0x0A  word: *(u16*)((u8*)a2 + a3*k)
    uint8_t pad_0x0C[4];                         // +0x0C..0x0F
    uint32_t field_0x10;                         // +0x10  dword: written 0x3000000
};                                               // sizeof == 0x14

static_assert(offsetof(sub_bc6e360_state, field_0x14A) == 0x14A, "sub_0xbc6e360 writes word state+0x14A+idx*0x14");
static_assert(offsetof(sub_bc6e360_state, field_0x153) == 0x153, "sub_0xbc6e360 writes byte state+0x153+idx*0x14");
static_assert(offsetof(sub_bc6e360_state, field_0x680) == 0x680, "sub_0xbc6e360 reads/writes state+0x680");
static_assert(offsetof(sub_bc6e360_state, field_0x688) == 0x688, "sub_0xbc6e360 writes byte state+0x688");
static_assert(sizeof(sub_bc6e360_state) == 0x68A, "sub_0xbc6e360 object size");
static_assert(offsetof(sub_bc6e360_entry, field_0x00) == 0x00, "entry buffer pointer at +0x00");
static_assert(offsetof(sub_bc6e360_entry, field_0x08) == 0x08, "entry count at +0x08");
static_assert(sizeof(sub_bc6e360_entry) == 0x10, "entry stride 0x10");
static_assert(offsetof(sub_bc6e360_item, field_0x00) == 0x00, "item dword at +0x00");
static_assert(offsetof(sub_bc6e360_item, field_0x0A) == 0x0A, "item word at +0x0A");
static_assert(offsetof(sub_bc6e360_item, field_0x10) == 0x10, "item dword at +0x10");
static_assert(sizeof(sub_bc6e360_item) == 0x14, "item stride 0x14");

// sub_0xbc6e360(state* a0 = rcx, u32 a1 = edx, uint16_t* a2 = r8, u32 a3 = r9,
//                u32* a4 = [rsp+0xA0], u32 a5 = [rsp+0xA8], u32 a6 = [rsp+0xB0], u32 a7 = [rsp+0xB8]) -> void
// Minecraft Windows 1.26.62.01. [0xbc6e360, 0xbc6e54b)
void sub_bc6e360(sub_bc6e360_state* a0, uint32_t a1, uint16_t* a2, uint32_t a3,
                 uint32_t* a4, uint32_t a5, uint32_t a6, uint32_t a7);

} // namespace native::bgfx
