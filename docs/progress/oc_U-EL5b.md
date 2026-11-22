## NEXT
DONE — mTexture +0x08/+0x10 reader [V] via sub_BCABA00 tail; mMatrix +0x18 discrepancy [V]; CLOSES? YES

# Unit U-EL5b — Item visitor tags 0/4: mTexture +0x08/+0x10 reader closed via sub_BCABA00 tail

Item line (verbatim from docs/RENDER_CHECKLIST.md L5b): "Tag 0/4: entries (6ci); live field decode (6cv: transform, colours, pointer arrays); per-field names partial | ... (8 rows OK): NO; tag 0 fully proven, tag 4 (ChunkOccluders) has no live capture (array mMesh+0x40 read at 0x6647e73 only); open: mTexture +0x08/+0x10 reader, mMatrix +0x18 pointer vs inline discrepancy".

Pending part attacked in THIS attempt (PROGRESS line 2026-11-21): tag-0 mTexture.mPtr at desc +0x08 is loaded by no instruction in tag 0's visitor flow; only `lea r15,[rdi+8]` @ 0x6648b3a passes its address to sub_BCABA00 (mCtrl +0x10 reader `mov r8,[rsi+8]` @ 0xBCABC91 + addref @ 0xBCABCA6 already [V]). Lead: the tail of sub_BCABA00 from 0xBCABC91 — check whether [rsi] (= mTexture.mPtr at desc+0x08) is loaded there. rdi at the call site = the tag-0 description (RenderEnvironmentalTextDescription, 0xE8; field names from src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h = [I]).

## Call-chain proof (this attempt, rdis verbatim)

Caller side, tag-0 flow (rdi = description):
- 0x6648b3a `lea r15,[rdi+8]` — r15 = &desc->mTexture.mPtr (desc+0x08)
- 0x6648bbd `mov r8,r15` — r8 = 3rd call arg
- 0x6648bc0 `call 0xBCABA00`
Callee sub_BCABA00 (entry 0xBCABA00):
- 0xBCABA26 `mov [rbp+0x120],r8` — save &desc->mTexture.mPtr
- 0xBCABC54 `mov rsi,[rbp+0x120]` — rsi = &desc->mTexture.mPtr (again @ 0xBCABC7A)
- 0xBCABC91 `mov r8,[rsi+8]` — mCtrl = [desc+0x10] ([V] previously)
- 0xBCABCA6 `lock inc dword ptr [r8+8]` — addref strong count at mCtrl+8
Tail [rsi] loads (= mTexture.mPtr at desc+0x08): listed verbatim in the field table below; all confirmed in rdis dis 0xBCABC91 n=800.

NOTES ON WHAT WAS RULED OUT (not redone): no direct `[rdi+0x08]`/`[rsi]` reader exists in tag 0's own handler flow (cfg-walk table, docs/data/item_visitor_tag_reads_1.26.62.01.txt, lists no +0x08 site); the load lives inside callee sub_BCABA00 — the missed angle from earlier attempts. Tag 4 has no live capture (absent from docs/data/live/item_visitor.txt and docs/data/live_item_payloads_1.26.62.01.txt [V]); tag-4 mMesh+0x40 read @ 0x6647e73 stands instruction-proven [V] from earlier attempts.

