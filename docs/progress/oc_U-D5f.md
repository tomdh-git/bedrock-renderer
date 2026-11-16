# U-D5f — RenderSkinnedMeshDescription (Item tag 7)

## GOAL
Independently verify EVERY field of `RenderSkinnedMeshDescription` (size 0x1D0, header in src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h lines 84-126 — READ ONLY, do NOT edit) against the exe Minecraft.Windows.exe 1.26.62.01:
- fat clone 0x6b84e60 (Item tag 7, general clone) — find its description-builder callee (header says 0x668d350, called from producer 0x4e39f20).
- second producer 0x4e39f20 (thin clone) — say which fields it sets.
- Build table: offset / size / header field / RVA / instruction / source arg / verdict MATCH|MISMATCH|NOT-WRITTEN for EVERY header field.
- Quote instruction lines as `0xRVA  instr` for verify_oc.py. Run verify_oc.py. End with ## TOOL REQUESTS.
Model: docs/progress/oc_U-D5h.md (finished unit, same kind).

## NEXT
Run verify_oc.py; fix any mismatches; end with ## TOOL REQUESTS.

## CLONE FACTS (0x6b84e60) [V]
- Frame: push rbp,r15,r14,r13,r12,rsi,rdi,rbx; sub rsp,0x3D8; rbp=rsp+0x80. Size 0x1bf0 (0x6b84e60..0x6b86a50).
- Desc lives on clone stack at [rbp+0x60..0x230] (0x1D0 bytes).
- Builder callee: `0x6b86616  call 0x668D350` [V]. rcx=rsi=lea rsi,[rbp+0x60] (desc dest). [V]
- rdx=matA, r8=matB (set earlier in fn), r9=lea r9,[rbp+0x40] (bounds, 4th arg). [V]
- Stack args (5th–21st) at [rsp+0x20..0xA0]: [rsp+0x20]=rbx(mesh), [rsp+0x28]=ecx(valueB8), [rsp+0x30]=&[rbp+0x290](refs), [rsp+0x38]=[rbp+0x3C8](material), [rsp+0x40]=r9(block154), [rsp+0x48]=&[rbp+0x248](blockC0), [rsp+0x50]=&[rbp+0x258](blockD0), [rsp+0x58]=r12b(f0), [rsp+0x60]=r14b(f1), [rsp+0x68]=r10b(f2), [rsp+0x70]=dil(f3), [rsp+0x78]=ax(flags1CC), [rsp+0x80]=[rbp+0x308](pv variant), [rsp+0x88]=r13(block164), [rsp+0x90]=[rbp+0x308]+0x60(override), [rsp+0x98]=r15d(count), [rsp+0xA0]=r11b(byte1CE). [V]
- Variant {desc,tag} setup: `0x6b8668c  mov [rbp+0x310],rsi` (desc ptr qword = &[rbp+0x60]); `0x6b86693  mov byte ptr [rbp+0x318],7` (tag byte=7, Item group tag 7). [V]
- => desc base = [rbp+0x60]; variant at [rbp+0x310]: +0x00 desc-ptr qword, +0x08 tag byte=7.

## BUILDER STORE TABLE (0x668d350, size 0x5cf, ret 0x668d8e2; stores.py on docs/progress/builder_668d350_stores.lst)
[V] every line below is a real [rcx+off] store from the disassembly; rcx=desc base. Non-[rcx] stores ([rax]/[rsi]/[rdi]) are heap/temp ops, NOT desc fields, excluded.
[rsi+off] stores in the 0x668d7bf..0x668d85e range (kind-1 variant heap copy) write to a heap block, NOT to desc fields — excluded.

