## NEXT
DONE

# U-Part: particle effect clone / ctor / drawargs (instruction-complete dossiers)

Input data (read fully, not regenerated): docs/data/listings/effect_particle_clone_5b8d520_5b8d65a.txt (71 instructions), docs/data/listings/effect_particle_ctor_668c220_668c3c0.txt (104 instructions), docs/data/listings/effect_particle_drawargs_67450a0_6745340.txt (146 instructions).

## Function A: effect_particle_clone, 0x5b8d520..0x5b8d659 (71 instructions)

Signature guess: `void ParticleEffect_clone(ParticleEffect* this /*rcx*/, void* arg2 /*rdx*/)` [I: rcx saved to rsi as `this`, rdx saved to rdi and forwarded inside the argument bundle at rbp+0x10; returns void, no value set before ret at 0x5b8d5d9].

### Phases

#### 0x5b8d520..0x5b8d560: Prologue saves rbp/rsi/rdi/rbx and reserves 0xC8; rdi=rdx, rsi=rcx; then reads global dword 0x129D1888 and the TLS slot `gs:[0x58]` indexed by dword 0x128767C8, comparing the global epoch against the dword at `[slot+4]`; if the global is greater it takes the slow path at 0x5B8D5DA.

```
0x5b8d520  push rbp
0x5b8d521  push rsi
0x5b8d522  push rdi
0x5b8d523  push rbx
0x5b8d524  sub rsp,0xC8
0x5b8d52b  lea rbp,[rsp+0x80]
0x5b8d533  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE
0x5b8d53b  mov rdi,rdx
0x5b8d53e  mov rsi,rcx
0x5b8d541  mov eax,[0x129D1888]
0x5b8d547  mov ecx,[0x128767C8]
0x5b8d54d  mov rdx,gs:[0x58]
0x5b8d556  mov rcx,[rdx+rcx*8]
0x5b8d55a  cmp eax,[rcx+4]
0x5b8d560  jg short 0x5B8D5DA
```

#### 0x5b8d562..0x5b8d5d9: Fast path: builds a local record at rbp+0x20 (module pointer 0x129D1750, bool flag) and a zeroed buffer (rbx=rbp+0x30, [rbp+0x38]=0, byte [rbp-0x18]=0); calls 0x39A7D40(rcx=0x129D1750, rdx=rbx, r8=rbp-0x50) whose byte result lands in [rbp+0x28]; then packs an argument bundle {arg2 at rbp+0x10, byte 2 at rbp+0x18}, loads `[[rsi]+0x360]` into rax and calls through the absolute pointer [0xF99FFA0] with rcx=this and rdx=&bundle; if the flag byte equals 1 it calls 0x77A2500(rcx=0x1244FD00, rdx=rbx, r8=0x129D1750+0x60); epilogue restores and returns.

```
0x5b8d562  lea rcx,[0x129D1750]
0x5b8d569  mov [rbp+0x20],rcx
0x5b8d56d  mov byte ptr [rbp+0x28],0
0x5b8d571  lea rbx,[rbp+0x30]
0x5b8d575  mov qword ptr [rbp+0x38],0
0x5b8d57d  mov byte ptr [rbp-0x18],0
0x5b8d581  lea r8,[rbp-0x50]
0x5b8d585  mov rdx,rbx
0x5b8d588  call 0x39A7D40
0x5b8d58d  mov [rbp+0x28],al
0x5b8d590  mov [rbp+0x10],rdi
0x5b8d594  mov byte ptr [rbp+0x18],2
0x5b8d598  mov rax,[rsi]
0x5b8d59b  mov rax,[rax+0x360]
0x5b8d5a2  lea rdx,[rbp+0x10]
0x5b8d5a6  mov rcx,rsi
0x5b8d5a9  call qword ptr [0xF99FFA0]
0x5b8d5af  nop
0x5b8d5b0  cmp byte ptr [rbp+0x28],1
0x5b8d5b4  jne short 0x5B8D5CE
0x5b8d5b6  mov r8,[rbp+0x20]
0x5b8d5ba  add r8,0x60
0x5b8d5be  lea rcx,[0x1244FD00]
0x5b8d5c5  mov rdx,rbx
0x5b8d5c8  call 0x77A2500
0x5b8d5cd  nop
0x5b8d5ce  add rsp,0xC8
0x5b8d5d5  pop rbx
0x5b8d5d6  pop rdi
0x5b8d5d7  pop rsi
0x5b8d5d8  pop rbp
0x5b8d5d9  ret
```

[UNVERIFIED: 0x5b8d5a9 semantic role of rax loaded from [vtable+0x360] — the call goes through absolute pointer [0xF99FFA0], not rax.]

#### 0x5b8d5da..0x5b8d659: Slow path: calls 0xE938CB0(0x129D1888) to refresh the epoch and re-tests the dword at 0x129D1888; if it still equals 0xFFFFFFFF it builds an error state at rbp (string {ptr 0xF52E07A, length 0x15} at rbp, 16 bytes copied from 0xF0BCBF8 into rbp-0x10) and calls 0x2FE330(rcx=0x129D1750, rdx=rbp-0x10, r8b=1, r9=rbp, stack args [rsp+0x20]=0 and [rsp+0x28]=0xF279E80); afterwards it calls 0xE935740(0x5BC5250) and 0xE938D70(0x129D1888) and jumps back into the fast path at 0x5B8D562; final instruction is padding.

```
0x5b8d5da  lea rcx,[0x129D1888]
0x5b8d5e1  call 0xE938CB0
0x5b8d5e6  cmp dword ptr [0x129D1888],0xFFFFFFFF
0x5b8d5ed  jne 0x5B8D562
0x5b8d5f3  lea rax,[0xF52E07A]
0x5b8d5fa  mov [rbp],rax
0x5b8d5fe  mov qword ptr [rbp+8],0x15
0x5b8d606  movups xmm0,[0xF0BCBF8]
0x5b8d60d  movaps [rbp-0x10],xmm0
0x5b8d611  lea rax,[0xF279E80]
0x5b8d618  mov [rsp+0x28],rax
0x5b8d61d  mov dword ptr [rsp+0x20],0
0x5b8d625  lea rcx,[0x129D1750]
0x5b8d62c  lea rdx,[rbp-0x10]
0x5b8d630  mov r9,rbp
0x5b8d633  mov r8b,1
0x5b8d636  call 0x2FE330
0x5b8d63b  nop
0x5b8d63c  lea rcx,[0x5BC5250]
0x5b8d643  call 0xE935740
0x5b8d648  lea rcx,[0x129D1888]
0x5b8d64f  call 0xE938D70
0x5b8d654  jmp 0x5B8D562
0x5b8d659  nop [rax]
```

