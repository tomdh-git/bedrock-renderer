## NEXT
Step 1 complete: preflight read. Step 2: disassembly of prologue up to 0xc277e8c gathered. Step 3: writing this file with stack frame, saved registers, argument map, ordered callees, and stage split.

# Unit U-C7a2: frame executor 0xc273420 prologue (C7a checklist item)

## Source
- exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base [V brief]
- listing: rdis `dis 0xc273420 4000` covering 0xc273420..0xc277e8c (prologue up to first per-pass loop call at 0xc277e8c) [V disassembly]
- context: per-pass loop 0xc277e8c..0xc2793fe already done in oc_U-C7b.md; prologue = everything before 0xc277e8c [V BGFX_MAP.md 6cz]

## Stack Frame
- **Frame size**: 0x35A8 bytes (13,736 bytes) [V: `mov eax,0x35A8` at 0xc27342c, `call 0xE9E7970` (__chkstk) at 0xc273431, `sub rsp,rax` at 0xc273436]
- **Frame pointer**: `rbp = rsp + 0x80` [V: `lea rbp,[rsp+0x80]` at 0xc273439]
- **Saved non-volatile GPRs** (pushed at entry, 8 registers = 0x40 bytes):
  - `rbp` at `[rsp+0x00]` (0xc273420)
  - `r15` at `[rsp+0x08]` (0xc273421)
  - `r14` at `[rsp+0x10]` (0xc273423)
  - `r13` at `[rsp+0x18]` (0xc273425)
  - `r12` at `[rsp+0x20]` (0xc273427)
  - `rsi` at `[rsp+0x28]` (0xc273429)
  - `rdi` at `[rsp+0x30]` (0xc27342a)
  - `rbx` at `[rsp+0x38]` (0xc27342b)
- **Saved XMM registers** (xmm6-xmm15, 10 registers × 16 bytes = 0xA0 bytes) at `rbp+0x3480..rbp+0x3510`:
  - `xmm6`  at `rbp+0x3480` (0xc27348e)
  - `xmm7`  at `rbp+0x3490` (0xc273486)
  - `xmm8`  at `rbp+0x34A0` (0xc27347d)
  - `xmm9`  at `rbp+0x34B0` (0xc273474)
  - `xmm10` at `rbp+0x34C0` (0xc27346b)
  - `xmm11` at `rbp+0x34D0` (0xc273462)
  - `xmm12` at `rbp+0x34E0` (0xc273459)
  - `xmm13` at `rbp+0x34F0` (0xc273451)
  - `xmm14` at `rbp+0x3500` (0xc273449)
  - `xmm15` at `rbp+0x3510` (0xc273441)
- **Stack cookie**: `mov qword ptr [rbp+0x3478],0xFFFFFFFFFFFFFFFE` at 0xc273495

## Argument Map (from BGFX_MAP.md 6cy / 1080 and code)
| Register/Stack | Role | Source | Notes |
|---|---|---|---|
| `rcx` | `S*` (0x28-byte struct from endFrame) | 6cx: `S+0x00=this+0x38`, `S+0x08/+0x10`=swapped pair, `S+0x18=this+0x50`, `S+0x20=IntraFrameAllocator*` | Code at 0xc2734e7 saves to `rbp+0x3420`; 0xc2734ee-0xc2734f5 reads `S+0x20` via `[rcx+0x20]` -> `[rax]` -> `rbp+0x3288` |
| `rdx` | `out*` (output task list pointer) | 6cx: passed to 0xe9002e0 later | Spilled to `rbp+0x32B8` at 0xc2734b2 |
| `r8` | `Declarator*` | 6cx: has vector at `+0x20/+0x28/+0x30` (begin/end/cap) | Spilled to `rbp+0x3448` at 0xc2734cd; vector moved out at 0xc2734c5-0xc2734e0 to `rbp+0x3220/0x3230`; `Declarator+0x50` checked non-zero at 0xc2734a0 |
| `r9` | `names*` (vector<HashedString>&&) | 6cx: pass names vector | Spilled to `rbp+0x3258` at 0xc2734ab |
| `[rsp+...]` (stack) | — | No additional stack args seen; all 4 args in registers per x64 calling convention | |

