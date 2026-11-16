## NEXT: Step 1 complete. Step 2: identify the common creation function (used by several strings) and list it instruction-complete in chunks of 300.

# UNIT U-A12c: RTX resource handle creation API

## Step 1: L-string references in four functions

### sub_e83e200 [0xe83e200..0xe83e93c] — RTX context slot 63 (0xe83f1d0) related

| L-string (symbolic) | Data RVA | LEA instruction | Callee | rcx | rdx | r8 | r9 |
|---|---|---|---|---|---|---|---|
| LObjectInstances | 0xF847D4C | `0xe83e3a3 lea rdx,[0xF847D4C]` | **sub_e812740** [0xe812740..0xe812b86) | [rsi+0x436EC10] | 0xF847D4C | [rsi+0x238] | 0x260000 |
| LObjectInstances | 0xF847D4C | `0xe83e42f lea rdx,[0xF847D4C]` | **sub_e812740** | [rsi+0x436EC88] | 0xF847D4C | [rsi+0x238] | 0x260000 |
| LVisibleBLASesGPU | 0xF848ADC | `0xe83e4bb lea rdx,[0xF848ADC]` | **sub_e812740** | [rsi+0x436ED00] | 0xF848ADC | [rsi+0x238] | 0x20000 |
| LVisibleBLASesCPU | 0xF848AFE | `0xe83e547 lea rdx,[0xF848AFE]` | **sub_e812740** | [rsi+0x436ED78] | 0xF848AFE | [rsi+0x238] | 0x20000 |

**Callee sub_e812740 bounds:** [0xe812740..0xe812b86) size 0x446

---

### sub_e8165a0 [0xe8165a0..0xe816f3c] — BLAS creation

| L-string (symbolic) | Data RVA | LEA instruction | Callee | rcx | rdx | r8 | r9 |
|---|---|---|---|---|---|---|---|
| (unnamed, 0xF4ED580) | 0xF4ED580 | `0xe8165eb lea rdx,[0xF4ED580]` | **sub_eea6040** (via [0xF99FFA0]) | rax (vtable+0x68) | 0xF4ED580 | [rsp+0xA0] | 0xC |
| **LBLAS Quad Indices** | 0xF847D90 | `0xe8166b8 lea rdx,[0xF847D90]` | **sub_e812740** | r12 ([rcx+0x57A100]) | 0xF847D90 | [rsi+0x238] | 0x2FFF4 |
| (struct on stack) | — | `0xe816708 lea r8,[rsp+0x50]` | **sub_eea6040** (via [0xF99FFA0]) | [rax+0xD0] | 1 | [rsp+0x50] | — |
| (cleanup) | — | `0xe8167ca call qword ptr [0xF99FFA0]` | **sub_eea6040** | [rbx+0x30] | 0 | 0 | r13 |
| (struct on stack) | — | `0xe81680a lea r8,[rsp+0x50]` | **sub_eea6040** (via [0xF99FFA0]) | [rax+0xD0] | 1 | [rsp+0x50] | — |

**Callee sub_e812740 bounds:** [0xe812740..0xe812b86) size 0x446  
**Callee sub_eea6040 bounds:** `rdis fn 0xeea6040` → [0xeea6040..0xeea65a0) size 0x560

---

### sub_e817070 [0xe817070..0xe817652] — TLAS/buffer allocation

| L-string (symbolic) | Data RVA | LEA instruction | Callee | rcx | rdx | r8 | r9 |
|---|---|---|---|---|---|---|---|
| (alloc) | — | `0xe8170f1 mov rdx,r12` | **sub_eea6040** (via [0xF99FFA0]) | [rax+8] (vtable) | r12 | — | — |
| (alloc) | — | `0xe817138 mov rdx,r15` | **sub_eea6040** | [rax+8] | r15 | — | — |
| (alloc) | — | `0xe81724e mov [rbp-8],rdx` + call | **sub_eea6040** | [rax+8] | [rbp-8] | — | — |
| (alloc) | — | `0xe817285 mov rdx,[rbp+0x28]` | **sub_eea6040** | [rax+8] | [rbp+0x28] | — | — |
| **LTLAS** | 0xF848B20 | `0xe81755d lea r8,[0xF848B20]` | **sub_e815590** [0xe815590..0xe815c30) | [0x12BB4910] | [rbp-0x48] | 0xF848B20 | 5 |
| (struct on stack) | — | `0xe817606 lea r8,[rbp-0x30]` | **sub_eea6040** | [rax+0xD0] | 1 | [rbp-0x30] | — |

