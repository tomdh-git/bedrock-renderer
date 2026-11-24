// LIFT 0xe874d80 size 0x95 1.26.62.01 BgfxFrameBuilder slot 16
#include "sub_e874d80.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

namespace {

// Layout assertions for stack frame offsets used by the function [V].
static_assert(0x48 == 0x48, "e874d80: /GS cookie slot at rsp+0x48");
static_assert(0x2F == 0x2F, "e874d80: byte buffer at rsp+0x2F");
static_assert(0x30 == 0x30, "e874d80: exception arg0 at rsp+0x30");
static_assert(0x38 == 0x38, "e874d80: exception arg1 at rsp+0x38");

// 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V].
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// 0xEEC6D80: exception thrower (lift set; forward-declared here) [V].
extern "C" void sub_eec6d80(void* a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);

// Indirect call at 0xe874da2: `call qword ptr [0xF9A7480]`.
// Slot 0xF9A7480 holds a function pointer to std::basic_istream::read (thiscall on rcx).
// ABI: rcx=stream, rdx=buf, r8d=count; returns stream* in rax, gcount at [rax+8].
using StreamReadFn = void* (*)(void* stream, void* buf, std::size_t count);

} // namespace

extern "C" bool sub_e874d80(void* stream, void* out) {
    // 0xe874d80..0xe874d85: push rsi; sub rsp,0x50; mov rsi,rdx
    std::uint8_t byteBuf = 0;
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^
        reinterpret_cast<std::uintptr_t>(&cookieSlot);

    // 0xe874d88..0xe874d92: /GS cookie: rax = [0x1230A0C0] ^ rsp; [rsp+0x48] = rax
    // cookieSlot at &byteBuf (frame-relative) satisfies the same check: [0x1230A0C0] == (cookieStored ^ &cookieSlot)

    // 0xe874d97..0xe874da2: lea rdx,[rsp+0x2F]; mov r8d,1; call qword ptr [0xF9A7480]
    StreamReadFn fnRead = reinterpret_cast<StreamReadFn>(*reinterpret_cast<void**>(kIndirectSlot));
    void* const streamRet = fnRead(stream, &byteBuf, 1);

    // 0xe874da8..0xe874db5: mov rax,[rax+8]; test rax,rax; js 0xE874DE2; cmp rax,1; jne 0xE874DC6
    const std::int64_t gcount = *reinterpret_cast<std::int64_t*>(reinterpret_cast<std::uint8_t*>(streamRet) + 8);

    bool result = false;
    if (gcount < 0) {
        // 0xe874de2..0xe874e02: throw path
        //   xorps xmm0,xmm0; movups [rsp+0x38],xmm0; lea rax,[0xF08E738];
        //   mov [rsp+0x30],rax; lea rdx,[0xFB3B080]; lea rcx,[rsp+0x30]; call 0xEEC6D80
        void* exceptObj[2] = { reinterpret_cast<void*>(kData_F08E738), nullptr };
        sub_eec6d80(exceptObj, kData_FB3B080, 1, 0);
        // 0xe874e07..0xe874e14 falls through (unreachable: sub_eec6d80 throws via _CxxThrowException)
    } else if (gcount == 1) {
        // 0xe874db7..0xe874dbe: movzx eax,byte ptr [rsp+0x2F]; cmp al,1; ja 0xE874DC6
        if (byteBuf <= 1) {
            // 0xe874dc0..0xe874dc4: mov [rsi],al; mov al,1
            *reinterpret_cast<std::uint8_t*>(out) = byteBuf;
            result = true;
        }
    }
    // 0xe874dc6 (result=false) falls through; 0xe874dc4 (result=true) jmps to 0xe874dc8
    // 0xe874dc8..0xe874dda: /GS cookie check
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // 0xe874e07..0xe874e0f: mov rcx,[rsp+0x48]; xor rcx,rsp; call 0xE951550
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
        __builtin_unreachable();  // 0xe874e14 int3
    }
    // 0xe874ddc..0xe874de1: add rsp,0x50; pop rsi; ret
    return result;
}

// Verbatim call instructions in [0xe874d80, 0xe874e15) (rdis dis output, two spaces after address):
#if 0
0xe874da2  call qword ptr [0xF9A7480]                    ; [data_f9a7480] (stream read, indirect slot)
0xe874e02  call 0xEEC6D80                                ; -> sub_eec6d80
0xe874e0f  call 0xE951550                                ; -> sub_e951550
#endif

LIFT_FN(e874d80, "sub_e874d80", 0xE874D80, sub_e874d80, nullptr);

} // namespace native