# Function dossier: sub_bcd54a0 (0xbcd54a0)

## Signature
`void* sub_bcd54a0(void* a0)` — x64 Microsoft ABI: argument in RCX, return value in RAX (the tail call to sub_e935700 passes RAX through).

## Size / range
0xb9 bytes, [0xbcd54a0, 0xbcd5559). Version 1.26.62.01.

## Register / argument map
- RCX = a0: pointer to argument object (ArgLayout)
- RSI = saved a0 (base of argument object)
- RDI = ref-counted object pointer (*(a0+0x40) = refObject)
- RAX = size / scratch (*(a0+0x28) = size)

## Struct fields touched
| Offset | Size | Direction | Meaning | Tag |
|--------|------|-----------|---------|-----|
| a0+0x10 | 8 | R | buffer pointer [V: 0xbcd54e7 mov rcx,[rsi+0x10]] | [V] |
| a0+0x10 | 1 | W | single zero byte at buffer field start [V: 0xbcd5528 mov byte ptr [rsi+0x10],0] | [V] |
| a0+0x20 | 8 | W | field20 reset to 0 [V: 0xbcd5518 mov qword ptr [rsi+0x20],0] | [V] |
| a0+0x28 | 8 | R/W | size/capacity [V: 0xbcd54dd mov rax,[rsi+0x28]; 0xbcd5520 mov qword ptr [rsi+0x28],0xF] | [V] |
| a0+0x40 | 8 | R | refObject: ref-counted object pointer [V: 0xbcd54a9 mov rdi,[rcx+0x40]] | [V] |
| (refObject)+0x8 | 4 | R/W | interlocked dword decrement (refcount) [V: 0xbcd54b2 lock dec dword ptr [rdi+8]] | [V] |
| (refObject)+0x0 | 8 | R | dead vtable read [V: 0xbcd54b8 mov rax,[rdi]] | [V] |
| (refObject)+0x0 | 8 | R | dead vtable[0] read [V: 0xbcd54bb mov rax,[rax]] | [V] |
| (refObject)+0xC | 4 | R/W | interlocked dword decrement [V: 0xbcd54c7 lock dec dword ptr [rdi+0xC]] | [V] |
| (refObject)+0x8 | 8 | R | dead vtable[1] read [V: 0xbcd54d0 mov rax,[rax+8]] | [V] |

## Callees
| Address | Target | Class | Source |
|---------|--------|-------|--------|
| 0xbcd54c1 | via [0xF99FFA0] (sub_eea6040) | vendor boundary via data slot | brief rule 69: call qword ptr [0xF99FFA0]; [data_f99ffa0] = sub_eea6040 (native_boundary.tsv line 506) |
| 0xbcd54d7 | via [0xF99FFA0] (sub_eea6040) | vendor boundary via data slot | brief rule 69: call qword ptr [0xF99FFA0]; [data_f99ffa0] = sub_eea6040 (native_boundary.tsv line 506) |
| 0xbcd5513 | sub_e935700 | lift | docs/data/native_boundary.tsv line 505; header: helpers/sub_e935700.h |
| 0xbcd5552 | via [0xF9A8C78] | indirect data slot | brief rule 69: call qword ptr [0xF9A8C78]; VA = imageBase() + 0xF9A8C78 |

## Reversed source (complete)

The C++ source lives at `src/client/features/render/native/helpers/sub_bcd54a0.cpp`
with header `src/client/features/render/native/helpers/sub_bcd54a0.h`.
Every instruction of [0xbcd54a0, 0xbcd5559) is covered by a cited range below,
and every `call` is quoted verbatim.

### 0xbcd54a0..0xbcd54a6 — prologue
```
// 0xbcd54a0  push rsi
// 0xbcd54a1  push rdi
// 0xbcd54a2  sub rsp,0x28
```
Compiler frame setup; no game memory touched.

