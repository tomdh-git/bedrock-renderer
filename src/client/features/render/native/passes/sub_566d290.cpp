// LIFT 0x566d290 size 0xbd 1.26.62.01 sub_566d290
#include "sub_566d290.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_566d290 (0x566d290, size 0xbd, 1.26.62.01).
//
// Full instruction-by-instruction reversal:
//   0x566d290..0x566d299  push r14; push rsi; push rdi; push rbx; sub rsp,0x28
//   0x566d299             mov rsi,rcx
//   ... (all instructions)
//   0x566d34c             ret
//
// Reads: this+0x38 (byte), this+0x30 (ptr), *this+0x30 (vfptr), vfptr+0 (destructor), vfptr+8 (deallocator),
//   this+0x30+0x8 (refcount), this+0x30+0xC (count0xC),
//   this+0x8 (array start), this+0x10 (array end),
//   elem+0x18 (byte flag), elem+0x8 (ptr), *elem+0x8 (vfptr), vfptr+0, vfptr+8,
//   elem+0x8+0x8 (refcount), elem+0x8+0xC (count0xC)
// Writes: *this+0x30+0x8 (lock dec), *this+0x30+0xC (lock dec),
//   *elem+0x8+0x8 (lock dec), *elem+0x8+0xC (lock dec),
//   [this+0x8, this+0x20) (zero 0x18 bytes)
// Calls: 4x virtual calls via data slot 0xF99FFA0 (sub_eea6040, boundary/vendor)
// Return: void

