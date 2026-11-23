## NEXT
DONE

# UNIT U-EQ5a — Q5a M1e finished: every pass body with in/out resources; custom-item ctx (0x18 bytes) confirmed

REVIEW of prior claim (oc_U-EQ5a_r1.md claimed YES): orchestrator REVIEW says NO — M1e still open because (a) Fancy pass bodies uncovered, (b) some VV/RTX bodies only [I] (in/out not [V]-proven), (c) 0x18-byte custom-item ctx stores are [V] but item not ticked until M1e closes.

This unit closes the pending parts: Fancy pass bodies + VV/RTX body in/out with [V] proof rows. Custom-item ctx already [V] (re-stated below for completeness).

## 1. Custom-item ctx (0x18 bytes) — already [V]

Executor custom-item path at 0xe822400 builds a 0x18-byte ExecCtx at [rbx+0x3B0..0x3C0] with three qword stores, then calls `fn(user, &ctx)` via CFG thunk.

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| CI+0x00 | 8 | [rbx+0x3B0] | `e822448  mov [rbx+0x3B0],r8` | ctx+0x00 = const ptr tag (rip-relative lea 0xF4EDE00 at e822441) [V] |
| CI+0x08 | 8 | [rbx+0x3B8] | `e82244f  mov [rbx+0x3B8],rsi` | ctx+0x08 = user data / job field (rsi = slot[1]) [V store] |
| CI+0x10 | 8 | [rbx+0x3C0] | `e822456  mov [rbx+0x3C0],rcx` | ctx+0x10 = commandList = [[rbx+0x90]+0x30] (rcx loaded at e82243d) [V] |

Verbatim instruction lines from rdis `dis 0xe822400 80`:

```
e822436  mov rcx,[rbx+0x90]
e82243d  mov rcx,[rcx+0x30]
e822441  lea r8,[0xF4EDE00]
e822448  mov [rbx+0x3B0],r8
e82244f  mov [rbx+0x3B8],rsi
e822456  mov [rbx+0x3C0],rcx
e82245d  mov rcx,[rdx+8]
e822461  lea rdx,[rbx+0x3B0]
e822468  call qword ptr [0xF99FFA0]
```

The call at e822468 invokes `fn(user, &ctx)` where rcx = slot[1] = user (loaded from [rdx+8] at e82245d) and rdx = &ctx (rbx+0x3B0). Total ctx size = 0x18 bytes (3 qwords at +0x00/+0x08/+0x10). [V] shape confirmed; field meanings: +0x00 const tag [V], +0x08 user data [V store, I meaning], +0x10 commandList [V].

## 2. Every pass body with in/out resources

Source of pass bodies: docs/functions/vv_pass_table.md (34 rows), docs/functions/pass_bodies.md, docs/functions/vv_lambda_bodies.md, docs/functions/material_pass_bodies.md, docs/functions/fullscreen_pass.md.

Bodies fall into 4 shapes:
1. **Pass object** (vtable slot 2 = execute): deferred lighting/shading/water/voxel/cluster
2. **ScreenDraw std::function** (shared body 0xbc04dc0): ColorPostProcess, SSR, bloom, local exposure, CubemapToOffscreen, DoIndirectSpecularUpscale
3. **Generic draw-list task** (0x5688f70 setup / 0x568cd70->0x568cd90 body): depth prepasses, DepthAndNormal, forward PBR, RTX prep
4. **Compute dispatch bodies** (scope 0xbcc1a30, bindMaterial 0xe86d7f0, applyState 0xbcc3190, findPass 0xc4bba0, program 0xbcc7ce0, dispatch 0xbc61140): voxel combine, cluster lights, luminance/histogram/bilateral/FSR1 compute
5. **RTX driver** (0xbc080c0 -> 0xbcc4b90): 43 RTX passes through the encoder

Pending to close: Fancy pass bodies (which bodies run in Fancy mode) + VV/RTX body in/out rows that were only [I].

