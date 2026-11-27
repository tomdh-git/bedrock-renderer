// LIFT 0x6758b90 size 0xdd 1.26.62.01 sub_6758b90
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_6758b90.h"
#include "client/features/render/native/helpers/sub_a784c0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Layout assertions for every field read or written (mirrored from the header so
// liftcheck sees them in the compiled source too).
static_assert(offsetof(native::helpers::sub_6758b90_rcx, vtable) == 0x0, "sub_0x6758b90 rcx+0x0 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner08) == 0x8, "sub_0x6758b90 rcx+0x8 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner10) == 0x10, "sub_0x6758b90 rcx+0x10 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner18) == 0x18, "sub_0x6758b90 rcx+0x18 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner20) == 0x20, "sub_0x6758b90 rcx+0x20 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner28) == 0x28, "sub_0x6758b90 rcx+0x28 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner30) == 0x30, "sub_0x6758b90 rcx+0x30 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner38) == 0x38, "sub_0x6758b90 rcx+0x38 field");
static_assert(offsetof(native::helpers::sub_6758b90_rcx, owner40) == 0x40, "sub_0x6758b90 rcx+0x40 field");
static_assert(sizeof(native::helpers::sub_6758b90_rcx) >= 0x48, "sub_0x6758b90 rcx sizeof lower bound");
static_assert(offsetof(native::helpers::sub_6758b90_rax, active) == 0x10, "sub_0x6758b90 rax+0x10 field");
static_assert(sizeof(native::helpers::sub_6758b90_rax) >= 0x11, "sub_0x6758b90 rax sizeof lower bound");
static_assert(offsetof(native::helpers::sub_6758b90_rbp, cookie) == 0x0, "sub_0x6758b90 rbp+0x0 field");
static_assert(sizeof(native::helpers::sub_6758b90_rbp) >= 0x8, "sub_0x6758b90 rbp sizeof lower bound");
static_assert(offsetof(native::helpers::sub_6758b90_rsp, frame) == 0x20, "sub_0x6758b90 rsp+0x20 field");
static_assert(sizeof(native::helpers::sub_6758b90_rsp) >= 0x21, "sub_0x6758b90 rsp sizeof lower bound");

