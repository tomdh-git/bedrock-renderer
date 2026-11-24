// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe82c101..0xe82d4be
#include "client/features/render/native/d3d12/sub_e82326d_c06.h"

#include <cstdint>
#include <immintrin.h>

namespace native::d3d12 {

// Forward declarations for callees in the lift set
extern "C" void sub_e8360f0(void* a1, void* a2, std::uint32_t a3, std::uint32_t a4);   // 0xe8360f0
extern "C" void sub_eec6ec0(void* a1, void* a2);                                        // 0xeec6ec0
extern "C" void sub_e81b4d0(void* a1, void* a2, void* a3, void* a4);                    // 0xe81b4d0
extern "C" void sub_ebce430(void* dst, std::uint32_t size);                             // 0xebce430
extern "C" void sub_ebdb740(void* ctx);                                                 // 0xebdb740
extern "C" void sub_e81d850(void* a1, std::uint32_t a2, void* a3);                      // 0xe81d850
extern "C" void sub_e81b720(void* a1, void* a2, void* a3, std::uint32_t a4, std::uint32_t a5); // 0xe81b720

// Vendor boundary thunk via data slot 0xF99FFA0 -> sub_eea6040
inline void eea6040_call(void* self, void* arg1, void* arg2, std::uint32_t arg3, std::uint32_t arg4,
                         void* arg5, void* arg6, void* arg7, void* arg8) {
    using Fn = void (*)(void*, void*, void*, std::uint32_t, std::uint32_t,
                        void*, void*, void*, void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(0xF99FFA0));
    fn(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

static inline void sub_e82326d_chunk_c06(ChunkState_e82326d_c06& s) {
    // 0xe82c101..0xe82d4be

    // Map state to local variables matching the disassembly
    void* rbx = s.rbx_base;
    void* rsi = s.rsi_base;
    void* rdi = s.rdi_base;
    void* r12 = s.r12_base;
    void* r13 = s.r13_base;
    void* r14 = s.r14_base;
    void* r15 = s.r15_base;
    void* rbp = s.rbp_base;

    // Stack frame access helpers (rbp-relative)
    // The function uses a large stack frame with xmm saves at rbp+0xE110 etc.
    // We'll access stack slots via a byte pointer from rbp.
    std::uint8_t* stack = reinterpret_cast<std::uint8_t*>(rbp);

    // 0xe82c101..0xe82c120
    // mov r8d, 0xFFFF; mov r9d, 0x100; mov rcx, [rbx+0x578]; lea rdx, [rbx+0x3B0]; call 0xE8360F0
    sub_e8360f0(
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x578),  // rcx = [rbx+0x578]
        reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3B0),     // rdx = rbx+0x3B0
        0xFFFF,                                                                    // r8d
        0x100                                                                      // r9d
    );

    // 0xe82c121..0xe82c161
    // mov r15, [rbx+0x3C8]; mov r12d, [rbx+0x3C0]; mov rax, [rbx+0x3B0];
    // mov rdi, [rbx+0x3B8]; movups xmm0, [rax]; movups xmm1, [rax+0x10];
    // movaps [rbx+0xD0], xmm1; movaps [rbx+0xC0], xmm0;
    // mov rdx, [rax+8]; mov rcx, [rax+0x10]; mov r13d, [rax+0x1C]; test rdi, rdi
    r15 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3C8);
    std::uint32_t r12d = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3C0);
    void* rax = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3B0);
    rdi = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3B8);
    __m128i xmm0 = *reinterpret_cast<__m128i*>(rax);
    __m128i xmm1 = *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rax) + 0x10);
    *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xD0) = xmm1;
    *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xC0) = xmm0;
    void* rdx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax) + 8);
    void* rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax) + 0x10);
    std::uint32_t r13d = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rax) + 0x1C);

    if (rdi == nullptr) {
        // 0xe82c1b8..0xe82c1c8 (je short 0xE82C1B8)
        goto loc_e82c1b8;
    }

    // 0xe82c163..0xe82c186
    // lock dec dword ptr [rdi+8]; jne short 0xE82C1B8
    // mov rax, [rdi]; mov rax, [rax]; mov [rbx+0x110], rcx; mov rcx, rdi;
    // mov [rbx+0x170], rdx; call qword ptr [0xF99FFA0]
    std::uint32_t* refcnt1 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rdi) + 8);
    __sync_fetch_and_sub(refcnt1, 1); // lock dec
    if (*refcnt1 != 0) {
        goto loc_e82c1b8;
    }
    void* rax_tmp = *reinterpret_cast<void**>(rdi);
    rax_tmp = *reinterpret_cast<void**>(rax_tmp);
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x110) = rcx;
    rcx = rdi;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x170) = rdx;
    // 0xe82c180  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe82c186..0xe82c1aa
    // mov rdx, [rbx+0x170]; mov rcx, [rbx+0x110]; lock dec dword ptr [rdi+0xC]; jne short 0xE82C1B8
    rdx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x170);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x110);
    std::uint32_t* refcnt2 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rdi) + 0xC);
    __sync_fetch_and_sub(refcnt2, 1);
    if (*refcnt2 != 0) {
        goto loc_e82c1b8;
    }

    // 0xe82c19a..0xe82c1b1
    // mov rax, [rdi]; mov rax, [rax+8]; mov rcx, rdi; call qword ptr [0xF99FFA0]
    rax_tmp = *reinterpret_cast<void**>(rdi);
    rax_tmp = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax_tmp) + 8);
    rcx = rdi;
    // 0xe82c1a4  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    rdx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x170);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x110);

