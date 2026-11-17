## NEXT
Resume at line 401 (address 0x5334F7C) - continue analysis from second global lock sequence, hash table walk, and draw record writes via 0x533f580.

---

# U-H1c: Visibility Event Processor sub_5334850 (0x5334850..0x533A78C, size 0x5F3C)

## Phase Table (0x5334850..0x5334F7C - first 400 lines)

| Range | Description |
|-------|-------------|
| 0x5334850..0x53348E2 | Function prologue, stack frame setup (0x388 bytes), save XMM6-15, early exit if [rcx+0x130] == [rcx+0x138] |
| 0x53348E8..0x53349AD | Timestamp calculation: call 0xEEC5920/0xEEC5930, compare against 0x16E3600/0x989680, compute delta with magic constant 0xB2F4FC0794908CF3 and scale 0x3B9ACA00 (1e9 ns) |
| 0x53349B0..0x53349CE | Store timestamp at [rsi+0x5A8], compare [rsi+0x418] vs [rsi+0x420], update max, save rsi at [rbp+0x250] |
| 0x53349D5..0x5334A27 | Global state init: lock 0x128C4FD0, inc qword [0x128C5030], unlock, read [0x128C5038], check byte==1, load [0x128C5040], inc refcount |
| 0x5334A2C..0x5334ACC | Alt path: zero [rbp+0x38/0x40/0x48/0x58], call 0x3B2020, zero stack buffers [rbp+0x120/0x140/0x150/0x160] |
| 0x5334A61..0x5334AFC | Load rdi=[rbp+0x250], check if [rdi+0x138]-[rdi+0x130] >= 0x11, set [rbp+0x246], init stack buffers [rbp+0x160=0x3F600000], call 0x53D9BE0 |
| 0x5334AD4..0x5334AF7 | Load [rdi+0x138]/[rdi+0x130], compute rsi=rax-rcx, rbx=rax, if zero jump to 0x5334BAA |
| 0x5334AFD..0x5334B4E | sar rsi/4, compute rax=rsi>>4, if rax>>0x3E!=0 jump to 0x533A6F3, if rsi<0x400 jump to 0x5334B54, large alloc path |
| 0x5334B1B..0x5334B78 | Large alloc (rsi>=0x400): call 0x1233E1A8 allocator, r14=result, align, store at [rbp+0x70], call 0xEEC6ED0, store rsi at [rbp+0x68], load [rdi+0x130/0x138], compute diff, sar 4, call 0x12B290 |
| 0x5334BD0..0x5334C1C | Small alloc path: sar rsi/4, overflow check to 0x533A6F9, sar rbx/2, if rsi<0x400 jump to 0x5334C57, alloc via 0x1233E1A8, set up rsi=[r14+rsi*4], call 0xEEC6ED0 |
| 0x5334C1E..0x5334CA8 | Alloc completion: store r14 at [rbp+0x90], rsi at [rbp+0xA0], call 0xEEC6ED0, store rsi at [rbp+0x98], load [rdi+0x128]->[rax+0x480], cvttss2si from [rax+0x5D4], zero [rbp+0x190], load [rax+0x9A8], inc refcount |
| 0x5334CA8..0x5334D37 | Load [rax+0x9A0], store at [rbp+0x190/0x198], call vtable at [rax+0x58] via 0xF99FFA0, dec refcount on rbx, cleanup |
| 0x5334D37..0x5334D67 | Compare r14d with [rax+0x568] and +1, check [rax+0x520], if matches jump to 0x5334ECC |
| 0x5334D6D..0x5334DF1 | Linked list manipulation: [rbx+0x518], zero [rcx], test/list operations, call 0xE935700 |
| 0x5334DFF..0x5334E7A | Error/alt path: zero eax, load [0x128C5048], set up stack frame, test rsi, check byte, crash with 0xDEADC0DE, call allocator, jump to 0x533A0CB or 0x5334A68 |
| 0x5334E7F..0x5334ECC | Buffer fill: shr r9/3, inc, align, movdqu xmm0 fills, finalize stores |
| 0x5334ECC..0x5334F7C | Zero [rbp+0x80], clear flag [rbp+0x247], lock global 0x128D2240, inc counter, unlock, load [0x128D22A8], check byte==1, load [0x128D22B0], inc refcount, load config at [0x128D22B8], read byte at [r14+0x18], check values |

Key instructions (verbatim, max 6 per phase):
```
0x533485c  sub rsp,0x388
0x53348d4  mov rax,[rcx+0x130]
0x53348db  cmp rax,[rcx+0x138]
0x53348e2  je 0x533A069
0x53348ee  call 0xEEC5920
0x53348f6  call 0xEEC5930
```
```
0x53348fb  cmp rbx,0x16E3600
0x5334902  je short 0x5334916
0x5334904  cmp rbx,0x989680
0x5334916  mov r9,0xB2F4FC0794908CF3
0x5334923  imul r9
0x5334944  imul rcx,0x3B9ACA00
```
```
0x53349b0  mov [rsi+0x5A8],rax
0x53349b7  mov rax,[rsi+0x418]
0x53349be  cmp rax,[rsi+0x420]
0x53349c7  mov [rsi+0x420],rax
0x53349ce  mov [rbp+0x250],rsi
0x53349df  call 0xE943178
```
```
0x53349e4  lock inc qword ptr [0x128C5030]
0x53349ef  call 0xE94319C
0x53349f4  mov rsi,[0x128C5038]
0x5334a00  cmp byte ptr [rsi],1
0x5334a05  mov rax,[0x128C5040]
0x5334a15  lock inc dword ptr [rax+8]
```
```
0x5334a2c  mov qword ptr [rbp+0x38],0
0x5334a38  pxor xmm0,xmm0
0x5334a3c  movdqu [rbp+0x48],xmm0
0x5334a49  lea rcx,[0x128C4FD0]
0x5334a50  call 0x3B2020
0x5334a55  mov dword ptr [rbp+0x17C],0
```
```
0x5334a61  mov rdi,[rbp+0x250]
0x5334a68  mov [rbp+0x1DF],al
0x5334a75  sub rax,[rdi+0x130]
0x5334a7c  cmp rax,0x11
0x5334a80  setae [rbp+0x246]
0x5334ac7  call 0x53D9BE0
```
```
0x5334ad4  mov rcx,[rdi+0x130]
0x5334adb  mov rsi,rax
0x5334ade  sub rsi,rcx
0x5334ae1  mov rbx,rax
0x5334af7  je 0x5334BAA
0x5334afd  sar rsi,4
```
```
0x5334b01  mov rax,rsi
0x5334b04  shr rax,0x3E
0x5334b08  jne 0x533A6F3
0x5334b12  cmp rsi,0x400
0x5334b1b  lea r15,[rbx+0x27]
0x5334b30  call qword ptr [0xF99FFA0]
```
```
0x5334bd0  mov rbx,[rdi+0x138]
0x5334bd7  mov rax,[rdi+0x130]
0x5334be4  movdqa [rbp+0x90],xmm6
0x5334c00  sar rsi,4
0x5334c04  mov rax,rsi
0x5334c0b  jne 0x533A6F9
```
```
0x5334c1e  lea r15,[rbx+0x27]
0x5334c30  mov rdx,r15
0x5334c7b  mov [rbp+0x90],r14
0x5334c86  mov [rbp+0xA0],rsi
0x5334c95  call 0xEEC6ED0
0x5334ca8  mov rax,[rdi+0x128]
```
```
0x5334caf  mov rax,[rax+0x480]
0x5334cb6  cvttss2si edi,[rax+0x5D4]
0x5334cc6  mov rcx,[rax+0x9A8]
0x5334ccd  test rcx,rcx
0x5334cf9  mov rax,[rax+0x58]
0x5334cfd  call qword ptr [0xF99FFA0]
```
```
0x5334d37  mov rax,[rbp+0x250]
0x5334d3e  mov eax,[rax+0x568]
0x5334d44  cmp r14d,eax
0x5334d47  je 0x5334ECC
0x5334d6d  mov rbx,[rbp+0x250]
0x5334d98  call 0xE935700
```
```
0x5334dff  xor eax,eax
0x5334e01  mov rbx,[0x128C5048]
0x5334e10  mov [rbp+0x48],rsi
0x5334e35  mov rcx,rbx
0x5334e38  call qword ptr [0xF99FFA0]
0x5334e48  je 0x533A0CB
0x5334e7a  jmp 0x5334A68
```
```
0x5334e7f  shr r9,3
0x5334e83  inc r9
0x5334e9b  xor r11d,r11d
0x5334ea0  movdqu [rdx+r11*8],xmm0
0x5334ec0  mov [r8],rcx
0x5334ecc  mov qword ptr [rbp+0x80],0
```
```
0x5334ed7  mov byte ptr [rbp+0x247],0
0x5334ede  lea rbx,[0x128D2240]
0x5334ee8  call 0xE943178
0x5334eed  lock inc qword ptr [0x128D22A0]
0x5334efd  mov rsi,[0x128D22A8]
0x5334f1d  mov rax,[0x128D22B0]
0x5334f50  movzx eax,byte ptr [r14+0x18]
```

## Strings Referenced (first 400 lines)

| RVA | Text | Site |
|-----|------|------|
| 0x128C4FD0 | (global state object, not a string) | 0x53349D5, 0x5334A49 |
| 0x128C5030 | (global counter, not a string) | 0x53349E4 |
| 0x128C5038 | (global ptr, not a string) | 0x53349F4, 0x5334A19 |
| 0x128C5040 | (global ptr, not a string) | 0x5334A05, 0x5334A20 |
| 0x128C5048 | (global ptr, not a string) | 0x5334E01, 0x5334E0C |
| 0x128D2240 | (global state object, not a string) | 0x5334EDE, 0x5334F24 |
| 0x128D22A0 | (global counter, not a string) | 0x5334EED |
| 0x128D22A8 | (global ptr, not a string) | 0x5334EFD, 0x5334F34 |
| 0x128D22B0 | (global ptr, not a string) | 0x5334F1D, 0x5334F49 |
| 0x128D22B8 | (global config, not a string) | 0x5334F50 |

No ASCII/UTF-8 string literals referenced in first 400 lines. Global RVAs resolve to data structures via rvastr.py (binary blobs, not strings).

## Callees in Order (first 400 lines)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xEEC5920 | Get timestamp | 0x53348EE |
| 0xEEC5930 | Get frequency | 0x53348F6 |
| 0xE943178 | Lock global | 0x53349DF, 0x5334A49, 0x5334EDE, 0x5334F24 |
| 0xE94319C | Unlock global | 0x53349EF, 0x5334F31 |
| 0x3B2020 | Global cleanup | 0x5334A50, 0x5334FE6 |
| 0x53D9BE0 | Helper (buffer init) | 0x5334AC7, 0x5334F83 |
| 0xEEC6ED0 | Buffer clear/memset | 0x5334B8C, 0x5334C95, 0x5334F83 |
| 0x12B290 | Helper | 0x5334BCA |
| 0x533A069 | Early exit | 0x53348E2 |
| 0x533A6F3 | Overflow handler | 0x5334B08 |
| 0x533A6F9 | Overflow handler | 0x5334C0B |
| 0x533A65F | Alloc fail | 0x5334B3D |
| 0x533A66D | Alloc fail | 0x5334B72 |
| 0x533A67E | Alloc fail | 0x5334C40 |
| 0x533A68C | Alloc fail | 0x5334C75 |
| 0x5334BAA | Early exit | 0x5334AF7 |
| 0x5334CA8 | Early exit | 0x5334BFA |
| 0x5334ECC | Completion | 0x5334D47, 0x5334D52, 0x5334D67 |
| 0x533A0CB | Completion | 0x5334E48 |
| 0x5334A55 | Error path | 0x5334A2C, 0x5334E1F, 0x5334E28 |
| 0x5334DFF | Error path | 0x5334A0F |
| 0x5334E01 | Success path | 0x5334A27 |
| 0x5334A68 | Callback | 0x5334E7A |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5334B30, 0x5334B65, 0x5334C30, 0x5334C65, 0x5334CFD, 0x5334E38, 0x5334E68, 0x5334FBB, 0x5334FD1, 0x5334FCD, 0x5335197, 0x5335249 |
| 0xE935700 | Deque push | 0x5334D98 |

## Field Table: [reg+off] Reads/Writes into Output/Description/Draw/Event Objects (first 400 lines)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rsi+0x5A8] | 8 | W | 0x53349B0 | Timestamp result |
| [rsi+0x418] | 8 | R | 0x53349B7 | Compare field |
| [rsi+0x420] | 8 | R/W | 0x53349BE/0x53349C7 | Compare/max field |
| [rbp+0x250] | 8 | W | 0x53349CE | Saved rsi (input ptr) |
| [rbp+0x1DF] | 1 | W | 0x5334A68 | Flag byte |
| [rbp+0x120] | 16 | W | 0x5334A8B | Zeroed buffer |
| [rbp+0x130] | 8 | W | 0x5334A93 | Zeroed |
| [rbp+0x140] | 16 | W | 0x5334A9E | Zeroed |
| [rbp+0x150] | 8 | W | 0x5334AA6 | Zeroed |
| [rbp+0x160] | 4 | W | 0x5334AB1 | Float 0x3F600000 (1.0) |
| [rbp+0x60] | 16 | W | 0x5334AE4 | Zeroed |
| [rbp+0x70] | 8 | W | 0x5334AE9 | Zeroed |
| [rbp+0x68] | 8 | W | 0x5334B91 | Saved rsi |
| [rbp+0x246] | 1 | W | 0x5334A80 | Flag (>=0x11) |
| [rbp+0x200] | 1 | W | 0x5334BAD | Flag=0 |
| [rbp+0x190] | 16 | W | 0x5334BC3 | Buffer |
| [rbp+0x200] | 1 | W | 0x5334CBE | Flag |
| [rbp+0x60] | 16 | W | 0x5334CBE | Buffer |
| [rbp+0x70] | 8 | W | 0x5334C7C | Saved rsi |
| [rbp+0xA0] | 8 | W | 0x5334C86 | rsi pointer |
| [rbp+0x90] | 8 | W | 0x5334C7B | r14 pointer |
| [rbp+0x98] | 8 | W | 0x5334C9A | rsi pointer |
| [rbp+0x1C8] | 8 | W | 0x5335238 | r14 pointer |
| [rdi+0x130] | 8 | R | 0x5334A75 | Source ptr |
| [rdi+0x138] | 8 | R | 0x5334A82 | Source ptr+8 |
| [rdi+0x130] | 8 | R | 0x5334BA3 | Source ptr |
| [rdi+0x138] | 8 | R | 0x5334BAA | Source ptr+8 |
| [rdi+0x128] | 8 | R | 0x5334CA8 | Source ptr |
| [rax+0x480] | 8 | R | 0x5334CAF | Source ptr |
| [rax+0x5D4] | 4 | R | 0x5334CB6 | Float to int (cvttss2si) |
| [rax+0x9A8] | 8 | R | 0x5334CC3 | Ptr (refcounted) |
| [rax+0x9A0] | 8 | R | 0x5334CE1 | Ptr |
| [rbx+0x518] | 8 | R | 0x5334D74 | List head |
| [rbx+0x520] | 8 | R | 0x5334D5F | List tail/check |
| [rbx+0x528] | 8 | R | 0x5334DBE | Ptr |
| [rbx+0x530] | 8 | R | 0x5334DC5 | Ptr |
| [rbp+0x80] | 8 | W | 0x5334ECC | Zero |
| [rbp+0x247] | 1 | W/R | 0x5334ED7/0x5335DD8 | Flag |
| [rbp+0x38] | 8 | W | 0x5334E0C | Ptr |
| [rbp+0x40] | 1 | W | 0x5334E10 | Byte flag |
| [rbp+0x48] | 8 | W | 0x5334E14 | Ptr |
| [rbp+0x50] | 8 | W | 0x5334E18 | Zero |
| [rbp+0x58] | 8 | W | 0x5334E1C | Ptr |
| [rcx+8] | 4 | W | 0x5334A15, 0x5334CD2, 0x5334F0F, 0x53350DF | Refcount++ |
| [rbx+8] | 4 | W | 0x5334D10, 0x5334FAC, 0x53350E3, 0x5335527 | Refcount-- |
| [rbx+0xC] | 4 | W | 0x5334D21, 0x5334FC5, 0x53350E3, 0x533554B | Weak refcount-- |

---

## Phase Table (0x5334F7C..0x53356DB - lines 401-800)

| Range | Description |
|-------|-------------|
| 0x5334F7C..0x5334FD7 | Second global lock cleanup: call 0xEEC6ED0, check [rsi], crash on 0, zero [r14+0x80], dec refcount on rbx, full shared_ptr release |
| 0x5334FD7..0x533509A | Setup loop: store xmm7 at [rbp+0x78], imul edi, call 0x3B2020, zero [rbp+0x200/0x210], load [r14+0x130], compare [rcx+0x1A8] vs [0x1B0], update, cvtsi2ss edi, load constants from 0xF246D38/0xEFFB2B0/0xEFFB2C0/0xEF98220/0xEECF680/0xEEE6700 |
| 0x533509A..0x5335173 | Main loop entry: cmp rdx/[rbp+0x180], store rdx at [rbp+0x100/0x1E8], load [r14+0x130], compute rsi=rax+rcx*16, load [rax+0x9A8], inc refcount, load [rax+0x9A0], compute float at [rdx+0x40C], addss/mulss, store at [rax+rcx*4], bit manipulation on [r8+0x9B0], or/not/and into [rcx+rax*4] |
| 0x5335173..0x5335256 | Alloc struct at 0x1233E1A8 (size 0x70), init vtable 0xF248AB0, populate fields at [r14+8..0x60] with stack addresses, call vtable at [rbx+0x18] with [rbp+0x190] |
| 0x5335257..0x53354D0 | Compare [rbp+0x246], if !=1 jump to 0x53354DE, else compute hash: sub rcx/rax, sar 2, mul 0xAAAAAAAAAAAAAAAB, cvttsd2si, bounds check vs 0xAAAAAAAAAAAAAAB, alloc if needed (0x1233E1A8), copy 0x18-byte chunks from [rbp+0x140] to rbx, grow buffer via 0xE935700 |
| 0x53354D0..0x5335590 | Float path: test rdi, cvtsi2ss, divss by [rbp+0x160], call 0xEEC73F0, cvttss2si, lea rcx=[rbp+0x120], call 0x53D9BE0, compare [rbp+0x200] vs [0x1F0], update [rbp+0x208], dec refcounts, loop to 0x5335090 |
| 0x5335590..0x53356DB | Hash table probe: load byte at [r12], FNV-1a hash (0xCBF29CE484222325, 0x100000001B3) over 12 bytes, compute bucket index, walk linked list at [r14+rdi*8], compare keys at [r10+8/0xC], cmpxchg refcount at [r10+0x14], loop |

Key instructions (verbatim, max 6 per phase):
```
0x5334f7e  call 0xEEC6ED0
0x5334f83  cmp byte ptr [rsi],0
0x5334f88  mov dword ptr [0],0xDEADC0DE
0x5334f97  movdqu [r14+0x80],xmm0
0x5334fac  lock dec dword ptr [rbx+8]
0x5334fbb  call qword ptr [0xF99FFA0]
```
```
0x5334fd7  movss [rbp+0x78],xmm7
0x5334fdf  lea rcx,[0x128D2240]
0x5334fe6  call 0x3B2020
0x5334fef  movdqa [rbp+0x200],xmm6
0x5335002  mov rax,[r14+0x130]
0x533504d  movss xmm8,[0xF246D38]
```
```
0x533509a  cmp rdx,[rbp+0x180]
0x53350a7  mov [rbp+0x100],rdx
0x53350ae  mov rax,[r14+0x130]
0x53350c0  mov rax,[rax+rcx]
0x53350cc  mov rcx,[rax+0x9A8]
0x5335125  movss xmm0,[rdx+0x40C]
```
```
0x5335176  mov qword ptr [rbp+0x10],0
0x5335189  mov rcx,[0x1233E1A8]
0x53351af  lea rax,[0xF248AB0]
0x53351b6  mov [r14],rax
0x5335242  mov rax,[rax+0x18]
0x5335250  call qword ptr [0xF99FFA0]
```
```
0x5335265  cmp byte ptr [rbp+0x246],1
0x5335272  sub rcx,rax
0x5335279  mov rdx,0xAAAAAAAAAAAAAAAB
0x5335287  movq xmm0,rcx
0x53352e5  mov rax,0xAAAAAAAAAAAAAAB
0x533532b  mov rcx,[0x1233E1A8]
```
```
0x5335445  test rdi,rdi
0x5335460  mov rax,rdi
0x533546f  cvtsi2ss xmm0,rdi
0x5335478  divss xmm0,[rbp+0x160]
0x5335480  call 0xEEC73F0
0x53354a8  call 0x53D9BE0
```
```
0x5335590  movzx eax,byte ptr [r12]
0x5335595  mov r9,0xCBF29CE484222325
0x533559f  xor rax,r9
0x53355a2  mov r10,0x100000001B3
0x53355ac  imul rax,r10
0x5335697  mov rax,[r14+rdi*8]
```

## Strings Referenced (lines 401-800)

| RVA | Text | Site |
|-----|------|------|
| 0xF246D38 | (constant float, not string) | 0x533504D |
| 0xEFFB2B0 | (constant, not string) | 0x5335056 |
| 0xEFFB2C0 | (constant, not string) | 0x533505F |
| 0xEF98220 | (constant, not string) | 0x5335068 |
| 0xEECF680 | (constant, not string) | 0x5335071 |
| 0xEEE6700 | (constant, not string) | 0x533507A |
| 0xF248AB0 | (vtable, not string) | 0x53351AF |

No ASCII/UTF-8 string literals referenced in lines 401-800. Constant RVAs resolve to binary data (floats, vtables).

## Callees in Order (lines 401-800)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xEEC6ED0 | Buffer clear/memset | 0x5334F7E, 0x533533C, 0x5335371 |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5334FBB, 0x5334FD1, 0x5335197, 0x5335249, 0x533533C, 0x5335371, 0x533540D, 0x5335537, 0x5335558 |
| 0x3B2020 | Global cleanup | 0x5334FE6 |
| 0xEEC73F0 | Float helper | 0x5335480 |
| 0x53D9BE0 | Buffer init | 0x5334F83, 0x53354A8 |
| 0xE935700 | Deque push/grow | 0x533541D |
| 0xE943178 | Lock global | 0x5334F24 (dup from earlier) |
| 0xE94319C | Unlock global | 0x5334F31 (dup from earlier) |

