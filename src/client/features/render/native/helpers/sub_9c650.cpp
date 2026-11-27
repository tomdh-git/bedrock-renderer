// LIFT 0x9c650 size 0xf3 1.26.62.01 sub_9c650
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_9c650.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {

// sub_e935700 (0xe935700): tail jump to sub_392960; argument forwarded in RCX,
// result returned in RAX. Forward-declared here (see sub_e935700.h).
void* sub_e935700(void* a0);

} // namespace native

namespace native::helpers {

LIFT_FN(sub_9c650, "sub_9c650", 0x9c650, sub_9c650, nullptr);

// Instruction coverage for [0x9c650, 0x9c743): every instruction lies in this
// cited range; the three calls are also quoted verbatim in the #if 0 block below.
// 0x9c650..0x9c743

// Layout assertion (also asserted in sub_9c650.h; repeated here so the lift
// source is self-contained for the layout check).
static_assert(offsetof(sub_9c650_rcx, block) == 0x0, "sub_9c650 rcx+0x0 block");
static_assert(offsetof(sub_9c650_rcx, end) == 0x8, "sub_9c650 rcx+0x8 end");
static_assert(offsetof(sub_9c650_rcx, cap) == 0x10, "sub_9c650 rcx+0x10 cap");
static_assert(offsetof(sub_9c650_rdi, ptr) == 0x20, "sub_9c650 rdi+0x20 ptr");
static_assert(offsetof(sub_9c650_rdi, field30) == 0x30, "sub_9c650 rdi+0x30 field30");
static_assert(offsetof(sub_9c650_rdi, size) == 0x38, "sub_9c650 rdi+0x38 size");
static_assert(offsetof(sub_9c650_rdi, flag) == 0x50, "sub_9c650 rdi+0x50 flag");
static_assert(offsetof(sub_9c650_rsp, home20) == 0x20, "sub_9c650 rsp+0x20 home20");

// Verbatim call instructions from the disassembly of [0x9c650, 0x9c743) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x9c680  call 0xE935700
0x9c70e  call 0xE935700
0x9c73c  call qword ptr [0xF9A8C78]
#endif

// Release a heap block described by the release context a0 (RCX).
//   a0->block (+0x0): current block pointer, a0->end (+0x8): end pointer,
//   a0->cap   (+0x10): size field.
// Walks sub-blocks of 0x58 bytes from block to end; sub-blocks whose +0x50 flag
// == 1 are released via sub_e935700 and their slot is cleared. On the
// heap-corruption path (block start < 0x20) calls the function pointer held in
// data slot RVA 0xF9A8C78 with five zero arguments; that block ends in int3
// (noreturn).
void* sub_9c650(void* a0) {
    auto* ctx = reinterpret_cast<sub_9c650_rcx*>(a0);

    // 0x9c650..0x9c663: prologue + block load + null test
    void* rdi = ctx->block;           // 0x9c657  mov rdi,[rcx]
    if (rdi == nullptr) {             // 0x9c65a  test rdi,rdi / 0x9c65d  je 0x9C721
        return nullptr;               // 0x9c721..0x9c729: epilogue; ret
    }

    void* rsi = a0;                   // 0x9c663  mov rsi,rcx
    void* rbx = ctx->end;             // 0x9c666  mov rbx,[rcx+8]

    // Noreturn heap-corruption path: calls the function pointer held in data
    // slot RVA 0xF9A8C78 with five zero arguments, then int3.
    auto fail = []() {
        using FailFn = void (*)(void*, void*, void*, void*, void*);
        FailFn failfn = reinterpret_cast<FailFn>(
            *reinterpret_cast<uintptr_t*>(
                RewriteRegistry::imageBase() + 0xF9A8C78));
        failfn(nullptr, nullptr, nullptr, nullptr, nullptr);
        __assume(false);   // int3: this block does not return
    };

    // 0x9c66a: if rdi == rbx skip the release loop
    if (rdi != rbx) {                 // 0x9c66a  cmp rdi,rbx / 0x9c66d  jne 0x9C6A2
        while (true) {                // 0x9c6a2: loop entry (from 0x9c69d)
            auto* sb = reinterpret_cast<sub_9c650_rdi*>(rdi);

            // 0x9c6a2  cmp byte ptr [rdi+0x50],1 / 0x9c6a6  jne 0x9C699
            if (sb->flag == 1) {      // 0x9c6a6  fall through -> 0x9c
                std::uint64_t rax = sb->size;   // 0x9c6a8  mov rax,[rdi+0x38]

                // 0x9c6ac  cmp rax,0x10 / 0x9c6b0  jb 0x9C685
                if (rax < 0x10) {     // 0x9c6b0  jb -> clear slot only
                    // (no sub_e935700 call on this path)
                } else {
                    void* rcx = sb->ptr;      // 0x9c6b2  mov rcx,[rdi+0x20]
                    std::uint64_t rdx = rax + 1; // 0x9c6b6  lea rdx,[rax+1]

                    // 0x9c6ba  cmp rdx,0x1000 / 0x9c6c1  jb 0x9C680
                    if (rdx < 0x1000) {       // 0x9c6c1  jb -> call sub_e935700(rcx)
                        // 0x9c680  call 0xE935700  (rcx = sb->ptr)
                        (void)native::sub_e935700(rcx);
                    } else {
                        // 0x9c6c3  mov r8,[rcx-8] / add rcx,-8 / sub rcx,r8
                        std::uint64_t r8 = *reinterpret_cast<std::uint64_t*>(
                            reinterpret_cast<uintptr_t>(rcx) - 8);
                        std::uint64_t rcx_val =
                            (reinterpret_cast<uintptr_t>(rcx) - 8) - r8;

                        // 0x9c6ce  cmp rcx,0x20 / 0x9c6d2  jae 0x9C729
                        if (rcx_val >= 0x20) {    // heap corruption -> fail path
                            fail();
                        }

                        // 0x9c6d4  add rax,0x28 / mov rdx,rax / mov rcx,r8 / jmp 0x9C680
                        rax += 0x28;              // 0x9c6d4 (rdx/rcx set up for call)
                        // 0x9c680  call 0xE935700  (rcx = r8)
                        (void)native::sub_e935700(reinterpret_cast<void*>(r8));
                    }
                }

                // 0x9c685: clear slot (reached on every non-fail path through 0x9c6a8)
                sb->field30 = 0;  // 0x9c685  mov qword ptr [rdi+0x30],0
                sb->size = 0xF;   // 0x9c68d  mov qword ptr [rdi+0x38],0xF
                sb->ptr = nullptr;// 0x9c695  mov byte ptr [rdi+0x20],0
            }

            // 0x9c699  add rdi,0x58 / cmp rdi,rbx / je 0x9C6E0
            rdi = reinterpret_cast<void*>(
                reinterpret_cast<uintptr_t>(rdi) + 0x58);
            if (rdi == rbx) {         // 0x9c6a0  je 0x9C6E0
                rdi = ctx->block;     // 0x9c6e0  mov rdi,[rsi]
                break;
            }
            // else fall through to 0x9c6a2 (loop)
        }
    }

    // 0x9c6e3  mov rdx,[rsi+0x10] / sub rdx,rdi
    std::uint64_t rdx = ctx->cap;
    rdx -= reinterpret_cast<uintptr_t>(rdi);

    // 0x9c6ea  cmp rdx,0x1000 / 0x9c6f1  jb 0x9C70B
    if (rdx >= 0x1000) {              // 0x9c6f1  jb not taken -> 0x9c6f3
        // 0x9c6f3  mov rax,[rdi-8] / add rdi,-8 / sub rdi,rax
        std::uint64_t rax = *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<uintptr_t>(rdi) - 8);
        std::uint64_t rdi2 =
            (reinterpret_cast<uintptr_t>(rdi) - 8) - rax;

        // 0x9c6fe  cmp rdi,0x20 / 0x9c702  jae 0x9C729
        if (rdi2 >= 0x20) {           // heap corruption -> fail path
            fail();
        }

        // 0x9c704  add rdx,0x27 / mov rdi,rax
        rdx += 0x27;
        rdi = reinterpret_cast<void*>(rax);   // 0x9c708  mov rdi,rax
    }

    // 0x9c70b  mov rcx,rdi / call 0xE935700
    void* ret = native::sub_e935700(rdi);   // 0x9c70e  call 0xE935700

    // 0x9c713  xorps xmm0,xmm0 / movups [rsi],xmm0 / mov [rsi+0x10],0
    ctx->block = nullptr;        // 0x9c716  movups [rsi],xmm0  (clears +0x0,+0x8)
    ctx->end = nullptr;
    ctx->cap = 0;                // 0x9c719  mov qword ptr [rsi+0x10],0

    // 0x9c721..0x9c729: epilogue; ret  (RAX = sub_e935700 result)
    return ret;
}

} // namespace native::helpers
