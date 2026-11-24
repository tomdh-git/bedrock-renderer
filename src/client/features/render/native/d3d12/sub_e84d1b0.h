#pragma once
#include <cstdint>

namespace native {

// Layout constants for sub_e84d1b0 (0xe84d1b0, size 0x23c).
static_assert(sizeof(void*) == 8, "e84d1b0: x64 target");

struct E84d1b0Node {
    void* next;          // +0x00
    void* data;          // +0x08
    unsigned char hash[8];// +0x10  (bytes +0x10..+0x17)
};
static_assert(sizeof(E84d1b0Node) == 0x18, "e84d1b0: node stride 0x18");

struct E84d1b0Ctx {
    void* a;             // +0x00
    std::uint64_t count; // +0x10
    void* table;         // +0x18
    void* mask;          // +0x30
};
static_assert(sizeof(E84d1b0Ctx) == 0x38, "e84d1b0: ctx size 0x38");

extern "C" void* sub_e935700(void* p, std::uint32_t size);

} // namespace native

#define LIFT_FN_E84D1B0 0xe84d1b0