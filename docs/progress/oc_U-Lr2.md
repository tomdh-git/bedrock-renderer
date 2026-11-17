## NEXT
DONE

# oc_U-Lr2 — ClientInstance::loadResources 0x186e6a0, slice 0x186eb3a..0x186f04a (chunk 2 of 6)

All `0xRVA  instr` lines below are copied verbatim from docs/progress/_part_Lr2.txt (250 instructions, 0x186eb3a..0x186f04a). Size key: qword/64-bit reg store or load = 8, dword = 4, movups/movaps = 16. Tags: [V] visible in the listed instruction, [I] inferred from the call/immediate pattern, '-' = not shown by any instruction or string.

## Phases

### Phase 1: 0x186eb3a..0x186ec00 (40 instructions)
Stores 0 to [rbp+0x450], builds descriptor {ptr 0xF58E601 at [rbp-0x40], len 0xE at [rbp-0x38]}, spills rsi to [rsp+0x20], and calls 0x1870DE0 (rcx=[rbp+0x628], rdx=&desc, rsi=r8=&[rbp+0x450], r9d=0x13) to load resource string #1 into [rbp+0x450] [I]; a non-null result is released (0x2FE440) and 0x138 bytes zeroed at it (0xE935700), then [rbp+0x450] is cleared (movaps) and [rbp+0x460] zeroed. An object is allocated via call qword ptr [0xF99FFA0] (edx=0x14, interface slots [0x1233E1A8]+0/+8) [V]; on success [rbp+0x450]=rax, [rbp+0x460]=rax+0x14, 16 bytes from [0xF0FBDD8] are stored at [rdi], dword 0xC at [rdi+0x10], and rax saved at [rbp+0x458].

```
0x186eb3a  mov qword ptr [rbp+0x450],0
0x186eb45  lea rax,[0xF58E601]
0x186eb4c  mov [rbp-0x40],rax
0x186eb50  mov qword ptr [rbp-0x38],0xE
0x186eb58  mov [rsp+0x20],rsi
0x186eb5d  lea rdx,[rbp-0x40]
0x186eb61  lea rsi,[rbp+0x450]
0x186eb68  mov rcx,[rbp+0x628]
0x186eb6f  mov r8,rsi
0x186eb72  mov r9d,0x13
0x186eb78  call 0x1870DE0
0x186eb7d  nop
0x186eb7e  mov rdi,[rbp+0x450]
0x186eb85  test rdi,rdi
0x186eb88  je short 0x186EB9F
0x186eb8a  mov rcx,rdi
0x186eb8d  call 0x2FE440
0x186eb92  mov edx,0x138
0x186eb97  mov rcx,rdi
0x186eb9a  call 0xE935700
0x186eb9f  xorps xmm0,xmm0
0x186eba2  movaps [rbp+0x450],xmm0
0x186eba9  mov qword ptr [rbp+0x460],0
0x186ebb4  mov rcx,[0x1233E1A8]
0x186ebbb  mov rax,[rcx]
0x186ebbe  mov rax,[rax+8]
0x186ebc2  mov edx,0x14
0x186ebc7  call qword ptr [0xF99FFA0]
0x186ebcd  nop
0x186ebce  mov rdi,rax
0x186ebd1  test rax,rax
0x186ebd4  je 0x18701E1
0x186ebda  mov [rbp+0x450],rdi
0x186ebe1  mov rax,rdi
0x186ebe4  add rax,0x14
0x186ebe8  mov [rbp+0x460],rax
0x186ebef  movups xmm0,[0xF0FBDD8]
0x186ebf6  movups [rdi],xmm0
0x186ebf9  mov dword ptr [rdi+0x10],0xC
0x186ec00  mov [rbp+0x458],rax
```