## Field Table: [reg+off] Reads/Writes (lines 401-800)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [r14+0x80] | 16 | W | 0x5334F97 | Zeroed |
| [rbx+8] | 4 | W | 0x5334FAC, 0x53350DF, 0x53350E3, 0x5335527 | Refcount-- |
| [rbx] | 8 | R | 0x5334FB2, 0x533523F | Vtable ptr |
| [rbx+0xC] | 4 | W | 0x5334FC5, 0x533554B | Weak refcount-- |
| [rbp+0x78] | 4 | W | 0x5334FD7 | Saved xmm7 (float) |
| [rbp+0x200] | 16 | W | 0x5334FEF | Zeroed |
| [rbp+0x210] | 8 | W | 0x5334FF7 | Zeroed |
| [r14+0x130] | 8 | R | 0x5335002, 0x53350AE, 0x5335E3F | Source ptr |
| [rcx+0x1A8] | 8 | R | 0x533500C | Source ptr |
| [rcx+0x1B0] | 8 | R/W | 0x5335013/0x533501C | Compare/max |
| [rbp+0x180] | 8 | W | 0x5335044 | Loop bound |
| [rbp+0x1E8] | 8 | R/W | 0x5335066/0x5335090 | Loop index |
| [rbp+0x100] | 8 | W | 0x53350A7 | Loop index copy |
| [rax+rcx] | 8 | R | 0x53350C0 | Element ptr |
| [rax+0x9A8] | 8 | R | 0x53350CC, 0x53350E3 | Refcounted ptr |
| [rax+0x9A0] | 8 | R | 0x5335106 | Ptr |
| [rdx+0x40C] | 4 | R | 0x533511D | Float source |
| [rax+rcx*4] | 4 | W | 0x533513A | Float result |
| [r8+0x9B0] | 1 | R | 0x5335157 | Byte flag (cmp 2) |
| [rcx+rax*4] | 4 | R/W | 0x5335167/0x5335170/0x5335173 | Bitfield accumulator |
| [rbp+0x10] | 8 | W | 0x5335176 | Zero |
| [rbp+0x1C8] | 8 | W | 0x5335181/0x5335238 | Struct ptr |
| [r14] | 8 | W | 0x53351B6 | Vtable ptr (0xF248AB0) |
| [r14+8] | 8 | W | 0x53351BF | Stack addr [rbp+0x247] |
| [r14+0x10] | 8 | W | 0x53351C8 | Stack addr [rbp+0x10] |
| [r14+0x18] | 8 | W | 0x53351D3 | Stack addr [rbp+0x246] |
| [r14+0x20] | 8 | W | 0x53351DE | Stack addr [rbp+0x200] |
| [r14+0x28] | 8 | W | 0x53351E9 | Ptr [rbp+0x250] |
| [r14+0x30] | 8 | W | 0x53351ED | Ptr rsi |
| [r14+0x38] | 8 | W | 0x53351F5 | Stack addr [rbp-0x40] |
| [r14+0x40] | 8 | W | 0x5335200 | Stack addr [rbp+0x100] |
| [r14+0x48] | 8 | W | 0x533520B | Ptr [rbp+0x1E0] |
| [r14+0x50] | 8 | W | 0x5335213 | Stack addr [rbp+0x60] |
| [r14+0x58] | 8 | W | 0x533521E | Stack addr [rbp+0x1DF] |
| [r14+0x60] | 8 | W | 0x5335229 | Stack addr [rbp+0x80] |
| [r14+0x68] | 8 | W | 0x5335234 | Stack addr [rbp+0x90] |
| [rbp+0x1C8] | 8 | W | 0x5335238 | r14 (struct) |
| [rbx+0x18] | 8 | R | 0x5335242 | Vtable func |
| [rbp+0x200] | 8 | R | 0x5335257 | Ptr |
| [rbp+0x208] | 8 | R/W | 0x533525E/0x53354EA | Ptr |
| [rbp+0x246] | 1 | R | 0x5335265 | Flag |
| [rbp+0x140] | 8 | R | 0x53352C3 | Buffer base |
| [rbp+0x150] | 8 | R | 0x53352CE | Buffer end |
| [rbp+0x148] | 8 | R/W | 0x53352F8/0x533542F | Buffer ptr |
| [rbp+0x150] | 8 | W | 0x533543E | Buffer end updated |
| [rbp+0x120] | 8 | R | 0x53354A1, 0x533567C | Buffer base |
| [rbp+0x128] | 8 | R | 0x5335683 | Buffer end |
| [r12] | 1 | R | 0x5335590 | Key byte 0 |
| [r12+1] | 1 | R | 0x53355B5 | Key byte 1 |
| [r12+2] | 1 | R | 0x53355C3 | Key byte 2 |
| [r12+3] | 1 | R | 0x53355CF | Key byte 3 |
| [r12+4] | 1 | R | 0x53355E6 | Key byte 4 |
| [r12+5] | 1 | R | 0x53355F3 | Key byte 5 |
| [r12+6] | 1 | R | 0x53355FA | Key byte 6 |
| [r12+7] | 1 | R | 0x533560D | Key byte 7 |
| [r12+8] | 1 | R | 0x5335634 | Key byte 8 |
| [r12+9] | 1 | R | 0x5335641 | Key byte 9 |
| [r12+0xA] | 1 | R | 0x533564E | Key byte 10 |
| [r12+0xB] | 1 | R | 0x533565B | Key byte 11 |
| [r14+rdi*8] | 8 | R | 0x5335697 | Hash bucket head |
| [r10] | 8 | R | 0x53356C0 | Next in chain |
| [r10+8] | 4 | R | 0x53356D1 | Key compare |
| [r10+0xC] | 4 | R | 0x53356D8 | Key compare |
| [r10+0x14] | 1 | R/W | 0x533556C | Refcount bitfield (cmpxchg) |

---

## Phase Table (0x53356DC..0x5335E1A - lines 801-1200)

| Range | Description |
|-------|-------------|
| 0x53356DC..0x53357C0 | Hash table probe: walk linked list at [rbp+0x140], compare key bytes at [r12], lock cmpxchg for refcount at [r10+0x14], store matched entry in r13, jump to 0x5335B61 if not found |
| 0x53357C0..0x53358E3 | Hash table insert: compute bucket from hash, lock cmpxchg refcount, on miss call allocator 0x1233E1A8, init new entry with key bytes from r12, store r8/r9/r10/r11, jump to 0x53358E3 to store |
| 0x53358E3..0x53359D5 | Store key-value: copy 8 qwords (64 bytes) from r13 to [rbx+rsi], advance rdx/rsi by 0x18 per element, loop until rdx==r13 (end marker) |
| 0x53359D5..0x5335A86 | Alternate store path: if r13==rax jump to 0x5335A1A, else copy from r13 to [rbx+rax] in 0x18-byte chunks, advance by 0x18, loop |
| 0x5335A1A..0x5335A86 | Finalize: test rcx, compute rdx=0x150-rcx, if <0x1000 call 0xE935700, else grow buffer (mul/div by 0xAAAA...), call 0xE935700 |
| 0x5335A86..0x5335B59 | Finalize insert: sub rax,rbx, sar 3, mul by 0xAAAA..., store at [rcx+rdi*8], compute rdx=[rbp+0x128]-[rbp+0x120], sar 3, js/cvtsi2ss path |
| 0x5335AE0..0x5335B59 | Float path: cvtsi2ss/addss/divss/mulss/cvttss2si, compute r11 from xmm0, compare r8/r11, call 0x53D9BE0 |
| 0x5335B59..0x5335C09 | Hash bucket full: compute r10, set bit in [r10+0x14], inc r12 by 0xC, loop to 0x5335590 or 0x53354D0 |
| 0x5335C09..0x5335DAA | Completion/cleanup: cmp [rbp+0x246], if zero jump to 0x5335DAA, else iterate rsi/rdi, sar 3, mul by 0xAAAA..., call 0x53C5B50, loop to 0x5335DAA |
| 0x5335DAA..0x5335E1A | Main loop restart: mov r14=[rbp+0x250], compute timestamp delta (r14+0x450 - 0x448) sar 2, mul by 0xAAAA..., store at [r14+0x570], check [rbp+0x247], call 0xEEC5920/0xEEC5930, timestamp magic again, jmp to 0x5335EFF |

Key instructions (verbatim, max 6 per phase):
```
0x53356dc  jne short 0x53356C0
0x53356de  cmp [r10+0x10],r9d
0x53356e4  mov rcx,[rbp+0x100]
0x53356eb  cmp [rbp+0x148],r10
0x5335720  mov r10,[r10]
0x5335729  lea r11,[r10+r10*2]
```
```
0x5335760  mov r13,[rbp+0x148]
0x5335770  mov [r13],rax
0x5335774  mov eax,[r12]
0x533578e  mov byte ptr [r13+0x14],0
0x533579a  mov rax,[rbp+0x148]
0x53357a5  mov [rbp+0x148],rax
```
```
0x53358e3  mov rax,[r14+rdi*8]
0x53358e7  mov [rbx+rsi],rax
0x53358eb  mov eax,[r12]
0x53358f3  mov eax,[r12+4]
0x5335930  mov rdx,[rcx+rax]
0x5335934  mov [rbx+rax],rdx
```
```
0x53359d5  cmp rcx,r13
0x53359e0  mov rdx,[rcx+rax]
0x53359e4  mov [rbx+rax],rdx
0x5335a1a  mov rcx,[rbp+0x140]
0x5335a26  mov rdx,[rbp+0x150]
0x5335a55  call 0xE935700
```
```
0x5335a86  sub rax,rbx
0x5335a89  sar rax,3
0x5335a8d  mov rcx,0xAAAAAAAAAAAAAAAB
0x5335a97  imul rax,rcx
0x5335aa9  mov rdx,[rbp+0x128]
0x5335ae0  mov r9,r8
```
```
0x5335b59  lea r10,[rax+rcx]
0x5335b5d  add r10,0xFFFFFFFFFFFFFFE8
0x5335b61  mov eax,1
0x5335b66  mov rcx,[rbp+0x248]
0x5335b6f  mov [r10+0x14],al
0x5335b73  add r12,0xC
0x5335b77  cmp r12,[rbp+0x1F0]
```
```
0x5335c09  cmp byte ptr [rbp+0x246],0
0x5335c16  mov rsi,[rbp+0x140]
0x5335c4d  mov rdx,[r8+0x458]
0x5335c62  sar rdx,2
0x5335c8c  call 0x53C5B50
0x5335cec  lea rdx,[rbp+0x190]
0x5335cf6  call 0x2F6DF0
```
```
0x5335d20  movzx eax,byte ptr [r8]
0x5335d24  mov [rdx],al
0x5335d26  inc qword ptr [rcx+0x468]
0x5335d4d  mov eax,[rsi+8]
0x5335d58  mov eax,[rsi+0x10]
0x5335d66  jmp short 0x5335D7D
0x5335d77  call 0x53C5CE0
```
```
0x5335daa  mov r14,[rbp+0x250]
0x5335db1  mov rax,[r14+0x450]
0x5335dbf  sar rax,2
0x5335dc3  mov rcx,0xAAAAAAAAAAAAAAAB
0x5335dd1  mov [r14+0x570],rax
0x5335de1  call 0xEEC5920
```

## Strings Referenced (lines 801-1200)

| RVA | Text | Site |
|-----|------|------|
| 0x1233E1A8 | (global allocator, not a string) | 0x5335877, 0x53358B7, 0x53358C5, 0x5335B66, 0x5335BAE, 0x5335BBA, 0x5335BBE, 0x5335BC9, 0x5335C8C, 0x5335CF6, 0x5335D77, 0x5335D9B |
| 0xF248AB0 | (vtable, not a string) | 0x53351AF (earlier) |
| 0x9BC830 | (allocator helper, not a string) | 0x53358D6, 0x5335B90, 0x5335BA0, 0x5335BAB, 0x5335BBE, 0x5335C04, 0x5335C7C |
| 0xE935700 | (deque push, not a string) | 0x533541D, 0x5335A55, 0x5335C04, 0x5335D0F |
| 0x53C5B50 | (helper, not a string) | 0x5335C8C, 0x5335D77 |
| 0x2F6DF0 | (helper, not a string) | 0x5335CF6 |
| 0x53C5CE0 | (helper, not a string) | 0x5335D77 |
| 0x2F6F30 | (helper, not a string) | 0x5335D9B |

No ASCII/UTF-8 string literals referenced in lines 801-1200.

## Callees in Order (lines 801-1200)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5335877, 0x53358B7, 0x53358C5, 0x5335B66, 0x5335BAE, 0x5335BBA, 0x5335BBE, 0x5335BC9, 0x5335C8C, 0x5335CF6, 0x5335D77, 0x5335D9B |
| 0x9BC830 | Allocator helper | 0x53358D6, 0x5335B90, 0x5335BA0, 0x5335BAB, 0x5335BBE, 0x5335C04, 0x5335C7C |
| 0xE935700 | Deque push/grow | 0x533541D, 0x5335A55, 0x5335C04, 0x5335D0F |
| 0x53D9BE0 | Buffer init | 0x53354A8, 0x5335B42 |
| 0x53C5B50 | Helper | 0x5335C8C, 0x5335D77 |
| 0x2F6DF0 | Helper | 0x5335CF6 |
| 0x53C5CE0 | Helper | 0x5335D77 |
| 0x2F6F30 | Helper | 0x5335D9B |
| 0xEEC5920 | Get timestamp | 0x5335DE1, 0x5335E3A |
| 0xEEC5930 | Get frequency | 0x5335DE9, 0x5335E42 |
| 0x533A659 | Overflow handler | 0x5335835, 0x533586D |
| 0x533A6D5 | Overflow handler | 0x533586D |
| 0x533A6BB | Buffer grow | 0x5335410, 0x5335A48, 0x5335BF7, 0x5335C7C, 0x5335A48 |
| 0x533A6E1 | Overflow handler | 0x53352F2, 0x5335C7C |
| 0x533A6ED | Overflow handler | 0x5335321, 0x5335331 |
| 0x533A711 | Overflow handler | 0x5335C7C, 0x5335C82 |
| 0x533A717 | Overflow handler | 0x5335CE6, 0x5335D14 |
| 0x5335BAA | Early exit | 0x5335C10 |
| 0x53354D0 | Loop continue | 0x5335B7E, 0x5335B84 |
| 0x5335590 | Hash loop | 0x533557D, 0x5335B7E |
| 0x53358E1 | Alloc zero path | 0x5335845 |
| 0x53359D5 | Alt store | 0x533591B, 0x5335943, 0x5335974 |
| 0x5335A1A | Finalize | 0x5335974, 0x53359D3, 0x5335A18 |
| 0x5335DAA | Completion | 0x5335C10, 0x5335D0F, 0x5335D34, 0x5335DA8 |
| 0x5335EFF | Timestamp restart | 0x5335E1A, 0x5335E48, 0x5335EAE |

## Field Table: [reg+off] Reads/Writes (lines 801-1200)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [r10+0x10] | 4 | R | 0x53356DE | Key compare (3rd dword) |
| [r10+0xC] | 4 | R | 0x53356D8, 0x533573C | Key compare (2nd dword) |
| [r10+8] | 4 | R | 0x53356D1, 0x5335731 | Key compare (1st dword) |
| [r10+0x14] | 1 | R/W | 0x533556C, 0x5335B6F | Refcount bitfield (cmpxchg/or) |
| [rbp+0x248] | 8 | W | 0x533570A, 0x53357C7 | Loop index copy |
| [rbp+0x148] | 8 | R/W | 0x533576E/0x53357A5 | Buffer current ptr |
| [rbp+0x150] | 8 | R | 0x533576E, 0x53357DC | Buffer end |
| [r13] | 8 | W | 0x5335770 | New entry ptr |
| [r13+8] | 4 | W | 0x5335778 | Key dword 0 |
| [r13+0xC] | 4 | W | 0x5335781 | Key dword 1 |
| [r13+0x10] | 4 | W | 0x533578A | Key dword 2 |
| [r13+0x14] | 1 | W | 0x533578E | Key byte 3 (zero) |
| [rbp+0x140] | 8 | R | 0x5335793, 0x533590A | Buffer base |
| [rbp+0x148] | 8 | W | 0x53357A5, 0x5335911 | Buffer current |
| [rbx+rsi] | 8 | W | 0x53358E7 | Key-value store (qword) |
| [rbx+rsi+8] | 4 | W | 0x53358EF | Key-value store (dword) |
| [rbx+rsi+0xC] | 4 | W | 0x53358F3 | Key-value store (dword) |
| [rbx+rsi+0x10] | 4 | W | 0x53358FC | Key-value store (dword) |
| [rbx+rsi+0x14] | 1 | W | 0x5335905 | Key-value store (byte) |
| [rcx+rax] | 8 | R | 0x5335930, 0x53359E0 | Source element |
| [rbx+rax] | 8 | W | 0x5335934, 0x53359E4 | Dest element |
| [rcx+rax+8] | 4 | R | 0x5335938, 0x53359EC | Source element |
| [rbx+rax+8] | 4 | W | 0x533593C, 0x53359E8 | Dest element |
| [rcx+rax+0xC] | 4 | R | 0x5335940, 0x53359F0 | Source element |
| [rbx+rax+0xC] | 4 | W | 0x5335944, 0x53359EC | Dest element |
| [rcx+rax+0x10] | 4 | R | 0x5335948, 0x53359F8 | Source element |
| [rbx+rax+0x10] | 4 | W | 0x533594C, 0x53359FC | Dest element |
| [rcx+rax+0x14] | 1 | R | 0x5335950, 0x5335A00 | Source element |
| [rbx+rax+0x14] | 1 | W | 0x5335955, 0x5335A05 | Dest element |
| [rcx+rdx-0x14] | 8 | W | 0x5335995 | Reverse copy |
| [rcx+rdx-0xC] | 4 | W | 0x533599F | Reverse copy |
| [rcx+rdx-8] | 4 | W | 0x53359A4 | Reverse copy |
| [rcx+rdx-4] | 4 | W | 0x53359AE | Reverse copy |
| [rcx+rdx] | 1 | W | 0x53359BE | Reverse copy |
| [rbp+0x140] | 8 | W | 0x5335A5A | New buffer base |
| [rbp+0x148] | 8 | W | 0x5335A70 | New buffer current |
| [rbp+0x150] | 8 | W | 0x5335A7F | New buffer end |
| [rcx+rdi*8] | 8 | W | 0x5335AA9 | Hash bucket store |
| [rbp+0x120] | 8 | R | 0x5335AA9, 0x5335B45 | Buffer base |
| [rbp+0x128] | 8 | R | 0x5335AA9, 0x5335B0A | Buffer end |
| [rbp+0x140] | 8 | R | 0x5335B48 | Buffer base |
| [rbp+0x148] | 8 | R | 0x5335B4F | Buffer current |
| [r10+0x14] | 1 | W | 0x5335B6F | Set bit in refcount |
| [r12] | 8 | R/W | 0x5335B73/0x5335590 | Key pointer (advances by 0xC) |
| [rbp+0x1F0] | 8 | R | 0x5335B77, 0x53354C3 | Limit |
| [rbp+0x200] | 8 | R | 0x5335BC9 | Ptr |
| [rbp+0x210] | 8 | R | 0x5335BDC | Ptr |
| [rbp+0x140] | 8 | R | 0x5335C16 | Buffer base |
| [rbp+0x148] | 8 | R | 0x5335C1D | Buffer current |
| [r8+0x458] | 8 | R | 0x5335C4D | Source ptr |
| [r8+0x448] | 8 | R | 0x5335C54 | Source ptr |
| [r8+0x450] | 8 | R/W | 0x5335C54/0x5335D5E | Source ptr + counter |
| [r8+0x460] | 8 | R | 0x5335CC2 | Source ptr |
| [r8+0x470] | 8 | R | 0x5335CD0 | Source ptr |
| [r8+0x468] | 8 | R/W | 0x5335CD7/0x5335D26 | Counter |
| [rbp+0x190] | 8 | W | 0x5335C3F, 0x5335CBB | Computed count |
| [rsi+8] | 4 | R | 0x5335D4D | Element field |
| [rdx] | 4 | W | 0x5335D50 | Dest field |
| [rsi+0xC] | 4 | R | 0x5335D52 | Element field |
| [rdx+4] | 4 | W | 0x5335D55 | Dest field |
| [rsi+0x10] | 4 | R | 0x5335D58 | Element field |
| [rdx+8] | 4 | W | 0x5335D5B | Dest field |
| [rcx+0x450] | 8 | W | 0x5335D5E | Counter increment |
| [r8] | 1 | R | 0x5335D20 | Byte source |
| [rdx] | 1 | W | 0x5335D24 | Byte dest |
| [rcx+0x468] | 8 | W | 0x5335D26 | Counter increment |
| [rsi+0x14] | 1 | R | 0x5335D81 | Element byte |
| [rcx+0x468] | 8 | R | 0x5335D88 | Counter |
| [rcx+0x470] | 8 | R | 0x5335D8F | Limit |
| [r14+0x450] | 8 | R | 0x5335DB1 | Timestamp source |
| [r14+0x448] | 8 | R | 0x5335DB8 | Timestamp source |
| [r14+0x570] | 8 | W | 0x5335DD1 | Timestamp delta result |
| [rbp+0x247] | 1 | R | 0x5335DD8 | Flag check |
| [rbp+0x170] | 8 | W | 0x5335E04 | Zero |
| [rbp+0xF8] | 8 | W | 0x5335E13 | Timestamp/computed |

---

## Phase Table (0x5335E1F..0x5336526 - lines 1201-1600)

| Range | Description |
|-------|-------------|
| 0x5335E1F..0x5335EAC | Timestamp path 1: zero [rbp+0x170/0xF8], jmp to 0x5335EFF |
| 0x5335E3A..0x5335EAC | Timestamp path 2 (freq=0x16E3600): magic 0xB2F4FC0794908CF3, mul/div, store at [rbp+0xF8], jmp to 0x5335EFF |
| 0x5335EAE..0x5335EFF | Timestamp path 3 (freq=0x989680): or rbx, div, magic 0x4D0B03F86B6F730D/0xC4653600, mul/div, store at [rbp+0xF8], jmp to 0x5335EFF |
| 0x5335EFF..0x5335FC0 | Main loop setup: load r12=[r14+0x450]-[0x448], sar 2, mul 0xAAAA..., store ptrs at [rbp+0x88/0x30], zero [rbp+0x178/0x230], load constants 0xEF3F044/0xEEE7C00/0xF0B8810, jmp to 0x5335FC0 |
| 0x5335FC0..0x5336070 | Main loop body: load bytes from [rbp+0x1E0/0x1E8], compare rcx vs r12, if rcx>=r12 jump to 0x5336070, else load [r14+0x460], mask byte, inc rcx, load [r14+0x130/0x138], compare, jmp to 0x53362C1 |
| 0x5336070..0x53362C1 | Alt path (rcx>=r12): set dil=1, zero r15, compare rcx/r12, test r10, load [r10+0x10], check byte [r10+8]&0x20, check [rcx], load [rcx+0x1C], sar 4, movq [rbp+0x200], check [r10+0x20]/[rcx+0x28], store byte at [rcx+0x3F], float math on [rax+0x14/0x18/0x1C], store at [r10]/[r10+4] |
| 0x533619A..0x53362B0 | Check [rcx+4]==1, load [rcx+0x28], test -1, load [rbp+0x250]->[rcx+0x128]->[0x390], test byte [rax+0x28]&0x20, cmovne, compare, load [rax+8]+0x3C, compare, load byte [rax+9], check ==1, load [rax+0x10], check [rax+4]==1, check [rdx+0x28]&2, compare [rax] vs [rcx+0x20], load byte [rax+0x25E], compare with [rcx+0xA], test [rax+8]&2 |
| 0x5336284..0x53362C1 | Load [r14+0x130/0x138] into rsi/rbx, jmp to 0x53368F1/0x53368A3/0x533629E |
| 0x53362C1..0x533642E | Element processing: load [rbx], [rax+0x5E8], check [rdx+0xEC]>0, load [rbp+0x248], compare [rdx+0xC8/0xD4/0xCC/0xD8/0xD0/0xDC], bounds check, float math with constants 0xEF3F044/0xEEE7C00/0xF0B8800/0xF0B8810, ucomiss, load [rdx+0xF8/0x100], imul/index, lock inc/dec refcounts at [rcx+8]/[rdi+8]/[rdi+0xC], call allocator 0xF99FFA0 |
| 0x533642E..0x5336526 | Alloc fail path: call 0x53D92F0, test rax, call 0x53D96D0, check [rax+0x10], check [rax] byte==1, test [rax+8]&0x20, call 0x5340B30, check [rax+0xB0] vs [rsi+0x5A8], call 0x5340B30 again |

