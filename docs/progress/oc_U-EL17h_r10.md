## NEXT
DONE

# UNIT U-EL17h — L17h graphics options plumbing (OptionSync)

Item line: Close checklist item: L17h graphics options plumbing (OptionSync) pending | 2026-11-16 oc_U-Eratio.md (9 rows OK): NO; ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers)

Orchestrator 2026-11-22 state (treated as verified unless disassembly contradicts):
- upscaling_percentage = option id 0x243, targetResolution = id 0x246 (registered, [V]). sub_10c1ad0 (reads ids 0xFD/0xFE/0x100/0x101) is NOT the upscaling reader; STOP following it.
- find who READS option ids 0x243/0x246 via get-option-by-id (vtable[0xD8]): `mov r8d,0x243`/`mov edx,0x246` right before `call [reg+0xD8]`. Follow the float to a store at [elem+0x14] or descriptor/ctx +0x1F0.
- endFrame's caller is ret=0x8890E4 [LIVE el17h_endframe_caller.txt]; the array1 builder is in that caller. Follow it to the option id 0x243 read.
- endFrame 0x66232b0 has no direct callers: BgfxFrameBuilder vtable slot 18 (offset 0x90).
- Chain proven: descriptor +0x1F0 -> element +0x1F0 (sub_566cb20 at 0x566d04a/0x566d052) -> ctx +0x1F0 (0x67c791f). Remaining: who stores descriptor +0x1F0.
- L10c: ctx+0x1F0 = 1.0f / [elem+0x14] in endFrame 0x6625094; 0xEEC8060 is read-only 1.0f. Chain must END at the store of [elem+0x14].

Known zero-hit captures: er5_clone_4c8a5b0, l8b_resizetex_slot31, oc_u_el6b_desc, el10b_lighting_desc.

LIVE read: docs/data/live/el17h_endframe_caller.txt (24 samples, 18090 hits) — every line ret=0x8890E4 [V live].

## FINDINGS (table: offset | size | site | instr | meaning)

| offset    | size     | site                                           | instr                                                       | meaning                                                       |
|-----------|----------|------------------------------------------------|-------------------------------------------------------------|---------------------------------------------------------------|
| 0x5b71f47 | 8 (qword)| sub_5b719b0 option-0x243 reader                | `0x5b71f47  mov rax,[rax+0xD8]`                             | [V] loads vtable[0xD8] (get_option_by_id ptr); object rsi=[rsp+0x28] |
| 0x5b71f56 | 4        | sub_5b719b0 option-0x243 reader                | `0x5b71f56  mov r8d,0x243`                                  | [V] id argument = upscaling_percentage (0x243)                |
| 0x5b71f5c | 8 (call) | sub_5b719b0 option-0x243 reader                | `0x5b71f5c  call qword ptr [0xF99FFA0]`                     | [V] calls sub_eea6040 = jmp rax → invokes vtable[0xD8]        |
| 0x5bc3063 | 8 (qword)| sub_5bc2eb0 option-0x243 reader                | `0x5bc3063  mov eax,[rax+0xD8]`                             | [V] loads vtable[0xD8] (get_option_by_id ptr); object rdi     |
| 0x5bc3071 | 4        | sub_5bc2eb0 option-0x243 reader                | `0x5bc3071  mov r8d,0x243`                                  | [V] id argument = upscaling_percentage (0x243)                |
| 0x5bc3077 | 8 (call) | sub_5bc2eb0 option-0x243 reader                | `0x5bc3077  call qword ptr [0xF99FFA0]`                     | [V] calls sub_eea6040 = jmp rax → invokes vtable[0xD8]        |
| 0xeea6040 | 1        | sub_eea6040 indirect-call thunk                | `0xeea6040  jmp rax`                                        | [V] indirect-call target; rax holds vtable[0xD8] result       |
| 0x5b71f62 | 8        | option-0x243 result read                       | `0x5b71f62  mov rsi,[rsp+0x28]`                             | [V] get-option-by-id output pointer read back                 |
| 0x5bc307d | 8        | option-0x243 result read                       | `0x5bc307d  mov rcx,[rsp+0x20]`                             | [V] get-option-by-id output pointer read back                 |
| 0x888c42  | 8 (qword)| array1 builder vtable[0xD8] get_option_by_id   | `0x888c42  mov rax,[rax+0x6C0]`                             | [V] loads vtable[0x6C0]=slot 0xD8 (get_option_by_id); object [rbp+0x4D8] |
| 0x888c50  | 8 (call) | array1 builder vtable[0xD8] get_option_by_id   | `0x888c50  call qword ptr [0xF99FFA0]`                      | [V] output [rbp+0x280]; id argument (r8d) not visible as imm  |
| 0x888d46  | 4 (movss)| array1 builder container field load            | `0x888d46  movss xmm1,[rbx+0x18]`                           | [V] loads [rbx+0x18]; rbx=sub_88bb50() object lookup          |
| 0x888d4b  | 4 (movss)| array1 builder container+0x14 store            | `0x888d4b  movss [rbp+0x294],xmm1`                          | [?] writes [rbp+0x280]+0x14 from [rbx+0x18]; link to option 0x243 unproven |
| 0x8890d0  | 8 (qword)| endFrame vtable[0x90] call                     | `0x8890d0  mov rax,[rax+0x90]`                              | [V] loads BgfxFrameBuilder vtable slot 18 = endFrame          |
| 0x8890de  | 8 (call) | endFrame vtable call                           | `0x8890de  call qword ptr [0xF99FFA0]`                      | [V] calls endFrame; returns to ret=0x8890E4 [LIVE]            |
| 0x66232fa | 8 (qword)| endFrame prologue                              | `0x66232fa  mov [rbp+0x1998],rdx`                           | [V] stores endFrame 2nd arg = array1 container                |
| 0x662504d | 8 (qword)| endFrame element-array begin                   | `0x662504d  mov r15,[rcx+0x38]`                             | [V] r15 = element array begin ([rbp+0x1998]+0x38)             |
| 0x6625055 | 8 (qword)| endFrame element-array end                     | `0x6625055  mov [rbp+0x19A0],rcx`                           | [V] element array end ([rbp+0x1998]+0x40)                     |
| 0x6625077 | 4 (movss)| endFrame 1.0f constant                         | `0x6625077  movss xmm7,[0xEEC8060]`                         | [V] read-only constant 1.0f (L10c hint)                       |
| 0x6625094 | 4        | endFrame [elem+0x14] read                      | `0x6625094  divss xmm8,[r15+0x14]`                          | [V] xmm8 = 1.0f / [elem+0x14] → ctx ratio (L10c hint)         |

