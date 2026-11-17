## NEXT
DONE

# Unit U-Lr6 — ClientInstance::loadResources slice 0x1870001..0x1870357 (chunk 6 of 6)

Input: docs/progress/_part_Lr6.txt — 199 instructions, 0x1870001..0x1870357, static listing only. Every `0xRVA  instr` line below is copied verbatim from that file; no dynamic analysis, no guesses. [V] = seen in the listing at the cited RVA; '-' = meaning not shown by any instruction or string in the slice.

## Summary
Continuation of ClientInstance::loadResources (function entry 0x186e6a0; this slice starts mid-function at 0x1870001). It allocates an 8-byte object through the allocator at IAT slot [0xF99FFA0], tags it with qword 0x900000001 at [rdi], then replaces a prior object: releases via 0x2FE440, frees via 0xE935700 (edx=0x138), allocates 4 bytes, writes dword 0x2A at [rdi], builds two string descriptors ({0xF60BDDE/len 0x15} and {0xF602348/len 0xC}) at [rbp+0x1C0]/[rbp+0x1C8] and [rbp+0x1D0]/[rbp+0x1D8], and calls helper 0x1870DE0 twice (rcx=[rbp+0x628], r9d=0x1D then 0x1E). Allocation-failure cold paths call 0x9BC830 and jump back into earlier code or to retry stubs; the hot path ends with the standard epilogue and ret.

## Register / argument map (within this slice, [V])
- rbp frame: string descriptors at [rbp+0x1C0] (ptr) / [rbp+0x1C8] (len) and [rbp+0x1D0] (ptr) / [rbp+0x1D8] (len); object-pointer slots [rbp+0x420], [rbp+0x428], [rbp+0x430], [rbp+0x438], [rbp+0x440], [rbp+0x448]; context handle [rbp+0x628]; result slot [rbp+0x618]; spill slot [rsp+0x20] (written twice).
- rcx: context handle reloaded from [rbp+0x628] before each call 0x1870DE0 [V 0x1870087, 0x187013d]; also the [rcx]+0 load target at 0x1870008/0x18700c5.
- rax: scratch; allocator return value moved to rdi [V 0x187001b, 0x18700d8].
- rdi: current object pointer, stored into [rbp+0x420] and [rbp+0x438].
- rsi: release/free subject, spilled to [rsp+0x20].
- rdx: string-descriptor address (lea [rbp+0x1C0] / lea [rbp+0x1D0]) for call 0x1870DE0.
- r8: out-reference address (lea [rbp+0x438] / lea [rbp+0x618]) for call 0x1870DE0.
- r9d: tag 0x1D for the first call 0x1870DE0, 0x1E for the second [V 0x1870091, 0x1870144].

## Phase 1: 0x1870001..0x187009c (28 instructions)
Loads the heap/global pointer from [0x1233E1A8], reads [rcx] then [rax+8], and calls the allocator through IAT slot [0xF99FFA0] with edx=8; if the result is null it jumps to retry stub 0x1870301. Otherwise the object pointer (rdi) is stored at [rbp+0x420], qword 0x900000001 is stored into [rdi] as an object tag, rdi+8 is kept at [rbp+0x430]/[rbp+0x428], [rbp+0x438] is zeroed, string descriptor {ptr 0xF60BDDE, len 0x15} is built at [rbp+0x1C0]/[rbp+0x1C8], and helper 0x1870DE0 is called with rcx=[rbp+0x628], rdx=&descriptor, r8=&[rbp+0x438], r9d=0x1D.

0x1870001  mov rcx,[0x1233E1A8]
0x1870008  mov rax,[rcx]
0x187000b  mov rax,[rax+8]
0x187000f  mov edx,8
0x1870014  call qword ptr [0xF99FFA0]
0x187001a  nop
0x187001b  mov rdi,rax
0x187001e  test rax,rax
0x1870021  je 0x1870301
0x1870027  mov [rbp+0x420],rdi
0x187002e  mov rax,rdi
0x1870031  add rax,8
0x1870035  mov [rbp+0x430],rax
0x187003c  mov rcx,0x900000001
0x1870046  mov [rdi],rcx
0x1870049  mov [rbp+0x428],rax
0x1870050  mov qword ptr [rbp+0x438],0
0x187005b  lea rax,[0xF60BDDE]
0x1870062  mov [rbp+0x1C0],rax
0x1870069  mov qword ptr [rbp+0x1C8],0x15
0x1870074  mov [rsp+0x20],rsi
0x1870079  lea rdx,[rbp+0x1C0]
0x1870080  lea rsi,[rbp+0x438]
0x1870087  mov rcx,[rbp+0x628]
0x187008e  mov r8,rsi
0x1870091  mov r9d,0x1D
0x1870097  call 0x1870DE0
0x187009c  nop

