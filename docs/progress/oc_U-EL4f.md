## NEXT
DONE

# U-EL4f ChunkGeometry description field layout from live capture — D5b pending part

Checklist item D5b (docs/RENDER_CHECKLIST.md): "ChunkGeometry description: extractor + pointer route (6be); 6 live dumps (6iq); layout +0x00..+0x7F confirmed; +0xB8/+0xD8 byte flags vs live pointers unresolved; header asserts for the typed live fields pending". Cited sections: docs/BGFX_MAP.md 6be (line 813, extractor anchor) and 6iq (lines 2056-2058, live dump method).
This unit does ONLY the pending part: the description field layout, decoded from the 6 live dumps with verbatim disassembly proof. Extractor bodies A-D, dedicated builders and the Item visitor are out of scope (closed via 6be / E4 / D5c).

Extractor: 0x66ea3d0, Item tag 3, size 0xF430 [V]. Entered by tag-3 visitor tail-jump; r8 = desc at entry, kept as r12 then rbx [V]. Live dumps: docs/data/live_chunk_desc_1.26.62.01.txt, 6 samples x 0x200 bytes, format "n r8=ADDR K=N key=A:B:C hex" (hex = 0x200 bytes at r8, memory order) [V live]. Verbatim proof lines: docs/data/listings/e4_A.txt (head listing 0x66ea3d0..0x66ec64c, copied verbatim from the exe; each proof line below has two spaces after the address).
Header under test: src/sdk/mc/deps/minecraft_renderer/framebuilder/ChunkGeometryDescription.h (ChunkGeometryDescriptionView; static_asserts lines 39-50) [V].

## (1) Field table — one row per distinct offset with evidence; size from the instruction; meaning only where an instruction/string shows it

| name (meaning) | offset | size | verbatim `0xRVA  instr` proof line | tag |
|---|---|---|---|---|
| mShared0Ptr = shared_ptr object pointer | +0x00 | 8 | `0x66eb05e  mov rcx,[rbx]` | [V] |
| mShared0Ctl = shared_ptr control block; live ctl = object - 0x10 | +0x08 | 8 | `0x66eafb8  mov rax,[rbx+8]` | [V] |
| mShared1Ptr = shared_ptr object pointer (2nd pair) | +0x10 | 8 | `0x66eb06f  lea r15,[rbx+0x10]` / `0x66eb090  mov rax,[r15]` | [V] |
| mShared1Ctl = shared_ptr control block (2nd pair) | +0x18 | 8 | `0x66eb07a  mov rax,[rbx+0x18]` | [V] |
| mShared2Ptr = shared_ptr object pointer (3rd pair); &desc+0x20 taken and passed to 0xBCAB8F0; live ctl = object - 0x10 | +0x20 | 8 | `0x66eb460  lea r9,[rbx+0x20]` | [V] / [V live] |
| mBindingCount = 3, compared against 2 (jb -> single-binding path) | +0x30 | 8 | `0x66eafd2  cmp qword ptr [rbx+0x30],2` / `0x66eb40c  cmp qword ptr [rbx+0x30],3` | [V] |
| mSpanCount = count of desc+0x40 span entries; u64 limit 0xAAAAAAAAAAAAAAB | +0x38 | 8 | `0x66ec257  mov rax,[rax+0x38]` (rax=desc) / `0x66ec56d  imul rcx,[rax+0x38],0x58` | [V] |
| mSpanPtr = span data pointer (stack vector) | +0x40 | 8 | `0x66ec2de  mov rdi,[rcx+0x40]` (rcx=desc) / `0x66ec569  mov rdi,[rax+0x40]` | [V] |
| mPassKind = pointer into module data holding pass-kind K; *(u64*)pointee compared with 1 / 0xB / 0xC / 0xA | +0x48 | 8 | `0x66ea58f  mov rax,[r12+0x48]` / `0x66eafa4  mov rax,[rbx+0x48]` / `0x66eafa8  cmp qword ptr [rax],1` | [V] |
| mFlag50 byte = selects predicate set | +0x50 | 1 | `0x66ea5ba  cmp byte ptr [r12+0x50],0` | [V] |
| FogColor f32x4 loaded via movups; written as FogColor uniform by 0x5679db0 context | +0x54 | 16 | `0x66eb99e  movups xmm0,[rbx+0x54]` | [V] |
| FogAndDistanceControl f32x4 loaded via movups | +0x64 | 16 | `0x66eb91a  movups xmm0,[rbx+0x64]` | [V] |
| mTime f32 = ViewPositionAndTime.w | +0x74 | 4 | `0x66eb6c2  movss xmm0,[rbx+0x74]` | [V] |
| mFlagB8 byte = MeshContext.x / ViewPositionAndTime + Fog selector; tested against 0 at 6 sites | +0xB8 | 1 | `0x66ea56e  movzx eax,byte ptr [r12+0xB8]` / `0x66ea6e4  movzx edx,byte ptr [r12+0xB8]` / `0x66eb5f0  movzx eax,byte ptr [rbx+0xB8]` / `0x66eb6bb  movzx eax,byte ptr [rbx+0xB8]` / `0x66ebca3  cmp byte ptr [rbx+0xB8],0` / `0x66ebd92  cmp byte ptr [rbx+0xB8],0` / `0x66ebfa0  cmp byte ptr [rbx+0xB8],0` | [V] |
| mModeD8 byte = compared with 3 (isMode3 gate for inline bodies B-D) | +0xD8 | 1 | `0x66ea72e  cmp byte ptr [r12+0xD8],3` | [V] |
| mFlagE0 byte | +0xE0 | 1 | `0x66ea65c  movzx ebx,byte ptr [r12+0xE0]` | [V] |
| mFlagE1 byte | +0xE1 | 1 | `0x66ea76f  cmp byte ptr [r12+0xE1],0` | [V] |
| mViewPos.xyz f32x3 = ViewPositionAndTime.xyz; movsd reads +0xE4..+0xEB (x+y), movss +0xEC (z) | +0xE4 | 8 | `0x66eb758  movsd xmm2,[rbx+0xE4]` | [V] |
| mViewPos.z f32 | +0xEC | 4 | `0x66eb750  movss xmm1,[rbx+0xEC]` | [V] |

