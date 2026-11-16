# U-D5h — RenderBlockSelectionOverlayBlockEntityDescription (Item tag 8)

## GOAL
Independently verify EVERY field of `RenderBlockSelectionOverlayDescription` (size 0xB8, header in src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h lines 191-211 — READ ONLY, do NOT edit) against the exe Minecraft.Windows.exe 1.26.62.01:
- fat clone 0x539b7c0 (Item tag 8) + its description-builder callee 0x668d990 (per header comment).
- Build table: offset / size / source / RVA from real stores. Stack-image stores ([rbp+..]) are excluded from stores.py; map stack offset -> desc offset using the base found at the variant {desc,tag} setup; tag byte store 'mov byte ptr [..],8' locates the tag.
- Mark each header field MATCH / MISMATCH / NOT-WRITTEN with RVA.
- Quote instruction lines as `0xRVA  instr` for verify_oc.py. Run verify_oc.py. End with ## TOOL REQUESTS.

## NEXT
Build MATCH/MISMATCH/NOT-WRITTEN table, write quoted `0xRVA  instr` lines, run verify_oc.py, end with ## TOOL REQUESTS.

## CLONE FACTS (0x539b7c0, size 0x1c00, [V] rdis fn)
- Frame: push rbp,r15,r14,r13,r12,rsi,rdi,rbx; sub rsp,0x638; rbp=rsp+0x80.
- Desc builder call: `0x539c8a4  call 0x668D990` with rcx=rdi=[rbp+0x2C0] (desc dest, desc lives on clone stack at [rbp+0x2C0..0x378]), rdx=[rbp+0x450], r8=[rbp+0x50], r9d=0. [V]
- Variant {desc,tag} setup: `0x539c916  mov [rbp+0x410],rdi` (desc ptr rdi=[rbp+0x2C0] stored qword at [rbp+0x410]); `0x539c91d  mov byte ptr [rbp+0x418],8` (tag byte=8, Item group tag 8). [V]
- => desc base = [rbp+0x2C0] (address); variant at [rbp+0x410]: +0x00 desc-ptr qword, +0x08 tag byte=8.
- Builder arg map [V]: rcx/rsi=out(dest); rdx=matrix(2nd); r8=mesh(3rd); r9d=v48(4th)=0 (clone `xor r9d,r9d`); stack args contiguous from [rbp+0x60]: [rbp+0x60]=textureSource(5th), [rbp+0x68]=material(6th), [rbp+0x70]=color(7th), [rbp+0x78]=flags u16(8th), [rbp+0x80]=block50(9th), [rbp+0x88]=variant(10th).
- stores.py excludes [rbp+..]/[rsp+..]; real desc-field stores are [rsi+off] inside builder 0x668d990 (rsi != rbp/rsp, captured by stores.py).

## BUILDER STORE TABLE (0x668d990, size ~0x2e0, ret 0x668dc6f; stores.py on docs/progress/builder_668d990.lst)
[V] every line below is a real [rsi+off] store from the disassembly; rsi=desc base. Non-[rsi] stores ([rax]/[rcx]/[rdi]/[r15]) are refcount/heap/temp ops, NOT desc fields, excluded.

