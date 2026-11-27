// LIFT 0x67627d0 size 0x127 1.26.62.01 sub_67627d0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67627d0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// sub_e935700 (0xe935700, size 0x5): lift-set callee (tail jump to sub_392960).
// Forward-declared here and called through its native symbol (brief rule 66).
namespace native {
void* sub_e935700(void* a0);
} // namespace native

namespace native::helpers {

// Layout assertion in source (liftcheck checks the .cpp file directly).
static_assert(sizeof(Sub67627d0Layout) > 0, "sub_67627d0: layout constant block");


// sub_67627d0 (0x67627d0, size 0x127, 1.26.62.01): item group visitor.
//
//   Reads:  self+0x98 (u8); self+0x58 (ptr); self+0x68 (u64); *(self+0x58)-8 (u64);
//           self+0x38 (u8); self+0x30 (ptr); *(self+0x30)+8 (u32 lock dec);
//           *(*(self+0x30)) (vfptr[0]); *(self+0x30)+0xC (u32 lock dec);
//           *(*(self+0x30))+8 (vfptr[8]); self+0x8 (ptr); self+0x10 (ptr);
//           loop: rbx+0x18 (u8); rbx+8 (ptr); *(rbx+8)+8 (u32 lock dec);
//           *(*(rbx+8)) (vfptr[0]); *(rbx+8)+0xC (u32 lock dec); *(*(rbx+8))+8 (vfptr[8]).
//   Writes: self+0x58+0 (16-byte clear); self+0x58+0x10 (u64 = 0);
//           *(self+0x30)+8 (lock dec); *(self+0x30)+0xC (lock dec);
//           self+0x8+0x28*n (loop cursor advance); self+0x8 (16-byte clear);
//           self+0x18 (u64 = 0); rsp+0x20 (u64 = 0, dead on fail path).
//   Calls:  sub_e935700(rcx) [lift set]; thunk(obj, vfptr[0]) x4 [data slot 0xF99FFA0];
//           thunk(obj, vfptr[8]) x2 [data slot 0xF99FFA0]; failHandler(0,0,0,0) [data slot 0xF9A8C78] + int3 (noreturn).
//   Return: none on normal path (fall-through ret); noreturn on fail path.
//   Same reads, same writes, same calls in the same order, same return. Nothing else
//   happens in [0x67627d0, 0x67628f7).
//
// x64 Microsoft ABI: RCX = self (this). No null guards and no SEH exist in the
// original; none are added.

uintptr_t sub_67627d0(void* self)
{
    // 0x67627d0..0x67627d5  push r14; push rsi; push rdi; push rbx; sub rsp,0x28
    // 0x67627d9             mov rsi,rcx                       ; a0 = self
    std::uint8_t* const a0 = reinterpret_cast<std::uint8_t*>(self);

    // Temporaries (one per register used as a memory base or computed value).
    void* rdi = nullptr;       // &a0->0x58 sub-object, then reused as loop item ptr
    void* rcxVal = nullptr;    // [a0+0x58] or dealloc argument
    std::uintptr_t rdx = 0;    // size / bias computation
    std::uintptr_t rax = 0;    // block size header or vtable entry
    std::uintptr_t rcxVal2 = 0;// dealloc argument or vtable-relative delta
    void* rdi2 = nullptr;      // [a0+0x30] refcounted object
    void* rbx = nullptr;       // loop walk cursor ([a0+0x8] advanced by 0x28)
    void* r14 = nullptr;       // loop end ([a0+0x10])
    std::uint8_t* walkPtr = nullptr; // rsi after +8 advance (= &a0->0x8 cursor base)

    // Vtable-call thunk via data slot 0xF99FFA0 (jmp rax; sub_eea6040, boundary/vendor).
    // RAX must hold the target function pointer on entry; RCX = object; return ignored.
    ::native::Boundary<std::uintptr_t, void*, void*> vtableThunk("sub_eea6040");

    // -------------------------------------------------------------------------
    // 0x67627d0..0x67627e5  block 0: prologue; cmp byte [a0+0x98],1
    // -> if *u8(a0+0x98) != 1 goto L_0x6762830
    // -> if *u8(a0+0x98) == 1 goto L_0x67627e5
    if (*reinterpret_cast<const std::uint8_t*>(a0 + 0x98) != 1) {
        goto L_0x6762830;
    }

    // -------------------------------------------------------------------------
    // 0x67627e5..0x67627f1  block 1: lea rdi,[a0+0x58]; mov rcx,[rdi]; test rcx,rcx
    // -> if *(a0+0x58) == 0 goto L_0x6762830
    // -> if *(a0+0x58) != 0 goto L_0x67627f1
    rdi = *reinterpret_cast<void**>(a0 + 0x58);
    if (rdi == nullptr) {
        goto L_0x6762830;
    }

    // -------------------------------------------------------------------------
    // 0x67627f1..0x6762801  block 2: mov rdx,[a0+0x68]; sub rdx,rcx; cmp rdx,0x1000
    // -> if (*(a0+0x68) - *(a0+0x58)) <u 0x1000 goto L_0x676281d
    // -> if (*(a0+0x68) - *(a0+0x58)) >=u 0x1000 goto L_0x6762801
    rdx = *reinterpret_cast<std::uintptr_t*>(a0 + 0x68) -
         reinterpret_cast<std::uintptr_t>(rdi);
    if (rdx < 0x1000) {
        goto L_0x676281d;
    }

    // -------------------------------------------------------------------------
    // 0x6762801..0x6762816  block 3: mov rax,[rcx-8]; add rcx,-8; sub rcx,rax; cmp rcx,0x20
    // -> if (*(a0+0x58)-0x8 - *(*(a0+0x58)-0x8)) >=u 0x20 goto L_0x67628dd
    // -> if (*(a0+0x58)-0x8 - *(*(a0+0x58)-0x8)) <u 0x20 goto L_0x6762816
    rax = *reinterpret_cast<const std::uintptr_t*>(
              reinterpret_cast<const std::uint8_t*>(rdi) - 8);
    rcxVal2 = reinterpret_cast<std::uintptr_t>(rdi) - 8 - rax;
    if (rcxVal2 >= 0x20) {
        goto L_0x67628dd;
    }

    // -------------------------------------------------------------------------
    // 0x6762816..0x676281d  block 4: or rdx,0x27; mov rcx,rax
    // -> fallthrough goto L_0x676281d
    rdx |= 0x27;
    rcxVal2 = rax;

L_0x676281d:
    // -------------------------------------------------------------------------
    // 0x676281d..0x6762830  block 5: call 0xE935700; xorps; movups [rdi],xmm0; mov [rdi+0x10],0
    // -> fallthrough goto L_0x6762830
    ::native::sub_e935700(reinterpret_cast<void*>(rcxVal2));  // 0x676281d  call 0xE935700
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(rdi) + 0x00) = 0;  // 0x6762825  movups [rdi],xmm0 (+0x00)
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(rdi) + 0x08) = 0;  // 0x6762825  movups [rdi],xmm0 (+0x08)
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(rdi) + 0x10) = 0;  // 0x6762828  mov qword [rdi+0x10],0