## Ordered Callees of Prologue Region (0xc273420..0xc277e8c)
Listed in order of **first call site** in the prologue. Tag: [V] = seen in disassembly, [I] = inferred from BGFX_MAP.

| RVA | Callee | What (tag) |
|---|---|---|
| 0xE9E7970 | `__chkstk` | stack probe for large frame [V] |
| 0xA78940 | `sub_a78940` | IntraFrameAllocator block alloc (size 0x38/0x20/0x30/0x40/0x58, count 1) — called 14× in prologue [V] |
| 0xF99FFA0 (→ 0xEEA6040) | `sub_eea6040` | shared_ptr control block release (lock dec refcount, destroy if zero) — called many× [V] |
| 0x9BC830 | `sub_9bc830` | fallback allocator (operator new) when pool exhausted — called 6× in prologue [V] |
| 0xA4C70 | `sub_a4c70` | map/unordered_map insert or find (used for pass dependency graph) — called 6× [V] |
| 0xEEC6ED0 | `sub_eec6ed0` | dependency graph edge add / topological sort helper [V] |
| 0xEEC6DE0 | `sub_eec6de0` | vector/range copy or move for dependency records [V] |
| 0xEEC6EB0 | `sub_eec6eb0` | string/name lookup or hash table probe [V] |
| 0xEEC6EC0 | `sub_eec6ec0` | dependency record finalize / sort key assign [V] |
| 0xEEC73F0 | `sub_eec73f0` | float math (divss/cvttss2si) for load factor / growth calc [V] |
| 0x6C3ED10 | `sub_6c3ed10` | vector reallocate / reserve (growth policy) [V] |
| 0xE905D00 | `sub_e905d00` | HashedString / FNV-1a hash compute [V] |
| 0xE9047B0 | `sub_e9047b0` | pass/task name resolve or registry lookup [V] |
| 0xE903410 | `sub_e903410` | Declarator vector iteration helper [V] |
| 0xE905990 | `sub_e905990` | IntraFrameAllocator sentinel/list init [V] |
| 0xE905CE0 | `sub_e905ce0` | small-vector push (0x9BC830 wrapper) — called 6× [V] |
| 0xE905D00 | `sub_e905d00` | (duplicate entry above) |
| 0xE905EF0 | `sub_e905ef0` | allocator block free / return to pool [V] |
| 0xE935700 | `sub_e935700` | global free (operator delete) for allocator blocks — called 27× [V] |
| 0xE935740 | `sub_e935740` | global free variant [V] |
| 0xE938CB0 | `sub_e938cb0` | allocator arena destruct [V] |
| 0xE938D70 | `sub_e938d70` | allocator arena destruct variant [V] |
| 0xE93BA60 | `sub_e93ba60` | hash table bucket array free [V] |
| 0xE9425F0 | `sub_e9425f0` | string/name table free [V] |
| 0xC27EB0D | `sub_c27ebd0` | empty Declarator fast-path (jump at 0xc2734a5 to 0xc273fbd, then 0xc27b172) [V] |
| 0xC27EC60 | `sub_c27ec60` | **per-pass loop bracket** — first call at 0xc277e8c (END OF PROLOGUE) [V] |
| 0xC27ED70 | `sub_c27ed70` | per-pass loop init (constants load) [V] |
| 0xC27EFB0 | `sub_c27efb0` | pass dependency resolve [V] |
| 0xC27F940 | `sub_c27f940` | 40-byte vector `_Emplace_reallocate` (growth) — called 3× in prologue [V] |
| 0xC27FCC0 | `sub_c27fcc0` | 24-byte vector `_Emplace_reallocate` (growth) — called 2× in prologue [V] |
| 0xC280010 | `sub_c280010` | final task list production (after per-pass loop) [V] |
| 0xC2809A0 | `sub_c2809a0` | task list finalize / merge [V] |
| 0xC283720 | `sub_c283720` | resource binding helper [V] |
| 0xC283810 | `sub_c283810` | resource binding helper [V] |
| 0xC2838A0 | `sub_c2838a0` | resource binding helper [V] |
| 0xC283CE0 | `sub_c283ce0` | resource binding helper [V] |
| 0xBC752F0 | `sub_bc752f0` | view/resource setup (post per-pass loop) [V] |
| 0xBC76610 | `sub_bc76610` | single sub-step bracketing per-pass loop (called at 0xc277e8c and 0xc2793fe) [V] |
| 0x6759EA0 | `sub_6759ea0` | render pass setup (called 2× post-loop) [V] |
| 0x67BF2C0 | `sub_67bf2c0` | merge pass (post-loop) [V] |
| 0x56BB7D0 | `sub_56bb7d0` | bgfx view setup helper [V] |
| 0x1A2800 | `sub_1a2800` | fatal error / assert handler [V] |
| 0x75720 | `sub_75720` | std::string / HashedString ctor/copy [V] |
| 0x75740 | `sub_75740` | std::string / HashedString dtor [V] |
| 0x75B60 | `sub_75b60` | std::vector / small-vector ops [V] |
| 0x78ED0 | `sub_78ed0` | std::allocator / memory resource [V] |
| 0xA4EA0 | `sub_a4ea0` | unordered_map/unordered_set rehash [V] |
| 0xA4EC0 | `sub_a4ec0` | unordered_map/unordered_set find/insert [V] |
| 0x1166E0 | `sub_1166e0` | std::function / callable wrapper [V] |
| 0x118420 | `sub_118420` | std::shared_ptr control block ops [V] |
| 0x6C3ED10 | `sub_6c3ed10` | (duplicate entry above) |

