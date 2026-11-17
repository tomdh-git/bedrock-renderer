## NEXT
DONE

# ChunkGeometry extractor 0x66EA3D0 (tag 0, checklist D5b/L4f): description read list fieldmap (reg r12)

## tag 0 (one table per tag)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0xB8 | 1 | 0x66ea6e4 | 0x66ea56e  movzx eax,byte ptr [r12+0xB8] | - |
| 0x48 | 8 | 0x66ea6dc, 0x66ea7f3 | 0x66ea58f  mov rax,[r12+0x48] | - |
| 0x50 | 1 | - | 0x66ea5ba  cmp byte ptr [r12+0x50],0 | compared with 0 |
| 0xE0 | 1 | - | 0x66ea65c  movzx ebx,byte ptr [r12+0xE0] | - |
| 0xD8 | 1 | - | 0x66ea72e  cmp byte ptr [r12+0xD8],3 | compared with 3 |
| 0xE1 | 1 | - | 0x66ea76f  cmp byte ptr [r12+0xE1],0 | compared with 0 |
| 0x8 | 8 | 0x66ef6eb, 0x66f0b87, 0x66f0ba8, 0x66f1990, 0x66f19b1, 0x66f2aba, 0x66f2beb | 0x66ef5ba  lea rdx,[r12+8] | [I] later sites: lock dec dword (atomic) at +8 and add qword [r12+8],0xC8 [UNVERIFIED: r12 reused] |
| 0x28 | 8 | 0x66f2aff | 0x66ef5ff  mov rdx,[r12+0x28] | - [UNVERIFIED: r12 reused] |
| 0x10 | 8 | 0x66f0b8c, 0x66f1995, 0x66f2b0c | 0x66ef60c  cmp rcx,[r12+0x10] | compared with rcx [UNVERIFIED: r12 reused] |
| 0x0 | 8 | 0x66ef713, 0x66f2bf7, 0x66f2c13 | 0x66ef6f7  mov rax,[r12] | - [UNVERIFIED: r12 reused] |
| 0xC | 8 | 0x66f2c07 | 0x66ef707  lock dec dword ptr [r12+0xC] | lock dec dword (atomic) [UNVERIFIED: r12 reused] |
| 0x8A8 | 8 | 0x66f0601, 0x66f063d, 0x66f14ac, 0x66f14c8, 0x66f1504 | 0x66f05e5  mov rdx,[r12+0x8A8] | [I] queue cursor: cmp vs [r12+0x8B0], add qword [r12+0x8A8],2, sub [r12+0x8A0] [UNVERIFIED: r12 reused] |
| 0x8B0 | 8 | 0x66f14b4 | 0x66f05ed  cmp rdx,[r12+0x8B0] | compared with cursor [r12+0x8A8] [UNVERIFIED: r12 reused] |
| 0x8A0 | 8 | 0x66f0645, 0x66f14d3, 0x66f150c | 0x66f060c  lea rcx,[r12+0x8A0] | [I] base: sub eax,[r12+0x8A0] after mov eax,[r12+0x8A8] [UNVERIFIED: r12 reused] |
| 0x758 | 8 | 0x66f0704, 0x66f074b, 0x66f153c, 0x66f15cb, 0x66f1612 | 0x66f0675  mov rdx,[r12+0x758] | [I] queue cursor: cmp vs [r12+0x760], add qword [r12+0x758],0x58, sub [r12+0x750] [UNVERIFIED: r12 reused] |
| 0x760 | 8 | 0x66f1544 | 0x66f067d  cmp rdx,[r12+0x760] | compared with cursor [r12+0x758] [UNVERIFIED: r12 reused] |
| 0x750 | 8 | 0x66f0753, 0x66f15d6, 0x66f161a | 0x66f070f  lea rcx,[r12+0x750] | [I] base: sub eax,[r12+0x750] after mov eax,[r12+0x758] [UNVERIFIED: r12 reused] |
| 0x890 | 8 | 0x66f079f, 0x66f07dd, 0x66f1651, 0x66f1666, 0x66f16a4 | 0x66f078a  mov rdx,[r12+0x890] | read+store (mov [r12+0x890],rdx); add eax with [r12+0x888] [UNVERIFIED: r12 reused] |
| 0x898 | 8 | 0x66f1659 | 0x66f0792  cmp rdx,[r12+0x898] | compared with cursor [r12+0x890] [UNVERIFIED: r12 reused] |
| 0x888 | 4 | 0x66f07d3, 0x66f1670, 0x66f169a | 0x66f07a9  lea rcx,[r12+0x888] | [I] base: mov eax,[r12+0x888]; add eax,[r12+0x890] [UNVERIFIED: r12 reused] |
| 0x7A0 | 8 | 0x66f081e, 0x66f0867, 0x66f16d0, 0x66f16e5, 0x66f1723 | 0x66f0809  mov rdx,[r12+0x7A0] | read+store (mov [r12+0x7A0],rdx); add eax with [r12+0x798] [UNVERIFIED: r12 reused] |
| 0x7A8 | 8 | 0x66f16d8 | 0x66f0811  cmp rdx,[r12+0x7A8] | compared with cursor [r12+0x7A0] [UNVERIFIED: r12 reused] |
| 0x798 | 4 | 0x66f085d, 0x66f16ef, 0x66f1719 | 0x66f0828  lea rcx,[r12+0x798] | [I] base: mov eax,[r12+0x798]; add eax,[r12+0x7A0] [UNVERIFIED: r12 reused] |
| 0x648 | 8 | 0x66f08cb, 0x66f174e, 0x66f1787 | 0x66f0892  lea rcx,[r12+0x648] | [I] base: sub eax,[r12+0x648] after mov eax,[r12+0x650] [UNVERIFIED: r12 reused] |
| 0x650 | 4 | 0x66f177f | 0x66f08c3  mov eax,[r12+0x650] | [I] cursor vs base [r12+0x648]; no end cmp seen [UNVERIFIED: r12 reused] |
| 0x780 | 8 | 0x66f0902, 0x66f17a1, 0x66f17c9 | 0x66f08e5  lea rcx,[r12+0x780] | [I] base: sub eax,[r12+0x780] after mov eax,[r12+0x788] [UNVERIFIED: r12 reused] |
| 0x788 | 4 | 0x66f17c1 | 0x66f08fa  mov eax,[r12+0x788] | [I] cursor vs base [r12+0x780]; no end cmp seen [UNVERIFIED: r12 reused] |
| 0x770 | 8 | 0x66f097f, 0x66f09cc, 0x66f1800, 0x66f1846, 0x66f1888 | 0x66f0939  mov rbx,[r12+0x770] | [I] queue cursor: cmp vs [r12+0x778], add qword [r12+0x770],0x88, sub [r12+0x768] [UNVERIFIED: r12 reused] |
| 0x778 | 8 | 0x66f1808 | 0x66f0941  cmp rbx,[r12+0x778] | compared with cursor [r12+0x770] [UNVERIFIED: r12 reused] |
| 0x768 | 4 | 0x66f09d4, 0x66f1854, 0x66f1890 | 0x66f098d  lea rcx,[r12+0x768] | [I] base: sub eax,[r12+0x768] after mov eax,[r12+0x770] [UNVERIFIED: r12 reused] |
| 0x680 | 8 | 0x66f0a43, 0x66f0a7f | 0x66f0a0b  mov rdx,[r12+0x680] | [I] queue cursor: cmp vs [r12+0x688], add qword [r12+0x680],0xC, sub [r12+0x678] [UNVERIFIED: r12 reused] |
| 0x688 | 8 | - | 0x66f0a13  cmp rdx,[r12+0x688] | compared with cursor [r12+0x680] [UNVERIFIED: r12 reused] |
| 0x678 | 4 | 0x66f0a87 | 0x66f0a4e  lea rcx,[r12+0x678] | [I] base: sub eax,[r12+0x678] after mov eax,[r12+0x680] [UNVERIFIED: r12 reused] |
| 0x2D8 | 8 | 0x66f0ad3, 0x66f0b11, 0x66f18c7, 0x66f18dc, 0x66f191a | 0x66f0abe  mov rdx,[r12+0x2D8] | read+store (mov [r12+0x2D8],rdx); add eax with [r12+0x2D0] [UNVERIFIED: r12 reused] |
| 0x2E0 | 8 | 0x66f18cf | 0x66f0ac6  cmp rdx,[r12+0x2E0] | compared with cursor [r12+0x2D8] [UNVERIFIED: r12 reused] |
| 0x2D0 | 4 | 0x66f0b07, 0x66f18e6, 0x66f1910 | 0x66f0add  lea rcx,[r12+0x2D0] | [I] base: mov eax,[r12+0x2D0]; add eax,[r12+0x2D8] [UNVERIFIED: r12 reused] |
| 0x5D8 | 4 | 0x66f1951 | 0x66f0b48  mov eax,[r12+0x5D8] | [I] cursor vs base [r12+0x5D0]; no end cmp seen [UNVERIFIED: r12 reused] |
| 0x5D0 | 4 | 0x66f1959 | 0x66f0b50  sub eax,[r12+0x5D0] | [I] base: subtracted from cursor [r12+0x5D8] [UNVERIFIED: r12 reused] |
### writes to the register (r12) — overwrite sites flagged by the data file
First write is the entry copy of the description pointer (r8 -> r12); reads before the next write are valid:

    0x66ea44a  mov r12,r8
    0x66eaca4  mov r12,[rax]
    0x66ef59e  mov r12,[rcx+0x28]
    0x66ef621  xor r12d,r12d
    0x66ef6db  mov r12,[rbp+0x1448]
    0x66ef7e1  lea r12,[rbp+0x1130]
    0x66f0566  mov r12,rax
    0x66f0be6  lea r12,[rbp+0x1130]
    0x66f142d  mov r12,rax
    0x66f19ef  lea r12,[rbp+0x1130]
    0x66f2a9e  mov r12,[rcx+0x28]
    0x66f2b21  xor r12d,r12d
    0x66f2bdb  mov r12,[rbp+0x1448]
    0x66f2ca1  lea r12,[rbp+0x1050]

