// LIFT 0xbc5f110 size 0x121 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc5f110.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_ebcf430
extern "C" void sub_ebcf430(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbc5f119: call 0xE9E7970                                ; -> sub_e9e7970 -> sub_e9e7970
//   0xbc5f199: call 0xE9E7970                                ; -> sub_e9e7970 -> sub_e9e7970
//   0xbc5f1db: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc5f212: call 0xEBCE470                                ; -> sub_ebce470 -> sub_ebce470
//   0xbc5f217: call qword ptr [0xF9A8CB0]                    ; [data_f9a8cb0] (indirect)
//   0xbc5f22b: call 0xE951550                                ; -> sub_e951550 -> sub_e951550

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bc5f110(/* LIFT-BODY: exact args */);

void sub_bc5f110(/* LIFT-BODY: exact args */) {
    // 0xbc5f110..0xbc5f1bb
    0xbc5f119  call 0xE9E7970                                ; -> sub_e9e7970
    0xbc5f17d  call 0xEBCF430                                ; -> sub_ebcf430
    0xbc5f199  call 0xE9E7970                                ; -> sub_e9e7970
    0xbc5f1b2  call 0xEBCF430                                ; -> sub_ebcf430
    LIFT-BODY;  // implement basic block 0xbc5f110..0xbc5f1bb

    // 0xbc5f1bd..0xbc5f206
    0xbc5f1db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc5f1bd..0xbc5f206

    // 0xbc5f207..0xbc5f217
    0xbc5f212  call 0xEBCE470                                ; -> sub_ebce470
    0xbc5f217  call qword ptr [0xF9A8CB0]                    ; [data_f9a8cb0]
    LIFT-BODY;  // implement basic block 0xbc5f207..0xbc5f217

    // 0xbc5f21d..0xbc5f230
    0xbc5f22b  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbc5f21d..0xbc5f230

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bc5f110: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc5f110, 0xbc5f231) (rdis dis output, two spaces after address):
#if 0
0xbc5f119  call 0xE9E7970                                ; -> sub_e9e7970
0xbc5f17d  call 0xEBCF430                                ; -> sub_ebcf430
0xbc5f199  call 0xE9E7970                                ; -> sub_e9e7970
0xbc5f1b2  call 0xEBCF430                                ; -> sub_ebcf430
0xbc5f1db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5f212  call 0xEBCE470                                ; -> sub_ebce470
0xbc5f217  call qword ptr [0xF9A8CB0]                    ; [data_f9a8cb0]
0xbc5f22b  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   sub_e9e7970 (0xe9e7970, boundary) - call 0xE9E7970                                ; -> sub_e9e7970
//   sub_ebcf430 (0xebcf430, lift set) - call 0xEBCF430                                ; -> sub_ebcf430
//   sub_e9e7970 (0xe9e7970, boundary) - call 0xE9E7970                                ; -> sub_e9e7970
//   sub_ebcf430 (0xebcf430, lift set) - call 0xEBCF430                                ; -> sub_ebcf430
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_ebce470 (0xebce470, boundary) - call 0xEBCE470                                ; -> sub_ebce470
//   call qword ptr [0xF9A8CB0]                    ; [data_f9a8cb0] (indirect, boundary via data slot)
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bc5f110, "sub_bc5f110", 0xbc5f110, sub_bc5f110, nullptr);

} // namespace native::bgfx