| desc off | size | header field | RVA | instruction | source arg | verdict |
|----------|------|--------------|-----|-------------|------------|---------|
| 0x00 | 4 | mMatrix[0] | 0x668d9ca | movss [rsi],xmm0 | [rdx]=matrix[0] | MATCH |
| 0x04 | 4 | mMatrix[1] | 0x668d9d3 | movss [rsi+4],xmm0 | [rdx+4] | MATCH |
| 0x08 | 4 | mMatrix[2] | 0x668d9dd | movss [rsi+8],xmm0 | [rdx+8] | MATCH |
| 0x0C | 4 | mMatrix[3] | 0x668d9e7 | movss [rsi+0xC],xmm0 | [rdx+0xC] | MATCH |
| 0x10 | 4 | mMatrix[4] | 0x668d9f1 | movss [rsi+0x10],xmm0 | [rdx+0x10] | MATCH |
| 0x14 | 4 | mMatrix[5] | 0x668d9fb | movss [rsi+0x14],xmm0 | [rdx+0x14] | MATCH |
| 0x18 | 4 | mMatrix[6] | 0x668da05 | movss [rsi+0x18],xmm0 | [rdx+0x18] | MATCH |
| 0x1C | 4 | mMatrix[7] | 0x668da0f | movss [rsi+0x1C],xmm0 | [rdx+0x1C] | MATCH |
| 0x20 | 4 | mMatrix[8] | 0x668da19 | movss [rsi+0x20],xmm0 | [rdx+0x20] | MATCH |
| 0x24 | 4 | mMatrix[9] | 0x668da23 | movss [rsi+0x24],xmm0 | [rdx+0x24] | MATCH |
| 0x28 | 4 | mMatrix[10] | 0x668da2d | movss [rsi+0x28],xmm0 | [rdx+0x28] | MATCH |
| 0x2C | 4 | mMatrix[11] | 0x668da37 | movss [rsi+0x2C],xmm0 | [rdx+0x2C] | MATCH |
| 0x30 | 4 | mMatrix[12] | 0x668da41 | movss [rsi+0x30],xmm0 | [rdx+0x30] | MATCH |
| 0x34 | 4 | mMatrix[13] | 0x668da4b | movss [rsi+0x34],xmm0 | [rdx+0x34] | MATCH |
| 0x38 | 4 | mMatrix[14] | 0x668da55 | movss [rsi+0x38],xmm0 | [rdx+0x38] | MATCH |
| 0x3C | 4 | mMatrix[15] | 0x668da5f | movss [rsi+0x3C],xmm0 | [rdx+0x3C] | MATCH |
| 0x40 | 8 | mMesh | 0x668da64 | mov [rsi+0x40],r8 | r8=mesh | MATCH |
| 0x48 | 4 | mValue48 | 0x668da68 | mov [rsi+0x48],r9d | r9d=0 (clone) | MATCH ("0 from the clone") |
| 0x4C | 4 | mPad4C | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x50 | 16 | mBlock50 float[4] | 0x668da70 | movups [rsi+0x50],xmm0 | [r11]=[rbp+0x80]=block50 | MATCH |
| 0x60 | 8 | mTexture.ptr | 0x668da77 | movups [rsi+0x60],xmm0 (zero) | — | MATCH (init {}) |
| 0x60 | 8 | mTexture.ptr | 0x668dbf0 | mov [rsi+0x60],rcx | convert(0x4dfb570) ptr | MATCH (cond, src non-null) |
| 0x68 | 8 | mTexture.ctrl | 0x668da77 | movups [rsi+0x60],xmm0 (zero) | — | MATCH (init {}) |
| 0x68 | 8 | mTexture.ctrl | 0x668dbf8 | mov [rsi+0x68],rax | convert(0x4dfb570) ctrl | MATCH (cond, src non-null) |
| 0x70 | 8 | mMaterial.ptr | 0x668da7b | movups [rsi+0x70],xmm0 (zero) | — | MATCH (init {}) |
| 0x70 | 8 | mMaterial.ptr | 0x668da9f | mov [rsi+0x70],rdx | [r10]=[rbp+0x68]=material ptr | MATCH (+1 strong) |
| 0x78 | 8 | mMaterial.ctrl | 0x668da7b | movups [rsi+0x70],xmm0 (zero) | — | MATCH (init {}) |
| 0x78 | 8 | mMaterial.ctrl | 0x668daa7 | mov [rsi+0x78],rdx | [r10+8]=[rbp+0x68]+8 material ctrl | MATCH (+1 strong; addref 0x668da88) |
| 0x80 | 16 | mColor float[4] | 0x668daae | movups [rsi+0x80],xmm0 | [rcx]=[rbp+0x70]=color | MATCH |
| 0x90 | 2 | mFlags u16 | 0x668dab5 | mov [rsi+0x90],ax | ax=word [rbp+0x78]=flags | MATCH |
| 0x92 | 6 | mPad92 | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x98 | 8 | mVariantPayload[0..7] | 0x668daec | mov [rsi+0x98],rax | variant kind payload | MATCH (kind 1 heap ptr / kind 2,3 u64) |
| 0xA0 | 16 | mVariantPayload[8..0x17] | 0x668dafd | movups [rsi+0xA0],xmm0 (zero) | — | MATCH (kind 2,3 zero+ref pair) |
| 0xA0 | 8 | mVariantPayload[8..F] (ptr) | 0x668db19 | mov [rax],rcx | [rax]=rsi+0xA0, SharedRef.ptr | MATCH (kind 2,3) |
| 0xA8 | 8 | mVariantPayload[0x10..17] (ctrl) | 0x668db1f | mov [rsi+0xA8],rax | SharedRef.ctrl | MATCH (kind 2,3) |
| 0xB0 | 1 | mVariantIndex | 0x668dac3 | mov byte ptr [rsi+0xB0],0xFF | — | MATCH (default empty=0xFF) |
| 0xB0 | 1 | mVariantIndex | 0x668dbb1 | mov [rsi+0xB0],r14b | r14b=variant index [rbx+0x18] | MATCH (actual index, overwrites 0xFF) |
| 0xB1 | 7 | mPadB1 | — | (no store) | — | NOT-WRITTEN (padding) |

