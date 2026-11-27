// LIFT 0xbcd41c0 size 0xad 1.26.62.01 sub_bcd41c0
#include "sub_bcd41c0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// sub_bcd41c0 (0xbcd41c0, size 0xad, 1.26.62.01).
//
// Walks a list of pointers stored in the argument object and processes each
// entry with sub_e87c6d0 + sub_e935700, then releases the remaining buffer
// region. Argument object layout (ArgLayout):
//   +0x00  void* field00  R/W: list current/start pointer
//   +0x08  void* field08  R/W: end pointer
//   +0x10  void* field10  R/W: buffer end pointer
//
// Calls:
//   0xbcd41f4  call 0xE87C6D0     -> native::sub_e87c6d0        (lift set)
//   0xbcd4201  call 0xE935700     -> native::sub_e935700        (lift set)
//   0xbcd4236  call 0xE935700     -> native::sub_e935700        (lift set)
//   0xbcd4266  call qword ptr [0xF9A8C78]  -> indirect via data slot (brief rule 69)
//
// x64 Microsoft ABI: argument in RCX, no return value.

void sub_bcd41c0(void* a0)
{
    auto* obj = reinterpret_cast<ArgLayout*>(a0);

    // 0xbcd41c0..0xbcd41c9   push r14; push rsi; push rdi; push rbx; sub rsp,0x28   (prologue)
    char* rdi = static_cast<char*>(obj->field00);  // 0xbcd41c9  mov rdi,[rcx]        R a0+0x0
    // 0xbcd41cc..0xbcd41cf   test rdi,rdi
    if (rdi == nullptr) {                        // 0xbcd41cc  test rdi,rdi ; 0xbcd41cf  je short 0xBCD4249
        return;                                  // 0xbcd4249..0xbcd4253   add rsp,0x28; pop; pop; pop; pop; ret
    }

    // 0xbcd41d1..0xbcd41d8   mov rsi,rcx ; mov r14,[rcx+8]
    char* rsi = static_cast<char*>(a0);          // 0xbcd41d1  mov rsi,rcx
    char* r14 = static_cast<char*>(obj->field08);  // 0xbcd41d4  mov r14,[rcx+8]    R a0+0x8

    // 0xbcd41d8..0xbcd41db   cmp rdi,r14
    if (rdi != r14) {                            // 0xbcd41d8  cmp rdi,r14 ; 0xbcd41db  jne short 0xBCD41E9
        do {
            // 0xbcd41e9..0xbcd41ef   mov rbx,[rdi] ; test rbx,rbx
            void* rbx = *reinterpret_cast<void**>(rdi);   // 0xbcd41e9  mov rbx,[rdi]
            if (rbx != nullptr) {                // 0xbcd41ec  test rbx,rbx ; 0xbcd41ef  je short 0xBCD41E0
                // 0xbcd41f1..0xbcd41f4   mov rcx,rbx ; call 0xE87C6D0
                native::sub_e87c6d0(rbx);        // 0xbcd41f4  call 0xE87C6D0
                // 0xbcd41f9..0xbcd4201   mov edx,0x38 ; mov rcx,rbx ; call 0xE935700
                native::sub_e935700(rbx);        // 0xbcd4201  call 0xE935700
            }
            // 0xbcd41e0..0xbcd41e4   add rdi,8
            rdi += 8;                            // 0xbcd41e0  add rdi,8
            // 0xbcd41e4..0xbcd41e7   cmp rdi,r14
        } while (rdi != r14);                    // 0xbcd41e7  je short 0xBCD4208
        // 0xbcd4208  mov rdi,[rsi]
        rdi = static_cast<char*>(obj->field00);  // 0xbcd4208  mov rdi,[rsi]      (= field00)
    }

    // 0xbcd420b..0xbcd4212   mov rdx,[rsi+0x10] ; sub rdx,rdi ; cmp rdx,0x1000
    uintptr_t remaining = (uintptr_t)(static_cast<char*>(obj->field10) - rdi);
    // 0xbcd4219  jb short 0xBCD4233
    if (remaining < 0x1000) {                    // 0xbcd4212  cmp rdx,0x1000 ; 0xbcd4219  jb short 0xBCD4233
        // 0xbcd4233  mov rcx,rdi ; call 0xE935700
        native::sub_e935700(rdi);                // 0xbcd4236  call 0xE935700
    } else {
        // 0xbcd421b  mov rax,[rdi-8]
        uintptr_t rax_val = *reinterpret_cast<uintptr_t*>(rdi - 8);
        // 0xbcd421f  add rdi,0xFFFFFFFFFFFFFFF8 ; 0xbcd4223  sub rdi,rax
        void* block_start = static_cast<void*>(rdi - 8 - static_cast<ptrdiff_t>(rax_val));
        // 0xbcd4226  cmp rdi,0x20 ; 0xbcd422a  jae short 0xBCD4253
        if (reinterpret_cast<uintptr_t>(block_start) >= 0x20) {  // 0xbcd422a  jae short 0xBCD4253
            // 0xbcd4253  mov qword ptr [rsp+0x20],0
            // 0xbcd425c..0xbcd4263   xor ecx,ecx ; xor edx,edx ; xor r8d,r8d ; xor r9d,r9d
            // 0xbcd4266  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
            using FnPtr = void (*)(void*, void*, void*, void*, void*);
            FnPtr fn = reinterpret_cast<FnPtr>(
                *reinterpret_cast<uintptr_t*>(0x140000000ULL + 0xF9A8C78ULL));
            fn(nullptr, nullptr, nullptr, nullptr, nullptr);
            // 0xbcd426c  int3   (trap after indirect call return; end of function)
            return;
        }
        // 0xbcd422c  add rdx,0x27   (dead store: rdx never read again)
        // 0xbcd4230  mov rdi,rax
        rdi = reinterpret_cast<char*>(rax_val);  // 0xbcd4230  mov rdi,rax
        // 0xbcd4233  mov rcx,rdi ; call 0xE935700
        native::sub_e935700(rdi);                // 0xbcd4236  call 0xE935700
    }

    // 0xbcd423b  xorps xmm0,xmm0
    // 0xbcd423e  movups [rsi],xmm0   ; zeroes a0+0x0 and a0+0x8 (16 bytes)
    // 0xbcd4241  mov qword ptr [rsi+0x10],0
    obj->field00 = nullptr;                      // 0xbcd423e  movups [rsi],xmm0
    obj->field08 = nullptr;
    obj->field10 = nullptr;                      // 0xbcd4241  mov [rsi+0x10],0

    // 0xbcd4249..0xbcd4253   add rsp,0x28 ; pop rbx ; pop rdi ; pop rsi ; pop r14 ; ret
}

