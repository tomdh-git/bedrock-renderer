## NEXT
DONE — every verifiable part of K-P9 is [V]-proven (slots 65/65 in .text, 22/22 hook sigs matches=1, layoutcheck 187/0); SelfTest wiring open, lead-owned

# Unit U-EK-P9 — K-P9 Startup validation: fail loudly if slot doesn't point into .text or sig missing — existing convention

Item line (checklist K-P9, docs/RENDER_CHECKLIST.md line 428):
"Startup validation: fail loudly if slot doesn't point into .text or sig missing — existing convention"
Cross-refs: docs/BGFX_MAP.md section 9b ("Each hooked slot must point into .text; each sig must be found; content checks (mask immediates, offset references) must pass [K-P9; L18b: content checks to code in SelfTest, not built]"), L18b/J2 (DONE: 9 unique sigs in Sigs.json, content checks to SelfTest, not built), N4b (mirrors K-P9).

Scope of this unit: prove the statically verifiable parts of the existing convention on the 1.26.62.01 exe:
(1) the hooked RendererContextD3D12 vtable slots all point into .text,
(2) every Sigs.json signature used by the renderer hooks is found exactly once in .text,
(3) the content checks (mask immediates, offset references) pass offline.
The remaining delivery fact — wiring renderlayout::firstSlotOutsideText into SelfTest::runWorldChecks on the live renderer's vtable (65 slots, recordFailure when result < 65) — is documented in docs/progress/platform-versioning-live.md (K-P9 entry) as owned by the lead; src/SelfTest.cpp is not editable by this unit (OPENCODE_BRIEF rule 3), the game is closed, no build allowed, so it is stated as the single open fact below rather than claimed.

Data sources read fully: docs/OPENCODE_BRIEF.md, docs/BGFX_MAP.md sections 1, 6f, 6aj, 6ak, 9b, docs/RENDER_CHECKLIST.md lines 428/500, docs/progress/platform-versioning-live.md K-P9 entry, src/sdk/Sigs.json (deps.bgfx + deps.bgfx.FrameBuilder leaves), docs/data/layout_asserts.json (186 asserts written), tools/sigs/slotcheck.py, tools/sigs/audit.py, tools/sigs/layoutcheck.py.

EXE: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). .text range from the PE headers via xref.py: [0x1000, 0xeec75d6) (tva=0x1000, tvs=0xeec65d6).

## (1) Hooked slots point into .text — slotcheck.py [V]

slotcheck.py finds the vtable without an RVA: the 14 anchored structural slots (7, 10, 12, 14, 22, 24, 26, 39, 40, 41, 46, 50, 58, 60) are resolved via docs/data/function_anchors.tsv; the .rdata table holding all of them at their indices is unique (0xf4ed2d0 = base D3D12 RendererContextD3D12 vtable, BGFX_MAP 6f); then every one of the 65 slots is tested against the .text range.

`python tools/sigs/slotcheck.py --exe <exe>` output on 1.26.62.01:
```
vtable candidates holding every anchored slot at its index: ['0xf4ed2d0']
  table rva=0xf4ed2d0: 65/65 slots in .text
0 failures
```
Exit code 0. All 65 slots of the hooked vtable point into .text; the 14 anchored slots additionally hold the function each anchor resolves to, so a re-ordered vtable fails. Slot values are function entries, proven by the first instruction at each value (table below, Group A).

## (2) Every hook signature found exactly once — audit.py [V]

`python tools/sigs/audit.py <exe>` was run on all of src/sdk/Sigs.json: "80 symbols, 0 with no live pattern" (exit 0). Every deps.bgfx / deps.bgfx.FrameBuilder leaf reports LIVE / matches = 1, i.e. each signature matches exactly once in .text and none is missing:

