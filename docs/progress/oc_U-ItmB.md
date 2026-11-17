## NEXT
DONE - all 3 tag tables written and checked (37 rows, 37/37 verbatim lines match the exe)

# Item group visitor description read lists: tags 5 Crack / 7 SkinnedMesh / 9 BlockChanges (reg rsi)

Input data: docs/progress/_itemB_data.txt (precomputed by the orchestrator; not re-run). Every quoted `0xRVA  instr` line is checked against the exe by tools/sigs/verify_oc.py -> all rows [V].
Offset keys carry a (t5)/(t7)/(t9) suffix: offsets 0x0/0x8/0xC/0x10 recur in several tags and the checker requires globally unique first cells; the suffix is not part of the offset.
Site column = every read/store site of that [rsi+off] (first included, comma-separated). Size from the instruction (movups 16, qword 8, dword 4). Meaning only where an instruction shows it, else '-'. No line reads a register other than rsi (the tag-header register), so no lines were dropped.

## tag 5 Crack (head 0x66471de, reg rsi, 61 sites -> 4 offsets)

| offset | size | site | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t5) | 8 | 0x664e44b, 0x664e460, 0x664e4a5, 0x664e4ba, 0x664e6a3, 0x664e6b8, 0x664e6fb, 0x664e710, 0x664e734, 0x664e749, 0x664e76b, 0x664e780, 0x664e7a2, 0x664e7b7, 0x664e7d9, 0x664e7ee, 0x664e810, 0x664e825, 0x664e844, 0x664e859, 0x664e87b, 0x664e890, 0x664e8b2, 0x664e8c7, 0x664e8f8, 0x664e90d, 0x664e94a, 0x664e95f, 0x664e98b, 0x664e9a4 | `0x664e44b  mov rax,[rsi]` | - |
| 0x8 (t5) | 4 | 0x664e445, 0x664e49f, 0x664e69d, 0x664e6f5, 0x664e72e, 0x664e765, 0x664e79c, 0x664e7d3, 0x664e80a, 0x664e83e, 0x664e875, 0x664e8ac, 0x664e8f2, 0x664e944, 0x664e981 | `0x664e445  lock dec dword ptr [rsi+8]` | atomic dec of dword (lock dec) [V] |
| 0xC (t5) | 4 | 0x664e45a, 0x664e4b4, 0x664e6b2, 0x664e70a, 0x664e743, 0x664e77a, 0x664e7b1, 0x664e7e8, 0x664e81f, 0x664e853, 0x664e88a, 0x664e8c1, 0x664e907, 0x664e959, 0x664e99a | `0x664e45a  lock dec dword ptr [rsi+0xC]` | atomic dec of dword (lock dec) [V] |
| 0x10 (t5) | 8 | 0x664e3c8 | `0x664e3c8  add rcx,[rsi+0x10]` | - |

verify tag 5 (first instruction per row, verbatim from _itemB_data.txt):
0x664e44b  mov rax,[rsi]
0x664e445  lock dec dword ptr [rsi+8]
0x664e45a  lock dec dword ptr [rsi+0xC]
0x664e3c8  add rcx,[rsi+0x10]

## tag 7 SkinnedMesh (head 0x6646dc2, reg rsi, 53 sites -> 28 offsets)

| offset | size | site | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t7) | 16 (store) / 8 (reads) | 0x664b826, 0x664cac9, 0x664cade, 0x664cb21, 0x664cb36, 0x664e98b, 0x664e9a4, 0x664eadc, 0x664eaf1, 0x664eb34, 0x664eb49, 0x664eb6d, 0x664eb82 | `0x664b826  movups [rsi],xmm0` | 0x664b826 stores xmm0 (16 bytes) [V]; the other sites load qword [rsi] [V] |
| 0x8 (t7) | 4 | 0x664cac3, 0x664cb1b, 0x664e981, 0x664ead6, 0x664eb2e, 0x664eb67 | `0x664cac3  lock dec dword ptr [rsi+8]` | atomic dec of dword (lock dec) [V] |
| 0xC (t7) | 4 | 0x664cad8, 0x664cb30, 0x664e99a, 0x664eaeb, 0x664eb43, 0x664eb7c | `0x664cad8  lock dec dword ptr [rsi+0xC]` | atomic dec of dword (lock dec) [V] |
| 0x10 (t7) | 8 | 0x664b829, 0x664ca89 | `0x664b829  mov qword ptr [rsi+0x10],0` | 0x664b829 stores qword 0 [V]; 0x664ca89 reads [rsi+0x10] into rcx [V] |
| 0x70 (t7) | 8 | 0x664b660 | `0x664b660  mov rax,[rsi+0x70]` | - |
| 0x78 (t7) | 8 | 0x664b69b | `0x664b69b  mov rax,[rsi+0x78]` | - |
| 0x80 (t7) | 8 | 0x664b6bc | `0x664b6bc  mov rax,[rsi+0x80]` | - |
| 0xD0 (t7) | 8 | 0x664b506 | `0x664b506  mov rax,[rsi+0xD0]` | - |
| 0xD8 (t7) | 8 | 0x664b582 | `0x664b582  mov rax,[rsi+0xD8]` | - |
| 0xE0 (t7) | 8 | 0x664b5c0 | `0x664b5c0  mov rax,[rsi+0xE0]` | - |
| 0xE8 (t7) | 8 | 0x664b5e4 | `0x664b5e4  mov rax,[rsi+0xE8]` | - |
| 0xF0 (t7) | 8 | 0x664b544 | `0x664b544  mov rax,[rsi+0xF0]` | - |
| 0xF8 (t7) | 8 | 0x664b4c8 | `0x664b4c8  mov rax,[rsi+0xF8]` | - |
| 0x100 (t7) | 8 | 0x664b73f | `0x664b73f  mov rax,[rsi+0x100]` | - |
| 0x108 (t7) | 8 | 0x664b622 | `0x664b622  mov rax,[rsi+0x108]` | - |
| 0x110 (t7) | 8 | 0x664b6d3 | `0x664b6d3  mov rax,[rsi+0x110]` | - |
| 0x118 (t7) | 8 | 0x664b6f7 | `0x664b6f7  mov rax,[rsi+0x118]` | - |
| 0x120 (t7) | 8 | 0x664b71b | `0x664b71b  mov rax,[rsi+0x120]` | - |
| 0x150 (t7) | 8 | 0x664b77d | `0x664b77d  mov rax,[rsi+0x150]` | - |
| 0x260 (t7) | 8 | 0x6647632, 0x6647645 | `0x6647632  mov rax,[rsi+0x260]` | - |
| 0x268 (t7) | 8 | 0x6648852, 0x6648868 | `0x6648852  mov rcx,[rsi+0x268]` | - |
| 0x278 (t7) | 16 | 0x66488ce | `0x66488ce  movups xmm0,[rsi+0x278]` | - |
| 0x288 (t7) | 16 | 0x66488dc | `0x66488dc  movups xmm1,[rsi+0x288]` | - |
| 0x298 (t7) | 16 | 0x66488ea | `0x66488ea  movups xmm2,[rsi+0x298]` | - |
| 0x2A8 (t7) | 16 | 0x66488f8 | `0x66488f8  movups xmm3,[rsi+0x2A8]` | - |
| 0x2B8 (t7) | 8 | 0x6647b71 | `0x6647b71  mov rax,[rsi+0x2B8]` | - |
| 0x2C0 (t7) | 8 | 0x664abfc | `0x664abfc  mov rdx,[rsi+0x2C0]` | - |
| 0x2C8 (t7) | 8 | 0x664aca1 | `0x664aca1  mov rdx,[rsi+0x2C8]` | - |

