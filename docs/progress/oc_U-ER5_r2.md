## NEXT
DONE

# Unit U-ER5 — R5 EditorHighlight (Effect tag 8): 64-byte block, +0x50, pass+0x80 consumer

Goal (checklist R5, docs/RENDER_CHECKLIST.md line 603): close the pending parts — the meanings of the description's 64-byte block (+0x10..+0x4F) and +0x50, and identification of the pass that consumes the pass+0x80 queue.

## Sources read fully (precomputed input data; no tools re-run to regenerate it)
- docs/progress/oc_U-ER5_r1.md (RETRY #1 notes: queue begin +0x78/end +0x80/cap +0x88/stride 0x58 proven [V] via 0x666b5c0 add; consumer not located; block/+0x50 meanings no [V] proof)
- docs/progress/oc_U-Edh.md — clone 0x4c8a5b0 + producer 0x4c88900 dossiers (full listings 0x4c8a5b0..0x4c8a6e9 and 0x4c88900..0x4c89880, phase-exact)
- docs/functions/0x666b316.md, docs/functions/0x4c8a5b0.md
- docs/functions/light_game_descriptions.md — section 3.3 (description record built at [rbp+0x568] by producer 0x4c88900), section 5 pass-vector table (EditorHighlight: pass +0x78/+0x80/+0x88, element 0x58, written by Effect tag 8), line 1103 (lighting/environment consumers not located — E2 consumer blocker)
- docs/BGFX_MAP.md — section 6ih EditorHighlight paragraph (verbatim 0x58-byte copy to pass vector at +0x80/+0x88, stride 0x58, `add [pass+0x80], 0x58` at 0x666b5c0)
- docs/data/producer_fields.txt — EditorHighlight producer store map

## Convention
[V] = seen in the disassembly, instruction cited verbatim; [I] = inferred from the instruction pattern; [?] = unknown (no instruction or string shows it). Meaning column: '-' unless an instruction or a string names the field. No sizes, offsets or names are written unless seen.

## NEW ANGLES TRIED (this retry) — all failed to locate the consumer
1. `rdis imm 0x9D0` — every user of immediate 0x9D0 is a producer/visitor (Light sub_6640d80 x8, Effect tag 8 sub_666aca0 at 0x666b319, UI sub_6664a00, sub_66232b0 endFrame). No consumer reads slot 0x9D0's pass for the +0x78/+0x80 queue.
2. `rdis callers 0x5ABA5C0` — all ~200 call sites are producers/visitors/frame-graph builder (sub_55f1450 VV frame-graph builder, sub_66232b0 endFrame, sub_66a6830 shadow-volume builder, RenderChunkFogAlpha builders). None is the EditorHighlight-queue consumer.
3. `ripscan.py 0x9D0` — 0 results (0x9D0 is an immediate, not rip-relative).
4. `sub_66a6830` (the call right after the tag-8 queue copy) — it is "Shadow volume builder" (D0), a producer, not a consumer of the queue.
5. `sub_66232b0` (BgfxFrameBuilder::endFrame) at slot 0x9D0 — reads light records +0x648/+0x650 (`lea rdx,[rbx+0x650]` at 0x66286e6) and a +0x20/+0x28 queue stride 0x250 (`add qword ptr [rsi+0x20],0x250` at 0x66289d1); full 400-instruction dump grepped: NO reads of `+0x78` or `+0x80` queue offsets. endFrame is NOT the EditorHighlight consumer.
6. ScreenDraw (EditorHighlight) pass body 0xbc04dc0 (vv_pass_table.md) — reads a2+0x278/a2+0x268/a2+0x280 and other fields, no pass+0x78/+0x80 queue iteration. Not the consumer.

descscan2: not applicable — no candidate consumer function identified to scan. livemem: not applicable — no live instance seed address for the pass/description; range-scan forbidden by brief.

## Answer table: RenderEditorHighlightDescription (0x58 bytes, Effect tag 8; verbatim copy into pass+0x78 queue, stride 0x58)
| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| +0x00 | 8 | desc source read `0x666b586  mov rax,[rbx]`; stored to pass element `0x666b589  mov [r15],rax` | `0x666b586  mov rax,[rbx]` | '-': shared_ref object pointer; +0x00..+0x0F is the shared_ref pair (object ptr + control-block ptr) | [I] |
| +0x08 | 8 | desc source read `0x666b58c  mov rax,[rbx+8]`; addref `0x666b3cb  lock inc dword ptr [rax+8]` (rax = [desc+0x08] = control-block pointer; matches BGFX_MAP 6ih `lock inc [ctrl+8]`); stored `0x666b590  mov [r15+8],rax` | `0x666b58c  mov rax,[rbx+8]` | '-': control-block pointer of the shared_ref pair | [I] |
| +0x10 | 16 | desc source read `0x666b594  movups xmm0,[rbx+0x10]`; stored `0x666b5a4  movups [r15+0x10],xmm0` | `0x666b594  movups xmm0,[rbx+0x10]` | '-': producer stores +0x10 dword=1 (`0x4c893df`), +0x14 qword [r12+0x84] (`0x4c89400`), +0x1C dword [r12+0x8C] (`0x4c893f6`); settings fields unnamed | [?] |
| +0x20 | 16 | desc source read `0x666b598  movups xmm1,[rbx+0x20]`; stored `0x666b5a9  movups [r15+0x20],xmm1` | `0x666b598  movups xmm1,[rbx+0x20]` | '-': producer stores +0x20 f32 [r12+0x90] via xmm14 (`0x4c89403`), +0x24 qword [r12+0x84] (`0x4c8941c`), +0x2C dword [r12+0x8C] (`0x4c89412`); settings fields unnamed | [?] |
| +0x30 | 16 | desc source read `0x666b59c  movups xmm2,[rbx+0x30]`; stored `0x666b5ae  movups [r15+0x30],xmm2` | `0x666b59c  movups xmm2,[rbx+0x30]` | '-': producer stores +0x30 f32 [r12+0x90] via xmm14 (`0x4c89420`), +0x34..+0x43 16B vec4 [r12+0x74] (`0x4c89430`); settings fields unnamed | [?] |
| +0x40 | 16 | desc source read `0x666b5a0  movups xmm3,[rbx+0x40]`; stored `0x666b5b3  movups [r15+0x40],xmm3` | `0x666b5a0  movups xmm3,[rbx+0x40]` | '-': producer +0x44..+0x4F 16B constant vec4 xmm12 ([0xF20A380]=(0.12,1,1,0.125)) (`0x4c89434  movups [rbp+0x5AC],xmm12`; `0x4c890df  movaps xmm12,[0xF20A380]`); no semantic name | [?] |
| +0x50 | 8 | desc source read `0x666b5b8  mov rax,[rbx+0x50]`; stored `0x666b5bc  mov [r15+0x50],rax` | `0x666b5b8  mov rax,[rbx+0x50]` | '-': producer +0x50..+0x53 = 0.125f (element 3 of +0x44 constant-vec4 store `0x4c89434`); +0x54..+0x57 = 1.0f (`0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000`); no semantic name in any instruction or string | [?] |

## What is proven [V] for the block and +0x50
Byte contents only: the visitor copies the description verbatim as a 0x58-byte element (`0x666b586..0x666b5bc`, ending `0x666b5c0  add qword ptr [rsi+0x80],0x58`). Producer stores: +0x10 dword 1; +0x14/+0x24 qword [settings+0x84]; +0x1C/+0x2C dword [settings+0x8C]; +0x20/+0x30 f32 [settings+0x90] (xmm14); +0x34..+0x43 vec4 [settings+0x74]; +0x44..+0x4F constant vec4 (0.12,1,1,0.125); +0x50..+0x53 = 0.125f; +0x54..+0x57 = 1.0f. No instruction or string gives any of these fields a semantic name, so meanings stay [?].

## Part 3 — the pass that consumes pass+0x80 [?]
The Effect tag 8 case gets the pass via `0x666b319  mov ecx,0x9D0` / `0x666b31e  add rcx,[r12+0x10]` / `0x666b323  call 0x5ABA5C0` (ThreadLocalObject::get at ctx+0x9D0; rsi = pass), takes vector end `0x666b3a6  mov r15,[rsi+0x80]` vs cap `0x666b3ad  cmp r15,[rsi+0x88]`, appends the description verbatim as a 0x58-byte element at pass+0x78 and advances end with `0x666b5c0  add qword ptr [rsi+0x80],0x58`. The consumer/drainer of this queue is NOT located: no decoded pass reads [pass+0x78]/[pass+0x80] as this 0x58-stride queue. endFrame (sub_66232b0) consumes light records at +0x648/+0x650 and a +0x20/+0x28 queue from the same slot-0x9D0 pass but reads no +0x78/+0x80 offsets. The only name-match candidate, Forward sub-pass "EditorHighlight" (ScreenDraw body 0xbc04dc0), does not read the queue [?].

## CLOSES?
CLOSES?: NO — single blocking fact: the pass that consumes the pass+0x80 EditorHighlight queue (begin +0x78, end +0x80 advanced at `0x666b5c0  add qword ptr [rsi+0x80],0x58`, cap +0x88, stride 0x58) is not located — no instruction in any decoded pass reads [pass+0x78]/[pass+0x80] as this queue, and the 64-byte block (+0x10..+0x4F) and +0x50 meanings carry no [V] semantic proof (copied verbatim, unnamed; all [?] rows above). Finding the consumer is the prerequisite for [V] field-meaning proof.

## TOOL REQUESTS
None.
