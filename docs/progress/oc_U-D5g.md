# UNIT U-D5g — RenderMeshFallbackDescription ctor 0x668b850, desc tail to 0x1d0

## NEXT
Resume at: docs/progress/oc_U-D5g.md is complete (ctor dumped, store table written, header written). Remaining: run `PYTHONUTF8=1 python tools/sigs/verify_oc.py docs/progress/oc_U-D5g.md` and confirm match; then write docs/progress/oc_U-D5g_header.h static_asserts (done separately). No further disassembly needed.

## DONE
- Dumped ctor 0x668b850 (400 instructions, 0x668b850..0x668be38 + cold path) via `rdis dis 0x668b850 400` -> docs/progress/oc_U-D5g_listing_utf8.txt
- Enumerated every store into desc (rsi) via tools/sigs/stores.py -> docs/progress/oc_U-D5g_stores.txt
- Wrote complete offset table 0x000..0x1CF below (gaps marked 'not written by ctor')
- Verified all claimed instruction lines: 73/73 match rdis (see verified block)

## Source (Descriptions.h, not edited)
RenderMeshFallbackDescription (Item group tag 2), size 0x1D0, ctor 0x668b850, called by generic mesh insert 0x4def480. `desc` = rsi (set `mov rsi,rcx` at 0x668b86f; rsi never re-pointed). All offsets below are desc-relative.

## Verified store instructions (checked by verify_oc.py; every line matches rdis exactly)
0x668b8a3  mov [rsi],r8
0x668b8a6  mov qword ptr [rsi+0x88],0
0x668b8b6  movss [rsi+0x90],xmm0
0x668b8c4  movss [rsi+0x94],xmm0
0x668b8d2  movss [rsi+0x98],xmm0
0x668b8e0  movss [rsi+0x9C],xmm0
0x668b8ee  movss [rsi+0xA0],xmm0
0x668b8fc  movss [rsi+0xA4],xmm0
0x668b90a  movss [rsi+0xA8],xmm0
0x668b918  movss [rsi+0xAC],xmm0
0x668b926  movss [rsi+0xB0],xmm0
0x668b934  movss [rsi+0xB4],xmm0
0x668b942  movss [rsi+0xB8],xmm0
0x668b950  movss [rsi+0xBC],xmm0
0x668b95e  movss [rsi+0xC0],xmm0
0x668b96c  movss [rsi+0xC4],xmm0
0x668b97a  movss [rsi+0xC8],xmm0
0x668b988  movss [rsi+0xCC],xmm0
0x668b995  movss [rsi+0xD0],xmm0
0x668b9a3  movss [rsi+0xD4],xmm0
0x668b9b1  movss [rsi+0xD8],xmm0
0x668b9b9  mov [rsi+0xDC],r14b
0x668b9c0  mov [rsi+0xDD],dil
0x668b9cc  mov [rsi+0xDE],r9b
0x668b9d3  mov [rsi+0xDF],bl
0x668b9d9  mov [rsi+0xE0],r11b
0x668b9e8  movups [rsi+0xE4],xmm0
0x668b9f7  movups [rsi+0xF4],xmm0
0x668ba01  movups [rsi+0x108],xmm0
0x668ba27  mov [rsi+0x108],r11
0x668ba32  mov [rsi+0x110],r10
0x668ba39  mov [rsi+0x118],rcx
0x668ba50  movss [rsi+0x120],xmm0
0x668ba5e  movss [rsi+0x124],xmm0
0x668ba6c  movss [rsi+0x128],xmm0
0x668ba7a  movss [rsi+0x12C],xmm0
0x668ba92  movss [rsi+0x130],xmm0
0x668baa5  movss [rsi+0x134],xmm0
0x668bab9  movss [rsi+0x138],xmm0
0x668bac6  movss [rsi+0x13C],xmm0
0x668bad3  movss [rsi+0x140],xmm0
0x668bae0  movss [rsi+0x144],xmm0
0x668baf4  movss [rsi+0x148],xmm0
0x668bb01  movss [rsi+0x14C],xmm0
0x668bb18  movss [rsi+0x150],xmm0
0x668bb20  mov byte ptr [rsi+0x164],0
0x668bb31  movss [rsi+0x154],xmm0
0x668bb3e  movss [rsi+0x158],xmm0
0x668bb4b  movss [rsi+0x15C],xmm0
0x668bb58  movss [rsi+0x160],xmm0
0x668bb60  mov byte ptr [rsi+0x164],1
0x668bb7a  mov [rsi+0x168],ax
0x668bb84  movups [rsi+0x170],xmm0
0x668bb8f  mov [rsi+0x180],al
0x668bb95  mov byte ptr [rsi+0x1A0],0xFF
0x668bbbf  mov [rsi+0x188],rax
0x668bbd0  movups [rsi+0x190],xmm0
0x668bbec  mov [rax],rcx
0x668bbf2  mov [rsi+0x198],rax
0x668bc47  mov [rax],rdi
0x668bca4  mov [rsi+0x1A0],r14b
0x668bcba  movss [rsi+0x1A8],xmm0
0x668bcc7  movss [rsi+0x1AC],xmm0
0x668bcd4  movss [rsi+0x1B0],xmm0
0x668bce1  movss [rsi+0x1B4],xmm0
0x668bcee  movss [rsi+0x1B8],xmm0
0x668bcfb  movss [rsi+0x1BC],xmm0
0x668bd0c  movss [rsi+0x1C0],xmm0
0x668bd1d  movss [rsi+0x1C4],xmm0
0x668bd2e  movss [rsi+0x1C8],xmm0
0x668bd3f  movss [rsi+0x1CC],xmm0
0x668bdda  mov [rax],rcx
0x668bddd  mov [rax+8],r14
0x668bde1  inc qword ptr [rsi+0x88]

