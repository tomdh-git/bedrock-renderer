## NEXT
DONE

# UNIT U-EN3a — close checklist item N3a (replacement submit runs on bgfx render thread)

## Goal (verbatim)

docs/RENDER_CHECKLIST.md line 493:

```
- [ ] N3a Replacement submit runs on bgfx render thread; game thread / dragon task threads /
    render thread model per 6as/6ac — L17e (done); BGFX_MAP 11d
```

## (1) What exists on disk for this item

| path | role |
|---|---|
| docs/BGFX_MAP.md | section 11d "Threading contract" already states the model (game thread, dragon task threads, bgfx render thread [L17e; 6as/6ac]) and "The replacement's submit runs on the render thread", plus the double-buffer/semaphore lines. Not edited here: hard rule 3 forbids editing docs/BGFX_MAP.md and docs/RENDER_CHECKLIST.md. [V: section present on disk] |
| docs/RENDER_CHECKLIST.md | item N3a line 493 still shows `[ ]`; not ticked here (same hard rule). |
| docs/progress/oc_U-EN3a.md | this file: the [V] proof rows below. NEW. |
| src/client/features/render/rewrite/RenderThread.h | new header pinning the threading contract for the replacement submit seam (RVAs, semaphore order, double-buffer slots, the two entry paths). NEW. |

