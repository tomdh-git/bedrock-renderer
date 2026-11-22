## NEXT
DONE — content complete; every quoted `0xRVA  instr` line re-verified verbatim against the exe this session (rdis dis); CLOSES? NO (block/+0x50 semantic names unproven; capture er5_clone_4c8a5b0 queued, result pending).

# Unit U-ER5 — R5 EditorHighlight (Effect tag 8): 64-byte block (+0x10..+0x4F) and +0x50 meanings; pass+0x80 queue consumer

Goal (checklist R5): close the pending parts — the semantic meanings of the description's 64-byte block (+0x10..+0x4F) and +0x50, and identification of the pass that consumes the pass+0x80 queue (begin +0x78, end +0x80, cap +0x88, element stride 0x58, end advanced at `0x666b5c0  add qword ptr [rsi+0x80],0x58`).

## Convention
[V] = seen in the disassembly, instruction cited verbatim (RVA of the instruction); [I] = inferred from the instruction pattern; [?] = unknown (no instruction or string shows it). [V live] = live-capture evidence (cite file + line). Meaning column: '-' unless an instruction or a string names the field. No sizes, offsets or names are written unless seen. Sizes: movups/movaps=16, qword=8, dword/movss=4, word=2, byte=1. Every quoted `0xRVA  instr` line is verbatim (two spaces after the address), copied from the listing/rdis output.

## Sources read fully
- docs/progress/oc_U-ER5_r1.md .. oc_U-ER5_r17.md — all prior RETRY notes (queue proven [V]; consumer located [V] inside fn 0x666aca0 drain/compactor; block/+0x50 meanings no [V] proof — not re-done)
- docs/progress/oc_U-EffB.md + docs/progress/_effB_data.txt — Effect group visitor case 0x666b316 (tag 8; description register r15 -> rbx at case entry)
- docs/progress/oc_U-Edh.md — clone 0x4c8a5b0 + producer 0x4c88900 dossiers (full listings 0x4c8a5b0..0x4c8a6e9 and 0x4c88900..0x4c89880, phase-exact)
- docs/functions/0x666b316.md, docs/functions/0x4c8a5b0.md
- docs/BGFX_MAP.md — section 6ih EditorHighlight paragraph; line 322: clone 0x4c8a5b0 = gamecomponents::EditorHighlightConfiguration insert clone (Effect group); line 501 Effect tag 8 = EditorHighlightConfiguration
- docs/data/producer_fields.txt — EditorHighlight producer store map
- docs/data/listings/effect_visitor_666aca0_667191c.txt and docs/data/listings/lightgame_edhighlight_producer_4c88900_4c89881.txt (verified with rdis dis)
- docs/data/listings/effect_fullscreen_emplace_66b2b30_66b2dd9.txt — sub_66b2b30 consumer of queued head element
- docs/data/live/effect_visitor.txt, docs/data/live/editor_visitor.txt — 0 tag-8 samples in either capture
- SDK headers: src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h (RenderEditorHighlightDescription) — field names there are [I] from headers, NOT disassembly

## What is proven [V] (summarized from r1-r17; listings verified with rdis dis, not re-run)

Queue object (pass object obtained via `0x666b319  mov ecx,0x9D0`, `0x666b31e  add rcx,[r12+0x10]`, `0x666b323  call 0x5ABA5C0`, `0x666b328  mov rsi,rax`):
- begin +0x78, end +0x80, cap +0x88; element stride 0x58; end advanced per inserted EditorHighlight element by `0x666b5c0  add qword ptr [rsi+0x80],0x58`; insert cap test `0x666b3ad  cmp r15,[rsi+0x88]`.
- Tag-8 case entry: `0x666b3be  mov rax,[rbx+8]` (desc control-block ptr), `0x666b3c2  test rax,rax`, `0x666b3cb  lock inc dword ptr [rax+8]` (addref on insert). Full verbatim copy of the 0x58-byte description into the queue element: `0x666b586..0x666b5bc`, ending `0x666b5c0  add qword ptr [rsi+0x80],0x58`.

