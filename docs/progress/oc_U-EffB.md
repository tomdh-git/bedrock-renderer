## NEXT
DONE

# U-EffB: description read lists, GROUP visitor cases (tags 6,7,8) — checklist R4/R5/L4s

Source data: docs/progress/_effB_data.txt (verbatim lines copied from it; precomputed by the orchestrator, not re-run).
Filter: only lines whose `[reg+off]` (or `[reg]`) memory operand is READ (source operand); pure stores (`mov [reg],x`, `movups [reg+off],xmm`) and `lea` lines are ignored; `lock dec`/`add [mem]` read-modify-writes count as reads. One row per distinct offset per tag; the first site of the offset is the verbatim instruction (its RVA is the first read address), the remaining read addresses of that offset are listed comma-separated. Size = size of the first instruction (movups 16, qword/movsd 8, dword/movss 4, word 2, byte 1, register-size otherwise). Meaning '-' unless an instruction shows it; no read instruction in these lists shows a meaning, so all are '-'. First column carries a t6/t7/t8 prefix because the checker forbids duplicate offset values across the whole file. All 307 data lines (reads and ignored store/lea lines) are quoted at line start in the CLAIM LINES section for tools/sigs/verify_oc.py.

## tag 6 (head 0x666b143, reg rsi; 66 listed lines: 66 read sites, 0 ignored store/lea sites)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| t6 0x10 | 1 | - | 0x666b2a5  cmp byte ptr [rsi+0x10],1 | - |
| t6 0x8 | 4 | 0x666c9bd, 0x666d2a5, 0x666d5a7, 0x666e61f, 0x666e678, 0x666e737, 0x666e7b6, 0x666eaa7, 0x666ede2, 0x666ee48, 0x666fb88 | 0x666b2de  lock dec dword ptr [rsi+8] | - |
| t6 0x0 | 8 | 0x666b301, 0x666c9c7, 0x666c9e0, 0x666d2ab, 0x666d2c0, 0x666d5ad, 0x666d5c2, 0x666e625, 0x666e63a, 0x666e67e, 0x666e693, 0x666e73d, 0x666e752, 0x666e7bc, 0x666e7d1, 0x666eaad, 0x666eac2, 0x666ede8, 0x666edfd, 0x666ee4e, 0x666ee63, 0x666fb92, 0x666fbab | 0x666b2e8  mov rax,[rsi] | - |
| t6 0xC | 4 | 0x666c9d6, 0x666d2ba, 0x666d5bc, 0x666e634, 0x666e68d, 0x666e74c, 0x666e7cb, 0x666eabc, 0x666edf7, 0x666ee5d, 0x666fba1 | 0x666b2f7  lock dec dword ptr [rsi+0xC] | - |
| t6 0x60 | 8 | 0x666e9b5 | 0x666d4b5  mov rax,[rsi+0x60] | - |
| t6 0x58 | 8 | 0x666e9b9 | 0x666d4b9  sub rax,[rsi+0x58] | - |
| t6 0x1D4 | 1 | 0x666ea02 | 0x666d502  cmp byte ptr [rsi+0x1D4],0 | - |
| t6 0x1D0 | 4 | 0x666ea0b | 0x666d50b  mov r14d,[rsi+0x1D0] | - |
| t6 0x1B0 | 8 | 0x666d586, 0x666ea5b, 0x666ea86 | 0x666d55b  mov rax,[rsi+0x1B0] | - |
| t6 0x1B8 | 8 | 0x666d57b, 0x666ea6b, 0x666ea7b | 0x666d56b  mov rax,[rsi+0x1B8] | - |
| t6 0x84 | 4 | - | 0x666e6f5  mov r15d,[rsi+0x84] | - |

