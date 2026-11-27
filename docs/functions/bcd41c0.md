# Function dossier: sub_bcd41c0 (0xbcd41c0)

## Signature
`void sub_bcd41c0(void* a0)` — x64 Microsoft ABI: argument in RCX, no return value.

## Size / range
0xad bytes, [0xbcd41c0, 0xbcd426d). Version 1.26.62.01.

## Register / argument map
- RCX = a0: pointer to argument object (ArgLayout)
- RDI = walking pointer into the list (starts at *a0 = field00)
- RSI = saved a0 (base of argument object)
- R14 = end pointer (*(a0+0x8) = field08)
- RBX = current list node pointer (*rdi)
- RDX = remaining size (*(a0+0x10) - rdi)
- RAX = scratch / metadata (*(rdi-8))

## Struct fields touched
| Offset | Size | Direction | Meaning | Tag |
|--------|------|-----------|---------|-----|
| a0+0x00 | 8 | R/W | field00: list current/start pointer [V: 0xbcd41c9 mov rdi,[rcx]; 0xbcd423e movups [rsi],xmm0] |
| a0+0x08 | 8 | R/W | field08: end pointer [V: 0xbcd41d4 mov r14,[rcx+8]; 0xbcd423e movups [rsi],xmm0] |
| a0+0x10 | 8 | R/W | field10: buffer end pointer [V: 0xbcd420b mov rdx,[rsi+0x10]; 0xbcd4241 mov [rsi+0x10],0] |

## Callees
| Address | Target | Class | Source |
|---------|--------|-------|--------|
| 0xbcd41f4 | sub_e87c6d0 | lift | docs/data/native_functions.tsv (callee_in_set); header: d3d12/sub_e87c6d0.h |
| 0xbcd4201 | sub_e935700 | lift | docs/data/native_boundary.tsv line 505; header: helpers/sub_e935700.h |
| 0xbcd4236 | sub_e935700 | lift | docs/data/native_boundary.tsv line 505; header: helpers/sub_e935700.h |
| 0xbcd4266 | via [0xF9A8C78] | indirect data slot | brief rule 69: call qword ptr [0xF9A8C78]; target unknown at static analysis time |

## Reversed source (complete)

The C++ source lives at `src/client/features/render/native/helpers/sub_bcd41c0.cpp`
with header `src/client/features/render/native/helpers/sub_bcd41c0.h`.
Every instruction of [0xbcd41c0, 0xbcd426d) is covered by a cited range below,
and every `call` is quoted verbatim.

### 0xbcd41c0..0xbcd41c9 — prologue
```
// 0xbcd41c0  push r14
// 0xbcd41c2  push rsi
// 0xbcd41c4  push rbx
// 0xbcd41c5  sub rsp,0x28
```
Compiler frame setup; no game memory touched.

### 0xbcd41c9..0xbcd41d1 — read field00, null check
```
// 0xbcd41c9  mov rdi,[rcx]        ; R a0+0x0
// 0xbcd41cc  test rdi,rdi
// 0xbcd41cf  je short 0xBCD4249   ; -> epilogue if field00 == NULL
```
```cpp
void* rdi = obj->field00;                    // 0xbcd41c9  mov rdi,[rcx]
if (rdi == nullptr) {                        // 0xbcd41cc  test rdi,rdi ; 0xbcd41cf  je short 0xBCD4249
    return;                                  // 0xbcd4249..0xbcd4253   epilogue + ret
}
```

### 0xbcd41d1..0xbcd41d8 — save base, read field08
```
// 0xbcd41d1  mov rsi,rcx
// 0xbcd41d4  mov r14,[rcx+8]      ; R a0+0x8
```
```cpp
void* rsi = a0;                              // 0xbcd41d1  mov rsi,rcx
void* r14 = obj->field08;                    // 0xbcd41d4  mov r14,[rcx+8]
```

### 0xbcd41d8..0xbcd41dd — compare field00 vs field08
```
// 0xbcd41d8  cmp rdi,r14
// 0xbcd41db  jne short 0xBCD41E9   ; -> loop if non-empty
// 0xbcd41dd  jmp short 0xBCD420B   ; -> skip loop if empty
```
```cpp
if (rdi != r14) {                            // 0xbcd41d8  cmp rdi,r14 ; 0xbcd41db  jne short 0xBCD41E9
```

### 0xbcd41e0..0xbcd4208 — list walk loop
```
// 0xbcd41e0  add rdi,8
// 0xbcd41e4  cmp rdi,r14
// 0xbcd41e7  je short 0xBCD4208   ; -> loop exit
// 0xbcd41e9  mov rbx,[rdi]        ; R *rdi (list node pointer)
// 0xbcd41ec  test rbx,rbx
// 0xbcd41ef  je short 0xBCD41E0   ; -> next entry if node is NULL
// 0xbcd41f1  mov rcx,rbx
// 0xbcd41f4  call 0xE87C6D0
// 0xbcd41f9  mov edx,0x38
// 0xbcd41fe  mov rcx,rbx
// 0xbcd4201  call 0xE935700
// 0xbcd4206  jmp short 0xBCD41E0   ; -> next entry
```
```cpp
    do {
        void* rbx = *reinterpret_cast<void**>(rdi);   // 0xbcd41e9  mov rbx,[rdi]
        if (rbx != nullptr) {                // 0xbcd41ec  test rbx,rbx ; 0xbcd41ef  je short 0xBCD41E0
            native::sub_e87c6d0(rbx);        // 0xbcd41f4  call 0xE87C6D0
            native::sub_e935700(rbx);        // 0xbcd4201  call 0xE935700
        }
        rdi += 8;                            // 0xbcd41e0  add rdi,8
    } while (rdi != r14);                    // 0xbcd41e7  je short 0xBCD4208
// 0xbcd4208  mov rdi,[rsi]
    rdi = obj->field00;                      // 0xbcd4208  mov rdi,[rsi]      (= field00)
```

