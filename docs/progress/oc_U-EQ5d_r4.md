## NEXT
DONE

# Unit U-EQ5d — Q5d Pass-level rewrites: TAAUpscaling body reversal

Scope (this run, per orchestrator): ONLY the TAAUpscaling body at 0xbc8ab12. ScreenDraw body 0xbc04dc0 is left for the next run. Output file: docs/progress/oc_U-EQ5d.md only. No Sigs.json edits, no HookManager.cpp, no existing hook registration, no CMake, no build, no commit, no game launch/attach — static analysis only.

## (1) What changed

- docs/progress/oc_U-EQ5d.md — this file (the unit's only output). Created this run.

## (2) Function bounds (verified with rdis fn against the exe)

- `rdis fn 0xbc8ab12` reports: `0xbc8ab12 is inside sub_bc8a380`, `sub_bc8a380 [0xbc8a380..0xbc8be7c) size 0x1afc 1 xrefs in` [V]. So 0xbc8ab12 is mid-function, not a function start.
- Requested reversal window this run: `0xbc8ab12 .. 0xbc8be7c` (function end per rdis fn) [V]. Every instruction in that window is tabled below; none skipped.
- Head `0xbc8a380..0xbc8ab12`: prologue (`push rbp..rbx; sub rsp,0xD08; lea rbp,[rsp+0x80]`) plus early-out guards reading slot globals [0x12AE1B60], [0x12AE1B70], [0x12AE1B80] (seen in the rdis fn head output) — outside the requested window, not tabled here.
- Calling convention [V from fn head]: `rcx -> [rbp+0xC58]` (arg1), `rdx -> rdi` (arg2), `r8 -> r15` (arg3), `r9 -> r14` (arg4). Guess: `void __fastcall sub_bc8a380(void* a1, void* a2, void* a3, void* a4)` [I].
- Last REACHABLE instruction of the window: `0xbc8be70 jmp 0xBC8A644` (tail jump to handler below the window, target not decoded this run) [V]. Bytes `0xbc8be75..0xbc8be7b` (`call 0x75740; nop; int3`) are fall-through-only trailing bytes inside rdis's bound, not control-flow reached from the body [I unreached].

## (3) Basic-block reversal of 0xbc8ab12..0xbc8be7c

All reads/writes/calls below are proven [V] by verbatim rows in section (5)/(6); offsets/sizes are instruction-derived.

### BB1 0xbc8ab12..0xbc8abbe — stack cookie + pass object 1 (0x130 bytes) init
- Reads: stack cookie constant `0x33404347445A915D`; stack slots [rbp+0xC18], [rbp+0xB28], [rbp+0xBF8], [rbp+0xC08], [rbp+0x720], [rbp+0x2A0]; global allocator object [0x1233E1A8], then [rax] and [rax+8] (allocate function pointer); indirect allocator call target [0xF99FFA0].
- Calls: `sub_568AD40` (object init helper), `sub_bc8c890` (pass-record copy), allocator `allocate(size=0x130)` via [0xF99FFA0].
- Writes: [rbp+0xB78] cookie; [rbp+0xB28] object pointer; [rbp+0xB30]=0xC; [rbp+0xBF8..0xC18] small-string/struct fields; [rbp-0x40], [rbp-0x50] (16-byte xmm saves); [rbp+0xC08]=0, [rbp+0xC10]=0xF; byte [rbp+0xBF8]=0; object1 fields at [r14+0..0x11C] (vtable [0xF44B2E0], many 1.0f = 0x3F800000 defaults); [rbp+0x2A0]=r14 (first object slot).

### BB2 loc_bc8abc8..0xbc8acc0 — object1 field init (continuation from alloc-fail retry)
- Writes: object1 [r14] = vtable [0xF44B2E0]; [r14+8], [r14+0x1C], [r14+0x30], [r14+0x5C], [r14+0x70], [r14+0x84] = 0x3F800000 (1.0f); [r14+0xC], [r14+0x20], [r14+0x34], [r14+0x4C], [r14+0x60], [r14+0x74], [r14+0x88], [r14+0x90], [r14+0xA0], [r14+0xB4], [r14+0xC8], [r14+0xF4] = 0; [r14+0x44], [r14+0xD8] = xmm6; [r14+0x88], [r14+0x90] = r13; [r14+0x98] = rsi; [r14+0x11C] = xmm0 from [rbp+0x700].
- Branches: `cmp [rbp+0x2A0],0; jne loc_bc8b8be` (alloc-fail path); else [rbp+0x2A0]=r14.

### BB3 0xbc8acce..0xbc8ad29 — sub_76a8a0 call + small-string saves
- Reads: [rbp+0xBA8], [rbp+0xBB0], [rbp+0xBC8].
- Calls: `sub_76a8a0`.
- Writes: [rbp+0xBC8]=0xF, byte [rbp+0xBB0]=0, [rbp+0xB70]=0, [rbp+0xB50]=[rbp+0xBB0], [rbp+0xB48]=[rbp+0xBA8], [rbp+0xB60]=0, [rbp+0xB68]=0xF, byte [rbp+0xB50]=0; then [rbp+0xA98]=rbx; [rbp+0xAA0]=0; [rbp+0xAA4]=0; byte [rbp+0xAA8]=0; [rbp+0xAB0]=r12; byte [rbp+0xABA]=0; [rbp+0xAC0]=[rbp+0xBF0]; word [rbp+0xAC8]=0; [rbp+0xACC]=0; byte [rbp+0xAD0]=0; [rbp+0xAD8]=[rbp+0xBE8]; byte [rbp+0xAE2]=0; [rbp+0xAE8]=[rbp+0xC38]; word [rbp+0xAF0]=0; [rbp+0xAF4]=0; byte [rbp+0xAF8]=0; [rbp+0xB00]=[rbp+0xC50]; byte [rbp+0xB0A]=0; [rbp+0xB10]=[rbp+0xC40]; [rbp+0xB18]=[rbp+0xC48]; byte [rbp+0xB22]=0.

### BB4 0xbc8ae12..0xbc8ae95 — xmm saves + second sub_bc8c890 copy
- Reads: [rbp+0xA90], [rbp+0xA70], [rbp+0xBB8], [rbp-0x50], [rbp-0x40].
- Calls: `sub_bc8c890` (second copy, dest [rbp+0x350]).
- Writes: [rbp+0xA90]=0; [rbp+0xA70]=rcx; [rbp+0xA78]=xmm0 ([rbp+0xBB8]); [rbp+0xA88]=rax; [rbp+0xA68]=rsi; [rbp+0x340]=xmm1, [rbp+0x330]=xmm0; [rbp-0x40]=0, [rbp-0x38]=0xF; byte [rbp-0x50]=0.

### BB5 0xbc8ae96..0xbc8aec2 — pass-record field gather into [rbp+0x628..0x6E0] block
- Reads (via rbx=[rbp+0xA98], r12=[rbp+0x5E8]): [rbx-0x28], [rbx-0x18], [rbx], [rbx+0x10], [rbx+0x20], [rbx+0x28], [rbx+0x38], [rbx+0x48], [rbx+0x50], [rbx+0x60], [rbx+0x70], [rbx+0x78], [rbx+0x88]; [rbp+0x2A0], [rbp+0x268].
- Writes: [rbp+0x620]=[rbp+0x2A0] (if != [rbp+0x268]); [rbp+0x630], [rbp+0x640], [rbp+0xA80]=0, [rbp+0xA88]=0xF, byte [rbp+0xA70]=0, [rbp+0x628]=rsi, [rbp+0x678]=[rbx+0x20], [rbp+0x658]=[rbx], [rbp+0x668]=[rbx+0x10], [rbp+0x6A0]=[rbx+0x48], [rbp+0x680]=[rbx+0x28], [rbp+0x690]=[rbx+0x38], [rbp+0x6C8]=[rbx+0x70], [rbp+0x6A8]=[rbx+0x50], [rbp+0x6B8]=[rbx+0x60], [rbp+0x6E0]=[rbx+0x88], [rbp+0x6D0]=[rbx+0x78].

### BB6 loc_bc8aed0..0xbc8af06 — release previous [rbp+0x2A0] via allocator, then zero it
- Calls: allocator via [0xF99FFA0] (`[rax+8]` release path) twice.
- Writes: [rbp+0x620]=rax; [rbp+0x2A0]=0.

### BB7 loc_bc8af11..0xbc8afe4 — pass object 2 (0x340 bytes) allocation + init start
- Reads: global allocator [0x1233E1A8] -> [rax], [rax+8]; size constant 0x340.
- Calls: allocator `allocate(size=0x340)` via [0xF99FFA0].
- Writes: [rbp+0x650]=0; [rbp+0x630], [rbp+0x640] from [rbx-0x28], [rbx-0x18]; [rbp+0x6A8], [rbp+0xA88] init; r13 = alloc result.

### BB8 loc_bc8aff7..0xbc8b0d7 — object2 init + link [rbp+0x620] into object2+0x80
- Writes: [r13+8]=0x100000001; [r13]=vtable [0xF09A740]; [r13+0x28], [r13+0x18]=0; [r13+0x38]=0xF, [r13+0x40]=0; [r13+0x10]=vtable [0xF44B2C0]; [rbp+0xC48]=lea [r13+0x48]; [rbp+0xC60]=r13; [r13+0x80]=0; [rax+0x80]=[rbp+0x620] (or via allocator release path [rcx+0x80]=rax).

### BB9 loc_bc8b0d7..0xbc8b17f — small-string copy into aligned heap buffer
- Reads: [rbp+0xC60] (=r13), [rbp+0xC40], [rbp+0xC58], rbx (count), r15 (count), rsi (source).
- Calls: `sub_bc8c890` (third copy, dest r12=[rcx+0x88]); allocator via [0xF99FFA0] (size r13+1 or r13+0x28); `sub_eec6ec0` (memcpy r15 bytes); `sub_e935700` (growth-fail path via [0xF9A8C78]).
- Writes: [rbp+0xC40]=[r13+0x10]; [rbp+0xC50]=r12; [r12+0x330], [r12+0x320]=0; aligned string store [r12-8]=rax, r12 aligned up by 0x27&~0x1F; [r14]=r12; [r12+0x330]=r15, [r12+0x338]=r13; byte [r14+r15]=0; object-list append at [rsi], [rsi+8] with [rcx+0x10]+=0x10 (or growth realloc + movups copy loops at loc_bc8b350/bc8b3a0/bc8b3e0 copying 16 bytes/iter).

### BB10 loc_bc8b40c..0xbc8b481 — sub_130ee0 + sub_568c420 + sub_5693A80 x3
- Calls: `sub_130ee0` (rcx=[rbp+0xC48], rdx=r12, r8=r14, r9=r15); `sub_568c420` (rcx=[rbp+0xC58]+0x58 data, rdx=[rbp+0x6D0]); `sub_5693A80` x3 (rdx=[rbp+0x6A8], [rbp+0x680], [rbp+0x658]).
- Writes: byte [rcx+0x60]=1; [rcx+0x58]=[rax-0x10].

### BB11 loc_bc8b481..0xbc8b50c — small-string assign [rbp+0x628] into [rsi+8]
- Calls: `sub_9d6d0` (heap branch) or `sub_eec6de0` (inline branch); `sub_e935700` (dtor of old [rbp+0x648] if >0x10).
- Writes: [rsi+0x20]=rbx; [rsi+8]=rax; [rsi+0x30]=0; [rax+0x58]=0.

### BB12 loc_bc8b50c..0xbc8b786 — small-string dtors + refcount releases
- Calls: `sub_e935700` x7 (dtors for [rbp+0x648], [rbp+0xA70], [rbp+0xBB0], [rbp+0xBF8], [rbp+0xB80], [rbp+0xC18], [rbp+0xC50]); refcount `lock dec` + [0xF99FFA0] release for [rbp+0x778]; array scan [rbp+0x728] releasing entries with byte [rsi+0x18]==2 ([0xF99FFA0] x2 each); [rbp+0xBE0] release ([0xF99FFA0] x2).
- Writes: zeroed size/capacity fields (e.g. [rbp+0x640]=0, [rbp+0x648]=0xF, ...); released pointers nulled.

### BB13 loc_bc8b81d..0xbc8b8bd — epilogue + return
- Calls: `sub_56D5810` (rcx=[rbp+0x9C0]); `sub_9BD3C0` (rcx=[rbp+0xA60]).
- Writes: epilogue restores xmm6, pops rbx/r12-r15/rsi/rdi/rbp, `add rsp,0xD08`, `ret` at 0xbc8b8bd.

### BB14 loc_bc8b8be..0xbc8b8cf — allocation failure path
- Calls: `sub_78ED0`; `sub_9bc830` (ecx=0x88); then `jmp 0xBC8A7DD`.
- Writes: none (noreturn path).

### BB15-BB19 loc_bc8b8d4..0xbc8b922 — alloc retry/fail paths
- Calls: `sub_9bc830` (ecx=0x130 / 0x340 / size) then jump back to loc_bc8abc8 / loc_bc8aff7 / loc_bc8b17f / loc_bc8b1a8 / loc_bc8b2d2.

### BB20 loc_bc8b923..0xbc8be70 — input-resource slot resolution (the hash/bind block)
- Reads: global [0xF9A8C78] (registration call with zeroed args); slot globals [0x12AE1B60], [0x12AE1B70], [0x12AE1B80], [0x12AE1B98], [0x12AE1BA8] via `sub_e938cb0`; rodata strings [0xF563B27] "InputFinalColor", [0xF549A53] "InputBufferMotionVectors", [0xF5182C0] "InputTAAHistory", [0xF7E41CA] "Color0", [0xF5B67DB] "Upscaling" (len 9); scratch small-string at [rbp+0x330]/[rbp+0x340]/[rbp+0x348].
- Calls: `call qword ptr [0xF9A8C78]`; `sub_e938cb0` x5 (slot lookup); `sub_79580` x4 (FNV-1a 64 hash, basis `0xCBF29CE484222325`, prime `0x100000001B3`, inline 4-byte then byte loops); `sub_5668ac0` ("Upscaling" registration, rcx=[0x12AE1B88]); `sub_e938d70` x5 (slot register).
- Writes: hash globals [0x12AE1B58]=FNV("InputFinalColor"), [0x12AE1B68]=FNV("InputBufferMotionVectors"), [0x12AE1B78]=FNV("InputTAAHistory"), [0x12AE1BA0]=FNV("Color0"); slots [0x12AE1B60/70/80/98/BA8] via sub_e938d70; [0x12AE1B88] via sub_5668ac0.
- End: `0xbc8be70 jmp 0xBC8A644` (tail jump to handler below the window — target not decoded this run) [V].

### BB21 0xbc8be75..0xbc8be7b — trailing bytes (fall-through only)
- `call 0x75740; nop; int3` — inside rdis's bound but not control-flow reached [I unreached].

## (4) Proof rows

## (5) Proof rows — window 1: 0xbc8ab12..0xbc8ba47 (source: docs/progress/_taa_p1.txt)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc8ab12 | 8 | - | `0xbc8ab12  mov rax,0x33404347445A915D` | stack cookie load | [V] |
| 0xbc8ab1c | - | [rbp+0xB78] | `0xbc8ab1c  mov [rbp+0xB78],rax` | stack cookie store at [rbp+0xB78] | [V] |
| 0xbc8ab23 | - | [rbp+0xC18] | `0xbc8ab23  lea rax,[rbp+0xC18]` | - | [V] |
| 0xbc8ab2a | - | [rbp+0xB28] | `0xbc8ab2a  mov [rbp+0xB28],rax` | - | [V] |
| 0xbc8ab31 | 8 | [rbp+0xB30] | `0xbc8ab31  mov qword ptr [rbp+0xB30],0xC` | - | [V] |
| 0xbc8ab3c | - | [rbp+0xBF8] | `0xbc8ab3c  lea rcx,[rbp+0xBF8]` | - | [V] |
| 0xbc8ab43 | - | [rbp+0xB28] | `0xbc8ab43  lea rdx,[rbp+0xB28]` | - | [V] |
| 0xbc8ab4a | - | ->0x568AD40 | `0xbc8ab4a  call 0x568AD40                                ; -> sub_568ad40` | call sub_568ad40 (pass object 1 init helper) | [V] |
| 0xbc8ab4f | - | - | `0xbc8ab4f  nop` | nop padding | [V] |
| 0xbc8ab50 | 16 | [rbp+0xBF8] | `0xbc8ab50  movups xmm0,[rbp+0xBF8]` | - | [V] |
| 0xbc8ab57 | 16 | [rbp+0xC08] | `0xbc8ab57  movups xmm1,[rbp+0xC08]` | - | [V] |
| 0xbc8ab5e | 16 | [rbp-0x40] | `0xbc8ab5e  movaps [rbp-0x40],xmm1` | - | [V] |
| 0xbc8ab62 | 16 | [rbp-0x50] | `0xbc8ab62  movaps [rbp-0x50],xmm0` | - | [V] |
| 0xbc8ab66 | 8 | [rbp+0xC08] | `0xbc8ab66  mov qword ptr [rbp+0xC08],0` | - | [V] |
| 0xbc8ab71 | 8 | [rbp+0xC10] | `0xbc8ab71  mov qword ptr [rbp+0xC10],0xF` | - | [V] |
| 0xbc8ab7c | 1 | [rbp+0xBF8] | `0xbc8ab7c  mov byte ptr [rbp+0xBF8],0` | - | [V] |
| 0xbc8ab83 | - | [rbp-0x30] | `0xbc8ab83  lea r15,[rbp-0x30]` | - | [V] |
| 0xbc8ab87 | - | [rbp+0x720] | `0xbc8ab87  lea rdx,[rbp+0x720]` | - | [V] |
| 0xbc8ab8e | 8 | - | `0xbc8ab8e  mov rcx,r15` | - | [V] |
| 0xbc8ab91 | - | ->0xBC8C890 | `0xbc8ab91  call 0xBC8C890                                ; -> sub_bc8c890` | call sub_bc8c890 (pass-record/struct copy) | [V] |
| 0xbc8ab96 | - | - | `0xbc8ab96  nop` | nop padding | [V] |
| 0xbc8ab97 | 8 | [rbp+0x2A0] | `0xbc8ab97  mov qword ptr [rbp+0x2A0],0` | - | [V] |
| 0xbc8aba2 | 8 | [0x1233E1A8] | `0xbc8aba2  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]` | - | [V] |
| 0xbc8aba9 | 8 | [rcx] | `0xbc8aba9  mov rax,[rcx]` | - | [V] |
| 0xbc8abac | 8 | [rax+8] | `0xbc8abac  mov rax,[rax+8]` | - | [V] |
| 0xbc8abb0 | 4 | - | `0xbc8abb0  mov edx,0x130` | - | [V] |
| 0xbc8abb5 | 8 | [0xF99FFA0] | `0xbc8abb5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8abbb | - | - | `0xbc8abbb  nop` | nop padding | [V] |
| 0xbc8abbc | 8 | - | `0xbc8abbc  mov r14,rax` | - | [V] |
| 0xbc8abbf | - | - | `0xbc8abbf  test rax,rax` | - | [V] |
| 0xbc8abc2 | - | - | `0xbc8abc2  je 0xBC8B8D4                                  ; -> loc_bc8b8d4` | branch to 0xBC8B8D4 | [V] |
| 0xbc8abc8 | - | [0xF44B2E0] | `0xbc8abc8  lea rax,[0xF44B2E0]                           ; [data_f44b2e0]` | lea rodata 0xF44B2E0 | [V] |
| 0xbc8abcf | - | [r14] | `0xbc8abcf  mov [r14],rax` | - | [V] |
| 0xbc8abd2 | 4 | [r14+8] | `0xbc8abd2  mov dword ptr [r14+8],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8abda | - | - | `0xbc8abda  xorps xmm0,xmm0` | - | [V] |
| 0xbc8abdd | 16 | [r14+0xC] | `0xbc8abdd  movups [r14+0xC],xmm0` | - | [V] |
| 0xbc8abe2 | 4 | [r14+0x1C] | `0xbc8abe2  mov dword ptr [r14+0x1C],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8abea | 16 | [r14+0x20] | `0xbc8abea  movups [r14+0x20],xmm0` | - | [V] |
| 0xbc8abef | 4 | [r14+0x30] | `0xbc8abef  mov dword ptr [r14+0x30],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8abf7 | 16 | [r14+0x34] | `0xbc8abf7  movups [r14+0x34],xmm0` | - | [V] |
| 0xbc8abfc | 8 | [r14+0x44] | `0xbc8abfc  movsd [r14+0x44],xmm6` | - | [V] |
| 0xbc8ac02 | 16 | [r14+0x4C] | `0xbc8ac02  movups [r14+0x4C],xmm0` | - | [V] |
| 0xbc8ac07 | 4 | [r14+0x5C] | `0xbc8ac07  mov dword ptr [r14+0x5C],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8ac0f | 16 | [r14+0x60] | `0xbc8ac0f  movups [r14+0x60],xmm0` | - | [V] |
| 0xbc8ac14 | 4 | [r14+0x70] | `0xbc8ac14  mov dword ptr [r14+0x70],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8ac1c | 16 | [r14+0x74] | `0xbc8ac1c  movups [r14+0x74],xmm0` | - | [V] |
| 0xbc8ac21 | 4 | [r14+0x84] | `0xbc8ac21  mov dword ptr [r14+0x84],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8ac2c | - | [r14+0x88] | `0xbc8ac2c  mov [r14+0x88],r13` | - | [V] |
| 0xbc8ac33 | - | [r14+0x90] | `0xbc8ac33  mov [r14+0x90],r13` | - | [V] |
| 0xbc8ac3a | - | [r14+0x98] | `0xbc8ac3a  mov [r14+0x98],rsi` | - | [V] |
| 0xbc8ac41 | 16 | [r14+0xA0] | `0xbc8ac41  movups [r14+0xA0],xmm0` | - | [V] |
| 0xbc8ac49 | 4 | [r14+0xB0] | `0xbc8ac49  mov dword ptr [r14+0xB0],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8ac54 | 16 | [r14+0xB4] | `0xbc8ac54  movups [r14+0xB4],xmm0` | - | [V] |
| 0xbc8ac5c | 4 | [r14+0xC4] | `0xbc8ac5c  mov dword ptr [r14+0xC4],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8ac67 | 16 | [r14+0xC8] | `0xbc8ac67  movups [r14+0xC8],xmm0` | - | [V] |
| 0xbc8ac6f | 8 | [r14+0xD8] | `0xbc8ac6f  movsd [r14+0xD8],xmm6` | - | [V] |
| 0xbc8ac78 | 16 | [r14+0xE0] | `0xbc8ac78  movups [r14+0xE0],xmm0` | - | [V] |
| 0xbc8ac80 | 4 | [r14+0xF0] | `0xbc8ac80  mov dword ptr [r14+0xF0],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8ac8b | 16 | [r14+0xF4] | `0xbc8ac8b  movups [r14+0xF4],xmm0` | - | [V] |
| 0xbc8ac93 | 4 | [r14+0x104] | `0xbc8ac93  mov dword ptr [r14+0x104],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8ac9e | 16 | [r14+0x108] | `0xbc8ac9e  movups [r14+0x108],xmm0` | - | [V] |
| 0xbc8aca6 | 4 | [r14+0x118] | `0xbc8aca6  mov dword ptr [r14+0x118],0x3F800000` | store 1.0f (0x3F800000) default | [V] |
| 0xbc8acb1 | 16 | [rbp+0x700] | `0xbc8acb1  movaps xmm0,[rbp+0x700]` | - | [V] |
| 0xbc8acb8 | 16 | [r14+0x11C] | `0xbc8acb8  movups [r14+0x11C],xmm0` | - | [V] |
| 0xbc8acc0 | 8 | [rbp+0x2A0] | `0xbc8acc0  cmp qword ptr [rbp+0x2A0],0` | - | [V] |
| 0xbc8acc8 | - | - | `0xbc8acc8  jne 0xBC8B8BE                                 ; -> loc_bc8b8be` | branch to 0xBC8B8BE | [V] |
| 0xbc8acce | - | [rbp+0x2A0] | `0xbc8acce  mov [rbp+0x2A0],r14` | - | [V] |
| 0xbc8acd5 | - | [rbp+0xBA8] | `0xbc8acd5  lea rcx,[rbp+0xBA8]` | - | [V] |
| 0xbc8acdc | - | [rbp+0xC18] | `0xbc8acdc  lea rdx,[rbp+0xC18]` | - | [V] |
| 0xbc8ace3 | - | ->0x76A8A0 | `0xbc8ace3  call 0x76A8A0                                 ; -> sub_76a8a0` | call sub_76a8a0 | [V] |
| 0xbc8ace8 | - | - | `0xbc8ace8  nop` | nop padding | [V] |
| 0xbc8ace9 | 8 | [rbp+0xBA8] | `0xbc8ace9  mov rsi,[rbp+0xBA8]` | - | [V] |
| 0xbc8acf0 | 8 | [rbp+0xBB0] | `0xbc8acf0  mov rcx,[rbp+0xBB0]` | - | [V] |
| 0xbc8acf7 | 8 | [rbp+0xBC8] | `0xbc8acf7  mov rax,[rbp+0xBC8]` | - | [V] |
| 0xbc8acfe | 8 | [rbp+0xBC8] | `0xbc8acfe  mov qword ptr [rbp+0xBC8],0xF` | - | [V] |
| 0xbc8ad09 | 1 | [rbp+0xBB0] | `0xbc8ad09  mov byte ptr [rbp+0xBB0],0` | - | [V] |
| 0xbc8ad10 | 8 | [rbp+0xB70] | `0xbc8ad10  mov qword ptr [rbp+0xB70],0` | - | [V] |
| 0xbc8ad1b | - | [rbp+0xB50] | `0xbc8ad1b  mov [rbp+0xB50],rcx` | - | [V] |
| 0xbc8ad22 | - | [rbp+0xB48] | `0xbc8ad22  mov [rbp+0xB48],rsi` | - | [V] |
| 0xbc8ad29 | 8 | [rbp+0xB60] | `0xbc8ad29  mov qword ptr [rbp+0xB60],0` | - | [V] |
| 0xbc8ad34 | 8 | [rbp+0xB68] | `0xbc8ad34  mov qword ptr [rbp+0xB68],0xF` | - | [V] |
| 0xbc8ad3f | 1 | [rbp+0xB50] | `0xbc8ad3f  mov byte ptr [rbp+0xB50],0` | - | [V] |
| 0xbc8ad46 | - | [rbp+0xA98] | `0xbc8ad46  mov [rbp+0xA98],rbx` | - | [V] |
| 0xbc8ad4d | 2 | [rbp+0xAA0] | `0xbc8ad4d  mov word ptr [rbp+0xAA0],0` | - | [V] |
| 0xbc8ad56 | 4 | [rbp+0xAA4] | `0xbc8ad56  mov dword ptr [rbp+0xAA4],0` | - | [V] |
| 0xbc8ad60 | 1 | [rbp+0xAA8] | `0xbc8ad60  mov byte ptr [rbp+0xAA8],0` | - | [V] |
| 0xbc8ad67 | - | [rbp+0xAB0] | `0xbc8ad67  mov [rbp+0xAB0],r12` | - | [V] |
| 0xbc8ad6e | 1 | [rbp+0xABA] | `0xbc8ad6e  mov byte ptr [rbp+0xABA],0` | - | [V] |
| 0xbc8ad75 | 8 | [rbp+0xBF0] | `0xbc8ad75  mov rdx,[rbp+0xBF0]` | - | [V] |
| 0xbc8ad7c | - | [rbp+0xAC0] | `0xbc8ad7c  mov [rbp+0xAC0],rdx` | - | [V] |
| 0xbc8ad83 | 2 | [rbp+0xAC8] | `0xbc8ad83  mov word ptr [rbp+0xAC8],0` | - | [V] |
| 0xbc8ad8c | 4 | [rbp+0xACC] | `0xbc8ad8c  mov dword ptr [rbp+0xACC],0` | - | [V] |
| 0xbc8ad96 | 1 | [rbp+0xAD0] | `0xbc8ad96  mov byte ptr [rbp+0xAD0],0` | - | [V] |
| 0xbc8ad9d | 8 | [rbp+0xBE8] | `0xbc8ad9d  mov rdx,[rbp+0xBE8]` | - | [V] |
| 0xbc8ada4 | - | [rbp+0xAD8] | `0xbc8ada4  mov [rbp+0xAD8],rdx` | - | [V] |
| 0xbc8adab | 1 | [rbp+0xAE2] | `0xbc8adab  mov byte ptr [rbp+0xAE2],0` | - | [V] |
| 0xbc8adb2 | 8 | [rbp+0xC38] | `0xbc8adb2  mov rdx,[rbp+0xC38]` | - | [V] |
| 0xbc8adb9 | - | [rbp+0xAE8] | `0xbc8adb9  mov [rbp+0xAE8],rdx` | - | [V] |
| 0xbc8adc0 | 2 | [rbp+0xAF0] | `0xbc8adc0  mov word ptr [rbp+0xAF0],0` | - | [V] |
| 0xbc8adc9 | 4 | [rbp+0xAF4] | `0xbc8adc9  mov dword ptr [rbp+0xAF4],0` | - | [V] |
| 0xbc8add3 | 1 | [rbp+0xAF8] | `0xbc8add3  mov byte ptr [rbp+0xAF8],0` | - | [V] |
| 0xbc8adda | 8 | [rbp+0xC50] | `0xbc8adda  mov rdx,[rbp+0xC50]` | - | [V] |
| 0xbc8ade1 | - | [rbp+0xB00] | `0xbc8ade1  mov [rbp+0xB00],rdx` | - | [V] |
| 0xbc8ade8 | 1 | [rbp+0xB0A] | `0xbc8ade8  mov byte ptr [rbp+0xB0A],0` | - | [V] |
| 0xbc8adef | 8 | [rbp+0xC40] | `0xbc8adef  mov rdx,[rbp+0xC40]` | - | [V] |
| 0xbc8adf6 | - | [rbp+0xB10] | `0xbc8adf6  mov [rbp+0xB10],rdx` | - | [V] |
| 0xbc8adfd | 8 | [rbp+0xC48] | `0xbc8adfd  mov rdx,[rbp+0xC48]` | - | [V] |
| 0xbc8ae04 | - | [rbp+0xB18] | `0xbc8ae04  mov [rbp+0xB18],rdx` | - | [V] |
| 0xbc8ae0b | 1 | [rbp+0xB22] | `0xbc8ae0b  mov byte ptr [rbp+0xB22],0` | - | [V] |
| 0xbc8ae12 | 8 | [rbp+0xA90] | `0xbc8ae12  mov qword ptr [rbp+0xA90],0` | - | [V] |
| 0xbc8ae1d | - | [rbp+0xA70] | `0xbc8ae1d  mov [rbp+0xA70],rcx` | - | [V] |
| 0xbc8ae24 | 16 | [rbp+0xBB8] | `0xbc8ae24  movups xmm0,[rbp+0xBB8]` | - | [V] |
| 0xbc8ae2b | 8 | [rbp+0xBB8] | `0xbc8ae2b  mov rcx,[rbp+0xBB8]` | - | [V] |
| 0xbc8ae32 | 8 | [rbp+0xBC0] | `0xbc8ae32  mov qword ptr [rbp+0xBC0],0` | - | [V] |
| 0xbc8ae3d | - | [rbp+0xB58] | `0xbc8ae3d  mov [rbp+0xB58],rcx` | - | [V] |
| 0xbc8ae44 | 16 | [rbp+0xA78] | `0xbc8ae44  movups [rbp+0xA78],xmm0` | - | [V] |
| 0xbc8ae4b | - | [rbp+0xA88] | `0xbc8ae4b  mov [rbp+0xA88],rax` | - | [V] |
| 0xbc8ae52 | - | [rbp+0xA68] | `0xbc8ae52  mov [rbp+0xA68],rsi` | - | [V] |
| 0xbc8ae59 | 16 | [rbp-0x50] | `0xbc8ae59  movaps xmm0,[rbp-0x50]` | - | [V] |
| 0xbc8ae5d | 16 | [rbp-0x40] | `0xbc8ae5d  movaps xmm1,[rbp-0x40]` | - | [V] |
| 0xbc8ae61 | 16 | [rbp+0x340] | `0xbc8ae61  movaps [rbp+0x340],xmm1` | - | [V] |
| 0xbc8ae68 | 16 | [rbp+0x330] | `0xbc8ae68  movaps [rbp+0x330],xmm0` | - | [V] |
| 0xbc8ae6f | 8 | [rbp-0x40] | `0xbc8ae6f  mov qword ptr [rbp-0x40],0` | - | [V] |
| 0xbc8ae77 | 8 | [rbp-0x38] | `0xbc8ae77  mov qword ptr [rbp-0x38],0xF` | - | [V] |
| 0xbc8ae7f | 1 | [rbp-0x50] | `0xbc8ae7f  mov byte ptr [rbp-0x50],0` | - | [V] |
| 0xbc8ae83 | - | [rbp+0x350] | `0xbc8ae83  lea r14,[rbp+0x350]` | - | [V] |
| 0xbc8ae8a | 8 | - | `0xbc8ae8a  mov rcx,r14` | - | [V] |
| 0xbc8ae8d | 8 | - | `0xbc8ae8d  mov rdx,r15` | - | [V] |
| 0xbc8ae90 | - | ->0xBC8C890 | `0xbc8ae90  call 0xBC8C890                                ; -> sub_bc8c890` | call sub_bc8c890 (pass-record/struct copy) | [V] |
| 0xbc8ae95 | - | - | `0xbc8ae95  nop` | nop padding | [V] |
| 0xbc8ae96 | - | [rbp+0xA98] | `0xbc8ae96  lea rbx,[rbp+0xA98]` | - | [V] |
| 0xbc8ae9d | - | [rbp+0x5E8] | `0xbc8ae9d  lea r12,[rbp+0x5E8]` | - | [V] |
| 0xbc8aea4 | 8 | [rbp+0x620] | `0xbc8aea4  mov qword ptr [rbp+0x620],0` | - | [V] |
| 0xbc8aeaf | 8 | [rbp+0x2A0] | `0xbc8aeaf  mov rcx,[rbp+0x2A0]` | - | [V] |
| 0xbc8aeb6 | - | - | `0xbc8aeb6  test rcx,rcx` | - | [V] |
| 0xbc8aeb9 | - | - | `0xbc8aeb9  je short 0xBC8AF11                            ; -> loc_bc8af11` | branch to 0xBC8AF11 | [V] |
| 0xbc8aebb | - | [rbp+0x268] | `0xbc8aebb  lea r15,[rbp+0x268]` | - | [V] |
| 0xbc8aec2 | - | - | `0xbc8aec2  cmp rcx,r15` | - | [V] |
| 0xbc8aec5 | - | - | `0xbc8aec5  je short 0xBC8AED0                            ; -> loc_bc8aed0` | branch to 0xBC8AED0 | [V] |
| 0xbc8aec7 | - | [rbp+0x620] | `0xbc8aec7  mov [rbp+0x620],rcx` | - | [V] |
| 0xbc8aece | - | - | `0xbc8aece  jmp short 0xBC8AF06                           ; -> loc_bc8af06` | branch to 0xBC8AF06 | [V] |
| 0xbc8aed0 | 8 | [rcx] | `0xbc8aed0  mov rax,[rcx]` | - | [V] |
| 0xbc8aed3 | 8 | [rax+8] | `0xbc8aed3  mov rax,[rax+8]` | - | [V] |
| 0xbc8aed7 | 8 | - | `0xbc8aed7  mov rdx,r12` | - | [V] |
| 0xbc8aeda | 8 | [0xF99FFA0] | `0xbc8aeda  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8aee0 | - | [rbp+0x620] | `0xbc8aee0  mov [rbp+0x620],rax` | - | [V] |
| 0xbc8aee7 | 8 | [rbp+0x2A0] | `0xbc8aee7  mov rcx,[rbp+0x2A0]` | - | [V] |
| 0xbc8aeee | - | - | `0xbc8aeee  test rcx,rcx` | - | [V] |
| 0xbc8aef1 | - | - | `0xbc8aef1  je short 0xBC8AF11                            ; -> loc_bc8af11` | branch to 0xBC8AF11 | [V] |
| 0xbc8aef3 | - | - | `0xbc8aef3  cmp rcx,r15` | - | [V] |
| 0xbc8aef6 | - | - | `0xbc8aef6  setne dl` | - | [V] |
| 0xbc8aef9 | 8 | [rcx] | `0xbc8aef9  mov rax,[rcx]` | - | [V] |
| 0xbc8aefc | 8 | [rax+0x20] | `0xbc8aefc  mov rax,[rax+0x20]` | - | [V] |
| 0xbc8af00 | 8 | [0xF99FFA0] | `0xbc8af00  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8af06 | 8 | [rbp+0x2A0] | `0xbc8af06  mov qword ptr [rbp+0x2A0],0` | - | [V] |
| 0xbc8af11 | 8 | [rbp+0x650] | `0xbc8af11  mov qword ptr [rbp+0x650],0` | - | [V] |
| 0xbc8af1c | 16 | [rbx-0x28] | `0xbc8af1c  movups xmm0,[rbx-0x28]` | - | [V] |
| 0xbc8af20 | 16 | [rbx-0x18] | `0xbc8af20  movups xmm1,[rbx-0x18]` | - | [V] |
| 0xbc8af24 | 16 | [rbp+0x630] | `0xbc8af24  movaps [rbp+0x630],xmm0` | - | [V] |
| 0xbc8af2b | 16 | [rbp+0x640] | `0xbc8af2b  movaps [rbp+0x640],xmm1` | - | [V] |
| 0xbc8af32 | 8 | [rbp+0xA80] | `0xbc8af32  mov qword ptr [rbp+0xA80],0` | - | [V] |
| 0xbc8af3d | 8 | [rbp+0xA88] | `0xbc8af3d  mov qword ptr [rbp+0xA88],0xF` | - | [V] |
| 0xbc8af48 | 1 | [rbp+0xA70] | `0xbc8af48  mov byte ptr [rbp+0xA70],0` | - | [V] |
| 0xbc8af4f | - | [rbp+0x628] | `0xbc8af4f  mov [rbp+0x628],rsi` | - | [V] |
| 0xbc8af56 | 8 | [rbx+0x20] | `0xbc8af56  mov rax,[rbx+0x20]` | - | [V] |
| 0xbc8af5a | - | [rbp+0x678] | `0xbc8af5a  mov [rbp+0x678],rax` | - | [V] |
| 0xbc8af61 | 16 | [rbx] | `0xbc8af61  movups xmm0,[rbx]` | - | [V] |
| 0xbc8af64 | 16 | [rbx+0x10] | `0xbc8af64  movups xmm1,[rbx+0x10]` | - | [V] |
| 0xbc8af68 | 16 | [rbp+0x668] | `0xbc8af68  movups [rbp+0x668],xmm1` | - | [V] |
| 0xbc8af6f | 16 | [rbp+0x658] | `0xbc8af6f  movups [rbp+0x658],xmm0` | - | [V] |
| 0xbc8af76 | 8 | [rbx+0x48] | `0xbc8af76  mov rax,[rbx+0x48]` | - | [V] |
| 0xbc8af7a | - | [rbp+0x6A0] | `0xbc8af7a  mov [rbp+0x6A0],rax` | - | [V] |
| 0xbc8af81 | 16 | [rbx+0x28] | `0xbc8af81  movups xmm0,[rbx+0x28]` | - | [V] |
| 0xbc8af85 | 16 | [rbx+0x38] | `0xbc8af85  movups xmm1,[rbx+0x38]` | - | [V] |
| 0xbc8af89 | 16 | [rbp+0x690] | `0xbc8af89  movaps [rbp+0x690],xmm1` | - | [V] |
| 0xbc8af90 | 16 | [rbp+0x680] | `0xbc8af90  movaps [rbp+0x680],xmm0` | - | [V] |
| 0xbc8af97 | 8 | [rbx+0x70] | `0xbc8af97  mov rax,[rbx+0x70]` | - | [V] |
| 0xbc8af9b | - | [rbp+0x6C8] | `0xbc8af9b  mov [rbp+0x6C8],rax` | - | [V] |
| 0xbc8afa2 | 16 | [rbx+0x50] | `0xbc8afa2  movups xmm0,[rbx+0x50]` | - | [V] |
| 0xbc8afa6 | 16 | [rbx+0x60] | `0xbc8afa6  movups xmm1,[rbx+0x60]` | - | [V] |
| 0xbc8afaa | 16 | [rbp+0x6B8] | `0xbc8afaa  movups [rbp+0x6B8],xmm1` | - | [V] |
| 0xbc8afb1 | 16 | [rbp+0x6A8] | `0xbc8afb1  movups [rbp+0x6A8],xmm0` | - | [V] |
| 0xbc8afb8 | 8 | [rbx+0x88] | `0xbc8afb8  mov rax,[rbx+0x88]` | - | [V] |
| 0xbc8afbf | - | [rbp+0x6E0] | `0xbc8afbf  mov [rbp+0x6E0],rax` | - | [V] |
| 0xbc8afc6 | 16 | [rbx+0x78] | `0xbc8afc6  movups xmm0,[rbx+0x78]` | - | [V] |
| 0xbc8afca | 16 | [rbp+0x6D0] | `0xbc8afca  movaps [rbp+0x6D0],xmm0` | - | [V] |
| 0xbc8afd1 | 8 | [0x1233E1A8] | `0xbc8afd1  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]` | - | [V] |
| 0xbc8afd8 | 8 | [rcx] | `0xbc8afd8  mov rax,[rcx]` | - | [V] |
| 0xbc8afdb | 8 | [rax+8] | `0xbc8afdb  mov rax,[rax+8]` | - | [V] |
| 0xbc8afdf | 4 | - | `0xbc8afdf  mov edx,0x340` | - | [V] |
| 0xbc8afe4 | 8 | [0xF99FFA0] | `0xbc8afe4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8afea | - | - | `0xbc8afea  nop` | nop padding | [V] |
| 0xbc8afeb | 8 | - | `0xbc8afeb  mov r13,rax` | - | [V] |
| 0xbc8afee | - | - | `0xbc8afee  test rax,rax` | - | [V] |
| 0xbc8aff1 | - | - | `0xbc8aff1  je 0xBC8B8E4                                  ; -> loc_bc8b8e4` | branch to 0xBC8B8E4 | [V] |
| 0xbc8aff7 | 8 | - | `0xbc8aff7  mov rax,0x100000001` | - | [V] |
| 0xbc8b001 | - | [r13+8] | `0xbc8b001  mov [r13+8],rax` | - | [V] |
| 0xbc8b005 | - | [0xF09A740] | `0xbc8b005  lea rax,[0xF09A740]                           ; [data_f09a740]` | lea rodata 0xF09A740 | [V] |
| 0xbc8b00c | - | [r13] | `0xbc8b00c  mov [r13],rax` | - | [V] |
| 0xbc8b010 | 8 | [rbp+0x348] | `0xbc8b010  mov rbx,[rbp+0x348]` | - | [V] |
| 0xbc8b017 | 8 | [rbp+0x330] | `0xbc8b017  mov rsi,[rbp+0x330]` | - | [V] |
| 0xbc8b01e | 8 | [rbp+0x340] | `0xbc8b01e  mov r15,[rbp+0x340]` | - | [V] |
| 0xbc8b025 | - | - | `0xbc8b025  xorps xmm0,xmm0` | - | [V] |
| 0xbc8b028 | 16 | [r13+0x28] | `0xbc8b028  movups [r13+0x28],xmm0` | - | [V] |
| 0xbc8b02d | 16 | [r13+0x18] | `0xbc8b02d  movups [r13+0x18],xmm0` | - | [V] |
| 0xbc8b032 | 8 | [r13+0x38] | `0xbc8b032  mov qword ptr [r13+0x38],0xF` | - | [V] |
| 0xbc8b03a | 8 | [r13+0x40] | `0xbc8b03a  mov qword ptr [r13+0x40],0` | - | [V] |
| 0xbc8b042 | - | [0xF44B2C0] | `0xbc8b042  lea rax,[0xF44B2C0]                           ; [data_f44b2c0]` | lea rodata 0xF44B2C0 | [V] |
| 0xbc8b049 | - | [r13+0x10] | `0xbc8b049  mov [r13+0x10],rax` | - | [V] |
| 0xbc8b04d | - | [r13+0x48] | `0xbc8b04d  lea rax,[r13+0x48]` | - | [V] |
| 0xbc8b051 | - | [rbp+0xC48] | `0xbc8b051  mov [rbp+0xC48],rax` | - | [V] |
| 0xbc8b058 | - | [rbp+0xC60] | `0xbc8b058  mov [rbp+0xC60],r13` | - | [V] |
| 0xbc8b05f | 8 | [r13+0x80] | `0xbc8b05f  mov qword ptr [r13+0x80],0` | - | [V] |
| 0xbc8b06a | 8 | [rbp+0x620] | `0xbc8b06a  mov rcx,[rbp+0x620]` | - | [V] |
| 0xbc8b071 | - | - | `0xbc8b071  test rcx,rcx` | - | [V] |
| 0xbc8b074 | - | - | `0xbc8b074  je short 0xBC8B0D7                            ; -> loc_bc8b0d7` | branch to 0xBC8B0D7 | [V] |
| 0xbc8b076 | - | - | `0xbc8b076  cmp rcx,r12` | - | [V] |
| 0xbc8b079 | - | - | `0xbc8b079  je short 0xBC8B08B                            ; -> loc_bc8b08b` | branch to 0xBC8B08B | [V] |
| 0xbc8b07b | 8 | [rbp+0xC60] | `0xbc8b07b  mov rax,[rbp+0xC60]` | - | [V] |
| 0xbc8b082 | - | [rax+0x80] | `0xbc8b082  mov [rax+0x80],rcx` | - | [V] |
| 0xbc8b089 | - | - | `0xbc8b089  jmp short 0xBC8B0CC                           ; -> loc_bc8b0cc` | branch to 0xBC8B0CC | [V] |
| 0xbc8b08b | 8 | [rcx] | `0xbc8b08b  mov rax,[rcx]` | - | [V] |
| 0xbc8b08e | 8 | [rax+8] | `0xbc8b08e  mov rax,[rax+8]` | - | [V] |
| 0xbc8b092 | 8 | [rbp+0xC48] | `0xbc8b092  mov rdx,[rbp+0xC48]` | - | [V] |
| 0xbc8b099 | 8 | [0xF99FFA0] | `0xbc8b099  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b09f | 8 | [rbp+0xC60] | `0xbc8b09f  mov rcx,[rbp+0xC60]` | - | [V] |
| 0xbc8b0a6 | - | [rcx+0x80] | `0xbc8b0a6  mov [rcx+0x80],rax` | - | [V] |
| 0xbc8b0ad | 8 | [rbp+0x620] | `0xbc8b0ad  mov rcx,[rbp+0x620]` | - | [V] |
| 0xbc8b0b4 | - | - | `0xbc8b0b4  test rcx,rcx` | - | [V] |
| 0xbc8b0b7 | - | - | `0xbc8b0b7  je short 0xBC8B0D7                            ; -> loc_bc8b0d7` | branch to 0xBC8B0D7 | [V] |
| 0xbc8b0b9 | - | - | `0xbc8b0b9  cmp rcx,r12` | - | [V] |
| 0xbc8b0bc | - | - | `0xbc8b0bc  setne dl` | - | [V] |
| 0xbc8b0bf | 8 | [rcx] | `0xbc8b0bf  mov rax,[rcx]` | - | [V] |
| 0xbc8b0c2 | 8 | [rax+0x20] | `0xbc8b0c2  mov rax,[rax+0x20]` | - | [V] |
| 0xbc8b0c6 | 8 | [0xF99FFA0] | `0xbc8b0c6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b0cc | 8 | [rbp+0x620] | `0xbc8b0cc  mov qword ptr [rbp+0x620],0` | - | [V] |
| 0xbc8b0d7 | 8 | [rbp+0xC60] | `0xbc8b0d7  mov rcx,[rbp+0xC60]` | - | [V] |
| 0xbc8b0de | - | [rcx+0x10] | `0xbc8b0de  lea rax,[rcx+0x10]` | - | [V] |
| 0xbc8b0e2 | - | [rbp+0xC40] | `0xbc8b0e2  mov [rbp+0xC40],rax` | - | [V] |
| 0xbc8b0e9 | - | [rcx+0x88] | `0xbc8b0e9  lea r12,[rcx+0x88]` | - | [V] |
| 0xbc8b0f0 | 8 | - | `0xbc8b0f0  mov rcx,r12` | - | [V] |
| 0xbc8b0f3 | 8 | - | `0xbc8b0f3  mov rdx,r14` | - | [V] |
| 0xbc8b0f6 | - | ->0xBC8C890 | `0xbc8b0f6  call 0xBC8C890                                ; -> sub_bc8c890` | call sub_bc8c890 (pass-record/struct copy) | [V] |
| 0xbc8b0fb | - | - | `0xbc8b0fb  nop` | nop padding | [V] |
| 0xbc8b0fc | - | [rbp+0xC50] | `0xbc8b0fc  mov [rbp+0xC50],r12` | - | [V] |
| 0xbc8b103 | - | - | `0xbc8b103  xorps xmm0,xmm0` | - | [V] |
| 0xbc8b106 | 8 | [rbp+0xC60] | `0xbc8b106  mov r12,[rbp+0xC60]` | - | [V] |
| 0xbc8b10d | 16 | [r12+0x330] | `0xbc8b10d  movups [r12+0x330],xmm0` | - | [V] |
| 0xbc8b116 | 16 | [r12+0x320] | `0xbc8b116  movups [r12+0x320],xmm0` | - | [V] |
| 0xbc8b11f | - | - | `0xbc8b11f  test r15,r15` | - | [V] |
| 0xbc8b122 | - | - | `0xbc8b122  js 0xBC8BB70                                  ; -> loc_bc8bb70` | branch to 0xBC8BB70 | [V] |
| 0xbc8b128 | - | [r12+0x320] | `0xbc8b128  lea r14,[r12+0x320]` | - | [V] |
| 0xbc8b130 | 4 | - | `0xbc8b130  mov r13d,0xF` | - | [V] |
| 0xbc8b136 | - | - | `0xbc8b136  cmp r15,0x10` | - | [V] |
| 0xbc8b13a | - | - | `0xbc8b13a  jb short 0xBC8B1B5                            ; -> loc_bc8b1b5` | branch to 0xBC8B1B5 | [V] |
| 0xbc8b13c | 8 | - | `0xbc8b13c  mov rdx,r15` | - | [V] |
| 0xbc8b13f | - | - | `0xbc8b13f  or rdx,0xF` | - | [V] |
| 0xbc8b143 | - | - | `0xbc8b143  cmp rdx,0x17` | - | [V] |
| 0xbc8b147 | 4 | - | `0xbc8b147  mov r13d,0x16` | - | [V] |
| 0xbc8b14d | - | - | `0xbc8b14d  cmovae r13,rdx` | - | [V] |
| 0xbc8b151 | 8 | [0x1233E1A8] | `0xbc8b151  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]` | - | [V] |
| 0xbc8b158 | 8 | [rcx] | `0xbc8b158  mov rax,[rcx]` | - | [V] |
| 0xbc8b15b | 8 | [rax+8] | `0xbc8b15b  mov rax,[rax+8]` | - | [V] |
| 0xbc8b15f | - | - | `0xbc8b15f  cmp rdx,0xFFF` | - | [V] |
| 0xbc8b166 | - | - | `0xbc8b166  jb short 0xBC8B191                            ; -> loc_bc8b191` | branch to 0xBC8B191 | [V] |
| 0xbc8b168 | - | [r13+0x28] | `0xbc8b168  lea rdx,[r13+0x28]` | - | [V] |
| 0xbc8b16c | 8 | [0xF99FFA0] | `0xbc8b16c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b172 | - | - | `0xbc8b172  nop` | nop padding | [V] |
| 0xbc8b173 | 8 | - | `0xbc8b173  mov r12,rax` | - | [V] |
| 0xbc8b176 | - | - | `0xbc8b176  test rax,rax` | - | [V] |
| 0xbc8b179 | - | - | `0xbc8b179  je 0xBC8B8F4                                  ; -> loc_bc8b8f4` | branch to 0xBC8B8F4 | [V] |
| 0xbc8b17f | 8 | - | `0xbc8b17f  mov rax,r12` | - | [V] |
| 0xbc8b182 | - | - | `0xbc8b182  add r12,0x27` | - | [V] |
| 0xbc8b186 | - | - | `0xbc8b186  and r12,0xFFFFFFFFFFFFFFE0` | - | [V] |
| 0xbc8b18a | - | [r12-8] | `0xbc8b18a  mov [r12-8],rax` | - | [V] |
| 0xbc8b18f | - | - | `0xbc8b18f  jmp short 0xBC8B1A8                           ; -> loc_bc8b1a8` | branch to 0xBC8B1A8 | [V] |
| 0xbc8b191 | - | [r13+1] | `0xbc8b191  lea rdx,[r13+1]` | - | [V] |
| 0xbc8b195 | 8 | [0xF99FFA0] | `0xbc8b195  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b19b | - | - | `0xbc8b19b  nop` | nop padding | [V] |
| 0xbc8b19c | 8 | - | `0xbc8b19c  mov r12,rax` | - | [V] |
| 0xbc8b19f | - | - | `0xbc8b19f  test rax,rax` | - | [V] |
| 0xbc8b1a2 | - | - | `0xbc8b1a2  je 0xBC8B903                                  ; -> loc_bc8b903` | branch to 0xBC8B903 | [V] |
| 0xbc8b1a8 | - | [r14] | `0xbc8b1a8  mov [r14],r12` | - | [V] |
| 0xbc8b1ab | 8 | - | `0xbc8b1ab  mov r14,r12` | - | [V] |
| 0xbc8b1ae | 8 | [rbp+0xC60] | `0xbc8b1ae  mov r12,[rbp+0xC60]` | - | [V] |
| 0xbc8b1b5 | - | - | `0xbc8b1b5  cmp rbx,0x10` | - | [V] |
| 0xbc8b1b9 | - | [rbp+0x330] | `0xbc8b1b9  lea rdx,[rbp+0x330]` | - | [V] |
| 0xbc8b1c0 | - | - | `0xbc8b1c0  cmovae rdx,rsi` | - | [V] |
| 0xbc8b1c4 | - | [r12+0x330] | `0xbc8b1c4  mov [r12+0x330],r15` | - | [V] |
| 0xbc8b1cc | - | [r12+0x338] | `0xbc8b1cc  mov [r12+0x338],r13` | - | [V] |
| 0xbc8b1d4 | 8 | - | `0xbc8b1d4  mov rcx,r14` | - | [V] |
| 0xbc8b1d7 | 8 | - | `0xbc8b1d7  mov r8,r15` | - | [V] |
| 0xbc8b1da | - | ->0xEEC6EC0 | `0xbc8b1da  call 0xEEC6EC0                                ; -> sub_eec6ec0` | call sub_eec6ec0 (memcpy) | [V] |
| 0xbc8b1df | 1 | [r14+r15] | `0xbc8b1df  mov byte ptr [r14+r15],0` | - | [V] |
| 0xbc8b1e4 | 8 | [rbp+0xC58] | `0xbc8b1e4  mov rcx,[rbp+0xC58]` | - | [V] |
| 0xbc8b1eb | 8 | [rcx+0x10] | `0xbc8b1eb  mov rsi,[rcx+0x10]` | - | [V] |
| 0xbc8b1ef | - | [rcx+0x18] | `0xbc8b1ef  cmp rsi,[rcx+0x18]` | - | [V] |
| 0xbc8b1f3 | - | - | `0xbc8b1f3  je short 0xBC8B214                            ; -> loc_bc8b214` | branch to 0xBC8B214 | [V] |
| 0xbc8b1f5 | 8 | [rbp+0xC40] | `0xbc8b1f5  mov rax,[rbp+0xC40]` | - | [V] |
| 0xbc8b1fc | - | [rsi] | `0xbc8b1fc  mov [rsi],rax` | - | [V] |
| 0xbc8b1ff | - | [rsi+8] | `0xbc8b1ff  mov [rsi+8],r12` | - | [V] |
| 0xbc8b203 | 8 | [rcx+0x10] | `0xbc8b203  mov rax,[rcx+0x10]` | - | [V] |
| 0xbc8b207 | - | - | `0xbc8b207  add rax,0x10` | - | [V] |
| 0xbc8b20b | - | [rcx+0x10] | `0xbc8b20b  mov [rcx+0x10],rax` | - | [V] |
| 0xbc8b20f | - | - | `0xbc8b20f  jmp 0xBC8B42C                                 ; -> loc_bc8b42c` | branch to 0xBC8B42C | [V] |
| 0xbc8b214 | - | [rcx+8] | `0xbc8b214  lea r8,[rcx+8]` | - | [V] |
| 0xbc8b218 | 8 | - | `0xbc8b218  mov r9,r12` | - | [V] |
| 0xbc8b21b | - | - | `0xbc8b21b  add r9,0xC` | - | [V] |
| 0xbc8b21f | 8 | - | `0xbc8b21f  mov rbx,rsi` | - | [V] |
| 0xbc8b222 | - | [r8] | `0xbc8b222  sub rbx,[r8]` | - | [V] |
| 0xbc8b225 | 8 | - | `0xbc8b225  mov rax,rbx` | - | [V] |
| 0xbc8b228 | - | - | `0xbc8b228  sar rax,4` | - | [V] |
| 0xbc8b22c | - | [rax+1] | `0xbc8b22c  lea r14,[rax+1]` | - | [V] |
| 0xbc8b230 | 8 | - | `0xbc8b230  mov r15,rax` | - | [V] |
| 0xbc8b233 | - | - | `0xbc8b233  shr r15,1` | - | [V] |
| 0xbc8b236 | 8 | - | `0xbc8b236  mov rcx,0xFFFFFFFFFFFFFFF` | - | [V] |
| 0xbc8b240 | 8 | - | `0xbc8b240  mov rdx,rcx` | - | [V] |
| 0xbc8b243 | - | - | `0xbc8b243  sub rdx,r15` | - | [V] |
| 0xbc8b246 | - | - | `0xbc8b246  add r15,rax` | - | [V] |
| 0xbc8b249 | - | - | `0xbc8b249  cmp r15,r14` | - | [V] |
| 0xbc8b24c | - | - | `0xbc8b24c  cmovbe r15,r14` | - | [V] |
| 0xbc8b250 | - | - | `0xbc8b250  cmp rax,rdx` | - | [V] |
| 0xbc8b253 | - | - | `0xbc8b253  cmova r15,rcx` | - | [V] |
| 0xbc8b257 | - | [r12+8] | `0xbc8b257  lea rcx,[r12+8]` | - | [V] |
| 0xbc8b25c | 8 | - | `0xbc8b25c  mov rax,r15` | - | [V] |
| 0xbc8b25f | - | - | `0xbc8b25f  shr rax,0x3C` | - | [V] |
| 0xbc8b263 | - | - | `0xbc8b263  jne 0xBC8BB76                                 ; -> loc_bc8bb76` | branch to 0xBC8BB76 | [V] |
| 0xbc8b269 | - | - | `0xbc8b269  test r15,r15` | - | [V] |
| 0xbc8b26c | - | [rbp+0xC48] | `0xbc8b26c  mov [rbp+0xC48],r8` | - | [V] |
| 0xbc8b273 | - | - | `0xbc8b273  je 0xBC8B30D                                  ; -> loc_bc8b30d` | branch to 0xBC8B30D | [V] |
| 0xbc8b279 | - | [rbp+0xC38] | `0xbc8b279  mov [rbp+0xC38],r9` | - | [V] |
| 0xbc8b280 | 8 | - | `0xbc8b280  mov r13,r15` | - | [V] |
| 0xbc8b283 | - | - | `0xbc8b283  shl r13,4` | - | [V] |
| 0xbc8b287 | - | - | `0xbc8b287  cmp r15,0x100` | - | [V] |
| 0xbc8b28e | - | [rbp+0xC50] | `0xbc8b28e  mov [rbp+0xC50],rcx` | - | [V] |
| 0xbc8b295 | - | - | `0xbc8b295  jb short 0xBC8B2E4                            ; -> loc_bc8b2e4` | branch to 0xBC8B2E4 | [V] |
| 0xbc8b297 | 8 | - | `0xbc8b297  mov rax,0xFFFFFFFFFFFFFFE` | - | [V] |
| 0xbc8b2a1 | - | - | `0xbc8b2a1  cmp r15,rax` | - | [V] |
| 0xbc8b2a4 | - | - | `0xbc8b2a4  jae 0xBC8BE75                                 ; -> loc_bc8be75` | branch to 0xBC8BE75 | [V] |
| 0xbc8b2aa | - | - | `0xbc8b2aa  add r13,0x27` | - | [V] |
| 0xbc8b2ae | 8 | [0x1233E1A8] | `0xbc8b2ae  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]` | - | [V] |
| 0xbc8b2b5 | 8 | [rcx] | `0xbc8b2b5  mov rax,[rcx]` | - | [V] |
| 0xbc8b2b8 | 8 | [rax+8] | `0xbc8b2b8  mov rax,[rax+8]` | - | [V] |
| 0xbc8b2bc | 8 | - | `0xbc8b2bc  mov rdx,r13` | - | [V] |
| 0xbc8b2bf | 8 | [0xF99FFA0] | `0xbc8b2bf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b2c5 | - | - | `0xbc8b2c5  nop` | nop padding | [V] |
| 0xbc8b2c6 | 8 | - | `0xbc8b2c6  mov r12,rax` | - | [V] |
| 0xbc8b2c9 | - | - | `0xbc8b2c9  test rax,rax` | - | [V] |
| 0xbc8b2cc | - | - | `0xbc8b2cc  je 0xBC8B915                                  ; -> loc_bc8b915` | branch to 0xBC8B915 | [V] |
| 0xbc8b2d2 | 8 | - | `0xbc8b2d2  mov rax,r12` | - | [V] |
| 0xbc8b2d5 | - | - | `0xbc8b2d5  add r12,0x27` | - | [V] |
| 0xbc8b2d9 | - | - | `0xbc8b2d9  and r12,0xFFFFFFFFFFFFFFE0` | - | [V] |
| 0xbc8b2dd | - | [r12-8] | `0xbc8b2dd  mov [r12-8],rax` | - | [V] |
| 0xbc8b2e2 | - | - | `0xbc8b2e2  jmp short 0xBC8B310                           ; -> loc_bc8b310` | branch to 0xBC8B310 | [V] |
| 0xbc8b2e4 | 8 | [0x1233E1A8] | `0xbc8b2e4  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]` | - | [V] |
| 0xbc8b2eb | 8 | [rcx] | `0xbc8b2eb  mov rax,[rcx]` | - | [V] |
| 0xbc8b2ee | 8 | [rax+8] | `0xbc8b2ee  mov rax,[rax+8]` | - | [V] |
| 0xbc8b2f2 | 8 | - | `0xbc8b2f2  mov rdx,r13` | - | [V] |
| 0xbc8b2f5 | 8 | [0xF99FFA0] | `0xbc8b2f5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b2fb | - | - | `0xbc8b2fb  nop` | nop padding | [V] |
| 0xbc8b2fc | 8 | - | `0xbc8b2fc  mov r12,rax` | - | [V] |
| 0xbc8b2ff | - | - | `0xbc8b2ff  test rax,rax` | - | [V] |
| 0xbc8b302 | - | - | `0xbc8b302  jne short 0xBC8B310                           ; -> loc_bc8b310` | branch to 0xBC8B310 | [V] |
| 0xbc8b304 | 8 | - | `0xbc8b304  mov rcx,r13` | - | [V] |
| 0xbc8b307 | - | ->0x9BC830 | `0xbc8b307  call 0x9BC830                                 ; -> sub_9bc830` | call sub_9bc830 (alloc-fail/raise) | [V] |
| 0xbc8b30c | - | - | `0xbc8b30c  nop` | nop padding | [V] |
| 0xbc8b30d | - | - | `0xbc8b30d  xor r12d,r12d` | - | [V] |
| 0xbc8b310 | 8 | [rbp+0xC40] | `0xbc8b310  mov rax,[rbp+0xC40]` | - | [V] |
| 0xbc8b317 | - | [r12+rbx] | `0xbc8b317  mov [r12+rbx],rax` | - | [V] |
| 0xbc8b31b | 8 | [rbp+0xC60] | `0xbc8b31b  mov rax,[rbp+0xC60]` | - | [V] |
| 0xbc8b322 | - | [r12+rbx+8] | `0xbc8b322  mov [r12+rbx+8],rax` | - | [V] |
| 0xbc8b327 | 8 | [rbp+0xC58] | `0xbc8b327  mov rcx,[rbp+0xC58]` | - | [V] |
| 0xbc8b32e | 8 | [rcx+8] | `0xbc8b32e  mov rax,[rcx+8]` | - | [V] |
| 0xbc8b332 | 8 | [rcx+0x10] | `0xbc8b332  mov rcx,[rcx+0x10]` | - | [V] |
| 0xbc8b336 | - | - | `0xbc8b336  cmp rsi,rcx` | - | [V] |
| 0xbc8b339 | - | - | `0xbc8b339  je 0xBC8B3CD                                  ; -> loc_bc8b3cd` | branch to 0xBC8B3CD | [V] |
| 0xbc8b33f | - | - | `0xbc8b33f  cmp rax,rsi` | - | [V] |
| 0xbc8b342 | - | - | `0xbc8b342  je short 0xBC8B387                            ; -> loc_bc8b387` | branch to 0xBC8B387 | [V] |
| 0xbc8b344 | - | - | `0xbc8b344  xor ecx,ecx` | - | [V] |
| 0xbc8b346 | - | - | `0xbc8b346  xorps xmm0,xmm0` | - | [V] |
| 0xbc8b349 | - | [rax] | `0xbc8b349  nop [rax]` | nop padding | [V] |
| 0xbc8b350 | 16 | [r12+rcx] | `0xbc8b350  movups [r12+rcx],xmm0` | - | [V] |
| 0xbc8b355 | 8 | [rax+rcx] | `0xbc8b355  mov rdx,[rax+rcx]` | - | [V] |
| 0xbc8b359 | - | [r12+rcx] | `0xbc8b359  mov [r12+rcx],rdx` | - | [V] |
| 0xbc8b35d | 8 | [rax+rcx+8] | `0xbc8b35d  mov rdx,[rax+rcx+8]` | - | [V] |
| 0xbc8b362 | - | [r12+rcx+8] | `0xbc8b362  mov [r12+rcx+8],rdx` | - | [V] |
| 0xbc8b367 | 16 | [rax+rcx] | `0xbc8b367  movups [rax+rcx],xmm0` | - | [V] |
| 0xbc8b36b | - | [rax+rcx] | `0xbc8b36b  lea rdx,[rax+rcx]` | - | [V] |
| 0xbc8b36f | - | - | `0xbc8b36f  add rdx,0x10` | - | [V] |
| 0xbc8b373 | - | - | `0xbc8b373  add rcx,0x10` | - | [V] |
| 0xbc8b377 | - | - | `0xbc8b377  cmp rdx,rsi` | - | [V] |
| 0xbc8b37a | - | - | `0xbc8b37a  jne short 0xBC8B350                           ; -> loc_bc8b350` | branch to 0xBC8B350 | [V] |
| 0xbc8b37c | 8 | [rbp+0xC58] | `0xbc8b37c  mov rax,[rbp+0xC58]` | - | [V] |
| 0xbc8b383 | 8 | [rax+0x10] | `0xbc8b383  mov rcx,[rax+0x10]` | - | [V] |
| 0xbc8b387 | - | - | `0xbc8b387  cmp rsi,rcx` | - | [V] |
| 0xbc8b38a | - | - | `0xbc8b38a  je 0xBC8B40C                                  ; -> loc_bc8b40c` | branch to 0xBC8B40C | [V] |
| 0xbc8b390 | - | [rbx+r12] | `0xbc8b390  lea rax,[rbx+r12]` | - | [V] |
| 0xbc8b394 | - | - | `0xbc8b394  add rax,0x10` | - | [V] |
| 0xbc8b398 | - | - | `0xbc8b398  xor edx,edx` | - | [V] |
| 0xbc8b39a | - | - | `0xbc8b39a  xorps xmm0,xmm0` | - | [V] |
| 0xbc8b39d | - | [rax] | `0xbc8b39d  nop [rax]` | nop padding | [V] |
| 0xbc8b3a0 | 16 | [rax+rdx] | `0xbc8b3a0  movups [rax+rdx],xmm0` | - | [V] |
| 0xbc8b3a4 | 8 | [rsi+rdx] | `0xbc8b3a4  mov r8,[rsi+rdx]` | - | [V] |
| 0xbc8b3a8 | - | [rax+rdx] | `0xbc8b3a8  mov [rax+rdx],r8` | - | [V] |
| 0xbc8b3ac | 8 | [rsi+rdx+8] | `0xbc8b3ac  mov r8,[rsi+rdx+8]` | - | [V] |
| 0xbc8b3b1 | - | [rax+rdx+8] | `0xbc8b3b1  mov [rax+rdx+8],r8` | - | [V] |
| 0xbc8b3b6 | 16 | [rsi+rdx] | `0xbc8b3b6  movups [rsi+rdx],xmm0` | - | [V] |
| 0xbc8b3ba | - | [rsi+rdx] | `0xbc8b3ba  lea r8,[rsi+rdx]` | - | [V] |
| 0xbc8b3be | - | - | `0xbc8b3be  add r8,0x10` | - | [V] |
| 0xbc8b3c2 | - | - | `0xbc8b3c2  add rdx,0x10` | - | [V] |
| 0xbc8b3c6 | - | - | `0xbc8b3c6  cmp r8,rcx` | - | [V] |
| 0xbc8b3c9 | - | - | `0xbc8b3c9  jne short 0xBC8B3A0                           ; -> loc_bc8b3a0` | branch to 0xBC8B3A0 | [V] |
| 0xbc8b3cb | - | - | `0xbc8b3cb  jmp short 0xBC8B40C                           ; -> loc_bc8b40c` | branch to 0xBC8B40C | [V] |
| 0xbc8b3cd | - | - | `0xbc8b3cd  cmp rax,rsi` | - | [V] |
| 0xbc8b3d0 | - | - | `0xbc8b3d0  je short 0xBC8B40C                            ; -> loc_bc8b40c` | branch to 0xBC8B40C | [V] |
| 0xbc8b3d2 | - | - | `0xbc8b3d2  xor ecx,ecx` | - | [V] |
| 0xbc8b3d4 | - | - | `0xbc8b3d4  xorps xmm0,xmm0` | - | [V] |
| 0xbc8b3d7 | - | [rax+rax] | `0xbc8b3d7  nop [rax+rax]` | nop padding | [V] |
| 0xbc8b3e0 | 16 | [r12+rcx] | `0xbc8b3e0  movups [r12+rcx],xmm0` | - | [V] |
| 0xbc8b3e5 | 8 | [rax+rcx] | `0xbc8b3e5  mov rdx,[rax+rcx]` | - | [V] |
| 0xbc8b3e9 | - | [r12+rcx] | `0xbc8b3e9  mov [r12+rcx],rdx` | - | [V] |
| 0xbc8b3ed | 8 | [rax+rcx+8] | `0xbc8b3ed  mov rdx,[rax+rcx+8]` | - | [V] |
| 0xbc8b3f2 | - | [r12+rcx+8] | `0xbc8b3f2  mov [r12+rcx+8],rdx` | - | [V] |
| 0xbc8b3f7 | 16 | [rax+rcx] | `0xbc8b3f7  movups [rax+rcx],xmm0` | - | [V] |
| 0xbc8b3fb | - | [rax+rcx] | `0xbc8b3fb  lea rdx,[rax+rcx]` | - | [V] |
| 0xbc8b3ff | - | - | `0xbc8b3ff  add rdx,0x10` | - | [V] |
| 0xbc8b403 | - | - | `0xbc8b403  add rcx,0x10` | - | [V] |
| 0xbc8b407 | - | - | `0xbc8b407  cmp rdx,rsi` | - | [V] |
| 0xbc8b40a | - | - | `0xbc8b40a  jne short 0xBC8B3E0                           ; -> loc_bc8b3e0` | branch to 0xBC8B3E0 | [V] |
| 0xbc8b40c | 8 | [rbp+0xC48] | `0xbc8b40c  mov rcx,[rbp+0xC48]` | - | [V] |
| 0xbc8b413 | 8 | - | `0xbc8b413  mov rdx,r12` | - | [V] |
| 0xbc8b416 | 8 | - | `0xbc8b416  mov r8,r14` | - | [V] |
| 0xbc8b419 | 8 | - | `0xbc8b419  mov r9,r15` | - | [V] |
| 0xbc8b41c | - | ->0x130EE0 | `0xbc8b41c  call 0x130EE0                                 ; -> sub_130ee0` | call sub_130ee0 | [V] |
| 0xbc8b421 | 8 | [rbp+0xC58] | `0xbc8b421  mov rcx,[rbp+0xC58]` | - | [V] |
| 0xbc8b428 | 8 | [rcx+0x10] | `0xbc8b428  mov rax,[rcx+0x10]` | - | [V] |
| 0xbc8b42c | - | [rbp+0x6D0] | `0xbc8b42c  lea rdx,[rbp+0x6D0]` | - | [V] |
| 0xbc8b433 | 1 | [rcx+0x60] | `0xbc8b433  mov byte ptr [rcx+0x60],1` | - | [V] |
| 0xbc8b437 | 8 | [rax-0x10] | `0xbc8b437  mov rax,[rax-0x10]` | - | [V] |
| 0xbc8b43b | - | [rcx+0x58] | `0xbc8b43b  mov [rcx+0x58],rax` | - | [V] |
| 0xbc8b43f | - | ->0x568C420 | `0xbc8b43f  call 0x568C420                                ; -> sub_568c420` | call sub_568c420 | [V] |
| 0xbc8b444 | - | - | `0xbc8b444  nop` | nop padding | [V] |
| 0xbc8b445 | - | [rbp+0x6A8] | `0xbc8b445  lea rdx,[rbp+0x6A8]` | - | [V] |
| 0xbc8b44c | 8 | [rbp+0xC58] | `0xbc8b44c  mov rcx,[rbp+0xC58]` | - | [V] |
| 0xbc8b453 | - | ->0x5693A80 | `0xbc8b453  call 0x5693A80                                ; -> sub_5693a80` | call sub_5693a80 | [V] |
| 0xbc8b458 | - | - | `0xbc8b458  nop` | nop padding | [V] |
| 0xbc8b459 | - | [rbp+0x680] | `0xbc8b459  lea rdx,[rbp+0x680]` | - | [V] |
| 0xbc8b460 | 8 | [rbp+0xC58] | `0xbc8b460  mov rcx,[rbp+0xC58]` | - | [V] |
| 0xbc8b467 | - | ->0x5693A80 | `0xbc8b467  call 0x5693A80                                ; -> sub_5693a80` | call sub_5693a80 | [V] |
| 0xbc8b46c | - | - | `0xbc8b46c  nop` | nop padding | [V] |
| 0xbc8b46d | - | [rbp+0x658] | `0xbc8b46d  lea rdx,[rbp+0x658]` | - | [V] |
| 0xbc8b474 | 8 | [rbp+0xC58] | `0xbc8b474  mov rcx,[rbp+0xC58]` | - | [V] |
| 0xbc8b47b | - | ->0x5693A80 | `0xbc8b47b  call 0x5693A80                                ; -> sub_5693a80` | call sub_5693a80 | [V] |
| 0xbc8b480 | - | - | `0xbc8b480  nop` | nop padding | [V] |
| 0xbc8b481 | - | [rbp+0x628] | `0xbc8b481  lea rax,[rbp+0x628]` | - | [V] |
| 0xbc8b488 | 8 | [rbp+0xC58] | `0xbc8b488  mov rcx,[rbp+0xC58]` | - | [V] |
| 0xbc8b48f | 8 | [rcx+0x58] | `0xbc8b48f  mov rsi,[rcx+0x58]` | - | [V] |
| 0xbc8b493 | - | [rsi+8] | `0xbc8b493  lea rcx,[rsi+8]` | - | [V] |
| 0xbc8b497 | - | - | `0xbc8b497  cmp rcx,rax` | - | [V] |
| 0xbc8b49a | - | - | `0xbc8b49a  je short 0xBC8B4F9                            ; -> loc_bc8b4f9` | branch to 0xBC8B4F9 | [V] |
| 0xbc8b49c | 8 | [rbp+0x640] | `0xbc8b49c  mov rbx,[rbp+0x640]` | - | [V] |
| 0xbc8b4a3 | 8 | [rbp+0x648] | `0xbc8b4a3  cmp qword ptr [rbp+0x648],0x10` | - | [V] |
| 0xbc8b4ab | - | - | `0xbc8b4ab  jb short 0xBC8B4B6                            ; -> loc_bc8b4b6` | branch to 0xBC8B4B6 | [V] |
| 0xbc8b4ad | 8 | [rbp+0x630] | `0xbc8b4ad  mov r9,[rbp+0x630]` | - | [V] |
| 0xbc8b4b4 | - | - | `0xbc8b4b4  jmp short 0xBC8B4BD                           ; -> loc_bc8b4bd` | branch to 0xBC8B4BD | [V] |
| 0xbc8b4b6 | - | [rbp+0x630] | `0xbc8b4b6  lea r9,[rbp+0x630]` | - | [V] |
| 0xbc8b4bd | - | [rsi+0x10] | `0xbc8b4bd  lea r14,[rsi+0x10]` | - | [V] |
| 0xbc8b4c1 | 8 | [rsi+0x28] | `0xbc8b4c1  mov rax,[rsi+0x28]` | - | [V] |
| 0xbc8b4c5 | - | - | `0xbc8b4c5  cmp rbx,rax` | - | [V] |
| 0xbc8b4c8 | - | - | `0xbc8b4c8  jbe short 0xBC8B4D8                           ; -> loc_bc8b4d8` | branch to 0xBC8B4D8 | [V] |
| 0xbc8b4ca | 8 | - | `0xbc8b4ca  mov rcx,r14` | - | [V] |
| 0xbc8b4cd | 8 | - | `0xbc8b4cd  mov rdx,rbx` | - | [V] |
| 0xbc8b4d0 | - | ->0x9D6D0 | `0xbc8b4d0  call 0x9D6D0                                  ; -> sub_9d6d0` | call sub_9d6d0 (heap string copy) | [V] |
| 0xbc8b4d5 | - | - | `0xbc8b4d5  nop` | nop padding | [V] |
| 0xbc8b4d6 | - | - | `0xbc8b4d6  jmp short 0xBC8B4F9                           ; -> loc_bc8b4f9` | branch to 0xBC8B4F9 | [V] |
| 0xbc8b4d8 | - | - | `0xbc8b4d8  cmp rax,0x10` | - | [V] |
| 0xbc8b4dc | - | - | `0xbc8b4dc  jb short 0xBC8B4E2                            ; -> loc_bc8b4e2` | branch to 0xBC8B4E2 | [V] |
| 0xbc8b4de | 8 | [rsi+0x10] | `0xbc8b4de  mov r14,[rsi+0x10]` | - | [V] |
| 0xbc8b4e2 | - | [rsi+0x20] | `0xbc8b4e2  mov [rsi+0x20],rbx` | - | [V] |
| 0xbc8b4e6 | 8 | - | `0xbc8b4e6  mov rcx,r14` | - | [V] |
| 0xbc8b4e9 | 8 | - | `0xbc8b4e9  mov rdx,r9` | - | [V] |
| 0xbc8b4ec | 8 | - | `0xbc8b4ec  mov r8,rbx` | - | [V] |
| 0xbc8b4ef | - | ->0xEEC6DE0 | `0xbc8b4ef  call 0xEEC6DE0                                ; -> sub_eec6de0` | call sub_eec6de0 (inline string copy) | [V] |
| 0xbc8b4f4 | 1 | [r14+rbx] | `0xbc8b4f4  mov byte ptr [r14+rbx],0` | - | [V] |
| 0xbc8b4f9 | 8 | [rbp+0x628] | `0xbc8b4f9  mov rax,[rbp+0x628]` | - | [V] |
| 0xbc8b500 | - | [rsi+8] | `0xbc8b500  mov [rsi+8],rax` | - | [V] |
| 0xbc8b504 | 8 | [rsi+0x30] | `0xbc8b504  mov qword ptr [rsi+0x30],0` | - | [V] |
| 0xbc8b50c | 8 | [rbp+0xC58] | `0xbc8b50c  mov rax,[rbp+0xC58]` | - | [V] |
| 0xbc8b513 | 8 | [rax+0x58] | `0xbc8b513  mov qword ptr [rax+0x58],0` | - | [V] |
| 0xbc8b51b | 8 | [rbp+0x648] | `0xbc8b51b  mov rax,[rbp+0x648]` | - | [V] |
| 0xbc8b522 | - | - | `0xbc8b522  cmp rax,0x10` | - | [V] |
| 0xbc8b526 | - | - | `0xbc8b526  jb short 0xBC8B560                            ; -> loc_bc8b560` | branch to 0xBC8B560 | [V] |
| 0xbc8b528 | 8 | [rbp+0x630] | `0xbc8b528  mov rcx,[rbp+0x630]` | - | [V] |
| 0xbc8b52f | - | [rax+1] | `0xbc8b52f  lea rdx,[rax+1]` | - | [V] |
| 0xbc8b533 | - | - | `0xbc8b533  cmp rdx,0x1000` | - | [V] |
| 0xbc8b53a | - | - | `0xbc8b53a  jb short 0xBC8B55B                            ; -> loc_bc8b55b` | branch to 0xBC8B55B | [V] |
| 0xbc8b53c | 8 | [rcx-8] | `0xbc8b53c  mov r8,[rcx-8]` | - | [V] |
| 0xbc8b540 | - | - | `0xbc8b540  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8b544 | - | - | `0xbc8b544  sub rcx,r8` | - | [V] |
| 0xbc8b547 | - | - | `0xbc8b547  cmp rcx,0x20` | - | [V] |
| 0xbc8b54b | - | - | `0xbc8b54b  jae 0xBC8B923                                 ; -> loc_bc8b923` | branch to 0xBC8B923 | [V] |
| 0xbc8b551 | - | - | `0xbc8b551  add rax,0x28` | - | [V] |
| 0xbc8b555 | 8 | - | `0xbc8b555  mov rdx,rax` | - | [V] |
| 0xbc8b558 | 8 | - | `0xbc8b558  mov rcx,r8` | - | [V] |
| 0xbc8b55b | - | ->0xE935700 | `0xbc8b55b  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b560 | 8 | [rbp+0x640] | `0xbc8b560  mov qword ptr [rbp+0x640],0` | - | [V] |
| 0xbc8b56b | 8 | [rbp+0x648] | `0xbc8b56b  mov qword ptr [rbp+0x648],0xF` | - | [V] |
| 0xbc8b576 | 1 | [rbp+0x630] | `0xbc8b576  mov byte ptr [rbp+0x630],0` | - | [V] |
| 0xbc8b57d | - | [rbp+0x330] | `0xbc8b57d  lea rcx,[rbp+0x330]` | - | [V] |
| 0xbc8b584 | - | ->0xBC8C720 | `0xbc8b584  call 0xBC8C720                                ; -> sub_bc8c720` | call 0xBC8C720 | [V] |
| 0xbc8b589 | 8 | [rbp+0xA88] | `0xbc8b589  mov rax,[rbp+0xA88]` | - | [V] |
| 0xbc8b590 | - | - | `0xbc8b590  cmp rax,0x10` | - | [V] |
| 0xbc8b594 | - | - | `0xbc8b594  jb short 0xBC8B5CE                            ; -> loc_bc8b5ce` | branch to 0xBC8B5CE | [V] |
| 0xbc8b596 | 8 | [rbp+0xA70] | `0xbc8b596  mov rcx,[rbp+0xA70]` | - | [V] |
| 0xbc8b59d | - | [rax+1] | `0xbc8b59d  lea rdx,[rax+1]` | - | [V] |
| 0xbc8b5a1 | - | - | `0xbc8b5a1  cmp rdx,0x1000` | - | [V] |
| 0xbc8b5a8 | - | - | `0xbc8b5a8  jb short 0xBC8B5C9                            ; -> loc_bc8b5c9` | branch to 0xBC8B5C9 | [V] |
| 0xbc8b5aa | 8 | [rcx-8] | `0xbc8b5aa  mov r8,[rcx-8]` | - | [V] |
| 0xbc8b5ae | - | - | `0xbc8b5ae  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8b5b2 | - | - | `0xbc8b5b2  sub rcx,r8` | - | [V] |
| 0xbc8b5b5 | - | - | `0xbc8b5b5  cmp rcx,0x20` | - | [V] |
| 0xbc8b5b9 | - | - | `0xbc8b5b9  jae 0xBC8B923                                 ; -> loc_bc8b923` | branch to 0xBC8B923 | [V] |
| 0xbc8b5bf | - | - | `0xbc8b5bf  add rax,0x28` | - | [V] |
| 0xbc8b5c3 | 8 | - | `0xbc8b5c3  mov rdx,rax` | - | [V] |
| 0xbc8b5c6 | 8 | - | `0xbc8b5c6  mov rcx,r8` | - | [V] |
| 0xbc8b5c9 | - | ->0xE935700 | `0xbc8b5c9  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b5ce | 8 | [rbp+0xB68] | `0xbc8b5ce  mov rax,[rbp+0xB68]` | - | [V] |
| 0xbc8b5d5 | - | - | `0xbc8b5d5  cmp rax,0x10` | - | [V] |
| 0xbc8b5d9 | - | - | `0xbc8b5d9  jb short 0xBC8B613                            ; -> loc_bc8b613` | branch to 0xBC8B613 | [V] |
| 0xbc8b5db | 8 | [rbp+0xB50] | `0xbc8b5db  mov rcx,[rbp+0xB50]` | - | [V] |
| 0xbc8b5e2 | - | [rax+1] | `0xbc8b5e2  lea rdx,[rax+1]` | - | [V] |
| 0xbc8b5e6 | - | - | `0xbc8b5e6  cmp rdx,0x1000` | - | [V] |
| 0xbc8b5ed | - | - | `0xbc8b5ed  jb short 0xBC8B60E                            ; -> loc_bc8b60e` | branch to 0xBC8B60E | [V] |
| 0xbc8b5ef | 8 | [rcx-8] | `0xbc8b5ef  mov r8,[rcx-8]` | - | [V] |
| 0xbc8b5f3 | - | - | `0xbc8b5f3  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8b5f7 | - | - | `0xbc8b5f7  sub rcx,r8` | - | [V] |
| 0xbc8b5fa | - | - | `0xbc8b5fa  cmp rcx,0x20` | - | [V] |
| 0xbc8b5fe | - | - | `0xbc8b5fe  jae 0xBC8B923                                 ; -> loc_bc8b923` | branch to 0xBC8B923 | [V] |
| 0xbc8b604 | - | - | `0xbc8b604  add rax,0x28` | - | [V] |
| 0xbc8b608 | 8 | - | `0xbc8b608  mov rdx,rax` | - | [V] |
| 0xbc8b60b | 8 | - | `0xbc8b60b  mov rcx,r8` | - | [V] |
| 0xbc8b60e | - | ->0xE935700 | `0xbc8b60e  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b613 | 8 | [rbp+0xBC8] | `0xbc8b613  mov rax,[rbp+0xBC8]` | - | [V] |
| 0xbc8b61a | - | - | `0xbc8b61a  cmp rax,0x10` | - | [V] |
| 0xbc8b61e | - | - | `0xbc8b61e  jb short 0xBC8B658                            ; -> loc_bc8b658` | branch to 0xBC8B658 | [V] |
| 0xbc8b620 | 8 | [rbp+0xBB0] | `0xbc8b620  mov rcx,[rbp+0xBB0]` | - | [V] |
| 0xbc8b627 | - | [rax+1] | `0xbc8b627  lea rdx,[rax+1]` | - | [V] |
| 0xbc8b62b | - | - | `0xbc8b62b  cmp rdx,0x1000` | - | [V] |
| 0xbc8b632 | - | - | `0xbc8b632  jb short 0xBC8B653                            ; -> loc_bc8b653` | branch to 0xBC8B653 | [V] |
| 0xbc8b634 | 8 | [rcx-8] | `0xbc8b634  mov r8,[rcx-8]` | - | [V] |
| 0xbc8b638 | - | - | `0xbc8b638  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8b63c | - | - | `0xbc8b63c  sub rcx,r8` | - | [V] |
| 0xbc8b63f | - | - | `0xbc8b63f  cmp rcx,0x20` | - | [V] |
| 0xbc8b643 | - | - | `0xbc8b643  jae 0xBC8B923                                 ; -> loc_bc8b923` | branch to 0xBC8B923 | [V] |
| 0xbc8b649 | - | - | `0xbc8b649  add rax,0x28` | - | [V] |
| 0xbc8b64d | 8 | - | `0xbc8b64d  mov rdx,rax` | - | [V] |
| 0xbc8b650 | 8 | - | `0xbc8b650  mov rcx,r8` | - | [V] |
| 0xbc8b653 | - | ->0xE935700 | `0xbc8b653  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b658 | - | [rbp-0x50] | `0xbc8b658  lea rcx,[rbp-0x50]` | - | [V] |
| 0xbc8b65c | - | ->0xBC8C720 | `0xbc8b65c  call 0xBC8C720                                ; -> sub_bc8c720` | call 0xBC8C720 | [V] |
| 0xbc8b661 | 8 | [rbp+0xC10] | `0xbc8b661  mov rax,[rbp+0xC10]` | - | [V] |
| 0xbc8b668 | - | - | `0xbc8b668  cmp rax,0x10` | - | [V] |
| 0xbc8b66c | - | - | `0xbc8b66c  jb short 0xBC8B6A6                            ; -> loc_bc8b6a6` | branch to 0xBC8B6A6 | [V] |
| 0xbc8b66e | 8 | [rbp+0xBF8] | `0xbc8b66e  mov rcx,[rbp+0xBF8]` | - | [V] |
| 0xbc8b675 | - | [rax+1] | `0xbc8b675  lea rdx,[rax+1]` | - | [V] |
| 0xbc8b679 | - | - | `0xbc8b679  cmp rdx,0x1000` | - | [V] |
| 0xbc8b680 | - | - | `0xbc8b680  jb short 0xBC8B6A1                            ; -> loc_bc8b6a1` | branch to 0xBC8B6A1 | [V] |
| 0xbc8b682 | 8 | [rcx-8] | `0xbc8b682  mov r8,[rcx-8]` | - | [V] |
| 0xbc8b686 | - | - | `0xbc8b686  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8b68a | - | - | `0xbc8b68a  sub rcx,r8` | - | [V] |
| 0xbc8b68d | - | - | `0xbc8b68d  cmp rcx,0x20` | - | [V] |
| 0xbc8b691 | - | - | `0xbc8b691  jae 0xBC8B923                                 ; -> loc_bc8b923` | branch to 0xBC8B923 | [V] |
| 0xbc8b697 | - | - | `0xbc8b697  add rax,0x28` | - | [V] |
| 0xbc8b69b | 8 | - | `0xbc8b69b  mov rdx,rax` | - | [V] |
| 0xbc8b69e | 8 | - | `0xbc8b69e  mov rcx,r8` | - | [V] |
| 0xbc8b6a1 | - | ->0xE935700 | `0xbc8b6a1  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b6a6 | 8 | [rbp+0xB98] | `0xbc8b6a6  mov rax,[rbp+0xB98]` | - | [V] |
| 0xbc8b6ad | - | - | `0xbc8b6ad  cmp rax,0x10` | - | [V] |
| 0xbc8b6b1 | - | - | `0xbc8b6b1  jb short 0xBC8B6EB                            ; -> loc_bc8b6eb` | branch to 0xBC8B6EB | [V] |
| 0xbc8b6b3 | 8 | [rbp+0xB80] | `0xbc8b6b3  mov rcx,[rbp+0xB80]` | - | [V] |
| 0xbc8b6ba | - | [rax+1] | `0xbc8b6ba  lea rdx,[rax+1]` | - | [V] |
| 0xbc8b6be | - | - | `0xbc8b6be  cmp rdx,0x1000` | - | [V] |
| 0xbc8b6c5 | - | - | `0xbc8b6c5  jb short 0xBC8B6E6                            ; -> loc_bc8b6e6` | branch to 0xBC8B6E6 | [V] |
| 0xbc8b6c7 | 8 | [rcx-8] | `0xbc8b6c7  mov r8,[rcx-8]` | - | [V] |
| 0xbc8b6cb | - | - | `0xbc8b6cb  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8b6cf | - | - | `0xbc8b6cf  sub rcx,r8` | - | [V] |
| 0xbc8b6d2 | - | - | `0xbc8b6d2  cmp rcx,0x20` | - | [V] |
| 0xbc8b6d6 | - | - | `0xbc8b6d6  jae 0xBC8B923                                 ; -> loc_bc8b923` | branch to 0xBC8B923 | [V] |
| 0xbc8b6dc | - | - | `0xbc8b6dc  add rax,0x28` | - | [V] |
| 0xbc8b6e0 | 8 | - | `0xbc8b6e0  mov rdx,rax` | - | [V] |
| 0xbc8b6e3 | 8 | - | `0xbc8b6e3  mov rcx,r8` | - | [V] |
| 0xbc8b6e6 | - | ->0xE935700 | `0xbc8b6e6  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b6eb | 8 | [rbp+0xC30] | `0xbc8b6eb  mov rax,[rbp+0xC30]` | - | [V] |
| 0xbc8b6f2 | - | - | `0xbc8b6f2  cmp rax,0x10` | - | [V] |
| 0xbc8b6f6 | - | - | `0xbc8b6f6  jb short 0xBC8B730                            ; -> loc_bc8b730` | branch to 0xBC8B730 | [V] |
| 0xbc8b6f8 | 8 | [rbp+0xC18] | `0xbc8b6f8  mov rcx,[rbp+0xC18]` | - | [V] |
| 0xbc8b6ff | - | [rax+1] | `0xbc8b6ff  lea rdx,[rax+1]` | - | [V] |
| 0xbc8b703 | - | - | `0xbc8b703  cmp rdx,0x1000` | - | [V] |
| 0xbc8b70a | - | - | `0xbc8b70a  jb short 0xBC8B72B                            ; -> loc_bc8b72b` | branch to 0xBC8B72B | [V] |
| 0xbc8b70c | 8 | [rcx-8] | `0xbc8b70c  mov r8,[rcx-8]` | - | [V] |
| 0xbc8b710 | - | - | `0xbc8b710  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8b714 | - | - | `0xbc8b714  sub rcx,r8` | - | [V] |
| 0xbc8b717 | - | - | `0xbc8b717  cmp rcx,0x20` | - | [V] |
| 0xbc8b71b | - | - | `0xbc8b71b  jae 0xBC8B923                                 ; -> loc_bc8b923` | branch to 0xBC8B923 | [V] |
| 0xbc8b721 | - | - | `0xbc8b721  add rax,0x28` | - | [V] |
| 0xbc8b725 | 8 | - | `0xbc8b725  mov rdx,rax` | - | [V] |
| 0xbc8b728 | 8 | - | `0xbc8b728  mov rcx,r8` | - | [V] |
| 0xbc8b72b | - | ->0xE935700 | `0xbc8b72b  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b730 | 8 | [rbp+0x778] | `0xbc8b730  mov rcx,[rbp+0x778]` | - | [V] |
| 0xbc8b737 | - | - | `0xbc8b737  test rcx,rcx` | - | [V] |
| 0xbc8b73a | - | - | `0xbc8b73a  je short 0xBC8B746                            ; -> loc_bc8b746` | branch to 0xBC8B746 | [V] |
| 0xbc8b73c | 4 | - | `0xbc8b73c  mov edx,0x88` | - | [V] |
| 0xbc8b741 | - | ->0xE935700 | `0xbc8b741  call 0xE935700                                ; -> sub_e935700` | call sub_e935700 (small-string dtor) | [V] |
| 0xbc8b746 | 1 | [rbp+0x758] | `0xbc8b746  cmp byte ptr [rbp+0x758],3` | - | [V] |
| 0xbc8b74d | - | - | `0xbc8b74d  jne short 0xBC8B786                           ; -> loc_bc8b786` | branch to 0xBC8B786 | [V] |
| 0xbc8b74f | 8 | [rbp+0x750] | `0xbc8b74f  mov rbx,[rbp+0x750]` | - | [V] |
| 0xbc8b756 | - | - | `0xbc8b756  test rbx,rbx` | - | [V] |
| 0xbc8b759 | - | - | `0xbc8b759  je short 0xBC8B786                            ; -> loc_bc8b786` | branch to 0xBC8B786 | [V] |
| 0xbc8b75b | 4 | [rbx+8] | `0xbc8b75b  lock dec dword ptr [rbx+8]` | - | [V] |
| 0xbc8b75f | - | - | `0xbc8b75f  jne short 0xBC8B786                           ; -> loc_bc8b786` | branch to 0xBC8B786 | [V] |
| 0xbc8b761 | 8 | [rbx] | `0xbc8b761  mov rax,[rbx]` | - | [V] |
| 0xbc8b764 | 8 | [rax] | `0xbc8b764  mov rax,[rax]` | - | [V] |
| 0xbc8b767 | 8 | - | `0xbc8b767  mov rcx,rbx` | - | [V] |
| 0xbc8b76a | 8 | [0xF99FFA0] | `0xbc8b76a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b770 | 4 | [rbx+0xC] | `0xbc8b770  lock dec dword ptr [rbx+0xC]` | - | [V] |
| 0xbc8b774 | - | - | `0xbc8b774  jne short 0xBC8B786                           ; -> loc_bc8b786` | branch to 0xBC8B786 | [V] |
| 0xbc8b776 | 8 | [rbx] | `0xbc8b776  mov rax,[rbx]` | - | [V] |
| 0xbc8b779 | 8 | [rax+8] | `0xbc8b779  mov rax,[rax+8]` | - | [V] |
| 0xbc8b77d | 8 | - | `0xbc8b77d  mov rcx,rbx` | - | [V] |
| 0xbc8b780 | 8 | [0xF99FFA0] | `0xbc8b780  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b786 | 8 | [rbp+0x728] | `0xbc8b786  mov rsi,[rbp+0x728]` | - | [V] |
| 0xbc8b78d | - | - | `0xbc8b78d  test rsi,rsi` | - | [V] |
| 0xbc8b790 | - | - | `0xbc8b790  je short 0xBC8B7E5                            ; -> loc_bc8b7e5` | branch to 0xBC8B7E5 | [V] |
| 0xbc8b792 | 8 | [rbp+0x730] | `0xbc8b792  mov r14,[rbp+0x730]` | - | [V] |
| 0xbc8b799 | - | - | `0xbc8b799  jmp short 0xBC8B7A4                           ; -> loc_bc8b7a4` | branch to 0xBC8B7A4 | [V] |
| 0xbc8b79b | - | [rax+rax] | `0xbc8b79b  nop [rax+rax]` | nop padding | [V] |
| 0xbc8b7a0 | - | - | `0xbc8b7a0  add rsi,0x28` | - | [V] |
| 0xbc8b7a4 | - | - | `0xbc8b7a4  cmp rsi,r14` | - | [V] |
| 0xbc8b7a7 | - | - | `0xbc8b7a7  je short 0xBC8B7E5                            ; -> loc_bc8b7e5` | branch to 0xBC8B7E5 | [V] |
| 0xbc8b7a9 | 1 | [rsi+0x18] | `0xbc8b7a9  cmp byte ptr [rsi+0x18],2` | - | [V] |
| 0xbc8b7ad | - | - | `0xbc8b7ad  jne short 0xBC8B7A0                           ; -> loc_bc8b7a0` | branch to 0xBC8B7A0 | [V] |
| 0xbc8b7af | 8 | [rsi+8] | `0xbc8b7af  mov rbx,[rsi+8]` | - | [V] |
| 0xbc8b7b3 | - | - | `0xbc8b7b3  test rbx,rbx` | - | [V] |
| 0xbc8b7b6 | - | - | `0xbc8b7b6  je short 0xBC8B7A0                            ; -> loc_bc8b7a0` | branch to 0xBC8B7A0 | [V] |
| 0xbc8b7b8 | 4 | [rbx+8] | `0xbc8b7b8  lock dec dword ptr [rbx+8]` | - | [V] |
| 0xbc8b7bc | - | - | `0xbc8b7bc  jne short 0xBC8B7A0                           ; -> loc_bc8b7a0` | branch to 0xBC8B7A0 | [V] |
| 0xbc8b7be | 8 | [rbx] | `0xbc8b7be  mov rax,[rbx]` | - | [V] |
| 0xbc8b7c1 | 8 | [rax] | `0xbc8b7c1  mov rax,[rax]` | - | [V] |
| 0xbc8b7c4 | 8 | - | `0xbc8b7c4  mov rcx,rbx` | - | [V] |
| 0xbc8b7c7 | 8 | [0xF99FFA0] | `0xbc8b7c7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b7cd | 4 | [rbx+0xC] | `0xbc8b7cd  lock dec dword ptr [rbx+0xC]` | - | [V] |
| 0xbc8b7d1 | - | - | `0xbc8b7d1  jne short 0xBC8B7A0                           ; -> loc_bc8b7a0` | branch to 0xBC8B7A0 | [V] |
| 0xbc8b7d3 | 8 | [rbx] | `0xbc8b7d3  mov rax,[rbx]` | - | [V] |
| 0xbc8b7d6 | 8 | [rax+8] | `0xbc8b7d6  mov rax,[rax+8]` | - | [V] |
| 0xbc8b7da | 8 | - | `0xbc8b7da  mov rcx,rbx` | - | [V] |
| 0xbc8b7dd | 8 | [0xF99FFA0] | `0xbc8b7dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b7e3 | - | - | `0xbc8b7e3  jmp short 0xBC8B7A0                           ; -> loc_bc8b7a0` | branch to 0xBC8B7A0 | [V] |
| 0xbc8b7e5 | 8 | [rbp+0xBE0] | `0xbc8b7e5  mov rbx,[rbp+0xBE0]` | - | [V] |
| 0xbc8b7ec | - | - | `0xbc8b7ec  test rbx,rbx` | - | [V] |
| 0xbc8b7ef | - | - | `0xbc8b7ef  je short 0xBC8B81D                            ; -> loc_bc8b81d` | branch to 0xBC8B81D | [V] |
| 0xbc8b7f1 | 4 | [rbx+8] | `0xbc8b7f1  lock dec dword ptr [rbx+8]` | - | [V] |
| 0xbc8b7f5 | - | - | `0xbc8b7f5  jne short 0xBC8B81D                           ; -> loc_bc8b81d` | branch to 0xBC8B81D | [V] |
| 0xbc8b7f7 | 8 | [rbx] | `0xbc8b7f7  mov rax,[rbx]` | - | [V] |
| 0xbc8b7fa | 8 | [rax] | `0xbc8b7fa  mov rax,[rax]` | - | [V] |
| 0xbc8b7fd | 8 | - | `0xbc8b7fd  mov rcx,rbx` | - | [V] |
| 0xbc8b800 | 8 | [0xF99FFA0] | `0xbc8b800  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b806 | 4 | [rbx+0xC] | `0xbc8b806  lock dec dword ptr [rbx+0xC]` | - | [V] |
| 0xbc8b80a | - | - | `0xbc8b80a  jne short 0xBC8B81D                           ; -> loc_bc8b81d` | branch to 0xBC8B81D | [V] |
| 0xbc8b80c | 8 | [rbx] | `0xbc8b80c  mov rax,[rbx]` | - | [V] |
| 0xbc8b80f | 8 | [rax+8] | `0xbc8b80f  mov rax,[rax+8]` | - | [V] |
| 0xbc8b813 | 8 | - | `0xbc8b813  mov rcx,rbx` | - | [V] |
| 0xbc8b816 | 8 | [0xF99FFA0] | `0xbc8b816  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b81c | - | - | `0xbc8b81c  nop` | nop padding | [V] |
| 0xbc8b81d | - | [rbp+0x9C0] | `0xbc8b81d  lea rsi,[rbp+0x9C0]` | - | [V] |
| 0xbc8b824 | 8 | - | `0xbc8b824  mov rcx,rsi` | - | [V] |
| 0xbc8b827 | - | ->0x56D5810 | `0xbc8b827  call 0x56D5810                                ; -> sub_56d5810` | call sub_56d5810 | [V] |
| 0xbc8b82c | - | - | `0xbc8b82c  nop` | nop padding | [V] |
| 0xbc8b82d | - | [rbp+0xA60] | `0xbc8b82d  lea rcx,[rbp+0xA60]` | - | [V] |
| 0xbc8b834 | - | ->0x9BD3C0 | `0xbc8b834  call 0x9BD3C0                                 ; -> sub_9bd3c0` | call sub_9bd3c0 | [V] |
| 0xbc8b839 | - | [rax] | `0xbc8b839  nop [rax]                                     ; R ret@9bd3c0+0x0` | nop padding | [V] |
| 0xbc8b840 | 8 | [rbp+0xA00] | `0xbc8b840  mov rax,[rbp+0xA00]` | - | [V] |
| 0xbc8b847 | - | - | `0xbc8b847  cmp rax,rdi` | - | [V] |
| 0xbc8b84a | - | - | `0xbc8b84a  je short 0xBC8B863                            ; -> loc_bc8b863` | branch to 0xBC8B863 | [V] |
| 0xbc8b84c | 8 | [rax] | `0xbc8b84c  mov rcx,[rax]` | - | [V] |
| 0xbc8b84f | 8 | [rax+8] | `0xbc8b84f  mov rdx,[rax+8]` | - | [V] |
| 0xbc8b853 | - | [rdx] | `0xbc8b853  mov [rdx],rcx` | - | [V] |
| 0xbc8b856 | - | [rcx+8] | `0xbc8b856  mov [rcx+8],rdx` | - | [V] |
| 0xbc8b85a | - | [rax] | `0xbc8b85a  mov [rax],rax` | - | [V] |
| 0xbc8b85d | - | [rax+8] | `0xbc8b85d  mov [rax+8],rax` | - | [V] |
| 0xbc8b861 | - | - | `0xbc8b861  jmp short 0xBC8B840                           ; -> loc_bc8b840` | branch to 0xBC8B840 | [V] |
| 0xbc8b863 | - | - | `0xbc8b863  cmp rax,rdi` | - | [V] |
| 0xbc8b866 | - | - | `0xbc8b866  je short 0xBC8B884                            ; -> loc_bc8b884` | branch to 0xBC8B884 | [V] |
| 0xbc8b868 | 8 | [rbp+0xA08] | `0xbc8b868  mov rcx,[rbp+0xA08]` | - | [V] |
| 0xbc8b86f | - | [rcx] | `0xbc8b86f  mov [rcx],rax` | - | [V] |
| 0xbc8b872 | - | [rax+8] | `0xbc8b872  mov [rax+8],rcx` | - | [V] |
| 0xbc8b876 | - | [rbp+0xA00] | `0xbc8b876  mov [rbp+0xA00],rdi` | - | [V] |
| 0xbc8b87d | - | [rbp+0xA08] | `0xbc8b87d  mov [rbp+0xA08],rdi` | - | [V] |
| 0xbc8b884 | 8 | [rbp+0x9F8] | `0xbc8b884  mov rcx,[rbp+0x9F8]` | - | [V] |
| 0xbc8b88b | - | - | `0xbc8b88b  test rcx,rcx` | - | [V] |
| 0xbc8b88e | - | - | `0xbc8b88e  je short 0xBC8B8A3                            ; -> loc_bc8b8a3` | branch to 0xBC8B8A3 | [V] |
| 0xbc8b890 | - | - | `0xbc8b890  cmp rcx,rsi` | - | [V] |
| 0xbc8b893 | - | - | `0xbc8b893  setne dl` | - | [V] |
| 0xbc8b896 | 8 | [rcx] | `0xbc8b896  mov rax,[rcx]` | - | [V] |
| 0xbc8b899 | 8 | [rax+0x20] | `0xbc8b899  mov rax,[rax+0x20]` | - | [V] |
| 0xbc8b89d | 8 | [0xF99FFA0] | `0xbc8b89d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | call via [0xF99FFA0] (sub_eea6040 allocator/release) | [V] |
| 0xbc8b8a3 | 16 | [rbp+0xC70] | `0xbc8b8a3  movaps xmm6,[rbp+0xC70]` | - | [V] |
| 0xbc8b8aa | - | - | `0xbc8b8aa  add rsp,0xD08` | - | [V] |
| 0xbc8b8b1 | 8 | - | `0xbc8b8b1  pop rbx` | - | [V] |
| 0xbc8b8b2 | 8 | - | `0xbc8b8b2  pop rdi` | - | [V] |
| 0xbc8b8b3 | 8 | - | `0xbc8b8b3  pop rsi` | - | [V] |
| 0xbc8b8b4 | 8 | - | `0xbc8b8b4  pop r12` | - | [V] |
| 0xbc8b8b6 | 8 | - | `0xbc8b8b6  pop r13` | - | [V] |
| 0xbc8b8b8 | 8 | - | `0xbc8b8b8  pop r14` | - | [V] |
| 0xbc8b8ba | 8 | - | `0xbc8b8ba  pop r15` | - | [V] |
| 0xbc8b8bc | 8 | - | `0xbc8b8bc  pop rbp` | - | [V] |
| 0xbc8b8bd | - | - | `0xbc8b8bd  ret` | function return (epilogue at 0xbc8b8bd) | [V] |
| 0xbc8b8be | - | ->0x78ED0 | `0xbc8b8be  call 0x78ED0                                  ; -> sub_78ed0` | call sub_78ed0 | [V] |
| 0xbc8b8c3 | - | - | `0xbc8b8c3  nop` | nop padding | [V] |
| 0xbc8b8c4 | 4 | - | `0xbc8b8c4  mov ecx,0x88` | - | [V] |
| 0xbc8b8c9 | - | ->0x9BC830 | `0xbc8b8c9  call 0x9BC830                                 ; -> sub_9bc830` | call sub_9bc830 (alloc-fail/raise) | [V] |
| 0xbc8b8ce | - | - | `0xbc8b8ce  nop` | nop padding | [V] |
| 0xbc8b8cf | - | - | `0xbc8b8cf  jmp 0xBC8A7DD                                 ; -> sub_bc8a7dd` | branch to 0xBC8A7DD | [V] |
| 0xbc8b8d4 | 4 | - | `0xbc8b8d4  mov ecx,0x130` | - | [V] |
| 0xbc8b8d9 | - | ->0x9BC830 | `0xbc8b8d9  call 0x9BC830                                 ; -> sub_9bc830` | call sub_9bc830 (alloc-fail/raise) | [V] |
| 0xbc8b8de | - | - | `0xbc8b8de  nop` | nop padding | [V] |
| 0xbc8b8df | - | - | `0xbc8b8df  jmp 0xBC8ABC8                                 ; -> loc_bc8abc8` | branch to 0xBC8ABC8 | [V] |
| 0xbc8b8e4 | 4 | - | `0xbc8b8e4  mov ecx,0x340` | - | [V] |
| 0xbc8b8e9 | - | ->0x9BC830 | `0xbc8b8e9  call 0x9BC830                                 ; -> sub_9bc830` | call sub_9bc830 (alloc-fail/raise) | [V] |
| 0xbc8b8ee | - | - | `0xbc8b8ee  nop` | nop padding | [V] |
| 0xbc8b8ef | - | - | `0xbc8b8ef  jmp 0xBC8AFF7                                 ; -> loc_bc8aff7` | branch to 0xBC8AFF7 | [V] |
| 0xbc8b8f4 | - | [r13+0x28] | `0xbc8b8f4  lea rcx,[r13+0x28]` | - | [V] |
| 0xbc8b8f8 | - | ->0x9BC830 | `0xbc8b8f8  call 0x9BC830                                 ; -> sub_9bc830` | call sub_9bc830 (alloc-fail/raise) | [V] |
| 0xbc8b8fd | - | - | `0xbc8b8fd  nop` | nop padding | [V] |
| 0xbc8b8fe | - | - | `0xbc8b8fe  jmp 0xBC8B17F                                 ; -> loc_bc8b17f` | branch to 0xBC8B17F | [V] |
| 0xbc8b903 | - | [r13+1] | `0xbc8b903  lea rcx,[r13+1]` | - | [V] |
| 0xbc8b907 | - | ->0x9BC830 | `0xbc8b907  call 0x9BC830                                 ; -> sub_9bc830` | call sub_9bc830 (alloc-fail/raise) | [V] |
| 0xbc8b90c | - | - | `0xbc8b90c  nop` | nop padding | [V] |
| 0xbc8b90d | - | - | `0xbc8b90d  xor r12d,r12d` | - | [V] |
| 0xbc8b910 | - | - | `0xbc8b910  jmp 0xBC8B1A8                                 ; -> loc_bc8b1a8` | branch to 0xBC8B1A8 | [V] |
| 0xbc8b915 | 8 | - | `0xbc8b915  mov rcx,r13` | - | [V] |
| 0xbc8b918 | - | ->0x9BC830 | `0xbc8b918  call 0x9BC830                                 ; -> sub_9bc830` | call sub_9bc830 (alloc-fail/raise) | [V] |
| 0xbc8b91d | - | - | `0xbc8b91d  nop` | nop padding | [V] |
| 0xbc8b91e | - | - | `0xbc8b91e  jmp 0xBC8B2D2                                 ; -> loc_bc8b2d2` | branch to 0xBC8B2D2 | [V] |
| 0xbc8b923 | 8 | [rsp+0x20] | `0xbc8b923  mov qword ptr [rsp+0x20],0` | - | [V] |
| 0xbc8b92c | - | - | `0xbc8b92c  xor ecx,ecx` | - | [V] |
| 0xbc8b92e | - | - | `0xbc8b92e  xor edx,edx` | - | [V] |
| 0xbc8b930 | - | - | `0xbc8b930  xor r8d,r8d` | - | [V] |
| 0xbc8b933 | - | - | `0xbc8b933  xor r9d,r9d` | - | [V] |
| 0xbc8b936 | 8 | [0xF9A8C78] | `0xbc8b936  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | call via [0xF9A8C78] (registration callback) | [V] |
| 0xbc8b93c | - | [0x12AE1B60] | `0xbc8b93c  lea rcx,[0x12AE1B60]                          ; [data_12ae1b60]` | lea rodata 0x12AE1B60 | [V] |
| 0xbc8b943 | - | ->0xE938CB0 | `0xbc8b943  call 0xE938CB0                                ; -> sub_e938cb0` | call sub_e938cb0 (input slot lookup) | [V] |
| 0xbc8b948 | 4 | [0x12AE1B60] | `0xbc8b948  cmp dword ptr [0x12AE1B60],0xFFFFFFFF         ; [data_12ae1b60]` | - | [V] |
| 0xbc8b94f | - | - | `0xbc8b94f  jne 0xBC8A3E2                                 ; -> sub_bc8a3e2` | branch to 0xBC8A3E2 | [V] |
| 0xbc8b955 | - | [0xF563B27] | `0xbc8b955  lea rdx,[0xF563B27]                           ; [data_f563b27] "InputFinalColor"` | lea rodata 0xF563B27 | [V] |
| 0xbc8b95c | - | [rbp+0x330] | `0xbc8b95c  lea rsi,[rbp+0x330]` | - | [V] |
| 0xbc8b963 | 8 | - | `0xbc8b963  mov rcx,rsi` | - | [V] |
| 0xbc8b966 | - | ->0x79580 | `0xbc8b966  call 0x79580                                  ; -> sub_79580` | call sub_79580 (FNV-1a 64 hash) | [V] |
| 0xbc8b96b | - | - | `0xbc8b96b  nop` | nop padding | [V] |
| 0xbc8b96c | 8 | [rbp+0x340] | `0xbc8b96c  mov rdx,[rbp+0x340]` | - | [V] |
| 0xbc8b973 | 8 | [rbp+0x348] | `0xbc8b973  cmp qword ptr [rbp+0x348],0x10` | - | [V] |
| 0xbc8b97b | - | - | `0xbc8b97b  jb short 0xBC8B984                            ; -> loc_bc8b984` | branch to 0xBC8B984 | [V] |
| 0xbc8b97d | 8 | [rbp+0x330] | `0xbc8b97d  mov rsi,[rbp+0x330]` | - | [V] |
| 0xbc8b984 | - | - | `0xbc8b984  test rdx,rdx` | - | [V] |
| 0xbc8b987 | - | - | `0xbc8b987  je 0xBC8BB8A                                  ; -> loc_bc8bb8a` | branch to 0xBC8BB8A | [V] |
| 0xbc8b98d | 4 | - | `0xbc8b98d  mov eax,edx` | - | [V] |
| 0xbc8b98f | - | - | `0xbc8b98f  and eax,3` | - | [V] |
| 0xbc8b992 | - | - | `0xbc8b992  cmp rdx,4` | - | [V] |
| 0xbc8b996 | - | - | `0xbc8b996  jae 0xBC8BBC6                                 ; -> loc_bc8bbc6` | branch to 0xBC8BBC6 | [V] |
| 0xbc8b99c | 8 | - | `0xbc8b99c  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8b9a6 | - | - | `0xbc8b9a6  xor r8d,r8d` | - | [V] |
| 0xbc8b9a9 | - | - | `0xbc8b9a9  jmp 0xBC8BC22                                 ; -> loc_bc8bc22` | branch to 0xBC8BC22 | [V] |
| 0xbc8b9ae | - | [0x12AE1B70] | `0xbc8b9ae  lea rcx,[0x12AE1B70]                          ; [data_12ae1b70]` | lea rodata 0x12AE1B70 | [V] |
| 0xbc8b9b5 | - | ->0xE938CB0 | `0xbc8b9b5  call 0xE938CB0                                ; -> sub_e938cb0` | call sub_e938cb0 (input slot lookup) | [V] |
| 0xbc8b9ba | 4 | [0x12AE1B70] | `0xbc8b9ba  cmp dword ptr [0x12AE1B70],0xFFFFFFFF         ; [data_12ae1b70]` | - | [V] |
| 0xbc8b9c1 | - | - | `0xbc8b9c1  jne 0xBC8A407                                 ; -> sub_bc8a407` | branch to 0xBC8A407 | [V] |
| 0xbc8b9c7 | - | [0xF549A53] | `0xbc8b9c7  lea rdx,[0xF549A53]                           ; [data_f549a53] "InputBufferMotionVectors"` | lea rodata 0xF549A53 | [V] |
| 0xbc8b9ce | - | [rbp+0x330] | `0xbc8b9ce  lea rsi,[rbp+0x330]` | - | [V] |
| 0xbc8b9d5 | 8 | - | `0xbc8b9d5  mov rcx,rsi` | - | [V] |
| 0xbc8b9d8 | - | ->0x79580 | `0xbc8b9d8  call 0x79580                                  ; -> sub_79580` | call sub_79580 (FNV-1a 64 hash) | [V] |
| 0xbc8b9dd | - | - | `0xbc8b9dd  nop` | nop padding | [V] |
| 0xbc8b9de | 8 | [rbp+0x340] | `0xbc8b9de  mov rdx,[rbp+0x340]` | - | [V] |
| 0xbc8b9e5 | 8 | [rbp+0x348] | `0xbc8b9e5  cmp qword ptr [rbp+0x348],0x10` | - | [V] |
| 0xbc8b9ed | - | - | `0xbc8b9ed  jb short 0xBC8B9F6                            ; -> loc_bc8b9f6` | branch to 0xBC8B9F6 | [V] |
| 0xbc8b9ef | 8 | [rbp+0x330] | `0xbc8b9ef  mov rsi,[rbp+0x330]` | - | [V] |
| 0xbc8b9f6 | - | - | `0xbc8b9f6  test rdx,rdx` | - | [V] |
| 0xbc8b9f9 | - | - | `0xbc8b9f9  je 0xBC8BB99                                  ; -> loc_bc8bb99` | branch to 0xBC8BB99 | [V] |
| 0xbc8b9ff | 4 | - | `0xbc8b9ff  mov eax,edx` | - | [V] |
| 0xbc8ba01 | - | - | `0xbc8ba01  and eax,3` | - | [V] |
| 0xbc8ba04 | - | - | `0xbc8ba04  cmp rdx,4` | - | [V] |
| 0xbc8ba08 | - | - | `0xbc8ba08  jae 0xBC8BC6E                                 ; -> loc_bc8bc6e` | branch to 0xBC8BC6E | [V] |
| 0xbc8ba0e | 8 | - | `0xbc8ba0e  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8ba18 | - | - | `0xbc8ba18  xor r8d,r8d` | - | [V] |
| 0xbc8ba1b | - | - | `0xbc8ba1b  jmp 0xBC8BCCA                                 ; -> loc_bc8bcca` | branch to 0xBC8BCCA | [V] |
| 0xbc8ba20 | - | [0x12AE1B80] | `0xbc8ba20  lea rcx,[0x12AE1B80]                          ; [data_12ae1b80]` | lea rodata 0x12AE1B80 | [V] |
| 0xbc8ba27 | - | ->0xE938CB0 | `0xbc8ba27  call 0xE938CB0                                ; -> sub_e938cb0` | call sub_e938cb0 (input slot lookup) | [V] |
| 0xbc8ba2c | 4 | [0x12AE1B80] | `0xbc8ba2c  cmp dword ptr [0x12AE1B80],0xFFFFFFFF         ; [data_12ae1b80]` | - | [V] |
| 0xbc8ba33 | - | - | `0xbc8ba33  jne 0xBC8A42C                                 ; -> sub_bc8a42c` | branch to 0xBC8A42C | [V] |
| 0xbc8ba39 | - | [0xF5182C0] | `0xbc8ba39  lea rdx,[0xF5182C0]                           ; [data_f5182c0] "InputTAAHistory"` | lea rodata 0xF5182C0 | [V] |
| 0xbc8ba40 | - | [rbp+0x330] | `0xbc8ba40  lea rsi,[rbp+0x330]` | - | [V] |

