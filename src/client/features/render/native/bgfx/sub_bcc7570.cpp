// LIFT 0xbcc7570 size 0x54e 1.26.62.01 sub_bcc7570
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcc7570.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_e935700
extern "C" void sub_e935700(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec5850
extern "C" void sub_eec5850(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec73f0
extern "C" void sub_eec73f0(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbcc7612: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc7761: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc77b5: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc7a61: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc7a6e: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc7a7c: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc7ab7: call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bcc7570(/* LIFT-BODY: exact args */);

void sub_bcc7570(/* LIFT-BODY: exact args */) {
    // 0xbcc7570..0xbcc75bd
    LIFT-BODY;  // implement basic block 0xbcc7570..0xbcc75bd

    // 0xbcc75bf..0xbcc75c6
    LIFT-BODY;  // implement basic block 0xbcc75bf..0xbcc75c6

    // 0xbcc75d0..0xbcc75e1
    LIFT-BODY;  // implement basic block 0xbcc75d0..0xbcc75e1

    // 0xbcc75e3..0xbcc75e8
    LIFT-BODY;  // implement basic block 0xbcc75e3..0xbcc75e8

    // 0xbcc75eb..0xbcc761e
    0xbcc7612  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc75eb..0xbcc761e

    // 0xbcc7624..0xbcc763b
    LIFT-BODY;  // implement basic block 0xbcc7624..0xbcc763b

    // 0xbcc763d..0xbcc764e
    LIFT-BODY;  // implement basic block 0xbcc763d..0xbcc764e

    // 0xbcc7652..0xbcc7664
    LIFT-BODY;  // implement basic block 0xbcc7652..0xbcc7664

    // 0xbcc7666..0xbcc767a
    LIFT-BODY;  // implement basic block 0xbcc7666..0xbcc767a

    // 0xbcc767e..0xbcc76e2
    0xbcc7692  call 0xEEC73F0                                ; -> sub_eec73f0
    LIFT-BODY;  // implement basic block 0xbcc767e..0xbcc76e2

    // 0xbcc76e5..0xbcc776e
    0xbcc7761  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc76e5..0xbcc776e

    // 0xbcc7774..0xbcc7783
    LIFT-BODY;  // implement basic block 0xbcc7774..0xbcc7783

    // 0xbcc7785..0xbcc779f
    LIFT-BODY;  // implement basic block 0xbcc7785..0xbcc779f

    // 0xbcc77a4..0xbcc77c2
    0xbcc77b5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc77a4..0xbcc77c2

    // 0xbcc77c8..0xbcc77f7
    LIFT-BODY;  // implement basic block 0xbcc77c8..0xbcc77f7

    // 0xbcc77fa..0xbcc77fa
    0xbcc77fa  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc77fa..0xbcc77fa

    // 0xbcc77ff..0xbcc781c
    LIFT-BODY;  // implement basic block 0xbcc77ff..0xbcc781c

    // 0xbcc781e..0xbcc783d
    LIFT-BODY;  // implement basic block 0xbcc781e..0xbcc783d

    // 0xbcc7840..0xbcc785b
    LIFT-BODY;  // implement basic block 0xbcc7840..0xbcc785b

    // 0xbcc7860..0xbcc786c
    LIFT-BODY;  // implement basic block 0xbcc7860..0xbcc786c

    // 0xbcc786e..0xbcc788d
    LIFT-BODY;  // implement basic block 0xbcc786e..0xbcc788d

    // 0xbcc7890..0xbcc78ab
    LIFT-BODY;  // implement basic block 0xbcc7890..0xbcc78ab

    // 0xbcc78b0..0xbcc78ba
    LIFT-BODY;  // implement basic block 0xbcc78b0..0xbcc78ba

    // 0xbcc78bc..0xbcc78d9
    LIFT-BODY;  // implement basic block 0xbcc78bc..0xbcc78d9

    // 0xbcc78e0..0xbcc78e0
    LIFT-BODY;  // implement basic block 0xbcc78e0..0xbcc78e0

    // 0xbcc78e3..0xbcc78e3
    LIFT-BODY;  // implement basic block 0xbcc78e3..0xbcc78e3

    // 0xbcc78e7..0xbcc78ea
    LIFT-BODY;  // implement basic block 0xbcc78e7..0xbcc78ea

    // 0xbcc78f0..0xbcc7947
    LIFT-BODY;  // implement basic block 0xbcc78f0..0xbcc7947

    // 0xbcc7950..0xbcc7989
    LIFT-BODY;  // implement basic block 0xbcc7950..0xbcc7989

    // 0xbcc798e..0xbcc79b2
    LIFT-BODY;  // implement basic block 0xbcc798e..0xbcc79b2

    // 0xbcc79b7..0xbcc79b7
    LIFT-BODY;  // implement basic block 0xbcc79b7..0xbcc79b7

    // 0xbcc79bb..0xbcc79de
    LIFT-BODY;  // implement basic block 0xbcc79bb..0xbcc79de

    // 0xbcc79e0..0xbcc79ec
    LIFT-BODY;  // implement basic block 0xbcc79e0..0xbcc79ec

    // 0xbcc79ee..0xbcc79f7
    LIFT-BODY;  // implement basic block 0xbcc79ee..0xbcc79f7

    // 0xbcc79f9..0xbcc79f9
    LIFT-BODY;  // implement basic block 0xbcc79f9..0xbcc79f9

    // 0xbcc79fc..0xbcc7a32
    LIFT-BODY;  // implement basic block 0xbcc79fc..0xbcc7a32

    // 0xbcc7a34..0xbcc7a3b
    LIFT-BODY;  // implement basic block 0xbcc7a34..0xbcc7a3b

    // 0xbcc7a3d..0xbcc7a3d
    LIFT-BODY;  // implement basic block 0xbcc7a3d..0xbcc7a3d

    // 0xbcc7a40..0xbcc7a40
    LIFT-BODY;  // implement basic block 0xbcc7a40..0xbcc7a40

    // 0xbcc7a42..0xbcc7a5b
    LIFT-BODY;  // implement basic block 0xbcc7a42..0xbcc7a5b

    // 0xbcc7a5c..0xbcc7a66
    0xbcc7a61  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc7a5c..0xbcc7a66

    // 0xbcc7a6b..0xbcc7a74
    0xbcc7a6e  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc7a6b..0xbcc7a74

    // 0xbcc7a79..0xbcc7a85
    0xbcc7a7c  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc7a79..0xbcc7a85

    // 0xbcc7a8a..0xbcc7a96
    0xbcc7a91  call 0xEEC5850                                ; -> sub_eec5850
    LIFT-BODY;  // implement basic block 0xbcc7a8a..0xbcc7a96

    // 0xbcc7a97..0xbcc7aa3
    0xbcc7a9e  call 0xEEC5850                                ; -> sub_eec5850
    LIFT-BODY;  // implement basic block 0xbcc7a97..0xbcc7aa3

    // 0xbcc7aa4..0xbcc7abd
    0xbcc7ab7  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
    LIFT-BODY;  // implement basic block 0xbcc7aa4..0xbcc7abd

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bcc7570: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbcc7570, 0xbcc7abe) (rdis dis output, two spaces after address):
#if 0
0xbcc7612  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc7692  call 0xEEC73F0                                ; -> sub_eec73f0
0xbcc7761  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc77b5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc77fa  call 0xE935700                                ; -> sub_e935700
0xbcc7a61  call 0x9BC830                                 ; -> sub_9bc830
0xbcc7a6e  call 0x9BC830                                 ; -> sub_9bc830
0xbcc7a7c  call 0x9BC830                                 ; -> sub_9bc830
0xbcc7a91  call 0xEEC5850                                ; -> sub_eec5850
0xbcc7a9e  call 0xEEC5850                                ; -> sub_eec5850
0xbcc7ab7  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec73f0 (0xeec73f0, lift set) - call 0xEEC73F0                                ; -> sub_eec73f0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_eec5850 (0xeec5850, lift set) - call 0xEEC5850                                ; -> sub_eec5850
//   sub_eec5850 (0xeec5850, lift set) - call 0xEEC5850                                ; -> sub_eec5850
//   call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bcc7570, "sub_bcc7570", 0xbcc7570, sub_bcc7570, nullptr);

} // namespace native::bgfx