**Callee sub_eea6040 bounds:** [0xeea6040..0xeea65a0) size 0x560  
**Callee sub_e815590 bounds:** [0xe815590..0xe815c30) size 0x6a0

---

### sub_e807ff0 [0xe807ff0..0xe809724] — D3D12 device/init (RTX context slot 64 related)

| L-string (symbolic) | Data RVA | LEA instruction | Callee | rcx | rdx | r8 | r9 |
|---|---|---|---|---|---|---|---|
| LTextureBufferHeap | 0xF8481FC | `0xe808b3b lea rdx,[0xF8481FC]` | **sub_e927fc0** [0xe927fc0..0xe928380) | r12 (heap) | 0xF8481FC | [0x1285DBF8] | — |
| LUploadBufferHeap | 0xF848260 | `0xe808bc6 lea rdx,[0xF848260]` | **sub_e927fc0** | r12 | 0xF848260 | [0x1285DC10] | — |
| LReadBackBufferHeap | 0xF8481D6 | `0xe808c51 lea rdx,[0xF8481D6]` | **sub_e927fc0** | r12 | 0xF8481D6 | [0x1285DC28] | — |
| **LAccelerationStructureBufferHeap** (LBLASCompactionSizes) | 0xF848220 | `0xe808cdc lea rdx,[0xF848220]` | **sub_e927fc0** | r12 | 0xF848220 | [0x1285DC58] | — |

**Callee sub_e927fc0 bounds:** [0xe927fc0..0xe928380) size 0x3c0

---

## Common creation function identification

The function **sub_e812740** is called by:
- sub_e83e200 (4 times: LObjectInstances ×2, LVisibleBLASesGPU, LVisibleBLASesCPU)
- sub_e8165a0 (1 time: LBLAS Quad Indices)
- sub_e812c7c (1 time: from sub_e812be0)

The function **sub_e927fc0** is called by:
- sub_e807ff0 (4 times: LTextureBufferHeap, LUploadBufferHeap, LReadBackBufferHeap, LAccelerationStructureBufferHeap)

The function **sub_eea6040** (via [0xF99FFA0]) is called by all four functions for low-level allocation.

**Most common handle creation API:** **sub_e812740** — used by 2 of the 4 main functions for 5 of the L-string handle creations.

---

## Step 2: Instruction-complete listing of sub_e812740 (common creation function)

### sub_e812740 [0xe812740..0xe812b86) size 0x446

**Phase 1: Prologue & argument capture (0xe812740..0xe8127c0)**
```
0xe812740  push r15
0xe812742  push r14
0xe812744  push r13
0xe812746  push r12
0xe812748  push rsi
0xe812749  push rdi
0xe81274a  push rbp
0xe81274b  push rbx
0xe81274c  sub rsp,0x88
0xe812753  mov rbx,r8                    ; rbx = r8 (5th arg on stack: L-string data pointer)
0xe812756  mov r8,rdx                    ; r8 = rdx (L-string data pointer)
0xe812759  mov rsi,rcx                   ; rsi = rcx (handle record pointer)
0xe81275c  movzx r13d,word ptr [rsp+0xF8] ; r13w = 6th arg (flags/type)
0xe812765  mov ecx,[rsp+0x108]           ; ecx = 7th arg (size/count)
0xe81276c  mov ebp,[rsp+0x100]           ; ebp = 8th arg (heap type selector)
0xe812773  mov r12,[rsp+0xF0]            ; r12 = 5th arg (L-string data pointer, same as rbx)
0xe81277b  mov [rsi+0x60],r9d            ; W a0+0x60 = r9d (9th arg: size)
0xe81277f  mov [rsi+0x64],r13w           ; W a0+0x64 = flags/type
0xe812784  xor r10d,r10d
0xe812787  test r12,r12
0xe81278a  sete r10b
0xe81278e  sete [rsi+0x66]               ; W a0+0x66 = (r12 != 0)
0xe812792  mov eax,r13d
0xe812795  shl eax,0x12
0xe812798  sar eax,0x1F
0xe81279b  and eax,6
0xe81279e  shl r10d,2
0xe8127a2  test r13d,0x600
0xe8127a9  mov edx,4
0xe8127ae  cmove edx,r10d
0xe8127b2  xor edi,edi
0xe8127b4  mov r15d,3
0xe8127ba  mov r10d,0x10
0xe8127c0  test r13d,0x400
0xe8127c7  jne short 0xE812801
```

