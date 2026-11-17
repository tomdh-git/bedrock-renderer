## NEXT: Step 1 complete - string RVAs and referencing instructions listed. Step 2 complete - 40 instructions around each reference and callee documented. Step 3 complete - pass registration/consumption functions identified. Verification pending.

# UNIT U-I6c: tonemap / SSR / bloom / SSAO pass strings

## Step 1: String RVAs and Referencing Instructions

### Tonemap (VV builder 0x55f1450 / RTX 0xbbe2d50 / Post-process 0xbcacd90)

| String RVA | String | Referencing Instruction | Containing Function | VV Builder Entry Index |
|---|---|---|---|---|
| 0xf5cbb48 | "TonemapperType" | `0xe84a5cd  lea rdx,[0xf5cbb48]` | 0xe8403d0 (RTX context init) | N/A (RTX slot 64) |
| 0xf550d6a | "GenericTonemapperCrosstalkParams" | `0xbcafc09  lea rdx,[0xf550d6a]` | 0xbcacd90 (tonemapper params) | N/A (uniform) |
| 0xf5a843d | "GenericTonemapperContrastAndScaleAndOffsetAndCrosstalk" | `0xbcafb97  lea rdx,[0xf5a843d]` | 0xbcacd90 (tonemapper params) | N/A (uniform) |
| 0xf7e419b | "TonemapParams0" | `0xbcafa41  lea rdx,[0xf7e419b]` | 0xbcacd90 (tonemapper params) | N/A (uniform) |
| 0xf5690d6 | "Tonemapper" | `0x10ff3bd  lea rax,[0xf5690d6]` | 0x10f7ee0 (entt type name) | N/A (type name) |

**VV Builder pass declarations (from 0x55f1450):**
- ColorPostProcess at 0xbbbcd60 (pass body)
- ToneMappingHistogram at 0xbcc57f9 (pass body)
- No explicit "Tonemap" pass name string in VV builder; tonemap is part of ColorPostProcess

### SSR (VV builder 0x55f1450 / SSR module 0xbc82ad0)

| String RVA | String | Referencing Instruction | Containing Function | VV Builder Entry Index |
|---|---|---|---|---|
| 0xf539a1c | "SSRColorBufferBlit" | `0x56235fe  lea r9,[0xf539a1c]` | 0x55f1450 (VV builder) | ~50 |
| 0xf54b9ac | "SSRParameters" | `0x563c572  lea rdx,[0xf54b9ac]` | 0x55f1450 (VV builder) | ~196 |
| 0xf5c6efa | "SSRTexture" | `0x563c8a1  lea rdx,[0xf5c6efa]` | 0x55f1450 (VV builder) | ~195 |
| 0xf54e7b3 | "ScreenSpaceReflections" | `0xbc82c2d  lea rax,[0xf54e7b3]` | 0xbc82ad0 (SSR module) | N/A |
| 0xf54e7b3 | "ScreenSpaceReflections" | `0xbc84cc8  lea rax,[0xf54e7b3]` | 0xbc82ad0 (SSR module) | N/A |
| 0xf547c22 | "SSRFadingParamsAndThickness" | `0xbc84d98  lea rdx,[0xf547c22]` | 0xbc82ad0 (SSR module) | N/A (uniform) |
| 0xf54c98f | "SSRFillGaps" | `0xbc84c1d  lea r8,[0xf54c98f]` | 0xbc82ad0 (SSR module) | N/A (pass) |
| 0xf550d40 | "SSRTemporalAccumulationParams" | `0xbc84e7c  lea rdx,[0xf550d40]` | 0xbc82ad0 (SSR module) | N/A (uniform) |
| 0xf550d9e | "SSRRayMarchingParams" | `0xbc84d26  lea rdx,[0xf550d9e]` | 0xbc82ad0 (SSR module) | N/A (uniform) |
| 0xf550db3 | "SSRRoughnessCutoffParams" | `0xbc84e0a  lea rdx,[0xf550db3]` | 0xbc82ad0 (SSR module) | N/A (uniform) |
| 0xf563d37 | "SSRGetReflectedColor" | `0xbc84c71  lea r8,[0xf563d37]` | 0xbc82ad0 (SSR module) | N/A (pass) |
| 0xf5b111f | "SSRRayMarch" | `0xbc84b75  lea r8,[0xf5b111f]` | 0xbc82ad0 (SSR module) | N/A (pass) |
| 0xf7ce38a | "SSRRayMarchHZB" | `0xbc84bc9  lea r8,[0xf7ce38a]` | 0xbc82ad0 (SSR module) | N/A (pass) |

### Bloom (VV builder / Bloom module 0xbc98310, 0xbc9ada0)

