## NEXT
DONE

# ClientInstance::loadResources — instruction slice 0x186f04d..0x186f5b0 (chunk 3 of 6)
Function: ClientInstance::loadResources at 0x186e6a0. Slice: 0x186f04d..0x186f5b0 (250 instructions).
Source: docs/progress/_part_Lr3.txt (precomputed by the orchestrator; not re-derived).
Register map (observed): rcx = this/context pointer, reloaded from [rbp+0x628] before each 0x1870DE0 call; rdi = resource handle / call return value; rax = scratch and end pointer; rsi = destination buffer; rdx = descriptor source pointer; r8 = destination; r9d = small length/tag immediate. Calls: 0x1870DE0 (descriptor load), 0x2FE440 then 0xE935700 (release with edx=0x138), interface method qword [0xF99FFA0] (edx=4 then edx=8).

## Phases (instruction-complete; every instruction covered; verbatim lines listed under each phase)

### Phase 1: 0x186f04d..0x186f0d5 — On the not-taken path, store handle rdi at [rbp+0x490] and handle+4 at [rbp+0x4A0], write dword tag 0xF at [rdi], save [rbp+0x498], zero [rbp+0x2D0], build a descriptor at [rbp+0x50] (pointer to string const 0xF55A8EB, length 0x16) and call 0x1870DE0 (r9d=0x10), then reload [rbp+0x2D0] and release it via 0x2FE440/0xE935700 with edx=0x138.
0x186f04d  je 0x1870201
0x186f053  mov [rbp+0x490],rdi
0x186f05a  mov rax,rdi
0x186f05d  add rax,4
0x186f061  mov [rbp+0x4A0],rax
0x186f068  mov dword ptr [rdi],0xF
0x186f06e  mov [rbp+0x498],rax
0x186f075  mov qword ptr [rbp+0x2D0],0
0x186f080  lea rax,[0xF55A8EB]
0x186f087  mov [rbp+0x50],rax
0x186f08b  mov qword ptr [rbp+0x58],0x16
0x186f093  mov [rsp+0x20],rsi
0x186f098  lea rdx,[rbp+0x50]
0x186f09c  lea rsi,[rbp+0x2D0]
0x186f0a3  mov rcx,[rbp+0x628]
0x186f0aa  mov r8,rsi
0x186f0ad  mov r9d,0x10
0x186f0b3  call 0x1870DE0
0x186f0b8  nop
0x186f0b9  mov rdi,[rbp+0x2D0]
0x186f0c0  test rdi,rdi
0x186f0c3  je short 0x186F0DA
0x186f0c5  mov rcx,rdi
0x186f0c8  call 0x2FE440
0x186f0cd  mov edx,0x138
0x186f0d2  mov rcx,rdi
0x186f0d5  call 0xE935700

### Phase 2: 0x186f0da..0x186f189 — Zero [rbp+0x2D0] with a 16-byte movaps and [rbp+0x2E0], zero [rbp+0x4B0], build descriptor at [rbp+0x60] (pointer to string const 0xF543FAA, length 0x13) and call 0x1870DE0 (r9d=0x11), reload [rbp+0x4B0] and release it via 0x2FE440/0xE935700, zero [rbp+0x4B0] (movaps) and [rbp+0x4C0], then load the global at [0x1233E1A8], follow [rcx] and [rax+8], call interface method qword [0xF99FFA0] with edx=4 and test the result.
0x186f0da  xorps xmm0,xmm0
0x186f0dd  movaps [rbp+0x2D0],xmm0
0x186f0e4  mov qword ptr [rbp+0x2E0],0
0x186f0ef  mov qword ptr [rbp+0x4B0],0
0x186f0fa  lea rax,[0xF543FAA]
0x186f101  mov [rbp+0x60],rax
0x186f105  mov qword ptr [rbp+0x68],0x13
0x186f10d  mov [rsp+0x20],rsi
0x186f112  lea rdx,[rbp+0x60]
0x186f116  lea rsi,[rbp+0x4B0]
0x186f11d  mov rcx,[rbp+0x628]
0x186f124  mov r8,rsi
0x186f127  mov r9d,0x11
0x186f12d  call 0x1870DE0
0x186f132  nop
0x186f133  mov rdi,[rbp+0x4B0]
0x186f13a  test rdi,rdi
0x186f13d  je short 0x186F154
0x186f13f  mov rcx,rdi
0x186f142  call 0x2FE440
0x186f147  mov edx,0x138
0x186f14c  mov rcx,rdi
0x186f14f  call 0xE935700
0x186f154  xorps xmm0,xmm0
0x186f157  movaps [rbp+0x4B0],xmm0
0x186f15e  mov qword ptr [rbp+0x4C0],0
0x186f169  mov rcx,[0x1233E1A8]
0x186f170  mov rax,[rcx]
0x186f173  mov rax,[rax+8]
0x186f177  mov edx,4
0x186f17c  call qword ptr [0xF99FFA0]
0x186f182  nop
0x186f183  mov rdi,rax
0x186f186  test rax,rax
0x186f189  je 0x1870211

