## NEXT
DONE

# UNIT U-Tl3 — texload slice 0x58a1ba4..0x58a1fcc (chunk 3 of 4 of texload_58a1310_58a23d0; texload 0x58a1310)

Instruction-complete dossier. Every instruction in the slice belongs to a phase; verbatim lines are copied from the disassembly. Field map lists every distinct [reg+off] load/store offset.

## Phases

### Phase 1: 0x58a1ba4..0x58a1c09 — store 1.0f (0x3F800000) to [rbp+0x94] and xmm8 to [rax+0x14], then compute a packed vector result from xmm7/xmm6/xmm4 constants and store xmm0 to [rbp+0xA8]
0x58a1ba4  mov dword ptr [rbp+0x94],0x3F800000
0x58a1bae  movups [rax+0x14],xmm8
0x58a1bb3  movaps xmm0,xmm7
0x58a1bb6  movaps xmm4,[0xF0A4080]
0x58a1bbd  mulps xmm0,xmm4
0x58a1bc0  movaps xmm1,xmm0
0x58a1bc3  shufps xmm1,xmm0,0x55
0x58a1bc7  addss xmm1,xmm0
0x58a1bcb  shufps xmm0,xmm0,0xE1
0x58a1bcf  subps xmm0,xmm7
0x58a1bd2  movaps xmm2,xmm6
0x58a1bd5  mulss xmm2,[0xEF5EAAC]
0x58a1bdd  movaps xmm3,xmm2
0x58a1be0  addss xmm3,xmm1
0x58a1be4  subss xmm1,xmm6
0x58a1be8  unpcklps xmm1,xmm3
0x58a1beb  addps xmm1,[0xEFD32F0]
0x58a1bf2  unpcklps xmm2,xmm2
0x58a1bf5  addps xmm2,xmm0
0x58a1bf8  movaps xmm0,xmm4
0x58a1bfb  movlhps xmm0,xmm2
0x58a1bfe  movss xmm2,[0xEEC8060]
0x58a1c06  addps xmm0,xmm2
0x58a1c09  movups [rbp+0xA8],xmm0

### Phase 2: 0x58a1c10..0x58a1c8d — store xmm1 to [rbp+0xB8], call 0xAA6580 with struct pointers [rbp+0xC0]/[rbp+0x80]/[rbp+0x110], copy the 16-byte struct from [rbp+0xC0..F0] to [rbp+0x110..140], then compute xmm7=[r13+0x70]*[0xEFD3334], call [0xF9A8E18] into xmm6, and xmm9=[0xEEC8060]-xmm0
0x58a1c10  movlps [rbp+0xB8],xmm1
0x58a1c17  lea rcx,[rbp+0xC0]
0x58a1c1e  lea rdx,[rbp+0x80]
0x58a1c25  lea r8,[rbp+0x110]
0x58a1c2c  call 0xAA6580
0x58a1c31  nop
0x58a1c32  movaps xmm0,[rbp+0xC0]
0x58a1c39  movaps xmm1,[rbp+0xD0]
0x58a1c40  movaps xmm2,[rbp+0xE0]
0x58a1c47  movaps xmm3,[rbp+0xF0]
0x58a1c4e  movaps [rbp+0x110],xmm0
0x58a1c55  movaps [rbp+0x120],xmm1
0x58a1c5c  movaps [rbp+0x130],xmm2
0x58a1c63  movaps [rbp+0x140],xmm3
0x58a1c6a  movss xmm7,[r13+0x70]
0x58a1c70  mulss xmm7,[0xEFD3334]
0x58a1c78  movaps xmm0,xmm7
0x58a1c7b  call qword ptr [0xF9A8E18]
0x58a1c81  movaps xmm6,xmm0
0x58a1c84  movss xmm9,[0xEEC8060]
0x58a1c8d  subss xmm9,xmm0

