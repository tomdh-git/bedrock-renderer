// LIFT 0x4dfb470 size 0x47 1.26.62.01 sub_4dfb470
#include "sub_4dfb470.h"

namespace native {

// sub_4dfb470 (0x4dfb470, size 0x47, 1.26.62.01).
//
//   0x4dfb470  push rsi
//   0x4dfb471  sub rsp,0x20
//   0x4dfb475  mov rcx,[rcx]
//   0x4dfb478  test rcx,rcx
//   0x4dfb47b  je short 0x4DFB4B1
//   0x4dfb47d  mov rdx,[rcx+8]
//   0x4dfb481  test rdx,rdx
//   0x4dfb484  je short 0x4DFB4A2
//   0x4dfb486  lock dec dword ptr [rdx+0xC]
//   0x4dfb48a  jne short 0x4DFB4A2
//   0x4dfb48c  mov rax,[rdx]
//   0x4dfb48f  mov rax,[rax+8]
//   0x4dfb493  mov rsi,rcx
//   0x4dfb496  mov rcx,rdx
//   0x4dfb499  call qword ptr [0xF99FFA0]
//   0x4dfb49f  mov rcx,rsi
//   0x4dfb4a2  mov edx,0x20
//   0x4dfb4a7  add rsp,0x20
//   0x4dfb4ab  pop rsi
//   0x4dfb4ac  jmp 0xE935700
//   0x4dfb4b1  add rsp,0x20
//   0x4dfb4b5  pop rsi
//   0x4dfb4b6  ret
//
// Effect: smart pointer release. If the managed object has an inner ref-counted object,
// decrement its refcount; if it reaches zero, invoke its destructor via the vendor thunk.
// Then tail-call sub_e935700 to free the managed object storage (size 0x20).
// Reads: [a0] (managed), [managed+0x8] (inner), [inner+0xC] (refcount), [inner] (vfptr),
// [vfptr+0x8] (destructor). Writes: [inner+0xC] (atomic dec). Calls: sub_eea6040 (vendor
// boundary via data slot 0xF99FFA0), sub_e935700 (lift-set tail call).
// x64 Microsoft ABI: argument in RCX, no return value (void, tail call transfers control).

// Verbatim instructions of the function (matches rdis dis 0x4dfb470 0x47):
#if 0
0x4dfb470  push rsi
0x4dfb471  sub rsp,0x20
0x4dfb475  mov rcx,[rcx]
0x4dfb478  test rcx,rcx
0x4dfb47b  je short 0x4DFB4B1
0x4dfb47d  mov rdx,[rcx+8]
0x4dfb481  test rdx,rdx
0x4dfb484  je short 0x4DFB4A2
0x4dfb486  lock dec dword ptr [rdx+0xC]
0x4dfb48a  jne short 0x4DFB4A2
0x4dfb48c  mov rax,[rdx]
0x4dfb48f  mov rax,[rax+8]
0x4dfb493  mov rsi,rcx
0x4dfb496  mov rcx,rdx
0x4dfb499  call qword ptr [0xF99FFA0]
0x4dfb49f  mov rcx,rsi
0x4dfb4a2  mov edx,0x20
0x4dfb4a7  add rsp,0x20
0x4dfb4ab  pop rsi
0x4dfb4ac  jmp 0xE935700
0x4dfb4b1  add rsp,0x20
0x4dfb4b5  pop rsi
0x4dfb4b6  ret
#endif

void sub_4dfb470(void* a0)
{
    // 0x4dfb470..0x4dfb475  push rsi; sub rsp,0x20
    // 0x4dfb475..0x4dfb47b  mov rcx,[rcx]; test rcx,rcx; je 0x4DFB4B1
    void* managed = *static_cast<void**>(a0);                    // 0x4dfb475  mov rcx,[rcx]
    if (managed == nullptr) {                                    // 0x4dfb478  test rcx,rcx ; 0x4dfb47b  je 0x4DFB4B1
        // 0x4dfb4b1..0x4dfb4b6  add rsp,0x20; pop rsi; ret
        return;
    }

    // 0x4dfb47d..0x4dfb484  mov rdx,[rcx+8]; test rdx,rdx; je 0x4DFB4A2
    void* inner = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(managed) + 0x8); // 0x4dfb47d  mov rdx,[rcx+8]
    if (inner == nullptr) {                                      // 0x4dfb481  test rdx,rdx ; 0x4dfb484  je 0x4DFB4A2
        goto cleanup;                                            // 0x4dfb484  je 0x4DFB4A2
    }

    // 0x4dfb486..0x4dfb48a  lock dec dword ptr [rdx+0xC]; jne 0x4DFB4A2
    std::uint32_t* refcount = reinterpret_cast<std::uint32_t*>(reinterpret_cast<uintptr_t>(inner) + 0xC);
    if (--(*refcount) != 0) {                                    // 0x4dfb486  lock dec dword ptr [rdx+0xC] ; 0x4dfb48a  jne 0x4DFB4A2
        goto cleanup;
    }

    // 0x4dfb48c..0x4dfb49f  refcount reached zero -> destroy inner
    // 0x4dfb48c  mov rax,[rdx]          ; vtable = inner[+0x0]
    void* vtable = *static_cast<void**>(inner);
    // 0x4dfb48f  mov rax,[rax+8]        ; destructor = vtable[1]
    void* destructor = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(vtable) + 0x8);
    (void)destructor; // value produced by the two loads; the thunk reads it from RAX at call time

    // 0x4dfb493  mov rsi,rcx            ; save managed
    // 0x4dfb496  mov rcx,rdx            ; rcx = inner (this for destructor)
    // 0x4dfb499  call qword ptr [0xF99FFA0]  ; call sub_eea6040 via data slot
    // 0x4dfb49f  mov rcx,rsi            ; restore managed
    sub_eea6040(inner, destructor);                              // 0x4dfb499  call qword ptr [0xF99FFA0]

cleanup:
    // 0x4dfb4a2..0x4dfb4ac  mov edx,0x20; add rsp,0x20; pop rsi; jmp 0xE935700
    // 0x4dfb4a2  mov edx,0x20
    // 0x4dfb4a7  add rsp,0x20
    // 0x4dfb4ab  pop rsi
    // 0x4dfb4ac  jmp 0xE935700
    sub_e935700(managed, 0x20);                                  // 0x4dfb4ac  jmp 0xE935700 (tail call)
}

LIFT_FN(e935700, "sub_4dfb470", 0x4DFB470, sub_4dfb470, nullptr);

} // namespace native