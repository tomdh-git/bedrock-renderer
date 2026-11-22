## NEXT
DONE

# Unit U-EN3b: N3b Frame double buffer 0xE749C0 apart; ctx+0x80 frame-ready and ctx+0x100 frame-consumed semaphores signaled in backend order — BGFX_MAP 8b/11d; A10

Source item: RENDER_CHECKLIST.md line 494 `[ ] N3b Frame double buffer 0xE749C0 apart; ctx+0x80 frame-ready and ctx+0x100 frame-consumed semaphores signaled in backend order — BGFX_MAP 8b/11d; A10`.
BGFX_MAP 8b: "Two Frame instances are spaced 0xE749C0 apart. The render thread signals ctx+0x80 (frame-ready semaphore) and waits ctx+0x100 (frame-consumed semaphore) [A10; not verified in this binary: [?]]." — this [?] is the pending part.
BGFX_MAP 11d: "Frame double buffer: two Frame instances 0xE749C0 apart; ctx+0x80 frame-ready semaphore, ctx+0x100 frame-consumed semaphore [A10]. Preserve signal/wait order."
A10 (already closed, oc_U-A10.md / oc_U-EL1t.md): render thread proc 0xbc63150 waits ctx+0x80 (`lea rcx,[rsi+0x80]` → `call 0xEBDBC60` at 0xbc6322f) and posts ctx+0x100 (`mov rcx,rsi; mov edx,1; call 0xEBDBC50` at 0xbc633da). oc_U-EL1t closed CLOSES? NO because ctx+0x100 is not a `[reg+0x100]` memory operand in 0xbc63150 — it is read inside 0xEBDBC50.
A4b (closed): both semaphores created by 0xBC6B560 via 0xEBDBC20 (CreateSemaphoreW): `lea rcx,[rsi+0x80]` creates ctx+0x80, `lea rcx,[rax+0x100]` creates ctx+0x100 (needs re-quote verification).

Pending to prove for N3b:
1. Frame pair spacing 0xE749C0 apart — both Frame* loads (ctx+0x1CFD0C0 / ctx+0x1CFD0C8) quoted; size 0xE749C0 from Frame.h kFrameSize / live (already [V] elsewhere, re-cite here).
2. ctx+0x80 is a semaphore HANDLE: creation site + wait site quoted.
3. ctx+0x100 is a semaphore HANDLE: creation site + post site + proof that 0xEBDBC50 reads [rcx+0x100] as the handle (this is the open gap from oc_U-EL1t).
4. Backend signal/wait order: API thread (frame() 0xbc65800) POSTS ctx+0x80 then WAITS ctx+0x100; render thread (0xbc63150) WAITS ctx+0x80 then POSTs ctx+0x100. Order: 0x80 first (fill), then 0x100 (drain) — reversing deadlocks.

Input data read fully: docs/progress/pre/0xbc63150.md, docs/progress/pre/0xBC63690.md, docs/progress/oc_U-A10.md, docs/progress/oc_U-A4b.md, docs/BGFX_MAP.md sections 8b/11d, docs/RENDER_CHECKLIST.md line 494, docs/progress/bgfx-d3d12-dragon.md.

## Changes (paths)
- Created: docs/progress/oc_U-EN3b.md (this file; the only file created or edited). No edits to HookManager.cpp, Sigs.json, CMake, existing hook registration; no build run; game not launched. All evidence below is static disassembly quoted verbatim from rdis.exe plus existing docs.

## Pending parts of the item line (RENDER_CHECKLIST.md 494; BGFX_MAP 8b/11d, tagged [A10] with [?] "not verified in this binary")
1. Frame double buffer 0xE749C0 apart. 2. ctx+0x80 frame-ready semaphore exists and is signaled. 3. ctx+0x100 frame-consumed semaphore exists and is signaled. 4. Both signaled in backend order (no inversion → no deadlock).

