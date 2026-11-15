# Light visitor 0x6640d80: ShadowAtlasFrame (tag 4), VoxelVolume (tag 6), TransitioningVoxelVolume (tag 7) + the producer's insert sites

Checklist item D9b. Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing AND re-run with rdis, [I] inference, [?] unknown.
Listings (tools/sigs/dumplist.py): docs/data/listings/light_visitor_6640d80_6645400.txt (whole visitor incl. cold stubs), light_clone_53599d0_535ce80.txt
(the producer function 0x53599d0), light_shadowatlas_builder_7915d50_7915fc0.txt. Typed read-views: src/sdk/mc/deps/minecraft_renderer/framebuilder/LightDescriptions.h.
SkyAmbientSamples (the other D9b part) is in 66560f0_sky_visitor.md.

Case separation: the cases are interleaved fragments like the sky visitor; a control-flow walk from each case head over the dumped range (calls continue, `call 0x75740`,
`call 0x75B60`, `call [0xF9A8C78]`, int3 and ret end a path) gave per-case reachable sets of 437 (tag 4), 444 (tag 6) and 522 (tag 7) instructions; all of them were read.

## 1. Dispatch, tag -> type [V]
```
6640dc4  movzx eax,byte ptr [rdx+8]
6640dc8  cmp rax,7
6640dcc  ja 0x6644D1C
6640dd5  mov rsi,[rdx]
6640dd8  lea rcx,[0xF2BF2B0]
6640de6  jmp rax
```
`rdx` = the variant {description pointer +0x00, tag byte +0x08}; rsi = description, rdi = frame context (`[rdi+0x10]+0x9D0` is the pass-object argument of 0x5ABA5C0).
Jump table 0xF2BF2B0 (8 int32, parsed from the PE): 0 0x6640de8, 1 0x66415b0, 2 0x6640f1b, 3 0x66410a0, 4 0x6640ec1, 5 0x66417af, 6 0x664187d, 7 0x6641524.

Tag -> type (this CORRECTS the order guessed in 6ih / group_visitors.md, which named tag 4 "unnamed", tag 7 "VoxelVolume"): the producer 0x53599d0 makes four
`FrameBuilder::insert` calls through vslot 0x380 (Light group). Each call site carries a profiler zone whose source-location record (the cold initialiser at 0x535cd60 / 0x535aac0 / 0x535cdef / 0x535ccd1
loads `lea rax,[0xF248DNN]`) names the instantiated type; the record's 2nd qword is the __FUNCSIG__ string, read from the exe:
| Insert call | zone record | `FrameBuilder::insert [TDescription = ...]` | tag byte store | description register |
|---|---|---|---|---|
| 0x535a6a0 | 0xF248D80 | ShadowAtlasFrameDescription | `mov byte ptr [rbp+0x278],4` 0x535a696 | rdi (= &[rbp+0xC0], built by 0x7915D50) |
| 0x535a9c1 | 0xF248DA0 | LightPointDescription | `mov byte ptr [rbp+0x278],3` 0x535a9b7 | &[rbp+0xC0] (built by 0x668ADE0) |
| 0x535ad3e | 0xF248DC0 | VoxelVolumeDescription | `mov byte ptr [rbp+0xC8],6` 0x535ad34 | rbx = &[rbp+0x270] (built by 0x5AE5760) |
| 0x535aec3 | 0xF248DE0 | TransitioningVoxelVolumeDescription | `mov byte ptr [rbp+0x278],7` 0x535aeb9 | rbx = &[rbp+0xC0] (built by 0x6B19E30) |
GameplayMetadata is Light tag 2 (`mov byte ptr [rbp-0x18],2` 0x53e5fb4, then `[rax+0x380]` 0x53e5fbf in clone 0x53e5910), so FrameBuilder.h's LightGroupTag value 2 is right.
BGFX_MAP 6ee/6ih rows that put LightPoint/ShadowAtlas/Voxel at "2/3/4/5.." are superseded by this table.

