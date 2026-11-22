#include "client/features/render/rewrite/RewritePasses.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"

// Q5d detours for pass-level rewrites. Each detour intercepts a pass function called
// through std::function (indirect call). Mode Off => forward to the original. Mode On
// => call our own RewritePasses::* implementation. Shadow/Verify => run the original,
// then run our rewrite on the same inputs; compare pass-record fields before/after
// (GPU-side render-target output cannot be compared statically - see RewritePasses.h).
//
// Pass records are complex objects; the detour does not copy them (no sizeof known,
// no allocator available). Shadow/Verify therefore runs the original on the live
// pass record, then runs the rewrite on the same live record. Any divergence in
// pass-record fields the function writes is a candidate difference; full comparison
// requires knowing which fields are outputs (pending reversal of the body).

// TAAUpscaling 0xbc8ab12 (size 0x2000), sig "RendererContextD3D12::PassTAAUpscaling".
static void __fastcall rwTaaUpscaleDetour(void* _This, void* ctx, void* passRecord);
static RewriteEntry sTaaEntry("Pass::TAAUpscaling", "RendererContextD3D12::PassTAAUpscaling", 0xbc8ab12,
                       reinterpret_cast<void*>(&rwTaaUpscaleDetour));
static RewriteReg sTaaReg(sTaaEntry);

// ScreenDraw 0xbc04dc0 (size 0x2000), sig "RendererContextD3D12::PassScreenDraw".
static void __fastcall rwScreenDrawDetour(void* _This, void* ctx, void* passRecord);
static RewriteEntry sScreenDrawEntry("Pass::ScreenDraw", "RendererContextD3D12::PassScreenDraw", 0xbc04dc0,
                              reinterpret_cast<void*>(&rwScreenDrawDetour));
static RewriteReg sScreenDrawReg(sScreenDrawEntry);


void __fastcall RewritePasses::taaUpscale(void* _This, void* ctx, void* passRecord)
{
    // Our own upscale pass implementation (stub pending full body reversal).
    // Reads: passRecord+0x168 (rect min), +0x16C (rect max), +0x178 (flag byte),
    //        passRecord+0x268 (name string), +0x278 (name length).
    // Writes: render targets via the D3D12 command list (not directly comparable).
    (void)_This;
    (void)ctx;
    (void)passRecord;
}

void __fastcall RewritePasses::screenDraw(void* _This, void* ctx, void* passRecord)
{
    // Our own fullscreen post pass implementation (stub pending full body reversal).
    // Reads: passRecord+0x168/+0x16C (rect), +0x178 (flag byte), +0x268 (name),
    //        +0x278 (name length). Writes view rect + 4 mat4 into s_ctx->views[],
    //        binds material/state/uniforms/textures, submits via 0xbcc38e0.
    (void)_This;
    (void)ctx;
    (void)passRecord;
}

void __fastcall rwTaaUpscaleDetour(void* _This, void* ctx, void* passRecord)
{
    RewriteEntry& e = sTaaEntry;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
        return e.original<&rwTaaUpscaleDetour>()(_This, ctx, passRecord);
    if (mode == RewriteMode::On) {
        RewriteTimed timed(e, e.ticksRewrite);
        return RewritePasses::taaUpscale(_This, ctx, passRecord);
    }
    // Shadow / Verify: run the original on the live pass record, then our rewrite.
    // Outputs are GPU-side; no byte comparison possible without a frame-buffer capture.
    // The call is counted as evaluated; a field-level comparison is left as TODO.
    RewriteBusy::Scope busy;
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&rwTaaUpscaleDetour>()(_This, ctx, passRecord);
    }
    e.evaluated.fetch_add(1, std::memory_order_relaxed);
    RewritePasses::taaUpscale(_This, ctx, passRecord);
}

void __fastcall rwScreenDrawDetour(void* _This, void* ctx, void* passRecord)
{
    RewriteEntry& e = sScreenDrawEntry;
    const uint64_t calls = e.calls.fetch_add(1, std::memory_order_relaxed);
    const RewriteMode mode = e.current();
    if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
        return e.original<&rwScreenDrawDetour>()(_This, ctx, passRecord);
    if (mode == RewriteMode::On) {
        RewriteTimed timed(e, e.ticksRewrite);
        return RewritePasses::screenDraw(_This, ctx, passRecord);
    }
    RewriteBusy::Scope busy;
    {
        RewriteTimed timed(e, e.ticksOriginal);
        e.original<&rwScreenDrawDetour>()(_This, ctx, passRecord);
    }
    e.evaluated.fetch_add(1, std::memory_order_relaxed);
    RewritePasses::screenDraw(_This, ctx, passRecord);
}
