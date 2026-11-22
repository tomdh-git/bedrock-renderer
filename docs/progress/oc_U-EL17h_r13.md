## NEXT
step 2

UNIT U-EL17h — L17h graphics options plumbing (OptionSync): upscaling_percentage (option id 0x243) / targetResolution (option id 0x246) readers via vtable[0xD8] get-option-by-id, followed forward to the store of [elem+0x14] (endFrame ratio denominator: ratio = 1.0f / [elem+0x14]) or descriptor/ctx +0x1F0, closing L17h + L10c.
Output file: docs/progress/oc_U-EL17h.md only.

Anchors (verified earlier, re-confirmed below where quoted):
- upscaling_percentage = option id 0x243; targetResolution = option id 0x246 (registered, [V] per orchestrator; sub_10c1ad0 reads ids 0xFD/0xFE/0x100/0x101 and is NOT the upscaling reader — dropped).
- get-option-by-id = vtable[0xD8]; endFrame ratio: `0x6625077 movss xmm7,[0xEEC8060]` (1.0f), `0x6625094 divss xmm8,[r15+0x14]` ([LIVE el17h_endframe_caller.txt]; endFrame caller ret=0x8890E4, RCX=0x22FC6252800 constant, 24 samples/18090 hits).
- Live capture u_el17h_888c50 (0x888c50, array1-builder get-option-by-id call) = 0 hits [LIVE docs/data/live/_status.txt: u_el17h_888c50 hits=0 samples=0]; runs only on options load/change — relying on static hops.

Table (one row per distinct offset; all sites merged; every instr line quoted verbatim from rdis):

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | [V]/[I]/[?] |