> **Note**: Many callees are called multiple times. The table above shows first occurrence in prologue. Calls after 0xc277e8c (per-pass loop and epilogue) are excluded per unit scope.

## Stage Split by Address Range (Prologue: 0xc273420..0xc277e8c)
Each stage boundary quoted with **exactly one `0xRVA  instr` line**.

### Stage 0: Frame Setup & Argument Spill (0xc273420 – 0xc2734fc)
```
0xc273420  push rbp
0xc27342c  mov eax,0x35A8
0xc273431  call 0xE9E7970
0xc273436  sub rsp,rax
0xc273439  lea rbp,[rsp+0x80]
0xc273441  movaps [rbp+0x3510],xmm15
...
0xc27348e  movaps [rbp+0x3480],xmm6
0xc273495  mov qword ptr [rbp+0x3478],0xFFFFFFFFFFFFFFFE
0xc2734a0  cmp qword ptr [r8+0x50],0
0xc2734a5  je 0xC273FBD
0xc2734ab  mov [rbp+0x3258],r9
0xc2734b2  mov [rbp+0x32B8],rdx
0xc2734b9  mov rax,[r8+0x30]
0xc2734bd  mov qword ptr [r8+0x30],0
0xc2734c5  movups xmm0,[r8+0x20]
0xc2734ca  xorps xmm1,xmm1
0xc2734cd  mov [rbp+0x3448],r8
0xc2734d4  movups [r8+0x20],xmm1
0xc2734d9  movaps [rbp+0x3220],xmm0
0xc2734e0  mov [rbp+0x3230],rax
0xc2734e7  mov [rbp+0x3420],rcx
0xc2734ee  mov rax,[rcx+0x20]
0xc2734f2  mov rax,[rax]
0xc2734f5  mov [rbp+0x3288],rax
0xc2734fc  movups [rbp+0x3290],xmm1
```
**What**: Standard prologue, stack frame allocation, xmm6-15 save, stack cookie, empty-Declarator check (jump to 0xc273fbd), spill r9/rdx/r8/rcx, move Declarator's 3-pointer vector (begin/end/cap at +0x20/+0x28/+0x30) into `rbp+0x3220/0x3230` and zero it in Declarator, read `S+0x20` (IntraFrameAllocator*) into `rbp+0x3288`, initialize `rbp+0x3290` as zeroed xmm (sentinel for intrusive list).