Key instructions (verbatim, max 6 per phase):
```
0x5335e1f  mov qword ptr [rbp+0x170],0
0x5335e2a  mov qword ptr [rbp+0xF8],0
0x5335e35  jmp 0x5335EFF
0x5335e3a  mov qword ptr [rbp+0x170],0
0x5335e45  mov rdx,0xB2F4FC0794908CF3
0x5335e52  imul rdx
```
```
0x5335eae  mov rcx,rax
0x5335eb1  or rcx,rbx
0x5335eb4  shr rcx,0x20
0x5335eba  cqo
0x5335ebc  idiv rbx
0x5335ec5  imul r8,rax,0xFFFFFFFFC4653600
```
```
0x5335eff  mov r12,[r14+0x450]
0x5335f06  sub r12,[r14+0x448]
0x5335f0d  sar r12,2
0x5335f11  mov rax,0xAAAAAAAAAAAAAAAB
0x5335f1b  imul r12,rax
0x5335f43  movss xmm7,[0xEF3F044]
```
```
0x5335fc0  mov [rbp+0x238],r8
0x5335fc7  mov rcx,[rbp+0x230]
0x5335fce  test al,1
0x5335fd0  jne 0x5336B3B
0x5335fd6  mov r13,r9
0x5335fde  mov [rbp+0x1E8],dl
```
```
0x5335fea  mov r10b,1
0x5335fed  cmp byte ptr [rbp+0x246],1
0x5335ff6  mov rax,[r14+0x460]
0x5335ffd  movzx r10d,byte ptr [rax+rcx]
0x5336002  and r10b,0xF
0x5336011  mov rbx,[r14+0x130]
```
```
0x5336070  mov dil,1
0x5336073  xor r15d,r15d
0x533608c  xor eax,eax
0x53360d1  mov rcx,[r10+0x10]
0x53360e8  test byte ptr [r10+8],0x20
0x5336102  mov eax,[rcx+0x1C]
```
```
0x533619a  mov eax,[rcx+4]
0x53361a0  mov [rbp+0x1E0],sil
0x53361ad  mov rax,[rcx+0x28]
0x53361ba  mov rdx,[rax]
0x53361c3  mov rcx,[rbp+0x250]
0x53361d8  test byte ptr [rax+0x28],0x20
```
```
0x5336284  mov rax,[rbp+0x250]
0x533628b  mov rsi,[rax+0x130]
0x5336292  mov rbx,[rax+0x138]
0x5336299  jmp 0x53368F1
0x53362c1  mov rax,[rbx]
0x53362cb  mov eax,[rdx+0xEC]
```
```
0x533642e  lock inc dword ptr [rcx+8]
0x5336432  mov rsi,[rax]
0x5336435  mov rdi,[rax+8]
0x5336442  lock dec dword ptr [rdi+8]
0x5336452  mov rcx,rdi
0x5336455  call qword ptr [0xF99FFA0]
0x533646f  call qword ptr [0xF99FFA0]
```
```
0x533647a  mov rcx,[rbp+0x88]
0x5336481  call 0x53D92F0
0x533648f  lea rdx,[rbp+0x200]
0x5336496  call 0x53D96D0
0x53364ac  cmp byte ptr [rdx],1
0x53364c5  mov rcx,[rbp+0x30]
0x53364d7  call 0x5340B30
```

## Strings Referenced (lines 1201-1600)

| RVA | Text | Site |
|-----|------|------|
| 0xEF3F044 | (constant float, not string) | 0x5335F43 |
| 0xEEE7C00 | (constant float, not string) | 0x5335F4B |
| 0xF0B8810 | (constant, not string) | 0x5335F54 |
| 0xF0B8800 | (constant, not string) | 0x53363B0 |

No ASCII/UTF-8 string literals referenced in lines 1201-1600.

## Callees in Order (lines 1201-1600)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xEEC5920 | Get timestamp | (earlier, not in this range) |
| 0xEEC5930 | Get frequency | (earlier, not in this range) |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5336455, 0x533646F |
| 0x53D92F0 | Helper (alloc?) | 0x5336481 |
| 0x53D96D0 | Helper | 0x5336496 |
| 0x5340B30 | Draw record handler | 0x53364D7, 0x533651F |
| 0x53D9BE0 | Buffer init | (earlier) |
| 0xEEC73F0 | Float helper | (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 1201-1600)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rbp+0x170] | 8 | W | 0x5335E1F, 0x5335E3A, 0x5335EEA | Zero/init |
| [rbp+0xF8] | 8 | W | 0x5335E2A, 0x5335EA5, 0x5335EF8 | Timestamp/computed |
| [r14+0x450] | 8 | R | 0x5335EFF, 0x5335DB1 | Timestamp source |
| [r14+0x448] | 8 | R | 0x5335F06, 0x5335DB8 | Timestamp source |
| [rbp+0x88] | 8 | W | 0x5335F26 | Ptr [r14+0x148] |
| [rbp+0x30] | 8 | W | 0x5335F34 | Ptr [r14+0x478] |
| [rbp+0x178] | 4 | W | 0x5335F3B | Zero float |
| [rbp+0x28] | 8 | W | 0x5335F63 | Ptr [rbp+0x200] |
| [rbp+0x230] | 8 | W | 0x5335F6F, 0x533600A, 0x5336076 | Loop counter |
| [rbp+0x188] | 8 | W | 0x5335F82 | r12 copy |
| [rbp+0x1E0] | 1 | R/W | 0x5335F92/0x53361A0 | Byte (sil) |
| [rbp+0x1E8] | 1 | R/W | 0x5335F9B/0x5336090/0x5336133 | Byte (dl/cl) |
| [rbp+0x238] | 8 | R/W | 0x5335FC0/0x533602A/0x5336205 | Draw record ptr |
| [rbp+0xF0] | 8 | R/W | 0x5335FAB/0x5336047 | Ptr (r13) |
| [rbp+0x246] | 1 | R | 0x5335FED | Flag |
| [r14+0x460] | 8 | R | 0x5335FF6 | Ptr to byte array |
| [rax+rcx] | 1 | R | 0x5335FFD | Byte from array |
| [rbp+0x230] | 8 | W | 0x533600A | Incremented counter |
| [r14+0x130] | 8 | R | 0x5336011, 0x533628B | Source ptr |
| [r14+0x138] | 8 | R | 0x5336018, 0x5336292 | Source ptr |
| [rbp+0x1F0] | 8 | W | 0x533602D | r11 copy |
| [rbp+0x248] | 8 | W | 0x533605D | Computed ptr |
| [rbp+0x1FF] | 1 | W | 0x5336039 | r10b copy |
| [r10+0x10] | 8 | R | 0x53360D1 | Ptr |
| [r10+8] | 1 | R | 0x53360E8 | Flag byte (test 0x20) |
| [rcx] | 1 | R | 0x53360F1 | Byte check |
| [rcx+0x1C] | 4 | R | 0x5336102 | Value (sar 4) |
| [rcx+0x14] | 8 | R | 0x5336105 | Float pair (movq) |
| [rbp+0x200] | 8 | W | 0x5336112 | xmm0 save |
| [rbp+0x208] | 4 | W | 0x533611A | Int save |
| [r10+0x20] | 8 | R | 0x5336120 | Ptr check |
| [rcx+0x28] | 8 | R | 0x5336127 | Ptr check |
| [rcx+0x3F] | 1 | W | 0x5336139 | Byte store (from [rbp+0x1E8]) |
| [rax+0x14] | 4 | R | 0x5336145 | Int field |
| [rax+0x1C] | 4 | R | 0x5336152 | Int field |
| [rax+0x18] | 4 | R | 0x5336155 | Int field |
| [rbp-0x18] | 4 | R | 0x533615C, 0x533616B, 0x5336175 | Float constants |
| [r10+4] | 4 | W | 0x5336187 | Float result |
| [r10] | 4 | W | 0x5336195 | Float result |
| [rcx+4] | 4 | R | 0x533619A | Compare (==1) |
| [rcx+0x28] | 8 | R | 0x53361AD | Ptr |
| [rax] | 8 | R | 0x53361BA | Ptr (cmp -1) |
| [rbp+0x250] | 8 | R | 0x53361C3 | Context ptr |
| [rcx+0x128] | 8 | R | 0x53361CA | Nested ptr |
| [rcx+0x390] | 8 | R | 0x53361D1 | Nested ptr |
| [rax+0x28] | 1 | R | 0x53361D8 | Flag byte (test 0x20) |
| [rdx+0x14] | 8 | R | 0x53361DD | Ptr (cmovne) |
| [rax+8] | 8 | R | 0x53361ED | Ptr |
| [rax+0x3C] | 8 | R | 0x53361F1 | Ptr (+0x3C) |
| [rax+9] | 1 | R | 0x5336205 | Byte (cmp 1) |
| [rax+0x10] | 8 | R | 0x5336218 | Ptr |
| [rax+4] | 4 | R | 0x5336225 | Int (cmp 1) |
| [rdx+0x28] | 1 | R | 0x5336243 | Flag byte (test 2) |
| [rax] | 8 | R | 0x5336253 | Ptr compare |
| [rcx+0x20] | 8 | R | 0x533625A | Ptr compare |
| [rax+0x25E] | 1 | R | 0x5336260 | Byte (depth?) |
| [rcx+0xA] | 1 | R | 0x533626E | Byte compare |
| [rax+8] | 1 | R | 0x5336273 | Flag byte (test 2) |
| [rbx] | 8 | R | 0x53362C1 | Element ptr |
| [rax+0x5E8] | 8 | R | 0x53362C4 | Nested ptr |
| [rdx+0xEC] | 4 | R | 0x53362CB | Int check (>0) |
| [rbp+0x248] | 8 | R | 0x53362D5 | Ptr |
| [rcx] | 4 | R | 0x53362DC | Int load |
| [rdx+0xC8] | 4 | R | 0x53362E5 | Int load |
| [rdx+0xD4] | 4 | R | 0x53362EC | Int load |
| [rdx+0xCC] | 4 | R | 0x533630C | Int load |
| [rdx+0xD8] | 4 | R | 0x533631B | Int load |
| [rdx+0xD0] | 4 | R | 0x5336339 | Int load |
| [rdx+0xDC] | 4 | R | 0x533634C | Int load |
| [rdx+0xE0] | 4 | R | 0x53363A2 | Int load |
| [rdx+0xF8] | 8 | R | 0x53363EF | Ptr |
| [rdx+0x100] | 8 | R | 0x53363F6 | Ptr |
| [rbp+0x1D0] | 4 | W | 0x533633F | Computed |
| [rbp+0x180] | 4 | W | 0x5336353 | Computed |
| [r10+rcx] | 8 | R | 0x533641C | Indexed ptr |
| [r10+rcx+8] | 8 | R | 0x5336425 | Ptr (test) |
| [rcx+8] | 4 | W | 0x533642E | Refcount++ |
| [rax] | 8 | R | 0x5336432 | Ptr (rsi) |
| [rax+8] | 8 | R | 0x5336435 | Ptr (rdi) |
| [rdi+8] | 4 | W | 0x5336442 | Refcount-- |
| [rdi] | 8 | R | 0x533644C | Vtable |
| [rdi+0xC] | 4 | W | 0x533645B | Weak refcount-- |
| [rbp+0x88] | 8 | R | 0x533647A | Ptr |
| [rbp+0x30] | 8 | R | 0x53364C5, 0x533651B | Ptr |
| [rbp+0x238] | 8 | R | 0x53364A3, 0x53364B1, 0x53364E7 | Draw record ptr |
| [rax+0x10] | 8 | R | 0x53364AA, 0x53364F2 | Nested ptr |
| [rdx] | 1 | R | 0x53364AC | Byte (cmp 1) |
| [rax+8] | 1 | R | 0x53364B8 | Flag byte (test 0x20) |
| [rsi+0x5A8] | 8 | R | 0x5336512 | Timestamp compare |
| [rax+0xB0] | 8 | R | 0x533650B | Timestamp compare |

---

## Phase Table (0x533652D..0x5336C84 - lines 1601-2000)

| Range | Description |
|-------|-------------|
| 0x533652D..0x5336604 | Draw record path: call 0x5340B30, test [r8+8]&8, load [rax+0x68], call allocator via [rcx+0xC8], call 0x792C3E0, load [r8+0x20], call 0x533F580 with [rbp+0x190], **write [rax+0x63]=bl** (depth byte from [rax+0x25E]), test [r8+8]&1 |
| 0x5336604..0x533677F | Hash lookup: test [rsi+0x520], FNV-1a hash over 12 bytes at [rbp+0x200..0x20B], compute bucket, walk linked list at [rsi+0x518/0x528], compare keys at [rcx+0x10/0x14/0x18], jump to 0x5336AA6 on match |
| 0x533677F..0x53368F1 | Append to array: compare [rsi+0x420] vs [0x428], store [rbp+0x238] at [rcx], inc [rsi+0x420] by 8, jmp to 0x5336A5D, else grow buffer via 0x53D92F0/0x53D96D0 |
| 0x53368F1..0x5336985 | Element iteration: cmp rsi/rbx, call 0x533F160, check [rbp+0x190], dec refcount on [rbp+0x198], call 0x533F8D0, cleanup |
| 0x5336985..0x5336A5D | Array grow: store [rbp+0x238] at [rcx+r14], compute new capacity (mul/div 0xAAAA...), alloc via 0x1233E1A8, copy via 0xEEC6DE0, update [rsi+0x418/0x420/0x428], inc [rbp+0x170], addss [rbp+0x178] |
| 0x5336A5D..0x5336B3B | Loop continue: jmp to 0x5335FC0, or match found at 0x5336AA6, or zero [rbp+0x190], call 0x533F8D0, dec refcounts |
| 0x5336B3B..0x5336C84 | Next frame: sync [r14+0x448/0x450], [r14+0x460/0x468], check [r14+0x488], load constants 0xEFD33B4/0xEFD33B0/0xEFD3390/0xEFD3380, copy 0xC-byte chunks from [rax] to [rdx], call 0x53C5CE0, compare [rax] vs [r14+0x500], load [r14+0x4C0], check byte [r14+0x10]==1 |

Key instructions (verbatim, max 6 per phase):
```
0x533652d  call 0x5340B30
0x533653f  test byte ptr [r8+8],8
0x533655f  movzx r8d,byte ptr [rax+0x25E]
0x53365e8  call 0x533F580
0x53365fa  mov [rax+0x63],bl
0x5336604  test byte ptr [r8+8],1
```
```
0x533661d  movzx eax,byte ptr [rbp+0x200]
0x5336624  mov r9,0xCBF29CE484222325
0x533662e  xor rax,r9
0x5336631  mov r10,0x100000001B3
0x5336711  add rdx,r8
0x5336714  xor rdx,rax
```
```
0x533677f  mov rcx,[rsi+0x420]
0x5336786  cmp rcx,[rsi+0x428]
0x533678f  mov rax,[rbp+0x238]
0x5336796  mov [rcx],rax
0x5336799  add qword ptr [rsi+0x420],8
0x53367a6  mov rcx,[rbp+0x88]
```
```
0x53368f1  cmp rsi,rbx
0x533690b  call 0x533F160
0x5336910  cmp qword ptr [rbp+0x190],0
0x5336925  test r14,r14
0x5336928  je short 0x53368ED
0x533692a  lock dec dword ptr [r14+8]
0x533692f  jne short 0x53368ED
```
```
0x5336985  mov rax,[rbp+0x238]
0x533698c  mov [rcx+r14],rax
0x5336993  mov r14,[rbp+0x248]
0x53369c2  sub r8,rdx
0x53369c5  call 0xEEC6DE0
0x5336a2d  call 0xE935700
```
```
0x5336a5d  mov rax,[rbp+0x170]
0x5336a64  inc eax
0x5336a66  mov [rbp+0x170],rax
0x5336a75  mov rax,[rbp+0x238]
0x5336a7c  addss xmm0,[rax+0xC]
0x5336a81  movss [rbp+0x178],xmm0
0x5336a9a  mov r14,[rbp+0x250]
```
```
0x5336b3b  mov rax,[r14+0x448]
0x5336b42  cmp rax,[r14+0x450]
0x5336b4b  mov [r14+0x450],rax
0x5336b59  cmp rax,[r14+0x468]
0x5336b62  mov [r14+0x468],rax
0x5336b77  lea rax,[r14+0x4F8]
0x5336bb3  movq xmm8,[0xEFD3390]
```
```
0x5336c20  add r8,0x10
0x5336c24  mov rcx,[rbp+0x238]
0x5336c2b  call 0x53C5CE0
0x5336c3f  mov rax,[rbp+0x238]
0x5336c4b  mov rcx,[r14+0x4C0]
0x5336c52  cmp byte ptr [r14+0x10],1
0x5336c5d  mov rax,[rcx]
```

## Strings Referenced (lines 1601-2000)

| RVA | Text | Site |
|-----|------|------|
| 0xEFD33B4 | (constant float, not string) | 0x5336BA1 |
| 0xEFD33B0 | (constant float, not string) | 0x5336BAA |
| 0xEFD3390 | (constant, not string) | 0x5336BB3 |
| 0xEFD3380 | (constant, not string) | 0x5336BC4 |

No ASCII/UTF-8 string literals referenced in lines 1601-2000.

## Callees in Order (lines 1601-2000)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0x5340B30 | Draw record handler | 0x533652D, 0x533651F (earlier), 0x533673F (earlier) |
| 0x533F580 | **Handle lookup (draw record +0x63 write)** | 0x53365E8 |
| 0x792C3E0 | Helper | 0x5336594 |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5336586, 0x533692F, 0x533693A, 0x5336872, 0x533696B, 0x5336B1C, 0x5336B30 |
| 0x53D92F0 | Helper (alloc?) | 0x53367A6, 0x533647A (earlier) |
| 0x53D96D0 | Helper | 0x53367C6, 0x5336496 (earlier) |
| 0x533F160 | Helper | 0x533690B |
| 0x533F8D0 | Helper | 0x5336AC6 |
| 0xEEC6DE0 | Buffer copy/move | 0x53369C2, 0x53369ED |
| 0xE935700 | Deque push/grow | 0x5336A2D |
| 0x9BC830 | Allocator helper | 0x5336B1C, 0x5336B30 |
| 0x53C5CE0 | Helper | 0x5336C2B |

## Field Table: [reg+off] Reads/Writes (lines 1601-2000)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [r8+8] | 1 | R | 0x533653F, 0x5336544, 0x5336604 | Flag byte (test 8, test 1) |
| [rax+0x68] | 8 | R | 0x5336556 | Ptr |
| [rax+0x25E] | 1 | R | 0x533655F, 0x53365D8 | **Depth byte (source for +0x63 write)** |
| [rax+0x128] | 8 | R | 0x533656E | Nested ptr |
| [rcx+0x480] | 8 | R | 0x5336575 | Ptr |
| [rax+0xC8] | 8 | R | 0x533657F | Vtable func |
| [r8+0x10] | 8 | R | 0x53365A1 | Ptr |
| [rax+0x1C] | 4 | R | 0x53365B1 | Int (sar 4) |
| [rax+0x14] | 8 | R | 0x53365B7 | Float pair (movq) |
| [rbp+0x190] | 8 | W | 0x53365C1, 0x5336745, 0x5336904 | Key for hash/lookup |
| [rbp+0x198] | 4 | W | 0x53365C9 | Int for hash/lookup |
| [r8+0x20] | 8 | R | 0x53365CF | Ptr |
| [rax+0x25E] | 1 | R | 0x53365D8 | Depth byte (bl) |
| **[rax+0x63]** | **1** | **W** | **0x53365FA** | **DEPTH BYTE WRITE via 0x533F580 return** |
| [rsi+0x520] | 8 | R | 0x533660F | Ptr check |
| [rbp+0x200..0x20B] | 12×1 | R | 0x533661D-0x53366F9 | Hash key bytes (12 bytes) |
| [rsi+0x540] | 8 | R | 0x5336717 | Hash mask |
| [rsi+0x518] | 8 | R | 0x533671E | Bucket array base |
| [rsi+0x528] | 8 | R | 0x5336725 | Bucket array end |
| [r8+rdx] | 8 | R | 0x5336730, 0x533673A | Bucket entry |
| [r8+rdx+8] | 8 | R | 0x5336730 | Bucket entry next |
| [rcx+0x10] | 4 | R | 0x5336753, 0x5336764 | Key compare |
| [rcx+0x14] | 4 | R | 0x533676A | Key compare |
| [rcx+0x18] | 4 | R | 0x5336770 | Key compare |
| [rcx+8] | 8 | R | 0x5336760 | Next in chain |
| [rsi+0x420] | 8 | R/W | 0x533677F/0x5336799 | Array current |
| [rsi+0x428] | 8 | R | 0x5336786 | Array end |
| [rcx] | 8 | W | 0x5336796 | Store draw record ptr |
| [rsi+0x420] | 8 | W | 0x5336799 | Inc by 8 |
| [rbp+0x248] | 8 | W | 0x53367D1 | Array current copy |
| [rsi+0x418] | 8 | R | 0x53367DB, 0x53369E0 | Array base |
| [rbp+0x1F0] | 8 | W | 0x5336809 | New capacity |
| [rsi+0x418] | 8 | W | 0x5336A39 | New base |
| [rsi+0x420] | 8 | W | 0x5336A47 | New current |
| [rsi+0x428] | 8 | W | 0x5336A52 | New end |
| [rbp+0x170] | 4 | R/W | 0x5336A5D/0x5336A64/0x5336A66 | Counter |
| [rbp+0x178] | 4 | R/W | 0x5336A6D/0x5336A7C/0x5336A81 | Float accumulator |
| [rax+0xC] | 4 | R | 0x5336A7C | Float addend |
| [rbp+0x1E0] | 1 | R | 0x5336A90, 0x5335F92 | Byte (sil) |
| [rbp+0x238] | 8 | R | 0x5336985, 0x5336735 (earlier) | Draw record ptr |
| [rcx+r14] | 8 | W | 0x533698C | Store in grown array |
| [rbp+0x1D0] | 8 | W | 0x53369A8 | Copy of rcx |
| [rbp+0x1E8] | 8 | W | 0x53369B8 | Computed ptr |
| [r14+0x448] | 8 | R/W | 0x5336B3B/0x5336B4B | Sync ptr |
| [r14+0x450] | 8 | R/W | 0x5336B42/0x5336B4B | Sync ptr |
| [r14+0x460] | 8 | R/W | 0x5336B45/0x5336B52 | Sync ptr |
| [r14+0x468] | 8 | R/W | 0x5336B59/0x5336B62 | Sync ptr |
| [r14+0x488] | 8 | R | 0x5336B69, 0x5336BD0 | Check zero |
| [rbp+0x238] | 8 | W | 0x5336B77 | Ptr [r14+0x4F8] |
| [rbp+0x1D0] | 8 | W | 0x5336B8C | Ptr [r14+0x4B8] |
| [rbp+0xF0] | 8 | W | 0x5336B9A | Ptr [r14+0x510] |
| [r14+0x480] | 8 | R | 0x5336BD5 | Ptr |
| [r14+0x500] | 8 | R/W | 0x5336BEC/0x5336BF8/0x5336C13 | Buffer ptr |
| [r14+0x508] | 8 | R | 0x5336BEF | Buffer end |
| [rax] | 8 | R | 0x5336BF0, 0x5336C46 | Source ptr |
| [r8+0x10] | 4 | R | 0x5336BFC | Element field |
| [rdx] | 4 | W | 0x5336BFE | Dest field |
| [r8+0x14] | 4 | R | 0x5336C02 | Element field |
| [rdx+4] | 4 | W | 0x5336C05 | Dest field |
| [r8+0x18] | 4 | R | 0x5336C09 | Element field |
| [rdx+8] | 4 | W | 0x5336C0C | Dest field |
| [r14+0x500] | 8 | W | 0x5336C17 | Inc by 0xC |
| [rbp+0x238] | 8 | R | 0x5336C24 | Draw record ptr |
| [rax] | 8 | R | 0x5336C3F, 0x5336C46 | Compare |
| [r14+0x4C0] | 8 | R | 0x5336C4B | Ptr |
| [r14+0x10] | 1 | R | 0x5336C52 | Byte flag (cmp 1) |
| [rcx] | 8 | R | 0x5336C5D | Ptr |
| [rbp+0x248] | 8 | W | 0x5336C67 | Store rax |
| [r14+0x130] | 8 | R | 0x5336C70 | Source ptr |
| [r14+0x138] | 8 | R | 0x5336C77 | Source ptr |