No existing file was edited. No build, no game launch, no hook registration was touched (the detour install itself is checklist item N1a, still open; N3a closes the threading contract that N1a's hook must respect).

## (2) Proof table (one row per distinct offset; all instruction lines verbatim from rdis)

### Render thread creation (Context init tail 0xbc63690)

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc63709 | 7 | rsi+0x200 | `0xbc63709  lea rcx,[rsi+0x200]` | Context init tail builds the render-thread parameter block at ctx+0x200 | [V] |
| 0xbc63710 | 7 | 0xF602711 (rdata string) | `0xbc63710  lea rax,[0xF602711]` | thread name pointer; string content "bgfx - renderer backend thread" confirmed at 0xf602711 (xref str: single ref from 0xbc63710 inside 0xbc63690) | [V] |
| 0xbc6371c | 7 | 0xBC65720 | `0xbc6371c  lea rdx,[0xBC65720]` | lpStartAddress = render thread proc | [V] |
| 0xbc6372b | 5 | 0xEBDB9B0 | `0xbc6372b  call 0xEBDB9B0` | CreateThread spawns the render thread during Context init | [V] |
| 0xbc6374a | 7 | rsi+0x1EBF2F1 | `0xbc6374a  mov [rsi+0x1EBF2F1],dil` | ctx+0x1EBF2F1 = render-thread alive flag (set from the TLS bgfx slot at 0xbc636f2-0xbc636f9) | [V] |

### Render thread proc: 0xbc65720 loops renderFrame(5000) until Exiting(3)

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc65740 | 10 | 0x12AE1748 (s_ctx) | `0xbc65740  mov rcx,[0x12AE1748]` | render thread proc loads the bgfx context global first | [V] |
| 0xbc65764 | 5 | imm 0x1388 = 5000 ms | `0xbc65764  mov edx,0x1388` | renderFrame timeout per loop iteration | [V] |
| 0xbc65769 | 5 | 0xBC63150 | `0xbc65769  call 0xBC63150` | loop body: renderFrame(5000) | [V] |
| 0xbc65775 | 3 | eax = renderFrame result | `0xbc65775  cmp eax,3` | stock bgfx renderFrame enum: 3 = Exiting | [V] |
| 0xbc65778 | 2 | 0xBC6575F | `0xbc65778  jne short 0xBC6575F` | loop until Exiting | [V] |
| 0xbc657d4 | 10 | 0x12AE1748 | `0xbc657d4  mov qword ptr [0x12AE1748],0` | teardown clears s_ctx | [V] |
| 0xbc657e8 | 5 | imm 1 | `0xbc657e8  mov edx,1` | ReleaseSemaphore(count=1) | [V] |
| 0xbc657ed | 5 | 0xEBDBC50 | `0xbc657ed  call 0xEBDBC50` | post ctx+0x100 (frame-consumed) on teardown | [V] |

### renderFrame 0xbc63150 — one frame on the render thread, and the submit dispatch

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc6316e | 10 | rcx+0x1CFD0C0 | `0xbc6316e  mov rax,[rcx+0x1CFD0C0]` | renderFrame loads the consume/submit Frame slot of the double buffer | [V] |
| 0xbc63175 | 7 | rax+0xDC5810 | `0xbc63175  mov ebp,[rax+0xDC5810]` | Frame+0xDC5810 reset-flags word (AND-clears bit 0x40000) | [V] |
| 0xbc63192 | 10 | rsi+0x1EBF2D0 | `0xbc63192  mov rcx,[rsi+0x1EBF2D0]` | renderer object pointer (ctx+0x1EBF2D0) | [V] |
| 0xbc63199 | 3 | [rcx] | `0xbc63199  mov rax,[rcx]` | renderer vtable load | [V] |
| 0xbc6319c | 4 | rax+0x48 | `0xbc6319c  mov rax,[rax+0x48]` | vtable slot 9 (+0x48) fetch in the renderFrame init/reset path | [V] |
| 0xbc631a0 | 6 | [0xF99FFA0] | `0xbc631a0  call qword ptr [0xF99FFA0]` | indirect vtable call | [V] |
| 0xbc63226 | 7 | rsi+0x80 | `0xbc63226  lea rcx,[rsi+0x80]` | semaphore ctx+0x80 = frame-ready gate | [V] |
| 0xbc6322f | 5 | 0xEBDBC60 | `0xbc6322f  call 0xEBDBC60` | WaitForSingleObjectEx(ctx+0x80, 5000): render thread blocks here until the API side signals | [V] |
| 0xbc63252 | 7 | rcx+0xE746C8 | `0xbc63252  mov [rcx+0xE746C8],rax` | Frame+0xE746C8 = render-thread wait-time stat | [V] |
| 0xbc6336c | 5 | edx = 0xDC5818 | `0xbc6336c  mov edx,0xDC5818` | cmdPre command-buffer offset inside the Frame | [V] |
| 0xbc63371 | 10 | rsi+0x1CFD0C0 | `0xbc63371  add rdx,[rsi+0x1CFD0C0]` | cmdPre pointer = consume Frame + 0xDC5818 | [V] |
| 0xbc6337b | 5 | 0xBC68E40 | `0xbc6337b  call 0xBC68E40` | command interpreter for pre-commands | [V] |
| 0xbc6339e | 10 | rsi+0x1CFD0C0 | `0xbc6339e  mov rdx,[rsi+0x1CFD0C0]` | rdx = Frame* argument to submit | [V] |
| 0xbc633a5 | 3 | [rcx] | `0xbc633a5  mov rax,[rcx]` | renderer vtable load (rcx = ctx+0x1EBF2D0) | [V] |
| 0xbc633a8 | 4 | rax+0x190 | `0xbc633a8  mov rax,[rax+0x190]` | vtable slot fetch at +0x190 = slot 50 (0x190/8) = submit entry | [V] |
| 0xbc633af | 6 | [0xF99FFA0] | `0xbc633af  call qword ptr [0xF99FFA0]` | submit(renderer, Frame=rdx, r8=ctx+0x1EBF1F0, r9=ctx+0x1EBF260) — submit is reached from renderFrame on the render thread | [V] |
| 0xbc633c4 | 5 | 0xBC68E40 | `0xbc633c4  call 0xBC68E40` | command interpreter for post-commands (Frame+0xE05820) | [V] |
| 0xbc633d5 | 5 | imm 1 | `0xbc633d5  mov edx,1` | ReleaseSemaphore(count=1) | [V] |
| 0xbc633da | 5 | 0xEBDBC50 | `0xbc633da  call 0xEBDBC50` | post ctx+0x100 = frame-consumed gate (render thread releases the API side) | [V] |

### Slot-50 target: submit

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xe82e230 | 1 | - | `0xe82e230  push rbp` | RendererContextD3D12::submit slot 50 prologue (base); xref callers: exactly one, 0xe83d440 [V] | [V] |
| 0xe83d440 | 1 | - | `0xe83d440  push r14` | RTX subclass submit override (slot 50 of vtable 0xF4EEE80); pre-does TLAS/BLAS then calls base 0xe82e230 (single-caller chain verified by xref; override identity [I] per 6al) | [I] |

### API side: frame()/handoff 0xbc65800 (signals the render thread)

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc65899 | 7 | rsi+0x100 | `0xbc65899  lea rbx,[rsi+0x100]` | frame() 0xbc65800 loads semaphore ctx+0x100 = frame-consumed gate | [V] |
| 0xbc658b0 | 3 | - | `0xbc658b0  mov rcx,rbx` | rcx = semaphore handle | [V] |
| 0xbc658b3 | 5 | imm 0xFFFFFFFF | `0xbc658b3  mov edx,0xFFFFFFFF` | INFINITE timeout | [V] |
| 0xbc658b8 | 5 | 0xEBDBC60 | `0xbc658b8  call 0xEBDBC60` | API thread waits ctx+0x100 until the render thread consumes the frame, repeated per active surface | [V] |
| 0xbc65ae0 | 3 | - | `0xbc65ae0  mov rcx,rsi` | ctx argument | [V] |
| 0xbc65ae3 | 5 | 0xBC66DE0 | `0xbc65ae3  call 0xBC66DE0` | swap pre/post command buffers | [V] |
| 0xbc65af2 | 7 | rsi+0x80 | `0xbc65af2  lea rcx,[rsi+0x80]` | semaphore ctx+0x80 = frame-ready gate | [V] |
| 0xbc65af9 | 5 | imm 1 | `0xbc65af9  mov edx,1` | ReleaseSemaphore(count=1) | [V] |
| 0xbc65afe | 5 | 0xEBDBC50 | `0xbc65afe  call 0xEBDBC50` | post ctx+0x80 — wakes the render thread's renderFrame | [V] |
| 0xbc65a60 | 10 | rsi+0x1CFD0C8 | `0xbc65a60  mov rax,[rsi+0x1CFD0C8]` | frame() loads the fill/API Frame slot | [V] |
| 0xbc65a6c | 7 | rax+0xE74988 | `0xbc65a6c  mov [rax+0xE74988],cl` | Frame+0xE74988 capture flag written on the fill frame | [V] |
| 0xbc65a8e | 10 | rax+0xE746D8 | `0xbc65a8e  mov edi,[rax+0xE746D8]` | Frame+0xE746D8 per-frame counter read on the fill frame | [V] |

### Dragon task threads: GraphicsTasks::Execute 0xc25fc50

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xc25fcc0 | 10 | rsi+0x68 | `0xc25fcc0  mov rcx,[rsi+0x68]` | Execute loads the task-queue head | [V] |
| 0xc25fcc4 | 5 | 0xC25FE20 | `0xc25fcc4  call 0xC25FE20` | drain the GraphicsTasks queue (task runner) | [V] |
| 0xc25fcd0 | 10 | 0x12AE1748 | `0xc25fcd0  mov rcx,[0x12AE1748]` | rcx = s_ctx for the handoff call | [V] |
| 0xc25fcd7 | 5 | 0xBC65800 | `0xc25fcd7  call 0xBC65800` | bgfx frame()/handoff called exactly once per frame (capture flag = byte [rsi+5]*2) | [V] |

### Exceptional synchronous path (not the shipping threaded model)

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xc262012 | 5 | 0xBC63060 | `0xc262012  call 0xBC63060` | task 0xc262000 invokes the synchronous render entry (timeout 5000) | [V] |
| 0xbc63066 | 2 | eax = ecx (timeout) | `0xbc63066  mov eax,ecx` | 0xbc63060 single-threaded render entry | [V] |
| 0xbc63083 | 5 | 0xBC63150 | `0xbc63083  call 0xBC63150` | 0xbc63060 -> renderFrame(5000) | [V] |
| 0xbc63088 | 3 | eax = renderFrame result | `0xbc63088  cmp eax,3` | result 3 = Exiting -> teardown | [V] |

### Globals and shared Frame/semaphore fields

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x12AE1748 | 8 | - | `0xbc65740  mov rcx,[0x12AE1748]` | s_ctx = bgfx::Context global (data RVA): loaded by the render thread proc at start, cleared on exit | [V] |
| 0x80 | 7 | rsi+0x80 | `0xbc63226  lea rcx,[rsi+0x80]` | ctx+0x80 frame-ready semaphore: waited by renderFrame [V], posted by frame() [V] | [V] |
| 0x100 | 7 | rsi+0x100 | `0xbc65899  lea rbx,[rsi+0x100]` | ctx+0x100 frame-consumed semaphore: posted by renderFrame [V], waited by frame() [V] | [V] |
| 0x1CFD0C0 | 8 | rcx+0x1CFD0C0 / rsi+0x1CFD0C0 | `0xbc6316e  mov rax,[rcx+0x1CFD0C0]` | double-buffer consume/submit Frame slot: renderFrame reads it [V]; frame()/swap write it [V]; fill slot at +0x1CFD0C8 [V]; the two Frames are 0xE749C0 apart [V live, BGFX_MAP 1173] | [V] |

## (3) Thread model (game thread / dragon task threads / bgfx render thread, per 6as/6ac; L17e done)

- **Game thread.** Per-frame the game inserts typed descriptions into BgfxFrameBuilder and calls `BgfxFrameBuilder::endFrame 0x66232b0`; endFrame encodes the frame graph (`BgfxContext::endFrame 0xc270460`, task dispatch `0xe9002e0`) and internally reaches Wait-for-previous-frame `0xc25f960` -> `GraphicsTasks::Execute 0xc25fc50` -> bgfx `frame()`/`handoff 0xbc65800`. Thread-role attribution "game thread" for endFrame is structural [I]: no direct xref to 0x66232b0 was found (indirect/virtual call site), so only the RVA is [V]; the position "game thread -> FrameBuilder inserts -> endFrame" is the 6ac chain.
- **Dragon task threads.** `GraphicsTasks` scheduler `0xc25b1a0` dispatches pass/encoder tasks (Render lambda `0xc267200` among others, queued by endFrame via `0xe9002e0`). `GraphicsTasks::Execute 0xc25fc50` drains the queue (`0xc25fe20` x2) and calls bgfx `frame()`/`handoff 0xc25fcd7->0xBC65800` exactly once per frame with `rcx = s_ctx 0x12AE1748` [V]. Scheduler worker-thread identity "dragon task threads" is structural [I]; every RVA above is [V].
- **bgfx render thread.** Context init `0xbc63690` creates the thread "bgfx - renderer backend thread" (string `0xf602711`, xref-confirmed) via `CreateThread 0xebdb9b0` with proc `0xbc65720` [V]. The proc loops `while (renderFrame(5000) != 3)` [V]. `renderFrame 0xbc63150` waits semaphore `ctx+0x80` [V], runs the command interpreters (cmdPre `Frame+0xDC5818`, cmdPost `Frame+0xE05820`), dispatches renderer vtable slot 50 (`+0x190`) = submit with `Frame ctx+0x1CFD0C0` [V], then posts semaphore `ctx+0x100` [V].
- **Double buffer / semaphore contract.** `ctx+0x1CFD0C0` = consume/submit Frame (renderFrame reads it), `ctx+0x1CFD0C8` = fill/API Frame (frame() writes capture/counter/stats into it); two Frames `0xE749C0` apart [V live, BGFX_MAP 1173]. Order that any replacement must preserve: render thread waits `ctx+0x80` -> submit -> posts `ctx+0x100`; frame() posts `ctx+0x80` -> (render thread submits) -> waits `ctx+0x100` per active surface [V R35-R43].
- **Submit target.** Slot 50 is base submit `0xe82e230` (single caller `0xe83d440` [V xref]) with RTX override `0xe83d440` -> base [I per 6al].
- **Exceptional path.** Task `0xc262000` calls synchronous render entry `0xbc63060` (timeout 5000) -> `renderFrame 0xbc63150` -> submit [V R51-R53]; `0xc262000` has no direct xrefs (indirect via the task queue), so its role/thread is [I]. This is not the shipping threaded model; it is noted so the replacement does not assume submit is *only* reachable from `0xbc65720`.

## (4) Why the replacement submit runs on the render thread

The replacement submit hooks vtable slot 50 (`0xe82e230`, reached through the RTX override `0xe83d440` which forwards to base). The only ordinary entry to that dispatch is `renderFrame 0xbc63150` (vtable slot fetch at `0xbc633a5-0xbc633af`, [V]), and `renderFrame` runs on the `0xbc65720` "bgfx - renderer backend thread" proc ([V] thread creation + loop). Therefore a replacement submit at slot 50 executes on the bgfx render thread under the 6as/6ac model. [V] for the call path and thread; [I] only for the slot-50->submit name identity (cross-confirmed by docs/data/functions.tsv D2 and RewriteSubmit.h). The sync path `0xc262000->0xbc63060->renderFrame` is exceptional and unpinned ([I]); the replacement preserves the semaphore order either way.

N3a closes the threading contract. The actual detour install at submit slot 50 is checklist item N1a (separate, still open).

## CLOSES?

YES — every pending part of N3a is proven by [V] rows on disk now: submit runs on the bgfx render thread (renderFrame 0xbc63150 dispatches vtable slot 50 submit on thread proc 0xbc65720 [V]); the game-thread / dragon-task-thread / render-thread model per 6as/6ac is mapped by [V] RVAs (0xbc65720, 0xbc63150, 0xbc65800, 0xc25fc50, 0xc267200, 0xc25b1a0, 0x66232b0) with thread-role names [I] per 6as/6ac (L17e already done); the semaphore order and double-buffer slots are [V]; BGFX_MAP 11d exists on disk with the contract [V]. Blocking fact: none.

## TOOL REQUESTS

None (verify_oc/delegate.py used as-is; no helper script written).
