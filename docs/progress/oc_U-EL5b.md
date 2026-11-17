## NEXT
DONE — pointer arrays + per-field names decoded for tags 0/4; CLOSES?=NO (tag 4 no live capture)

# Unit U-EL5b — Item visitor tags 0/4: pointer-array live decode + per-field names

Pending part of L5b line "Tag 0/4: entries (6ci); live field decode (6cv: transform, colours, pointer arrays); per-field names partial":
- entries (6ci: tag 0 -> 0x6646a10, tag 4 -> 0x6646a89) [V] — done, cited below.
- transform + colours (tag 0) [V] — done via 6cv/E1b, cited below.
- THIS UNIT: pointer arrays (tag 0 mSource/mTexture, tag 4 mMesh) + per-field names for tags 0/4.

## Decode basis (input data read fully; not regenerated)
- docs/data/item_visitor_tag_reads_1.26.62.01.txt — tag-0/tag-4 read offsets, widths, first sites (cfg-walk derived).
- docs/data/live/item_visitor.txt — visitor-entry description dumps; tags 10,6,7,0,1,3,2 seen; tag 4 ABSENT [V].
- docs/data/live_item_payloads_1.26.62.01.txt — handler-entry payload dumps (rdi); tag 0 rdi=149E40: +0x00 0x4BE6D0F7B00, +0x08 0x4BE6401FC40, +0x10 0x4BE6401FC30 (three heap pointers [V live]); tag 4 ABSENT [V].
- src header Descriptions.h — RenderEnvironmentalTextDescription (tag 0, 0xE8), RenderChunkOccludersDescription (tag 4, 0x50).
- rdis verbatim disassembly of exe 1.26.62.01 (see verification lines).

## Already proven (cited, not redone)
- Entries 6ci [V]: tag 0 handler 0x6646a10, tag 4 handler 0x6646a89 (disassembly matches E1b exactly).
- Tag 0 transform [6cv, V]: mMatrix 4x16 bytes at +0x18, mPosition vec3 at +0x58.
- Tag 0 colours [6cv, V]: mParamD8 block at +0x8C; mByte89 +0x89 via `or sil,[rdi+0x89]` @ 0x6646a57 [V]; live +0x89 = 0x43 [V live].
- Tag 0 mText.mPtr +0x78 via `mov rax,[rdi+0x78]` @ 0x6646a10 [V]; live +0x78 = 0x34600D41570 [V live].
- Tag 4 handler 0x6646a89 [V, E1b]: `mov rbx,[rbp+0x8A0]` (frame_context = [FrameBuilder+0xF0]), `mov rcx,[rbx+0x68]`, `mov r9,[rbx+0x40]`, `call 0x67D6D70`, `jmp 0x66477d8` — handler's own range reads frame_context, not the description.

## NEW DECODE — pointer arrays + per-field names (this unit)
Tag 0 (EnvironmentalText, payload = rdi): pointer array = mSource+0x00, mTexture.mPtr+0x08, mTexture.mCtrl+0x10. Tag 4 (ChunkOccluders): pointer field mMesh+0x40. rdi = the description at the read sites below (proven by the field pattern matching RenderChunkOccludersDescription: mat4 +0x00, pointer +0x40, u16 +0x48).

