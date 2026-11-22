## NEXT
DONE - U-EL10c trace written to docs/progress/oc_U-EL10c.md (16 verified rows); CLOSES? NO: writer of [obj+0x5C] unidentified and settings-to-elem+0x14 link unproven ([a0+0x5C] = constant 2.0f live across all captured callers).

UNIT U-EL10c — L10c "viewport and render-resolution selection, dynamic resolution pending".
Output file: docs/progress/oc_U-EL10c.md only. Static analysis of Minecraft.Windows.exe 1.26.62.01 (image-relative RVAs). Every `0xRVA  instr` quoted below was taken from rdis.exe output against the exe; tags: [V] = seen in disassembly, [V live] = seen in live capture bytes, [I] = inferred, [?] = unknown.

GOAL (orchestrator, this run; overrides prior r1-r21 "complete" notes): trace the [elem+0x14] scale-float chain (endFrame `0x6625094 divss xmm8,[r15+0x14]`, ratio = 1.0f/[elem+0x14]) back through descriptor+0x14 = sub_e7e150([rbp+0x58]) return, and report: (1) what sub_e7e150 computes, (2) what object [rbp+0x58] is in sub_887860, (3) who writes [obj+0x5C] / [sub_88bb50_result+0x18], and whether either path links to option id 0x243 (upscaling_percentage) reader sub_5b72000 (0x5B72030).

LIVE INPUT (read, not re-derived): docs/data/live/u_el10c_e7e150.txt (356576 hits, 24 samples), u_el10c_887860.txt (1026 hits, 4 samples, caller ret=0x87BD14), el17h_endframe_caller.txt (endFrame caller ret=0x8890E4).

----------------------------------------------------------------------
EVIDENCE TABLE — offset | size | site | verbatim `0xRVA  instr` | meaning | tag
----------------------------------------------------------------------

| a0+0xCB0 (e7e150 flag byte) | 1 (cmp byte) | 0xE7E16C | `0xE7E16C  cmp byte ptr [rcx+0xCB0],1` | sub_e7e150 guard on object flag: ==1 -> vtable/settings path, !=1 -> [a0+0x5C] fallback | [V] |
| a0+0x5C (e7e150 fallback return) | 4 (movss) | 0xE7E248 | `0xE7E248  movss xmm6,[rsi+0x5C]` | sub_e7e150 returns [a0+0x5C] when flag != 1 (rsi=a0=[rbp+0x58]) | [V] |
| sub_88bb50_result+0x18 (e7e150 vtable-path return) | 4 (movss) | 0xE7E1C4 | `0xE7E1C4  movss xmm6,[rax+0x18]` | sub_e7e150 returns [sub_88bb50(vcall(*(a0+0x98)+0x108))+0x18] when flag == 1 | [V] |
| call sub_88bb50 inside sub_e7e150 | 8 (call) | 0xE7E1B9 | `0xE7E1B9  call 0x88BB50` | sub_e7e150 vtable path calls sub_88bb50(vcall-result object) | [V] |
| [rbp+0x58] (sub_e7e150 argument slot in sub_887860) | 8 (mov qword) | 0x888951 | `0x888951  mov rcx,[rbp+0x58]` | sub_e7e150(rcx=[rbp+0x58]); [rbp+0x58] is NEVER written anywhere in sub_887860 (only this one read) | [V] |
| call sub_e7e150 in sub_887860 | 8 (call) | 0x888955 | `0x888955  call 0xE7E150` | descriptor+0x14 value computed by sub_e7e150 | [V] |
| descriptor+0x14 ([rbp+0x294]; descriptor base [rbp+0x280]) | 4 (movss) | 0x88895B | `0x88895B  movss [rbp+0x294],xmm0` | sub_887860 stores descriptor+0x14 = sub_e7e150([rbp+0x58]) return | [V] |
| imm 0xDA6A3486 (sub_88bb50 settings-tree key) | 4 (mov imm) | 0x88BCCF | `0x88BCCF  mov r8d,0xDA6A3486` | sub_88bb50 looks up settings tree by hash key 0xDA6A3486 | [V] |
| call sub_1219a0 inside sub_88bb50 | 8 (call) | 0x88BCD8 | `0x88BCD8  call 0x1219A0` | sub_88bb50 returns the settings value object for hash 0xDA6A3486 (rax); its [+0x18] is read at e7e1c4 | [V] |
| option id 0x243 (upscaling_percentage) | 4 (mov imm) | 0x5B7202A | `0x5B7202A  mov r8d,0x243` | sub_5b72000 get-option-by-id for option id 0x243 | [V] |
| call [0xF99FFA0] inside sub_5b72000 | 8 (call) | 0x5B72030 | `0x5B72030  call qword ptr [0xF99FFA0]` | sub_eea6040 option-get dispatch; result option object at [rsp+0x28] | [V] |
| [option_obj+0x18] | 4 (mov dword) | 0x5B72053 | `0x5B72053  mov edi,[rax+0x18]` | sub_5b72000 reads option 0x243 VALUE at +0x18 into edi; then applies it via setters at [a0+0x1A40]+0xC0/+0xC8 — sub_5b72000 is an option APPLICATOR, disconnected from the elem+0x14 chain | [V] |
| element+0x10..0x1F write (covers elem+0x14) | 16 (movups) | 0x6AD160 | `0x6AD160  movups [rax+0x10],xmm1` | sub_6ad150 WRITES element+0x14 (divisor); rax=element dst, rdx=descriptor src | [V] |
| descriptor+0x10..0x17 read (elem+0x14 source) | 16 (movups) | 0x6AD15C | `0x6AD15C  movups xmm1,[rdx+0x10]` | xmm1 (stored at elem+0x10..0x1F, incl. +0x14) comes from descriptor+0x10..0x17 => descriptor+0x14 | [V] |
| endFrame elem+0x14 ratio read | 4 (divss) | 0x6625094 | `0x6625094  divss xmm8,[r15+0x14]` | endFrame 0x66232b0: ratio = 1.0f / [r15+0x14]; r15 iterates array1=[rdx+0x38..0x40] elements | [V] |
| ratio numerator [0xEEC8060] | 4 (movss) | 0x6625077 | `0x6625077  movss xmm7,[0xEEC8060]` | numerator = read-only 1.0f constant (PAGE_READONLY, bytes 00 00 80 3F); NO store to it exists | [V] |

