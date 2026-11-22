## NEXT
DONE

# M1f D3 pass — final: every D2 dossier has a live row

GOAL (met): M1f "Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked (never a debugger/breakpoint session: it crashed the game twice)" (docs/RENDER_CHECKLIST.md line 443). Entry state was PARTIAL = NOT DONE; all captures this unit queued have now run and exist under docs/data/live/. Static proof rows for the submit/executor/PSO/flush/endFrame/dispatch/view-setup paths were written verbatim from rdis in earlier runs (docs/progress/oc_U-EM1f_r1..r3.md); this file closes the item with the live table.

Per the live-data README (docs/data/live/README.md line 3-6), each capture file's line 1 states the target rva/kind/size and line 3 is the CALLER record (ret = caller); register dumps follow. All citations below are [V live] file:line.

## Final table: D2 dossier -> live capture -> confirmed

| dossier (D2 claim) | rva | proof instr (verbatim) | live file:line | hits | samples | per-frame | confirmed |
| submit entry 0xe82e230: Frame ptr in RDX; item count [Frame+0xDC57E8], counter [Frame+0xE746D8], backbuffer [Frame+0xDC5808] | 0xe82e230 | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | u_em1f_submit_entry.txt:3 | 418 | 32 | ~0.38/frame (418/1108 endFrames; submit not called every frame) | YES |
| draw flush / DrawBatcher 0xe81b720: pending counts [batcher+0x10+kind*4], record arrays, per-draw emission path | 0xe81b720 | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | u_em1f_draw_flush.txt:3 | 354192 | 32 | ~320/frame (354192/1108; matches ~514 items/frame) | YES |
| endFrame 0xc270460: rcx = BgfxContext, early-out flag [rcx+0x35] | 0xc270460 | `0xc270521  call 0xC273420` | u_em1f_endframe.txt:3 | 1108 | 34 | exactly 1/frame | YES |
| task dispatch 0xe9002e0: dispatch struct {allocator, sub-object ptr, task-list ptr, surface, DragonFrameResources*} | 0xe9002e0 | `0xc270554  call 0xE9002E0` | u_em1f_dispatch.txt:3 | 1108 | 32 | exactly 1/frame; 1:1 with endFrame | YES |
| frame-graph generate/encode 0xc273420 | 0xc273420 | `0xc270521  call 0xC273420` (caller) | u_em1f_generate.txt:3 | 1105 | 32 | ~1/frame (3 hits lost to capture window edge vs endFrame's 1108) | YES |
| view-setup task 0x568cdcc: viewId word [[task+8]]+8, per-view record rect/matrix/sort-mode writes | 0x568cdcc | `0x568cdcc  movzx eax,word ptr [rax+8]` | u_em1f_view_setup.txt:3 | 14371 | 34 | ~13/endFrame (14371/1108) | YES |

## DrawIndexedInstanced reach claim (the last open M1f claim)

The flush body at 0xe81b720 contains `0xe81b866  mov rax,[rax+0x68]` — the cmdlist vtable slot-13 load (D3D12 DrawIndexedInstanced) immediately before the DrawIndexedInstanced call; indexed record fields +0x70 IndexCountPerInstance … +0x80 StartInstanceLocation. Live capture u_em1f_draw_call.txt (rva=0xE81B866, kind=regs, size=0x40, header at line 1) hit that address 212713 times = ~192 DrawIndexedInstanced slot-13 dispatches per frame over 1108 endFrames (212713/1108), so the flush DOES reach DrawIndexedInstanced per draw. Cite: [V live u_em1f_draw_call.txt:1] and its reg dumps at lines 4-48.

`u_em1f_draw_emit` was queued on the same 0xe81b720 as draw_flush (a duplicate target), so it was dropped as pending; the orchestrator ran the sharper draw_call capture instead. Nothing is queued now, and no further capture is needed.

## CLOSES?

YES — every D2 dossier listed above has a [V live] row in docs/data/live/ with quoted hit counts:

- submit_entry: 418 hits, 32 samples — u_em1f_submit_entry.txt:3 (ret=0xE83D4DB caller; RCX=Frame pointer stable across hits)
- draw_flush: 354192 hits, 32 samples — u_em1f_draw_flush.txt:3 (~320/frame, matches ~514 items/frame; ret=0xE822E53/0xE822E70/0xE82D130/0xE82D14D callers)
- endframe: 1108 hits, 34 samples — u_em1f_endframe.txt:3 (exactly 1/frame; rcx = BgfxContext)
- dispatch: 1108 hits, 32 samples — u_em1f_dispatch.txt:3 (1:1 with endFrame; ret=0xC270559)
- generate: 1105 hits, 32 samples — u_em1f_generate.txt:3 (~1/frame; ret=0xC270526)
- view_setup: 14371 hits, 34 samples — u_em1f_view_setup.txt:3 (~13/endFrame; ret=0xFFFF8009FA420000*)
- DrawIndexedInstanced reach: draw_call 212713 hits, 24 samples at 0xe81b866 (~192/frame) — u_em1f_draw_call.txt:1; flush fires per draw: 354192/1108 ≈ 320/frame — u_em1f_draw_flush.txt:3

No capture is pending (draw_emit dropped as duplicate of draw_flush).

## TOOL REQUESTS

None — all queued captures (submit_entry, draw_flush, endframe, dispatch, view_setup, generate, draw_call) ran and are cited above; nothing pending; no new capture needed since every dossier has a live row. No in-game step remains (this unit never touches the game; the orchestrator builds and runs captures).
