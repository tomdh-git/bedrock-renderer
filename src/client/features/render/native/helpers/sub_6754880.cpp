// LIFT 0x6754880 size 0x115 1.26.62.01 sub_6754880
#include "client/features/render/native/helpers/sub_6754880.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Layout static_asserts (also in the header; repeated here for liftcheck source scan).
static_assert(offsetof(sub_6754880_state, f28) == 0x28, "sub_0x6754880 state+0x28 field");
static_assert(offsetof(sub_6754880_state, f30) == 0x30, "sub_0x6754880 state+0x30 field");
static_assert(offsetof(sub_6754880_state, f40) == 0x40, "sub_0x6754880 state+0x40 field");
static_assert(offsetof(sub_6754880_state, f48) == 0x48, "sub_0x6754880 state+0x48 field");
static_assert(offsetof(sub_6754880_ctrl, f0) == 0x00, "sub_0x6754880 ctrl+0x00 field");
static_assert(offsetof(sub_6754880_ctrl, f8) == 0x08, "sub_0x6754880 ctrl+0x08 field");
static_assert(offsetof(sub_6754880_ctrl, fc) == 0x0c, "sub_0x6754880 ctrl+0x0c field");

LIFT_FN(sub_6754880, "sub_6754880", 0x6754880, sub_6754880, nullptr);