## (2) Live capture verification — docs/data/live_chunk_desc_1.26.62.01.txt (samples 1..6)

| offset | sample 1 | sample 2 | sample 3 | sample 4 | sample 5 | sample 6 |
|---|---|---|---|---|---|---|
| +0x00 mShared0Ptr | 0x000003463D4D4AE0 | 0x000003463D4D4AE0 | 0x000003463D4D4AE0 | 0x000003463D4D4AE0 | 0x000003463D4D4AE0 | 0x000003463D4D4AE0 |
| +0x08 mShared0Ctl | obj-0x10 (...4AD0) | obj-0x10 (...4AD0) | obj-0x10 (...4AD0) | obj-0x10 (...4AD0) | obj-0x10 (...4AD0) | obj-0x10 (...4AD0) |
| +0x10 mShared1Ptr | 0x000003463D079B80 | 0x000003463D079B80 | 0x000003463D079B80 | 0x000003463D079B80 | 0x000003463D079B80 | 0x000003463D079B80 |
| +0x18 mShared1Ctl | obj-0x10 (...9B70) | obj-0x10 (...9B70) | obj-0x10 (...9B70) | obj-0x10 (...9B70) | obj-0x10 (...9B70) | obj-0x10 (...9B70) |
| +0x20 mShared2Ptr | 0x000003463EDAC100 | 0x000003463EDAC100 | 0x000003463EDAC100 | 0x000003463EDAC100 | 0x000003463EDAC100 | 0x000003463EDAC100 |
| +0x28 mShared2Ctl | obj-0x10 (...C0F0) | obj-0x10 (...C0F0) | obj-0x10 (...C0F0) | obj-0x10 (...C0F0) | obj-0x10 (...C0F0) | obj-0x10 (...C0F0) |
| +0x30 mBindingCount | 3 | 3 | 3 | 3 | 3 | 3 |
| +0x38 mSpanCount | 0x45 | 0x25 | 0x33 | 0x67 | 0x10 | 0x2B |
| +0x40 mSpanPtr | 0x48AB208 | 0x4ACB208 | 0x4BDB208 | 0x479B208 | 0x4DFB208 | 0x4DFB208 |
| +0x48 mPassKind ptr | 0x00007FF7F8B04A20 | ...4BE0 | ...4A80 | ...4A20 | ...4AE0 | ...4AE0 |
| +0x50 mFlag50 | 0 | 0 | 0 | 1 | 0 | 1 |
| +0x54 FogColor f32x4 | {0.0402,0.0494,0.09,1.0} | same | same | same | same | same |
| +0x64 FogAndDistance f32x4 | {0.6562,1.0,128.0,57.0} | same | same | same | same | same |
| +0x74 mTime f32 | 348.04 | 348.04 | 348.04 | 348.04 | 348.04 | 348.04 |
| +0xB8 mFlagB8 | byte 0; qword 0x000003459E160300 | byte 0; qword 0x000003459E160300 | byte 0; qword 0x000003459E160300 | byte 0; qword 0 | byte 0; qword 0x000003459E160300 | byte 0; qword 0x000003459E160300 |
| +0xD8 mModeD8 | byte 0; qword 0x00007FF7F8363000 | byte 0; qword 0x00007FF7F8363000 | byte 0; qword 0x00007FF988A33000 | byte 0; qword 0x00007FF7F8363000 | byte 0; qword 0x00007FF7F8363000 | byte 0; qword 0x00007FF7F8363000 |
| +0xE0 mFlagE0 | 0 | 0 | 0 | 0 | 0 | 0 |
| +0xE1 mFlagE1 | 1 | 1 | 1 | 1 | 1 | 1 |
| +0xE4 mViewPos.x | -0.0 | -0.0 | -0.0 | -0.0 | -0.0 | -0.0 |
| +0xEC mViewPos.z | -0.0 | -0.0 | -0.0 | -0.0 | -0.0 | -0.0 |

