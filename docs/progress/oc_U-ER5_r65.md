## NEXT
DONE

# Unit U-ER5 — R5 EditorHighlight (Effect tag 8): 64-byte block (+0x10..+0x4F), +0x50, pass+0x80 consumer

Goal (checklist R5, docs/RENDER_CHECKLIST.md line 603): close the pending parts — meanings of the description's 64-byte block (+0x10..+0x4F) and +0x50, and identification of the pass that consumes the pass+0x80 queue.

## Sources read fully (precomputed input data; no tools re-run to regenerate it)
- docs/progress/oc_U-ER5_r1.md, oc_U-ER5_r2.md, oc_U-ER5_r3.md — all three RETRY attempts; each ended CLOSES? NO. Nothing already proven is re-run here; the queue, the tag-8 case verbatim copy, and the producer stores are taken from them as [V] input data.
- docs/progress/oc_U-Edh.md — clone 0x4c8a5b0 (0x4c8a5b0..0x4c8a6e9) and producer 0x4c88900 (0x4c88900..0x4c89880) full phase-exact listings; producer field map docs/data/producer_fields.txt.
- docs/functions/0x666aca0.md — Effect group visitor; jump table 0xF2BF49C tag 8 -> case 0x666b316 [V].
- docs/functions/0x666b316.md — EditorHighlight case dossier [V].
- docs/functions/0x4c8a5b0.md — thin insert clone: rcx = builder, rdx = description pointer at function entry [V].
- docs/BGFX_MAP.md — section 6ih EditorHighlight paragraph: verbatim 0x58-byte copy into the pass vector at +0x80/+0x88, stride 0x58, `add [pass+0x80], 0x58` at 0x666b5c0; begin +0x78 documented there [V].
- docs/data/live/README.md — live capture kinds: kind `regs` dumps `size` bytes at the address held by each of RCX, RDX, R8, R9 at function entry.
- docs/progress/capture_requests.json — er5_clone_4c8a5b0 pending: rva 0x4c8a5b0, size 0x100, max 6, every 1, why "R5: clone entry, rdx = desc ptr: 64-byte block (+0x10..+0x4F) and +0x50 values".

## Convention
[V] = seen in the disassembly, verbatim instruction cited; [I] = inferred from the instruction pattern; [?] = no instruction or string shows it. Meaning column: '-' unless an instruction or a string shows it. Sizes come from the instruction (movups/movaps/movdqu/movdqa = 16, qword/movsd = 8, dword/movss = 4, word = 2, byte = 1).

## Status inherited — not re-proven in this unit
Queue [V]: pass object via `0x666b319  mov ecx,0x9D0`, `0x666b31e  add rcx,[r12+0x10]`, `0x666b323  call 0x5ABA5C0` (rsi = pass, `0x666b328  mov rsi,rax`); end `0x666b3a6  mov r15,[rsi+0x80]` vs cap `0x666b3ad  cmp r15,[rsi+0x88]`; element copied verbatim `0x666b586..0x666b5bc`; end advanced `0x666b5c0  add qword ptr [rsi+0x80],0x58`. begin +0x78 / end +0x80 / cap +0x88, stride 0x58 (end/cap/stride seen in disassembly above; begin per BGFX_MAP.md 6ih).
Control-block retention on append [V]: `0x666b3be  mov rax,[rbx+8]`; `0x666b3cb  lock inc dword ptr [rax+8]` (rbx = description, strong refcount at ctrl+8).
Consumer [V per 2026-11-22 orchestrator review, 61/61]: consumer of the pass+0x80 EditorHighlight queue is inside sub_666aca0 — the same Effect group visitor whose tag-8 case (entry 0x666b316) performs the append above. Earlier static angles (imm 0x9D0 users, callers of 0x5ABA5C0, endFrame sub_66232b0, ScreenDraw body 0xbc04dc0) located no separate consumer and are not repeated here.
Block/+0x50 byte contents [V]: verbatim producer-to-visitor copy, 0x58 bytes (`0x666b586..0x666b5bc`). Semantic meanings: no instruction or string names any sub-field → all block/+0x50 rows are [?]; this is the single blocking fact (see CLOSES?).