### [reg+off] fields (clone, 0x5b8d520..0x5b8d659)

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| gs:[0x58] | 8 | R | 0x5b8d54d  mov rdx,gs:[0x58] | TLS array base [I: gs-relative, indexed next] |
| rdx+rcx*8 | 8 | R | 0x5b8d556  mov rcx,[rdx+rcx*8] | TLS slot selected by dword 0x128767C8 [I: ecx loaded from 0x128767C8] |
| rcx+4 | 4 | R | 0x5b8d55a  cmp eax,[rcx+4] | epoch dword of the TLS slot, compared against global 0x129D1888 [I: eax loaded from 0x129D1888 at 0x5b8d541] |
| rsi+0x0 | 8 | R | 0x5b8d598  mov rax,[rsi] | vtable pointer of `this` [I: rax immediately indexed +0x360] |
| rax+0x360 | 8 | R | 0x5b8d59b  mov rax,[rax+0x360] | - |
| rbp+0x40 | 8 | W | 0x5b8d533  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE | frame guard constant -2 [V: immediate] |
| rbp+0x20 | 8 | R/W | 0x5b8d569  mov [rbp+0x20],rcx<br>0x5b8d5b6  mov r8,[rbp+0x20] | module pointer 0x129D1750, later read as base for +0x60 [V: rcx=lea 0x129D1750] |
| rbp+0x28 | 1 | R/W | 0x5b8d56d  mov byte ptr [rbp+0x28],0<br>0x5b8d58d  mov [rbp+0x28],al<br>0x5b8d5b0  cmp byte ptr [rbp+0x28],1 | bool result of call 0x39A7D40, tested against 1 [V: stored from al] |
| rbp+0x38 | 8 | W | 0x5b8d575  mov qword ptr [rbp+0x38],0 | - |
| rbp-0x18 | 1 | W | 0x5b8d57d  mov byte ptr [rbp-0x18],0 | - |
| rbp+0x10 | 8 | W | 0x5b8d590  mov [rbp+0x10],rdi | argument bundle slot holding arg2 (rdx) of the clone call [V: rdi=rdx at 0x5b8d53b] |
| rbp+0x18 | 1 | W | 0x5b8d594  mov byte ptr [rbp+0x18],2 | argument bundle byte = 2 [V: immediate] |
| rbp+0x0 (clone err string) | 8 | W | 0x5b8d5fa  mov [rbp],rax | pointer to string 0xF52E07A [V: lea rax,[0xF52E07A]] |
| rbp+0x8 (clone err string) | 8 | W | 0x5b8d5fe  mov qword ptr [rbp+8],0x15 | length 0x15 paired with the 0xF52E07A pointer [V: immediate] |
| rbp-0x10 (clone err state) | 16 | W | 0x5b8d60d  movaps [rbp-0x10],xmm0 | 16 bytes copied from 0xF0BCBF8 [V: xmm0=movups [0xF0BCBF8] at 0x5b8d606] |
| rsp+0x28 | 8 | W | 0x5b8d618  mov [rsp+0x28],rax | stack argument = pointer 0xF279E80 [V: rax=lea 0xF279E80] |
| rsp+0x20 | 4 | W | 0x5b8d61d  mov dword ptr [rsp+0x20],0 | stack argument = 0 [V: immediate] |

## Function B: effect_particle_ctor, 0x668c220..0x668c3bf (104 instructions)

Signature guess: `void ctor(dst /*rcx*/, qword v /*rdx*/, src /*r8*/, dword a4 /*r9d*/, ptr a5 /*[rsp+0x38]*/, ptr a6 /*[rsp+0x40]*/, byte a7 /*[rsp+0x48]*/, word a8 /*[rsp+0x50]*/, ptr a9 /*[rsp+0x58]*/)` [I: rcx saved as dst rax, r8 used read-only as source; stack slots after the 2 pushes map to incoming arguments 5..9].

### Phases

#### 0x668c220..0x668c2a8: Constructor copies a source struct (r8) into the destination object (rcx, kept as rax): stores arg2 rdx into [dst+0]; zeroes xmm0 for the padding gaps; copies four pointer pairs src+0x0/+0x8 → dst+0x8/+0x10, src+0x10/+0x18 → dst+0x18/+0x20, src+0x28/+0x30 → dst+0x30/+0x38, src+0x40/+0x48 → dst+0x48/+0x50 (the source layout is dst-8), plus bytes src+0x20 → dst+0x28 and src+0x38 → dst+0x40; before each pair copy the second pointer (control-block slot) is atomically incremented at [ptr+8] when non-null.

```
0x668c220  push rsi
0x668c221  push rdi
0x668c222  mov rax,rcx
0x668c225  mov [rcx],rdx
0x668c228  xorps xmm0,xmm0
0x668c22b  movups [rcx+8],xmm0
0x668c22f  mov rcx,[r8+8]
0x668c233  test rcx,rcx
0x668c236  je short 0x668C23C
0x668c238  lock inc dword ptr [rcx+8]
0x668c23c  mov rcx,[r8]
0x668c23f  mov [rax+8],rcx
0x668c243  mov rcx,[r8+8]
0x668c247  mov [rax+0x10],rcx
0x668c24b  movups [rax+0x18],xmm0
0x668c24f  mov rcx,[r8+0x18]
0x668c253  test rcx,rcx
0x668c256  je short 0x668C25C
0x668c258  lock inc dword ptr [rcx+8]
0x668c25c  mov rcx,[r8+0x10]
0x668c260  mov [rax+0x18],rcx
0x668c264  mov rcx,[r8+0x18]
0x668c268  mov [rax+0x20],rcx
0x668c26c  movzx ecx,byte ptr [r8+0x20]
0x668c271  mov [rax+0x28],cl
0x668c274  movups [rax+0x30],xmm0
0x668c278  mov rcx,[r8+0x30]
0x668c27c  test rcx,rcx
0x668c27f  je short 0x668C285
0x668c281  lock inc dword ptr [rcx+8]
0x668c285  mov rcx,[r8+0x28]
0x668c289  mov [rax+0x30],rcx
0x668c28d  mov rcx,[r8+0x30]
0x668c291  mov [rax+0x38],rcx
0x668c295  movzx ecx,byte ptr [r8+0x38]
0x668c29a  mov [rax+0x40],cl
0x668c29d  movups [rax+0x48],xmm0
0x668c2a1  mov rcx,[r8+0x48]
0x668c2a5  test rcx,rcx
0x668c2a8  je short 0x668C2AE
```

