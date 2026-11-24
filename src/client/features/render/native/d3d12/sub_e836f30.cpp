// LIFT 0xe836f30 size 0x91e 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e836f30.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe8370b8: call 0xA7AAF0                                 ; -> sub_a7aaf0 -> sub_a7aaf0
//   0xe8370fa: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8371d0: call 0xA7AAF0                                 ; -> sub_a7aaf0 -> sub_a7aaf0
//   0xe837212: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8372c9: call 0xA7AAF0                                 ; -> sub_a7aaf0 -> sub_a7aaf0
//   0xe83730b: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8373ce: call 0xA7AAF0                                 ; -> sub_a7aaf0 -> sub_a7aaf0
//   0xe837410: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8374d8: call 0xA7AAF0                                 ; -> sub_a7aaf0 -> sub_a7aaf0
//   0xe83751a: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe837603: call 0xA7AAF0                                 ; -> sub_a7aaf0 -> sub_a7aaf0
//   0xe837645: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe837723: call 0xA7AAF0                                 ; -> sub_a7aaf0 -> sub_a7aaf0
//   0xe837765: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8377e3: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe8377f3: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe837803: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe837813: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe837823: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe837833: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xe837843: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e836f30(/* LIFT-BODY: exact args */);

void sub_e836f30(/* LIFT-BODY: exact args */) {
    // 0xe836f30..0xe836f8c
    LIFT-BODY;  // implement basic block 0xe836f30..0xe836f8c

    // 0xe836f92..0xe836fd6
    LIFT-BODY;  // implement basic block 0xe836f92..0xe836fd6

    // 0xe836fdb..0xe837007
    LIFT-BODY;  // implement basic block 0xe836fdb..0xe837007

    // 0xe837009..0xe83704b
    LIFT-BODY;  // implement basic block 0xe837009..0xe83704b

    // 0xe837050..0xe837077
    LIFT-BODY;  // implement basic block 0xe837050..0xe837077

    // 0xe83707c..0xe83707c
    LIFT-BODY;  // implement basic block 0xe83707c..0xe83707c

    // 0xe83707f..0xe8370c2
    0xe8370b8  call 0xA7AAF0                                 ; -> sub_a7aaf0
    LIFT-BODY;  // implement basic block 0xe83707f..0xe8370c2

    // 0xe8370c6..0xe837107
    0xe8370fa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8370c6..0xe837107

    // 0xe83710d..0xe837123
    LIFT-BODY;  // implement basic block 0xe83710d..0xe837123

    // 0xe837127..0xe83715f
    LIFT-BODY;  // implement basic block 0xe837127..0xe83715f

    // 0xe837164..0xe837190
    LIFT-BODY;  // implement basic block 0xe837164..0xe837190

    // 0xe837195..0xe837195
    LIFT-BODY;  // implement basic block 0xe837195..0xe837195

    // 0xe837198..0xe8371da
    0xe8371d0  call 0xA7AAF0                                 ; -> sub_a7aaf0
    LIFT-BODY;  // implement basic block 0xe837198..0xe8371da

    // 0xe8371de..0xe83721f
    0xe837212  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8371de..0xe83721f

    // 0xe837225..0xe83723b
    LIFT-BODY;  // implement basic block 0xe837225..0xe83723b

    // 0xe83723f..0xe83728c
    LIFT-BODY;  // implement basic block 0xe83723f..0xe83728c

    // 0xe83728e..0xe83728e
    LIFT-BODY;  // implement basic block 0xe83728e..0xe83728e

    // 0xe837291..0xe8372d3
    0xe8372c9  call 0xA7AAF0                                 ; -> sub_a7aaf0
    LIFT-BODY;  // implement basic block 0xe837291..0xe8372d3

    // 0xe8372d7..0xe837318
    0xe83730b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8372d7..0xe837318

    // 0xe83731e..0xe837334
    LIFT-BODY;  // implement basic block 0xe83731e..0xe837334

    // 0xe837338..0xe837392
    LIFT-BODY;  // implement basic block 0xe837338..0xe837392

    // 0xe837397..0xe837397
    LIFT-BODY;  // implement basic block 0xe837397..0xe837397

    // 0xe837399..0xe8373d8
    0xe8373ce  call 0xA7AAF0                                 ; -> sub_a7aaf0
    LIFT-BODY;  // implement basic block 0xe837399..0xe8373d8

    // 0xe8373dc..0xe83741d
    0xe837410  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8373dc..0xe83741d

    // 0xe837423..0xe837439
    LIFT-BODY;  // implement basic block 0xe837423..0xe837439

    // 0xe83743d..0xe83745e
    LIFT-BODY;  // implement basic block 0xe83743d..0xe83745e

    // 0xe837462..0xe837497
    LIFT-BODY;  // implement basic block 0xe837462..0xe837497

    // 0xe837499..0xe837499
    LIFT-BODY;  // implement basic block 0xe837499..0xe837499

    // 0xe83749b..0xe8374e2
    0xe8374d8  call 0xA7AAF0                                 ; -> sub_a7aaf0
    LIFT-BODY;  // implement basic block 0xe83749b..0xe8374e2

    // 0xe8374e6..0xe837527
    0xe83751a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8374e6..0xe837527

    // 0xe83752d..0xe837543
    LIFT-BODY;  // implement basic block 0xe83752d..0xe837543

    // 0xe837547..0xe83756c
    LIFT-BODY;  // implement basic block 0xe837547..0xe83756c

    // 0xe837570..0xe83759d
    LIFT-BODY;  // implement basic block 0xe837570..0xe83759d

    // 0xe8375a2..0xe8375c3
    LIFT-BODY;  // implement basic block 0xe8375a2..0xe8375c3

    // 0xe8375c8..0xe8375c8
    LIFT-BODY;  // implement basic block 0xe8375c8..0xe8375c8

    // 0xe8375ca..0xe83760d
    0xe837603  call 0xA7AAF0                                 ; -> sub_a7aaf0
    LIFT-BODY;  // implement basic block 0xe8375ca..0xe83760d

    // 0xe837611..0xe837652
    0xe837645  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe837611..0xe837652

    // 0xe837658..0xe83766e
    LIFT-BODY;  // implement basic block 0xe837658..0xe83766e

    // 0xe837672..0xe8376b5
    LIFT-BODY;  // implement basic block 0xe837672..0xe8376b5

    // 0xe8376b9..0xe8376c5
    LIFT-BODY;  // implement basic block 0xe8376b9..0xe8376c5

    // 0xe8376c9..0xe8376c9
    LIFT-BODY;  // implement basic block 0xe8376c9..0xe8376c9

    // 0xe8376d1..0xe8376d3
    LIFT-BODY;  // implement basic block 0xe8376d1..0xe8376d3

    // 0xe8376d7..0xe8376e7
    LIFT-BODY;  // implement basic block 0xe8376d7..0xe8376e7

    // 0xe8376e8..0xe8376e8
    LIFT-BODY;  // implement basic block 0xe8376e8..0xe8376e8

    // 0xe8376ea..0xe83772d
    0xe837723  call 0xA7AAF0                                 ; -> sub_a7aaf0
    LIFT-BODY;  // implement basic block 0xe8376ea..0xe83772d

    // 0xe837731..0xe837772
    0xe837765  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe837731..0xe837772

    // 0xe837778..0xe83778e
    LIFT-BODY;  // implement basic block 0xe837778..0xe83778e

    // 0xe837792..0xe8377d9
    LIFT-BODY;  // implement basic block 0xe837792..0xe8377d9

    // 0xe8377de..0xe8377e9
    0xe8377e3  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe8377de..0xe8377e9

    // 0xe8377ee..0xe8377f9
    0xe8377f3  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe8377ee..0xe8377f9

    // 0xe8377fe..0xe837809
    0xe837803  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe8377fe..0xe837809

    // 0xe83780e..0xe837819
    0xe837813  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe83780e..0xe837819

    // 0xe83781e..0xe837829
    0xe837823  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe83781e..0xe837829

    // 0xe83782e..0xe837839
    0xe837833  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe83782e..0xe837839

    // 0xe83783e..0xe837849
    0xe837843  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xe83783e..0xe837849

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e836f30: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe836f30, 0xe83784e) (rdis dis output, two spaces after address):
#if 0
0xe8370b8  call 0xA7AAF0                                 ; -> sub_a7aaf0
0xe8370fa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8371d0  call 0xA7AAF0                                 ; -> sub_a7aaf0
0xe837212  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8372c9  call 0xA7AAF0                                 ; -> sub_a7aaf0
0xe83730b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8373ce  call 0xA7AAF0                                 ; -> sub_a7aaf0
0xe837410  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8374d8  call 0xA7AAF0                                 ; -> sub_a7aaf0
0xe83751a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe837603  call 0xA7AAF0                                 ; -> sub_a7aaf0
0xe837645  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe837723  call 0xA7AAF0                                 ; -> sub_a7aaf0
0xe837765  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8377e3  call 0x9BC830                                 ; -> sub_9bc830
0xe8377f3  call 0x9BC830                                 ; -> sub_9bc830
0xe837803  call 0x9BC830                                 ; -> sub_9bc830
0xe837813  call 0x9BC830                                 ; -> sub_9bc830
0xe837823  call 0x9BC830                                 ; -> sub_9bc830
0xe837833  call 0x9BC830                                 ; -> sub_9bc830
0xe837843  call 0x9BC830                                 ; -> sub_9bc830
#endif

// Calls out of lifted code:
//   sub_a7aaf0 (0xa7aaf0, boundary) - call 0xA7AAF0                                 ; -> sub_a7aaf0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a7aaf0 (0xa7aaf0, boundary) - call 0xA7AAF0                                 ; -> sub_a7aaf0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a7aaf0 (0xa7aaf0, boundary) - call 0xA7AAF0                                 ; -> sub_a7aaf0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a7aaf0 (0xa7aaf0, boundary) - call 0xA7AAF0                                 ; -> sub_a7aaf0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a7aaf0 (0xa7aaf0, boundary) - call 0xA7AAF0                                 ; -> sub_a7aaf0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a7aaf0 (0xa7aaf0, boundary) - call 0xA7AAF0                                 ; -> sub_a7aaf0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a7aaf0 (0xa7aaf0, boundary) - call 0xA7AAF0                                 ; -> sub_a7aaf0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e836f30, "sub_e836f30", 0xe836f30, sub_e836f30, nullptr);

} // namespace native::d3d12