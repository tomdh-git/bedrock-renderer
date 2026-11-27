// LIFT 0x67cab00 size 0xce 1.26.62.01 sub_67cab00
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67cab00.h"
#include "client/features/render/native/helpers/sub_a784c0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Layout assertions for every field read or written (mirrored from the header).
static_assert(offsetof(native::helpers::sub_67cab00_rcx, field_0x00) == 0x0, "sub_0x67cab00 rcx+0x0 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, frameRenderer) == 0x8, "sub_0x67cab00 rcx+0x08 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, field_0x10) == 0x10, "sub_0x67cab00 rcx+0x10 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, field_0x18) == 0x18, "sub_0x67cab00 rcx+0x18 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, field_0x20) == 0x20, "sub_0x67cab00 rcx+0x20 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, field_0x28) == 0x28, "sub_0x67cab00 rcx+0x28 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, field_0x30) == 0x30, "sub_0x67cab00 rcx+0x30 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, field_0x38) == 0x38, "sub_0x67cab00 rcx+0x38 field");
static_assert(offsetof(native::helpers::sub_67cab00_rcx, shouldRender) == 0x40, "sub_0x67cab00 rcx+0x40 field");
static_assert(sizeof(native::helpers::sub_67cab00_rcx) >= 0x41, "sub_0x67cab00 rcx sizeof lower bound");
static_assert(offsetof(native::helpers::sub_67cab00_rax, f10) == 0x10, "sub_0x67cab00 rax+0x10 field");
static_assert(sizeof(native::helpers::sub_67cab00_rax) >= 0x11, "sub_0x67cab00 rax sizeof lower bound");
static_assert(offsetof(native::helpers::sub_67cab00_rsp, f30) == 0x30, "sub_0x67cab00 rsp+0x30 field");
static_assert(sizeof(native::helpers::sub_67cab00_rsp) >= 0x31, "sub_0x67cab00 rsp sizeof lower bound");

namespace native::helpers {

LIFT_FN(sub_67cab00, "sub_67cab00", 0x67cab00, sub_67cab00, nullptr);

// Verbatim call instructions from the disassembly of [0x67cab00, 0x67cabce) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x67cab4f  call 0xA784C0
0x67cab60  call 0xA784C0
0x67cab71  call 0xA784C0
0x67cab82  call 0xA784C0
0x67cab93  call 0xA784C0
0x67caba4  call 0xA784C0
0x67cabb5  call 0xA784C0
#endif

// Ranges: every instruction of [0x67cab00, 0x67cabce) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_67cab00(void* self) {
    auto* const s = reinterpret_cast<sub_67cab00_rcx*>(self);

    // 0x67cab00..0x67cab2f: basic block 0
    // 0x67cab00  push rbp
    // 0x67cab01  push r15
    // 0x67cab03  push r14
    // 0x67cab05  push r12
    // 0x67cab07  push rsi
    // 0x67cab08  push rdi
    // 0x67cab09  push rbx
    // 0x67cab0a  sub rsp,0x30
    // 0x67cab0e  lea rbp,[rsp+0x30]
    // 0x67cab13  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0x67cab1b  lea rax,[0xF2BEBD0]                           ; [data_f2bebd0]
    // 0x67cab22  mov [rcx],rax                                 ; W a0+0x0
    // 0x67cab25  cmp byte ptr [rcx+0x40],1                     ; R a0+0x40
    // 0x67cab29  jne 0x67CABBF                                 ; -> loc_67cabbf
    // -> if *u8(a0+0x40) != 0x1 goto L_0x67cabbf
    // -> if *u8(a0+0x40) == 0x1 goto L_0x67cab2f
    *reinterpret_cast<void**>(self) = reinterpret_cast<void*>(0xF2BEBD0ULL);
    if (s->shouldRender != 0x1u) {
        // 0x67cabbf..0x67cabce: basic block 2
        // 0x67cabbf  add rsp,0x30
        // 0x67cabc3  pop rbx
        // 0x67cabc4  pop rdi
        // 0x67cabc5  pop rsi
        // 0x67cabc6  pop r12
        // 0x67cabc8  pop r14
        // 0x67cabca  pop r15
        // 0x67cabcc  pop rbp
        // 0x67cabcd  ret
        // -> (fall-through / ret / end)
        return 0;
    }

