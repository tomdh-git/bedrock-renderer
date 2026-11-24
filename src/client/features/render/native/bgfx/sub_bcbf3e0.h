// LIFT 0xbcbf3e0 size 0x181 1.26.62.01 BgfxFrameBuilder slot 15
#pragma once

namespace native {

// Forward declarations for lift callees
void* sub_e935700(void* ptr, size_t size);  // 0xe935700 - free buffer

// Data slot function pointers (resolved at runtime)
using alloc_fn_t = void*(void* context, size_t size);
extern alloc_fn_t* const data_f99ffa0;  // 0xF99FFA0 -> sub_eea6040 (vendor thunk)
extern void* const data_1233e1a8;        // 0x1233E1A8 -> allocator context
using error_fn_t = void(void*, void*, void*, void*);
extern error_fn_t* const data_f9a8c78;   // 0xF9A8C78 -> unknown error handler

// Boundary allocator (0x9bc830)
void* boundary_alloc(size_t size);

// BgfxFrameBuilder layout assertions (a0 = this)
struct BgfxFrameBuilder {
    // +0x00: dword - copied from input, then set to 1.0f (0x3F800000)
    // +0x08: qword - pointer to first allocation (circular list head)
    // +0x18: qword - buffer pointer
    // +0x20: qword - buffer start (buffer - 0x80)
    // +0x28: qword - buffer end
    // +0x30: qword - constant 7
    // +0x38: qword - constant 8
    // Total observed: 0x40 bytes
};

static_assert(sizeof(BgfxFrameBuilder) >= 0x40, "BgfxFrameBuilder too small");
static_assert(offsetof(BgfxFrameBuilder, field_0x08) == 0x08, "field_0x08 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x18) == 0x18, "field_0x18 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x20) == 0x20, "field_0x20 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x28) == 0x28, "field_0x28 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x30) == 0x30, "field_0x30 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x38) == 0x38, "field_0x38 offset");

// First allocation (0x38 bytes): circular list node
struct ListNode38 {
    ListNode38* next;  // +0x00
    ListNode38* prev;  // +0x08
    // +0x10..0x37: padding/unknown (0x28 bytes)
};
static_assert(sizeof(ListNode38) == 0x38, "ListNode38 size");

// Second allocation (0x80 bytes): array of 16 pointers to ListNode38
static constexpr size_t kSecondAllocSize = 0x80;
static constexpr size_t kSecondAllocCount = 16;  // 0x80 / 8

// Lifted function signature
extern "C" void* sub_bcbf3e0(void* a0, const void* a1);

}  // namespace native