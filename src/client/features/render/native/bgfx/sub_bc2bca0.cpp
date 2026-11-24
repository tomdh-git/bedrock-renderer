// LIFT 0xbc2bca0 size 0x172 1.26.62.01 sub_bc2bca0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc2bca0.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_bc2bca0.h; repeated here so liftcheck sees them in the source file).
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

// sub_655cea0 is in docs/data/native_boundary.tsv (class stl, line 289). Per the repository
// convention (see bgfx/sub_bc40a30.cpp) CRT/stl/alloc callees are called through their native
// symbol as plain extern "C" functions; the call is quoted verbatim below. Return value ignored.
extern "C" void sub_655cea0(void* container);

// Verbatim call instructions from the disassembly of [0xbc2bca0, 0xbc2be12) (rdis dis output).
// Targets: sub_eea6040 via data slot [0xF99FFA0] (a `jmp rax` thunk: each call is an indirect
// virtual call through a vtable slot already loaded into rax); sub_655cea0 (boundary, stl,
// called through its native symbol); sub_e935700 (= jmp 0x392960 -> sub_392960: reads the global
// at VA 0x15233E1A8 and invokes its vtable slot 2 when its argument is non-zero); and [0xF9A8C78],
// the IAT slot of _invoke_watson (api-ms-win-crt-runtime-l1-1-0.dll, loader-patched at runtime).
// No lift-set callees. UNRESOLVED CALL = none.
// 0xbc2bcd0  call qword ptr [0xF99FFA0]
// 0xbc2bd05  call qword ptr [0xF99FFA0]
// 0xbc2bd1b  call qword ptr [0xF99FFA0]
// 0xbc2bd68  call qword ptr [0xF99FFA0]
// 0xbc2bd7e  call qword ptr [0xF99FFA0]
// 0xbc2bd98  call 0x655CEA0
// 0xbc2bdd2  call 0xE935700
// 0xbc2be0b  call qword ptr [0xF9A8C78]

namespace native::bgfx {

// sub_eea6040 ([data_f99ffa0]) is a `jmp rax` thunk, so each `call qword ptr [0xF99FFA0]`
// above is an indirect virtual call whose target (vtable slot) the original already loaded
// into rax. Reads: [obj] (vtable pointer) and [vtable + slot*8]; call: target(obj) with rcx=obj.
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

// Strong-refcount release pattern used for field_0x88 and for list-entry objects:
// lock dec [obj+8]; if zero: vtable[0](obj); lock dec [obj+0xC]; if zero: vtable[1](obj).
// Matches 0xbc2bcf6..0xbc2bd05 and 0xbc2bd0b..0xbc2bd1b (field_0x88) and
// 0xbc2bd59..0xbc2bd68 / 0xbc2bd6e..0xbc2bd7e (list entries).
static void releaseRefObj(void* obj) {
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(obj) + 8)) == 0) {
        vtableCallSlot0(obj);                           // 0xbc2bd05 / 0xbc2bd68  call qword ptr [0xF99FFA0]
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(obj) + 0xC)) == 0) {
            vtableCallSlot1(obj);                       // 0xbc2bd1b / 0xbc2bd7e      call qword ptr [0xF99FFA0]
        }
    }
}

// sub_e935700 = jmp 0x392960 -> sub_392960:
//   mov rdx,rcx; mov rcx,[VA 0x15233E1A8]; test rdx,rdx; je return(0);
//   rax = (*(void**)rcx)[0x10] via jmp-rax thunk; call rax(rcx); return rax.
// VA 0x15233E1A8 = image base 0x140000000 + RVA 0x1233E1A8 (the exe loads at its fixed base).
static uintptr_t notifyGlobal(uint64_t x) {
    if (x == 0) {
        return 0;                                       // rax still holds x == 0
    }
    void* global = *reinterpret_cast<void**>(0x15233E1A8);
    void** vt = *reinterpret_cast<void***>(global);
    return reinterpret_cast<uintptr_t (*)(void*)>(vt[2])(global);  // slot 2 at +0x10
}

