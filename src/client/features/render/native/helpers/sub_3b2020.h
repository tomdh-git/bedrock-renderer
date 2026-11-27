// LIFT 0x3b2020 size 0xac 1.26.62.01 sub_3b2020
#pragma once

#include <cstdint>

namespace native {

// Forward declarations for resolved lift callees
int sub_eec59f0(struct _Mtx* mtx);
void sub_eec5a00(int errorCode);
void sub_eec5a10(struct _Mtx* mtx);

// Opaque MSVCP140 C11 mutex (partial layout known from sub_3b2020)
struct _Mtx {
    uint8_t pad_0x00[0x4C];
    uint32_t field_0x4C;            // +0x4C - mutex state dword
};

// sub_3b2020_state layout (matches exe at 0x3b2020)
struct sub_3b2020_state {
    uint8_t pad_0x00[0x8];
    struct _Mtx* field_0x08;        // +0x08
    uint8_t pad_0x10[0x8];
    void* field_0x18;               // +0x18
    uint8_t pad_0x20[0x2C];
    uint32_t field_0x4C;            // +0x4C
    uint8_t pad_0x50[0x10];
    int64_t field_0x60;             // +0x60
};

// Layout assertions
static_assert(offsetof(sub_3b2020_state, field_0x08) == 0x08, "field_0x08 offset");
static_assert(offsetof(sub_3b2020_state, field_0x18) == 0x18, "field_0x18 offset");
static_assert(offsetof(sub_3b2020_state, field_0x4C) == 0x4C, "field_0x4C offset");
static_assert(offsetof(sub_3b2020_state, field_0x60) == 0x60, "field_0x60 offset");
static_assert(sizeof(sub_3b2020_state) >= 0x68, "sub_3b2020_state size");
static_assert(offsetof(_Mtx, field_0x4C) == 0x4C, "_Mtx field_0x4C offset");

// Function signature: void sub_3b2020(sub_3b2020_state* self)
// x64 Microsoft ABI: RCX = self, void return
void sub_3b2020(sub_3b2020_state* self);

} // namespace native