verify tag 7 (first instruction per row, verbatim from _itemB_data.txt):
0x664b826  movups [rsi],xmm0
0x664cac3  lock dec dword ptr [rsi+8]
0x664cad8  lock dec dword ptr [rsi+0xC]
0x664b829  mov qword ptr [rsi+0x10],0
0x664b660  mov rax,[rsi+0x70]
0x664b69b  mov rax,[rsi+0x78]
0x664b6bc  mov rax,[rsi+0x80]
0x664b506  mov rax,[rsi+0xD0]
0x664b582  mov rax,[rsi+0xD8]
0x664b5c0  mov rax,[rsi+0xE0]
0x664b5e4  mov rax,[rsi+0xE8]
0x664b544  mov rax,[rsi+0xF0]
0x664b4c8  mov rax,[rsi+0xF8]
0x664b73f  mov rax,[rsi+0x100]
0x664b622  mov rax,[rsi+0x108]
0x664b6d3  mov rax,[rsi+0x110]
0x664b6f7  mov rax,[rsi+0x118]
0x664b71b  mov rax,[rsi+0x120]
0x664b77d  mov rax,[rsi+0x150]
0x6647632  mov rax,[rsi+0x260]
0x6648852  mov rcx,[rsi+0x268]
0x66488ce  movups xmm0,[rsi+0x278]
0x66488dc  movups xmm1,[rsi+0x288]
0x66488ea  movups xmm2,[rsi+0x298]
0x66488f8  movups xmm3,[rsi+0x2A8]
0x6647b71  mov rax,[rsi+0x2B8]
0x664abfc  mov rdx,[rsi+0x2C0]
0x664aca1  mov rdx,[rsi+0x2C8]

## tag 9 BlockChanges (head 0x6646bc6, reg rsi, 17 sites -> 5 offsets)

| offset | size | site | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x90 (t9) | 8 (0x6647a9d: 4) | 0x66474eb, 0x664789b, 0x6647a07, 0x6647a47, 0x6647a9d | `0x66474eb  sub r13,[rsi+0x90]` | 0x6647a47 stores rdi [V]; 0x6647a9d subtracts dword [rsi+0x90] from eax [V] |
| 0x98 (t9) | 8 (0x6647a97: 4) | 0x6646c61, 0x6646c80, 0x66478a2, 0x6647917, 0x6647a56, 0x6647a97 | `0x6646c61  mov r12,[rsi+0x98]` | 0x6646c80 adds 0x18 to qword [rsi+0x98] [V]; 0x6647a56 stores rax [V] |
| 0xA0 (t9) | 8 | 0x6646c68, 0x6647a13, 0x6647a65 | `0x6646c68  cmp r12,[rsi+0xA0]` | 0x6647a65 stores rax [V] |
| 0x8 (t9) | 8 | 0x6647ad1, 0x6647af0 | `0x6647ad1  mov rax,[rsi+8]` | 0x6647af0 adds 0xC8 to qword [rsi+8] [V] |
| 0x10 (t9) | 8 | 0x6647ad5 | `0x6647ad5  cmp rax,[rsi+0x10]` | - |

verify tag 9 (first instruction per row, verbatim from _itemB_data.txt):
0x66474eb  sub r13,[rsi+0x90]
0x6646c61  mov r12,[rsi+0x98]
0x6646c68  cmp r12,[rsi+0xA0]
0x6647ad1  mov rax,[rsi+8]
0x6647ad5  cmp rax,[rsi+0x10]

## TOOL REQUESTS
None

<!-- END -->
