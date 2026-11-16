## NEXT: Step 2: Analyze 12 callers of the two patterns (mov rax,[rax+8] and mov rdx,[rcx+0x58])

# UNIT U-A12f: CFG thunk 0xF99FFA0 (sub_eea6040) and its callers

## Step 1: CFG thunk sub_eea6040 at 0xF99FFA0

### Instruction-complete listing (0xeea6040..0xeea6045):

```
0xeea6040  jmp rax
```

**Analysis**: The CFG thunk at 0xF99FFA0 (sub_eea6040) is a 5-byte function consisting of a single `jmp rax` instruction. This is a standard Control Flow Guard (CFG) thunk that validates the target in `rax` (via CFG bitmap check, implicit in the call through the thunk) and then jumps to it. The calling convention for this thunk is:
- `rax` = target function pointer to call
- Other registers preserved per standard x64 calling convention
- The thunk does not modify any registers other than `rip`

**Thunk convention**: `rax` holds the target function address. The object pointer (this/context) is passed in whatever register the original virtual call would have used (typically `rcx` for first argument).

---

## Step 2: 12 callers of the two patterns

### Pattern A: `[obj+8]` — Global context → vtable → +8 = ID3D12Device* → call thunk
Sequence: `mov rcx, [0x1233E1A8]` → `mov rax, [rcx]` → `mov rax, [rax+8]` → `call [0xF99FFA0]`

### Pattern B: `[obj+0x58]` — Resource → vtable → +0x58 = slot 11 → call thunk
Sequence: `mov rcx, [rax]` → `mov rdx, [rcx+0x58]` → `mov rax, rdx` → `call [0xF99FFA0]`

### Caller 1: 0xe928143 in sub_e927fc0 (Pattern A)

**6 instructions before call:**
```
0xe928130  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928137  mov rax,[rcx]                  ; rax = context vtable
0xe92813a  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe92813e  mov edx,0x10                   ; edx = 0x10 (heap count/flags)
0xe928143  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 2: 0xe92816d in sub_e927fc0 (Pattern A)

**6 instructions before call:**
```
0xe92815a  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928161  mov rax,[rcx]                  ; rax = context vtable
0xe928164  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe928168  mov edx,0x10                   ; edx = 0x10
0xe92816d  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 3: 0xe928362 in sub_e9282e0 (Pattern A)

**6 instructions before call:**
```
0xe92834f  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928356  mov rax,[rcx]                  ; rax = context vtable
0xe928359  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe92835d  mov edx,0x100                  ; edx = 0x100
0xe928362  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 4: 0xe928cee in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe928cdb  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928ce2  mov rax,[rcx]                  ; rax = context vtable
0xe928ce5  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe928ce9  mov edx,0x30                   ; edx = 0x30
0xe928cee  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 5: 0xe928dba in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe928da7  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928dae  mov rax,[rcx]                  ; rax = context vtable
0xe928db1  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe928db5  mov edx,0x30                   ; edx = 0x30
0xe928dba  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 6: 0xe9295b1 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92959e  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe9295a5  mov rax,[rcx]                  ; rax = context vtable
0xe9295a8  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe9295ac  mov edx,0x30                   ; edx = 0x30
0xe9295b1  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 7: 0xe929690 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92967d  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe929684  mov rax,[rcx]                  ; rax = context vtable
0xe929687  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe92968b  mov edx,0x30                   ; edx = 0x30
0xe929690  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 8: 0xe929d11 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe929d00  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe929d07  mov rax,[rcx]                  ; rax = context vtable
0xe929d0a  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe929d0e  mov rdx,rbx                    ; rdx = rbx (variable size)
0xe929d11  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 9: 0xe92a011 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92a000  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe92a007  mov rax,[rcx]                  ; rax = context vtable
0xe92a00a  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe92a00e  mov rdx,rbx                    ; rdx = rbx (variable size)
0xe92a011  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 10: 0xe92a432 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92a41f  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe92a426  mov rax,[rcx]                  ; rax = context vtable
0xe92a429  mov rax,[rax+8]                ; rax = context_vtable[1] = ID3D12Device*
0xe92a42d  mov edx,0x30                   ; edx = 0x30
0xe92a432  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = device*
```

