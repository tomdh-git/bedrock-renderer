// LIFT 0xbcd54a0 size 0xb9 1.26.62.01 sub_bcd54a0
#include "sub_bcd54a0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_bcd54a0 (0xbcd54a0, size 0xb9, 1.26.62.01).
//
// Releases the ref-counted object held at a0+0x40: two interlocked dword
// decrements (at +0x8 and +0xC of the object) each gate a release call
// through the vendor thunk at data slot 0xF99FFA0 (sub_eea6040). The vtable
// loads that precede each call are dead reads: the call target is the data
// slot, not the loaded vtable entry.
//
// Then the buffer at a0+0x10 (size at a0+0x28) is handled:
//   size < 0x10                      -> small buffer, nothing to free
//   size+1 < 0x1000                  -> free via sub_e935700(buffer)
//   size+1 >= 0x1000                 -> compute block start; if block_start
//                                       >= 0x20 call indirect free via data
//                                       slot 0xF9A8C78 then trap (int3, noreturn);
//                                       otherwise free via sub_e935700([buffer-8])
// In every non-trap path the object fields are reset (field20=0, size=0xF,
// first buffer byte=0) and the function tail-calls sub_e935700(a0).
//
// Calls:
//   0xbcd54c1  call qword ptr [0xF99FFA0]  -> function pointer via data slot (sub_eea6040, vendor)
//   0xbcd54d7  call qword ptr [0xF99FFA0]  -> function pointer via data slot (sub_eea6040, vendor)
//   0xbcd5513  call 0xE935700              -> native::sub_e935700        (lift set)
//   0xbcd5552  call qword ptr [0xF9A8C78]  -> function pointer via data slot (indirect)
//
// x64 Microsoft ABI: argument in RCX, return value in RAX (tail call through
// sub_e935700).