| desc off | size | header field | RVA | instruction | source arg | verdict |
|----------|------|--------------|-----|-------------|------------|---------|
| 0x000 | 4 | mMatrixA[0] | 0x668d386 | movss [rcx],xmm0 | [rdx]=matA[0] | MATCH |
| 0x004 | 4 | mMatrixA[1] | 0x668d38f | movss [rcx+4],xmm0 | [rdx+4] | MATCH |
| 0x008 | 4 | mMatrixA[2] | 0x668d399 | movss [rcx+8],xmm0 | [rdx+8] | MATCH |
| 0x00C | 4 | mMatrixA[3] | 0x668d3a3 | movss [rcx+0xC],xmm0 | [rdx+0xC] | MATCH |
| 0x010 | 4 | mMatrixA[4] | 0x668d3ad | movss [rcx+0x10],xmm0 | [rdx+0x10] | MATCH |
| 0x014 | 4 | mMatrixA[5] | 0x668d3b7 | movss [rcx+0x14],xmm0 | [rdx+0x14] | MATCH |
| 0x018 | 4 | mMatrixA[6] | 0x668d3c1 | movss [rcx+0x18],xmm0 | [rdx+0x18] | MATCH |
| 0x01C | 4 | mMatrixA[7] | 0x668d3cb | movss [rcx+0x1C],xmm0 | [rdx+0x1C] | MATCH |
| 0x020 | 4 | mMatrixA[8] | 0x668d3d5 | movss [rcx+0x20],xmm0 | [rdx+0x20] | MATCH |
| 0x024 | 4 | mMatrixA[9] | 0x668d3df | movss [rcx+0x24],xmm0 | [rdx+0x24] | MATCH |
| 0x028 | 4 | mMatrixA[10] | 0x668d3e9 | movss [rcx+0x28],xmm0 | [rdx+0x28] | MATCH |
| 0x02C | 4 | mMatrixA[11] | 0x668d3f3 | movss [rcx+0x2C],xmm0 | [rdx+0x2C] | MATCH |
| 0x030 | 4 | mMatrixA[12] | 0x668d3fd | movss [rcx+0x30],xmm0 | [rdx+0x30] | MATCH |
| 0x034 | 4 | mMatrixA[13] | 0x668d407 | movss [rcx+0x34],xmm0 | [rdx+0x34] | MATCH |
| 0x038 | 4 | mMatrixA[14] | 0x668d411 | movss [rcx+0x38],xmm0 | [rdx+0x38] | MATCH |
| 0x03C | 4 | mMatrixA[15] | 0x668d41b | movss [rcx+0x3C],xmm0 | [rdx+0x3C] | MATCH |
| 0x040 | 4 | mMatrixB[0] | 0x668d425 | movss [rcx+0x40],xmm0 | [r8]=matB[0] | MATCH |
| 0x044 | 4 | mMatrixB[1] | 0x668d430 | movss [rcx+0x44],xmm0 | [r8+4] | MATCH |
| 0x048 | 4 | mMatrixB[2] | 0x668d43b | movss [rcx+0x48],xmm0 | [r8+8] | MATCH |
| 0x04C | 4 | mMatrixB[3] | 0x668d446 | movss [rcx+0x4C],xmm0 | [r8+0xC] | MATCH |
| 0x050 | 4 | mMatrixB[4] | 0x668d451 | movss [rcx+0x50],xmm0 | [r8+0x10] | MATCH |
| 0x054 | 4 | mMatrixB[5] | 0x668d45c | movss [rcx+0x54],xmm0 | [r8+0x14] | MATCH |
| 0x058 | 4 | mMatrixB[6] | 0x668d467 | movss [rcx+0x58],xmm0 | [r8+0x18] | MATCH |
| 0x05C | 4 | mMatrixB[7] | 0x668d472 | movss [rcx+0x5C],xmm0 | [r8+0x1C] | MATCH |
| 0x060 | 4 | mMatrixB[8] | 0x668d47d | movss [rcx+0x60],xmm0 | [r8+0x20] | MATCH |
| 0x064 | 4 | mMatrixB[9] | 0x668d488 | movss [rcx+0x64],xmm0 | [r8+0x24] | MATCH |
| 0x068 | 4 | mMatrixB[10] | 0x668d493 | movss [rcx+0x68],xmm0 | [r8+0x28] | MATCH |
| 0x06C | 4 | mMatrixB[11] | 0x668d49e | movss [rcx+0x6C],xmm0 | [r8+0x2C] | MATCH |
| 0x070 | 4 | mMatrixB[12] | 0x668d4a9 | movss [rcx+0x70],xmm0 | [r8+0x30] | MATCH |
| 0x074 | 4 | mMatrixB[13] | 0x668d4b4 | movss [rcx+0x74],xmm0 | [r8+0x34] | MATCH |
| 0x078 | 4 | mMatrixB[14] | 0x668d4bf | movss [rcx+0x78],xmm0 | [r8+0x38] | MATCH |
| 0x07C | 4 | mMatrixB[15] | 0x668d4ca | movss [rcx+0x7C],xmm0 | [r8+0x3C] | MATCH |
| 0x080 | 4 | mBounds[0] | 0x668d4e2 | movss [rcx+0x80],xmm0 | [r9]=bounds[0] | MATCH (cond, bounds->idx!=0xFF) |
| 0x084 | 4 | mBounds[1] | 0x668d4f0 | movss [rcx+0x84],xmm0 | [r9+4] | MATCH (cond) |
| 0x088 | 4 | mBounds[2] | 0x668d4fe | movss [rcx+0x88],xmm0 | [r9+8] | MATCH (cond) |
| 0x08C | 4 | mBounds[3] | 0x668d50c | movss [rcx+0x8C],xmm0 | [r9+0xC] | MATCH (cond) |
| 0x090 | 4 | mBounds[4] | 0x668d51a | movss [rcx+0x90],xmm0 | [r9+0x10] | MATCH (cond) |
| 0x094 | 4 | mBounds[5] | 0x668d528 | movss [rcx+0x94],xmm0 | [r9+0x14] | MATCH (cond) |
| 0x098 | 1 | mBoundsEmpty | 0x668d4cf | mov byte ptr [rcx+0x98],0xFF | — | MATCH (default = none) |
| 0x098 | 1 | mBoundsEmpty | 0x668d530 | mov byte ptr [rcx+0x98],0 | — | MATCH (cond, overwrites to valid) |
| 0x099 | 3 | mPad099 | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x09C | 4 | mMeshVec4[0] | 0x668d53f | movss [rcx+0x9C],xmm0 | [rdi+0x190]=mesh->f190 | MATCH |
| 0x0A0 | 4 | mMeshVec4[1] | 0x668d54f | movss [rcx+0xA0],xmm0 | [rdi+0x194] | MATCH |
| 0x0A4 | 4 | mMeshVec4[2] | 0x668d55f | movss [rcx+0xA4],xmm0 | [rdi+0x198] | MATCH |
| 0x0A8 | 4 | mMeshVec4[3] | 0x668d56f | movss [rcx+0xA8],xmm0 | [rdi+0x19C] | MATCH |
| 0x0AC | 4 | mPad0AC | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x0B0 | 8 | mMesh | 0x668d577 | mov [rcx+0xB0],rdi | rdi=mesh (5th arg) | MATCH |
| 0x0B8 | 4 | mValueB8 | 0x668d57e | mov [rcx+0xB8],esi | esi=valueB8 (6th arg) | MATCH |
| 0x0BC | 4 | mPad0BC | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x0C0 | 16 | mBlockC0 | 0x668d588 | movups [rcx+0xC0],xmm0 | [r11]=[rbp+0x88]=blockC0 | MATCH |
| 0x0D0 | 16 | mBlockD0 | 0x668d593 | movups [rcx+0xD0],xmm0 | [r10]=[rbp+0x90]=blockD0 | MATCH |
| 0x0E0 | 16 | mRefE0 SharedRef | 0x668d59d | movups [rcx+0xE0],xmm0 | zero init | MATCH |
| 0x0E0 | 8 | mRefE0.ptr | 0x668d5b4 | mov [rcx+0xE0],rdx | refs->r00 | MATCH (+1 strong) |
| 0x0E8 | 8 | mRefE0.ctrl | 0x668d5bf | mov [rcx+0xE8],rdx | refs->ctrl | MATCH (+1 strong) |
| 0x0F0 | 16 | mRefF0 SharedRef | 0x668d5c6 | movups [rcx+0xF0],xmm0 | zero init | MATCH |
| 0x0F0 | 8 | mRefF0.ptr | 0x668d5de | mov [rcx+0xF0],rdx | refs->r10 | MATCH (+1 strong) |
| 0x0F8 | 8 | mRefF0.ctrl | 0x668d5e9 | mov [rcx+0xF8],rdx | refs->ctrl | MATCH (+1 strong) |
| 0x100 | 1 | mByte100 | 0x668d5f4 | mov [rcx+0x100],dl | refs->b20 | MATCH |
| 0x101 | 7 | mPad101 | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x108 | 16 | mRef108 SharedRef | 0x668d5fa | movups [rcx+0x108],xmm0 | zero init | MATCH |
| 0x108 | 8 | mRef108.ptr | 0x668d612 | mov [rcx+0x108],rdx | refs->r28 | MATCH (+1 strong) |
| 0x110 | 8 | mRef108.ctrl | 0x668d61d | mov [rcx+0x110],rdx | refs->ctrl | MATCH (+1 strong) |
| 0x118 | 1 | mByte118 | 0x668d628 | mov [rcx+0x118],dl | refs->b38 | MATCH |
| 0x119 | 7 | mPad119 | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x120 | 16 | mRef120 SharedRef | 0x668d62e | movups [rcx+0x120],xmm0 | zero init | MATCH |
| 0x120 | 8 | mRef120.ptr | 0x668d64a | mov [rcx+0x120],rdx | refs->r40 | MATCH (+1 strong) |
| 0x128 | 8 | mRef120.ctrl | 0x668d655 | mov [rcx+0x128],rdx | refs->ctrl | MATCH (+1 strong) |
| 0x130 | 16 | mRef130 SharedRef | 0x668d65c | movups [rcx+0x130],xmm0 | zero init | MATCH |
| 0x130 | 8 | mRef130.ptr | 0x668d6a5 | mov [rcx+0x130],r14 | refs->r50 | MATCH (+1 strong) |
| 0x138 | 8 | mRef130.ctrl | 0x668d6b0 | mov [rcx+0x138],rax | refs->ctrl | MATCH (+1 strong) |
| 0x140 | 16 | mMaterial SharedRef | 0x668d6b7 | movups [rcx+0x140],xmm0 | zero init | MATCH |
| 0x140 | 8 | mMaterial.ptr | 0x668d6dc | mov [rcx+0x140],rax | material ptr ([rbp+0x78]) | MATCH (+1 strong) |
| 0x148 | 8 | mMaterial.ctrl | 0x668d6e7 | mov [rcx+0x148],rax | material ctrl | MATCH (+1 strong) |
| 0x150 | 1 | mFlags150[0] | 0x668d6ee | mov [rcx+0x150],dil | f0 ([rbp+0x98]) | MATCH |
| 0x151 | 1 | mFlags150[1] | 0x668d6f5 | mov [rcx+0x151],sil | f1 ([rbp+0xA0]) | MATCH |
| 0x152 | 1 | mFlags150[2] | 0x668d6fc | mov [rcx+0x152],bl | f2 ([rbp+0xA8]) | MATCH |
| 0x153 | 1 | mFlags150[3] | 0x668d702 | mov [rcx+0x153],r10b | f3 ([rbp+0x90]) | MATCH |
| 0x154 | 16 | mBlock154 | 0x668d70d | movups [rcx+0x154],xmm0 | [r11]=[rbp+0x80]=block154 | MATCH |
| 0x164 | 16 | mBlock164 | 0x668d718 | movups [rcx+0x164],xmm0 | [r9]=[rbp+0xC8]=block164 | MATCH |
| 0x174 | 4 | mValue174 | 0x668d723 | mov [rcx+0x174],eax | block164->u32_10 | MATCH |
| 0x178 | 2 | mCount178 | 0x668d73c | mov [rcx+0x178],dx | count u16 (checked <0x10000) | MATCH |
| 0x17A | 6 | mPad17A | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x180 | 16 | mVariantHead | 0x668d746 | movups [rcx+0x180],xmm0 | variant->head[0..15] | MATCH |
| 0x190 | 1 | mVariantByte | 0x668d751 | mov [rcx+0x190],al | variant->byte at +0x10 | MATCH |
| 0x191 | 7 | mPad191 | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x198 | 8 | mVariantPayload[0..7] | 0x668d780 | mov [rcx+0x198],rax | kind-0 u64 payload | MATCH (kind 0) |
| 0x198 | 8 | mVariantPayload[0..7] | 0x668d809 | mov [rax],rsi (rax=rcx+0x198) | kind-1 heap ptr | MATCH (kind 1) |
| 0x1A0 | 16 | mVariantPayload[8..0x17] | 0x668d791 | movups [rcx+0x1A0],xmm0 | zero (kind 0) | MATCH (kind 0) |
| 0x1B0 | 1 | mVariantIndex | 0x668d757 | mov byte ptr [rcx+0x1B0],0xFF | — | MATCH (default empty=0xFF) |
| 0x1B0 | 1 | mVariantIndex | 0x668d85e | mov [rcx+0x1B0],dil | variant kind (0..3) | MATCH (actual, overwrites 0xFF) |
| 0x1B1 | 7 | mPad1B1 | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x1B8 | 4 | mOverride[0] | 0x668d88d | movss [rcx+0x1B8],xmm0 | override->v[0] | MATCH (cond, override->has==1) |
| 0x1BC | 4 | mOverride[1] | 0x668d89b | movss [rcx+0x1BC],xmm0 | override->v[1] | MATCH (cond) |
| 0x1C0 | 4 | mOverride[2] | 0x668d8a9 | movss [rcx+0x1C0],xmm0 | override->v[2] | MATCH (cond) |
| 0x1C4 | 4 | mOverride[3] | 0x668d8b7 | movss [rcx+0x1C4],xmm0 | override->v[3] | MATCH (cond) |
| 0x1C8 | 1 | mHasOverride | 0x668d87a | mov byte ptr [rcx+0x1C8],0 | — | MATCH (default false) |
| 0x1C8 | 1 | mHasOverride | 0x668d8bf | mov byte ptr [rcx+0x1C8],1 | — | MATCH (cond, overwrites to true) |
| 0x1C9 | 3 | mPad1C9 | — | (no store) | — | NOT-WRITTEN (padding) |
| 0x1CC | 2 | mFlags1CC | 0x668d8c6 | mov [rcx+0x1CC],dx | flags1CC | MATCH |
| 0x1CE | 1 | mByte1CE | 0x668d8cd | mov [rcx+0x1CE],al | byte1CE | MATCH |
| 0x1CF | 1 | (trailing pad to 0x1D0) | — | (no store) | — | NOT-WRITTEN (padding) |

