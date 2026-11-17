## NEXT
DONE

# U-ED5b ChunkGeometry description — pending Q1/Q2 (D5b)

Checklist item D5b: "ChunkGeometry description: extracter + pointer route (6be); 6 live dumps (6iq); layout +0x00..+0x7F confirmed; +0xB8/+0xD8 byte flags vs live pointers unresolved; header asserts for the typed live fields pending".

Scope of this unit: ONLY the pending parts.
- Q1: is desc+0xB8 / desc+0xD8 a byte flag or the low byte of a live pointer?
- Q2: do the header static_asserts / typed fields match the live dumps?

Extractor: 0x66ea3d0 (Item tag 3, size 0xF430) [V]. Entered by tag-3 visitor tail-jump; r8=desc kept as r12 then rbx [V]. Live dumps: docs/data/live_chunk_desc_1.26.62.01.txt, 6 samples [V live].
Header under test: src/sdk/mc/deps/minecraft_renderer/framebuilder/ChunkGeometryDescription.h (ChunkGeometryDescriptionView), static_asserts lines 39-50 [V].

## Field table (one row per distinct offset, verbatim `0xRVA  instr` proof lines copied from rdis listings)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
| +0x00 | 8 | desc+0x00 (rbx=desc) | `0x66eb05e  mov rcx,[rbx]` | mShared0Ptr: shared_ptr object pointer | [V] |
| +0x08 | 8 | desc+0x08 (rbx=desc) | `0x66eafb8  mov rax,[rbx+8]` | mShared0Ctl: control-block pointer (ctl = object-0x10) | [V] |
| +0x10 | 8 | desc+0x10 (rbx=desc) | `0x66eb06f  lea r15,[rbx+0x10]` / `0x66eb090  mov rax,[r15]` | mShared1Ptr: second shared_ptr object pointer | [V] |
| +0x18 | 8 | desc+0x18 (rbx=desc) | `0x66eb07a  mov rax,[rbx+0x18]` / `0x66eb087  mov r14,[rbx+0x18]` | mShared1Ctl: second control-block pointer | [V] |
| +0x30 | 8 | desc+0x30 (rbx=desc) | `0x66eafd2  cmp qword ptr [rbx+0x30],2` | mBindingCount: compared with 2 (jb -> single-binding path); live = 3 | [V] |
| +0x38 | 4 | desc+0x38 (rax=desc via [rbp+0x16C0] @0x66ec562) | `0x66ec56d  imul rcx,[rax+0x38],0x58` | span count (dword); live varies 0x10..0x67 per sample | [V] |
| +0x40 | 8 | desc+0x40 (rax=desc via [rbp+0x16C0] @0x66ec562) | `0x66ec569  mov rdi,[rax+0x40]` | span data pointer (qword); live = stack vector ptr per sample | [V] |
| +0x48 | 8 | desc+0x48 (r12/rbx=desc) | `0x66ea58f  mov rax,[r12+0x48]` / `0x66eafa4  mov rax,[rbx+0x48]` | mPassKind: pointer into .data holding pass kind K | [V] |
| +0x50 | 1 | desc+0x50 (r12=desc) | `0x66ea5ba  cmp byte ptr [r12+0x50],0` | mFlag50: selects predicate set; live 0/1 across samples | [V] |
| +0x54 | 16 | desc+0x54 (rbx=desc) | `0x66eb99e  movups xmm0,[rbx+0x54]` | FogColor f32x4; live {0.0403,0.0494,0.09,1.0} all samples | [V] |
| +0x64 | 16 | desc+0x64 (rbx=desc) | `0x66eb91a  movups xmm0,[rbx+0x64]` | FogAndDistanceControl f32x4; live {0.656,1.0,128,57} all samples | [V] |
| +0x74 | 4 | desc+0x74 (rbx=desc) | `0x66eb6c2  movss xmm0,[rbx+0x74]` | mTime f32; live 348.04 all samples | [V] |
| +0xB8 | 1 | desc+0xB8 (r12/rbx=desc) | `0x66ea56e  movzx eax,byte ptr [r12+0xB8]` / `0x66eb6bb  movzx eax,byte ptr [rbx+0xB8]` / `0x66ebca3  cmp byte ptr [rbx+0xB8],0` | mFlagB8 byte: MeshContext.x / ViewPositionAndTime selector; read as byte by extractor [V]; live low byte always 0x00 [V live] | [V] instr / [?] live |
| +0xD8 | 1 | desc+0xD8 (r12=desc) | `0x66ea72e  cmp byte ptr [r12+0xD8],3` | mModeD8 byte: compared with 3; read as byte by extractor [V]; live low byte always 0x00 [V live] | [V] instr / [?] live |
| +0xE0 | 1 | desc+0xE0 (r12=desc) | `0x66ea65c  movzx ebx,byte ptr [r12+0xE0]` | mFlagE0 byte | [V] |
| +0xE1 | 1 | desc+0xE1 (r12=desc) | `0x66ea76f  cmp byte ptr [r12+0xE1],0` | mFlagE1 byte; live = 1 all samples | [V] |
| +0xE4 | 8 | desc+0xE4 (rbx=desc) | `0x66eb758  movsd xmm2,[rbx+0xE4]` | mViewPos.xyz f32x3 (+0xE4..+0xEC; +0xEC also read via movss at 0x66eb750); live -0,-0,-0 | [V] |