void* sub_bcd54a0(void* a0)
{
    auto* obj = reinterpret_cast<ArgLayout*>(a0);

    // 0xbcd54a0..0xbcd54a6   push rsi; push rdi; sub rsp,0x28   (prologue)
    // 0xbcd54a6  mov rsi,rcx
    // 0xbcd54a9  mov rdi,[rcx+0x40]   R a0+0x40
    void* refObject = obj->refObject;    // 0xbcd54a9  mov rdi,[rcx+0x40]

    // 0xbcd54ad  test rdi,rdi
    // 0xbcd54b0  je short 0xBCD54DD
    if (refObject != nullptr) {          // 0xbcd54ad  test rdi,rdi ; 0xbcd54b0  je short 0xBCD54DD
        // 0xbcd54b2  lock dec dword ptr [rdi+8]   W *(refObject)+0x8
        int32_t* refcount8 = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(refObject) + 8);
        int32_t after8 = --(*refcount8); // 0xbcd54b2  lock dec dword ptr [rdi+8]
        // 0xbcd54b6  jne short 0xBCD54DD
        if (after8 != 0) {               // 0xbcd54b6  jne short 0xBCD54DD
            goto loc_bcd54dd;
        }

        // 0xbcd54b8  mov rax,[rdi]      R *(refObject)+0x0   (dead read: call target is the data slot)
        void** vtable = reinterpret_cast<void**>(refObject);   // *refObject  -> vtable pointer
        // 0xbcd54bb  mov rax,[rax]      R *(*(refObject))+0x0 (dead read: call target is the data slot)
        (void)vtable[0];                 // *vtable  -> vtable[0], value unused
        // 0xbcd54be  mov rcx,rdi        rcx = refObject
        // 0xbcd54c1  call qword ptr [0xF99FFA0]   rcx=refObject
        {
            using DtorFn = void (*)(void*);
            DtorFn dtor = reinterpret_cast<DtorFn>(
                *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
            dtor(refObject);             // 0xbcd54c1  call qword ptr [0xF99FFA0]
        }

        // 0xbcd54c7  lock dec dword ptr [rdi+0xC]   W *(refObject)+0xC
        int32_t* refcountC = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(refObject) + 0xC);
        int32_t afterC = --(*refcountC); // 0xbcd54c7  lock dec dword ptr [rdi+0xC]
        // 0xbcd54cb  jne short 0xBCD54DD
        if (afterC != 0) {               // 0xbcd54cb  jne short 0xBCD54DD
            goto loc_bcd54dd;
        }

        // 0xbcd54cd  mov rax,[rdi]      R *(refObject)+0x0   (dead read)
        vtable = reinterpret_cast<void**>(refObject);
        // 0xbcd54d0  mov rax,[rax+8]    R *(*(refObject))+0x8 (dead read)
        (void)vtable[1];                 // *(vtable+1), value unused
        // 0xbcd54d4  mov rcx,rdi        rcx = refObject
        // 0xbcd54d7  call qword ptr [0xF99FFA0]   rcx=refObject
        {
            using DtorFn = void (*)(void*);
            DtorFn dtor = reinterpret_cast<DtorFn>(
                *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
            dtor(refObject);             // 0xbcd54d7  call qword ptr [0xF99FFA0]
        }
    }

loc_bcd54dd:   // 0xbcd54dd  mov rax,[rsi+0x28]   R a0+0x28
    uintptr_t size = obj->size;          // 0xbcd54dd  mov rax,[rsi+0x28]
    // 0xbcd54e1  cmp rax,0x10
    // 0xbcd54e5  jb short 0xBCD5518
    if (size >= 0x10) {                  // 0xbcd54e1  cmp rax,0x10 ; 0xbcd54e5  jb short 0xBCD5518
        // 0xbcd54e7  mov rcx,[rsi+0x10]   R a0+0x10
        char* buffer = *reinterpret_cast<char**>(obj->field10);  // 0xbcd54e7  mov rcx,[rsi+0x10]
        // 0xbcd54eb  lea rdx,[rax+1]      rdx = size + 1
        uintptr_t rdx = size + 1;        // 0xbcd54eb  lea rdx,[rax+1]
        // 0xbcd54ef  cmp rdx,0x1000
        // 0xbcd54f6  jb short 0xBCD5513
        if (rdx < 0x1000) {              // 0xbcd54ef  cmp rdx,0x1000 ; 0xbcd54f6  jb short 0xBCD5513
            // 0xbcd5513  call 0xE935700   rcx=buffer
            sub_e935700(buffer);         // 0xbcd5513  call 0xE935700
        } else {
            // 0xbcd54f8  mov r8,[rcx-8]   R *(buffer-8)
            uintptr_t r8 = *reinterpret_cast<uintptr_t*>(buffer - 8);  // 0xbcd54f8  mov r8,[rcx-8]
            // 0xbcd54fc  add rcx,0xFFFFFFFFFFFFFFF8   rcx = buffer - 8
            uintptr_t rcx = reinterpret_cast<uintptr_t>(buffer) - 8;   // 0xbcd54fc  add rcx,0xFFFFFFFFFFFFFFF8
            // 0xbcd5500  sub rcx,r8       rcx = block_start
            rcx -= r8;                   // 0xbcd5500  sub rcx,r8
            // 0xbcd5503  cmp rcx,0x20
            // 0xbcd5507  jae short 0xBCD553F
            if (rcx >= 0x20) {           // 0xbcd5503  cmp rcx,0x20 ; 0xbcd5507  jae short 0xBCD553F
                goto loc_bcd553f;
            }
            // 0xbcd5509  add rax,0x28     rax = size + 0x28
            // 0xbcd550d  mov rdx,rax      rdx = size + 0x28  (dead store: sub_e935700 reads only RCX)
            // 0xbcd5510  mov rcx,r8       rcx = r8
            // 0xbcd5513  call 0xE935700   rcx=r8
            sub_e935700(reinterpret_cast<void*>(r8));  // 0xbcd5510..0xbcd5513  rcx=r8 ; call 0xE935700
        }
        // bcd5513 falls through to bcd5518
    }

loc_bcd5518:   // 0xbcd5518  mov qword ptr [rsi+0x20],0   W a0+0x20
    obj->field20 = 0;                    // 0xbcd5518  mov qword ptr [rsi+0x20],0
    // 0xbcd5520  mov qword ptr [rsi+0x28],0xF   W a0+0x28
    obj->size = 0xF;                     // 0xbcd5520  mov qword ptr [rsi+0x28],0xF
    // 0xbcd5528  mov byte ptr [rsi+0x10],0    W a0+0x10 (single byte)
    obj->field10[0] = '\0';              // 0xbcd5528  mov byte ptr [rsi+0x10],0
    // 0xbcd552c  mov edx,0x48             (dead store: sub_e935700 reads only RCX)
    // 0xbcd5531  mov rcx,rsi              rcx = a0
    // 0xbcd5534  add rsp,0x28; pop rdi; pop rsi
    // 0xbcd553a  jmp 0xE935700            tail call sub_e935700(a0)
    return sub_e935700(a0);              // 0xbcd552c..0xbcd553a  edx=0x48 ; tail call sub_e935700(a0)

loc_bcd553f:   // 0xbcd553f  mov qword ptr [rsp+0x20],0   (stack store)
    // 0xbcd5548  xor ecx,ecx
    // 0xbcd554a  xor edx,edx
    // 0xbcd554c  xor r8d,r8d
    // 0xbcd554f  xor r9d,r9d             (all arguments = 0)
    // 0xbcd5552  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
    {
        using FailFn = void (*)(void*, void*, void*, void*, void*);
        FailFn fail = reinterpret_cast<FailFn>(
            *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8C78));
        fail(nullptr, nullptr, nullptr, nullptr, nullptr);  // 0xbcd5552  call qword ptr [0xF9A8C78]
    }
    // 0xbcd5558  int3   (trap if the indirect call returns; noreturn block terminator)
    __assume(false);                      // 0xbcd5558  int3
}

