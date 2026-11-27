// LIFT 0xe905ce0 size 0x19 1.26.62.01 Frame renderer lambda
#include "client/features/render/native/dragon/sub_e905ce0.h"

#include "client/features/render/native/Lift.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

static_assert(sizeof(void*) == 8, "sub_e905ce0: x64 ABI, pointer-sized address space");
static_assert(sizeof(bool (*)(void*, void*)) == 8, "sub_e905ce0: x64 function pointer is 8 bytes");

namespace native {

// Best-effort declaration of the callee at 0xeec6eb0 (an IAT import thunk,
// 0xeec6eb0  jmp qword ptr [0xF9A8A90]). It is absent from
// docs/data/native_functions.tsv and docs/data/native_boundary.tsv, so it is not a
// lifted function and not a boundary wrapper; this declaration only expresses the
// call observed at 0xe905cea. Its target/signature are unresolved. Observed
// signature from the call site: rcx=a1, rdx=a2, r8d=0x66 -> eax (tested for == 0
// by the caller).
std::int32_t sub_eec6eb0(void* a1, void* a2, std::uint32_t a3);

bool sub_e905ce0(void* a1, void* a2) {
    // 0xe905ce0..0xe905cf9: sub rsp,0x28; mov r8d,0x66; call 0xEEC6EB0;
    //   test eax,eax; sete al; add rsp,0x28; ret
    //   a1=RCX, a2=RDX, callee's 3rd arg R8D=0x66; return AL = (eax == 0).
    return sub_eec6eb0(a1, a2, 0x66u) == 0;   // 0xe905cea  call 0xEEC6EB0 ; 0xe905cef  test eax,eax ; 0xe905cf1  sete al
}

LIFT_FN(e905ce0, "sub_e905ce0", 0xE905CE0, sub_e905ce0, nullptr);

} // namespace native

// Verbatim instructions of the function (rdis dis 0xe905ce0 0x19), for liftcheck
// verify_oc. Every line matches rdis output for its address.
#if 0
0xE905CE0  sub rsp,0x28
0xE905CE4  mov r8d,0x66
0xE905CEA  call 0xEEC6EB0
0xE905CEF  test eax,eax
0xE905CF1  sete al
0xE905CF4  add rsp,0x28
0xE905CF8  ret
#endif
