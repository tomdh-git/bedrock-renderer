## NEXT
DONE

# Unit U-ER5 / R5 EditorHighlight (Effect tag 8): meanings of the 64-byte block (+0x10..+0x4F) and +0x50; the pass consuming pass+0x80 queue

GOAL: Close checklist item R5 — decode the semantics of the description's 64-byte block (+0x10..+0x4F) and +0x50 for effect tag 8 (EditorHighlight), and identify the pass consuming pass+0x80.

SOURCES (read, not re-run): docs/data/listings/effect_visitor_666aca0_667191c.txt, docs/data/listings/lightgame_edhighlight_producer_4c88900_4c89881.txt, docs/data/listings/lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt, docs/data/producer_fields.txt (EditorHighlight section), docs/functions/0x4c8a5b0.md, docs/functions/0x666aca0.md, docs/BGFX_MAP.md section 6ih (line 1854), earlier notes oc_U-ER5_r1..r38 (latest r38).

CONVENTION: [V] = instruction seen verbatim in the listing/exe (cite RVA); [V live] = live value from tools/sigs/livemem.py; [I] = inferred; [?] = unknown (no instruction or string shows it). Meaning column: '-' unless an instruction or a string names the field. No sizes/offsets/names written unless seen. Sizes: movups/movaps=16, qword=8, dword/movss=4, word=2, byte=1. Every block/+0x50 access in fn 0x666aca0 is a verbatim copy (no math, compares, or string references on block bytes).

## Answer table (pending part: field meanings of the 64-byte block +0x10..+0x4F and +0x50, effect tag 8, clone 0x4c8a5b0, producer 0x4c88900; one row per offset, all sites listed)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
| +0x10 | 16 | insert: desc source read rbx+0x10, element write [r15+0x10] at 0x666b5a4; drain read [rdi+0x10] at 0x666cc5e, write [rax+0x10] at 0x666cc6e; producer dword 1 at 0x4c893df | `0x666b594  movups xmm0,[rbx+0x10]` | '-': 16-byte field, verbatim-copied on insert and drain; producer stores dword 1; dead store — the block is never read/interpreted by any consumer (sub_66b2b30 reads element+0x00 → object+0x40 only, and only on the FullscreenEffect tag-7 path per BGFX_MAP 6ih line 1854, never +0x10..+0x57, and never for tag 8); no instruction or string names the field | [V] |
| +0x20 | 16 | insert: desc source read rbx+0x20, element write [r15+0x20] at 0x666b5a9; drain read [rdi+0x20] at 0x666cc62, write [rax+0x20] at 0x666cc72; producer stores 4 bytes movss [rbp+0x588],xmm14 at 0x4c89403 (= desc+0x20) | `0x666b598  movups xmm1,[rbx+0x20]` | '-': 16-byte field, verbatim-copied; dead store — never read/interpreted by any consumer; producer value is an unnamed settings-object field (r12+0x90) | [V] |
| +0x30 | 16 | insert: desc source read rbx+0x30, element write [r15+0x30] at 0x666b5ae; drain read [rdi+0x30] at 0x666cc66, write [rax+0x30] at 0x666cc76; producer stores 4 bytes movss [rbp+0x598],xmm14 at 0x4c89420 (= desc+0x30) | `0x666b59c  movups xmm2,[rbx+0x30]` | '-': 16-byte field, verbatim-copied; dead store — never read/interpreted by any consumer; producer value is an unnamed settings-object field (r12+0x90) | [V] |
| +0x40 | 16 | insert: desc source read rbx+0x40, element write [r15+0x40] at 0x666b5b3; drain read [rdi+0x40] at 0x666cc6a, write [rax+0x40] at 0x666cc7a; producer constant vec4 tail `0x4c890df  movaps xmm12,[0xF20A380]` / `0x4c89434  movups [rbp+0x5AC],xmm12` (= desc+0x44..+0x4F) | `0x666b5a0  movups xmm3,[rbx+0x40]` | '-': 16-byte field, verbatim-copied; dead store — never read/interpreted by any consumer; +0x44..+0x4F = constant vec4 tail from data [0xF20A380]; no semantic name | [V] |
| +0x50 | 8 | insert: desc source read rbx+0x50, element write [r15+0x50] at 0x666b5bc; drain read [rdi+0x50] at 0x666cc7e, write [rax+0x50] at 0x666cc82; second drain loop read [r15+0x50] at 0x666cd02, write [rcx+0x50] at 0x666cd06; producer `0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000` (= desc+0x54, 1.0f) | `0x666b5b8  mov rax,[rbx+0x50]` | '-': qword field, verbatim-copied; dead store — never read/interpreted by any consumer; +0x50..+0x53 = element 3 of constant vec4 from data [0xF20A380] = bytes `00 00 00 3e` (0.25f) [V live]; +0x54..+0x57 = 1.0f; no semantic name | [V] |

