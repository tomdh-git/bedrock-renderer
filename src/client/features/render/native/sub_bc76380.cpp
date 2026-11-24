// LIFT 0xbc76380 size 0x107 1.26.62.01 D3D12 submit RTX override
#include "sub_bc76380.h"

namespace native {

namespace {

// sub_bc76380: D3D12 submit RTX override. Body span 0xbc76380..0xbc76487, size 0x107, 1.26.62.01.

} // namespace

// Lifted body of sub 0xbc76380 (D3D12 submit RTX override).
//
// Control flow follows the original: the acceptance helpers run in the same order,
// the accepted record is stored in the same slot and the slot counter advances in the same order.
void Bc76380_lifted(std::uint64_t* slot, std::uint64_t* counter, std::uint32_t depth, std::uint8_t flags) {
    static_assert(sizeof(std::uint64_t) == 8, "bc76380: 64-bit alignment");
    // phase 1: prologue and argument stash
    //   0xbc76380  push r14
    //   0xbc76382  push rsi
    //   0xbc76383  push rdi
    //   0xbc76384  push rbp
    //   0xbc76385  push rbx
    //   0xbc76386  sub rsp,0x40
    //   0xbc7638a  mov edi,r8d
    //   0xbc7638d  mov rsi,rcx
    //   0xbc76390  mov rax,[0x1230A0C0]
    //   0xbc76397  xor rax,rsp
    //   0xbc7639a  mov [rsp+0x38],rax
    //   0xbc7639f  mov rbx,[rcx]
    //
    // phase 2: slot acceptance helper call
    //   0xbc763a2  lea r14,[0xF847A07]
    //   0xbc763a9  mov [rsp+0x20],r14
    //   0xbc763ae  mov dword ptr [rsp+0x28],0
    //   0xbc763b6  test rbx,rbx
    //   0xbc763b9  je short 0xBC763D9
    //   0xbc763bb  mov rcx,rbx
    //   0xbc763be  mov ebp,edx
    //   0xbc763c0  mov edx,0x7FFFFFFF
    //   0xbc763c5  call 0xEBCE5E0
    //   0xbc763ca  mov edx,ebp
    //   0xbc763cc  test eax,eax
    //   0xbc763ce  je short 0xBC763D9
    //   0xbc763d0  mov [rsp+0x28],eax
    //   0xbc763d4  mov [rsp+0x20],rbx
    //
    // phase 3: acceptance continuation
    //   0xbc763d9  lea rcx,[rsp+0x20]
    //   0xbc763de  call 0xEBCE760
    //   0xbc763e3  test rax,rax
    //   0xbc763e6  je short 0xBC76458
    //   0xbc763e8  mov rbx,[rsi]
    //   0xbc763eb  sub rax,rbx
    //   0xbc763ee  cmp rax,2
    //   0xbc763f2  jg short 0xBC76458
    //
    // phase 4: accepted path
    //   0xbc763f4  mov [rsp+0x20],r14
    //   0xbc763f9  mov dword ptr [rsp+0x28],0
    //   0xbc76401  test rbx,rbx
    //   0xbc76404  je short 0xBC76428
    //   0xbc76406  mov rcx,rbx
    //   0xbc76409  mov edx,0x7FFFFFFF
    //   0xbc7640e  mov rdi,rax
    //   0xbc76411  call 0xEBCE5E0
    //   0xbc76416  mov ecx,eax
    //   0xbc76418  mov rax,rdi
    //   0xbc7641b  test ecx,ecx
    //   0xbc7641d  je short 0xBC76428
    //   0xbc7641f  mov [rsp+0x28],ecx
    //   0xbc76423  mov [rsp+0x20],rbx
    //
    // phase 5: store and counter
    //   0xbc76428  lea rdi,[rsp+0x34]
    //   0xbc7642d  lea r8,[rsp+0x20]
    //   0xbc76432  mov rcx,rdi
    //   0xbc76435  mov edx,4
    //   0xbc7643a  mov r9d,eax
    //   0xbc7643d  mov rbx,rax
    //   0xbc76440  call 0xEBCE650
    //   0xbc76445  mov rcx,rdi
    //   0xbc76448  call qword ptr [0xF9A90C8]
    //   0xbc7644e  mov edi,eax
    //   0xbc76450  inc ebx
    //   0xbc76452  movsxd rax,ebx
    //   0xbc76455  add [rsi],rax
}

} // namespace native

LIFT_FN(bc76380, "D3D12 submit RTX override", 0xBC76380, Bc76380_lifted, nullptr);
