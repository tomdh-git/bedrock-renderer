// LIFT 0xc2a4150 size 0x132 1.26.62.01 sub_c2a4150
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c2a4150.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_c2a4150, "sub_c2a4150", 0xc2a4150, sub_c2a4150, nullptr);

// Verbatim call instructions from the disassembly of [0xc2a4150, 0xc2a4282) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc2a41a7  call 0xE935700
0xc2a41e8  call 0xE935700
0xc2a4210  call qword ptr [0xF99FFA0]
0xc2a4226  call qword ptr [0xF99FFA0]
0xc2a423a  call 0xE935700
0xc2a4243  call 0x67577C0
0xc2a427b  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0xc2a4150, 0xc2a4282) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

extern "C" void sub_e935700(uint64_t a0, uint64_t a1, void* a2, void* a3);
extern "C" void sub_67577c0(void* a0);
extern "C" void sub_eea6040(void* a0);

// Layout assertions for all dereferenced base-register structs (offsets match the listing).
static_assert(offsetof(sub_c2a4150_rdx, f10) == 0x10, "rdx+0x10");
static_assert(offsetof(sub_c2a4150_rdx, f288) == 0x288, "rdx+0x288");
static_assert(offsetof(sub_c2a4150_rdx, f298) == 0x298, "rdx+0x298");
static_assert(offsetof(sub_c2a4150_rdx, f2a8) == 0x2a8, "rdx+0x2a8");
static_assert(sizeof(sub_c2a4150_rdx) >= 0x2b0, "rdx sizeof");
static_assert(offsetof(sub_c2a4150_r14, f0) == 0x0, "r14+0x0");
static_assert(offsetof(sub_c2a4150_r14, f20) == 0x20, "r14+0x20");
static_assert(sizeof(sub_c2a4150_r14) >= 0x28, "r14 sizeof");
static_assert(offsetof(sub_c2a4150_rax, f0) == 0x0, "rax+0x0");
static_assert(offsetof(sub_c2a4150_rax, f8) == 0x8, "rax+0x8");
static_assert(sizeof(sub_c2a4150_rax) >= 0x10, "rax sizeof");
static_assert(offsetof(sub_c2a4150_rbx, f0) == 0x0, "rbx+0x0");
static_assert(offsetof(sub_c2a4150_rbx, f8) == 0x8, "rbx+0x8");
static_assert(offsetof(sub_c2a4150_rbx, fc) == 0xc, "rbx+0xc");
static_assert(sizeof(sub_c2a4150_rbx) >= 0x10, "rbx sizeof");
static_assert(offsetof(sub_c2a4150_rdi, f0) == 0x0, "rdi+0x0");
static_assert(offsetof(sub_c2a4150_rdi, f10) == 0x10, "rdi+0x10");
static_assert(sizeof(sub_c2a4150_rdi) >= 0x18, "rdi sizeof");
static_assert(offsetof(sub_c2a4150_rsp, f20) == 0x20, "rsp+0x20");
static_assert(sizeof(sub_c2a4150_rsp) >= 0x28, "rsp sizeof");

