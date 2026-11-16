# oc_U-D8b-imgui2 — UI visitor tag 4 = UIImGui: desc read verification (finish of oc_U-D8b-imgui)

## NEXT
Unit DONE: all four first-use questions resolved; verify_oc.py: 46/46 match (see below).

## Source
- Listing: docs/data/listings/ui_visitor_6664a00_6668510.txt (UI visitor 0x6664a00) [V]
- Tag-4 case head: 0x6664aab; desc base = [rbp+0x520], saved there by `0x6664aab  mov [rbp+0x520],r9` [V]
- Rebinding caveat: at `0x6664f7f  mov r9,[rax]` r9 is rebound to [desc+0x00] (a source object); thereafter [r9+off] reads the source object, not the desc. Desc reads after rebinding use [rbp+0x520] or rsi (=desc) [V] (see oc_U-D8b-imgui.md lines 35-37, not proof, consistent here).

Tags: [V] = seen in the disassembly (RVA cited), [I] = inferred (source stated), [?] = unknown.

## 1) desc +0x20 (qword) — read at 0x6666301

Quoted disassembly forward from the read (rdis, exe per brief rule 4):
```
0x6666301  mov rdi,[rdx+0x20]            ; rdi = desc+0x20 (rdx = desc = [rbp+0x520])
0x6666324  test rax,rax                  ; rax = length (loaded before the read window)
0x6666327  je 0x66663CE                  ; length==0 -> copy skipped entirely
0x66663b2  mov rcx,r12                   ; rcx = dst = sub_eea6040 allocation result
0x66663b5  mov rdx,rdi                   ; rdx = src = desc+0x20 (rdi untouched since 0x6666301)
0x66663b8  mov r8,r15                    ; r8 = n = rax*2 bytes
0x66663bb  call 0xEEC6DE0                ; memcpy-like(dst rcx, src rdx, n r8)
```

Verified use: desc+0x20 is passed as **rdx (2nd argument = source pointer)** to `call 0xEEC6DE0` at **0x66663bb** [V]. Destination rcx = r12, the result of the sub_eea6040 allocation via [0xF99FFA0] (rcx=[0x1233E1A8]->[rax+8], rdx=size) seen at 0x6666351/0x666638a with r12=rax at 0x6666358/0x6666391 [V]. Size r8 = r15 = rax*2 bytes [V at 0x66663b8]. The copy is conditional: `test rax,rax / je 0x66663CE` at 0x6666324/327 skips it when length==0 [V]. rdi is not clobbered between 0x6666301 and 0x66663b5 [V]. Callee sub_eec6de0 = memcpy-like (rcx=dst, rdx=src, r8=n) per docs/functions/67417f0.md line 163 and docs/progress/oc_U-PASS4B.md line 1318 [I via docs]. Suggested field name: **`copySrcB` [I]** (pointer to a `rax*2`-byte source buffer copied by memcpy).

## 2) desc +0x28 (qword) — read at 0x6666c74, and desc +0x30 (qword) — read at 0x6666c78