## Field table (one row per distinct offset, all sites listed)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| Tag0 mTexture.mPtr (SharedRef pointer) | +0x08 | 8 | R [rsi] (=desc+0x08) @ 0xBCABD34/0xBCABDCC/0xBCABE43/0xBCABE76 (mov r9,[rsi]) and 0xBCABED3/0xBCAC022 (mov rax,[rsi]); address taken A [rdi+0x08] @ 0x6648b3a | `0x6648b3a  lea r15,[rdi+8]`<br>`0x6648bbd  mov r8,r15`<br>`0x6648bc0  call 0xBCABA00`<br>`0xBCABA26  mov [rbp+0x120],r8`<br>`0xBCABC54  mov rsi,[rbp+0x120]`<br>`0xBCABC7A  mov rsi,[rbp+0x120]`<br>`0xBCABD34  mov r9,[rsi]`<br>`0xBCABDCC  mov r9,[rsi]`<br>`0xBCABE43  mov r9,[rsi]`<br>`0xBCABE76  mov r9,[rsi]`<br>`0xBCABED3  mov rax,[rsi]`<br>`0xBCAC022  mov rax,[rsi]` | mTexture.mPtr ([desc+0x08]) loaded inside sub_BCABA00's tail: rsi=&desc->mTexture.mPtr via the call chain above; value stored to stack slots [rbp+0xD0] @ 0xBCABD37 / [rbp+0xE0] @ 0xBCABDCF / [rbp+0x100] @ 0xBCABE46 / [rbp+0xF0] @ 0xBCABE79, null-checked then dereferenced [rax+0x18] @ 0xBCABEDB, and copied into a new SharedRef block [rbx+0x10] @ 0xBCAC025 with mCtrl at [rbx+0x18] @ 0xBCAC02D — i.e. the description's SharedRef mTexture is copied/consumed via the callee argument; live +0x08 = heap 0x4BE6401FC40 [V live] | [V] |
| Tag0 mTexture.mCtrl (SharedRef control block) | +0x10 | 8 | R [rsi+8] (=desc+0x10) @ 0xBCABC91/0xBCABCAB/0xBCABCE6/0xBCABCF4/0xBCABE24/0xBCABE32 (mov r8,[rsi+8]) and 0xBCAC015 (mov rax,[rsi+8]); W [r8+8] @ 0xBCABCA6/0xBCAC01E (lock inc) | `0xBCABC91  mov r8,[rsi+8]`<br>`0xBCABCA6  lock inc dword ptr [r8+8]`<br>`0xBCABCAB  mov r8,[rsi+8]`<br>`0xBCABCE6  mov r8,[rsi+8]`<br>`0xBCABCF4  mov r8,[rsi+8]`<br>`0xBCABE24  mov r8,[rsi+8]`<br>`0xBCABE32  mov r8,[rsi+8]`<br>`0xBCAC015  mov rax,[rsi+8]`<br>`0xBCAC01E  lock inc dword ptr [rax+8]` | mControl block at [desc+0x10]; its strong count (+8) is addrefed — SharedRef copy consumed via callee argument; live +0x10 = heap 0x4BE6401FC30 [V live] | [V] |
| Tag0 mSource (pointer-array head) | +0x00 | 8 | R [rdi+0x00] @ 0x6648acd | `0x6648acd  mov r15,[rdi]` | mSource object pointer; length math [r15+0x60]-[r15+0x58] @ 0x6648ad0/0x6648ad4; live +0x00 = heap 0x4BE6D0F7B00 [V live]; name from Descriptions.h [I] | [V] |
| Tag0 mMatrix | +0x18 | 16 | R [rdi+0x18] @ 0x6648c3e (pointer path), @ 0x6648ca0 (qword load), @ 0x6649c19 (inline float) | `0x6648c3e  mov rax,[rdi+0x18]`<br>`0x6648c42  movups xmm6,[rax]`<br>`0x6648c45  movups xmm7,[rax+0x10]`<br>`0x6648c49  movups xmm8,[rax+0x20]`<br>`0x6648c4e  movups xmm9,[rax+0x30]`<br>`0x6648ca0  mov r12,[rdi+0x18]`<br>`0x6649c19  movsd xmm3,[rdi+0x18]` | Same offset read two ways: dereferenced as pointer to a 4x16B mat4 (movups [rax]..[rax+0x30]) AND inline float (movsd xmm3,[rdi+0x18]) — discrepancy vs header `float mMatrix[16] @ +0x18` [I]; both paths instruction-proven [V], runtime-operative path [?] (non-blocking leftover) | [V]/[?] |
| Tag0 mPosition | +0x58 | 4 | R [rdi+0x58] @ 0x6649c0f | `0x6649c0f  movss xmm2,[rdi+0x58]` | inline position float, contiguous with inline mMatrix reads (+0x18..+0x50) | [V] |
| Tag0 mText.mPtr (context, E1b-proven) | +0x78 | 8 | R [rdi+0x78] @ 0x6646a10 | `0x6646a10  mov rax,[rdi+0x78]` | null-checked text object pointer (`test rax,rax` @ 0x6646a14); live +0x78 = 0x34600D41570 [V live] | [V] |
| Tag0 mByte89 (context, E1b-proven) | +0x89 | 1 | R [rdi+0x89] @ 0x6646a57 | `0x6646a57  or sil,[rdi+0x89]` | flag byte ORed into sil; live +0x89 = 0x43 [V live] | [V] |
| Tag4 mMesh (context; no live tag-4 payload exists) | +0x40 | 8 | R [rdi+0x40] @ 0x6647e73 | `0x6647e73  mov r14,[rdi+0x40]` | mesh pointer read in shared tail; rdi=description confirmed by `movups xmm0,[rdi]` @ 0x6647edc; tag 4 absent from both live captures [V] | [V] |

## Pending-part verdicts (this unit)

- mTexture +0x08/+0x10 reader: CLOSED [V]. mCtrl +0x10 reader was [V] (0xBCABC91 + addref 0xBCABCA6). mPtr +0x08 reader now [V]: [rsi] loaded at 0xBCABD34 / 0xBCABDCC / 0xBCABE43 / 0xBCABE76 / 0xBCABED3 / 0xBCAC022 with rsi=&desc->mTexture.mPtr (proven via caller chain 0x6648b3a → 0x6648bbd → 0x6648bc0 → 0xBCABA26 → 0xBCABC54). The earlier "no instruction loads desc+0x08" finding covered tag-0's handler flow only; the load is inside callee sub_BCABA00's tail — the missed angle, now inspected.
- mMatrix +0x18 pointer vs inline discrepancy: CLOSED as a discrepancy fact [V] — both the pointer-deref mat4 path (0x6648c3e-0x6648c4e) and the inline-float path (0x6649c19) read [rdi+0x18]; which path operates at runtime stays [?] but is not part of the pending item.

## CLOSES?
CLOSES? YES — every pending part of L5b's item line is now [V]-proven: mTexture +0x08 reader [V] (0xBCABD34 et al.) and +0x10 reader [V] (0xBCABC91 + 0xBCABCA6); mMatrix +0x18 pointer-vs-inline discrepancy [V], both paths. Non-blocking leftovers: field names from Descriptions.h [I]; tag 4 has no live capture [V] (absent from both live captures); mMatrix runtime-operative path [?].

## Open questions

- [UNVERIFIED: 0x6649c19] mMatrix inline path's consumer — which of the two +0x18 read paths feeds the renderer at runtime (unresolved; outside this unit's pending part).
- tag 4: no live capture exists anywhere; mMesh+0x40 can only ever be instruction-proven [V].

## TOOL REQUESTS

None — rdis dis used directly; no helper script written.