### Phase 3: 0x58a1c92..0x58a1d2f — call [0xF9A8F48] with xmm7 into xmm2, then build several shuffled/unpacked vectors (xmm9/xmm7/xmm1/xmm2/xmm3/xmm10/xmm4/xmm6/xmm5) using addps/mulps/subps/unpcklps/shufps/movlhps
0x58a1c92  movaps xmm0,xmm7
0x58a1c95  call qword ptr [0xF9A8F48]
0x58a1c9b  movaps xmm2,xmm0
0x58a1c9e  xorps xmm11,xmm11
0x58a1ca2  mulss xmm2,xmm11
0x58a1ca7  movaps xmm7,xmm6
0x58a1caa  addss xmm7,xmm9
0x58a1caf  unpcklps xmm9,xmm7
0x58a1cb3  mulps xmm9,xmm8
0x58a1cb7  movaps xmm1,xmm2
0x58a1cba  addss xmm1,xmm9
0x58a1cbf  movaps xmm5,xmm1
0x58a1cc2  mulss xmm5,xmm11
0x58a1cc7  unpcklps xmm2,xmm5
0x58a1cca  movaps xmm3,xmm9
0x58a1cce  subps xmm3,xmm2
0x58a1cd1  addps xmm2,xmm9
0x58a1cd5  movaps xmm10,xmm2
0x58a1cd9  shufps xmm10,xmm3,1
0x58a1cde  unpcklps xmm7,xmm1
0x58a1ce1  movaps xmm4,xmm3
0x58a1ce4  unpcklps xmm4,xmm9
0x58a1ce8  movss xmm9,xmm5
0x58a1ced  addps xmm9,xmm7
0x58a1cf1  shufps xmm9,xmm10,0x24
0x58a1cf6  mulps xmm4,xmm8
0x58a1cfa  movaps xmm10,xmm4
0x58a1cfe  shufps xmm10,xmm4,0x55
0x58a1d03  subss xmm10,xmm0
0x58a1d08  shufps xmm2,xmm4,1
0x58a1d0c  movaps xmm7,xmm10
0x58a1d10  mulss xmm7,xmm11
0x58a1d15  unpcklps xmm10,xmm6
0x58a1d19  movaps xmm6,xmm4
0x58a1d1c  movss xmm6,xmm5
0x58a1d20  addps xmm6,xmm10
0x58a1d24  addss xmm1,xmm7
0x58a1d28  addss xmm7,xmm5
0x58a1d2c  movaps xmm5,xmm7
0x58a1d2f  movlhps xmm1,xmm6

### Phase 4: 0x58a1d32..0x58a1df4 — finish vector blending with shufps/mulps/addps, store xmm4 to [rbp+0x80], xmm2 to [rbp+0x90], xmm1 to [rbp+0xA0], load constant [0xF0922E0] to [rbp+0xB0], then call 0xAA6580 again and copy [rbp+0xC0..F0] to [rbp+0x110..140]
0x58a1d32  shufps xmm7,xmm6,0xD4
0x58a1d36  shufps xmm6,xmm3,1
0x58a1d3a  shufps xmm0,xmm3,0xF4
0x58a1d3e  shufps xmm6,xmm0,0x82
0x58a1d42  shufps xmm6,xmm6,0x64
0x58a1d46  mulps xmm6,[0xF0F60E0]
0x58a1d4d  movaps xmm0,xmm6
0x58a1d50  shufps xmm0,xmm4,0xC7
0x58a1d54  shufps xmm0,xmm4,0x18
0x58a1d58  shufps xmm4,xmm2,0x80
0x58a1d5c  addps xmm4,xmm9
0x58a1d60  movaps [rbp+0x80],xmm4
0x58a1d67  addps xmm0,xmm6
0x58a1d6a  movaps xmm2,xmm0
0x58a1d6d  unpckhpd xmm2,xmm0
0x58a1d71  mulss xmm2,xmm11
0x58a1d76  shufps xmm2,xmm2,0x10
0x58a1d7a  addps xmm2,xmm0
0x58a1d7d  movaps [rbp+0x90],xmm2
0x58a1d84  shufps xmm5,xmm6,0xF4
0x58a1d88  shufps xmm5,xmm5,0x8A
0x58a1d8c  shufps xmm1,xmm7,0x28
0x58a1d90  addps xmm1,xmm5
0x58a1d93  movaps [rbp+0xA0],xmm1
0x58a1d9a  movaps xmm0,[0xF0922E0]
0x58a1da1  movaps [rbp+0xB0],xmm0
0x58a1da8  lea rcx,[rbp+0xC0]
0x58a1daf  lea rdx,[rbp+0x80]
0x58a1db6  lea r8,[rbp+0x110]
0x58a1dbd  call 0xAA6580
0x58a1dc2  nop
0x58a1dc3  movaps xmm0,[rbp+0xC0]
0x58a1dca  movaps xmm1,[rbp+0xD0]
0x58a1dd1  movaps xmm2,[rbp+0xE0]
0x58a1dd8  movaps xmm3,[rbp+0xF0]
0x58a1ddf  movaps [rbp+0x110],xmm0
0x58a1de6  movaps [rbp+0x120],xmm1
0x58a1ded  movaps [rbp+0x130],xmm2
0x58a1df4  movaps [rbp+0x140],xmm3