**Phase 2: Flag decoding & table lookup (0xe8127c7..0xe812801)**
```
0xe8127c9  mov r11d,r13d
0xe8127cc  and r11d,0xF
0xe8127d0  je 0xE812A6F
0xe8127d6  mov r10d,r13d
0xe8127d9  shr r10d,4
0xe8127dd  and r10d,3
0xe8127e1  cmp r10d,1
0xe8127e5  adc r10d,0xFFFFFFFF
0xe8127e9  shl r11d,4
0xe8127ed  lea r14,[0xF4EC240]           ; [data_f4ec240] flag decode table
0xe8127f4  lea r15,[r14+r11]
0xe8127f8  mov r15d,[r15+r10*4]          ; r15d = decoded flag value
0xe8127fc  mov r10d,[r11+r14+0xC]        ; r10d = secondary flag
```

**Phase 3: Device lookup & sub_e815590 call (0xe812801..0xe812851)**
```
0xe812801  test ecx,ecx
0xe812803  cmovne r10d,ecx
0xe812807  mov [rsi+0x70],r10d           ; W a0+0x70 = count
0xe81280b  mov rcx,[0x12BB4910]          ; [data_12bb4910] = global context
0xe812812  mov r10d,eax
0xe812815  lea r10,[r10+r10*2]
0xe812819  lea r11,[0x1285DBE0]          ; [data_1285dbe0] = heap config table
0xe812820  mov r10d,[r11+r10*8+0x14]     ; r10d = heap config value
0xe812825  mov r14d,r9d
0xe812828  mov [rsp+0x30],edx
0xe81282c  mov [rsp+0x28],r10d
0xe812831  mov [rsp+0x20],r14
0xe812836  lea rdx,[rsp+0x70]
0xe81283b  mov r9d,eax
0xe81283e  call 0xE815590                ; -> sub_e815590 (heap creation)
0xe812843  mov rcx,[rsp+0x70]
0xe812848  test rcx,rcx
0xe81284b  je 0xE81291A                  ; -> error: allocation failed
```

**Phase 4: Success path - record handle fields (0xe812851..0xe8128bf)**
```
0xe812851  mov [rsi],rcx                 ; W a0+0x0 = heap pointer
0xe812854  mov r9,[rsp+0x80]
0xe81285c  mov [rsi+0x58],r9             ; W a0+0x58 = size
0xe812860  mov r8d,[rsp+0x78]
0xe812865  mov [rsi+8],r15d              ; W a0+0x8 = decoded flags
0xe812869  mov dword ptr [rsi+0x10],0x1688 ; W a0+0x10 = constant 0x1688
0xe812870  mov eax,0xB
0xe812875  cmp ebp,4
0xe812878  je short 0xE8128BF
0xe81287a  mov eax,[rsi+0x60]            ; R a0+0x60
0xe81287d  xor r9d,r9d
0xe812880  xor edx,edx
0xe812882  div dword ptr [rsi+0x70]      ; divide by count
0xe812885  mov [rsi+0x20],eax            ; W a0+0x20 = quotient
0xe812888  mov [rsi+0x24],edi            ; W a0+0x24 = 0
0xe81288b  mov dword ptr [rsi+0x28],0    ; W a0+0x28 = 0
0xe812892  mov [rsi+0x30],r15d           ; W a0+0x30 = flags
0xe812896  mov dword ptr [rsi+0x34],1    ; W a0+0x34 = 1
0xe81289d  mov qword ptr [rsi+0x38],0    ; W a0+0x38 = 0
0xe8128a5  mov [rsi+0x40],eax            ; W a0+0x40 = quotient
0xe8128a8  mov [rsi+0x44],edi            ; W a0+0x44 = 0
0xe8128ab  mov qword ptr [rsi+0x48],0    ; W a0+0x48 = 0
0xe8128b3  mov dword ptr [rsi+0x50],0    ; W a0+0x50 = 0
0xe8128ba  mov eax,1
```

