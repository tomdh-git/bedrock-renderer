## NEXT
DONE: field maps for tags 0/1/2/4 written and check passed

# U-ItmA — GROUP visitor description-read field maps (tags 0 EnvText, 1 Nametag, 2 MeshFallback, 4 ChunkOccluders)

Data source: docs/progress/_itemA_data.txt (orchestrator-computed `[reg+off]` access lists per tag; reg from tag header). One row per distinct offset per tag. "read address" column = RVAs of every further site of that offset after the first; the first site is given verbatim in the table and repeated as an indented `0xRVA  instr` line under each table (for tools/sigs/verify_oc.py). Sizes are from the instruction (movups/movdqu 16, movsd 8, qword 8, dword/movss 4, word 2, byte 1; lea = 8-byte address-of, no load). Meaning only where an instruction shows it, else '-'. No line not read from the tag's own pointer register (rsi/rdi per header) appears in the data.

## tag 0 — head 0x6646a10, reg rsi (EnvText)

| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t0) | 8 | 0x6647d17, 0x664824b, 0x66491bf, 0x664c222, 0x664c237, 0x664c27a, 0x664c28f, 0x664c2b3, 0x664c2c8, 0x664e44b, 0x664e460, 0x664e4a5, 0x664e4ba, 0x664e6a3, 0x664e6b8, 0x664e710, 0x664e734, 0x664e749, 0x664e76b, 0x664e780, 0x664e7a2, 0x664e7b7, 0x664e7d9, 0x664e7ee, 0x664e810, 0x664e825, 0x664e844, 0x664e859, 0x664e87b, 0x664e890, 0x664e8b2, 0x664e8c7, 0x664e8f8, 0x664e90d, 0x664e94a, 0x664e95f, 0x664e98b, 0x664e9a4 | 0x6647ccb  mov rbx,[rsi] | - |
| 0x8 (t0) | 8 | 0x6647d1a, 0x664c21c, 0x664c274, 0x664c2ad, 0x664e445, 0x664e49f, 0x664e69d, 0x664e6f5, 0x664e72e, 0x664e765, 0x664e79c, 0x664e7d3, 0x664e80a, 0x664e83e, 0x664e875, 0x664e8ac, 0x664e8f2, 0x664e944, 0x664e981 | 0x6647d06  mov rax,[rsi+8] | sites vary: 8-byte loads, atomic dword dec (lock dec) |
| 0xC (t0) | 4 | 0x664c289, 0x664c2c2, 0x664e45a, 0x664e4b4, 0x664e6b2, 0x664e70a, 0x664e743, 0x664e77a, 0x664e7b1, 0x664e7e8, 0x664e81f, 0x664e853, 0x664e88a, 0x664e8c1, 0x664e907, 0x664e959, 0x664e99a | 0x664c231  lock dec dword ptr [rsi+0xC] | atomic dword dec |
| 0x10 (t0) | 8 | - | 0x664e3c8  add rcx,[rsi+0x10] | - |
| 0x28 (t0) | 8 | - | 0x664998f  cmp [rsi+0x28],r10 | - |

    0x6647ccb  mov rbx,[rsi]
    0x6647d06  mov rax,[rsi+8]
    0x664c231  lock dec dword ptr [rsi+0xC]
    0x664e3c8  add rcx,[rsi+0x10]
    0x664998f  cmp [rsi+0x28],r10

## tag 1 — head 0x6646f5b, reg rsi (Nametag)

| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t1) | 8 | 0x6647d17, 0x664824b, 0x66491bf, 0x664c222, 0x664c237, 0x664c27a, 0x664c28f, 0x664c2b3, 0x664c2c8, 0x664d405, 0x664d41a, 0x664d45d, 0x664d472, 0x664d496, 0x664d4ab, 0x664e44b, 0x664e460, 0x664e4a5, 0x664e4ba, 0x664e6a3, 0x664e6b8, 0x664e710, 0x664e734, 0x664e749, 0x664e76b, 0x664e780, 0x664e7a2, 0x664e7b7, 0x664e7d9, 0x664e7ee, 0x664e810, 0x664e825, 0x664e844, 0x664e859, 0x664e87b, 0x664e890, 0x664e8b2, 0x664e8c7, 0x664e8f8, 0x664e90d, 0x664e94a, 0x664e95f, 0x664e98b, 0x664e9a4 | 0x6647ccb  mov rbx,[rsi] | - |
| 0x8 (t1) | 8 | 0x6647d1a, 0x664c21c, 0x664c274, 0x664c2ad, 0x664d330, 0x664d34f, 0x664d3ff, 0x664d457, 0x664d490, 0x664e445, 0x664e49f, 0x664e69d, 0x664e6f5, 0x664e72e, 0x664e765, 0x664e79c, 0x664e7d3, 0x664e80a, 0x664e83e, 0x664e875, 0x664e8ac, 0x664e8f2, 0x664e944, 0x664e981 | 0x6647d06  mov rax,[rsi+8] | sites vary: 8-byte loads, qword += 0xC8, atomic dword dec (lock dec) |
| 0xC (t1) | 4 | 0x664c289, 0x664c2c2, 0x664d414, 0x664d46c, 0x664d4a5, 0x664e45a, 0x664e4b4, 0x664e6b2, 0x664e70a, 0x664e743, 0x664e77a, 0x664e7b1, 0x664e7e8, 0x664e81f, 0x664e853, 0x664e88a, 0x664e8c1, 0x664e907, 0x664e959, 0x664e99a | 0x664c231  lock dec dword ptr [rsi+0xC] | atomic dword dec |
| 0x10 (t1) | 8 | 0x664e3c8 | 0x664d334  cmp rax,[rsi+0x10] | - |
| 0x28 (t1) | 8 | - | 0x664998f  cmp [rsi+0x28],r10 | - |
| 0x788 (t1) | 4 | - | 0x664ce91  mov eax,[rsi+0x788] | - |
| 0x780 (t1) | 4 | - | 0x664ce97  sub eax,[rsi+0x780] | - |
| 0x8A8 (t1) | 8 | 0x664cee6, 0x664cf2b | 0x664cecc  mov rdx,[rsi+0x8A8] | sites vary: 8-byte load, qword += 2, dword read |
| 0x8B0 (t1) | 8 | - | 0x664ced3  cmp rdx,[rsi+0x8B0] | - |
| 0x8A0 (t1) | 8 | 0x664cf31 | 0x664cef7  lea rcx,[rsi+0x8A0] | address-of (lea); dword read at 2nd site |
| 0x770 (t1) | 8 | 0x664cf9f, 0x664cfdf | 0x664cf5f  mov rbx,[rsi+0x770] | sites vary: 8-byte load, qword += 0x88, dword read |
| 0x778 (t1) | 8 | - | 0x664cf66  cmp rbx,[rsi+0x778] | - |
| 0x768 (t1) | 8 | 0x664cfe5 | 0x664cfb3  lea rcx,[rsi+0x768] | address-of (lea); dword read at 2nd site |
| 0x758 (t1) | 8 | 0x664d09b, 0x664d0ce | 0x664d021  mov rdx,[rsi+0x758] | sites vary: 8-byte load, qword += 0x58, dword read |
| 0x760 (t1) | 8 | - | 0x664d028  cmp rdx,[rsi+0x760] | - |
| 0x750 (t1) | 8 | 0x664d0d4 | 0x664d0a5  lea rcx,[rsi+0x750] | address-of (lea); dword read at 2nd site |
| 0x648 (t1) | 8 | 0x664d149 | 0x664d10f  lea rcx,[rsi+0x648] | address-of (lea); dword read at 2nd site |
| 0x650 (t1) | 4 | - | 0x664d143  mov eax,[rsi+0x650] | - |
| 0xC8 (t1) | 8 | 0x664d191, 0x664d1d6 | 0x664d17e  mov rdx,[rsi+0xC8] | sites vary: 8-byte load, 8-byte store of rdx, dword add |
| 0xD0 (t1) | 8 | - | 0x664d185  cmp rdx,[rsi+0xD0] | - |
| 0xC0 (t1) | 8 | 0x664d1ce | 0x664d19a  lea rcx,[rsi+0xC0] | address-of (lea); dword read at 2nd site |
| 0x830 (t1) | 8 | 0x664d213, 0x664d24d | 0x664d200  mov rdx,[rsi+0x830] | sites vary: 8-byte load, 8-byte store of rdx, dword add |
| 0x838 (t1) | 8 | - | 0x664d207  cmp rdx,[rsi+0x838] | - |
| 0x828 (t1) | 8 | 0x664d245 | 0x664d21c  lea rcx,[rsi+0x828] | address-of (lea); dword read at 2nd site |
| 0x680 (t1) | 8 | 0x664d2ad, 0x664d2f5 | 0x664d277  mov rdx,[rsi+0x680] | sites vary: 8-byte load, qword += 0xC, dword read |
| 0x688 (t1) | 8 | - | 0x664d27e  cmp rdx,[rsi+0x688] | - |
| 0x678 (t1) | 4 | - | 0x664d2fb  sub eax,[rsi+0x678] | - |

    0x6647ccb  mov rbx,[rsi]
    0x6647d06  mov rax,[rsi+8]
    0x664c231  lock dec dword ptr [rsi+0xC]
    0x664d334  cmp rax,[rsi+0x10]
    0x664998f  cmp [rsi+0x28],r10
    0x664ce91  mov eax,[rsi+0x788]
    0x664ce97  sub eax,[rsi+0x780]
    0x664cecc  mov rdx,[rsi+0x8A8]
    0x664ced3  cmp rdx,[rsi+0x8B0]
    0x664cef7  lea rcx,[rsi+0x8A0]
    0x664cf5f  mov rbx,[rsi+0x770]
    0x664cf66  cmp rbx,[rsi+0x778]
    0x664cfb3  lea rcx,[rsi+0x768]
    0x664d021  mov rdx,[rsi+0x758]
    0x664d028  cmp rdx,[rsi+0x760]
    0x664d0a5  lea rcx,[rsi+0x750]
    0x664d10f  lea rcx,[rsi+0x648]
    0x664d143  mov eax,[rsi+0x650]
    0x664d17e  mov rdx,[rsi+0xC8]
    0x664d185  cmp rdx,[rsi+0xD0]
    0x664d19a  lea rcx,[rsi+0xC0]
    0x664d200  mov rdx,[rsi+0x830]
    0x664d207  cmp rdx,[rsi+0x838]
    0x664d21c  lea rcx,[rsi+0x828]
    0x664d277  mov rdx,[rsi+0x680]
    0x664d27e  cmp rdx,[rsi+0x688]
    0x664d2fb  sub eax,[rsi+0x678]

