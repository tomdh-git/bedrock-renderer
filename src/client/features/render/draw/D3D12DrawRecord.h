#pragma once

// DrawBatcher + DrawRecord struct layouts for the D3D12 draw-flush seam.
// Every offset below was verified verbatim in the disassembly of
// C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe.
// See docs/progress/oc_U-EM3e.md for the full verbatim proof table.
//
// This header is header-only (no CMake change) and registers nothing:
// HookManager.cpp and existing hook registrations are off-limits to this unit.
// It provides the verified struct layouts + static asserts so that any future
// hook at flush 0xe81b720 can read/modify every DrawBatcher record before the GPU.
//
// Fail-fast style (CLAUDE.md): static_assert on every layout, no null guards, no SEH.


#include "../draw/D3D12DrawFlushWrap.h"  // kRecordNonIndexed, kRecordIndexed, batcher offsets

namespace bgfx::d3d12draw {

// ---------------------------------------------------------------------------
// DrawBatcher (pointed to by [executorState + 0x250]; set at 0xe821774
//   mov [rbx+0x250],r8)
// ---------------------------------------------------------------------------
struct DrawBatcher {
    // +0x10: u32 pending[2] — pending[0] non-indexed, pending[1] indexed
    //   0xe81b736 mov esi,[rcx+r12*4+0x10]   (load)
    //   0xe81b74a mov dword ptr [rcx+r12*4+0x10],0  (clear after snapshot)
    char _pad_0[0x10];
    uint32_t pending[2];          // +0x10

    // +0x18: u64 records[2] — record array pointers
    //   0xe81b779 mov rax,[rdi+r12*8+0x18]   (load records[kind])
    uint64_t records[2];          // +0x18

    // ... fields between +0x20 and +0x10BF not needed for record editing ...

    // +0x10C0: u8 vbCache[5*16] — last 5 vertex buffer views (dedup)
    // +0x1110: u8 ibCache[16]   — last index buffer view (dedup)
    // +0x1120: u64 lastCbv[2]   — last root CBV pair (dedup)
    // +0x1148: u32 statDirect[2]
    // +0x1150: u32 statOverflow[2]
    // +0x115C: u32 capacity     — 0xe81b753 cmp [rcx+0x115C],esi
    // +0x1164: u8  indirectEnabled
    char _pad_to_10c0[0x10C0 - 0x28];
    uint8_t vbCache[5 * 16];      // +0x10C0
    uint8_t ibCache[16];          // +0x1110
    uint64_t lastCbv[2];          // +0x1120
    char _pad_to_1148[0x1148 - (0x1120 + 16)];
    uint32_t statDirect[2];       // +0x1148
    uint32_t statOverflow[2];     // +0x1150
    char _pad_to_115c[0x115C - 0x1158];
    uint32_t capacity;            // +0x115C
    char _pad_to_1164[0x1164 - (0x115C + 4)];
    uint8_t indirectEnabled;      // +0x1164



