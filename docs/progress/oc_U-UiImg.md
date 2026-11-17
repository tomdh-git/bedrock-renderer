## NEXT
DONE (2026-11-16): field map of UI visitor tag 4 (head 0x6664aab, reg rdi) complete - 29 distinct offsets / 102 sites in the table below; delegate.py check exits 0 (claimed=102 match=102 mismatch=0 no-such-instr=0).

# Field map - UI visitor tag 4 (head 0x6664aab, description reg rdi)

Source: docs/progress/_uiB_data.txt (102 sites of [rdi+off] under tag 4, head 0x6664aab, description reg rdi). One row per distinct offset; the address cell lists every site of that offset (R = read, W = store, RMW = lock inc/dec read-modify-write, addr = lea address-taken, no memory access); the instruction cell holds the verbatim input-data lines for all those sites, `<br>`-separated, two spaces after each address. Sizes are per instruction (movups/movaps 16, qword 8, dword 4, word 2, byte 1). Meaning only where the instruction itself shows it, else '-'.

## tag 4 (head 0x6664aab, reg rdi): 29 distinct offsets, 102 sites

| offset | size | read/store address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 | 16 (movups/movaps) / 8 / 2 / 1 | R: 0x6664ba8, 0x6664bc1, 0x6665acd, 0x6665ae2, 0x6665dcd, 0x66661ca, 0x6666567, 0x666657c, 0x6666782, 0x6666b83, 0x6666b98, 0x6666c04, 0x6666c19, 0x666781c, 0x6667831, 0x6667892, 0x66678a7<br>W: 0x666598d, 0x6665a29, 0x6665a75, 0x6665a90, 0x6665df2, 0x6666439, 0x6666530, 0x666662b, 0x66667a7, 0x66669a0, 0x66671c5 | `0x6664ba8  mov rax,[rdi]`<br>`0x6664bc1  mov rax,[rdi]`<br>`0x666598d  movups [rdi],xmm0`<br>`0x6665a29  mov [rdi],rax`<br>`0x6665a75  movaps [rdi],xmm0`<br>`0x6665a90  mov word ptr [rdi],0xFFFF`<br>`0x6665acd  mov rax,[rdi]`<br>`0x6665ae2  mov rax,[rdi]`<br>`0x6665dcd  movups xmm0,[rdi]`<br>`0x6665df2  mov byte ptr [rdi],0`<br>`0x66661ca  mov rax,[rdi]`<br>`0x6666439  movups [rdi],xmm0`<br>`0x6666530  mov word ptr [rdi],0xFFFF`<br>`0x6666567  mov rax,[rdi]`<br>`0x666657c  mov rax,[rdi]`<br>`0x666662b  mov [rdi],rax`<br>`0x6666782  movups xmm0,[rdi]`<br>`0x66667a7  mov byte ptr [rdi],0`<br>`0x66669a0  mov [rdi],rax`<br>`0x6666b83  mov rax,[rdi]`<br>`0x6666b98  mov rax,[rdi]`<br>`0x6666c04  mov rax,[rdi]`<br>`0x6666c19  mov rax,[rdi]`<br>`0x66671c5  mov [rdi],rax`<br>`0x666781c  mov rax,[rdi]`<br>`0x6667831  mov rax,[rdi]`<br>`0x6667892  mov rax,[rdi]`<br>`0x66678a7  mov rax,[rdi]` | - |
| 0x2 | 1 | W: 0x6666518 | `0x6666518  mov byte ptr [rdi+2],0` | - |
| 0x4 | 8 | W: 0x6666524 | `0x6666524  mov qword ptr [rdi+4],0` | - |
| 0x8 | 16 (movups) / 8 / 4 (lock dec) / lea: no access | RMW: 0x6664b9e, 0x6665ac7, 0x6666561, 0x6666b7d, 0x6666bfe, 0x6667816, 0x666788c<br>W: 0x6665a1e, 0x666662e, 0x66669a3<br>addr: 0x66671c8 | `0x6664b9e  lock dec dword ptr [rdi+8]`<br>`0x6665a1e  mov [rdi+8],rax`<br>`0x6665ac7  lock dec dword ptr [rdi+8]`<br>`0x6666561  lock dec dword ptr [rdi+8]`<br>`0x666662e  mov [rdi+8],rcx`<br>`0x66669a3  movups [rdi+8],xmm0`<br>`0x6666b7d  lock dec dword ptr [rdi+8]`<br>`0x6666bfe  lock dec dword ptr [rdi+8]`<br>`0x66671c8  lea rcx,[rdi+8]`<br>`0x6667816  lock dec dword ptr [rdi+8]`<br>`0x666788c  lock dec dword ptr [rdi+8]` | atomic dword dec (lock prefix) at 7 sites; lea at 0x66671c8 takes the address only |
| 0xC | 4 (lock inc/dec) / 2 / 1 | RMW: 0x6664bb7, 0x6665adc, 0x66660d1, 0x66660e7, 0x66661c4, 0x6666576, 0x6666b92, 0x6666c13, 0x666782b, 0x66678a1<br>W: 0x6665a95, 0x666652c | `0x6664bb7  lock dec dword ptr [rdi+0xC]`<br>`0x6665a95  mov word ptr [rdi+0xC],0xFFFF`<br>`0x6665adc  lock dec dword ptr [rdi+0xC]`<br>`0x66660d1  lock inc dword ptr [rdi+0xC]`<br>`0x66660e7  lock inc dword ptr [rdi+0xC]`<br>`0x66661c4  lock dec dword ptr [rdi+0xC]`<br>`0x666652c  mov byte ptr [rdi+0xC],0`<br>`0x6666576  lock dec dword ptr [rdi+0xC]`<br>`0x6666b92  lock dec dword ptr [rdi+0xC]`<br>`0x6666c13  lock dec dword ptr [rdi+0xC]`<br>`0x666782b  lock dec dword ptr [rdi+0xC]`<br>`0x66678a1  lock dec dword ptr [rdi+0xC]` | atomic dword inc/dec (lock prefix) |
| 0xF | 4 | W: 0x6665983, 0x666642f | `0x6665983  mov [rdi+0xF],eax`<br>`0x666642f  mov [rdi+0xF],eax` | - |
| 0x10 | 16 (movups/movaps) / 8 / 1 | R: 0x6664b65, 0x6665dd0, 0x6666785<br>W: 0x6665a3d, 0x6665a8c, 0x6665de2, 0x6666255, 0x666651c, 0x6666632, 0x6666797, 0x6666ab2 | `0x6664b65  cmp byte ptr [rdi+0x10],1`<br>`0x6665a3d  movups [rdi+0x10],xmm0`<br>`0x6665a8c  movaps [rdi+0x10],xmm0`<br>`0x6665dd0  movups xmm1,[rdi+0x10]`<br>`0x6665de2  mov qword ptr [rdi+0x10],0`<br>`0x6666255  mov byte ptr [rdi+0x10],1`<br>`0x666651c  mov qword ptr [rdi+0x10],0`<br>`0x6666632  mov [rdi+0x10],r15`<br>`0x6666785  movups xmm1,[rdi+0x10]`<br>`0x6666797  mov qword ptr [rdi+0x10],0`<br>`0x6666ab2  mov byte ptr [rdi+0x10],1` | byte set to 1 and compared to 1 (0x6664b65); other sites are 8/16-byte loads/stores |
| 0x13 | 1 | W: 0x6665990, 0x666643c | `0x6665990  mov byte ptr [rdi+0x13],0`<br>`0x666643c  mov byte ptr [rdi+0x13],0` | - |
| 0x18 | 16 (movups) / 8 | W: 0x6665dea, 0x666679f, 0x66669b1, 0x66669ee | `0x6665dea  mov qword ptr [rdi+0x18],0xF`<br>`0x666679f  mov qword ptr [rdi+0x18],0xF`<br>`0x66669b1  movups [rdi+0x18],xmm6`<br>`0x66669ee  mov [rdi+0x18],rax` | 0xF stored (qword) at 2 sites |
| 0x20 | 16 (movaps) / 1 | W: 0x6665a48, 0x6665a88 | `0x6665a48  mov byte ptr [rdi+0x20],0`<br>`0x6665a88  movaps [rdi+0x20],xmm0` | - |
| 0x30 | 16 | W: 0x6665a84 | `0x6665a84  movaps [rdi+0x30],xmm0` | - |
| 0x40 | 16 | W: 0x6665a80 | `0x6665a80  movaps [rdi+0x40],xmm0` | - |
| 0x4E | 8 | W: 0x6666f2f | `0x6666f2f  mov qword ptr [rdi+0x4E],0` | - |
| 0x50 | 16 | W: 0x6665a7c | `0x6665a7c  movaps [rdi+0x50],xmm0` | - |
| 0x54 | 8 | W: 0x6666f27 | `0x6666f27  mov qword ptr [rdi+0x54],0` | - |
| 0x58 | 16 | W: 0x66669f2 | `0x66669f2  movups [rdi+0x58],xmm6` | - |
| 0x60 | 16 | W: 0x6665a78 | `0x6665a78  movaps [rdi+0x60],xmm0` | - |
| 0x68 | 16 | W: 0x66669f6 | `0x66669f6  movups [rdi+0x68],xmm6` | - |
| 0x78 | 16 (movups) / 8 | R: 0x666600f, 0x6666031<br>W: 0x6665b5e, 0x6666016, 0x6666038, 0x66669fa<br>RMW: 0x666605d | `0x6665b5e  mov qword ptr [rdi+0x78],0`<br>`0x666600f  mov rcx,[rdi+0x78]`<br>`0x6666016  mov [rdi+0x78],rcx`<br>`0x6666031  mov rcx,[rdi+0x78]`<br>`0x6666038  mov [rdi+0x78],rcx`<br>`0x666605d  inc qword ptr [rdi+0x78]`<br>`0x66669fa  movups [rdi+0x78],xmm6` | qword inc'd (0x666605d) and copied via rcx |
| 0x80 | 8 / 2 | W: 0x6666073, 0x66671e0 | `0x6666073  mov [rdi+0x80],ax`<br>`0x66671e0  mov [rdi+0x80],rax` | - |
| 0x88 | 8 / 4 | W: 0x6666080, 0x66669fe | `0x6666080  mov [rdi+0x88],eax`<br>`0x66669fe  mov qword ptr [rdi+0x88],0` | - |
| 0x90 | 16 (movups) / 8 | W: 0x66660a9, 0x6666a09 | `0x66660a9  movups [rdi+0x90],xmm1`<br>`0x6666a09  mov qword ptr [rdi+0x90],0xF` | 0xF stored (qword) |
| 0x98 | 8 | W: 0x6666a14 | `0x6666a14  mov [rdi+0x98],rsi` | - |
| 0xA0 | 8 | W: 0x66660b0 | `0x66660b0  mov [rdi+0xA0],rax` | - |
| 0xEA | 16 | W: 0x6666f7c | `0x6666f7c  movups [rdi+0xEA],xmm6` | - |
| 0xFE | 16 | W: 0x6666f8d | `0x6666f8d  movups [rdi+0xFE],xmm6` | - |
| 0x112 | 16 | W: 0x6666f9e | `0x6666f9e  movups [rdi+0x112],xmm6` | - |
| 0x16E | 16 | W: 0x666708c | `0x666708c  movups [rdi+0x16E],xmm0` | - |
| 0x17E | 8 | W: 0x6667081 | `0x6667081  mov [rdi+0x17E],rax` | - |

