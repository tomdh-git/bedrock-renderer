## NEXT
All steps complete. Constructor at 0x5e3dd30 analyzed, 5 callers listed, RTTI at 0xF2BE100 checked (no COL pointer found). Run verify_oc.py.

## Step 1: Constructor Function Analysis (0x5e3dd30)

### Function Signature
```
sub_5e3dd30 (0x5e3dd30..0x5e3dfb6) size 0x286
Arguments: RCX=object (this), RDX=param1, R8=param2, CL=task_type (0-4)
Returns: RAX=object pointer
```

### Phase Table
| Phase | RVA Range | Description |
|-------|-----------|-------------|
| 0 | 0x5e3dd30-0x5e3dd6b | Prologue, save registers, setup stack frame, jump table dispatch on CL (0-4) |
| 1 | 0x5e3dd6d-0x5e3ddcd | Case 0 (CL=0): Thread-local init, atomic operations, calls sub_e938cb0, sub_5e3dad0, sub_e938d70 |
| 2 | 0x5e3ddd2-0x5e3de32 | Case 1 (CL=1): Initialize object with constructor pointer at +0x10, magic 0xA2436688 at +0x20, vfunc 0x11E5AA0 at +0x18, flag 1 at +0x24; alloc via sub_eea6040, call sub_103aee0, store result at [rsi] |
| 3 | 0x5e3de33-0x5e3de35 | Case 2 (CL=2): Simple return zero |
| 4 | 0x5e3de3a-0x5e3de8e | Case 3 (CL=3): Copy/swap object fields, call sub_5e3e020, sub_5e3e5e0, sub_266190 |
| 5 | 0x5e3de93-0x5e3df1b | Case 4 (CL=4): Swap all fields 0x0..0x38 between rsi and rdi |
| 6 | 0x5e3df1d-0x5e3df8f | Floating-point calculation (shared), call sub_eec73f0, sub_77d80 |
| 7 | 0x5e3df95-0x5e3dfa0 | Epilogue, return object in RAX |
| 8 | 0x5e3dfa1-0x5e3dfb1 | Error path: call sub_9bc830, retry allocation |

### Strings Referenced
- None directly in this function (strings are in caller contexts)

### Callees (in order)
1. 0xE938CB0 (sub_e938cb0) - atomic/init
2. 0x5E3DAD0 (sub_5e3dad0) - internal
3. 0xE938D70 (sub_e938d70) - atomic/init
4. 0xEEA6040 (via [0xF99FFA0], sub_eea6040) - memory allocation
5. 0x103AEE0 (sub_103aee0) - initialization
6. 0x5E3E020 (sub_5e3e020) - copy helper
7. 0x5E3E5E0 (sub_5e3e5e0) - compare helper
8. 0x266190 (sub_266190) - field operation
9. 0xEEC73F0 (sub_eec73f0) - float conversion
10. 0x77D80 (sub_77d80) - resize/realloc
11. 0x9BC830 (sub_9bc830) - error handling

### [reg+off] Stores (from stores.py)
| Offset | Size | Site (RVA) | Instruction |
|--------|------|------------|-------------|
| +0x10  | 8    | 0x5e3dddc  | mov [rsi+0x10], rax |
| +0x20  | 4    | 0x5e3dde0  | mov dword ptr [rsi+0x20], 0xA2436688 |
| +0x18  | 8    | 0x5e3ddee  | mov [rsi+0x18], rax |
| +0x24  | 1    | 0x5e3ddf2  | mov byte ptr [rsi+0x24], 1 |
| +0x0   | 8    | 0x5e3de30  | mov [rsi], rax |
| +0x0   | 4    | 0x5e3de45  | mov [rdx], eax |
| +0x0   | 4    | 0x5e3dea9  | mov [rdi], eax |
| +0x8   | 8    | 0x5e3deb3  | mov [rdi+8], rcx |
| +0x8   | 8    | 0x5e3deb7  | mov [rsi+8], rax |
| +0x10  | 8    | 0x5e3dec3  | mov [rdi+0x10], rcx |
| +0x10  | 8    | 0x5e3dec7  | mov [rsi+0x10], rax |
| +0x18  | 8    | 0x5e3ded3  | mov [rdi+0x18], rcx |
| +0x18  | 8    | 0x5e3ded7  | mov [rsi+0x18], rax |
| +0x20  | 8    | 0x5e3dee3  | mov [rdi+0x20], rcx |
| +0x20  | 8    | 0x5e3dee7  | mov [rsi+0x20], rax |
| +0x28  | 8    | 0x5e3def3  | mov [rdi+0x28], rcx |
| +0x28  | 8    | 0x5e3def7  | mov [rsi+0x28], rax |
| +0x30  | 8    | 0x5e3df03  | mov [rdi+0x30], rcx |
| +0x30  | 8    | 0x5e3df07  | mov [rsi+0x30], rax |
| +0x38  | 8    | 0x5e3df13  | mov [rdi+0x38], rcx |
| +0x38  | 8    | 0x5e3df17  | mov [rsi+0x38], rax |

**Key initialization (Case 1, CL=1):**
- `[rsi+0x10]` = address of this constructor (0x5E3DD30) - function pointer
- `[rsi+0x18]` = 0x11E5AA0 (sub_11e5aa0) - virtual function pointer
- `[rsi+0x20]` = 0xA2436688 - magic/cookie value
- `[rsi+0x24]` = 1 - flag
- `[rsi+0x0]` = result of allocation (sub_eea6040 + sub_103aee0)

### Rip-relative Reference to Vtable
`ripscan.py 0xF2BE108` reports one reference at **0x5e3df24** inside this function. However, disassembly at 0x5e3df24 shows `and eax,1` (mid-instruction). The rip-relative reference may be a false positive from the scanner, or an embedded constant in the code section. No explicit `lea rax, [0xF2BE108]` or `mov [rcx], 0xF2BE108` found in the function.