---

## Phase Table (0x5336C84..0x533734D - lines 2001-2400)

| Range | Description |
|-------|-------------|
| 0x5336C84..0x5336CC7 | Setup: movaps xmm11/xmm7, store rcx at [rbp+0x180], jmp to 0x53375F8, compare r9/rcx, load [r14+0x500], compare with [r14+0x4F8] |
| 0x5336CC7..0x5336E2F | Pop from stack: lea r8=[rcx-0xC], load 3 dwords to [rbp+0x190/0x194/0x198], FNV-1a hash over 12 bytes, compute bucket, walk hash table at [r14+0x4E8/0x4C0/0x4D0], compare keys at [r9+0x10/0x14/0x18], jump to 0x5336C98 on match |
| 0x5336E2F..0x5336ECD | Match found: and r8 with [rdi+0x4A8], load [rdi+0x480/0x490], shl r8/4, walk linked list at [r9+r8], compare keys at [rcx+0x10/0x14/0x18], jump to 0x5337567 on match |
| 0x5336ECD..0x5336FEF | No match: iterate [rdi+0x130/0x138], call 0x53C5CE0, call 0x533BA90, test result, check [rdi+0x10], hash [rbp+0x190..0x19B] (12 bytes), compute bucket, walk hash table at [rax+0x4E8/0x4C0/0x4D0] |
| 0x5336FEF..0x5337220 | Hash table insert: check [rax+0x4C8] limit, alloc 0x20 bytes via 0x1233E1A8, store key at [r13+0x10/0x18], float math with [rax+0x4B8/0x4F0], call 0xEEC73F0, cvttss2si, bounds check, call 0x3813810, link into hash table at [rdx+rcx], update [r8+0x4C8], link list pointers |
| 0x5337220..0x53372EF | Post-insert: inc [r8+0x4C8], store [r13] at [rsi]/[rsi+8], link list, check [rax+r15] vs [r8+0x4C0], update bucket, load [rdi+0x20], test [rdi+0x254]&1 |
| 0x53372EF..0x533734D | Flag 1 path: paddd xmm0/xmm6, store [rbp+0x200/0x208], write to [rcx+0x500] if space, else call 0x53C5CE0, test [rdi+0x254]&2 |

Key instructions (verbatim, max 6 per phase):
```
0x5336c88  movaps xmm11,xmm7
0x5336c8c  mov [rbp+0x180],rcx
0x5336c93  jmp 0x53375F8
0x5336cc7  lea r8,[rcx-0xC]
0x5336ccb  mov eax,[rcx-0xC]
0x5336ced  movzx ecx,al
```
```
0x5336cfa  xor rcx,r11
0x5336d07  imul rcx,rdi
0x5336d32  mov r15d,0x9E3779B9
0x5336d38  add r8,r15
0x5336d82  xor rcx,r8
0x5336ddb  and r10,r8
```
```
0x5336e2f  mov rdi,[rbp+0x250]
0x5336e36  and r8,[rdi+0x4A8]
0x5336e44  mov r9,[rdi+0x490]
0x5336e4f  mov rsi,[r9+r8+8]
0x5336e60  cmp eax,[rcx+0x10]
0x5336e79  cmp edx,[rcx+0x14]
```
```
0x5336ecd  mov rcx,[r12]
0x5336ed1  lea rdx,[rbp+0x190]
0x5336ed8  call 0x533BA90
0x5336ede  mov rdi,rax
0x5336ef4  mov r9,0xCBF29CE484222325
0x5336efe  xor rax,r9
```
```
0x5336fef  mov rax,[rbp+0x250]
0x5336fef  mov rcx,[rax+0x4E8]
0x5337072  cmp [rax+0x4C8],rcx
0x533708d  mov edx,0x20
0x5337092  call qword ptr [0xF99FFA0]
0x53370a5  mov rax,[rbp+0x190]
0x53370f8  mov rbx,[rax+0x4F0]
```
```
0x5337220  mov rcx,[rsi+8]
0x5337232  mov [r13],rsi
0x533723a  mov [rcx],r13
0x533723d  mov [rsi+8],r13
0x533724f  shl r15,4
0x5337257  cmp rdx,[r8+0x4C0]
```
```
0x5337294  mov eax,[rbp+0x190]
0x53372a0  movq xmm0,[rbp+0x190]
0x53372a8  paddd xmm0,xmm6
0x53372d1  mov [rdx],eax
0x53372d9  mov [rdx+4],eax
0x53372ef  mov rcx,[rbp+0x238]
```

## Strings Referenced (lines 2001-2400)

| RVA | Text | Site |
|-----|------|------|
| None | No string literals in this range | - |

## Callees in Order (lines 2001-2400)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0x53C5CE0 | Helper | 0x5336EAA (earlier), 0x5336EB2, 0x53372FD |
| 0x533BA90 | Hash/compare helper | 0x5336ED8 |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5337092 |
| 0xEEC73F0 | Float helper (sqrt?) | 0x5337136 |
| 0x3813810 | Helper (alloc/link) | 0x5337197 |
| 0x53D92F0 | Helper (alloc?) | (earlier) |
| 0x53D96D0 | Helper | (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 2001-2400)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rbp+0x180] | 8 | W | 0x5336C8C | rcx save |
| [r14+0x500] | 8 | R/W | 0x5336CB7/0x5336CE6 | Stack ptr (pop) |
| [r14+0x4F8] | 8 | R | 0x5336CBE | Stack base |
| [rbp+0x190] | 4 | W | 0x5336CCB, 0x53370A5 | Popped dword 0 / key |
| [rbp+0x194] | 4 | W | 0x5336CD4 | Popped dword 1 |
| [rbp+0x198] | 4 | W | 0x5336CDD | Popped dword 2 |
| [rbp+0x190..0x19B] | 12×1 | R | 0x5336CEC-0x5336FC7 | Hash key bytes (12) |
| [r14+0x4E8] | 8 | R | 0x5336DD4, 0x5336FF6 | Hash mask |
| [r14+0x4C0] | 8 | R | 0x5336DD9, 0x5336FFA, 0x53371AA | Bucket array base |
| [r14+0x4D0] | 8 | R | 0x5336DE6, 0x5337000 | Bucket array end |
| [r11+r10] | 8 | R | 0x5336DF0 | Bucket head |
| [r11+r10+8] | 8 | R | 0x5336DF5 | Bucket next |
| [r9+0x10] | 4 | R | 0x5336DF2, 0x5336E17, 0x5336E60, 0x5336E74 | Key compare |
| [r9+0x14] | 4 | R | 0x5336E1E, 0x5336E7C | Key compare |
| [r9+0x18] | 4 | R | 0x5336E24, 0x5336E81 | Key compare |
| [r9+8] | 8 | R | 0x5336E10, 0x5336E70 | Next in chain |
| [rdi+0x4A8] | 8 | R | 0x5336E36 | Hash mask |
| [rdi+0x480] | 8 | R | 0x5336E3D | Bucket array base |
| [rdi+0x490] | 8 | R | 0x5336E44 | Bucket array end |
| [r9+r8] | 8 | R | 0x5336E4F, 0x5336E59 | Bucket entry |
| [r9+r8+8] | 8 | R | 0x5336E4F | Bucket next |
| [rcx+0x10] | 4 | R | 0x5336E60, 0x5336E74, 0x533701F, 0x5337044, 0x53371E1, 0x53371F4 | Key compare |
| [rcx+0x14] | 4 | R | 0x5336E7C, 0x533704D, 0x53371FD | Key compare |
| [rcx+0x18] | 4 | R | 0x5336E81, 0x5337053, 0x53371FF | Key compare |
| [rcx+8] | 8 | R | 0x5336E70, 0x53371F0 | Next in chain |
| [rdi+0x130] | 8 | R | 0x5336E8C, 0x5336E9A | Source ptr |
| [rdi+0x138] | 8 | R | 0x5336E93 | Source ptr |
| [r12] | 8 | R | 0x5336ED1 | Element ptr |
| [rbp+0x238] | 8 | R | 0x5336EA4, 0x53372EF | Draw record ptr |
| [rbp+0x200] | 8 | R/W | 0x5336EB2, 0x53372A8, 0x53372D1, 0x5337321 | xmm buffer |
| [rdi+0x10] | 8 | R | 0x5336EE6 | Ptr check |
| [rbp+0x250] | 8 | R | 0x5336FEE, 0x5337062, 0x53370E2, 0x53371A4, 0x533722B, 0x53372C1, 0x5337334 | Context ptr |
| [rax+0x4E8] | 8 | R | 0x5336FF6, 0x533700B, 0x53371AA | Hash mask |
| [rax+0x4C0] | 8 | R | 0x5336FFA, 0x5337007, 0x53371AD | Bucket base |
| [rax+0x4D0] | 8 | R | 0x5337000, 0x533700F | Bucket end |
| [rax+0x4C8] | 8 | R | 0x5337072, 0x5337238 | Counter (limit check) |
| [0x1233E1A8] | 8 | R | 0x533707F | Global allocator |
| [r13+0x10] | 8 | W | 0x53370AC | Store key |
| [r13+0x18] | 4 | W | 0x53370B6 | Store key |
| [rax+0x4B8] | 4 | R | 0x53370F0 | Float constant |
| [rax+0x4F0] | 8 | R | 0x53370F8 | Int constant |
| [rbp+0x248] | 8 | W | 0x5337164 | Store r13 |
| [rbp+0x1D0] | 8 | R | 0x533718D | Ptr |
| [rsi+8] | 8 | R | 0x5337220 | Next ptr |
| [r8+0x4C8] | 8 | W | 0x5337238 | Inc counter |
| [r13] | 8 | W | 0x5337232, 0x533723A, 0x533726E, 0x5337277 | List links |
| [r13+8] | 8 | W | 0x5337236 | List links |
| [rcx] | 8 | W | 0x533723A, 0x533723D | List links |
| [rsi+8] | 8 | W | 0x5337241 | List links |
| [rax+r15] | 8 | R | 0x5337246, 0x5337265 | Bucket entry |
| [r8+0x4C0] | 8 | R | 0x5337247, 0x533725E | Bucket base |
| [rax+r15+8] | 8 | R | 0x5337252 | Bucket next |
| [rax+r15] | 8 | W | 0x533726E, 0x5337272, 0x5337279 | Bucket update |
| [rax+r15+8] | 8 | W | 0x5337272 | Bucket update |
| [rdi+0x20] | 8 | R | 0x533727D | Next ptr |
| [rdi+0x254] | 1 | R | 0x5337290, 0x5337309 | Flag byte (test 1, test 2) |
| [rbp+0x190] | 4 | R | 0x5337294, 0x533730D | Key dword |
| [rbp+0x198] | 4 | R | 0x533729A, 0x5337319 | Key dword |
| [rbp+0x190] | 8 | R | 0x53372A0, 0x5337313 | Key qword (movq) |
| [rbp+0x200] | 8 | W | 0x53372AC, 0x5337321 | paddd result |
| [rbp+0x208] | 4 | W | 0x53372B4, 0x533732E | paddd result |
| [rcx+0x500] | 8 | R/W | 0x53372C1/0x53372D1/0x533733B/0x533734B | Buffer ptr |
| [rcx+0x508] | 8 | R | 0x53372C8, 0x5337342 | Buffer end |
| [rdx] | 4 | W | 0x53372D1, 0x533734B | Store key |
| [rdx+4] | 4 | W | 0x53372D9, 0x5337353 | Store key |
| [rdx+8] | 4 | W | 0x53372E2, 0x533735C | Store key |
| [rcx+0x500] | 8 | W | 0x53372E5, 0x533735F | Inc by 0xC |

---

## Phase Table (0x533734D..0x5337A80 - lines 2401-2800)

| Range | Description |
|-------|-------------|
| 0x533734D..0x53373F8 | Flag 2 path: test [rdi+0x254]&4, dec ecx, write [rbp+0x190/0x198/0x200/0x208] to [rcx+0x500], call 0x53C5CE0 if full |
| 0x53373F8..0x533746D | Flag 3 path: test [rdi+0x254]&8, inc ecx, write to [rcx+0x500], call 0x53C5CE0 if full |
| 0x533746D..0x53374E3 | Flag 4 path: test [rdi+0x254]&0x10, paddd xmm0/xmm14, movd [rdx], write to [rcx+0x500], call 0x53C5CE0 if full |
| 0x53374E3..0x5337552 | Flag 5 path: test [rdi+0x254]&0x20, paddd xmm0/xmm15, movd [rdx], write to [rcx+0x500], jmp to 0x5336EA4 if full, inc r12 by 0x10, loop to 0x5336ECD/0x5336CB0 |
| 0x5337552..0x53375D0 | Alloc fail path: call 0x9BC830, jmp to 0x53370A5, hash table unlink: cmp rcx/r10/rsi/r11, mov [r9+r8], dec [rdi+0x488], relink list, call 0xE935700, jmp to 0x5336E8C |
| 0x53375D0..0x5337840 | Element iteration: test [rcx+8]&8, load [rbp+0x248], compare with [rbp+0x180], load [r14+0x130/0x138], iterate r15 by 0x10, load [rax+0x5E8], check [rdx+0xEC], bounds check with [rdx+0xC8/0xD4/0xCC/0xD8/0xD0/0xDC], float math with xmm11/xmm12/xmm13, ucomiss, load [rdx+0xF8/0x100], index, lock inc/dec refcounts |
| 0x5337840..0x533790D | Alt element path: test [rax+8]&2, inc [rbp+0x230] up to 6, bt [rax+0x254], load [r15], compute coords from 0xF167AB4 table, xorps/cvtsi2ss/punpckldq/cvtdq2ps |
| 0x533790D..0x5337A80 | Another element loop: iterate r15, load [rax+0x5E8], bounds check with [rdx+0xC8/0xD4/0xCC/0xD8/0xD0/0xDC], float math with xmm7/xmm11/xmm12/xmm13, ucomiss, load [rdx+0xF8/0x100], index, lock inc/dec refcounts, check [rsi+0x10]/[rax+0x28] |

Key instructions (verbatim, max 6 per phase):
```
0x533734d  mov eax,[rbp+0x204]
0x5337353  mov [rdx+4],eax
0x5337356  mov eax,[rbp+0x208]
0x533735c  mov [rdx+8],eax
0x533735f  add qword ptr [rcx+0x500],0xC
0x5337369  mov rcx,[rbp+0x238]
```
```
0x5337387  mov eax,[rbp+0x190]
0x5337393  dec ecx
0x5337395  mov rdx,[rbp+0x190]
0x533739c  mov [rbp+0x200],rdx
0x53373b0  mov rdx,[rcx+0x500]
0x53373c0  mov [rdx],eax
0x53373de  mov rcx,[rbp+0x238]
```
```
0x53373fc  mov eax,[rbp+0x190]
0x5337408  inc ecx
0x5337411  mov [rbp+0x200],rdx
0x5337418  mov [rbp+0x208],ecx
0x533741e  mov rcx,[rbp+0x250]
0x5337453  mov rcx,[rbp+0x238]
```
```
0x5337471  mov eax,[rbp+0x198]
0x5337477  movq xmm0,[rbp+0x190]
0x533747f  paddd xmm0,xmm14
0x5337484  movq [rbp+0x200],xmm0
0x5337499  mov rdx,[rcx+0x500]
0x53374c9  mov rcx,[rbp+0x238]
```
```
0x53374eb  mov eax,[rbp+0x198]
0x53374f1  movq xmm0,[rbp+0x190]
0x53374f9  paddd xmm0,xmm15
0x5337506  mov [rbp+0x208],eax
0x533750c  mov rcx,[rbp+0x250]
0x5337527  movd [rdx],xmm0
```
```
0x5337557  mov ecx,0x20
0x533755c  call 0x9BC830
0x5337567  cmp rcx,r10
0x5337575  cmp r11,rcx
0x533757a  mov rax,[rcx]
0x533759f  dec qword ptr [rdi+0x488]
0x53375b5  mov edx,0x20
0x53375ba  call 0xE935700
```
```
0x53375c4  test byte ptr [rcx+8],8
0x53375d0  mov rax,[rbp+0x248]
0x53375e1  mov [rbp+0x248],rax
0x53375f8  mov r15,[r14+0x130]
0x533762d  mov rax,[r15]
0x5337637  mov eax,[rdx+0xEC]
0x5337648  mov r11d,[rcx+0x10]
```
```
0x533782b  mov rax,[rbp+0x188]
0x5337840  mov rcx,[rbp+0x230]
0x5337847  inc rcx
0x533786f  bt eax,ecx
0x533788e  mov rax,[rbp+0x230]
0x5337895  lea rax,[rax+rax*2]
0x53378ab  add r8d,[rcx+rax*4+8]
```
```
0x533790d  mov rax,[r15]
0x5337917  mov eax,[rdx+0xEC]
0x5337921  mov r11d,[rdx+0xC8]
0x533792e  jl short 0x5337900
0x533797d  add ebx,r12d
0x53379e9  mov r10,[rdx+0xF8]
```

## Strings Referenced (lines 2401-2800)

| RVA | Text | Site |
|-----|------|------|
| 0xF167AB4 | (lookup table, not string) | 0x53378AA, 0x53378AE, 0x53378B2 |
| 0xF0B8800 | (constant, not string) | 0x5337713, 0x53379A9 |

No ASCII/UTF-8 string literals referenced in lines 2401-2800.

## Callees in Order (lines 2401-2800)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0x53C5CE0 | Helper | 0x5337370, 0x53373E5, 0x533745A, 0x53374D0, 0x53372FD (earlier), 0x5336EAA (earlier), 0x5336EB2 (earlier) |
| 0x9BC830 | Allocator helper | 0x533755C |
| 0xE935700 | Deque push/grow | 0x53375BA |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5337792, 0x53377B9, 0x53377D3, 0x5337A24, 0x5337A4B, 0x5337A65 |
| 0x533BA90 | Hash/compare helper | (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 2401-2800)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rdi+0x254] | 1 | R | 0x5337309, 0x5337383, 0x53373F8, 0x533746D, 0x53374E3 | Flag byte (test 1,2,4,8,0x10,0x20) |
| [rbp+0x190] | 4 | R | 0x5337387, 0x53373FC, 0x533739C, 0x5337411, 0x5337471, 0x5337294 (earlier) | Key dword |
| [rbp+0x198] | 4 | R/W | 0x5337393, 0x53373A3, 0x5337408, 0x5337418, 0x5337477, 0x533729A (earlier) | Key dword |
| [rbp+0x200] | 8 | R/W | 0x533739C, 0x53373A3, 0x5337411, 0x5337418, 0x533747F, 0x533748C, 0x53372A0 (earlier) | Key qword / paddd result |
| [rbp+0x204] | 4 | R | 0x5337353, 0x53373C2, 0x5337437, 0x53374AD, 0x53372D9 (earlier) | Key dword |
| [rbp+0x208] | 4 | R/W | 0x5337356, 0x53373CB, 0x53373D1, 0x5337440, 0x53374B6, 0x53374BC, 0x53372B4 (earlier) | Key dword |
| [rcx+0x500] | 8 | R/W | 0x53373B0, 0x53373C0, 0x53373D4, 0x5337425, 0x5337435, 0x5337449, 0x53374BF, 0x5337513, 0x5337527, 0x533753D | Buffer ptr (inc by 0xC) |
| [rcx+0x508] | 8 | R | 0x53373B7, 0x53373BE, 0x533742C, 0x5337433, 0x53374A0, 0x53374A7, 0x533751A, 0x5337521 | Buffer end |
| [rdx] | 4 | W | 0x53373C0, 0x53373D1, 0x5337435, 0x5337446, 0x53374A9, 0x5337527 | Store key |
| [rdx+4] | 4 | W | 0x53373C8, 0x53373CB, 0x533743D, 0x53374B3, 0x53374AD, 0x5337531 | Store key |
| [rdx+8] | 4 | W | 0x53373D1, 0x53373CB, 0x5337440, 0x53374BC, 0x53374BF, 0x5337534 | Store key |
| [rcx+0x500] | 8 | W | 0x53373DC, 0x53373E5, 0x5337449, 0x5337451, 0x53374C7, 0x53374DC, 0x533751D, 0x5337540 | Inc by 0xC |
| [rbp+0x238] | 8 | R | 0x5337369, 0x53373DE, 0x5337453, 0x53374C9, 0x53372EF (earlier) | Draw record ptr |
| [rdi+0x488] | 8 | W | 0x533759F | Dec counter |
| [r9+r8] | 8 | W | 0x533757A, 0x533758C, 0x5337593, 0x5337597 | List unlink |
| [r9+r8+8] | 8 | W | 0x5337581, 0x533758C, 0x5337597 | List unlink |
| [rcx] | 8 | R | 0x533757A, 0x5337588, 0x53375A6 | List entry |
| [rcx+8] | 8 | R | 0x53375A6, 0x53375AD | List next |
| [rdx] | 8 | W | 0x53375AA, 0x53375AD | List relink |
| [rax+8] | 8 | W | 0x53375AD, 0x53375B1 | List relink |
| [rdi+0x488] | 8 | W | 0x533759F | Dec counter |
| [rcx+8] | 1 | R | 0x53375C4 | Flag byte (test 8) |
| [rbp+0x248] | 8 | R/W | 0x53375D0/0x53375E1/0x53375D7 (earlier) | Ptr |
| [rbp+0x180] | 8 | R | 0x53375E8, 0x5336C8C (earlier) | Compare ptr |
| [r14+0x130] | 8 | R | 0x53375F8, 0x5336011 (earlier) | Source ptr |
| [r14+0x138] | 8 | R | 0x5337606, 0x5336018 (earlier) | Source ptr |
| [rbp+0x1F0] | 8 | W | 0x533760D, 0x533602D (earlier) | End ptr |
| [r15] | 8 | R/W | 0x5337614/0x5337620/0x5337900/0x5337904 | Iteration ptr |
| [rax] | 8 | R | 0x5337614, 0x533762D, 0x53378E7, 0x533790D | Element ptr |
| [rax+0x5E8] | 8 | R | 0x5337630, 0x5337910, 0x53362C4 (earlier) | Nested ptr |
| [rdx+0xEC] | 4 | R | 0x5337637, 0x5337917, 0x53362CB (earlier) | Int check |
| [rbp+0x248] | 8 | R | 0x5337641, 0x53375D0 | Ptr |
| [rcx+0x10] | 4 | R | 0x5337648, 0x5336E60 (earlier) | Int |
| [rdx+0xC8] | 4 | R | 0x5337651, 0x5337921, 0x53362E5 (earlier) | Int |
| [rdx+0xD4] | 4 | R | 0x5337659, 0x5337937, 0x53362EC (earlier) | Int |
| [rdx+0xCC] | 4 | R | 0x5337669, 0x5337943, 0x533630C (earlier) | Int |
| [rdx+0xD8] | 4 | R | 0x5337673, 0x5337955, 0x533631B (earlier) | Int |
| [rdx+0xD0] | 4 | R | 0x5337679, 0x5337963, 0x5336339 (earlier) | Int |
| [rdx+0xDC] | 4 | R | 0x5337683, 0x5337975, 0x533634C (earlier) | Int |
| [rdx+0xE0] | 4 | R | 0x5337699, 0x5337995, 0x53363A2 (earlier) | Int |
| [rbp+0x230] | 4 | R/W | 0x53376A2/0x5337847/0x5337868 | Counter/loop |
| [rbp+0x1F0] | 4 | R | 0x5337670, 0x533794A | Int |
| [rbp+0x1E8] | 4 | R/W | 0x53376D8/0x533796A/0x533796D | Int |
| [rdx+0xF8] | 8 | R | 0x5337753, 0x53379E9, 0x53363EF (earlier) | Ptr |
| [rdx+0x100] | 8 | R | 0x533775A, 0x53379F0, 0x53363F6 (earlier) | Ptr |
| [rcx+8] | 4 | W | 0x5337792, 0x5337A24 | Refcount++ |
| [rax] | 8 | R | 0x5337796, 0x5337A28 | Ptr |
| [rax+8] | 8 | R | 0x5337799, 0x5337A2B | Ptr |
| [rdi+8] | 4 | W | 0x53377A6, 0x5337A38 | Refcount-- |
| [rdi] | 8 | R | 0x53377B0, 0x5337A42 | Vtable |
| [rdi+0xC] | 4 | W | 0x53377BF, 0x5337A51 | Weak refcount-- |
| [rax+8] | 1 | R | 0x533782B, 0x53361D8 (earlier) | Flag byte (test 2) |
| [rbp+0x230] | 8 | R/W | 0x5337840/0x5337847/0x5337868 | Loop counter |
| [rax+0x254] | 1 | R | 0x5337868, 0x5337290 (earlier) | Flag byte (bt) |
| [rbp+0x250] | 8 | R | 0x5337874, 0x5336FEE (earlier) | Context ptr |
| [rax+0x130] | 8 | R | 0x533787B, 0x5336011 (earlier) | Source ptr |
| [rax+0x138] | 8 | R | 0x5337882, 0x5336018 (earlier) | Source ptr |
| [0xF167AB4] | 4 | R | 0x53378AA, 0x53378AE, 0x53378B2 | Lookup table (coord offsets) |
| [rbp+0x1E8] | 4 | W | 0x53378CC | Int |
| [rbp+0x1E0] | 8 | R | 0x533787B, 0x5337A79 | Ptr |
| [rbp+0x188] | 8 | W | 0x53377E5, 0x533782B | Ptr |
| [rbp+0x1E0] | 8 | R | 0x5337A79 | Ptr |
| [rbp+0x230] | 8 | R | 0x5337A80 | Counter |