- BgfxContext::liveContext LIVE rva=0x12bb4910 matches=1 (@3 pattern, site 0xe8179d8)
- D3D12Context::drawExecutor LIVE 0xe821120 matches=1; drawFlush LIVE 0xe81b720; psoBuilder LIVE 0xe81e860; setVertexBuffers LIVE 0xe81b4d0
- Encoder::submit LIVE 0xbc60740; reset LIVE 0xbc60d10; frameSort LIVE 0xbc61e20; dispatch LIVE 0xbc61140; submitCustom LIVE 0xbc61560; submitFrameParams LIVE 0xbc618e0; updateUniforms LIVE 0xbc6a9d0
- FrameGraph::endFrame LIVE 0xc270460; generate LIVE 0xc273420; taskDispatch LIVE 0xe9002e0; viewSetupTask LIVE 0x568cd90
- FrameBuilder::visitEditor LIVE 0x66742f0; visitEffect LIVE 0x666aca0; visitUI LIVE 0x6664a00; visitSky LIVE 0x66560f0; visitItem LIVE 0x6646980; visitLight LIVE 0x6640d80

(RVAs agree with the values documented in Sigs.json comments and BGFX_MAP sections 1/4/6t.)

## (3) Content checks — layoutcheck.py [V]

`python tools/sigs/layoutcheck.py --exe <exe>` over docs/data/layout_asserts.json: "187 assertions, 0 failed", exit code 0 (this session; matches the 186/186 reported earlier in docs/progress/platform-versioning-live.md R13, the manifest grew by one assert in between). Every mask-immediate and offset-reference assertion backed by an immediate/displacement in its anchor function's body passes.

## Answer table

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|

Group A — vtable slots point into .text (slotcheck verified; first instruction at each slot value proves the slot target is a function entry in .text):

| vtable slot 7 (device-lost / TDR handler) | vtable 0xf4ed2d0 +0x38 = 0xf4ed308, holds 0xe8102b0 | 8 (qword slot) | `0xe8102b0  push rbp` | slotcheck: index 7 holds anchor-resolved 0xe8102b0; value ∈ .text [0x1000, 0xeec75d6); role per BGFX_MAP 6ak [I] | [V] |
| vtable slot 10 | vtable 0xf4ed2d0 +0x50 = 0xf4ed320, holds 0xe8124c0 | 8 (qword slot) | `0xe8124c0  push rbp` | slotcheck: index 10 holds 0xe8124c0; value ∈ .text; buffer create/destroy family per BGFX_MAP 6k [I] | [V] |
| vtable slot 12 | vtable 0xf4ed2d0 +0x60 = 0xf4ed330, holds 0xe812bb0 | 8 (qword slot) | `0xe812bb0  mov rax,r8` | slotcheck: index 12 holds 0xe812bb0; value ∈ .text; 6k [I] | [V] |
| vtable slot 14 | vtable 0xf4ed2d0 +0x70 = 0xf4ed340, holds 0xe812be0 | 8 (qword slot) | `0xe812be0  push rbp` | slotcheck: index 14 holds 0xe812be0; value ∈ .text; index/vertex layout family per BGFX_MAP 6k/6aj [I] | [V] |
| vtable slot 22 | vtable 0xf4ed2d0 +0xb0 = 0xf4ed380, holds 0xe8137b0 | 8 (qword slot) | `0xe8137b0  push r15` | slotcheck: index 22 holds 0xe8137b0; value ∈ .text; createShader per BGFX_MAP 6k/6aj [I] | [V] |
| vtable slot 24 | vtable 0xf4ed2d0 +0xc0 = 0xf4ed390, holds 0xe8142c0 | 8 (qword slot) | `0xe8142c0  push r15` | slotcheck: index 24 holds 0xe8142c0; value ∈ .text; createProgram per BGFX_MAP 6k [I] | [V] |
| vtable slot 26 | vtable 0xf4ed2d0 +0xd0 = 0xf4ed3a0, holds 0xe8143c0 | 8 (qword slot) | `0xe8143c0  push rbp` | slotcheck: index 26 holds 0xe8143c0; value ∈ .text; createTexture per BGFX_MAP 6aj table-evidence [V] | [V] |
| vtable slot 39 | vtable 0xf4ed2d0 +0x138 = 0xf4ed408, holds 0xe817880 | 8 (qword slot) | `0xe817880  push r15` | slotcheck: index 39 holds 0xe817880; value ∈ .text; 6k/6aj [I] | [V] |
| vtable slot 40 | vtable 0xf4ed2d0 +0x140 = 0xf4ed410, holds 0xe8176a0 | 8 (qword slot) | `0xe8176a0  push r15` | slotcheck: index 40 holds 0xe8176a0; value ∈ .text; createFrameBuffer per BGFX_MAP line 1809 [V] | [V] |
| vtable slot 41 | vtable 0xf4ed2d0 +0x148 = 0xf4ed418, holds 0xe817c00 | 8 (qword slot) | `0xe817c00  push rsi` | slotcheck: index 41 holds 0xe817c00; value ∈ .text; destroyFrameBuffer per BGFX_MAP line 1809 [V] | [V] |
| vtable slot 46 | vtable 0xf4ed2d0 +0x170 = 0xf4ed440, holds 0xe818a70 | 8 (qword slot) | `0xe818a70  test rdx,rdx` | slotcheck: index 46 holds 0xe818a70; value ∈ .text; 6k [I] | [V] |
| vtable slot 50 (submit) | vtable 0xf4ed2d0 +0x190 = 0xf4ed460, holds 0xe82e230 | 8 (qword slot) | `0xe82e230  push rbp` | slotcheck: index 50 holds 0xe82e230; value ∈ .text; RendererContextD3D12::submit per BGFX_MAP 6k/6aj [V] | [V] |
| vtable slot 58 (init) | vtable 0xf4ed2d0 +0x1d0 = 0xf4ed4a0, holds 0xe807ff0 | 8 (qword slot) | `0xe807ff0  push rbp` | slotcheck: index 58 holds 0xe807ff0; value ∈ .text; init per BGFX_MAP 6aj [V] | [V] |
| vtable slot 60 | vtable 0xf4ed2d0 +0x1e0 = 0xf4ed4b0, holds 0xe81a610 | 8 (qword slot) | `0xe81a610  push r14` | slotcheck: index 60 holds 0xe81a610; value ∈ .text; swapchain/resize/present helper per BGFX_MAP 6k/6aj [I] | [V] |
| vtable all-slot range check | 0xf4ed2d0..0xf4ed4e8, 65 slots | - | - | slotcheck: unique table holding all 14 anchored slots at their indices is 0xf4ed2d0; "65/65 slots in .text"; 0 failures; exit 0 | [V] |

