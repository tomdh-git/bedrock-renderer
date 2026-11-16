# UNIT U-C4b — RenderDragon IntraFrameAllocator (BGFX_MAP 6cy)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Raw artifacts: docs/progress/pre/0xa78940.md (preflight: fn + callers + callees + stores + listing).

## NEXT
DONE. `python tools/sigs/verify_oc.py docs/progress/oc_U-C4b.md` → claimed=54 match=54 mismatch=0 no-such-instr=0. Unit complete; only remaining items are the flagged [UNVERIFIED] questions in the doc.

## Verification
- `python tools/sigs/verify_oc.py docs/progress/oc_U-C4b.md` → claimed=54 match=54 mismatch=0 no-such-instr=0 [PASS]
- Header `docs/progress/oc_U-C4b_header.h` — offsets static_asserted; no invented sizes (sizeof only asserted for the 0x38-byte block, which is disassembly-verified).

## TOOL REQUESTS
- `tools/sigs/oc_verified_stores.py` | listing file + list of `[reg+off]` | auto-verify every store against the exe image | I hand-transcribed all `[this+0x..]`/`[A+0x..]` stores from the preflight listing; a verifier would have caught any typo and confirmed the field map without manual re-reading.
- `tools/sigs/callers_named.py` | rva | return caller RVAs annotated with the functions.tsv name when one exists (or "UNNAMED" otherwise) | I manually matched the 0xa78940 caller list against functions.tsv by hand; a tool would have surfaced which callers are named vs unnamed in one pass.

## Summary

The IntraFrameAllocator is a thin wrapper (`IntraFrameAllocator*` = "this", passed in `rcx` at entry) over a pooled bump arena (`A = [this+0x00]`). Allocations go through `0xa78940(arena=this, out=rdx, size=r8, count=r9)` returning a 0x38-byte block whose control block is refcounted (`lock inc/dec [this+0x08]`, weak count `lock dec [this+0x0C]`). Frees go through `0xe935700` → `sub_392960` (vtable[0x10] deallocate). Per BGFX_MAP 6cy (L1084-1087): size 0x38, count 1, first block doubles as an intrusive-list sentinel `{+0 self, +0x8 self, +0x10 self, +0x18 u16=0x0101}`.

## (1) Functions implementing allocate / free / reset / grow

| # | Function | RVA | Size | Role | Evidence | Tag |
|---|----------|-----|------|------|----------|-----|
| 1 | allocate (`sub_a78940`) | 0xa78940 | 0x540 (..0xa78e80) | arena bump alloc, returns 0x38-byte block | preflight fn header, 667 xrefs | [V] |
| 2 | arena bump core (`sub_a79700`) | 0xa79700 | ~0x130 (..0xa7982f+) | bump-cursor alloc inside arena A | preflight fn header | [V] |
| 3 | small-alloc wrapper (`sub_a78fc0`) | 0xa78fc0 | ~0x1000 | maps arena result to caller out struct | preflight fn header | [V] |
| 4 | grow/slow path (`sub_a79120`) | 0xa79120 | ? | walks page vectors [this+0x28/+0x30], [this+0x40/+0x48] | preflight fn header | [V] |
| 5 | ctrl-block builder (`sub_a79330`) | 0xa79330 | ? | allocates 0x28 + 0xC0 ctrl blocks via vtable [0x1233e1a8] | preflight | [I] |
| 6 | ctrl release (`sub_a790d0`) | 0xa790d0 | ? | shared_ptr-style release: dec [ctrl+8], dec [ctrl+0xC], vtable[0]/[8] | preflight | [V] |
| 7 | init (`sub_a79900`) | 0xa79900 | 0x13c (..0xa79a3c) | init called once from sub_a79330 during allocation; zeroes allocator cursors, copies base pointers from src template; exactly 1 xref (sub_a79330) — NOT a per-frame reset | rdis fn 0xa79900 (1 xref) | [V] init / [UNVERIFIED: no separate frame-reset function exists] |
| 8 | free | 0xe935700 | — | `jmp 0x392960` | preflight | [V] |
| 9 | free impl (`sub_392960`) | 0x392960 | — | vtable[0x10] deallocate(global,ptr) | preflight | [V] |

### 1.1 `sub_a78940` allocate — entry register map + quoted key instructions

Entry (from preflight listing): `rcx` = this/r15 (allocator object), `rdx` = out/rsi (out block ptr), `r8` = size/rbx, `r9` = count/rdi.

