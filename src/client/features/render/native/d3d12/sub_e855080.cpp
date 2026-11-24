// LIFT 0xe855080 size 0xa6b 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e855080.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Forward declaration for callee in lift set: sub_e855080
extern "C" void sub_e855080(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec6de0
extern "C" void sub_eec6de0(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe855ae5: call 0xE951550                                ; -> sub_e951550 -> sub_e951550

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e855080(/* LIFT-BODY: exact args */);

void sub_e855080(/* LIFT-BODY: exact args */) {
    // 0xe855080..0xe8550b7
    LIFT-BODY;  // implement basic block 0xe855080..0xe8550b7

    // 0xe8550bd..0xe8550d8
    LIFT-BODY;  // implement basic block 0xe8550bd..0xe8550d8

    // 0xe8550e0..0xe8550f1
    0xe8550ec  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xe8550e0..0xe8550f1

    // 0xe8550f4..0xe855103
    LIFT-BODY;  // implement basic block 0xe8550f4..0xe855103

    // 0xe855109..0xe855122
    LIFT-BODY;  // implement basic block 0xe855109..0xe855122

    // 0xe855130..0xe855147
    LIFT-BODY;  // implement basic block 0xe855130..0xe855147

    // 0xe855149..0xe855162
    LIFT-BODY;  // implement basic block 0xe855149..0xe855162

    // 0xe855170..0xe8551f0
    LIFT-BODY;  // implement basic block 0xe855170..0xe8551f0

    // 0xe8551f6..0xe855268
    LIFT-BODY;  // implement basic block 0xe8551f6..0xe855268

    // 0xe85526b..0xe8552b2
    LIFT-BODY;  // implement basic block 0xe85526b..0xe8552b2

    // 0xe8552b7..0xe85532d
    LIFT-BODY;  // implement basic block 0xe8552b7..0xe85532d

    // 0xe855330..0xe85537f
    LIFT-BODY;  // implement basic block 0xe855330..0xe85537f

    // 0xe855385..0xe8553f8
    LIFT-BODY;  // implement basic block 0xe855385..0xe8553f8

    // 0xe8553fb..0xe855437
    LIFT-BODY;  // implement basic block 0xe8553fb..0xe855437

    // 0xe85543c..0xe8554bb
    LIFT-BODY;  // implement basic block 0xe85543c..0xe8554bb

    // 0xe8554c0..0xe8554fb
    LIFT-BODY;  // implement basic block 0xe8554c0..0xe8554fb

    // 0xe855500..0xe855575
    LIFT-BODY;  // implement basic block 0xe855500..0xe855575

    // 0xe855580..0xe855597
    LIFT-BODY;  // implement basic block 0xe855580..0xe855597

    // 0xe855599..0xe8555a1
    LIFT-BODY;  // implement basic block 0xe855599..0xe8555a1

    // 0xe8555b0..0xe8555c7
    LIFT-BODY;  // implement basic block 0xe8555b0..0xe8555c7

    // 0xe8555c9..0xe8555d1
    LIFT-BODY;  // implement basic block 0xe8555c9..0xe8555d1

    // 0xe8555e0..0xe8555e0
    LIFT-BODY;  // implement basic block 0xe8555e0..0xe8555e0

    // 0xe8555e4..0xe8555e4
    LIFT-BODY;  // implement basic block 0xe8555e4..0xe8555e4

    // 0xe8555e8..0xe855637
    LIFT-BODY;  // implement basic block 0xe8555e8..0xe855637

    // 0xe855639..0xe855643
    LIFT-BODY;  // implement basic block 0xe855639..0xe855643

    // 0xe855650..0xe855650
    LIFT-BODY;  // implement basic block 0xe855650..0xe855650

    // 0xe855653..0xe855659
    LIFT-BODY;  // implement basic block 0xe855653..0xe855659

    // 0xe85565b..0xe8556ae
    LIFT-BODY;  // implement basic block 0xe85565b..0xe8556ae

    // 0xe8556b0..0xe8556b3
    LIFT-BODY;  // implement basic block 0xe8556b0..0xe8556b3

    // 0xe8556b6..0xe8556be
    LIFT-BODY;  // implement basic block 0xe8556b6..0xe8556be

    // 0xe8556c4..0xe85570d
    LIFT-BODY;  // implement basic block 0xe8556c4..0xe85570d

    // 0xe855712..0xe855742
    LIFT-BODY;  // implement basic block 0xe855712..0xe855742

    // 0xe855745..0xe855783
    LIFT-BODY;  // implement basic block 0xe855745..0xe855783

    // 0xe855788..0xe8557be
    LIFT-BODY;  // implement basic block 0xe855788..0xe8557be

    // 0xe8557c1..0xe8557fc
    LIFT-BODY;  // implement basic block 0xe8557c1..0xe8557fc

    // 0xe855800..0xe855831
    0xe855824  call 0xE855080                                ; -> sub_e855080
    LIFT-BODY;  // implement basic block 0xe855800..0xe855831

    // 0xe855840..0xe855851
    0xe855849  call 0xE855080                                ; -> sub_e855080
    LIFT-BODY;  // implement basic block 0xe855840..0xe855851

    // 0xe855854..0xe85586a
    LIFT-BODY;  // implement basic block 0xe855854..0xe85586a

    // 0xe855870..0xe85589a
    LIFT-BODY;  // implement basic block 0xe855870..0xe85589a

    // 0xe8558a0..0xe8558a0
    LIFT-BODY;  // implement basic block 0xe8558a0..0xe8558a0

    // 0xe8558a3..0xe8558b6
    LIFT-BODY;  // implement basic block 0xe8558a3..0xe8558b6

    // 0xe8558bc..0xe8558d7
    LIFT-BODY;  // implement basic block 0xe8558bc..0xe8558d7

    // 0xe8558d9..0xe8558f1
    LIFT-BODY;  // implement basic block 0xe8558d9..0xe8558f1

    // 0xe8558f4..0xe8558f9
    LIFT-BODY;  // implement basic block 0xe8558f4..0xe8558f9

    // 0xe855900..0xe85593d
    LIFT-BODY;  // implement basic block 0xe855900..0xe85593d

    // 0xe855940..0xe855945
    LIFT-BODY;  // implement basic block 0xe855940..0xe855945

    // 0xe855950..0xe855950
    LIFT-BODY;  // implement basic block 0xe855950..0xe855950

    // 0xe855958..0xe855971
    LIFT-BODY;  // implement basic block 0xe855958..0xe855971

    // 0xe855977..0xe855994
    LIFT-BODY;  // implement basic block 0xe855977..0xe855994

    // 0xe8559a0..0xe8559a0
    LIFT-BODY;  // implement basic block 0xe8559a0..0xe8559a0

    // 0xe8559a2..0xe8559b4
    LIFT-BODY;  // implement basic block 0xe8559a2..0xe8559b4

    // 0xe8559ba..0xe8559f4
    LIFT-BODY;  // implement basic block 0xe8559ba..0xe8559f4

    // 0xe8559fa..0xe855a1f
    LIFT-BODY;  // implement basic block 0xe8559fa..0xe855a1f

    // 0xe855a22..0xe855a2b
    LIFT-BODY;  // implement basic block 0xe855a22..0xe855a2b

    // 0xe855a30..0xe855a6b
    LIFT-BODY;  // implement basic block 0xe855a30..0xe855a6b

    // 0xe855a70..0xe855a70
    LIFT-BODY;  // implement basic block 0xe855a70..0xe855a70

    // 0xe855a78..0xe855a90
    LIFT-BODY;  // implement basic block 0xe855a78..0xe855a90

    // 0xe855a96..0xe855ab1
    LIFT-BODY;  // implement basic block 0xe855a96..0xe855ab1

    // 0xe855ab3..0xe855adc
    LIFT-BODY;  // implement basic block 0xe855ab3..0xe855adc

    // 0xe855add..0xe855aea
    0xe855ae5  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xe855add..0xe855aea

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e855080: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe855080, 0xe855aeb) (rdis dis output, two spaces after address):
#if 0
0xe8550ec  call 0xEEC6DE0                                ; -> sub_eec6de0
0xe855824  call 0xE855080                                ; -> sub_e855080
0xe855849  call 0xE855080                                ; -> sub_e855080
0xe855ae5  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   sub_e855080 (0xe855080, lift set) - call 0xE855080                                ; -> sub_e855080
//   sub_e855080 (0xe855080, lift set) - call 0xE855080                                ; -> sub_e855080
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e855080, "sub_e855080", 0xe855080, sub_e855080, nullptr);

} // namespace native::d3d12