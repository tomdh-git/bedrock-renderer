## NEXT
Last analysed: L_4fde750.txt (0x4FDE750). All 9 functions complete.

---

# Unit U-I5f: cohtml backend callees of the Ore UI glue function 0x52D26A0

Functions analysed in order from oc_U-I5b.md callee table:
1. 0xA0233E0 — sub_a0233e0 (Cohtml element creation #1)
2. 0xA0228E0 — sub_a0228e0 (Cohtml draw call setup)
3. 0xA01BDD0 — sub_a01bdd0 (Cohtml texture upload)
4. 0xA018300 — sub_a018300 (Cohtml view creation)
5. 0xA0264A0 — sub_a0264a0 (Cohtml layout/measure)
6. 0x1F383F0 — sub_1f383f0 (Draw command encoding)
7. 0x1F38E40 — sub_1f38e40 (Resource cleanup)
8. 0x1F39A30 — sub_1f39a30 (Texture handle lookup)
9. 0x4FDE750 — sub_4fde750 (Cohtml callback registration)

---

## 1. 0xA0233E0 — sub_a0233e0 (Cohtml element creation #1)

**Listing**: docs/listings/L_a0233e0.txt (56 lines, verified)

### (a) Role guess [I]
Initialises a Cohtml element object (rcx) with vtable 0xF3CAA10, then for each of three input pointers (rdx, r8, r9 = arguments 2–4) reads the object at `[ptr+0x38]`, calls its virtual function at `[[ptr+0x38]+0]` via thunk 0xF99FFA0, and stores the result into the element at offsets +0x40, +0x80, +0xC0. Returns the element pointer in rax.
Key instructions:
```
0xa0233fd  lea rax,[0xF3CAA10]
0xa023404  mov [rcx],rax
0xa023417  mov rcx,[rdx+0x38]
0xa02342e  call qword ptr [0xF99FFA0]
0xa023439  mov [r8+0x40],rax
0xa023450  mov rcx,[rdi+0x38]
0xa023463  call qword ptr [0xF99FFA0]
0xa02346e  mov [r8+0x80],rax
0xa023480  mov rcx,[rsi+0x38]
0xa02349a  call qword ptr [0xF99FFA0]
0xa0234a5  mov [r8+0xC0],rax
```

### (b) Strings referenced
None.

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0xF99FFA0 | virtual thunk | 0xA02342E | CFG virtual call (thrice: for rdx, rdi, rsi) |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Element (rcx, arg1) | rcx | +0x0 | 8 | W | 0xA023404 | `mov [rcx], rax` | VTable = 0xF3CAA10 |
| Element | rcx | +0x40 | 8 | W | 0xA023414 | `mov qword ptr [rcx+0x40], 0` | Zero init |
| Element | rcx | +0x40 | 8 | W | 0xA023439 | `mov [r8+0x40], rax` | Result from 1st virtual call (rdx+0x38) |
| Element | rcx | +0x48 | 8 | W | 0xA023441 | `lea rax, [r8+0x48]` (addr stored to stack) | Pointer to +0x48 field |
| Element | rcx | +0x80 | 8 | W | 0xA023445 | `mov qword ptr [r8+0x80], 0` | Zero init |
| Element | rcx | +0x80 | 8 | W | 0xA02346E | `mov [r8+0x80], rax` | Result from 2nd virtual call (rdi+0x38) |
| Element | rcx | +0xC0 | 8 | W | 0xA023475 | `mov qword ptr [r8+0xC0], 0` | Zero init |
| Element | rcx | +0xC0 | 8 | W | 0xA0234A5 | `mov [r8+0xC0], rax` | Result from 3rd virtual call (rsi+0x38) |
| Input 2 (rdx) | rdx | +0x38 | 8 | R | 0xA023415 | `mov rcx, [rdx+0x38]` | Child object pointer |
| Input 3 (r8→rdi) | rdi | +0x38 | 8 | R | 0xA02344F | `mov rcx, [rdi+0x38]` | Child object pointer |
| Input 4 (r9→rsi) | rsi | +0x38 | 8 | R | 0xA023480 | `mov rcx, [rsi+0x38]` | Child object pointer |
| Return value | rax | — | 8 | W | 0xA0234AC | `mov rax, r8` | Returns element pointer |

---

## 2. 0xA0228E0 — sub_a0228e0 (Cohtml draw call setup)

**Listing**: docs/listings/L_a0228e0.txt (188 lines, verified)

### (a) Role guess [I]
Sets up a Cohtml draw call record (rdi = arg1) by stealing pointers from three source objects (rdx, r8, r9 = args 2–4), initialising refcounted string/buffer fields at +0x8, +0x18, +0x20, +0x30, then conditionally (if r9≠0) calling 0x9BF300 to acquire a resource, followed by a long sequence of refcount increments/decrements and virtual calls via 0xF99FFA0 on multiple nested objects (at +0x10, +0x28, etc.) to build the draw command. Returns the draw call record pointer in rax.
Key instructions:
```
0xa022900  mov rax,[rdx]
0xa02290a  mov [rcx],rax
0xa022910  movups [rcx+8],xmm0
0xa022914  mov rax,[r8]
0xa02291e  mov [rcx+0x18],rax
0xa022922  movups [rcx+0x20],xmm0
0xa022926  mov qword ptr [rcx+0x30],0
0xa022995  call 0x9BF300
0xa0229af  call qword ptr [0xF99FFA0]
0xa0229cf  call qword ptr [0xF99FFA0]
... (many more virtual calls and refcount ops)
```

### (b) Strings referenced
None directly (string data may be in objects passed in).

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0x9BF300 | direct | 0xA022995 | Resource acquisition / lock |
| 2 | 0xF99FFA0 | virtual thunk | 0xA0229AF | CFG virtual call (many sites) |
| 3 | 0xE935700 | direct | (not in this listing; called by virtual thunks) | Vector/string dealloc |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Draw call (rcx→rdi) | rcx | +0x0 | 8 | W | 0xA02290A | `mov [rcx], rax` | Copy pointer from rdx |
| Draw call | rcx | +0x8 | 16 | W | 0xA022910 | `movups [rcx+8], xmm0` | Zero init refcounted field |
| Draw call | rcx | +0x18 | 8 | W | 0xA02291E | `mov [rcx+0x18], rax` | Copy pointer from r8 |
| Draw call | rcx | +0x20 | 16 | W | 0xA022922 | `movups [rcx+20], xmm0` | Zero init |
| Draw call | rcx | +0x30 | 8 | W | 0xA02292E | `mov qword ptr [rcx+0x30], 0` | Zero init |
| Source 1 (rdx) | rdx | +0x0 | 8 | R | 0xA022900 | `mov rax, [rdx]` | Read pointer |
| Source 1 | rdx | +0x0 | 8 | W | 0xA022903 | `mov qword ptr [rdx], 0` | Null out |
| Source 2 (r8) | r8 | +0x0 | 8 | R | 0xA022914 | `mov rax, [r8]` | Read pointer |
| Source 2 | r8 | +0x0 | 8 | W | 0xA022917 | `mov qword ptr [r8], 0` | Null out |
| Source 3 (r9) | r9 | +0x8 | 8 | R | 0xA022972 | `mov rcx, [r9+8]` | Read nested object |
| Draw call | rdi | +0x10 | 8 | R | 0xA0229E6 | `mov rcx, [rdi+0x10]` | Refcounted object |
| Draw call | rdi | +0x10 | 8 | R/W (atomic) | 0xA022A07 | `lock cmpxchg [rcx+8], edx` | Inc refcount |
| Draw call | rdi | +0x28 | 8 | R | 0xA022AA0 | `mov rcx, [rbp+0x28]` | Another refcounted object |
| Draw call | rdi | +0x28 | 8 | R/W (atomic) | 0xA022AB7 | `lock cmpxchg [rcx+8], edx` | Inc refcount |
| Return value | rax | — | 8 | W | 0xA022B76 | `mov rax, rdi` | Returns draw call pointer |

---

## 3. 0xA01BDD0 — sub_a01bdd0 (Cohtml texture upload)

**Listing**: docs/listings/L_a01bdd0.txt (94 lines, verified)

### (a) Role guess [I]
Initialises a large texture upload record (rcx = arg1, size ~0x410 bytes) by zeroing all fields (xmm0 stores at +0x0..+0x3F0, byte stores at +0x40, +0xF0, +0x100…+0x360), setting up two callback pointers at +0x3C8 and +0x3E0 via calls to 0xA01C030 with indices 0x1EA and 0x1EB, and storing the second argument (rdx) at +0x400. Returns the record pointer in rax.
Key instructions:
```
0xa01bde9  movups [rcx+0x30],xmm0
0xa01bdf1  movups [rcx+0x10],xmm0
0xa01bdf5  movups [rcx],xmm0
0xa01bdf8  mov byte ptr [rcx+0x40],0
0xa01bdfc  mov byte ptr [rcx+0xF0],0
... (zero bytes at +0xF0, +0x100, ..., +0x360)
0xa01bf3e  movups [rcx+0xD8],xmm0
... (zero xmm at +0xC8, +0xB8, +0xA8, +0x98, +0x88, +0x78, +0x68, +0x58, +0x48)
0xa01bf78  lea r9,[rcx+0x3D0]
0xa01bf86  mov [rbp-0x10],rax
0xa01bfbd  mov [rbp-0x18],r9
0xa01bfda  mov r9,[rbp-0x10]
0xa01bfb5  mov rcx,rdx
0xa01bfaa  mov qword ptr [rcx+0x400],0
```

### (b) Strings referenced
None.

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0xA01C030 | direct | 0xA01BFC1 | Callback setup (index 0x1EA) |
| 2 | 0xA01C030 | direct | 0xA01BFDE | Callback setup (index 0x1EB) |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Texture record (rcx) | rcx | +0x0 | 16 | W | 0xA01BDF8 | `movups [rcx], xmm0` | Zero init |
| Texture record | rcx | +0x10 | 16 | W | 0xA01BDF1 | `movups [rcx+0x10], xmm0` | Zero init |
| Texture record | rcx | +0x20 | 16 | W | 0xA01BDE9 | `movups [rcx+0x20], xmm0` | Zero init |
| Texture record | rcx | +0x30 | 16 | W | 0xA01BDE9 | `movups [rcx+0x30], xmm0` | Zero init |
| Texture record | rcx | +0x40 | 1 | W | 0xA01BDFC | `mov byte ptr [rcx+0x40], 0` | Flag |
| Texture record | rcx | +0xF0 | 1 | W | 0xA01BE03 | `mov byte ptr [rcx+0xF0], 0` | Flag |
| Texture record | rcx | +0x100..0x360 | 1 each | W | 0xA01BE0A.. | `mov byte ptr [rcx+...], 0` | Flag array (0x10-step) |
| Texture record | rcx | +0xD8 | 16 | W | 0xA01BF3E | `movups [rcx+0xD8], xmm0` | Zero init |
| Texture record | rcx | +0xC8 | 16 | W | 0xA01BF45 | `movups [rcx+0xC8], xmm0` | Zero init |
| Texture record | rcx | +0xB8 | 16 | W | 0xA01BF4C | `movups [rcx+0xB8], xmm0` | Zero init |
| Texture record | rcx | +0xA8 | 16 | W | 0xA01BF53 | `movups [rcx+0xA8], xmm0` | Zero init |
| Texture record | rcx | +0x98 | 16 | W | 0xA01BF5A | `movups [rcx+0x98], xmm0` | Zero init |
| Texture record | rcx | +0x88 | 16 | W | 0xA01BF61 | `movups [rcx+0x88], xmm0` | Zero init |
| Texture record | rcx | +0x78 | 16 | W | 0xA01BF68 | `movups [rcx+0x78], xmm0` | Zero init |
| Texture record | rcx | +0x68 | 16 | W | 0xA01BF6C | `movups [rcx+0x68], xmm0` | Zero init |
| Texture record | rcx | +0x58 | 16 | W | 0xA01BF70 | `movups [rcx+0x58], xmm0` | Zero init |
| Texture record | rcx | +0x48 | 16 | W | 0xA01BF74 | `movups [rcx+0x48], xmm0` | Zero init |
| Texture record | rcx | +0x3D0 | 16 | W | 0xA01BF9F | `movups [rcx+0x3D0], xmm0` | Zero init callback slot |
| Texture record | rcx | +0x3E0 | 16 | W | 0xA01BF98 | `movups [rcx+0x3E0], xmm0` | Zero init callback slot |
| Texture record | rcx | +0x3F0 | 16 | W | 0xA01BF91 | `movups [rcx+0x3F0], xmm0` | Zero init callback slot |
| Texture record | rcx | +0x3C8 | 8 | W | 0xA01BFC1 (via 0xA01C030) | callback 0x1EA | Setup via external call |
| Texture record | rcx | +0x3E0 | 8 | W | 0xA01BFDE (via 0xA01C030) | callback 0x1EB | Setup via external call |
| Texture record | rcx | +0x400 | 8 | W | 0xA01BFAA | `mov qword ptr [rcx+0x400], 0` | Zero init |
| Arg2 (rdx) | rdx | — | 8 | W | 0xA01BFB5 | `mov rcx, rdx` then store at +0x400 | Userdata pointer |
| Return value | rax | — | 8 | W | 0xA01BFE4 | `mov rax, [rbp-8]` | Returns record pointer |

---

## 4. 0xA018300 — sub_a018300 (Cohtml view creation)

**Listing**: docs/listings/L_a018300.txt (62 lines, verified)

### (a) Role guess [I]
Creates a Cohtml view object (rbx = arg1) by allocating a 0x18-byte block via allocator 0x1233E1A8 (thunk 0xF99FFA0), initialising it with vtable 0xEFCC490 and refcount=0x100000001, then setting up the view object at rbx with vtable 0xF3CA970, user pointer (rsi=arg2) at +0x18, and calling 0xA0260E0 and 0x24AF560 for further initialisation. On allocation failure, jumps to error handler at 0xA0183F1 which calls 0x9BC830 (alloc) and retries. Returns the view pointer in rax.
Key instructions:
```
0xa01831b  lea rax,[0xEFCC480]
0xa018322  mov [rcx],rax
0xa018325  mov rcx,[0x1233E1A8]
0xa018333  mov edx,0x18
0xa018338  call qword ptr [0xF99FFA0]   ; allocate 0x18 bytes
0xa018347  mov rcx,0x100000001
0xa018351  mov [rax+8],rcx
0xa018355  lea rcx,[0xEFCC490]
0xa01835c  mov [rax],rcx
0xa018366  mov byte ptr [rax+0x10],1
0xa01836a  mov [rbx+8],rcx
0xa01836e  mov [rbx+0x10],rax
0xa018372  lea rax,[0xF3CA970]
0xa018379  mov [rbx],rax
0xa01837c  mov [rbx+0x18],rsi
0xa018397  mov [rbp-0x10],rbx
0xa0183b8  call 0x24AF560
```

### (b) Strings referenced
None.

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0xF99FFA0 | virtual thunk | 0xA018338 | Allocator (guarded paged array) via context 0x1233E1A8 |
| 2 | 0x9BC830 | direct | 0xA0183F6 | Fallback allocator (error path) |
| 3 | 0xA0260E0 | direct | 0xA018397 | View initialisation helper |
| 4 | 0x24AF560 | direct | 0xA0183B8 | View initialisation helper |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| View (rbx=arg1) | rbx | +0x0 | 8 | W | 0xA018379 | `mov [rbx], rax` | VTable = 0xF3CA970 |
| View | rbx | +0x8 | 8 | W | 0xA01836A | `mov [rbx+8], rcx` | Pointer to allocated block (+0x10) |
| View | rbx | +0x10 | 8 | W | 0xA01836E | `mov [rbx+0x10], rax` | Allocated block pointer |
| View | rbx | +0x18 | 8 | W | 0xA01837C | `mov [rbx+0x18], rsi` | User pointer (arg2) |
| Allocated block (rax) | rax | +0x0 | 8 | W | 0xA01835C | `mov [rax], rcx` | VTable = 0xEFCC490 |
| Allocated block | rax | +0x8 | 8 | W | 0xA018351 | `mov [rax+8], rcx` | Refcount = 0x100000001 |
| Allocated block | rax | +0x10 | 1 | W | 0xA018366 | `mov byte ptr [rax+0x10], 1` | Initialised flag |
| Allocator context | rcx (from 0x1233E1A8) | +0x0 | 8 | R | 0xA01832C | `mov rcx, [0x1233E1A8]` | Read allocator |
| Allocator vfunc | rax | +0x8 | 8 | R | 0xA01832F | `mov rax, [rax+8]` | Read alloc vfunc |
| Return value | rax | — | 8 | W | 0xA0183C5 | `mov rax, [rbp-0x10]` | Returns view pointer (rbx) |

---

## 5. 0xA0264A0 — sub_a0264a0 (Cohtml layout/measure)

**Listing**: docs/listings/L_a0264a0.txt (99 lines, verified)

### (a) Role guess [I]
Initialises a layout/measure object (rsi = arg1) by copying a dword from arg2 (rdx) to +0x0, zeroing +0x8..+0x28, allocating a 0x30-byte node via allocator 0x1233E1A8 (thunk 0xF99FFA0) and linking it into a circular list at +0x8 (self-referential), then allocating a 0x80-byte buffer via same allocator, growing it if needed (realloc logic at 0xA02655C–0xA026581 calling 0xE935700), initialising the buffer with the node pointer, setting float 1.0 (0x3F800000) at +0x0, and constants 7, 8 at +0x30, +0x38. Returns the layout object pointer in rax.
Key instructions:
```
0xa0264bc  mov eax,[rdx]
0xa0264be  mov [rcx],eax
0xa0264c3  movups [rcx+8],xmm6
0xa0264d5  mov edx,0x30
0xa0264da  call qword ptr [0xF99FFA0]   ; alloc 0x30 node
0xa0264f4  mov [rdi],rdi
0xa0264f7  mov [rdi+8],rdi
0xa0264fb  mov [rsi+8],rdi
0xa026537  mov edx,0x80
0xa02653c  call qword ptr [0xF99FFA0]   ; alloc 0x80 buffer
0xa02655c  cmp rdx,0x1000
0xa026586  mov [rsi+0x18],rbx
0xa026523  mov dword ptr [rsi],0x3F800000
0xa026513  mov qword ptr [rsi+0x30],7
0xa02651b  mov qword ptr [rsi+0x38],8
```

### (b) Strings referenced
None.

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0xF99FFA0 | virtual thunk | 0xA0264DA | Allocator (guarded paged array) via 0x1233E1A8 (size 0x30) |
| 2 | 0xF99FFA0 | virtual thunk | 0xA02653C | Allocator (size 0x80) |
| 3 | 0xE935700 | direct | 0xA026581 | Vector/string dealloc (realloc path) |
| 4 | 0x9BC830 | direct | 0xA0265ED | Fallback allocator (error path, size 0x30) |
| 5 | 0x9BC830 | direct | 0xA0265FC | Fallback allocator (error path, size 0x80) |
| 6 | 0xF9A8C78 | virtual thunk | 0xA02661A | Exception handler (error path) |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Layout (rsi=arg1) | rsi | +0x0 | 4 | W | 0xA0264BE | `mov [rcx], eax` | Flags/dword from arg2 |
| Layout | rsi | +0x8 | 16 | W | 0xA0264C3 | `movups [rcx+8], xmm6` | Zero init (list head + next) |
| Layout | rsi | +0x8 | 8 | W | 0xA0264FB | `mov [rsi+8], rdi` | List head = new node |
| Layout | rsi | +0x18 | 8 | W | 0xA02650B | `movups [rsi+0x18], xmm6` | Zero init buffer ptr/size |
| Layout | rsi | +0x28 | 8 | W | 0xA026513 | `mov qword ptr [rsi+0x28], 0` | Zero init |
| Layout | rsi | +0x30 | 8 | W | 0xA026513 | `mov qword ptr [rsi+0x30], 7` | Constant 7 |
| Layout | rsi | +0x38 | 8 | W | 0xA02651B | `mov qword ptr [rsi+0x38], 8` | Constant 8 |
| Layout | rsi | +0x0 | 4 | W | 0xA026523 | `mov dword ptr [rsi], 0x3F800000` | Float 1.0 |
| Layout | rsi | +0x18 | 8 | W | 0xA026586 | `mov [rsi+0x18], rbx` | Buffer pointer |
| Layout | rsi | +0x20 | 8 | W | 0xA026591 | `mov [rsi+0x20], rax` | Buffer start |
| Layout | rsi | +0x28 | 8 | W | 0xA026595 | `mov [rsi+0x28], rax` | Buffer current |
| Allocated node (rdi) | rdi | +0x0 | 8 | W | 0xA0264F4 | `mov [rdi], rdi` | Self-pointer (circular) |
| Allocated node | rdi | +0x8 | 8 | W | 0xA0264F7 | `mov [rdi+8], rdi` | Self-pointer |
| Allocated buffer (rbx) | rbx | +0x0..0x78 | 8 each | W | 0xA02659C.. | `mov [rbx+...], rdi` | Fill buffer with node ptr |
| Allocator context | rcx (from 0x1233E1A8) | +0x0 | 8 | R | 0xA0264C7 | `mov rcx, [0x1233E1A8]` | Read allocator |
| Allocator vfunc | rax | +0x8 | 8 | R | 0xA0264D1 | `mov rax, [rax+8]` | Read alloc vfunc |
| Return value | rax | — | 8 | W | 0xA0265D8 | `mov rax, rsi` | Returns layout pointer |

---

## 6. 0x1F383F0 — sub_1f383f0 (Draw command encoding)

**Listing**: docs/listings/L_1f383f0.txt (488 lines, verified)

### (a) Role guess [I]
Encodes a draw command into a command buffer (rcx = arg1) by capturing 7 pointer arguments from stack (r9, r8, r10, r11, and [rbp+0xF0], [rbp+0xF8], [rbp+0x108]), initialising refcounted fields at +0x8, +0x10, +0x18, +0x30, +0x38, +0x40, then if the object at +0x30 has a non-zero tag byte, iterates a chain via +0x8/+0x238 to find a matching entry (hash at 0xD2ACA77479857640), extracts a byte at [match+0x14] into the command at +0x63, then makes a second virtual call (0x185) on the same object, repeats the chain walk, and finally cleans up all captured refcounts (lock dec at +8/+0xC, virtual dtor via 0xF99FFA0). Returns the command buffer pointer in rax.
Key instructions:
```
0x1f38423  mov [rcx],dl
0x1f38428  mov qword ptr [r9],0
0x1f3842f  mov [rcx+8],rax
0x1f38436  mov qword ptr [r8],0
0x1f3843d  mov [rcx+0x10],rax
0x1f38444  mov qword ptr [r10],0
0x1f3844b  mov [rcx+0x18],rax
0x1f38453  xorps xmm0,xmm0
0x1f3845a  mov rax,[r11+8]
0x1f38463  lock inc dword ptr [rax+8]
0x1f38472  mov [rcx+0x30],rdx
0x1f38476  mov [rcx+0x38],rax
0x1f3855f  lea rdi,[rbp+0x90]
0x1f3856c  mov r8d,0x187
0x1f38572  call qword ptr [0xF99FFA0]   ; virtual 0x187
0x1f38823  mov r11,[r8+0x40]
0x1f38833  mov r10,0xD2ACA77479857640
0x1f3883d  and r10,r11
0x1f3887c  movzx edx,byte ptr [rdx+0x14]
0x1f38880  mov [rcx],dl

0x1f387d8  lea rdi,[rbp+0x90]
0x1f387e5  mov r8d,0x185
0x1f387eb  call qword ptr [0xF99FFA0]   ; virtual 0x185
```

### (b) Strings referenced
None.

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0xF99FFA0 | virtual thunk | 0x1F38463 | Refcount increment (on r11+8 object) |
| 2 | 0xF99FFA0 | virtual thunk | 0x1F384BE | Refcount increment (on r8+8 object) |
| 3 | 0xF99FFA0 | virtual thunk | 0x1F38572 | Virtual call 0x187 (on rsi) |
| 4 | 0xF99FFA0 | virtual thunk | 0x1F38612 | Virtual dtor (on acquired object) |
| 5 | 0xF99FFA0 | virtual thunk | 0x1F38636 | Virtual call (on stack guard) |
| 6 | 0xF99FFA0 | virtual thunk | 0x1F3869D | Virtual dtor (on rdi) |
| 7 | 0xF99FFA0 | virtual thunk | 0x1F38706 | Virtual dtor (on rbx+0x70) |
| 8 | 0xF99FFA0 | virtual thunk | 0x1F38771 | Virtual dtor (on rdi) |
| 9 | 0xF99FFA0 | virtual thunk | 0x1F387C8 | Virtual dtor (on rbp+0x88) |
| 10 | 0xF99FFA0 | virtual thunk | 0x1F387EB | Virtual call 0x185 (on rsi) |
| 11 | 0xF99FFA0 | virtual thunk | 0x1F388DB | Virtual dtor (on acquired object) |
| 12 | 0xF99FFA0 | virtual thunk | 0x1F388FF | Virtual call (on stack guard) |
| 13 | 0xF99FFA0 | virtual thunk | 0x1F3896A | Virtual dtor (on rsi) |
| 14 | 0xF99FFA0 | virtual thunk | 0x1F389D9 | Virtual dtor (on rbx+0x88) |
| 15 | 0xF99FFA0 | virtual thunk | 0x1F38A41 | Virtual dtor (on rdi) |
| 16 | 0xF99FFA0 | virtual thunk | 0x1F38A98 | Virtual dtor (on rbp+0x88) |
| 17 | 0xA022CD0 | direct | 0x1F38AD1 | Cleanup helper (on rbp+0x60 object) |
| 18 | 0xE935700 | direct | 0x1F38ADB | Vector/string dealloc (size 0x38) |
| 19 | 0x1F5D340 | direct | 0x1F38AF5 | Cleanup helper (on rbp+0xF0 object) |
| 20 | 0xE935700 | direct | 0x1F38B02 | Vector/string dealloc (size 0x408) |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Command buffer (rcx) | rcx | +0x0 | 1 | W | 0x1F38423 | `mov [rcx], dl` | Tag byte (arg1 low byte) |
| Command buffer | rcx | +0x8 | 8 | W | 0x1F3842F | `mov [rcx+8], rax` | Pointer from r9 |
| Command buffer | rcx | +0x10 | 8 | W | 0x1F3843D | `mov [rcx+0x10], rax` | Pointer from r8 |
| Command buffer | rcx | +0x18 | 8 | W | 0x1F3844B | `mov [rcx+0x18], rax` | Pointer from r10 |
| Command buffer | rcx | +0x20 | 16 | W | 0x1F3844F | `movups [rcx+0x20], xmm0` | Zero init |
| Command buffer | rcx | +0x30 | 8 | W | 0x1F38472 | `mov [rcx+0x30], rdx` | Pointer from r11 (object) |
| Command buffer | rcx | +0x38 | 8 | W | 0x1F38476 | `mov [rcx+0x38], rax` | Refcounted ptr from r11+8 |
| Command buffer | rcx | +0x40 | 8 | W | 0x1F3847E | `mov [rcx+0x40], rax` | Pointer from r11+0x10 |
| Source r9 | r9 | +0x0 | 8 | R | 0x1F38428 | `mov rax, [r9]` | Read pointer |
| Source r9 | r9 | +0x0 | 8 | W | 0x1F3842B | `mov qword ptr [r9], 0` | Null out |
| Source r8 | r8 | +0x0 | 8 | R | 0x1F38436 | `mov rax, [r8]` | Read pointer |
| Source r8 | r8 | +0x0 | 8 | W | 0x1F38439 | `mov qword ptr [r8], 0` | Null out |
| Source r10 | r10 | +0x0 | 8 | R | 0x1F38444 | `mov rax, [r10]` | Read pointer |
| Source r10 | r10 | +0x0 | 8 | W | 0x1F38447 | `mov qword ptr [r10], 0` | Null out |
| Source r11 | r11 | +0x8 | 8 | R | 0x1F3845A | `mov rax, [r11+8]` | Read refcounted ptr |
| Source r11 | r11 | +0x8 | 8 | R/W (atomic) | 0x1F38463 | `lock inc dword ptr [rax+8]` | Inc refcount |
| Source r11 | r11 | +0x0 | 8 | R | 0x1F38471 | `mov rdx, [r11]` | Read object ptr |
| Source r8 (arg5) | r8 | +0x8 | 8 | R | 0x1F384B8 | `mov rdx, [r8+8]` | Read refcounted ptr |
| Source r8 | r8 | +0x8 | 8 | R/W (atomic) | 0x1F384BE | `lock inc dword ptr [rdx+8]` | Inc refcount |
| Command buffer | rcx | +0x48 | 16 | W | 0x1F384B1 | `movups [rcx+0x48], xmm0` | Zero init |
| Command buffer | rcx | +0x60 | 2 | W | 0x1F384F9 | `mov word ptr [rcx+0x60], 0` | Zero init |
| Command buffer | rcx | +0x62 | 1 | W | 0x1F384FF | `mov [rcx+0x62], al` | Byte from stack arg |
| Command buffer | rcx | +0x63 | 1 | W | 0x1F38502 | `mov byte ptr [rcx+0x63], 0` | Zero init |
| Command buffer | rcx | +0x63 | 1 | W | 0x1F385B7 | `mov [rcx], dl` | Tag from chain walk |
| Command buffer | rcx | +0x63 | 1 | W | 0x1F38883 | `mov [rcx], dl` | Tag from second chain walk |
| Command buffer | rcx | +0x68 | 16 | W | 0x1F38524 | `movups [rcx+0x68], xmm0` | Zero init |
| Command buffer | rcx | +0x78 | 1 | W | 0x1F3852C | `mov byte ptr [rcx+0x78], 0` | Zero init |
| Command buffer | rcx | +0x80 | 16 | W | 0x1F3852C | `movups [rcx+0x80], xmm0` | Zero init |
| Command buffer | rcx | +0x90 | 16 | W | 0x1F38533 | `movups [rcx+0x90], xmm0` | Zero init |
| Command buffer | rcx | +0xA0 | 8 | W | 0x1F3853A | `mov qword ptr [rcx+0xA0], 0` | Zero init |
| Object at +0x30 | rdx (from r11) | +0x0 | 1 | R | 0x1F3848B | `cmp byte ptr [rdx], 0` | Check tag |
| Object at +0x30 | rdx | +0x8 | 8 | R | 0x1F385A3 | `mov r8, [r8+8]` | Chain walk next |
| Object at +0x30 | rdx | +0x238 | 8 | R | 0x1F385A7 | `mov r8, [r8+0x238]` | Chain walk hash bucket |
| Object at +0x30 | rdx | +0x10 | 1 | R | 0x1F385B3 | `movzx edx, byte ptr [rdx+0x10]` | Extract tag |
| Object at +0x30 | rdx | +0x14 | 1 | R | 0x1F38880 | `movzx edx, byte ptr [rdx+0x14]` | Extract tag (2nd walk) |
| Stack guard (rbp-0x50) | rbp-0x50 | +0x0 | 8 | W | 0x1F385C0 | `mov [rbp-0x50], rdx` | Guard object |
| Stack guard | rbp-0x50 | +0x8 | 8 | W | 0x1F385C4 | `mov [rbp-0x48], rcx` | Guard ptr |
| Return value | rax | — | 8 | W | 0x1F38B7D | `mov rax, rbx` | Returns command buffer (rbx = original rcx) |

---

## 7. 0x1F38E40 — sub_1f38e40 (Resource cleanup)

**Listing**: docs/listings/L_1f38e40.txt (242 lines, verified)

### (a) Role guess [I]
Cleans up a resource container (rsi = rcx = arg1) by releasing all refcounted pointers stored at offsets +0x98, +0x88, +0x70, +0x50, +0x38, +0x18, +0x10. For each non-null pointer: lock dec refcount at +8, if zero call virtual dtor via 0xF99FFA0; lock dec at +0xC, if zero call virtual dtor via 0xF99FFA0. Also calls 0x1F5D340 and 0xE935700 on +0x18 object, and 0xA022CD0 and 0xE935700 on +0x8 object. Zeroes the pair fields at each offset. Returns void.
Key instructions:
```
0x1f38e5a  mov rdi,[rcx+0x98]
0x1f38e6d  lock dec dword ptr [rdi+8]
0x1f38e7c  call qword ptr [0xF99FFA0]
0x1f38e86  jne short 0x1F38E98
0x1f38e92  call qword ptr [0xF99FFA0]
... (repeated for +0x88, +0x70, +0x50, +0x38)
0x1f39147  mov rcx,rdi
0x1f3914a  call 0x1F5D340
0x1f39154  mov rcx,rdi
0x1f39165  mov rax,[rcx]
0x1f39170  call qword ptr [0xF99FFA0]
0x1f3917f  mov rcx,rsi
0x1f39182  call 0xA022CD0
0x1f3918c  mov rcx,rsi
```

### (b) Strings referenced
None.

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0xF99FFA0 | virtual thunk | 0x1F38E7C | Virtual dtor (on +0x98 object) |
| 2 | 0xF99FFA0 | virtual thunk | 0x1F38E92 | Virtual dtor (on +0x98 object, 2nd ref) |
| 3 | 0xF99FFA0 | virtual thunk | 0x1F38EB8 | Virtual dtor (on +0x88 object) |
| 4 | 0xF99FFA0 | virtual thunk | 0x1F38ECE | Virtual dtor (on +0x88 object, 2nd ref) |
| 5 | 0xF99FFA0 | virtual thunk | 0x1F38F3B | Virtual dtor (on +0x70 object) |
| 6 | 0xF99FFA0 | virtual thunk | 0x1F38F51 | Virtual dtor (on +0x70 object, 2nd ref) |
| 7 | 0xF99FFA0 | virtual thunk | 0x1F38F8F | Virtual dtor (on +0x50 object) |
| 8 | 0xF99FFA0 | virtual thunk | 0x1F38FA5 | Virtual dtor (on +0x50 object, 2nd ref) |
| 9 | 0xF99FFA0 | virtual thunk | 0x1F39004 | Virtual dtor (on +0x38 object) |
| 10 | 0xF99FFA0 | virtual thunk | 0x1F3901A | Virtual dtor (on +0x38 object, 2nd ref) |
| 11 | 0xF99FFA0 | virtual thunk | 0x1F3905B | Virtual dtor (on +0x50 object again) |
| 12 | 0xF99FFA0 | virtual thunk | 0x1F39071 | Virtual dtor (on +0x50 object, 2nd ref) |
| 13 | 0xF99FFA0 | virtual thunk | 0x1F390DC | Virtual dtor (on +0x38 object again) |
| 14 | 0xF99FFA0 | virtual thunk | 0x1F390F2 | Virtual dtor (on +0x38 object, 2nd ref) |
| 15 | 0x1F5D340 | direct | 0x1F3914A | Cleanup helper (on +0x18 object) |
| 16 | 0xE935700 | direct | 0x1F39154 | Vector/string dealloc (size 0x408, on +0x18) |
| 17 | 0xF99FFA0 | virtual thunk | 0x1F39170 | Virtual dtor (on +0x10 object) |
| 18 | 0xA022CD0 | direct | 0x1F39182 | Cleanup helper (on +0x8 object) |
| 19 | 0xE935700 | direct | 0x1F3918F | Vector/string dealloc (size 0x38, on +0x8) |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Container (rsi=arg1) | rsi | +0x98 | 8 | R | 0x1F38E5A | `mov rdi, [rcx+0x98]` | Read refcounted ptr |
| Container | rsi | +0x90 | 16 | W | 0x1F38E61 | `movups [rcx+0x90], xmm0` | Zero pair |
| Container | rsi | +0x98 | 8 | W | 0x1F38E9F | `mov qword ptr [rsi+0xA0], 0` | Zero size |
| Container | rsi | +0x88 | 8 | R | 0x1F38EF5 | `mov rcx, [rsi+0x88]` | Read refcounted ptr |
| Container | rsi | +0x80 | 16 | W | 0x1F38F0E | `movaps [rbp-0x20], xmm0` then store | Zero pair (via stack) |
| Container | rsi | +0x88 | 8 | W | 0x1F38F7D | `mov qword ptr [rcx+0xA0], 0` | Zero size |
| Container | rsi | +0x70 | 8 | R | 0x1F38F9C | `mov rcx, [rsi+0x70]` | Read refcounted ptr |
| Container | rsi | +0x68 | 16 | W | 0x1F38FBE | `movups [rsi+0x68], xmm0` | Zero pair |
| Container | rsi | +0x70 | 8 | W | 0x1F38F82 | `lock dec dword ptr [rcx+0xC]` | Dec refcount |
| Container | rsi | +0x50 | 8 | R | 0x1F39029 | `mov rdi, [rsi+0x50]` | Read refcounted ptr |
| Container | rsi | +0x48 | 16 | W | 0x1F39043 | `movups [rsi+0x48], xmm0` | Zero pair |
| Container | rsi | +0x50 | 8 | W | 0x1F3907B | `mov qword ptr [rsi+0x58], 0` | Zero size |
| Container | rsi | +0x38 | 8 | R | 0x1F390C4 | `mov rdi, [rsi+0x38]` | Read refcounted ptr |
| Container | rsi | +0x30 | 16 | W | 0x1F390E0 | `movups [rsi+0x30], xmm0` | Zero pair |
| Container | rsi | +0x38 | 8 | W | 0x1F390FC | `mov qword ptr [rsi+0x40], 0` | Zero size |
| Container | rsi | +0x18 | 8 | R | 0x1F3913E | `mov rdi, [rsi+0x18]` | Read refcounted ptr |
| Container | rsi | +0x18 | 8 | R/W | 0x1F3914A | `call 0x1F5D340` | Cleanup helper |
| Container | rsi | +0x18 | 8 | R/W | 0x1F39154 | `call 0xE935700` | Dealloc (size 0x408) |
| Container | rsi | +0x10 | 8 | R | 0x1F3915F | `mov rax, [rsi+0x10]` | Read ptr |
| Container | rsi | +0x10 | 8 | R | 0x1F39165 | `mov rax, [rcx]` | Read for dtor |
| Container | rsi | +0x8 | 8 | R | 0x1F39176 | `mov rsi, [rsi+8]` | Read refcounted ptr |
| Container | rsi | +0x8 | 8 | R/W | 0x1F3917F | `call 0xA022CD0` | Cleanup helper |
| Container | rsi | +0x8 | 8 | R/W | 0x1F39187 | `call 0xE935700` | Dealloc (size 0x38) |
| Return value | — | — | — | — | — | — | void (no return) |

---

## 8. 0x1F39A30 — sub_1f39a30 (Texture handle lookup)

**Listing**: docs/listings/L_1f39a30.txt (110 lines, verified)

### (a) Role guess [I]
Swaps the texture handle in a texture record (rdi = rcx = arg1) with a new handle from arg2 (rsi). Releases the old handle at +0x98 (lock dec refcounts at +8/+0xC, virtual dtor via 0xF99FFA0), then if arg2 is non-null, increments refcount on its +0x10 sub-object, stores arg2's +0x8 at +0x90 and arg2 at +0x98. Also updates a nested object at +0x18 (rbx) by clearing +0x3F0, releasing its +0x3F8 handle, and installing arg2's +0x10 sub-object at +0x3F8 (with refcount inc). Returns the old +0x90 value in rax.
Key instructions:
```
0x1f39a40  mov rbx,[rcx+0x98]
0x1f39a47  movups [rcx+0x90],xmm0
0x1f39a53  lock dec dword ptr [rbx+8]
0x1f39a62  call qword ptr [0xF99FFA0]
0x1f39a68  lock dec dword ptr [rbx+0xC]
0x1f39a75  mov rcx,rbx
0x1f39a8e  mov rax,[rsi+0x10]
0x1f39a97  lock inc dword ptr [rax+8]
0x1f39aa7  mov [rdi+0x90],rax
0x1f39aae  mov rbx,[rdi+0x98]
0x1f39b0e  mov rdi,[rbx+0x3F8]
0x1f39b15  mov qword ptr [rbx+0x3F8],0
0x1f39b25  lock dec dword ptr [rdi+8]
0x1f39b34  call qword ptr [0xF99FFA0]
0x1f39b69  lock inc dword ptr [rax+8]
0x1f39b80  mov rdi,[rbx+0x3F8]
0x1f39b87  mov [rbx+0x3F8],rcx
```

### (b) Strings referenced
None.

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0xF99FFA0 | virtual thunk | 0x1F39A62 | Virtual dtor (on old +0x98 handle) |
| 2 | 0xF99FFA0 | virtual thunk | 0x1F39A75 | Virtual dtor (on old +0x98 handle, 2nd ref) |
| 3 | 0xF99FFA0 | virtual thunk | 0x1F39ACD | Virtual dtor (on old +0x3F8 handle) |
| 4 | 0xF99FFA0 | virtual thunk | 0x1F39B34 | Virtual dtor (on old +0x3F8 handle, 2nd ref) |
| 5 | 0xF99FFA0 | virtual thunk | 0x1F39B9F | Virtual dtor (on old +0x3F8 handle again) |
| 6 | 0xF99FFA0 | virtual thunk | 0x1F39BA8 | Virtual dtor (on old +0x3F8 handle, 2nd ref) |
| 7 | 0xF99FFA0 | virtual thunk | 0x1F39B70 | Virtual dtor (on +0x10 object) |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Texture record (rdi=arg1) | rdi | +0x98 | 8 | R | 0x1F39A40 | `mov rbx, [rcx+0x98]` | Old handle |
| Texture record | rdi | +0x90 | 16 | W | 0x1F39A47 | `movups [rcx+0x90], xmm0` | Zero pair |
| Texture record | rdi | +0x90 | 8 | W | 0x1F39AA7 | `mov [rdi+0x90], rax` | New handle's +0x8 |
| Texture record | rdi | +0x98 | 8 | W | 0x1F39AAE | `mov [rdi+0x98], rcx` | New handle (arg2) |
| Texture record | rdi | +0x18 | 8 | R | 0x1F39A3D | `mov rbx, [rcx+0x18]` | Nested object |
| Texture record | rdi | +0xA0 | 8 | W | 0x1F39AF8 | `mov [rdi+0xA0], rsi` | Store arg2 |
| Nested object (rbx) | rbx | +0x3F0 | 8 | W | 0x1F39B0E | `mov qword ptr [rbx+0x3F0], 0` | Zero |
| Nested object | rbx | +0x3F8 | 8 | R | 0x1F39B0E | `mov rdi, [rbx+0x3F8]` | Old nested handle |
| Nested object | rbx | +0x3F8 | 8 | W | 0x1F39B15 | `mov qword ptr [rbx+0x3F8], 0` | Zero |
| Nested object | rbx | +0x3F0 | 8 | W | 0x1F39B80 | `mov [rbx+0x3F0], rax` | New nested handle's +0x8 |
| Nested object | rbx | +0x3F8 | 8 | W | 0x1F39B87 | `mov [rbx+0x3F8], rcx` | New nested handle |
| Arg2 (rsi) | rsi | +0x10 | 8 | R | 0x1F39A8E | `mov rax, [rsi+0x10]` | Sub-object |
| Arg2 | rsi | +0x10 | 8 | R/W (atomic) | 0x1F39A97 | `lock inc dword ptr [rax+8]` | Inc refcount |
| Arg2 | rsi | +0x8 | 8 | R | 0x1F39AA3 | `mov rax, [rsi+8]` | Pointer |
| Old handle (rbx) | rbx | +0x8 | 4 | R/W (atomic) | 0x1F39A53 | `lock dec dword ptr [rbx+8]` | Dec refcount |
| Old handle | rbx | +0xC | 4 | R/W (atomic) | 0x1F39A68 | `lock dec dword ptr [rbx+0xC]` | Dec 2nd refcount |
| Old nested handle | rdi | +0x8 | 4 | R/W (atomic) | 0x1F39B25 | `lock dec dword ptr [rdi+8]` | Dec refcount |
| Old nested handle | rdi | +0xC | 4 | R/W (atomic) | 0x1F39B3A | `lock dec dword ptr [rdi+0xC]` | Dec 2nd refcount |
| Return value | rax | — | 8 | W | 0x1F39AA3 | `mov rax, [rsi+8]` | Returns old +0x90 value |

---

## 9. 0x4FDE750 — sub_4fde750 (Cohtml callback registration)

**Listing**: docs/listings/L_4fde750.txt (55 lines, verified)

### (a) Role guess [I]
Registers or clears Cohtml callbacks on an object (rsi = rcx = arg1). If byte at +0x138 == 1, calls 0x75C10 on sub-object at +0x120. Then if the string/buffer at +0x20 has length >= 0x10 (at +0x38), deallocates its backing storage via 0xE935700 (with grow logic). Resets the string at +0x20 to empty (SSO: length 0 at +0x30, capacity 0xF at +0x38, null terminator at +0x20). Does the same for string at +0x0 (length at +0x10, capacity at +0x18, data at +0x0). Returns void.
Key instructions:
```
0x4fde758  cmp byte ptr [rcx+0x138],1
0x4fde75f  jne short 0x4FDE76D
0x4fde761  lea rcx,[rsi+0x120]
0x4fde768  call 0x75C10
0x4fde76d  mov rax,[rsi+0x38]
0x4fde771  cmp rax,0x10
0x4fde777  jb short 0x4FDE7A8
0x4fde777  mov rcx,[rsi+0x20]
0x4fde7a3  call 0xE935700
0x4fde7a8  mov qword ptr [rsi+0x30],0
0x4fde7b0  mov qword ptr [rsi+0x38],0xF
0x4fde7b8  mov byte ptr [rsi+0x20],0
0x4fde7bc  mov rax,[rsi+0x18]
0x4fde7c0  cmp rax,0x10
0x4fde7f6  mov qword ptr [rsi+0x10],0
0x4fde7fe  mov qword ptr [rsi+0x18],0xF
0x4fde806  mov byte ptr [rsi],0
```

### (b) Strings referenced
None (operates on SSO string buffers inside the object).

### (c) Callees in order
| Order | Callee RVA | Via | First call site | What |
|-------|------------|-----|-----------------|------|
| 1 | 0x75C10 | direct | 0x4FDE768 | Callback unregister / cleanup |
| 2 | 0xE935700 | direct | 0x4FDE7A3 | Vector/string dealloc (for +0x20 string) |
| 3 | 0xE935700 | direct | 0x4FDE7F1 | Vector/string dealloc (for +0x0 string) |
| 4 | 0xF9A8C78 | virtual thunk | 0x4FDE822 | Exception handler (error path) |

### (d) [reg+off] reads/writes into argument objects & return
| Target object | Base reg | Offset | Size | R/W | First site RVA | Instruction | Meaning |
|---------------|----------|--------|------|-----|----------------|-------------|---------|
| Callback object (rsi=arg1) | rsi | +0x138 | 1 | R | 0x4FDE758 | `cmp byte ptr [rcx+0x138], 1` | Flag check |
| Callback object | rsi | +0x120 | 8 | R | 0x4FDE761 | `lea rcx, [rsi+0x120]` | Sub-object for 0x75C10 |
| Callback object | rsi | +0x38 | 8 | R | 0x4FDE770 | `mov rax, [rsi+0x38]` | String capacity |
| Callback object | rsi | +0x20 | 8 | R | 0x4FDE777 | `mov rcx, [rsi+0x20]` | String data pointer |
| Callback object | rsi | +0x30 | 8 | W | 0x4FDE7A8 | `mov qword ptr [rsi+0x30], 0` | String length = 0 |
| Callback object | rsi | +0x38 | 8 | W | 0x4FDE7B0 | `mov qword ptr [rsi+0x38], 0xF` | String capacity = 15 (SSO) |
| Callback object | rsi | +0x20 | 1 | W | 0x4FDE7B8 | `mov byte ptr [rsi+0x20], 0` | Null terminator |
| Callback object | rsi | +0x18 | 8 | R | 0x4FDE7C0 | `mov rax, [rsi+0x18]` | 2nd string capacity |
| Callback object | rsi | +0x0 | 8 | R | 0x4FDE7C6 | `mov rcx, [rsi]` | 2nd string data pointer |
| Callback object | rsi | +0x10 | 8 | W | 0x4FDE7F6 | `mov qword ptr [rsi+0x10], 0` | 2nd string length = 0 |
| Callback object | rsi | +0x18 | 8 | W | 0x4FDE7FE | `mov qword ptr [rsi+0x18], 0xF` | 2nd string capacity = 15 |
| Callback object | rsi | +0x0 | 1 | W | 0x4FDE806 | `mov byte ptr [rsi], 0` | 2nd string null terminator |
| Return value | — | — | — | — | — | — | void (no return) |

---

## TOOL REQUESTS

| Name | Input → Output | Why it would have helped |
|------|----------------|--------------------------|
| `batch_listing_analyser.py` | Dir of listing files → combined JSON with phases, stores, callees, strings | Would automate the repetitive extraction of (a)/(b)/(c)/(d) across 9 files; did by hand with read+grep. |
| `verify_offset_consistency.py` | Progress MD → cross-checks same offset across functions | Would catch if +0x38 means different things in different callees; manual comparison error-prone. |
| `callee_graph.py` | Callee tables → DOT/mermaid graph | Visualising the call chain from 0x52D26A0 through these 9 callees would clarify architecture; drew mentally. |

None of the above are critical; the manual process worked but was time-consuming.