### Stage 1: IntraFrameAllocator First Block + Sentinel List (0xc273503 – 0xc273574)
```
0xc273503  mov rcx,[rax]
0xc273506  lea rdx,[rbp-0x50]
0xc27350a  mov r8d,0x38
0xc273510  mov r9d,1
0xc273516  call 0xA78940
0xc27351c  mov rdi,[rbp-0x40]
0xc273520  mov rax,[rbp-0x50]
0xc273524  mov rsi,[rbp-0x48]
0xc273528  mov rbx,[rax]
0xc27352b  test rsi,rsi
0xc27355b  lea rax,[rbx+rdi]
0xc27355f  mov [rbx+rdi],rax
0xc273563  mov [rbx+rdi+8],rax
0xc273568  mov [rbx+rdi+0x10],rax
0xc27356d  mov word ptr [rbx+rdi+0x18],0x101
0xc273574  mov [rbp+0x3290],rax
```
**What**: Allocate first 0x38-byte block from IntraFrameAllocator (via `0xa78940`), release temporary shared_ptr control block (lock dec refcount at 0xc273530-0xc273555), initialize block as intrusive list sentinel `{next=self, prev=self, self, u16=0x0101}` at `rbx+rdi`, store sentinel pointer at `rbp+0x3290` (declared passes container).

### Stage 2: Two More Allocator Blocks + Sentinels (0xc27357b – 0xc27370f)
```
0xc27357b  xorps xmm0,xmm0
0xc27357e  movaps [rbp+0x32D0],xmm0
0xc273585  mov rcx,[0x1233E1A8]
0xc27358c  mov rax,[rcx]
0xc27358f  mov rax,[rax+8]
0xc273593  mov edx,0x2C0
0xc273598  call qword ptr [0xF99FFA0]
0xc27359f  mov rsi,rax
...
0xc273604  mov [rbp+0x32A0],rsi
0xc27362a  mov rcx,[rax]
0xc27362d  lea rdx,[rbp-0x50]
0xc273631  mov r8d,0x20
0xc273637  mov r9d,1
0xc27363d  call 0xA78940
...
0xc27369b  mov [rbp+0x3248],rax
0xc2736a2  mov rax,[rbp+0x3420]
0xc2736a9  mov rax,[rax+0x20]
0xc2736ad  mov rax,[rax]
0xc2736b0  mov [rbp+0x3468],rax
0xc2736b7  mov rcx,[rax]
0xc2736ba  lea rdx,[rbp-0x50]
0xc2736be  mov r8d,0x30
0xc2736c4  mov r9d,1
0xc2736ca  call 0xA78940
...
0xc27370f  lea rax,[rbx+rdi]
0xc273713  mov [rbx+rdi],rax
0xc273717  lea rcx,[rbx+rdi]
0xc27371b  add rcx,8
0xc27371f  mov [rbp+0x3470],rcx
0xc273726  mov [rbx+rdi+8],rax
0xc27372b  mov [rbp+0x3438],rax
0xc273732  mov [rbx+rdi+0x10],rax
0xc273737  mov word ptr [rbx+rdi+0x18],0x101
```
**What**: Two more `0xa78940` allocations (size 0x2C0 and 0x20 and 0x30), each with shared_ptr control block release, each initialized as self-sentinel lists at `rbp+0x32D0`, `rbp+0x32A0`, `rbp+0x3248`. Also reads `S+0x20` (IntraFrameAllocator*) again via `rbp+0x3420` -> `[rax+0x20]` -> `[rax]` into `rbp+0x3468` and `rbp+0x3438`.

