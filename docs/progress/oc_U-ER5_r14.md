## NEXT
DONE

# Unit U-ER5 — R5 EditorHighlight (Effect tag 8): 64-byte block (+0x10..+0x4F) and +0x50 meanings; pass+0x80 queue consumer

Goal (checklist R5, docs/RENDER_CHECKLIST.md line 603): close the pending parts — the semantic meanings of the description's 64-byte block (+0x10..+0x4F) and +0x50, and identification of the pass that consumes the pass+0x80 queue (begin +0x78, end +0x80, cap +0x88, element stride 0x58, end advanced at `0x666b5c0  add qword ptr [rsi+0x80],0x58`).

## Convention
[V] = seen in the disassembly, instruction cited verbatim (RVA of the instruction); [I] = inferred from the instruction pattern; [?] = unknown (no instruction or string shows it). [V live] = live-capture evidence (cite command + output lines). Meaning column: '-' unless an instruction or a string names the field. No sizes, offsets or names written unless seen. Sizes: movups/movaps=16, qword=8, dword/movss=4, word=2, byte=1. Every quoted `0xRVA  instr` line is verbatim (two spaces after the address), copied from the listing/rdis output.

## Sources read fully (precomputed input data; not re-generated this session)
- docs/progress/oc_U-ER5_r1.md .. oc_U-ER5_r13.md — all prior RETRY notes (queue proven [V], consumer located [V] inside fn 0x666aca0 drain/compactor; block/+0x50 meanings no [V] proof — not re-done)
- docs/progress/oc_U-EffB.md + docs/progress/_effB_data.txt — Effect group visitor case 0x666b316 (tag 8; description register r15 -> rbx at case entry)
- docs/progress/oc_U-Edh.md — clone 0x4c8a5b0 + producer 0x4c88900 dossiers (full listings 0x4c8a5b0..0x4c8a6e9 and 0x4c88900..0x4c89880)
- docs/functions/0x666b316.md, docs/functions/0x4c8a5b0.md
- docs/BGFX_MAP.md — section 6ih EditorHighlight paragraph (line 1854): description exactly 0x58 bytes, appended verbatim (qword +0x00, qword +0x08 shared_ptr control block with `lock inc [ctrl+8]`, four 16-byte rows +0x10..+0x4F, qword +0x50), element stride 0x58 (`add [pass+0x80], 0x58` at 0x666b5c0); block meaning unknown [?]
- docs/data/producer_fields.txt — EditorHighlight producer store map
- docs/data/listings/effect_visitor_666aca0_667191c.txt and docs/data/listings/lightgame_edhighlight_producer_4c88900_4c89881.txt (verified with `rdis dis`)
- docs/data/live/effect_visitor.txt, docs/data/live/editor_visitor.txt — 0 tag-8 samples in either capture
- SDK headers: src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h (RenderEditorHighlightDescription) — field names there are [I] from headers, NOT disassembly proof

## Answer table — RenderEditorHighlightDescription (0x58 bytes; Effect tag 8; tag-8 case 0x666b316 inside fn 0x666aca0 copies the description verbatim as a 0x58-byte element into the pass vector at pass+0x78, stride 0x58; producer 0x4c88900 builds the record at [rbp+0x568])
| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| pass +0x78 (queue begin) | +0x78 | 8 | `0x666cc26  mov rdi,[rsi+0x78]` | [V] |
| pass +0x80 (queue end) | +0x80 | 8 | `0x666b5c0  add qword ptr [rsi+0x80],0x58` | [V] |
| pass +0x88 (queue cap) | +0x88 | 8 | `0x666cdf5  mov rdx,[rsi+0x88]` | [V] |
| block +0x00 (shared_ref object pointer) | +0x00 | 8 | `0x666b586  mov rax,[rbx]` | [I] |
| block +0x08 (control-block pointer) | +0x08 | 8 | `0x666b58c  mov rax,[rbx+8]` | [I] |
| block +0x10 | +0x10 | 16 | `0x666b594  movups xmm0,[rbx+0x10]` | [?] |
| block +0x20 | +0x20 | 16 | `0x666b598  movups xmm1,[rbx+0x20]` | [?] |
| block +0x30 | +0x30 | 16 | `0x666b59c  movups xmm2,[rbx+0x30]` | [?] |
| block +0x40 | +0x40 | 16 | `0x666b5a0  movups xmm3,[rbx+0x40]` | [?] |
| block +0x50 | +0x50 | 8 | `0x666b5b8  mov rax,[rbx+0x50]` | [?] |

