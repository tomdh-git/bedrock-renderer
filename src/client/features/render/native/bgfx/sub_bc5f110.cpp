// LIFT 0xbc5f110 size 0x121 1.26.62.01 RendererContextD3D12 base slot 59
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc5f110.h"
#include "client/features/render/native/helpers/sub_ebcf430.h"

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <malloc.h>

namespace native::bgfx {

static_assert(offsetof(SubBc5f110Frame, va_list_ptr) == 0x0000, "sub_bc5f110: va_list pointer at RBP-0x78");
static_assert(offsetof(SubBc5f110Frame, buffer) == 0x0008, "sub_bc5f110: format buffer at RBP-0x70");
static_assert(offsetof(SubBc5f110Frame, cookie) == 0x2008, "sub_bc5f110: stack cookie at RBP+0x1F90");
static_assert(offsetof(SubBc5f110Frame, vararg_r8) == 0x2048, "sub_bc5f110: R8 save slot at RBP+0x1FD0");
static_assert(offsetof(SubBc5f110Frame, vararg_r9) == 0x2050, "sub_bc5f110: R9 save slot at RBP+0x1FD8");
static_assert(sizeof(SubBc5f110Frame) == 0x2058, "sub_bc5f110: frame ends after the R9 save slot");

// Boundary callees (docs/data/native_boundary.tsv: class crt). Declared with the
// x64 Microsoft ABI they are entered with, exactly like the call sites set them up.
extern "C" void sub_e951550(void* cookie);                 // 0xe951550 __security_check_cookie
extern "C" void sub_ebce470(const char* fmt, void* ap);    // 0xebce470 format + fail-fast helper

// 0xbc5f110 (size 0x121): format a variadic message into a 0x2000-byte stack
// buffer and hand it to the logger object's vtable slot 1. When the logger
// pointer at 0x12ADF808 is null, the message goes to sub_ebce470 and the
// loader-resolved terminate pointer in slot 0xF9A8CB0 is called instead.
extern "C" void sub_bc5f110(std::int32_t level, const char* fmt, std::uintptr_t varg1, std::uintptr_t varg2) {
    // 0xbc5f110..0xbc5f13a
    // prologue: push rbp/rsi/rdi/rbx, `mov eax,0x2018; call 0xE9E7970; sub rsp,rax`
    // (__chkstk stack probe, 0x2018 bytes), `lea rbp,[rsp+0x80]`, RDX (fmt) -> RDI,
    // R8/R9 vararg spill to RBP+0x1FD0/0x1FD8.
    SubBc5f110Frame frame;
    // 0xbc5f12c..0xbc5f133  mov [rbp+0x1FD0],r8 ; mov [rbp+0x1FD8],r9  (spill register varargs)
    // 0xbc5f14b..0xbc5f152  lea rax,[rbp+0x1FD0]; [rbp-0x78] = rax        (va_list pointer)
    std::uintptr_t vaArgs[2] = {varg1, varg2};              // contiguous {R8, R9} block
    void* vaArgsPtr = vaArgs;

    // 0xbc5f13a..0xbc5f156
    // rax = [0x1230A0C0]; rax ^= rbp; [rbp+0x1F90] = rax; rax = &[rbp+0x1FD0]; [rbp-0x78] = rax
    frame.cookie = *reinterpret_cast<std::uintptr_t*>(kSubBc5f110CookieGlobal) ^ reinterpret_cast<std::uintptr_t>(&frame);
    frame.va_list_ptr = vaArgsPtr;

    // 0xbc5f156..0xbc5f164
    // cmp qword ptr [0x12ADF808],0 ; je 0xBC5F207
    if (*reinterpret_cast<void**>(kSubBc5f110LoggerGlobal) == nullptr) {
        // 0xbc5f207..0xbc5f217
        // rdx = [rbp-0x78]; rcx = rdi; call 0xEBCE470 ; call qword ptr [0xF9A8CB0]
        sub_ebce470(fmt, vaArgsPtr);
        reinterpret_cast<void (*)()>(*reinterpret_cast<void**>(kSubBc5f110TerminateSlot))();
        // 0xbc5f21d..0xbc5f231
        // rcx = [rbp+0x1F90]; rcx ^= rbp; call 0xE951550 ; int3
        sub_e951550(reinterpret_cast<void*>(frame.cookie ^ reinterpret_cast<std::uintptr_t>(&frame)));
        __assume(false);
    }

    // 0xbc5f164..0xbc5f18f
    // esi = ecx (level); r9 = [rbp-0x78]; rcx = &[rbp-0x70]; edx = 0x2000; r8 = rdi; call 0xEBCF430;
    // edx = eax; cmp eax,0x2001; jl 0xBC5F1BD
    std::int32_t length = native::sub_ebcf430(frame.buffer, kSubBc5f110BufferSize, const_cast<char*>(fmt), vaArgsPtr);
    char* text = frame.buffer;
    if (length >= kSubBc5f110BufferSize + 1) {
        // 0xbc5f18f..0xbc5f1bd
        // rax = edx (length); rax += 0x10; rax &= ~0xF; call 0xE9E7970 ; sub rsp,rax ;
        // rbx = rsp; r9 = [rbp-0x78]; rcx = rbx; r8 = rdi (fmt); call 0xEBCF430 ;
        // edx = eax
        const std::size_t bytes = (static_cast<std::size_t>(length) + 0x10) & ~static_cast<std::size_t>(0xF);
        text = static_cast<char*>(_alloca(bytes));
        length = native::sub_ebcf430(text, length, const_cast<char*>(fmt), vaArgsPtr);
    }

    // 0xbc5f1bd..0xbc5f1e5
    // rax = (int64)edx ; byte ptr [rbx+rax] = 0 ; rcx = [0x12ADF808] ;
    // rax = [rcx] ; rax = [rax+8] ; edx = esi (level) ; r8 = rbx (text) ;
    // call qword ptr [0xF99FFA0] (CFG dispatch of vtable slot 1)
    text[length] = 0;
    void* const target = *reinterpret_cast<void**>(kSubBc5f110LoggerGlobal);
    void** const vtable = *reinterpret_cast<void***>(target);
    using LogCall = void (*)(void*, std::int32_t, const char*);
    const LogCall logCall = reinterpret_cast<LogCall>(vtable[kSubBc5f110LogVtableSlot]);
    logCall(target, level, text);                          // 0xbc5f1db  call qword ptr [0xF99FFA0]

    // 0xbc5f1e5..0xbc5f207
    // rax = [rbp+0x1F90]; rax ^= rbp; rcx = [0x1230A0C0]; cmp rcx,rax ; jne 0xBC5F21D ;
    // epilogue: lea rsp,[rbp+0x1F98]; pop rbx/rdi/rsi/rbp; ret
    if (*reinterpret_cast<std::uintptr_t*>(kSubBc5f110CookieGlobal) !=
        (frame.cookie ^ reinterpret_cast<std::uintptr_t>(&frame))) {
        // 0xbc5f21d..0xbc5f231
        // rcx = [rbp+0x1F90]; rcx ^= rbp; call 0xE951550 ; int3
        sub_e951550(reinterpret_cast<void*>(frame.cookie ^ reinterpret_cast<std::uintptr_t>(&frame)));
        __assume(false);
    }
}

// Verbatim log of every call instruction in [0xbc5f110, 0xbc5f231) (rdis dis output, two spaces after the address):
#if 0
0xbc5f119  call 0xE9E7970                                ; -> sub_e9e7970
0xbc5f17d  call 0xEBCF430                                ; -> sub_ebcf430
0xbc5f199  call 0xE9E7970                                ; -> sub_e9e7970
0xbc5f1b2  call 0xEBCF430                                ; -> sub_ebcf430
0xbc5f1db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5f212  call 0xEBCE470                                ; -> sub_ebce470
0xbc5f217  call qword ptr [0xF9A8CB0]                    ; [data_f9a8cb0]
0xbc5f22b  call 0xE951550                                ; -> sub_e951550
#endif

// Calls out of lifted code:
//   sub_e9e7970 (0xe9e7970, boundary crt) - __chkstk, emitted by the compiler for the 0x2018 frame and the alloca
//   sub_ebcf430 (0xebcf430, lift set) - native::sub_ebcf430, format into buffer
//   [0xF99FFA0] (data slot, loader-resolved __guard_dispatch_icall) - dispatches vtable slot 1 of the logger
//   sub_ebce470 (0xebce470, boundary crt) - format + fail-fast helper on the null-logger path
//   [0xF9A8CB0] (data slot, loader-resolved terminate pointer) - read at call time
//   sub_e951550 (0xe951550, boundary crt) - __security_check_cookie
//   UNRESOLVED CALL = none: every call target is lifted or listed in docs/data/native_boundary.tsv

LIFT_FN(sub_bc5f110, "sub_bc5f110", 0xbc5f110, sub_bc5f110, nullptr);

} // namespace native::bgfx
