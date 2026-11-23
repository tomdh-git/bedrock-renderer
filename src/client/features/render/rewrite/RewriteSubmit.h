#pragma once

// RendererContextD3D12::submit takeover seam (checklist N1a; docs/BGFX_MAP.md 8a, 10).
//
// submit is vtable slot 50 of RendererContextI:
//   base D3D12 vtable 0xF4ED2D0 at +0x190 -> 0xe82e230, size 0x4d91  [V: vt dump + rdis]
//   RTX subclass vtable 0xF4EEE80 overrides slot 50 with 0xe83d440, which pre-does TLAS/BLAS
//   and then calls base 0xe82e230, so detouring 0xe82e230 covers every submit entry path.  [I: 6al]
// Signature: (rcx = RendererContext*, rdx = Frame*, r8/r9 = two small helper objects, untyped here).
//
// Frame contract for the walk (all [V] in submit's own body on 1.26.62.01, quoted in
// docs/progress/oc_U-EN1a.md):
//   Frame+0xDC57E8 u32 item/draw count, CAS-allocated, cap 0xFFFE
//   Frame+0x14700  u64 sort keys (viewId = key >> 54)
//   Frame+0x94700  u16 sorted item index list
//   Frame+0xB4700  RenderDrawHeader[], stride 0x80, header = base + (index << 7)
//   RenderDraw state word u64 at header+0x20 (executor tests byte header+0x23)
// All pinned by static_asserts in src/sdk/mc/deps/bgfx/Frame.h (FrameOffsets + RenderDraw).
//
// This file only declares the seam; the detour lives in RewriteSubmit.cpp. Nothing is
// enabled by default: RewriteRegistry installs the detour only when a mode != Off is set
// (BS_REWRITE or setMode), and the client must be rebuilt first - see the CLOSES? line in
// docs/progress/oc_U-EN1a.md.



#include "client/features/hooks/Detour.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "sdk/mc/deps/bgfx/Frame.h"

namespace bgfx {
struct Frame;
struct RendererContext;
} // namespace bgfx

namespace RenderSubmit {

// vtable 0xF4ED2D0 slot 50 (+0x190) on 1.26.62.01
constexpr uintptr_t kSubmitRva = 0xe82e230;
constexpr uintptr_t kBaseVtable = 0xF4ED2D0; // RendererContextI base (RTX: 0xF4EEE80 overrides slot 50)
constexpr size_t kSlot = 50;
constexpr size_t kSize = 0x4d91; // rdis vt size

using Fn = void(__fastcall*)(bgfx::RendererContext* ctx, bgfx::Frame* frame, uintptr_t a3, uintptr_t a4);

// Per-draw verdict produced by the veto/rewrite policy. The detour never modifies game
// memory except the draw header it is allowed to touch (header+0x63 streamMask); every
// other decision is read-only observation.
enum class DrawVerdict : uint8_t { Allow = 0, Veto, Rewrite };

// Q4d: per-draw veto/rewrite over the Frame draw-header walk. The executor skips any draw
// whose header+0x63 streamMask == 0 (0xe822b92 movzx/e822b98 test/e822b9b je -> skip path),
// so veto = zero streamMask before forwarding to the original submit. Rewrite touches the
// same header fields the executor consumes (stateFlags +0x20, submitFlags +0x62,
// occlusionQuery +0x7A, streamMask +0x63); no other game memory is written.
// Fail fast: no null guards, no SEH.
struct DrawVetoPolicy {
    // Called once per draw header, inside the detour, before forwarding to the original.
    // `frame` is the submit Frame*; `header` points at the current 0x80-byte header
    // (Frame+0xB4700 + idx*0x80, idx from Frame+0x94700). Returns Allow / Veto / Rewrite.
    static DrawVerdict verdict(const bgfx::Frame* frame, const uint8_t* header);
};

// Per-draw veto/rewrite stats live in RewriteSubmit.cpp (relaxed atomics, statistics only).

// The detour: walks Frame+0xB4700 headers stride 0x80, collects per-draw stats + QPC timers,
// applies DrawVetoPolicy::verdict per draw (veto = zero header+0x63 streamMask so the
// executor skips it; rewrite = record-only by default), then forwards to the original
// through the RewriteRegistry trampoline (mode Shadow/On).
// Fail fast: no null guards, no SEH - a null Frame crashes here exactly as in the original.
void __fastcall takeover(bgfx::RendererContext* ctx, bgfx::Frame* frame, uintptr_t a3, uintptr_t a4);

// Registry entry (defined in RewriteSubmit.cpp); mode Off until explicitly switched.
extern RewriteEntry entry;

} // namespace RenderSubmit