---

## Phase Table (0x5337A80..0x5338178 - lines 2801-3200)

| Range | Description |
|-------|-------------|
| 0x5337A80..0x5337B88 | Validation checks: load byte [rcx+rdx+0x258], compare with [rsi+0xA], check [rax], load [rax+0x28], test -1, load [rbp+0x250]->[0x128]->[0x390], test [rcx+0x28]&0x20, cmovne, compare, load [rcx+8]+0x3C, check [rax] byte==1, check [rax+4], load [rbp+0x188]+9, check al, cmp al==1, check [rax+0x10], check [rax+4]==1, check [rax+0x28], test [rax+0x28]&2, compare [rax] vs [rcx+0x20], load [rax+0x25E], compare with [rcx+0xA] |
| 0x5337B88..0x5337C00 | Sync: load [r14+0x4C0], mov [rbp+0x180/0x248], compare, movaps xmm7/xmm11, xmm10/xmm12, jmp to 0x5337EE6/0x53382B0 |
| 0x5337C00..0x5337EC1 | Element iteration: load [rbp+0x248], [rax], compare with [rbp+0x180], load [r14+0x130/0x138], iterate r15 by 0x10, load [rax+0x5E8], check [rdx+0xEC], bounds check with [rdx+0xC8/0xD4/0xCC/0xD8/0xD0/0xDC], float math with xmm7/xmm10/xmm11/xmm12/xmm13, ucomiss, load [rdx+0xF8/0x100], index, lock inc/dec refcounts, call 0x792C3E0, call 0x533F580, **write [rax+0x63]=bl** |
| 0x5337EC1..0x5337F2D | Next element: movaps xmm7/xmm11, load [rbp+0x248], compare, load [r14+0x130/0x138], iterate r15, bounds check, float math with xmm7/xmm10, ucomiss, lock inc/dec refcounts |
| 0x5337F2D..0x5338178 | Another element loop: similar bounds checks, float math, ucomiss, lock inc/dec refcounts, check [rsi+0x10], [rax+4]==1, [rax+0x28], test [rcx] -1, test [rcx+0x28]&0x20, cmovne, compare with [rdx+0x390], check [rax] byte, check [rsi+9]==1, check [rax+0x10], [rax+4]==1, [rax+0x28], test [rax+0x28]&2 |

Key instructions (verbatim, max 6 per phase):
```
0x5337a87  movzx ecx,byte ptr [rcx+rdx+0x258]
0x5337a8f  cmp [rsi+0xA],cl
0x5337aa3  mov rcx,[rax+0x28]
0x5337ab5  mov rdx,[rbp+0x250]
0x5337aca  test byte ptr [rcx+0x28],0x20
0x5337ae8  cmp byte ptr [rax],1
```
```
0x5337b88  mov r14,[rbp+0x250]
0x5337b8f  mov rax,[r14+0x4C0]
0x5337b96  mov rcx,[rax]
0x5337baa  movaps xmm7,xmm11
0x5337bae  movaps xmm10,xmm12
0x5337bb8  jmp 0x53382B0
```
```
0x5337c00  mov rax,[rbp+0x248]
0x5337c07  mov rax,[rax]
0x5337c28  mov r15,[r14+0x130]
0x5337c60  mov rdx,[rax+0x5E8]
0x5337c67  mov eax,[rdx+0xEC]
0x5337d82  mov r10,[rdx+0xF8]
```
```
0x5337eb9  movaps xmm7,xmm11
0x5337ec1  mov rax,[rbp+0x248]
0x5337ec8  mov rax,[rax]
0x5337ee6  mov r15,[r14+0x130]
0x5337f2d  mov rax,[r15]
0x5337f37  mov eax,[rdx+0xEC]
```
```
0x53380db  mov rax,[rsi+0x10]
0x53380e8  mov ecx,[rax+4]
0x53380eb  cmp ecx,1
0x53380f4  mov rcx,[rax+0x28]
0x5338106  mov rdx,[rbp+0x250]
0x533811b  test byte ptr [rcx+0x28],0x20
```

## Strings Referenced (lines 2801-3200)

| RVA | Text | Site |
|-----|------|------|
| None | No string literals in this range | - |

## Callees in Order (lines 2801-3200)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5337E46, 0x5337DC8, 0x5337DE8, 0x5337E02, 0x53380B6, 0x53380CD, 0x53380D0 |
| 0x792C3E0 | Helper | 0x5337E50, 0x5336594 (earlier) |
| 0x533F580 | **Handle lookup (draw record +0x63 write)** | 0x5337EA2, 0x53365E8 (earlier) |
| 0x53C5CE0 | Helper | (earlier) |
| 0x9BC830 | Allocator helper | (earlier) |
| 0xE935700 | Deque push/grow | (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 2801-3200)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rcx+rdx+0x258] | 1 | R | 0x5337A87 | Byte compare |
| [rsi+0xA] | 1 | R | 0x5337A8F | Byte compare |
| [rax] | 1 | R | 0x5337A94, 0x5337AE8, 0x5337AEB, 0x5338139, 0x533813C | Byte check |
| [rax+0x28] | 8 | R | 0x5337AA3, 0x53380F4 | Ptr |
| [rcx] | 8 | R | 0x5337AAF, 0x53380FD | Ptr (cmp -1) |
| [rbp+0x250] | 8 | R | 0x5337AB5, 0x5338106, 0x53375F8 (earlier) | Context ptr |
| [rdx+0x128] | 8 | R | 0x5337ABC, 0x533810D | Nested ptr |
| [rdx+0x390] | 8 | R | 0x5337AC3, 0x5338114 | Nested ptr |
| [rcx+0x28] | 1 | R | 0x5337ACA, 0x533811B | Flag byte (test 0x20) |
| [r8+0x14] | 8 | R | 0x5337AD2, 0x533811F | Ptr (cmovne) |
| [rcx+8] | 8 | R | 0x5337ADB, 0x533812C | Ptr |
| [rcx+0x3C] | 8 | R | 0x5337AE3, 0x5338130 | Ptr (+0x3C) |
| [rax+4] | 4 | R | 0x5337AF1, 0x5338157 | Int check |
| [rbp+0x188] | 8 | R | 0x5337AFC, 0x5337B03, 0x5337B1E, 0x5337B3E, 0x5337B45, 0x5337B60 | Ptr |
| [rax+9] | 1 | R | 0x5337B03, 0x5337B12, 0x533813E | Byte (cmp 1) |
| [rax+0x10] | 8 | R | 0x5337B25, 0x5337B45, 0x533814A | Ptr |
| [rax+4] | 4 | R | 0x5337B32, 0x533815A | Int (cmp 1) |
| [rax+0x28] | 8 | R | 0x5337B49, 0x5338163 | Ptr |
| [rax+0x28] | 1 | R | 0x5337B56, 0x5338174 | Flag byte (test 2) |
| [rcx+0x20] | 8 | R | 0x5337B60, 0x5337B54 (earlier) | Ptr compare |
| [rax+0x25E] | 1 | R | 0x5337B71, 0x5337E8E | **Depth byte (source for +0x63)** |
| [rcx+0xA] | 1 | R | 0x5337B7F, 0x5337B82 | Byte compare |
| [r14+0x4C0] | 8 | R | 0x5337B8F, 0x5337BD0, 0x5337C4B (earlier) | Ptr |
| [rax] | 8 | R | 0x5337B96, 0x5337BD4, 0x5337C07, 0x53380DB | Ptr |
| [rbp+0x180] | 8 | W | 0x5337B99, 0x5337BFE, 0x5336C8C (earlier) | Ptr |
| [rbp+0x248] | 8 | W | 0x5337BA0, 0x5337BD3, 0x5337C11, 0x5337EC1 | Ptr |
| [rbp+0x1F0] | 8 | W | 0x5337C36, 0x5337EF4, 0x533602D (earlier) | End ptr |
| [r14+0x130] | 8 | R | 0x5337C28, 0x5337EE6, 0x5336011 (earlier) | Source ptr |
| [r14+0x138] | 8 | R | 0x5337C36, 0x5337EF4, 0x5336018 (earlier) | Source ptr |
| [r15] | 8 | R/W | 0x5337C44/0x5337C50/0x5337F20/0x5337F14 | Iteration ptr |
| [rax+0x5E8] | 8 | R | 0x5337C60, 0x5337F30, 0x5337630 (earlier) | Nested ptr |
| [rdx+0xEC] | 4 | R | 0x5337C67, 0x5337F37, 0x5337637 (earlier) | Int check |
| [rbp+0x248] | 8 | R | 0x5337C71, 0x5337F41, 0x5337641 (earlier) | Ptr |
| [rcx+0x10] | 4 | R | 0x5337C78, 0x5337F48, 0x5337648 (earlier) | Int |
| [rdx+0xC8] | 4 | R | 0x5337C82, 0x5337F52, 0x5337651 (earlier) | Int |
| [rdx+0xD4] | 4 | R | 0x5337C90, 0x5337F60, 0x5337659 (earlier) | Int |
| [rdx+0xCC] | 4 | R | 0x5337CA7, 0x5337F77, 0x5337669 (earlier) | Int |
| [rdx+0xD8] | 4 | R | 0x5337CB6, 0x5337F85, 0x5337673 (earlier) | Int |
| [rdx+0xD0] | 4 | R | 0x5337CCC, 0x5337F9B, 0x5337679 (earlier) | Int |
| [rdx+0xDC] | 4 | R | 0x5337CE6, 0x5337FAE, 0x5337683 (earlier) | Int |
| [rdx+0xE0] | 4 | R | 0x5337D35, 0x5338003, 0x5337699 (earlier) | Int |
| [rbp+0x230] | 4 | R/W | 0x5337CD2/0x5337FA1/0x5337847 (earlier) | Counter |
| [r8+0x14] | 4 | R | 0x5337C9C, 0x5337F6C, 0x533766C (earlier) | Int |
| [rdx+0xF8] | 8 | R | 0x5337D82, 0x5338050, 0x5337753 (earlier) | Ptr |
| [rdx+0x100] | 8 | R | 0x5337D89, 0x5338057, 0x533775A (earlier) | Ptr |
| [rcx+8] | 4 | W | 0x5337DC1, 0x533808F | Refcount++ |
| [rax] | 8 | R | 0x5337DC5, 0x5338093 | Ptr |
| [rax+8] | 8 | R | 0x5337DC8, 0x5338096 | Ptr |
| [rbx+8] | 4 | W | 0x5337DD5, 0x53380A3 | Refcount-- |
| [rbx] | 8 | R | 0x5337DDF, 0x53380AD | Vtable |
| [rbx+0xC] | 4 | W | 0x5337DF2, 0x53380BC | Weak refcount-- |
| [rdi+0x10] | 8 | R | 0x5337E00, 0x5337E56 | Ptr |
| [rdi+0x68] | 8 | R | 0x5337E16 | Ptr |
| [rax+0x25E] | 1 | R | 0x5337E1F, 0x5337E8E | **Depth byte (source for +0x63)** |
| [rax+0x128] | 8 | R | 0x5337E2E, 0x5337E35 | Nested ptr |
| [rcx+0x480] | 8 | R | 0x5337E35 | Ptr |
| [rax+0xC8] | 8 | R | 0x5337E3F | Vtable func |
| [rax+0x1C] | 4 | R | 0x5337E63 | Int (sar 4) |
| [rax+0x14] | 8 | R | 0x5337E69 | Float pair (movq) |
| [rbp+0x190] | 8 | W | 0x5337E73 | Key for lookup |
| [rbp+0x198] | 4 | W | 0x5337E7B | Key for lookup |
| [rdi+0x20] | 8 | R | 0x5337E81, 0x533727D (earlier) | Ptr |
| [rax+0x25E] | 1 | R | 0x5337E8E, 0x5337E1F | **Depth byte (bl)** |
| **[rax+0x63]** | **1** | **W** | **0x5337EB1, 0x53365FA (earlier)** | **DEPTH BYTE WRITE via 0x533F580 return** |
| [rsi+0x10] | 8 | R | 0x53380DB | Ptr |
| [rax+4] | 4 | R | 0x53380E8, 0x533815A | Int (cmp 1) |
| [rax+0x28] | 8 | R | 0x53380F4, 0x5338163 | Ptr |
| [rcx] | 8 | R | 0x53380FD, 0x5337AAF | Ptr (cmp -1) |
| [rbp+0x250] | 8 | R | 0x5338106, 0x5337AB5 | Context ptr |
| [rdx+0x128] | 8 | R | 0x533810D, 0x5337ABC | Nested ptr |
| [rdx+0x390] | 8 | R | 0x5338114, 0x5337AC3 | Nested ptr |
| [rcx+0x28] | 1 | R | 0x533811B, 0x5337ACA | Flag byte (test 0x20) |
| [r8+0x14] | 8 | R | 0x533811F, 0x5337AD2 | Ptr (cmovne) |
| [rcx+8] | 8 | R | 0x533812C, 0x5337ADB | Ptr |
| [rcx+0x3C] | 8 | R | 0x5338130, 0x5337AE3 | Ptr (+0x3C) |
| [rsi+9] | 1 | R | 0x533813E | Byte (cmp 1) |

---

## Phase Table (0x5338178..0x533889E - lines 3201-3600)

| Range | Description |
|-------|-------------|
| 0x5338178..0x53381E0 | Final validation: cmp [rax] vs [rsi+0x20], load [rax+0x25E], compare with [rsi+0xA], test [rsi+8]&2, load [r14+0x130/0x138], jmp to 0x53381E0 |
| 0x53381E0..0x53382A4 | Element iteration: cmp rsi/r15, call 0x533F160, check [rbp+0x190], dec refcount on [rbp+0x198], call 0x533F8D0, test [rbp+0x198], dec refcounts, call 0xF99FFA0 |
| 0x53382A4..0x5338370 | Cleanup: load [r14+0x4C0], zero list at [rax+8], walk list call 0xE935700, zero [rax]/[rax+8], zero [r14+0x4C8], check [r14+0x4D0] vs [0x4D8], grow buffer via 0xE935700 or fill with movdqu |
| 0x5338370..0x53386B1 | Element loop: iterate r12 by 0x10, load [rax+0x5E8], bounds check with [rdx+0xC8/0xD4/0xCC/0xD8/0xD0/0xDC], float math with xmm7/xmm10/xmm11/xmm12/xmm13, ucomiss, load [rdx+0xF8/0x100], index, lock inc/dec refcounts, test [rsi+8]&1, call 0x5340B30, load [rax+0x9A8], inc refcount, call vtable [rax+0x58], store at [rsi+0x568], dec refcounts |
| 0x53386B1..0x533889E | Next phase: zero [rbp+0xD0/0xE0], load [r14+0x138/0x130], compute diff, sar 4, overflow check, alloc via 0x1233E1A8 (large/small), copy from [rax] to rbx with lock inc refcount on [rdx+8], call 0x26E9D0, load [r14+0x518], iterate list, copy [rbx+0x10/0x14/0x18] to [rdx], inc [r14+0x558] by 0xC |

Key instructions (verbatim, max 6 per phase):
```
0x533817e  cmp rax,[rsi+0x20]
0x5338184  movzx eax,byte ptr [rax+0x25E]
0x5338190  test byte ptr [rsi+8],2
0x53381a8  mov r15,[rax+0x138]
0x53381e5  mov rcx,[rsi]
0x53381e8  lea rdx,[rbp+0x190]
0x53381ef  mov r8,[rbp+0x1E0]
```
```
0x53382b0  mov rax,[r14+0x4C0]
0x53382b7  mov rcx,[rax]
0x53382d1  cmp qword ptr [r14+0x4C8],0
0x53382df  mov rax,[r14+0x4C0]
0x53382ea  mov qword ptr [rcx],0
0x5338308  call 0xE935700
```
```
0x5338395  mov r12,[r14+0x130]
0x53383dd  mov rax,[r12]
0x53383e1  mov rdx,[rax+0x5E8]
0x533847d  cvtsi2ss xmm0,r15d
0x5338490  add r10d,esi
0x5338542  lock inc dword ptr [rcx+8]
```
```
0x533858e  test byte ptr [rsi+8],1
0x5338598  mov rcx,[rbp+0xF0]
0x53385ad  call 0x5340B30
0x53385d2  mov rcx,[rax+0x9A8]
0x5338609  call qword ptr [0xF99FFA0]
0x5338610  mov [rsi+0x568],eax
```
```
0x53386b1  xorps xmm0,xmm0
0x53386cd  mov rcx,[r14+0x130]
0x53386d4  mov rax,rdi
0x53386d7  sub rax,rcx
0x53386da  sub rdi,rcx
0x53386e3  sar rax,4
0x533870e  mov rdx,r14
```
```
0x53387a0  mov rdx,[rax]
0x53387a3  mov [rbx],rdx
0x53387a6  mov rdx,[rax+8]
0x53387ae  add rbx,0x10
0x53387c7  lock inc dword ptr [rdx+8]
```
```
0x5338810  mov rbx,[rbp+0x248]
0x5338817  mov eax,[rbx+0x10]
0x533881a  mov [rdx],eax
0x533881c  mov eax,[rbx+0x14]
0x533881f  mov [rdx+4],eax
0x5338822  mov eax,[rbx+0x18]
0x5338825  mov [rdx+8],eax
0x5338828  add qword ptr [r14+0x558],0xC
```

## Strings Referenced (lines 3201-3600)

| RVA | Text | Site |
|-----|------|------|
| None | No string literals in this range | - |