## (6) Proof rows — window 2: 0xbc8ba47..0xbc8be7b (source: docs/progress/_taa_p2.txt; thunks at 0xbc8be80..0xbc8c56f are separate functions outside rdis's bound for sub_bc8a380 and are not part of this body)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc8ba47 | 8 | - | `0xbc8ba47  mov rcx,rsi` | - | [V] |
| 0xbc8ba4a | - | ->0x79580 | `0xbc8ba4a  call 0x79580                                  ; -> sub_79580` | call sub_79580 (FNV-1a 64 hash) | [V] |
| 0xbc8ba4f | - | - | `0xbc8ba4f  nop` | nop padding | [V] |
| 0xbc8ba50 | 8 | [rbp+0x340] | `0xbc8ba50  mov rdx,[rbp+0x340]` | - | [V] |
| 0xbc8ba57 | 8 | [rbp+0x348] | `0xbc8ba57  cmp qword ptr [rbp+0x348],0x10` | - | [V] |
| 0xbc8ba5f | - | - | `0xbc8ba5f  jb short 0xBC8BA68                            ; -> loc_bc8ba68` | branch to 0xBC8BA68 | [V] |
| 0xbc8ba61 | 8 | [rbp+0x330] | `0xbc8ba61  mov rsi,[rbp+0x330]` | - | [V] |
| 0xbc8ba68 | - | - | `0xbc8ba68  test rdx,rdx` | - | [V] |
| 0xbc8ba6b | - | - | `0xbc8ba6b  je 0xBC8BBA8                                  ; -> loc_bc8bba8` | branch to 0xBC8BBA8 | [V] |
| 0xbc8ba71 | 4 | - | `0xbc8ba71  mov eax,edx` | - | [V] |
| 0xbc8ba73 | - | - | `0xbc8ba73  and eax,3` | - | [V] |
| 0xbc8ba76 | - | - | `0xbc8ba76  cmp rdx,4` | - | [V] |
| 0xbc8ba7a | - | - | `0xbc8ba7a  jae 0xBC8BD16                                 ; -> loc_bc8bd16` | branch to 0xBC8BD16 | [V] |
| 0xbc8ba80 | 8 | - | `0xbc8ba80  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8ba8a | - | - | `0xbc8ba8a  xor r8d,r8d` | - | [V] |
| 0xbc8ba8d | - | - | `0xbc8ba8d  jmp 0xBC8BD72                                 ; -> loc_bc8bd72` | branch to 0xBC8BD72 | [V] |
| 0xbc8ba92 | - | [0x12AE1B98] | `0xbc8ba92  lea rcx,[0x12AE1B98]                          ; [data_12ae1b98]` | lea rodata 0x12AE1B98 | [V] |
| 0xbc8ba99 | - | ->0xE938CB0 | `0xbc8ba99  call 0xE938CB0                                ; -> sub_e938cb0` | call sub_e938cb0 (input slot lookup) | [V] |
| 0xbc8ba9e | 4 | [0x12AE1B98] | `0xbc8ba9e  cmp dword ptr [0x12AE1B98],0xFFFFFFFF         ; [data_12ae1b98]` | - | [V] |
| 0xbc8baa5 | - | - | `0xbc8baa5  jne 0xBC8A4E4                                 ; -> sub_bc8a4e4` | branch to 0xBC8A4E4 | [V] |
| 0xbc8baab | - | - | `0xbc8baab  xorps xmm0,xmm0` | - | [V] |
| 0xbc8baae | 16 | [rbp+0x6F0] | `0xbc8baae  movaps [rbp+0x6F0],xmm0` | - | [V] |
| 0xbc8bab5 | - | [0xF5B67DB] | `0xbc8bab5  lea rax,[0xF5B67DB]                           ; [data_f5b67db] "Upscaling"` | lea rodata 0xF5B67DB | [V] |
| 0xbc8babc | - | [rbp+0xB38] | `0xbc8babc  mov [rbp+0xB38],rax` | - | [V] |
| 0xbc8bac3 | 8 | [rbp+0xB40] | `0xbc8bac3  mov qword ptr [rbp+0xB40],9` | - | [V] |
| 0xbc8bace | - | [0x12AE1B88] | `0xbc8bace  lea rcx,[0x12AE1B88]                          ; [data_12ae1b88]` | lea rodata 0x12AE1B88 | [V] |
| 0xbc8bad5 | - | [rbp+0xB38] | `0xbc8bad5  lea rdx,[rbp+0xB38]` | - | [V] |
| 0xbc8badc | - | [rbp+0x6F0] | `0xbc8badc  lea r8,[rbp+0x6F0]` | - | [V] |
| 0xbc8bae3 | - | ->0x5668AC0 | `0xbc8bae3  call 0x5668AC0                                ; -> sub_5668ac0` | call sub_5668ac0 (register "Upscaling" pass name) | [V] |
| 0xbc8bae8 | - | - | `0xbc8bae8  nop` | nop padding | [V] |
| 0xbc8bae9 | - | [0x12AE1B98] | `0xbc8bae9  lea rcx,[0x12AE1B98]                          ; [data_12ae1b98]` | lea rodata 0x12AE1B98 | [V] |
| 0xbc8baf0 | - | ->0xE938D70 | `0xbc8baf0  call 0xE938D70                                ; -> sub_e938d70` | call sub_e938d70 (input slot register) | [V] |
| 0xbc8baf5 | - | - | `0xbc8baf5  jmp 0xBC8A4E4                                 ; -> sub_bc8a4e4` | branch to 0xBC8A4E4 | [V] |
| 0xbc8bafa | - | [0x12AE1BA8] | `0xbc8bafa  lea rcx,[0x12AE1BA8]                          ; [data_12ae1ba8]` | lea rodata 0x12AE1BA8 | [V] |
| 0xbc8bb01 | - | ->0xE938CB0 | `0xbc8bb01  call 0xE938CB0                                ; -> sub_e938cb0` | call sub_e938cb0 (input slot lookup) | [V] |
| 0xbc8bb06 | 4 | [0x12AE1BA8] | `0xbc8bb06  cmp dword ptr [0x12AE1BA8],0xFFFFFFFF         ; [data_12ae1ba8]` | - | [V] |
| 0xbc8bb0d | - | - | `0xbc8bb0d  jne 0xBC8A644                                 ; -> sub_bc8a644` | branch to 0xBC8A644 | [V] |
| 0xbc8bb13 | - | [0xF7E41CA] | `0xbc8bb13  lea rdx,[0xF7E41CA]                           ; [data_f7e41ca] "Color0"` | lea rodata 0xF7E41CA | [V] |
| 0xbc8bb1a | - | [rbp+0x330] | `0xbc8bb1a  lea r15,[rbp+0x330]` | - | [V] |
| 0xbc8bb21 | 8 | - | `0xbc8bb21  mov rcx,r15` | - | [V] |
| 0xbc8bb24 | - | ->0x79580 | `0xbc8bb24  call 0x79580                                  ; -> sub_79580` | call sub_79580 (FNV-1a 64 hash) | [V] |
| 0xbc8bb29 | - | - | `0xbc8bb29  nop` | nop padding | [V] |
| 0xbc8bb2a | 8 | [rbp+0x340] | `0xbc8bb2a  mov r8,[rbp+0x340]` | - | [V] |
| 0xbc8bb31 | 8 | [rbp+0x348] | `0xbc8bb31  cmp qword ptr [rbp+0x348],0x10` | - | [V] |
| 0xbc8bb39 | - | - | `0xbc8bb39  jb short 0xBC8BB42                            ; -> loc_bc8bb42` | branch to 0xBC8BB42 | [V] |
| 0xbc8bb3b | 8 | [rbp+0x330] | `0xbc8bb3b  mov r15,[rbp+0x330]` | - | [V] |
| 0xbc8bb42 | - | - | `0xbc8bb42  test r8,r8` | - | [V] |
| 0xbc8bb45 | - | - | `0xbc8bb45  je short 0xBC8BBB7                            ; -> loc_bc8bbb7` | branch to 0xBC8BBB7 | [V] |
| 0xbc8bb47 | 4 | - | `0xbc8bb47  mov eax,r8d` | - | [V] |
| 0xbc8bb4a | - | - | `0xbc8bb4a  and eax,7` | - | [V] |
| 0xbc8bb4d | 8 | - | `0xbc8bb4d  mov rcx,0x100000001B3` | - | [V] |
| 0xbc8bb57 | - | - | `0xbc8bb57  cmp r8,8` | - | [V] |
| 0xbc8bb5b | - | - | `0xbc8bb5b  jae 0xBC8BDBE                                 ; -> loc_bc8bdbe` | branch to 0xBC8BDBE | [V] |
| 0xbc8bb61 | 8 | - | `0xbc8bb61  mov rdx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bb6b | - | - | `0xbc8bb6b  jmp 0xBC8BE3A                                 ; -> loc_bc8be3a` | branch to 0xBC8BE3A | [V] |
| 0xbc8bb70 | - | ->0x75720 | `0xbc8bb70  call 0x75720                                  ; -> sub_75720` | call 0x75720 | [V] |
| 0xbc8bb75 | - | - | `0xbc8bb75  nop` | nop padding | [V] |
| 0xbc8bb76 | - | [rbp+0xC50] | `0xbc8bb76  mov [rbp+0xC50],rcx` | - | [V] |
| 0xbc8bb7d | - | [rbp+0xC38] | `0xbc8bb7d  mov [rbp+0xC38],r9` | - | [V] |
| 0xbc8bb84 | - | ->0x75740 | `0xbc8bb84  call 0x75740                                  ; -> sub_75740` | call 0x75740 (trailing unreached) | [V] |
| 0xbc8bb89 | - | - | `0xbc8bb89  nop` | nop padding | [V] |
| 0xbc8bb8a | 8 | - | `0xbc8bb8a  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bb94 | - | - | `0xbc8bb94  jmp 0xBC8BC4A                                 ; -> loc_bc8bc4a` | branch to 0xBC8BC4A | [V] |
| 0xbc8bb99 | 8 | - | `0xbc8bb99  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bba3 | - | - | `0xbc8bba3  jmp 0xBC8BCF2                                 ; -> loc_bc8bcf2` | branch to 0xBC8BCF2 | [V] |
| 0xbc8bba8 | 8 | - | `0xbc8bba8  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bbb2 | - | - | `0xbc8bbb2  jmp 0xBC8BD9A                                 ; -> loc_bc8bd9a` | branch to 0xBC8BD9A | [V] |
| 0xbc8bbb7 | 8 | - | `0xbc8bbb7  mov rdx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bbc1 | - | - | `0xbc8bbc1  jmp 0xBC8BE51                                 ; -> loc_bc8be51` | branch to 0xBC8BE51 | [V] |
| 0xbc8bbc6 | - | - | `0xbc8bbc6  and rdx,0xFFFFFFFFFFFFFFFC` | - | [V] |
| 0xbc8bbca | 8 | - | `0xbc8bbca  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bbd4 | - | - | `0xbc8bbd4  xor r8d,r8d` | - | [V] |
| 0xbc8bbd7 | 8 | - | `0xbc8bbd7  mov r9,0x100000001B3` | - | [V] |
| 0xbc8bbe1 | 1 | [rsi+r8] | `0xbc8bbe1  movzx r10d,byte ptr [rsi+r8]` | - | [V] |
| 0xbc8bbe6 | - | - | `0xbc8bbe6  xor r10,rcx` | - | [V] |
| 0xbc8bbe9 | - | - | `0xbc8bbe9  imul r10,r9` | - | [V] |
| 0xbc8bbed | 1 | [rsi+r8+1] | `0xbc8bbed  movzx ecx,byte ptr [rsi+r8+1]` | - | [V] |
| 0xbc8bbf3 | - | - | `0xbc8bbf3  xor rcx,r10` | - | [V] |
| 0xbc8bbf6 | - | - | `0xbc8bbf6  imul rcx,r9` | - | [V] |
| 0xbc8bbfa | 1 | [rsi+r8+2] | `0xbc8bbfa  movzx r10d,byte ptr [rsi+r8+2]` | - | [V] |
| 0xbc8bc00 | - | - | `0xbc8bc00  xor r10,rcx` | - | [V] |
| 0xbc8bc03 | - | - | `0xbc8bc03  imul r10,r9` | - | [V] |
| 0xbc8bc07 | 1 | [rsi+r8+3] | `0xbc8bc07  movzx ecx,byte ptr [rsi+r8+3]` | - | [V] |
| 0xbc8bc0d | - | - | `0xbc8bc0d  xor rcx,r10` | - | [V] |
| 0xbc8bc10 | - | - | `0xbc8bc10  imul rcx,r9` | - | [V] |
| 0xbc8bc14 | - | - | `0xbc8bc14  add r8,4` | - | [V] |
| 0xbc8bc18 | - | - | `0xbc8bc18  cmp rdx,r8` | - | [V] |
| 0xbc8bc1b | - | - | `0xbc8bc1b  jne short 0xBC8BBE1                           ; -> loc_bc8bbe1` | branch to 0xBC8BBE1 | [V] |
| 0xbc8bc1d | - | - | `0xbc8bc1d  test rax,rax` | - | [V] |
| 0xbc8bc20 | - | - | `0xbc8bc20  je short 0xBC8BC4A                            ; -> loc_bc8bc4a` | branch to 0xBC8BC4A | [V] |
| 0xbc8bc22 | - | - | `0xbc8bc22  add rsi,r8` | - | [V] |
| 0xbc8bc25 | - | - | `0xbc8bc25  xor edx,edx` | - | [V] |
| 0xbc8bc27 | 8 | - | `0xbc8bc27  mov r8,0x100000001B3` | - | [V] |
| 0xbc8bc31 | 8 | - | `0xbc8bc31  mov r9,rcx` | - | [V] |
| 0xbc8bc34 | 1 | [rsi+rdx] | `0xbc8bc34  movzx ecx,byte ptr [rsi+rdx]` | - | [V] |
| 0xbc8bc38 | - | - | `0xbc8bc38  xor rcx,r9` | - | [V] |
| 0xbc8bc3b | - | - | `0xbc8bc3b  imul rcx,r8` | - | [V] |
| 0xbc8bc3f | - | - | `0xbc8bc3f  inc rdx` | - | [V] |
| 0xbc8bc42 | 8 | - | `0xbc8bc42  mov r9,rcx` | - | [V] |
| 0xbc8bc45 | - | - | `0xbc8bc45  cmp rax,rdx` | - | [V] |
| 0xbc8bc48 | - | - | `0xbc8bc48  jne short 0xBC8BC34                           ; -> loc_bc8bc34` | branch to 0xBC8BC34 | [V] |
| 0xbc8bc4a | - | [0x12AE1B58] | `0xbc8bc4a  mov [0x12AE1B58],rcx                          ; [data_12ae1b58]` | store -> 0x12AE1B58 | [V] |
| 0xbc8bc51 | - | [rbp+0x330] | `0xbc8bc51  lea rcx,[rbp+0x330]` | - | [V] |
| 0xbc8bc58 | - | ->0x73150 | `0xbc8bc58  call 0x73150                                  ; -> sub_73150` | call 0x73150 | [V] |
| 0xbc8bc5d | - | [0x12AE1B60] | `0xbc8bc5d  lea rcx,[0x12AE1B60]                          ; [data_12ae1b60]` | lea rodata 0x12AE1B60 | [V] |
| 0xbc8bc64 | - | ->0xE938D70 | `0xbc8bc64  call 0xE938D70                                ; -> sub_e938d70` | call sub_e938d70 (input slot register) | [V] |
| 0xbc8bc69 | - | - | `0xbc8bc69  jmp 0xBC8A3E2                                 ; -> sub_bc8a3e2` | branch to 0xBC8A3E2 | [V] |
| 0xbc8bc6e | - | - | `0xbc8bc6e  and rdx,0xFFFFFFFFFFFFFFFC` | - | [V] |
| 0xbc8bc72 | 8 | - | `0xbc8bc72  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bc7c | - | - | `0xbc8bc7c  xor r8d,r8d` | - | [V] |
| 0xbc8bc7f | 8 | - | `0xbc8bc7f  mov r9,0x100000001B3` | - | [V] |
| 0xbc8bc89 | 1 | [rsi+r8] | `0xbc8bc89  movzx r10d,byte ptr [rsi+r8]` | - | [V] |
| 0xbc8bc8e | - | - | `0xbc8bc8e  xor r10,rcx` | - | [V] |
| 0xbc8bc91 | - | - | `0xbc8bc91  imul r10,r9` | - | [V] |
| 0xbc8bc95 | 1 | [rsi+r8+1] | `0xbc8bc95  movzx ecx,byte ptr [rsi+r8+1]` | - | [V] |
| 0xbc8bc9b | - | - | `0xbc8bc9b  xor rcx,r10` | - | [V] |
| 0xbc8bc9e | - | - | `0xbc8bc9e  imul rcx,r9` | - | [V] |
| 0xbc8bca2 | 1 | [rsi+r8+2] | `0xbc8bca2  movzx r10d,byte ptr [rsi+r8+2]` | - | [V] |
| 0xbc8bca8 | - | - | `0xbc8bca8  xor r10,rcx` | - | [V] |
| 0xbc8bcab | - | - | `0xbc8bcab  imul r10,r9` | - | [V] |
| 0xbc8bcaf | 1 | [rsi+r8+3] | `0xbc8bcaf  movzx ecx,byte ptr [rsi+r8+3]` | - | [V] |
| 0xbc8bcb5 | - | - | `0xbc8bcb5  xor rcx,r10` | - | [V] |
| 0xbc8bcb8 | - | - | `0xbc8bcb8  imul rcx,r9` | - | [V] |
| 0xbc8bcbc | - | - | `0xbc8bcbc  add r8,4` | - | [V] |
| 0xbc8bcc0 | - | - | `0xbc8bcc0  cmp rdx,r8` | - | [V] |
| 0xbc8bcc3 | - | - | `0xbc8bcc3  jne short 0xBC8BC89                           ; -> loc_bc8bc89` | branch to 0xBC8BC89 | [V] |
| 0xbc8bcc5 | - | - | `0xbc8bcc5  test rax,rax` | - | [V] |
| 0xbc8bcc8 | - | - | `0xbc8bcc8  je short 0xBC8BCF2                            ; -> loc_bc8bcf2` | branch to 0xBC8BCF2 | [V] |
| 0xbc8bcca | - | - | `0xbc8bcca  add rsi,r8` | - | [V] |
| 0xbc8bccd | - | - | `0xbc8bccd  xor edx,edx` | - | [V] |
| 0xbc8bccf | 8 | - | `0xbc8bccf  mov r8,0x100000001B3` | - | [V] |
| 0xbc8bcd9 | 8 | - | `0xbc8bcd9  mov r9,rcx` | - | [V] |
| 0xbc8bcdc | 1 | [rsi+rdx] | `0xbc8bcdc  movzx ecx,byte ptr [rsi+rdx]` | - | [V] |
| 0xbc8bce0 | - | - | `0xbc8bce0  xor rcx,r9` | - | [V] |
| 0xbc8bce3 | - | - | `0xbc8bce3  imul rcx,r8` | - | [V] |
| 0xbc8bce7 | - | - | `0xbc8bce7  inc rdx` | - | [V] |
| 0xbc8bcea | 8 | - | `0xbc8bcea  mov r9,rcx` | - | [V] |
| 0xbc8bced | - | - | `0xbc8bced  cmp rax,rdx` | - | [V] |
| 0xbc8bcf0 | - | - | `0xbc8bcf0  jne short 0xBC8BCDC                           ; -> loc_bc8bcdc` | branch to 0xBC8BCDC | [V] |
| 0xbc8bcf2 | - | [0x12AE1B68] | `0xbc8bcf2  mov [0x12AE1B68],rcx                          ; [data_12ae1b68]` | store -> 0x12AE1B68 | [V] |
| 0xbc8bcf9 | - | [rbp+0x330] | `0xbc8bcf9  lea rcx,[rbp+0x330]` | - | [V] |
| 0xbc8bd00 | - | ->0x73150 | `0xbc8bd00  call 0x73150                                  ; -> sub_73150` | call 0x73150 | [V] |
| 0xbc8bd05 | - | [0x12AE1B70] | `0xbc8bd05  lea rcx,[0x12AE1B70]                          ; [data_12ae1b70]` | lea rodata 0x12AE1B70 | [V] |
| 0xbc8bd0c | - | ->0xE938D70 | `0xbc8bd0c  call 0xE938D70                                ; -> sub_e938d70` | call sub_e938d70 (input slot register) | [V] |
| 0xbc8bd11 | - | - | `0xbc8bd11  jmp 0xBC8A407                                 ; -> sub_bc8a407` | branch to 0xBC8A407 | [V] |
| 0xbc8bd16 | - | - | `0xbc8bd16  and rdx,0xFFFFFFFFFFFFFFFC` | - | [V] |
| 0xbc8bd1a | 8 | - | `0xbc8bd1a  mov rcx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bd24 | - | - | `0xbc8bd24  xor r8d,r8d` | - | [V] |
| 0xbc8bd27 | 8 | - | `0xbc8bd27  mov r9,0x100000001B3` | - | [V] |
| 0xbc8bd31 | 1 | [rsi+r8] | `0xbc8bd31  movzx r10d,byte ptr [rsi+r8]` | - | [V] |
| 0xbc8bd36 | - | - | `0xbc8bd36  xor r10,rcx` | - | [V] |
| 0xbc8bd39 | - | - | `0xbc8bd39  imul r10,r9` | - | [V] |
| 0xbc8bd3d | 1 | [rsi+r8+1] | `0xbc8bd3d  movzx ecx,byte ptr [rsi+r8+1]` | - | [V] |
| 0xbc8bd43 | - | - | `0xbc8bd43  xor rcx,r10` | - | [V] |
| 0xbc8bd46 | - | - | `0xbc8bd46  imul rcx,r9` | - | [V] |
| 0xbc8bd4a | 1 | [rsi+r8+2] | `0xbc8bd4a  movzx r10d,byte ptr [rsi+r8+2]` | - | [V] |
| 0xbc8bd50 | - | - | `0xbc8bd50  xor r10,rcx` | - | [V] |
| 0xbc8bd53 | - | - | `0xbc8bd53  imul r10,r9` | - | [V] |
| 0xbc8bd57 | 1 | [rsi+r8+3] | `0xbc8bd57  movzx ecx,byte ptr [rsi+r8+3]` | - | [V] |
| 0xbc8bd5d | - | - | `0xbc8bd5d  xor rcx,r10` | - | [V] |
| 0xbc8bd60 | - | - | `0xbc8bd60  imul rcx,r9` | - | [V] |
| 0xbc8bd64 | - | - | `0xbc8bd64  add r8,4` | - | [V] |
| 0xbc8bd68 | - | - | `0xbc8bd68  cmp rdx,r8` | - | [V] |
| 0xbc8bd6b | - | - | `0xbc8bd6b  jne short 0xBC8BD31                           ; -> loc_bc8bd31` | branch to 0xBC8BD31 | [V] |
| 0xbc8bd6d | - | - | `0xbc8bd6d  test rax,rax` | - | [V] |
| 0xbc8bd70 | - | - | `0xbc8bd70  je short 0xBC8BD9A                            ; -> loc_bc8bd9a` | branch to 0xBC8BD9A | [V] |
| 0xbc8bd72 | - | - | `0xbc8bd72  add rsi,r8` | - | [V] |
| 0xbc8bd75 | - | - | `0xbc8bd75  xor edx,edx` | - | [V] |
| 0xbc8bd77 | 8 | - | `0xbc8bd77  mov r8,0x100000001B3` | - | [V] |
| 0xbc8bd81 | 8 | - | `0xbc8bd81  mov r9,rcx` | - | [V] |
| 0xbc8bd84 | 1 | [rsi+rdx] | `0xbc8bd84  movzx ecx,byte ptr [rsi+rdx]` | - | [V] |
| 0xbc8bd88 | - | - | `0xbc8bd88  xor rcx,r9` | - | [V] |
| 0xbc8bd8b | - | - | `0xbc8bd8b  imul rcx,r8` | - | [V] |
| 0xbc8bd8f | - | - | `0xbc8bd8f  inc rdx` | - | [V] |
| 0xbc8bd92 | 8 | - | `0xbc8bd92  mov r9,rcx` | - | [V] |
| 0xbc8bd95 | - | - | `0xbc8bd95  cmp rax,rdx` | - | [V] |
| 0xbc8bd98 | - | - | `0xbc8bd98  jne short 0xBC8BD84                           ; -> loc_bc8bd84` | branch to 0xBC8BD84 | [V] |
| 0xbc8bd9a | - | [0x12AE1B78] | `0xbc8bd9a  mov [0x12AE1B78],rcx                          ; [data_12ae1b78]` | store -> 0x12AE1B78 | [V] |
| 0xbc8bda1 | - | [rbp+0x330] | `0xbc8bda1  lea rcx,[rbp+0x330]` | - | [V] |
| 0xbc8bda8 | - | ->0x73150 | `0xbc8bda8  call 0x73150                                  ; -> sub_73150` | call 0x73150 | [V] |
| 0xbc8bdad | - | [0x12AE1B80] | `0xbc8bdad  lea rcx,[0x12AE1B80]                          ; [data_12ae1b80]` | lea rodata 0x12AE1B80 | [V] |
| 0xbc8bdb4 | - | ->0xE938D70 | `0xbc8bdb4  call 0xE938D70                                ; -> sub_e938d70` | call sub_e938d70 (input slot register) | [V] |
| 0xbc8bdb9 | - | - | `0xbc8bdb9  jmp 0xBC8A42C                                 ; -> sub_bc8a42c` | branch to 0xBC8A42C | [V] |
| 0xbc8bdbe | - | - | `0xbc8bdbe  and r8,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8bdc2 | 8 | - | `0xbc8bdc2  mov rdx,0xCBF29CE484222325` | - | [V] |
| 0xbc8bdcc | 1 | [r15] | `0xbc8bdcc  movzx r9d,byte ptr [r15]` | - | [V] |
| 0xbc8bdd0 | - | - | `0xbc8bdd0  imul rdx,rcx` | - | [V] |
| 0xbc8bdd4 | - | - | `0xbc8bdd4  xor rdx,r9` | - | [V] |
| 0xbc8bdd7 | 1 | [r15+1] | `0xbc8bdd7  movzx r9d,byte ptr [r15+1]` | - | [V] |
| 0xbc8bddc | - | - | `0xbc8bddc  imul rdx,rcx` | - | [V] |
| 0xbc8bde0 | - | - | `0xbc8bde0  xor rdx,r9` | - | [V] |
| 0xbc8bde3 | 1 | [r15+2] | `0xbc8bde3  movzx r9d,byte ptr [r15+2]` | - | [V] |
| 0xbc8bde8 | - | - | `0xbc8bde8  imul rdx,rcx` | - | [V] |
| 0xbc8bdec | - | - | `0xbc8bdec  xor rdx,r9` | - | [V] |
| 0xbc8bdef | 1 | [r15+3] | `0xbc8bdef  movzx r9d,byte ptr [r15+3]` | - | [V] |
| 0xbc8bdf4 | - | - | `0xbc8bdf4  imul rdx,rcx` | - | [V] |
| 0xbc8bdf8 | - | - | `0xbc8bdf8  xor rdx,r9` | - | [V] |
| 0xbc8bdfb | 1 | [r15+4] | `0xbc8bdfb  movzx r9d,byte ptr [r15+4]` | - | [V] |
| 0xbc8be00 | - | - | `0xbc8be00  imul rdx,rcx` | - | [V] |
| 0xbc8be04 | - | - | `0xbc8be04  xor rdx,r9` | - | [V] |
| 0xbc8be07 | 1 | [r15+5] | `0xbc8be07  movzx r9d,byte ptr [r15+5]` | - | [V] |
| 0xbc8be0c | - | - | `0xbc8be0c  imul rdx,rcx` | - | [V] |
| 0xbc8be10 | - | - | `0xbc8be10  xor rdx,r9` | - | [V] |
| 0xbc8be13 | 1 | [r15+6] | `0xbc8be13  movzx r9d,byte ptr [r15+6]` | - | [V] |
| 0xbc8be18 | - | - | `0xbc8be18  imul rdx,rcx` | - | [V] |
| 0xbc8be1c | - | - | `0xbc8be1c  xor rdx,r9` | - | [V] |
| 0xbc8be1f | 1 | [r15+7] | `0xbc8be1f  movzx r9d,byte ptr [r15+7]` | - | [V] |
| 0xbc8be24 | - | - | `0xbc8be24  imul rdx,rcx` | - | [V] |
| 0xbc8be28 | - | - | `0xbc8be28  xor rdx,r9` | - | [V] |
| 0xbc8be2b | - | - | `0xbc8be2b  add r15,8` | - | [V] |
| 0xbc8be2f | - | - | `0xbc8be2f  add r8,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0xbc8be33 | - | - | `0xbc8be33  jne short 0xBC8BDCC                           ; -> loc_bc8bdcc` | branch to 0xBC8BDCC | [V] |
| 0xbc8be35 | - | - | `0xbc8be35  test rax,rax` | - | [V] |
| 0xbc8be38 | - | - | `0xbc8be38  je short 0xBC8BE51                            ; -> loc_bc8be51` | branch to 0xBC8BE51 | [V] |
| 0xbc8be3a | - | - | `0xbc8be3a  xor r8d,r8d` | - | [V] |
| 0xbc8be3d | 1 | [r15+r8] | `0xbc8be3d  movzx r9d,byte ptr [r15+r8]` | - | [V] |
| 0xbc8be42 | - | - | `0xbc8be42  imul rdx,rcx` | - | [V] |
| 0xbc8be46 | - | - | `0xbc8be46  xor rdx,r9` | - | [V] |
| 0xbc8be49 | - | - | `0xbc8be49  inc r8` | - | [V] |
| 0xbc8be4c | - | - | `0xbc8be4c  cmp rax,r8` | - | [V] |
| 0xbc8be4f | - | - | `0xbc8be4f  jne short 0xBC8BE3D                           ; -> loc_bc8be3d` | branch to 0xBC8BE3D | [V] |
| 0xbc8be51 | - | [0x12AE1BA0] | `0xbc8be51  mov [0x12AE1BA0],rdx                          ; [data_12ae1ba0]` | store -> 0x12AE1BA0 | [V] |
| 0xbc8be58 | - | [rbp+0x330] | `0xbc8be58  lea rcx,[rbp+0x330]` | - | [V] |
| 0xbc8be5f | - | ->0x73150 | `0xbc8be5f  call 0x73150                                  ; -> sub_73150` | call 0x73150 | [V] |
| 0xbc8be64 | - | [0x12AE1BA8] | `0xbc8be64  lea rcx,[0x12AE1BA8]                          ; [data_12ae1ba8]` | lea rodata 0x12AE1BA8 | [V] |
| 0xbc8be6b | - | ->0xE938D70 | `0xbc8be6b  call 0xE938D70                                ; -> sub_e938d70` | call sub_e938d70 (input slot register) | [V] |
| 0xbc8be70 | - | - | `0xbc8be70  jmp 0xBC8A644                                 ; -> sub_bc8a644` | branch to 0xBC8A644 | [V] |
| 0xbc8be75 | - | ->0x75740 | `0xbc8be75  call 0x75740                                  ; -> sub_75740` | call 0x75740 (trailing unreached) [I unreached: trailing bytes after tail-jmp] | [V] |
| 0xbc8be7a | - | - | `0xbc8be7a  nop` | nop padding [I unreached: trailing bytes after tail-jmp] | [V] |
| 0xbc8be7b | - | - | `0xbc8be7b  int3` | int3 padding [I unreached: trailing bytes after tail-jmp] | [V] |


## (5) Replacement block plan (own upscale)

This body is pass SETUP/BIND, not the upscale compute: it allocates two pass objects (0x130 + 0x340 bytes), resolves four input-resource slots by FNV-1a hashing their names, and registers the "Upscaling" pass name. There is no shader, render-target, command-list or draw logic in 0xbc8ab12..0xbc8be7c [V: no such instruction in the table].

A replacement that "calls only through proven blocks" would need:
- [V] BB20: slot resolution — FNV-1a hash of "InputFinalColor"/"InputBufferMotionVectors"/"InputTAAHistory"/"Color0" via sub_79580/inlined loops, slot lookup via sub_e938cb0, slot registration via sub_e938d70, globals [0x12AE1B58/68/78/BA0] (hashes) and [0x12AE1B60/70/80/98/BA8] (slots), [0x12AE1B88]/"Upscaling" via sub_5668ac0.
- [V] allocator path: [0x1233E1A8] -> [0xF99FFA0] (sub_eea6040) allocate(0x130/0x340), plus object init (sub_568AD40, sub_bc8c890 x3, sub_eec6ec0 memcpy, small-string helpers sub_73150/sub_e935700).
- [I] the actual upscale compute (texture reads, shader dispatch, render-target write) is NOT in this body — it lies beyond the tail-jmp target 0xBC8A644 or elsewhere (map anchors TAA upscaling at 0xbc8cfd0, unverified for this unit). Marked [I]: any replacement must provide its own compute and only call through the proven binding blocks above.

Registry half (RewritePasses.h/.cpp, RewriteRegistry entries, Sigs.json sigs PassTAAUpscaling@0xbc8ab12) already exists on disk from prior units; stubs remain stubs until the C++ replacement is written (not this run).

## CLOSES?

NO — Q5d wording is "Pass-level rewrites (own upscale, own post) behind the registry". This run reverses the TAAUpscaling body 0xbc8ab12 (0xbc8ab12..0xbc8be7c fully tabled [V]) so the proven binding blocks are known, but no working own-upscale/own-post replacement C++ exists on disk yet (stubs only), and the ScreenDraw body 0xbc04dc0 is left for the next run per orchestrator scope. Single blocking fact: no working own-upscale/own-post replacement implementation exists on disk (ScreenDraw body 0xbc04dc0 not reversed; TAA replacement not yet implemented in C++).