## TAG STORE (clone, Item group tag 7) [V]
`0x6b86693  mov byte ptr [rbp+0x318],7` — variant tag byte=7 at [rbp+0x318], desc ptr qword at [rbp+0x310] via `0x6b8668c  mov [rbp+0x310],rsi` (rsi=&[rbp+0x60], preserved by callee-saved rsi in builder). [V]
Builder call [V]: `0x6b86616  call 0x668D350` (rcx=rsi=[rbp+0x60]=desc dest).

## SECOND PRODUCER 0x4e39f20 — WHICH FIELDS IT SETS [V]
- Producer 0x4e39f20 (thin clone, size 0x9af) calls builder 0x668d350 at `0x4e3a43e  call 0x668D350` [V].
- rcx=lea r12,[rbp+0x30] / mov rcx,r12 → desc dest = [rbp+0x30] on producer stack. [V]
- rdx=lea rdx,[rbp+0x240] (matA); r8=rdx (matB — SAME pointer as matA); r9=lea r9,[rbp+0x39C] (bounds). [V]
- Stack args: [rsp+0x20]=rax(mesh), [rsp+0x28]=0(valueB8), [rsp+0x30]=[rbp+0x330](refs), [rsp+0x38]=[rbp+0x3C8](material), [rsp+0x40]=&[rbp+0x2B0](block154), [rsp+0x48]=&[rbp+0x2E8](blockC0), [rsp+0x50]=&[rbp+0x2D8](blockD0), [rsp+0x58]=0(f0), [rsp+0x60]=1(f1), [rsp+0x68]=0(f2), [rsp+0x70]=0(f3), [rsp+0x78]=[rbp+0x3C4](flags1CC), [rsp+0x80]=&[rbp+0x2F8](pv variant), [rsp+0x88]=[rbp+0x338](block164), [rsp+0x90]=&[rbp+0x28C](override), [rsp+0x98]=r9d(count), [rsp+0xA0]=r8b(byte1CE). [V]
- **The producer writes NO desc field directly.** All desc fields are written by the builder 0x668d350. The producer only computes source arguments and calls the builder. [V]
- Variant tag setup: `0x4e3a4ad  mov [rbp+0x200],r12` (desc ptr = &[rbp+0x30]); `0x4e3a4b4  mov byte ptr [rbp+0x208],7` (tag byte=7). [V]
- Fields whose SOURCE DATA the producer sets (all of them, passed to builder): mMatrixA/mMatrixB (same ptr [rbp+0x240]), mBounds ([rbp+0x39C]), mMesh (rax), mValueB8 (0), mRefE0/mRefF0/mByte100/mRef108/mByte118/mRef120/mRef130 (refs block at [rbp+0x330]), mMaterial ([rbp+0x3C8]), mBlock154 ([rbp+0x2B0]), mBlockC0 ([rbp+0x2E8]), mBlockD0 ([rbp+0x2D8]), mFlags150 (f0=0,f1=1,f2=0,f3=0), mBlock164 ([rbp+0x338]), mValue174 (from block164), mCount178 (count=r9d), mVariantHead/mVariantByte/mVariantPayload/mVariantIndex (variant at [rbp+0x2F8]), mOverride ([rbp+0x28C]), mHasOverride (from override), mFlags1CC ([rbp+0x3C4]), mByte1CE (r8b). [V]

