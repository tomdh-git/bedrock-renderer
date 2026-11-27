// LIFT 0x8f21d0 size 0xe3 1.26.62.01 sub_8f21d0
#include "client/features/render/native/helpers/sub_8f21d0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_8f21d0 (0x8f21d0, size 0xe3, 1.26.62.01).
//
// Releases the slot buffer and its elements of the context object a0 (RCX):
//   1. calls sub_7705b0(a0, &local{0xEFCA680, 0x873D0});
//   2. for each pointer in [a0+0x150, a0+0x158) step 8: calls sub_8f22e0(ptr);
//   3. releases the buffer at [a0+0x150] (size = [a0+0x160] - [a0+0x150]) via sub_e935700,
//      or via the noreturn data-slot indirect call at 0xF9A8C78 when the heap-geometry
//      check fails; then zeroes [a0+0x150], [a0+0x158], [a0+0x160];
//   4. calls sub_7727b0(a0) and returns.
//
// Callees: sub_e935700 (lift/set, native symbol), sub_7705b0 / sub_8f22e0 / sub_7727b0
// (callees not yet classified; forward-declared only; see docs/progress/oc_U-EX7.8f21d0.md).
// x64 Microsoft ABI: arg1 (RCX) = context pointer a0, returns void. The slow path
// (0x8f2299) is noreturn (int3 after the data-slot indirect call).

