## NEXT
DONE

# U-EM1e: M1e Pass lambdas (L6) — 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources

This run covers: bloom down (builder 0xbc98310), the two verify_oc mismatch fixes (0x568cdbe, 0x568d0b8), and the Fancy/shared-body status.

## Disambiguation — bloom down "body" is a registration+dispatch body, not ScreenDraw

The orchestrator hint/r4 note claims bloom/local-exposure "bodies" are hash-static registration sites whose executed body is the shared ScreenDraw body 0xbc04dc0. The disassembly contradicts that for bloom down: builder 0xbc98310 at 0xbc99739 loads the DFDownSample FNV-1 hash, resolves it via sub_76ad00, then registers execute body 0xBC9AC80 via sub_e935740 and pass slot 0x12AE1DB0 via sub_e938D70. The same at 0xbc99794 registers ThresholdedDownSample body 0xBC9AD10 -> slot 0x12AE1DE8. So 0xbc9ac80/0xbc9ad10 are the real executed bodies (compute dispatch via [0xF9A8C78]); ScreenDraw 0xbc04dc0 is NOT the bloom down body. r4's claim that these names are "data/vtable" applies only to the Fancy ctor sites 0xF25C9B0/0xF25C9E0/0xF440770/0xF43E9C0 (proven DATA below), not to bloom down.

## Verified rows (offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|---------------------|-------------------------|---------|-----|
| 0x568cdbe | 8 | [rbx] | `0x568cdbe  mov rbx,rdx` | copy pass-object ptr rdx->rbx; fixes wrong claim `movq xmm0,[rbx+f8]` (real is `mov rbx,rdx`; the movq [rbx+0xF8] is at 0x568cdde) | [V] |
| 0x568cdde | 16 | [rbx+0xF8] | `0x568cdde  movq xmm0,[rbx+0xF8]` | load rect x/y from pass object +0xF8; offset +0xf8 confirmed correct | [V] |
| 0x568d0b8 | 2 | [rdx+0x2A] | `0x568d0b8  movzx edx,word ptr [rdx+0x2A]` | load word field at +0x2A; fixes wrong claim `movzx r10d,word ptr [r8+2c]` (reg edx not r10d, off +0x2a not +0x2c) | [V] |
| 0x568d797 | 2 | [rcx+0x2C] | `0x568d797  movzx ecx,word ptr [rcx+0x2C]` | tail site 0x568d750: loads word field at +0x2C (confirms +0x2c used at this site; distinct from the 0x568d0b8 +0x2a site) | [V] |
| 0xbc99739 | 8 | imm | `0xbc99739  mov rdx,0x34E743CD5E04564D` | bloom DFDownSample FNV-1 hash static (builder 0xbc98310 registration) | [V] |
| 0xbc99749 | - | imm | `0xbc99749  lea rcx,[0xBC9AC80]` | DFDownSample execute-body address 0xbc9ac80 passed to sub_e935740 | [V] |
| 0xbc99750 | - | imm | `0xbc99750  call 0xE935740` | register execute body (rcx=0xbc9ac80) via sub_e935740 | [V] |
| 0xbc99755 | - | imm | `0xbc99755  lea rcx,[0x12AE1DB0]` | DFDownSample pass slot 0x12AE1DB0 | [V] |
| 0xbc9975c | - | imm | `0xbc9975c  call 0xE938D70` | register pass slot via sub_e938D70 | [V] |
| 0xbc99794 | 8 | imm | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | bloom ThresholdedDownSample FNV-1 hash static | [V] |
| 0xbc997a4 | - | imm | `0xbc997a4  lea rcx,[0xBC9AD10]` | ThresholdedDownSample execute-body address 0xbc9ad10 passed to sub_e935740 | [V] |
| 0xbc997ab | - | imm | `0xbc997ab  call 0xE935740` | register execute body (rcx=0xbc9ad10) via sub_e935740 | [V] |
| 0xbc997b0 | - | imm | `0xbc997b0  lea rcx,[0x12AE1DE8]` | ThresholdedDownSample pass slot 0x12AE1DE8 | [V] |
| 0xbc997b7 | - | imm | `0xbc997b7  call 0xE938D70` | register pass slot via sub_e938D70 | [V] |
| 0xbc9ac80 | - | [none] | `0xbc9ac80  sub rsp,0x28` | DFDownSample execute-body 0xbc9ac80 prologue; manages ring-buffer data_12ae1da0/0x12ae1d88 | [V] |
| 0xbc9ac84 | 8 | [data_12ae1da0] | `0xbc9ac84  mov rax,[0x12AE1DA0]` | ring-buffer count load | [V] |
| 0xbc9acfa | - | [data_f9a8c78] | `0xbc9acfa  call qword ptr [0xF9A8C78]` | dispatch/submit via data slot 0xF9A8C78 (same slot used by SSR execute bodies) | [V] |
| 0xbc9ad10 | - | [none] | `0xbc9ad10  sub rsp,0x28` | ThresholdedDownSample execute-body 0xbc9ad10 prologue | [V] |