## Callees in Order (lines 3201-3600)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0x533F160 | Helper | 0x53381EF, 0x533690B (earlier) |
| 0x533F8D0 | Helper | 0x5338256, 0x5336AC6 (earlier) |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5338220, 0x5338233, 0x5338236, 0x5338308, 0x53385E2, 0x5338609, 0x533861F, 0x533862F, 0x5338649, 0x533870E, 0x5338746, 0x53387C7 |
| 0xE935700 | Deque push/grow | 0x5338308, 0x5338657 (jae), 0x53386A0 (jmp) |
| 0x5340B30 | Draw record handler | 0x53385AD, 0x53364D7 (earlier), 0x533651F (earlier), 0x533652D (earlier), 0x53372D1 (earlier), 0x5337370 (earlier) |
| 0x26E9D0 | Helper | 0x53387E6 |
| 0x53C5CE0 | Helper | 0x533888A, 0x53372FD (earlier), 0x5336EAA (earlier), 0x5336EB2 (earlier), 0x5337370 (earlier), 0x53373E5 (earlier), 0x533745A (earlier), 0x53374D0 (earlier) |
| 0x53D92F0 | Helper (alloc?) | 0x53381B8, 0x533647A (earlier), 0x53367A6 (earlier) |
| 0x53D96D0 | Helper | 0x53381D1, 0x5336496 (earlier), 0x53367C6 (earlier) |
| 0x533BA90 | Hash/compare helper | (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 3201-3600)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rax] | 8 | R | 0x533817E, 0x5338184, 0x53382F4, 0x5338300, 0x53387A0 | Ptr |
| [rsi+0x20] | 8 | R | 0x533817E | Ptr compare |
| [rax+0x25E] | 1 | R | 0x5338184, 0x5337B71 (earlier) | **Depth byte** |
| [rsi+0xA] | 1 | R | 0x533818B, 0x5337B7F (earlier) | Byte compare |
| [rsi+8] | 1 | R | 0x5338190, 0x533858E | Flag byte (test 2, test 1) |
| [r14+0x130] | 8 | R | 0x53381A1, 0x5338395, 0x5337C28 (earlier) | Source ptr |
| [r14+0x138] | 8 | R | 0x53381A8, 0x533839C, 0x5337C36 (earlier) | Source ptr |
| [rsi] | 8 | R | 0x53381E5, 0x53383C3 | Element ptr |
| [rbp+0x190] | 8 | R/W | 0x53381EF, 0x5338241, 0x53385CB, 0x533877F | Key buffer |
| [rbp+0x1E0] | 8 | R | 0x53381F6, 0x53385AD, 0x5338883 | Ptr |
| [rbp+0x198] | 8 | R | 0x5338205, 0x533825C | Ptr |
| [rbx+8] | 4 | W | 0x5338211, 0x5338270 | Refcount-- |
| [rbx] | 8 | R | 0x5338217, 0x5338279 | Vtable |
| [rbx+0xC] | 4 | W | 0x5338226, 0x5338289 | Weak refcount-- |
| [rbp+0x190] | 16 | W | 0x5338241 | Zero (xorps) |
| [rbp+0x250] | 8 | R | 0x5338248, 0x5337AB5 (earlier) | Context ptr |
| [rbp+0x198] | 8 | R | 0x533825C, 0x5338205 | Ptr |
| [rdi+8] | 4 | W | 0x5338270, 0x5338289 | Refcount-- |
| [rdi] | 8 | R | 0x5338279, 0x5338292 | Vtable |
| [rdi+0xC] | 4 | W | 0x5338289 | Weak refcount-- |
| [r14+0x4C0] | 8 | R | 0x53382B0, 0x5337B8F (earlier) | Ptr |
| [rax] | 8 | R | 0x53382B7, 0x53382DF, 0x5338310 | Ptr |
| [rbp+0x180] | 8 | W | 0x53382BA, 0x5337B99 (earlier) | Ptr |
| [rbp+0x248] | 8 | W | 0x53382C1, 0x5337BA0 (earlier) | Ptr |
| [r14+0x4C8] | 8 | R/W | 0x53382D1/0x5338323 | Counter |
| [rax+8] | 8 | R | 0x53382E6 | Ptr |
| [rcx] | 8 | W | 0x53382EA, 0x533831C | Zero |
| [rax] | 8 | W | 0x533831C, 0x533831F | Self-ptr |
| [rax+8] | 8 | W | 0x533831F | Self-ptr |
| [r14+0x4C8] | 8 | W | 0x5338323 | Zero |
| [r14+0x4D0] | 8 | R | 0x533832E, 0x5337BEF (earlier) | Ptr |
| [r14+0x4D8] | 8 | R | 0x5338335, 0x5337BF6 (earlier) | Ptr |
| [r14+0x4C0] | 8 | R | 0x5338345, 0x5337C4B (earlier) | Ptr |
| [r8] | 8 | W | 0x5338360, 0x53386A0 | Buffer fill |
| [rbp+0x248] | 8 | R/W | 0x5338370/0x5338377/0x5338810 | Ptr |
| [rbp+0x180] | 8 | R | 0x5338381, 0x53382BA | Compare ptr |
| [r14+0x130] | 8 | R | 0x5338395, 0x53381A1 | Source ptr |
| [r14+0x138] | 8 | R | 0x533839C, 0x53381A8 | Source ptr |
| [rbp+0x1F0] | 8 | W | 0x53383A3, 0x5337C36 | End ptr |
| [rbp+0x1E0] | 8 | W | 0x53383BA, 0x53383EF (earlier) | Ptr |
| [r12] | 8 | R/W | 0x53383AF/0x53383D4/0x53386D0 | Iteration ptr |
| [rax+0x5E8] | 8 | R | 0x53383E1, 0x5337C60 (earlier) | Nested ptr |
| [rdx+0xEC] | 4 | R | 0x53383E8, 0x5337C67 (earlier) | Int check |
| [rbp+0x248] | 8 | R | 0x53383F2, 0x5337C71 (earlier) | Ptr |
| [rcx+0x10] | 4 | R | 0x53383F9, 0x5337C78 (earlier) | Int |
| [rdx+0xC8] | 4 | R | 0x5338403, 0x5337C82 (earlier) | Int |
| [rdx+0xD4] | 4 | R | 0x5338411, 0x5337C90 (earlier) | Int |
| [rdx+0xCC] | 4 | R | 0x5338428, 0x5337CA7 (earlier) | Int |
| [rdx+0xD8] | 4 | R | 0x5338437, 0x5337CB6 (earlier) | Int |
| [rdx+0xD0] | 4 | R | 0x5338447, 0x5337CCC (earlier) | Int |
| [rdx+0xDC] | 4 | R | 0x5338467, 0x5337CE6 (earlier) | Int |
| [rdx+0xE0] | 4 | R | 0x53384B6, 0x5337D35 (earlier) | Int |
| [rbp+0x230] | 4 | R/W | 0x5338453/0x5337CD2 (earlier) | Counter |
| [r8+0x14] | 4 | R | 0x533841D, 0x5337C9C (earlier) | Int |
| [rdx+0xF8] | 8 | R | 0x5338503, 0x5337D82 (earlier) | Ptr |
| [rdx+0x100] | 8 | R | 0x533850A, 0x5337D89 (earlier) | Ptr |
| [rcx+8] | 4 | W | 0x5338542, 0x5337DC1 (earlier) | Refcount++ |
| [rax] | 8 | R | 0x5338546, 0x5337DC5 (earlier) | Ptr |
| [rax+8] | 8 | R | 0x5338549, 0x5337DC8 (earlier) | Ptr |
| [rbx+8] | 4 | W | 0x5338556, 0x5337DD5 (earlier) | Refcount-- |
| [rbx] | 8 | R | 0x5338560, 0x5337DDF (earlier) | Vtable |
| [rbx+0xC] | 4 | W | 0x533856F, 0x5337DF2 (earlier) | Weak refcount-- |
| [rsi+8] | 1 | R | 0x533858E | Flag byte (test 1) |
| [rbp+0xF0] | 8 | R | 0x5338598 | Ptr |
| [rbp+0x1E0] | 8 | R | 0x53385AD, 0x5338883 | Ptr |
| [rsi+0x128] | 8 | R | 0x53385BA | Nested ptr |
| [rax+0x480] | 8 | R | 0x53385C1 | Ptr |
| [rax+0x9A8] | 8 | R | 0x53385D2, 0x53350CC (earlier) | Refcounted ptr |
| [rcx+8] | 4 | W | 0x53385DE | Refcount++ |
| [rax+0x9A0] | 8 | R | 0x53385E9 | Ptr |
| [rbp+0x190] | 8 | W | 0x53385F4 | Ptr |
| [rbp+0x198] | 8 | W | 0x53385FB | Ptr |
| [rcx] | 8 | R | 0x5338602 | Vtable |
| [rax+0x58] | 8 | R | 0x5338605 | Vtable func |
| [rsi+0x568] | 4 | W | 0x5338610 | Store eax |
| [rdi+8] | 4 | W | 0x533861F, 0x5338638 | Refcount-- |
| [rdi] | 8 | R | 0x5338629, 0x5338642 | Vtable |
| [rdi+0xC] | 4 | W | 0x533863C | Weak refcount-- |
| [rbp+0xD0] | 16 | W | 0x53386B1 | Zero (xorps) |
| [rbp+0xE0] | 8 | W | 0x53386BB | Zero |
| [r14+0x138] | 8 | R | 0x53386C6 | Source ptr |
| [r14+0x130] | 8 | R | 0x53386CD | Source ptr |
| [rbp+0xD0] | 8 | W | 0x5338759, 0x5338760 | Alloc ptr |
| [rbp+0xD8] | 8 | W | 0x5338759, 0x5338767, 0x53387CD | Alloc ptr |
| [rbp+0xE0] | 8 | W | 0x5338767, 0x533876A | Alloc end |
| [rbp+0x190] | 8 | W | 0x533877F | Ptr [rbp+0xD0] |
| [rax] | 8 | R | 0x53387A0, 0x53387AE | Source ptr |
| [rbx] | 8 | W | 0x53387A0, 0x53387A6, 0x53387BB | Dest ptr |
| [rax+8] | 8 | R | 0x53387A3, 0x53387BE | Source ptr |
| [rbx+8] | 8 | W | 0x53387A6, 0x53387BE | Dest ptr |
| [rdx+8] | 4 | W | 0x53387C7 | Refcount++ |
| [rbp+0x190] | 8 | R | 0x53387DF, 0x53387E6 | Ptr |
| [r14+0x518] | 8 | R | 0x53387EB | List head |
| [r14+0x550] | 8 | R | 0x53387F9 | Ptr |
| [rbp+0x1E8] | 8 | W | 0x53387FF | Ptr |
| [rbp+0x1D0] | 8 | W | 0x5338800 | List head copy |
| [rbx+0x10] | 4 | R | 0x5338817 | Int |
| [rdx] | 4 | W | 0x533881A | Store int |
| [rbx+0x14] | 4 | R | 0x533881C | Int |
| [rdx+4] | 4 | W | 0x533881F | Store int |
| [rbx+0x18] | 4 | R | 0x5338822 | Int |
| [rdx+8] | 4 | W | 0x5338825 | Store int |
| [r14+0x558] | 8 | W | 0x5338828 | Inc by 0xC |
| [rbx] | 8 | R | 0x5338833 | Next in list |
| [rbp+0x248] | 8 | W | 0x5338840 | Ptr |
| [rbp+0xD0] | 8 | R | 0x5338847, 0x533885C | Alloc ptr |
| [rbp+0xD8] | 8 | R | 0x5338848, 0x5338855 | Alloc ptr |
| [rbp+0x1F0] | 8 | W | 0x5338855 | Alloc end |
| [r14+0x558] | 8 | R | 0x5338868 | Buffer ptr |
| [r14+0x560] | 8 | R | 0x533886F | Buffer end |
| [rbp+0x248] | 8 | R | 0x533887B | Ptr |
| [rbx+0x10] | 8 | R | 0x533887F | Ptr |
| [rbp+0x1E8] | 8 | R | 0x533888A | Ptr |

---

## Phase Table (0x533889E..0x5338F75 - lines 3601-4000)

| Range | Description |
|-------|-------------|
| 0x533889E..0x5338A5D | Element loop: iterate r15 by 0x10, load [rax+0x5E8], bounds check [rdx+0xC8/0xD4/0xCC/0xD8/0xD0/0xDC], float math with xmm7/xmm10/xmm11/xmm12/xmm13, ucomiss, load [rdx+0xF8/0x100], index, lock inc/dec refcounts |
| 0x5338A5D..0x5338B7A | Append to array: check [r14+0x420] vs [0x428], store rsi at [r12], inc [r14+0x420] by 8, else grow: compute new capacity (mul/div 0xAAAA...), alloc via 0x1233E1A8 (large/small), copy via 0xEEC6DE0, update [r14+0x418/0x420/0x428] |
| 0x5338B7A..0x5338C45 | Grow completion: call 0xE935700 if needed, store new base at [r14+0x418], jmp to 0x5338830 |
| 0x5338C45..0x5338E44 | List iteration: load [r14+0x550/0x558], compare, movd xmm6/xmm7, FNV-1a hash over 12 bytes at [rdi], compute bucket, walk hash table at [rdx+rax], compare keys [rcx+0x10/0x14/0x18], unlink: dec [rdx+0x520], relink list, call 0xE935700 |
| 0x5338E44..0x5338F75 | Cleanup: iterate [rbp+0xD0/0xD8], dec refcounts, call 0xF99FFA0, shrink buffer via 0xE935700, call 0x53C5F80, lock global 0x128D7360, inc counter, unlock, load [0x128D73C8], check byte==1, load [0x128D73D0], inc refcount |

Key instructions (verbatim, max 6 per phase):
```
0x53388a0  add r15,0x10
0x53388ad  mov rax,[r15]
0x53388b7  mov eax,[rdx+0xEC]
0x53389d2  mov r10,[rdx+0xF8]
0x5338a11  lock inc dword ptr [rcx+8]
0x5338a25  lock dec dword ptr [rdi+8]
0x5338a38  call qword ptr [0xF99FFA0]
```
```
0x5338a5d  mov r14,[rbp+0x250]
0x5338a64  mov r12,[r14+0x420]
0x5338a74  mov [r12],rsi
0x5338a8c  mov r15,r12
0x5338a99  sar rax,3
0x5338b1b  mov rax,[rcx]
```
```
0x5338b7a  mov [rdi+r15],rsi
0x5338b9e  call 0xEEC6DE0
0x5338bc5  call 0xEEC6DE0
0x5338c05  call 0xE935700
0x5338c11  mov rax,[rbp+0x1F0]
0x5338c18  lea rax,[rdi+rax*8]
0x5338c1c  mov [r14+0x420],rax
0x5338c2e  jmp 0x5338830
```
```
0x5338c45  mov rdi,[r14+0x550]
0x5338c53  cmp rdi,rbx
0x5338c56  movd xmm6,[rbp+0x78]
0x5338c5b  movss xmm7,[rbp+0x7C]
0x5338cbd  movzx eax,byte ptr [rdi]
0x5338cca  xor rax,r9
0x5338d94  and rax,[rcx+0x540]
```
```
0x5338e44  mov rdi,[rbp+0xD0]
0x5338e82  lock dec dword ptr [rbx+8]
0x5338e91  call qword ptr [0xF99FFA0]
0x5338ec9  mov rax,[rdi-8]
0x5338ee8  call 0xE935700
0x5338f0a  sar r8,3
0x5338f0e  call 0x53C5F80
```
```
0x5338f13  lea rdi,[0x128D7360]
0x5338f1a  mov rcx,rdi
0x5338f1d  call 0xE943178
0x5338f22  lock inc qword ptr [0x128D73C0]
0x5338f2a  mov rcx,rdi
0x5338f2d  call 0xE94319C
0x5338f32  mov rax,[0x128D73C8]
0x5338f43  mov rcx,[0x128D73D0]
```

## Strings Referenced (lines 3601-4000)

| RVA | Text | Site |
|-----|------|------|
| 0x128D7360 | (global state, not string) | 0x5338F13 |
| 0x128D73C0 | (global counter, not string) | 0x5338F22 |
| 0x128D73C8 | (global ptr, not string) | 0x5338F32, 0x5338F57 |
| 0x128D73D0 | (global ptr, not string) | 0x5338F43, 0x5338F65 |

No ASCII/UTF-8 string literals referenced in lines 3601-4000.

## Callees in Order (lines 3601-4000)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5338A11, 0x5338A38, 0x5338B1B, 0x5338B54, 0x5338E91, 0x5338EA7, 0x5338F53 |
| 0xEEC6DE0 | Buffer copy/move | 0x5338B9E, 0x5338BC5, 0x53389C2 (earlier), 0x53369C2 (earlier) |
| 0xE935700 | Deque push/grow | 0x5338C05, 0x5338CA5, 0x5338EE8 |
| 0x53C5F80 | Helper | 0x5338F0E |
| 0xE943178 | Lock global | 0x5338F1D, 0x5339DF (earlier), 0x5334EDE (earlier) |
| 0xE94319C | Unlock global | 0x5338F2D, 0x5334F31 (earlier) |
| 0x533BA90 | Hash/compare helper | (earlier) |
| 0x53C5CE0 | Helper | (earlier) |
| 0x9BC830 | Allocator helper | 0x5338B72, 0x5338C3A, 0x5339BC8 (earlier) |
| 0x53D92F0 | Helper | (earlier) |
| 0x53D96D0 | Helper | (earlier) |
| 0x533F160 | Helper | (earlier) |
| 0x533F8D0 | Helper | (earlier) |
| 0x5340B30 | Draw record handler | (earlier) |
| 0x533F580 | Handle lookup (draw record +0x63 write) | 0x53365E8, 0x5337EA2 (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 3601-4000)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [r15] | 8 | R/W | 0x53388A0/0x53388AD/0x5338892 (earlier) | Iteration ptr |
| [rbp+0x1F0] | 8 | R | 0x53388A4, 0x53383A3 (earlier) | End ptr |
| [rax+0x5E8] | 8 | R | 0x53388B0, 0x53383E1 (earlier) | Nested ptr |
| [rdx+0xEC] | 4 | R | 0x53388B7, 0x53383E8 (earlier) | Int check |
| [rbp+0x248] | 8 | R | 0x53388C1, 0x53383F2 (earlier) | Ptr |
| [rcx+0x10] | 4 | R | 0x53388C8, 0x53383F9 (earlier) | Int |
| [rdx+0xC8] | 4 | R | 0x53388D2, 0x5338403 (earlier) | Int |
| [rdx+0xD4] | 4 | R | 0x53388E0, 0x5338411 (earlier) | Int |
| [rdx+0xCC] | 4 | R | 0x53388F6, 0x5338428 (earlier) | Int |
| [rdx+0xD8] | 4 | R | 0x5338905, 0x5338437 (earlier) | Int |
| [rdx+0xD0] | 4 | R | 0x533891C, 0x5338447 (earlier) | Int |
| [rdx+0xDC] | 4 | R | 0x5338936, 0x5338467 (earlier) | Int |
| [rdx+0xE0] | 4 | R | 0x5338985, 0x53384B6 (earlier) | Int |
| [rbp+0x238] | 4 | W | 0x5338922 | Computed |
| [rbp+0x230] | 4 | W | 0x533893D | Computed |
| [rbp+0x238] | 4 | R | 0x53389E6 | Computed |
| [rdx+0xF8] | 8 | R | 0x53389D2, 0x5338503 (earlier) | Ptr |
| [rdx+0x100] | 8 | R | 0x53389D9, 0x533850A (earlier) | Ptr |
| [rcx+8] | 4 | W | 0x5338A11, 0x5338542 (earlier) | Refcount++ |
| [rax] | 8 | R | 0x5338A15, 0x5338546 (earlier) | Ptr |
| [rax+8] | 8 | R | 0x5338A18, 0x5338549 (earlier) | Ptr |
| [rdi+8] | 4 | W | 0x5338A25, 0x5338556 (earlier) | Refcount-- |
| [rdi] | 8 | R | 0x5338A2F, 0x5338560 (earlier) | Vtable |
| [rdi+0xC] | 4 | W | 0x5338A3E, 0x533856F (earlier) | Weak refcount-- |
| [r14+0x420] | 8 | R/W | 0x5338A64/0x5338A78/0x5338B75 | Array current |
| [r14+0x428] | 8 | R | 0x5338A6B | Array end |
| [r12] | 8 | W | 0x5338A74 | Store rsi |
| [r14+0x420] | 8 | W | 0x5338A78 | Inc by 8 |
| [rbp+0x248] | 8 | R | 0x5338A80, 0x5338840 | Ptr |
| [r14+0x418] | 8 | R | 0x5338A8F, 0x5338B95 | Array base |
| [rbp+0x1F0] | 8 | W | 0x5338AA6, 0x53383A3 | New capacity |
| [rbp+0x238] | 8 | W | 0x5338B22 | Alloc size |
| [rdi+r15] | 8 | W | 0x5338B7A | Store rsi in grown array |
| [r14+0x420] | 8 | R | 0x5338B85 | Array current |
| [r14+0x418] | 8 | R | 0x5338B95 | Array base |
| [r14+0x418] | 8 | W | 0x5338C11 | New base |
| [r14+0x420] | 8 | W | 0x5338C1C | New current |
| [r14+0x428] | 8 | W | 0x5338C27 | New end |
| [r14+0x550] | 8 | R | 0x5338C45, 0x53387F2 (earlier) | List head |
| [r14+0x558] | 8 | R/W | 0x5338C4C/0x5338C91/0x5338F07 | Buffer ptr |
| [rbp+0x78] | 4 | R | 0x5338C5B, 0x5335FD7 (earlier) | Float |
| [rbp+0x7C] | 4 | R | 0x5338C60, 0x5335031 (earlier) | Float |
| [rdi] | 1 | R | 0x5338CBD, 0x5335590 (earlier) | Hash key byte |
| [rdi+1..0xB] | 11×1 | R | 0x5338CDF-0x5338D6C | Hash key bytes (12 total) |
| [rbp+0x250] | 8 | R | 0x5338C8A, 0x5337AB5 (earlier) | Context ptr |
| [rdx+0x520] | 8 | W | 0x5338C8A | Dec counter |
| [rcx+8] | 8 | R | 0x5338C83, 0x5338C95 | Ptr |
| [rdx] | 8 | W | 0x5338C95, 0x5338C98 | Relink |
| [rax+8] | 8 | W | 0x5338C98, 0x5338C9C | Relink |
| [rbp+0xD0] | 8 | R | 0x5338E44, 0x533877F (earlier) | Alloc base |
| [rbp+0xD8] | 8 | R | 0x5338E54, 0x53387CD (earlier) | Alloc end |
| [rdi+8] | 8 | R | 0x5338E79, 0x5338E47 | Ptr |
| [rbx+8] | 4 | W | 0x5338E82, 0x5338211 (earlier) | Refcount-- |
| [rbx] | 8 | R | 0x5338E88, 0x5338217 (earlier) | Vtable |
| [rbx+0xC] | 4 | W | 0x5338E9B, 0x5338226 (earlier) | Weak refcount-- |
| [rdi-8] | 8 | R | 0x5338EC9 | Alloc header |
| [r14+0x418] | 8 | R | 0x5338EF6 | Array base |
| [r14+0x420] | 8 | R | 0x5338EFD | Array current |
| [rbp+0x190] | 8 | W | 0x5338F6A, 0x5338241 (earlier) | Zero |
| [rbp+0x198] | 1 | W | 0x5338F75, 0x5338248 (earlier) | Zero byte |
| [0x128D7360] | 8 | R | 0x5338F13, 0x5338F1A | Global state |
| [0x128D73C0] | 8 | W | 0x5338F22 | Global counter inc |
| [0x128D73C8] | 8 | R | 0x5338F32, 0x5338F57 | Global ptr |
| [rax] | 1 | R | 0x5338F3E | Byte check (==1) |
| [0x128D73D0] | 8 | R | 0x5338F43, 0x5338F65 | Global ptr |
| [rcx+8] | 4 | W | 0x5338F53 | Refcount++ |

---

## Phase Table (0x5338F75..0x5339674 - lines 4001-4400)

| Range | Description |
|-------|-------------|
| 0x5338F75..0x5339052 | Cleanup: zero stack buffers [rbp+0x1A0/0x1B0/0x100/0x110/0x10/0x20/-0x10/0], call 0x3B2020, compute [r14+0x138]-[0x130] sar 4, call 0x2FB1C0 twice |
| 0x5339052..0x533914E | Load [r14+0x128]->[rax+0x480]->[r14], load [r14+0x998]->[rax+0x480], load [rax+0x1160], call vtable [rax+0x150] via 0xF99FFA0, lock cmpxchg [rcx+8], complex hash lookup with bitmasks 0x3FFFF/0x7FF/0xFFFC0000, compare with 0x3FFFE/0x85B93800 |
| 0x533914E..0x5339256 | Dec refcounts on rdi, test r12b, traverse nested pointers at [rsi+0x48/0x50/0x68/0x70], check [rcx+8]==0x85B93800, check [rax+0x50], check byte [rdi+0x289] |
| 0x5339256..0x53392DF | Zero [rbp+0x200/0x210], set [rbp+0x218]=0xF, check [r14+0x968/0x96B], write "unwreward" (0x7461777265646E75) or "unlreward" (0x76616C7265646E75) to [rbp+0x200], call 0x5AC9F30 |
| 0x53392DF..0x533940A | Buffer grow check, write "fadi" (0x69646166) + "ng" (0x676E) to [rbp+0x200], call 0x5AC9F30, buffer grow check |
| 0x533940A..0x533951C | Iterate [rsi+0x418] to [0x420], prefetch, load [r8+0x20/0x10/0x30/0x40/0x48], check byte [r8+0x40], bounds check, load [rcx+0x20/0x10/0x30/0x40/0x48], check byte [rcx+0x40] |
| 0x53394C9..0x533951C | Global lock path: xor ecx, load [0x128D73D8], set up [rbp+0x190/0x198/0x1A0/0x1A8/0x1B0], check [rax] byte==1, load [rdx+0x188], jmp to 0x5338FA0 |
| 0x533951C..0x5339674 | Main render loop: iterate r14 up to rbx, prefetch [rax+r14*8+0x18/0x10], load [rcx+0x20/0x10/0x30/0x40/0x48], check byte [rcx+0x40], load [rcx+0x48], check byte [rcx+0x20], load [rax+0x130]->[rcx+0x960], call 0x537E150 |

