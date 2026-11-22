## NEXT
DONE

# Unit U-ER5 — R5 EditorHighlight (Effect tag 8): meanings of the 64-byte block (+0x10..+0x4F) and +0x50; the pass that consumes the pass+0x80 queue

Goal (checklist R5, docs/RENDER_CHECKLIST.md line 603): close the pending parts — the meanings of the description's 64-byte block (+0x10..+0x4F) and +0x50, and identification of the pass that consumes the pass+0x80 queue (begin +0x78, end +0x80, cap +0x88, element stride 0x58, end advanced at `0x666b5c0  add qword ptr [rsi+0x80],0x58`).

## Sources read fully (precomputed input data; no tools re-run to regenerate it)
- docs/progress/oc_U-ER5_r1.md, oc_U-ER5_r2.md, oc_U-ER5_r3.md (prior RETRY notes: queue proven [V], consumer not located, block/+0x50 meanings no [V] proof — all not re-done)
- docs/progress/oc_U-EffB.md + docs/progress/_effB_data.txt — Effect group visitor case 0x666b316 (tag 8; description register r15 -> rbx at case entry)
- docs/progress/oc_U-Edh.md — clone 0x4c8a5b0 + producer 0x4c88900 dossiers (full listings 0x4c8a5b0..0x4c8a6e9 and 0x4c88900..0x4c89880, phase-exact)
- docs/functions/0x666b316.md, docs/functions/0x4c8a5b0.md
- docs/BGFX_MAP.md — section 6ih EditorHighlight paragraph; line 501 Effect tag 8 = EditorHighlightConfiguration; line 1332 EditorHighlightConfiguration at 0x4c8a5b0
- docs/data/producer_fields.txt — EditorHighlight producer store map
- docs/data/listings/effect_visitor_666aca0_667191c.txt — full listing of fn 0x666aca0 (contains BOTH the tag-8 insert case and the queue drain/compactor)

## Convention
[V] = seen in the disassembly, instruction cited verbatim; [I] = inferred from the instruction pattern (say from what); [?] = unknown (no instruction or string shows it). Meaning column: '-' unless an instruction or a string names the field. No sizes, offsets or names are written unless seen.