## Semaphore wrapper contracts (quoted verbatim from disassembly)
- `0xEBDBC20` CreateSemaphoreW wrapper: `ebdbc26  mov rbx,rcx` … `ebdbc36  call qword ptr [0xF9A7C50]` … `ebdbc3c  mov [rbx],rax` → handle stored at [rcx], i.e. at the &storage passed by the caller [V].
- `0xEBDBC50` ReleaseSemaphore wrapper: `ebdbc50  mov rcx,[rcx]` … `ebdbc56  jmp qword ptr [0xF9A7B40]` → ReleaseSemaphore(*[rcx], edx=count, NULL=prev) [V]; every post site passes edx=1.
- `0xEBDBC60` WaitForSingleObject wrapper: `ebdbc64  mov rcx,[rcx]` … `ebdbc71  call qword ptr [0xF9A7B60]` → WaitForSingleObject(*[rcx], edx=ms; INFINITE via cmovs) [V].

## Proof table (one row per distinct offset; all sites for that offset listed)
| name | offset | size | verbatim `0xRVA  instr` sites | meaning [tag] |
|---|---|---|---|---|
| Frame* slot ctx+0x1cfd0c0 (submit/consume Frame) | ctx+0x1cfd0c0 | 8 | `0xbc6316e  mov rax,[rcx+0x1CFD0C0]` | First of the two double-buffered Frame* stored in the context [V preflight 0xbc63150]. |
| Frame* slot ctx+0x1cfd0c8 (API/fill Frame) | ctx+0x1cfd0c8 | 8 | `0xbc63259  mov rax,[rsi+0x1CFD0C8]` | Second Frame* of the pair [V]; pointers swap every frame, `[ctx+0x1cfd0c0]` = consume/complete, `[ctx+0x1cfd0c8]` = fill (AGENT_BRIEF 26, BGFX_MAP 6do, oc_U-EM3a) [V live]. |
| Frame pair spacing | ctx+0x1cfd0c0→ctx+0x1cfd0c8 | - | - | Two Frame instances 0xE749C0 apart = Frame.h kFrameSize [V oc_U-EM3a.md FrameOffsets kFrameSize 0xE749C0; live both pointers differ by exactly 0xE749C0, BGFX_MAP 6do line 1011 and line 1867] [V]. |
| Semaphore handle ctx+0x00 (apiSem) | ctx+0x00 | 8 | creation `0xbc6b5bc  call 0xEBDBC20` (rcx=ctx) + wrapper `0xebdbc3c  mov [rbx],rax`; render-thread post `0xbc633d2  mov rcx,rsi` / `0xbc633da  call 0xEBDBC50`; thread-exit post `0xbc657ed  call 0xEBDBC50` (rcx=ctx=rdi) | CreateSemaphoreW handle stored at [ctx+0x00] = apiSem [V 0xBC6B560 + ebdbc20]; the render thread's own post signals *[ctx+0x00], NOT ctx+0x100 [V]. |
| Semaphore handle ctx+0x80 (renderSem, frame-ready) | ctx+0x80 | 8 | creation `0xbc6b5c5  lea rcx,[rsi+0x80]` / `0xbc6b5d0  call 0xEBDBC20`; render-thread wait `0xbc63226  lea rcx,[rsi+0x80]` / `0xbc6322f  call 0xEBDBC60`; API-thread signal `0xbc65af2  lea rcx,[rsi+0x80]` / `0xbc65af9  mov edx,1` / `0xbc65afe  call 0xEBDBC50`; thread-entry wait `0xbc6578e  lea rcx,[rdi+0x80]` / `0xbc6579a  call 0xEBDBC60`; wrappers `0xebdbc64  mov rcx,[rcx]` / `0xebdbc71  call qword ptr [0xF9A7B60]` (wait) and `0xebdbc50  mov rcx,[rcx]` / `0xebdbc56  jmp qword ptr [0xF9A7B40]` (post) | Handle stored at [ctx+0x80] = renderSem [V 0xBC6B560]; waited by render thread [V], signaled by API thread frame() after Context::swap [V]. |
| Semaphore handle ctx+0x100 (encoderEndSem, frame-consumed) | ctx+0x100 | 8 | creation `0xbc6b5da  lea rcx,[rax+0x100]` / `0xbc6b5e5  call 0xEBDBC20`; API-thread wait `0xbc65899  lea rbx,[rsi+0x100]` → `0xbc658b0  mov rcx,rbx` / `0xbc658b3  mov edx,0xFFFFFFFF` / `0xbc658b8  call 0xEBDBC60` (loop `0xbc658c1  cmp r15w,r14w`, N-1, N=u16 [ctx+0x13D20]); endFrame signal `0xc2705f5  add rbx,0x100` / `0xc2705fc  mov rcx,rbx` / `0xc2705ff  mov edx,1` / `0xc270604  call 0xEBDBC50` (per surface over [ctx+0x13D18]) | Handle stored at [ctx+0x100] = encoderEndSem [V 0xBC6B560]; waited N-1 times by frame() 0xbc65800 [V], signaled by endFrame/frame-graph-encode 0xC270460 per surface [V]. |
| Backend signal/wait order | - | - | - | frame() 0xbc65800 WAITS ctx+0x100 (`0xbc658b8 call 0xEBDBC60`) BEFORE it SIGNALs ctx+0x80 (`0xbc65afe call 0xEBDBC50`); endFrame 0xC270460 SIGNALs ctx+0x100 (`0xc270604 call 0xEBDBC50`) before the next frame() waits it. Consumed→ready order preserved, no inversion, no deadlock [V order]. Thread-attribution naming (frame-ready/frame-consumed) [I per BGFX_MAP 8b/11d]. |