## Verbatim proof lines (standalone for verify_oc)
0x66eb05e  mov rcx,[rbx]
0x66eafb8  mov rax,[rbx+8]
0x66eb06f  lea r15,[rbx+0x10]
0x66eb090  mov rax,[r15]
0x66eb07a  mov rax,[rbx+0x18]
0x66eb087  mov r14,[rbx+0x18]
0x66eafd2  cmp qword ptr [rbx+0x30],2
0x66ec56d  imul rcx,[rax+0x38],0x58
0x66ec569  mov rdi,[rax+0x40]
0x66ea58f  mov rax,[r12+0x48]
0x66eafa4  mov rax,[rbx+0x48]
0x66ea5ba  cmp byte ptr [r12+0x50],0
0x66eb99e  movups xmm0,[rbx+0x54]
0x66eb91a  movups xmm0,[rbx+0x64]
0x66eb6c2  movss xmm0,[rbx+0x74]
0x66ea56e  movzx eax,byte ptr [r12+0xB8]
0x66eb6bb  movzx eax,byte ptr [rbx+0xB8]
0x66ebca3  cmp byte ptr [rbx+0xB8],0
0x66ebd92  cmp byte ptr [rbx+0xB8],0
0x66ea72e  cmp byte ptr [r12+0xD8],3
0x66ea65c  movzx ebx,byte ptr [r12+0xE0]
0x66ea76f  cmp byte ptr [r12+0xE1],0
0x66eb758  movsd xmm2,[rbx+0xE4]

## Q1: +0xB8 / +0xD8 byte flag vs live pointer

The extractor reads desc+0xB8 as a single byte at 5+ sites (`movzx eax,byte ptr [r12+0xB8]`, `movzx edx,byte ptr [r12+0xB8]`, `movzx eax,byte ptr [rbx+0xB8]`, `cmp byte ptr [rbx+0xB8],0` x2) and desc+0xD8 as a single byte (`cmp byte ptr [r12+0xD8],3`) [V by instruction]. This matches the header's `uint8_t mFlagB8` / `uint8_t mModeD8` byte interpretation [V].

Live dumps: the qwords at +0xB8 and +0xD8 are heap/exe pointers (0x...300 / 0x...000 / exe base) whose low byte is always 0x00 across all 6 samples [V live]. Because every sample reads 0x00, the live data cannot distinguish "genuine byte flag that happens to be 0" from "low byte of an aligned pointer" [?]. No non-zero live case found.

Q1 status: byte-access nature proven [V]; live semantic (flag vs pointer low byte) unresolved [?] — no non-zero sample.

## Q2: header static_asserts / typed fields vs live dumps

Every header-claimed typed field has verbatim instruction proof and matches live values [V]:
- +0x00/+0x08/+0x10/+0x18 shared_ptr pairs: object ptr + control-block-ptr (ctl = object-0x10) confirmed by `mov rcx,[rbx]` / `mov rax,[rbx+8]` / `lea r15,[rbx+0x10]` / `mov rax,[rbx+0x18]` [V] + live (all 6 samples: ptr and ptr-0x10) [V live].
- +0x30 mBindingCount = 3, compared with 2 at `cmp qword ptr [rbx+0x30],2` [V] + live = 3 [V live].
- +0x48 mPassKind ptr into .data holding K [V] + live varies by key [V live].
- +0x50 mFlag50 byte [V] + live 0/1 [V live].
- +0x54 FogColor f32x4 via `movups` [V] + live identical {0.0403,0.0494,0.09,1.0} [V live].
- +0x64 FogAndDistance f32x4 via `movups` [V] + live identical {0.656,1.0,128,57} [V live].
- +0x74 mTime f32 via `movss` [V] + live 348.04 [V live].
- +0xB8 mFlagB8 byte [V] + live 0 [V live].
- +0xD8 mModeD8 byte [V] + live 0 [V live].
- +0xE0 mFlagE0 byte [V] + live 0 [V live].
- +0xE1 mFlagE1 byte [V] + live 1 [V live].
- +0xE4 mViewPos f32x3 via `movsd`/`movss` [V] + live -0,-0,-0 [V live].

All static_asserts (lines 39-50: +0x10,+0x30,+0x48,+0x50,+0x54,+0x64,+0x74,+0xB8,+0xD8,+0xE0,+0xE1,+0xE4) are consistent with observed accesses [V].

Correction (refutes header): header claims +0x38..+0x47 is `mPad38` [?] padding. Disassembly reads +0x38 as a count (`imul rcx,[rax+0x38],0x58`) and +0x40 as a pointer (`mov rdi,[rax+0x40]`) [V]. Live confirms +0x38 = varying count and +0x40 = varying stack vector ptr [V live]. So +0x38/+0x40 are a {count, ptr} span, NOT padding — header field mPad38 is wrong [V].

Still undecoded (no instruction access observed): +0x20..+0x2F (mPad20), +0x78..+0xB7 (mPad78), +0xB9..+0xD7 (mPadB9), +0xD9..+0xDF (mPadD9), +0xE2..+0xE3 (mPadE2) — remain [?].

## CLOSES?
NO — Q1 byte-access nature is [V]-proven but the live semantic of +0xB8/+0xD8 is [?]: all 6 samples read low byte 0x00 because the containing qwords are aligned heap/exe pointers, and no non-zero live case was found to prove they are real byte flags rather than pointer low bytes. Q2 is [V]-proven for every typed field (with +0x38/+0x40 corrected from pad to count/ptr).

## TOOL REQUESTS
None.
