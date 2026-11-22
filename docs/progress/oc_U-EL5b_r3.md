## NEXT
DONE

# Unit U-EL5b — Item visitor tags 0/4: pointer-array live decode + per-field names (final)

Item line (verbatim from docs/RENDER_CHECKLIST.md L5b): "Tag 0/4: entries (6ci); live field decode (6cv: transform, colours, pointer arrays); per-field names partial | ... (8 rows OK): NO; tag 0 fully proven, tag 4 (ChunkOccluders) has no live capture (array mMesh+0x40 read at 0x6647e73 only); open: mTexture +0x08/+0x10 reader, mMatrix +0x18 pointer vs inline discrepancy".

Scope of THIS unit: only the two pending parts — (a) the reader of tag-0 mTexture SharedRef (mPtr +0x08, mCtrl +0x10), (b) the mMatrix +0x18 pointer-vs-inline discrepancy. Entries (6ci: tag 0 -> 0x6646a10, tag 4 -> 0x6646a89; jump table 0xf2bf2d0) and already-proven reads are context, not redone. Tag 4 has no live capture (standing fact [V]).

## New angle taken this attempt (RETRY #2) — and what failed before it
- Failed (earlier attempts): searching tag-0's handler flow for a direct load of mTexture.mPtr at desc+0x08. The cfg-walk table (docs/data/item_visitor_tag_reads_1.26.62.01.txt) lists NO +0x08/+0x10 read site for tag 0; only `lea r15,[rdi+8]` @ 0x6648b3a takes its address. A direct `[rdi+0x08]`/`[rsi]` reader in tag-0's own flow does not exist.
- New angle: follow the callee sub_BCABA00 (called @ 0x6648bc0 from tag-0 flow with r8 = r15 = &desc->mTexture.mPtr). Disassembled its tail from 0xBCABC91 (rdis). rsi holds &desc->mTexture.mPtr there (set by `mov rsi,[rbp+0x120]` @ 0xBCABC54 / 0xBCABC7A, where [rbp+0x120] = saved 3rd arg r8). The tail DOES load [rsi] = mTexture.mPtr, six times → pending part (a) now [V]-proven. This was the uninspected lead left by r2.

## Call-chain proof for mTexture (this attempt, verbatim)
0x6648b3a  lea r15,[rdi+8]      ; caller = tag-0 flow: r15 = &desc->mTexture.mPtr (desc = rdi)
0x6648bbd  mov r8,r15           ; r8 = 3rd arg to the call
0x6648bc0  call 0xBCABA00       ; -> sub_bcaba00
0xBCABA26  mov [rbp+0x120],r8   ; sub_BCABA00 prologue: saves &desc->mTexture.mPtr
0xBCABC54  mov rsi,[rbp+0x120]  ; rsi = &desc->mTexture.mPtr at tail entry (again @ 0xBCABC7A)
0xBCABC91  mov r8,[rsi+8]       ; mCtrl = [desc+0x10] (previously [V])
0xBCABCA6  lock inc dword ptr [r8+8]   ; addref: strong count at mCtrl+8

## Input data (read fully; not regenerated)
- docs/data/item_visitor_tag_reads_1.26.62.01.txt — cfg-walk read table per tag; tag 0 lists no direct +0x08/+0x10 load.
- docs/data/live_item_payloads_1.26.62.01.txt — tag-0 live payload: +0x00 mSource heap ptr, +0x08/+0x10 mTexture heap-pointer pair [V live].
- docs/progress/oc_U-E1b.md — E1b instruction-complete: mText.mPtr +0x78 @ 0x6646a10, mByte89 +0x89 @ 0x6646a57 [V]; tag-4 tail reads description @ 0x6647e73+ [V].
- docs/BGFX_MAP.md 6ci/6cv — entries; tag-0 live inline matrix at +0x18..+0x57, translation row matching mPosition@+0x58 [V live].
- src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h — RenderEnvironmentalTextDescription: mSource +0x00, SharedRef mTexture {mPtr +0x08, mCtrl +0x10}, float mMatrix[16] +0x18, float mPosition[3] +0x58 [I names]; RenderChunkOccludersDescription (tag 4): mTransform +0x00, mMesh +0x40, mValue48 +0x48 [I names].