## tag 2 — head 0x6646c8d, reg rdi (MeshFallback)

| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x108 (t2) | 8 | 0x6646cb1, 0x6649ea2 | 0x6646c94  mov rax,[rdi+0x108] | 8-byte loads; address-of (lea) at 2nd site |
| 0xE0 (t2) | 1 | 0x6649bca | 0x6646cc4  cmp byte ptr [rdi+0xE0],0 | - |
| 0x8 (t2) | 8 | 0x66499a9, 0x664bd1e, 0x664c26b, 0x664e496, 0x664e6ec, 0x664e93b, 0x664e9ed, 0x664eb25 | 0x6648b3a  lea r15,[rdi+8] | address-of (lea); 8-byte loads and atomic dword dec at later sites |
| 0x0 (t2) | 8 | 0x6648beb, 0x6648c88, 0x6649b83, 0x6649bab, 0x6649e41, 0x664a549, 0x664bccf, 0x664bd24, 0x664bd39, 0x664cd16, 0x664e62b | 0x6648bd7  mov r9,[rdi] | 8-byte loads; 16-byte store (movdqu) at last site |
| 0x18 (t2) | 8 | 0x6648ca0, 0x6649c19, 0x664c265, 0x664e490, 0x664e6e6, 0x664e935, 0x664eb1f | 0x6648c3e  mov rax,[rdi+0x18] | sites vary: 8-byte loads, 8-byte load (xmm), byte cmp vs 2 |
| 0x20 (t2) | 1 | 0x6649c33, 0x664a6d4 | 0x6648c9c  movzx esi,byte ptr [rdi+0x20] | sites vary: byte read, 16-byte load, byte cmp vs 1 |
| 0x64 (t2) | 16 | - | 0x6649242  movups xmm0,[rdi+0x64] | - |
| 0x8C (t2) | 16 | - | 0x6649641  movups xmm0,[rdi+0x8C] | - |
| 0x9C (t2) | 8 | - | 0x66496ce  movsd xmm0,[rdi+0x9C] | - |
| 0xA4 (t2) | 16 | - | 0x664975c  movups xmm0,[rdi+0xA4] | - |
| 0xB4 (t2) | 16 | - | 0x66497e9  movups xmm0,[rdi+0xB4] | - |
| 0xCC (t2) | 4 | - | 0x664987a  movss xmm0,[rdi+0xCC] | - |
| 0xC4 (t2) | 8 | - | 0x6649882  movsd xmm1,[rdi+0xC4] | - |
| 0x78 (t2) | 8 | - | 0x6649915  lea r12,[rdi+0x78] | address-of (lea) |
| 0x88 (t2) | 1 | 0x664cd7d | 0x6649ae5  cmp byte ptr [rdi+0x88],0 | sites vary: byte cmp vs 0, qword cmp vs 0 |
| 0xD0 (t2) | 16 | 0x664c77a, 0x664c89c | 0x6649bda  movups xmm0,[rdi+0xD0] | sites vary: 16-byte load, 4-byte loads (xmm) |
| 0x58 (t2) | 4 | - | 0x6649c0f  movss xmm2,[rdi+0x58] | - |
| 0x5C (t2) | 8 | - | 0x6649c14  movsd xmm1,[rdi+0x5C] | - |
| 0x1C (t2) | 4 | - | 0x6649c1e  movss xmm4,[rdi+0x1C] | - |
| 0x30 (t2) | 16 | - | 0x6649c3e  movups xmm5,[rdi+0x30] | - |
| 0x40 (t2) | 16 | - | 0x6649c49  movups xmm6,[rdi+0x40] | - |
| 0x50 (t2) | 8 | - | 0x6649c54  movsd xmm7,[rdi+0x50] | - |
| 0xE4 (t2) | 2 | - | 0x6649c7c  mov si,[rdi+0xE4] | - |
| 0xDC (t2) | 1 | 0x664a10e, 0x664c671 | 0x664a040  movzx eax,byte ptr [rdi+0xDC] | byte read and byte cmp vs 1 |
| 0xDD (t2) | 1 | 0x664c7c9 | 0x664a063  cmp byte ptr [rdi+0xDD],0 | byte cmp vs 0 and vs 1 |
| 0x1A0 (t2) | 1 | 0x664c67e | 0x664a11b  cmp byte ptr [rdi+0x1A0],3 | byte cmp vs 3 and byte read |
| 0x188 (t2) | 4 | 0x664c6b0 | 0x664a13f  mov eax,[rdi+0x188] | sites vary: dword read, 8-byte read |
| 0x18C (t2) | 4 | - | 0x664a14b  mov eax,[rdi+0x18C] | - |
| 0x134 (t2) | 4 | - | 0x664a283  movss xmm0,[rdi+0x134] | - |
| 0x164 (t2) | 1 | - | 0x664a574  cmp byte ptr [rdi+0x164],1 | - |
| 0x154 (t2) | 16 | - | 0x664a584  movups xmm0,[rdi+0x154] | - |
| 0x22 (t2) | 2 | 0x664a97b, 0x664a97c, 0x664bcca | 0x664a73a  mov di,[rdi+0x22] | sites vary: 2-byte reads; 4-byte read at 0x664a97c |
| 0xC (t2) | 4 | - | 0x664bd33  lock dec dword ptr [rdi+0xC] | atomic dword dec |
| 0x89 (t2) | 1 | - | 0x664c06b  cmp byte ptr [rdi+0x89],1 | - |
| 0x168 (t2) | 2 | - | 0x664c428  movzx eax,word ptr [rdi+0x168] | - |
| 0x90 (t2) | 16 | - | 0x664c4dd  movups xmm0,[rdi+0x90] | - |
| 0xA0 (t2) | 16 | - | 0x664c4e8  movups xmm0,[rdi+0xA0] | - |
| 0xB0 (t2) | 16 | - | 0x664c4f3  movups xmm0,[rdi+0xB0] | - |
| 0xC0 (t2) | 16 | 0x664ecdc | 0x664c4fe  movups xmm0,[rdi+0xC0] | sites vary: 16-byte load, 8-byte load |
| 0x1A8 (t2) | 16 | - | 0x664c55d  movups xmm2,[rdi+0x1A8] | - |
| 0x1B8 (t2) | 8 | - | 0x664c564  movsd xmm1,[rdi+0x1B8] | - |
| 0x1C0 (t2) | 16 | - | 0x664c56c  movups xmm0,[rdi+0x1C0] | - |
| 0xD4 (t2) | 8 | 0x664c8a4 | 0x664c782  movsd xmm0,[rdi+0xD4] | - |
| 0xDE (t2) | 1 | - | 0x664c878  cmp byte ptr [rdi+0xDE],1 | - |
| 0x190 (t2) | 8 | - | 0x664cbe2  lea rdx,[rdi+0x190] | address-of (lea) |
| 0x10 (t2) | 8 | 0x664cda6, 0x664e62f | 0x664cd95  mov rax,[rdi+0x10] | 8-byte loads; 8-byte store of 0 at last site |
| 0xDF (t2) | 1 | - | 0x664ea06  cmp byte ptr [rdi+0xDF],1 | - |
| 0xC8 (t2) | 4 | - | 0x664ecd4  movss xmm0,[rdi+0xC8] | - |

    0x6646c94  mov rax,[rdi+0x108]
    0x6646cc4  cmp byte ptr [rdi+0xE0],0
    0x6648b3a  lea r15,[rdi+8]
    0x6648bd7  mov r9,[rdi]
    0x6648c3e  mov rax,[rdi+0x18]
    0x6648c9c  movzx esi,byte ptr [rdi+0x20]
    0x6649242  movups xmm0,[rdi+0x64]
    0x6649641  movups xmm0,[rdi+0x8C]
    0x66496ce  movsd xmm0,[rdi+0x9C]
    0x664975c  movups xmm0,[rdi+0xA4]
    0x66497e9  movups xmm0,[rdi+0xB4]
    0x664987a  movss xmm0,[rdi+0xCC]
    0x6649882  movsd xmm1,[rdi+0xC4]
    0x6649915  lea r12,[rdi+0x78]
    0x6649ae5  cmp byte ptr [rdi+0x88],0
    0x6649bda  movups xmm0,[rdi+0xD0]
    0x6649c0f  movss xmm2,[rdi+0x58]
    0x6649c14  movsd xmm1,[rdi+0x5C]
    0x6649c1e  movss xmm4,[rdi+0x1C]
    0x6649c3e  movups xmm5,[rdi+0x30]
    0x6649c49  movups xmm6,[rdi+0x40]
    0x6649c54  movsd xmm7,[rdi+0x50]
    0x6649c7c  mov si,[rdi+0xE4]
    0x664a040  movzx eax,byte ptr [rdi+0xDC]
    0x664a063  cmp byte ptr [rdi+0xDD],0
    0x664a11b  cmp byte ptr [rdi+0x1A0],3
    0x664a13f  mov eax,[rdi+0x188]
    0x664a14b  mov eax,[rdi+0x18C]
    0x664a283  movss xmm0,[rdi+0x134]
    0x664a574  cmp byte ptr [rdi+0x164],1
    0x664a584  movups xmm0,[rdi+0x154]
    0x664a73a  mov di,[rdi+0x22]
    0x664bd33  lock dec dword ptr [rdi+0xC]
    0x664c06b  cmp byte ptr [rdi+0x89],1
    0x664c428  movzx eax,word ptr [rdi+0x168]
    0x664c4dd  movups xmm0,[rdi+0x90]
    0x664c4e8  movups xmm0,[rdi+0xA0]
    0x664c4f3  movups xmm0,[rdi+0xB0]
    0x664c4fe  movups xmm0,[rdi+0xC0]
    0x664c55d  movups xmm2,[rdi+0x1A8]
    0x664c564  movsd xmm1,[rdi+0x1B8]
    0x664c56c  movups xmm0,[rdi+0x1C0]
    0x664c782  movsd xmm0,[rdi+0xD4]
    0x664c878  cmp byte ptr [rdi+0xDE],1
    0x664cbe2  lea rdx,[rdi+0x190]
    0x664cd95  mov rax,[rdi+0x10]
    0x664ea06  cmp byte ptr [rdi+0xDF],1
    0x664ecd4  movss xmm0,[rdi+0xC8]

