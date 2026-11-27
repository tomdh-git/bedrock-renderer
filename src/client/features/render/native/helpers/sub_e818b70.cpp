// LIFT 0xe818b70 size 0x4c 1.26.62.01 sub_e818b70
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e818b70.h"
#include "client/features/render/native/helpers/sub_e83abb0.h"
#include "client/features/render/native/bgfx/sub_bc5f110.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

// Verbatim call instructions from the disassembly of [0xe818b70, 0xe818bbc) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xe818b90  call 0xE83ABB0
0xe818baf  call 0xBC5F110
#endif

// Calls resolved through the lifted headers:
//   0xe818b90  call 0xE83ABB0 -> sub_e83abb0(void* self, std::uint64_t size) : uintptr_t
//   0xe818baf  call 0xBC5F110 -> native::bgfx::sub_bc5f110(std::int32_t level, const char* fmt,
//                                                             std::uintptr_t varg1, std::uintptr_t varg2) : void
// The listing sets rcx=0 and rdx="FAILED: ..." for the log call; R8/R9 are not
// written by this function before the call, so 0 is passed for those vararg slots.

LIFT_FN(sub_e818b70, "sub_e818b70", 0xe818b70, sub_e818b70, nullptr);

// Layout assertions for the fields this lift reads (also in sub_e818b70.h).
static_assert(offsetof(sub_e818b70_rcx, fc96190) == 0xc96190, "sub_e818b70 rcx+0xc96190 field");
static_assert(sizeof(sub_e818b70_rcx) >= 0xc96191, "sub_e818b70 rcx sizeof lower bound");

uintptr_t sub_e818b70(void* self, std::uint32_t a2)
{
    // ret models rax where the listing writes it (the 0xe818b90 call); on every
    // other path rax still holds the value it had on entry (not modeled here,
    // exactly like the real register).
    uintptr_t ret;

    // 0xe818b70..0xe818b7c: basic block 0
    // 0xe818b70  push rsi
    // 0xe818b71  push rdi
    // 0xe818b72  sub rsp,0x28
    // 0xe818b76  cmp dx,1
    // 0xe818b7a  jne short 0xE818BB5
    // -> if u16(a2) != 0x1 goto L_0xe818bb5
    // -> if u16(a2) == 0x1 goto L_0xe818b7c
    if (static_cast<std::uint16_t>(a2) != 1u) goto L_0xe818bb5;

    // 0xe818b7c..0xe818b9d: basic block 1
    // 0xe818b7c  mov rsi,rcx
    // 0xe818b7f  mov eax,edx
    // 0xe818b81  shr eax,0x10
    // 0xe818b84  add rcx,0xBDE178
    // 0xe818b8b  mov edi,edx
    // 0xe818b8d  mov rdx,rax
    // 0xe818b90  call 0xE83ABB0
    // 0xe818b95  cmp edi,0x10000000
    // 0xe818b9b  jb short 0xE818BB5
    // -> ret = sub_e83abb0(self + 0xBDE178, u16(a2 >> 16))
    // -> if u32(a2) <u 0x10000000 goto L_0xe818bb5
    //    (declared without an initializer so the 0xe818b7a goto does not skip it)
    void* p;
    p = reinterpret_cast<std::uint8_t*>(self) + 0xBDE178;
    ret = sub_e83abb0(p, static_cast<std::uint64_t>(static_cast<std::uint16_t>(a2 >> 16)));
    if (a2 < 0x10000000u) goto L_0xe818bb5;

    // 0xe818b9d..0xe818ba6: basic block 2
    // 0xe818b9d  cmp byte ptr [rsi+0xC96190],0
    // 0xe818ba4  je short 0xE818BB5
    // -> if *u8(self + 0xC96190) == 0x0 goto L_0xe818bb5
    if (reinterpret_cast<sub_e818b70_rcx*>(self)->fc96190 == 0) goto L_0xe818bb5;

    // 0xe818ba6..0xe818bb5: basic block 3
    // 0xe818ba6  lea rdx,[0xF7F68E3]
    // 0xe818bad  xor ecx,ecx
    // 0xe818baf  call 0xBC5F110
    // 0xe818bb4  nop
    // -> native::bgfx::sub_bc5f110(0, "FAILED: accessing a guarded paged heap backed array out of bounds.", 0, 0)
    //    rax after this void-returning call is not modeled (void callee); see epilogue.
    native::bgfx::sub_bc5f110(0, "FAILED: accessing a guarded paged heap backed array out of bounds.", 0, 0);

L_0xe818bb5:
    // 0xe818bb5..0xe818bbc: basic block 4
    // 0xe818bb5  add rsp,0x28
    // 0xe818bb9  pop rdi
    // 0xe818bba  pop rsi
    // 0xe818bbb  ret
    // -> (fall-through / ret / end)
    return ret;
}

} // namespace native::helpers