## tag 7 (head 0x666ae72, reg rsi; 221 listed lines: 178 read sites, 43 ignored store/lea sites)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| t7 0x18 | 8 | 0x66703a0 | 0x666b648  mov rbx,[rsi+0x18] | - |
| t7 0x8 | 4 | 0x666b7d4, 0x666b9d6, 0x666baca, 0x666c6c1, 0x666c728, 0x666c7bc, 0x666c800, 0x666cf17, 0x666dd71, 0x666dd85, 0x666dd99, 0x666e15f, 0x666e1a3, 0x666e3dc, 0x666e3ed, 0x666ef24, 0x666f133, 0x666f13f, 0x666fa2c, 0x666fa47, 0x666faf3, 0x666fb4b, 0x666fb88, 0x666fe8d, 0x666fe9d, 0x666fead, 0x666ff28, 0x666ff6c, 0x66700b3, 0x6670623, 0x667067b, 0x66706b4, 0x6670869, 0x66708c1, 0x66708fa | 0x666b746  lock dec dword ptr [rsi+8] | - |
| t7 0x0 | 8 | 0x666b761, 0x666b7da, 0x666b7ef, 0x666b9dc, 0x666b9f1, 0x666bad0, 0x666bae5, 0x666c6c7, 0x666c6dc, 0x666c72e, 0x666c743, 0x666c7c2, 0x666c7d7, 0x666c80a, 0x666c823, 0x666da5f, 0x666da83, 0x666dd2f, 0x666dd82, 0x666dda3, 0x666ddbc, 0x666e111, 0x666e169, 0x666e182, 0x666e1a9, 0x666e1be, 0x666e240, 0x666ef2a, 0x666ef3f, 0x666faf9, 0x666fb0e, 0x666fb51, 0x666fb66, 0x666fb92, 0x666fbab, 0x666fe4b, 0x666fe9a, 0x666feb3, 0x666fec8, 0x666feda, 0x666ff32, 0x666ff4b, 0x666ff72, 0x666ff87, 0x6670000, 0x66700b9, 0x66700ce, 0x6670629, 0x667063e, 0x6670681, 0x6670696, 0x66706ba, 0x66706cf, 0x667074b, 0x667086f, 0x6670884, 0x66708c7, 0x66708dc, 0x6670900, 0x6670915, 0x6670991 | 0x666b74c  mov rax,[rsi] | - |
| t7 0xC | 4 | 0x666b7e9, 0x666b9eb, 0x666badf, 0x666c6d6, 0x666c73d, 0x666c7d1, 0x666c819, 0x666ddb2, 0x666e178, 0x666e1b8, 0x666ef39, 0x666fb08, 0x666fb60, 0x666fba1, 0x666fec2, 0x666ff41, 0x666ff81, 0x66700c8, 0x6670638, 0x6670690, 0x66706c9, 0x667087e, 0x66708d6, 0x667090f | 0x666b75b  lock dec dword ptr [rsi+0xC] | - |
| t7 0x60 | 8 | - | 0x666b945  mov rax,[rsi+0x60] | - |
| t7 0x58 | 8 | 0x667049a | 0x666b949  sub rax,[rsi+0x58] | - |
| t7 0x1D4 | 1 | - | 0x666b987  cmp byte ptr [rsi+0x1D4],0 | - |
| t7 0x1D0 | 4 | - | 0x666b990  mov edi,[rsi+0x1D0] | - |
| t7 0x20 | 8 | 0x666e3ad, 0x666e3e0, 0x666e3f1, 0x666f104, 0x666f137, 0x666f143 | 0x666cf0c  cmp qword ptr [rsi+0x20],0x10 | - |
| t7 0x28 | 8 | 0x666f10a, 0x66703ab | 0x666e3b3  cmp qword ptr [rsi+0x28],0x10 | - |
| t7 0x10 | 8 | 0x666f111, 0x666fa30 | 0x666e3ba  mov rdx,[rsi+0x10] | - |
| t7 0x788 | 4 | - | 0x666f57d  mov eax,[rsi+0x788] | - |
| t7 0x780 | 4 | - | 0x666f583  sub eax,[rsi+0x780] | - |
| t7 0x770 | 8 | 0x666f5f5, 0x666f635 | 0x666f5b5  mov rbx,[rsi+0x770] | - |
| t7 0x778 | 8 | - | 0x666f5bc  cmp rbx,[rsi+0x778] | - |
| t7 0x768 | 4 | - | 0x666f63b  sub eax,[rsi+0x768] | - |
| t7 0x758 | 8 | 0x666f6ee, 0x666f729 | 0x666f674  mov rdx,[rsi+0x758] | - |
| t7 0x760 | 8 | - | 0x666f67b  cmp rdx,[rsi+0x760] | - |
| t7 0x750 | 4 | - | 0x666f72f  sub eax,[rsi+0x750] | - |
| t7 0x8A8 | 8 | 0x666f77b, 0x666f7b5 | 0x666f761  mov rdx,[rsi+0x8A8] | - |
| t7 0x8B0 | 8 | - | 0x666f768  cmp rdx,[rsi+0x8B0] | - |
| t7 0x8A0 | 4 | - | 0x666f7bb  sub eax,[rsi+0x8A0] | - |
| t7 0x650 | 4 | - | 0x666f818  mov eax,[rsi+0x650] | - |
| t7 0x648 | 4 | - | 0x666f81e  sub eax,[rsi+0x648] | - |
| t7 0x500 | 8 | 0x666f92c, 0x666f951, 0x666fa05 | 0x666f84c  mov rbx,[rsi+0x500] | - |
| t7 0x508 | 8 | 0x666f984 | 0x666f853  cmp rbx,[rsi+0x508] | - |
| t7 0x4F8 | 8 | 0x666f93c, 0x666f963, 0x666f978, 0x666f9fd | 0x666f86e  sub r13,[rsi+0x4F8] | - |
| t7 0x38 | 16 | - | 0x66703b6  movups xmm0,[rsi+0x38] | - |
| t7 0x48 | 16 | - | 0x66703c1  movups xmm0,[rsi+0x48] | - |
| t7 0x88 | 2 | - | 0x66703e2  movzx eax,word ptr [rsi+0x88] | - |
| t7 0x5C | 8 | - | 0x667049f  movsd xmm0,[rsi+0x5C] | - |
| t7 0xC9 | 1 | - | 0x6670513  cmp byte ptr [rsi+0xC9],1 | - |

