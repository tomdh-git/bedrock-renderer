# oc_U-D8b-imgui — UI visitor tag 4 = UIImGui

## NEXT
Unit complete pending verify_oc.py run. File: docs/progress/oc_U-D8b-imgui.md

## Source
- Listing: docs/data/listings/ui_visitor_6664a00_6668510.txt (UI visitor 0x6664a00)
- Jump table: 0xF2BF468 (5 tags), decoded with `python tools/sigs/jt.py 0xF2BF468 5` [V]

## Jump table (decode) [V]
- tag 0 -> 0x6664a6c
- tag 1 -> 0x6664d51
- tag 2 -> 0x6664bd6
- tag 3 -> 0x6664c83
- tag 4 -> 0x6664aab   <- UIImGui (this unit)

`0xF2BF468` confirmed as the UI visitor jump table in docs/BGFX_MAP.md line 2052 [V].

## Visitor head [V]
```
0x6664a44  movzx eax,byte ptr [r8+8]      ; tag byte at [r8+8]
0x6664a49  cmp rax,4
0x6664a4d  ja 0x66682F3
0x6664a53  mov r14,rdx
0x6664a56  mov r13,rcx
0x6664a59  mov r9,[r8]                    ; r9 = description pointer (desc reg), loaded from [r8]
0x6664a5c  lea rcx,[0xF2BF468]
0x6664a63  movsxd rax,[rcx+rax*4]
0x6664a67  add rax,rcx
0x6664a6a  jmp rax                        ; indirect jump into tag case
```
- Desc register: **r9**, loaded from `[r8]` at `0x6664a59` [V] (matches tag-3 convention in oc_U-D5i.md: r9 = desc).
- Tag 4 case head: `0x6664aab` [V]

## Rebinding caveat (critical) [V]
`0x6664aab  mov [rbp+0x520],r9` saves desc to `[rbp+0x520]`.
At `0x6664f78  mov rax,[rbp+0x520]` / `0x6664f7f  mov r9,[rax]`, r9 is **rebound to `[desc+0x00]`** (a source object). Thereafter `[r9+off]` reads (0xf86 +0x80, 0x504b +0x78, 0x5794/57a2/57c2/57d0/5800/580d) read the **source object**, not the description — excluded from the description-read table below. Description is accessed after rebinding via `[rbp+0x520]` (rax/rcx/rdx) and via rsi at 0xc4e.

## Reachable-instruction cap
`python tools/sigs/casewalk.py docs/data/listings/ui_visitor_6664a00_6668510.txt 0x6664aab r9` -> `reachable=2054` > 600 cap. Listing description reads found (not exhaustive first-40; desc reads are few; source-object reads are numerous and excluded).

## Description READS in tag-4 case (desc base = [rbp+0x520] / rsi)

| Offset | Size | RVA | Instruction (quoted) | What the value is used for | Callee at first use | Tag |
|--------|------|-----|----------------------|----------------------------|---------------------|-----|
| +0x00 | 8 | 0x666510b | `0x666510b  mov r8,[rax]` (rax=[rbp+0x520]=desc) | desc+0x00 = source-object pointer; base for `[r8+0x28]` at 0x51ae | — (used as base) | [V] |
| +0x00 | 8 | 0x66651ab | `0x66651ab  mov r8,[rax]` | same as above (repeat use) | — | [V] |
| +0x00 | 8 | 0x6665249 | `0x6665249  mov r8,[rax]` | same as above (repeat use) | — | [V] |
| +0x00 | 8 | 0x6665298 | `0x6665298  mov r8,[rax]` | same as above (repeat use) | — | [V] |
| +0x00 | 8 | 0x66652f3 | `0x66652f3  mov r8,[rcx]` (rcx=[rbp+0x520]=desc) | same as above | — | [V] |
| +0x10 | 8 | 0x6665841 | `0x6665841  mov rdi,[rax+0x10]` | rdi passed as `rdx` arg to memcpy-like callee | `0xEEC6DE0` at `0x6665902  call 0xEEC6DE0` (rdx=rdi) | [V] |
| +0x18 | 8 | 0x66662f0 | `0x66662f0  mov rax,[rdx+0x18]` (rdx=[rbp+0x520]=desc) | high dword checked: `0x66662f7  shr rcx,0x20` / `0x66662fb  jne 0x66683B1` | — | [V] |
| +0x20 | 8 | 0x6666301 | `0x6666301  mov rdi,[rdx+0x20]` | first use not clearly a callee in reachable window | [UNVERIFIED: 0x6666301 what is rdi=desc+0x20 first passed to?] | [?] |
| +0x28 | 8 | 0x6666c74 | `0x6666c74  mov rax,[rsi+0x28]` (rsi=desc) | `rax*5` then `r15+rax*8` -> array element addr, stored [rbp+0x518] | [UNVERIFIED: 0x6666c74 callee at first use of desc+0x28-derived value] | [?] |
| +0x30 | 8 | 0x6666c78 | `0x6666c78  mov r15,[rsi+0x30]` (rsi=desc) | array base in `0x6666c80  lea rax,[r15+rax*8]` | [UNVERIFIED: 0x6666c78 callee at first use of desc+0x30] | [?] |
| +0x48 | 2 | 0x6665561 | `0x6665561  movzx esi,word ptr [rax+0x48]` (rax=[rbp+0x520]=desc) | first use / callee not traced within window | [UNVERIFIED: 0x6665561 callee at first use of desc+0x48] | [?] |

Address-only / non-value reads of desc (not counted as value reads):
- `0x6664aab  mov [rbp+0x520],r9` — stores desc pointer (write, not read)
- `0x6666c55  lea r9,[rsi+0x38]` — computes desc+0x38 address (address-only, not dereferenced)

## Source-object reads (EXCLUDED — r9 rebound to [desc+0x00])
`0x6664f86  movzx r8d,word ptr [r9+0x80]`, `0x666504b  mov rax,[r9+0x78]`, `0x6665794  movzx r10d,word ptr [r9+4]`, `0x66657a2  mov r10d,[r9]`, `0x66657c2  movzx r10d,word ptr [r9+0xA]`, `0x66657d0  mov r10d,[r9+6]`, `0x6665800  movzx ecx,word ptr [r9+4]`, `0x666580d  mov ecx,[r9]` — these read `[desc+0x00]` fields (source object), not the description itself.

## Open
- First-use callee for desc +0x20 (0x6666301), +0x28 (0x6666c74), +0x30 (0x6666c78), +0x48 (0x6665561) not traced within reachable window; marked [?]/[UNVERIFIED].
- Case reachable = 2054 instructions; full description-read enumeration not completed (cap applied).

## TOOL REQUESTS
None.