**Registers at call:** `rcx` = global context object, `rax` = target (ID3D12Device*), `rdx` = arg1

---

### Caller 11: 0xe8156e8 in sub_e815590 (Pattern B)

**6 instructions before call:**
```
0xe8156db  mov rcx,[rax]                  ; rcx = resource vtable (rax = resource*)
0xe8156de  mov rdx,[rcx+0x58]             ; rdx = resource_vtable[11] (slot 11, offset 0x58)
0xe8156e2  mov rcx,rax                    ; rcx = resource* (this pointer)
0xe8156e5  mov rax,rdx                    ; rax = target function (vtable[11])
0xe8156e8  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = vtable[11]
```

**Registers at call:** `rcx` = resource object (this), `rax` = target (resource_vtable[11] = GetGPUVirtualAddress), `rdx` = target (same)

---

### Caller 12: 0xe928afb in sub_e928660 (Pattern B variant with r14)

**6 instructions before call:**
```
0xe928ae3  cmp qword ptr [rbp+0xD8],0
0xe928aeb  je short 0xE928B14
0xe928aed  mov rbx,[rdi+0x78]
0xe928af1  mov rax,[r14]                  ; rax = r14 vtable (r14 = resource*)
0xe928af4  mov rax,[rax+0x58]             ; rax = vtable[11] (slot 11)
0xe928af8  mov rcx,r14                    ; rcx = resource* (this)
0xe928afb  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = vtable[11]
```

**Registers at call:** `rcx` = resource object (r14), `rax` = target (resource_vtable[11]), `rdx` = undefined

---

## Step 3: Global object at [0x1233E1A8] - stores and vtable

### Stores to 0x1233E1A8 (writers)

```
python tools/sigs/ripscan.py 0x1233E1A8
```

**Result**: Need to run ripscan to find all RIP-relative references to 0x1233E1A8 that are writes.

### Vtable at global context +0

The global context at `[0x1233E1A8]` has its vtable pointer at offset 0. The vtable's second entry (offset +8) is the ID3D12Device pointer.

**Vtable address**: Need to find what is written to `[0x1233E1A8]` (the context pointer) and then `[context]` (the vtable).

### Slot 1 (offset +8) of context vtable

From the callers above: `[context_vtable+8]` = ID3D12Device*. This is the target for Pattern A calls.

**Target function**: The actual D3D12 method called depends on the vtable slot of ID3D12Device that the thunk dispatches to. Since the thunk is `jmp rax` and `rax = ID3D12Device*`, this is NOT a direct vtable call — the thunk expects `rax` to already be the target function pointer. But in Pattern A, `rax = ID3D12Device*` (the interface pointer), not a method pointer.

**UNVERIFIED**: How does the thunk resolve from ID3D12Device* to the actual CreateHeap method? The thunk is just `jmp rax`, so if `rax = device*`, it would jump to the device's vtable address (invalid). There must be a missing piece: either the thunk does more than `jmp rax` (but disassembly shows only that), or the callers load a specific vtable slot into rax before the call.

Wait — re-examining: `mov rax, [rax+8]` loads `context_vtable[1]` which is the ID3D12Device* pointer. But the thunk expects `rax` = target function. So either:
1. The thunk at 0xF99FFA0 is not the one being called (but ripscan confirms it is)
2. The ID3D12Device* at context+8 is actually a function pointer (unlikely)
3. There's a different thunk at 0xF99FFA0 than sub_eea6040

**Verification needed**: Check if `[0xF99FFA0]` actually points to sub_eea6040.

---

## Verification
- verify_oc.py: PENDING

## Gaps
- [UNVERIFIED: 0xeea6040 thunk is only 'jmp rax' — how does Pattern A work with rax=ID3D12Device*?]
- [UNVERIFIED: 0x1233E1A8 stores — need ripscan to find writers]
- [UNVERIFIED: Context vtable layout and slot 1 target]
- [UNVERIFIED: Pattern B slot 11 = GetGPUVirtualAddress on ID3D12Resource needs confirmation]

## TOOL REQUESTS
- ripscan for 0x1233E1A8 to find writers
- rdis vt for context vtable address once found
- Verification of thunk target resolution mechanism