### Phase 5: 0x58a1dfb..0x58a1e8b — xmm7=[r13+0x74]*[0xEFD3334], call [0xF9A8E18]→xmm6 and call [0xF9A8F48]→(via xmm0), xmm3=[0xEEC8060]-xmm6, then build vectors with mulss/subss/addps/unpcklps/shufps/mulps and store xmm7 to [rbp+0x80]
0x58a1dfb  movss xmm7,[r13+0x74]
0x58a1e01  mulss xmm7,[0xEFD3334]
0x58a1e09  movaps xmm0,xmm7
0x58a1e0c  call qword ptr [0xF9A8E18]
0x58a1e12  movaps xmm6,xmm0
0x58a1e15  movaps xmm0,xmm7
0x58a1e18  call qword ptr [0xF9A8F48]
0x58a1e1e  movss xmm3,[0xEEC8060]
0x58a1e26  subss xmm3,xmm6
0x58a1e2a  movaps xmm2,xmm3
0x58a1e2d  xorps xmm10,xmm10
0x58a1e31  mulss xmm2,xmm10
0x58a1e36  movaps xmm1,xmm2
0x58a1e39  mulss xmm1,xmm10
0x58a1e3e  movaps xmm4,xmm2
0x58a1e41  unpcklps xmm4,xmm1
0x58a1e44  movaps xmm5,xmm1
0x58a1e47  subss xmm5,xmm0
0x58a1e4b  addss xmm1,xmm0
0x58a1e4f  mulss xmm0,xmm10
0x58a1e54  subss xmm2,xmm0
0x58a1e58  unpcklps xmm0,xmm6
0x58a1e5b  addps xmm4,xmm0
0x58a1e5e  movaps xmm7,xmm5
0x58a1e61  mulss xmm7,xmm10
0x58a1e66  movaps xmm0,xmm4
0x58a1e69  mulps xmm0,xmm8
0x58a1e6d  movaps xmm9,xmm0
0x58a1e71  movlhps xmm9,xmm0
0x58a1e75  unpcklps xmm7,xmm5
0x58a1e78  movaps xmm5,xmm4
0x58a1e7b  shufps xmm5,xmm0,0x11
0x58a1e7f  addps xmm9,xmm5
0x58a1e83  shufps xmm7,xmm7,0x10
0x58a1e87  addps xmm7,xmm9
0x58a1e8b  movaps [rbp+0x80],xmm7