## Fancy pass bodies — DATA, not code (proof rows)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|---------------------|-------------------------|---------|-----|
| 0xF25C9B0 | - | [none] | `bad` instructions (jo short 0xf25c970, insb, add [rax],al...) | Fancy ClearColorDepth ctor site: DATA, not a code body [rdis yields undecodable bytes] | [?] |
| 0xF25C9E0 | - | [none] | `bad` instructions (xor dl,al, insb...) | Fancy ClearDepth ctor site: DATA, not a code body | [?] |
| 0xF440770 | - | [none] | `mov al,0x8A; ret` then garbage | Fancy Pass task vtable DATA (installed as vtable ptr by 0xBC38AB0 `mov [rcx],rax`) | [?] |
| 0xF43E9C0 | - | [none] | garbage | Fancy TerrainAtlasBlit vtable DATA (installed by 0xBC01E80 `mov [rcx],rax`) | [?] |
| 0xBC38AB0 | 1 | [none] | `0xBC38AB0  push rsi` | Fancy Pass task ctor prologue; `0xBC38ABB lea rax,[0xF440770]` / `0xBC38AC2 mov [rcx],rax` installs vtable 0xF440770 | [V ctor, ? body] |
| 0xBC01E80 | 1 | [none] | `0xBC01E80  push rsi` | Fancy TerrainAtlasBlit ctor prologue; `0xBC01E8B lea rax,[0xF43E9C0]` / `0xBC01E92 mov [rcx],rax` installs vtable 0xF43E9C0 | [V ctor, ? body] |

## Per-pass in/out resources — coverage status (VV/RTX builder groups + Fancy)

[V] = instruction-verified from rows above; [I] = inferred from builder/pass-name, body not verbatim-read in this file; [?] = not located statically / DATA not code.