#### 0x668c2aa..0x668c360: Completes the pending refcount increment for the src+0x48 pair and loads the incoming stack arguments (arg9 pointer → rcx, arg8 word → edx, arg7 byte → r10d, arg6 pointer → r11, arg5 pointer → rsi); copies the last pointer pair src+0x50/+0x58 → dst+0x58/+0x60 with its own increment; stores arg4 r9d into [dst+0x68]; then follows [rsi+0x70]/[rsi+0x78]/[rsi+0x80]/[rsi+0x88] each to a pointer at +0x40 of the referenced object and copies floats from those arrays into dst+0x6C..0x88 (4 floats, 2 floats, 1 float, 1 float respectively).

```
0x668c2aa  lock inc dword ptr [rcx+8]
0x668c2ae  mov rcx,[rsp+0x58]
0x668c2b3  movzx edx,word ptr [rsp+0x50]
0x668c2b8  movzx r10d,byte ptr [rsp+0x48]
0x668c2be  mov r11,[rsp+0x40]
0x668c2c3  mov rsi,[rsp+0x38]
0x668c2c8  mov rdi,[r8+0x40]
0x668c2cc  mov [rax+0x48],rdi
0x668c2d0  mov rdi,[r8+0x48]
0x668c2d4  mov [rax+0x50],rdi
0x668c2d8  movups [rax+0x58],xmm0
0x668c2dc  mov rdi,[r8+0x58]
0x668c2e0  test rdi,rdi
0x668c2e3  je short 0x668C2E9
0x668c2e5  lock inc dword ptr [rdi+8]
0x668c2e9  mov rdi,[r8+0x50]
0x668c2ed  mov [rax+0x58],rdi
0x668c2f1  mov r8,[r8+0x58]
0x668c2f5  mov [rax+0x60],r8
0x668c2f9  mov [rax+0x68],r9d
0x668c2fd  mov r8,[rsi+0x70]
0x668c301  mov r8,[r8+0x40]
0x668c305  movss xmm0,[r8]
0x668c30a  movss [rax+0x6C],xmm0
0x668c30f  movss xmm0,[r8+4]
0x668c315  movss [rax+0x70],xmm0
0x668c31a  movss xmm0,[r8+8]
0x668c320  movss [rax+0x74],xmm0
0x668c325  movss xmm0,[r8+0xC]
0x668c32b  movss [rax+0x78],xmm0
0x668c330  mov r8,[rsi+0x78]
0x668c334  mov r8,[r8+0x40]
0x668c338  movss xmm0,[r8]
0x668c33d  movss [rax+0x7C],xmm0
0x668c342  movss xmm0,[r8+4]
0x668c348  movss [rax+0x80],xmm0
0x668c350  mov r8,[rsi+0x80]
0x668c357  mov r8,[r8+0x40]
0x668c35b  movss xmm0,[r8]
0x668c360  movss [rax+0x84],xmm0
```

#### 0x668c368..0x668c3bf: Copies the last float (from [[rsi+0x88]+0x40]) into dst+0x88; stores dword [r11] into dst+0x8C and dword [r11+3] into dst+0x8F; stores the arg7 byte into dst+0x93 and the arg8 word into dst+0x94; copies 16 bytes from the arg9 pointer into dst+0x98 and a dword from arg9+0x10 into dst+0xA8; epilogue; int3 padding to the end of the function.

```
0x668c368  mov r8,[rsi+0x88]
0x668c36f  mov r8,[r8+0x40]
0x668c373  movss xmm0,[r8]
0x668c378  movss [rax+0x88],xmm0
0x668c380  mov r8d,[r11]
0x668c383  mov r9d,[r11+3]
0x668c387  mov [rax+0x8C],r8d
0x668c38e  mov [rax+0x8F],r9d
0x668c395  mov [rax+0x93],r10b
0x668c39c  mov [rax+0x94],dx
0x668c3a3  movups xmm0,[rcx]
0x668c3a6  movups [rax+0x98],xmm0
0x668c3ad  mov ecx,[rcx+0x10]
0x668c3b0  mov [rax+0xA8],ecx
0x668c3b6  pop rdi
0x668c3b7  pop rsi
0x668c3b8  ret
0x668c3b9  int3
0x668c3ba  int3
0x668c3bb  int3
0x668c3bc  int3
0x668c3bd  int3
0x668c3be  int3
0x668c3bf  int3
```

### [reg+off] fields (ctor, 0x668c220..0x668c3bf)

Destination object (rax = rcx = dst):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rax+0x0 (ctor dst) | 8 | W | 0x668c225  mov [rcx],rdx | arg2 (rdx) stored as first qword of dst [V] |
| rax+0x8 (ctor dst) | 16 | W | 0x668c22b  movups [rcx+8],xmm0<br>0x668c23f  mov [rax+8],rcx | 16B zero fill, then the 8B first shared-pointer slot from src+0x0 [V: xmm0=xorps] |
| rax+0x10 (ctor dst) | 8 | W | 0x668c247  mov [rax+0x10],rcx | control-block slot of the first pair, from src+0x8 [I: paired inc at [ptr+8]] |
| rax+0x18 (ctor dst) | 16 | W | 0x668c24b  movups [rax+0x18],xmm0<br>0x668c260  mov [rax+0x18],rcx | 16B zero fill, then the 8B pointer slot from src+0x10 [V] |
| rax+0x20 (ctor dst) | 8 | W | 0x668c268  mov [rax+0x20],rcx | control-block slot, from src+0x18 [V] |
| rax+0x28 (ctor dst) | 1 | W | 0x668c271  mov [rax+0x28],cl | byte from src+0x20 [V: movzx ecx,[r8+0x20]] |
| rax+0x30 (ctor dst) | 16 | W | 0x668c274  movups [rax+0x30],xmm0<br>0x668c289  mov [rax+0x30],rcx | 16B zero fill, then the 8B pointer slot from src+0x28 [V] |
| rax+0x38 (ctor dst) | 8 | W | 0x668c291  mov [rax+0x38],rcx | control-block slot, from src+0x30 [V] |
| rax+0x40 (ctor dst) | 1 | W | 0x668c29a  mov [rax+0x40],cl | byte from src+0x38 [V: movzx ecx,[r8+0x38]] |
| rax+0x48 (ctor dst) | 16 | W | 0x668c29d  movups [rax+0x48],xmm0<br>0x668c2cc  mov [rax+0x48],rdi | 16B zero fill, then the 8B pointer slot from src+0x40 [V] |
| rax+0x50 (ctor dst) | 8 | W | 0x668c2d4  mov [rax+0x50],rdi | control-block slot, from src+0x48 [V] |
| rax+0x58 (ctor dst) | 16 | W | 0x668c2d8  movups [rax+0x58],xmm0<br>0x668c2ed  mov [rax+0x58],rdi | 16B zero fill, then the 8B pointer slot from src+0x50 [V] |
| rax+0x60 (ctor dst) | 8 | W | 0x668c2f5  mov [rax+0x60],r8 | control-block slot, from src+0x58 [V] |
| rax+0x68 (ctor dst) | 4 | W | 0x668c2f9  mov [rax+0x68],r9d | arg4 dword stored [V: r9d is the arg4 register] |
| rax+0x6C (ctor dst) | 4 | W | 0x668c30a  movss [rax+0x6C],xmm0 | float[0] from [[rsi+0x70]+0x40] [V: load chain] |
| rax+0x70 (ctor dst) | 4 | W | 0x668c315  movss [rax+0x70],xmm0 | float[1] from [[rsi+0x70]+0x40] [V] |
| rax+0x74 (ctor dst) | 4 | W | 0x668c320  movss [rax+0x74],xmm0 | float[2] from [[rsi+0x70]+0x40] [V] |
| rax+0x78 (ctor dst) | 4 | W | 0x668c32b  movss [rax+0x78],xmm0 | float[3] from [[rsi+0x70]+0x40] [V] |
| rax+0x7C (ctor dst) | 4 | W | 0x668c33d  movss [rax+0x7C],xmm0 | float[0] from [[rsi+0x78]+0x40] [V] |
| rax+0x80 (ctor dst) | 4 | W | 0x668c348  movss [rax+0x80],xmm0 | float[1] from [[rsi+0x78]+0x40] [V] |
| rax+0x84 (ctor dst) | 4 | W | 0x668c360  movss [rax+0x84],xmm0 | float from [[rsi+0x80]+0x40] [V] |
| rax+0x88 (ctor dst) | 4 | W | 0x668c378  movss [rax+0x88],xmm0 | float from [[rsi+0x88]+0x40] [V] |
| rax+0x8C (ctor dst) | 4 | W | 0x668c387  mov [rax+0x8C],r8d | dword from [r11] (arg6) [V] |
| rax+0x8F (ctor dst) | 4 | W | 0x668c38e  mov [rax+0x8F],r9d | dword from [r11+3] (arg6+3) [V] |
| rax+0x93 (ctor dst) | 1 | W | 0x668c395  mov [rax+0x93],r10b | arg7 byte [V: r10b from [rsp+0x48]] |
| rax+0x94 (ctor dst) | 2 | W | 0x668c39c  mov [rax+0x94],dx | arg8 word [V: dx from [rsp+0x50]] |
| rax+0x98 (ctor dst) | 16 | W | 0x668c3a6  movups [rax+0x98],xmm0 | 16 bytes from the arg9 pointer [V: xmm0=movups [rcx]] |
| rax+0xA8 (ctor dst) | 4 | W | 0x668c3b0  mov [rax+0xA8],ecx | dword from arg9+0x10 [V] |

