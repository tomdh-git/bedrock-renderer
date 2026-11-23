#pragma once
// Draw batch record layouts consumed by D3D12Context::drawFlush (0xe81b720) and
// built by D3D12Context::drawExecutor (0xe821120) from the 0x80-byte draw
// headers at Frame::kDrawHeaders = Frame+0xB4700 (stride 0x80).
//
// The headers are written verbatim by bgfx::EncoderImpl::submit (0xbc60740):
//   idx = CAS(Frame+0xDC57E8, cap 0xFFFE);            // 0xbc607bf..0xbc607fd
//   movaps x5 Encoder::m_draw -> Frame+0xB4700 + (idx << 7)   // 0xbc60abc..0xbc60b13
// so every draw of the game lands in this array before the executor sees it.
// Verbatim instruction map header field -> record field -> GPU draw args:
// docs/progress/oc_U-EP3c.md.
//
// Two record kinds, selected by the header index-buffer handle (header+0x74,
// u16, 0xFFFF = non-indexed). Header+0x78 (u16 indirectBuffer, 0xFFFF = batched)
// selects the ExecuteIndirect path.
//   kind 0: DrawRecordNonIndexed, stride 0x70   -> DrawInstanced   (slot 12)
//   kind 1: DrawRecordIndexed,   stride 0x88   -> DrawIndexedInstanced (slot 13)
//
// VBVs: 5 x D3D12_VERTEX_BUFFER_VIEW at record+0x00, stride 0x10
//   +0x00 BufferLocation (qword), +0x08 SizeInBytes (dword), +0x0C StrideInBytes (dword)
//   built by fillVertexBufferViews (0xe81b4d0) from the header stream array
//   (header+s*8 = {u32 startVertex, u16 vbHandle, u16 layout}, s<4; streamMask u8 at +0x63)
//   and the vertex-buffer record table at ctx+0x9B2178 (0x80 stride; record fields
//   +0x50/+0x54/+0x58 read verbatim at 0xe82ccbb/0xe82ccd8/0xe82cccc).
//
// The flush (0xe81b720) also binds record+0x50/+0x58 as root CBVs #2/#3 and, for
// indexed records, the IBV at record+0x50 ({gpuVA qword +0x00, SizeInBytes dword
// +0x10, DXGI format dword +0x14}) plus IASetVertexBuffers(rec+0x00), then:
//   DrawInstanced(rec+0x60, rec+0x64, rec+0x68, rec+0x6C)
//   DrawIndexedInstanced(rec+0x70, rec+0x74, rec+0x78, rec+0x7C, rec+0x80)
// All offsets below are read as immediates/displacements by the executor or the
// flush; role names tagged [V] = instruction shows the read/store, [I] = role inferred.