### Phase 3: 0x186f18f..0x186f272 — Store fresh handle rdi at [rbp+0x4B0] and handle+4 at [rbp+0x4C0], write dword tag 0x11 at [rdi], save [rbp+0x4B8], zero [rbp+0x2F0], build descriptor at [rbp+0x70] (pointer to string const 0xF545CB4, length 0x13) and call 0x1870DE0 (r9d=0x12); then reload [rbp+0x2F0] and release it via 0x2FE440/0xE935700, zero [rbp+0x2F0] (movaps), [rbp+0x300] and [rbp+0x310], build descriptor at [rbp+0x80] (pointer to string const 0xF5ED23A, length 5) and call 0x1870DE0 (r9d=2).
0x186f18f  mov [rbp+0x4B0],rdi
0x186f196  mov rax,rdi
0x186f199  add rax,4
0x186f19d  mov [rbp+0x4C0],rax
0x186f1a4  mov dword ptr [rdi],0x11
0x186f1aa  mov [rbp+0x4B8],rax
0x186f1b1  mov qword ptr [rbp+0x2F0],0
0x186f1bc  lea rax,[0xF545CB4]
0x186f1c3  mov [rbp+0x70],rax
0x186f1c7  mov qword ptr [rbp+0x78],0x13
0x186f1cf  mov [rsp+0x20],rsi
0x186f1d4  lea rdx,[rbp+0x70]
0x186f1d8  lea rsi,[rbp+0x2F0]
0x186f1df  mov rcx,[rbp+0x628]
0x186f1e6  mov r8,rsi
0x186f1e9  mov r9d,0x12
0x186f1ef  call 0x1870DE0
0x186f1f4  nop
0x186f1f5  mov rdi,[rbp+0x2F0]
0x186f1fc  test rdi,rdi
0x186f1ff  je short 0x186F216
0x186f201  mov rcx,rdi
0x186f204  call 0x2FE440
0x186f209  mov edx,0x138
0x186f20e  mov rcx,rdi
0x186f211  call 0xE935700
0x186f216  xorps xmm0,xmm0
0x186f219  movaps [rbp+0x2F0],xmm0
0x186f220  mov qword ptr [rbp+0x300],0
0x186f22b  mov qword ptr [rbp+0x310],0
0x186f236  lea rax,[0xF5ED23A]
0x186f23d  mov [rbp+0x80],rax
0x186f244  mov qword ptr [rbp+0x88],5
0x186f24f  mov [rsp+0x20],rsi
0x186f254  lea rdx,[rbp+0x80]
0x186f25b  lea rsi,[rbp+0x310]
0x186f262  mov rcx,[rbp+0x628]
0x186f269  mov r8,rsi
0x186f26c  mov r9d,2
0x186f272  call 0x1870DE0