### 0xbcd54a6..0xbcd54dd — read refObject, refcount, two release calls
```
// 0xbcd54a6  mov rsi,rcx
// 0xbcd54a9  mov rdi,[rcx+0x40]        ; R a0+0x40
// 0xbcd54ad  test rdi,rdi
// 0xbcd54b0  je short 0xBCD54DD        ; -> loc_bcd54dd if refObject == NULL
// 0xbcd54b2  lock dec dword ptr [rdi+8] ; W *(refObject)+0x8
// 0xbcd54b6  jne short 0xBCD54DD       ; -> loc_bcd54dd if refcount != 0
// 0xbcd54b8  mov rax,[rdi]             ; R *(refObject)+0x0   (dead read)
// 0xbcd54bb  mov rax,[rax]             ; R *(*(refObject))+0x0 (dead read)
// 0xbcd54be  mov rcx,rdi
// 0xbcd54c1  call qword ptr [0xF99FFA0] ; rcx=refObject
// 0xbcd54c7  lock dec dword ptr [rdi+0xC] ; W *(refObject)+0xC
// 0xbcd54cb  jne short 0xBCD54DD       ; -> loc_bcd54dd if refcount != 0
// 0xbcd54cd  mov rax,[rdi]             ; R *(refObject)+0x0   (dead read)
// 0xbcd54d0  mov rax,[rax+8]           ; R *(*(refObject))+0x8 (dead read)
// 0xbcd54d4  mov rcx,rdi
// 0xbcd54d7  call qword ptr [0xF99FFA0] ; rcx=refObject
```
```cpp
void* refObject = obj->refObject;                    // 0xbcd54a9  mov rdi,[rcx+0x40]
if (refObject != nullptr) {                          // 0xbcd54ad  test rdi,rdi ; 0xbcd54b0  je short 0xBCD54DD
    int32_t* refcount8 = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(refObject) + 8);
    int32_t after8 = --(*refcount8);                 // 0xbcd54b2  lock dec dword ptr [rdi+8]
    if (after8 != 0) goto loc_bcd54dd;               // 0xbcd54b6  jne short 0xBCD54DD
    void** vtable = reinterpret_cast<void**>(refObject);   // 0xbcd54b8  mov rax,[rdi]
    (void)vtable[0];                                 // 0xbcd54bb  mov rax,[rax]   (dead read)
    {                                                // 0xbcd54be  mov rcx,rdi ; 0xbcd54c1  call qword ptr [0xF99FFA0]
        using DtorFn = void (*)(void*);
        DtorFn dtor = reinterpret_cast<DtorFn>(
            *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
        dtor(refObject);                             // 0xbcd54c1  call qword ptr [0xF99FFA0]
    }
    int32_t* refcountC = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(refObject) + 0xC);
    int32_t afterC = --(*refcountC);                 // 0xbcd54c7  lock dec dword ptr [rdi+0xC]
    if (afterC != 0) goto loc_bcd54dd;               // 0xbcd54cb  jne short 0xBCD54DD
    vtable = reinterpret_cast<void**>(refObject);    // 0xbcd54cd  mov rax,[rdi]
    (void)vtable[1];                                 // 0xbcd54d0  mov rax,[rax+8] (dead read)
    {                                                // 0xbcd54d4  mov rcx,rdi ; 0xbcd54d7  call qword ptr [0xF99FFA0]
        using DtorFn = void (*)(void*);
        DtorFn dtor = reinterpret_cast<DtorFn>(
            *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
        dtor(refObject);                             // 0xbcd54d7  call qword ptr [0xF99FFA0]
    }
}
```

### 0xbcd54dd..0xbcd5518 — size branch and buffer free
```
// 0xbcd54dd  mov rax,[rsi+0x28]          ; R a0+0x28
// 0xbcd54e1  cmp rax,0x10
// 0xbcd54e5  jb short 0xBCD5518          ; -> loc_bcd5518 if size < 0x10
// 0xbcd54e7  mov rcx,[rsi+0x10]          ; R a0+0x10
// 0xbcd54eb  lea rdx,[rax+1]             ; rdx = size + 1
// 0xbcd54ef  cmp rdx,0x1000
// 0xbcd54f6  jb short 0xBCD5513          ; -> loc_bcd5513 if size+1 < 0x1000
// 0xbcd54f8  mov r8,[rcx-8]              ; R *(buffer-8)
// 0xbcd54fc  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx = buffer - 8
// 0xbcd5500  sub rcx,r8                  ; rcx = block_start
// 0xbcd5503  cmp rcx,0x20
// 0xbcd5507  jae short 0xBCD553F         ; -> loc_bcd553f if block_start >= 0x20
// 0xbcd5509  add rax,0x28                ; rax = size + 0x28 (dead)
// 0xbcd550d  mov rdx,rax                 ; rdx = size + 0x28 (dead)
// 0xbcd5510  mov rcx,r8                  ; rcx = r8
// 0xbcd5513  call 0xE935700              ; rcx = buffer (small path) or r8 (large path)
```
```cpp
uintptr_t size = obj->size;                          // 0xbcd54dd  mov rax,[rsi+0x28]
if (size >= 0x10) {                                  // 0xbcd54e1  cmp rax,0x10 ; 0xbcd54e5  jb short 0xBCD5518
    char* buffer = *reinterpret_cast<char**>(obj->field10);  // 0xbcd54e7  mov rcx,[rsi+0x10]
    uintptr_t rdx = size + 1;                        // 0xbcd54eb  lea rdx,[rax+1]
    if (rdx < 0x1000) {                              // 0xbcd54ef  cmp rdx,0x1000 ; 0xbcd54f6  jb short 0xBCD5513
        sub_e935700(buffer);                         // 0xbcd5513  call 0xE935700
    } else {
        uintptr_t r8 = *reinterpret_cast<uintptr_t*>(buffer - 8);  // 0xbcd54f8  mov r8,[rcx-8]
        uintptr_t rcx = reinterpret_cast<uintptr_t>(buffer) - 8;   // 0xbcd54fc  add rcx,0xFFFFFFFFFFFFFFF8
        rcx -= r8;                                   // 0xbcd5500  sub rcx,r8
        if (rcx >= 0x20) goto loc_bcd553f;           // 0xbcd5503  cmp rcx,0x20 ; 0xbcd5507  jae short 0xBCD553F
        // 0xbcd5509  add rax,0x28 ; 0xbcd550d  mov rdx,rax  (dead stores)
        sub_e935700(reinterpret_cast<void*>(r8));    // 0xbcd5510  mov rcx,r8 ; 0xbcd5513  call 0xE935700
    }
    // 0xbcd5513 falls through to 0xbcd5518
}
```