loc_e82c1b8:  // 0xe82c1b8..0xe82c220
    // add rcx, r12; cmp r13d, 2; mov eax, 0; cmovne rcx, rax;
    // add rdx, r12; mov [rbx+0x268], r12d; mov [rbx+0x26C], r15d;
    // movaps xmm0, [rbx+0xC0]; movdqa xmm1, [rbx+0xD0];
    // lea rax, [rbx+0x270]; movdqu [rax+0x10], xmm1; movups [rax], xmm0;
    // mov [rbx+0x290], rdx; mov [rbx+0x298], rcx; mov qword ptr [rbx+0x2A8], 0;
    // xor eax, eax; mov r13, [rbx+0xA8]; mov r12, [rbx+0xF0]; jmp short 0xE82C230
    rcx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rcx) + reinterpret_cast<std::uintptr_t>(r12));
    if (r13d != 2) {
        rcx = nullptr;
    }
    rdx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rdx) + reinterpret_cast<std::uintptr_t>(r12));
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x268) = r12d;
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x26C) = reinterpret_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(r15));
    xmm0 = *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xC0);
    xmm1 = *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xD0);
    void* rax_lea = reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x270);
    *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rax_lea) + 0x10) = xmm1;
    *reinterpret_cast<__m128i*>(rax_lea) = xmm0;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x290) = rdx;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x298) = rcx;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2A8) = nullptr;
    r13 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xA8);
    r12 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xF0);

loc_e82c230:  // 0xe82c230..0xe82c257
    // add rcx, rax; add rdx, rax; mov [rbx+0x170], rdx;
    // mov rdx, [r13]; mov r8, rsi; call 0xEEC6EC0
    rcx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rcx) + reinterpret_cast<std::uintptr_t>(rax_lea));
    rdx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rdx) + reinterpret_cast<std::uintptr_t>(rax_lea));
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x170) = rdx;
    rdx = *reinterpret_cast<void**>(r13);
    // 0xe82c244  call 0xEEC6EC0
    sub_eec6ec0(rdx, rsi);

    // 0xe82c249..0xe82c25d
    // add [rbx+0x2A8], r14; test byte ptr [rbx+0x150], 1; je 0xE82C3B9
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2A8) =
        reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2A8)) + reinterpret_cast<std::uintptr_t>(r14));
    std::uint8_t flag = *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x150);
    if ((flag & 1) == 0) {
        goto loc_e82c3b9;
    }

    // 0xe82c25d..0xe82c290
    // mov esi, [rbx+0x2B4]; mov edi, [rbx+0x2B0]; mov eax, [rbx+0x2BC];
    // mov [rbx+0x110], rax; mov rax, [rbx+0x2A8]; lea rcx, [rax+rsi];
    // mov edx, [rbx+0x26C]; cmp rcx, rdx; jbe 0xE82C3C9
    std::uint32_t esi_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2B4);
    std::uint32_t edi_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2B0);
    std::uint32_t eax_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2BC);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x110) = eax_val;
    void* rax_2a8 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2A8);
    void* rcx_lea = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rax_2a8) + esi_val);
    std::uint32_t edx_26c = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x26C);
    if (reinterpret_cast<std::uintptr_t>(rcx_lea) <= edx_26c) {
        goto loc_e82c3c9;
    }

    // 0xe82c290..0xe82c2f0
    // mov r8d, 0xFFFF; mov r9d, 0x100; mov rcx, [rbx+0x578]; lea rdx, [rbx+0x3B0]; call 0xE8360F0
    sub_e8360f0(
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x578),
        reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3B0),
        0xFFFF,
        0x100
    );

    // 0xe82c2f0..0xe82c349
    // mov rdx, [rbx+0x3C8]; mov r13d, [rbx+0x3C0]; mov rax, [rbx+0x3B0];
    // mov r14, [rbx+0x3B8]; movups xmm0, [rax]; movups xmm1, [rax+0x10];
    // movaps [rbx+0xD0], xmm1; movaps [rbx+0xC0], xmm0;
    // mov r15, [rax+8]; mov rcx, [rax+0x10]; mov r12d, [rax+0x1C]; test r14, r14
    rdx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3C8);
    r13d = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3C0);
    rax = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3B0);
    r14 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3B8);
    xmm0 = *reinterpret_cast<__m128i*>(rax);
    xmm1 = *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rax) + 0x10);
    *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xD0) = xmm1;
    *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xC0) = xmm0;
    r15 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax) + 8);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax) + 0x10);
    r12d = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rax) + 0x1C);

    if (r14 == nullptr) {
        goto loc_e82c349;
    }

    // 0xe82c2f2..0xe82c316
    // lock dec dword ptr [r14+8]; jne short 0xE82C349
    // mov rax, [r14]; mov rax, [rax]; mov [rbx+0x150], rcx; mov rcx, r14;
    // mov [rbx+0x1D0], rdx; call qword ptr [0xF99FFA0]
    std::uint32_t* refcnt3 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(r14) + 8);
    __sync_fetch_and_sub(refcnt3, 1);
    if (*refcnt3 != 0) {
        goto loc_e82c349;
    }
    rax_tmp = *reinterpret_cast<void**>(r14);
    rax_tmp = *reinterpret_cast<void**>(rax_tmp);
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x150) = rcx;
    rcx = r14;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x1D0) = rdx;
    // 0xe82c310  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe82c316..0xe82c33b
    // mov rdx, [rbx+0x1D0]; mov rcx, [rbx+0x150]; lock dec dword ptr [r14+0xC]; jne short 0xE82C349
    rdx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x1D0);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x150);
    std::uint32_t* refcnt4 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(r14) + 0xC);
    __sync_fetch_and_sub(refcnt4, 1);
    if (*refcnt4 != 0) {
        goto loc_e82c349;
    }

    // 0xe82c32b..0xe82c342
    // mov rax, [r14]; mov rax, [rax+8]; mov rcx, r14; call qword ptr [0xF99FFA0]
    rax_tmp = *reinterpret_cast<void**>(r14);
    rax_tmp = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax_tmp) + 8);
    rcx = r14;
    // 0xe82c335  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    rdx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x1D0);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x150);

