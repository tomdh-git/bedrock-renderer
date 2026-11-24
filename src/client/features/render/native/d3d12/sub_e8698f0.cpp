// LIFT 0xe8698f0 size 0x39a 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e8698f0.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe869925: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe869c76: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e8698f0(/* LIFT-BODY: exact args */);

void sub_e8698f0(/* LIFT-BODY: exact args */) {
    // 0xe8698f0..0xe869c5f
    0xe869925  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8698f0..0xe869c5f

    // 0xe869c63..0xe869c89
    0xe869c76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe869c63..0xe869c89

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e8698f0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe8698f0, 0xe869c8a) (rdis dis output, two spaces after address):
#if 0
0xe869925  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe869c76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e8698f0, "sub_e8698f0", 0xe8698f0, sub_e8698f0, nullptr);

} // namespace native::d3d12