Common machinery of the cases [V]:
- Pass object: `mov ecx,0x9D0; add rcx,[rdi+0x10]; call 0x5ABA5C0; mov rsi,rax` (tag 4: 0x6641923..0x6641932; tag 6: 0x6642432..0x6642441; tag 7: 0x6642611..0x6642620). After it rsi is the PASS.
- A local 0xC8-byte record is zeroed (12 x `movaps [rbp-0x50..0x60],xmm0` + `mov qword ptr [rbp+0x70],0`, e.g. 0x664244b..0x664247e) and appended to the pass stream at pass+0x08/+0x10:
  `mov rax,[rsi+8]; cmp rax,[rsi+0x10]; je grow; lea rdx,[rbp-0x50]; mov r8d,0xC8; mov rcx,rax; call 0xEEC6EC0; add qword ptr [rsi+8],0xC8` (tag 4 0x6643801..0x664381d, grow call 0x5ABA6D0 at 0x6643831;
  tag 6 0x6643ad8..0x6643b08; tag 7 0x6643f7a..0x6643faa). Only a few words of this record are set (per case below); the layout of the record elsewhere is the DrawItem of DrawItem.h (+0x00 mask, +0x0A kind, ...) but the Light cases write the qword at +0x08 and the indices below, NOT the mask [I].
- `mov rcx,[0x1233E1B0]; mov rax,[rcx]; mov rax,[rax+0x10]; mov dl,0x4A; call [0xF99FFA0]` pairs bracket the copy and the record append (0x6641970..0x6641980, 0x66437e4..0x66437f4): a begin/end scope hook, result byte kept at [rbp+0xCC0] [I].
- Every case leaves through the shared epilogue 0x66447a0..0x66447d1 (movaps xmm6..9 from [rbp+0xCD0..0xD00], `add rsp,0xD98`, 8 pops, ret). Allocation failure stubs call 0x9BC830 (returns, then re-joins) and length stubs `call 0x75740`
  ("bad array new length", verified at 0x75740) / `call 0x75B60` ("vector too long", verified) never return. The 0x6643eae `call [0xF9A8C78]` is the heap-corruption check of the big-block free path (the listing text after it, 0x6643ec7, is tag 7 code reached by a jump, not a fall-through).