Source struct (r8 = src; dst layout is src layout shifted +8 for the pointer pairs):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| r8+0x0 | 8 | R | 0x668c23c  mov rcx,[r8] | first pointer of pair 1 [V] |
| r8+0x8 | 8 | R | 0x668c22f  mov rcx,[r8+8]<br>0x668c243  mov rcx,[r8+8] | control-block pointer of pair 1; loaded twice (null test + copy) [V] |
| r8+0x10 | 8 | R | 0x668c25c  mov rcx,[r8+0x10] | pointer of pair 2 [V] |
| r8+0x18 | 8 | R | 0x668c24f  mov rcx,[r8+0x18]<br>0x668c264  mov rcx,[r8+0x18] | control-block pointer of pair 2, loaded twice [V] |
| r8+0x20 | 1 | R | 0x668c26c  movzx ecx,byte ptr [r8+0x20] | byte copied to dst+0x28 [V] |
| r8+0x28 | 8 | R | 0x668c285  mov rcx,[r8+0x28] | pointer of pair 3 [V] |
| r8+0x30 | 8 | R | 0x668c278  mov rcx,[r8+0x30]<br>0x668c28d  mov rcx,[r8+0x30] | control-block pointer of pair 3, loaded twice [V] |
| r8+0x38 | 1 | R | 0x668c295  movzx ecx,byte ptr [r8+0x38] | byte copied to dst+0x40 [V] |
| r8+0x40 | 8 | R | 0x668c2c8  mov rdi,[r8+0x40] | pointer of pair 4 [V] |
| r8+0x48 | 8 | R | 0x668c2a1  mov rcx,[r8+0x48]<br>0x668c2d0  mov rdi,[r8+0x48] | control-block pointer of pair 4, loaded twice [V] |
| r8+0x50 | 8 | R | 0x668c2e9  mov rdi,[r8+0x50] | pointer of pair 5 [V] |
| r8+0x58 | 8 | R | 0x668c2dc  mov rdi,[r8+0x58]<br>0x668c2f1  mov r8,[r8+0x58] | control-block pointer of pair 5, loaded twice [V] |

Refcounted control blocks (pointer held in a register):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| ptr+0x8 (refcount) | 4 | W | 0x668c238  lock inc dword ptr [rcx+8]<br>0x668c258  lock inc dword ptr [rcx+8]<br>0x668c281  lock inc dword ptr [rcx+8]<br>0x668c2aa  lock inc dword ptr [rcx+8]<br>0x668c2e5  lock inc dword ptr [rdi+8]<br>0x6745276  lock inc dword ptr [rax+8] | atomic refcount increment at pointee+8 for each copied/moved pointer (first 5 sites: ctor pairs 1-5; last site: drawargs variant pointer [rdi+0x30]) [I: lock inc guarded by null test] |

Argument-object chains (rsi = arg5 pointer, its +0x70/+0x78/+0x80/+0x88 slots):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rsi+0x70 | 8 | R | 0x668c2fd  mov r8,[rsi+0x70] | pointer to object whose +0x40 holds the 4-float array copied to dst+0x6C..0x78 [I: following movss chain] |
| rsi+0x78 | 8 | R | 0x668c330  mov r8,[rsi+0x78] | pointer to object whose +0x40 holds the 2-float array copied to dst+0x7C..0x80 [I] |
| rsi+0x80 | 8 | R | 0x668c350  mov r8,[rsi+0x80] | pointer to object whose +0x40 holds the float copied to dst+0x84 [I] |
| rsi+0x88 | 8 | R | 0x668c368  mov r8,[rsi+0x88] | pointer to object whose +0x40 holds the float copied to dst+0x88 [I] |
| ptr+0x40 | 8 | R | 0x668c301  mov r8,[r8+0x40]<br>0x668c334  mov r8,[r8+0x40]<br>0x668c357  mov r8,[r8+0x40]<br>0x668c36f  mov r8,[r8+0x40] | float-array base inside each referenced object [I] |
| ptr+0x0 | 4 | R | 0x668c305  movss xmm0,[r8]<br>0x668c338  movss xmm0,[r8]<br>0x668c35b  movss xmm0,[r8]<br>0x668c373  movss xmm0,[r8] | float[0] of each array [V] |
| ptr+0x4 | 4 | R | 0x668c30f  movss xmm0,[r8+4]<br>0x668c342  movss xmm0,[r8+4] | float[1] (used for the 4-float and 2-float arrays) [V] |
| ptr+0x8 (ctor float arrays) | 4 | R | 0x668c31a  movss xmm0,[r8+8] | float[2] of the 4-float array [V] |
| ptr+0xC | 4 | R | 0x668c325  movss xmm0,[r8+0xC] | float[3] of the 4-float array [V] |