namespace bgfx {

struct D3d12Vbv {                 // 0x10 bytes, D3D12_VERTEX_BUFFER_VIEW shape
    uint64_t bufferLocation;      // +0x00
    uint32_t sizeInBytes;         // +0x08
    uint32_t strideInBytes;       // +0x0C
};
static_assert(sizeof(D3d12Vbv) == 0x10);

// Non-indexed draw record, 0x70 bytes, kind 0 (header+0x74 == 0xFFFF).
struct DrawRecordNonIndexed {
    D3d12Vbv vbv[5];              // +0x00..0x4F  [V: 0xe82cb8b call 0xe81b4d0, store 0xe82ccc8 mov [rdi+rax],rcx]
    uint64_t vsConstantsGpuVa;    // +0x50 root CBV #2              [V: 0xe81ba07 mov r8,[r15+0x50]]
    uint64_t fsConstantsGpuVa;    // +0x58 root CBV #3              [V: 0xe81ba24 mov r8,[r15+0x58]]
    uint32_t vertexCountPerInstance;// +0x60 = header numVertices +0x4C [V chain: 0xe81b4f4 mov eax,[r8+0x4C] -> 0xe82cdde mov eax,[rbx+0xC0] -> 0xe82cde4 mov [rsi+0x60],eax]
    uint32_t instanceCount;       // +0x64 = header numInstances +0x54 [V: 0xe82cdd8 mov eax,[rax+0x54] -> 0xe82cddb mov [rsi+0x64],eax]
    uint32_t startVertexLocation; // +0x68 = 0                      [V: 0xe81cde7 mov qword ptr [rsi+0x68],0]
    uint32_t startInstanceLocation;// +0x6C = 0                     [same store]
};
static_assert(sizeof(DrawRecordNonIndexed) == 0x70);
static_assert(offsetof(DrawRecordNonIndexed, vbv) == 0x00);
static_assert(offsetof(DrawRecordNonIndexed, vsConstantsGpuVa) == 0x50);
static_assert(offsetof(DrawRecordNonIndexed, fsConstantsGpuVa) == 0x58);
static_assert(offsetof(DrawRecordNonIndexed, vertexCountPerInstance) == 0x60);
static_assert(offsetof(DrawRecordNonIndexed, instanceCount) == 0x64);
static_assert(offsetof(DrawRecordNonIndexed, startVertexLocation) == 0x68);
static_assert(offsetof(DrawRecordNonIndexed, startInstanceLocation) == 0x6C);

// Indexed draw record, 0x88 bytes, kind 1 (header+0x74 indexBuffer != 0xFFFF).
// Field order verified verbatim in executor 0xe821120 record build (0xe82caf2..0xe82cd27) and by the
// flush dossier (0xe81b720: VBVs at rec+0x00, IBV at rec+0x50, root CBVs at +0x60/+0x68, args at +0x70..).
// NOTE: vbv[5] at +0x00 comes BEFORE the ibv at +0x50 (an earlier draft had them swapped).
struct DrawRecordIndexed {
    D3d12Vbv vbv[5];              // +0x00..0x4F  [V: 0xe82ccad movzx eax,r12b / 0xe82ccc8 mov [rdi+rax],rcx / 0xe82ccd0 mov [rdi+rax+0xC],ecx / 0xe82ccdc mov [rdi+rax+8],ecx]
    // +0x50..0x5F D3D12_INDEX_BUFFER_VIEW:
    uint64_t ibvBufferLocation;   // +0x50 gpuVA = index-buffer record +0x58 at ctx+0x93A178[handle*0x78] [V: 0xe82cb4e mov r8,[rcx+0x58] -> 0xe82cb52 mov [rdx+rax+0x50],r8]
    uint32_t ibvSizeInBytes;      // +0x58 = index-buffer record size +0x60 [V: 0xe82cb57 mov ecx,[rcx+0x60] -> 0xe82cb5a mov [rdx+rax+0x58],ecx]
    uint32_t ibvFormat;           // +0x5C 0x39 DXGI_FORMAT_R16_UINT when header indexStride +0x48 == 2, else 0x2A R32_UINT [V: 0xe82cb5e cmp [r12+0x48],2 / 0xe82cb64 mov ecx,0x2A / 0xe82cb69 mov r8d,0x39 / 0xe82cb6f cmove ecx,r8d / 0xe82cb73 mov [rdx+rax+0x5C],ecx]
    uint64_t vsConstantsGpuVa;    // +0x60 root CBV #2              [V: 0xe82cb36 mov r8,[rbx+0x170] -> 0xe82cb3d mov [rdx+rax+0x60],r8]
    uint64_t fsConstantsGpuVa;    // +0x68 root CBV #3              [V: 0xe82cb42 mov r8,[rbx+0x380] -> 0xe82cb49 mov [rdx+rax+0x68],r8]
    uint32_t indexCount;          // +0x70 = header numIndices +0x44 (0xFFFFFFFF = computed as ib.size/stride) [V: 0xe82caf2 mov esi,[r12+0x44] -> 0xe82cd11 mov [rdi+0x70],esi]
    uint32_t instanceCount;       // +0x74 = header numInstances +0x54 [V: 0xe82cd1b mov eax,[rcx+0x54] -> 0xe82cd1e mov [rdi+0x74],eax]
    uint32_t startIndexLocation;  // +0x78 = header startIndex +0x40 [V: 0xe82cd21 mov eax,[rcx+0x40] -> 0xe82cd24 mov [rdi+0x78],eax]
    int32_t baseVertexLocation;   // +0x7C = 0                      [V: 0xe82cd27 mov qword ptr [rdi+0x7C],0 covers +0x7C..+0x87]
    uint32_t startInstanceLocation;// +0x80 = 0                     [same store]
};
static_assert(sizeof(DrawRecordIndexed) == 0x88);
static_assert(offsetof(DrawRecordIndexed, vbv) == 0x00);
static_assert(offsetof(DrawRecordIndexed, ibvBufferLocation) == 0x50);
static_assert(offsetof(DrawRecordIndexed, ibvSizeInBytes) == 0x58);
static_assert(offsetof(DrawRecordIndexed, ibvFormat) == 0x5C);
static_assert(offsetof(DrawRecordIndexed, vsConstantsGpuVa) == 0x60);
static_assert(offsetof(DrawRecordIndexed, fsConstantsGpuVa) == 0x68);
static_assert(offsetof(DrawRecordIndexed, indexCount) == 0x70);
static_assert(offsetof(DrawRecordIndexed, instanceCount) == 0x74);
static_assert(offsetof(DrawRecordIndexed, startIndexLocation) == 0x78);
static_assert(offsetof(DrawRecordIndexed, baseVertexLocation) == 0x7C);
static_assert(offsetof(DrawRecordIndexed, startInstanceLocation) == 0x80);

// DrawBatcher fields used by the flush (0xe81b720), all verified verbatim:
//   +0x10  u32 pending[2]        [0]=non-indexed, [1]=indexed; consumed then zeroed (0xe81b736/0xe81b74a)
//   +0x18  void* records[2]      record array base per kind (0xe81b79e)
//   +0x10C0 u8 vbCache[0x50]     last VBV block (memcmp against record+0x00)
//   +0x1110 u8 ibCache[0x10]     last IBV (memcmp against record+0x50)
//   +0x1120/+0x1128 u64 last CBV pair (record+0x60/+0x68 indexed, +0x50/+0x58 non-indexed)
//   +0x1148/+0x1150 u32 direct/overflow stats
//   +0x115C u32 capacity
//   +0x1164 u8 indirectEnabled
struct DrawBatcher {              // sizes of the individual members below are not proven; use the offsets only
    uint8_t pad0[0x10];
    uint32_t pending[2];        // +0x10
    void* records[2];           // +0x18
};

// Header (Frame+0xB4700 + idx*0x80, stride 0x80) -> DrawBatcher record mapping,
// proven verbatim in executor 0xe821120 record build (docs/progress/oc_U-EN1b.md):
//   header+0x44 numIndices    -> indexed rec+0x70 indexCount            [V 0xe82caf2 / 0xe82cd11]
//   header+0x54 numInstances  -> indexed rec+0x74 instanceCount         [V 0xe82cd1b / 0xe82cd1e]
//   header+0x54 numInstances  -> non-indexed rec+0x64 instanceCount     [V 0xe82cdd8 / 0xe82cddb]
//   header+0x40 startIndex    -> indexed rec+0x78 startIndex            [V 0xe82cd21 / 0xe82cd24]
//   rec+0x7C baseVertex+startInstance = 0                               [V 0xe82cd27]
//   rec+0x60 vsConstantsGpuVa (root CBV #2)                             [V 0xe82cb36 / 0xe82cb3d]
//   rec+0x68 fsConstantsGpuVa (root CBV #3)                             [V 0xe82cb42 / 0xe82cb49]
//   header+0x48 indexStride   -> indexed rec+0x5C IBV.Format (0x39/0x2A)[V 0xe82cb5e..0xe82cb73]
//   IB record+0x58 gpuVA      -> indexed rec+0x50 IBV.BufferLocation    [V 0xe82cb4e / 0xe82cb52]
//   IB record+0x60 size       -> indexed rec+0x58 IBV.SizeInBytes       [V 0xe82cb57 / 0xe82cb5a]
//   header stream{s} (s<4)    -> indexed rec VBV[stream*16]: BufferLocation, Stride(+0x58), SizeInBytes(stride*numInstances) [V 0xe82ccad..0xe82ccdc]
// Non-indexed rec+0x60 vertexCount (header+0x4C) reader not found verbatim [UNVERIFIED].

// Seam RVAs for "edit draws at submit" (M3e / P3c):
//   RendererContextD3D12::submit slot 50 = 0xe82e230 (live RTX override 0xe83d440 on vtable 0xF4EEE80):
//     replacement submit walks Frame+0xB4700 headers (count Frame+0xDC57E8, cap 0xFFFE)
//     before the executor consumes them.
//   Per-draw veto/rewrite at the flush: hook D3D12Context::drawFlush 0xe81b720;
//     set pending[kind] = 0 at batcher+0x10+kind*4 to skip a whole batch, or edit
//     record fields in place (stride 0x70 / 0x88) before they reach the GPU.
//   Executor (0xe821120) flush call sites: 0xe822e4e, 0xe822e6b, 0xe82cfc1, 0xe82cfde,
//   0xe82d0f6, 0xe82d12b, 0xe82d148.
// None of these is registered or patched by this header; it documents the seam only.

} // namespace bgfx
