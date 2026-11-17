## NEXT
DONE (2026-11-16): field map of UI visitor tag 1 (head 0x6664d51, reg rsi) complete - 31 distinct offsets / 63 sites in the table below; delegate.py check exits 0 (claimed=63 match=63 mismatch=0 no-such-instr=0).

# Field map - UI visitor tag 1 (head 0x6664d51, description reg rsi)

Source: docs/progress/_uiA_data.txt (63 sites of [rsi+off] under tag 1, head 0x6664d51, description reg rsi). One row per distinct offset; the address cell lists every site of that offset (R = read, W = store, RMW = add / lock dec read-modify-write, addr = lea address-taken, no memory access); the instruction cell holds the verbatim input-data lines for all those sites, `<br>`-separated, two spaces after each address. Sizes are per instruction (qword 8, dword 4; lea has no memory access). Meaning only where the instruction itself shows it, else '-'.

## tag 1 (head 0x6664d51, reg rsi): 31 distinct offsets, 63 sites

| offset | size | read/store address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 | 8 | R: 0x6667f93, 0x6667fa8, 0x6667fee, 0x6668003, 0x66680b0, 0x66680c5 | `0x6667f93  mov rax,[rsi]`<br>`0x6667fa8  mov rax,[rsi]`<br>`0x6667fee  mov rax,[rsi]`<br>`0x6668003  mov rax,[rsi]`<br>`0x66680b0  mov rax,[rsi]`<br>`0x66680c5  mov rax,[rsi]` | - |
| 0x8 | 8 / 4 (lock dec) | R: 0x6667f14<br>RMW: 0x6667f33, 0x6667f8d, 0x6667fe8, 0x66680aa | `0x6667f14  mov rax,[rsi+8]`<br>`0x6667f33  add qword ptr [rsi+8],0xC8`<br>`0x6667f8d  lock dec dword ptr [rsi+8]`<br>`0x6667fe8  lock dec dword ptr [rsi+8]`<br>`0x66680aa  lock dec dword ptr [rsi+8]` | qword += 0xC8 at 0x6667f33; atomic dword dec (lock prefix) at 3 sites |
| 0xC | 4 (lock dec) | RMW: 0x6667fa2, 0x6667ffd, 0x66680bf | `0x6667fa2  lock dec dword ptr [rsi+0xC]`<br>`0x6667ffd  lock dec dword ptr [rsi+0xC]`<br>`0x66680bf  lock dec dword ptr [rsi+0xC]` | atomic dword dec (lock prefix) |
| 0x10 | 8 | R: 0x6667f18 | `0x6667f18  cmp rax,[rsi+0x10]` | - |
| 0x58 | 8 | R: 0x6665253 | `0x6665253  sub rax,[rsi+0x58]` | pair with 0x60: rax=[rsi+0x60] at 0x666524f, then rax-=[rsi+0x58] |
| 0x60 | 8 | R: 0x666524f | `0x666524f  mov rax,[rsi+0x60]` | pair with 0x58 (rax-=[rsi+0x58] at 0x6665253) |
| 0x360 | lea: no access / 4 | addr: 0x6667dea<br>R: 0x6667e13 | `0x6667dea  lea rcx,[rsi+0x360]`<br>`0x6667e13  mov eax,[rsi+0x360]` | lea takes the address only; dword read then add eax,[rsi+0x368] (0x6667e1b) |
| 0x368 | 8 / 4 | R: 0x6667dce, 0x6667e1b<br>W: 0x6667de1 | `0x6667dce  mov rdx,[rsi+0x368]`<br>`0x6667de1  mov [rsi+0x368],rdx`<br>`0x6667e1b  add eax,[rsi+0x368]` | qword stored back after read (0x6667dce/0x6667de1; value compared vs [rsi+0x370] at 0x6667dd5); dword read added to eax |
| 0x370 | 8 | R: 0x6667dd5 | `0x6667dd5  cmp rdx,[rsi+0x370]` | - |
| 0x630 | lea: no access / 4 | addr: 0x6667b69<br>R: 0x6667b98 | `0x6667b69  lea rcx,[rsi+0x630]`<br>`0x6667b98  sub eax,[rsi+0x630]` | lea takes the address only; dword subtracted from eax (eax=[rsi+0x638] at 0x6667b92) |
| 0x638 | 8 / 4 | R: 0x6667b40, 0x6667b92<br>RMW: 0x6667b58 | `0x6667b40  mov rdx,[rsi+0x638]`<br>`0x6667b58  add qword ptr [rsi+0x638],4`<br>`0x6667b92  mov eax,[rsi+0x638]` | qword += 4 at 0x6667b58; dword read then sub eax,[rsi+0x630] (0x6667b98); qword compared vs [rsi+0x640] at 0x6667b47 |
| 0x640 | 8 | R: 0x6667b47 | `0x6667b47  cmp rdx,[rsi+0x640]` | - |
| 0x648 | lea: no access / 4 | addr: 0x6667ad1<br>R: 0x6667b0b | `0x6667ad1  lea rcx,[rsi+0x648]`<br>`0x6667b0b  sub eax,[rsi+0x648]` | lea takes the address only; dword subtracted from eax (eax=[rsi+0x650] at 0x6667b05) |
| 0x650 | 4 | R: 0x6667b05 | `0x6667b05  mov eax,[rsi+0x650]` | - |
| 0x690 | lea: no access / 4 | addr: 0x6667bf2<br>R: 0x6667c2c | `0x6667bf2  lea rcx,[rsi+0x690]`<br>`0x6667c2c  sub eax,[rsi+0x690]` | lea takes the address only; dword subtracted from eax (eax=[rsi+0x698] at 0x6667c26) |
| 0x698 | 8 / 4 | R: 0x6667bc7, 0x6667c26<br>RMW: 0x6667be1 | `0x6667bc7  mov rdx,[rsi+0x698]`<br>`0x6667be1  add qword ptr [rsi+0x698],2`<br>`0x6667c26  mov eax,[rsi+0x698]` | qword += 2 at 0x6667be1; dword read then sub eax,[rsi+0x690] (0x6667c2c); qword compared vs [rsi+0x6A0] at 0x6667bce |
| 0x6A0 | 8 | R: 0x6667bce | `0x6667bce  cmp rdx,[rsi+0x6A0]` | - |
| 0x750 | lea: no access / 4 | addr: 0x6667ce8<br>R: 0x6667d17 | `0x6667ce8  lea rcx,[rsi+0x750]`<br>`0x6667d17  sub eax,[rsi+0x750]` | lea takes the address only; dword subtracted from eax (eax=[rsi+0x758] at 0x6667d11) |
| 0x758 | 8 / 4 | R: 0x6667c61, 0x6667d11<br>RMW: 0x6667cde | `0x6667c61  mov rdx,[rsi+0x758]`<br>`0x6667cde  add qword ptr [rsi+0x758],0x58`<br>`0x6667d11  mov eax,[rsi+0x758]` | qword += 0x58 at 0x6667cde; dword read then sub eax,[rsi+0x750] (0x6667d17); qword compared vs [rsi+0x760] at 0x6667c68 |
| 0x760 | 8 | R: 0x6667c68 | `0x6667c68  cmp rdx,[rsi+0x760]` | - |
| 0x768 | 4 | R: 0x6667edf | `0x6667edf  sub eax,[rsi+0x768]` | pair with 0x770: eax=[rsi+0x770] at 0x6667ed9, then eax-=[rsi+0x768] |
| 0x770 | 8 / 4 | R: 0x6667e45, 0x6667ed9<br>RMW: 0x6667e85 | `0x6667e45  mov rbx,[rsi+0x770]`<br>`0x6667e85  add qword ptr [rsi+0x770],0x88`<br>`0x6667ed9  mov eax,[rsi+0x770]` | qword += 0x88 at 0x6667e85; dword read then sub eax,[rsi+0x768] (0x6667edf); qword compared vs [rsi+0x778] at 0x6667e4c |
| 0x778 | 8 | R: 0x6667e4c | `0x6667e4c  cmp rbx,[rsi+0x778]` | - |
| 0x780 | 4 | R: 0x6667a0e | `0x6667a0e  sub eax,[rsi+0x780]` | pair with 0x788: eax=[rsi+0x788] at 0x6667a08, then eax-=[rsi+0x780] |
| 0x788 | 4 | R: 0x6667a08 | `0x6667a08  mov eax,[rsi+0x788]` | - |
| 0x810 | lea: no access / 4 | addr: 0x6667d68<br>R: 0x6667d9c | `0x6667d68  lea rcx,[rsi+0x810]`<br>`0x6667d9c  mov eax,[rsi+0x810]` | lea takes the address only; dword read then add eax,[rsi+0x818] (0x6667da4) |
| 0x818 | 8 / 4 | R: 0x6667d4c, 0x6667da4<br>W: 0x6667d5f | `0x6667d4c  mov rdx,[rsi+0x818]`<br>`0x6667d5f  mov [rsi+0x818],rdx`<br>`0x6667da4  add eax,[rsi+0x818]` | qword stored back after read (0x6667d4c/0x6667d5f; value compared vs [rsi+0x820] at 0x6667d53); dword read added to eax |
| 0x820 | 8 | R: 0x6667d53 | `0x6667d53  cmp rdx,[rsi+0x820]` | - |
| 0x8A0 | lea: no access / 4 | addr: 0x6667a6e<br>R: 0x6667a9d | `0x6667a6e  lea rcx,[rsi+0x8A0]`<br>`0x6667a9d  sub eax,[rsi+0x8A0]` | lea takes the address only; dword subtracted from eax (eax=[rsi+0x8A8] at 0x6667a97) |
| 0x8A8 | 8 / 4 | R: 0x6667a43, 0x6667a97<br>RMW: 0x6667a5d | `0x6667a43  mov rdx,[rsi+0x8A8]`<br>`0x6667a5d  add qword ptr [rsi+0x8A8],2`<br>`0x6667a97  mov eax,[rsi+0x8A8]` | qword += 2 at 0x6667a5d; dword read then sub eax,[rsi+0x8A0] (0x6667a9d); qword compared vs [rsi+0x8B0] at 0x6667a4a |
| 0x8B0 | 8 | R: 0x6667a4a | `0x6667a4a  cmp rdx,[rsi+0x8B0]` | - |

