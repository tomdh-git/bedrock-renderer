// LIFT 0xaa3c0 size 0x8 1.26.62.01 sub_aa3c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_aa3c0.h"

namespace native {

// Verbatim instructions of [0xaa3c0, 0xaa3c8) (rdis dis 0xaa3c0 8):
#if 0
0xaa3c0  lea rax,[0x128C1588]
0xaa3c7  ret
#endif

// Layout assertions (also in sub_aa3c0.h; repeated here so the source file is
// self-contained for liftcheck).
static_assert(sizeof(void*) == 8, "sub_aa3c0: return value is an 8-byte pointer in RAX (x64 Microsoft ABI)");

// sub_aa3c0() -> void*
//   0xaa3c0  lea rax,[0x128C1588]            ; [data_128c1588]
//   0xaa3c7  ret
// The function takes no arguments, reads nothing, writes nothing, and returns
// the address of the game global data_128c1588 (the address loaded by the lea,
// RVA 0x128C1588) in RAX. The global's pointee type is not recoverable from
// this function alone — exactly one .text reference to 0x128C1588 exists, the
// lea at 0xaa3c3 itself [V] — so it is modeled as an opaque object and its
// address is returned: exactly what `lea rax,[0x128C1588]; ret` computes, one
// address computation, no load, no call.
extern "C" {
struct data_128c1588;
extern struct data_128c1588 data_128c1588;
}

void* sub_aa3c0(void) {
// 0xaa3c0..0xaa3c8: lea rax,[0x128C1588] then ret — address of the global in
// RAX, no memory read, no write, no call [V].
    return reinterpret_cast<void*>(&data_128c1588);
    // 0xaa3c0  lea rax,[0x128C1588]            ; [data_128c1588]
    // 0xaa3c7  ret
}

LIFT_FN(sub_aa3c0, "sub_aa3c0", 0xaa3c0, ::native::sub_aa3c0, nullptr);

} // namespace native