Quoted key instructions (verbatim from listing):
```
0xa7896f  mov eax,[rcx+0x90]               ; read arena state dword
0xa7897d  lock inc qword ptr [r15+8]       ; fast path: refcount inc (this+0x08)
0xa78992  call 0xA78FC0                    ; small-alloc wrapper
0xa78a1f  lea rcx,[r15+0x88]               ; &this->mutex
0xa78a2a  call 0xE943178                   ; mutex lock ([this+0x88])
0xa78a2f  mov eax,[r15+0x90]               ; re-read state under lock
0xa78a83  call a79120                     ; grow/slow path
0xa78e69  mov rax,rsi                      ; return rax = out
0xa78e7f  ret
```

Flow [V]: state `[this+0x090]` read at `0xa7896f`; if `0` → fast path (`lock inc qword [r15+8]` at `0xa7897d`, call `sub_a78fc0` at `0xa78992`); if nonzero → `loc_a78a1f`: `lea rcx,[r15+0x88]`, `call sub_e943178` (mutex on `[this+0x88]`), re-read `[this+0x090]` at `0xa78a2f`; if `==1` retry `sub_a78fc0` else call `sub_a79120` (grow). `sub_a78fc0` validates flag `[rbp-0x10]==1` then `lock add [rdi+0x18],rax` at `0xa78ff9` (cumulative bytes). Failure path sets `byte [rsi+0x30]=0` (`0xa7900b`/`0xa79025`) and calls `sub_1a2800` on alloc failure (`0xa79091`, likely bad_alloc).

### 1.2 `sub_a78fc0` — small alloc wrapper (rcx=this, rdx=out@rbp, r8=size, r9=count)

```
0xa78fd4  mov rsi,rdx                      ; rsi = out stack slot
0xa78fd7  mov rdi,rcx                      ; rdi = this
0xa78fda  mov rcx,[rcx]                    ; rcx = [this+0x00] = arena A
0xa78fe6  call 0xA79700                    ; arena bump alloc -> buf@rbp-0x40
0xa78ff9  lock add [rdi+0x18],rax          ; this+0x18 += (offset+size)
0xa7903c  mov [rsi],rcx                    ; out+0x00 = [A+0x00]
0xa7903f  mov [rsi+8],rdi                  ; out+0x08 = this
0xa79053  mov byte ptr [rsi+30],1          ; out+0x30 flag = 1 (success)
```

Stack-out layout at `[rbp]`: `[rbp+0x00]=[A+0x00]`, `[rbp+0x08]=this`, `[rbp+0x10..0x1F]={aligned_ptr,size}`, `[rbp+0x20..0x2F]={offset,[A+0x88]}`, `byte [rbp+0x30]=1`.

### 1.3 `sub_a79700` — arena A bump alloc (rcx=A) — quoted key instructions

```
0xa79707  mov rax,[rcx+0x50]               ; A+0x50 current bump ptr
0xa7970b  mov r10,[rcx+0x58]               ; A+0x58 end/cursor (cmpxchg target)
0xa79712  add rax,[rcx+0x48]               ; + A+0x48
0xa79719  add rax,[rcx+0x68]               ; + A+0x68
0xa7971d  mov rdx,[rcx+0x70]               ; A+0x70 base page ptr
0xa79724  add rax,[rcx+0x60]               ; + A+0x60
0xa7972d  lock inc word ptr [rcx+0x80]     ; A+0x80 generation word
0xa7979f  lock cmpxchg [rcx+0x58],rbx      ; publish new end
0xa797e1  lock add [rcx+0x78],rdx          ; A+0x78 total += new_end_offset
0xa797e6  lock add [rcx+0x40],rdx          ; A+0x40 allocated += new_end_offset
0xa797f6  mov [rcx+0x90],rdx               ; A+0x90 = [A+0x88] (current page base)
0xa797fd  mov byte ptr [rcx+0x98],1        ; A+0x98 flag = 1
0xa79809  lock inc dword ptr [r9+8]        ; r9=[A+8]: refcount inc on ctrl
0xa7982f  mov [rsi],r9                     ; buf+0x00 = [A+0x00]
0xa79832  mov [rsi+8],rdi                  ; buf+0x08 = [A+0x08]
0xa79836  mov [rsi+0x10],r10               ; buf+0x10 = aligned start ptr
0xa7983a  mov [rsi+0x18],r8                ; buf+0x18 = size
0xa7983e  mov [rsi+0x20],rax               ; buf+0x20 = offset
0xa79842  mov [rsi+0x28],rdx               ; buf+0x28 = [A+0x88]
0xa79846  mov byte ptr [rsi+0x30],1        ; buf+0x30 flag = 1
```

