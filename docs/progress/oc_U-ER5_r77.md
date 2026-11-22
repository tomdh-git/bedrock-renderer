## NEXT
DONE

# Unit U-ER5 / R5 EditorHighlight (Effect tag 8) — meanings of the 64-byte block (+0x10..+0x4F) and +0x50

GOAL: close checklist item R5 — semantic meanings/names of the description's 64-byte block (+0x10..+0x4F) and +0x50 (Effect tag 8, clone 0x4c8a5b0, producer 0x4c88900, handler fn 0x666aca0). The pass+0x80 queue consumer is already [V]-proven inside fn 0x666aca0 itself (drain/compactor) per oc_U-ER5_r31..r38 — NOT redone.

SOURCES (read, not re-run): docs/data/listings/effect_visitor_666aca0_667191c.txt, lightgame_edhighlight_producer_4c88900_4c89881.txt, lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt.

CONVENTION: [V] = instruction seen verbatim in the listing/exe (cite RVA); [V live] = live value from tools/sigs/livemem.py; [I] = inferred; [?] = unknown. Meaning column '-' unless an instruction or a string names the field. No sizes, offsets or names written unless seen. Sizes: movups/movaps = 16, qword = 8, dword/movss = 4.

## New angles tried this session (failed or blocked)

- python tools/livecap/request.py result er5_clone_4c8a5b0 -> 'no result yet (orchestrator has not run it)'; docs/data/live/er5_clone_4c8a5b0.txt does not exist.
- docs/progress/capture_requests.json: er5_clone_4c8a5b0 state=pending (rva 0x4C8A5B0 = 80258480, size 256, max 6, why 'R5: clone entry, rdx = desc ptr: 64-byte block (+0x10..+0x4F) and +0x50 values', queued 2026-11-22). Four captures are pending (er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc) = at the 4-pending limit; `add` returns 'already queued' (exit 1), so it cannot be re-added here.
- livemem inapplicable: the desc object is stack-transient at [rbp+0x568] inside clone 0x4c8a5b0 and handed to it via rdx; no static address exists for a livemem read, range-scan is forbidden, and byte values cannot supply semantic names anyway.
- Static angles exhausted per the 2026-11-22 review (61/61, CLOSES NO): rdis imm/xr/callers around 0x5ABA5C0; ripscan 0x9D0 = 0 hits; rdis str 'EditorHighlight' (pass/scene-name strings only); descscan2; vt/vcalls; endFrame 0x66232b0; ScreenDraw 0xbc04dc0; rendergraph builder 0xbb84ee0; sub_66a6830; ripscan sub_66b2b30 (9 call sites, none interprets the block); sibling cross-checks oc_U-D9c2/oc_U-EL4w. No new static angle remains; nothing repeated here.

## Verbatim instruction proof (re-confirmed against the exe with rdis dis this session)

