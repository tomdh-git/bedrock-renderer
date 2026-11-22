#pragma once

// D3D12 draw flush / draw executor wrap seam — Q4b (instancing/batch merge, state dedup, PSO key cache).
// Every RVA below was verified verbatim in the disassembly of
// C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe.
// See docs/progress/oc_U-EQ4b.md section (3) for the full verbatim proof table.
//
// Targets:
//   drawFlush     0xe81b720 — flush(kind): batcher in rcx ([batcher+0x10] = u32 pending[2],
//                               [batcher+0x18] = record arrays), command list via [job+0x30], kind in r9d
//   drawExecutor  0xe821120 — per-job item loop; flush call sites:
//                               0xe822e4e, 0xe822e6b, 0xe82cfc1, 0xe82cfde, 0xe82d0f6, 0xe82d12b, 0xe82d148
//   psoBuilder    0xe81e860 — PSO key = state & 0x0707007FFFFFF0FF (program table ctx+0xB62178, stride 0xF8)
//
// This header is the on-disk part of the wrap. It is header-only (no CMake change) and registers nothing:
// HookManager.cpp and existing hook registrations are off-limits to this unit. Registration at the 7 flush
// call sites, a build, an in-game run and a stream diff are the remaining step (see the unit file).
//
// Fail-fast style (CLAUDE.md): preconditions are asserted, no null guards, no SEH.


