// LIFT 0xe824fbe size 0x8525 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e824fbe.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Forward declaration for callee in lift set: sub_bc5f110
extern "C" void sub_bc5f110(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e820500
extern "C" void sub_e820500(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e82d960
extern "C" void sub_e82d960(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e82dcc0
extern "C" void sub_e82dcc0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e82de90
extern "C" void sub_e82de90(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e835b50
extern "C" void sub_e835b50(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e835f00
extern "C" void sub_e835f00(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e83abb0
extern "C" void sub_e83abb0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e83ace0
extern "C" void sub_e83ace0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e83aed0
extern "C" void sub_e83aed0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e935700
extern "C" void sub_e935700(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ebce390
extern "C" void sub_ebce390(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe825162: call r10 (indirect)
//   0xe825260: call r10 (indirect)
//   0xe8252c4: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe82533b: call 0xEBD1560                                ; -> sub_ebd1560 -> sub_ebd1560
//   0xe82548c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe82553a: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825596: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825688: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825762: call r10 (indirect)
//   0xe8258ad: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825954: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825986: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8259aa: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825a55: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xe825d18: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825dd3: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825e76: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825f52: call r10 (indirect)
//   0xe826061: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe8262b2: call 0xEBCE430                                ; -> sub_ebce430 -> sub_ebce430
//   0xe8262c7: call 0xEBCE430                                ; -> sub_ebce430 -> sub_ebce430
//   0xe82681d: call r10 (indirect)
//   0xe8268d3: call r10 (indirect)
//   0xe8268e5: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xe826be7: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e824fbe(/* LIFT-BODY: exact args */);

void sub_e824fbe(/* LIFT-BODY: exact args */) {
// CHUNK 0xe824fbe..0xe8267b7
    // 0xe824fbe..0xe824fcd
    LIFT-BODY;  // implement basic block 0xe824fbe..0xe824fcd

    // 0xe824fd2..0xe824fe0
    LIFT-BODY;  // implement basic block 0xe824fd2..0xe824fe0

    // 0xe824fe6..0xe82502c
    LIFT-BODY;  // implement basic block 0xe824fe6..0xe82502c

    // 0xe825030..0xe825041
    LIFT-BODY;  // implement basic block 0xe825030..0xe825041

    // 0xe825043..0xe82504c
    LIFT-BODY;  // implement basic block 0xe825043..0xe82504c

    // 0xe825050..0xe825096
    LIFT-BODY;  // implement basic block 0xe825050..0xe825096

    // 0xe825098..0xe82509f
    LIFT-BODY;  // implement basic block 0xe825098..0xe82509f

    // 0xe8250a5..0xe825124
    0xe8250c2  call 0xE82D960                                ; -> sub_e82d960
    0xe8250fb  call 0xEBCE390                                ; -> sub_ebce390
    LIFT-BODY;  // implement basic block 0xe8250a5..0xe825124

    // 0xe82512b..0xe825131
    LIFT-BODY;  // implement basic block 0xe82512b..0xe825131

    // 0xe825138..0xe825166
    0xe825162  call r10
    LIFT-BODY;  // implement basic block 0xe825138..0xe825166

    // 0xe82516b..0xe8251b5
    0xe825174  call 0xE82DCC0                                ; -> sub_e82dcc0
    LIFT-BODY;  // implement basic block 0xe82516b..0xe8251b5

    // 0xe8251ba..0xe8251c3
    LIFT-BODY;  // implement basic block 0xe8251ba..0xe8251c3

    // 0xe8251c8..0xe8251d2
    LIFT-BODY;  // implement basic block 0xe8251c8..0xe8251d2

    // 0xe8251d6..0xe8251ed
    LIFT-BODY;  // implement basic block 0xe8251d6..0xe8251ed

    // 0xe8251f0..0xe825264
    0xe825260  call r10
    LIFT-BODY;  // implement basic block 0xe8251f0..0xe825264

    // 0xe825269..0xe825284
    LIFT-BODY;  // implement basic block 0xe825269..0xe825284

    // 0xe825289..0xe8252ec
    0xe8252c4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe825289..0xe8252ec

    // 0xe8252f3..0xe82531a
    LIFT-BODY;  // implement basic block 0xe8252f3..0xe82531a

    // 0xe82531f..0xe82532d
    LIFT-BODY;  // implement basic block 0xe82531f..0xe82532d

    // 0xe825333..0xe8253c9
    0xe82533b  call 0xEBD1560                                ; -> sub_ebd1560
    0xe825369  call 0xE82D960                                ; -> sub_e82d960
    0xe8253a6  call 0xEBCE390                                ; -> sub_ebce390
    LIFT-BODY;  // implement basic block 0xe825333..0xe8253c9

    // 0xe8253cf..0xe8253d9
    LIFT-BODY;  // implement basic block 0xe8253cf..0xe8253d9

    // 0xe8253de..0xe825493
    0xe82548c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8253de..0xe825493

    // 0xe825498..0xe8254a1
    LIFT-BODY;  // implement basic block 0xe825498..0xe8254a1

    // 0xe8254a6..0xe8254b0
    LIFT-BODY;  // implement basic block 0xe8254a6..0xe8254b0

    // 0xe8254b4..0xe8254cf
    LIFT-BODY;  // implement basic block 0xe8254b4..0xe8254cf

    // 0xe8254d2..0xe825540
    0xe82553a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8254d2..0xe825540

    // 0xe825541..0xe825561
    LIFT-BODY;  // implement basic block 0xe825541..0xe825561

    // 0xe825566..0xe825566
    LIFT-BODY;  // implement basic block 0xe825566..0xe825566

    // 0xe825571..0xe825571
    LIFT-BODY;  // implement basic block 0xe825571..0xe825571

    // 0xe825578..0xe8255cc
    0xe825596  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe825578..0xe8255cc

    // 0xe8255d3..0xe8255ed
    LIFT-BODY;  // implement basic block 0xe8255d3..0xe8255ed

    // 0xe8255f2..0xe82562a
    LIFT-BODY;  // implement basic block 0xe8255f2..0xe82562a

    // 0xe82562c..0xe82568e
    0xe825688  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe82562c..0xe82568e

    // 0xe82568f..0xe8256c6
    LIFT-BODY;  // implement basic block 0xe82568f..0xe8256c6

    // 0xe8256c8..0xe8256d2
    LIFT-BODY;  // implement basic block 0xe8256c8..0xe8256d2

    // 0xe8256d6..0xe8256ee
    LIFT-BODY;  // implement basic block 0xe8256d6..0xe8256ee

    // 0xe8256f1..0xe825765
    0xe825762  call r10
    LIFT-BODY;  // implement basic block 0xe8256f1..0xe825765

    // 0xe825766..0xe825782
    LIFT-BODY;  // implement basic block 0xe825766..0xe825782

    // 0xe825786..0xe82578c
    LIFT-BODY;  // implement basic block 0xe825786..0xe82578c

    // 0xe825790..0xe8257a1
    LIFT-BODY;  // implement basic block 0xe825790..0xe8257a1

    // 0xe8257a6..0xe8257d6
    LIFT-BODY;  // implement basic block 0xe8257a6..0xe8257d6

    // 0xe8257de..0xe825816
    LIFT-BODY;  // implement basic block 0xe8257de..0xe825816

    // 0xe825818..0xe825822
    LIFT-BODY;  // implement basic block 0xe825818..0xe825822

    // 0xe825826..0xe825841
    LIFT-BODY;  // implement basic block 0xe825826..0xe825841

    // 0xe825844..0xe8258f0
    0xe8258ad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe825844..0xe8258f0

    // 0xe8258f5..0xe82595b
    0xe825910  call 0xE820500                                ; -> sub_e820500
    0xe825954  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8258f5..0xe82595b

    // 0xe825962..0xe825a09
    0xe825986  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8259aa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xe8259d7  call 0xE82DE90                                ; -> sub_e82de90
    LIFT-BODY;  // implement basic block 0xe825962..0xe825a09

    // 0xe825a0c..0xe825a14
    0xe825a0f  call 0xE935700                                ; -> sub_e935700
    LIFT-BODY;  // implement basic block 0xe825a0c..0xe825a14

    // 0xe825a19..0xe825a2d
    LIFT-BODY;  // implement basic block 0xe825a19..0xe825a2d

    // 0xe825a32..0xe825a3e
    0xe825a39  call 0xE835B50                                ; -> sub_e835b50
    LIFT-BODY;  // implement basic block 0xe825a32..0xe825a3e

    // 0xe825a3f..0xe825a68
    0xe825a55  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe825a3f..0xe825a68

    // 0xe825a70..0xe825a9f
    LIFT-BODY;  // implement basic block 0xe825a70..0xe825a9f

    // 0xe825aab..0xe825ab1
    LIFT-BODY;  // implement basic block 0xe825aab..0xe825ab1

    // 0xe825ab3..0xe825c0a
    0xe825b62  call 0xE82DCC0                                ; -> sub_e82dcc0
    LIFT-BODY;  // implement basic block 0xe825ab3..0xe825c0a

    // 0xe825c10..0xe825c36
    LIFT-BODY;  // implement basic block 0xe825c10..0xe825c36

    // 0xe825c3a..0xe825c44
    LIFT-BODY;  // implement basic block 0xe825c3a..0xe825c44

    // 0xe825c46..0xe825d1f
    0xe825d18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe825c46..0xe825d1f

    // 0xe825d24..0xe825dda
    0xe825dd3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe825d24..0xe825dda

    // 0xe825ddf..0xe825e17
    LIFT-BODY;  // implement basic block 0xe825ddf..0xe825e17

    // 0xe825e19..0xe825e7d
    0xe825e76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe825e19..0xe825e7d

    // 0xe825e80..0xe825eb3
    LIFT-BODY;  // implement basic block 0xe825e80..0xe825eb3

    // 0xe825eb5..0xe825ec0
    LIFT-BODY;  // implement basic block 0xe825eb5..0xe825ec0

    // 0xe825ec4..0xe825ede
    LIFT-BODY;  // implement basic block 0xe825ec4..0xe825ede

    // 0xe825ee1..0xe825f56
    0xe825f52  call r10
    LIFT-BODY;  // implement basic block 0xe825ee1..0xe825f56

    // 0xe825f5b..0xe825f8b
    LIFT-BODY;  // implement basic block 0xe825f5b..0xe825f8b

    // 0xe825f93..0xe825fc7
    LIFT-BODY;  // implement basic block 0xe825f93..0xe825fc7

    // 0xe825fc9..0xe825fd4
    LIFT-BODY;  // implement basic block 0xe825fc9..0xe825fd4

    // 0xe825fd8..0xe825ff5
    LIFT-BODY;  // implement basic block 0xe825fd8..0xe825ff5

    // 0xe825ff8..0xe826067
    0xe826061  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe825ff8..0xe826067

    // 0xe826068..0xe826108
    LIFT-BODY;  // implement basic block 0xe826068..0xe826108

    // 0xe826110..0xe82612d
    LIFT-BODY;  // implement basic block 0xe826110..0xe82612d

    // 0xe826131..0xe826147
    LIFT-BODY;  // implement basic block 0xe826131..0xe826147

    // 0xe82614e..0xe826216
    0xe8261e2  call 0xE83ACE0                                ; -> sub_e83ace0
    LIFT-BODY;  // implement basic block 0xe82614e..0xe826216

    // 0xe826220..0xe826239
    LIFT-BODY;  // implement basic block 0xe826220..0xe826239

    // 0xe826240..0xe826261
    LIFT-BODY;  // implement basic block 0xe826240..0xe826261

    // 0xe826270..0xe826285
    LIFT-BODY;  // implement basic block 0xe826270..0xe826285

    // 0xe826287..0xe826287
    LIFT-BODY;  // implement basic block 0xe826287..0xe826287

    // 0xe82628a..0xe8262d3
    0xe8262b2  call 0xEBCE430                                ; -> sub_ebce430
    0xe8262c7  call 0xEBCE430                                ; -> sub_ebce430
    LIFT-BODY;  // implement basic block 0xe82628a..0xe8262d3

    // 0xe8262d9..0xe8262ee
    LIFT-BODY;  // implement basic block 0xe8262d9..0xe8262ee

    // 0xe8262f5..0xe82631d
    0xe82630e  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe8262f5..0xe82631d

    // 0xe826320..0xe82632d
    LIFT-BODY;  // implement basic block 0xe826320..0xe82632d

    // 0xe826333..0xe82637d
    LIFT-BODY;  // implement basic block 0xe826333..0xe82637d

    // 0xe826380..0xe826391
    LIFT-BODY;  // implement basic block 0xe826380..0xe826391

    // 0xe826393..0xe82639c
    LIFT-BODY;  // implement basic block 0xe826393..0xe82639c

    // 0xe8263a0..0xe8263e6
    LIFT-BODY;  // implement basic block 0xe8263a0..0xe8263e6

    // 0xe8263e8..0xe8263eb
    LIFT-BODY;  // implement basic block 0xe8263e8..0xe8263eb

    // 0xe8263ed..0xe8263f4
    LIFT-BODY;  // implement basic block 0xe8263ed..0xe8263f4

    // 0xe8263f7..0xe826438
    LIFT-BODY;  // implement basic block 0xe8263f7..0xe826438

    // 0xe82643a..0xe826496
    0xe826471  call 0xE835F00                                ; -> sub_e835f00
    LIFT-BODY;  // implement basic block 0xe82643a..0xe826496

    // 0xe826498..0xe8264af
    LIFT-BODY;  // implement basic block 0xe826498..0xe8264af

    // 0xe8264b6..0xe8264f6
    0xe8264d4  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe8264b6..0xe8264f6

    // 0xe826500..0xe826500
    LIFT-BODY;  // implement basic block 0xe826500..0xe826500

    // 0xe826507..0xe826511
    LIFT-BODY;  // implement basic block 0xe826507..0xe826511

    // 0xe826513..0xe82653e
    LIFT-BODY;  // implement basic block 0xe826513..0xe82653e

    // 0xe826540..0xe826553
    LIFT-BODY;  // implement basic block 0xe826540..0xe826553

    // 0xe826555..0xe826558
    LIFT-BODY;  // implement basic block 0xe826555..0xe826558

    // 0xe82655a..0xe82656d
    LIFT-BODY;  // implement basic block 0xe82655a..0xe82656d

    // 0xe826573..0xe8265b9
    LIFT-BODY;  // implement basic block 0xe826573..0xe8265b9

    // 0xe8265c0..0xe8265d1
    LIFT-BODY;  // implement basic block 0xe8265c0..0xe8265d1

    // 0xe8265d3..0xe8265db
    LIFT-BODY;  // implement basic block 0xe8265d3..0xe8265db

    // 0xe8265e0..0xe826626
    LIFT-BODY;  // implement basic block 0xe8265e0..0xe826626

    // 0xe826628..0xe826630
    LIFT-BODY;  // implement basic block 0xe826628..0xe826630

    // 0xe826636..0xe82664b
    LIFT-BODY;  // implement basic block 0xe826636..0xe82664b

    // 0xe82664d..0xe8266a9
    0xe826684  call 0xE835F00                                ; -> sub_e835f00
    LIFT-BODY;  // implement basic block 0xe82664d..0xe8266a9

    // 0xe8266ab..0xe8266c2
    LIFT-BODY;  // implement basic block 0xe8266ab..0xe8266c2

    // 0xe8266c9..0xe826705
    0xe8266e7  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe8266c9..0xe826705

    // 0xe826710..0xe826710
    LIFT-BODY;  // implement basic block 0xe826710..0xe826710

    // 0xe826717..0xe826721
    LIFT-BODY;  // implement basic block 0xe826717..0xe826721

    // 0xe826723..0xe82674e
    LIFT-BODY;  // implement basic block 0xe826723..0xe82674e

    // 0xe826750..0xe826763
    LIFT-BODY;  // implement basic block 0xe826750..0xe826763

    // 0xe826765..0xe826768
    LIFT-BODY;  // implement basic block 0xe826765..0xe826768

    // 0xe82676a..0xe826779
    LIFT-BODY;  // implement basic block 0xe82676a..0xe826779

    // 0xe82677f..0xe8267c8
    LIFT-BODY;  // implement basic block 0xe82677f..0xe8267c8

    // 0xe8267cd..0xe82683c
    0xe82681d  call r10
    LIFT-BODY;  // implement basic block 0xe8267cd..0xe82683c

    // 0xe826843..0xe826879
    LIFT-BODY;  // implement basic block 0xe826843..0xe826879

    // 0xe826880..0xe826896
    LIFT-BODY;  // implement basic block 0xe826880..0xe826896

    // 0xe82689c..0xe826921
    0xe8268d3  call r10
    0xe8268e5  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe82689c..0xe826921

    // 0xe826930..0xe826959
    LIFT-BODY;  // implement basic block 0xe826930..0xe826959

    // 0xe82695e..0xe826971
    LIFT-BODY;  // implement basic block 0xe82695e..0xe826971

    // 0xe826977..0xe8269bd
    LIFT-BODY;  // implement basic block 0xe826977..0xe8269bd

    // 0xe8269c0..0xe8269d1
    LIFT-BODY;  // implement basic block 0xe8269c0..0xe8269d1

    // 0xe8269d3..0xe8269db
    LIFT-BODY;  // implement basic block 0xe8269d3..0xe8269db

    // 0xe8269e0..0xe826a26
    LIFT-BODY;  // implement basic block 0xe8269e0..0xe826a26

    // 0xe826a28..0xe826a35
    LIFT-BODY;  // implement basic block 0xe826a28..0xe826a35

    // 0xe826a3a..0xe826a4c
    LIFT-BODY;  // implement basic block 0xe826a3a..0xe826a4c

    // 0xe826a52..0xe826abf
    0xe826a5c  call 0xE83AED0                                ; -> sub_e83aed0
    0xe826a70  call 0xE83AED0                                ; -> sub_e83aed0
    0xe826a8d  call 0xE83ABB0                                ; -> sub_e83abb0
    0xe826ab2  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe826a52..0xe826abf

    // 0xe826ac1..0xe826ad2
    LIFT-BODY;  // implement basic block 0xe826ac1..0xe826ad2

    // 0xe826ad8..0xe826b1e
    LIFT-BODY;  // implement basic block 0xe826ad8..0xe826b1e

    // 0xe826b20..0xe826b31
    LIFT-BODY;  // implement basic block 0xe826b20..0xe826b31

    // 0xe826b33..0xe826b3c
    LIFT-BODY;  // implement basic block 0xe826b33..0xe826b3c

    // 0xe826b40..0xe826b86
    LIFT-BODY;  // implement basic block 0xe826b40..0xe826b86

    // 0xe826b88..0xe826b8b
    LIFT-BODY;  // implement basic block 0xe826b88..0xe826b8b

    // 0xe826b8d..0xe826b90
    LIFT-BODY;  // implement basic block 0xe826b8d..0xe826b90

    // 0xe826b92..0xe826b96
    LIFT-BODY;  // implement basic block 0xe826b92..0xe826b96

    // 0xe826b98..0xe826b9b
    LIFT-BODY;  // implement basic block 0xe826b98..0xe826b9b

    // 0xe826b9e..0xe826bee
    0xe826be7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe826b9e..0xe826bee

    // 0xe826bf3..0xe826bf3
    LIFT-BODY;  // implement basic block 0xe826bf3..0xe826bf3

    // 0xe826bf5..0xe826c29
    LIFT-BODY;  // implement basic block 0xe826bf5..0xe826c29

    // 0xe826c2f..0xe826c52
    LIFT-BODY;  // implement basic block 0xe826c2f..0xe826c52

    // 0xe826c54..0xe826cb6
    0xe826c8a  call 0xE835F00                                ; -> sub_e835f00
    LIFT-BODY;  // implement basic block 0xe826c54..0xe826cb6

    // 0xe826cbc..0xe826cca
    LIFT-BODY;  // implement basic block 0xe826cbc..0xe826cca

    // 0xe826cd2..0xe826d15
    0xe826cf0  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe826cd2..0xe826d15

    // 0xe826d20..0xe826d20
    LIFT-BODY;  // implement basic block 0xe826d20..0xe826d20

    // 0xe826d27..0xe826d32
    LIFT-BODY;  // implement basic block 0xe826d27..0xe826d32

    // 0xe826d38..0xe826d65
    LIFT-BODY;  // implement basic block 0xe826d38..0xe826d65

    // 0xe826d70..0xe826d85
    LIFT-BODY;  // implement basic block 0xe826d70..0xe826d85

    // 0xe826d87..0xe826d8c
    LIFT-BODY;  // implement basic block 0xe826d87..0xe826d8c

    // 0xe826d90..0xe826d90
    LIFT-BODY;  // implement basic block 0xe826d90..0xe826d90

    // 0xe826d97..0xe826da1
    LIFT-BODY;  // implement basic block 0xe826d97..0xe826da1

    // 0xe826da7..0xe826dd4
    LIFT-BODY;  // implement basic block 0xe826da7..0xe826dd4

    // 0xe826de0..0xe826df3
    LIFT-BODY;  // implement basic block 0xe826de0..0xe826df3

    // 0xe826df5..0xe826df8
    LIFT-BODY;  // implement basic block 0xe826df5..0xe826df8

    // 0xe826dfa..0xe826e0d
    LIFT-BODY;  // implement basic block 0xe826dfa..0xe826e0d

    // 0xe826e13..0xe826e59
    LIFT-BODY;  // implement basic block 0xe826e13..0xe826e59

    // 0xe826e60..0xe826e71
    LIFT-BODY;  // implement basic block 0xe826e60..0xe826e71

    // 0xe826e73..0xe826e7b
    LIFT-BODY;  // implement basic block 0xe826e73..0xe826e7b

    // 0xe826e80..0xe826ec6
    LIFT-BODY;  // implement basic block 0xe826e80..0xe826ec6

    // 0xe826ec8..0xe826ed0
    LIFT-BODY;  // implement basic block 0xe826ec8..0xe826ed0

    // 0xe826ed2..0xe826ed2
    LIFT-BODY;  // implement basic block 0xe826ed2..0xe826ed2

    // 0xe826ed7..0xe826f02
    LIFT-BODY;  // implement basic block 0xe826ed7..0xe826f02

    // 0xe826f08..0xe826f6f
    0xe826f42  call 0xE83ACE0                                ; -> sub_e83ace0
    LIFT-BODY;  // implement basic block 0xe826f08..0xe826f6f

    // 0xe826f70..0xe826f85
    LIFT-BODY;  // implement basic block 0xe826f70..0xe826f85

    // 0xe826f90..0xe826faa
    LIFT-BODY;  // implement basic block 0xe826f90..0xe826faa

    // 0xe826fb0..0xe826fb7
    LIFT-BODY;  // implement basic block 0xe826fb0..0xe826fb7

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e824fbe: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe824fbe, 0xe82d4e3) (rdis dis output, two spaces after address):
#if 0
0xe8250c2  call 0xE82D960                                ; -> sub_e82d960
0xe8250fb  call 0xEBCE390                                ; -> sub_ebce390
0xe825162  call r10
0xe825174  call 0xE82DCC0                                ; -> sub_e82dcc0
0xe825260  call r10
0xe8252c4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82533b  call 0xEBD1560                                ; -> sub_ebd1560
0xe825369  call 0xE82D960                                ; -> sub_e82d960
0xe8253a6  call 0xEBCE390                                ; -> sub_ebce390
0xe82548c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82553a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825596  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825688  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825762  call r10
0xe8258ad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825910  call 0xE820500                                ; -> sub_e820500
0xe825954  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825986  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8259aa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8259d7  call 0xE82DE90                                ; -> sub_e82de90
0xe825a0f  call 0xE935700                                ; -> sub_e935700
0xe825a39  call 0xE835B50                                ; -> sub_e835b50
0xe825a55  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe825b62  call 0xE82DCC0                                ; -> sub_e82dcc0
0xe825d18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825dd3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825e76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe825f52  call r10
0xe826061  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8261e2  call 0xE83ACE0                                ; -> sub_e83ace0
0xe8262b2  call 0xEBCE430                                ; -> sub_ebce430
0xe8262c7  call 0xEBCE430                                ; -> sub_ebce430
0xe82630e  call 0xBC5F110                                ; -> sub_bc5f110
0xe826471  call 0xE835F00                                ; -> sub_e835f00
0xe8264d4  call 0xBC5F110                                ; -> sub_bc5f110
0xe826684  call 0xE835F00                                ; -> sub_e835f00
0xe8266e7  call 0xBC5F110                                ; -> sub_bc5f110
0xe82681d  call r10
0xe8268d3  call r10
0xe8268e5  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe826a5c  call 0xE83AED0                                ; -> sub_e83aed0
0xe826a70  call 0xE83AED0                                ; -> sub_e83aed0
0xe826a8d  call 0xE83ABB0                                ; -> sub_e83abb0
0xe826ab2  call 0xBC5F110                                ; -> sub_bc5f110
0xe826be7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe826c8a  call 0xE835F00                                ; -> sub_e835f00
0xe826cf0  call 0xBC5F110                                ; -> sub_bc5f110
0xe826f42  call 0xE83ACE0                                ; -> sub_e83ace0
#endif

// Calls out of lifted code:
//   sub_e82d960 (0xe82d960, lift set) - call 0xE82D960                                ; -> sub_e82d960
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   call r10 (indirect, boundary via data slot)
//   sub_e82dcc0 (0xe82dcc0, lift set) - call 0xE82DCC0                                ; -> sub_e82dcc0
//   call r10 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_ebd1560 (0xebd1560, boundary) - call 0xEBD1560                                ; -> sub_ebd1560
//   sub_e82d960 (0xe82d960, lift set) - call 0xE82D960                                ; -> sub_e82d960
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e820500 (0xe820500, lift set) - call 0xE820500                                ; -> sub_e820500
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e82de90 (0xe82de90, lift set) - call 0xE82DE90                                ; -> sub_e82de90
//   sub_e935700 (0xe935700, lift set) - call 0xE935700                                ; -> sub_e935700
//   sub_e835b50 (0xe835b50, lift set) - call 0xE835B50                                ; -> sub_e835b50
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_e82dcc0 (0xe82dcc0, lift set) - call 0xE82DCC0                                ; -> sub_e82dcc0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e83ace0 (0xe83ace0, lift set) - call 0xE83ACE0                                ; -> sub_e83ace0
//   sub_ebce430 (0xebce430, boundary) - call 0xEBCE430                                ; -> sub_ebce430
//   sub_ebce430 (0xebce430, boundary) - call 0xEBCE430                                ; -> sub_ebce430
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_e835f00 (0xe835f00, lift set) - call 0xE835F00                                ; -> sub_e835f00
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_e835f00 (0xe835f00, lift set) - call 0xE835F00                                ; -> sub_e835f00
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   call r10 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_e83aed0 (0xe83aed0, lift set) - call 0xE83AED0                                ; -> sub_e83aed0
//   sub_e83aed0 (0xe83aed0, lift set) - call 0xE83AED0                                ; -> sub_e83aed0
//   sub_e83abb0 (0xe83abb0, lift set) - call 0xE83ABB0                                ; -> sub_e83abb0
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e835f00 (0xe835f00, lift set) - call 0xE835F00                                ; -> sub_e835f00
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_e83ace0 (0xe83ace0, lift set) - call 0xE83ACE0                                ; -> sub_e83ace0
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e824fbe, "sub_e824fbe", 0xe824fbe, sub_e824fbe, nullptr);

} // namespace native::d3d12