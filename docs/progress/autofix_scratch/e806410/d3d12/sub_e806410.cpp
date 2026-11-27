// LIFT 0xe806410 size 0x127 1.26.62.01 sub_e806410

#include "sub_e806410.h"
#include "client/features/render/native/Lift.h"
#include <cstddef>
static_assert(sizeof(void*) == 8, "ptr");

#if 0
0xe806410  push rsi
0xe806411  sub rsp,0x30
0xe806415  mov rsi,rcx
0xe806418  mov rcx,[rcx+8]
0xe80641c  mov r8,[rsi+0x10]
0xe806420  sub r8,rcx
0xe806423  sar r8,3
0xe806427  mov r9,[rdx]
0xe80642a  mov rax,[rdx+0x10]
0xe8064be  add r8,0xFFFFFFFFFFFFFFFE
0xe8064c2  and r8,r10
0xe8064d0  cmp [rcx+r8*8],rdx
0xe8064d4  jne short 0xE8064E0
0xe8064d6  mov [rcx+r8*8],rax
0xe8064da  sub r8,1
0xe8064de  jae short 0xE8064D0
0xe8064e0  mov rcx,[rdx+0x18]
0xe8064e4  test rcx,rcx
0xe8064e7  je short 0xE8064F1
0xe8064e9  mov r8,[rdx+0x10]
0xe8064ed  mov [rcx+0x10],r8
0xe8064f1  test rax,rax
0xe8064f4  je short 0xE8064FE
0xe8064f6  mov rcx,[rdx+0x18]
0xe8064fa  mov [rax+0x18],rcx
0xe8064fe  mov rcx,[0x12ADF800]
0xe806505  test rcx,rcx
0xe806508  je short 0xE80652E
0xe80650a  mov rax,[rcx]
0xe80650d  mov rax,[rax+8]
0xe806511  mov dword ptr [rsp+0x28],0
0xe806519  mov qword ptr [rsp+0x20],0
0xe806522  xor r8d,r8d
0xe806525  xor r9d,r9d
0xe806528  call qword ptr [0xF99FFA0]
0xe80652e  dec qword ptr [rsi]
0xe806531  add rsp,0x30
0xe806535  pop rsi
0xe806536  ret
#endif

extern "C" void sub_e806410(void* a0, void* a1) {
    // 0xe806410..0xe806415

    void* rsi = a0;
    // 0xe806418..0xe806423

    void** rcx = *(void***)((char*)rsi + 0x8); // begin

    void** r8p = *(void***)((char*)rsi + 0x10); // end

    std::ptrdiff_t r8 = (r8p - rcx) >> 3; // sar 3

    // 0xe806427..0xe8064bb: hash r9 -> r10

    unsigned long long r9 = *(unsigned long long*)a1;
    long long r10 = (signed char)(r9 & 0xFF);
    int r11;
    // byte 1

    r11 = (int)((r9 >> 8) & 0xFF); r11 = (signed char)r11;
    r10 = r10 * 0x1003F + r11;
    r11 = (int)((r9 >> 16) & 0xFF); r11 = (signed char)r11;
    r10 = r10 * 0x1003F + r11;
    r11 = (int)((r9 >> 24) & 0xFF); r11 = (signed char)r11;
    r10 = r10 * 0x1003F + r11;
    // byte 4

    long long t = (long long)(r9 >> 32); t = (signed char)(t & 0xFF);
    r10 = r10 * 0x1003F + t;
    t = (long long)(r9 >> 40); t = (signed char)(t & 0xFF);
    r10 = r10 * 0x1003F + t;
    t = (long long)(r9 >> 48); t = (signed char)(t & 0xFF);
    r10 = r10 * 0x1003F + t;
    t = (long long)(r9 >> 56); // sar 56

    r10 = r10 * 0x1003F + t;
    // 0xe8064be..0xe8064c2

    r8 = (r8 + (-2)) & r10;
    // 0xe8064c5..0xe8064c5

    // nop [rax+rax]

    // loop 0xe8064d0..0xe8064de

    void* rax = *(void**)((char*)a1 + 0x10);
    for (;;) {
        if (rcx[r8] == a1) { // cmp [rcx+r8*8],rdx

            rcx[r8] = rax; // mov

            --r8;
            if (r8 >= 0) continue; else break;
        } else {
            break;
        }
    }
    // 0xe8064e0

    void* rcx2 = *(void**)((char*)a1 + 0x18);
    if (rcx2) {
        void* r8v = *(void**)((char*)a1 + 0x10);
        *(void**)((char*)rcx2 + 0x10) = r8v;
    }
    if (rax) {
        void* rcx3 = *(void**)((char*)a1 + 0x18);
        *(void**)((char*)rax + 0x18) = rcx3;
    }
    // 0xe8064fe

    void* data = *(void**)0x12ADF800;
    if (data) {
        void** vtbl = *(void***)data;
        auto fn = (void(*)(void*,void*,void*,void*,void*,int,void*))vtbl[1]; // [rax+8]

        void* slot = *(void**)0xF99FFA0;
        // args: rcx=data, rdx=0, r8=0, r9=0, [rsp+0x20]=0, [rsp+0x28]=0

        ((void(*)(void*,void*,void*,void*,void*,int,void*))slot)(data, nullptr, nullptr, nullptr, 0, 0, nullptr);
        (void)fn;
    }
    // 0xe80652e

    --*(unsigned long long*)rsi;
}

// LIFT_FN registry entry

// native::registry::register_fn("sub_e806410", 0xe806410, &sub_e806410);

@9@<|channel|>assistant<|channel|>analysis<|message|>Wait the loop logic: original loop continues while cmp equal and r8 >= 0 after decrement. My for loop breaks when not equal. But after decrement if r8>=0 (jae) jumps back to compare. If r8 <0 (unsigned) exits. I used if (r8>=0) continue; else break. Good. But r8 is ptrdiff_t; after decrement could be -1. Compare unsigned? original `jae` treats r8 unsigned. Since r8 starts nonnegative and decrements, when r8=0, decrement -> -1 as unsigned huge >=0? Wait jae after sub r8,1: if r8 (unsigned) >=0 always true unless underflow? Actually sub sets flags; jae means unsigned >=. After sub, if result unsigned >= 0 always except... jae is carry flag clear. sub of 0 -1 sets carry, so jae false. So exits when r8 was 0. My `if (r8 >= 0)` where r8 is signed ptrdiff_t: after decrement r8=-1, signed >=0 false -> break. Good. But if r8 started huge? no.

The boundary call: original calls slot with r8d=0, r9d=0, [rsp+0x20]=0 (qword), [rsp+0x28]=0 (dword). I passed (data, nullptr, nullptr, nullptr, 0, 0, nullptr) -> rdx=null, r8=null(0), r9=null(0), then stack args: r8d? Let me map: Microsoft ABI: rcx, rdx, r8, r9, then stack. Original: rcx=data, rdx=0 (xor r8d? wait r8d zeroed -> r8=0 but r8 is 4th? Let's check: xor r8d,r8d sets r8=0 (3rd arg). xor r9d,r9d sets r9=0 (4th arg). [rsp+0x20]=0 (5th arg). [rsp+0x28]=0 (6th arg, dword but slot expects? unknown). Actually call target sub_eea6040 signature unknown. We just call via slot with same args. I'll keep as is.

Now create dossier.<|end|><|start|> fileList to=assistant<|channel|>analysis <|constrain|>xml<|message|><rfl:parameter name="command">
mkdir -p docs/functions 2>/dev/null; python -c "print('ok')"