// sub_0xbc2bca0(sub_bc2bca0_state* self = rcx) -> uintptr_t (rax).
// Every block carries the instruction range it implements; every call is quoted verbatim above.
uintptr_t sub_bc2bca0(sub_bc2bca0_state* self) {
    // 0xbc2bca0..0xbc2bcad: prologue (push r15/r14/r12/rsi/rdi/rbx, sub rsp,0x28, mov rsi,rcx) — no observable effect.

    // 0xbc2bcad..0xbc2bce1
    if (self->field_0x2F8 != 0) {                       // 0xbc2bcb0  mov rcx,[rcx+0x2F8]; 0xbc2bcb7  test rcx,rcx; 0xbc2bcba  je
        void* obj2 = self->field_0x2F8;
        // 0xbc2bcbc  lea rax,[rsi+0x2C0]; 0xbc2bcc3  cmp rcx,rax; 0xbc2bcc6  setne dl — result (dl) is never read: no observable effect.
        vtableCallSlot4(obj2);                          // 0xbc2bcc9..0xbc2bcd0  call qword ptr [0xF99FFA0]  (vtable[4](obj2), rcx = obj2)
    }
    self->field_0x2F8 = 0;                              // 0xbc2bcd6  mov qword ptr [rsi+0x2F8],0

    // 0xbc2bce1..0xbc2bd21
    if (self->field_0x90 == 3) {                        // 0xbc2bce1  cmp byte ptr [rsi+0x90],3; 0xbc2bce8  jne
        void* obj1 = self->field_0x88;                  // 0xbc2bcea  mov rdi,[rsi+0x88]
        if (obj1 != 0) {                                // 0xbc2bcf1  test rdi,rdi; 0xbc2bcf4  je
            releaseRefObj(obj1);                        // 0xbc2bcf6..0xbc2bd1b
        }
    }

    // 0xbc2bd21..0xbc2bd86
    void* container = &self->field_0x20;                // 0xbc2bd21  lea rdi,[rsi+0x20]
    uint8_t* entry = reinterpret_cast<uint8_t*>(self->field_0x60);  // 0xbc2bd25  mov r14,[rsi+0x60]
    uint8_t* end = reinterpret_cast<uint8_t*>(self->field_0x68);    // 0xbc2bd32  mov r12,[rsi+0x68]
    if (entry != 0) {                                   // 0xbc2bd29  test r14,r14; 0xbc2bd2c  je
        while (entry != end) {                          // 0xbc2bd36  jmp 0xBC2BD44; 0xbc2bd44  cmp r14,r12; 0xbc2bd47  je
            // 0xbc2bd40  add r14,0x28 (loop back-edge target)
            if (reinterpret_cast<sub_bc2bca0_entry*>(entry)->field_0x18 == 2) {  // 0xbc2bd49  cmp byte ptr [r14+0x18],2; 0xbc2bd4e  jne
                void* objx = reinterpret_cast<sub_bc2bca0_entry*>(entry)->field_0x08;  // 0xbc2bd50  mov rbx,[r14+8]
                if (objx != 0) {                        // 0xbc2bd54  test rbx,rbx; 0xbc2bd57  je
                    releaseRefObj(objx);                // 0xbc2bd59..0xbc2bd7e
                }
            }
            entry += 0x28;                              // 0xbc2bd40  add r14,0x28
        }
    }
    self->field_0x60 = 0;                               // 0xbc2bd86  xorps xmm0,xmm0; 0xbc2bd89  movups [r15],xmm0  (zeroes [0x60,0x70))
    self->field_0x68 = 0;
    self->field_0x70 = 0;                               // 0xbc2bd8d  mov qword ptr [r15+0x10],0

    // 0xbc2bd95..0xbc2bd9d
    sub_655cea0(container);                             // 0xbc2bd95  mov rcx,rdi; 0xbc2bd98  call 0x655CEA0  (boundary stl; return ignored)

    // 0xbc2bd9d..0xbc2bde8
    uintptr_t ret;
    uint64_t cap = self->field_0x18;                    // 0xbc2bd9d  mov rax,[rsi+0x18]
    if (cap < 0x10) {                                   // 0xbc2bda1  cmp rax,0x10; 0xbc2bda5  jb
        ret = (uintptr_t)cap;                           // rax still holds cap
        self->field_0x10 = 0;                           // 0xbc2bdd7..0xbc2bde7: reset
        self->field_0x18 = 0xF;
        self->field_0x00 = 0;
        return ret;                                     // 0xbc2bdea..0xbc2bdf7: epilogue, rax = ret
    }
    void* ptr = self->field_0x00;                       // 0xbc2bda7  mov rcx,[rsi]
    if (cap + 1 < 0x1000) {                             // 0xbc2bdaa  lea rdx,[rax+1]; 0xbc2bdae  cmp rdx,0x1000; 0xbc2bdb5  jb
        ret = notifyGlobal((uint64_t)ptr);              // 0xbc2bdd2  call 0xE935700  (rcx = ptr)
    } else {
        uint64_t hdr = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptr) - 8);  // 0xbc2bdb7  mov r8,[rcx-8]
        uint64_t delta = (reinterpret_cast<uintptr_t>(ptr) - 8) - hdr;                  // 0xbc2bdbb  add rcx,0xFFFFFFFFFFFFFFF8; 0xbc2bdbf  sub rcx,r8
        if (delta >= 0x20) {                            // 0xbc2bdc2  cmp rcx,0x20; 0xbc2bdc6  jae 0xBC2BDF8
            // 0xbc2bdf8..0xbc2be08: zero [rsp+0x20], ecx, edx, r8d, r9d, then
            // 0xbc2be0b  call qword ptr [0xF9A8C78]  -> _invoke_watson(nullptr,nullptr,nullptr,0,0)
            // The IAT slot at VA 0x14F9A8C78 (image base 0x140000000 + RVA 0xF9A8C78) holds
            // _invoke_watson's loader-patched address at runtime (import of api-ms-win-crt-runtime-l1-1-0.dll).
            using Watson = uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
            return reinterpret_cast<Watson>(*reinterpret_cast<uintptr_t*>(0x14F9A8C78))(nullptr, nullptr, nullptr, 0, 0);
        }
        ret = notifyGlobal(hdr);                        // 0xbc2bdd2  call 0xE935700  (rcx = hdr; rdx = cap + 0x28, unused by sub_392960)
    }
    self->field_0x10 = 0;                               // 0xbc2bdd7  mov qword ptr [rsi+0x10],0
    self->field_0x18 = 0xF;                             // 0xbc2bddf  mov qword ptr [rsi+0x18],0xF
    self->field_0x00 = 0;                               // 0xbc2bde7  mov byte ptr [rsi],0
    return ret;                                         // 0xbc2bdea..0xbc2bdf7: add rsp,0x28; pop rbx/rdi/rsi/r12/r14/r15; ret  (rax = ret)
}

static native::Footprint sub_bc2bca0_footprint(sub_bc2bca0_state* self) {
    // Conservative: every byte written to *self. Refcount writes to other objects (via the
    // virtual calls above) and [VA 0x15233E1A8] (via notifyGlobal) are outside this footprint,
    // same as the original's out-of-function side effects; they cannot be declared statically.
    return { { self, 0x300 } };
}

LIFT_FN(sub_bc2bca0, "sub_bc2bca0", 0xbc2bca0, sub_bc2bca0, sub_bc2bca0_footprint);

} // namespace native::bgfx
