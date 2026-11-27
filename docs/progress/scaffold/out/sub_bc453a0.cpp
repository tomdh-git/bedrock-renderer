// LIFT 0xbc453a0 size 0x3d9 1.26.62.01 sub_bc453a0
#include "sub_bc453a0.h"

#include <cstdint>
#include <cstddef>

namespace native::bgfx {

// Placeholder LIFT_FN registry entry: the real definition lives in
// client/features/render/native/Lift.h (unit X0d framework). The skeleton does not
// include Lift.h so it compiles standalone for a syntax check; at integration time
// replace this block with the real LIFT_FN(...) and include Lift.h.
#ifndef LIFT_FN
#define LIFT_FN(ID, NAME, RVA, LIFTED, FOOTPRINT) /* LIFT_FN placeholder; real registry entry from Lift.h */
#endif
LIFT_FN(sub_bc453a0, "sub_bc453a0", 0xbc453a0, sub_bc453a0, nullptr);

// Verbatim call instructions from the disassembly of [0xbc453a0, 0xbc45779) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbc453b3  call qword ptr [0xF9A6FF0]
0xbc454bd  call qword ptr [0xF99FFA0]
0xbc45585  call 0x9BC830
0xbc4564f  call qword ptr [0xF99FFA0]
0xbc456a6  call 0xAC4F0
0xbc456e9  call 0xAC370
0xbc4576f  call 0x9BC830
#endif

// Ranges: the whole function body [0xbc453a0, 0xbc45779) is one lifted region (scaffold placeholder).
uintptr_t sub_bc453a0(sub_bc453a0_state* self) {
    // 0xbc453a0..0xbc45779: sub_bc453a0
    (void)self;
    return 0;   // [open] return value / body TBD
}

} // namespace native::bgfx
