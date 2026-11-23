# Unit U-EM1c — M1c Dossiers (D2): Context::init 0xbc63690 field map (verified)

## NEXT
DONE

## Source
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0xbc63690 320` [V]. Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01); RVAs are image-relative [V]. rdis reports `sub_bc63690 [0xbc63690..0xbc65690) size 0x2000 2 xrefs in` [V]; entry `mov rsi,rcx` at 0xbc63697 so `this`=rcx=rsi [V]; code ends at `jmp 0xEBCE430` (0xbc63b72) followed by int3 padding [V].

## What this unit did
Field-map of Context::init (0xbc63690): one annotated row per distinct `this`-relative field offset accessed, each with its verified `0xRVA  instr` proof line, size from the instruction, and R/W site. Sizes: movaps=16, qword=8, dword/mov=4, word=2, byte=1 [V]. No raw instruction dumps pasted; every instruction lives inside a table cell [V]. No shorthand used [V].

## Field map — Context::init (0xbc63690); `this`=rsi; loop index rbx steps 0..0x14000 by 0x140 over 0x140-byte elements
| offset | size | site | `0xRVA  instr` | meaning |
| 0x1EBF19F | 1 | W | `0xbc6369a  and byte ptr [rcx+0x1EBF19F],0x7F` | clear flag bit 0x80 of field a0+0x1EBF19F [V] |
| 0x1EBF2EF | 1 | W | `0xbc636a1  mov byte ptr [rcx+0x1EBF2EF],0` | zero byte field a0+0x1EBF2EF [V] |
| 0x1EBF1D0 | 4 | W | `0xbc636a8  mov dword ptr [rcx+0x1EBF1D0],0` | zero dword field a0+0x1EBF1D0 [V] |
| 0x1EBF1C8 | 8 | W | `0xbc636b7  mov [rsi+0x1EBF1C8],rax` | store call result to qword field a0+0x1EBF1C8 [V] |
| 0x1CFD0C8 | 8 | R | `0xbc636be  mov rcx,[rsi+0x1CFD0C8]` | load qword field a0+0x1CFD0C8 into rcx [V] |
| 0x1CFD0C0 | 8 | R | `0xbc636ca  mov rcx,[rsi+0x1CFD0C0]` | load qword field a0+0x1CFD0C0 into rcx [V] |
| 0x1EBF2F1 | 1 | W | `0xbc6374a  mov [rsi+0x1EBF2F1],dil` | store sete bool to byte field a0+0x1EBF2F1 [V] |
| 0x1EAAA60 | 16 | W | `0xbc6375e  movaps [rsi+0x1EAAA60],xmm0` | store 16 bytes from data_f441430 to a0+0x1EAAA60 [V] |
| 0x1EBF080 | 16 | W | `0xbc63ac1  movaps [rsi+0x1EBF080],xmm0` | store 16 bytes from data_f0922e0 to a0+0x1EBF080 [V] |
| 0x12AE1751 | 1 | R | `0xbc636d6  cmp byte ptr [0x12AE1751],1` | compare global byte data_12ae1751 with 1 [V] |
| 0x128767C8 | 4 | R | `0xbc636df  mov eax,[0x128767C8]` | load global dword data_128767c8 (thread index) [V] |
| 0x1EAB088 | 4 | W | `0xbc63942  mov dword ptr [rsi+rbx+0x1EAB088],0` | zero dword field of loop element rbx [V] |
| 0x1EAB08C | 1 | W | `0xbc6394d  mov byte ptr [rsi+rbx+0x1EAB08C],0` | zero byte field of loop element rbx [V] |
| 0x1EAB08E | 8 | W | `0xbc6393a  mov [rsi+rbx+0x1EAB08E],rdi` | store 0x1000000000000 to qword field of loop element rbx [V] |
| 0x1EAB096 | 2 | W | `0xbc63930  mov word ptr [rsi+rbx+0x1EAB096],1` | store word 1 to field of loop element rbx [V] |
| 0x1EAB0A0 | 4 | W | `0xbc639b7  mov dword ptr [rsi+rbx+0x1EAB0A0],0x3F800000` | store float 1.0f to field of loop element rbx [V] |

## Phase summary (from the same verified listing)
1. 0xbc63690..0xbc63707: clear `this` flag/dword/byte fields, load two qword fields, call sub_ebdb740 store result to a0+0x1EBF1C8, branch on global byte data_12ae1751 [V].
2. 0xbc63709..0xbc6374a: thread start — lea thread name "bgfx - renderer backend thread" (data_f602711), call sub_ebdb9b0 with thread proc sub_bc65720 [V].
3. 0xbc6374a..0xbc63930: store sete bool to a0+0x1EBF2F1, write dword 0x78666762 ("bgfx") to TLS slot, then movaps-bulk zero/init 16-byte fields a0+0x1EAAA60..0x1EAAC30 from read-only constants [V].
4. 0xbc63930..0xbc63ab4: loop rbx=0..0x14000 step 0x140 — per-element field init (word=1, qword=0x1000000000000, dwords=0, bytes=0, floats=1.0f 0x3F800000, memset via sub_ebce430) [V].
5. 0xbc63aba..0xbc63b72: movaps store data_f0922e0 to a0+0x1EBF080..0x1EBF170, two memsets (0x1EA69E0 size 0x80, 0x1EA6A60 size 0x2000 fill 0xFF), tail-call sub_ebce430 [V].

## CLOSES?
NO — the M1c D2 item ("every structural function of L1-L3") is not met by what exists on disk now; this unit only documents Context::init 0xbc63690. Single blocking fact: pending decode remains for the 6cs header fields, slots 39-45, the 6 drain blocks of 0xbc660a0, the generate per-pass loop, and L4/L5 dossiers (endFrame 0x66232b0 + extractors); no precomputed input data files were provided for those offsets.

## TOOL REQUESTS
None