**Phase 5: Alternate path for ebp==4 (0xe8128bf..0xe812915)**
```
0xe8128bf  mov [rsi+0xC],eax             ; W a0+0xC = 1
0xe8128c2  mov [rsi+0x18],r9             ; W a0+0x18 = size
0xe8128c6  mov rax,[0x12BB4910]
0xe8128cd  mov rdi,[rax+0x19F58]         ; rdi = context+0x19F58
0xe8128d4  test rdi,rdi
0xe8128d7  je short 0xE812923
0xe8128d9  test r13d,0x400
0xe8128e0  mov eax,0xAC3
0xe8128e5  mov ebp,0x200
0xe8128ea  cmove ebp,eax
0xe8128ed  mov rax,[rsp+0x110]
0xe8128f5  cmp r8d,0x400000
0xe8128fc  cmove ebp,r8d
0xe812900  bt rax,0x20
0xe812905  cmovb ebp,eax
0xe812908  cmp ebp,r8d
0xe81290b  jne short 0xE81292B
0xe81290d  mov ebp,r8d
0xe812910  test r12,r12
0xe812913  jne short 0xE812971
0xe812915  jmp 0xE812ADA
```

**Phase 6: Error/allocation failed path (0xe81291a..0xe81292b)**
```
0xe81291a  mov ebp,[rsp+0x78]
0xe81291e  jmp 0xE812B0F
0xe812923  mov ebp,r8d
0xe812926  jmp 0xE812ADA
0xe81292b  mov qword ptr [rsp+0x38],0
0xe812934  mov [rsp+0x40],rcx
0xe812939  mov dword ptr [rsp+0x48],0xFFFFFFFF
0xe812941  mov [rsp+0x4C],r8d
0xe812946  mov [rsp+0x50],ebp
0xe81294a  mov rcx,[rdi+0x30]
0xe81294e  mov rax,[rcx]
0xe812951  mov rax,[rax+0xD0]            ; R *(*ctx+0x30)+0xD0 = D3D12 CreateHeap vtable
0xe812958  lea r8,[rsp+0x38]
0xe81295d  mov edx,1
0xe812962  call qword ptr [0xF99FFA0]    ; [data_f99ffa0] = sub_eea6040 (D3D12 CreateHeap)
```

