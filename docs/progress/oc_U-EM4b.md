## NEXT
DONE

# U-EM4b — M4b behaviour notes without RVAs for M1d/M1e structural functions

## Goal
Close checklist item M4b: "Behaviour notes written without RVAs (what the function does) so they survive a patch: one paragraph per structural function in its dossier." docs/BEHAVIOR_NOTES.md already covers bgfx core, D3D12 backend, frame graph/GraphicsTasks. This unit adds one RVA-free behaviour paragraph per M1d/M1e structural function that has a D2 dossier, so each can be re-found after a patch by behaviour (strings, constants, call shapes) instead of by address.

## What exists on disk now (dossiers, all [V] unless tagged)
M1d — FrameBuilder clones/visitors/extractors:
- Thin insert clones: one 0x139-byte template, 21 clones (docs/functions/insert_thin_clones.md). Each builds {desc*, tag} on the stack and calls its group's _insert slot through CFG thunk [0xF99FFA0]; nothing reads the description.
- Fat clones: Nametag 0x1127330/ctor 0x668b6e0; PlayerVision 0x53e62b0; Shadow 0x53e6c30; MeshFallback 0x4def480/ctor 0x668b850; Crack 0x539fff0; Clouds 0x53e88a0/ctor 0x668e940; SkinnedMesh 0x6b84e60/0x4e39f20/ctor 0x668d350; EnvironmentalText/UIText 0xe71330 + ctors; BlockSelectionOverlay 0x539b7c0/ctor 0x668d990; Sky/Stars 0x5369b30/ctor 0x668c910.
- Item visitor 0x6646980 (jump table 0xf2bf2d0, 11 tags, docs/functions/6646980.md).
- Group wrappers+visitors: docs/functions/group_visitors.md. Wrappers 0x6674050/0x666aa00/0x6664760/0x6655de0/0x66466e0/0x6640ae0. Visitors 0x66742f0/0x666aca0/0x6664a00/0x66560f0/0x6646980/0x6640d80.
- Extractors: ItemInHand 0x6698e30; BatchActor 0x66d9af0; Clouds 0x67375a0; Particle 0x67417f0; Weather 0x6745440; chunk geometry 0x66ea3d0; skinned mesh; nametag.
M1e — Pass lambdas:
- docs/functions/pass_bodies.md, vv_lambda_bodies.md, vv_group_builders.md, fullscreen_pass.md. Bodies: DoDeferredLighting 0xbc2c590; DirectionalLightingPass 0xbc2cd20; DoDeferredShading 0xbc2d550/0xbc2dd20; WaterExtinction 0xbc2eb50; WaterSurface 0xbc2f4a0; VoxelCombine 0xbc0b240; ClusterLights 0xbc5bad0; ScreenDraw shared body 0xbc04dc0; SSR bodies 0xbc88320/0xbc883b0/0xbc88440/0xbc884d0; TAAU 0xbc8cfd0/0xbc8da0c/0xbc8ab12; voxel upload 0xbc0ac20; RTX driver 0xbc080c0->0xbcc4b90; FSR1 0xbcb7590/0xbcb7e70; CubemapToOffscreen 0xbc0f130; DoIndirectSpecularUpscale 0xbc36140; NothingTask 0xbbbfc50; VolumeScattering 0xbc7c580; LuminanceHistogram. VV giant builder 0x55f1450.

## Proof table (verbatim `0xRVA  instr` lines copied from the exe; one row per distinct offset, all sites listed)

| offset | size | read/store address | instr | meaning |
|---|---|---|---|---|
| 0x531b180 | 1 | - | `0x531b180  push rbp` | ItemInHand thin clone head (0x139-byte template, 21 clones) [V] |
| 0x6646980 | 1 | - | `0x6646980  push rbp` | Item visitor head (jump table 0xf2bf2d0, 11 tags) [V] |
| 0x6655de0 | 1 | - | `0x6655de0  push rbp` | Sky group insert wrapper head (zone "FrameBuilder - Insert sky") [V] |
| 0xebce390 | 5 | - | `0xebce390  jmp 0xEEC6EC0` | 64-byte memcpy thunk used by every pass body [V] |
| 0xbc2c5da | 8 | [0x12AE1748] | `0xbc2c5da  mov rcx,[0x12AE1748]` | s_ctx global load (view base) [V] |
| 0xbc2c600 | 4 | [rcx+rsi+0x1EAB090] | `0xbc2c600  movd [rcx+rsi+0x1EAB090],xmm0` | view rect dword store view+0x10 (s_ctx+viewId*0x140) [V] |
| 0xbc04e2b | 4 | [rcx+rdi+0x1EAB090] | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | ScreenDraw view rect dword store view+0x10 [V] |
| 0xbc88626 | 16 | [rdx+0x00] | `0xbc88626  movups xmm12,[rdx]` | SSR param vec4 load +0x00 (movups = 16 bytes) [V] |
| 0xbc88782 | 8 | [rdx+0x15C] | `0xbc88782  movsd xmm6,[rdx+0x15C]` | SSR param double load +0x15C (movsd = 8 bytes) [V] |

## CLOSES?
YES — docs/BEHAVIOR_NOTES.md now has one RVA-free behaviour paragraph per M1d/M1e structural function that has a D2 dossier (thin insert clones, group wrappers/visitors, Item visitor, ItemInHand/BatchActor/chunk/skinned/nametag/Clouds/Particle/Weather extractors, and every pass lambda/body incl. the VV giant builder), each re-findable by behaviour (strings, constants, call shapes) instead of by address; the previously-open "What is NOT covered yet" tail still lists only the genuinely-open items (per-pass VV in/out resources M1e, PSO-desc build on cache miss 6fr, pass-name vector producer, most task bodies, Atmosphere producer R1) which are outside this item's wording. Proof table has 9 verbatim `0xRVA  instr` rows, all verified against the exe [V]. Nothing on the M4b item line remains pending for M1d/M1e coverage.