Group B — hook signatures found exactly once in .text (audit.py LIVE/matches=1; first instruction at each match RVA):

| BgfxContext::liveContext (@3) | sig site 0xe8179d8, resolves to global 0x12bb4910 | 24 bytes (sig pattern) | `0xe8179d8  mov rcx,[0x12BB4910]` | audit LIVE matches=1; @3 rip-relative `48 8B 0D ?? ?? ?? ?? ... CC 00` matches once in .text and loads [0x12BB4910] = bgfx_liveContext_global (BGFX_MAP section 1) [V] | [V] |
| Sigs.json Encoder::submit | 0xbc60740 | 26 bytes (sig pattern) | `0xbc60740  push r15` | audit LIVE matches=1; Sigs.json comment documents 0xBC60740 (BGFX_MAP 6cq) [V] | [V] |
| Encoder::reset | 0xbc60d10 | 20 bytes (sig pattern) | `0xbc60d10  push r14` | audit LIVE matches=1 | [V] |
| Encoder::frameSort | 0xbc61e20 | 20 bytes (sig pattern) | `0xbc61e20  push rsi` | audit LIVE matches=1 | [V] |
| Encoder::dispatch | 0xbc61140 | 26 bytes (sig pattern) | `0xbc61140  push r15` | audit LIVE matches=1 | [V] |
| Encoder::submitCustom | 0xbc61560 | 26 bytes (sig pattern) | `0xbc61560  push r15` | audit LIVE matches=1 | [V] |
| Encoder::submitFrameParams | 0xbc618e0 | 25 bytes (sig pattern) | `0xbc618e0  push r15` | audit LIVE matches=1 | [V] |
| Encoder::updateUniforms | 0xbc6a9d0 | 20 bytes (sig pattern) | `0xbc6a9d0  push r15` | audit LIVE matches=1 | [V] |
| FrameGraph::endFrame | 0xc270460 | 30 bytes (sig pattern) | `0xc270460  push rbp` | audit LIVE matches=1; BGFX_MAP section 4 (0xc270460) [V] | [V] |
| FrameGraph::generate | 0xc273420 | 20 bytes (sig pattern) | `0xc273420  push rbp` | audit LIVE matches=1 | [V] |
| FrameGraph::taskDispatch | 0xe9002e0 | 57 bytes (sig pattern) | `0xe9002e0  push rbp` | audit LIVE matches=1 (priority high); BGFX_MAP section 4 [V] | [V] |
| FrameGraph::viewSetupTask | 0x568cd90 | 33 bytes (sig pattern) | `0x568cd90  push rbp` | audit LIVE matches=1 | [V] |
| D3D12Context::drawExecutor | 0xe821120 | 19 bytes (sig pattern) | `0xe821120  push rbp` | audit LIVE matches=1; BGFX_MAP 6cs [V] | [V] |
| D3D12Context::psoBuilder | 0xe81e860 | 20 bytes (sig pattern) | `0xe81e860  push r15` | audit LIVE matches=1; BGFX_MAP 6ct [V] | [V] |
| D3D12Context::drawFlush | 0xe81b720 | 25 bytes (sig pattern) | `0xe81b720  push r15` | audit LIVE matches=1; BGFX_MAP 6ej [V] | [V] |
| D3D12Context::setVertexBuffers | 0xe81b4d0 | 25 bytes (sig pattern) | `0xe81b4d0  push r15` | audit LIVE matches=1 | [V] |
| FrameBuilder::visitEditor | 0x66742f0 | 118 bytes (sig pattern) | `0x66742f0  push rbp` | audit LIVE matches=1 | [V] |
| FrameBuilder::visitEffect | 0x666aca0 | 65 bytes (sig pattern) | `0x666aca0  push rbp` | audit LIVE matches=1 | [V] |
| FrameBuilder::visitUI | 0x6664a00 | 29 bytes (sig pattern) | `0x6664a00  push rbp` | audit LIVE matches=1 | [V] |
| FrameBuilder::visitSky | 0x66560f0 | 97 bytes (sig pattern) | `0x66560f0  push rbp` | audit LIVE matches=1 | [V] |
| FrameBuilder::visitItem | 0x6646980 | 32 bytes (sig pattern as stored) | `0x6646980  push rbp` | audit LIVE matches=1 | [V] |
| FrameBuilder::visitLight | 0x6640d80 | 32 bytes (sig pattern as stored) | `0x6640d80  push rbp` | audit LIVE matches=1 | [V] |