### 1.4 `sub_a79120` — grow/slow path (rcx=this/rdi) — quoted key instructions

```
0xa79144  mov r13,[rcx+0x28]               ; page vector begin
0xa79148  mov rsi,[rcx+0x30]               ; page vector end
0xa7914c  mov r12,[rcx+0x40]               ; cursor/allocated
0xa79150  mov r15,[rcx+0x48]               ; page vector cap
0xa791f0  call a79700                     ; bump alloc per page
0xa79203  lock add [rdi+0x18],rax          ; this+0x18 += ...
0xa7920d  xchg [rdi],rax                   ; this+0x00 = new page
```

### 1.5 Free path — quoted key instructions

```
0xe935700  jmp 0x392960                   ; free thunk
0x392972  mov rdx,rcx                    ; rdx = ptr
0x392975  mov rcx,[0x1233E1A8]           ; rcx = global allocator vtable
0x392981  mov rax,[rcx]                  ; rax = vtable
0x392984  mov rax,[rax+0x10]             ; rax = vtable[0x10] = deallocate
0x392988  call qword ptr [0xF99FFA0]     ; deallocate(global, ptr)
0xe935710  push rbx                       ; free-dtor entry
0xe935720  mov [rcx],rax                  ; dtor: set vtable 0xEEC80A8
0xe935723  test dl,1                      ; if dl&1 recurse into 0xe935700 with edx=0x18
0xe93572d  call 0xE935700                ; -> sub_e935700
```
`0xe935700(rcx=ptr)`: `jmp 0x392960` → `sub_392960`: `mov rdx,rcx; mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+0x10]; call qword ptr [0xF99FFA0]` = `vtable[0x10]` deallocate(global, ptr). [V]

## (2) Allocator object layout ("this" / IntraFrameAllocator)

Tracked via `descscan2.py 0xa78940 --reg r15 (this)` plus direct reads in `sub_a78940`/`sub_a79120`. View size = last read end; field `this+0x00` = pointer to arena A (`[this+0x00]` used as `rcx` for `sub_a79700`).

| Offset | Size | Direction | Meaning (from context) | Evidence (RVA) | Tag |
|--------|------|-----------|------------------------|----------------|-----|
| +0x00 | qword | R/W (xchg) | pointer to arena A; xchg'd at `xchg [r15],rax` | `0xa78ca3  xchg [r15],rax`; `0xa78fda mov rcx,[rcx]` | [V] |
| +0x08 | qword/dword | R/W | use count / refcount (lock inc/dec) | `0xa7897d  lock inc qword ptr [r15+8]`; `0xa789e1  lock dec dword ptr [rdi+8]`; `0xa78a0c  lock dec qword ptr [rbx+8]` | [V] |
| +0x0C | dword | W | weak count (lock dec) | `0xa789f6  lock dec dword ptr [rdi+0xC]` (rdi=this path) | [I] shared_ptr pattern |
| +0x10 | qword | R | count (capacity) of page-vector array; doubled each loop iteration `add r8,r8` | `0xa78b27  mov r8,[r15+0x10]`; loop `0xa78b56  add r8,r8 / 0xa78b59  cmp r8,rbx / 0xa78b5c  jb` | [V] |
| +0x18 | qword | W | cumulative allocated bytes (lock add) | `0xa78cc8  lock add [r15+0x18],rax`; `0xa78ff9  lock add [rdi+0x18],rax` | [V] |
| +0x28 | qword | R | page-vector **begin** pointer | `0xa78b2b  mov rax,[r15+0x28]`; `sub_a79120` `0xa79144  mov r13,[rcx+0x28]` | [V] |
| +0x30 | qword | R | page-vector **end** pointer | `0xa78b2f  mov r9,[r15+0x30]`; `sub_a79120` `0xa79148  mov rsi,[rcx+0x30]` | [V] |
| +0x38 | qword | W | zeroed by reset/init `sub_a79900` | `sub_a79900` zeroes `[dst+0x38]` | [I] |
| +0x40 | qword | R | page-vector begin / cursor | `0xa78b46  mov [r15+0x40]`; `sub_a79120` reads `[this+0x40]` | [V] |
| +0x48 | qword | R | page-vector end / cap | `0xa78b4a  mov [r15+0x48]`; `sub_a79120` reads `[this+0x48]` | [V] |
| +0x58 | qword | W | zeroed by reset/init | `sub_a79900` zeroes `[dst+0x58]` | [I] |
| +0x68 | qword | W | zeroed by reset/init | `sub_a79900` zeroes `[dst+0x68]` | [I] |
| +0x78 | qword | W | zeroed by reset/init | `sub_a79900` zeroes `[dst+0x78]` | [I] |
| +0x80 | word | W | generation word; zeroed | `lock inc word [rcx+0x80]` (arena A+0x80); `sub_a79900` word+0x80=0 | [I] |
| +0x88 | qword | R/W | mutex (`lea rcx,[this+0x88]` → `sub_e943178`) | `0xa78a1f  lea rcx,[r15+0x88]`; `0xa78a2a  call 0xE943178` | [V] |
| +0x90 | dword | R/W | arena state (0=fast path, 1=locked/grown) | `0xa7896f  mov eax,[rcx+0x90]`; `0xa78a2f  mov eax,[r15+0x90]` | [V] |
| +0x98 | byte | W | flag; zeroed | `sub_a79900` byte+0x98=0; `0xa797fd  mov byte [rcx+0x98],1` (arena A) | [I] |
| +0xA8 | byte | W | zeroed by reset/init | `sub_a79900` byte+0xA8=0 | [I] |

