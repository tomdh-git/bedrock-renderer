## NEXT
Continue sub_bc57460 pass body from 0xbc584de (end of chunk 2)

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