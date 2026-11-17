## NEXT
DONE

# BlockSelectionOverlay extractor 0x66E75F0 (tag 0): description reads via rdi

Description pointer: rdi (second argument r8 copied at entry, `0x66e7634  mov rdi,r8`).
One row per distinct [rdi+off] offset; read address column lists every site of that offset in the input data (comma-separated); verbatim line is the first site; size from the first instruction. '-' = no meaning shown by any instruction/string.

## tag 0
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x00 | 16 | 0x66e845a, 0x66e8537, 0x66e87cd, 0x66e8a3b | `0x66e845a  movups xmm0,[rdi]` | - |
| 0x08 | 8 | 0x66e891f, 0x66e8e7d | `0x66e891f  mov rsi,[rdi+8]` | - |
| 0x10 | 16 | 0x66e8464, 0x66e8541, 0x66e87d7, 0x66e8a45 | `0x66e8464  movups xmm0,[rdi+0x10]` | - |
| 0x18 | 1 | 0x66e8919, 0x66e8e77 | `0x66e8919  cmp byte ptr [rdi+0x18],2` | - |
| 0x20 | 16 | 0x66e846f, 0x66e854c, 0x66e87e2, 0x66e8a50 | `0x66e846f  movups xmm0,[rdi+0x20]` | - |
| 0x30 | 8 | 0x66e8128, 0x66e847a, 0x66e8559, 0x66e87ed, 0x66e8a5b | `0x66e8128  movsd xmm7,[rdi+0x30]` | - |
| 0x38 | 4 | 0x66e8123 | `0x66e8123  movss xmm6,[rdi+0x38]` | - |
| 0x40 | 8 | 0x66e7648, 0x66e7e7a, 0x66e7eba, 0x66e80d7, 0x66e8100 | `0x66e7648  mov rax,[rdi+0x40]` | - |
| 0x48 | 4 | 0x66e7ebe | `0x66e7ebe  mov eax,[rdi+0x48]` | - |
| 0x50 | 8 | 0x66e7d0a | `0x66e7d0a  mov rax,[rdi+0x50]` | - |
| 0x58 | 8 | 0x66e7d18 | `0x66e7d18  mov rcx,[rdi+0x58]` | - |
| 0x60 | - | 0x66e7b2d, 0x66e7ffd | `0x66e7b2d  lea r8,[rdi+0x60]` | - |
| 0x70 | 8 | 0x66e778c, 0x66e80fc | `0x66e778c  mov rax,[rdi+0x70]` | - |
| 0x80 | 16 | 0x66e7df2, 0x66e8041 | `0x66e7df2  movups xmm0,[rdi+0x80]` | - |
| 0x90 | 2 | 0x66e844c, 0x66e852f, 0x66e87bf, 0x66e8a2d | `0x66e844c  movzx eax,word ptr [rdi+0x90]` | - |
| 0x98 | 4 | 0x66e8144, 0x66e8390 | `0x66e8144  mov r12d,[rdi+0x98]` | - |
| 0x9C | 4 | 0x66e814b, 0x66e8397 | `0x66e814b  mov r13d,[rdi+0x9C]` | - |
| 0xA0 | 8 | 0x66e8756, 0x66e89c1 | `0x66e8756  mov r8,[rdi+0xA0]` | - |
| 0xA8 | 8 | 0x66e872d, 0x66e873d, 0x66e8998, 0x66e89a8 | `0x66e872d  mov rcx,[rdi+0xA8]` | - |
| 0xB0 | 1 | 0x66e7666, 0x66e77a4, 0x66e8137, 0x66e8383 | `0x66e7666  movzx r12d,byte ptr [rdi+0xB0]` | - |

Note on 0x30: offset 0x30 is read both as `movsd` (8) at 0x66e8128 and as part of `movups` (16) at 0x66e847a/0x66e8559/0x66e87ed/0x66e8a5b; row size is from the first instruction.
Note on 0x70: offset 0x70 is read as `mov rax` (8) at 0x66e778c and address-taken via `lea rdx` at 0x66e80fc.
Note on 0x60: only `lea` (address taken), no sized load — size column '-'.

Verbatim first-instruction lines for the check tool (one per distinct offset):

0x66e845a  movups xmm0,[rdi]
0x66e891f  mov rsi,[rdi+8]
0x66e8464  movups xmm0,[rdi+0x10]
0x66e8919  cmp byte ptr [rdi+0x18],2
0x66e846f  movups xmm0,[rdi+0x20]
0x66e8128  movsd xmm7,[rdi+0x30]
0x66e8123  movss xmm6,[rdi+0x38]
0x66e7648  mov rax,[rdi+0x40]
0x66e7ebe  mov eax,[rdi+0x48]
0x66e7d0a  mov rax,[rdi+0x50]
0x66e7d18  mov rcx,[rdi+0x58]
0x66e7b2d  lea r8,[rdi+0x60]
0x66e778c  mov rax,[rdi+0x70]
0x66e7df2  movups xmm0,[rdi+0x80]
0x66e844c  movzx eax,word ptr [rdi+0x90]
0x66e8144  mov r12d,[rdi+0x98]
0x66e814b  mov r13d,[rdi+0x9C]
0x66e8756  mov r8,[rdi+0xA0]
0x66e872d  mov rcx,[rdi+0xA8]
0x66e7666  movzx r12d,byte ptr [rdi+0xB0]

## writes to the register
Instructions that write rdi (from the input data, 6 lines):

0x66e7634  mov rdi,r8
0x66e86ce  lea rdi,[rbp+0x368]
0x66e8823  lea rdi,[rbp-0x10]
0x66e88f9  mov rdi,[rbp+0x1B0]
0x66e8a97  lea rdi,[rbp+0x200]
0x66e8e59  mov rdi,[rbp+0x4A8]

`0x66e7634  mov rdi,r8` is the entry copy itself (header: description pointer copy = rdi), so reads after it are reads of the description and are NOT flagged.

Read lines the data file flags as possibly after a register overwrite (site RVA falls after one of the 5 non-copy rdi writes; per the data: "ignore reads below them in the same block and flag them"):
- after `0x66e86ce  lea rdi,[rbp+0x368]`: 0x66e872d, 0x66e873d, 0x66e8756, 0x66e87bf, 0x66e87cd, 0x66e87d7, 0x66e87e2, 0x66e87ed
- after `0x66e8823  lea rdi,[rbp-0x10]`: 0x66e8919, 0x66e891f
- after `0x66e88f9  mov rdi,[rbp+0x1B0]`: 0x66e8998, 0x66e89a8, 0x66e89c1, 0x66e8a2d, 0x66e8a3b, 0x66e8a45, 0x66e8a50, 0x66e8a5b
- after `0x66e8e59  mov rdi,[rbp+0x4A8]`: 0x66e8e77, 0x66e8e7d
- after `0x66e8a97  lea rdi,[rbp+0x200]`: none

Rows marked [UNVERIFIED: rdi reused]: 0x00, 0x08, 0x10, 0x18, 0x20, 0x30, 0x90, 0xA0, 0xA8 (each contains at least one flagged site above).
Rows NOT flagged (all sites before 0x66e86ce): 0x38, 0x40, 0x48, 0x50, 0x58, 0x60, 0x70, 0x80, 0x98, 0x9C, 0xB0.

## TOOL REQUESTS
None.
