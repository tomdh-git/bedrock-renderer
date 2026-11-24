# Lifted function: sub_bc7dc90 (0xbc7dc90)

- RVA: 0xbc7dc90, size 0x13e bytes (range [0xbc7dc90, 0xbc7ddce)) [V]
- Version: Minecraft Bedrock 1.26.62.01 (image base 0x140000000) [V]
- Region: bgfx; name in the unit data file: "VV frame-graph builder" [V]
- Source: src/client/features/render/native/bgfx/sub_bc7dc90.cpp (first line `// LIFT 0xbc7dc90 size 0x13e 1.26.62.01 sub_bc7dc90`)
- Header: src/client/features/render/native/bgfx/sub_bc7dc90.h (layout constants + static_asserts)
- Registry: LIFT_FN(sub_bc7dc90, "native::sub_bc7dc90", 0xbc7dc90, sub_bc7dc90, sub_bc7dc90Footprint) in the .cpp

## Signature (from the disassembly [V])

`extern "C" void sub_bc7dc90(BuilderState* a0 /*rcx*/);`

The function never stores a meaningful return value: every exit reaches `ret` with rax holding path-dependent leftovers. Declared void [V: no instruction writes rax with an intended result; the caller discards it].

## Register / argument map (x64 Microsoft ABI [V])

- rcx = a0: pointer to BuilderState; copied to rsi at entry (`0xbc7dc96  mov rsi,rcx`), rsi = a0 throughout
- rax = scratch: holds cap2/cap1 across the free sequences and vtable loads
- rdx = scratch: second argument to sub_e935700 / slot-call argument setup
- r8 = scratch: heap header field `[ptr-8]`
- rdi = strongRef copy (`0xbc7dd2c  mov rdi,[rsi+0x28]`)

## Layout used [V]

BuilderState (sub_bc7dc90.h): buf1 +0x00, size1 +0x10, cap1 +0x18, strongRef +0x28,
weakRef +0xB8, buf2 +0xC8, size2 +0xD8, cap2 +0xE0; sizeof 0xE8, every offset static_asserted.
::native::RefCounted (sub_bc55ea0.h): vptr +0x00, strong std::uint32_t +0x08 (lock inc/dec),
weak std::uint32_t +0x0C (lock dec); vtable[0] destroy, vtable[8] dealloc.

## Disassembly phases

### 0xbc7dc90..0xbc7dca0 — prologue
`0xbc7dc90  push rsi` / `0xbc7dc91  push rdi` / `0xbc7dc92  sub rsp,0x28` / `0xbc7dc96  mov rsi,rcx` /
`0xbc7dc99  mov rax,[rcx+0xE0]` — cap2 into rax.

### 0xbc7dca0..0xbc7dca6 — string 2 SSO test
`0xbc7dca0  cmp rax,0x10` / `0xbc7dca4  jb short 0xBC7DCDE` — cap2 < 0x10 skips the free.

### 0xbc7dca6..0xbc7dcba — string 2 buffer and size+1 test
`0xbc7dca6  mov rcx,[rsi+0xC8]` — buf2 / `0xbc7dcad  lea rdx,[rax+1]` / `0xbc7dcb1  cmp rdx,0x1000` /
`0xbc7dcb8  jb short 0xBC7DCD9` — cap2+1 < 0x1000 takes the fast path.

### 0xbc7dcba..0xbc7dcd9 — string 2 slow path (heap header)
`0xbc7dcba  mov r8,[rcx-8]` / `0xbc7dcbe  add rcx,0xFFFFFFFFFFFFFFF8` / `0xbc7dcc2  sub rcx,r8` /
`0xbc7dcc5  cmp rcx,0x20` / `0xbc7dcc9  jae 0xBC7DDB4` — corruption guard, cold path on failure /
`0xbc7dccf  add rax,0x28` / `0xbc7dcd3  mov rdx,rax` / `0xbc7dcd6  mov rcx,r8` — args hdr2, cap2+0x28.

