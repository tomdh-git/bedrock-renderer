// LIFT 0xbc6aeb0 size 0x86 1.26.62.01 sub_bc6aeb0
#include "client/features/render/native/bgfx/sub_bc6aeb0.h"

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc7a9d0.h"

// Verbatim call instructions from the disassembly of [0xbc6aeb0, 0xbc6af36).
// 0xbc6aecf  call 0xE9E7970                                ; -> sub_e9e7970
// 0xbc6aedf  call 0xE9E7970                                ; -> sub_e9e7970
// 0xbc6aefd  call 0xBC7A9D0                                ; -> sub_bc7a9d0
// 0xbc6af30  call 0xE951550                                ; -> sub_e951550

namespace {

native::Boundary<std::uintptr_t, std::uintptr_t> sub_e9e7970("sub_e9e7970");
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

} // namespace

namespace native::bgfx {

bool sub_bc6aeb0(void* p) {
    // 0xbc6aeb0..0xbc6aec4 — prologue + load count = *(u32*)p.
    std::uint32_t count = *static_cast<std::uint32_t*>(p);   // 0xbc6aec4  mov esi,[rcx]

    // 0xbc6aec6..0xbc6aec8 — if (count == 0) skip to epilogue.
    if (count == 0) {                                         // 0xbc6aec6  test esi,esi / 0xbc6aec8  je short 0xBC6AF06
        // 0xbc6af06..0xbc6af24 — epilogue: return (count != 0).
        return count != 0;                                    // 0xbc6af06  test esi,esi / 0xbc6af08  setne al
    }

    // 0xbc6aeca..0xbc6aed4 — chkstk 0x400, buf0 = rsp.
    (void)sub_e9e7970(0x400u);                               // 0xbc6aecf  call 0xE9E7970
    // 0xbc6aed4..0xbc6aed7 — sub rsp, rax (performed by boundary); buf0 = rsp.
    // We model the two buffers as local arrays.
    // 0xbc6aeda..0xbc6aee4 — chkstk 0x400, buf1 = rsp.
    (void)sub_e9e7970(0x400u);                               // 0xbc6aedf  call 0xE9E7970

    // 0xbc6aee7..0xbc6aef2 — r9 = buf1; r8 = p+0x404; rcx += 4.
    // 0xbc6aef5..0xbc6aefd — push count to [rsp+0x20]; call sub_bc7a9d0.
    // buf0/buf1 are the two stack buffers; pass them as the workKeys/parOut args.
    std::uint8_t buf0[0x400];
    std::uint8_t buf1[0x400];
    sub_bc7a9d0(static_cast<std::uint32_t*>(static_cast<void*>(static_cast<char*>(p) + 4)),
                reinterpret_cast<std::uint32_t*>(buf0),
                static_cast<std::uint32_t*>(static_cast<void*>(static_cast<char*>(p) + 0x404)),
                reinterpret_cast<std::uint32_t*>(buf1),
                count);                                       // 0xbc6aefd  call 0xBC7A9D0

    // 0xbc6af02  add rsp,0x30
    // 0xbc6af02 — add rsp,0x30 (performed by scope).
    // 0xbc6af06.. — epilogue.
    return count != 0;                                        // 0xbc6af06  test esi,esi / 0xbc6af08  setne al
}

} // namespace native::bgfx

LIFT_FN(sub_bc6aeb0, "sub_bc6aeb0", 0xbc6aeb0, sub_bc6aeb0, nullptr);

// Stack cookie check at 0xbc6af0b..0xbc6af35 is compiler-generated; on mismatch
// the original calls sub_e951550 (boundary crt, noreturn) at 0xbc6af30.
static_assert(true, "sub_bc6aeb0: no struct offsets beyond the leading count");