Incoming stack arguments (arg6 pointer r11, arg9 pointer rcx):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| r11+0x0 | 4 | R | 0x668c380  mov r8d,[r11] | first dword of arg6, stored to dst+0x8C [V] |
| r11+0x3 | 4 | R | 0x668c383  mov r9d,[r11+3] | dword at arg6+3, stored to dst+0x8F [V] |
| rcx+0x0 (ctor arg9) | 16 | R | 0x668c3a3  movups xmm0,[rcx] | 16 bytes of arg9, stored to dst+0x98 [V] |
| rcx+0x10 (ctor arg9) | 4 | R | 0x668c3ad  mov ecx,[rcx+0x10] | dword at arg9+0x10, stored to dst+0xA8 [V] |

Incoming stack-argument slots (rsp-relative at function body):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rsp+0x58 | 8 | R | 0x668c2ae  mov rcx,[rsp+0x58] | arg9 pointer [I: stack slot after 2 pushes] |
| rsp+0x50 | 2 | R | 0x668c2b3  movzx edx,word ptr [rsp+0x50] | arg8 word [I] |
| rsp+0x48 | 1 | R | 0x668c2b8  movzx r10d,byte ptr [rsp+0x48] | arg7 byte [I] |
| rsp+0x40 | 8 | R | 0x668c2be  mov r11,[rsp+0x40] | arg6 pointer [I] |
| rsp+0x38 | 8 | R | 0x668c2c3  mov rsi,[rsp+0x38] | arg5 pointer [I] |

## Function C: effect_particle_drawargs, 0x67450a0..0x6745339 (146 instructions)

Signature guess: `void draw_args(ParticleEffect* this /*rcx*/, DrawArgs* out /*rdx*/)` [I: rdx saved to rsi and written through both rdx and rsi as one output object; returns void, plain ret at 0x6745316].

### Phases

#### 0x67450a0..0x6745140: Prologue saves rbp/r14/rsi/rdi/rbx and reserves 0x90, storing xmm6 at [rbp]; rsi=rdx (out), rbx=[this+0x10], rax=[this+0x18]; initializes three vec4 rows {1.0f,0,0,0} at rbp-0x50/-0x38/-0x20 (dword 0x3F800000 + 16 zero bytes each) and a flag byte [rbp-0x10]=0; rdi=[this] and r14w = word at [this+8]+0x94; then copies from the struct at rax into rdx: 16 bytes [rax]→[rdx], dword [rax+0x10]→[rdx+0x10], byte [rax+0x14]→[rdx+0x14], and four floats [rax+0x18..0x24]→[rdx+0x18..0x24].

```
0x67450a0  push rbp
0x67450a1  push r14
0x67450a3  push rsi
0x67450a4  push rdi
0x67450a5  push rbx
0x67450a6  sub rsp,0x90
0x67450ad  lea rbp,[rsp+0x80]
0x67450b5  movaps [rbp],xmm6
0x67450b9  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
0x67450c1  mov rsi,rdx
0x67450c4  mov rbx,[rcx+0x10]
0x67450c8  mov rax,[rcx+0x18]
0x67450cc  mov dword ptr [rbp-0x50],0x3F800000
0x67450d3  xorps xmm6,xmm6
0x67450d6  movups [rbp-0x4C],xmm6
0x67450da  mov dword ptr [rbp-0x3C],0x3F800000
0x67450e1  movups [rbp-0x38],xmm6
0x67450e5  mov dword ptr [rbp-0x28],0x3F800000
0x67450ec  movups [rbp-0x24],xmm6
0x67450f0  mov dword ptr [rbp-0x14],0x3F800000
0x67450f7  mov byte ptr [rbp-0x10],0
0x67450fb  mov rdi,[rcx]
0x67450fe  mov rcx,[rcx+8]
0x6745102  mov r14w,[rcx+0x94]
0x674510a  mov ecx,[rax+0x10]
0x674510d  mov [rdx+0x10],ecx
0x6745110  movups xmm0,[rax]
0x6745113  movups [rdx],xmm0
0x6745116  movzx ecx,byte ptr [rax+0x14]
0x674511a  mov [rdx+0x14],cl
0x674511d  movss xmm0,[rax+0x18]
0x6745122  movss [rdx+0x18],xmm0
0x6745127  movss xmm0,[rax+0x1C]
0x674512c  movss [rdx+0x1C],xmm0
0x6745131  movss xmm0,[rax+0x20]
0x6745136  movss [rdx+0x20],xmm0
0x674513b  movss xmm0,[rax+0x24]
0x6745140  movss [rdx+0x24],xmm0
```

#### 0x6745145..0x6745231: Copies three 16-byte rows [rax+0x28]/[rax+0x38]/[rax+0x47] into [rdx+0x28]/+0x38/+0x47; qword [rbx]→[rdx+0x60] and copies data from rbx+8 into rdx+0x68 via call 0xE869FF0; moves the pointer [rbx+0x80] into [rsi+0xE0] and zeroes [rbx+0x80] (ownership move); initializes rsi+0xE8..0x124 with the same three {1.0f,0,0,0} vec4 rows; byte 0 → [rsi+0x128], word r14w → [rsi+0x130]; copies 16 bytes [rdi] → [rsi+0x138] then zeroes [rdi+8], copies [rdi+0x10] → [rsi+0x148] and zeroes it with xmm6, qword [rdi+0x20] → [rsi+0x158]; 0xFF → [rsi+0x170]; dispatches on byte [rdi+0x38] (values ≤3 go through the jump table at 0xF2BFC70, larger values to the default at 0x67452EF).