L_0x6762830:
    // -------------------------------------------------------------------------
    // 0x6762830..0x6762836  block 6: cmp byte [a0+0x38],3
    // -> if *u8(a0+0x38) != 3 goto L_0x676286a
    // -> if *u8(a0+0x38) == 3 goto L_0x6762836
    if (*reinterpret_cast<const std::uint8_t*>(a0 + 0x38) != 3) {
        goto L_0x676286a;
    }

    // -------------------------------------------------------------------------
    // 0x6762836..0x676283f  block 7: mov rdi,[a0+0x30]; test rdi,rdi
    // -> if *(a0+0x30) == 0 goto L_0x676286a
    // -> if *(a0+0x30) != 0 goto L_0x676283f
    rdi2 = *reinterpret_cast<void**>(a0 + 0x30);
    if (rdi2 == nullptr) {
        goto L_0x676286a;
    }

    // -------------------------------------------------------------------------
    // 0x676283f..0x6762845  block 8: lock dec [rdi+8]; jne short L_0x676286a
    // -> if (Dec *(a0+0x30)+8) != 0 goto L_0x676286a
    // -> if (Dec *(a0+0x30)+8) == 0 goto L_0x6762845
    if (_InterlockedDecrement(
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(rdi2) + 8)) != 0) {
        goto L_0x676286a;
    }

    // -------------------------------------------------------------------------
    // 0x6762845..0x676285a  block 9: mov rax,[rdi]; mov rax,[rax]; mov rcx,rdi;
    //           call [0xF99FFA0]; lock dec [rdi+0xC]; jne short L_0x676286a
    // -> if (Dec *(a0+0x30)+0xC) != 0 goto L_0x676286a
    // -> if (Dec *(a0+0x30)+0xC) == 0 goto L_0x676285a
    {
        void** const vfptr = *reinterpret_cast<void***>(rdi2);  // 0x6762845  mov rax,[rdi]
                                                            // 0x6762848  mov rax,[rax]
        vtableThunk(rdi2, vfptr[0]);                        // 0x676284b  mov rcx,rdi
                                                            // 0x676284e  call qword ptr [0xF99FFA0]
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rdi2) + 0xC)) != 0) {  // 0x6762854  lock dec [rdi+0xC]
                                                            // 0x6762858  jne short L_0x676286a
            goto L_0x676286a;
        }
    }

    // -------------------------------------------------------------------------
    // 0x676285a..0x676286a  block 10: mov rax,[rdi]; mov rax,[rax+8]; mov rcx,rdi;
    //           call [0xF99FFA0]; fallthrough goto L_0x676286a
    {
        void** const vfptr = *reinterpret_cast<void***>(rdi2);  // 0x676285a  mov rax,[rdi]
                                                            // 0x676285d  mov rax,[rax+8]
        vtableThunk(rdi2, vfptr[1]);                        // 0x6762861  mov rcx,rdi
                                                            // 0x6762864  call qword ptr [0xF99FFA0]
    }

