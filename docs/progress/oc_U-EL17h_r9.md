## NEXT
DONE

UNIT U-EL17h (er vtable slot 18 / BgfxFrameBuilder endFrame). Goal this run: find who stores the passLookup descriptor +0x1F0 (float store at offset 0x1F0 in the descriptor builder), and close the index<->name link for the options (sub_10c1ad0 reads by index 0xFD/0xFE/0x100/0x101; name readers sub_5b0c1b0 "upscaling_percentage" @0x5b3e79c and "options.targetResolution" @0x5b3ead3 read the same objects by name).

=== RESULT TABLE (offset | size | read/store address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?]) ===

| 0x1F0 | 4 | 0x566d04a; 0x566d052; 0x10c1dc3 | `0x566d04a  movss xmm0,[rsi+0x1F0]`; `0x566d052  movss [rdx+0x1F0],xmm0`; `0x10c1dc3  movss [r12+0x1F0],xmm4` | sub_566cb20 copies source+0x1F0 to dest+0x1F0; sub_10c1ad0 stores computed float to r12+0x1F0 (r12=[a0+0x40] NOT confirmed as passLookup descriptor) | [V]/[V]/[?] |

| 0x18 | 4 | 0x10c1b83; 0x10c1bc3; 0x10c1c03; 0x10c1c66 | `0x10c1b83  movss xmm7,[rax+0x18]`; `0x10c1bc3  movss xmm8,[rax+0x18]`; `0x10c1c03  movss xmm9,[rax+0x18]`; `0x10c1c66  movss xmm2,[rax+0x18]` | sub_10c1ad0 reads option value [rax+0x18] for indices 0xFD/0xFE/0x100/0x101 | [V] |

| string "upscaling_percentage" | 16 | 0x51de12b; 0x5b3e799 | `0x51de12b  movups xmm0,[0xF5E13CC]`; `0x5b3e799  movups xmm0,[0xF5E13CC]` | string stored at [rax]; id edx=0x243 at 0x51de156 (sub_51de0c0) and 0x5b3e844 (sub_5b0c1b0) | [V] |

| string "options.targetResolution" | - | 0x5b3ead3 | `0x5b3ead3  (string ref in sub_5b0c1b0)` | string at 0xF5850DE referenced; registration site NOT found | [V] reader only |

| ctx +0x1F0 computation | 4 | 0x6625077; 0x6625090; 0x6625094 | `0x6625077  movss xmm7,[0xEEC8060]`; `0x6625090  movaps xmm8,xmm7`; `0x6625094  divss xmm8,[r15+0x14]` | endFrame: 1.0f constant; xmm8=1.0f; 1.0f / [elem+0x14] (chain must end at store of [elem+0x14]) | [V] |

| option index 0xFD | 4 | 0x10c1b52 | `0x10c1b52  mov r8d,0xFD` | sub_10c1ad0 reads option by index 0xFD via vtable+0xD8 | [V] |
| option index 0xFE | 4 | 0x10c1b9a | `0x10c1b9a  mov r8d,0xFE` | sub_10c1ad0 reads option by index 0xFE via vtable+0xD8 | [V] |
| option index 0x100 | 4 | 0x10c1bdb | `0x10c1bdb  mov r8d,0x100` | sub_10c1ad0 reads option by index 0x100 via vtable+0xD8 | [V] |
| option index 0x101 | 4 | 0x10c1c1b | `0x10c1c1b  mov r8d,0x101` | sub_10c1ad0 reads option by index 0x101 via vtable+0xD8 | [V] |

=== KNOWN CHAIN (verified unless noted) ===
- endFrame = BgfxFrameBuilder vtable slot 18 (0x66232b0, size 0xB3D0) [V - BGFX_MAP.md line 167]
- Called via vtable/function pointer, no direct callers [V - 66232b0.md]
- Chain: descriptor +0x1F0 -> element +0x1F0 (sub_566cb20 at 0x566d04a/0x566d052) -> ctx +0x1F0 (0x67c791f) [V]
- endFrame at 0x6625094: divss xmm8,[r15+0x14] where xmm8=1.0f (0xEEC8060) [V]; chain must END at store of [elem+0x14] [per L10c]
- sub_67c82f0 (called from endFrame 0x662b435) calls sub_566cb20 at 0x67c8319, then copies many fields from source descriptor (2nd arg, [rbp+0x170]) to dest element (1st arg) [V]

=== PENDING / NOT CLOSED ===
1. Writer of source(r13)+0x1F0 (descriptor +0x1F0): sub_10c1ad0 at 0x10c1dc3 `movss [r12+0x1F0],xmm4` is a candidate but r12=[a0+0x40] is NOT confirmed as the passLookup descriptor. sub_10c1ad0 callers are NOT called from endFrame; no data-flow path from sub_10c1ad0 output to endFrame's source descriptor [rbp+0x170] established.
2. Index<->name link: sub_10c1ad0 reads indices 0xFD/0xFE/0x100/0x101. "upscaling_percentage" found with id 0x243 (sub_5b0c1b0 0x5b3e844 `mov edx,0x243`, sub_51de0c0 0x51de156 `mov edx,0x243`) but 0x243 != 0xFD/0xFE/0x100/0x101. sub_9c4220 does NOT use edx (verified by full disassembly read). Renderer option registration function (name->numeric id) NOT found. "options.targetResolution" registration site NOT found (only reader at 0x5b3ead3 in sub_5b0c1b0).
3. Who stores to [elem+0x14] (the divisor read at endFrame 0x6625094): NOT found.

=== CLOSES? ===
NO — Two pending facts unproven:
 (a) Writer of descriptor +0x1F0 not confirmed: sub_10c1ad0 0x10c1dc3 `movss [r12+0x1F0],xmm4` is a candidate but r12 not confirmed as passLookup descriptor; no data-flow path to endFrame source descriptor established.
 (b) Index<->name link not closed: id 0x243 found for "upscaling_percentage" but doesn't match sub_10c1ad0 indices 0xFD/0xFE/0x100/0x101; renderer option registry registration function not found.

=== NEXT STEPS ===
- Trace sub_10c1ad0 output [r12+0x1F0] to see if it reaches endFrame's source descriptor [rbp+0x170] (check callers of sub_954dc0/sub_4d5b030; check sub_6584fa0/other sub_10c1ad0 callers)
- Find renderer option registry registration: check sub_9c4220 callees sub_e93a0d0/sub_e9397f0; find vtable+0xD8 implementation; search for (name,id) registration in 0x5b0xxx range
- Find who stores [elem+0x14]

LIVE: docs/data/live/el17h_endframe_caller.txt (24 samples, ret=0x8890E4) — not yet mined.

TOOL REQUESTS: None yet.
