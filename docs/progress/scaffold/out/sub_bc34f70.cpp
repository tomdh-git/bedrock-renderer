// LIFT 0xbc34f70 size 0x113 1.26.62.01 sub_bc34f70
#include "sub_bc34f70.h"

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
LIFT_FN(sub_bc34f70, "sub_bc34f70", 0xbc34f70, sub_bc34f70, nullptr);

// Verbatim call instructions from the disassembly of [0xbc34f70, 0xbc35083) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbc34f99  call qword ptr [0xF99FFA0]
0xbc34fb1  call 0x655CEA0
0xbc34ff9  call 0xE935700
0xbc35010  call 0x56C9740
0xbc3504a  call 0xE935700
0xbc3507c  call qword ptr [0xF9A8C78]
#endif

// Ranges: the whole function body [0xbc34f70, 0xbc35083) is one lifted region (scaffold placeholder).
uintptr_t sub_bc34f70(sub_bc34f70_state* self) {
    // 0xbc34f70..0xbc35083: sub_bc34f70
    (void)self;
    return 0;   // [open] return value / body TBD
}

} // namespace native::bgfx
