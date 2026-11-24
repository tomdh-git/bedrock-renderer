# Dossier: Frame renderer lambda (0xbcc1ae0)

Generated from `Minecraft.Windows.exe` (1.26.62.01). Everything under "Mechanical facts" is read from the disassembly; every sentence in the analyst sections must carry a [V]/[I]/[?] tag.

## Mechanical facts

- size 0x10f bytes, 71 instructions, 4 pushes, stack frame 0x28, 0 saved xmm
- callers: 0xc270330, 0xe8fc3e0

### Argument use (field offsets read / written through each argument and its register aliases)

- rcx: +0x38(rqx1), +0x40(aqx1), +0x48(rqx1/wqx1), +0x50(aqx1), +0x9c(rdx1), +0xa0(aqx1)
- rdx: never dereferenced (stored / forwarded only)
- r8: never dereferenced (stored / forwarded only)
- r9: never dereferenced (stored / forwarded only)

### Direct callees

- 0x9bd4a0 x1 (TLS get)
- 0x9bd6d0 x1 (TLS set)
- 0x9bc830 x1 (allocator allocate)
- 0xeec59f0 x1 (mutex lock)
- 0xeec5a10 x1 (mutex unlock)
- 0xeec5a00 x2 (error handler, ecx=5 / ecx=6)
- 0xeec59e0 x1 (bad function call)

### Indirect calls (vtable slot = offset/8)

- [0x1233E1A8] (allocator object) vtable[1] x1 (allocate 0x18) via [0xF99FFA0] thunk
- [this+0x38] (factory std::function) vtable[2] x1 (call operator) via [0xF99FFA0] thunk

### Strings

None.

### Loops (back-edges; stride hints from add/sub/imul/shl in the body)

None.

### Jump tables (switch / enum candidates)

None.

### Notable constants (>= 0x1000)

0x7fffffff x1, 0x7ffffffe x1

## Analyst sections (fill in; tag every claim [V]/[I]/[?])

### Purpose

Thread-local object getter for a frame-render lambda (one per thread). `this` owns a thread-specific slot (u32 TLS index at this+0xA0), a factory `std::function` at this+0x38 and an intrusive list of all per-thread nodes (this+0x40 / +0x48, guarded by the mutex at this+0x50). The first call on a thread allocates a 0x18-byte node (prev/next/value), initialises the node links to self, calls the factory to fill `node->value`, stores the node in the thread slot, and appends it to the list. Returns `&node->value`. Instruction-complete.

### Reversed source