## tag 4 — head 0x6646a89, reg rsi (ChunkOccluders)

| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t4) | 8 | 0x6646b75, 0x66477ce, 0x6647e20, 0x664e20e, 0x664e223, 0x664e266, 0x664e27b, 0x664e98b, 0x664e9a4, 0x664eadc, 0x664eaf1, 0x664eb34, 0x664eb49, 0x664eb6d, 0x664eb82 | 0x6646b29  mov rbx,[rsi] | - |
| 0x8 (t4) | 8 | 0x6646b78, 0x664e18f, 0x664e1ae, 0x664e208, 0x664e260, 0x664e981, 0x664ead6, 0x664eb2e, 0x664eb67 | 0x6646b64  mov rax,[rsi+8] | sites vary: 8-byte loads, qword += 0xC8, atomic dword dec (lock dec) |
| 0xC (t4) | 4 | 0x664e275, 0x664e99a, 0x664eaeb, 0x664eb43, 0x664eb7c | 0x664e21d  lock dec dword ptr [rsi+0xC] | atomic dword dec |
| 0x10 (t4) | 8 | - | 0x664e193  cmp rax,[rsi+0x10] | - |
| 0x788 (t4) | 4 | - | 0x664dd30  mov eax,[rsi+0x788] | - |
| 0x780 (t4) | 4 | - | 0x664dd36  sub eax,[rsi+0x780] | - |
| 0x8A8 (t4) | 8 | 0x664dd85, 0x664ddbf | 0x664dd6b  mov rdx,[rsi+0x8A8] | sites vary: 8-byte load, qword += 2, dword read |
| 0x8B0 (t4) | 8 | - | 0x664dd72  cmp rdx,[rsi+0x8B0] | - |
| 0x8A0 (t4) | 8 | 0x664ddc5 | 0x664dd96  lea rcx,[rsi+0x8A0] | address-of (lea); dword read at 2nd site |
| 0x648 (t4) | 8 | 0x664de28 | 0x664ddf9  lea rcx,[rsi+0x648] | address-of (lea); dword read at 2nd site |
| 0x650 (t4) | 4 | - | 0x664de22  mov eax,[rsi+0x650] | - |
| 0x770 (t4) | 8 | 0x664de9d, 0x664dee8 | 0x664de5d  mov rbx,[rsi+0x770] | sites vary: 8-byte load, qword += 0x88, dword read |
| 0x778 (t4) | 8 | - | 0x664de64  cmp rbx,[rsi+0x778] | - |
| 0x768 (t4) | 8 | 0x664deee | 0x664deb1  lea rcx,[rsi+0x768] | address-of (lea); dword read at 2nd site |
| 0x758 (t4) | 8 | 0x664dfa0, 0x664dfd6 | 0x664df23  mov rdx,[rsi+0x758] | sites vary: 8-byte load, qword += 0x58, dword read |
| 0x760 (t4) | 8 | - | 0x664df2a  cmp rdx,[rsi+0x760] | - |
| 0x750 (t4) | 8 | 0x664dfdc | 0x664dfaa  lea rcx,[rsi+0x750] | address-of (lea); dword read at 2nd site |
| 0x860 (t4) | 8 | 0x664e024, 0x664e069 | 0x664e011  mov rdx,[rsi+0x860] | sites vary: 8-byte load, 8-byte store of rdx, dword add |
| 0x868 (t4) | 8 | - | 0x664e018  cmp rdx,[rsi+0x868] | - |
| 0x858 (t4) | 8 | 0x664e061 | 0x664e02d  lea rcx,[rsi+0x858] | address-of (lea); dword read at 2nd site |
| 0x6C8 (t4) | 8 | 0x664e0a6, 0x664e0e0 | 0x664e093  mov rdx,[rsi+0x6C8] | sites vary: 8-byte load, 8-byte store of rdx, dword add |
| 0x6D0 (t4) | 8 | - | 0x664e09a  cmp rdx,[rsi+0x6D0] | - |
| 0x6C0 (t4) | 8 | 0x664e0d8 | 0x664e0af  lea rcx,[rsi+0x6C0] | address-of (lea); dword read at 2nd site |
| 0x6B0 (t4) | 8 | 0x664e11d, 0x664e165 | 0x664e10a  mov rdx,[rsi+0x6B0] | sites vary: 8-byte load, 8-byte store of rdx, dword add |
| 0x6B8 (t4) | 8 | - | 0x664e111  cmp rdx,[rsi+0x6B8] | - |
| 0x6A8 (t4) | 4 | - | 0x664e15d  mov eax,[rsi+0x6A8] | - |

    0x6646b29  mov rbx,[rsi]
    0x6646b64  mov rax,[rsi+8]
    0x664e21d  lock dec dword ptr [rsi+0xC]
    0x664e193  cmp rax,[rsi+0x10]
    0x664dd30  mov eax,[rsi+0x788]
    0x664dd36  sub eax,[rsi+0x780]
    0x664dd6b  mov rdx,[rsi+0x8A8]
    0x664dd72  cmp rdx,[rsi+0x8B0]
    0x664dd96  lea rcx,[rsi+0x8A0]
    0x664ddf9  lea rcx,[rsi+0x648]
    0x664de22  mov eax,[rsi+0x650]
    0x664de5d  mov rbx,[rsi+0x770]
    0x664de64  cmp rbx,[rsi+0x778]
    0x664deb1  lea rcx,[rsi+0x768]
    0x664df23  mov rdx,[rsi+0x758]
    0x664df2a  cmp rdx,[rsi+0x760]
    0x664dfaa  lea rcx,[rsi+0x750]
    0x664e011  mov rdx,[rsi+0x860]
    0x664e018  cmp rdx,[rsi+0x868]
    0x664e02d  lea rcx,[rsi+0x858]
    0x664e093  mov rdx,[rsi+0x6C8]
    0x664e09a  cmp rdx,[rsi+0x6D0]
    0x664e0af  lea rcx,[rsi+0x6C0]
    0x664e10a  mov rdx,[rsi+0x6B0]
    0x664e111  cmp rdx,[rsi+0x6B8]
    0x664e15d  mov eax,[rsi+0x6A8]

## Notes
- Offset column carries the tag suffix because the same wrapper-struct offsets (rsi) recur across tags 0/1/4 and rdi offsets 0x0/0x8/0xC/0x10/0xC0/0xC8/0xD0 in tag 2; each table is per-tag as required.
- Every data line in docs/progress/_itemA_data.txt accesses the tag's own pointer register (rsi for tags 0/1/4, rdi for tag 2); none were ignored. The 80/135/94/73 site counts are fully distributed over the rows above.

## TOOL REQUESTS
None
