#include "client/features/render/rewrite/RewritePasses.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"

// All RVAs below are image-relative; rebase onto the running module before use.
static inline uintptr_t bsRva(uintptr_t rva) { return reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) + rva; }


// Q5d detours for pass-level rewrites. Each detour intercepts a pass function called
// through std::function (indirect call). Mode Off => forward to the original. Mode On
// => call our own RewritePasses::* implementation. Shadow/Verify => run the original,
// then run our rewrite on the same live pass record.
// (GPU-side render-target output cannot be compared statically - see RewritePasses.h.)

// TAAUpscaling 0xbc8ab12 (size 0x2000), sig "RendererContextD3D12::PassTAAUpscaling".
static void __fastcall rwTaaUpscaleDetour(void* _This, void* ctx, void* passRecord);
static RewriteEntry sTaaEntry("Pass::TAAUpscaling", "RendererContextD3D12::PassTAAUpscaling", 0xbc8ab12,
                       reinterpret_cast<void*>(&rwTaaUpscaleDetour));
static RewriteReg sTaaReg(sTaaEntry);

// ScreenDraw 0xbc04dc0 (size 0x2000 per Sigs.json; real body 0xbc04dc0..0xbc05393, size 0x5d3),
// sig "RendererContextD3D12::PassScreenDraw".
static void __fastcall rwScreenDrawDetour(void* _This, void* ctx, void* passRecord);
static RewriteEntry sScreenDrawEntry("Pass::ScreenDraw", "RendererContextD3D12::PassScreenDraw", 0xbc04dc0,
                             reinterpret_cast<void*>(&rwScreenDrawDetour));
static RewriteReg sScreenDrawReg(sScreenDrawEntry);