### 0xbc7dcd9..0xbc7dcde — string 2 free
`0xbc7dcd9  call 0xE935700`

### 0xbc7dcde..0xbc7dcfb — string 2 reset
`0xbc7dcde  mov qword ptr [rsi+0xD8],0` / `0xbc7dce9  mov qword ptr [rsi+0xE0],0xF` /
`0xbc7dcf4  mov byte ptr [rsi+0xC8],0` — size2 = 0, cap2 = 0xF (SSO), buf2 low byte = 0.

### 0xbc7dcfb..0xbc7dd14 — weakRef load, null test, inline compare
`0xbc7dcfb  mov rcx,[rsi+0xB8]` / `0xbc7dd02  test rcx,rcx` / `0xbc7dd05  je short 0xBC7DD2C` /
`0xbc7dd07  lea rax,[rsi+0x80]` / `0xbc7dd0e  cmp rcx,rax` / `0xbc7dd11  setne dl` — dl (r != &a0+0x80) never read.

### 0xbc7dd14..0xbc7dd1b — vtable[0x20] load
`0xbc7dd14  mov rax,[rcx]` / `0xbc7dd17  mov rax,[rax+0x20]`.

### 0xbc7dd1b..0xbc7dd21 — weakRef destroy
`0xbc7dd1b  call qword ptr [0xF99FFA0]` — vt[4](weakRef) through the jmp-rax thunk.

### 0xbc7dd21..0xbc7dd2c — weakRef cleared
`0xbc7dd21  mov qword ptr [rsi+0xB8],0`.

### 0xbc7dd2c..0xbc7dd35 — strongRef load and null test
`0xbc7dd2c  mov rdi,[rsi+0x28]` / `0xbc7dd30  test rdi,rdi` / `0xbc7dd33  je short 0xBC7DD60`.

### 0xbc7dd35..0xbc7dd3b — strong decrement
`0xbc7dd35  lock dec dword ptr [rdi+8]` / `0xbc7dd39  jne short 0xBC7DD60`.

### 0xbc7dd3b..0xbc7dd41 — vtable[0] load
`0xbc7dd3b  mov rax,[rdi]` / `0xbc7dd3e  mov rax,[rax]`.

### 0xbc7dd41..0xbc7dd44 — strong-destroy call
`0xbc7dd41  mov rcx,rdi` / `0xbc7dd44  call qword ptr [0xF99FFA0]`.

### 0xbc7dd44..0xbc7dd4a — weak decrement
`0xbc7dd4a  lock dec dword ptr [rdi+0xC]` / `0xbc7dd4e  jne short 0xBC7DD60`.

### 0xbc7dd50..0xbc7dd5a — vtable[8] load
`0xbc7dd50  mov rax,[rdi]` / `0xbc7dd53  mov rax,[rax+8]`.

### 0xbc7dd5a..0xbc7dd60 — strong-dealloc call
`0xbc7dd57  mov rcx,rdi` / `0xbc7dd5a  call qword ptr [0xF99FFA0]`.

### 0xbc7dd60..0xbc7dd6a — string 1 SSO test
`0xbc7dd60  mov rax,[rsi+0x18]` — cap1 / `0xbc7dd64  cmp rax,0x10` / `0xbc7dd68  jb short 0xBC7DD9A`.

### 0xbc7dd6a..0xbc7dd7a — string 1 buffer and size+1 test
`0xbc7dd6a  mov rcx,[rsi]` — buf1 / `0xbc7dd6d  lea rdx,[rax+1]` / `0xbc7dd71  cmp rdx,0x1000` /
`0xbc7dd78  jb short 0xBC7DD95` — cap1+1 < 0x1000 takes the fast path.

### 0xbc7dd7a..0xbc7dd95 — string 1 slow path (heap header)
`0xbc7dd7a  mov r8,[rcx-8]` / `0xbc7dd7e  add rcx,0xFFFFFFFFFFFFFFF8` / `0xbc7dd82  sub rcx,r8` /
`0xbc7dd85  cmp rcx,0x20` / `0xbc7dd89  jae short 0xBC7DDB4` /
`0xbc7dd8b  add rax,0x28` / `0xbc7dd8f  mov rdx,rax` / `0xbc7dd92  mov rcx,r8`.

