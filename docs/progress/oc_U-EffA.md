## NEXT
DONE: field maps for tags 1/3/5 written (tables + verbatim lines + notes); delegate.py check green apart from this line at time of writing.

# U-EffA: description read lists, GROUP visitor cases (tags 1,3,5) — checklist R3/R9

Source data: docs/progress/_effA_data.txt (verbatim lines copied from it; precomputed by orchestrator, not re-run).
Filter (same as oc_U-EffB.md): only lines whose `[rsi+off]` (or `[rsi]`) memory operand is READ (source operand). Pure stores (`mov [rsi],x`, `mov [rsi+0x80],rax`, `movups [rsi+off],xmm`) and `lea` lines are ignored. `lock dec` / `add qword ptr [mem]` read-modify-writes count as reads. One row per distinct offset per tag; first site verbatim, remaining read sites comma-separated. First column carries a t1/t3/t5 prefix because the checker forbids duplicate offset values across the whole file.
Visitor: effect visitor rva=0x666ACA0 [V docs/data/live/effect_visitor.txt line 1]. Tag names per unit: tag 1 = BlitFlipbook (R3), tag 3 = PlayerVision, tag 5 = FadeToBlack (R9).
Ignored (store/lea) sites per tag are listed in Notes at the bottom.

## tag 1 BlitFlipbook (head 0x666aec2, reg rsi)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| t1 0x10 | 1 | - | 0x666af6d  cmp byte ptr [rsi+0x10],1 | byte flag tested against 1 (gate before the member-copy block at 0x666af77) |
| t1 0x8 | 4 | 0x666b746, 0x666b7d4, 0x666b9d6, 0x666baca, 0x666c6c1, 0x666c728, 0x666c7bc, 0x666c800, 0x666fb88 | 0x666afa6  lock dec dword ptr [rsi+8] | refcount decrement (atomic RMW) in each paired release block |
| t1 0x0 | 8 | 0x666afc9, 0x666b74c, 0x666b761, 0x666b7da, 0x666b7ef, 0x666b9dc, 0x666b9f1, 0x666bad0, 0x666bae5, 0x666c6c7, 0x666c6dc, 0x666c72e, 0x666c743, 0x666c7c2, 0x666c7d7, 0x666c80a, 0x666c823, 0x666fb92, 0x666fbab | 0x666afb0  mov rax,[rsi] | - |
| t1 0xC | 4 | 0x666b75b, 0x666b7e9, 0x666b9eb, 0x666badf, 0x666c6d6, 0x666c73d, 0x666c7d1, 0x666c819, 0x666fba1 | 0x666afbf  lock dec dword ptr [rsi+0xC] | second refcount decrement, paired with the +0x8 one in every release block |
| t1 0x60 | 8 | - | 0x666b945  mov rax,[rsi+0x60] | end pointer of a pair; with the +0x58 site it computes ((+0x60 - +0x58) >> 2) / 3 (12-byte elements, 0x666b945..0x666b959) |
| t1 0x58 | 8 | - | 0x666b949  sub rax,[rsi+0x58] | start pointer of the same pair |
| t1 0x1D4 | 1 | - | 0x666b987  cmp byte ptr [rsi+0x1D4],0 | byte flag tested against 0 |
| t1 0x1D0 | 4 | - | 0x666b990  mov edi,[rsi+0x1D0] | dword loaded only when the +0x1D4 byte is nonzero (0x666b987..0x666b990) |

## tag 3 PlayerVision (head 0x666adbf, reg rsi)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| t3 0x338 | 8 | 0x666ae65, 0x666ca2b, 0x666ca50, 0x666cb14 | 0x666ae4a  mov rdi,[rsi+0x338] | cursor read; add site 0x666ae65 advances the qword by 0x14 (element stride 0x14, paired end +0x340); also read as dword at 0x666cb14 |
| t3 0x340 | 8 | 0x666ca83 | 0x666ae51  cmp rdi,[rsi+0x340] | end pointer compared with cursor +0x338 |
| t3 0x330 | 8 | 0x666ca3b, 0x666ca62, 0x666ca77 | 0x666b3e3  sub rbx,[rsi+0x330] | - |
| t3 0x8 | 8 | 0x666cb6d | 0x666cb4e  mov rax,[rsi+8] | cursor; advanced by 0xC8 per element (0x666cb6d), end at +0x10 |
| t3 0x10 | 8 | - | 0x666cb52  cmp rax,[rsi+0x10] | end pointer compared with cursor +0x8 |