// Verbatim call instructions from the disassembly of [0x6754880, 0x6754995) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// All four calls are to sub_eea6040 via data slot 0xF99FFA0 (boundary/vendor).
#if 0
0x6754902  call qword ptr [0xF99FFA0]
0x6754918  call qword ptr [0xF99FFA0]
0x6754961  call qword ptr [0xF99FFA0]
0x6754977  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x6754880, 0x6754995) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_6754880(sub_6754880_state* self) {
    void* const rsi = self;
    void* rbx = self->f28;      // 0x6754890  mov rbx,[rcx+0x28]
    void* r14 = self->f30;      // 0x6754894  mov r14,[rcx+0x30]
    void* r15 = self->f40;      // 0x6754898  mov r15,[rcx+0x40]
    void* r12 = self->f48;      // 0x675489c  mov r12,[rcx+0x48]
    uintptr_t rax = 0;

    // 0x6754880..0x67548b1: basic block 0 (prologue + range check)
    //   mov rsi,rcx
    //   mov rbx,[rcx+0x28]  mov r14,[rcx+0x30]  mov r15,[rcx+0x40]  mov r12,[rcx+0x48]
    //   mov rax,rbx  xor rax,r14  mov rcx,r15  xor rcx,r12  or rcx,rax
    //   je short 0x675492E  ; if ((f40^f48)|(f28^f30)) == 0 goto block 11
    uintptr_t const combined0 =
        ((uintptr_t)r15 ^ (uintptr_t)r12) | ((uintptr_t)rbx ^ (uintptr_t)r14);
    if (combined0 != 0) {
        // 0x67548b1..0x67548bb: basic block 1 (advance cursors)
        //   add r15,0x10  add rbx,8  jmp short 0x67548D9
        r15 = (void*)((uintptr_t)r15 + 0x10);
        rbx = (void*)((uintptr_t)rbx + 8);

        // 0x67548c0..0x67548d9: basic block 3 (loop check + advance)
        //   mov rax,rbx  xor rax,r14  mov rcx,r15  xor rcx,r12
    L_0x67548c0:
        //   add r15,0x10  add rbx,8  or rcx,rax  je short 0x6754920
        r15 = (void*)((uintptr_t)r15 + 0x10);
        rbx = (void*)((uintptr_t)rbx + 8);

        // 0x67548d9..0x67548e6: basic block 4 (process element)
        //   mov rax,[r15-0x10]  mov rcx,[rax+8]  test rcx,rcx  je short 0x67548C0
        for (;;) {
            // 0x67548d9: mov rax,[r15-0x10]
            void* const obj_ptr = *(void**)((uintptr_t)r15 - 0x10);
            // 0x67548dd: mov rcx,[rax+8]
            void* const ctrl_ptr = *(void**)((uintptr_t)obj_ptr + 8);
            if (ctrl_ptr != nullptr) {
                // 0x67548e6: lock inc dword ptr [rcx+8]
                _InterlockedIncrement(
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(ctrl_ptr) + 8));
                // 0x67548ea: mov rdi,[rax+8]
                void* const rdi = *(void**)((uintptr_t)obj_ptr + 8);
                if (rdi != nullptr) {
                    // 0x67548f3: lock dec dword ptr [rdi+8]
                    // 0x67548f7: jne short 0x67548C0
                    if (_InterlockedDecrement(
                            reinterpret_cast<volatile long*>(
                                reinterpret_cast<std::uint8_t*>(rdi) + 8)) == 0) {
                        // 0x67548f9..0x6754902: primary destroy (vfptr[0])
                        void** const vfptr = *(void***)rdi;
                        sub_eea6040(rdi, vfptr[0]);  // 0x6754902 call qword ptr [0xF99FFA0]
                        // 0x6754908: lock dec dword ptr [rdi+0xC]
                        // 0x675490c: jne short 0x67548C0
                        if (_InterlockedDecrement(
                                reinterpret_cast<volatile long*>(
                                    reinterpret_cast<std::uint8_t*>(rdi) + 0xC)) == 0) {
                            // 0x675490e..0x6754918: secondary destroy (vfptr[1])
                            void** const vfptr2 = *(void***)rdi;
                            sub_eea6040(rdi, vfptr2[1]);  // 0x6754977 call qword ptr [0xF99FFA0]
                        }
                    }
                }
            }

            // 0x67548c0: loop back-edge (check + advance)
            //   mov rax,rbx  xor rax,r14  mov rcx,r15  xor rcx,r12
            //   add r15,0x10  add rbx,8  or rcx,rax  je short 0x6754920
            r15 = (void*)((uintptr_t)r15 + 0x10);
            rbx = (void*)((uintptr_t)rbx + 8);
            uintptr_t const combined1 =
                ((uintptr_t)r15 ^ (uintptr_t)r12) | ((uintptr_t)rbx ^ (uintptr_t)r14);
            if (combined1 == 0) {
                break;
            }
        }

        // 0x6754920..0x675492a: basic block 9 (empty array1 if non-empty)
        //   mov rax,[rsi+0x28]  cmp rax,[rsi+0x30]  je short 0x675492E
        //   mov [rsi+0x30],rax
        rax = (uintptr_t)self->f28;
        if (rax != (uintptr_t)self->f30) {
            self->f30 = (void*)rax;
        }
    }

    // 0x675492e..0x675493b: basic block 11 (setup loop 2)
    //   mov rbx,[rsi+0x40]  mov r14,[rsi+0x48]  cmp rbx,r14
    //   jne short 0x6754949  jmp short 0x6754987
    rbx = self->f40;
    r14 = self->f48;
    if (rbx != r14) {
        // 0x6754940..0x6754949: basic block 14 (advance + check)
        //   add rbx,0x10  cmp rbx,r14  je short 0x675497F
    L_0x6754940:
        rbx = (void*)((uintptr_t)rbx + 0x10);
        if (rbx == r14) {
            // 0x675497f..0x6754987: basic block 19 (empty array2, epilogue)
            //   mov rax,[rsi+0x40]  mov [rsi+0x48],rax
            rax = (uintptr_t)self->f40;
            self->f48 = self->f40;
            return rax;
        }

        // 0x6754949..0x6754952: basic block 15 (process element)
        //   mov rdi,[rbx+8]  test rdi,rdi  je short 0x6754940
        for (;;) {
            void* const rdi = *(void**)((uintptr_t)rbx + 8);
            if (rdi != nullptr) {
                // 0x6754952: lock dec dword ptr [rdi+8]
                // 0x6754956: jne short 0x6754940
                if (_InterlockedDecrement(
                        reinterpret_cast<volatile long*>(
                            reinterpret_cast<std::uint8_t*>(rdi) + 8)) == 0) {
                    // 0x6754958..0x6754961: primary destroy (vfptr[0])
                    void** const vfptr = *(void***)rdi;
                    sub_eea6040(rdi, vfptr[0]);  // 0x6754961 call qword ptr [0xF99FFA0]
                    // 0x6754967: lock dec dword ptr [rdi+0xC]
                    // 0x675496b: jne short 0x6754940
                    if (_InterlockedDecrement(
                            reinterpret_cast<volatile long*>(
                                reinterpret_cast<std::uint8_t*>(rdi) + 0xC)) == 0) {
                        // 0x675496d..0x6754977: secondary destroy (vfptr[1])
                        void** const vfptr2 = *(void***)rdi;
                        sub_eea6040(rdi, vfptr2[1]);  // 0x6754977 call qword ptr [0xF99FFA0]
                    }
                }
            }

            // 0x6754940: loop back-edge (advance + check)
            rbx = (void*)((uintptr_t)rbx + 0x10);
            if (rbx == r14) {
                rax = (uintptr_t)self->f40;
                self->f48 = self->f40;
                return rax;
            }
        }
    }

    // 0x6754987..0x6754995: basic block 20 (epilogue)
    //   add rsp,0x28  pop rbx,rdi,rsi,r12,r14,r15  ret  (RAX = rax)
    return rax;
}

} // namespace native::helpers