## What is proven [V]
Queue object (pass object obtained via `0x666b319  mov ecx,0x9D0`, `0x666b31e  add rcx,[r12+0x10]`, `0x666b323  call 0x5ABA5C0`, `0x666b328  mov rsi,rax`; end `0x666b3a6  mov r15,[rsi+0x80]` against cap `0x666b3ad  cmp r15,[rsi+0x88]`):
- begin +0x78, end +0x80, cap +0x88; element stride 0x58; end advanced per inserted EditorHighlight element by `0x666b5c0  add qword ptr [rsi+0x80],0x58`.

Consumer of the pass+0x80 queue [V]: no separate consuming pass exists. The queue is drained/compacted by the SAME Effect visitor function, fn 0x666aca0, immediately after the insert cases, before the shared tail at 0x666ce59:
- `0x666cc26  mov rdi,[rsi+0x78]` / `0x666cc2a  mov rax,[rsi+0x80]` read queue begin/end
- each 0x58-byte element copied verbatim (+0x00, +0x08, +0x10, +0x20, +0x30, +0x40, +0x50), e.g. `0x666cc50  mov rcx,[rdi]` / `0x666cc53  mov [rax],rcx`, `0x666cc7e  mov rcx,[rdi+0x50]` / `0x666cc82  mov [rax+0x50],rcx`, `0x666cc86  add rax,0x58` / `0x666cc8a  add rdi,0x58`
- control block addref `0x666cc9f  lock inc dword ptr [rcx+8]`; old elements released `0x666cdd8  lock dec dword ptr [r15+0xC]`
- queue buffer free `0x666ce24  mov rcx,rdi` / `0x666ce27  call 0xE935700`; begin/end/cap reset `0x666ce2c  mov [rsi+0x78],r14`, `0x666ce30  imul rax,[rbp+0x648],0x58`, `0x666ce3b  mov [rsi+0x80],rax`, `0x666ce45  mov [rsi+0x88],r12`
- head element parsed for rendering: `0x666ae72  mov rax,[r15+0x78]` / `0x666ae79  je 0x6670032` (skip if empty) / `0x666ae91  lea r12,[r15+0x78]` / `0x666aea4  mov rdx,r12` / `0x666aea7  call 0x66B2B30`; sub_66b2b30 reads `0x66b2b5b  mov rcx,[rdx]` (element+0x00 = object pointer) then `0x66b2b5e  mov rdx,[rcx+0x40]` (object+0x40 flags) — the renderer consumes the shared config OBJECT (desc+0x00), NEVER the description block (+0x10..+0x57). Earlier hypotheses (Forward sub-pass ScreenDraw 0xbc04dc0, rendergraph builder 0xbb84ee0, endFrame 0x66232b0) are dead: none reads [pass+0x78]/[pass+0x80] as this queue.

Block byte contents [V]: the visitor copies the description verbatim as a 0x58-byte element (`0x666b586..0x666b5bc`, ending `0x666b5c0  add qword ptr [rsi+0x80],0x58`) and the drain copies each element verbatim including +0x50. Producer stores (record at [rbp+0x568], producer 0x4c88900, desc handed off by `0x4c89478  call 0x4C8A5B0` to clone 0x4c8a5b0): shared_ref pair via `0x4c893cf  lea rcx,[rbp+0x568]` / `0x4c893d9  call 0x4DFB570`; +0x10 dword 1 (`0x4c893df  mov dword ptr [rbp+0x578],1`); +0x14 qword [r12+0x84] (`0x4c89400  mov [rcx],rax`); +0x1C dword [r12+0x8C] (`0x4c893f6  mov [rcx+8],eax`); +0x20 f32 [r12+0x90] via xmm14 (`0x4c89403  movss [rbp+0x588],xmm14`); +0x24 qword [r12+0x84] (`0x4c8941c  mov [rcx+0x10],rax`); +0x2C dword [r12+0x8C] (`0x4c89412  mov [rcx+0x18],eax`); +0x30 f32 [r12+0x90] (`0x4c89420  movss [rbp+0x598],xmm14`); +0x34..+0x43 vec4 [r12+0x74] (`0x4c89430  movups [rcx+0x20],xmm0`); +0x44..+0x4F constant vec4 (`0x4c890df  movaps xmm12,[0xF20A380]`, `0x4c89434  movups [rbp+0x5AC],xmm12`); +0x54..+0x57 dword 0x3F800000 (`0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000`).