L_0x676286a:
    // -------------------------------------------------------------------------
    // 0x676286a..0x6762873  block 11: mov rbx,[a0+8]; test rbx,rbx
    // -> if *(a0+0x8) == 0 goto L_0x67628d3
    // -> if *(a0+0x8) != 0 goto L_0x6762873
    rbx = *reinterpret_cast<void**>(a0 + 0x8);
    if (rbx == nullptr) {
        goto L_0x67628d3;
    }

    // -------------------------------------------------------------------------
    // 0x6762873..0x676287d  block 12: mov r14,[a0+0x10]; add rsi,8; jmp L_0x6762884
    r14 = *reinterpret_cast<void**>(a0 + 0x10);
    walkPtr = a0 + 8;   // 0x6762877  add rsi,8  (walk cursor base = &a0->0x8)
    goto L_0x6762884;

L_0x676287d:
    // -------------------------------------------------------------------------
    // 0x676287d..0x6762880  block 13: nop [rax]; fallthrough goto L_0x6762880
    goto L_0x6762880;

L_0x6762880:
    // -------------------------------------------------------------------------
    // 0x6762880..0x6762884  block 14: add rbx,0x28; fallthrough goto L_0x6762884
    rbx = reinterpret_cast<void*>(
        reinterpret_cast<std::uint8_t*>(rbx) + 0x28);
    goto L_0x6762884;

