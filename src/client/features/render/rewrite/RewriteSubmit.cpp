#include "RewriteSubmit.h"

namespace {
// Per-frame counters the takeover shim observes. Read-only for the game: no game memory
// is written here, only walked (docs/BGFX_MAP.md 8a: submit walks Frame+0xB4700, stride 0x80).
std::atomic<uint64_t> sDrawsWalked{0};
std::atomic<uint64_t> sDrawNs{0};
std::atomic<uint64_t> sFrames{0};
// Q4d: per-draw veto/rewrite stats (On mode applies the veto; Shadow/Verify count only).
std::atomic<uint64_t> sDrawsVetoed{0};
std::atomic<uint64_t> sDrawsRewritten{0};
} // namespace

// Q4d verdict policy: read-only (reads header fields only). Veto = the draw is an
// occlusion-query draw (stateFlags bit 62 set), which the executor already special-cases;
// vetoing it means zeroing header+0x63 streamMask so the executor skips it entirely.
// Rewrite = record-only by default: the rewrite shape (touching the same header fields the
// executor consumes: stateFlags +0x20, submitFlags +0x62, occlusionQuery +0x7A,
// streamMask +0x63) is proven; no field is changed until a policy selects one.
RenderSubmit::DrawVerdict RenderSubmit::DrawVetoPolicy::verdict(const bgfx::Frame*, const uint8_t* header)
{
    const uint64_t state =
        *reinterpret_cast<const uint64_t*>(header + bgfx::RenderDrawHeader::kState); // +0x20
    if ((state >> 62) & 1ull) // BGFX_STATE_INTERNAL_OCCLUSION_QUERY
        return DrawVerdict::Veto;
    return DrawVerdict::Allow;
}

void __fastcall RenderSubmit::takeover(bgfx::RendererContext* ctx, bgfx::Frame* frame, uintptr_t a3, uintptr_t a4)
{
    // ---- takeover: observe + per-draw veto/rewrite + forward (contract in RewriteSubmit.h) ----
    uint8_t* f = reinterpret_cast<uint8_t*>(frame);

    // Renderer-state fast path, mirrors 0xe82e273: state < 5 => the original submits nothing.
    if (*reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(ctx) + 0x19F88) < 5u) {
        RenderSubmit::entry.original<&RenderSubmit::takeover>()(ctx, frame, a3, a4);
        return;
    }

    // QPC-style timer around the per-draw walk (submit's own stats/timers are inline, 0xe82e332).
    const uint64_t t0 = __rdtsc();

    const bool apply = RenderSubmit::entry.current() == RewriteMode::On; // only On writes game memory
    const uint32_t count =
        *reinterpret_cast<const uint32_t*>(f + bgfx::FrameOffsets::kItemCount); // Frame+0xDC57E8, cap 0xFFFE
    uint64_t draws = 0;
    for (uint32_t i = 0; i < count; ++i) {
        uint8_t* h = f + bgfx::FrameOffsets::kDrawHeaders + i * bgfx::RenderDrawHeader::kSize; // +0xB4700, stride 0x80
        ++draws;
        const DrawVerdict v = DrawVetoPolicy::verdict(frame, h);
        switch (v) {
        case DrawVerdict::Veto:
            ++sDrawsVetoed;
            if (apply)
                *reinterpret_cast<uint8_t*>(h + bgfx::RenderDrawHeader::kStreamMask) = 0; // +0x63 -> executor skips (0xe822b92/e822b98/e822b9b)
            break;
        case DrawVerdict::Rewrite:
            ++sDrawsRewritten; // record-only: no field changed by default
            break;
        case DrawVerdict::Allow:
            break;
        }
    }

    sDrawsWalked.fetch_add(draws, std::memory_order_relaxed);
    sDrawNs.fetch_add(__rdtsc() - t0, std::memory_order_relaxed);
    ++sFrames;

    // ---- forward to the original submit through the RewriteRegistry trampoline ----
    RenderSubmit::entry.original<&RenderSubmit::takeover>()(ctx, frame, a3, a4);
}

RewriteEntry RenderSubmit::entry{
    "RendererContextD3D12::submit",             // registry key + profiler row
    "RendererContextD3D12::submit",    // Sigs.json symbol (already present at line 159)
    RenderSubmit::kSubmitRva,                   // 0xe82e230 on 1.26.62.01; install() fatals if the resolved sig disagrees
    reinterpret_cast<void*>(&RenderSubmit::takeover),
    false                                       // not hosted: we own slot 50 ourselves
};
static RewriteReg gRenderSubmitReg{RenderSubmit::entry}; // registers the entry at static init (mode Off: nothing installs)