Flagged read lines (possibly after a register overwrite -> rows marked [UNVERIFIED: r12 reused]): all 114 sites at 0x66ef5ba and later, i.e. every site in the read address column of the rows for 0x8, 0x28, 0x10, 0x0, 0xC, 0x8A8, 0x8B0, 0x8A0, 0x758, 0x760, 0x750, 0x890, 0x898, 0x888, 0x7A0, 0x7A8, 0x798, 0x648, 0x650, 0x780, 0x788, 0x770, 0x778, 0x768, 0x680, 0x688, 0x678, 0x2D8, 0x2E0, 0x2D0, 0x5D8, 0x5D0. Each such site address lies after at least one of the 13 non-entry writes above (first one: 0x66eaca4). The 9 sites of the 0xB8, 0x48, 0x50, 0xE0, 0xD8, 0xE1 rows (0x66ea56e..0x66ea7f3) lie between the entry copy 0x66ea44a and the first overwrite 0x66eaca4 and are NOT flagged. The data file gives no basic-block structure, so flagging is address-order only [UNVERIFIED: r12 reused block membership].

### verbatim first instruction per offset (quoted for verify)
    0x66ea56e  movzx eax,byte ptr [r12+0xB8]
    0x66ea58f  mov rax,[r12+0x48]
    0x66ea5ba  cmp byte ptr [r12+0x50],0
    0x66ea65c  movzx ebx,byte ptr [r12+0xE0]
    0x66ea72e  cmp byte ptr [r12+0xD8],3
    0x66ea76f  cmp byte ptr [r12+0xE1],0
    0x66ef5ba  lea rdx,[r12+8]
    0x66ef5ff  mov rdx,[r12+0x28]
    0x66ef60c  cmp rcx,[r12+0x10]
    0x66ef6f7  mov rax,[r12]
    0x66ef707  lock dec dword ptr [r12+0xC]
    0x66f05e5  mov rdx,[r12+0x8A8]
    0x66f05ed  cmp rdx,[r12+0x8B0]
    0x66f060c  lea rcx,[r12+0x8A0]
    0x66f0675  mov rdx,[r12+0x758]
    0x66f067d  cmp rdx,[r12+0x760]
    0x66f070f  lea rcx,[r12+0x750]
    0x66f078a  mov rdx,[r12+0x890]
    0x66f0792  cmp rdx,[r12+0x898]
    0x66f07a9  lea rcx,[r12+0x888]
    0x66f0809  mov rdx,[r12+0x7A0]
    0x66f0811  cmp rdx,[r12+0x7A8]
    0x66f0828  lea rcx,[r12+0x798]
    0x66f0892  lea rcx,[r12+0x648]
    0x66f08c3  mov eax,[r12+0x650]
    0x66f08e5  lea rcx,[r12+0x780]
    0x66f08fa  mov eax,[r12+0x788]
    0x66f0939  mov rbx,[r12+0x770]
    0x66f0941  cmp rbx,[r12+0x778]
    0x66f098d  lea rcx,[r12+0x768]
    0x66f0a0b  mov rdx,[r12+0x680]
    0x66f0a13  cmp rdx,[r12+0x688]
    0x66f0a4e  lea rcx,[r12+0x678]
    0x66f0abe  mov rdx,[r12+0x2D8]
    0x66f0ac6  cmp rdx,[r12+0x2E0]
    0x66f0add  lea rcx,[r12+0x2D0]
    0x66f0b48  mov eax,[r12+0x5D8]
    0x66f0b50  sub eax,[r12+0x5D0]

## TOOL REQUESTS
None
