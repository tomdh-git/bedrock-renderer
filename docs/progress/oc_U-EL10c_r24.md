## NEXT
DONE

UNIT U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending.
Output file: docs/progress/oc_U-EL10c.md (only file for this unit).
Minecraft.Windows.exe 1.26.62.01, image-relative RVAs. Live data cited as [LIVE docs/data/live/<file>:line].
Tags: [V] = seen in rdis disassembly, [V live] = seen in live capture bytes, [I] = inferred, [?] = unknown.

GOAL (this run): decode [a0+0x5C] float per sample in u_el10c_e7e150.txt grouped by ret= caller; for u_el10c_887860.txt identify which register holds the object whose +0x5C is read and decode it. Report the value and hop chain; state whether it changes with in-game upscaling_percentage.

Class of a0 (sub_e7e150's argument = [rbp+0x58] in sub_887860): live vptr 0x7FF614C9B220 - game base 0x7FF605BE0000 = vtable RVA 0xF0BB220 [V live + rdis vt].
- `rdis vt 0xF0BB220`: slot 0 sub_ecb4f0 (0x6c8), slot 0xb8 sub_eb76c0 (0x4000), remaining slots ret/non-code.
- `rdis xr 0xF0BB220`: `0xe89eda  lea rax,[0xF0BB220]` (sub_e89e00+0xda) and `0xecb50e  lea rax,[0xF0BB220]` (sub_ecb4f0+0x1e) — two constructors set vptr 0xF0BB220 [V].

EVIDENCE TABLE (offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag)
| offset | size | site | instr | meaning | tag |
| 0x887860 | 1 | sub_887860 start | `0x887860  push rbp` | sub_887860 [0x887860..0x8897f9) contains 0x88895b; fn start RVA = 0x887860 via rdis fn; exactly 1 xref in (sub_879480) | [V] |
| 0x888951 | 8 | sub_887860 [rbp+0x58] | `0x888951  mov rcx,[rbp+0x58]` | only access to [rbp+0x58] in the whole listing 0x887860..0x8897f9: a LOAD; [rbp+0x58] is NEVER stored in sub_887860, passed as sub_e7e150's a0 | [V] |
| 0x888955 | 5 | sub_887860 call | `0x888955  call 0xE7E150` | sub_e7e150([rbp+0x58]); invoked from sub_879480 `0x87bd0f  call 0x887860` returning to 0x87bd14 nop = live capture ret=0x87BD14 | [V] |
| 0x88895b | 4 | sub_887860 descriptor+0x14 | `0x88895b  movss [rbp+0x294],xmm0` | [rbp+0x294] = descriptor base [rbp+0x280] + 0x14 := sub_e7e150 return | [V] |
| 0xe7e16c | 1 | sub_e7e150 flag guard | `0xe7e16c  cmp byte ptr [rcx+0xCB0],1` | flag [a0+0xCB0]; ==1 -> vtable/sub_88bb50 path, !=1 -> [a0+0x5C] fallback | [V] |
| 0xe7e248 | 4 | sub_e7e150 fallback return | `0xe7e248  movss xmm6,[rsi+0x5C]` | returns [a0+0x5C] float when flag != 1 (rsi = a0 = [rbp+0x58]) | [V] |
| 0xe7e1c4 | 4 | sub_e7e150 settings path | `0xe7e1c4  movss xmm6,[rax+0x18]` | flag==1 -> returns [sub_88bb50(vcall(*(a0+0x98)+0x108))+0x18] via `0xe7e1b9  call 0x88bb50`, `0xe7e183  mov rax,[rax+0x108]` | [V] |
| 0xe89eda | 8 | sub_e89e00 ctor vptr | `0xe89eda  lea rax,[0xF0BB220]` | constructor sets a0 vptr = vtable 0xF0BB220; immediately followed by `0xe89ee1  mov [rbx],rax` (W a0+0x0) | [V] |
| 0xe89f0d | 8 | sub_e89e00 ctor +0x5C | `0xe89f0d  movsd [rbx+0x5C],xmm1` | constructor DEFAULT write to a0+0x5C; xmm1 loaded by `0xe89f05  movsd xmm1,[0xF0B86B0]` | [V] |
| 0xe8a801 | 1 | sub_e89e00 ctor flag | `0xe8a801  mov byte ptr [r14+0xCB0],0` | constructor initializes flag [a0+0xCB0] = 0, so sub_e7e150 takes the [a0+0x5C] fallback | [V] |
| 0x87bd0f | 5 | sub_879480 caller | `0x87bd0f  call 0x887860` | only caller of sub_887860 (1 xref); rets to 0x87bd14 nop = [LIVE u_el10c_887860.txt:4] CALLER ret=0x87BD14 | [V] |
| LIVE:e7e150:+0x5C | 4 | u_el10c_e7e150.txt L4/L9/L13/L17 | `-` | RCX=a0=0x22FC7F44600; +0x5C bytes 00 00 00 40 = float 2.0 for ret= 0x6608063 (L4), 0xE6FE79 (L9), 0xE6FE95 (L13), 0xE6FEBF (L17); same object, constant across caller groups | [V live] |
| LIVE:887860:+0x5C | 8 | u_el10c_887860.txt L4 | `-` | RCX=0x22FC62D0000 = sub_887860's own a0 (-> saved at [rbp+0x588] by `0x88791b  mov [rbp+0x588],rdi`); [RCX+0x5C] bytes f6 7f 00 00 = qword pointer, NOT the scale float. R9=0x7FFE4000 (stack) +0x5C=0.0; R8 code/zeros not objects. No RDX captured: no register holds [rbp+0x58]'s object | [V live] |

LIVE DATA DECODE (python struct '<f', 0x100-byte dumps at register value)

u_el10c_e7e150.txt (target sub_e7e150 entry; RCX == a0):
- [LIVE u_el10c_e7e150.txt:4] ret=0x6608063, RCX=0x22FC7F44600, +0x5C bytes 00 00 00 40 -> float 2.0
- [LIVE u_el10c_e7e150.txt:9] ret=0xE6FE79, RCX=0x22FC7F44600, +0x5C -> float 2.0
- [LIVE u_el10c_e7e150.txt:13] ret=0xE6FE95, RCX=0x22FC7F44600, +0x5C -> float 2.0
- [LIVE u_el10c_e7e150.txt:17] ret=0xE6FEBF, RCX=0x22FC7F44600, +0x5C -> float 2.0
Same object address in all 4 samples; [a0+0x5C] = 2.0f in every captured caller group (ret= 0x6608063, 0xE6FE79, 0xE6FE95, 0xE6FEBF). R8/R9 point at string tables / small handles ([+0x5C] not a float); RDX=0x14B580 small ([+0x5C]=0.0).

u_el10c_887860.txt (target sub_887860 entry, CALLER ret=0x87BD14, 1 sample):
- [LIVE u_el10c_887860.txt:4] RCX=0x22FC62D0000 (sub_887860's own a0); [RCX+0x5C] bytes f6 7f 00 00 -> qword pointer, not the scale float (decoded f32 = 4.59e-41, meaningless).
- [LIVE u_el10c_887860.txt:6] R9=0x7FFE4000 (stack), [+0x5C]=0.0. R8=0x7FF6184B4483 (code) and R8=0xF4283 (all zeros) -> [+0x5C]=0.0. No RDX line captured.
-> No register in the sub_887860 capture holds [rbp+0x58]'s object. RCX is sub_887860's own a0 (vptr 0x7FF614C72B50, a DIFFERENT class than a0's 0xF0BB220); its +0x5C is a pointer. [rbp+0x58] (e7e150's argument object = 0x22FC7F44600 per the e7e150 capture) is a sub_887860 stack slot, never written there (only loaded at 0x888951), set by caller sub_879480's mechanism outside this function.

ANSWER (value + upscaling_percentage dependence):
- [a0+0x5C] = 2.0f CONSTANT. It does NOT change with in-game upscaling_percentage in this capture: single live session, identical 2.0f across all 4 captured caller groups and the same object address. The value is the constructor default (sub_e89e00 `0xe89f0d  movsd [rbx+0x5C],xmm1`, xmm1=data_0xF0B86B0 at `0xe89f05`), set when the object (vtable 0xF0BB220) is constructed; flag [a0+0xCB0] is initialized to 0 (`0xe8a801`), so sub_e7e150 takes the [a0+0x5C] fallback (`0xe7e16c  cmp byte ptr [rcx+0xCB0],1` -> `0xe7e248  movss xmm6,[rsi+0x5C]`).
- The alternative flag==1 path reads [sub_88bb50(a0)+0x18] (`0xe7e1c4`, `0xe7e1b9  call 0x88bb50`, `0xe7e183  mov rax,[rax+0x108]`); sub_88bb50 looks up the settings tree by hash 0xDA6A3486 (`0x88bccf  mov r8d,0xDA6A3486`, `0x88bcd8  call 0x1219a0`) — that hash is NOT option id 0x243 (sub_5b72000 `0x5b7202a  mov r8d,0x243` / `0x5b72030  call qword ptr [0xF99FFA0]` returns void via unresolved virtual setters on [a0+0x1A40], never stores +0x5C). So upscaling_percentage is disconnected from [a0+0x5C]/descriptor+0x14/element+0x14 via this path.

HOP CHAIN (element+0x14 scale = descriptor+0x14 = sub_e7e150([rbp+0x58])):
Hop 1 [V]: descriptor+0x14 := sub_e7e150([rbp+0x58]) — `0x888951  mov rcx,[rbp+0x58]` / `0x888955  call 0xE7E150` / `0x88895b  movss [rbp+0x294],xmm0` (sub_887860; called `0x87bd0f  call 0x887860` from sub_879480).
Hop 2 [V]: sub_e7e150 returns [a0+0x5C] (`0xe7e248  movss xmm6,[rsi+0x5C]`) when flag [a0+0xCB0]!=1 (`0xe7e16c`); or [sub_88bb50(...)+0x18] (`0xe7e1c4`) when flag==1.
Hop 3 [V]: [a0+0x5C] default = 2.0f written by ctor sub_e89e00 `0xe89f0d  movsd [rbx+0x5C],xmm1` (vptr 0xF0BB220 at `0xe89eda`/`0xe89ee1`).
Hop 4 [V live]: live [a0+0x5C] = 2.0f constant across ret= 0x6608063/0xE6FE79/0xE6FE95/0xE6FEBF ([LIVE u_el10c_e7e150.txt:4/9/13/17]).
Hop 5 [I]: not option-driven — sub_5b72000 id-0x243 read returns void via unresolved setters; no store to +0x5C; hash 0xDA6A3486 not linked to id 0x243.

CLOSES? — NO
Single blocking fact: [a0+0x5C] = 2.0f is proven constant (ctor default, live), but it is NOT derived from upscaling_percentage (option id 0x243): sub_5b72000 returns void via unresolved virtual setters on [a0+0x1A40] and never stores +0x5C, sub_88bb50 uses a different key (hash 0xDA6A3486), and [rbp+0x58]'s object type/+0x5C setter is not tied to the option. So element+0x14 = constant 2.0 here (ratio 1/2 constant), not option-driven; the L10c upscaling link is not closed by this path.

TOOL REQUESTS: None — all evidence from rdis.exe (vt/xr/dis/fld) and reads of docs/data/live/*.txt; live float decode was a throwaway python one-liner (struct '<f'), no script saved.