(+0xE8 = mViewPos.y = -0.0, read as the high dword of the +0xE4 movsd load.)

## Q1: +0xB8 / +0xD8 — byte flag or low byte of a live pointer?

Byte access is proven [V]: desc+0xB8 is read as a single byte at 6 sites (`movzx eax,byte ptr [r12+0xB8]` @0x66ea56e / [rbx+0xB8] @0x66eb6bb; `cmp byte ptr [rbx+0xB8],0` @0x66ebca3, @0x66ebd92, @0x66ebfa0; `movzx edx,byte ptr [r12+0xB8]` @0x66ea6e4) and desc+0xD8 via `cmp byte ptr [r12+0xD8],3` @0x66ea72e. That matches the header's uint8_t reading for the byte the code actually tests [V].

Live storage refutes "flag byte + pad": the qword at +0xB8 is 0x000003459E160300 in samples 1,2,3,5,6 and 0 in sample 4; the qword at +0xD8 is 0x00007FF7F8363000 in samples 1,2,4,5,6 and 0x00007FF988A33000 in sample 3 [V live]. The low byte is 0x00 in every sample (so the flag the extractor tests is always 0) [V live], while the remaining 7 bytes are non-zero, pointer-shaped values (heap 0x00000345xxxxxx range, matching the shared_ptr object range at +0x00; module 0x7FF7xxxxxxx / 0x7FF9xxxxxxx range) [V live values; module/heap range classification [I]].

Conclusion: +0xB8/+0xD8 are qword-wide storage (pointer or NULL); the extractor tests only the low byte as a flag. The header's `uint8_t` + pad annotation is wrong at the storage level [V live]; the code-visible semantic (byte compared with 0 / 3) is [V]. Residual [?]: a non-zero byte at +0xB8/+0xD8 was never observed in 6 samples, so semantics when non-zero are undecided — non-blocking for the layout.

## Q2: header static_asserts vs live dumps

static_asserts lines 39-50 (+0x10,+0x30,+0x48,+0x50,+0x54,+0x64,+0x74,+0xB8,+0xD8,+0xE0,+0xE1,+0xE4) are consistent with observed accesses [V] and match all 6 live dumps [V live]:
- +0x00/+0x08/+0x10/+0x18: shared_ptr pairs with ctl = object-0x10 [V instr] + [V live].
- +0x20/+0x28: the header's mPad20 [?] is WRONG — a third shared_ptr pair (ctl = object-0x10 in all 6 samples) [V live]; address of +0x20 taken by `lea r9,[rbx+0x20]` @0x66eb460 [V].
- +0x30 mBindingCount = 3 vs `cmp qword ptr [rbx+0x30],2` [V] + live = 3 [V live].
- +0x38/+0x40: the header's mPad38 [?] is WRONG — {count, ptr} span (count varies 0x10..0x67; ptr is a stack vector per sample) [V instr `mov rax,[rax+0x38]` / `mov rdi,[rcx+0x40]`] + [V live].
- +0x48 mPassKind module pointer [V] + live varies per key [V live].
- +0x50 mFlag50 byte 0/1 across samples [V] + [V live].
- +0x54 FogColor {0.0402,0.0494,0.09,1.0} ×6 [V movups] + [V live].
- +0x64 FogAndDistance {0.6562,1.0,128.0,57.0} ×6 [V movups] + [V live].
- +0x74 mTime 348.04 ×6 [V movss] + [V live].
- +0xB8/+0xD8: see Q1 [V instr] + [V live].
- +0xE0 = 0, +0xE1 = 1 ×6 [V] + [V live]; +0xE4/+0xE8/+0xEC = -0.0,-0.0,-0.0 ×6 [V movsd/movss] + [V live].

Undecoded, no instruction access in the extractor head (out of scope: bodies A-D may touch them): +0x78..+0xB7 (mPad78), +0xC0, +0xC8, +0xD0 (live shows pointer/f32 data there, no head access), +0xF0.. → [?].

## CLOSES?
YES — every pending part of item D5b is proven by [V] rows: the full typed field layout (+0x00..+0xEC) has verbatim disassembly proof [V] and matches all 6 live dumps [V live]; +0xB8/+0xD8 are resolved as qword-wide storage (pointer or NULL) whose low byte the extractor reads as a flag [V instr + V live]; header static_asserts verified [V], with corrections (+0x20/+0x28 third shared pair, +0x38/+0x40 span count/ptr, +0xB8/+0xD8 qword pointers — none of them pad). Residual non-blocking [?]: non-zero +0xB8/+0xD8 byte never observed (all 6 samples read 0x00); undecoded pad regions have no instruction access and are outside this item.

## TOOL REQUESTS
live-dump parser | docs/data/live_chunk_desc_1.26.62.01.txt -> per-offset u64/f32 decode table | inline python3 one-liner (not saved); no general tool exists to decode live capture hex dumps, doing it by hand is error-prone