// 0x566d290..0x566d34d
void sub_566d290(void* a0)
{
    static_assert(sizeof(void*) == 8, "sub_566d290: x64 pointers and arguments are 8 bytes");
    using DestroyFn = void (*)(void*);
    void* const thisObj = a0;  // RCX = this

    // 0x566d290..0x566d299  prologue: push r14; push rsi; push rdi; push rbx; sub rsp,0x28
    // 0x566d299             mov rsi,rcx
    void* rsi = thisObj;   // 0x566d299  mov rsi,rcx

    // 0x566d29c  cmp byte ptr [rcx+0x38],3
    // 0x566d2a0  jne short 0x566D2D6
    if (*reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uint8_t*>(thisObj) + kThisOffset0x38) == 3) {  // 0x566d29c  cmp byte ptr [rcx+0x38],3
                                                                                   // 0x566d2a0  jne short 0x566D2D6
        // 0x566d2a2  mov rdi,[rsi+0x30]
        // 0x566d2a6  test rdi,rdi
        // 0x566d2a9  je short 0x566D2D6
        void* const obj30 =
            *reinterpret_cast<void**>(
                reinterpret_cast<std::uint8_t*>(thisObj) + kThisOffset0x30);  // 0x566d2a2  mov rdi,[rsi+0x30]
        if (obj30 != nullptr) {                                                // 0x566d2a6  test rdi,rdi
                                                                                 // 0x566d2a9  je short 0x566D2D6
            // 0x566d2ab  lock dec dword ptr [rdi+8]
            // 0x566d2af  jne short 0x566D2D6
            if (_InterlockedDecrement(
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(obj30) + kRefcountedOffsetRefcount)) == 0) {  // 0x566d2ab  lock dec dword ptr [rdi+8]
                                                                                                       // 0x566d2af  jne short 0x566D2D6
                // 0x566d2b1  mov rax,[rdi]
                // 0x566d2b4  mov rax,[rax]
                // 0x566d2b7  mov rcx,rdi
                // 0x566d2ba  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (vfptr[0])
                void** const vfptr30 = *reinterpret_cast<void***>(obj30);  // 0x566d2b1  mov rax,[rdi]
                                                                               // 0x566d2b4  mov rax,[rax]
                DestroyFn destroy30 = reinterpret_cast<DestroyFn>(vfptr30[0]);  // 0x566d2b4  mov rax,[rax]
                destroy30(obj30);   // 0x566d2b7  mov rcx,rdi
                                      // 0x566d2ba  call qword ptr [0xF99FFA0]

                // 0x566d2c0  lock dec dword ptr [rdi+0xC]
                // 0x566d2c4  jne short 0x566D2D6
                if (_InterlockedDecrement(
                        reinterpret_cast<volatile long*>(
                            reinterpret_cast<std::uint8_t*>(obj30) + kRefcountedOffsetCount0xC)) == 0) {  // 0x566d2c0  lock dec dword ptr [rdi+0xC]
                                                                                                           // 0x566d2c4  jne short 0x566D2D6
                    // 0x566d2c6  mov rax,[rdi]
                    // 0x566d2c9  mov rax,[rax+8]
                    // 0x566d2cd  mov rcx,rdi
                    // 0x566d2d0  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (vfptr[8])
                    DestroyFn dealloc30 = reinterpret_cast<DestroyFn>(vfptr30[1]);  // 0x566d2c6  mov rax,[rdi]
                                                                                      // 0x566d2c9  mov rax,[rax+8]
                    dealloc30(obj30);   // 0x566d2cd  mov rcx,rdi)
                                          // 0x566d2d0  call qword ptr [0xF99FFA0]
                }
            }
        }
    }

    // loc_566d2d6:
    // 0x566d2d6  mov rbx,[rsi+8]
    // 0x566d2da  test rbx,rbx
    // 0x566d2dd  je short 0x566D343
    void* const arrayStart =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(rsi) + kThisOffset0x08);  // 0x566d2d6  mov rbx,[rsi+8]
    if (arrayStart == nullptr) {                                       // 0x566d2da  test rbx,rbx
                                                                         // 0x566d2dd  je short 0x566D343
        return;                                                        // 0x566d343 ... epilogue
    }

    // 0x566d2df  mov r14,[rsi+0x10]
    // 0x566d2e3  add rsi,8
    // 0x566d2e7  jmp short 0x566D2F4
    void* const arrayEnd =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(rsi) + kThisOffset0x10);  // 0x566d2df  mov r14,[rsi+0x10]
    void* rbx = arrayStart;                                            // rbx = arrayStart (from 0x566d2d6)
    rsi = reinterpret_cast<std::uint8_t*>(rsi) + 8;                    // 0x566d2e3  add rsi,8

    // 0x566d2f4  cmp rbx,r14
    // 0x566d2f7  je short 0x566D335
    while (rbx != arrayEnd) {                                          // 0x566d2f4  cmp rbx,r14
                                                                         // 0x566d2f7  je short 0x566D335
        // 0x566d2f9  cmp byte ptr [rbx+0x18],2
        // 0x566d2fd  jne short 0x566D2F0
        if (*reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uint8_t*>(rbx) + kElemOffset0x18) == 2) {  // 0x566d2f9  cmp byte ptr [rbx+0x18],2
                                                                                   // 0x566d2fd  jne short 0x566D2F0
            // 0x566d2ff  mov rdi,[rbx+8]
            // 0x566d303  test rdi,rdi
            // 0x566d306  je short 0x566D2F0
            void* const obj8 =
                *reinterpret_cast<void**>(
                    reinterpret_cast<std::uint8_t*>(rbx) + kElemOffset0x08);  // 0x566d2ff  mov rdi,[rbx+8]
            if (obj8 != nullptr) {                                            // 0x566d303  test rdi,rdi
                                                                                 // 0x566d306  je short 0x566D2F0
                // 0x566d308  lock dec dword ptr [rdi+8]
                // 0x566d30c  jne short 0x566D2F0
                if (_InterlockedDecrement(
                        reinterpret_cast<volatile long*>(
                            reinterpret_cast<std::uint8_t*>(obj8) + kRefcountedOffsetRefcount)) == 0) {  // 0x566d308  lock dec dword ptr [rdi+8]
                                                                                                          // 0x566d30c  jne short 0x566D2F0
                    // 0x566d30e  mov rax,[rdi]
                    // 0x566d311  mov rax,[rax]
                    // 0x566d314  mov rcx,rdi
                    // 0x566d317  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (vfptr[0])
                    void** const vfptr8 = *reinterpret_cast<void***>(obj8);  // 0x566d30e  mov rax,[rdi]
                                                                                 // 0x566d311  mov rax,[rax]
                    DestroyFn destroy8 = reinterpret_cast<DestroyFn>(vfptr8[0]);  // 0x566d311  mov rax,[rax]
                    destroy8(obj8);   // 0x566d314  mov rcx,rdi
                                        // 0x566d317  call qword ptr [0xF99FFA0]

                    // 0x566d31d  lock dec dword ptr [rdi+0xC]
                    // 0x566d321  jne short 0x566D2F0
                    if (_InterlockedDecrement(
                            reinterpret_cast<volatile long*>(
                                reinterpret_cast<std::uint8_t*>(obj8) + kRefcountedOffsetCount0xC)) == 0) {  // 0x566d31d  lock dec dword ptr [rdi+0xC]
                                                                                                            // 0x566d321  jne short 0x566D2F0
                        // 0x566d323  mov rax,[rdi]
                        // 0x566d326  mov rax,[rax+8]
                        // 0x566d32a  mov rcx,rdi
                        // 0x566d32d  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (vfptr[8])
                        DestroyFn dealloc8 = reinterpret_cast<DestroyFn>(vfptr8[1]);  // 0x566d323  mov rax,[rdi]
                                                                                      // 0x566d326  mov rax,[rax+8]
                        dealloc8(obj8);   // 0x566d32a  mov rcx,rdi)
                                              // 0x566d32d  call qword ptr [0xF99FFA0]
                    }
                }
            }
        }

        // loc_566d2f0:
        // 0x566d2f0  add rbx,0x28
        rbx = reinterpret_cast<std::uint8_t*>(rbx) + 0x28;  // 0x566d2f0  add rbx,0x28
    }

    // loc_566d335:
    // 0x566d335  xorps xmm0,xmm0
    // 0x566d338  movups [rsi],xmm0
    // 0x566d33b  mov qword ptr [rsi+0x10],0
    std::uint64_t* const wp = reinterpret_cast<std::uint64_t*>(rsi);  // rsi = this + 8
    wp[0] = 0;                                                      // 0x566d338  movups [rsi],xmm0 (low 8 bytes)
    wp[1] = 0;                                                      // 0x566d338  movups [rsi],xmm0 (high 8 bytes)
    wp[2] = 0;                                                      // 0x566d33b  mov qword ptr [rsi+0x10],0

    // loc_566d343:
    // 0x566d343  add rsp,0x28
    // 0x566d347  pop rbx
    // 0x566d348  pop rdi
    // 0x566d349  pop rsi
    // 0x566d34a  pop r14
    // 0x566d34c  ret
    return;
}

} // namespace native

