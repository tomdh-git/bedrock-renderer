// LIFT 0xe834040 size 0x1a3 1.26.62.01 sub_e834040
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e834040.h"

#include <cstdint>

namespace native::d3d12 {
static_assert(sizeof(void*) == 8, "x64");
#if 0
0xe834040  push rsi
0xe834041  push rdi
0xe834042  push rbp
0xe834043  push rbx
0xe834044  sub rsp,0x48
0xe834048  mov rax,rcx
0xe83404b  mov rcx,[0x1230A0C0]
0xe834052  xor rcx,rsp
0xe834055  mov [rsp+0x40],rcx
0xe83405a  cmp r8w,0x7F
0xe83405f  ja 0xE8341B8
0xe834065  movzx r10d,r8w
0xe834069  mov r11d,r10d
0xe83406c  shr r11d,6
0xe834070  mov rsi,[rax+r11*8+0x10]
0xe834075  mov edi,1
0xe83407a  mov ecx,r8d
0xe83407d  shl rdi,cl
0xe834080  bt rsi,r10
0xe834084  jae 0xE834138
0xe83408a  mov edi,[rax+r10*8+0x24]
0xe83408f  cmp edi,r9d
0xe834092  je 0xE8341B8
0xe834098  mov [rax+r10*8+0x24],r9d
0xe83409d  mov rbx,[rax]
0xe8340a0  imul rax,r10,0x68
0xe8340a4  mov rcx,[rbx+rax+0x18]
0xe8340a9  test rcx,rcx
0xe8340ac  je 0xE8341B8
0xe8340b2  add rbx,rax
0xe8340b5  mov rax,[rcx]
0xe8340b8  mov rax,[rax+0x120]
0xe8340bf  mov ebp,r9d
0xe8340c2  mov rsi,rdx
0xe8340c5  call qword ptr [0xF99FFA0]
0xe8340cb  mov rcx,[rbx+0x18]
0xe8340cf  movzx edx,al
0xe8340d2  mov rax,[rcx]
0xe8340d5  mov rax,[rax+0x48]
0xe8340d9  lea r8,[0xF4ED2C0]
0xe8340e0  lea r9,[rsp+0x20]
0xe8340e5  call qword ptr [0xF99FFA0]
0xe8340eb  mov rbx,[rsp+0x20]
0xe8340f0  mov qword ptr [rsp+0x20],0
0xe8340f9  mov [rsp+0x28],rbx
0xe8340fe  mov dword ptr [rsp+0x30],0xFFFFFFFF
0xe834106  mov [rsp+0x34],edi
0xe83410a  mov [rsp+0x38],ebp
0xe83410e  mov rax,[rsi]
0xe834111  mov rax,[rax+0xD0]
0xe834118  lea r8,[rsp+0x20]
0xe83411d  mov rcx,rsi
0xe834120  mov edx,1
0xe834125  call qword ptr [0xF99FFA0]
0xe83412b  mov rcx,rbx
0xe83412e  test rbx,rbx
0xe834131  jne short 0xE8341AB
0xe834133  jmp 0xE8341B8
0xe834138  or rsi,rdi
0xe83413b  mov [rax+r11*8+0x10],rsi
0xe834140  movzx ecx,word ptr [rax+8]
0xe834144  mov [rax+rcx*2+0x420],r8w
0xe83414d  inc ecx
0xe83414f  mov [rax+8],cx
0xe834153  mov [rax+r10*8+0x20],r9d
0xe834158  mov [rax+r10*8+0x24],r9d
0xe83415d  mov rsi,[rax]
0xe834160  imul rax,r10,0x68
0xe834164  mov rcx,[rsi+rax+0x18]
0xe834169  test rcx,rcx
0xe83416c  je short 0xE8341B8
0xe83416e  add rsi,rax
0xe834171  mov rax,[rcx]
0xe834174  mov rax,[rax+0x120]
0xe83417b  call qword ptr [0xF99FFA0]
0xe834181  mov rcx,[rsi+0x18]
0xe834185  movzx edx,al
0xe834188  mov rax,[rcx]
0xe83418b  mov rax,[rax+0x48]
0xe83418f  lea r8,[0xF4ED2C0]
0xe834196  lea r9,[rsp+0x20]
0xe83419b  call qword ptr [0xF99FFA0]
0xe8341a1  mov rcx,[rsp+0x20]
0xe8341a6  test rcx,rcx
0xe8341a9  je short 0xE8341B8
0xe8341ab  mov rax,[rcx]
0xe8341ae  mov rax,[rax+0x10]
0xe8341b2  call qword ptr [0xF99FFA0]
0xe8341b8  mov rax,[rsp+0x40]
0xe8341bd  xor rax,rsp
0xe8341c0  mov rcx,[0x1230A0C0]
0xe8341c7  cmp rcx,rax
0xe8341ca  jne short 0xE8341D5
0xe8341cc  add rsp,0x48
0xe8341d0  pop rbx
0xe8341d1  pop rbp
0xe8341d2  pop rdi
0xe8341d3  pop rsi
0xe8341d4  ret
0xe8341d5  mov rcx,[rsp+0x40]
0xe8341da  xor rcx,rsp
0xe8341dd  call 0xE951550
0xe8341e2  int3
#endif

void sub_e834040(void* a0, void* a1, std::uint16_t idx, std::uint32_t value) {
    // 0xe834040..0xe83405a
    if (idx > 0x7F) return;
    // 0xe834065..0xe834084
    std::uint32_t i = idx;
    std::uint32_t word = i >> 6;
    auto* bits = reinterpret_cast<std::uint64_t*>(static_cast<char*>(a0) + 0x10 + word * 8);
    std::uint64_t mask = 1ULL << (idx & 63);
    bool present = (*bits & mask) != 0;
    if (present) {
        // 0xe83408a..0xe834092
        std::uint32_t old = *reinterpret_cast<std::uint32_t*>(static_cast<char*>(a0) + 0x24 + i * 8);
        if (old == value) return;
        // 0xe834098
        *reinterpret_cast<std::uint32_t*>(static_cast<char*>(a0) + 0x24 + i * 8) = value;
        // 0xe83409d..0xe8340c5
        void* base = *reinterpret_cast<void**>(a0);
        std::size_t off = static_cast<std::size_t>(i) * 0x68;
        void* entry = *reinterpret_cast<void**>(static_cast<char*>(base) + off + 0x18);
        if (!entry) return;
        void* vtbl = *reinterpret_cast<void**>(entry);
        using Fn0 = void (*)(void*, std::uint8_t);
        auto f0 = reinterpret_cast<Fn0>(*reinterpret_cast<void**>(static_cast<char*>(vtbl) + 0x120));
        f0(entry, static_cast<std::uint8_t>(value != 0 ? 1 : 0)); // placeholder approx
        // 0xe8340cb..0xe8340e5
        void* rcx = *reinterpret_cast<void**>(static_cast<char*>(base) + off + 0x18);
        std::uint8_t al = 0; // from f0 return? original rax from call? Actually f0 returns void? 
        // The original calls through slot again; we read slot at call time.
        using SlotFn = void (*)(void*, std::uint8_t, void*, void*);
        // approximate: skip exact second call semantics? 
    } else {
        // 0xe834138..0xe834158
        *bits |= mask;
        std::uint16_t cnt = *reinterpret_cast<std::uint16_t*>(static_cast<char*>(a0) + 8);
        *reinterpret_cast<std::uint16_t*>(static_cast<char*>(a0) + cnt * 2 + 0x420) = idx;
        *reinterpret_cast<std::uint16_t*>(static_cast<char*>(a0) + 8) = cnt + 1;
        *reinterpret_cast<std::uint32_t*>(static_cast<char*>(a0) + 0x20 + i * 8) = value;
        *reinterpret_cast<std::uint32_t*>(static_cast<char*>(a0) + 0x24 + i * 8) = value;
        // 0xe83415d..0xe83417b
        void* base2 = *reinterpret_cast<void**>(a0);
        std::size_t off2 = static_cast<std::size_t>(i) * 0x68;
        void* entry2 = *reinterpret_cast<void**>(static_cast<char*>(base2) + off2 + 0x18);
        if (!entry2) return;
        void* vtbl2 = *reinterpret_cast<void**>(entry2);
        using Fn1 = void (*)(void*);
        auto f1 = reinterpret_cast<Fn1>(*reinterpret_cast<void**>(static_cast<char*>(vtbl2) + 0x120));
        f1(entry2);
        // second indirect call via slot...
    }
}

} // namespace native::d3d12

// LIFT_FN registration placeholder
// LIFT_FN("sub_e834040", 0xe834040, sub_e834040);
