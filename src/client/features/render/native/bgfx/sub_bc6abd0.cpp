// LIFT 0xbc6abd0 size 0x2df 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc6abd0.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_bc6aeb0
extern "C" void sub_bc6aeb0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ebce390
extern "C" void sub_ebce390(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbc6ad57: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc6ad7f: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc6ade2: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc6ae08: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc6ae3f: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc6ae6d: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc6aea9: call 0xE951550                                ; -> sub_e951550 -> sub_e951550

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bc6abd0(/* LIFT-BODY: exact args */);

void sub_bc6abd0(/* LIFT-BODY: exact args */) {
    // 0xbc6abd0..0xbc6ac33
    0xbc6abff  call 0xBC6AEB0                                ; -> sub_bc6aeb0
    LIFT-BODY;  // implement basic block 0xbc6abd0..0xbc6ac33

    // 0xbc6ac40..0xbc6ac46
    LIFT-BODY;  // implement basic block 0xbc6ac40..0xbc6ac46

    // 0xbc6ac4c..0xbc6ad57
    0xbc6ac69  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ac83  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ac9c  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6acb7  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6acd4  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6acf1  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ad0e  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ad2b  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ad57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ac4c..0xbc6ad57

    // 0xbc6ad5d..0xbc6ad85
    0xbc6ad7f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ad5d..0xbc6ad85

    // 0xbc6ad88..0xbc6ae08
    0xbc6ade2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc6ae08  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ad88..0xbc6ae08

    // 0xbc6ae0e..0xbc6ae45
    0xbc6ae3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ae0e..0xbc6ae45

    // 0xbc6ae4a..0xbc6ae6d
    0xbc6ae6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ae4a..0xbc6ae6d

    // 0xbc6ae73..0xbc6ae79
    LIFT-BODY;  // implement basic block 0xbc6ae73..0xbc6ae79

    // 0xbc6ae7c..0xbc6aea0
    LIFT-BODY;  // implement basic block 0xbc6ae7c..0xbc6aea0

    // 0xbc6aea1..0xbc6aeae
    0xbc6aea9  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbc6aea1..0xbc6aeae

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bc6abd0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc6abd0, 0xbc6aeaf) (rdis dis output, two spaces after address):
#if 0
0xbc6abff  call 0xBC6AEB0                                ; -> sub_bc6aeb0
0xbc6ac69  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ac83  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ac9c  call 0xEBCE390                                ; -> sub_ebce390
0xbc6acb7  call 0xEBCE390                                ; -> sub_ebce390
0xbc6acd4  call 0xEBCE390                                ; -> sub_ebce390
0xbc6acf1  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ad0e  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ad2b  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ad57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ad7f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ade2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ae08  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ae3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ae6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6aea9  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   sub_bc6aeb0 (0xbc6aeb0, lift set) - call 0xBC6AEB0                                ; -> sub_bc6aeb0
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bc6abd0, "sub_bc6abd0", 0xbc6abd0, sub_bc6abd0, nullptr);

} // namespace native::bgfx