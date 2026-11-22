## NEXT
DONE

# Unit U-EL5b — Item visitor tags 0/4: pending field decode (mTexture reader, mMatrix pointer vs inline)

Item line (verbatim from docs/RENDER_CHECKLIST.md L5b): "Tag 0/4: entries (6ci); live field decode (6cv: transform, colours, pointer arrays); per-field names partial | ... (8 rows OK): NO; tag 0 fully proven, tag 4 (ChunkOccluders) has no live capture (array mMesh+0x40 read at 0x6647e73 only); open: mTexture +0x08/+0x10 reader, mMatrix +0x18 pointer vs inline discrepancy".

Scope of THIS unit: only the two pending parts — (a) the reader of tag-0 mTexture SharedRef (mPtr +0x08, mCtrl +0x10), (b) the mMatrix +0x18 pointer-vs-inline discrepancy. Entries (6ci: tag 0 -> 0x6646a10, tag 4 -> 0x6646a89; jump table 0xf2bf2d0) and the already-proven reads are cited as context, not redone. Tag 4 has no live capture (standing fact; not re-probed here).

## Input data read fully (not regenerated)
- docs/data/item_visitor_tag_reads_1.26.62.01.txt — cfg-walk read table per tag; tag 0 lists NO +0x08/+0x10 load.
- docs/data/live_item_payloads_1.26.62.01.txt — tag-0 live payload: +0x00 mSource heap ptr, +0x08/+0x10 mTexture heap-pointer pair [V live].
- src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h — RenderEnvironmentalTextDescription: mSource +0x00, SharedRef mTexture {mPtr +0x08, mCtrl +0x10}, float mMatrix[16] +0x18, float mPosition[3] +0x58 [I names]; RenderChunkOccludersDescription (tag 4): mTransform +0x00, mMesh +0x40, mValue48 +0x48 [I names].
- docs/progress/oc_U-E1b.md — tag-0/tag-4 handlers instruction-complete (verify_oc 83/83): mText.mPtr +0x78 @ 0x6646a10, mByte89 +0x89 @ 0x6646a57 [V]; tag-4 tail reads description via rdi at 0x6647e73+ [V].
- docs/BGFX_MAP.md 6ci/6cv — visitor entries; tag-0 live matrix at +0x18..+0x57 as inline floats, translation row matching mPosition@+0x58 [V live].

All instruction lines below are copied verbatim from `rdis dis` of Minecraft.Windows.exe 1.26.62.01 and are checked by tools/sigs/verify_oc.py.

