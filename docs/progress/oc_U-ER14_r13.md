## NEXT
DONE (R14 rollup table written; CLOSES? NO — M1c, M1d, M1e, M3a, M3c, M3e, M3f, M1f still open)

# R14 rollup — M-section sub-items (docs/RENDER_CHECKLIST.md section M, item R14 at line 612)

R14 is a rollup of M1b, M1c, M1d, M1e, M3a-M3f, M4a-M4d, M1f. Each sub-item below shows its current [x]/[ ] state exactly as written in docs/RENDER_CHECKLIST.md (read in full this run, lines 431-612). No disassembly was done for this rollup; states are copied from the checklist, and evidence cites the accepting unit file where one exists. The two backtick lines are verbatim rdis citations of already-D2-dossiered functions, quoted as [V] evidence only.

| Sub-item | State | Evidence |
|---|---|---|
| M1b Inventory per layer (functions.tsv D0 + class column) | [x] | oc_U-EM1b.md verify_oc 8/8; 15113 D0+ rows, functions_full.tsv joined |
| M1c Dossiers D2 for L1-L3 structural functions | [ ] | open |
| M1d Dossiers for FrameBuilder clones/visitors/extractors | [ ] | open |
| M1e Pass lambdas L6 with in/out resources | [ ] | open |
| M3a Data structures: headers + startup self-check | [ ] | open |
| M3b Control flow: frame trace, every path fn has D2 dossier | [x] | oc_U-EM3b.md verify_oc 24/24; FRAME_CALLGRAPH.md; `0x67c9c20  push rbp` [V] |
| M3c Frame graph: add/remove/reorder a pass | [ ] | open |
| M3d Actor to draw, re-validated on 1.26.62.01 | [x] | oc_U-EM3d.md verify_oc 67/67; `0xe81b720  push r15` [V] |
| M3e Edit draws at submit (flush record mapping + in-game test) | [ ] | open |
| M3f Whole-frame replacement via submitCustom seam | [ ] | open (PROGRESS: seam decoded, untested in game) |
| M4a Version-stable anchors beside RVAs | [x] | oc_U-EM4a.md verify_oc 11/11 |
| M4b Behaviour notes without RVAs | [x] | oc_U-EM4b.md verify_oc 9/9 |
| M4c Startup validation (slots/sigs/content checks) | [x] | mirror of N4b/O3b; layoutcheck 199/0 |
| M4d Port check on previous exes | [x] | oc_U-EO3c.md verify_oc 130/130 |
| M1f D3 pass: live/in-game check per D2 claim | [ ] | PARTIAL = NOT DONE |

CLOSES? NO — still-open sub-items: M1c, M1d, M1e, M3a, M3c, M3e, M3f, M1f