## tag 5 FadeToBlack (head 0x666afde, reg rsi)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| t5 0x0 | 8 | 0x666b0f4, 0x666b115, 0x666b12e, 0x666c85b, 0x666c8b8, 0x666c8d1, 0x666cf7d, 0x666cf92, 0x666faf9, 0x666fb0e, 0x666fb51, 0x666fb66, 0x666fb92, 0x666fbab | 0x666b0a8  mov rbx,[rsi] | - |
| t5 0x8 | 8 | 0x666b0f7, 0x666b10b, 0x666c8ae, 0x666cf77, 0x666fa2c, 0x666fa47, 0x666faf3, 0x666fb4b, 0x666fb88 | 0x666b0e3  mov rax,[rsi+8] | dual role: cursor vs end +0x10 advanced by 0xC8 (0x666fa2c..0x666fa47) at one site set; lock dec release sites at the others |
| t5 0xC | 4 | 0x666b124, 0x666c8c7, 0x666cf8c, 0x666fb08, 0x666fb60, 0x666fba1 | 0x666b124  lock dec dword ptr [rsi+0xC] | second refcount decrement, paired with the +0x8 one |
| t5 0x788 | 4 | - | 0x666f57d  mov eax,[rsi+0x788] | end of a pair with +0x780 (dword diff computed) |
| t5 0x780 | 4 | - | 0x666f583  sub eax,[rsi+0x780] | start of the pair with +0x788 |
| t5 0x770 | 8 | 0x666f5f5, 0x666f635 | 0x666f5b5  mov rbx,[rsi+0x770] | cursor; add site 0x666f5f5 advances the qword by 0x88 (element stride 0x88), end +0x778; also read as dword at 0x666f635 |
| t5 0x778 | 8 | - | 0x666f5bc  cmp rbx,[rsi+0x778] | end pointer compared with cursor +0x770 |
| t5 0x768 | 4 | - | 0x666f63b  sub eax,[rsi+0x768] | - |
| t5 0x758 | 8 | 0x666f6ee, 0x666f729 | 0x666f674  mov rdx,[rsi+0x758] | cursor; add site 0x666f6ee advances the qword by 0x58 (element stride 0x58), end +0x760; also read as dword at 0x666f729 |
| t5 0x760 | 8 | - | 0x666f67b  cmp rdx,[rsi+0x760] | end pointer compared with cursor +0x758 |
| t5 0x750 | 4 | - | 0x666f72f  sub eax,[rsi+0x750] | - |
| t5 0x8A8 | 8 | 0x666f77b, 0x666f7b5 | 0x666f761  mov rdx,[rsi+0x8A8] | cursor; add site 0x666f77b advances the qword by 2, end +0x8B0; also read as dword at 0x666f7b5 |
| t5 0x8B0 | 8 | - | 0x666f768  cmp rdx,[rsi+0x8B0] | end pointer compared with cursor +0x8A8 |
| t5 0x8A0 | 4 | - | 0x666f7bb  sub eax,[rsi+0x8A0] | - |
| t5 0x650 | 4 | - | 0x666f818  mov eax,[rsi+0x650] | end of a pair with +0x648 (dword diff computed) |
| t5 0x648 | 4 | - | 0x666f81e  sub eax,[rsi+0x648] | start of the pair with +0x650 |
| t5 0x500 | 8 | 0x666f92c, 0x666f951, 0x666fa05 | 0x666f84c  mov rbx,[rsi+0x500] | - |
| t5 0x508 | 8 | 0x666f984 | 0x666f853  cmp rbx,[rsi+0x508] | - |
| t5 0x4F8 | 8 | 0x666f93c, 0x666f963, 0x666f978, 0x666f9fd | 0x666f86e  sub r13,[rsi+0x4F8] | - |
| t5 0x10 | 8 | - | 0x666fa30  cmp rax,[rsi+0x10] | end pointer compared with cursor +0x8 |