Key instructions (verbatim, max 6 per phase):
```
0x5338f7c  xorps xmm0,xmm0
0x5338f7f  movups [rbp+0x1A0],xmm0
0x5338f98  call 0x3B2020
0x5338ff1  shr rax,0x3D
0x5339006  call 0x2FB1C0
0x533904c  call 0x2FB1C0
```
```
0x5339052  mov rax,[rbp+0x250]
0x5339060  mov r14,[rax+0x480]
0x5339067  mov rax,[r14+0x998]
0x5339075  mov rcx,[rax+0x1160]
0x5339086  lea rdx,[rbp+0xB0]
0x533908d  call qword ptr [0xF99FFA0]
```
```
0x53390c8  lea edx,[rax+1]
0x53390cb  lock cmpxchg [rcx+8],edx
0x53390f7  mov rdx,[rsi+0x110]
0x533911a  and eax,0x7FF
0x533912c  cmp edx,0x3FFFE
0x5339142  add rsi,0x30
```
```
0x5339256  xorps xmm0,xmm0
0x533926b  mov qword ptr [rbp+0x218],0xF
0x533927d  cmp byte ptr [r14+0x968],0
0x5339293  mov rcx,0x7461777265646E75
0x53392c0  lea rdx,[rbp+0x200]
0x53392c7  mov [rbp+0x210],rax
0x53392fc  call 0x5AC9F30
```
```
0x5339371  mov qword ptr [rbp+0x210],6
0x533939b  mov dword ptr [rbp+0x200],0x69646166
0x53393ae  lea rdx,[rbp+0xB0]
0x53393bf  call 0x5AC9F30
0x533940a  mov rdx,[rsi+0x418]
```
```
0x53394c9  xor ecx,ecx
0x53394d2  mov [rbp+0x190],rdi
0x53394d9  mov byte ptr [rbp+0x198],1
0x53394e0  mov [rbp+0x1A0],rax
0x53394e7  mov [rbp+0x1A8],rcx
0x53394ee  mov [rbp+0x1B0],rdx
```
```
0x5339530  lea rax,[r14+3]
0x533953d  mov rax,[rbp+0x250]
0x533954b  mov rcx,[rax+r14*8+0x18]
0x5339558  mov rdx,[rcx+0x20]
0x5339566  movzx edx,byte ptr [rcx+0x40]
0x53395d4  inc r14
0x533960d  call 0x537E150
```

## Strings Referenced (lines 4001-4400)

| RVA | Text | Site |
|-----|------|------|
| 0x7461777265646E75 | "unwreward" (little-endian: "unwreward") | 0x5339293 |
| 0x76616C7265646E75 | "unlreward" (little-endian: "unlreward") | 0x53392C7 |
| 0x69646166 | "fadi" (little-endian: "fadi") | 0x533939B |
| 0x676E | "ng" (little-endian: "ng") | 0x53393A5 |

These are ASCII strings written to stack buffers for debug/logging: "unwreward", "unlreward", "fading".

## Callees in Order (lines 4001-4400)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0x3B2020 | Global cleanup | 0x5338F98, 0x5334A50 (earlier), 0x5334FE6 (earlier) |
| 0x2FB1C0 | Helper | 0x5339006, 0x533904C |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x533908D, 0x533915F, 0x5339162, 0x5339178, 0x533936B, 0x5338F53 (earlier) |
| 0x5AC9F30 | String/log helper | 0x53392FC, 0x53393BF |
| 0xE935700 | Deque push/grow | 0x533932E, 0x53393E6, 0x5338CA5 (earlier), 0x5338EE8 (earlier), 0x5338C05 (earlier) |
| 0x537E150 | **Render/draw call** | 0x533960D, 0x533966C |
| 0xE943178 | Lock global | 0x5338F1D (earlier), 0x5339DF (earlier), 0x5334EDE (earlier) |
| 0xE94319C | Unlock global | 0x5338F2D (earlier), 0x5334F31 (earlier) |
| 0x53C5F80 | Helper | 0x5338F0E (earlier) |
| 0x53C5CE0 | Helper | (earlier) |
| 0x9BC830 | Allocator helper | (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 4001-4400)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rbp+0x1A0] | 16 | W | 0x5338F7F | Zero |
| [rbp+0x1B0] | 8 | W | 0x5338F86 | Zero |
| [rbp+0x100] | 16 | W | 0x5338FA3 | Zero |
| [rbp+0x110] | 8 | W | 0x5338FAA | Zero |
| [rbp+0x10] | 16 | W | 0x5338FB5 | Zero |
| [rbp+0x20] | 8 | W | 0x5338FB9 | Zero |
| [rbp-0x10] | 16 | W | 0x5338FC1 | Zero |
| [rbp] | 8 | W | 0x5338FC5 | Zero |
| [r14+0x138] | 8 | R | 0x5338FD4, 0x5338FC3 (earlier) | Source ptr |
| [r14+0x130] | 8 | R | 0x5338FDB, 0x5338FC3 (earlier) | Source ptr |
| [rbp+0x200] | 8 | W | 0x5338FE5, 0x533902B, 0x5339259, 0x533929D, 0x53392D8, 0x533939B | Computed/string |
| [rbp+0x250] | 8 | R | 0x533900C, 0x5337AB5 (earlier) | Context ptr |
| [rax+0x138] | 8 | R | 0x5339013, 0x5338FC3 (earlier) | Source ptr |
| [rax+0x130] | 8 | R | 0x533901A, 0x5338FC3 (earlier) | Source ptr |
| [rax+0x128] | 8 | R | 0x5339059, 0x5338FC3 (earlier) | Nested ptr |
| [rax+0x480] | 8 | R | 0x5339060, 0x533906E, 0x5338FC3 (earlier) | Ptr |
| [r14+0x998] | 8 | R | 0x5339067 | Ptr |
| [rax+0x480] | 8 | R | 0x533906E | Ptr |
| [rax+0x1160] | 8 | R | 0x5339075 | Ptr |
| [rcx] | 8 | R | 0x533907C | Vtable |
| [rax+0x150] | 8 | R | 0x533907F | Vtable func |
| [rbp+0xB0] | 8 | R | 0x5339086, 0x53393AE | Ptr |
| [rbp+0xB8] | 8 | R/W | 0x5339094, 0x5339359 | Ptr (refcounted) |
| [rbp+0xC0] | 4 | R | 0x53390A9, 0x53390EB, 0x53391E1, 0x5339211 | Hash key |
| [rcx+8] | 4 | R/W | 0x53390BD/0x53390CB/0x5339153 | Refcount (cmpxchg/dec) |
| [rbp+0xB0] | 8 | R | 0x53390D9 | Ptr |
| [rbp+0xB8] | 8 | R | 0x53390E0 | Ptr |
| [rsi+0x110] | 8 | R | 0x53390F7 | Ptr |
| [rsi+0x118] | 8 | R | 0x5339105 | Ptr |
| [rdx+rcx*8] | 8 | R | 0x5339111 | Indexed ptr |
| [rcx+rax*4] | 4 | R | 0x5339127, 0x5339217 | Indexed int |
| [rsi+0x150] | 8 | R | 0x5339139 | Limit |
| [rsi+0x48] | 8 | R | 0x5339187 | Ptr |
| [rsi+0x50] | 8 | R | 0x533918B | Ptr |
| [rsi+0x68] | 8 | R | 0x53391A2 | Ptr |
| [rsi+0x70] | 8 | R | 0x53391D2 | Ptr |
| [rax+rcx] | 8 | R | 0x53391C1, 0x53391CF | Ptr |
| [rax+rcx+8] | 4 | R | 0x53391C5 | Int (cmp 0x85B93800) |
| [rax+0x10] | 8 | R | 0x53391D8 | Ptr |
| [rax+8] | 8 | R | 0x53391F2 | Ptr |
| [rax+0x10] | 8 | R | 0x53391F6 | Ptr |
| [rax+0x50] | 8 | R | 0x5339224 | Ptr |
| [rax+rdx] | 8 | R | 0x5339233 | Ptr |
| [rax+rcx*8] | 8 | R | 0x5339245 | Ptr |
| [rdi+0x289] | 1 | R | 0x5339249 | Byte check |
| [rbp+0x200] | 16 | W | 0x5339259, 0x533929D, 0x53392D8, 0x533939B | String buffer |
| [rbp+0x210] | 8 | W | 0x533926B, 0x533928C, 0x53392C0, 0x5339371 | Length |
| [rbp+0x218] | 8 | W | 0x533926B, 0x533928C, 0x53392C0, 0x533937C | Capacity (0xF) |
| [r14+0x968] | 1 | R | 0x533927D | Byte flag |
| [r14+0x96B] | 1 | R | 0x53392AC | Byte flag |
| [rbp+0x28] | 8 | R | 0x533929D | Ptr |
| [rdx] | 8 | W | 0x53392A1, 0x53392D8 | String write |
| [rdx+8] | 2 | W | 0x53392AA, 0x53392DB | String write |
| [rbp+rax+0x200] | 1 | W | 0x53392DF | Null terminator |
| [r14] | 8 | R | 0x53392E7 | Ptr (+0x370) |
| [rbp-0x20] | 8 | R | 0x53392EE, 0x5339302 | Ptr |
| [rbp+0x200] | 8 | R | 0x53392F9, 0x5339321 | Ptr |
| [rbp+0x218] | 8 | R | 0x5339306, 0x53393CC | Capacity |
| [rbp+0x250] | 8 | R | 0x5339318, 0x533953D, 0x533962F | Context ptr |
| [rbp+0xB8] | 8 | R | 0x5339359, 0x5339094 | Ptr |
| [rcx+0xC] | 4 | W | 0x533935E, 0x533916C | Weak refcount-- |
| [rcx] | 8 | R | 0x5339364, 0x5339159 | Vtable |
| [rax+8] | 8 | R | 0x5339367, 0x5339171 | Vtable func |
| [rbp+0x206] | 2 | W | 0x5339387 | Zero word |
| [rbp+0x20E] | 2 | W | 0x5339392 | Zero word |
| [rbp+0x200] | 4 | W | 0x533939B | "fadi" |
| [rbp+0x204] | 2 | W | 0x53393A5 | "ng" |
| [rbp+0xB0] | 8 | R | 0x53393AE, 0x5339086 | Ptr |
| [rbp+0x200] | 8 | R | 0x53393BF, 0x53392F9 | Ptr |
| [rsi+0x418] | 8 | R | 0x533940A, 0x5338EF6 (earlier) | Array base |
| [rsi+0x420] | 8 | R | 0x5339411, 0x5338EFD (earlier) | Array current |
| [rsi+0x418] | 8 | R | 0x533953D | Array base |
| [rax+r14*8+0x18] | 8 | R | 0x533954B | Element ptr |
| [rax+r14*8+0x10] | 8 | R | 0x5339553 | Element ptr |
| [rcx+0x20] | 8 | R | 0x5339558, 0x5339437, 0x533947B | Ptr |
| [rcx+0x10] | 8 | R | 0x533955F, 0x533943E, 0x5339482 | Ptr |
| [rcx+0x30] | 8 | R | 0x5339574, 0x5339459, 0x5339497 | Ptr |
| [rcx+0x40] | 1 | R | 0x5339566, 0x5339446, 0x5339485 | Byte flag |
| [rcx+0x48] | 8 | R | 0x5339588, 0x5339468, 0x53394A8 | Ptr |
| [rax+r14*8+8] | 8 | R | 0x533958F | Element ptr |
| [rcx+0x20] | 8 | R | 0x533959F | Ptr |
| [rcx+0x20] | 1 | R | 0x53395A4 | Byte flag |
| [rcx+0x10] | 8 | R | 0x53395B2 | Ptr |
| [rax+r14*8] | 8 | R | 0x53395D4, 0x5339636 | Element ptr |
| [r8+8] | 1 | R | 0x53395DC, 0x533963F | Byte flag (test 1) |
| [rax+0x130] | 8 | R | 0x53395E9, 0x5339648, 0x5338FC3 (earlier) | Source ptr |
| [rcx+0x960] | 8 | R | 0x53395F3, 0x5339652 | Ptr |
| [rsp+0x30] | 8 | W | 0x53395FA, 0x5339659 | Stack save |
| [rsp+0x28] | 8 | W | 0x53395FF, 0x533965E | Stack save |
| [rsp+0x20] | 4 | W | 0x5339604, 0x5339663 | Stack save (xmm6) |
| [rbp+0x170] | 8 | R | 0x5339674, 0x5336A5D (earlier) | Counter |

---

## Phase Table (0x5339674..0x5339DFF - lines 4401-4800)

| Range | Description |
|-------|-------------|
| 0x5339674..0x53396C7 | Final stats: test [rbp+0x170], cvtsi2ss/divss, load [rax+0x128]->[0x480], load [rax+0x5C8], subss/mulss/addss, store back [rax+0x5C8] |
| 0x53396C7..0x5339766 | Global lock 0x128D2240: lock, inc counter, unlock, load [0x128D22A8], check byte==1, load [0x128D22B0], inc refcount, or zero [rbp+0x200/0x208], call 0x3B2020, check flag |
| 0x5339766..0x5339920 | Draw record finalization: test r15b, load [rbp+0x1A0/0x1B0], check [rsi] byte==1, compare [r14+0x190] vs [0x198], store, load [rbp+0x100/0x108], shr 2, mul 0xAAAAAAAB, store at [r14+0x18C], lock 0x128D2240, call 0xE943170, loop: call 0x533F580, **check [rax+0x63]==0**, crash if not, call 0x53C5CE0, unlock 0xE943194 |
| 0x5339920..0x5339C4C | Element iteration: load [rax+0x130/0x138], iterate rbx by 0x10, load [rbx+0x960], compute (rcx-[rax+0x18]) sar 3, imul 0x8E38E38E38E38E39, store at [r13+8], lock global 0x128D2240, inc counter, unlock, load [0x128D22A8/B0/B8], inc refcounts, xchg [rax+0x178], lock add [rax+0x170], dec refcounts |
| 0x5339C4C..0x5339DD7 | Stats aggregation: load [rbp+0x90/0x98], lea 0x128D2240, lock/inc/unlock, load [0x128D22A8/B0/B8], inc refcounts, xchg [rax+0x188], lock add [rax+0x180], dec refcounts, unlock, check rcx-rax >= 5 |
| 0x5339DD7..0x5339DFF | Buffer shrink: test [rbp-0x10], sub [rbp]-[rbp-0x10], cmp 0x1000, grow/shrink via 0xE935700 |

Key instructions (verbatim, max 6 per phase):
```
0x533967b  test ecx,ecx
0x5339689  cvtsi2ss xmm0,ecx
0x5339695  divss xmm1,xmm0
0x53396a7  movss xmm0,[rax+0x5C8]
0x53396bb  addss xmm1,xmm0
0x53396bf  movss [rax+0x5C8],xmm1
```
```
0x53396d4  lea rbx,[0x128D2240]
0x53396de  call 0xE943178
0x53396e3  lock inc qword ptr [0x128D22A0]
0x53396eb  mov rcx,rbx
0x53396ee  call 0xE94319C
0x53396f3  mov r14,[0x128D22A8]
0x533971c  lock inc dword ptr [rax+8]
```
```
0x533976f  mov rsi,[rbp+0x1A0]
0x533978f  mov rax,[r14+0x190]
0x533985a  shr rax,2
0x533985e  imul eax,0xAAAAAAAB
0x5339864  mov [r14+0x18C],eax
0x5339899  call 0xE943170
```
```
0x53398d9  mov rcx,[rbp+0x250]
0x53398e0  mov rdx,rdi
0x53398e3  call 0x533F580
0x53398ee  cmp byte ptr [rax+0x63],0
0x53398f2  jne short 0x53398D0
0x533990c  call 0x53C5CE0
```
```
0x533993e  mov r15,0x8E38E38E38E38E39
0x5339975  mov rax,[r13+0x960]
0x5339984  sar rcx,3
0x5339988  imul rcx,r15
0x5339990  mov rcx,rsi
0x5339993  call 0xE943178
0x5339998  lock inc qword ptr [0x128D22A0]
0x53399cd  lock inc dword ptr [rax+8]
```
```
0x5339a58  nop [rax+rax]
0x5339a60  mov r8,[rdx+rcx+0x38]
0x5339a6a  sar r8,3
0x5339a72  mov [rax-0x80],r8
0x5339b63  mov rdx,[r13+0x960]
0x5339c41  jne 0x5339A60
```
```
0x5339c4c  mov rax,[rbp+0x90]
0x5339c5d  mov rcx,rsi
0x5339c60  call 0xE943178
0x5339c6d  mov rcx,rsi
0x5339c70  call 0xE94319C
0x5339c75  mov rax,[0x128D22A8]
0x5339c92  lock inc dword ptr [rax+8]
0x5339cc3  lock add [rax+0x170],rdi
0x5339d07  mov rax,[rbp+0x90]
0x5339d18  cmp rcx,5
```

## Strings Referenced (lines 4401-4800)

| RVA | Text | Site |
|-----|------|------|
| None | No string literals in this range | - |

## Callees in Order (lines 4401-4800)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xE943178 | Lock global | 0x53396DE, 0x5339993, 0x5339C5D, 0x5339D2D |
| 0xE94319C | Unlock global | 0x53396EB, 0x53399A0, 0x5339C70, 0x5339D40 |
| 0xE943170 | Lock (variant) | 0x5339899 |
| 0xE943194 | Unlock (variant) | 0x533991B |
| 0x3B2020 | Global cleanup | 0x533974C, 0x5339843, 0x5339A43, 0x5339CFB, 0x5339D02, 0x5339DD2 |
| 0x533F580 | **Handle lookup (draw record +0x63 write)** | 0x53398E3 |
| 0x53C5CE0 | Helper | 0x533990C, 0x533888A (earlier), 0x53372FD (earlier), 0x5336EAA (earlier) |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x53399CD, 0x5339C92, 0x5339D62, 0x5339A1E, 0x5339A2E, 0x5339A34, 0x5339CDF, 0x5339CE5, 0x5339D7F, 0x5339DBF, 0x5339E07 |
| 0xEEC5920 | Get timestamp | 0x5339816, 0x53348EE (earlier), 0x5335DE1 (earlier) |
| 0xEEC5930 | Get frequency | 0x533981E, 0x53348F6 (earlier), 0x5335DE9 (earlier) |
| 0x533BA90 | Hash/compare helper | (earlier) |
| 0x53D92F0 | Helper | (earlier) |
| 0x53D96D0 | Helper | (earlier) |
| 0x533F160 | Helper | (earlier) |
| 0x533F8D0 | Helper | (earlier) |
| 0x5340B30 | Draw record handler | (earlier) |
| 0x5AC9F30 | String/log helper | (earlier) |
| 0x2FB1C0 | Helper | (earlier) |
| 0xE935700 | Deque push/grow | 0x5339E0C, 0x5339DEE (earlier), 0x5338CA5 (earlier), 0x5338EE8 (earlier), 0x5338C05 (earlier), 0x533932E (earlier), 0x53393E6 (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 4401-4800)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rbp+0x170] | 4 | R | 0x533967B, 0x5336A5D (earlier) | Counter |
| [rbp+0x178] | 4 | R | 0x533968D, 0x5336A6D (earlier) | Float accumulator |
| [rbp+0x250] | 8 | R | 0x5339681, 0x5337AB5 (earlier) | Context ptr |
| [rax+0x128] | 8 | R | 0x5339699, 0x5338FC3 (earlier) | Nested ptr |
| [rax+0x480] | 8 | R | 0x53396A0, 0x5338FC3 (earlier) | Ptr |
| [rax+0x5C8] | 4 | R/W | 0x53396AF/0x53396BF | Float value |
| [rbp+0x247] | 1 | R | 0x53396C7, 0x5335DD8 (earlier) | Flag |
| [0x128D2240] | 8 | R | 0x53396D4, 0x5339745, 0x533994F, 0x5339C5D, 0x5339D2D | Global state |
| [0x128D22A0] | 8 | W | 0x53396E3, 0x5339998, 0x5339C6D, 0x5339D35 | Global counter |
| [0x128D22A8] | 8 | R | 0x53396F3, 0x53399A8, 0x5339C7C, 0x5339D4C | Global ptr |
| [0x128D22B0] | 8 | R | 0x5339705, 0x53399C1, 0x5339C86, 0x5339D56 | Global ptr |
| [rax+8] | 4 | W | 0x533971C, 0x53399CD, 0x5339C92, 0x5339D62 | Refcount++ |
| [rbp+0x1F0] | 4 | W | 0x5339716 | r15d save |
| [rbp+0x200] | 8 | W | 0x5339733, 0x53397E0, 0x5339259 (earlier) | Zero/ptr |
| [rbp+0x208] | 1 | W | 0x533973E, 0x53397E7, 0x5339259 (earlier) | Flag byte |
| [rbp+0x210] | 8 | W | 0x53397E7 | Ptr |
| [rbp+0x218] | 8 | W | 0x53397FC | Ptr |
| [rbp+0x220] | 8 | W | 0x53397FC | Ptr |
| [0x128D22B8] | 8 | R | 0x53397D9, 0x53399EB, 0x5339CB9, 0x5339D89 | Global config |
| [r14+0x190] | 8 | R | 0x533978F, 0x533988B | Ptr |
| [r14+0x198] | 8 | R/W | 0x5339796/0x53397A3/0x53398A7/0x53398C0 | Ptr |
| [r14+0x1A0] | 8 | R | 0x53398A7 | Ptr |
| [rbp+0x100] | 8 | R | 0x53397AA, 0x5339846 | Ptr |
| [rbp+0x108] | 8 | R | 0x53397B1, 0x533984D | Ptr |
| [r14+0x18C] | 4 | W | 0x5339864 | Computed |
| [rsi] | 1 | R | 0x53397BE, 0x53397C1, 0x5339874, 0x53398F4 | Byte check |
| **[rax+0x63]** | **1** | **R** | **0x53398EE** | **DEPTH BYTE READ (check if 0) via 0x533F580 return** |
| [rbp+0x248] | 8 | W | 0x5339899 | Ptr |
| [rbx] | 8 | R | 0x5339960, 0x533996D | Element ptr |
| [r13] | 8 | R | 0x5339970, 0x5339A56 | Element ptr |
| [r13+0x960] | 8 | R | 0x5339975, 0x5339A4F, 0x5339B63 | Ptr |
| [rax+0x20] | 8 | R | 0x533997C | Ptr |
| [rax+0x18] | 8 | R | 0x5339980 | Ptr |
| [r13+8] | 8 | W | 0x533998C | Computed |
| [0x128D22A0] | 8 | W | 0x5339998, 0x5339C6D, 0x5339D35 | Global counter |
| [0x128D22A8] | 8 | R | 0x53399A8, 0x5339C7C, 0x5339D4C | Global ptr |
| [0x128D22B0] | 8 | R | 0x53399C1, 0x5339C86, 0x5339D56 | Global ptr |
| [rax+8] | 4 | W | 0x53399CD, 0x5339C92, 0x5339D62 | Refcount++ |
| [rax+0x178] | 8 | R/W | 0x53399FB/0x5339A02/0x5339CBC/0x5339D8C | Xchg |
| [rax+0x170] | 8 | W | 0x5339A02, 0x5339CC3, 0x5339D93 | Lock add |
| [rdi+8] | 4 | W | 0x5339A0F, 0x5339A24, 0x5339CD4, 0x5339DA4 | Refcount-- |
| [rdi] | 8 | R | 0x5339A15, 0x5339A2A, 0x5339CD6, 0x5339DA6 | Vtable |
| [rdi+0xC] | 4 | W | 0x5339A1E, 0x5339A2E, 0x5339CDF, 0x5339DB5 | Weak refcount-- |
| [rax+0x188] | 8 | R/W | 0x5339CBC/0x5339D8C | Xchg |
| [rax+0x180] | 8 | W | 0x5339CC3, 0x5339D93 | Lock add |
| [rbp+0x90] | 8 | R | 0x5339C4C, 0x5339D07 | Ptr |
| [rbp+0x98] | 8 | R | 0x5339D0E | Ptr |
| [rbp-0x10] | 8 | R | 0x5339DD7, 0x5338FC1 (earlier) | Ptr |
| [rbp] | 8 | R | 0x5339DE0, 0x5338FC5 (earlier) | Ptr |
| [rcx-8] | 8 | R | 0x5339DF0, 0x5338A15 (earlier) | Alloc header |
| [rcx] | 8 | R/W | 0x5339DF4/0x5339DF8 | Ptr |
| [rdx+rcx+0x38] | 8 | R | 0x5339A60 | Ptr |
| [rdx+rcx+0x30] | 8 | R | 0x5339A65 | Ptr |
| [rdx+rcx+0x50] | 8 | R | 0x5339A76 | Ptr |
| [rdx+rcx+0x48] | 8 | R | 0x5339A7B | Ptr |
| [rdx+rcx+0x68] | 8 | R | 0x5339A8C | Ptr |
| [rdx+rcx+0x60] | 8 | R | 0x5339A91 | Ptr |
| [rdx+rcx+0x80] | 8 | R | 0x5339AA2 | Ptr |
| [rdx+rcx+0x78] | 8 | R | 0x5339AAA | Ptr |
| [rdx+rcx+0x98] | 8 | R | 0x5339ABB | Ptr |
| [rdx+rcx+0x90] | 8 | R | 0x5339AC3 | Ptr |
| [rdx+rcx+0xB0] | 8 | R | 0x5339AD7 | Ptr |
| [rdx+rcx+0xA8] | 8 | R | 0x5339ADF | Ptr |
| [rdx+rcx+0xC8] | 8 | R | 0x5339AF3 | Ptr |
| [rdx+rcx+0xC0] | 8 | R | 0x5339AFB | Ptr |
| [rdx+rcx+0xE0] | 8 | R | 0x5339B0F | Ptr |
| [rdx+rcx+0xD8] | 8 | R | 0x5339B17 | Ptr |
| [rdx+rcx+0xF8] | 8 | R | 0x5339B2B | Ptr |
| [rdx+rcx+0xF0] | 8 | R | 0x5339B33 | Ptr |
| [rdx+rcx+0x110] | 8 | R | 0x5339B47 | Ptr |
| [rdx+rcx+0x108] | 8 | R | 0x5339B4F | Ptr |
| [rdx+rcx+0x128] | 8 | R | 0x5339B6A | Ptr |
| [rdx+rcx+0x120] | 8 | R | 0x5339B72 | Ptr |
| [rdx+rcx+0x140] | 8 | R | 0x5339B86 | Ptr |
| [rdx+rcx+0x138] | 8 | R | 0x5339B8E | Ptr |
| [rdx+rcx+0x158] | 8 | R | 0x5339BAA | Ptr |
| [rdx+rcx+0x150] | 8 | R | 0x5339B96 | Ptr |
| [rdx+rcx+0x170] | 8 | R | 0x5339BBE | Ptr |
| [rdx+rcx+0x168] | 8 | R | 0x5339BC6 | Ptr |
| [rdx+rcx+0x188] | 8 | R | 0x5339BDA | Ptr |
| [rdx+rcx+0x180] | 8 | R | 0x5339BE2 | Ptr |
| [rdx+rcx+0x1A0] | 8 | R | 0x5339BFE | Ptr |
| [rdx+rcx+0x198] | 8 | R | 0x5339C06 | Ptr |
| [rdx+rcx+0x1B8] | 8 | R | 0x5339C12 | Ptr |
| [rdx+rcx+0x1B0] | 8 | R | 0x5339C1A | Ptr |
| [rax-0x80] | 8 | W | 0x5339A72 | Computed |
| [rax-0x78] | 8 | W | 0x5339A84 | Computed |
| [rax-0x70] | 8 | W | 0x5339A9A | Computed |
| [rax-0x68] | 8 | W | 0x5339AB7 | Computed |
| [rax-0x60] | 8 | W | 0x5339ACF | Computed |
| [rax-0x58] | 8 | W | 0x5339AE7 | Computed |
| [rax-0x50] | 8 | W | 0x5339B0B | Computed |
| [rax-0x48] | 8 | W | 0x5339B27 | Computed |
| [rax-0x40] | 8 | W | 0x5339B43 | Computed |
| [rax-0x38] | 8 | W | 0x5339B5F | Computed |
| [rax-0x30] | 8 | W | 0x5339B82 | Computed |
| [rax-0x28] | 8 | W | 0x5339B9E | Computed |
| [rax-0x20] | 8 | W | 0x5339BBA | Computed |
| [rax-0x18] | 8 | W | 0x5339BD6 | Computed |
| [rax-0x10] | 8 | W | 0x5339BF2 | Computed |
| [rax-8] | 8 | W | 0x5339C0E | Computed |
| [rax] | 8 | W | 0x5339C2A | Computed |

