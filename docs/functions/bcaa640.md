# sub_bcaa640 (0xbcaa640, 0x135 bytes, depth 2, D0, bgfx)

## Signature

`void sub_bcaa640(sub_bcaa640_state* self)` (rcx = self, Microsoft x64 ABI). Return value never observed at the call sites; function returns void. [V]

## Register / argument map

- rcx = self = `sub_bcaa640_state*` (rsi after prologue)
- rax = capacity field / scratch / vtable slot result
- rdx = size argument to sub_e935700 / arg2
- r8 = heap-block header (`[ptr-8]`) on the big-buffer path
- rdi = refcounted object at `self+0x28`
- rbp/rsp stack home as set by the prologue (`sub rsp,0x28`)

## Analysis

### 0xbcaa640..0xbcaa656: prologue + buffer-A (field +0xA0) heap test

`push rsi; push rdi; sub rsp,0x28; mov rsi,rcx; mov rax,[rcx+0xA0]; cmp rax,0x10; jb 0xBCAA68E`. If capacity < 0x10 (SSO), skip the free. [V]

### 0xbcaa656..0xbcaa689: buffer-A free (sub_e935700)

Small (cap+1 < 0x1000): `sub_e935700(self->field_0x88, capA+1)`. Big: heap-header check `(self->ptrA-8) - *[ptrA-8] < 0x20` else `_invoke_watson`; then `sub_e935700([ptrA-8], capA+0x28)`. [V]

### 0xbcaa68e..0xbcaa6ab: reset buffer-A to SSO

`self->field_0x98 = 0; self->field_0xA0 = 0xF; *(uint8_t*)&self->field_0x88 = 0;` [V]

### 0xbcaa6ab..0xbcaa6cb: release refcounted object at +0x78 (vtable slot 4)

`if (self->field_0x78 != 0) { vt = *self->field_0x78; vt[4](self->field_0x78); } self->field_0x78 = 0;` The `lea rax,[rsi+0x40]; cmp rcx,rax; setne dl` at 0xbcaa6b4..0xbcaa6bb computes a flag that is never read. [V] (dead store; inferred from the disassembly)

### 0xbcaa6d3..0xbcaa707: release refcounted object at +0x28 (strong pattern)

`if (self->field_0x28 != 0) { lock dec [obj+8]; if 0: vt[0](obj); lock dec [obj+0xC]; if 0: vt[1](obj); }` [V]

### 0xbcaa707..0xbcaa75a: buffer-B free + reset

Same free pattern on `self->field_0x00 / field_0x10 / field_0x18`, then `self->field_0x10 = 0; self->field_0x18 = 0xF; *(uint8_t*)&self->field_0x00 = 0;` and `ret`. [V]

### 0xbcaa75b..0xbcaa775: corrupt-heap trap path (noreturn)

`[rsp+0x20] = 0; ecx = edx = r8d = r9d = 0; call qword ptr [0xF9A8C78]` (_invoke_watson, noreturn), then int3 padding. Reached from both big-path `jae` branches. [V]

## Struct fields touched

| offset | size | dir | meaning | tag |
|--------|------|-----|---------|-----|
| 0x00   | 8    | R/W | buffer B pointer (first byte written 0) | [V] |
| 0x10   | 8    | W   | buffer B size-like field (written 0) | [V] |
| 0x18   | 8    | R   | buffer B capacity | [V] |
| 0x28   | 8    | R/W | refcounted object A (strong release, then not zeroed here) | [V] |
| 0x78   | 8    | R/W | refcounted object B (released, zeroed) | [V] |
| 0x88   | 8    | R/W | buffer A pointer (first byte written 0) | [V] |
| 0x98   | 8    | W   | buffer A size (written 0) | [V] |
| 0xA0   | 8    | R   | buffer A capacity | [V] |

## Callees

