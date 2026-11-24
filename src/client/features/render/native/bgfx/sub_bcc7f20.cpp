// LIFT 0xbcc7f20 size 0x7421 1.26.62.01 MaterialInstance::initFromMaterial (uniform defaults, flags, bgfx shaders/programs)
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcc7f20.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_77d80
extern "C" void sub_77d80(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_53d5c20
extern "C" void sub_53d5c20(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_660e670
extern "C" void sub_660e670(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bcd3f50
extern "C" void sub_bcd3f50(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bcd5a20
extern "C" void sub_bcd5a20(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bcd6770
extern "C" void sub_bcd6770(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bcd6840
extern "C" void sub_bcd6840(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bcd6df0
extern "C" void sub_bcd6df0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e86a1b0
extern "C" void sub_e86a1b0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e935700
extern "C" void sub_e935700(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec6de0
extern "C" void sub_eec6de0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec73f0
extern "C" void sub_eec73f0(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbcc7faa: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc8012: call 0x9D6D0                                  ; -> sub_9d6d0 -> sub_9d6d0
//   0xbcc8070: call 0x1CFDF0                                 ; -> sub_1cfdf0 -> sub_1cfdf0
//   0xbcc811e: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc824b: call 0x9D6D0                                  ; -> sub_9d6d0 -> sub_9d6d0
//   0xbcc8703: call r8 (indirect)
//   0xbcc8784: call r8 (indirect)
//   0xbcc87cf: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc89dd: call 0x9D6D0                                  ; -> sub_9d6d0 -> sub_9d6d0
//   0xbcc8a87: call r8 (indirect)
//   0xbcc8aff: call r8 (indirect)
//   0xbcc8b41: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc90a1: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc921e: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc9272: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc95ef: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc95fd: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc960b: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbcc9886: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc9a2a: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc9a7e: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc9e64: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc9e99: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbcc9eab: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bcc7f20(/* LIFT-BODY: exact args */);

void sub_bcc7f20(/* LIFT-BODY: exact args */) {
    // 0xbcc7f20..0xbcc7ff5
    0xbcc7faa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc7f20..0xbcc7ff5

    // 0xbcc7ff9..0xbcc801f
    0xbcc8012  call 0x9D6D0                                  ; -> sub_9d6d0
    LIFT-BODY;  // implement basic block 0xbcc7ff9..0xbcc801f

    // 0xbcc8021..0xbcc802e
    LIFT-BODY;  // implement basic block 0xbcc8021..0xbcc802e

    // 0xbcc8035..0xbcc8051
    0xbcc804c  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xbcc8035..0xbcc8051

    // 0xbcc8055..0xbcc8076
    0xbcc8070  call 0x1CFDF0                                 ; -> sub_1cfdf0
    LIFT-BODY;  // implement basic block 0xbcc8055..0xbcc8076

    // 0xbcc8078..0xbcc80ba
    LIFT-BODY;  // implement basic block 0xbcc8078..0xbcc80ba

    // 0xbcc80bd..0xbcc80bd
    0xbcc80bd  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc80bd..0xbcc80bd

    // 0xbcc80c2..0xbcc80e6
    LIFT-BODY;  // implement basic block 0xbcc80c2..0xbcc80e6

    // 0xbcc80ed..0xbcc812b
    0xbcc80fe  call 0x660E670                                ; -> sub_660e670
    0xbcc811e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc80ed..0xbcc812b

    // 0xbcc8131..0xbcc817c
    0xbcc8157  call 0xE86A1B0                                ; -> sub_e86a1b0
    0xbcc817c  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc8131..0xbcc817c

    // 0xbcc8181..0xbcc81eb
    LIFT-BODY;  // implement basic block 0xbcc8181..0xbcc81eb

    // 0xbcc81ed..0xbcc81f1
    LIFT-BODY;  // implement basic block 0xbcc81ed..0xbcc81f1

    // 0xbcc8200..0xbcc8209
    LIFT-BODY;  // implement basic block 0xbcc8200..0xbcc8209

    // 0xbcc820f..0xbcc822a
    LIFT-BODY;  // implement basic block 0xbcc820f..0xbcc822a

    // 0xbcc8230..0xbcc8230
    LIFT-BODY;  // implement basic block 0xbcc8230..0xbcc8230

    // 0xbcc8234..0xbcc8253
    0xbcc824b  call 0x9D6D0                                  ; -> sub_9d6d0
    LIFT-BODY;  // implement basic block 0xbcc8234..0xbcc8253

    // 0xbcc8260..0xbcc8266
    LIFT-BODY;  // implement basic block 0xbcc8260..0xbcc8266

    // 0xbcc826a..0xbcc827c
    0xbcc8277  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xbcc826a..0xbcc827c

    // 0xbcc8281..0xbcc83d8
    0xbcc837e  call 0x53D5C20                                ; -> sub_53d5c20
    LIFT-BODY;  // implement basic block 0xbcc8281..0xbcc83d8

    // 0xbcc83dd..0xbcc83f1
    LIFT-BODY;  // implement basic block 0xbcc83dd..0xbcc83f1

    // 0xbcc83f6..0xbcc846f
    LIFT-BODY;  // implement basic block 0xbcc83f6..0xbcc846f

    // 0xbcc8473..0xbcc8488
    LIFT-BODY;  // implement basic block 0xbcc8473..0xbcc8488

    // 0xbcc848d..0xbcc8557
    LIFT-BODY;  // implement basic block 0xbcc848d..0xbcc8557

    // 0xbcc855b..0xbcc8570
    LIFT-BODY;  // implement basic block 0xbcc855b..0xbcc8570

    // 0xbcc8575..0xbcc85b7
    LIFT-BODY;  // implement basic block 0xbcc8575..0xbcc85b7

    // 0xbcc85bb..0xbcc85d0
    LIFT-BODY;  // implement basic block 0xbcc85bb..0xbcc85d0

    // 0xbcc85d5..0xbcc85d9
    LIFT-BODY;  // implement basic block 0xbcc85d5..0xbcc85d9

    // 0xbcc85db..0xbcc85db
    LIFT-BODY;  // implement basic block 0xbcc85db..0xbcc85db

    // 0xbcc85df..0xbcc85f0
    LIFT-BODY;  // implement basic block 0xbcc85df..0xbcc85f0

    // 0xbcc85f5..0xbcc85f9
    LIFT-BODY;  // implement basic block 0xbcc85f5..0xbcc85f9

    // 0xbcc85fe..0xbcc8651
    LIFT-BODY;  // implement basic block 0xbcc85fe..0xbcc8651

    // 0xbcc8655..0xbcc8655
    LIFT-BODY;  // implement basic block 0xbcc8655..0xbcc8655

    // 0xbcc865a..0xbcc866b
    LIFT-BODY;  // implement basic block 0xbcc865a..0xbcc866b

    // 0xbcc8670..0xbcc868c
    LIFT-BODY;  // implement basic block 0xbcc8670..0xbcc868c

    // 0xbcc8690..0xbcc8690
    LIFT-BODY;  // implement basic block 0xbcc8690..0xbcc8690

    // 0xbcc8695..0xbcc86a6
    LIFT-BODY;  // implement basic block 0xbcc8695..0xbcc86a6

    // 0xbcc86ab..0xbcc870d
    0xbcc8703  call r8
    LIFT-BODY;  // implement basic block 0xbcc86ab..0xbcc870d

    // 0xbcc8713..0xbcc8742
    0xbcc8725  call 0xBCD5A20                                ; -> sub_bcd5a20
    LIFT-BODY;  // implement basic block 0xbcc8713..0xbcc8742

    // 0xbcc8750..0xbcc878e
    0xbcc8784  call r8
    LIFT-BODY;  // implement basic block 0xbcc8750..0xbcc878e

    // 0xbcc8790..0xbcc87bd
    0xbcc87a2  call 0xBCD5A20                                ; -> sub_bcd5a20
    LIFT-BODY;  // implement basic block 0xbcc8790..0xbcc87bd

    // 0xbcc87bf..0xbcc87d5
    0xbcc87cf  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc87bf..0xbcc87d5

    // 0xbcc87d7..0xbcc87fd
    LIFT-BODY;  // implement basic block 0xbcc87d7..0xbcc87fd

    // 0xbcc8804..0xbcc880b
    LIFT-BODY;  // implement basic block 0xbcc8804..0xbcc880b

    // 0xbcc8810..0xbcc881e
    LIFT-BODY;  // implement basic block 0xbcc8810..0xbcc881e

    // 0xbcc8820..0xbcc8827
    LIFT-BODY;  // implement basic block 0xbcc8820..0xbcc8827

    // 0xbcc882a..0xbcc882a
    0xbcc882a  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc882a..0xbcc882a

    // 0xbcc882f..0xbcc8859
    0xbcc884b  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc882f..0xbcc8859

    // 0xbcc885b..0xbcc888a
    LIFT-BODY;  // implement basic block 0xbcc885b..0xbcc888a

    // 0xbcc888f..0xbcc889d
    LIFT-BODY;  // implement basic block 0xbcc888f..0xbcc889d

    // 0xbcc88a4..0xbcc88b8
    LIFT-BODY;  // implement basic block 0xbcc88a4..0xbcc88b8

    // 0xbcc88ba..0xbcc88ce
    LIFT-BODY;  // implement basic block 0xbcc88ba..0xbcc88ce

    // 0xbcc88d2..0xbcc8931
    0xbcc88e1  call 0xEEC73F0                                ; -> sub_eec73f0
    LIFT-BODY;  // implement basic block 0xbcc88d2..0xbcc8931

    // 0xbcc8934..0xbcc8943
    0xbcc893e  call 0x77D80                                  ; -> sub_77d80
    LIFT-BODY;  // implement basic block 0xbcc8934..0xbcc8943

    // 0xbcc8944..0xbcc899a
    LIFT-BODY;  // implement basic block 0xbcc8944..0xbcc899a

    // 0xbcc89a0..0xbcc89bd
    LIFT-BODY;  // implement basic block 0xbcc89a0..0xbcc89bd

    // 0xbcc89c0..0xbcc89c0
    LIFT-BODY;  // implement basic block 0xbcc89c0..0xbcc89c0

    // 0xbcc89c5..0xbcc89e5
    0xbcc89dd  call 0x9D6D0                                  ; -> sub_9d6d0
    LIFT-BODY;  // implement basic block 0xbcc89c5..0xbcc89e5

    // 0xbcc89f0..0xbcc89f6
    LIFT-BODY;  // implement basic block 0xbcc89f0..0xbcc89f6

    // 0xbcc89fa..0xbcc8a0c
    0xbcc8a07  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xbcc89fa..0xbcc8a0c

    // 0xbcc8a11..0xbcc8a2a
    0xbcc8a1a  call 0xBCD6DF0                                ; -> sub_bcd6df0
    LIFT-BODY;  // implement basic block 0xbcc8a11..0xbcc8a2a

    // 0xbcc8a30..0xbcc8a91
    0xbcc8a87  call r8
    LIFT-BODY;  // implement basic block 0xbcc8a30..0xbcc8a91

    // 0xbcc8a97..0xbcc8abd
    0xbcc8aaa  call 0xBCD6840                                ; -> sub_bcd6840
    LIFT-BODY;  // implement basic block 0xbcc8a97..0xbcc8abd

    // 0xbcc8ac0..0xbcc8b09
    0xbcc8aff  call r8
    LIFT-BODY;  // implement basic block 0xbcc8ac0..0xbcc8b09

    // 0xbcc8b0b..0xbcc8b2f
    0xbcc8b1e  call 0xBCD6840                                ; -> sub_bcd6840
    LIFT-BODY;  // implement basic block 0xbcc8b0b..0xbcc8b2f

    // 0xbcc8b31..0xbcc8b47
    0xbcc8b41  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc8b31..0xbcc8b47

    // 0xbcc8b49..0xbcc8b76
    LIFT-BODY;  // implement basic block 0xbcc8b49..0xbcc8b76

    // 0xbcc8b81..0xbcc8b8d
    0xbcc8b88  call 0xBCD6770                                ; -> sub_bcd6770
    LIFT-BODY;  // implement basic block 0xbcc8b81..0xbcc8b8d

    // 0xbcc8b92..0xbcc8baa
    LIFT-BODY;  // implement basic block 0xbcc8b92..0xbcc8baa

    // 0xbcc8bb0..0xbcc8bb0
    0xbcc8bb0  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc8bb0..0xbcc8bb0

    // 0xbcc8bb5..0xbcc8bdf
    0xbcc8bd1  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc8bb5..0xbcc8bdf

    // 0xbcc8be1..0xbcc8c27
    0xbcc8be8  call 0xBCD3F50                                ; -> sub_bcd3f50
    LIFT-BODY;  // implement basic block 0xbcc8be1..0xbcc8c27

    // 0xbcc8c29..0xbcc8c30
    LIFT-BODY;  // implement basic block 0xbcc8c29..0xbcc8c30

    // 0xbcc8c37..0xbcc8c59
    LIFT-BODY;  // implement basic block 0xbcc8c37..0xbcc8c59

    // 0xbcc8c5b..0xbcc8c6f
    LIFT-BODY;  // implement basic block 0xbcc8c5b..0xbcc8c6f

    // 0xbcc8c73..0xbcc8cd2
    0xbcc8c82  call 0xEEC73F0                                ; -> sub_eec73f0
    LIFT-BODY;  // implement basic block 0xbcc8c73..0xbcc8cd2

    // 0xbcc8cd5..0xbcc8ce1
    0xbcc8cdb  call 0x77D80                                  ; -> sub_77d80
    LIFT-BODY;  // implement basic block 0xbcc8cd5..0xbcc8ce1

    // 0xbcc8ce8..0xbcc8d17
    LIFT-BODY;  // implement basic block 0xbcc8ce8..0xbcc8d17

    // 0xbcc8d20..0xbcc8d33
    0xbcc8d28  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc8d20..0xbcc8d33

    // 0xbcc8d35..0xbcc8d89
    LIFT-BODY;  // implement basic block 0xbcc8d35..0xbcc8d89

    // 0xbcc8d8b..0xbcc8daa
    LIFT-BODY;  // implement basic block 0xbcc8d8b..0xbcc8daa

    // 0xbcc8db0..0xbcc8dcb
    LIFT-BODY;  // implement basic block 0xbcc8db0..0xbcc8dcb

    // 0xbcc8dd0..0xbcc8dda
    LIFT-BODY;  // implement basic block 0xbcc8dd0..0xbcc8dda

    // 0xbcc8ddc..0xbcc8e27
    LIFT-BODY;  // implement basic block 0xbcc8ddc..0xbcc8e27

    // 0xbcc8e30..0xbcc8e30
    LIFT-BODY;  // implement basic block 0xbcc8e30..0xbcc8e30

    // 0xbcc8e33..0xbcc8e39
    LIFT-BODY;  // implement basic block 0xbcc8e33..0xbcc8e39

    // 0xbcc8e3f..0xbcc8e4c
    LIFT-BODY;  // implement basic block 0xbcc8e3f..0xbcc8e4c

    // 0xbcc8e50..0xbcc8e50
    LIFT-BODY;  // implement basic block 0xbcc8e50..0xbcc8e50

    // 0xbcc8e54..0xbcc8e81
    LIFT-BODY;  // implement basic block 0xbcc8e54..0xbcc8e81

    // 0xbcc8e90..0xbcc8ea4
    LIFT-BODY;  // implement basic block 0xbcc8e90..0xbcc8ea4

    // 0xbcc8eb0..0xbcc8eef
    LIFT-BODY;  // implement basic block 0xbcc8eb0..0xbcc8eef

    // 0xbcc8ef1..0xbcc8ef9
    LIFT-BODY;  // implement basic block 0xbcc8ef1..0xbcc8ef9

    // 0xbcc8f00..0xbcc8f14
    LIFT-BODY;  // implement basic block 0xbcc8f00..0xbcc8f14

    // 0xbcc8f16..0xbcc8f23
    LIFT-BODY;  // implement basic block 0xbcc8f16..0xbcc8f23

    // 0xbcc8f30..0xbcc8f30
    LIFT-BODY;  // implement basic block 0xbcc8f30..0xbcc8f30

    // 0xbcc8f34..0xbcc8f61
    LIFT-BODY;  // implement basic block 0xbcc8f34..0xbcc8f61

    // 0xbcc8f70..0xbcc8f84
    LIFT-BODY;  // implement basic block 0xbcc8f70..0xbcc8f84

    // 0xbcc8f90..0xbcc8fcf
    LIFT-BODY;  // implement basic block 0xbcc8f90..0xbcc8fcf

    // 0xbcc8fd1..0xbcc8fd9
    LIFT-BODY;  // implement basic block 0xbcc8fd1..0xbcc8fd9

    // 0xbcc8fe0..0xbcc8ff5
    LIFT-BODY;  // implement basic block 0xbcc8fe0..0xbcc8ff5

    // 0xbcc8ff7..0xbcc900d
    LIFT-BODY;  // implement basic block 0xbcc8ff7..0xbcc900d

    // 0xbcc9013..0xbcc904a
    LIFT-BODY;  // implement basic block 0xbcc9013..0xbcc904a

    // 0xbcc9050..0xbcc9064
    LIFT-BODY;  // implement basic block 0xbcc9050..0xbcc9064

    // 0xbcc9070..0xbcc90ae
    0xbcc90a1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc9070..0xbcc90ae

    // 0xbcc90b4..0xbcc90db
    LIFT-BODY;  // implement basic block 0xbcc90b4..0xbcc90db

    // 0xbcc90dd..0xbcc90ee
    LIFT-BODY;  // implement basic block 0xbcc90dd..0xbcc90ee

    // 0xbcc90f2..0xbcc9112
    LIFT-BODY;  // implement basic block 0xbcc90f2..0xbcc9112

    // 0xbcc9114..0xbcc9128
    LIFT-BODY;  // implement basic block 0xbcc9114..0xbcc9128

    // 0xbcc912c..0xbcc918c
    0xbcc9140  call 0xEEC73F0                                ; -> sub_eec73f0
    LIFT-BODY;  // implement basic block 0xbcc912c..0xbcc918c

    // 0xbcc918f..0xbcc922b
    0xbcc921e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc918f..0xbcc922b

    // 0xbcc9231..0xbcc9240
    LIFT-BODY;  // implement basic block 0xbcc9231..0xbcc9240

    // 0xbcc9242..0xbcc925c
    LIFT-BODY;  // implement basic block 0xbcc9242..0xbcc925c

    // 0xbcc9261..0xbcc927f
    0xbcc9272  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc9261..0xbcc927f

    // 0xbcc9285..0xbcc92c1
    LIFT-BODY;  // implement basic block 0xbcc9285..0xbcc92c1

    // 0xbcc92c4..0xbcc92c4
    0xbcc92c4  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc92c4..0xbcc92c4

    // 0xbcc92c9..0xbcc92fd
    LIFT-BODY;  // implement basic block 0xbcc92c9..0xbcc92fd

    // 0xbcc92ff..0xbcc931e
    LIFT-BODY;  // implement basic block 0xbcc92ff..0xbcc931e

    // 0xbcc9320..0xbcc9342
    LIFT-BODY;  // implement basic block 0xbcc9320..0xbcc9342

    // 0xbcc9350..0xbcc935c
    LIFT-BODY;  // implement basic block 0xbcc9350..0xbcc935c

    // 0xbcc935e..0xbcc937d
    LIFT-BODY;  // implement basic block 0xbcc935e..0xbcc937d

    // 0xbcc9380..0xbcc939b
    LIFT-BODY;  // implement basic block 0xbcc9380..0xbcc939b

    // 0xbcc93a0..0xbcc93aa
    LIFT-BODY;  // implement basic block 0xbcc93a0..0xbcc93aa

    // 0xbcc93ac..0xbcc93d9
    LIFT-BODY;  // implement basic block 0xbcc93ac..0xbcc93d9

    // 0xbcc93e0..0xbcc93e0
    LIFT-BODY;  // implement basic block 0xbcc93e0..0xbcc93e0

    // 0xbcc93e4..0xbcc93e4
    LIFT-BODY;  // implement basic block 0xbcc93e4..0xbcc93e4

    // 0xbcc93e9..0xbcc93ec
    LIFT-BODY;  // implement basic block 0xbcc93e9..0xbcc93ec

    // 0xbcc93f2..0xbcc9457
    LIFT-BODY;  // implement basic block 0xbcc93f2..0xbcc9457

    // 0xbcc9460..0xbcc9493
    LIFT-BODY;  // implement basic block 0xbcc9460..0xbcc9493

    // 0xbcc9498..0xbcc94bd
    LIFT-BODY;  // implement basic block 0xbcc9498..0xbcc94bd

    // 0xbcc94c2..0xbcc94c9
    LIFT-BODY;  // implement basic block 0xbcc94c2..0xbcc94c9

    // 0xbcc94cc..0xbcc94e7
    LIFT-BODY;  // implement basic block 0xbcc94cc..0xbcc94e7

    // 0xbcc94e9..0xbcc9524
    LIFT-BODY;  // implement basic block 0xbcc94e9..0xbcc9524

    // 0xbcc9530..0xbcc9541
    LIFT-BODY;  // implement basic block 0xbcc9530..0xbcc9541

    // 0xbcc9543..0xbcc9543
    LIFT-BODY;  // implement basic block 0xbcc9543..0xbcc9543

    // 0xbcc9546..0xbcc95b2
    LIFT-BODY;  // implement basic block 0xbcc9546..0xbcc95b2

    // 0xbcc95b7..0xbcc95cd
    LIFT-BODY;  // implement basic block 0xbcc95b7..0xbcc95cd

    // 0xbcc95d2..0xbcc95dd
    LIFT-BODY;  // implement basic block 0xbcc95d2..0xbcc95dd

    // 0xbcc95e2..0xbcc95e5
    LIFT-BODY;  // implement basic block 0xbcc95e2..0xbcc95e5

    // 0xbcc95ea..0xbcc95f5
    0xbcc95ef  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc95ea..0xbcc95f5

    // 0xbcc95fa..0xbcc9603
    0xbcc95fd  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc95fa..0xbcc9603

    // 0xbcc9608..0xbcc9613
    0xbcc960b  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc9608..0xbcc9613

    // 0xbcc9618..0xbcc9653
    LIFT-BODY;  // implement basic block 0xbcc9618..0xbcc9653

    // 0xbcc9660..0xbcc9664
    LIFT-BODY;  // implement basic block 0xbcc9660..0xbcc9664

    // 0xbcc9667..0xbcc9673
    0xbcc966b  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc9667..0xbcc9673

    // 0xbcc967b..0xbcc968e
    0xbcc9683  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc967b..0xbcc968e

    // 0xbcc9690..0xbcc96bd
    LIFT-BODY;  // implement basic block 0xbcc9690..0xbcc96bd

    // 0xbcc96c2..0xbcc9716
    LIFT-BODY;  // implement basic block 0xbcc96c2..0xbcc9716

    // 0xbcc9718..0xbcc9737
    LIFT-BODY;  // implement basic block 0xbcc9718..0xbcc9737

    // 0xbcc9740..0xbcc975b
    LIFT-BODY;  // implement basic block 0xbcc9740..0xbcc975b

    // 0xbcc9760..0xbcc976a
    LIFT-BODY;  // implement basic block 0xbcc9760..0xbcc976a

    // 0xbcc976c..0xbcc979b
    LIFT-BODY;  // implement basic block 0xbcc976c..0xbcc979b

    // 0xbcc97a0..0xbcc97a7
    LIFT-BODY;  // implement basic block 0xbcc97a0..0xbcc97a7

    // 0xbcc97ac..0xbcc9826
    LIFT-BODY;  // implement basic block 0xbcc97ac..0xbcc9826

    // 0xbcc9830..0xbcc983f
    LIFT-BODY;  // implement basic block 0xbcc9830..0xbcc983f

    // 0xbcc9844..0xbcc9844
    LIFT-BODY;  // implement basic block 0xbcc9844..0xbcc9844

    // 0xbcc9847..0xbcc9893
    0xbcc9886  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc9847..0xbcc9893

    // 0xbcc9899..0xbcc98df
    LIFT-BODY;  // implement basic block 0xbcc9899..0xbcc98df

    // 0xbcc98e0..0xbcc98f1
    LIFT-BODY;  // implement basic block 0xbcc98e0..0xbcc98f1

    // 0xbcc98f5..0xbcc9917
    LIFT-BODY;  // implement basic block 0xbcc98f5..0xbcc9917

    // 0xbcc9920..0xbcc9934
    LIFT-BODY;  // implement basic block 0xbcc9920..0xbcc9934

    // 0xbcc9938..0xbcc9998
    0xbcc994c  call 0xEEC73F0                                ; -> sub_eec73f0
    LIFT-BODY;  // implement basic block 0xbcc9938..0xbcc9998

    // 0xbcc999b..0xbcc9a37
    0xbcc9a2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc999b..0xbcc9a37

    // 0xbcc9a3d..0xbcc9a4c
    LIFT-BODY;  // implement basic block 0xbcc9a3d..0xbcc9a4c

    // 0xbcc9a4e..0xbcc9a68
    LIFT-BODY;  // implement basic block 0xbcc9a4e..0xbcc9a68

    // 0xbcc9a6d..0xbcc9a8b
    0xbcc9a7e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc9a6d..0xbcc9a8b

    // 0xbcc9a91..0xbcc9acd
    LIFT-BODY;  // implement basic block 0xbcc9a91..0xbcc9acd

    // 0xbcc9ad0..0xbcc9ad0
    0xbcc9ad0  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc9ad0..0xbcc9ad0

    // 0xbcc9ad5..0xbcc9b02
    LIFT-BODY;  // implement basic block 0xbcc9ad5..0xbcc9b02

    // 0xbcc9b04..0xbcc9b23
    LIFT-BODY;  // implement basic block 0xbcc9b04..0xbcc9b23

    // 0xbcc9b30..0xbcc9b4b
    LIFT-BODY;  // implement basic block 0xbcc9b30..0xbcc9b4b

    // 0xbcc9b50..0xbcc9b5c
    LIFT-BODY;  // implement basic block 0xbcc9b50..0xbcc9b5c

    // 0xbcc9b5e..0xbcc9b7d
    LIFT-BODY;  // implement basic block 0xbcc9b5e..0xbcc9b7d

    // 0xbcc9b80..0xbcc9b9b
    LIFT-BODY;  // implement basic block 0xbcc9b80..0xbcc9b9b

    // 0xbcc9ba0..0xbcc9baa
    LIFT-BODY;  // implement basic block 0xbcc9ba0..0xbcc9baa

    // 0xbcc9bac..0xbcc9bdb
    LIFT-BODY;  // implement basic block 0xbcc9bac..0xbcc9bdb

    // 0xbcc9be0..0xbcc9be0
    LIFT-BODY;  // implement basic block 0xbcc9be0..0xbcc9be0

    // 0xbcc9be4..0xbcc9be4
    LIFT-BODY;  // implement basic block 0xbcc9be4..0xbcc9be4

    // 0xbcc9be9..0xbcc9bec
    LIFT-BODY;  // implement basic block 0xbcc9be9..0xbcc9bec

    // 0xbcc9bf2..0xbcc9c57
    LIFT-BODY;  // implement basic block 0xbcc9bf2..0xbcc9c57

    // 0xbcc9c60..0xbcc9c93
    LIFT-BODY;  // implement basic block 0xbcc9c60..0xbcc9c93

    // 0xbcc9c98..0xbcc9cbd
    LIFT-BODY;  // implement basic block 0xbcc9c98..0xbcc9cbd

    // 0xbcc9cc2..0xbcc9cd0
    LIFT-BODY;  // implement basic block 0xbcc9cc2..0xbcc9cd0

    // 0xbcc9cd7..0xbcc9cfd
    LIFT-BODY;  // implement basic block 0xbcc9cd7..0xbcc9cfd

    // 0xbcc9d00..0xbcc9d0d
    LIFT-BODY;  // implement basic block 0xbcc9d00..0xbcc9d0d

    // 0xbcc9d0f..0xbcc9d12
    LIFT-BODY;  // implement basic block 0xbcc9d0f..0xbcc9d12

    // 0xbcc9d14..0xbcc9d17
    LIFT-BODY;  // implement basic block 0xbcc9d14..0xbcc9d17

    // 0xbcc9d20..0xbcc9d76
    LIFT-BODY;  // implement basic block 0xbcc9d20..0xbcc9d76

    // 0xbcc9d78..0xbcc9d78
    LIFT-BODY;  // implement basic block 0xbcc9d78..0xbcc9d78

    // 0xbcc9d7c..0xbcc9d81
    LIFT-BODY;  // implement basic block 0xbcc9d7c..0xbcc9d81

    // 0xbcc9d83..0xbcc9d83
    LIFT-BODY;  // implement basic block 0xbcc9d83..0xbcc9d83

    // 0xbcc9d87..0xbcc9dbf
    LIFT-BODY;  // implement basic block 0xbcc9d87..0xbcc9dbf

    // 0xbcc9dc2..0xbcc9dc2
    0xbcc9dc2  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbcc9dc2..0xbcc9dc2

    // 0xbcc9dc7..0xbcc9e71
    0xbcc9e64  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbcc9dc7..0xbcc9e71

    // 0xbcc9e77..0xbcc9e86
    LIFT-BODY;  // implement basic block 0xbcc9e77..0xbcc9e86

    // 0xbcc9e88..0xbcc9eb0
    0xbcc9e99  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbcc9eab  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbcc9e88..0xbcc9eb0

    // 0xbcc9eb1..0xbcc9eb1
    LIFT-BODY;  // implement basic block 0xbcc9eb1..0xbcc9eb1

    // 0xbcc9eb4..0xbcc9eef
    0xbcc9edd  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xbcc9eb4..0xbcc9eef

    // 0xbcc9ef1..0xbcc9efb
    LIFT-BODY;  // implement basic block 0xbcc9ef1..0xbcc9efb

    // 0xbcc9efe..0xbcc9f1c
    0xbcc9efe  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xbcc9efe..0xbcc9f1c

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bcc7f20: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbcc7f20, 0xbccf341) (rdis dis output, two spaces after address):
#if 0
0xbcc7faa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc8012  call 0x9D6D0                                  ; -> sub_9d6d0
0xbcc804c  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbcc8070  call 0x1CFDF0                                 ; -> sub_1cfdf0
0xbcc80bd  call 0xE935700                                ; -> sub_e935700
0xbcc80fe  call 0x660E670                                ; -> sub_660e670
0xbcc811e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc8157  call 0xE86A1B0                                ; -> sub_e86a1b0
0xbcc817c  call 0xE935700                                ; -> sub_e935700
0xbcc824b  call 0x9D6D0                                  ; -> sub_9d6d0
0xbcc8277  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbcc837e  call 0x53D5C20                                ; -> sub_53d5c20
0xbcc8703  call r8
0xbcc8725  call 0xBCD5A20                                ; -> sub_bcd5a20
0xbcc8784  call r8
0xbcc87a2  call 0xBCD5A20                                ; -> sub_bcd5a20
0xbcc87cf  call 0x9BC830                                 ; -> sub_9bc830
0xbcc882a  call 0xE935700                                ; -> sub_e935700
0xbcc884b  call 0xE935700                                ; -> sub_e935700
0xbcc88e1  call 0xEEC73F0                                ; -> sub_eec73f0
0xbcc893e  call 0x77D80                                  ; -> sub_77d80
0xbcc89dd  call 0x9D6D0                                  ; -> sub_9d6d0
0xbcc8a07  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbcc8a1a  call 0xBCD6DF0                                ; -> sub_bcd6df0
0xbcc8a87  call r8
0xbcc8aaa  call 0xBCD6840                                ; -> sub_bcd6840
0xbcc8aff  call r8
0xbcc8b1e  call 0xBCD6840                                ; -> sub_bcd6840
0xbcc8b41  call 0x9BC830                                 ; -> sub_9bc830
0xbcc8b88  call 0xBCD6770                                ; -> sub_bcd6770
0xbcc8bb0  call 0xE935700                                ; -> sub_e935700
0xbcc8bd1  call 0xE935700                                ; -> sub_e935700
0xbcc8be8  call 0xBCD3F50                                ; -> sub_bcd3f50
0xbcc8c82  call 0xEEC73F0                                ; -> sub_eec73f0
0xbcc8cdb  call 0x77D80                                  ; -> sub_77d80
0xbcc8d28  call 0xE935700                                ; -> sub_e935700
0xbcc90a1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc9140  call 0xEEC73F0                                ; -> sub_eec73f0
0xbcc921e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc9272  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc92c4  call 0xE935700                                ; -> sub_e935700
0xbcc95ef  call 0x9BC830                                 ; -> sub_9bc830
0xbcc95fd  call 0x9BC830                                 ; -> sub_9bc830
0xbcc960b  call 0x9BC830                                 ; -> sub_9bc830
0xbcc966b  call 0xE935700                                ; -> sub_e935700
0xbcc9683  call 0xE935700                                ; -> sub_e935700
0xbcc9886  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc994c  call 0xEEC73F0                                ; -> sub_eec73f0
0xbcc9a2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc9a7e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc9ad0  call 0xE935700                                ; -> sub_e935700
0xbcc9dc2  call 0xE935700                                ; -> sub_e935700
0xbcc9e64  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc9e99  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcc9eab  call 0x9BC830                                 ; -> sub_9bc830
0xbcc9edd  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbcc9efe  call 0xEEC6DE0                                ; -> sub_eec6de0
#endif

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_9d6d0 (0x9d6d0, boundary) - call 0x9D6D0                                  ; -> sub_9d6d0
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   sub_1cfdf0 (0x1cfdf0, boundary) - call 0x1CFDF0                                 ; -> sub_1cfdf0
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_660e670 (0x660e670, lift set) - call 0x660E670                                ; -> sub_660e670
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e86a1b0 (0xe86a1b0, lift set) - call 0xE86A1B0                                ; -> sub_e86a1b0
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_9d6d0 (0x9d6d0, boundary) - call 0x9D6D0                                  ; -> sub_9d6d0
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   sub_53d5c20 (0x53d5c20, lift set) - call 0x53D5C20                                ; -> sub_53d5c20
//   call r8 (indirect, boundary via data slot)
//   sub_bcd5a20 (0xbcd5a20, lift set) - call 0xBCD5A20                                ; -> sub_bcd5a20
//   call r8 (indirect, boundary via data slot)
//   sub_bcd5a20 (0xbcd5a20, lift set) - call 0xBCD5A20                                ; -> sub_bcd5a20
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_eec73f0 (0xeec73f0, lift set) - call 0xEEC73F0                                ; -> sub_eec73f0
//   sub_77d80 (0x77d80, lift set) - call 0x77D80                                  ; -> sub_77d80
//   sub_9d6d0 (0x9d6d0, boundary) - call 0x9D6D0                                  ; -> sub_9d6d0
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   sub_bcd6df0 (0xbcd6df0, lift set) - call 0xBCD6DF0                                ; -> sub_bcd6df0
//   call r8 (indirect, boundary via data slot)
//   sub_bcd6840 (0xbcd6840, lift set) - call 0xBCD6840                                ; -> sub_bcd6840
//   call r8 (indirect, boundary via data slot)
//   sub_bcd6840 (0xbcd6840, lift set) - call 0xBCD6840                                ; -> sub_bcd6840
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_bcd6770 (0xbcd6770, lift set) - call 0xBCD6770                                ; -> sub_bcd6770
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_bcd3f50 (0xbcd3f50, lift set) - call 0xBCD3F50                                ; -> sub_bcd3f50
//   sub_eec73f0 (0xeec73f0, lift set) - call 0xEEC73F0                                ; -> sub_eec73f0
//   sub_77d80 (0x77d80, lift set) - call 0x77D80                                  ; -> sub_77d80
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec73f0 (0xeec73f0, lift set) - call 0xEEC73F0                                ; -> sub_eec73f0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec73f0 (0xeec73f0, lift set) - call 0xEEC73F0                                ; -> sub_eec73f0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bcc7f20, "sub_bcc7f20", 0xbcc7f20, sub_bcc7f20, nullptr);

} // namespace native::bgfx