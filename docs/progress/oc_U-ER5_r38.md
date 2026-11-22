## NEXT
DONE

# Unit U-ER5 / R5 EditorHighlight — description record (+0x10..+0x50)

GOAL: decode semantics of the description's 64-byte block (+0x10..+0x4F) and +0x50 for effect tag 8 (EditorHighlight), read by clone 0x4c8a5b0, produced by 0x4c88900, handled in fn 0x666aca0.

SOURCES (read, not re-run): docs/data/listings/effect_visitor_666aca0_667191c.txt, lightgame_edhighlight_producer_4c88900_4c89881.txt, lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt.

CONVENTION: [V] = instruction seen verbatim in the listing/exe; [V live] = live value from tools/sigs/livemem.py. Meaning '-' = no instruction or string names this field. Block bytes are only ever copied verbatim (no math, no compares, no string references anywhere in fn 0x666aca0).

## Answer table (pending part: field meanings of the 64-byte block +0x10..+0x50)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
| +0x10 | 16 | desc+0x10 read by insert copy into element+0x10, fn 0x666aca0 tag-8 case | `0x666b594  movups xmm0,[rbx+0x10]` `0x666b5a4  movups [r15+0x10],xmm0` | - | [V] |
| +0x20 | 16 | desc+0x20 read → element+0x20 | `0x666b598  movups xmm1,[rbx+0x20]` `0x666b5a9  movups [r15+0x20],xmm1` | - | [V] |
| +0x30 | 16 | desc+0x30 read → element+0x30 | `0x666b59c  movups xmm2,[rbx+0x30]` `0x666b5ae  movups [r15+0x30],xmm2` | - | [V] |
| +0x40 | 16 | desc+0x40 read → element+0x40 | `0x666b5a0  movups xmm3,[rbx+0x40]` `0x666b5b3  movups [r15+0x40],xmm3` | - | [V] |
| +0x50 | 8 | desc+0x50 read → element+0x50 (insert copy); also read r15+0x50 → rcx+0x50 in second drain loop | `0x666b5b8  mov rax,[rbx+0x50]` `0x666b5bc  mov [r15+0x50],rax` `0x666cd02  mov rdx,[r15+0x50]` `0x666cd06  mov [rcx+0x50],rdx` | - | [V] |

## Queue/pass context (proven [V], not redone)

pass+0x78 = queue begin, +0x80 = end, +0x88 = cap, element stride 0x58. Per-EditorHighlight-insert end advance: add qword ptr [rsi+0x80],0x58 at 0x666b5c0. Cap test cmp r15,[rsi+0x88] at 0x666b3ad; end load mov r15,[rsi+0x80] at 0x666b3a6. Pass allocates via mov ecx,0x9D0 at 0x666b319 / add rcx,[r12+0x10] at 0x666b31e / call 0x5ABA5C0 at 0x666b323 / mov rsi,rax at 0x666b328; tag-8 case at 0x666b316. Fast-path addref: lock inc dword ptr [rax+8] at 0x666b3cb (rax = desc+0x8 ctrl block).

Consumer: NO separate consuming pass exists — the drain/compactor is inside fn 0x666aca0 itself right after the insert cases. It walks the queue copying each 0x58-byte element verbatim (mov rcx,[rdi] / mov [rax],rcx at 0x666cc50/0x666cc53; movups xmm1..xmm4,[rdi+0x10..0x40] / movups [rax+0x10..0x40] at 0x666cc5e..0x666cc7a; mov rcx,[rdi+0x50] / mov [rax+0x50],rcx at 0x666cc7e/0x666cc82), then a second drain loop (mov rdx,[r15+0x50] / mov [rcx+0x50],rdx at 0x666cd02/0x666cd06), addref lock inc dword ptr [rcx+8] at 0x666cc9f, lock dec dword ptr [r15+0xC] at 0x666cdd8, call 0xE935700 at 0x666ce27, reset begin/end/cap via mov [rsi+0x78],r14 / mov [rsi+0x80],rax / mov [rsi+0x88],r12 at 0x666ce2c/0x666ce3b/0x666ce45. Head parse feeds sub_66b2b30 via call 0x66B2B30 at 0x666aea7, which does mov rcx,[rdx] at 0x66b2b5b / mov rdx,[rcx+0x40] at 0x66b2b5e — the renderer consumes the shared config OBJECT (element+0x00 → object+0x40), NEVER block +0x10..+0x57.

