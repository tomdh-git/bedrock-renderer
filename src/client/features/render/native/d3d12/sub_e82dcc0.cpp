// LIFT 0xe82dcc0 size 0x1cf 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e82dcc0.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe82de61: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe82de89: call 0xE951550                                ; -> sub_e951550 -> sub_e951550

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e82dcc0(/* LIFT-BODY: exact args */);

void sub_e82dcc0(/* LIFT-BODY: exact args */) {
    // 0xe82dcc0..0xe82dd31
    LIFT-BODY;  // implement basic block 0xe82dcc0..0xe82dd31

    // 0xe82dd33..0xe82dd7d
    LIFT-BODY;  // implement basic block 0xe82dd33..0xe82dd7d

    // 0xe82dd80..0xe82dd92
    LIFT-BODY;  // implement basic block 0xe82dd80..0xe82dd92

    // 0xe82dd97..0xe82ddc5
    LIFT-BODY;  // implement basic block 0xe82dd97..0xe82ddc5

    // 0xe82ddca..0xe82de01
    LIFT-BODY;  // implement basic block 0xe82ddca..0xe82de01

    // 0xe82de03..0xe82de13
    LIFT-BODY;  // implement basic block 0xe82de03..0xe82de13

    // 0xe82de15..0xe82de24
    LIFT-BODY;  // implement basic block 0xe82de15..0xe82de24

    // 0xe82de27..0xe82de45
    LIFT-BODY;  // implement basic block 0xe82de27..0xe82de45

    // 0xe82de4a..0xe82de61
    0xe82de61  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe82de4a..0xe82de61

    // 0xe82de67..0xe82de80
    LIFT-BODY;  // implement basic block 0xe82de67..0xe82de80

    // 0xe82de81..0xe82de8e
    0xe82de89  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xe82de81..0xe82de8e

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e82dcc0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe82dcc0, 0xe82de8f) (rdis dis output, two spaces after address):
#if 0
0xe82de61  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82de89  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e82dcc0, "sub_e82dcc0", 0xe82dcc0, sub_e82dcc0, nullptr);

} // namespace native::d3d12