#pragma once

// Render-thread contract for the replacement submit (checklist N3a; docs/BGFX_MAP.md 11d;
// 6as/6ac; L17e done). Every RVA below is verified by disassembly and quoted verbatim in
// docs/progress/oc_U-EN3a.md with a [V] tag unless marked [I].
//
// Thread model on 1.26.62.01:
//   game thread:     FrameBuilder inserts per-frame descriptions; BgfxFrameBuilder::endFrame
//                    0x66232b0 encodes the frame graph and reaches Wait-for-previous-frame
//                    0xc25f960 -> GraphicsTasks::Execute 0xc25fc50 -> bgfx frame()/handoff
//                    0xbc65800, which posts semaphore ctx+0x80 (thread-role "game thread"
//                    is structural [I]: no direct xref to 0x66232b0).
//   dragon task threads: GraphicsTasks scheduler 0xc25b1a0 dispatches tasks; Execute
//                    0xc25fc50 drains the queue (0xc25fe20 x2) and calls frame()/handoff
//                    0xbc65800 exactly once per frame with rcx = s_ctx 0x12AE1748 [V at
//                    0xc25fcd0-0xc25fcd7] (worker-thread identity [I]).
//   bgfx render thread: Context init 0xbc63690 creates the thread "bgfx - renderer backend
//                    thread" (string 0xf602711) via CreateThread 0xebdb9b0 with proc
//                    0xbc65720 [V]; the proc loops `while (renderFrame(5000) != 3)` [V].
//
// renderFrame 0xbc63150 (render thread): waits semaphore ctx+0x80 [V], runs the command
// interpreters (cmdPre Frame+0xDC5818, cmdPost Frame+0xE05820), then dispatches renderer
// vtable slot 50 (+0x190) = submit with Frame ctx+0x1CFD0C0 [V at 0xbc633a5-0xbc633af]
// and posts semaphore ctx+0x100 [V]. Slot 50 = submit 0xe82e230 (single caller 0xe83d440
// [V xref]); RTX override 0xe83d440 -> base [I per 6al]. A replacement submit hooked at
// slot 50 therefore runs on the render thread.
//
// Semaphore order (must be preserved by any replacement submit):
//   render thread: wait ctx+0x80 -> submit -> post ctx+0x100 [V]
//   frame() (API side): post ctx+0x80 -> ... render thread submits ... -> wait ctx+0x100
//     per active surface [V]
//
// Double buffer: ctx+0x1CFD0C0 = consume/submit Frame (renderThread), ctx+0x1CFD0C8 =
// fill/API Frame (frame()); two Frames 0xE749C0 apart [V live, BGFX_MAP 1173].
//
// Exceptional path (not the shipping threaded model, noted so the replacement does not
// assume submit is only reachable from 0xbc65720): task 0xc262000 calls synchronous render
// entry 0xbc63060 (timeout 5000) -> renderFrame -> submit [V]; 0xc262000 has no direct
// xrefs (indirect via the task queue), role/thread [I].


namespace RenderThread {

// bgfx::Context global (s_ctx), data RVA.
inline constexpr uintptr_t kCtxGlobalRva = 0x12AE1748;

// Render thread (created by Context init 0xbc63690).
inline constexpr uintptr_t kRenderThreadProcRva = 0xbc65720;
inline constexpr const char* kRenderThreadName = "bgfx - renderer backend thread"; // string 0xf602711

// bgfx::Context::renderFrame(int32_t msecs): waits ctx+0x80, dispatches submit,
// posts ctx+0x100; returns 1 Render / 2 Timeout / 3 Exiting.
inline constexpr uintptr_t kRenderFrameRva = 0xbc63150;

// Semaphore offsets within bgfx::Context.
inline constexpr std::size_t kSemFrameReady = 0x80;       // waited by render thread, posted by frame()
inline constexpr std::size_t kSemFrameConsumed = 0x100;   // posted by render thread, waited by frame()

// Double-buffered Frame slots within bgfx::Context.
inline constexpr std::size_t kFrameConsume = 0x1CFD0C0; // render thread submits this one
inline constexpr std::size_t kFrameFill = 0x1CFD0C8;    // game/API thread fills this one
inline constexpr std::size_t kFrameDelta = 0xE749C0;    // live-verified spacing (BGFX_MAP 1173)

// submit = RendererContextD3D12 vtable slot 50 (+0x190): base 0xe82e230, RTX override
// 0xe83d440 -> base (a detour at 0xe82e230 covers both; see RewriteSubmit.h, checklist N1a).
inline constexpr uintptr_t kSubmitRva = 0xe82e230;
inline constexpr uintptr_t kSubmitRtxOverrideRva = 0xe83d440;
inline constexpr uintptr_t kRendererVtableBase = 0xF4ED2D0;
inline constexpr uintptr_t kRendererVtableRtx = 0xF4EEE80;
inline constexpr std::size_t kSubmitSlot = 50;
static_assert(kSubmitSlot * 8 == 0x190, "slot 50 must be at vtable offset +0x190");

// Synchronous (single-threaded) entry: task 0xc262000 -> 0xbc63060 -> renderFrame.
// Role/thread of 0xc262000 unpinned [I].
inline constexpr uintptr_t kSyncRenderEntryRva = 0xbc63060;

} // namespace RenderThread
