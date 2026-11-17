## NEXT
DONE

# U-EG4b — VV/RTX render targets (static census)

Item: `G4b Live texture census + record layout (Fancy) — 6z-2; VV/RTX RTs pending`.
Fancy live census and the record layout (+0x00..+0xB1) are already closed (`docs/progress/materials-visuals.md`, BGFX_MAP 6z-2/6im). This note closes only the pending part: the VV/RTX render-target set, which cannot be captured live in a Fancy session.

## Method (all [V])

- `0x5698290` is the frame-graph texture-target declarator: allocates a 0x28-byte node (vtable 0xF25C820), copies a 0x1C-byte descriptor from `r8` into node+8 (`movups` x2), pushes the node and appends a 0x50-byte pass record. Every call declares one texture target.
- Descriptor fields used here: `+0x00` u16 width, `+0x02` u16 height, `+0x04` u32 format (D3D12 format id). Proven by construction in `0xbb78240` (desc @rbp+0xD28, width `[rsi]` at +0, height `[rsi+4]` at +2, format store at +4) and consumption in `0xe81bf30` where the descriptor format becomes `D3D12_RESOURCE_DESC.Format` (rec +0x28) through the 0x10-byte format table at `0xF4ED700` (`0xe81c1ca  lea rdi,[0xF4ED700]`, `0xe81c2a9  shl eax,4`, `0xe81c2ac  mov ecx,[rax+rdi]`, `0xe81c2b3  mov [r13+0x28],ecx`).
- Coverage: all 55 call sites of `0x5698290` (`xr 0x5698290`) are accounted for by the 46 rows below (sites listed per row; 9 rows aggregate 2-3 sites each). 5 rows are re-declarations of a caller-supplied descriptor (aliases), so they add no new allocation.
- Size column = 4 for every row: the format field is a dword store/read.
- D3D12 numeric ids seen (interpretation, not part of the claim): 0x1A R11G11B10_FLOAT, 0x1C R8G8B8A8_UNORM, 0x22 R16G16_FLOAT, 0x28 D32_FLOAT, 0x29 R32_FLOAT, 0x2D D24_UNORM_S8_UINT, 0x36 R16_FLOAT, 0x0A R16G16B16A16_FLOAT, 0x0B R16G16B16A16_UNORM, 0x0C R16G16B16A16_UINT, 0x02 R32G32B32A32_FLOAT [I].

## Answer table

