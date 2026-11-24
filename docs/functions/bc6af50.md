# Function dossier: 0xbc6af50 (BgfxFrameBuilder slot 82)

## Signature

`uint32_t sub_bc6af50(uint8_t a1 /*cl*/, uint32_t* a2 /*rdx*/);`

Return: EAX = ESI (0..11 range). x64 Microsoft ABI.

## Register / argument map

| Register | At entry | Meaning |
|---|---|---|
| RCX/CL | a1 | uint8_t loop/test value; tested at entry, zero-extended to EBX as loop limit |
| RDX | a2 | uint32_t* output array; written at a2[sil++] = counter |
| R8 | - | unused at entry |
| R9 | - | unused at entry |
| RSP | - | stack frame; local buffer at rsp+0x24 (0x9C bytes), cookie at rsp+0xC0 |

## Global data reads ([V])

- `0x1230A0C0` (data_1230a0c0): stack cookie global, R at 0xbc6af63 and 0xbc6b110
- `0x127CA028` (data_127ca028): base of 0x28-stride global array, R via `lea r15,[0x127CA028]` at 0xbc6af8b; byte-checked at `[r15]` per iteration
- `0xF9A8770` (data_f9a8770): fn1 indirect-call slot, R at 0xbc6af99 (r13) and 0xbc6b07f (rbx)
- `0xF9A8780` (data_f9a8780): fn2 indirect-call slot, R at 0xbc6afa0 (rbp) and 0xbc6b09f (r15)

## Global data writes ([V])

- `rsp+0xC0`: stack cookie slot, W at 0xbc6af6d

## Local stack ([V])

- `rsp+0x24`..`rsp+0xC0` (0x9C bytes): scratch buffer, written via `memset` (call 0xEBCE430), then `buffer[0] = 0x50000009C` (u64) and `buffer[0x2C] = 2` (u32 at index 11)

## Calls ([V])

All calls are quoted verbatim from the disassembly:

1. `0xbc6afd5  call 0xEBCE430` — memset(buffer, 0, 0x9C). Library intrinsic (memset). [V]
2. `0xbc6affb  call r13` — fn1(nullptr, 2, 5) via data slot [0xF9A8770]. [V]
3. `0xbc6b009  call r13` — fn1(v1, 1, 5) via data slot [0xF9A8770]. [V]
4. `0xbc6b017  call rbp` — fn2(&buffer, 3, v2) via data slot [0xF9A8780]. [V]
5. `0xbc6b063  call 0xEBCE430` — memset(buffer, 0, 0x9C) (second path). Library intrinsic. [V]
6. `0xbc6b090  call rbx` — fn1(nullptr, 2, 5) via data slot [0xF9A8770]. [V]
7. `0xbc6b09d  call rbx` — fn1(v1, 1, 5) via data slot [0xF9A8770]. [V]
8. `0xbc6b0b1  call r15` — fn2(&buffer, 3, v2) via data slot [0xF9A8780]. [V]
9. `0xbc6b0c5  call 0xEBCE430` — memset(buffer, 0, 0x9C) (second path, second round). Library intrinsic. [V]
10. `0xbc6b0e1  call rbx` — fn1(nullptr, 2, 5) via data slot [0xF9A8770]. [V]
11. `0xbc6b0ee  call rbx` — fn1(v1, 1, 5) via data slot [0xF9A8770]. [V]
12. `0xbc6b0fb  call r15` — fn2(&buffer, 3, v2) via data slot [0xF9A8780]. [V]
13. `0xbc6b13d  call 0xE951550` — stack-cookie-failure handler (boundary, crt), noreturn (int3 follows). [V]

Indirect calls (2,3,4,6,7,8,10,11,12) go through data slots per spec section 69:
- `[0xF9A8770]` = fn1: `void* (*)(void*, int, int)`, returns pointer in rax
- `[0xF9A8780]` = fn2: `int (*)(void*, int, void*)`, returns int in eax

## Callees

| RVA | Class | How resolved |
|---|---|---|
| 0xEBCE430 | library intrinsic (memset) | called directly as `memset()` in C++; original `call 0xEBCE430` quoted verbatim |
| [0xF9A8770] | indirect (data slot) | loaded at runtime via `RewriteRegistry::imageBase() + 0xF9A8770`, called as fn1 |
| [0xF9A8780] | indirect (data slot) | loaded at runtime via `RewriteRegistry::imageBase() + 0xF9A8780`, called as fn2 |
| 0xE951550 | boundary (crt) | via `native::Boundary<void, uintptr_t> sub_e951550("sub_e951550")` |

