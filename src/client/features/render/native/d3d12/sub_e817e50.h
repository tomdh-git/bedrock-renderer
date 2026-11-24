#pragma once
#include <cstddef>
#include <cstdint>

namespace native { namespace d3d12 {

// LIFT 0xe817e50 size 0x1fe 1.26.62.01 sub_e817e50
// "RendererContextD3D12 base slot 43" (command byte 37).
//
// Releases and clears the per-context value pointer stored at
// context + handle*8 + 0x1250 for every context in
// [this+0x19F60, this+0x19F68), then (when handle != 0xFFFF) removes the
// handle from the 0x400-entry open-addressing handle map at
// this+0xC9AA9C / this+0xC9AAA0 / this+0xC9BAA0.
//
// Instruction-level geometry (Minecraft Windows 1.26.62.01):
//   0xe817e62  mov rbx,[rcx+0x19F60]            ; begin
//   0xe817e69  mov r14,[rcx+0x19F68]            ; end
//   0xe817e75  movzx r15d,si                    ; handle index
//   0xe817e80  mov qword ptr [r12+r15*8+0x1250],0

// Offsets inside the RendererContextD3D12 object (a0 / rcx).
constexpr std::size_t kContextArrayBegin = 0x19F60;  // char* begin of per-context pointer array
constexpr std::size_t kContextArrayEnd   = 0x19F68;  // char* end of that array
constexpr std::size_t kValueSlotBase     = 0x1250;   // per-context value pointer base
constexpr std::size_t kValueSlotStride   = 8;        // one pointer per handle

// 0x400-entry open-addressing handle map (UniformHandleMapOffsets in D3D12Context.h).
constexpr std::size_t kHandleMapCount    = 0xC9AA9C;  // u32 active entries
constexpr std::size_t kHandleMapKeys     = 0xC9AAA0;  // u32[0x400] hash source
constexpr std::size_t kHandleMapHandles  = 0xC9BAA0;  // u16[0x400], 0xFFFF = empty
constexpr std::size_t kHandleMapCapacity = 0x400;
constexpr std::uint16_t kHandleEmpty     = 0xFFFF;

// Handle-map hash: ((v * 0x5EBCA77) >> 0x13) * 0x1B1 & 0x3FF.
constexpr std::uint32_t kHashMul1  = 0x5EBCA77u;
constexpr unsigned      kHashShift = 0x13;
constexpr std::uint32_t kHashMul2  = 0x1B1u;
constexpr std::uint32_t kHashMask  = 0x3FFu;

// Loader-resolved allocator global and the release thunk slot (data_12adf800 / data_f99ffa0).
constexpr std::size_t kAllocatorGlobal = 0x12ADF800;  // void* allocator object
constexpr std::size_t kReleaseThunkSlot = 0xF99FFA0;  // sub_eea6040 (jmp rax), vendor boundary

static_assert(kContextArrayEnd - kContextArrayBegin == 8, "context array is one pointer long");
static_assert(kHandleMapKeys == kHandleMapCount + 4, "keys follow count");
static_assert(kHandleMapHandles == kHandleMapKeys + kHandleMapCapacity * 4, "handles follow keys");

// Exact x64 ABI: this in rcx (a0), 16-bit handle in dx (a1).
extern "C" void sub_e817e50(void* a0, unsigned short a1);

} } // namespace native::d3d12