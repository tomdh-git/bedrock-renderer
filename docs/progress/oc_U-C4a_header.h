// DragonFrameResources (C4a) — verified-only struct.
// Every offset below is read from the disassembly of dispatcher 0xE9002E0.
// Source: docs/progress/oc_U-C4a.md ; verification: python tools/sigs/verify_oc.py docs/progress/oc_U-C4a.md
// Nothing here is compiled against the game; offsets are instruction-level readings.

#pragma once
#include <cstddef>

namespace dragon {

// The dispatcher 0xE9002E0 touches ONLY these three fields of DragonFrameResources.
// Correction to BGFX_MAP 6cx: +0x298 is the vector's LAST (push cursor), +0x2A0 its END (capacity),
// FIRST is +0x290. Element size 0x10 = {Task*, shared_ptr control block*}.
struct DragonFrameResourcesOffsets {
    static constexpr size_t kTasksFirst = 0x290; // [V] R: 0xE900827, 0xE900913, 0xE9009FF, 0xE900A71; W: 0xE900ABA, 0xE900B2D
    static constexpr size_t kTasksLast  = 0x298; // [V] R: 0xE9004AA, 0xE90091A, 0xE90096F, 0xE900A16; W: 0xE9004C5, 0xE900ABA, 0xE900B3F
    static constexpr size_t kTasksEnd   = 0x2A0; // [V] R: 0xE9004B1, 0xE900A7F; W: 0xE900ADD, 0xE900B50
    static constexpr size_t kTaskElementSize = 0x10; // [V] {Task*, shared_ptr ctrl*}
    static constexpr size_t kInOwner  = 0x268;   // [V] 0x67CA3BB: edx = 0x268; add rdx,[rsi+0x10]
};

static_assert(DragonFrameResourcesOffsets::kTasksFirst == 0x290);
static_assert(DragonFrameResourcesOffsets::kTasksLast  == 0x298);
static_assert(DragonFrameResourcesOffsets::kTasksEnd   == 0x2A0);
static_assert(DragonFrameResourcesOffsets::kTaskElementSize == 0x10);
static_assert(DragonFrameResourcesOffsets::kInOwner == 0x268);

// Fields below +0x290 and at/after +0x2A8 are NOT verified: no reader/writer found in 0xE9002E0.
// Constructor/destructor of DragonFrameResources: not located (OPEN per bgfx-d3d12-dragon.md C4a).

} // namespace dragon