## Queue / pass context (proven [V], not redone per RETRY rule)

pass+0x78 = queue begin, +0x80 = end, +0x88 = cap, element stride 0x58. Per-EditorHighlight-insert end advance: `0x666b5c0  add qword ptr [rsi+0x80],0x58`. Cap test `0x666b3ad  cmp r15,[rsi+0x88]`; end load `0x666b3a6  mov r15,[rsi+0x80]`. Pass allocates via `0x666b319  mov ecx,0x9D0` / `0x666b31e  add rcx,[r12+0x10]` / `0x666b323  call 0x5ABA5C0` / `0x666b328  mov rsi,rax`; tag-8 case at 0x666b316. Fast-path addref: `0x666b3cb  lock inc dword ptr [rax+8]` (rax = desc+0x8 ctrl block).

Consumer: NO separate consuming pass exists — the drain/compactor is inside fn 0x666aca0 itself right after the insert cases. It walks the queue copying each 0x58-byte element verbatim (`0x666cc50  mov rcx,[rdi]` / `0x666cc53  mov [rax],rcx`; `0x666cc5e..0x666cc7a` movups rows +0x10..+0x40; `0x666cc7e  mov rcx,[rdi+0x50]` / `0x666cc82  mov [rax+0x50],rcx`), then a second drain loop (`0x666cd02  mov rdx,[r15+0x50]` / `0x666cd06  mov [rcx+0x50],rdx`), `0x666cc9f  lock inc dword ptr [rcx+8]`, `0x666cdd8  lock dec dword ptr [r15+0xC]`, `0x666ce27  call 0xE935700`, reset begin/end/cap via `0x666ce2c  mov [rsi+0x78],r14` / `0x666ce3b  mov [rsi+0x80],rax` / `0x666ce45  mov [rsi+0x88],r12`. sub_66b2b30 (`0x66b2b5b  mov rcx,[rdx]` / `0x66b2b5e  mov rdx,[rcx+0x40]`) is the FullscreenEffect tag-7 case's consumer per BGFX_MAP 6ih line 1854 (reads element+0x00 → shared config object +0x40); it is NOT part of the tag-8 path, and nothing interprets block +0x10..+0x57.

## New angle tried this session: post-drain call 0xE935700 at 0x666ce27

Disassembled target: `0xE935700  jmp 0x392960` (tail to sub_392960); the surrounding code block is C++ exception-handling/frame machinery (gs:[0x30] at e935841, `lock cmpxchg [0x128766C0]` at e935857, guard vars [0x128766C0/0x128766D0/0x128766E8]). It reads no description fields and is not an EditorHighlight consumer [V]. Result: nothing after the drain interprets +0x10..+0x50 either — the block is pure verbatim payload from insert through drain through reset.

## Producer (proven [V], not redone)

0x4c88900 builds the record at [rbp+0x568] and hands it to clone 0x4c8a5b0 (`0x4c89478  call 0x4C8A5B0`, rdx=desc): shared_ref ctor `0x4c893d9  call 0x4DFB570` (rdx=r12 settings object); `0x4c893cf  lea rcx,[rbp+0x568]`; +0x10 dword 1 (`0x4c893df  mov dword ptr [rbp+0x578],1`); +0x14=[r12+0x84] (`mov [rcx],rax` at 0x4c89400); +0x1C=[r12+0x8C] (`mov [rcx+8],eax` at 0x4c893f6); +0x20 f32=[r12+0x90] (`0x4c89403  movss [rbp+0x588],xmm14`); +0x24/+0x2C dup of +0x14/+0x1C (`mov [rcx+0x10],rax` at 0x4c8941c / `mov [rcx+0x18],eax` at 0x4c89412); +0x30 f32=[r12+0x90] (`0x4c89420  movss [rbp+0x598],xmm14`); +0x34..+0x43 vec4=[r12+0x74] (`movups [rcx+0x20],xmm0` at 0x4c89430); +0x44..+0x53 constant vec4 from 0xF20A380 (`0x4c890df  movaps xmm12,[0xF20A380]` / `0x4c89434  movups [rbp+0x5AC],xmm12`); +0x54..+0x57 dword 1.0f (`0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000`). No instruction or string names any block/+0x50 field; settings fields r12+0x74/+0x84/+0x8C/+0x90 are unnamed. Description type = gamecomponents::EditorHighlightConfiguration (BGFX_MAP 6ih). producer_fields.txt EditorHighlight section confirms store offsets/sizes (+0x010 dword, +0x020 dword, +0x030 dword, +0x044 16-byte, +0x054 dword), writers=1 each, no field names.