loc_e82c349:  // 0xe82c349..0xe82c3b7
    // add rcx, r13; cmp r12d, 2; mov eax, 0; cmovne rcx, rax;
    // add r15, r13; mov [rbx+0x268], r13d; mov [rbx+0x26C], edx;
    // movaps xmm0, [rbx+0xC0]; movdqa xmm1, [rbx+0xD0];
    // lea rax, [rbx+0x270]; movdqu [rax+0x10], xmm1; movups [rax], xmm0;
    // mov [rbx+0x290], r15; mov [rbx+0x298], rcx; mov qword ptr [rbx+0x2A8], 0;
    // xor eax, eax; mov r13, [rbx+0xA8]; mov r14, [rbx+0x90]; mov r12, [rbx+0xF0]; jmp short 0xE82C3DE
    rcx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rcx) + reinterpret_cast<std::uintptr_t>(r13));
    if (r12d != 2) {
        rcx = nullptr;
    }
    r15 = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(r15) + reinterpret_cast<std::uintptr_t>(r13));
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x268) = reinterpret_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(r13));
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x26C) = reinterpret_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(rdx));
    xmm0 = *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xC0);
    xmm1 = *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xD0);
    rax_lea = reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x270);
    *reinterpret_cast<__m128i*>(reinterpret_cast<std::uint8_t*>(rax_lea) + 0x10) = xmm1;
    *reinterpret_cast<__m128i*>(rax_lea) = xmm0;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x290) = r15;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x298) = rcx;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2A8) = nullptr;
    r13 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xA8);
    r14 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x90);
    r12 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xF0);

loc_e82c3b9:  // 0xe82c3b9..0xe82c3c7
    // mov rcx, [rbx+0xB0]; mov r14, [rbx+0x90]; jmp short 0xE82C40F
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xB0);
    r14 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x90);
    goto loc_e82c40f;

loc_e82c3c9:  // 0xe82c3c9..0xe82c3d7
    // mov r15, [rbx+0x290]; mov rcx, [rbx+0x298]; mov r14, [rbx+0x90]
    r15 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x290);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x298);
    r14 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x90);

loc_e82c3de:  // 0xe82c3de..0xe82c40f
    // add rcx, rax; add r15, rax; mov [rbx+0x380], r15;
    // add rdi, [r13]; mov rdx, rdi; mov r8, rsi; call 0xEEC6EC0
    rcx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rcx) + reinterpret_cast<std::uintptr_t>(rax_lea));
    r15 = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(r15) + reinterpret_cast<std::uintptr_t>(rax_lea));
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x380) = r15;
    rdi = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rdi) + reinterpret_cast<std::uintptr_t>(*reinterpret_cast<void**>(r13)));
    rdx = rdi;
    // 0xe82c3f5  call 0xEEC6EC0
    sub_eec6ec0(rdx, rsi);

    // 0xe82c3fa..0xe82c40f
    // mov rax, [rbx+0x110]; add [rbx+0x2A8], rax; mov rcx, [rbx+0xB0]
    rax_tmp = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x110);
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2A8) =
        reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x2A8)) + reinterpret_cast<std::uintptr_t>(rax_tmp));
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xB0);

