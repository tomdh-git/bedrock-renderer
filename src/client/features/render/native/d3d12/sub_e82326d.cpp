// LIFT 0xe82326d size 0xa276 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e82326d.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Forward declaration for callee in lift set: sub_bc5f110
extern "C" void sub_bc5f110(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e82d960
extern "C" void sub_e82d960(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e82dcc0
extern "C" void sub_e82dcc0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e835f00
extern "C" void sub_e835f00(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e83abb0
extern "C" void sub_e83abb0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e83ace0
extern "C" void sub_e83ace0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_e83aed0
extern "C" void sub_e83aed0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ebce390
extern "C" void sub_ebce390(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xe8233de: call r10 (indirect)
//   0xe823493: call r10 (indirect)
//   0xe8234a5: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xe8235f1: call 0xEBCE430                                ; -> sub_ebce430 -> sub_ebce430
//   0xe823606: call 0xEBCE430                                ; -> sub_ebce430 -> sub_ebce430
//   0xe823833: call r10 (indirect)
//   0xe823929: call r10 (indirect)
//   0xe8239e3: call r10 (indirect)
//   0xe8239f5: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xe823e30: call r10 (indirect)
//   0xe823ee3: call r10 (indirect)
//   0xe823ef5: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xe824419: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe824812: call 0xEBCE430                                ; -> sub_ebce430 -> sub_ebce430
//   0xe824827: call 0xEBCE430                                ; -> sub_ebce430 -> sub_ebce430
//   0xe82491c: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe824a36: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe824c35: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe824cf0: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe824d93: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe824e72: call r10 (indirect)
//   0xe824f81: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xe825162: call r10 (indirect)
//   0xe825260: call r10 (indirect)

} // namespace

// LIFT-BODY: replace with exact x64 Microsoft ABI signature matching the original
extern "C" void sub_e82326d(/* LIFT-BODY: exact args */);

void sub_e82326d(/* LIFT-BODY: exact args */) {
    // 0xe82326d..0xe82329d
    LIFT-BODY;  // implement basic block 0xe82326d..0xe82329d

    // 0xe8232a0..0xe8232c8
    LIFT-BODY;  // implement basic block 0xe8232a0..0xe8232c8

    // 0xe8232cc..0xe8232d9
    LIFT-BODY;  // implement basic block 0xe8232cc..0xe8232d9

    // 0xe8232e0..0xe8233f6
    0xe8233de  call r10
    LIFT-BODY;  // implement basic block 0xe8232e0..0xe8233f6

    // 0xe8233fd..0xe82343a
    LIFT-BODY;  // implement basic block 0xe8233fd..0xe82343a

    // 0xe823440..0xe823456
    LIFT-BODY;  // implement basic block 0xe823440..0xe823456

    // 0xe82345c..0xe8234e1
    0xe823493  call r10
    0xe8234a5  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe82345c..0xe8234e1

    // 0xe8234f0..0xe82350b
    LIFT-BODY;  // implement basic block 0xe8234f0..0xe82350b

    // 0xe82350f..0xe82354b
    LIFT-BODY;  // implement basic block 0xe82350f..0xe82354b

    // 0xe82354d..0xe82354d
    LIFT-BODY;  // implement basic block 0xe82354d..0xe82354d

    // 0xe823552..0xe82356a
    LIFT-BODY;  // implement basic block 0xe823552..0xe82356a

    // 0xe823570..0xe823589
    LIFT-BODY;  // implement basic block 0xe823570..0xe823589

    // 0xe823590..0xe8235aa
    LIFT-BODY;  // implement basic block 0xe823590..0xe8235aa

    // 0xe8235b0..0xe8235c5
    LIFT-BODY;  // implement basic block 0xe8235b0..0xe8235c5

    // 0xe8235c7..0xe8235c7
    LIFT-BODY;  // implement basic block 0xe8235c7..0xe8235c7

    // 0xe8235ca..0xe823619
    0xe8235f1  call 0xEBCE430                                ; -> sub_ebce430
    0xe823606  call 0xEBCE430                                ; -> sub_ebce430
    LIFT-BODY;  // implement basic block 0xe8235ca..0xe823619

    // 0xe82361f..0xe823635
    LIFT-BODY;  // implement basic block 0xe82361f..0xe823635

    // 0xe82363c..0xe823671
    0xe823658  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe82363c..0xe823671

    // 0xe823680..0xe82368d
    LIFT-BODY;  // implement basic block 0xe823680..0xe82368d

    // 0xe823693..0xe8236d9
    LIFT-BODY;  // implement basic block 0xe823693..0xe8236d9

    // 0xe8236e0..0xe8236f1
    LIFT-BODY;  // implement basic block 0xe8236e0..0xe8236f1

    // 0xe8236f3..0xe8236fc
    LIFT-BODY;  // implement basic block 0xe8236f3..0xe8236fc

    // 0xe823700..0xe823746
    LIFT-BODY;  // implement basic block 0xe823700..0xe823746

    // 0xe823748..0xe82374b
    LIFT-BODY;  // implement basic block 0xe823748..0xe82374b

    // 0xe82374d..0xe823754
    LIFT-BODY;  // implement basic block 0xe82374d..0xe823754

    // 0xe823757..0xe8237f4
    0xe82378b  call 0xE82D960                                ; -> sub_e82d960
    0xe8237cb  call 0xEBCE390                                ; -> sub_ebce390
    LIFT-BODY;  // implement basic block 0xe823757..0xe8237f4

    // 0xe8237fb..0xe823801
    LIFT-BODY;  // implement basic block 0xe8237fb..0xe823801

    // 0xe823808..0xe82383c
    0xe823833  call r10
    LIFT-BODY;  // implement basic block 0xe823808..0xe82383c

    // 0xe823840..0xe823878
    LIFT-BODY;  // implement basic block 0xe823840..0xe823878

    // 0xe82387e..0xe823948
    0xe823929  call r10
    LIFT-BODY;  // implement basic block 0xe82387e..0xe823948

    // 0xe82394f..0xe82398a
    LIFT-BODY;  // implement basic block 0xe82394f..0xe82398a

    // 0xe823990..0xe8239a6
    LIFT-BODY;  // implement basic block 0xe823990..0xe8239a6

    // 0xe8239ac..0xe823a31
    0xe8239e3  call r10
    0xe8239f5  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe8239ac..0xe823a31

    // 0xe823a40..0xe823a58
    LIFT-BODY;  // implement basic block 0xe823a40..0xe823a58

    // 0xe823a5f..0xe823a92
    LIFT-BODY;  // implement basic block 0xe823a5f..0xe823a92

    // 0xe823a94..0xe823a94
    LIFT-BODY;  // implement basic block 0xe823a94..0xe823a94

    // 0xe823a9a..0xe823ab3
    LIFT-BODY;  // implement basic block 0xe823a9a..0xe823ab3

    // 0xe823ab5..0xe823ac4
    LIFT-BODY;  // implement basic block 0xe823ab5..0xe823ac4

    // 0xe823acc..0xe823b0c
    0xe823aea  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe823acc..0xe823b0c

    // 0xe823b10..0xe823b10
    LIFT-BODY;  // implement basic block 0xe823b10..0xe823b10

    // 0xe823b17..0xe823b21
    LIFT-BODY;  // implement basic block 0xe823b17..0xe823b21

    // 0xe823b23..0xe823b4e
    LIFT-BODY;  // implement basic block 0xe823b23..0xe823b4e

    // 0xe823b50..0xe823b63
    LIFT-BODY;  // implement basic block 0xe823b50..0xe823b63

    // 0xe823b65..0xe823b68
    LIFT-BODY;  // implement basic block 0xe823b65..0xe823b68

    // 0xe823b6a..0xe823b7d
    LIFT-BODY;  // implement basic block 0xe823b6a..0xe823b7d

    // 0xe823b83..0xe823bc9
    LIFT-BODY;  // implement basic block 0xe823b83..0xe823bc9

    // 0xe823bd0..0xe823be1
    LIFT-BODY;  // implement basic block 0xe823bd0..0xe823be1

    // 0xe823be3..0xe823beb
    LIFT-BODY;  // implement basic block 0xe823be3..0xe823beb

    // 0xe823bf0..0xe823c36
    LIFT-BODY;  // implement basic block 0xe823bf0..0xe823c36

    // 0xe823c38..0xe823c40
    LIFT-BODY;  // implement basic block 0xe823c38..0xe823c40

    // 0xe823c46..0xe823c5b
    LIFT-BODY;  // implement basic block 0xe823c46..0xe823c5b

    // 0xe823c5d..0xe823cb8
    0xe823c93  call 0xE835F00                                ; -> sub_e835f00
    LIFT-BODY;  // implement basic block 0xe823c5d..0xe823cb8

    // 0xe823cba..0xe823cd0
    LIFT-BODY;  // implement basic block 0xe823cba..0xe823cd0

    // 0xe823cd7..0xe823d19
    0xe823cf5  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe823cd7..0xe823d19

    // 0xe823d20..0xe823d20
    LIFT-BODY;  // implement basic block 0xe823d20..0xe823d20

    // 0xe823d27..0xe823d31
    LIFT-BODY;  // implement basic block 0xe823d27..0xe823d31

    // 0xe823d33..0xe823d5e
    LIFT-BODY;  // implement basic block 0xe823d33..0xe823d5e

    // 0xe823d60..0xe823d73
    LIFT-BODY;  // implement basic block 0xe823d60..0xe823d73

    // 0xe823d75..0xe823d78
    LIFT-BODY;  // implement basic block 0xe823d75..0xe823d78

    // 0xe823d7a..0xe823d89
    LIFT-BODY;  // implement basic block 0xe823d7a..0xe823d89

    // 0xe823d8f..0xe823dd8
    LIFT-BODY;  // implement basic block 0xe823d8f..0xe823dd8

    // 0xe823ddd..0xe823e56
    0xe823e30  call r10
    LIFT-BODY;  // implement basic block 0xe823ddd..0xe823e56

    // 0xe823e59..0xe823e8f
    LIFT-BODY;  // implement basic block 0xe823e59..0xe823e8f

    // 0xe823e90..0xe823ea6
    LIFT-BODY;  // implement basic block 0xe823e90..0xe823ea6

    // 0xe823eac..0xe823f31
    0xe823ee3  call r10
    0xe823ef5  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe823eac..0xe823f31

    // 0xe823f40..0xe823f62
    LIFT-BODY;  // implement basic block 0xe823f40..0xe823f62

    // 0xe823f67..0xe823f7a
    LIFT-BODY;  // implement basic block 0xe823f67..0xe823f7a

    // 0xe823f80..0xe823fc6
    LIFT-BODY;  // implement basic block 0xe823f80..0xe823fc6

    // 0xe823fd0..0xe823fe1
    LIFT-BODY;  // implement basic block 0xe823fd0..0xe823fe1

    // 0xe823fe3..0xe823feb
    LIFT-BODY;  // implement basic block 0xe823fe3..0xe823feb

    // 0xe823ff0..0xe824036
    LIFT-BODY;  // implement basic block 0xe823ff0..0xe824036

    // 0xe824038..0xe824045
    LIFT-BODY;  // implement basic block 0xe824038..0xe824045

    // 0xe82404a..0xe82405c
    LIFT-BODY;  // implement basic block 0xe82404a..0xe82405c

    // 0xe824062..0xe824084
    LIFT-BODY;  // implement basic block 0xe824062..0xe824084

    // 0xe824086..0xe8240de
    0xe8240b9  call 0xE835F00                                ; -> sub_e835f00
    LIFT-BODY;  // implement basic block 0xe824086..0xe8240de

    // 0xe8240e0..0xe8240f6
    LIFT-BODY;  // implement basic block 0xe8240e0..0xe8240f6

    // 0xe8240fd..0xe82413b
    0xe82411a  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe8240fd..0xe82413b

    // 0xe824140..0xe824140
    LIFT-BODY;  // implement basic block 0xe824140..0xe824140

    // 0xe824147..0xe824151
    LIFT-BODY;  // implement basic block 0xe824147..0xe824151

    // 0xe824153..0xe82417e
    LIFT-BODY;  // implement basic block 0xe824153..0xe82417e

    // 0xe824180..0xe824193
    LIFT-BODY;  // implement basic block 0xe824180..0xe824193

    // 0xe824195..0xe824198
    LIFT-BODY;  // implement basic block 0xe824195..0xe824198

    // 0xe82419a..0xe8241ab
    LIFT-BODY;  // implement basic block 0xe82419a..0xe8241ab

    // 0xe8241b1..0xe8241f7
    LIFT-BODY;  // implement basic block 0xe8241b1..0xe8241f7

    // 0xe824200..0xe824211
    LIFT-BODY;  // implement basic block 0xe824200..0xe824211

    // 0xe824213..0xe82421b
    LIFT-BODY;  // implement basic block 0xe824213..0xe82421b

    // 0xe824220..0xe824266
    LIFT-BODY;  // implement basic block 0xe824220..0xe824266

    // 0xe824268..0xe82426b
    LIFT-BODY;  // implement basic block 0xe824268..0xe82426b

    // 0xe82426d..0xe824270
    LIFT-BODY;  // implement basic block 0xe82426d..0xe824270

    // 0xe824276..0xe82427a
    LIFT-BODY;  // implement basic block 0xe824276..0xe82427a

    // 0xe82427f..0xe824286
    LIFT-BODY;  // implement basic block 0xe82427f..0xe824286

    // 0xe824289..0xe8242ef
    0xe824297  call 0xE83AED0                                ; -> sub_e83aed0
    0xe8242b8  call 0xE83ABB0                                ; -> sub_e83abb0
    0xe8242de  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe824289..0xe8242ef

    // 0xe8242f1..0xe8242fd
    LIFT-BODY;  // implement basic block 0xe8242f1..0xe8242fd

    // 0xe824303..0xe82434d
    LIFT-BODY;  // implement basic block 0xe824303..0xe82434d

    // 0xe824350..0xe824361
    LIFT-BODY;  // implement basic block 0xe824350..0xe824361

    // 0xe824363..0xe82436c
    LIFT-BODY;  // implement basic block 0xe824363..0xe82436c

    // 0xe824370..0xe8243b8
    LIFT-BODY;  // implement basic block 0xe824370..0xe8243b8

    // 0xe8243ba..0xe8243ba
    LIFT-BODY;  // implement basic block 0xe8243ba..0xe8243ba

    // 0xe8243c1..0xe8243c4
    LIFT-BODY;  // implement basic block 0xe8243c1..0xe8243c4

    // 0xe8243c6..0xe8243cc
    LIFT-BODY;  // implement basic block 0xe8243c6..0xe8243cc

    // 0xe8243d3..0xe824420
    0xe824419  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8243d3..0xe824420

    // 0xe824425..0xe824425
    LIFT-BODY;  // implement basic block 0xe824425..0xe824425

    // 0xe824427..0xe824454
    LIFT-BODY;  // implement basic block 0xe824427..0xe824454

    // 0xe82445a..0xe824476
    LIFT-BODY;  // implement basic block 0xe82445a..0xe824476

    // 0xe824478..0xe8244d3
    0xe8244ae  call 0xE835F00                                ; -> sub_e835f00
    LIFT-BODY;  // implement basic block 0xe824478..0xe8244d3

    // 0xe8244d9..0xe8244ef
    LIFT-BODY;  // implement basic block 0xe8244d9..0xe8244ef

    // 0xe8244f6..0xe824539
    0xe824514  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe8244f6..0xe824539

    // 0xe824540..0xe824540
    LIFT-BODY;  // implement basic block 0xe824540..0xe824540

    // 0xe824547..0xe824551
    LIFT-BODY;  // implement basic block 0xe824547..0xe824551

    // 0xe824557..0xe82457d
    LIFT-BODY;  // implement basic block 0xe824557..0xe82457d

    // 0xe824580..0xe824595
    LIFT-BODY;  // implement basic block 0xe824580..0xe824595

    // 0xe824597..0xe82459c
    LIFT-BODY;  // implement basic block 0xe824597..0xe82459c

    // 0xe8245a0..0xe8245a0
    LIFT-BODY;  // implement basic block 0xe8245a0..0xe8245a0

    // 0xe8245a7..0xe8245b1
    LIFT-BODY;  // implement basic block 0xe8245a7..0xe8245b1

    // 0xe8245b7..0xe8245e4
    LIFT-BODY;  // implement basic block 0xe8245b7..0xe8245e4

    // 0xe8245f0..0xe824603
    LIFT-BODY;  // implement basic block 0xe8245f0..0xe824603

    // 0xe824605..0xe824608
    LIFT-BODY;  // implement basic block 0xe824605..0xe824608

    // 0xe82460a..0xe82461d
    LIFT-BODY;  // implement basic block 0xe82460a..0xe82461d

    // 0xe824623..0xe824669
    LIFT-BODY;  // implement basic block 0xe824623..0xe824669

    // 0xe824670..0xe824681
    LIFT-BODY;  // implement basic block 0xe824670..0xe824681

    // 0xe824683..0xe82468b
    LIFT-BODY;  // implement basic block 0xe824683..0xe82468b

    // 0xe824690..0xe8246d6
    LIFT-BODY;  // implement basic block 0xe824690..0xe8246d6

    // 0xe8246d8..0xe8246e0
    LIFT-BODY;  // implement basic block 0xe8246d8..0xe8246e0

    // 0xe8246e2..0xe8246e2
    LIFT-BODY;  // implement basic block 0xe8246e2..0xe8246e2

    // 0xe8246e7..0xe824712
    LIFT-BODY;  // implement basic block 0xe8246e7..0xe824712

    // 0xe824718..0xe824782
    0xe824755  call 0xE83ACE0                                ; -> sub_e83ace0
    LIFT-BODY;  // implement basic block 0xe824718..0xe824782

    // 0xe824790..0xe8247a5
    LIFT-BODY;  // implement basic block 0xe824790..0xe8247a5

    // 0xe8247b0..0xe8247ca
    LIFT-BODY;  // implement basic block 0xe8247b0..0xe8247ca

    // 0xe8247d0..0xe8247e5
    LIFT-BODY;  // implement basic block 0xe8247d0..0xe8247e5

    // 0xe8247e7..0xe8247e7
    LIFT-BODY;  // implement basic block 0xe8247e7..0xe8247e7

    // 0xe8247ea..0xe824833
    0xe824812  call 0xEBCE430                                ; -> sub_ebce430
    0xe824827  call 0xEBCE430                                ; -> sub_ebce430
    LIFT-BODY;  // implement basic block 0xe8247ea..0xe824833

    // 0xe824839..0xe82484e
    LIFT-BODY;  // implement basic block 0xe824839..0xe82484e

    // 0xe824855..0xe824871
    0xe82486b  call 0xBC5F110                                ; -> sub_bc5f110
    LIFT-BODY;  // implement basic block 0xe824855..0xe824871

    // 0xe824880..0xe8248dd
    0xe8248ba  call 0xEBCE390                                ; -> sub_ebce390
    LIFT-BODY;  // implement basic block 0xe824880..0xe8248dd

    // 0xe8248df..0xe8248e9
    LIFT-BODY;  // implement basic block 0xe8248df..0xe8248e9

    // 0xe8248eb..0xe8248eb
    LIFT-BODY;  // implement basic block 0xe8248eb..0xe8248eb

    // 0xe8248f6..0xe8248f6
    LIFT-BODY;  // implement basic block 0xe8248f6..0xe8248f6

    // 0xe8248fd..0xe824922
    0xe82491c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe8248fd..0xe824922

    // 0xe824923..0xe82495b
    LIFT-BODY;  // implement basic block 0xe824923..0xe82495b

    // 0xe824960..0xe824975
    LIFT-BODY;  // implement basic block 0xe824960..0xe824975

    // 0xe82497a..0xe824a52
    0xe824a36  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe82497a..0xe824a52

    // 0xe824a59..0xe824b19
    0xe824a73  call 0xE82DCC0                                ; -> sub_e82dcc0
    LIFT-BODY;  // implement basic block 0xe824a59..0xe824b19

    // 0xe824b20..0xe824b46
    LIFT-BODY;  // implement basic block 0xe824b20..0xe824b46

    // 0xe824b4a..0xe824b5d
    LIFT-BODY;  // implement basic block 0xe824b4a..0xe824b5d

    // 0xe824b63..0xe824c3c
    0xe824c35  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe824b63..0xe824c3c

    // 0xe824c41..0xe824cf7
    0xe824cf0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe824c41..0xe824cf7

    // 0xe824cfc..0xe824d34
    LIFT-BODY;  // implement basic block 0xe824cfc..0xe824d34

    // 0xe824d36..0xe824d9a
    0xe824d93  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe824d36..0xe824d9a

    // 0xe824da0..0xe824dd3
    LIFT-BODY;  // implement basic block 0xe824da0..0xe824dd3

    // 0xe824dd5..0xe824de0
    LIFT-BODY;  // implement basic block 0xe824dd5..0xe824de0

    // 0xe824de4..0xe824dfe
    LIFT-BODY;  // implement basic block 0xe824de4..0xe824dfe

    // 0xe824e01..0xe824e76
    0xe824e72  call r10
    LIFT-BODY;  // implement basic block 0xe824e01..0xe824e76

    // 0xe824e7b..0xe824eab
    LIFT-BODY;  // implement basic block 0xe824e7b..0xe824eab

    // 0xe824eb3..0xe824ee7
    LIFT-BODY;  // implement basic block 0xe824eb3..0xe824ee7

    // 0xe824ee9..0xe824ef4
    LIFT-BODY;  // implement basic block 0xe824ee9..0xe824ef4

    // 0xe824ef8..0xe824f15
    LIFT-BODY;  // implement basic block 0xe824ef8..0xe824f15

    // 0xe824f18..0xe824f87
    0xe824f81  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe824f18..0xe824f87

    // 0xe824f88..0xe824fb9
    LIFT-BODY;  // implement basic block 0xe824f88..0xe824fb9

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

    // 0xe825269..0xe825269
    LIFT-BODY;  // implement basic block 0xe825269..0xe825269

}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_e82326d: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xe82326d, 0xe82d4e3) (rdis dis output, two spaces after address):
#if 0
0xe8233de  call r10
0xe823493  call r10
0xe8234a5  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8235f1  call 0xEBCE430                                ; -> sub_ebce430
0xe823606  call 0xEBCE430                                ; -> sub_ebce430
0xe823658  call 0xBC5F110                                ; -> sub_bc5f110
0xe82378b  call 0xE82D960                                ; -> sub_e82d960
0xe8237cb  call 0xEBCE390                                ; -> sub_ebce390
0xe823833  call r10
0xe823929  call r10
0xe8239e3  call r10
0xe8239f5  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe823aea  call 0xBC5F110                                ; -> sub_bc5f110
0xe823c93  call 0xE835F00                                ; -> sub_e835f00
0xe823cf5  call 0xBC5F110                                ; -> sub_bc5f110
0xe823e30  call r10
0xe823ee3  call r10
0xe823ef5  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8240b9  call 0xE835F00                                ; -> sub_e835f00
0xe82411a  call 0xBC5F110                                ; -> sub_bc5f110
0xe824297  call 0xE83AED0                                ; -> sub_e83aed0
0xe8242b8  call 0xE83ABB0                                ; -> sub_e83abb0
0xe8242de  call 0xBC5F110                                ; -> sub_bc5f110
0xe824419  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8244ae  call 0xE835F00                                ; -> sub_e835f00
0xe824514  call 0xBC5F110                                ; -> sub_bc5f110
0xe824755  call 0xE83ACE0                                ; -> sub_e83ace0
0xe824812  call 0xEBCE430                                ; -> sub_ebce430
0xe824827  call 0xEBCE430                                ; -> sub_ebce430
0xe82486b  call 0xBC5F110                                ; -> sub_bc5f110
0xe8248ba  call 0xEBCE390                                ; -> sub_ebce390
0xe82491c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe824a36  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe824a73  call 0xE82DCC0                                ; -> sub_e82dcc0
0xe824c35  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe824cf0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe824d93  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe824e72  call r10
0xe824f81  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe8250c2  call 0xE82D960                                ; -> sub_e82d960
0xe8250fb  call 0xEBCE390                                ; -> sub_ebce390
0xe825162  call r10
0xe825174  call 0xE82DCC0                                ; -> sub_e82dcc0
0xe825260  call r10
#endif

// Calls out of lifted code:
//   call r10 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_ebce430 (0xebce430, boundary) - call 0xEBCE430                                ; -> sub_ebce430
//   sub_ebce430 (0xebce430, boundary) - call 0xEBCE430                                ; -> sub_ebce430
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_e82d960 (0xe82d960, lift set) - call 0xE82D960                                ; -> sub_e82d960
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   call r10 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_e835f00 (0xe835f00, lift set) - call 0xE835F00                                ; -> sub_e835f00
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   call r10 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_e835f00 (0xe835f00, lift set) - call 0xE835F00                                ; -> sub_e835f00
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_e83aed0 (0xe83aed0, lift set) - call 0xE83AED0                                ; -> sub_e83aed0
//   sub_e83abb0 (0xe83abb0, lift set) - call 0xE83ABB0                                ; -> sub_e83abb0
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e835f00 (0xe835f00, lift set) - call 0xE835F00                                ; -> sub_e835f00
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_e83ace0 (0xe83ace0, lift set) - call 0xE83ACE0                                ; -> sub_e83ace0
//   sub_ebce430 (0xebce430, boundary) - call 0xEBCE430                                ; -> sub_ebce430
//   sub_ebce430 (0xebce430, boundary) - call 0xEBCE430                                ; -> sub_ebce430
//   sub_bc5f110 (0xbc5f110, lift set) - call 0xBC5F110                                ; -> sub_bc5f110
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e82dcc0 (0xe82dcc0, lift set) - call 0xE82DCC0                                ; -> sub_e82dcc0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call r10 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e82d960 (0xe82d960, lift set) - call 0xE82D960                                ; -> sub_e82d960
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   call r10 (indirect, boundary via data slot)
//   sub_e82dcc0 (0xe82dcc0, lift set) - call 0xE82DCC0                                ; -> sub_e82dcc0
//   call r10 (indirect, boundary via data slot)
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv

LIFT_FN(sub_e82326d, "sub_e82326d", 0xe82326d, sub_e82326d, nullptr);

} // namespace native::d3d12