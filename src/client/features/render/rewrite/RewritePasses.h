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
    // Our own TAA upscale pass. Reads the pass record (render-target bindings, rect,
    // parameters at known offsets) and emits equivalent draw commands.
    // Full reversal of 0xbc8ab12..0xbc8cb12 (0x2000 bytes) is pending; On mode is a
    // stub until the body is decoded.
    static void __fastcall taaUpscale(void* _This, void* ctx, void* passRecord);

    // Our own fullscreen post pass. Binds material/state/uniforms/textures, submits a
    // fullscreen-quad draw through the executor. Reads pass record at r8: rect +0x168/
    // +0x16C, flag byte +0x178, name string +0x268 (length +0x278).
    // Full reversal of 0xbc04dc0..0xbc06dc0 (0x2000 bytes) is pending; On mode is a
    // stub until the body is decoded.
    static void __fastcall screenDraw(void* _This, void* ctx, void* passRecord);
};