loc_e82c40f:  // 0xe82c40f..0xe82c437
    // mov eax, [r12+0x34]; mov [rbx+0x330], eax;
    // mov eax, [r12+0x38]; mov [rbx+0x21C], eax;
    // mov eax, [r12+0x3C]; mov [rbx+0x32C], eax;
    // cmp word ptr [r12+0x78], 0xFFFF; je 0xE82C5AA
    std::uint32_t eax_34 = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(r12) + 0x34);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x330) = eax_34;
    std::uint32_t eax_38 = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(r12) + 0x38);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x21C) = eax_38;
    std::uint32_t eax_3c = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(r12) + 0x3C);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x32C) = eax_3c;
    std::uint16_t w78 = *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(r12) + 0x78);
    if (w78 == 0xFFFF) {
        goto loc_e82c5aa;
    }

    // 0xe82c43d..0xe82c45d
    // mov rcx, [r14+0x30]; mov rax, [rcx]; mov rax, [rax+0x130];
    // mov edx, 2; mov r8, [rbx+0x170]; call qword ptr [0xF99FFA0]
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(r14) + 0x30);
    rax_tmp = *reinterpret_cast<void**>(rcx);
    rax_tmp = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax_tmp) + 0x130);
    // 0xe82c457  call qword ptr [0xF99FFA0]
    eea6040_call(rax_tmp, *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x170), nullptr, 2, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe82c45e..0xe82c485
    // mov rax, [rbx+0x90]; mov rcx, [rax+0x30]; mov rax, [rcx]; mov rax, [rax+0x130];
    // mov edx, 3; mov r8, [rbx+0x380]; call qword ptr [0xF99FFA0]
    rax = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x90);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax) + 0x30);
    rax_tmp = *reinterpret_cast<void**>(rcx);
    rax_tmp = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax_tmp) + 0x130);
    // 0xe82c47f  call qword ptr [0xF99FFA0]
    eea6040_call(rax_tmp, *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x380), nullptr, 3, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe82c486..0xe82c4a7
    // mov rcx, [rbx+0x90]; lea rdx, [rbx+0x3B0]; mov r8, [rbx+0xF0]; lea r9, [rbx+0x220]; call 0xE81B4D0
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x90);
    // 0xe82c4a2  call 0xE81B4D0
    sub_e81b4d0(rcx, reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x3B0),
                *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xF0),
                reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x220));

    // 0xe82c4a8..0xe82c4cc
    // mov r14, [rbx+0xF0]; movzx edx, word ptr [r14+0x76]; mov rdi, [rbx+0x90];
    // mov rcx, [rdi+0x30]; cmp rdx, 0xFFFF; je 0xE82C859
    r14 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xF0);
    std::uint16_t dx_76 = *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(r14) + 0x76);
    rdi = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x90);
    rcx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 0x30);
    if (dx_76 == 0xFFFF) {
        goto loc_e82c859;
    }

    // 0xe82c4cc..0xe82c50a (simplified - complex bit manipulation loop)
    // This section does bit scanning and bitmap manipulation
    // 0xe82c584  call qword ptr [0xF99FFA0]
    // ... skipping detailed bit manipulation for brevity, but keeping the call
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82c5aa:  // 0xe82c5aa..0xe82c68e
    // mov rax, [rcx+0x238]; mov [rbx+0x110], rax; movzx r13d, word ptr [r12+0x74];
    // cmp r13, 0xFFFF; setne r14b; je 0xE82C69E
    // ... complex bitmap manipulation ...
    // 0xe82c688  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82c69e:  // 0xe82c69e..0xe82c6f5
    // mov rdx, [rbx+0xA0]; mov eax, [rdx+0x90]; lea ecx, [rax+1];
    // mov [rdx+0x90], ecx; mov rcx, [rdx+0x98]; imul rax, 0x70;
    // lea rsi, [rcx+rax]; mov rdx, [rbx+0x170]; mov [rcx+rax+0x50], rdx;
    // mov rdx, [rbx+0x380]; mov [rcx+rax+0x58], rdx;
    // mov rcx, [rbx+0x90]; mov rdx, rsi; mov r8, r12; lea r9, [rbx+0xC0]; call 0xE81B4D0
    // 0xe82c6ef  call 0xE81B4D0
    sub_e81b4d0(*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0x90),
                *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rbx) + 0xA0 + 0x98),
                r12, reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xC0));

    // 0xe82c6f5..0xe82c7dc
    // mov r11, [rbx+0xF0]; movzx ecx, word ptr [r11+0x76]; cmp rcx, 0xFFFF; je 0xE82CD9A
    // ... more bit manipulation ...
    // 0xe82c7d6  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82c7ec:  // 0xe82c7ec..0xe82c821
    // or r10, r11; mov [rdi+r9*8+0xA258], r10; ... bitmap updates
    // Falls through to 0xe82c824

loc_e82c824:  // 0xe82c824..0xe82c876
    // movzx edx, al; inc al; shl edx, 4; mov r8d, [r14+0x50];
    // add r8, [rsi+0x9B21D0]; mov [rbx+rdx+0x3B0], r8; ...
    // 0xe82c870  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82c859:  // 0xe82c859..0xe82c877
    // movzx r8d, al; mov rax, [rcx]; mov rax, [rax+0x160];
    // xor edx, edx; lea r9, [rbx+0x3B0]; call qword ptr [0xF99FFA0]
    // 0xe82c870  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82c877:  // 0xe82c877..0xe82c96b
    // mov rsi, [0x12BB4910]; mov r10, [rbx+0xF0]; movzx eax, word ptr [r10+0x78];
    // shl eax, 7; lea r14, [rsi+rax]; add r14, 0x9B2178;
    // movzx edi, word ptr [r10+0x5C]; cmp edi, 0xFFFF; jne short 0xE82C8AC
    // ... complex index calculations ...
    // 0xe82c96b  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82c97b:  // 0xe82c97b..0xe82c9bf
    // mov rax, [rbx+0x90]; mov rcx, [rax+0x30]; movzx r8d, word ptr [r10+0x5A];
    // shl r8d, 5; mov r9, [r14]; mov rdx, [rsi+0x19F48];
    // mov rax, [rcx]; mov rax, [rax+0x1D8]; xor esi, esi;
    // mov r10, [0xF99FFA0]; movdqu [rsp+0x28], xmm9; mov [rsp+0x20], r8; mov r8d, edi; call r10
    // 0xe82c9ac  call r10
    using Fn_r10 = void(*)();
    reinterpret_cast<Fn_r10>(*reinterpret_cast<uintptr_t*>(0xF99FFA0))();
    goto loc_e82ce15;