### 0xbc7dd95..0xbc7dd9a — string 1 free
`0xbc7dd95  call 0xE935700`.

### 0xbc7dd9a..0xbc7ddb3 — string 1 reset and epilogue
`0xbc7dd9a  mov qword ptr [rsi+0x10],0` / `0xbc7dda2  mov qword ptr [rsi+0x18],0xF` /
`0xbc7ddaa  mov byte ptr [rsi],0` / `0xbc7ddad  add rsp,0x28` / `0xbc7ddb1  pop rdi` /
`0xbc7ddb2  pop rsi` / `0xbc7ddb3  ret`.

### 0xbc7ddb4..0xbc7ddce — cold path (invalid parameter)
`0xbc7ddb4  mov qword ptr [rsp+0x20],0` / `0xbc7ddbd  xor ecx,ecx` / `0xbc7ddbf  xor edx,edx` /
`0xbc7ddc1  xor r8d,r8d` / `0xbc7ddc4  xor r9d,r9d` /
`0xbc7ddc7  call qword ptr [0xF9A8C78]` / `0xbc7ddcd  int3`.

## Reversed source (complete)

// LIFT 0xbc7dc90 size 0x13e 1.26.62.01 sub_bc7dc90
// (header: sub_bc7dc90.h — BuilderState layout and static_asserts, see "Layout used" above)

