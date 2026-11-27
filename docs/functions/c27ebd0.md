# sub_c27ebd0 (0xc27ebd0, size 0x8b, 1.26.62.01)

## Signature
```cpp
void sub_c27ebd0(FrameRendererNode* node);
```
x64 Microsoft ABI: `node` in RCX. Returns void.

## Register/Argument Map
| Register | Use |
|----------|-----|
| RCX      | Input: `node` (FrameRendererNode*); recycled as recursive call arg |
| RSI      | Current node pointer (loop cursor) |
| RDI      | Previous node pointer (for type/refcount handling) |
| RBX      | RefCountBase* during refcount handling |
| RAX      | Scratch (vtable loads, type value) |
| RDX      | Constant 0x58 for sub_e935700 call |

## Reversed source (complete)

### 0xc27ebd0..0xc27ebdb: Prologue + flag check
```
0xC27EBD0  push rsi
0xC27EBD1  push rdi
0xC27EBD2  push rbx
0xC27EBD3  sub rsp,0x20
0xC27EBD7  cmp byte ptr [rcx+0x19],0
```
If `node->flag != 0`, jump to epilog and return.

### 0xc27ebdb..0xc27ebdd: Early exit jump
```
0xC27EBDB  je short 0xC27EBE5
```

### 0xc27ebdd..0xc27ebe5: Early exit epilog
```
0xC27EBDD  add rsp,0x20
0xC27EBE1  pop rbx
0xC27EBE2  pop rdi
0xC27EBE3  pop rsi
0xC27EBE4  ret
```

### 0xc27ebe5..0xc27ebea: Loop entry
```
0xC27EBE5  mov rsi,rcx
0xC27EBE8  jmp short 0xC27EC03
```

### 0xc27ebea..0xc27ebf0: Padding nop
```
0xC27EBEA  nop [rax+rax]
```

### 0xc27ebf0..0xc27ebf8: sub_e935700 call setup
```
0xC27EBF0  mov edx,0x58
0xC27EBF5  mov rcx,rdi
```

### 0xc27ebf8..0xc27ebfd: Call sub_e935700
```
0xC27EBF8  call 0xE935700
```

### 0xc27ebfd..0xc27ec01: Flag check on next node
```
0xC27EBFD  cmp byte ptr [rsi+0x19],0
```

### 0xc27ec01..0xc27ec03: Jump to epilog or continue
```
0xC27EC01  jne short 0xC27EBDD
```

### 0xc27ec03..0xc27ec06: Save prev pointer
```
0xC27EC03  mov rdi,rsi
```

### 0xc27ec06..0xc27ec0a: Load recursiveArg
```
0xC27EC06  mov rcx,[rsi+0x10]
```

### 0xc27ec0a..0xc27ec0f: Recursive self-call
```
0xC27EC0A  call 0xC27EBD0
```

### 0xc27ec0f..0xc27ec20: Advance to next node; load type; branch on type (includes nop)
```
0xC27EC0F  mov rsi,[rsi]
0xC27EC12  movzx eax,byte ptr [rdi+0x50]
0xC27EC16  cmp eax,1
0xC27EC19  jg short 0xC27EC20
0xC27EC1B  test eax,eax
0xC27EC1D  jmp short 0xC27EC25
0xC27EC1F  nop
```

### 0xc27ec20..0xc27ec25: Type 2 vs >=3 discrimination
```
0xC27EC20  cmp eax,2
0xC27EC23  jne short 0xC27EBF0
```

### 0xc27ec25..0xc27ec5b: Refcount handling + jump back
```
0xC27EC25  mov rbx,[rdi+0x48]
0xC27EC29  test rbx,rbx
0xC27EC2C  je short 0xC27EBF0
0xC27EC2E  lock dec dword ptr [rbx+8]
0xC27EC32  jne short 0xC27EBF0
0xC27EC34  mov rax,[rbx]
0xC27EC37  mov rax,[rax]
0xC27EC3A  mov rcx,rbx
0xC27EC3D  call qword ptr [0xF99FFA0]
0xC27EC43  lock dec dword ptr [rbx+c]
0xC27EC47  jne short 0xC27EBF0
0xC27EC49  mov rax,[rbx]
0xC27EC4C  mov rax,[rax+8]
0xC27EC50  mov rcx,rbx
0xC27EC53  call qword ptr [0xF99FFA0]
0xC27EC59  jmp short 0xC27EBF0
```

## Struct Fields Touched

| Struct | Offset | Size | Direction | Meaning | Tag |
|--------|--------|------|-----------|---------|-----|
| FrameRendererNode | +0x00 | 8 | R | `next` pointer | [V] |
| FrameRendererNode | +0x10 | 8 | R | `recursiveArg` pointer | [V] |
| FrameRendererNode | +0x19 | 1 | R | `flag` byte (early exit) | [V] |
| FrameRendererNode | +0x48 | 8 | R | `refCountedObject` pointer | [V] |
| FrameRendererNode | +0x50 | 1 | R | `type` byte | [V] |
| RefCountBase | +0x00 | 8 | R | `vtable` pointer | [V] |
| RefCountBase | +0x08 | 4 | RW | `strong` ref count (interlocked dec) | [V] |
| RefCountBase | +0x0C | 4 | RW | `weak` ref count (interlocked dec) | [V] |

## Callees

| RVA | Target | Class | Note |
|-----|--------|-------|------|
| 0xC27EBD0 | sub_c27ebd0 (self) | lift | Recursive call; same function |
| 0xE935700 | sub_e935700 | lift | Classified `lift` in native_boundary.tsv; forward-declared |
| 0xF99FFA0 | sub_eea6040 (via data slot) | vendor | Data slot holds sub_eea6040; called twice (vtable[0], vtable[8]) |

## Ownership / Threading
The function traverses a singly-linked list of `FrameRendererNode` objects, recursively processing each node's `recursiveArg` before moving to the next node. It performs interlocked decrement of strong/weak reference counts on `RefCountBase` objects and invokes their destructor/deallocator via a vendor thunk when counts reach zero. No locks are held across calls; the interlocked operations provide synchronization. The list is expected to be flag-terminated (node->flag != 0 ends the loop).

## Version Anchors
- Minecraft Bedrock 1.26.62.01
- RVA 0xc27ebd0, size 0x8b
- Recursive lambda in frame renderer (dragon area)

## Verification
- All 0x8b bytes covered by cited ranges above.
- Every `call` quoted verbatim in source (`#if 0` block) and dossier.
- Layout constants asserted in `sub_c27ebd0.h`.
- Registry entry via `LIFT_FN(c27ebd0, ...)` in `sub_c27ebd0.cpp`.
- Callees: self (lift), sub_e935700 (lift), sub_eea6040 (vendor boundary via data slot).