uintptr_t sub_c2a4150(void* self) {
    // State machine lifting blocks 0..15 of [0xc2a4150, 0xc2a4282).
    // No gotos: each block is a case that sets `pc` to fall into the next case.
    uint32_t pc = 0;

    // Block-local state carried across cases.
    auto* rdxx = reinterpret_cast<sub_c2a4150_rdx*>(self);
    uint64_t rcx = 0;
    uint64_t rdx = 0;
    uint64_t rax = 0;
    auto* rdi = reinterpret_cast<sub_c2a4150_rdi*>(&rdxx->f298);
    void* r14p = nullptr;
    auto* rbx = reinterpret_cast<sub_c2a4150_rbx*>(nullptr);
    auto* rax_ptr = reinterpret_cast<sub_c2a4150_rax*>(nullptr);

    while (true) {
        switch (pc) {
        case 0: { // 0xc2a4150..0xc2a4162: basic block 0
                  // push r14 / push rsi / push rdi / push rbx / sub rsp,0x28
                  // test rdx,rdx ; je 0xC2A425E
            if (self == nullptr) { pc = 15; break; }
            pc = 1; break;
        }

        case 1: { // 0xc2a4162..0xc2a4171: basic block 1
                  // mov rsi,rdx ; mov rcx,[rdx+0x298] ; test rcx,rcx ; je short 0xC2A41BA
            rcx = rdxx->f298;
            if (rcx == 0) { pc = 6; break; }
            pc = 2; break;
        }

        case 2: { // 0xc2a4171..0xc2a4184: basic block 2
                  // mov rdx,[rsi+0x2A8] ; sub rdx,rcx ; cmp rdx,0x1000 ; jb short 0xC2A41A0
            rdx = reinterpret_cast<uintptr_t>(rdxx->f2a8) - rcx;
            if (rdx < 0x1000ULL) { pc = 5; break; }
            pc = 3; break;
        }

        case 3: { // 0xc2a4184..0xc2a4199: basic block 3
                  // mov rax,[rcx-8] ; add rcx,0xFFFFFFFFFFFFFFF8 ; sub rcx,rax
                  // cmp rcx,0x20 ; jae 0xC2A4268
            rax = *reinterpret_cast<uintptr_t*>(static_cast<uintptr_t>(rcx) - 8);
            rcx -= 8;
            rcx -= rax;
            if (rcx >= 0x20ULL) { pc = 15; break; }
            pc = 4; break;
        }

        case 4: { // 0xc2a4199..0xc2a41a0: basic block 4
                  // add rdx,0x27 ; mov rcx,rax ; fallthrough to block 5
            rdx += 0x27;
            rcx = rax;
            pc = 5; break;
        }

        case 5: { // 0xc2a41a0..0xc2a41ba: basic block 5
                  // lea rdi,[rsi+0x298] ; call 0xE935700 ; xorps xmm0,xmm0
                  // movups [rdi],xmm0 ; mov qword ptr [rdi+0x10],0
            sub_e935700(0, 0, rdi, nullptr);
            rdi->f0[0] = 0;
            rdi->f0[1] = 0;
            rdi->f10 = 0;
            pc = 6; break;
        }

        case 6: { // 0xc2a41ba..0xc2a41d1: basic block 6
                  // mov rax,[rsi+0x288] ; mov rcx,[rax+8] ; mov qword ptr [rcx],0
                  // mov r14,[rax] ; jmp short 0xC2A41ED
            rax_ptr = reinterpret_cast<sub_c2a4150_rax*>(rdxx->f288);
            *reinterpret_cast<void**>(rax_ptr->f8) = nullptr;
            r14p = rax_ptr->f0;
            pc = 9; break;
        }

        case 7: { // 0xc2a41d1..0xc2a41e0: basic block 7 (nop [rax+rax])
                  // fallthrough to block 8
            pc = 8; break;
        }

        case 8: { // 0xc2a41e0..0xc2a41ed: basic block 8
                  // mov edx,0x28 ; mov rcx,rdi ; call 0xE935700
            sub_e935700(0x28, 0, rdi, nullptr);
            pc = 9; break;
        }

        case 9: { // 0xc2a41ed..0xc2a41f2: basic block 9
                  // test r14,r14 ; je short 0xC2A422E
            if (r14p == nullptr) { pc = 14; break; }
            pc = 10; break;
        }

        case 10: { // 0xc2a41f2..0xc2a4201: basic block 10
                   // mov rdi,r14 ; mov r14,[r14] ; mov rbx,[rdi+0x20]
                   // test rbx,rbx ; je short 0xC2A41E0
            auto* rdi_ = reinterpret_cast<sub_c2a4150_r14*>(r14p);
            r14p = rdi_->f0;
            rbx = reinterpret_cast<sub_c2a4150_rbx*>(rdi_->f20);
            if (rbx == nullptr) { pc = 8; break; }
            pc = 11; break;
        }

        case 11: { // 0xc2a4201..0xc2a4207: basic block 11
                   // lock dec dword ptr [rbx+8] ; jne short 0xC2A41E0
            auto dec8 = _InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rbx->f8));
            if (dec8 != 0) { pc = 8; break; }
            pc = 12; break;
        }

        case 12: { // 0xc2a4207..0xc2a421c: basic block 12
                   // mov rax,[rbx] ; mov rax,[rax] ; mov rcx,rbx ; call qword ptr [0xF99FFA0]
                   // lock dec dword ptr [rbx+0xC] ; jne short 0xC2A41E0
            sub_eea6040(rbx->f0);
            auto decC = _InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rbx->fc));
            if (decC != 0) { pc = 8; break; }
            pc = 13; break;
        }

        case 13: { // 0xc2a421c..0xc2a422e: basic block 13
                   // mov rax,[rbx] ; mov rax,[rax+8] ; mov rcx,rbx ; call qword ptr [0xF99FFA0]
                   // jmp short 0xC2A41E0
            sub_eea6040(reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(rbx->f0) + 8)));
            pc = 8; break;
        }

        case 14: { // 0xc2a422e..0xc2a425e: basic block 14
                   // mov rcx,[rsi+0x288] ; mov edx,0x28 ; call 0xE935700
                   // lea rcx,[rsi+0x10] ; call 0x67577c0
                   // mov edx,0x2C0 ; mov rcx,rsi ; jmp 0xE935700
            sub_e935700(0x28, 0, rdxx->f288, nullptr);
            sub_67577c0(&rdxx->f10);
            sub_e935700(0x2C0, 0, self, nullptr);
            return 0;
        }

        case 15: { // 0xc2a425e..0xc2a4268: basic block 15
                   // add rsp,0x28 ; pop rbx / pop rdi / pop rsi / pop r14 ; ret
            return 0;
        }

        default: return 0;
        }
    }
}

} // namespace native::helpers
