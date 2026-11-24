#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

struct Frame_sort_state {
    // Layout constants from dossier
    static constexpr std::size_t kViewRemap = 0x0;
    static constexpr std::size_t kSortKeys = 0x14700;
    static constexpr std::size_t kSortedItems = 0x94700;
    static constexpr std::size_t kBlitKeys = 0x934778;
    static constexpr std::size_t kItemCount = 0xDC57E8;
    static constexpr std::size_t kBlitCount = 0xDC57EC;
};

static_assert(Frame_sort_state::kViewRemap == 0x0);
static_assert(Frame_sort_state::kSortKeys == 0x14700);
static_assert(Frame_sort_state::kSortedItems == 0x94700);
static_assert(Frame_sort_state::kBlitKeys == 0x934778);
static_assert(Frame_sort_state::kItemCount == 0xDC57E8);
static_assert(Frame_sort_state::kBlitCount == 0xDC57EC);

// Context offsets
static constexpr std::size_t kCtxTempKeys = 0x1CFD0D0;
static constexpr std::size_t kCtxTempValues = 0x1D7D0C8;

void Frame_sort(void* self);

} // namespace native::bgfx
