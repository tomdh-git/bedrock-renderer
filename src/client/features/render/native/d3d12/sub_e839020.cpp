// LIFT 0xe839020 size 0x72f 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e839020.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Forward declaration for callee in lift set: sub_e935700
extern "C" void sub_e935700(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe8390f9: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839126: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839147: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839183: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8391a4: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8391dd: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8391f0: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe839224: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839245: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839281: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8392a2: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe83935b: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe83937c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8393b4: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8393d9: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839482: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8394a6: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8394f1: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe83951a: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8395ab: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8395cc: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839604: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839629: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe83967b: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8396a6: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe839723: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe839730: call 0x75740                                  ; -> sub_75740 -> sub_75740
//   0xe839748: call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e839020(/* LIFT-BODY: exact args */);

void sub_e839020(/* LIFT-BODY: exact args */) {
    // 0xe839020..0xe839063
    LIFT-BODY;  // implement basic block 0xe839020..0xe839063

    // 0xe839068..0xe839102
    0xe8390f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe839068..0xe839102

    // 0xe839108..0xe839117
    LIFT-BODY;  // implement basic block 0xe839108..0xe839117

    // 0xe83911c..0xe839147
    0xe839126  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe839147  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83911c..0xe839147

    // 0xe83914d..0xe83914d
    LIFT-BODY;  // implement basic block 0xe83914d..0xe83914d

    // 0xe839156..0xe839176
    LIFT-BODY;  // implement basic block 0xe839156..0xe839176

    // 0xe839178..0xe8391a4
    0xe839183  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8391a4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe839178..0xe8391a4

    // 0xe8391aa..0xe8391aa
    LIFT-BODY;  // implement basic block 0xe8391aa..0xe8391aa

    // 0xe8391b3..0xe8391ca
    LIFT-BODY;  // implement basic block 0xe8391b3..0xe8391ca

    // 0xe8391cf..0xe8391f0
    0xe8391dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8391f0  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe8391cf..0xe8391f0

    // 0xe8391f5..0xe8391f5
    LIFT-BODY;  // implement basic block 0xe8391f5..0xe8391f5

    // 0xe8391f8..0xe839218
    LIFT-BODY;  // implement basic block 0xe8391f8..0xe839218

    // 0xe83921a..0xe839245
    0xe839224  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe839245  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83921a..0xe839245

    // 0xe83924b..0xe83924b
    LIFT-BODY;  // implement basic block 0xe83924b..0xe83924b

    // 0xe839254..0xe839274
    LIFT-BODY;  // implement basic block 0xe839254..0xe839274

    // 0xe839276..0xe8392a2
    0xe839281  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8392a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe839276..0xe8392a2

    // 0xe8392a8..0xe8392a8
    LIFT-BODY;  // implement basic block 0xe8392a8..0xe8392a8

    // 0xe8392b1..0xe8392e3
    LIFT-BODY;  // implement basic block 0xe8392b1..0xe8392e3

    // 0xe8392f0..0xe8392f0
    LIFT-BODY;  // implement basic block 0xe8392f0..0xe8392f0

    // 0xe8392f4..0xe8392f4
    LIFT-BODY;  // implement basic block 0xe8392f4..0xe8392f4

    // 0xe8392fd..0xe83931f
    LIFT-BODY;  // implement basic block 0xe8392fd..0xe83931f

    // 0xe839325..0xe839347
    LIFT-BODY;  // implement basic block 0xe839325..0xe839347

    // 0xe839350..0xe83937c
    0xe83935b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe83937c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe839350..0xe83937c

    // 0xe839382..0xe839382
    LIFT-BODY;  // implement basic block 0xe839382..0xe839382

    // 0xe83938b..0xe8393df
    0xe8393b4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8393d9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83938b..0xe8393df

    // 0xe8393e4..0xe8393e4
    LIFT-BODY;  // implement basic block 0xe8393e4..0xe8393e4

    // 0xe8393e8..0xe8393f6
    LIFT-BODY;  // implement basic block 0xe8393e8..0xe8393f6

    // 0xe839400..0xe839400
    LIFT-BODY;  // implement basic block 0xe839400..0xe839400

    // 0xe839408..0xe839408
    LIFT-BODY;  // implement basic block 0xe839408..0xe839408

    // 0xe839411..0xe839435
    LIFT-BODY;  // implement basic block 0xe839411..0xe839435

    // 0xe83943b..0xe839464
    LIFT-BODY;  // implement basic block 0xe83943b..0xe839464

    // 0xe839470..0xe8394a6
    0xe839482  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8394a6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe839470..0xe8394a6

    // 0xe8394ac..0xe8394ac
    LIFT-BODY;  // implement basic block 0xe8394ac..0xe8394ac

    // 0xe8394b4..0xe839520
    0xe8394f1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe83951a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8394b4..0xe839520

    // 0xe839525..0xe839538
    LIFT-BODY;  // implement basic block 0xe839525..0xe839538

    // 0xe839540..0xe839540
    LIFT-BODY;  // implement basic block 0xe839540..0xe839540

    // 0xe839544..0xe839544
    LIFT-BODY;  // implement basic block 0xe839544..0xe839544

    // 0xe83954d..0xe83956f
    LIFT-BODY;  // implement basic block 0xe83954d..0xe83956f

    // 0xe839575..0xe839597
    LIFT-BODY;  // implement basic block 0xe839575..0xe839597

    // 0xe8395a0..0xe8395cc
    0xe8395ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8395cc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8395a0..0xe8395cc

    // 0xe8395d2..0xe8395d2
    LIFT-BODY;  // implement basic block 0xe8395d2..0xe8395d2

    // 0xe8395db..0xe83962f
    0xe839604  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe839629  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8395db..0xe83962f

    // 0xe839634..0xe839634
    LIFT-BODY;  // implement basic block 0xe839634..0xe839634

    // 0xe839637..0xe83964f
    LIFT-BODY;  // implement basic block 0xe839637..0xe83964f

    // 0xe839650..0xe839662
    LIFT-BODY;  // implement basic block 0xe839650..0xe839662

    // 0xe839664..0xe839681
    0xe83967b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe839664..0xe839681

    // 0xe83968a..0xe8396b5
    0xe8396a6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83968a..0xe8396b5

    // 0xe8396b7..0xe8396b7
    LIFT-BODY;  // implement basic block 0xe8396b7..0xe8396b7

    // 0xe8396ba..0xe8396e0
    LIFT-BODY;  // implement basic block 0xe8396ba..0xe8396e0

    // 0xe8396e3..0xe8396e6
    0xe8396e6  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xe8396e3..0xe8396e6

    // 0xe8396eb..0xe839708
    LIFT-BODY;  // implement basic block 0xe8396eb..0xe839708

    // 0xe83970c..0xe83971c
    LIFT-BODY;  // implement basic block 0xe83970c..0xe83971c

    // 0xe83971d..0xe83972b
    0xe839723  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe83971d..0xe83972b

    // 0xe839730..0xe839730
    0xe839730  call 0x75740                                  ; -> sub_75740
    LIFT-BODY;  // implement basic block 0xe839730..0xe839730

    // 0xe839735..0xe83974e
    0xe839748  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
    LIFT-BODY;  // implement basic block 0xe839735..0xe83974e

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e839020: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe839020, 0xe83974f) (rdis dis output, two spaces after address):
#if 0
0xe8390f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839126  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839147  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839183  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8391a4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8391dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8391f0  call 0x9BC830                                 ; -> sub_9bc830
0xe839224  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839245  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839281  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8392a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83935b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83937c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8393b4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8393d9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839482  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8394a6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8394f1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83951a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8395ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8395cc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839604  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe839629  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83967b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8396a6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8396e6  call 0xE935700                                ; -> sub_e935700
0xe839723  call 0x9BC830                                 ; -> sub_9bc830
0xe839730  call 0x75740                                  ; -> sub_75740
0xe839748  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_75740 (0x75740, boundary) - call 0x75740                                  ; -> sub_75740
//   call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e839020, "sub_e839020", 0xe839020, sub_e839020, nullptr);

} // namespace native::d3d12