```
0x6745145  movups xmm0,[rax+0x28]
0x6745149  movups xmm1,[rax+0x38]
0x674514d  movups xmm2,[rax+0x47]
0x6745151  movups [rdx+0x28],xmm0
0x6745155  movups [rdx+0x38],xmm1
0x6745159  movups [rdx+0x47],xmm2
0x674515d  mov rax,[rbx]
0x6745160  mov [rdx+0x60],rax
0x6745164  lea rcx,[rdx+0x68]
0x6745168  lea rdx,[rbx+8]
0x674516c  call 0xE869FF0
0x6745171  nop
0x6745172  mov rax,[rbx+0x80]
0x6745179  mov [rsi+0xE0],rax
0x6745180  mov qword ptr [rbx+0x80],0
0x674518b  mov dword ptr [rsi+0xE8],0x3F800000
0x6745195  movups [rsi+0xEC],xmm6
0x674519c  mov dword ptr [rsi+0xFC],0x3F800000
0x67451a6  movups [rsi+0x100],xmm6
0x67451ad  mov dword ptr [rsi+0x110],0x3F800000
0x67451b7  movups [rsi+0x114],xmm6
0x67451be  mov dword ptr [rsi+0x124],0x3F800000
0x67451c8  mov byte ptr [rsi+0x128],0
0x67451cf  mov [rsi+0x130],r14w
0x67451d7  movups xmm0,[rdi]
0x67451da  mov qword ptr [rdi+8],0
0x67451e2  movups [rsi+0x138],xmm0
0x67451e9  movups xmm0,[rdi+0x10]
0x67451ed  movups [rdi+0x10],xmm6
0x67451f1  movups [rsi+0x148],xmm0
0x67451f8  mov rax,[rdi+0x20]
0x67451fc  mov [rsi+0x158],rax
0x6745203  mov byte ptr [rsi+0x170],0xFF
0x674520a  movzx eax,byte ptr [rdi+0x38]
0x674520e  cmp rax,3
0x6745212  ja 0x67452EF
0x6745218  lea rcx,[rsi+0x160]
0x674521f  lea rdx,[rdi+0x28]
0x6745223  lea r8,[0xF2BFC70]
0x674522a  movsxd r9,[r8+rax*4]
0x674522e  add r9,r8
0x6745231  jmp r9
```

#### 0x6745234..0x67452d6: Switch cases: two of them copy the variant payload — one moves the qword [[rdi+0x28]] and one moves 16 bytes from [rdi+0x28] — into [rsi+0x160]; a third zeroes the 16 bytes at rsi+0x160, takes the pointer [rdi+0x30], atomically increments it at [ptr+8] when non-null, then copies 16 bytes [rdi+0x28] → [rsi+0x160] with tag byte 3; every case then stores the tag byte al → [rsi+0x170] and copies [rdi+0x40] → [rsi+0x178] and [rdi+0x50] → [rsi+0x188] before the common epilogue; the phase also contains the start of the stack-object release check ([rbp-0x50]/[rbp-0x40] buffer: if end-start > 0x1000 and the header [rcx-8] is within 0x20 bytes it jumps to the dealloc path at 0x6745339, otherwise rcx=rax and it falls into the epilogue with a tail call to 0xE935700).

```
0x6745234  mov rdx,[rdx]
0x6745237  mov [rcx],rdx
0x674523a  jmp short 0x6745242
0x674523c  movups xmm0,[rdx]
0x674523f  movups [rcx],xmm0
0x6745242  mov [rsi+0x170],al
0x6745248  movups xmm0,[rdi+0x40]
0x674524c  movups [rsi+0x178],xmm0
0x6745253  mov rax,[rdi+0x50]
0x6745257  mov [rsi+0x188],rax
0x674525e  jmp 0x6745305
0x6745263  xorps xmm0,xmm0
0x6745266  movups [rcx],xmm0
0x6745269  mov rax,[rdi+0x30]
0x674526d  test rax,rax
0x6745270  je 0x6745317
0x6745276  lock inc dword ptr [rax+8]
0x674527a  cmp byte ptr [rbp-0x10],1
0x674527e  movups xmm0,[rdi+0x28]
0x6745282  movups [rsi+0x160],xmm0
0x6745289  mov byte ptr [rsi+0x170],3
0x6745290  movups xmm0,[rdi+0x40]
0x6745294  movups [rsi+0x178],xmm0
0x674529b  mov rax,[rdi+0x50]
0x674529f  mov [rsi+0x188],rax
0x67452a6  jne short 0x6745305
0x67452a8  mov rcx,[rbp-0x50]
0x67452ac  test rcx,rcx
0x67452af  je short 0x6745305
0x67452b1  mov rdx,[rbp-0x40]
0x67452b5  sub rdx,rcx
0x67452b8  cmp rdx,0x1000
0x67452bf  jb short 0x67452D9
0x67452c1  mov rax,[rcx-8]
0x67452c5  add rcx,0xFFFFFFFFFFFFFFF8
0x67452c9  sub rcx,rax
0x67452cc  cmp rcx,0x20
0x67452d0  jae short 0x6745339
0x67452d2  or rdx,0x27
0x67452d6  mov rcx,rax
```

#### 0x67452d9..0x6745339: Epilogue A (reached after the buffer check): restores xmm6, pops and tail-jumps to 0xE935700; the default switch case (tag > 3): copies [rdi+0x50] → [rsi+0x188] and [rdi+0x40] → [rsi+0x178] then falls into epilogue B (restore xmm6, pops, ret); the [rdi+0x30]==0 case: qword [rdi+0x28] → [rsi+0x160], qword 0 → [rsi+0x168], tag 3 → [rsi+0x170], then jumps to 0x6745248; the last line is the entry of the dealloc continuation at 0x6745339, where the input range ends.

```
0x67452d9  movaps xmm6,[rbp]
0x67452dd  add rsp,0x90
0x67452e4  pop rbx
0x67452e5  pop rdi
0x67452e6  pop rsi
0x67452e7  pop r14
0x67452e9  pop rbp
0x67452ea  jmp 0xE935700
0x67452ef  mov rax,[rdi+0x50]
0x67452f3  mov [rsi+0x188],rax
0x67452fa  movups xmm0,[rdi+0x40]
0x67452fe  movups [rsi+0x178],xmm0
0x6745305  movaps xmm6,[rbp]
0x6745309  add rsp,0x90
0x6745310  pop rbx
0x6745311  pop rdi
0x6745312  pop rsi
0x6745313  pop r14
0x6745315  pop rbp
0x6745316  ret
0x6745317  mov rax,[rdi+0x28]
0x674531b  mov [rsi+0x160],rax
0x6745322  mov qword ptr [rsi+0x168],0
0x674532d  mov byte ptr [rsi+0x170],3
0x6745334  jmp 0x6745248
0x6745339  mov qword ptr [rsp+0x20],0
```

[UNVERIFIED: 0x6745339 the dealloc continuation starting here is cut off by the input range (67450a0_6745340); only its first instruction is in the listing.]

### [reg+off] fields (drawargs, 0x67450a0..0x6745339)