## VERDICT SUMMARY
- MATCH: mMatrixA(+0x000,16 floats), mMatrixB(+0x040,16 floats), mBounds(+0x080,6 floats, cond), mBoundsEmpty(+0x098, 0xFF default then 0 cond), mMeshVec4(+0x09C,4 floats), mMesh(+0x0B0), mValueB8(+0x0B8), mBlockC0(+0x0C0), mBlockD0(+0x0D0), mRefE0(+0x0E0,+1 strong), mRefF0(+0x0F0,+1 strong), mByte100(+0x100), mRef108(+0x108,+1 strong), mByte118(+0x118), mRef120(+0x120,+1 strong), mRef130(+0x130,+1 strong), mMaterial(+0x140,+1 strong), mFlags150(+0x150,4 bytes), mBlock154(+0x154), mBlock164(+0x164), mValue174(+0x174), mCount178(+0x178), mVariantHead(+0x180), mVariantByte(+0x190), mVariantPayload(+0x198 kind-0 u64 / kind-1 heap ptr, +0x1A0 zero), mVariantIndex(+0x1B0=0xFF default then kind), mOverride(+0x1B8,4 floats, cond), mHasOverride(+0x1C8=0 default then 1 cond), mFlags1CC(+0x1CC), mByte1CE(+0x1CE).
- MISMATCH: NONE.
- NOT-WRITTEN: mPad099(+0x099), mPad0AC(+0x0AC), mPad0BC(+0x0BC), mPad101(+0x101), mPad119(+0x119), mPad17A(+0x17A), mPad191(+0x191), mPad1B1(+0x1B1), mPad1C9(+0x1C9), trailing pad(+0x1CF) — all padding, expected (no store, no header store expected).
- All header fields + padding regions accounted for. Header size 0x1D0 consistent.

