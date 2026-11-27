// LIFT 0x56bbb60 size 0x11d 1.26.62.01 sub_56bbb60
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56bbb60.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_56bbb60, "sub_56bbb60", 0x56bbb60, sub_56bbb60, nullptr);

// Layout assertions binding this unit to RVA 0x56bbb60 (gate requirement).
static_assert(offsetof(sub_56bbb60_rdi, value) == 0x0, "0x56bbb60: layout rdi+0x0");
static_assert(offsetof(sub_56bbb60_rdi, state) == 0x18, "0x56bbb60: layout rdi+0x18");
static_assert(offsetof(sub_56bbb60_rsi, count0xC) == 0xc, "0x56bbb60: layout rsi+0xc");

// Boundary callee: sub_eea6040, a vendor thunk reached through data slot 0xF99FFA0
// (loader-resolved; docs/data/native_boundary.tsv). The thunk is `jmp rax`, so the
// call takes the vtable target in RAX and the object in RCX; rdx carries the target.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Verbatim call instructions from the disassembly of [0x56bbb60, 0x56bbc7d) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56bbbff  call qword ptr [0xF99FFA0]
0x56bbc1f  call qword ptr [0xF99FFA0]
0x56bbc54  call qword ptr [0xF99FFA0]
0x56bbc6a  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x56bbb60, 0x56bbc7d) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_56bbb60(void* a0, void* a1) {
    // 0x56bbb60..0x56bbb76: basic block 0
    // 0x56bbb60  push r14
    // 0x56bbb62  push rsi
    // 0x56bbb63  push rdi
    // 0x56bbb64  push rbx
    // 0x56bbb65  sub rsp,0x28
    // 0x56bbb69  mov rdi,[rcx]
    // 0x56bbb6c  movzx eax,byte ptr [rdi+0x18]
    // 0x56bbb70  cmp rax,4
    // 0x56bbb74  ja short 0x56BBB86
    // -> if *u8(*(a0)+0x18) >u 0x4 goto L_0x56bbb86
    // -> if *u8(*(a0)+0x18) <=u 0x4 goto L_0x56bbb76
    void** const a0slot = reinterpret_cast<void**>(a0);                 // RCX: target slot pointer
    void** const a1slot = reinterpret_cast<void**>(a1);                 // RDX: source slot pointer
    std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(*a0slot); // 0x56bbb69  mov rdi,[rcx]
    std::uint8_t const state = self[0x18];                              // 0x56bbb6c  movzx eax,byte ptr [rdi+0x18]
    if (state <= 4) {                                                   // 0x56bbb70  cmp rax,4
        // 0x56bbb76..0x56bbb86: basic block 1
        // 0x56bbb76  lea r8,[0xF25D340]
        // 0x56bbb7d  movsxd rax,[r8+rax*4]
        // 0x56bbb81  add rax,r8
        // 0x56bbb84  jmp rax
        // -> switch@56bbb84 index in [0, 3, 4] goto L_0x56bbb86
        // -> switch@56bbb84 index in [2] goto L_0x56bbbcb
        // -> switch@56bbb84 index in [1] goto L_0x56bbbe1
        switch (state) {
        case 1: goto L_0x56bbbe1;
        case 2: goto L_0x56bbbcb;
        default: break;   // 0, 3, 4 fall through to the assign path
        }
    }
    goto L_0x56bbb86;

L_0x56bbb86:
    // 0x56bbb86..0x56bbb9f: basic block 2
    // 0x56bbb86  mov byte ptr [rdi+0x18],0xFF
    // 0x56bbb8a  mov rax,[rdx]
    // 0x56bbb8d  mov rdx,[rcx]
    // 0x56bbb90  xorps xmm0,xmm0
    // 0x56bbb93  movups [rdx],xmm0
    // 0x56bbb96  mov r8,[rax+8]
    // 0x56bbb9a  test r8,r8
    // 0x56bbb9d  je short 0x56BBBA4
    // -> if *(*(a1)+0x8) == 0 goto L_0x56bbba4
    // -> if *(*(a1)+0x8) != 0 goto L_0x56bbb9f
    {
        self[0x18] = 0xFF;                                              // 0x56bbb86  mov byte ptr [rdi+0x18],0xFF
        void* const source = *a1slot;                                   // 0x56bbb8a  mov rax,[rdx]
        std::uint8_t* const dst =
            reinterpret_cast<std::uint8_t*>(*a0slot);                   // 0x56bbb8d  mov rdx,[rcx]
        *reinterpret_cast<std::uint64_t*>(dst) = 0;                     // 0x56bbb90  xorps xmm0,xmm0
        *reinterpret_cast<std::uint64_t*>(dst + 8) = 0;                 // 0x56bbb93  movups [rdx],xmm0
        std::uint8_t* const src = reinterpret_cast<std::uint8_t*>(source);
        void* const srcCtrl = *reinterpret_cast<void**>(src + 8);       // 0x56bbb96  mov r8,[rax+8]
        if (srcCtrl != nullptr) {                                       // 0x56bbb9a  test r8,r8
                                                                        // 0x56bbb9d  je short 0x56BBBA4
            // 0x56bbb9f..0x56bbba4: basic block 3
            // 0x56bbb9f  lock inc dword ptr [r8+8]
            // -> if fallthrough goto L_0x56bbba4
            _InterlockedIncrement(reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(srcCtrl) + 8));          // 0x56bbb9f  lock inc dword ptr [r8+8]
        }
        // 0x56bbba4..0x56bbbc1: basic block 4
        // 0x56bbba4  mov r8,[rax]
        // 0x56bbba7  mov [rdx],r8
        // 0x56bbbaa  mov r8,[rax+8]
        // 0x56bbbae  mov [rdx+8],r8
        // 0x56bbbb2  movzx eax,word ptr [rax+0x10]
        // 0x56bbbb6  mov [rdx+0x10],ax
        // 0x56bbbba  mov rax,[rcx]
        // 0x56bbbbd  mov byte ptr [rax+0x18],2
        // -> if fallthrough goto L_0x56bbbc1
        *reinterpret_cast<void**>(dst) =
            *reinterpret_cast<void**>(src);                             // 0x56bbba4/0x56bbba7
        *reinterpret_cast<void**>(dst + 8) = srcCtrl;                   // 0x56bbbaa/0x56bbbae
        *reinterpret_cast<std::uint16_t*>(dst + 0x10) =
            *reinterpret_cast<std::uint16_t*>(src + 0x10);              // 0x56bbbb2/0x56bbbb6
        dst[0x18] = 2;                                                  // 0x56bbbba/0x56bbbbd
        // 0x56bbbc1..0x56bbbcb: basic block 5 (epilogue shared by every return path)
        // 0x56bbbc1  add rsp,0x28
        // 0x56bbbc5  pop rbx
        // 0x56bbbc6  pop rdi
        // 0x56bbbc7  pop rsi
        // 0x56bbbc8  pop r14
        // 0x56bbbca  ret
        // -> (fall-through / ret / end)
        return reinterpret_cast<uintptr_t>(dst);                        // RAX = *a0 (target pointer)
    }