### Phase 4: 0x186f277..0x186f34a — Release [rbp+0x310] via 0x2FE440/0xE935700, zero [rbp+0x310] (movaps), [rbp+0x320] and [rbp+0x330], build descriptor at [rbp+0x90] (pointer to string const 0xF58907B, length 0xF) and call 0x1870DE0 (r9d=3), reload [rbp+0x330] and release it, zero [rbp+0x330] (movaps), [rbp+0x340] and [rbp+0x350], and build descriptor at [rbp+0xA0] (pointer to string const 0xF5A66B5, length 8).
0x186f277  nop
0x186f278  mov rdi,[rbp+0x310]
0x186f27f  test rdi,rdi
0x186f282  je short 0x186F299
0x186f284  mov rcx,rdi
0x186f287  call 0x2FE440
0x186f28c  mov edx,0x138
0x186f291  mov rcx,rdi
0x186f294  call 0xE935700
0x186f299  xorps xmm0,xmm0
0x186f29c  movaps [rbp+0x310],xmm0
0x186f2a3  mov qword ptr [rbp+0x320],0
0x186f2ae  mov qword ptr [rbp+0x330],0
0x186f2b9  lea rax,[0xF58907B]
0x186f2c0  mov [rbp+0x90],rax
0x186f2c7  mov qword ptr [rbp+0x98],0xF
0x186f2d2  mov [rsp+0x20],rsi
0x186f2d7  lea rdx,[rbp+0x90]
0x186f2de  lea rsi,[rbp+0x330]
0x186f2e5  mov rcx,[rbp+0x628]
0x186f2ec  mov r8,rsi
0x186f2ef  mov r9d,3
0x186f2f5  call 0x1870DE0
0x186f2fa  nop
0x186f2fb  mov rdi,[rbp+0x330]
0x186f302  test rdi,rdi
0x186f305  je short 0x186F31C
0x186f307  mov rcx,rdi
0x186f30a  call 0x2FE440
0x186f30f  mov edx,0x138
0x186f314  mov rcx,rdi
0x186f317  call 0xE935700
0x186f31c  xorps xmm0,xmm0
0x186f31f  movaps [rbp+0x330],xmm0
0x186f326  mov qword ptr [rbp+0x340],0
0x186f331  mov qword ptr [rbp+0x350],0
0x186f33c  lea rax,[0xF5A66B5]
0x186f343  mov [rbp+0xA0],rax
0x186f34a  mov qword ptr [rbp+0xA8],8

### Phase 5: 0x186f355..0x186f41d — Spill rsi, complete the [rbp+0xA0]/[rbp+0x350] descriptor call (r9d=0xC), reload [rbp+0x350] and release it, zero [rbp+0x350] (movaps), [rbp+0x360] and [rbp+0x370], build descriptor at [rbp+0xB0] (pointer to string const 0xF5C701E, length 7) and call 0x1870DE0 (r9d=1), then reload [rbp+0x370] and release it.
0x186f355  mov [rsp+0x20],rsi
0x186f35a  lea rdx,[rbp+0xA0]
0x186f361  lea rsi,[rbp+0x350]
0x186f368  mov rcx,[rbp+0x628]
0x186f36f  mov r8,rsi
0x186f372  mov r9d,0xC
0x186f378  call 0x1870DE0
0x186f37d  nop
0x186f37e  mov rdi,[rbp+0x350]
0x186f385  test rdi,rdi
0x186f388  je short 0x186F39F
0x186f38a  mov rcx,rdi
0x186f38d  call 0x2FE440
0x186f392  mov edx,0x138
0x186f397  mov rcx,rdi
0x186f39a  call 0xE935700
0x186f39f  xorps xmm0,xmm0
0x186f3a2  movaps [rbp+0x350],xmm0
0x186f3a9  mov qword ptr [rbp+0x360],0
0x186f3b4  mov qword ptr [rbp+0x370],0
0x186f3bf  lea rax,[0xF5C701E]
0x186f3c6  mov [rbp+0xB0],rax
0x186f3cd  mov qword ptr [rbp+0xB8],7
0x186f3d8  mov [rsp+0x20],rsi
0x186f3dd  lea rdx,[rbp+0xB0]
0x186f3e4  lea rsi,[rbp+0x370]
0x186f3eb  mov rcx,[rbp+0x628]
0x186f3f2  mov r8,rsi
0x186f3f5  mov r9d,1
0x186f3fb  call 0x1870DE0
0x186f400  nop
0x186f401  mov rdi,[rbp+0x370]
0x186f408  test rdi,rdi
0x186f40b  je short 0x186F422
0x186f40d  mov rcx,rdi
0x186f410  call 0x2FE440
0x186f415  mov edx,0x138
0x186f41a  mov rcx,rdi
0x186f41d  call 0xE935700