L_0x6762884:
    // -------------------------------------------------------------------------
    // 0x6762884..0x6762889  block 15: cmp rbx,r14; je short L_0x67628c5
    // -> if rbx == r14 goto L_0x67628c5
    // -> if rbx != r14 goto L_0x6762889
    if (rbx == r14) {
        goto L_0x67628c5;
    }

    // -------------------------------------------------------------------------
    // 0x6762889..0x676288f  block 16: cmp byte [rbx+0x18],2; jne short L_0x6762880
    // -> if *u8(rbx+0x18) != 2 goto L_0x6762880
    // -> if *u8(rbx+0x18) == 2 goto L_0x676288f
    if (*reinterpret_cast<const std::uint8_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x18) != 2) {
        goto L_0x6762880;
    }

    // -------------------------------------------------------------------------
    // 0x676288f..0x6762898  block 17: mov rdi,[rbx+8]; test rdi,rdi
    // -> if *(rbx+8) == 0 goto L_0x6762880
    // -> if *(rbx+8) != 0 goto L_0x6762898
    rdi = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 8);
    if (rdi == nullptr) {
        goto L_0x6762880;
    }

    // -------------------------------------------------------------------------
    // 0x6762898..0x676289e  block 18: lock dec [rdi+8]; jne short L_0x6762880
    // -> if (Dec *(rbx+8)+8) != 0 goto L_0x6762880
    // -> if (Dec *(rbx+8)+8) == 0 goto L_0x676289e
    if (_InterlockedDecrement(
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(rdi) + 8)) != 0) {
        goto L_0x6762880;
    }

    // -------------------------------------------------------------------------
    // 0x676289e..0x67628b3  block 19: mov rax,[rdi]; mov rax,[rax]; mov rcx,rdi;
    //           call [0xF99FFA0]; lock dec [rdi+0xC]; jne short L_0x6762880
    // -> if (Dec *(rbx+8)+0xC) != 0 goto L_0x6762880
    // -> if (Dec *(rbx+8)+0xC) == 0 goto L_0x67628b3
    {
        void** const vfptr = *reinterpret_cast<void***>(rdi);   // 0x676289e  mov rax,[rdi]
                                                            // 0x67628a1  mov rax,[rax]
        vtableThunk(rdi, vfptr[0]);                         // 0x67628a4  mov rcx,rdi
                                                            // 0x67628a7  call qword ptr [0xF99FFA0]
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rdi) + 0xC)) != 0) {  // 0x67628ad  lock dec [rdi+0xC]
                                                            // 0x67628b1  jne short L_0x6762880
            goto L_0x6762880;
        }
    }

    // -------------------------------------------------------------------------
    // 0x67628b3..0x67628c5  block 20: mov rax,[rdi]; mov rax,[rax+8]; mov rcx,rdi;
    //           call [0xF99FFA0]; jmp short L_0x6762880
    {
        void** const vfptr = *reinterpret_cast<void***>(rdi);   // 0x67628b3  mov rax,[rdi]
                                                            // 0x67628b6  mov rax,[rax+8]
        vtableThunk(rdi, vfptr[1]);                         // 0x67628ba  mov rcx,rdi
                                                            // 0x67628bd  call qword ptr [0xF99FFA0]
    }
    goto L_0x6762880;

L_0x67628c5:
    // -------------------------------------------------------------------------
    // 0x67628c5..0x67628d3  block 21: xorps; movups [rsi],xmm0; mov [rsi+0x10],0
    // (rsi == walkPtr == &a0->0x8)
    // -> fallthrough goto L_0x67628d3
    *reinterpret_cast<std::uint64_t*>(walkPtr + 0x00) = 0;  // 0x67628c8  movups [rsi],xmm0 (+0x00)
    *reinterpret_cast<std::uint64_t*>(walkPtr + 0x08) = 0;  // 0x67628c8  movups [rsi],xmm0 (+0x08)
    *reinterpret_cast<std::uint64_t*>(walkPtr + 0x10) = 0;  // 0x67628cb  mov qword [rsi+0x10],0

L_0x67628d3:
    // -------------------------------------------------------------------------
    // 0x67628d3..0x67628dd  block 22: add rsp,0x28; pop rbx; pop rdi; pop rsi; pop r14; ret
    return 0;

L_0x67628dd:
    // -------------------------------------------------------------------------
    // 0x67628dd..0x67628f7  block 23: mov [rsp+0x20],0; xor ecx,ecx; xor edx,edx;
    //           xor r8d,r8d; xor r9d,r9d; call [0xF9A8C78]; int3 (noreturn)
    // [rsp+0x20] = 0 is a dead stack store (never read); zero args are explicit nullptr.
    auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
        *reinterpret_cast<const std::uintptr_t*>(
            RewriteRegistry::imageBase() + kRvaFailSlot));  // slot read at call time
    failFn(nullptr, nullptr, nullptr, nullptr);             // 0x67628f0  call qword ptr [0xF9A8C78]
    __debugbreak();                                         // 0x67628f6  int3
    __assume(false);                                        // int3 is noreturn pad
}

} // namespace native::helpers