## Producer (proven [V], not redone)

0x4c88900 builds the record at [rbp+0x568] and hands it to clone 0x4c8a5b0 (call 0x4C8A5B0 at 0x4c89478, rdx=desc): shared_ref ctor call 0x4DFB570 at 0x4c893d9 (rdx=r12 settings object); lea rcx,[rbp+0x568] at 0x4c893cf; +0x10 dword 1 (mov dword ptr [rbp+0x578],1 at 0x4c893df); +0x14=[r12+0x84] (mov [rcx],rax at 0x4c89400); +0x1C=[r12+0x8C] (mov [rcx+8],eax at 0x4c893f6); +0x20 f32=[r12+0x90] (movss [rbp+0x588],xmm14 at 0x4c89403); +0x24/+0x2C dup of +0x14/+0x1C (mov [rcx+0x10],rax at 0x4c8941c / mov [rcx+0x18],eax at 0x4c89412); +0x30 f32=[r12+0x90] (movss [rbp+0x598],xmm14 at 0x4c89420); +0x34..+0x43 vec4=[r12+0x74] (movups [rcx+0x20],xmm0 at 0x4c89430); +0x44..+0x53 constant vec4 from 0xF20A380 (movaps xmm12,[0xF20A380] at 0x4c890df / movups [rbp+0x5AC],xmm12 at 0x4c89434); +0x54..+0x57 dword 1.0f (mov dword ptr [rbp+0x5BC],0x3F800000 at 0x4c8943c). No instruction or string names any block/+0x50 field; settings fields r12+0x74/+0x84/+0x8C/+0x90 are unnamed. Description type = gamecomponents::EditorHighlightConfiguration (BGFX_MAP 6ih).

## Value map ([V live])

python tools/sigs/livemem.py read @0xF20A380 16 -> 00007FF7B4BCA380  8f c2 f5 3d 00 00 80 3f 00 00 80 3f 00 00 00 3e
=> +0x44=0.0913f, +0x48=1.0f, +0x4C=1.0f, +0x50..+0x53=0.25f (0x3E000000), +0x54..+0x57=1.0f.
Byte values only: no semantic name. Producer stores the constant vec4 from 0xF20A380 at +0x44..+0x53 and 1.0f at +0x54..+0x57, so +0x50..+0x53's 0.25f comes from the constant table, not per-instance data. livemem cannot target the desc object itself: it is stack-transient at [rbp+0x568], handed via rdx; no static address exists; range-scan is forbidden.

## CLOSES?

NO — single blocking fact remains: semantic meanings/names of +0x10..+0x4F and +0x50 have no [V] proof. All block reads are verbatim copies; sub_66b2b30 never touches +0x10..+0x57; producer settings fields are unnamed; no instruction or string names any block/+0x50 field.

## New angles tried this session (failed / unavailable)

- python tools/livecap/request.py result er5_clone_4c8a5b0 -> 'no result yet (orchestrator has not run it)'; docs/data/live/er5_clone_4c8a5b0.txt absent; add blocked (already queued; 4 pending = limit, cannot re-add).
- docs/data/live/effect_visitor.txt: 10 samples, tags {1,2,3,4} only — ZERO tag-8 samples; editor_visitor.txt empty; older dumps live_desc_item_ui_editor_sky2_1.26.62.01.txt and live_item_payloads_1.26.62.01.txt empty/absent.
- livemem inapplicable (no static address of live EditorHighlight desc object; stack-transient; range-scan forbidden; values cannot give names).
- Static angles exhausted: rdis imm/xr/callers ~0x5ABA5C0; ripscan 0x9D0 = 0 hits; rdis str 'EditorHighlight' (pass/scene name strings only); descscan2; vt/vcalls; endFrame 0x66232b0; ScreenDraw 0xbc04dc0; rendergraph builder 0xbb84ee0; sub_66a6830; ripscan sub_66b2b30 (9 call sites, none interprets block); sibling cross-checks oc_U-D9c2/oc_U-EL4w.

## TOOL REQUESTS (unblock)

- Orchestrator must run capture er5_clone_4c8a5b0 so docs/data/live/er5_clone_4c8a5b0.txt exists (clone-entry block bytes +0x10..+0x57, sizes/values only [V live]; names cannot come from bytes).