## Claim lines (same 63 sites, grouped by offset, unindented so verify_oc reads them)

**[rsi+0x0]** (6 sites)
0x6667f93  mov rax,[rsi]
0x6667fa8  mov rax,[rsi]
0x6667fee  mov rax,[rsi]
0x6668003  mov rax,[rsi]
0x66680b0  mov rax,[rsi]
0x66680c5  mov rax,[rsi]

**[rsi+0x8]** (5 sites)
0x6667f14  mov rax,[rsi+8]
0x6667f33  add qword ptr [rsi+8],0xC8
0x6667f8d  lock dec dword ptr [rsi+8]
0x6667fe8  lock dec dword ptr [rsi+8]
0x66680aa  lock dec dword ptr [rsi+8]

**[rsi+0xC]** (3 sites)
0x6667fa2  lock dec dword ptr [rsi+0xC]
0x6667ffd  lock dec dword ptr [rsi+0xC]
0x66680bf  lock dec dword ptr [rsi+0xC]

**[rsi+0x10]** (1 site)
0x6667f18  cmp rax,[rsi+0x10]

**[rsi+0x58]** (1 site)
0x6665253  sub rax,[rsi+0x58]

**[rsi+0x60]** (1 site)
0x666524f  mov rax,[rsi+0x60]