| target (builder / descriptor) | rva (format store) | size | proof | meaning | tag |
|---|---|---|---|---|---|
| VV frame graph 0x55f1450 @rbp+0x2C00 fmt 0x2D | 0x55f1fa5 | 4 | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | desc +4 = 0x2D; declare call 0x55f1fca | [V] |
| VV frame graph 0x55f1450 @rbp+0x27A0 caller desc (alias) | 0x55f1f7d | 4 | `0x55f1f7d  mov eax,[rbp+0x27A4]` | format copied from caller desc +4; declare call 0x55f1fe7; not a new RT | [V] |
| VV frame graph 0x55f1450 @rbp+0x1EF4 fmt 0x1A | 0x55ff22a | 4 | `0x55ff22a  mov dword ptr [rbp+0x1EF8],0x1A` | desc +4 = 0x1A; declare calls 0x55ff2c5, 0x562cc0a | [V] |
| VV frame graph 0x55f1450 @rbp+0x1C40 fmt 0x2D | 0x55ff2a0 | 4 | `0x55ff2a0  mov dword ptr [rbp+0x1C44],0x2D` | desc +4 = 0x2D; declare calls 0x55ff2f8, 0x55ff31d, 0x5625585 | [V] |
| VV frame graph 0x55f1450 @rbp+0x2440 fmt 0x29 (a) | 0x560b6a3 | 4 | `0x560b6a3  mov dword ptr [rbp+0x2444],0x29` | desc +4 = 0x29; declare call 0x560b6be | [V] |
| VV frame graph 0x55f1450 @rbp+0x1EA0 fmt 0x29 | 0x560bcf2 | 4 | `0x560bcf2  mov dword ptr [rbp+0x1EA4],0x29` | desc +4 = 0x29; declare call 0x560bd0d | [V] |
| VV frame graph 0x55f1450 @rbp+0x2440 fmt 0x29 (b) | 0x56119fd | 4 | `0x56119fd  mov dword ptr [rbp+0x2444],0x29` | desc +4 = 0x29; declare call 0x5611a18 | [V] |
| VV frame graph 0x55f1450 @rbp+0x2C00 fmt 0x1A | 0x562e4c8 | 4 | `0x562e4c8  mov dword ptr [rbp+0x2C04],0x1A` | desc +4 = 0x1A; declare call 0x562e4e3 | [V] |
| VV frame graph 0x55f1450 @rbp+0x25F0 fmt 0x1C | 0x562e646 | 4 | `0x562e646  mov dword ptr [rbp+0x25F4],0x1C` | desc +4 = 0x1C; declare call 0x562e661 | [V] |
| VV frame graph 0x55f1450 @rbp+0x2440 fmt 0x1C (a) | 0x5632803 | 4 | `0x5632803  mov dword ptr [rbp+0x2444],0x1C` | desc +4 = 0x1C; declare call 0x563281e | [V] |
| VV frame graph 0x55f1450 @rbp+0x2440 fmt 0x1C (b) | 0x5632ae9 | 4 | `0x5632ae9  mov dword ptr [rbp+0x2444],0x1C` | desc +4 = 0x1C; declare call 0x5632b0e | [V] |
| VV frame graph 0x55f1450 @rbp+0x2C00 fmt 0x1C | 0x563333e | 4 | `0x563333e  mov dword ptr [rbp+0x2C04],0x1C` | desc +4 = 0x1C; declare call 0x5633359 | [V] |
| Color0/1/2 builder 0x5667fe0 @rbp-0x18 fmt 0x1C | 0x56680a4 | 4 | `0x56680a4  mov dword ptr [rbp-0x14],0x1C` | desc +4 = 0x1C; Color0 string 0x566816f; declare call 0x56680b5 | [V] |
| Color0/1/2 builder 0x5667fe0 @rbp-0x60 fmt 0x0A | 0x56680d4 | 4 | `0x56680d4  mov dword ptr [rbp-0x5C],0xA` | desc +4 = 0x0A; Color1 string 0x56681d2; declare call 0x56680e5 | [V] |
| Color0/1/2 builder 0x5667fe0 @rbp-0x40 fmt 0x0C | 0x5668104 | 4 | `0x5668104  mov dword ptr [rbp-0x3C],0xC` | desc +4 = 0x0C; Color2 string 0x5668235; declare call 0x5668115 | [V] |
| Sky probe builder 0x56a06a0 @rbp+0xCFC fmt 0x28 | 0x56a0f31 | 4 | `0x56a0f31  mov dword ptr [rbp+0xD00],0x28` | desc +4 = 0x28; declare call 0x56a0f4c | [V] |
| ClearDiffuseLightingBuffers 0xbb43a90 @rbp+0x214 fmt 0x1A | 0xbb43b06 | 4 | `0xbb43b06  mov dword ptr [rbp+0x218],0x1A` | desc +4 = 0x1A; declare calls 0xbb43b8f, 0xbb43bab | [V] |
| ClearDiffuseLightingBuffers 0xbb43a90 @rbp-0x50 fmt 0x0B | 0xbb43bd0 | 4 | `0xbb43bd0  mov dword ptr [rbp-0x4C],0xB` | desc +4 = 0x0B; declare call 0xbb43be8 | [V] |
| BlitHDR 0xbb487c0 @rbp+0xC34 fmt 0x02 | 0xbb488f8 | 4 | `0xbb488f8  mov dword ptr [rbp+0xC38],2` | desc +4 = 2; BlitHDR string 0xbb4882f; declare call 0xbb48963 | [V] |
| DeferredLighting 0xbb6b350 @rbp+0x3AC fmt 0x36 | 0xbb6b617 | 4 | `0xbb6b617  mov dword ptr [rbp+0x3B0],0x36` | desc +4 = 0x36; declare call 0xbb6b653 | [V] |
| DepthAndNormal 0xbb78240 @rbp+0xD28 fmt 0x22 | 0xbb78325 | 4 | `0xbb78325  mov dword ptr [rbp+0xD2C],0x22` | desc +4 = 0x22; declare call 0xbb7834a | [V] |
| DepthAndNormal 0xbb78240 @rbp+0xD48 fmt 0x28 | 0xbb783c1 | 4 | `0xbb783c1  mov dword ptr [rbp+0xD4C],0x28` | desc +4 = 0x28; declare call 0xbb783e6 | [V] |
| Forward 0xbb84ee0 @rbp+0x1204 fmt 0x1C | 0xbb85003 | 4 | `0xbb85003  mov dword ptr [rbp+0x1208],0x1C` | desc +4 = 0x1C; declare call 0xbb850bd | [V] |
| Forward 0xbb84ee0 @rbp+0x11E8 fmt 0x2D | 0xbb85050 | 4 | `0xbb85050  mov dword ptr [rbp+0x11EC],0x2D` | desc +4 = 0x2D; declare call 0xbb850eb | [V] |
| declare-helper 0xbb93760 @rsp+0x20 fmt 0x2D | 0xbb93800 | 4 | `0xbb93800  mov dword ptr [rsp+0x24],0x2D` | desc +4 = 0x2D; declare call 0xbb9381b | [V] |
| declare-helper 0xbb93760 @rsp+0x3C caller desc (alias) | 0xbb937c4 | 4 | `0xbb937c4  mov [rsp+0x40],ecx` | format = caller ecx ([r8+0x18]); declare call 0xbb9382e; not a new RT | [V] |
| declare-helper 0xbb93890 @rsp+0x20 fmt 0x2D | 0xbb9392c | 4 | `0xbb9392c  mov dword ptr [rsp+0x24],0x2D` | desc +4 = 0x2D; declare call 0xbb93947 | [V] |
| declare-helper 0xbb93890 @rsp+0x3C caller desc (alias) | 0xbb938ef | 4 | `0xbb938ef  mov [rsp+0x40],r8d` | format = caller r8d; declare call 0xbb9395a; not a new RT | [V] |
| declare-helper 0xbb939c0 @rbp-0x50 fmt 0x2D | 0xbb93a86 | 4 | `0xbb93a86  mov dword ptr [rbp-0x4C],0x2D` | desc +4 = 0x2D; declare call 0xbb93a9e | [V] |
| declare-helper 0xbb939c0 @rbp-0x30 fmt 0x1C | 0xbb93a4b | 4 | `0xbb93a4b  mov dword ptr [rbp-0x2C],0x1C` | desc +4 = 0x1C; declare call 0xbb93ab0 | [V] |
| NothingTask 0xbbbfc50 @rbp+0x980 fmt 0x2D | 0xbbc3138 | 4 | `0xbbc3138  mov dword ptr [rbp+0x984],0x2D` | desc +4 = 0x2D; declare calls 0xbbc3159, 0xbbc316f, 0xbbc4372 | [V] |
| NothingTask 0xbbbfc50 @rbp+0xDF0 caller desc (alias) | 0xbbc42f9 | 4 | `0xbbc42f9  mov [rbp+0xDF4],ecx` | format = caller ecx; declare call 0xbbc438c; not a new RT | [V] |
| FullscreenSceneGammaPass 0xbbd25f0 @rbp+0x640 fmt 0x2D | 0xbbd27e9 | 4 | `0xbbd27e9  mov dword ptr [rbp+0x644],0x2D` | desc +4 = 0x2D; declare call 0xbbd280a | [V] |
| FullscreenSceneGammaPass 0xbbd25f0 @rbp+0x4D0 fmt 0x1C | 0xbbd2787 | 4 | `0xbbd2787  mov dword ptr [rbp+0x4D4],0x1C` | desc +4 = 0x1C; declare calls 0xbbd281f, 0xbbd2ad0, 0xbbd2b09 | [V] |
| RTX prep 0xbbe2d50 @rbp+0xD80 fmt 0x2D | 0xbbe3fbc | 4 | `0xbbe3fbc  mov dword ptr [rbp+0xD84],0x2D` | desc +4 = 0x2D; declare call 0xbbe3fe1 | [V] |
| RTX prep 0xbbe2d50 @rbp+0xA10 fmt 0x1C | 0xbbe3f5a | 4 | `0xbbe3f5a  mov dword ptr [rbp+0xA14],0x1C` | desc +4 = 0x1C; declare call 0xbbe3ffb | [V] |
| RTX prep 0xbbe2d50 @rbp+0x7B4 fmt 0x1C | 0xbbe41bd | 4 | `0xbbe41bd  mov dword ptr [rbp+0x7B8],0x1C` | desc +4 = 0x1C; declare call 0xbbe4244 | [V] |
| RTX prep 0xbbe2d50 @rbp+0x410 fmt 0x2D | 0xbbe421f | 4 | `0xbbe421f  mov dword ptr [rbp+0x414],0x2D` | desc +4 = 0x2D; declare call 0xbbe4277 | [V] |
| builder 0xbc55100 @rbp-0x28 fmt 0x1A | 0xbc55313 | 4 | `0xbc55313  mov dword ptr [rbp-0x24],0x1A` | desc +4 = 0x1A; declare call 0xbc55336 | [V] |
| MinMax 0xbc7f6e0 @rbp+0x214 fmt 0x22 | 0xbc7fa89 | 4 | `0xbc7fa89  mov dword ptr [rbp+0x218],0x22` | desc +4 = 0x22; declare call 0xbc7fad7 | [V] |
| SSR 0xbc82ad0 @rbp+0x484 fmt 0x0A | 0xbc833f3 | 4 | `0xbc833f3  mov dword ptr [rbp+0x488],0xA` | desc +4 = 0x0A; declare calls 0xbc83433, 0xbc83466 | [V] |
| local exposure 0xbc9d7a0 @rbp+0x7AC fmt 0x36 | 0xbca0913 | 4 | `0xbca0913  mov dword ptr [rbp+0x7B0],0x36` | desc +4 = 0x36; declare call 0xbca092a | [V] |
| local exposure 0xbc9d7a0 @rbp+0x97C fmt 0x1A | 0xbca0987 | 4 | `0xbca0987  mov dword ptr [rbp+0x980],0x1A` | desc +4 = 0x1A; declare call 0xbca09ac | [V] |
| FSR1 0xbcb64f0 @rbp-0x50 fmt 0x1C | 0xbcb65c4 | 4 | `0xbcb65c4  mov dword ptr [rbp-0x4C],0x1C` | desc +4 = 0x1C; declare call 0xbcb65e0 | [V] |
| CubemapToOffscreen 0xbcd77b0 @rbp+0xD3C caller desc (alias) | 0xbcd7b57 | 4 | `0xbcd7b57  mov [rbp+0xD40],eax` | format = eax from [rbp+0xF80]; declare call 0xbcd7b99; not a new RT | [V] |
| Bloom (post, non-VV) 0xe7ec1f0 @rbp+0x114 fmt 0x0A | 0xe7ec339 | 4 | `0xe7ec339  mov dword ptr [rbp+0x118],0xA` | desc +4 = 0x0A; BloomDownscaleGaussianPass string 0xf5497a0; declare call 0xe7ec471 | [V] |