## tag 8 (head 0x666b316, reg r15; 20 listed lines: 12 read sites, 8 ignored store/lea sites)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| t8 0x0 | 8 | 0x666cdc9, 0x666cddf | 0x666ccd0  mov rdx,[r15] | - |
| t8 0x8 | 8 | 0x666cd1a, 0x666cdc2 | 0x666ccd6  mov rdx,[r15+8] | - |
| t8 0x10 | 16 | - | 0x666ccde  movups xmm1,[r15+0x10] | - |
| t8 0x20 | 16 | - | 0x666cce3  movups xmm2,[r15+0x20] | - |
| t8 0x30 | 16 | - | 0x666cce8  movups xmm3,[r15+0x30] | - |
| t8 0x40 | 16 | - | 0x666cced  movups xmm4,[r15+0x40] | - |
| t8 0x50 | 8 | - | 0x666cd02  mov rdx,[r15+0x50] | - |
| t8 0xC | 4 | - | 0x666cdd8  lock dec dword ptr [r15+0xC] | - |

## CLAIM LINES (every data line of docs/progress/_effB_data.txt, verbatim, for tools/sigs/verify_oc.py)

tag 6 reads:
0x666b2a5  cmp byte ptr [rsi+0x10],1
0x666b2de  lock dec dword ptr [rsi+8]
0x666c9bd  lock dec dword ptr [rsi+8]
0x666d2a5  lock dec dword ptr [rsi+8]
0x666d5a7  lock dec dword ptr [rsi+8]
0x666e61f  lock dec dword ptr [rsi+8]
0x666e678  lock dec dword ptr [rsi+8]
0x666e737  lock dec dword ptr [rsi+8]
0x666e7b6  lock dec dword ptr [rsi+8]
0x666eaa7  lock dec dword ptr [rsi+8]
0x666ede2  lock dec dword ptr [rsi+8]
0x666ee48  lock dec dword ptr [rsi+8]
0x666fb88  lock dec dword ptr [rsi+8]
0x666b2e8  mov rax,[rsi]
0x666b301  mov rax,[rsi]
0x666c9c7  mov rax,[rsi]
0x666c9e0  mov rax,[rsi]
0x666d2ab  mov rax,[rsi]
0x666d2c0  mov rax,[rsi]
0x666d5ad  mov rax,[rsi]
0x666d5c2  mov rax,[rsi]
0x666e625  mov rax,[rsi]
0x666e63a  mov rax,[rsi]
0x666e67e  mov rax,[rsi]
0x666e693  mov rax,[rsi]
0x666e73d  mov rax,[rsi]
0x666e752  mov rax,[rsi]
0x666e7bc  mov rax,[rsi]
0x666e7d1  mov rax,[rsi]
0x666eaad  mov rax,[rsi]
0x666eac2  mov rax,[rsi]
0x666ede8  mov rax,[rsi]
0x666edfd  mov rax,[rsi]
0x666ee4e  mov rax,[rsi]
0x666ee63  mov rax,[rsi]
0x666fb92  mov rax,[rsi]
0x666fbab  mov rax,[rsi]
0x666b2f7  lock dec dword ptr [rsi+0xC]
0x666c9d6  lock dec dword ptr [rsi+0xC]
0x666d2ba  lock dec dword ptr [rsi+0xC]
0x666d5bc  lock dec dword ptr [rsi+0xC]
0x666e634  lock dec dword ptr [rsi+0xC]
0x666e68d  lock dec dword ptr [rsi+0xC]
0x666e74c  lock dec dword ptr [rsi+0xC]
0x666e7cb  lock dec dword ptr [rsi+0xC]
0x666eabc  lock dec dword ptr [rsi+0xC]
0x666edf7  lock dec dword ptr [rsi+0xC]
0x666ee5d  lock dec dword ptr [rsi+0xC]
0x666fba1  lock dec dword ptr [rsi+0xC]
0x666d4b5  mov rax,[rsi+0x60]
0x666e9b5  mov rax,[rsi+0x60]
0x666d4b9  sub rax,[rsi+0x58]
0x666e9b9  sub rax,[rsi+0x58]
0x666d502  cmp byte ptr [rsi+0x1D4],0
0x666ea02  cmp byte ptr [rsi+0x1D4],0
0x666d50b  mov r14d,[rsi+0x1D0]
0x666ea0b  mov r14d,[rsi+0x1D0]
0x666d55b  mov rax,[rsi+0x1B0]
0x666d586  mov rcx,[rsi+0x1B0]
0x666ea5b  mov rax,[rsi+0x1B0]
0x666ea86  mov rcx,[rsi+0x1B0]
0x666d56b  mov rax,[rsi+0x1B8]
0x666d57b  mov rax,[rsi+0x1B8]
0x666ea6b  mov rax,[rsi+0x1B8]
0x666ea7b  mov rax,[rsi+0x1B8]
0x666e6f5  mov r15d,[rsi+0x84]