### Phase 6: 0x58a1e92..0x58a1f49 — continue vector construction storing xmm4 to [rbp+0x90] and xmm0 to [rbp+0xA0], load [0xF0922E0] to [rbp+0xB0], call 0xAA6580, copy [rbp+0xC0..F0] to [rbp+0x110..140]
0x58a1e92  addss xmm3,xmm6
0x58a1e96  movlhps xmm4,xmm0
0x58a1e99  movaps xmm6,xmm0
0x58a1e9c  shufps xmm6,xmm4,0x80
0x58a1ea0  movaps xmm4,xmm2
0x58a1ea3  unpcklps xmm4,xmm3
0x58a1ea6  unpcklps xmm3,xmm2
0x58a1ea9  mulps xmm3,xmm8
0x58a1ead  shufps xmm2,xmm3,0xD4
0x58a1eb1  movlhps xmm3,xmm3
0x58a1eb4  movlhps xmm4,xmm4
0x58a1eb7  mulps xmm4,[0xEFD3400]
0x58a1ebe  addps xmm4,xmm3
0x58a1ec1  addps xmm4,xmm6
0x58a1ec4  movaps [rbp+0x90],xmm4
0x58a1ecb  movaps xmm3,xmm1
0x58a1ece  mulss xmm3,xmm10
0x58a1ed3  unpcklps xmm1,xmm3
0x58a1ed6  shufps xmm2,xmm2,0xA2
0x58a1eda  shufps xmm1,xmm1,0x54
0x58a1ede  addps xmm1,xmm2
0x58a1ee1  shufps xmm0,xmm5,0x85
0x58a1ee5  addps xmm0,xmm1
0x58a1ee8  movaps [rbp+0xA0],xmm0
0x58a1eef  movaps xmm0,[0xF0922E0]
0x58a1ef6  movaps [rbp+0xB0],xmm0
0x58a1efd  lea rcx,[rbp+0xC0]
0x58a1f04  lea rdx,[rbp+0x80]
0x58a1f0b  lea r8,[rbp+0x110]
0x58a1f12  call 0xAA6580
0x58a1f17  nop
0x58a1f18  movaps xmm0,[rbp+0xC0]
0x58a1f1f  movaps xmm1,[rbp+0xD0]
0x58a1f26  movaps xmm2,[rbp+0xE0]
0x58a1f2d  movaps xmm3,[rbp+0xF0]
0x58a1f34  movaps [rbp+0x110],xmm0
0x58a1f3b  movaps [rbp+0x120],xmm1
0x58a1f42  movaps [rbp+0x130],xmm2
0x58a1f49  movaps [rbp+0x140],xmm3

### Phase 7: 0x58a1f50..0x58a1fcc — xmm7=[r13+0x78]*[0xEFD3334], call [0xF9A8E18]→xmm6 and call [0xF9A8F48]→(via xmm0), xmm1=[0xEEC8060]-xmm6, then final vector blend ending at unpcklps xmm5,xmm10
0x58a1f50  movss xmm7,[r13+0x78]
0x58a1f56  mulss xmm7,[0xEFD3334]
0x58a1f5e  movaps xmm0,xmm7
0x58a1f61  call qword ptr [0xF9A8E18]
0x58a1f67  movaps xmm6,xmm0
0x58a1f6a  movaps xmm0,xmm7
0x58a1f6d  call qword ptr [0xF9A8F48]
0x58a1f73  movss xmm1,[0xEEC8060]
0x58a1f7b  subss xmm1,xmm6
0x58a1f7f  movaps xmm4,xmm1
0x58a1f82  mulss xmm4,xmm11
0x58a1f87  movaps xmm7,xmm4
0x58a1f8a  mulss xmm7,xmm11
0x58a1f8f  movaps xmm5,xmm7
0x58a1f92  subss xmm5,xmm0
0x58a1f96  movaps xmm2,xmm6
0x58a1f99  unpcklps xmm2,xmm0
0x58a1f9c  movaps xmm9,xmm0
0x58a1fa0  mulss xmm9,xmm11
0x58a1fa5  shufps xmm7,xmm7,0
0x58a1fa9  addps xmm7,xmm2
0x58a1fac  movaps xmm0,xmm7
0x58a1faf  mulps xmm0,xmm8
0x58a1fb3  movaps xmm2,xmm0
0x58a1fb6  shufps xmm2,xmm0,0xE1
0x58a1fba  movaps xmm3,xmm7
0x58a1fbd  addps xmm3,xmm2
0x58a1fc0  addps xmm2,xmm0
0x58a1fc3  movaps xmm10,xmm5
0x58a1fc7  mulss xmm10,xmm11
0x58a1fcc  unpcklps xmm5,xmm10

