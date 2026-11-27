// LIFT 0xbc61140 size 0x411 1.26.62.01 EncoderImpl::dispatch (compute), fully reversed

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc61140.h"

#include <cstdint>
#include <cstring>
// Forward declarations (autofix)
struct sub_eec6ec0;


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

//   0xbc614d1: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)

//   0xbc61507: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0

//   0xbc6154b: call 0xE951550                                ; -> sub_e951550 -> sub_e951550


} // namespace


// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original

extern "C" void sub_bc61140(/* LIFT-BODY: exact args */);

void sub_bc61140(/* LIFT-BODY: exact args */) {
    // 0xbc61140..0xbc611a7

    LIFT-BODY;  // implement basic block 0xbc61140..0xbc611a7


    // 0xbc611ac..0xbc611bb

    LIFT-BODY;  // implement basic block 0xbc611ac..0xbc611bb


    // 0xbc611c0..0xbc611e9

    LIFT-BODY;  // implement basic block 0xbc611c0..0xbc611e9


    // 0xbc611eb..0xbc61201

    0xbc611f6  call 0xBC60D10                                ; -> sub_bc60d10
    LIFT-BODY;  // implement basic block 0xbc611eb..0xbc61201


    // 0xbc61206..0xbc61372

    0xbc61317  call 0xBC76610                                ; -> sub_bc76610
    LIFT-BODY;  // implement basic block 0xbc61206..0xbc61372


    // 0xbc61379..0xbc613e9

    0xbc613b7  call 0xBC7A7C0                                ; -> sub_bc7a7c0
    0xbc613d3  call 0xEEC6EC0                                ; -> sub_eec6ec0
    0xbc613e9  call 0xBC60F10                                ; -> sub_bc60f10
    LIFT-BODY;  // implement basic block 0xbc61379..0xbc613e9


    // 0xbc613ee..0xbc61435

    LIFT-BODY;  // implement basic block 0xbc613ee..0xbc61435


    // 0xbc61440..0xbc61483

    LIFT-BODY;  // implement basic block 0xbc61440..0xbc61483


    // 0xbc61485..0xbc614a8

    LIFT-BODY;  // implement basic block 0xbc61485..0xbc614a8


    // 0xbc614b0..0xbc614d7

    0xbc614d1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc614b0..0xbc614d7


    // 0xbc614de..0xbc614ed

    LIFT-BODY;  // implement basic block 0xbc614de..0xbc614ed


    // 0xbc614ef..0xbc614fa

    LIFT-BODY;  // implement basic block 0xbc614ef..0xbc614fa


    // 0xbc614fc..0xbc61507

    0xbc61507  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xbc614fc..0xbc61507


    // 0xbc6150c..0xbc6150c

    LIFT-BODY;  // implement basic block 0xbc6150c..0xbc6150c


    // 0xbc61516..0xbc61516

    LIFT-BODY;  // implement basic block 0xbc61516..0xbc61516


    // 0xbc6151d..0xbc61542

    LIFT-BODY;  // implement basic block 0xbc6151d..0xbc61542


    // 0xbc61543..0xbc61550

    0xbc6154b  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbc61543..0xbc61550


}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)

static_assert(true, "sub_bc61140: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc61140, 0xbc61551) (rdis dis output, two spaces after address):

#if 0
0xbc611f6  call 0xBC60D10                                ; -> sub_bc60d10
0xbc61317  call 0xBC76610                                ; -> sub_bc76610
0xbc613b7  call 0xBC7A7C0                                ; -> sub_bc7a7c0
0xbc613d3  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbc613e9  call 0xBC60F10                                ; -> sub_bc60f10
0xbc614d1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc61507  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xbc6154b  call 0xE951550                                ; -> sub_e951550
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


LIFT_FN(sub_bc61140, "sub_bc61140", 0xbc61140, sub_bc61140, nullptr);

} // namespace native::bgfx