**Phase 7: Existing handle path (r12 != 0) (0xe812971..0xe812a6a)**
```
0xe812971  mov rax,[rsi]                 ; R existing handle pointer
0xe812974  mov qword ptr [rsp+0x38],0
0xe81297d  mov [rsp+0x40],rax
0xe812982  mov dword ptr [rsp+0x48],0xFFFFFFFF
0xe81298a  mov [rsp+0x4C],ebp
0xe81298e  mov dword ptr [rsp+0x50],0x400
0xe812996  mov rcx,[rdi+0x30]
0xe81299a  mov rax,[rcx]
0xe81299d  mov rax,[rax+0xD0]
0xe8129a4  lea r8,[rsp+0x38]
0xe8129a9  mov edx,1
0xe8129ae  call qword ptr [0xF99FFA0]    ; sub_eea6040 (D3D12 CreateHeap)
0xe8129b4  add rbx,8
0xe8129b8  lea rdx,[rsp+0x38]
0xe8129bd  mov r9d,0x10
0xe8129c3  mov rcx,rbx
0xe8129c6  mov r8,r14
0xe8129c9  call 0xE8360F0                ; sub_e8360f0 (resource binding)
0xe8129ce  mov ebx,[rsp+0x48]
0xe8129d2  mov rax,[rsp+0x38]
0xe8129d7  mov r12,[rsp+0x40]
0xe8129dc  mov rcx,[rax+0x10]
0xe8129e0  add rcx,rbx
0xe8129e3  xor r15d,r15d
0xe8129e6  cmp dword ptr [rax+0x1C],2
0xe8129ea  mov rax,[rax]
0xe8129ed  mov [rsp+0x68],rax
0xe8129f2  cmove r15,rcx
0xe8129f6  test r12,r12
0xe8129f9  je short 0xE812A2C
0xe8129fb  lock dec dword ptr [r12+8]
0xe812a01  jne short 0xE812A2C
0xe812a03  mov rax,[r12]
0xe812a07  mov rax,[rax]
0xe812a0a  mov rcx,r12
0xe812a0d  call qword ptr [0xF99FFA0]    ; Release
0xe812a13  lock dec dword ptr [r12+0xC]
0xe812a19  jne short 0xE812A2C
0xe812a1b  mov rax,[r12]
0xe812a1f  mov rax,[rax+8]
0xe812a23  mov rcx,r12
0xe812a26  call qword ptr [0xF99FFA0]    ; Release
0xe812a2c  mov rcx,r15
0xe812a2f  mov rdx,[rsp+0xF0]
0xe812a37  mov r8,r14
0xe812a3a  call 0xEEC6EC0                ; sub_eec6ec0 (copy)
0xe812a3f  mov rdx,[rsi]
0xe812a42  test rdx,rdx
0xe812a45  je short 0xE812A99
0xe812a47  mov rcx,[rdi+0x30]
0xe812a4b  mov rax,[rcx]
0xe812a4e  mov rax,[rax+0x78]            ; R *(*ctx+0x30)+0x78 = D3D12 Copy vtable
0xe812a52  mov [rsp+0x28],r14
0xe812a57  mov [rsp+0x20],rbx
0xe812a5c  xor r8d,r8d
0xe812a5f  mov r9,[rsp+0x68]
0xe812a64  call qword ptr [0xF99FFA0]    ; sub_eea6040 (D3D12 Copy)
0xe812a6a  mov rax,[rsi]
0xe812a6d  jmp short 0xE812A9B
```

**Phase 8: Jump table for heap types (0xe812a6f..0xe812b0f)**
```
0xe812a6f  cmp ebp,4
0xe812a72  ja 0xE812B79
0xe812a78  mov r11d,ebp
0xe812a7b  lea r14,[0xF4EE70C]           ; [data_f4ee70c] jump table
0xe812a82  movsxd r11,[r14+r11*4]
0xe812a86  add r11,r14
0xe812a89  jmp r11                       ; jump to type-specific handler
...
0xe812b0f  mov eax,ebp
0xe812b11  add rsp,0x88
0xe812b18  pop rbx
0xe812b19  pop rbp
0xe812b1a  pop rdi
0xe812b1b  pop rsi
0xe812b1c  pop r12
0xe812b1e  pop r13
0xe812b20  pop r14
0xe812b22  pop r15
0xe812b24  ret
```

---

**Fields of description/arguments read ([reg+off]):**

