// LIFT 0xe835b50 size 0x1a5 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e835b50.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Forward declaration for callee in lift set: sub_e935700
extern "C" void sub_e935700(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec6de0
extern "C" void sub_eec6de0(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe835bed: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe835c1e: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe835c2f: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe835c54: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xe835cc9: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe835cd6: call 0x75740                                  ; -> sub_75740 -> sub_75740
//   0xe835cee: call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e835b50(/* LIFT-BODY: exact args */);

void sub_e835b50(/* LIFT-BODY: exact args */) {
    // 0xe835b50..0xe835bf6
    0xe835bed  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe835b50..0xe835bf6

    // 0xe835bfc..0xe835c0b
    LIFT-BODY;  // implement basic block 0xe835bfc..0xe835c0b

    // 0xe835c0d..0xe835c2f
    0xe835c1e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe835c2f  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe835c0d..0xe835c2f

    // 0xe835c34..0xe835c34
    LIFT-BODY;  // implement basic block 0xe835c34..0xe835c34

    // 0xe835c36..0xe835c54
    0xe835c54  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe835c36..0xe835c54

    // 0xe835c59..0xe835c98
    0xe835c66  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xe835c59..0xe835c98

    // 0xe835c9b..0xe835c9b
    0xe835c9b  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xe835c9b..0xe835c9b

    // 0xe835ca0..0xe835cc2
    LIFT-BODY;  // implement basic block 0xe835ca0..0xe835cc2

    // 0xe835cc3..0xe835cd1
    0xe835cc9  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe835cc3..0xe835cd1

    // 0xe835cd6..0xe835cd6
    0xe835cd6  call 0x75740                                  ; -> sub_75740
    LIFT-BODY;  // implement basic block 0xe835cd6..0xe835cd6

    // 0xe835cdb..0xe835cf4
    0xe835cee  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
    LIFT-BODY;  // implement basic block 0xe835cdb..0xe835cf4

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e835b50: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe835b50, 0xe835cf5) (rdis dis output, two spaces after address):
#if 0
0xe835bed  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe835c1e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe835c2f  call 0x9BC830                                 ; -> sub_9bc830
0xe835c54  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe835c66  call 0xEEC6DE0                                ; -> sub_eec6de0
0xe835c9b  call 0xE935700                                ; -> sub_e935700
0xe835cc9  call 0x9BC830                                 ; -> sub_9bc830
0xe835cd6  call 0x75740                                  ; -> sub_75740
0xe835cee  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_75740 (0x75740, boundary) - call 0x75740                                  ; -> sub_75740
//   call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e835b50, "sub_e835b50", 0xe835b50, sub_e835b50, nullptr);

} // namespace native::d3d12