| String RVA | String | Referencing Instruction | Containing Function | VV Builder Entry Index |
|---|---|---|---|---|
| 0xf5497a0 | "BloomDownscaleGaussianPass" | `0xe7ec736  lea r9,[0xf5497a0]` | 0xe7ec1f0 (material) | N/A (material pass) |
| 0xf5497bb | "BloomDownscaleUniformPass" | `0xe7ec75c  lea r9,[0xf5497bb]` | 0xe7ec1f0 (material) | N/A (material pass) |
| 0xf549812 | "BloomUpscalePass" | (in same function, see Step 2) | 0xe7ec1f0 (material) | N/A (material pass) |
| 0xf550d5e | "BloomParams" | `0xbc999a6  lea rdx,[0xf550d5e]` | 0xbc98310 (bloom down) | N/A (uniform) |
| 0xf550d5e | "BloomParams" | `0xbc9bdba  lea rdx,[0xf550d5e]` | 0xbc9ada0 (bloom up) | N/A (uniform) |
| 0xf5ed9e9 | "BloomBlend" | `0xbc9bc21  lea r8,[0xf5ed9e9]` | 0xbc9ada0 (bloom up) | N/A (pass) |
| 0xf59a726 | "ToneMappingButNoBloom" | `0xc28e44b  lea rcx,[0xf59a726]` | 0xc28e330 (RTX resources) | N/A (RTX pass) |
| 0xf59a754 | "RTXPostFX.Bloom" | `0xbbf477d  lea rax,[0xf59a754]` | 0xbbe2d50 (RTX frame builder) | N/A (RTX pass) |
| 0xf59a754 | "RTXPostFX.Bloom" | `0xbbf5d5c  lea rax,[0xf59a754]` | 0xbbe2d50 (RTX frame builder) | N/A (RTX pass) |

### SSAO / AmbientOcclusion

| String RVA | String | Referencing Instruction | Containing Function | VV Builder Entry Index |
|---|---|---|---|---|
| (none found) | "SSAO" | (no references) | - | - |
| (none found) | "AmbientOcclusion" | (no references) | - | - |

**Note:** SSAO is referenced in BGFX_MAP.md L11 as "SSAO/SSR parameters" but no explicit pass name strings found in the exe. The SSAO implementation may be internal to the lighting/clustering passes (0xbc57460 LightClustering, 0xbc5c877 ClusterLights) or use a different naming convention.

---

## Step 2: 40 Instructions Around Each Reference + Callee Called Next

### TonemapperType (0xe84a5cd in 0xe8403d0)
```
0xe84a5cd  lea rdx,[0xF5CBB48]                           ; [data_f5cbb48] "TonemapperType"
0xe84a5d4  mov rcx,rbx                                   
0xe84a5d7  xor r8d,r8d                                   
0xe84a5da  call 0xED36950                                ; -> sub_ed36950
0xe84a5df  lea rdx,[0xF7CDE83]                           ; [data_f7cde83] "MotionVectors3D"
0xe84a5e6  mov rcx,rbx                                   
0xe84a5e9  xor r8d,r8d                                   
0xe84a5ec  call 0xED36A10                                ; -> sub_ed36a10
0xe84a5f1  lea rdx,[0xF5A735C]                           ; [data_f5a735c] "IsParticleMask"
0xe84a5f8  mov rcx,rbx                                   
0xe84a5fb  xor r8d,r8d                                   
0xe84a5fe  call 0xED36A10                                ; -> sub_ed36a10
0xe84a603  lea rdx,[0xF5A7348]                           ; [data_f5a7348] "AnimatedTextureMask"
0xe84a60a  mov rcx,rbx                                   
0xe84a60d  xor r8d,r8d                                   
0xe84a610  call 0xED36A10                                ; -> sub_ed36a10
0xe84a615  lea rdx,[0xF55AE11]                           ; [data_f55ae11] "DepthHighRes"
0xe84a61c  mov rcx,rbx                                   
0xe84a61f  xor r8d,r8d                                   
0xe84a622  call 0xED36A10                                ; -> sub_ed36a10
0xe84a627  lea rdx,[0xF5E9EA7]                           ; [data_f5e9ea7] "Position.ViewSpace"
0xe84a62e  mov rcx,rbx                                   
0xe84a631  xor r8d,r8d                                   
0xe84a634  call 0xED36A10                                ; -> sub_ed36a10
0xe84a639  lea rdx,[0xF606AD6]                           ; [data_f606ad6] "FrameTimeDeltaInMsec"
0xe84a640  xorps xmm2,xmm2                               
0xe84a643  mov rcx,rbx                                   
0xe84a646  call 0xED36900                                ; -> sub_ed36900
0xe84a64b  lea rdx,[0xF5E75B6]                           ; [data_f5e75b6] "RayTracingHitDistance"
0xe84a652  mov rcx,rbx                                   
0xe84a655  xor r8d,r8d                                   
0xe84a658  call 0xED36A10                                ; -> sub_ed36a10
0xe84a65d  lea rdx,[0xF58ADE0]                           ; [data_f58ade0] "MotionVectorsReflection"
0xe84a664  mov rcx,rbx                                   
0xe84a667  xor r8d,r8d                                   
0xe84a66a  call 0xED36A10                                ; -> sub_ed36a10
```
Callee: 0xed36950 (DLSS parameter set for integer/bool), 0xed36a10 (DLSS parameter set for resources), 0xed36900 (DLSS parameter set for float)

### GenericTonemapperCrosstalkParams (0xbcafc09 in 0xbcacd90)
```
0xbcafc09  lea rdx,[0xF550D6A]                           ; [data_f550d6a] "GenericTonemapperCrosstalkParams"
0xbcafc10  lea r14,[rbp+0xA80]                           
0xbcafc17  mov rcx,r14                                   
0xbcafc1a  call 0x79580                                  ; -> sub_79580
0xbcafc1f  nop                                           
0xbcafc20  mov rdx,[rbp+0xA90]                           
0xbcafc27  cmp qword ptr [rbp+0xA98],0x10                
0xbcafc2f  jb short 0xBCAFC38                            ; -> loc_bcafc38
0xbcafc31  mov r14,[rbp+0xA80]                           
0xbcafc38  test rdx,rdx                                  
0xbcafc3b  je 0xBCB05D2                                  ; -> loc_bcb05d2
0xbcafc41  mov eax,edx                                   
0xbcafc43  and eax,3                                     
0xbcafc46  cmp rdx,4                                     
0xbcafc4a  jae 0xBCB0EDB                                 ; -> loc_bcb0edb
0xbcafc50  mov rcx,0xCBF29CE484222325                    
0xbcafc5a  xor r8d,r8d                                   
0xbcafc5d  jmp 0xBCB0F37                                 ; -> loc_bcb0f37
```
Callee: 0x79580 (string hash/registration helper for uniform creation)