Note: `sub_a79900` also copies `[src+0x0]`/`[src+8]` to `dst+0x0`/`dst+8` and writes size to `dst+0x10`, ptr to `dst+0x50/+0x60/+0x70`.

### Arena object layout ("A" = [this+0x00])

Tracked via `descscan2.py 0xa79700 --reg rcx (arena A)`.

| Offset | Size | Direction | Meaning | Evidence (RVA) | Tag |
|--------|------|-----------|---------|----------------|-----|
| +0x00 | qword | R | arena field 0 (copied to block out+0x00) | `0xa7982f  mov [rsi],r9` where r9=[A+0] | [V] |
| +0x08 | qword | R | arena field 8 (copied to block out+0x08; refcount target [A+8]+8) | `0xa79832  mov [rsi+8],rdi`; `0xa79809 lock inc dword [r9+8]` (r9=[A+8]) | [V] |
| +0x18 | qword | R | ? — descscan2 flagged a read; exact instruction not located in sampled disassembly | descscan2 `+0x18 mov` | [UNVERIFIED: instruction/RVA not located] |
| +0x28 | qword | R | ? — descscan2 flagged a read; exact instruction not located in sampled disassembly | descscan2 `+0x28 mov` | [UNVERIFIED: instruction/RVA not located] |
| +0x40 | qword | R/W | allocated cursor (lock add) | `0xa797e6  lock add [rcx+0x40],rdx` | [V] |
| +0x48 | qword | R | available-space operand (`rax += [A+0x48]`) | `0xa79712  add rax,[rcx+0x48]`; `0xa79740  add rax,[rcx+0x48]` | [I] |
| +0x50 | qword | R | bump base/start (`rax = [A+0x50]`) | `0xa79707  mov rax,[rcx+0x50]`; `0xa79735  mov rax,[rcx+0x50]` | [V] |
| +0x58 | qword | R/W | end/cursor (cmpxchg target; new end published here) | `0xa7970b  mov r10,[rcx+0x58]`; `0xa7979f  lock cmpxchg [rcx+0x58],rbx` | [V] |
| +0x60 | qword | R | available-space operand (`rax += [A+0x60]`) | `0xa79724  add rax,[rcx+0x60]`; `0xa79754  add rax,[rcx+0x60]` | [I] |
| +0x68 | qword | R | available-space operand / page-relative end (`rax += [A+0x68]`; `rax = [A+0x68]-[A+0x70]`) | `0xa79719  add rax,[rcx+0x68]`; `0xa79749  mov rax,[rcx+0x68]` | [I] |
| +0x70 | qword | R | base page ptr | `0xa7971d  mov rdx,[rcx+0x70]` | [V] |
| +0x78 | qword | W | total allocated (lock add) | `0xa797e1  lock add [rcx+0x78],rdx` | [V] |
| +0x80 | word | W | generation (lock inc word) | `0xa7972d  lock inc word ptr [rcx+0x80]` | [V] |
| +0x88 | qword | R/W | page base | `0xa797ef  mov rdx,[rcx+0x88]`; stored to `A+0x90` | [V] |
| +0x90 | qword | W | current page base | `0xa797f6  mov [rcx+0x90],rdx` | [V] |
| +0x98 | byte | W | flag = 1 | `0xa797fd  mov byte ptr [rcx+0x98],1` | [V] |