| name | size | rva or offset | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|---|
| Tag0 mSource (pointer) | 8 | +0x00 (tag 0) | R [rdi+0x00] @ 0x6648acd | `0x6648acd  mov r15,[rdi]` | qword load of description+0x00 into r15; r15+0x60/0x58 length math at 0x6648ad0 → source-object pointer; live +0x00 = heap 0x4BE6D0F7B00 [V live]; name mSource from header [I] | [V] |
| Tag0 mTexture.mPtr (pointer) | 8 | +0x08 (tag 0) | - | - | - | [I] |
| Tag0 mTexture.mCtrl (pointer) | 8 | +0x10 (tag 0) | - | - | - | [I] |
| Tag0 mText.mPtr | 8 | +0x78 (tag 0) | R [rdi+0x78] @ 0x6646a10 | `0x6646a10  mov rax,[rdi+0x78]` | null-checked (test rax,rax; je 0x664EBD7); live +0x78 = 0x34600D41570 [V live]; proven in 6cv [V] | [V] |
| Tag0 mByte89 | 1 | +0x89 (tag 0) | R [rdi+0x89] @ 0x6646a57 | `0x6646a57  or sil,[rdi+0x89]` | flag merged into sil; live +0x89 = 0x43 [V live]; proven in 6cv [V] | [V] |
| Tag4 mTransform | 16 | +0x00 (tag 4) | R [rdi+0x00/+0x10/+0x20/+0x30] @ 0x6647edc/0x6647ee6/0x6647ef1/0x6647efc | `0x6647edc  movups xmm0,[rdi]<br>0x6647ee6  movups xmm0,[rdi+0x10]<br>0x6647ef1  movups xmm0,[rdi+0x20]<br>0x6647efc  movdqu xmm0,[rdi+0x30]` | mat4 as four 16-byte loads into stack block [rbp+0x140..0x170]; first block of tag-4 tail | [V] |
| Tag4 mMesh (pointer) | 8 | +0x40 (tag 4) | R [rdi+0x40] @ 0x6647e73, 0x6647eb9 | `0x6647e73  mov r14,[rdi+0x40]<br>0x6647eb9  mov r14,[rdi+0x40]` | mesh/geometry pointer; r14 used as object ([r14+0x58/+0x60 string-like length; [r14+0x1D0]/[r14+0x1D4] read); no live tag-4 payload [?] | [V] |
| Tag4 mValue48 | 2 | +0x48 (tag 4) | R [rdi+0x48] @ 0x6647f10 | `0x6647f10  movzx esi,word ptr [rdi+0x48]` | u16 value | [V] |

## Field-meaning notes
- Tag0 mSource +0x00 [V]: pointer proved by instruction + live value; name from Descriptions.h [I].
- Tag0 mTexture.mPtr +0x08 [I] / mTexture.mCtrl +0x10 [I]: no tag-0 handler read site for either offset; live values +0x08 = 0x4BE6401FC40 and +0x10 = 0x4BE6401FC30 (heap pointers) [V live]; roles from header only [I].
- Tag4 mTransform +0x00 [V], mMesh +0x40 [V], mValue48 +0x48 [V]: reads proven above; names from Descriptions.h [I]; no live tag-4 payload exists (tag 4 absent from both live capture files [V]).
- Conflict noted: E1b's tag-4 handler listing ends `jmp 0x66477d8`, while the tag-4 description reads live at 0x6647e04+ (0x6647edc/0x6647e73/0x6647f10). Relation between 0x66477d8 and 0x6647e04 unchecked — see Open questions.

## Verification lines (claims, checked by verify_oc against rdis)
  0x6646a10  mov rax,[rdi+0x78]
  0x6646a57  or sil,[rdi+0x89]
  0x6648acd  mov r15,[rdi]
  0x6647edc  movups xmm0,[rdi]
  0x6647e73  mov r14,[rdi+0x40]
  0x6647f10  movzx esi,word ptr [rdi+0x48]

CLOSES? NO — tag 4 (ChunkOccluders) has no live capture: absent from docs/data/live/item_visitor.txt and docs/data/live_item_payloads_1.26.62.01.txt [V], so its pointer array mMesh+0x40 is instruction-proven (0x6647e73 mov r14,[rdi+0x40]) but no live value exists to decode; tag-4 names stay header-proven [I]. All tag-0 pending parts are proven [V]/[V live]: mSource+0x00 read [V]; mTexture.mPtr/mCtrl +0x08/+0x10 live values [V live].

## Open questions
- [UNVERIFIED: 0x66477d8] E1b's tag-4 handler listing ends `jmp 0x66477d8`, but the tag-4 description reads live at 0x6647e04+ (0x6647edc/0x6647e73/0x6647f10); whether 0x66477d8 flows into that tail is unchecked.
- mTexture.mPtr/mCtrl (+0x08/+0x10): no tag-0 handler read site found; role from Descriptions.h only [I].
- mMatrix +0x18 read via pointer (rax=[rdi+0x18]; movups [rax]) at 0x6648c3e vs Descriptions.h inline mMatrix[16]+0x18 — discrepancy vs 6cv; left to 6cv/E1b, not re-opened here.

## TOOL REQUESTS

None — rdis dis used directly; no helper script written.