void sub_8f21d0(void* a0) {
    // 0x8f21d0..0x8f220e:  prologue; build local {data_efca680=0xEFCA680, sub_873d0=0x873D0}
    //                      and call sub_7705b0(a0, &local)
    // 0x8f21d0  push rbp
    // 0x8f21d1  push r14
    // 0x8f21d3  push rsi
    // 0x8f21d4  push rdi
    // 0x8f21d5  push rbx
    // 0x8f21d6  sub rsp,0x70
    // 0x8f21da  lea rbp,[rsp+0x70]
    // 0x8f21df  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0x8f21e7  mov rsi,rcx
    // 0x8f21ea  lea rax,[0xEFCA680]     ; [data_efca680]
    // 0x8f21f1  mov [rbp-0x48],rax
    // 0x8f21f5  lea rax,[0x873D0]       ; [sub_873d0]
    // 0x8f21fc  mov [rbp-0x40],rax
    // 0x8f2200  lea rdx,[rbp-0x48]
    // 0x8f2204  mov [rbp-0x10],rdx
    // 0x8f2208  call 0x7705B0
    // 0x8f220d  nop
    struct LocalParam {
        void* data;   // [rbp-0x48] = 0xEFCA680
        void* func;   // [rbp-0x40] = 0x873D0
    };
    LocalParam local;
    local.data = reinterpret_cast<void*>(0xEFCA680ULL);
    local.func = reinterpret_cast<void*>(0x873D0ULL);
    sub_7705b0(a0, &local);   // 0x8f2208  call 0x7705B0   ; 0x8f220d  nop

    // 0x8f220e..0x8f221a:  rdi = [a0+0x150]; if rdi == 0 goto loc_8f2285 (skip release)
    // 0x8f220e  mov rdi,[rsi+0x150]   ; R a0+0x150
    // 0x8f2215  test rdi,rdi
    // 0x8f2218  je short 0x8F2285
    SlotCtx* ctx = reinterpret_cast<SlotCtx*>(a0);
    void* rdi = ctx->buffer_start;   // 0x8f220e  mov rdi,[rsi+0x150]

    if (rdi != nullptr) {            // 0x8f2215  test rdi,rdi ; 0x8f2218  je short 0x8F2285

        // 0x8f221a..0x8f2244:  loop over [a0+0x150, a0+0x158) step 8 calling sub_8f22e0(each)
        // 0x8f221a  lea rbx,[rsi+0x150]   ; R a0+0x150  (address of the slot)
        // 0x8f2221  mov r14,[rsi+0x158]   ; R a0+0x158  (end)
        // 0x8f2228  cmp rdi,r14
        // 0x8f222b  je short 0x8F2244
        // 0x8f222d  nop [rax]
        // loc_8f2230:
        // 0x8f2230  mov rcx,rdi
        // 0x8f2233  call 0x8F22E0
        // 0x8f2238  add rdi,8
        // 0x8f223c  cmp rdi,r14
        // 0x8f223f  jne short 0x8F2230
        // 0x8f2241  mov rdi,[rbx]         ; R a0+0x150+0x0  (reload start)
        void** rbx = &ctx->buffer_start;   // 0x8f221a  lea rbx,[rsi+0x150]
        void* r14 = ctx->buffer_end;       // 0x8f2221  mov r14,[rsi+0x158]
        if (rdi != r14) {                  // 0x8f2228  cmp rdi,r14 ; 0x8f222b  je short 0x8F2244 ; 0x8f222d  nop [rax]
            do {
                sub_8f22e0(rdi);           // 0x8f2230  mov rcx,rdi ; 0x8f2233  call 0x8F22E0
                rdi = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rdi) + 8);  // 0x8f2238  add rdi,8
            } while (rdi != r14);          // 0x8f223c  cmp rdi,r14 ; 0x8f223f  jne short 0x8F2230
        }
        rdi = *rbx;                        // 0x8f2241  mov rdi,[rbx]

        // loc_8f2244:
        // 0x8f2244  mov rdx,[rsi+0x160]   ; R a0+0x160
        // 0x8f224b  sub rdx,rdi
        // 0x8f224e  cmp rdx,0x1000
        // 0x8f2255  jb short 0x8F226F
        std::uintptr_t rdx = reinterpret_cast<std::uintptr_t>(ctx->buffer_end2) - reinterpret_cast<std::uintptr_t>(rdi);  // 0x8f2244  mov rdx,[rsi+0x160] ; 0x8f224b  sub rdx,rdi
        if (rdx >= 0x1000) {               // 0x8f224e  cmp rdx,0x1000 ; 0x8f2255  jb short 0x8F226F
            // 0x8f2257  mov rax,[rdi-8]   ; R *(a0+0x150+0x0)-0x8
            // 0x8f225b  add rdi,0xFFFFFFFFFFFFFFF8
            // 0x8f225f  sub rdi,rax
            // 0x8f2262  cmp rdi,0x20
            // 0x8f2266  jae short 0x8F2299
            std::uintptr_t rax = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uint8_t*>(rdi) - 8);  // 0x8f2257  mov rax,[rdi-8]
            std::uintptr_t rdi2 = reinterpret_cast<std::uintptr_t>(rdi) - 8;   // 0x8f225b  add rdi,0xFFFFFFFFFFFFFFF8
            rdi2 = rdi2 - rax;               // 0x8f225f  sub rdi,rax
            if (rdi2 >= 0x20) {              // 0x8f2262  cmp rdi,0x20 ; 0x8f2266  jae short 0x8F2299
                // loc_8f2299:  slow path, noreturn
                // 0x8f2299  mov qword ptr [rsp+0x20],0
                // 0x8f22a2  xor ecx,ecx
                // 0x8f22a4  xor edx,edx
                // 0x8f22a6  xor r8d,r8d
                // 0x8f22a9  xor r9d,r9d
                // 0x8f22ac  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
                // 0x8f22b2  int3
                auto fn = reinterpret_cast<void(*)(void*, void*, void*, void*)>(
                    *reinterpret_cast<void**>(0xF9A8C78ULL));
                fn(nullptr, nullptr, nullptr, nullptr);   // 0x8f22ac  call qword ptr [0xF9A8C78]
                __assume(false);                          // 0x8f22b2  int3  (noreturn)
            }
            // 0x8f2268  add rdx,0x27
            // 0x8f226c  mov rdi,rax
            rdx += 0x27;                              // 0x8f2268  add rdx,0x27
            rdi = reinterpret_cast<void*>(rax);       // 0x8f226c  mov rdi,rax
        }

        // loc_8f226f:
        // 0x8f226f  mov rcx,rdi
        // 0x8f2272  call 0xE935700     ; -> sub_e935700 (lift/set)
        // 0x8f2277  xorps xmm0,xmm0
        // 0x8f227a  movups [rbx],xmm0   ; W a0+0x150+0x0
        // 0x8f227d  mov qword ptr [rbx+0x10],0   ; W a0+0x150+0x10
        sub_e935700(rdi);                                  // 0x8f226f  mov rcx,rdi ; 0x8f2272  call 0xE935700
        std::uint64_t* slot = reinterpret_cast<std::uint64_t*>(rbx);
        slot[0] = 0;                                       // 0x8f2277  xorps xmm0,xmm0 ; 0x8f227a  movups [rbx],xmm0
        slot[1] = 0;                                       // (movups second qword)
        slot[2] = 0;                                       // 0x8f227d  mov qword ptr [rbx+0x10],0

    } // if (rdi != nullptr) -> falls through to loc_8f2285

    // loc_8f2285:
    // 0x8f2285  mov rcx,rsi
    // 0x8f2288  call 0x7727B0     ; -> sub_7727b0
    // 0x8f228d  nop
    // 0x8f228e  add rsp,0x70
    // 0x8f2292  pop rbx
    // 0x8f2293  pop rdi
    // 0x8f2294  pop rsi
    // 0x8f2295  pop r14
    // 0x8f2297  pop rbp
    // 0x8f2298  ret
    sub_7727b0(a0);   // 0x8f2285  mov rcx,rsi ; 0x8f2288  call 0x7727B0 ; 0x8f228d  nop ; epilogue 0x8f228e..0x8f2298
    return;
}

} // namespace native

