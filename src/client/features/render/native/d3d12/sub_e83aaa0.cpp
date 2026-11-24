// LIFT 0xe83aaa0 size 0x10d 1.26.62.01 sub_e83aaa0
#include "client/features/render/native/d3d12/sub_e83aaa0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

namespace {

// Indirect call through data slot 0xF99FFA0 (loader-resolved; boundary row 506).
// Read the pointer from the slot at call time, exactly as the instruction does.
using Eea6040Fn = void* (*)(void*, std::uint64_t);
inline Eea6040Fn eea6040_slot() {
    return reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + 0xF99FFA0));
}

} // namespace

void* sub_e83aaa0(void* a0, void* a1) {
    std::uint8_t* const s0 = reinterpret_cast<std::uint8_t*>(a0);
    std::uint8_t* const s1 = reinterpret_cast<std::uint8_t*>(a1);

    // 0xe83aaa0..0xe83aaaf: prologue. rsi=a0, rdi=a1.
    // 0xe83aaac  cmp rcx,rdx ; je 0xE83ABA0
    if (a0 == a1) {
        // 0xe83aba0..0xe83abac: epilogue, return rsi (a0).
        return a0;
    }

    // 0xe83aab5..0xe83aab8: rdi=a1; rbx=rsi+0x40.
    void* const inline78 = reinterpret_cast<void*>(s0 + native::E83aaa0Layout::kInlineF78);

    // 0xe83aabc..0xe83aad8: release a0's current +0x78 member if present.
    //   rcx=[rsi+0x78]; test; je 0xE83AAE0
    //   cmp rcx,rbx; setne dl
    //   mov rax,[rcx]; mov rax,[rax+0x20]   (CFG vtable load, dead)
    //   0xe83aad2  call qword ptr [0xF99FFA0]
    //   0xe83aad8  mov [rsi+0x78],0
    {
        void* cur = *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF78);
        if (cur != nullptr) {
            const bool ne = (cur != inline78);
            std::uint64_t rdx_arg = reinterpret_cast<std::uint64_t>(a1);
            rdx_arg = (rdx_arg & ~0xFFULL) | (ne ? 1ULL : 0ULL);
            // 0xe83aad2  call qword ptr [0xF99FFA0]
            eea6040_slot()(cur, rdx_arg);
            *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF78) = nullptr;
        }
    }

    // 0xe83aae0..0xe83ab28: move a1's +0x78 member into a0.
    //   rcx=[rdi+0x78]; test; je 0xE83AB30
    //   r14=rdi+0x40; cmp rcx,r14
    //   if not equal: [rsi+0x78]=rcx; jmp 0xE83AB28
    //   else (inline): clone via vtable[+8] into rbx, then destroy a1's via vtable[+0x20]
    {
        void* cur = *reinterpret_cast<void**>(s1 + native::E83aaa0Layout::kOffF78);
        void* const inline78_src = reinterpret_cast<void*>(s1 + native::E83aaa0Layout::kInlineF78);
        if (cur != nullptr) {
            if (cur != inline78_src) {
                // 0xe83aaf2  mov [rsi+0x78],rcx
                *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF78) = cur;
            } else {
                // 0xe83aaf8..0xe83ab08: clone into rbx (a0+0x40).
                //   mov rax,[rcx]; mov rax,[rax+8]; mov rdx,rbx; call [slot]
                //   mov [rsi+0x78],rax
                void* cloned = eea6040_slot()(cur, reinterpret_cast<std::uint64_t>(inline78));
                *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF78) = cloned;

                // 0xe83ab0c..0xe83ab22: destroy a1's (now old) inline member.
                void* cur2 = *reinterpret_cast<void**>(s1 + native::E83aaa0Layout::kOffF78);
                if (cur2 != nullptr) {
                    const bool ne2 = (cur2 != inline78_src);
                    std::uint64_t rdx_arg2 = reinterpret_cast<std::uint64_t>(a1);
                    rdx_arg2 = (rdx_arg2 & ~0xFFULL) | (ne2 ? 1ULL : 0ULL);
                    // 0xe83ab22  call qword ptr [0xF99FFA0]
                    eea6040_slot()(cur2, rdx_arg2);
                }
            }
            // 0xe83ab28  mov [rdi+0x78],0
            *reinterpret_cast<void**>(s1 + native::E83aaa0Layout::kOffF78) = nullptr;
        }
    }

    // 0xe83ab30..0xe83ab4c: release a0's current +0x38 member if present.
    //   rcx=[rsi+0x38]; test; je 0xE83AB54
    //   cmp rcx,rsi; setne dl
    //   mov rax,[rcx]; mov rax,[rax+0x20]; call [slot]
    //   mov [rsi+0x38],0
    {
        void* cur = *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF38);
        if (cur != nullptr) {
            const bool ne = (cur != a0);
            std::uint64_t rdx_arg = reinterpret_cast<std::uint64_t>(a0);
            rdx_arg = (rdx_arg & ~0xFFULL) | (ne ? 1ULL : 0ULL);
            // 0xe83ab46  call qword ptr [0xF99FFA0]
            eea6040_slot()(cur, rdx_arg);
            *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF38) = nullptr;
        }
    }

    // 0xe83ab54..0xe83ab98: move a1's +0x38 member into a0.
    //   rcx=[rdi+0x38]; test; je 0xE83ABA0
    //   cmp rcx,rdi
    //   if not equal: [rsi+0x38]=rcx; jmp 0xE83AB98
    //   else (inline): clone via vtable[+8] into rsi (a0), then destroy a1's via vtable[+0x20]
    {
        void* cur = *reinterpret_cast<void**>(s1 + native::E83aaa0Layout::kOffF38);
        if (cur != nullptr) {
            if (cur != a1) {
                // 0xe83ab62  mov [rsi+0x38],rcx
                *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF38) = cur;
            } else {
                // 0xe83ab68..0xe83ab78: clone into rsi (a0).
                //   mov rax,[rcx]; mov rax,[rax+8]; mov rdx,rsi; call [slot]
                //   mov [rsi+0x38],rax
                void* cloned = eea6040_slot()(cur, reinterpret_cast<std::uint64_t>(a0));
                *reinterpret_cast<void**>(s0 + native::E83aaa0Layout::kOffF38) = cloned;

                // 0xe83ab7c..0xe83ab92: destroy a1's (now old) inline member.
                void* cur2 = *reinterpret_cast<void**>(s1 + native::E83aaa0Layout::kOffF38);
                if (cur2 != nullptr) {
                    const bool ne2 = (cur2 != a1);
                    std::uint64_t rdx_arg2 = reinterpret_cast<std::uint64_t>(a1);
                    rdx_arg2 = (rdx_arg2 & ~0xFFULL) | (ne2 ? 1ULL : 0ULL);
                    // 0xe83ab92  call qword ptr [0xF99FFA0]
                    eea6040_slot()(cur2, rdx_arg2);
                }
            }
            // 0xe83ab98  mov [rdi+0x38],0
            *reinterpret_cast<void**>(s1 + native::E83aaa0Layout::kOffF38) = nullptr;
        }
    }

    // 0xe83aba0..0xe83abac: epilogue, return rsi (a0).
    return a0;
}