Quoted disassembly forward from the reads (the two reads are adjacent, one computation):
```
0x6666c74  mov rax,[rsi+0x28]            ; rax = desc+0x28 (rsi = desc)
0x6666c78  mov r15,[rsi+0x30]            ; r15 = desc+0x30 (array base)
0x6666c7c  lea rax,[rax+rax*4]           ; rax = desc+0x28 * 5
0x6666c80  lea rax,[r15+rax*8]           ; rax = base + desc+0x28 * 40  (array end)
0x6666c84  mov [rbp+0x518],rax           ; store end pointer in stack local [rbp+0x518]
0x6666c8b  lea rdi,[rbp+0x1E2]
0x6666c92  lea rbx,[rbp+0x58]
0x6666c96  xorps xmm6,xmm6
0x6666c99  mov [rbp+0x28],r14
0x6666c9d  mov [rbp+0x1D8],r13
0x6666ca4  jmp short 0x6666CBF           ; -> loop head
loc_6666cb0:
0x6666cb0  add r15,0x28                  ; advance element pointer by 0x28 = 40 bytes
0x6666cb4  lea rdi,[rbp+0x1E2]
0x6666cbb  lea rbx,[rbp+0x58]
loc_6666cbf:
0x6666cbf  cmp r15,[rbp+0x518]           ; compare cursor vs end
0x6666cc6  je 0x66678C7                  ; exit loop when equal
0x6666ccc  movups xmm7,[r15]             ; read element[0x00..0x0F]
0x6666cd0  mov eax,[r15+0x10]            ; read element+0x10
0x6666cd4  mov ecx,[r15+0x14]            ; read element+0x14
0x6666cd8  movaps [rbp+0x4E0],xmm6
0x6666cdf  mov rdx,[rbp+0x188]
...
loc_6666d42:
0x6666d42  mov r8,[rbp+0x170]
0x6666d49  mov [rbp+0x30],r8
0x6666d4d  mov [rbp+0x38],rdx
0x6666d51  mov rdx,[r14]
0x6666d54  mov [rsp+0x30],eax            ; element+0x10 -> stack arg
0x6666d58  mov [rsp+0x28],rcx            ; element+0x14 -> stack arg
0x6666d5d  mov [rsp+0x20],r12
0x6666d62  lea rcx,[rbp+0x3A0]
0x6666d69  lea r8,[rbp+0x30]
0x6666d6d  lea r9,[rbp+0x4E0]
0x6666d74  call 0x66B2730                ; sub_66b2730 per element
...
0x6666dd8  lea r8,[r15+0x18]             ; element+0x18 address materialized
0x6666ddc  sub ecx,eax
0x6666dde  shr ecx,4                     ; /16
0x6666de1  imul eax,ecx,0xFFFFAAAB
0x6666de7  mov [rbp+0x400],ax            ; element-derived index
...
0x6666e19  call 0xBCABA00                ; rdx = [rbp+0x400] (element-derived)
```

Verified use:
- desc+0x28 = element **count** [V read at 0x6666c74; count*5 at 0x6666c7c; *8 byte scale at 0x6666c80]. Array end = base + count*5*8 = base + count*40 bytes, stored into stack local **[rbp+0x518]** at 0x6666c84 [V].
- desc+0x30 = array **base pointer**, loaded into r15 at 0x6666c78 and used as the loop cursor [V].
- Loop: head `cmp r15,[rbp+0x518] / je 0x66678C7` at 0x6666cbf/cc6 [V]; per-iteration step `add r15,0x28` at 0x6666cb0 [V] → **element size = 0x28 (40) bytes = 5 qwords** [V]; with end = base + count*40, the loop iterates exactly count elements.
- Per element, fields read: [r15] (movups, +0x00..0x0F) at 0x6666ccc, [r15+0x10] at 0x6666cd0, [r15+0x14] at 0x6666cd4 [V]; element+0x10 → [rsp+0x30] at 0x6666d54, element+0x14 → [rsp+0x28] at 0x6666d58 (stack args to the per-element callee) [V]; element+0x18 address materialized at 0x6666dd8 and reduced by /16 to [rbp+0x400] (0x6666de7).
- Per-element callees inside the iteration: **`call 0x66B2730` at 0x6666d74** (rcx=[rbp+0x3A0], r8=[rbp+0x30], r9=[rbp+0x4E0], plus stack args incl. element+0x10/+0x14) [V] and **`call 0xBCABA00` at 0x6666e19** with rdx = element-derived index [V]. Callee IDs: sub_66b2730 = terrain/chunk draw builder (docs/data/frame_path_functions.tsv; also listed as called by 0x6664a00, this visitor, in docs/data/inventory_L4L5_builder.tsv) [I via docs]; sub_bcaba00 = Item group visitor (bgfx) per docs/data/frame_path_functions.tsv [I via docs].
- The array is iterated for **per-element draw/item setup feeding sub_66b2730 and sub_bcaba00** [V mechanism]; the higher-level purpose of the iteration is not determined in the window [?].

Suggested field names: desc+0x28 **`elemCount` [I]**, desc+0x30 **`elemArray` [I]**.

## 3) desc +0x48 (word) — read at 0x6665561

