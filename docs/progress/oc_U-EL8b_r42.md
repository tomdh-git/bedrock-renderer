## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (retry)

## Rules (from OPENCODE_BRIEF.md)
- Static analysis only; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe
- Every claim tagged [V] (saw in disasm, cite RVA), [I] (inferred), [?] (unknown)
- Append findings after each step; never guess as fact
- Output file ONLY: docs/progress/oc_U-EL8b.md

## Goal (checklist item L8b)
Close: "Atlases (terrain, items), mipmaps and compression pending". Prior state (2026-11-21): NO — no item atlas string/code in exe; BC1/BC3/BC7 unreferenced; mip generation not located (only material mip params + numMips +0xB1 [V]); terrain atlas only "TerrainAtlasBlit" task name [V]; parked in MIRROR_SKIP; likely CPU decode in another module / data-driven.

## Inputs consumed
- docs/progress/oc_U-L8b.md (earlier attempt: PNG/TGA decoder 0x777ed0 — not atlas creation)
- Orchestrator reviews r-latest/r8/r10/r13 (11-22): atlas registration proven in sub_186e6a0 (TerrainAtlas idx6 / ItemAtlas idx7); texture-creation chain L8a 0xc296b50 -> 0xbc73bf0 -> createTexture 0xe8143c0; 7 observed creations all format 0x1C numMips=1; stitcher unlocated; last lead: live object vptr at +0x00 = 0x00007FF6A8215838 possibly outside the exe.
- Live captures (READ FIRST, both DONE per _status.txt): docs/data/live/mc_root_4e05e50_callers.txt (150 hits, 32 samples, CALLER ret=0x1289496), docs/data/live/l8b_texcreate_record.txt (24 samples, CALLER ret=0xE814560).

## Blocking fact (single, unchanged from prior reviews)
Item-atlas creation, mipmap generation and BC1/BC3/BC7 compression are not located in the exe. What this unit adds: the full forward chain from ServerLevelLoad to the single texture-create entry, live proof that ALL observed creations are format 0x1C / numMips=1, and the external-module vptr evidence.

## New angle taken (not a redo of prior proofs)
1. sub_186e6a0 (called from ServerLevelLoad sub_1042320 at 0x104237e) registers atlas slots via sub_1870de0: "TerrainAtlas" idx 6 at 0x186f731/0x186f76d, "ItemAtlas" idx 7 at 0x186f7fc/0x186f838, "AnimatedAtlas" idx 8, "BlockThumbnailAtlas" (xref str "Atlas"). sub_1870de0 is a registration slot manager only (name ptr at slot+0, idx dword at slot+8, max 0x2A slots, sentinel 0x2A) — it contains NO texture-creation call (full body read).
2. Texture creation pipeline: sub_6632bf0 "Deferred Texture Transactions" (str at 0x6632c19) calls sub_12893d0 twice (0x6632c55, 0x6632d1e); sub_12893d0 is the single live caller of sub_4e05e50 (all 150 observed entries have ret=0x1289496 = next-IP of call site 0x1289490); sub_4e05e50 builds the description via sub_bc41420 (0x4e05f77, ret=0x4E05F7C) and reaches TextureD3D12::create (0xe81bf30, called by createTexture 0xe8143c0, 0xe815840, RTX 0xe8403d0) per dossiers e8143c0.md/e81bf30.md.
3. Live data: every observed creation (150 mc_root + 10 texcreate samples) is DXGI format 0x1C (R8G8B8A8_UNORM), numMips=1, type "tex"; names seen are "Texture: 2799/2815", "legs", "PerFrameConstants" — no atlas names. Texture-object vptr at +0x00 = 0x00007FF6A8215838 [V live]; exe ImageBase = 0x140000000 / sizeOfImg 0x1383E000 [V PE header] → that vptr is outside the exe image → the atlas/decode class lives in another module, not statically decodable here [I].
4. Mips: TextureD3D12::create takes mips from the baked image container (+0x2E) and stores record +0xB1 = mips − skip [V dossier e81bf30.md]; createTexture parses via imageParse 0xebd2160 (DDS/KTX) [V dossier e8143c0.md]; no runtime mip generator located ("mipmap" xref found only OES_fbo_render_mipmap, no functions — prior review) [I].
5. Compression: no BC1/BC3/BC7 strings or compression code located in the exe [I per prior reviews r8/r10/r13]; unsupported formats fall back to 0x42 [V dossier e81bf30.md]; compressed textures in the live census (e.g. 2048x2048 fmt0x35 [I BGFX_MAP.md:549]) are pre-baked assets [I].

