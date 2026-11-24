// LIFT 0xe869cb0 size 0x2f4 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e869cb0.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

extern "C" void sub_e935700();
extern "C" void sub_eec6ec0();

} // namespace

extern "C" void sub_e869cb0();

void sub_e869cb0() {
    // 0xe869cb0..0xe869d19
    // 0xe869d1d..0xe869d20
    // 0xe869d23..0xe869d33
    // 0xe869d34..0xe869d76
    // 0xe869d78..0xe869d82
    // 0xe869d87..0xe869da5
    // 0xe869da7..0xe869dc5
    0xe869dbc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    // 0xe869dcb..0xe869dda
    // 0xe869ddc..0xe869dfd
    0xe869dee  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    // 0xe869e00..0xe869e03
    // 0xe869e07..0xe869e7f
    0xe869e42  call 0xEEC6EC0                                ; -> sub_eec6ec0
    0xe869e79  call 0xA0850                                  ; -> sub_a0850
    // 0xe869e81..0xe869e96
    // 0xe869e9a..0xe869ec9
    // 0xe869ece..0xe869f1b
    // 0xe869f1e..0xe869f1e
    0xe869f1e  call 0xE935700                                ; -> sub_e935700
    // 0xe869f23..0xe869f52
    // 0xe869f55..0xe869f5d
    0xe869f58  call 0xE935700                                ; -> sub_e935700
    // 0xe869f62..0xe869f70
    0xe869f68  call 0x9BC830                                 ; -> sub_9bc830
    // 0xe869f75..0xe869f80
    0xe869f79  call 0x9BC830                                 ; -> sub_9bc830
    // 0xe869f85..0xe869f85
    0xe869f85  call 0x75720                                  ; -> sub_75720
    // 0xe869f8a..0xe869fa3
    0xe869f9d  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
}

static_assert(true, "sub_e869cb0 layout");

LIFT_FN(sub_e869cb0, "sub_e869cb0", 0xe869cb0, sub_e869cb0, nullptr);

} // namespace native::d3d12