### Phase 2: 0x186ec07..0x186ecd4 (40 instructions)
Zeros [rbp+0x210], builds descriptor {ptr 0xF56B1E9 at [rbp-0x30], len 0x10 at [rbp-0x28]}, spills rsi, and calls 0x1870DE0 (r9d=0x16) to load resource string #2 into [rbp+0x210] [I]; a non-null result is released (0x2FE440) and 0x138 bytes zeroed (0xE935700), then [rbp+0x210] is cleared (movaps), [rbp+0x220] and [rbp+0x230] zeroed. Builds descriptor {ptr 0xF58736F at [rbp-0x20], len 0x13 at [rbp-0x18]}, spills rsi, and calls 0x1870DE0 (r9d=0x15) to load resource string #3 into [rbp+0x230] [I]; its pointer is released if non-null (call at 0x186ecd4; the 0x138-byte zero completes in phase 3).

```
0x186ec07  mov qword ptr [rbp+0x210],0
0x186ec12  lea rax,[0xF56B1E9]
0x186ec19  mov [rbp-0x30],rax
0x186ec1d  mov qword ptr [rbp-0x28],0x10
0x186ec25  mov [rsp+0x20],rsi
0x186ec2a  lea rdx,[rbp-0x30]
0x186ec2e  lea rsi,[rbp+0x210]
0x186ec35  mov rcx,[rbp+0x628]
0x186ec3c  mov r8,rsi
0x186ec3f  mov r9d,0x16
0x186ec45  call 0x1870DE0
0x186ec4a  nop
0x186ec4b  mov rdi,[rbp+0x210]
0x186ec52  test rdi,rdi
0x186ec55  je short 0x186EC6C
0x186ec57  mov rcx,rdi
0x186ec5a  call 0x2FE440
0x186ec5f  mov edx,0x138
0x186ec64  mov rcx,rdi
0x186ec67  call 0xE935700
0x186ec6c  xorps xmm0,xmm0
0x186ec6f  movaps [rbp+0x210],xmm0
0x186ec76  mov qword ptr [rbp+0x220],0
0x186ec81  mov qword ptr [rbp+0x230],0
0x186ec8c  lea rax,[0xF58736F]
0x186ec93  mov [rbp-0x20],rax
0x186ec97  mov qword ptr [rbp-0x18],0x13
0x186ec9f  mov [rsp+0x20],rsi
0x186eca4  lea rdx,[rbp-0x20]
0x186eca8  lea rsi,[rbp+0x230]
0x186ecaf  mov rcx,[rbp+0x628]
0x186ecb6  mov r8,rsi
0x186ecb9  mov r9d,0x15
0x186ecbf  call 0x1870DE0
0x186ecc4  nop
0x186ecc5  mov rdi,[rbp+0x230]
0x186eccc  test rdi,rdi
0x186eccf  je short 0x186ECE6
0x186ecd1  mov rcx,rdi
0x186ecd4  call 0x2FE440
```

### Phase 3: 0x186ecd9..0x186edac (40 instructions)
Completes string #3's release: 0x138 bytes zeroed at the pointer (0xE935700), then [rbp+0x230] cleared (movaps) and [rbp+0x240]/[rbp+0x250] zeroed. Builds descriptor {ptr 0xF5B3C10 at [rbp-0x10], len 8 at [rbp-8]}, spills rsi, and calls 0x1870DE0 (r9d=0x20) to load resource string #4 into [rbp+0x250] [I]; non-null result released + zeroed, [rbp+0x250] cleared (movaps), [rbp+0x260] and [rbp+0x270] zeroed. Builds descriptor {ptr = rbp at [rbp+0x0], len 0xE at [rbp+8]}, sets rdx=rbp, rsi=&[rbp+0x270], and calls 0x1870DE0 (r9d=0x1F) to load resource string #5 into [rbp+0x270] [I].

