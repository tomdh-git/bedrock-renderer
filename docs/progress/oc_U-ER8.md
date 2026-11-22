## NEXT
DONE

# UNIT U-ER8 — R8 Light tags 6 and 7: payload behind the shared pair; VoxelVolume queue destination after 0x66421a9

Goal: close checklist item R8 (docs/RENDER_CHECKLIST.md). Only the pending parts: (a) payload behind the shared pair in Light tags 6/7 cases, (b) VoxelVolume queue destination after 0x66421a9 (tag 7 case head).

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), static analysis only, RVAs image-relative.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Source data read fully: docs/data/listings/light_visitor_6640d80_6645400.txt (tag 6 case head ~lines 530-714; tag 7 head + dword-array memcpy ~990-1090; pass lookup/record push/queues ~1181-1330; tag 6 epilogue ~2374-2433), docs/progress/_lightB_data.txt (merged read lists t6/t7), docs/functions/6640d80_light_visitor.md (case walk + producer), docs/progress/descriptions.md R8 entry, docs/BGFX_MAP.md sections 6em (tag->type correction) and 6ih (first reads).

Tag->type (BGFX_MAP 6em [V]): producer 0x53599d0 stores tag 6 at 0x535ad34 (VoxelVolumeDescription, desc [rbp+0x270]) and tag 7 at 0x535aeb9 (TransitioningVoxelVolumeDescription, desc [rbp+0xC0]). Jump table 0xF2BF2B0: tag 6 -> 0x664187d, tag 7 -> 0x6641524 [V]. Description register = rsi in both cases [V].

## Part A — payload behind the shared pair (tags 6 and 7)

desc+0x00 and desc+0x08 are each a POINTER to a shared pair {object head, control block}; they are not inline structs. Case head (tag 6): `0x664187d mov rax,[rsi]` reads pair A pointer; rcx = [rax+8] = control block; `0x6641897 lock inc dword ptr [rcx+8]` bumps the strong use count [V]; `0x66418a2 movups xmm0,[rax]` copies the object's first 16 bytes into local slot [rbp+0xB10], which becomes VoxelRecord +0x00 [V]. Tag 7 identical for pair A: `0x664213a mov rax,[rsi]`; `0x664214d lock inc dword ptr [rcx+8]`; `0x664215b movaps [rbp+0xB10],xmm0` [V].

desc+0x08 = pair B pointer: tag 6 `0x6641b3a mov rax,[rsi+8]` -> [rbp+0xB20] -> VoxelRecord +0x10 [V]; tag 7 `0x66421a9 mov rax,[rsi+8]` -> [rbp+0xB20] (`0x66421ce movaps [rbp+0xB20],xmm0`) -> VoxelRecord +0x10 [V].

On exit each case releases its old local pair: strong `lock dec dword ptr [+8]` / weak `lock dec dword ptr [+0xC]`, then object and control-block destructors via `call qword ptr [0xF99FFA0]` ([ctrl+8]=strong refcount, [ctrl+0xC]=weak per BGFX_MAP 6em) [V]. No instruction in either tag case reads the object's fields beyond byte 16 or names its dynamic type -> object type behind the pair is not statically provable ([?] transparency row only; the payload the code actually moves — 16-byte object head plus strong/weak control block — is proven [V]).

## Part B — VoxelVolume queue destination after 0x66421a9

Tag 7: `0x66421a9 mov rax,[rsi+8]` (desc+0x08 = pair B) -> [rbp+0xB20] -> VoxelRecord +0x10 -> pass+0x138, a vector of 0x40-byte VoxelRecords. The record is move-emplaced by `0x664266c call 0x67D5FF0` with rcx = [rax+0x138] (pass pointer rsi loaded at `0x6642620 mov rsi,rax` after the lookup at 0x6642611-0x6642620) [V].

Tag 6: its desc+0x08 read `0x6641b3a mov rax,[rsi+8]` reaches the same pass+0x138 queue: record build at 0x66423e1-0x664242b, pass lookup `0x6642441 mov rsi,rax` (after `0x6642432 mov ecx,0x9D0; add rcx,[rdi+0x10]; call 0x5ABA5C0`), then `0x664248d call 0x67D5FF0` with rdx = [rbp+0xBE8] (the local record holding pair A at +0x00 and pair B at +0x10) [V]. Tag 6's VoxelRecord queue index: `0x6642493 mov eax,[rsi+0x140]` (queue end), `0x6642499 sub eax,[rsi+0x138]` (queue begin), `shr eax,6` -> record+0xAE [V]. Tag 7 equivalent: `0x6642672 mov eax,[rsi+0x140]`, `0x6642678 sub eax,[rsi+0x138]` [V]; tag 7 record+0x08 qword = 0xA000 [V] (tag 6: 0x8004 at 0x6643aa1 [V]).