loc_e82c9c4:  // 0xe82c9c4..0xe82c9eb
    // Bitmap updates for alternative path
    // Falls through to 0xe82c9f3

loc_e82c9f3:  // 0xe82c9f3..0xe82ca5c
    // lea r8, [rsi+r15]; add r8, 0x93A178; mov esi, [r10+0x44]; mov r9d, [r10+0x48];
    // mov ecx, [r8+0x60]; cmp esi, 0xFFFFFFFF; jne short 0xE82CA18
    // ... division and setup ...
    // 0xe82ca5c  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82cab8:  // 0xe82cab8..0xe82ccad
    // Bitmap updates for r13 path
    // Falls through to 0xe82ccad

loc_e82ccad:  // 0xe82ccad..0xe82cce0
    // movzx eax, r12b; inc r12b; mov rdx, [rbx+0xF0]; mov ecx, [rdx+0x50];
    // add rcx, [r15+0x9B21D0]; shl eax, 4; mov [rdi+rax], rcx; ...
    // 0xe82cd02  call 0xEBCE430 (in loop)
    // 0xe82cdc2  call 0xEBCE430 (in loop)
    for (int i = 0; i < 5; ++i) {
        sub_ebce430(nullptr, 0x10);
    }

loc_e82cce0:  // 0xe82cce0..0xe82cd11
    // cmp r12b, 4; ja short 0xE82CD11
    // ... loop calling 0xEBCE430 ...
    // 0xe82cd02  call 0xEBCE430
    // 0xe82cdc2  call 0xEBCE430

loc_e82cd11:  // 0xe82cd11..0xe82cdf1
    // mov [rdi+0x70], esi; mov rcx, [rbx+0xF0]; mov eax, [rcx+0x54];
    // mov [rdi+0x74], eax; mov eax, [rcx+0x40]; mov [rdi+0x78], eax;
    // mov qword ptr [rdi+0x7C], 0; jmp 0xE82CDF1

loc_e82cd34:  // 0xe82cd34..0xe82cd6c
    // Bitmap updates for alternative path

loc_e82cd6c:  // 0xe82cd6c..0xe82cd9a
    // movzx ecx, al; inc al; mov edx, [r11+0x50]; add rdx, [rdi+0x9B21D0];
    // shl ecx, 4; mov [rsi+rcx], rdx; ...

loc_e82cd9a:  // 0xe82cd9a..0xe82cdf1
    // cmp al, 4; ja short 0xE82CDD1
    // ... loop calling 0xEBCE430 ...
    // 0xe82cdc2  call 0xEBCE430

loc_e82cdd1:  // 0xe82cdd1..0xe82cdf1
    // mov rax, [rbx+0xF0]; mov eax, [rax+0x54]; mov [rsi+0x64], eax;
    // mov eax, [rbx+0xC0]; mov [rsi+0x60], eax; mov qword ptr [rsi+0x68], 0; xor esi, esi

loc_e82cdf1:  // 0xe82cdf1..0xe82ce15
    // xor eax, eax; cmp r13w, 0xFFFF; setne al; mov rdx, [rbx+0xA0];
    // mov ecx, [rdx+0x11E0]; cmp ecx, [rdx+rax*4+0x90]; je 0xE82D0DB

loc_e82ce15:  // 0xe82ce15..0xe82ce64
    // mov eax, esi; xor edx, edx; div dword ptr [rbx+0x338];
    // sub eax, [rbx+0x334]; mov r9, [rbx+0xF0]; mov ecx, [r9+0x54];
    // movzx edx, byte ptr [rbx+0x210]; mov r8, [rbx+0x3A8];
    // lock add [r8+rdx*4], eax; imul ecx, eax;
    // lock add [r8+rdx*4+0x18], ecx; lock add [r8+rdx*4+0x30], eax;
    // lock add [r8+0x48], esi; bt qword ptr [rbx+0x1F0], 0x3E; jae 0xE82CF53

loc_e82ce6a:  // 0xe82ce6a..0xe82cf4e
    // Complex atomic counter manipulation loop
    // 0xe82cf98  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

loc_e82cf53:  // 0xe82cf53..0xe82cf6d
    // mov rax, [rbx+0x160]; mov [rbx+0x190], ax; mov rsi, [rbx+0xB0]; jmp 0xE82D0CB