## Answer table — RenderEditorHighlightDescription (0x58 bytes; Effect tag 8; tag-8 case entry 0x666b316 inside fn 0x666aca0 copies the description verbatim as a 0x58-byte element into the pass vector at pass+0x78, stride 0x58)
| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| +0x00 | 8 | desc source read `0x666b586  mov rax,[rbx]`; stored to pass element `0x666b589  mov [r15],rax` | `0x666b586  mov rax,[rbx]` | '-': shared_ref object pointer; +0x00..+0x0F is the shared_ref pair (object ptr + control-block ptr) | [I] |
| +0x08 | 8 | desc source read `0x666b58c  mov rax,[rbx+8]`; addref `0x666b3cb  lock inc dword ptr [rax+8]` (rax = [desc+0x08] = control-block pointer; matches BGFX_MAP 6ih `lock inc [ctrl+8]`); stored `0x666b590  mov [r15+8],rax` | `0x666b58c  mov rax,[rbx+8]` | '-': control-block pointer of the shared_ref pair | [I] |
| +0x10 | 16 | desc source read `0x666b594  movups xmm0,[rbx+0x10]`; stored `0x666b5a4  movups [r15+0x10],xmm0` | `0x666b594  movups xmm0,[rbx+0x10]` | '-': producer stores +0x10 dword=1 (`0x4c893df`), +0x14 qword [r12+0x84] (`0x4c89400`), +0x1C dword [r12+0x8C] (`0x4c893f6`); settings fields unnamed | [?] |
| +0x20 | 16 | desc source read `0x666b598  movups xmm1,[rbx+0x20]`; stored `0x666b5a9  movups [r15+0x20],xmm1` | `0x666b598  movups xmm1,[rbx+0x20]` | '-': producer stores +0x20 f32 [r12+0x90] via xmm14 (`0x4c89403`), +0x24 qword [r12+0x84] (`0x4c8941c`), +0x2C dword [r12+0x8C] (`0x4c89412`); settings fields unnamed | [?] |
| +0x30 | 16 | desc source read `0x666b59c  movups xmm2,[rbx+0x30]`; stored `0x666b5ae  movups [r15+0x30],xmm2` | `0x666b59c  movups xmm2,[rbx+0x30]` | '-': producer stores +0x30 f32 [r12+0x90] via xmm14 (`0x4c89420`), +0x34..+0x43 16B vec4 [r12+0x74] (`0x4c89430`); settings fields unnamed | [?] |
| +0x40 | 16 | desc source read `0x666b5a0  movups xmm3,[rbx+0x40]`; stored `0x666b5b3  movups [r15+0x40],xmm3` | `0x666b5a0  movups xmm3,[rbx+0x40]` | '-': producer +0x40..+0x43 high dword of +0x34 vec4 store (`0x4c89430`); +0x44..+0x4F 16B constant vec4 xmm12 = (0.12, 1, 1, 0.125) (`0x4c89434  movups [rbp+0x5AC],xmm12`; `0x4c890df  movaps xmm12,[0xF20A380]`); no semantic name | [?] |
| +0x50 | 8 | desc source read `0x666b5b8  mov rax,[rbx+0x50]`; stored `0x666b5bc  mov [r15+0x50],rax` | `0x666b5b8  mov rax,[rbx+0x50]` | '-': producer +0x50..+0x53 dword 0.125f (part of +0x44 constant-vec4 store `0x4c89434`); +0x54..+0x57 dword 1.0f (`0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000`); no semantic name in any instruction or string | [?] |
| pass +0x80 (queue end) | 8 | pass object via `0x666b319  mov ecx,0x9D0`, `0x666b31e  add rcx,[r12+0x10]`, `0x666b323  call 0x5ABA5C0` (rsi = pass); end `0x666b3a6  mov r15,[rsi+0x80]`, cap test `0x666b3ad  cmp r15,[rsi+0x88]`; writer `0x666b5c0  add qword ptr [rsi+0x80],0x58` | `0x666b5c0  add qword ptr [rsi+0x80],0x58` | pass vector begin +0x78 / end +0x80 / cap +0x88, element stride 0x58; end advanced per inserted EditorHighlight element | [V] |
| pass +0x78 (queue begin) | 8 | consumer reads `0x666cc26  mov rdi,[rsi+0x78]` and `0x666cd95  mov rdi,[rsi+0x78]`; prologue read `0x666ae72  mov rax,[r15+0x78]`; reset `0x666ce2c  mov [rsi+0x78],r14` | `0x666cc26  mov rdi,[rsi+0x78]` | queue begin; read by the drain/compactor inside fn 0x666aca0 (consumer located — see below) | [V] |
| pass +0x88 (queue cap) | 8 | consumer reads `0x666b3ad  cmp r15,[rsi+0x88]` (cap test at insert) and `0x666cdf5  mov rdx,[rsi+0x88]` (drain); reset `0x666ce45  mov [rsi+0x88],r12` | `0x666cdf5  mov rdx,[rsi+0x88]` | queue cap; read by the drain/compactor inside fn 0x666aca0 | [V] |

## What is proven [V] for the block (+0x10..+0x4F) and +0x50
Byte contents only: the visitor copies the description verbatim as a 0x58-byte element (`0x666b586..0x666b5bc`, ending `0x666b5c0  add qword ptr [rsi+0x80],0x58`). Producer stores (producer 0x4c88900 builds the record at [rbp+0x568]): +0x10 dword 1 (`0x4c893df`); +0x14/+0x24 qword [r12+0x84] (`0x4c89400`/`0x4c8941c`); +0x1C/+0x2C dword [r12+0x8C] (`0x4c893f6`/`0x4c89412`); +0x20/+0x30 f32 [r12+0x90] via xmm14 (`0x4c89403`/`0x4c89420`); +0x34..+0x43 vec4 [r12+0x74] (`0x4c89430`); +0x40..+0x43 high dword of that vec4 store; +0x44..+0x4F constant vec4 xmm12 = (0.12, 1, 1, 0.125) (load `0x4c890df  movaps xmm12,[0xF20A380]`, store `0x4c89434  movups [rbp+0x5AC],xmm12`); +0x50..+0x53 = 0.125f (element 3 of the +0x44 store); +0x54..+0x57 = 1.0f (`0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000`). No instruction or string gives any of these fields a semantic name, so their meanings stay [?], not [V]. The settings object (r12, element of the shared_ptr vector [rbp+0x618]) exposes fields +0x74 vec4, +0x84 qword, +0x8C dword, +0x90 f32, all unnamed [I: sources only]. Live capture cannot add tag-8 data: docs/data/live/effect_visitor.txt (capture at fn entry 0x666ACA0, kind=visitor, size=0x300) holds tags 1-4 only — grep for '^8 ' returns 0 samples.