---

## Phase Table (0x5339DFF..0x533A78B - lines 4801-5365)

| Range | Description |
|-------|-------------|
| 0x5339DFF..0x5339E4B | Buffer shrink: add rdx/0x27, call 0xE935700, shrink [rbp+0x10/0x20], [rbp+0x100/0x110], [rbp-0x40/-0x30], [rbp+0x60/0x70] |
| 0x5339E4B..0x5339F0E | Cleanup: zero [rbp+0x1A0/0x1B0], dec refcounts on [rbp+0x1A8], [rbp+0x50], call 0xF99FFA0 |
| 0x5339F0E..0x533A069 | Final checks: test [rbp+0x198], call 0x3B2020, shrink [rbp+0x90/0xA0], [rbp-0x40/-0x30], [rbp+0x60/0x70], call 0x112CB0, zero [rbp+0x48/0x58], dec refcounts, check [rbp+0x40], call 0x3B2020 |
| 0x533A069..0x533A0CB | Epilog: restore XMM6-15 from [rbp+0x260..0x2F0], add rsp/0x388, pop rbx/rdi/rsi/r12-r15/rbp, ret |
| 0x533A0CB..0x533A17B | Alt exit: zero [rbp+0x17C], jmp to 0x5334A68, timestamp magic (0xB2F4FC0794908CF3/0x16E3600/0x989680), mul/div, check [r14] byte |
| 0x533A17B..0x533A2A0 | Path: call 0xEEC59F0, check [r12+0xDC/0x13C], store [rbp+0x80] at [r12+0x80/0xE0], add [r12+0x88/0xE8], call 0xEEC5A10, check [r14] byte |
| 0x533A2A0..0x533A4B0 | Loop: mov [rbp+0x248], imul r10/0x198, loop r11 0..0x10, load [rax+0x960+rcx*8+0x30/0x38], mul r9 (0xCCCCCCCCCCCCCCCD), SIMD pcmpeqb/punpcklbw/pshuflw/pshufd/pand/paddq, accumulate xmm2/xmm3 |
| 0x533A4B0..0x533A548 | Finalize: test r14, check byte, add [r12+r11*8+0x218], dec refcounts on [rbp+0x218/0x220], call 0xF99FFA0 |
| 0x533A548..0x533A659 | Error/debug: lea rcx/[0xF5B2BCD], call 0xEEC5850, call 0x297C080, cmp eax, call vtable [rax+0x460] via 0xF99FFA0, write "fog" (0x6F66) + "g" (0x67) to stack |
| 0x533A659..0x533A78B | Overflow handlers: call 0x75740, 0x9BC830, 0x1166E0, 0x75B60, 0xEEC5A00, set [r12+0xDC/0x13C]=0x7FFFFFFE, int3 at end |

Key instructions (verbatim, max 6 per phase):
```
0x5339e05  add rdx,0x27
0x5339e0c  call 0xE935700
0x5339e11  mov rcx,[rbp+0x10]
0x5339e15  test rcx,rcx
0x5339e1e  sub rdx,rcx
0x5339e2a  mov rax,[rcx-8]
```
```
0x5339e4b  mov rcx,[rbp+0x100]
0x5339e8b  xorps xmm0,xmm0
0x5339e9c  test rsi,rsi
0x5339ea1  lock dec dword ptr [rsi+8]
0x5339eb0  call qword ptr [0xF99FFA0]
0x5339f0e  cmp byte ptr [rbp+0x198],1
```
```
0x5339f63  mov rcx,[rbp-0x40]
0x5339fd7  lea rcx,[rbp+0x120]
0x5339fde  call 0x112CB0
0x5339fe3  xorps xmm0,xmm0
0x5339ff3  lock dec dword ptr [rsi+8]
0x533a002  call qword ptr [0xF99FFA0]
```
```
0x533a069  movaps xmm6,[rbp+0x260]
0x533a070  movaps xmm7,[rbp+0x270]
0x533a0b7  add rsp,0x388
0x533a0be  pop rbx
0x533a0c9  pop rbp
0x533a0ca  ret
0x533a0cb  mov dword ptr [rbp+0x17C],0
```
```
0x533a0dc  mov r9,0xB2F4FC0794908CF3
0x533a0e9  imul r9
0x533a17b  cmp byte ptr [r14],0
0x533a181  mov dword ptr [0],0xDEADC0DE
0x533a197  call 0xEEC59F0
0x533a1d0  call 0xEEC5A10
```
```
0x533a2b4  mov [rbp+0x248],rax
0x533a2bb  imul r10,rax,0x198
0x533a319  mov rdi,[rax+rcx*8+0x30]
0x533a390  movzx r15d,byte ptr [rcx-0x78]
0x533a3bb  pcmpeqb xmm4,xmm0
0x533a3fc  paddq xmm2,xmm3
```
```
0x533a493  mov byte ptr [r12+0x18],0
0x533a499  mov rdi,[rbp+0x218]
0x533a4b0  mov r15d,[rbp+0x1F0]
0x533a4b7  je 0x5339751
0x533a4bd  lock dec dword ptr [rdi+8]
0x533a4cc  call qword ptr [0xF99FFA0]
```
```
0x533a53b  lea rcx,[0xF5B2BCD]
0x533a542  call 0xEEC5850
0x533a54c  call 0x297C080
0x533a56a  call qword ptr [0xF99FFA0]
0x533a5dd  mov word ptr [rbp+0x200],0x6F66
0x533a5e6  mov byte ptr [rbp+0x202],0x67
```
```
0x533a659  call 0x75740
0x533a65f  mov rcx,r15
0x533a662  call 0x9BC830
0x533a6bb  mov qword ptr [rsp+0x20],0
0x533a6ce  call qword ptr [0xF9A8C78]
0x533a73b  mov ecx,5
0x533a740  call 0xEEC5A00
```

## Strings Referenced (lines 4801-5365)

| RVA | Text | Site |
|-----|------|------|
| 0xF5B2BCD | (string pointer, not literal) | 0x533A53B |
| 0x6F66 | "fo" (little-endian: "of") | 0x533A5DD |
| 0x67 | "g" | 0x533A5E6 |
| 0x2E | "." | 0x533A61A, 0x533A63D |

Debug strings written to stack: "fog.", "of." (partial).

## Callees in Order (lines 4801-5365)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xE935700 | Deque push/grow | 0x5339E0C, 0x5339E46, 0x5339E86, 0x5339F5E, 0x5339F98, 0x5339FD2, 0x5339E3F (earlier), 0x5339E7F (earlier), 0x5339F57 (earlier), 0x5339F91 (earlier), 0x5339FCB (earlier), 0x5338CA5 (earlier) |
| 0xF99FFA0 | Allocator (sub_eea6040) | 0x5339EB0, 0x5339EBF, 0x5339EC6, 0x5339EF2, 0x5339F01, 0x5339F08, 0x533A002, 0x533A018, 0x533A03E, 0x533A04D, 0x533A054, 0x533A197, 0x533A1D0, 0x533A1FF, 0x533A231, 0x533A4CC, 0x533A4D2, 0x533A4DF, 0x533A4E2, 0x533A50D, 0x533A513, 0x533A516, 0x533A529, 0x533A56A, 0x533A5A0 |
| 0x3B2020 | Global cleanup | 0x5339F1E, 0x533A064, 0x5338F98 (earlier), 0x5334A50 (earlier), 0x5334FE6 (earlier), 0x533974C (earlier), 0x5339843 (earlier), 0x5339A43 (earlier), 0x5339CFB (earlier), 0x5339D02 (earlier), 0x5339DD2 (earlier) |
| 0x112CB0 | Helper | 0x5339FDE |
| 0xEEC59F0 | Helper | 0x533A197, 0x533A1FF |
| 0xEEC5A10 | Helper | 0x533A1D0, 0x533A231 |
| 0xEEC5850 | Helper | 0x533A542 |
| 0x297C080 | Helper | 0x533A54C |
| 0x9BC830 | Allocator helper | 0x533A662, 0x533A670, 0x533A681, 0x533A68F, 0x533A69D, 0x533A6A0, 0x533A6AE |
| 0x75740 | Helper | 0x533A659, 0x533A6D5, 0x533A6ED, 0x533A71D, 0x533A729, 0x533A72E, 0x533A73E, 0x533A743, 0x533A77F, 0x533A784 |
| 0x1166E0 | Helper | 0x533A6DA, 0x533A6E0, 0x533A6E7, 0x533A722, 0x533A728, 0x533A735 |
| 0x75B60 | Helper | 0x533A6E1, 0x533A6E6, 0x533A6F2, 0x533A6F8, 0x533A6FE, 0x533A704, 0x533A70A, 0x533A710, 0x533A716, 0x533A71C |
| 0xEEC5A00 | Helper | 0x533A740, 0x533A748, 0x533A757, 0x533A762, 0x533A767, 0x533A774, 0x533A779 |
| 0xF9A8C78 | Allocator vtable | 0x533A6CE |
| 0x533F580 | Handle lookup (draw record +0x63 write) | 0x53365E8, 0x5337EA2, 0x53398E3 (earlier) |
| 0x53C5CE0 | Helper | 0x533990C (earlier), 0x533888A (earlier), 0x53372FD (earlier), 0x5336EAA (earlier), 0x5336EB2 (earlier), 0x5337370 (earlier), 0x53373E5 (earlier), 0x533745A (earlier), 0x53374D0 (earlier), 0x533888A (earlier) |
| 0x53D92F0 | Helper | (earlier) |
| 0x53D96D0 | Helper | (earlier) |
| 0x533F160 | Helper | (earlier) |
| 0x533F8D0 | Helper | (earlier) |
| 0x5340B30 | Draw record handler | (earlier) |
| 0x5AC9F30 | String/log helper | (earlier) |
| 0x2FB1C0 | Helper | (earlier) |
| 0x537E150 | Render/draw call | (earlier) |
| 0xE943178 | Lock global | (earlier) |
| 0xE94319C | Unlock global | (earlier) |
| 0xE943170 | Lock (variant) | (earlier) |
| 0xE943194 | Unlock (variant) | (earlier) |
| 0x53C5F80 | Helper | (earlier) |
| 0x533BA90 | Hash/compare helper | (earlier) |

## Field Table: [reg+off] Reads/Writes (lines 4801-5365)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rbp+0x10] | 8 | R | 0x5339E14, 0x5338FB5 (earlier) | Ptr |
| [rbp+0x20] | 8 | R | 0x5339E1A, 0x5338FB9 (earlier) | Ptr |
| [rcx-8] | 8 | R | 0x5339E2A, 0x5338A15 (earlier) | Alloc header |
| [rbp+0x100] | 8 | R | 0x5339E4B, 0x5338FA3 (earlier) | Ptr |
| [rbp+0x110] | 8 | R | 0x5339E57, 0x5338FAA (earlier) | Ptr |
| [rbp-0x40] | 8 | R | 0x5339F63, 0x5338FC1 (earlier) | Ptr |
| [rbp-0x30] | 8 | R | 0x5339F6C, 0x5338FC1 (earlier) | Ptr |
| [rbp+0x60] | 8 | R | 0x5339F9D, 0x5338FA3 (earlier) | Ptr |
| [rbp+0x70] | 8 | R | 0x5339FA6, 0x5338FAA (earlier) | Ptr |
| [rbp+0x1A0] | 16 | W | 0x5339E95, 0x5338F7F (earlier) | Zero |
| [rbp+0x1B0] | 8 | W | 0x5339ED3, 0x5338F86 (earlier) | Zero |
| [rbp+0x1A8] | 8 | R | 0x5339E95, 0x53394E7 (earlier) | Ptr |
| [rsi+8] | 4 | W | 0x5339EA1, 0x5339EE3, 0x5339FF3, 0x533A02F | Refcount-- |
| [rsi] | 8 | R | 0x5339EA7, 0x5339EEC, 0x5339FF9, 0x533A035 | Vtable |
| [rsi+0xC] | 4 | W | 0x5339EB6, 0x5339EFC, 0x533A00C, 0x533A044 | Weak refcount-- |
| [rbp+0x198] | 1 | R | 0x5339F0E, 0x5338F75 (earlier) | Flag |
| [rbp+0x190] | 8 | R | 0x5339F17, 0x53394D2 (earlier) | Ptr |
| [rbp+0x90] | 8 | R | 0x5339F23, 0x5339C4C (earlier) | Ptr |
| [rbp+0xA0] | 8 | R | 0x5339F2F, 0x5339D0E (earlier) | Ptr |
| [rbp+0x120] | 8 | R | 0x5339FDE, 0x5338F63 (earlier) | Ptr |
| [rbp+0x50] | 8 | R | 0x5339FE6, 0x5338FAA (earlier) | Ptr |
| [rbp+0x48] | 16 | W | 0x5339FEE, 0x5338F7F (earlier) | Zero |
| [rbp+0x58] | 8 | W | 0x533A022, 0x5338F86 (earlier) | Zero |
| [rbp+0x40] | 1 | R | 0x533A05A, 0x5338F10 (earlier) | Flag |
| [rbp+0x38] | 8 | R | 0x533A060, 0x5338F0C (earlier) | Ptr |
| [rbp+0x260] | 16 | R | 0x533A069, 0x53348B6 (earlier) | XMM6 save |
| [rbp+0x270] | 16 | R | 0x533A070, 0x53348AF (earlier) | XMM7 save |
| [rbp+0x280] | 16 | R | 0x533A077, 0x53348A7 (earlier) | XMM8 save |
| [rbp+0x290] | 16 | R | 0x533A07F, 0x533489F (earlier) | XMM9 save |
| [rbp+0x2A0] | 16 | R | 0x533A087, 0x5334897 (earlier) | XMM10 save |
| [rbp+0x2B0] | 16 | R | 0x533A08F, 0x533488E (earlier) | XMM11 save |
| [rbp+0x2C0] | 16 | R | 0x533A097, 0x5334885 (earlier) | XMM12 save |
| [rbp+0x2D0] | 16 | R | 0x533A09F, 0x533487D (earlier) | XMM13 save |
| [rbp+0x2E0] | 16 | R | 0x533A0A7, 0x5334874 (earlier) | XMM14 save |
| [rbp+0x2F0] | 16 | R | 0x533A0AF, 0x533486B (earlier) | XMM15 save |
| [rbp+0x17C] | 4 | W | 0x533A0CB, 0x5334A55 (earlier) | Zero |
| [r14] | 1 | R | 0x533A17B, 0x533A1D9, 0x533A236, 0x533A43A, 0x533A467, 0x533A482, 0x533A590 | Byte check |
| [r12+0xDC] | 4 | R/W | 0x533A1A4/0x533A746 | Int (check/set 0x7FFFFFFE) |
| [r12+0x80] | 8 | W | 0x533A1B6 | Store [rbp+0x80] |
| [r12+0x88] | 8 | W | 0x533A1C5 | Add [rbp+0x80] |
| [r12+0x13C] | 4 | R/W | 0x533A20C/0x533A768 | Int (check/set 0x7FFFFFFE) |
| [r12+0xE0] | 8 | W | 0x533A21E | Store rdi |
| [r12+0xE8] | 8 | W | 0x533A226 | Add rdi |
| [rbp+0x248] | 8 | W | 0x533A2B4, 0x5339899 (earlier) | Loop counter |
| [rbp+0x250] | 8 | R | 0x533A2F6, 0x5337AB5 (earlier) | Context ptr |
| [rax+0x128] | 8 | R | 0x533A2FD, 0x5338FC3 (earlier) | Nested ptr |
| [rax+0x480] | 8 | R | 0x533A304, 0x5338FC3 (earlier) | Ptr |
| [rax+0x960] | 8 | R | 0x533A30B, 0x53395F3 (earlier) | Ptr |
| [rax+rcx*8+0x30] | 8 | R | 0x533A315 | Ptr |
| [rax+rcx*8+0x38] | 8 | R | 0x533A31E | Ptr |
| [rcx-0x78] | 1 | R | 0x533A390 | Byte |
| [rcx-0x50] | 1 | R | 0x533A395 | Byte |
| [rcx-0x28] | 1 | R | 0x533A3A6 | Byte |
| [rcx] | 1 | R | 0x533A3AF | Byte |
| [r12+r11*8+0x190] | 8 | W | 0x533A2ED | Accumulate |
| [r12+r11*8+0x218] | 8 | W | 0x533A44B | Accumulate |
| [rbp+0x218] | 8 | R | 0x533A453, 0x53397FC (earlier) | Ptr |
| [rbp+0x210] | 8 | R | 0x533A463, 0x53397E7 (earlier) | Ptr |
| [rdi+8] | 4 | W | 0x533A4C1, 0x533A503, 0x533A4BD (earlier) | Refcount-- |
| [rdi] | 8 | R | 0x533A4C6, 0x533A510, 0x533A4C3 (earlier) | Vtable |
| [rdi+0xC] | 4 | W | 0x533A4D2, 0x533A51C, 0x533A4C9 (earlier) | Weak refcount-- |
| [0xF5B2BCD] | 8 | R | 0x533A53B | String ptr |
| [rdi+8] | 8 | R | 0x533A54C | Ptr |
| [rdi+0x200] | 8 | R | 0x533A559 | Ptr |
| [rcx] | 8 | R | 0x533A560 | Vtable |
| [rax+0x460] | 8 | R | 0x533A563 | Vtable func |
| [rbp+0x200] | 2 | W | 0x533A5DD | "fo" |
| [rbp+0x202] | 1 | W | 0x533A5E6 | "g" |
| [r14+0x968] | 1 | R | 0x533A5ED, 0x533927D (earlier) | Byte flag |
| [r14+0x96B] | 1 | R | 0x533A5FC, 0x53392AC (earlier) | Byte flag |
| [rbp+0x203] | 1 | W | 0x533A61A, 0x533A63D | "." |
| [rbp+0x204] | 8 | R | 0x533A62D, 0x533A650 | Ptr |
| [rbp+0x28] | 8 | W | 0x533A650, 0x53392F2 (earlier) | Ptr |
| [rsp+0x20] | 8 | W | 0x533A6BB | Zero |
| [r12+0xDC] | 4 | W | 0x533A746 | 0x7FFFFFFE |
| [r12+0x13C] | 4 | W | 0x533A768 | 0x7FFFFFFE |
| **[rax+0x63]** | **1** | **R** | **0x53398EE (earlier)** | **DEPTH BYTE READ (check if 0) via 0x533F580 return** |

---

## NEXT
Complete - all 5365 lines analyzed. Run verify_oc.py.

---

## TOOL REQUESTS

- `verify_oc.py` run on docs/progress/oc_U-H1c.md to validate all quoted instruction lines against the listing
- `stores2.py` enhancement: handle stack-relative stores (rbp/rsp) more completely for this 5000+ instruction function
- `casewalk.py` for the timestamp calculation phases (0x53348E8..0x53349AD, 0x5335E3A..0x5335EFF, 0x5339816..0x5339841) - these have complex magic constant divisions
- `dumplist.py` for sub_533F580 (the handle lookup that writes draw record +0x63) - need its full listing to verify the +0x63 write mechanism
- `xref.py callers 0x533F580` to find all callers of the handle lookup function
- `ripscan.py 0x128C4FD0 0x128C5030 0x128C5038 0x128C5040 0x128C5048 0x128D2240 0x128D22A0 0x128D22A8 0x128D22B0 0x128D22B8 0x128D7360 0x128D73C0 0x128D73C8 0x128D73D0 0x128D73D8` to find all references to these global state objects