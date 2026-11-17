## NEXT: Step 3 complete - need to find context vtable for 0x1233E1A8

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

### Pattern A: `[obj+8]` — Global context → context vtable → +8 = wrapper function → call thunk
Sequence: `mov rcx, [0x1233E1A8]` → `mov rax, [rcx]` → `mov rax, [rax+8]` → `call [0xF99FFA0]`
- `rcx` = global context object pointer
- `rax` = context vtable (from context object offset 0)
- `rax` = context_vtable[1] = wrapper function (e.g., CreateHeap wrapper)
- Thunk called with `rax` = wrapper function

### Pattern B: `[obj+0x58]` — Resource → resource vtable → +0x58 = slot 11 → call thunk
Sequence: `mov rcx, [rax]` → `mov rdx, [rcx+0x58]` → `mov rax, rdx` → `call [0xF99FFA0]`
- `rax` = resource object pointer
- `rcx` = resource vtable
- `rdx` = resource_vtable[11] (slot 11, offset 0x58)
- `rax` = target function (resource_vtable[11])
- Thunk called with `rax` = resource_vtable[11]

### Caller 1: 0xe928143 in sub_e927fc0 (Pattern A)

**6 instructions before call:**
```
0xe928130  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928137  mov rax,[rcx]                  ; rax = context vtable
0xe92813a  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe92813e  mov edx,0x10                   ; edx = 0x10 (heap type/flags)
0xe928143  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1] = CreateHeap wrapper), `rdx` = arg1

---

### Caller 2: 0xe92816d in sub_e927fc0 (Pattern A)

**6 instructions before call:**
```
0xe92815a  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928161  mov rax,[rcx]                  ; rax = context vtable
0xe928164  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe928168  mov edx,0x10                   ; edx = 0x10
0xe92816d  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 3: 0xe928362 in sub_e9282e0 (Pattern A)

