## NEXT
DONE (tags 5-7 fieldmaps written and verified: python tools/delegate.py check docs/progress/oc_U-D10x3.md -> CHECK OK, 39 rows, verify_oc mismatch=0 no-such-instr=0)

# Editor tags 5-7 fieldmap (checklist D10): editor-group description read lists

## tag 5 (case head 0x6674ac3): one row per distinct [rdi+off] offset
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x3C t5 | 1 | - | 0x6674ac3  cmp byte ptr [rdi+0x3C],1 | compared with 1 |
| 0xC t5 | 8 | - | 0x6674ad7  movsd xmm1,[rdi+0xC] | - |
| 0x14 t5 | 4 | - | 0x6674b05  movss xmm1,[rdi+0x14] | - |
| 0x0 t5 | 8 | - | 0x6674b87  movsd xmm3,[rdi] | - |
| 0x8 t5 | 4 | 0x66779ee | 0x6674b9b  movss xmm3,[rdi+8] | - |
| 0x38 t5 | 4 | 0x66775db | 0x667598b  movss xmm0,[rdi+0x38] | - |
| 0x28 t5 | 16 | - | 0x6675a36  movups xmm0,[rdi+0x28] | - |
| 0x90 t5 | 8 | - | 0x6675af5  lea r8,[rdi+0x90] | - |
| 0xE0 t5 | 2 | 0x6677759 | 0x6675b0c  mov bx,[rdi+0xE0] | - |
| 0x18 t5 | 16 | 0x66779e8 | 0x6677686  movups xmm0,[rdi+0x18] | compared with 2 (byte cmp at 0x66779e8) |
| 0x40 t5 | 8 | - | 0x6677745  lea r8,[rdi+0x40] | - |

verbatim lines (tag 5, for verify):
    0x6674ac3  cmp byte ptr [rdi+0x3C],1
    0x6674ad7  movsd xmm1,[rdi+0xC]
    0x6674b05  movss xmm1,[rdi+0x14]
    0x6674b87  movsd xmm3,[rdi]
    0x6674b9b  movss xmm3,[rdi+8]
    0x667598b  movss xmm0,[rdi+0x38]
    0x6675a36  movups xmm0,[rdi+0x28]
    0x6675af5  lea r8,[rdi+0x90]
    0x6675b0c  mov bx,[rdi+0xE0]
    0x6677686  movups xmm0,[rdi+0x18]
    0x6677745  lea r8,[rdi+0x40]

## tag 6 (case head 0x6674d02): one row per distinct [rdi+off] offset
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x3C t6 | 1 | - | 0x6674d02  cmp byte ptr [rdi+0x3C],1 | compared with 1 |
| 0xC t6 | 8 | - | 0x6674d16  movsd xmm1,[rdi+0xC] | - |
| 0x14 t6 | 4 | - | 0x6674d44  movss xmm1,[rdi+0x14] | - |
| 0x0 t6 | 8 | - | 0x6674dc6  movsd xmm3,[rdi] | - |
| 0x8 t6 | 4 | 0x667cbb6 | 0x6674dda  movss xmm3,[rdi+8] | - |
| 0xE2 t6 | 1 | - | 0x6676eab  cmp byte ptr [rdi+0xE2],1 | compared with 1 |
| 0x38 t6 | 4 | 0x667c1fe, 0x667c7a5 | 0x667a87b  movss xmm0,[rdi+0x38] | - |
| 0x20 t6 | 4 | - | 0x667a926  movss xmm0,[rdi+0x20] | - |
| 0xE4 t6 | 4 | - | 0x667a92b  movss xmm1,[rdi+0xE4] | - |
| 0x18 t6 | 8 | 0x667c850, 0x667cbb0 | 0x667a933  movsd xmm2,[rdi+0x18] | compared with 2 (byte cmp at 0x667cbb0) |
| 0x40 t6 | 8 | 0x667c90f | 0x667aa04  lea r8,[rdi+0x40] | - |
| 0xE0 t6 | 2 | 0x667c37f, 0x667c923 | 0x667aa18  mov r15w,[rdi+0xE0] | - |
| 0xE3 t6 | 1 | - | 0x667c107  cmp byte ptr [rdi+0xE3],1 | compared with 1 |
| 0x28 t6 | 16 | - | 0x667c2a9  movups xmm0,[rdi+0x28] | - |
| 0x90 t6 | 8 | - | 0x667c368  lea r8,[rdi+0x90] | - |