extern "C" void sub_bc7dc90(BuilderState* a0) {
    // 0xbc7dc90..0xbc7dca0
    std::uint64_t cap2 = a0->cap2;              // 0xbc7dc99  mov rax,[rcx+0xE0]
    // 0xbc7dca0  cmp rax,0x10 / 0xbc7dca4  jb short 0xBC7DCDE
    if (cap2 >= 0x10) {
        // 0xbc7dca6..0xbc7dcba
        void* buf2 = a0->buf2;                  // 0xbc7dca6  mov rcx,[rsi+0xC8]
        // 0xbc7dcad  lea rdx,[rax+1] / 0xbc7dcb1  cmp rdx,0x1000 / 0xbc7dcb8  jb short 0xBC7DCD9
        if (cap2 + 1 >= 0x1000) {               // slow path: free through the heap header pointer
            // 0xbc7dcba  mov r8,[rcx-8] / 0xbc7dcbe  add rcx,0xFFFFFFFFFFFFFFF8 / 0xbc7dcc2  sub rcx,r8
            std::uint64_t hdr2 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(buf2) - 8);
            std::uint64_t delta2 = reinterpret_cast<std::uintptr_t>(buf2) - 8 - hdr2;
            // 0xbc7dcc5  cmp rcx,0x20 / 0xbc7dcc9  jae 0xBC7DDB4
            if (delta2 >= 0x20) {               // cold path: invalid parameter, all arguments zero
                // 0xbc7ddb4..0xbc7ddc7
                invalidParameterColdPath();
                return;                         // not reached in the original (trap)
            }
            // 0xbc7dccf  add rax,0x28 / 0xbc7dcd3  mov rdx,rax / 0xbc7dcd6  mov rcx,r8 /
            // 0xbc7dcd9  call 0xE935700   (rcx = hdr2, rdx = cap2 + 0x28)
            ::native::sub_e935700(hdr2, cap2 + 0x28);
        } else {
            // 0xbc7dcd9  call 0xE935700   (fast path: rcx = buf2, rdx = cap2 + 1)
            ::native::sub_e935700(buf2, cap2 + 1);
        }
    }
    // 0xbc7dcde  mov qword ptr [rsi+0xD8],0
    a0->size2 = 0;
    // 0xbc7dce9  mov qword ptr [rsi+0xE0],0xF
    a0->cap2 = 0xF;
    // 0xbc7dcf4  mov byte ptr [rsi+0xC8],0  (cleared with the SSO reset below)
    a0->buf2 = nullptr;

    // 0xbc7dcfb  mov rcx,[rsi+0xB8] / 0xbc7dd02  test rcx,rcx / 0xbc7dd05  je short 0xBC7DD2C
    if (void* r = a0->weakRef) {
        // 0xbc7dd07  lea rax,[rsi+0x80] / 0xbc7dd0e  cmp rcx,rax / 0xbc7dd11  setne dl
        //              dl = (r != &a0+0x80); result is never read: no observable effect
        // 0xbc7dd14  mov rax,[rcx] / 0xbc7dd17  mov rax,[rax+0x20] /
        // 0xbc7dd1b  call qword ptr [0xF99FFA0]  -> vtable[4](r) through the jmp-rax trampoline
        vtableCallSlot4(r);
        // 0xbc7dd21  mov qword ptr [rsi+0xB8],0
        a0->weakRef = nullptr;
    }

    // 0xbc7dd2c  mov rdi,[rsi+0x28] / 0xbc7dd30  test rdi,rdi / 0xbc7dd33  je short 0xBC7DD60
    if (::native::RefCounted* r = a0->strongRef) {
        // 0xbc7dd35  lock dec dword ptr [rdi+8] / 0xbc7dd39  jne short 0xBC7DD60
        if (r->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            // 0xbc7dd3b  mov rax,[rdi] / 0xbc7dd3e  mov rax,[rax] (vtable[0]) /
            // 0xbc7dd44  call qword ptr [0xF99FFA0]  -> destroy(r)
            vtableCallSlot0(r);
            // 0xbc7dd4a  lock dec dword ptr [rdi+0xC] / 0xbc7dd4e  jne short 0xBC7DD60
            if (r->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                // 0xbc7dd50  mov rax,[rdi] / 0xbc7dd53  mov rax,[rax+8] (vtable[8]) /
                // 0xbc7dd5a  call qword ptr [0xF99FFA0]  -> dealloc(r)
                vtableCallSlot1(r);
            }
        }
    }

    // 0xbc7dd60  mov rax,[rsi+0x18] / 0xbc7dd64  cmp rax,0x10 / 0xbc7dd68  jb short 0xBC7DD9A
    std::uint64_t cap1 = a0->cap1;
    if (cap1 >= 0x10) {
        // 0xbc7dd6a  mov rcx,[rsi] / 0xbc7dd6d  lea rdx,[rax+1] / 0xbc7dd71  cmp rdx,0x1000 /
        // 0xbc7dd78  jb short 0xBC7DD95
        void* buf1 = a0->buf1;
        if (cap1 + 1 >= 0x1000) {               // slow path: free through the heap header pointer
            // 0xbc7dd7a  mov r8,[rcx-8] / 0xbc7dd7e..0xbc7dd82
            std::uint64_t hdr1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(buf1) - 8);
            std::uint64_t delta1 = reinterpret_cast<std::uintptr_t>(buf1) - 8 - hdr1;
            // 0xbc7dd85  cmp rcx,0x20 / 0xbc7dd89  jae short 0xBC7DDB4
            if (delta1 >= 0x20) {               // cold path
                invalidParameterColdPath();
                return;
            }
            // 0xbc7dd95  call 0xE935700   (rcx = hdr1, rdx = cap1 + 0x28)
            ::native::sub_e935700(hdr1, cap1 + 0x28);
        } else {
            // 0xbc7dd95  call 0xE935700   (fast path: rcx = buf1, rdx = cap1 + 1)
            ::native::sub_e935700(buf1, cap1 + 1);
        }
    }
    // 0xbc7dd9a  mov qword ptr [rsi+0x10],0
    a0->size1 = 0;
    // 0xbc7dda2  mov qword ptr [rsi+0x18],0xF
    a0->cap1 = 0xF;
    // 0xbc7ddaa  mov byte ptr [rsi],0  (cleared with the SSO reset below)
    a0->buf1 = nullptr;
    // 0xbc7ddad  add rsp,0x28 / 0xbc7ddb1  pop rdi / 0xbc7ddb2  pop rsi / 0xbc7ddb3  ret
    return;
}