## Verbatim proof lines

0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D
0x55f1f7d  mov eax,[rbp+0x27A4]
0x55ff22a  mov dword ptr [rbp+0x1EF8],0x1A
0x55ff2a0  mov dword ptr [rbp+0x1C44],0x2D
0x560b6a3  mov dword ptr [rbp+0x2444],0x29
0x560bcf2  mov dword ptr [rbp+0x1EA4],0x29
0x56119fd  mov dword ptr [rbp+0x2444],0x29
0x562e4c8  mov dword ptr [rbp+0x2C04],0x1A
0x562e646  mov dword ptr [rbp+0x25F4],0x1C
0x5632803  mov dword ptr [rbp+0x2444],0x1C
0x5632ae9  mov dword ptr [rbp+0x2444],0x1C
0x563333e  mov dword ptr [rbp+0x2C04],0x1C
0x56680a4  mov dword ptr [rbp-0x14],0x1C
0x56680d4  mov dword ptr [rbp-0x5C],0xA
0x5668104  mov dword ptr [rbp-0x3C],0xC
0x56a0f31  mov dword ptr [rbp+0xD00],0x28
0xbb43b06  mov dword ptr [rbp+0x218],0x1A
0xbb43bd0  mov dword ptr [rbp-0x4C],0xB
0xbb488f8  mov dword ptr [rbp+0xC38],2
0xbb6b617  mov dword ptr [rbp+0x3B0],0x36
0xbb78325  mov dword ptr [rbp+0xD2C],0x22
0xbb783c1  mov dword ptr [rbp+0xD4C],0x28
0xbb85003  mov dword ptr [rbp+0x1208],0x1C
0xbb85050  mov dword ptr [rbp+0x11EC],0x2D
0xbb93800  mov dword ptr [rsp+0x24],0x2D
0xbb937c4  mov [rsp+0x40],ecx
0xbb9392c  mov dword ptr [rsp+0x24],0x2D
0xbb938ef  mov [rsp+0x40],r8d
0xbb93a86  mov dword ptr [rbp-0x4C],0x2D
0xbb93a4b  mov dword ptr [rbp-0x2C],0x1C
0xbbc3138  mov dword ptr [rbp+0x984],0x2D
0xbbc42f9  mov [rbp+0xDF4],ecx
0xbbd27e9  mov dword ptr [rbp+0x644],0x2D
0xbbd2787  mov dword ptr [rbp+0x4D4],0x1C
0xbbe3fbc  mov dword ptr [rbp+0xD84],0x2D
0xbbe3f5a  mov dword ptr [rbp+0xA14],0x1C
0xbbe41bd  mov dword ptr [rbp+0x7B8],0x1C
0xbbe421f  mov dword ptr [rbp+0x414],0x2D
0xbc55313  mov dword ptr [rbp-0x24],0x1A
0xbc7fa89  mov dword ptr [rbp+0x218],0x22
0xbc833f3  mov dword ptr [rbp+0x488],0xA
0xbca0913  mov dword ptr [rbp+0x7B0],0x36
0xbca0987  mov dword ptr [rbp+0x980],0x1A
0xbcb65c4  mov dword ptr [rbp-0x4C],0x1C
0xbcd7b57  mov [rbp+0xD40],eax
0xe7ec339  mov dword ptr [rbp+0x118],0xA

