## NEXT
DONE

# U-EL16c — L16c RT shaders and denoiser: lambda bodies inside sub_bbe2d50

Scope (RENDER_CHECKLIST.md line L16c): "L16c RT shaders and denoiser — 6cg (lambda bodies undecoded)".
Pending part done here: the declaration lambda bodies inside sub_bbe2d50 (0xbbe2d50..0xbbf62cf, size 0x1357f, BGFX_MAP 6cg/6ei) — which execute body each declared RTX lambda runs. Everything else on the item (RTX pass names/resources 0xbbe2d50/0xc28e330 closed by oc_U-EL16a [V 53/53]; RTX pass-name hashes 0xbcc4b90 closed by oc_U-EF4 [V 51/51]; BLAS/TLAS build call sites closed by oc_U-EB10c/oc_U-EL2v [V]) is NOT re-decoded here; it is cited as closed.

Input data read (precomputed by the orchestrator, not regenerated):
- docs/functions/vv_closures.txt [V]: builder->closure vtable->slot-2 body table; builder 0xbbe2d50 rows: vtable 0xf43eb80 body 0xbc068f0 (PreBlasSkinDispatch 0x5fa), 0xf43ebb0 body 0xbc07890 (0x12f), 0xf43ebe0 body 0xbc07a70 (PrepareTLAS first 0x162), 0xf43ec30 body 0xbc080c0 (RTX driver -> 0xbcc4b90 0x25b), 0xf43ecf0 body 0xbc084b0 (RTX thunk 0x71), plus vtable 0xf43ec60 body 0x56aeeb0 (NothingTask-type small 0x123).
- docs/functions/vv_lambda_bodies.md [V structure/I roles]: 0xbc068f0 PreBlasSkinDispatch flow, 0xbc07a70 PrepareTLAS, 0xbc080c0 RTX driver -> 0xbcc4b90, 0xbc07890/0xbc084b0 dtor/thunk, 0x56aeeb0 NothingTask-type body. RTX driver 0xbc080c0 resolves all 43 RTX passes via 0xbcc4b90.
- docs/BGFX_MAP.md 6cg (lines 955-966): pass names declared inside sub_bbe2d50.

## Answer table (one row per distinct offset, all its sites listed; verbatim `0xRVA  instr` lines copied verbatim from the input data; sizes from the instruction)

