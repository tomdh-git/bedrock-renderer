// LIFT 0xebcf430 size 0x2a 1.26.62.01 sub_ebcf430
#include "sub_ebcf430.h"

#include <atomic>
#include <string>
#include <vector>

#include "client/features/render/native/Lift.h"

#if 0
// Verbatim instructions of sub_ebcf430 [0xebcf430, 0xebcf45a), as printed by
// `rdis ... dis 0xebcf430 0x2a`:
0xebcf430  mov [rsp+0x10],rbp
0xebcf435  mov [rsp+0x18],rsi
0xebcf43a  mov [rsp+0x20],rdi
0xebcf43f  push r14
0xebcf441  sub rsp,0x40
0xebcf445  mov rsi,r9
0xebcf448  mov rbp,r8
0xebcf44b  mov rdi,rcx
0xebcf44e  mov r14,0xFFFFFFFFFFFFFFFF
0xebcf455  test rcx,rcx
0xebcf458  je short 0xEBCF49C
#endif

namespace native {

// Lifted body of sub_ebcf430 (0xebcf430, size 0x2a, 1.26.62.01): prologue,
// register reassignment and the branch on RCX.
//
// The incoming callee-saved registers (RBP, RSI, RDI, R14) are spilled to the
// stack frame, then RBP = R8 (a3), RSI = R9 (a4), RDI = RCX (a1), R14 = -1, and
// the function branches on RCX:
//
//   0xebcf458  je short 0xEBCF49C   ; taken when a1 == nullptr
//
// Both successors (0xebcf49c on the jump, 0xebcf45a on the fall-through) lie
// outside [0xebcf430, 0xebcf45a), so no return value is produced inside this
// lift unit; EAX is produced by later ranges of sub_ebcf430 (the epilogue at
// 0xebcf4ca..0xebcf4df returns EAX).
//
// Writes, in order:
//   [entry RSP+0x10] <- incoming RBP   0xebcf430  mov [rsp+0x10],rbp
//   [entry RSP+0x18] <- incoming RSI   0xebcf435  mov [rsp+0x18],rsi
//   [entry RSP+0x20] <- incoming RDI   0xebcf43a  mov [rsp+0x20],rdi
//   [entry RSP-8]    <- incoming R14   0xebcf43f  push r14
//   RSP -= 0x40                          0xebcf441  sub rsp,0x40
//   RSI <- R9                            0xebcf445  mov rsi,r9
//   RBP <- R8                            0xebcf448  mov rbp,r8
//   RDI <- RCX                           0xebcf44b  mov rdi,rcx
//   R14 <- -1                            0xebcf44e  mov r14,0xFFFFFFFFFFFFFFFF
//   branch on RCX                        0xebcf455  test rcx,rcx ; 0xebcf458  je short 0xEBCF49C
int32_t sub_ebcf430_lifted(void* a1 [[maybe_unused]], int32_t a2 [[maybe_unused]],
                           void* a3 [[maybe_unused]], void* a4 [[maybe_unused]]) {
    // 0xebcf430..0xebcf441
    // Incoming callee-saved register contents (caller-dependent; stored to the
    // frame and never read again inside [0xebcf430, 0xebcf45a)).
    std::uintptr_t saved_rbp;
    std::uintptr_t saved_rsi;
    std::uintptr_t saved_rdi;
    std::uintptr_t saved_r14;

    SubEbcf430Frame frame;

    // 0xebcf430  mov [rsp+0x10],rbp   -> frame.rbp_save  (offset 0x58 from post-sub RSP)
    // 0xebcf435  mov [rsp+0x18],rsi   -> frame.rsi_save  (offset 0x60)
    // 0xebcf43a  mov [rsp+0x20],rdi   -> frame.rdi_save  (offset 0x68)
    // 0xebcf43f  push r14             -> frame.r14_save  (offset 0x40; [entry RSP-8])
    // 0xebcf441  sub rsp,0x40          (frame base already assumes the post-sub RSP)
    frame.rbp_save = saved_rbp;
    frame.rsi_save = saved_rsi;
    frame.rdi_save = saved_rdi;
    frame.r14_save = saved_r14;

    // 0xebcf445  mov rsi,r9
    // 0xebcf448  mov rbp,r8
    // 0xebcf44b  mov rdi,rcx
    [[maybe_unused]] void* rdi = a1;
    [[maybe_unused]] void* rbp = a3;
    [[maybe_unused]] void* rsi = a4;
    [[maybe_unused]] std::uintptr_t r14 = 0xFFFFFFFFFFFFFFFFui64;

    // 0xebcf455  test rcx,rcx
    // 0xebcf458  je short 0xEBCF49C   ; successor 0xebcf49c (taken, a1 == nullptr)
    //          fall-through           ; successor 0xebcf45a (not taken)
    if (a1 == nullptr) {
        // control leaves this lift unit at 0xebcf49c; no instruction of this unit runs after
    } else {
        // control leaves this lift unit at 0xebcf45a; no instruction of this unit runs after
    }

    // No return statement is reached inside [0xebcf430, 0xebcf45a): every path through
    // this range ends at the branch above, which transfers control outside the lift unit.
    __assume(false);
}

} // namespace native

LIFT_FN(sub_ebcf430, "sub_ebcf430", 0xEBCF430, sub_ebcf430_lifted, nullptr);