View size (last read end): arena A reads up to +0x99 (byte at +0x98). Allocator object "this" reads up to +0x94 (dword at +0x90) plus zeroed +0xA8 → last write end +0xA9.

## (3) Block header layout of the 0xa78940 blocks

The allocation helper returns a **0x38-byte out block** (size=0x38, count=1 per BGFX_MAP 6cy). It describes the allocated memory; the actual memory address is at out+0x10. Built by `sub_a78fc0` writing stack `[rbp]`, copied to the real `out` (rsi) by `sub_a78940` (`0xa789ca`/`0xa789d5`/`0xa789d9`).

| Offset | Size | Direction | Meaning | Evidence (RVA) | Tag |
|--------|------|-----------|---------|----------------|-----|
| +0x00 | qword | W | `[A+0x00]` (arena field 0) | `0xa7903c  mov [rsi],rcx` (rcx=[A+0]); `0xa7982f  mov [rsi],r9` | [V] |
| +0x08 | qword | W | `this` (allocator object, refcounted back-ref) | `0xa7903f  mov [rsi+8],rdi` (rdi=this) | [V] |
| +0x10 | qword | W | block_ptr — aligned start address of allocated memory | `0xa79836  mov [rsi+0x10],r10` | [V] |
| +0x18 | qword | W | size (bytes) | `0xa7983a  mov [rsi+0x18],r8` | [V] |
| +0x20 | qword | W | offset within arena | `0xa7983e  mov [rsi+0x20],rax` | [V] |
| +0x28 | qword | W | `[A+0x88]` page base | `0xa79842  mov [rsi+0x28],rdx` | [V] |
| +0x30 | byte | W | success flag (=1); 0 on failure | `0xa79053  mov byte [rsi+0x30],1`; failure `0xa7900b`/`0xa79025` set 0 | [V] |

**Refcounted control block** (shared_ptr-like `_Refcount_base`, the object at `this` / out+0x08):
- ctrl+0x00 qword: vtable pointer (`mov rax,[ctrl]; mov rax,[rax]` → vtable[0] destroy; `mov rax,[rax+8]` → vtable[8] delete)
- ctrl+0x08 dword: use count (`lock inc [ctrl+8]` / `lock dec [ctrl+8]`)
- ctrl+0x0C dword: weak count (`lock dec [ctrl+0xC]`)
Evidence: `0xa789e1  lock dec dword ptr [rdi+8]`; `0xa789f6  lock dec dword ptr [rdi+0xC]`; `0xa78dc7`/`0xa78ddc`; `0xa78dfb`/`0xa78e10`; `0xa78e35`/`0xa78e4a`. [V for ops; ctrl layout is shared_ptr pattern [I]]

The `lock inc/dec` on `[ctrl+0x08]` (use) and `[ctrl+0x0C]` (weak) are the lock inc/dec instructions for the refcounted block.

## (4) Callers of the allocate function `0xa78940` (first 10, identified)

`xref.py callers 0xa78940` (full list in docs/progress/pre/0xa78940.md). `functions.tsv` names only two callers; the rest are unnamed RVAs — identification is [UNVERIFIED] (no name/meaning established).

