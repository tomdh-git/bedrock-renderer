// LIFT 0xbc9d7a0 size 0x67db 1.26.62.01 
// CHUNK 0xbc9e11a..0xbc9f890
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc9d7a0.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_130ee0
extern "C" void sub_130ee0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_567c8b0
extern "C" void sub_567c8b0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_568ad40
extern "C" void sub_568ad40(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_56939c0
extern "C" void sub_56939c0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_5693a80
extern "C" void sub_5693a80(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_56ba620
extern "C" void sub_56ba620(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_56bd700
extern "C" void sub_56bd700(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bc09250
extern "C" void sub_bc09250(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bc431b0
extern "C" void sub_bc431b0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bca8190
extern "C" void sub_bca8190(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e935700
extern "C" void sub_e935700(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec6de0
extern "C" void sub_eec6de0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec6ec0
extern "C" void sub_eec6ec0(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbc9d7b1: call 0xE9E7970                                ; -> sub_e9e7970 -> sub_e9e7970
//   0xbc9e0ce: call 0x9D6D0                                  ; -> sub_9d6d0 -> sub_9d6d0
//   0xbc9e14d: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e163: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e1a5: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e1bb: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e2e5: call r8 (indirect)
//   0xbc9e3d3: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e4ee: call 0x76A8A0                                 ; -> sub_76a8a0 -> sub_76a8a0
//   0xbc9e71f: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e7cd: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e7f3: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e8ac: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9e8d7: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9ea01: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9ea36: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9ea48: call 0x9BC830                                 ; -> sub_9bc830 -> sub_9bc830
//   0xbc9ebec: call 0x9D6D0                                  ; -> sub_9d6d0 -> sub_9d6d0
//   0xbc9ed34: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9ed60: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9ed76: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9ee68: call rsi (indirect)
//   0xbc9ee72: call rsi (indirect)
//   0xbc9eee6: call r8 (indirect)
//   0xbc9f045: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9f175: call 0x76A8A0                                 ; -> sub_76a8a0 -> sub_76a8a0
//   0xbc9f479: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9f52f: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9f555: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9f626: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9f64e: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc9f77b: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_bc9d7a0(/* LIFT-BODY: exact args */);

void sub_bc9d7a0(/* LIFT-BODY: exact args */) {
    // 0xbc9d7a0..0xbc9d83a
    0xbc9d7b1  call 0xE9E7970                                ; -> sub_e9e7970
    LIFT-BODY;  // implement basic block 0xbc9d7a0..0xbc9d83a

    // 0xbc9d840..0xbc9d85f
    LIFT-BODY;  // implement basic block 0xbc9d840..0xbc9d85f

    // 0xbc9d865..0xbc9d884
    LIFT-BODY;  // implement basic block 0xbc9d865..0xbc9d884

    // 0xbc9d88a..0xbc9d8a9
    LIFT-BODY;  // implement basic block 0xbc9d88a..0xbc9d8a9

    // 0xbc9d8af..0xbc9d8ce
    LIFT-BODY;  // implement basic block 0xbc9d8af..0xbc9d8ce

    // 0xbc9d8d4..0xbc9d8f3
    LIFT-BODY;  // implement basic block 0xbc9d8d4..0xbc9d8f3

    // 0xbc9d8f9..0xbc9d918
    LIFT-BODY;  // implement basic block 0xbc9d8f9..0xbc9d918

    // 0xbc9d91e..0xbc9d93d
    LIFT-BODY;  // implement basic block 0xbc9d91e..0xbc9d93d

    // 0xbc9d943..0xbc9d962
    LIFT-BODY;  // implement basic block 0xbc9d943..0xbc9d962

    // 0xbc9d968..0xbc9d987
    LIFT-BODY;  // implement basic block 0xbc9d968..0xbc9d987

    // 0xbc9d98d..0xbc9d9ac
    LIFT-BODY;  // implement basic block 0xbc9d98d..0xbc9d9ac

    // 0xbc9d9b2..0xbc9d9d1
    LIFT-BODY;  // implement basic block 0xbc9d9b2..0xbc9d9d1

    // 0xbc9d9d7..0xbc9d9f6
    LIFT-BODY;  // implement basic block 0xbc9d9d7..0xbc9d9f6

    // 0xbc9d9fc..0xbc9da1b
    LIFT-BODY;  // implement basic block 0xbc9d9fc..0xbc9da1b

    // 0xbc9da21..0xbc9da40
    LIFT-BODY;  // implement basic block 0xbc9da21..0xbc9da40

    // 0xbc9da46..0xbc9da65
    LIFT-BODY;  // implement basic block 0xbc9da46..0xbc9da65

    // 0xbc9da6b..0xbc9da8a
    LIFT-BODY;  // implement basic block 0xbc9da6b..0xbc9da8a

    // 0xbc9da90..0xbc9daaf
    LIFT-BODY;  // implement basic block 0xbc9da90..0xbc9daaf

    // 0xbc9dab5..0xbc9dad4
    LIFT-BODY;  // implement basic block 0xbc9dab5..0xbc9dad4

    // 0xbc9dada..0xbc9daf9
    LIFT-BODY;  // implement basic block 0xbc9dada..0xbc9daf9

    // 0xbc9daff..0xbc9db1e
    LIFT-BODY;  // implement basic block 0xbc9daff..0xbc9db1e

    // 0xbc9db24..0xbc9db43
    LIFT-BODY;  // implement basic block 0xbc9db24..0xbc9db43

    // 0xbc9db49..0xbc9db68
    LIFT-BODY;  // implement basic block 0xbc9db49..0xbc9db68

    // 0xbc9db6e..0xbc9dc1a
    LIFT-BODY;  // implement basic block 0xbc9db6e..0xbc9dc1a

    // 0xbc9dc1c..0xbc9dc37
    LIFT-BODY;  // implement basic block 0xbc9dc1c..0xbc9dc37

    // 0xbc9dc3b..0xbc9dc74
    LIFT-BODY;  // implement basic block 0xbc9dc3b..0xbc9dc74

    // 0xbc9dc7a..0xbc9dc84
    LIFT-BODY;  // implement basic block 0xbc9dc7a..0xbc9dc84

    // 0xbc9dc86..0xbc9dc86
    LIFT-BODY;  // implement basic block 0xbc9dc86..0xbc9dc86

    // 0xbc9dc8d..0xbc9dcb3
    LIFT-BODY;  // implement basic block 0xbc9dc8d..0xbc9dcb3

    // 0xbc9dcb9..0xbc9dd65
    LIFT-BODY;  // implement basic block 0xbc9dcb9..0xbc9dd65

    // 0xbc9dd67..0xbc9dd82
    LIFT-BODY;  // implement basic block 0xbc9dd67..0xbc9dd82

    // 0xbc9dd86..0xbc9dd9e
    LIFT-BODY;  // implement basic block 0xbc9dd86..0xbc9dd9e

    // 0xbc9dda0..0xbc9ddb1
    LIFT-BODY;  // implement basic block 0xbc9dda0..0xbc9ddb1

    // 0xbc9ddb6..0xbc9ddc7
    LIFT-BODY;  // implement basic block 0xbc9ddb6..0xbc9ddc7

    // 0xbc9ddc9..0xbc9ddd3
    LIFT-BODY;  // implement basic block 0xbc9ddc9..0xbc9ddd3

    // 0xbc9ddda..0xbc9de79
    0xbc9de49  call 0x567C8B0                                ; -> sub_567c8b0
    LIFT-BODY;  // implement basic block 0xbc9ddda..0xbc9de79

    // 0xbc9de7f..0xbc9e019
    0xbc9debf  call 0x567C8B0                                ; -> sub_567c8b0
    0xbc9dfd5  call 0xBC09250                                ; -> sub_bc09250
    LIFT-BODY;  // implement basic block 0xbc9de7f..0xbc9e019

    // 0xbc9e01f..0xbc9e03e
    LIFT-BODY;  // implement basic block 0xbc9e01f..0xbc9e03e

    // 0xbc9e044..0xbc9e169
    0xbc9e0ce  call 0x9D6D0                                  ; -> sub_9d6d0
    0xbc9e0ec  call 0xBC431B0                                ; -> sub_bc431b0
    0xbc9e107  call 0x56BD700                                ; -> sub_56bd700
    0xbc9e14d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc9e163  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e044..0xbc9e169

    // 0xbc9e16b..0xbc9e186
    LIFT-BODY;  // implement basic block 0xbc9e16b..0xbc9e186

    // 0xbc9e18a..0xbc9e1bb
    0xbc9e1a5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc9e1bb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e18a..0xbc9e1bb

    // 0xbc9e1c1..0xbc9e1fe
    LIFT-BODY;  // implement basic block 0xbc9e1c1..0xbc9e1fe

    // 0xbc9e201..0xbc9e201
    0xbc9e201  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9e201..0xbc9e201

    // 0xbc9e206..0xbc9e251
    LIFT-BODY;  // implement basic block 0xbc9e206..0xbc9e251

    // 0xbc9e254..0xbc9e254
    0xbc9e254  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9e254..0xbc9e254

    // 0xbc9e259..0xbc9e2a5
    0xbc9e274  call 0x56BA620                                ; -> sub_56ba620
    LIFT-BODY;  // implement basic block 0xbc9e259..0xbc9e2a5

    // 0xbc9e2a7..0xbc9e2a7
    LIFT-BODY;  // implement basic block 0xbc9e2a7..0xbc9e2a7

    // 0xbc9e2a9..0xbc9e2ec
    0xbc9e2e5  call r8
    LIFT-BODY;  // implement basic block 0xbc9e2a9..0xbc9e2ec

    // 0xbc9e2f2..0xbc9e3e0
    0xbc9e34c  call 0x568AD40                                ; -> sub_568ad40
    0xbc9e3d3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e2f2..0xbc9e3e0

    // 0xbc9e3e6..0xbc9e72c
    0xbc9e4ee  call 0x76A8A0                                 ; -> sub_76a8a0
    0xbc9e71f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e3e6..0xbc9e72c

    // 0xbc9e732..0xbc9e7c0
    LIFT-BODY;  // implement basic block 0xbc9e732..0xbc9e7c0

    // 0xbc9e7c2..0xbc9e7f3
    0xbc9e7cd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc9e7f3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e7c2..0xbc9e7f3

    // 0xbc9e7f9..0xbc9e7f9
    LIFT-BODY;  // implement basic block 0xbc9e7f9..0xbc9e7f9

    // 0xbc9e804..0xbc9e8b9
    0xbc9e8ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e804..0xbc9e8b9

    // 0xbc9e8bf..0xbc9e8ce
    LIFT-BODY;  // implement basic block 0xbc9e8bf..0xbc9e8ce

    // 0xbc9e8d0..0xbc9e8e4
    0xbc9e8d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e8d0..0xbc9e8e4

    // 0xbc9e8ea..0xbc9e8ed
    LIFT-BODY;  // implement basic block 0xbc9e8ea..0xbc9e8ed

    // 0xbc9e8f0..0xbc9e95c
    0xbc9e927  call 0xEEC6EC0                                ; -> sub_eec6ec0
    LIFT-BODY;  // implement basic block 0xbc9e8f0..0xbc9e95c

    // 0xbc9e961..0xbc9ea0e
    0xbc9ea01  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9e961..0xbc9ea0e

    // 0xbc9ea14..0xbc9ea23
    LIFT-BODY;  // implement basic block 0xbc9ea14..0xbc9ea23

    // 0xbc9ea25..0xbc9ea4d
    0xbc9ea36  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc9ea48  call 0x9BC830                                 ; -> sub_9bc830
    LIFT-BODY;  // implement basic block 0xbc9ea25..0xbc9ea4d

    // 0xbc9ea4e..0xbc9ea4e
    LIFT-BODY;  // implement basic block 0xbc9ea4e..0xbc9ea4e

    // 0xbc9ea50..0xbc9ea8a
    LIFT-BODY;  // implement basic block 0xbc9ea50..0xbc9ea8a

    // 0xbc9ea90..0xbc9eac4
    LIFT-BODY;  // implement basic block 0xbc9ea90..0xbc9eac4

    // 0xbc9eac8..0xbc9eadf
    LIFT-BODY;  // implement basic block 0xbc9eac8..0xbc9eadf

    // 0xbc9eae0..0xbc9eb10
    LIFT-BODY;  // implement basic block 0xbc9eae0..0xbc9eb10

    // 0xbc9eb12..0xbc9eb1d
    LIFT-BODY;  // implement basic block 0xbc9eb12..0xbc9eb1d

    // 0xbc9eb20..0xbc9eb4b
    LIFT-BODY;  // implement basic block 0xbc9eb20..0xbc9eb4b

    // 0xbc9eb4d..0xbc9eb69
    0xbc9eb5d  call 0x130EE0                                 ; -> sub_130ee0
    LIFT-BODY;  // implement basic block 0xbc9eb4d..0xbc9eb69

    // 0xbc9eb6d..0xbc9ebd0
    0xbc9eb83  call 0x56939C0                                ; -> sub_56939c0
    0xbc9eb97  call 0x5693A80                                ; -> sub_5693a80
    LIFT-BODY;  // implement basic block 0xbc9eb6d..0xbc9ebd0

    // 0xbc9ebd2..0xbc9ebd2
    LIFT-BODY;  // implement basic block 0xbc9ebd2..0xbc9ebd2

    // 0xbc9ebd9..0xbc9ebf2
    0xbc9ebec  call 0x9D6D0                                  ; -> sub_9d6d0
    LIFT-BODY;  // implement basic block 0xbc9ebd9..0xbc9ebf2

    // 0xbc9ebf4..0xbc9ebfa
    LIFT-BODY;  // implement basic block 0xbc9ebf4..0xbc9ebfa

    // 0xbc9ebfe..0xbc9ec10
    0xbc9ec0b  call 0xEEC6DE0                                ; -> sub_eec6de0
    LIFT-BODY;  // implement basic block 0xbc9ebfe..0xbc9ec10

    // 0xbc9ec14..0xbc9ec82
    0xbc9ec40  call 0xBCA8190                                ; -> sub_bca8190
    LIFT-BODY;  // implement basic block 0xbc9ec14..0xbc9ec82

    // 0xbc9ec85..0xbc9ec85
    0xbc9ec85  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9ec85..0xbc9ec85

    // 0xbc9ec8a..0xbc9ecc7
    LIFT-BODY;  // implement basic block 0xbc9ec8a..0xbc9ecc7

    // 0xbc9ecca..0xbc9ecca
    0xbc9ecca  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9ecca..0xbc9ecca

    // 0xbc9eccf..0xbc9ed0c
    LIFT-BODY;  // implement basic block 0xbc9eccf..0xbc9ed0c

    // 0xbc9ed0f..0xbc9ed0f
    0xbc9ed0f  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9ed0f..0xbc9ed0f

    // 0xbc9ed14..0xbc9ed3a
    0xbc9ed34  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9ed14..0xbc9ed3a

    // 0xbc9ed45..0xbc9ed76
    0xbc9ed60  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc9ed76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9ed45..0xbc9ed76

    // 0xbc9ed7c..0xbc9edb9
    LIFT-BODY;  // implement basic block 0xbc9ed7c..0xbc9edb9

    // 0xbc9edbc..0xbc9edbc
    0xbc9edbc  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9edbc..0xbc9edbc

    // 0xbc9edc1..0xbc9edfe
    LIFT-BODY;  // implement basic block 0xbc9edc1..0xbc9edfe

    // 0xbc9ee01..0xbc9ee01
    0xbc9ee01  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9ee01..0xbc9ee01

    // 0xbc9ee06..0xbc9ee43
    LIFT-BODY;  // implement basic block 0xbc9ee06..0xbc9ee43

    // 0xbc9ee46..0xbc9ee46
    0xbc9ee46  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xbc9ee46..0xbc9ee46

    // 0xbc9ee4b..0xbc9ee90
    0xbc9ee68  call rsi
    0xbc9ee72  call rsi
    LIFT-BODY;  // implement basic block 0xbc9ee4b..0xbc9ee90

    // 0xbc9ee92..0xbc9ee92
    LIFT-BODY;  // implement basic block 0xbc9ee92..0xbc9ee92

    // 0xbc9ee94..0xbc9eeed
    0xbc9eee6  call r8
    LIFT-BODY;  // implement basic block 0xbc9ee94..0xbc9eeed

    // 0xbc9eef3..0xbc9f052
    0xbc9ef4d  call 0x568AD40                                ; -> sub_568ad40
    0xbc9f045  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9eef3..0xbc9f052

    // 0xbc9f058..0xbc9f486
    0xbc9f175  call 0x76A8A0                                 ; -> sub_76a8a0
    0xbc9f479  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9f058..0xbc9f486

    // 0xbc9f48c..0xbc9f522
    LIFT-BODY;  // implement basic block 0xbc9f48c..0xbc9f522

    // 0xbc9f524..0xbc9f555
    0xbc9f52f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc9f555  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9f524..0xbc9f555

    // 0xbc9f55b..0xbc9f55b
    LIFT-BODY;  // implement basic block 0xbc9f55b..0xbc9f55b

    // 0xbc9f566..0xbc9f633
    0xbc9f626  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9f566..0xbc9f633

    // 0xbc9f639..0xbc9f648
    LIFT-BODY;  // implement basic block 0xbc9f639..0xbc9f648

    // 0xbc9f64a..0xbc9f65b
    0xbc9f64e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9f64a..0xbc9f65b

    // 0xbc9f661..0xbc9f664
    LIFT-BODY;  // implement basic block 0xbc9f661..0xbc9f664

    // 0xbc9f667..0xbc9f6c9
    0xbc9f68d  call 0xEEC6EC0                                ; -> sub_eec6ec0
    LIFT-BODY;  // implement basic block 0xbc9f667..0xbc9f6c9

    // 0xbc9f6ce..0xbc9f788
    0xbc9f77b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc9f6ce..0xbc9f788

    // 0xbc9f78e..0xbc9f79d
    LIFT-BODY;  // implement basic block 0xbc9f78e..0xbc9f79d

    // 0xbc9f79f..0xbc9f79f
    LIFT-BODY;  // implement basic block 0xbc9f79f..0xbc9f79f

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bc9d7a0: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc9d7a0, 0xbca3f7b) (rdis dis output, two spaces after address):
#if 0
0xbc9d7b1  call 0xE9E7970                                ; -> sub_e9e7970
0xbc9de49  call 0x567C8B0                                ; -> sub_567c8b0
0xbc9debf  call 0x567C8B0                                ; -> sub_567c8b0
0xbc9dfd5  call 0xBC09250                                ; -> sub_bc09250
0xbc9e0ce  call 0x9D6D0                                  ; -> sub_9d6d0
0xbc9e0ec  call 0xBC431B0                                ; -> sub_bc431b0
0xbc9e107  call 0x56BD700                                ; -> sub_56bd700
0xbc9e14d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e163  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e1a5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e1bb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e201  call 0xE935700                                ; -> sub_e935700
0xbc9e254  call 0xE935700                                ; -> sub_e935700
0xbc9e274  call 0x56BA620                                ; -> sub_56ba620
0xbc9e2e5  call r8
0xbc9e34c  call 0x568AD40                                ; -> sub_568ad40
0xbc9e3d3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e4ee  call 0x76A8A0                                 ; -> sub_76a8a0
0xbc9e71f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e7cd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e7f3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e8ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e8d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9e927  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbc9ea01  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9ea36  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9ea48  call 0x9BC830                                 ; -> sub_9bc830
0xbc9eb5d  call 0x130EE0                                 ; -> sub_130ee0
0xbc9eb83  call 0x56939C0                                ; -> sub_56939c0
0xbc9eb97  call 0x5693A80                                ; -> sub_5693a80
0xbc9ebec  call 0x9D6D0                                  ; -> sub_9d6d0
0xbc9ec0b  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbc9ec40  call 0xBCA8190                                ; -> sub_bca8190
0xbc9ec85  call 0xE935700                                ; -> sub_e935700
0xbc9ecca  call 0xE935700                                ; -> sub_e935700
0xbc9ed0f  call 0xE935700                                ; -> sub_e935700
0xbc9ed34  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9ed60  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9ed76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9edbc  call 0xE935700                                ; -> sub_e935700
0xbc9ee01  call 0xE935700                                ; -> sub_e935700
0xbc9ee46  call 0xE935700                                ; -> sub_e935700
0xbc9ee68  call rsi
0xbc9ee72  call rsi
0xbc9eee6  call r8
0xbc9ef4d  call 0x568AD40                                ; -> sub_568ad40
0xbc9f045  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f175  call 0x76A8A0                                 ; -> sub_76a8a0
0xbc9f479  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f52f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f555  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f626  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f64e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f68d  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbc9f77b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f7b0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc9f7c2  call 0x9BC830                                 ; -> sub_9bc830
#endif

// Calls out of lifted code:
//   sub_e9e7970 (0xe9e7970, boundary) - call 0xE9E7970                                ; -> sub_e9e7970
//   sub_567c8b0 (0x567c8b0, lift set) - call 0x567C8B0                                ; -> sub_567c8b0
//   sub_567c8b0 (0x567c8b0, lift set) - call 0x567C8B0                                ; -> sub_567c8b0
//   sub_bc09250 (0xbc09250, lift set) - call 0xBC09250                                ; -> sub_bc09250
//   sub_9d6d0 (0x9d6d0, boundary) - call 0x9D6D0                                  ; -> sub_9d6d0
//   sub_bc431b0 (0xbc431b0, lift set) - call 0xBC431B0                                ; -> sub_bc431b0
//   sub_56bd700 (0x56bd700, lift set) - call 0x56BD700                                ; -> sub_56bd700
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_56ba620 (0x56ba620, lift set) - call 0x56BA620                                ; -> sub_56ba620
//   call r8 (indirect, boundary via data slot)
//   sub_568ad40 (0x568ad40, lift set) - call 0x568AD40                                ; -> sub_568ad40
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_76a8a0 (0x76a8a0, boundary) - call 0x76A8A0                                 ; -> sub_76a8a0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ec0 (0xeec6ec0, lift set) - call 0xEEC6EC0                                ; -> sub_eec6ec0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_9bc830 (0x9bc830, boundary) - call 0x9BC830                                 ; -> sub_9bc830
//   sub_130ee0 (0x130ee0, lift set) - call 0x130EE0                                 ; -> sub_130ee0
//   sub_56939c0 (0x56939c0, lift set) - call 0x56939C0                                ; -> sub_56939c0
//   sub_5693a80 (0x5693a80, lift set) - call 0x5693A80                                ; -> sub_5693a80
//   sub_9d6d0 (0x9d6d0, boundary) - call 0x9D6D0                                  ; -> sub_9d6d0
//   sub_eec6de0 (0xeec6de0, lift set) - call 0xEEC6DE0                                ; -> sub_eec6de0
//   sub_bca8190 (0xbca8190, lift set) - call 0xBCA8190                                ; -> sub_bca8190
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   call rsi (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   call r8 (indirect, boundary via data slot)
//   sub_568ad40 (0x568ad40, lift set) - call 0x568AD40                                ; -> sub_568ad40
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_76a8a0 (0x76a8a0, boundary) - call 0x76A8A0                                 ; -> sub_76a8a0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ec0 (0xeec6ec0, lift set) - call 0xEEC6EC0                                ; -> sub_eec6ec0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_bc9d7a0, "sub_bc9d7a0", 0xbc9d7a0, sub_bc9d7a0, nullptr);

} // namespace native::bgfx