## VERIFICATION (verify_oc.py) — PENDING

## QUOTED INSTRUCTION LINES (for verify_oc.py)
0x668d386  movss [rcx],xmm0
0x668d38f  movss [rcx+4],xmm0
0x668d399  movss [rcx+8],xmm0
0x668d3a3  movss [rcx+0xC],xmm0
0x668d3ad  movss [rcx+0x10],xmm0
0x668d3b7  movss [rcx+0x14],xmm0
0x668d3c1  movss [rcx+0x18],xmm0
0x668d3cb  movss [rcx+0x1C],xmm0
0x668d3d5  movss [rcx+0x20],xmm0
0x668d3df  movss [rcx+0x24],xmm0
0x668d3e9  movss [rcx+0x28],xmm0
0x668d3f3  movss [rcx+0x2C],xmm0
0x668d3fd  movss [rcx+0x30],xmm0
0x668d407  movss [rcx+0x34],xmm0
0x668d411  movss [rcx+0x38],xmm0
0x668d41b  movss [rcx+0x3C],xmm0
0x668d425  movss [rcx+0x40],xmm0
0x668d430  movss [rcx+0x44],xmm0
0x668d43b  movss [rcx+0x48],xmm0
0x668d446  movss [rcx+0x4C],xmm0
0x668d451  movss [rcx+0x50],xmm0
0x668d45c  movss [rcx+0x54],xmm0
0x668d467  movss [rcx+0x58],xmm0
0x668d472  movss [rcx+0x5C],xmm0
0x668d47d  movss [rcx+0x60],xmm0
0x668d488  movss [rcx+0x64],xmm0
0x668d493  movss [rcx+0x68],xmm0
0x668d49e  movss [rcx+0x6C],xmm0
0x668d4a9  movss [rcx+0x70],xmm0
0x668d4b4  movss [rcx+0x74],xmm0
0x668d4bf  movss [rcx+0x78],xmm0
0x668d4ca  movss [rcx+0x7C],xmm0
0x668d4cf  mov byte ptr [rcx+0x98],0xFF
0x668d4e2  movss [rcx+0x80],xmm0
0x668d4f0  movss [rcx+0x84],xmm0
0x668d4fe  movss [rcx+0x88],xmm0
0x668d50c  movss [rcx+0x8C],xmm0
0x668d51a  movss [rcx+0x90],xmm0
0x668d528  movss [rcx+0x94],xmm0
0x668d530  mov byte ptr [rcx+0x98],0
0x668d53f  movss [rcx+0x9C],xmm0
0x668d54f  movss [rcx+0xA0],xmm0
0x668d55f  movss [rcx+0xA4],xmm0
0x668d56f  movss [rcx+0xA8],xmm0
0x668d577  mov [rcx+0xB0],rdi
0x668d57e  mov [rcx+0xB8],esi
0x668d588  movups [rcx+0xC0],xmm0
0x668d593  movups [rcx+0xD0],xmm0
0x668d59d  movups [rcx+0xE0],xmm0
0x668d5b4  mov [rcx+0xE0],rdx
0x668d5bf  mov [rcx+0xE8],rdx
0x668d5c6  movups [rcx+0xF0],xmm0
0x668d5de  mov [rcx+0xF0],rdx
0x668d5e9  mov [rcx+0xF8],rdx
0x668d5f4  mov [rcx+0x100],dl
0x668d5fa  movups [rcx+0x108],xmm0
0x668d612  mov [rcx+0x108],rdx
0x668d61d  mov [rcx+0x110],rdx
0x668d628  mov [rcx+0x118],dl
0x668d62e  movups [rcx+0x120],xmm0
0x668d64a  mov [rcx+0x120],rdx
0x668d655  mov [rcx+0x128],rdx
0x668d65c  movups [rcx+0x130],xmm0
0x668d6a5  mov [rcx+0x130],r14
0x668d6b0  mov [rcx+0x138],rax
0x668d6b7  movups [rcx+0x140],xmm0
0x668d6dc  mov [rcx+0x140],rax
0x668d6e7  mov [rcx+0x148],rax
0x668d6ee  mov [rcx+0x150],dil
0x668d6f5  mov [rcx+0x151],sil
0x668d6fc  mov [rcx+0x152],bl
0x668d702  mov [rcx+0x153],r10b
0x668d70d  movups [rcx+0x154],xmm0
0x668d718  movups [rcx+0x164],xmm0
0x668d723  mov [rcx+0x174],eax
0x668d73c  mov [rcx+0x178],dx
0x668d746  movups [rcx+0x180],xmm0
0x668d751  mov [rcx+0x190],al
0x668d757  mov byte ptr [rcx+0x1B0],0xFF
0x668d780  mov [rcx+0x198],rax
0x668d791  movups [rcx+0x1A0],xmm0
0x668d7ad  mov [rax],rdx
0x668d7b3  mov [rcx+0x1A8],rax
0x668d809  mov [rax],rsi
0x668d85e  mov [rcx+0x1B0],dil
0x668d87a  mov byte ptr [rcx+0x1C8],0
0x668d88d  movss [rcx+0x1B8],xmm0
0x668d89b  movss [rcx+0x1BC],xmm0
0x668d8a9  movss [rcx+0x1C0],xmm0
0x668d8b7  movss [rcx+0x1C4],xmm0
0x668d8bf  mov byte ptr [rcx+0x1C8],1
0x668d8c6  mov [rcx+0x1CC],dx
0x668d8cd  mov [rcx+0x1CE],al
0x6b86616  call 0x668D350
0x6b8668c  mov [rbp+0x310],rsi
0x6b86693  mov byte ptr [rbp+0x318],7
0x4e3a43e  call 0x668D350
0x4e3a4b4  mov byte ptr [rbp+0x208],7