Quoted disassembly forward from the read (250 instructions, 6× the requested window):
```
0x6665561  movzx esi,word ptr [rax+0x48]   ; esi = desc+0x48 (rax = desc)
```
(calls later in the window: sub_eea6040 at 0x66655c7/0x66655dd/0x6665898/0x66658d1/0x66659a2..., sub_66a0f60 at 0x6665615, sub_e869ff0 at 0x666563a, sub_eec6de0 at 0x6665902, sub_eec6e70 at 0x66659a2, sub_eec7570 at 0x66659b7 — none takes esi as an argument)

Verified (negative): esi is **defined once (0x6665561) and never read again** within 250 instructions; it is not passed to any callee, never stored to memory, never compared or branched on [V]. First use of desc+0x48 is beyond the window → **unknown [?]**. No field name suggested (meaning not clear); value purpose **[?]**.

## Verified description-read table (tag-4 case, desc base = [rbp+0x520])

| Offset | Size | RVA | Instruction (quoted) | Verified use / destination of loaded value | Suggested field name | Tag |
|--------|------|-----|----------------------|--------------------------------------------|----------------------|-----|
| +0x00 | 8 | 0x666510b | `0x666510b  mov r8,[rax]` (rax = desc = [rbp+0x520]) | Source-object pointer; base for `[r8+0x28]` at 0x66651ae; used as base, not passed to a callee in window | `srcObj` [I] | [V] |
| +0x10 | 8 | 0x6665841 | `0x6665841  mov rdi,[rax+0x10]` | rdi passed as rdx (src) arg to `0x6665902  call 0xEEC6DE0` (memcpy-like, docs/functions/67417f0.md) | `copySrcA` [I] | [V] |
| +0x18 | 8 | 0x66662f0 | `0x66662f0  mov rax,[rdx+0x18]` then `0x66662f7  shr rcx,0x20` / `0x66662fb  jne 0x66683B1` | Compare/branch: high dword of desc+0x18 must be 0 (jne exits on nonzero) | — | [V] |
| +0x20 | 8 | 0x6666301 | `0x6666301  mov rdi,[rdx+0x20]` | rdx (src, 2nd arg) of `0x66663bb  call 0xEEC6DE0` (memcpy-like), dst=r12 alloc result, size=rax*2; skipped when length==0 via `0x6666324  test rax,rax` / `0x6666327  je 0x66663CE` | `copySrcB` [I] | [V] |
| +0x28 | 8 | 0x6666c74 | `0x6666c74  mov rax,[rsi+0x28]` | Element count: `0x6666c7c  lea rax,[rax+rax*4]` (*5), end = base+count*40 stored at `[rbp+0x518]` by `0x6666c84  mov [rbp+0x518],rax` | `elemCount` [I] | [V] |
| +0x30 | 8 | 0x6666c78 | `0x6666c78  mov r15,[rsi+0x30]` | Array base (loop cursor); `0x6666cbf  cmp r15,[rbp+0x518]` / `0x6666cc6  je 0x66678C7` exit, step `0x6666cb0  add r15,0x28`; per element: `0x6666ccc  movups xmm7,[r15]`, `0x6666cd0  mov eax,[r15+0x10]`, `0x6666cd4  mov ecx,[r15+0x14]`, `0x6666dd8  lea r8,[r15+0x18]`; feeds `0x6666d74  call 0x66B2730` and `0x6666e19  call 0xBCABA00` | `elemArray` [I] | [V] |
| +0x48 | 2 | 0x6665561 | `0x6665561  movzx esi,word ptr [rax+0x48]` | esi never consumed: no callee argument, no store, no compare/branch within 250 instructions; first use unknown | — | [?] |

Element size / iteration meaning for +0x28/+0x30: element size **0x28 (40) bytes** [V from `add r15,0x28` stride and end = base + count*40]; desc+0x28 is the element **count** [I]. Iterated for per-element setup: element+0x10/+0x14 passed as stack args to sub_66b2730 at 0x6666d74; element+0x18 reduced by /16 and passed as rdx to sub_bcaba00 at 0x6666e19 [V]. Higher-level iteration purpose not determined in window [?].

## Open
- desc +0x48 first use: not visible within 250 instructions of the read; esi is dead in that window [?]. Beyond unit scope.

## TOOL REQUESTS
None.