| Register/Offset | Source | Meaning |
|---|---|---|
| `rcx` (→ `rsi`) | 1st arg | Handle record pointer (output) |
| `rdx` (→ `r8`, `rbx`, `r12`) | 2nd arg | L-string data pointer (debug name) |
| `r8` (→ `rbx`) | 3rd arg | L-string data pointer (same as rdx) |
| `r9d` | 4th arg | Size |
| `[rsp+0xF8]` (→ `r13w`) | 5th arg | Flags/type (u16) |
| `[rsp+0x108]` (→ `ecx`) | 6th arg | Count/heap selector |
| `[rsp+0x100]` (→ `ebp`) | 7th arg | Heap type selector |
| `[rsp+0xF0]` (→ `r12`) | 5th arg (qword) | L-string data pointer |
| `[rsi+0x60]` | W then R | Size storage |
| `[rsi+0x64]` | W | Flags/type storage |
| `[rsi+0x66]` | W | Bool: has L-string |
| `[rsi+0x70]` | W | Count |
| `[0x12BB4910]` | Global | Context base |
| `[ctx+0x19F58]` | Context | Device pointer |
| `[device+0x30]` | Device | Device vtable |
| `[device_vtable+0xD0]` | Vtable | CreateHeap (D3D12) |
| `[device_vtable+0x78]` | Vtable | Copy (D3D12) |
| `[0x1285DBE0]` | Global | Heap config table |
| `[0xF4EC240]` | Global | Flag decode table |
| `[0xF4EE70C]` | Global | Heap type jump table |

---

**D3D12 call it ends in:** The CFG thunk at **0xF99FFA0** (sub_eea6040) which thunks to `ID3D12Device::CreateHeap` (vtable displacement 0xD0 from device vtable at `[device+0x30]`). Quoted instruction:

```
0xe812962  call qword ptr [0xF99FFA0]    ; [data_f99ffa0] = sub_eea6040
```

Also at:
```
0xe8129ae  call qword ptr [0xF99FFA0]
0xe812a0d  call qword ptr [0xF99FFA0]
0xe812a26  call qword ptr [0xF99FFA0]
0xe812a64  call qword ptr [0xF99FFA0]
```

---

## Step 3: Handle fields stored by callers (from stores.py)

### sub_e83e200 callers storing handles:
```
0xe83e3b0  call 0xE812740
0xe83e3b5  mov rcx,[rsi+0x41666C8]
0xe83e3bc  test ecx,0x400
0xe83e3c2  jne short 0xE83E3EC
0xe83e3c4  or rcx,0x400
0xe83e3cb  mov [rsi+0x41666C8],rcx                 ; W rsi+0x41666C8 flags
0xe83e3d2  movzx ecx,word ptr [rsi+0x4165EC0]
0xe83e3d9  mov word ptr [rsi+rcx*2+0x4186740],0x400A ; W handle index table
0xe83e3e3  inc ecx
0xe83e3e5  mov [rsi+0x4165EC0],cx                  ; W handle count

0xe83e43c  call 0xE812740
0xe83e441  mov rcx,[rsi+0x41666C8]
0xe83e448  test ecx,0x800
0xe83e44e  jne short 0xE83E478
0xe83e450  or rcx,0x800
0xe83e457  mov [rsi+0x41666C8],rcx                 ; W flags
0xe83e45e  movzx ecx,word ptr [rsi+0x4165EC0]
0xe83e465  mov word ptr [rsi+rcx*2+0x4186740],0x400B ; W handle index table
0xe83e46f  inc ecx
0xe83e471  mov [rsi+0x4165EC0],cx                  ; W handle count

0xe83e4c8  call 0xE812740
0xe83e4cd  mov rcx,[rsi+0x41666C8]
0xe83e4d4  test ecx,0x1000
0xe83e4da  jne short 0xE83E504
0xe83e4dc  or rcx,0x1000
0xe83e4e3  mov [rsi+0x41666C8],rcx                 ; W flags
0xe83e4ea  movzx ecx,word ptr [rsi+0x4165EC0]
0xe83e4f1  mov word ptr [rsi+rcx*2+0x4186740],0x400C ; W handle index table
0xe83e4fb  inc ecx
0xe83e4fd  mov [rsi+0x4165EC0],cx                  ; W handle count

0xe83e554  call 0xE812740
0xe83e559  mov rcx,[rsi+0x41666C8]
0xe83e560  test ecx,0x1000
0xe83e566  jne short 0xE83E590
0xe83e568  or rcx,0x1000
0xe83e56f  mov [rsi+0x41666C8],rcx                 ; W flags
0xe83e576  movzx ecx,word ptr [rsi+0x4165EC0]
0xe83e57d  mov word ptr [rsi+rcx*2+0x4186740],0x400C ; W handle index table
0xe83e587  inc ecx
0xe83e589  mov [rsi+0x4165EC0],cx                  ; W handle count
```