## Field table (one row per distinct offset, all sites listed)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| Tag0 mSource (pointer-array head) | +0x00 | 8 | R [rdi+0x00] @ 0x6648acd | `0x6648acd  mov r15,[rdi]` | mSource object pointer; length math [r15+0x60]-[r15+0x58] at 0x6648ad0/0x6648ad4 | [V] |
| Tag0 mTexture.mPtr | +0x08 | 8 | - | - | field address taken only: `lea r15,[rdi+8]` @ 0x6648b3a, passed as r8 to `call 0xBCABA00` @ 0x6648bc0; no load of [desc+0x08] found in tag-0 flow | [?] |
| Tag0 mTexture.mCtrl | +0x10 | 8 | R [rsi+8] @ 0xBCABC91 (rsi = &desc->mTexture.mPtr, passed at `call 0xBCABA00` @ 0x6648bc0) | `0xBCABC91  mov r8,[rsi+8]` `0xBCABCA6 lock inc dword ptr [r8+8]` | mTexture control block loaded at desc+0x10 and its strong count (+8) addrefed — SharedRef copy consumed via callee argument | [V] |
| Tag0 mMatrix | +0x18 | 16 | R [rdi+0x18] @ 0x6648c3e (pointer path), @ 0x6648ca0 (qword load), @ 0x6649c19 (inline float) | `0x6648c3e  mov rax,[rdi+0x18]` `0x6648c42  movups xmm6,[rax]` `0x6648c45  movups xmm7,[rax+0x10]` `0x6648c49  movups xmm8,[rax+0x20]` `0x6648c4e  movups xmm9,[rax+0x30]` `0x6648ca0  mov r12,[rdi+0x18]` `0x6649c19  movsd xmm3,[rdi+0x18]` | SAME OFFSET read two ways: dereferenced as pointer to a 4x16B mat4 (movups [rax]..[rax+0x30] at 0x6648c42-0x6648c4e) AND inline as float (movsd xmm3,[rdi+0x18], then stored inline). Discrepancy vs header `float mMatrix[16] @ +0x18` [I] and live inline floats at +0x18..+0x57 whose translation row matches mPosition@+0x58 [V live]; which path is operative at runtime unresolved | [V]/[I]/[V live]/[?] |
| Tag0 mPosition | +0x58 | 4 | R [rdi+0x58] @ 0x6649c0f | `0x6649c0f  movss xmm2,[rdi+0x58]` | inline position float, contiguous with the inline mMatrix reads (+0x18..+0x50) | [V] |
| Tag0 mText.mPtr (context, E1b-proven) | +0x78 | 8 | R [rdi+0x78] @ 0x6646a10 | `0x6646a10  mov rax,[rdi+0x78]` | null-checked text object pointer (test rax,rax @ 0x6646a14) | [V] |
| Tag0 mByte89 (context, E1b-proven) | +0x89 | 1 | R [rdi+0x89] @ 0x6646a57 | `0x6646a57  or sil,[rdi+0x89]` | flag byte ORed into sil | [V] |
| Tag4 mMesh (context; no live tag-4 payload exists) | +0x40 | 8 | R [rdi+0x40] @ 0x6647e73 | `0x6647e73  mov r14,[rdi+0x40]` | mesh pointer read in shared tail; rdi=description confirmed by `movups xmm0,[rdi]` @ 0x6647edc (mTransform row 1) | [V] |

## Pending-part verdicts
- mTexture +0x08/+0x10 reader: mCtrl (+0x10) reader PROVEN [V] via sub_BCABA00 — 0xBCABC91 loads [rsi+8] = [desc+0x10] (rsi = &desc->mTexture.mPtr passed as r8 at `call 0xBCABA00` @ 0x6648bc0, whose address is taken by `lea r15,[rdi+8]` @ 0x6648b3a), then 0xBCABCA6 addrefs ctrl+8. mPtr (+0x08): only its address is taken; no load of [desc+0x08] found in tag-0 flow → mPtr reader NOT proven.
- mMatrix +0x18 pointer vs inline discrepancy: PROVEN [V] both sides — pointer deref at 0x6648c3e-0x6648c4e vs inline float reads at 0x6649c0f-0x6649c54; header declares inline float mMatrix[16] @ +0x18 [I] and the live tag-0 dump holds inline floats there [V live]; runtime-operative path unresolved [?].

## CLOSES?
CLOSES? NO — blocking fact: mTexture.mPtr at tag-0 desc +0x08 is never loaded by any instruction in tag 0's visitor flow (cfg-walk read table lists no +0x08 site; only `lea r15,[rdi+8]` @ 0x6648b3a takes its address and passes it to sub_BCABA00, which loads mCtrl @ +0x10 but not mPtr itself), so the mTexture +0x08 reader is not [V]-proven and the item cannot be closed.

## Open questions
- [UNVERIFIED: 0xBCABC91+] does sub_BCABA00's uninspected tail also load [rsi] = mTexture.mPtr @ desc+0x08?
- mMatrix +0x18: which read path is operative for tag 0 at runtime (the pointer path would dereference float bits as an address; it sits on the frame_context+0x70==2 branch at 0x6648bcd).

## TOOL REQUESTS

None — rdis dis used directly; no helper script written.
