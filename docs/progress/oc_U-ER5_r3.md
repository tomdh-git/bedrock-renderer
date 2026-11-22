## NEXT
DONE

# Unit U-ER5 — R5 EditorHighlight (Effect tag 8): 64-byte block, +0x50, pass+0x80 consumer

Goal (checklist R5, docs/RENDER_CHECKLIST.md line 603): close the pending parts — the meanings of the description's 64-byte block (+0x10..+0x4F) and +0x50, and identification of the pass that consumes the pass+0x80 queue.

## Sources read fully
- docs/progress/oc_U-ER5_r1.md (prior RETRY #1 attempt; its PROGRESS notes read first; nothing re-done that was already proven)
- docs/progress/oc_U-EffB.md + docs/progress/_effB_data.txt — Effect group visitor case 0x666b316 (tag 8; description register r15, copied to rbx at case entry), read-site filter
- docs/progress/oc_U-Edh.md — clone 0x4c8a5b0 + producer 0x4c88900 dossiers
- docs/functions/0x666b316.md, docs/functions/0x4c8a5b0.md
- docs/BGFX_MAP.md — section 6ih EditorHighlight paragraph
- docs/data/producer_fields.txt — EditorHighlight producer store map
- docs/progress/descriptions.md and docs/progress/re_small_overlays.md

## Convention
[V] = seen in the disassembly, instruction cited verbatim; [I] = inferred from the instruction pattern; [?] = unknown (no instruction or string shows it). Meaning column: '-' unless an instruction or a string names the field. No sizes, offsets or names written unless seen.

## Answer table: RenderEditorHighlightDescription (0x58 bytes, Effect tag 8, clone 0x4c8a5b0, producer 0x4c88900 builds the record at [rbp+0x568]; tag-8 case 0x666b316 copies it verbatim into pass vector entry at [r15])

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| +0x00 | 8 | producer: call 0x4DFB570 initializes the pair at [rbp+0x568] (`0x4c893cf  lea rcx,[rbp+0x568]`, `0x4c893d9  call 0x4DFB570`); case entry `0x666b316  mov rbx,r15` (rbx = desc); desc source read `0x666b586  mov rax,[rbx]`, stored to pass element `0x666b589  mov [r15],rax` | `0x666b586  mov rax,[rbx]` | shared_ref object pointer; +0x00..+0x0F is the shared_ref pair (object ptr + control-block ptr) | [I] |
| +0x08 | 8 | desc source read `0x666b58c  mov rax,[rbx+8]`; addref `0x666b3cb  lock inc dword ptr [rax+8]` (rax = [desc+0x08] = control-block pointer; matches BGFX_MAP 6ih `lock inc [ctrl+8]`); stored `0x666b590  mov [r15+8],rax` | `0x666b58c  mov rax,[rbx+8]` | control-block pointer of the shared_ref pair | [I] |
| +0x10 | 16 | producer stores +0x10 dword=1, +0x14 qword [r12+0x84], +0x1C dword [r12+0x8C]; desc source read `0x666b594  movups xmm0,[rbx+0x10]`, stored `0x666b5a4  movups [r15+0x10],xmm0` | `0x666b594  movups xmm0,[rbx+0x10]` | dword 1; qword [settings+0x84]; dword [settings+0x8C]; settings fields unnamed | [?] |
| +0x20 | 16 | producer stores +0x20 f32 [r12+0x90] via xmm14, +0x24 qword [r12+0x84], +0x2C dword [r12+0x8C]; desc source read `0x666b598  movups xmm1,[rbx+0x20]`, stored `0x666b5a9  movups [r15+0x20],xmm1` | `0x666b598  movups xmm1,[rbx+0x20]` | f32 [settings+0x90]; qword [settings+0x84]; dword [settings+0x8C]; settings fields unnamed | [?] |
| +0x30 | 16 | producer stores +0x30 f32 [r12+0x90] via xmm14, +0x34..+0x43 16B vec4 [r12+0x74]; desc source read `0x666b59c  movups xmm2,[rbx+0x30]`, stored `0x666b5ae  movups [r15+0x30],xmm2` | `0x666b59c  movups xmm2,[rbx+0x30]` | f32 [settings+0x90]; vec4 [settings+0x74]; settings fields unnamed | [?] |
| +0x40 | 16 | producer: +0x40..+0x43 = high dword of the +0x34 vec4 store; +0x44..+0x4F = 16B constant vec4 xmm12 = (0.12, 1, 1, 0.125); desc source read `0x666b5a0  movups xmm3,[rbx+0x40]`, stored `0x666b5b3  movups [r15+0x40],xmm3` | `0x666b5a0  movups xmm3,[rbx+0x40]` | constant vec4 tail (0.12,1,1,0.125 at +0x44..+0x4F); no semantic name | [?] |
| +0x50 | 8 | producer: +0x50..+0x53 = dword 0.125f; +0x54..+0x57 = dword 1.0f; desc source read `0x666b5b8  mov rax,[rbx+0x50]`, stored `0x666b5bc  mov [r15+0x50],rax` | `0x666b5b8  mov rax,[rbx+0x50]` | 0.125f then 1.0f; no semantic name in any instruction or string | [?] |
| pass +0x80 | 8 | pass object: `0x666b319  mov ecx,0x9D0`, `0x666b31e  add rcx,[r12+0x10]`, `0x666b323  call 0x5ABA5C0` (rsi = pass, `0x666b328  mov rsi,rax`); vector end `0x666b3a6  mov r15,[rsi+0x80]`, cap test `0x666b3ad  cmp r15,[rsi+0x88]`; writer `0x666b5c0  add qword ptr [rsi+0x80],0x58` (end += element stride 0x58) | `0x666b5c0  add qword ptr [rsi+0x80],0x58` | pass vector begin +0x78 / end +0x80 / cap +0x88, element stride 0x58; the consuming pass itself is not located [?] | [V] |

## What is proven for the 64-byte block (+0x10..+0x4F) and +0x50
Byte contents are fully proven by the producer stores above (the visitor copies them verbatim, 0x58 bytes, `0x666b586..0x666b5bc`):
- +0x10 dword 1; +0x14/+0x24 qword [settings+0x84]; +0x1C/+0x2C dword [settings+0x8C]; +0x20/+0x30 f32 [settings+0x90] (xmm14); +0x34..+0x43 vec4 [settings+0x74]; +0x44..+0x4F constant vec4 (0.12, 1, 1, 0.125).
- +0x50..+0x53 = 0.125f (part of the +0x44 store); +0x54..+0x57 = 1.0f (`0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000`).
No instruction or string gives any of these fields a semantic name, so their meanings stay [?], not [V]. The settings object (r12, element of the shared_ptr vector [rbp+0x618]) exposes fields +0x74 vec4, +0x84 qword, +0x8C dword, +0x90 f32, all unnamed [I: sources only].

## Part 3 — the pass that consumes pass+0x80 [?]
The Effect tag 8 case gets the pass object via `0x666b319  mov ecx,0x9D0` / `0x666b31e  add rcx,[r12+0x10]` / `0x666b323  call 0x5ABA5C0` (ThreadLocalObject::get at frameCtx+0x10+0x9D0; rsi = pass), takes the vector end `0x666b3a6  mov r15,[rsi+0x80]` against cap `0x666b3ad  cmp r15,[rsi+0x88]`, appends the description verbatim as a 0x58-byte element at pass+0x78 and advances the end with `0x666b5c0  add qword ptr [rsi+0x80],0x58`.
The consumer/drainer of this queue is NOT located: no decoded pass reads [pass+0x78] or [pass+0x80] as this 0x58-stride queue.

## New angles tried (from RETRY #1 requirement — all failed to find the consumer)
1. `rdis imm 0x9D0` — users are all producers/visitors (Light sub_6640d80 x8, Effect tag 8 case, UI sub_6664a00, endFrame sub_66232b0); no consumer found.
2. `rdis callers 0x5ABA5C0` — ~200 sites, all producers/frame-graph builder; no consumer.
3. `ripscan.py 0x9D0` — 0 results (immediate, not rip-relative).
4. `sub_66a6830` (called right after tag-8 queue copy) — shadow-volume builder, a producer not a consumer.
5. endFrame `sub_66232b0` slot 0x9D0 — consumes light records +0x648/+0x650 and +0x20/+0x28 queue stride 0x250 at `0x66289d1  add qword ptr [rsi+0x20],0x250`; full 400-instruction dump has NO +0x78/+0x80 reads.
6. ScreenDraw (EditorHighlight) body `0xbc04dc0` (vtable 0xF43FBF0 slot 2, pass 0xbb84ee0) — reads a2+0x278/a2+0x268/a2+0x280, no queue iteration.
descscan2 not applicable (no candidate consumer function to scan). livemem not applicable (no live instance seed/address for tag-8; range-scan forbidden by brief; live value cannot prove static writer).

## CLOSES?
CLOSES?: NO — single blocking fact: the pass that consumes the pass+0x80 EditorHighlight queue (begin +0x78, end +0x80 advanced at `0x666b5c0  add qword ptr [rsi+0x80],0x58`, cap +0x88, stride 0x58) is not located — no instruction in any decoded pass reads [pass+0x78]/[pass+0x80] as this queue, and the 64-byte block (+0x10..+0x4F) and +0x50 meanings carry no [V] semantic proof (copied verbatim, unnamed; all [?] rows above).

## TOOL REQUESTS
None.