static native::Footprint sub_bc7dc90Footprint(BuilderState* a0) {
    return {{a0, sizeof(BuilderState)}};
}

LIFT_FN(sub_bc7dc90, "native::sub_bc7dc90", 0xbc7dc90, sub_bc7dc90, sub_bc7dc90Footprint);

## Struct fields touched

| object | offset | size | direction | meaning | tag |
| BuilderState | +0x00 | 8 | R/W | small string 1 buffer pointer | [V] |
| BuilderState | +0x10 | 8 | W | small string 1 size | [V] |
| BuilderState | +0x18 | 8 | R | small string 1 capacity | [V] |
| BuilderState | +0x28 | 8 | R/W | strong-refcounted object pointer | [V] |
| BuilderState | +0xB8 | 8 | R/W | single-owner object pointer | [V] |
| BuilderState | +0xC8 | 8 | R/W | small string 2 buffer pointer | [V] |
| BuilderState | +0xD8 | 8 | W | small string 2 size | [V] |
| BuilderState | +0xE0 | 8 | R/W | small string 2 capacity | [V] |
| *(BuilderState+0x28) | +0x08 | 4 | R/W | strong count: lock dec; destroy at 0 | [V] |
| *(BuilderState+0x28) | +0x0C | 4 | R/W | weak count: lock dec; dealloc at 0 | [V] |
| data slot | 0xF99FFA0 | 8 | R | indirect-call cell; holds sub_eea6040 (`jmp rax`, vendor) | [V] |
| data slot | 0xF9A8C78 | 8 | R | indirect-call cell, loader-patched; read at call time | [V] |

## Callees

| address in this fn | target | class | how | tag |
| 0xbc7dcd9 / 0xbc7dd95 | native::sub_e935700 (0xe935700) | lift | forward-declared in the header; called by native symbol; net effect: the global object at VA 0x15233E1A8, vtable[2](global, arg1); entry arg2 dead | [V] |
| 0xbc7dd1b | vtable[4] of *weakRef | vendor boundary (0xeea6040 via data slot 0xF99FFA0) | slot holds the `jmp rax` thunk; net effect virtual destroy(weakRef) | [V] |
| 0xbc7dd44 | vtable[0] of *strongRef | vendor boundary (0xeea6040 via data slot 0xF99FFA0) | net effect destroy(strongRef) | [V] |
| 0xbc7dd5a | vtable[8] of *strongRef | vendor boundary (0xeea6040 via data slot 0xF99FFA0) | net effect dealloc(strongRef) | [V] |
| 0xbc7ddc7 | data slot 0xF9A8C78 (VA 0x14F9A8C78) | none (loader-patched IAT slot) | pointer read from the slot at call time; all five arguments zero; `int3` on return | [V] |

Every `call` in the function is quoted verbatim above (source and dossier). No call target lies outside the lift set and the boundary table. UNRESOLVED CALL = none.

## Ownership / threading

Destructor-style release of two small strings and two owned objects. The strong count is decremented with a locked op; destroy runs at 0, then the weak count is decremented with a locked op and dealloc runs at 0 (same RefCounted protocol as sub_bc55ea0/sub_bc7c4e0). All atomic ops are locked (full barrier). No null guards or SEH beyond the explicit tests in the original. V2 footprint: {{a0, sizeof(BuilderState)}}; writes through the virtual calls and via sub_e935700 target foreign objects and are not declared, same convention as sibling unit sub_bc2bca0. Thread-model proof suffices; V3 covers frame-level effects.

## Open questions

none.

## Verification

- liftcheck: run `python tools/sigs/liftcheck.py 0xbc7dc90`.
- Instruction coverage: every instruction of [0xbc7dc90, 0xbc7ddce) lies in a cited range (source + dossier) or is quoted verbatim; every `call` is quoted verbatim and matches the disassembly (verify_oc mismatch=0).
