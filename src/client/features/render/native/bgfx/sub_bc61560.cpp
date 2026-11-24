// LIFT 0xbc61560 size 0x372 1.26.62.01 custom item submit (key bit 53)
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc61560.h"

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
//   0xbc61851: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc61887: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xbc618cc: call 0xE951550                                ; -> sub_e951550 -> sub_e951550

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bc61560(/* LIFT-BODY: exact args */);

void sub_bc61560(/* LIFT-BODY: exact args */) {
    // 0xbc61560..0xbc615ba
    LIFT-BODY;  // implement basic block 0xbc61560..0xbc615ba

    // 0xbc615bf..0xbc615ce
    LIFT-BODY;  // implement basic block 0xbc615bf..0xbc615ce

    // 0xbc615d0..0xbc615fd
    LIFT-BODY;  // implement basic block 0xbc615d0..0xbc615fd

    // 0xbc615ff..0xbc61615
    0xbc6160a  call 0xBC60D10                                ; -> sub_bc60d10
    LIFT-BODY;  // implement basic block 0xbc615ff..0xbc61615

    // 0xbc6161a..0xbc6173c
    0xbc616e1  call 0xBC76610                                ; -> sub_bc76610
    LIFT-BODY;  // implement basic block 0xbc6161a..0xbc6173c

    // 0xbc61743..0xbc617a0
    0xbc6176d  call 0xBC7A7C0                                ; -> sub_bc7a7c0
    0xbc6178a  call 0xEEC6EC0                                ; -> sub_eec6ec0
    0xbc617a0  call 0xBC60F10                                ; -> sub_bc60f10
    LIFT-BODY;  // implement basic block 0xbc61743..0xbc617a0

    // 0xbc617a5..0xbc617bd
    LIFT-BODY;  // implement basic block 0xbc617a5..0xbc617bd

    // 0xbc617c0..0xbc61803
    LIFT-BODY;  // implement basic block 0xbc617c0..0xbc61803

    // 0xbc61805..0xbc61828
    LIFT-BODY;  // implement basic block 0xbc61805..0xbc61828

    // 0xbc61830..0xbc61857
    0xbc61851  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc61830..0xbc61857

    // 0xbc6185e..0xbc6186d
    LIFT-BODY;  // implement basic block 0xbc6185e..0xbc6186d

    // 0xbc6186f..0xbc6187a
    LIFT-BODY;  // implement basic block 0xbc6186f..0xbc6187a

    // 0xbc6187c..0xbc61887
    0xbc61887  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xbc6187c..0xbc61887

    // 0xbc6188c..0xbc6188c
    LIFT-BODY;  // implement basic block 0xbc6188c..0xbc6188c

    // 0xbc61896..0xbc61896
    LIFT-BODY;  // implement basic block 0xbc61896..0xbc61896

    // 0xbc6189d..0xbc618c3
    LIFT-BODY;  // implement basic block 0xbc6189d..0xbc618c3

    // 0xbc618c4..0xbc618d1
    0xbc618cc  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbc618c4..0xbc618d1

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bc61560: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc61560, 0xbc618d2) (rdis dis output, two spaces after address):
#if 0
0xbc6160a  call 0xBC60D10                                ; -> sub_bc60d10
0xbc616e1  call 0xBC76610                                ; -> sub_bc76610
0xbc6176d  call 0xBC7A7C0                                ; -> sub_bc7a7c0
0xbc6178a  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbc617a0  call 0xBC60F10                                ; -> sub_bc60f10
0xbc61851  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc61887  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xbc618cc  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   sub_bc60d10 (0xbc60d10, lift set) - call 0xBC60D10                                ; -> sub_bc60d10
//   sub_bc76610 (0xbc76610, lift set) - call 0xBC76610                                ; -> sub_bc76610
//   sub_bc7a7c0 (0xbc7a7c0, lift set) - call 0xBC7A7C0                                ; -> sub_bc7a7c0
//   sub_eec6ec0 (0xeec6ec0, lift set) - call 0xEEC6EC0                                ; -> sub_eec6ec0
//   sub_bc60f10 (0xbc60f10, lift set) - call 0xBC60F10                                ; -> sub_bc60f10
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bc61560, "sub_bc61560", 0xbc61560, sub_bc61560, nullptr);

} // namespace native::bgfx