```
0x186ecd9  mov edx,0x138
0x186ecde  mov rcx,rdi
0x186ece1  call 0xE935700
0x186ece6  xorps xmm0,xmm0
0x186ece9  movaps [rbp+0x230],xmm0
0x186ecf0  mov qword ptr [rbp+0x240],0
0x186ecfb  mov qword ptr [rbp+0x250],0
0x186ed06  lea rax,[0xF5B3C10]
0x186ed0d  mov [rbp-0x10],rax
0x186ed11  mov qword ptr [rbp-8],8
0x186ed19  mov [rsp+0x20],rsi
0x186ed1e  lea rdx,[rbp-0x10]
0x186ed22  lea rsi,[rbp+0x250]
0x186ed29  mov rcx,[rbp+0x628]
0x186ed30  mov r8,rsi
0x186ed33  mov r9d,0x20
0x186ed39  call 0x1870DE0
0x186ed3e  nop
0x186ed3f  mov rdi,[rbp+0x250]
0x186ed46  test rdi,rdi
0x186ed49  je short 0x186ED60
0x186ed4b  mov rcx,rdi
0x186ed4e  call 0x2FE440
0x186ed53  mov edx,0x138
0x186ed58  mov rcx,rdi
0x186ed5b  call 0xE935700
0x186ed60  xorps xmm0,xmm0
0x186ed63  movaps [rbp+0x250],xmm0
0x186ed6a  mov qword ptr [rbp+0x260],0
0x186ed75  mov qword ptr [rbp+0x270],0
0x186ed80  lea rax,[0xF541032]
0x186ed87  mov [rbp],rax
0x186ed8b  mov qword ptr [rbp+8],0xE
0x186ed93  mov [rsp+0x20],rsi
0x186ed98  mov rdx,rbp
0x186ed9b  lea rsi,[rbp+0x270]
0x186eda2  mov rcx,[rbp+0x628]
0x186eda9  mov r8,rsi
0x186edac  mov r9d,0x1F
```

### Phase 4: 0x186edb2..0x186ee86 (40 instructions)
Calls 0x1870DE0 (r9d=0x1F) to load resource string #5 into [rbp+0x270] [I]; string #5's pointer released if non-null (0x2FE440) and 0x138 bytes zeroed (0xE935700), then [rbp+0x270] cleared (movaps), [rbp+0x280] and [rbp+0x290] zeroed. Builds descriptor {ptr 0xF517F47 at [rbp+0x10], len 8 at [rbp+0x18]}, spills rsi, and calls 0x1870DE0 (r9d=5) to load resource string #6 into [rbp+0x290] [I]; non-null result released + zeroed, [rbp+0x290] cleared (movaps), [rbp+0x2A0] and [rbp+0x470] zeroed. Builds descriptor {ptr 0xF5B6558 at [rbp+0x20], len 0xC at [rbp+0x28]} targeting [rbp+0x470], spills rsi.

```
0x186edb2  call 0x1870DE0
0x186edb7  nop
0x186edb8  mov rdi,[rbp+0x270]
0x186edbf  test rdi,rdi
0x186edc2  je short 0x186EDD9
0x186edc4  mov rcx,rdi
0x186edc7  call 0x2FE440
0x186edcc  mov edx,0x138
0x186edd1  mov rcx,rdi
0x186edd4  call 0xE935700
0x186edd9  xorps xmm0,xmm0
0x186eddc  movaps [rbp+0x270],xmm0
0x186ede3  mov qword ptr [rbp+0x280],0
0x186edee  mov qword ptr [rbp+0x290],0
0x186edf9  lea rax,[0xF517F47]
0x186ee00  mov [rbp+0x10],rax
0x186ee04  mov qword ptr [rbp+0x18],8
0x186ee0c  mov [rsp+0x20],rsi
0x186ee11  lea rdx,[rbp+0x10]
0x186ee15  lea rsi,[rbp+0x290]
0x186ee1c  mov rcx,[rbp+0x628]
0x186ee23  mov r8,rsi
0x186ee26  mov r9d,5
0x186ee2c  call 0x1870DE0
0x186ee31  nop
0x186ee32  mov rdi,[rbp+0x290]
0x186ee39  test rdi,rdi
0x186ee3c  je short 0x186EE53
0x186ee3e  mov rcx,rdi
0x186ee41  call 0x2FE440
0x186ee46  mov edx,0x138
0x186ee4b  mov rcx,rdi
0x186ee4e  call 0xE935700
0x186ee53  xorps xmm0,xmm0
0x186ee56  movaps [rbp+0x290],xmm0
0x186ee5d  mov qword ptr [rbp+0x2A0],0
0x186ee68  mov qword ptr [rbp+0x470],0
0x186ee73  lea rax,[0xF5B6558]
0x186ee7a  mov [rbp+0x20],rax
0x186ee7e  mov qword ptr [rbp+0x28],0xC
0x186ee86  mov [rsp+0x20],rsi
```

