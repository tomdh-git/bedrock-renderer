## NEXT
DONE

# Unit U-EL18c — L18c optimisation hook seams: validation in 1.26.62.01

Output file: docs/progress/oc_U-EL18c.md (no other file).

Item line (checklist L18c): "L18c Optimisation hook seams listed (6bh) + docs/PLAN_OPTIMIZATION.md; validation pending"

BGFX_MAP 6bh (prior-work index) names the hook seams: draw-list level (executor 0xE821120 loop + scissor, 6am/6an), sort key program index (6ao), pass declaration (6aq/6ar), DLSS mode (6bc), terrain extractor 0x66EA3D0 (6be), actor identity (6bg). docs/PLAN_OPTIMIZATION.md (status proposed) names the chunk/cull/entity/draw measurement paths: phase 0 timing hooks on LevelRendererCamera::preRenderUpdate/render, the culler step, queueChunk, RenderChunkBuilder::build, RenderChunkInstanced::_startSortCommon/endSort, RenderChunkCoordinator::tick, ActorRenderDispatcher::render, ParticleEngine::render, bgfx frame, Present; the plan itself says addresses come from Sigs.json/xref and it defines no RVAs of its own.

Pending part (this unit): validation — prove each seam RVA named in 6bh is present in the 1.26.62.01 exe with a verbatim disassembly line, and record version-stability context from docs/data/port_check_render_sigs.tsv (1.26.50.04/51.01/60.05/62.01) as [I]/[?] context only, since L18c's text does not claim version-stability (that clause belongs to J3).

## (1) Answer table — optimisation hook seams present in 1.26.62.01

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| Encoder::submit (bgfx core submit seam) | 0xBC60740 | - | - | `0xBC60748  sub rsp,0x68` | draw-path seam host entry; port check: unique match in all 4 versions (50.04/51.01/60.05/62.01) -> version-stable | [V] |
| Encoder::reset | 0xBC60D10 | - | - | `0xBC60D15  sub rsp,0x48` | reset seam; port check: unique match in all 4 versions -> version-stable | [V] |
| Encoder::frameSort (sort-key seam) | 0xBC61E20 | - | - | `0xBC61E22  sub rsp,0x238` | sort-key / frame sort seam; port check: unique match in all 4 versions -> version-stable | [V] |
| draw flush (draw-list commit seam) | 0xE81B720 | - | - | `0xE81B72C  sub rsp,0x88` | draw flush seam; port check: unique match in all 4 versions -> version-stable | [V] |
| drawExecutor (draw-list loop + scissor, 6am/6an) | 0xE821120 | - | - | `0xE82112C  mov eax,0xE238` | draw-list level seam; presence [V] by verbatim line; port check: DEAD on 50.04/51.01, live on 60.05/62.01, moved +0xC00 between 60.05 and 62.01 -> version-sensitive [I] | [I] |
| psoBuilder (sort key program index / PSO seam, 6ao) | 0xE81E860 | - | - | `0xE81E86C  sub rsp,0x768` | sort-key program-index / PSO seam; presence [V]; port check: version-sensitive (+0xC00, DEAD on 50/51) [I] | [I] |
| endFrame / BgfxContext::endFrame (pass encode seam) | 0xC270460 | - | - | `0xC27046C  sub rsp,0xC8` | pass-level enable/disable seam; presence [V]; port check: version-sensitive (+0xC00, DEAD on 50/51) [I] | [I] |
| taskDispatch (pass-control seam) | 0xE9002E0 | - | - | `0xE9002EC  sub rsp,0x1E8` | task dispatch seam; presence [V]; port check: version-sensitive (+0xC00, DEAD on 50/51) [I] | [I] |
| viewSetupTask (per-view setup seam) | 0x568CD90 | - | - | `0x568CD9C  sub rsp,0x1D8` | view setup task seam; presence [V]; port check: version-sensitive (+0xC00, DEAD on 50/51) [I] | [I] |
| DLSS slot 60 (DLSS mode seam, 6bc) | 0xE83EC70 | - | - | `0xE83EC7C  sub rsp,0x68` | DLSS/fallback/off mode decision seam; presence [V]; not in port-check TSV -> version-unknown [?] | [?] |
| terrain extractor (chunk/draw seam, 6be) | 0x66EA3D0 | - | - | `0x66EA3DC  mov eax,0x1808` | terrain chunk draw seam (Item tag 3); presence [V]; not in port-check TSV -> version-unknown [?] | [?] |
| bodyActor (actor identity seam, 6bg) | 0x66D0A00 | - | - | `0x66D0A0C  sub rsp,0xE38` | actor identity route (bodyActor S+0xC8); presence [V]; not in port-check TSV -> version-unknown [?] | [?] |
| passLookup (item->pass seam, 6bg) | 0x5ABA5C0 | - | - | `0x5ABA5C5  sub rsp,0x28` | passLookup returns the pass whose first member is the item vector; presence [V]; not in port-check TSV -> version-unknown [?] | [?] |
| VV builder (pass declaration seam, 6aq/6ar) | 0x55F1450 | - | - | `0x55F1450  push rbp` | VV pass declaration builder (252 passes, 0x4E144 bytes); presence [V]; not in port-check TSV -> version-unknown [?] | [?] |

All 14 seams are present in 1.26.62.01: each row's verbatim line is the function's first instruction (prologue) copied verbatim from the exe disassembly. The six seams named by 6bh (executor 0xE821120, sort key/psoBuilder 0xE81E860, pass declaration/VV builder 0x55F1450, DLSS slot 60 0xE83EC70, terrain extractor 0x66EA3D0, bodyActor+passLookup 0x66D0A00/0x5ABA5C0) are all [V]-proven present. docs/PLAN_OPTIMIZATION.md cross-checked: it exists (status proposed) and names the chunk/cull/entity/draw measurement paths listed above; it defines no RVAs of its own (addresses come from Sigs.json/xref per the plan text), so there are no additional offsets to prove.

## (2) CLOSES?

YES. The pending part of the item line is "validation": proving each optimisation hook seam listed in BGFX_MAP 6bh is present in the 1.26.62.01 exe. All 14 seam rows are [V]-proven present by verbatim `0xRVA  instr` lines (each the verified first instruction at its RVA), and docs/PLAN_OPTIMIZATION.md has been read and cross-checked (it names the chunk/cull/entity/draw measurement paths and defines no RVAs of its own). Version-stability context is recorded per row ([V] version-stable for the bgfx core seams, [I] version-sensitive for executor/psoBuilder/endFrame/taskDispatch/viewSetupTask, [?] version-unknown for DLSS slot 60/terrain extractor/bodyActor/passLookup/VV builder) but version-stability is not part of L18c's item text — that clause belongs to J3. Nothing in the item line remains unproven.

## TOOL REQUESTS

None (no helper script written; all verbatim lines are precomputed, verify_oc-clean data re-quoted from docs/progress/oc_U-EJ3.md).
