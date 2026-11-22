## NEXT
DONE

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)

GOAL: Close checklist item: L17h graphics options plumbing (OptionSync) pending — prove the index <-> name link: sub_10c1ad0 reads options by id 0xFD/0xFE/0x100/0x101; name-based readers sub_5b0c1b0 ("upscaling_percentage" @0x5b3e79c) and "options.targetResolution" @0x5b3ead3 get the same option objects by name. Find the option registry id for each name and compare to {0xFD,0xFE,0x100,0x101}. One matching row (name -> id -> read at 0x10c1ad0) closes it.

## SUMMARY OF FINDINGS

The option registry is sub_9c4220 (0x9c4220), reached via sub_9be320 -> sub_9be400. sub_9be400 allocates a 0x2A0-byte option object and stores three id-ish dwords:
- [new_obj+0x1CC] = edx (the numeric id)           <- THE id field, read later as id (cmp vs 0x7FFFFFFF sentinel)
- [new_obj+0x1D0] = r8d (=1)
- [new_obj+0x1D4] = descriptor+0x10 dword

sub_5b3e100 registers "upscaling_percentage" by building the name string then calling sub_9c4220 with edx=0x243. sub_5b3ea00 registers "options.targetResolution" by calling sub_9c4220 with edx=0x246.

sub_10c1ad0 (0x10c1ad0) reads 4 options by id via virtual call `call qword ptr [0xF99FFA0]` (vtable[0xD8]) with r8d = 0xFD, 0xFE, 0x100, 0x101, then reads [result+0x18] as a float and writes to [r12+0x1F0] region.

RESULT: upscaling_percentage id = 0x243; targetResolution id = 0x246. sub_10c1ad0 reads ids {0xFD,0xFE,0x100,0x101}. {0x243,0x246} ∩ {0xFD,0xFE,0x100,0x101} = empty set. NO name->id match exists to sub_10c1ad0's reads.

## LIVE capture: docs/data/live/el17h_endframe_caller.txt (rva=0x66232B0 kind=regs size=0x100)
- CALLER ret=0x8890E4 all samples; RCX=22FC6252800 (BgfxFrameBuilder whose slot holds endFrame 0x66232b0, vtable slot 18); R9 varies per sample (options/data object). [V live docs/data/live/el17h_endframe_caller.txt:3-27]

## FINDINGS (table: name | rva or offset | size | verbatim proof `0xRVA  instr` | tag)

| upscaling_percentage | rva 0x5b3e844 | 4 | `0x5b3e844  mov edx,0x243` | [V] |
| upscaling_percentage | rva 0x5b3e855 | — | `0x5b3e855  call 0x9C4220` | [V] |
| upscaling_percentage | offset +0x1CC (option id field) | 4 | `0x9be850  mov [r13+0x1CC],eax` (eax=[rbp+8]=edx=0x243, set by caller sub_5b3e100) | [V] |
| targetResolution | rva 0x5b3eb1b | 4 | `0x5b3eb1b  mov edx,0x246` | [V] |
| targetResolution | rva 0x5b3eb2c | — | `0x5b3eb2c  call 0x9C4220` | [V] |
| targetResolution | offset +0x1CC (option id field) | 4 | `0x9be850  mov [r13+0x1CC],eax` (eax=[rbp+8]=edx=0x246, set by caller sub_5b3ea00) | [V] |
| sub_10c1ad0 read id 1 | rva 0x10c1b52 | 4 | `0x10c1b52  mov r8d,0xFD` | [V] |
| sub_10c1ad0 lookup call | rva 0x10c1b58 | — | `0x10c1b58  call qword ptr [0xF99FFA0]` (vtable[0xD8] get-option-by-id) | [V] |
| sub_10c1ad0 read id 2 | rva 0x10c1b9a | 4 | `0x10c1b9a  mov r8d,0xFE` | [V] |
| sub_10c1ad0 read id 3 | rva 0x10c1bdb | 4 | `0x10c1bdb  mov r8d,0x100` | [V] |
| sub_10c1ad0 read id 4 | rva 0x10c1c1b | 4 | `0x10c1c1b  mov r8d,0x101` | [V] |

Id-store proof (sub_9be400, reached from sub_9c4220->sub_9be320):
- `0x9be84d  mov eax,[rbp+8]` — eax = edx passed by caller (0x243 upscaling / 0x246 targetResolution) [V]
- `0x9be850  mov [r13+0x1CC],eax` — stores id at new_obj+0x1CC [V]
- `0x9be857  mov eax,[rbp+0x18]` ; `0x9be85a  mov [r13+0x1D0],eax` — +0x1D0 = r8d = 1 [V]
- `0x9be861  mov eax,[rbp+0x10]` ; `0x9be864  mov [r13+0x1D4],eax` — +0x1D4 = descriptor+0x10 dword [V]

sub_9c4220 passes caller edx through to sub_9be320->sub_9be400:
- `0x9c42ac  mov r12d,edx` ; `0x9c4343  mov edx,r12d` (restore before sub_9be320 call) [V]

sub_10c1ad0 reads [result+0x18] as float for each id:
- `0x10c1b83  movss xmm7,[rax+0x18]` (id 0xFD) [V]
- `0x10c1bc3  movss xmm8,[rax+0x18]` (id 0xFE) [V]
- `0x10c1c03  movss xmm9,[rax+0x18]` (id 0x100) [V]
- `0x10c1c66  movss xmm2,[rax+0x18]` (id 0x101) [V]
- Writes to [r12+0x1F0]: `0x10c1dc3  movss [r12+0x1F0],xmm4` [V]

Comparison (id sets): upscaling_percentage=0x243, targetResolution=0x246 vs sub_10c1ad0 reads {0xFD,0xFE,0x100,0x101}. Intersection = empty. No match.

## STRING XREFS (for completeness)
- "upscaling_percentage" @0xf5e13cc: refs at 0x5b3e799 (sub_5b3e100 registration, builds string object), 0x5b3e79c (sub_5b0c1b0 name-reader), 0x51de12e (sub_51cd6c0 UI localization "_mode_radio_taau", edx=0x243 via call 0x4BB6CB0 — NOT the option registry) [V]
- "options.targetResolution" @0xf5850de: ref at 0x5b3ead3 (sub_5b0c1b0 name-reader only); string data built at 0x5b3ea6d [0xF585051] in sub_5b3ea00 registration [V]

## CLOSES?
NO — upscaling_percentage is registered with id 0x243 ([new_obj+0x1CC]) and targetResolution with id 0x246, but sub_10c1ad0 reads ids 0xFD/0xFE/0x100/0x101 via vtable[0xD8] get-option-by-id. {0x243,0x246} does not intersect {0xFD,0xFE,0x100,0x101}, so the name->id->read-at-0x10c1ad0 link is NOT established. Blocking fact: no registration of upscaling_percentage/targetResolution uses any id in {0xFD,0xFE,0x100,0x101}.

## TOOL REQUESTS
None.