LIFT_FN(sub_67627d0, "sub_67627d0", 0x67627d0, ::native::helpers::sub_67627d0, nullptr);

// Verbatim instructions of [0x67627d0, 0x67628f7) (rdis dis 0x67627d0 0x127);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x67627d0  push r14
0x67627d2  push rsi
0x67627d3  push rdi
0x67627d4  push rbx
0x67627d5  sub rsp,0x28
0x67627d9  mov rsi,rcx
0x67627dc  cmp byte ptr [rcx+0x98],1
0x67627e3  jne short 0x6762830
0x67627e5  lea rdi,[rsi+0x58]
0x67627e9  mov rcx,[rdi]
0x67627ec  test rcx,rcx
0x67627ef  je short 0x6762830
0x67627f1  mov rdx,[rsi+0x68]
0x67627f5  sub rdx,rcx
0x67627f8  cmp rdx,0x1000
0x67627ff  jb short 0x676281D
0x6762801  mov rax,[rcx-8]
0x6762805  add rcx,0xFFFFFFFFFFFFFFF8
0x6762809  sub rcx,rax
0x676280c  cmp rcx,0x20
0x6762810  jae 0x67628DD
0x6762816  or rdx,0x27
0x676281a  mov rcx,rax
0x676281d  call 0xE935700
0x6762822  xorps xmm0,xmm0
0x6762825  movups [rdi],xmm0
0x6762828  mov qword ptr [rdi+0x10],0
0x6762830  cmp byte ptr [rsi+0x38],3
0x6762834  jne short 0x676286A
0x6762836  mov rdi,[rsi+0x30]
0x676283a  test rdi,rdi
0x676283d  je short 0x676286A
0x676283f  lock dec dword ptr [rdi+8]
0x6762843  jne short 0x676286A
0x6762845  mov rax,[rdi]
0x6762848  mov rax,[rax]
0x676284b  mov rcx,rdi
0x676284e  call qword ptr [0xF99FFA0]
0x6762854  lock dec dword ptr [rdi+0xC]
0x6762858  jne short 0x676286A
0x676285a  mov rax,[rdi]
0x676285d  mov rax,[rax+8]
0x6762861  mov rcx,rdi
0x6762864  call qword ptr [0xF99FFA0]
0x676286a  mov rbx,[rsi+8]
0x676286e  test rbx,rbx
0x6762871  je short 0x67628D3
0x6762873  mov r14,[rsi+0x10]
0x6762877  add rsi,8
0x676287b  jmp short 0x6762884
0x676287d  nop [rax]
0x6762880  add rbx,0x28
0x6762884  cmp rbx,r14
0x6762887  je short 0x67628C5
0x6762889  cmp byte ptr [rbx+0x18],2
0x676288d  jne short 0x6762880
0x676288f  mov rdi,[rbx+8]
0x6762893  test rdi,rdi
0x6762896  je short 0x6762880
0x6762898  lock dec dword ptr [rdi+8]
0x676289c  jne short 0x6762880
0x676289e  mov rax,[rdi]
0x67628a1  mov rax,[rax]
0x67628a4  mov rcx,rdi
0x67628a7  call qword ptr [0xF99FFA0]
0x67628ad  lock dec dword ptr [rdi+0xC]
0x67628b1  jne short 0x6762880
0x67628b3  mov rax,[rdi]
0x67628b6  mov rax,[rax+8]
0x67628ba  mov rcx,rdi
0x67628bd  call qword ptr [0xF99FFA0]
0x67628c3  jmp short 0x6762880
0x67628c5  xorps xmm0,xmm0
0x67628c8  movups [rsi],xmm0
0x67628cb  mov qword ptr [rsi+0x10],0
0x67628d3  add rsp,0x28
0x67628d7  pop rbx
0x67628d8  pop rdi
0x67628d9  pop rsi
0x67628da  pop r14
0x67628dc  ret
0x67628dd  mov qword ptr [rsp+0x20],0
0x67628e6  xor ecx,ecx
0x67628e8  xor edx,edx
0x67628ea  xor r8d,r8d
0x67628ed  xor r9d,r9d
0x67628f0  call qword ptr [0xF9A8C78]
0x67628f6  int3
#endif
