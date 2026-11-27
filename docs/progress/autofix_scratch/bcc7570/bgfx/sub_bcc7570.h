#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/RewriteRegistry.h"
#include "client/features/render/native/RewriteVerify.h"
#include "sdk/SigManager.h"
// Forward declarations (autofix)
struct sub_eec73f0;


// sub_bcc7570: unordered_map insertion (size 0x54e, 1.26.62.01).

// Layout constants for the lifted body, taken from the disassembly of

// [0xbcc7570, 0xbcc7abc).


namespace native::bgfx {

// Forward declarations for lift-set callees (forward-declared; lifted by own unit).

extern "C" void sub_eec73f0();  // 0xeec73f0 lift (math)

extern "C" void sub_eec5850();  // 0xeec5850 lift (error throw)

extern "C" void sub_e935700();  // 0xe935700 lift (deallocator/free)


// Boundary wrappers.

namespace boundary {
    // alloc: 0x9bc830

    void* alloc(size_t size);
    // vendor: 0xeea6040 via data slot 0xF99FFA0

    void* vendor_alloc(size_t size);
}

// Struct layout constants observed in the disassembly.

static constexpr uintptr_t kBcc7570MaxSize = 0xAAAAAAAAAAAAAAA; // 0xbcc75f5

static constexpr uint32_t kBcc7570AllocSize = 0x18;             // 0xbcc760d

static constexpr uint32_t kBcc7570MinBucket = 0x1;               // 0xbcc76b6

static constexpr uint32_t kBcc7570MaxBucket = 0x9;               // 0xbcc76b6

static constexpr uint32_t kBcc7570Threshold = 0x200;             // 0xbcc76d7


// Signature: void* sub_bcc7570(void* this /*rcx*/, const void* key /*rdx*/, void* out_result /*r8*/)

// Returns rax = out_result (rsi).

void* sub_bcc7570(void* self, const void* key, void* out_result);

} // namespace native::bgfx