**[rsi+0x360]** (2 sites)
0x6667dea  lea rcx,[rsi+0x360]
0x6667e13  mov eax,[rsi+0x360]

**[rsi+0x368]** (3 sites)
0x6667dce  mov rdx,[rsi+0x368]
0x6667de1  mov [rsi+0x368],rdx
0x6667e1b  add eax,[rsi+0x368]

**[rsi+0x370]** (1 site)
0x6667dd5  cmp rdx,[rsi+0x370]

**[rsi+0x630]** (2 sites)
0x6667b69  lea rcx,[rsi+0x630]
0x6667b98  sub eax,[rsi+0x630]

**[rsi+0x638]** (3 sites)
0x6667b40  mov rdx,[rsi+0x638]
0x6667b58  add qword ptr [rsi+0x638],4
0x6667b92  mov eax,[rsi+0x638]

**[rsi+0x640]** (1 site)
0x6667b47  cmp rdx,[rsi+0x640]

**[rsi+0x648]** (2 sites)
0x6667ad1  lea rcx,[rsi+0x648]
0x6667b0b  sub eax,[rsi+0x648]

**[rsi+0x650]** (1 site)
0x6667b05  mov eax,[rsi+0x650]

**[rsi+0x690]** (2 sites)
0x6667bf2  lea rcx,[rsi+0x690]
0x6667c2c  sub eax,[rsi+0x690]