All quoted lines below match rdis output exactly (also enforced by tools/sigs/verify_oc.py).
Insert copy, tag-8 case inside fn 0x666aca0 (case head 0x666b316): `0x666b594  movups xmm0,[rbx+0x10]` `0x666b598  movups xmm1,[rbx+0x20]` `0x666b59c  movups xmm2,[rbx+0x30]` `0x666b5a0  movups xmm3,[rbx+0x40]` `0x666b5a4  movups [r15+0x10],xmm0` `0x666b5a9  movups [r15+0x20],xmm1` `0x666b5ae  movups [r15+0x30],xmm2` `0x666b5b3  movups [r15+0x40],xmm3` `0x666b5b8  mov rax,[rbx+0x50]` `0x666b5bc  mov [r15+0x50],rax`
Drain/compactor inside fn 0x666aca0 (first loop): `0x666cc5e  movups xmm1,[rdi+0x10]` `0x666cc62  movups xmm2,[rdi+0x20]` `0x666cc66  movups xmm3,[rdi+0x30]` `0x666cc6a  movups xmm4,[rdi+0x40]` `0x666cc6e  movups [rax+0x10],xmm1` `0x666cc72  movups [rax+0x20],xmm2` `0x666cc76  movups [rax+0x30],xmm3` `0x666cc7a  movups [rax+0x40],xmm4` `0x666cc7e  mov rcx,[rdi+0x50]` `0x666cc82  mov [rax+0x50],rcx`
Second drain loop: `0x666cd02  mov rdx,[r15+0x50]` `0x666cd06  mov [rcx+0x50],rdx`
Producer 0x4c88900 (record base rbp+0x568; clone entry 0x4c89478 `lea rdx,[rbp+0x568]` / `call 0x4C8A5B0`): `0x4c893df  mov dword ptr [rbp+0x578],1` (=desc+0x10) `0x4c89403  movss [rbp+0x588],xmm14` (=desc+0x20) `0x4c89420  movss [rbp+0x598],xmm14` (=desc+0x30) `0x4c890df  movaps xmm12,[0xF20A380]` then `0x4c89434  movups [rbp+0x5AC],xmm12` (=desc+0x44..+0x4F) `0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000` (=desc+0x54, 1.0f)

## Answer table: RenderEditorHighlightDescription block (+0x10..+0x4F = 64 bytes) and +0x50 (Effect tag 8)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| +0x10 | 16 | insert: desc read rbx+0x10 -> element [r15+0x10] (tag-8 case 0x666b316); drain: read [rdi+0x10] -> write [rax+0x10]; producer: dword 1 at [rbp+0x578] (record base rbp+0x568 = desc+0x00) | `0x666b594  movups xmm0,[rbx+0x10]` `0x666b5a4  movups [r15+0x10],xmm0` | '-': 16-byte chunk copied verbatim on insert and drain; producer stores dword 1; never read/interpreted by any consumer (sub_66b2b30 via call 0x66B2B30 at 0x666aea7 reads desc+0x00 -> object+0x40 only, never +0x10..+0x57); no instruction or string names the field | [V] |
| +0x20 | 16 | insert: read rbx+0x20 -> write [r15+0x20]; drain: read [rdi+0x20] -> write [rax+0x20]; producer: movss xmm14 at [rbp+0x588] (from unnamed settings field r12+0x90) at desc+0x20 | `0x666b598  movups xmm1,[rbx+0x20]` `0x666b5a9  movups [r15+0x20],xmm1` | '-': 16-byte chunk copied verbatim; producer value is an unnamed settings-object field; never interpreted by any consumer | [V] |
| +0x30 | 16 | insert: read rbx+0x30 -> write [r15+0x30]; drain: read [rdi+0x30] -> write [rax+0x30]; producer: movss xmm14 at [rbp+0x598] at desc+0x30; movups [rcx+0x20],xmm0 (vec4 from unnamed r12+0x74) at desc+0x34..+0x43 | `0x666b59c  movups xmm2,[rbx+0x30]` `0x666b5ae  movups [r15+0x30],xmm2` | '-': 16-byte chunk copied verbatim; producer values are unnamed settings-object fields; never interpreted by any consumer | [V] |
| +0x40 | 16 | insert: read rbx+0x40 -> write [r15+0x40]; drain: read [rdi+0x40] -> write [rax+0x40]; producer: movaps xmm12,[0xF20A380] then movups [rbp+0x5AC],xmm12 (constant vec4) at desc+0x44..+0x4F | `0x666b5a0  movups xmm3,[rbx+0x40]` `0x666b5b3  movups [r15+0x40],xmm3` | '-': 16-byte chunk copied verbatim; +0x44..+0x4F = tail of constant vec4 from read-only data [0xF20A380]; no semantic name | [V] |
| +0x50 | 8 | insert: read rbx+0x50 -> write [r15+0x50]; drain: read [rdi+0x50] -> write [rax+0x50]; second drain loop: read [r15+0x50] -> write [rcx+0x50]; producer: dword 0x3F800000 (1.0f) at [rbp+0x5BC] = desc+0x54 | `0x666b5b8  mov rax,[rbx+0x50]` `0x666b5bc  mov [r15+0x50],rax` `0x666cd02  mov rdx,[r15+0x50]` `0x666cd06  mov [rcx+0x50],rdx` | '-': qword chunk copied verbatim; +0x50..+0x53 = element 3 of constant vec4 [0xF20A380] = bytes 00 00 00 3e (0.25f) [V live]; +0x54..+0x57 = 1.0f; no semantic name | [V] |