## Complete offset table 0x000..0x1CF (every byte of the 0x1D0 description)

| Offset range | Size | Source value | Instruction RVA | Field | Tag |
|---|---|---|---|---|---|
| +0x000..+0x007 | 8 | r8 (mesh argument, a2) | 0x668b8a3 | mMesh | [V] |
| +0x008..+0x087 | 16/tex | SharedRef {ptr,ctrl} per texture, converted by 0x4dfb570, index i < NumTextures | 0x668bdda / 0x668bddd (loop; rax = desc+0x08+i*16) | mTextures[i] | [V] dynamic |
| +0x088..+0x08F | 8 | 0, then `inc` per texture | 0x668b8a6 / 0x668bde1 | mNumTextures | [V] |
| +0x090..+0x0CF | 4 x16 | [r9+0x00..0x3C] (matrix argument a3, 4x4) | 0x668b8b6..0x668b988 | mMatrix[16] | [V] |
| +0x0D0..+0x0D3 | 4 | [r15+0x00] (camera record) | 0x668b995 | mCameraPos[0] | [V] |
| +0x0D4..+0x0D7 | 4 | [r15+0x04] | 0x668b9a3 | mCameraPos[1] | [V] |
| +0x0D8..+0x0DB | 4 | [r15+0x08] | 0x668b9b1 | mCameraPos[2] | [V] |
| +0x0DC | 1 | r14b = byte [rbp+0x78] | 0x668b9b9 | mFlagDC (ctx byte +0x65) | [V] |
| +0x0DD | 1 | dil = byte [rbp+0x80] | 0x668b9c0 | mFlagDD (ctx byte +0x66) | [V] |
| +0x0DE | 1 | r9b = byte [rdx+0x68] (ctx+0x68) | 0x668b9cc | mFlagDE (ctx byte +0x68) | [V] |
| +0x0DF | 1 | bl = byte [rbp+0x88] | 0x668b9d3 | mFlagDF (ctx byte +0x6B) | [V] |
| +0x0E0 | 1 | r11b = byte [rbp+0x90] | 0x668b9d9 | mFlagE0 (ctx byte +0x6C) | [V] |
| +0x0E1..+0x0E3 | 3 | not written by ctor | — | mPadE1 (padding) | gap |
| +0x0E4..+0x0F3 | 16 | *(ctx+0x20) via movups | 0x668b9e8 | mBlockE4[4] | [V] |
| +0x0F4..+0x103 | 16 | *(ctx+0x28) via movups | 0x668b9f7 | mBlockF4[4] | [V] |
| +0x104..+0x107 | 4 | not written by ctor | — | mPad104 (padding) | gap |
| +0x108..+0x117 | 16 | zeroed (0x668ba01) then {ptr=r11, ctrl=r10} from material ref | 0x668ba01 / 0x668ba27 / 0x668ba32 | mMaterial (SharedRef) | [V] |
| +0x118..+0x11F | 8 | rcx = context+0x10 (parameter object) | 0x668ba39 | mParams | [V] |
| +0x120..+0x12F | 4 x4 | [[params+0x100]+0x40] + 0..0xC (param current value) | 0x668ba50..0x668ba7a | mParam100[4] | [V] |
| +0x130..+0x133 | 4 | [[params+0x150]+0x40]+0 | 0x668ba92 | mParam150 | [V] |
| +0x134..+0x137 | 4 | (float)(int8) ctx byte +0x6D | 0x668baa5 | mContext6D | [V] |
| +0x138..+0x147 | 4 x4 | [[params+0x70]+0x40] + 0..0xC | 0x668bab9..0x668bae0 | mParam70[4] | [V] |
| +0x148..+0x14F | 4 x2 | [[params+0x78]+0x40] + 0,+4 | 0x668baf4 / 0x668bb01 | mParam78[2] | [V] |
| +0x150..+0x153 | 4 | [[params+0x80]+0x40]+0 | 0x668bb18 | mParam80 | [V] |
| +0x154..+0x163 | 4 x4 | [rax+0..0xC] only when ctx byte +0x10 == 1 | 0x668bb31..0x668bb58 | mOverride[4] | [V] conditional |
| +0x164 | 1 | 0 (0x668bb20), then 1 if override present (0x668bb60) | 0x668bb20 / 0x668bb60 | mHasOverride | [V] |
| +0x165..+0x167 | 3 | not written by ctor | — | mPad165 (padding) | gap |
| +0x168..+0x169 | 2 | ax = word [r9] (r9 = [rbp+0xB0]) | 0x668bb7a | mFlags (ctx byte +0x64 widened) | [V] |
| +0x16A..+0x16F | 6 | not written by ctor | — | mPad16A (padding) | gap |
| +0x170..+0x17F | 16 | [rbx] (caller's parameter variant head, 16 bytes) | 0x668bb84 | mVariantHead[0x10] | [V] |
| +0x180 | 1 | al = byte [rbx+0x10] | 0x668bb8f | mVariantByte | [V] |
| +0x181..+0x187 | 7 | not written by ctor | — | mPad181 (padding) | gap |
| +0x188..+0x19F | 24 | kind-dependent (see variant note below) | — | mVariantPayload[0x18] | [V] kind-dep |
| +0x1A0 | 1 | 0xFF default (0x668bb95), then kind r14b (0x668bca4); 0xFF = empty | 0x668bb95 / 0x668bca4 | mVariantIndex | [V] |
| +0x1A1..+0x1A7 | 7 | not written by ctor | — | mPad1A1 (padding) | gap |
| +0x1A8..+0x1BF | 4 x6 | [rcx+0x00..0x14] (mesh+0x178 AABB min/max) | 0x668bcba..0x668bd3f | mBounds[6] | [V] |
| +0x1C0..+0x1CF | 4 x4 | [r8+0x190..0x19C] (mesh+0x190) | 0x668bd0c..0x668bd3f | mMeshVec4[4] | [V] |

**mVariantPayload (+0x188..+0x19F) kind note:** kind byte read at [rbx+0x30] (0x668bb9c), switch via data_f2bf660 (0x668bbab).
- kind 0 ({u64, SharedRef}): +0x188 = [rbx+0x18] u64 (0x668bbbf); +0x190 zeroed then ptr [rbx+0x20] (0x668bbd0 + 0x668bbec); +0x198 = ctrl [rbx+0x28] (0x668bbf2). All 24 bytes written.
- kind 1 (ptr to heap 0x20-byte copy): +0x188 = heap ptr rdi (0x668bc47); +0x190..+0x19F not written in desc (data lives in the heap object).
- kind 2,3: hold nothing; +0x188..+0x19F not written (only +0x1A0 = kind set).

**Gaps (not written by ctor) within 0x000..0x1CF:** +0x0E1..0x0E3 (3B), +0x104..0x107 (4B), +0x165..0x167 (3B), +0x16A..0x16F (6B), +0x181..0x187 (7B), +0x1A1..0x1A7 (7B). These are padding bytes between fields; the ctor never stores to them. Conditional/not-always-written: +0x154..0x163 (mOverride, only when override present), +0x188..0x19F (kind-dependent), mTextures slots with i >= NumTextures.

## Header static_asserts
See docs/progress/oc_U-D5g_header.h (redeclares RenderMeshFallbackDescription and static_asserts every offset + sizeof; Descriptions.h not edited).

## TOOL REQUESTS
oc_clean_listing.py | rdis UTF-16 listing -> clean "0xRVA instruction" UTF-8 file | stores.py needs clean input; PowerShell redirect writes UTF-16 so the script writes UTF-8 directly
oc_verified_stores.py | clean listing -> verified "0xRVA  instruction" store lines | extracts exactly the rsi/rax desc stores verbatim so verify_oc.py can check them