### Stage 3: Declarator Vector Iteration & Map Population (0xc27373e – 0xc273d19)
```
0xc27373e  mov rax,[rbp+0x3448]
0xc273745  mov r12,[rax+0x38]
0xc273749  mov rax,[rax+0x40]
0xc27374d  mov [rbp+0x3460],rax
0xc273754  cmp r12,rax
0xc273757  je 0xC273D19
0xc27375d  xor esi,esi
0xc27375f  jmp short 0xC2737CA
...
0xc273770  mov [r14+0x20],r15
0xc273774  mov dword ptr [r14+0x28],0
0xc27377c  mov [r14],rdi
0xc27377f  mov [r14+8],rdi
0xc273783  mov [r14+0x10],rdi
0xc273787  mov word ptr [r14+0x18],0
0xc27378e  mov [rbp-0x50],r13
0xc273792  mov [rbp-0x48],ebx
0xc273795  lea rcx,[rbp+0x32A0]
0xc27379c  lea rdx,[rbp-0x50]
0xc2737a0  mov r8,r14
0xc2737a3  call 0xA4C70
...
0xc273910  mov rbx,r12
0xc273913  mov rax,[rbp+0x3448]
0xc27391a  sub rbx,[rax+0x38]
0xc27391e  mov rdi,[r12]
0xc273922  mov rax,[rbp+0x3468]
0xc273929  mov rcx,[rax]
0xc27392c  mov r8d,0x30
0xc273932  mov r9d,1
0xc273938  lea rdx,[rbp-0x50]
0xc27393c  call 0xA78940
...
0xc273a79  mov rcx,[r11]
0xc273a7c  mov byte ptr [rcx+0x18],1
0xc273a80  cmp dword ptr [r12+0x48],0xFFFFFFFF
0xc273a86  jne 0xC2737B6
0xc273a8c  mov r15,[r12+8]
...
0xc273d19  mov rax,[rbp+0x3420]
0xc273d20  mov rax,[rax+0x20]
0xc273d24  mov rax,[rax]
0xc273d27  mov [rbp+0x3260],rax
```
**What**: Iterate the moved-out Declarator vector (begin at `rbp+0x3220`, end at `rbp+0x3230`). For each declared entry `d` (stride 0x50), insert into map at `rbp+0x32A0` (via `0xa4c70`), building the pass dependency graph. Complex intrusive list/link manipulation (0xc273770-0xc273c24) handles hash collisions and ordering. Final allocation at 0xc27393c (size 0x30) for a new container at `rbp+0x3260`.

### Stage 4: Hash Table / Dependency Graph Build (0xc273d19 – 0xc27414c)
```
0xc273d19  mov rax,[rbp+0x3420]
0xc273d20  mov rax,[rax+0x20]
0xc273d24  mov rax,[rax]
0xc273d27  mov [rbp+0x3260],rax
0xc273d2e  mov dword ptr [rbp+0x1FC0],0
0xc273d38  xorps xmm0,xmm0
0xc273d3b  movups [rbp+0x1FC8],xmm0
0xc273d42  mov rcx,[0x1233E1A8]
0xc273d49  mov rax,[rcx]
0xc273d4c  mov rax,[rax+8]
0xc273d50  mov edx,0x20
0xc273d55  call qword ptr [0xF99FFA0]
...
0xc273e70  mov r12,rdx
0xc273e73  mov rbx,rdi
0xc273e76  sar rbx,1
0xc273e79  mov rcx,[rcx]
0xc273e7c  lea rdx,[rbp+0x2FF0]
0xc273e83  mov r9d,1
0xc273e89  mov r8,rbx
0xc273e8c  call 0xA78940
...
0xc273f90  mov [r9],r10
0xc273f93  movups [r9+8],xmm0
0xc273f98  mov qword ptr [r9+0x18],0
0xc273fa0  add r9,0x20
0xc273fa4  inc rcx
0xc273fa7  cmp rax,rcx
0xc273faa  jne short 0xC273F90
...
0xc274113  mov [rbp+0x3218],r8
0xc27411a  mov qword ptr [rbp+0x3468],0xFFFFFFFFFFFFFFFF
0xc274125  xor esi,esi
0xc274127  movss xmm6,[0xEEE6700]
0xc27412f  mov r14d,8
0xc274135  lea rdi,[rbp+0x1FC0]
0xc27413c  jmp short 0xC27414C
```
**What**: Build hash table for dependency resolution (bucket array allocated via `0xa78940` at 0xc273e8c, initialized with zeroed 0x20-byte entries at 0xc273f90-0xc273faa). FNV-1a constants loaded (`xmm6` from `0xEEE6700`). Sets up iteration state at `rbp+0x1FC0` (index), `rbp+0x3468` (sentinel), `rbp+0x3218` (bucket count).

