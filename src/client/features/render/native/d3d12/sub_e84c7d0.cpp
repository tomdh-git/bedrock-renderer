// LIFT 0xe84c7d0 size 0x62f 1.26.62.01 sub_e84c7d0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e84c7d0.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe84c90e: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84c99d: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84ca18: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84ca94: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84cb02: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84cb6a: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84cbe2: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84cc5b: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84cd3a: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84cdad: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84cdf9: call 0xE951550                                ; -> sub_e951550 -> sub_e951550

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e84c7d0(/* LIFT-BODY: exact args */);

void sub_e84c7d0(/* LIFT-BODY: exact args */) {
    // 0xe84c7d0..0xe84c80a
    LIFT-BODY;  // implement basic block 0xe84c7d0..0xe84c80a

    // 0xe84c810..0xe84c8b8
    LIFT-BODY;  // implement basic block 0xe84c810..0xe84c8b8

    // 0xe84c8c0..0xe84c8d6
    LIFT-BODY;  // implement basic block 0xe84c8c0..0xe84c8d6

    // 0xe84c8dd..0xe84c90e
    0xe84c90e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84c8dd..0xe84c90e

    // 0xe84c914..0xe84c920
    LIFT-BODY;  // implement basic block 0xe84c914..0xe84c920

    // 0xe84c926..0xe84c93b
    LIFT-BODY;  // implement basic block 0xe84c926..0xe84c93b

    // 0xe84c940..0xe84c958
    LIFT-BODY;  // implement basic block 0xe84c940..0xe84c958

    // 0xe84c95f..0xe84c9b7
    0xe84c99d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84c95f..0xe84c9b7

    // 0xe84c9c0..0xe84c9d6
    LIFT-BODY;  // implement basic block 0xe84c9c0..0xe84c9d6

    // 0xe84c9dd..0xe84ca32
    0xe84ca18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84c9dd..0xe84ca32

    // 0xe84ca40..0xe84ca56
    LIFT-BODY;  // implement basic block 0xe84ca40..0xe84ca56

    // 0xe84ca5d..0xe84caae
    0xe84ca94  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84ca5d..0xe84caae

    // 0xe84cab0..0xe84cac6
    LIFT-BODY;  // implement basic block 0xe84cab0..0xe84cac6

    // 0xe84cacd..0xe84cb1c
    0xe84cb02  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84cacd..0xe84cb1c

    // 0xe84cb20..0xe84cb36
    LIFT-BODY;  // implement basic block 0xe84cb20..0xe84cb36

    // 0xe84cb3d..0xe84cb84
    0xe84cb6a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84cb3d..0xe84cb84

    // 0xe84cb90..0xe84cba6
    LIFT-BODY;  // implement basic block 0xe84cb90..0xe84cba6

    // 0xe84cbad..0xe84cc08
    0xe84cbe2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84cbad..0xe84cc08

    // 0xe84cc10..0xe84cc26
    LIFT-BODY;  // implement basic block 0xe84cc10..0xe84cc26

    // 0xe84cc2d..0xe84cc5b
    0xe84cc5b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84cc2d..0xe84cc5b

    // 0xe84cc61..0xe84cc87
    LIFT-BODY;  // implement basic block 0xe84cc61..0xe84cc87

    // 0xe84cc8c..0xe84ccd4
    LIFT-BODY;  // implement basic block 0xe84cc8c..0xe84ccd4

    // 0xe84cce0..0xe84ccf6
    LIFT-BODY;  // implement basic block 0xe84cce0..0xe84ccf6

    // 0xe84ccfd..0xe84cd4c
    0xe84cd3a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84ccfd..0xe84cd4c

    // 0xe84cd4e..0xe84cd60
    LIFT-BODY;  // implement basic block 0xe84cd4e..0xe84cd60

    // 0xe84cd62..0xe84cdbd
    0xe84cdad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84cd62..0xe84cdbd

    // 0xe84cdc3..0xe84cded
    LIFT-BODY;  // implement basic block 0xe84cdc3..0xe84cded

    // 0xe84cdee..0xe84cdfe
    0xe84cdf9  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xe84cdee..0xe84cdfe

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e84c7d0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe84c7d0, 0xe84cdff) (rdis dis output, two spaces after address):
#if 0
0xe84c90e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84c99d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84ca18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84ca94  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84cb02  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84cb6a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84cbe2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84cc5b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84cd3a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84cdad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84cdf9  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e84c7d0, "sub_e84c7d0", 0xe84c7d0, sub_e84c7d0, nullptr);

} // namespace native::d3d12