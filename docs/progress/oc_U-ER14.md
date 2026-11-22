## NEXT
DONE

# Unit U-ER14 — Close checklist item R14

Source item (docs/RENDER_CHECKLIST.md line 612):
`- [ ] R14 M1b classification, M1c/M1d/M1e dossier gaps, M3a-M3f, M4a-M4d, M1f (see their own lines)`

This is a meta ledger item: it references its own sub-lines in section M of the checklist, none of which is `[x]`. I close only what can be proven here — that each referenced anchor RVA exists in the 1.26.62.01 exe (verified by rdis, verbatim first instruction) — and record that none of the sub-lines is closed, so R14 stays `[ ]`.

Sub-line states from docs/RENDER_CHECKLIST.md:
- M1b classification — `[ ]` (inventories exist for L1/L2/L3/L4-L5/L6; annotate/classify + add big render function rows remain)
- M1c — `[ ]` (D2 dossiers done for submit/draw-flush/executor/PSO builder/submit 0xe82e230/Frame::sort/endFrame/Context::frame/dispatch/init/handoff/Execute; many others still D1/open)
- M1d — `[ ]` (BatchActor/ItemInHand dossiers started; chunk/skinned/nametag/particle/sky/clones/visitors/extractors open)
- M1e — `[ ]` (35 VV/RTX lambdas + Fancy pass bodies with in/out resources; ScreenDraw mapped, non-ScreenDraw bodies open)
- M3a — `[ ]` (static_asserts + SelfTest validate sizes/offsets)
- M3b — `[ ]` (one frame traced game logic -> submit with every function D2; open links remain)
- M3c — `[ ]` (TaskDispatchHook + dragon/Tasks.h written, never built or run)
- M3d — `[ ]` (actor->draw via RenderMarkHook; re-validate against flush 0xe81b720 + Encoder::submit seam)
- M3e — `[ ]` (edit draws at submit; needs header->record mapping + in-game test)
- M3f — `[ ]` (whole-frame replacement; custom item submitCustom key bit 53 seam found, untested)
- M4a — `[ ]` (version-stable anchor string/__FUNCSIG__/sig beside every D2/D3 RVA)
- M4b — `[ ]` (behaviour notes without RVAs, one paragraph per structural function)
- M4c — `[ ]` (startup validation: slots into .text, sigs found, content checks)
- M4d — `[ ]` (port check: dossier tool re-run on previous exes for every D2 function)
- M1f — `[ ]` PARTIAL = NOT DONE (every D2 dossier gets a D3 live poll-only read; only first two passes done)

## Field/anchor evidence table (one row per distinct anchor RVA; all sites listed; verbatim `0xRVA  instr` copied from rdis of the exe)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
| M1c anchor: RendererContextD3D12::submit (slot 50) | 0xe82e230 | 0x4d91 | `0xe82e230  push rbp` | [V] |
| M1c anchor: draw executor 0xe821120 | 0xe821120 | 0xc3c3 | `0xe821120  push rbp` | [V] |
| M3e anchor: draw flush 0xe81b720 | 0xe81b720 | 0x2000 | `0xe81b720  push r15` | [V] |
| M1c anchor: BgfxFrameBuilder::endFrame 0xc270460 | 0xc270460 | 0x2aa | `0xc270460  push rbp` | [V] |
| M1c anchor: dragon frame graph generate 0xc273420 | 0xc273420 | 0x8A73 | `0xc273420  push rbp` | [V] |
| M1c anchor: Context::init/thread start 0xbc63690 | 0xbc63690 | 0x4e7 | `0xbc63690  push rsi` | [V] |
| M1c anchor: D3D12 init slot 58 0xe807ff0 | 0xe807ff0 | - | `0xe807ff0  push rbp` | [V] |
| M3c anchor: task dispatch 0xe9002e0 | 0xe9002e0 | - | `0xe9002e0  push rbp` | [V] |
| M3d anchor: bodyActor 0x66d0a00 | 0x66d0a00 | - | `0x66d0a00  push rbp` | [V] |
| M1c anchor: Item visitor 0x6646980 | 0x6646980 | - | `0x6646980  push rbp` | [V] |

## What is proven vs what remains open

Proven [V] here: each anchor RVA above is a real function entry in the exe (verbatim first instruction matches rdis). Sizes 0x4d91/0xc3c3/0x2aa/0x8A73/0x4e7 are taken from docs/BGFX_MAP.md section 6t/6n-2/6q ([V/I] there).

Not proven (blocking R14): none of the sub-lines M1b, M1c-M1e, M3a-M3f, M4a-M4d, M1f is closed. Classification (M1b) is not annotated/added to functions.tsv; dossier gaps (M1c-M1e) remain D1/open for the majority of structural functions; acceptance capabilities M3a-M3f are all `[ ]` (no SelfTest validation, no full frame trace, TaskDispatchHook not built/run, RenderMarkHook not re-validated against the new flush, no draw edit in game, no whole-frame takeover); version resilience M4a-M4d is all `[ ]` (no per-function anchors, no behaviour notes, no startup validation wired, no port check on older exes); M1f D3 live checks are PARTIAL (only two passes done). These are multi-unit efforts tracked as `[ ]`/PROGRESS/PARTIAL in the checklist; none is closed by [V] verbatim-instruction rows in this note.

CLOSES?: NO — blocking fact: every sub-line referenced by R14 (M1b classification, M1c/M1d/M1e dossier gaps, M3a–M3f acceptance capabilities, M4a–M4d version resilience, M1f D3 live checks) is still `[ ]` or PROGRESS/PARTIAL in docs/RENDER_CHECKLIST.md; none is proven closed by [V] verbatim-instruction rows, so R14 cannot be ticked [x].

## TOOL REQUESTS
None