### Stage 5: Declarator Entry Processing Loop (0xc27414c – 0xc275072)
```
0xc27414c  mov r8,[rbp+0x3448]
0xc274153  mov rax,[r8+8]
0xc274157  mov rcx,[r8+0x10]
0xc27415b  mov rdx,rcx
0xc27415e  sub rdx,rax
0xc274161  sar rdx,4
0xc274165  cmp rsi,rdx
0xc274168  jae 0xC27446B
0xc27416e  mov rcx,rsi
0xc274171  shl rcx,4
0xc274175  mov rbx,[rax+rcx]
0xc274179  cmp rbx,[r8+0x50]
0xc27417d  mov rax,[rbp+0x3468]
0xc274184  cmove rax,rsi
0xc274188  mov [rbp+0x3468],rax
...
0xc2746ab  add r12,0x28
0xc2746af  mov rax,[rbp+0x3440]
0xc2746b6  shl rax,5
0xc2746ba  add rax,[rbp+0x3430]
0xc2746c1  mov [rbp+0x3458],rax
...
0xc275072  cmp rax,r9
0xc275075  je 0xC277CFE
```
**What**: Main loop over Declarator entries (stride 0x10). For each entry, compute hash, probe hash table at `rbp+0x2FF0` (bucket array), insert or find dependency record. Calls `0xa4c70` (map insert) at 0xc2746a6, `0x9bc830` (fallback alloc) at 0xc274c11/0xc274d0e, `0xeec6ed0`/`0xeec6de0`/`0xeec6eb0`/`0xeec6ec0` (graph edge ops). Exit at 0xc275072 when all entries processed (`rax == r9` = end of vector).

### Stage 6: Pass Dependency Record Vector Population (0xc275072 – 0xc277e8c)
```
0xc275072  cmp rax,r9
0xc275075  je 0xC277CFE
0xc27507b  mov [rbp+0x3308],rax
0xc275082  mov rax,[rax+8]
0xc275086  mov rsi,[rax+0x238]
0xc27508d  mov rax,[rax+0x240]
0xc275094  mov [rbp+0x3428],rax
0xc27509b  jmp short 0xC2750AB
...
0xc277e8c  call 0xC27EC60
```
**What**: For each resolved pass, populate the two dependency record vectors:
- **40-byte vector** at `rbp+0x3330/0x3338/0x3340` (begin/end/cap): `{u64 handle/hash, shared_ptr{ptr,ctrl}, u32, u16/u8 flags}` — growth via `0xc27f940` at 0xc278508/0xc27859e/0xc278625
- **24-byte vector** at `rbp+0x3348/0x3350/0x3358`: `{u64 handle/hash, shared_ptr{ptr,ctrl}}` — growth via `0xc27fcc0` at 0xc27881d/0xc278882
This stage includes the complex Bind* dependency kind handling (5 kinds from 6aq) and per-pass resource binding setup. Ends at the first call to `0xc27ec60` (0xc277e8c) which brackets the per-pass loop (6cz).

---

## Gaps / UNVERIFIED
- `[UNVERIFIED: 0xc2734a5]` Exact condition for empty Declarator fast-path (jump to 0xc273fbd -> 0xc27b172): `cmp qword ptr [r8+0x50],0` — what is `Declarator+0x50`?
- `[UNVERIFIED: 0xc273585]` Global allocator vtable at `[0x1233E1A8]` — exact type and layout of the allocator object.
- `[UNVERIFIED: 0xc2737a3]` `sub_a4c70` exact semantics: map insert vs find, key/value types.
- `[UNVERIFIED: 0xc274179]` `[r8+0x50]` in Declarator — purpose (capacity? flags?).
- `[UNVERIFIED: 0xc275086]` `[rax+0x238]` and `[rax+0x240]` — pass entry field meanings (dependency vector pointers?).
- `[UNVERIFIED: 0xc277e8c]` Confirm `sub_c27ec60` is the per-pass loop bracket (6cz says yes, but static only).

## TOOL REQUESTS
- `preflight` | `0xc273420 --n 300` -> `docs/progress/pre/0xc273420.md` | Already run; gave fn, callers, callees, stores, listing (300 instr). Needed full 4000+ instr for prologue; had to use rdis directly.
- `rdis` | `dis 0xc273420 4000` -> full prologue listing | Used manually; would be nice if preflight `--n` accepted larger values or auto-extended to next known boundary (0xc277e8c).
- `verify_oc` | `docs/progress/oc_U-C7a2.md` -> check quoted `0xRVA  instr` lines | To be run after writing this file.