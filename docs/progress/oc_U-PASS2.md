# Progress: U-PASS2 (follow-up to oc_U-PASS)

## NEXT
Unit is complete; no further steps. All results below are written to disk. Open items tagged [?] remain.

## Unit task (from brief)
- sub_c21db0 (0xc21db0) copies a struct containing pass-object pools (+0x648, +0x750, +0x780, +0x8A0); sub_833e30 (0x833e30) destroys such a struct (+0x750, +0x768, +0x780, +0x8A0): copy/destroy of same element type; thread-local pass object (payload 0x8B8) moved/copied into a container.
(1) rdis callers 0xc21db0 / 0x833e30 / 0xc1cb60 -> list each caller and what container/vector it appends to (store to [reg+0x...] after the call; element size for alloc/mul).
(2) Element size from stride in sub_c1cb60 / sub_c0a050 / sub_842a010 (imul/lea with constant like 0x8B8 or 0x8C8).
(3) Function that owns the container + when consumed: who iterates it (loop with add reg,0x8B8 or add reg,0x8C8).
(4) Whether consumer reads fields +0x648/+0x750/+0x768/+0x780/+0x8A0 of each element and what it does with them.
All disassembly lines quoted verbatim as `0xRVA  instruction`; tags: [V]=seen in disassembly (cite RVA), [I]=inferred, [?]=could not determine.

## METHOD / TOOLS
- rdis.exe: tools/rdis/target/release/rdis.exe "<Minecraft.Windows.exe>" <cmd> <rva>
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only. No game run, no builds, no edits to other files.
- Output file: docs/progress/oc_U-PASS2.md only.

## TASK 1 — callers of 0xc21db0 / 0x833e30 / 0xc1cb60

### rdis callers 0xc21db0  [V]
```
  sub_c1cb60                   2 call site(s)
  sub_36bc250                  1 call site(s)
  sub_3722fe0                  1 call site(s)
-- 3 calling function(s)
```
Matches oc_U-PASS (sub_c1cb60 2x, sub_36bc250 1x, sub_3722fe0 1x). Each caller invokes sub_c21db0 inside a loop that copies elements into a destination buffer; after each call the destination offset is advanced by `add rax,0xD30` / `add rcx,0xD30` (element stride 0xD30, see Task 2). There is no separate "append store" after the call — sub_c21db0 itself writes into [rcx+...] (dest) and the caller bumps the offset.

### rdis callers 0x833e30  [V]
```
  sub_96f8b0                   1 call site(s)
-- 1 calling function(s)
```
sub_96f8b0 (0x96f8b0) calls sub_833e30 once, then conditionally frees the object:
```
  96f8b8  mov rsi,rcx
  96f8bb  call 0x833E30        ; -> sub_833e30   (rsi = object to destroy)
  96f8c0  test dil,1
  96f8c4  je short 0x96F8D3
  96f8c6  mov edx,0x2010
  96f8cb  mov rcx,rsi
  96f8ce  call 0xE935700       ; -> sub_e935700   (free, size 0x2010)
```
[V] The object passed to sub_833e30 is freed with size 0x2010, i.e. the copied/destroyed struct is ~0x2010 bytes, NOT a 0x8B8-byte pass-object payload. This contradicts the brief's "payload size 0x8B8" framing (see NOTE below).

### rdis callers 0xc1cb60  [V]
```
  sub_c0a050                   1 call site(s)
  sub_842a010                  2 call site(s)
-- 2 calling function(s)
```
sub_842a010 (behavior/AI goal code, references "minecraft:behavior.vex_random_move") bumps a byte-end counter at [r14+0x168] by element stride 0xD30, then calls sub_c1cb60 to grow/copy — twice:
```
  842a4ae  add qword ptr [r14+0x168],0xD30
  842a4cc  call 0xC1CB60      ; -> sub_c1cb60
  ...
  842a95d  add qword ptr [r14+0x168],0xD30
  842a97b  call 0xC1CB60      ; -> sub_c1cb60
```
[r14+0x168] is the container's byte-size/end counter; incrementing by 0xD30 = appending one 0xD30-byte element. sub_c0a050's call site to sub_c1cb60 was not reached within a 900-instruction dis window (function is 0x2000 bytes); recorded as [I] that sub_c0a050 also drives sub_c1cb60.