## Control flow

```
ENTRY
  if (a1 == 0 || a2 == nullptr) -> second_path
  sil = 0; counter = 0; gArrayPtr = 0x127CA028
LOOP:
  counter++; gArrayPtr += 0x28
  if (counter == 11) -> EPILOGUE
LOOP_BODY:
  if ((counter-1) > 1) -> SKIP
  memset(buffer,0,0x9C); buffer[0]=0x50000009C; buffer[11]=2
  v1 = fn1(nullptr,2,5); v2 = fn1(v1,1,5)
  r = fn2(&buffer,3,v2)
  if (!(r==0 && sil<a1)) -> LOOP
  goto STORE
SKIP:
  if (sil >= a1) -> LOOP
STORE:
  if (*gArrayPtr != 1) -> LOOP
  a2[sil++] = counter
  -> LOOP
second_path:
  memset(buffer,0,0x9C); buffer[0]=0x50000009C; buffer[11]=2
  v1 = fn1(nullptr,2,5); v2 = fn1(v1,1,5)
  r1 = fn2(&buffer,3,v2); sil = (r1==0)
  memset(buffer,0,0x9C); buffer[0]=0x50000009C; buffer[11]=2
  v1 = fn1(nullptr,2,5); v2 = fn1(v1,1,5)
  r2 = fn2(&buffer,3,v2); sil = sil + 9 + (r2==0)
  -> EPILOGUE
EPILOGUE:
  stack cookie check; if fail -> COOKIE_FAILURE
  return sil
COOKIE_FAILURE:
  sub_e951550(...); int3 (noreturn)
```

## Struct fields touched

None — the function touches no named game struct. All writes are to the stack buffer, the caller's `a2[]` output array, and the stack cookie slot.

## Reversed source (complete)