namespace native::helpers {

LIFT_FN(sub_6758b90, "sub_6758b90", 0x6758b90, sub_6758b90, nullptr);

// Verbatim call instructions from the disassembly of [0x6758b90, 0x6758c6d) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x6758bdb  call 0xA784C0
0x6758bec  call 0xA784C0
0x6758bfd  call 0xA784C0
0x6758c0e  call 0xA784C0
0x6758c1f  call 0xA784C0
0x6758c30  call 0xA784C0
0x6758c41  call 0xA784C0
0x6758c52  call 0xA784C0
#endif

// The single callee is the lifted node factory: it takes the address of the
// +0x30 subobject in RCX and returns the node payload pointer in RAX.

// Ranges: every instruction of [0x6758b90, 0x6758c6d) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

void* sub_6758b90(sub_6758b90_rcx* self) {
    // 0x6758b90..0x6758c6d: basic block 0
    // 0x6758b90  push rbp
    // 0x6758b91  push r15
    // 0x6758b93  push r14
    // 0x6758b95  push r13
    // 0x6758b97  push r12
    // 0x6758b99  push rsi
    // 0x6758b9a  push rdi
    // 0x6758b9b  push rbx
    // 0x6758b9c  sub rsp,0x28
    // 0x6758ba0  lea rbp,[rsp+0x20]
    // 0x6758ba5  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x6758bad  lea rax,[0xF2BE800]
    // 0x6758bb4  mov [rcx],rax
    // 0x6758bb7  mov rsi,[rcx+8]
    // 0x6758bbb  mov rdi,[rcx+0x10]
    // 0x6758bbf  mov rbx,[rcx+0x18]
    // 0x6758bc3  mov r14,[rcx+0x20]
    // 0x6758bc7  mov r15,[rcx+0x28]
    // 0x6758bcb  mov r12,[rcx+0x30]
    // 0x6758bcf  mov r13,[rcx+0x38]
    // 0x6758bd3  mov rcx,[rcx+0x40]
    // 0x6758bd7  add rcx,0x30
    // 0x6758bdb  call 0xA784C0
    // 0x6758be0  nop
    // 0x6758be1  mov byte ptr [rax+0x10],0
    // 0x6758be5  add r13,0x30
    // 0x6758be9  mov rcx,r13
    // 0x6758bec  call 0xA784C0
    // 0x6758bf1  nop
    // 0x6758bf2  mov byte ptr [rax+0x10],0
    // 0x6758bf6  add r12,0x30
    // 0x6758bfa  mov rcx,r12
    // 0x6758bfd  call 0xA784C0
    // 0x6758c02  nop
    // 0x6758c03  mov byte ptr [rax+0x10],0
    // 0x6758c07  add r15,0x30
    // 0x6758c0b  mov rcx,r15
    // 0x6758c0e  call 0xA784C0
    // 0x6758c13  nop
    // 0x6758c14  mov byte ptr [rax+0x10],0
    // 0x6758c18  add r14,0x30
    // 0x6758c1c  mov rcx,r14
    // 0x6758c1f  call 0xA784C0
    // 0x6758c24  nop
    // 0x6758c25  mov byte ptr [rax+0x10],0
    // 0x6758c29  add rbx,0x30
    // 0x6758c2d  mov rcx,rbx
    // 0x6758c30  call 0xA784C0
    // 0x6758c35  nop
    // 0x6758c36  mov byte ptr [rax+0x10],0
    // 0x6758c3a  add rdi,0x30
    // 0x6758c3e  mov rcx,rdi
    // 0x6758c41  call 0xA784C0
    // 0x6758c46  nop
    // 0x6758c47  mov byte ptr [rax+0x10],0
    // 0x6758c4b  add rsi,0x30
    // 0x6758c4f  mov rcx,rsi
    // 0x6758c52  call 0xA784C0
    // 0x6758c57  nop
    // 0x6758c58  mov byte ptr [rax+0x10],0
    // 0x6758c5c  add rsp,0x28
    // 0x6758c60  pop rbx
    // 0x6758c61  pop rdi
    // 0x6758c62  pop rsi
    // 0x6758c63  pop r12
    // 0x6758c65  pop r13
    // 0x6758c67  pop r14
    // 0x6758c69  pop r15
    // 0x6758c6b  pop rbp
    // 0x6758c6c  ret
    // -> (fall-through / ret / end)

    // 0x6758bad..0x6758bb4: the static table address is written to this+0x00.
    self->vtable = reinterpret_cast<void*>(static_cast<std::uintptr_t>(0xF2BE800u));

    // 0x6758bb7..0x6758bd3: all eight owner pointers are loaded before any call.
    void* const owner08 = self->owner08;   // rsi
    void* const owner10 = self->owner10;   // rdi
    void* const owner18 = self->owner18;   // rbx
    void* const owner20 = self->owner20;   // r14
    void* const owner28 = self->owner28;   // r15
    void* const owner30 = self->owner30;   // r12
    void* const owner38 = self->owner38;   // r13
    void* const owner40 = self->owner40;   // rcx

    sub_6758b90_rax* node;

    // 0x6758bd7..0x6758be1: owner40 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner40) + 0x30));
    node->active = 0;

    // 0x6758be5..0x6758bf2: owner38 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner38) + 0x30));
    node->active = 0;

    // 0x6758bf6..0x6758c03: owner30 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner30) + 0x30));
    node->active = 0;

    // 0x6758c07..0x6758c14: owner28 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner28) + 0x30));
    node->active = 0;

    // 0x6758c18..0x6758c25: owner20 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner20) + 0x30));
    node->active = 0;

    // 0x6758c29..0x6758c36: owner18 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner18) + 0x30));
    node->active = 0;

    // 0x6758c3a..0x6758c47: owner10 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner10) + 0x30));
    node->active = 0;

    // 0x6758c4b..0x6758c58: owner08 + 0x30 -> sub_a784c0, clear payload byte +0x10.
    node = static_cast<sub_6758b90_rax*>(sub_a784c0(static_cast<std::uint8_t*>(owner08) + 0x30));
    node->active = 0;

    // 0x6758c5c..0x6758c6c: epilogue; RAX still holds the last payload pointer.
    return node;
}

} // namespace native::helpers