## Phase 2: 0x187009d..0x18700de (17 instructions)
If [rbp+0x438] holds a prior non-null object, releases it via call 0x2FE440 then frees via call 0xE935700 with edx=0x138; then allocates 4 bytes through IAT slot [0xF99FFA0] and, if null, jumps to retry stub 0x1870311.

0x187009d  mov rdi,[rbp+0x438]
0x18700a4  test rdi,rdi
0x18700a7  je short 0x18700BE
0x18700a9  mov rcx,rdi
0x18700ac  call 0x2FE440
0x18700b1  mov edx,0x138
0x18700b6  mov rcx,rdi
0x18700b9  call 0xE935700
0x18700be  mov rcx,[0x1233E1A8]
0x18700c5  mov rax,[rcx]
0x18700c8  mov rax,[rax+8]
0x18700cc  mov edx,4
0x18700d1  call qword ptr [0xF99FFA0]
0x18700d7  nop
0x18700d8  mov rdi,rax
0x18700db  test rax,rax
0x18700de  je 0x1870311

## Phase 3: 0x18700e4..0x187016c (25 instructions)
Stores the new 4-byte object at [rbp+0x438], keeps rdi+4 at [rbp+0x448] and [rbp+0x440], writes dword 0x2A into [rdi], zeroes [rbp+0x618], builds string descriptor {ptr 0xF602348, len 0xC} at [rbp+0x1D0]/[rbp+0x1D8], and calls 0x1870DE0 with rcx=[rbp+0x628], rdx=&descriptor, r8=&[rbp+0x618], r9d=0x1E; if [rbp+0x618] is non-null afterwards it is released via 0x2FE440 and freed via 0xE935700 (edx=0x138).

0x18700e4  mov [rbp+0x438],rdi
0x18700eb  mov rax,rdi
0x18700ee  add rax,4
0x18700f2  mov [rbp+0x448],rax
0x18700f9  mov dword ptr [rdi],0x2A
0x18700ff  mov [rbp+0x440],rax
0x1870106  mov qword ptr [rbp+0x618],0
0x1870111  lea rax,[0xF602348]
0x1870118  mov [rbp+0x1D0],rax
0x187011f  mov qword ptr [rbp+0x1D8],0xC
0x187012a  mov [rsp+0x20],rsi
0x187012f  lea rdx,[rbp+0x1D0]
0x1870136  lea r8,[rbp+0x618]
0x187013d  mov rcx,[rbp+0x628]
0x1870144  mov r9d,0x1E
0x187014a  call 0x1870DE0
0x187014f  nop
0x1870150  mov rsi,[rbp+0x618]
0x1870157  test rsi,rsi
0x187015a  je short 0x1870171
0x187015c  mov rcx,rsi
0x187015f  call 0x2FE440
0x1870164  mov edx,0x138
0x1870169  mov rcx,rsi
0x187016c  call 0xE935700

## Phase 4: 0x1870171..0x187018b (11 instructions)
Epilogue: reloads [rbp+0x628] into rax, deallocates the frame (add rsp,0x6B8), pops rbx/rdi/rsi/r12/r13/r14/r15/rbp and returns.

0x1870171  mov rax,[rbp+0x628]
0x1870178  add rsp,0x6B8
0x187017f  pop rbx
0x1870180  pop rdi
0x1870181  pop rsi
0x1870182  pop r12
0x1870184  pop r13
0x1870186  pop r14
0x1870188  pop r15
0x187018a  pop rbp
0x187018b  ret

## Phase 5: 0x187018c..0x187020c (33 instructions)
Cold allocation-failure stubs: each loads a size into ecx (0x18, 0x30, 0x150, 0x20, 8, 0x14, 0x1C, 4 — the first also does mov rax,rdi around the call), calls helper 0x9BC830, then jumps to an earlier function address (0x186E6F8 .. 0x186F053).

0x187018c  mov ecx,0x18
0x1870191  mov rdi,rax
0x1870194  call 0x9BC830
0x1870199  mov rax,rdi
0x187019c  jmp 0x186E6F8
0x18701a1  mov ecx,0x30
0x18701a6  call 0x9BC830
0x18701ab  nop
0x18701ac  jmp 0x186E850
0x18701b1  mov ecx,0x150
0x18701b6  call 0x9BC830
0x18701bb  nop
0x18701bc  jmp 0x186E9CB
0x18701c1  mov ecx,0x20
0x18701c6  call 0x9BC830
0x18701cb  nop
0x18701cc  jmp 0x186EA09
0x18701d1  mov ecx,8
0x18701d6  call 0x9BC830
0x18701db  nop
0x18701dc  jmp 0x186EA97
0x18701e1  mov ecx,0x14
0x18701e6  call 0x9BC830
0x18701eb  nop
0x18701ec  jmp 0x186EBDA
0x18701f1  mov ecx,0x1C
0x18701f6  call 0x9BC830
0x18701fb  nop
0x18701fc  jmp 0x186EF08
0x1870201  mov ecx,4
0x1870206  call 0x9BC830
0x187020b  nop
0x187020c  jmp 0x186F053

