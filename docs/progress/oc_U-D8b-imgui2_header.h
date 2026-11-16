// oc_U-D8b-imgui2_header.h — read view of UIImGui description (UI tag 4, case 0x6664aab)
// Verified desc reads: +0x00..+0x07, +0x10..+0x17, +0x18..+0x1F, +0x20..+0x27,
// +0x28..+0x2F, +0x30..+0x37, +0x48..+0x49 (see docs/progress/oc_U-D8b-imgui2.md)
// Read view spans desc[0x00 .. 0x49] -> size = 0x4A (74 bytes); last read end = 0x48+2 = 0x4A.

#include <cstddef>

struct UIImGuiDescReadView {
    char pad_0x00[0x10];   // +0x00 source-object ptr (+0x10 memcpy src)
    char pad_0x10[0x8];    // +0x18 high-dword==0 branch guard
    char pad_0x18[0x8];    // +0x20 memcpy src pointer
    char pad_0x20[0x8];    // +0x28 element count (u64)
    char pad_0x28[0x8];    // +0x30 element array base pointer
    char pad_0x30[0x18];   // gap 0x38..0x47
    char pad_0x48[0x2];    // +0x48 u16 (dead in window; first use unknown)
};

// View size = last read end (0x48 + 2 bytes = 0x4A).
static_assert(sizeof(UIImGuiDescReadView) == 0x4A, "view size must equal last desc-read end");
static_assert(offsetof(UIImGuiDescReadView, pad_0x00) == 0x00, "desc+0x00");
static_assert(offsetof(UIImGuiDescReadView, pad_0x10) == 0x10, "desc+0x10");
static_assert(offsetof(UIImGuiDescReadView, pad_0x18) == 0x18, "desc+0x18");
static_assert(offsetof(UIImGuiDescReadView, pad_0x20) == 0x20, "desc+0x20");
static_assert(offsetof(UIImGuiDescReadView, pad_0x28) == 0x28, "desc+0x28");
static_assert(offsetof(UIImGuiDescReadView, pad_0x30) == 0x30, "desc+0x30");
static_assert(offsetof(UIImGuiDescReadView, pad_0x48) == 0x48, "desc+0x48");
