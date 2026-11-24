#pragma once
#include <cstddef>
#include <cstdint>

namespace native { namespace d3d12 {

struct MoveStruct {
    std::uint64_t f00;          // +0x00
    std::uint64_t f08[2];       // +0x08  (16 bytes)
    std::uint64_t f18;          // +0x18
    std::uint64_t f20[2];       // +0x20  (16 bytes)
    std::uint64_t f30;          // +0x30
    std::uint16_t f38;          // +0x38
    std::uint16_t f3a;          // +0x3A
    std::uint64_t f40;          // +0x40
    std::uint16_t f48;          // +0x48
    std::uint16_t f4a;          // +0x4A
    std::uint64_t f50;          // +0x50
    std::uint16_t f58;          // +0x58
    std::uint16_t f5a;          // +0x5A
    std::uint64_t f60;          // +0x60
    std::uint16_t f68;          // +0x68
    std::uint16_t f6a;          // +0x6A
    std::uint64_t f70;          // +0x70
};

static_assert(sizeof(MoveStruct) == 0x78, "MoveStruct size");
static_assert(offsetof(MoveStruct, f00) == 0x00);
static_assert(offsetof(MoveStruct, f08) == 0x08);
static_assert(offsetof(MoveStruct, f18) == 0x18);
static_assert(offsetof(MoveStruct, f20) == 0x20);
static_assert(offsetof(MoveStruct, f30) == 0x30);
static_assert(offsetof(MoveStruct, f38) == 0x38);
static_assert(offsetof(MoveStruct, f3a) == 0x3A);
static_assert(offsetof(MoveStruct, f40) == 0x40);
static_assert(offsetof(MoveStruct, f48) == 0x48);
static_assert(offsetof(MoveStruct, f4a) == 0x4A);
static_assert(offsetof(MoveStruct, f50) == 0x50);
static_assert(offsetof(MoveStruct, f58) == 0x58);
static_assert(offsetof(MoveStruct, f5a) == 0x5A);
static_assert(offsetof(MoveStruct, f60) == 0x60);
static_assert(offsetof(MoveStruct, f68) == 0x68);
static_assert(offsetof(MoveStruct, f6a) == 0x6A);
static_assert(offsetof(MoveStruct, f70) == 0x70);

extern "C" MoveStruct* sub_e869ff0(MoveStruct* dst, const MoveStruct* src);

#define LIFT_FN(name, rva) /* registry placeholder */

} } // namespace