### Phase 6: 0x186f422..0x186f501 — Zero [rbp+0x370] (movaps), [rbp+0x380] and [rbp+0x390], build descriptor at [rbp+0xC0] (pointer to string const 0xF5AFF69, length 9) and call 0x1870DE0 (r9d=9), reload [rbp+0x390] and release it, zero [rbp+0x390] (movaps), [rbp+0x3A0] and [rbp+0x4D0], build descriptor at [rbp+0xD0] (pointer to string const 0xF58C410, length 0xC) and call 0x1870DE0 (r9d=4).
0x186f422  xorps xmm0,xmm0
0x186f425  movaps [rbp+0x370],xmm0
0x186f42c  mov qword ptr [rbp+0x380],0
0x186f437  mov qword ptr [rbp+0x390],0
0x186f442  lea rax,[0xF5AFF69]
0x186f449  mov [rbp+0xC0],rax
0x186f450  mov qword ptr [rbp+0xC8],9
0x186f45b  mov [rsp+0x20],rsi
0x186f460  lea rdx,[rbp+0xC0]
0x186f467  lea rsi,[rbp+0x390]
0x186f46e  mov rcx,[rbp+0x628]
0x186f475  mov r8,rsi
0x186f478  mov r9d,9
0x186f47e  call 0x1870DE0
0x186f483  nop
0x186f484  mov rdi,[rbp+0x390]
0x186f48b  test rdi,rdi
0x186f48e  je short 0x186F4A5
0x186f490  mov rcx,rdi
0x186f493  call 0x2FE440
0x186f498  mov edx,0x138
0x186f49d  mov rcx,rdi
0x186f4a0  call 0xE935700
0x186f4a5  xorps xmm0,xmm0
0x186f4a8  movaps [rbp+0x390],xmm0
0x186f4af  mov qword ptr [rbp+0x3A0],0
0x186f4ba  mov qword ptr [rbp+0x4D0],0
0x186f4c5  lea rax,[0xF58C410]
0x186f4cc  mov [rbp+0xD0],rax
0x186f4d3  mov qword ptr [rbp+0xD8],0xC
0x186f4de  mov [rsp+0x20],rsi
0x186f4e3  lea rdx,[rbp+0xD0]
0x186f4ea  lea rsi,[rbp+0x4D0]
0x186f4f1  mov rcx,[rbp+0x628]
0x186f4f8  mov r8,rsi
0x186f4fb  mov r9d,4
0x186f501  call 0x1870DE0

### Phase 7: 0x186f506..0x186f5b0 — Release [rbp+0x4D0] via 0x2FE440/0xE935700, zero [rbp+0x4D0] (movaps) and [rbp+0x4E0], load the global at [0x1233E1A8], follow [rcx] and [rax+8], call interface method qword [0xF99FFA0] with edx=8; on success store handle at [rbp+0x4D0], handle+8 at [rbp+0x4E0], write qword 0x60000000A at [rdi], save [rbp+0x4D8]; zero [rbp+0x4F0] and build descriptor at [rbp+0xE0] (pointer to string const 0xF560778, length 0xB).
0x186f506  nop
0x186f507  mov rdi,[rbp+0x4D0]
0x186f50e  test rdi,rdi
0x186f511  je short 0x186F528
0x186f513  mov rcx,rdi
0x186f516  call 0x2FE440
0x186f51b  mov edx,0x138
0x186f520  mov rcx,rdi
0x186f523  call 0xE935700
0x186f528  xorps xmm0,xmm0
0x186f52b  movaps [rbp+0x4D0],xmm0
0x186f532  mov qword ptr [rbp+0x4E0],0
0x186f53d  mov rcx,[0x1233E1A8]
0x186f544  mov rax,[rcx]
0x186f547  mov rax,[rax+8]
0x186f54b  mov edx,8
0x186f550  call qword ptr [0xF99FFA0]
0x186f556  nop
0x186f557  mov rdi,rax
0x186f55a  test rax,rax
0x186f55d  je 0x1870221
0x186f563  mov [rbp+0x4D0],rdi
0x186f56a  mov rax,rdi
0x186f56d  add rax,8
0x186f571  mov [rbp+0x4E0],rax
0x186f578  mov rcx,0x60000000A
0x186f582  mov [rdi],rcx
0x186f585  mov [rbp+0x4D8],rax
0x186f58c  mov qword ptr [rbp+0x4F0],0
0x186f597  lea rax,[0xF560778]
0x186f59e  mov [rbp+0xE0],rax
0x186f5a5  mov qword ptr [rbp+0xE8],0xB
0x186f5b0  mov [rsp+0x20],rsi