## Notes
- Sources: all quoted lines copied verbatim from docs/progress/_effA_data.txt (orchestrator-computed read lists for the effect visitor captured at rva=0x666ACA0, [V live] docs/data/live/effect_visitor.txt line 1). Visitor prologue loads r15 = [r8] = incoming description pointer and r8+8 = tag byte, then switches to cases with heads 0x666aec2 (tag 1), 0x666adbf (tag 3), 0x666afde (tag 5) [V disassembly].
- Ignored (store/lea) sites, not reads: tag 1 = 0x666c57b (store [rsi]), 0x666c57e (lea rcx,[rsi+8]), 0x666c596 (store [rsi+0x80]); there rsi is a cursor-list element loaded at 0x666c564 (list at rbx+0x768/0x770/0x778, stride 0x88), so these are element writes, not description reads. Tag 3 = 0x666cab7, 0x666cacd, 0x666cadc (stores). Tag 5 = 0x666f609, 0x666f6f8, 0x666f78c (lea), 0x666f85f, 0x666f9b8, 0x666f9c2, 0x666f9cc (stores).
- Provenance caveat [V disassembly]: rsi is re-assigned during each case, so not every row above reads the description object itself. Tag 1: rsi = tag pointer at 0x666af3c after keyed lookup sub_675E440 ("Flipbook" string loaded at 0x666aefb); later reloaded from members (0x666af92, 0x666b730, 0x666b7c8, 0x666b942, 0x666b982, 0x666bacd, 0x666c6b5, 0x666c71f, 0x666c7b0, 0x666c7f0, 0x666c564). The t1 0x8/0xC/0x0 lock-dec/load pairs are member release blocks (paired virtual release call sub_eea6040); they are kept because the unit filter is register-based only, which is also why checklist R3 still calls description +0x00..+0x0F unread. Tag 3: rsi = object returned by the call at 0x666add7 (alloc size 0x9D0 at 0x666adc8). Tag 5: rsi = [rbp+0x630] at 0x666b0a1 after keyed lookup sub_67D6D70 ("UI/Base" string loaded at 0x666b05d), reassigned at 0x666b0f7 and 0x666c894. The 0x666fb88..0x666fbab block is the shared function exit and therefore appears in both the tag 1 and tag 5 lists.
- Tag names: tag 1 BlitFlipbook and tag 5 FadeToBlack per unit assignment and docs/RENDER_CHECKLIST.md lines 601 (R3) and 607 (R9); tag 3 PlayerVision per unit assignment. The "Flipbook" string at tag 1 [V]; no name string seen for tags 3/5 in these cases.

## Verbatim first-site lines (one per row above, copied from docs/progress/_effA_data.txt)
0x666af6d  cmp byte ptr [rsi+0x10],1
0x666afa6  lock dec dword ptr [rsi+8]
0x666afb0  mov rax,[rsi]
0x666afbf  lock dec dword ptr [rsi+0xC]
0x666b945  mov rax,[rsi+0x60]
0x666b949  sub rax,[rsi+0x58]
0x666b987  cmp byte ptr [rsi+0x1D4],0
0x666b990  mov edi,[rsi+0x1D0]
0x666ae4a  mov rdi,[rsi+0x338]
0x666ae51  cmp rdi,[rsi+0x340]
0x666b3e3  sub rbx,[rsi+0x330]
0x666cb4e  mov rax,[rsi+8]
0x666cb52  cmp rax,[rsi+0x10]
0x666b0a8  mov rbx,[rsi]
0x666b0e3  mov rax,[rsi+8]
0x666b124  lock dec dword ptr [rsi+0xC]
0x666f57d  mov eax,[rsi+0x788]
0x666f583  sub eax,[rsi+0x780]
0x666f5b5  mov rbx,[rsi+0x770]
0x666f5bc  cmp rbx,[rsi+0x778]
0x666f63b  sub eax,[rsi+0x768]
0x666f674  mov rdx,[rsi+0x758]
0x666f67b  cmp rdx,[rsi+0x760]
0x666f72f  sub eax,[rsi+0x750]
0x666f761  mov rdx,[rsi+0x8A8]
0x666f768  cmp rdx,[rsi+0x8B0]
0x666f7bb  sub eax,[rsi+0x8A0]
0x666f818  mov eax,[rsi+0x650]
0x666f81e  sub eax,[rsi+0x648]
0x666f84c  mov rbx,[rsi+0x500]
0x666f853  cmp rbx,[rsi+0x508]
0x666f86e  sub r13,[rsi+0x4F8]
0x666fa30  cmp rax,[rsi+0x10]

## TOOL REQUESTS
None