### 0xbcd5518..0xbcd553a — reset fields and tail call
```
// 0xbcd5518  mov qword ptr [rsi+0x20],0   ; W a0+0x20
// 0xbcd5520  mov qword ptr [rsi+0x28],0xF ; W a0+0x28
// 0xbcd5528  mov byte ptr [rsi+0x10],0    ; W a0+0x10
// 0xbcd552c  mov edx,0x48                 ; dead store
// 0xbcd5531  mov rcx,rsi                  ; rcx = a0
// 0xbcd5534  add rsp,0x28
// 0xbcd5538  pop rdi
// 0xbcd5539  pop rsi
// 0xbcd553a  jmp 0xE935700                ; tail call sub_e935700(a0)
```
```cpp
obj->field20 = 0;                        // 0xbcd5518  mov qword ptr [rsi+0x20],0
obj->size = 0xF;                         // 0xbcd5520  mov qword ptr [rsi+0x28],0xF
obj->field10[0] = '\0';                  // 0xbcd5528  mov byte ptr [rsi+0x10],0
// 0xbcd552c  mov edx,0x48                 (dead store)
return sub_e935700(a0);                  // 0xbcd5531  mov rcx,rsi ; 0xbcd553a  jmp 0xE935700
```

### 0xbcd553f..0xbcd5559 — indirect call through data slot (noreturn)
```
// 0xbcd553f  mov qword ptr [rsp+0x20],0
// 0xbcd5548  xor ecx,ecx
// 0xbcd554a  xor edx,edx
// 0xbcd554c  xor r8d,r8d
// 0xbcd554f  xor r9d,r9d
// 0xbcd5552  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
// 0xbcd5558  int3
```
```cpp
{                                          // 0xbcd553f..0xbcd554f   zero args; stack store
    using FailFn = void (*)(void*, void*, void*, void*, void*);
    FailFn fail = reinterpret_cast<FailFn>(
        *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8C78));
    fail(nullptr, nullptr, nullptr, nullptr, nullptr);  // 0xbcd5552  call qword ptr [0xF9A8C78]
}
// 0xbcd5558  int3   (noreturn block terminator)
__assume(false);
```

## Ownership / threading
No locks, no thread synchronization beyond the interlocked dword decrements on the ref-counted object. The argument object is owned by the caller. The refObject release is the game's own lifetime management. Safe for V2 differential testing with footprint = {a0+0x10, 8}, {a0+0x20, 8}, {a0+0x28, 8}.

## Verification artifacts
- Source: `src/client/features/render/native/helpers/sub_bcd54a0.cpp`
- Header: `src/client/features/render/native/helpers/sub_bcd54a0.h`
- Registry: `LIFT_FN(sub_bcd54a0, "sub_bcd54a0", 0xbcd54a0, sub_bcd54a0, nullptr)` in the .cpp
- Layout assertions: `static_assert` for field10/field20/size/refObject offsets and sizeof in the header

## Version anchors
- Version: 1.26.62.01
- Exe: Minecraft.Windows.exe (image base 0x140000000), data slots resolved via `RewriteRegistry::imageBase() + RVA`
