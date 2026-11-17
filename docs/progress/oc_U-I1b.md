## NEXT
Start sub_bc5bad0 pass body from 0xbc5bad0 (0xbc5bad0..0xbc5d4a1)

## Step 1: String Search Results
[V] String search completed via rdis str for LightVolume, Light, Cluster, zLights, VoxelBuffer, LightLookup

### LightVolume
- f56e63d "LightVolumeManager" -> sub_4661780+0x81fc (0x466997c)

### Light (relevant ones with code refs)
- f5fa463 "VolumeScatteringEnabledAndPointLightVolumetricsEnabled" -> sub_55f1450+0x44ce1 (0x5636131)
- f5461d6 "zLights" -> sub_bc57460+0x28fb (0xbc59d5b)
- f51dbd7 "zLightLookupArray" -> sub_bc57460+0x29e5 (0xbc59e45)
- f5b49bf "LightClustering" -> sub_bc57460+0x2d9 (0xbc57739), sub_bc57460+0x2ade (0xbc59f3e)
- f5c5f05 "LightClusteringPhase" -> sub_bc57460+0x158d (0xbc589ed)

### Cluster
- f54f409 "ClusterDimensions" -> sub_55f1450+0x45b4a (0x5636f9a), sub_bc57460+0x2a5a (0xbc59eba)
- f53b2f9 "ClusterNearFarWidthHeight" -> sub_55f1450+0x45bc1 (0x5637011), sub_bc5bad0+0x12a2 (0xbc5cc72)
- f55b3ec "ClusterDepthBounds" -> sub_55f1450+0x45e8b (0x56372db), sub_bc5bad0+0x13f8 (0xbc5ced8)
- f5bbf34 "ClusterSize" -> sub_55f1450+0x45c38 (0x5637088), sub_bc5bad0+0x1386 (0xbc5ce56)

### VoxelBuffer
- f56ec6f "TransitioningVoxelBuffer" -> sub_bb3e2b0+0x20f8 (0xbb403a8)
- 5635c14 "VoxelBuffer" -> sub_55f1450+0x447c4 (0x5635c14) [VV builder]

### LightLookup
- f51dbd7 "zLightLookupArray" -> sub_bc57460+0x29e5 (0xbc59e45) [same as above]

## VV builder pass order light/cluster entries (from docs/functions/vv_builder_pass_order_55f1450.md):
- 5635c14 "VoxelBuffer"
- 5636f23 "ClusterDimensions"
- 5637011 "ClusterNearFarWidthHeight"
- 5637088 "ClusterSize"
- 56372db "ClusterDepthBounds"
- 5637c6c "VolumeDimensions"
- 5637ce3 "VolumeNearFar"
- 5637edc "VolumetricsShadows"
- 5637f43 "PopulateVolume"
- 5637fa8 "ScatteringBufferOut"

## Step 2: For each referencing site, function info and 60 instructions [V]

### Site 1: 0x466997c (LightVolumeManager in sub_4661780)
Containing function: sub_4661780 [0x4661780..0x46765c3) size 0x14e43
Caller: sub_8024d60
60 instructions at 0x466997c:
```
0x466997c  lea rax,[0xF56E63D]                           ; [data_f56e63d] "LightVolumeManager"
0x4669983  mov [rbp+0x118],rax                           
0x466998a  mov qword ptr [rbp+0x120],0x12                
0x4669995  lea rcx,[rbp-0x48]                            
0x4669999  lea rdx,[rbp+0x118]                           
0x46699a0  call 0x46DF530                                ; -> sub_46df530
```
Callee called with string: sub_46df530 (string hashing/registration)

### Site 2: 0x5636131 (VolumeScatteringEnabledAndPointLightVolumetricsEnabled in VV builder)
Containing function: sub_55f1450 [0x55f1450..0x563f594) size 0x4e144
60 instructions at 0x5636131:
```
0x5636131  lea rdx,[0xF5FA463]                           ; [data_f5fa463] "VolumeScatteringEnabledAndPointLightVolumetricsEnabled"
0x5636138  call 0x79580                                  ; -> sub_79580
0x563613d  nop                                           
0x563613e  cmp qword ptr [rbp+0x27B8],0x10               
0x5636146  lea rax,[rbp+0x27A0]                          
0x563614d  jb short 0x5636156                            ; -> loc_5636156
0x563614f  mov rax,[rbp+0x27A0]                          
```
Callee called with string: sub_79580 (string registration)

### Site 3: 0xbc59d5b (zLights in sub_bc57460)
Containing function: sub_bc57460 [0xbc57460..0xbc5a28f) size 0x2e2f
Caller: sub_55f1450 (VV builder)
60 instructions at 0xbc59d5b:
```
0xbc59d5b  lea rdx,[0xF5461D6]                           ; [data_f5461d6] "zLights"
0xbc59d62  lea r12,[rbp+0x410]                           
0xbc59d69  mov rcx,r12                                   
0xbc59d6c  call 0x79580                                  ; -> sub_79580
0xbc59d71  nop                                           
0xbc59d72  mov rdx,[rbp+0x420]                           
```
Callee called with string: sub_79580 (string registration)

### Site 4: 0xbc59e45 (zLightLookupArray in sub_bc57460)
Containing function: sub_bc57460 [0xbc57460..0xbc5a28f) size 0x2e2f
60 instructions at 0xbc59e45:
```
0xbc59e45  lea rdx,[0xF51DBD7]                           ; [data_f51dbd7] "zLightLookupArray"
0xbc59e4c  lea r12,[rbp+0x410]                           
0xbc59e53  mov rcx,r12                                   
0xbc59e56  call 0x79580                                  ; -> sub_79580
0xbc59e5b  nop                                           
0xbc59e5c  mov rdx,[rbp+0x420]                           
```
Callee called with string: sub_79580 (string registration)

### Site 5: 0x5636f9a (ClusterDimensions in VV builder)
Containing function: sub_55f1450 [0x55f1450..0x563f594) size 0x4e144
60 instructions at 0x5636f9a:
```
0x5636f9a  lea rdx,[0xF54F409]                           ; [data_f54f409] "ClusterDimensions"
0x5636fa1  call 0x79580                                  ; -> sub_79580
0x5636fa6  nop                                           
0x5636fa7  cmp qword ptr [rbp+0x27B8],0x10               
0x5636faf  lea rax,[rbp+0x27A0]                          
0x5636fb6  jb short 0x5636FBF                            ; -> loc_5636fbf
0x5636fb8  mov rax,[rbp+0x27A0]                          
```
Callee called with string: sub_79580 (string registration)

### Site 6: 0xbc59eba (ClusterDimensions in sub_bc57460)
Containing function: sub_bc57460 [0xbc57460..0xbc5a28f) size 0x2e2f
60 instructions at 0xbc59eba:
```
0xbc59eba  lea rdx,[0xF54F409]                           ; [data_f54f409] "ClusterDimensions"
0xbc59ec1  lea r12,[rbp+0x410]                           
0xbc59ec8  mov rcx,r12                                   
0xbc59ecb  call 0x79580                                  ; -> sub_79580
0xbc59ed0  nop                                           
0xbc59ed1  mov r8,[rbp+0x420]                            
```
Callee called with string: sub_79580 (string registration)

### Site 7: 0x5637011 (ClusterNearFarWidthHeight in VV builder)
Containing function: sub_55f1450 [0x55f1450..0x563f594) size 0x4e144
60 instructions at 0x5637011:
```
0x5637011  lea rdx,[0xF53B2F9]                           ; [data_f53b2f9] "ClusterNearFarWidthHeight"
0x5637018  call 0x79580                                  ; -> sub_79580
0x563701d  nop                                           
0x563701e  cmp qword ptr [rbp+0x27B8],0x10               
0x5637026  lea rax,[rbp+0x27A0]                          
0x563702d  jb short 0x5637036                            ; -> loc_5637036
0x563702f  mov rax,[rbp+0x27A0]                          
```
Callee called with string: sub_79580 (string registration)

### Site 8: 0xbc5cd72 (ClusterNearFarWidthHeight in sub_bc5bad0)
Containing function: sub_bc5bad0 [0xbc5bad0..0xbc5d4a1) size 0x19d1
60 instructions at 0xbc5cd72:
```
0xbc5cd72  lea rdx,[0xF53B2F9]                           ; [data_f53b2f9] "ClusterNearFarWidthHeight"
0xbc5cd79  lea r13,[rbp+0x1E0]                           
0xbc5cd80  mov rcx,r13                                   
0xbc5cd83  call 0x79580                                  ; -> sub_79580
0xbc5cd88  nop                                           
0xbc5cd89  mov rdx,[rbp+0x1F0]                           
```
Callee called with string: sub_79580 (string registration)

### Site 9: 0x56372db (ClusterDepthBounds in VV builder)
Containing function: sub_55f1450 [0x55f1450..0x563f594) size 0x4e144
60 instructions at 0x56372db:
```
0x56372db  lea rdx,[0xF55B3EC]                           ; [data_f55b3ec] "ClusterDepthBounds"
0x56372e2  call 0x79580                                  ; -> sub_79580
0x56372e7  nop                                           
0x56372e8  cmp qword ptr [rbp+0x27B8],0x10               
0x56372f0  lea rax,[rbp+0x27A0]                          
0x56372f7  jb short 0x5637300                            ; -> loc_5637300
0x56372f9  mov rax,[rbp+0x27A0]                          
```
Callee called with string: sub_79580 (string registration)

### Site 10: 0xbc5cec8 (ClusterDepthBounds in sub_bc5bad0)
Containing function: sub_bc5bad0 [0xbc5bad0..0xbc5d4a1) size 0x19d1
60 instructions at 0xbc5cec8:
```
0xbc5cec8  lea rdx,[0xF55B3EC]                           ; [data_f55b3ec] "ClusterDepthBounds"
0xbc5cecf  lea r13,[rbp+0x1E0]                           
0xbc5ced6  mov rcx,r13                                   
0xbc5ced9  call 0x79580                                  ; -> sub_79580
0xbc5cede  nop                                           
0xbc5cedf  mov rdx,[rbp+0x1F0]                           
```
Callee called with string: sub_79580 (string registration)

### Site 11: 0x5637088 (ClusterSize in VV builder)
Containing function: sub_55f1450 [0x55f1450..0x563f594) size 0x4e144
60 instructions at 0x5637088:
```
0x5637088  lea rdx,[0xF5BBF34]                           ; [data_f5bbf34] "ClusterSize"
0x563708f  call 0x79580                                  ; -> sub_79580
0x5637094  nop                                           
0x5637095  cmp qword ptr [rbp+0x27B8],0x10               
0x563709d  lea rax,[rbp+0x27A0]                          
0x56370a4  jb short 0x56370AD                            ; -> loc_56370ad
0x56370a6  mov rax,[rbp+0x27A0]                          
```
Callee called with string: sub_79580 (string registration)

### Site 12: 0xbc5ce56 (ClusterSize in sub_bc5bad0)
Containing function: sub_bc5bad0 [0xbc5bad0..0xbc5d4a1) size 0x19d1
60 instructions at 0xbc5ce56:
```
0xbc5ce56  lea rdx,[0xF5BBF34]                           ; [data_f5bbf34] "ClusterSize"
0xbc5ce5d  lea r13,[rbp+0x1E0]                           
0xbc5ce64  mov rcx,r13                                   
0xbc5ce67  call 0x79580                                  ; -> sub_79580
0xbc5ce6c  nop                                           
0xbc5ce6d  mov rdx,[rbp+0x1F0]                           
```
Callee called with string: sub_79580 (string registration)

### Site 13: 0xbc57739 (LightClustering in sub_bc57460)
Containing function: sub_bc57460 [0xbc57460..0xbc5a28f) size 0x2e2f
60 instructions at 0xbc57739:
```
0xbc57739  lea rax,[0xF5B49BF]                           ; [data_f5b49bf] "LightClustering"
0xbc57740  mov [rbp+0x1D0],rax                           
0xbc57747  mov qword ptr [rbp+0x1D8],0xF                 
0xbc57752  lea rax,[rbp+0x410]                           
0xbc57759  mov [rsp+0x28],rax                            
0xbc5775e  lea rax,[rbp+0x1D0]                           
0xbc57765  mov [rsp+0x20],rax                            
```
Callee called with string: sub_567c8b0 (different pattern - stores string pointer then calls)

### Site 14: 0xbc59f3e (LightClustering in sub_bc57460)
Containing function: sub_bc57460 [0xbc57460..0xbc5a28f) size 0x2e2f
60 instructions at 0xbc59f3e:
```
0xbc59f3e  lea rax,[0xF5B49BF]                           ; [data_f5b49bf] "LightClustering"
0xbc59f45  mov [rbp+0x1C0],rax                           
0xbc59f4c  mov qword ptr [rbp+0x1C8],0xF                 
0xbc59f57  lea rcx,[0x12ADF788]                          ; [data_12adf788]
0xbc59f5e  lea rdx,[rbp+0x1C0]                           
0xbc59f65  lea r8,[rbp-0x20]                             
0xbc59f69  call 0x5668AC0                                ; -> sub_5668ac0
```
Callee called with string: sub_5668ac0 (different pattern)

### Site 15: 0xbc589ed (LightClusteringPhase in sub_bc57460)
Containing function: sub_bc57460 [0xbc57460..0xbc5a28f) size 0x2e2f
60 instructions at 0xbc589ed:
```
0xbc589ed  movups xmm0,[0xF5C5F05]                       ; [data_f5c5f05] "LightClusteringPhase"
0xbc589f4  movups [rdi],xmm0                             
0xbc589f7  mov dword ptr [rdi+0x10],0x65736168           
0xbc589fe  mov byte ptr [rdi+0x14],0                     
0xbc58a02  mov qword ptr [rbp+0x400],0xF                 
0xbc58a0d  mov qword ptr [rbp+0x408],0                   
```
Different pattern - loads string via movups to xmm0, stores to [rdi]

### Site 16: 0xbb403a8 (TransitioningVoxelBuffer in sub_bb3e2b0)
Containing function: sub_bb3e2b0 [0xbb3e2b0..0xbb40bee) size 0x293e
Caller: sub_55f1450 (VV builder)
60 instructions at 0xbb403a8:
```
0xbb403a8  lea rdx,[0xF56EC6F]                           ; [data_f56ec6f] "TransitioningVoxelBuffer"
0xbb403af  lea rdi,[rbp+0x240]                           
0xbb403b6  mov rcx,rdi                                   
0xbb403b9  call 0x79580                                  ; -> sub_79580
0xbb403be  nop                                           
0xbb403bf  mov rdx,[rbp+0x250]                           
```
Callee called with string: sub_79580 (string registration)

### Site 17: 0x5635c14 (VoxelBuffer in VV builder)
Containing function: sub_55f1450 [0x55f1450..0x563f594) size 0x4e144
60 instructions at 0x5635c14:
```
0x5635c14  lea rdx,[0xF56EC95]                           ; [data_f56ec95] "VoxelBuffer"
0x5635c1b  call 0x79580                                  ; -> sub_79580
0x5635c20  nop                                           
0x5635c21  cmp qword ptr [rbp+0x27B8],0x10               
0x5635c29  lea rax,[rbp+0x27A0]                          
0x5635c30  jb short 0x5635C39                            ; -> loc_5635c39
0x5635c32  mov rax,[rbp+0x27A0]                          
```
Callee called with string: sub_79580 (string registration)

## Step 3: Stores of pass description fields after each registration [V]

### Stores for sub_4661780 (LightVolumeManager)
From stores.py on docs/data/listings/sub_4661780.txt (only verified instructions):
```
0x4661ac4  mov dword ptr [0],0xDEADC0DE
```
Note: The stores.py output showed many DEADC0DE pattern fills at regular intervals, but only the first at 0x4661ac4 is a verified instruction. The others appear to be pattern matches in the disassembly output, not actual instructions. The actual pass registration for LightVolumeManager appears to be in sub_46df530 (called at 0x46699a0).

### Stores for sub_bc57460 (Light clustering)
From stores.py on docs/data/listings/sub_bc57460.txt:
```
0xbc57895  mov byte ptr [r12+0x10],0
0xbc5789b  mov byte ptr [r12+0x28],0
0xbc578a4  movups [r12+0x30],xmm0
0xbc578aa  mov dword ptr [r12+0x40],0
0xbc589f4  movups [rdi],xmm0
0xbc589f7  mov dword ptr [rdi+0x10],0x65736168
0xbc589fe  mov byte ptr [rdi+0x14],0
0xbc58b25  movups [rax],xmm0
0xbc58cf6  mov [rdi],rax
0xbc58cf9  mov dword ptr [rdi+8],0x3F800000
0xbc58d03  movups [rdi+0xC],xmm0
0xbc58d07  mov dword ptr [rdi+0x1C],0x3F800000
0xbc58d0e  movups [rdi+0x20],xmm0
0xbc58d12  mov dword ptr [rdi+0x30],0x3F800000
0xbc58d19  movups [rdi+0x34],xmm0
0xbc58d25  movsd [rdi+0x44],xmm1
0xbc58d2a  movups [rdi+0x4C],xmm0
0xbc58d2e  mov dword ptr [rdi+0x5C],0x3F800000
0xbc58d35  movups [rdi+0x60],xmm0
0xbc58d39  mov dword ptr [rdi+0x70],0x3F800000
0xbc58d40  movups [rdi+0x74],xmm0
0xbc58d44  mov dword ptr [rdi+0x84],0x3F800000
0xbc58d4e  movups [rdi+0x88],xmm0
0xbc58d5f  mov [rdi+0x98],rax
0xbc58d66  movups [rdi+0xA0],xmm0
0xbc58d6d  mov dword ptr [rdi+0xB0],0x3F800000
0xbc58d77  movups [rdi+0xB4],xmm0
0xbc58d7e  mov dword ptr [rdi+0xC4],0x3F800000
0xbc58d88  movups [rdi+0xC8],xmm0
0xbc58d8f  movsd [rdi+0xD8],xmm1
0xbc58d97  movups [rdi+0xE0],xmm0
0xbc58d9e  mov dword ptr [rdi+0xF0],0x3F800000
0xbc58da8  movups [rdi+0xF4],xmm0
0xbc58daf  mov dword ptr [rdi+0x104],0x3F800000
0xbc58db9  movups [rdi+0x108],xmm0
0xbc58dc0  mov dword ptr [rdi+0x118],0x3F800000
0xbc58dce  movups [rdi+0x11C],xmm0
0xbc58f72  movups [rax+0x38],xmm0
0xbc59233  mov [r15+8],rax
0xbc5923e  mov [r15],rax
0xbc59259  movups [r15+0x28],xmm6
0xbc5925e  movups [r15+0x18],xmm6
0xbc59263  mov qword ptr [r15+0x38],0xF
0xbc5926b  mov qword ptr [r15+0x40],0
0xbc5927a  mov [r15+0x10],rax
0xbc59282  mov qword ptr [r15+0x80],0
0xbc5929e  mov [r15+0x80],rcx
0xbc592b7  mov [r15+0x80],rax
0xbc592f3  mov [r15+0xB8],rcx
0xbc59308  movups [r15+0xA8],xmm2
0xbc59310  movups [r15+0x98],xmm1
0xbc59318  movups [r15+0x88],xmm0
0xbc59327  movups [r15+0xC0],xmm0
0xbc5932f  movups [r14+0x38],xmm6
0xbc5933b  mov [r15+0xD0],rcx
0xbc59349  movups [r15+0xD8],xmm0
0xbc59359  movsd [r15+0xE8],xmm0
0xbc59374  movups [r15+0x110],xmm2
0xbc5937c  movups [r15+0x100],xmm1
0xbc59384  movups [r15+0xF0],xmm0
0xbc59394  movups [r15+0x120],xmm0
0xbc593a3  mov [r15+0x130],rcx
0xbc593b1  movups [r15+0x138],xmm0
0xbc593c0  movups [r15+0x148],xmm0
0xbc593cf  movups [r15+0x158],xmm0
0xbc593de  movups [r15+0x168],xmm0
0xbc593ed  movups [r15+0x178],xmm0
0xbc593fc  movups [r15+0x188],xmm0
0xbc5940b  movups [r15+0x198],xmm0
0xbc5941a  movups [r15+0x1A8],xmm0
0xbc59429  movups [r15+0x1B8],xmm0
0xbc59438  movups [r15+0x1C8],xmm0
0xbc59447  movups [r15+0x1D8],xmm0
0xbc59457  movsd [r15+0x1E8],xmm0
0xbc59468  movss [r15+0x1F0],xmm0
0xbc59479  movups [r15+0x1F4],xmm0
0xbc59488  mov [r15+0x204],ecx
0xbc5948f  mov byte ptr [r15+0x220],0
0xbc594c3  movups [r15+0x208],xmm0
0xbc594cb  mov [r15+0x218],rcx
0xbc594d2  mov byte ptr [r15+0x220],1
0xbc594ef  mov [r15+0x230],ecx
0xbc594f9  mov [r15+0x228],rax
0xbc59503  movups [r15+0x238],xmm0
0xbc5950b  movups [r15+0x248],xmm0
0xbc595b5  mov [rbx],r14
0xbc595d1  mov [r14+0x248],rdi
0xbc595d8  mov [r14+0x250],r13
0xbc59606  mov [rsi],rax
0xbc59609  mov [rsi+8],r14
0xbc59615  mov [rcx+0x10],rax
0xbc5982f  mov byte ptr [rcx+0x60],1
0xbc59837  mov [rcx+0x58],rax
0xbc598d1  mov [rsi+0x20],rdi
0xbc598ee  mov [rsi+8],rax
0xbc598f2  mov qword ptr [rsi+0x30],0
0xbc59901  mov qword ptr [rax+0x58],0
0xbc59b2f  mov [r14],rax
0xbc59b39  mov [r14+8],rax
0xbc59b44  mov [r14+0x18],rax
0xbc59b4f  mov [r14+0x20],rax
0xbc59b57  mov byte ptr [r14+0x10],1
0xbc59b5c  mov byte ptr [r14+0x28],1
0xbc59b68  movss [r14+0x30],xmm1
0xbc59b75  movss [r14+0x34],xmm1
0xbc59b83  movss [r14+0x38],xmm1
0xbc59b89  movss [r14+0x3C],xmm0
0xbc59b8f  movss [r14+0x40],xmm7
0xbc59be8  movups [rsi],xmm0
0xbc59beb  mov qword ptr [rsi+0x10],0
0xbc5a062  mov [0x12ADF748],rcx
0xbc5a10e  mov [0x12ADF758],rcx
0xbc5a1c1  mov [0x12ADF768],rcx
0xbc5a261  mov [0x12ADF778],rdx
```

### Stores for sub_bc5bad0 (Light clustering)
From stores.py on docs/data/listings/sub_bc5bad0.txt:
```
0xbc5bc86  mov [r14+8],rax
0xbc5bc91  mov [r14],rax
0xbc5bc9e  mov [r14+0x10],rcx
0xbc5bca6  movdqu [r14+0x18],xmm0
0xbc5bcac  mov qword ptr [r14+0x28],0
0xbc5c631  mov [rax+8],r14d
0xbc5c635  mov [rax],r15
0xbc5c63b  movups [rax+0x10],xmm0
0xbc5c711  mov [rax+8],r14d
0xbc5c715  mov [rax],r15
0xbc5c71b  movups [rax+0x10],xmm0
0xbc5c801  mov [rax+8],r14d
0xbc5c805  mov [rax],r15
0xbc5c80b  movups [rax+0x10],xmm0
0xbc5cab4  movups [rsi],xmm0
0xbc5cab7  mov qword ptr [rsi+0x10],0
0xbc5caca  mov qword ptr [rcx],0
0xbc5cbf3  mov [rdx],rcx
0xbc5cbf6  mov [rcx+8],rdx
0xbc5cbfa  mov [rax],rax
0xbc5cbfd  mov [rax+8],rax
0xbc5cc0f  mov [rcx],rax
0xbc5cc12  mov [rax+8],rcx
0xbc5d119  mov [0x12ADF7A0],rcx
0xbc5d1c8  mov [0x12ADF7B0],rcx
0xbc5d27a  mov [0x12ADF7C0],rcx
0xbc5d32c  mov [0x12ADF7D0],rcx
0xbc5d3de  mov [0x12ADF7E0],rcx
0xbc5d47d  mov [0x12ADF7F0],rdx
```

### Stores for sub_bb3e2b0 (Voxel lighting)
From stores.py on docs/data/listings/sub_bb3e2b0.txt:
```
0xbb3e420  mov [rdx],ax
0xbb3e42a  mov [rdx+2],ax
0xbb3e435  mov [rdx+4],ax
0xbb3e440  mov [rdx+6],ax
0xbb3e4c0  mov [rdx],ax
0xbb3e4ca  mov [rdx+2],ax
0xbb3e4d5  mov [rdx+4],ax
0xbb3e4e0  mov [rdx+6],ax
0xbb3e5c0  mov [rax+8],dx
0xbb3e5c9  mov [rax+0xA],r8w
0xbb3e5d3  mov [rax+0xC],r8w
0xbb3e5dd  mov [rax+0xE],r8w
0xbb3e635  mov [rax],dx
0xbb3e63d  mov [rax+2],dx
0xbb3e646  mov [rax+4],dx
0xbb3e64f  mov [rax+6],dx
0xbb3e86f  movups [rbx],xmm7
0xbb3e872  mov dword ptr [rbx+0x10],0x676E6974
0xbb3e879  mov byte ptr [rbx+0x14],0
0xbb3ec38  movups [rbx],xmm7
0xbb3ec3b  mov dword ptr [rbx+0x10],0x676E6974
0xbb3ec42  mov byte ptr [rbx+0x14],0
0xbb3f44a  movups [rdi],xmm7
0xbb3f44d  mov dword ptr [rdi+0x10],0x676E6974
0xbb3f45b  mov byte ptr [rdi+0x14],0
0xbb3f548  movups [rax],xmm0
0xbb3f5aa  mov [rdi],rax
0xbb3f5ad  mov dword ptr [rdi+8],0x3F800000
0xbb3f5b7  movups [rdi+0xC],xmm7
0xbb3f5bb  mov dword ptr [rdi+0x1C],0x3F800000
0xbb3f5c2  movups [rdi+0x20],xmm7
0xbb3f5c6  mov dword ptr [rdi+0x30],0x3F800000
0xbb3f5cd  movups [rdi+0x34],xmm7
0xbb3f5d1  movsd [rdi+0x44],xmm6
0xbb3f5d6  movups [rdi+0x4C],xmm7
0xbb3f5da  mov dword ptr [rdi+0x5C],0x3F800000
0xbb3f5e1  movups [rdi+0x60],xmm7
0xbb3f5e5  mov dword ptr [rdi+0x70],0x3F800000
0xbb3f5ec  movups [rdi+0x74],xmm7
0xbb3f5f0  mov dword ptr [rdi+0x84],0x3F800000
0xbb3f5fa  movups [rdi+0x88],xmm7
0xbb3f60b  mov [rdi+0x98],rax
0xbb3f612  movups [rdi+0xA0],xmm7
0xbb3f619  mov dword ptr [rdi+0xB0],0x3F800000
0xbb3f623  movups [rdi+0xB4],xmm7
0xbb3f62a  mov dword ptr [rdi+0xC4],0x3F800000
0xbb3f634  movups [rdi+0xC8],xmm7
0xbb3f63b  movsd [rdi+0xD8],xmm6
0xbb3f643  movups [rdi+0xE0],xmm7
0xbb3f64a  mov dword ptr [rdi+0xF0],0x3F800000
0xbb3f654  movups [rdi+0xF4],xmm7
0xbb3f65b  mov dword ptr [rdi+0x104],0x3F800000
0xbb3f665  movups [rdi+0x108],xmm7
0xbb3f66c  mov dword ptr [rdi+0x118],0x3F800000
0xbb3f676  movups [rdi+0x11C],xmm7
0xbb3f79c  movups [rax],xmm7
0xbb3f7bb  movups [rax+0x18],xmm7
0xbb3f8cd  mov [r14+8],rax
0xbb3f8d8  mov [r14],rax
0xbb3f8f3  movups [r14+0x28],xmm6
0xbb3f8f8  movups [r14+0x18],xmm6
0xbb3f8fd  mov qword ptr [r14+0x38],0xF
0xbb3f905  mov qword ptr [r14+0x40],0
0xbb3f914  mov [r14+0x10],rax
0xbb3f91c  mov qword ptr [r14+0x80],0
0xbb3f938  mov [r14+0x80],rcx
0xbb3f951  mov [r14+0x80],rax
0xbb3f9a2  movups [r14+0x88],xmm0
0xbb3f9aa  movups [rbx],xmm6
0xbb3f9b4  movups [r14+0x98],xmm0
0xbb3f9ca  movups [rbx+0x18],xmm6
0xbb3f9ce  movups [r14+0xB0],xmm6
0xbb3f9d6  mov qword ptr [r14+0xC0],0
0xbb3f9e8  mov [r14+0xC8],al
0xbb3f9fc  movups [r14+0xD8],xmm6
0xbb3fa04  movups [r14+0xE8],xmm6
0xbb3faa9  mov [rbx],r14
0xbb3fac5  mov [r14+0xE8],rdi
0xbb3facc  mov [r14+0xF0],rsi
0xbb3fafa  mov [r13],rax
0xbb3fafe  mov [r13+8],r14
0xbb3fb0a  mov [rcx+0x10],rax
0xbb3fd2f  mov byte ptr [rcx+0x60],1
0xbb3fd37  mov [rcx+0x58],rax
0xbb3fdb6  mov [rbx+0x20],rsi
0xbb3fdd3  mov [rbx+8],rax
0xbb3fdd7  mov qword ptr [rbx+0x30],0
0xbb3fde6  mov qword ptr [rax+0x58],0
0xbb406fe  mov [0x12ADF3C8],rcx
0xbb407ad  mov [0x12ADF3D8],rcx
0xbb40863  mov [0x12ADE670],rcx
0xbb40912  mov [0x12ADE680],rcx
0xbb409c1  mov [0x12ADE690],rcx
0xbb40a70  mov [0x12ADE6A0],rcx
0xbb40b1f  mov [0x12ADE6B0],rcx
0xbb40bbc  mov [0x12ADE6C0],rdx
```

### Stores for sub_79580 (String registration function)
From manual analysis of sub_79580:
```
0x79596  movups [rcx+0x10],xmm0
0x7959a  movups [rcx],xmm0
0x79626  mov [rsi],r14
0x79629  mov [rsi+0x10],rbx
0x7962d  mov [rsi+0x18],r12
0x7963f  mov byte ptr [r14+rbx],0
```
These are the key stores for string registration: clearing the destination buffer, storing the string pointer, length, capacity, and null terminator.

### Stores for VV builder light/cluster section (sub_55f1450 0x5635c14-0x5638000)
From stores.py on docs/data/listings/vv_builder_light_cluster.txt:
```
(no stores found)
```
The VV builder section only calls sub_79580 for each string; pass description fields are stored elsewhere (in the light clustering functions).

## Gaps / Unverified
[UNVERIFIED: 0x46df530] What pass description fields are stored by sub_46df530 (LightVolumeManager registration callee)?
[UNVERIFIED: 0x567c8b0] What pass description fields are stored by sub_567c8b0 (LightClustering registration callee in sub_bc57460)?
[UNVERIFIED: 0x5668ac0] What pass description fields are stored by sub_5668ac0 (LightClustering registration callee in sub_bc57460)?
[UNVERIFIED: 0xbc5761a] Sub_bc57460 jumps to sub_bc5761a after some string registrations - what does it do?
[UNVERIFIED: 0xbc5bd02] Sub_bc5bad0 jumps to sub_bc5bd02 after some string registrations - what does it do?
[UNVERIFIED: 0xbb3efa3] Sub_bb3e2b0 jumps to sub_bb3efa3 after some string registrations - what does it do?

## TOOL REQUESTS
None

# Pass bodies

## sub_bc57460 (0xbc57460..0xbc5a28f) - Light clustering pass registration

### Chunk 1: 0xbc57460..0xbc57cd7 (400 instructions)
```
0xbc57460  push rbp                                      
0xbc57461  push r15                                      
0xbc57463  push r14                                      
0xbc57465  push r13                                      
0xbc57467  push r12                                      
0xbc57469  push rsi                                      
0xbc5746a  push rdi                                      
0xbc5746b  push rbx                                      
0xbc5746c  sub rsp,0x9E8                                 
0xbc57473  lea rbp,[rsp+0x80]                            
0xbc5747b  movaps [rbp+0x950],xmm15                      
0xbc57483  movaps [rbp+0x940],xmm14                      
0xbc5748b  movaps [rbp+0x930],xmm13                      
0xbc57493  movaps [rbp+0x920],xmm12                      
0xbc5749b  movaps [rbp+0x910],xmm11                      
0xbc574a3  movaps [rbp+0x900],xmm10                      
0xbc574ab  movaps [rbp+0x8F0],xmm9                       
0xbc574b3  movaps [rbp+0x8E0],xmm8                       
0xbc574bb  movaps [rbp+0x8D0],xmm7                       
0xbc574c2  movaps [rbp+0x8C0],xmm6                       
0xbc574c9  mov qword ptr [rbp+0x8B8],0xFFFFFFFFFFFFFFFE  
0xbc574d4  mov r12,rcx                                   
0xbc574d7  cmp byte ptr [rbp+0xA00],0                    
0xbc574de  je 0xBC57895                                  ; -> loc_bc57895
0xbc574e4  mov r15,r9                                    
0xbc574e7  mov rdi,r8                                    
0xbc574ea  mov [rbp+0x8A0],rdx                           
0xbc574f1  mov r14,[rbp+0x9E8]                           
0xbc574f8  movzx eax,word ptr [r14+0xC]                  
0xbc574fd  cvtsi2ss xmm0,eax                             
0xbc57501  mov rbx,[rbp+0x9F8]                           
0xbc57508  mov rsi,[rbp+0x9F0]                           
0xbc5750f  divss xmm0,[rbx+4]                            
0xbc57514  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc57519  movzx eax,word ptr [r14+0xE]                  
0xbc5751e  cvtsi2ss xmm1,eax                             
0xbc57522  movaps xmm6,xmm0                              
0xbc57525  divss xmm1,[rbx+8]                            
0xbc5752a  movaps xmm0,xmm1                              
0xbc5752d  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc57532  movss xmm1,[rbx+0xC]                          
0xbc57537  movaps [rbp+0x7C0],xmm6                       
0xbc5753e  movss [rbp+0x7B4],xmm6                        
0xbc57546  movaps [rbp+0x7D0],xmm0                       
0xbc5754d  movss [rbp+0x7B8],xmm0                        
0xbc57555  movss [rbp+0x894],xmm1                        
0xbc5755d  movss [rbp+0x7BC],xmm1                        
0xbc57565  mov rax,[rsi+0x50]                            
0xbc57569  sub rax,[rsi+0x48]                            
0xbc5756d  sar rax,3                                     
0xbc57571  mov rbx,0xEF7BDEF7BDEF7BDF                    
0xbc5757b  imul rbx,rax                                  
0xbc5757f  cmp rbx,1                                     
0xbc57583  adc rbx,0                                     
0xbc57587  mov qword ptr [rbp+0x88C],0                   
0xbc57592  mov eax,[0x12ADF750]                          ; [data_12adf750]
0xbc57598  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5759e  mov rdx,gs:[0x58]                             
0xbc575a7  mov rcx,[rdx+rcx*8]                           
0xbc575ab  cmp eax,[rcx+4]                               
0xbc575b1  jg 0xBC59D3F                                  ; -> sub_bc59d3f
0xbc575b7  mov dword ptr [rbp+0x890],0x80                
0xbc575c1  mov [rbp+0x88C],ebx                           
0xbc575c7  mov rax,[0x12ADF748]                          ; [data_12adf748]
0xbc575ce  mov [rbp+0x760],rax                           
0xbc575d5  lea r8,[rbp+0x88C]                            
0xbc575dc  mov r13,[rbp+0x8A0]                           
0xbc575e3  mov rcx,r13                                   
0xbc575e6  mov rdx,r13                                   
0xbc575e9  call 0xBC09250                                ; -> sub_bc09250
0xbc575ee  mov [rbp+0x768],rax                           
0xbc575f5  mov eax,[0x12ADF760]                          ; [data_12adf760]
0xbc575fb  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc57601  mov rdx,gs:[0x58]                             
0xbc5760a  mov rcx,[rdx+rcx*8]                           
0xbc5760e  cmp eax,[rcx+4]                               
0xbc57614  jg 0xBC59DB4                                  ; -> sub_bc59db4
0xbc5761a  mov dword ptr [rbp+0x890],0x40                
0xbc57624  mov [rbp+0x88C],ebx                           
0xbc5762a  mov rax,[0x12ADF758]                          ; [data_12adf758]
0xbc57631  mov [rbp+0x698],rax                           
0xbc57638  lea r8,[rbp+0x88C]                            
0xbc5763f  mov rcx,r13                                   
0xbc57642  mov rdx,r13                                   
0xbc57645  call 0xBC09250                                ; -> sub_bc09250
0xbc5764a  mov [rbp+0x6A0],rax                           
0xbc57651  mov eax,[0x12ADF770]                          ; [data_12adf770]
0xbc57657  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5765d  mov rdx,gs:[0x58]                             
0xbc57666  mov rcx,[rdx+rcx*8]                           
0xbc5766a  cmp eax,[rcx+4]                               
0xbc57670  jg 0xBC59E29                                  ; -> sub_bc59e29
0xbc57676  movaps xmm0,[rbp+0x7C0]                       
0xbc5767d  mulss xmm0,[rbp+0x7D0]                        
0xbc57685  mulss xmm0,[rbp+0x894]                        
0xbc5768d  cvttss2si rcx,xmm0                            
0xbc57692  mov rax,[rbp+0x9F8]                           
0xbc57699  imul ecx,[rax]                                
0xbc5769c  mov dword ptr [rbp+0x890],4                   
0xbc576a6  mov [rbp+0x880],rcx                           
0xbc576ad  mov [rbp+0x88C],ecx                           
0xbc576b3  mov rax,[0x12ADF768]                          ; [data_12adf768]
0xbc576ba  mov [rbp+0x770],rax                           
0xbc576c1  lea r8,[rbp+0x88C]                            
0xbc576c8  mov rcx,r13                                   
0xbc576cb  mov rdx,r13                                   
0xbc576ce  call 0xBC09250                                ; -> sub_bc09250
0xbc576d3  mov [rbp+0x778],rax                           
0xbc576da  mov eax,[0x12ADF780]                          ; [data_12adf780]
0xbc576e0  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc576e6  mov rdx,gs:[0x58]                             
0xbc576ef  mov rcx,[rdx+rcx*8]                           
0xbc576f3  cmp eax,[rcx+4]                               
0xbc576f9  jg 0xBC59E9E                                  ; -> sub_bc59e9e
0xbc576ff  mov eax,[0x12ADF798]                          ; [data_12adf798]
0xbc57705  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5770b  mov rdx,gs:[0x58]                             
0xbc57714  mov rcx,[rdx+rcx*8]                           
0xbc57718  cmp eax,[rcx+4]                               
0xbc5771e  jg 0xBC59F1E                                  ; -> sub_bc59f1e
0xbc57724  mov r9,[rbp+0x9D0]                            
0xbc5772b  lea r13,[r14+0x18]                            
0xbc5772f  xorps xmm0,xmm0                               
0xbc57732  movaps [rbp+0x410],xmm0                       
0xbc57739  lea rax,[0xF5B49BF]                           ; [data_f5b49bf] "LightClustering"
0xbc57740  mov [rbp+0x1D0],rax                           
0xbc57747  mov qword ptr [rbp+0x1D8],0xF                 
0xbc57752  lea rax,[rbp+0x410]                           
0xbc57759  mov [rsp+0x28],rax                            
0xbc5775e  lea rax,[rbp+0x1D0]                           
0xbc57765  mov [rsp+0x20],rax                            
0xbc5776a  lea r8,[0x12ADF788]                           ; [data_12adf788]
0xbc57771  lea rdx,[rbp+0x750]                           
0xbc57778  mov rcx,r15                                   
0xbc5777b  call 0x567C8B0                                ; -> sub_567c8b0
0xbc57780  movss xmm6,[r14+0x18]                         
0xbc57786  movss xmm7,[r14+0x2C]                         
0xbc5778c  mov r15d,[0x12ADF818]                         ; [data_12adf818]
0xbc57793  lea rcx,[rbp+0x410]                           
0xbc5779a  mov rdx,r13                                   
0xbc5779d  call 0xAB49C0                                 ; -> sub_ab49c0
0xbc577a2  nop                                           
0xbc577a3  add r15d,0xFFFFFFF9                           
0xbc577a7  movss xmm0,[0xEF1D470]                        ; [data_ef1d470]
0xbc577af  xorps xmm3,xmm3                               
0xbc577b2  movaps xmm9,xmm0                              
0xbc577b6  cmp r15d,2                                    
0xbc577ba  jb short 0xBC577C0                            ; -> loc_bc577c0
0xbc577bc  xorps xmm9,xmm9                               

loc_bc577c0:  ; from bc577ba
0xbc577c0  divss xmm0,xmm6                               
0xbc577c4  divss xmm6,xmm7                               
0xbc577c8  movss xmm1,[rbp+0x41C]                        
0xbc577d0  mulss xmm1,xmm3                               
0xbc577d4  movss xmm2,[rbp+0x418]                        
0xbc577dc  mulss xmm2,xmm3                               
0xbc577e0  movss xmm4,[rbp+0x42C]                        
0xbc577e8  mulss xmm4,xmm3                               
0xbc577ec  addss xmm4,xmm1                               
0xbc577f0  mulss xmm3,[rbp+0x428]                        
0xbc577f8  addss xmm3,xmm2                               
0xbc577fc  movss xmm1,[rbp+0x438]                        
0xbc57804  movss xmm5,[rbp+0x43C]                        
0xbc5780c  movaps xmm2,xmm9                              
0xbc57810  mulss xmm2,xmm5                               
0xbc57814  mulss xmm9,xmm1                               
0xbc57819  movss xmm7,[rbp+0x448]                        
0xbc57821  movss xmm8,[rbp+0x44C]                        
0xbc5782a  addss xmm2,xmm8                               
0xbc5782f  addss xmm9,xmm7                               
0xbc57834  addss xmm2,xmm4                               
0xbc57838  addss xmm9,xmm3                               
0xbc5783d  addss xmm5,xmm8                               
0xbc57842  addss xmm1,xmm7                               
0xbc57846  addss xmm5,xmm4                               
0xbc5784a  addss xmm1,xmm3                               
0xbc5784e  divss xmm1,xmm5                               
0xbc57852  addss xmm0,xmm0                               
0xbc57856  mulss xmm0,xmm1                               
0xbc5785a  movaps xmm3,xmm0                              
0xbc5785d  divss xmm3,xmm6                               
0xbc57861  xorps xmm4,xmm4                               
0xbc57864  movaps [rbp+0x30],xmm4                        
0xbc57868  movaps [rbp+0x20],xmm4                        
0xbc5786c  movaps [rbp+0x10],xmm4                        
0xbc57870  movaps [rbp],xmm4                             
0xbc57874  mov qword ptr [rbp+0x40],0                    
0xbc5787c  mov rax,[rbp+0x758]                           
0xbc57883  test rax,rax                                  
0xbc57886  je short 0xBC578BB                            ; -> loc_bc578bb
0xbc57888  lock inc dword ptr [rax+8]                    
0xbc5788c  mov rax,[rbp+0x758]                           
0xbc57893  jmp short 0xBC578BD                           ; -> loc_bc578bd

loc_bc57895:  ; from bc574de
0xbc57895  mov byte ptr [r12+0x10],0                     
0xbc5789b  mov byte ptr [r12+0x28],0                     
0xbc578a1  xorps xmm0,xmm0                               
0xbc578a4  movups [r12+0x30],xmm0                        
0xbc578aa  mov dword ptr [r12+0x40],0                    
0xbc578b3  mov rax,r12                                   
0xbc578b6  jmp 0xBC59C61                                 ; -> sub_bc59c61

loc_bc578bb:  ; from bc57886
0xbc578bb  xor eax,eax                                   

loc_bc578bd:  ; from bc57893
0xbc578bd  mov rcx,[rbp+0x750]                           
0xbc578c4  mov [rbp+0x38],rcx                            
0xbc578c8  mov [rbp+0x40],rax                            
0xbc578cc  mov [rbp+0x48],rdi                            
0xbc578d0  movaps xmm4,[rbp+0x7C0]                       
0xbc578d7  movss [rbp+0x50],xmm4                         
0xbc578dc  movaps xmm4,[rbp+0x7D0]                       
0xbc578e3  movss [rbp+0x54],xmm4                         
0xbc578e8  movss xmm4,[rbp+0x894]                        
0xbc578f0  movss [rbp+0x58],xmm4                         
0xbc578f5  movsd xmm4,[0xF246EA0]                        ; [data_f246ea0] = sub_800000
0xbc578fd  movsd [rbp+0x5C],xmm4                         
0xbc57902  mov dword ptr [rbp+0x64],0x40800000           
0xbc57909  mov rax,[rbp+0x9F8]                           
0xbc57910  movups xmm4,[rax]                             
0xbc57913  movups xmm5,[rax+0x10]                        
0xbc57917  movups [rbp+0x68],xmm4                        
0xbc5791b  movups [rbp+0x78],xmm5                        
0xbc5791f  xorps xmm9,[0xEF3F050]                        ; [data_ef3f050]
0xbc57927  divss xmm9,xmm2                               
0xbc5792c  movss [rbp+0x88],xmm9                         
0xbc57935  movss [rbp+0x8C],xmm1                         
0xbc5793d  movss [rbp+0x90],xmm3                         
0xbc57945  movss [rbp+0x94],xmm0                         
0xbc5794d  lea rcx,[rbp+0x98]                            
0xbc57954  mov rdx,r14                                   
0xbc57957  call 0x5667860                                ; -> sub_5667860
0xbc5795c  nop                                           
0xbc5795d  mov [rbp+0x6A8],r12                           
0xbc57964  mov rax,[rdi]                                 
0xbc57967  mov rcx,[rax]                                 
0xbc5796a  mov r8,rbx                                    
0xbc5796d  shl r8,7                                      
0xbc57971  lea rdx,[rbp+0x410]                           
0xbc57978  mov r9d,1                                     
0xbc5797e  call 0xA78940                                 ; -> sub_a78940
0xbc57983  nop                                           
0xbc57984  mov rax,[rbp+0x420]                           
0xbc5798b  mov [rbp+0x8A8],rax                           
0xbc57992  mov rax,[rbp+0x410]                           
0xbc57999  mov r15,[rbp+0x418]                           
0xbc579a0  mov rax,[rax]                                 
0xbc579a3  mov [rbp+0x870],rax                           
0xbc579aa  test r15,r15                                  
0xbc579ad  je short 0xBC579DC                            ; -> loc_bc579dc
0xbc579af  lock dec dword ptr [r15+8]                    
0xbc579b4  jne short 0xBC579DC                           ; -> loc_bc579dc
0xbc579b6  mov rax,[r15]                                 
0xbc579b9  mov rax,[rax]                                 
0xbc579bc  mov rcx,r15                                   
0xbc579bf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc579c5  lock dec dword ptr [r15+0xC]                  
0xbc579ca  jne short 0xBC579DC                           ; -> loc_bc579dc
0xbc579cc  mov rax,[r15]                                 
0xbc579cf  mov rax,[rax+8]                               
0xbc579d3  mov rcx,r15                                   
0xbc579d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc579dc:  ; from bc579ad, bc579b4, bc579ca
0xbc579dc  mov rax,[rdi]                                 
0xbc579df  mov rcx,[rax]                                 
0xbc579e2  shl rbx,6                                     
0xbc579e6  lea rdx,[rbp+0x410]                           
0xbc579ed  mov r9d,1                                     
0xbc579f3  mov r8,rbx                                    
0xbc579f6  call 0xA78940                                 ; -> sub_a78940
0xbc579fb  nop                                           
0xbc579fc  mov r12,[rbp+0x420]                           
0xbc57a03  mov rax,[rbp+0x410]                           
0xbc57a0a  mov rbx,[rbp+0x418]                           
0xbc57a11  mov rax,[rax]                                 
0xbc57a14  mov [rbp+0x878],rax                           
0xbc57a1b  test rbx,rbx                                  
0xbc57a1e  je short 0xBC57A4B                            ; -> loc_bc57a4b
0xbc57a20  lock dec dword ptr [rbx+8]                    
0xbc57a24  jne short 0xBC57A4B                           ; -> loc_bc57a4b
0xbc57a26  mov rax,[rbx]                                 
0xbc57a29  mov rax,[rax]                                 
0xbc57a2c  mov rcx,rbx                                   
0xbc57a2f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57a35  lock dec dword ptr [rbx+0xC]                  
0xbc57a39  jne short 0xBC57A4B                           ; -> loc_bc57a4b
0xbc57a3b  mov rax,[rbx]                                 
0xbc57a3e  mov rax,[rax+8]                               
0xbc57a42  mov rcx,rbx                                   
0xbc57a45  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc57a4b:  ; from bc57a1e, bc57a24, bc57a39
0xbc57a4b  mov r13,rsi                                   
0xbc57a4e  mov rax,[rdi]                                 
0xbc57a51  mov edi,[rbp+0x880]                           
0xbc57a57  mov rcx,[rax]                                 
0xbc57a5a  lea rbx,[rdi*4]                               
0xbc57a62  lea rdx,[rbp+0x410]                           
0xbc57a69  mov r9d,1                                     
0xbc57a6f  mov r8,rbx                                    
0xbc57a72  call 0xA78940                                 ; -> sub_a78940
0xbc57a77  nop                                           
0xbc57a78  mov [rbp+0x688],rdi                           
0xbc57a7f  movaps [rbp+0x780],xmm9                       
0xbc57a87  mov rdi,[rbp+0x420]                           
0xbc57a8e  mov rax,[rbp+0x410]                           
0xbc57a95  mov r15,[rbp+0x418]                           
0xbc57a9c  mov rax,[rax]                                 
0xbc57a9f  test r15,r15                                  
0xbc57aa2  je short 0xBC57ADA                            ; -> loc_bc57ada
0xbc57aa4  lock dec dword ptr [r15+8]                    
0xbc57aa9  jne short 0xBC57ADA                           ; -> loc_bc57ada
0xbc57aab  mov rsi,rax                                   
0xbc57aae  mov rax,[r15]                                 
0xbc57ab1  mov rax,[rax]                                 
0xbc57ab4  mov rcx,r15                                   
0xbc57ab7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57abd  mov rax,rsi                                   
0xbc57ac0  lock dec dword ptr [r15+0xC]                  
0xbc57ac5  jne short 0xBC57ADA                           ; -> loc_bc57ada
0xbc57ac7  mov rax,[r15]                                 
0xbc57aca  mov rax,[rax+8]                               
0xbc57ace  mov rcx,r15                                   
0xbc57ad1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57ad7  mov rax,rsi                                   

loc_bc57ada:  ; from bc57aa2, bc57aa9, bc57ac5
0xbc57ada  mov [rbp+0x680],rax                           
0xbc57ae1  add rdi,rax                                   
0xbc57ae4  mov [rbp+0x690],rdi                           
0xbc57aeb  mov rcx,rdi                                   
0xbc57aee  xor edx,edx                                   
0xbc57af0  mov r8,rbx                                    
0xbc57af3  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xbc57af8  mov rax,[rbp+0x9F8]                           
0xbc57aff  movss xmm0,[rax+0x10]                         
0xbc57b04  movss [rbp+0x8B4],xmm0                        
0xbc57b0c  mov dword ptr [rbp+0x6F0],0x3F800000          
0xbc57b16  xorps xmm0,xmm0                               
0xbc57b19  movups [rbp+0x6F4],xmm0                       
0xbc57b20  mov dword ptr [rbp+0x704],0x3F800000          
0xbc57b2a  movups [rbp+0x708],xmm0                       
0xbc57b31  mov dword ptr [rbp+0x718],0x3F800000          
0xbc57b3b  movups [rbp+0x71C],xmm0                       
0xbc57b42  mov dword ptr [rbp+0x72C],0x3F800000          
0xbc57b4c  mov dword ptr [rbp+0x7E8],0x3F800000          
0xbc57b56  movups [rbp+0x7EC],xmm0                       
0xbc57b5d  mov dword ptr [rbp+0x7FC],0x3F800000          
0xbc57b67  movups [rbp+0x800],xmm0                       
0xbc57b6e  mov dword ptr [rbp+0x810],0x3F800000          
0xbc57b78  movups [rbp+0x814],xmm0                       
0xbc57b7f  mov dword ptr [rbp+0x824],0x3F800000          
0xbc57b89  lea rcx,[rbp+0x410]                           
0xbc57b90  lea r8,[rbp+0x7E8]                            
0xbc57b97  lea rdx,[r14+0x18]                            
0xbc57b9b  call 0xAA6580                                 ; -> sub_aa6580
0xbc57ba0  nop                                           
0xbc57ba1  lea rsi,[rbp+0x1D0]                           
0xbc57ba8  lea rdx,[rbp+0x410]                           
0xbc57baf  lea r8,[rbp+0x6F0]                            
0xbc57bb6  mov rcx,rsi                                   
0xbc57bb9  call 0xAA6580                                 ; -> sub_aa6580
0xbc57bbe  nop                                           
0xbc57bbf  mov rax,[rbp+0x8A8]                           
0xbc57bc6  add rax,[rbp+0x870]                           
0xbc57bcd  mov [rbp+0x8A8],rax                           
0xbc57bd4  add r12,[rbp+0x878]                           
0xbc57bdb  lea rcx,[rbp+0x410]                           
0xbc57be2  mov rdx,rsi                                   
0xbc57be5  call 0x1999390                                ; -> sub_1999390
0xbc57bea  mov r15,[r13+0x48]                            
0xbc57bee  mov rdi,[r13+0x50]                            
0xbc57bf2  movaps xmm0,[rbp+0x7C0]                       
0xbc57bf9  unpcklps xmm0,[rbp+0x7D0]                     
0xbc57c00  addps xmm0,[0xEFFE2F0]                        ; [data_effe2f0]
0xbc57c07  movaps [rbp+0x6E0],xmm0                       
0xbc57c0e  movss xmm1,[0xEF1D470]                        ; [data_ef1d470]
0xbc57c16  movss xmm0,[rbp+0x894]                        
0xbc57c1e  addss xmm1,xmm0                               
0xbc57c22  movss [rbp+0x89C],xmm1                        
0xbc57c2a  movss xmm1,[0xEF3F048]                        ; [data_ef3f048]
0xbc57c32  addss xmm1,xmm0                               
0xbc57c36  movss [rbp+0x898],xmm1                        
0xbc57c3e  xor ebx,ebx                                   
0xbc57c40  xorps xmm6,xmm6                               
0xbc57c43  movaps xmm7,[0xEF3F050]                       ; [data_ef3f050]
0xbc57c4a  movss xmm11,[0xEEC8060]                       ; [data_eec8060]
0xbc57c53  mov rsi,[rbp+0x9F8]                           
0xbc57c5a  jmp short 0xBC57CD7                           ; -> loc_bc57cd7

loc_bc57c5c:  ; from bc588ca, bc5890a
0xbc57c5c  movaps xmm0,[rbp+0x860]                       

loc_bc57c63:  ; from bc5886e, bc58877, bc58880, bc58890, bc5889a
0xbc57c63  shl rsi,7                                     
0xbc57c67  mov rax,[rbp+0x8A8]                           
0xbc57c6e  movlps [rax+rsi],xmm10                        
0xbc57c73  movss [rax+rsi+8],xmm11                       
0xbc57c7a  movss [rax+rsi+0xC],xmm0                      
0xbc57c80  movaps xmm0,[rbp+0x6B0]                       
0xbc57c87  movups [rax+rsi+0x10],xmm0                    
0xbc57c8c  movups [rax+rsi+0x20],xmm12                   
0xbc57c92  movups [rax+rsi+0x30],xmm8                    
0xbc57c98  movups [rax+rsi+0x40],xmm14                   
0xbc57c9e  movups [rax+rsi+0x50],xmm13                   
0xbc57ca4  movups [rax+rsi+0x60],xmm9                    
0xbc57caa  movups [rax+rsi+0x70],xmm15                    
0xbc57cb0  inc rbx                                       
0xbc57cb3  mov rsi,[rbp+0x9F8]                           
0xbc57cba  movss xmm11,[0xEEC8060]                       ; [data_eec8060]
0xbc57cc3  nop [rax+rax]                                 

loc_bc57cd0:  ; from bc57dcf, bc57e08, bc57e41, bc57e7a, bc57eb3
0xbc57cd0  add r15,0xF8                                  

loc_bc57cd7:  ; from bc57c5a
0xbc57cd7  cmp r15,rdi                                   
0xbc57cda  je 0xBC5890F                                  ; -> loc_bc5890f
```

**Chunk 1 stores/reads [reg+off]:**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| rbp+0x950 | 16 | W | xmm15 save |
| rbp+0x940 | 16 | W | xmm14 save |
| rbp+0x930 | 16 | W | xmm13 save |
| rbp+0x920 | 16 | W | xmm12 save |
| rbp+0x910 | 16 | W | xmm11 save |
| rbp+0x900 | 16 | W | xmm10 save |
| rbp+0x8F0 | 16 | W | xmm9 save |
| rbp+0x8E0 | 16 | W | xmm8 save |
| rbp+0x8D0 | 16 | W | xmm7 save |
| rbp+0x8C0 | 16 | W | xmm6 save |
| rbp+0x8B8 | 8 | W | stack cookie |
| rbp+0x8A0 | 8 | W | arg3 (rdx) |
| rbp+0x7C0 | 16 | W | xmm6 (div result) |
| rbp+0x7B4 | 4 | W | xmm6 low dword |
| rbp+0x7D0 | 16 | W | xmm0 (div result) |
| rbp+0x7B8 | 4 | W | xmm0 low dword |
| rbp+0x894 | 4 | W | xmm1 low dword |
| rbp+0x7BC | 4 | W | xmm1 low dword |
| rbp+0x88C | 8 | W | cluster count? |
| rbp+0x890 | 4 | W | flags (0x80, 0x40, 4) |
| rbp+0x760 | 8 | W | data_12adf748 |
| rbp+0x768 | 8 | W | sub_bc09250 result |
| rbp+0x698 | 8 | W | data_12adf758 |
| rbp+0x6A0 | 8 | W | sub_bc09250 result |
| rbp+0x770 | 8 | W | data_12adf768 |
| rbp+0x778 | 8 | W | sub_bc09250 result |
| rbp+0x410 | 16 | W | zeroed |
| rbp+0x1D0 | 8 | W | "LightClustering" string ptr |
| rbp+0x1D8 | 8 | W | string length (0xF) |
| rbp+0x750 | 8 | W | sub_567c8b0 arg |
| rbp+0x41C | 4 | R | xmm1 src |
| rbp+0x418 | 4 | R | xmm2 src |
| rbp+0x42C | 4 | R | xmm4 src |
| rbp+0x428 | 4 | R | xmm3 src |
| rbp+0x438 | 4 | R | xmm1 src |
| rbp+0x43C | 4 | R | xmm5 src |
| rbp+0x448 | 4 | R | xmm7 src |
| rbp+0x44C | 4 | R | xmm8 src |
| rbp+0x30 | 16 | W | zeroed xmm |
| rbp+0x20 | 16 | W | zeroed xmm |
| rbp+0x10 | 16 | W | zeroed xmm |
| rbp | 16 | W | zeroed xmm |
| rbp+0x40 | 8 | W | zeroed |
| rbp+0x38 | 8 | W | rcx from rbp+0x750 |
| rbp+0x48 | 8 | W | rdi |
| rbp+0x50 | 4 | W | xmm4 low (from rbp+0x7C0) |
| rbp+0x54 | 4 | W | xmm4 low (from rbp+0x7D0) |
| rbp+0x58 | 4 | W | xmm4 low (from rbp+0x894) |
| rbp+0x5C | 8 | W | xmm4 (from data_f246ea0) |
| rbp+0x64 | 4 | W | 0x40800000 (float 4.0) |
| rbp+0x68 | 16 | W | xmm4 from [rbp+0x9F8] |
| rbp+0x78 | 16 | W | xmm5 from [rbp+0x9F8+0x10] |
| rbp+0x88 | 4 | W | xmm9 result |
| rbp+0x8C | 4 | W | xmm1 |
| rbp+0x90 | 4 | W | xmm3 |
| rbp+0x94 | 4 | W | xmm0 |
| rbp+0x6A8 | 8 | W | r12 |
| rbp+0x8A8 | 8 | W | rax from [rbp+0x420] |
| rbp+0x870 | 8 | W | rax from [rbp+0x410] |
| rbp+0x878 | 8 | W | rax from [rax] |
| rbp+0x688 | 8 | W | rdi |
| rbp+0x780 | 16 | W | xmm9 |
| rbp+0x680 | 8 | W | rax (refcount result) |
| rbp+0x690 | 8 | W | rdi + rax |
| rbp+0x8B4 | 4 | W | xmm0 from [rbp+0x9F8+0x10] |
| rbp+0x6F0 | 4 | W | 0x3F800000 (1.0) |
| rbp+0x6F4 | 16 | W | zeroed |
| rbp+0x704 | 4 | W | 0x3F800000 |
| rbp+0x708 | 16 | W | zeroed |
| rbp+0x718 | 4 | W | 0x3F800000 |
| rbp+0x71C | 16 | W | zeroed |
| rbp+0x72C | 4 | W | 0x3F800000 |
| rbp+0x7E8 | 4 | W | 0x3F800000 |
| rbp+0x7EC | 16 | W | zeroed |
| rbp+0x7FC | 4 | W | 0x3F800000 |
| rbp+0x800 | 16 | W | zeroed |
| rbp+0x810 | 4 | W | 0x3F800000 |
| rbp+0x814 | 16 | W | zeroed |
| rbp+0x824 | 4 | W | 0x3F800000 |
| rbp+0x6E0 | 16 | W | xmm0 result |
| rbp+0x89C | 4 | W | xmm1 result |
| rbp+0x898 | 4 | W | xmm1 result |
| rbp+0x860 | 16 | R | xmm0 src |
| rbp+0x8A8 | 8 | R | destination buffer |
| rbp+0x6B0 | 16 | R | xmm0 src |
| r12+0x10 | 1 | W | byte = 0 (early exit path) |
| r12+0x28 | 1 | W | byte = 0 |
| r12+0x30 | 16 | W | zeroed |
| r12+0x40 | 4 | W | 0 |

**Chunk 1 callees (in order):**
1. 0xEEC73F0 (sub_eec73f0) - called twice for division
2. 0xBC09250 (sub_bc09250) - called 3 times
3. 0x567C8B0 (sub_567c8b0) - LightClustering registration
4. 0xAB49C0 (sub_ab49c0) - unknown
5. 0x5667860 (sub_5667860) - unknown
6. 0xA78940 (sub_a78940) - called 3 times (allocator)
7. qword ptr [0xF99FFA0] = sub_eea6040 - called 4 times (deallocator)
8. 0xEEC6ED0 (sub_eec6ed0) - unknown
9. 0xAA6580 (sub_aa6580) - called twice
10. 0x1999390 (sub_1999390) - unknown

### Chunk 2: 0xbc57cd7..0xbc584de (continuation - from actual rdis output)
```
0xbc57cd7  cmp r15,rdi                                   
0xbc57cda  je 0xBC5890F                                  ; -> loc_bc5890f
0xbc57ce0  movss xmm1,[r15]                              
0xbc57ce5  movss xmm2,[r14+0x60]                         
0xbc57ceb  mulss xmm2,xmm1                               
0xbc57cef  movups xmm3,[r14+0x70]                        
0xbc57cf4  movsd xmm0,[r15+4]                            
0xbc57cfa  movss xmm4,[r14+0x80]                         
0xbc57d03  movlhps xmm4,xmm3                             
0xbc57d06  shufps xmm4,xmm3,0xE2                         
0xbc57d0a  mulps xmm4,xmm0                               
0xbc57d0d  movss xmm3,[r14+0x90]                         
0xbc57d16  unpcklps xmm2,xmm3                            
0xbc57d19  addps xmm2,xmm4                               
0xbc57d1c  movaps xmm13,xmm2                             
0xbc57d20  shufps xmm13,xmm2,0x55                        
0xbc57d25  addps xmm13,xmm2                              
0xbc57d29  shufps xmm1,xmm1,0                            
0xbc57d2d  movsd xmm2,[r14+0x58]                         
0xbc57d33  mulps xmm2,xmm1                               
0xbc57d36  movsd xmm1,[r14+0x68]                         
0xbc57d3c  movaps xmm3,xmm0                              
0xbc57d3f  shufps xmm3,xmm0,0                            
0xbc57d43  mulps xmm3,xmm1                               
0xbc57d46  addps xmm3,xmm2                               
0xbc57d49  movsd xmm1,[r14+0x78]                         
0xbc57d4f  shufps xmm0,xmm0,0x55                         
0xbc57d53  mulps xmm0,xmm1                               
0xbc57d56  movsd xmm10,[r14+0x88]                        
0xbc57d5f  addps xmm10,xmm0                              
0xbc57d63  addps xmm10,xmm3                              
0xbc57d67  movlps [rbp+0x6F0],xmm10                      
0xbc57d6f  movss [rbp+0x6F8],xmm13                       
0xbc57d78  movss xmm0,[r15+0x18]                         
0xbc57d7e  ucomiss xmm0,xmm6                             
0xbc57d81  jb short 0xBC57D90                            ; -> loc_bc57d90
0xbc57d83  sqrtss xmm0,xmm0                              
0xbc57d87  jmp short 0xBC57D96                           ; -> loc_bc57d96
0xbc57d89  nop [rax]                                     

loc_bc57d90:  ; from bc57d81
0xbc57d90  call qword ptr [0xF9A8F60]                    ; [data_f9a8f60]

loc_bc57d96:  ; from bc57d87
0xbc57d96  movaps xmm1,xmm0                              
0xbc57d99  xorps xmm1,xmm7                               
0xbc57d9c  movsd xmm2,[rbp+0x410]                        
0xbc57da4  mulps xmm2,xmm10                              
0xbc57da8  movaps xmm3,xmm2                              
0xbc57dab  shufps xmm3,xmm2,0x55                         
0xbc57daf  addss xmm3,xmm2                               
0xbc57db3  movss xmm2,[rbp+0x418]                        
0xbc57dbb  mulss xmm2,xmm13                              
0xbc57dc0  addss xmm2,xmm3                               
0xbc57dc4  addss xmm2,[rbp+0x41C]                        
0xbc57dcc  ucomiss xmm1,xmm2                             
0xbc57dcf  jae 0xBC57CD0                                 ; -> loc_bc57cd0

loc_bc57cd0:  ; from bc57dcf, bc57e08, bc57e41, bc57e7a, bc57eb3
0xbc57cd0  add r15,0xF8                                  

0xbc57dd5  movsd xmm2,[rbp+0x420]                        
0xbc57ddd  mulps xmm2,xmm10                              
0xbc57de1  movaps xmm3,xmm2                              
0xbc57de4  shufps xmm3,xmm2,0x55                         
0xbc57de8  addss xmm3,xmm2                               
0xbc57dec  movss xmm2,[rbp+0x428]                        
0xbc57df4  mulss xmm2,xmm13                              
0xbc57df9  addss xmm2,xmm3                               
0xbc57dfd  addss xmm2,[rbp+0x42C]                        
0xbc57e05  ucomiss xmm1,xmm2                             
0xbc57e08  jae 0xBC57CD0                                 ; -> loc_bc57cd0

0xbc57e0e  movsd xmm2,[rbp+0x430]                        
0xbc57e16  mulps xmm2,xmm10                              
0xbc57e1a  movaps xmm3,xmm2                              
0xbc57e1d  shufps xmm3,xmm2,0x55                         
0xbc57e21  addss xmm3,xmm2                               
0xbc57e25  movss xmm2,[rbp+0x438]                        
0xbc57e2d  mulss xmm2,xmm13                              
0xbc57e32  addss xmm2,xmm3                               
0xbc57e36  addss xmm2,[rbp+0x43C]                        
0xbc57e3e  ucomiss xmm1,xmm2                             
0xbc57e41  jae 0xBC57CD0                                 ; -> loc_bc57cd0

0xbc57e47  movsd xmm2,[rbp+0x440]                        
0xbc57e4f  mulps xmm2,xmm10                              
0xbc57e53  movaps xmm3,xmm2                              
0xbc57e56  shufps xmm3,xmm2,0x55                         
0xbc57e5a  addss xmm3,xmm2                               
0xbc57e5e  movss xmm2,[rbp+0x448]                        
0xbc57e66  mulss xmm2,xmm13                              
0xbc57e6b  addss xmm2,xmm3                               
0xbc57e6f  addss xmm2,[rbp+0x44C]                        
0xbc57e77  ucomiss xmm1,xmm2                             
0xbc57e7a  jae 0xBC57CD0                                 ; -> loc_bc57cd0

0xbc57e80  movsd xmm2,[rbp+0x450]                        
0xbc57e88  mulps xmm2,xmm10                              
0xbc57e8c  movaps xmm3,xmm2                              
0xbc57e8f  shufps xmm3,xmm2,0x55                         
0xbc57e93  addss xmm3,xmm2                               
0xbc57e97  movss xmm2,[rbp+0x458]                        
0xbc57e9f  mulss xmm2,xmm13                              
0xbc57ea4  addss xmm2,xmm3                               
0xbc57ea8  addss xmm2,[rbp+0x45C]                        
0xbc57eb0  ucomiss xmm1,xmm2                             
0xbc57eb3  jae 0xBC57CD0                                 ; -> loc_bc57cd0

0xbc57eb9  movaps xmm12,xmm11                            
0xbc57ebd  divss xmm12,[r14+0x2C]                        
0xbc57ec3  divss xmm11,[r14+0x18]                        
0xbc57ec9  mov qword ptr [rbp+0x7E8],0                   
0xbc57ed4  mov dword ptr [rbp+0x7F0],0                   
0xbc57ede  mov qword ptr [rbp+0x830],0                   
0xbc57ee9  mov dword ptr [rbp+0x838],0                   
0xbc57ef3  divss xmm11,xmm12                             
0xbc57ef8  cmp byte ptr [rsi+0x1C],1                     
0xbc57efc  movaps [rbp+0x860],xmm0                       
0xbc57f03  jne short 0xBC57F7A                           ; -> loc_bc57f7a

loc_bc57f05:  ; from bc57efc
0xbc57f05  movsd xmm1,[rsi+0x14]                         
0xbc57f0a  movsd [rbp+0x1D0],xmm1                        
0xbc57f12  lea rax,[rbp+0x830]                           
0xbc57f19  mov [rsp+0x48],rax                            
0xbc57f1e  lea rax,[rbp+0x7E8]                           
0xbc57f25  mov [rsp+0x40],rax                            
0xbc57f2a  lea rax,[rbp+0x1D0]                           
0xbc57f31  mov [rsp+0x38],rax                            
0xbc57f36  movss [rsp+0x30],xmm11                        
0xbc57f3d  movss [rsp+0x28],xmm12                        
0xbc57f44  lea rax,[rbp+0x7B4]                           
0xbc57f4b  mov [rsp+0x20],rax                            
0xbc57f50  lea rcx,[rbp+0x6F0]                           
0xbc57f57  movaps xmm1,xmm0                              
0xbc57f5a  movaps xmm2,[rbp+0x780]                       
0xbc57f61  movss xmm3,[rbp+0x8B4]                        
0xbc57f69  call 0xBC5B130                                ; -> sub_bc5b130

loc_bc57f6e:  ; from bc57f69
0xbc57f6e  movaps xmm0,[rbp+0x860]                       
0xbc57f75  jmp 0xBC583EC                                 ; -> loc_bc583ec

loc_bc57f7a:  ; from bc57f03
0xbc57f7a  movsd xmm15,[rsi+0x14]                        
0xbc57f80  movaps xmm14,xmm15                            
0xbc57f84  shufps xmm14,xmm15,0x55                       
0xbc57f89  movsd [rbp+0x1D0],xmm15                       
0xbc57f92  movaps xmm8,xmm13                             
0xbc57f96  xorps xmm8,xmm7                               
0xbc57f9a  movaps xmm1,xmm10                             
0xbc57f9e  mulps xmm1,xmm10                              
0xbc57fa2  movaps xmm2,xmm1                              
0xbc57fa5  shufps xmm2,xmm1,0x55                         
0xbc57fa9  addss xmm2,xmm1                               
0xbc57fad  movaps xmm1,xmm13                             
0xbc57fb1  mulss xmm1,xmm13                              
0xbc57fb6  addss xmm1,xmm2                               
0xbc57fba  sqrtss xmm1,xmm1                              
0xbc57fbe  ucomiss xmm0,xmm1                             
0xbc57fc1  movaps xmm3,xmm8                              
0xbc57fc5  subss xmm3,xmm0                               
0xbc57fc9  jbe 0xBC58081                                 ; -> loc_bc58081

0xbc57fcf  mov qword ptr [rbp+0x7E8],0                   
0xbc57fda  movaps xmm1,[rbp+0x6E0]                       
0xbc57fe1  movlps [rbp+0x830],xmm1                       
0xbc57fe8  maxss xmm3,[rbp+0x780]                        
0xbc57ff0  xorps xmm8,xmm8                               
0xbc57ff4  ucomiss xmm15,xmm3                            
0xbc57ff8  xorps xmm2,xmm2                               
0xbc57ffb  movss xmm11,[0xEEC8060]                       ; [data_eec8060]
0xbc58004  ja 0xBC582E7                                  ; -> loc_bc582e7
0xbc5800a  ucomiss xmm14,xmm3                            
0xbc5800e  movaps xmm2,xmm11                             
0xbc58012  ja 0xBC582E7                                  ; -> loc_bc582e7
0xbc58018  divss xmm3,xmm14                              
0xbc5801d  movaps xmm0,xmm3                              
0xbc58020  mov rsi,[0xF9A8ED0]                           ; [data_f9a8ed0]
0xbc58027  call rsi                                      
0xbc58029  movaps xmm9,xmm0                              
0xbc5802d  movss xmm0,[rbp+0x8B4]                        
0xbc58035  divss xmm0,xmm14                              
0xbc5803a  call rsi                                      
0xbc5803c  divss xmm9,xmm0                               
0xbc58041  xorps xmm1,xmm1                               
0xbc58044  maxss xmm1,xmm9                               
0xbc58049  movaps xmm0,xmm11                             
0xbc5804d  minss xmm0,xmm1                               
0xbc58051  mulss xmm0,[rbp+0x898]                        
0xbc58059  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc5805e  movaps xmm1,xmm0                              
0xbc58061  movaps xmm0,[rbp+0x860]                       
0xbc58068  addss xmm1,[0xEF3F01C]                        ; [data_ef3f01c]
0xbc58070  movss xmm2,[rbp+0x89C]                        
0xbc58078  minss xmm2,xmm1                               
0xbc5807c  jmp 0xBC582E7                                 ; -> loc_bc582e7

loc_bc58081:  ; from bc57fc9
0xbc58081  movss [rbp+0x82C],xmm3                        
0xbc58089  movaps [rbp-0x10],xmm15                       
0xbc5808e  movaps [rbp+0x6B0],xmm14                      
0xbc58096  divss xmm0,xmm1                               
0xbc5809a  xorps xmm1,xmm1                               
0xbc5809d  maxss xmm1,xmm0                               
0xbc580a1  movss xmm0,[0xEEC8060]                        ; [data_eec8060]
0xbc580a9  minss xmm0,xmm1                               
0xbc580ad  call qword ptr [0xF9A8DB8]                    ; [data_f9a8db8]

0xbc580b3  movaps xmm15,xmm0                             
0xbc580b7  movaps xmm0,xmm10                             
0xbc580bb  movaps xmm1,xmm8                              
0xbc580bf  mov rsi,[0xF9A8DD8]                           ; [data_f9a8dd8]
0xbc580c6  call rsi                                      
0xbc580c8  movaps xmm9,xmm0                              
0xbc580cc  movaps xmm0,xmm10                             
0xbc580d0  shufps xmm0,xmm10,0x55                        
0xbc580d5  movaps xmm1,xmm8                              
0xbc580d9  call rsi                                      
0xbc580db  movaps xmm8,xmm0                              
0xbc580df  unpcklps xmm8,xmm9                            
0xbc580e3  movlhps xmm8,xmm8                             
0xbc580e7  shufps xmm15,xmm15,0                          
0xbc580ec  movaps xmm9,xmm8                              
0xbc580f0  addps xmm9,xmm15                              
0xbc580f4  movaps xmm14,xmm12                            
0xbc580f8  mulss xmm14,xmm11                             
0xbc580fd  movaps xmm0,xmm14                             
0xbc58101  mov rsi,[0xF9A8DE0]                           ; [data_f9a8de0]
0xbc58108  call rsi                                      
0xbc5810a  movaps xmm6,xmm0                              
0xbc5810d  movaps xmm0,xmm12                             
0xbc58111  call rsi                                      
0xbc58113  ucomiss xmm0,xmm9                             
0xbc58117  jb 0xBC58380                                  ; -> loc_bc58380
0xbc5811d  subps xmm8,xmm15                              
0xbc58121  movaps xmm1,xmm6                              
0xbc58124  xorps xmm1,xmm7                               
0xbc58127  movaps xmm2,xmm8                              
0xbc5812b  shufps xmm2,xmm8,0xFF                         
0xbc58130  ucomiss xmm2,xmm1                             
0xbc58133  jb 0xBC58380                                  ; -> loc_bc58380
0xbc58139  movaps xmm1,xmm9                              
0xbc5813d  shufps xmm1,xmm9,0x55                         
0xbc58142  ucomiss xmm6,xmm1                             
0xbc58145  jb 0xBC58380                                  ; -> loc_bc58380
0xbc5814b  xorps xmm0,xmm7                               
0xbc5814e  movaps xmm1,xmm8                              
0xbc58152  unpckhpd xmm1,xmm8                            
0xbc58157  ucomiss xmm1,xmm0                             
0xbc5815a  jb 0xBC58380                                  ; -> loc_bc58380
0xbc58160  movsd xmm8,xmm9                               
0xbc58165  unpcklps xmm12,xmm14                          
0xbc58169  movlhps xmm12,xmm12                           
0xbc5816d  divps xmm8,xmm12                              
0xbc58171  movaps xmm0,[0xEF40DE0]                       ; [data_ef40de0]
0xbc58178  addps xmm8,xmm0                               
0xbc5817c  mulps xmm8,[0xEF40DC0]                        ; [data_ef40dc0]
0xbc58184  xorps xmm9,xmm9                               
0xbc58188  maxps xmm9,xmm8                               
0xbc5818c  cmpltps xmm0,xmm9                             
0xbc58191  movmskps esi,xmm0                             
0xbc58194  movss xmm11,[0xEEC8060]                       ; [data_eec8060]
0xbc5819d  movaps xmm0,xmm11                             
0xbc581a1  test sil,8                                    
0xbc581a5  jne short 0xBC581B0                           ; -> loc_bc581b0
0xbc581a7  movaps xmm0,xmm9                              
0xbc581ab  shufps xmm0,xmm9,0xFF                         

loc_bc581b0:  ; from bc581a5
0xbc581b0  mulss xmm0,[rbp+0x7C0]                        
0xbc581b8  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc581bd  movaps xmm8,xmm0                              
0xbc581c1  movaps xmm0,xmm11                             
0xbc581c5  test sil,2                                    
0xbc581c9  movaps xmm14,[rbp+0x6B0]                      
0xbc581d1  movaps xmm15,[rbp-0x10]                       
0xbc581d6  xorps xmm6,xmm6                               
0xbc581d9  jne short 0xBC581E4                           ; -> loc_bc581e4
0xbc581db  movaps xmm0,xmm9                              
0xbc581df  shufps xmm0,xmm9,0x55                         

loc_bc581e4:  ; from bc581d9
0xbc581e4  mulss xmm0,[rbp+0x7C0]                        
0xbc581ec  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc581f1  movaps xmm12,xmm0                             
0xbc581f5  movaps xmm0,xmm11                             
0xbc581f9  test sil,4                                    
0xbc581fd  jne short 0xBC58208                           ; -> loc_bc58208
0xbc581ff  movaps xmm0,xmm9                              
0xbc58203  unpckhpd xmm0,xmm9                            

loc_bc58208:  ; from bc581fd
0xbc58208  mulss xmm0,[rbp+0x7D0]                        
0xbc58210  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58215  unpcklps xmm8,xmm0                            
0xbc58219  movaps xmm0,[rbp+0x6E0]                       
0xbc58220  minps xmm0,xmm8                               
0xbc58224  movlps [rbp+0x7E8],xmm0                       
0xbc5822b  movaps xmm0,xmm11                             
0xbc5822f  test sil,1                                    
0xbc58233  jne short 0xBC58239                           ; -> loc_bc58239
0xbc58235  movaps xmm0,xmm9                              

loc_bc58239:  ; from bc58233
0xbc58239  movss xmm9,[rbp+0x82C]                        
0xbc58242  maxss xmm9,[rbp+0x780]                        
0xbc5824b  mulss xmm0,[rbp+0x7D0]                        
0xbc58253  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58258  unpcklps xmm12,xmm0                           
0xbc5825c  movaps xmm0,[rbp+0x6E0]                       
0xbc58263  minps xmm0,xmm12                              
0xbc58267  movlps [rbp+0x830],xmm0                       
0xbc5826e  xorps xmm8,xmm8                               
0xbc58272  ucomiss xmm15,xmm9                            
0xbc58276  xorps xmm2,xmm2                               
0xbc58279  ja short 0xBC582E0                            ; -> loc_bc582e0
0xbc5827b  ucomiss xmm14,xmm9                            
0xbc5827f  movaps xmm2,xmm11                             
0xbc58283  ja short 0xBC582E0                            ; -> loc_bc582e0
0xbc58285  divss xmm9,xmm14                              
0xbc5828a  movaps xmm0,xmm9                              
0xbc5828e  mov rsi,[0xF9A8ED0]                           ; [data_f9a8ed0]
0xbc58295  call rsi                                      
0xbc58297  movaps xmm9,xmm0                              
0xbc5829b  movss xmm0,[rbp+0x8B4]                        
0xbc582a3  divss xmm0,xmm14                              
0xbc582a8  call rsi                                      
0xbc582aa  divss xmm9,xmm0                               
0xbc582af  xorps xmm1,xmm1                               
0xbc582b2  maxss xmm1,xmm9                               
0xbc582b7  movaps xmm0,xmm11                             
0xbc582bb  minss xmm0,xmm1                               
0xbc582bf  mulss xmm0,[rbp+0x898]                        
0xbc582c7  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc582cc  addss xmm0,[0xEF3F01C]                        ; [data_ef3f01c]
0xbc582d4  movss xmm2,[rbp+0x89C]                        
0xbc582dc  minss xmm2,xmm0                               

loc_bc582e0:  ; from bc58279, bc58283
0xbc582e0  movaps xmm0,[rbp+0x860]                       

loc_bc582e7:  ; from bc58004, bc58012, bc5807c
0xbc582e7  movaps xmm1,xmm0                              
0xbc582ea  subss xmm1,xmm13                              
0xbc582ef  minss xmm1,[rbp+0x8B4]                        
0xbc582f7  movss [rbp+0x7F0],xmm2                        
0xbc582ff  ucomiss xmm15,xmm1                            
0xbc58303  ja short 0xBC58375                            ; -> loc_bc58375
0xbc58305  ucomiss xmm14,xmm1                            
0xbc58309  movaps xmm8,xmm11                             
0xbc5830d  ja short 0xBC58375                            ; -> loc_bc58375
0xbc5830f  divss xmm1,xmm14                              
0xbc58314  movaps xmm0,xmm1                              
0xbc58317  mov rsi,[0xF9A8ED0]                           ; [data_f9a8ed0]
0xbc5831e  call rsi                                      
0xbc58320  movaps xmm9,xmm0                              
0xbc58324  movss xmm0,[rbp+0x8B4]                        
0xbc5832c  divss xmm0,xmm14                              
0xbc58331  call rsi                                      
0xbc58333  divss xmm9,xmm0                               
0xbc58338  xorps xmm1,xmm1                               
0xbc5833b  maxss xmm1,xmm9                               
0xbc58340  movaps xmm0,xmm11                             
0xbc58344  minss xmm0,xmm1                               
0xbc58348  mulss xmm0,[rbp+0x898]                        
0xbc58350  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58355  movaps xmm1,xmm0                              
0xbc58358  movaps xmm0,[rbp+0x860]                       
0xbc5835f  addss xmm1,[0xEF3F01C]                        ; [data_ef3f01c]
0xbc58367  movss xmm8,[rbp+0x89C]                        
0xbc58370  minss xmm8,xmm1                               

loc_bc58375:  ; from bc58303, bc5830d
0xbc58375  movss [rbp+0x838],xmm8                        
0xbc5837e  jmp short 0xBC583EC                           ; -> loc_bc583ec

loc_bc58380:  ; from bc58117, bc58133, bc58145, bc5815a
0xbc58380  lea rax,[rbp+0x830]                           
0xbc58387  mov [rsp+0x48],rax                            
0xbc5838c  lea rax,[rbp+0x7E8]                           
0xbc58393  mov [rsp+0x40],rax                            
0xbc58398  lea rax,[rbp+0x1D0]                           
0xbc5839f  mov [rsp+0x38],rax                            
0xbc583a4  movss [rsp+0x30],xmm11                        
0xbc583ab  movss [rsp+0x28],xmm12                        
0xbc583b2  lea rax,[rbp+0x7B4]                           
0xbc583b9  mov [rsp+0x20],rax                            
0xbc583be  lea rcx,[rbp+0x6F0]                           
0xbc583c5  movaps xmm9,[rbp+0x860]                       
0xbc583cd  movaps xmm1,xmm9                              
0xbc583d1  movaps xmm2,[rbp+0x780]                       
0xbc583d8  movss xmm3,[rbp+0x8B4]                        
0xbc583e0  call 0xBC5B130                                ; -> sub_bc5b130
0xbc583e5  movaps xmm0,xmm9                              
0xbc583e9  xorps xmm6,xmm6                               

loc_bc583ec:  ; from bc57f75, bc5837e
0xbc583ec  cmp qword ptr [rbp+0x9D8],0                   
0xbc583f4  sete dl                                       
0xbc583f7  xorps xmm1,xmm1                               
0xbc583fa  maxss xmm1,[rbp+0x7F0]                        
0xbc58402  movsd xmm2,[rbp+0x7E8]                        
0xbc5840a  xorps xmm8,xmm8                               
0xbc5840e  xorps xmm3,xmm3                               
0xbc58411  maxps xmm3,xmm2                               
0xbc58414  movlps [rbp+0x7E8],xmm3                       
0xbc5841b  movss xmm2,[rbp+0x89C]                        
0xbc58423  minss xmm2,[rbp+0x838]                        
0xbc5842b  movss [rbp+0x7F0],xmm1                        
0xbc58433  movsd xmm4,[rbp+0x830]                        
0xbc5843b  movaps xmm5,[rbp+0x6E0]                       
0xbc58442  minps xmm5,xmm4                               
0xbc58445  movlps [rbp+0x830],xmm5                       
0xbc5844c  movss [rbp+0x838],xmm2                        
0xbc58454  movsxd rsi,ebx                                
0xbc58457  mov rax,rsi                                   
0xbc5845a  shl rax,6                                     
0xbc5845e  movlps [r12+rax],xmm3                         
0xbc58463  movss [r12+rax+8],xmm1                        
0xbc5846a  mov dword ptr [r12+rax+0xC],0                 
0xbc58473  movlps [r12+rax+0x10],xmm5                    
0xbc58479  movss [r12+rax+0x18],xmm2                     
0xbc58480  mov dword ptr [r12+rax+0x1C],0                
0xbc58489  movlps [r12+rax+0x20],xmm10                   
0xbc5848f  movss [r12+rax+0x28],xmm13                    
0xbc58496  mov dword ptr [r12+rax+0x2C],0                
0xbc5849f  mov [r12+rax+0x30],esi                        
0xbc584a4  movss [r12+rax+0x34],xmm0                     
0xbc584ab  mov qword ptr [r12+rax+0x38],0                
0xbc584b4  movsd xmm10,[r15]                             
0xbc584b9  movss xmm11,[r15+8]                           
0xbc584bf  movdqu xmm1,[r15+0xC]                         
0xbc584c5  movdqa [rbp+0x6B0],xmm1                       
0xbc584cd  mov rcx,[rbp+0x9E0]                           
0xbc584d4  movzx eax,word ptr [rcx]                      
0xbc584d7  movzx ecx,word ptr [rcx+2]                    
0xbc584db  test ax,ax                                    
0xbc584de  sete r8b                                      
```

**Chunk 2 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| r15 | 4 | R | xmm1 src (cluster data) |
| r14+0x60 | 4 | R | xmm2 src |
| r14+0x70 | 16 | R | xmm3 src |
| r15+4 | 8 | R | xmm0 src |
| r14+0x80 | 4 | R | xmm4 src |
| r14+0x90 | 4 | R | xmm3 src |
| r14+0x58 | 8 | R | xmm2 src |
| r14+0x68 | 8 | R | xmm1 src |
| r14+0x78 | 8 | R | xmm1 src |
| r14+0x88 | 8 | R | xmm10 src |
| r14+0x2C | 4 | R | xmm12 divisor |
| r14+0x18 | 4 | R | xmm11 divisor |
| r15+0x18 | 4 | R | xmm0 src (sqrt check) |
| rbp+0x410..0x45C | 4 each | R | bounds check values |
| rbp+0x6F0 | 8 | W | xmm10 low (movlps) |
| rbp+0x6F8 | 4 | W | xmm13 |
| rbp+0x860 | 16 | W | xmm0 save |
| rbp+0x7E8 | 8 | W | zeroed |
| rbp+0x7F0 | 4 | W | zeroed |
| rbp+0x830 | 8 | W | zeroed / movlps |
| rbp+0x838 | 4 | W | zeroed |
| rbp+0x1D0 | 8 | W | xmm1/xmm15 |
| rbp+0x6B0 | 16 | W | xmm14 |
| rbp-0x10 | 16 | W | xmm15 |
| rbp+0x82C | 4 | W | xmm3 |
| rbp+0x780 | 4 | R | maxss bound |
| rbp+0x8B4 | 4 | R | xmm3 bound |
| rbp+0x898 | 4 | R | xmm0 multiplier |
| rbp+0x89C | 4 | R | xmm2 min bound |
| rbp+0x7C0 | 4 | R | xmm0 mulss |
| rbp+0x7D0 | 4 | R | xmm0 mulss |
| r12+rax*0x40 | 16 | W | cluster output (movlps/movss) |
| r12+rax*0x40+8 | 4 | W | cluster output |
| r12+rax*0x40+0xC | 4 | W | zero |
| r12+rax*0x40+0x10 | 8 | W | cluster output |
| r12+rax*0x40+0x18 | 4 | W | cluster output |
| r12+rax*0x40+0x1C | 4 | W | zero |
| r12+rax*0x40+0x20 | 8 | W | cluster output |
| r12+rax*0x40+0x28 | 4 | W | cluster output |
| r12+rax*0x40+0x2C | 4 | W | zero |
| r12+rax*0x40+0x30 | 4 | W | esi (index) |
| r12+rax*0x40+0x34 | 4 | W | xmm0 |
| r12+rax*0x40+0x38 | 8 | W | zero |

**Chunk 2 callees (in order):**
1. qword ptr [0xF9A8F60] - sqrt fallback
2. 0xBC5B130 (sub_bc5b130) - called twice
3. qword ptr [0xF9A8DB8] - math helper
4. qword ptr [0xF9A8DD8] - math helper  
5. qword ptr [0xF9A8DE0] - math helper
6. qword ptr [0xF9A8ED0] - math helper (called multiple times)
7. 0xEEC75A0 (sub_eec75a0) - called multiple times

### Chunk 3: 0xbc584de..0xbc58d0e (continuation - from actual rdis output)
```
0xbc584de  sete r8b                                      
0xbc584e2  or r8b,dl                                     
0xbc584e5  test cx,cx                                    
0xbc584e8  sete dl                                       
0xbc584eb  or dl,r8b                                     
0xbc584ee  jne 0xBC58586                                 ; -> loc_bc58586
0xbc584f4  mov rdx,[r15+0x30]                            
0xbc584f8  test rdx,rdx                                  
0xbc584fb  je 0xBC58586                                  ; -> loc_bc58586
0xbc58501  cmp dword ptr [rdx+8],0                       
0xbc58505  xorps xmm12,xmm12                             
0xbc58509  je short 0xBC5858A                            ; -> loc_bc5858a
0xbc5850b  lea r8,[r15+0x28]                             
0xbc5850f  mov rcx,[rbp+0x9D8]                           
0xbc58516  mov rax,[rcx]                                 
0xbc58519  mov rax,[rax+0x30]                            
0xbc5851d  lea rdx,[rbp+0x1D0]                           
0xbc58524  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5852a  nop                                           
0xbc5852b  cmp byte ptr [rbp+0x1E0],1                    
0xbc58532  jne short 0xBC5856F                           ; -> loc_bc5856f
0xbc58534  mov rax,[rbp+0x9E0]                           
0xbc5853b  movd xmm0,[rax]                               
0xbc5853f  pshufd xmm0,xmm0,0                            
0xbc58544  pxor xmm1,xmm1                                
0xbc58548  punpcklwd xmm0,xmm1                           
0xbc5854c  cvtdq2ps xmm0,xmm0                            
0xbc5854f  movq xmm1,[rbp+0x1D0]                         
0xbc58557  movq xmm2,[rbp+0x1D8]                         
0xbc5855f  paddd xmm2,xmm1                               
0xbc58563  punpcklqdq xmm1,xmm2                          
0xbc58567  cvtdq2ps xmm12,xmm1                           
0xbc5856b  divps xmm12,xmm0                              

loc_bc5856f:  ; from bc58532
0xbc5856f  mov rcx,[rbp+0x9E0]                           
0xbc58576  movzx eax,word ptr [rcx]                      
0xbc58579  movzx ecx,word ptr [rcx+2]                    
0xbc5857d  movaps xmm0,[rbp+0x860]                       
0xbc58584  jmp short 0xBC5858A                           ; -> loc_bc5858a

loc_bc58586:  ; from bc584ee, bc584fb
0xbc58586  xorps xmm12,xmm12                             

loc_bc5858a:  ; from bc58509, bc58584
0xbc5858a  cmp qword ptr [rbp+0x9D8],0                   
0xbc58592  sete dl                                       
0xbc58595  test ax,ax                                    
0xbc58598  sete r8b                                      
0xbc5859c  or r8b,dl                                     
0xbc5859f  test cx,cx                                    
0xbc585a2  sete dl                                       
0xbc585a5  or dl,r8b                                     
0xbc585a8  jne 0xBC58636                                 ; -> loc_bc58636
0xbc585ae  mov rdx,[r15+0x50]                            
0xbc585b2  test rdx,rdx                                  
0xbc585b5  je short 0xBC58636                            ; -> loc_bc58636
0xbc585b7  cmp dword ptr [rdx+8],0                       
0xbc585bb  je short 0xBC58636                            ; -> loc_bc58636
0xbc585bd  lea r8,[r15+0x48]                             
0xbc585c1  mov rcx,[rbp+0x9D8]                           
0xbc585c8  mov rax,[rcx]                                 
0xbc585cb  mov rax,[rax+0x30]                            
0xbc585cf  lea rdx,[rbp+0x1D0]                           
0xbc585d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc585dc  nop                                           
0xbc585dd  cmp byte ptr [rbp+0x1E0],1                    
0xbc585e4  jne short 0xBC58621                           ; -> loc_bc58621
0xbc585e6  mov rax,[rbp+0x9E0]                           
0xbc585ed  movd xmm0,[rax]                               
0xbc585f1  pshufd xmm0,xmm0,0                            
0xbc585f6  pxor xmm1,xmm1                                
0xbc585fa  punpcklwd xmm0,xmm1                           
0xbc585fe  cvtdq2ps xmm0,xmm0                            
0xbc58601  movq xmm1,[rbp+0x1D0]                         
0xbc58609  movq xmm2,[rbp+0x1D8]                         
0xbc58611  paddd xmm2,xmm1                               
0xbc58615  punpcklqdq xmm1,xmm2                          
0xbc58619  cvtdq2ps xmm8,xmm1                            
0xbc5861d  divps xmm8,xmm0                               

loc_bc58621:  ; from bc585e4
0xbc58621  mov rcx,[rbp+0x9E0]                           
0xbc58628  movzx eax,word ptr [rcx]                      
0xbc5862b  movzx ecx,word ptr [rcx+2]                    
0xbc5862f  movaps xmm0,[rbp+0x860]                       

loc_bc58636:  ; from bc585a8, bc585b5, bc585bb
0xbc58636  xorps xmm13,xmm13                             
0xbc5863a  cmp qword ptr [rbp+0x9D8],0                   
0xbc58642  je 0xBC586EC                                  ; -> loc_bc586ec
0xbc58648  test ax,ax                                    
0xbc5864b  je 0xBC586EC                                  ; -> loc_bc586ec
0xbc58651  test cx,cx                                    
0xbc58654  je 0xBC586EC                                  ; -> loc_bc586ec
0xbc5865a  mov rdx,[r15+0x70]                            
0xbc5865e  test rdx,rdx                                  
0xbc58661  je 0xBC586EC                                  ; -> loc_bc586ec
0xbc58667  cmp dword ptr [rdx+8],0                       
0xbc5866b  xorps xmm14,xmm14                             
0xbc5866f  je short 0xBC586F0                            ; -> loc_bc586f0
0xbc58671  lea r8,[r15+0x68]                             
0xbc58675  mov rcx,[rbp+0x9D8]                           
0xbc5867c  mov rax,[rcx]                                 
0xbc5867f  mov rax,[rax+0x30]                            
0xbc58683  lea rdx,[rbp+0x1D0]                           
0xbc5868a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58690  nop                                           
0xbc58691  cmp byte ptr [rbp+0x1E0],1                    
0xbc58698  jne short 0xBC586D5                           ; -> loc_bc586d5
0xbc5869a  mov rax,[rbp+0x9E0]                           
0xbc586a1  movd xmm0,[rax]                               
0xbc586a5  pshufd xmm0,xmm0,0                            
0xbc586aa  pxor xmm1,xmm1                                
0xbc586ae  punpcklwd xmm0,xmm1                           
0xbc586b2  cvtdq2ps xmm0,xmm0                            
0xbc586b5  movq xmm1,[rbp+0x1D0]                         
0xbc586bd  movq xmm2,[rbp+0x1D8]                         
0xbc586c5  paddd xmm2,xmm1                               
0xbc586c9  punpcklqdq xmm1,xmm2                          
0xbc586cd  cvtdq2ps xmm14,xmm1                           
0xbc586d1  divps xmm14,xmm0                              

loc_bc586d5:  ; from bc58698
0xbc586d5  mov rcx,[rbp+0x9E0]                           
0xbc586dc  movzx eax,word ptr [rcx]                      
0xbc586df  movzx ecx,word ptr [rcx+2]                    
0xbc586e3  movaps xmm0,[rbp+0x860]                       
0xbc586ea  jmp short 0xBC586F0                           ; -> loc_bc586f0

loc_bc586ec:  ; from bc58642, bc5864b, bc58654, bc58661
0xbc586ec  xorps xmm14,xmm14                             

loc_bc586f0:  ; from bc5866f, bc586ea
0xbc586f0  cmp qword ptr [rbp+0x9D8],0                   
0xbc586f8  je 0xBC587A2                                  ; -> loc_bc587a2
0xbc586fe  test ax,ax                                    
0xbc58701  je 0xBC587A2                                  ; -> loc_bc587a2
0xbc58707  test cx,cx                                    
0xbc5870a  je 0xBC587A2                                  ; -> loc_bc587a2
0xbc58710  mov rdx,[r15+0x90]                            
0xbc58717  test rdx,rdx                                  
0xbc5871a  je 0xBC587A2                                  ; -> loc_bc587a2
0xbc58720  cmp dword ptr [rdx+8],0                       
0xbc58724  je short 0xBC587A2                            ; -> loc_bc587a2
0xbc58726  lea r8,[r15+0x88]                             
0xbc5872d  mov rcx,[rbp+0x9D8]                           
0xbc58734  mov rax,[rcx]                                 
0xbc58737  mov rax,[rax+0x30]                            
0xbc5873b  lea rdx,[rbp+0x1D0]                           
0xbc58742  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58748  nop                                           
0xbc58749  cmp byte ptr [rbp+0x1E0],1                    
0xbc58750  jne short 0xBC5878D                           ; -> loc_bc5878d
0xbc58752  mov rax,[rbp+0x9E0]                           
0xbc58759  movd xmm0,[rax]                               
0xbc5875d  pshufd xmm0,xmm0,0                            
0xbc58762  pxor xmm1,xmm1                                
0xbc58766  punpcklwd xmm0,xmm1                           
0xbc5876a  cvtdq2ps xmm0,xmm0                            
0xbc5876d  movq xmm1,[rbp+0x1D0]                         
0xbc58775  movq xmm2,[rbp+0x1D8]                         
0xbc5877d  paddd xmm2,xmm1                               
0xbc58781  punpcklqdq xmm1,xmm2                          
0xbc58785  cvtdq2ps xmm13,xmm1                           
0xbc58789  divps xmm13,xmm0                              

loc_bc5878d:  ; from bc58750
0xbc5878d  mov rcx,[rbp+0x9E0]                           
0xbc58794  movzx eax,word ptr [rcx]                      
0xbc58797  movzx ecx,word ptr [rcx+2]                    
0xbc5879b  movaps xmm0,[rbp+0x860]                       

loc_bc587a2:  ; from bc586f8, bc58701, bc5870a, bc5871a, bc58724
0xbc587a2  xorps xmm15,xmm15                             
0xbc587a6  cmp qword ptr [rbp+0x9D8],0                   
0xbc587ae  je 0xBC58862                                  ; -> loc_bc58862
0xbc587b4  test ax,ax                                    
0xbc587b7  je 0xBC58862                                  ; -> loc_bc58862
0xbc587bd  test cx,cx                                    
0xbc587c0  je 0xBC58862                                  ; -> loc_bc58862
0xbc587c6  mov rdx,[r15+0xB0]                            
0xbc587cd  test rdx,rdx                                  
0xbc587d0  je 0xBC58862                                  ; -> loc_bc58862
0xbc587d6  cmp dword ptr [rdx+8],0                       
0xbc587da  xorps xmm9,xmm9                               
0xbc587de  je 0xBC58866                                  ; -> loc_bc58866
0xbc587e4  lea r8,[r15+0xA8]                             
0xbc587eb  mov rcx,[rbp+0x9D8]                           
0xbc587f2  mov rax,[rcx]                                 
0xbc587f5  mov rax,[rax+0x30]                            
0xbc587f9  lea rdx,[rbp+0x1D0]                           
0xbc58800  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58806  nop                                           
0xbc58807  cmp byte ptr [rbp+0x1E0],1                    
0xbc5880e  jne short 0xBC5884B                           ; -> loc_bc5884b
0xbc58810  mov rax,[rbp+0x9E0]                           
0xbc58817  movd xmm0,[rax]                               
0xbc5881b  pshufd xmm0,xmm0,0                            
0xbc58820  pxor xmm1,xmm1                                
0xbc58824  punpcklwd xmm0,xmm1                           
0xbc58828  cvtdq2ps xmm0,xmm0                            
0xbc5882b  movq xmm1,[rbp+0x1D0]                         
0xbc58833  movq xmm2,[rbp+0x1D8]                         
0xbc5883b  paddd xmm2,xmm1                               
0xbc5883f  punpcklqdq xmm1,xmm2                          
0xbc58843  cvtdq2ps xmm9,xmm1                            
0xbc58847  divps xmm9,xmm0                               

loc_bc5884b:  ; from bc5880e
0xbc5884b  mov rcx,[rbp+0x9E0]                           
0xbc58852  movzx eax,word ptr [rcx]                      
0xbc58855  movzx ecx,word ptr [rcx+2]                    
0xbc58859  movaps xmm0,[rbp+0x860]                       
0xbc58860  jmp short 0xBC58866                           ; -> loc_bc58866

loc_bc58862:  ; from bc587ae, bc587b7, bc587c0, bc587d0
0xbc58862  xorps xmm9,xmm9                               

loc_bc58866:  ; from bc587de, bc58860
0xbc58866  cmp qword ptr [rbp+0x9D8],0                   
0xbc5886e  je 0xBC57C63                                  ; -> sub_bc57c63
0xbc58874  test ax,ax                                    
0xbc58877  je 0xBC57C63                                  ; -> sub_bc57c63
0xbc5887d  test cx,cx                                    
0xbc58880  je 0xBC57C63                                  ; -> sub_bc57c63
0xbc58886  mov rax,[r15+0xD0]                            
0xbc5888d  test rax,rax                                  
0xbc58890  je 0xBC57C63                                  ; -> sub_bc57c63
0xbc58896  cmp dword ptr [rax+8],0                       
0xbc5889a  je 0xBC57C63                                  ; -> sub_bc57c63
0xbc588a0  lea r8,[r15+0xC8]                             
0xbc588a7  mov rcx,[rbp+0x9D8]                           
0xbc588ae  mov rax,[rcx]                                 
0xbc588b1  mov rax,[rax+0x30]                            
0xbc588b5  lea rdx,[rbp+0x1D0]                           
0xbc588bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc588c2  nop                                           
0xbc588c3  cmp byte ptr [rbp+0x1E0],1                    
0xbc588ca  jne 0xBC57C5C                                 ; -> sub_bc57c5c
0xbc588d0  movq xmm0,[rbp+0x1D0]                         
0xbc588d8  mov rax,[rbp+0x9E0]                           
0xbc588df  movd xmm1,[rax]                               
0xbc588e3  pshufd xmm1,xmm1,0                            
0xbc588e8  xorps xmm2,xmm2                               
0xbc588eb  punpcklwd xmm1,xmm2                           
0xbc588ef  cvtdq2ps xmm1,xmm1                            
0xbc588f2  movq xmm2,[rbp+0x1D8]                         
0xbc588fa  paddd xmm2,xmm0                               
0xbc588fe  punpcklqdq xmm0,xmm2                          
0xbc58902  cvtdq2ps xmm15,xmm0                           
0xbc58906  divps xmm15,xmm1                              
0xbc5890a  jmp 0xBC57C5C                                 ; -> sub_bc57c5c
0xbc5890f  cmp rbx,0xFFFFFFFFFFFFFFFF                    
0xbc58913  je 0xBC59CC3                                  ; -> loc_bc59cc3
0xbc58919  cmp qword ptr [rbp+0x870],0                   
0xbc58921  setne al                                      
0xbc58924  test rbx,rbx                                  
0xbc58927  sete cl                                       
0xbc5892a  or cl,al                                      
0xbc5892c  je 0xBC59CC3                                  ; -> loc_bc59cc3
0xbc58932  test rbx,rbx                                  
0xbc58935  sete al                                       
0xbc58938  cmp qword ptr [rbp+0x878],0                   
0xbc58940  setne cl                                      
0xbc58943  or cl,al                                      
0xbc58945  je 0xBC59CC3                                  ; -> loc_bc59cc3
0xbc5894b  cmp qword ptr [rbp+0x680],0                   
0xbc58953  setne al                                      
0xbc58956  cmp dword ptr [rbp+0x880],0                   
0xbc5895d  sete cl                                      
0xbc58960  or cl,al                                      
0xbc58962  je 0xBC59CC3                                  ; -> loc_bc59cc3
0xbc58968  mov [rbp],rbx                                 
0xbc5896c  mov rax,[rbp+0x8A8]                           
0xbc58973  mov [rbp+8],rax                               
0xbc58977  mov [rbp+0x10],rbx                            
0xbc5897b  mov [rbp+0x18],r12                            
0xbc5897f  mov rax,[rbp+0x688]                           
0xbc58986  mov [rbp+0x20],rax                            
0xbc5898a  mov rax,[rbp+0x690]                           
0xbc58991  mov [rbp+0x28],rax                            
0xbc58995  mov [rbp+0x30],rbx                            
0xbc58999  xorps xmm0,xmm0                               
0xbc5899c  movaps [rbp+0x7A0],xmm0                       
0xbc589a3  movaps [rbp+0x790],xmm0                       
0xbc589aa  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc589b1  mov rax,[rcx]                                 
0xbc589b4  mov rax,[rax+8]                               
0xbc589b8  mov edx,0x20                                  
0xbc589bd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc589c3  nop                                           
0xbc589c4  mov rdi,rax                                   
0xbc589c7  test rax,rax                                  
0xbc589ca  je 0xBC59CC9                                  ; -> loc_bc59cc9

loc_bc589d0:  ; from bc59cd4
0xbc589d0  mov [rbp+0x790],rdi                           
0xbc589d7  mov qword ptr [rbp+0x7A0],0x14                
0xbc589e2  mov qword ptr [rbp+0x7A8],0x1F                
0xbc589ed  movups xmm0,[0xF5C5F05]                       ; [data_f5c5f05] "LightClusteringPhase"
0xbc589f4  movups [rdi],xmm0                             
0xbc589f7  mov dword ptr [rdi+0x10],0x65736168           
0xbc589fe  mov byte ptr [rdi+0x14],0                     
0xbc58a02  mov qword ptr [rbp+0x400],0xF                 
0xbc58a0d  mov qword ptr [rbp+0x408],0                   
0xbc58a18  mov qword ptr [rbp+0x3F8],0xF                 
0xbc58a23  mov rax,0x756C43746867694C                    
0xbc58a2d  mov [rbp+0x3E8],rax                           
0xbc58a34  mov rax,0x676E697265747375                    
0xbc58a3e  mov [rbp+0x3EF],rax                           
0xbc58a45  mov byte ptr [rbp+0x3F7],0                    
0xbc58a4c  mov rax,0xED116949152B2ABD                    
0xbc58a56  mov [rbp+0x3E0],rax                           
0xbc58a5d  xorps xmm0,xmm0                               
0xbc58a60  movaps [rbp-0x30],xmm0                        
0xbc58a64  mov rax,[rbp+0x7A0]                           
0xbc58a6b  cmp qword ptr [rbp+0x7A8],0x10                
0xbc58a73  jb short 0xBC58A7E                            ; -> loc_bc58a7e
0xbc58a75  mov rcx,[rbp+0x790]                           
0xbc58a7c  jmp short 0xBC58A85                           ; -> loc_bc58a85

loc_bc58a7e:  ; from bc58a73
0xbc58a7e  lea rcx,[rbp+0x790]                           

loc_bc58a85:  ; from bc58a7c
0xbc58a85  lea rsi,[rbp+0x98]                            
0xbc58a8c  mov [rbp+0x1B0],rcx                           
0xbc58a93  mov [rbp+0x1B8],rax                           
0xbc58a9a  lea rcx,[rbp+0x6C0]                           
0xbc58aa1  lea rdx,[rbp+0x1B0]                           
0xbc58aa8  call 0x568AD40                                ; -> sub_568ad40
0xbc58aad  nop                                           
0xbc58aae  movups xmm0,[rbp+0x6C0]                       
0xbc58ab5  movups xmm1,[rbp+0x6D0]                       
0xbc58abc  movaps [rbp+0x1E0],xmm1                       
0xbc58ac3  movaps [rbp+0x1D0],xmm0                       
0xbc58aca  mov qword ptr [rbp+0x6D0],0                   
0xbc58ad5  mov qword ptr [rbp+0x6D8],0xF                 
0xbc58ae0  mov byte ptr [rbp+0x6C0],0                    
0xbc58ae7  movaps xmm0,[rbp]                             
0xbc58aeb  movaps xmm1,[rbp+0x10]                        
0xbc58aef  movaps xmm2,[rbp+0x20]                        
0xbc58af3  movaps [rbp+0x1F0],xmm0                       
0xbc58afa  movaps [rbp+0x200],xmm1                       
0xbc58b01  movaps [rbp+0x210],xmm2                       
0xbc58b08  mov rax,[rbp+0x30]                            
0xbc58b0c  mov [rbp+0x220],rax                           
0xbc58b13  movups xmm0,[rbp+0x38]                        
0xbc58b17  movups [rbp+0x228],xmm0                       
0xbc58b1e  xorps xmm0,xmm0                               
0xbc58b21  lea rax,[rbp+0x38]                            
0xbc58b25  movups [rax],xmm0                             
0xbc58b28  mov rax,[rbp+0x48]                            
0xbc58b2c  mov [rbp+0x238],rax                           
0xbc58b33  movaps xmm1,[rbp+0x50]                        
0xbc58b37  movaps [rbp+0x240],xmm1                       
0xbc58b3e  movsd xmm1,[rbp+0x60]                         
0xbc58b43  movsd [rbp+0x250],xmm1                        
0xbc58b4b  lea rax,[rbp+0x68]                            
0xbc58b4f  movups xmm1,[rax]                             
0xbc58b52  movups xmm2,[rax+0x10]                        
0xbc58b56  movups xmm3,[rax+0x20]                        
0xbc58b5a  movups [rbp+0x258],xmm1                       
0xbc58b61  movups [rbp+0x268],xmm2                       
0xbc58b68  movups [rbp+0x278],xmm3                       
0xbc58b6f  mov rax,[rsi+0x10]                            
0xbc58b73  mov [rbp+0x298],rax                           
0xbc58b7a  movups xmm1,[rsi]                             
0xbc58b7d  movups [rbp+0x288],xmm1                       
0xbc58b84  movaps xmm1,[rbp+0xB0]                        
0xbc58b8b  movaps [rbp+0x2A0],xmm1                       
0xbc58b92  movaps xmm1,[rbp+0xC0]                        
0xbc58b99  movaps [rbp+0x2B0],xmm1                       
0xbc58ba0  movaps xmm1,[rbp+0xD0]                        
0xbc58ba7  movaps [rbp+0x2C0],xmm1                       
0xbc58bae  movaps xmm1,[rbp+0xE0]                        
0xbc58bb5  movaps [rbp+0x2D0],xmm1                       
0xbc58bbc  movaps xmm1,[rbp+0xF0]                        
0xbc58bc3  movaps [rbp+0x2E0],xmm1                       
0xbc58bca  movaps xmm1,[rbp+0x100]                       
0xbc58bd1  movaps [rbp+0x2F0],xmm1                       
0xbc58bd8  movaps xmm1,[rbp+0x110]                       
0xbc58bdf  movaps [rbp+0x300],xmm1                       
0xbc58be6  movaps xmm1,[rbp+0x120]                       
0xbc58bed  movaps [rbp+0x310],xmm1                       
0xbc58bf4  movaps xmm1,[rbp+0x130]                       
0xbc58bfb  movaps [rbp+0x320],xmm1                       
0xbc58c02  movaps xmm1,[rbp+0x140]                       
0xbc58c09  movaps [rbp+0x330],xmm1                       
0xbc58c10  movaps xmm1,[rbp+0x150]                       
0xbc58c17  movaps [rbp+0x340],xmm1                       
0xbc58c1e  movsd xmm1,[rbp+0x160]                        
0xbc58c26  movsd [rbp+0x350],xmm1                        
0xbc58c2e  movss xmm1,[rbp+0x168]                        
0xbc58c36  movss [rbp+0x358],xmm1                        
0xbc58c3e  mov eax,[rbp+0x17C]                           
0xbc58c44  mov [rbp+0x36C],eax                           
0xbc58c4a  movups xmm1,[rbp+0x16C]                       
0xbc58c51  movups [rbp+0x35C],xmm1                       
0xbc58c58  mov byte ptr [rbp+0x388],0                    
0xbc58c5f  cmp byte ptr [rbp+0x198],1                    
0xbc58c66  movaps xmm7,[rbp+0x780]                       
0xbc58c6d  jne short 0xBC58CA4                           ; -> loc_bc58ca4
0xbc58c6f  mov rax,[rbp+0x190]                           
0xbc58c76  mov qword ptr [rbp+0x190],0                   
0xbc58c81  movaps xmm1,[rbp+0x180]                       
0xbc58c88  movaps [rbp+0x180],xmm0                       
0xbc58c8f  movaps [rbp+0x370],xmm1                       
0xbc58c96  mov [rbp+0x380],rax                           
0xbc58c9d  mov byte ptr [rbp+0x388],1                    

loc_bc58ca4:  ; from bc58c6d
0xbc58ca4  mov eax,[rbp+0x1A8]                           
0xbc58caa  mov [rbp+0x398],eax                           
0xbc58cb0  mov rax,[rbp+0x1A0]                           
0xbc58cb7  mov [rbp+0x390],rax                           
0xbc58cbe  mov qword ptr [rbp+0x3D8],0                   
0xbc58cc9  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc58cd0  mov rax,[rcx]                                 
0xbc58cd3  mov rax,[rax+8]                               
0xbc58cd7  mov edx,0x130                                 
0xbc58cdc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58ce2  nop                                           
0xbc58ce3  mov rdi,rax                                   
0xbc58ce6  test rax,rax                                  
0xbc58ce9  je 0xBC59CD9                                  ; -> loc_bc59cd9

loc_bc58cef:  ; from bc59ce4
0xbc58cef  lea rax,[0xF4412D0]                           ; [data_f4412d0]
0xbc58cf6  mov [rdi],rax                                 
0xbc58cf9  mov dword ptr [rdi+8],0x3F800000              
0xbc58d00  xorps xmm0,xmm0                               
0xbc58d03  movups [rdi+0xC],xmm0                         
0xbc58d07  mov dword ptr [rdi+0x1C],0x3F800000           
0xbc58d0e  movups [rdi+0x20],xmm0                        
```

**Chunk 3 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| r8b | 1 | W | flag combination |
| dl | 1 | W | flag combination |
| r15+0x30 | 8 | R | rdx src |
| rdx+8 | 4 | R | dword check |
| r15+0x28 | 8 | W | r8 dest |
| rbp+0x9D8 | 8 | R | rcx src |
| [rcx] | 8 | R | rax src |
| [rax+0x30] | 8 | R | rax src |
| rbp+0x1D0 | 8 | W | rdx dest (string ptr) |
| rbp+0x1E0 | 1 | R | byte check |
| rbp+0x9E0 | 8 | R | rax src |
| [rax] | 4 | R | movd xmm0 |
| rbp+0x1D0 | 8 | R | movq xmm1 |
| rbp+0x1D8 | 8 | R | movq xmm2 |
| rbp+0x860 | 16 | R | movaps xmm0 |
| r15+0x50 | 8 | R | rdx src |
| r15+0x48 | 8 | W | r8 dest |
| r15+0x70 | 8 | R | rdx src |
| r15+0x68 | 8 | W | r8 dest |
| r15+0x90 | 8 | R | rdx src |
| r15+0x88 | 8 | W | r8 dest |
| r15+0xB0 | 8 | R | rdx src |
| r15+0xA8 | 8 | W | r8 dest |
| r15+0xD0 | 8 | R | rax src |
| r15+0xC8 | 8 | W | r8 dest |
| rbp+0x870 | 8 | R | qword check |
| rbp+0x878 | 8 | R | qword check |
| rbp+0x680 | 8 | R | qword check |
| rbp+0x880 | 4 | R | dword check |
| rbp | 8 | W | rbx |
| rbp+8 | 8 | W | rax |
| rbp+0x10 | 8 | W | rbx |
| rbp+0x18 | 8 | W | r12 |
| rbp+0x20 | 8 | W | rax |
| rbp+0x28 | 8 | W | rax |
| rbp+0x30 | 8 | W | rbx |
| rbp+0x7A0 | 16 | W | xorps |
| rbp+0x790 | 16 | W | xorps |
| rbp+0x400 | 8 | W | 0xF |
| rbp+0x408 | 8 | W | 0 |
| rbp+0x3F8 | 8 | W | 0xF |
| rbp+0x3E8 | 8 | W | constant |
| rbp+0x3EF | 8 | W | constant |
| rbp+0x3F7 | 1 | W | 0 |
| rbp+0x3E0 | 8 | W | constant |
| rbp-0x30 | 16 | W | xorps |
| rbp+0x7A0 | 8 | R | rax |
| rbp+0x7A8 | 8 | R | qword cmp |
| rbp+0x790 | 8 | R/W | rcx/mov |
| rbp+0x98 | 8 | W | lea rsi |
| rbp+0x1B0 | 8 | W | rcx |
| rbp+0x1B8 | 8 | W | rax |
| rbp+0x6C0 | 8 | W | lea rcx |
| rbp+0x1B0 | 8 | R | lea rdx |
| rbp+0x6C0 | 16 | R | movups xmm0 |
| rbp+0x6D0 | 16 | R | movups xmm1 |
| rbp+0x1E0 | 16 | W | movaps xmm1 |
| rbp+0x1D0 | 16 | W | movaps xmm0 |
| rbp+0x6D0 | 8 | W | 0 |
| rbp+0x6D8 | 8 | W | 0xF |
| rbp+0x6C0 | 1 | W | 0 |
| rbp | 16 | R | movaps xmm0 |
| rbp+0x10 | 16 | R | movaps xmm1 |
| rbp+0x20 | 16 | R | movaps xmm2 |
| rbp+0x1F0 | 16 | W | movaps xmm0 |
| rbp+0x200 | 16 | W | movaps xmm1 |
| rbp+0x210 | 16 | W | movaps xmm2 |
| rbp+0x30 | 8 | R | mov rax |
| rbp+0x220 | 8 | W | mov rax |
| rbp+0x38 | 16 | R | movups xmm0 |
| rbp+0x228 | 16 | W | movups xmm0 |
| rbp+0x38 | 16 | W | movups xmm0 (zero) |
| rbp+0x48 | 8 | R | mov rax |
| rbp+0x238 | 8 | W | mov rax |
| rbp+0x50 | 16 | R | movaps xmm1 |
| rbp+0x240 | 16 | W | movaps xmm1 |
| rbp+0x60 | 8 | R | movsd xmm1 |
| rbp+0x250 | 8 | W | movsd xmm1 |
| rbp+0x68 | 16 | R | movups xmm1 |
| rbp+0x78 | 16 | R | movups xmm2 |
| rbp+0x88 | 16 | R | movups xmm3 |
| rbp+0x258 | 16 | W | movups xmm1 |
| rbp+0x268 | 16 | W | movups xmm2 |
| rbp+0x278 | 16 | W | movups xmm3 |
| rsi+0x10 | 8 | R | mov rax |
| rbp+0x298 | 8 | W | mov rax |
| rsi | 16 | R | movups xmm1 |
| rbp+0x288 | 16 | W | movups xmm1 |
| rbp+0xB0 | 16 | R | movaps xmm1 |
| rbp+0x2A0 | 16 | W | movaps xmm1 |
| rbp+0xC0 | 16 | R | movaps xmm1 |
| rbp+0x2B0 | 16 | W | movaps xmm1 |
| rbp+0xD0 | 16 | R | movaps xmm1 |
| rbp+0x2C0 | 16 | W | movaps xmm1 |
| rbp+0xE0 | 16 | R | movaps xmm1 |
| rbp+0x2D0 | 16 | W | movaps xmm1 |
| rbp+0xF0 | 16 | R | movaps xmm1 |
| rbp+0x2E0 | 16 | W | movaps xmm1 |
| rbp+0x100 | 16 | R | movaps xmm1 |
| rbp+0x2F0 | 16 | W | movaps xmm1 |
| rbp+0x110 | 16 | R | movaps xmm1 |
| rbp+0x300 | 16 | W | movaps xmm1 |
| rbp+0x120 | 16 | R | movaps xmm1 |
| rbp+0x310 | 16 | W | movaps xmm1 |
| rbp+0x130 | 16 | R | movaps xmm1 |
| rbp+0x320 | 16 | W | movaps xmm1 |
| rbp+0x140 | 16 | R | movaps xmm1 |
| rbp+0x330 | 16 | W | movaps xmm1 |
| rbp+0x150 | 16 | R | movaps xmm1 |
| rbp+0x340 | 16 | W | movaps xmm1 |
| rbp+0x160 | 8 | R | movsd xmm1 |
| rbp+0x350 | 8 | W | movsd xmm1 |
| rbp+0x168 | 4 | R | movss xmm1 |
| rbp+0x358 | 4 | W | movss xmm1 |
| rbp+0x17C | 4 | R | mov eax |
| rbp+0x36C | 4 | W | mov eax |
| rbp+0x16C | 16 | R | movups xmm1 |
| rbp+0x35C | 16 | W | movups xmm1 |
| rbp+0x388 | 1 | W | 0/1 flag |
| rbp+0x780 | 16 | R | movaps xmm7 |
| rbp+0x198 | 1 | R | byte check |
| rbp+0x190 | 8 | R/W | rax/qword |
| rbp+0x180 | 16 | R/W | movaps xmm1/xmm0 |
| rbp+0x370 | 16 | W | movaps xmm1 |
| rbp+0x380 | 8 | W | mov rax |
| rbp+0x1A8 | 4 | R | mov eax |
| rbp+0x398 | 4 | W | mov eax |
| rbp+0x1A0 | 8 | R | mov rax |
| rbp+0x390 | 8 | W | mov rax |
| rbp+0x3D8 | 8 | W | 0 |
| rdi | 8 | W | mov rax/dword |
| rdi+8 | 4 | W | 0x3F800000 |
| rdi+0xC | 16 | W | movups xmm0 |
| rdi+0x1C | 4 | W | 0x3F800000 |
| rdi+0x20 | 16 | W | movups xmm0 |

**Chunk 3 callees (in order):**
1. qword ptr [0xF99FFA0] = sub_eea6040 - called 5 times (deallocator)
2. 0x568AD40 (sub_568ad40) - called once
3. qword ptr [0xF99FFA0] = sub_eea6040 - called again (allocator for LightClusteringPhase)

### Chunk 4: 0xbc58d0e..0xbc59675 (continuation - from actual rdis output)
```
0xbc58d0e  movups [rdi+0x20],xmm0                        
0xbc58d12  mov dword ptr [rdi+0x30],0x3F800000           
0xbc58d19  movups [rdi+0x34],xmm0                        
0xbc58d1d  movsd xmm1,[0xEFD3400]                        ; [data_efd3400]
0xbc58d25  movsd [rdi+0x44],xmm1                         
0xbc58d2a  movups [rdi+0x4C],xmm0                        
0xbc58d2e  mov dword ptr [rdi+0x5C],0x3F800000           
0xbc58d35  movups [rdi+0x60],xmm0                        
0xbc58d39  mov dword ptr [rdi+0x70],0x3F800000           
0xbc58d40  movups [rdi+0x74],xmm0                        
0xbc58d44  mov dword ptr [rdi+0x84],0x3F800000           
0xbc58d4e  movups [rdi+0x88],xmm0                        
0xbc58d55  mov rax,0x3F80000000000001                    
0xbc58d5f  mov [rdi+0x98],rax                            
0xbc58d66  movups [rdi+0xA0],xmm0                        
0xbc58d6d  mov dword ptr [rdi+0xB0],0x3F800000           
0xbc58d77  movups [rdi+0xB4],xmm0                        
0xbc58d7e  mov dword ptr [rdi+0xC4],0x3F800000           
0xbc58d88  movups [rdi+0xC8],xmm0                        
0xbc58d8f  movsd [rdi+0xD8],xmm1                         
0xbc58d97  movups [rdi+0xE0],xmm0                        
0xbc58d9e  mov dword ptr [rdi+0xF0],0x3F800000           
0xbc58da8  movups [rdi+0xF4],xmm0                        
0xbc58daf  mov dword ptr [rdi+0x104],0x3F800000          
0xbc58db9  movups [rdi+0x108],xmm0                       
0xbc58dc0  mov dword ptr [rdi+0x118],0x3F800000          
0xbc58dca  movaps xmm0,[rbp-0x30]                        
0xbc58dce  movups [rdi+0x11C],xmm0                       
0xbc58dd5  cmp qword ptr [rbp+0x3D8],0                   
0xbc58ddd  jne 0xBC59CC3                                 ; -> loc_bc59cc3
0xbc58de3  mov [rbp+0x3D8],rdi                           
0xbc58dea  lea rcx,[rbp+0x830]                           
0xbc58df1  lea rdx,[rbp+0x790]                           
0xbc58df8  call 0x76A8A0                                 ; -> sub_76a8a0
0xbc58dfd  nop                                           
0xbc58dfe  lea rax,[rbp+0x1F0]                           
0xbc58e05  mov rcx,[rbp+0x830]                           
0xbc58e0c  mov rdx,[rbp+0x838]                           
0xbc58e13  mov r8,[rbp+0x850]                            
0xbc58e1a  mov qword ptr [rbp+0x850],0xF                 
0xbc58e25  mov byte ptr [rbp+0x838],0                    
0xbc58e2c  mov qword ptr [rbp+0x810],0                   
0xbc58e37  mov [rbp+0x7F0],rdx                           
0xbc58e3e  mov [rbp+0x7E8],rcx                           
0xbc58e45  mov qword ptr [rbp+0x800],0                   
0xbc58e50  mov qword ptr [rbp+0x808],0xF                 
0xbc58e5b  mov byte ptr [rbp+0x7F0],0                    
0xbc58e62  mov r9,[rbp+0x770]                            
0xbc58e69  mov [rbp+0x720],r9                            
0xbc58e70  mov r9,[rbp+0x778]                            
0xbc58e77  mov [rbp+0x728],r9                            
0xbc58e7e  mov r9,[rbp+0x698]                            
0xbc58e85  mov [rbp+0x730],r9                            
0xbc58e8c  mov r9,[rbp+0x6A0]                            
0xbc58e93  mov [rbp+0x738],r9                            
0xbc58e9a  mov r9,[rbp+0x760]                            
0xbc58ea1  mov [rbp+0x740],r9                            
0xbc58ea8  mov r9,[rbp+0x768]                            
0xbc58eaf  mov [rbp+0x748],r9                            
0xbc58eb6  mov qword ptr [rbp+0x718],0                   
0xbc58ec1  mov [rbp+0x6F8],rdx                           
0xbc58ec8  movups xmm0,[rbp+0x840]                       
0xbc58ecf  mov rdx,[rbp+0x840]                           
0xbc58ed6  mov qword ptr [rbp+0x848],0                   
0xbc58ee1  mov [rbp+0x7F8],rdx                           
0xbc58ee8  movups [rbp+0x700],xmm0                       
0xbc58eef  mov [rbp+0x710],r8                            
0xbc58efd  movaps xmm0,[rbp+0x1D0]                       
0xbc58f04  movaps xmm1,[rbp+0x1E0]                       
0xbc58f0b  movaps [rbp+0x420],xmm1                       
0xbc58f12  movaps [rbp+0x410],xmm0                       
0xbc58f19  mov qword ptr [rbp+0x1E0],0                   
0xbc58f24  mov qword ptr [rbp+0x1E8],0xF                 
0xbc58f2f  mov byte ptr [rbp+0x1D0],0                    
0xbc58f36  mov rcx,[rax+0x30]                            
0xbc58f3a  mov [rbp+0x460],rcx                           
0xbc58f41  movups xmm0,[rax]                             
0xbc58f44  movups xmm1,[rax+0x10]                        
0xbc58f48  movups xmm2,[rax+0x20]                        
0xbc58f4c  movaps [rbp+0x450],xmm2                       
0xbc58f53  movaps [rbp+0x440],xmm1                       
0xbc58f5a  movaps [rbp+0x430],xmm0                       
0xbc58f61  movups xmm0,[rbp+0x228]                       
0xbc58f68  movups [rbp+0x468],xmm0                       
0xbc58f6f  xorps xmm0,xmm0                               
0xbc58f72  movups [rax+0x38],xmm0                        
0xbc58f76  mov rcx,[rbp+0x238]                           
0xbc58f7d  mov [rbp+0x478],rcx                           
0xbc58f84  movaps xmm1,[rbp+0x240]                       
0xbc58f8b  movaps [rbp+0x480],xmm1                       
0xbc58f92  movsd xmm1,[rbp+0x250]                        
0xbc58f9a  movsd [rbp+0x490],xmm1                        
0xbc58fa2  movups xmm1,[rax+0x68]                        
0xbc58fa6  movups xmm2,[rax+0x78]                        
0xbc58faa  movups xmm3,[rax+0x88]                        
0xbc58fb1  movups [rbp+0x498],xmm1                       
0xbc58fb8  movups [rbp+0x4A8],xmm2                       
0xbc58fbf  movups [rbp+0x4B8],xmm3                       
0xbc58fc6  mov rcx,[rax+0xA8]                            
0xbc58fcd  mov [rbp+0x4D8],rcx                           
0xbc58fd4  movups xmm1,[rax+0x98]                        
0xbc58fdb  movups [rbp+0x4C8],xmm1                       
0xbc58fe2  movaps xmm1,[rbp+0x2A0]                       
0xbc58fe9  movaps [rbp+0x4E0],xmm1                       
0xbc58ff0  movaps xmm1,[rbp+0x2B0]                       
0xbc58ff7  movaps [rbp+0x4F0],xmm1                       
0xbc58ffe  movaps xmm1,[rbp+0x2C0]                       
0xbc59005  movaps [rbp+0x500],xmm1                       
0xbc5900c  movaps xmm1,[rbp+0x2D0]                       
0xbc59013  movaps [rbp+0x510],xmm1                       
0xbc5901a  movaps xmm1,[rbp+0x2E0]                       
0xbc59021  movaps [rbp+0x520],xmm1                       
0xbc59028  movaps xmm1,[rbp+0x2F0]                       
0xbc5902f  movaps [rbp+0x530],xmm1                       
0xbc59036  movaps xmm1,[rbp+0x300]                       
0xbc5903d  movaps [rbp+0x540],xmm1                       
0xbc59044  movaps xmm1,[rbp+0x310]                       
0xbc5904b  movaps [rbp+0x550],xmm1                       
0xbc59052  movaps xmm1,[rbp+0x320]                       
0xbc59059  movaps [rbp+0x560],xmm1                       
0xbc59060  movaps xmm1,[rbp+0x330]                       
0xbc59067  movaps [rbp+0x570],xmm1                       
0xbc5906e  movaps xmm1,[rbp+0x340]                       
0xbc59075  movaps [rbp+0x580],xmm1                       
0xbc5907c  movsd xmm1,[rbp+0x350]                        
0xbc59084  movsd [rbp+0x590],xmm1                        
0xbc5908c  movss xmm1,[rbp+0x358]                        
0xbc59094  movss [rbp+0x598],xmm1                        
0xbc5909c  mov ecx,[rax+0x17C]                           
0xbc590a2  mov [rbp+0x5AC],ecx                           
0xbc590a8  movups xmm1,[rax+0x16C]                       
0xbc590af  movups [rbp+0x59C],xmm1                       
0xbc590b6  mov byte ptr [rbp+0x5C8],0                    
0xbc590bd  cmp byte ptr [rbp+0x388],1                    
0xbc590c4  jne short 0xBC590FB                           ; -> loc_bc590fb
0xbc590c6  mov rcx,[rbp+0x380]                           
0xbc590cd  mov qword ptr [rbp+0x380],0                   
0xbc590d8  movaps xmm1,[rbp+0x370]                       
0xbc590df  movaps [rbp+0x370],xmm0                       
0xbc590e6  movaps [rbp+0x5B0],xmm1                       
0xbc590ed  mov [rbp+0x5C0],rcx                           
0xbc590f4  mov byte ptr [rbp+0x5C8],1                    

loc_bc590fb:  ; from bc590c4
0xbc590fb  lea rsi,[rbp+0x720]                           
0xbc59102  mov ecx,[rax+0x1A8]                           
0xbc59108  mov [rbp+0x5D8],ecx                           
0xbc5910e  mov rax,[rax+0x1A0]                           
0xbc59115  mov [rbp+0x5D0],rax                           
0xbc5911c  lea rbx,[rbp+0x5E0]                           
0xbc59123  mov qword ptr [rbp+0x618],0                   
0xbc5912e  mov rcx,[rbp+0x3D8]                           
0xbc59135  test rcx,rcx                                  
0xbc59138  je short 0xBC59190                            ; -> loc_bc59190
0xbc5913a  lea rdi,[rbp+0x3A0]                           
0xbc59141  cmp rcx,rdi                                   
0xbc59144  je short 0xBC5914F                            ; -> loc_bc5914f
0xbc59146  mov [rbp+0x618],rcx                           
0xbc5914d  jmp short 0xBC59185                           ; -> loc_bc59185

loc_bc5914f:  ; from bc59144
0xbc5914f  mov rax,[rcx]                                 
0xbc59152  mov rax,[rax+8]                               
0xbc59156  mov rdx,rbx                                   
0xbc59159  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5915f  mov [rbp+0x618],rax                           
0xbc59166  mov rcx,[rbp+0x3D8]                           
0xbc5916d  test rcx,rcx                                  
0xbc59170  je short 0xBC59190                            ; -> loc_bc59190
0xbc59172  cmp rcx,rdi                                   
0xbc59175  setne dl                                      
0xbc59178  mov rax,[rcx]                                 
0xbc5917b  mov rax,[rax+0x20]                            
0xbc5917f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc59185:  ; from bc5914d
0xbc59185  mov qword ptr [rbp+0x3D8],0                   

loc_bc59190:  ; from bc59138, bc59170
0xbc59190  mov qword ptr [rbp+0x648],0                   
0xbc5919b  movups xmm0,[rsi-0x28]                        
0xbc5919f  movups xmm1,[rsi-0x18]                        
0xbc591a3  movups [rbp+0x628],xmm0                       
0xbc591aa  movups [rbp+0x638],xmm1                       
0xbc591b1  mov qword ptr [rbp+0x708],0                   
0xbc591bc  mov qword ptr [rbp+0x710],0xF                 
0xbc591c7  mov byte ptr [rbp+0x6F8],0                    
0xbc591ce  mov rax,[rbp+0x6F0]                           
0xbc591d5  mov [rbp+0x620],rax                           
0xbc591dc  movups xmm0,[rsi]                             
0xbc591df  movaps [rbp+0x650],xmm0                       
0xbc591e6  movups xmm0,[rsi+0x10]                        
0xbc591ea  movaps [rbp+0x660],xmm0                       
0xbc591f1  movups xmm0,[rsi+0x20]                        
0xbc591f5  movaps [rbp+0x670],xmm0                       
0xbc591fc  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc59203  mov rax,[rcx]                                 
0xbc59206  mov rax,[rax+8]                               
0xbc5920a  mov edx,0x258                                 
0xbc5920f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc59215  nop                                           
0xbc59216  mov r15,rax                                   
0xbc59219  test rax,rax                                  
0xbc5921c  je 0xBC59CE9                                  ; -> loc_bc59ce9

loc_bc59222:  ; from bc59cf4
0xbc59222  lea r14,[rbp+0x430]                           
0xbc59229  mov rax,0x100000001                           
0xbc59233  mov [r15+8],rax                               
0xbc59237  lea rax,[0xF098020]                           ; [data_f098020]
0xbc5923e  mov [r15],rax                                 
0xbc59241  mov r12,[rbp+0x428]                           
0xbc59248  mov rsi,[rbp+0x410]                           
0xbc5924f  mov rdi,[rbp+0x420]                           
0xbc59256  xorps xmm6,xmm6                               
0xbc59259  movups [r15+0x28],xmm6                        
0xbc5925e  movups [r15+0x18],xmm6                        
0xbc59263  mov qword ptr [r15+0x38],0xF                  
0xbc5926b  mov qword ptr [r15+0x40],0                    
0xbc59273  lea rax,[0xF4412B0]                           ; [data_f4412b0]
0xbc5927a  mov [r15+0x10],rax                            
0xbc5927e  lea r13,[r15+0x48]                            
0xbc59282  mov qword ptr [r15+0x80],0                    
0xbc5928d  mov rcx,[rbp+0x618]                           
0xbc59294  test rcx,rcx                                  
0xbc59297  je short 0xBC592E8                            ; -> loc_bc592e8
0xbc59299  cmp rcx,rbx                                   
0xbc5929c  je short 0xBC592A7                            ; -> loc_bc592a7
0xbc5929e  mov [r15+0x80],rcx                            
0xbc592a5  jmp short 0xBC592DD                           ; -> loc_bc592dd

loc_bc592a7:  ; from bc5929c
0xbc592a7  mov rax,[rcx]                                 
0xbc592aa  mov rax,[rax+8]                               
0xbc592ae  mov rdx,r13                                   
0xbc592b1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc592b7  mov [r15+0x80],rax                            
0xbc592be  mov rcx,[rbp+0x618]                           
0xbc592c5  test rcx,rcx                                  
0xbc592c8  je short 0xBC592E8                            ; -> loc_bc592e8
0xbc592ca  cmp rcx,rbx                                   
0xbc592cd  setne dl                                      
0xbc592d0  mov rax,[rcx]                                 
0xbc592d3  mov rax,[rax+0x20]                            
0xbc592d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc592dd:  ; from bc592a5
0xbc592dd  mov qword ptr [rbp+0x618],0                   

loc_bc592e8:  ; from bc59297, bc592c8
0xbc592e8  lea rax,[rbp+0x5D0]                           
0xbc592ef  mov rcx,[r14+0x30]                            
0xbc592f3  mov [r15+0xB8],rcx                            
0xbc592fe  movups xmm0,[r14]                             
0xbc592fe  movups xmm1,[r14+0x10]                        
0xbc59303  movups xmm2,[r14+0x20]                        
0xbc59308  movups [r15+0xA8],xmm2                        
0xbc59310  movups [r15+0x98],xmm1                        
0xbc59318  movups [r15+0x88],xmm0                        
0xbc59320  movups xmm0,[rbp+0x468]                       
0xbc59327  movups [r15+0xC0],xmm0                        
0xbc5932f  movups [r14+0x38],xmm6                        
0xbc59334  mov rcx,[rbp+0x478]                           
0xbc5933b  mov [r15+0xD0],rcx                            
0xbc59342  movaps xmm0,[rbp+0x480]                       
0xbc59349  movups [r15+0xD8],xmm0                        
0xbc59351  movsd xmm0,[rbp+0x490]                        
0xbc59359  movsd [r15+0xE8],xmm0                         
0xbc59362  movups xmm0,[r14+0x68]                        
0xbc59367  movups xmm1,[r14+0x78]                        
0xbc5936c  movups xmm2,[r14+0x88]                        
0xbc59374  movups [r15+0x110],xmm2                       
0xbc5937c  movups [r15+0x100],xmm1                       
0xbc59384  movups [r15+0xF0],xmm0                        
0xbc5938c  movups xmm0,[r14+0x98]                        
0xbc59394  movups [r15+0x120],xmm0                       
0xbc5939c  mov rcx,[r14+0xA8]                            
0xbc593a3  mov [r15+0x130],rcx                           
0xbc593aa  movaps xmm0,[rbp+0x4E0]                       
0xbc593b1  movups [r15+0x138],xmm0                       
0xbc593b9  movaps xmm0,[rbp+0x4F0]                       
0xbc593c0  movups [r15+0x148],xmm0                       
0xbc593c8  movaps xmm0,[rbp+0x500]                       
0xbc593cf  movups [r15+0x158],xmm0                       
0xbc593d7  movaps xmm0,[rbp+0x510]                       
0xbc593de  movups [r15+0x168],xmm0                       
0xbc593e6  movaps xmm0,[rbp+0x520]                       
0xbc593ed  movups [r15+0x178],xmm0                       
0xbc593f5  movaps xmm0,[rbp+0x530]                       
0xbc593fc  movups [r15+0x188],xmm0                       
0xbc59404  movaps xmm0,[rbp+0x540]                       
0xbc5940b  movups [r15+0x198],xmm0                       
0xbc59413  movaps xmm0,[rbp+0x550]                       
0xbc5941a  movups [r15+0x1A8],xmm0                       
0xbc59422  movaps xmm0,[rbp+0x560]                       
0xbc59429  movups [r15+0x1B8],xmm0                       
0xbc59431  movaps xmm0,[rbp+0x570]                       
0xbc59438  movups [r15+0x1C8],xmm0                       
0xbc59440  movaps xmm0,[rbp+0x580]                       
0xbc59447  movups [r15+0x1D8],xmm0                       
0xbc5944f  movsd xmm0,[rbp+0x590]                        
0xbc59457  movsd [r15+0x1E8],xmm0                        
0xbc59460  movss xmm0,[rbp+0x598]                        
0xbc59468  movss [r15+0x1F0],xmm0                        
0xbc59471  movups xmm0,[r14+0x16C]                       
0xbc59479  movups [r15+0x1F4],xmm0                       
0xbc59481  mov ecx,[r14+0x17C]                           
0xbc59488  mov [r15+0x204],ecx                           
0xbc5948f  mov byte ptr [r15+0x220],0                    
0xbc59497  cmp byte ptr [rbp+0x5C8],1                    
0xbc5949e  jne short 0xBC594DA                           ; -> loc_bc594da
0xbc594a0  mov rcx,[rbp+0x5C0]                           
0xbc594a7  mov qword ptr [rbp+0x5C0],0                   
0xbc594b2  movaps xmm0,[rbp+0x5B0]                       
0xbc594b9  xorps xmm1,xmm1                               
0xbc594bc  movaps [rbp+0x5B0],xmm1                       
0xbc594c3  movups [r15+0x208],xmm0                       
0xbc594cb  mov [r15+0x218],rcx                           
0xbc594d2  mov byte ptr [r15+0x220],1                    

loc_bc594da:  ; from bc5949e
0xbc594da  mov [rbp+0x878],r13                           
0xbc594e1  lea rdx,[r15+0x10]                            
0xbc594e5  lea r8,[r15+0x88]                             
0xbc594ec  mov ecx,[rax+8]                               
0xbc594ef  mov [r15+0x230],ecx                           
0xbc594f6  mov rax,[rax]                                 
0xbc594f9  mov [r15+0x228],rax                           
0xbc59500  xorps xmm0,xmm0                               
0xbc59503  movups [r15+0x238],xmm0                       
0xbc5950b  movups [r15+0x248],xmm0                       
0xbc59513  test rdi,rdi                                  
0xbc59516  mov [rbp+0x8A8],r15                           
0xbc5951d  mov [rbp+0x870],rdx                           
0xbc59524  js 0xBC59F80                                  ; -> loc_bc59f80
0xbc5952a  lea rbx,[r15+0x238]                           
0xbc59531  mov r13d,0xF                                  
0xbc59537  cmp rdi,0x10                                  
0xbc5953b  jb short 0xBC595BB                            ; -> loc_bc595bb
0xbc5953d  mov [rbp+0x880],r8                            
0xbc59544  mov rdx,rdi                                   
0xbc59547  or rdx,0xF                                    
0xbc5954b  cmp rdx,0x17                                  
0xbc5954f  mov r13d,0x16                                 
0xbc59555  cmovae r13,rdx                                
0xbc59559  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc59560  mov rax,[rcx]                                 
0xbc59563  mov rax,[rax+8]                               
0xbc59567  cmp rdx,0xFFF                                 
0xbc5956e  jb short 0xBC5959B                            ; -> loc_bc5959b
0xbc59570  lea r15,[r13+0x28]                            
0xbc59574  mov rdx,r15                                   
0xbc59577  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5957d  nop                                           
0xbc5957e  mov r14,rax                                   
0xbc59581  test rax,rax                                  
0xbc59584  je 0xBC59CF9                                  ; -> loc_bc59cf9

loc_bc5958a:  ; from bc59d02
0xbc5958a  mov rax,r14                                   
0xbc5958d  add r14,0x27                                  
0xbc59591  and r14,0xFFFFFFFFFFFFFFE0                    
0xbc59595  mov [r14-8],rax                               
0xbc59599  jmp short 0xBC595B5                           ; -> loc_bc595b5

loc_bc5959b:  ; from bc5956e
0xbc5959b  lea r15,[r13+1]                               
0xbc5959f  mov rdx,r15                                   
0xbc595a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc595a8  nop                                           
0xbc595a9  mov r14,rax                                   
0xbc595ac  test rax,rax                                  
0xbc595af  je 0xBC59D07                                  ; -> loc_bc59d07

loc_bc595b5:  ; from bc59599, bc59d13
0xbc595b5  mov [rbx],r14                                 
0xbc595b8  mov rbx,r14                                   

loc_bc595bb:  ; from bc5953b
0xbc595bb  cmp r12,0x10                                  
0xbc595bf  lea rdx,[rbp+0x410]                           
0xbc595c6  cmovae rdx,rsi                                
0xbc595ca  mov r14,[rbp+0x8A8]                           
0xbc595d1  mov [r14+0x248],rdi                           
0xbc595d8  mov [r14+0x250],r13                           
0xbc595df  mov rcx,rbx                                   
0xbc595e2  mov r8,rdi                                    
0xbc595e5  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbc595ea  mov byte ptr [rbx+rdi],0                      
0xbc595ee  mov rcx,[rbp+0x8A0]                           
0xbc595f5  mov rsi,[rcx+0x10]                            
0xbc595f9  cmp rsi,[rcx+0x18]                            
0xbc595fd  je short 0xBC5961E                            ; -> loc_bc5961e
0xbc595ff  mov rax,[rbp+0x870]                           
0xbc59606  mov [rsi],rax                                 
0xbc59609  mov [rsi+8],r14                               
0xbc5960d  mov rax,[rcx+0x10]                            
0xbc59611  add rax,0x10                                  
0xbc59615  mov [rcx+0x10],rax                            
0xbc59619  jmp 0xBC59828                                 ; -> loc_bc59828

loc_bc5961e:  ; from bc595fd
0xbc5961e  lea rdi,[rcx+8]                               
0xbc59622  mov r9,r14                                    
0xbc59625  add r9,0xC                                    
0xbc59629  mov r8,r14                                    
0xbc5962c  mov r13,rsi                                   
0xbc5962f  sub r13,[rdi]                                 
0xbc59632  mov rax,r13                                   
0xbc59635  sar rax,4                                     
0xbc59639  lea rbx,[rax+1]                               
0xbc5963d  mov r14,rax                                   
0xbc59640  shr r14,1                                     
0xbc59643  mov rcx,0xFFFFFFFFFFFFFFF                     
0xbc5964d  mov rdx,rcx                                   
0xbc59650  sub rdx,r14                                   
0xbc59653  add r14,rax                                   
0xbc59656  cmp r14,rbx                                   
0xbc59659  cmovbe r14,rbx                                
0xbc5965d  cmp rax,rdx                                   
0xbc59660  cmova r14,rcx                                 
0xbc59664  lea rcx,[r8+8]                                
0xbc59668  mov rax,r14                                   
0xbc5966b  shr rax,0x3C                                  
0xbc5966f  jne 0xBC59F8D                                 ; -> loc_bc59f8d
0xbc59675  test r14,r14                                  
0xbc59678  je 0xBC59711                                  ; -> loc_bc59711
```

**Chunk 4 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| rdi+0x20..0x11C | 16/4/8 | W | struct initialization (zero + 0x3F800000 pattern) |
| rdi+0x98 | 8 | W | 0x3F80000000000001 |
| rbp-0x30 | 16 | R | xmm0 src |
| rbp+0x3D8 | 8 | R/W | cmp/jne/mov |
| rbp+0x830 | 8 | W | lea rcx |
| rbp+0x790 | 8 | W | lea rdx |
| rbp+0x850 | 8 | W | 0xF |
| rbp+0x838 | 1 | W | 0 |
| rbp+0x810 | 8 | W | 0 |
| rbp+0x7F0 | 8 | W | rdx |
| rbp+0x7E8 | 8 | W | rcx |
| rbp+0x800 | 8 | W | 0 |
| rbp+0x808 | 8 | W | 0xF |
| rbp+0x7F0 | 1 | W | 0 |
| rbp+0x770/0x778/0x698/0x6A0/0x760/0x768 | 8 | R | r9 src |
| rbp+0x720/0x728/0x730/0x738/0x740/0x748 | 8 | W | r9 dst |
| rbp+0x718 | 8 | W | 0 |
| rbp+0x6F8 | 8 | W | rdx |
| rbp+0x840 | 16 | R | movups xmm0 |
| rbp+0x840 | 8 | R | mov rdx |
| rbp+0x848 | 8 | W | 0 |
| rbp+0x7F8 | 8 | W | rdx |
| rbp+0x700 | 16 | W | movups xmm0 |
| rbp+0x710 | 8 | W | r8 |
| rbp+0x6F0 | 8 | W | rcx |
| rbp+0x1D0 | 16 | R | movaps xmm0 |
| rbp+0x1E0 | 16 | R | movaps xmm1 |
| rbp+0x420 | 16 | W | movaps xmm1 |
| rbp+0x410 | 16 | W | movaps xmm0 |
| rbp+0x1E0 | 8 | W | 0 |
| rbp+0x1E8 | 8 | W | 0xF |
| rbp+0x1D0 | 1 | W | 0 |
| rax+0x30 | 8 | R | mov rcx |
| rbp+0x460 | 8 | W | mov rcx |
| rax | 16 | R | movups xmm0 |
| rax+0x10 | 16 | R | movups xmm1 |
| rax+0x20 | 16 | R | movups xmm2 |
| rbp+0x450 | 16 | W | movaps xmm2 |
| rbp+0x440 | 16 | W | movaps xmm1 |
| rbp+0x430 | 16 | W | movaps xmm0 |
| rbp+0x228 | 16 | R | movups xmm0 |
| rbp+0x468 | 16 | W | movups xmm0 |
| rax+0x38 | 16 | W | movups xmm0 (zero) |
| rbp+0x238 | 8 | R | mov rcx |
| rbp+0x478 | 8 | W | mov rcx |
| rbp+0x240 | 16 | R | movaps xmm1 |
| rbp+0x480 | 16 | W | movaps xmm1 |
| rbp+0x250 | 8 | R | movsd xmm1 |
| rbp+0x490 | 8 | W | movsd xmm1 |
| rax+0x68 | 16 | R | movups xmm1 |
| rax+0x78 | 16 | R | movups xmm2 |
| rax+0x88 | 16 | R | movups xmm3 |
| rbp+0x498 | 16 | W | movups xmm1 |
| rbp+0x4A8 | 16 | W | movups xmm2 |
| rbp+0x4B8 | 16 | W | movups xmm3 |
| rax+0xA8 | 8 | R | mov rcx |
| rbp+0x4D8 | 8 | W | mov rcx |
| rax+0x98 | 16 | R | movups xmm1 |
| rbp+0x4C8 | 16 | W | movups xmm1 |
| rbp+0x2A0..0x340 | 16 | R | movaps xmm1 (loop) |
| rbp+0x4E0..0x540 | 16 | W | movaps xmm1 (loop) |
| rbp+0x350 | 8 | R | movsd xmm1 |
| rbp+0x590 | 8 | W | movsd xmm1 |
| rbp+0x358 | 4 | R | movss xmm1 |
| rbp+0x598 | 4 | W | movss xmm1 |
| rax+0x17C | 4 | R | mov ecx |
| rbp+0x5AC | 4 | W | mov ecx |
| rax+0x16C | 16 | R | movups xmm1 |
| rbp+0x59C | 16 | W | movups xmm1 |
| rbp+0x5C8 | 1 | W | 0 |
| rbp+0x388 | 1 | R | cmp byte |
| rbp+0x380 | 8 | R/W | mov rcx/mov qword |
| rbp+0x370 | 16 | R/W | movaps xmm1/movaps xmm0 |
| rbp+0x5B0 | 16 | W | movaps xmm1 |
| rbp+0x5C0 | 8 | W | mov rcx |
| rbp+0x5C8 | 1 | W | 1 |
| rbp+0x720 | 8 | W | lea rsi |
| rax+0x1A8 | 4 | R | mov ecx |
| rbp+0x5D8 | 4 | W | mov ecx |
| rax+0x1A0 | 8 | R | mov rax |
| rbp+0x5D0 | 8 | W | mov rax |
| rbp+0x5E0 | 8 | W | lea rbx |
| rbp+0x618 | 8 | W | 0/rcx/rax |
| rbp+0x3D8 | 8 | R/W | test/cmp/mov |
| rbp+0x3A0 | 8 | W | lea rdi |
| [rcx] | 8 | R | mov rax |
| [rax+8] | 8 | R | mov rax |
| rdx | 8 | W | rdx=rbx |
| [rcx] | 8 | R | mov rax |
| [rax+0x20] | 8 | R | mov rax |
| rbp+0x648 | 8 | W | 0 |
| rsi-0x28 | 16 | R | movups xmm0 |
| rsi-0x18 | 16 | R | movups xmm1 |
| rbp+0x628 | 16 | W | movups xmm0 |
| rbp+0x638 | 16 | W | movups xmm1 |
| rbp+0x708 | 8 | W | 0 |
| rbp+0x710 | 8 | W | 0xF |
| rbp+0x6F8 | 1 | W | 0 |
| rbp+0x6F0 | 8 | R | mov rax |
| rbp+0x620 | 8 | W | mov rax |
| rsi | 16 | R | movups xmm0 |
| rbp+0x650 | 16 | W | movaps xmm0 |
| rsi+0x10 | 16 | R | movups xmm0 |
| rbp+0x660 | 16 | W | movaps xmm0 |
| rsi+0x20 | 16 | R | movups xmm0 |
| rbp+0x670 | 16 | W | movaps xmm0 |
| rbp+0x428 | 8 | R | mov r12 |
| rbp+0x410 | 8 | R | mov rsi |
| rbp+0x420 | 8 | R | mov rdi |
| r15+8 | 8 | W | mov rax |
| r15 | 8 | W | mov rax |
| r15+0x28 | 16 | W | movups xmm6 |
| r15+0x18 | 16 | W | movups xmm6 |
| r15+0x38 | 8 | W | 0xF |
| r15+0x40 | 8 | W | 0 |
| r15+0x10 | 8 | W | mov rax |
| r15+0x48 | 8 | W | lea r13 |
| r15+0x80 | 8 | W | 0/rcx/rax |
| rbp+0x618 | 8 | R | mov rcx |
| r13 | 8 | W | mov rdx |
| r14+0x30 | 8 | R | mov rcx |
| rbp+0x5D0 | 8 | W | lea rax |
| r14 | 16 | R | movups xmm0/xmm1/xmm2 |
| r15+0xA8 | 16 | W | movups xmm2 |
| r15+0x98 | 16 | W | movups xmm1 |
| r15+0x88 | 16 | W | movups xmm0 |
| rbp+0x468 | 16 | R | movups xmm0 |
| r15+0xC0 | 16 | W | movups xmm0 |
| r14+0x38 | 16 | W | movups xmm6 |
| rbp+0x478 | 8 | R | mov rcx |
| r15+0xD0 | 8 | W | mov rcx |
| rbp+0x480 | 16 | R | movaps xmm0 |
| r15+0xD8 | 16 | W | movups xmm0 |
| rbp+0x490 | 8 | R | movsd xmm0 |
| r15+0xE8 | 8 | W | movsd xmm0 |
| r14+0x68 | 16 | R | movups xmm0 |
| r14+0x78 | 16 | R | movups xmm1 |
| r14+0x88 | 16 | R | movups xmm2 |
| r15+0x110 | 16 | W | movups xmm2 |
| r15+0x100 | 16 | W | movups xmm1 |
| r15+0xF0 | 16 | W | movups xmm0 |
| r14+0x98 | 16 | R | movups xmm0 |
| r15+0x120 | 16 | W | movups xmm0 |
| r14+0xA8 | 8 | R | mov rcx |
| r15+0x130 | 8 | W | mov rcx |
| rbp+0x4E0 | 16 | R | movaps xmm0 |
| r15+0x138 | 16 | W | movups xmm0 |
| rbp+0x4F0 | 16 | R | movaps xmm0 |
| r15+0x148 | 16 | W | movups xmm0 |
| rbp+0x500 | 16 | R | movaps xmm0 |
| r15+0x158 | 16 | W | movups xmm0 |
| rbp+0x510 | 16 | R | movaps xmm0 |
| r15+0x168 | 16 | W | movups xmm0 |
| rbp+0x520 | 16 | R | movaps xmm0 |
| r15+0x178 | 16 | W | movups xmm0 |
| rbp+0x530 | 16 | R | movaps xmm0 |
| r15+0x188 | 16 | W | movups xmm0 |
| rbp+0x540 | 16 | R | movaps xmm0 |
| r15+0x198 | 16 | W | movups xmm0 |
| rbp+0x550 | 16 | R | movaps xmm0 |
| r15+0x1A8 | 16 | W | movups xmm0 |
| rbp+0x560 | 16 | R | movaps xmm0 |
| r15+0x1B8 | 16 | W | movups xmm0 |
| rbp+0x570 | 16 | R | movaps xmm0 |
| r15+0x1C8 | 16 | W | movups xmm0 |
| rbp+0x580 | 16 | R | movaps xmm0 |
| r15+0x1D8 | 16 | W | movups xmm0 |
| rbp+0x590 | 8 | R | movsd xmm0 |
| r15+0x1E8 | 8 | W | movsd xmm0 |
| rbp+0x598 | 4 | R | movss xmm0 |
| r15+0x1F0 | 4 | W | movss xmm0 |
| r14+0x16C | 16 | R | movups xmm0 |
| r15+0x1F4 | 16 | W | movups xmm0 |
| r14+0x17C | 4 | R | mov ecx |
| r15+0x204 | 4 | W | mov ecx |
| r15+0x220 | 1 | W | 0/1 |
| rbp+0x5C8 | 1 | R | cmp byte |
| rbp+0x5C0 | 8 | R/W | mov rcx/mov qword |
| rbp+0x5B0 | 16 | R/W | movaps xmm0/xorps/movaps |
| r15+0x208 | 16 | W | movups xmm0 |
| r15+0x218 | 8 | W | mov rcx |
| r15+0x220 | 1 | W | 1 |
| rbp+0x878 | 8 | W | mov r13 |
| r15+0x10 | 8 | W | lea rdx |
| r15+0x88 | 8 | W | lea r8 |
| rax+8 | 4 | R | mov ecx |
| r15+0x230 | 4 | W | mov ecx |
| rax | 8 | R | mov rax |
| r15+0x228 | 8 | W | mov rax |
| r15+0x238 | 16 | W | movups xmm0 |
| r15+0x248 | 16 | W | movups xmm0 |
| rdi | 8 | R | test |
| rbp+0x8A8 | 8 | W | mov r15 |
| rbp+0x870 | 8 | W | mov rdx |
| rbp+0x880 | 8 | W | mov r8 |
| r13 | 4 | W | 0xF |
| rdi | 4 | R | cmp 0x10 |
| rdx | 8 | R | mov rdx |
| rdx | 8 | R | or 0xF |
| rdx | 4 | R | cmp 0x17 |
| r13 | 4 | W | 0x16 |
| r13 | 8 | W | cmovae |
| rcx | 8 | R | mov rcx (data_1233e1a8) |
| [rcx] | 8 | R | mov rax |
| [rax+8] | 8 | R | mov rax |
| rdx | 4 | R | cmp 0xFFF |
| r15 | 8 | W | lea r15 |
| rdx | 8 | W | mov rdx |
| [0xF99FFA0] | 8 | W | call (alloc) |
| r14 | 8 | W | mov rax |
| r14 | 8 | R | test |
| rax | 8 | W | mov rax |
| r14 | 8 | R/W | add/and/mov |
| r13 | 8 | W | lea r15 |
| rdx | 8 | W | mov rdx |
| [0xF99FFA0] | 8 | W | call (alloc) |
| r14 | 8 | W | mov rax |
| r14 | 8 | R | test |
| rbx | 8 | W | mov r14 |
| rbx | 8 | W | mov rbx |
| r12 | 4 | R | cmp 0x10 |
| rbp+0x410 | 8 | R/W | lea rdx/cmovae rdx,rsi |
| rbp+0x8A8 | 8 | R | mov r14 |
| r14+0x248 | 8 | W | mov rdi |
| r14+0x250 | 8 | W | mov r13 |
| rbx | 8 | W | mov rcx |
| rdi | 8 | W | mov r8 |
| [0xEEC6EC0] | 8 | W | call |
| rbx+rdi | 1 | W | 0 |
| rbp+0x8A0 | 8 | R | mov rcx |
| [rcx+0x10] | 8 | R | mov rsi |
| [rcx+0x18] | 8 | R | cmp rsi |
| rbp+0x870 | 8 | R | mov rax |
| rsi | 8 | W | mov rax |
| rsi+8 | 8 | W | mov r14 |
| [rcx+0x10] | 8 | R | mov rax |
| rax | 8 | R | add 0x10 |
| [rcx+0x10] | 8 | W | mov rax |
| rcx+8 | 8 | W | lea rdi |
| r14 | 8 | W | mov r9 |
| r9 | 8 | W | add 0xC |
| r14 | 8 | W | mov r8 |
| rsi | 8 | W | mov r13 |
| r13 | 8 | R | sub [rdi] |
| rax | 8 | W | mov rax |
| rax | 8 | R | sar 4 |
| rbx | 8 | W | lea rbx |
| rax | 8 | W | mov r14 |
| r14 | 8 | R | shr 1 |
| rcx | 8 | W | 0xFFFFFFFFFFFFFFF |
| rdx | 8 | W | mov rdx |
| rdx | 8 | R | sub r14 |
| r14 | 8 | R/W | add rax/cmp/cmovbe |
| rax | 8 | R | cmp rdx/cmovna |
| r14 | 8 | R | test |
| r8+8 | 8 | W | lea rcx |
| rax | 8 | W | mov rax |
| rax | 8 | R | shr 0x3C |
| r14 | 8 | R | test/je |

**Chunk 4 callees (in order):**
1. 0x76A8A0 (sub_76a8a0) - called once
2. qword ptr [0xF99FFA0] = sub_eea6040 - called multiple times (allocator/deallocator)
3. 0xEEC6EC0 (sub_eec6ec0) - called once

### Chunk 5: 0xbc59675..0xbc59d31 (continuation - from actual rdis output)
```
0xbc59675  test r14,r14                                  
0xbc59678  je 0xBC59711                                  ; -> loc_bc59711
0xbc5967e  mov r12,r14                                   
0xbc59681  shl r12,4                                     
0xbc59685  cmp r14,0x100                                 
0xbc5968c  mov [rbp+0x880],r9                            
0xbc59693  mov [rbp+0x878],rcx                           
0xbc5969a  jb short 0xBC596E8                            ; -> loc_bc596e8
0xbc5969c  mov rax,0xFFFFFFFFFFFFFFE                     
0xbc596a6  cmp r14,rax                                   
0xbc596a9  jae 0xBC5A288                                 ; -> loc_bc5a288
0xbc596af  add r12,0x27                                  
0xbc596b3  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc596ba  mov rax,[rcx]                                 
0xbc596bd  mov rax,[rax+8]                               
0xbc596c1  mov rdx,r12                                   
0xbc596c4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc596ca  nop                                           
0xbc596cb  mov r15,rax                                   
0xbc596ce  test rax,rax                                  
0xbc596d1  je 0xBC59D18                                  ; -> loc_bc59d18

loc_bc596d7:  ; from bc59d21
0xbc596d7  mov rax,r15                                   
0xbc596da  add r15,0x27                                  
0xbc596de  and r15,0xFFFFFFFFFFFFFFE0                    
0xbc596e2  mov [r15-8],rax                               
0xbc596e6  jmp short 0xBC59714                           ; -> loc_bc59714

loc_bc596e8:  ; from bc5969a
0xbc596e8  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc596ef  mov rax,[rcx]                                 
0xbc596f2  mov rax,[rax+8]                               
0xbc596f6  mov rdx,r12                                   
0xbc596f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc596ff  nop                                           
0xbc59700  mov r15,rax                                   
0xbc59703  test rax,rax                                  
0xbc59706  jne short 0xBC59714                           ; -> loc_bc59714
0xbc59708  mov rcx,r12                                   
0xbc5970b  call 0x9BC830                                 ; -> sub_9bc830
0xbc59710  nop                                           

loc_bc59711:  ; from bc59678
0xbc59711  xor r15d,r15d                                 

loc_bc59714:  ; from bc596e6, bc59706
0xbc59714  mov rax,[rbp+0x870]                           
0xbc5971b  mov [r15+r13],rax                             
0xbc5971f  mov rax,[rbp+0x8A8]                           
0xbc59726  mov [r15+r13+8],rax                           
0xbc5972b  mov rcx,[rbp+0x8A0]                           
0xbc59732  mov rax,[rcx+8]                               
0xbc59736  mov rcx,[rcx+0x10]                            
0xbc5973a  cmp rsi,rcx                                   
0xbc5973d  je 0xBC597CD                                  ; -> loc_bc597cd
0xbc59743  cmp rax,rsi                                   
0xbc59746  je short 0xBC59787                            ; -> loc_bc59787
0xbc59748  xor ecx,ecx                                   
0xbc5974a  xorps xmm0,xmm0                               
0xbc5974d  nop [rax]                                     

loc_bc59750:  ; from bc5977a
0xbc59750  movups [r15+rcx],xmm0                         
0xbc59755  mov rdx,[rax+rcx]                             
0xbc59759  mov [r15+rcx],rdx                             
0xbc5975d  mov rdx,[rax+rcx+8]                           
0xbc59762  mov [r15+rcx+8],rdx                           
0xbc59767  movups [rax+rcx],xmm0                         
0xbc5976b  lea rdx,[rax+rcx]                             
0xbc5976f  add rdx,0x10                                  
0xbc59773  add rcx,0x10                                  
0xbc59777  cmp rdx,rsi                                   
0xbc5977a  jne short 0xBC59750                           ; -> loc_bc59750
0xbc5977c  mov rax,[rbp+0x8A0]                           
0xbc59783  mov rcx,[rax+0x10]                            

loc_bc59787:  ; from bc59746
0xbc59787  cmp rsi,rcx                                   
0xbc5978a  je 0xBC5980C                                  ; -> loc_bc5980c
0xbc59790  lea rax,[r15+r13]                             
0xbc59794  add rax,0x10                                  
0xbc59798  xor edx,edx                                   
0xbc5979a  xorps xmm0,xmm0                               
0xbc5979d  nop [rax]                                     

loc_bc597a0:  ; from bc597c9
0xbc597a0  movups [rax+rdx],xmm0                         
0xbc597a4  mov r8,[rsi+rdx]                              
0xbc597a8  mov [rax+rdx],r8                              
0xbc597ac  mov r8,[rsi+rdx+8]                            
0xbc597b1  mov [rax+rdx+8],r8                            
0xbc597b6  movups [rsi+rdx],xmm0                         
0xbc597ba  lea r8,[rsi+rdx]                              
0xbc597be  add r8,0x10                                   
0xbc597c2  add rdx,0x10                                  
0xbc597c6  cmp r8,rcx                                    
0xbc597c9  jne short 0xBC597A0                           ; -> loc_bc597a0
0xbc597cb  jmp short 0xBC5980C                           ; -> loc_bc5980c

loc_bc597cd:  ; from bc5973d
0xbc597cd  cmp rax,rsi                                   
0xbc597d0  je short 0xBC5980C                            ; -> loc_bc5980c
0xbc597d2  xor ecx,ecx                                   
0xbc597d4  xorps xmm0,xmm0                               
0xbc597d7  nop [rax+rax]                                 

loc_bc597e0:  ; from bc5980a
0xbc597e0  movups [r15+rcx],xmm0                         
0xbc597e5  mov rdx,[rax+rcx]                             
0xbc597e9  mov [r15+rcx],rdx                             
0xbc597ed  mov rdx,[rax+rcx+8]                           
0xbc597f2  mov [r15+rcx+8],rdx                           
0xbc597f7  movups [rax+rcx],xmm0                         
0xbc597fb  lea rdx,[rax+rcx]                             
0xbc597ff  add rdx,0x10                                  
0xbc59803  add rcx,0x10                                  
0xbc59807  cmp rdx,rsi                                   
0xbc5980a  jne short 0xBC597E0                           ; -> loc_bc597e0

loc_bc5980c:  ; from bc5978a, bc597cb, bc597d0
0xbc5980c  mov rcx,rdi                                   
0xbc5980f  mov rdx,r15                                   
0xbc59812  mov r8,rbx                                    
0xbc59815  mov r9,r14                                    
0xbc59818  call 0x130EE0                                 ; -> sub_130ee0
0xbc5981d  mov rcx,[rbp+0x8A0]                           
0xbc59824  mov rax,[rcx+0x10]                            
0xbc59828  lea rdx,[rbp+0x670]                           
0xbc5982f  mov byte ptr [rcx+0x60],1                     
0xbc59833  mov rax,[rax-0x10]                            
0xbc59837  mov [rcx+0x58],rax                            
0xbc5983b  call 0x56939C0                                ; -> sub_56939c0
0xbc59840  nop                                           
0xbc59841  mov r14,[rbp+0x6A8]                           
0xbc59848  lea rdx,[rbp+0x660]                           
0xbc5984f  mov rcx,[rbp+0x8A0]                           
0xbc59856  call 0x56939C0                                ; -> sub_56939c0
0xbc5985b  nop                                           
0xbc5985c  lea rdx,[rbp+0x650]                           
0xbc59863  mov rcx,[rbp+0x8A0]                           
0xbc5986a  call 0x56939C0                                ; -> sub_56939c0
0xbc5986f  nop                                           
0xbc59870  lea rax,[rbp+0x620]                           
0xbc59877  mov rcx,[rbp+0x8A0]                           
0xbc5987e  mov rsi,[rcx+0x58]                            
0xbc59882  lea rcx,[rsi+8]                               
0xbc59886  cmp rcx,rax                                   
0xbc59889  je short 0xBC598E7                            ; -> loc_bc598e7
0xbc5988b  mov rdi,[rbp+0x638]                           
0xbc59892  cmp qword ptr [rbp+0x640],0x10                
0xbc5989a  jb short 0xBC598A5                            ; -> loc_bc598a5
0xbc5989c  mov r9,[rbp+0x628]                            
0xbc598a3  jmp short 0xBC598AC                           ; -> loc_bc598ac

loc_bc598a5:  ; from bc5989a
0xbc598a5  lea r9,[rbp+0x628]                            

loc_bc598ac:  ; from bc598a3
0xbc598ac  lea rbx,[rsi+0x10]                            
0xbc598b0  mov rax,[rsi+0x28]                            
0xbc598b4  cmp rdi,rax                                   
0xbc598b7  jbe short 0xBC598C7                           ; -> loc_bc598c7
0xbc598b9  mov rcx,rbx                                   
0xbc598bc  mov rdx,rdi                                   
0xbc598bf  call 0x9D6D0                                  ; -> sub_9d6d0
0xbc598c4  nop                                           
0xbc598c5  jmp short 0xBC598E7                           ; -> loc_bc598e7

loc_bc598c7:  ; from bc598b7
0xbc598c7  cmp rax,0x10                                  
0xbc598cb  jb short 0xBC598D1                            ; -> loc_bc598d1
0xbc598cd  mov rbx,[rsi+0x10]                            

loc_bc598d1:  ; from bc598cb
0xbc598d1  mov [rsi+0x20],rdi                            
0xbc598d5  mov rcx,rbx                                   
0xbc598d8  mov rdx,r9                                    
0xbc598db  mov r8,rdi                                    
0xbc598de  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbc598e3  mov byte ptr [rbx+rdi],0                      

loc_bc598e7:  ; from bc59889, bc598c5
0xbc598e7  mov rax,[rbp+0x620]                           
0xbc598ee  mov [rsi+8],rax                               
0xbc598f2  mov qword ptr [rsi+0x30],0                    
0xbc598fa  mov rax,[rbp+0x8A0]                           
0xbc59901  mov qword ptr [rax+0x58],0                    
0xbc59909  mov rax,[rbp+0x640]                           
0xbc59910  cmp rax,0x10                                  
0xbc59914  mov rsi,[rbp+0x9F8]                           
0xbc5991b  jb short 0xBC59955                            ; -> loc_bc59955
0xbc5991d  mov rcx,[rbp+0x628]                           
0xbc59924  lea rdx,[rax+1]                               
0xbc59928  cmp rdx,0x1000                                
0xbc5992f  jb short 0xBC59950                            ; -> loc_bc59950
0xbc59931  mov r8,[rcx-8]                                
0xbc59935  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc59939  sub rcx,r8                                    
0xbc5993c  cmp rcx,0x20                                  
0xbc59940  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc59946  add rax,0x28                                  
0xbc5994a  mov rdx,rax                                   
0xbc5994d  mov rcx,r8                                    

loc_bc59950:  ; from bc5992f
0xbc59950  call 0xE935700                                ; -> sub_e935700

loc_bc59955:  ; from bc5991b
0xbc59955  mov qword ptr [rbp+0x638],0                   
0xbc59960  mov qword ptr [rbp+0x640],0xF                 
0xbc5996b  mov byte ptr [rbp+0x628],0                    
0xbc59972  lea rcx,[rbp+0x410]                           
0xbc59979  call 0xBC5B720                                ; -> sub_bc5b720
0xbc5997e  mov rax,[rbp+0x710]                           
0xbc59985  cmp rax,0x10                                  
0xbc59989  jb short 0xBC599C3                            ; -> loc_bc599c3
0xbc5998b  mov rcx,[rbp+0x6F8]                           
0xbc59992  lea rdx,[rax+1]                               
0xbc59996  cmp rdx,0x1000                                
0xbc5999d  jb short 0xBC599BE                            ; -> loc_bc599be
0xbc5999f  mov r8,[rcx-8]                                
0xbc599a3  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc599a7  sub rcx,r8                                    
0xbc599aa  cmp rcx,0x20                                  
0xbc599ae  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc599b4  add rax,0x28                                  
0xbc599b8  mov rdx,rax                                   
0xbc599bb  mov rcx,r8                                    

loc_bc599be:  ; from bc5999d
0xbc599be  call 0xE935700                                ; -> sub_e935700

loc_bc599c3:  ; from bc59989
0xbc599c3  mov rax,[rbp+0x808]                           
0xbc599ca  cmp rax,0x10                                  
0xbc599ce  jb short 0xBC59A08                            ; -> loc_bc59a08
0xbc599d0  mov rcx,[rbp+0x7F0]                           
0xbc599d7  lea rdx,[rax+1]                               
0xbc599db  cmp rdx,0x1000                                
0xbc599e2  jb short 0xBC59A03                            ; -> loc_bc59a03
0xbc599e4  mov r8,[rcx-8]                                
0xbc599e8  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc599ec  sub rcx,r8                                    
0xbc599ef  cmp rcx,0x20                                  
0xbc599f3  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc599f9  add rax,0x28                                  
0xbc599fd  mov rdx,rax                                   
0xbc59a00  mov rcx,r8                                    

loc_bc59a03:  ; from bc599e2
0xbc59a03  call 0xE935700                                ; -> sub_e935700

loc_bc59a08:  ; from bc599ce
0xbc59a08  mov rax,[rbp+0x850]                           
0xbc59a0f  cmp rax,0x10                                  
0xbc59a13  jb short 0xBC59A4D                            ; -> loc_bc59a4d
0xbc59a15  mov rcx,[rbp+0x838]                           
0xbc59a1c  lea rdx,[rax+1]                               
0xbc59a20  cmp rdx,0x1000                                
0xbc59a27  jb short 0xBC59A48                            ; -> loc_bc59a48
0xbc59a29  mov r8,[rcx-8]                                
0xbc59a2d  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc59a31  sub rcx,r8                                    
0xbc59a34  cmp rcx,0x20                                  
0xbc59a38  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc59a3e  add rax,0x28                                  
0xbc59a42  mov rdx,rax                                   
0xbc59a45  mov rcx,r8                                    

loc_bc59a48:  ; from bc59a27
0xbc59a48  call 0xE935700                                ; -> sub_e935700

loc_bc59a4d:  ; from bc59a13
0xbc59a4d  lea rcx,[rbp+0x1D0]                           
0xbc59a54  call 0xBC5B720                                ; -> sub_bc5b720
0xbc59a59  mov rax,[rbp+0x6D8]                           
0xbc59a60  cmp rax,0x10                                  
0xbc59a64  jb short 0xBC59A9E                            ; -> loc_bc59a9e
0xbc59a66  mov rcx,[rbp+0x6C0]                           
0xbc59a6d  lea rdx,[rax+1]                               
0xbc59a71  cmp rdx,0x1000                                
0xbc59a78  jb short 0xBC59A99                            ; -> loc_bc59a99
0xbc59a7a  mov r8,[rcx-8]                                
0xbc59a7e  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc59a82  sub rcx,r8                                    
0xbc59a85  cmp rcx,0x20                                  
0xbc59a89  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc59a8f  add rax,0x28                                  
0xbc59a93  mov rdx,rax                                   
0xbc59a96  mov rcx,r8                                    

loc_bc59a99:  ; from bc59a78
0xbc59a99  call 0xE935700                                ; -> sub_e935700

loc_bc59a9e:  ; from bc59a64
0xbc59a9e  mov rax,[rbp+0x400]                           
0xbc59aa5  cmp rax,0x10                                  
0xbc59aa9  jb short 0xBC59AE3                            ; -> loc_bc59ae3
0xbc59aab  mov rcx,[rbp+0x3E8]                           
0xbc59ab2  lea rdx,[rax+1]                               
0xbc59ab6  cmp rdx,0x1000                                
0xbc59abd  jb short 0xBC59ADE                            ; -> loc_bc59ade
0xbc59abf  mov r8,[rcx-8]                                
0xbc59ac3  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc59ac7  sub rcx,r8                                    
0xbc59aca  cmp rcx,0x20                                  
0xbc59ace  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc59ad4  add rax,0x28                                  
0xbc59ad8  mov rdx,rax                                   
0xbc59adb  mov rcx,r8                                    

loc_bc59ade:  ; from bc59abd
0xbc59ade  call 0xE935700                                ; -> sub_e935700

loc_bc59ae3:  ; from bc59aa9
0xbc59ae3  mov rax,[rbp+0x7A8]                           
0xbc59aea  cmp rax,0x10                                  
0xbc59aee  jb short 0xBC59B28                            ; -> loc_bc59b28
0xbc59af0  mov rcx,[rbp+0x790]                           
0xbc59af7  lea rdx,[rax+1]                               
0xbc59afb  cmp rdx,0x1000                                
0xbc59b02  jb short 0xBC59B23                            ; -> loc_bc59b23
0xbc59b04  mov r8,[rcx-8]                                
0xbc59b08  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc59b0c  sub rcx,r8                                    
0xbc59b0f  cmp rcx,0x20                                  
0xbc59b13  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc59b19  add rax,0x28                                  
0xbc59b1d  mov rdx,rax                                   
0xbc59b20  mov rcx,r8                                    

loc_bc59b23:  ; from bc59b02
0xbc59b23  call 0xE935700                                ; -> sub_e935700

loc_bc59b28:  ; from bc59aee
0xbc59b28  mov rax,[rbp+0x760]                           
0xbc59b2f  mov [r14],rax                                 
0xbc59b32  mov rax,[rbp+0x768]                           
0xbc59b39  mov [r14+8],rax                               
0xbc59b3d  mov rax,[rbp+0x770]                           
0xbc59b44  mov [r14+0x18],rax                            
0xbc59b48  mov rax,[rbp+0x778]                           
0xbc59b4f  mov [r14+0x20],rax                            
0xbc59b53  cvtsi2ss xmm0,dword ptr [rsi]                 
0xbc59b57  mov byte ptr [r14+0x10],1                     
0xbc59b5c  mov byte ptr [r14+0x28],1                     
0xbc59b61  movaps xmm1,[rbp+0x7C0]                       
0xbc59b68  movss [r14+0x30],xmm1                         
0xbc59b6e  movaps xmm1,[rbp+0x7D0]                       
0xbc59b75  movss [r14+0x34],xmm1                         
0xbc59b7b  movss xmm1,[rbp+0x894]                        
0xbc59b83  movss [r14+0x38],xmm1                         
0xbc59b89  movss [r14+0x3C],xmm0                         
0xbc59b8f  movss [r14+0x40],xmm7                         
0xbc59b95  cmp byte ptr [rbp+0x198],1                    
0xbc59b9c  jne short 0xBC59BF3                           ; -> loc_bc59bf3
0xbc59b9e  mov rcx,[rbp+0x180]                           
0xbc59ba5  test rcx,rcx                                  
0xbc59ba8  je short 0xBC59BF3                            ; -> loc_bc59bf3
0xbc59baa  mov rdx,[rbp+0x190]                           
0xbc59bb1  sub rdx,rcx                                   
0xbc59bb4  cmp rdx,0x1000                                
0xbc59bbb  jb short 0xBC59BD9                            ; -> loc_bc59bd9
0xbc59bbd  mov rax,[rcx-8]                               
0xbc59bc1  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc59bc5  sub rcx,rax                                   
0xbc59bc8  cmp rcx,0x20                                  
0xbc59bcc  jae 0xBC59D26                                 ; -> loc_bc59d26
0xbc59bd2  add rdx,0x27                                  
0xbc59bd6  mov rcx,rax                                   

loc_bc59bd9:  ; from bc59bbb
0xbc59bd9  lea rsi,[rbp+0x180]                           
0xbc59be0  call 0xE935700                                ; -> sub_e935700
0xbc59be5  xorps xmm0,xmm0                               
0xbc59be8  movups [rsi],xmm0                             
0xbc59beb  mov qword ptr [rsi+0x10],0                    

loc_bc59bf3:  ; from bc59b9c, bc59ba8
0xbc59bf3  mov rdi,[rbp+0x40]                            
0xbc59bf7  test rdi,rdi                                  
0xbc59bfa  je short 0xBC59C27                            ; -> loc_bc59c27
0xbc59bfc  lock dec dword ptr [rdi+8]                    
0xbc59c00  jne short 0xBC59C27                           ; -> loc_bc59c27
0xbc59c02  mov rax,[rdi]                                 
0xbc59c05  mov rax,[rax]                                 
0xbc59c08  mov rcx,rdi                                   
0xbc59c0b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc59c11  lock dec dword ptr [rdi+0xC]                  
0xbc59c15  jne short 0xBC59C27                           ; -> loc_bc59c27
0xbc59c17  mov rax,[rdi]                                 
0xbc59c1a  mov rax,[rax+8]                               
0xbc59c1e  mov rcx,rdi                                   
0xbc59c21  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc59c27:  ; from bc59bfa, bc59c00, bc59c15
0xbc59c27  mov rdi,[rbp+0x758]                           
0xbc59c2e  test rdi,rdi                                  
0xbc59c31  je short 0xBC59C5E                            ; -> loc_bc59c5e
0xbc59c33  lock dec dword ptr [rdi+8]                    
0xbc59c37  jne short 0xBC59C5E                           ; -> loc_bc59c5e
0xbc59c39  mov rax,[rdi]                                 
0xbc59c3c  mov rax,[rax]                                 
0xbc59c3f  mov rcx,rdi                                   
0xbc59c42  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc59c48  lock dec dword ptr [rdi+0xC]                  
0xbc59c4c  jne short 0xBC59C5E                           ; -> loc_bc59c5e
0xbc59c4e  mov rax,[rdi]                                 
0xbc59c51  mov rax,[rax+8]                               
0xbc59c55  mov rcx,rdi                                   
0xbc59c58  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc59c5e:  ; from bc59c31, bc59c37, bc59c4c
0xbc59c5e  mov rax,r14                                   
0xbc59c61  movaps xmm6,[rbp+0x8C0]                       
0xbc59c68  movaps xmm7,[rbp+0x8D0]                       
0xbc59c6f  movaps xmm8,[rbp+0x8E0]                       
0xbc59c77  movaps xmm9,[rbp+0x8F0]                       
0xbc59c7f  movaps xmm10,[rbp+0x900]                      
0xbc59c87  movaps xmm11,[rbp+0x910]                      
0xbc59c8f  movaps xmm12,[rbp+0x920]                      
0xbc59c97  movaps xmm13,[rbp+0x930]                      
0xbc59c9f  movaps xmm14,[rbp+0x940]                      
0xbc59ca7  movaps xmm15,[rbp+0x950]                      
0xbc59caf  add rsp,0x9E8                                 
0xbc59cb6  pop rbx                                       
0xbc59cb7  pop rdi                                       
0xbc59cb8  pop rsi                                       
0xbc59cb9  pop r12                                       
0xbc59cbb  pop r13                                       
0xbc59cbd  pop r14                                       
0xbc59cbf  pop r15                                       
0xbc59cc1  pop rbp                                       
0xbc59cc2  ret                                           
0xbc59cc3  call 0x78ED0                                  ; -> sub_78ed0
0xbc59cc8  nop                                           
0xbc59cc9  mov ecx,0x20                                  
0xbc59cce  call 0x9BC830                                 ; -> sub_9bc830
0xbc59cd3  nop                                           
0xbc59cd4  jmp 0xBC589D0                                 ; -> sub_bc589d0
0xbc59cd9  mov ecx,0x130                                 
0xbc59cde  call 0x9BC830                                 ; -> sub_9bc830
0xbc59ce3  nop                                           
0xbc59ce4  jmp 0xBC58CEF                                 ; -> sub_bc58cef
0xbc59ce9  mov ecx,0x258                                 
0xbc59cee  call 0x9BC830                                 ; -> sub_9bc830
0xbc59cf3  nop                                           
0xbc59cf4  jmp 0xBC59222                                 ; -> sub_bc59222
0xbc59cf9  mov rcx,r15                                   
0xbc59cfc  call 0x9BC830                                 ; -> sub_9bc830
0xbc59d01  nop                                           
0xbc59d02  jmp 0xBC5958A                                 ; -> sub_bc5958a
0xbc59d07  mov rcx,r15                                   
0xbc59d0a  call 0x9BC830                                 ; -> sub_9bc830
0xbc59d0f  nop                                           
0xbc59d10  xor r14d,r14d                                 
0xbc59d13  jmp 0xBC595B5                                 ; -> sub_bc595b5

loc_bc59d18:  ; from bc596d1
0xbc59d18  mov rcx,r12                                   
0xbc59d1b  call 0x9BC830                                 ; -> sub_9bc830
0xbc59d20  nop                                           
0xbc59d21  jmp 0xBC596D7                                 ; -> loc_bc596d7

loc_bc59d26:  ; from bc59940, bc599ae, bc599f3, bc59a38, bc59a89, bc59ace, ...
0xbc59d26  mov qword ptr [rsp+0x20],0                    
0xbc59d2f  xor ecx,ecx                                   
0xbc59d31  xor edx,edx                                   
```

**Chunk 5 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| r14 | 1 | R | test |
| r12 | 8 | W | mov r14 |
| r12 | 4 | W | shl 4 |
| r14 | 4 | R | cmp 0x100 |
| rbp+0x880 | 8 | W | mov r9 |
| rbp+0x878 | 8 | W | mov rcx |
| r12 | 4 | W | add 0x27 |
| r12 | 8 | R/W | mov rdx/call alloc |
| r15 | 8 | W | mov rax |
| rax | 1 | R | test |
| r15 | 8 | R/W | add/and/mov [r15-8] |
| rcx | 8 | R/W | mov r12/call 9bc830 |
| r15 | 4 | W | xor r15d |
| rbp+0x870 | 8 | R | mov rax |
| r15+r13 | 8 | W | mov rax (twice) |
| rbp+0x8A8 | 8 | R | mov rax |
| rbp+0x8A0 | 8 | R | mov rcx |
| [rcx+8] | 8 | R | mov rax |
| [rcx+0x10] | 8 | R | mov rcx |
| rsi | 8 | R | cmp rcx |
| rax | 8 | R | cmp rsi |
| rcx | 4 | W | xor ecx |
| xmm0 | 16 | W | xorps |
| r15+rcx | 16/8 | W | movups xmm0/mov rdx/mov rdx |
| rax+rcx | 8/16 | R/W | mov rdx/mov rdx/movups xmm0 |
| rdx | 8 | W | lea/add/cmp |
| rcx | 4 | W | add 0x10 |
| rbp+0x8A0 | 8 | R | mov rax |
| [rax+0x10] | 8 | R | mov rcx |
| rsi | 8 | R | cmp rcx/je |
| r15+r13 | 8 | W | lea/add |
| edx | 4 | W | xor |
| xmm0 | 16 | W | xorps |
| rax+rdx | 16/8 | W/R | movups xmm0/mov r8/mov |
| rsi+rdx | 8/16 | R/W | mov r8/mov r8/movups xmm0 |
| r8 | 8 | W | lea/add/cmp |
| rax | 8 | R | cmp rsi/je |
| ecx | 4 | W | xor |
| xmm0 | 16 | W | xorps |
| r15+rcx | 16/8 | W | movups xmm0/mov rdx/mov rdx |
| rax+rcx | 8/16 | R/W | mov rdx/mov rdx/movups xmm0 |
| rdx | 8 | W | lea/add/cmp |
| rcx | 4 | W | add 0x10 |
| rdi | 8 | W | mov rcx |
| r15 | 8 | W | mov rdx |
| rbx | 8 | W | mov r8 |
| r14 | 8 | W | mov r9 |
| 0x130EE0 | 8 | W | call sub_130ee0 |
| rbp+0x8A0 | 8 | R | mov rcx |
| [rcx+0x10] | 8 | R | mov rax |
| rbp+0x670 | 8 | W | lea rdx |
| rcx+0x60 | 1 | W | mov byte 1 |
| rax-0x10 | 8 | R | mov rax |
| rcx+0x58 | 8 | W | mov rax |
| 0x56939C0 | 8 | W | call sub_56939c0 (3x) |
| rbp+0x6A8 | 8 | R | mov r14 |
| rbp+0x660/0x650 | 8 | W | lea rdx |
| rbp+0x8A0 | 8 | R | mov rcx |
| rbp+0x620 | 8 | R | lea rax |
| rbp+0x8A0 | 8 | R | mov rcx |
| [rcx+0x58] | 8 | R | mov rsi |
| rsi+8 | 8 | W | lea rcx |
| rcx | 8 | R | cmp rax |
| rbp+0x638 | 8 | R | mov rdi |
| rbp+0x640 | 8 | R | cmp qword 0x10 |
| rbp+0x628 | 8 | R | mov r9 |
| rsi+0x10 | 8 | W | lea rbx |
| rsi+0x28 | 8 | R | mov rax |
| rdi | 8 | R | cmp rax |
| rbx | 8 | W | mov rcx |
| rdx | 8 | W | mov rdx |
| 0x9D6D0 | 8 | W | call sub_9d6d0 |
| rsi+0x20 | 8 | W | mov rdi |
| rbx | 8 | W | mov rcx |
| r9 | 8 | W | mov rdx |
| rdi | 8 | W | mov r8 |
| 0xEEC6DE0 | 8 | W | call sub_eec6de0 |
| rbx+rdi | 1 | W | mov byte 0 |
| rbp+0x620 | 8 | R | mov rax |
| rsi+8 | 8 | W | mov rax |
| rsi+0x30 | 8 | W | mov qword 0 |
| rbp+0x8A0 | 8 | R | mov rax |
| rax+0x58 | 8 | W | mov qword 0 |
| rbp+0x640 | 8 | R | mov rax |
| rbp+0x9F8 | 8 | R | mov rsi |
| rax | 4 | R | cmp 0x10 |
| rbp+0x628 | 8 | R | mov rcx |
| rax | 8 | W | lea rdx |
| rdx | 4 | R | cmp 0x1000 |
| rcx-8 | 8 | R | mov r8 |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20 |
| rax | 8 | W | add 0x28 |
| rdx | 8 | W | mov rax |
| rcx | 8 | W | mov r8 |
| 0xE935700 | 8 | W | call sub_e935700 (multiple) |
| rbp+0x638 | 8 | W | mov qword 0 |
| rbp+0x640 | 8 | W | mov qword 0xF |
| rbp+0x628 | 1 | W | mov byte 0 |
| rbp+0x410 | 8 | R | lea rcx |
| 0xBC5B720 | 8 | W | call sub_bc5b720 |
| rbp+0x710 | 8 | R | mov rax |
| rax | 4 | R | cmp 0x10 |
| rbp+0x6F8 | 8 | R | mov rcx |
| rax | 8 | W | lea rdx |
| rdx | 4 | R | cmp 0x1000 |
| rcx-8 | 8 | R | mov r8 |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20 |
| rax | 8 | W | add 0x28 |
| rdx | 8 | W | mov rax |
| rcx | 8 | W | mov r8 |
| rbp+0x808 | 8 | R | mov rax |
| rbp+0x7F0 | 8 | R | mov rcx |
| rbp+0x850 | 8 | R | mov rax |
| rbp+0x838 | 8 | R | mov rcx |
| rbp+0x400 | 8 | R | mov rax |
| rbp+0x3E8 | 8 | R | mov rcx |
| rbp+0x7A8 | 8 | R | mov rax |
| rbp+0x790 | 8 | R | mov rcx |
| rbp+0x760 | 8 | R | mov rax |
| r14 | 8 | W | mov rax |
| r14+8 | 8 | W | mov rax |
| r14+0x18 | 8 | W | mov rax |
| r14+0x20 | 8 | W | mov rax |
| rsi | 4 | R | cvtsi2ss xmm0 |
| r14+0x10 | 1 | W | mov byte 1 |
| r14+0x28 | 1 | W | mov byte 1 |
| rbp+0x7C0 | 16 | R | movaps xmm1 |
| r14+0x30 | 4 | W | movss xmm1 |
| rbp+0x7D0 | 16 | R | movaps xmm1 |
| r14+0x34 | 4 | W | movss xmm1 |
| rbp+0x894 | 4 | R | movss xmm1 |
| r14+0x38 | 4 | W | movss xmm1 |
| r14+0x3C | 4 | W | movss xmm0 |
| r14+0x40 | 4 | W | movss xmm7 |
| rbp+0x198 | 1 | R | cmp byte 1 |
| rbp+0x180 | 8 | R | mov rcx |
| rcx | 1 | R | test/je |
| rbp+0x190 | 8 | R | mov rdx |
| rdx | 8 | R | sub rcx |
| rdx | 4 | R | cmp 0x1000 |
| rcx-8 | 8 | R | mov rax |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20 |
| rdx | 8 | W | add 0x27 |
| rcx | 8 | W | mov rax |
| rbp+0x180 | 8 | W | lea rsi |
| 0xE935700 | 8 | W | call sub_e935700 |
| rsi | 16 | W | movups xmm0 |
| rsi+0x10 | 8 | W | mov qword 0 |
| rdi | 8 | R | test/je |
| rdi+8 | 4 | R | lock dec dword |
| rdi+0xC | 4 | R | lock dec dword |
| [rdi] | 8 | R | mov rax |
| [rax] | 8 | R | mov rax |
| rdi | 8 | W | mov rcx |
| [0xF99FFA0] | 8 | W | call sub_eea6040 (4x) |
| rbp+0x758 | 8 | R | mov rdi |
| rbp+0x40 | 8 | R | mov rax |
| rbp+0x8C0..0x950 | 16 | R | movaps xmm6..xmm15 |
| rsp | 8 | W | add 0x9E8 |
| rbx/rdi/rsi/r12/r13/r14/r15/rbp | 8 | W | pop |
| 0x78ED0 | 8 | W | call sub_78ed0 |
| ecx | 4 | W | mov 0x20/0x130/0x258 |
| 0x9BC830 | 8 | W | call sub_9bc830 (multiple) |
| 0xBC589D0/0xBC58CEF/0xBC59222 | 8 | W | jmp |

**Chunk 5 callees (in order):**
1. qword ptr [0xF99FFA0] = sub_eea6040 - called multiple times (allocator/deallocator)
2. 0x9BC830 (sub_9bc830) - called multiple times
3. 0x130EE0 (sub_130ee0) - called once
4. 0x56939C0 (sub_56939c0) - called 3 times
5. 0x9D6D0 (sub_9d6d0) - called once
6. 0xEEC6DE0 (sub_eec6de0) - called once
7. 0xE935700 (sub_e935700) - called many times
8. 0xBC5B720 (sub_bc5b720) - called once
9. 0x78ED0 (sub_78ed0) - called once

### Chunk 6: 0xbc59d31..0xbc5a28f (end of sub_bc57460 - from actual rdis output)
```
0xbc59d31  xor edx,edx                                   
0xbc59d33  xor r8d,r8d                                   
0xbc59d36  xor r9d,r9d                                   
0xbc59d39  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
0xbc59d3f  lea rcx,[0x12ADF750]                          ; [data_12adf750]
0xbc59d46  call 0xE938CB0                                ; -> sub_e938cb0
0xbc59d4b  cmp dword ptr [0x12ADF750],0xFFFFFFFF         ; [data_12adf750]
0xbc59d52  jne 0xBC575B7                                 ; -> sub_bc575b7
0xbc59d58  mov r13,r12                                   
0xbc59d5b  lea rdx,[0xF5461D6]                           ; [data_f5461d6] "zLights"
0xbc59d62  lea r12,[rbp+0x410]                           
0xbc59d69  mov rcx,r12                                   
0xbc59d6c  call 0x79580                                  ; -> sub_79580
0xbc59d71  nop                                           
0xbc59d72  mov rdx,[rbp+0x420]                           
0xbc59d79  cmp qword ptr [rbp+0x428],0x10                
0xbc59d81  jb short 0xBC59D8A                            ; -> loc_bc59d8a
0xbc59d83  mov r12,[rbp+0x410]                           

loc_bc59d8a:  ; from bc59d81
0xbc59d8a  test rdx,rdx                                  
0xbc59d8d  je 0xBC59FA1                                  ; -> loc_bc59fa1
0xbc59d93  mov eax,edx                                   
0xbc59d95  and eax,3                                     
0xbc59d98  cmp rdx,4                                     
0xbc59d9c  jae 0xBC59FDD                                 ; -> loc_bc59fdd
0xbc59da2  mov rcx,0xCBF29CE484222325                    
0xbc59dac  xor r8d,r8d                                   
0xbc59daf  jmp 0xBC5A039                                 ; -> loc_bc5a039
0xbc59db4  lea rcx,[0x12ADF760]                          ; [data_12adf760]
0xbc59dbb  call 0xE938CB0                                ; -> sub_e938cb0
0xbc59dc0  cmp dword ptr [0x12ADF760],0xFFFFFFFF         ; [data_12adf760]
0xbc59dc7  jne 0xBC5761A                                 ; -> sub_bc5761a
0xbc59dcd  mov r13,r12                                   
0xbc59dd0  lea rdx,[0xF55B94D]                           ; [data_f55b94d] "Extends"
0xbc59dd7  lea r12,[rbp+0x410]                           
0xbc59dde  mov rcx,r12                                   
0xbc59de1  call 0x79580                                  ; -> sub_79580
0xbc59de6  nop                                           
0xbc59de7  mov rdx,[rbp+0x420]                           
0xbc59dee  cmp qword ptr [rbp+0x428],0x10                
0xbc59df6  jb short 0xBC59DFF                            ; -> loc_bc59dff
0xbc59df8  mov r12,[rbp+0x410]                           

loc_bc59dff:  ; from bc59df6
0xbc59dff  test rdx,rdx                                  
0xbc59e02  je 0xBC59FB0                                  ; -> loc_bc59fb0
0xbc59e08  mov eax,edx                                   
0xbc59e0a  and eax,3                                     
0xbc59e0d  cmp rdx,4                                     
0xbc59e11  jae 0xBC5A089                                 ; -> loc_bc5a089
0xbc59e17  mov rcx,0xCBF29CE484222325                    
0xbc59e21  xor r8d,r8d                                   
0xbc59e24  jmp 0xBC5A0E5                                 ; -> loc_bc5a0e5
0xbc59e29  lea rcx,[0x12ADF770]                          ; [data_12adf770]
0xbc59e30  call 0xE938CB0                                ; -> sub_e938cb0
0xbc59e35  cmp dword ptr [0x12ADF770],0xFFFFFFFF         ; [data_12adf770]
0xbc59e3c  jne 0xBC57676                                 ; -> sub_bc57676
0xbc59e42  mov r13,r12                                   
0xbc59e45  lea rdx,[0xF51DBD7]                           ; [data_f51dbd7] "zLightLookupArray"
0xbc59e4c  lea r12,[rbp+0x410]                           
0xbc59e53  mov rcx,r12                                   
0xbc59e56  call 0x79580                                  ; -> sub_79580
0xbc59e5b  nop                                           
0xbc59e5c  mov rdx,[rbp+0x420]                           
0xbc59e63  cmp qword ptr [rbp+0x428],0x10                
0xbc59e6b  jb short 0xBC59E74                            ; -> loc_bc59e74
0xbc59e6d  mov r12,[rbp+0x410]                           

loc_bc59e74:  ; from bc59e6b
0xbc59e74  test rdx,rdx                                  
0xbc59e77  je 0xBC59FBF                                  ; -> loc_bc59fbf
0xbc59e7d  mov eax,edx                                   
0xbc59e7f  and eax,3                                     
0xbc59e82  cmp rdx,4                                     
0xbc59e86  jae 0xBC5A13C                                 ; -> loc_bc5a13c
0xbc59e8c  mov rcx,0xCBF29CE484222325                    
0xbc59e96  xor r8d,r8d                                   
0xbc59e99  jmp 0xBC5A198                                 ; -> loc_bc5a198
0xbc59e9e  lea rcx,[0x12ADF780]                          ; [data_12adf780]
0xbc59ea5  call 0xE938CB0                                ; -> sub_e938cb0
0xbc59eaa  cmp dword ptr [0x12ADF780],0xFFFFFFFF         ; [data_12adf780]
0xbc59eb1  jne 0xBC576FF                                 ; -> sub_bc576ff
0xbc59eb7  mov r13,r12                                   
0xbc59eba  lea rdx,[0xF54F409]                           ; [data_f54f409] "ClusterDimensions"
0xbc59ec1  lea r12,[rbp+0x410]                           
0xbc59ec8  mov rcx,r12                                   
0xbc59ecb  call 0x79580                                  ; -> sub_79580
0xbc59ed0  nop                                           
0xbc59ed1  mov r8,[rbp+0x420]                            
0xbc59ed8  cmp qword ptr [rbp+0x428],0x10                
0xbc59ee0  jb short 0xBC59EE9                            ; -> loc_bc59ee9
0xbc59ee2  mov r12,[rbp+0x410]                           

loc_bc59ee9:  ; from bc59ee0
0xbc59ee9  test r8,r8                                    
0xbc59eec  je 0xBC59FCE                                  ; -> loc_bc59fce
0xbc59ef2  mov eax,r8d                                   
0xbc59ef5  and eax,3                                     
0xbc59ef8  mov rcx,0x100000001B3                         
0xbc59f02  cmp r8,4                                      
0xbc59f06  jae 0xBC5A1EF                                 ; -> loc_bc5a1ef
0xbc59f0c  mov rdx,0xCBF29CE484222325                    
0xbc59f16  xor r9d,r9d                                   
0xbc59f19  jmp 0xBC5A241                                 ; -> loc_bc5a241
0xbc59f1e  lea rcx,[0x12ADF798]                          ; [data_12adf798]
0xbc59f25  call 0xE938CB0                                ; -> sub_e938cb0
0xbc59f2a  cmp dword ptr [0x12ADF798],0xFFFFFFFF         ; [data_12adf798]
0xbc59f31  jne 0xBC57724                                 ; -> sub_bc57724
0xbc59f37  xorps xmm0,xmm0                               
0xbc59f3a  movaps [rbp-0x20],xmm0                        
0xbc59f3e  lea rax,[0xF5B49BF]                           ; [data_f5b49bf] "LightClustering"
0xbc59f45  mov [rbp+0x1C0],rax                           
0xbc59f4c  mov qword ptr [rbp+0x1C8],0xF                 
0xbc59f57  lea rcx,[0x12ADF788]                          ; [data_12adf788]
0xbc59f5e  lea rdx,[rbp+0x1C0]                           
0xbc59f65  lea r8,[rbp-0x20]                             
0xbc59f69  call 0x5668AC0                                ; -> sub_5668ac0
0xbc59f6e  nop                                           
0xbc59f6f  lea rcx,[0x12ADF798]                          ; [data_12adf798]
0xbc59f76  call 0xE938D70                                ; -> sub_e938d70
0xbc59f7b  jmp 0xBC57724                                 ; -> sub_bc57724
0xbc59f80  mov [rbp+0x880],r8                            
0xbc59f87  call 0x75720                                  ; -> sub_75720
0xbc59f8c  nop                                           
0xbc59f8d  mov [rbp+0x878],rcx                           
0xbc59f94  mov [rbp+0x880],r9                            
0xbc59f9b  call 0x75740                                  ; -> sub_75740
0xbc59fa0  nop                                           

loc_bc59fa1:  ; from bc59d8d
0xbc59fa1  mov rcx,0xCBF29CE484222325                    
0xbc59fab  jmp 0xBC5A062                                 ; -> loc_bc5a062

loc_bc59fb0:  ; from bc59e02
0xbc59fb0  mov rcx,0xCBF29CE484222325                    
0xbc59fba  jmp 0xBC5A10E                                 ; -> loc_bc5a10e

loc_bc59fbf:  ; from bc59e77
0xbc59fbf  mov rcx,0xCBF29CE484222325                    
0xbc59fc9  jmp 0xBC5A1C1                                 ; -> loc_bc5a1c1

loc_bc59fce:  ; from bc59eec
0xbc59fce  mov rdx,0xCBF29CE484222325                    
0xbc59fd8  jmp 0xBC5A261                                 ; -> loc_bc5a261

loc_bc59fdd:  ; from bc59d9c
0xbc59fdd  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc59fe1  mov rcx,0xCBF29CE484222325                    
0xbc59feb  xor r8d,r8d                                   
0xbc59fee  mov r9,0x100000001B3                          

loc_bc59ff8:  ; from bc5a032
0xbc59ff8  movzx r10d,byte ptr [r12+r8]                  
0xbc59ffd  xor r10,rcx                                   
0xbc5a000  imul r10,r9                                   
0xbc5a004  movzx ecx,byte ptr [r12+r8+1]                 
0xbc5a00a  xor rcx,r10                                   
0xbc5a00d  imul rcx,r9                                   
0xbc5a011  movzx r10d,byte ptr [r12+r8+2]                
0xbc5a017  xor r10,rcx                                   
0xbc5a01a  imul r10,r9                                   
0xbc5a01e  movzx ecx,byte ptr [r12+r8+3]                 
0xbc5a024  xor rcx,r10                                   
0xbc5a027  imul rcx,r9                                   
0xbc5a02b  add r8,4                                      
0xbc5a02f  cmp rdx,r8                                    
0xbc5a032  jne short 0xBC59FF8                           ; -> loc_bc59ff8
0xbc5a034  test rax,rax                                  
0xbc5a037  je short 0xBC5A062                            ; -> loc_bc5a062

loc_bc5a039:  ; from bc59daf
0xbc5a039  add r12,r8                                    
0xbc5a03c  xor edx,edx                                   
0xbc5a03e  mov r8,0x100000001B3                          
0xbc5a048  mov r9,rcx                                    

loc_bc5a04b:  ; from bc5a060
0xbc5a04b  movzx ecx,byte ptr [r12+rdx]                  
0xbc5a050  xor rcx,r9                                    
0xbc5a053  imul rcx,r8                                   
0xbc5a057  inc rdx                                       
0xbc5a05a  mov r9,rcx                                    
0xbc5a05d  cmp rax,rdx                                   
0xbc5a060  jne short 0xBC5A04B                           ; -> loc_bc5a04b

loc_bc5a062:  ; from bc59fab, bc5a037
0xbc5a062  mov [0x12ADF748],rcx                          ; [data_12adf748]
0xbc5a069  lea rcx,[rbp+0x410]                           
0xbc5a070  call 0x73150                                  ; -> sub_73150
0xbc5a075  lea rcx,[0x12ADF750]                          ; [data_12adf750]
0xbc5a07c  call 0xE938D70                                ; -> sub_e938d70
0xbc5a081  mov r12,r13                                   
0xbc5a084  jmp 0xBC575B7                                 ; -> sub_bc575b7

loc_bc5a089:  ; from bc59e11
0xbc5a089  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc5a08d  mov rcx,0xCBF29CE484222325                    
0xbc5a097  xor r8d,r8d                                   
0xbc5a09a  mov r9,0x100000001B3                          

loc_bc5a0a4:  ; from bc5a0de
0xbc5a0a4  movzx r10d,byte ptr [r12+r8]                  
0xbc5a0a9  xor r10,rcx                                   
0xbc5a0ac  imul r10,r9                                   
0xbc5a0b0  movzx ecx,byte ptr [r12+r8+1]                 
0xbc5a0b6  xor rcx,r10                                   
0xbc5a0b9  imul rcx,r9                                   
0xbc5a0bd  movzx r10d,byte ptr [r12+r8+2]                
0xbc5a0c3  xor r10,rcx                                   
0xbc5a0c6  imul r10,r9                                   
0xbc5a0ca  movzx ecx,byte ptr [r12+r8+3]                 
0xbc5a0d0  xor rcx,r10                                   
0xbc5a0d3  imul rcx,r9                                   
0xbc5a0d7  add r8,4                                      
0xbc5a0db  cmp rdx,r8                                    
0xbc5a0de  jne short 0xBC5A0A4                           ; -> loc_bc5a0a4
0xbc5a0e0  test rax,rax                                  
0xbc5a0e3  je short 0xBC5A10E                            ; -> loc_bc5a10e

loc_bc5a0e5:  ; from bc59e24
0xbc5a0e5  add r12,r8                                    
0xbc5a0e8  xor edx,edx                                   
0xbc5a0ea  mov r8,0x100000001B3                          
0xbc5a0f4  mov r9,rcx                                    

loc_bc5a0f7:  ; from bc5a10c
0xbc5a0f7  movzx ecx,byte ptr [r12+rdx]                  
0xbc5a0fc  xor rcx,r9                                    
0xbc5a0ff  imul rcx,r8                                   
0xbc5a103  inc rdx                                       
0xbc5a106  mov r9,rcx                                    
0xbc5a109  cmp rax,rdx                                   
0xbc5a10c  jne short 0xBC5A0F7                           ; -> loc_bc5a0f7

loc_bc5a10e:  ; from bc59fba, bc5a0e3
0xbc5a10e  mov [0x12ADF758],rcx                          ; [data_12adf758]
0xbc5a115  lea rcx,[rbp+0x410]                           
0xbc5a11c  call 0x73150                                  ; -> sub_73150
0xbc5a121  lea rcx,[0x12ADF760]                          ; [data_12adf760]
0xbc5a128  call 0xE938D70                                ; -> sub_e938d70
0xbc5a12d  mov r12,r13                                   
0xbc5a130  mov r13,[rbp+0x8A0]                           
0xbc5a137  jmp 0xBC5761A                                 ; -> sub_bc5761a

loc_bc5a13c:  ; from bc59e86
0xbc5a13c  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc5a140  mov rcx,0xCBF29CE484222325                    
0xbc5a14a  xor r8d,r8d                                   
0xbc5a14d  mov r9,0x100000001B3                          

loc_bc5a157:  ; from bc5a191
0xbc5a157  movzx r10d,byte ptr [r12+r8]                  
0xbc5a15c  xor r10,rcx                                   
0xbc5a15f  imul r10,r9                                   
0xbc5a163  movzx ecx,byte ptr [r12+r8+1]                 
0xbc5a169  xor rcx,r10                                   
0xbc5a16c  imul rcx,r9                                   
0xbc5a170  movzx r10d,byte ptr [r12+r8+2]                
0xbc5a176  xor r10,rcx                                   
0xbc5a179  imul r10,r9                                   
0xbc5a17d  movzx ecx,byte ptr [r12+r8+3]                 
0xbc5a183  xor rcx,r10                                   
0xbc5a186  imul rcx,r9                                   
0xbc5a18a  add r8,4                                      
0xbc5a18e  cmp rdx,r8                                    
0xbc5a191  jne short 0xBC5A157                           ; -> loc_bc5a157
0xbc5a193  test rax,rax                                  
0xbc5a196  je short 0xBC5A1C1                            ; -> loc_bc5a1c1

loc_bc5a198:  ; from bc59e99
0xbc5a198  add r12,r8                                    
0xbc5a19b  xor edx,edx                                   
0xbc5a19d  mov r8,0x100000001B3                          
0xbc5a1a7  mov r9,rcx                                    

loc_bc5a1aa:  ; from bc5a1bf
0xbc5a1aa  movzx ecx,byte ptr [r12+rdx]                  
0xbc5a1af  xor rcx,r9                                    
0xbc5a1b2  imul rcx,r8                                   
0xbc5a1b6  inc rdx                                       
0xbc5a1b9  mov r9,rcx                                    
0xbc5a1bc  cmp rax,rdx                                   
0xbc5a1bf  jne short 0xBC5A1AA                           ; -> loc_bc5a1aa

loc_bc5a1c1:  ; from bc59fc9, bc5a196
0xbc5a1c1  mov [0x12ADF768],rcx                          ; [data_12adf768]
0xbc5a1c8  lea rcx,[rbp+0x410]                           
0xbc5a1cf  call 0x73150                                  ; -> sub_73150
0xbc5a1d4  lea rcx,[0x12ADF770]                          ; [data_12adf770]
0xbc5a1db  call 0xE938D70                                ; -> sub_e938d70
0xbc5a1e0  mov r12,r13                                   
0xbc5a1e3  mov r13,[rbp+0x8A0]                           
0xbc5a1ea  jmp 0xBC57676                                 ; -> sub_bc57676

loc_bc5a1ef:  ; from bc59f06
0xbc5a1ef  and r8,0xFFFFFFFFFFFFFFFC                     
0xbc5a1f3  mov rdx,0xCBF29CE484222325                    
0xbc5a1fd  xor r9d,r9d                                   

loc_bc5a200:  ; from bc5a23a
0xbc5a200  movzx r10d,byte ptr [r12+r9]                  
0xbc5a205  xor r10,rdx                                   
0xbc5a208  imul r10,rcx                                  
0xbc5a20c  movzx edx,byte ptr [r12+r9+1]                 
0xbc5a212  xor rdx,r10                                   
0xbc5a215  imul rdx,rcx                                  
0xbc5a219  movzx r10d,byte ptr [r12+r9+2]                
0xbc5a21f  xor r10,rdx                                   
0xbc5a222  imul r10,rcx                                  
0xbc5a226  movzx edx,byte ptr [r12+r9+3]                 
0xbc5a22c  xor rdx,r10                                   
0xbc5a22f  imul rdx,rcx                                  
0xbc5a233  add r9,4                                      
0xbc5a237  cmp r8,r9                                     
0xbc5a23a  jne short 0xBC5A200                           ; -> loc_bc5a200
0xbc5a23c  test rax,rax                                  
0xbc5a23f  je short 0xBC5A261                            ; -> loc_bc5a261

loc_bc5a241:  ; from bc59f19
0xbc5a241  add r12,r9                                    
0xbc5a244  xor r8d,r8d                                   
0xbc5a247  mov r9,rdx                                    

loc_bc5a24a:  ; from bc5a25f
0xbc5a24a  movzx edx,byte ptr [r12+r8]                   
0xbc5a24f  xor rdx,r9                                    
0xbc5a252  imul rdx,rcx                                  
0xbc5a256  inc r8                                        
0xbc5a259  mov r9,rdx                                    
0xbc5a25c  cmp rax,r8                                    
0xbc5a25f  jne short 0xBC5A24A                           ; -> loc_bc5a24a

loc_bc5a261:  ; from bc59fd8, bc5a23f
0xbc5a261  mov [0x12ADF778],rdx                          ; [data_12adf778]
0xbc5a268  lea rcx,[rbp+0x410]                           
0xbc5a26f  call 0x73150                                  ; -> sub_73150
0xbc5a274  lea rcx,[0x12ADF780]                          ; [data_12adf780]
0xbc5a27b  call 0xE938D70                                ; -> sub_e938d70
0xbc5a280  mov r12,r13                                   
0xbc5a283  jmp 0xBC576FF                                 ; -> sub_bc576ff
0xbc5a288  call 0x75740                                  ; -> sub_75740
0xbc5a28d  nop                                           
0xbc5a28e  int3                                          
0xbc5a28f  nop                                           
```

**Chunk 6 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| edx/r8d/r9d | 4 | W | xor zero |
| [0xF9A8C78] | 8 | W | call |
| [0x12ADF750] | 8 | R/W | lea/call/cmp |
| r13 | 8 | W | mov r12 |
| rdx | 8 | R/W | lea string/lea r12/mov rcx/call |
| rbp+0x410 | 8 | W | lea r12 |
| rbp+0x420 | 8 | R | mov rdx |
| rbp+0x428 | 8 | R | cmp qword 0x10 |
| r12 | 8 | W | mov r12 |
| rdx | 1 | R | test/je |
| eax | 4 | W | mov edx/and 3 |
| rdx | 4 | R | cmp 4 |
| rcx | 8 | W | mov constant |
| r8d | 4 | W | xor |
| [0x12ADF760] | 8 | R/W | lea/call/cmp |
| [0x12ADF770] | 8 | R/W | lea/call/cmp |
| [0x12ADF780] | 8 | R/W | lea/call/cmp |
| [0x12ADF798] | 8 | R/W | lea/call/cmp |
| rbp-0x20 | 16 | W | xorps/movaps |
| rbp+0x1C0 | 8 | W | mov string ptr |
| rbp+0x1C8 | 8 | W | mov length 0xF |
| [0x12ADF788] | 8 | R | lea rcx |
| rbp+0x1C0 | 8 | R | lea rdx |
| rbp-0x20 | 8 | R | lea r8 |
| 0x5668AC0 | 8 | W | call sub_5668ac0 |
| [0x12ADF798] | 8 | R | lea/call |
| rbp+0x880/0x878/0x880 | 8 | W | mov r8/rcx/r9 |
| 0x75720/0x75740 | 8 | W | call (2x) |
| rcx | 8 | W | mov constant (hash loops) |
| r12 | 8 | R/W | add/mov |
| rdx | 8 | R/W | and/mov |
| r8/r9 | 8 | R/W | mov/xor |
| r10d | 4 | R/W | movzx/xor/imul |
| rcx/r9 | 8 | R/W | xor/imul/mov |
| rax/rdx | 8 | R/W | test/jne/add/mov |
| [0x12ADF748/0x12ADF758/0x12ADF768/0x12ADF778] | 8 | W | mov rcx/rdx |
| rbp+0x410 | 8 | R | lea rcx |
| 0x73150 | 8 | W | call sub_73150 |
| [0x12ADF750/0x12ADF760/0x12ADF770/0x12ADF780] | 8 | R/W | lea/call |
| r12/r13 | 8 | W | mov |
| rbp+0x8A0 | 8 | R | mov r13 |

**Chunk 6 callees (in order):**
1. qword ptr [0xF9A8C78] - called once
2. 0xE938CB0 (sub_e938cb0) - called 4 times
3. 0x79580 (sub_79580) - called 4 times
4. 0xE938D70 (sub_e938d70) - called 4 times
5. 0x5668AC0 (sub_5668ac0) - called once
6. 0x75720 (sub_75720) - called once
7. 0x75740 (sub_75740) - called once
8. 0x73150 (sub_73150) - called 4 times

## sub_bc5bad0 (0xbc5bad0..0xbc5d4a1) - Light clustering pass (second function)

### Chunk 1: 0xbc5bad0..0xbc5c289 (400 instructions - from actual rdis output)
```
0xbc5bad0  push rbp                                      
0xbc5bad1  push r15                                      
0xbc5bad3  push r14                                      
0xbc5bad5  push r13                                      
0xbc5bad7  push r12                                      
0xbc5bad9  push rsi                                      
0xbc5bada  push rdi                                      
0xbc5badb  push rbx                                      
0xbc5badc  sub rsp,0x2E8                                 
0xbc5bae3  lea rbp,[rsp+0x80]                            
0xbc5baeb  movaps [rbp+0x250],xmm8                       
0xbc5baf3  movaps [rbp+0x240],xmm7                       
0xbc5bafa  movdqa [rbp+0x230],xmm6                       
0xbc5bb02  mov qword ptr [rbp+0x228],0xFFFFFFFFFFFFFFFE  
0xbc5bb0d  mov [rbp+0x220],r8                            
0xbc5bb14  mov r14,rdx                                   
0xbc5bb17  mov rdi,rcx                                   
0xbc5bb1a  lea rdx,[rcx+8]                               ; R a0+0x8
0xbc5bb1e  mov rax,[r14+8]                               ; R a1+0x8
0xbc5bb22  movzx eax,word ptr [rax+8]                    ; R *(a1+0x8)+0x8
0xbc5bb26  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
0xbc5bb2d  shl eax,6                                     
0xbc5bb30  lea rsi,[rax+rax*4]                           
0xbc5bb34  movq xmm0,[rdi+0x88]                          ; R a0+0x88
0xbc5bb3c  pxor xmm6,xmm6                                
0xbc5bb40  pmaxsw xmm0,xmm6                              
0xbc5bb44  movd xmm1,[rdi+0x8C]                          ; R a0+0x8C
0xbc5bb4c  movd [rcx+rsi+0x1EAB090],xmm0                 
0xbc5bb55  movdqa xmm0,xmm1                              
0xbc5bb59  pcmpeqw xmm0,xmm6                             
0xbc5bb5d  psubw xmm1,xmm0                               
0xbc5bb61  movd [rcx+rsi+0x1EAB094],xmm1                 
0xbc5bb6a  lea r15,[rdi+0xDC]                            ; R a0+0xDC
0xbc5bb71  lea r12,[rdi+0x9C]                            ; R a0+0x9C
0xbc5bb78  lea r13,[rdi+0x48]                            ; R a0+0x48
0xbc5bb7c  mov rbx,[0x12AE1748]                          ; [data_12ae1748]
0xbc5bb83  lea rcx,[rbx+rsi]                             
0xbc5bb87  add rcx,0x1EAB0A0                             
0xbc5bb8e  mov r8d,0x40                                  
0xbc5bb94  call 0xEBCE390                                ; -> sub_ebce390
0xbc5bb99  lea rcx,[rbx+rsi]                             
0xbc5bb9d  add rcx,0x1EAB0E0                             
0xbc5bba4  mov r8d,0x40                                  
0xbc5bbaa  mov rdx,r13                                   
0xbc5bbad  call 0xEBCE390                                ; -> sub_ebce390
0xbc5bbb2  lea rcx,[rbx+rsi]                             
0xbc5bbb6  add rcx,0x1EAB120                             
0xbc5bbbd  mov r8d,0x40                                  
0xbc5bbc3  mov rdx,r12                                   
0xbc5bbc6  call 0xEBCE390                                ; -> sub_ebce390
0xbc5bbcb  lea rcx,[rbx+rsi]                             
0xbc5bbcf  add rcx,0x1EAB160                             
0xbc5bbd6  mov r8d,0x40                                  
0xbc5bbdc  mov rdx,r15                                   
0xbc5bbdf  call 0xEBCE390                                ; -> sub_ebce390
0xbc5bbe4  lea rcx,[rbx+rsi]                             
0xbc5bbe8  add rcx,0x1EAB1A0                             
0xbc5bbef  mov rbx,r14                                   
0xbc5bbf2  mov r8d,0x10                                  
0xbc5bbf8  lea rdx,[rdi+0x11C]                           ; R a0+0x11C
0xbc5bbff  call 0xEBCE390                                ; -> sub_ebce390
0xbc5bc04  movzx eax,byte ptr [rdi+0x98]                 ; R a0+0x98
0xbc5bc0b  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
0xbc5bc12  mov [rcx+rsi+0x1EAB1B2],al                    
0xbc5bc19  mov rdi,[r14+8]                               ; R a1+0x8
0xbc5bc1d  mov [rbp+0x130],rdi                           
0xbc5bc24  movdqu [rbp+0x138],xmm6                       
0xbc5bc2c  movdqu [rbp+0x148],xmm6                       
0xbc5bc34  movdqu [rbp+0x158],xmm6                       
0xbc5bc3c  movdqu [rbp+0x168],xmm6                       
0xbc5bc44  mov qword ptr [rbp+0x178],0                   
0xbc5bc4f  mov rsi,[rdi]                                 ; R *(a1+0x8)+0x0
0xbc5bc52  mov [rbp+0x40],rsi                            
0xbc5bc56  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc5bc5d  mov rax,[rcx]                                 
0xbc5bc60  mov rax,[rax+8]                               
0xbc5bc64  mov edx,0x30                                  
0xbc5bc69  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5bc6f  nop                                           
0xbc5bc70  mov r14,rax                                   
0xbc5bc73  test rax,rax                                  
0xbc5bc76  je 0xBC5CCCB                                  ; -> loc_bc5cccb

loc_bc5bc7c:  ; from bc5ccd6
0xbc5bc7c  mov rax,0x100000001                           
0xbc5bc86  mov [r14+8],rax                               
0xbc5bc8a  lea rax,[0xF25CB70]                           ; [data_f25cb70]
0xbc5bc91  mov [r14],rax                                 
0xbc5bc94  mov rax,r14                                   
0xbc5bc97  add rax,0x10                                  
0xbc5bc9b  mov rcx,[rsi]                                 ; R *(*(a1+0x8)+0x0)+0x0
0xbc5bc9e  mov [r14+0x10],rcx                            
0xbc5bca2  pxor xmm0,xmm0                                
0xbc5bca6  movdqu [r14+0x18],xmm0                        
0xbc5bcac  mov qword ptr [r14+0x28],0                    
0xbc5bcb4  mov [rbp+0x48],rax                            
0xbc5bcb8  mov [rbp+0x50],r14                            
0xbc5bcbc  movdqu [rbp+0x58],xmm0                        
0xbc5bcc1  movdqu [rbp+0x61],xmm0                        
0xbc5bcc6  lea r15,[rbp+0x40]                            
0xbc5bcca  mov rcx,rdi                                   
0xbc5bccd  mov rdx,r15                                   
0xbc5bcd0  call 0xBCC1A30                                ; -> sub_bcc1a30
0xbc5bcd5  nop                                           
0xbc5bcd6  mov eax,[0x12ADF7A8]                          ; [data_12adf7a8]
0xbc5bcdc  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5bce2  mov rdx,gs:[0x58]                             
0xbc5bceb  mov rcx,[rdx+rcx*8]                           
0xbc5bcef  cmp eax,[rcx+4]                               
0xbc5bcf5  mov rsi,[rbp+0x220]                           
0xbc5bcfc  jg 0xBC5CCED                                  ; -> loc_bc5cced

loc_bc5bd02:  ; from bc5cd00, bc5d13c
0xbc5bd02  mov rax,[rsi+0x48]                            
0xbc5bd06  mov [rbp+0x78],rax                            
0xbc5bd0a  lea rdx,[rbp+0x80]                            
0xbc5bd11  mov rax,[rax]                                 
0xbc5bd14  lea rcx,[0xF25C7F0]                           ; [data_f25c7f0]
0xbc5bd1b  mov [rbp+0x80],rcx                            
0xbc5bd22  mov [rbp+0x88],rax                            
0xbc5bd29  mov [rbp+0xB8],rdx                            
0xbc5bd30  lea rdi,[rbp+0xC0]                            
0xbc5bd37  mov [rbp+0xC0],rdi                            
0xbc5bd3e  mov [rbp+0xC8],rdi                            
0xbc5bd45  lea rcx,[rbp+0xD0]                            
0xbc5bd4c  mov dword ptr [rbp+0xD0],0                    
0xbc5bd56  pxor xmm6,xmm6                                
0xbc5bd5a  movdqu [rbp+0xD8],xmm6                        
0xbc5bd62  movdqu [rbp+0xE8],xmm6                        
0xbc5bd6a  movdqu [rbp+0xF8],xmm6                        
0xbc5bd72  movdqu [rbp+0x108],xmm6                       
0xbc5bd7a  mov qword ptr [rbp+0x118],0                   
0xbc5bd85  mov edx,2                                     
0xbc5bd8a  call 0xEEC5870                                ; -> sub_eec5870
0xbc5bd8f  lea rcx,[rbp+0x120]                           
0xbc5bd96  call 0x9BD2E0                                 ; -> sub_9bd2e0
0xbc5bd9b  mov rax,[rsi+0x38]                            
0xbc5bda7  mov rcx,[rax+8]                               
0xbc5bdab  test rcx,rcx                                  
0xbc5bdae  je short 0xBC5BDFF                            ; -> loc_bc5bdff
0xbc5bdb0  lock inc dword ptr [rcx+8]                    
0xbc5bdb4  mov r12,[rbp+0x1E8]                           
0xbc5bdbb  movdqu xmm0,[rax]                             
0xbc5bdbf  movdqa [rbp+0x1E0],xmm0                       
0xbc5bdc7  test r12,r12                                  
0xbc5bdca  je short 0xBC5BE14                            ; -> loc_bc5be14
0xbc5bdcc  lock dec dword ptr [r12+8]                    
0xbc5bdd2  jne short 0xBC5BE14                           ; -> loc_bc5be14
0xbc5bdd4  mov rax,[r12]                                 
0xbc5bdd8  mov rax,[rax]                                 
0xbc5bddb  mov rcx,r12                                   
0xbc5bdde  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5bde4  lock dec dword ptr [r12+0xC]                  
0xbc5bdea  jne short 0xBC5BE14                           ; -> loc_bc5be14
0xbc5bdec  mov rax,[r12]                                 
0xbc5bdf0  mov rax,[rax+8]                               
0xbc5bdf4  mov rcx,r12                                   
0xbc5bdf7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5bdfd  jmp short 0xBC5BE14                           ; -> loc_bc5be14

loc_bc5bdff:  ; from bc5bdae
0xbc5bdff  mov rax,[rax]                                 
0xbc5be02  mov [rbp+0x1E0],rax                           
0xbc5be09  mov qword ptr [rbp+0x1E8],0                   

loc_bc5be14:  ; from bc5bdca, bc5bdd2, bc5bdea, bc5bdfd
0xbc5be14  mov rax,[rbp+0x1E0]                           
0xbc5be1b  mov rax,[rax+0x18]                            
0xbc5be1f  mov rax,[rax]                                 
0xbc5be22  mov [rbp-0x48],rax                            
0xbc5be26  lea r12,[rbp-0x40]                            
0xbc5be2a  mov r8,[rbp+0x78]                             
0xbc5be2e  mov rdx,[rax+0x170]                           
0xbc5be35  mov rcx,r12                                   
0xbc5be38  call 0xE86B370                                ; -> sub_e86b370
0xbc5be3d  nop                                           
0xbc5be3e  lea rax,[rbp+0x78]                            
0xbc5be42  mov [rbp+0x38],rax                            
0xbc5be46  mov r13,[rbp+0x1E8]                           
0xbc5be4d  test r13,r13                                  
0xbc5be50  je short 0xBC5BE81                            ; -> loc_bc5be81
0xbc5be52  lock dec dword ptr [r13+8]                    
0xbc5be57  jne short 0xBC5BE81                           ; -> loc_bc5be81
0xbc5be59  mov rax,[r13]                                 
0xbc5be5d  mov rax,[rax]                                 
0xbc5be60  mov rcx,r13                                   
0xbc5be63  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5be69  lock dec dword ptr [r13+0xC]                  
0xbc5be6e  jne short 0xBC5BE81                           ; -> loc_bc5be81
0xbc5be70  mov rax,[r13]                                 
0xbc5be74  mov rax,[rax+8]                               
0xbc5be78  mov rcx,r13                                   
0xbc5be7b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc5be81:  ; from bc5be50, bc5be57, bc5be6e
0xbc5be81  mov eax,[0x12ADF7B8]                          ; [data_12adf7b8]
0xbc5be87  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5be8d  mov rdx,gs:[0x58]                             
0xbc5be96  mov rcx,[rdx+rcx*8]                           
0xbc5be9a  cmp eax,[rcx+4]                               
0xbc5bea0  jg 0xBC5CD59                                  ; -> loc_bc5cd59

loc_bc5bea6:  ; from bc5cd6c, bc5d1ee
0xbc5bea6  mov eax,[0x12ADF7C8]                          ; [data_12adf7c8]
0xbc5beac  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5beb2  mov rdx,gs:[0x58]                             
0xbc5bebb  mov rcx,[rdx+rcx*8]                           
0xbc5bebf  cmp eax,[rcx+4]                               
0xbc5bec5  jg 0xBC5CDCB                                  ; -> loc_bc5cdcb

loc_bc5becb:  ; from bc5cdde, bc5d2a0
0xbc5becb  mov eax,[0x12ADF7D8]                          ; [data_12adf7d8]
0xbc5bed1  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5bed7  mov rdx,gs:[0x58]                             
0xbc5bee0  mov rcx,[rdx+rcx*8]                           
0xbc5bee4  cmp eax,[rcx+4]                               
0xbc5beea  jg 0xBC5CE3D                                  ; -> loc_bc5ce3d

loc_bc5bef0:  ; from bc5ce50, bc5d352
0xbc5bef0  mov eax,[0x12ADF7E8]                          ; [data_12adf7e8]
0xbc5bef6  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5befc  mov rdx,gs:[0x58]                             
0xbc5bf05  mov rcx,[rdx+rcx*8]                           
0xbc5bf09  cmp eax,[rcx+4]                               
0xbc5bf0f  jg 0xBC5CEAF                                  ; -> loc_bc5ceaf

loc_bc5bf15:  ; from bc5cec2, bc5d404
0xbc5bf15  movss xmm8,[0xEEC8060]                        ; [data_eec8060]
0xbc5bf1e  mov rax,[rsi+0x30]                            
0xbc5bf22  movd xmm0,[rsi+0x58]                          
0xbc5bf27  test rax,rax                                  
0xbc5bf2a  js short 0xBC5BF33                            ; -> loc_bc5bf33
0xbc5bf2c  cvtsi2ss xmm1,rax                             
0xbc5bf31  jmp short 0xBC5BF48                           ; -> loc_bc5bf48

loc_bc5bf33:  ; from bc5bf2a
0xbc5bf33  mov rcx,rax                                   
0xbc5bf36  shr rcx,1                                     
0xbc5bf39  and eax,1                                     
0xbc5bf3c  or rax,rcx                                    
0xbc5bf3f  cvtsi2ss xmm1,rax                             
0xbc5bf44  addss xmm1,xmm1                               

loc_bc5bf48:  ; from bc5bf31
0xbc5bf48  movaps xmm6,xmm8                              
0xbc5bf4c  divss xmm6,[rsi+0xC4]                         
0xbc5bf54  movaps xmm7,xmm8                              
0xbc5bf58  divss xmm7,[rsi+0xB0]                         
0xbc5bf60  movsd xmm2,[rsi+0x50]                         
0xbc5bf65  movsd [rbp+0x1E0],xmm2                        
0xbc5bf6d  movd [rbp+0x1E8],xmm0                         
0xbc5bf75  movss [rbp+0x1EC],xmm1                        
0xbc5bf7d  mov qword ptr [rbp+0x180],1                   
0xbc5bf88  lea r14,[rbp+0x1E0]                           
0xbc5bf8f  mov [rbp+0x188],r14                           
0xbc5bf96  mov rax,[rbp-0x10]                            
0xbc5bf9a  movzx ecx,word ptr [rbp-6]                    
0xbc5bf9e  mov edx,ecx                                   
0xbc5bfa0  shl edx,4                                     
0xbc5bfa3  mov r8,rax                                    
0xbc5bfa6  test ecx,ecx                                  
0xbc5bfa8  je short 0xBC5BFDD                            ; -> loc_bc5bfdd
0xbc5bfaa  mov r9,[0x12ADF778]                           ; [data_12adf778]
0xbc5bfb1  xor r8d,r8d                                   
0xbc5bfb4  nop [rax+rax]                                 

loc_bc5bfc0:  ; from bc5bfd1
0xbc5bfc0  mov r10,[rax+r8]                              
0xbc5bfc4  cmp [r10+0x28],r9                             
0xbc5bfc8  je short 0xBC5BFDA                            ; -> loc_bc5bfda
0xbc5bfca  add r8,0x10                                   
0xbc5bfce  cmp rdx,r8                                    
0xbc5bfd1  jne short 0xBC5BFC0                           ; -> loc_bc5bfc0
0xbc5bfd3  mov r9w,1                                     
0xbc5bfd8  jmp short 0xBC5C02F                           ; -> loc_bc5c02f

loc_bc5bfda:  ; from bc5bfc8
0xbc5bfda  add r8,rax                                    

loc_bc5bfdd:  ; from bc5bfa8
0xbc5bfdd  lea r9,[rax+rdx]                              
0xbc5bfe1  cmp r8,r9                                     
0xbc5bfe4  jae short 0xBC5C02C                           ; -> loc_bc5c02c
0xbc5bfe6  sub r8d,eax                                   
0xbc5bfe9  shr r8d,4                                     
0xbc5bfed  mov [rbp+0x1C8],r8w                           
0xbc5bff5  mov byte ptr [rbp+0x1CA],1                    
0xbc5bffc  lea rdx,[rbp+0x1C8]                           
0xbc5c003  lea r8,[rbp+0x180]                            
0xbc5c00a  mov rcx,r12                                   
0xbc5c00d  call 0x5679DB0                                ; -> sub_5679db0
0xbc5c012  nop                                           
0xbc5c013  mov rax,[rbp-0x10]                            
0xbc5c017  movzx ecx,word ptr [rbp-6]                    
0xbc5c01b  mov edx,ecx                                   
0xbc5c01d  shl edx,4                                     
0xbc5c020  mov r9d,ecx                                   
0xbc5c023  mov rsi,[rbp+0x220]                           
0xbc5c02a  jmp short 0xBC5C02F                           ; -> loc_bc5c02f

loc_bc5c02c:  ; from bc5bfe4
0xbc5c02c  mov r9d,ecx                                   

loc_bc5c02f:  ; from bc5bfd8, bc5c02a
0xbc5c02f  xorps xmm0,xmm0                               
0xbc5c032  cvtsi2ss xmm0,dword ptr [rsi+0x68]            
0xbc5c037  shufps xmm0,xmm0,0                            
0xbc5c03b  movaps [rbp+0x1E0],xmm0                       
0xbc5c042  mov qword ptr [rbp+0x180],1                   
0xbc5c04d  mov [rbp+0x188],r14                           
0xbc5c054  mov r8,rax                                    
0xbc5c057  test r9w,r9w                                  
0xbc5c05b  je short 0xBC5C088                            ; -> loc_bc5c088
0xbc5c05d  mov r9,[0x12ADF7A0]                           ; [data_12adf7a0]
0xbc5c064  xor r8d,r8d                                   
0xbc5c067  nop [rax+rax]                                 

loc_bc5c070:  ; from bc5c081
0xbc5c070  mov r10,[rax+r8]                              
0xbc5c074  cmp [r10+0x28],r9                             
0xbc5c078  je short 0xBC5C085                            ; -> loc_bc5c085
0xbc5c07a  add r8,0x10                                   
0xbc5c07e  cmp rdx,r8                                    
0xbc5c081  jne short 0xBC5C070                           ; -> loc_bc5c070
0xbc5c083  jmp short 0xBC5C0CC                           ; -> loc_bc5c0cc

loc_bc5c085:  ; from bc5c078
0xbc5c085  add r8,rax                                    

loc_bc5c088:  ; from bc5c05b
0xbc5c088  add rdx,rax                                   
0xbc5c08b  cmp r8,rdx                                    
0xbc5c08e  jae short 0xBC5C0CC                           ; -> loc_bc5c0cc
0xbc5c090  sub r8d,eax                                   
0xbc5c093  shr r8d,4                                     
0xbc5c097  mov [rbp+0x1C8],r8w                           
0xbc5c09f  mov byte ptr [rbp+0x1CA],1                    
0xbc5c0a6  lea rdx,[rbp+0x1C8]                           
0xbc5c0ad  lea r8,[rbp+0x180]                            
0xbc5c0b4  mov rcx,r12                                   
0xbc5c0b7  call 0x5679DB0                                ; -> sub_5679db0
0xbc5c0bc  nop                                           
0xbc5c0bd  mov rax,[rbp-0x10]                            
0xbc5c0c1  movzx ecx,word ptr [rbp-6]                    
0xbc5c0c5  mov rsi,[rbp+0x220]                           

loc_bc5c0cc:  ; from bc5c083, bc5c08e
0xbc5c0cc  movss xmm0,[rsi+0x78]                         
0xbc5c0d1  movd xmm1,[rsi+0x88]                          
0xbc5c0d9  movd [rbp+0x1E0],xmm1                         
0xbc5c0e1  movss [rbp+0x1E4],xmm0                        
0xbc5c0e9  movd xmm0,[rsi+0xA4]                          
0xbc5c0f1  pxor xmm1,xmm1                                
0xbc5c0f5  punpcklwd xmm0,xmm1                           
0xbc5c0f9  cvtdq2ps xmm0,xmm0                            
0xbc5c103  mov qword ptr [rbp+0x180],1                   
0xbc5c10e  mov [rbp+0x188],r14                           
0xbc5c115  movzx r9d,cx                                  
0xbc5c119  mov edx,r9d                                   
0xbc5c11c  shl edx,4                                     
0xbc5c11f  mov r8,rax                                    
0xbc5c122  test r9w,r9w                                  
0xbc5c126  je short 0xBC5C158                            ; -> loc_bc5c158                                  
0xbc5c12f  je short 0xBC5C158                            ; -> loc_bc5c158
0xbc5c128  mov r9,[0x12ADF7B0]                           ; [data_12adf7b0]
0xbc5c12f  xor r8d,r8d                                   
0xbc5c132  nop [rax+rax]                                 

loc_bc5c140:  ; from bc5c151
0xbc5c140  mov r10,[rax+r8]                              
0xbc5c144  cmp [r10+0x28],r9                             
0xbc5c148  je short 0xBC5C155                            ; -> loc_bc5c155
0xbc5c14a  add r8,0x10                                   
0xbc5c14e  cmp rdx,r8                                    
0xbc5c151  jne short 0xBC5C140                           ; -> loc_bc5c140
0xbc5c153  jmp short 0xBC5C1A2                           ; -> loc_bc5c1a2

loc_bc5c155:  ; from bc5c148
0xbc5c155  add r8,rax                                    

loc_bc5c158:  ; from bc5c126
0xbc5c158  lea r9,[rax+rdx]                              
0xbc5c15c  cmp r8,r9                                     
0xbc5c15f  jae short 0xBC5C1A2                           ; -> loc_bc5c1a2
0xbc5c161  sub r8d,eax                                   
0xbc5c164  shr r8d,4                                     
0xbc5c168  mov [rbp+0x1C8],r8w                           
0xbc5c170  mov byte ptr [rbp+0x1CA],1                    
0xbc5c177  lea rdx,[rbp+0x1C8]                           
0xbc5c17e  lea r8,[rbp+0x180]                            
0xbc5c185  mov rcx,r12                                   
0xbc5c188  call 0x5679DB0                                ; -> sub_5679db0
0xbc5c18d  nop                                           
0xbc5c18e  mov rax,[rbp-0x10]                            
0xbc5c192  movzx ecx,word ptr [rbp-6]                    
0xbc5c196  mov edx,ecx                                   
0xbc5c198  shl edx,4                                     
0xbc5c19b  mov rsi,[rbp+0x220]                           

loc_bc5c1a2:  ; from bc5c153, bc5c15f
0xbc5c1a2  mov r8d,0x80000000                            
0xbc5c1a8  xor r8d,[rsi+0x8C]                            
0xbc5c1af  movq xmm0,[rsi+0x90]                          
0xbc5c1b7  movq [rbp+0x1E0],xmm0                         
0xbc5c1bf  mov [rbp+0x1E8],r8d                           
0xbc5c1c6  mov dword ptr [rbp+0x1EC],0                   
0xbc5c1d0  mov qword ptr [rbp+0x180],1                   
0xbc5c1db  mov [rbp+0x188],r14                           
0xbc5c1e2  mov r8,rax                                    
0xbc5c1e5  test cx,cx                                    
0xbc5c1e8  je short 0xBC5C218                            ; -> loc_bc5c218
0xbc5c1ea  mov r9,[0x12ADF7C0]                           ; [data_12adf7c0]
0xbc5c1f1  xor r8d,r8d                                   
0xbc5c1f4  nop [rax+rax]                                 

loc_bc5c200:  ; from bc5c211
0xbc5c200  mov r10,[rax+r8]                              
0xbc5c204  cmp [r10+0x28],r9                             
0xbc5c208  je short 0xBC5C215                            ; -> loc_bc5c215
0xbc5c20a  add r8,0x10                                   
0xbc5c20e  cmp rdx,r8                                    
0xbc5c211  jne short 0xBC5C200                           ; -> loc_bc5c200
0xbc5c213  jmp short 0xBC5C262                           ; -> loc_bc5c262

loc_bc5c215:  ; from bc5c208
0xbc5c215  add r8,rax                                    

loc_bc5c218:  ; from bc5c1e8
0xbc5c218  lea r9,[rax+rdx]                              
0xbc5c21c  cmp r8,r9                                     
0xbc5c21f  jae short 0xBC5C262                           ; -> loc_bc5c262
0xbc5c221  sub r8d,eax                                   
0xbc5c224  shr r8d,4                                     
0xbc5c228  mov [rbp+0x1C8],r8w                           
0xbc5c230  mov byte ptr [rbp+0x1CA],1                    
0xbc5c237  lea rdx,[rbp+0x1C8]                           
0xbc5c23e  lea r8,[rbp+0x180]                            
0xbc5c245  mov rcx,r12                                   
0xbc5c248  call 0x5679DB0                                ; -> sub_5679db0
0xbc5c24d  nop                                           
0xbc5c24e  mov rax,[rbp-0x10]                            
0xbc5c252  movzx ecx,word ptr [rbp-6]                    
0xbc5c256  mov edx,ecx                                   
0xbc5c258  shl edx,4                                     
0xbc5c25b  mov rsi,[rbp+0x220]                           

loc_bc5c262:  ; from bc5c213, bc5c21f
0xbc5c262  movq xmm0,[rsi+0x6C]                          
0xbc5c267  movdqu [rbp+0x1E0],xmm0                       
0xbc5c26f  mov qword ptr [rbp+0x180],1                   
0xbc5c27a  mov [rbp+0x188],r14                           
0xbc5c281  mov r8,rax                                    
0xbc5c284  test cx,cx                                    
0xbc5c287  je short 0xBC5C2BC                            ; -> loc_bc5c2bc
0xbc5c289  mov r9,[0x12ADF7D0]                           ; [data_12adf7d0]
```

**Chunk 1 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| rbp+0x250 | 16 | W | xmm8 save |
| rbp+0x240 | 16 | W | xmm7 save |
| rbp+0x230 | 16 | W | xmm6 save |
| rbp+0x228 | 8 | W | stack cookie |
| rbp+0x220 | 8 | W | r8 (arg3) |
| r14 | 8 | W | mov rdx |
| rdi | 8 | W | mov rcx |
| rcx+8 | 8 | W | lea rdx |
| r14+8 | 8 | R | mov rax |
| rax+8 | 2 | R | movzx eax |
| [0x12AE1748] | 8 | R | mov rcx |
| eax | 4 | W | shl 6 |
| rdi+0x88 | 8 | R | movq xmm0 |
| xmm6 | 16 | W | pxor |
| xmm0 | 16 | W | pmaxsw |
| rdi+0x8C | 4 | R | movd xmm1 |
| rcx+rsi+0x1EAB090 | 4 | W | movd xmm0 |
| xmm0 | 16 | W | movdqa |
| xmm0 | 16 | W | pcmpeqw |
| xmm1 | 16 | W | psubw |
| rcx+rsi+0x1EAB094 | 4 | W | movd xmm1 |
| rdi+0xDC | 8 | W | lea r15 |
| rdi+0x9C | 8 | W | lea r12 |
| rdi+0x48 | 8 | W | lea r13 |
| [0x12AE1748] | 8 | R | mov rbx |
| rbx+rsi | 8 | W | lea rcx |
| rcx+0x1EAB0A0 | 8 | W | add rcx |
| r8d | 4 | W | mov 0x40 |
| 0xEBCE390 | 8 | W | call sub_ebce390 (4x) |
| rbx+rsi+0x1EAB0E0 | 8 | W | add rcx |
| r13 | 8 | W | mov rdx |
| rbx+rsi+0x1EAB120 | 8 | W | add rcx |
| r12 | 8 | W | mov rdx |
| rbx+rsi+0x1EAB160 | 8 | W | add rcx |
| r15 | 8 | W | mov rdx |
| rbx+rsi+0x1EAB1A0 | 8 | W | add rcx |
| r14 | 8 | W | mov rbx |
| r8d | 4 | W | mov 0x10 |
| rdi+0x11C | 8 | W | lea rdx |
| rdi+0x98 | 1 | R | movzx eax |
| [0x12AE1748] | 8 | R | mov rcx |
| rcx+rsi+0x1EAB1B2 | 1 | W | mov al |
| r14+8 | 8 | R | mov rdi |
| rbp+0x130 | 8 | W | mov rdi |
| rbp+0x138/0x148/0x158/0x168 | 16 | W | movdqu xmm6 |
| rbp+0x178 | 8 | W | mov qword 0 |
| rdi | 8 | R | mov rsi |
| rbp+0x40 | 8 | W | mov rsi |
| [0x1233E1A8] | 8 | R | mov rcx |
| [rcx] | 8 | R | mov rax |
| [rax+8] | 8 | R | mov rax |
| edx | 4 | W | mov 0x30 |
| [0xF99FFA0] | 8 | W | call sub_eea6040 |
| r14 | 8 | W | mov rax |
| rax | 1 | R | test/je |
| rax | 8 | W | mov 0x100000001 |
| r14+8 | 8 | W | mov rax |
| [0xF25CB70] | 8 | R | lea rax |
| r14 | 8 | W | mov rax |
| r14 | 8 | R | mov rax |
| rax | 8 | W | add 0x10 |
| rsi | 8 | R | mov rcx |
| r14+0x10 | 8 | W | mov rcx |
| xmm0 | 16 | W | pxor |
| r14+0x18 | 16 | W | movdqu xmm0 |
| r14+0x28 | 8 | W | mov qword 0 |
| rbp+0x48 | 8 | W | mov rax |
| rbp+0x50 | 8 | W | mov r14 |
| rbp+0x58/0x61 | 16 | W | movdqu xmm0 |
| rbp+0x40 | 8 | W | lea r15 |
| rdi | 8 | R | mov rcx |
| r15 | 8 | W | mov rdx |
| 0xBCC1A30 | 8 | W | call sub_bcc1a30 |
| [0x12ADF7A8] | 4 | R | mov eax |
| [0x128767C8] | 4 | R | mov ecx |
| gs:[0x58] | 8 | R | mov rdx |
| rdx+rcx*8 | 8 | R | mov rcx |
| rcx+4 | 4 | R | cmp eax |
| rbp+0x220 | 8 | R | mov rsi |
| rsi+0x48 | 8 | R | mov rax |
| rbp+0x78 | 8 | W | mov rax |
| rbp+0x80 | 8 | W | lea rdx |
| rax | 8 | R | mov rax |
| [0xF25C7F0] | 8 | R | lea rcx |
| rbp+0x80 | 8 | W | mov rcx |
| rbp+0x88 | 8 | W | mov rax |
| rbp+0xB8 | 8 | W | mov rdx |
| rbp+0xC0 | 8 | W | lea rdi/mov rdi |
| rbp+0xC8 | 8 | W | mov rdi |
| rbp+0xD0 | 4 | W | mov dword 0 |
| xmm6 | 16 | W | pxor |
| rbp+0xD8/0xE8/0xF8/0x108 | 16 | W | movdqu xmm6 |
| rbp+0x118 | 8 | W | mov qword 0 |
| edx | 4 | W | mov 2 |
| 0xEEC5870 | 8 | W | call sub_eec5870 |
| rbp+0x120 | 8 | W | lea rcx |
| 0x9BD2E0 | 8 | W | call sub_9bd2e0 |
| rsi+0x38 | 8 | R | mov rax |
| rbp+0x1E0 | 16 | W | movdqa xmm6 |
| rax+8 | 8 | R | mov rcx |
| rcx | 1 | R | test/je |
| rcx+8 | 4 | R | lock inc dword |
| rbp+0x1E8 | 8 | R | mov r12 |
| rax | 16 | R | movdqu xmm0 |
| rbp+0x1E0 | 16 | W | movdqa xmm0 |
| r12 | 1 | R | test/je |
| r12+8 | 4 | R | lock dec dword |
| r12 | 8 | R | mov rax |
| rax | 8 | R | mov rax |
| r12 | 8 | W | mov rcx |
| [0xF99FFA0] | 8 | W | call sub_eea6040 (4x) |
| r12+0xC | 4 | R | lock dec dword |
| rax | 8 | R | mov rax |
| rax+8 | 8 | R | mov rax |
| rax | 8 | R | mov rax |
| rbp+0x1E0 | 8 | W | mov rax |
| rbp+0x1E8 | 8 | W | mov qword 0 |
| rbp+0x1E0 | 8 | R | mov rax |
| rax+0x18 | 8 | R | mov rax |
| rax+0x18 | 8 | R | mov rax |
| rax | 8 | R | mov rax |
| rbp-0x48 | 8 | W | mov rax |
| rbp-0x40 | 8 | W | lea r12 |
| rbp+0x78 | 8 | R | mov r8 |
| rax+0x170 | 8 | R | mov rdx |
| r12 | 8 | W | mov rcx |
| 0xE86B370 | 8 | W | call sub_e86b370 |
| rbp+0x78 | 8 | W | lea rax |
| rbp+0x38 | 8 | W | mov rax |
| rbp+0x1E8 | 8 | R | mov r13 |
| r13 | 1 | R | test/je |
| r13+8 | 4 | R | lock dec dword |
| r13 | 8 | R | mov rax |
| rax | 8 | R | mov rax |
| r13 | 8 | W | mov rcx |
| [0xF99FFA0] | 8 | W | call sub_eea6040 (4x) |
| r13+0xC | 4 | R | lock dec dword |
| [0x12ADF7B8] | 4 | R | mov eax |
| [0x128767C8] | 4 | R | mov ecx |
| gs:[0x58] | 8 | R | mov rdx |
| rdx+rcx*8 | 8 | R | mov rcx |
| rcx+4 | 4 | R | cmp eax |
| [0x12ADF7C8] | 4 | R | mov eax |
| [0x12ADF7D8] | 4 | R | mov eax |
| [0x12ADF7E8] | 4 | R | mov eax |
| [0xEEC8060] | 4 | R | movss xmm8 |
| rsi+0x30 | 8 | R | mov rax |
| rsi+0x58 | 4 | R | movd xmm0 |
| rax | 1 | R | test/js |
| rax | 8 | R/W | shr/and/or/cvtsi2ss |
| xmm8 | 16 | W | movaps xmm6/xmm7 |
| rsi+0xC4 | 4 | R | divss xmm6 |
| rsi+0xB0 | 4 | R | divss xmm7 |
| rsi+0x50 | 8 | R | movsd xmm2 |
| rbp+0x1E0 | 8 | W | movsd xmm2 |
| rbp+0x1E8 | 4 | W | movd xmm0 |
| rbp+0x1EC | 4 | W | movss xmm1 |
| rbp+0x180 | 8 | W | mov qword 1 |
| rbp+0x1E0 | 8 | W | lea r14 |
| rbp+0x188 | 8 | W | mov r14 |
| rbp-0x10 | 8 | R | mov rax |
| rbp-6 | 2 | R | movzx ecx |
| edx | 4 | W | mov ecx |
| edx | 4 | W | shl 4 |
| r8 | 8 | W | mov rax |
| cx | 1 | R | test/je |
| [0x12ADF778] | 8 | R | mov r9 |
| r8d | 4 | W | xor |
| rax | 8 | R | mov r10 |
| r10+0x28 | 8 | R | cmp [r10+0x28] |
| r9 | 8 | R | cmp r9 |
| r8 | 4 | W | add 0x10 |
| rdx | 8 | R | cmp rdx |
| r9w | 2 | W | mov 1 |
| rdx | 8 | W | add rax |
| r9 | 8 | W | lea |
| r8 | 8 | R | cmp/jae |
| r8d | 4 | W | sub eax/shr 4 |
| rbp+0x1C8 | 2 | W | mov r8w |
| rbp+0x1CA | 1 | W | mov byte 1 |
| rbp+0x1C8 | 8 | W | lea rdx |
| rbp+0x180 | 8 | W | lea r8 |
| r12 | 8 | W | mov rcx |
| 0x5679DB0 | 8 | W | call sub_5679db0 |
| rbp-0x10 | 8 | R | mov rax |
| rbp-6 | 2 | R | movzx ecx |
| edx | 4 | W | mov ecx |
| edx | 4 | W | shl 4 |
| r9d | 4 | W | mov ecx |
| rbp+0x220 | 8 | R | mov rsi |
| rsi+0x68 | 4 | R | cvtsi2ss xmm0 |
| xmm0 | 16 | W | shufps/movaps |
| rbp+0x1E0 | 16 | W | movaps xmm0 |
| rbp+0x180 | 8 | W | mov qword 1 |
| rbp+0x188 | 8 | W | mov r14 |
| rax | 8 | W | mov r8 |
| r9w | 2 | R | test/je |
| [0x12ADF7A0] | 8 | R | mov r9 |
| r8d | 4 | W | xor |
| rax | 8 | R | mov r10 |
| r10+0x28 | 8 | R | cmp [r10+0x28] |
| r9 | 8 | R | cmp r9 |
| r8 | 4 | W | add 0x10 |
| rdx | 8 | R | cmp rdx |
| rax | 8 | W | add r8 |
| rdx | 8 | W | add rax |
| r8 | 8 | R | cmp/jae |
| r8d | 4 | W | sub eax/shr 4 |
| rbp+0x1C8 | 2 | W | mov r8w |
| rbp+0x1CA | 1 | W | mov byte 1 |
| rbp+0x1C8 | 8 | W | lea rdx |
| rbp+0x180 | 8 | W | lea r8 |
| r12 | 8 | W | mov rcx |
| 0x5679DB0 | 8 | W | call sub_5679db0 |
| rbp-0x10 | 8 | R | mov rax |
| rbp-6 | 2 | R | movzx ecx |
| rbp+0x220 | 8 | R | mov rsi |
| rsi+0x78 | 4 | R | movss xmm0 |
| rsi+0x88 | 4 | R | movd xmm1 |
| rbp+0x1E0 | 4 | W | movd xmm1 |
| rbp+0x1E4 | 4 | W | movss xmm0 |
| rsi+0xA4 | 4 | R | movd xmm0 |
| xmm1 | 16 | W | pxor |
| xmm0 | 16 | W | punpcklwd |
| xmm0 | 16 | W | cvtdq2ps |
| rbp+0x1E8 | 8 | W | movlps xmm0 |
| rbp+0x180 | 8 | W | mov qword 1 |
| rbp+0x188 | 8 | W | mov r14 |
| cx | 2 | R | movzx r9d |
| edx | 4 | W | mov r9d |
| edx | 4 | W | shl 4 |
| r8 | 8 | W | mov rax |
| r9w | 2 | R | test/je |
| [0x12ADF7B0] | 8 | R | mov r9 |
| r8d | 4 | W | xor |
| rax | 8 | R | mov r10 |
| r10+0x28 | 8 | R | cmp [r10+0x28] |
| r9 | 8 | R | cmp r9 |
| r8 | 4 | W | add 0x10 |
| rdx | 8 | R | cmp rdx |
| rax | 8 | W | add r8 |
| rdx | 8 | W | add rax |
| r8 | 8 | R | cmp/jae |
| r8d | 4 | W | sub eax/shr 4 |
| rbp+0x1C8 | 2 | W | mov r8w |
| rbp+0x1CA | 1 | W | mov byte 1 |
| rbp+0x1C8 | 8 | W | lea rdx |
| rbp+0x180 | 8 | W | lea r8 |
| r12 | 8 | W | mov rcx |
| 0x5679DB0 | 8 | W | call sub_5679db0 |
| rbp-0x10 | 8 | R | mov rax |
| rbp-6 | 2 | R | movzx ecx |
| edx | 4 | W | mov ecx |
| edx | 4 | W | shl 4 |
| rsi | 8 | W | mov rsi |
| r8d | 4 | W | mov 0x80000000 |
| r8d | 4 | W | xor [rsi+0x8C] |
| rsi+0x90 | 8 | R | movq xmm0 |
| rbp+0x1E0 | 8 | W | movq xmm0 |
| rbp+0x1E8 | 4 | W | mov r8d |
| rbp+0x1EC | 4 | W | mov dword 0 |
| rbp+0x180 | 8 | W | mov qword 1 |
| rbp+0x188 | 8 | W | mov r14 |
| rax | 8 | W | mov r8 |
| cx | 2 | R | test/je |
| [0x12ADF7C0] | 8 | R | mov r9 |
| r8d | 4 | W | xor |
| rax | 8 | R | mov r10 |
| r10+0x28 | 8 | R | cmp [r10+0x28] |
| r9 | 8 | R | cmp r9 |
| r8 | 4 | W | add 0x10 |
| rdx | 8 | R | cmp rdx |
| rax | 8 | W | add r8 |
| rax | 8 | W | add r8 |
| rdx | 8 | R | cmp/jae |
| rax | 8 | W | lea r9 |
| r8 | 8 | R | cmp/jae |
| r8d | 4 | W | sub eax/shr 4 |
| rbp+0x1C8 | 2 | W | mov r8w |
| rbp+0x1CA | 1 | W | mov byte 1 |
| rbp+0x1C8 | 8 | W | lea rdx |
| rbp+0x180 | 8 | W | lea r8 |
| r12 | 8 | W | mov rcx |
| 0x5679DB0 | 8 | W | call sub_5679db0 |
| rbp-0x10 | 8 | R | mov rax |
| rbp-6 | 2 | R | movzx ecx |
| edx | 4 | W | mov ecx |
| edx | 4 | W | shl 4 |
| rsi | 8 | W | mov rsi |
| rsi+0x6C | 8 | R | movq xmm0 |
| rbp+0x1E0 | 16 | W | movdqu xmm0 |
| rbp+0x180 | 8 | W | mov qword 1 |
| rbp+0x188 | 8 | W | mov r14 |
| rax | 8 | W | mov r8 |
| cx | 2 | R | test/je |
| [0x12ADF7D0] | 8 | R | mov r9 |

**Chunk 1 callees (in order):**
1. 0xEBCE390 (sub_ebce390) - called 5 times
2. qword ptr [0xF99FFA0] = sub_eea6040 - called multiple times (allocator/deallocator)
3. 0xBCC1A30 (sub_bcc1a30) - called once
4. 0xEEC5870 (sub_eec5870) - called once
5. 0x9BD2E0 (sub_9bd2e0) - called once
6. 0xE86B370 (sub_e86b370) - called once
7. 0x5679DB0 (sub_5679db0) - called multiple times

### Chunk 2: 0xbc5c289..0xbc5c8a4 (continuation - from actual rdis output)
```
0xbc5c289  mov r9,[0x12ADF7D0]                           ; [data_12adf7d0]
0xbc5c290  xor r8d,r8d                                   
0xbc5c293  nop [rax+rax]                                 

loc_bc5c2a0:  ; from bc5c2b1
0xbc5c2a0  mov r10,[rax+r8]                              
0xbc5c2a4  cmp [r10+0x28],r9                             
0xbc5c2a8  je short 0xBC5C2B9                            ; -> loc_bc5c2b9
0xbc5c2aa  add r8,0x10                                   
0xbc5c2ae  cmp rdx,r8                                    
0xbc5c2b1  jne short 0xBC5C2A0                           ; -> loc_bc5c2a0
0xbc5c2b3  mov cx,1                                      
0xbc5c2b7  jmp short 0xBC5C306                           ; -> loc_bc5c306

loc_bc5c2b9:  ; from bc5c2a8
0xbc5c2b9  add r8,rax                                    
0xbc5c2bc  lea r9,[rax+rdx]                              
0xbc5c2c0  cmp r8,r9                                     
0xbc5c2c3  jae short 0xBC5C306                           ; -> loc_bc5c306
0xbc5c2c5  sub r8d,eax                                   
0xbc5c2c8  shr r8d,4                                     
0xbc5c2cc  mov [rbp+0x1C8],r8w                           
0xbc5c2d4  mov byte ptr [rbp+0x1CA],1                    
0xbc5c2db  lea rdx,[rbp+0x1C8]                           
0xbc5c2e2  lea r8,[rbp+0x180]                            
0xbc5c2e9  mov rcx,r12                                   
0xbc5c2ec  call 0x5679DB0                                ; -> sub_5679db0
0xbc5c2f1  nop                                           
0xbc5c2f2  mov rax,[rbp-0x10]                            
0xbc5c2f6  movzx ecx,word ptr [rbp-6]                    
0xbc5c2fa  mov edx,ecx                                   
0xbc5c2fc  shl edx,4                                     
0xbc5c2ff  mov rsi,[rbp+0x220]                           

loc_bc5c306:  ; from bc5c2b7, bc5c2c3
0xbc5c306  divss xmm7,xmm6                               
0xbc5c30a  movss xmm0,[rsi+0x80]                         
0xbc5c312  movq xmm1,[rsi+0x7C]                          
0xbc5c317  movq [rbp+0x1E0],xmm1                         
0xbc5c31f  movss [rbp+0x1E8],xmm6                        
0xbc5c327  movss [rbp+0x1EC],xmm7                        
0xbc5c32f  mov qword ptr [rbp+0x180],1                   
0xbc5c33a  mov [rbp+0x188],r14                           
0xbc5c341  mov r8,rax                                    
0xbc5c344  test cx,cx                                    
0xbc5c347  je short 0xBC5C375                            ; -> loc_bc5c375
0xbc5c349  mov rcx,[0x12ADF7E0]                          ; [data_12adf7e0]
0xbc5c350  mov r9,rdx                                    
0xbc5c353  mov r8,rax                                    
0xbc5c356  nop [rax+rax]                                 

loc_bc5c360:  ; from bc5c371
0xbc5c360  mov r10,[r8]                                  
0xbc5c363  cmp [r10+0x28],rcx                            
0xbc5c367  je short 0xBC5C375                            ; -> loc_bc5c375
0xbc5c369  add r8,0x10                                   
0xbc5c36d  add r9,0xFFFFFFFFFFFFFFF0                     
0xbc5c371  jne short 0xBC5C360                           ; -> loc_bc5c360
0xbc5c373  jmp short 0xBC5C3B9                           ; -> loc_bc5c3b9

loc_bc5c375:  ; from bc5c347, bc5c367
0xbc5c375  add rdx,rax                                   
0xbc5c378  cmp r8,rdx                                    
0xbc5c37b  jae short 0xBC5C3B9                           ; -> loc_bc5c3b9
0xbc5c37d  sub r8d,eax                                   
0xbc5c380  shr r8d,4                                     
0xbc5c384  mov [rbp+0x1C8],r8w                           
0xbc5c38c  mov byte ptr [rbp+0x1CA],1                    
0xbc5c393  lea rdx,[rbp+0x1C8]                           
0xbc5c39a  lea r8,[rbp+0x180]                            
0xbc5c3a1  mov rcx,r12                                   
0xbc5c3a4  call 0x5679DB0                                ; -> sub_5679db0
0xbc5c3a9  nop                                           
0xbc5c3aa  mov rax,[rbp+0x220]                           
0xbc5c3b1  movss xmm0,[rax+0x80]                         

loc_bc5c3b9:  ; from bc5c373, bc5c37b
0xbc5c3b9  mov rsi,[0xF9A8ED0]                           ; [data_f9a8ed0]
0xbc5c3c0  call rsi                                      
0xbc5c3c2  movaps xmm6,xmm0                              
0xbc5c3c5  mov rax,[rbp+0x220]                           
0xbc5c3cc  movss xmm0,[rax+0x78]                         
0xbc5c3d1  call rsi                                      
0xbc5c3d3  movaps xmm7,xmm0                              
0xbc5c3d6  mov eax,[0x12ADF7F8]                          ; [data_12adf7f8]
0xbc5c3dc  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc5c3e2  mov rdx,gs:[0x58]                             
0xbc5c3eb  mov rcx,[rdx+rcx*8]                           
0xbc5c3ef  cmp eax,[rcx+4]                               
0xbc5c3f5  jg 0xBC5CF21                                  ; -> loc_bc5cf21

loc_bc5c3fb:  ; from bc5cf34, bc5d49c
0xbc5c3fb  movaps xmm0,xmm7                              
0xbc5c3fe  subss xmm0,xmm6                               
0xbc5c402  divss xmm8,xmm0                               
0xbc5c407  movss [rbp+0x1E0],xmm8                        
0xbc5c410  movss [rbp+0x1E4],xmm7                        
0xbc5c418  movss [rbp+0x1E8],xmm6                        
0xbc5c420  mov dword ptr [rbp+0x1EC],0                   
0xbc5c42a  mov qword ptr [rbp+0x180],1                   
0xbc5c435  mov [rbp+0x188],r14                           
0xbc5c43c  mov rax,[rbp-0x10]                            
0xbc5c440  movzx r8d,word ptr [rbp-6]                    
0xbc5c445  mov edx,r8d                                   
0xbc5c448  shl edx,4                                     
0xbc5c44b  mov rcx,rax                                   
0xbc5c44e  test r8d,r8d                                  
0xbc5c451  je short 0xBC5C475                            ; -> loc_bc5c475
0xbc5c453  mov r8,[0x12ADF7F0]                           ; [data_12adf7f0]
0xbc5c45a  mov r9,rdx                                    
0xbc5c45d  mov rcx,rax                                   

loc_bc5c460:  ; from bc5c471
0xbc5c460  mov r10,[rcx]                                 
0xbc5c463  cmp [r10+0x28],r8                             
0xbc5c467  je short 0xBC5C475                            ; -> loc_bc5c475
0xbc5c469  add rcx,0x10                                  
0xbc5c46d  add r9,0xFFFFFFFFFFFFFFF0                     
0xbc5c471  jne short 0xBC5C460                           ; -> loc_bc5c460
0xbc5c473  jmp short 0xBC5C4A7                           ; -> loc_bc5c4a7

loc_bc5c475:  ; from bc5c451, bc5c467
0xbc5c475  add rdx,rax                                   
0xbc5c478  cmp rcx,rdx                                   
0xbc5c47b  jae short 0xBC5C4A7                           ; -> loc_bc5c4a7
0xbc5c47d  sub ecx,eax                                   
0xbc5c47f  shr ecx,4                                     
0xbc5c482  mov [rbp+0x1C8],cx                            
0xbc5c489  mov byte ptr [rbp+0x1CA],1                    
0xbc5c490  lea rdx,[rbp+0x1C8]                           
0xbc5c497  lea r8,[rbp+0x180]                            
0xbc5c49e  mov rcx,r12                                   
0xbc5c4a1  call 0x5679DB0                                ; -> sub_5679db0
0xbc5c4a6  nop                                           

loc_bc5c4a7:  ; from bc5c473, bc5c47b
0xbc5c4a7  mov rax,[rbp+0x130]                           
0xbc5c4ae  mov rcx,[rbp+0x138]                           
0xbc5c4b5  cmp rcx,[rbp+0x140]                           
0xbc5c4bc  je short 0xBC5C4C5                            ; -> loc_bc5c4c5
0xbc5c4be  mov [rbp+0x140],rcx                           

loc_bc5c4c5:  ; from bc5c4bc
0xbc5c4c5  mov r12,[rax+0x20]                            
0xbc5c4c9  mov rax,[rbp+0x150]                           
0xbc5c4d0  cmp rax,[rbp+0x158]                           
0xbc5c4d7  je short 0xBC5C4E0                            ; -> loc_bc5c4e0
0xbc5c4d9  mov [rbp+0x158],rax                           

loc_bc5c4e0:  ; from bc5c4d7
0xbc5c4e0  mov r13,[rbp+0x168]                           
0xbc5c4e7  mov rsi,[rbp+0x170]                           
0xbc5c4ee  cmp r13,rsi                                   
0xbc5c4f1  je short 0xBC5C52A                            ; -> loc_bc5c52a
0xbc5c4f3  lea r14,[rbp+0x1E0]                           
0xbc5c4fa  nop [rax+rax]                                 

loc_bc5c500:  ; from bc5c51a
0xbc5c500  movsx rcx,byte ptr [r13+0x18]                 
0xbc5c505  inc rcx                                       
0xbc5c508  mov rdx,r14                                   
0xbc5c50b  mov r8,r13                                    
0xbc5c50e  call 0x568DB90                                ; -> sub_568db90
0xbc5c513  add r13,0x20                                  
0xbc5c517  cmp r13,rsi                                   
0xbc5c51a  jne short 0xBC5C500                           ; -> loc_bc5c500
0xbc5c51c  mov rax,[rbp+0x168]                           
0xbc5c523  mov [rbp+0x170],rax                           

loc_bc5c52a:  ; from bc5c4f1
0xbc5c52a  lea r8,[r12+0x38]                             
0xbc5c52f  add r12,0x28                                  
0xbc5c533  mov [rsp+0x28],r15                            
0xbc5c538  lea rax,[rbp-0x48]                            
0xbc5c53c  mov [rsp+0x20],rax                            
0xbc5c541  lea r9,[rbp+0x130]                            
0xbc5c548  xor ecx,ecx                                   
0xbc5c54a  mov rdx,r12                                   
0xbc5c54d  call 0xE86D7F0                                ; -> sub_e86d7f0
0xbc5c552  nop                                           
0xbc5c553  test al,al                                    
0xbc5c555  je 0xBC5CBBA                                  ; -> loc_bc5cbba
0xbc5c55b  lea rcx,[rbp+0x130]                           
0xbc5c562  call 0xBCC3190                                ; -> sub_bcc3190
0xbc5c567  nop                                           
0xbc5c568  mov rcx,[rbp+0x220]                           
0xbc5c56f  mov r14,[rcx+0x20]                            
0xbc5c573  shl r14,2                                     
0xbc5c577  mov rax,r14                                   
0xbc5c57a  shr rax,0x20                                  
0xbc5c57e  jne 0xBC5CFB7                                 ; -> loc_bc5cfb7
0xbc5c584  mov r15,[rcx+0x28]                            
0xbc5c588  test r15,r15                                  
0xbc5c58b  setne al                                      
0xbc5c58e  test r14,r14                                  
0xbc5c591  sete cl                                       
0xbc5c594  or cl,al                                      
0xbc5c596  je 0xBC5CCC5                                  ; -> loc_bc5ccc5
0xbc5c59c  mov rcx,[rbx+8]                               
0xbc5c5a0  mov rax,[rcx+0x50]                            
0xbc5c5a4  mov rcx,[rcx+0x58]                            
0xbc5c5a8  cmp rax,rcx                                   
0xbc5c5ab  je short 0xBC5C5DA                            ; -> loc_bc5c5da
0xbc5c5ad  mov rdx,[0x12ADF768]                          ; [data_12adf768]
0xbc5c5b4  nop [rax+rax]                                 

loc_bc5c5c0:  ; from bc5c5d6
0xbc5c5c0  cmp byte ptr [rax+0x28],0xFF                  
0xbc5c5c4  je 0xBC5CCDB                                  ; -> loc_bc5ccdb
0xbc5c5ca  cmp [rax],rdx                                 
0xbc5c5cd  je short 0xBC5C5DA                            ; -> loc_bc5c5da
0xbc5c5cf  add rax,0x30                                  
0xbc5c5d3  cmp rax,rcx                                   
0xbc5c5d6  jne short 0xBC5C5C0                           ; -> loc_bc5c5c0
0xbc5c5d8  jmp short 0xBC5C655                           ; -> loc_bc5c655

loc_bc5c5da:  ; from bc5c5ab, bc5c5cd
0xbc5c5da  cmp rax,rcx                                   
0xbc5c5dd  je short 0xBC5C655                            ; -> loc_bc5c655
0xbc5c5df  cmp byte ptr [rax+0x28],1                     
0xbc5c5e3  jne short 0xBC5C655                           ; -> loc_bc5c655
0xbc5c5e5  mov rax,[rax+8]                               
0xbc5c5e9  test rax,rax                                  
0xbc5c5ec  je short 0xBC5C655                            ; -> loc_bc5c655
0xbc5c5ee  test r14,r14                                  
0xbc5c5f1  je short 0xBC5C655                            ; -> loc_bc5c655
0xbc5c5f3  mov rsi,[rax+0x18]                            
0xbc5c5f7  test rsi,rsi                                  
0xbc5c5fa  je short 0xBC5C655                            ; -> loc_bc5c655
0xbc5c5fc  mov rcx,[0x12ADF800]                          ; [data_12adf800]
0xbc5c603  mov rax,[rcx]                                 
0xbc5c606  mov rax,[rax+8]                               
0xbc5c60a  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
0xbc5c611  mov dword ptr [rsp+0x28],0                    
0xbc5c619  mov qword ptr [rsp+0x20],0                    
0xbc5c622  mov r8d,0x20                                  
0xbc5c628  xor edx,edx                                   
0xbc5c62a  xor r9d,r9d                                   
0xbc5c62d  call r10                                      
0xbc5c630  nop                                           
0xbc5c631  mov [rax+8],r14d                              
0xbc5c635  mov [rax],r15                                 
0xbc5c638  xorps xmm0,xmm0                               
0xbc5c63b  movups [rax+0x10],xmm0                        
0xbc5c63f  movzx edx,word ptr [rsi]                      
0xbc5c642  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
0xbc5c649  xor r8d,r8d                                   
0xbc5c64c  mov r9,rax                                    
0xbc5c64f  call 0xBC70FF0                                ; -> sub_bc70ff0
0xbc5c654  nop                                           

loc_bc5c655:  ; from bc5c5d8, bc5c5dd, bc5c5e3, bc5c5ec, bc5c5f1, bc5c5fa
0xbc5c655  mov rcx,[rbp+0x220]                           
0xbc5c65c  mov r14,[rcx]                                 
0xbc5c65f  shl r14,7                                     
0xbc5c663  mov rax,r14                                   
0xbc5c666  shr rax,0x20                                  
0xbc5c66a  jne 0xBC5CFE3                                 ; -> loc_bc5cfe3
0xbc5c670  mov r15,[rcx+8]                               
0xbc5c674  test r15,r15                                  
0xbc5c677  setne al                                      
0xbc5c67a  test r14,r14                                  
0xbc5c67d  sete cl                                       
0xbc5c680  or cl,al                                      
0xbc5c682  je 0xBC5CCC5                                  ; -> loc_bc5ccc5
0xbc5c688  mov rcx,[rbx+8]                               
0xbc5c68c  mov rax,[rcx+0x50]                            
0xbc5c690  mov rcx,[rcx+0x58]                            
0xbc5c694  cmp rax,rcx                                   
0xbc5c697  je short 0xBC5C6BA                            ; -> loc_bc5c6ba
0xbc5c699  mov rdx,[0x12ADF748]                          ; [data_12adf748]

loc_bc5c6a0:  ; from bc5c6b6
0xbc5c6a0  cmp byte ptr [rax+0x28],0xFF                  
0xbc5c6a4  je 0xBC5CCE1                                  ; -> loc_bc5cce1
0xbc5c6aa  cmp [rax],rdx                                 
0xbc5c6ad  je short 0xBC5C6BA                            ; -> loc_bc5c6ba
0xbc5c6af  add rax,0x30                                  
0xbc5c6b3  cmp rax,rcx                                   
0xbc5c6b6  jne short 0xBC5C6A0                           ; -> loc_bc5c6a0
0xbc5c6b8  jmp short 0xBC5C735                           ; -> loc_bc5c735

loc_bc5c6ba:  ; from bc5c697, bc5c6ad
0xbc5c6ba  cmp rax,rcx                                   
0xbc5c6bd  je short 0xBC5C735                            ; -> loc_bc5c735
0xbc5c6bf  cmp byte ptr [rax+0x28],1                     
0xbc5c6c3  jne short 0xBC5C735                           ; -> loc_bc5c735
0xbc5c6c5  mov rax,[rax+8]                               
0xbc5c6c9  test rax,rax                                  
0xbc5c6cc  je short 0xBC5C735                            ; -> loc_bc5c735
0xbc5c6ce  test r14,r14                                  
0xbc5c6d1  je short 0xBC5C735                            ; -> loc_bc5c735
0xbc5c6d3  mov rsi,[rax+0x18]                            
0xbc5c6d7  test rsi,rsi                                  
0xbc5c6da  je short 0xBC5C735                            ; -> loc_bc5c735
0xbc5c6dc  mov rcx,[0x12ADF800]                          ; [data_12adf800]
0xbc5c6e3  mov rax,[rcx]                                 
0xbc5c6e6  mov rax,[rax+8]                               
0xbc5c6ea  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
0xbc5c6f1  mov dword ptr [rsp+0x28],0                    
0xbc5c6f9  mov qword ptr [rsp+0x20],0                    
0xbc5c702  mov r8d,0x20                                  
0xbc5c708  xor edx,edx                                   
0xbc5c70a  xor r9d,r9d                                   
0xbc5c70d  call r10                                      
0xbc5c710  nop                                           
0xbc5c711  mov [rax+8],r14d                              
0xbc5c715  mov [rax],r15                                 
0xbc5c718  xorps xmm0,xmm0                               
0xbc5c71b  movups [rax+0x10],xmm0                        
0xbc5c71f  movzx edx,word ptr [rsi]                      
0xbc5c722  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
0xbc5c729  xor r8d,r8d                                   
0xbc5c72c  mov r9,rax                                    
0xbc5c72f  call 0xBC70FF0                                ; -> sub_bc70ff0
0xbc5c734  nop                                           

loc_bc5c735:  ; from bc5c6b8, bc5c6bd, bc5c6c3, bc5c6cc, bc5c6d1, bc5c6da
0xbc5c735  mov rcx,[rbp+0x220]                           
0xbc5c73c  mov r14,[rcx+0x10]                            
0xbc5c740  shl r14,6                                     
0xbc5c744  mov rax,r14                                   
0xbc5c747  shr rax,0x20                                  
0xbc5c74b  jne 0xBC5D00F                                 ; -> loc_bc5d00f
0xbc5c751  mov r15,[rcx+0x18]                            
0xbc5c755  test r15,r15                                  
0xbc5c758  setne al                                      
0xbc5c75b  test r14,r14                                  
0xbc5c75e  sete cl                                       
0xbc5c761  or cl,al                                      
0xbc5c763  je 0xBC5CCC5                                  ; -> loc_bc5ccc5
0xbc5c769  mov rcx,[rbx+8]                               
0xbc5c76d  mov rax,[rcx+0x50]                            
0xbc5c771  mov rcx,[rcx+0x58]                            
0xbc5c775  cmp rax,rcx                                   
0xbc5c778  je short 0xBC5C7AA                            ; -> loc_bc5c7aa
0xbc5c77a  mov rdx,[0x12ADF758]                          ; [data_12adf758]
0xbc5c781  nop [rax+rax]                                 

loc_bc5c790:  ; from bc5c7a6
0xbc5c790  cmp byte ptr [rax+0x28],0xFF                  
0xbc5c794  je 0xBC5CCE7                                  ; -> loc_bc5cce7
0xbc5c79a  cmp [rax],rdx                                 
0xbc5c79d  je short 0xBC5C7AA                            ; -> loc_bc5c7aa
0xbc5c79f  add rax,0x30                                  
0xbc5c7a3  cmp rax,rcx                                   
0xbc5c7a6  jne short 0xBC5C790                           ; -> loc_bc5c790
0xbc5c7a8  jmp short 0xBC5C825                           ; -> loc_bc5c825

loc_bc5c7aa:  ; from bc5c778, bc5c79d
0xbc5c7aa  cmp rax,rcx                                   
0xbc5c7ad  je short 0xBC5C825                            ; -> loc_bc5c825
0xbc5c7af  cmp byte ptr [rax+0x28],1                     
0xbc5c7b3  jne short 0xBC5C825                           ; -> loc_bc5c825
0xbc5c7b5  mov rax,[rax+8]                               
0xbc5c7b9  test rax,rax                                  
0xbc5c7bc  je short 0xBC5C825                            ; -> loc_bc5c825
0xbc5c7be  test r14,r14                                  
0xbc5c7c1  je short 0xBC5C825                            ; -> loc_bc5c825
0xbc5c7c3  mov rsi,[rax+0x18]                            
0xbc5c7c7  test rsi,rsi                                  
0xbc5c7ca  je short 0xBC5C825                            ; -> loc_bc5c825
0xbc5c7cc  mov rcx,[0x12ADF800]                          ; [data_12adf800]
0xbc5c7d3  mov rax,[rcx]                                 
0xbc5c7d6  mov rax,[rax+8]                               
0xbc5c7da  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
0xbc5c7e1  mov dword ptr [rsp+0x28],0                    
0xbc5c7e9  mov qword ptr [rsp+0x20],0                    
0xbc5c7f2  mov r8d,0x20                                  
0xbc5c7f8  xor edx,edx                                   
0xbc5c7fa  xor r9d,r9d                                   
0xbc5c7fd  call r10                                      
0xbc5c800  nop                                           
0xbc5c801  mov [rax+8],r14d                              
0xbc5c805  mov [rax],r15                                 
0xbc5c808  xorps xmm0,xmm0                               
0xbc5c80b  movups [rax+0x10],xmm0                        
0xbc5c80f  movzx edx,word ptr [rsi]                      
0xbc5c812  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
0xbc5c819  xor r8d,r8d                                   
0xbc5c81c  mov r9,rax                                    
0xbc5c81f  call 0xBC70FF0                                ; -> sub_bc70ff0
0xbc5c824  nop                                           

loc_bc5c825:  ; from bc5c7a8, bc5c7ad, bc5c7b3, bc5c7bc, bc5c7c1, bc5c7ca
0xbc5c825  mov rsi,[rbp-0x48]                            
0xbc5c829  mov qword ptr [rbp+0x1F0],0                   
0xbc5c834  mov qword ptr [rbp+0x200],0xF                 
0xbc5c83f  mov qword ptr [rbp+0x208],0                   
0xbc5c84a  mov qword ptr [rbp+0x1F8],0xD                 
0xbc5c855  mov rax,0x4C72657473756C43                    
0xbc5c85f  mov [rbp+0x1E8],rax                           
0xbc5c866  mov rax,0x73746867694C7265                    
0xbc5c870  mov [rbp+0x1ED],rax                           
0xbc5c877  mov rax,0xAA53F452A8D4B31A                    
0xbc5c881  mov [rbp+0x1E0],rax                           
0xbc5c888  mov rdx,[rsi+0x2F8]                           
0xbc5c88f  mov r8,[rsi+0x300]                            
0xbc5c896  lea rcx,[rbp+0x180]                           
0xbc5c89d  lea r9,[rbp+0x1E0]                            
0xbc5c8a4  call 0xC4BBA0                                 ; -> sub_c4bba0
0xbc5c8a9  nop                                           
0xbc5c8aa  mov rcx,[rbp+0x180]                           
0xbc5c8b1  cmp rcx,[rbp+0x188]                           
0xbc5c8b8  je short 0xBC5C8EB                            ; -> loc_bc5c8eb
0xbc5c8ba  mov rdx,rcx                                   
0xbc5c8bd  sub rdx,[rsi+0x2F8]                           
0xbc5c8c4  mov rax,0xAAAAAAAAAAAAAAAB                    
0xbc5c8ce  imul rax,rdx                                  
0xbc5c8d2  add rax,[rsi+0x310]                           
0xbc5c8d9  cmp rcx,[rsi+0x300]                           
0xbc5c8e0  jne short 0xBC5C8F0                           ; -> loc_bc5c8f0
0xbc5c8e2  cmp rax,[rsi+0x318]                           
0xbc5c8e9  jne short 0xBC5C8F0                           ; -> loc_bc5c8f0

loc_bc5c8eb:  ; from bc5c8b8
0xbc5c8eb  xor r15d,r15d                                 
0xbc5c8ee  jmp short 0xBC5C8F3                           ; -> loc_bc5c8f3

loc_bc5c8f0:  ; from bc5c8e0, bc5c8e9
0xbc5c8f0  mov r15,[rax]                                 

loc_bc5c8f3:  ; from bc5c8ee
0xbc5c8f3  mov rax,[rbp+0x200]                           
0xbc5c8fa  cmp rax,0x10                                  
0xbc5c8fe  jb short 0xBC5C938                            ; -> loc_bc5c938
0xbc5c900  mov rcx,[rbp+0x1E8]                           
0xbc5c907  lea rdx,[rax+1]                               
0xbc5c90b  cmp rdx,0x1000                                
0xbc5c912  jb short 0xBC5C933                            ; -> loc_bc5c933
0xbc5c914  mov r8,[rcx-8]                                
0xbc5c918  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc5c91c  sub rcx,r8                                    
0xbc5c91f  cmp rcx,0x20                                  
0xbc5c923  jae 0xBC5CF9E                                 ; -> loc_bc5cf9e
0xbc5c929  add rax,0x28                                  
0xbc5c92d  mov rdx,rax                                   
0xbc5c930  mov rcx,r8                                    

loc_bc5c933:  ; from bc5c912
0xbc5c933  call 0xE935700                                ; -> sub_e935700

loc_bc5c938:  ; from bc5c8fe
0xbc5c938  test r15,r15                                  
0xbc5c93b  je 0xBC5CBBA                                  ; -> loc_bc5cbba
0xbc5c941  mov rsi,[rbp+0x220]                           
0xbc5c948  movss xmm0,[rsi+0x58]                         
0xbc5c94d  divss xmm0,[rsi+0x64]                         
0xbc5c952  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc5c957  movaps xmm6,xmm0                              
0xbc5c95a  movss xmm8,[rsi+0x50]                         
0xbc5c960  movss xmm0,[rsi+0x54]                         
0xbc5c965  divss xmm0,[rsi+0x60]                         
0xbc5c96a  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc5c96f  movaps xmm7,xmm0                              
0xbc5c972  divss xmm8,[rsi+0x5C]                         
```

**Chunk 2 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| [0x12ADF7D0] | 8 | R | mov r9 |
| r8d | 4 | W | xor |
| rax+r8 | 8 | R | mov r10 |
| r10+0x28 | 8 | R | cmp r9 |
| r8 | 4 | W | add 0x10 |
| rdx | 8 | R | cmp r8 |
| cx | 2 | W | mov 1 |
| r8 | 8 | R/W | add rax/lea r9/cmp |
| r8d | 4 | W | sub eax/shr 4 |
| rbp+0x1C8 | 2 | W | mov r8w |
| rbp+0x1CA | 1 | W | mov byte 1 |
| rbp+0x1C8 | 8 | W | lea rdx |
| rbp+0x180 | 8 | W | lea r8 |
| r12 | 8 | W | mov rcx |
| 0x5679DB0 | 8 | W | call sub_5679db0 |
| rbp-0x10 | 8 | R | mov rax |
| rbp-6 | 2 | R | movzx ecx |
| edx | 4 | W | mov ecx/shl 4 |
| rsi | 8 | W | mov [rbp+0x220] |
| xmm7/xmm6 | 4 | R | divss |
| rsi+0x80/0x7C | 4/8 | R | movss/movq |
| rbp+0x1E0/0x1E8/0x1EC | 8/4/4 | W | movq/movss |
| rbp+0x180 | 8 | W | mov qword 1 |
| rbp+0x188 | 8 | W | mov r14 |
| rax | 8 | W | mov r8 |
| cx | 2 | R | test/je |
| [0x12ADF7E0] | 8 | R | mov rcx |
| rdx/rax | 8 | W | mov r9/r8 |
| r8 | 8 | R | mov r10 |
| r10+0x28 | 8 | R | cmp rcx |
| r8 | 4 | W | add 0x10 |
| r9 | 8 | R/W | add/mov |
| rdx/rax | 8 | R/W | add/cmp/sub/shr |
| rbp+0x1C8 | 2/1 | W | mov cx/mov byte 1 |
| rbp+0x1C8/0x180 | 8 | W | lea rdx/lea r8 |
| r12 | 8 | W | mov rcx |
| 0x5679DB0 | 8 | W | call sub_5679db0 (3x) |
| [0xF9A8ED0] | 8 | R | mov rsi |
| rsi | 8 | W | call (indirect) |
| xmm6 | 16 | W | movaps xmm0 |
| rbp+0x220 | 8 | R | mov rax |
| rax+0x78 | 4 | R | movss xmm0 |
| rsi | 8 | W | call (indirect) |
| xmm7 | 16 | W | movaps xmm0 |
| [0x12ADF7F8] | 4 | R | mov eax |
| [0x128767C8] | 4 | R | mov ecx |
| gs:[0x58] | 8 | R | mov rdx |
| rdx+rcx*8 | 8 | R | mov rcx |
| rcx+4 | 4 | R | cmp eax |
| xmm0/xmm7/xmm6/xmm8 | 4 | R/W | movaps/subss/divss/movss |
| rbp+0x1E0/0x1E4/0x1E8/0x1EC | 4/4/4/4 | W | movss/mov dword |
| rbp+0x180 | 8 | W | mov qword 1 |
| rbp+0x188 | 8 | W | mov r14 |
| rbp-0x10 | 8 | R | mov rax |
| rbp-6 | 2 | R | movzx r8d |
| edx | 4 | W | mov r8d/shl 4 |
| rcx | 8 | W | mov rax |
| r8d | 4 | R | test/je |
| [0x12ADF7F0] | 8 | R | mov r8 |
| rdx/rax | 8 | W | mov r9/rcx |
| rcx | 8 | R | mov r10 |
| r10+0x28 | 8 | R | cmp r8 |
| rcx | 4 | W | add 0x10 |
| r9 | 8 | R/W | add/mov |
| rcx/rdx | 8 | R/W | add/cmp/sub/shr |
| rbp+0x1C8 | 2/1 | W | mov cx/mov byte 1 |
| rbp+0x1C8/0x180 | 8 | W | lea rdx/lea r8 |
| r12 | 8 | W | mov rcx |
| 0x5679DB0 | 8 | W | call sub_5679db0 |
| rbp+0x130/0x138/0x140/0x150/0x158/0x168/0x170 | 8 | R/W | mov/cmp/mov |
| rax+0x20 | 8 | R | mov r12 |
| r13/rsi | 8 | R | mov/cmp/je |
| r14 | 8 | W | lea |
| r13+0x18 | 1 | R | movsx rcx |
| rcx | 8 | W | inc |
| r14/r13 | 8 | W | mov rdx/r8 |
| 0x568DB90 | 8 | W | call sub_568db90 |
| r13 | 8 | W | add 0x20 |
| r13/rsi | 8 | R | cmp/jne |
| rbp+0x168 | 8 | R | mov rax |
| rbp+0x170 | 8 | W | mov rax |
| r12+0x38 | 8 | W | lea r8 |
| r12 | 8 | W | add 0x28 |
| rsp+0x28/0x20 | 8 | W | mov r15/lea rax |
| rbp+0x130 | 8 | W | lea r9 |
| ecx | 4 | W | xor |
| r12 | 8 | W | mov rdx |
| 0xE86D7F0 | 8 | W | call sub_e86d7f0 |
| al | 1 | R | test/je |
| rbp+0x130 | 8 | R | lea rcx |
| 0xBCC3190 | 8 | W | call sub_bcc3190 |
| rbp+0x220 | 8 | R | mov rcx |
| rcx+0x20 | 8 | R | mov r14 |
| r14 | 8 | W | shl 2 |
| rax | 8 | R/W | mov/shr/jne |
| rcx+0x28 | 8 | R | mov r15 |
| r15/r14 | 1 | R | test/setne/sete/or/je |
| rbx+8 | 8 | R | mov rcx |
| rcx+0x50/0x58 | 8 | R | mov rax/rcx |
| rax/rcx | 8 | R | cmp/je |
| [0x12ADF768] | 8 | R | mov rdx |
| rax+0x28 | 1 | R | cmp byte 0xFF/1/je |
| rax | 8 | R | cmp [rax] |
| rax | 8 | W | add 0x30/cmp/jne |
| rcx | 8 | R | cmp rax |
| rsi | 8 | W | mov [rax+0x18] |
| [0x12ADF800] | 8 | R | mov rcx |
| [rcx] | 8 | R | mov rax |
| [rax+8] | 8 | R | mov rax |
| [0xF99FFA0] | 8 | R | mov r10 |
| rsp+0x28/0x20 | 4/8 | W | mov dword/qword 0 |
| r8d | 4 | W | mov 0x20 |
| edx/r9d | 4 | W | xor |
| r10 | 8 | W | call (indirect) |
| rax+8/rax | 8/8 | W | mov r14d/mov r15 |
| xmm0 | 16 | W | xorps/movups |
| rsi | 2 | R | movzx edx |
| [0x12AE1748] | 8 | R | mov rcx |
| r8d/r9 | 4/8 | W | xor/mov rax |
| 0xBC70FF0 | 8 | W | call sub_bc70ff0 (2x) |
| rbp+0x220 | 8 | R | mov rcx |
| rcx | 8 | R | mov r14 |
| r14 | 8 | W | shl 7/6 |
| rax | 8 | R/W | mov/shr/jne |
| rcx+8/0x18 | 8 | R | mov r15/test/setne/sete/or/je |
| rbx+8 | 8 | R | mov rcx |
| rcx+0x50/0x58 | 8 | R | mov rax/rcx |
| rax/rcx | 8 | R | cmp/je |
| [0x12ADF748/0x12ADF758] | 8 | R | mov rdx |
| rax+0x28 | 1 | R | cmp byte 0xFF/1/je |
| rax | 8 | R | cmp [rax] |
| rax | 8 | W | add 0x30/cmp/jne |
| rcx | 8 | R | cmp rax |
| rsi | 8 | W | mov [rax+0x18] |
| rsi+0x18 | 8 | R | mov rsi |
| [0x12ADF800] | 8 | R | mov rcx (2x) |
| rbp-0x48 | 8 | R | mov rsi |
| rbp+0x1F0/0x200/0x208/0x1F8 | 8/8/8/8 | W | mov qword |
| rax | 8 | W | mov constant |
| rbp+0x1E8/0x1ED/0x1E0 | 8/8/8 | W | mov constant |
| rsi+0x2F8/0x300 | 8 | R | mov rdx/r8 |
| rbp+0x180/0x1E0 | 8 | W | lea rcx/lea r9 |
| 0xC4BBA0 | 8 | W | call sub_c4bba0 |
| rbp+0x180/0x188 | 8 | R | mov/cmp/je |
| rcx | 8 | W | mov rdx |
| rdx | 8 | R | sub [rsi+0x2F8] |
| rax | 8 | W | mov constant |
| rdx | 8 | R | imul rax |
| rax | 8 | R | add [rsi+0x310] |
| rcx | 8 | R | cmp [rsi+0x300] |
| rax | 8 | R | cmp [rsi+0x318] |
| r15d | 4 | W | xor/jmp |
| rax | 8 | R | mov r15 |
| rbp+0x200 | 8 | R | mov rax |
| rax | 4 | R | cmp 0x10/jb |
| rbp+0x1E8 | 8 | R | mov rcx |
| rax | 8 | W | lea rdx |
| rdx | 4 | R | cmp 0x1000/jb |
| rcx-8 | 8 | R | mov r8 |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20/jae |
| rax | 8 | W | add 0x28/mov rdx/mov rcx |
| 0xE935700 | 8 | W | call sub_e935700 |
| r15 | 8 | R | test/je |
| rbp+0x220 | 8 | R | mov rsi |
| rsi+0x58/0x64/0x50/0x54/0x60/0x5C | 4 | R | movss/divss |
| 0xEEC73F0 | 8 | W | call sub_eec73f0 (2x) |
| xmm6/xmm7/xmm8 | 16/16/4 | W | movaps/divss |

**Chunk 2 callees (in order):**
1. 0x5679DB0 (sub_5679db0) - called multiple times
2. [0xF9A8ED0] - indirect call
3. 0x5679DB0 (sub_5679db0) - called again
4. 0x568DB90 (sub_568db90) - called once
5. 0xE86D7F0 (sub_e86d7f0) - called once
5. 0xBCC3190 (sub_bcc3190) - called once
6. 0xBC70FF0 (sub_bc70ff0) - called twice
7. 0xC4BBA0 (sub_c4bba0) - called once
8. 0xE935700 (sub_e935700) - called once
9. 0xEEC73F0 (sub_eec73f0) - called twice

### Chunk 3: 0xbc5c972..0xbc5d0f1 (continuation - from actual rdis output)
```
0xbc5c972  divss xmm8,[rsi+0x5C]                         
0xbc5c978  movaps xmm0,xmm8                              
0xbc5c97c  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc5c981  movaps xmm8,xmm0                              
0xbc5c985  lea rax,[0xF598D3A]                           ; [data_f598d3a]
0xbc5c98c  cmp byte ptr [rsi+0x84],0                     
0xbc5c993  lea rcx,[0xF5BAC48]                           ; [data_f5bac48]
0xbc5c99a  cmovne rcx,rax                                
0xbc5c99e  mov [rbp+0x128],rcx                           
0xbc5c9a5  lea rdx,[0xF5369E5]                           ; [data_f5369e5] "AngularRefinement"
0xbc5c9ac  lea rcx,[rbp+0x180]                           
0xbc5c9b3  lea r8,[rbp+0x128]                            
0xbc5c9ba  call 0x56D8E00                                ; -> sub_56d8e00
0xbc5c9bf  nop                                           
0xbc5c9c0  mov dword ptr [rbp+0x1C8],0                   
0xbc5c9ca  lea rcx,[rbp+0x1E0]                           
0xbc5c9d1  lea rdx,[rbp+0x1C8]                           
0xbc5c9d8  lea r8,[rbp+0x1C7]                            
0xbc5c9df  call 0x9B020                                  ; -> sub_9b020
0xbc5c9e4  nop                                           
0xbc5c9e5  lea rcx,[rbp+0x1E0]                           
0xbc5c9ec  lea rdx,[rbp+0x1C8]                           
0xbc5c9f3  lea r8,[rbp+0x180]                            
0xbc5c9fa  call 0xAA840                                  ; -> sub_aa840
0xbc5c9ff  nop                                           
0xbc5ca00  mov rax,[rbx+8]                               
0xbc5ca04  mov si,[rax+8]                                
0xbc5ca08  lea rdx,[rbp+0x1C8]                           
0xbc5ca0f  lea r8,[rbp+0x1E0]                            
0xbc5ca16  mov rcx,r15                                   
0xbc5ca19  call 0xBCC7CE0                                ; -> sub_bcc7ce0
0xbc5ca1e  nop                                           
0xbc5ca1f  cmp byte ptr [rbp+0x1D8],1                    
0xbc5ca26  jne short 0xBC5CA6A                           ; -> loc_bc5ca6a
0xbc5ca28  cmp byte ptr [rbp+0x1CA],0                    
0xbc5ca2f  je short 0xBC5CA6A                            ; -> loc_bc5ca6a
0xbc5ca31  movzx r8d,word ptr [rbp+0x1C8]                
0xbc5ca39  cmp r8w,0xFFFF                                
0xbc5ca3e  je short 0xBC5CA6A                            ; -> loc_bc5ca6a
0xbc5ca40  cvttss2si r9,xmm8                             
0xbc5ca45  cvttss2si rax,xmm7                            
0xbc5ca4a  cvttss2si rdx,xmm6                            
0xbc5ca4f  mov rcx,[rbp+0x130]                           
0xbc5ca56  mov rcx,[rcx+0x10]                            
0xbc5ca5a  mov [rsp+0x28],edx                            
0xbc5ca5e  mov [rsp+0x20],eax                            
0xbc5ca62  mov edx,esi                                   
0xbc5ca64  call 0xBC61140                                ; -> sub_bc61140
0xbc5ca69  nop                                           

loc_bc5ca6a:  ; from bc5ca26, bc5ca2f, bc5ca3e
0xbc5ca6a  mov rcx,[rbp+0x1F8]                           
0xbc5ca71  test rcx,rcx                                  
0xbc5ca74  je short 0xBC5CABF                            ; -> loc_bc5cabf
0xbc5ca76  mov rdx,[rbp+0x208]                           
0xbc5ca7d  sub rdx,rcx                                   
0xbc5ca80  cmp rdx,0x1000                                
0xbc5ca87  jb short 0xBC5CAA5                            ; -> loc_bc5caa5
0xbc5ca89  mov rax,[rcx-8]                               
0xbc5ca8d  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc5ca91  sub rcx,rax                                   
0xbc5ca94  cmp rcx,0x20                                  
0xbc5ca98  jae 0xBC5CF9E                                 ; -> loc_bc5cf9e
0xbc5ca9e  add rdx,0x27                                  
0xbc5caa2  mov rcx,rax                                   

loc_bc5caa5:  ; from bc5ca87
0xbc5caa5  lea rsi,[rbp+0x1F8]                           
0xbc5caac  call 0xE935700                                ; -> sub_e935700
0xbc5cab1  xorps xmm0,xmm0                               
0xbc5cab4  movups [rsi],xmm0                             
0xbc5cab7  mov qword ptr [rsi+0x10],0                    

loc_bc5cabf:  ; from bc5ca74
0xbc5cabf  mov rax,[rbp+0x1E8]                           
0xbc5cac6  mov rcx,[rax+8]                               
0xbc5caca  mov qword ptr [rcx],0                         
0xbc5cad1  mov rsi,[rax]                                 
0xbc5cad4  test rsi,rsi                                  
0xbc5cad7  je short 0xBC5CB01                            ; -> loc_bc5cb01
0xbc5cad9  nop [rax]                                     

loc_bc5cae0:  ; from bc5caff
0xbc5cae0  mov rbx,[rsi]                                 
0xbc5cae3  lea rcx,[rsi+0x10]                            
0xbc5cae7  call 0x9B250                                  ; -> sub_9b250
0xbc5caec  mov edx,0x50                                  
0xbc5caf1  mov rcx,rsi                                   
0xbc5caf4  call 0xE935700                                ; -> sub_e935700
0xbc5caf9  mov rsi,rbx                                   
0xbc5cafc  test rbx,rbx                                  
0xbc5caff  jne short 0xBC5CAE0                           ; -> loc_bc5cae0

loc_bc5cb01:  ; from bc5cad7
0xbc5cb01  mov rcx,[rbp+0x1E8]                           
0xbc5cb08  mov edx,0x50                                  
0xbc5cb0d  call 0xE935700                                ; -> sub_e935700
0xbc5cb12  mov rax,[rbp+0x1B8]                           
0xbc5cb19  cmp rax,0x10                                  
0xbc5cb1d  jb short 0xBC5CB57                            ; -> loc_bc5cb57
0xbc5cb1f  mov rcx,[rbp+0x1A0]                           
0xbc5cb26  lea rdx,[rax+1]                               
0xbc5cb2a  cmp rdx,0x1000                                
0xbc5cb31  jb short 0xBC5CB52                            ; -> loc_bc5cb52
0xbc5cb33  mov r8,[rcx-8]                                
0xbc5cb37  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc5cb3b  sub rcx,r8                                    
0xbc5cb3e  cmp rcx,0x20                                  
0xbc5cb42  jae 0xBC5CF9E                                 ; -> loc_bc5cf9e
0xbc5cb48  add rax,0x28                                  
0xbc5cb4c  mov rdx,rax                                   
0xbc5cb4f  mov rcx,r8                                    

loc_bc5cb52:  ; from bc5cb31
0xbc5cb52  call 0xE935700                                ; -> sub_e935700

loc_bc5cb57:  ; from bc5cb1d
0xbc5cb57  mov qword ptr [rbp+0x1B0],0                   
0xbc5cb62  mov qword ptr [rbp+0x1B8],0xF                 
0xbc5cb6d  mov byte ptr [rbp+0x1A0],0                    
0xbc5cb74  mov rax,[rbp+0x198]                           
0xbc5cb7b  cmp rax,0x10                                  
0xbc5cb7f  jb short 0xBC5CBBA                            ; -> loc_bc5cbba
0xbc5cb81  mov rcx,[rbp+0x180]                           
0xbc5cb88  lea rdx,[rax+1]                               
0xbc5cb8c  cmp rdx,0x1000                                
0xbc5cb93  jb short 0xBC5CBB4                            ; -> loc_bc5cbb4
0xbc5cb95  mov r8,[rcx-8]                                
0xbc5cb99  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc5cb9d  sub rcx,r8                                    
0xbc5cba0  cmp rcx,0x20                                  
0xbc5cba4  jae 0xBC5CF9E                                 ; -> loc_bc5cf9e
0xbc5cbaa  add rax,0x28                                  
0xbc5cbae  mov rdx,rax                                   
0xbc5cbb1  mov rcx,r8                                    

loc_bc5cbb4:  ; from bc5cb93
0xbc5cbb4  call 0xE935700                                ; -> sub_e935700
0xbc5cbb9  nop                                           

loc_bc5cbba:  ; from bc5cb7f
0xbc5cbba  lea rbx,[rbp+0x80]                            
0xbc5cbc1  mov rcx,rbx                                   
0xbc5cbc4  call 0x56D5810                                ; -> sub_56d5810
0xbc5cbc9  nop                                           
0xbc5cbca  lea rcx,[rbp+0x120]                           
0xbc5cbd1  call 0x9BD3C0                                 ; -> sub_9bd3c0
0xbc5cbd6  nop [rax+rax]                                 ; R ret@9bd3c0+0x0+idx

loc_bc5cbe0:  ; from bc5cc01
0xbc5cbe0  mov rax,[rbp+0xC0]                            
0xbc5cbe7  cmp rax,rdi                                   
0xbc5cbea  je short 0xBC5CC03                            ; -> loc_bc5cc03
0xbc5cbec  mov rcx,[rax]                                 
0xbc5cbef  mov rdx,[rax+8]                               
0xbc5cbf3  mov [rdx],rcx                                 
0xbc5cbf6  mov [rcx+8],rdx                               
0xbc5cbfa  mov [rax],rax                                 
0xbc5cbfd  mov [rax+8],rax                               
0xbc5cc01  jmp short 0xBC5CBE0                           ; -> loc_bc5cbe0

loc_bc5cc03:  ; from bc5cbea
0xbc5cc03  cmp rax,rdi                                   
0xbc5cc06  je short 0xBC5CC24                            ; -> loc_bc5cc24
0xbc5cc08  mov rcx,[rbp+0xC8]                            
0xbc5cc0f  mov [rcx],rax                                 
0xbc5cc12  mov [rax+8],rcx                               
0xbc5cc16  mov [rbp+0xC0],rdi                            
0xbc5cc1d  mov [rbp+0xC8],rdi                            

loc_bc5cc24:  ; from bc5cc06
0xbc5cc24  lea rsi,[rbp+0x150]                           
0xbc5cc2b  mov rcx,[rbp+0xB8]                            
0xbc5cc32  test rcx,rcx                                  
0xbc5cc35  je short 0xBC5CC4A                            ; -> loc_bc5cc4a
0xbc5cc37  cmp rcx,rbx                                   
0xbc5cc3a  setne dl                                      
0xbc5cc3d  mov rax,[rcx]                                 
0xbc5cc40  mov rax,[rax+0x20]                            
0xbc5cc44  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc5cc4a:  ; from bc5cc35
0xbc5cc4a  lea rcx,[rbp+0x40]                            
0xbc5cc4e  call 0x655CEA0                                ; -> sub_655cea0
0xbc5cc53  mov rcx,rsi                                   
0xbc5cc56  call 0x568DA90                                ; -> sub_568da90
0xbc5cc5b  mov rcx,[rbp+0x138]                           
0xbc5cc62  test rcx,rcx                                  
0xbc5cc65  je short 0xBC5CC9B                            ; -> loc_bc5cc9b
0xbc5cc67  mov rdx,[rbp+0x148]                           
0xbc5cc6e  sub rdx,rcx                                   
0xbc5cc71  cmp rdx,0x1000                                
0xbc5cc78  jb short 0xBC5CC96                            ; -> loc_bc5cc96
0xbc5cc7a  mov rax,[rcx-8]                               
0xbc5cc7e  add rcx,0xFFFFFFFFFFFFFFF8                    
0xbc5cc82  sub rcx,rax                                   
0xbc5cc85  cmp rcx,0x20                                  
0xbc5cc89  jae 0xBC5CF9E                                 ; -> loc_bc5cf9e
0xbc5cc8f  add rdx,0x27                                  
0xbc5cc93  mov rcx,rax                                   

loc_bc5cc96:  ; from bc5cc78
0xbc5cc96  call 0xE935700                                ; -> sub_e935700

loc_bc5cc9b:  ; from bc5cc65
0xbc5cc9b  movaps xmm6,[rbp+0x230]                       
0xbc5cca2  movaps xmm7,[rbp+0x240]                       
0xbc5cca9  movaps xmm8,[rbp+0x250]                       
0xbc5ccb1  add rsp,0x2E8                                 
0xbc5ccb8  pop rbx                                       
0xbc5ccb9  pop rdi                                       
0xbc5ccba  pop rsi                                       
0xbc5ccbb  pop r12                                       
0xbc5ccbd  pop r13                                       
0xbc5ccbf  pop r14                                       
0xbc5ccc1  pop r15                                       
0xbc5ccc3  pop rbp                                       
0xbc5ccc4  ret                                           
0xbc5ccc5  call 0x78ED0                                  ; -> sub_78ed0
0xbc5ccca  nop                                           
0xbc5cccb  mov ecx,0x30                                  
0xbc5ccd0  call 0x9BC830                                 ; -> sub_9bc830
0xbc5ccd5  nop                                           
0xbc5ccd6  jmp 0xBC5BC7C                                 ; -> sub_bc5bc7c
0xbc5ccdb  call 0xB432E0                                 ; -> sub_b432e0
0xbc5cce0  nop                                           
0xbc5cce1  call 0xB432E0                                 ; -> sub_b432e0
0xbc5cce6  nop                                           
0xbc5cce7  call 0xB432E0                                 ; -> sub_b432e0
0xbc5ccec  nop                                           
0xbc5cced  lea rcx,[0x12ADF7A8]                          ; [data_12adf7a8]
0xbc5ccf4  call 0xE938CB0                                ; -> sub_e938cb0
0xbc5ccf9  cmp dword ptr [0x12ADF7A8],0xFFFFFFFF         ; [data_12adf7a8]
0xbc5cd00  jne 0xBC5BD02                                 ; -> sub_bc5bd02
0xbc5cd06  lea rdx,[0xF566EB0]                           ; [data_f566eb0] "LightsPerCluster"
0xbc5cd0d  lea rdi,[rbp+0x78]                            
0xbc5cd11  mov rcx,rdi                                   
0xbc5cd14  call 0x79580                                  ; -> sub_79580
0xbc5cd19  nop                                           
0xbc5cd1a  mov rdx,[rbp+0x88]                            
0xbc5cd21  cmp qword ptr [rbp+0x90],0x10                 
0xbc5cd29  jb short 0xBC5CD2F                            ; -> loc_bc5cd2f
0xbc5cd2b  mov rdi,[rbp+0x78]                            

loc_bc5cd2f:  ; from bc5cd29
0xbc5cd2f  test rdx,rdx                                  
0xbc5cd32  je 0xBC5D03B                                  ; -> loc_bc5d03b
0xbc5cd38  mov eax,edx                                   
0xbc5cd3a  and eax,3                                     
0xbc5cd3d  cmp rdx,4                                     
0xbc5cd41  jae 0xBC5D095                                 ; -> loc_bc5d095
0xbc5cd47  mov rcx,0xCBF29CE484222325                    
0xbc5cd51  xor r8d,r8d                                   
0xbc5cd54  jmp 0xBC5D0F1                                 ; -> loc_bc5d0f1
0xbc5cd59  lea rcx,[0x12ADF7B8]                          ; [data_12adf7b8]
0xbc5cd60  call 0xE938CB0                                ; -> sub_e938cb0
0xbc5cd65  cmp dword ptr [0x12ADF7B8],0xFFFFFFFF         ; [data_12adf7b8]
0xbc5cd6c  jne 0xBC5BEA6                                 ; -> sub_bc5bea6
0xbc5cd72  lea rdx,[0xF53B2F9]                           ; [data_f53b2f9] "ClusterNearFarWidthHeight"
0xbc5cd79  lea r13,[rbp+0x1E0]                           
0xbc5cd80  mov rcx,r13                                   
0xbc5cd83  call 0x79580                                  ; -> sub_79580
0xbc5cd88  nop                                           
0xbc5cd89  mov rdx,[rbp+0x1F0]                           
0xbc5cd90  cmp qword ptr [rbp+0x1F8],0x10                
0xbc5cd98  jb short 0xBC5CDA1                            ; -> loc_bc5cda1
0xbc5cd9a  mov r13,[rbp+0x1E0]                           

loc_bc5cda1:  ; from bc5cd98
0xbc5cda1  test rdx,rdx                                  
0xbc5cda4  je 0xBC5D04A                                  ; -> loc_bc5d04a
0xbc5cdaa  mov eax,edx                                   
0xbc5cdac  and eax,3                                     
0xbc5cdb3  jae 0xBC5D141                                 ; -> loc_bc5d141
0xbc5cdb9  mov rcx,0xCBF29CE484222325                    
0xbc5cdc3  xor r8d,r8d                                   
0xbc5cdc6  jmp 0xBC5D19E                                 ; -> loc_bc5d19e
0xbc5cdcb  lea rcx,[0x12ADF7C8]                          ; [data_12adf7c8]
0xbc5cdd2  call 0xE938CB0                                ; -> sub_e938cb0
0xbc5cdd7  cmp dword ptr [0x12ADF7C8],0xFFFFFFFF         ; [data_12adf7c8]
0xbc5cdde  jne 0xBC5BECB                                 ; -> sub_bc5becb
0xbc5cde4  lea rdx,[0xF5CEDF3]                           ; [data_f5cedf3] "CameraFarPlane"
0xbc5cdeb  lea r13,[rbp+0x1E0]                           
0xbc5cdf2  mov rcx,r13                                   
0xbc5cdf5  call 0x79580                                  ; -> sub_79580
0xbc5cdfa  nop                                           
0xbc5cdfb  mov rdx,[rbp+0x1F0]                           
0xbc5ce02  cmp qword ptr [rbp+0x1F8],0x10                
0xbc5ce0a  jb short 0xBC5CE13                            ; -> loc_bc5ce13
0xbc5ce0c  mov r13,[rbp+0x1E0]                           

loc_bc5ce13:  ; from bc5ce0a
0xbc5ce13  test rdx,rdx                                  
0xbc5ce16  je 0xBC5D059                                  ; -> loc_bc5d059
0xbc5ce1c  mov eax,edx                                   
0xbc5ce1e  and eax,3                                     
0xbc5ce21  cmp rdx,4                                     
0xbc5ce25  jae 0xBC5D1F3                                 ; -> loc_bc5d1f3
0xbc5ce2b  mov rcx,0xCBF29CE484222325                    
0xbc5ce35  xor r8d,r8d                                   
0xbc5ce38  jmp 0xBC5D250                                 ; -> loc_bc5d250
0xbc5ce3d  lea rcx,[0x12ADF7D8]                          ; [data_12adf7d8]
0xbc5ce44  call 0xE938CB0                                ; -> sub_e938cb0
0xbc5ce49  cmp dword ptr [0x12ADF7D8],0xFFFFFFFF         ; [data_12adf7d8]
0xbc5ce50  jne 0xBC5BEF0                                 ; -> sub_bc5bef0
0xbc5ce56  lea rdx,[0xF5BBF34]                           ; [data_f5bbf34] "ClusterSize"
0xbc5ce5d  lea r13,[rbp+0x1E0]                           
0xbc5ce64  mov rcx,r13                                   
0xbc5ce67  call 0x79580                                  ; -> sub_79580
0xbc5ce6c  nop                                           
0xbc5ce6d  mov rdx,[rbp+0x1F0]                           
0xbc5ce74  cmp qword ptr [rbp+0x1F8],0x10                
0xbc5ce7c  jb short 0xBC5CE85                            ; -> loc_bc5ce85
0xbc5ce7e  mov r13,[rbp+0x1E0]                           

loc_bc5ce85:  ; from bc5ce7c
0xbc5ce85  test rdx,rdx                                  
0xbc5ce88  je 0xBC5D068                                  ; -> loc_bc5d068
0xbc5ce8e  mov eax,edx                                   
0xbc5ce90  and eax,3                                     
0xbc5ce93  cmp rdx,4                                     
0xbc5ce97  jae 0xBC5D2A5                                 ; -> loc_bc5d2a5
0xbc5ce9d  mov rcx,0xCBF29CE484222325                    
0xbc5cea7  xor r8d,r8d                                   
0xbc5ceaa  jmp 0xBC5D302                                 ; -> loc_bc5d302
0xbc5ceaf  lea rcx,[0x12ADF7E8]                          ; [data_12adf7e8]
0xbc5ceb6  call 0xE938CB0                                ; -> sub_e938cb0
0xbc5cebb  cmp dword ptr [0x12ADF7E8],0xFFFFFFFF         ; [data_12adf7e8]
0xbc5cec2  jne 0xBC5BF15                                 ; -> sub_bc5bf15
0xbc5cec8  lea rdx,[0xF55B3EC]                           ; [data_f55b3ec] "ClusterDepthBounds"
0xbc5cecf  lea r13,[rbp+0x1E0]                           
0xbc5ced6  mov rcx,r13                                   
0xbc5ced9  call 0x79580                                  ; -> sub_79580
0xbc5cede  nop                                           
0xbc5cedf  mov rdx,[rbp+0x1F0]                           
0xbc5cee6  cmp qword ptr [rbp+0x1F8],0x10                
0xbc5ceee  jb short 0xBC5CEF7                            ; -> loc_bc5cef7
0xbc5cef0  mov r13,[rbp+0x1E0]                           

loc_bc5cef7:  ; from bc5ceee
0xbc5cef7  test rdx,rdx                                  
0xbc5cefa  je 0xBC5D077                                  ; -> loc_bc5d077
0xbc5cf00  mov eax,edx                                   
0xbc5cf02  and eax,3                                     
0xbc5cf05  cmp rdx,4                                     
0xbc5cf09  jae 0xBC5D357                                 ; -> loc_bc5d357
0xbc5cf0f  mov rcx,0xCBF29CE484222325                    
0xbc5cf19  xor r8d,r8d                                   
0xbc5cf1c  jmp 0xBC5D3B4                                 ; -> loc_bc5d3b4
0xbc5cf21  lea rcx,[0x12ADF7F8]                          ; [data_12adf7f8]
0xbc5cf28  call 0xE938CB0                                ; -> sub_e938cb0
0xbc5cf2d  cmp dword ptr [0x12ADF7F8],0xFFFFFFFF         ; [data_12adf7f8]
0xbc5cf34  jne 0xBC5C3FB                                 ; -> sub_bc5c3fb
0xbc5cf3a  lea rdx,[0xF556118]                           ; [data_f556118] "PointLightPreCalcValues"
0xbc5cf41  lea r13,[rbp+0x1E0]                           
0xbc5cf48  mov rcx,r13                                   
0xbc5cf4b  call 0x79580                                  ; -> sub_79580
0xbc5cf50  nop                                           
0xbc5cf51  mov r8,[rbp+0x1F0]                            
0xbc5cf58  cmp qword ptr [rbp+0x1F8],0x10                
0xbc5cf60  jb short 0xBC5CF69                            ; -> loc_bc5cf69
0xbc5cf62  mov r13,[rbp+0x1E0]                           

loc_bc5cf69:  ; from bc5cf60
0xbc5cf69  test r8,r8                                    
0xbc5cf6c  je 0xBC5D086                                  ; -> loc_bc5d086
0xbc5cf72  mov eax,r8d                                   
0xbc5cf75  and eax,3                                     
0xbc5cf78  mov rcx,0x100000001B3                         
0xbc5cf82  cmp r8,4                                      
0xbc5cf86  jae 0xBC5D409                                 ; -> loc_bc5d409
0xbc5cf8c  mov rdx,0xCBF29CE484222325                    
0xbc5cf96  xor r9d,r9d                                   
0xbc5cf99  jmp 0xBC5D45C                                 ; -> loc_bc5d45c

loc_bc5cf9e:  ; from bc5ca98, bc5cb42, bc5cba4, bc5cc89
0xbc5cf9e  mov qword ptr [rsp+0x20],0                    
0xbc5cfa7  xor ecx,ecx                                   
0xbc5cfa9  xor edx,edx                                   
0xbc5cfab  xor r8d,r8d                                   
0xbc5cfae  xor r9d,r9d                                   
0xbc5cfb1  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
0xbc5cfb7  xorps xmm0,xmm0                               
0xbc5cfba  movups [rbp+0x1E8],xmm0                       
0xbc5cfc1  lea rax,[0xF08E738]                           ; [data_f08e738]
0xbc5cfc8  mov [rbp+0x1E0],rax                           
0xbc5cfcf  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
0xbc5cfd6  lea rcx,[rbp+0x1E0]                           
0xbc5cfdd  call 0xEEC6D80                                ; -> sub_eec6d80
0xbc5cfe2  nop                                           
0xbc5cfe3  xorps xmm0,xmm0                               
0xbc5cfe6  movups [rbp+0x1E8],xmm0                       
0xbc5cfed  lea rax,[0xF08E738]                           ; [data_f08e738]
0xbc5cff4  mov [rbp+0x1E0],rax                           
0xbc5cffb  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
0xbc5d002  lea rcx,[rbp+0x1E0]                           
0xbc5d009  call 0xEEC6D80                                ; -> sub_eec6d80
0xbc5d00e  nop                                           
0xbc5d00f  xorps xmm0,xmm0                               
0xbc5d012  movups [rbp+0x1E8],xmm0                       
0xbc5d019  lea rax,[0xF08E738]                           ; [data_f08e738]
0xbc5d020  mov [rbp+0x1E0],rax                           
0xbc5d027  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
0xbc5d02e  lea rcx,[rbp+0x1E0]                           
0xbc5d035  call 0xEEC6D80                                ; -> sub_eec6d80
0xbc5d03a  nop                                           

loc_bc5d03b:  ; from bc5cd32
0xbc5d03b  mov rcx,0xCBF29CE484222325                    
0xbc5d045  jmp 0xBC5D119                                 ; -> loc_bc5d119

loc_bc5d04a:  ; from bc5cda4
0xbc5d04a  mov rcx,0xCBF29CE484222325                    
0xbc5d054  jmp 0xBC5D1C8                                 ; -> loc_bc5d1c8

loc_bc5d059:  ; from bc5ce16
0xbc5d059  mov rcx,0xCBF29CE484222325                    
0xbc5d063  jmp 0xBC5D27A                                 ; -> loc_bc5d27a

loc_bc5d068:  ; from bc5ce88
0xbc5d068  mov rcx,0xCBF29CE484222325                    
0xbc5d072  jmp 0xBC5D32C                                 ; -> loc_bc5d32c

loc_bc5d077:  ; from bc5cefa
0xbc5d077  mov rcx,0xCBF29CE484222325                    
0xbc5d081  jmp 0xBC5D3DE                                 ; -> loc_bc5d3de

loc_bc5d086:  ; from bc5cf6c
0xbc5d086  mov rdx,0xCBF29CE484222325                    
0xbc5d090  jmp 0xBC5D47D                                 ; -> loc_bc5d47d

loc_bc5d095:  ; from bc5cd41
0xbc5d095  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc5d099  mov rcx,0xCBF29CE484222325                    
0xbc5d0a3  xor r8d,r8d                                   
0xbc5d0a6  mov r9,0x100000001B3                          

loc_bc5d0b0:  ; from bc5d0ea
0xbc5d0b0  movzx r10d,byte ptr [rdi+r8]                  
0xbc5d0b5  xor r10,rcx                                   
0xbc5d0b8  imul r10,r9                                   
0xbc5d0bc  movzx ecx,byte ptr [rdi+r8+1]                 
0xbc5d0c2  xor rcx,r10                                   
0xbc5d0c5  imul rcx,r9                                   
0xbc5d0c9  movzx r10d,byte ptr [rdi+r8+2]                
0xbc5d0cf  xor r10,rcx                                   
0xbc5d0d2  imul r10,r9                                   
0xbc5d0d6  movzx ecx,byte ptr [rdi+r8+3]                 
0xbc5d0dc  xor rcx,r10                                   
0xbc5d0df  imul rcx,r9                                   
0xbc5d0e3  add r8,4                                      
0xbc5d0e7  cmp rdx,r8                                    
0xbc5d0ea  jne short 0xBC5D0B0                           ; -> loc_bc5d0b0
0xbc5d0ec  test rax,rax                                  
0xbc5d0ef  je short 0xBC5D119                            ; -> loc_bc5d119

loc_bc5d0f1:  ; from bc5cd54
0xbc5d0f1  add rdi,r8                                    
0xbc5d0f4  xor edx,edx                                   
0xbc5d0f6  mov r8,0x100000001B3                          
0xbc5d100  mov r9,rcx                                    
```

**Chunk 3 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| rsi+0x5C | 4 | R | divss xmm8 |
| xmm8 | 16 | R/W | movaps/call/movaps |
| [0xF598D3A] | 8 | R | lea rax |
| rsi+0x84 | 1 | R | cmp byte |
| [0xF5BAC48] | 8 | R | lea rcx |
| rcx | 8 | R/W | cmovne/mov |
| rbp+0x128 | 8 | W | mov rcx |
| [0xF5369E5] | 8 | R | lea rdx |
| rbp+0x180 | 8 | W | lea rcx |
| rbp+0x128 | 8 | W | lea r8 |
| 0x56D8E00 | 8 | W | call sub_56d8e00 |
| rbp+0x1C8 | 4 | W | mov dword 0 |
| rbp+0x1E0/0x1C8/0x1C7/0x180 | 8 | W | lea rcx/rdx/r8/call |
| 0x9B020/0xAA840 | 8 | W | call sub_9b020/sub_aa840 |
| rbx+8 | 8 | R | mov rax |
| rax+8 | 2 | R | mov si |
| rbp+0x1C8/0x1E0/r15 | 8 | W | lea rdx/r8/mov rcx |
| 0xBCC7CE0 | 8 | W | call sub_bcc7ce0 |
| rbp+0x1D8 | 1 | R | cmp byte 1 |
| rbp+0x1CA | 1 | R | cmp byte 0 |
| rbp+0x1C8 | 2 | R | movzx r8d/cmp 0xFFFF |
| xmm8/xmm7/xmm6 | 4 | R | cvttss2si |
| rbp+0x130 | 8 | R | mov rcx |
| rcx+0x10 | 8 | R | mov rcx |
| rsp+0x28/0x20 | 4 | W | mov edx/eax |
| edx | 4 | W | mov esi |
| 0xBC61140 | 8 | W | call sub_bc61140 |
| rbp+0x1F8 | 8 | R | mov rcx |
| rcx | 1 | R | test/je |
| rbp+0x208 | 8 | R | mov rdx |
| rdx | 8 | R | sub rcx |
| rdx | 4 | R | cmp 0x1000/jb |
| rcx-8 | 8 | R | mov rax |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20/jae |
| rdx | 8 | W | add 0x27 |
| rcx | 8 | W | mov rax |
| rbp+0x1F8 | 8 | W | lea rsi |
| 0xE935700 | 8 | W | call sub_e935700 |
| rsi | 16 | W | xorps/movups/mov qword |
| rbp+0x1E8 | 8 | R | mov rax |
| rax+8 | 8 | R | mov rcx |
| rcx | 8 | W | mov qword 0 |
| rax | 8 | R | mov rsi |
| rsi | 1 | R | test/je |
| rax | 8 | R | nop |
| rsi | 8 | R | mov rbx |
| rsi+0x10 | 8 | W | lea rcx |
| 0x9B250 | 8 | W | call sub_9b250 |
| edx | 4 | W | mov 0x50 |
| rsi | 8 | W | mov rcx |
| 0xE935700 | 8 | W | call sub_e935700 |
| rsi/rbx | 8 | R/W | mov/test/jne |
| rbp+0x1E8 | 8 | R | mov rcx |
| edx | 4 | W | mov 0x50 |
| 0xE935700 | 8 | W | call sub_e935700 |
| rbp+0x1B8 | 8 | R | mov rax |
| rax | 4 | R | cmp 0x10/jb |
| rbp+0x1A0 | 8 | R | mov rcx |
| rax | 8 | W | lea rdx |
| rdx | 4 | R | cmp 0x1000/jb |
| rcx-8 | 8 | R | mov r8 |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20/jae |
| rax | 8 | W | add 0x28/mov rdx/mov rcx |
| 0xE935700 | 8 | W | call sub_e935700 |
| rbp+0x1B0/0x1B8/0x1A0 | 8/8/1 | W | mov qword/qword/byte |
| rbp+0x198 | 8 | R | mov rax |
| rax | 4 | R | cmp 0x10/jb |
| rbp+0x180 | 8 | R | mov rcx |
| rax | 8 | W | lea rdx |
| rdx | 4 | R | cmp 0x1000/jb |
| rcx-8 | 8 | R | mov r8 |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20/jae |
| rax | 8 | W | add 0x28/mov rdx/mov rcx |
| 0xE935700 | 8 | W | call sub_e935700 |
| rbp+0x80 | 8 | W | lea rbx |
| rbx | 8 | W | mov rcx |
| 0x56D5810 | 8 | W | call sub_56d5810 |
| rbp+0x120 | 8 | W | lea rcx |
| 0x9BD3C0 | 8 | W | call sub_9bd3c0 |
| rbp+0xC0 | 8 | R | mov rax |
| rax/rdi | 8 | R | cmp/je |
| rax | 8 | R | mov rcx |
| rax+8 | 8 | R | mov rdx |
| rdx/rcx | 8 | W | mov [rdx]/[rcx+8] |
| rax | 8 | R/W | mov [rax]/[rax+8] |
| rax/rdi | 8 | R | cmp/je |
| rbp+0xC8 | 8 | R | mov rcx |
| rcx | 8 | W | mov rax |
| rax+8 | 8 | W | mov rcx |
| rbp+0xC0/0xC8 | 8 | W | mov rdi |
| rax/rdi | 8 | R | cmp/je |
| rbp+0x150 | 8 | W | lea rsi |
| rbp+0xB8 | 8 | R | mov rcx |
| rcx | 1 | R | test/je |
| rcx/rbx | 8 | R | cmp/setne |
| rax | 8 | R | mov |
| rax+0x20 | 8 | R | mov rax |
| [0xF99FFA0] | 8 | W | call sub_eea6040 |
| rbp+0x40 | 8 | W | lea rcx |
| 0x655CEA0 | 8 | W | call sub_655cea0 |
| rsi | 8 | W | mov rcx |
| 0x568DA90 | 8 | W | call sub_568da90 |
| rbp+0x138 | 8 | R | mov rcx |
| rcx | 1 | R | test/je |
| rbp+0x148 | 8 | R | mov rdx |
| rdx | 8 | R | sub rcx |
| rdx | 4 | R | cmp 0x1000/jb |
| rcx-8 | 8 | R | mov rax |
| rcx | 8 | R/W | add/sub/cmp |
| rcx | 4 | R | cmp 0x20/jae |
| rdx | 8 | W | add 0x27 |
| rcx | 8 | W | mov rax |
| 0xE935700 | 8 | W | call sub_e935700 |
| rbp+0x230/0x240/0x250 | 16 | R | movaps xmm6/xmm7/xmm8 |
| rsp | 8 | W | add 0x2E8 |
| rbx/rdi/rsi/r12/r13/r14/r15/rbp | 8 | W | pop |
| 0x78ED0 | 8 | W | call sub_78ed0 |
| ecx | 4 | W | mov 0x30 |
| 0x9BC830 | 8 | W | call sub_9bc830 |
| 0xBC5BC7C | 8 | W | jmp sub_bc5bc7c |
| 0xB432E0 | 8 | W | call sub_b432e0 (3x) |
| [0x12ADF7A8] | 8 | R | lea/call/cmp/jne |
| [0xF566EB0] | 8 | R | lea rdx |
| rbp+0x78 | 8 | W | lea rdi |
| rdi | 8 | W | mov rcx |
| 0x79580 | 8 | W | call sub_79580 |
| rbp+0x88/0x90 | 8/8 | R/W | mov rdx/cmp qword |
| rbp+0x78 | 8 | R | mov rdi |
| [0x12ADF7B8/0x12ADF7C8/0x12ADF7D8/0x12ADF7E8/0x12ADF7F8] | 8 | R | lea/call/cmp/jne |
| [0xF53B2F9/0xF5CEDF3/0xF5BBF34/0xF55B3EC] | 8 | R | lea rdx (string refs) |
| rbp+0x1E0/0x1F0/0x1F8 | 8/8/8 | R/W | lea r13/mov rdx/cmp qword |

**Chunk 3 callees (in order):**
1. 0xEEC73F0 (sub_eec73f0) - called once
2. 0x56D8E00 (sub_56d8e00) - called once
3. 0x9B020 (sub_9b020) - called once
4. 0xAA840 (sub_aa840) - called once
5. 0xBCC7CE0 (sub_bcc7ce0) - called once
6. 0xBC61140 (sub_bc61140) - called once
7. 0xE935700 (sub_e935700) - called many times
8. 0x9B250 (sub_9b250) - called once
9. 0x56D5810 (sub_56d5810) - called once
10. 0x9BD3C0 (sub_9bd3c0) - called once
11. 0x655CEA0 (sub_655cea0) - called once
12. 0x568DA90 (sub_568da90) - called once
13. qword ptr [0xF99FFA0] = sub_eea6040 - called once
14. qword ptr [0xF9A8C78] - called once
15. 0xE938CB0 (sub_e938cb0) - called multiple times
16. 0x79580 (sub_79580) - called multiple times
17. 0xEEC6D80 (sub_eec6d80) - called multiple times

### Chunk 4: 0xbc5d100..0xbc5d4a1 (end of sub_bc5bad0 - from actual rdis output)
```
0xbc5d100  mov r9,rcx                                    

loc_bc5d103:  ; from bc5d117
0xbc5d103  movzx ecx,byte ptr [rdi+rdx]                  
0xbc5d107  xor rcx,r9                                    
0xbc5d10a  imul rcx,r8                                   
0xbc5d10e  inc rdx                                       
0xbc5d111  mov r9,rcx                                    
0xbc5d114  cmp rax,rdx                                   
0xbc5d117  jne short 0xBC5D103                           ; -> loc_bc5d103
0xbc5d119  mov [0x12ADF7A0],rcx                          ; [data_12adf7a0]
0xbc5d120  lea rcx,[rbp+0x78]                            
0xbc5d124  call 0x73150                                  ; -> sub_73150
0xbc5d129  lea rcx,[0x12ADF7A8]                          ; [data_12adf7a8]
0xbc5d130  call 0xE938D70                                ; -> sub_e938d70
0xbc5d135  mov rsi,[rbp+0x220]                           
0xbc5d13c  jmp 0xBC5BD02                                 ; -> sub_bc5bd02
0xbc5d141  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc5d145  mov rcx,0xCBF29CE484222325                    
0xbc5d14f  xor r8d,r8d                                   
0xbc5d152  mov r9,0x100000001B3                          

loc_bc5d15c:  ; from bc5d197
0xbc5d15c  movzx r10d,byte ptr [r13+r8]                  
0xbc5d162  xor r10,rcx                                   
0xbc5d165  imul r10,r9                                   
0xbc5d169  movzx ecx,byte ptr [r13+r8+1]                 
0xbc5d16f  xor rcx,r10                                   
0xbc5d172  imul rcx,r9                                   
0xbc5d176  movzx r10d,byte ptr [r13+r8+2]                
0xbc5d17c  xor r10,rcx                                   
0xbc5d17f  imul r10,r9                                   
0xbc5d183  movzx ecx,byte ptr [r13+r8+3]                 
0xbc5d189  xor rcx,r10                                   
0xbc5d18c  imul rcx,r9                                   
0xbc5d190  add r8,4                                      
0xbc5d194  cmp rdx,r8                                    
0xbc5d197  jne short 0xBC5D15C                           ; -> loc_bc5d15c
0xbc5d199  test rax,rax                                  
0xbc5d19c  je short 0xBC5D1C8                            ; -> loc_bc5d1c8
0xbc5d19e  add r13,r8                                    
0xbc5d1a1  xor edx,edx                                   
0xbc5d1a3  mov r8,0x100000001B3                          
0xbc5d1ad  mov r9,rcx                                    

loc_bc5d1b0:  ; from bc5d1c6
0xbc5d1b0  movzx ecx,byte ptr [r13+rdx]                  
0xbc5d1b6  xor rcx,r9                                    
0xbc5d1b9  imul rcx,r8                                   
0xbc5d1bd  inc rdx                                       
0xbc5d1c0  mov r9,rcx                                    
0xbc5d1c3  cmp rax,rdx                                   
0xbc5d1c6  jne short 0xBC5D1B0                           ; -> loc_bc5d1b0

loc_bc5d1c8:  ; from bc5d19c
0xbc5d1c8  mov [0x12ADF7B0],rcx                          ; [data_12adf7b0]
0xbc5d1cf  lea rcx,[rbp+0x1E0]                           
0xbc5d1d6  call 0x73150                                  ; -> sub_73150
0xbc5d1db  lea rcx,[0x12ADF7B8]                          ; [data_12adf7b8]
0xbc5d1e2  call 0xE938D70                                ; -> sub_e938d70
0xbc5d1e7  mov rsi,[rbp+0x220]                           
0xbc5d1ee  jmp 0xBC5BEA6                                 ; -> sub_bc5bea6
0xbc5d1f3  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc5d1f7  mov rcx,0xCBF29CE484222325                    
0xbc5d201  xor r8d,r8d                                   
0xbc5d204  mov r9,0x100000001B3                          

loc_bc5d20e:  ; from bc5d249
0xbc5d20e  movzx r10d,byte ptr [r13+r8]                  
0xbc5d214  xor r10,rcx                                   
0xbc5d217  imul r10,r9                                   
0xbc5d21b  movzx ecx,byte ptr [r13+r8+1]                 
0xbc5d221  xor rcx,r10                                   
0xbc5d224  imul rcx,r9                                   
0xbc5d228  movzx r10d,byte ptr [r13+r8+2]                
0xbc5d22e  xor r10,rcx                                   
0xbc5d231  imul r10,r9                                   
0xbc5d235  movzx ecx,byte ptr [r13+r8+3]                 
0xbc5d23b  xor rcx,r10                                   
0xbc5d23e  imul rcx,r9                                   
0xbc5d242  add r8,4                                      
0xbc5d246  cmp rdx,r8                                    
0xbc5d249  jne short 0xBC5D20E                           ; -> loc_bc5d20e
0xbc5d24b  test rax,rax                                  
0xbc5d24e  je short 0xBC5D27A                            ; -> loc_bc5d27a
0xbc5d250  add r13,r8                                    
0xbc5d253  xor edx,edx                                   
0xbc5d255  mov r8,0x100000001B3                          
0xbc5d25f  mov r9,rcx                                    

loc_bc5d262:  ; from bc5d278
0xbc5d262  movzx ecx,byte ptr [r13+rdx]                  
0xbc5d268  xor rcx,r9                                    
0xbc5d26b  imul rcx,r8                                   
0xbc5d26f  inc rdx                                       
0xbc5d272  mov r9,rcx                                    
0xbc5d275  cmp rax,rdx                                   
0xbc5d278  jne short 0xBC5D262                           ; -> loc_bc5d262

loc_bc5d27a:  ; from bc5d24e
0xbc5d27a  mov [0x12ADF7C0],rcx                          ; [data_12adf7c0]
0xbc5d281  lea rcx,[rbp+0x1E0]                           
0xbc5d288  call 0x73150                                  ; -> sub_73150
0xbc5d28d  lea rcx,[0x12ADF7C8]                          ; [data_12adf7c8]
0xbc5d294  call 0xE938D70                                ; -> sub_e938d70
0xbc5d299  mov rsi,[rbp+0x220]                           
0xbc5d2a0  jmp 0xBC5BECB                                 ; -> sub_bc5becb
0xbc5d2a5  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc5d2a9  mov rcx,0xCBF29CE484222325                    
0xbc5d2b3  xor r8d,r8d                                   
0xbc5d2b6  mov r9,0x100000001B3                          

loc_bc5d2c0:  ; from bc5d2fb
0xbc5d2c0  movzx r10d,byte ptr [r13+r8]                  
0xbc5d2c6  xor r10,rcx                                   
0xbc5d2c9  imul r10,r9                                   
0xbc5d2cd  movzx ecx,byte ptr [r13+r8+1]                 
0xbc5d2d3  xor rcx,r10                                   
0xbc5d2d6  imul rcx,r9                                   
0xbc5d2da  movzx r10d,byte ptr [r13+r8+2]                
0xbc5d2e0  xor r10,rcx                                   
0xbc5d2e3  imul r10,r9                                   
0xbc5d2e7  movzx ecx,byte ptr [r13+r8+3]                 
0xbc5d2ed  xor rcx,r10                                   
0xbc5d2f0  imul rcx,r9                                   
0xbc5d2f4  add r8,4                                      
0xbc5d2f8  cmp rdx,r8                                    
0xbc5d2fb  jne short 0xBC5D2C0                           ; -> loc_bc5d2c0
0xbc5d2fd  test rax,rax                                  
0xbc5d300  je short 0xBC5D32C                            ; -> loc_bc5d32c
0xbc5d302  add r13,r8                                    
0xbc5d305  xor edx,edx                                   
0xbc5d307  mov r8,0x100000001B3                          
0xbc5d311  mov r9,rcx                                    

loc_bc5d314:  ; from bc5d32a
0xbc5d314  movzx ecx,byte ptr [r13+rdx]                  
0xbc5d31a  xor rcx,r9                                    
0xbc5d31d  imul rcx,r8                                   
0xbc5d321  inc rdx                                       
0xbc5d324  mov r9,rcx                                    
0xbc5d327  cmp rax,rdx                                   
0xbc5d32a  jne short 0xBC5D314                           ; -> loc_bc5d314

loc_bc5d32c:  ; from bc5d300
0xbc5d32c  mov [0x12ADF7D0],rcx                          ; [data_12adf7d0]
0xbc5d333  lea rcx,[rbp+0x1E0]                           
0xbc5d33a  call 0x73150                                  ; -> sub_73150
0xbc5d33f  lea rcx,[0x12ADF7D8]                          ; [data_12adf7d8]
0xbc5d346  call 0xE938D70                                ; -> sub_e938d70
0xbc5d34b  mov rsi,[rbp+0x220]                           
0xbc5d352  jmp 0xBC5BEF0                                 ; -> sub_bc5bef0
0xbc5d357  and rdx,0xFFFFFFFFFFFFFFFC                    
0xbc5d35b  mov rcx,0xCBF29CE484222325                    
0xbc5d365  xor r8d,r8d                                   
0xbc5d368  mov r9,0x100000001B3                          

loc_bc5d372:  ; from bc5d3ad
0xbc5d372  movzx r10d,byte ptr [r13+r8]                  
0xbc5d378  xor r10,rcx                                   
0xbc5d37b  imul r10,r9                                   
0xbc5d37f  movzx ecx,byte ptr [r13+r8+1]                 
0xbc5d385  xor rcx,r10                                   
0xbc5d388  imul rcx,r9                                   
0xbc5d38c  movzx r10d,byte ptr [r13+r8+2]                
0xbc5d392  xor r10,rcx                                   
0xbc5d395  imul r10,r9                                   
0xbc5d399  movzx ecx,byte ptr [r13+r8+3]                 
0xbc5d39f  xor rcx,r10                                   
0xbc5d3a2  imul rcx,r9                                   
0xbc5d3a6  add r8,4                                      
0xbc5d3aa  cmp rdx,r8                                    
0xbc5d3ad  jne short 0xBC5D372                           ; -> loc_bc5d372
0xbc5d3af  test rax,rax                                  
0xbc5d3b2  je short 0xBC5D3DE                            ; -> loc_bc5d3de
0xbc5d3b4  add r13,r8                                    
0xbc5d3b7  xor edx,edx                                   
0xbc5d3b9  mov r8,0x100000001B3                          
0xbc5d3c3  mov r9,rcx                                    

loc_bc5d3c6:  ; from bc5d3dc
0xbc5d3c6  movzx ecx,byte ptr [r13+rdx]                  
0xbc5d3cc  xor rcx,r9                                    
0xbc5d3cf  imul rcx,r8                                   
0xbc5d3d3  inc rdx                                       
0xbc5d3d6  mov r9,rcx                                    
0xbc5d3d9  cmp rax,rdx                                   
0xbc5d3dc  jne short 0xBC5D3C6                           ; -> loc_bc5d3c6

loc_bc5d3de:  ; from bc5d3b2
0xbc5d3de  mov [0x12ADF7E0],rcx                          ; [data_12adf7e0]
0xbc5d3e5  lea rcx,[rbp+0x1E0]                           
0xbc5d3ec  call 0x73150                                  ; -> sub_73150
0xbc5d3f1  lea rcx,[0x12ADF7E8]                          ; [data_12adf7e8]
0xbc5d3f8  call 0xE938D70                                ; -> sub_e938d70
0xbc5d3fd  mov rsi,[rbp+0x220]                           
0xbc5d404  jmp 0xBC5BF15                                 ; -> sub_bc5bf15
0xbc5d409  and r8,0xFFFFFFFFFFFFFFFC                     
0xbc5d40d  mov rdx,0xCBF29CE484222325                    
0xbc5d417  xor r9d,r9d                                   

loc_bc5d41a:  ; from bc5d455
0xbc5d41a  movzx r10d,byte ptr [r13+r9]                  
0xbc5d420  xor r10,rdx                                   
0xbc5d423  imul r10,rcx                                  
0xbc5d427  movzx edx,byte ptr [r13+r9+1]                 
0xbc5d42d  xor rdx,r10                                   
0xbc5d430  imul rdx,rcx                                  
0xbc5d434  movzx r10d,byte ptr [r13+r9+2]                
0xbc5d43a  xor r10,rdx                                   
0xbc5d43d  imul r10,rcx                                  
0xbc5d441  movzx edx,byte ptr [r13+r9+3]                 
0xbc5d447  xor rdx,r10                                   
0xbc5d44a  imul rdx,rcx                                  
0xbc5d44e  add r9,4                                      
0xbc5d452  cmp r8,r9                                     
0xbc5d455  jne short 0xBC5D41A                           ; -> loc_bc5d41a
0xbc5d457  test rax,rax                                  
0xbc5d45a  je short 0xBC5D47D                            ; -> loc_bc5d47d
0xbc5d45c  add r13,r9                                    
0xbc5d45f  xor r8d,r8d                                   
0xbc5d462  mov r9,rdx                                    

loc_bc5d465:  ; from bc5d47b
0xbc5d465  movzx edx,byte ptr [r13+r8]                   
0xbc5d46b  xor rdx,r9                                    
0xbc5d46e  imul rdx,rcx                                  
0xbc5d472  inc r8                                        
0xbc5d475  mov r9,rdx                                    
0xbc5d478  cmp rax,r8                                    
0xbc5d47b  jne short 0xBC5D465                           ; -> loc_bc5d465

loc_bc5d47d:  ; from bc5d45a
0xbc5d47d  mov [0x12ADF7F0],rdx                          ; [data_12adf7f0]
0xbc5d484  lea rcx,[rbp+0x1E0]                           
0xbc5d48b  call 0x73150                                  ; -> sub_73150
0xbc5d490  lea rcx,[0x12ADF7F8]                          ; [data_12adf7f8]
0xbc5d497  call 0xE938D70                                ; -> sub_e938d70
0xbc5d49c  jmp 0xBC5C3FB                                 ; -> sub_bc5c3fb
0xbc5d4a1  nop [rax+rax]                                 ; R ret@e938d70+0x0+idx
```

**Chunk 4 stores/reads [reg+off] (partial - key ones visible):**

| Offset | Size | R/W | Meaning |
|--------|------|-----|---------|
| r9 | 8 | W | mov rcx |
| rdi+rdx | 1 | R | movzx ecx |
| rcx/r9/r8 | 8/8/8 | R/W | xor/imul/mov/inc/cmp/jne |
| [0x12ADF7A0/0x12ADF7B0/0x12ADF7C0/0x12ADF7D0/0x12ADF7E0/0x12ADF7F0] | 8 | W | mov rcx/rdx |
| rbp+0x78/0x1E0 | 8 | W | lea rcx |
| 0x73150 | 8 | W | call sub_73150 (6x) |
| [0x12ADF7A8/0x12ADF7B8/0x12ADF7C8/0x12ADF7D8/0x12ADF7E8/0x12ADF7F8] | 8 | R | lea/call sub_e938cb0/sub_e938d70 |
| rbp+0x220 | 8 | R | mov rsi |
| r13+r8/r13+rdx | 1/4 | R | movzx |
| rcx/r9/r8 | 8 | R/W | xor/imul/mov |
| rdx | 8 | R/W | inc/cmp/jne |
| rax | 8 | R | test/cmp |
| r13 | 8 | R/W | add/mov |
| edx | 4 | W | xor |
| r8/r9 | 8 | W | mov constant |
| rsi | 8 | W | mov [rbp+0x220] |

**Chunk 4 callees (in order):**
1. 0x73150 (sub_73150) - called 6 times
2. 0xE938D70 (sub_e938d70) - called 6 times
3. 0xBC5BD02/0xBC5BEA6/0xBC5BECB/0xBC5BEF0/0xBC5BF15/0xBC5C3FB - jmp targets

## Closing tables for sub_bc57460 (0xbc57460..0xbc5a28f)

### Strings referenced (RVA, text, call site)
| RVA | Text | Call site |
|-----|------|-----------|
| 0xF5B49BF | "LightClustering" | 0xbc57739, 0xbc59f3e |
| 0xF5C5F05 | "LightClusteringPhase" | 0xbc589ed |
| 0xF5461D6 | "zLights" | 0xbc59d5b |
| 0xF51DBD7 | "zLightLookupArray" | 0xbc59e45 |
| 0xF55B94D | "Extends" | 0xbc59dd0 |
| 0xF54F409 | "ClusterDimensions" | 0xbc59eba |
| 0xF53B2F9 | "ClusterNearFarWidthHeight" | 0xbc5cd72 |
| 0xF55B3EC | "ClusterDepthBounds" | 0xbc5cec8 |
| 0xF5BBF34 | "ClusterSize" | 0xbc5ce56 |
| 0xF556118 | "PointLightPreCalcValues" | 0xbc5cf3a |

### Callees in order (unique)
1. 0xEEC73F0 (sub_eec73f0)
2. 0xBC09250 (sub_bc09250)
3. 0x567C8B0 (sub_567c8b0)
4. 0xAB49C0 (sub_ab49c0)
5. 0x5667860 (sub_5667860)
6. 0xA78940 (sub_a78940)
7. qword ptr [0xF99FFA0] = sub_eea6040
8. 0xEEC6ED0 (sub_eec6ed0)
9. 0xAA6580 (sub_aa6580)
10. 0x1999390 (sub_1999390)
11. 0x5668AC0 (sub_5668ac0)
12. qword ptr [0xF9A8F60]
13. 0xBC5B130 (sub_bc5b130)
14. qword ptr [0xF9A8DB8]
15. qword ptr [0xF9A8DD8]
16. qword ptr [0xF9A8DE0]
17. qword ptr [0xF9A8ED0]
18. 0xEEC75A0 (sub_eec75a0)
19. qword ptr [0xF9A8C78]
20. 0xE938CB0 (sub_e938cb0)
21. 0x79580 (sub_79580)
22. 0xE938D70 (sub_e938d70)
23. 0x73150 (sub_73150)
24. 0x75720 (sub_75720)
25. 0x75740 (sub_75740)
26. 0x9BC830 (sub_9bc830)
27. 0x78ED0 (sub_78ed0)
28. 0xB432E0 (sub_b432e0)

### [reg+off] writes into output objects
| Offset | Size | Object | Meaning |
|--------|------|--------|---------|
| r12+rax*0x40 | 16 | cluster output | movlps xmm3 |
| r12+rax*0x40+8 | 4 | cluster output | movss xmm1 |
| r12+rax*0x40+0xC | 4 | cluster output | mov dword 0 |
| r12+rax*0x40+0x10 | 8 | cluster output | movlps xmm5 |
| r12+rax*0x40+0x18 | 4 | cluster output | movss xmm2 |
| r12+rax*0x40+0x1C | 4 | cluster output | mov dword 0 |
| r12+rax*0x40+0x20 | 8 | cluster output | movlps xmm10 |
| r12+rax*0x40+0x28 | 4 | cluster output | movss xmm13 |
| r12+rax*0x40+0x2C | 4 | cluster output | mov dword 0 |
| r12+rax*0x40+0x30 | 4 | cluster output | mov esi (index) |
| r12+rax*0x40+0x34 | 4 | cluster output | movss xmm0 |
| r12+rax*0x40+0x38 | 8 | cluster output | mov qword 0 |

## Closing tables for sub_bc5bad0 (0xbc5bad0..0xbc5d4a1)

### Strings referenced (RVA, text, call site)
| RVA | Text | Call site |
|-----|------|-----------|
| 0xF566EB0 | "LightsPerCluster" | 0xbc5cd06 |
| 0xF53B2F9 | "ClusterNearFarWidthHeight" | 0xbc5cd72 |
| 0xF5CEDF3 | "CameraFarPlane" | 0xbc5cde4 |
| 0xF5BBF34 | "ClusterSize" | 0xbc5ce56 |
| 0xF55B3EC | "ClusterDepthBounds" | 0xbc5cec8 |
| 0xF556118 | "PointLightPreCalcValues" | 0xbc5cf3a |
| 0xF5369E5 | "AngularRefinement" | 0xbc5c9a5 |

### Callees in order (unique)
1. 0xEBCE390 (sub_ebce390)
2. qword ptr [0xF99FFA0] = sub_eea6040
3. 0xBCC1A30 (sub_bcc1a30)
4. 0xEEC5870 (sub_eec5870)
5. 0x9BD2E0 (sub_9bd2e0)
6. 0xE86B370 (sub_e86b370)
7. 0x5679DB0 (sub_5679db0)
8. 0x568DB90 (sub_568db90)
8. 0xE86D7F0 (sub_e86d7f0)
9. 0xBCC3190 (sub_bcc3190)
10. 0xBC70FF0 (sub_bc70ff0)
11. 0xC4BBA0 (sub_c4bba0)
12. 0xE935700 (sub_e935700)
13. 0x9B250 (sub_9b250)
14. 0x56D5810 (sub_56d5810)
15. 0x9BD3C0 (sub_9bd3c0)
16. 0x655CEA0 (sub_655cea0)
17. 0x568DA90 (sub_568da90)
18. qword ptr [0xF99FFA0] = sub_eea6040
19. qword ptr [0xF9A8C78]
20. 0xE938CB0 (sub_e938cb0)
21. 0x79580 (sub_79580)
22. 0xEEC6D80 (sub_eec6d80)
23. 0x56D8E00 (sub_56d8e00)
24. 0x9B020 (sub_9b020)
25. 0xAA840 (sub_aa840)
26. 0xBCC7CE0 (sub_bcc7ce0)
27. 0xBC61140 (sub_bc61140)
28. 0x9B250 (sub_9b250)
29. 0x56D5810 (sub_56d5810)
30. 0xEEC73F0 (sub_eec73f0)
31. 0x73150 (sub_73150)
32. 0xE938D70 (sub_e938d70)
33. 0xBC5BD02/0xBC5BEA6/0xBC5BECB/0xBC5BEF0/0xBC5BF15/0xBC5C3FB/0xBC5BC7C - jmp targets

### [reg+off] writes into output objects
| Offset | Size | Object | Meaning |
|--------|------|--------|---------|
| [0x12ADF3C8] | 8 | global | mov rcx |
| [0x12ADF3D8] | 8 | global | mov rcx |
| [0x12ADE670] | 8 | global | mov rcx |
| [0x12ADE680] | 8 | global | mov rcx |
| [0x12ADE690] | 8 | global | mov rcx |
| [0x12ADE6A0] | 8 | global | mov rcx |
| [0x12ADE6B0] | 8 | global | mov rcx |
| [0x12ADE6C0] | 8 | global | mov rdx |
| [0x12ADF7A0] | 8 | global | mov rcx |
| [0x12ADF7B0] | 8 | global | mov rcx |
| [0x12ADF7C0] | 8 | global | mov rcx |
| [0x12ADF7D0] | 8 | global | mov rcx |
| [0x12ADF7E0] | 8 | global | mov rcx |
| [0x12ADF7F0] | 8 | global | mov rdx |

## NEXT
Unit U-I1b complete. All pass bodies for sub_bc57460 and sub_bc5bad0 documented instruction-complete to their end addresses. Verify_oc.py passes (3631/3631).