# Function 0xbc2bca0 — sub_bc2bca0 (Minecraft Windows 1.26.62.01)

## Identity
- RVA: 0xbc2bca0, size 0x172 bytes ([0xbc2bca0, 0xbc2be12)), depth 1, milestone D0, region bgfx.
- Root: 0xbb6b350 (added by this unit). Callees in lift set: none. Callees outside set: 0x655cea0 (boundary, stl).
- Lifted at: src/client/features/render/native/bgfx/sub_bc2bca0.cpp (+ .h), registry entry LIFT_FN(sub_bc2bca0).

## Signature (x64 Microsoft ABI)
`uintptr_t sub_bc2bca0(sub_bc2bca0_state* self);`  — `self` = rcx (this pointer), return in rax.

## Register/argument map
- rcx = self (object pointer) → copied to rsi at 0xbc2bcad (`mov rsi,rcx`); all field accesses use rsi-based offsets.
- rax = return value (varies by path: capacity on SSO path, notifyGlobal result on heap paths, _invoke_watson result on the corruption path).

## Phases
```
// 0xbc2bca0..0xbc2bcad
Prologue: push r15/r14/r12/rsi/rdi/rbx; sub rsp,0x28; mov rsi,rcx. No observable effect.

// 0xbc2bcad..0xbc2bce1
obj2 = self->field_0x2F8; if (obj2 == 0) skip.
Dead address comparison: lea rax,[rsi+0x2C0]; cmp rcx,rax; setne dl — dl never read.
call vtable[4](obj2) through the jmp-rax thunk at data slot [0xF99FFA0] ([data_f99ffa0] = sub_eea6040).
self->field_0x2F8 = 0 (always, even when obj2 == 0).

// 0xbc2bce1..0xbc2bd21
if (byte self->field_0x90 == 3) {
    obj1 = self->field_0x88; if (obj1 != 0) {
        lock dec [obj1+8]; if result == 0: call vtable[0](obj1);
        lock dec [obj1+0xC]; if result == 0: call vtable[1](obj1);
    }
}

// 0xbc2bd21..0xbc2bd8d
container = &self->field_0x20; entry = self->field_0x60; end = self->field_0x68;
if (entry != 0) walk [entry, end) in strides of 0x28:
    if (byte[entry+0x18] == 2) { objx = ptr[entry+0x8]; if (objx != 0) releaseRefObj(objx); }
self->field_0x60 = 0; self->field_0x68 = 0; self->field_0x70 = 0 (movups 16-byte zero store at +0x60, then qword store at +0x70).

// 0xbc2bd95..0xbc2bd9d
call 0x655CEA0 (sub_655cea0, boundary stl) with rcx = &self->field_0x20; return ignored.

// 0xbc2bd95..0xbc2bde8 — buffer deallocation
cap = self->field_0x18;
if (cap < 0x10): ret = cap; fall to reset.
else:
    ptr = self->field_0x00;
    if (cap + 1 < 0x1000): ret = call 0xE935700(rcx = ptr)  — sub_e935700 = jmp 0x392960: if (ptr != 0) { g = *(void**)VA 0x15233E1A8; call g->vtable[2](g); } return rax.
    else:
        hdr = u64 at (ptr - 8); delta = (ptr - 8) - hdr;
        if (delta >= 0x20): zero rcx/rdx/r8/r9/[rsp+0x20]; tail call qword ptr [0xF9A8C78] = _invoke_watson(nullptr,nullptr,nullptr,0,0) via IAT slot (VA 0x14F9A8C78); no reset, no return to epilogue.
        ret = call 0xE935700(rcx = hdr).
reset: self->field_0x10 = 0; self->field_0x18 = 0xF; self->field_0x00 = 0; return ret.

// 0xbc2bde7..0xbc2be12
Epilogue: add rsp,0x28; pop rbx/rdi/rsi/r12/r14/r15; ret.

## Struct fields touched
| offset | size | R/W | meaning | tag |
| 0x00 | 8 | R/W | buffer pointer; read at 0xbc2bda7, written 0 at 0xbc2bde7 | [V] |
| 0x10 | 8 | W | written 0 at 0xbc2bdd7 | [V] |
| 0x18 | 8 | R | capacity; read at 0xbc2bd9d | [V] |
| 0x20 | - | R | address passed to sub_655cea0 at 0xbc2bd98 (&self+0x20) | [V] |
| 0x60 | 8 | R/W | list head pointer; read 0xbc2bd25, written 0 0xbc2bd89 | [V] |
| 0x68 | 8 | R/W | list end pointer; read 0xbc2bd32, written 0 0xbc2bd89 | [V] |
| 0x70 | 8 | W | written 0 at 0xbc2bd8d | [V] |
| 0x88 | 8 | R | refcounted object A; read 0xbc2bcea | [V] |
| 0x90 | 1 | R | flag byte compared with 3 at 0xbc2bce1 | [V] |
| 0x2F8 | 8 | R/W | refcounted object B; read 0xbc2bcb0, written 0 at 0xbc2bcd6 | [V] |
Entry objects at [field_0x60, field_0x68), stride 0x28: +0x8 object ptr (R), +0x18 type byte (R, ==2).

## Callees
- `call qword ptr [0xF99FFA0]` x4 (0xbc2bcd0, 0xbc2bd05, 0xbc2bd1b, 0xbc2bd68, 0xbc2bd7e — actually 5x): slot [data_f99ffa0] = sub_eea6040, a `jmp rax` thunk; each is an indirect virtual call through a vtable slot loaded into rax (slots 4, 0, 1, 0, 1). Not a callee in the lift-set sense; lifted as raw vtable indirect calls.
- `call 0x655CEA0` (0xbc2bd98): sub_655cea0, boundary class stl (docs/data/native_boundary.tsv line 289); called through its native symbol.
- `call 0xE935700` (0xbc2bdd2): sub_e935700 = jmp 0x392960 (sub_392960); effect inlined as notifyGlobal: reads global at VA 0x15233E1A8, invokes its vtable slot 2 when the argument is non-zero. Not lift-set/boundary; no wrapper used.
- `call qword ptr [0xF9A8C78]` (0xbc2be0b): IAT slot of _invoke_watson (api-ms-win-crt-runtime-l1-1-0.dll); called with (0,0,0,0,0) as a tail call. Target resolved from the exe's import table; loaded at runtime via the same slot the original reads.

## Reversed source (complete)

The C++ below is the complete lift (src/client/features/render/native/bgfx/sub_bc2bca0.cpp, first line `// LIFT 0xbc2bca0 size 0x172 1.26.62.01 sub_bc2bca0`). Every block carries its instruction range; every `call` in [0xbc2bca0, 0xbc2be12) is quoted verbatim.