Extra queues proven incidentally: tag 6 appends one byte to the pass+0x270/+0x278/+0x280 triplet (`0x66424c1 mov rbx,[rsi+0x278]`, `0x66424d4 mov [rsi+0x278],rbx` end += 1 [V]); the appended byte is never stored -> queued element unwritten [I]. Tag 7 appends a 0x20-byte TransitionRecord {desc+0x18 qword -> +0x00; dword array desc+0x38/+0x40 memcpy'd via `0x664212b call 0xEEC6DE0` -> +0x08..+0x18} to pass+0x168/+0x170/+0x178 (`0x66426ea add qword ptr [rsi+0x170],0x20` [V]).

## Answer table (one row per distinct offset, all its sites listed; verbatim lines copied from the listing = exe dump)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning |
| 0x00 (t6) | 8 | 0x664187d, 0x6643b74, 0x6643b91, 0x6643ba6, 0x6643bc8, 0x6643bdd, 0x6643c50, 0x6643c65, 0x6643c8f, 0x6643ca8 | `0x664187d  mov rax,[rsi]` | desc+0x00 = pointer to shared pair {object head, control block} [V]; control block [rax+8], strong count `lock inc dword ptr [rcx+8]` 0x6641897 [V]; object head 16 B `movups xmm0,[rax]` 0x66418a2 -> [rbp+0xB10] -> VoxelRecord +0x00 [V]. Epilogue releases local pair slots: `movups [rsi],xmm0` 0x6643b74 zeroes slot [rbp+0xC10] [V]; `lock dec dword ptr [rsi+8]` 0x6643b8b..0x6643c85 strong [V]; `lock dec dword ptr [rsi+0xC]` 0x6643ba0..0x6643c9e weak [V]; dtors via `call qword ptr [0xF99FFA0]` [V]. Object type beyond byte 16 not shown [?]. |
| 0x08 (t6) | 8 | 0x6641b3a, 0x6643ad8, 0x6643af4, 0x6643b8b, 0x6643bc2, 0x6643c4a, 0x6643c85 | `0x6641b3a  mov rax,[rsi+8]` | desc+0x08 = pair B pointer -> [rbp+0xB20] -> VoxelRecord +0x10 [V]. After pass lookup rsi = pass: `add qword ptr [rsi+8],0xC8` 0x6643af4 pass stream write cursor += 0xC8 (DrawItem record) [V]; epilogue `lock dec dword ptr [rsi+8]` 0x6643b8b/0x6643bc2/0x6643c4a/0x6643c85 strong on local slots [V]. |
| 0x0C (t6) | 4 | 0x6643ba0, 0x6643bd7, 0x6643c5f, 0x6643c9e | `0x6643ba0  lock dec dword ptr [rsi+0xC]` | epilogue weak-count lock-dec on local pair slots [V] |
| 0x10 (t6) | 8 | 0x6641bb4, 0x6643adc, 0x6643b77 | `0x6641bb4  mov r13,[rsi+0x10]` | desc+0x10 qword -> [rbp+0xB30] -> VoxelRecord +0x20 [V]; epilogue `mov qword ptr [rsi+0x10],0` 0x6643b77 zeroes local slot +0x10 [V] |
| 0x18 (t6) | 8 | 0x6641bd8, 0x66422df | `0x6641bd8  mov rcx,[rsi+0x18]` | vector begin (8-byte elements) -> record vector block +0x28..+0x38 [V] |
| 0x20 (t6) | 8 | 0x6641bd4, 0x66422e3 | `0x6641bd4  mov rbx,[rsi+0x20]` | vector end -> record vector block +0x28..+0x38 [V] |
| 0x138 (t6) | 4 | 0x6642499 | `0x6642499  sub eax,[rsi+0x138]` | after pass lookup rsi = pass at 0x6642441: pass+0x138 = VoxelRecord queue begin [V]; `(end-begin)>>6` -> record+0xAE [V] |
| 0x140 (t6) | 4 | 0x6642493 | `0x6642493  mov eax,[rsi+0x140]` | pass+0x140 = VoxelRecord queue end [V] |
| 0x270 (t6) | 8 | 0x66424e3, 0x66439ee, 0x6643a03, 0x6643a15, 0x6643a2a, 0x6643a36, 0x6643a6a, 0x6643aa9 | `0x66424e3  sub r15,[rsi+0x270]` | pass+0x270 = 1-byte element queue begin (rsi = pass) [V] |
| 0x278 (t6) | 8 | 0x66424c1, 0x66424d4, 0x66439df, 0x6643a03, 0x6643a74, 0x6643ab1 | `0x66424c1  mov rbx,[rsi+0x278]` | pass+0x278 = queue end [V]; `inc rbx; mov [rsi+0x278],rbx` 0x66424c1/0x66424d4 appends ONE byte — the appended byte is never stored, so the queued element is unwritten [I] |
| 0x280 (t6) | 8 | 0x66424c8, 0x6643a36, 0x6643a7e | `0x66424c8  cmp rbx,[rsi+0x280]` | pass+0x280 = queue cap [V] |
| 0x00 (t7) | 8 | 0x664213a | `0x664213a  mov rax,[rsi]` | pair A pointer -> [rbp+0xB10] -> VoxelRecord +0x00 [V] |
| 0x08 (t7) | 8 | 0x66421a9, 0x6643f7a, 0x6643f96 | `0x66421a9  mov rax,[rsi+8]` | pair B pointer -> [rbp+0xB20] -> VoxelRecord +0x10 -> pass+0x138 VoxelRecord queue via `call 0x67D5FF0` 0x664266c [V]. THIS is the VoxelVolume queue destination after 0x66421a9 [V]; `add qword ptr [rsi+8],0xC8` 0x6643f96 pass stream end += 0xC8 after lookup [V] |
| 0x10 (t7) | 8 | 0x6642223, 0x6643f7e | `0x6642223  mov r12,[rsi+0x10]` | desc+0x10 qword -> [rbp+0xB30] -> VoxelRecord +0x20 (`mov [rbp+0xC20],r12` 0x66425ea) [V] |
| 0x18 (t7) | 8 | 0x6641524 | `0x6641524  mov rax,[rsi+0x18]` | qword -> [rbp+0xAC0] -> TransitionRecord +0x00 [V] |
| 0x20 (t7) | 8 | 0x6642244, 0x664236e | `0x6642244  mov rcx,[rsi+0x20]` | vector begin (8-byte elements) -> TransitionRecord +0x28..+0x38 [V] |
| 0x28 (t7) | 8 | 0x6642240, 0x6642372 | `0x6642240  mov rbx,[rsi+0x28]` | vector end -> TransitionRecord +0x28..+0x38 [V] |
| 0x38 (t7) | 8 | 0x6641548, 0x664211a | `0x6641548  mov rcx,[rsi+0x38]` | dword-array begin; memcpy'd with `call 0xEEC6DE0` 0x664212b -> TransitionRecord +0x08..+0x18 {begin,end,cap} [V] |
| 0x40 (t7) | 8 | 0x6641544, 0x664211e | `0x6641544  mov rbx,[rsi+0x40]` | dword-array end [V] |
| 0x138 (t7) | 4 | 0x6642678 | `0x6642678  sub eax,[rsi+0x138]` | pass+0x138 VoxelRecord queue begin; `(end-begin)>>6` -> record+0xAE [V] |
| 0x140 (t7) | 4 | 0x6642672 | `0x6642672  mov eax,[rsi+0x140]` | pass+0x140 VoxelRecord queue end [V] |
| 0x168 (t7) | 8 | 0x66426fa, 0x6643d21, 0x6643e3d, 0x6643ec7, 0x6643f01, 0x6643f4e | `0x66426fa  sub r13,[rsi+0x168]` | pass+0x168 = TransitionRecord queue begin (0x20-byte elements), rsi = pass after lookup [V] |
| 0x170 (t7) | 8 | 0x66426a1, 0x66426ea, 0x6643d28, 0x6643d8d, 0x6643e4d, 0x6643f0f, 0x6643f48 | `0x66426a1  mov r12,[rsi+0x170]` | pass+0x170 = TransitionRecord queue end [V]; `add qword ptr [rsi+0x170],0x20` 0x66426ea appends one TransitionRecord [V] |
| 0x178 (t7) | 8 | 0x66426a8, 0x6643ece, 0x6643f19 | `0x66426a8  cmp r12,[rsi+0x178]` | pass+0x178 = TransitionRecord queue cap [V] |

## CLOSES?
YES — every pending part of R8 is now proven by [V] rows: (a) payload behind the shared pair: desc+0x00/+0x08 are pointers to shared pairs {object head, control block}; the object head (16 B) is copied via `movups xmm0,[rax]` (`0x66418a2` / `0x664215b movaps`) into VoxelRecord +0x00/+0x10 and the control block at [rax+8] is strong use-counted (`lock inc dword ptr [rcx+8]` at 0x6641897 / 0x664214d / 0x6641b51) and released with `lock dec [+8]` / `lock dec [+0xC]` plus dtors via `call qword ptr [0xF99FFA0]` [V]; no instruction reads/typifies the object beyond byte 16 so its dynamic type is not statically provable ([?] transparency row only — not part of the item line). (b) VoxelVolume queue destination after 0x66421a9: `0x66421a9 mov rax,[rsi+8]` (desc+0x08) -> pair B -> [rbp+0xB20] -> VoxelRecord +0x10 -> pass+0x138 vector of 0x40-byte VoxelRecords via move-emplace `call 0x67D5FF0` at 0x664266c [V]; tag 6's desc+0x08 (`0x6641b3a`) reaches the same queue via `call 0x67D5FF0` at 0x664248d [V]; tag 6's 1-byte queue pass+0x270/+0x278/+0x280 (end += 1 at 0x66424c1/0x66424d4 [V]; queued byte unwritten [I]) and tag 7's TransitionRecord queue pass+0x168/+0x170/+0x178 (end += 0x20 at 0x66426ea [V]) also decoded.

## TOOL REQUESTS
None.