namespace bgfx::d3d12wrap {

// Offsets inside the draw executor's job state (rbx at the flush call sites, e.g. 0xe822e4e:
// mov rcx,[rbx+0x250] batcher; mov r8,[rbx+0x90] wrapper; command list = [[rbx+0x90]+0x30]).
static constexpr std::size_t kJobBatcher = 0x250;   // the DrawBatcher the executor fills and flush drains
static constexpr std::size_t kJobWrapper = 0x90;    // command-list wrapper object
static constexpr std::size_t kWrapperCommandList = 0x30; // ID3D12GraphicsCommandList* at [wrapper+0x30]

// Record strides used by the flush loops: 0xe81ba9f add r15,0x70 (non-indexed),
// 0xe81b89d add r15,0x88 (indexed).
static constexpr std::size_t kRecordNonIndexed = 0x70;
static constexpr std::size_t kRecordIndexed = 0x88;

// PSO key cache key. psoBuilder 0xe81e860: mov rsi,0x707007FFFFFF0FF at 0xe81e8ec,
// and rsi,r13 at 0xe81e8f6 → key = state & 0x0707007FFFFFF0FF over the program table at
// ctx+0xB62178 (add rbx,0xB62178 at 0xe81e8e5, stride imul rax,0xF8 at 0xe81e8d7).
static constexpr uint64_t kPsoKeyMask = 0x0707007FFFFFF0ull;
inline uint64_t psoKey(uint64_t state) noexcept { return state & kPsoKeyMask; }

// Executor batch-merge test (0xe822dae .. 0xe822e2a, docs/functions/e821120.md part 3): a draw joins the
// open batch iff bind hash, stencil, program, blend state, primitive type (state bits 48-50,
// mask 0x0007000000000000: mov rcx,0x7000000000000 at 0xe822db5; and rax,rcx at 0xe822dbf),
// topology, scissor and PSO all match, and state bit 62 (0x4000000000000000:
// mov rcx,... at 0xe822e1d; and at 0xe822e27) is clear. Merging = one instanced draw whose
// instanceCount accumulates.
struct DrawKey {
    uint32_t bindHash = 0;
    uint8_t stencil = 0;
    uint32_t program = 0xFFFFFFFFu;
    uint64_t state = 0;
    uint32_t topology = 0xFFFFFFFFu;
    uint16_t scissor = 0xFFFFu;
    uintptr_t pso = 0;
};
inline bool batchMergeable(const DrawKey& a, const DrawKey& b) noexcept
{
    if (a.bindHash != b.bindHash) return false;
    if (a.stencil != b.stencil) return false;
    if (a.program != b.program) return false;
    if ((a.state ^ b.state) & 0x0007000000000000ull) return false; // primitive type changed
    if ((a.state | b.state) & 0x4000000000000000ull) return false; // bit 62: never batch
    if (a.topology != b.topology) return false;
    if (a.scissor != b.scissor) return false;
    if (a.pso != b.pso) return false;
    return true;
}

// State dedup at the flush (0xe81baee / 0xe81bafd / 0xe81bb60): skip rebind when equal to the cached
// values (lastCbv at batcher+0x1120/+0x1128, vbCache at +0x10C0, ibCache at +0x1110).
struct BatcherCaches {
    uint64_t lastCbv[2]; // +0x1120, root CBV addresses for root params 2 and 3
    uint8_t vbCache[5 * 16]; // +0x10C0, last 5 vertex buffer views (5 x D3D12_VERTEX_BUFFER_VIEW)
    uint8_t ibCache[16]; // +0x1110, last index buffer view (D3D12_INDEX_BUFFER_VIEW)
};
inline bool skipCbvPair(const BatcherCaches& c, uint64_t cbv0, uint64_t cbv1) noexcept
{
    return c.lastCbv[0] == cbv0 && c.lastCbv[1] == cbv1;
}
inline bool skipVbvBlock(const BatcherCaches& c, const void* vbvBlock) noexcept
{
    assert(vbvBlock != nullptr);
    return std::memcmp(c.vbCache, vbvBlock, 5 * 16) == 0;
}
inline bool skipIbv(const BatcherCaches& c, const void* ibv) noexcept
{
    assert(ibv != nullptr);
    return std::memcmp(c.ibCache, ibv, 16) == 0;
}

// One draw as recorded at the flush seam; one JSON object per flush invocation (fixed field order) forms
// the "recorded D3D12 call stream" compared by tools/sigs/drawstream_compare.py.
struct StreamDraw {
    uint32_t count;        // indexCount or vertexCount
    uint32_t instanceCount;
    uint32_t startIndex;   // startIndexLocation (indexed) / startVertex (non-indexed)
    int32_t baseVertex;    // indexed only
    uint32_t startInstance;
    uint64_t cbv0;
    uint64_t cbv1;
};
struct StreamFlush {
    uint32_t kind;        // 0 non-indexed (BatchDraw), 1 indexed (BatchDrawIndexed)
    uint32_t pending;     // records flushed this invocation
    uint64_t cbv0;
    uint64_t cbv1;
    uint8_t vbvDirty;     // 1 if IASetVertexBuffers was issued, else deduped
    uint8_t ibvDirty;     // 1 if IASetIndexBuffer was issued, else deduped
    std::vector<StreamDraw> draws;
};

// DrawFlushRecorder: appended to by the wrap at each of the 7 flush call sites before the real flush runs.
// The wrap reads batcher = [job+0x250], kind = r9d, pending = u32[batcher+0x10+kind*4],
// records = [batcher+0x18+kind*8], command list = [[job+0x90]+0x30].
class DrawFlushRecorder {
public:
    void onFlush(uint32_t kind, uint32_t pending, uint64_t cbv0, uint64_t cbv1,
                 uint8_t vbvDirty, uint8_t ibvDirty,
                 StreamDraw* draws, std::size_t numDraws) noexcept
    {
        StreamFlush f;
        f.kind = kind;
        f.pending = pending;
        f.cbv0 = cbv0;
        f.cbv1 = cbv1;
        f.vbvDirty = vbvDirty;
        f.ibvDirty = ibvDirty;
        f.draws.assign(draws, draws + numDraws);
        m_stream.push_back(std::move(f));
    }
    const std::vector<StreamFlush>& stream() const noexcept { return m_stream; }
    void clear() noexcept { m_stream.clear(); }

private:
    std::vector<StreamFlush> m_stream;
};

} // namespace bgfx::d3d12wrap