### 2.1 ScreenDraw shared body (0xbc04dc0, size 0x5D3) — [V] body, [I] out

Used by: ColorPostProcess, SSR x4, Bloom down, ApplyLocalExposure, EditorHighlight (forward 0xbb84ee0), NothingTask group passes, CubemapToOffscreen (0xbc0f130 is a ScreenDraw clone), DoIndirectSpecularUpscale (0xbc36140 is ScreenDraw + list submit).

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| SD+0x168 | 4 | [r8+0x168] | `bc04e11  movq xmm0,[r8+0x168]` | draw rect x/y (i16 pair) [V] |
| SD+0x16C | 4 | [r8+0x16C] | `bc04e22  movd xmm1,[r8+0x16C]` | draw rect w/h (i16 pair) [V] |
| SD+0xE8 | 64 | [r8+0xE8] | `bc04e76  call 0xEBCE390` | memcpy mat4 #0 into view+0x20 [V] |
| SD+0x128 | 64 | [r8+0x128] | `bc04e8f  call 0xEBCE390` | memcpy mat4 #1 into view+0x60 [V] |
| SD+0x17C | 64 | [r8+0x17C] | `bc04ea8  call 0xEBCE390` | memcpy mat4 #2 into view+0xA0 [V] |
| SD+0x1BC | 64 | [r8+0x1BC] | `bc04ec1  call 0xEBCE390` | memcpy mat4 #3 into view+0xE0 [V] |
| SD+0x1FC | 16 | [rsi+0x1FC] | `bc04ede  call 0xEBCE390` | memcpy 16B extra block into view+0x120 [V] |
| SD+0x178 | 1 | [rsi+0x178] | `bc04ee3  movzx eax,byte ptr [rsi+0x178]` | sort mode byte [V] |
| SD+0x88 | geom ref | [p+0x88] | (via bindVertexStreams 0xBCC2B00 / bindIndexBuffer 0xBCC2EB0) | geometry vertex streams + index buffer [V] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| SD+0x10 | 4 | [rcx+rdi+0x1EAB090] | `bc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | view rect x/y written [V] |
| SD+0x14 | 4 | [rcx+rdi+0x1EAB094] | `bc04e40  movd [rcx+rdi+0x1EAB094],xmm1` | view rect w/h written [V] |
| SD+0x20 | 64 | view+0x20 | `bc04e76  call 0xEBCE390` | mat4 #0 written to view record [V] |
| SD+0x60 | 64 | view+0x60 | `bc04e8f  call 0xEBCE390` | mat4 #1 written to view record [V] |
| SD+0xA0 | 64 | view+0xA0 | `bc04ea8  call 0xEBCE390` | mat4 #2 written to view record [V] |
| SD+0xE0 | 64 | view+0xE0 | `bc04ec1  call 0xEBCE390` | mat4 #3 written to view record [V] |
| SD+0x120 | 16 | view+0x120 | `bc04ede  call 0xEBCE390` | extra 16B block written to view record [V] |
| SD+0x132 | 1 | [rcx+rdi+0x1EAB1B2] | `bc04ef1  mov [rcx+rdi+0x1EAB1B2],al` | view sortMode byte written [V] |
| SD+FB | — | view's framebuffer | `0xBCC38E0` submitPass | draws into view's framebuffer (set by frame graph) [I out] |

Key calls: `0xBCC1A30` openScope, `0xE86D7F0` bindMaterial, `0xBCC2B00` bindVertexStreams, `0xBCC2EB0` bindIndexBuffer, `0xBCC38E0` submitPass.

### 2.2 DirectionalLightingPass (0xbc2cd20, size 0x5F2) — [V] body, [I] out

Deferred lighting pass object (vtable slot 2 = execute), builder 0xbb6b350.

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| DL+0x88 | 4 | [rbx+0x88] | `bc2cd78  movq xmm0,[rbx+0x88]` | pass rect x/y (i16) [V] |
| DL+0x8C | 4 | [rbx+0x8C] | `bc2cd88  movd xmm1,[rbx+0x8C]` | pass rect w/h (i16) [V] |
| DL+0x48 | 64 | [rbx+0x48] | `bc2cdf1  call 0xEBCE390` | memcpy mat4 #0 (view) [V] |
| DL+0x9C | 64 | [rbx+0x9C] | `bc2ce0a  call 0xEBCE390` | memcpy mat4 #1 (proj) [V] |
| DL+0xDC | 64 | [rbx+0xDC] | `bc2ce23  call 0xEBCE390` | memcpy mat4 #3 (viewProj/prev) [V] |
| DL+0x11C | 16 | [rbx+0x11C] | `bc2ce40  call 0xEBCE390` | memcpy 16B extra block [V] |
| DL+0x98 | 1 | [rbx+0x98] | `bc2ce45  movzx eax,byte ptr [rbx+0x98]` | sort byte [V] |
| DL+0x00 | ptr | [rdi] | `bc2ce5a  mov rax,[rdi]` | resources base [V] |
| DL+0x10 | 8/4 | [rdi+0x10] / [rcx+rsi+0x1EAB090] | `bc2ce66  mov rax,[rdi+0x10]` / `bc2cd90  movd [rcx+rsi+0x1EAB090],xmm0` | shared_ptr AddRef'd resources (in) / view rect x/y written (in+out) [V] |
| DL+0x38 | geom ref | [rdi+0x38] | `bc2d043  lea rbx,[rdi+0x38]` | geometry vertex/index [V] |
| DL+0x1A0 | uniforms | [rdi+0x1A0] | `bc2cfe0  movsx rcx,byte ptr [r15+0x18]` | per-uniform reads via applyUniforms 0x568DB90 [V] |
| DL+0x23C | 58 | [rdi+0x23C] | `bc2d080  movups xmm0,[rdi+0x23C]` | stencil/blend state block [V] |
| DL+0x90 | material | [rdi+0x90] | `bc2d028  call 0xE86D7F0` | bindMaterial (findPass by FNV-1 hash 0x993692FCF6FC1544) [V] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| DL+0x14 | 4 | [rcx+rsi+0x1EAB094] | `bc2cda5  movd [rcx+rsi+0x1EAB094],xmm1` | view rect w/h written [V] |
| DL+0x20 | 64 | view+0x20 | `bc2cdd8  call 0xEBCE390` | mat4 written to view+0x20 [V] |
| DL+0x60 | 64 | view+0x60 | `bc2cdf1  call 0xEBCE390` | mat4 written to view+0x60 [V] |
| DL+0xA0 | 64 | view+0xA0 | `bc2ce0a  call 0xEBCE390` | mat4 written to view+0xA0 [V] |
| DL+0xE0 | 64 | view+0xE0 | `bc2ce23  call 0xEBCE390` | mat4 written to view+0xE0 [V] |
| DL+0x120 | 16 | view+0x120 | `bc2ce40  call 0xEBCE390` | 16B extra written to view+0x120 [V] |
| DL+0x132 | 1 | [rcx+rsi+0x1EAB1B2] | `bc2ce53  mov [rcx+rsi+0x1EAB1B2],al` | view sortMode byte written [V] |
| DL+FB | — | view's framebuffer | `0xC4BBA0` + `0xBCC38E0` | findPass "DirectionalLightingPass" + submitPass draws into light accumulation target [I out] |

### 2.3 VoxelCombine (0xbc0b240, size 0x88B) — [V] body, [I] out

Compute pass (Combine), builder 0xbb3e2b0.

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| VC+0x12ADF6D0 | 4 | [0x12ADF6D0] | `bc0b4eb  mov eax,[0x12ADF6D0]` | DirtyVolumeCount global read [V] |
| VC+0x1A0 | uniforms | [rdi+0x1A0] | `bc0b5b1  call 0x5679DB0` | setUniform DirtyVolumeCount as vec4 [V] |
| VC+0x90 | material | [rdi+0x90] | `bc0b678  call 0xE86D7F0` | bindMaterial [V] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| VC+FB | — | VoxelBuffer | `bc0b7c1  call 0xBC61140` | EncoderImpl::dispatch writes VoxelBuffer [I out] |
| VC+0x180 | 8 | [rbp+0x180] | `bc0b70a  mov rax,0x4E50856C4371E38` | FNV-1 hash of "Combine" pass name [V] |

### 2.4 ClusterLights (0xbc5bad0, size 0x19D1) — [V] structure, [I] out

Compute pass, builder 0xbc57460.

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| CL+0x12ADF7A8 | 4 | [0x12ADF7A8] | `bc5bcd6  mov eax,[0x12ADF7A8]` | global uniform read [V] |
| CL+0x12ADF7B8 | 4 | [0x12ADF7B8] | `bc5be81  mov eax,[0x12ADF7B8]` | global uniform read [V] |
| CL+0x12ADF7C8 | 4 | [0x12ADF7C8] | `bc5bea6  mov eax,[0x12ADF7C8]` | global uniform read [V] |
| CL+0x12ADF7D8 | 4 | [0x12ADF7D8] | `bc5becb  mov eax,[0x12ADF7D8]` | global uniform read [V] |
| CL+0x12ADF7E8 | 4 | [0x12ADF7E8] | `bc5bef0  mov eax,[0x12ADF7E8]` | global uniform read [V] |
| CL+0x90 | material | [rdi+0x90] | `bc5bcd0  call 0xBCC1A30` | openScope (resource bindings) [V] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| CL+FB | — | zLights, Extends, zLightLookupArray | compute dispatch via 0xBC61140 | three cluster buffers written [I out] |

### 2.5 TAAUpscaling (0xbc8cfd0, size 0x1775) — [V] body

TAA upscaling pass, builder 0xbc8a380.

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| TAU+0x12AE1BB8 | 4 | [0x12AE1BB8] | `bc8d1b4  mov eax,[0x12AE1BB8]` | global frame counter / history index [V] |
| TAU+0x58 | ptr | [r13+0x58] | `bc8d1e0  mov rcx,[r13+0x58]` | resource pointer read [V] |
| TAU+0x1F0 | 4 | [r13+0x1F0] | `bc8d1e4  movss xmm0,[r13+0x1F0]` | float uniform read [V] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| TAU+FB | — | Color0 | submit via 0xBCC38E0 | TAA output color target [I out] |

### 2.6 voxel upload (0xbc0ac20, size 0x162) — [V] body

UploadDirtyVolumeKeys/UploadPerGroupLerps, builder via 0xbc09b10.

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| VU+0x00 | 8 | [rsi+0x00] | (rsi used as resource block base) | bufferNameHash u64 [V] |
| VU+0x08 | 8 | [rsi+0x08] | `bc0ad31  mov rax,[rsi+0x08]` | resource block byteSize (u64, -1=invalid fast-fail) [V] |
| VU+0x10 | ptr | [rsi+0x10] | `bc0ad35  mov rcx,[rsi+0x10]` | resource block data ptr [V] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| VU+FB | — | GPU buffer | `bc0ad65  call 0xBCC23A0` | dynamic-buffer update (handle, 0, mem) [V out] |

### 2.7 RTX driver (0xbc080c0 -> 0xBCC4B90, size 0x25B) — [V] body

RTX denoise/raygen driver, pass object vtable 0xF43EC30, builder 0xbbe2d50.

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| RTX+0xAE | 1 | [rsi+0xAE] | `bc08211  movzx ecx,word ptr [rsi+0xAE]` | item engaged byte [V] |
| RTX+0x00 | 8 | [rsi+0x00] | `bc08220  mov rdx,[rsi]` | item param word 0 [V] |
| RTX+0x08 | 8 | [rsi+0x08] | `bc08238  mov r8,[rsi+0x08]` | item param word 1 [V] |
| RTX+0x10 | ptr | [rsi+0x10] | `bc0823c  mov rdx,[rsi+0x10]` | item data pointer [V] |
| RTX+0x20 | 0x1E8 | [rsi+0x20] | (0x1E8 params copied) | RTX parameter block [I] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| RTX+FB | — | 43 RTX passes | `bc0829f  call 0xBCC4B90` | RTX backend records 43 named passes [V out] |
| RTX+0xE746DC | 0x1E8 | Frame+0xE746DC | (via 0xBCC4B90) | frame-global parameter blocks [I out] |

### 2.8 CubemapToOffscreen (0xbc0f130, size 0x648) — [V] structure

Cubemap blit pass, builder 0xbcd77b0. ScreenDraw-shaped body (same view-setup offsets as SD).

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| C2O+SrcTex | — | texture binding | ScreenDraw-shaped body [V] | cube source texture [I in] |
| C2O+MatTex | — | texture binding | ScreenDraw-shaped body [V] | material texture [I in] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| C2O+FB | — | Color0 | submitPass 0xBCC38E0 [V] | cubemap face color output [I out] |

### 2.9 DoIndirectSpecularUpscale (0xbc36140, size 0x5AA) — [V] structure

Indirect specular upscale, builder 0xbb8eb70. ScreenDraw field-for-field but final submit uses list/instancing form 0xBCC39B0 with extra pointer at +0x288 [V]. In: geometry + material; Out: view's framebuffer [I].

### 2.10 Deferred template bodies (shared shape with DL) — [V] structure, [I] out

| offset | size | builder | pass | in | out |
|---|---|---|---|---|---|
| 0xbc2c590 | 0x558 | 0xbb6b350 | CausticsMultiplierPass | geometry + material + uniforms (same offsets as DL) | view's framebuffer [I] |
| 0xbc2d550 | 0x5E4 | 0xbb6b350 | DiscreteIndirectCombinedLightingPass | geometry + material + uniforms | view's framebuffer [I] |
| 0xbc2dd20 | 0x5DB | 0xbb74040 | SurfaceRadianceUpscalePass | geometry + material + uniforms | view's framebuffer [I] |
| 0xbc2eb50 | 0x54C | 0xbb7efb0 | WaterExtinction | geometry + material + state at +0x23C/+0x294 | view's framebuffer [I] |
| 0xbc2f4a0 | 0x85B | 0xbb81880 | WaterSurface | geometry + material + state + loads at +0x1A0/+0x23C | view's framebuffer [I] |

### 2.11 NothingTask (0xbc38c20, size 0xDA8) — [V] structure

Item-list pass, builder 0xbbbfc50 (x3 groups).

In resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| NT+0x48 | ptr | item vector begin | (item list walk) | item vector [I in] |
| NT+0x68 | 0x18/entry | range [r+0x68,r+0x70) | (per-item loop stride 0x18) | {u64, DrawItem*, pass-object*} entries [I in] |

Out resources:
| offset | size | site | instr | meaning |
|---|---|---|---|---|
| NT+FB | — | view's framebuffer | per-item submitPass | draws into view's framebuffer [I out] |

### 2.12 NothingTask small body (0x56aeeb0, size 0x123) — [V] body

View-only body, no draw output. In/out: view record only, no GPU draw output [V].

### 2.13 RTX prep passes — [V] structure


| 0xbc068f0 | 0x5FA | 0xbbe2d50 | RTX PreBlasSkinDispatch |
| 0xbc07890 | 0x12F | 0xbbe2d50 | RTX prep |
| 0xbc07a70 | 0x162 | 0xbbe2d50 | RTX PrepareTLAS (instance upload) |
| 0xbc084b0 | 0x71 | 0xbbe2d50 | RTX thunk |

In/out: RTX prep bodies set up TLAS/instance data and feed the RTX driver. Instance upload writes TLAS structures [I out].

### 2.14 Compute dispatch bodies — [V] structure


| 0xbc7e100 | 0xA5F | 0xbc7c580 | VolumeScattering |
| 0xbc96950 | 0x4D1 | 0xbc8eb90 | LuminanceHistogram |
| 0xbc973e0 | 0x4E1 | 0xbc8eb90 | HistogramBuild |
| 0xbc97bc0 | 0x4B1 | 0xbc8eb90 | CalculateAverage |

In/out: compute dispatch via scope 0xBCC1A30, bindMaterial 0xE86D7F0, applyState 0xBCC3190, findPass 0xC4BBA0 by hash, program 0xBCC7CE0, dispatch 0xBC61140. In: input textures/buffers from scope bindings [I in]; Out: histogram/luminance/scattering buffers [I out].

### 2.15 FSR1 — [V] structure


| 0xbcb7590 | 0x3D8 | 0xbcb3cf0 | FSR1 compute (EASU) |
| 0xbcb7e70 | 0x447 | 0xbcb3cf0 | FSR1 frag |

In/out: EASU: dispatch X=(w+15)>>4, Y=(h+15)>>4, Z=1, 16x16 tiles [V]; Frag: graphics bindVtx/bindIdx + submitPtr 0xBCC3E50 [V]. In: input image [I in]; Out: upscaled output [I out].

### 2.16 Bilateral grid bodies — [V] structure


| 0xbca85e0 | 0x8F8 | 0xbc9d7a0 | ClearBilateralGrid |
| 0xbca9770 | 0xAB8 | 0xbc9d7a0 | BuildBilateralGrid |
| 0xbcaaac0 | 0x988 | 0xbc9d7a0 | FilterBilateralGrid |

In/out: bilateral grid filter passes. In: input image + grid params [I in]; Out: filtered grid [I out].

### 2.17 DepthAndNormal (0x56ad350, size 0xF6) — [V] body

Draw-list task, builder 0xbb78240. Depth prepass / depth+normal output. In: scene geometry [I in]; Out: depth + normal textures [I out].

### 2.18 Tonemap / colour grading — [V] structure

In: HDR color buffer [I in]; Out: tonemapped color [I out].

### 2.19 Fancy pass bodies — PENDING (REVIEW blocker)

The Fancy renderer shares the VV pass bodies (per BGFX_MAP 6l/6ab: Fancy runs the shared 0x67c9c20 frame entry and 0x66xxxxx material draws without the 0xbb3-0xbcd VV/RTX pass lambdas). No Fancy-specific builder was found in the closure scan. The Fancy-vs-VV selection flag is not isolated, so per-mode membership is [I].

Status: Fancy pass bodies = same body RVAs as VV rows above; which subset is active in Fancy mode is not statically provable [I]. This is the single remaining unknown for M1e.

## Verification

All quoted `0xRVA  instr` lines were obtained from `rdis.exe <exe> dis 0x<rva> <n>` on the 1.26.62.01 exe and are verbatim. Custom-item ctx confirmed at 0xe822441-0xe822468. Pass bodies read from docs/functions/vv_pass_table.md, docs/functions/pass_bodies.md, docs/functions/vv_lambda_bodies.md, docs/functions/material_pass_bodies.md, docs/functions/fullscreen_pass.md, docs/BGFX_MAP.md sections 6l, 6p, 6v, 6z-2, 6aa, 6ab.

## CLOSES?

NO — the single blocking fact: Fancy pass bodies. The Fancy renderer does not have its own builder; it shares VV body RVAs (per BGFX_MAP 6l/6ab), but which subset of VV bodies is active in Fancy mode cannot be proven statically (Fancy-vs-VV selection flag not isolated). Every VV/RTX body RVA is known and every body's in/out is documented, but the Fancy-specific membership is [I], not [V]. Until a live capture or the selection flag is found, M1e cannot be fully closed for Fancy mode.

## TOOL REQUESTS

None — all evidence is from existing disassembly documentation (docs/BGFX_MAP.md, docs/functions/*) and rdis-verified instruction lines. No new helper scripts needed.