## Part 3 — the pass that consumes pass+0x80 — LOCATED [V]
No separate consuming pass exists. The queue is drained/compacted by the SAME Effect visitor function, fn 0x666aca0, in the code immediately following the insert cases, before the shared tail at 0x666ce59:
- `0x666cc26  mov rdi,[rsi+0x78]` / `0x666cc2a  mov rax,[rsi+0x80]` — reads queue begin ([pass+0x78]) and end ([pass+0x80]); element copy loops with stride `add rax,0x58` / `add rdi,0x58` (`0x666cc86`, `0x666cc8a`, `0x666cd76`, `0x666cd7a`) copy each 0x58-byte element verbatim (+0x00, +0x08 with `lock inc dword ptr [rcx+8]` addref at `0x666cc9f`/`0x666cd23`/`0x666cd8f`, +0x10, +0x20, +0x30, +0x40, +0x50)
- `0x666cdc2  lock dec dword ptr [r15+8]` — releases (consumes) each element's shared_ref in the drain loop (0x666cdb9..0x666cdb7)
- `0x666ce27  call 0xE935700` / `0x666ce24  mov rcx,rdi; call 0xE935700` — frees the queue buffer when empty
- `0x666ce2c  mov [rsi+0x78],r14` / `0x666ce3b  mov [rsi+0x80],rax` (`rax = r14 + [rbp+0x648]*0x58` at `0x666ce30  imul rax,[rbp+0x648],0x58`) / `0x666ce45  mov [rsi+0x88],r12` — resets begin/end/cap after the drain
- `0x666aea7  call 0x66B2B30` with `rdx = &pass+0x78` (`0x666ae91  lea r12,[r15+0x78]`, `0x666aea4  mov rdx,r12`): sub_66b2b30 parses the head queued element (`0x66b2b5b  mov rcx,[rdx]` = [pass+0x78] = begin; `0x66b2b5e  mov rdx,[rcx+0x40]` reads element+0x40; decodes flags at [that+0x180/+0x181/+0x185] into an output record at `0x66b2c11..0x66b2cfe`)
- Earlier queue-prologue read `0x666ae72  mov rax,[r15+0x78]` ([pass+0x78] begin) gates the whole path (`0x666ae79  je 0x6670032` if empty)

So the "consuming pass" is not a separate pass: the EditorHighlight queue (begin +0x78, end +0x80, cap +0x88, stride 0x58) is written by the tag-8 case and drained by fn 0x666aca0 itself (the effect visitor). Proven [V]; the earlier hypothesis (Forward sub-pass ScreenDraw 0xbc04dc0 / rendergraph builder 0xbb84ee0 / endFrame 0x66232b0) is dead — none reads [pass+0x78]/[pass+0x80].

## Exhausted angles (not re-done)
rdis imm 0x9D0; rdis callers 0x5ABA5C0 (~200 sites); ripscan 0x9D0 (0 — immediate); sub_66a6830 (shadow-volume builder); endFrame sub_66232b0 (slot 0x9D0; light records +0x648/+0x650 and +0x20/+0x28 queue stride 0x250 at `0x66289d1  add qword ptr [rsi+0x20],0x250`; no +0x78/+0x80 reads); ScreenDraw body 0xbc04dc0 (pass 0xbb84ee0; no queue iteration); rendergraph builder 0xbb84ee0 (full 860-line listing read — pass builder only); descscan2 (no candidate consumer function); livemem (no seed address; range-scan forbidden). Live: effect_visitor.txt capture at 0x666ACA0 exists but has no tag-8 samples; mc_root_4e05e50_callers dumps are texture objects, not the pass object.

## CLOSES?
CLOSES?: NO — single blocking fact: the pass+0x80 queue consumer IS now proven [V] (drain/compactor inside sub_666aca0: 0x666cc26/0x666cc2a/0x666cdf5/0x666cdc2/0x666ce27/0x666ce2c-0x666ce45, plus 0x666aea7 call 0x66B2B30 with rdx=&pass+0x78), but the semantic meanings of the 64-byte block (+0x10..+0x4F) and +0x50 carry no [V] proof — no instruction or string names them (all block/+0x50 rows are [?] with meaning '-'; only verbatim byte contents are proven). No tag-8 live samples exist to add information.

## TOOL REQUESTS
None.
