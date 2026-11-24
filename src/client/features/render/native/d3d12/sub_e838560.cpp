// LIFT 0xe838560 size 0x8fb 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e838560.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe8386e3: call 0x6B35400                                ; -> sub_6b35400 -> sub_6b35400
//   0xe838725: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8387f6: call 0x6B35400                                ; -> sub_6b35400 -> sub_6b35400
//   0xe838838: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8388ea: call 0x6B35400                                ; -> sub_6b35400 -> sub_6b35400
//   0xe83892c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8389ea: call 0x6B35400                                ; -> sub_6b35400 -> sub_6b35400
//   0xe838a2c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe838aef: call 0x6B35400                                ; -> sub_6b35400 -> sub_6b35400
//   0xe838b31: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe838c15: call 0x6B35400                                ; -> sub_6b35400 -> sub_6b35400
//   0xe838c57: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe838d30: call 0x6B35400                                ; -> sub_6b35400 -> sub_6b35400
//   0xe838d72: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe838df0: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe838e00: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe838e10: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe838e20: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe838e30: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe838e40: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe838e50: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e838560(/* LIFT-BODY: exact args */);

void sub_e838560(/* LIFT-BODY: exact args */) {
    // 0xe838560..0xe8385bc
    LIFT-BODY;  // implement basic block 0xe838560..0xe8385bc

    // 0xe8385c2..0xe838606
    LIFT-BODY;  // implement basic block 0xe8385c2..0xe838606

    // 0xe83860b..0xe838637
    LIFT-BODY;  // implement basic block 0xe83860b..0xe838637

    // 0xe838639..0xe83867b
    LIFT-BODY;  // implement basic block 0xe838639..0xe83867b

    // 0xe838680..0xe8386a7
    LIFT-BODY;  // implement basic block 0xe838680..0xe8386a7

    // 0xe8386ac..0xe8386ac
    LIFT-BODY;  // implement basic block 0xe8386ac..0xe8386ac

    // 0xe8386af..0xe8386ed
    0xe8386e3  call 0x6B35400                                ; -> sub_6b35400
    LIFT-BODY;  // implement basic block 0xe8386af..0xe8386ed

    // 0xe8386f1..0xe838732
    0xe838725  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8386f1..0xe838732

    // 0xe838738..0xe83874e
    LIFT-BODY;  // implement basic block 0xe838738..0xe83874e

    // 0xe838752..0xe83878a
    LIFT-BODY;  // implement basic block 0xe838752..0xe83878a

    // 0xe83878f..0xe8387bb
    LIFT-BODY;  // implement basic block 0xe83878f..0xe8387bb

    // 0xe8387c0..0xe8387c0
    LIFT-BODY;  // implement basic block 0xe8387c0..0xe8387c0

    // 0xe8387c3..0xe838800
    0xe8387f6  call 0x6B35400                                ; -> sub_6b35400
    LIFT-BODY;  // implement basic block 0xe8387c3..0xe838800

    // 0xe838804..0xe838845
    0xe838838  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe838804..0xe838845

    // 0xe83884b..0xe838861
    LIFT-BODY;  // implement basic block 0xe83884b..0xe838861

    // 0xe838865..0xe8388b2
    LIFT-BODY;  // implement basic block 0xe838865..0xe8388b2

    // 0xe8388b4..0xe8388b4
    LIFT-BODY;  // implement basic block 0xe8388b4..0xe8388b4

    // 0xe8388b7..0xe8388f4
    0xe8388ea  call 0x6B35400                                ; -> sub_6b35400
    LIFT-BODY;  // implement basic block 0xe8388b7..0xe8388f4

    // 0xe8388f8..0xe838939
    0xe83892c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8388f8..0xe838939

    // 0xe83893f..0xe838955
    LIFT-BODY;  // implement basic block 0xe83893f..0xe838955

    // 0xe838959..0xe8389b3
    LIFT-BODY;  // implement basic block 0xe838959..0xe8389b3

    // 0xe8389b8..0xe8389b8
    LIFT-BODY;  // implement basic block 0xe8389b8..0xe8389b8

    // 0xe8389ba..0xe8389f4
    0xe8389ea  call 0x6B35400                                ; -> sub_6b35400
    LIFT-BODY;  // implement basic block 0xe8389ba..0xe8389f4

    // 0xe8389f8..0xe838a39
    0xe838a2c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8389f8..0xe838a39

    // 0xe838a3f..0xe838a55
    LIFT-BODY;  // implement basic block 0xe838a3f..0xe838a55

    // 0xe838a59..0xe838a7a
    LIFT-BODY;  // implement basic block 0xe838a59..0xe838a7a

    // 0xe838a7e..0xe838ab3
    LIFT-BODY;  // implement basic block 0xe838a7e..0xe838ab3

    // 0xe838ab5..0xe838ab5
    LIFT-BODY;  // implement basic block 0xe838ab5..0xe838ab5

    // 0xe838ab7..0xe838af9
    0xe838aef  call 0x6B35400                                ; -> sub_6b35400
    LIFT-BODY;  // implement basic block 0xe838ab7..0xe838af9

    // 0xe838afd..0xe838b3e
    0xe838b31  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe838afd..0xe838b3e

    // 0xe838b44..0xe838b5a
    LIFT-BODY;  // implement basic block 0xe838b44..0xe838b5a

    // 0xe838b5e..0xe838b83
    LIFT-BODY;  // implement basic block 0xe838b5e..0xe838b83

    // 0xe838b87..0xe838bb4
    LIFT-BODY;  // implement basic block 0xe838b87..0xe838bb4

    // 0xe838bb9..0xe838bda
    LIFT-BODY;  // implement basic block 0xe838bb9..0xe838bda

    // 0xe838bdf..0xe838bdf
    LIFT-BODY;  // implement basic block 0xe838bdf..0xe838bdf

    // 0xe838be1..0xe838c1f
    0xe838c15  call 0x6B35400                                ; -> sub_6b35400
    LIFT-BODY;  // implement basic block 0xe838be1..0xe838c1f

    // 0xe838c23..0xe838c64
    0xe838c57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe838c23..0xe838c64

    // 0xe838c6a..0xe838c80
    LIFT-BODY;  // implement basic block 0xe838c6a..0xe838c80

    // 0xe838c84..0xe838cc7
    LIFT-BODY;  // implement basic block 0xe838c84..0xe838cc7

    // 0xe838ccb..0xe838cd7
    LIFT-BODY;  // implement basic block 0xe838ccb..0xe838cd7

    // 0xe838cdb..0xe838cdb
    LIFT-BODY;  // implement basic block 0xe838cdb..0xe838cdb

    // 0xe838ce3..0xe838ce5
    LIFT-BODY;  // implement basic block 0xe838ce3..0xe838ce5

    // 0xe838ce9..0xe838cf9
    LIFT-BODY;  // implement basic block 0xe838ce9..0xe838cf9

    // 0xe838cfa..0xe838cfa
    LIFT-BODY;  // implement basic block 0xe838cfa..0xe838cfa

    // 0xe838cfc..0xe838d3a
    0xe838d30  call 0x6B35400                                ; -> sub_6b35400
    LIFT-BODY;  // implement basic block 0xe838cfc..0xe838d3a

    // 0xe838d3e..0xe838d7f
    0xe838d72  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe838d3e..0xe838d7f

    // 0xe838d85..0xe838d9b
    LIFT-BODY;  // implement basic block 0xe838d85..0xe838d9b

    // 0xe838d9f..0xe838de6
    LIFT-BODY;  // implement basic block 0xe838d9f..0xe838de6

    // 0xe838deb..0xe838df6
    0xe838df0  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe838deb..0xe838df6

    // 0xe838dfb..0xe838e06
    0xe838e00  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe838dfb..0xe838e06

    // 0xe838e0b..0xe838e16
    0xe838e10  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe838e0b..0xe838e16

    // 0xe838e1b..0xe838e26
    0xe838e20  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe838e1b..0xe838e26

    // 0xe838e2b..0xe838e36
    0xe838e30  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe838e2b..0xe838e36

    // 0xe838e3b..0xe838e46
    0xe838e40  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe838e3b..0xe838e46

    // 0xe838e4b..0xe838e56
    0xe838e50  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe838e4b..0xe838e56

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e838560: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe838560, 0xe838e5b) (rdis dis output, two spaces after address):
#if 0
0xe8386e3  call 0x6B35400                                ; -> sub_6b35400
0xe838725  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8387f6  call 0x6B35400                                ; -> sub_6b35400
0xe838838  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8388ea  call 0x6B35400                                ; -> sub_6b35400
0xe83892c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8389ea  call 0x6B35400                                ; -> sub_6b35400
0xe838a2c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe838aef  call 0x6B35400                                ; -> sub_6b35400
0xe838b31  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe838c15  call 0x6B35400                                ; -> sub_6b35400
0xe838c57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe838d30  call 0x6B35400                                ; -> sub_6b35400
0xe838d72  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe838df0  call 0x9BC830                                 ; -> sub_9bc830
0xe838e00  call 0x9BC830                                 ; -> sub_9bc830
0xe838e10  call 0x9BC830                                 ; -> sub_9bc830
0xe838e20  call 0x9BC830                                 ; -> sub_9bc830
0xe838e30  call 0x9BC830                                 ; -> sub_9bc830
0xe838e40  call 0x9BC830                                 ; -> sub_9bc830
0xe838e50  call 0x9BC830                                 ; -> sub_9bc830
#endif

// Calls out of lifted code:
//   sub_6b35400 (0x6b35400, boundary) - call 0x6B35400                                ; -> sub_6b35400
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_6b35400 (0x6b35400, boundary) - call 0x6B35400                                ; -> sub_6b35400
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_6b35400 (0x6b35400, boundary) - call 0x6B35400                                ; -> sub_6b35400
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_6b35400 (0x6b35400, boundary) - call 0x6B35400                                ; -> sub_6b35400
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_6b35400 (0x6b35400, boundary) - call 0x6B35400                                ; -> sub_6b35400
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_6b35400 (0x6b35400, boundary) - call 0x6B35400                                ; -> sub_6b35400
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_6b35400 (0x6b35400, boundary) - call 0x6B35400                                ; -> sub_6b35400
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e838560, "sub_e838560", 0xe838560, sub_e838560, nullptr);

} // namespace native::d3d12