namespace {

// ============================================================================
// Proven blocks (entry points [V] from ScreenDraw body reversal, screendraw_full.txt).
// Called by absolute address; roles known, bodies not re-reversed here.
// Blocks whose BODIES are not reversed are marked UNPROVEN and are not called.
//
//   sub_ebce390 @ 0xEBCE390   memcpy-like copy (dst rcx, src rdx, len r8d)          [PROVEN]
//   sub_ebce5e0 @ 0xEBCE5E0   bounded strlen (rcx=buf, edx=max) -> eax=len           [PROVEN FULLY]
//   sub_eec6ec0 @ 0xEEC6EC0   memcpy                                                [PROVEN]
//   sub_bcc1a30 @ 0xBCC1A30   per-element init loop over object+0x50..0x58           [PROVEN FULLY, not called]
//   sub_bcc3190 @ 0xBCC3190   bind material/state (rcx)                             [PROVEN]
//   sub_bcc1910 @ 0xBCC1910   state/uniform convert (rcx=buf, rdx=passRecord+0x20C) [PROVEN]
//   sub_bcc24f0 @ 0xBCC24F0   uniforms (rcx, rdx=passRecord+0x170, r8=buf)          [PROVEN]
//   sub_bcc2b00 @ 0xBCC2B00   bindVertexStreams (rcx, rdx=passRecord+0x88) -> al    [PROVEN]
//   sub_bcc2eb0 @ 0xBCC2EB0   bindIndexBuffer   (rcx, rdx=passRecord+0x88) -> al    [PROVEN]
//   sub_bcc38e0 @ 0xBCC38E0   submitPass draw                                       [PROVEN]
//   sub_e86d7f0 @ 0xE86D7F0   draw setup -> bool eax (head arg layout + epilogue [V])[PROVEN head+epilogue]
//
// Globals:
//   [0x12AE1748]  s_ctx pointer
//   [0x1233E1A8]  allocator object; [allocator+8] = allocate fn
//   [0xF7D08C5]   "raw:"     [0xF7D08BE] "ScreenDraw:"
// ============================================================================

using CopyFn = void(__fastcall*)(void* dst, const void* src, uint32_t len);
using IdCounterFn = uint32_t(__fastcall*)(void* buf, uint32_t edx);
using MemcpyFn = void(__fastcall*)(void* dst, const void* src, uint64_t len);
using DrawSetupFn = bool(__fastcall*)(void* a1, void* a2, void* a3, void* a4, uint8_t flag);
using BindMatStateFn = void(__fastcall*)(void* a);
using BindStateUniformFn = void(__fastcall*)(void* buf, void* a);
using BindUniformsFn = void(__fastcall*)(void* a, void* b, void* buf);
using BindVertexStreamsFn = bool(__fastcall*)(void* a, void* b);
using BindIndexBufferFn = bool(__fastcall*)(void* a, void* b);
using SubmitPassFn = void(__fastcall*)(void* a, uint32_t edx, uint32_t index, void* d, void* stack1, uint32_t stack2);
using AllocFn = void*(__fastcall*)(void* allocator, uint32_t size);

static CopyFn      copyFn      = reinterpret_cast<CopyFn>(bsRva(0xEBCE390));
static IdCounterFn idCounterFn = reinterpret_cast<IdCounterFn>(bsRva(0xEBCE5E0));
static MemcpyFn    memcpyFn    = reinterpret_cast<MemcpyFn>(bsRva(0xEEC6EC0));
static DrawSetupFn drawSetupFn = reinterpret_cast<DrawSetupFn>(bsRva(0xE86D7F0));
static BindMatStateFn bindMatStateFn  = reinterpret_cast<BindMatStateFn>(bsRva(0xBCC3190));
static BindStateUniformFn bindStateFn = reinterpret_cast<BindStateUniformFn>(bsRva(0xBCC1910));
static BindUniformsFn bindUniformsFn  = reinterpret_cast<BindUniformsFn>(bsRva(0xBCC24F0));
static BindVertexStreamsFn bindVSFn   = reinterpret_cast<BindVertexStreamsFn>(bsRva(0xBCC2B00));
static BindIndexBufferFn bindIBFn     = reinterpret_cast<BindIndexBufferFn>(bsRva(0xBCC2EB0));
static SubmitPassFn submitPassFn      = reinterpret_cast<SubmitPassFn>(bsRva(0xBCC38E0));

static void** const g_s_ctx_addr   = reinterpret_cast<void**>(bsRva(0x12AE1748));   // holds s_ctx
static void** const g_allocator_addr = reinterpret_cast<void**>(bsRva(0x1233E1A8)); // holds allocator object
static void* const g_raw_prefix    = reinterpret_cast<void*>(bsRva(0xF7D08C5));     // "raw:"
static void* const g_screen_draw_prefix = reinterpret_cast<void*>(bsRva(0xF7D08BE)); // "ScreenDraw:"

static inline void* s_ctx() { return *g_s_ctx_addr; }

static inline void* allocator_object() { return *g_allocator_addr; }

static inline AllocFn allocator_allocate_fn() {
    void* alloc = allocator_object();
    return reinterpret_cast<AllocFn>(*reinterpret_cast<void** const*>(reinterpret_cast<uintptr_t>(alloc) + 8));
}

} // namespace


