// LIFT 0xbcc3fa0 size 0x1af 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcc3fa0.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_bc60740
extern "C" void sub_bc60740(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ebce390
extern "C" void sub_ebce390(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec6d80
extern "C" void sub_eec6d80(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbcc411f: call 0xE951550                                ; -> sub_e951550 -> sub_e951550
//   0xbcc4149: call 0x1A2800                                 ; -> sub_1a2800 -> sub_1a2800

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bcc3fa0(/* LIFT-BODY: exact args */);

void sub_bcc3fa0(/* LIFT-BODY: exact args */) {
    // 0xbcc3fa0..0xbcc3fce
    LIFT-BODY;  // implement basic block 0xbcc3fa0..0xbcc3fce

    // 0xbcc3fd3..0xbcc404b
    LIFT-BODY;  // implement basic block 0xbcc3fd3..0xbcc404b

    // 0xbcc4050..0xbcc407d
    LIFT-BODY;  // implement basic block 0xbcc4050..0xbcc407d

    // 0xbcc407f..0xbcc40e9
    0xbcc40a5  call 0xEBCE390                                ; -> sub_ebce390
    0xbcc40e4  call 0xBC60740                                ; -> sub_bc60740
    LIFT-BODY;  // implement basic block 0xbcc407f..0xbcc40e9

    // 0xbcc40eb..0xbcc4113
    LIFT-BODY;  // implement basic block 0xbcc40eb..0xbcc4113

    // 0xbcc4114..0xbcc411f
    0xbcc411f  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbcc4114..0xbcc411f

    // 0xbcc4124..0xbcc4144
    0xbcc4144  call 0xEEC6D80                                ; -> sub_eec6d80
    LIFT-BODY;  // implement basic block 0xbcc4124..0xbcc4144

    // 0xbcc4149..0xbcc414e
    0xbcc4149  call 0x1A2800                                 ; -> sub_1a2800
    LIFT-BODY;  // implement basic block 0xbcc4149..0xbcc414e

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bcc3fa0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbcc3fa0, 0xbcc414f) (rdis dis output, two spaces after address):
#if 0
0xbcc40a5  call 0xEBCE390                                ; -> sub_ebce390
0xbcc40e4  call 0xBC60740                                ; -> sub_bc60740
0xbcc411f  call 0xE951550                                ; -> sub_e951550
0xbcc4144  call 0xEEC6D80                                ; -> sub_eec6d80
0xbcc4149  call 0x1A2800                                 ; -> sub_1a2800
#endif

// Calls out of lifted code:
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_bc60740 (0xbc60740, lift set) - call 0xBC60740                                ; -> sub_bc60740
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   sub_eec6d80 (0xeec6d80, lift set) - call 0xEEC6D80                                ; -> sub_eec6d80
//   sub_1a2800 (0x1a2800, boundary) - call 0x1A2800                                 ; -> sub_1a2800
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bcc3fa0, "sub_bcc3fa0", 0xbcc3fa0, sub_bcc3fa0, nullptr);

} // namespace native::bgfx