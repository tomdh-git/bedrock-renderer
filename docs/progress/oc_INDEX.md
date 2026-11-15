# Index of verified opencode output (for the merge agent)
Verdicts and checks: docs/progress/oc_verification.md. Verifier: `python tools/sigs/verify_oc.py <file>` (compares each quoted instruction line with the exe).
| Unit | File | Verdict | Feeds checklist item |
|---|---|---|---|
| U-E4-A2 | oc_U-E4-A2.md | accepted (instruction-level, spot-checked) | E4 / L5g body A 0x66ed987..0x66ef28d |
| U-E4-B/C/D | oc_U-E4-B/C/D.md | provisional walkthroughs (diffs vs body A) | E4 bodies B/C/D |
| U-GF | oc_U-GF.md | accepted with correction (0x66af780..99 zeroing) | Gameface 0x66ade80; Viewport write still open |
| U-NT | oc_U-NT.md | accepted (400/400) | nametag producer 0x11276b0 ranges |
| U-IH | oc_U-IH.md | accepted covered part (503/503), continuation running | ItemInHand 0x6698e30 |
| U-UI5 | oc_U-UI5.md | accepted covered part (693/696), continuation running | UI extractor 0x674a3a0 |
| U-PASS/PASS2 | oc_U-PASS.md, oc_U-PASS2.md | negative: c21db0/833e30/c1cb60 are unrelated (0xD30/0x2010 objects) | E2 blocker open; trace readers of 0xC8 records next |
| U-E4-F1 | oc_U-E4-F1.md | accepted (778/778) | builder 0x67762e0 0x67762e0..0x677736d |
| U-ED | oc_U-ED.md | accepted (1018/1018) | editor extractor callees (M1d / R11 Editor) |
| U-PASS3 | oc_U-PASS3.md | accepted (54/54) | E2: consumers sub_bbdad00 / sub_bbbfc50 / sub_562bb00 found |
| U-UI5 | oc_U-UI5.md | accepted (1806/1811, trivial noise) | UI extractor 0x674a3a0 whole function |
| U-E4-F2 | oc_U-E4-F2.md | accepted (796/797; 0x67785b7 wrong) | builder 0x67762e0 0x677736e..0x6778c1a |
| U-IH | oc_U-IH.md | accepted (1340/1340) | ItemInHand 0x6698e30 scoped ranges + callees (D5e/L4i partial) |
| U-E4-G0/G0b/G1 | oc_U-E4-G0.md, G0b, G1 | accepted (202+170+317 lines, all match) | builder 0x670b6e0 0x670b6e0..0x670c5a6 |
| U-PASS4A/4A2 | oc_U-PASS4A.md, oc_U-PASS4A2.md | accepted (430/431 + 1068/1079, noise) | E2: sub_bbdad00 whole function + caller sub_67c9970 |
| U-E4-F3 | oc_U-E4-F3.md | accepted (1248/1248) | builder 0x67762e0 0x6778c1a..0x677a4d0 |
Ticks: none yet; an item closes only when every part is accepted.
| U-PASS5 | accepted (178/178) | docs/progress/oc_U-PASS5.md |
| U-E4-G3 | accepted (619/619) | docs/progress/oc_U-E4-G3.md |
| U-SK1b | accepted partial (694/694) | docs/progress/oc_U-SK1b.md |
| U-E4-H2 | accepted (799/800, 1 fixed) | docs/progress/oc_U-E4-H2.md |
| U-E4-G4 | accepted (777/779, 2 fixed) | docs/progress/oc_U-E4-G4.md |
| U-E4-G5 | accepted (800/800) | docs/progress/oc_U-E4-G5.md |
| U-E4-G6 | accepted (800/800) | docs/progress/oc_U-E4-G6.md |
| U-SK1c | accepted (1040/1040), cold range to 0x665d5d1 | docs/progress/oc_U-SK1c.md |
| U-SK1e | accepted (65/65) | docs/progress/oc_U-SK1e.md |
| U-SK3c | accepted (209/209) | docs/progress/oc_U-SK3c.md |
| U-SK2c | accepted (915/916 + 5 supplied) | docs/progress/oc_U-SK2c.md |
| U-E4-G9 | accepted (383/388 + 3 supplied) -> builder 0x670b6e0 complete | docs/progress/oc_U-E4-G9.md |
| U-E4-F10 | accepted (377/386, 9 cosmetic) -> builder 0x67762e0 complete | docs/progress/oc_U-E4-F10.md |
| U-BA1 | accepted (1355/1355) bodyActor 0x66d0a00..0x66d23a1 | docs/progress/oc_U-BA1.md |
| U-L8b | accepted (263/264), decoder 0x777ed0 found | docs/progress/oc_U-L8b.md |
| U-SK5b | accepted (320/320, complete 0x6658ffc..0x6659615) | docs/progress/oc_U-SK5b.md |
| U-L8d | accepted (184/184), RT LUT loader traced | docs/progress/oc_U-L8d.md |