## Queue context (proven [V], not redone)

pass+0x78 = queue begin, +0x80 = end (advanced per insert at `0x666b5c0  add qword ptr [rsi+0x80],0x58`), +0x88 = cap, element stride 0x58 (cap test `cmp r15,[rsi+0x88]` at 0x666b3ad; end load `mov r15,[rsi+0x80]` at 0x666b3a6; pass allocates `mov ecx,0x9D0` at 0x666b319 / `add rcx,[r12+0x10]` at 0x666b31e / `call 0x5ABA5C0` at 0x666b323 / `mov rsi,rax` at 0x666b328). The drain/compactor is inside fn 0x666aca0 itself right after the insert cases (copies each 0x58-byte element verbatim, `lock inc dword ptr [rcx+8]` at 0x666cc9f, `lock dec dword ptr [r15+0xC]` at 0x666cdd8, `call 0xE935700` at 0x666ce27, resets `mov [rsi+0x78],r14` / `mov [rsi+0x80],rax` / `mov [rsi+0x88],r12` at 0x666ce2c/0x666ce3b/0x666ce45). Head parse feeds sub_66b2b30 via `call 0x66B2B30` at 0x666aea7 (`mov rcx,[rdx]` at 0x66b2b5b / `mov rdx,[rcx+0x40]` at 0x66b2b5e): the renderer consumes the shared config object (element+0x00 -> object+0x40), NEVER block +0x10..+0x57. No separate consuming pass exists.

## Value map ([V live])

`python tools/sigs/livemem.py read @0xF20A380 16` -> `00007FF7B4BCA380  8f c2 f5 3d 00 00 80 3f 00 00 80 3f 00 00 00 3e`
=> +0x44=0.0913f, +0x48=1.0f, +0x4C=1.0f, +0x50..+0x53=0.25f (0x3E000000), +0x54..+0x57=1.0f (0x3F800000). Byte values only: no semantic name; the desc object itself is stack-transient (no static address) so livemem cannot target it.

## CLOSES?

CLOSES?: NO — single blocking fact: semantic meanings/names of +0x10..+0x4F and +0x50 have no [V] proof. All five rows are access/value facts ([V]; +0x50 constant bytes [V live]) with meaning '-'. Every block access is a verbatim copy; sub_66b2b30 never touches +0x10..+0x57; producer settings fields are unnamed; no instruction or string names any block/+0x50 field. Unblock path: the orchestrator must run the pending capture er5_clone_4c8a5b0 (clone entry 0x4C8A5B0, state pending, size 256, max 6, queued 2026-11-22) so docs/data/live/er5_clone_4c8a5b0.txt exists; live bytes can confirm field sizes/values at call time and the ret= caller chain, but cannot supply semantic names (none exist statically). Leave R5 for later.

## TOOL REQUESTS

CAPTURE REQUESTED er5_clone_4c8a5b0 — already pending in docs/progress/capture_requests.json (rva 0x4C8A5B0, size 256, max 6, queued 2026-11-22); `python tools/livecap/request.py result er5_clone_4c8a5b0` -> 'no result yet'; `add` blocked (4 pending = limit, 'already queued' exit 1). No helper scripts written this unit; every quoted `0xRVA  instr` line re-verified verbatim against the exe with rdis dis this session. No other file created for this unit.
