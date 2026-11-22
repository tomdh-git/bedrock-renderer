## NEXT
DONE

# U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending (carried from oc_U-Eratio.md, was CLOSES? NO)

Scope: prove the render-ratio chain into ctx+0x1F0 → TAAU read 0xbc8d34e; the render-width global [0xEEC8060] store and its link from upscaling_percentage/targetResolution were NOT found statically (handoff r5, 2026-11-22). All instruction lines below re-verified verbatim with rdis this session.

## Evidence table

| offset | size | site | instr | meaning | tag |
|--------|------|------|-------|---------|-----|
| ctx+0x1F0 | 16 (movups read), 4 (movss write) | TAAU 0xbc8d34e read (r13 = ctx base); struct-copy 0x67C73D0 write via endFrame 0x662def4 | `0xbc8d34e  movups xmm0,[r13+0x1F0]`\n`0x67c791f  movss [rdx+0x1F0],xmm0` (reads `0x67c7917 movss xmm0,[rsi+0x1F0]`; invoked `0x662def4 call 0x67C73D0`; element loop `0x662ded3 add r13,0x2B0` / `0x662dee1 cmp r13,rdi`) | TAAU 0xbc8cfd0 reads ctx+0x1F0 as render/display ratio (`0xbc8d36d mulps xmm0,xmm1` = ratio*dims); 0x67C73D0 copies element+0x1F0 → ctx+0x1F0 per element | [V] |
| template+0x1F0 (src = passLookup descriptor 0x5aba5c0+0x1F0) | 4 | sub_566cb20 via endFrame 0x662abef (rdx = template [rbp+0x170], rsi = passLookup descriptor rax from `0x662ab42 call 0x5ABA5C0`) | `0x566d052  movss [rdx+0x1F0],xmm0` (reads `0x566d04a movss xmm0,[rsi+0x1F0]`; call `0x662abef call 0x566CB20`) | passLookup descriptor+0x1F0 copied to template+0x1F0; sub_566cb20 called x7 in endFrame | [V] |
| element+0x1F0 | 16 | endFrame 0x6628fb0 (rsi = element base) | `0x6628fb0  movups [rsi+0x1F0],xmm6` | xmm6 loaded from render-width global [0xEEC8060] at `0x6624da7 movss xmm6,[0xEEC8060]` (xmm6 value live at 0x6628fb0 not re-traced) | [V] |
| template+0x390 | 16 | sub_6634db0 via endFrame `0x66252be call 0x6634DB0` (xmm8 = ratio) | `0x6636731  movups [rsi+0x390],xmm1` (xmm1 = [rbp+0x348] = xmm8 via `0x663512e movq [rbp+0x348],xmm8`; rsi = template base [rbp+0x4B8] = rcx arg) | template+0x390 := ratio | [V] |
| [r15+0x14] (per-viewport width) | 4 | endFrame 0x6625094 | `0x6625094  divss xmm8,[r15+0x14]` (xmm7 = [0xEEC8060] via `0x6625077 movss xmm7,[0xEEC8060]`; `0x6625090 movaps xmm8,xmm7`) | per-viewport width divisor; ratio = render width [0xEEC8060] / viewport width [r15+0x14] | [V] |
| [0xEEC8060] (render-width global) | 4 | endFrame `0x6624da7 movss xmm6,[0xEEC8060]` / `0x6625077 movss xmm7,[0xEEC8060]`; sub_dfb90 viewport setup `0xdfb9c movss xmm0,[0xEEC8060]`; ~4403 other reader sites (all reads) | `0x6624da7  movss xmm6,[0xEEC8060]`\n`0x6625077  movss xmm7,[0xEEC8060]`\n`0xdfb9c  movss xmm0,[0xEEC8060]` | render-width global; dividend of ratio at 0x6625094; 4403 read-refs, ZERO static stores (rdis imm 0xEEC8060 = 0 hits, no movabs, no data pointer at 0xEEC8060) — register-indirect store at window resize / upscaling_percentage change NOT located | [V reads] / [? store] |
| [0xF5E13CC] (string "upscaling_percentage") | 16 | Options ctor 0x5b3e799 via sub_9C4220/sub_5BC0530 | `0x5b3e799  movups xmm0,[0xF5E13CC]` (string "upscaling_percentage"); default store `0x5b3e835 mov dword ptr [rsp+0x30],0x32` (=50) | setting registered with default 50; table-registered (no direct code xrefs to the string) | [V] |
| [0xF5850DE] (string "options.targetResolution") | 16 | Options ctor 0x5b3ead0 via sub_9C4220/sub_5BC0530 | `0x5b3ead0  movups xmm0,[0xF5850DE]` (string "options.targetResolution"); default store `0x5b3eb0c mov dword ptr [rsp+0x30],1` (=1) | setting registered with default 1; link from this setting to [0xEEC8060] not found | [V] |