## Phase 6: 0x1870211..0x18702ac (40 instructions)
More cold failure stubs: ecx sizes 4, 8, 0x10, 4, 4, 4, 4, 0x10, 4, 8, each calling 0x9BC830 followed by nop and jumping to 0x186F18F .. 0x186FBD1.

0x1870211  mov ecx,4
0x1870216  call 0x9BC830
0x187021b  nop
0x187021c  jmp 0x186F18F
0x1870221  mov ecx,8
0x1870226  call 0x9BC830
0x187022b  nop
0x187022c  jmp 0x186F563
0x1870231  mov ecx,0x10
0x1870236  call 0x9BC830
0x187023b  nop
0x187023c  jmp 0x186F635
0x1870241  mov ecx,4
0x1870246  call 0x9BC830
0x187024b  nop
0x187024c  jmp 0x186F704
0x1870251  mov ecx,4
0x1870256  call 0x9BC830
0x187025b  nop
0x187025c  jmp 0x186F7CF
0x1870261  mov ecx,4
0x1870266  call 0x9BC830
0x187026b  nop
0x187026c  jmp 0x186F89A
0x1870271  mov ecx,0x10
0x1870276  call 0x9BC830
0x187027b  nop
0x187027c  jmp 0x186F965
0x1870281  mov ecx,4
0x1870286  call 0x9BC830
0x187028b  nop
0x187028c  jmp 0x186FA34
0x1870291  mov ecx,8
0x1870296  call 0x9BC830
0x187029b  nop
0x187029c  jmp 0x186FAFF
0x18702a1  mov ecx,8
0x18702a6  call 0x9BC830
0x18702ab  nop
0x18702ac  jmp 0x186FBD1

## Phase 7: 0x18702b1..0x187033a (36 instructions)
Remaining cold failure stubs (ecx=4/8/8/4/8/4/0x70 then rcx=r15, each calling 0x9BC830 and jumping to 0x186FC8E/0x186FD44/0x186FE01/0x186FEB4/0x186FF6A/0x186E77D/0x186E932), plus two retry paths: 0x1870301 calls 0x9BC830 with ecx=8 then jumps back to 0x1870027, and 0x1870311 calls 0x9BC830 with ecx=4 then jumps back to 0x18700E4.

0x18702b1  mov ecx,4
0x18702b6  call 0x9BC830
0x18702bb  nop
0x18702bc  jmp 0x186FC8E
0x18702c1  mov ecx,8
0x18702c6  call 0x9BC830
0x18702cb  nop
0x18702cc  jmp 0x186FD44
0x18702d1  mov ecx,8
0x18702d6  call 0x9BC830
0x18702db  nop
0x18702dc  jmp 0x186FE01
0x18702e1  mov ecx,4
0x18702e6  call 0x9BC830
0x18702eb  nop
0x18702ec  jmp 0x186FEB4
0x18702f1  mov ecx,8
0x18702f6  call 0x9BC830
0x18702fb  nop
0x18702fc  jmp 0x186FF6A
0x1870301  mov ecx,8
0x1870306  call 0x9BC830
0x187030b  nop
0x187030c  jmp 0x1870027
0x1870311  mov ecx,4
0x1870316  call 0x9BC830
0x187031b  nop
0x187031c  jmp 0x18700E4
0x1870321  mov ecx,0x70
0x1870326  call 0x9BC830
0x187032b  nop
0x187032c  jmp 0x186E77D
0x1870331  mov rcx,r15
0x1870334  call 0x9BC830
0x1870339  nop
0x187033a  jmp 0x186E932

## Phase 8: 0x187033f..0x1870357 (9 instructions)
Last cold stub (rcx=r15, call 0x9BC830, xor r14d,r14d, jmp 0x186E977) followed by unreachable tail: call 0x75720, nop, int3, nop [rax+rax] padding.

0x187033f  mov rcx,r15
0x1870342  call 0x9BC830
0x1870347  nop
0x1870348  xor r14d,r14d
0x187034b  jmp 0x186E977
0x1870350  call 0x75720
0x1870355  nop
0x1870356  int3
0x1870357  nop [rax+rax]

## Instruction completeness
Every one of the 199 instructions (0x1870001..0x1870357) is assigned to exactly one phase (phases 1-8); none are skipped or summarized.

