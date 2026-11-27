// LIFT 0x4e01c30 size 0x9d 1.26.62.01 sub_4e01c30
#include "sub_4e01c30.h"

#include <atomic>

namespace native {

// sub_4e01c30 (0x4e01c30, size 0x9d, 1.26.62.01): see sub_4e01c30.h for the
// register/argument map, the layout mirrors and the callee list.
//
// Verbatim instructions of [0x4e01c30, 0x4e01ccd) (matches `rdis dis 0x4e01c30 0x9d`):
#if 0
0x4e01c30  push rsi
0x4e01c31  push rdi
0x4e01c32  sub rsp,0x28
0x4e01c36  lea rax,[0xF2158B8]
0x4e01c3d  movsxd rcx,[rax+rcx*4]
0x4e01c41  add rcx,rax
0x4e01c44  jmp rcx
0x4e01c46  mov rsi,[r8+8]
0x4e01c4a  test rsi,rsi
0x4e01c4d  je short 0x4E01C84
0x4e01c4f  lock dec dword ptr [rsi+8]
0x4e01c53  jne short 0x4E01C84
0x4e01c55  mov rax,[rsi]
0x4e01c58  mov rax,[rax]
0x4e01c5b  mov rcx,rsi
0x4e01c5e  call qword ptr [0xF99FFA0]
0x4e01c64  lock dec dword ptr [rsi+0xC]
0x4e01c68  jne short 0x4E01C84
0x4e01c6a  mov rax,[rsi]
0x4e01c6d  mov rax,[rax+8]
0x4e01c71  mov rdx,[0xF99FFA0]
0x4e01c78  mov rcx,rsi
0x4e01c7b  add rsp,0x28
0x4e01c7f  pop rdi
0x4e01c80  pop rsi
0x4e01c81  jmp rdx
0x4e01c84  add rsp,0x28
0x4e01c88  pop rdi
0x4e01c89  pop rsi
0x4e01c8a  ret
0x4e01c8b  mov rsi,[r8+0x18]
0x4e01c8f  test rsi,rsi
0x4e01c92  je short 0x4E01C46
0x4e01c94  lock dec dword ptr [rsi+8]
0x4e01c98  jne short 0x4E01C46
0x4e01c9a  mov rax,[rsi]
0x4e01c9d  mov rax,[rax]
0x4e01ca0  mov rcx,rsi
0x4e01ca3  mov rdi,r8
0x4e01ca6  call qword ptr [0xF99FFA0]
0x4e01cac  mov r8,rdi
0x4e01caf  lock dec dword ptr [rsi+0xC]
0x4e01cb3  jne short 0x4E01C46
0x4e01cb5  mov rax,[rsi]
0x4e01cb8  mov rax,[rax+8]
0x4e01cbc  mov rcx,rsi
0x4e01cbf  call qword ptr [0xF99FFA0]
0x4e01cc5  mov r8,rdi
0x4e01cc8  jmp 0x4E01C46
#endif

void sub_4e01c30(std::int32_t index, void* a1, void* a2)
{
    // 0x4e01c30  push rsi
    // 0x4e01c31  push rdi
    // 0x4e01c32  sub rsp,0x28
    // Callee-saved frame setup; no stack location is read by this function.

    // 0x4e01c36  lea rax,[0xF2158B8]   ; jump table base (image base 0x140000000 + RVA 0xF2158B8 = VA 0x14F2158B8)
    // 0x4e01c3d  movsxd rcx,[rax+rcx*4]   ; entry = (int32_t)table[index], sign-extended
    // 0x4e01c41  add rcx,rax              ; target = table base + entry
    // 0x4e01c44  jmp rcx                  ; computed tail jump
    // No bounds check: any index reads the table at its real address, so the
    // same bytes the exe reads are read here.
    static const std::int32_t* const kJumpTable =
        reinterpret_cast<const std::int32_t*>(0x14F2158B8ULL);
    void* target = reinterpret_cast<void*>(
        0x14F2158B8ULL +
        static_cast<std::int64_t>(static_cast<std::int32_t>(kJumpTable[index])));

    // 0x4e01c84..0x4e01c8a   shared epilogue: add rsp,0x28; pop rdi; pop rsi; ret
    if (target == reinterpret_cast<void*>(0x144E01C84ULL)) {
        return;   // 0x4e01c44  jmp rcx   -> table entry points at the epilogue
    }

    // 0x4e01c8b..0x4e01cc8   release the object at [a2+0x18], then
    // 0x4e01cc8  jmp 0x4E01C46   joins the [a2+8] release path below.
    if (target == reinterpret_cast<void*>(0x144E01C8BULL)) {
        // 0x4e01c8b  mov rsi,[r8+0x18]   ; obj = a2+0x18
        void* obj = *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a2) + 0x18);
        // 0x4e01c8f  test rsi,rsi   ; 0x4e01c92  je short 0x4E01C46   ; null -> [a2+8] path
        if (obj != nullptr) {
            // 0x4e01c94  lock dec dword ptr [rsi+8]
            // 0x4e01c98  jne short 0x4E01C46   ; result != 0 -> [a2+8] path
            std::atomic<std::uint32_t>* ref8 =
                reinterpret_cast<std::atomic<std::uint32_t>*>(
                    reinterpret_cast<std::uint8_t*>(obj) + 0x8);
            if (ref8->fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                // 0x4e01c9a  mov rax,[rsi]
                // 0x4e01c9d  mov rax,[rax]        ; rax = obj->vfptr[0]
                // 0x4e01ca0  mov rcx,rsi
                // 0x4e01ca3  mov rdi,r8           ; save r8 (the call clobbers volatile R8)
                // 0x4e01ca6  call qword ptr [0xF99FFA0]   ; sub_eea6040 (jmp rax) -> obj->vfptr[0](obj)
                void* method0 = *reinterpret_cast<void**>(
                    reinterpret_cast<std::uint8_t*>(
                        *reinterpret_cast<void**>(obj)));
                ((void(__cdecl*)(void*))method0)(obj);   // 0x4e01ca6  call qword ptr [0xF99FFA0]
                // 0x4e01cac  mov r8,rdi           ; restore r8
                // 0x4e01caf  lock dec dword ptr [rsi+0xC]
                // 0x4e01cb3  jne short 0x4E01C46   ; result != 0 -> [a2+8] path
                std::atomic<std::uint32_t>* refC =
                    reinterpret_cast<std::atomic<std::uint32_t>*>(
                        reinterpret_cast<std::uint8_t*>(obj) + 0xC);
                if (refC->fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                    // 0x4e01cb5  mov rax,[rsi]
                    // 0x4e01cb8  mov rax,[rax+8]   ; rax = obj->vfptr[1]
                    // 0x4e01cbc  mov rcx,rsi
                    // 0x4e01cbf  call qword ptr [0xF99FFA0]   ; sub_eea6040 -> obj->vfptr[1](obj)
                    void* method1 = *reinterpret_cast<void**>(
                        reinterpret_cast<std::uint8_t*>(
                            *reinterpret_cast<void**>(obj)) + 8);
                    ((void(__cdecl*)(void*))method1)(obj);   // 0x4e01cbf  call qword ptr [0xF99FFA0]
                    // 0x4e01cc5  mov r8,rdi   ; restore r8
                    // 0x4e01cc8  jmp 0x4E01C46   -> [a2+8] release path below
                }
            }
        }
        // 0x4e01c92 / 0x4e01c98 / 0x4e01cb3 / 0x4e01cc8 all join here at 0x4e01c46
    } else if (target != reinterpret_cast<void*>(0x144E01C46ULL)) {
        // 0x4e01c44  jmp rcx   — any other table entry tail-jumps to code
        // outside this function with RCX = the target address, RDX = a1,
        // R8 = a2 forwarded unchanged.
        using D0Tail = void(__cdecl*)(void* targetAddress, void* a1, void* a2);
        return ((D0Tail)target)(target, a1, a2);   // 0x4e01c44  jmp rcx
    }
    // target == 0x144E01C46 (or control fell out of the [a2+0x18] path
    // through 0x4e01cc8 jmp 0x4E01C46): release the object at [a2+8].

    // 0x4e01c46..0x4e01c8a   release the object at [a2+8]
    // 0x4e01c46  mov rsi,[r8+8]   ; obj = a2+8
    void* obj = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a2) + 0x8);
    // 0x4e01c4a  test rsi,rsi   ; 0x4e01c4d  je short 0x4E01C84   ; null -> epilogue, ret
    if (obj == nullptr) {
        return;   // 0x4e01c84..0x4e01c8a: add rsp,0x28; pop rdi; pop rsi; ret
    }
    // 0x4e01c4f  lock dec dword ptr [rsi+8]
    // 0x4e01c53  jne short 0x4E01C84   ; result != 0 -> epilogue, ret
    std::atomic<std::uint32_t>* ref8 =
        reinterpret_cast<std::atomic<std::uint32_t>*>(
            reinterpret_cast<std::uint8_t*>(obj) + 0x8);
    if (ref8->fetch_sub(1u, std::memory_order_seq_cst) != 1u) {
        return;   // 0x4e01c84..0x4e01c8a: add rsp,0x28; pop rdi; pop rsi; ret
    }
    // 0x4e01c55  mov rax,[rsi]
    // 0x4e01c58  mov rax,[rax]        ; rax = obj->vfptr[0]
    // 0x4e01c5b  mov rcx,rsi
    // 0x4e01c5e  call qword ptr [0xF99FFA0]   ; sub_eea6040 (jmp rax) -> obj->vfptr[0](obj)
    void* method0 = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(
            *reinterpret_cast<void**>(obj)));
    ((void(__cdecl*)(void*))method0)(obj);   // 0x4e01c5e  call qword ptr [0xF99FFA0]
    // 0x4e01c64  lock dec dword ptr [rsi+0xC]
    // 0x4e01c68  jne short 0x4E01C84   ; result != 0 -> epilogue, ret
    std::atomic<std::uint32_t>* refC =
        reinterpret_cast<std::atomic<std::uint32_t>*>(
            reinterpret_cast<std::uint8_t*>(obj) + 0xC);
    if (refC->fetch_sub(1u, std::memory_order_seq_cst) != 1u) {
        return;   // 0x4e01c84..0x4e01c8a: add rsp,0x28; pop rdi; pop rsi; ret
    }
    // 0x4e01c6a  mov rax,[rsi]
    // 0x4e01c6d  mov rax,[rax+8]      ; rax = obj->vfptr[1]
    // 0x4e01c71  mov rdx,[0xF99FFA0]  ; rdx = sub_eea6040 (ignored by the jmp rax thunk)
    // 0x4e01c78  mov rcx,rsi
    // 0x4e01c7b  add rsp,0x28
    // 0x4e01c7f  pop rdi
    // 0x4e01c80  pop rsi
    // 0x4e01c81  jmp rdx              ; tail call sub_eea6040 (jmp rax) -> obj->vfptr[1](obj), no return
    void* method1 = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(
            *reinterpret_cast<void**>(obj)) + 8);
    return ((void(__cdecl*)(void*))method1)(obj);   // 0x4e01c81  jmp rdx
}

LIFT_FN(4e01c30, "sub_4e01c30", 0x4E01C30, sub_4e01c30, nullptr);

} // namespace native
