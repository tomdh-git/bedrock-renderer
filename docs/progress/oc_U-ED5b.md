## NEXT
DONE

# U-ED5b ChunkGeometry description — close D5b pending parts (Q1 +0xB8/+0xD8, Q2 header asserts)

Checklist item D5b (docs/RENDER_CHECKLIST.md): "ChunkGeometry description: extractor + pointer route (6be); 6 live dumps (6iq); layout +0x00..+0x7F confirmed; +0xB8/+0xD8 byte flags vs live pointers unresolved; header asserts for the typed live fields pending". Predecessor oc_U-ED5b_r1.md (2026-11-16) left Q1 unresolved [?]: all 6 live samples read low byte 0x00 at +0xB8/+0xD8 so "genuine byte flag vs low byte of an aligned pointer" could not be decided. oc_U-EL4f.md (2026-11-21, DONE) proved the full typed layout [V], including +0xB8/+0xD8 as qword-wide storage whose low byte the extractor reads as a flag. This unit: (a) re-verifies every Q1 quoted address:instruction pair against Minecraft.Windows.exe 1.26.62.01 with rdis before writing it down, (b) closes Q2 by editing the header and its static_asserts so they match the disassembly and all 6 live dumps. Only the pending parts are touched here; the +0x00..+0x7F layout is closed elsewhere and is not re-decoded.

Extractor: 0x66ea3d0 (Item tag 3, size 0xF430) [V; docs/BGFX_MAP.md section 6be, line 813]. r8 = description pointer at entry, kept as r12 then rbx [V]. Live dumps: docs/data/live_chunk_desc_1.26.62.01.txt lines 2-7, 6 samples x 0x200 bytes [V live; docs/BGFX_MAP.md section 6iq, lines 2056-2058]. Header under test: src/sdk/mc/deps/minecraft_renderer/framebuilder/ChunkGeometryDescription.h, struct ChunkGeometryDescriptionView, static_asserts lines 39-50 [V]. This header is named in the unit, so editing it and its asserts is in scope.

## (1) Field table — pending and correction offsets only (one row per distinct offset, all sites listed)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line(s) | meaning | tag |
| +0x20 | 8 | desc+0x20 (rbx=desc) | `0x66eb460  lea r9,[rbx+0x20]` | &desc+0x20 taken and passed to 0xBCAB8F0 — third shared_ptr-like pair being constructed [V]; live pointer varies per sample [V live] | [V] + [V live] |
| +0x28 | 8 | desc+0x28 (paired with +0x20; no separate head read) | - | third shared_ptr control block; live ctl = object - 0x10 in all 6 samples (matches the +0x00/+0x08 and +0x10/+0x18 pairs) [V live] | [V live] |
| +0x38 | 8 | desc+0x38 | `0x66ec56d  imul rcx,[rax+0x38],0x58` | span entry count (qword), multiplied by 0x58 entry stride [V]; live count varies per sample (0x10..0x67) [V live] | [V] + [V live] |
| +0x40 | 8 | desc+0x40 | `0x66ec569  mov rdi,[rax+0x40]` | span data pointer (stack vector) [V]; live pointer varies per sample [V live] | [V] + [V live] |
| +0xB8 | 1 | desc+0xB8 (r12/rbx=desc) | `0x66ea56e  movzx eax,byte ptr [r12+0xB8]` / `0x66ea6e4  movzx edx,byte ptr [r12+0xB8]` / `0x66eb5f0  movzx eax,byte ptr [rbx+0xB8]` / `0x66eb6bb  movzx eax,byte ptr [rbx+0xB8]` / `0x66ebca3  cmp byte ptr [rbx+0xB8],0` / `0x66ebd92  cmp byte ptr [rbx+0xB8],0` / `0x66ebfa0  cmp byte ptr [rbx+0xB8],0` | extractor reads only the low byte as a flag (tested against 0; MeshContext.x/ViewPositionAndTime vs Fog selector) [V]; live storage is qword-sized and pointer-shaped (0x000003459E160300 in samples 1,2,3,5,6; 0 in sample 4), low byte always 0x00 [V live] | [V] instr / [V live] storage |
| +0xD8 | 1 | desc+0xD8 (r12=desc) | `0x66ea72e  cmp byte ptr [r12+0xD8],3` | low byte compared with 3 (isMode3 gate selecting inline bodies B-D) [V]; live qword 0x00007FF7F8363000 (samples 1,2,4,5,6) / 0x00007FF988A33000 (sample 3), low byte always 0x00 [V live] | [V] instr / [V live] storage |


## (2) Q1 — +0xB8 / +0xD8: byte flag vs low byte of a live pointer