### Phase 5: 0x186ee8b..0x186ef4f (39 instructions)
String #7 load: descriptor {ptr 0xF5B6558 at [rbp+0x20], len 0xC at [rbp+0x28]} targeting [rbp+0x470], calls 0x1870DE0 (r9d=0x23) [I]; non-null result released (0x2FE440) and 0x138 bytes zeroed (0xE935700), [rbp+0x470] cleared (movaps) and [rbp+0x480] zeroed. Object allocated via call qword ptr [0xF99FFA0] (edx=0x1C, slots [0x1233E1A8]+0/+8) [V]; on success [rbp+0x470]=rax, [rbp+0x480]=rax+0x1C; 16 bytes from [0xF0FBDF8] stored at [rdi+0xC], 16 bytes from [0xF0FBDEC] stored at [rdi], rax saved at [rbp+0x478]; [rbp+0x2B0] zeroed. String #8 descriptor setup: ptr 0xF588EA6 stored at [rbp+0x30], len 0x17 stored at [rbp+0x38].

```
0x186ee8b  lea rdx,[rbp+0x20]
0x186ee8f  lea rsi,[rbp+0x470]
0x186ee96  mov rcx,[rbp+0x628]
0x186ee9d  mov r8,rsi
0x186eea0  mov r9d,0x23
0x186eea6  call 0x1870DE0
0x186eeab  nop
0x186eeac  mov rdi,[rbp+0x470]
0x186eeb3  test rdi,rdi
0x186eeb6  je short 0x186EECD
0x186eeb8  mov rcx,rdi
0x186eebb  call 0x2FE440
0x186eec0  mov edx,0x138
0x186eec5  mov rcx,rdi
0x186eec8  call 0xE935700
0x186eecd  xorps xmm0,xmm0
0x186eed0  movaps [rbp+0x470],xmm0
0x186eed7  mov qword ptr [rbp+0x480],0
0x186eee2  mov rcx,[0x1233E1A8]
0x186eee9  mov rax,[rcx]
0x186eeec  mov rax,[rax+8]
0x186eef0  mov edx,0x1C
0x186eef5  call qword ptr [0xF99FFA0]
0x186eefb  nop
0x186eefc  mov rdi,rax
0x186eeff  test rax,rax
0x186ef02  je 0x18701F1
0x186ef08  mov [rbp+0x470],rdi
0x186ef0f  mov rax,rdi
0x186ef12  add rax,0x1C
0x186ef16  mov [rbp+0x480],rax
0x186ef1d  movups xmm0,[0xF0FBDF8]
0x186ef24  movups [rdi+0xC],xmm0
0x186ef28  movups xmm0,[0xF0FBDEC]
0x186ef2f  movups [rdi],xmm0
0x186ef32  mov [rbp+0x478],rax
0x186ef39  mov qword ptr [rbp+0x2B0],0
0x186ef44  lea rax,[0xF588EA6]
0x186ef4b  mov [rbp+0x30],rax
0x186ef4f  mov qword ptr [rbp+0x38],0x17
```