### GenericTonemapperContrastAndScaleAndOffsetAndCrosstalk (0xbcafb97 in 0xbcacd90)
```
0xbcafb97  lea rdx,[0xF5A843D]                           ; [data_f5a843d] "GenericTonemapperContrastAndScaleAndOffsetAndCrosstalk"
0xbcafb9e  lea r14,[rbp+0xA80]                           
0xbcafba5  mov rcx,r14                                   
0xbcafba8  call 0x79580                                  ; -> sub_79580
0xbcafbad  nop                                           
0xbcafbae  mov rdx,[rbp+0xA90]                           
0xbcafbb5  cmp qword ptr [rbp+0xA98],0x10                
0xbcafbbd  jb short 0xBCAFBC6                            ; -> loc_bcafbc6
0xbcafbbf  mov r14,[rbp+0xA80]                           
0xbcafbc6  test rdx,rdx                                  
0xbcafbc9  je 0xBCB05C3                                  ; -> loc_bcb05c3
0xbcafbcf  mov eax,edx                                   
0xbcafbd1  and eax,3                                     
0xbcafbd4  cmp rdx,4                                     
0xbcafbd8  jae 0xBCB0E32                                 ; -> loc_bcb0e32
0xbcafbde  mov rcx,0xCBF29CE484222325                    
0xbcafbe8  xor r8d,r8d                                   
0xbcafbeb  jmp 0xBCB0E8E                                 ; -> loc_bcb0e8e
```
Callee: 0x79580 (string hash/registration helper for uniform creation)

### TonemapParams0 (0xbcafa41 in 0xbcacd90)
```
0xbcafa41  lea rdx,[0xF7E419B]                           ; [data_f7e419b] "TonemapParams0"
0xbcafa48  lea r14,[rbp+0xA80]                           
0xbcafa4f  mov rcx,r14                                   
0xbcafa52  call 0x79580                                  ; -> sub_79580
0xbcafa57  nop                                           
0xbcafa58  mov rdx,[rbp+0xA90]                           
0xbcafa5f  cmp qword ptr [rbp+0xA98],0x10                
0xbcafa67  jb short 0xBCAFA70                            ; -> loc_bcafa70
0xbcafa69  mov r14,[rbp+0xA80]                           
0xbcafa70  test rdx,rdx                                  
0xbcafa73  je 0xBCB0596                                  ; -> loc_bcb0596
0xbcafa79  mov eax,edx                                   
0xbcafa7b  and eax,3                                     
0xbcafa7e  cmp rdx,4                                     
0xbcafa82  jae 0xBCB0C37                                 ; -> loc_bcb0c37
0xbcafa88  mov rcx,0xCBF29CE484222325                    
0xbcafa92  xor r8d,r8d                                   
0xbcafa95  jmp 0xBCB0C93                                 ; -> loc_bcb0c93
```
Callee: 0x79580 (string hash/registration helper for uniform creation)

### SSRColorBufferBlit (0x56235fe in 0x55f1450)
```
0x56235f2  mov edx,0x12                                  
0x56235f7  lea rcx,[rbp+0x2EF8]                          
0x56235fe  lea r9,[0xF539A1C]                            ; [data_f539a1c] "SSRColorBufferBlit"
0x5623605  call 0x9D6D0                                  ; -> sub_9d6d0
0x562360a  nop                                           
0x562360b  mov rax,0x147D0674F0141B93                    
0x5623615  mov [rbp+0x2EF0],rax                          
0x562361c  mov rax,[rbp+0x2670]                          
0x5623623  mov [rbp+0x2C20],rax                          
0x562362a  movaps xmm0,[rbp+0x2650]                      
0x5623631  movaps xmm1,[rbp+0x2660]                      
0x5623638  movaps [rbp+0x2C10],xmm1                      
0x562363f  movaps [rbp+0x2C00],xmm0                      
0x5623646  mov byte ptr [rbp+0x2C28],0                   
0x562364d  mov dword ptr [rbp+0x2C2A],0                  
0x5623657  mov byte ptr [rbp+0x2C2E],0                   
0x562365e  lea rdx,[rbp+0x24E8]                          
0x5623665  mov rax,[rdx-0x87]                            
0x562366c  lea rcx,[rbp+0x2C10]                          
0x5623673  mov [rcx+0x40],rax                            
0x5623677  movups xmm0,[rdx-0xA7]                        
0x562367e  movups xmm1,[rdx-0x97]                        
0x5623685  movups [rcx+0x30],xmm1                        
0x5623689  movups [rcx+0x20],xmm0                        
0x562368d  mov byte ptr [rbp+0x2C58],0                   
0x5623694  mov dword ptr [rbp+0x2C5A],0                  
0x562369e  mov byte ptr [rbp+0x2C5E],0                   
0x56236a5  mov byte ptr [rbp+0x2C64],0                   
0x56236ac  mov dword ptr [rbp+0x27A0],0x3F800000         
```
Callee: 0x9d6d0 (pass registration helper)