## Claim lines (same 102 sites, grouped by offset, unindented so verify_oc reads them)

**[rdi+0x0]** (28 sites)
0x6664ba8  mov rax,[rdi]
0x6664bc1  mov rax,[rdi]
0x666598d  movups [rdi],xmm0
0x6665a29  mov [rdi],rax
0x6665a75  movaps [rdi],xmm0
0x6665a90  mov word ptr [rdi],0xFFFF
0x6665acd  mov rax,[rdi]
0x6665ae2  mov rax,[rdi]
0x6665dcd  movups xmm0,[rdi]
0x6665df2  mov byte ptr [rdi],0
0x66661ca  mov rax,[rdi]
0x6666439  movups [rdi],xmm0
0x6666530  mov word ptr [rdi],0xFFFF
0x6666567  mov rax,[rdi]
0x666657c  mov rax,[rdi]
0x666662b  mov [rdi],rax
0x6666782  movups xmm0,[rdi]
0x66667a7  mov byte ptr [rdi],0
0x66669a0  mov [rdi],rax
0x6666b83  mov rax,[rdi]
0x6666b98  mov rax,[rdi]
0x6666c04  mov rax,[rdi]
0x6666c19  mov rax,[rdi]
0x66671c5  mov [rdi],rax
0x666781c  mov rax,[rdi]
0x6667831  mov rax,[rdi]
0x6667892  mov rax,[rdi]
0x66678a7  mov rax,[rdi]

