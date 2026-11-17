## NEXT
DONE

# Unit U-EJ3 — J3 optimisation hook seams: version-stability validation

Item line (checklist J3): "J3 Optimisation hook seams listed (6bh) + docs/PLAN_OPTIMIZATION.md; validation pending (P1) — seams are version-stable".

Pending part (the only part this unit touches): validate whether every optimisation hook seam is version-stable. The seams named in BGFX_MAP 6bh are: draw-list level (executor 0xE821120 loop + scissor, 6am/6an), sort key program index (6ao), pass declaration (6aq/6ar), DLSS mode (6bc), terrain extractor 0x66EA3D0 (6be), actor identity (6bg). PLAN_OPTIMIZATION.md names the chunk/cull/entity/draw paths.

Version-stability evidence (docs/data/port_check_render_sigs.tsv — port check of Sigs.json across 1.26.50.04 / 1.26.51.01 / 1.26.60.05 / 1.26.62.01):
- Version-stable (unique match in ALL four versions): Encoder::submit 0xBC60740, Encoder::reset 0xBC60D10, Encoder::frameSort 0xBC61E20, draw flush 0xE81B720.
- Version-sensitive (DEAD on 1.26.50/51, live on 60.05/62.01, moved +0xC00 between 60.05 and 62.01): drawExecutor 0xE821120, psoBuilder 0xE81E860, endFrame 0xC270460, generate 0xC273420, taskDispatch 0xE9002E0, viewSetupTask 0x568CD90.
- Not present in the port-check TSV (version unknown): DLSS slot 60 0xE83EC70, terrain extractor 0x66EA3D0, bodyActor 0x66D0A00, passLookup 0x5ABA5C0, VV builder 0x55F1450.

So the seams are NOT all version-stable: several are version-sensitive, and several have no port-check data.

## Verbatim proof lines (each checked by tools/sigs/verify_oc.py against rdis dis of Minecraft.Windows.exe 1.26.62.01)

0xBC60748  sub rsp,0x68
0xBC60D15  sub rsp,0x48
0xBC61E22  sub rsp,0x238
0xE81B72C  sub rsp,0x88
0xE82112C  mov eax,0xE238
0xE81E86C  sub rsp,0x768
0xC27046C  sub rsp,0xC8
0xE9002EC  sub rsp,0x1E8
0x568CD9C  sub rsp,0x1D8
0xE83EC7C  sub rsp,0x68
0x66EA3DC  mov eax,0x1808
0x66D0A0C  sub rsp,0xE38
0x5ABA5C5  sub rsp,0x28
0x55F1450  push rbp

## (1) Answer table — optimisation hook seams and version-stability

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| Encoder::submit (draw-path seam, host entry) | 0xBC60740 | - | - | `0xBC60748  sub rsp,0x68` | draw-path seam (submit takes Frame* in rdx); port check: unique match in all 4 versions (50.04/51.01/60.05/62.01) -> version-stable | [V] |
| Encoder::reset | 0xBC60D10 | - | - | `0xBC60D15  sub rsp,0x48` | reset seam; port check: unique match in all 4 versions -> version-stable | [V] |
| Encoder::frameSort (sort-key seam) | 0xBC61E20 | - | - | `0xBC61E22  sub rsp,0x238` | sort-key / frame sort seam; port check: unique match in all 4 versions -> version-stable | [V] |
| draw flush (draw-list commit seam) | 0xE81B720 | - | - | `0xE81B72C  sub rsp,0x88` | draw flush seam; port check: unique match in all 4 versions -> version-stable | [V] |
| drawExecutor (draw-list loop + scissor, 6am/6an) | 0xE821120 | - | - | `0xE82112C  mov eax,0xE238` | draw-list level seam; port check: DEAD on 50.04/51.01, live on 60.05/62.01, moved +0xC00 -> version-sensitive | [I] |
| psoBuilder (PSO key seam, 6ao) | 0xE81E860 | - | - | `0xE81E86C  sub rsp,0x768` | sort-key program-index / PSO seam; port check: version-sensitive (+0xC00, DEAD on 50/51) | [I] |
| endFrame (frame-graph encode seam) | 0xC270460 | - | - | `0xC27046C  sub rsp,0xC8` | pass-level enable/disable seam; port check: version-sensitive (+0xC00, DEAD on 50/51) | [I] |
| taskDispatch (pass-control seam) | 0xE9002E0 | - | - | `0xE9002EC  sub rsp,0x1E8` | task dispatch seam; port check: version-sensitive (+0xC00, DEAD on 50/51) | [I] |
| viewSetupTask | 0x568CD90 | - | - | `0x568CD9C  sub rsp,0x1D8` | view setup task seam; port check: version-sensitive (+0xC00, DEAD on 50/51) | [I] |
| DLSS slot 60 (upscaling mode seam, 6bc) | 0xE83EC70 | - | - | `0xE83EC7C  sub rsp,0x68` | DLSS/fallback/off mode decision seam; not in port-check TSV -> version-unknown | [?] |
| terrain extractor (chunk/draw seam, 6be) | 0x66EA3D0 | - | - | `0x66EA3DC  mov eax,0x1808` | terrain chunk draw seam (Item tag 3); not in port-check TSV -> version-unknown | [?] |
| bodyActor (actor identity seam, 6bg) | 0x66D0A00 | - | - | `0x66D0A0C  sub rsp,0xE38` | actor identity route (bodyActor S+0xC8); not in port-check TSV -> version-unknown | [?] |
| passLookup (item->pass seam, 6bg) | 0x5ABA5C0 | - | - | `0x5ABA5C5  sub rsp,0x28` | passLookup returns pass whose first member is item vector; not in port-check TSV -> version-unknown | [?] |
| VV builder (pass declaration seam, 6aq/6ar) | 0x55F1450 | - | - | `0x55F1450  push rbp` | VV pass declaration builder (252 passes); not in port-check TSV -> version-unknown | [?] |

## (2) CLOSES?

NO. The pending part is to validate that every optimisation hook seam is version-stable. The port check (docs/data/port_check_render_sigs.tsv) proves only the bgfx core seams (Encoder::submit/reset/frameSort, draw flush) are version-stable (unique match in all 4 versions). The draw-list executor drawExecutor 0xE821120 — a core draw-path seam — is version-sensitive: DEAD on 1.26.50.04/51.01 and moved +0xC00 between 1.26.60.05 and 1.26.62.01. Several other seams (DLSS slot 60, terrain extractor, bodyActor, passLookup, VV builder) have no port-check data at all (version-unknown). Single blocking fact: drawExecutor 0xE821120 is not version-stable, so the claim "seams are version-stable" cannot be closed as YES.

## TOOL REQUESTS

None (rdis.exe only, no helper script written).