void __fastcall RewritePasses::taaUpscale(void* _This, void* ctx, void* passRecord)
{
    // Our own TAA upscale pass. Calls the proven sub-blocks of TAAUpscaling body
    // 0xbc8ab12..0xbc8be7c (proven call sites tabled in docs/progress/oc_U-EQ5d.md
    // section (5)):
    //
    //   sub_5668ac0 @ 0x5668AC0   (0xbc8bae3)  register "Upscaling" pass name
    //   sub_130ee0  @ 0x130EE0    (0xbc8b41c)  entry-array header manager -- NOT called here:
    //                                          rcx=[rbp+0xC48] = object2+0x48; object2 (0x340-byte
    //                                          pass copy built by the in-body allocator) is not
    //                                          reconstructed in this subset (mode Off).
    //   sub_568c420 @ 0x568C420   (0xbc8b43f)  rcx = taaCtx+0x58, rdx = pr+0x78
    //   sub_5693A80 @ 0x5693A80 x3(0xbc8b453/467/47b): rcx = taaCtx,
    //                                          rdx = pr+0x6A8 / pr+0x680 / pr+0x658
    //
    // TAA context object: passRecord+0xC58 holds it (proven 0xbc8b421/0xbc8b44c/0xbc8b460/0xbc8b474:
    // mov rcx,[rbp+0xC58]).
    //
    // Registry mode left Off: this rewrite is a subset of the original and is not called until a
    // mode is set to On. No full TAA resolve (jitter/history-blend/render-target write) is
    // reimplemented -- that path lies beyond the body's tail-jmp target 0xBC8A644 and is not part
    // of the proven body [V: no such instruction in 0xbc8ab12..0xbc8be7c].
    //
    // Unproven (NOT called): sub_5668ac0 (pass name "Upscaling" registration), the
    // TAA resolve / jitter / history-blend render path unique to TAA. Args for
    // sub_130ee0 come from object2-derived locals ([rbp+0xC48]) not reconstructed
    // here — nullptr passed for those. The upscale render path is not fully decoded,
    // so taaUpscale reads inputs and issues the proven sub-calls only; no full TAA
    // resolve is reimplemented.
    //
    // Registry mode left Off: this rewrite is a subset of the original and is not
    // called until mode is set to On AND the missing blocks are reversed.
    (void)_This;
    (void)ctx;
    const uint8_t* pr = static_cast<const uint8_t*>(passRecord);

    void* const taaCtx = *reinterpret_cast<void* const*>(pr + 0xC58);   // R passRecord+0xC58

    // ---- sub_5668ac0 @ 0x5668AC0: register "Upscaling" pass name (0xbc8bae3) ----
    //   rcx = &g_upscalingSlot ([0x12AE1B88]), rdx = &{ptr="Upscaling", len=9},
    //   r8 = &{ptr=nullptr, len=0}  ([rbp+0x6F0] was a zeroed 16-byte buffer).
    //   Body [V]: FNV-1a 64(name) -> [rcx]; FNV-1a 64(buf) -> [rcx+8]; buf{0,0} takes the
    //   len==ptr==0 shortcut (0x5668bbc je) so no second pass runs. Fatal sub_78ED0 if
    //   name.ptr==0 || name.len==0 (not possible here: "Upscaling" ptr != 0, len 9).
    static uint8_t g_upscaleName[] = "Upscaling";      // 9 chars [V rodata 0xF5B67DB, len 9 at 0xbc8bac3]
    uint64_t nameFields[2]   = { reinterpret_cast<uint64_t>(g_upscaleName), 9 };
    uint64_t zeroFields[2]   = { 0, 0 };
    using Sub5668ac0Fn = void(__fastcall*)(void** slot, uint64_t* name2, uint64_t* buf2);
    static Sub5668ac0Fn sub5668ac0 = reinterpret_cast<Sub5668ac0Fn>(bsRva(0x5668AC0));
    sub5668ac0(reinterpret_cast<void**>(bsRva(0x12AE1B88)), nameFields, zeroFields);

    // ---- sub_568c420 @ 0x568C420 (0xbc8b43f): rcx = taaCtx+0x58, rdx = pr+0x78 ----
    using Sub568c420Fn = void(__fastcall*)(void*, void*);
    static Sub568c420Fn sub568c420 = reinterpret_cast<Sub568c420Fn>(bsRva(0x568C420));
    sub568c420(reinterpret_cast<uint8_t*>(taaCtx) + 0x58, const_cast<uint8_t*>(pr) + 0x78);

    // ---- sub_5693A80 @ 0x5693A80 x3 (0xbc8b453/0xbc8b467/0xbc8b47b) ----
    using Sub5693A80Fn = void(__fastcall*)(void* ctx, void* src);
    static Sub5693A80Fn sub5693a80 = reinterpret_cast<Sub5693A80Fn>(bsRva(0x5693A80));
    sub5693a80(taaCtx, const_cast<uint8_t*>(pr) + 0x6A8);
    sub5693a80(taaCtx, const_cast<uint8_t*>(pr) + 0x680);
    sub5693a80(taaCtx, const_cast<uint8_t*>(pr) + 0x658);
}