## Proven [V] chain

endFrame 0x66232b0 (BgfxFrameBuilder vtable slot 18, vtable 0xf2bdeb0, indirect call only):
1. `0x6624da7 movss xmm6,[0xEEC8060]` / `0x6625077 movss xmm7,[0xEEC8060]` read render-width global; `0x6625090 movaps xmm8,xmm7`; `0x6625094 divss xmm8,[r15+0x14]` → ratio = render width / per-viewport width; `0x6625298 movss [rsp+0x40],xmm8`; `0x66252be call 0x6634DB0` with rcx = template [rbp+0x170].
2. sub_6634db0: `0x663512e movq [rbp+0x348],xmm8`; `0x663672a movups xmm1,[rbp+0x348]`; `0x6636731 movups [rsi+0x390],xmm1` → template+0x390 := ratio. (No +0x1F0 store inside sub_6634db0.)
3. endFrame `0x662ab42 call 0x5ABA5C0` (passLookup descriptor 0x5aba5c0 → rsi); `0x662abe5 lea rdx,[rbp+0x170]`; `0x662abec mov rcx,rdi`; `0x662abef call 0x566CB20` → sub_566cb20: `0x566d04a movss xmm0,[rsi+0x1F0]` / `0x566d052 movss [rdx+0x1F0],xmm0` → descriptor+0x1F0 → template+0x1F0.
4. endFrame `0x662def4 call 0x67C73D0` loop (`0x662ded3 add r13,0x2B0` / `0x662dee1 cmp r13,rdi`): `0x67c7917 movss xmm0,[rsi+0x1F0]` / `0x67c791f movss [rdx+0x1F0],xmm0` → element+0x1F0 → ctx+0x1F0.
5. TAAU 0xbc8cfd0: `0xbc8d34e movups xmm0,[r13+0x1F0]` (ctx+0x1F0); `0xbc8d36d mulps xmm0,xmm1` → ratio*dims. Chain proven endFrame → ctx+0x1F0 → TAAU.

Render-resolution data path [V]: [0xEEC8060] reads at endFrame 0x6624da7/0x6625077 and sub_dfb90 0xdfb9c; ratio computed at 0x6625094 inside endFrame; settings upscaling_percentage [0xF5E13CC] (default 50, `0x5b3e835 ... 0x32`) and options.targetResolution [0xF5850DE] (default 1, `0x5b3eb0c ... 1`) registered in Options ctor 0x5b0c1b0.

## Live data cross-check

grep of docs/data/live/*.txt for 0xEEC8060, 0x6625094, 0x67c73d0, 0xbc8d34e, 0x566cb20, 0x6634DB0, upscaling_percentage, targetResolution: NO matches (docs/data/live/_status.txt = DONE). The existing el17h_endframe_caller capture (docs/data/live/el17h_endframe_caller.txt, state done) names only the indirect endFrame caller (ret=0x8890E4) and builder/frame-package args — it does not show a store to [0xEEC8060] or a settings→[0xEEC8060] link.

## Still open

- Store of render-width global [0xEEC8060]: register-indirect, at window resize / upscaling_percentage change. Statically exhausted: 4403 read-refs, 0 stores, imm scan 0 hits, no movabs, no data pointer.
- Link upscaling_percentage [0xF5E13CC] / options.targetResolution [0xF5850DE] → [0xEEC8060]: strings table-registered, no code xrefs; no static or live connection found.

## CLOSES?

CLOSES? NO — blocking fact: no static store of render-width global [0xEEC8060] exists (exhausted: 4403 reads, 0 stores, no immediate/data-pointer reference), so the register-indirect store at window resize / upscaling_percentage change and its link from upscaling_percentage/targetResolution remain unproven; no live capture names [0xEEC8060]; no function-entry RVA for the store function was identified statically (all candidates indirect), so no livecap request was queued.

## TOOL REQUESTS

None — livecap captures log registers at function entry only (no memory write-watch on [0xEEC8060] available), and no entry RVA for the [0xEEC8060] store function was identified statically; a resize/upscaling_percentage-change write-watch capture on [0xEEC8060] is still needed to close this item.
