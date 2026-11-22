#include "RewriteSubmit.h"


namespace {
// Per-frame counters the takeover shim observes. Read-only for the game: no game memory
// is written here, only walked (docs/BGFX_MAP.md 8a: submit walks Frame+0xB4700, stride 0x80).
std::atomic<uint64_t> sDrawsWalked{0};
std::atomic<uint64_t> sDrawNs{0};
std::atomic<uint64_t> sFrames{0};
} // namespace

void __fastcall RenderSubmit::takeover(bgfx::RendererContext* ctx, bgfx::Frame* frame, uintptr_t a3, uintptr_t a4)
{
    // ---- takeover: observe + forward (contract in RewriteSubmit.h) ----
    const uint8_t* f = reinterpret_cast<const uint8_t*>(frame);

    // Renderer-state fast path, mirrors 0xe82e273: state < 5 => the original submits nothing.
    if (*reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(ctx) + 0x19F88) < 5u) {
        RenderSubmit::entry.original<&RenderSubmit::takeover>()(ctx, frame, a3, a4);
        return;
    }

    // QPC-style timer around the per-draw walk (submit's own stats/timers are inline, 0xe82e332).
    const uint64_t t0 = __rdtsc();

    const uint32_t count =
        *reinterpret_cast<const uint32_t*>(f + bgfx::FrameOffsets::kItemCount); // Frame+0xDC57E8, cap 0xFFFE
    uint64_t draws = 0;
    for (uint32_t i = 0; i < count; ++i) {
        const bgfx::RenderDraw* h = reinterpret_cast<const bgfx::RenderDraw*>(
            f + bgfx::FrameOffsets::kDrawHeaders + i * bgfx::RenderDrawHeader::kSize); // +0xB4700, stride 0x80
        ++draws;
        // Per-draw stats candidates (all [V]-pinned in Frame.h, read-only here):
        //   h->stateFlags       +0x20 u64 (executor tests byte +0x23)
        //   h->streamMask       +0x63 u8
        //   h->indexBuffer      +0x74 u16 (0xFFFF = non-indexed)
        //   h->instanceDataBuffer +0x76 u16 (0xFFFF = none)
        (void)h;
    }

    sDrawsWalked.fetch_add(draws, std::memory_order_relaxed);
    sDrawNs.fetch_add(__rdtsc() - t0, std::memory_order_relaxed);
    ++sFrames;

    // ---- forward to the original submit through the RewriteRegistry trampoline ----
    RenderSubmit::entry.original<&RenderSubmit::takeover>()(ctx, frame, a3, a4);
}

RewriteEntry RenderSubmit::entry{
    "RendererContextD3D12::submit",             // registry key + profiler row
    "RendererContextD3D12::submit",    // Sigs.json symbol (appended in this unit)
    RenderSubmit::kSubmitRva,                   // 0xe82e230 on 1.26.62.01; install() fatals if the resolved sig disagrees
    reinterpret_cast<void*>(&RenderSubmit::takeover),
    false                                       // not hosted: we own slot 50 ourselves
};
static RewriteReg gRenderSubmitReg{RenderSubmit::entry}; // registers the entry at static init (mode Off: nothing installs)
