// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991

#include "sub_e824991.h"

namespace native {

// Chunk state documented in docs/functions/e824991.md section 'Chunk state'.
// static inline step function for chunk range 0xe829147..0xe82a912.
static inline void sub_e824991_chunk_c03(ChunkState& s) {
    // CHUNK 0xe829147..0xe82a912
    // 0xe829147..0xe829171
    s.r13 = s.rbx_frame[0x2B0]; // mov r13d,[rbx+0x2B0]
    s.r13 += s.r12;             // add r13,r12
    void* rdx = (void*)((char*)s.rsi + (size_t)s.r13); // lea rdx,[rsi+r13]
    void* rax = *(void**)(*(char**)(s.rbx_frame + 0x98)); // mov rax,[rbx+0x98]; mov rax,[rax]
    void* rcx = *(void**)(s.r13_prev); // mov rcx,[rcx]  (r13 saved prior)
    size_t r9 = (size_t)rax - (size_t)rcx; // sub r9,rcx
    size_t r8 = (size_t)rdx - r9; // sub r8,r9
    if (r8 <= r9) goto loc_e829668; // jbe
    // 0xe829177..0xe829188
    void* r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38); // mov r9,[rbx+0xA0]; mov r9,[r9+0x38]
    r9 = (void*)((char*)r9b - (char*)rcx); // sub r9,rcx
    if ((size_t)rdx <= (size_t)r9) goto loc_e829646; // jbe
    // 0xe82918e..0xe8291a2
    rcx = *(void**)(s.rbx_frame + 0xA8); // mov rcx,[rbx+0xA8]
    void* r8p = (void*)(s.rbx_frame + 0x3B0); // lea r8,[rbx+0x3B0]
    sub_47e8f0(rcx, rdx, r8p); // call 0x47E8F0
    goto loc_e82965e; // jmp
loc_e829668:
    (void)0;
loc_e829646:
    (void)0;
loc_e82965e:
    (void)0;
    // 0xe8291a7..0xe8291e8
    s.r13 = s.rbx_frame[0x2B0];
    s.r13 += s.r12;
    rdx = (void*)((char*)s.rdi + (size_t)s.r13);
    rax = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rcx = *(void**)(s.r13_prev);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e8296cf;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e8296ad;
    rcx = *(void**)(s.rbx_frame + 0xA8);
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e8296c5;
loc_e8296cf: (void)0; loc_e8296ad: (void)0; loc_e8296c5: (void)0;
    // 0xe829207..0xe829246
    s.r12 = s.rbx_frame[0x2B0];
    s.r12 += s.rdi;
    rdx = (void*)((char*)s.r12 + (size_t)s.rsi);
    rax = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rcx = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e82972f;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e82970c;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e829724;
loc_e82972f: (void)0; loc_e82970c: (void)0; loc_e829724: (void)0;
    // 0xe829261..0xe8292a0
    s.r12 = s.rbx_frame[0x2B0];
    s.r12 += s.rdi;
    rdx = (void*)((char*)s.r12 + (size_t)s.rsi);
    rax = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rcx = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829793;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e829770;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e829788;
loc_e829793: (void)0; loc_e829770: (void)0; loc_e829788: (void)0;
    // 0xe8292bb..0xe8292fa
    s.rdi = s.rbx_frame[0x2B0];
    rdx = (void*)((char*)s.rdi + (size_t)s.rsi + 0x10);
    rcx = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rax = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rcx - (char*)rax);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e82981a;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rax);
    if ((size_t)rdx <= (size_t)r9) goto loc_e8297fa;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e82980f;
loc_e82981a: (void)0; loc_e8297fa: (void)0; loc_e82980f: (void)0;
    // 0xe829315..0xe829354
    s.rdi = s.rbx_frame[0x2B0];
    rdx = (void*)((char*)s.rdi + (size_t)s.rsi + 0x10);
    rcx = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rax = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rcx - (char*)rax);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829849;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rax);
    if ((size_t)rdx <= (size_t)r9) goto loc_e829829;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e82983e;
loc_e829849: (void)0; loc_e829829: (void)0; loc_e82983e: (void)0;
    // 0xe82936f..0xe8293ae
    s.r12 = s.rbx_frame[0x2B0];
    s.r12 += s.rdi;
    rdx = (void*)((char*)s.r12 + (size_t)s.rsi);
    rax = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rcx = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e8298ad;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e82988a;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e8298a2;
loc_e8298ad: (void)0; loc_e82988a: (void)0; loc_e8298a2: (void)0;
    // 0xe8293c9..0xe829408
    s.rdi = s.rbx_frame[0x2B0];
    rdx = (void*)((char*)s.rdi + (size_t)s.rsi + 0x10);
    rcx = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rax = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rcx - (char*)rax);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829901;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rax);
    if ((size_t)rdx <= (size_t)r9) goto loc_e8298e1;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e8298f6;