### Phase 6: 0x186ef57..0x186f018 (40 instructions)
String #8 load: spills rsi, descriptor {ptr 0xF588EA6 at [rbp+0x30], len 0x17 at [rbp+0x38]}, calls 0x1870DE0 (r9d=0xE) into [rbp+0x2B0] [I]; non-null result released + zeroed, [rbp+0x2B0] cleared (movaps), [rbp+0x2C0] and [rbp+0x490] zeroed. String #9 load: descriptor {ptr 0xF54E3A0 at [rbp+0x40], len 0xD at [rbp+0x48]}, calls 0x1870DE0 (r9d=0xF) into [rbp+0x490] [I]; non-null result released + zeroed, then [rbp+0x490] cleared (movaps).

```
0x186ef57  mov [rsp+0x20],rsi
0x186ef5c  lea rdx,[rbp+0x30]
0x186ef60  lea rsi,[rbp+0x2B0]
0x186ef67  mov rcx,[rbp+0x628]
0x186ef6e  mov r8,rsi
0x186ef71  mov r9d,0xE
0x186ef77  call 0x1870DE0
0x186ef7c  nop
0x186ef7d  mov rdi,[rbp+0x2B0]
0x186ef84  test rdi,rdi
0x186ef87  je short 0x186EF9E
0x186ef89  mov rcx,rdi
0x186ef8c  call 0x2FE440
0x186ef91  mov edx,0x138
0x186ef96  mov rcx,rdi
0x186ef99  call 0xE935700
0x186ef9e  xorps xmm0,xmm0
0x186efa1  movaps [rbp+0x2B0],xmm0
0x186efa8  mov qword ptr [rbp+0x2C0],0
0x186efb3  mov qword ptr [rbp+0x490],0
0x186efbe  lea rax,[0xF54E3A0]
0x186efc5  mov [rbp+0x40],rax
0x186efc9  mov qword ptr [rbp+0x48],0xD
0x186efd1  mov [rsp+0x20],rsi
0x186efd6  lea rdx,[rbp+0x40]
0x186efda  lea rsi,[rbp+0x490]
0x186efe1  mov rcx,[rbp+0x628]
0x186efe8  mov r8,rsi
0x186efeb  mov r9d,0xF
0x186eff1  call 0x1870DE0
0x186eff6  nop
0x186eff7  mov rdi,[rbp+0x490]
0x186effe  test rdi,rdi
0x186f001  je short 0x186F018
0x186f003  mov rcx,rdi
0x186f006  call 0x2FE440
0x186f00b  mov edx,0x138
0x186f010  mov rcx,rdi
0x186f013  call 0xE935700
0x186f018  xorps xmm0,xmm0
```

### Phase 7: 0x186f01b..0x186f04a (10 instructions)
[r bp+0x490] cleared (movaps), [rbp+0x4A0] zeroed. Final object allocation via call qword ptr [0xF99FFA0] (edx=4, slots [0x1233E1A8]+0/+8) [V]; result in rax→rdi, then test rax,rax (slice ends mid-branch at 0x186f04a).

```
0x186f01b  movaps [rbp+0x490],xmm0
0x186f022  mov qword ptr [rbp+0x4A0],0
0x186f02d  mov rcx,[0x1233E1A8]
0x186f034  mov rax,[rcx]
0x186f037  mov rax,[rax+8]
0x186f03b  mov edx,4
0x186f040  call qword ptr [0xF99FFA0]
0x186f046  nop
0x186f047  mov rdi,rax
0x186f04a  test rax,rax
```

## Field map — every [reg+off] field stored or loaded in the slice