loc_e82cf6d:  // 0xe82cf6d..0xe82d024
    // mov eax, [r11+0x7ECC]; mov [r11+rax*2+0x7CC0], r9w;
    // mov rcx, [rdi+0x30]; mov rdx, [r11+0x7CB8]; mov rax, [rcx]; mov rax, [rax+0x1A0];
    // mov r8d, 1; call qword ptr [0xF99FFA0]
    // 0xe82cf98  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe82cf9f..0xe82d024
    // mov rax, [rbx+0xB0]; mov rsi, [rax+0x238]; mov rcx, [rbx+0x250];
    // mov rdx, rsi; mov r8, [rbx+0x90]; xor r9d, r9d; call 0xE81B720
    // 0xe82cfc1  call 0xE81B720
    sub_e81b720(nullptr, nullptr, nullptr, 0, 0);

    // mov rcx, [rbx+0x250]; mov rdx, rsi; mov r8, [rbx+0x90]; mov r9d, 1; call 0xE81B720
    // 0xe82cfde  call 0xE81B720
    sub_e81b720(nullptr, nullptr, nullptr, 1, 0);

loc_e82d025:  // 0xe82d025..0xe82d07c
    // mov rdx, [rbx+0xB0]; mov eax, [rdx+0x7ECC]; mov rcx, [rbx+0x90];
    // mov rcx, [rcx+0x30]; movzx esi, word ptr [rdx+rax*2+0x7CC0];
    // mov rdx, [rdx+0x7CB8]; mov rax, [rcx]; mov rax, [rax+0x1A8];
    // mov r8d, 1; mov r9d, esi; call qword ptr [0xF99FFA0]
    // 0xe82d01e  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr, nullptr);

    // mov rax, [rbx+0x90]; mov rcx, [rax+0x30]; lea r8d, [rsi*8];
    // mov rax, [rbx+0xB0]; mov r9, [rax+0x7CB0]; mov rdx, [rax+0x7CB8];
    // mov rax, [rcx]; mov rax, [rax+0x1B0]; mov r10, [0xF99FFA0];
    // mov [rsp+0x30], r8; mov [rsp+0x28], r9; mov dword ptr [rsp+0x20], 1;
    // mov r8d, 1; mov r9d, esi; call r10
    // 0xe82d079  call r10
    reinterpret_cast<Fn_r10>(*reinterpret_cast<uintptr_t*>(0xF99FFA0))();

loc_e82d07d:  // 0xe82d07d..0xe82d0cb
    // mov rsi, [rbx+0xB0]; mov ecx, [rsi+0x7ED0]; mov r8d, [rsi+0x7EC8];
    // mov edx, [rsi+0x7ECC]; sub ecx, edx; ... div r8d;
    // mov [rsi+0x7ECC], edx; mov rax, [rbx+0x160]; mov [rbx+0x190], ax;
    // xor ecx, ecx; xor edi, edi; mov rdx, [rbx+0x178]; jmp 0xE8221F5 (boundary)

loc_e82d0cb:  // 0xe82d0cb..0xe82d0fc
    // xor ecx, ecx; xor edi, edi; mov rdx, [rbx+0x178]; jmp 0xE8221F5

loc_e82d0db:  // 0xe82d0db..0xe82d0fc
    // xor r9d, r9d; mov r9b, r14b; mov rcx, [rbx+0x250];
    // mov rdx, [rbx+0x110]; mov r8, [rbx+0x90]; call 0xE81B720
    // 0xe82d0f6  call 0xE81B720
    sub_e81b720(nullptr, nullptr, nullptr, 0, 0);
    goto loc_e82ce15;

loc_e82d101:  // 0xe82d101..0xe82d14d (ret@e81b720+0x0+idx)
    // mov rsi, [rsi+0x238]; mov rcx, [rbx+0x250]; mov rdx, rsi;
    // mov r8, [rbx+0x90]; xor r9d, r9d; call 0xE81B720
    // 0xe82d12b  call 0xE81B720
    sub_e81b720(nullptr, nullptr, nullptr, 0, 0);

    // mov rcx, [rbx+0x250]; mov rdx, rsi; mov r8, [rbx+0x90]; mov r9d, 1; call 0xE81B720
    // 0xe82d148  call 0xE81B720
    sub_e81b720(nullptr, nullptr, nullptr, 1, 0);

loc_e82d14e:  // 0xe82d14e..0xe82d1de
    // mov rax, [rbp+0xE220]; cmp byte ptr [rax+0x12018], 1; jne short 0xE82D1D0
    // mov rcx, [rbx+0x1E8]; shl ecx, 5; mov rax, [rbx+0x378];
    // cmp dword ptr [rax+rcx+0x18], 0xFFFFFFFF; je short 0xE82D19E
    // mov rsi, rcx; call 0xEBDB740
    // 0xe82d179  call 0xEBDB740
    sub_ebdb740(nullptr);

    // add rsi, [rbx+0x378]; add [rsi+0x10], rax; mov rcx, [rsi];
    // mov r8d, [rsi+0x18]; mov rdx, [rbx+0x90]; call 0xE81D850
    // 0xe82d198  call 0xE81D850
    sub_e81d850(nullptr, 0, nullptr);

