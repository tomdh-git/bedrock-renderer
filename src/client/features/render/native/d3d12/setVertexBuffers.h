#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe81b4d0 (size 0x24f, 1.26.62.01).
// D3D12 setVertexBuffers: build one D3D12_VERTEX_BUFFER_VIEW per set bit of a draw's
// stream mask, transitioning each stream's vertex buffer to GENERIC_READ the first time
// it is seen this frame (tracked per handle on the per-job context), and reduce the
// draw's vertex count to the smallest stream. Returns the number of views written.
//
//   rcx = ctx  (RendererContextD3D12*, per-job state), rdx = out (VERTEX_BUFFER_VIEW*),
//   r8  = draw (RenderDraw const*),                 r9  = outNumVertices (u32*).
//
// Two contexts: the state tracking reads/writes the per-job ctx (rcx); the buffer and
// layout tables are read through the global renderer s_renderD3D12 ([0x12BB4910]).
// Every offset below is an instruction [reg+off] seen in the listing [V].

// ---- global data slots [V] ----
static constexpr std::uintptr_t kGblRenderD3D12 = 0x12BB4910u; // mov rsi,[0x12BB4910]   s_renderD3D12
static constexpr std::uintptr_t kGblCookie      = 0x1230A0C0u; // mov rax,[0x1230A0C0]   /GS stack cookie
static constexpr std::uintptr_t kGuardSlot      = 0xF99FFA0u;  // call qword ptr [0xF99FFA0] (sub_eea6040 = jmp rax thunk)

// ---- ctx (rcx) fields [V] ----
static constexpr std::size_t kCommandList       = 0x30;    // ID3D12GraphicsCommandList*  (R 0xe81b5ae [rax+0x30])
static constexpr std::size_t kVbResources       = 0xA248;  // ID3D12Resource*[] stride 0x80 (R 0xe81b5be [rax+0xA248])
static constexpr std::size_t kVbResourceStride  = 0x80;    // shl r8d,7                 (0xe81b5c8)
static constexpr std::size_t kVbTouchedCount    = 0xA250;  // u16 touched-handle count    (R/W 0xe81b620,0xe81b633)
static constexpr std::size_t kVbTouchedBitmap   = 0xA258;  // u64[] per-handle seen bitmap (R/W 0xe81b574,0xe81b618)
static constexpr std::size_t kVbState           = 0xA458;  // {u32 initial, u32 current}[] stride 8 (R/W 0xe81b645)
static constexpr std::size_t kVbStateCurrentOff = 0x04;    // current = base+4 (= 0xA45C)  (R/W 0xe81b592,0xe81b5b2)
static constexpr std::size_t kVbStateStride     = 0x08;    // r13*8
static constexpr std::size_t kVbTouchedList     = 0x12458; // u16[] touched handles       (W 0xe81b628 [r9+rax*2+0x12458])

static_assert(kVbTouchedCount - kVbResources == 0x08, "e81b4d0: count follows resource array");
static_assert(kVbTouchedBitmap - kVbTouchedCount == 0x08, "e81b4d0: bitmap follows count");
static_assert(kVbStateCurrentOff < kVbStateStride, "e81b4d0: current is inside the state pair");
static_assert(kVbTouchedList > kVbState, "e81b4d0: touched list is at a higher offset than the state pairs");

// ---- draw (r8/rdi) fields [V] ----
static constexpr std::size_t kDrawNumVertices  = 0x4C;  // u32 numVertices  (R 0xe81b4f4 [r8+0x4C])
static constexpr std::size_t kDrawStreamMask   = 0x63;  // u8  streamMask   (R 0xe81b4fb [r8+0x63])
static constexpr std::size_t kStreamStride     = 0x08;  // streams[] element size (rdi+r12*8)
static constexpr std::size_t kStreamStartOff   = 0x00;  // u32 startVertex  (R 0xe81b689 [rdx])
static constexpr std::size_t kStreamHandleOff  = 0x04;  // u16 handle       (R 0xe81b54c [rdi+r12*8+4])
static constexpr std::size_t kStreamLayoutOff  = 0x06;  // u16 layoutHandle (R 0xe81b670 [rdx+6])

static_assert(kStreamHandleOff + 2 == kStreamLayoutOff, "e81b4d0: handle then layoutHandle in a stream");
static_assert(kStreamLayoutOff + 2 == kStreamStride, "e81b4d0: stream record is 8 bytes");
static_assert(kDrawStreamMask > kDrawNumVertices, "e81b4d0: mask follows numVertices");

// ---- s_renderD3D12 (g) fields [V] ----
static constexpr std::size_t kVertexBuffers    = 0x9B2178; // VertexBufferD3D12[] base  (R 0xe81b65c add rcx,0x9B2178)
static constexpr std::size_t kVertexBufferStride = 0x80;   // handle*0x80               (0xe81b654 shl r13d,7)
static constexpr std::size_t kVbGpuVA          = 0x58;    // u64 gpu virtual address   (R 0xe81b690 [rcx+0x58])
static constexpr std::size_t kVbSize           = 0x60;    // u32 buffer size in bytes  (R 0xe81b6a9 [rcx+0x60])
static constexpr std::size_t kVbLayoutHandle   = 0x78;    // u16 layout handle, 0xFFFF=none (R 0xe81b663 [rcx+0x78])
static constexpr std::size_t kVertexLayouts    = 0xC96198; // VertexLayout[] base
static constexpr std::size_t kVertexLayoutStride = 0x54;   // layout*0x54              (0xe81b678 imul rsi,r8,0x54)
static constexpr std::size_t kVertexLayoutStrideOff = 0x04; // u16 stride field (base+4 -> 0xC9619C) (R 0xe81b67c)

