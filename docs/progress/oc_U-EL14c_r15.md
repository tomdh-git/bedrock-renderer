## NEXT
step 2

# Unit U-EL14c: L14c Text/font — glyph atlas (static angles exhausted; live capture pending)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending" (BGFX_MAP.md 6ce anchors UI pass extractor 0x674a3a0 and lists "Still pending: glyph atlas management"). The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the GLYPH ATLAS — the 16-byte atlas NAME bound as GlyphTexture at draw time, who writes it, and its load site.

## Blocking fact (single unknown)

The live 16-byte glyph atlas NAME bytes have never been captured. The name is caller-provided arg8 ([rbp+0xEB8]) in UI extractor 0x674a3a0, loaded as a 16-byte SSO texture NAME via `0x674aa09  movups xmm0,[rax]` and written into the hash-selected GlyphTexture uniform slot by sub_5679DB0 (`0x5679df9  call 0xEEC6EC0`, memcpy 16). The field that carries it is the UI item/description record field (UIText case 0x6664c83 passes &d.texture at description+0x10; visitor paths stage [r9+0x28] stride-0x38 / [r9] stride-0x86). Assembled by record builder sub_6664760 (vtable[0] of .rdata dispatch table at 0xf2be218; wrapper slot 109 "FrameBuilder - Insert UI" per BGFX_MAP.md 6ce), whose inbound caller is reachable only through indirect dispatch (0 static callers). No createTexture/createDynamicTexture call ANYWHERE in .text; texload 0x58a1310 has no font caller; no glyph-atlas name string located; "ui_text_msdf"/"_ttf"/"_ttfmsdf" dead ends. The atlas is a named pack texture resolved by name at draw time; its NAME, writer and load site require live data.

## Live capture status (this run)

Per orchestrator 2026-11-22 22:35, the two earlier captures must NOT be re-requested (0 hits each, 60 s, loaded world, text visible):
- l14c_glyph_draw 0x674a3a0 size 0x200 max 8: state=done, hits=0
- l14c_record_builder 0x6664760 size 0x200 max 8: state=done, hits=0

Replacement capture queued by prior run (state=pending, must NOT be re-added — duplicate pending names are rejected):
- l14c_uniform_writer 0x5679db0 size 0x100 max 8: `python tools/livecap/request.py add l14c_uniform_writer 0x5679db0 --size 0x100 --max 8` (UniformBlock::setVec4Array entry; 390 static call sites, bounded, max-8 entry sampling; hits filtered to the GlyphTexture slot write, index 0x000A = 10; the dumped 16 bytes at namePtr are the atlas NAME [LIVE]). `python tools/livecap/request.py result l14c_uniform_writer` -> "no result yet (orchestrator has not run it)".

livemem: `python tools/sigs/livemem.py status` -> "game not running (no Minecraft.Windows.exe process)". Per brief rule 30 the game is closed and I may not start it; livemem unavailable until the game runs. No livemem target address exists anyway (name-buffer addresses are past-run ASLR values).

## New angles tried this run (not redone from r1-r12)

- BGFX_MAP.md 6ce re-read: UI group insert wrapper slot 109 = 0x6664760 ("FrameBuilder - Insert UI"), visitor 0x6664a00, case jump table 0xF2BF468, 5 cases (Gameface 0x6664a6c, HudIcon 0x6664d51, UIMesh 0x6664bd6, UIText 0x6664c83, UIImGui 0x6664aab). [V group_visitors.md]
- UIText case 0x6664c83 calls 0x674a3a0 directly with the description's fields: `src = d+0x00`, `d+0x08`, `&d.texture (+0x10)`, `d+0x20`, `d+0x28`, `d+0x30`, `&d.flags (+0x38)`, `d.byte3A`, `&d.variant (+0x40)`; matches RenderUITextDescription in Descriptions.h. [V group_visitors.md] => d.texture at description+0x10 is the 16-byte SSO texture-name field delivered to the renderer as the name pointer (arg8).
- `xref.py callers 0x6664a00` and sibling-wrapper callers: pending probe (not yet run).
- Writer of description+0x10 (the atlas-name writer): not yet located statically; the description is built by the UI/Hud text layout path (cohtml-side text entities), variant constructed before the wrapper dispatch — no static writer found yet.
- `rdis imm 0xf2be218` (0 hits) and `xref.py ptr 0xf2be218` (0 hits) from r1-r12 stand: the vtable address is stored nowhere; builder inbound caller not statically locatable.

## Offset table (one row per distinct offset; all its sites listed; verbatim instr line; size from instruction; [V]/[I]/[-])

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|

## CLOSES?

CLOSES? NO — missing REVERSING: the single unknown is the live 16-byte glyph atlas NAME bytes (the atlas identity) and the writer/load site of the UI record/description name field that becomes sub_674a3a0's arg8 (inbound caller of sub_6664760 via .rdata dispatch, and who writes RenderUITextDescription+0x10). The l14c_uniform_writer capture at 0x5679db0 is queued (state=pending) awaiting the orchestrator; read it with `python tools/livecap/request.py result l14c_uniform_writer`. If the capture shows the name, its load site is found with `rdis str` on that string / its hash, and the item closes. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units), the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; slot index 0x000A=10), and that the atlas is a named pack texture, not created by font code.

## What I tried that failed (new angles; static r1-r12 angles not redone)

- l14c_glyph_draw (0x674a3a0) and l14c_record_builder (0x6664760): state=done, hits=0, samples=0 — neither function fires on the live glyph-text path; do NOT re-request (orchestrator 2026-11-22 22:35).
- livemem: game not running; unavailable until the game runs (brief rule 30).
- Static angles from r1-r12 remain exhausted: object+0x38 contradicted; no createTexture/createDynamicTexture ANYWHERE in .text; no glyph-atlas name string; font init/reset create no textures; "ui_text_msdf"/"_ttf"/"_ttfmsdf" dead ends; 0xEEC7570 call at 0x4f78966 refuted as strlen, not a texture fetch.

## TOOL REQUESTS

- l14c_uniform_writer | `python tools/livecap/request.py add l14c_uniform_writer 0x5679db0 --size 0x100 --max 8 --why "L14c: UniformBlock::setVec4Array entry; capture the GlyphTexture slot write (index 0x000A): r8 = {count=1, namePtr}; the dumped 16 bytes at namePtr are the atlas NAME [LIVE]. ret= names the caller"` | ALREADY QUEUED (state=pending) per orchestrator hint 2026-11-22 22:35 — do NOT re-add (duplicate pending names are rejected); read results with `python tools/livecap/request.py result l14c_uniform_writer`. Not flagged too hot (bounded entry sampling, max 8); if the orchestrator reports it as too hot / 0 hits, answer NO with exactly that, and the single unknown stays the live 16-byte NAME bytes.
- livemem read | none possible now | `python tools/sigs/livemem.py status` -> game not running; brief rule 30: write the request in the progress file instead.
- None (helper scripts): all evidence from rdis.exe dis/fn/imm/vt, xref.py callers/str/ptr, descscan2.py; no throwaway one-liners needed; no _tmp files left behind.

## NEXT
step 2
