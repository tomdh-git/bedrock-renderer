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

// The detour: walks Frame+0xB4700 headers stride 0x80, collects per-draw stats + QPC timers,
// then forwards to the original through the RewriteRegistry trampoline (mode Shadow/On).
// Fail fast: no null guards, no SEH - a null Frame crashes here exactly as in the original.
void __fastcall takeover(bgfx::RendererContext* ctx, bgfx::Frame* frame, uintptr_t a3, uintptr_t a4);

// Registry entry (defined in RewriteSubmit.cpp); mode Off until explicitly switched.
extern RewriteEntry entry;

} // namespace RenderSubmit
