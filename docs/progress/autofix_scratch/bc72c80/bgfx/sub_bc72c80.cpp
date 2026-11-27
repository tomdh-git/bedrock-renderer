// LIFT 0xbc72c80 size 0x321 1.26.62.01 bgfx::createProgram(vsh, fsh, destroy)

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc72c80.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_bc79790

extern "C" void sub_bc79790(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ebce390

extern "C" void sub_ebce390(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ebdbf10

extern "C" void sub_ebdbf10(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ebdbf20

extern "C" void sub_ebdbf20(/* LIFT-BODY: exact ABI from dossier */);

} // namespace


// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original

extern "C" void sub_bc72c80(/* LIFT-BODY: exact args */);

void sub_bc72c80(/* LIFT-BODY: exact args */) {
    // 0xbc72c80..0xbc72cfd

    0xbc72cbb  call 0xEBDBF10                                ; -> sub_ebdbf10
    LIFT-BODY;  // implement basic block 0xbc72c80..0xbc72cfd


    // 0xbc72d00..0xbc72d30

    LIFT-BODY;  // implement basic block 0xbc72d00..0xbc72d30


    // 0xbc72d32..0xbc72df1

    LIFT-BODY;  // implement basic block 0xbc72d32..0xbc72df1


    // 0xbc72e00..0xbc72e2d

    LIFT-BODY;  // implement basic block 0xbc72e00..0xbc72e2d


    // 0xbc72e32..0xbc72e37

    LIFT-BODY;  // implement basic block 0xbc72e32..0xbc72e37


    // 0xbc72e39..0xbc72e79

    LIFT-BODY;  // implement basic block 0xbc72e39..0xbc72e79


    // 0xbc72e7b..0xbc72e7b

    LIFT-BODY;  // implement basic block 0xbc72e7b..0xbc72e7b


    // 0xbc72e81..0xbc72e84

    LIFT-BODY;  // implement basic block 0xbc72e81..0xbc72e84


    // 0xbc72e86..0xbc72e9f

    0xbc72e8d  call 0xBC79790                                ; -> sub_bc79790
    0xbc72e9a  call 0xBC79790                                ; -> sub_bc79790
    LIFT-BODY;  // implement basic block 0xbc72e86..0xbc72e9f


    // 0xbc72ea0..0xbc72ea5

    LIFT-BODY;  // implement basic block 0xbc72ea0..0xbc72ea5


    // 0xbc72ea9..0xbc72ea9

    LIFT-BODY;  // implement basic block 0xbc72ea9..0xbc72ea9


    // 0xbc72ead..0xbc72ec7

    0xbc72eb0  call 0xEBDBF20                                ; -> sub_ebdbf20
    LIFT-BODY;  // implement basic block 0xbc72ead..0xbc72ec7


    // 0xbc72ec8..0xbc72ed9

    LIFT-BODY;  // implement basic block 0xbc72ec8..0xbc72ed9


    // 0xbc72edf..0xbc72f9c

    0xbc72f06  call 0xEBCE390                                ; -> sub_ebce390
    0xbc72f34  call 0xEBCE390                                ; -> sub_ebce390
    0xbc72f5b  call 0xEBCE390                                ; -> sub_ebce390
    0xbc72f85  call 0xEBCE390                                ; -> sub_ebce390
    LIFT-BODY;  // implement basic block 0xbc72edf..0xbc72f9c


}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)

static_assert(true, "sub_bc72c80: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc72c80, 0xbc72fa1) (rdis dis output, two spaces after address):

#if 0
0xbc72cbb  call 0xEBDBF10                                ; -> sub_ebdbf10
0xbc72e8d  call 0xBC79790                                ; -> sub_bc79790
0xbc72e9a  call 0xBC79790                                ; -> sub_bc79790
0xbc72eb0  call 0xEBDBF20                                ; -> sub_ebdbf20
0xbc72f06  call 0xEBCE390                                ; -> sub_ebce390
0xbc72f34  call 0xEBCE390                                ; -> sub_ebce390
0xbc72f5b  call 0xEBCE390                                ; -> sub_ebce390
0xbc72f85  call 0xEBCE390                                ; -> sub_ebce390
#endif

// Calls out of lifted code:

//   sub_ebdbf10 (0xebdbf10, lift set) - call 0xEBDBF10                                ; -> sub_ebdbf10

//   sub_bc79790 (0xbc79790, lift set) - call 0xBC79790                                ; -> sub_bc79790

//   sub_bc79790 (0xbc79790, lift set) - call 0xBC79790                                ; -> sub_bc79790

//   sub_ebdbf20 (0xebdbf20, lift set) - call 0xEBDBF20                                ; -> sub_ebdbf20

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv


LIFT_FN(sub_bc72c80, "sub_bc72c80", 0xbc72c80, sub_bc72c80, nullptr);

} // namespace native::bgfx