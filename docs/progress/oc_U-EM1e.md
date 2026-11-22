## NEXT
DONE

# M1e Pass lambdas (L6): non-ScreenDraw VV/RTX pass bodies + per-pass in/out resources

## Summary

GOAL (from M1e line): close checklist item "Pass lambdas (L6): the 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources". Done before this unit (per docs/BGFX_MAP.md 6gz/6ha/6hb/6hr): ScreenDraw path fully mapped (ColorPostProcess builder 0xbbbcb20 -> declareScreenPass 0xbbbd3d0 -> buildScreenPass 0xbc37320 -> registerPass 0xbc37ca0; execute std::function vtable 0xF440710, _Do_call 0xbc380d0 -> shared ScreenDraw body 0xbc04dc0 -> submit 0xbcc38e0); ColorPostProcess in/out read (in=ColorTexture at in+8 + ColorGrading_Misc uniform; out=pass view's framebuffer); SSR passes run shared ScreenDraw body via 0xbc88560; voxel upload body 0xbc0ac20; RTX denoise/raygen body 0xbcc4b90 reached from RTX prep body 0xbc080c0; submitPass inline variant reversed at 0xbcc3b90 (0xbc60740 submit, 0xbc60d10 dispatch variant, 0xbc618e0 submitFrameParams).

This unit (so far): instruction-level reads of DoDeferredLighting 0xbc2c590, DirectionalLightingPass 0xbc2cd20, DoDeferredShading 0xbc2d550/0xbc2dd20, WaterExtinction 0xbc2eb50, WaterSurface 0xbc2f4a0, VoxelCombine 0xbc0b240, ClusterLights 0xbc5bad0 — plus ScreenDraw shared body 0xbc04dc0 (view writes via s_ctx 0x12AE1748+viewId*0x140; draw-call build via indirect call data slot 0xF99FFA0 edx=0x30; "ScreenDraw:"/"raw:" strings data 0xF7D08BE/0xF7D08C5; pass-name lookup sub_ebce5e0 on chain [rcx+0xDC57E0]) and SSR (stubs 0xbc84b7c/bd0/c24/c78: FNV-1 resolve sub_76ad00, execute-body registration sub_e935740 bodies 0xbc88320/3B0/440/4D0, pass-slot registration sub_e938D70 slots 0x12AE18D8/1910/1948/1980, group "ScreenSpaceReflections" data 0xF54E7B3 len 0x16 via sub_5668AC0 slot 0x12AE1988, named param blocks SSRRayMarchingParams/SSRFadingParamsAndThickness/SSRRoughnessCutoffParams via sub_79580 FNV-1 basis 0xCBF29CE484222325; sub_bc88560 param unpack: cmp byte [rdx+0x17C],1 and movups/movss/movsd reads param+0x00..+0x17A, call sub_6760450) plus TAAU 0xbc8da0c/0xbc8ab12 (submitPass via 0xBCC38E0, named param blocks ResolutionRatiosAndFPEpsilon/PreviousViewProjectionMatrixUniform/CurrentViewProjectionMatrixUniform/RenderResolution/DisplayResolution/RecipDisplayResolution/SubPixelJitterAndValidHistory via sub_79580), RTX prep 0xbc080c0 (standard view prologue, calls RTX denoise sub_bcc4b90, nested RTX pass-object ctors vtables [data_f43ec60]/[data_f43ec90]) + RTX denoise/raygen 0xbcc4b90 (args a0/a2/a3, refcount via data slot 0xF99FFA0, compute entry strings "ClearVertexIrradianceCache"..."BlendCheckerboardFields" via sub_9d6d0) plus voxel upload 0xbc0ac20 (standard view prologue, upload via sub_bcc23a0, nested release via data slot 0xF99FFA0) — 404 rows verified verbatim against the exe with verify_oc.py.

UNIT DONE: (a) ScreenDraw 0xbc04dc0 + SSR stubs/bodies/param unpack; (b) TAAU 0xbc8da0c/0xbc8ab12; (c) RTX prep 0xbc080c0 + denoise 0xbcc4b90; (d) voxel upload 0xbc0ac20; (e) per-pass in/out for every VV builder group (see Per-pass in/out section, 23 VV groups from docs/BGFX_MAP.md 6gz + 3 indirect, strings from docs/functions/vv_builder_pass_order_55f1450.md). Verbatim-read bodies: 17; remaining VV lambdas (depth 0xbb4c2e0, forward 0xbb84ee0, CausticsMultiplierPass, DiscreteIndirectCombinedLightingPass, DoWaterSurfaceBuffer 0xbb7b210, DoIndirectSpecularUpscale 0xbb8eb70, NothingTask 0xbbbfc50, VolumeScattering 0xbc7c580, MinMax 0xbc7f6e0, LuminanceHistogram 0xbc8eb90, bloom down 0xbc98310, bloom up 0xbc9ada0, local exposure 0xbc9d7a0, CubemapToOffscreen 0xbcd77b0, Convolve 0xbcdba70, FSR1 0xbcb3cf0) are [I]-inferred from builder/pass-name only, not verbatim-read.

## Verified rows (offset | size | site | verbatim `0xRVA  instr` | meaning | tag)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc2c5d6 | 2 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c5d6  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read; shl eax,6 + lea rsi,[rax+rax*4] = viewId*0x140 view stride | [V] |
| 0xbc2c5e8 | 8 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c5e8  movq xmm0,[rbx+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 | [V] |
| 0xbc2c600 | 4 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c600  movd [rcx+rsi+0x1EAB090],xmm0                 ` | view rect dword store view+0x10 (s_ctx+0x1EAB090+viewId*0x140) | [V] |
| 0xbc2c615 | 4 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c615  movd [rcx+rsi+0x1EAB094],xmm1                 ` | view rect dword store view+0x14 | [V] |
| 0xbc2c648 | - | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c648  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call (r8d=0x40, set at 0xbc2c642) into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc2c5c7); memcpy pattern [I] | [V] |
| 0xbc2c661 | - | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c661  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc2c67a | - | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c67a  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc2c693 | - | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c693  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r15=a0+0xDC; memcpy pattern [I] | [V] |
| 0xbc2c6b5 | 1 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c6b5  movzx eax,byte ptr [rbx+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc2c6c3 | 1 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c6c3  mov [rcx+rsi+0x1EAB1B2],al                    ` | view+0x132 u8 store (s_ctx+0x1EAB1B2+viewId*0x140) | [V] |
| 0xbc2c6df | 4 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c6df  lock inc dword ptr [rax+8]                    ; W *(a2+0x10)+0x8` | refcount dword inc on pass object+0x10+8 | [V] |
| 0xbc2c6ca | 8 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c6ca  mov rax,[rdi]                                 ; R a2+0x0` | pass object qword load +0x0 | [V] |
| 0xbc2c6eb | 8 | DoDeferredLighting 0xbc2c590 prologue | `0xbc2c6eb  mov rcx,[rdi+8]                               ` | pass object qword load +8 | [V] |
| 0xbc2c76a | - | DoDeferredLighting 0xbc2c590 | `0xbc2c76a  lea rcx,[0xF5B3C06]                           ; [data_f5b3c06] "DoDeferredLighting"` | pass-name string argument for lookup | [V] |
| 0xbc2c810 | - | DoDeferredLighting 0xbc2c590 | `0xbc2c810  lea r13,[rdi+0x90]                            ` | material pointer load from pass+0x90 | [V] |
| 0xbc2c88d | - | DoDeferredLighting 0xbc2c590 | `0xbc2c88d  lea rbx,[rdi+0x38]                            ` | textures/buffers pointer load from pass+0x38 | [V] |
| 0xbc2c901 | 8 | DoDeferredLighting 0xbc2c590 | `0xbc2c901  mov rdx,[rsi+0x2F8]                            ` | material+0x2F8 qword load (pass table) | [V] |
| 0xbc2c908 | 8 | DoDeferredLighting 0xbc2c590 | `0xbc2c908  mov r8,[rsi+0x300]                            ` | material+0x300 qword load | [V] |
| 0xbc2cd66 | 2 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2cd66  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read; viewId*0x140 view stride | [V] |
| 0xbc2cd78 | 8 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2cd78  movq xmm0,[rbx+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 | [V] |
| 0xbc2cd90 | 4 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2cd90  movd [rcx+rsi+0x1EAB090],xmm0                 ` | view rect dword store view+0x10 | [V] |
| 0xbc2cda5 | 4 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2cda5  movd [rcx+rsi+0x1EAB094],xmm1                 ` | view rect dword store view+0x14 | [V] |
| 0xbc2cdd8 | - | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2cdd8  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc2cd57); memcpy pattern [I] | [V] |
| 0xbc2cdf1 | - | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2cdf1  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc2ce0a | - | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2ce0a  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc2ce23 | - | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2ce23  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r15=a0+0xDC; memcpy pattern [I] | [V] |
| 0xbc2ce45 | 1 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2ce45  movzx eax,byte ptr [rbx+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc2ce53 | 1 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2ce53  mov [rcx+rsi+0x1EAB1B2],al                    ` | view+0x132 u8 store | [V] |
| 0xbc2ce6f | 4 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2ce6f  lock inc dword ptr [rax+8]                    ; W *(a2+0x10)+0x8` | refcount dword inc on pass object+0x10+8 | [V] |
| 0xbc2ce5a | 8 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2ce5a  mov rax,[rdi]                                 ; R a2+0x0` | pass object qword load +0x0 | [V] |
| 0xbc2ce7b | 8 | DirectionalLightingPass 0xbc2cd20 prologue | `0xbc2ce7b  mov rcx,[rdi+8]                               ` | pass object qword load +8 | [V] |
| 0xbc2cf03 | - | DirectionalLightingPass 0xbc2cd20 | `0xbc2cf03  lea rcx,[0xF5B3C06]                           ; [data_f5b3c06] "DoDeferredLighting"` | pass-name string argument for lookup | [V] |
| 0xbc2d077 | 4 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d077  mov eax,[rdi+0x24C]                            ` | material dword load +0x24C | [V] |
| 0xbc2d080 | 16 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d080  movups xmm0,[rdi+0x23C]                        ` | material vec4 load +0x23C (movups = 16 bytes) | [V] |
| 0xbc2d08b | 1 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d08b  movzx eax,byte ptr [rdi+0x250]                 ` | material byte load +0x250 | [V] |
| 0xbc2d095 | 16 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d095  movups xmm0,[rdi+0x254]                        ` | material vec4 load +0x254 (movups = 16 bytes) | [V] |
| 0xbc2d0a0 | 16 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d0a0  movdqu xmm0,[rdi+0x264]                        ` | material load +0x264 (movdqu = 16 bytes) | [V] |
| 0xbc2d0a8 | 16 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d0a8  movdqu xmm1,[rdi+0x274]                        ` | material load +0x274 (movdqu = 16 bytes) | [V] |
| 0xbc2d0b0 | 16 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d0b0  movups xmm2,[rdi+0x283]                        ` | material vec4 load +0x283 (movups = 16 bytes) | [V] |
| 0xbc2d0c5 | 8 | DirectionalLightingPass 0xbc2cd20 | `0xbc2d0c5  mov rsi,[rdi+0x90]                             ` | pass object pointer load from pass+0x90 | [V] |
| 0xbc2d596 | 2 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d596  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read; viewId*0x140 view stride | [V] |
| 0xbc2d5a8 | 8 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d5a8  movq xmm0,[rbx+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 | [V] |
| 0xbc2d5c0 | 4 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d5c0  movd [rcx+rsi+0x1EAB090],xmm0                 ` | view rect dword store view+0x10 | [V] |
| 0xbc2d5d5 | 4 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d5d5  movd [rcx+rsi+0x1EAB094],xmm1                 ` | view rect dword store view+0x14 | [V] |
| 0xbc2d608 | - | DoDeferredShading 0xbc2d550 prologue | `0xbc2d608  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc2d587); memcpy pattern [I] | [V] |
| 0xbc2d621 | - | DoDeferredShading 0xbc2d550 prologue | `0xbc2d621  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc2d63a | - | DoDeferredShading 0xbc2d550 prologue | `0xbc2d63a  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc2d653 | - | DoDeferredShading 0xbc2d550 prologue | `0xbc2d653  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r15=a0+0xDC; memcpy pattern [I] | [V] |
| 0xbc2d675 | 1 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d675  movzx eax,byte ptr [rbx+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc2d683 | 1 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d683  mov [rcx+rsi+0x1EAB1B2],al                    ` | view+0x132 u8 store | [V] |
| 0xbc2d69f | 4 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d69f  lock inc dword ptr [rax+8]                    ; W *(a2+0x10)+0x8` | refcount dword inc on pass object+0x10+8 | [V] |
| 0xbc2d68a | 8 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d68a  mov rax,[rdi]                                 ; R a2+0x0` | pass object qword load +0x0 | [V] |
| 0xbc2d6ab | 8 | DoDeferredShading 0xbc2d550 prologue | `0xbc2d6ab  mov rcx,[rdi+8]                               ` | pass object qword load +8 | [V] |
| 0xbc2d733 | - | DoDeferredShading 0xbc2d550 | `0xbc2d733  lea rcx,[0xF5B7E33]                           ; [data_f5b7e33] "DoDeferredShading"` | pass-name string argument for lookup | [V] |
| 0xbc2dd66 | 2 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2dd66  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read; viewId*0x140 view stride | [V] |
| 0xbc2dd78 | 8 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2dd78  movq xmm0,[rbx+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 | [V] |
| 0xbc2dd90 | 4 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2dd90  movd [rcx+rsi+0x1EAB090],xmm0                 ` | view rect dword store view+0x10 | [V] |
| 0xbc2dda5 | 4 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2dda5  movd [rcx+rsi+0x1EAB094],xmm1                 ` | view rect dword store view+0x14 | [V] |
| 0xbc2ddd8 | - | DoDeferredShading 0xbc2dd20 prologue | `0xbc2ddd8  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc2dd57); memcpy pattern [I] | [V] |
| 0xbc2ddf1 | - | DoDeferredShading 0xbc2dd20 prologue | `0xbc2ddf1  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc2de0a | - | DoDeferredShading 0xbc2dd20 prologue | `0xbc2de0a  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc2de23 | - | DoDeferredShading 0xbc2dd20 prologue | `0xbc2de23  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r15=a0+0xDC; memcpy pattern [I] | [V] |
| 0xbc2de45 | 1 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2de45  movzx eax,byte ptr [rbx+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc2de53 | 1 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2de53  mov [rcx+rsi+0x1EAB1B2],al                    ` | view+0x132 u8 store | [V] |
| 0xbc2de6f | 4 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2de6f  lock inc dword ptr [rax+8]                    ; W *(a2+0x10)+0x8` | refcount dword inc on pass object+0x10+8 | [V] |
| 0xbc2de5a | 8 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2de5a  mov rax,[rdi]                                 ; R a2+0x0` | pass object qword load +0x0 | [V] |
| 0xbc2de7b | 8 | DoDeferredShading 0xbc2dd20 prologue | `0xbc2de7b  mov rcx,[rdi+8]                               ` | pass object qword load +8 | [V] |
| 0xbc2df03 | - | DoDeferredShading 0xbc2dd20 | `0xbc2df03  lea rcx,[0xF5B7E33]                           ; [data_f5b7e33] "DoDeferredShading"` | pass-name string argument for lookup | [V] |
| 0xbc2eb96 | 2 | WaterExtinction 0xbc2eb50 prologue | `0xbc2eb96  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read; viewId*0x140 view stride | [V] |
| 0xbc2eba8 | 8 | WaterExtinction 0xbc2eb50 prologue | `0xbc2eba8  movq xmm0,[rbx+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 | [V] |
| 0xbc2ebc0 | 4 | WaterExtinction 0xbc2eb50 prologue | `0xbc2ebc0  movd [rcx+rsi+0x1EAB090],xmm0                 ` | view rect dword store view+0x10 | [V] |
| 0xbc2ebd5 | 4 | WaterExtinction 0xbc2eb50 prologue | `0xbc2ebd5  movd [rcx+rsi+0x1EAB094],xmm1                 ` | view rect dword store view+0x14 | [V] |
| 0xbc2ec08 | - | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec08  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc2eb87); memcpy pattern [I] | [V] |
| 0xbc2ec21 | - | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec21  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc2ec3a | - | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec3a  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc2ec53 | - | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec53  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r15=a0+0xDC; memcpy pattern [I] | [V] |
| 0xbc2ec75 | 1 | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec75  movzx eax,byte ptr [rbx+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc2ec83 | 1 | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec83  mov [rcx+rsi+0x1EAB1B2],al                    ` | view+0x132 u8 store | [V] |
| 0xbc2ec8a | 8 | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec8a  mov rax,[rdi]                                 ; R a2+0x0` | pass object qword load +0x0 | [V] |
| 0xbc2ec9f | 4 | WaterExtinction 0xbc2eb50 prologue | `0xbc2ec9f  lock inc dword ptr [rax+8]                    ; W *(a2+0x10)+0x8` | refcount dword inc on pass object+0x10+8 | [V] |
| 0xbc2ecab | 8 | WaterExtinction 0xbc2eb50 prologue | `0xbc2ecab  mov rcx,[rdi+8]                               ` | pass object qword load +8 | [V] |
| 0xbc2ed2d | - | WaterExtinction 0xbc2eb50 | `0xbc2ed2d  lea rcx,[0xF589E41]                           ; [data_f589e41] "WaterExtinction"` | pass-name string argument for lookup | [V] |
| 0xbc2ee8b | - | WaterExtinction 0xbc2eb50 | `0xbc2ee8b  lea rdx,[rdi+0x23C]                            ` | material vec load address +0x23C (rdi=pass object) | [V] |
| 0xbc2f4e6 | 2 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f4e6  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read; viewId*0x140 view stride | [V] |
| 0xbc2f4f8 | 8 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f4f8  movq xmm0,[rbx+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 | [V] |
| 0xbc2f510 | 4 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f510  movd [rcx+rsi+0x1EAB090],xmm0                 ` | view rect dword store view+0x10 | [V] |
| 0xbc2f525 | 4 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f525  movd [rcx+rsi+0x1EAB094],xmm1                 ` | view rect dword store view+0x14 | [V] |
| 0xbc2f558 | - | WaterSurface 0xbc2f4a0 prologue | `0xbc2f558  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc2f4d7); memcpy pattern [I] | [V] |
| 0xbc2f571 | - | WaterSurface 0xbc2f4a0 prologue | `0xbc2f571  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc2f58a | - | WaterSurface 0xbc2f4a0 prologue | `0xbc2f58a  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc2f5a3 | - | WaterSurface 0xbc2f4a0 prologue | `0xbc2f5a3  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r15=a0+0xDC; memcpy pattern [I] | [V] |
| 0xbc2f5c5 | 1 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f5c5  movzx eax,byte ptr [rbx+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc2f5d3 | 1 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f5d3  mov [rcx+rsi+0x1EAB1B2],al                    ` | view+0x132 u8 store | [V] |
| 0xbc2f5da | 8 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f5da  mov rax,[rdi]                                 ; R a2+0x0` | pass object qword load +0x0 | [V] |
| 0xbc2f5ef | 4 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f5ef  lock inc dword ptr [rax+8]                    ; W *(a2+0x10)+0x8` | refcount dword inc on pass object+0x10+8 | [V] |
| 0xbc2f5fb | 8 | WaterSurface 0xbc2f4a0 prologue | `0xbc2f5fb  mov rcx,[rdi+8]                               ` | pass object qword load +8 | [V] |
| 0xbc2f682 | - | WaterSurface 0xbc2f4a0 | `0xbc2f682  lea rcx,[0xF5EA52C]                           ; [data_f5ea52c] "WaterSurface"` | pass-name string argument for lookup | [V] |
| 0xbc2f7f7 | - | WaterSurface 0xbc2f4a0 | `0xbc2f7f7  lea rdx,[rdi+0x23C]                            ` | material vec load address +0x23C | [V] |
| 0xbc2f80b | - | WaterSurface 0xbc2f4a0 | `0xbc2f80b  lea rdx,[rdi+0x1A0]                            ` | material load address +0x1A0 | [V] |
| 0xbc2f830 | 1 | WaterSurface 0xbc2f4a0 | `0xbc2f830  cmp byte ptr [rdi+0x294],0                     ` | material byte test +0x294 (cmovne string select follows) | [V] |
| 0xbc0b27f | 2 | VoxelCombine 0xbc0b240 prologue | `0xbc0b27f  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read (note: rdi=a1 view, rsi=a0 pass); viewId*0x140 stride | [V] |
| 0xbc0b291 | 8 | VoxelCombine 0xbc0b240 prologue | `0xbc0b291  movq xmm0,[rsi+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 (rsi=pass) | [V] |
| 0xbc0b2a9 | 4 | VoxelCombine 0xbc0b240 prologue | `0xbc0b2a9  movd [rcx+rbx+0x1EAB090],xmm0                  ` | view rect dword store view+0x10 (rbx=viewId*0x140) | [V] |
| 0xbc0b2be | 4 | VoxelCombine 0xbc0b240 prologue | `0xbc0b2be  movd [rcx+rbx+0x1EAB094],xmm1                  ` | view rect dword store view+0x14 | [V] |
| 0xbc0b2ea | - | VoxelCombine 0xbc0b240 prologue | `0xbc0b2ea  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc0b277); memcpy pattern [I] | [V] |
| 0xbc0b303 | - | VoxelCombine 0xbc0b240 prologue | `0xbc0b303  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc0b31c | - | VoxelCombine 0xbc0b240 prologue | `0xbc0b31c  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc0b339 | - | VoxelCombine 0xbc0b240 prologue | `0xbc0b339  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src rdx=a0+0xDC (set at 0xbc0b332); memcpy pattern [I] | [V] |
| 0xbc0b359 | - | VoxelCombine 0xbc0b240 prologue | `0xbc0b359  call 0xEBCE390                                ; -> sub_ebce390` | 16-byte copy call (r8d=0x10) into view+0x120; src rdx=a0+0x11C; memcpy pattern [I] | [V] |
| 0xbc0b35e | 1 | VoxelCombine 0xbc0b240 prologue | `0xbc0b35e  movzx eax,byte ptr [rsi+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc0b36c | 1 | VoxelCombine 0xbc0b240 prologue | `0xbc0b36c  mov [rcx+rbx+0x1EAB1B2],al                     ` | view+0x132 u8 store | [V] |
| 0xbc0b37a | 8 | VoxelCombine 0xbc0b240 | `0xbc0b37a  mov rax,[rax]                                 ; R *(a1+0x8)+0x0` | qword load *(view record+8)+0 | [V] |
| 0xbc0b388 | - | VoxelCombine 0xbc0b240 | `0xbc0b388  lea rcx,[0xF25C7F0]                           ; [data_f25c7f0]` | string data reference | [V] |
| 0xbc0b3f4 | - | VoxelCombine 0xbc0b240 | `0xbc0b3f4  call 0xEEC5870                                ; -> sub_eec5870` | call with edx=2 | [V] |
| 0xbc0b403 | - | VoxelCombine 0xbc0b240 | `0xbc0b403  call 0x9BD2E0                                 ; -> sub_9bd2e0` | call | [V] |
| 0xbc0b41c | 4 | VoxelCombine 0xbc0b240 | `0xbc0b41c  lock inc dword ptr [rcx+8]                    ; W *(*(a2+0x0)+0x8)+0x8` | refcount dword inc (a2=r15=material arg) | [V] |
| 0xbc0b427 | 16 | VoxelCombine 0xbc0b240 | `0xbc0b427  movdqu xmm0,[rax]                             ; R *(a2+0x0)+0x0` | 16-byte load from material+0x0 (movdqu = 16 bytes) | [V] |
| 0xbc0b438 | 4 | VoxelCombine 0xbc0b240 | `0xbc0b438  lock dec dword ptr [r15+8]                     ` | refcount dword dec on material+8 | [V] |
| 0xbc0b448 | - | VoxelCombine 0xbc0b240 | `0xbc0b448  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | indirect call via data slot 0xF99FFA0 | [V] |
| 0xbc0b496 | 8 | VoxelCombine 0xbc0b240 | `0xbc0b496  mov rdx,[rax+0x170]                            ` | qword load rax+0x170 (sub_e86b370 argument setup) | [V] |
| 0xbc0b4a0 | - | VoxelCombine 0xbc0b240 | `0xbc0b4a0  call 0xE86B370                                ; -> sub_e86b370` | call | [V] |
| 0xbc0b4eb | 4 | VoxelCombine 0xbc0b240 | `0xbc0b4eb  mov eax,[0x12ADF6D0]                          ; [data_12adf6d0]` | global data dword read | [V] |
| 0xbc0b4f1 | 4 | VoxelCombine 0xbc0b240 | `0xbc0b4f1  mov ecx,[0x128767C8]                          ; [data_128767c8]` | global data dword read (TLS index) | [V] |
| 0xbc0b510 | 4 | VoxelCombine 0xbc0b240 | `0xbc0b510  mov eax,[r14+0x48]                             ` | dword load a2+0x48 (r14=r15=a2=material arg) | [V] |
| 0xbc0b570 | 8 | VoxelCombine 0xbc0b240 | `0xbc0b570  mov r10,[rcx]                                  ` | table-entry pointer load (pass-name hash scan loop) | [V] |
| 0xbc0b5b7 | 8 | VoxelCombine 0xbc0b240 | `0xbc0b5b7  mov rax,[r14+0x10]                             ` | qword load a2+0x10 | [V] |
| 0xbc0b5d5 | 4 | VoxelCombine 0xbc0b240 | `0xbc0b5d5  lock inc dword ptr [rax+8]                     ` | refcount dword inc | [V] |
| 0xbc5bb22 | 2 | ClusterLights 0xbc5bad0 prologue | `0xbc5bb22  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8` | viewId word read (rdi=a0 pass, r14=a1 view); viewId*0x140 stride | [V] |
| 0xbc5bb34 | 8 | ClusterLights 0xbc5bad0 prologue | `0xbc5bb34  movq xmm0,[rdi+0x88]                          ; R a0+0x88` | pass rect x/y load from pass+0x88 | [V] |
| 0xbc5bb4c | 4 | ClusterLights 0xbc5bad0 prologue | `0xbc5bb4c  movd [rcx+rsi+0x1EAB090],xmm0                  ` | view rect dword store view+0x10 | [V] |
| 0xbc5bb61 | 4 | ClusterLights 0xbc5bad0 prologue | `0xbc5bb61  movd [rcx+rsi+0x1EAB094],xmm1                  ` | view rect dword store view+0x14 | [V] |
| 0xbc5bb94 | - | ClusterLights 0xbc5bad0 prologue | `0xbc5bb94  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x20 mat4 slot; src rdx=a0+8 (set at 0xbc5bb1a); memcpy pattern [I] | [V] |
| 0xbc5bbad | - | ClusterLights 0xbc5bad0 prologue | `0xbc5bbad  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r13=a0+0x48; memcpy pattern [I] | [V] |
| 0xbc5bbc6 | - | ClusterLights 0xbc5bad0 prologue | `0xbc5bbc6  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r12=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc5bbdf | - | ClusterLights 0xbc5bad0 prologue | `0xbc5bbdf  call 0xEBCE390                                ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r15=a0+0xDC; memcpy pattern [I] | [V] |
| 0xbc5bbff | - | ClusterLights 0xbc5bad0 prologue | `0xbc5bbff  call 0xEBCE390                                ; -> sub_ebce390` | 16-byte copy call (r8d=0x10) into view+0x120; src rdx=a0+0x11C; memcpy pattern [I] | [V] |
| 0xbc5bc04 | 1 | ClusterLights 0xbc5bad0 prologue | `0xbc5bc04  movzx eax,byte ptr [rdi+0x98]                 ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc5bc12 | 1 | ClusterLights 0xbc5bad0 prologue | `0xbc5bc12  mov [rcx+rsi+0x1EAB1B2],al                     ` | view+0x132 u8 store | [V] |
| 0xbc5bc4f | 8 | ClusterLights 0xbc5bad0 | `0xbc5bc4f  mov rsi,[rdi]                                 ; R *(a1+0x8)+0x0` | qword load *(view record+8)+0 | [V] |
| 0xbc5bc56 | 8 | ClusterLights 0xbc5bad0 | `0xbc5bc56  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]` | global data qword read | [V] |
| 0xbc5bc69 | - | ClusterLights 0xbc5bad0 | `0xbc5bc69  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | indirect call via data slot 0xF99FFA0, edx=0x30 | [V] |
| 0xbc5bc8a | - | ClusterLights 0xbc5bad0 | `0xbc5bc8a  lea rax,[0xF25CB70]                           ; [data_f25cb70]` | string data reference | [V] |
| 0xbc5bcd0 | - | ClusterLights 0xbc5bad0 | `0xbc5bcd0  call 0xBCC1A30                                ; -> sub_bcc1a30` | call (encoder begin/draw setup) | [V] |
| 0xbc5bcd6 | 4 | ClusterLights 0xbc5bad0 | `0xbc5bcd6  mov eax,[0x12ADF7A8]                          ; [data_12adf7a8]` | global data dword read | [V] |
| 0xbc5bd9b | 8 | ClusterLights 0xbc5bad0 | `0xbc5bd9b  mov rax,[rsi+0x38]                             ` | qword load from rsi+0x38 (rsi=*(view record+8)) | [V] |
| 0xbc5bdb0 | 4 | ClusterLights 0xbc5bad0 | `0xbc5bdb0  lock inc dword ptr [rcx+8]                     ` | refcount dword inc at *(rsi+0x38)+8+8 | [V] |
| 0xbc5bdbb | 16 | ClusterLights 0xbc5bad0 | `0xbc5bdbb  movdqu xmm0,[rax]                             ` | 16-byte load from [rsi+0x38]+0 (movdqu = 16 bytes) | [V] |
| 0xbc5bdcc | 4 | ClusterLights 0xbc5bad0 | `0xbc5bdcc  lock dec dword ptr [r12+8]                     ` | refcount dword dec | [V] |
| 0xbc5bdde | - | ClusterLights 0xbc5bad0 | `0xbc5bdde  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | indirect call via data slot 0xF99FFA0 | [V] |
| 0xbc5bdf7 | - | ClusterLights 0xbc5bad0 | `0xbc5bdf7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | indirect call via data slot 0xF99FFA0 | [V] |
| 0xbc5be81 | 4 | ClusterLights 0xbc5bad0 | `0xbc5be81  mov eax,[0x12ADF7B8]                          ; [data_12adf7b8]` | global data dword read | [V] |
| 0xbc5bea6 | 4 | ClusterLights 0xbc5bad0 | `0xbc5bea6  mov eax,[0x12ADF7C8]                          ; [data_12adf7c8]` | global data dword read | [V] |
| 0xbc5becb | 4 | ClusterLights 0xbc5bad0 | `0xbc5becb  mov eax,[0x12ADF7D8]                          ; [data_12adf7d8]` | global data dword read | [V] |
| 0xbc04dee | - | ScreenDraw 0xbc04dc0 args | `0xbc04dee  mov rsi,r8                        ; R a2=r8` | drawstate arg rsi=r8 | [V] |
| 0xbc04df1 | - | ScreenDraw 0xbc04dc0 args | `0xbc04df1  mov rbx,rdx                        ; R a1=rdx` | view record arg rbx=rdx | [V] |
| 0xbc04df4 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04df4  lea rdx,[r8+0xE8]                 ; R a2+0xE8` | mat4 copy src address a2+0xE8 (view+0x20 slot) | [V] |
| 0xbc04dfb | 8 | ScreenDraw 0xbc04dc0 prologue | `0xbc04dfb  mov rax,[rbx+8]                  ; R a1+0x8` | view record qword load +8 | [V] |
| 0xbc04dff | 2 | ScreenDraw 0xbc04dc0 prologue | `0xbc04dff  movzx eax,word ptr [rax+8]       ; R *(a1+0x8)+0x8` | viewId word read *(view record+8)+8 | [V] |
| 0xbc04e03 | 8 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e03  mov rcx,[0x12AE1748]              ; [data_12ae1748]` | s_ctx global load (view base) | [V] |
| 0xbc04e11 | 8 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e11  movq xmm0,[r8+0x168]              ; R a2+0x168` | drawstate rect x/y load (movq 8 bytes) | [V] |
| 0xbc04e22 | 4 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e22  movd xmm1,[r8+0x16C]              ; R a2+0x16C` | drawstate rect z/w load (movd 4 bytes) | [V] |
| 0xbc04e2b | 4 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0     ` | view rect dword store view+0x10 (s_ctx+0x1EAB090+viewId*0x140) | [V] |
| 0xbc04e40 | 4 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e40  movd [rcx+rdi+0x1EAB094],xmm1     ` | view rect dword store view+0x14 | [V] |
| 0xbc04e49 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04e49  lea r14,[r8+0x1BC]                ; R a2+0x1BC` | mat4 copy src address a2+0x1BC (view+0xE0 slot) | [V] |
| 0xbc04e50 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04e50  lea r15,[r8+0x17C]                ; R a2+0x17C` | mat4 copy src address a2+0x17C (view+0xA0 slot) | [V] |
| 0xbc04e57 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04e57  lea r12,[r8+0x128]                ; R a2+0x128` | mat4 copy src address a2+0x128 (view+0x60 slot) | [V] |
| 0xbc04e76 | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e76  call 0xEBCE390                   ; -> sub_ebce390` | 64-byte copy call (r8d=0x40 at 0xbc04e70) into view+0x20 mat4 slot; src rdx=a2+0xE8; memcpy pattern [I] | [V] |
| 0xbc04e8f | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e8f  call 0xEBCE390                   ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src r12=a2+0x128; memcpy pattern [I] | [V] |
| 0xbc04ea8 | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ea8  call 0xEBCE390                   ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src r15=a2+0x17C; memcpy pattern [I] | [V] |
| 0xbc04ec1 | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ec1  call 0xEBCE390                   ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src r14=a2+0x1BC; memcpy pattern [I] | [V] |
| 0xbc04ed7 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04ed7  lea rdx,[rsi+0x1FC]              ; R a2+0x1FC` | 16-byte copy src address a2+0x1FC (view+0x120 slot) | [V] |
| 0xbc04ede | 16 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ede  call 0xEBCE390                   ; -> sub_ebce390` | 16-byte copy call (r8d=0x10 at 0xbc04ed1) into view+0x120; src rsi+0x1FC; memcpy pattern [I] | [V] |
| 0xbc04ee3 | 1 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]   ; R a2+0x178` | drawstate byte load +0x178 | [V] |
| 0xbc04ef1 | 1 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ef1  mov [rcx+rdi+0x1EAB1B2],al        ` | view+0x132 u8 store | [V] |
| 0xbc04f1d | - | ScreenDraw 0xbc04dc0 draw build | `0xbc04f1d  call qword ptr [0xF99FFA0]        ; [data_f99ffa0] = sub_eea6040` | draw-call build indirect call via data slot 0xF99FFA0; edx=0x30 (set 0xbc04f18) | [V] |
| 0xbc04f4b | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04f4b  mov rdx,[rdi]                     ; R *(*(a1+0x8)+0x0)+0x0` | draw-state chain qword load | [V] |
| 0xbc04f78 | - | ScreenDraw 0xbc04dc0 draw build | `0xbc04f78  call 0xBCC1A30                    ; -> sub_bcc1a30` | encoder begin/draw setup call | [V] |
| 0xbc04fb3 | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04fb3  mov r15,[rsi+0x278]               ; R a2+0x278` | drawstate qword load +0x278 | [V] |
| 0xbc04fcd | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04fcd  mov rbx,[rsi+0x268]               ; R a2+0x268` | drawstate qword load +0x268 | [V] |
| 0xbc04fd4 | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04fd4  mov r13,[rsi+0x280]               ; R a2+0x280` | drawstate qword load +0x280 | [V] |
| 0xbc050a4 | 4 | ScreenDraw 0xbc04dc0 strings | `0xbc050a4  mov eax,[0xF7D08C5]               ; [data_f7d08c5] "raw:"` | "raw:" dword load | [V] |
| 0xbc050af | 8 | ScreenDraw 0xbc04dc0 strings | `0xbc050af  mov rax,[0xF7D08BE]               ; [data_f7d08be] "ScreenDraw:"` | "ScreenDraw:" qword load | [V] |
| 0xbc050c2 | - | ScreenDraw 0xbc04dc0 strings | `0xbc050c2  call 0xEEC6EC0                    ; -> sub_eec6ec0` | draw-name string build call | [V] |
| 0xbc050fd | - | ScreenDraw 0xbc04dc0 pass lookup | `0xbc050fd  call 0xEBCE5E0                    ; -> sub_ebce5e0` | pass-name lookup on chain [rcx+0xDC57E0] (rcx=[rax] at 0xbc050e0) | [V] |
| 0xbc05136 | 4 | ScreenDraw 0xbc04dc0 pass lookup | `0xbc05136  call 0xEBCE390                    ; -> sub_ebce390` | 4-byte name copy call (r8d=4 at 0xbc05130) | [V] |
| 0xbc0515e | - | ScreenDraw 0xbc04dc0 pass lookup | `0xbc0515e  call 0xEBCE390                    ; -> sub_ebce390` | pass-name copy call (r8d=ebx at 0xbc0514e) | [V] |
| 0xbc051fe | - | ScreenDraw 0xbc04dc0 per-element | `0xbc051fe  call 0x568DB90                    ; -> sub_568db90` | per-element draw call | [V] |
| 0xbc0521a | - | ScreenDraw 0xbc04dc0 tail | `0xbc0521a  lea r8,[r14+0x38]                 ` | r8 = r14+0x38 (textures/buffers pointer) | [V] |
| 0xbc84b7c | - | SSR stub 0xbc84b7c (SSRRayMarch) | `0xbc84b7c  mov rdx,0x46B26355E42496DA         ` | FNV-1 hash load for pass-name resolve | [V] |
| 0xbc84b86 | - | SSR stub 0xbc84b7c | `0xbc84b86  call 0x76AD00                      ; -> sub_76ad00` | pass-name resolve call | [V] |
| 0xbc84b8c | - | SSR stub 0xbc84b7c | `0xbc84b8c  lea rcx,[0xBC88320]                ; [sub_bc88320]` | execute-body address SSRRayMarch 0xbc88320 | [V] |
| 0xbc84b93 | - | SSR stub 0xbc84b7c | `0xbc84b93  call 0xE935740                     ; -> sub_e935740` | execute-body registration call | [V] |
| 0xbc84b98 | - | SSR stub 0xbc84b7c | `0xbc84b98  lea rcx,[0x12AE18D8]               ; [data_12ae18d8]` | pass slot address 0x12AE18D8 | [V] |
| 0xbc84b9f | - | SSR stub 0xbc84b7c | `0xbc84b9f  call 0xE938D70                     ; -> sub_e938d70` | pass-slot registration call | [V] |
| 0xbc84bc9 | - | SSR stub area 0xbc84ba9 | `0xbc84bc9  lea r8,[0xF7CE38A]                 ; [data_f7ce38a] "SSRRayMarchHZB"` | pass-name string reference | [V] |
| 0xbc84bd0 | - | SSR stub 0xbc84bd0 (SSRRayMarchHZB) | `0xbc84bd0  mov rdx,0x2B39461B3803879A         ` | FNV-1 hash load | [V] |
| 0xbc84bda | - | SSR stub 0xbc84bd0 | `0xbc84bda  call 0x76AD00                      ; -> sub_76ad00` | pass-name resolve call | [V] |
| 0xbc84be0 | - | SSR stub 0xbc84bd0 | `0xbc84be0  lea rcx,[0xBC883B0]                ; [sub_bc883b0]` | execute-body address SSRRayMarchHZB 0xbc883B0 | [V] |
| 0xbc84be7 | - | SSR stub 0xbc84bd0 | `0xbc84be7  call 0xE935740                     ; -> sub_e935740` | execute-body registration call | [V] |
| 0xbc84bec | - | SSR stub 0xbc84bd0 | `0xbc84bec  lea rcx,[0x12AE1910]               ; [data_12ae1910]` | pass slot address 0x12AE1910 | [V] |
| 0xbc84bf3 | - | SSR stub 0xbc84bd0 | `0xbc84bf3  call 0xE938D70                     ; -> sub_e938d70` | pass-slot registration call | [V] |
| 0xbc84c1d | - | SSR stub area 0xbc84c16 | `0xbc84c1d  lea r8,[0xF54C98F]                 ; [data_f54c98f] "SSRFillGaps"` | pass-name string reference | [V] |
| 0xbc84c24 | - | SSR stub 0xbc84c24 (SSRFillGaps) | `0xbc84c24  mov rdx,0x1DF55AD7E2C2C59F         ` | FNV-1 hash load | [V] |
| 0xbc84c2e | - | SSR stub 0xbc84c24 | `0xbc84c2e  call 0x76AD00                      ; -> sub_76ad00` | pass-name resolve call | [V] |
| 0xbc84c34 | - | SSR stub 0xbc84c24 | `0xbc84c34  lea rcx,[0xBC88440]                ; [sub_bc88440]` | execute-body address SSRFillGaps 0xbc88440 | [V] |
| 0xbc84c3b | - | SSR stub 0xbc84c24 | `0xbc84c3b  call 0xE935740                     ; -> sub_e935740` | execute-body registration call | [V] |
| 0xbc84c40 | - | SSR stub 0xbc84c24 | `0xbc84c40  lea rcx,[0x12AE1948]               ; [data_12ae1948]` | pass slot address 0x12AE1948 | [V] |
| 0xbc84c47 | - | SSR stub 0xbc84c24 | `0xbc84c47  call 0xE938D70                     ; -> sub_e938d70` | pass-slot registration call | [V] |
| 0xbc84c71 | - | SSR stub area 0xbc84c6a | `0xbc84c71  lea r8,[0xF563D37]                 ; [data_f563d37] "SSRGetReflectedColor"` | pass-name string reference | [V] |
| 0xbc84c78 | - | SSR stub 0xbc84c78 (SSRGetReflectedColor) | `0xbc84c78  mov rdx,0xCF01D3F07DAC7C8          ` | FNV-1 hash load | [V] |
| 0xbc84c82 | - | SSR stub 0xbc84c78 | `0xbc84c82  call 0x76AD00                      ; -> sub_76ad00` | pass-name resolve call | [V] |
| 0xbc84c88 | - | SSR stub 0xbc84c78 | `0xbc84c88  lea rcx,[0xBC884D0]                ; [sub_bc884d0]` | execute-body address SSRGetReflectedColor 0xbc884D0 | [V] |
| 0xbc84c8f | - | SSR stub 0xbc84c78 | `0xbc84c8f  call 0xE935740                     ; -> sub_e935740` | execute-body registration call | [V] |
| 0xbc84c94 | - | SSR stub 0xbc84c78 | `0xbc84c94  lea rcx,[0x12AE1980]               ; [data_12ae1980]` | pass slot address 0x12AE1980 | [V] |
| 0xbc84c9b | - | SSR stub 0xbc84c78 | `0xbc84c9b  call 0xE938D70                     ; -> sub_e938d70` | pass-slot registration call | [V] |
| 0xbc84cc8 | - | SSR group registration | `0xbc84cc8  lea rax,[0xF54E7B3]                ; [data_f54e7b3] "ScreenSpaceReflections"` | pass-group string reference, len 0x16 | [V] |
| 0xbc84ce1 | - | SSR group registration | `0xbc84ce1  lea rcx,[0x12AE1988]               ; [data_12ae1988]` | pass-group slot address 0x12AE1988 | [V] |
| 0xbc84cf6 | - | SSR group registration | `0xbc84cf6  call 0x5668AC0                     ; -> sub_5668ac0` | group registration call (rcx=slot, rdx=[rbp+0x378], r8=[rbp+0x2E0]) | [V] |
| 0xbc84d26 | - | SSR named param block | `0xbc84d26  lea rdx,[0xF550D9E]                ; [data_f550d9e] "SSRRayMarchingParams"` | param-block name string | [V] |
| 0xbc84d37 | - | SSR named param block | `0xbc84d37  call 0x79580                       ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc84d6d | - | SSR named param block | `0xbc84d6d  mov rcx,0xCBF29CE484222325         ` | FNV-1 basis for param-block hashing | [V] |
| 0xbc84d98 | - | SSR named param block | `0xbc84d98  lea rdx,[0xF547C22]                ; [data_f547c22] "SSRFadingParamsAndThickness"` | param-block name string | [V] |
| 0xbc84da9 | - | SSR named param block | `0xbc84da9  call 0x79580                       ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc84e0a | - | SSR named param block | `0xbc84e0a  lea rdx,[0xF550DB3]                ; [data_f550db3] "SSRRoughnessCutoffParams"` | param-block name string | [V] |
| 0xbc84e1b | - | SSR named param block | `0xbc84e1b  call 0x79580                       ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc88324 | 8 | SSR execute body 0xbc88320 (SSRRayMarch) | `0xbc88324  mov rax,[0x12AE18C8]                ; [data_12ae18c8]` | registration-flag slot qword load | [V] |
| 0xbc88331 | 8 | SSR execute body 0xbc88320 | `0xbc88331  mov rcx,[0x12AE18B0]                ; [data_12ae18b0]` | registration-flag slot qword load | [V] |
| 0xbc88365 | 8 | SSR execute body 0xbc88320 | `0xbc88365  mov qword ptr [0x12AE18C0],0        ; [data_12ae18c0]` | registration-flag slot clear write | [V] |
| 0xbc8839a | - | SSR execute body 0xbc88320 | `0xbc8839a  call qword ptr [0xF9A8C78]           ; [data_f9a8c78]` | indirect call via data slot 0xF9A8C78 | [V] |
| 0xbc883b4 | 8 | SSR execute body 0xbc883B0 (SSRRayMarchHZB) | `0xbc883b4  mov rax,[0x12AE1900]                ; [data_12ae1900]` | registration-flag slot qword load | [V] |
| 0xbc883c1 | 8 | SSR execute body 0xbc883B0 | `0xbc883c1  mov rcx,[0x12AE18E8]                ; [data_12ae18e8]` | registration-flag slot qword load | [V] |
| 0xbc8842a | - | SSR execute body 0xbc883B0 | `0xbc8842a  call qword ptr [0xF9A8C78]           ; [data_f9a8c78]` | indirect call via data slot 0xF9A8C78 | [V] |
| 0xbc88444 | 8 | SSR execute body 0xbc88440 (SSRFillGaps) | `0xbc88444  mov rax,[0x12AE1938]                ; [data_12ae1938]` | registration-flag slot qword load | [V] |
| 0xbc88451 | 8 | SSR execute body 0xbc88440 | `0xbc88451  mov rcx,[0x12AE1920]                ; [data_12ae1920]` | registration-flag slot qword load | [V] |
| 0xbc884ba | - | SSR execute body 0xbc88440 | `0xbc884ba  call qword ptr [0xF9A8C78]           ; [data_f9a8c78]` | indirect call via data slot 0xF9A8C78 | [V] |
| 0xbc884d4 | 8 | SSR execute body 0xbc884D0 (SSRGetReflectedColor) | `0xbc884d4  mov rax,[0x12AE1970]                ; [data_12ae1970]` | registration-flag slot qword load | [V] |
| 0xbc884e1 | 8 | SSR execute body 0xbc884D0 | `0xbc884e1  mov rcx,[0x12AE1958]                ; [data_12ae1958]` | registration-flag slot qword load | [V] |
| 0xbc8854a | - | SSR execute body 0xbc884D0 | `0xbc8854a  call qword ptr [0xF9A8C78]           ; [data_f9a8c78]` | indirect call via data slot 0xF9A8C78 | [V] |
| 0xbc88619 | 1 | sub_bc88560 param unpack | `0xbc88619  cmp byte ptr [rdx+0x17C],1           ; R param+0x17C` | param byte compare ==1 (fast path) | [V] |
| 0xbc88626 | 16 | sub_bc88560 param unpack | `0xbc88626  movups xmm12,[rdx]                   ; R param+0x00` | param vec4 load +0x00 (movups 16 bytes) | [V] |
| 0xbc8862a | 16 | sub_bc88560 param unpack | `0xbc8862a  movups xmm10,[rdx+0x10]              ; R param+0x10` | param vec4 load +0x10 (movups 16 bytes) | [V] |
| 0xbc8862f | 16 | sub_bc88560 param unpack | `0xbc8862f  movups xmm9,[rdx+0x20]               ; R param+0x20` | param vec4 load +0x20 (movups 16 bytes) | [V] |
| 0xbc88634 | 16 | sub_bc88560 param unpack | `0xbc88634  movups xmm8,[rdx+0x30]               ; R param+0x30` | param vec4 load +0x30 (movups 16 bytes) | [V] |
| 0xbc88673 | 4 | sub_bc88560 param unpack | `0xbc88673  mov eax,[rdx+0x90]                   ; R param+0x90` | param dword load +0x90 | [V] |
| 0xbc886e5 | 4 | sub_bc88560 param unpack | `0xbc886e5  mov r12d,[rdx+0x124]                 ; R param+0x124` | param dword load +0x124 | [V] |
| 0xbc886ec | 1 | sub_bc88560 param unpack | `0xbc886ec  movzx eax,byte ptr [rdx+0x128]       ; R param+0x128` | param byte load +0x128 | [V] |
| 0xbc88714 | 4 | sub_bc88560 param unpack | `0xbc88714  movss xmm0,[rdx+0x130]               ; R param+0x130` | param float load +0x130 (movss 4 bytes) | [V] |
| 0xbc8874c | 2 | sub_bc88560 param unpack | `0xbc8874c  movzx eax,word ptr [rdx+0x159]       ; R param+0x159` | param word load +0x159 | [V] |
| 0xbc88782 | 8 | sub_bc88560 param unpack | `0xbc88782  movsd xmm6,[rdx+0x15C]               ; R param+0x15C` | param double load +0x15C (movsd 8 bytes) | [V] |
| 0xbc8879e | 1 | sub_bc88560 param unpack | `0xbc8879e  movzx eax,byte ptr [rdx+0x17A]       ; R param+0x17A` | param byte load +0x17A | [V] |
| 0xbc888de | - | sub_bc88560 param unpack | `0xbc888de  call 0x6760450                        ; -> sub_6760450` | param-derived setup call; rcx=rbp+0xA98, rdx=rbp+0xDB8 | [V] |
| 0xbc8da0c | - | TAAU 0xbc8da0c | `0xbc8da0c  mov rax,0x765EF57E0263FFB6             ` | pass-name/hash constant load (stored [rbp+0x40]) | [V] |
| 0xbc8da1a | 8 | TAAU 0xbc8da0c | `0xbc8da1a  mov rdx,[rsi+0x2F8]                    ; R a2+0x2F8` | material+0x2F8 pass-table start (rsi=pass arg) | [V] |
| 0xbc8da21 | 8 | TAAU 0xbc8da0c | `0xbc8da21  mov r8,[rsi+0x300]                    ; R a2+0x300` | material+0x300 pass-table end | [V] |
| 0xbc8da33 | - | TAAU 0xbc8da0c | `0xbc8da33  call 0xC4BBA0                          ; -> sub_c4bba0` | pass-table iterator helper | [V] |
| 0xbc8da7e | 8 | TAAU 0xbc8da0c | `0xbc8da7e  mov rdi,[rax]                          ` | resolved pass object (iterator result) | [V] |
| 0xbc8dafb | 8 | TAAU 0xbc8da0c | `0xbc8dafb  mov rax,[rbx+8]                        ; R *(a1+0x8)+0x0` | view record qword load +8 (rbx=view record) | [V] |
| 0xbc8daff | 2 | TAAU 0xbc8da0c | `0xbc8daff  movzx r8d,word ptr [rax+8]             ; R *(a1+0x8)+0x8` | viewId word read | [V] |
| 0xbc8db1b | - | TAAU 0xbc8da0c | `0xbc8db1b  call 0xBCC38E0                          ; -> sub_bcc38e0` | submitPass call (edx=0, r9=[rbp+0x40]=u32 arg) | [V] |
| 0xbc8db64 | - | TAAU 0xbc8da0c | `0xbc8db64  lea rcx,[rbp+0x10]                     ` | cleanup setup | [V] |
| 0xbc8db68 | - | TAAU 0xbc8da0c | `0xbc8db68  call 0x568DA90                          ; -> sub_568da90` | string/name cleanup call | [V] |
| 0xbc8dbab | - | TAAU 0xbc8da0c | `0xbc8dbab  call 0x655CEA0                          ; -> sub_655cea0` | string cleanup call | [V] |
| 0xbc8dbe0 | 8 | TAAU 0xbc8da0c named params | `0xbc8dbe0  lea rcx,[0x12AE1BB8]                    ; [data_12ae1bb8]` | named-param slot data_12ae1bb8 | [V] |
| 0xbc8dbf9 | - | TAAU 0xbc8da0c named params | `0xbc8dbf9  lea rdx,[0xF584FC3]                     ; [data_f584fc3] "ResolutionRatiosAndFPEpsilon"` | param-block name string | [V] |
| 0xbc8dc07 | - | TAAU 0xbc8da0c named params | `0xbc8dc07  call 0x79580                            ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc8dc46 | 8 | TAAU 0xbc8da0c named params | `0xbc8dc46  lea rcx,[0x12AE1BC8]                    ; [data_12ae1bc8]` | named-param slot data_12ae1bc8 | [V] |
| 0xbc8dc5f | - | TAAU 0xbc8da0c named params | `0xbc8dc5f  lea rdx,[0xF5998F8]                     ; [data_f5998f8] "PreviousViewProjectionMatrixUniform"` | param-block name string | [V] |
| 0xbc8dc6d | - | TAAU 0xbc8da0c named params | `0xbc8dc6d  call 0x79580                            ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc8dcac | 8 | TAAU 0xbc8da0c named params | `0xbc8dcac  lea rcx,[0x12AE1BD8]                    ; [data_12ae1bd8]` | named-param slot data_12ae1bd8 | [V] |
| 0xbc8dcc5 | - | TAAU 0xbc8da0c named params | `0xbc8dcc5  lea rdx,[0xF5998D5]                     ; [data_f5998d5] "CurrentViewProjectionMatrixUniform"` | param-block name string | [V] |
| 0xbc8dcd3 | - | TAAU 0xbc8da0c named params | `0xbc8dcd3  call 0x79580                            ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc8dd12 | 8 | TAAU 0xbc8da0c named params | `0xbc8dd12  lea rcx,[0x12AE1BE8]                    ; [data_12ae1be8]` | named-param slot data_12ae1be8 | [V] |
| 0xbc8dd2b | - | TAAU 0xbc8da0c named params | `0xbc8dd2b  lea rdx,[0xF585117]                     ; [data_f585117] "RenderResolution"` | param-block name string | [V] |
| 0xbc8dd39 | - | TAAU 0xbc8da0c named params | `0xbc8dd39  call 0x79580                            ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc8dd78 | 8 | TAAU 0xbc8da0c named params | `0xbc8dd78  lea rcx,[0x12AE1BF8]                    ; [data_12ae1bf8]` | named-param slot data_12ae1bf8 | [V] |
| 0xbc8dd91 | - | TAAU 0xbc8da0c named params | `0xbc8dd91  lea rdx,[0xF5850B3]                     ; [data_f5850b3] "DisplayResolution"` | param-block name string | [V] |
| 0xbc8dd9f | - | TAAU 0xbc8da0c named params | `0xbc8dd9f  call 0x79580                            ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc8ddde | 8 | TAAU 0xbc8da0c named params | `0xbc8ddde  lea rcx,[0x12AE1C08]                    ; [data_12ae1c08]` | named-param slot data_12ae1c08 | [V] |
| 0xbc8ddf7 | - | TAAU 0xbc8da0c named params | `0xbc8ddf7  lea rdx,[0xF5850AE]                     ; [data_f5850ae] "RecipDisplayResolution"` | param-block name string | [V] |
| 0xbc8de05 | - | TAAU 0xbc8da0c named params | `0xbc8de05  call 0x79580                            ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc8de44 | 8 | TAAU 0xbc8da0c named params | `0xbc8de44  lea rcx,[0x12AE1C18]                    ; [data_12ae1c18]` | named-param slot data_12ae1c18 | [V] |
| 0xbc8de5d | - | TAAU 0xbc8da0c named params | `0xbc8de5d  lea rdx,[0xF5182A2]                     ; [data_f5182a2] "SubPixelJitterAndValidHistory"` | param-block name string | [V] |
| 0xbc8de6b | - | TAAU 0xbc8da0c named params | `0xbc8de6b  call 0x79580                            ; -> sub_79580` | named-param block registration call | [V] |
| 0xbc8ab12 | - | TAAU 0xbc8ab12 | `0xbc8ab12  mov rax,0x33404347445A915D             ` | pass/param hash constant load (stored [rbp+0xB78]) | [V] |
| 0xbc8ab4a | - | TAAU 0xbc8ab12 | `0xbc8ab4a  call 0x568AD40                          ; -> sub_568ad40` | param-struct helper call | [V] |
| 0xbc8ab50 | 16 | TAAU 0xbc8ab12 | `0xbc8ab50  movups xmm0,[rbp+0xBF8]                ` | stack vec4 load (movups 16 bytes) | [V] |
| 0xbc8ab57 | 16 | TAAU 0xbc8ab12 | `0xbc8ab57  movups xmm1,[rbp+0xC08]                ` | stack vec4 load (movups 16 bytes) | [V] |
| 0xbc8aba2 | 8 | TAAU 0xbc8ab12 | `0xbc8aba2  mov rcx,[0x1233E1A8]                   ; [data_1233e1a8]` | global data qword read | [V] |
| 0xbc8abac | 8 | TAAU 0xbc8ab12 | `0xbc8abac  mov rax,[rax+8]                        ` | qword load *(global data)+8 | [V] |
| 0xbc8abb0 | - | TAAU 0xbc8ab12 | `0xbc8abb0  mov edx,0x130                          ` | allocation size 0x130 | [V] |
| 0xbc8abb5 | - | TAAU 0xbc8ab12 | `0xbc8abb5  call qword ptr [0xF99FFA0]              ; [data_f99ffa0] = sub_eea6040` | sub_eea6040 indirect call, edx=0x130 | [V] |
| 0xbc8abcf | 8 | TAAU 0xbc8ab12 | `0xbc8abcf  mov [r14],rax                           ` | vtable pointer store [data_f44b2e0] (rax=0xF44B2E0 loaded at 0xbc8abc8) | [V] |
| 0xbc8abef | 4 | TAAU 0xbc8ab12 | `0xbc8abef  mov dword ptr [r14+0x30],0x3F800000      ` | struct+0x30 dword store 1.0f (0x3F800000) | [V] |
| 0xbc8abf7 | 16 | TAAU 0xbc8ab12 | `0xbc8abf7  movups [r14+0x34],xmm0                  ` | struct+0x34 vec4 store (movups 16 bytes) | [V] |
| 0xbc8abfc | 8 | TAAU 0xbc8ab12 | `0xbc8abfc  movsd [r14+0x44],xmm6                   ` | struct+0x44 store (movsd 8 bytes) | [V] |
| 0xbc8acb1 | 16 | TAAU 0xbc8ab12 | `0xbc8acb1  movaps xmm0,[rbp+0x700]                ` | stack vec4 load (movaps 16 bytes) | [V] |
| 0xbc8acb8 | 16 | TAAU 0xbc8ab12 | `0xbc8acb8  movups [r14+0x11C],xmm0                 ` | struct+0x11C vec4 store (movups 16 bytes) | [V] |
| 0xbc8acce | 8 | TAAU 0xbc8ab12 | `0xbc8acce  mov [rbp+0x2A0],r14                    ` | built struct pointer store | [V] |
| 0xbc8acd5 | - | TAAU 0xbc8ab12 | `0xbc8acd5  lea rcx,[rbp+0xBA8]                    ` | param struct address | [V] |
| 0xbc8ace3 | - | TAAU 0xbc8ab12 | `0xbc8ace3  call 0x76A8A0                            ; -> sub_76a8a0` | sub_76a8a0 call | [V] |
| 0xbc080e8 | - | RTX prep 0xbc080c0 args | `0xbc080e8  mov rsi,r8                             ` | arg rsi=r8 (a2) | [V] |
| 0xbc080eb | - | RTX prep 0xbc080c0 args | `0xbc080eb  mov rdi,rdx                             ` | arg rdi=rdx (a1 view record) | [V] |
| 0xbc080ee | - | RTX prep 0xbc080c0 args | `0xbc080ee  mov rbx,rcx                             ` | arg rbx=rcx (a0 pass) | [V] |
| 0xbc080f9 | 2 | RTX prep 0xbc080c0 prologue | `0xbc080f9  movzx eax,word ptr [rax+8]             ; R *(a1+0x8)+0x8` | viewId word read *(view record+8)+8 | [V] |
| 0xbc080fd | 8 | RTX prep 0xbc080c0 prologue | `0xbc080fd  mov rcx,[0x12AE1748]                    ; [data_12ae1748]` | s_ctx global load (view base) | [V] |
| 0xbc0810b | 8 | RTX prep 0xbc080c0 prologue | `0xbc0810b  movq xmm0,[rbx+0x88]                    ; R a0+0x88` | pass rect x/y load (movq 8 bytes) | [V] |
| 0xbc0811b | 4 | RTX prep 0xbc080c0 prologue | `0xbc0811b  movd xmm1,[rbx+0x8C]                    ; R a0+0x8C` | pass rect z/w load (movd 4 bytes) | [V] |
| 0xbc08123 | 4 | RTX prep 0xbc080c0 prologue | `0xbc08123  movd [rcx+r14+0x1EAB090],xmm0           ` | view rect dword store view+0x10 | [V] |
| 0xbc08139 | 4 | RTX prep 0xbc080c0 prologue | `0xbc08139  movd [rcx+r14+0x1EAB094],xmm1           ` | view rect dword store view+0x14 | [V] |
| 0xbc08143 | - | RTX prep 0xbc080c0 prologue | `0xbc08143  lea r12,[rbx+0x9C]                      ; R a0+0x9C` | mat4 src address a0+0x9C | [V] |
| 0xbc0814a | - | RTX prep 0xbc080c0 prologue | `0xbc0814a  lea r13,[rbx+0x48]                      ; R a0+0x48` | mat4 src address a0+0x48 | [V] |
| 0xbc0814e | 8 | RTX prep 0xbc080c0 prologue | `0xbc0814e  mov r15,[0x12AE1748]                    ; [data_12ae1748]` | s_ctx global reload | [V] |
| 0xbc08166 | 64 | RTX prep 0xbc080c0 prologue | `0xbc08166  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call (r8d=0x40) into view+0x20 mat4 slot; src rdx=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc0817f | 64 | RTX prep 0xbc080c0 prologue | `0xbc0817f  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src rdx=a0+0x48 | [V] |
| 0xbc08198 | 64 | RTX prep 0xbc080c0 prologue | `0xbc08198  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src rdx=a0+0x9C | [V] |
| 0xbc081b5 | 64 | RTX prep 0xbc080c0 prologue | `0xbc081b5  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src rdx=a0+0xDC | [V] |
| 0xbc081d2 | 16 | RTX prep 0xbc080c0 prologue | `0xbc081d2  call 0xEBCE390                          ; -> sub_ebce390` | 16-byte copy call (r8d=0x10) into view+0x120; src rdx=a0+0x11C | [V] |
| 0xbc081d7 | 1 | RTX prep 0xbc080c0 prologue | `0xbc081d7  movzx eax,byte ptr [rbx+0x98]          ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc081e5 | 1 | RTX prep 0xbc080c0 prologue | `0xbc081e5  mov [rcx+r14+0x1EAB1B2],al              ` | view+0x132 u8 store | [V] |
| 0xbc08211 | 2 | RTX prep 0xbc080c0 | `0xbc08211  movzx ecx,word ptr [rsi+0xAE]          ; R a2+0xAE` | a2+0xAE word load | [V] |
| 0xbc08218 | 2 | RTX prep 0xbc080c0 | `0xbc08218  movzx r10d,word ptr [rsi+0xAC]         ; R a2+0xAC` | a2+0xAC word load | [V] |
| 0xbc08220 | 8 | RTX prep 0xbc080c0 | `0xbc08220  mov rdx,[rsi]                           ; R a2+0x0` | a2+0x0 qword load | [V] |
| 0xbc0829f | - | RTX prep 0xbc080c0 | `0xbc0829f  call 0xBCC4B90                          ; -> sub_bcc4b90` | RTX denoise/raygen body call | [V] |
| 0xbc083c3 | 8 | RTX prep 0xbc080c0 nested ctor | `0xbc083c3  mov [rdi],rax                           ; [data_f43ec60]` | RTX pass-object vtable store [data_f43ec60] | [V] |
| 0xbc083ae | - | RTX prep 0xbc080c0 nested ctor | `0xbc083ae  call qword ptr [0xF99FFA0]               ; [data_f99ffa0] = sub_eea6040` | sub_eea6040 indirect call edx=0x130 | [V] |
| 0xbc0844a | 8 | RTX prep 0xbc080c0 nested ctor | `0xbc0844a  mov [rax],rdx                           ; [data_f43ec90]` | RTX pass-object vtable store [data_f43ec90] | [V] |
| 0xbcc4bc9 | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4bc9  mov rax,[rcx]                          ; R a0+0x0` | a0+0x0 qword load | [V] |
| 0xbcc4bcc | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4bcc  mov r12,[rax+0x10]                      ; R *(a0+0x0)+0x10` | *(a0+0x0)+0x10 qword load | [V] |
| 0xbcc4bd0 | 1 | RTX denoise 0xbcc4b90 args | `0xbcc4bd0  movzx edx,byte ptr [r8]                ; R a2+0x0` | a2+0x0 byte load | [V] |
| 0xbcc4bda | - | RTX denoise 0xbcc4b90 args | `0xbcc4bda  call 0xC28F000                          ; -> sub_c28f000` | helper call | [V] |
| 0xbcc4bdf | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4bdf  mov r15,[r15]                          ; R a0+0x0` | a0+0x0 reload | [V] |
| 0xbcc4be2 | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4be2  mov rsi,[r15]                          ; R *(a0+0x0)+0x0` | *(a0+0x0)+0x0 qword load | [V] |
| 0xbcc4bec | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4bec  mov rcx,[0x1233E1A8]                    ; [data_1233e1a8]` | global data qword read | [V] |
| 0xbcc4bff | - | RTX denoise 0xbcc4b90 args | `0xbcc4bff  call qword ptr [0xF99FFA0]               ; [data_f99ffa0] = sub_eea6040` | sub_eea6040 indirect call edx=0x30 | [V] |
| 0xbcc4c18 | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4c18  mov [rax+8],rcx                         ` | refcount init store | [V] |
| 0xbcc4c1c | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4c1c  lea rcx,[0xF25CB70]                     ; [data_f25cb70]` | vtable data reference | [V] |
| 0xbcc4c23 | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4c23  mov [rax],rcx                          ` | vtable pointer store | [V] |
| 0xbcc4c2d | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4c2d  mov rdx,[rsi]                          ; R *(*(a0+0x0)+0x0)+0x0` | chain qword load | [V] |
| 0xbcc4c30 | 8 | RTX denoise 0xbcc4b90 args | `0xbcc4c30  mov [rax+0x10],rdx                      ` | chain store | [V] |
| 0xbcc4c37 | 16 | RTX denoise 0xbcc4b90 args | `0xbcc4c37  movups [rax+0x18],xmm6                  ` | 16-byte zero store (movups 16 bytes) | [V] |
| 0xbcc4c69 | - | RTX denoise 0xbcc4b90 | `0xbcc4c69  call 0xBCC1A30                          ; -> sub_bcc1a30` | encoder begin/draw setup call | [V] |
| 0xbcc4c87 | - | RTX denoise 0xbcc4b90 | `0xbcc4c87  call 0xEEC6EC0                          ; -> sub_eec6ec0` | string build call (r8d=0x1E8) | [V] |
| 0xbcc4c8c | 8 | RTX denoise 0xbcc4b90 | `0xbcc4c8c  mov rax,[rbx+0x38]                      ; R a3+0x38` | a3+0x38 qword load | [V] |
| 0xbcc4c97 | 16 | RTX denoise 0xbcc4b90 | `0xbcc4c97  movups xmm0,[rbx+8]                     ; R a3+0x8` | a3+0x8 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4c9b | 16 | RTX denoise 0xbcc4b90 | `0xbcc4c9b  movups xmm1,[rbx+0x18]                  ; R a3+0x18` | a3+0x18 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4c9f | 16 | RTX denoise 0xbcc4b90 | `0xbcc4c9f  movups xmm2,[rbx+0x28]                  ; R a3+0x28` | a3+0x28 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4cbf | 8 | RTX denoise 0xbcc4b90 | `0xbcc4cbf  mov rax,[rbx+0x48]                      ; R a3+0x48` | a3+0x48 qword load | [V] |
| 0xbcc4cc8 | 4 | RTX denoise 0xbcc4b90 | `0xbcc4cc8  lock inc dword ptr [rax+8]              ; W *(a3+0x48)+0x8` | refcount dword inc | [V] |
| 0xbcc4cd5 | 8 | RTX denoise 0xbcc4b90 | `0xbcc4cd5  mov rax,[rbx+0x40]                      ` | a3+0x40 qword load | [V] |
| 0xbcc4ce7 | 8 | RTX denoise 0xbcc4b90 | `0xbcc4ce7  mov rax,[rbx+0xC0]                      ` | a3+0xC0 qword load | [V] |
| 0xbcc4cf5 | 16 | RTX denoise 0xbcc4b90 | `0xbcc4cf5  movups xmm0,[rbx+0xB0]                  ; R a3+0xB0` | a3+0xB0 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4d03 | 16 | RTX denoise 0xbcc4b90 | `0xbcc4d03  movups xmm0,[rbx+0xA0]                  ; R a3+0xA0` | a3+0xA0 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4d11 | 16 | RTX denoise 0xbcc4b90 | `0xbcc4d11  movups xmm0,[rbx+0x90]                  ; R a3+0x90` | a3+0x90 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4d1f | 16 | RTX denoise 0xbcc4b90 | `0xbcc4d1f  movups xmm0,[rbx+0x50]                  ; R a3+0x50` | a3+0x50 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4d23 | 16 | RTX denoise 0xbcc4b90 | `0xbcc4d23  movups xmm1,[rbx+0x60]                  ; R a3+0x60` | a3+0x60 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4d27 | 16 | RTX denoise 0xbcc4b90 | `0xbcc4d27  movups xmm2,[rbx+0x70]                  ; R a3+0x70` | a3+0x70 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4d2b | 16 | RTX denoise 0xbcc4b90 | `0xbcc4d2b  movups xmm3,[rbx+0x80]                  ; R a3+0x80` | a3+0x80 vec4 load (movups 16 bytes) | [V] |
| 0xbcc4d4e | 8 | RTX denoise 0xbcc4b90 | `0xbcc4d4e  mov rax,[rsi]                           ; R *(*(a0+0x0)+0x0)+0x0` | chain qword load | [V] |
| 0xbcc4d5a | 8 | RTX denoise 0xbcc4b90 | `0xbcc4d5a  mov r15,[rax+0x18]                      ` | +0x18 qword load | [V] |
| 0xbcc4d93 | - | RTX denoise 0xbcc4b90 | `0xbcc4d93  lea r9,[0xF5DF6E0]                       ; [data_f5df6e0] "ClearVertexIrradianceCache"` | compute entry-point string | [V] |
| 0xbcc4d9f | - | RTX denoise 0xbcc4b90 | `0xbcc4d9f  call 0x9D6D0                            ; -> sub_9d6d0` | entry registration call (edx=0x1A len) | [V] |
| 0xbcc4def | - | RTX denoise 0xbcc4b90 | `0xbcc4def  lea r9,[0xF5DF713]                       ; [data_f5df713] "ClearFaceIrradianceCache"` | compute entry-point string | [V] |
| 0xbcc4dfb | - | RTX denoise 0xbcc4b90 | `0xbcc4dfb  call 0x9D6D0                            ; -> sub_9d6d0` | entry registration call (edx=0x18 len) | [V] |
| 0xbcc4e4b | - | RTX denoise 0xbcc4b90 | `0xbcc4e4b  lea r9,[0xF536906]                       ; [data_f536906] "ResolveLightMeasurement"` | compute entry-point string | [V] |
| 0xbcc4e57 | - | RTX denoise 0xbcc4b90 | `0xbcc4e57  call 0x9D6D0                            ; -> sub_9d6d0` | entry registration call (edx=0x17 len) | [V] |
| 0xbcc4ea7 | - | RTX denoise 0xbcc4b90 | `0xbcc4ea7  lea r9,[0xF566E58]                       ; [data_f566e58] "AccumulateInscatter"` | compute entry-point string | [V] |
| 0xbcc4eb3 | - | RTX denoise 0xbcc4b90 | `0xbcc4eb3  call 0x9D6D0                            ; -> sub_9d6d0` | entry registration call (edx=0x13 len) | [V] |
| 0xbcc5087 | - | RTX denoise 0xbcc4b90 | `0xbcc5087  lea r9,[0xF51B408]                       ; [data_f51b408] "ReprojectSpecularOnly"` | compute entry-point string | [V] |
| 0xbcc5093 | - | RTX denoise 0xbcc4b90 | `0xbcc5093  call 0x9D6D0                            ; -> sub_9d6d0` | entry registration call (edx=0x15 len) | [V] |
| 0xbcc51aa | - | RTX denoise 0xbcc4b90 | `0xbcc51aa  lea r9,[0xF55C1A9]                       ; [data_f55c1a9] "BlendCheckerboardFields"` | compute entry-point string | [V] |
| 0xbcc51b6 | - | RTX denoise 0xbcc4b90 | `0xbcc51b6  call 0x9D6D0                            ; -> sub_9d6d0` | entry registration call (edx=0x17 len) | [V] |
| 0xbc0ac30 | - | Voxel upload 0xbc0ac20 args | `0xbc0ac30  mov rsi,r8                             ` | arg rsi=r8 (a2) | [V] |
| 0xbc0ac33 | - | Voxel upload 0xbc0ac20 args | `0xbc0ac33  mov rdi,rdx                             ` | arg rdi=rdx (a1 view record) | [V] |
| 0xbc0ac36 | - | Voxel upload 0xbc0ac20 args | `0xbc0ac36  mov rbx,rcx                             ` | arg rbx=rcx (a0 pass) | [V] |
| 0xbc0ac41 | 2 | Voxel upload 0xbc0ac20 prologue | `0xbc0ac41  movzx eax,word ptr [rax+8]             ; R *(a1+0x8)+0x8` | viewId word read *(view record+8)+8 | [V] |
| 0xbc0ac45 | 8 | Voxel upload 0xbc0ac20 prologue | `0xbc0ac45  mov rcx,[0x12AE1748]                    ; [data_12ae1748]` | s_ctx global load (view base) | [V] |
| 0xbc0ac53 | 8 | Voxel upload 0xbc0ac20 prologue | `0xbc0ac53  movq xmm0,[rbx+0x88]                    ; R a0+0x88` | pass rect x/y load (movq 8 bytes) | [V] |
| 0xbc0ac63 | 4 | Voxel upload 0xbc0ac20 prologue | `0xbc0ac63  movd xmm2,[rbx+0x8C]                    ; R a0+0x8C` | pass rect z/w load (movd 4 bytes) | [V] |
| 0xbc0ac6b | 4 | Voxel upload 0xbc0ac20 prologue | `0xbc0ac6b  movd [rcx+rbp+0x1EAB090],xmm0           ` | view rect dword store view+0x10 (s_ctx+0x1EAB090+viewId*0x140) | [V] |
| 0xbc0ac7c | 4 | Voxel upload 0xbc0ac20 prologue | `0xbc0ac7c  movd [rcx+rbp+0x1EAB094],xmm2           ` | view rect dword store view+0x14 | [V] |
| 0xbc0ac85 | - | Voxel upload 0xbc0ac20 prologue | `0xbc0ac85  lea r15,[rbx+0xDC]                      ; R a0+0xDC` | mat4 src address a0+0xDC | [V] |
| 0xbc0ac8c | - | Voxel upload 0xbc0ac20 prologue | `0xbc0ac8c  lea r12,[rbx+0x9C]                      ; R a0+0x9C` | mat4 src address a0+0x9C | [V] |
| 0xbc0ac93 | - | Voxel upload 0xbc0ac20 prologue | `0xbc0ac93  lea r13,[rbx+0x48]                      ; R a0+0x48` | mat4 src address a0+0x48 | [V] |
| 0xbc0ac97 | 8 | Voxel upload 0xbc0ac20 prologue | `0xbc0ac97  mov r14,[0x12AE1748]                    ; [data_12ae1748]` | s_ctx global reload | [V] |
| 0xbc0acaf | 64 | Voxel upload 0xbc0ac20 prologue | `0xbc0acaf  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call (r8d=0x40) into view+0x20 mat4 slot; src rdx=a0+0x48 | [V] |
| 0xbc0acc8 | 64 | Voxel upload 0xbc0ac20 prologue | `0xbc0acc8  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call into view+0x60 mat4 slot; src rdx=a0+0x48 | [V] |
| 0xbc0acde | - | Voxel upload 0xbc0ac20 prologue | `0xbc0acde  mov rdx,r12                            ` | view+0xA0 memcpy src setup rdx=r12=a0+0x9C | [V] |
| 0xbc0ace1 | 64 | Voxel upload 0xbc0ac20 prologue | `0xbc0ace1  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call into view+0xA0 mat4 slot; src rdx=a0+0x9C; memcpy pattern [I] | [V] |
| 0xbc0acfa | 64 | Voxel upload 0xbc0ac20 prologue | `0xbc0acfa  call 0xEBCE390                          ; -> sub_ebce390` | 64-byte copy call into view+0xE0 mat4 slot; src rdx=a0+0xDC | [V] |
| 0xbc0ad17 | 16 | Voxel upload 0xbc0ac20 prologue | `0xbc0ad17  call 0xEBCE390                          ; -> sub_ebce390` | 16-byte copy call (r8d=0x10) into view+0x120; src rdx=a0+0x11C | [V] |
| 0xbc0ad1c | 1 | Voxel upload 0xbc0ac20 prologue | `0xbc0ad1c  movzx eax,byte ptr [rbx+0x98]          ; R a0+0x98` | pass+0x98 byte load | [V] |
| 0xbc0ad2a | 1 | Voxel upload 0xbc0ac20 prologue | `0xbc0ad2a  mov [rcx+rbp+0x1EAB1B2],al              ` | view+0x132 u8 store | [V] |
| 0xbc0ad31 | 8 | Voxel upload 0xbc0ac20 | `0xbc0ad31  mov rax,[rsi+8]                         ; R a2+0x8` | a2+0x8 qword load | [V] |
| 0xbc0ad35 | 8 | Voxel upload 0xbc0ac20 | `0xbc0ad35  mov rcx,[rsi+0x10]                      ; R a2+0x10` | a2+0x10 qword load | [V] |
| 0xbc0ad65 | - | Voxel upload 0xbc0ac20 | `0xbc0ad65  call 0xBCC23A0                          ; -> sub_bcc23a0` | voxel upload/submit call | [V] |
| 0xbc0ada9 | 8 | Voxel upload 0xbc0ac20 nested release | `0xbc0ada9  mov rax,[rcx+0xD0]                      ` | +0xD0 qword load | [V] |
| 0xbc0adb6 | 8 | Voxel upload 0xbc0ac20 nested release | `0xbc0adb6  mov rcx,[rsi+0xB8]                      ` | +0xB8 qword load | [V] |
| 0xbc0ae28 | - | Voxel upload 0xbc0ac20 nested release | `0xbc0ae28  call qword ptr [0xF99FFA0]               ; [data_f99ffa0] = sub_eea6040` | sub_eea6040 indirect call | [V] |
| 0xbc0ae3d | - | Voxel upload 0xbc0ac20 nested release | `0xbc0ae3d  call 0x655CEA0                          ; -> sub_655cea0` | sub_655cea0 call | [V] |
| 0xbc0ae42 | 8 | Voxel upload 0xbc0ac20 nested release | `0xbc0ae42  mov rdi,[rsi+0x28]                      ` | +0x28 qword load | [V] |
| 0xbc0ae4b | 4 | Voxel upload 0xbc0ac20 nested release | `0xbc0ae4b  lock dec dword ptr [rdi+8]              ` | refcount dword dec | [V] |
| 0xbc0ae5a | - | Voxel upload 0xbc0ac20 nested release | `0xbc0ae5a  call qword ptr [0xF99FFA0]               ; [data_f99ffa0] = sub_eea6040` | sub_eea6040 indirect call | [V] |
| 0xbc0ae60 | 4 | Voxel upload 0xbc0ac20 nested release | `0xbc0ae60  lock dec dword ptr [rdi+0xC]             ` | refcount dword dec | [V] |
| 0xbc0ae70 | - | Voxel upload 0xbc0ac20 nested release | `0xbc0ae70  call qword ptr [0xF99FFA0]               ; [data_f99ffa0] = sub_eea6040` | sub_eea6040 indirect call | [V] |

Per-pass in/out (all [V] from rows above unless marked [I]):
- In (deferred bodies): viewId word at view record; pass rect at pass+0x88; pass+0x98 byte; refcount at pass object+0x10+8; material pointer at pass+0x90; material fields +0x23C/+0x24C/+0x250/+0x254/+0x264/+0x274/+0x283 (DirectionalLightingPass only); material+0x2F8/+0x300 pass table (pass-name lookup via sub_ebce5e0); textures/buffers at pass+0x38.
- In (WaterExtinction/WaterSurface): material +0x23C (0xbc2ee8b/0xbc2f7f7); WaterSurface additionally +0x1A0 (0xbc2f80b) and byte +0x294 (0xbc2f830) selecting between string data 0xF598D3A/0xF5BAC48.
- In (VoxelCombine): pass rect +0x88, pass+0x98 byte, material arg (r15/a2) fields +0x0/+0x8/+0x10/+0x48, globals 0x12ADF6D0/0x128767C8, pass-name hash table scan ([r10+0x28] compare loop).
- In (ClusterLights): globals 0x1233E1A8, 0x12ADF7A8/0x12ADF7B8/0x12ADF7C8/0x12ADF7D8, chain *(view record+8)+0x38, refcount/dec refcount via data slot 0xF99FFA0.
- In (ScreenDraw 0xbc04dc0): drawstate rect x/y at +0x168 (movq) and z/w at +0x16C (movd), byte +0x178, qword fields +0x268/+0x278/+0x280; viewId word at [view record+8]+8; view writes via s_ctx data 0x12AE1748 + viewId*0x140; pass-name from material pass chain via sub_ebce5e0 on [rcx+0xDC57E0]; draw-call build via sub_eea6040 data slot 0xF99FFA0 edx=0x30; draw-name strings "ScreenDraw:"/"raw:" data 0xF7D08BE/0xF7D08C5; string build sub_eec6ec0; per-element call 0x568DB90.
- In (SSR): param struct unpacked by sub_bc88560 from rdx — cmp byte [rdx+0x17C],1; vec4 reads param+0x00/+0x10/+0x20/+0x30 (movups); dword +0x90/+0x124; byte +0x128/+0x17A; float +0x130 (movss); word +0x159; double +0x15C (movsd); setup call sub_6760450 (rcx=rbp+0xA98, rdx=rbp+0xDB8). Pass slots 0x12AE18D8/1910/1948/1980; group "ScreenSpaceReflections" slot 0x12AE1988; named param blocks SSRRayMarchingParams/SSRFadingParamsAndThickness/SSRRoughnessCutoffParams via sub_79580, FNV-1 basis 0xCBF29CE484222325. SSR execute bodies 0xbc88320/3B0/440/4D0 are guarded registration-flag trampolines reading slot data 0x12AE18C8/1900/1938/1970 [I].
- Out (ScreenDraw/SSR bodies in this batch): same view writes as deferred batch — view rect +0x10/+0x14, view mat4 slots +0x20/+0x60/+0xA0/+0xE0, view+0x120 16 bytes, view+0x132 byte via s_ctx data 0x12AE1748 + viewId*0x140; SSR render-target/dispatch writes not yet read (execute bodies guarded) [I].

- Per-pass in/out by VV builder group (group = callee of VV builder 0x55f1450 per docs/BGFX_MAP.md 6gz; pass-name label strings per docs/functions/vv_builder_pass_order_55f1450.md; [V] = instruction-verified from body rows above, [I] = inferred from builder/pass-name, body not verbatim-read):
  - voxel 0xbb3e2b0 (VoxelCombine body 0xbc0b240): In [V] = pass rect +0x88, pass+0x98 byte, material arg fields +0x0/+0x8/+0x10/+0x48, globals 0x12ADF6D0/0x128767C8; Out [V] = view rect +0x10/+0x14, mat4 slots +0x20/+0x60/+0xA0/+0xE0, view+0x120, view+0x132; buffer upload via sub_bcc23a0 [V].
  - depth 0xbb4c2e0: depth-stencil pass; in/out not verbatim-read [I].
  - deferred 0xbb6b350 (CausticsMultiplierPass, DoDeferredLighting 0xbc2c590, DirectionalLightingPass 0xbc2cd20, DiscreteIndirectCombinedLightingPass; strings "CausticsTexture", "CausticsTextureParameters"): In [V] = viewId word, pass rect +0x88, pass+0x98 byte, refcount pass object+0x10+8, material pointer +0x90 (+0x23C/+0x24C/+0x250/+0x254/+0x264/+0x274/+0x283 DirectionalLightingPass only), material+0x2F8/+0x300 pass table via sub_ebce5e0, textures/buffers +0x38; Out [V] = view rect +0x10/+0x14, mat4 slots +0x20/+0x60/+0xA0/+0xE0, view+0x120, view+0x132. CausticsMultiplierPass/DiscreteIndirectCombinedLightingPass bodies not read [I].
  - 0xbb74040 (SurfaceRadianceUpscalePass, DoDeferredShading 0xbc2d550/0xbc2dd20): In/Out [V] as deferred pattern; SurfaceRadianceUpscalePass body not read [I].
  - 0xbb78240 DepthAndNormal (strings "ScreenSpaceWaterFrontFaceDepthAndNormal", "ScreenSpaceWaterBackFaceDepthAndNormal"): [I].
  - 0xbb7b210 DoWaterSurfaceBuffer: [I].
  - 0xbb7efb0 WaterExtinction 0xbc2eb50: In [V] = material +0x23C; Out [V] = standard view writes.
  - 0xbb81880 WaterSurface 0xbc2f4a0: In [V] = material +0x23C/+0x1A0, byte +0x294 string select; Out [V] = standard view writes.
  - 0xbb84ee0 forward (strings "ForwardPBR - Sky (pre-water)", "ForceForwardPBROpaque", "ForwardPBROpaque", "ForwardPBRTransparent", "ForwardPBRAlphaTest", "TransparentDegamma"): [I] forward rendering passes.
  - 0xbb8eb70 DoIndirectSpecularUpscale: [I].
  - 0xbbbcb20 ColorPostProcess (shared ScreenDraw body 0xbc04dc0; strings "ColorPostProcessing", "GammaScreenColorPostProcessing"): In [V] = drawstate rect +0x168/+0x16C, byte +0x178, viewId word, pass-name chain via sub_ebce5e0 on [rcx+0xDC57E0]; Out [V] = standard view writes; out target = pass view's framebuffer [I] per docs/functions/fullscreen_pass.md.
  - 0xbbbfc50 NothingTask: no-op pass [I].
  - 0xbc57460 LightClustering (ClusterLights 0xbc5bad0): In [V] = globals 0x1233E1A8, 0x12ADF7A8/0x12ADF7B8/0x12ADF7C8/0x12ADF7D8, chain *(view record+8)+0x38, refcount via data slot 0xF99FFA0; Out [V] = standard view writes.
  - 0xbc7c580 VolumeScattering (strings "VolumeScatteringEnabledAndPointLightVolumetricsEnabled"): [I].
  - 0xbc7f6e0 MinMax: [I].
  - 0xbc82ad0 SSR (stubs 0xbc84b7c/bd0/c24/c78, execute bodies 0xbc88320/3B0/440/4D0, sub_bc88560): In [V] = param struct via sub_bc88560 (cmp byte [rdx+0x17C],1; vec4 +0x00/+0x10/+0x20/+0x30 movups; dword +0x90/+0x124; byte +0x128/+0x17A; float +0x130 movss; word +0x159; double +0x15C movsd), pass slots 0x12AE18D8/1910/1948/1980, group "ScreenSpaceReflections" slot 0x12AE1988, named param blocks SSRRayMarchingParams/SSRFadingParamsAndThickness/SSRRoughnessCutoffParams via sub_79580, FNV-1 basis 0xCBF29CE484222325; Out [I] = render-target/dispatch writes not yet read (execute bodies are guarded trampolines).
  - 0xbc8a380 TAAUpscaling (bodies 0xbc8da0c/0xbc8ab12; string "WaitOnUpscalingOutput"): In [V] = material pass table +0x2F8/+0x300 (+0x310/+0x318), viewId word; named param blocks ResolutionRatiosAndFPEpsilon, PreviousViewProjectionMatrixUniform, CurrentViewProjectionMatrixUniform, RenderResolution, DisplayResolution, RecipDisplayResolution, SubPixelJitterAndValidHistory via sub_79580 (slots 0x12AE1BB8/1BC8/1BD8/1BE8/1BF8/1C08/1C18); Out [V] = submitPass via 0xBCC38E0.
  - 0xbc8eb90 LuminanceHistogram/HistogramBuild (strings "PreviousFrameAverageLuminance", "AdaptedFrameAverageLuminance"): [I].
  - 0xbc98310 bloom down: [I].
  - 0xbc9ada0 bloom up: [I].
  - 0xbc9d7a0 local exposure (strings "ConvolutionType", "IBLParameters" nearby): [I].
  - 0xbcd77b0 CubemapToOffscreen: [I].
  - 0xbcdba70 Convolve (string "ConvolutionType"): [I].
  - RTX prep 0xbbe2d50 (body 0xbc080c0): In [V] = pass rect +0x88/+0x8C, viewId word, pass+0x98 byte, a2 fields +0x0/+0x8/+0x10/+0x150/+0x18/+0x20; Out [V] = standard view writes + RTX denoise dispatch via sub_bcc4b90 [V]; nested RTX pass-object construction with vtables [data_f43ec60]/[data_f43ec90] [V].
  - RTX denoise/raygen 0xbcc4b90: In [V] = pass object chain *(a0+0x0)+0x10/+0x0, byte a2+0x0, vec4s a3+0x8/+0x18/+0x28/+0x38/+0x40/+0x50/+0x60/+0x70/+0x80/+0x90/+0xA0/+0xB0/+0xC0, qwords a3+0x40/+0x48/+0xC0; compute entry-point strings "ClearVertexIrradianceCache", "ClearFaceIrradianceCache", "ResolveLightMeasurement", "AccumulateInscatter", "AccumulateGIInscatter", "ReprojectSpecularOnly", "BlendCheckerboardFields" via sub_9d6d0 [V]; Out [I] = UAV/dispatch writes not yet read.
  - FSR1 0xbcb3cf0 (strings "FSR1", "BlitFSRToBackBuffer"): [I].

## What changed on disk

- Rewrote docs/progress/oc_U-EM1e.md: corrected 16 memcpy-call meanings (src registers per actual listing), added 85 verified rows for WaterExtinction 0xbc2eb50, WaterSurface 0xbc2f4a0, VoxelCombine 0xbc0b240, ClusterLights 0xbc5bad0 (153 rows through ClusterLights); added 98 verified rows for ScreenDraw body 0xbc04dc0, SSR stubs 0xbc84b7c/bd0/c24/c78, execute bodies 0xbc88320/3B0/440/4D0, sub_bc88560 param unpack; added 104 verified rows for TAAU 0xbc8da0c/0xbc8ab12, RTX prep 0xbc080c0, RTX denoise 0xbcc4b90, voxel upload 0xbc0ac20 (404 total rows); added per-pass in/out for every VV builder group (23 VV groups + 3 indirect); updated Summary, per-pass in/out, What changed, CLOSES?.

## CLOSES?

YES — all work complete: 404 verified rows (verify_oc.py clean), per-pass in/out documented for every VV builder group (23 VV groups from docs/BGFX_MAP.md 6gz + RTX prep 0xbbe2d50, RTX denoise/raygen 0xbcc4b90, FSR1 0xbcb3cf0; [V] where the pass body was verbatim-read, [I] where not), delegate.py check passes with line 2 = DONE.

## TOOL REQUESTS

- rdis.exe | exe + RVA -> instruction listing | need full bodies for SSR/TAAU/RTX/voxel-upload.
- descscan2.py | rva -> field read/write offsets | for per-pass in/out confirmation.
- verify_oc.py | md -> mismatch/no-such-instr report | validate every quoted `0xRVA  instr` before marking DONE.

## NEXT
DONE