**[rdi+0x2]** (1 site)
0x6666518  mov byte ptr [rdi+2],0

**[rdi+0x4]** (1 site)
0x6666524  mov qword ptr [rdi+4],0

**[rdi+0x8]** (11 sites)
0x6664b9e  lock dec dword ptr [rdi+8]
0x6665a1e  mov [rdi+8],rax
0x6665ac7  lock dec dword ptr [rdi+8]
0x6666561  lock dec dword ptr [rdi+8]
0x666662e  mov [rdi+8],rcx
0x66669a3  movups [rdi+8],xmm0
0x6666b7d  lock dec dword ptr [rdi+8]
0x6666bfe  lock dec dword ptr [rdi+8]
0x66671c8  lea rcx,[rdi+8]
0x6667816  lock dec dword ptr [rdi+8]
0x666788c  lock dec dword ptr [rdi+8]

**[rdi+0xC]** (12 sites)
0x6664bb7  lock dec dword ptr [rdi+0xC]
0x6665a95  mov word ptr [rdi+0xC],0xFFFF
0x6665adc  lock dec dword ptr [rdi+0xC]
0x66660d1  lock inc dword ptr [rdi+0xC]
0x66660e7  lock inc dword ptr [rdi+0xC]
0x66661c4  lock dec dword ptr [rdi+0xC]
0x666652c  mov byte ptr [rdi+0xC],0
0x6666576  lock dec dword ptr [rdi+0xC]
0x6666b92  lock dec dword ptr [rdi+0xC]
0x6666c13  lock dec dword ptr [rdi+0xC]
0x666782b  lock dec dword ptr [rdi+0xC]
0x66678a1  lock dec dword ptr [rdi+0xC]