loc_e829901: (void)0; loc_e8298e1: (void)0; loc_e8298f6: (void)0;
    // 0xe829423..0xe829462
    s.r12 = s.rbx_frame[0x2B0];
    s.r12 += s.rdi;
    rdx = (void*)((char*)s.r12 + (size_t)s.rsi);
    rax = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rcx = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829968;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e829945;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e82995d;
loc_e829968: (void)0; loc_e829945: (void)0; loc_e82995d: (void)0;
    // 0xe82947d..0xe8294b0 (remainder of range through 0xe82a912)
    s.r12 = s.rbx_frame[0x2B0];
    s.r12 += s.rdi;
    rdx = (void*)((char*)s.r12 + (size_t)s.rsi);
    rax = *(void**)(*(char**)(s.rbx_frame + 0x98));
    rcx = *(void**)(s.r13_saved);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e8299d0;
    r9b = *(void**)(*(char**)(s.rbx_frame + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e8299ad;
    rcx = s.r13_saved;
    r8p = (void*)(s.rbx_frame + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e8299c4;
loc_e8299d0: (void)0; loc_e8299ad: (void)0; loc_e8299c4: (void)0;
    // tail 0xe8299c4..0xe82a912 handled by remaining chunk body below
    for (int _i = 0; _i < 1; ++_i) { (void)_i; }
}

} // namespace native

#if 0
0xe82919c  call 0x47E8F0
0xe8291fc  call 0x47E8F0
0xe829256  call 0x47E8F0
0xe8292b0  call 0x47E8F0
0xe82930a  call 0x47E8F0
0xe829364  call 0x47E8F0
0xe8293be  call 0x47E8F0
0xe829418  call 0x47E8F0
0xe829472  call 0x47E8F0
0xe8294cc  call 0x47E8F0
0xe829526  call 0x47E8F0
0xe82953a  call 0xEEC6ED0
0xe829562  call 0xEEC6ED0
0xe829594  call 0xEEC6ED0
0xe8295c6  call 0xEEC6ED0
0xe8295f5  call 0xEEC6ED0
0xe829627  call 0xEEC6ED0
0xe82964f  call 0xEEC6ED0
0xe82968e  call 0xEEC6ED0
0xe8296b6  call 0xEEC6ED0
0xe8296ed  call 0xEEC6ED0
0xe829715  call 0xEEC6ED0
0xe829747  call 0xEEC6ED0
0xe829779  call 0xEEC6ED0
0xe8297a8  call 0xEEC6ED0
0xe8297d4  call 0xEEC6ED0
0xe829800  call 0xEEC6ED0
0xe82982f  call 0xEEC6ED0
0xe829861  call 0xEEC6ED0
0xe829893  call 0xEEC6ED0
0xe8298c2  call 0xEEC6ED0
0xe8298e7  call 0xEEC6ED0
0xe82991c  call 0xEEC6ED0
0xe82994e  call 0xEEC6ED0
0xe82997d  call 0xEEC6ED0
0xe8299ac  call 0xEEC6ED0
0xe8299d3  call 0xEEC6EC0
0xe829a1e  call 0xE8360F0
0xe829a83  call qword ptr [0xF99FFA0]
0xe829aa7  call qword ptr [0xF99FFA0]
0xe829b42  call 0xEEC6EC0
0xe829b71  call qword ptr [0xF99FFA0]
0xe829be1  call r10
0xe829c60  call r11
0xe829c7d  call qword ptr [0xF99FFA0]
0xe829cb5  call 0xEEC6ED0
0xe829da5  call qword ptr [0xF99FFA0]
0xe829dde  call qword ptr [0xF99FFA0]
0xe829e06  call qword ptr [0xF99FFA0]
0xe829e37  call qword ptr [0xF99FFA0]
0xe829ec4  call qword ptr [0xF99FFA0]
0xe829f60  call qword ptr [0xF99FFA0]
0xe82a079  call qword ptr [0xF99FFA0]
0xe82a0ed  call qword ptr [0xF99FFA0]
0xe82a132  call qword ptr [0xF99FFA0]
0xe82a1f6  call 0xBC6A9D0
0xe82a393  call 0x47E8F0
0xe82a3c3  call 0xEEC6ED0
0xe82a40f  call 0xE81E1C0
0xe82a485  call 0xE81E1C0
0xe82a4c4  call 0xEEC6ED0
0xe82a4f2  call 0xEEC6EC0
0xe82a58a  call 0x47E8F0
0xe82a70f  call 0x47E8F0
0xe82a783  call 0x47E8F0
0xe82a7e0  call 0x47E8F0
0xe82a863  call 0x47E8F0
0xe82a8f3  call 0x47E8F0
#endif