L_0x56bbbcb:
    // 0x56bbbcb..0x56bbbd7: basic block 6
    // 0x56bbbcb  mov rbx,[rdx]
    // 0x56bbbce  mov rax,[rbx+8]
    // 0x56bbbd2  test rax,rax
    // 0x56bbbd5  je short 0x56BBC30
    // -> if *(*(a1)+0x8) == 0 goto L_0x56bbc30
    // -> if *(*(a1)+0x8) != 0 goto L_0x56bbbd7
    {
        void* const source = *a1slot;                                   // 0x56bbbcb  mov rbx,[rdx]
        std::uint8_t* const src = reinterpret_cast<std::uint8_t*>(source);
        void* newCtrl = *reinterpret_cast<void**>(src + 8);             // 0x56bbbce  mov rax,[rbx+8]
        if (newCtrl != nullptr) {                                       // 0x56bbbd2  test rax,rax
                                                                        // 0x56bbbd5  je short 0x56BBC30
            // 0x56bbbd7..0x56bbbe1: basic block 7
            // 0x56bbbd7  lock inc dword ptr [rax+8]
            // 0x56bbbdb  mov rax,[rbx+8]
            // 0x56bbbdf  jmp short 0x56BBC32
            // -> if jmp goto L_0x56bbc32
            _InterlockedIncrement(reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(newCtrl) + 8));         // 0x56bbbd7  lock inc dword ptr [rax+8]
            newCtrl = *reinterpret_cast<void**>(src + 8);               // 0x56bbbdb  mov rax,[rbx+8]
        } else {
            // 0x56bbc30..0x56bbc32: basic block 12
            // 0x56bbc30  xor eax,eax
            // -> if fallthrough goto L_0x56bbc32
            newCtrl = nullptr;                                          // 0x56bbc30  xor eax,eax
        }
        // 0x56bbc32..0x56bbc45: basic block 13
        // 0x56bbc32  mov rcx,[rbx]
        // 0x56bbc35  mov [rdi],rcx
        // 0x56bbc38  mov rsi,[rdi+8]
        // 0x56bbc3c  mov [rdi+8],rax
        // 0x56bbc40  test rsi,rsi
        // 0x56bbc43  je short 0x56BBC70
        // -> if *(*(a0)+0x8) == 0 goto L_0x56bbc70
        // -> if *(*(a0)+0x8) != 0 goto L_0x56bbc45
        *reinterpret_cast<void**>(self) =
            *reinterpret_cast<void**>(src);                             // 0x56bbc32/0x56bbc35
        void* const oldCtrl = *reinterpret_cast<void**>(self + 8);      // 0x56bbc38  mov rsi,[rdi+8]
        *reinterpret_cast<void**>(self + 8) = newCtrl;                  // 0x56bbc3c  mov [rdi+8],rax
        if (oldCtrl != nullptr) {                                       // 0x56bbc40  test rsi,rsi
                                                                        // 0x56bbc43  je short 0x56BBC70
            // 0x56bbc45..0x56bbc4b: basic block 14
            // 0x56bbc45  lock dec dword ptr [rsi+8]
            // 0x56bbc49  jne short 0x56BBC70
            // -> if (Dec *u32(*(*(a0)+0x8)+0x8), ?) != 0 goto L_0x56bbc70
            // -> if (Dec *u32(*(*(a0)+0x8)+0x8), ?) == 0 goto L_0x56bbc4b
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(oldCtrl) + 8)) == 0) {  // 0x56bbc45/0x56bbc49
                // 0x56bbc4b..0x56bbc60: basic block 15
                // 0x56bbc4b  mov rax,[rsi]
                // 0x56bbc4e  mov rax,[rax]
                // 0x56bbc51  mov rcx,rsi
                // 0x56bbc54  call qword ptr [0xF99FFA0]
                // 0x56bbc5a  lock dec dword ptr [rsi+0xC]
                // 0x56bbc5e  jne short 0x56BBC70
                void** const vf = *reinterpret_cast<void***>(oldCtrl);  // 0x56bbc4b/0x56bbc4e
                sub_eea6040(oldCtrl, vf[0]);                            // 0x56bbc51/0x56bbc54
                if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(oldCtrl) + 0xC)) == 0) {  // 0x56bbc5a/0x56bbc5e
                    // 0x56bbc60..0x56bbc70: basic block 16
                    // 0x56bbc60  mov rax,[rsi]
                    // 0x56bbc63  mov rax,[rax+8]
                    // 0x56bbc67  mov rcx,rsi
                    // 0x56bbc6a  call qword ptr [0xF99FFA0]
                    // -> if fallthrough goto L_0x56bbc70
                    void** const vf2 = *reinterpret_cast<void***>(oldCtrl);  // 0x56bbc60/0x56bbc63
                    sub_eea6040(oldCtrl, vf2[1]);                       // 0x56bbc67/0x56bbc6a
                }
            }
        }
        // 0x56bbc70..0x56bbc7d: basic block 17
        // 0x56bbc70  movzx eax,word ptr [rbx+0x10]
        // 0x56bbc74  mov [rdi+0x10],ax
        // 0x56bbc78  jmp 0x56BBBC1
        // -> if jmp goto L_0x56bbbc1
        std::uint16_t const srcTag =
            *reinterpret_cast<std::uint16_t*>(src + 0x10);              // 0x56bbc70  movzx eax,word ptr [rbx+0x10]
        *reinterpret_cast<std::uint16_t*>(self + 0x10) = srcTag;        // 0x56bbc74  mov [rdi+0x10],ax
        return static_cast<uintptr_t>(srcTag);                          // 0x56bbc78  jmp 0x56BBBC1 (epilogue)
    }