## OPEN

1. [BLOCKING] Store of [elem+0x14] linked to option id 0x243 NOT found. endFrame reads [elem+0x14] at `0x6625094  divss xmm8,[r15+0x14]` [V], but the writer of [elem+0x14] (and its derivation from option 0x243) is not statically identified. The array1 builder writes [rbp+0x280]+0x14 ([rbp+0x294]) from [rbx+0x18] at `0x888d4b  movss [rbp+0x294],xmm1` [V], but rbx = sub_88bb50() object lookup (not an option read), and the container->element relationship is unresolved — [rbp+0x280]+0x38/+0x40 should be the elem array but [rbp+0x2B8] (+0x38) is written as 1.0f at `0x888d7b  mov dword ptr [rbp+0x2B8],0x3F800000`, contradiction unresolved (possibly overwritten by sub_6a0350/sub_88bb10 before the endFrame call at 0x8890de).
2. [BLOCKING] Option id read at array1-builder vtable[0xD8] call (`0x888c50  call qword ptr [0xF99FFA0]`): the id argument (r8d) is not set as an immediate in this function (no `mov r8d,0x243` in 0x888xxx per exhaustive `rdis imm 0x243` scan), so it is unproven that this call reads option 0x243.
3. [BLOCKING] Option id 0x246 (targetResolution) reader via vtable[0xD8] NOT found: exhaustive `rdis imm 0x246` scan found no `mov r8d/edx,0x246` before `call [reg+0xD8]`; all other 0x246 immediates are SSL/crypto coincidences.
4. source(r13)+0x1F0 writer (descriptor+0x1F0 / passLookup descriptor) NOT found statically (per prior checklist item; endFrame 0x66232b0 has no direct callers, called via vtable).

## CLOSES?

NO — blocking fact: the store of [elem+0x14] derived from option id 0x243 is not statically identified (endFrame reads [elem+0x14] at `0x6625094  divss xmm8,[r15+0x14]` [V] but its writer is unknown), and the option id 0x246 vtable[0xD8] reader is not found. The array1-builder vtable[0xD8] call at `0x888c50` is confirmed but its id argument (r8d) is not visible statically.

## TOOL REQUESTS

1. Capture the function containing the array1-builder vtable[0xD8] call at `0x888c50` to observe the id argument (r8d) at the `call qword ptr [0xF99FFA0]` — need the function's entry RVA (sub_888c00 is mid-function; entry not yet located). Question: does this get-option-by-id call read option id 0x243, and does its result feed [elem+0x14]? Trigger: in-game graphics/upscaling settings change or per-frame render.
2. If (1) is not feasible, capture endFrame (0x66232b0) or the element-array builder to observe [elem+0x14] being written and trace it back to option 0x243. ret=0x8890E4 [LIVE el17h_endframe_caller.txt].
