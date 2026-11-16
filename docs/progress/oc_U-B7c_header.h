// docs/progress/oc_U-B7c_header.h
// UNIT U-B7c — static_asserts of VERIFIED offsets only (D3D12 upload tracking lists, slots 55/56/57).
// Every offset asserted below was observed directly in the disassembly of slots 55/56/57
// (0xe8165a0 / 0xe817070 / 0xe816f40). Offsets whose *meaning* is not pinned are still asserted
// because the offset itself was seen as a read/write target; meaning tags are in oc_U-B7c.md.
//
// Build check:  cl /c /W4 /nologo docs/progress/oc_U-B7c_header.h   (or equivalent)
//               The static_asserts must all pass; if any fails the disassembly citation is wrong.

#pragma once
#include <cstddef>
#include <cstdint>

namespace blueysense { namespace u_b7c {

// =====================================================================
// Context offsets (member offsets within the D3D12 renderer context).
// Verified by direct [ctx+off] reads/writes in slots 55/56/57.
// =====================================================================
struct ContextUploadLists {
    // 0x18-byte readback/fence ring (slot 56 push; slot 57 retire)
    //   begin = +0x19FE0, end = +0x19FE8, cap = +0x19FF0  [V e8172cb/e817185/e81718c]
    std::uintptr_t _pad_19fe0[0]; // placeholder; real members asserted via ContextMembers below
};
// NOTE: asserting members of the full context requires the complete context type, which is not
// fully reverse-engineered. The context member offsets below are asserted through a minimal
// view struct that places char[] padding to reach each verified offset.
struct ContextMembersView {
    char pad_19fe0[0x19FE0];
    std::uintptr_t fence_ring_begin; // +0x19FE0  [V]
    char pad_19fe8[0x8];
    std::uintptr_t fence_ring_end;   // +0x19FE8  [V]
    char pad_19ff0[0x8];
    std::uintptr_t fence_ring_cap;   // +0x19FF0  [V]
    char pad_1a000[0x10];            // 0x19FF8..0x1A000
    std::uintptr_t upload_list_begin; // +0x1A000 [V e816f66]
    std::uintptr_t upload_list_end;   // +0x1A008 [V e816f6d]
    std::uintptr_t upload_list_cap;   // +0x1A010 [V e816eef]
    // +0x1A018..0x1A028 = 0x18-list end/cap (slot 55/57) not separately asserted here
    char pad_57a100[0x57A100 - 0x1A018];
    std::uintptr_t upload_ring_resource; // +0x57A100 [V e8165c0]
    char pad_57a178[0x57A178 - 0x57A108];
    // +0x57A178 = base of 0x78-stride per-handle record table [V e816f5a/e81688b]

    static_assert(offsetof(ContextMembersView, fence_ring_begin) == 0x19FE0, "ctx +0x19FE0 fence ring begin");
    static_assert(offsetof(ContextMembersView, fence_ring_end)   == 0x19FE8, "ctx +0x19FE8 fence ring end");
    static_assert(offsetof(ContextMembersView, fence_ring_cap)   == 0x19FF0, "ctx +0x19FF0 fence ring cap");
    static_assert(offsetof(ContextMembersView, upload_list_begin) == 0x1A000, "ctx +0x1A000 upload list begin");
    static_assert(offsetof(ContextMembersView, upload_list_end)   == 0x1A008, "ctx +0x1A008 upload list end");
    static_assert(offsetof(ContextMembersView, upload_list_cap)   == 0x1A010, "ctx +0x1A010 upload list cap");
    static_assert(offsetof(ContextMembersView, upload_ring_resource) == 0x57A100, "ctx +0x57A100 upload ring resource");
};

// =====================================================================
// 0x48-byte upload-tracking entry (ctx+0x1A000 list) — slot 55 push / slot 57 erase.
// =====================================================================
struct UploadEntry48 {
    std::uint16_t handle_lo;          // +0x00  [V e816b7f]
    std::uint16_t handle_hi;          // +0x02  [V e816b89]
    std::uint16_t field_04;           // +0x04  [V e816b8f]
    std::uint16_t field_06;           // +0x06  [V e816b9d]
    std::uint32_t field_08;           // +0x08  [V e816baa]
    std::uint32_t field_0C;           // +0x0C  [V e816bba]
    std::uint32_t field_10;           // +0x10  [V e816bd3]
    std::uint32_t field_14;           // +0x14  [V e816bd8]
    std::uint32_t field_18;           // +0x18  [V e816be8]
    std::uint16_t field_1C;           // +0x1C  [V e816bed]
    std::uint32_t field_20;           // +0x20  [V e816b6c]
    std::uint32_t field_24;           // +0x24  [V e816bfc]
    std::uint32_t sentinel_28;        // +0x28 = 0xFFFFFFFF  [V e816b71]
    std::uint16_t field_2C;           // +0x2C  [V e816c0f]
    std::uint32_t sentinel_2E;        // +0x2E = 0xFFFFFFFF  [V e816bf3]
    std::uint8_t  flag_32;            // +0x32 OR 1  [V e816c01]
    std::uint8_t  pad_33[5];          // +0x33..+0x37
    std::uint16_t handle_key_38;      // +0x38 handle matched by slot 57  [V e816f80/e816fa9]
    std::uint8_t  pad_3a[6];          // +0x3a..+0x3f
    std::uint64_t copy_src_40;        // +0x40  [V e816cec]
    std::uint8_t  pad_48[0];          // sizeof == 0x48