**[rdi+0xF]** (2 sites)
0x6665983  mov [rdi+0xF],eax
0x666642f  mov [rdi+0xF],eax

**[rdi+0x10]** (11 sites)
0x6664b65  cmp byte ptr [rdi+0x10],1
0x6665a3d  movups [rdi+0x10],xmm0
0x6665a8c  movaps [rdi+0x10],xmm0
0x6665dd0  movups xmm1,[rdi+0x10]
0x6665de2  mov qword ptr [rdi+0x10],0
0x6666255  mov byte ptr [rdi+0x10],1
0x666651c  mov qword ptr [rdi+0x10],0
0x6666632  mov [rdi+0x10],r15
0x6666785  movups xmm1,[rdi+0x10]
0x6666797  mov qword ptr [rdi+0x10],0
0x6666ab2  mov byte ptr [rdi+0x10],1

**[rdi+0x13]** (2 sites)
0x6665990  mov byte ptr [rdi+0x13],0
0x666643c  mov byte ptr [rdi+0x13],0

**[rdi+0x18]** (4 sites)
0x6665dea  mov qword ptr [rdi+0x18],0xF
0x666679f  mov qword ptr [rdi+0x18],0xF
0x66669b1  movups [rdi+0x18],xmm6
0x66669ee  mov [rdi+0x18],rax

**[rdi+0x20]** (2 sites)
0x6665a48  mov byte ptr [rdi+0x20],0
0x6665a88  movaps [rdi+0x20],xmm0

**[rdi+0x30]** (1 site)
0x6665a84  movaps [rdi+0x30],xmm0

**[rdi+0x40]** (1 site)
0x6665a80  movaps [rdi+0x40],xmm0

**[rdi+0x4E]** (1 site)
0x6666f2f  mov qword ptr [rdi+0x4E],0

**[rdi+0x50]** (1 site)
0x6665a7c  movaps [rdi+0x50],xmm0

**[rdi+0x54]** (1 site)
0x6666f27  mov qword ptr [rdi+0x54],0

**[rdi+0x58]** (1 site)
0x66669f2  movups [rdi+0x58],xmm6

**[rdi+0x60]** (1 site)
0x6665a78  movaps [rdi+0x60],xmm0

**[rdi+0x68]** (1 site)
0x66669f6  movups [rdi+0x68],xmm6

**[rdi+0x78]** (7 sites)
0x6665b5e  mov qword ptr [rdi+0x78],0
0x666600f  mov rcx,[rdi+0x78]
0x6666016  mov [rdi+0x78],rcx
0x6666031  mov rcx,[rdi+0x78]
0x6666038  mov [rdi+0x78],rcx
0x666605d  inc qword ptr [rdi+0x78]
0x66669fa  movups [rdi+0x78],xmm6

**[rdi+0x80]** (2 sites)
0x6666073  mov [rdi+0x80],ax
0x66671e0  mov [rdi+0x80],rax

**[rdi+0x88]** (2 sites)
0x6666080  mov [rdi+0x88],eax
0x66669fe  mov qword ptr [rdi+0x88],0
[UNVERIFIED resolved: input data had "0x66669ff  mov dword ptr [rdi+0x88],0"; rdis dis 0x66669f2 shows the site is 0x66669fe mov qword ptr [rdi+0x88],0 (qword, 8 B) - corrected above, [V] rdis dis 0x66669f2]

**[rdi+0x90]** (2 sites)
0x66660a9  movups [rdi+0x90],xmm1
0x6666a09  mov qword ptr [rdi+0x90],0xF

**[rdi+0x98]** (1 site)
0x6666a14  mov [rdi+0x98],rsi

**[rdi+0xA0]** (1 site)
0x66660b0  mov [rdi+0xA0],rax

**[rdi+0xEA]** (1 site)
0x6666f7c  movups [rdi+0xEA],xmm6

**[rdi+0xFE]** (1 site)
0x6666f8d  movups [rdi+0xFE],xmm6

**[rdi+0x112]** (1 site)
0x6666f9e  movups [rdi+0x112],xmm6

**[rdi+0x16E]** (1 site)
0x666708c  movups [rdi+0x16E],xmm0

**[rdi+0x17E]** (1 site)
0x6667081  mov [rdi+0x17E],rax

## TOOL REQUESTS
None