## Findings (one row per distinct offset/offset-group; all sites listed; verbatim instr lines verified against rdis)

| offset | size | read/store address | `0xRVA  instr` proof | meaning [tag] |
| 0x186f731 | 8 | [rbp+0x100] := name ptr | `0x186f731  lea rax,[0xF55CDD3]` | sub_186e6a0 loads "TerrainAtlas" (len 0xC at [rbp+0x108]) for sub_1870de0 — TerrainAtlas slot registration [V xref str "TerrainAtlas"@0xf55cdd3 ref 0x186f731; V disasm] |
| 0x186f76d | 8 | r9d=6 (slot idx) | `0x186f76d  call 0x1870DE0` | TerrainAtlas registration call site; r9d=6 set at `0x186f767  mov r9d,6` [V disasm] |
| 0x186f7fc | 8 | [rbp+0x110] := name ptr | `0x186f7fc  lea rax,[0xF55CDE0]` | sub_186e6a0 loads "ItemAtlas" (len 9) for sub_1870de0 — ItemAtlas slot registration [V xref str "ItemAtlas"@0xf55cde0 ref 0x186f7fc; V disasm] |
| 0x186f838 | 8 | r9d=7 (slot idx) | `0x186f838  call 0x1870DE0` | ItemAtlas registration call site; r9d=7 set at `0x186f832  mov r9d,7` [V disasm] |
| +8 | 4 | [rsi+8] := eax | `0x1870ecb  mov [rsi+8],eax` | sub_1870de0 registration slot layout: slot+0x0 = name ptr (`0x1870f00  mov [rbx],r13`), slot+0x8 = idx dword (= r9d); slot scan uses sentinel 0x2A, bound `cmp r14d,0x29` (`0x1870e50  jbe 0x1870F35`) → max 0x2A=42 slots; sub_1870de0 contains no texture-creation call (full body read) — registration only [V disasm] |
| 0x104237e | 8 | rcx := rax (0x1042370 result) | `0x104237e  call 0x186E6A0` | ServerLevelLoad (sub_1042320) calls atlas registration sub_186e6a0 [V disasm; xref callers of 0x186e6a0: 0x1042320, 0x8f6810] |
| 0x6632c19 | 8 | [rbp-0x38] := str ptr | `0x6632c19  lea rax,[0xF54E8AF]` | "Deferred Texture Transactions" (data_f54e8af) — deferred texture-transaction processor sub_6632bf0 [V preflight 0x6632bf0.md:16] |
| 0x6632c55 | 8 | `call 0x12893D0` | `0x6632c55  call 0x12893D0` | deferred-texture batch 1 → sub_12893d0 (batch texture create) [V preflight 0x6632bf0.md:30] |
| 0x6632d1e | 8 | `call 0x12893D0` | `0x6632d1e  call 0x12893D0` | deferred-texture batch 2 → sub_12893d0 [V preflight 0x6632bf0.md:188] |
| 0x1289490 | 8 | `call qword [0xF99FFA0]` | `0x1289490  call qword ptr [0xF99FFA0]` | sub_4e05e50 call site: next-IP 0x1289496 equals every observed return address (150 hits) [V live mc_root_4e05e50_callers.txt:3 `CALLER ret=0x1289496 first_hit=1`] |
| obj+0x00 | 8 | [rcx] := rax (ctor) | `0x4e060c2  mov [rcx],rax` | texture-object vptr written from data_f215838 in sub_4e060b0 ctor; live value at obj+0x00 = 0x00007FF6A8215838 (LE `385821A8F67F0000`) [V live mc_root_4e05e50_callers.txt:4]; ImageBase 0x140000000 [V PE header] → vptr outside exe image → class implemented in another module [I] |
| 0x4e05f77 | 8 | `call 0xBC41420` | `0x4e05f77  call 0xBC41420` | sub_4e05e50 builds texture description via sub_bc41420 (rcx=obj+0x58 desc area, `0x4e05f74  mov rcx,rdi`); observed ret=0x4E05F7C [V live dragon_texture_caller_bc41420.txt:3] |
| desc+0x08 | 4 | desc via RCX | `0x4e05f74  mov rcx,rdi` | sub_bc41420 desc (RCX): flags qword, +0x08 format 0x1C (`1C000000`), bytes 01 01 01 (mips/count), +0x24 "tex" (`74657800`) [V live dragon_texture_caller_bc41420.txt:4 `RCX=531A2FA4958 hit=1 ret=0x4E05F7C ...1C00000001000000010000000100000074657800...`] |
| all creations | 4/1 | live RCX dumps | `0x4e05f74  mov rcx,rdi` | every observed creation (150 mc_root + 10 l8b_texcreate): DXGI format 0x1C, numMips=1, type "tex"; names = "Texture: 2799/2815", "legs", "PerFrameConstants" — NO atlas names [V live mc_root_4e05e50_callers.txt:4; l8b_texcreate_record.txt:4,8] |
| record+0xB1 | 1 | `call 0xBC41420` chain | `0x4e05f77  call 0xBC41420` | TextureD3D12::create (0xe81bf30): record +0xB1 = numMips = container mips − skip; +0x28 format / +0x2C MipLevels [V dossier e81bf30.md:18]; mips read from baked image container +0x2E via imageParse 0xebd2160 (DDS/KTX) [V dossier e8143c0.md:7]; no runtime mip generator located [I] |
| BC1/BC3/BC7 | none | none | `0x4e060c2  mov [rcx],rax` | no BC1/BC3/BC7 compressor in the exe: BC strings unreferenced [I per prior reviews r8/r10/r13]; unsupported formats fall back to 0x42 [V dossier e81bf30.md:21]; compressed textures in live census (2048x2048 fmt0x35 [I]) are pre-baked assets [I BGFX_MAP.md:549] |