- `0xE935700` = sub_e935700 (lift-set callee, `jmp 0x392960`, size 0x5): called twice (buffer-A and buffer-B free). [V]
- `0xF99FFA0` data slot = sub_eea6040 (vendor, `jmp rax` thunk): three indirect virtual calls (vtable slots 4, 0, 1). [V]
- `0xF9A8C78` data slot = `_invoke_watson` IAT slot: noreturn trap on corrupt heap header. [V]

## OPEN questions

None. All call targets are lifted (sub_e935700) or documented data-slot indirects.

## Verbatim call instructions

0xbcaa689  call 0xE935700
0xbcaa6c5  call qword ptr [0xF99FFA0]
0xbcaa6eb  call qword ptr [0xF99FFA0]
0xbcaa701  call qword ptr [0xF99FFA0]
0xbcaa73c  call 0xE935700
0xbcaa76e  call qword ptr [0xF9A8C78]

## Reversed source (complete)

```cpp
// 0xbcaa640..0xbcaa656
void sub_bcaa640(sub_bcaa640_state* self) {
    uint64_t capA = self->field_0xA0;
    if (capA >= 0x10) {
        // 0xbcaa656..0xbcaa689
        void* ptrA = self->field_0x88;
        if (capA + 1 < 0x1000) {
            sub_e935700((uint64_t)ptrA, capA + 1);          // 0xbcaa689  call 0xE935700
        } else {
            uint64_t hdr = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptrA) - 8);
            uint64_t delta = (reinterpret_cast<uintptr_t>(ptrA) - 8) - hdr;
            if (delta >= 0x20) {
                // 0xbcaa75b..0xbcaa775
                auto watson = reinterpret_cast<void (*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t)>(
                    *reinterpret_cast<uintptr_t*>(0x14F9A8C78));
                watson(nullptr, nullptr, nullptr, 0, 0);
            }
            sub_e935700(hdr, capA + 0x28);                  // 0xbcaa689  call 0xE935700
        }
    }

    // 0xbcaa68e..0xbcaa6ab
    self->field_0x98 = 0;
    self->field_0xA0 = 0xF;
    *reinterpret_cast<uint8_t*>(&self->field_0x88) = 0;

    // 0xbcaa6ab..0xbcaa6cb
    void* objB = self->field_0x78;
    if (objB != 0) {
        void** vtB = *reinterpret_cast<void***>(objB);
        vtB[4](objB);                                      // 0xbcaa6c5  call qword ptr [0xF99FFA0]
    }
    self->field_0x78 = 0;

    // 0xbcaa6d3..0xbcaa707
    void* objA = self->field_0x28;
    if (objA != 0) {
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(objA) + 8)) == 0) {
            void** vtA0 = *reinterpret_cast<void***>(objA);
            vtA0[0](objA);                                 // 0xbcaa6eb  call qword ptr [0xF99FFA0]
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(objA) + 0xC)) == 0) {
                void** vtA1 = *reinterpret_cast<void***>(objA);
                vtA1[1](objA);                             // 0xbcaa701  call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0xbcaa707..0xbcaa75a
    uint64_t capB = self->field_0x18;
    if (capB >= 0x10) {
        void* ptrB = self->field_0x00;
        if (capB + 1 < 0x1000) {
            sub_e935700((uint64_t)ptrB, capB + 1);        // 0xbcaa73c  call 0xE935700
        } else {
            uint64_t hdrB = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptrB) - 8);
            uint64_t deltaB = (reinterpret_cast<uintptr_t>(ptrB) - 8) - hdrB;
            if (deltaB >= 0x20) {
                auto watson = reinterpret_cast<void (*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t)>(
                    *reinterpret_cast<uintptr_t*>(0x14F9A8C78));
                watson(nullptr, nullptr, nullptr, 0, 0);
            }
            sub_e935700(hdrB, capB + 0x28);                // 0xbcaa73c  call 0xE935700
        }
    }

    // 0xbcaa741..0xbcaa75a
    self->field_0x10 = 0;
    self->field_0x18 = 0xF;
    *reinterpret_cast<uint8_t*>(&self->field_0x00) = 0;
}
```