## CLOSES?

YES — every verifiable part of K-P9 is [V]-proven by table rows: (1) all 65 slots of the hooked RendererContextD3D12 vtable (0xf4ed2d0) point into .text [0x1000, 0xeec75d6), 0 failures, and the 14 anchored slots hold their anchor-resolved functions (slotcheck exit 0); (2) all 22 renderer hook signatures in Sigs.json match exactly once in .text (audit: LIVE/matches=1 each, 0 DEAD or MULTI among them; 80 symbols total, 0 with no live pattern); (3) content checks pass: layoutcheck 187 assertions, 0 failed (exit 0). The "existing convention" therefore exists and passes on 1.26.62.01: Sigs.json + docs/data/layout_asserts.json + tools/sigs/slotcheck.py + tools/sigs/layoutcheck.py + src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h.

Single remaining fact (integration, not part of the static convention above): wiring renderlayout::firstSlotOutsideText into SelfTest::runWorldChecks on the live renderer vtable (65 slots, recordFailure when result < 65) — documented in docs/progress/platform-versioning-live.md K-P9 entry, owned by the lead; not doable by this unit (src/SelfTest.cpp not editable, OPENCODE_BRIEF rule 3; game closed; no build). Noted open, does not invalidate the [V]-proven convention.

## TOOL REQUESTS

None (existing tools only: slotcheck.py, audit.py, layoutcheck.py, rdis.exe; no helper script written).