## Coverage check

- 46 rows, 55 declarator call sites: 15 (0x55f1450) + 3 (0x5667fe0) + 1 (0x56a06a0) + 3 (0xbb43a90) + 1 (0xbb487c0) + 1 (0xbb6b350) + 2 (0xbb78240) + 2 (0xbb84ee0) + 2 (0xbb93760) + 2 (0xbb93890) + 2 (0xbb939c0) + 4 (0xbbbfc50) + 4 (0xbbd25f0) + 4 (0xbbe2d50) + 1 (0xbc55100) + 1 (0xbc7f6e0) + 2 (0xbc82ad0) + 2 (0xbc9d7a0) + 1 (0xbcb64f0) + 1 (0xbcd77b0) + 1 (0xe7ec1f0) = 55.
- No other function in the image calls the target declarator (`callers 0x5698290` = 21 functions, all listed above).

CLOSES? YES — every VV/RTX render-target declaration is proven [V] at instruction level: all 55 call sites of the target declarator are enumerated, 54 across the 20 VV/RTX builders and 1 in the bloom post builder (0xe7ec1f0, not a VV RT), each with its descriptor stack offset and the dword format store (46 rows, 5 of them caller-desc aliases rather than new allocations); the Fancy live census and the record layout were already closed in materials-visuals.md (6z-2, 6im), so no pending part of the item remains.