**[rsi+0x698]** (3 sites)
0x6667bc7  mov rdx,[rsi+0x698]
0x6667be1  add qword ptr [rsi+0x698],2
0x6667c26  mov eax,[rsi+0x698]

**[rsi+0x6A0]** (1 site)
0x6667bce  cmp rdx,[rsi+0x6A0]

**[rsi+0x750]** (2 sites)
0x6667ce8  lea rcx,[rsi+0x750]
0x6667d17  sub eax,[rsi+0x750]

**[rsi+0x758]** (3 sites)
0x6667c61  mov rdx,[rsi+0x758]
0x6667cde  add qword ptr [rsi+0x758],0x58
0x6667d11  mov eax,[rsi+0x758]

**[rsi+0x760]** (1 site)
0x6667c68  cmp rdx,[rsi+0x760]

**[rsi+0x768]** (1 site)
0x6667edf  sub eax,[rsi+0x768]

**[rsi+0x770]** (3 sites)
0x6667e45  mov rbx,[rsi+0x770]
0x6667e85  add qword ptr [rsi+0x770],0x88
0x6667ed9  mov eax,[rsi+0x770]

**[rsi+0x778]** (1 site)
0x6667e4c  cmp rbx,[rsi+0x778]

**[rsi+0x780]** (1 site)
0x6667a0e  sub eax,[rsi+0x780]

**[rsi+0x788]** (1 site)
0x6667a08  mov eax,[rsi+0x788]

**[rsi+0x810]** (2 sites)
0x6667d68  lea rcx,[rsi+0x810]
0x6667d9c  mov eax,[rsi+0x810]

**[rsi+0x818]** (3 sites)
0x6667d4c  mov rdx,[rsi+0x818]
0x6667d5f  mov [rsi+0x818],rdx
0x6667da4  add eax,[rsi+0x818]

**[rsi+0x820]** (1 site)
0x6667d53  cmp rdx,[rsi+0x820]

**[rsi+0x8A0]** (2 sites)
0x6667a6e  lea rcx,[rsi+0x8A0]
0x6667a9d  sub eax,[rsi+0x8A0]

**[rsi+0x8A8]** (3 sites)
0x6667a43  mov rdx,[rsi+0x8A8]
0x6667a5d  add qword ptr [rsi+0x8A8],2
0x6667a97  mov eax,[rsi+0x8A8]

**[rsi+0x8B0]** (1 site)
0x6667a4a  cmp rdx,[rsi+0x8B0]

## TOOL REQUESTS
None
