// LIFT 0xbc8c720 size 0x167 1.26.62.01 sub_bc8c720
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc8c720.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions for every struct offset this function touches (defined in
// sub_bc8c720.h; repeated here so liftcheck finds them in the source file).
static_assert(offsetof(sub_bc8c720_state, field_0x00) == 0x00, "sub_0xbc8c720: self+0x00");
static_assert(offsetof(sub_bc8c720_state, field_0x10) == 0x10, "sub_0xbc8c720: self+0x10");
static_assert(offsetof(sub_bc8c720_state, field_0x18) == 0x18, "sub_0xbc8c720: self+0x18");
static_assert(offsetof(sub_bc8c720_state, field_0x28) == 0x28, "sub_0xbc8c720: self+0x28");
static_assert(offsetof(sub_bc8c720_state, field_0x30) == 0x30, "sub_0xbc8c720: self+0x30");
static_assert(offsetof(sub_bc8c720_state, field_0x38) == 0x38, "sub_0xbc8c720: self+0x38");
static_assert(offsetof(sub_bc8c720_state, field_0x50) == 0x50, "sub_0xbc8c720: self+0x50");
static_assert(offsetof(sub_bc8c720_state, field_0x58) == 0x58, "sub_0xbc8c720: self+0x58");
static_assert(offsetof(sub_bc8c720_state, field_0x78) == 0x78, "sub_0xbc8c720: self+0x78");
static_assert(offsetof(sub_bc8c720_state, field_0x2F0) == 0x2F0, "sub_0xbc8c720: self+0x2F0");
static_assert(sizeof(sub_bc8c720_state) == 0x2F8, "sub_0xbc8c720 object size");
static_assert(offsetof(sub_bc8c720_entry, field_0x08) == 0x08, "list entry object at +0x08");
static_assert(offsetof(sub_bc8c720_entry, field_0x18) == 0x18, "list entry type byte at +0x18");
static_assert(sizeof(sub_bc8c720_entry) == 0x28, "list entry stride");

// Reversed from the disassembly of [0xbc8c720, 0xbc8c887), Minecraft Windows 1.26.62.01
// (rdis dis output, docs/progress/pre/bc8c720_dis.txt). Every block carries the
// instruction range it implements as // 0xA..0xB beside it; every call is quoted
// verbatim in the verbatim log below.
//
// This is the exact twin of bgfx/sub_bc2bca0.cpp: same two indirect-call slots
// [0xF99FFA0] (sub_eea6040, `jmp rax` vtable thunk) and [0xF9A8C78] (_invoke_watson
// IAT slot), same strong-refcount release pattern (lock dec [obj+8]; vtable[0]; lock
// dec [obj+0xC]; vtable[1]), and same sub_e935700 (0xE935700 = jmp 0x392960 ->
// sub_392960) notification. The object layout differs only in field offsets.
//
// Boundaries and lift-set callees:
//   sub_e935700 x2 is a lift-set callee (docs/data/native_boundary.tsv line 505,
//   class lift), declared in sub_bc8c720.h and called as plain C++.
//   [0xF99FFA0] (sub_eea6040, vendor thunk via data slot, boundary.tsv line 506) is an
//   indirect virtual call whose target the original already loaded into rax; modelled
//   as vtable slot calls through function pointers (same convention as sub_bc2bca0).
//   [0xF9A8C78] (_invoke_watson IAT slot, read at VA 0x14F9A8C78 at call time) is
//   modelled as a function-pointer call through the slot (boundary hard rule:
//   indirect call through a data slot).
// Verbatim call instructions from the disassembly of [0xbc8c720, 0xbc8c887)
// (rdis dis output, copied verbatim, two spaces after the address):
//   0xbc8c74e  call qword ptr [0xF99FFA0]
//   0xbc8c76d  call 0xE935700
//   0xbc8c790  call qword ptr [0xF99FFA0]
//   0xbc8c7a6  call qword ptr [0xF99FFA0]
//   0xbc8c7e7  call qword ptr [0xF99FFA0]
//   0xbc8c7fd  call qword ptr [0xF99FFA0]
//   0xbc8c849  call 0xE935700
//   0xbc8c880  call qword ptr [0xF9A8C78]
// UNRESOLVED CALL = none: every target above is either a lift-set callee (sub_e935700)
// or an indirect call through a documented data slot ([0xF99FFA0] vtable thunk,
// [0xF9A8C78] _invoke_watson IAT slot).

namespace native::bgfx {

// sub_eea6040 ([data_f99ffa0]) is a `jmp rax` thunk, so each `call qword ptr
// [0xF99FFA0]` above is an indirect virtual call whose target (vtable slot) the
// original already loaded into rax. Reads: [obj] (vtable pointer) and
// [vtable + slot*8]; call: target(obj) with rcx = obj.
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

// Strong-refcount release pattern used for field_0x50 and for list-entry objects:
// lock dec [obj+8]; if zero: vtable[0](obj); lock dec [obj+0xC]; if zero: vtable[1](obj).
// Matches 0xbc8c781..0xbc8c7a6 (field_0x50) and 0xbc8c7d8..0xbc8c7fd (list entries).
static void releaseRefObj(void* obj) {
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(obj) + 8)) == 0) {
        vtableCallSlot0(obj);                           // 0xbc8c790 / 0xbc8c7e7  call qword ptr [0xF99FFA0]
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(obj) + 0xC)) == 0) {
            vtableCallSlot1(obj);                       // 0xbc8c7a6 / 0xbc8c7fd      call qword ptr [0xF99FFA0]
        }
    }
}

