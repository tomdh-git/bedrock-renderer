// LIFT 0xe8692c0 size 0x5cd 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e8692c0.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe869310: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe869829: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe86984c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e8692c0(/* LIFT-BODY: exact args */);

void sub_e8692c0(/* LIFT-BODY: exact args */) {
    // 0xe8692c0..0xe86933b
    0xe869310  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8692c0..0xe86933b

    // 0xe86933d..0xe86933d
    LIFT-BODY;  // implement basic block 0xe86933d..0xe86933d

    // 0xe86933f..0xe869365
    LIFT-BODY;  // implement basic block 0xe86933f..0xe869365

    // 0xe86936a..0xe869394
    LIFT-BODY;  // implement basic block 0xe86936a..0xe869394

    // 0xe869399..0xe869408
    LIFT-BODY;  // implement basic block 0xe869399..0xe869408

    // 0xe86940a..0xe869417
    LIFT-BODY;  // implement basic block 0xe86940a..0xe869417

    // 0xe869419..0xe869419
    LIFT-BODY;  // implement basic block 0xe869419..0xe869419

    // 0xe86941d..0xe869430
    LIFT-BODY;  // implement basic block 0xe86941d..0xe869430

    // 0xe869432..0xe869432
    LIFT-BODY;  // implement basic block 0xe869432..0xe869432

    // 0xe869436..0xe869445
    LIFT-BODY;  // implement basic block 0xe869436..0xe869445

    // 0xe86944a..0xe869452
    LIFT-BODY;  // implement basic block 0xe86944a..0xe869452

    // 0xe869457..0xe869813
    LIFT-BODY;  // implement basic block 0xe869457..0xe869813

    // 0xe869818..0xe869879
    0xe869829  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe86984c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe869818..0xe869879

    // 0xe86987c..0xe86988c
    LIFT-BODY;  // implement basic block 0xe86987c..0xe86988c

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e8692c0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe8692c0, 0xe86988d) (rdis dis output, two spaces after address):
#if 0
0xe869310  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe869829  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe86984c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e8692c0, "sub_e8692c0", 0xe8692c0, sub_e8692c0, nullptr);

} // namespace native::d3d12