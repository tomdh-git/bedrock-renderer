#pragma once
#include <cstdint>

#include "client/features/render/native/Lift.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_e9058a0 (0xe9058a0, size 0xbd, 1.26.62.01): Frame renderer lambda destructor/cleanup.
// Layout constants for the object operated on (this pointer in RCX).
struct sub_e9058a0Layout {
    // Vtable pointer at offset 0x0 (written at 0xe9058af)
    static constexpr std::ptrdiff_t kVtableOffset = 0x0;
    // Shared pointer / refcounted object at offset 0x10 (read at 0xe905918, refcount at +0xC)
    static constexpr std::ptrdiff_t kSharedPtr1Offset = 0x10;
    // Refcount offset within the shared pointer control block (lock dec at 0xe905921)
    static constexpr std::ptrdiff_t kRefcountOffset = 0xC;
    // Second shared pointer at offset 0x18 (read at 0xe905901, destructor at vtable+8)
    static constexpr std::ptrdiff_t kSharedPtr2Offset = 0x18;
    // Buffer pointer for small buffer optimization at offset 0x58 (read at 0xe9058bc, byte zeroed at 0xe9058fd)
    static constexpr std::ptrdiff_t kBufferPtrOffset = 0x58;
    // Auxiliary pointer at offset 0x68 (zeroed at 0xe9058ed)
    static constexpr std::ptrdiff_t kAuxPtrOffset = 0x68;
    // Size/length field at offset 0x70 (read at 0xe9058b2, written at 0xe9058f5)
    static constexpr std::ptrdiff_t kSizeOffset = 0x70;

    // Vtable address used by this function (0xF4F2130, loaded at 0xe9058a8)
    static constexpr uintptr_t kVtableAddress = 0xF4F2130;
    // Small buffer optimization threshold: size < 0x10 uses inline buffer (cmp at 0xe9058b6)
    static constexpr uint64_t kSboThreshold = 0x10;
    // Small buffer max size: 0xF (written at 0xe9058f5)
    static constexpr uint64_t kSboMaxSize = 0xF;
    // Large allocation threshold: size+1 >= 0x1000 takes error path (cmp at 0xe9058c4)
    static constexpr uint64_t kLargeAllocThreshold = 0x1000;
    // Allocation header size check: allocation header at [ptr-8] must be >= 0x20 (cmp at 0xe9058d8)
    static constexpr uint64_t kMinAllocHeaderSize = 0x20;
    // Size adjustment for large path: +0x28 (add at 0xe9058de)
    static constexpr uint64_t kLargeSizeAdjust = 0x28;

    // Data slot for vendor shared_ptr deleter thunk (0xF99FFA0, called at 0xe905912 and 0xe90593a)
    static constexpr uintptr_t kVendorDeleterSlot = 0xF99FFA0;
    // Data slot for error/abort handler (0xF9A8C78, called at 0xe905956)
    static constexpr uintptr_t kErrorHandlerSlot = 0xF9A8C78;

    // ABI assertion: pointer size is 8 bytes (x64)
    static_assert(sizeof(void*) == 8, "sub_e9058a0: x64 ABI requires 8-byte pointers");
};

// Layout constant block marker (outside struct to avoid incomplete type)
static_assert(sizeof(sub_e9058a0Layout) > 0, "layout constant block");

namespace native {

// Forward declarations for lift-set callees
// sub_e935700 (0xe935700, size 0x5): tail jump to sub_392960, in lift set (helpers)
void* sub_e935700(void* a0);

// Vendor shared_ptr deleter thunk via data slot 0xF99FFA0 (sub_eea6040, boundary class 'vendor').
// Called with RCX = address of the shared_ptr control block field (this+0x18 or this+0x10).
using VendorDeleterFn = void(__fastcall*)(void* control_block_ptr);

// Error/abort handler via data slot 0xF9A8C78 (boundary, class unknown).
// Called with RCX=0, RDX=0, R8=0, R9=0, stack[0x20]=0. Does not return (followed by int3).
using ErrorHandlerFn = void(__fastcall*)(void*, void*, void*, void*, void*);

// sub_e9058a0: Frame renderer lambda destructor/cleanup.
// Argument: RCX = this pointer to the object being destroyed.
// Returns: void (cleanup function, no meaningful return).
void sub_e9058a0(void* this_ptr);

} // namespace native