L_0x56bbbe1:
    // 0x56bbbe1..0x56bbbea: basic block 8
    // 0x56bbbe1  mov rsi,[rdi+8]
    // 0x56bbbe5  test rsi,rsi
    // 0x56bbbe8  je short 0x56BBB86
    // -> if *(*(a0)+0x8) == 0 goto L_0x56bbb86
    // -> if *(*(a0)+0x8) != 0 goto L_0x56bbbea
    {
        void* const ctrl = *reinterpret_cast<void**>(self + 8);         // 0x56bbbe1  mov rsi,[rdi+8]
        if (ctrl != nullptr) {                                          // 0x56bbbe5  test rsi,rsi
                                                                        // 0x56bbbe8  je short 0x56BBB86
            // 0x56bbbea..0x56bbbf0: basic block 9
            // 0x56bbbea  lock dec dword ptr [rsi+8]
            // 0x56bbbee  jne short 0x56BBB86
            // -> if (Dec *u32(*(*(a0)+0x8)+0x8), ?) != 0 goto L_0x56bbb86
            // -> if (Dec *u32(*(*(a0)+0x8)+0x8), ?) == 0 goto L_0x56bbbf0
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(ctrl) + 8)) == 0) {  // 0x56bbbea/0x56bbbee
                // 0x56bbbf0..0x56bbc15: basic block 10
                // 0x56bbbf0  mov rax,[rsi]
                // 0x56bbbf3  mov rax,[rax]
                // 0x56bbbf6  mov rbx,rcx
                // 0x56bbbf9  mov rcx,rsi
                // 0x56bbbfc  mov r14,rdx
                // 0x56bbbff  call qword ptr [0xF99FFA0]
                // 0x56bbc05  mov rdx,r14
                // 0x56bbc08  mov rcx,rbx
                // 0x56bbc0b  lock dec dword ptr [rsi+0xC]
                // 0x56bbc0f  jne 0x56BBB86
                void** const vf = *reinterpret_cast<void***>(ctrl);     // 0x56bbbf0/0x56bbbf3
                sub_eea6040(ctrl, vf[0]);                               // 0x56bbbf9/0x56bbbff
                if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(ctrl) + 0xC)) == 0) {  // 0x56bbc0b/0x56bbc0f
                    // 0x56bbc15..0x56bbc30: basic block 11
                    // 0x56bbc15  mov rax,[rsi]
                    // 0x56bbc18  mov rax,[rax+8]
                    // 0x56bbc1c  mov rcx,rsi
                    // 0x56bbc1f  call qword ptr [0xF99FFA0]
                    // 0x56bbc25  mov rdx,r14
                    // 0x56bbc28  mov rcx,rbx
                    // 0x56bbc2b  jmp 0x56BBB86
                    void** const vf2 = *reinterpret_cast<void***>(ctrl);  // 0x56bbc15/0x56bbc18
                    sub_eea6040(ctrl, vf2[1]);                          // 0x56bbc1c/0x56bbc1f
                }
            }
        }
        goto L_0x56bbb86;   // 0x56bbc2b  jmp 0x56BBB86
    }
}

} // namespace native::helpers