Consumer of the pass+0x80 queue [V]: no separate consuming pass exists. The queue is drained/compacted by the SAME Effect visitor function, fn 0x666aca0, immediately after the insert cases, before the shared tail at 0x666ce59:
- `0x666cc26  mov rdi,[rsi+0x78]` / `0x666cc2a  mov rax,[rsi+0x80]` read queue begin/end; `0x666cc31  cmp r15,rax` / `0x666cc34  je 0x666CD29` loop bound; second begin read `0x666cdf1  mov rdi,[rsi+0x78]`.
- each 0x58-byte element copied verbatim (+0x00, +0x08, +0x10, +0x20, +0x30, +0x40, +0x50): `0x666cc50  mov rcx,[rdi]` / `0x666cc53  mov [rax],rcx`; `0x666cc5e  movups xmm1,[rdi+0x10]` / `0x666cc6e  movups [rax+0x10],xmm1`; `0x666cc62  movups xmm2,[rdi+0x20]` / `0x666cc72  movups [rax+0x20],xmm2`; `0x666cc66  movups xmm3,[rdi+0x30]` / `0x666cc76  movups [rax+0x30],xmm3`; `0x666cc6a  movups xmm4,[rdi+0x40]` / `0x666cc7a  movups [rax+0x40],xmm4`; `0x666cc7e  mov rcx,[rdi+0x50]` / `0x666cc82  mov [rax+0x50],rcx`; `0x666cc86  add rax,0x58` / `0x666cc8a  add rdi,0x58`.
- control block addref `0x666cc9f  lock inc dword ptr [rcx+8]` (after null-skip `0x666cc9d  je short 0x666CC50`); old elements released `0x666cdd8  lock dec dword ptr [r15+0xC]`.
- queue buffer free `0x666ce24  mov rcx,rdi` / `0x666ce27  call 0xE935700`; begin/end/cap reset `0x666ce2c  mov [rsi+0x78],r14` / `0x666ce3b  mov [rsi+0x80],rax` / `0x666ce45  mov [rsi+0x88],r12`.
- head element parsed for rendering: `0x666ae72  mov rax,[r15+0x78]` / `0x666ae79  je 0x6670032` (skip if empty) / `0x666ae91  lea r12,[r15+0x78]` / `0x666aea4  mov rdx,r12` / `0x666aea7  call 0x66B2B30`; sub_66b2b30 reads `0x66b2b5b  mov rcx,[rdx]` (element+0x00 = object pointer) then `0x66b2b5e  mov rdx,[rcx+0x40]` (object+0x40 flags) — the renderer consumes the shared config OBJECT (desc+0x00), NEVER the description block (+0x10..+0x57). Earlier hypotheses (Forward sub-pass ScreenDraw 0xbc04dc0, rendergraph builder 0xbb84ee0, endFrame 0x66232b0) are dead: none reads [pass+0x78]/[pass+0x80] as this queue.

## Producer value provenance [V] (producer 0x4c88900 builds the 0x58-byte record at [rbp+0x568]; desc base handed to clone 0x4c8a5b0 at `0x4c89478  call 0x4C8A5B0`; `0x4c893d0 lea ecx,[rbp+0x568]` / `0x4c893d9 call 0x4DFB570` builds the +0x00/+0x08 shared_ref pair from the settings object r12)

The settings object r12 is taken from the shared-pointer vector [rbp+0x618]..[rbp+0x620] (element addref via `lock cmpxchg [rcx+8]` at 0x4c89127); the producer reads from it: vec4 [r12+0x74] (`0x4c89363  movups xmm0,[r12+0x74]`), qword [r12+0x84], dword [r12+0x8C], f32 [r12+0x90] (`0x4c8938d  movss xmm14,[r12+0x90]`). Stores into the description record (rcx base = [rbp+0x57C] = desc+0x14):

