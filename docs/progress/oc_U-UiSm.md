## NEXT
DONE

# Field map of UI visitor tags 2 and 3 (reg r9)

Source: docs/progress/_uiC_data.txt (orchestrator-precomputed [r9+off] sites). One row per distinct offset; all sites of an offset are listed as raw verbatim lines under the table (and the tag-3 rows carry a `(tag3)` suffix in the offset cell to keep rows unique file-wide). Sizes from the instruction (mov 8, movss 4, movzx byte 1, cmp qword 8; lea = address only, no size).

## tag 2 (head 0x6664bd6, reg r9) — 19 reads, 18 distinct offsets
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x00 | 8 | [r9] | 0x6664eb1  mov r13,[r9] | - |
| 0x08 | 8 | [r9+0x8] | 0x6664eb4  mov r14,[r9+8] | - |
| 0x10 | 8 | [r9+0x10] | 0x6664ea9  mov r15,[r9+0x10] | - |
| 0x18 | - | [r9+0x18] (lea, address only) | 0x6664c3b  lea rax,[r9+0x18] | - |
| 0x28 | 8 | [r9+0x28] | 0x6664e97  mov r12,[r9+0x28] | - |
| 0x30 | 8 | [r9+0x30] (2 sites) | 0x6664c68  mov r15,[r9+0x30] / 0x6664c7a  mov r15,[r9+0x30] | - |
| 0x58 | 8 | [r9+0x58] | 0x6664c3f  cmp qword ptr [r9+0x58],2 | - |
| 0x60 | 8 | [r9+0x60] | 0x6664c2b  mov r11,[r9+0x60] | - |
| 0x68 | 8 | [r9+0x68] | 0x6664c2f  mov rdx,[r9+0x68] | - |
| 0x70 | 4 | [r9+0x70] | 0x6664c25  movss xmm0,[r9+0x70] | - |
| 0x78 | 8 | [r9+0x78] | 0x6664ead  mov r12,[r9+0x78] | - |
| 0x80 | 1 | [r9+0x80] | 0x6664c33  movzx edi,byte ptr [r9+0x80] | - |
| 0x81 | 1 | [r9+0x81] | 0x6664c1d  movzx r8d,byte ptr [r9+0x81] | - |
| 0x82 | 1 | [r9+0x82] | 0x6664bd6  movzx ecx,byte ptr [r9+0x82] | - |
| 0x83 | 1 | [r9+0x83] | 0x6664bde  movzx r12d,byte ptr [r9+0x83] | - |
| 0x84 | 1 | [r9+0x84] | 0x6664be6  movzx edx,byte ptr [r9+0x84] | - |
| 0x85 | 1 | [r9+0x85] | 0x6664c15  movzx esi,byte ptr [r9+0x85] | - |
| 0x88 | - | [r9+0x88] (lea, address only) | 0x6664c07  lea rbx,[r9+0x88] | - |

Verbatim site lines (tag 2), one per site:
```
  0x6664bd6  movzx ecx,byte ptr [r9+0x82]
  0x6664bde  movzx r12d,byte ptr [r9+0x83]
  0x6664be6  movzx edx,byte ptr [r9+0x84]
  0x6664c07  lea rbx,[r9+0x88]
  0x6664c15  movzx esi,byte ptr [r9+0x85]
  0x6664c1d  movzx r8d,byte ptr [r9+0x81]
  0x6664c25  movss xmm0,[r9+0x70]
  0x6664c2b  mov r11,[r9+0x60]
  0x6664c2f  mov rdx,[r9+0x68]
  0x6664c33  movzx edi,byte ptr [r9+0x80]
  0x6664c3b  lea rax,[r9+0x18]
  0x6664c3f  cmp qword ptr [r9+0x58],2
  0x6664c68  mov r15,[r9+0x30]
  0x6664c7a  mov r15,[r9+0x30]
  0x6664e97  mov r12,[r9+0x28]
  0x6664ea9  mov r15,[r9+0x10]
  0x6664ead  mov r12,[r9+0x78]
  0x6664eb1  mov r13,[r9]
  0x6664eb4  mov r14,[r9+8]
```

## tag 3 (head 0x6664c83, reg r9) — 8 reads, 8 distinct offsets
(offset cells carry a `(tag3)` suffix so table rows stay unique across the two sections; offsets are per-tag, relative to r9)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x00 (tag3) | 8 | [r9] | 0x6664cb4  mov r11,[r9] | - |
| 0x08 (tag3) | 8 | [r9+0x8] | 0x6664cb7  mov rsi,[r9+8] | - |
| 0x10 (tag3) | - | [r9+0x10] (lea, address only) | 0x6664ca2  lea rdi,[r9+0x10] | - |
| 0x20 (tag3) | 8 | [r9+0x20] | 0x6664c9e  mov r8,[r9+0x20] | - |
| 0x28 (tag3) | 8 | [r9+0x28] | 0x6664cb0  mov r10,[r9+0x28] | - |
| 0x30 (tag3) | 8 | [r9+0x30] | 0x6664c87  mov rcx,[r9+0x30] | - |
| 0x3A (tag3) | 1 | [r9+0x3A] | 0x6664c8b  movzx edx,byte ptr [r9+0x3A] | - |
| 0x40 (tag3) | - | [r9+0x40] (lea, address only) | 0x6664c83  lea rax,[r9+0x40] | - |

Verbatim site lines (tag 3), one per site:
```
  0x6664c83  lea rax,[r9+0x40]
  0x6664c87  mov rcx,[r9+0x30]
  0x6664c8b  movzx edx,byte ptr [r9+0x3A]
  0x6664c9e  mov r8,[r9+0x20]
  0x6664ca2  lea rdi,[r9+0x10]
  0x6664cb0  mov r10,[r9+0x28]
  0x6664cb4  mov r11,[r9]
  0x6664cb7  mov rsi,[r9+8]
```

## TOOL REQUESTS
None