## TAG STORE (clone, Item group tag 8) [V]
`0x539c91d  mov byte ptr [rbp+0x418],8` — variant tag byte=8 at [rbp+0x418], desc ptr qword at [rbp+0x410] via `0x539c916  mov [rbp+0x410],rdi`. [V]
Desc builder call [V]: `0x539c8a4  call 0x668D990` (rcx=rdi=[rbp+0x2C0]=desc dest).

## VERDICT SUMMARY
- MATCH: mMatrix(+0x00,16 floats), mMesh(+0x40), mValue48(+0x48=0), mBlock50(+0x50), mTexture(+0x60, conditional convert), mMaterial(+0x70, +1 strong ref), mColor(+0x80), mFlags(+0x90), mVariantPayload(+0x98/+0xA0/+0xA8, kind-dependent), mVariantIndex(+0xB0=0xFF default then actual index).
- MISMATCH: NONE.
- NOT-WRITTEN: mPad4C(+0x4C), mPad92(+0x92), mPadB1(+0xB1) — all padding, expected (no store, no header store expected).
- All 13 header fields + 3 padding regions accounted for. Header size 0xB8 consistent (last write ends at +0xB1.. padding; sizeof 0xB8).

## VERIFICATION (verify_oc.py) [V]
`python tools/sigs/verify_oc.py docs/progress/oc_U-D5h.md` -> claimed=35 match=35 mismatch=0 no-such-instr=0. All quoted instruction lines confirmed in the real disassembly.

## QUOTED INSTRUCTION LINES (for verify_oc.py)
0x668d9ca  movss [rsi],xmm0
0x668d9d3  movss [rsi+4],xmm0
0x668d9dd  movss [rsi+8],xmm0
0x668d9e7  movss [rsi+0xC],xmm0
0x668d9f1  movss [rsi+0x10],xmm0
0x668d9fb  movss [rsi+0x14],xmm0
0x668da05  movss [rsi+0x18],xmm0
0x668da0f  movss [rsi+0x1C],xmm0
0x668da19  movss [rsi+0x20],xmm0
0x668da23  movss [rsi+0x24],xmm0
0x668da2d  movss [rsi+0x28],xmm0
0x668da37  movss [rsi+0x2C],xmm0
0x668da41  movss [rsi+0x30],xmm0
0x668da4b  movss [rsi+0x34],xmm0
0x668da55  movss [rsi+0x38],xmm0
0x668da5f  movss [rsi+0x3C],xmm0
0x668da64  mov [rsi+0x40],r8
0x668da68  mov [rsi+0x48],r9d
0x668da70  movups [rsi+0x50],xmm0
0x668da77  movups [rsi+0x60],xmm0
0x668da7b  movups [rsi+0x70],xmm0
0x668da9f  mov [rsi+0x70],rdx
0x668daa7  mov [rsi+0x78],rdx
0x668daae  movups [rsi+0x80],xmm0
0x668dab5  mov [rsi+0x90],ax
0x668dac3  mov byte ptr [rsi+0xB0],0xFF
0x668daec  mov [rsi+0x98],rax
0x668dafd  movups [rsi+0xA0],xmm0
0x668db1f  mov [rsi+0xA8],rax
0x668dbb1  mov [rsi+0xB0],r14b
0x668dbf0  mov [rsi+0x60],rcx
0x668dbf8  mov [rsi+0x68],rax
0x539c8a4  call 0x668D990
0x539c916  mov [rbp+0x410],rdi
0x539c91d  mov byte ptr [rbp+0x418],8

## TOOL REQUESTS
None | — | —



## FACTS (from header, [I] = unverified until seen in disasm)
- Struct RenderBlockSelectionOverlayDescription: sizeof 0xB8 [static_assert, header only].
- +0x00 mMatrix float[16]; +0x40 mMesh ptr; +0x48 mValue48 u32 ("0 from the clone"); +0x50 mBlock50 float[4]; +0x60 mTexture SharedRef (ptr+ctrl); +0x70 mMaterial SharedRef ("one extra strong reference"); +0x80 mColor float[4]; +0x90 mFlags u16; +0x98 mVariantPayload u8[0x18]; +0xB0 mVariantIndex u8 (0xFF = empty).
- Tag 8 = Item group; tag store expected 'mov byte ptr [..],8' [I].

## DONE
(none yet)

## BLOCKED
(none yet)
