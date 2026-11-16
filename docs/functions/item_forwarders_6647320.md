# Item visitor forwarders, tags 6 / 10 / 8 (E1d) — 1.26.62.01

Item visitor 0x6646980, jump table 0xF2BF2D0 (tools/sigs/jt.py: tag 6 -> 0x6647320, tag 10 -> 0x6647383, tag 8 -> 0x66473e6 [V]). The three entries are identical 22-instruction epilogue stubs: the visitor's frame is torn down and the extractor is tail-called with the visitor's own arguments. Every instruction is listed (rdis dis, re-run 2026-11-15):

```
0x6647320  mov rcx,rbx            ; rcx = this (BgfxFrameBuilder renderer object)
0x6647323  mov rdx,[rbp+0x8A0]    ; rdx = frame context saved by the visitor prologue
0x664732a  mov r8,rdi             ; r8 = rdi = description pointer ([r8] of the visitor, loaded at 0x66469fd)
0x664732d  movaps xmm6,[rbp+0x8B0]  ... xmm7 [0x8C0] xmm8 [0x8D0] xmm9 [0x8E0] xmm10 [0x8F0] xmm11 [0x900] xmm12 [0x910] xmm13 [0x920]   ; restore callee-saved xmm6..13
0x664736b  add rsp,0x9B8          ; frame size 0x9B8
0x6647372  pop rbx / rdi / rsi / r12 / r13 / r14 / r15 / rbp
0x664737e  jmp 0x6698E30          ; tag 6 = ItemInHand extractor
```
Tag 10 (0x6647383..0x66473e1): same instructions, `jmp 0x66D9AF0` at 0x66473e1 = BatchActor extractor (docs/functions: batch actor).
Tag 8 (0x66473e6..0x6647444): same instructions, `jmp 0x66E75F0` at 0x6647444 = BlockSelectionOverlayBlockEntity extractor (description verified in docs/progress/oc_U-D5h.md).
Argument convention of the three extractors therefore equals the visitor's: (rcx = this, rdx = frame context, r8 = description pointer); the description is NOT copied. [V]

Correction of the checklist wording "GlowInkSign inside 8": the string "GlowInkSignForwardPBR" (0xF7CA238) has exactly one code reference, 0x66476d2 (xref.py str), inside the visitor 0x6646980 itself in the material-name hash chain (`mov rcx,0x5857C29E32ACEF88 ; cmp [rax+0x10],rcx` at 0x66476be..0x66476cc, then `lea r9,[0xF7CA238]; mov edx,0x15; call 0x9D6D0` = build a 21-character name). A casewalk from the tag 8 entry (0x66473e6) never reaches 0x66476xx (it only reaches the forwarder), and neither do the tag 0/1/2 cases from their heads; so GlowInkSign belongs to the shared hash-switch area of the visitor (material selected by name hash for sign-like geometry), not to the tag-8 forwarder. Which tag reaches it through the data-driven switch is not proven [?].