## Step 2: Five Callers of Constructor (0x5e3dd30)

From `rdis xr 0x5e3dd30`:

| # | Caller RVA | Call Site | Context | What They Pass/Do |
|---|------------|-----------|---------|-------------------|
| 1 | 0x5E3DB70 | 0x5E3DB92 | sub_5e3db70 | `lea rax, [0x5E3DD30]; mov [rcx+0x10], rax` - stores constructor ptr at object+0x10; initializes object with magic 0xA2436688 at +0x20, vfunc 0x11E5AA0 at +0x18, flag 1 at +0x24; RCX=object, RDX=param |
| 2 | 0x5E3DD30 | 0x5E3DDD5 | sub_5e3dd30 (self, Case 1) | Same initialization pattern: `lea rax, [0x5E3DD30]; mov [rsi+0x10], rax` - recursive/self-reference in case 1 |
| 3 | 0x5E41130 | 0x5E4119B | sub_5e41130 | `lea rax, [0x5E3DD30]; mov [rsi+0x10], rax` - same object init pattern; RSI=object |
| 4 | 0x639A320 | 0x639A807 | sub_639a320 | `lea rsi, [0x5E3DD30]; mov [rbp+0x480], rsi` - stores constructor ptr in stack frame at offset 0x480; builds parameter block for call to sub_24311d0 |
| 5 | 0x639CB90 | 0x639D70C | sub_639cb90 | `lea rax, [0x5E3DD30]; mov [rbp+0x4E8], rax` - stores constructor ptr in stack frame at offset 0x4E8; builds parameter block for call to sub_24314d0 |

**Pattern**: All callers load the constructor address (0x5E3DD30) and store it either at `object+0x10` (callers 1-3) or in a stack frame (callers 4-5). They do NOT call the constructor directly via `call 0x5E3DD30`. The constructor is used as a function pointer/vtable entry.

## Step 3: RTTI Check at 0xF2BE100 (8 bytes before vtable start 0xF2BE108)

### Vtable at 0xF2BE100 (`rdis vt 0xF2BE100`)
- Slot 0 (0xF2BE100): sub_66397e0 (code pointer)
- Slot 1 (0xF2BE108): sub_66397e0 (code pointer) - **this is the vtable start per ripscan**
- Slot 2 (0xF2BE110): sub_6639850
- ... all slots are code pointers in .text

### Vtable at 0xF2BE0F8 (8 bytes before 0xF2BE100)
- Slot 0 (0xF2BE0F8): sub_6622a80 (code pointer)

### Vtable at 0xF2BE1F0 (8 bytes before insert-task vtable 0xF2BE1F8)
- Slot 0 (0xF2BE1F0): sub_6610a60 (code pointer)

### Conclusion
**No MSVC RTTI Complete Object Locator (COL) pointer found at vtable-8 for any of these vtable starts.** The qword at vtable-8 is always a code pointer (first virtual function), not a pointer into .rdata with signature=1. The class does not appear to use standard MSVC RTTI, or the vtable at 0xF2BE108 is a secondary/embedded vtable without its own COL.

The insert-task vtable at 0xF2BE1F8 is a subset of the larger vtable starting at 0xF2BE108 (offset 0xF0 = 30 slots). The larger vtable appears to be the primary vtable for a class (likely `mce::framebuilder::BgfxFrameBuilder` based on string references), but it lacks the standard RTTI COL pointer at -8.

[UNVERIFIED: 0xF2BE108 question] The ripscan reference at 0x5e3df24 to 0xF2BE108 could not be verified in disassembly - the instruction at that address is `and eax,1` (mid-instruction). The reference may be a false positive or embedded data.

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5g.md`

## Quoted Instructions for Verification
0x5e3dd30  push rbp
0x5e3dd31  push rsi
0x5e3dd32  push rdi
0x5e3dd33  push rbx
0x5e3dd34  sub rsp,0x38
0x5e3dd38  lea rbp,[rsp+0x30]
0x5e3dd3d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x5e3dd45  mov rsi,r8
0x5e3dd48  cmp byte ptr [rdx+0x24],2
0x5e3dd51  cmp cl,4
0x5e3dd54  ja 0x5E3DE33
0x5e3dd5a  movzx eax,cl
0x5e3dd5d  lea rcx,[0xF281DBC]
0x5e3dd64  movsxd rax,[rcx+rax*4]
0x5e3dd68  add rax,rcx
0x5e3dd6b  jmp rax
0x5e3ddd5  lea rax,[0x5E3DD30]
0x5e3dddc  mov [rsi+0x10],rax
0x5e3dde0  mov dword ptr [rsi+0x20],0xA2436688
0x5e3dde7  lea rax,[0x11E5AA0]
0x5e3ddee  mov [rsi+0x18],rax
0x5e3ddf2  mov byte ptr [rsi+0x24],1
0x5e3de30  mov [rsi],rax
0x5e3df95  mov rax,rsi
0x5e3df98  add rsp,0x38
0x5e3df9c  pop rbx
0x5e3df9d  pop rdi
0x5e3df9e  pop rsi
0x5e3df9f  pop rbp
0x5e3dfa0  ret
0x5e3db92  lea rax,[0x5E3DD30]
0x5e3db99  mov [rcx+0x10],rax
0x5e4119b  lea rax,[0x5E3DD30]
0x5e411a2  mov [rsi+0x10],rax
0x639a807  lea rsi,[0x5E3DD30]
0x639a80e  mov [rbp+0x480],rsi
0x639d70c  lea rax,[0x5E3DD30]
0x639d713  mov [rbp+0x4E8],rax