LIFT_FN(sub_8f21d0, "sub_8f21d0", 0x8F21D0, native::sub_8f21d0, nullptr);

// Verbatim instructions of the function (rdis dis 0x8f21d0 0xe3), for
// liftcheck/verify_oc. Every line matches rdis output for its address.
#if 0
0x8f21d0  push rbp
0x8f21d1  push r14
0x8f21d3  push rsi
0x8f21d4  push rdi
0x8f21d5  push rbx
0x8f21d6  sub rsp,0x70
0x8f21da  lea rbp,[rsp+0x70]
0x8f21df  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
0x8f21e7  mov rsi,rcx
0x8f21ea  lea rax,[0xEFCA680]
0x8f21f1  mov [rbp-0x48],rax
0x8f21f5  lea rax,[0x873D0]
0x8f21fc  mov [rbp-0x40],rax
0x8f2200  lea rdx,[rbp-0x48]
0x8f2204  mov [rbp-0x10],rdx
0x8f2208  call 0x7705B0
0x8f220d  nop
0x8f220e  mov rdi,[rsi+0x150]
0x8f2215  test rdi,rdi
0x8f2218  je short 0x8F2285
0x8f221a  lea rbx,[rsi+0x150]
0x8f2221  mov r14,[rsi+0x158]
0x8f2228  cmp rdi,r14
0x8f222b  je short 0x8F2244
0x8f222d  nop [rax]
0x8f2230  mov rcx,rdi
0x8f2233  call 0x8F22E0
0x8f2238  add rdi,8
0x8f223c  cmp rdi,r14
0x8f223f  jne short 0x8F2230
0x8f2241  mov rdi,[rbx]
0x8f2244  mov rdx,[rsi+0x160]
0x8f224b  sub rdx,rdi
0x8f224e  cmp rdx,0x1000
0x8f2255  jb short 0x8F226F
0x8f2257  mov rax,[rdi-8]
0x8f225b  add rdi,0xFFFFFFFFFFFFFFF8
0x8f225f  sub rdi,rax
0x8f2262  cmp rdi,0x20
0x8f2266  jae short 0x8F2299
0x8f2268  add rdx,0x27
0x8f226c  mov rdi,rax
0x8f226f  mov rcx,rdi
0x8f2272  call 0xE935700
0x8f2277  xorps xmm0,xmm0
0x8f227a  movups [rbx],xmm0
0x8f227d  mov qword ptr [rbx+0x10],0
0x8f2285  mov rcx,rsi
0x8f2288  call 0x7727B0
0x8f228d  nop
0x8f228e  add rsp,0x70
0x8f2292  pop rbx
0x8f2293  pop rdi
0x8f2294  pop rsi
0x8f2295  pop r14
0x8f2297  pop rbp
0x8f2298  ret
0x8f2299  mov qword ptr [rsp+0x20],0
0x8f22a2  xor ecx,ecx
0x8f22a4  xor edx,edx
0x8f22a6  xor r8d,r8d
0x8f22a9  xor r9d,r9d
0x8f22ac  call qword ptr [0xF9A8C78]
0x8f22b2  int3
#endif
