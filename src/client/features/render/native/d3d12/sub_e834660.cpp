// LIFT 0xe834660 size 0x15f 1.26.62.01 sub_e834660
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e834660.h"

#include <cstdint>

namespace native::d3d12 {
static_assert(sizeof(void*) == 8, "x64");

#if 0
0xe834660  push rbp
0xe834661  push rsi
0xe834662  push rdi
0xe834663  push rbx
0xe834664  sub rsp,0x38
0xe834668  lea rbp,[rsp+0x30]
0xe83466d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xe834675  mov rsi,rcx
0xe834678  mov qword ptr [rcx+0xE030],0
0xe834683  mov rax,[rcx+0xE028]
0xe83468a  test rax,rax
0xe83468d  je 0xE834716
0xe834693  mov rdx,[rax]
0xe834696  lea rdi,[0xF7CC762]
0xe83469d  nop [rax]
0xe8346a0  test rdx,rdx
0xe8346a3  je short 0xE8346E0
0xe8346a5  mov rbx,[rdx+0x2000]
0xe8346ac  mov rcx,[0x12ADF800]
0xe8346b3  mov rax,[rcx]
0xe8346b6  mov rax,[rax+8]
0xe8346ba  mov r10,[0xF99FFA0]
0xe8346c1  mov [rsp+0x20],rdi
0xe8346c6  mov dword ptr [rsp+0x28],0
0xe8346ce  mov r9d,1
0xe8346d4  xor r8d,r8d
0xe8346d7  call r10
0xe8346da  nop
0xe8346db  mov rdx,rbx
0xe8346de  jmp short 0xE8346A0
0xe8346e0  mov rdx,[rsi+0xE028]
0xe8346e7  mov rcx,[0x12ADF800]
0xe8346ee  mov rax,[rcx]
0xe8346f1  mov rax,[rax+8]
0xe8346f5  mov r10,[0xF99FFA0]
0xe8346fc  mov [rsp+0x20],rdi
0xe834701  mov dword ptr [rsp+0x28],0
0xe834709  mov r9d,1
0xe83470f  xor r8d,r8d
0xe834712  call r10
0xe834715  nop
0xe834716  mov qword ptr [rsi+0xC010],0
0xe834721  mov rax,[rsi+0xC008]
0xe834728  test rax,rax
0xe83472b  je 0xE8347B6
0xe834731  mov rdx,[rax]
0xe834734  lea rdi,[0xF7CC762]
0xe83473b  nop [rax+rax]
0xe834740  test rdx,rdx
0xe834743  je short 0xE834780
0xe834745  mov rbx,[rdx+0xC000]
0xe83474c  mov rcx,[0x12ADF800]
0xe834753  mov rax,[rcx]
0xe834756  mov rax,[rax+8]
0xe83475a  mov r10,[0xF99FFA0]
0xe834761  mov [rsp+0x20],rdi
0xe834766  mov dword ptr [rsp+0x28],0
0xe83476e  mov r9d,1
0xe834774  xor r8d,r8d
0xe834777  call r10
0xe83477a  nop
0xe83477b  mov rdx,rbx
0xe83477e  jmp short 0xE834740
0xe834780  mov rdx,[rsi+0xC008]
0xe834787  mov rcx,[0x12ADF800]
0xe83478e  mov rax,[rcx]
0xe834791  mov rax,[rax+8]
0xe834795  mov r10,[0xF99FFA0]
0xe83479c  mov [rsp+0x20],rdi
0xe8347a1  mov dword ptr [rsp+0x28],0
0xe8347a9  mov r9d,1
0xe8347af  xor r8d,r8d
0xe8347b2  call r10
0xe8347b5  nop
0xe8347b6  add rsp,0x38
0xe8347ba  pop rbx
0xe8347bb  pop rdi
0xe8347bc  pop rsi
0xe8347bd  pop rbp
0xe8347be  ret
#endif

void sub_e834660(void* a0) {
    // 0xe834660..0xe834678
    auto* rsi = a0;
    *reinterpret_cast<std::uint64_t*>(static_cast<char*>(rsi) + 0xE030) = 0;
    // 0xe834683..0xe83468d
    auto* rax = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0xE028);
    if (rax) {
        // 0xe834693..0xe83469d
        auto* rdx = *reinterpret_cast<void**>(rax);
        const char* rdi = "NOFILE";
        // 0xe8346a0..0xe8346de
        while (rdx) {
            auto* rbx = *reinterpret_cast<void**>(static_cast<char*>(rdx) + 0x2000);
            auto* rcx = *reinterpret_cast<void**>(0x12ADF800ULL);
            auto fn = *reinterpret_cast<void(**)(void*, std::uint32_t, std::uint32_t, std::uint32_t, const char*, std::uint32_t)>(reinterpret_cast<char*>(*reinterpret_cast<void**>(rcx)) + 8);
            // call through slot 0xF99FFA0
            using CallFn = void(*)(void*, std::uint32_t, std::uint32_t, std::uint32_t, const char*, std::uint32_t);
            auto slot = *reinterpret_cast<CallFn*>(0xF99FFA0ULL);
            // args: rcx (from rcx+8 vtable), r8d=0, r9d=1, rsp+0x20=rdi, rsp+0x28=0
            slot(rcx, 0, 1, 0, rdi, 0);
            rdx = rbx;
        }
        // 0xe8346e0..0xe834715
        rdx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0xE028);
        rcx = *reinterpret_cast<void**>(0x12ADF800ULL);
        fn = *reinterpret_cast<void(**)(...)>(reinterpret_cast<char*>(*reinterpret_cast<void**>(rcx)) + 8);
        slot = *reinterpret_cast<CallFn*>(0xF99FFA0ULL);
        slot(rcx, 0, 1, 0, rdi, 0);
    }
    // 0xe834716..0xe8347b5
    *reinterpret_cast<std::uint64_t*>(static_cast<char*>(rsi) + 0xC010) = 0;
    rax = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0xC008);
    if (rax) {
        auto* rdx2 = *reinterpret_cast<void**>(rax);
        const char* rdi2 = "NOFILE";
        while (rdx2) {
            auto* rbx2 = *reinterpret_cast<void**>(static_cast<char*>(rdx2) + 0xC000);
            auto* rcx2 = *reinterpret_cast<void**>(0x12ADF800ULL);
            auto slot2 = *reinterpret_cast<CallFn*>(0xF99FFA0ULL);
            slot2(rcx2, 0, 1, 0, rdi2, 0);
            rdx2 = rbx2;
        }
        rdx2 = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0xC008);
        auto* rcx3 = *reinterpret_cast<void**>(0x12ADF800ULL);
        auto slot3 = *reinterpret_cast<CallFn*>(0xF99FFA0ULL);
        slot3(rcx3, 0, 1, 0, rdi2, 0);
    }
    // 0xe8347b6..0xe8347be
}

// Registry entry
LIFT_FN(sub_e834660, "sub_e834660", 0xe834660, Off);

} // namespace native::d3d12