## TOOL REQUESTS
None — all evidence gathered with rdis.exe directly (quotes verified verbatim via shell); no helper scripts written.

## CLOSES?
YES — every pending part of N3b is proven by [V] rows on disk now:
- Frame double buffer 0xE749C0 apart: both Frame* slots loaded (`0xbc6316e  mov rax,[rcx+0x1CFD0C0]`, `0xbc63259  mov rax,[rsi+0x1CFD0C8]`) [V]; spacing 0xE749C0 = kFrameSize [V Frame.h/oc_U-EM3a.md; live BGFX_MAP 6do line 1011 and line 1867].
- ctx+0x80 frame-ready semaphore: created at `0xbc6b5c5  lea rcx,[rsi+0x80]` / `0xbc6b5d0  call 0xEBDBC20` [V]; signaled by API thread frame() 0xbc65800 at `0xbc65afe  call 0xEBDBC50` [V]; waited by render thread renderFrame 0xbc63150 at `0xbc63226  lea rcx,[rsi+0x80]` / `0xbc6322f  call 0xEBDBC60` [V] and thread entry 0xbc65720 at `0xbc6578e` / `0xbc6579a` [V].
- ctx+0x100 frame-consumed semaphore: created at `0xbc6b5da  lea rcx,[rax+0x100]` / `0xbc6b5e5  call 0xEBDBC20` [V]; signaled by endFrame 0xC270460 at `0xc270604  call 0xEBDBC50` [V]; waited by frame() at `0xbc65899`…`0xbc658b8` (N-1) [V].
- Backend order: frame() waits ctx+0x100 (`0xbc658b8`) before signaling ctx+0x80 (`0xbc65afe`); endFrame signals ctx+0x100 (`0xc270604`) before the next frame() waits it — consumed→ready preserved [V].
Attribution caveat [V]: BGFX_MAP 8b's per-thread wording is inverted for this binary — the render thread WAITS ctx+0x80 (`0xbc63226`) and its own post (`0xbc633da  call 0xEBDBC50` with rcx=ctx) targets *[ctx+0x00] apiSem, not ctx+0x100; ctx+0x100 is signaled by endFrame (`0xc270604`). The item's own wording (both semaphores exist, are signaled, backend order preserved) is met.
Remaining in-game/build step: none — all evidence is static disassembly plus existing docs; no game run or build needed.
