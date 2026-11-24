# BgfxFrameBuilder::endFrame helper sub_bc55ea0 (0xbc55ea0, size 0x105)

## Signature guess
`extern "C" void sub_bc55ea0(Slot* a /*rcx*/, Slot* b /*rdx*/)` → void.
x64 Microsoft ABI: rcx = first arg (Slot* a), rdx = second arg (Slot* b).

## Register/argument map
- rcx = a (Slot*), rdx = b (Slot*) on entry
- rdi = b (copied from rdx at 0xbc55ea9)
- rsi = temp RefCounted* (slot a's ref, re-acquired)
- rbx = temp RefCounted* (slot b's ref / released old)
- r14 = temp void* (slot a's raw)
- rax = scratch (loaded refs, vtable entries)

## Phases (each instruction of [0xbc55ea0, 0xbc55fa5) is inside one cited range)

### 0xbc55ea0..0xbc55ebf  — acquire slot a's ref, slot b's ref
```
bc55ea0  push r14
bc55ea2  push rsi
bc55ea3  push rdi
bc55ea4  push rbx
bc55ea5  sub rsp,0x28
bc55ea9  mov rdi,rdx                      ; rdi = b
bc55eac  mov rax,[rcx+8]                  ; rax = a->ref
bc55eb0  test rax,rax
bc55eb3  je short 0xBC55EBF               ; if a->ref == 0 skip addref
bc55eb5  lock inc dword ptr [rax+8]       ; a->ref->strong++
bc55eb9  mov rsi,[rcx+8]                  ; rsi = a->ref
bc55ebd  jmp short 0xBC55EC1

loc_bc55ebf:
bc55ebf  xor esi,esi                      ; rsi = 0

loc_bc55ec1:
bc55ec1  mov r14,[rcx]                    ; r14 = a->raw
bc55ec4  mov rax,[rdi+8]                  ; rax = b->ref
bc55ec8  test rax,rax
bc55ecb  je short 0xBC55EDB               ; if b->ref == 0 skip
bc55ecd  lock inc dword ptr [rax+8]       ; b->ref->strong++
bc55ed1  mov rax,[rdi+8]
bc55ed5  mov rbx,[rcx+8]                  ; rbx = a->ref (oldA)
bc55ed9  jmp short 0xBC55EE0

loc_bc55edb:
bc55edb  xor eax,eax                      ; rax = 0
bc55edd  mov rbx,rsi                      ; rbx = a->ref (may be 0)

loc_bc55ee0:
```

### 0xbc55ee0..0xbc55eea  — copy slot b into slot a
```
bc55ee0  mov rdx,[rdi]                    ; rdx = b->raw
bc55ee3  mov [rcx],rdx                    ; a->raw = b->raw
bc55ee6  mov [rcx+8],rax                  ; a->ref = b->ref (rax = b->ref or 0)
bc55eea  test rbx,rbx                     ; rbx = oldA
bc55eed  je short 0xBC55F1A               ; if oldA == 0 skip release
```

### 0xbc55eea..0xbc55ef3  — release oldA (strong), maybe destroy+dealloc
```
bc55eef  lock dec dword ptr [rbx+8]       ; oldA->strong--
bc55ef3  jne short 0xBC55F1A              ; if strong != 0 skip destroy
bc55ef5  mov rax,[rbx]                    ; rax = oldA->vptr
bc55ef8  mov rax,[rax]                    ; rax = vtable[0] (destroy)
bc55efb  mov rcx,rbx                      ; rcx = oldA
bc55efe  call qword ptr [0xF99FFA0]       ; destroy(oldA)  [vtable dispatch]
bc55f04  lock dec dword ptr [rbx+0xC]     ; oldA->weak--
bc55f08  jne short 0xBC55F1A              ; if weak != 0 skip dealloc
bc55f0a  mov rax,[rbx]                    ; rax = oldA->vptr
bc55f0d  mov rax,[rax+8]                  ; rax = vtable[1] (dealloc)
bc55f11  mov rcx,rbx                      ; rcx = oldA
bc55f14  call qword ptr [0xF99FFA0]       ; dealloc(oldA)  [vtable dispatch]
```

### 0xbc55ef3..0xbc55f1a  — re-acquire oldA for slot b
```
loc_bc55f1a:
bc55f1a  test rsi,rsi                     ; rsi = oldA
bc55f1d  je short 0xBC55F23               ; if oldA == 0 skip
bc55f1f  lock inc dword ptr [rsi+8]       ; oldA->strong++
```

### 0xbc55f1a..0xbc55f23  — copy oldA's raw into slot b, set slot b's ref = oldA
```
loc_bc55f23:
bc55f23  mov [rdi],r14                    ; b->raw = oldRawA (a's old raw)
bc55f26  mov rbx,[rdi+8]                  ; rbx = b->ref (= oldA now)
bc55f2a  mov [rdi+8],rsi                  ; b->ref = oldA
bc55f2e  test rbx,rbx                     ; rbx = oldB (saved earlier)
bc55f31  je short 0xBC55F5E               ; if oldB == 0 skip release
```

### 0xbc55f2e..0xbc55f37  — release oldB (strong), maybe destroy+dealloc
```
bc55f33  lock dec dword ptr [rbx+8]       ; oldB->strong--
bc55f37  jne short 0xBC55F5E              ; if strong != 0 skip
bc55f39  mov rax,[rbx]                    ; rax = oldB->vptr
bc55f3c  mov rax,[rax]                    ; rax = vtable[0]
bc55f3f  mov rcx,rbx                      ; rcx = oldB
bc55f42  call qword ptr [0xF99FFA0]       ; destroy(oldB)
bc55f48  lock dec dword ptr [rbx+0xC]     ; oldB->weak--
bc55f4c  jne short 0xBC55F5E              ; if weak != 0 skip
bc55f4e  mov rax,[rbx]
bc55f51  mov rax,[rax+8]
bc55f55  mov rcx,rbx
bc55f58  call qword ptr [0xF99FFA0]       ; dealloc(oldB)
```

### 0xbc55f37..0xbc55f5e  — (fall-through of oldB release)
```
loc_bc55f5e:
bc55f5e  test rsi,rsi                     ; rsi = oldA
bc55f61  je short 0xBC55F9B               ; if oldA == 0 skip (-> epilogue)
bc55f63  lock dec dword ptr [rsi+8]       ; oldA->strong--  (the re-acquired temp)
bc55f67  jne short 0xBC55F9B
bc55f69  mov rax,[rsi]                    ; rax = oldA->vptr
bc55f6c  mov rax,[rax]                    ; rax = vtable[0]
bc55f6f  mov rcx,rsi                      ; rcx = oldA
bc55f72  call qword ptr [0xF99FFA0]       ; destroy(oldA)
bc55f78  lock dec dword ptr [rsi+0xC]     ; oldA->weak--
bc55f7c  jne short 0xBC55F9B              ; if weak != 0 skip dealloc
bc55f7e  mov rax,[rsi]                    ; rax = oldA->vptr
bc55f81  mov rax,[rax+8]                  ; rax = vtable[1]
bc55f85  mov rdx,[0xF99FFA0]              ; rdx = dealloc gadget address
bc55f8c  mov rcx,rsi                      ; rcx = oldA
bc55f8f  add rsp,0x28
bc55f93  pop rbx
bc55f94  pop rdi
bc55f95  pop rsi
bc55f96  pop r14
bc55f98  jmp rdx                          ; tail-jmp dealloc(oldA)
```

### 0xbc55f5e..0xbc55f9b  — release temp oldA, tail-call dealloc
```
loc_bc55f9b:
bc55f9b  add rsp,0x28
bc55f9f  pop rbx
bc55fa0  pop rdi
bc55fa1  pop rsi
bc55fa2  pop r14
bc55fa4  ret
```

### 0xbc55f9b..0xbc55fa5  — epilogue

## Struct fields touched
- `Slot::raw` (+0x00): W at 0xbc55ee3 (a->raw = b->raw), W at 0xbc55f23 (b->raw = oldRawA) [V]
- `Slot::ref` (+0x08): W at 0xbc55ee6 (a->ref = b->ref), W at 0xbc55f2a (b->ref = oldA) [V]
- `RefCounted::strong` (+0x08): RW lock inc/dec on each referenced object [V]
- `RefCounted::weak` (+0x0C): RW lock dec on each referenced object [V]
- `RefCounted::vptr` (+0x00): R to read vtable[0]/vtable[1] [V]

## Callees
- 0xF99FFA0 (data slot): indirect-call gadget `jmp rax` (at 0xeea6040). Target = object's vtable[0]/vtable[1] — virtual destroy/dealloc on the referenced RefCounted object. Not an external function; no static callee address; no boundary wrapper. 5 call sites: 0xbc55efe, 0xbc55f14, 0xbc55f42, 0xbc55f58, 0xbc55f72 [V].
- No callees in the lift set (CALLEES IN THE LIFT SET is empty) [V data file].
- native_boundary.tsv does not exist; no boundary calls in this function.

## Reversed source (complete)

See `src/client/features/render/native/bgfx/sub_bc55ea0.cpp` (first line `// LIFT 0xbc55ea0 size 0x105 1.26.62.01 sub_bc55ea0`). The C++ below is the complete reversed source; every statement is annotated with the instruction range it implements.

```cpp
// 0xbc55ea0..0xbc55ebf
RefCounted* oldA = a->ref;
if (oldA != nullptr) {
    oldA->strong.fetch_add(1u, std::memory_order_seq_cst);
}
void* oldRawA = a->raw;
RefCounted* oldB = b->ref;
if (oldB != nullptr) {
    oldB->strong.fetch_add(1u, std::memory_order_seq_cst);
}
// 0xbc55ed9..0xbc55eea
void* rawB = b->raw;
a->raw = rawB;
a->ref = oldB;
// 0xbc55eea..0xbc55ef3
if (oldA != nullptr) {
    if (oldA->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
        // 0xbc55efe  call qword ptr [0xF99FFA0]
        vtableDestroy(oldA)(oldA);
        if (oldA->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            // 0xbc55f14  call qword ptr [0xF99FFA0]
            vtableDealloc(oldA)(oldA);
        }
    }
}
// 0xbc55ef3..0xbc55f1a
if (oldA != nullptr) {
    oldA->strong.fetch_add(1u, std::memory_order_seq_cst);
}
// 0xbc55f1a..0xbc55f23
b->raw = oldRawA;
RefCounted* oldB2 = b->ref;
b->ref = oldA;
// 0xbc55f23..0xbc55f2e
// 0xbc55f2e..0xbc55f37
if (oldB2 != nullptr) {
    if (oldB2->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
        // 0xbc55f42  call qword ptr [0xF99FFA0]
        vtableDestroy(oldB2)(oldB2);
        if (oldB2->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            // 0xbc55f58  call qword ptr [0xF99FFA0]
            vtableDealloc(oldB2)(oldB2);
        }
    }
}
// 0xbc55f37..0xbc55f5e
// 0xbc55f5e..0xbc55f9b
if (oldA != nullptr) {
    if (oldA->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
        // 0xbc55f72  call qword ptr [0xF99FFA0]
        vtableDestroy(oldA)(oldA);
        if (oldA->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            VoidFn dealloc = vtableDealloc(oldA);
            return dealloc(oldA);   // 0xbc55f85..0xbc55f98 tail-jmp dealloc
        }
    }
}
// 0xbc55f9b..0xbc55fa5
return;
```

Where `vtableDestroy(r)` reads `r->vptr[0]` and `vtableDealloc(r)` reads `r->vptr[1]`, both invoked through the `0xF99FFA0` indirect-call gadget (`jmp rax`).

## Ownership / threading
No threading primitives beyond the lock-prefixed refcount ops on the referenced objects. The function does not touch any global state except the data-slot indirect-call gadget. Fail fast: no null guards beyond the explicit `test/jz` branches in the original; no SEH.

## Version anchors
Minecraft Bedrock 1.26.62.01, RVA 0xbc55ea0, size 0x105.

## Verification
- liftcheck: run `python tools/sigs/liftcheck.py 0xbc55ea0`.
- verify_oc: every quoted `0xRVA  call ...` line matches rdis output.