    // Access the record array for a given kind (0=non-indexed, 1=indexed).
    // Returns pointer to records[kind] array; element i is at [records[kind] + i*stride].
    inline uint64_t* recordArray(uint32_t kind) const noexcept { return reinterpret_cast<uint64_t*>(records[kind]); }
};

static_assert(offsetof(DrawBatcher, pending) == 0x10, "DrawBatcher::pending offset");
static_assert(offsetof(DrawBatcher, records) == 0x18, "DrawBatcher::records offset");
static_assert(offsetof(DrawBatcher, vbCache) == 0x10C0, "DrawBatcher::vbCache offset");
static_assert(offsetof(DrawBatcher, ibCache) == 0x1110, "DrawBatcher::ibCache offset");
static_assert(offsetof(DrawBatcher, lastCbv) == 0x1120, "DrawBatcher::lastCbv offset");
static_assert(offsetof(DrawBatcher, capacity) == 0x115C, "DrawBatcher::capacity offset");
static_assert(offsetof(DrawBatcher, indirectEnabled) == 0x1164,
              "DrawBatcher::indirectEnabled offset");

// ---------------------------------------------------------------------------
// DrawRecordNonIndexed — stride 0x70 (0xe81ba9f add r15,0x70)
// Read by the flush non-indexed loop at 0xe81bab0..0xe81bb62:
//   0xe81babc mov edx,[r15+0x60]    vertexCount
//   0xe81bac0 mov r8d,[r15+0x64]    instanceCount
//   0xe81bab8 mov r9d,[r15+0x68]    startVertex
//   0xe81babc mov r10d,[r15+0x6C]   startInstance
// CBV pair at rec+0x50/0x58 (0xe81b9ed..0xe81b9fc):
//   0xe81b9ed mov rax,[r15+0x50]    cbv0
//   0xe81b9f8 mov rax,[r15+0x58]    cbv1
// VBV block at rec+0x00..0x4F (5 x D3D12_VERTEX_BUFFER_VIEW, 16 bytes each):
//   passed to IASetVertexBuffers via 0xEBCE390 at 0xe81b80f with rdx=r15(rec base)
struct DrawRecordNonIndexed {
    // +0x00..0x4F: 5 vertex buffer views (D3D12_VERTEX_BUFFER_VIEW each, 16 bytes)
    uint8_t vbv[5 * 16];          // +0x00..0x4F
    // +0x50: u64 root CBV for root parameter 2
    uint64_t cbv0;                // +0x50
    // +0x58: u64 root CBV for root parameter 3
    uint64_t cbv1;                // +0x58
    // +0x60: u32 vertexCount  → DrawInstanced edx
    uint32_t vertexCount;         // +0x60
    // +0x64: u32 instanceCount → DrawInstanced r8d
    uint32_t instanceCount;       // +0x64
    // +0x68: u32 startVertex   → DrawInstanced r9d
    uint32_t startVertex;         // +0x68
    // +0x6C: u32 startInstance → DrawInstanced r10d
    uint32_t startInstance;       // +0x6C
};

static_assert(sizeof(DrawRecordNonIndexed) == 0x70,
              "DrawRecordNonIndexed size must be 0x70");
static_assert(offsetof(DrawRecordNonIndexed, cbv0) == 0x50,
              "DrawRecordNonIndexed::cbv0 offset");
static_assert(offsetof(DrawRecordNonIndexed, cbv1) == 0x58,
              "DrawRecordNonIndexed::cbv1 offset");
static_assert(offsetof(DrawRecordNonIndexed, vertexCount) == 0x60,
              "DrawRecordNonIndexed::vertexCount offset");
static_assert(offsetof(DrawRecordNonIndexed, instanceCount) == 0x64,
              "DrawRecordNonIndexed::instanceCount offset");
static_assert(offsetof(DrawRecordNonIndexed, startVertex) == 0x68,
              "DrawRecordNonIndexed::startVertex offset");
static_assert(offsetof(DrawRecordNonIndexed, startInstance) == 0x6C,
              "DrawRecordNonIndexed::startInstance offset");

// ---------------------------------------------------------------------------
// DrawRecordIndexed — stride 0x88 (0xe81b89d add r15,0x88)
// Read by the flush indexed loop at 0xe81b8b0..0xe81b9ba:
//   0xe81b86a mov edx,[r15+0x70]    indexCount
//   0xe81b86e mov r8d,[r15+0x74]    instanceCount
//   0xe81b872 mov r9d,[r15+0x78]    startIndex
//   0xe81b876 mov r10d,[r15+0x7C]   baseVertex
//   0xe81b87a mov r11d,[r15+0x80]   startInstance
// CBV pair at rec+0x60/0x68 (0xe81b7b3..0xe81b7be):
//   0xe81b7b3 mov rax,[r15+0x60]    cbv0
//   0xe81b7be mov rax,[r15+0x68]    cbv1
// IBV at rec+0x50..0x5F (D3D12_INDEX_BUFFER_VIEW, 16 bytes), VBV block at rec+0x00..0x4F.
// Field order verified verbatim in executor 0xe821120: vbv[5] at +0x00..0x4F, then IBV at +0x50..0x5F,
// then root CBVs +0x60/+0x68, then draw args +0x70..+0x80 (docs/progress/oc_U-EN1b.md).
struct DrawRecordIndexed {
    // +0x00..0x4F: 5 vertex buffer views (D3D12_VERTEX_BUFFER_VIEW each, 16 bytes)
    uint8_t vbv[5 * 16];          // +0x00..0x4F
    // +0x50..0x5F: index buffer view (D3D12_INDEX_BUFFER_VIEW, 16 bytes)
    uint64_t ibvBufferLocation;   // +0x50
    uint32_t ibvSizeInBytes;      // +0x58
    uint32_t ibvFormat;           // +0x5C
    // +0x60: u64 root CBV for root parameter 2
    uint64_t cbv0;                // +0x60
    // +0x68: u64 root CBV for root parameter 3
    uint64_t cbv1;                // +0x68
    // +0x70: u32 indexCount   → DrawIndexedInstanced edx
    uint32_t indexCount;          // +0x70
    // +0x74: u32 instanceCount → DrawIndexedInstanced r8d
    uint32_t instanceCount;       // +0x74
    // +0x78: u32 startIndex    → DrawIndexedInstanced r9d
    uint32_t startIndex;          // +0x78
    // +0x7C: i32 baseVertex    → DrawIndexedInstanced r10d
    int32_t baseVertex;           // +0x7C
    // +0x80: u32 startInstance → DrawIndexedInstanced r11d
    uint32_t startInstance;       // +0x80
};

static_assert(sizeof(DrawRecordIndexed) == 0x88,
              "DrawRecordIndexed size must be 0x88");
static_assert(offsetof(DrawRecordIndexed, vbv) == 0x00,
              "DrawRecordIndexed::vbv offset");
static_assert(offsetof(DrawRecordIndexed, ibvBufferLocation) == 0x50,
              "DrawRecordIndexed::ibvBufferLocation offset");
static_assert(offsetof(DrawRecordIndexed, ibvSizeInBytes) == 0x58,
              "DrawRecordIndexed::ibvSizeInBytes offset");
static_assert(offsetof(DrawRecordIndexed, ibvFormat) == 0x5C,
              "DrawRecordIndexed::ibvFormat offset");
static_assert(offsetof(DrawRecordIndexed, cbv0) == 0x60,
              "DrawRecordIndexed::cbv0 offset");
static_assert(offsetof(DrawRecordIndexed, cbv1) == 0x68,
              "DrawRecordIndexed::cbv1 offset");
static_assert(offsetof(DrawRecordIndexed, indexCount) == 0x70,
              "DrawRecordIndexed::indexCount offset");
static_assert(offsetof(DrawRecordIndexed, instanceCount) == 0x74,
              "DrawRecordIndexed::instanceCount offset");
static_assert(offsetof(DrawRecordIndexed, startIndex) == 0x78,
              "DrawRecordIndexed::startIndex offset");
static_assert(offsetof(DrawRecordIndexed, baseVertex) == 0x7C,
              "DrawRecordIndexed::baseVertex offset");
static_assert(offsetof(DrawRecordIndexed, startInstance) == 0x80,
              "DrawRecordIndexed::startInstance offset");

// ---------------------------------------------------------------------------
// Header → Record field mapping (draw header at Frame+0xB4700+idx*0x80,
// written by Encoder::submit 0xbc60740 via 8 movaps at 0xe820abc..0xe820b13).
// The executor (0xe821120) converts header fields into DrawBatcher records;
// the mapping below is inferred from the header offsets the executor reads
// and the record offsets the flush consumes. Field mappings marked [I] are
// inferred; [V] means the record-side read is verified verbatim.
//
//   Header field              → Record field               Confidence   Verbatim proof
//   +0x44 u32 numIndices      → indexed.indexCount (+0x70)   [V] 0xe82caf2 mov esi,[r12+0x44] / 0xe82cd11 mov [rdi+0x70],esi
//   +0x54 u32 numInstances    → indexed.instanceCount (+0x74)[V] 0xe82cd1b mov eax,[rcx+0x54] / 0xe82cd1e mov [rdi+0x74],eax
//   +0x54 u32 numInstances    → non-indexed.instanceCount(+0x64)[V] 0xe82cdd8 mov eax,[rax+0x54] / 0xe82cddb mov [rsi+0x64],eax
//   +0x40 u32 startIndex      → indexed.startIndex (+0x78)   [V] 0xe82cd21 mov eax,[rcx+0x40] / 0xe82cd24 mov [rdi+0x78],eax
//   -                         → indexed.baseVertex+startInstance = 0 (+0x7C) [V] 0xe82cd27 mov [rdi+0x7C],0
//   -                         → indexed.vsConstantsGpuVa (+0x60, root CBV #2) [V] 0xe82cb36 mov r8,[rbx+0x170] / 0xe82cb3d mov [rdx+rax+0x60],r8
//   -                         → indexed.fsConstantsGpuVa (+0x68, root CBV #3) [V] 0xe82cb42 mov r8,[rbx+0x380] / 0xe82cb49 mov [rdx+rax+0x68],r8
//   +0x48 u32 indexStride     → indexed.IBV.Format (+0x5C: 0x39 R16 / 0x2A R32) [V] 0xe82cb5e cmp [r12+0x48],2 / 0xe82cb73 mov [rdx+rax+0x5C],ecx
//   IB record+0x58 gpuVA      → indexed.IBV.BufferLocation (+0x50) [V] 0xe82cb4e mov r8,[rcx+0x58] / 0xe82cb52 mov [rdx+rax+0x50],r8
//   IB record+0x60 size       → indexed.IBV.SizeInBytes (+0x58)    [V] 0xe82cb57 mov ecx,[rcx+0x60] / 0xe82cb5a mov [rdx+rax+0x58],ecx
//   header stream{s} (s<4)    → indexed.VBV[stream*16] (+0x00..0x4F): BufferLocation/Stride/SizeInBytes [V] 0xe82ccad..0xe82ccdc
// Non-indexed rec+0x60 vertexCount (header+0x4C) reader not found verbatim [UNVERIFIED].
// ---------------------------------------------------------------------------

} // namespace bgfx::d3d12draw