Constant vec4 bytes [V live]: `python tools/sigs/livemem.py read @0xF20A380 16` → `00007FF7B4BCA380  8f c2 f5 3d 00 00 80 3f 00 00 80 3f 00 00 00 3e`. Decoded as 4 f32 LE: block +0x44 ≈ 0.0913f (0x3DF5C28F), +0x48 = 1.0f (0x3F800000), +0x4C = 1.0f (0x3F800000), +0x50 = 0.25f (0x3E000000); +0x54..+0x57 = 1.0f. +0x50 is the 4th float of the constant vec4 at +0x44..+0x53, not a separate named field.

## What remains [?] — the single blocking fact
The semantic meanings of the 64-byte block (+0x10..+0x4F) and of +0x50 have NO [V] proof:
- every read of those fields in the entire visitor fn 0x666aca0 is a verbatim copy (insert `0x666b594..0x666b5b8`; drain `0x666cc5e..0x666cd06`), and sub_66b2b30 (the only consumer of the queued head element) reads only element+0x00 → object+0x40 flags, never +0x10..+0x57 — so the block fields are dead stores (copied, queued, released, never interpreted).
- no instruction or string assigns any block/+0x50 field a name (all block/+0x50 rows above have meaning '-'); SDK header names (RenderEditorHighlightDescription.mBlock10[16] +0x10, mValue50 +0x50) are [I] from headers, not disassembly; the producer's settings object fields ([r12+0x74] vec4, [r12+0x84] qword, [r12+0x8C] dword, [r12+0x90] f32) are likewise unnamed.
- static analysis is exhausted (all previously tried angles, not re-run: rdis imm 0x9D0; rdis callers 0x5ABA5C0 (~200 sites); ripscan 0x9D0 (0 hits — immediate); sub_66a6830; endFrame sub_66232b0; ScreenDraw 0xbc04dc0; rendergraph builder 0xbb84ee0; `rdis str "EditorHighlight"` (only pass/scene name strings); descscan2 (no candidate consumer function); livemem on a tag-8 seed (no tag-8 seed address; range-scan forbidden by brief); vt/vcalls (no candidate vtable address reachable from the tag-8 case)). None names a block/+0x50 field.

Byte contents/layout and field sizes are [V]-proven; the constant vec4 bytes are confirmed [V live]. Semantic names remain unproven.

## Capture status
er5_clone_4c8a5b0 (clone 0x4c8a5b0 entry; rdx = description pointer at entry per docs/functions/0x4c8a5b0.md) is queued in docs/progress/capture_requests.json (state "pending", rva 0x4C8A5B0, size 256, max 6, why "R5: clone entry, rdx = desc ptr: 64-byte block (+0x10..+0x4F) and +0x50 values"). `python tools/livecap/request.py add er5_clone_4c8a5b0 0x4c8a5b0 --size 0x100 --max 6 --why "R5: ..."` → "already queued" (cannot re-add). `python tools/livecap/request.py result er5_clone_4c8a5b0` → "no result yet (orchestrator has not run it)". docs/data/live/er5_clone_4c8a5b0.txt does not exist. Per the orchestrator hint (2026-11-22): read that file when it exists; otherwise leave R5 for later. When it exists, decode the dumped description bytes per offset as [V live] (cite file + line) and re-evaluate CLOSES?.

## CLOSES?
CLOSES?: NO — single blocking fact: the pass+0x80 queue consumer IS proven [V] (drain/compactor inside sub_666aca0 itself; head parsed by sub_66b2b30 via element+0x00 → object+0x40; no separate pass exists), but the semantic meanings of the 64-byte block (+0x10..+0x4F) and +0x50 carry no [V] proof — every block/+0x50 row is [?] with meaning '-', no instruction or string names them, the consumer never reads them (dead stores), and the live capture er5_clone_4c8a5b0 that could confirm runtime field values/caller chain is queued but its result file docs/data/live/er5_clone_4c8a5b0.txt does not yet exist.

## TOOL REQUESTS
None (no helper scripts written; all input data was precomputed listings). CAPTURE REQUESTED er5_clone_4c8a5b0 — already queued (pending) in docs/progress/capture_requests.json as shown above; no re-add attempted ("already queued").
