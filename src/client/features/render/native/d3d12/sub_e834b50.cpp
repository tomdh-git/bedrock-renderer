// LIFT 0xe834b50 size 0xf4 1.26.62.01 sub_e834b50
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e834b50.h"

#include <cstdint>

namespace native::d3d12 {
static_assert(sizeof(void*) == 8, "x64");

#if 0
0xe834b50  push rsi
0xe834b51  push rdi
0xe834b52  push rbx
0xe834b53  sub rsp,0x30
0xe834b57  mov rdi,[rcx]
0xe834b5a  test rdi,rdi
0xe834b5d  je 0xE834C22
0xe834b63  mov rsi,rcx
0xe834b66  mov rbx,[rcx+8]
0xe834b6a  cmp rdi,rbx
0xe834b6d  je short 0xE834BE4
0xe834b6f  add rdi,0x40
0xe834b73  jmp short 0xE834B93
0xe834b75  nop [rax+rax]
0xe834b80  lea rax,[rdi+0x88]
0xe834b87  add rdi,0x48
0xe834b8b  cmp rdi,rbx
0xe834b8e  mov rdi,rax
0xe834b91  je short 0xE834BE1
0xe834b93  mov rcx,[rdi+0x38]
0xe834b97  test rcx,rcx
0xe834b9a  je short 0xE834BB7
0xe834b9c  cmp rdi,rcx
0xe834b9f  setne dl
0xe834ba2  mov rax,[rcx]
0xe834ba5  mov rax,[rax+0x20]
0xe834ba9  call qword ptr [0xF99FFA0]
0xe834baf  mov qword ptr [rdi+0x38],0
0xe834bb7  mov rcx,[rdi-8]
0xe834bbb  test rcx,rcx
0xe834bbe  je short 0xE834B80
0xe834bc0  lea rax,[rdi-0x40]
0xe834bc4  cmp rax,rcx
0xe834bc7  setne dl
0xe834bca  mov rax,[rcx]
0xe834bcd  mov rax,[rax+0x20]
0xe834bd1  call qword ptr [0xF99FFA0]
0xe834bd7  mov qword ptr [rdi-8],0
0xe834bdf  jmp short 0xE834B80
0xe834be1  mov rdi,[rsi]
0xe834be4  mov rdx,[rsi+0x10]
0xe834be8  sub rdx,rdi
0xe834beb  cmp rdx,0x1000
0xe834bf2  jb short 0xE834C0C
0xe834bf4  mov rax,[rdi-8]
0xe834bf8  add rdi,0xFFFFFFFFFFFFFFF8
0xe834bfc  sub rdi,rax
0xe834bff  cmp rdi,0x20
0xe834c03  jae short 0xE834C2A
0xe834c05  add rdx,0x27
0xe834c09  mov rdi,rax
0xe834c0c  mov rcx,rdi
0xe834c0f  call 0xE935700
0xe834c14  xorps xmm0,xmm0
0xe834c17  movups [rsi],xmm0
0xe834c1a  mov qword ptr [rsi+0x10],0
0xe834c22  add rsp,0x30
0xe834c26  pop rbx
0xe834c27  pop rdi
0xe834c28  pop rsi
0xe834c29  ret
0xe834c2a  mov qword ptr [rsp+0x20],0
0xe834c33  xor ecx,ecx
0xe834c35  xor edx,edx
0xe834c37  xor r8d,r8d
0xe834c3a  xor r9d,r9d
0xe834c3d  call qword ptr [0xF9A8C78]
#endif

void sub_e834b50(void* a0) {
    // 0xe834b50..0xe834b5d
    void* rdi = *reinterpret_cast<void**>(a0);
    if (!rdi) {
        // 0xe834c22..0xe834c29
        return;
    }
    // 0xe834b63..0xe834b73
    void* rsi = a0;
    void* rbx = *reinterpret_cast<void**>(static_cast<char*>(a0) + 8);
    if (rdi != rbx) {
        rdi = static_cast<char*>(rdi) + 0x40;
    } else {
        // 0xe834be4
        goto free_block;
    }
    // 0xe834b93 loop
    for (;;) {
        // 0xe834b93..0xe834baf
        void* rcx = *reinterpret_cast<void**>(static_cast<char*>(rdi) + 0x38);
        if (rcx) {
            unsigned char dl = (rdi != rcx) ? 1 : 0;
            auto vtbl = *reinterpret_cast<void**>(rcx);
            auto fn = *reinterpret_cast<void(*)(void*, unsigned char)>(static_cast<char*>(vtbl) + 0x20);
            // call through slot 0xF99FFA0
            using SlotFn = void(*)(void*, unsigned char);
            auto slot = *reinterpret_cast<SlotFn*>(0xF99FFA0ULL);
            fn(rcx, dl);
            *reinterpret_cast<void**>(static_cast<char*>(rdi) + 0x38) = nullptr;
        }
        // 0xe834bb7..0xe834bd7
        rcx = *reinterpret_cast<void**>(static_cast<char*>(rdi) - 8);
        if (rcx) {
            unsigned char dl2 = (static_cast<char*>(rdi) - 0x40 != rcx) ? 1 : 0;
            auto vtbl2 = *reinterpret_cast<void**>(rcx);
            auto fn2 = *reinterpret_cast<void(*)(void*, unsigned char)>(static_cast<char*>(vtbl2) + 0x20);
            using SlotFn2 = void(*)(void*, unsigned char);
            auto slot2 = *reinterpret_cast<SlotFn2*>(0xF99FFA0ULL);
            fn2(rcx, dl2);
            *reinterpret_cast<void**>(static_cast<char*>(rdi) - 8) = nullptr;
        }
        // 0xe834b80..0xe834b91
        void* rax = static_cast<char*>(rdi) + 0x88;
        rdi = static_cast<char*>(rdi) + 0x48;
        if (rdi == rbx) {
            rdi = *reinterpret_cast<void**>(rsi);
            goto free_block;
        }
        rdi = rax;
    }

free_block:
    // 0xe834be4..0xe834c1a
    void* rdx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x10);
    rdx = static_cast<char*>(rdx) - static_cast<char*>(rdi);
    if (rdx >= reinterpret_cast<void*>(0x1000)) {
        void* rax2 = *reinterpret_cast<void**>(static_cast<char*>(rdi) - 8);
        rdi = static_cast<char*>(rdi) - 8;
        rdi = static_cast<char*>(rdi) - static_cast<char*>(rax2);
        if (reinterpret_cast<std::uintptr_t>(rdi) >= 0x20) {
            // 0xe834c2a..0xe834c3d
            *reinterpret_cast<void**>(/*rsp+0x20*/nullptr) = nullptr;
            using SlotFn = void(*)(int,int,int,int);
            auto slot = *reinterpret_cast<SlotFn*>(0xF9A8C78ULL);
            slot(0,0,0,0);
        }
    // 0xe834c43..0xe834c44
        rdx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rdx) + 0x27);
        rdi = rax2;
    }
    sub_e935700(rdi);
    // zero
    // movups xmm0
    *reinterpret_cast<unsigned __int128*>(rsi) = 0;
    *reinterpret_cast<std::uint64_t*>(static_cast<char*>(rsi) + 0x10) = 0;
    // 0xe834c22
}

// Registry entry
LIFT_FN(sub_e834b50, "sub_e834b50", 0xe834b50, Off);

} // namespace native::d3d12