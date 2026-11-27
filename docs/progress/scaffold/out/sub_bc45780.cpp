// LIFT 0xbc45780 size 0x1da 1.26.62.01 sub_bc45780
#include "sub_bc45780.h"

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
LIFT_FN(sub_bc45780, "sub_bc45780", 0xbc45780, sub_bc45780, nullptr);

// Verbatim call instructions from the disassembly of [0xbc45780, 0xbc4595a) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbc45837  call 0xAC4F0
0xbc45904  call 0xBC45C40
#endif

// Ranges: the whole function body [0xbc45780, 0xbc4595a) is one lifted region (scaffold placeholder).
uintptr_t sub_bc45780(sub_bc45780_state* self) {
    // 0xbc45780..0xbc4595a: sub_bc45780
    (void)self;
    return 0;   // [open] return value / body TBD
}

} // namespace native::bgfx