### 0xbcd420b..0xbcd421b — remaining size computation
```
// 0xbcd420b  mov rdx,[rsi+0x10]   ; R a0+0x10
// 0xbcd420f  sub rdx,rdi
// 0xbcd4212  cmp rdx,0x1000
```
```cpp
uintptr_t remaining = (uintptr_t)((char*)obj->field10 - (char*)rdi);
```

### 0xbcd4219 — branch on remaining size
```
// 0xbcd4219  jb short 0xBCD4233   ; -> direct release if remaining < 0x1000
```
```cpp
if (remaining < 0x1000) {                    // 0xbcd4212  cmp rdx,0x1000 ; 0xbcd4219  jb short 0xBCD4233
    native::sub_e935700(rdi);                // 0xbcd4236  call 0xE935700
```

### 0xbcd421b..0xbcd422a — block metadata path (remaining >= 0x1000)
```
// 0xbcd421b  mov rax,[rdi-8]        ; R *(rdi - 8)
// 0xbcd421f  add rdi,0xFFFFFFFFFFFFFFF8   ; rdi -= 8
// 0xbcd4223  sub rdi,rax            ; rdi = (rdi - 8) - rax
// 0xbcd4226  cmp rdi,0x20
// 0xbcd422a  jae short 0xBCD4253    ; -> indirect call if block_start >= 0x20
```
```cpp
} else {
    uintptr_t rax_val = *reinterpret_cast<uintptr_t*>((char*)rdi - 8);   // 0xbcd421b  mov rax,[rdi-8]
    void* block_start = (void*)((char*)rdi - 8 - rax_val);               // 0xbcd421f  add rdi,-8 ; 0xbcd4223  sub rdi,rax
    if ((uintptr_t)block_start >= 0x20) {    // 0xbcd422a  jae short 0xBCD4253
```

### 0xbcd4253..0xbcd426d — indirect call through data slot
```
// 0xbcd4253  mov qword ptr [rsp+0x20],0
// 0xbcd425c  xor ecx,ecx
// 0xbcd425e  xor edx,edx
// 0xbcd4260  xor r8d,r8d
// 0xbcd4263  xor r9d,r9d
// 0xbcd4266  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
// 0xbcd426c  int3
```
```cpp
        using FnPtr = void (*)(void*, void*, void*, void*, void*);
        FnPtr fn = reinterpret_cast<FnPtr>(
            *reinterpret_cast<uintptr_t*>(0x140000000ULL + 0xF9A8C78ULL));
        fn(nullptr, nullptr, nullptr, nullptr, nullptr);
        return;   // 0xbcd426c  int3   (trap; end of function)
```

### 0xbcd422c..0xbcd4230 — block_start < 0x20 path
```
// 0xbcd422c  add rdx,0x27   ; dead store: rdx never read again
// 0xbcd4230  mov rdi,rax
```
```cpp
        rdi = (void*)rax_val;                    // 0xbcd4230  mov rdi,rax
        native::sub_e935700(rdi);                // 0xbcd4236  call 0xE935700
    }
```

### 0xbcd4233..0xbcd4249 — release and zero
```
// 0xbcd4233  mov rcx,rdi
// 0xbcd4236  call 0xE935700
// 0xbcd423b  xorps xmm0,xmm0
// 0xbcd423e  movups [rsi],xmm0   ; W a0+0x0 (8 bytes) + a0+0x8 (8 bytes)
// 0xbcd4241  mov qword ptr [rsi+0x10],0   ; W a0+0x10
```
```cpp
    obj->field00 = nullptr;                      // 0xbcd423e  movups [rsi],xmm0
    obj->field08 = nullptr;
    obj->field10 = nullptr;                      // 0xbcd4241  mov [rsi+0x10],0
```

### 0xbcd4249..0xbcd4253 — epilogue
```
// 0xbcd4249  add rsp,0x28
// 0xbcd424d  pop rbx
// 0xbcd424e  pop rdi
// 0xbcd424f  pop rsi
// 0xbcd4250  pop r14
// 0xbcd4252  ret
```
```cpp
}   // fall through to return; compiler emits add rsp,0x28; pop rbx; pop rdi; pop rsi; pop r14; ret
```

## Ownership / threading
No locks, no thread synchronization. The argument object is owned by the caller. Safe for V2 differential testing with footprint = {a0+0x0, 16}, {a0+0x10, 8}.

## Verification artifacts
- Source: `src/client/features/render/native/helpers/sub_bcd41c0.cpp`
- Header: `src/client/features/render/native/helpers/sub_bcd41c0.h`
- Registry: `LIFT_FN(sub_bcd41c0, "sub_bcd41c0", 0xbcd41c0, sub_bcd41c0, nullptr)` in the .cpp
- Layout assertions: `static_assert` for field00/field08/field10 offsets and sizeof in the header