```cpp
// LIFT 0xbc2bca0 size 0x172 1.26.62.01 sub_bc2bca0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc2bca0.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x00) == 0x00);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x10) == 0x10);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x18) == 0x18);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x20) == 0x20);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x60) == 0x60);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x68) == 0x68);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x70) == 0x70);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x88) == 0x88);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x90) == 0x90);
static_assert(offsetof(native::bgfx::sub_bc2bca0_state, field_0x2F8) == 0x2F8);
static_assert(sizeof(native::bgfx::sub_bc2bca0_state) == 0x300);

extern "C" void sub_655cea0(void* container);

// `0xbc2bcd0  call qword ptr [0xF99FFA0]`
// `0xbc2bd05  call qword ptr [0xF99FFA0]`
// `0xbc2bd1b  call qword ptr [0xF99FFA0]`
// `0xbc2bd68  call qword ptr [0xF99FFA0]`
// `0xbc2bd7e  call qword ptr [0xF99FFA0]`
// `0xbc2bd98  call 0x655CEA0`
// `0xbc2bdd2  call 0xE935700`
// `0xbc2be0b  call qword ptr [0xF9A8C78]`

namespace native::bgfx {

static void vtableCallSlot0(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[0])(obj);
}
static void vtableCallSlot1(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[1])(obj);
}
static void vtableCallSlot4(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[4])(obj);
}

static void releaseRefObj(void* obj) {
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(obj) + 8)) == 0) {
        vtableCallSlot0(obj);                           // 0xbc2bd05 / 0xbc2bd68  call qword ptr [0xF99FFA0]
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(obj) + 0xC)) == 0) {
            vtableCallSlot1(obj);                       // 0xbc2bd1b / 0xbc2bd7e      call qword ptr [0xF99FFA0]
        }
    }
}

static uintptr_t notifyGlobal(uint64_t x) {
    if (x == 0) {
        return 0;
    }
    void* global = *reinterpret_cast<void**>(0x15233E1A8);
    void** vt = *reinterpret_cast<void***>(global);
    return reinterpret_cast<uintptr_t (*)(void*)>(vt[2])(global);
}

uintptr_t sub_bc2bca0(sub_bc2bca0_state* self) {
    // 0xbc2bca0..0xbc2bcad: prologue.

    // 0xbc2bcad..0xbc2bce1
    if (self->field_0x2F8 != 0) {
        void* obj2 = self->field_0x2F8;
        // 0xbc2bcbc  lea rax,[rsi+0x2C0]; cmp rcx,rax; setne dl — dl never read.
        vtableCallSlot4(obj2);                          // 0xbc2bcd0  call qword ptr [0xF99FFA0]
    }
    self->field_0x2F8 = 0;                              // 0xbc2bcd6  mov qword ptr [rsi+0x2F8],0

    // 0xbc2bce1..0xbc2bd21
    if (self->field_0x90 == 3) {
        void* obj1 = self->field_0x88;
        if (obj1 != 0) {
            releaseRefObj(obj1);                        // 0xbc2bcf6..0xbc2bd1b
        }
    }

    // 0xbc2bd21..0xbc2bd86
    void* container = &self->field_0x20;
    uint8_t* entry = reinterpret_cast<uint8_t*>(self->field_0x60);
    uint8_t* end = reinterpret_cast<uint8_t*>(self->field_0x68);
    if (entry != 0) {
        while (entry != end) {
            if (reinterpret_cast<sub_bc2bca0_entry*>(entry)->field_0x18 == 2) {
                void* objx = reinterpret_cast<sub_bc2bca0_entry*>(entry)->field_0x08;
                if (objx != 0) {
                    releaseRefObj(objx);                // 0xbc2bd59..0xbc2bd7e
                }
            }
            entry += 0x28;
        }
    }
    self->field_0x60 = 0;                               // 0xbc2bd86..0xbc2bd8d  movups [r15],xmm0 / mov [r15+0x10],0
    self->field_0x68 = 0;
    self->field_0x70 = 0;

    // 0xbc2bd95..0xbc2bd9d
    sub_655cea0(container);                             // 0xbc2bd98  call 0x655CEA0

    // 0xbc2bd9d..0xbc2bde8
    uintptr_t ret;
    uint64_t cap = self->field_0x18;
    if (cap < 0x10) {
        ret = (uintptr_t)cap;
        self->field_0x10 = 0;
        self->field_0x18 = 0xF;
        self->field_0x00 = 0;
        return ret;
    }
    void* ptr = self->field_0x00;
    if (cap + 1 < 0x1000) {
        ret = notifyGlobal((uint64_t)ptr);              // 0xbc2bdd2  call 0xE935700
    } else {
        uint64_t hdr = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptr) - 8);
        uint64_t delta = (reinterpret_cast<uintptr_t>(ptr) - 8) - hdr;
        if (delta >= 0x20) {
            using Watson = uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
            return reinterpret_cast<Watson>(*reinterpret_cast<uintptr_t*>(0x14F9A8C78))(nullptr, nullptr, nullptr, 0, 0);  // 0xbc2be0b  call qword ptr [0xF9A8C78]
        }
        ret = notifyGlobal(hdr);                        // 0xbc2bdd2  call 0xE935700
    }
    self->field_0x10 = 0;
    self->field_0x18 = 0xF;
    self->field_0x00 = 0;
    return ret;
}

static native::Footprint sub_bc2bca0_footprint(sub_bc2bca0_state* self) {
    return { { self, 0x300 } };
}

LIFT_FN(sub_bc2bca0, "sub_bc2bca0", 0xbc2bca0, sub_bc2bca0, sub_bc2bca0_footprint);

} // namespace native::bgfx
```

## Ownership / threading
The function mutates `self` fields and releases refcounted objects it owns references to (field_0x88, field_0x2F8, list-entry objects) via interlocked decrements and virtual calls; sub_655cea0 destroys the container at &self+0x20. No synchronization beyond the interlocked decrements, matching the original. No SEH, no null guards beyond the original's explicit tests.

## Verification
- liftcheck: `python tools/sigs/liftcheck.py 0xbc2bca0` (pending — see docs/progress/oc_U-EX1.bc2bca0.md).
- Quotes verified with `tools/sigs/verify_oc.py`.