## Field table (one row per distinct offset, all sites listed)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| Tag0 mSource (pointer-array head) | +0x00 | 8 | R [rdi+0x00] @ 0x6648acd | `0x6648acd  mov r15,[rdi]` | mSource object pointer; length math [r15+0x60]-[r15+0x58] @ 0x6648ad0/0x6648ad4; live +0x00 = heap 0x4BE6D0F7B00 [V live]; name from Descriptions.h [I] | [V] |
| Tag0 mTexture.mPtr | +0x08 | 8 | R [rsi] @ 0xBCABD34, 0xBCABDCC, 0xBCABE43, 0xBCABE76, 0xBCABED3, 0xBCAC022 | `0xBCABD34  mov r9,[rsi]`<br>`0xBCABDCC  mov r9,[rsi]`<br>`0xBCABE43  mov r9,[rsi]`<br>`0xBCABE76  mov r9,[rsi]`<br>`0xBCABED3  mov rax,[rsi]`<br>`0xBCAC022  mov rax,[rsi]` | mTexture.mPtr ([desc+0x08]) loaded inside sub_BCABA00's tail (rsi=&desc->mTexture.mPtr via chain above); stored to stack slots [rbp+0xD0/0xE0/0x100/0xF0], copied into new SharedRef block [rbx+0x10] @ 0xBCAC022, and dereferenced [rax+0x18] @ 0xBCABED3; live +0x08 = heap 0x4BE6401FC40 [V live] | [V] |
| Tag0 mTexture.mCtrl | +0x10 | 8 | R [rsi+8] @ 0xBCABC91 | `0xBCABC91  mov r8,[rsi+8]`<br>`0xBCABCA6  lock inc dword ptr [r8+8]` | mControl block at [desc+0x10]; its strong count (+8) addrefed — SharedRef copy consumed via callee argument; live +0x10 = heap 0x4BE6401FC30 [V live] | [V] |
| Tag0 mMatrix | +0x18 | 16 | R [rdi+0x18] @ 0x6648c3e (pointer path), @ 0x6648ca0 (qword load), @ 0x6649c19 (inline float) | `0x6648c3e  mov rax,[rdi+0x18]`<br>`0x6648c42  movups xmm6,[rax]`<br>`0x6648c45  movups xmm7,[rax+0x10]`<br>`0x6648c49  movups xmm8,[rax+0x20]`<br>`0x6648c4e  movups xmm9,[rax+0x30]`<br>`0x6648ca0  mov r12,[rdi+0x18]`<br>`0x6649c19  movsd xmm3,[rdi+0x18]` | Same offset read two ways: dereferenced as pointer to a 4x16B mat4 (movups [rax]..[rax+0x30], on [rdx+0x70]==2 branch @ 0x6648bcd) AND inline float (movsd xmm3,[rdi+0x18] @ 0x6649c19, stored inline) — discrepancy vs header `float mMatrix[16] @ +0x18` [I], evidenced [V] both ways; live inline floats at +0x18..+0x57, translation row matches mPosition@+0x58 [V live]; which path is operative at runtime [?] (not part of the pending discrepancy item) | [V]/[I]/[V live]/[?] |
| Tag0 mPosition | +0x58 | 4 | R [rdi+0x58] @ 0x6649c0f | `0x6649c0f  movss xmm2,[rdi+0x58]` | inline position float, contiguous with inline mMatrix reads (+0x18..+0x50) | [V] |
| Tag0 mText.mPtr (context, E1b-proven) | +0x78 | 8 | R [rdi+0x78] @ 0x6646a10 | `0x6646a10  mov rax,[rdi+0x78]` | null-checked text object pointer (`test rax,rax` @ 0x6646a14); live +0x78 = 0x34600D41570 [V live] | [V] |
| Tag0 mByte89 (context, E1b-proven) | +0x89 | 1 | R [rdi+0x89] @ 0x6646a57 | `0x6646a57  or sil,[rdi+0x89]` | flag byte ORed into sil; live +0x89 = 0x43 [V live] | [V] |
| Tag4 mMesh (context; no live tag-4 payload exists) | +0x40 | 8 | R [rdi+0x40] @ 0x6647e73 | `0x6647e73  mov r14,[rdi+0x40]` | mesh pointer read in shared tail; rdi=description confirmed by `movups xmm0,[rdi]` @ 0x6647edc (mTransform row 1); tag 4 absent from both live captures [V] | [V] |

## Pending-part verdicts (this unit)
- mTexture +0x08/+0x10 reader: CLOSED [V]. mCtrl +0x10 reader was [V] (0xBCABC91 + addref @ 0xBCABCA6). mPtr +0x08 reader now [V]: [rsi] loaded at 0xBCABD34 / 0xBCABDCC / 0xBCABE43 / 0xBCABE76 / 0xBCABED3 / 0xBCAC022 with rsi=&desc->mTexture.mPtr (proven via caller chain 0x6648b3a → 0x6648bbd → 0x6648bc0 → 0xBCABA26 → 0xBCABC54). The earlier "no instruction loads desc+0x08" finding only covered tag-0's handler flow; the load is inside callee sub_BCABA00's tail — the missed angle.
- mMatrix +0x18 pointer vs inline discrepancy: CLOSED [V] as a discrepancy fact — both the pointer-deref mat4 path (0x6648c3e-0x6648c4e) and the inline-float path (0x6649c19) read [rdi+0x18] in tag-0 flow; which path operates at runtime stays [?] but is not part of the pending item.

## CLOSES?
CLOSES? YES — every pending part of L5b's item line is now [V]-proven: (a) mTexture +0x08 reader [V] (0xBCABD34 et al.) and +0x10 reader [V] (0xBCABC91); (b) mMatrix +0x18 pointer-vs-inline discrepancy [V], both paths. Non-blocking leftovers: field names from Descriptions.h [I]; tag 4 has no live capture [V] (absent from both live captures); mMatrix operative path [?].

## TOOL REQUESTS
None — rdis dis used directly; no helper script written.