// sub_e935700(self->field_0x78) notification; the original sets edx=0x88 before the
// call at 0xbc8c768 but sub_392960 overwrites rdx=rcx on entry, so edx is dead.
// Return value ignored at the 0xbc8c76d call site.
static void notifyField78(sub_bc8c720_state* self) {
    if (self->field_0x78 != 0) {
        sub_e935700(self->field_0x78);                  // 0xbc8c76d  call 0xE935700
    }
}

// sub_0xbc8c720(sub_bc8c720_state* self = rcx) -> uintptr_t (rax).
//   0xbc8c720..0xbc8c754: prologue; release field_0x2F0 refcounted object
//     (vtable[4] then zero the pointer); the lea/cmp/setne on [rsi+0x2B8] computes a
//     result (dl) that is never read, so it has no observable effect.
//   0xbc8c75f..0xbc8c76d: if field_0x78 != 0: sub_e935700(field_0x78).
//   0xbc8c772..0xbc8c7a6: if byte[field_0x58] == 3: releaseRefObj(field_0x50).
//   0xbc8c7ac..0xbc8c80c: release every list entry [field_0x28,field_0x30) of type 2,
//     then zero field_0x28/0x30/0x38.
//   0xbc8c814..0xbc8c849: if field_0x18 < 0x10 -> ret = field_0x18; else if
//     field_0x18+1 < 0x1000 -> ret = sub_e935700(field_0x00); else heap-header check:
//     delta = (field_0x00-8) - [field_0x00-8]; delta >= 0x20 -> _invoke_watson;
//     else ret = sub_e935700([field_0x00-8]).
//   0xbc8c84e..0xbc8c86c: reset field_0x10=0, field_0x18=0xF, field_0x00=0; return rax.
//   0xbc8c86d..0xbc8c886: zero [rsp+0x20]/ecx/edx/r8d/r9d then
//     call qword ptr [0xF9A8C78] -> _invoke_watson(nullptr,nullptr,nullptr,0,0)
//     (noreturn; int3 padding follows).
uintptr_t sub_bc8c720(sub_bc8c720_state* self) {
    // 0xbc8c720..0xbc8c754
    if (self->field_0x2F0 != 0) {
        void* obj2 = self->field_0x2F0;
        vtableCallSlot4(obj2);                          // 0xbc8c74e  call qword ptr [0xF99FFA0] (vtable[4](obj2), rcx = obj2)
    }
    self->field_0x2F0 = 0;                              // 0xbc8c754  mov qword ptr [rsi+0x2F0],0

    // 0xbc8c75f..0xbc8c76d
    notifyField78(self);                                // 0xbc8c76d  call 0xE935700

    // 0xbc8c772..0xbc8c7a6
    if (self->field_0x58 == 3) {                        // 0xbc8c772  cmp byte ptr [rsi+0x58],3
        void* obj1 = self->field_0x50;                  // 0xbc8c778  mov rdi,[rsi+0x50]
        if (obj1 != 0) {                                // 0xbc8c77c  test rdi,rdi
            releaseRefObj(obj1);                        // 0xbc8c781..0xbc8c7a6
        }
    }

    // 0xbc8c7ac..0xbc8c80c
    void* head = self->field_0x28;                      // 0xbc8c7ac  mov rbx,[rsi+0x28]
    void* end = self->field_0x30;                       // 0xbc8c7b9  mov r15,[rsi+0x30]
    if (head != 0) {
        uint8_t* entry = reinterpret_cast<uint8_t*>(head);
        uint8_t* endPtr = reinterpret_cast<uint8_t*>(end);
        while (entry != endPtr) {                       // 0xbc8c7c4  cmp rbx,r15; je 0xBC8C805
            if (reinterpret_cast<sub_bc8c720_entry*>(entry)->field_0x18 == 2) {  // 0xbc8c7c9  cmp byte ptr [rbx+0x18],2
                void* objx = reinterpret_cast<sub_bc8c720_entry*>(entry)->field_0x08;  // 0xbc8c7cf  mov rdi,[rbx+8]
                if (objx != 0) {                        // 0xbc8c7d3  test rdi,rdi
                    releaseRefObj(objx);                // 0xbc8c7d8..0xbc8c7fd
                }
            }
            entry += 0x28;                              // 0xbc8c7c0  add rbx,0x28
        }
    }
    self->field_0x28 = 0;                               // 0xbc8c805  xorps xmm0,xmm0; 0xbc8c808  movups [r14],xmm0
    self->field_0x30 = 0;
    self->field_0x38 = 0;                               // 0xbc8c80c  mov qword ptr [r14+0x10],0

    // 0xbc8c814..0xbc8c849
    uintptr_t ret;
    uint64_t cap = self->field_0x18;                    // 0xbc8c814  mov rax,[rsi+0x18]
    if (cap < 0x10) {                                   // 0xbc8c818  cmp rax,0x10; jb 0xBC8C84E
        ret = (uintptr_t)cap;                           // rax still holds cap
    } else {
        void* ptr = self->field_0x00;                   // 0xbc8c81e  mov rcx,[rsi]
        if (cap + 1 < 0x1000) {                         // 0xbc8c821  lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC8C849
            ret = sub_e935700((uint64_t)ptr);           // 0xbc8c849  call 0xE935700 (rcx = ptr)
        } else {
            uint64_t hdr = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptr) - 8);  // 0xbc8c82e  mov r8,[rcx-8]
            uint64_t delta = (reinterpret_cast<uintptr_t>(ptr) - 8) - hdr;          // 0xbc8c832  add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8
            if (delta >= 0x20) {                        // 0xbc8c839  cmp rcx,0x20; jae 0xBC8C86D
                // 0xbc8c86d..0xbc8c886: zero [rsp+0x20], ecx, edx, r8d, r9d, then
                // 0xbc8c880  call qword ptr [0xF9A8C78] -> _invoke_watson(nullptr,nullptr,nullptr,0,0)
                using Watson = uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
                return reinterpret_cast<Watson>(*reinterpret_cast<uintptr_t*>(0x14F9A8C78))(nullptr, nullptr, nullptr, 0, 0);
            }
            ret = sub_e935700(hdr);                     // 0xbc8c849  call 0xE935700 (rcx = hdr)
        }
    }

    // 0xbc8c84e..0xbc8c86c
    self->field_0x10 = 0;                               // 0xbc8c84e  mov qword ptr [rsi+0x10],0
    self->field_0x18 = 0xF;                             // 0xbc8c856  mov qword ptr [rsi+0x18],0xF
    *reinterpret_cast<uint8_t*>(&self->field_0x00) = 0; // 0xbc8c85e  mov byte ptr [rsi],0
    // 0xbc8c861..0xbc8c86c  add rsp,0x30; pop rbx/rdi/rsi/r14/r15; ret  (rax = ret)
    return ret;
}

static native::Footprint sub_bc8c720_footprint(sub_bc8c720_state* self) {
    // Conservative: every byte written to *self. Refcount writes to other objects
    // (via the virtual calls above) are outside this footprint, same as the
    // original's out-of-function side effects; they cannot be declared statically.
    return { { self, 0x2F8 } };
}

LIFT_FN(sub_bc8c720, "sub_bc8c720", 0xbc8c720, sub_bc8c720, sub_bc8c720_footprint);

} // namespace native::bgfx
