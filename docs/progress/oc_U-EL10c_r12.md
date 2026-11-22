## NEXT
DONE

# Unit U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending

GOAL (verbatim from item line): close "L10c viewport and render-resolution selection, dynamic resolution pending". Do ONLY the pending part: who writes source(r13)+0x1F0 (the render/display ratio that endFrame's struct-copy 0x67C73D0 propagates into ctx+0x1F0) and link it to upscaling_percentage/targetResolution.

STATUS (per r5 handoff 2026-11-22): ratio writer inside endFrame IS now [V]-proven (0x6625094 divss). Still pending: the store of render-width global [0xEEC8060] (register-indirect, no rip-relative store) and its link from upscaling_percentage/targetResolution.

## EVIDENCE TABLE (offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag)

| +0x1F0 render/display ratio | 4 | struct-copy 0x67C73D0 / sub_566cb20 / TAAU | `0x67c7917  movss xmm0,[rsi+0x1F0]` | `0x566d04a  movss xmm0,[rsi+0x1F0]` | `0x566d052  movss [rdx+0x1F0],xmm0` | `0x67c791f  movss [rdx+0x1F0],xmm0` | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | source+0x1F0→element+0x1F0→ctx+0x1F0→TAAU (ratio) | [V] |
| [0xEEC8060] render width | 4 | endFrame reads / sub_dfb90 reads | `0x6625077  movss xmm7,[0xEEC8060]` | `0xdfb9c  movss xmm0,[0xEEC8060]` | render-width global (ratio numerator); no static store found | [V reads] / [? store] |
| ratio computation divss | 4 | endFrame 0x66232b0 | `0x6625094  divss xmm8,[r15+0x14]` | ratio = render width [0xEEC8060] / viewport width [r15+0x14], computed INSIDE endFrame | [V] |
| upscaling_percentage string | 16 | Options ctor 0x5b0c1b0 | `0x5b3e799  movups xmm0,[0xF5E13CC]` | registers upscaling_percentage (default 50); computes NO ratio | [V] |
| options.targetResolution string | 16 | Options ctor 0x5b0c1b0 | `0x5b3ead0  movups xmm0,[0xF5850DE]` | registers options.targetResolution (default 1); computes NO ratio | [V] |

## PROVEN CHAIN [V]

endFrame 0x66232b0 (BgfxFrameBuilder vtable slot 18, vtable 0xf2bdeb0, indirect call only):
1. `0x6625077  movss xmm7,[0xEEC8060]` / `0x6625090  movaps xmm8,xmm7` / `0x6625094  divss xmm8,[r15+0x14]` → ratio = render width / viewport width; `0x6625298  movss [rsp+0x40],xmm8`; `0x66252be  call 0x6634DB0` (rcx = template [rbp+0x170]).
2. sub_6634db0: `0x663512e  movq [rbp+0x348],xmm8`; `0x663672a  movups xmm1,[rbp+0x348]`; `0x6636731  movups [rsi+0x390],xmm1` → template+0x390 := ratio. (No +0x1F0 store inside sub_6634db0.)
3. endFrame `0x662ab42  call 0x5ABA5C0` (passLookup descriptor→rsi); `0x662abe5  lea rdx,[rbp+0x170]`; `0x662abef  call 0x566CB20` → sub_566cb20: `0x566d04a  movss xmm0,[rsi+0x1F0]` / `0x566d052  movss [rdx+0x1F0],xmm0` → descriptor+0x1F0 → template+0x1F0.
4. endFrame `0x662def4  call 0x67C73D0` loop: `0x67c7917  movss xmm0,[rsi+0x1F0]` / `0x67c791f  movss [rdx+0x1F0],xmm0` → element+0x1F0 → ctx+0x1F0.
5. TAAU 0xbc8cfd0: `0xbc8d34e  movups xmm0,[r13+0x1F0]` (ctx+0x1F0); `0xbc8d36d  mulps xmm0,xmm1` → ratio*dims.

## NOT FOUND (blockers)

- Store of render-width global [0xEEC8060]: register-indirect at window resize / upscaling_percentage change. Statically exhausted: rips xr 0xEEC8060 → 4403 read-refs, 0 writes; imm scan 0 hits; no movabs; no data pointer at 0xEEC8060. fld 0x1F0 --w (12315 accesses) shows every [reg+0x1F0] write is a struct-field copy, zeroing, or stack store — none computes the ratio from upscaling settings. No function-entry RVA identified for the store function.
- Link upscaling_percentage [0xF5E13CC] / options.targetResolution [0xF5850DE] → [0xEEC8060]: strings table-registered only (xref refs=[] for both); no code xrefs; no static or live connection. Settings are registered in Options ctor 0x5b0c1b0 but never applied to [0xEEC8060] in statically reachable code.

## LIVE DATA

grep of docs/data/live/*.txt for 0xEEC8060, 0x6625094, 0x67c73d0, 0xbc8d34e, 0x566cb20, 0x6634DB0, upscaling_percentage, targetResolution: NO matches ([V live]). _status.txt = DONE. el17h_endframe_caller.txt names indirect endFrame caller (ret=0x8890E4) but no [0xEEC8060] store or settings→[0xEEC8060] link. No capture target exists for [0xEEC8060] store.

## CLOSES?

NO — Single blocking fact: the store of render-width global [0xEEC8060] is not located statically (register-indirect, no rip-relative store; 4403 reads, 0 writes found), so the link upscaling_percentage/targetResolution → [0xEEC8060] → ratio cannot be completed. No function-entry RVA for the store function was identified, so no livecap write-watch request could be queued.

## TOOL REQUESTS

None — static analysis exhausted for [0xEEC8060] store (imm scan, ripscan, fld 0x1F0 --w all negative); no function-entry RVA identified for a livecap write-watch on [0xEEC8060]; no live capture names [0xEEC8060].