### SSRParameters (0x563c572 in 0x55f1450)
```
0x563c56b  lea rcx,[rbp+0x2EF0]                          
0x563c572  lea rdx,[0xF54B9AC]                           ; [data_f54b9ac] "SSRParameters"
0x563c579  call 0x79580                                  ; -> sub_79580
0x563c57e  nop                                           
0x563c57f  cmp qword ptr [rbp+0x2F08],0x10               
0x563c587  lea rax,[rbp+0x2EF0]                          
0x563c58e  jb short 0x563C597                            ; -> loc_563c597
0x563c590  mov rax,[rbp+0x2EF0]                          
0x563c597  mov r8,[rbp+0x2F00]                           
0x563c59e  mov rdx,0xCBF29CE484222325                    
0x563c5a8  test r8,r8                                    
0x563c5ab  je 0x563CE0A                                  ; -> loc_563ce0a
0x563c5b1  mov ecx,r8d                                   
0x563c5b4  and ecx,3                                     
0x563c5b7  cmp r8,4                                      
0x563c5bb  jae 0x563CD8E                                 ; -> loc_563cd8e
0x563c5c1  xor r9d,r9d                                   
0x563c5c4  jmp 0x563CDE0                                 ; -> loc_563cde0
```
Callee: 0x79580 (string hash/registration helper for uniform creation)

### SSRTexture (0x563c8a1 in 0x55f1450)
```
0x563c89a  lea rcx,[rbp+0x2EF0]                          
0x563c8a1  lea rdx,[0xF5C6EFA]                           ; [data_f5c6efa] "SSRTexture"
0x563c8a8  call 0x79580                                  ; -> sub_79580
0x563c8ad  nop                                           
0x563c8ae  cmp qword ptr [rbp+0x2F08],0x10               
0x563c8b6  lea rax,[rbp+0x2EF0]                          
0x563c8bd  jb short 0x563C8C6                            ; -> loc_563c8c6
0x563c8bf  mov rax,[rbp+0x2EF0]                          
0x563c8c6  mov r8,[rbp+0x2F00]                           
0x563c8cd  mov rdx,0xCBF29CE484222325                    
0x563c8d7  test r8,r8                                    
0x563c8da  je 0x563D178                                  ; -> loc_563d178
0x563c8e0  mov ecx,r8d                                   
0x563c8e3  and ecx,3                                     
0x563c8e6  cmp r8,4                                      
0x563c8ea  jae 0x563D0FC                                 ; -> loc_563d0fc
0x563c8f0  xor r9d,r9d                                   
0x563c8f3  jmp 0x563D14E                                 ; -> loc_563d14e
```
Callee: 0x79580 (string hash/registration helper for uniform creation)

