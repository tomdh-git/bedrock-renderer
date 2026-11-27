// LIFT 0xebdb760 size 0x19 1.26.62.01 sub_ebdb760
#include "sub_ebdb760.h"

#include "client/features/render/native/Lift.h"

#if 0
// Verbatim instructions of sub_ebdb760 (matches the rdis output for 0xebdb760,
// [0xebdb760, 0xebdb779)):
0xebdb760  sub rsp,0x28
0xebdb764  lea rcx,[rsp+0x30]
0xebdb769  call qword ptr [0xF9A7CA0]
0xebdb76f  mov rax,[rsp+0x30]
0xebdb774  add rsp,0x28
0xebdb778  ret
#endif

namespace native {

// Lifted body of sub_ebdb760 (0xebdb760, size 0x19, 1.26.62.01).
//
// A leaf wrapper: no register arguments on entry (RCX is overwritten by the lea
// before it is read), return value in RAX. It calls the loader-resolved function
// in data slot 0xF9A7CA0 with RCX = &buf, then returns the qword the callee wrote
// there; the callee's own return value is discarded.
//
//   0xebdb760  sub rsp,0x28                                   (0xebdb760..0xebdb764)
//   0xebdb764  lea rcx,[rsp+0x30]                             (0xebdb764..0xebdb769)
//   0xebdb769  call qword ptr [0xF9A7CA0]   ; [data_f9a7ca0] (0xebdb769..0xebdb76f)
//   0xebdb76f  mov rax,[rsp+0x30]                             (0xebdb76f..0xebdb774)
//   0xebdb774  add rsp,0x28                                   (0xebdb774..0xebdb778)
//   0xebdb778  ret                                            (0xebdb778..0xebdb779)
//
// The int3 padding at 0xebdb779..0xebdb780 lies past the 0x19-byte function span
// [V: rdis dis 0xebdb760 0x19].
uint64_t sub_ebdb760_lifted(void) {
    static_assert(sizeof(void*) == 8, "sub_ebdb760: x64 ABI, 8-byte return value in RAX");
    static_assert(sizeof(uint64_t) == 8, "sub_ebdb760: returned value is 64 bits");

    // 0xebdb760..0xebdb764:  sub rsp,0x28   ; 32 bytes of stack space [0xebdb760  sub rsp,0x28]
    // 0xebdb764..0xebdb769:  lea rcx,[rsp+0x30]   ; RCX = &buf, the callee's out argument [0xebdb764  lea rcx,[rsp+0x30]]
    uint64_t buf = 0;
    // 0xebdb769..0xebdb76f:  call qword ptr [0xF9A7CA0]   ; indirect call through loader-resolved data slot 0xF9A7CA0, buf filled via RCX [0xebdb769  call qword ptr [0xF9A7CA0]]
    Ebdb760Callee fn = reinterpret_cast<Ebdb760Callee>(
        *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7CA0ull));
    fn(&buf);
    // 0xebdb76f..0xebdb774:  mov rax,[rsp+0x30]   ; return the qword the callee wrote [0xebdb76f  mov rax,[rsp+0x30]]
    // 0xebdb774..0xebdb778:  add rsp,0x28   ; restore stack [0xebdb774  add rsp,0x28]
    // 0xebdb778..0xebdb779:  ret   ; RAX = buf [0xebdb778  ret]
    return buf;
}

} // namespace native

LIFT_FN(sub_ebdb760, "sub_ebdb760", 0xEBDB760, sub_ebdb760_lifted, nullptr);