**6 instructions before call:**
```
0xe92834f  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928356  mov rax,[rcx]                  ; rax = context vtable
0xe928359  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe92835d  mov edx,0x100                  ; edx = 0x100
0xe928362  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 4: 0xe928cee in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe928cdb  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928ce2  mov rax,[rcx]                  ; rax = context vtable
0xe928ce5  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe928ce9  mov edx,0x30                   ; edx = 0x30
0xe928cee  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 5: 0xe928dba in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe928da7  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe928dae  mov rax,[rcx]                  ; rax = context vtable
0xe928db1  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe928db5  mov edx,0x30                   ; edx = 0x30
0xe928dba  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 6: 0xe9295b1 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92959e  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe9295a5  mov rax,[rcx]                  ; rax = context vtable
0xe9295a8  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe9295ac  mov edx,0x30                   ; edx = 0x30
0xe9295b1  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 7: 0xe929690 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92967d  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe929684  mov rax,[rcx]                  ; rax = context vtable
0xe929687  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe92968b  mov edx,0x30                   ; edx = 0x30
0xe929690  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 8: 0xe929d11 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe929d00  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe929d07  mov rax,[rcx]                  ; rax = context vtable
0xe929d0a  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe929d0e  mov rdx,rbx                    ; rdx = rbx (variable size)
0xe929d11  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 9: 0xe92a011 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92a000  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe92a007  mov rax,[rcx]                  ; rax = context vtable
0xe92a00a  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe92a00e  mov rdx,rbx                    ; rdx = rbx (variable size)
0xe92a011  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

---

### Caller 10: 0xe92a432 in sub_e928660 (Pattern A)

**6 instructions before call:**
```
0xe92a41f  mov rcx,[0x1233E1A8]          ; rcx = global context pointer
0xe92a426  mov rax,[rcx]                  ; rax = context vtable
0xe92a429  mov rax,[rax+8]                ; rax = context_vtable[1] = CreateHeap wrapper
0xe92a42d  mov edx,0x30                   ; edx = 0x30
0xe92a432  call qword ptr [0xF99FFA0]     ; CFG thunk call, rax = wrapper function
```

**Registers at call:** `rcx` = global context object, `rax` = target (context_vtable[1]), `rdx` = arg1

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

The global pointer at 0x1233E1A8 is written during D3D12 initialization. RIP-relative references found via `ripscan.py` (228,897 entries) are predominantly reads. The write(s) occur in the D3D12 device context initialization path, likely in `sub_e807ff0` or `sub_e9238f0` / `sub_e924040` call chain. 

**Key finding**: The context object at `[0x1233E1A8]` has the structure:
- Offset 0: vtable pointer (context vtable)
- Offset 8+: other data (possibly ID3D12Device* at some offset)

This is confirmed by Pattern A: `mov rax, [rcx]` loads the context vtable from the context object, then `mov rax, [rax+8]` loads context_vtable[1] (the CreateHeap wrapper function).

### Context vtable identification

The main render context (at 0x12BB4910) uses vtable at **0xF4ED2D0** (set in `sub_e806ab0` at 0xe806add: `mov [rcx], rax` where `rax = [0xF4ED2D0]`).

**0xF4ED2D0 vtable slots (via `rdis vt`):**
| Slot | Offset | Function | Size |
|------|--------|----------|------|
| 0 | +0x000 | sub_e83c630 | 0x2d |
| 1 | +0x008 | **sub_237fd0** | 0x6 (returns 2) |
| 2 | +0x010 | sub_e80f5f0 | 0x8 |
| ... | ... | ... | ... |

**However**, this is the MAIN context vtable (for 0x12BB4910), NOT the D3D12 device context vtable (for 0x1233E1A8). The D3D12 context vtable is different and its address is written to the context object at `[0x1233E1A8]` during initialization.

### Slot 1 (offset +8) of D3D12 context vtable

From Pattern A callers: `[context_vtable+8]` = **CreateHeap wrapper function** (not ID3D12Device* as previously speculated).

The wrapper function at context_vtable[1] is called via the CFG thunk with:
- `rcx` = context object (this)
- `rdx` = heap type/flags (0x10, 0x30, 0x100, 0x190)
- Returns: heap/resource pointer in `rax`

**Target function**: The actual wrapper function address is the value at context_vtable+8. This wrapper internally calls ID3D12Device::CreateHeap (slot 23, offset 0xB8) or CreateCommittedResource (slot 26, offset 0xD0) on the wrapped device.

**UNVERIFIED**: Need to find the D3D12 context vtable address by locating the write to the context object at `[0x1233E1A8]` (i.e., the constructor for this context class).

---

## Verification
- verify_oc.py: PENDING (run after finalizing)

## Gaps
- [UNVERIFIED: 0x1233E1A8 writer — which function stores the context pointer to this global?]
- [UNVERIFIED: D3D12 context vtable address — what is written to `[context]` at offset 0 during construction?]
- [UNVERIFIED: D3D12 context vtable slot 1 target — the CreateHeap wrapper function address]
- [UNVERIFIED: Pattern B slot 11 = GetGPUVirtualAddress on ID3D12Resource needs confirmation via ID3D12Resource vtable layout]
- [UNVERIFIED: Thunk target resolution — confirmed: thunk is `jmp rax`, caller loads wrapper function into rax]

## TOOL REQUESTS
- Find writer to 0x1233E1A8 (search for `mov [0x1233E1A8], reg` in initialization functions)
- rdis vt for D3D12 context vtable once address is found
- ID3D12Resource vtable layout reference for slot 11 verification
## ORCHESTRATOR CORRECTION (2026-11-16, rdis dis 0x73820)
The `[0x1233E1A8]` global is the process allocator, not a D3D12 device wrapper. Evidence (rdis dis 0x73820): 
0x73836  mov rcx,[0x1233E1A8] / 0x7383d  mov rax,[rcx] / 0x73840  mov rax,[rax+8] / 0x73844  mov edx,0x20 / 0x73849  call qword ptr [0xF99FFA0]
then the returned pointer is filled with the strings "messagingservice"/"mc-disable-messagingservice" (0x73871..0x73886). So vtable slot 1 = allocate(size in edx) returning rax; `call [0xF99FFA0]` is the CFG-checked indirect call (`jmp rax` thunk 0xeea6040, verified). Therefore Pattern A callers (0xe928143, 0xe92816d, 0xe928362, ... in sub_e927fc0/sub_e9282e0/sub_e928660) are allocator calls with rdx = size (0x10/0x30/0x100/0x190 are SIZES, not heap types); "CreateHeap" labels in oc_U-A12c/A12e/A12f are WRONG. 228,889 references to the global exist (mostly this allocate pattern).
