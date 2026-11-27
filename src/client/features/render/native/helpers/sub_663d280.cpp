// LIFT 0x663d280 size 0xf6 1.26.62.01 sub_663d280
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_663d280.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_663d280, "sub_663d280", 0x663d280, sub_663d280, nullptr);

// Boundary callee: sub_eea6040, vendor thunk via data slot 0xF99FFA0
// (docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)").
// The thunk is `jmp rax`; RAX must hold the target function pointer on entry.
// Called with (rcx = object, rdx = vfptr entry); return value ignored.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Verbatim call instructions from the disassembly of [0x663d280, 0x663d376) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x663d2bf  call qword ptr [0xF99FFA0]
0x663d2d5  call qword ptr [0xF99FFA0]
0x663d2fd  call qword ptr [0xF99FFA0]
0x663d313  call qword ptr [0xF99FFA0]
0x663d341  call qword ptr [0xF99FFA0]
0x663d357  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x663d280, 0x663d376) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

static_assert(offsetof(sub_663d280_rdx, obj50) == 0x50, "sub_663d280 obj50 at +0x50");
static_assert(offsetof(sub_663d280_rdx, flag58) == 0x58, "sub_663d280 flag58 at +0x58");
static_assert(offsetof(sub_663d280_rdx, obj68) == 0x68, "sub_663d280 obj68 at +0x68");
static_assert(offsetof(sub_663d280_rdx, flag70) == 0x70, "sub_663d280 flag70 at +0x70");
static_assert(offsetof(sub_663d280_rdx, obj80) == 0x80, "sub_663d280 obj80 at +0x80");
static_assert(offsetof(sub_663d280_rdx, flag88) == 0x88, "sub_663d280 flag88 at +0x88");
static_assert(offsetof(sub_663d280_rdx, field90) == 0x90, "sub_663d280 field90 at +0x90");

uintptr_t sub_663d280(void* a1, void* self)
{
    (void)a1;  // RCX (first parameter) is never read; object base comes from RDX (0x663d286 mov rsi,rdx)

    std::uint8_t* const s = reinterpret_cast<std::uint8_t*>(self);

    // 0x663d280..0x663d28f: block 0 — prologue, flag58 test
    // 0x663d28f..0x663d295: block 1 — flag70 test
    // 0x663d295..0x663d2a2: block 2 — flag88 test
    // 0x663d2a2..0x663d2a7: block 3 — jmp to end

    // Release refcounted object at +0x50 when flag58 == 1.
    // 0x663d2a7..0x663d2b0: block 4 — load obj50, null test
    // 0x663d2b0..0x663d2b6: block 5 — lock dec refcount, test zero
    // 0x663d2b6..0x663d2cb: block 6 — destructor vfptr[0], lock dec count0xC
    // 0x663d2cb..0x663d2db: block 7 — operator delete vfptr[1]
    // 0x663d2db..0x663d2e5: block 8 — clear flag58, test flag70
    if (*reinterpret_cast<std::uint8_t*>(s + 0x58) == 1) {
        void* const obj = *reinterpret_cast<void**>(s + 0x50);
        if (obj != nullptr) {
            std::uint8_t* const o = reinterpret_cast<std::uint8_t*>(obj);
            if (_InterlockedDecrement(
                    reinterpret_cast<volatile long*>(o + 8)) == 0) {
                void** const vfptr = *reinterpret_cast<void***>(obj);
                sub_eea6040(obj, vfptr[0]);   // 0x663d2bf  call qword ptr [0xF99FFA0]
                if (_InterlockedDecrement(
                        reinterpret_cast<volatile long*>(o + 0xC)) == 0) {
                    sub_eea6040(obj, vfptr[1]);   // 0x663d2d5  call qword ptr [0xF99FFA0]
                }
            }
        }
        *reinterpret_cast<std::uint8_t*>(s + 0x58) = 0;
    }

    // 0x663d2e5..0x663d2ee: block 9 — load obj68, null test
    // 0x663d2ee..0x663d2f4: block 10 — lock dec refcount, test zero
    // 0x663d2f4..0x663d309: block 11 — destructor vfptr[0], lock dec count0xC
    // 0x663d309..0x663d319: block 12 — operator delete vfptr[1]
    // 0x663d319..0x663d326: block 13 — clear flag70, test flag88
    if (*reinterpret_cast<std::uint8_t*>(s + 0x70) == 1) {
        void* const obj = *reinterpret_cast<void**>(s + 0x68);
        if (obj != nullptr) {
            std::uint8_t* const o = reinterpret_cast<std::uint8_t*>(obj);
            if (_InterlockedDecrement(
                    reinterpret_cast<volatile long*>(o + 8)) == 0) {
                void** const vfptr = *reinterpret_cast<void***>(obj);
                sub_eea6040(obj, vfptr[0]);   // 0x663d2fd  call qword ptr [0xF99FFA0]
                if (_InterlockedDecrement(
                        reinterpret_cast<volatile long*>(o + 0xC)) == 0) {
                    sub_eea6040(obj, vfptr[1]);   // 0x663d313  call qword ptr [0xF99FFA0]
                }
            }
        }
        *reinterpret_cast<std::uint8_t*>(s + 0x70) = 0;
    }

    // 0x663d326..0x663d332: block 14 — load obj80, null test
    // 0x663d332..0x663d338: block 15 — lock dec refcount, test zero
    // 0x663d338..0x663d34d: block 16 — destructor vfptr[0], lock dec count0xC
    // 0x663d34d..0x663d35d: block 17 — operator delete vfptr[1]
    // 0x663d35d..0x663d364: block 18 — clear flag88
    if (*reinterpret_cast<std::uint8_t*>(s + 0x88) == 1) {
        void* const obj = *reinterpret_cast<void**>(s + 0x80);
        if (obj != nullptr) {
            std::uint8_t* const o = reinterpret_cast<std::uint8_t*>(obj);
            if (_InterlockedDecrement(
                    reinterpret_cast<volatile long*>(o + 8)) == 0) {
                void** const vfptr = *reinterpret_cast<void***>(obj);
                sub_eea6040(obj, vfptr[0]);   // 0x663d341  call qword ptr [0xF99FFA0]
                if (_InterlockedDecrement(
                        reinterpret_cast<volatile long*>(o + 0xC)) == 0) {
                    sub_eea6040(obj, vfptr[1]);   // 0x663d357  call qword ptr [0xF99FFA0]
                }
            }
        }
        *reinterpret_cast<std::uint8_t*>(s + 0x88) = 0;
    }

    // 0x663d364..0x663d376: block 19 — clear field90, epilogue, ret
    *reinterpret_cast<std::uint64_t*>(s + 0x90) = 0;
    return 0;
}

} // namespace native::helpers