| offset | size | direction | verbatim instruction(s) | meaning |
|---|---|---|---|---|
| [rbp+0x450] | 16 | W/R | `0x186eb3a  mov qword ptr [rbp+0x450],0`<br>`0x186ebda  mov [rbp+0x450],rdi`<br>`0x186eba2  movaps [rbp+0x450],xmm0`<br>`0x186eb7e  mov rdi,[rbp+0x450]` | - |
| [rbp+0x460] | 8 | W | `0x186eba9  mov qword ptr [rbp+0x460],0`<br>`0x186ebe8  mov [rbp+0x460],rax` | - |
| [rbp+0x458] | 8 | W | `0x186ec00  mov [rbp+0x458],rax` | - |
| [rbp+0x210] | 16 | W/R | `0x186ec07  mov qword ptr [rbp+0x210],0`<br>`0x186ec6f  movaps [rbp+0x210],xmm0`<br>`0x186ec4b  mov rdi,[rbp+0x210]` | - |
| [rbp+0x220] | 8 | W | `0x186ec76  mov qword ptr [rbp+0x220],0` | - |
| [rbp+0x230] | 16 | W/R | `0x186ec81  mov qword ptr [rbp+0x230],0`<br>`0x186ece9  movaps [rbp+0x230],xmm0`<br>`0x186ecc5  mov rdi,[rbp+0x230]` | - |
| [rbp+0x240] | 8 | W | `0x186ecf0  mov qword ptr [rbp+0x240],0` | - |
| [rbp+0x250] | 16 | W/R | `0x186ecfb  mov qword ptr [rbp+0x250],0`<br>`0x186ed63  movaps [rbp+0x250],xmm0`<br>`0x186ed3f  mov rdi,[rbp+0x250]` | - |
| [rbp+0x260] | 8 | W | `0x186ed6a  mov qword ptr [rbp+0x260],0` | - |
| [rbp+0x270] | 16 | W/R | `0x186ed75  mov qword ptr [rbp+0x270],0`<br>`0x186eddc  movaps [rbp+0x270],xmm0`<br>`0x186edb8  mov rdi,[rbp+0x270]` | - |
| [rbp+0x280] | 8 | W | `0x186ede3  mov qword ptr [rbp+0x280],0` | - |
| [rbp+0x290] | 16 | W/R | `0x186edee  mov qword ptr [rbp+0x290],0`<br>`0x186ee56  movaps [rbp+0x290],xmm0`<br>`0x186ee32  mov rdi,[rbp+0x290]` | - |
| [rbp+0x2A0] | 8 | W | `0x186ee5d  mov qword ptr [rbp+0x2A0],0` | - |
| [rbp+0x470] | 16 | W/R | `0x186ee68  mov qword ptr [rbp+0x470],0`<br>`0x186eed0  movaps [rbp+0x470],xmm0`<br>`0x186eeac  mov rdi,[rbp+0x470]`<br>`0x186ef08  mov [rbp+0x470],rdi` | - |
| [rbp+0x480] | 8 | W | `0x186eed7  mov qword ptr [rbp+0x480],0`<br>`0x186ef16  mov [rbp+0x480],rax` | - |
| [rbp+0x478] | 8 | W | `0x186ef32  mov [rbp+0x478],rax` | - |
| [rbp+0x2B0] | 16 | W/R | `0x186ef39  mov qword ptr [rbp+0x2B0],0`<br>`0x186efa1  movaps [rbp+0x2B0],xmm0`<br>`0x186ef7d  mov rdi,[rbp+0x2B0]` | - |
| [rbp+0x2C0] | 8 | W | `0x186efa8  mov qword ptr [rbp+0x2C0],0` | - |
| [rbp+0x490] | 16 | W/R | `0x186efb3  mov qword ptr [rbp+0x490],0`<br>`0x186f01b  movaps [rbp+0x490],xmm0`<br>`0x186eff7  mov rdi,[rbp+0x490]` | - |
| [rbp+0x4A0] | 8 | W | `0x186f022  mov qword ptr [rbp+0x4A0],0` | - |
| [rbp-0x40] | 8 | W/R | `0x186eb4c  mov [rbp-0x40],rax`<br>`0x186eb5d  lea rdx,[rbp-0x40]` | - |
| [rbp-0x38] | 8 | W | `0x186eb50  mov qword ptr [rbp-0x38],0xE` | - |
| [rbp-0x30] | 8 | W/R | `0x186ec19  mov [rbp-0x30],rax`<br>`0x186ec2a  lea rdx,[rbp-0x30]` | - |
| [rbp-0x28] | 8 | W | `0x186ec1d  mov qword ptr [rbp-0x28],0x10` | - |
| [rbp-0x20] | 8 | W/R | `0x186ec93  mov [rbp-0x20],rax`<br>`0x186eca4  lea rdx,[rbp-0x20]` | - |
| [rbp-0x18] | 8 | W | `0x186ec97  mov qword ptr [rbp-0x18],0x13` | - |
| [rbp-0x10] | 8 | W/R | `0x186ed0d  mov [rbp-0x10],rax`<br>`0x186ed1e  lea rdx,[rbp-0x10]` | - |
| [rbp-8] | 8 | W | `0x186ed11  mov qword ptr [rbp-8],8` | - |
| [rbp+0x0] | 8 | W/R | `0x186ed87  mov [rbp],rax`<br>`0x186ed98  mov rdx,rbp` | - |
| [rbp+8] | 8 | W | `0x186ed8b  mov qword ptr [rbp+8],0xE` | - |
| [rbp+0x10] | 8 | W/R | `0x186ee00  mov [rbp+0x10],rax`<br>`0x186ee11  lea rdx,[rbp+0x10]` | - |
| [rbp+0x18] | 8 | W | `0x186ee04  mov qword ptr [rbp+0x18],8` | - |
| [rbp+0x20] | 8 | W/R | `0x186ee7a  mov [rbp+0x20],rax`<br>`0x186ee8b  lea rdx,[rbp+0x20]` | - |
| [rbp+0x28] | 8 | W | `0x186ee7e  mov qword ptr [rbp+0x28],0xC` | - |
| [rbp+0x30] | 8 | W/R | `0x186ef4b  mov [rbp+0x30],rax`<br>`0x186ef5c  lea rdx,[rbp+0x30]` | - |
| [rbp+0x38] | 8 | W | `0x186ef4f  mov qword ptr [rbp+0x38],0x17` | - |
| [rbp+0x40] | 8 | W/R | `0x186efc5  mov [rbp+0x40],rax`<br>`0x186efd6  lea rdx,[rbp+0x40]` | - |
| [rbp+0x48] | 8 | W | `0x186efc9  mov qword ptr [rbp+0x48],0xD` | - |
| [rsp+0x20] | 8 | W | `0x186eb58  mov [rsp+0x20],rsi`<br>`0x186ec25  mov [rsp+0x20],rsi`<br>`0x186ec9f  mov [rsp+0x20],rsi`<br>`0x186ed19  mov [rsp+0x20],rsi`<br>`0x186ed93  mov [rsp+0x20],rsi`<br>`0x186ee0c  mov [rsp+0x20],rsi`<br>`0x186ee86  mov [rsp+0x20],rsi`<br>`0x186efd1  mov [rsp+0x20],rsi` | - |
| [rdi] | 16 | W | `0x186ebf6  movups [rdi],xmm0`<br>`0x186ef2f  movups [rdi],xmm0` | - |
| [rdi+0x10] | 4 | W | `0x186ebf9  mov dword ptr [rdi+0x10],0xC` | - |
| [rdi+0xC] | 16 | W | `0x186ef24  movups [rdi+0xC],xmm0` | - |
| [rcx] | 8 | R | `0x186ebbb  mov rax,[rcx]`<br>`0x186eee9  mov rax,[rcx]`<br>`0x186f034  mov rax,[rcx]` | - |
| [rax+8] | 8 | R | `0x186ebbe  mov rax,[rax+8]`<br>`0x186eeec  mov rax,[rax+8]`<br>`0x186f037  mov rax,[rax+8]` | - |

## Notes
- Every instruction in the slice 0x186eb3a..0x186f04a (250 instructions) is covered by a phase above; none skipped.
- Immediate string pointers (lea rax,[0xF58E601] and similar) and call targets are not [reg+off] fields and are excluded from the field map; their meanings are not shown by any instruction or string literal, so '-' is used.
- [rcx] and [rax+8] loads are interface-vtable reads through slots [0x1233E1A8]+0/+8; the field meaning is not shown by any instruction/string, hence '-'.

## NEXT
DONE
