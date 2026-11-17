## NEXT
DONE - U-D10x1 complete: all 3 tag read maps annotated in this file (40 rows, one per distinct offset; verify_oc match=60 mismatch=0; delegate check OK).

# D10: editor-group description read maps, tags 1-3 (unit U-D10x1)

Source data: docs/progress/_d10a_data.txt (orchestrator-computed). All 60 source lines were re-checked against the exe with `python tools/sigs/verify_oc.py docs/progress/_d10a_data.txt`: claimed=60 match=60 mismatch=0 no-such-instr=0.

Conventions: one row per distinct `[rdi+off]` offset per tag. Size is taken from the row's first instruction (movsd 8, movss 4, movups 16, movzx/cmp byte 1, mov r12w/di/bx word 2, mov rsi qword 8; lea computes an address, no load). The read-address column lists the first site, then every further site of the same offset, comma-separated. The verbatim instruction column quotes only the first site; later sites of the same offset are given as addresses in the read-address column and their effect (if the data shows one, e.g. a compare) is noted in the meaning column. The offset cell carries a `(tag N)` marker only so that offsets repeated across the three tag tables stay distinct rows.

## tag 1 (case head 0x667499f): one row per distinct [rdi+off] offset
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0xC (tag 1) | 8 | 0x66753c7 | `0x66753c7  movsd xmm2,[rdi+0xC]` | - |
| 0x14 (tag 1) | 4 | 0x66753f5 | `0x66753f5  movss xmm2,[rdi+0x14]` | - |
| 0x0 (tag 1) | 8 | 0x6675477 | `0x6675477  movsd xmm3,[rdi]` | - |
| 0x8 (tag 1) | 4 | 0x6675488, 0x667a763 | `0x6675488  movss xmm3,[rdi+8]` | second site is a qword (8-byte) read: `0x667a763  mov rsi,[rdi+8]` |
| 0x78 (tag 1) | 4 | 0x66754dd | `0x66754dd  movss xmm0,[rdi+0x78]` | - |
| 0x80 (tag 1) | n/a (lea) | 0x6675518 | `0x6675518  lea rbx,[rdi+0x80]` | address of field taken (lea), not a load |
| 0x24 (tag 1) | n/a (lea) | 0x6675530 | `0x6675530  lea r8,[rdi+0x24]` | address of field taken (lea), not a load |
| 0x74 (tag 1) | 1 | 0x6675560 | `0x6675560  movzx eax,byte ptr [rdi+0x74]` | - |
| 0x64 (tag 1) | 16 | 0x66758bd | `0x66758bd  movups xmm6,[rdi+0x64]` | - |
| 0xD2 (tag 1) | 1 | 0x66758c1 | `0x66758c1  cmp byte ptr [rdi+0xD2],1` | compared with 1 |
| 0x20 (tag 1) | 4 | 0x6676b7a, 0x667a3fe | `0x6676b7a  movss xmm0,[rdi+0x20]` | - |
| 0x18 (tag 1) | 8 | 0x6676b7f, 0x667a403, 0x667a75d | `0x6676b7f  movsd xmm1,[rdi+0x18]` | third site reads only the low byte and compares it with 2: `0x667a75d  cmp byte ptr [rdi+0x18],2` |
| 0xD0 (tag 1) | 2 | 0x6676c9b, 0x667a4dd | `0x6676c9b  mov r12w,[rdi+0xD0]` | - |

Verbatim first-site lines of the table above (machine-checked):
0x66753c7  movsd xmm2,[rdi+0xC]
0x66753f5  movss xmm2,[rdi+0x14]
0x6675477  movsd xmm3,[rdi]
0x6675488  movss xmm3,[rdi+8]
0x66754dd  movss xmm0,[rdi+0x78]
0x6675518  lea rbx,[rdi+0x80]
0x6675530  lea r8,[rdi+0x24]
0x6675560  movzx eax,byte ptr [rdi+0x74]
0x66758bd  movups xmm6,[rdi+0x64]
0x66758c1  cmp byte ptr [rdi+0xD2],1
0x6676b7a  movss xmm0,[rdi+0x20]
0x6676b7f  movsd xmm1,[rdi+0x18]
0x6676c9b  mov r12w,[rdi+0xD0]