#if 0
0xbcd54a0  push rsi
0xbcd54a1  push rdi
0xbcd54a2  sub rsp,0x28
0xbcd54a6  mov rsi,rcx
0xbcd54a9  mov rdi,[rcx+0x40]
0xbcd54ad  test rdi,rdi
0xbcd54b0  je short 0xBCD54DD
0xbcd54b2  lock dec dword ptr [rdi+8]
0xbcd54b6  jne short 0xBCD54DD
0xbcd54b8  mov rax,[rdi]
0xbcd54bb  mov rax,[rax]
0xbcd54be  mov rcx,rdi
0xbcd54c1  call qword ptr [0xF99FFA0]
0xbcd54c7  lock dec dword ptr [rdi+0xC]
0xbcd54cb  jne short 0xBCD54DD
0xbcd54cd  mov rax,[rdi]
0xbcd54d0  mov rax,[rax+8]
0xbcd54d4  mov rcx,rdi
0xbcd54d7  call qword ptr [0xF99FFA0]
0xbcd54dd  mov rax,[rsi+0x28]
0xbcd54e1  cmp rax,0x10
0xbcd54e5  jb short 0xBCD5518
0xbcd54e7  mov rcx,[rsi+0x10]
0xbcd54eb  lea rdx,[rax+1]
0xbcd54ef  cmp rdx,0x1000
0xbcd54f6  jb short 0xBCD5513
0xbcd54f8  mov r8,[rcx-8]
0xbcd54fc  add rcx,0xFFFFFFFFFFFFFFF8
0xbcd5500  sub rcx,r8
0xbcd5503  cmp rcx,0x20
0xbcd5507  jae short 0xBCD553F
0xbcd5509  add rax,0x28
0xbcd550d  mov rdx,rax
0xbcd5510  mov rcx,r8
0xbcd5513  call 0xE935700
0xbcd5518  mov qword ptr [rsi+0x20],0
0xbcd5520  mov qword ptr [rsi+0x28],0xF
0xbcd5528  mov byte ptr [rsi+0x10],0
0xbcd552c  mov edx,0x48
0xbcd5531  mov rcx,rsi
0xbcd5534  add rsp,0x28
0xbcd5538  pop rdi
0xbcd5539  pop rsi
0xbcd553a  jmp 0xE935700
0xbcd553f  mov qword ptr [rsp+0x20],0
0xbcd5548  xor ecx,ecx
0xbcd554a  xor edx,edx
0xbcd554c  xor r8d,r8d
0xbcd554f  xor r9d,r9d
0xbcd5552  call qword ptr [0xF9A8C78]
0xbcd5558  int3
#endif

LIFT_FN(sub_bcd54a0, "sub_bcd54a0", 0xbcd54a0, sub_bcd54a0, nullptr);

} // namespace native