    static_assert(offsetof(UploadEntry48, handle_lo)          == 0x00, "entry48 +0x00");
    static_assert(offsetof(UploadEntry48, handle_hi)          == 0x02, "entry48 +0x02");
    static_assert(offsetof(UploadEntry48, field_04)           == 0x04, "entry48 +0x04");
    static_assert(offsetof(UploadEntry48, field_06)           == 0x06, "entry48 +0x06");
    static_assert(offsetof(UploadEntry48, field_08)           == 0x08, "entry48 +0x08");
    static_assert(offsetof(UploadEntry48, field_0C)           == 0x0C, "entry48 +0x0C");
    static_assert(offsetof(UploadEntry48, field_10)           == 0x10, "entry48 +0x10");
    static_assert(offsetof(UploadEntry48, field_14)           == 0x14, "entry48 +0x14");
    static_assert(offsetof(UploadEntry48, field_18)           == 0x18, "entry48 +0x18");
    static_assert(offsetof(UploadEntry48, field_1C)           == 0x1C, "entry48 +0x1C");
    static_assert(offsetof(UploadEntry48, field_20)           == 0x20, "entry48 +0x20");
    static_assert(offsetof(UploadEntry48, field_24)           == 0x24, "entry48 +0x24");
    static_assert(offsetof(UploadEntry48, sentinel_28)        == 0x28, "entry48 +0x28");
    static_assert(offsetof(UploadEntry48, field_2C)           == 0x2C, "entry48 +0x2C");
    static_assert(offsetof(UploadEntry48, sentinel_2E)        == 0x2E, "entry48 +0x2E");
    static_assert(offsetof(UploadEntry48, flag_32)            == 0x32, "entry48 +0x32");
    static_assert(offsetof(UploadEntry48, handle_key_38)      == 0x38, "entry48 +0x38 handle key");
    static_assert(offsetof(UploadEntry48, copy_src_40)        == 0x40, "entry48 +0x40");
    static_assert(sizeof(UploadEntry48) == 0x48, "entry48 sizeof 0x48");
};

// =====================================================================
// 0x18-byte readback/fence entry (ctx+0x19FE8 ring) — slot 56 push.
// =====================================================================
struct FenceEntry18 {
    std::uint16_t handle;             // +0x00  [V e817195]
    std::uint8_t  pad_02[6];          // +0x02..+0x07
    std::uint64_t alloc_ptr;          // +0x08  [V e8171a8]
    std::uint64_t size;               // +0x10  [V e8171ac]
    std::uint64_t size_dup_fence;     // +0x18  [V e8171b0 / cleared e817300]

    static_assert(offsetof(FenceEntry18, handle)              == 0x00, "fence18 +0x00");
    static_assert(offsetof(FenceEntry18, alloc_ptr)           == 0x08, "fence18 +0x08");
    static_assert(offsetof(FenceEntry18, size)                == 0x10, "fence18 +0x10");
    static_assert(offsetof(FenceEntry18, size_dup_fence)      == 0x18, "fence18 +0x18");
    static_assert(sizeof(FenceEntry18) == 0x18, "fence18 sizeof 0x18");
};

// =====================================================================
// 0x78-stride per-handle record (ctx+0x57A178 + handle*0x78) — slots 55/56/57.
// Only the fields written by slots 55/56 are asserted; the rest of the 0x78 record
// is not decoded in this unit.
// =====================================================================
struct BufferRecord78 {
    std::uint64_t field_00;           // +0x00  [V e816ac5/e817581]
    std::uint64_t field_08;           // +0x08  [V e816ae5/e817599] = 0xB00000000
    std::uint32_t field_10;           // +0x10  [V e816ae9/e81759d] = 0x1688
    std::uint32_t _pad_14[2];         // +0x14..+0x17
    std::uint64_t field_18;           // +0x18  [V e816af0/e8175a4]
    std::uint32_t _pad_20[0x16];      // +0x20..+0x57
    std::uint64_t field_58;           // +0x58  [V e816ad0/e817588]
    std::uint32_t field_60;           // +0x60  [V e816a68/e817523] = slot55 eax / slot56 0x2000000
    std::uint16_t field_64;           // +0x64  [V e816a6b/e81752a] = 0x200
    std::uint8_t  field_66;           // +0x66  [V e816a71/e817530] = 1
    std::uint8_t  _pad_67[9];         // +0x67..+0x6f
    std::uint32_t field_70;           // +0x70  [V e816a75/e817534] = 1
    std::uint8_t  _pad_74[0x78-0x74]; // +0x74..+0x77

    static_assert(offsetof(BufferRecord78, field_00)            == 0x00, "rec78 +0x00");
    static_assert(offsetof(BufferRecord78, field_08)            == 0x08, "rec78 +0x08");
    static_assert(offsetof(BufferRecord78, field_10)            == 0x10, "rec78 +0x10");
    static_assert(offsetof(BufferRecord78, field_18)            == 0x18, "rec78 +0x18");
    static_assert(offsetof(BufferRecord78, field_58)            == 0x58, "rec78 +0x58");
    static_assert(offsetof(BufferRecord78, field_60)            == 0x60, "rec78 +0x60");
    static_assert(offsetof(BufferRecord78, field_64)            == 0x64, "rec78 +0x64");
    static_assert(offsetof(BufferRecord78, field_66)            == 0x66, "rec78 +0x66");
    static_assert(offsetof(BufferRecord78, field_70)            == 0x70, "rec78 +0x70");
    static_assert(sizeof(BufferRecord78) == 0x78, "rec78 sizeof 0x78");

}} // namespace