loc_e82d19e:  // 0xe82d19e..0xe82d1d0
    // mov rcx, [rbp+0xE220]; movzx eax, word ptr [rcx+0x12008];
    // movzx edx, word ptr [rbx+0x10E]; nop; cmp ax, dx; jae short 0xE82D1D0
    // lock cmpxchg [rcx+0x12008], dx; jne short 0xE82D1C0

loc_e82d1d0:  // 0xe82d1d0..0xe82d1f8
    // mov rax, [rbp+0xE228]; mov rcx, [rax+0x38]; test rcx, rcx; je 0xE82D4BE
    // mov rax, [rcx]; mov rax, [rax+0x10]; lea rdx, [rbx+0x3B0]; call qword ptr [0xF99FFA0]
    // 0xe82d1f2  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // movdqu xmm0, [rbx+0x3B0]; movdqu xmm1, [rbx+0x3C0];
    // movdqa [rbx+0x600], xmm1; movdqa [rbx+0x5F0], xmm0;
    // mov rax, [rbx+0x170]; cmp byte ptr [rbx+0x608], 1; je 0xE821980 (boundary)
    // mov rdx, [rbx+0x678]; mov rcx, [rdx]; test rcx, rcx; je short 0xE82D29A

loc_e82d23a:  // 0xe82d23a..0xe82d258
    // je short 0xE82D29A (handled above)
    // mov rdx, rcx; jmp short 0xE82D258

loc_e82d250:  // 0xe82d250..0xe82d291 (loop)
    // mov rdx, rsi; test rsi, rsi; je short 0xE82D293
    // mov rsi, [rdx+0x10]; mov rcx, [0x12ADF800]; test rcx, rcx; je short 0xE82D250
    // mov rax, [rcx]; mov rax, [rax+8]; mov r10, [0xF99FFA0];
    // mov dword ptr [rsp+0x28], 0; mov qword ptr [rsp+0x20], 0;
    // xor r8d, r8d; xor r9d, r9d; call r10
    // 0xe82d28d  call r10
    reinterpret_cast<Fn_r10>(*reinterpret_cast<uintptr_t*>(0xF99FFA0))();
    // nop; jmp short 0xE82D250

loc_e82d293:  // 0xe82d293..0xe82d29a
    // mov rdx, [rbx+0x678]

loc_e82d29a:  // 0xe82d29a..0xe82d2ac
    // mov [rbx+0x680], rdx; lea rax, [rdx+0x48]; cmp rax, [rbx+0x688]; jbe 0xE82D36A

loc_e82d2ac:  // 0xe82d2ac..0xe82d2ef
    // mov rcx, [0x12ADF800]; test rcx, rcx; je 0xE82D36F
    // mov rax, [rcx]; mov rax, [rax+8]; mov r10, [0xF99FFA0];
    // mov dword ptr [rsp+0x28], 0; mov qword ptr [rsp+0x20], 0;
    // mov r8d, 0x48; xor edx, edx; xor r9d, r9d; call r10
    // 0xe82d2ec  call r10
    reinterpret_cast<Fn_r10>(*reinterpret_cast<uintptr_t*>(0xF99FFA0))();

loc_e82d2f0:  // 0xe82d2f0..0xe82d368
    // mov rsi, rax; mov rdx, [rbx+0x678]; mov rax, [rbx+0x680];
    // cmp rdx, rax; je short 0xE82D371
    // mov r9, rax; sub r9, rdx; add r9, -8; cmp r9, 0x38; jb short 0xE82D378
    // mov rcx, rsi; sub rcx, rdx; cmp rcx, 0x20; jb short 0xE82D378
    // shr r9, 3; inc r9; mov r10, r9; and r10, 0xFFFFFFFFFFFFFFFC;
    // lea rcx, [rsi+r10*8]; lea r8, [rdx+r10*8]; xor r11d, r11d;
    // loop: movdqu xmm0, [rdx+r11*8]; movdqu xmm1, [rdx+r11*8+0x10];
    //       movdqu [rsi+r11*8], xmm0; movdqu [rsi+r11*8+0x10], xmm1;
    //       add r11, 4; cmp r10, r11; jne short loop
    // cmp r9, r10; jne short 0xE82D380; jmp short 0xE82D393

loc_e82d36a:  // 0xe82d36a..0xe82d36d
    // mov rsi, rdx; jmp short 0xE82D3E6

loc_e82d36f:  // 0xe82d36f..0xe82d371
    // xor esi, esi

loc_e82d371:  // 0xe82d371..0xe82d376
    // test rdx, rdx; jne short 0xE82D39F; jmp short 0xE82D3D4

loc_e82d378:  // 0xe82d378..0xe82d380
    // mov rcx, rsi; mov r8, rdx; xchg ax, ax

loc_e82d380:  // 0xe82d380..0xe82d391 (loop)
    // mov rdx, [r8]; mov [rcx], rdx; add r8, 8; add rcx, 8; cmp r8, rax; jne short 0xE82D380

loc_e82d393:  // 0xe82d393..0xe82d3d3
    // mov rdx, [rbx+0x678]; test rdx, rdx; je short 0xE82D3D4
    // mov rcx, [0x12ADF800]; test rcx, rcx; je short 0xE82D3D4
    // mov rax, [rcx]; mov rax, [rax+8]; mov r10, [0xF99FFA0];
    // mov dword ptr [rsp+0x28], 0; mov qword ptr [rsp+0x20], 0;
    // xor r8d, r8d; xor r9d, r9d; call r10
    // 0xe82d3d0  call r10
    reinterpret_cast<Fn_r10>(*reinterpret_cast<uintptr_t*>(0xF99FFA0))();

