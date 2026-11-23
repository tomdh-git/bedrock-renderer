#pragma once

// Q5d: Pass-level rewrites (own upscale, own post) behind the registry.
//
// Two pass functions are registered as rewrite targets (see RewritePasses.cpp):
//   1. TAAUpscaling 0xbc8ab12 (size 0x2000) - the engine's TAA upscale pass body
//   2. ScreenDraw 0xbc04dc0 (size 0xbc04dc0..0xbc06dc0, size 0x2000) - the shared
//      fullscreen post-pass body used by ColorPostProcess and other ScreenDraw passes.
//
// Both are invoked through std::function (indirect call, 0 xrefs in), so detouring the
// function address intercepts every call site. Each rewrite keeps the same signature:
//
//   void __fastcall(void* _This /*rcx: std::function callable, unused*/,
//                   void* ctx /*rdx: render context*/,
//                   void* passRecord /*r8: pass record, name std::string at +0x268*/)
//
// Mode Off   -> forward to the original (game runs untouched).
// Mode On    -> call our own RewritePasses::* implementation.
// Shadow/Verify -> run the original, then run our rewrite; compare pass-record fields
//   that the function reads/writes. GPU-side render-target output cannot be compared
//   statically (needs a frame-buffer capture), so Shadow/Verify for passes is limited
//   to the pass-record mutation delta; this is noted per entry.
//
// Nothing is enabled by default: RewriteRegistry installs detours only when BS_REWRITE
// sets a non-Off mode (or setMode is called from a debug UI).


namespace bgfx {
struct PassRecord; // the pass record (r8 in ScreenDraw; name std::string at +0x268)
struct RenderContext; // render context (rdx in ScreenDraw; s_ctx global at [0x12AE1748])
} // namespace bgfx

struct RewritePasses {
    // Our own TAA upscale pass. Reads pass-record fields at proven offsets (+0x28,
    // +0x50, +0x78 via BB5 field gather) and calls the proven sub-blocks the original
    // TAAUpscaling body invokes: sub_130ee0 (0xbc8b41c), sub_568c420 (0xbc8b43f),
    // sub_5693A80 x3 (0xbc8b453). Unproven blocks (sub_5668ac0 name registration,
    // TAA resolve/jitter/history-blend path) are NOT called; registry mode left Off.
    static void __fastcall taaUpscale(void* _This, void* ctx, void* passRecord);

    // Our own fullscreen post pass. Replicates ScreenDraw body 0xbc04dc0: view rect
    // write (+0x168/+0x16C -> s_ctx view +0x1EAB090/+0x1EAB094), 5x sub_ebce390 mat4/
    // vec4 copies (+0x128/+0x17C/+0x1BC/+0x1FC -> view +0x1EAB0A0/0E0/120/160/1A0),
    // flag byte (+0x178 -> view +0x1EAB1B2), draw setup 0xE86D7F0, bind chain
    // 0xBCC3190/0xBCC1910(+0x20C)/0xBCC24F0(+0x170)/0xBCC2B00(+0x88)/0xBCC2EB0(+0x88),
    // submit 0xBCC38E0. Unproven blocks (0x30 object, name build, id counter,
    // per-element loop, cleanup) are NOT called; registry mode left Off.
    static void __fastcall screenDraw(void* _This, void* ctx, void* passRecord);
};