## FACTS (from header, [I] = unverified until seen in disasm)
- Struct RenderSkinnedMeshDescription: sizeof 0x1D0 [static_assert, header only].
- +0x000 mMatrixA float[16]; +0x040 mMatrixB float[16]; +0x080 mBounds float[6]; +0x098 mBoundsEmpty u8 (0xFF = no bounds); +0x09C mMeshVec4 float[4]; +0x0B0 mMesh ptr; +0x0B8 mValueB8 u32; +0x0C0 mBlockC0 float[4]; +0x0D0 mBlockD0 float[4]; +0x0E0 mRefE0 SharedRef; +0x0F0 mRefF0 SharedRef; +0x100 mByte100 u8; +0x108 mRef108 SharedRef; +0x118 mByte118 u8; +0x120 mRef120 SharedRef; +0x130 mRef130 SharedRef; +0x140 mMaterial SharedRef; +0x150 mFlags150 u8[4]; +0x154 mBlock154 float[4]; +0x164 mBlock164 float[4]; +0x174 mValue174 u32; +0x178 mCount178 u16 (checked < 0x10000, throws otherwise); +0x180 mVariantHead u8[0x10]; +0x190 mVariantByte u8; +0x198 mVariantPayload u8[0x18]; +0x1B0 mVariantIndex u8 (0xFF = empty); +0x1B8 mOverride float[4]; +0x1C8 mHasOverride bool; +0x1CC mFlags1CC u16; +0x1CE mByte1CE u8.
- Tag 7 = Item group; tag store 'mov byte ptr [..],7' [V] at 0x6b86693 (clone) and 0x4e3a4b4 (producer).
- Builder 0x668d350: 21-argument constructor, called from both clone 0x6b84e60 (at 0x6b86616) and producer 0x4e39f20 (at 0x4e3a43e). [V]
- Second producer writes NO desc fields directly; all fields set by builder. [V]

## DONE
- Clone facts: builder callee 0x668d350 at 0x6b86616; desc at [rbp+0x60]; variant {desc,tag} at [rbp+0x310]/[rbp+0x318]; tag=7 [V]
- Builder store table: all fields MATCH or NOT-WRITTEN (padding), extracted via stores.py from builder_668d350_list.txt [V]
- Tag store documented [V]
- Second producer 0x4e39f20: sets NO desc fields directly; only variant tag at [rbp+0x208]=7 and prepares all builder source args [V]

## BLOCKED
- verify_oc.py not yet run

## TOOL REQUESTS
None | — | —
