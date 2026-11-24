#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the object passed to sub_0xbc6e550 in rcx (this), reverse-engineered from the
// disassembly of [0xbc6e550, 0xbc6e766), Minecraft Windows 1.26.62.01. Only offsets the
// function touches are declared; the rest is padding. Verified against the disassembly.
struct sub_bc6e550_state {
    uint8_t pad_0x000[0x14A];                    // +0x000
    uint16_t field_0x14A;                        // +0x14A  word array base; element (u8)idx at +0x14A+idx*0x14
    uint8_t pad_0x14C[0x153 - 0x14C];            // +0x14C..0x152
    uint8_t field_0x153;                         // +0x153  byte array base; element (u8)idx at +0x153+idx*0x14
    uint8_t pad_0x154[0x680 - 0x154];            // +0x154..0x67F
    void* field_0x680;                           // +0x680  SlotArray*: slot[i] = {Record* record@0; u64 limit@8}; u32 counter at array base + 0x410
    uint8_t field_0x688;                         // +0x688  u8 ready flag, written 1 just before return
    uint8_t pad_0x689[1];                        // +0x689
};                                               // sizeof == 0x68A

// Record layout within the slot buffer, stride 0x14.
// Write order observed per index: +0x0A, +0x00, +0x10, +0x11, +0x12, +0x04, +0x08.
struct sub_bc6e550_record {
    uint32_t field_0x00;                         // +0x00  u32: 0
    uint32_t field_0x04;                         // +0x04  u32: dC
    uint16_t field_0x08;                         // +0x08  u16: 0
    uint16_t field_0x0A;                         // +0x0A  u16: w
    uint8_t pad_0x0C[4];                         // +0x0C..0x0F  untouched by the function
    uint8_t field_0x10;                          // +0x10  u8: 0
    uint8_t field_0x11;                          // +0x11  u8: (u8)dB
    uint16_t field_0x12;                         // +0x12  u16: 0x400
};                                               // sizeof == 0x14

// Slot layout at field_0x680 + idx*0x10.
struct sub_bc6e550_slot {
    sub_bc6e550_record* field_0x00;              // +0x00  record buffer pointer
    uint64_t field_0x08;                         // +0x08  record limit
};                                               // sizeof == 0x10

static_assert(offsetof(sub_bc6e550_state, field_0x14A) == 0x14A, "sub_0xbc6e550 writes word state+0x14A+idx*0x14");
static_assert(offsetof(sub_bc6e550_state, field_0x153) == 0x153, "sub_0xbc6e550 writes byte state+0x153+idx*0x14");
static_assert(offsetof(sub_bc6e550_state, field_0x680) == 0x680, "sub_0xbc6e550 reads/writes state+0x680");
static_assert(offsetof(sub_bc6e550_state, field_0x688) == 0x688, "sub_0xbc6e550 writes byte state+0x688");
static_assert(sizeof(sub_bc6e550_state) == 0x68A, "sub_0xbc6e550 object size");
static_assert(offsetof(sub_bc6e550_record, field_0x00) == 0x00, "record dword at +0x00");
static_assert(offsetof(sub_bc6e550_record, field_0x04) == 0x04, "record dword at +0x04");
static_assert(offsetof(sub_bc6e550_record, field_0x08) == 0x08, "record word at +0x08");
static_assert(offsetof(sub_bc6e550_record, field_0x0A) == 0x0A, "record word at +0x0A");
static_assert(offsetof(sub_bc6e550_record, field_0x10) == 0x10, "record byte at +0x10");
static_assert(offsetof(sub_bc6e550_record, field_0x11) == 0x11, "record byte at +0x11");
static_assert(offsetof(sub_bc6e550_record, field_0x12) == 0x12, "record word at +0x12");
static_assert(sizeof(sub_bc6e550_record) == 0x14, "record stride 0x14");
static_assert(offsetof(sub_bc6e550_slot, field_0x00) == 0x00, "slot record pointer at +0x00");
static_assert(offsetof(sub_bc6e550_slot, field_0x08) == 0x08, "slot limit at +0x08");
static_assert(sizeof(sub_bc6e550_slot) == 0x10, "slot stride 0x10");

// sub_0xbc6e550(state* a0 = rcx, u32 a1 = edx, u8* a2 = r8, u64 a3 = r9,
//                u8* a4 = [rsp+0xA0], u64 a5 = [rsp+0xA8], u8* a6 = [rsp+0xB0], u64 a7 = [rsp+0xB8],
//                u32 a8 = [rsp+0xC0], u32 a9 = [rsp+0xC8]) -> void
// Minecraft Windows 1.26.62.01. [0xbc6e550, 0xbc6e766)
void sub_bc6e550(sub_bc6e550_state* a0, uint32_t a1, uint8_t* a2, uint64_t a3,
                 uint8_t* a4, uint64_t a5, uint8_t* a6, uint64_t a7,
                 uint32_t a8, uint32_t a9);

} // namespace native::bgfx