`this` (rcx; rcx is reused as [this+8] for the +0x94 read, then as the destination [rsi+0x160] and as the jump table base):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rcx+0x0 (drawargs this) | 8 | R | 0x67450fb  mov rdi,[rcx] | pointer to the variant object copied at rsi+0x138..0x158 [V: rdi used as its base] |
| rcx+0x8 (drawargs this) | 8 | R | 0x67450fe  mov rcx,[rcx+8] | pointer whose +0x94 word is read into r14w [V: next instruction] |
| rcx+0x10 (drawargs this) | 8 | R | 0x67450c4  mov rbx,[rcx+0x10] | source sub-object: qword [rbx] → rdx+0x60, data from rbx+8 via 0xE869FF0, pointer [rbx+0x80] moved to rsi+0xE0 [V] |
| rcx+0x18 (drawargs this) | 8 | R | 0x67450c8  mov rax,[rcx+0x18] | source struct copied into rdx+0x00..0x47 [V] |
| ptr+0x94 | 2 | R | 0x6745102  mov r14w,[rcx+0x94] | word saved in r14w and later stored to rsi+0x130 [V] |

Source struct (rax = [this+0x18]):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rax+0x0 (drawargs src) | 16 | R | 0x6745110  movups xmm0,[rax] | 16 bytes copied to rdx+0x0 [V] |
| rax+0x10 (drawargs src) | 4 | R | 0x674510a  mov ecx,[rax+0x10] | dword copied to rdx+0x10 [V] |
| rax+0x14 (drawargs src) | 1 | R | 0x6745116  movzx ecx,byte ptr [rax+0x14] | byte copied to rdx+0x14 [V] |
| rax+0x18 (drawargs src) | 4 | R | 0x674511d  movss xmm0,[rax+0x18] | float copied to rdx+0x18 [V] |
| rax+0x1C (drawargs src) | 4 | R | 0x6745127  movss xmm0,[rax+0x1C] | float copied to rdx+0x1C [V] |
| rax+0x20 (drawargs src) | 4 | R | 0x6745131  movss xmm0,[rax+0x20] | float copied to rdx+0x20 [V] |
| rax+0x24 (drawargs src) | 4 | R | 0x674513b  movss xmm0,[rax+0x24] | float copied to rdx+0x24 [V] |
| rax+0x28 (drawargs src) | 16 | R | 0x6745145  movups xmm0,[rax+0x28] | 16-byte row copied to rdx+0x28 [V] |
| rax+0x38 (drawargs src) | 16 | R | 0x6745149  movups xmm1,[rax+0x38] | 16-byte row copied to rdx+0x38 [V] |
| rax+0x47 (drawargs src) | 16 | R | 0x674514d  movups xmm2,[rax+0x47] | 16-byte row copied to rdx+0x47 [V] |

Out object, first half (rdx = rsi = out):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rdx+0x0 | 16 | W | 0x6745113  movups [rdx],xmm0 | 16 bytes from rax+0x0 [V] |
| rdx+0x10 | 4 | W | 0x674510d  mov [rdx+0x10],ecx | dword from rax+0x10 [V] |
| rdx+0x14 | 1 | W | 0x674511a  mov [rdx+0x14],cl | byte from rax+0x14 [V] |
| rdx+0x18 | 4 | W | 0x6745122  movss [rdx+0x18],xmm0 | float from rax+0x18 [V] |
| rdx+0x1C | 4 | W | 0x674512c  movss [rdx+0x1C],xmm0 | float from rax+0x1C [V] |
| rdx+0x20 | 4 | W | 0x6745136  movss [rdx+0x20],xmm0 | float from rax+0x20 [V] |
| rdx+0x24 | 4 | W | 0x6745140  movss [rdx+0x24],xmm0 | float from rax+0x24 [V] |
| rdx+0x28 | 16 | W | 0x6745151  movups [rdx+0x28],xmm0 | row from rax+0x28 [V] |
| rdx+0x38 | 16 | W | 0x6745155  movups [rdx+0x38],xmm1 | row from rax+0x38 [V] |
| rdx+0x47 | 16 | W | 0x6745159  movups [rdx+0x47],xmm2 | row from rax+0x47 [V] |
| rdx+0x60 | 8 | W | 0x6745160  mov [rdx+0x60],rax | qword from [rbx] [V] |
| rdx+0x68 | - | W | 0x674516c  call 0xE869FF0 (rcx=lea [rdx+0x68], rdx=lea [rbx+8]) | filled by callee 0xE869FF0, contents not visible in this listing [?] |

Out object, second half (rsi = out; the rdx+0x160 alias is via rcx=lea [rsi+0x160]):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rsi+0xE0 | 8 | W | 0x6745179  mov [rsi+0xE0],rax | pointer moved out of [rbx+0x80] [V: next instruction zeroes rbx+0x80] |
| rsi+0xE8 | 4 | W | 0x674518b  mov dword ptr [rsi+0xE8],0x3F800000 | vec4 row start, 1.0f [V: constant] |
| rsi+0xEC | 16 | W | 0x6745195  movups [rsi+0xEC],xmm6 | vec4 row zeros [V: xmm6=xorps] |
| rsi+0xFC | 4 | W | 0x674519c  mov dword ptr [rsi+0xFC],0x3F800000 | vec4 row start, 1.0f [V] |
| rsi+0x100 | 16 | W | 0x67451a6  movups [rsi+0x100],xmm6 | vec4 row zeros [V] |
| rsi+0x110 | 4 | W | 0x67451ad  mov dword ptr [rsi+0x110],0x3F800000 | vec4 row start, 1.0f [V] |
| rsi+0x114 | 16 | W | 0x67451b7  movups [rsi+0x114],xmm6 | vec4 row zeros [V] |
| rsi+0x124 | 4 | W | 0x67451be  mov dword ptr [rsi+0x124],0x3F800000 | vec4 row start, 1.0f [V] |
| rsi+0x128 | 1 | W | 0x67451c8  mov byte ptr [rsi+0x128],0 | byte cleared [V] |
| rsi+0x130 | 2 | W | 0x67451cf  mov [rsi+0x130],r14w | word from [[this+8]+0x94] [V] |
| rsi+0x138 | 16 | W | 0x67451e2  movups [rsi+0x138],xmm0 | 16 bytes from [rdi] [V] |
| rsi+0x148 | 16 | W | 0x67451f1  movups [rsi+0x148],xmm0 | 16 bytes from [rdi+0x10] [V] |
| rsi+0x158 | 8 | W | 0x67451fc  mov [rsi+0x158],rax | qword from [rdi+0x20] [V] |
| rsi+0x160 | 16 | W | 0x6745282  movups [rsi+0x160],xmm0<br>0x6745237  mov [rcx],rdx<br>0x674523f  movups [rcx],xmm0<br>0x6745266  movups [rcx],xmm0<br>0x674531b  mov [rsi+0x160],rax | variant payload at out+0x160 (rcx=lea [rsi+0x160] in the switch cases): three 16B movups stores (copy, copy, zero) and two 8B qword stores [V] |
| rsi+0x168 | 8 | W | 0x6745322  mov qword ptr [rsi+0x168],0 | qword cleared in the null-pointer case [V] |
| rsi+0x170 | 1 | W | 0x6745203  mov byte ptr [rsi+0x170],0xFF<br>0x6745242  mov [rsi+0x170],al<br>0x6745289  mov byte ptr [rsi+0x170],3<br>0x674532d  mov byte ptr [rsi+0x170],3 | tag byte: pre-set 0xFF, then the dispatch value [rdi+0x38] or constant 3 [V] |
| rsi+0x178 | 16 | W | 0x674524c  movups [rsi+0x178],xmm0<br>0x6745294  movups [rsi+0x178],xmm0<br>0x67452fe  movups [rsi+0x178],xmm0 | 16 bytes from [rdi+0x40], common tail of every case [V] |
| rsi+0x188 | 8 | W | 0x6745257  mov [rsi+0x188],rax<br>0x674529f  mov [rsi+0x188],rax<br>0x67452f3  mov [rsi+0x188],rax | qword from [rdi+0x50], common tail of every case [V] |