verbatim lines (tag 6, for verify):
    0x6674d02  cmp byte ptr [rdi+0x3C],1
    0x6674d16  movsd xmm1,[rdi+0xC]
    0x6674d44  movss xmm1,[rdi+0x14]
    0x6674dc6  movsd xmm3,[rdi]
    0x6674dda  movss xmm3,[rdi+8]
    0x6676eab  cmp byte ptr [rdi+0xE2],1
    0x667a87b  movss xmm0,[rdi+0x38]
    0x667a926  movss xmm0,[rdi+0x20]
    0x667a92b  movss xmm1,[rdi+0xE4]
    0x667a933  movsd xmm2,[rdi+0x18]
    0x667aa04  lea r8,[rdi+0x40]
    0x667aa18  mov r15w,[rdi+0xE0]
    0x667c107  cmp byte ptr [rdi+0xE3],1
    0x667c2a9  movups xmm0,[rdi+0x28]
    0x667c368  lea r8,[rdi+0x90]

## tag 7 (case head 0x6674760): one row per distinct [rdi+off] offset
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x3C t7 | 1 | - | 0x6674760  cmp byte ptr [rdi+0x3C],1 | compared with 1 |
| 0xC t7 | 8 | - | 0x6674774  movsd xmm1,[rdi+0xC] | - |
| 0x14 t7 | 4 | - | 0x66747a2  movss xmm1,[rdi+0x14] | - |
| 0x0 t7 | 8 | - | 0x6674824  movsd xmm3,[rdi] | - |
| 0x8 t7 | 4 | 0x667b244 | 0x6674838  movss xmm3,[rdi+8] | - |
| 0x3D t7 | 1 | - | 0x66755d5  cmp byte ptr [rdi+0x3D],1 | compared with 1 |
| 0x34 t7 | 4 | - | 0x66755df  movss xmm0,[rdi+0x34] | - |
| 0x28 t7 | 16 | - | 0x6677105  movups xmm0,[rdi+0x28] | - |
| 0x90 t7 | 8 | - | 0x66771c4  lea r8,[rdi+0x90] | - |
| 0xE0 t7 | 2 | 0x667afb1 | 0x66771db  mov r15w,[rdi+0xE0] | - |
| 0x3E t7 | 1 | - | 0x667ad48  cmp byte ptr [rdi+0x3E],1 | compared with 1 |
| 0x18 t7 | 16 | 0x667b23e | 0x667aede  movups xmm0,[rdi+0x18] | compared with 2 (byte cmp at 0x667b23e) |
| 0x40 t7 | 8 | - | 0x667af9d  lea r8,[rdi+0x40] | - |

verbatim lines (tag 7, for verify):
    0x6674760  cmp byte ptr [rdi+0x3C],1
    0x6674774  movsd xmm1,[rdi+0xC]
    0x66747a2  movss xmm1,[rdi+0x14]
    0x6674824  movsd xmm3,[rdi]
    0x6674838  movss xmm3,[rdi+8]
    0x66755d5  cmp byte ptr [rdi+0x3D],1
    0x66755df  movss xmm0,[rdi+0x34]
    0x6677105  movups xmm0,[rdi+0x28]
    0x66771c4  lea r8,[rdi+0x90]
    0x66771db  mov r15w,[rdi+0xE0]
    0x667ad48  cmp byte ptr [rdi+0x3E],1
    0x667aede  movups xmm0,[rdi+0x18]
    0x667af9d  lea r8,[rdi+0x40]

## TOOL REQUESTS
None