sub_c1cb60 copy loops (destination base r15 / r14 / rdi depending on caller), advance by 0xD30:
```
  c1cbf4  imul rdx,r13,0xD30     ; sub_c1cb60: new buffer bytes = new_count * 0xD30
  c1ccda  add rax,0xD30
  c1cce0  add rcx,0xD30
  c1cd2d  add rax,0xD30
  c1cd33  add rcx,0xD30
```
sub_36bc250 (dest base r14):
```
  36bc73f  call 0xC21DB0
  36bc74d  add rax,0xD30
  36bc753  add rcx,0xD30
```
sub_3722fe0 (dest base rdi; args rcx=begin, rdx=end, r8=src):
```
  372301c  call 0xC21DB0
  372302a  add rax,0xD30
  3723030  add rcx,0xD30
```

### TASK 1 summary
- sub_c21db0 callers: sub_c1cb60 (2x), sub_36bc250 (1x), sub_3722fe0 (1x) — all copy elements stride 0xD30 into a destination buffer via sub_c21db0. [V]
- sub_833e30 caller: sub_96f8b0 (1x) — destroys an ~0x2010-byte object, then frees it. [V]
- sub_c1cb60 callers: sub_c0a050 (1x), sub_842a010 (2x) — sub_842a010 appends to container at r14, counter [r14+0x168], stride 0xD30. [V]
- Observed element/alloc size everywhere in this chain = **0xD30**, not 0x8B8/0x8C8. [V] (Brief hint 0x8B8/0x8C8 not found as stride here; see Task 2.)

## TASK 2 — element size from stride (sub_c1cb60 / sub_c0a050 / sub_842a010)

[V] No `0x8B8` or `0x8C8` immediate appears as a stride in sub_c1cb60, sub_c0a050, or sub_842a010. The stride used by all three is **0xD30**:
- sub_c1cb60: `imul rdx,r13,0xD30` (allocation = count * 0xD30) and `add rax,0xD30`/`add rcx,0xD30` in every copy loop.
- sub_842a010: `add qword ptr [r14+0x168],0xD30` before each `call sub_c1cb60` (counter += element size).
- sub_c0a050: only `lea rcx,[rbp+0xD30]` / `lea r9,[rbp+0xD30]` — these are stack-frame local offsets ([rbp+0xD30]), not a heap stride ([I]).

Conclusion: the element/alloc stride observed in the named functions is **0xD30** [V]; the brief's suggested 0x8B8/0x8C8 was not found as a stride in these three functions. This is a discrepancy with the "pass object payload 0x8B8" framing (see NOTE).

## TASK 3 — container owner / consumer (loop with add reg,0x8B8 or add reg,0x8C8)

`rdis imm 0x8B8` and `rdis imm 0x8C8` scan [V] — every instruction with those immediates:

`imm 0x8B8` (non-stack `add reg,0x8B8` loops):
```
  2210ac  sub_220d10+0x39c  add rdx,0x8B8
  289d1e  sub_289c80+0x9e   add rbx,0x8B8
```
(the rest are `sub rsp,0x8B8`/`add rsp,0x8B8` prologue/epilogue, or `mov dword ptr [rsp+0x28],0x8B8`).

`imm 0x8C8` (non-stack `add reg,0x8C8` loops):
```
  8801224 sub_88001a0+0x1084 add rsi,0x8C8
  c06d1dc sub_c06b7a0+0x1a3c add rcx,0x8C8
  c07209c sub_c06f610+0x2a8c add rcx,0x8C8
```
(the rest are `mov edx,0x8C8` alloc sizes in sub_5aba5c0/sub_67c0c50/sub_7499ff0, or `sub rsp,0x8C8`/`add rsp,0x8C8` prologue/epilogue).

None of these five `add reg,0x8B8/0x8C8` loops reads the five pass-object pool offsets (+0x648/+0x750/+0x768/+0x780/+0x8A0). Context around each:
- sub_220d10 (2210ac `add rdx,0x8B8`): reads `[rcx]`, `[rax+8]`, `[rbx]`, `[rax+0x188]` (vcall-style), not pools.
- sub_289c80 (289d1e `add rbx,0x8B8`): reads `[rsi+0x8F0]`, `[rcx]`, `[rax]` (vcall), not pools.
- sub_88001a0 (8801224 `add rsi,0x8C8`): reads `[rbp+0x248]`/`[rbp+0x258]`/`[rbp+0x230]`, `[r12]`, stack fields, not pools.
- sub_c06b7a0 (c06d1dc `add rcx,0x8C8`): reads `[rbx+r15+0x4C0]`, `[rbx+r15+0x4C8]`, `[rbp+0x780]+0x568`, etc., not pools.
- sub_c06f610 (c07209c `add rcx,0x8C8`): reads `[rbx+r15+0x4C0]`, `[rbx+r15+0x4C8]`, `[rbp+0x7B0]+0x6B0`, etc., not pools.