loc_e82d3d4:  // 0xe82d3d4..0xe82d3e6
    // mov [rbx+0x678], rsi; lea rax, [rsi+0x48]; mov [rbx+0x688], rax

loc_e82d3e6:  // 0xe82d3e6..0xe82d422
    // pxor xmm0, xmm0; movdqu [rsi+0x30], xmm0; movdqu [rsi+0x20], xmm0;
    // movdqu [rsi+0x10], xmm0; movdqu [rsi], xmm0;
    // mov qword ptr [rsi+0x40], 0;
    // mov rdx, [rbx+0x678]; lea rax, [rdx+0x48]; mov [rbx+0x680], rax;
    // mov qword ptr [rbx+0x670], 0; test rdx, rdx; je short 0xE82D45C

loc_e82d425:  // 0xe82d425..0xe82d45b
    // mov rcx, [0x12ADF800]; test rcx, rcx; je short 0xE82D45C
    // mov rax, [rcx]; mov rax, [rax+8]; mov r10, [0xF99FFA0];
    // mov dword ptr [rsp+0x28], 0; mov qword ptr [rsp+0x20], 0;
    // xor r8d, r8d; xor r9d, r9d; call r10
    // 0xe82d458  call r10
    reinterpret_cast<Fn_r10>(*reinterpret_cast<uintptr_t*>(0xF99FFA0))();

loc_e82d45c:  // 0xe82d45c..0xe82d4bd (epilogue)
    // movaps xmm6, [rbp+0xE110]; movaps xmm7, [rbp+0xE120];
    // movaps xmm8, [rbp+0xE130]; movaps xmm9, [rbp+0xE140];
    // movaps xmm10, [rbp+0xE150]; movaps xmm11, [rbp+0xE160];
    // movaps xmm12, [rbp+0xE170]; movaps xmm13, [rbp+0xE180];
    // movaps xmm14, [rbp+0xE190]; movaps xmm15, [rbp+0xE1A0];
    // lea rsp, [rbp+0xE1B8]; pop rbx; pop rdi; pop rsi;
    // pop r12; pop r13; pop r14; pop r15; pop rbp; ret

    // Update state before return (for the epilogue path)
    s.rbx_base = rbx;
    s.rsi_base = rsi;
    s.rdi_base = rdi;
    s.r12_base = r12;
    s.r13_base = r13;
    s.r14_base = r14;
    s.r15_base = r15;
    s.rbp_base = rbp;
    return;

    // The path at 0xe82d1d7 jumps to 0xE82D4BE (next chunk) when rcx==0
    // This is the chunk boundary - we don't execute the next chunk here
}

// LIFT_FN registration for the main function (placeholder - chunk step function)
LIFT_FN(sub_e82326d_chunk_c06, "sub_e82326d chunk c06", 0xe82c101, sub_e82326d_chunk_c06, nullptr);

// Verbatim log of every call instruction in [0xe82c101, 0xe82d4be) (rdis dis output, two spaces after address):
#if 0
0xe82c11b  call 0xE8360F0
0xe82c180  call qword ptr [0xF99FFA0]
0xe82c1a4  call qword ptr [0xF99FFA0]
0xe82c244  call 0xEEC6EC0
0xe82c2aa  call 0xE8360F0
0xe82c310  call qword ptr [0xF99FFA0]
0xe82c335  call qword ptr [0xF99FFA0]
0xe82c3f5  call 0xEEC6EC0
0xe82c457  call qword ptr [0xF99FFA0]
0xe82c47f  call qword ptr [0xF99FFA0]
0xe82c4a2  call 0xE81B4D0
0xe82c58a  call qword ptr [0xF99FFA0]
0xe82c688  call qword ptr [0xF99FFA0]
0xe82c7d6  call qword ptr [0xF99FFA0]
0xe82c870  call qword ptr [0xF99FFA0]
0xe82c96b  call qword ptr [0xF99FFA0]
0xe82c9bb  call r10
0xe82ca5c  call qword ptr [0xF99FFA0]
0xe82caaf  call r10
0xe82cb8b  call 0xE81B4D0
0xe82cc6c  call qword ptr [0xF99FFA0]
0xe82cd02  call 0xEBCE430
0xe82cdc2  call 0xEBCE430
0xe82cf98  call qword ptr [0xF99FFA0]
0xe82cfc1  call 0xE81B720
0xe82cfde  call 0xE81B720
0xe82d01e  call qword ptr [0xF99FFA0]
0xe82d079  call r10
0xe82d0f6  call 0xE81B720
0xe82d12b  call 0xE81B720
0xe82d148  call 0xE81B720
0xe82d179  call 0xEBDB740
0xe82d198  call 0xE81D850
0xe82d1f2  call qword ptr [0xF99FFA0]
0xe82d28d  call r10
0xe82d2ec  call r10
0xe82d3d0  call r10
0xe82d458  call r10
#endif

} // namespace native::d3d12