    // 0x67cab2f..0x67cabbb: basic block 1
    // 0x67cab2f  mov rsi,[rcx+8]                               ; R a0+0x8
    // 0x67cab33  mov rdi,[rcx+0x10]                            ; R a0+0x10
    // 0x67cab37  mov rbx,[rcx+0x18]                            ; R a0+0x18
    // 0x67cab3b  mov r14,[rcx+0x20]                            ; R a0+0x20
    // 0x67cab3f  mov r15,[rcx+0x28]                            ; R a0+0x28
    // 0x67cab43  mov r12,[rcx+0x30]                            ; R a0+0x30
    // 0x67cab47  mov rcx,[rcx+0x38]                            ; R a0+0x38
    // 0x67cab4b  add rcx,0x30
    // 0x67cab4f  call 0xA784C0                                 ; -> sub_a784c0
    // 0x67cab54  nop
    // 0x67cab55  mov byte ptr [rax+0x10],0                     ; W ret@a784c0+0x10
    // 0x67cab59  add r12,0x30
    // 0x67cab5d  mov rcx,r12
    // 0x67cab60  call 0xA784C0                                 ; -> sub_a784c0
    // 0x67cab65  nop
    // 0x67cab66  mov byte ptr [rax+0x10],0                     ; W ret@a784c0+0x10
    // 0x67cab6a  add r15,0x30
    // 0x67cab6e  mov rcx,r15
    // 0x67cab71  call 0xA784C0                                 ; -> sub_a784c0
    // 0x67cab76  nop
    // 0x67cab77  mov byte ptr [rax+0x10],0                     ; W ret@a784c0+0x10
    // 0x67cab7b  add r14,0x30
    // 0x67cab7f  mov rcx,r14
    // 0x67cab82  call 0xA784C0                                 ; -> sub_a784c0
    // 0x67cab87  nop
    // 0x67cab88  mov byte ptr [rax+0x10],0                     ; W ret@a784c0+0x10
    // 0x67cab8c  add rbx,0x30
    // 0x67cab90  mov rcx,rbx
    // 0x67cab93  call 0xA784C0                                 ; -> sub_a784c0
    // 0x67cab98  nop
    // 0x67cab99  mov byte ptr [rax+0x10],0                     ; W ret@a784c0+0x10
    // 0x67cab9d  add rdi,0x30
    // 0x67caba1  mov rcx,rdi
    // 0x67caba4  call 0xA784C0                                 ; -> sub_a784c0
    // 0x67caba9  nop
    // 0x67cabaa  mov byte ptr [rax+0x10],0                     ; W ret@a784c0+0x10
    // 0x67cabae  add rsi,0x30
    // 0x67cabb2  mov rcx,rsi
    // 0x67cabb5  call 0xA784C0                                 ; -> sub_a784c0
    // 0x67cabba  nop
    // 0x67cabbb  mov byte ptr [rax+0x10],0                     ; W ret@a784c0+0x10
    // -> if fallthrough goto L_0x67cabbf

    void* rsi = s->frameRenderer;
    void* rdi = s->field_0x10;
    void* rbx = s->field_0x18;
    void* r14 = s->field_0x20;
    void* r15 = s->field_0x28;
    void* r12 = s->field_0x30;
    void* rcx = reinterpret_cast<std::uint8_t*>(s->field_0x38) + 0x30;

    auto* result = sub_a784c0(rcx);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(result) + 0x10) = 0x0;
    r12 = reinterpret_cast<std::uint8_t*>(r12) + 0x30;
    rcx = r12;
    result = sub_a784c0(rcx);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(result) + 0x10) = 0x0;
    r15 = reinterpret_cast<std::uint8_t*>(r15) + 0x30;
    rcx = r15;
    result = sub_a784c0(rcx);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(result) + 0x10) = 0x0;
    r14 = reinterpret_cast<std::uint8_t*>(r14) + 0x30;
    rcx = r14;
    result = sub_a784c0(rcx);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(result) + 0x10) = 0x0;
    rbx = reinterpret_cast<std::uint8_t*>(rbx) + 0x30;
    rcx = rbx;
    result = sub_a784c0(rcx);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(result) + 0x10) = 0x0;
    rdi = reinterpret_cast<std::uint8_t*>(rdi) + 0x30;
    rcx = rdi;
    result = sub_a784c0(rcx);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(result) + 0x10) = 0x0;
    rsi = reinterpret_cast<std::uint8_t*>(rsi) + 0x30;
    rcx = rsi;
    result = sub_a784c0(rcx);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(result) + 0x10) = 0x0;

    return 0;
}

} // namespace native::helpers