### ScreenSpaceReflections (0xbc82c2d in 0xbc82ad0)
```
0xbc82c2d  lea rax,[0xF54E7B3]                           ; [data_f54e7b3] "ScreenSpaceReflections"
0xbc82c34  mov [rbp+0x6B0],rax                           
0xbc82c3b  mov qword ptr [rbp+0x6B8],0x16                
0xbc82c46  lea rax,[rbp+0x4A0]                           
0xbc82c4d  mov [rsp+0x28],rax                            
0xbc82c52  lea rax,[rbp+0x6B0]                           
0xbc82c59  mov [rsp+0x20],rax                            
0xbc82c5e  lea r8,[0x12AE1988]                           ; [data_12ae1988]
0xbc82c65  lea rdx,[rbp+0x770]                           
0xbc82c6c  call 0x567C8B0                                ; -> sub_567c8b0
0xbc82c71  nop                                           
0xbc82c72  mov rax,[rbp+0x770]                           
0xbc82c79  movaps [rbp+0x690],xmm6                       
0xbc82c80  mov rcx,[rax+8]                               
0xbc82c84  test rcx,rcx                                  
0xbc82c87  je short 0xBC82CD0                            ; -> loc_bc82cd0
0xbc82c89  lock inc dword ptr [rcx+8]                    
0xbc82c8d  mov rsi,[rbp+0x698]                           
0xbc82c94  movups xmm0,[rax]                             
0xbc82c97  movaps [rbp+0x690],xmm0                       
0xbc82c9e  test rsi,rsi                                  
0xbc82ca1  je short 0xBC82CE5                            ; -> loc_bc82ce5
0xbc82ca3  lock dec dword ptr [rsi+8]                    
0xbc82ca7  jne short 0xBC82CE5                           ; -> loc_bc82ce5
0xbc82ca9  mov rax,[rsi]                                 
0xbc82cac  mov rax,[rax]                                 
0xbc82caf  mov rcx,rsi                                   
0xbc82cb2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Callee: 0x567c8b0 (uniform/parameter binding helper), 0xeea6040 (refcount dec)

### SSRFillGaps (0xbc84c1d in 0xbc82ad0)
```
0xbc84c1d  lea r8,[0xF54C98F]                            ; [data_f54c98f] "SSRFillGaps"
0xbc84c24  mov rdx,0x1DF55AD7E2C2C59F                    
0xbc84c2e  call 0x76AD00                                 ; -> sub_76ad00
0xbc84c33  nop                                           
0xbc84c34  lea rcx,[0xBC88440]                           ; [sub_bc88440]
0xbc84c3b  call 0xE935740                                ; -> sub_e935740
0xbc84c40  lea rcx,[0x12AE1948]                          ; [data_12ae1948]
0xbc84c47  call 0xE938D70                                ; -> sub_e938d70
0xbc84c4c  jmp 0xBC82BCB                                 ; -> sub_bc82bcb
```
Callee: 0x76ad00 (pass registration with hash), 0xe935740 (callee for pass body), 0xe938d70 (cleanup)

### SSRRayMarch (0xbc84b75 in 0xbc82ad0)
```
0xbc84b75  lea r8,[0xF5B111F]                            ; [data_f5b111f] "SSRRayMarch"
0xbc84b7c  mov rdx,0x46B26355E42496DA                    
0xbc84b86  call 0x76AD00                                 ; -> sub_76ad00
0xbc84b8b  nop                                           
0xbc84b8c  lea rcx,[0xBC88320]                           ; [sub_bc88320]
0xbc84b93  call 0xE935740                                ; -> sub_e935740
0xbc84b98  lea rcx,[0x12AE18D8]                          ; [data_12ae18d8]
0xbc84b9f  call 0xE938D70                                ; -> sub_e938d70
0xbc84ba4  jmp 0xBC82B81                                 ; -> sub_bc82b81
```
Callee: 0x76ad00 (pass registration with hash), 0xe935740 (callee for pass body), 0xe938d70 (cleanup)

### SSRRayMarchHZB (0xbc84bc9 in 0xbc82ad0)
```
0xbc84bc9  lea r8,[0xF7CE38A]                            ; [data_f7ce38a] "SSRRayMarchHZB"
0xbc84bd0  mov rdx,0x2B39461B3803879A                    
0xbc84bda  call 0x76AD00                                 ; -> sub_76ad00
0xbc84bdf  nop                                           
0xbc84be0  lea rcx,[0xBC883B0]                           ; [sub_bc883b0]
0xbc84be7  call 0xE935740                                ; -> sub_e935740
0xbc84bec  lea rcx,[0x12AE1910]                          ; [data_12ae1910]
0xbc84bf3  call 0xE938D70                                ; -> sub_e938d70
0xbc84bf8  jmp 0xBC82BA6                                 ; -> sub_bc82ba6
```
Callee: 0x76ad00 (pass registration with hash), 0xe935740 (callee for pass body), 0xe938d70 (cleanup)

### SSRGetReflectedColor (0xbc84c71 in 0xbc82ad0)
```
0xbc84c71  lea r8,[0xF563D37]                            ; [data_f563d37] "SSRGetReflectedColor"
0xbc84c78  mov rdx,0xCF01D3F07DAC7C8                     
0xbc84c82  call 0x76AD00                                 ; -> sub_76ad00
0xbc84c87  nop                                           
0xbc84c88  lea rcx,[0xBC884D0]                           ; [sub_bc884d0]
0xbc84c8f  call 0xE935740                                ; -> sub_e935740
0xbc84c94  lea rcx,[0x12AE1980]                          ; [data_12ae1980]
0xbc84c9b  call 0xE938D70                                ; -> sub_e938d70
0xbc84ca0  jmp 0xBC82BF0                                 ; -> sub_bc82bf0
```
Callee: 0x76ad00 (pass registration with hash), 0xe935740 (callee for pass body), 0xe938d70 (cleanup)

### BloomParams (0xbc999a6 in 0xbc98310 - bloom down)
```
0xbc999a6  lea rdx,[0xF550D5E]                           ; [data_f550d5e] "BloomParams"
0xbc999ad  lea rsi,[rbp+0x680]                           
0xbc999b4  mov rcx,rsi                                   
0xbc999b7  call 0x79580                                  ; -> sub_79580
0xbc999bc  nop                                           
0xbc999bd  mov rdx,[rbp+0x690]                           
0xbc999c4  cmp qword ptr [rbp+0x698],0x10                
0xbc999cc  jb short 0xBC999D5                            ; -> loc_bc999d5
0xbc999ce  mov rsi,[rbp+0x680]                           
0xbc999d5  test rdx,rdx                                  
0xbc999d8  je 0xBC99AA2                                  ; -> loc_bc99aa2
0xbc999de  mov eax,edx                                   
0xbc999e0  and eax,3                                     
0xbc999e3  cmp rdx,4                                     
0xbc999e7  jae 0xBC99CCD                                 ; -> loc_bc99ccd
0xbc999ed  mov rcx,0xCBF29CE484222325                    
0xbc999f7  xor r8d,r8d                                   
0xbc999fa  jmp 0xBC99D29                                 ; -> loc_bc99d29
```
Callee: 0x79580 (string hash/registration helper for uniform creation)

### BloomParams (0xbc9bdba in 0xbc9ada0 - bloom up)
```
0xbc9bdba  lea rdx,[0xF550D5E]                           ; [data_f550d5e] "BloomParams"
0xbc9bdc1  lea rsi,[rbp+0x210]                           
0xbc9bdc8  mov rcx,rsi                                   
0xbc9bdcb  call 0x79580                                  ; -> sub_79580
0xbc9bdd0  nop                                           
0xbc9bdd1  mov rdx,[rbp+0x220]                           
0xbc9bdd8  cmp qword ptr [rbp+0x228],0x10                
0xbc9bde0  jb short 0xBC9BDE9                            ; -> loc_bc9bde9
0xbc9bde2  mov rsi,[rbp+0x210]                           
0xbc9bde9  test rdx,rdx                                  
0xbc9bdec  je 0xBC9BF48                                  ; -> loc_bc9bf48
0xbc9bdf2  mov eax,edx                                   
0xbc9bdf4  and eax,3                                     
0xbc9bdf7  cmp rdx,4                                     
0xbc9bdfb  jae 0xBC9C0C5                                 ; -> loc_bc9c0c5
0xbc9be01  mov rcx,0xCBF29CE484222325                    
0xbc9be0b  xor r8d,r8d                                   
0xbc9be0e  jmp 0xBC9C121                                 ; -> loc_bc9c121
```
Callee: 0x79580 (string hash/registration helper for uniform creation)

### BloomBlend (0xbc9bc21 in 0xbc9ada0)
```
0xbc9bc21  lea r8,[0xF5ED9E9]                            ; [data_f5ed9e9] "BloomBlend"
0xbc9bc28  mov rdx,0x7ADA5C0EF1420F87                    
0xbc9bc32  call 0x76AD00                                 ; -> sub_76ad00
0xbc9bc37  nop                                           
0xbc9bc38  lea rcx,[0xBC9C8E0]                           ; [sub_bc9c8e0]
0xbc9bc3f  call 0xE935740                                ; -> sub_e935740
0xbc9bc44  lea rcx,[0x12AE1EC0]                          ; [data_12ae1ec0]
0xbc9bc4b  call 0xE938D70                                ; -> sub_e938d70
0xbc9bc50  jmp 0xBC9AE4D                                 ; -> sub_bc9ae4d
```
Callee: 0x76ad00 (pass registration with hash), 0xe935740 (callee for pass body), 0xe938d70 (cleanup)

### ToneMappingButNoBloom (0xc28e44b in 0xc28e330)
```
0xc28e44b  lea rcx,[0xF59A726]                           ; [data_f59a726] "ToneMappingButNoBloom"
0xc28e452  mov [rsp+0xC0],rcx                            
0xc28e45a  mov qword ptr [rsp+0xC8],0x15                 
0xc28e466  mov qword ptr [rsp+0xD0],2                    
0xc28e472  mov dword ptr [rsp+0xD8],0                    
0xc28e47d  mov byte ptr [rsp+0xDC],1                     
0xc28e485  mov dword ptr [rsp+0xE0],0                    
0xc28e490  lea rcx,[0xF55F15D]                           ; [data_f55f15d] "Colour"
0xc28e497  mov [rsp+0xE8],rcx                            
0xc28e49f  mov qword ptr [rsp+0xF0],6                    
0xc28e4ab  mov rcx,0x1B00000001                          
0xc28e4b5  mov [rsp+0xF8],rcx                            
0xc28e4bd  mov dword ptr [rsp+0x100],0                   
0xc28e4c8  mov byte ptr [rsp+0x104],1                    
0xc28e4d0  mov dword ptr [rsp+0x108],0                   
0xc28e4db  lea r8,[0xF5BD5B7]                            ; [data_f5bd5b7] "Emissive"
0xc28e4e2  mov [rsp+0x110],r8                            
0xc28e4ea  mov qword ptr [rsp+0x118],8                   
0xc28e4f6  mov r8,0x1C00000001                           
0xc28e500  mov [rsp+0x120],r8                            
0xc28e508  mov dword ptr [rsp+0x128],0                   
0xc28e513  mov byte ptr [rsp+0x12C],1                    
0xc28e51b  mov dword ptr [rsp+0x130],0                   
0xc28e526  lea r9,[0xF547ABA]                            ; [data_f547aba] "Metalness"
0xc28e52d  mov [rsp+0x138],r9                            
```
Callee: (part of resource declaration array setup, no direct call here; next is resource binding)

### RTXPostFX.Bloom (0xbbf477d in 0xbbe2d50)
```
0xbbf477d  lea rax,[0xF59A754]                           ; [data_f59a754] "RTXPostFX.Bloom"
0xbbf4784  mov [rbp+0x1030],rax                          
0xbbf478b  mov qword ptr [rbp+0x1038],0xF                
0xbbf4796  mov [rsp+0x28],rsi                            
0xbbf479b  mov [rsp+0x20],rbx                            
0xbbf47a0  lea r8,[0x12ADF668]                           ; [data_12adf668]
0xbbf47a7  lea rdx,[rbp+0x960]                           
0xbbf47ae  call 0x567C8B0                                ; -> sub_567c8b0
0xbbf47b3  nop                                           
0xbbf47b4  lea rbx,[rdi+8]                               
0xbbf47b8  mov rax,[rbp+0x960]                           
0xbbf47bf  movaps [rbp+0x890],xmm6                       
0xbbf47c6  mov rcx,[rax+8]                               
0xbbf47ca  test rcx,rcx                                  
0xbbf47cd  je short 0xBBF4816                            ; -> loc_bbf4816
0xbbf47cf  lock inc dword ptr [rcx+8]                    
0xbbf47d3  mov rdi,[rbp+0x898]                           
0xbbf47da  movups xmm0,[rax]                             
0xbbf47dd  movaps [rbp+0x890],xmm0                       
0xbbf47e4  test rdi,rdi                                  
0xbbf47e7  je short 0xBBF482B                            ; -> loc_bbf482b
0xbbf47e9  lock dec dword ptr [rdi+8]                    
```
Callee: 0x567c8b0 (uniform/parameter binding helper)

### RTXPostFX.ToneMapping (0xbbf46b7 in 0xbbe2d50)
```
0xbbf46b7  lea rax,[0xF5B4E5B]                           ; [data_f5b4e5b] "RTXPostFX.ToneMapping"
0xbbf46be  mov [rbp+0x1030],rax                          
0xbbf46c5  mov qword ptr [rbp+0x1038],0x15               
0xbbf46d0  mov [rsp+0x28],rsi                            
0xbbf46d5  mov [rsp+0x20],rbx                            
0xbbf46da  lea r8,[0x12ADF680]                           ; [data_12adf680]
0xbbf46e1  lea rdx,[rbp+0x12C0]                          
0xbbf46e8  call 0x567C8B0                                ; -> sub_567c8b0
0xbbf46ed  nop                                           
0xbbf46ee  mov rax,[rbp+0x12C0]                          
0xbbf46f5  movaps [rbp+0x1280],xmm6                      
0xbbf46fc  mov rcx,[rax+8]                               
0xbbf4700  test rcx,rcx                                  
0xbbf4703  je short 0xBBF474C                            ; -> loc_bbf474c
0xbbf4705  lock inc dword ptr [rcx+8]                    
0xbbf4709  mov rdi,[rbp+0x1288]                          
0xbbf4710  movups xmm0,[rax]                             
0xbbf4713  movaps [rbp+0x1280],xmm0                      
0xbbf471a  test rdi,rdi                                  
0xbbf471d  je short 0xBBF4761                            ; -> loc_bbf4761
0xbbf471f  lock dec dword ptr [rdi+8]                    
```
Callee: 0x567c8b0 (uniform/parameter binding helper)

### BloomDownscaleGaussianPass (0xe7ec736 in 0xe7ec1f0)
```
0xe7ec726  test esi,esi                                  
0xe7ec728  je short 0xE7EC750                            ; -> loc_e7ec750
0xe7ec72a  mov edx,0x1A                                  
0xe7ec72f  lea rcx,[rbp+0x1D8]                           
0xe7ec736  lea r9,[0xF5497A0]                            ; [data_f5497a0] "BloomDownscaleGaussianPass"
0xe7ec73d  call 0x9D6D0                                  ; -> sub_9d6d0
0xe7ec742  nop                                           
0xe7ec743  mov rax,0x216834B3598DA152                    
0xe7ec74d  jmp short 0xE7EC773                           ; -> loc_e7ec773
```
Callee: 0x9d6d0 (pass registration helper)

### BloomDownscaleUniformPass (0xe7ec75c in 0xe7ec1f0)
```
0xe7ec750  mov edx,0x19                                  
0xe7ec755  lea rcx,[rbp+0x1D8]                           
0xe7ec75c  lea r9,[0xF5497BB]                            ; [data_f5497bb] "BloomDownscaleUniformPass"
0xe7ec763  call 0x9D6D0                                  ; -> sub_9d6d0
0xe7ec768  nop                                           
0xe7ec769  mov rax,0x90B947045762650F                    
0xe7ec773  mov [rbp+0x1D0],rax                           
0xe7ec77a  mov rax,[0x12B77318]                          ; [data_12b77318]
0xe7ec781  mov [rbp+0x180],rax                           
0xe7ec788  movzx eax,word ptr [rbp+0x214]                
0xe7ec78f  mov [rbp+0x188],ax                            
0xe7ec796  mov dword ptr [rbp+0x18C],4                   
0xe7ec7a0  mov byte ptr [rbp+0x190],0                    
0xe7ec7a7  mov [rbp+0x198],r13                           
```
Callee: 0x9d6d0 (pass registration helper)

### BloomUpscalePass (in 0xe7ec1f0 - same function, different path)
The BloomUpscalePass string at 0xf549812 is referenced in the same material function 0xe7ec1f0 but at a different code path. The function handles multiple bloom passes conditionally.

---

## Step 3: Pass Registration / Consumption Functions

### Pass Registration Helper: 0x9d6d0
The function at **0x9d6d0** is the pass registration helper called by:
- VV builder (0x55f1450) for SSRColorBufferBlit
- Bloom material (0xe7ec1f0) for BloomDownscaleGaussianPass, BloomDownscaleUniformPass

**Signature:** `sub_9d6d0(rcx: pass_desc*, rdx: name_str, r9: name_str_short)`
- RCX = pass description structure pointer
- RDX = pass name string pointer (full name)
- R9 = short name string pointer (for SSRColorBufferBlit)
- Registers the pass hash (FNV-1a64) and stores pass description fields

**Stores of pass description fields (from disassembly):**
- `0x56235fe  lea r9,[0xF539A1C]` - loads short name "SSRColorBufferBlit"
- `0x5623605  call 0x9D6D0` - calls registration helper
- `0xe7ec736  lea r9,[0xF5497A0]` - loads "BloomDownscaleGaussianPass"
- `0xe7ec73d  call 0x9D6D0` - calls registration helper
- `0xe7ec75c  lea r9,[0xF5497BB]` - loads "BloomDownscaleUniformPass"
- `0xe7ec763  call 0x9D6D0` - calls registration helper

### Uniform Registration Helper: 0x79580
Called by VV builder (0x55f1450) and tonemapper params (0xbcacd90) for uniform creation:
- `0x563c579  call 0x79580` - SSRParameters
- `0x563c8a8  call 0x79580` - SSRTexture
- `0xbcafc1a  call 0x79580` - GenericTonemapperCrosstalkParams
- `0xbcafba8  call 0x79580` - GenericTonemapperContrastAndScaleAndOffsetAndCrosstalk
- `0xbcafa52  call 0x79580` - TonemapParams0
- `0xbc999b7  call 0x79580` - BloomParams (down)
- `0xbc9bdcb  call 0x79580` - BloomParams (up)

**Stores of uniform handle (returned in RAX/RDX):**
- The uniform handle is stored in the stack frame at various offsets (e.g., [rbp+0xA80], [rbp+0x680], [rbp+0x210])

### Pass Registration with Hash: 0x76ad00
Called by SSR module (0xbc82ad0) and bloom up module (0xbc9ada0) for pass registration:
- `0xbc84c2e  call 0x76AD00` - SSRFillGaps (hash 0x1DF55AD7E2C2C59F)
- `0xbc84b86  call 0x76AD00` - SSRRayMarch (hash 0x46B26355E42496DA)
- `0xbc84bda  call 0x76AD00` - SSRRayMarchHZB (hash 0x2B39461B3803879A)
- `0xbc84c82  call 0x76AD00` - SSRGetReflectedColor (hash 0xCF01D3F07DAC7C8)
- `0xbc9bc32  call 0x76AD00` - BloomBlend (hash 0x7ADA5C0EF1420F87)

**Pattern:** RCX = pass function pointer, R8 = name string, RDX = precomputed FNV-1a64 hash

### Uniform/Parameter Binding Helper: 0x567c8b0
Called by:
- SSR module (0xbc82ad0) for ScreenSpaceReflections: `0xbc82c6c  call 0x567C8B0`
- RTX frame builder (0xbbe2d50) for RTXPostFX.ToneMapping: `0xbbf46e8  call 0x567C8B0`
- RTX frame builder (0xbbe2d50) for RTXPostFX.Bloom: `0xbbf47ae  call 0x567C8B0`

### Pass Body Callees: 0xe935740
Called after pass registration for each SSR/bloom pass:
- `0xbc84c3b  call 0xE935740` - SSRFillGaps body at 0xbc88440
- `0xbc84b93  call 0xE935740` - SSRRayMarch body at 0xbc88320
- `0xbc84be7  call 0xE935740` - SSRRayMarchHZB body at 0xbc883b0
- `0xbc84c8f  call 0xE935740` - SSRGetReflectedColor body at 0xbc884d0
- `0xbc9bc3f  call 0xE935740` - BloomBlend body at 0xbc9c8e0

### Cleanup/Finalize: 0xe938d70
Called after pass body registration:
- `0xbc84c47  call 0xE938D70` - after SSRFillGaps
- `0xbc84b9f  call 0xE938D70` - after SSRRayMarch
- `0xbc84bf3  call 0xE938D70` - after SSRRayMarchHZB
- `0xbc84c9b  call 0xE938D70` - after SSRGetReflectedColor
- `0xbc9bc4b  call 0xE938D70` - after BloomBlend

### VV Builder Pass Consumption: 0x55f1450
The VV builder at **0x55f1450** registers passes by:
1. Setting up pass description structure on stack (RBP+offsets)
2. Loading pass name strings into the structure
3. Calling 0x9d6d0 (for pass declarations) or 0x79580 (for uniform parameters)
4. Pass entries are stored in a vector for later frame-graph construction

**Entry indices from vv_builder_pass_order_55f1450.md:**
- SSRColorBufferBlit: entries ~50-51 (0x56235b4, 0x56235fe)
- SSRTexture: entry ~195 (0x563c8a1)
- SSRParameters: entry ~196 (0x563c572)

### RTX Frame Builder: 0xbbe2d50
Registers RTX-specific passes including:
- RTXPostFX.ToneMapping (0xbbf46b7)
- RTXPostFX.Bloom (0xbbf477d, 0xbbf5d5c)
- SceneGammaFallbackBlit / FullscreenSceneGammaPass
- WholeFrameGammaFallbackBlit / FullscreenWholeFrameGammaPass

### Tonemapper Parameter Setup: 0xbcacd90
Registers tonemapper uniform parameters (GenericTonemapperCrosstalkParams, GenericTonemapperContrastAndScaleAndOffsetAndCrosstalk, TonemapParams0) via uniform helper 0x79580.

### SSR Module: 0xbc82ad0
Registers all SSR-related uniforms and pass names:
- ScreenSpaceReflections via 0x567c8b0
- SSRFillGaps, SSRRayMarch, SSRRayMarchHZB, SSRGetReflectedColor via 0x76ad00 + 0xe935740
- Uniform parameters (SSRFadingParamsAndThickness, SSRTemporalAccumulationParams, SSRRayMarchingParams, SSRRoughnessCutoffParams) via 0x79580

### Bloom Modules:
- 0xbc98310 (bloom downscale: DFDownSample, ThresholdedDownSample) - registers BloomParams via 0x79580
- 0xbc9ada0 (bloom upscale: DFUpSample, BloomBlend) - registers BloomParams via 0x79580, BloomBlend via 0x76ad00

### RTX Resource Declaration: 0xc28e330
Registers RTX G-buffer and post-FX names including ToneMappingButNoBloom, RTXPostFX.Bloom via resource array setup.

### Bloom Material Pass Registration: 0xe7ec1f0
Registers Bloom material passes (BloomDownscaleGaussianPass, BloomDownscaleUniformPass) via 0x9d6d0.

---

## Verification Status

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-I6c.md`

### Gaps / UNVERIFIED items:
- [UNVERIFIED: 0xe7ec1f0] Exact instruction for "BloomUpscalePass" string reference (0xf549812) - same function as other bloom passes but different code path
- [UNVERIFIED: SSAO] No SSAO/AmbientOcclusion pass strings found in exe - may be internal to lighting passes (0xbc57460 LightClustering, 0xbc5c877 ClusterLights)
- [UNVERIFIED: 0x10f7ee0] Full context for Tonemapper entt type name usage

## TOOL REQUESTS

None - all data gathered with existing tools (xref.py, rdis dis, BGFX_MAP.md cross-reference).