// 0xbc6af50..0xbc6af75
uint32_t sub_bc6af50(uint8_t a1, uint32_t* a2) {
    const std::uintptr_t cookie_global =
        *reinterpret_cast<const std::uintptr_t*>(
            RewriteRegistry::imageBase() + 0x1230A0C0);   // 0xbc6af63  mov rax,[0x1230A0C0]
    std::uintptr_t cookie_slot =
        cookie_global ^ reinterpret_cast<std::uintptr_t>(&cookie_slot);
// 0xbc6af6a  xor rax,rsp; 0xbc6af6d  mov [rsp+0xC0],rax  (cookie store above)

// 0xbc6af75  test cl,cl; 0xbc6af77  je 0xBC6B053
// 0xbc6af7d  mov rdi,rdx; 0xbc6af80  test rdx,rdx; 0xbc6af83  je 0xBC6B053
    if (a1 == 0 || a2 == nullptr) {
        goto second_path;
// 0xbc6af89  mov ebx,ecx     (bl = a1)
// 0xbc6af8b  lea r15,[0x127CA028]
// 0xbc6af92  xor esi,esi     (sil = 0)
// 0xbc6af94  lea r14,[rsp+0x24]  (&buffer)
// 0xbc6af99  mov r13,[0xF9A8770]  (fn1)
// 0xbc6afa0  mov rbp,[0xF9A8780]  (fn2)
// 0xbc6afa7  xor r12d,r12d  (counter = 0)
// 0xbc6afaa  jmp short 0xBC6AFC1  (-> LOOP_BODY)
    }

    std::uint8_t buffer[0x9C];
    std::uint8_t* gArrayPtr =
        reinterpret_cast<std::uint8_t*>(
            RewriteRegistry::imageBase() + 0x127CA028);
    std::uint8_t sil = 0;
    std::uint64_t counter = 0;

    auto fn1 = reinterpret_cast<void* (*)(void*, int, int)>(
        *reinterpret_cast<void**>(
            RewriteRegistry::imageBase() + 0xF9A8770));
    auto fn2 = reinterpret_cast<int (*)(void*, int, void*)>(
        *reinterpret_cast<void**>(
            RewriteRegistry::imageBase() + 0xF9A8780));

loop:
// 0xbc6afb0  inc r12; 0xbc6afb3  add r15,0x28
    ++counter;
    gArrayPtr += 0x28;
// 0xbc6afb7  cmp r12,0xB; 0xbc6afbb  je 0xBC6B105
    if (counter == 0xB) {
        goto epilogue;
    }

loop_body:
// 0xbc6afc1  lea eax,[r12-1]; 0xbc6afc6  cmp al,1; 0xbc6afc8  ja short 0xBC6B030
    if (static_cast<std::uint8_t>(counter - 1) > 1) {
        goto skip_store_check;
    }

// 0xbc6afca  mov r8d,0x9C; 0xbc6afd0  mov rcx,r14; 0xbc6afd3  xor edx,edx
// 0xbc6afd5  call 0xEBCE430                              ; memset(buffer, 0, 0x9C)
    std::memset(buffer, 0, 0x9C);

// 0xbc6afda  mov rax,0x50000009C; 0xbc6afe4  mov [rsp+0x24],rax
    *reinterpret_cast<std::uint64_t*>(buffer) = 0x50000009Cull;

// 0xbc6afe9  mov dword ptr [rsp+0x2C],2
    *reinterpret_cast<std::uint32_t*>(buffer + 0x2C) = 2;

// 0xbc6aff1  xor ecx,ecx; 0xbc6aff3  mov edx,2; 0xbc6aff8  mov r8b,5
// 0xbc6affb  call r13                                    ; fn1(nullptr, 2, 5)
    void* v1 = fn1(nullptr, 2, 5);

// 0xbc6affe  mov rcx,rax; 0xbc6b001  mov edx,1; 0xbc6b006  mov r8b,5
// 0xbc6b009  call r13                                    ; fn1(v1, 1, 5)
    void* v2 = fn1(v1, 1, 5);

// 0xbc6b00c  mov rcx,r14; 0xbc6b00f  mov edx,3; 0xbc6b014  mov r8,rax
// 0xbc6b017  call rbp                                    ; fn2(&buffer, 3, v2)
    int r = fn2(reinterpret_cast<void*>(buffer), 3, v2);

// 0xbc6b019  test eax,eax; 0xbc6b01b  sete al
// 0xbc6b01e  cmp sil,bl; 0xbc6b021  setb cl
// 0xbc6b024  test al,cl; 0xbc6b026  je short 0xBC6AFB0
    if (!((r == 0) && (sil < a1))) {
        goto loop;
    }

// 0xbc6b028  jmp short 0xBC6B039
    goto store;

skip_store_check:
// 0xbc6b030  cmp sil,bl; 0xbc6b033  jae 0xBC6AFB0
    if (sil >= a1) {
        goto loop;
    }

store:
// 0xbc6b039  cmp byte ptr [r15],1; 0xbc6b03d  jne 0xBC6AFB0
    if (*gArrayPtr != 1) {
        goto loop;
    }

// 0xbc6b043  movzx eax,sil; 0xbc6b047  inc sil
// 0xbc6b04a  mov [rdi+rax*4],r12d                        ; a2[sil++] = counter
    a2[sil++] = static_cast<std::uint32_t>(counter);

// 0xbc6b04e  jmp 0xBC6AFB0
    goto loop;

second_path:
// 0xbc6b053  lea rdi,[rsp+0x24]
// 0xbc6b058  mov r8d,0x9C; 0xbc6b05e  mov rcx,rdi; 0xbc6b061  xor edx,edx
// 0xbc6b063  call 0xEBCE430                              ; memset(buffer, 0, 0x9C)
    {
        std::uint8_t buffer2[0x9C];
        std::memset(buffer2, 0, 0x9C);

// 0xbc6b068  mov r14,0x50000009C; 0xbc6b072  mov [rsp+0x24],r14
        *reinterpret_cast<std::uint64_t*>(buffer2) = 0x50000009Cull;

// 0xbc6b077  mov dword ptr [rsp+0x2C],2
        *reinterpret_cast<std::uint32_t*>(buffer2 + 0x2C) = 2;

// 0xbc6b07f  mov rbx,[0xF9A8770]
        auto fn1b = reinterpret_cast<void* (*)(void*, int, int)>(
            *reinterpret_cast<void**>(
                RewriteRegistry::imageBase() + 0xF9A8770));
        auto fn2b = reinterpret_cast<int (*)(void*, int, void*)>(
            *reinterpret_cast<void**>(
                RewriteRegistry::imageBase() + 0xF9A8780));

// 0xbc6b086  xor ecx,ecx; 0xbc6b088  mov edx,2; 0xbc6b08d  mov r8b,5
// 0xbc6b090  call rbx                                    ; fn1(nullptr, 2, 5)
        void* v1b = fn1b(nullptr, 2, 5);

// 0xbc6b092  mov rcx,rax; 0xbc6b095  mov edx,1; 0xbc6b09a  mov r8b,5
// 0xbc6b09d  call rbx                                    ; fn1(v1, 1, 5)
        void* v2b = fn1b(v1b, 1, 5);

// 0xbc6b09f  mov r15,[0xF9A8780]
// 0xbc6b0a6  mov rcx,rdi; 0xbc6b0a9  mov edx,3; 0xbc6b0ae  mov r8,rax
// 0xbc6b0b1  call r15                                    ; fn2(&buffer, 3, v2b)
        int rb = fn2b(reinterpret_cast<void*>(buffer2), 3, v2b);

// 0xbc6b0b4  test eax,eax; 0xbc6b0b6  sete sil
        sil = (rb == 0) ? 1u : 0u;

// 0xbc6b0ba  mov r8d,0x9C; 0xbc6b0c0  mov rcx,rdi; 0xbc6b0c3  xor edx,edx
// 0xbc6b0c5  call 0xEBCE430                              ; memset(buffer, 0, 0x9C)
        std::memset(buffer2, 0, 0x9C);

// 0xbc6b0ca  mov [rsp+0x24],r14; 0xbc6b0cf  mov dword ptr [rsp+0x2C],2
        *reinterpret_cast<std::uint64_t*>(buffer2) = 0x50000009Cull;
        *reinterpret_cast<std::uint32_t*>(buffer2 + 0x2C) = 2;

// 0xbc6b0d7  xor ecx,ecx; 0xbc6b0d9  mov edx,2; 0xbc6b0de  mov r8b,5
// 0xbc6b0e1  call rbx                                    ; fn1(nullptr, 2, 5)
        void* v1c = fn1b(nullptr, 2, 5);

// 0xbc6b0e3  mov rcx,rax; 0xbc6b0e6  mov edx,1; 0xbc6b0eb  mov r8b,5
// 0xbc6b0ee  call rbx                                    ; fn1(v1, 1, 5)
        void* v2c = fn1b(v1c, 1, 5);

// 0xbc6b0f0  mov rcx,rdi; 0xbc6b0f3  mov edx,3; 0xbc6b0f8  mov r8,rax
// 0xbc6b0fb  call r15                                    ; fn2(&buffer, 3, v2c)
        int rc = fn2b(reinterpret_cast<void*>(buffer2), 3, v2c);

// 0xbc6b0fe  cmp eax,1; 0xbc6b101  adc sil,9
        sil = static_cast<std::uint8_t>(sil + 9u + (rc == 0 ? 1u : 0u));
    }
    goto epilogue;

epilogue:
// 0xbc6b105  mov rax,[rsp+0xC0]; 0xbc6b10d  xor rax,rsp
// 0xbc6b110  mov rcx,[0x1230A0C0]; 0xbc6b117  cmp rcx,rax
// 0xbc6b11a  jne short 0xBC6B132
    if ((cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot)) != cookie_global) {
        goto cookie_failure;
    }

// 0xbc6b11c  mov eax,esi; 0xbc6b11e  add rsp,0xC8
// 0xbc6b125..0xbc6b12f  pop rbx/rbp/rdi/rsi/r12/r13/r14/r15
// 0xbc6b131  ret
    return static_cast<uint32_t>(sil);

cookie_failure:
// 0xbc6b132  mov rcx,[rsp+0xC0]; 0xbc6b13a  xor rcx,rsp
// 0xbc6b13d  call 0xE951550
// 0xbc6b142  int3
    native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");
    sub_e951550(cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot));
    __assume(false);  // original executes int3 here (noreturn)
}

native::Footprint sub_bc6af50_footprint(uint8_t a1, uint32_t* a2) {
    return { { { a2, static_cast<size_t>(a1) * sizeof(std::uint32_t) } } };
}

LIFT_FN(sub_bc6af50, "BgfxFrameBuilder slot 82", 0xbc6af50, sub_bc6af50,
        sub_bc6af50_footprint);
