// LIFT 0xe809f40 size 0x6a 1.26.62.01 sub_e809f40
#include "sub_e809f40.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native { namespace d3d12 {

// Boundary thunk note:
//   call qword ptr [0xF99FFA0]  ->  sub_eea6040, a "jmp rax" thunk.
// The caller first loads the real target into rax (here [0x12BB4938], and
// [[rsi]+0x120]); the thunk transfers control to it with the current registers.
// We therefore call the loaded target directly with the same register arguments.
// sub_eea6040 is classified vendor/boundary in docs/data/native_boundary.tsv.

extern "C" void* sub_e809f40(void* a0, void* a1) {
    void* rsi = a1;
    void* rdi = a0;

    // 0xe809f4c..0xe809f5b
    *reinterpret_cast<std::uint64_t*>(static_cast<char*>(rdi) + 0x28) = 1; // 0xe809f4c
    *reinterpret_cast<std::uint64_t*>(static_cast<char*>(rdi) + 0x30) = 0; // 0xe809f54

    // 0xe809f5c..0xe809f75 : first thunk call
    //   rax = [0x12BB4938]; ecx=0; edx=0; r8d=0; r9d=0x1F0003; call thunk
    using Fn1 = void* (*)(void* rcx, void* rdx, void* r8, std::uint32_t r9);
    Fn1 target1 = reinterpret_cast<Fn1>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + 0x12BB4938)); // 0xe809f5c
    void* rax = target1(nullptr, nullptr, nullptr, 0x001F0003u); // 0xe809f70 call [0xF99FFA0]

    *reinterpret_cast<void**>(static_cast<char*>(rdi) + 0x20) = rax; // 0xe809f76

    // 0xe809f7a..0xe809f9b : second thunk call
    void* this18 = static_cast<char*>(rdi) + 0x18;                   // 0xe809f7a
    void* vtbl = *reinterpret_cast<void**>(rsi);                     // 0xe809f7e
    void* fnptr = *reinterpret_cast<void**>(static_cast<char*>(vtbl) + 0x120); // 0xe809f81
    void* r9 = reinterpret_cast<void*>(RewriteRegistry::imageBase() + 0xF4ED5A0); // 0xe809f8d lea r9,[0xF4ED5A0]
    // rcx=rsi (0xe809f94); edx=0 (0xe809f97); r8d=0 (0xe809f99); [rsp+0x20]=this18 (0xe809f88)
    using Fn2 = void* (*)(void* rcx, void* rdx, void* r8, void* r9, void* stack0);
    Fn2 target2 = reinterpret_cast<Fn2>(fnptr);
    void* ret2 = target2(rsi, nullptr, nullptr, r9, this18);         // 0xe809f9c call [0xF99FFA0]

    // 0xe809fa2..0xe809fa9 : epilogue
    return ret2;
}

#if 0
0xe809f40  push rsi
0xe809f41  push rdi
0xe809f42  sub rsp,0x28
0xe809f46  mov rsi,rdx
0xe809f49  mov rdi,rcx
0xe809f4c  mov qword ptr [rcx+0x28],1
0xe809f54  mov qword ptr [rcx+0x30],0
0xe809f5c  mov rax,[0x12BB4938]
0xe809f63  xor ecx,ecx
0xe809f65  xor edx,edx
0xe809f67  xor r8d,r8d
0xe809f6a  mov r9d,0x1F0003
0xe809f70  call qword ptr [0xF99FFA0]
0xe809f76  mov [rdi+0x20],rax
0xe809f7a  add rdi,0x18
0xe809f7e  mov rax,[rsi]
0xe809f81  mov rax,[rax+0x120]
0xe809f88  mov [rsp+0x20],rdi
0xe809f8d  lea r9,[0xF4ED5A0]
0xe809f94  mov rcx,rsi
0xe809f97  xor edx,edx
0xe809f99  xor r8d,r8d
0xe809f9c  call qword ptr [0xF99FFA0]
0xe809fa2  nop
0xe809fa3  add rsp,0x28
0xe809fa7  pop rdi
0xe809fa8  pop rsi
0xe809fa9  ret
#endif

// Registry entry
LIFT_FN(sub_e809f40, "RendererContextD3D12 base slot 58", 0xe809f40, sub_e809f40, nullptr);

static_assert(kOff_0x20 == 0x20, "off 0x20");
static_assert(kOff_0x28 == 0x28, "off 0x28");
static_assert(kOff_0x30 == 0x30, "off 0x30");

} } // namespace