## Field map — every [reg+off] field stored or loaded in the slice (one row per distinct offset; all sites listed; verbatim lines for each site also appear verbatim in the phases above)
| offset | size | direction | site(s) — verbatim `0xRVA  instr` | meaning |
| rbp+0x490 | 8 | W | 0x186f053  mov [rbp+0x490],rdi | resource handle (rdi) |
| rbp+0x4A0 | 8 | W | 0x186f061  mov [rbp+0x4A0],rax | handle+4 end pointer |
| rdi+0x0 | 4 (dword) / 8 (qword) | W | 0x186f068  mov dword ptr [rdi],0xF ; 0x186f1a4  mov dword ptr [rdi],0x11 ; 0x186f582  mov [rdi],rcx | dword tag 0xF then 0x11, then qword 0x60000000A |
| rbp+0x498 | 8 | W | 0x186f06e  mov [rbp+0x498],rax | - |
| rbp+0x2D0 | 16 (movaps) / 8 (qword) | R/W | 0x186f075  mov qword ptr [rbp+0x2D0],0 ; 0x186f09c  lea rsi,[rbp+0x2D0] ; 0x186f0b9  mov rdi,[rbp+0x2D0] ; 0x186f0dd  movaps [rbp+0x2D0],xmm0 | destination buffer / string out-param (lea'd as rsi arg) |
| rbp+0x50 | 8 | R/W | 0x186f087  mov [rbp+0x50],rax ; 0x186f098  lea rdx,[rbp+0x50] | ptr to string const 0xF55A8EB |
| rbp+0x58 | 8 | W | 0x186f08b  mov qword ptr [rbp+0x58],0x16 | length 0x16 |
| rsp+0x20 | 8 | W | 0x186f093  mov [rsp+0x20],rsi ; 0x186f10d  mov [rsp+0x20],rsi ; 0x186f1cf  mov [rsp+0x20],rsi ; 0x186f24f  mov [rsp+0x20],rsi ; 0x186f2d2  mov [rsp+0x20],rsi ; 0x186f355  mov [rsp+0x20],rsi ; 0x186f3d8  mov [rsp+0x20],rsi ; 0x186f45b  mov [rsp+0x20],rsi ; 0x186f4de  mov [rsp+0x20],rsi ; 0x186f5b0  mov [rsp+0x20],rsi | spill slot for rsi |
| rbp+0x2E0 | 8 | W | 0x186f0e4  mov qword ptr [rbp+0x2E0],0 | - |
| rbp+0x4B0 | 16 (movaps) / 8 (qword) | R/W | 0x186f0ef  mov qword ptr [rbp+0x4B0],0 ; 0x186f116  lea rsi,[rbp+0x4B0] ; 0x186f133  mov rdi,[rbp+0x4B0] ; 0x186f157  movaps [rbp+0x4B0],xmm0 ; 0x186f18f  mov [rbp+0x4B0],rdi | next resource handle |
| rbp+0x60 | 8 | R/W | 0x186f101  mov [rbp+0x60],rax ; 0x186f112  lea rdx,[rbp+0x60] | ptr to string const 0xF543FAA |
| rbp+0x68 | 8 | W | 0x186f105  mov qword ptr [rbp+0x68],0x13 | length 0x13 |
| rbp+0x4C0 | 8 | W | 0x186f15e  mov qword ptr [rbp+0x4C0],0 ; 0x186f19d  mov [rbp+0x4C0],rax | end pointer (handle+4 / handle+8) |
| rcx+0x0 | 8 | R | 0x186f170  mov rax,[rcx] ; 0x186f544  mov rax,[rcx] | interface first pointer (from global [0x1233E1A8]) |
| rax+8 | 8 | R | 0x186f173  mov rax,[rax+8] ; 0x186f547  mov rax,[rax+8] | interface second pointer |
| rbp+0x4B8 | 8 | W | 0x186f1aa  mov [rbp+0x4B8],rax | - |
| rbp+0x2F0 | 16 (movaps) / 8 (qword) | R/W | 0x186f1b1  mov qword ptr [rbp+0x2F0],0 ; 0x186f1d8  lea rsi,[rbp+0x2F0] ; 0x186f1f5  mov rdi,[rbp+0x2F0] ; 0x186f219  movaps [rbp+0x2F0],xmm0 | destination buffer / string out-param |
| rbp+0x70 | 8 | R/W | 0x186f1c3  mov [rbp+0x70],rax ; 0x186f1d4  lea rdx,[rbp+0x70] | ptr to string const 0xF545CB4 |
| rbp+0x78 | 8 | W | 0x186f1c7  mov qword ptr [rbp+0x78],0x13 | length 0x13 |
| rbp+0x300 | 8 | W | 0x186f220  mov qword ptr [rbp+0x300],0 | - |
| rbp+0x310 | 16 (movaps) / 8 (qword) | R/W | 0x186f22b  mov qword ptr [rbp+0x310],0 ; 0x186f25b  lea rsi,[rbp+0x310] ; 0x186f278  mov rdi,[rbp+0x310] ; 0x186f29c  movaps [rbp+0x310],xmm0 | destination buffer / string out-param |
| rbp+0x80 | 8 | R/W | 0x186f23d  mov [rbp+0x80],rax ; 0x186f254  lea rdx,[rbp+0x80] | ptr to string const 0xF5ED23A |
| rbp+0x88 | 8 | W | 0x186f244  mov qword ptr [rbp+0x88],5 | length 5 |
| rbp+0x320 | 8 | W | 0x186f2a3  mov qword ptr [rbp+0x320],0 | - |
| rbp+0x330 | 16 (movaps) / 8 (qword) | R/W | 0x186f2ae  mov qword ptr [rbp+0x330],0 ; 0x186f2de  lea rsi,[rbp+0x330] ; 0x186f2fb  mov rdi,[rbp+0x330] ; 0x186f31f  movaps [rbp+0x330],xmm0 | destination buffer / string out-param |
| rbp+0x90 | 8 | R/W | 0x186f2c0  mov [rbp+0x90],rax ; 0x186f2d7  lea rdx,[rbp+0x90] | ptr to string const 0xF58907B |
| rbp+0x98 | 8 | W | 0x186f2c7  mov qword ptr [rbp+0x98],0xF | length 0xF |
| rbp+0x340 | 8 | W | 0x186f326  mov qword ptr [rbp+0x340],0 | - |
| rbp+0x350 | 16 (movaps) / 8 (qword) | R/W | 0x186f331  mov qword ptr [rbp+0x350],0 ; 0x186f361  lea rsi,[rbp+0x350] ; 0x186f37e  mov rdi,[rbp+0x350] ; 0x186f3a2  movaps [rbp+0x350],xmm0 | destination buffer / string out-param |
| rbp+0xA0 | 8 | R/W | 0x186f343  mov [rbp+0xA0],rax ; 0x186f35a  lea rdx,[rbp+0xA0] | ptr to string const 0xF5A66B5 |
| rbp+0xA8 | 8 | W | 0x186f34a  mov qword ptr [rbp+0xA8],8 | length 8 |
| rbp+0x360 | 8 | W | 0x186f3a9  mov qword ptr [rbp+0x360],0 | - |
| rbp+0x370 | 16 (movaps) / 8 (qword) | R/W | 0x186f3b4  mov qword ptr [rbp+0x370],0 ; 0x186f3e4  lea rsi,[rbp+0x370] ; 0x186f401  mov rdi,[rbp+0x370] ; 0x186f425  movaps [rbp+0x370],xmm0 | destination buffer / string out-param |
| rbp+0xB0 | 8 | R/W | 0x186f3c6  mov [rbp+0xB0],rax ; 0x186f3dd  lea rdx,[rbp+0xB0] | ptr to string const 0xF5C701E |
| rbp+0xB8 | 8 | W | 0x186f3cd  mov qword ptr [rbp+0xB8],7 | length 7 |
| rbp+0x380 | 8 | W | 0x186f42c  mov qword ptr [rbp+0x380],0 | - |
| rbp+0x390 | 16 (movaps) / 8 (qword) | R/W | 0x186f437  mov qword ptr [rbp+0x390],0 ; 0x186f467  lea rsi,[rbp+0x390] ; 0x186f484  mov rdi,[rbp+0x390] ; 0x186f4a8  movaps [rbp+0x390],xmm0 | destination buffer / string out-param |
| rbp+0xC0 | 8 | R/W | 0x186f449  mov [rbp+0xC0],rax ; 0x186f460  lea rdx,[rbp+0xC0] | ptr to string const 0xF5AFF69 |
| rbp+0xC8 | 8 | W | 0x186f450  mov qword ptr [rbp+0xC8],9 | length 9 |
| rbp+0x3A0 | 8 | W | 0x186f4af  mov qword ptr [rbp+0x3A0],0 | - |
| rbp+0x4D0 | 16 (movaps) / 8 (qword) | R/W | 0x186f4ba  mov qword ptr [rbp+0x4D0],0 ; 0x186f4ea  lea rsi,[rbp+0x4D0] ; 0x186f507  mov rdi,[rbp+0x4D0] ; 0x186f52b  movaps [rbp+0x4D0],xmm0 ; 0x186f563  mov [rbp+0x4D0],rdi | handle (from interface call) |
| rbp+0xD0 | 8 | R/W | 0x186f4cc  mov [rbp+0xD0],rax ; 0x186f4e3  lea rdx,[rbp+0xD0] | ptr to string const 0xF58C410 |
| rbp+0xD8 | 8 | W | 0x186f4d3  mov qword ptr [rbp+0xD8],0xC | length 0xC |
| rbp+0x4E0 | 8 | W | 0x186f532  mov qword ptr [rbp+0x4E0],0 ; 0x186f571  mov [rbp+0x4E0],rax | end pointer (handle+8) |
| rbp+0x4D8 | 8 | W | 0x186f585  mov [rbp+0x4D8],rax | - |
| rbp+0x4F0 | 8 | W | 0x186f58c  mov qword ptr [rbp+0x4F0],0 | - |
| rbp+0x628 | 8 | R | 0x186f0a3  mov rcx,[rbp+0x628] ; 0x186f11d  mov rcx,[rbp+0x628] ; 0x186f1df  mov rcx,[rbp+0x628] ; 0x186f262  mov rcx,[rbp+0x628] ; 0x186f2e5  mov rcx,[rbp+0x628] ; 0x186f368  mov rcx,[rbp+0x628] ; 0x186f3eb  mov rcx,[rbp+0x628] ; 0x186f46e  mov rcx,[rbp+0x628] ; 0x186f4f1  mov rcx,[rbp+0x628] | this/context pointer (rcx arg to 0x1870DE0) |
| rbp+0xE0 | 8 | W | 0x186f59e  mov [rbp+0xE0],rax | ptr to string const 0xF560778 |
| rbp+0xE8 | 8 | W | 0x186f5a5  mov qword ptr [rbp+0xE8],0xB | length 0xB |

## Notes
- Sizes come from the instruction: movaps/movups = 16B, mov qword = 8B, mov dword = 4B. lea computes an address (size 8, address load) and does not touch memory.
- Offsets rbp+0x2D0/0x4B0/0x2F0/0x310/0x330/0x350/0x370/0x390/0x4D0 are written both as qword (0) and as 16-byte zero (movaps) and read back (mov reg,[...] or lea reg,[...]); rdi+0x0 is written as dword (0xF/0x11) and later as qword (0x60000000A).
- Meaning is given only where an instruction immediate or string constant shows it (lengths, string-const pointers, tags); otherwise '-'.
- No instruction in the slice is skipped; no ellipsis used.

## TOOL REQUESTS
None
