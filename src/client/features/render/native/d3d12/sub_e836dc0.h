#pragma once
// LIFT 0xe836dc0 size 0x131 1.26.62.01 sub_e836dc0

#include <cstdint>
#include <cstddef>

namespace native { namespace d3d12 {

// Layout constants for sub_e836dc0 (0xe836dc0..0xe836ef1)
struct alignas(8) Obj_e836dc0 {
    void*  field_00;     // +0x00
    void*  field_08;     // +0x08
    uint64_t field_10;   // +0x10
    char   pad_18[0x20]; // +0x18..0x37
    uint64_t field_38;   // +0x38
};

static_assert(offsetof(Obj_e836dc0, field_00) == 0x00, "field_00");
static_assert(offsetof(Obj_e836dc0, field_08) == 0x08, "field_08");
static_assert(offsetof(Obj_e836dc0, field_10) == 0x10, "field_10");
static_assert(offsetof(Obj_e836dc0, field_38) == 0x38, "field_38");

} } // namespace

extern "C" void* sub_e836dc0(void* a0, void* a1);