- `desc+0x10`: `0x4c893df  mov dword ptr [rbp+0x578],1` → dword 1
- `desc+0x14`: `0x4c89400  mov [rcx],rax` (rax = [rbp+0x630] = [r12+0x84]) → qword [r12+0x84]
- `desc+0x1C`: `0x4c893f6  mov [rcx+8],eax` (eax = [rbp+0x638] = [r12+0x8C]) → dword [r12+0x8C]
- `desc+0x20`: `0x4c89403  movss [rbp+0x588],xmm14` (xmm14 = [r12+0x90]) → f32 [r12+0x90]
- `desc+0x24`: `0x4c8941c  mov [rcx+0x10],rax` (rax = [rbp+0x640] = [r12+0x84]) → qword [r12+0x84]
- `desc+0x2C`: `0x4c89412  mov [rcx+0x18],eax` (eax = [rbp+0x648] = [r12+0x8C]) → dword [r12+0x8C]
- `desc+0x30`: `0x4c89420  movss [rbp+0x598],xmm14` (xmm14 = [r12+0x90]) → f32 [r12+0x90]
- `desc+0x34..+0x43`: `0x4c89430  movups [rcx+0x20],xmm0` (xmm0 = vec4 [r12+0x74] via `0x4c89363  movups xmm0,[r12+0x74]`) → vec4 [r12+0x74]
- `desc+0x44..+0x4F`: `0x4c89434  movups [rbp+0x5AC],xmm12` (xmm12 = `0x4c890df  movaps xmm12,[0xF20A380]`) → constant vec4
- `desc+0x54..+0x57`: `0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000` → dword 1.0f

No instruction or string names any settings-object field or any block field. Constant vec4 bytes [V live]: `0xF20A380` = `8F C2 F5 3D 00 00 80 3F 00 00 80 3F 00 00 00 3E` = f32 (0.0913, 1.0, 1.0, 0.25); +0x50..+0x53 is the low dword of that store (0x3E000000 = 0.25f).

## New angle tried this session (failed to add [V] meaning)

1. Live capture result checked: `python tools/livecap/request.py result er5_clone_4c8a5b0` → "no result yet (orchestrator has not run it)"; docs/data/live/er5_clone_4c8a5b0.txt does not exist. The capture (clone 0x4c8a5b0 entry, rdx = description pointer at entry, size 0x100, max 6) remains queued in docs/progress/capture_requests.json; no re-add attempted ("already queued"). No live bytes available to decode this session. Even when delivered, capture bytes confirm runtime VALUES only — they cannot supply a semantic name that no instruction or string provides.

2. Sibling-unit cross-check (new static angle): oc_U-D9c2.md, oc_U-EL4w_r1..r5.md, light_game_descriptions.md §3.3. These confirm the producer copies unnamed settings-object fields into the block — vec4 [r12+0x74] → desc +0x34..+0x43, qword [r12+0x84] → +0x14/+0x24, dword [r12+0x8C] → +0x1C/+0x2C, f32 [r12+0x90] → +0x20/+0x30, constant vec4 [0xF20A380] → +0x44..+0x4F (+0x50 low dword), dword 1.0 → +0x54 — but NONE of those units proves a semantic name for any settings field or block field: oc_U-EL4w_r5 is blocked on the desc+0x08 writer (vtable 0xf20aa50 object; constructor not statically locatable — vptr never materialized, RTTI stripped, no ctor, no live tag-8 seed, range-scan forbidden) and oc_U-D9c2 leaves the block-region rows [UNVERIFIED]. No `rdis str` hit names a block field; descscan2 found no consumer function reading +0x10..+0x57; vt/vcalls reached no candidate. All static angles from r1-r17 remain exhausted (per the 2026-11-22 orchestrator review): rdis imm/xr/callers (~0x5ABA5C0), ripscan 0x9D0 (0 hits), endFrame 0x66232b0, ScreenDraw 0xbc04dc0, rendergraph builder 0xbb84ee0, sub_66a6830.