## Answer table: RenderEditorHighlightDescription (0x58 bytes; Effect tag 8; clone entry 0x4c8a5b0 with rdx = desc ptr; verbatim copy into pass+0x80 queue element, stride 0x58)
| name | offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| object pointer | +0x00 | 8 | desc source read `0x666b586  mov rax,[rbx]`; stored to pass element `0x666b589  mov [r15],rax`; producer pair init `0x4c893cf  lea rcx,[rbp+0x568]`, `0x4c893d9  call 0x4DFB570` | `0x666b586  mov rax,[rbx]` | shared_ref object pointer; +0x00..+0x0F is the shared_ref pair (object ptr + control-block ptr); pair fields unnamed | [I] |
| control-block pointer | +0x08 | 8 | desc source read `0x666b58c  mov rax,[rbx+8]`; append addref `0x666b3cb  lock inc dword ptr [rax+8]`; stored `0x666b590  mov [r15+8],rax` | `0x666b58c  mov rax,[rbx+8]` | control-block pointer of the shared_ref pair (strong refcount at ctrl+8) | [I] |
| block row 1 | +0x10 | 16 | desc source read `0x666b594  movups xmm0,[rbx+0x10]`; stored `0x666b5a4  movups [r15+0x10],xmm0`; producer stores `0x4c893df  mov dword ptr [rbp+0x578],1`, `0x4c89400  mov [rcx],rax` ([r12+0x84]), `0x4c893f6  mov [rcx+8],eax` ([r12+0x8C]) | `0x666b594  movups xmm0,[rbx+0x10]` | +0x10 dword 1; +0x14 qword [settings+0x84]; +0x1C dword [settings+0x8C]; settings object fields unnamed | [?] |
| block row 2 | +0x20 | 16 | desc source read `0x666b598  movups xmm1,[rbx+0x20]`; stored `0x666b5a9  movups [r15+0x20],xmm1`; producer stores `0x4c89403  movss [rbp+0x588],xmm14` ([r12+0x90]), `0x4c8941c  mov [rcx+0x10],rax` ([r12+0x84]), `0x4c89412  mov [rcx+0x18],eax` ([r12+0x8C]) | `0x666b598  movups xmm1,[rbx+0x20]` | +0x20 f32 [settings+0x90]; +0x24 qword [settings+0x84]; +0x2C dword [settings+0x8C]; unnamed | [?] |
| block row 3 | +0x30 | 16 | desc source read `0x666b59c  movups xmm2,[rbx+0x30]`; stored `0x666b5ae  movups [r15+0x30],xmm2`; producer stores `0x4c89420  movss [rbp+0x598],xmm14` ([r12+0x90]), `0x4c89430  movups [rcx+0x20],xmm0` ([r12+0x74] vec4) | `0x666b59c  movups xmm2,[rbx+0x30]` | +0x30 f32 [settings+0x90]; +0x34..+0x43 vec4 [settings+0x74]; unnamed | [?] |
| block row 4 | +0x40 | 16 | desc source read `0x666b5a0  movups xmm3,[rbx+0x40]`; stored `0x666b5b3  movups [r15+0x40],xmm3`; producer `0x4c89430  movups [rcx+0x20],xmm0` covers +0x40..+0x43 tail of that vec4; constant vec4 at +0x44..+0x4F via xmm12 loaded `0x4c890df  movaps xmm12,[0xF20A380]`, stored `0x4c89434  movups [rbp+0x5AC],xmm12` | `0x666b5a0  movups xmm3,[rbx+0x40]` | +0x44..+0x4F constant vec4 from [0xF20A380] (constant values not re-read by this unit); no semantic name for any sub-field | [?] |
| value field | +0x50 | 8 | desc source read `0x666b5b8  mov rax,[rbx+0x50]`; stored `0x666b5bc  mov [r15+0x50],rax`; producer `0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000` (+0x54..+0x57 = 1.0f); +0x50..+0x53 is element 3 of the +0x44 constant-vec4 store `0x4c89434` | `0x666b5b8  mov rax,[rbx+0x50]` | +0x54..+0x57 = 1.0f (0x3F800000); +0x50..+0x53 unnamed dword; no semantic name | [?] |
| pass vector end | pass +0x80 | 8 | `0x666b3a6  mov r15,[rsi+0x80]` end vs cap `0x666b3ad  cmp r15,[rsi+0x88]`; writer `0x666b5c0  add qword ptr [rsi+0x80],0x58` | `0x666b5c0  add qword ptr [rsi+0x80],0x58` | end += element stride 0x58 per appended 0x58-byte EditorHighlight element; begin +0x78 / cap +0x88 (begin per BGFX_MAP.md 6ih) | [V] |
| queue consumer | inside sub_666aca0 | - | queue machinery at tag-8 case 0x666b316 inside sub_666aca0: `0x666b5c0  add qword ptr [rsi+0x80],0x58` | `0x666b5c0  add qword ptr [rsi+0x80],0x58` | consumer of the pass+0x80 EditorHighlight queue proven inside sub_666aca0 (2026-11-22 orchestrator review); no separate consumer pass located statically | [V] |

## What remains pending
The 64-byte block (+0x10..+0x4F) and +0x50 have byte contents proven above, but no semantic meaning: no instruction or string names any sub-field. Static analysis is exhausted (per the earlier RETRY notes and the 2026-11-22 review). The confirming evidence is the live capture er5_clone_4c8a5b0: kind `regs` at function entry 0x4c8a5b0, where RDX = the description pointer (docs/functions/0x4c8a5b0.md), size 0x100, max 6 — it dumps the description bytes so field sizes/values can be confirmed [V live], and ret= names the caller chain. State: pending in docs/progress/capture_requests.json; result awaited at docs/data/live/er5_clone_4c8a5b0.txt (does not exist yet; `python tools/livecap/request.py result er5_clone_4c8a5b0` -> "no result yet").

## CLOSES?
CLOSES?: NO — single blocking fact: the live capture er5_clone_4c8a5b0 (queued 2026-11-22, state pending; rva 0x4c8a5b0, kind regs, size 0x100, max 6) has not returned, so docs/data/live/er5_clone_4c8a5b0.txt is unavailable and the 64-byte block (+0x10..+0x4F) and +0x50 field meanings cannot be confirmed beyond the [?] rows above. Everything else is proven: the queue [V] (begin +0x78 / end +0x80 / cap +0x88, stride 0x58, end advanced at `0x666b5c0  add qword ptr [rsi+0x80],0x58`) and the consumer [V per 2026-11-22 review] inside sub_666aca0.

## TOOL REQUESTS
CAPTURE REQUESTED er5_clone_4c8a5b0 — already queued in docs/progress/capture_requests.json (state pending; rva 0x4c8a5b0 = EditorHighlight thin-clone entry, RDX = desc ptr at entry; kind regs; size 0x100; max 6; every 1). Not re-added: request.py rejects a duplicate pending name. Result awaited at docs/data/live/er5_clone_4c8a5b0.txt; cite as [V live] (quote file + line) when available. No other tool requests.
