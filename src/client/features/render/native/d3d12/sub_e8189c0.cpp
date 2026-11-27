// LIFT 0xe8189c0 size 0xa1 1.26.62.01 sub_e8189c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e8189c0.h"
#include "client/features/render/native/helpers/sub_ebce650.h"

#include <cstdint>
#include <intrin.h>

extern std::uintptr_t data_1230a0c0;   // [0x1230A0C0] stack security cookie (mov rax,[0x1230A0C0] at 0xe8189cc and 0xe818a3f)

// Boundary callees (class `crt` per docs/data/native_boundary.tsv row 467: 0xe951550 crt).
namespace native::boundary {
    // Stack-cookie failure route: argument = the current cookie value. Re-validates the cookie
    // and returns if intact; otherwise jumps into the fail-fast path (sub_e98e3c0) and does not
    // return. The caller follows the call with int3 (0xe818a60).
    extern "C" void sub_e951550(std::uintptr_t cookie) noexcept;
}

// Verbatim call instructions from the disassembly of [0xe8189c0, 0xe818a61):
//   0xe8189ff  call 0xEBCE5E0   (sub_ebce5e0, lift-set, forward-declared in sub_e8189c0.h)
//   0xe818a32  call 0xEBCE650   (sub_ebce650, lift-set, native/helpers/sub_ebce650.h)
//   0xe818a5b  call 0xE951550   (sub_e951550, crt boundary wrapper above)
#if 0
0xe8189ff  call 0xEBCE5E0
0xe818a32  call 0xEBCE650
0xe818a5b  call 0xE951550
#endif

namespace native::d3d12 {

native::Footprint sub_e8189c0_footprint(RendererContextD3D12* ctx, std::uint16_t index,
                                        const char* name) {
    // Writes at most kNameCopyBound bytes (copied bytes plus terminator) at
    // ctx + kNameSlotBaseOffset + index*kNameSlotStride.
    (void)name;
    return { { reinterpret_cast<char*>(ctx) + kNameSlotBaseOffset +
                  static_cast<size_t>(index) * kNameSlotStride,
              kNameCopyBound } };
}

void sub_e8189c0(RendererContextD3D12* ctx, std::uint16_t index, const char* name) noexcept {
    // 0xe8189c0..0xe8189c3: prologue (push rsi, push rdi, push rbx, sub rsp,0x40) - stack frame,
    // nothing to emit in C++.

    // 0xe8189cc..0xe8189d6: stack cookie = data_1230a0c0 ^ rsp, stored at [rsp+0x38].
    std::uintptr_t cookie = data_1230a0c0 ^ reinterpret_cast<std::uintptr_t>(&cookie);

    // 0xe8189db..0xe8189e7: default descriptor { ptr = &data_f847a07, maxlen = 0 }.
    native::SrcDesc desc{};
    desc.ptr = data_f847a07;
    desc.maxlen = 0;

    // 0xe8189ef..0xe8189f2: if name == null, skip the length measurement.
    if (name != nullptr) {
        // 0xe8189f4..0xe8189ff: rbx = name; eax = sub_ebce5e0(name, 0x7FFFFFFF).
        // 0xe8189ff  call 0xEBCE5E0
        int len = sub_ebce5e0(name, kNameLengthCap);
        // 0xe818a04..0xe818a0c: if len != 0, descriptor = { ptr = name, maxlen = len }.
        if (len != 0) {
            desc.maxlen = len;
            desc.ptr = const_cast<char*>(name);   // the original stores the name pointer as-is (no const guarantee at ABI level)
        }
    }

    // 0xe818a11..0xe818a1b: destination = ctx + (index << 8) + 0x7EDE = &ctx->name_slot + index.
    char* dst = reinterpret_cast<char*>(&ctx->name_slot) +
                static_cast<size_t>(index) * kNameSlotStride;

    // 0xe818a22..0xe818a32: sub_ebce650(dst, 0xFA, &desc, 0x7FFFFFFF); return value ignored.
    // 0xe818a32  call 0xEBCE650
    (void)sub_ebce650(dst, kNameCopyBound, &desc, kNameLengthCap);

    // 0xe818a37..0xe818a49: verify the stored cookie; mismatch goes to the fail path.
    if (data_1230a0c0 != (cookie ^ reinterpret_cast<std::uintptr_t>(&cookie))) {
        // loc_e818a53:
        // 0xe818a53..0xe818a5b: rcx = cookie; call sub_e951550(cookie).
        // 0xe818a5b  call 0xE951550
        native::boundary::sub_e951550(cookie ^ reinterpret_cast<std::uintptr_t>(&cookie));
        // 0xe818a60  int3
        __debugbreak();
    }
    // 0xe818a4b..0xe818a52: add rsp,0x40; pop rbx; pop rdi; pop rsi; ret.
}

static_assert(offsetof(native::d3d12::RendererContextD3D12, name_slot) == 0x7EDE,
    "sub_e8189c0: name_slot at +0x7EDE (repeated here so liftcheck sees it)");

LIFT_FN(sub_e8189c0, "sub_e8189c0", 0xe8189c0, sub_e8189c0, sub_e8189c0_footprint);

} // namespace native::d3d12