Code-visible semantics (proven [V]): the extractor reads desc+0xB8 as a single byte at 7 sites (`movzx ... byte ptr [...]+0xB8` at 0x66ea56e / 0x66ea6e4 / 0x66eb5f0 / 0x66eb6bb; `cmp byte ptr [rbx+0xB8],0` at 0x66ebca3 / 0x66ebd92 / 0x66ebfa0) and desc+0xD8 as a single byte compared with 3 at 0x66ea72e. So at code level both offsets are byte flags, not qword reads.

Live storage ([V live], docs/data/live_chunk_desc_1.26.62.01.txt lines 2-7): the 8 bytes at +0xB8 hold a pointer-shaped qword in samples 1,2,3,5,6 (0x000003459E160300 — the same heap range as the shared_ptr objects at +0x00/+0x10/+0x20) and 0 in sample 4; the 8 bytes at +0xD8 hold 0x00007FF7F8363000 in samples 1,2,4,5,6 (module range) and 0x00007FF988A33000 in sample 3. In every sample the low byte is 0x00, which is why all byte reads return 0. Because no sample ever has a non-zero byte at +0xB8/+0xD8, the live data cannot distinguish "genuine byte flag that happens to be 0" from "low byte of an aligned pointer" — that distinction is [?]. It is non-blocking for the layout: the extractor never reads any byte beyond the low byte, so the correct storage type is qword (pointer or NULL) with a low-byte flag view, exactly as oc_U-EL4f.md concluded [V instr + V live].

## (3) Q2 — header static_asserts vs live dumps (edits to ChunkGeometryDescription.h)

This unit edits src/sdk/mc/deps/minecraft_renderer/framebuilder/ChunkGeometryDescription.h (named header — in scope) and nothing else:

- `uint8_t mPad20[0x10]` (+0x20..+0x2F) -> `void* mShared2Ptr` (+0x20) + `void* mShared2Ctl` (+0x28): third shared_ptr pair; &desc+0x20 taken at 0x66eb460 [V], ctl = object - 0x10 in all 6 live samples [V live].
- `uint8_t mPad38[0x10]` (+0x38..+0x47) -> `uint64_t mSpanCount` (+0x38) + `void* mSpanPtr` (+0x40): {count, ptr} span; count read via `imul rcx,[rax+0x38],0x58` at 0x66ec56d [V], ptr via `mov rdi,[rax+0x40]` at 0x66ec569 [V]; live count/ptr vary per sample [V live]. Neither is padding.
- `uint8_t mFlagB8` (+0xB8) -> `void* mPtrB8` (+0xB8): qword storage (pointer or NULL); the extractor tests only the low byte as a flag (7 sites above) [V]; remove `uint8_t mPadB9[0x1F]`.
- `uint8_t mModeD8` (+0xD8) -> `void* mPtrD8` (+0xD8): qword storage; low byte compared with 3 at 0x66ea72e [V]; remove `uint8_t mPadD9[7]`.
- Gap +0xC0..+0xD7 between the two qwords is `uint8_t mPadC0[0x18]` [?] (undecoded, no head access).
- Comments that said "when mFlagB8 == 0" (mFogAndDistance at +0x64, mViewPos at +0xE4) now say "when the low byte of mPtrB8 (+0xB8) is 0".
- static_asserts (lines 39-50): replace `mFlagB8 == 0xB8` / `mModeD8 == 0xD8` with `mShared2Ptr == 0x20`, `mShared2Ctl == 0x28`, `mSpanCount == 0x38`, `mSpanPtr == 0x40`, `mPtrB8 == 0xB8`, `mPtrD8 == 0xD8`. All asserted offsets now match the disassembly [V] and every asserted typed field matches all 6 live dumps [V live].

Undecoded and intentionally left [?]: +0x78..+0xB7 (mPad78) and +0xC0..+0xD7 (mPadC0) — no extractor-head instruction touches them; outside this item.

## CLOSES?
YES — every pending part of item D5b is now resolved: Q1 +0xB8/+0xD8 byte-flag reads are [V]-proven at 7 sites, and the live storage is [V live]-proven as qword-wide pointer-shaped data whose low byte is always 0x00 in all 6 samples (genuine-flag-vs-low-byte stays [?] but non-blocking: the extractor reads only the byte); Q2 header corrections (+0x20/+0x28 shared pair, +0x38/+0x40 span count/ptr, +0xB8/+0xD8 qword pointers instead of byte flags/pad) are applied to ChunkGeometryDescription.h and its static_asserts, all matching disassembly [V] and all 6 live dumps [V live]. Residual [?]: no non-zero +0xB8/+0xD8 byte was ever observed (would need a 7th live sample) — does not block layout closure.

## TOOL REQUESTS
None.