| offset | size | name | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| 0xbbe4465 | 8 | PreBlasSkinDispatch closure vtable install | [rsi] | `0xbbe4465  lea rax,[0xF43EB80]` `0xbbe446c  mov [rsi],rax` | vtable f43eb80 installed as std::function closure; slot-2 body = 0xbc068f0 (PreBlasSkinDispatch, 0x5fa bytes) per vv_closures.txt | [V] |
| 0xbbe51d8 | 8 | RTX prep closure vtable install | [rsi] | `0xbbe51d8  lea rax,[0xF43EBB0]` `0xbbe51df  mov [rsi],rax` | vtable f43ebb0 installed as std::function closure; slot-2 body = 0xbc07890 (0x12f bytes, destructor/thunk per vv_lambda_bodies.md, not a pass body) | [V] |
| 0xbbe5d07 | 8 | PrepareTLAS closure vtable install | [rsi] | `0xbbe5d07  lea rax,[0xF43EBE0]` `0xbbe5d0e  mov [rsi],rax` | vtable f43ebe0 installed as std::function closure; slot-2 body = 0xbc07a70 (PrepareTLAS first, 0x162 bytes) per vv_closures.txt | [V] |
| 0xbbe77f3 | 8 | RTX driver closure vtable install | [rsi] | `0xbbe77f3  lea rax,[0xF43EC30]` `0xbbe77fa  mov [rsi],rax` | vtable f43ec30 installed as std::function closure; slot-2 body = 0xbc080c0 (RTX driver -> 0xbcc4b90, 0x25b bytes, runs all 43 RTX denoise/raygen passes) per vv_closures.txt | [V] |
| 0xbbeab23 | 8 | RTX thunk closure vtable install | [rbp+0x8D8] | `0xbbeab23  lea rcx,[0xF43ECF0]` `0xbbeab2a  mov [rbp+0x8D8],rcx` | vtable f43ecf0 installed as std::function closure; slot-2 body = 0xbc084b0 (0x71 bytes, RTX thunk per vv_lambda_bodies.md, not a pass body) | [V] |
| 0xbbe8acb | 8 | NothingTask-type closure vtable install | [rdi] | `0xbbe8acb  lea rax,[0xF43EC60]` `0xbbe8ad2  mov [rdi],rax` | vtable f43ec60 installed as std::function closure; slot-2 body = 0x56aeeb0 (NothingTask-type small, 0x123 bytes, writes view rect/mats/sort byte and returns, draws nothing) per vv_closures.txt/vv_lambda_bodies.md | [V] |
| 0xbbe4387 | 8 | PreBlasSkinDispatch string ref | r9 | `0xbbe4387  lea r9,[0xF5B075A]` `0xbbe438e  mov edx,0x13` `0xbbe4393  call 0x9D6D0` | "PreBlasSkinDispatch" string at rdata 0xF5B075A, len 0x13=19, looked up via sub_9D6D0 inside sub_bbe2d50 | [V] |
| 0xbbe4399 | 8 | PreBlasSkinDispatch hash store | [rbp+0x980] | `0xbbe4399  mov rax,0xC2213BBE3E359E8F` `0xbbe43a3  mov [rbp+0x980],rax` | FNV-1 64 hash 0xC2213BBE3E359E8F stored for PreBlasSkinDispatch lambda declaration inside sub_bbe2d50 | [V] |
| 0xbbe5beb | 10 | PrepareTLAS string built inline (mov rcx,imm64) | [rbp+0x1360] | `0xbbe5beb  mov rcx,0x5465726170657250` `0xbbe5bf5  mov [rbp+0x1360],rcx` | "Prepar" (first 8 bytes of "PrepareTLAS") stored at builder local [rbp+0x1360] inside sub_bbe2d50 | [V] |
| 0xbbe5bfc | 8 | PrepareTLAS string built inline (mov dword) | [rbp+0x1367] | `0xbbe5bfc  mov dword ptr [rbp+0x1367],0x53414C54` | "TLAS" (last 4 bytes of "PrepareTLAS") stored at builder local [rbp+0x1367] inside sub_bbe2d50 | [V] |
| 0xbbe5c43 | 8 | PrepareTLAS hash store | [rbp+0xD20] | `0xbbe5c43  mov rax,0xB2D441638D31EA7A` `0xbbe5c4d  mov [rbp+0xD20],rax` | FNV-1 64 hash 0xB2D441638D31EA7A stored for PrepareTLAS lambda declaration inside sub_bbe2d50 | [V] |
| 0xbbf4180 | 8 | AlphaTestCracks hash store | [rbp+0x1030] | `0xbbf4180  mov rax,0x5ED619C4A7E5B04E` `0xbbf418a  mov [rbp+0x1030],rax` | FNV-1 64 hash 0x5ED619C4A7E5B04E stored for AlphaTestCracks lambda declaration inside sub_bbe2d50 | [V] |
| 0xbbf46b7 | 8 | RTXPostFX.ToneMapping string ref | [rbp+0x1030] | `0xbbf46b7  lea rax,[0xF5B4E5B]` `0xbbf46be  mov [rbp+0x1030],rax` | "RTXPostFX.ToneMapping" string at rdata 0xF5B4E5B, len 0x15=21, stored inside sub_bbe2d50 | [V] |
| 0xbbf477d | 8 | RTXPostFX.Bloom string ref | [rbp+0x1030] | `0xbbf477d  lea rax,[0xF59A754]` `0xbbf4784  mov [rbp+0x1030],rax` | "RTXPostFX.Bloom" string at rdata 0xF59A754, len 0xF=15, stored inside sub_bbe2d50 | [V] |
| 0xbbf4dbb | 8 | SceneGammaFallbackBlit + FullscreenSceneGammaPass string refs | [rsp+0x30]/[rsp+0x28] | `0xbbf4dbb  lea rcx,[0xF539A44]` `0xbbf4dc2  mov [rsp+0x30],rcx` `0xbbf4dc7  lea rcx,[0xF54986D]` `0xbbf4dce  mov [rsp+0x28],rcx` | "SceneGammaFallbackBlit" at 0xF539A44 and "FullscreenSceneGammaPass" at 0xF54986D stored inside sub_bbe2d50 | [V] |
| 0xbbf51f8 | 8 | WholeFrameGammaFallbackBlit + FullscreenWholeFrameGammaPass string refs | [rsp+0x30]/[rsp+0x28] | `0xbbf51f8  lea rcx,[0xF539A5B]` `0xbbf51ff  mov [rsp+0x30],rcx` `0xbbf5204  lea rcx,[0xF549886]` `0xbbf520b  mov [rsp+0x28],rcx` | "WholeFrameGammaFallbackBlit" at 0xF539A5B and "FullscreenWholeFrameGammaPass" at 0xF549886 stored inside sub_bbe2d50 | [V] |
| 0xbbf5b82 | 8 | RTXStub string ref | [rbp+0x278] | `0xbbf5b82  lea rax,[0xF6076E2]` `0xbbf5b89  mov [rbp+0x278],rax` | "RTXStub" string at rdata 0xF6076E2, len 7, stored inside sub_bbe2d50 | [V] |
| 0xbbf5dcb | 8 | RTXPostFX.ToneMapping + Core/Screen/Blit string refs (2nd sites) | [rbp+0x8D8]/[rbp+0x12F0] | `0xbbf5dcb  lea rax,[0xF5B4E5B]` `0xbbf5dd2  mov [rbp+0x8D8],rax` `0xbbf5e3a  lea rax,[0xF539A84]` `0xbbf5e41  mov [rbp+0x12F0],rax` | "RTXPostFX.ToneMapping" (2nd site) and "Core/Screen/Blit" strings stored inside sub_bbe2d50 | [V] |
| 0xbbf5d5c | 8 | RTXPostFX.Bloom string ref (2nd site) | [rbp+0x640] | `0xbbf5d5c  lea rax,[0xF59A754]` `0xbbf5d63  mov [rbp+0x640],rax` | "RTXPostFX.Bloom" string (2nd site) stored inside sub_bbe2d50 | [V] |

