## NEXT
DONE

UNIT U-EL10c (docs/progress/oc_U-EL10c.md only). L10c "viewport and render-resolution selection, dynamic resolution pending".

GOAL: close L10c by finding who writes [elem+0x14] (divisor float in endFrame's `ratio = 1.0f / [elem+0x14]`, read at `0x6625094 divss xmm8,[r15+0x14]`) and linking it to upscaling_percentage (option id 0x243) / options.targetResolution (id 0x246). Work backwards by copies, one hop per table row. Stop when source is a settings-object read (get-option-by-id 0xFD/0xFE/0x100/0x101 or upscaling_percentage id 0x243).

METHOD: static analysis of Minecraft.Windows.exe 1.26.62.01 (image-relative RVAs). Every quoted `0xRVA  instr` re-verified with rdis against the exe.

CONTEXT (verified facts from prior runs):
- endFrame 0x66232b0 reads [r15+0x14] at 0x6625094; r15 iterates array1=[rdx+0x38]..[rdx+0x40] where rdx=endFrame 2nd arg ([rbp+0x1998], set once at 0x66232fa, never rewritten).
- Ratio numerator = rodata const 1.0f at `0x6625077 movss xmm7,[0xEEC8060]` — 0xEEC8060 is PAGE_READONLY constant 1.0f (bytes 00 00 80 3F), NOT stored, NOT a render-width var.
- upscaling_percentage = option id 0x243; targetResolution = id 0x246. Settings reader sub_5b72000 at `0x5b72030 call qword ptr [0xF99FFA0]` with `0x5b7202a mov r8d,0x243` — verified present in exe but NOT connected to this chain.
- endFrame's caller known live: ret=0x8890E4 (docs/data/live/el17h_endframe_caller.txt). Caller = sub_887860 (0x887860..0x8897f9), calls endFrame via vtable[18]+sub_eea6040 tail-call at `0x8890d0 mov rax,[rax+0x90]; 0x8890d7 lea rdx,[rbp+0x280]; 0x8890de call qword ptr [0xF99FFA0]`, returns to 0x8890e4. rdx=endFrame 2nd arg = [rbp+0x280] (descriptor base).

EVIDENCE TABLE (name | rva or offset | size | verbatim `0xRVA  instr` proof | tag)

| endFrame reads elem+0x14 ratio divisor | 0x6625094 | 4 (divss) | `0x6625094  divss xmm8,[r15+0x14]` | r15 iterates array1 elements; ratio = 1.0f/[elem+0x14] | [V] |
| ratio numerator = rodata const 1.0f (no store exists) | 0x6625077 | 4 (movss) | `0x6625077  movss xmm7,[0xEEC8060]` | 0xEEC8060 = read-only 1.0f constant | [V] |
| sub_6ad150 WRITES element+0x10..0x1F (covers +0x14) | 0x6ad160 | 16 (movups) | `0x6ad160  movups [rax+0x10],xmm1` | WRITE element+0x14; rax=element dst, rdx=descriptor src | [V] |
| sub_6ad150 READS descriptor+0x10..0x1F (= xmm1 source for elem+0x14) | 0x6ad15c | 16 (movups) | `0x6ad15c  movups xmm1,[rdx+0x10]` | xmm1 originates from descriptor+0x10..0x17 (includes descriptor+0x14) | [V] |
| descriptor+0x14 ([rbp+0x294]) = sub_e7e150([rbp+0x58]) return | 0x88895b | 4 (movss) | `0x88895b  movss [rbp+0x294],xmm0` | sub_887860 stores descriptor+0x14; [rbp+0x280]=descriptor base, +0x14=+0x294 | [V] |
| sub_e7e150 argument read [rbp+0x58] (never written in sub_887860 => parameter) | 0x888951 | 8 (qword) | `0x888951  mov rcx,[rbp+0x58]` | sub_e7e150(rcx=[rbp+0x58]); origin = sub_887860 caller | [V] |
| sub_e7e150 guard: a0+0xCB0==1 ? vtable path : fallback | 0xE7E16C | 4 (cmp byte) | `e7e16c  cmp byte ptr [rcx+0xCB0],1` | rcx=rsi=a0=[rbp+0x58] | [V] |
| sub_e7e150 fallback returns a0+0x5C float | 0xE7E248 | 4 (movss) | `e7e248  movss xmm6,[rsi+0x5C]` | rsi=a0; returns float at object+0x5C | [V] |
| sub_e7e150 vtable path loads *(a0+0x98) vtable slot 0x108 | 0xE7E183 | 4 (load) | `e7e183  mov rax,[rax+0x108]` | *(*(a0+0x98)+0x0)+0x108 | [V] |
| sub_e7e150 vtable path indirect call [0xF99FFA0]=sub_eea6040 | 0xE7E18E | call | `e7e18e  call qword ptr [0xF99FFA0]` | returns object in rax | [V] |
| sub_e7e150 vtable path returns object->+0x18 float | 0xE7E1C4 | 4 (movss) | `e7e1c4  movss xmm6,[rax+0x18]` | rax=sub_88bb50 result; float at +0x18 | [V] |
| sub_e7e150 epilogue returns xmm0=xmm6 | 0xE7E24D | movaps | `e7e24d  movaps xmm0,xmm6` | returns descriptor+0x14 candidate | [V] |
| sub_88bb50 called by sub_e7e150 (format/size lookup, returns object ptr) | 0xE7E1B9 | call | `e7e1b9  call 0x88BB50` -> sub_88bb50 | reads [rax+0x18] afterwards; NOT a settings read | [V] |
| upscaling_percentage reader (id 0x243) via get-option-by-id | 0x5B72030 | call | `0x5b7202a mov r8d,0x243` / `0x5b72030 call qword ptr [0xF99FFA0]` | sub_5b72000 reads id 0x243; DISCONNECTED from elem+0x14 chain | [V] |
| upscaling_percentage = option id 0x243 (registration) | 0x5B0BA9B | 4 (mov edx,imm) | `0x5b0ba9b  mov edx,0x243` | registered in Options ctor | [V] |
| options.targetResolution = option id 0x246 (registration) | 0x5B3EB1B | 4 (mov edx,imm) | `0x5b3eb1b  mov edx,0x246` | registered in Options ctor | [V] |

CHAIN SUMMARY (hop-by-hop):
Hop 1 [V]: element+0x14 ← descriptor+0x14 via sub_6ad150 `0x6ad160 movups [rax+0x10],xmm1` (16-byte block copy covering +0x10..+0x1F, includes +0x14), source xmm1 from `0x6ad15c movups xmm1,[rdx+0x10]` (descriptor+0x10..0x17).
Hop 2 [V]: descriptor+0x14 ← sub_e7e150([rbp+0x58]) via `0x88895b movss [rbp+0x294],xmm0` in sub_887860 (descriptor base [rbp+0x280], +0x14 → [rbp+0x294]).
Hop 3 [V]: sub_e7e150 returns either `[a0+0x5C]` (`e7e248 movss xmm6,[rsi+0x5C]`) or `sub_88bb50(vtable_result)->+0x18` (`e7e1c4 movss xmm6,[rax+0x18]`). Neither path reads settings.
Blocker: sub_e7e150's argument [rbp+0x58] is sub_887860's parameter, NEVER written in sub_887860 (stores.py confirms zero stores to [rbp+0x58]); its origin is sub_887860's caller (indirect call from sub_879480, xref offset 0x4334). The upscaling_percentage reader sub_5b72000 (id 0x243) is a separate disconnected path. No chain row from a settings read to the [elem+0x14] store exists.

CLOSES? NO

Single blocking fact: The [elem+0x14] writer IS proven ([V]: sub_6ad150 `0x6ad160 movups [rax+0x10],xmm1` from descriptor+0x14), and descriptor+0x14 = sub_e7e150([rbp+0x58]) [V: `0x88895b movss [rbp+0x294],xmm0`], but sub_e7e150 returns either object+0x5C (`e7e248`) or vtable/sub_88bb50-derived (`e7e1c4`) — NEITHER is a read through the settings object (upscaling_percentage id 0x243 / targetResolution id 0x246). [rbp+0x58] (sub_e7e150's argument = sub_887860's parameter) is never written in sub_887860, so its origin (and any link to upscaling_percentage) cannot be established statically. No chain row from a settings read to the [elem+0x14] store exists, so L10c cannot close.

TOOL REQUESTS: None — all evidence gathered with rdis.exe, xref.py, dumplist.py, stores.py and reads of prior r1-r18 notes. No new scripts written.