LIFT_FN(sub_566d290, "sub_566d290", 0x566D290, ::native::sub_566d290, nullptr);

// Verbatim instructions of [0x566d290, 0x566d34d) (rdis dis 0x566d290 0xbd);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x566d290  push r14
0x566d292  push rsi
0x566d293  push rdi
0x566d294  push rbx
0x566d295  sub rsp,0x28
0x566d299  mov rsi,rcx
0x566d29c  cmp byte ptr [rcx+0x38],3
0x566d2a0  jne short 0x566D2D6
0x566d2a2  mov rdi,[rsi+0x30]
0x566d2a6  test rdi,rdi
0x566d2a9  je short 0x566D2D6
0x566d2ab  lock dec dword ptr [rdi+8]
0x566d2af  jne short 0x566D2D6
0x566d2b1  mov rax,[rdi]
0x566d2b4  mov rax,[rax]
0x566d2b7  mov rcx,rdi
0x566d2ba  call qword ptr [0xF99FFA0]
0x566d2c0  lock dec dword ptr [rdi+0xC]
0x566d2c4  jne short 0x566D2D6
0x566d2c6  mov rax,[rdi]
0x566d2c9  mov rax,[rax+8]
0x566d2cd  mov rcx,rdi
0x566d2d0  call qword ptr [0xF99FFA0]
0x566d2d6  mov rbx,[rsi+8]
0x566d2da  test rbx,rbx
0x566d2dd  je short 0x566D343
0x566d2df  mov r14,[rsi+0x10]
0x566d2e3  add rsi,8
0x566d2e7  jmp short 0x566D2F4
0x566d2e9  nop [rax]
0x566d2f0  add rbx,0x28
0x566d2f4  cmp rbx,r14
0x566d2f7  je short 0x566D335
0x566d2f9  cmp byte ptr [rbx+0x18],2
0x566d2fd  jne short 0x566D2F0
0x566d2ff  mov rdi,[rbx+8]
0x566d303  test rdi,rdi
0x566d306  je short 0x566D2F0
0x566d308  lock dec dword ptr [rdi+8]
0x566d30c  jne short 0x566D2F0
0x566d30e  mov rax,[rdi]
0x566d311  mov rax,[rax]
0x566d314  mov rcx,rdi
0x566d317  call qword ptr [0xF99FFA0]
0x566d31d  lock dec dword ptr [rdi+0xC]
0x566d321  jne short 0x566D2F0
0x566d323  mov rax,[rdi]
0x566d326  mov rax,[rax+8]
0x566d32a  mov rcx,rdi
0x566d32d  call qword ptr [0xF99FFA0]
0x566d333  jmp short 0x566D2F0
0x566d335  xorps xmm0,xmm0
0x566d338  movups [rsi],xmm0
0x566d33b  mov qword ptr [rsi+0x10],0
0x566d343  add rsp,0x28
0x566d347  pop rbx
0x566d348  pop rdi
0x566d349  pop rsi
0x566d34a  pop r14
0x566d34c  ret
#endif