tag 7 reads:
0x666b648  mov rbx,[rsi+0x18]
0x66703a0  movups xmm0,[rsi+0x18]
0x666b746  lock dec dword ptr [rsi+8]
0x666b7d4  lock dec dword ptr [rsi+8]
0x666b9d6  lock dec dword ptr [rsi+8]
0x666baca  lock dec dword ptr [rsi+8]
0x666c6c1  lock dec dword ptr [rsi+8]
0x666c728  lock dec dword ptr [rsi+8]
0x666c7bc  lock dec dword ptr [rsi+8]
0x666c800  lock dec dword ptr [rsi+8]
0x666cf17  mov rsi,[rsi+8]
0x666dd71  mov rax,[rsi+8]
0x666dd85  mov rsi,[rsi+8]
0x666dd99  lock dec dword ptr [rsi+8]
0x666e15f  lock dec dword ptr [rsi+8]
0x666e1a3  lock dec dword ptr [rsi+8]
0x666e3dc  mov rsi,[rsi+8]
0x666e3ed  mov rsi,[rsi+8]
0x666ef24  lock dec dword ptr [rsi+8]
0x666f133  mov rsi,[rsi+8]
0x666f13f  mov rsi,[rsi+8]
0x666fa2c  mov rax,[rsi+8]
0x666fa47  add qword ptr [rsi+8],0xC8
0x666faf3  lock dec dword ptr [rsi+8]
0x666fb4b  lock dec dword ptr [rsi+8]
0x666fb88  lock dec dword ptr [rsi+8]
0x666fe8d  mov rax,[rsi+8]
0x666fe9d  mov rsi,[rsi+8]
0x666fead  lock dec dword ptr [rsi+8]
0x666ff28  lock dec dword ptr [rsi+8]
0x666ff6c  lock dec dword ptr [rsi+8]
0x66700b3  lock dec dword ptr [rsi+8]
0x6670623  lock dec dword ptr [rsi+8]
0x667067b  lock dec dword ptr [rsi+8]
0x66706b4  lock dec dword ptr [rsi+8]
0x6670869  lock dec dword ptr [rsi+8]
0x66708c1  lock dec dword ptr [rsi+8]
0x66708fa  lock dec dword ptr [rsi+8]
0x666b74c  mov rax,[rsi]
0x666b761  mov rax,[rsi]
0x666b7da  mov rax,[rsi]
0x666b7ef  mov rax,[rsi]
0x666b9dc  mov rax,[rsi]
0x666b9f1  mov rax,[rsi]
0x666bad0  mov rax,[rsi]
0x666bae5  mov rax,[rsi]
0x666c6c7  mov rax,[rsi]
0x666c6dc  mov rax,[rsi]
0x666c72e  mov rax,[rsi]
0x666c743  mov rax,[rsi]
0x666c7c2  mov rax,[rsi]
0x666c7d7  mov rax,[rsi]
0x666c80a  mov rax,[rsi]
0x666c823  mov rax,[rsi]
0x666da5f  mov rsi,[rsi]
0x666da83  movups xmm0,[rsi]
0x666dd2f  mov rbx,[rsi]
0x666dd82  mov rax,[rsi]
0x666dda3  mov rax,[rsi]
0x666ddbc  mov rax,[rsi]
0x666e111  mov rax,[rsi]
0x666e169  mov rax,[rsi]
0x666e182  mov rax,[rsi]
0x666e1a9  mov rax,[rsi]
0x666e1be  mov rax,[rsi]
0x666e240  mov rdi,[rsi]
0x666ef2a  mov rax,[rsi]
0x666ef3f  mov rax,[rsi]
0x666faf9  mov rax,[rsi]
0x666fb0e  mov rax,[rsi]
0x666fb51  mov rax,[rsi]
0x666fb66  mov rax,[rsi]
0x666fb92  mov rax,[rsi]
0x666fbab  mov rax,[rsi]
0x666fe4b  mov rbx,[rsi]
0x666fe9a  mov rax,[rsi]
0x666feb3  mov rax,[rsi]
0x666fec8  mov rax,[rsi]
0x666feda  mov rax,[rsi]
0x666ff32  mov rax,[rsi]
0x666ff4b  mov rax,[rsi]
0x666ff72  mov rax,[rsi]
0x666ff87  mov rax,[rsi]
0x6670000  mov rdi,[rsi]
0x66700b9  mov rax,[rsi]
0x66700ce  mov rax,[rsi]
0x6670629  mov rax,[rsi]
0x667063e  mov rax,[rsi]
0x6670681  mov rax,[rsi]
0x6670696  mov rax,[rsi]
0x66706ba  mov rax,[rsi]
0x66706cf  mov rax,[rsi]
0x667074b  mov rdi,[rsi]
0x667086f  mov rax,[rsi]
0x6670884  mov rax,[rsi]
0x66708c7  mov rax,[rsi]
0x66708dc  mov rax,[rsi]
0x6670900  mov rax,[rsi]
0x6670915  mov rax,[rsi]
0x6670991  mov rdi,[rsi]
0x666b75b  lock dec dword ptr [rsi+0xC]
0x666b7e9  lock dec dword ptr [rsi+0xC]
0x666b9eb  lock dec dword ptr [rsi+0xC]
0x666badf  lock dec dword ptr [rsi+0xC]
0x666c6d6  lock dec dword ptr [rsi+0xC]
0x666c73d  lock dec dword ptr [rsi+0xC]
0x666c7d1  lock dec dword ptr [rsi+0xC]
0x666c819  lock dec dword ptr [rsi+0xC]
0x666ddb2  lock dec dword ptr [rsi+0xC]
0x666e178  lock dec dword ptr [rsi+0xC]
0x666e1b8  lock dec dword ptr [rsi+0xC]
0x666ef39  lock dec dword ptr [rsi+0xC]
0x666fb08  lock dec dword ptr [rsi+0xC]
0x666fb60  lock dec dword ptr [rsi+0xC]
0x666fba1  lock dec dword ptr [rsi+0xC]
0x666fec2  lock dec dword ptr [rsi+0xC]
0x666ff41  lock dec dword ptr [rsi+0xC]
0x666ff81  lock dec dword ptr [rsi+0xC]
0x66700c8  lock dec dword ptr [rsi+0xC]
0x6670638  lock dec dword ptr [rsi+0xC]
0x6670690  lock dec dword ptr [rsi+0xC]
0x66706c9  lock dec dword ptr [rsi+0xC]
0x667087e  lock dec dword ptr [rsi+0xC]
0x66708d6  lock dec dword ptr [rsi+0xC]
0x667090f  lock dec dword ptr [rsi+0xC]
0x666b945  mov rax,[rsi+0x60]
0x666b949  sub rax,[rsi+0x58]
0x667049a  movss xmm1,[rsi+0x58]
0x666b987  cmp byte ptr [rsi+0x1D4],0
0x666b990  mov edi,[rsi+0x1D0]
0x666cf0c  cmp qword ptr [rsi+0x20],0x10
0x666e3ad  cmp r12,[rsi+0x20]
0x666e3e0  cmp r12,[rsi+0x20]
0x666e3f1  cmp qword ptr [rsi+0x20],0
0x666f104  cmp r12,[rsi+0x20]
0x666f137  cmp r12,[rsi+0x20]
0x666f143  cmp qword ptr [rsi+0x20],0
0x666e3b3  cmp qword ptr [rsi+0x28],0x10
0x666f10a  cmp qword ptr [rsi+0x28],0x10
0x66703ab  movups xmm0,[rsi+0x28]
0x666e3ba  mov rdx,[rsi+0x10]
0x666f111  mov rdx,[rsi+0x10]
0x666fa30  cmp rax,[rsi+0x10]
0x666f57d  mov eax,[rsi+0x788]
0x666f583  sub eax,[rsi+0x780]
0x666f5b5  mov rbx,[rsi+0x770]
0x666f5f5  add qword ptr [rsi+0x770],0x88
0x666f635  mov eax,[rsi+0x770]
0x666f5bc  cmp rbx,[rsi+0x778]
0x666f63b  sub eax,[rsi+0x768]
0x666f674  mov rdx,[rsi+0x758]
0x666f6ee  add qword ptr [rsi+0x758],0x58
0x666f729  mov eax,[rsi+0x758]
0x666f67b  cmp rdx,[rsi+0x760]
0x666f72f  sub eax,[rsi+0x750]
0x666f761  mov rdx,[rsi+0x8A8]
0x666f77b  add qword ptr [rsi+0x8A8],2
0x666f7b5  mov eax,[rsi+0x8A8]
0x666f768  cmp rdx,[rsi+0x8B0]
0x666f7bb  sub eax,[rsi+0x8A0]
0x666f818  mov eax,[rsi+0x650]
0x666f81e  sub eax,[rsi+0x648]
0x666f84c  mov rbx,[rsi+0x500]
0x666f92c  cmp rbx,[rsi+0x500]
0x666f951  mov r8,[rsi+0x500]
0x666fa05  add eax,[rsi+0x500]
0x666f853  cmp rbx,[rsi+0x508]
0x666f984  mov rdx,[rsi+0x508]
0x666f86e  sub r13,[rsi+0x4F8]
0x666f93c  mov rdx,[rsi+0x4F8]
0x666f963  mov rdx,[rsi+0x4F8]
0x666f978  mov rcx,[rsi+0x4F8]
0x666f9fd  mov eax,[rsi+0x4F8]
0x66703b6  movups xmm0,[rsi+0x38]
0x66703c1  movups xmm0,[rsi+0x48]
0x66703e2  movzx eax,word ptr [rsi+0x88]
0x667049f  movsd xmm0,[rsi+0x5C]
0x6670513  cmp byte ptr [rsi+0xC9],1
tag 7 ignored (store/lea) sites:
0x666c57b  mov [rsi],rax
0x666c57e  lea rcx,[rsi+8]
0x666c596  mov [rsi+0x80],rax
0x666dc05  mov [rsi],rsi
0x666dc08  mov [rsi+8],rsi
0x666de2e  movups [rsi],xmm0
0x666de3b  mov [rsi+0xF],rax
0x666de3f  mov byte ptr [rsi+0x17],0
0x666df06  mov qword ptr [rsi+0x18],0
0x666df0e  mov qword ptr [rsi+0x20],9
0x666df16  mov qword ptr [rsi+0x28],0xF
0x666df28  mov [rsi+0x10],rax
0x666df2c  mov byte ptr [rsi+0x18],0x74
0x666df33  movups [rsi+0x30],xmm0
0x666df3e  movups [rsi+0x40],xmm0
0x666df8a  movups [rsi],xmm0
0x666df97  mov [rsi+0xE],rax
0x666df9b  mov byte ptr [rsi+0x16],0
0x666e030  mov qword ptr [rsi+0x18],0
0x666e038  mov qword ptr [rsi+0x20],9
0x666e040  mov qword ptr [rsi+0x28],0xF
0x666e052  mov [rsi+0x10],rax
0x666e056  mov byte ptr [rsi+0x18],0x74
0x666e05d  movups [rsi+0x30],xmm0
0x666e068  movups [rsi+0x40],xmm0
0x666e0b4  movups [rsi],xmm0
0x666e0b7  mov dword ptr [rsi+0x10],0x64657361
0x666e0be  mov byte ptr [rsi+0x14],0
0x666e243  lea rcx,[rsi+0x10]
0x666e3c0  lea rdx,[rsi+0x10]
0x666f117  lea rdx,[rsi+0x10]
0x666f609  lea rcx,[rsi+0x768]
0x666f6f8  lea rcx,[rsi+0x750]
0x666f78c  lea rcx,[rsi+0x8A0]
0x666f85f  mov [rsi+0x500],rbx
0x666f9b8  mov [rsi+0x4F8],r14
0x666f9c2  mov [rsi+0x500],r12
0x666f9cc  mov [rsi+0x508],rdi
0x666fd11  mov [rsi],rsi
0x666fd14  mov [rsi+8],rsi
0x6670003  lea rcx,[rsi+0x10]
0x667074e  lea rcx,[rsi+0x10]
0x6670994  lea rcx,[rsi+0x10]