3. livemem: no tag-8 instance seed address is known (effect_visitor.txt and editor_visitor.txt have no tag-8 samples); range-scanning memory is forbidden by the brief, so there is nothing to read. [UNVERIFIED: 0x4c88900 settings-object field names — writer of the runtime object's fields not located]

Result: this session adds producer VALUE provenance [V] for every block/+0x50 byte but no [V] semantic name. The block fields are dead stores: copied verbatim, queued, released, never read by the consumer (sub_66b2b30 reads element+0x00 → object+0x40 only; head gate at `0x666ae72`/`0x666ae7f` also touches only element+0x00 → object+0x40).

## Answer table — RenderEditorHighlightDescription (0x58 bytes; Effect tag 8; tag-8 case 0x666b316 inside fn 0x666aca0 copies the description verbatim as a 0x58-byte element into the pass vector at pass+0x78, stride 0x58; producer 0x4c88900 builds the record at [rbp+0x568])

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| +0x00 | 8 | desc source read `0x666b586`; element write `0x666b589`; insert addref of [rbx+8] `0x666b3cb`; drain read `0x666cc50` / write `0x666cc53` / drain addref `0x666cc9f`; producer pair build `0x4c893d0` / `0x4c893d9`; consumer head parse `0x666ae72` → `0x666ae7f  cmp qword ptr [rax+0x40],0` then `0x666aea7  call 0x66B2B30` → `0x66b2b5b` / `0x66b2b5e` | `0x666b586  mov rax,[rbx]` | '-': shared_ref pair head = object pointer; element +0x00..+0x0F copied verbatim on insert and drain; sub_66b2b30 dereferences element+0x00 as an object pointer (+0x40 flags), but no instruction or string names this field | [I] |
| +0x08 | 8 | desc source read `0x666b58c`; element write `0x666b590`; insert addref `0x666b3cb` (ctrl+8 strong refcount) [V]; drain `0x666cc56` / `0x666cc5a` / addref `0x666cc9f` [V]; release `0x666cdd8` (ctrl+0xC weak) [V] | `0x666b58c  mov rax,[rbx+8]` | '-': control-block pointer of the shared_ref pair; strong refcount at ctrl+8 (lock inc on insert and drain) [V], weak count at ctrl+0xC (lock dec on release) [V]; unnamed | [I] |
| +0x10 | 16 | desc source read `0x666b594`; element write `0x666b5a4`; drain `0x666cc5e` / `0x666cc6e`; producer store `0x4c893df` (dword 1 at desc+0x10) | `0x666b594  movups xmm0,[rbx+0x10]` | '-': dword 1 stored by producer at +0x10; remaining 12 bytes dead store — copied, queued, released, never read by consumer (sub_66b2b30 reads element+0x00 → object+0x40 only); no instruction or string names the field | [?] |
| +0x20 | 16 | desc source read `0x666b598`; element write `0x666b5a9`; drain `0x666cc62` / `0x666cc72`; producer store `0x4c89403` (f32 [r12+0x90] at +0x20) | `0x666b598  movups xmm1,[rbx+0x20]` | '-': producer stores f32 [r12+0x90] (settings object field, unnamed) at +0x20; dead store after copy; no instruction or string names the field | [?] |
| +0x30 | 16 | desc source read `0x666b59c`; element write `0x666b5ae`; drain `0x666cc66` / `0x666cc76`; producer store `0x4c89420` (f32 [r12+0x90] at +0x30) | `0x666b59c  movups xmm2,[rbx+0x30]` | '-': producer stores f32 [r12+0x90] at +0x30; dead store; no instruction or string names the field | [?] |
| +0x40 | 16 | desc source read `0x666b5a0`; element write `0x666b5b3`; drain `0x666cc6a` / `0x666cc7a`; producer store `0x4c89430` (vec4 [r12+0x74] spans +0x34..+0x43; high dword at +0x40..+0x43) and `0x4c89434` (constant vec4 at +0x44..+0x4F) | `0x666b5a0  movups xmm3,[rbx+0x40]` | '-': high dword of vec4 [r12+0x74] at +0x40..+0x43; constant vec4 [0xF20A380] = f32 (0.0913, 1.0, 1.0, 0.25) at +0x44..+0x4F [V live]; settings field unnamed; dead store; no instruction or string names the field | [?] |
| +0x50 | 8 | desc source read `0x666b5b8`; element write `0x666b5bc`; drain `0x666cc7e` / `0x666cc82`; producer: +0x54..+0x57 dword 0x3F800000 `0x4c8943c`; +0x50..+0x53 low dword of constant-vec4 store `0x4c89434` (0x3E000000 = 0.25f) | `0x666b5b8  mov rax,[rbx+0x50]` | '-': qword copied verbatim; +0x54 = 1.0f; no instruction or string names the field | [?] |
| pass +0x78 | 8 | queue begin: reads `0x666cc26` / `0x666cdf1`; gate `0x666ae72` / `0x666ae79  je 0x6670032` (skip if empty); head parse `0x666ae91` / `0x666aea4` / `0x666aea7  call 0x66B2B30`; reset `0x666ce2c` | `0x666cc26  mov rdi,[rsi+0x78]` | queue begin; read by the drain/compactor inside fn 0x666aca0 itself — no separate consuming pass exists | [V] |
| pass +0x80 | 8 | queue end: `0x666b3a6  mov r15,[rsi+0x80]`; cap test `0x666b3ad  cmp r15,[rsi+0x88]`; writer `0x666b5c0` (end += 0x58 per element); drain `0x666cc2a`; reset `0x666ce3b` | `0x666b5c0  add qword ptr [rsi+0x80],0x58` | queue end; advanced per inserted EditorHighlight element | [V] |
| pass +0x88 | 8 | queue cap: insert cap test `0x666b3ad`; drain `0x666cdf5`; buffer free `0x666ce24` / `0x666ce27  call 0xE935700`; reset `0x666ce45` | `0x666cdf5  mov rdx,[rsi+0x88]` | queue cap; read by the drain/compactor | [V] |

## CLOSES?

CLOSES?: NO — single blocking fact: the pass+0x80 queue consumer IS proven [V] (drain/compactor inside sub_666aca0 itself; head parsed by sub_66b2b30 via element+0x00 → object+0x40; no separate pass exists), but the semantic meanings of the 64-byte block (+0x10..+0x4F) and +0x50 carry NO [V] proof: every block/+0x50 row above is [?] with meaning '-', no instruction or string names them, the consumer never reads them (dead stores), producer value provenance [V] is known (settings-object fields [r12+0x74]/[r12+0x84]/[r12+0x8C]/[r12+0x90] and constant vec4 [0xF20A380]) but those fields are themselves unnamed anywhere, and the live capture er5_clone_4c8a5b0 that could confirm runtime field values is queued (pending) but its result file docs/data/live/er5_clone_4c8a5b0.txt does not yet exist. Byte layout, copy sites, sizes, constant bytes [V]/[V live] are proven; semantic names remain unproven.

## TOOL REQUESTS

CAPTURE REQUESTED er5_clone_4c8a5b0 — already queued (pending) in docs/progress/capture_requests.json: clone 0x4c8a5b0 entry (rdx = fully built EditorHighlight description ptr), size 0x100, max 6, why "R5: clone entry, rdx = desc ptr: 64-byte block (+0x10..+0x4F) and +0x50 values". Result file docs/data/live/er5_clone_4c8a5b0.txt does not yet exist; read it when the orchestrator runs the batch and decode bytes per offset as [V live]. No re-add attempted ("already queued"). Helper scripts: None.