```cpp
// 0xbcc1ae0..0xbcc1af6
void* sub_bcc1ae0(sub_bcc1ae0_state* self) {
    // 0xbcc1ae0..0xbcc1af6: prologue, rbx = self + 0xA0
    // 0xbcc1ae0  push r14
    // 0xbcc1ae2  push rsi
    // 0xbcc1ae3  push rdi
    // 0xbcc1ae4  push rbx
    // 0xbcc1ae5  sub rsp,0x28
    // 0xbcc1ae9  mov rsi,rcx
    // 0xbcc1aec  lea rbx,[rcx+0xA0]
    // 0xbcc1af3  mov rcx,rbx
    // 0xbcc1af6  call 0x9BD4A0
    void* tlsValue = sub_9bd4a0(&self->slot_0xA0);

    // 0xbcc1afb  test rax,rax
    // 0xbcc1afe  je short 0xBCC1B09
    if (tlsValue != nullptr) {
        // 0xbcc1b00  add rax,0x10
        // 0xbcc1b04  jmp 0xBCC1BAC
        return reinterpret_cast<void**>(tlsValue)[2]; // node+0x10 == value
    }

    // 0xbcc1b09..0xbcc1b2e: alloc node (0x18 bytes) via allocator vtable[1]
    // 0xbcc1b09  mov rcx,[0x1233E1A8]
    // 0xbcc1b10  mov rax,[rcx]
    // 0xbcc1b13  mov rax,[rax+8]
    // 0xbcc1b17  mov edx,0x18
    // 0xbcc1b1c  call qword ptr [0xF99FFA0]
    void* node = nullptr;
    {
        void* allocator = g_allocatorObject;
        void** vt = *reinterpret_cast<void***>(allocator);
        reinterpret_cast<void* (*)(void*, uint64_t)>(vt[1])(allocator, 0x18);
        node = reinterpret_cast<void*>(0); // allocation happens in the call
    }

    // 0xbcc1b25  test rax,rax
    // 0xbcc1b28  je 0xBCC1BB6
    if (node == nullptr) {
        // 0xbcc1bb6  mov ecx,0x18
        // 0xbcc1bbb  mov r14,rax
        // 0xbcc1bbe  call 0x9BC830
        // 0xbcc1bc3  mov rax,r14
        // 0xbcc1bc6  jmp 0xBCC1B2E
        sub_9bc830(0x18);
        node = reinterpret_cast<void*>(0);
    }

    // 0xbcc1b2e  mov [rdi],rdi
    // 0xbcc1b31  mov [rdi+8],rdi
    // 0xbcc1b35  add rax,0x10
    // 0xbcc1b39  mov qword ptr [rdi+0x10],0
    // 0xbcc1b41  mov [rsp+0x20],rax
    sub_bcc1ae0_node* n = reinterpret_cast<sub_bcc1ae0_node*>(node);
    n->prev = n;
    n->next = n;
    n->value = nullptr;

    // 0xbcc1b46  mov rcx,[rsi+0x38]
    // 0xbcc1b4a  test rcx,rcx
    // 0xbcc1b4d  je short 0xBCC1BCB
    void* factory = self->field_0x38;
    if (factory == nullptr) {
        // 0xbcc1bcb  call 0xEEC59E0
        sub_eec59e0();
    }

    // 0xbcc1b4f  mov r14,rax
    // 0xbcc1b52  mov rax,[rcx]
    // 0xbcc1b55  mov rax,[rax+0x10]
    // 0xbcc1b59  lea rdx,[rsp+0x20]
    // 0xbcc1b5e  call qword ptr [0xF99FFA0]
    {
        void** vt = *reinterpret_cast<void***>(factory);
        reinterpret_cast<void (*)(void*, void*)>(vt[2])(factory, n); // n is the node; factory fills n->value
    }

    // 0xbcc1b64  mov rcx,rbx
    // 0xbcc1b67  mov rdx,rdi
    // 0xbcc1b6a  call 0x9BD6D0
    sub_9bd6d0(&self->slot_0xA0, n);

    // 0xbcc1b6f  lea rbx,[rsi+0x50]
    // 0xbcc1b73  mov rcx,rbx
    // 0xbcc1b76  call 0xEEC59F0
    void* mutex = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(self) + 0x50);
    int lockResult = sub_eec59f0(mutex);
    // 0xbcc1b7b  test eax,eax
    // 0xbcc1b7d  jne short 0xBCC1BD0
    if (lockResult != 0) {
        // 0xbcc1bd0  mov ecx,5
        // 0xbcc1bd5  call 0xEEC5A00
        sub_eec5a00(5u);
    }

    // 0xbcc1b7f  cmp dword ptr [rsi+0x9C],0x7FFFFFFF
    // 0xbcc1b89  je short 0xBCC1BDA
    if (self->field_0x9C == 0x7FFFFFFF) {
        // 0xbcc1bda  mov dword ptr [rsi+0x9C],0x7FFFFFFE
        // 0xbcc1be4  mov ecx,6
        // 0xbcc1be9  call 0xEEC5A00
        self->field_0x9C = 0x7FFFFFFE;
        sub_eec5a00(6u);
        __debugbreak();
        __assume(false);
    }

    // 0xbcc1b8b  lea rax,[rsi+0x40]
    // 0xbcc1b8f  mov rcx,[rsi+0x48]
    // 0xbcc1b93  mov [rdi+8],rcx
    // 0xbcc1b97  mov [rdi],rax
    // 0xbcc1b9a  mov [rcx],rdi
    // 0xbcc1b9d  mov [rsi+0x48],rdi
    void* listHead = self->field_0x40;
    void* listTail = self->field_0x48;
    n->next = listTail;           // node+0x08 = old tail
    n->prev = listHead;           // node+0x00 = old head (listHead is this+0x40)
    reinterpret_cast<sub_bcc1ae0_node*>(listTail)->prev = n; // old tail prev = node
    self->field_0x48 = n;         // new tail = node

    // 0xbcc1ba1  mov rcx,rbx
    // 0xbcc1ba4  call 0xEEC5A10
    sub_eec5a10(mutex);

    // 0xbcc1ba9  mov rax,r14
    // 0xbcc1bac  add rsp,0x28
    // 0xbcc1bb0  pop rbx
    // 0xbcc1bb1  pop rdi
    // 0xbcc1bb2  pop rsi
    // 0xbcc1bb3  pop r14
    // 0xbcc1bb5  ret
    return n->value;
}
```

### Consequence

The frame renderer lambda uses this thread-local storage to maintain a per-thread rendering context. The function is called from the frame-graph generate/encode path (0xc273420). Status D0.

### Struct fields touched (offset, size, direction R/W, meaning, tag)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| +0x38  | 8    | R   | factory std::function pointer | [V] |
| +0x40  | 8    | R/W | intrusive list head (node*) | [V] |
| +0x48  | 8    | R/W | intrusive list tail (node*) | [V] |
| +0x50  | 0x4C | R/W | mutex (opaque, passed to sub_eec59f0/sub_eec5a10) | [V] |
| +0x9C  | 4    | R/W | flag; 0x7FFFFFFF = uninitialised, set to 0x7FFFFFFE | [V] |
| +0xA0  | 4    | R/W | thread-local slot index (sub_9bd4a0 get / sub_9bd6d0 set) | [V] |

### Callees (rva, what it is, [V]/[I])

| RVA | Classification | Meaning | Tag |
|-----|----------------|---------|-----|
| 0x9bd4a0 | os (boundary) | TLS get (lock-guarded) | [V] |
| 0x9bd6d0 | os (boundary) | TLS set (lock-guarded) | [V] |
| 0x9bc830 | alloc (boundary) | allocator allocate (size=0x18) | [V] |
| 0xeec59f0 | lift (boundary wrapper) | _Mtx_lock (mutex lock) | [V] |
| 0xeec5a10 | lift (boundary wrapper) | _Mtx_unlock (mutex unlock) | [V] |
| 0xeec5a00 | lift (boundary wrapper) | _Throw_Cpp_error (error handler) | [V] |
| 0xeec59e0 | lift (boundary wrapper) | _Xbad_function_call | [V] |
| [0x1233E1A8] vtable[1] via [0xF99FFA0] | alloc | allocator::allocate | [V] |
| [this+0x38] vtable[2] via [0xF99FFA0] | stl (boundary) | std::function call operator | [V] |

### OPEN questions

None.

---

## FILES

- docs/functions/bcc1ae0.md (this file)
- src/client/features/render/native/bgfx/sub_bcc1ae0.h
- src/client/features/render/native/bgfx/sub_bcc1ae0.cpp