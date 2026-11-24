// LIFT 0xe805e50 size 0x5b3 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e805e50.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe805f73: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe806157: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe80622c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe80626c: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e805e50(/* LIFT-BODY: exact args */);

void sub_e805e50(/* LIFT-BODY: exact args */) {
    // 0xe805e50..0xe805f26
    LIFT-BODY;  // implement basic block 0xe805e50..0xe805f26

    // 0xe805f30..0xe805f40
    LIFT-BODY;  // implement basic block 0xe805f30..0xe805f40

    // 0xe805f42..0xe806065
    0xe805f73  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe805f42..0xe806065

    // 0xe806067..0xe80606a
    LIFT-BODY;  // implement basic block 0xe806067..0xe80606a

    // 0xe80606f..0xe806077
    LIFT-BODY;  // implement basic block 0xe80606f..0xe806077

    // 0xe806080..0xe80608a
    LIFT-BODY;  // implement basic block 0xe806080..0xe80608a

    // 0xe80608c..0xe80608c
    LIFT-BODY;  // implement basic block 0xe80608c..0xe80608c

    // 0xe80608f..0xe806093
    LIFT-BODY;  // implement basic block 0xe80608f..0xe806093

    // 0xe8060a0..0xe8060b9
    LIFT-BODY;  // implement basic block 0xe8060a0..0xe8060b9

    // 0xe8060bb..0xe8060c3
    LIFT-BODY;  // implement basic block 0xe8060bb..0xe8060c3

    // 0xe8060d0..0xe8060de
    LIFT-BODY;  // implement basic block 0xe8060d0..0xe8060de

    // 0xe8060e0..0xe8061a6
    0xe806157  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8060e0..0xe8061a6

    // 0xe8061b0..0xe8061d4
    LIFT-BODY;  // implement basic block 0xe8061b0..0xe8061d4

    // 0xe8061d6..0xe8061d8
    LIFT-BODY;  // implement basic block 0xe8061d6..0xe8061d8

    // 0xe8061da..0xe8061dd
    LIFT-BODY;  // implement basic block 0xe8061da..0xe8061dd

    // 0xe8061e0..0xe8061f1
    LIFT-BODY;  // implement basic block 0xe8061e0..0xe8061f1

    // 0xe8061f3..0xe8061f3
    LIFT-BODY;  // implement basic block 0xe8061f3..0xe8061f3

    // 0xe8061f7..0xe806232
    0xe80622c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8061f7..0xe806232

    // 0xe806235..0xe80623d
    LIFT-BODY;  // implement basic block 0xe806235..0xe80623d

    // 0xe806241..0xe806271
    0xe80626c  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe806241..0xe806271

    // 0xe806275..0xe80628f
    LIFT-BODY;  // implement basic block 0xe806275..0xe80628f

    // 0xe806290..0xe806293
    LIFT-BODY;  // implement basic block 0xe806290..0xe806293

    // 0xe806299..0xe806363
    LIFT-BODY;  // implement basic block 0xe806299..0xe806363

    // 0xe806370..0xe806378
    LIFT-BODY;  // implement basic block 0xe806370..0xe806378

    // 0xe806380..0xe80638a
    LIFT-BODY;  // implement basic block 0xe806380..0xe80638a

    // 0xe80638c..0xe80638c
    LIFT-BODY;  // implement basic block 0xe80638c..0xe80638c

    // 0xe80638f..0xe806393
    LIFT-BODY;  // implement basic block 0xe80638f..0xe806393

    // 0xe8063a0..0xe8063b9
    LIFT-BODY;  // implement basic block 0xe8063a0..0xe8063b9

    // 0xe8063bb..0xe8063c3
    LIFT-BODY;  // implement basic block 0xe8063bb..0xe8063c3

    // 0xe8063d0..0xe8063e4
    LIFT-BODY;  // implement basic block 0xe8063d0..0xe8063e4

    // 0xe8063e9..0xe8063ec
    LIFT-BODY;  // implement basic block 0xe8063e9..0xe8063ec

    // 0xe8063f0..0xe806402
    LIFT-BODY;  // implement basic block 0xe8063f0..0xe806402

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e805e50: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe805e50, 0xe806403) (rdis dis output, two spaces after address):
#if 0
0xe805f73  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe806157  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe80622c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe80626c  call 0xEEC6ED0                                ; -> sub_eec6ed0
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e805e50, "sub_e805e50", 0xe805e50, sub_e805e50, nullptr);

} // namespace native::d3d12