## Value map

[V live] bytes: `python tools/sigs/livemem.py read @0xF20A380 16` -> `00007FF7B4BCA380  8f c2 f5 3d 00 00 80 3f 00 00 80 3f 00 00 00 3e` => +0x44=0.0913f, +0x48=1.0f, +0x4C=1.0f, +0x50..+0x53=0.25f (0x3E000000), +0x54..+0x57=1.0f. Byte values only; no semantic name. Producer stores the constant vec4 from 0xF20A380 at +0x44..+0x53 and 1.0f at +0x54..+0x57, so +0x50..+0x53's 0.25f comes from the constant table, not per-instance data. livemem cannot target the desc object itself: it is stack-transient at [rbp+0x568], handed via rdx; no static address exists; range-scan is forbidden.

## CLOSES?

NO — single blocking fact remains: the semantic meanings/names of +0x10..+0x4F and +0x50 have no [V] proof. All five rows are access/value facts ([V]; +0x50 constant bytes [V live]) with meaning '-'. No instruction or string names any block/+0x50 field, and the block is never consumed as interpreted data (only verbatim-moved; sub_66b2b30 never touches +0x10..+0x57 for tag 8; producer settings fields unnamed). The live capture er5_clone_4c8a5b0 can at best confirm field sizes/values at call time ([V live]) — it cannot supply semantic names because none exist statically; names would require a symbol/type source outside the exe.

## New angles tried this session (failed / unavailable)

- `python tools/livecap/request.py result er5_clone_4c8a5b0` -> "no result yet (orchestrator has not run it)"; docs/data/live/er5_clone_4c8a5b0.txt absent; re-add blocked (4 pending = limit: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc).
- producer_fields.txt EditorHighlight section read fully: store offsets/sizes only, no field names (writers=1 each).
- docs/functions/0x4c8a5b0.md and 0x666aca0.md read: clone only forwards {desc, tag}; tag-8 case appends verbatim 0x58-byte element; no block interpretation in either dossier.
- BGFX_MAP.md 6ih line 1854: RenderEditorHighlightDescription (0x58) in Descriptions.h, static_asserts, Release build OK; meaning of block and +0x50 explicitly [?].
- Post-drain call 0xE935700 disassembled: C++ EH/frame machinery, not a block consumer [V] (above).
- livemem inapplicable (no static address of live EditorHighlight desc object; stack-transient; range-scan forbidden; values cannot give names).
- Static angles exhausted previously: rdis imm/xr/callers ~0x5ABA5C0; ripscan 0x9D0 = 0 hits; rdis str 'EditorHighlight'; descscan2; vt/vcalls; sub_66b2b30 (tag-7 path only); sibling cross-checks oc_U-D9c2/oc_U-EL4w.

## TOOL REQUESTS

CAPTURE REQUESTED er5_clone_4c8a5b0 — already pending in docs/progress/capture_requests.json (rva 0x4C8A5B0 = 80258480, size 0x100 (filed as 256), max 6, queued 2026-11-22); `add` returns "already queued"; result file docs/data/live/er5_clone_4c8a5b0.txt absent, awaiting orchestrator batch run. [V live] bytes confirmed: `python tools/sigs/livemem.py read @0xF20A380 16`. No helper scripts written this unit; every quoted `0xRVA  instr` line re-verified verbatim against the exe with `rdis dis` this session (ranges 0x666b580, 0x666cc40, 0x666cd00, 0x666cdd0, 0x666ce10, 0x666b310, 0x666b3c0, 0x666aea0, 0x66b2b50, 0x4c890c0, 0x4c893c0, 0x4c89470, 0xE935700). No other file created for this unit.