Variant object (rdi = [this]; rdx is reused as rdi+0x28 in the switch cases):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rdi+0x0 | 16 | R | 0x67451d7  movups xmm0,[rdi] | 16 bytes moved to rsi+0x138 [V] |
| rdi+0x8 | 8 | W | 0x67451da  mov qword ptr [rdi+8],0 | source slot zeroed after the move [V] |
| rdi+0x10 | 16 | R/W | 0x67451e9  movups xmm0,[rdi+0x10]<br>0x67451ed  movups [rdi+0x10],xmm6 | 16 bytes moved to rsi+0x148, source zeroed [V] |
| rdi+0x20 | 8 | R | 0x67451f8  mov rax,[rdi+0x20] | qword copied to rsi+0x158 [V] |
| rdi+0x28 | 16 | R | 0x674527e  movups xmm0,[rdi+0x28]<br>0x6745234  mov rdx,[rdx]<br>0x674523c  movups xmm0,[rdx] | variant payload base (rdx=lea [rdi+0x28] in the switch cases): two 16B loads and one 8B qword load [V] |
| rdi+0x30 | 8 | R | 0x6745269  mov rax,[rdi+0x30] | pointer taken for the refcount-increment case [V: lock inc follows] |
| rdi+0x38 | 1 | R | 0x674520a  movzx eax,byte ptr [rdi+0x38] | switch tag byte (0..3 = jump table, else default) [V] |
| rdi+0x40 | 16 | R | 0x6745248  movups xmm0,[rdi+0x40]<br>0x6745290  movups xmm0,[rdi+0x40]<br>0x67452fa  movups xmm0,[rdi+0x40] | 16 bytes copied to rsi+0x178 in every case [V] |
| rdi+0x50 | 8 | R | 0x6745253  mov rax,[rdi+0x50]<br>0x674529b  mov rax,[rdi+0x50]<br>0x67452ef  mov rax,[rdi+0x50] | qword copied to rsi+0x188 in every case [V] |

Stack frame (rbp; rbp-0x50 holds the three vec4 rows and the release check):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rbp+0x0 (drawargs xmm6) | 16 | W/R | 0x67450b5  movaps [rbp],xmm6<br>0x67452d9  movaps xmm6,[rbp]<br>0x6745305  movaps xmm6,[rbp] | xmm6 callee-save spill and restore in both epilogues [V] |
| rbp-0x8 (drawargs frame) | 8 | W | 0x67450b9  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE | frame guard constant -2 [V: immediate] |
| rbp-0x50 (drawargs frame) | 4/8 | W/R | 0x67450cc  mov dword ptr [rbp-0x50],0x3F800000<br>0x67452a8  mov rcx,[rbp-0x50] | 4B store of 1.0f (vec4 row 1 start), later read as the 8B buffer start pointer for the release check [I: compared with [rbp-0x40]] |
| rbp-0x4C (drawargs frame) | 16 | W | 0x67450d6  movups [rbp-0x4C],xmm6 | vec4 row 1 zeros [V] |
| rbp-0x3C (drawargs frame) | 4 | W | 0x67450da  mov dword ptr [rbp-0x3C],0x3F800000 | vec4 row 2 start, 1.0f [V] |
| rbp-0x38 (drawargs frame) | 16 | W | 0x67450e1  movups [rbp-0x38],xmm6 | vec4 row 2 zeros [V] |
| rbp-0x40 (drawargs frame) | 8 | R | 0x67452b1  mov rdx,[rbp-0x40] | buffer end pointer for the release check [I: rdx-rcx compared to 0x1000] |
| rbp-0x28 (drawargs frame) | 4 | W | 0x67450e5  mov dword ptr [rbp-0x28],0x3F800000 | vec4 row 3 start, 1.0f [V] |
| rbp-0x24 (drawargs frame) | 16 | W | 0x67450ec  movups [rbp-0x24],xmm6 | vec4 row 3 zeros [V] |
| rbp-0x14 (drawargs frame) | 4 | W | 0x67450f0  mov dword ptr [rbp-0x14],0x3F800000 | - |
| rbp-0x10 (drawargs flag) | 1 | R/W | 0x67450f7  mov byte ptr [rbp-0x10],0<br>0x674527a  cmp byte ptr [rbp-0x10],1 | flag byte initialized 0, later tested against 1 (controls the release path at 0x67452a6) [V] |
| rcx-8 | 8 | R | 0x67452c1  mov rax,[rcx-8] | header dword/qword before the buffer in the heap-check sequence [I: part of the >0x1000 heap-buffer probe] |
| r8+rax*4 | 4 | R | 0x674522a  movsxd r9,[r8+rax*4] | 4-entry int32 jump table at 0xF2BFC70, indexed by the switch tag [V] |

Source sub-object (rbx = [this+0x10]):

| offset | size | dir | verbatim line(s) | meaning |
|---|---|---|---|---|
| rbx+0x0 | 8 | R | 0x674515d  mov rax,[rbx] | qword copied to rdx+0x60 [V] |
| rbx+0x80 | 8 | R/W | 0x6745172  mov rax,[rbx+0x80]<br>0x6745180  mov qword ptr [rbx+0x80],0 | pointer moved out to rsi+0xE0 and the source slot cleared [V] |
| rbx+0x8 | - | R | 0x674516c  call 0xE869FF0 (rdx=lea [rbx+8]) | base passed to callee 0xE869FF0 which fills rdx+0x68 [?] |

## TOOL REQUESTS

None (no helper scripts were written for this unit; the rdis `str 0xF52E07A` / `str 0xF279E80` lookups returned no output, so those addresses are left uninterpreted).