## 2. ShadowAtlasFrame, Light tag 4, case 0x6640ec1 [V]
Description reads (rsi), all in the head and 0x66418f0:
```
6640ec1  movups xmm6,[rsi]
6640ecb  movups xmm7,[rsi+0x10]
6640ed6  movups xmm8,[rsi+0x20]
6640ee3  movups xmm9,[rsi+0x30]
6640f01  mov rcx,[rsi+0x48]
6640f05  test rcx,rcx
6640f08  je 0x66418ED
6640f0e  lock inc dword ptr [rcx+8]
6640f12  mov r12,[rsi+0x48]
6640f16  jmp 0x66418F0
66418ed  xor r12d,r12d
66418f0  mov rbx,[rsi+0x40]
```
| Offset | Size | Read at | Destination |
|---|---|---|---|
| +0x00 | 16 | 0x6640ec1 | xmm6 -> pass element +0x00 |
| +0x10 | 16 | 0x6640ecb | xmm7 -> +0x10 |
| +0x20 | 16 | 0x6640ed6 | xmm8 -> +0x20 |
| +0x30 | 16 | 0x6640ee3 | xmm9 -> +0x30 |
| +0x40 | 8 | 0x66418f0 (rbx) | +0x40 (a pointer; with +0x48 a {ptr, control block} pair) |
| +0x48 | 8 | 0x6640f01 | +0x48; non-null: use count `lock inc [ctrl+8]` (0x6640f0e) |
Nothing after +0x48 is read: description size 0x50 (matches the builder, section 5). Matches the earlier 6ih "tag 4" note; the type is now ShadowAtlasFrame.
Copy: in place when the vector has room (`mov r14,[rsi+0x1D0]; cmp r14,[rsi+0x1D8]; je 0x6641CE9`, then
```
66419a5  movups [r14],xmm6
66419a9  movups [r14+0x10],xmm7
66419ae  movups [r14+0x20],xmm8
66419b3  movups [r14+0x30],xmm9
66419b8  mov [r14+0x40],rbx
66419bc  mov [r14+0x48],r12
66419c6  add qword ptr [rsi+0x1D0],0x50
66419ce  jmp 0x66437A9
```
so the pass vector is begin +0x1C8, end +0x1D0, cap +0x1D8, element 0x50. Grow path 0x6641ce9..0x6641db6 / 0x6643422..0x66439ae: new capacity max(1.5 x size, size+1) (`shr r15,1; add r15,rcx; cmovbe`, 0x6641d0f..0x6641d28) (`mov rcx,0xCCCCCCCCCCCCCCCD; imul rcx,rax` is the division of the byte
size by 0x50, 0x6641cfa..0x6641d04), limit 0x333333333333333 elements (`jae 0x6644D3F` -> bad array new length, 0x6641d47), allocation through the engine allocator `[0x1233E1A8]->vtbl+8` (`add rdx,0x27 ... and rdi,~0x1f` for >=0x1000 bytes, 0x6641d7b..0x6641db2),
the new element is stored at `[rdi+r13]` (0x6643455..0x6643471), old elements are COPIED (rows via 16 movss, `lock inc [rcx+8]` on the +0x48 control block, 0x66438d9..0x66439ae), old ones destroyed with the usual
`lock dec [+8]` / `lock dec [+0xC]` release loop (0x66436f9..0x664372f), old block freed, then begin/end/cap stored: `mov [rsi+0x1C8],rdi` .. `mov [rsi+0x1D0],rax` .. `mov [rsi+0x1D8],rax` (0x664376f..0x664379a).
Record: after the push (0x66437a9..) the 0xC8 local gets
```
66437c1  mov qword ptr [rbp-0x48],0x200
66437c9  mov eax,[rsi+0x1D0]
66437cf  sub eax,[rsi+0x1C8]
66437d5  shr eax,4
66437d8  imul eax,0xFFFFCCCD
66437de  dec eax
66437e0  mov [rbp+0x52],ax
```
i.e. record+0x08 qword = 0x200 and record+0xA2 word = index of the new element ((end-begin)/0x50 - 1; 0xFFFFCCCD is the inverse of 5 after the >>4), then the record is appended to the stream (section 1).
Exit: `mov rsi,[rbp+0xB58]; test rsi,rsi; jne 0x6643C85; jmp 0x66447A0` (0x6643891..0x664389a): [rbp+0xB50..0xB5F] was zeroed at 0x6640efa and again at 0x6641920, so the release path 0x6643c85 (a ctrl `lock dec` pair) is never taken by this case [I];
the local copy of the shared pointer (rbp+0xC20/+0xC28) was zeroed (moved from) before, 0x6643853..0x664388a releases a null. The case therefore exits at 0x66447a0 after exactly: copy into +0x1C8 vector, one DrawItem append.

## 3. VoxelVolume, Light tag 6, case 0x664187d [V]
Description layout from the reads (rsi):
```
664187d  mov rax,[rsi]
6641883  movaps [rbp+0xB10],xmm0
664188a  mov rcx,[rax+8]
664188e  test rcx,rcx
6641891  je 0x6641B25
6641897  lock inc dword ptr [rcx+8]
66418a2  movups xmm0,[rax]
66418a5  movaps [rbp+0xB10],xmm0
6641b3a  mov rax,[rsi+8]
6641bb4  mov r13,[rsi+0x10]
6641bb8  mov [rbp+0xB30],r13
6641bd4  mov rbx,[rsi+0x20]
6641bd8  mov rcx,[rsi+0x18]
```
| Offset | Size | Read at | Meaning / destination |
|---|---|---|---|
| +0x00 | 8 | 0x664187d | POINTER to a {object, ctrl} pair; the pair (16 B, use count incremented when ctrl != 0, 0x6641897/0x66418a2; old local value released by the dec +8 / dec +0xC pair 0x66418b5..0x66418e2) is copied to local [rbp+0xB10] then moved into VoxelRecord +0x00 |
| +0x08 | 8 | 0x6641b3a | second POINTER to a pair, same handling (0x6641b48..0x6641b96), local [rbp+0xB20] -> VoxelRecord +0x10 |
| +0x10 | 8 | 0x6641bb4 | qword -> [rbp+0xB30] -> [rbp+0xC08] -> VoxelRecord +0x20 |
| +0x18 | 8 | 0x6641bd8 | vector begin |
| +0x20 | 8 | 0x6641bd4 | vector end |
Vector: byte size = end-begin (0x6641bdc..0x6641be2), count = size>>3 (`sar rax,3`), `shr rcx,0x3D; jne 0x6644D27` (count >= 2^61 -> "vector too long"), < 0x200 elements allocated plainly (0x66422b8), otherwise the 0x27-padded
aligned big-block path (0x6641c04..0x6641c3b); the elements are copied 8 bytes (four u16 loads/stores) at a time (0x6642300..0x664233a). Empty vector skips everything (`je 0x6641C40` -> r14 = rax = rbx = 0, jmp 0x66423DA).
The local record (rbp+0xBE8..0xC28) is built at 0x66423da..0x664242b:
```
66423e1  movaps xmm0,[rbp+0xB10]
66423e8  movaps xmm1,[rbp+0xB20]
66423ef  movups [rbp+0xBE8],xmm0
66423fd  movups [rbp+0xBF8],xmm1
6642408  mov [rbp+0xC08],r13
664241d  mov [rbp+0xC10],r14
6642424  mov [rbp+0xC18],rax
664242b  mov [rbp+0xC20],rbx
```
and pushed with `lea rcx,[rax+0x138]` (rax = pass) / `lea rdx,[rbp+0xBE8]` / `call 0x67D5FF0` (0x6642444, 0x6642486, 0x664248d). 0x67D5FF0 is a MOVE-emplace: it reads [src+0x00],+0x08 (then `movups [r14],xmm0` zeroes the pair: 0x67d603e..0x67d604d),
+0x10,+0x18 (zeroed), +0x20, +0x38 (zeroed to 0) and +0x28 (movups, zeroed) (0x67d6073..0x67d6084; the second copy of the same sequence is the in-place branch 0x67d616b..0x67d61b5) and its capacity code uses element size 0x40 (limit 0x3FFFFFFFFFFFFFF). So pass+0x138/+0x140 is a vector of 0x40-byte VoxelRecords:
{pair A +0x00, pair B +0x10, qword +0x20, std::vector of 8-byte elements +0x28/+0x30/+0x38}.
Then:
```
6642493  mov eax,[rsi+0x140]
6642499  sub eax,[rsi+0x138]
664249f  shr eax,6
66424a2  dec eax
66424a4  mov [rbp+0x5E],ax
66424c1  mov rbx,[rsi+0x278]
66424c8  cmp rbx,[rsi+0x280]
66424d1  inc rbx
66424d4  mov [rsi+0x278],rbx
66424db  jmp 0x6643A8C
6643aa1  mov qword ptr [rbp-0x48],0x8004
6643aa9  mov eax,[rsi+0x270]
6643aaf  not eax
6643ab1  add eax,[rsi+0x278]
6643ab7  mov [rbp+0x44],ax
```
record+0xAE word = index of the new VoxelRecord; a second pass vector at pass+0x270/+0x278/+0x280 gets a ONE-BYTE element appended (`inc rbx; mov [rsi+0x278],rbx`; the grow branch 0x66424e0..0x66439e8 only memcpy's the old bytes with 0xEEC6DE0; no store writes the new byte: an empty/uninitialised 1-byte tag
element [I]); record+0x94 word = its index (end - begin - 1; `not eax; add eax,end`), record+0x08 qword = 0x8004. The record is appended to the stream.
Exit/cleanup (0x6643b2a..0x6643cb8): frees the local vector buffer [rbp+0xC10], releases the control blocks at [rbp+0xC00] and [rbp+0xBF0] (null after the move), frees [rbp+0xB38] (zeroed), releases [rbp+0xB28] and [rbp+0xB18]
(`mov rsi,[rbp+0xB18]; test rsi,rsi; je 0x66447A0`), then `jmp 0x66447A0`. Because 0x67D5FF0 moved the record, these releases find null in the normal path [I].

## 4. TransitioningVoxelVolume, Light tag 7, case 0x6641524 [V]
```
6641524  mov rax,[rsi+0x18]
6641528  mov [rbp+0xAC0],rax
6641544  mov rbx,[rsi+0x40]
6641548  mov rcx,[rsi+0x38]
664211a  mov rdx,[rsi+0x38]
664211e  mov rbx,[rsi+0x40]
664212b  call 0xEEC6DE0
664213a  mov rax,[rsi]
66421a9  mov rax,[rsi+8]
6642223  mov r12,[rsi+0x10]
6642240  mov rbx,[rsi+0x28]
6642244  mov rcx,[rsi+0x20]
```
| Offset | Size | Read at | Meaning / destination |
|---|---|---|---|
| +0x00 | 8 | 0x664213a | POINTER to a {object, ctrl} pair (use count +8 incremented, 0x664214d) -> local [rbp+0xB10] -> VoxelRecord +0x00 |
| +0x08 | 8 | 0x66421a9 | second pair pointer -> [rbp+0xB20] -> VoxelRecord +0x10 |
| +0x10 | 8 | 0x6642223 | qword -> [rbp+0xB30] -> VoxelRecord +0x20 (store 0x66425ea) |
| +0x18 | 8 | 0x6641524 | qword -> [rbp+0xAC0] -> [rbp+0xBE0] -> TransitionRecord +0x00 |
| +0x20 / +0x28 | 8 / 8 | 0x6642244 / 0x6642240 | begin / end of a vector of 8-byte elements, copied exactly like tag 6's vector (0x6642390..0x66423cd) -> VoxelRecord +0x28..0x38 |
| +0x38 / +0x40 | 8 / 8 | 0x6641548 / 0x6641544 | begin / end of a dword array (`sar rax,2`, `shr rcx,0x3E; jne 0x6644D21` count < 2^62, < 0x400 elements plain allocation 0x66420e6 else big block 0x6641578..0x66415a7), memcpy'd with 0xEEC6DE0 (0x664212b) -> TransitionRecord +0x08..+0x18 |
+0x30 and anything past +0x48 is not read by this case.
Local record: 0x60 bytes at rbp+0xBE0..0xC3F: {+0x00 qword (desc +0x18), +0x08..+0x18 dword array {begin,end,cap}, +0x20 pair A, +0x30 pair B, +0x40 qword (desc +0x10), +0x48..+0x58 vector {begin,end,cap}}. Its destructor is 0x66AD820 (reads [rcx+0x48], [rcx+0x58]; called at 0x6643fd3).
```
6642587  mov rdx,[rbp+0xAC0]
664258e  mov [rbp+0xBE0],rdx
66425b5  movups [rbp+0xBE8],xmm0
66425bc  mov [rbp+0xBF8],rdx
66425d1  movups [rbp+0xC00],xmm0
66425df  movups [rbp+0xC10],xmm1
66425ea  mov [rbp+0xC20],r12
66425fc  mov [rbp+0xC28],r14
6642603  mov [rbp+0xC30],rax
664260a  mov [rbp+0xC38],rbx
6642623  lea rdx,[rbp+0xC00]
6642665  lea rcx,[rax+0x138]
664266c  call 0x67D5FF0
6642683  mov [rbp+0x5E],ax
```
The 0x40-byte half at rbp+0xC00 (pair A, pair B, qword, vector) is pushed into the SAME pass vector +0x138 as tag 6 (identical VoxelRecord, index at record+0xAE). The other half is moved into a SECOND pass vector:
```
66426a1  mov r12,[rsi+0x170]
66426a8  cmp r12,[rsi+0x178]
66426b8  mov [r12],rax
66426e5  mov [r12+0x18],rax
66426ea  add qword ptr [rsi+0x170],0x20
6643f40  mov qword ptr [rbp-0x48],0xA000
6643f48  mov eax,[rsi+0x170]
6643f4e  sub eax,[rsi+0x168]
6643f54  shr eax,5
6643f57  dec eax
6643f59  mov [rbp+0x5A],ax
```
vector begin +0x168, end +0x170, cap +0x178, TransitionRecord 0x20 = {qword, std::vector<u32> {begin,end,cap}}, moved (zeroing the source, 0x6643d50..0x6643d77); grow path 0x66426f7..0x6643f19 (limit `shr rdx,0x3B` -> 2^59 elements). Record: +0x08 qword = 0xA000, word +0xAA = index into +0x168 (shr 5), word +0xAE = index into +0x138;
then the stream append. Exit: `call 0x66AD820` on the local 0x60 record, free [rbp+0xB38] if non-null, `jmp 0x66447A0` (0x6643fcc..0x664401c). 0x6641524's first reads happen BEFORE the pass lookup; no frame-context field is tested.
Observation [I]: the 0x40 VoxelRecord and the pass+0x138 vector are shared by both voxel types; TransitioningVoxelVolume = VoxelVolume body + {qword +0x18, dword array +0x38}. The description field offsets differ between the two (tag 6 vector at +0x18/+0x20, tag 7 at +0x20/+0x28) because tag 7 inserts +0x18 and the dword array.

## 5. Clone side: who builds each description (producer 0x53599d0, 2757 listing lines; fat clone = an ECS system) [V reads of the call sites, ? internals]
Prologue stores r8 (-> [rbp+0x338]), rdx (-> [rbp+0x218]) and rcx (the system object, -> [rbp+0x350]); fields of that object used: +0x480 (a settings block: +0x9BA flag, +0x5E8, +0x101C, ...), +0x490/+0x4A0 (listeners, 0x535f3e0), +0x68, +0x70, +0x80, +0x90, +0x178/+0x180.
Each insert is wrapped in a profiler zone (`call 0x39A7D40` before the tag store, 0x77A2500 after) and uses the vslot at `[[rbx]+0x380]` = group Light.
- ShadowAtlasFrame (tag 4): the desc at rbp+0xC0 is initialised by 0x7915D50 (rcx = [system+0x70], rdx = desc, r8 = [owner+0x6F8], call 0x535a4f7..0x535a4fa). Its first stores write four identity rows (1.0f at +0x00,+0x14,+0x28,+0x3C; zero elsewhere, +0x40 zeroed 16 bytes: 0x7915d71..0x7915d9b),
  then the rows are replaced by the result of 0x7912420 (movups from [rbp-0x28..+8]) and the final stores are
  ```
  7915e55  movups [rbx],xmm0
  7915e5c  movups [rbx+0x10],xmm0
  7915e64  movups [rbx+0x20],xmm0
  7915e6c  movups [rbx+0x30],xmm0
  7915e70  mov [rbx+0x40],rcx
  7915e74  mov [rbx+0x48],rax
  ```
  with rcx = `mov rcx,[rsi+0x178]` (7915e4a) and rax = `mov rax,[rsi+0x180]` (7915e2b) = a shared pair copied from the SYSTEM object (+0x178 object, +0x180 control block, use count incremented 0x7915e27); the old +0x48 pair is released. So +0x40/+0x48 of the description is the shadow-atlas texture shared pointer, the 16 floats a 4x4 matrix (identity unless 0x7912420 overrides it).
  Guard: `cmp qword ptr [rcx+0x178],0` at 0x7915d9f skips everything when the system has no atlas pointer (the identity stays). After the insert the call-site code releases `[rbp+0x108]` (= desc+0x48 control block) with the dec +8 / +0xC pair (0x535a6dc..0x535a70d).
- LightPoint (tag 3): desc at rbp+0xC0 filled by `call 0x668ADE0` (0x535a949) per element of a list iterated at 0x535a767 (stride 0xF0, `add rsi,0xF0`); not decoded here (the visitor side of tag 3 is in 6ih).
- VoxelVolume (tag 6): the system's `[+0x90]` object (`mov rbx,[rax+0x90]` 0x535ac00) must be non-null and `cmp qword ptr [rbx+0x140],0` non-zero (0x535ac47); then 0x5AE5760(rcx = [vm+0x140], rdx = &[rbp+0x270], r8 = [vm+8], r9 = vcall slot 0x1D8 of the frame-state object [rbp+0x210]) (0x535ac71..0x535ac90) and
  `cmp byte ptr [rbp+0x2A0],1` (0x535aca2) tests the "engaged" byte of the optional = desc+0x30 (the builder writes `mov byte ptr [rsi+0x30],0` at 0x5ae5880/0x5ae5a39 on failure and `mov byte ptr [rsi+0x30],1` at 0x5ae5b1e on success). The description is that 0x30-byte object (the visitor reads up to +0x28 [V], +0x28 itself unread). 0x5AE5760's success path writes
  `[rsi]=[rbp+0x1B8]` (0x5ae5b00), `[rsi+8]=[rbp+0x20]` (0x5ae5b07), `[rsi+0x10]=[[[rbp+0x200]+0x98]+0x18]` (0x5ae5b0b), zeroes +0x18..+0x2F (0x5ae5b12, 0x5ae5b16); a later path stores `[rsi+0x20]=0` (0x5ae751e): the vector at +0x18/+0x20 is filled by code not decoded here [?].
- TransitioningVoxelVolume (tag 7): `mov r14,[rax+0x80]` (0x535adca) non-null; 0x6B19E30(rcx = r14, rdx = &[rbp+0xC0], r8 = vcall slot 0x1D8 result) (0x535ae11..0x535ae21); it requires `[r14+0x140]` and `[r14+0x138]` non-null (0x6b19e5c..0x6b19e76), calls 0x5AE5760 (the same voxel builder, 0x6b19e86) into a local and
  checks its engaged byte [rbp+0xC0] (0x6b19e8b); the clone checks `cmp byte ptr [rbp+0x110],1` (0x535ae27), desc size >= 0x48 so +0x50 is the flag. So Transitioning = a VoxelVolume built for the system's second volume manager (+0x80) plus fields from a list at [r14+0xE0] (stride 0x130, 0x6b19edc..0x6b19f17) [?].
Observations [I]: the system holds two volume managers (+0x80 transitioning, +0x90 steady), both with the same {+0x138, +0x140} members; the visitor-side records match: VoxelRecord for both, TransitionRecord only for the transitioning one.

## 6. Re-verification (rdis, 2026-11)
Run with `python tools/sigs/verify_oc.py docs/functions/6640d80_light_visitor.md` (instruction lines quoted above) plus direct `rdis dis` checks of: jump table (parsed from the PE), the four insert call sites and their __FUNCSIG__ strings (read from the 0xF248D80/DA0/DC0/DE0 records), tag byte stores 0x535a696/0x535a9b7/0x535ad34/0x535aeb9/0x53e5fb4,
0x75740 ("bad array new length"), 0x75B60 ("vector too long"), 0x67D5FF0 move semantics, 0x66AD820 destructor reads (+0x48/+0x58), 0x7915D50 final stores, 0x5AE5760 engaged-byte stores. Result recorded in docs/progress/oc_verification.md.

## 7. Open [?]
- 0x5AE5760 and 0x6B19E30 internals (fields of the voxel description beyond +0x10: which of the vectors is filled and from what), LightPoint (tag 3) producer fields.
- The consumer of pass+0x138 / +0x168 / +0x1C8 / +0x270 vectors and the DrawItem words +0x08/+0x94/+0xAA/+0xAE/+0xA2 (the lighting/voxel passes): not located (same E2 consumer blocker as the other groups).
- `[0x1233E1B0]->+0x10 (dl=0x4A)` scope hook meaning.
