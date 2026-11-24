// LIFT 0xe83bdd0 size 0x5b3 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e83bdd0.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe83bef3: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe83c0d7: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe83c1ac: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe83c1ec: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e83bdd0(/* LIFT-BODY: exact args */);

void sub_e83bdd0(/* LIFT-BODY: exact args */) {
    // 0xe83bdd0..0xe83bea6
    LIFT-BODY;  // implement basic block 0xe83bdd0..0xe83bea6

    // 0xe83beb0..0xe83bec0
    LIFT-BODY;  // implement basic block 0xe83beb0..0xe83bec0

    // 0xe83bec2..0xe83bfe4
    0xe83bef3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83bec2..0xe83bfe4

    // 0xe83bfe6..0xe83bfe9
    LIFT-BODY;  // implement basic block 0xe83bfe6..0xe83bfe9

    // 0xe83bfee..0xe83bff6
    LIFT-BODY;  // implement basic block 0xe83bfee..0xe83bff6

    // 0xe83c000..0xe83c00a
    LIFT-BODY;  // implement basic block 0xe83c000..0xe83c00a

    // 0xe83c00c..0xe83c00c
    LIFT-BODY;  // implement basic block 0xe83c00c..0xe83c00c

    // 0xe83c00f..0xe83c013
    LIFT-BODY;  // implement basic block 0xe83c00f..0xe83c013

    // 0xe83c020..0xe83c039
    LIFT-BODY;  // implement basic block 0xe83c020..0xe83c039

    // 0xe83c03b..0xe83c043
    LIFT-BODY;  // implement basic block 0xe83c03b..0xe83c043

    // 0xe83c050..0xe83c05e
    LIFT-BODY;  // implement basic block 0xe83c050..0xe83c05e

    // 0xe83c060..0xe83c126
    0xe83c0d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83c060..0xe83c126

    // 0xe83c130..0xe83c154
    LIFT-BODY;  // implement basic block 0xe83c130..0xe83c154

    // 0xe83c156..0xe83c158
    LIFT-BODY;  // implement basic block 0xe83c156..0xe83c158

    // 0xe83c15a..0xe83c15d
    LIFT-BODY;  // implement basic block 0xe83c15a..0xe83c15d

    // 0xe83c160..0xe83c171
    LIFT-BODY;  // implement basic block 0xe83c160..0xe83c171

    // 0xe83c173..0xe83c173
    LIFT-BODY;  // implement basic block 0xe83c173..0xe83c173

    // 0xe83c177..0xe83c1b2
    0xe83c1ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83c177..0xe83c1b2

    // 0xe83c1b5..0xe83c1bd
    LIFT-BODY;  // implement basic block 0xe83c1b5..0xe83c1bd

    // 0xe83c1c1..0xe83c1f1
    0xe83c1ec  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe83c1c1..0xe83c1f1

    // 0xe83c1f5..0xe83c20f
    LIFT-BODY;  // implement basic block 0xe83c1f5..0xe83c20f

    // 0xe83c210..0xe83c213
    LIFT-BODY;  // implement basic block 0xe83c210..0xe83c213

    // 0xe83c219..0xe83c2e3
    LIFT-BODY;  // implement basic block 0xe83c219..0xe83c2e3

    // 0xe83c2f0..0xe83c2f8
    LIFT-BODY;  // implement basic block 0xe83c2f0..0xe83c2f8

    // 0xe83c300..0xe83c30a
    LIFT-BODY;  // implement basic block 0xe83c300..0xe83c30a

    // 0xe83c30c..0xe83c30c
    LIFT-BODY;  // implement basic block 0xe83c30c..0xe83c30c

    // 0xe83c30f..0xe83c313
    LIFT-BODY;  // implement basic block 0xe83c30f..0xe83c313

    // 0xe83c320..0xe83c339
    LIFT-BODY;  // implement basic block 0xe83c320..0xe83c339

    // 0xe83c33b..0xe83c343
    LIFT-BODY;  // implement basic block 0xe83c33b..0xe83c343

    // 0xe83c350..0xe83c364
    LIFT-BODY;  // implement basic block 0xe83c350..0xe83c364

    // 0xe83c369..0xe83c36c
    LIFT-BODY;  // implement basic block 0xe83c369..0xe83c36c

    // 0xe83c370..0xe83c382
    LIFT-BODY;  // implement basic block 0xe83c370..0xe83c382

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e83bdd0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe83bdd0, 0xe83c383) (rdis dis output, two spaces after address):
#if 0
0xe83bef3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83c0d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83c1ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83c1ec  call 0xEEC6ED0                                ; -> sub_eec6ed0
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e83bdd0, "sub_e83bdd0", 0xe83bdd0, sub_e83bdd0, nullptr);

} // namespace native::d3d12