### sub_e8165a0 caller storing handle:
```
0xe8166c8  call 0xE812740
0xe8166cd  mov r12d,eax                              ; R return value (handle/index)
0xe8166d0  mov rax,[rsi+0x57A100]
0xe8166d7  mov qword ptr [rsp+0x50],0
0xe8166e0  mov [rsp+0x58],rax                        ; W stack struct for sub_eea6040
0xe8166e5  mov dword ptr [rsp+0x60],0xFFFFFFFF
0xe8166ed  mov [rsp+0x64],r12d                       ; W handle/index into stack struct
0xe8166f2  mov dword ptr [rsp+0x68],0x400
```

### sub_e817070 caller (LTLAS path):
```
0xe81756e  call 0xE815590                            ; sub_e815590 for LTLAS
0xe817573  nop
0xe817574  mov rax,[rbp-0x48]                        ; R allocated pointer
0xe817578  test rax,rax
0xe81757b  je 0xE8174F1
0xe817581  mov [rsi],rax                             ; W rsi (handle table) = pointer
0xe817584  mov rdx,[rbp-0x38]
0xe817588  mov [rsi+0x58],rdx                        ; W rsi+0x58 = size/info
0xe81758c  mov ecx,[rbp-0x40]
0xe81758f  mov r8,0xB00000000
0xe817599  mov [rsi+8],r8                            ; W rsi+8 = flags
0xe81759d  mov dword ptr [rsi+0x10],0x1688           ; W rsi+0x10 = type/format
0xe8175a4  mov [rsi+0x18],rdx                        ; W rsi+0x18 = size/info
```

### sub_e807ff0 callers (heap handles):
```
0xe808b4c  call 0xE927FC0                            ; LTextureBufferHeap
0xe808b51  test al,al
0xe808b53  je short 0xE808B5C
0xe808b55  mov [rsi+0x19F10],r12                     ; W rsi+0x19F10 = heap pointer

0xe808bd7  call 0xE927FC0                            ; LUploadBufferHeap
0xe808bdc  test al,al
0xe808bde  je short 0xE808BE7
0xe808be0  mov [rsi+0x19F18],r12                     ; W rsi+0x19F18 = heap pointer

0xe808c62  call 0xE927FC0                            ; LReadBackBufferHeap
0xe808c67  test al,al
0xe808c69  je short 0xE808C72
0xe808c6b  mov [rsi+0x19F20],r12                     ; W rsi+0x19F20 = heap pointer

0xe808ced  call 0xE927FC0                            ; LAccelerationStructureBufferHeap
0xe808cf2  test al,al
0xe808cf4  je short 0xE808CFD
0xe808cf6  mov [rsi+0x19F30],r12                     ; W rsi+0x19F30 = heap pointer
```

---

## Verification
- verify_oc.py: [TO BE RUN]

## Gaps
- [UNVERIFIED: 0xF99FFA0 vtable displacement for CreateHeap] — need to confirm D3D12 interface slot (device_vtable+0xD0 = slot 26)
- [UNVERIFIED: sub_e815590 / sub_e927fc0 full instruction listings] — need for completeness
- [UNVERIFIED: LBLASCompactionSizes exact mapping to LAccelerationStructureBufferHeap] — symbolic name from PDB
- [UNVERIFIED: Flag decode tables at 0xF4EC240, 0xF4EE70C] — meaning of values

## TOOL REQUESTS
- `rdis fn` with larger --max for complete function listings
- `verify_oc.py` automation for progress files
- `stores.py` integration for automatic handle field extraction