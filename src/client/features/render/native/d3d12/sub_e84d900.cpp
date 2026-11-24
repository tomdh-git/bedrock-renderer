// LIFT 0xe84d900 size 0x369 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e84d900.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Forward declaration for callee in lift set: sub_e935700
extern "C" void sub_e935700(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec5850
extern "C" void sub_eec5850(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe84d988: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84d9d8: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe84dc27: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe84dc37: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe84dc62: call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e84d900(/* LIFT-BODY: exact args */);

void sub_e84d900(/* LIFT-BODY: exact args */) {
    // 0xe84d900..0xe84d991
    0xe84d988  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84d900..0xe84d991

    // 0xe84d997..0xe84d9a6
    LIFT-BODY;  // implement basic block 0xe84d997..0xe84d9a6

    // 0xe84d9a8..0xe84d9c2
    LIFT-BODY;  // implement basic block 0xe84d9a8..0xe84d9c2

    // 0xe84d9c7..0xe84d9e4
    0xe84d9d8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe84d9c7..0xe84d9e4

    // 0xe84d9ea..0xe84da19
    LIFT-BODY;  // implement basic block 0xe84d9ea..0xe84da19

    // 0xe84da1c..0xe84da1c
    0xe84da1c  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xe84da1c..0xe84da1c

    // 0xe84da21..0xe84da3e
    LIFT-BODY;  // implement basic block 0xe84da21..0xe84da3e

    // 0xe84da40..0xe84da5f
    LIFT-BODY;  // implement basic block 0xe84da40..0xe84da5f

    // 0xe84da60..0xe84da7b
    LIFT-BODY;  // implement basic block 0xe84da60..0xe84da7b

    // 0xe84da80..0xe84da8c
    LIFT-BODY;  // implement basic block 0xe84da80..0xe84da8c

    // 0xe84da8e..0xe84daad
    LIFT-BODY;  // implement basic block 0xe84da8e..0xe84daad

    // 0xe84dab0..0xe84dacb
    LIFT-BODY;  // implement basic block 0xe84dab0..0xe84dacb

    // 0xe84dad0..0xe84dada
    LIFT-BODY;  // implement basic block 0xe84dad0..0xe84dada

    // 0xe84dadc..0xe84db18
    LIFT-BODY;  // implement basic block 0xe84dadc..0xe84db18

    // 0xe84db20..0xe84db20
    LIFT-BODY;  // implement basic block 0xe84db20..0xe84db20

    // 0xe84db24..0xe84db24
    LIFT-BODY;  // implement basic block 0xe84db24..0xe84db24

    // 0xe84db29..0xe84db2c
    LIFT-BODY;  // implement basic block 0xe84db29..0xe84db2c

    // 0xe84db32..0xe84dba2
    LIFT-BODY;  // implement basic block 0xe84db32..0xe84dba2

    // 0xe84dbb0..0xe84dbe3
    LIFT-BODY;  // implement basic block 0xe84dbb0..0xe84dbe3

    // 0xe84dbe8..0xe84dc0e
    LIFT-BODY;  // implement basic block 0xe84dbe8..0xe84dc0e

    // 0xe84dc13..0xe84dc20
    LIFT-BODY;  // implement basic block 0xe84dc13..0xe84dc20

    // 0xe84dc21..0xe84dc2f
    0xe84dc27  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe84dc21..0xe84dc2f

    // 0xe84dc34..0xe84dc3e
    0xe84dc37  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe84dc34..0xe84dc3e

    // 0xe84dc43..0xe84dc4a
    0xe84dc4a  call 0xEEC5850                                ; -> sub_eec5850
    LIFT-BODY;  // implement basic block 0xe84dc43..0xe84dc4a

    // 0xe84dc4f..0xe84dc68
    0xe84dc62  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
    LIFT-BODY;  // implement basic block 0xe84dc4f..0xe84dc68

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e84d900: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe84d900, 0xe84dc69) (rdis dis output, two spaces after address):
#if 0
0xe84d988  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84d9d8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe84da1c  call 0xE935700                                ; -> sub_e935700
0xe84dc27  call 0x9BC830                                 ; -> sub_9bc830
0xe84dc37  call 0x9BC830                                 ; -> sub_9bc830
0xe84dc4a  call 0xEEC5850                                ; -> sub_eec5850
0xe84dc62  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_eec5850 (0xeec5850, lift set) - call 0xEEC5850                                ; -> sub_eec5850
//   call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e84d900, "sub_e84d900", 0xe84d900, sub_e84d900, nullptr);

} // namespace native::d3d12