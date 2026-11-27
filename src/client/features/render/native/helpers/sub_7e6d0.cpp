// LIFT 0x7e6d0 size 0x48 1.26.62.01 sub_7e6d0
#include "sub_7e6d0.h"

namespace native {

// sub_7e6d0 (0x7e6d0, size 0x48, 1.26.62.01): reference-counted object release.
// Decrements refcount1 at inner+0x8; if zero, calls vtable[0] (destroy) via sub_eea6040.
// Then decrements refcount2 at inner+0xC; if zero, tail-calls sub_eea6040 with vtable[1] (delete).
// Reads: [a0+0x8] (inner), [inner+0x8] (refcount1), [inner] (vtable), [vtable+0x0] (destroy),
// [inner+0xC] (refcount2), [vtable+0x8] (delete, dead read). Writes: [inner+0x8] (atomic dec),
// [inner+0xC] (atomic dec). Calls: sub_eea6040 (vendor boundary via data slot 0xF99FFA0), twice.
// x64 Microsoft ABI: argument in RCX, no return value.

void sub_7e6d0(void* a0)
{
    // 0x7e6d0..0x7e6d5  push rsi; sub rsp,0x20
    // 0x7e6d5  mov rsi,[rcx+8]       ; inner = a0+0x8
    void* inner = *static_cast<void**>(reinterpret_cast<uintptr_t>(a0) + 0x8);   // 0x7e6d5  mov rsi,[rcx+8]
    // 0x7e6d9  test rsi,rsi
    // 0x7e6dc  je short 0x7E712      ; if inner == null, return
    if (inner == nullptr) {           // 0x7e6d9  test rsi,rsi ; 0x7e6dc  je short 0x7E712
        // 0x7e712..0x7e718  add rsp,0x20; pop rsi; ret
        return;                       // 0x7e712  add rsp,0x20 ; 0x7e716  pop rsi ; 0x7e717  ret
    }

    // 0x7e6de  lock dec dword ptr [rsi+8]   ; refcount1-- at inner+0x8
    std::uint32_t* refcount1 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<uintptr_t>(inner) + 0x8);
    if (--(*refcount1) != 0) {        // 0x7e6de  lock dec dword ptr [rsi+8] ; 0x7e6e2  jne short 0x7E712
        // 0x7e712..0x7e718  add rsp,0x20; pop rsi; ret
        return;                       // 0x7e712  add rsp,0x20 ; 0x7e716  pop rsi ; 0x7e717  ret
    }

    // 0x7e6e4  mov rax,[rsi]         ; vtable = inner[+0x0]
    void** vtable = *static_cast<void***>(inner);
    // 0x7e6e7  mov rax,[rax]         ; destructor = vtable[0]
    void* destructor = vtable[0];     // 0x7e6e7  mov rax,[rax]
    // 0x7e6ea  mov rcx,rsi           ; rcx = inner
    // 0x7e6ed  call qword ptr [0xF99FFA0]  ; sub_eea6040(inner, destructor)
    sub_eea6040(inner, destructor);   // 0x7e6ea  mov rcx,rsi ; 0x7e6ed  call qword ptr [0xF99FFA0]

    // 0x7e6f3  lock dec dword ptr [rsi+0xC] ; refcount2-- at inner+0xC
    std::uint32_t* refcount2 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<uintptr_t>(inner) + 0xC);
    if (--(*refcount2) != 0) {        // 0x7e6f3  lock dec dword ptr [rsi+0xC] ; 0x7e6f7  jne short 0x7E712
        // 0x7e712..0x7e718  add rsp,0x20; pop rsi; ret
        return;                       // 0x7e712  add rsp,0x20 ; 0x7e716  pop rsi ; 0x7e717  ret
    }

    // 0x7e6f9  mov rax,[rsi]         ; vtable = inner[+0x0]
    void** vtable2 = *static_cast<void***>(inner);
    // 0x7e6fc  mov rax,[rax+8]       ; deleteFn = vtable[1] (dead read - target from data slot)
    void* deleteFn = vtable2[1];      // 0x7e6fc  mov rax,[rax+8]
    (void)deleteFn;                   // value produced by the load; the thunk target comes from the data slot
    // 0x7e700  mov rdx,[0xF99FFA0]   ; rdx = sub_eea6040
    // 0x7e707  mov rcx,rsi           ; rcx = inner
    // 0x7e70a  add rsp,0x20
    // 0x7e70e  pop rsi
    // 0x7e70f  jmp rdx               ; tail call sub_eea6040(inner) -- delete via thunk
    sub_eea6040(inner, nullptr);      // 0x7e700  mov rdx,[0xF99FFA0] ; 0x7e707  mov rcx,rsi ; 0x7e70f  jmp rdx
    // Unreachable: sub_eea6040 tail-jumps and never returns to this point
}

LIFT_FN(sub_7e6d0, "sub_7e6d0", 0x7E6D0, sub_7e6d0, nullptr);

} // namespace native
