// LIFT 0xe8230c8 size 0xa41b 1.26.62.01 sub_e8230c8
// CHUNK 0xe828fe9..0xe82a7d6
#include "client/features/render/native/d3d12/sub_e8230c8.h"

// chunk state documented in docs/functions/e8230c8.md section 'Chunk state'
struct ChunkState_e8230c8_c04 {
    void* rsi;
    void* rbx;
    void* r13;
    void* rdi;
    void* r10;
    void* r11;
    void* r12;
};

static inline void sub_e8230c8_chunk_c04(ChunkState_e8230c8_c04& s) {
    auto* rbx = (unsigned char*)s.rbx;
    auto* rsi = (unsigned char*)s.rsi;
    auto* r13 = (unsigned char*)s.r13;
    unsigned long long rdi = (unsigned long long)s.rdi;
    // 0xe828fe9..0xe829007
    void* rdx = (char*)rsi + (long long)rdi;
    void* rax = *(void**)(rbx + 0x98);
    rax = *(void**)rax;
    void* rcx = *(void**)r13;
    void* r9 = (char*)rax - (long long)rcx;
    void* r8 = (char*)rdx - (long long)r9;
    if ((unsigned long long)r8 <= (unsigned long long)r9) { /* jbe 0xe829997 */ }
    // 0xe82900d..0xe82901e
    r9 = *(void**)(rbx + 0xA0);
    r9 = *(void**)((unsigned char*)r9 + 0x38);
    r9 = (char*)r9 - (long long)rcx;
    if ((unsigned long long)rdx <= (unsigned long long)r9) { /* jbe 0xe829974 */ }
    // 0xe829024..0xe829033
    rcx = r13;
    void* r8b = rbx + 0x3B0;
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe82902e  call 0x47E8F0
    (void)rcx; (void)r8b;
    // 0xe829034..0xe829038
    // jmp 0xe82998c
    // 0xe829039..0xe829092
    unsigned r12d = *(unsigned*)(rbx + 0x2B0);
    unsigned long long r12 = r12d + rdi;
    rdx = (char*)r12 + (long long)rsi;
    rax = *(void**)(rbx + 0x98);
    rax = *(void**)rax;
    rcx = *(void**)r13;
    r9 = (char*)rax - (long long)rcx;
    r8 = (char*)rdx - (long long)r9;
    if ((unsigned long long)r8 <= (unsigned long long)r9) { /* jbe 0xe82957c */ }
    r9 = *(void**)(rbx + 0xA0);
    r9 = *(void**)((unsigned char*)r9 + 0x38);
    r9 = (char*)r9 - (long long)rcx;
    if ((unsigned long long)rdx <= (unsigned long long)r9) { /* jbe 0xe829559 */ }
    rcx = r13;
    r8b = rbx + 0xC0;
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe829088  call 0x47E8F0
    // 0xe82908e..0xe829092
    // jmp 0xe829571
    // 0xe829093..0xe8290e7
    r12d = *(unsigned*)(rbx + 0x2B0);
    r12 = r12d + rdi;
    rdx = (char*)r12 + (long long)rsi;
    rax = *(void**)(rbx + 0x98);
    rax = *(void**)rax;
    rcx = *(void**)r13;
    r9 = (char*)rax - (long long)rcx;
    r8 = (char*)rdx - (long long)r9;
    if ((unsigned long long)r8 <= (unsigned long long)r9) { /* jbe 0xe8295e0 */ }
    r9 = *(void**)(rbx + 0xA0);
    r9 = *(void**)((unsigned char*)r9 + 0x38);
    r9 = (char*)r9 - (long long)rcx;
    if ((unsigned long long)rdx <= (unsigned long long)r9) { /* jbe 0xe8295bd */ }
    rcx = r13;
    r8b = rbx + 0x3B0;
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe8290e2  call 0x47E8F0
    // 0xe8290e8..0xe829141
    // ... additional blocks translated below
    // 0xe82913c..0xe829141
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe82913c  call 0x47E8F0
    // 0xe829142..0xe8291a1
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe82919c  call 0x47E8F0
    // 0xe8291a2..0xe829201
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe8291fc  call 0x47E8F0
    // 0xe829202..0xe82925b
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe829256  call 0x47E8F0
    // 0xe82925c..0xe8292b5
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe8292b0  call 0x47E8F0
    // 0xe8292b6..0xe82930f
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe82930a  call 0x47E8F0
    // 0xe829310..0xe829369
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe829364  call 0x47E8F0
    // 0xe82936a..0xe8293c3
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe8293be  call 0x47E8F0
    // 0xe8293c4..0xe82941d
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe829418  call 0x47E8F0
    // 0xe82941e..0xe829477
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe829472  call 0x47E8F0
    // 0xe829478..0xe8294d1
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe8294cc  call 0x47E8F0
    // 0xe8294d2..0xe82952b
    sub_47e8f0(rcx, r8b, (void*)0); // 0xe829526  call 0x47E8F0
    // 0xe82952c..0xe82953f
    sub_eec6ed0(rcx); // 0xe82953a  call 0xEEC6ED0
    // 0xe829540..0xe829567
    sub_eec6ed0(rcx); // 0xe829562  call 0xEEC6ED0
    // 0xe829568..0xe829599
    sub_eec6ed0(rcx); // 0xe829594  call 0xEEC6ED0
    // 0xe82959a..0xe8295cb
    sub_eec6ed0(rcx); // 0xe8295c6  call 0xEEC6ED0
    // 0xe8295cc..0xe8295fa
    sub_eec6ed0(rcx); // 0xe8295f5  call 0xEEC6ED0
    // 0xe8295fb..0xe82962c
    sub_eec6ed0(rcx); // 0xe829627  call 0xEEC6ED0
    // 0xe82962d..0xe829654
    sub_eec6ed0(rcx); // 0xe82964f  call 0xEEC6ED0
    // 0xe829655..0xe829693
    sub_eec6ed0(rcx); // 0xe82968e  call 0xEEC6ED0
    // 0xe829694..0xe8296bc
    sub_eec6ed0(rcx); // 0xe8296b6  call 0xEEC6ED0
    // 0xe8296bd..0xe8296f2
    sub_eec6ed0(rcx); // 0xe8296ed  call 0xEEC6ED0
    // 0xe8296f3..0xe82971a
    sub_eec6ed0(rcx); // 0xe829715  call 0xEEC6ED0
    // 0xe82971b..0xe82974c
    sub_eec6ed0(rcx); // 0xe829747  call 0xEEC6ED0
    // 0xe82974d..0xe82977e
    sub_eec6ed0(rcx); // 0xe829779  call 0xEEC6ED0
    // 0xe82977f..0xe8297ad
    sub_eec6ed0(rcx); // 0xe8297a8  call 0xEEC6ED0
    // 0xe8297ae..0xe8297d9
    sub_eec6ed0(rcx); // 0xe8297d4  call 0xEEC6ED0
    // 0xe8297da..0xe829805
    sub_eec6ed0(rcx); // 0xe829800  call 0xEEC6ED0
    // 0xe829806..0xe829834
    sub_eec6ed0(rcx); // 0xe82982f  call 0xEEC6ED0
    // 0xe829835..0xe829866
    sub_eec6ed0(rcx); // 0xe829861  call 0xEEC6ED0
    // 0xe829867..0xe829898
    sub_eec6ed0(rcx); // 0xe829893  call 0xEEC6ED0
    // 0xe829899..0xe8298c7
    sub_eec6ed0(rcx); // 0xe8298c2  call 0xEEC6ED0
    // 0xe8298c8..0xe8298ec
    sub_eec6ed0(rcx); // 0xe8298e7  call 0xEEC6ED0
    // 0xe8298ed..0xe829921
    sub_eec6ed0(rcx); // 0xe82991c  call 0xEEC6ED0
    // 0xe829922..0xe829953
    sub_eec6ed0(rcx); // 0xe82994e  call 0xEEC6ED0
    // 0xe829954..0xe829982
    sub_eec6ed0(rcx); // 0xe82997d  call 0xEEC6ED0
    // 0xe829983..0xe829996
    sub_eec6ed0(rcx); // 0xe8299ac  call 0xEEC6ED0
    // 0xe829997..0xe8299d8
    sub_eec6ec0(rcx); // 0xe8299d3  call 0xEEC6EC0
    // 0xe8299d9..0xe829a23
    sub_e8360f0(rbx); // 0xe829a1e  call 0xE8360F0
    // 0xe829a24..0xe829a88
    // vendor thunk via 0xF99FFA0
    // 0xe829a83  call qword ptr [0xF99FFA0]
    // 0xe829aa7  call qword ptr [0xF99FFA0]
    // 0xe829b42  call 0xEEC6EC0
    // 0xe829b71  call qword ptr [0xF99FFA0]
    // 0xe829be1  call r10
    // 0xe829c60  call r11
    // 0xe829c7d  call qword ptr [0xF99FFA0]
    // 0xe829cb5  call 0xEEC6ED0
    // 0xe829da5  call qword ptr [0xF99FFA0]
    // 0xe829dde  call qword ptr [0xF99FFA0]
    // 0xe829e06  call qword ptr [0xF99FFA0]
    // 0xe829e37  call qword ptr [0xF99FFA0]
    // 0xe829ec4  call qword ptr [0xF99FFA0]
    // 0xe829f60  call qword ptr [0xF99FFA0]
    // 0xe82a079  call qword ptr [0xF99FFA0]
    // 0xe82a0ed  call qword ptr [0xF99FFA0]
    // 0xe82a132  call qword ptr [0xF99FFA0]
    // 0xe82a1f6  call 0xBC6A9D0
    // 0xe82a393  call 0x47E8F0
    // 0xe82a3c3  call 0xEEC6ED0
    // 0xe82a40f  call 0xE81E1C0
    // 0xe82a485  call 0xE81E1C0
    // 0xe82a4c4  call 0xEEC6ED0
    // 0xe82a4f2  call 0xEEC6EC0
    // 0xe82a58a  call 0x47E8F0
    // 0xe82a70f  call 0x47E8F0
    // 0xe82a783  call 0x47E8F0
    // final fallthrough
    (void)rbx; (void)rsi; (void)r13; (void)rdi; (void)r9; (void)r8; (void)rdx; (void)rcx; (void)rax;
    (void)r12; (void)r12d;
}

#if 0
0xe82902e  call 0x47E8F0
0xe829088  call 0x47E8F0
0xe8290e2  call 0x47E8F0
0xe82913c  call 0x47E8F0
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
#endif