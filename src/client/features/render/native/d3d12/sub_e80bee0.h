#pragma once
#include <cstddef>
#include <cstdint>

namespace native { namespace d3d12 {

// Layout constants for 0xe80bee0 (RendererContextD3D12 base slot 58).
// The function initialises a 256-entry table embedded in the context object
// and sets an "initialised" flag. Each table entry is 0x20 bytes.
constexpr std::size_t kTableBase   = 0x10000; // lea r12,[rcx+0x10000]   ; entry array base
constexpr std::size_t kEntryStride = 0x20;    // shl rax,5               ; index * 0x20
constexpr std::size_t kEntryPtr    = 0x00;    // mov [r12+rax],rdi       ; stored object pointer
constexpr std::size_t kEntryZero   = 0x08;    // movups [r12+rax+8],xmm6 ; 16 zero bytes
constexpr std::size_t kEntryTag    = 0x18;    // mov dword [r12+rax+0x18],0xFFFFFFFF
constexpr std::size_t kCountOff    = 0x12000; // live count / write cursor
constexpr std::size_t kReadyOff    = 0x12018; // ready flag byte (set to 1 at end)
constexpr std::size_t kEntryCount  = 0x100;   // cmp rbx,0x100           ; 256 iterations
constexpr std::size_t kPerStride   = 0x100;   // add r15,0x100           ; per-call object stride

static_assert(kTableBase == 0x10000, "table base");
static_assert(kEntryStride == 0x20, "entry stride");
static_assert(kEntryTag == 0x18, "entry tag offset");
static_assert(kCountOff == 0x12000, "count offset");
static_assert(kReadyOff == 0x12018, "ready offset");
static_assert(kEntryCount == 0x100, "entry count");
static_assert(kPerStride == 0x100, "per-call stride");

} } // namespace

#define LIFT_FN_E80BEE0 0xe80bee0