tag 8 reads:
0x666ccd0  mov rdx,[r15]
0x666cdc9  mov rax,[r15]
0x666cddf  mov rax,[r15]
0x666ccd6  mov rdx,[r15+8]
0x666cd1a  mov rdx,[r15+8]
0x666cdc2  lock dec dword ptr [r15+8]
0x666ccde  movups xmm1,[r15+0x10]
0x666cce3  movups xmm2,[r15+0x20]
0x666cce8  movups xmm3,[r15+0x30]
0x666cced  movups xmm4,[r15+0x40]
0x666cd02  mov rdx,[r15+0x50]
0x666cdd8  lock dec dword ptr [r15+0xC]
tag 8 ignored (store/lea) sites:
0x666b3ba  movups [r15],xmm6
0x666b589  mov [r15],rax
0x666b590  mov [r15+8],rax
0x666b5a4  movups [r15+0x10],xmm0
0x666b5a9  movups [r15+0x20],xmm1
0x666b5ae  movups [r15+0x30],xmm2
0x666b5b3  movups [r15+0x40],xmm3
0x666b5bc  mov [r15+0x50],rax

## TOOL REQUESTS
effB_merge.py (saved at C:\Users\Atomi\AppData\Local\Temp\opencode\effB_merge.py, not in repo because this unit allows only its one output file) | docs/progress/_effB_data.txt -> one markdown row per distinct [reg+off] offset with sites merged and read/store/lea classification | merging 307 data lines by hand did not reconcile site counts; the script did it exactly and is general for any fieldmap-style unit if moved to tools/sigs.
