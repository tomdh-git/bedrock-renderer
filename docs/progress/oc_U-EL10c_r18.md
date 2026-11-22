## NEXT
DONE

UNIT U-EL10c (docs/progress/oc_U-EL10c.md only). L10c "viewport and render-resolution selection, dynamic resolution pending".

GOAL (verbatim from item line): close "L10c viewport and render-resolution selection, dynamic resolution pending". Do ONLY the pending part: who writes [elem+0x14] (the divisor float in endFrame's ratio computation `ratio = 1.0f / [elem+0x14]`) and link it to upscaling_percentage / options.targetResolution.

METHOD: static analysis of Minecraft.Windows.exe 1.26.62.01 (image-relative RVAs). Every quoted `0xRVA  instr` re-verified with rdis against the exe.

Chain worked backward from endFrame's ratio read `0x6625094  divss xmm8,[r15+0x14]` (r15 iterates array1=[rdx+0x38]..[rdx+0x40], stride 0x208, rdx=endFrame 2nd arg).
State entering this run (r17): element+0x14 = descriptor+0x14 = sub_e7e150([rbp+0x58]) return [V]. Hop-by-hop below.

EVIDENCE TABLE (name | rva or offset | size | verbatim `0xRVA  instr` proof | tag)

| endFrame reads elem+0x14 ratio divisor | 0x6625094 | 4 (divss) | `0x6625094  divss xmm8,[r15+0x14]` | r15 iterates array1 stride 0x208; ratio = 1.0f/[elem+0x14] | [V] |
| ratio numerator = rodata const 1.0f (no store exists) | 0x6625077 | 4 (movss) | `0x6625077  movss xmm7,[0xEEC8060]` | 0xEEC8060 = read-only 1.0f | [V] |
| sub_6ad150 WRITES element+0x10..0x1F (covers +0x14) | 0x6ad160 | 16 (movups) | `0x6ad160  movups [rax+0x10],xmm1` | WRITE element+0x14; rax=element dst, rdx=descriptor src | [V] |
| sub_6ad150 READS descriptor+0x10..0x1F (= elem+0x14 source register xmm1) | 0x6ad15c | 16 (movups) | `0x6ad15c  movups xmm1,[rdx+0x10]` | xmm1 originates from descriptor+0x14 | [V] |
| descriptor+0x14 ([rbp+0x294]) = sub_e7e150([rbp+0x58]) result | 0x88895b | 4 (movss) | `0x88895b  movss [rbp+0x294],xmm0` | sub_887860 stores descriptor+0x14 | [V] |
| sub_e7e150 argument read [rbp+0x58] (never written in sub_887860 => parameter) | 0x888951 | 8 (qword) | `0x888951  mov rcx,[rbp+0x58]` | sub_e7e150(rcx=[rbp+0x58]); origin = sub_887860 caller | [V] |
| sub_e7e150 guard: a0+0xCB0==1 ? vtable path : fallback | 0xe7e16c | 4 (cmp byte) | `e7e16c  cmp byte ptr [rcx+0xCB0],1` | rcx=rsi=a0=[rbp+0x58] | [V] |
| sub_e7e150 fallback returns a0+0x5C float | 0xe7e248 | 4 (movss) | `e7e248  movss xmm6,[rsi+0x5C]` | rsi=a0; returns float at object+0x5C | [V] |
| sub_e7e150 vtable path loads *(a0+0x98) vtable slot 0x108 | 0xe7e183 | 4 (load) | `e7e183  mov rax,[rax+0x108]` | *(*(a0+0x98)+0x0)+0x108 | [V] |
| sub_e7e150 vtable path indirect call [0xF99FFA0]=sub_eea6040 | 0xe7e18e | call | `e7e18e  call qword ptr [0xF99FFA0]` | returns object in rax | [V] |
| sub_e7e150 vtable path returns object->+0x18 float | 0xe7e1c4 | 4 (movss) | `e7e1c4  movss xmm6,[rax+0x18]` | rax=sub_88bb50 result; float at +0x18 | [V] |
| sub_e7e150 epilogue returns xmm0=xmm6 | 0xe7e24d | movaps | `e7e24d  movaps xmm0,xmm6` | returns descriptor+0x14 candidate | [V] |
| sub_88bb50 called by sub_e7e150 (format/size lookup, returns object ptr) | 0xe7e1b9 | call | `e7e1b9  call 0x88BB50` -> sub_88bb50 | reads [rax+0x18] afterwards; NOT a settings read | [V] |
| upscaling_percentage reader (id 0x243) via get-option-by-id vtable[0xD8] | 0x5b72030 | call | `0x5b7202a  mov r8d,0x243` / `0x5b72030  call qword ptr [0xF99FFA0]` | sub_5b72000 reads id 0x243; r17: does NOT flow to elem+0x14 | [V] |
| upscaling_percentage = option id 0x243 (registration) | 0x5b0ba9b | 4 (mov edx,imm) | `0x5b0ba9b  mov edx,0x243` | registered in Options ctor | [V] |
| options.targetResolution = option id 0x246 (registration) | 0x5b3eb1b | 4 (mov edx,imm) | `0x5b3eb1b  mov edx,0x246` | registered in Options ctor | [V] |

CLOSES? — NO

Single blocking fact: The [elem+0x14] writer IS proven ([V]): sub_6ad150 `0x6ad160 movups [rax+0x10],xmm1` writes element+0x10..0x1F (covers +0x14) from descriptor+0x14 (`0x6ad15c movups xmm1,[rdx+0x10]`), and descriptor+0x14 = sub_e7e150([rbp+0x58]) (`0x88895b movss [rbp+0x294],xmm0`). sub_e7e150 returns either [a0+0x5C] (`e7e248 movss xmm6,[rsi+0x5C]`) or sub_88bb50(a0)->+0x18 (`e7e1c4 movss xmm6,[rax+0x18]`). NEITHER is a read through the settings object (upscaling_percentage id 0x243 / targetResolution id 0x246). The settings reader sub_5b72000 (`0x5b72030 call [0xF99FFA0]` with r8d=0x243) is a separate, disconnected path — r17: "does NOT flow to elem+0x14". [rbp+0x58] is sub_887860's parameter (caller 0x879480 via indirect call), origin/+0x5C writer not tied to upscaling_percentage. No chain row from a settings read to the [elem+0x14] store exists, so L10c cannot close.

TOOL REQUESTS: None — all evidence gathered with rdis.exe, xref.py, dumplist.py and reads of prior r16/r17 notes. No new scripts written.