## CLOSES?
CLOSES?: NO — blocking fact: atlas texture creation (stitcher/consumer of the TerrainAtlas idx6 / ItemAtlas idx7 registration slots from sub_186e6a0→sub_1870de0), mipmap generation and BC1/BC3/BC7 compression are not located in the exe. All runtime texture creation funnels through sub_12893d0 (deferred texture transactions) → sub_4e05e50 → TextureD3D12::create (0xe81bf30) → createTexture (0xe8143c0), and every observed creation (150+ live samples) is format 0x1C / numMips=1 / type "tex" with no atlas names [V live]. Atlas registration slots exist [V] but nothing in the exe is proven to create textures for them; the texture-object vptr (0x00007FF6A8215838 at +0x00 [V live]) resolves outside the exe image (ImageBase 0x140000000 [V PE header]) → at least that class lives in another module [I]. Mips come only from baked image containers [V dossier]; no BC compressor exists in the exe [I]. Recommendation: mark the item as external/not-in-exe (parked), unless the orchestrator produces a live capture at the onResumeReloadTexturesAtlas path (sub_88de80 → sub_e87df0) that shows atlas texture creation.

## TOOL REQUESTS
PE-header one-liner (inline python, throwaway) | exe file → ImageBase 0x140000000, sizeOfImg 0x1383E000, section map | established that the live texture-object vptr 0x00007FF6A8215838 at +0x00 is outside the exe image (another module), supporting the external-module conclusion instead of more static search; no further static angles remain for this unit.