`dispfun.py 0x648 0x750 0x768 0x780 0x8a0` [V] lists ~70 functions touching all 5 displacements, but per oc_U-PASS these are almost all known PUSHERS (getter callers, endFrame, item/sky/UI/effect/editor visitors, BatchActor builders, extractors) or use [rbp+...] stack locals — none is a drain consumer of the pass-object container.

### TASK 3 summary
No function was located that (a) owns/appends to the pass-object container and (b) iterates it with `add reg,0x8B8/0x8C8` while reading the pool fields. The `imm 0x8B8/0x8C8` candidates are unrelated loops. The container owner appears to be sub_842a010 (counter [r14+0x168] += 0xD30, calls sub_c1cb60) but its element stride is 0xD30 and it is behavior/AI code, not a pass-object drain [I]. **Consumer not found [?].**

## TASK 4 — does the consumer read +0x648/+0x750/+0x768/+0x780/+0x8A0 per element?

Since no consumer was identified (Task 3), this cannot be confirmed [?]. What IS verified:
- sub_c21db0 (copy) reads/writes many fields including +0x648-area pool vector pairs via sub_26e880 (16-byte elems, refcount inc) [V from oc_U-PASS + c21db0 head]. Per oc_U-PASS fld 0x768 scan, sub_c21db0 does NOT read [rsi+0x768].
- sub_833e30 (destroy) reads +0x750/+0x768/+0x780/+0x8A0 but NOT +0x648 [V from oc_U-PASS fld scans]; head shows it also tears down sub-objects at +0x1EE0..+0x1F88 and reads [rcx+0x2000].
- So sub_c21db0 covers {0x648,0x750,0x780,0x8A0} (missing 0x768) and sub_833e30 covers {0x750,0x768,0x780,0x8A0} (missing 0x648) — together all five, but neither is a consumer, and neither reads all five alone [V].

No drain function reading all five pool offsets of each container element was found [?].

## NOTE — discrepancy vs brief framing
The brief asserts the element is the thread-local pass object (payload 0x8B8) moved/copied into a container, copied by sub_c21db0 and destroyed by sub_833e30. What the disassembly actually shows [V]:
- sub_c21db0 deep-copies a struct field-by-field from rdx->rcx (copy ctor), calling sub_26e880 for vector pairs.
- sub_833e30 destroys a ~0x2010-byte object (sub_96f8b0 frees with edx=0x2010; sub_833e30 touches up to [rcx+0x2000] and sub-objects at +0x1EE0..+0x1F88).
- sub_c1cb60 reallocates/copies with stride **0xD30**, not 0x8B8/0x8C8.
So sub_c21db0/sub_833e30 operate on a large (~0x2010-byte) struct, and the observed container stride is 0xD30. The 0x8B8 pass-object payload and a 0x8B8/0x8C8-stride container consumer were NOT confirmed in static analysis. If the intended element is 0x8B8/0x8C8, it is not represented by the strides found in sub_c1cb60/sub_c0a050/sub_842a010 nor by any `add reg,0x8B8/0x8C8` pool-reading loop.

## VERIFICATION LOG
- rdis callers 0xc21db0 -> sub_c1cb60(2), sub_36bc250(1), sub_3722fe0(1) [V]
- rdis callers 0x833e30 -> sub_96f8b0(1) [V]; sub_96f8b0 frees with size 0x2010 [V]
- rdis callers 0xc1cb60 -> sub_c0a050(1), sub_842a010(2) [V]; sub_842a010 `add [r14+0x168],0xD30` then call sub_c1cb60 [V]
- Stride: imul/add 0xD30 in sub_c1cb60/sub_842a010; sub_c0a050 only stack [rbp+0xD30] refs [V]
- imm 0x8B8 / imm 0x8C8 full scan; five non-stack add-loops, none reads pools [V]
- dispfun 5 pool offsets: ~70 functions, all known pushers or stack-relative (per oc_U-PASS) [V]
