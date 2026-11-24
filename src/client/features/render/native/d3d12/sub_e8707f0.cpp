// LIFT 0xe8707f0 size 0x7b 1.26.62.01 sub_e8707f0
#include "sub_e8707f0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

namespace native { namespace d3d12 {

// Layout assertion: x64 target
static_assert(sizeof(void*) == 8, "sub_e8707f0: x64 target");

namespace {

// sub_e951550 = __report_gsfailure (docs/data/native_boundary.tsv: class crt).
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// sub_eec6d80 = C++ exception throw (docs/data/native_boundary.tsv: class lift).
// Called with (rcx = exception object, rdx = type_info).
native::Boundary<void, void*, const void*> sub_eec6d80("sub_eec6d80");

// The vtable slot for istream::read at 0xF9A7480.
// In the exe, this slot holds a pointer to the read() function.
// We load it at call time exactly as the instruction does: call qword ptr [0xF9A7480].
using ReadFn = void* (*)(void* stream, void* buffer, std::uint32_t count);

} // namespace

extern "C" bool sub_e8707f0(void* stream, std::uint32_t* out) {
    const std::uintptr_t base = RewriteRegistry::imageBase();

    // 0xe8707f0..0xe8707fe  security cookie prologue
    const std::uintptr_t cookie = *reinterpret_cast<std::uintptr_t*>(base + kCookieRva);
    volatile std::uintptr_t cookieSlot = 0;                       // [rsp+0x40]
    const std::uintptr_t frame = reinterpret_cast<std::uintptr_t>(&cookieSlot);
    cookieSlot = cookie ^ frame;                                  // mov [rsp+0x40],rax

    // 0xe870803..0xe87080f  call istream::read(stream, out, 4)
    // r8d = 4 (kReadSize), rdx = out, rcx = stream
    ReadFn readFn = *reinterpret_cast<ReadFn*>(base + kReadSlotRva);
    void* readResult = readFn(stream, out, kReadSize);            // 0xe870809  call qword ptr [0xF9A7480]

    // 0xe87080f..0xe87081c  check gcount()
    // read() returns the stream (this); gcount() is at stream+8
    std::int64_t gcount = *reinterpret_cast<std::int64_t*>(reinterpret_cast<std::uintptr_t>(readResult) + 8);

    bool success = false;
    if (gcount < 0) {
        // 0xe870816..0xe870837  error path: throw exception
        // xorps xmm0,xmm0; movups [rsp+0x30],xmm0
        // lea rax,[0xF08E738]; mov [rsp+0x28],rax
        // lea rdx,[0xFB3B080]; lea rcx,[rsp+0x28]; call 0xEEC6D80
        void* exceptionObj = reinterpret_cast<void*>(base + kExceptionObjRva);
        const void* typeInfo = reinterpret_cast<const void*>(base + kTypeInfoRva);
        sub_eec6d80(exceptionObj, typeInfo);                      // 0xe870858  call 0xEEC6D80
        __builtin_unreachable();                                  // noreturn
    } else {
        // 0xe870818..0xe87081c  cmp rax,4; sete al
        success = (gcount == 4);
    }

    // 0xe87081f..0xe870837  cookie check + return
    const std::uintptr_t check = cookieSlot ^ frame;
    if (check != cookie) {
        // 0xe87085d..0xe870865  failure path: __report_gsfailure
        sub_e951550(check);                                       // 0xe870865  call 0xE951550
        __builtin_unreachable();                                  // 0xe87086a  int3 (padding after noreturn)
    }

    // 0xe870833..0xe870837  add rsp,0x48; ret
    return success;
}

// Verbatim call instructions in [0xe8707f0, 0xe87086b) (rdis dis, two spaces after address):
#if 0
0xe870809  call qword ptr [0xF9A7480]
0xe870858  call 0xEEC6D80
0xe870865  call 0xE951550
#endif

// Calls out of lifted code:
//   0xe870809  call qword ptr [0xF9A7480]   -> istream::read (vtable slot, loaded from kReadSlotRva at call time)
//   0xe870858  call 0xEEC6D80               -> sub_eec6d80 (class lift, native::Boundary)
//   0xe870865  call 0xE951550               -> sub_e951550 (class crt, native::Boundary)
//   UNRESOLVED CALL = none

// Registry entry
LIFT_FN(sub_e8707f0, "sub_e8707f0", 0xe8707f0, sub_e8707f0, nullptr);

} } // namespace native::d3d12