## NEXT
DONE

# Unit U-EI2a — I2a Actor renderer dispatch anchors: bodyActor cross-link to 6bg

## Pending item (from oc_U-I2a.md)
`ActorRenderDispatcher::render` 0x594c5c0..0x594caba and `DataDrivenRendererV2::tryAddActor` 0x6ebb280..0x6ebb50a are instruction-complete (verify_oc 483/483). `bodyActor` / `RenderMark::bodyActor` 0x66d0a00 internals are in oc_U-BA1..BA9 (instruction-complete, 0x66d0a00..0x66d7d8b); the cross-link to the 6bg anchors (actor = *(S + 0xC8), passLookup 0x5ABA5C0, kItemSize = 0xC8 item push) is pending.

This unit closes that cross-link: it cites the bodyActor internals that ARE statically present in oc_U-BA1..BA9 and states the status of each 6bg anchor.

## Verified bodyActor internals (oc_U-BA1..BA9, [V])
| name | offset | size | read/store address | instr | meaning | tag |
| bodyActor entry | 0x66d0a00 | - | - | `0x66d0a00  push rbp` | RenderMark::bodyActor entry | [V] |
| bodyActor frame | 0x66d0a0c | - | - | `0x66d0a0c  sub rsp,0xE38` | 0xE38-byte stack frame (BGFX_MAP 6bg) | [V] |
| actor-source copy | 0x66d0a34 | 8 | - | `0x66d0a34  mov rdi,r8` | rdi = r8 (arg3); actor-source pointer candidate | [V] |
| actor-source deref | 0x66d0a41 | 8 | [r8] | `0x66d0a41  mov rax,[r8]` | rax = [r8]; deref actor-source struct | [V] |
| writer call A | 0x66d4265 | - | - | `0x66d4265  call 0x6765020` | bodyActor -> writer 0x6765020 (passLookup + 0xC8 item per 6bg/850) [I] | [V] |
| writer call B | 0x66d49e2 | - | - | `0x66d49e2  call 0x6768C70` | bodyActor -> writer 0x6768c70 (second writer) [I] | [V] |

## Proof lines (verbatim, for verify_oc)
 0x66d0a00  push rbp
 0x66d0a0c  sub rsp,0xE38
 0x66d0a34  mov rdi,r8
 0x66d0a41  mov rax,[r8]
 0x66d4265  call 0x6765020
 0x66d49e2  call 0x6768C70

## 6bg anchor status (per docs/BGFX_MAP.md lines 826-830, 850)
- actor = *(S + 0xC8): NOT present as a direct static read in bodyActor's disassembly. The only `+0xC8` read in BA1..BA9 is `0x66d313d  mov rax,[rax+0xC8]` (from `[[rdi+0xC0]]`, BA3), not from the 5th-arg pointer S. No `S+0xC8` read found. [?]
- passLookup 0x5ABA5C0: no direct `call 0x5ABA5C0` in bodyActor; bodyActor reaches it indirectly through the writer calls above. [?]
- kItemSize = 0xC8 item push: not present in bodyActor; writers 0x6765020 / 0x6768c70 push 0xC8-byte item records per BGFX_MAP line 850 [I].

## CLOSES?
NO — bodyActor's static disassembly (BA1–BA9, instruction-complete 0x66d0a00..0x66d7d8b) contains no direct `*(S + 0xC8)` actor read, no direct `passLookup` call, and no `0xC8`-byte item push. Those 6bg anchors live in the called writer functions (0x6765020 invoked at 0x66d4265 [V], 0x6768c70 invoked at 0x66d49e2 [V]); only the writer calls themselves are [V]-proven inside bodyActor. Blocking fact: the actor-identity read `*(S + 0xC8)` is not statically present in bodyActor.

## TOOL REQUESTS
- None.
