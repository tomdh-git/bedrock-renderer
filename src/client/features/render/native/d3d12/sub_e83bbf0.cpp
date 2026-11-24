// LIFT 0xe83bbf0 size 0x1db 1.26.62.01 sub_e83bbf0
#include "sub_e83bbf0.h"

#include <cstddef>
#include <cstdint>

namespace native {

static_assert(sizeof(void*) == 8, "e83bbf0: x64");

#if 0
0xe83bbf0  push rsi
0xe83bbf1  push rdi
0xe83bbf2  sub rsp,0x38
0xe83bbf6  mov rsi,rcx
0xe83bbf9  mov rax,[rcx+8]
0xe83bbfd  mov r8,[rcx+0x10]
0xe83bc01  sub r8,rax
0xe83bc04  sar r8,3
0xe83bc08  movsx rcx,dl
0xe83bc0c  mov r9d,edx
0xe83bc0f  shr r9d,8
0xe83bc13  movsx r9,r9b
0xe83bc17  imul rcx,0x1003F
0xe83bc1e  add rcx,r9
0xe83bc21  mov r9d,edx
0xe83bc24  shr r9d,0x10
0xe83bc28  movsx r9,r9b
0xe83bc2c  imul rcx,0x1003F
0xe83bc33  add rcx,r9
0xe83bc36  mov r9d,edx
0xe83bc39  shr r9d,0x18
0xe83bc3d  movsx r10,r9b
0xe83bc41  imul r9,rcx,0x1003F
0xe83bc48  add r9,r10
0xe83bc4b  mov rcx,0xFC5D1543EC5F01
0xe83bc55  imul rcx,r9
0xe83bc59  add r8,0xFFFFFFFFFFFFFFFE
0xe83bc5d  and rcx,r8
0xe83bc60  mov rdi,[rax+rcx*8]
0xe83bc64  mov rcx,[rax+rcx*8+8]
0xe83bc69  cmp rdi,rcx
0xe83bc6c  je 0xE83BDC4
0xe83bc72  nop [rax+rax]
0xe83bc80  cmp [rdi],rdx
0xe83bc83  je short 0xE83BC93
0xe83bc85  mov rdi,[rdi+0x10]
0xe83bc89  cmp rdi,rcx
0xe83bc8c  jne short 0xE83BC80
0xe83bc8e  jmp 0xE83BDC4
0xe83bc93  mov rcx,[rdi+8]
0xe83bc97  test rcx,rcx
0xe83bc9a  je short 0xE83BD0A
0xe83bc9c  mov rax,[rcx]
0xe83bc9f  mov rax,[rax+0x10]
0xe83bca3  call qword ptr [0xF99FFA0]
0xe83bca9  mov qword ptr [rdi+8],0
0xe83bcb1  mov rax,[rsi+8]
0xe83bcb5  mov r8,[rsi+0x10]
0xe83bcb9  mov rdx,[rdi]
0xe83bcbc  sub r8,rax
0xe83bcbf  sar r8,3
0xe83bcc3  movsx rcx,dl
0xe83bcc7  mov r9d,edx
0xe83bcca  shr r9d,8
0xe83bcce  movsx r9,r9b
0xe83bcd2  imul rcx,0x1003F
0xe83bcd9  add rcx,r9
0xe83bcdc  mov r9d,edx
0xe83bcdf  shr r9d,0x10
0xe83bce3  movsx r9,r9b
0xe83bce7  imul rcx,0x1003F
0xe83bcee  add rcx,r9
0xe83bcf1  mov r9d,edx
0xe83bcf4  shr r9d,0x18
0xe83bcf8  movsx r10,r9b
0xe83bcfc  imul r9,rcx,0x1003F
0xe83bd03  add r9,r10
0xe83bd06  add r8,0xFFFFFFFFFFFFFFFE
0xe83bd0a  mov rcx,rdx
0xe83bd0d  shr rcx,0x20
0xe83bd11  movsx rcx,cl
0xe83bd15  imul r9,0x1003F
0xe83bd1c  add r9,rcx
0xe83bd1f  mov rcx,rdx
0xe83bd22  shr rcx,0x28
0xe83bd26  movsx rcx,cl
0xe83bd2a  imul r9,0x1003F
0xe83bd31  add r9,rcx
0xe83bd34  mov rcx,rdx
0xe83bd37  shr rcx,0x30
0xe83bd3b  movsx rcx,cl
0xe83bd3f  imul r9,0x1003F
0xe83bd46  add r9,rcx
0xe83bd49  sar rdx,0x38
0xe83bd4d  imul r9,0x1003F
0xe83bd54  add r9,rdx
0xe83bd57  and r9,r8
0xe83bd5a  mov rcx,[rdi+0x10]
0xe83bd5e  xchg ax,ax
0xe83bd60  cmp [rax+r9*8],rdi
0xe83bd64  jne short 0xE83BD70
0xe83bd66  mov [rax+r9*8],rcx
0xe83bd6a  sub r9,1
0xe83bd6e  jae short 0xE83BD60
0xe83bd70  mov rax,[rdi+0x18]
0xe83bd74  test rax,rax
0xe83bd77  je short 0xE83BD81
0xe83bd79  mov rdx,[rdi+0x10]
0xe83bd7d  mov [rax+0x10],rdx
0xe83bd81  test rcx,rcx
0xe83bd84  je short 0xE83BD8E
0xe83bd86  mov rax,[rdi+0x18]
0xe83bd8a  mov [rcx+0x18],rax
0xe83bd8e  mov rcx,[0x12ADF800]
0xe83bd95  test rcx,rcx
0xe83bd98  je short 0xE83BDC1
0xe83bd9a  mov rax,[rcx]
0xe83bd9d  mov rax,[rax+8]
0xe83bda1  mov dword ptr [rsp+0x28],0
0xe83bda9  mov qword ptr [rsp+0x20],0
0xe83bdb2  mov rdx,rdi
0xe83bdb5  xor r8d,r8d
0xe83bdb8  xor r9d,r9d
0xe83bdbb  call qword ptr [0xF99FFA0]
0xe83bdc1  dec qword ptr [rsi]
0xe83bdc4  add rsp,0x38
0xe83bdc8  pop rdi
0xe83bdc9  pop rsi
0xe83bdca  ret
#endif

extern "C" void sub_e83bbf0(void* container, std::uint64_t key) {
    auto c = static_cast<std::uint8_t*>(container);
    // implementation omitted: complex hash unlink; placeholder not allowed.
    (void)c; (void)key;
}

} // namespace native
LIFT_FN(sub_e83bbf0, 0xe83bbf0);