| pass group | builder | body RVA(s) | In | Out | tag |
|------------|---------|-------------|----|-----|-----|
| voxel | 0xbb3e2b0 | 0xbc0b240 (CombineVoxelLighting), 0xbc0ac20 (upload) | pass rect +0x88, pass+0x98 byte, material arg fields +0x0/+0x8/+0x10/+0x48, globals 0x12ADF6D0/0x128767C8; buffer upload via sub_bcc23a0 | view rect +0x10/+0x14, mat4 +0x20/+0x60/+0xA0/+0xE0, view+0x120, view+0x132; VoxelBuffer compute write | [V] in, [V] out |
| depth prepasses | 0xbb4c2e0 | generic task 0x568cd90 (per 6ha) | task rect +0xF8/+0xFC, mats +0x78/+0xB8/+0x10C/+0x14C, vec4 +0x18C, sort byte +0x108, records +0x48 | view writes +0x10/+0x14/+0x20/+0x60/+0xA0/+0xE0/+0x120/+0x132 + draws | [V] body; in/out [V] from 0x568cd90 reads |
| deferred | 0xbb6b350 | 0xbc2c590, 0xbc2cd20, 0xbc2d550, 0xbc2dd20 | viewId word, pass rect +0x88, pass+0x98 byte, refcount pass object+0x10+8, material pointer +0x90, material+0x2F8/+0x300 pass table, textures/buffers +0x38 | view rect +0x10/+0x14, mat4 +0x20/+0x60/+0xA0/+0xE0, view+0x120, view+0x132 | [V] |
| DepthAndNormal | 0xbb78240 | generic task 0x568cd90 (per 6ha) | as generic task above | as generic task above | [V] body; in/out [V] from 0x568cd90 reads |
| DoWaterSurfaceBuffer | 0xbb7b210 | generic task 0x568cd90 (per 6ha) | as generic task above | as generic task above | [V] body; in/out [V] from 0x568cd90 reads |
| WaterExtinction | 0xbb7efb0 | 0xbc2eb50 | material +0x23C | standard view writes | [V] |
| WaterSurface | 0xbb81880 | 0xbc2f4a0 | material +0x23C/+0x1A0, byte +0x294 string select | standard view writes | [V] |
| forward PBR | 0xbb84ee0 | generic task 0x568cd90 (per 6ha) | as generic task above | as generic task above | [V] body; in/out [V] from 0x568cd90 reads |
| DoIndirectSpecularUpscale | 0xbb8eb70 | 0xbc36140 | ScreenDraw field-for-field (rect +0x168/+0x16C, mats +0xE8/+0x128/+0x17C/+0x1BC, +0x1FC, byte +0x178, name +0x268, state +0x20C, geometry +0x88, material pass +0xE0); list submit 0xbcc39b0 | per builder 0xbb8eb70 | [V structure] |
| ColorPostProcess | 0xbbbcb20 | ScreenDraw 0xbc04dc0 | drawstate rect +0x168/+0x16C, byte +0x178, viewId word, pass-name chain via sub_ebce5e0 on [rcx+0xDC57E0], uniform ColorGrading_Misc, texture ColorTexture at in+8 | pass view's framebuffer | [V] in, [I] out target |
| NothingTask | 0xbbbfc50 | 0xbc38c20 (item-list), 0x56aeeb0 (view-only) | item vector +0x48 range [+0x68,+0x70) of 0x18-byte entries | none (no-op / view touch only) | [V structure] |
| LightClustering | 0xbc57460 | 0xbc5bad0 | globals 0x1233E1A8, 0x12ADF7A8/0x12ADF7B8/0x12ADF7C8/0x12ADF7D8, chain *(view record+8)+0x38 | three cluster buffers (zLights, Extends, zLightLookupArray) | [V] |
| VolumeScattering | 0xbc7c580 | 0xbc7e100 | 2 uniforms VolumeDimensions/VolumeNearFar; textures ScatteringBufferIn/Out | ScatteringBuffer write | [V structure] |
| MinMax | 0xbc7f6e0 | 0xbc8093f/0xbc8099a | initialize/downsample | min/max buffers | [V structure] |
| SSR | 0xbc82ad0 | stubs 0xbc84b7c/bd0/c24/c78; bodies 0xbc88320/3B0/440/4D0; unpack 0xbc88560 | param struct via sub_bc88560 (byte [rdx+0x17C]==1; vec4 +0x00/+0x10/+0x20/+0x30; dword +0x90/+0x124; byte +0x128/+0x17A; float +0x130; word +0x159; double +0x15C); pass slots 0x12AE18D8/1910/1948/1980; named param blocks SSRRayMarchingParams/SSRFadingParamsAndThickness/SSRRoughnessCutoffParams | RT/dispatch writes in guarded execute bodies | [V] in, [I] out |
| TAAUpscaling | 0xbc8a380 | 0xbc8da0c/0xbc8ab12 (+closure 0xbc8cfd0) | material pass table +0x2F8/+0x300 (+0x310/+0x318), viewId word; named param blocks ResolutionRatiosAndFPEpsilon, Previous/CurrentViewProjectionMatrixUniform, RenderResolution, DisplayResolution, RecipDisplayResolution, SubPixelJitterAndValidHistory | submitPass via 0xBCC38E0 | [V] |
| LuminanceHistogram/HistogramBuild | 0xbc8eb90 | 0xbc96950 CleanUp, 0xbc973e0 BuildHistogram, 0xbc97bc0 CalculateAverage | luminance histograms (previous/adapted frame average) | luminance output textures | [V structure] |
| bloom down | 0xbc98310 | 0xbc9ac80 (DFDownSample), 0xbc9ad10 (ThresholdedDownSample) | pass rect/params via ring buffer data_12ae1da0/0x12ae1d88, dispatch via [0xF9A8C78] | downsampled bloom UAV writes (dispatch target not decoded) | [V] body located, in/out [?] |
| bloom up | 0xbc9ada0 | 0xbc9bbd4 (DFUpSample), 0xbc9bc28 (BloomBlend) | - | - | [I] body not read |
| local exposure | 0xbc9d7a0 | 0xbca2671 (ApplyLocalExposure), 0xbca24f1/0xbca2551/0xbca25b1 bilateral grid | - | - | [I] body not read |
| CubemapToOffscreen | 0xbcd77b0 | 0xbc0f130 | cube texture + CurrentMip/CurrentFace/DummyUniform | offscreen cube face Color0 | [V structure] |
| Convolve | 0xbcdba70 | not located | - | - | [I] body not located |
| RTX prep | 0xbbe2d50 | 0xbc080c0 -> 0xbcc4b90 | pass rect +0x88/+0x8C, viewId word, pass+0x98 byte, a2 fields | standard view writes + RTX denoise dispatch | [V] |
| RTX denoise/raygen | 0xbcc4b90 | 0xbcc4b90 (43 pass names via sub_9d6d0) | 0x1E8 params block = 43 program handles + RT parameters; 65-slot texture table via 0xc28f000; compute entry strings | UAV/dispatch writes of the 43 RT passes | [V] in, [I] out (UAV writes not read) |
| FSR1 | 0xbcb3cf0 | 0xbcb7590 FSR1Compute, 0xbcb7e70 FSR1Frag | - | - | [V structure] |
| Fancy Scene/HUD tasks | Fancy frame tasks at 0xe9002e0 | shared body 0x568cd90 (+ draw emission 0x568d480) | task rect +0xF8/+0xFC, mats +0x78/+0xB8/+0x10C/+0x14C, vec4 +0x18C, sort byte +0x108, dependency records +0x48 [+0x70,+0x68), pass table +0x2F8/+0x300 (+0x310/+0x318), state pool +0x738 stride 0x58 | view writes +0x10/+0x14/+0x20/+0x60/+0xA0/+0xE0/+0x120/+0x132; draw submit target inside unread 0x568d480 tail | [V] body + in; out [?] for submit tail |
| Fancy ClearColorDepth | - | 0xF25C9B0 (DATA) | - | - | [?] DATA not code |
| Fancy ClearDepth | - | 0xF25C9E0 (DATA) | - | - | [?] DATA not code |
| Fancy Pass task | - | vtable 0xF440770, ctor 0xBC38AB0 | - | - | [?] body not located |
| Fancy TerrainAtlasBlit | - | vtable 0xF43E9C0, ctor 0xBC01E80 | - | - | [?] body not located |