## Field map — every distinct [reg+off] load/store offset

| offset | size | direction | verbatim line | meaning |
|---|---|---|---|---|
| rbp+0x94 | 4 | W | 0x58a1ba4  mov dword ptr [rbp+0x94],0x3F800000 | - |
| rbp+0xA8 | 16 | W | 0x58a1c09  movups [rbp+0xA8],xmm0 | - |
| rbp+0xB8 | 8 | W | 0x58a1c10  movlps [rbp+0xB8],xmm1 | - |
| rbp+0xC0 | 16 | R | 0x58a1c32  movaps xmm0,[rbp+0xC0] ; 0x58a1dc3  movaps xmm0,[rbp+0xC0] ; 0x58a1f18  movaps xmm0,[rbp+0xC0] | - |
| rbp+0xD0 | 16 | R | 0x58a1c39  movaps xmm1,[rbp+0xD0] ; 0x58a1dca  movaps xmm1,[rbp+0xD0] ; 0x58a1f1f  movaps xmm1,[rbp+0xD0] | - |
| rbp+0xE0 | 16 | R | 0x58a1c40  movaps xmm2,[rbp+0xE0] ; 0x58a1dd1  movaps xmm2,[rbp+0xE0] ; 0x58a1f26  movaps xmm2,[rbp+0xE0] | - |
| rbp+0xF0 | 16 | R | 0x58a1c47  movaps xmm3,[rbp+0xF0] ; 0x58a1dd8  movaps xmm3,[rbp+0xF0] ; 0x58a1f2d  movaps xmm3,[rbp+0xF0] | - |
| rbp+0x110 | 16 | W | 0x58a1c4e  movaps [rbp+0x110],xmm0 ; 0x58a1ddf  movaps [rbp+0x110],xmm0 ; 0x58a1f34  movaps [rbp+0x110],xmm0 | - |
| rbp+0x120 | 16 | W | 0x58a1c55  movaps [rbp+0x120],xmm1 ; 0x58a1de6  movaps [rbp+0x120],xmm1 ; 0x58a1f3b  movaps [rbp+0x120],xmm1 | - |
| rbp+0x130 | 16 | W | 0x58a1c5c  movaps [rbp+0x130],xmm2 ; 0x58a1ded  movaps [rbp+0x130],xmm2 ; 0x58a1f42  movaps [rbp+0x130],xmm2 | - |
| rbp+0x140 | 16 | W | 0x58a1c63  movaps [rbp+0x140],xmm3 ; 0x58a1df4  movaps [rbp+0x140],xmm3 ; 0x58a1f49  movaps [rbp+0x140],xmm3 | - |
| rbp+0x80 | 16 | W | 0x58a1d60  movaps [rbp+0x80],xmm4 ; 0x58a1e8b  movaps [rbp+0x80],xmm7 | - |
| rbp+0x90 | 16 | W | 0x58a1d7d  movaps [rbp+0x90],xmm2 ; 0x58a1ec4  movaps [rbp+0x90],xmm4 | - |
| rbp+0xA0 | 16 | W | 0x58a1d93  movaps [rbp+0xA0],xmm1 ; 0x58a1ee8  movaps [rbp+0xA0],xmm0 | - |
| rbp+0xB0 | 16 | W | 0x58a1da1  movaps [rbp+0xB0],xmm0 ; 0x58a1ef6  movaps [rbp+0xB0],xmm0 | - |
| rax+0x14 | 16 | W | 0x58a1bae  movups [rax+0x14],xmm8 | - |
| r13+0x70 | 4 | R | 0x58a1c6a  movss xmm7,[r13+0x70] | - |
| r13+0x74 | 4 | R | 0x58a1dfb  movss xmm7,[r13+0x74] | - |
| r13+0x78 | 4 | R | 0x58a1f50  movss xmm7,[r13+0x78] | - |

## TOOL REQUESTS

None