// Verbatim instruction quotes (matches rdis dis 0xbcd41c0 0xad):
#if 0
0xbcd41c0  push r14
0xbcd41c2  push rsi
0xbcd41c4  push rbx
0xbcd41c5  sub rsp,0x28
0xbcd41c9  mov rdi,[rcx]
0xbcd41cc  test rdi,rdi
0xbcd41cf  je short 0xBCD4249
0xbcd41d1  mov rsi,rcx
0xbcd41d4  mov r14,[rcx+8]
0xbcd41d8  cmp rdi,r14
0xbcd41db  jne short 0xBCD41E9
0xbcd41dd  jmp short 0xBCD420B
0xbcd41df  nop
0xbcd41e0  add rdi,8
0xbcd41e4  cmp rdi,r14
0xbcd41e7  je short 0xBCD4208
0xbcd41e9  mov rbx,[rdi]
0xbcd41ec  test rbx,rbx
0xbcd41ef  je short 0xBCD41E0
0xbcd41f1  mov rcx,rbx
0xbcd41f4  call 0xE87C6D0
0xbcd41f9  mov edx,0x38
0xbcd41fe  mov rcx,rbx
0xbcd4201  call 0xE935700
0xbcd4206  jmp short 0xBCD41E0
0xbcd4208  mov rdi,[rsi]
0xbcd420b  mov rdx,[rsi+0x10]
0xbcd420f  sub rdx,rdi
0xbcd4212  cmp rdx,0x1000
0xbcd4219  jb short 0xBCD4233
0xbcd421b  mov rax,[rdi-8]
0xbcd421f  add rdi,0xFFFFFFFFFFFFFFF8
0xbcd4223  sub rdi,rax
0xbcd4226  cmp rdi,0x20
0xbcd422a  jae short 0xBCD4253
0xbcd422c  add rdx,0x27
0xbcd4230  mov rdi,rax
0xbcd4233  mov rcx,rdi
0xbcd4236  call 0xE935700
0xbcd423b  xorps xmm0,xmm0
0xbcd423e  movups [rsi],xmm0
0xbcd4241  mov qword ptr [rsi+0x10],0
0xbcd4249  add rsp,0x28
0xbcd424d  pop rbx
0xbcd424e  pop rdi
0xbcd424f  pop rsi
0xbcd4250  pop r14
0xbcd4252  ret
0xbcd4253  mov qword ptr [rsp+0x20],0
0xbcd425c  xor ecx,ecx
0xbcd425e  xor edx,edx
0xbcd4260  xor r8d,r8d
0xbcd4263  xor r9d,r9d
0xbcd4266  call qword ptr [0xF9A8C78]
0xbcd426c  int3
#endif

LIFT_FN(sub_bcd41c0, "sub_bcd41c0", 0xbcd41c0, sub_bcd41c0, nullptr);

} // namespace native