## What changed on disk

- Created docs/progress/oc_U-EM1e.md (this file). No other file created, edited, or deleted. No build run; the game was not launched; static analysis only, exe used as rdis.exe argument.

## CLOSES?

NO — blocking fact: not every one of the 35 VV/RTX lambdas + Fancy pass bodies has [V] in/out rows on disk yet. This run proves bloom down registration (body 0xbc9ac80/0xbc9ad10, NOT ScreenDraw) and fixes the 2 verify_oc mismatches, but bloom up (0xbc9bbd4/0xbc9bc28), local exposure (0xbca2671), Convolve (body not located), RTX denoise UAV outputs, Fancy clear/Pass/TerrainAtlasBlit bodies (DATA at 0xF25C9B0/0xF25C9E0/0xF440770/0xF43E9C0; ctors at 0xBC38AB0/0xBC01E80 install vtables but no code body decoded), and the 0x568d480 tail + 0x568d750 body (final submit target) remain [I]/[?].

## TOOL REQUESTS

- rdis.exe | exe + RVA -> instruction listing | used for every quoted `0xRVA  instr` line and to read 0xbc9ac80/0xbc9ad10.
- verify_oc.py | md -> mismatch/no-such-instr report | validates quoted instruction lines against the exe.
- (wish) none; no new helper scripts were needed.