## tag 2 (case head 0x6674518): one row per distinct [rdi+off] offset
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0xC (tag 2) | 8 | 0x667503a | `0x667503a  movsd xmm2,[rdi+0xC]` | - |
| 0x14 (tag 2) | 4 | 0x6675068 | `0x6675068  movss xmm2,[rdi+0x14]` | - |
| 0x0 (tag 2) | 8 | 0x66750ea | `0x66750ea  movsd xmm3,[rdi]` | - |
| 0x8 (tag 2) | 4 | 0x66750fb, 0x6679aa1 | `0x66750fb  movss xmm3,[rdi+8]` | second site is a qword (8-byte) read: `0x6679aa1  mov rsi,[rdi+8]` |
| 0x78 (tag 2) | 4 | 0x6675153 | `0x6675153  movss xmm0,[rdi+0x78]` | - |
| 0x80 (tag 2) | n/a (lea) | 0x667518e | `0x667518e  lea rbx,[rdi+0x80]` | address of field taken (lea), not a load |
| 0x74 (tag 2) | 1 | 0x66751a6 | `0x66751a6  movzx eax,byte ptr [rdi+0x74]` | - |
| 0x64 (tag 2) | 16 | 0x66751b2 | `0x66751b2  movups xmm6,[rdi+0x64]` | - |
| 0xD2 (tag 2) | 1 | 0x667589a | `0x667589a  cmp byte ptr [rdi+0xD2],0` | compared with 0 |
| 0x20 (tag 2) | 4 | 0x6676538, 0x6679715 | `0x6676538  movss xmm0,[rdi+0x20]` | - |
| 0x18 (tag 2) | 8 | 0x667653d, 0x667971a, 0x6679a9b | `0x667653d  movsd xmm1,[rdi+0x18]` | third site reads only the low byte and compares it with 2: `0x6679a9b  cmp byte ptr [rdi+0x18],2` |
| 0x24 (tag 2) | n/a (lea) | 0x66765cd, 0x66797aa | `0x66765cd  lea r8,[rdi+0x24]` | address of field taken (lea), not a load |
| 0xD0 (tag 2) | 2 | 0x6676652, 0x667981b | `0x6676652  mov r12w,[rdi+0xD0]` | - |

Verbatim first-site lines of the table above (machine-checked):
0x667503a  movsd xmm2,[rdi+0xC]
0x6675068  movss xmm2,[rdi+0x14]
0x66750ea  movsd xmm3,[rdi]
0x66750fb  movss xmm3,[rdi+8]
0x6675153  movss xmm0,[rdi+0x78]
0x667518e  lea rbx,[rdi+0x80]
0x66751a6  movzx eax,byte ptr [rdi+0x74]
0x66751b2  movups xmm6,[rdi+0x64]
0x667589a  cmp byte ptr [rdi+0xD2],0
0x6676538  movss xmm0,[rdi+0x20]
0x667653d  movsd xmm1,[rdi+0x18]
0x66765cd  lea r8,[rdi+0x24]
0x6676652  mov r12w,[rdi+0xD0]

## tag 3 (case head 0x667463c): one row per distinct [rdi+off] offset
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x8 (tag 3) | 4 | 0x6675218, 0x667bf1e | `0x6675218  movss xmm0,[rdi+8]` | second site is a qword (8-byte) read: `0x667bf1e  mov rsi,[rdi+8]` |
| 0x14 (tag 3) | 4 | 0x667521d | `0x667521d  subss xmm0,[rdi+0x14]` | - |
| 0x0 (tag 3) | 8 | 0x6675229 | `0x6675229  movsd xmm3,[rdi]` | - |
| 0xC (tag 3) | 8 | 0x667522d | `0x667522d  movsd xmm1,[rdi+0xC]` | - |
| 0x78 (tag 3) | 4 | 0x667529c | `0x667529c  movss xmm1,[rdi+0x78]` | - |
| 0xD0 (tag 3) | n/a (lea) | 0x66752ce | `0x66752ce  lea r14,[rdi+0xD0]` | address of field taken (lea), not a load |
| 0x80 (tag 3) | n/a (lea) | 0x66752e6 | `0x66752e6  lea rbx,[rdi+0x80]` | address of field taken (lea), not a load |
| 0x24 (tag 3) | n/a (lea) | 0x6675313 | `0x6675313  lea r8,[rdi+0x24]` | address of field taken (lea), not a load |
| 0x74 (tag 3) | 1 | 0x6675340, 0x6679c72 | `0x6675340  cmp byte ptr [rdi+0x74],0` | compared with 0 |
| 0x64 (tag 3) | 16 | 0x6675dea | `0x6675dea  movups xmm9,[rdi+0x64]` | - |
| 0x20 (tag 3) | 4 | 0x6676851, 0x6679e35, 0x667b5d3 | `0x6676851  movss xmm0,[rdi+0x20]` | - |
| 0x18 (tag 3) | 8 | 0x6676856, 0x6679e3a, 0x667b5d8, 0x667bf18 | `0x6676856  movsd xmm1,[rdi+0x18]` | fourth site reads only the low byte and compares it with 2: `0x667bf18  cmp byte ptr [rdi+0x18],2` |
| 0x120 (tag 3) | 2 | 0x667696d, 0x6679f27, 0x667b6b8 | `0x667696d  mov r12w,[rdi+0x120]` | - |
| 0x122 (tag 3) | 1 | 0x6679c65 | `0x6679c65  cmp byte ptr [rdi+0x122],1` | compared with 1 |

Verbatim first-site lines of the table above (machine-checked):
0x6675218  movss xmm0,[rdi+8]
0x667521d  subss xmm0,[rdi+0x14]
0x6675229  movsd xmm3,[rdi]
0x667522d  movsd xmm1,[rdi+0xC]
0x667529c  movss xmm1,[rdi+0x78]
0x66752ce  lea r14,[rdi+0xD0]
0x66752e6  lea rbx,[rdi+0x80]
0x6675313  lea r8,[rdi+0x24]
0x6675340  cmp byte ptr [rdi+0x74],0
0x6675dea  movups xmm9,[rdi+0x64]
0x6676851  movss xmm0,[rdi+0x20]
0x6676856  movsd xmm1,[rdi+0x18]
0x667696d  mov r12w,[rdi+0x120]
0x6679c65  cmp byte ptr [rdi+0x122],1

## TOOL REQUESTS
None.