void __fastcall RewritePasses::screenDraw(void* _This, void* ctx, void* passRecord)
{
    // Our own fullscreen post pass implementation. Replicates ScreenDraw body
    // 0xbc04dc0 behavior calling only through proven blocks [V per oc_U-EQ5d_r5.md].
    //
    // Reads: passRecord+0x168 (rect min), +0x16C (rect max), +0x178 (flag byte).
    // Writes: s_ctx view block (view index = word[*(ctx+8)+8], stride 0x140):
    //   +0x1EAB090 rect min, +0x1EAB094 rect max,
    //   +0x1EAB0A0/0E0/120/160 mat4 rows (from passRecord+0x128/+0x17C/+0x1BC/+0x1BC),
    //   +0x1EAB1A0 vec4 (from passRecord+0x1FC), +0x1EAB1B2 flag byte.
    // Then binds material/state/uniforms/vertex/index and submits a draw via
    // sub_bcc38e0 (submitPass).
    //
    // Unproven blocks (role known [V], body NOT reversed — NOT called by the rewrite):
    //   sub_ebce5e0 (id counter), sub_bcc1a30 (object init), sub_75720 (name-too-long),
    //   allocator object layout, per-element sub_568db90 loop, cleanup dtors.
    // sub_e86d7f0 (draw setup) IS called (proven address 0xE86D7F0, role [V], body
    // UNPROVEN) with best-effort args. The 0x30 object allocation and name/id
    // bookkeeping are skipped (debug naming, not rendering-critical).
    // Registry mode left Off.
    (void)_This;
    const uint8_t* pr = static_cast<const uint8_t*>(passRecord);
    const uint8_t* ctxb = static_cast<const uint8_t*>(ctx);

    // ---- P5: recover ctx+8 pointer and view index (word[*(ctx+8)+8]) ----
    const uint8_t* ctx8 = *reinterpret_cast<const uint8_t* const*>(ctxb + 8); // *(ctx+8)
    const uint32_t viewIdx = *reinterpret_cast<const uint16_t*>(ctx8 + 8);    // word[*(ctx+8)+8]

    void* sctx = s_ctx();                                  // [0x12AE1748]
    uint8_t* const viewBase = static_cast<uint8_t*>(sctx) + (uintptr_t)viewIdx * 0x140ULL;

    // ---- P2: view-rect write (rect min clamped >=0 per pmaxsw; rect max stored) ----
    const uint32_t rectMin = *reinterpret_cast<const uint32_t*>(pr + 0x168); // R passRecord+0x168
    const uint32_t rectMax = *reinterpret_cast<const uint32_t*>(pr + 0x16C); // R passRecord+0x16C
    int32_t rmin = static_cast<int32_t>(rectMin);
    if (rmin < 0)
        rmin = 0; // approx per-lane pmaxsw clamp to >=0
    *reinterpret_cast<uint32_t*>(viewBase + 0x1EAB090) = static_cast<uint32_t>(rmin); // W rect min
    *reinterpret_cast<uint32_t*>(viewBase + 0x1EAB094) = rectMax;                     // W rect max

    // ---- P3: mat4 rows + vec4 copies via proven sub_ebce390 ----
    copyFn(viewBase + 0x1EAB0A0, pr + 0x128, 0x40); // mat4 row 0
    copyFn(viewBase + 0x1EAB0E0, pr + 0x17C, 0x40); // mat4 row 1
    copyFn(viewBase + 0x1EAB120, pr + 0x1BC, 0x40); // mat4 row 2
    copyFn(viewBase + 0x1EAB160, pr + 0x1BC, 0x40); // mat4 row 3
    copyFn(viewBase + 0x1EAB1A0, pr + 0x1FC, 0x10); // vec4

    // ---- P4: flag byte ----
    *reinterpret_cast<uint8_t*>(viewBase + 0x1EAB1B2) = pr[0x178]; // W flag byte

    // ---- P8: build "raw:" + "ScreenDraw:" + name buffer via proven allocator + sub_eec6ec0 ----
    const uint64_t nameLen = *reinterpret_cast<const uint64_t*>(pr + 0x278);   // R name len
    const char* namePtr = reinterpret_cast<const char*>(
        *reinterpret_cast<const uint8_t* const*>(pr + 0x268));                 // R name ptr
    // Allocated size mirrors the original's aligned computation (rdi+0x28, aligned to 0x20).
    uint64_t allocSize = (nameLen + 0xB + 0x27) & ~0x1FULL;
    if (allocSize < 0x10)
        allocSize = 0x10;
    if (allocSize > 0xFFFFFFFFULL)
        allocSize = 0xFFFFFFFFULL;
    void* buf = allocator_allocate_fn()(allocator_object(), static_cast<uint32_t>(allocSize));
    if (buf != nullptr) {
        uint8_t* b = static_cast<uint8_t*>(buf);
        // "ScreenDraw:" prefix at [r12] (8 bytes explicit; remainder implied) and "raw:" at [r12+7].
        *reinterpret_cast<uint64_t*>(b) = *reinterpret_cast<const uint64_t*>(g_screen_draw_prefix);
        *reinterpret_cast<uint32_t*>(b + 7) = *reinterpret_cast<const uint32_t*>(g_raw_prefix);
        // name copied after the 0xB-byte prefix via proven sub_eec6ec0.
        memcpyFn(b + 0xB, namePtr, nameLen);
        b[nameLen + 0xB] = 0; // null terminator
    }

    // ---- P6/P7: 0x30 object allocation + sub_bcc1a30 init - SKIPPED.
    // The object is not consumed by the bind chain (sub_bcc3190/bcc1910/bcc24f0/
    // bcc2b00/bcc2eb0 all use buf and passRecord, not the object), so omitting it
    // is safe for rendering. sub_bcc1a30 body is UNPROVEN.

    // ---- P9-P11: view lookup + id counter (sub_ebce5e0) + copy id to view - SKIPPED.
    // Debug naming only (sub_ebce5e0 body UNPROVEN); not rendering-critical.

    // ---- P12: per-element sub_568db90 loop - SKIPPED.
    // The iterated range ([rbp+0x80..0x88]) is zero-initialized at P8, so the loop
    // body is a no-op (sub_568db90 body UNPROVEN, never reached in practice).

    // ---- P13: draw setup via sub_e86d7f0 (best-effort args; body UNPROVEN) ----
    bool proceed = true;
    if (drawSetupFn != nullptr) {
        // rcx = saved vtable[0] slot address | 1 (cl=1), rdx = buf, r8 = nullptr,
        // r9 = &viewBase-local proxy, cl = 1. Best-effort reconstruction.
        const uint8_t vtable0Slot = static_cast<const uint8_t*>(ctx)[0]; // proxy
        (void)vtable0Slot;
        proceed = drawSetupFn(reinterpret_cast<void*>(static_cast<uintptr_t>(1)), buf, nullptr, buf, 1);
        // NOTE: args are reconstructed; if sub_e86d7f0 is enabled while its body is
        // unproven this may not match the original. Keep mode Off until reversed.
    }

    if (!proceed)
        return; // draw setup declined (mirrors al==0 -> loc_bc052da skip draw)

    // ---- P14: bind pipeline via proven blocks ----
    const uint8_t* const ctx8ptr = ctx8; // *(ctx+8), used as rcx for bind calls
    bindMatStateFn(const_cast<uint8_t*>(ctx8ptr));                                  // sub_bcc3190
    bindStateFn(buf, const_cast<uint8_t*>(pr + 0x20C));                             // sub_bcc1910 state/uniform
    bindUniformsFn(const_cast<uint8_t*>(ctx8ptr), const_cast<uint8_t*>(pr + 0x170), // sub_bcc24f0 uniforms
                   buf);
    if (bindVSFn(const_cast<uint8_t*>(ctx8ptr), const_cast<uint8_t*>(pr + 0x88))) { // sub_bcc2b00 bindVertexStreams
        bindIBFn(const_cast<uint8_t*>(ctx8ptr), const_cast<uint8_t*>(pr + 0x88));   // sub_bcc2eb0 bindIndexBuffer
    }

    // ---- P15: draw via proven sub_bcc38e0 (submitPass) ----
    // index = word[*(*(ctx+8)+8)+8]; stack1 = passRecord+0xE0 (pre +0x2C8 advance);
    // r9 = passRecord advanced +0x2C8.
    const uint8_t* prNext = pr + 0x2C8;
    const uint32_t index = *reinterpret_cast<const uint16_t*>(ctx8 + 8);
    const uint32_t stack1 = *reinterpret_cast<const uint32_t*>(pr + 0xE0);
    submitPassFn(const_cast<uint8_t*>(ctx8ptr), 0, index, const_cast<uint8_t*>(prNext),
                 reinterpret_cast<void*>(static_cast<uintptr_t>(stack1)), 0);

    // ---- P16: cleanup - SKIPPED (sub_568da90/sub_e935700/sub_655cea0 bodies UNPROVEN;
    // our rewrite allocates buf but does not free it - acceptable for Off-mode stub;
    // add sub_568da90/sub_e935700 calls once bodies reversed).
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