## Field table — every [reg+off] store/load (one row per distinct offset, all sites listed)
| offset | size | direction | verbatim line(s) | meaning |
|---|---|---|---|---|
| 0 | 8B qword / 4B dword | R at [rcx] (2 sites), W at [rdi] (2 sites) | `0x1870008  mov rax,[rcx]` (R); `0x18700c5  mov rax,[rcx]` (R); `0x1870046  mov [rdi],rcx` (W); `0x18700f9  mov dword ptr [rdi],0x2A` (W) | - |
| 0x1c0 | 8B qword | W | `0x1870062  mov [rbp+0x1C0],rax` | string descriptor pointer 0xF60BDDE [V 0x187005b lea rax,[0xF60BDDE]] |
| 0x1c8 | 8B qword | W | `0x1870069  mov qword ptr [rbp+0x1C8],0x15` | string length 0x15 [V 0x1870069] |
| 0x1d0 | 8B qword | W | `0x1870118  mov [rbp+0x1D0],rax` | string descriptor pointer 0xF602348 [V 0x1870111 lea rax,[0xF602348]] |
| 0x1d8 | 8B qword | W | `0x187011f  mov qword ptr [rbp+0x1D8],0xC` | string length 0xC [V 0x187011f] |
| 0x420 | 8B qword | W | `0x1870027  mov [rbp+0x420],rdi` | - |
| 0x428 | 8B qword | W | `0x1870049  mov [rbp+0x428],rax` | - |
| 0x430 | 8B qword | W | `0x1870035  mov [rbp+0x430],rax` | - |
| 0x438 | 8B qword | W at 0x1870050 (=0) / R at 0x187009d (/->rdi) / W at 0x18700e4 (=rdi) | `0x1870050  mov qword ptr [rbp+0x438],0` (W); `0x187009d  mov rdi,[rbp+0x438]` (R); `0x18700e4  mov [rbp+0x438],rdi` (W) | - |
| 0x440 | 8B qword | W | `0x18700ff  mov [rbp+0x440],rax` | - |
| 0x448 | 8B qword | W | `0x18700f2  mov [rbp+0x448],rax` | - |
| 0x618 | 8B qword | W (=0) then R (->rsi) | `0x1870106  mov qword ptr [rbp+0x618],0` (W); `0x1870150  mov rsi,[rbp+0x618]` (R) | - |
| 0x628 | 8B qword | R | `0x1870087  mov rcx,[rbp+0x628]` (R); `0x187013d  mov rcx,[rbp+0x628]` (R); `0x1870171  mov rax,[rbp+0x628]` (R) | - |
| 8 | 8B qword | R | `0x187000b  mov rax,[rax+8]` | - |
| 0x20 | 8B qword | W (stack spill, rsi, 2 sites) | `0x1870074  mov [rsp+0x20],rsi` (W); `0x187012a  mov [rsp+0x20],rsi` (W) | - |

## Callees
0xF99FFA0 (IAT slot, `call qword ptr [0xF99FFA0]`) | allocator-like: called with edx=8 (0x187000f) and edx=4 (0x18700cc), return value used as object pointer | [V 0x1870014, 0x18700d1; meaning [I]]
0x1870DE0 | resource helper: rcx=[rbp+0x628], rdx=string-descriptor address, r8=out-reference, r9d=tag (0x1D / 0x1E) | [V 0x1870097, 0x187014a; meaning [I]]
0x2FE440 | release-like: rcx=object pointer | [V 0x18700ac, 0x187015f; meaning [I]]
0xE935700 | free-like: rcx=object pointer, edx=0x138 | [V 0x18700b9, 0x187016c; meaning [I]]
0x9BC830 | cold-path helper: ecx=size (or rcx=r15 at 0x1870331/0x187033f), always followed by jmp | [V 28 sites; meaning [I]]
0x75720 | called once at 0x1870350 before int3; not further resolvable in this slice | [V 0x1870350; meaning -]

## OPEN questions
- Meaning of frame slots [rbp+0x420], [rbp+0x428], [rbp+0x430], [rbp+0x438], [rbp+0x440], [rbp+0x448], [rbp+0x618] (object-pointer/result slots): not named by any instruction or string in the slice -> [?]
- Whether [rbp+0x438] old-object release is a destructor, close, or refcount decrement: not shown -> [?]
- Contents of the strings at 0xF60BDDE (len 0x15) and 0xF602348 (len 0xC): addresses seen, data not read in this static slice -> [?]
- Exact targets/semantics of IAT slot [0xF99FFA0] and of helpers 0x1870DE0, 0x2FE440, 0xE935700, 0x9BC830, 0x75720: call sites seen, callees not resolved in this slice -> [?]

## TOOL REQUESTS
None | - | - | All work done by verbatim transcription of the precomputed listing plus the delegate/verify checkers.
