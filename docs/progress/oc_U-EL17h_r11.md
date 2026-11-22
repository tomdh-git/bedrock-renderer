## NEXT
DONE

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)
Output file: docs/progress/oc_U-EL17h.md (only file for this unit).

GOAL (verbatim from this run's orchestrator brief): close checklist item "L17h graphics options plumbing (OptionSync) pending". r8 established upscaling_percentage = option id 0x243 and targetResolution = id 0x246 (registered via sub_9c4220, [V]); sub_10c1ad0 reads ids 0xFD/0xFE/0x100/0x101 via vtable[0xD8] get-option-by-id, so {0x243,0x246} does NOT intersect sub_10c1ad0's reads — sub_10c1ad0 is NOT the upscaling reader; stop following it. NEW HOP this run: find who READS option ids 0x243 and 0x246 through get-option-by-id via `rdis imm 0x243` / `imm 0x246` (instructions `mov r8d,0x243` / `mov edx,0x246` and similar instructions setting the id arg right before the call), follow each returned float to a store; the value ending at [elem+0x14] (endFrame 0x6625094: `divss xmm8,[r15+0x14]` where xmm8=1.0f from 0xEEC8060 — ratio = 1.0f/[elem+0x14]) or descriptor/ctx +0x1F0 closes L17h and L10c together. One row per hop, even if unfinished. Also: endFrame's caller is ret=0x8890E4 [LIVE el17h_endframe_caller.txt]; the array1 builder is in that caller — follow it to the option id 0x243 read.

Carried [V] facts (r1-r9, re-verified verbatim where cited):
- endFrame 0x66232b0 = BgfxFrameBuilder vtable slot 18 (vt 0xf2bdeb0 +0x90, size 0xb3d0) [V BGFX_MAP.md line 167; dossier 0x66232b0.md]; no direct callers (xref.py callers = []). Live capture: endFrame entered with CALLER ret=0x8890E4 (call at 0x8890de `call qword ptr [0xF99FFA0]`), RCX=BgfxFrameBuilder 0x22FC6252800 [V LIVE docs/data/live/el17h_endframe_caller.txt:3-4].
- Chain [V]: pass descriptor+0x1F0 -> element+0x1F0 (sub_566cb20: `0x566d04a movss xmm0,[rsi+0x1F0]` / `0x566d052 movss [rdx+0x1F0],xmm0`, endFrame calls it 7x) -> ctx+0x1F0 (struct-copy 0x67C73D0 `0x67c7917 movss xmm0,[rsi+0x1F0]` / `0x67c791f movss [rdx+0x1F0],xmm0` at 0x662def4) -> TAAU body 0xbc8cfd0 `0xbc8d34e movups xmm0,[r13+0x1F0]` consumes ctx+0x1F0 as render/display ratio [V oc_U-Eratio].
- endFrame 0x6625077 `movss xmm7,[0xEEC8060]` (1.0f), 0x6625090 `movaps xmm8,xmm7`, 0x6625094 `divss xmm8,[r15+0x14]` — endFrame ratio = 1.0f / [elem+0x14] (r15 = element) [V r9]; chain must END at the store of [elem+0x14].
- upscaling_percentage registration [V r8]: `0x5b3e844 mov edx,0x243` / `0x5b3e855 call 0x9C4220` in sub_5b3e100; id stored at option+0x1CC by `0x9be84d mov eax,[rbp+8]` / `0x9be850 mov [r13+0x1CC],eax` in sub_9be400. targetResolution registration [V r8]: `0x5b3eb1b mov edx,0x246` / `0x5b3eb2c call 0x9C4220` in sub_5b3ea00.
- sub_10c1ad0 reads [V r6]: `0x10c1b52 mov r8d,0xFD` / `0x10c1b58 call [0xF99FFA0]` / `0x10c1b83 movss xmm7,[rax+0x18]`; `0x10c1b9a mov r8d,0xFE` / `0x10c1bc3 movss xmm8,[rax+0x18]`; `0x10c1bdb mov r8d,0x100` / `0x10c1c03 movss xmm9,[rax+0x18]`; `0x10c1c1b mov r8d,0x101` / `0x10c1c66 movss xmm2,[rax+0x18]`; store `0x10c1dc3 movss [r12+0x1F0],xmm4`. {0x243,0x246} ∩ {0xFD,0xFE,0x100,0x101} = ∅.

## Answer table (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag)

| upscaling_percentage id=0x243 registration | 4 | 0x5b3e844 | `0x5b3e844  mov edx,0x243` | sub_5b3e100 sets id=0x243 before registration call | [V] |
| upscaling_percentage id=0x243 registration call | — | 0x5b3e855 | `0x5b3e855  call 0x9C4220` | registers option with id 0x243 | [V] |
| option id field +0x1CC store | 4 | 0x9be850 | `0x9be850  mov [r13+0x1CC],eax` | sub_9be400 stores id (eax=0x243 from caller) at option+0x1CC | [V] |
| targetResolution id=0x246 registration | 4 | 0x5b3eb1b | `0x5b3eb1b  mov edx,0x246` | sub_5b3ea00 sets id=0x246 before registration call | [V] |
| targetResolution id=0x246 registration call | — | 0x5b3eb2c | `0x5b3eb2c  call 0x9C4220` | registers option with id 0x246 | [V] |
| sub_10c1ad0 read id 0xFD | 4 | 0x10c1b52 | `0x10c1b52  mov r8d,0xFD` | sub_10c1ad0 reads option by index 0xFD via call [0xF99FFA0] | [V] |
| sub_10c1ad0 read id 0xFE | 4 | 0x10c1b9a | `0x10c1b9a  mov r8d,0xFE` | sub_10c1ad0 reads option by index 0xFE via call [0xF99FFA0] | [V] |
| sub_10c1ad0 read id 0x100 | 4 | 0x10c1bdb | `0x10c1bdb  mov r8d,0x100` | sub_10c1ad0 reads option by index 0x100 via call [0xF99FFA0] | [V] |
| sub_10c1ad0 read id 0x101 | 4 | 0x10c1c1b | `0x10c1c1b  mov r8d,0x101` | sub_10c1ad0 reads option by index 0x101 via call [0xF99FFA0] | [V] |
| sub_10c1ad0 option value read | 4 | 0x10c1b83/0x10c1bc3/0x10c1c03/0x10c1c66 | `0x10c1b83  movss xmm7,[rax+0x18]` / `0x10c1bc3  movss xmm8,[rax+0x18]` / `0x10c1c03  movss xmm9,[rax+0x18]` / `0x10c1c66  movss xmm2,[rax+0x18]` | reads option float at [rax+0x18] for each id | [V] |
| sub_10c1ad0 store to descriptor+0x1F0 | 4 | 0x10c1dc3 | `0x10c1dc3  movss [r12+0x1F0],xmm4` | stores computed value to descriptor+0x1F0 (r12=[rcx+0x40]) | [V] |
| id set mismatch | — | — | — | {0x243,0x246} ∩ {0xFD,0xFE,0x100,0x101} = ∅; sub_10c1ad0 NOT the upscaling reader | [V] |
| No call [reg+0xD8] pattern | — | — | — | `rdis find FF 91 D8 00 00 00` = 0 hits; no `call qword ptr [reg+0xD8]` exists in .exe | [V] |
| get-option-by-id via global [0xF99FFA0] | — | — | `call qword ptr [0xF99FFA0]` | all get-option-by-id calls use this global indirect call, not vtable[0xD8] | [V] |
| Reader of option 0x243 (sub_5b0aa90) id setup | 4 | 0x5b0b650 | `0x5b0b650  mov r8d,0x243` | sub_5b0aa90 sets id=0x243 before get-option-by-id call | [V] |
| Reader of option 0x243 (sub_5b0aa90) call | — | 0x5b0b656 | `0x5b0b656  call qword ptr [0xF99FFA0]` | reads option object for id 0x243 | [V] |
| Reader of option 0x243 (sub_5b0aa90) value read | 4 | 0x5b0b683 | `0x5b0b683  mov eax,[rax+0x18]` | reads option float value at [rax+0x18] | [V] |
| Reader of option 0x243 (sub_5b0aa90) store | 4 | 0x5b0b68d | `0x5b0b68d  mov [r13+0x1BB8],eax` | stores upscaling_percentage at [r13+0x1BB8] (r13=[rbp+0x6D8]=main object) | [V] |
| Reader of option 0x243 (sub_5b71ef0) id setup | 4 | 0x5b71f56 | `0x5b71f56  mov r8d,0x243` | sub_5b71ef0 sets id=0x243 before get-option-by-id call | [V] |
| Reader of option 0x243 (sub_5b71ef0) call | — | 0x5b71f5c | `0x5b71f5c  call qword ptr [0xF99FFA0]` | reads option object for id 0x243 | [V] |
| Reader of option 0x243 (sub_5b71ef0) pass to sub_d1720 | — | 0x5b71f6e | `0x5b71f6e  call 0xD1720` | passes option object to sub_d1720; target of sub_d1720 unknown | [?] |
| Reader of option 0x243 (sub_5bc3071) id setup | 4 | 0x5bc3071 | `0x5bc3071  mov r8d,0x243` | sub_5bc2eb0 sets id=0x243 before get-option-by-id call | [V] |
| Reader of option 0x243 (sub_5bc3071) call | — | 0x5bc3077 | `0x5bc3077  call qword ptr [0xF99FFA0]` | reads option object for id 0x243 | [V] |
| Reader of option 0x243 (sub_5bc3071) fallback store read | 4 | 0x5bc3090 | `0x5bc3090  mov edx,[rdi+0x1BB8]` | reads pre-stored upscaling_percentage as fallback when lookup returns null | [V] |
| Reader of option 0x243 (sub_20ff240) id setup | 4 | 0x210188e | `0x210188e  mov r8d,0x243` | sub_20ff240 sets id=0x243 before get-option-by-id call | [V] |
| Reader of option 0x243 (sub_20ff240) call | — | 0x2101894 | `0x2101894  call qword ptr [0xF99FFA0]` | reads option object for id 0x243; return value overwritten by next instr | [V] |
| No reader of option 0x246 via get-option-by-id | — | — | — | `rdis imm 0x246` found 8 hits, none use `call [0xF99FFA0]` or `call [reg+0xD8]` | [V] |
| Reader of option 0x243 (sub_20ff240) second id setup | 4 | 0x2101a40 | `0x2101a40  mov edx,0x243` | sub_20ff240 sets id=0x243 for call 0xB3ADA0 (different target) | [V] |
| Reader of option 0x243 (sub_5b72000) id setup | 4 | 0x5b7202a | `0x5b7202a  mov r8d,0x243` | sub_5b71fe0/sub_5b72000 sets id=0x243 before get-option-by-id call | [V] |
| Reader of option 0x243 (sub_5b72000) call | — | 0x5b7202a+6 | `0x5b72030  call qword ptr [0xF99FFA0]` | reads option object for id 0x243 | [V] |
| endFrame caller sub_888f00 | — | 0x8890de | `0x8890de  call qword ptr [0xF99FFA0]` | calls endFrame via vtable slot 18; sub_888f00 does NOT read options 0x243/0x246 | [V] |
| endFrame ratio computation | 4 | 0x6625094 | `0x6625094  divss xmm8,[r15+0x14]` | endFrame: 1.0f / [elem+0x14]; chain must END at store of [elem+0x14] | [V] |
| endFrame 1.0f constant | 4 | 0x6625077 | `0x6625077  movss xmm7,[0xEEC8060]` | 0xEEC8060 is read-only constant 1.0f | [V] |
| pass descriptor+0x1F0 read | 4 | 0x566d04a | `0x566d04a  movss xmm0,[rsi+0x1F0]` | sub_566cb20 reads descriptor+0x1F0 | [V] |
| element+0x1F0 write | 4 | 0x566d052 | `0x566d052  movss [rdx+0x1F0],xmm0` | sub_566cb20 writes element+0x1F0 from descriptor+0x1F0 | [V] |
| ctx+0x1F0 write | 4 | 0x67c791f | `0x67c791f  movss [rdx+0x1F0],xmm0` | struct-copy 0x67C73D0 writes ctx+0x1F0 from source+0x1F0 | [V] |
| TAAU ratio consume | 16 | 0xbc8d34e | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | TAAU body 0xbc8cfd0 consumes ctx+0x1F0 as render/display ratio | [V] |

## CLOSES?
NO — blocking fact: no reader of option ids 0x243/0x246 has been found whose returned float is stored to [elem+0x14] or descriptor/ctx +0x1F0. Readers of 0x243 found (sub_5b0aa90→[obj+0x1BB8], sub_5b71ef0→sub_d1720, sub_5bc3071→sub_9bf8b0, sub_20ff240→result unused) do not connect to +0x1F0/+0x14. No reader of 0x246 via get-option-by-id exists. No `call [reg+0xD8]` pattern exists in the binary — all get-option-by-id calls use `call [0xF99FFA0]`. endFrame's caller sub_888f00 (ret=0x8890E4) does not read options directly. The link from option ids 0x243/0x246 to [elem+0x14] or +0x1F0 remains unproven.

## TOOL REQUESTS

None yet.