static_assert(kVertexLayouts + kVertexLayoutStrideOff == 0xC9619C, "e81b4d0: stride field at 0xC9619C");
static_assert(kVbGpuVA + 8 == kVbSize, "e81b4d0: gpuVA then size in a vertex buffer record");
static_assert(kVbSize + 4 == kVbLayoutHandle, "e81b4d0: size then layoutHandle in a vertex buffer record");
static_assert(kVbLayoutHandle + 2 < kVertexBufferStride, "e81b4d0: layout handle inside the 0x80 vertex buffer record");

// ---- out (rdx/rbx) D3D12_VERTEX_BUFFER_VIEW fields [V] ----
static constexpr std::size_t kVbvStride          = 0x10;  // out index << 4          (0xe81b694 shl r10d,4)
static constexpr std::size_t kVbvBufferLocation  = 0x00;  // u64 BufferLocation      (W 0xe81b698 [rbx+r10])
static constexpr std::size_t kVbvSizeInBytes     = 0x08;  // u32 SizeInBytes         (W 0xe81b6b4 [rbx+r10+8])
static constexpr std::size_t kVbvStrideInBytes   = 0x0C;  // u32 StrideInBytes       (W 0xe81b6a4 [rbx+r10+0xC])

static_assert(kVbvSizeInBytes + 4 == kVbvStrideInBytes, "e81b4d0: SizeInBytes then StrideInBytes");
static_assert(kVbvStrideInBytes + 4 == kVbvStride, "e81b4d0: the view record is 16 bytes");

// ---- the D3D12_RESOURCE_BARRIER built on the stack at rsp+0x30 (6 stores, byte-exact) [V] ----
//   0xe81b5d0 mov qword ptr [rsp+0x30],0       -> type(0)+flags(0)
//   0xe81b5d9 mov [rsp+0x38],rax               -> pResource
//   0xe81b5de mov dword ptr [rsp+0x40],0xFFFFFFFF -> subresource (ALL)
//   0xe81b5e6 mov [rsp+0x44],edx               -> stateBefore (old current)
//   0xe81b5ea mov dword ptr [rsp+0x48],0xAC3    -> stateAfter (GENERIC_READ)
struct ResourceBarrier {
    std::uint32_t type;        // +0x00  D3D12_RESOURCE_BARRIER_TYPE_TRANSITION (0)
    std::uint32_t flags;       // +0x04  D3D12_RESOURCE_BARRIER_FLAG_NONE       (0)
    void*         pResource;   // +0x08  ID3D12Resource*
    std::uint32_t subresource; // +0x10  D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES (0xFFFFFFFF)
    std::uint32_t stateBefore; // +0x14  old current state
    std::uint32_t stateAfter;  // +0x18  0xAC3 GENERIC_READ
};
static_assert(offsetof(ResourceBarrier, type) == 0x00, "e81b4d0: barrier.type @0");
static_assert(offsetof(ResourceBarrier, flags) == 0x04, "e81b4d0: barrier.flags @4");
static_assert(offsetof(ResourceBarrier, pResource) == 0x08, "e81b4d0: barrier.pResource @8");
static_assert(offsetof(ResourceBarrier, subresource) == 0x10, "e81b4d0: barrier.subresource @0x10");
static_assert(offsetof(ResourceBarrier, stateBefore) == 0x14, "e81b4d0: barrier.stateBefore @0x14");
static_assert(offsetof(ResourceBarrier, stateAfter) == 0x18, "e81b4d0: barrier.stateAfter @0x18");

// ---- vtable slot of the command list's ResourceBarrier (CFG-guarded virtual call) [V] ----
static constexpr std::size_t kVslotResourceBarrier = 0xD0; // mov rax,[rax+0xD0] ; slot index = 0xD0/8 = 26 (0xe81b5f5)

// ---- enums / constants [V] ----
static constexpr std::uint32_t kGenericRead      = 0xAC3;          // D3D12_RESOURCE_STATE_GENERIC_READ
static constexpr std::uint32_t kAllSubresources  = 0xFFFFFFFFu;    // D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES
static constexpr std::uint64_t kPairGenericRead  = 0xAC300000AC3ull; // {initial, current} both GENERIC_READ (0xe81b63b)
static constexpr std::uint32_t kHandleMax         = 0xFFF;         // handles above this skip state tracking (cmp r13d,0xFFF)
static constexpr std::uint8_t  kMaskEarlyOut      = 0xFD;          // (uint8_t)(mask-1) > 0xFD -> no per-stream buffers

// x64 Microsoft ABI: rcx=ctx, rdx=out, r8=draw, r9=outNumVertices. Return r15b = number
// of vertex buffer views written [V]. void* is used for the COM/opaque pointers so this
// header needs no d3d12.h; the bytes written are identical to the original.
extern "C" std::uint8_t setVertexBuffers(void* ctx, void* out, const void* draw, std::uint32_t* outNumVertices);

} // namespace native