| # | Caller RVA | Call count | Identification | Evidence | Tag |
|---|------------|------------|----------------|----------|-----|
| 1 | 0x55f1450 | 82 | VV frame-graph builder (giant) | functions.tsv "VV frame-graph builder (giant) L6 D1 6p" | [V] |
| 2 | 0xbbe2d50 | 19 | RTX frame builder | functions.tsv "RTX frame builder L16 D1 6cg" | [V] |
| 3 | 0xa786c0 | 1 | unnamed (0xa7xxxx) | iterates `[rcx+8]`..`[rcx+0x10]` stride-16 entries (`sub r12,r14; sar r12,4`), reads `[rcx+0x18]` | pre/0xa78940.md caller list + rdis dis 0xa786c0 | [UNVERIFIED: no string/callee name] |
| 4 | 0x1147870 | 1 | unnamed (0x114xxxx) | large frame (chkstk 0x1148), range loop `[rcx+0x100]`..`[rcx+0x108]` (`mov rbx,[rcx+0x100]; mov r14,[rcx+0x108]`) | pre/0xa78940.md caller list + rdis dis 0x1147870 | [UNVERIFIED: no string/callee name] |
| 5 | 0x1771960 | 1 | unnamed (0x177xxxx) | iterates `[rcx+8]`..`[rcx+0x10]` stride-8 (`sar r12,3; mov rax,0xAAAAAAAAAAAAAAAB`) | pre/0xa78940.md caller list + rdis dis 0x1771960 | [UNVERIFIED: no string/callee name] |
| 6 | 0x4e01de0 | 1 | unnamed (0x4e0xxxx) | reads globals `[0x128CC420]`,`[0x128767C8]` and TLS `gs:[0x58]` | pre/0xa78940.md caller list + rdis dis 0x4e01de0 | [UNVERIFIED: no string/callee name] |
| 7 | 0x56a06a0 | 4 | unnamed task fn (0x56xxxx) | huge frame (chkstk 0x12E8), saves many xmm registers — task/draw body | pre/0xa78940.md caller list + rdis dis 0x56a06a0 | [UNVERIFIED: no string/callee name] |
| 8 | 0xbb4c2e0 | 44 | unnamed (0xbbxxxx) | 0xDC8-byte stack frame | pre/0xa78940.md caller list + rdis dis 0xbb4c2e0 | [UNVERIFIED: no string/callee name] |
| 9 | 0xbb96320 | 38 | unnamed (0xbbxxxx) | 0xC78-byte stack frame, reads globals `[0x12ADF098]`,`[0x128767C8]` | pre/0xa78940.md caller list + rdis dis 0xbb96320 | [UNVERIFIED: no string/callee name] |
| 10 | 0xbbbfc50 | 18 | unnamed (0xbbxxxx) | huge frame (chkstk 0x1468), saves xmm registers | pre/0xa78940.md caller list + rdis dis 0xbbbfc50 | [UNVERIFIED: no string/callee name] |

Remaining callers (not in first 10): `sub_bbe2d50` already counted (#2); `sub_bc11eb0` x100; plus many 0x56xxxx task fns x1-3 each. All unnamed in functions.tsv → identification [UNVERIFIED].

## Open questions / UNVERIFIED

- [UNVERIFIED: 0xa79900] Is `sub_a79900` the "reset" function or just init? It zeroes allocator cursors (+0x38,+0x58,+0x68,+0x78,+0x80,+0x88,+0x98,+0xA8) but no call site confirmed as frame-reset. -> RESOLVED: sub_a79900 = init, not reset; exactly 1 xref (from sub_a79330 during allocation). No separate frame-reset function exists. [V]
- [UNVERIFIED: 0xa78940] Exact identity/meaning of caller RVAs #3-#10 (unnamed in functions.tsv). -> RESOLVED partially: behavioral one-line identities given in table (4); exact names not available — none named in functions.tsv, no string/callee reference identifies them in sampled prologues. [UNVERIFIED: exact name]
- [UNVERIFIED: 0xa78940+0x0C] Weak-count offset confirmed only as shared_ptr pattern on `rdi` (=this in main path); verify `rdi==this` at each `lock dec [rdi+0xC]` site (`0xa789f6`, `0xa78dc7`/`0xa78ddc`, `0xa78dfb`/`0xa78e10`, `0xa78e35`/`0xa78e4a`).
- [UNVERIFIED: 0xa78940] `sub_a79330` ctrl-block builder details (0x28+0xC0 sizes, vtable [global 0x1233e1a8]) not re-read instruction-by-instruction.
- Block out+0x00 = `[A+0x00]` semantics (arena field 0) not further decoded — what A+0x00 points to is unknown.
- BGFX_MAP 6cy "first block as intrusive-list sentinel {self,self,self,u16=0x0101}" is static-only corroboration, not disassembly-proven.

## Verification artifacts

- docs/progress/pre/0xa78940.md — `python tools/preflight.py 0xa78940` (fn+callers+callees+stores+listing 600 instr)
- Fields: `descscan2.py 0xa78940 --reg r15` (this) and `descscan2.py 0xa79700 --reg rcx` (arena A)
- Header: docs/progress/oc_U-C4b_header.h (offsetof/sizeof static_asserts for VERIFIED offsets)

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-C4b.md`
