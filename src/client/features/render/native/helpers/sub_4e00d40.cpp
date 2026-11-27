// LIFT 0x4e00d40 size 0x94 1.26.62.01 sub_4e00d40
#include "sub_4e00d40.h"

#include <atomic>

namespace native {

// sub_4e00d40 (0x4e00d40, size 0x94, 1.26.62.01): see sub_4e00d40.h for the
// register/argument map, the layout mirrors and the callee list.
//
// Verbatim instructions of [0x4e00d40, 0x4e00dd4) (matches `rdis dis 0x4e00d40 0x94`):
#if 0
0x4e00d40  push rsi
0x4e00d41  sub rsp,0x20
0x4e00d45  lea rax,[0xF2158A4]
0x4e00d4c  movsxd rcx,[rax+rcx*4]
0x4e00d50  add rcx,rax
0x4e00d53  jmp rcx
0x4e00d55  mov rsi,[r8+0x10]
0x4e00d59  test rsi,rsi
0x4e00d5c  je short 0x4E00DCE
0x4e00d5e  lock dec dword ptr [rsi+8]
0x4e00d62  jne short 0x4E00DCE
0x4e00d64  mov rax,[rsi]
0x4e00d67  mov rax,[rax]
0x4e00d6a  mov rcx,rsi
0x4e00d6d  call qword ptr [0xF99FFA0]
0x4e00d73  lock dec dword ptr [rsi+0xC]
0x4e00d77  jne short 0x4E00DCE
0x4e00d79  mov rax,[rsi]
0x4e00d7c  mov rax,[rax+8]
0x4e00d80  mov rdx,[0xF99FFA0]
0x4e00d87  mov rcx,rsi
0x4e00d8a  add rsp,0x20
0x4e00d8e  pop rsi
0x4e00d8f  jmp rdx
0x4e00d92  mov rcx,[r8]
0x4e00d95  test rcx,rcx
0x4e00d98  je short 0x4E00DCE
0x4e00d9a  mov rdx,[rcx+8]
0x4e00d9e  test rdx,rdx
0x4e00da1  je short 0x4E00DBF
0x4e00da3  lock dec dword ptr [rdx+0xC]
0x4e00da7  jne short 0x4E00DBF
0x4e00da9  mov rax,[rdx]
0x4e00dac  mov rax,[rax+8]
0x4e00db0  mov rsi,rcx
0x4e00db3  mov rcx,rdx
0x4e00db6  call qword ptr [0xF99FFA0]
0x4e00dbc  mov rcx,rsi
0x4e00dbf  mov edx,0x20
0x4e00dc4  add rsp,0x20
0x4e00dc8  pop rsi
0x4e00dc9  jmp 0xE935700
0x4e00dce  add rsp,0x20
0x4e00dd2  pop rsi
0x4e00dd3  ret
#endif

void sub_4e00d40(std::uint32_t index, void* a1, void* a2)
{
    // 0x4e00d40  push rsi
    // 0x4e00d41  sub rsp,0x20
    // Callee-saved frame setup; no stack argument is read by this function.

    // 0x4e00d45  lea rax,[0xF2158A4]   ; jump table base (image base 0x140000000 + RVA 0xF2158A4 = VA 0x14F2158A4)
    // 0x4e00d4c  movsxd rcx,[rax+rcx*4]   ; entry = (int32_t)table[index], sign-extended
    // 0x4e00d50  add rcx,rax              ; target = table base + entry
    // 0x4e00d53  jmp rcx                  ; computed tail jump
    // No bounds check: indexes >= 19 read past the 19-entry table, exactly as
    // the original does. The table is read at its real address, so the same
    // bytes the exe reads are read here.
    static const std::int32_t* const kJumpTable =
        reinterpret_cast<const std::int32_t*>(0x14F2158A4ULL);
    void* target = reinterpret_cast<void*>(
        0x14F2158A4ULL +
        static_cast<std::int64_t>(static_cast<std::int32_t>(kJumpTable[index])));

    // 0x4e00dce  add rsp,0x20 / pop rsi / ret   (shared epilogue; indexes 0 and 1)
    if (target == reinterpret_cast<void*>(0x144E00DCE)) {
        return;   // 0x4e00dce..0x4e00dd3: add rsp,0x20; pop rsi; ret
    }

    // 0x4e00d55..0x4e00d8f   release path for the object at [a2+0x10] (indexes 3 and 4)
    if (target == reinterpret_cast<void*>(0x144E00D55)) {
        // 0x4e00d55  mov rsi,[r8+0x10]   ; obj = a2+0x10
        void* obj = *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a2) + 0x10);
        // 0x4e00d59  test rsi,rsi   ; 0x4e00d5c  je short 0x4E00DCE
        if (obj == nullptr) {
            return;   // 0x4e00dce: epilogue, ret
        }
        // 0x4e00d5e  lock dec dword ptr [rsi+8]
        // 0x4e00d62  jne short 0x4E00DCE   ; result != 0 -> epilogue, ret
        std::atomic<std::uint32_t>* ref8 =
            reinterpret_cast<std::atomic<std::uint32_t>*>(
                reinterpret_cast<std::uint8_t*>(obj) + 0x8);
        if (ref8->fetch_sub(1u, std::memory_order_seq_cst) != 1u) {
            return;   // 0x4e00d62: jne -> epilogue, ret
        }
        // 0x4e00d64  mov rax,[rsi]        ; rax = obj->vfptr
        // 0x4e00d67  mov rax,[rax]        ; rax = obj->vfptr[0]
        // 0x4e00d6a  mov rcx,rsi
        // 0x4e00d6d  call qword ptr [0xF99FFA0]   ; sub_eea6040 is `jmp rax`: obj->vfptr[0](obj)
        void* method0 = *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(*reinterpret_cast<void**>(obj)));
        ((void(__cdecl*)(void*))method0)(obj);   // 0x4e00d6d  call qword ptr [0xF99FFA0]
        // 0x4e00d73  lock dec dword ptr [rsi+0xC]
        // 0x4e00d77  jne short 0x4E00DCE   ; result != 0 -> epilogue, ret
        std::atomic<std::uint32_t>* refC =
            reinterpret_cast<std::atomic<std::uint32_t>*>(
                reinterpret_cast<std::uint8_t*>(obj) + 0xC);
        if (refC->fetch_sub(1u, std::memory_order_seq_cst) != 1u) {
            return;   // 0x4e00d77: jne -> epilogue, ret
        }
        // 0x4e00d79  mov rax,[rsi]
        // 0x4e00d7c  mov rax,[rax+8]      ; rax = obj->vfptr[1]
        // 0x4e00d80  mov rdx,[0xF99FFA0]  ; rdx = sub_eea6040
        // 0x4e00d87  mov rcx,rsi
        // 0x4e00d8a  add rsp,0x20
        // 0x4e00d8e  pop rsi
        // 0x4e00d8f  jmp rdx              ; tail call obj->vfptr[1](obj) via thunk, no return
        void* method1 = *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(*reinterpret_cast<void**>(obj)) + 8);
        return ((void(__cdecl*)(void*))method1)(obj);   // 0x4e00d8f  jmp rdx
    }

    // 0x4e00d92..0x4e00dc9   release path for the object at [a2+0x0] (index 2),
    // then tail call sub_e935700 (0x4e00dc9  jmp 0xE935700)
    if (target == reinterpret_cast<void*>(0x144E00D92)) {
        // 0x4e00d92  mov rcx,[r8]      ; obj = a2+0x0
        void* obj = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(a2));
        // 0x4e00d95  test rcx,rcx   ; 0x4e00d98  je short 0x4E00DCE
        if (obj == nullptr) {
            return;   // 0x4e00dce: epilogue, ret
        }
        // 0x4e00d9a  mov rdx,[rcx+8]   ; p = obj+0x8
        void* p = *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(obj) + 0x8);
        // 0x4e00d9e  test rdx,rdx   ; 0x4e00da1  je short 0x4E00DBF   ; p == 0 -> skip the dec and the call
        if (p != nullptr) {
            // 0x4e00da3  lock dec dword ptr [rdx+0xC]
            // 0x4e00da7  jne short 0x4E00DBF   ; result != 0 -> skip the call
            std::atomic<std::uint32_t>* refC =
                reinterpret_cast<std::atomic<std::uint32_t>*>(
                    reinterpret_cast<std::uint8_t*>(p) + 0xC);
            if (refC->fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                // 0x4e00da9  mov rax,[rdx]
                // 0x4e00dac  mov rax,[rax+8]   ; rax = p->vfptr[1]
                // 0x4e00db0  mov rsi,rcx
                // 0x4e00db3  mov rcx,rdx
                // 0x4e00db6  call qword ptr [0xF99FFA0]   ; p->vfptr[1](p) via sub_eea6040 thunk
                void* method1 = *reinterpret_cast<void**>(
                    reinterpret_cast<std::uint8_t*>(*reinterpret_cast<void**>(p)) + 8);
                ((void(__cdecl*)(void*))method1)(p);   // 0x4e00db6  call qword ptr [0xF99FFA0]
                // 0x4e00dbc  mov rcx,rsi   ; rcx = obj (restored after the call)
            }
        }
        // 0x4e00dbf  mov edx,0x20        ; edx is unused by sub_e935700
        // 0x4e00dc4  add rsp,0x20
        // 0x4e00dc8  pop rsi
        // 0x4e00dc9  jmp 0xE935700       ; tail call sub_e935700(obj)
        sub_e935700(obj);   // 0x4e00dc9  jmp 0xE935700  (lift callee, native symbol)
        return;
    }

    // 0x4e00d53  jmp rcx   — indexes 5..18 tail-jump to code outside this
    // function (table base + entry[index]). Forward the exact register state
    // the `jmp rcx` delivers: RCX = target address, RDX = a1, R8 = a2.
    using D0Tail = void(__cdecl*)(void* targetAddress, void* a1, void* a2);
    return ((D0Tail)target)(target, a1, a2);   // 0x4e00d53  jmp rcx
}

LIFT_FN(4e00d40, "sub_4e00d40", 0x4E00D40, sub_4e00d40, nullptr);

} // namespace native