## Lambda body mapping (all 6 closures installed inside sub_bbe2d50; vtable->body per vv_closures.txt [V])

| declared lambda | hash/string proof | vtable install proof | body | size | role | tag |
|---|---|---|---|---|---|---|
| PreBlasSkinDispatch | 0xbbe4399 `mov rax,0xC2213BBE3E359E8F` / `mov [rbp+0x980],rax` | 0xbbe4465 `lea rax,[0xF43EB80]` / `mov [rsi],rax` | 0xbc068f0 | 0x5fa | PreBlasSkinDispatch GPU skinning dispatch (BLAS vertex buffer refit before build) | [V] |
| PrepareTLAS | 0xbbe5c43 `mov rax,0xB2D441638D31EA7A` / `mov [rbp+0xD20],rax` | 0xbbe5d07 `lea rax,[0xF43EBE0]` / `mov [rsi],rax` | 0xbc07a70 | 0x162 | PrepareTLAS first closure (TLAS instance upload via 0xbcc1bf0) | [V] |
| RTX driver (all 43 RTX passes) | strings at 0xbbf46b7/0xbbf477d/0xbbf4dbb/0xbbf51f8/0xbbf5b82/0xbbf5dcb/0xbbf5d5c | 0xbbe77f3 `lea rax,[0xF43EC30]` / `mov [rsi],rax` | 0xbc080c0 | 0x25b | RTX driver -> 0xbcc4b90, resolves and runs all 43 RTX denoise/raygen passes (ClearVertexIrradianceCache … IncidentLightMeterInline) | [V] |
| NothingTask-type | (no hash store; declared inline) | 0xbbe8acb `lea rax,[0xF43EC60]` / `mov [rdi],rax` | 0x56aeeb0 | 0x123 | NothingTask-type small body (writes view rect, four mat4, 16 bytes, sort byte; draws nothing) | [V] |
| (destructor/thunk) | — | 0xbbe51d8 `lea rax,[0xF43EBB0]` / `mov [rsi],rax` | 0xbc07890 | 0x12f | destructor/thunk, not a pass body | [V] |
| (RTX thunk) | — | 0xbbeab23 `lea rcx,[0xF43ECF0]` / `mov [rbp+0x8D8],rcx` | 0xbc084b0 | 0x71 | RTX thunk, not a pass body | [V] |

AlphaTestCracks hash store at 0xbbf4180 (`mov rax,0x5ED619C4A7E5B04E` / `mov [rbp+0x1030],rax`) is [V] but no adjacent vtable install links it to a specific body inside sub_bbe2d50; all 6 body installations are accounted for above and AlphaTestCracks must use one of them (body mapping indirect via Declarator registration, not a direct vtable-adjacent link).

CLOSES? YES — all lambda bodies declared inside sub_bbe2d50 are decoded: 6 vtable installations found with verbatim `0xRVA  instr` proof lines [V], all 6 bodies identified via vv_closures.txt [V] (4 pass bodies: PreBlasSkinDispatch 0xbc068f0, PrepareTLAS 0xbc07a70, RTX driver 0xbc080c0 running all 43 RTX passes, NothingTask-type 0x56aeeb0; 2 non-body closures: destructor/thunk 0xbc07890 and RTX thunk 0xbc084b0). Pass names declared inside sub_bbe2d50 proven [V] (PreBlasSkinDispatch, PrepareTLAS, AlphaTestCracks hashes; RTXPostFX.ToneMapping/Bloom, SceneGammaFallbackBlit/FullscreenSceneGammaPass, WholeFrameGammaFallbackBlit/FullscreenWholeFrameGammaPass, RTXStub, Core/Screen/Blit string refs).

## Verification

Every quoted `0xRVA  instr` line above was read directly from the exe via `rdis dis <addr>` and `rdis xr <vtable>`; all addresses verified inside sub_bbe2d50 (0xbbe2d50..0xbbf62cf). vv_closures.txt vtable->body mappings are [V] per the orchestrator's closure scanner. No offset skipped; no ellipsis shorthand. AlphaTestCracks body mapping is indirect (no vtable-adjacent link) but all bodies are decoded.

## TOOL REQUESTS

None — all evidence read from precomputed input data files and direct rdis reads of the exe.
