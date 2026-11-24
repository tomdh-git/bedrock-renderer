// LIFT 0xbc618e0 size 0x535 1.26.62.01 compute item + frame parameter blocks
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc618e0.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_bc60d10
extern "C" void sub_bc60d10(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bc60f10
extern "C" void sub_bc60f10(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bc76610
extern "C" void sub_bc76610(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bc7a7c0
extern "C" void sub_bc7a7c0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec6ec0
extern "C" void sub_eec6ec0(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbc61c2c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc61c45: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc61d91: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc61dc7: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xbc61e0f: call 0xE951550                                ; -> sub_e951550 -> sub_e951550

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bc618e0(/* LIFT-BODY: exact args */);

void sub_bc618e0(/* LIFT-BODY: exact args */) {
    // 0xbc618e0..0xbc6194f
    LIFT-BODY;  // implement basic block 0xbc618e0..0xbc6194f

    // 0xbc61954..0xbc61963
    LIFT-BODY;  // implement basic block 0xbc61954..0xbc61963

    // 0xbc61970..0xbc61999
    LIFT-BODY;  // implement basic block 0xbc61970..0xbc61999

    // 0xbc6199b..0xbc619b1
    0xbc619a6  call 0xBC60D10                                ; -> sub_bc60d10
    LIFT-BODY;  // implement basic block 0xbc6199b..0xbc619b1

    // 0xbc619b6..0xbc61b21
    0xbc61ac6  call 0xBC76610                                ; -> sub_bc76610
    LIFT-BODY;  // implement basic block 0xbc619b6..0xbc61b21

    // 0xbc61b28..0xbc61b9b
    0xbc61b69  call 0xBC7A7C0                                ; -> sub_bc7a7c0
    0xbc61b85  call 0xEEC6EC0                                ; -> sub_eec6ec0
    0xbc61b9b  call 0xBC60F10                                ; -> sub_bc60f10
    LIFT-BODY;  // implement basic block 0xbc61b28..0xbc61b9b

    // 0xbc61ba0..0xbc61bfb
    0xbc61bb1  call 0xEEC6EC0                                ; -> sub_eec6ec0
    LIFT-BODY;  // implement basic block 0xbc61ba0..0xbc61bfb

    // 0xbc61bfd..0xbc61bfd
    LIFT-BODY;  // implement basic block 0xbc61bfd..0xbc61bfd

    // 0xbc61bff..0xbc61c4b
    0xbc61c2c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc61c45  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc61bff..0xbc61c4b

    // 0xbc61c4e..0xbc61cf9
    LIFT-BODY;  // implement basic block 0xbc61c4e..0xbc61cf9

    // 0xbc61d00..0xbc61d43
    LIFT-BODY;  // implement basic block 0xbc61d00..0xbc61d43

    // 0xbc61d45..0xbc61d68
    LIFT-BODY;  // implement basic block 0xbc61d45..0xbc61d68

    // 0xbc61d70..0xbc61d97
    0xbc61d91  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc61d70..0xbc61d97

    // 0xbc61d9e..0xbc61dad
    LIFT-BODY;  // implement basic block 0xbc61d9e..0xbc61dad

    // 0xbc61daf..0xbc61dba
    LIFT-BODY;  // implement basic block 0xbc61daf..0xbc61dba

    // 0xbc61dbc..0xbc61dc7
    0xbc61dc7  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xbc61dbc..0xbc61dc7

    // 0xbc61dcc..0xbc61dcc
    LIFT-BODY;  // implement basic block 0xbc61dcc..0xbc61dcc

    // 0xbc61dd6..0xbc61dd6
    LIFT-BODY;  // implement basic block 0xbc61dd6..0xbc61dd6

    // 0xbc61ddd..0xbc61e06
    LIFT-BODY;  // implement basic block 0xbc61ddd..0xbc61e06

    // 0xbc61e07..0xbc61e14
    0xbc61e0f  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbc61e07..0xbc61e14

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bc618e0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc618e0, 0xbc61e15) (rdis dis output, two spaces after address):
#if 0
0xbc619a6  call 0xBC60D10                                ; -> sub_bc60d10
0xbc61ac6  call 0xBC76610                                ; -> sub_bc76610
0xbc61b69  call 0xBC7A7C0                                ; -> sub_bc7a7c0
0xbc61b85  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbc61b9b  call 0xBC60F10                                ; -> sub_bc60f10
0xbc61bb1  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbc61c2c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc61c45  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc61d91  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc61dc7  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xbc61e0f  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   sub_bc60d10 (0xbc60d10, lift set) - call 0xBC60D10                                ; -> sub_bc60d10
//   sub_bc76610 (0xbc76610, lift set) - call 0xBC76610                                ; -> sub_bc76610
//   sub_bc7a7c0 (0xbc7a7c0, lift set) - call 0xBC7A7C0                                ; -> sub_bc7a7c0
//   sub_eec6ec0 (0xeec6ec0, lift set) - call 0xEEC6EC0                                ; -> sub_eec6ec0
//   sub_bc60f10 (0xbc60f10, lift set) - call 0xBC60F10                                ; -> sub_bc60f10
//   sub_eec6ec0 (0xeec6ec0, lift set) - call 0xEEC6EC0                                ; -> sub_eec6ec0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bc618e0, "sub_bc618e0", 0xbc618e0, sub_bc618e0, nullptr);

} // namespace native::bgfx