----------------------------------------------------------------------
LIVE CAPTURE DECODE (python struct '<f' on [a0+0x5C] bytes, grouped by ret= caller)
----------------------------------------------------------------------

- u_el10c_e7e150.txt:4 — ret=0x6608063: RCX=a0=0x22FC7F44600; bytes at +0x5C..+0x5F = 00 00 40 00 -> float 2.0f
- u_el10c_e7e150.txt:9 — ret=0xE6FE79: same object 0x22FC7F44600, identical bytes -> +0x5C = 2.0f
- u_el10c_e7e150.txt:13 — ret=0xE6FE95: same object -> +0x5C = 2.0f
- u_el10c_e7e150.txt:17 — ret=0xE6FEBF: same object -> +0x5C = 2.0f

All e7e150 samples pass the SAME object (a0=0x22FC7F44600) whose +0x5C reads 2.0f in every caller group (ret= 0x6608063, 0xE6FE79, 0xE6FE95, 0xE6FEBF). Single live session: value is CONSTANT 2.0f; no upscaling_percentage dependence observable from this capture.

sub_887860 capture (u_el10c_887860.txt:4, ret=0x87BD14): RCX=this=0x22FC62D0000 (the object sub_887860 is a method of — vptr at +0x0), R8=0x7FF6184B4483, R9=0x7FFE4000; RDX not captured. [rbp+0x58] (e7e150's argument object) is a DIFFERENT object from this; live e7e150 capture shows it as a0=0x22FC7F44600 (vptr 0x7FF614C9B220, +0x5C=2.0f). sub_887860 is entered via tail-jmp `jmp qword ptr [rsi+0x66]` (only xref: caller 0x879480); how [rbp+0x58] is set on the shared stack is unconfirmed.

----------------------------------------------------------------------
HOP CHAIN SUMMARY
----------------------------------------------------------------------

Hop 1 [V]: descriptor+0x14 := sub_e7e150([rbp+0x58]) — `0x888951  mov rcx,[rbp+0x58]` / `0x888955  call 0xE7E150` / `0x88895B  movss [rbp+0x294],xmm0`.
Hop 2 [V]: sub_e7e150 returns either [a0+0x5C] (`0xE7E248  movss xmm6,[rsi+0x5C]`) or [sub_88bb50(vcall(*(a0+0x98)+0x108))+0x18] (`0xE7E1C4  movss xmm6,[rax+0x18]` via `0xE7E1B9  call 0x88BB50`). Neither path reads the settings object.
Hop 3 [?]: sub_88bb50 returns settings value object for hash 0xDA6A3486 (`0x88BCCF  mov r8d,0xDA6A3486` / `0x88BCD8  call 0x1219A0`); [result+0x18] is the float. Link of 0xDA6A3486 to upscaling_percentage UNPROVEN: fnv1a32("upscaling_percentage") = 0xFDDD2E7E != 0xDA6A3486; string "upscaling_percentage" lives at 0xF5E13CC with NO code xrefs (xref.py str "upscaling_percentage" -> refs=[]).
Hop 4 [V]: option id 0x243 reader sub_5b72000 (`0x5B7202A  mov r8d,0x243` / `0x5B72030  call qword ptr [0xF99FFA0]` / `0x5B72053  mov edi,[rax+0x18]` reads [option_obj+0x18]) then applies values to setters [a0+0x1A40]+0xC0/+0xC8 — NOT connected to descriptor+0x14/elem+0x14.
Hop 5 [V]: element+0x14 := descriptor+0x14 via `0x6AD15C  movups xmm1,[rdx+0x10]` / `0x6AD160  movups [rax+0x10],xmm1`; endFrame ratio `0x6625094  divss xmm8,[r15+0x14]` = 1.0f (0x6625077)/[elem+0x14].

----------------------------------------------------------------------
OPEN ITEMS (blocking closure)
----------------------------------------------------------------------

- Writer of [obj+0x5C] on a0's class: NOT identified. `rdis fld 0x5C --w` yields 2313 exe-wide [reg+0x5C] writes; object-class writers (movss) include 0x512d5e, 0x69e5a7, 0x798ce3, 0x94446f, 0x945543, 0x6adaf1; block writers (movups) include 0x9e630, 0x599938, 0x285ff8, 0x877c5b — NONE tied to a0's class, because the class is unknown statically: a0's vptr 0x7FF614C9B220 is only observed live; ImageBase (0x140000000) != relocated live base, so the vtable RVA cannot be computed and `rdis vt`/ctor scan is not possible. Also: `rdis class`/`vt` need a file RVA which cannot be derived from the live address. [?]
- Writer of sub_88bb50_result+0x18 (settings value object +0x18, where option floats live): not traced (settings init/config-load path). [?]
- [rbp+0x58] setter: never written in sub_887860; set by caller 0x879480 mechanism unconfirmed (tail-jmp [rsi+0x66]). [?]
- Whether live [a0+0x5C] = 2.0f changes with in-game upscaling_percentage: undetermined (single session; 2.0f constant across all 4 captured caller groups).

----------------------------------------------------------------------
CLOSES? NO
----------------------------------------------------------------------

Blocking fact: no chain row connects a settings read (option id 0x243 via sub_5b72000 at `0x5B72030  call qword ptr [0xF99FFA0]`, or hash 0xDA6A3486 via sub_88bb50 at `0x88BCCF  mov r8d,0xDA6A3486`) to the [elem+0x14] store (`0x6AD160  movups [rax+0x10],xmm1`): sub_e7e150 returns either the cached [a0+0x5C] = 2.0f constant in the capture (not shown option-dependent) or sub_88bb50(...)->+0x18 under an unverified hash key; the [obj+0x5C] writer is unidentified. The proven part: descriptor+0x14 -> element+0x14 -> endFrame ratio is fully traced [V].

----------------------------------------------------------------------
TOOL REQUESTS
----------------------------------------------------------------------

None — all evidence gathered with rdis.exe, xref.py, dumplist.py and reads of docs/data/live/*.txt. No new scripts written.
