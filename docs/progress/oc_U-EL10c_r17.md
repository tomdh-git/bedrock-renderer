## NEXT
DONE

UNIT U-EL10c (docs/progress/oc_U-EL10c.md only). L10c "viewport and render-resolution selection, dynamic resolution".

TASK: find who writes element+0x14 (the scale/size float read by endFrame 0x66232b0 at `0x6625094  divss xmm8,[r15+0x14]` to compute ratio = 1.0f/[elem+0x14]) and whether that value derives from upscaling_percentage (option id 0x243) / options.targetResolution (id 0x246). One chain row from the setting read to the [elem+0x14] store closes L10c.

Hit captures (zero-hit, code did not run in a lobby — headers only, no hit lines): er5_clone_4c8a5b0, l8b_resizetex_slot31, oc_u_el6b_desc, el10b_lighting_desc. Not needed for this item.

PROVEN [V] context:
- endFrame 0x66232b0 computes ratio = 1.0f / [r15+0x14] at 0x6625094; the 1.0f numerator is the read-only rodata constant at 0xEEC8060 (verified PAGE_READONLY, bytes 00 00 80 3F = 1.0f, no store exists).
- r15 iterates the element array [rdx+0x38 .. rdx+0x40) with stride 0x208: `0x662504d  mov r15,[rcx+0x38]` (base), `0x6625055  mov [rbp+0x19A0],rcx` (rcx = [rcx+0x40] = end), `0x6625898  add r15,0x208`, `0x662589f  cmp r15,[rbp+0x19A0]`, `0x66258a6  jne 0x6625090`.
- The element array is sub_887860's local vector ([rbp+0x540]=begin, [rbp+0x548]=end), filled by sub_88bb10 push_back which copies descriptor [rbp+0x280] into each element via sub_6ad150: `0x88bb30  add qword ptr [rsi+8],0x208` (end += stride 0x208), `0x888fa5  movups [rbp+0x2B8],xmm1` ([rbp+0x2B8]/[rbp+0x2C0] = [rbp+0x540]/[rbp+0x548] passed to endFrame as rdx+0x38/+0x40).
- sub_6ad150 copies descriptor+0x10..+0x1F (16 bytes, covers +0x14) → element+0x10..+0x1F: `0x6ad15c  movups xmm1,[rdx+0x10]` (read descriptor+0x14), `0x6ad160  movups [rax+0x10],xmm1` (WRITE element+0x14). So element+0x14 = descriptor+0x14.
- descriptor+0x14 ([rbp+0x294]) = return of sub_e7e150([rbp+0x58]): `0x888951  mov rcx,[rbp+0x58]`; `0x888955  call 0xE7E150`; `0x88895b  movss [rbp+0x294],xmm0`. sub_e7e150 returns either [rcx+0x5C] or ([rcx+0x98] → vtable[0x108] → object)+0x18. [rbp+0x58] is not written anywhere in sub_887860 (only read at 0x888951).
- upscaling_percentage = option id 0x243 [V] (L17h r8; registered via sub_5b673d0 `0x5b0ba9b  mov edx,0x243`). options.targetResolution = id 0x246 [V] (L17h r8). sub_5b72000 reads id 0x243 through the get-option-by-id vtable[0xD8] call: `0x5b7201e  mov rax,[rax+0xD8]`; `0x5b7202a  mov r8d,0x243`; `0x5b72030  call qword ptr [0xF99FFA0]` — but this read does NOT flow to elem+0x14.

EVIDENCE TABLE (name | rva or offset | size | verbatim `0xRVA  instr` proof | tag)

| endFrame reads elem+0x14 scale: ratio = 1.0f / [elem+0x14] | 0x6625094 | 4 (divss) | `0x6625094  divss xmm8,[r15+0x14]` | [V] |
| 1.0f numerator (read-only rodata constant, no store exists) | 0x6625077 | 4 (movss) | `0x6625077  movss xmm7,[0xEEC8060]` | [V] |
| element iterator base r15 = [rcx+0x38] | 0x662504d | 8 (qword) | `0x662504d  mov r15,[rcx+0x38]` | [V] |
| element array end = [rcx+0x40] stored to [rbp+0x19A0] | 0x6625055 | 8 (qword) | `0x6625055  mov [rbp+0x19A0],rcx` | [V] |
| element stride 0x208, loop back-edge to divss | 0x6625898 | 8 (add r64,imm32) | `0x6625898  add r15,0x208` | [V] |
| element array base/end = sub_887860 [rbp+0x540]/[rbp+0x548] -> endFrame rdx+0x38/+0x40 | 0x888fa5 | 16 (movups) | `0x888fa5  movups [rbp+0x2B8],xmm1` | [V] |
| sub_88bb10 push_back: element end += stride 0x208 | 0x88bb30 | 8 (qword) | `0x88bb30  add qword ptr [rsi+8],0x208` | [V] |
| sub_6ad150 WRITES element+0x14 (movups +0x10..+0x1F covers +0x14) | 0x6ad160 | 16 (movups) | `0x6ad160  movups [rax+0x10],xmm1` | [V] |
| sub_6ad150 READS descriptor+0x14 (covers elem+0x14 source) | 0x6ad15c | 16 (movups) | `0x6ad15c  movups xmm1,[rdx+0x10]` | [V] |
| descriptor+0x14 ([rbp+0x294]) = sub_e7e150([rbp+0x58]) result | 0x88895b | 4 (movss) | `0x88895b  movss [rbp+0x294],xmm0` | [V] |
| sub_e7e150 argument [rbp+0x58] read (never written in sub_887860) | 0x888951 | 8 (qword) | `0x888951  mov rcx,[rbp+0x58]` | [V] |
| upscaling_percentage = option id 0x243 (registration) | 0x5b0ba9b | 4 (mov edx,imm) | `0x5b0ba9b  mov edx,0x243` | [V] |
| upscaling_percentage id 0x243 read via get-by-id vtable[0xD8] | 0x5b7202a | 4 (mov r8d,imm) | `0x5b7202a  mov r8d,0x243` / `0x5b72030  call qword ptr [0xF99FFA0]` | [V] |
| options.targetResolution = option id 0x246 (registration) | 0x5b3eb1b | 4 (mov edx,imm) | `0x5b3eb1b  mov edx,0x246` | [V] |

CLOSES? — NO

Single blocking fact: the [elem+0x14] writer IS proven (sub_6ad150 `0x6ad160  movups [rax+0x10],xmm1`, element+0x14 = descriptor+0x14), but descriptor+0x14 = sub_e7e150([rbp+0x58]) return value is NOT shown to derive from upscaling_percentage (id 0x243) or options.targetResolution (id 0x246). sub_5b72000's id-0x243 read (`0x5b72030  call qword ptr [0xF99FFA0]`) does not flow to elem+0x14. No chain row from the setting read to the [elem+0x14] store exists, so L10c cannot close.

TOOL REQUESTS: None (all evidence gathered with rdis.exe, xref.py and reads of docs/progress/hints/L10c.txt, L17h.txt, docs/functions/66232b0.md, docs/data/live/).