static native::Footprint sub_e83aaa0_footprint(void* a0, void* a1) {
    return { { a0, native::E83aaa0Layout::kObjSize }, { a1, native::E83aaa0Layout::kObjSize } };
}

// Layout assertions.
static_assert(native::E83aaa0Layout::kOffF38 == 0x38, "e83aaa0: +0x38");
static_assert(native::E83aaa0Layout::kOffF78 == 0x78, "e83aaa0: +0x78");
static_assert(native::E83aaa0Layout::kInlineF78 == 0x40, "e83aaa0: inline +0x40");
static_assert(sizeof(void*) == 8, "e83aaa0: 64-bit");

// Verbatim log of every call instruction in [0xe83aaa0, 0xe83abad) (rdis dis output,
// two spaces after the address):
#if 0
0xe83aad2  call qword ptr [0xF99FFA0]
0xe83ab02  call qword ptr [0xF99FFA0]
0xe83ab22  call qword ptr [0xF99FFA0]
0xe83ab46  call qword ptr [0xF99FFA0]
0xe83ab72  call qword ptr [0xF99FFA0]
0xe83ab92  call qword ptr [0xF99FFA0]
#endif
// Calls out of lifted code:
//   sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0, docs/data/native_boundary.tsv
//   row 506) x6: read through slot 0xF99FFA0 at every call.
//   UNRESOLVED CALL = none.

LIFT_FN(sub_e83aaa0, "sub_e83aaa0", 0xe83aaa0, sub_e83aaa0, sub_e83aaa0_footprint);

} // namespace native::d3d12
