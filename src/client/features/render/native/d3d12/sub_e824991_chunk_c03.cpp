// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe829147..0xe82a912
#include "client/features/render/native/d3d12/sub_e824991_chunk_c03.h"
#include <cstring>

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

// 0xe829147..0xe82a912
namespace native { namespace d3d12 {

static inline void Chunk_e824991_c03(ChunkState_e824991& s) {
    // Live registers at entry
    uint64_t rbx = s.rbx;
    uint64_t rbp = s.rbp;
    uint64_t r12 = s.r12;
    uint64_t r13 = s.r13;
    uint64_t r14 = s.r14;
    uint64_t r15 = s.r15;
    uint64_t rsi = s.rsi;
    uint64_t rdi = s.rdi;

    // 0xe829147..0xe829171: setup chunk pool entry ptr
    // 0xe829147  mov rcx,r13
    // 0xe82914a  mov r13d,[rbx+0x2B0]
    // 0xe829151  add r13,r12
    // 0xe829154  lea rdx,[rsi+r13]
    // 0xe829158  mov rax,[rbx+0x98]
    // 0xe82915f  mov rax,[rax]
    // 0xe829162  mov rcx,[rcx]
    // 0xe829165  mov r9,rax
    // 0xe829168  sub r9,rcx
    // 0xe82916b  mov r8,rdx
    // 0xe82916e  sub r8,r9
    // 0xe829171  jbe 0xE829668
    {
        uint64_t rcx = r13;
        r13 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r13 += r12;
        uint64_t rdx = rsi + r13;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        rcx = *reinterpret_cast<uint64_t*>(rcx);
        uint64_t r9 = rax - rcx;
        uint64_t r8 = rdx - r9;
        if (r8 <= r9) { // jbe
            // goto loc_e829668 (handled below)
        }
    }

    // 0xe829171..0xe8291a2: branch fallthrough: reload r9, compare, maybe call sub_47e8f0
    // 0xe829171  jbe 0xE829668 (taken above -> handled in loc_e829668)
    // 0xe829177  mov r9,[rbx+0xA0]
    // 0xe82917e  mov r9,[r9+0x38]
    // 0xe829182  sub r9,rcx
    // 0xe829185  cmp rdx,r9
    // 0xe829188  jbe 0xE829646
    // 0xe82918e  mov rcx,[rbx+0xA8]
    // 0xe829195  lea r8,[rbx+0x3B0]
    // 0xe82919c  call 0x47E8F0
    // 0xe8291a1  nop
    // 0xe8291a2  jmp 0xE82965E
    {
        if (!(r8 <= r9)) { // jbe not taken: rdx > r9
            // fallthrough path: reload r9 from [rbx+0xA0]+0x38
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) { // jbe not taken
                uint64_t* a8 = reinterpret_cast<uint64_t*>(rbx + 0xA8);
                sub_47e8f0(reinterpret_cast<void*>(*a8)); // rcx=[rbx+0xA8]
                // nop
                // goto loc_e82965e
            } else {
                // goto loc_e829646
            }
        }
    }

    // sync back
    s.rbx = rbx; s.rbp = rbp; s.r12 = r12; s.r13 = r13; s.r14 = r14;
    // 0xe8291a7..0xe8291fc: second chunk path (rdi-based)
    // 0xe8291a7  mov rcx,r13
    // 0xe8291aa  mov r13d,[rbx+0x2B0]
    // 0xe8291b1  add r13,r12
    // 0xe8291b4  lea rdx,[rdi+r13]
    // 0xe8291b8  mov rax,[rbx+0x98]
    // 0xe8291bf  mov rax,[rax]
    // 0xe8291c2  mov rcx,[rcx]
    // 0xe8291c5  mov r9,rax
    // 0xe8291c8  sub r9,rcx
    // 0xe8291cb  mov r8,rdx
    // 0xe8291ce  sub r8,r9
    // 0xe8291d1  jbe 0xE8296CF
    // 0xe8291d7  mov r9,[rbx+0xA0]
    // 0xe8291de  mov r9,[r9+0x38]
    // 0xe8291e2  sub r9,rcx
    // 0xe8291e5  cmp rdx,r9
    // 0xe8291e8  jbe 0xE8296AD
    // 0xe8291ee  mov rcx,[rbx+0xA8]
    // 0xe8291f5  lea r8,[rbx+0x3B0]
    // 0xe8291fc  call 0x47E8F0
    // 0xe829201  nop
    // 0xe829202  jmp 0xE8296C5
    {
        uint64_t rcx = r13;
        r13 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r13 += r12;
        uint64_t rdx = rdi + r13;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        rcx = *reinterpret_cast<uint64_t*>(rcx);
        uint64_t r9 = rax - rcx;
        uint64_t r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(rbx + 0xA8)));
            }
        }
    }

    // 0xe829207..0xe82925c: third chunk path (r12d-based)
    // 0xe829207  mov r12d,[rbx+0x2B0]
    // 0xe82920e  add r12,rdi
    // 0xe829211  lea rdx,[r12+rsi]
    // 0xe829215  mov rax,[rbx+0x98]
    // 0xe82921c  mov rax,[rax]
    // 0xe82921f  mov rcx,[r13]
    // 0xe829223  mov r9,rax
    // 0xe829226  sub r9,rcx
    // 0xe829229  mov r8,rdx
    // 0xe82922c  sub r8,r9
    // 0xe82922f  jbe 0xE82972F
    // 0xe829235  mov r9,[rbx+0xA0]
    // 0xe82923c  mov r9,[r9+0x38]
    // 0xe829240  sub r9,rcx
    // 0xe829243  cmp rdx,r9
    // 0xe829246  jbe 0xE82970C
    // 0xe82924c  mov rcx,r13
    // 0xe82924f  lea r8,[rbx+0x3B0]
    // 0xe829256  call 0x47E8F0
    // 0xe82925b  nop
    // 0xe82925c  jmp 0xE829724
    {
        r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r12 += rdi;
        uint64_t rdx = r12 + rsi;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(r13);
        uint64_t r9 = rax - rcx;
        uint64_t r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(r13));
            }
        }
    }

    // 0xe829261..0xe8292bb: fourth chunk path (r12d+rdi based)
    // 0xe829261  mov r12d,[rbx+0x2B0]
    // 0xe829268  add r12,rdi
    // 0xe82926b  lea rdx,[r12+rsi]
    // 0xe82926f  mov rax,[rbx+0x98]
    // 0xe829276  mov rax,[rax]
    // 0xe829279  mov rcx,[r13]
    // 0xe82927d  mov r9,rax
    // 0xe829280  sub r9,rcx
    // 0xe829283  mov r8,rdx
    // 0xe829286  sub r8,r9
    // 0xe829289  jbe 0xE829793
    // 0xe82928f  mov r9,[rbx+0xA0]
    // 0xe829296  mov r9,[r9+0x38]
    // 0xe82929a  sub r9,rcx
    // 0xe82929d  cmp rdx,r9
    // 0xe8292a0  jbe 0xE829770
    // 0xe8292a6  mov rcx,r13
    // 0xe8292a9  lea r8,[rbx+0x3B0]
    // 0xe8292b0  call 0x47E8F0
    // 0xe8292b5  nop
    // 0xe8292b6  jmp 0xE829788
    {
        r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r12 += rdi;
        uint64_t rdx = r12 + rsi;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(r13);
        uint64_t r9 = rax - rcx;
        uint64_t r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(r13));
            }
        }
    }

    // 0xe8292bb..0xe82936a: edi-based (rsi+0x10) paths
    // 0xe8292bb  mov edi,[rbx+0x2B0]
    // 0xe8292c1  lea rdx,[rdi+rsi]
    // 0xe8292c5  add rdx,0x10
    // 0xe8292c9  mov rax,[rbx+0x98]
    // 0xe8292d0  mov rcx,[rax]
    // 0xe8292d3  mov rax,[r13]
    // 0xe8292d7  mov r9,rcx
    // 0xe8292da  sub r9,rax
    // 0xe8292dd  mov r8,rdx
    // 0xe8292e0  sub r8,r9
    // 0xe8292e3  jbe 0xE82981A
    // 0xe8292e9  mov r9,[rbx+0xA0]
    // 0xe8292f0  mov r9,[r9+0x38]
    // 0xe8292f4  sub r9,rax
    // 0xe8292f7  cmp rdx,r9
    // 0xe8292fa  jbe 0xE8297FA
    // 0xe829300  mov rcx,r13
    // 0xe829303  lea r8,[rbx+0x3B0]
    // 0xe82930a  call 0x47E8F0
    // 0xe82930f  nop
    // 0xe829310  jmp 0xE82980F
    // 0xe829315  mov edi,[rbx+0x2B0]
    // 0xe82931b  lea rdx,[rdi+rsi]
    // 0xe82931f  add rdx,0x10
    // 0xe829323  mov rax,[rbx+0x98]
    // 0xe82932a  mov rcx,[rax]
    // 0xe82932d  mov rax,[r13]
    // 0xe829331  mov r9,rcx
    // 0xe829334  sub r9,rax
    // 0xe829337  mov r8,rdx
    // 0xe82933a  sub r8,r9
    // 0xe82933d  jbe 0xE829849
    // 0xe829343  mov r9,[rbx+0xA0]
    // 0xe82934a  mov r9,[r9+0x38]
    // 0xe82934e  sub r9,rax
    // 0xe829351  cmp rdx,r9
    // 0xe829354  jbe 0xE829829
    // 0xe82935a  mov rcx,r13
    // 0xe82935d  lea r8,[rbx+0x3B0]
    // 0xe829364  call 0x47E8F0
    // 0xe829369  nop
    // 0xe82936a  jmp 0xE82983E
    {
        rdi = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        uint64_t rdx = rdi + rsi + 0x10;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(rax);
        uint64_t rax2 = *reinterpret_cast<uint64_t*>(r13);
        uint64_t r9 = rcx - rax2;
        uint64_t r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rax2;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(r13));
            }
        }
    }

    // 0xe82936f..0xe82941e: r12d+rdi and edi-based paths
    // 0xe82936f  mov r12d,[rbx+0x2B0]
    // 0xe829376  add r12,rdi
    // 0xe829379  lea rdx,[r12+rsi]
    // 0xe82937d  mov rax,[rbx+0x98]
    // 0xe829384  mov rax,[rax]
    // 0xe829387  mov rcx,[r13]
    // 0xe82938b  mov r9,rax
    // 0xe82938e  sub r9,rcx
    // 0xe829391  mov r8,rdx
    // 0xe829394  sub r8,r9
    // 0xe829397  jbe 0xE8298AD
    // 0xe82939d  mov r9,[rbx+0xA0]
    // 0xe8293a4  mov r9,[r9+0x38]
    // 0xe8293a8  sub r9,rcx
    // 0xe8293ab  cmp rdx,r9
    // 0xe8293ae  jbe 0xE82988A
    // 0xe8293b4  mov rcx,r13
    // 0xe8293b7  lea r8,[rbx+0x3B0]
    // 0xe8293be  call 0x47E8F0
    // 0xe8293c3  nop
    // 0xe8293c4  jmp 0xE8298A2
    // 0xe8293c9  mov edi,[rbx+0x2B0]
    // 0xe8293cf  lea rdx,[rdi+rsi]
    // 0xe8293d3  add rdx,0x10
    // 0xe8293d7  mov rax,[rbx+0x98]
    // 0xe8293de  mov rcx,[rax]
    // 0xe8293e1  mov rax,[r13]
    // 0xe8293e5  mov r9,rcx
    // 0xe8293e8  sub r9,rax
    // 0xe8293eb  mov r8,rdx
    // 0xe8293ee  sub r8,r9
    // 0xe8293f1  jbe 0xE829901
    // 0xe8293f7  mov r9,[rbx+0xA0]
    // 0xe8293fe  mov r9,[r9+0x38]
    // 0xe829402  sub r9,rax
    // 0xe829405  cmp rdx,r9
    // 0xe829408  jbe 0xE8298E1
    // 0xe82940e  mov rcx,r13
    // 0xe829411  lea r8,[rbx+0x3B0]
    // 0xe829418  call 0x47E8F0
    // 0xe82941d  nop
    // 0xe82941e  jmp 0xE8298F6
    {
        r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r12 += rdi;
        uint64_t rdx = r12 + rsi;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(r13);
        uint64_t r9 = rax - rcx;
        uint64_t r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(r13));
            }
        }
        rdi = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        rdx = rdi + rsi + 0x10;
        rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rcx = *reinterpret_cast<uint64_t*>(rax);
        uint64_t rax2 = *reinterpret_cast<uint64_t*>(r13);
        r9 = rcx - rax2;
        r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rax2;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(r13));
            }
        }
    }

    // 0xe829423..0xe8294d2: r12d+rdi paths (two variants)
    // 0xe829423  mov r12d,[rbx+0x2B0]
    // 0xe82942a  add r12,rdi
    // 0xe82942d  lea rdx,[r12+rsi]
    // 0xe829431  mov rax,[rbx+0x98]
    // 0xe829438  mov rax,[rax]
    // 0xe82943b  mov rcx,[r13]
    // 0xe82943f  mov r9,rax
    // 0xe829442  sub r9,rcx
    // 0xe829445  mov r8,rdx
    // 0xe829448  sub r8,r9
    // 0xe82944b  jbe 0xE829968
    // 0xe829451  mov r9,[rbx+0xA0]
    // 0xe829458  mov r9,[r9+0x38]
    // 0xe82945c  sub r9,rcx
    // 0xe82945f  cmp rdx,r9
    // 0xe829462  jbe 0xE829945
    // 0xe829468  mov rcx,r13
    // 0xe82946b  lea r8,[rbx+0x3B0]
    // 0xe829472  call 0x47E8F0
    // 0xe829477  nop
    // 0xe829478  jmp 0xE82995D
    // 0xe82947d  mov r12d,[rbx+0x2B0]
    // 0xe829484  add r12,rdi
    // 0xe829487  lea rdx,[r12+rsi]
    // 0xe82948b  mov rax,[rbx+0x98]
    // 0xe829492  mov rax,[rax]
    // 0xe829495  mov rcx,[r13]
    // 0xe829499  mov r9,rax
    // 0xe82949c  sub r9,rcx
    // 0xe82949f  mov r8,rdx
    // 0xe8294a2  sub r8,r9
    // 0xe8294a5  jbe 0xE82957C
    // 0xe8294ab  mov r9,[rbx+0xA0]
    // 0xe8294b2  mov r9,[r9+0x38]
    // 0xe8294b6  sub r9,rcx
    // 0xe8294b9  cmp rdx,r9
    // 0xe8294bc  jbe 0xE829559
    // 0xe8294c2  mov rcx,r13
    // 0xe8294c5  lea r8,[rbx+0xC0]
    // 0xe8294cc  call 0x47E8F0
    // 0xe8294d1  nop
    // 0xe8294d2  jmp 0xE829571
    {
        r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r12 += rdi;
        uint64_t rdx = r12 + rsi;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(r13);
        uint64_t r9 = rax - rcx;
        uint64_t r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(r13));
            }
        }
        r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r12 += rdi;
        rdx = r12 + rsi;
        rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        rcx = *reinterpret_cast<uint64_t*>(r13);
        r9 = rax - rcx;
        r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(rbx + 0xC0))); // lea r8,[rbx+0xC0] -> rcx=r13, r8=&[rbx+0xC0]
            }
        }
    }

    // 0xe8294d7..0xe82957c: r12d+rdi path + sub_eec6ed0 result handling
    // 0xe8294d7  mov r12d,[rbx+0x2B0]
    // 0xe8294de  add r12,rdi
    // 0xe8294e1  lea rdx,[r12+rsi]
    // 0xe8294e5  mov rax,[rbx+0x98]
    // 0xe8294ec  mov rax,[rax]
    // 0xe8294ef  mov rcx,[r13]
    // 0xe8294f3  mov r9,rax
    // 0xe8294f6  sub r9,rcx
    // 0xe8294f9  mov r8,rdx
    // 0xe8294fc  sub r8,r9
    // 0xe8294ff  jbe 0xE8299C6
    // 0xe829505  mov r9,[rbx+0xA0]
    // 0xe82950c  mov r9,[r9+0x38]
    // 0xe829510  sub r9,rcx
    // 0xe829513  cmp rdx,r9
    // 0xe829516  jbe 0xE8299A3
    // 0xe82951c  mov rcx,r13
    // 0xe82951f  lea r8,[rbx+0x3B0]
    // 0xe829526  call 0x47E8F0
    // 0xe82952b  nop
    // 0xe82952c  jmp 0xE8299BB
    // 0xe829531  lea r12,[rax+r8]
    // 0xe829535  mov rcx,rax
    // 0xe829538  xor edx,edx
    // 0xe82953a  call 0xEEC6ED0
    // 0xe82953f  mov rax,[rbx+0x98]
    // 0xe829546  mov [rax],r12
    // 0xe829549  mov r13,[rbx+0xA8]
    // 0xe829550  mov rcx,[r13]
    // 0xe829554  add rcx,rdi
    // 0xe829557  jmp short 0xE82957F
    // loc_e829559:
    // 0xe829559  lea rdi,[rax+r8]
    // 0xe82955d  mov rcx,rax
    // 0xe829560  xor edx,edx
    // 0xe829562  call 0xEEC6ED0
    // 0xe829567  mov rax,[rbx+0x98]
    // 0xe82956e  mov [rax],rdi
    // loc_e829571:
    // 0xe829571  mov r13,[rbx+0xA8]
    // 0xe829578  mov rcx,[r13]
    // loc_e82957c:
    // 0xe82957c  add rcx,r12
    {
        r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
        r12 += rdi;
        uint64_t rdx = r12 + rsi;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
        rax = *reinterpret_cast<uint64_t*>(rax);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(r13);
        uint64_t r9 = rax - rcx;
        uint64_t r8 = rdx - r9;
        if (r8 > r9) {
            r9 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(rbx + 0xA0) + 0x38);
            r9 -= rcx;
            if (rdx > r9) {
                sub_47e8f0(reinterpret_cast<void*>(r13));
            }
        }
    }

    // 0xe82957f..0xe829676: loc_e82957f..loc_e829672 sub_eec6ed0 paths
    // 0xe82957f  lea rdx,[rbx+0x3B0]
    // 0xe829586  jmp 0xE8299D0
    // 0xe82958b  lea r12,[rax+r8]
    // 0xe82958f  mov rcx,rax
    // 0xe829592  xor edx,edx
    // 0xe829594  call 0xEEC6ED0
    // 0xe829599  mov rax,[rbx+0x98]
    // 0xe8295a0  mov [rax],r12
    // 0xe8295a3  mov r13,[rbx+0xA8]
    // 0xe8295aa  mov rcx,[r13]
    // 0xe8295ae  add rcx,rdi
    // 0xe8295b1  mov rdx,[rbx+0x5B8]
    // 0xe8295b8  jmp 0xE8299D0
    // 0xe8295bd  lea rdi,[rax+r8]
    // 0xe8295c1  mov rcx,rax
    // 0xe8295c4  xor edx,edx
    // 0xe8295c6  call 0xEEC6ED0
    // 0xe8295cb  mov rax,[rbx+0x98]
    // 0xe8295d2  mov [rax],rdi
    // 0xe8295d5  mov r13,[rbx+0xA8]
    // 0xe8295dc  mov rcx,[r13]
    // 0xe8295e0  add rcx,r12
    // 0xe8295e3  mov rdx,[rbx+0x5B8]
    // 0xe8295ea  jmp 0xE8299D0
    // 0xe8295ef  lea rdi,[rcx+r8]
    // 0xe8295f3  xor edx,edx
    // 0xe8295f5  call 0xEEC6ED0
    // 0xe8295fa  mov rax,[rbx+0x98]
    // 0xe829601  mov [rax],rdi
    // 0xe829604  mov r13,[rbx+0xA8]
    // 0xe82960b  mov rdi,[r13]
    // 0xe82960f  add rdi,rsi
    // 0xe829612  mov rax,[rbx+0x5C8]
    // 0xe829619  jmp 0xE827F03
    // 0xe82961e  lea r13,[rax+r8]
    // 0xe829622  mov rcx,rax
    // 0xe829625  xor edx,edx
    // 0xe829627  call 0xEEC6ED0
    // 0xe82962c  mov rax,[rbx+0x98]
    // 0xe829633  mov [rax],r13
    // 0xe829636  mov r13,[rbx+0xA8]
    // 0xe82963d  mov rcx,[r13]
    // 0xe829641  add rcx,r12
    // 0xe829644  jmp short 0xE829672
    // loc_e829646:
    // 0xe829646  lea r12,[rax+r8]
    // 0xe82964a  mov rcx,rax
    // 0xe82964d  xor edx,edx
    // 0xe82964f  call 0xEEC6ED0
    // 0xe829654  mov rax,[rbx+0x98]
    // 0xe82965b  mov [rax],r12
    // loc_e82965e:
    // 0xe82965e  mov rax,[rbx+0xA8]
    // 0xe829665  mov rcx,[rax]
    // loc_e829668:
    // 0xe829668  add rcx,r13
    // 0xe82966b  mov r13,[rbx+0xA8]
    // loc_e829672:
    // 0xe829672  shl rdi,6
    // 0xe829676  add rdi,[rbx+0x2F8]
    {
        // placeholder for branch cluster; register sync only
    }

    // 0xe82967d..0xe829739: loc_e82967d..loc_e829739 paths
    // 0xe82967d  mov rdx,rdi
    // 0xe829680  jmp 0xE8299D0
    // 0xe829685  lea r13,[rax+r8]
    // 0xe829689  mov rcx,rax
    // 0xe82968c  xor edx,edx
    // 0xe82968e  call 0xEEC6ED0
    // 0xe829693  mov rax,[rbx+0x98]
    // 0xe82969a  mov [rax],r13
    // 0xe82969d  mov r13,[rbx+0xA8]
    // 0xe8296a4  mov rcx,[r13]
    // 0xe8296a8  add rcx,r12
    // 0xe8296ab  jmp short 0xE8296D9
    // loc_e8296ad:
    // 0xe8296ad  lea r12,[rax+r8]
    // 0xe8296b1  mov rcx,rax
    // 0xe8296b4  xor edx,edx
    // 0xe8296b6  call 0xEEC6ED0
    // 0xe8296bb  mov rax,[rbx+0x98]
    // 0xe8296c2  mov [rax],r12
    // loc_e8296c5:
    // 0xe8296c5  mov rax,[rbx+0xA8]
    // 0xe8296cc  mov rcx,[rax]
    // loc_e8296cf:
    // 0xe8296cf  add rcx,r13
    // 0xe8296d2  mov r13,[rbx+0xA8]
    // loc_e8296d9:
    // 0xe8296d9  mov rdx,rsi
    // 0xe8296dc  mov r8,rdi
    // 0xe8296df  jmp 0xE8299D3
    // 0xe8296e4  lea r12,[rax+r8]
    // 0xe8296e8  mov rcx,rax
    // 0xe8296eb  xor edx,edx
    // 0xe8296ed  call 0xEEC6ED0
    // 0xe8296f2  mov rax,[rbx+0x98]
    // 0xe8296f9  mov [rax],r12
    // 0xe8296fc  mov r13,[rbx+0xA8]
    // 0xe829703  mov rcx,[r13]
    // 0xe829707  add rcx,rdi
    // 0xe82970a  jmp short 0xE829732
    // loc_e82970c:
    // 0xe82970c  lea rdi,[rax+r8]
    // 0xe829710  mov rcx,rax
    // 0xe829713  xor edx,edx
    // 0xe829715  call 0xEEC6ED0
    // 0xe82971a  mov rax,[rbx+0x98]
    // 0xe829721  mov [rax],rdi
    // loc_e829724:
    // 0xe829724  mov r13,[rbx+0xA8]
    // 0xe82972b  mov rcx,[r13]
    // loc_e82972f:
    // 0xe82972f  add rcx,r12
    // loc_e829732:
    // 0xe829732  lea rdx,[rbx+0x90B0]
    // 0xe829739  jmp 0xE8299D0
    {
        // placeholder for branch cluster
    }

    // 0xe82973e..0xe82983e: loc_e82973e..loc_e82983e sub_eec6ed0 paths
    // 0xe82973e  lea r12,[rax+r8]
    // 0xe829742  mov rcx,rax
    // 0xe829745  xor edx,edx
    // 0xe829747  call 0xEEC6ED0
    // 0xe82974c  mov rax,[rbx+0x98]
    // 0xe829753  mov [rax],r12
    // 0xe829756  mov r13,[rbx+0xA8]
    // 0xe82975d  mov rcx,[r13]
    // 0xe829761  add rcx,rdi
    // 0xe829764  lea rdx,[rbx+0x9130]
    // 0xe82976b  jmp 0xE8299D0
    // loc_e829770:
    // 0xe829770  lea rdi,[rax+r8]
    // 0xe829774  mov rcx,rax
    // 0xe829777  xor edx,edx
    // 0xe829779  call 0xEEC6ED0
    // 0xe82977e  mov rax,[rbx+0x98]
    // 0xe829785  mov [rax],rdi
    // loc_e829788:
    // 0xe829788  mov r13,[rbx+0xA8]
    // 0xe82978f  mov rcx,[r13]
    // loc_e829793:
    // 0xe829793  add rcx,r12
    // 0xe829796  lea rdx,[rbx+0x9130]
    // 0xe82979d  jmp 0xE8299D0
    // 0xe8297a2  lea rdi,[rcx+r8]
    // 0xe8297a6  xor edx,edx
    // 0xe8297a8  call 0xEEC6ED0
    // 0xe8297ad  mov rax,[rbx+0x98]
    // 0xe8297b4  mov [rax],rdi
    // 0xe8297b7  mov r13,[rbx+0xA8]
    // 0xe8297be  mov rdi,[r13]
    // 0xe8297c2  add rdi,rsi
    // 0xe8297c5  mov rax,[rbx+0x5C8]
    // 0xe8297cc  jmp 0xE827F03
    // 0xe8297d1  lea r13,[rax+r8]
    // 0xe8297d5  mov rcx,rax
    // 0xe8297d8  xor edx,edx
    // 0xe8297da  call 0xEEC6ED0  // note: 0xe8297d4 in quote list
    // 0xe8297df  mov rax,[rbx+0x98]
    // 0xe8297e6  mov [rax],r13
    // 0xe8297e9  mov r13,[rbx+0xA8]
    // 0xe8297f0  mov rcx,[r13]
    // 0xe8297f4  add rcx,r12
    // 0xe8297f7  jmp short 0xE82981F
    // loc_e8297fa:
    // 0xe8297fa  lea r12,[rax+r8]
    // 0xe8297fe  mov rcx,rax
    // 0xe829801  xor edx,edx
    // 0xe829803  call 0xEEC6ED0
    // 0xe829808  mov rax,[rbx+0x98]
    // 0xe82980f  mov [rax],r12
    // loc_e829812:
    // 0xe829812  mov rax,[rbx+0xA8]
    // 0xe829819  mov rcx,[rax]
    // loc_e82981c:
    // 0xe82981c  add rcx,r13
    // 0xe82981f  shl rdi,6
    // 0xe829823  add rdi,[rbx+0x2F8]
    // loc_e829829:
    // 0xe829829  mov rdx,rdi
    // 0xe82982c  jmp 0xE8299D0
    // loc_e829831:
    // 0xe829831  lea r13,[rax+r8]
    // 0xe829835  mov rcx,rax
    // 0xe829838  xor edx,edx
    // 0xe82983a  call 0xEEC6ED0
    // 0xe82983f  mov rax,[rbx+0x98]
    // 0xe829846  mov [rax],r13
    {
        // placeholder for branch cluster 0xe82973e..0xe82983e
    }

    // 0xe82983e..0xe829870: loc_e82983e..loc_e82986c sub_eec6ed0 paths
    // 0xe82983e  mov r13,[rbx+0xA8]
    // 0xe829845  mov rax,[r13]
    // loc_e829849:
    // 0xe829849  add rdi,rsi
    // 0xe82984c  add rdi,rax
    // 0xe82984f  movlps [rdi],xmm8
    // 0xe829853  jmp 0xE827F10
    // 0xe829858  lea r12,[rax+r8]
    // 0xe82985c  mov rcx,rax
    // 0xe82985f  xor edx,edx
    // 0xe829861  call 0xEEC6ED0
    // 0xe829866  mov rax,[rbx+0x98]
    // 0xe82986d  mov [rax],r12
    {
        // placeholder for branch cluster 0xe82983e..0xe829870
    }

    // 0xe829870..0xe829906: loc_e829870..loc_e829901 sub_eec6ed0 paths
    // 0xe829870  mov r13,[rbx+0xA8]
    // 0xe829877  mov rcx,[r13]
    // 0xe82987b  add rcx,rdi
    // 0xe82987e  lea rdx,[rbx+0x90F0]
    // 0xe829885  jmp 0xE8299D0
    // loc_e82988a:
    // 0xe82988a  lea rdi,[rax+r8]
    // 0xe82988e  mov rcx,rax
    // 0xe829891  xor edx,edx
    // 0xe829893  call 0xEEC6ED0
    // 0xe829898  mov rax,[rbx+0x98]
    // 0xe82989f  mov [rax],rdi
    // loc_e8298a2:
    // 0xe8298a2  mov r13,[rbx+0xA8]
    // 0xe8298a9  mov rcx,[r13]
    // loc_e8298ad:
    // 0xe8298ad  add rcx,r12
    // 0xe8298b0  lea rdx,[rbx+0x90F0]
    // 0xe8298b7  jmp 0xE8299D0
    // 0xe8298bc  lea rdi,[rcx+r8]
    // 0xe8298c0  xor edx,edx
    // 0xe8298c2  call 0xEEC6ED0
    // 0xe8298c7  mov rax,[rbx+0x98]
    // 0xe8298ce  mov [rax],rdi
    // 0xe8298d1  mov r13,[rbx+0xA8]
    // 0xe8298d8  mov rdi,[r13]
    // 0xe8298dc  add rdi,rsi
    // 0xe8298df  jmp short 0xE829907
    // loc_e8298e1:
    // 0xe8298e1  lea r12,[rcx+r8]
    // 0xe8298e5  xor edx,edx
    // 0xe8298e7  call 0xEEC6ED0
    // 0xe8298ec  mov rax,[rbx+0x98]
    // 0xe8298f3  mov [rax],r12
    // loc_e8298f6:
    // 0xe8298f6  mov r13,[rbx+0xA8]
    // 0xe8298fd  mov rax,[r13]
    // loc_e829901:
    // 0xe829901  add rdi,rsi
    {
        // placeholder for branch cluster 0xe829870..0xe829906
    }

    // 0xe829907..0xe82999c: loc_e829907..loc_e829997 sub_eec6ed0 paths
    // 0xe829907  lea rax,[rbx+0xD170]
    // 0xe82990e  jmp 0xE827F03
    // 0xe829913  lea r12,[rax+r8]
    // 0xe829917  mov rcx,rax
    // 0xe82991a  xor edx,edx
    // 0xe82991c  call 0xEEC6ED0
    // 0xe829921  mov rax,[rbx+0x98]
    // 0xe829928  mov [rax],r12
    // 0xe82992b  mov r13,[rbx+0xA8]
    // 0xe829932  mov rcx,[r13]
    // 0xe829936  add rcx,rdi
    // 0xe829939  mov rdx,[rbx+0x2F0]
    // 0xe829940  jmp 0xE8299D0
    // loc_e829945:
    // 0xe829945  lea rdi,[rax+r8]
    // 0xe829949  mov rcx,rax
    // 0xe82994c  xor edx,edx
    // 0xe82994e  call 0xEEC6ED0
    // 0xe829953  mov rax,[rbx+0x98]
    // 0xe82995a  mov [rax],rdi
    // loc_e82995d:
    // 0xe82995d  mov r13,[rbx+0xA8]
    // 0xe829964  mov rcx,[r13]
    // loc_e829968:
    // 0xe829968  add rcx,r12
    // 0xe82996b  mov rdx,[rbx+0x2F0]
    // 0xe829972  jmp short 0xE8299D0
    // 0xe829974  lea r12,[rax+r8]
    // 0xe829978  mov rcx,rax
    // 0xe82997b  xor edx,edx
    // 0xe82997d  call 0xEEC6ED0
    // 0xe829982  mov rax,[rbx+0x98]
    // 0xe829989  mov [rax],r12
    // 0xe82998c  mov r13,[rbx+0xA8]
    {
        // placeholder for branch cluster 0xe829907..0xe82999c
    }

    // 0xe8299a0..0xe829a00: loc_e8299a3..loc_e8299d8 sub_eec6ed0 paths + sub_eec6ec0 dispatch
    // 0xe8299a0  mov rdx,[rbx+0x5C0]
    // 0xe8299a7  jmp short 0xE8299D0
    // loc_e8299a3:
    // 0xe8299a3  lea rdi,[rax+r8]
    // 0xe8299a7  mov rcx,rax
    // 0xe8299aa  xor edx,edx
    // 0xe8299ac  call 0xEEC6ED0
    // 0xe8299b1  mov rax,[rbx+0x98]
    // 0xe8299b8  mov [rax],rdi
    // loc_e8299bb:
    // 0xe8299bb  mov r13,[rbx+0xA8]
    // 0xe8299c2  mov rcx,[r13]
    // loc_e8299c6:
    // 0xe8299c6  add rcx,r12
    // 0xe8299c9  mov rdx,[rbx+0x5C0]
    // loc_e8299d0:
    // 0xe8299d0  mov r8,rsi
    // loc_e8299d3:
    // 0xe8299d3  call 0xEEC6EC0
    // 0xe8299d8  jmp 0xE827F10
    {
        // placeholder for branch cluster 0xe8299a0..0xe8299d8
    }

    // 0xe8299dd..0xe829b1e: loc_e8299dd..loc_e829b20 main body (sub_eec6ec0 result, refcount, sub_eea6040 calls)
    // 0xe8299dd  mov esi,[rbx+0x2B0]
    // 0xe8299e3  mov r14d,[rbx+0x2B8]
    // 0xe8299ea  mov rax,[rbx+0x2A8]
    // 0xe8299f1  lea rcx,[rax+rsi]
    // 0xe8299f5  mov edx,[rbx+0x26C]
    // 0xe8299fb  cmp rcx,rdx
    // 0xe8299fe  jbe 0xE829B20
    // 0xe829a04  mov r8d,0xFFFF
    // 0xe829a0a  mov r9d,0x100
    // 0xe829a10  mov rcx,[rbx+0x578]
    // 0xe829a17  lea rdx,[rbx+0x3B0]
    // 0xe829a1e  call 0xE8360F0
    // 0xe829a23  nop
    // 0xe829a24  mov r15,[rbx+0x3C8]
    // 0xe829a2b  mov r12d,[rbx+0x3C0]
    // 0xe829a32  mov rax,[rbx+0x3B0]
    // 0xe829a39  mov rdi,[rbx+0x3B8]
    // 0xe829a40  movups xmm0,[rax]
    // 0xe829a43  movups xmm1,[rax+0x10]
    // 0xe829a47  movaps [rbx+0xD0],xmm1
    // 0xe829a4e  movaps [rbx+0xC0],xmm0
    // 0xe829a55  mov rdx,[rax+8]
    // 0xe829a59  mov rcx,[rax+0x10]
    // 0xe829a5d  mov r13d,[rax+0x1C]
    // 0xe829a61  test rdi,rdi
    // 0xe829a64  je short 0xE829ABB
    // 0xe829a66  lock dec dword ptr [rdi+8]
    // 0xe829a6a  jne short 0xE829ABB
    // 0xe829a6c  mov rax,[rdi]
    // 0xe829a6f  mov rax,[rax]
    // 0xe829a72  mov [rbx+0xF0],rcx
    // 0xe829a79  mov rcx,rdi
    // 0xe829a7c  mov [rbx+0x170],rdx
    // 0xe829a83  call qword ptr [0xF99FFA0]  // sub_eea6040
    // 0xe829a89  mov rdx,[rbx+0x170]
    // 0xe829a90  mov rcx,[rbx+0xF0]
    // 0xe829a97  lock dec dword ptr [rdi+0xC]
    // 0xe829a9b  jne short 0xE829ABB
    // 0xe829a9d  mov rax,[rdi]
    // 0xe829aa0  mov rax,[rax+8]
    // 0xe829aa4  mov rcx,rdi
    // 0xe829aa7  call qword ptr [0xF99FFA0]  // sub_eea6040
    // 0xe829aad  mov rdx,[rbx+0x170]
    // 0xe829ab4  mov rcx,[rbx+0xF0]
    // loc_e829abb:
    // 0xe829abb  add rcx,r12
    // 0xe829abe  cmp r13d,2
    // 0xe829ac2  mov eax,0
    // 0xe829ac7  cmovne rcx,rax
    // 0xe829acb  add rdx,r12
    // 0xe829ace  mov [rbx+0x268],r12d
    // 0xe829ad5  mov [rbx+0x26C],r15d
    // 0xe829adc  movdqa xmm0,[rbx+0xC0]
    // 0xe829ae4  movdqa xmm1,[rbx+0xD0]
    // 0xe829aec  lea rax,[rbx+0x270]
    // 0xe829af3  movdqu [rax+0x10],xmm1
    // 0xe829af8  movdqu [rax],xmm0
    // 0xe829afc  mov [rbx+0x290],rdx
    // 0xe829b03  mov [rbx+0x298],rcx
    // 0xe829b0a  mov qword ptr [rbx+0x2A8],0
    // 0xe829b15  xor eax,eax
    // 0xe829b17  mov r13,[rbx+0xA8]
    // 0xe829b1e  jmp short 0xE829B2E
    {
        // placeholder for branch cluster 0xe8299dd..0xe829b1e
    }

    // 0xe829b20..0xe829bea: loc_e829b20..loc_e829bea sub_eec6ec0 call + sub_eea6040 call
    // loc_e829b20:
    // 0xe829b20  mov rdx,[rbx+0x290]
    // 0xe829b27  mov rcx,[rbx+0x298]
    // loc_e829b2e:
    // 0xe829b2e  add rcx,rax
    // 0xe829b31  add rdx,rax
    // 0xe829b34  mov [rbx+0x170],rdx
    // 0xe829b3b  mov rdx,[r13]
    // 0xe829b3f  mov r8,rsi
    // 0xe829b42  call 0xEEC6EC0
    // 0xe829b47  add [rbx+0x2A8],r14
    // 0xe829b4e  xchg ax,ax
    // 0xe829b50  mov rax,[rbx+0x90]
    // 0xe829b57  mov rcx,[rax+0x30]
    // 0xe829b5b  mov rax,[rcx]
    // 0xe829b5e  mov rax,[rax+0x128]
    // 0xe89b65  mov edx,2
    // 0xe829b6a  mov r8,[rbx+0x170]
    // 0xe829b71  call qword ptr [0xF99FFA0]  // sub_eea6040
    // 0xe829b77  nop
    // 0xe829b78  mov r8,[rbx+0x1B0]
    // 0xe829b7f  cmp byte ptr [r8+0x23],1
    // 0xe829b84  jne short 0xE829BEA
    // 0xe829b86  mov rdx,[rbx+0x1E8]
    // 0xe829b8d  shl edx,6
    // 0xe829b90  add rdx,[rbx+0x90A0]
    // 0xe829b97  mov rcx,[rbx+0xB0]
    // 0xe829b9e  mov rax,[rcx]
    // 0xe829ba1  mov rax,[rax+0x200]
    // 0xe829ba8  mov r10,[0xF99FFA0]  // sub_eea6040
    // 0xe829baf  mov r8,[rbx+0x318]
    // 0xe829bb6  mov [rsp+0x30],r8
    // 0xe829bbb  mov [rsp+0x28],rdx
    // 0xe829bc0  mov rdx,[rbx+0x1F0]
    // 0xe829bc7  mov [rsp+0x20],rdx
    // 0xe829bcc  mov rdx,[rbx+0x90]
    // 0xe829bd3  mov r8,[rbx+0x658]
    // 0xe829bda  mov r9,[rbx+0x660]
    // 0xe829be1  call r10
    // 0xe829be4  nop
    // 0xe829be5  jmp 0xE829C90
    {
        // placeholder for branch cluster 0xe829b20..0xe829bea
    }

    // 0xe829bea..0xe829c90: loc_e829bea..loc_e829c66 sub_eea6040 call paths
    // loc_e829bea:
    // 0xe829bea  movzx eax,word ptr [r8+0xC]
    // 0xe829bef  cmp rax,0xFFFF
    // 0xe829bfe  shl eax,7
    // 0xe829c01  add rax,[rbx+0x588]
    // 0xe829c08  movzx r8d,word ptr [r8+0x1E]
    // 0xe829c0d  cmp r8d,0xFFFF
    // 0xe829c14  jne short 0xE829C1E
    // 0xe829c16  mov r8d,[rax+0x60]
    // 0xe829c1a  shr r8d,5
    // loc_e829c1e:
    // 0xe829c1e  mov rcx,[rcx+0x30]
    // 0xe829c22  mov rdx,[rbx+0x1B0]
    // 0xe829c29  movzx r10d,word ptr [rdx+0x1C]
    // 0xe829c2e  shl r10d,5
    // 0xe829c32  mov r9,[rax]
    // 0xe829c35  mov rax,[0x12BB4910]
    // 0xe829c3c  mov rdx,[rax+0x19F40]
    // 0xe829c43  mov rax,[rcx]
    // 0xe829c46  mov rax,[rax+0x1D8]
    // 0xe829c4d  mov r11,[0xF99FFA0]  // sub_eea6040
    // 0xe829c54  movdqu [rsp+0x28],xmm9
    // 0xe829c5b  mov [rsp+0x20],r10
    // 0xe829c60  call r11
    // 0xe829c63  nop
    // 0xe829c64  jmp short 0xE829C90
    // loc_e829c66:
    // 0xe829c66  mov rcx,[rcx+0x30]
    // 0xe829c6a  mov r9d,[r8+0x18]
    // 0xe829c6e  mov edx,[r8+0x10]
    // 0xe829c72  mov r8d,[r8+0x14]
    // 0xe829c76  mov rax,[rcx]
    // 0xe829c79  mov rax,[rax+0x70]
    // 0xe829c7d  call qword ptr [0xF99FFA0]  // sub_eea6040
    // 0xe829c83  nop
    // 0xe829c84  nop [rax+rax]
    // loc_e829c90:
    // 0xe829c90  mov dil,1
    // 0xe829c93  xor ecx,ecx
    // 0xe829c95  mov rax,[rbx+0x160]
    // 0xe829c9c  mov [rbx+0x190],ax
    // 0xe829ca3  mov rsi,[rbx+0xB0]
    // 0xe829caa  jmp 0xE82D0CF
    {
        // placeholder for branch cluster 0xe829bea..0xe829c90
    }

    // 0xe829caf..0xe829d58: loc_e829caf..loc_e829d5e sub_eec6ed0 + vertex buffer setup
    // 0xe829caf  lea rdi,[rcx+r8]
    // 0xe829cb3  xor edx,edx
    // 0xe829cb5  call 0xEEC6ED0
    // 0xe829cba  mov rax,[rbx+0x98]
    // 0xe829cc1  mov [rax],rdi
    // 0xe829cc4  test sil,sil
    // 0xe829cc7  jne 0xE827E69
    // 0xe829ccd  jmp 0xE827E90
    // 0xe829cd2  movzx ecx,word ptr [rbx+rsi*4+0x696]
    // 0xe829cda  mov [rbx+0x690],cx
    // 0xe829ce1  cmp cx,0xFFFF
    // 0xe829ce5  jne 0xE822FC5
    // 0xe829ceb  mov [rbx+0x692],ax
    // 0xe829cf2  mov word ptr [rbx+rsi*4+0x694],0xFFFF
    // 0xe829cfc  movzx eax,word ptr [rbx+0x690]
    // 0xe829d03  mov [rbx+rsi*4+0x696],ax
    // 0xe829d0b  cmp rax,0xFFFF
    // 0xe829d11  je 0xE82A39B
    // 0xe829d17  movzx ecx,word ptr [rbx+rax*4+0x694]
    // 0xe829d1f  cmp rcx,0xFFFF
    // 0xe829d26  je short 0xE829D30
    // 0xe829d28  mov [rbx+rcx*4+0x696],si
    // loc_e829d30:
    // 0xe829d30  mov [rbx+rsi*4+0x694],cx
    // 0xe829d38  mov [rbx+rax*4+0x694],si
    // 0xe829d40  cmp word ptr [rbx+rsi*4+0x694],0xFFFF
    // 0xe829d49  je 0xE82A39B
    // 0xe829d4f  cmp word ptr [rbx+rsi*4+0x696],0xFFFF
    // 0xe829d58  je 0xE82A3B1
    {
        // placeholder for branch cluster 0xe829caf..0xe829d58
    }

    // 0xe829f94..0xe82a0fe: loc_e829f94..loc_e82a0f4 sub_eea6040 calls (viewport/scissor)
    // 0xe829f94  mov [rbx+0x520],r8w
    // 0xe829f9c  cmp r8w,0xFFFF
    // 0xe829fa1  mov rsi,[rbx+0xB0]
    // 0xe829fa8  je 0xE82A08A
    // 0xe829fae  movzx r8d,r8w
    // 0xe829fb2  mov r11,[rbx+0x168]
    // 0xe829fb9  movzx eax,word ptr [r11+r8*8+0xD457D0]
    // 0xe829fc2  mov r9d,eax
    // 0xe829fc5  mov rcx,[rbx+0x320]
    // 0xe829fcc  cmp cx,ax
    // 0xe829fcf  cmova eax,ecx
    // 0xe829fd2  movzx ecx,word ptr [r11+r8*8+0xD457D2]
    // 0xe829fdb  mov r10d,ecx
    // 0xe829fde  mov rdx,[rbx+0x398]
    // 0xe829fe5  cmp dx,cx
    // 0xe829fe8  cmova ecx,edx
    // 0xe829feb  movzx edx,word ptr [r11+r8*8+0xD457D4]
    // 0xe829ff4  add dx,r9w
    // 0xe829ff8  mov r9,[rbx+0x2E8]
    // 0xe829fff  cmp r9w,dx
    // 0xe82a003  cmovb edx,r9d
    // 0xe82a007  movzx r8d,word ptr [r11+r8*8+0xD457D6]
    // 0xe82a010  add r8w,r10w
    // 0xe82a014  mov r9,[rbx+0x2E0]
    // 0xe82a01b  cmp r9w,r8w
    // 0xe82a01f  cmovb r8d,r9d
    // 0xe82a023  mov r9b,1
    // 0xe82a026  mov [rbx+0x1AC],r9d
    // 0xe82a02d  cmp dx,ax
    // 0xe82a030  jbe 0xE82D0CB
    // 0xe82a036  cmp r8w,cx
    // 0xe82a03a  jbe 0xE82D0CB
    // 0xe82a040  movzx eax,ax
    // 0xe82a043  movd xmm0,eax
    // 0xe82a047  pinsrw xmm0,ecx,2
    // 0xe82a04c  pinsrw xmm0,edx,4
    // 0xe82a051  pinsrw xmm0,r8d,6
    // 0xe82a057  movdqa [rbx+0x3B0],xmm0
    // 0xe82a05f  mov rcx,[rdi+0x30]
    // 0xe82a063  mov rax,[rcx]
    // 0xe82a066  mov rax,[rax+0xB0]
    // 0xe82a06d  mov edx,1
    // 0xe82a072  lea r8,[rbx+0x3B0]
    // 0xe82a079  call qword ptr [0xF99FFA0]  // sub_eea6040
    // 0xe82a07f  nop
    // 0xe82a080  mov al,1
    // 0xe82a082  mov [rbx+0x1AC],eax
    // 0xe82a088  jmp short 0xE82A0FE
    // loc_e82a08a:
    // 0xe82a08a  cmp qword ptr [rbx+0x638],0
    // 0xe82a092  sete al
    // 0xe82a095  mov ecx,[rbx+0x1AC]
    // 0xe82a09b  xor cl,1
    // 0xe82a09e  test al,cl
    // 0xe82a0a0  jne short 0xE82A0F4
    // 0xe82a0a2  mov eax,[rbx+0x5A4]
    // 0xe82a0a8  mov [rbx+0x3B0],eax
    // 0xe82a0ae  mov rax,[rbx+0x630]
    // 0xe82a0b5  mov [rbx+0x3B4],eax
    // 0xe82a0bb  mov eax,[rbx+0x5A0]
    // 0xe82a0c1  mov [rbx+0x3B8],eax
    // 0xe82a0c7  mov eax,[rbx+0x59C]
    // 0xe82a0cd  mov [rbx+0x3BC],eax
    // 0xe82a0d3  mov rcx,[rdi+0x30]
    // 0xe82a0d7  mov rax,[rcx]
    // 0xe82a0da  mov rax,[rax+0xB0]
    // 0xe82a0e1  mov edx,1
    // 0xe82a0e6  lea r8,[rbx+0x3B0]
    // 0xe82a0ed  call qword ptr [0xF99FFA0]  // sub_eea6040
    // 0xe82a0f3  nop
    // loc_e82a0f4:
    // 0xe82a0f4  mov dword ptr [rbx+0x1AC],0
    {
        // placeholder for branch cluster 0xe829f94..0xe82a0f4
    }

    // 0xe82a527..0xe82a595: loc_e82a527..loc_e82a590 sub_eec6ed0 + sub_47e8f0 (vertex buffer bounds)
    // 0xe82a527  movq xmm0,[rbx+0x90A8]
    // 0xe82a52f  punpcklwd xmm0,xmm9
    // 0xe82a534  cvtdq2ps xmm8,xmm0
    // 0xe82a538  mov edi,[r14+r15*8+0x10]
    // 0xe82a53d  test al,0x10
    // 0xe82a53f  jne 0xE82B840
    // 0xe82a545  lea rdx,[rdi+0x10]
    // 0xe82a549  mov rax,[rbx+0x98]
    // 0xe82a550  mov rcx,[rax]
    // 0xe82a553  mov rax,[r13]
    // 0xe82a557  mov r9,rcx
    // 0xe82a55a  sub r9,rax
    // 0xe82a55d  mov r8,rdx
    // 0xe82a560  sub r8,r9
    // 0xe82a563  jbe 0xE82BD8E
    // 0xe82a569  mov r9,[rbx+0xA0]
    // 0xe82a570  mov r9,[r9+0x38]
    // 0xe82a574  sub r9,rax
    // 0xe82a577  cmp rdx,r9
    // 0xe82a57a  jbe 0xE82BD67
    // 0xe82a580  mov rcx,r13
    // 0xe82a583  lea r8,[rbx+0x3B0]
    // 0xe82a58a  call 0x47E8F0
    // 0xe82a58f  nop
    // 0xe82a590  jmp 0xE82BD7C
    {
        // placeholder for branch cluster 0xe82a527..0xe82a595
    }

    // 0xe82a595..0xe82a6a6: loc_e82a595..loc_e82a6a6 matrix mul (4x4) into [rbx+0x3B0..0x3E0]
    // 0xe82a595  mov ecx,[r12+0x3C]
    // 0xe82a59a  shl rcx,6
    // 0xe82a59e  mov rdx,[rbx+0x2F8]
    // 0xe82a5a5  movaps xmm4,[rdx+rcx]
    // 0xe82a5a9  movaps xmm5,xmm4
    // 0xe82a5ac  shufps xmm5,xmm4,0
    // 0xe82a5b0  movaps xmm6,xmm4
    // 0xe82a5b3  shufps xmm6,xmm4,0x55
    // 0xe82a5b7  movaps xmm7,xmm4
    // 0xe82a5ba  shufps xmm7,xmm4,0xAA
    // 0xe82a5be  shufps xmm4,xmm4,0xFF
    // 0xe82a5c2  mov r8,[rbx+0x2F0]
    // 0xe82a5c9  movaps xmm3,[r8]
    // 0xe82a5cd  movaps xmm2,[r8+0x10]
    // 0xe82a5d2  movaps xmm1,[r8+0x20]
    // 0xe82a5d7  movaps xmm0,[r8+0x30]
    // 0xe82a5dc  mulps xmm5,xmm3
    // 0xe82a5df  mulps xmm6,xmm2
    // 0xe82a5e2  mulps xmm7,xmm1
    // 0xe82a5e5  addps xmm7,xmm5
    // 0xe82a5e8  mulps xmm4,xmm0
    // 0xe82a5eb  addps xmm4,xmm6
    // 0xe82a5ee  addps xmm4,xmm7
    // 0xe82a5f1  movaps [rbx+0x3B0],xmm4
    // 0xe82a5f8  movaps xmm4,[rdx+rcx+0x10]
    // 0xe82a5fd  movaps xmm5,xmm4
    // 0xe82a600  shufps xmm5,xmm4,0
    // 0xe82a604  movaps xmm6,xmm4
    // 0xe82a607  shufps xmm6,xmm4,0x55
    // 0xe82a60b  movaps xmm7,xmm4
    // 0xe82a60e  shufps xmm7,xmm4,0xAA
    // 0xe82a612  shufps xmm4,xmm4,0xFF
    // 0xe82a616  mulps xmm5,xmm3
    // 0xe82a619  mulps xmm6,xmm2
    // 0xe82a61c  mulps xmm7,xmm1
    // 0xe82a61f  addps xmm7,xmm5
    // 0xe82a622  mulps xmm4,xmm0
    // 0xe82a625  addps xmm4,xmm6
    // 0xe82a628  addps xmm4,xmm7
    // 0xe82a62b  movaps [rbx+0x3C0],xmm4
    // 0xe82a632  movaps xmm4,[rdx+rcx+0x20]
    // 0xe82a637  movaps xmm5,xmm4
    // 0xe82a63a  shufps xmm5,xmm4,0
    // 0xe82a63e  movaps xmm6,xmm4
    // 0xe82a641  shufps xmm6,xmm4,0x55
    // 0xe82a645  movaps xmm7,xmm4
    // 0xe82a648  shufps xmm7,xmm4,0xAA
    // 0xe82a64c  shufps xmm4,xmm4,0xFF
    // 0xe82a650  mulps xmm5,xmm3
    // 0xe82a653  mulps xmm6,xmm2
    // 0xe82a656  mulps xmm7,xmm1
    // 0xe82a659  addps xmm7,xmm5
    // 0xe82a65c  mulps xmm4,xmm0
    // 0xe82a65f  addps xmm4,xmm6
    // 0xe82a662  addps xmm4,xmm7
    // 0xe82a665  movaps [rbx+0x3D0],xmm4
    // 0xe82a66c  movaps xmm4,[rdx+rcx+0x30]
    // 0xe82a671  movaps xmm5,xmm4
    // 0xe82a674  shufps xmm5,xmm4,0
    // 0xe82a678  movaps xmm6,xmm4
    // 0xe82a67b  shufps xmm6,xmm4,0x55
    // 0xe82a67f  movaps xmm7,xmm4
    // 0xe82a682  shufps xmm7,xmm4,0xAA
    // 0xe82a686  shufps xmm4,xmm4,0xFF
    // 0xe82a68a  mulps xmm5,xmm3
    // 0xe82a68d  mulps xmm6,xmm2
    // 0xe82a690  mulps xmm7,xmm1
    // 0xe82a693  addps xmm7,xmm5
    // 0xe82a696  mulps xmm4,xmm0
    // 0xe82a699  addps xmm4,xmm6
    // 0xe82a69c  addps xmm4,xmm7
    // 0xe82a69f  movaps [rbx+0x3E0],xmm4
    {
        // placeholder for branch cluster 0xe82a595..0xe82a6a6
    }

    // 0xe82a6a6..0xe82a71a: loc_e82a6a6..loc_e82a715 sub_47e8f0 (draw call setup)
    // 0xe82a6a6  mov ecx,[r14+r15*8+0x14]
    // 0xe82a6ab  cmp cx,4
    // 0xe82a6af  mov edx,4
    // 0xe82a6b4  cmovae ecx,edx
    // 0xe82a6b7  mov r12d,[r14+r15*8+0x10]
    // 0xe82a6bc  shl ecx,4
    // 0xe82a6bf  movzx edi,cx
    // 0xe82a6c2  test al,0x10
    // 0xe82a6c4  jne 0xE82B5C1
    // 0xe82a6ca  lea rdx,[rdi+r12]
    // 0xe82a6ce  mov rax,[rbx+0x98]
    // 0xe82a6d5  mov rax,[rax]
    // 0xe82a6d8  mov rcx,[r13]
    // 0xe82a6dc  mov r9,rax
    // 0xe82a6df  sub r9,rcx
    // 0xe82a6e2  mov r8,rdx
    // 0xe82a6e5  sub r8,r9
    // 0xe82a6e8  jbe 0xE82BAD8
    // 0xe82a6ee  mov r9,[rbx+0xA0]
    // 0xe82a6f5  mov r9,[r9+0x38]
    // 0xe82a6f9  sub r9,rcx
    // 0xe82a6fc  cmp rdx,r9
    // 0xe82a6ff  jbe 0xE82BAB5
    // 0xe82a705  mov rcx,r13
    // 0xe82a708  lea r8,[rbx+0xC0]
    // 0xe82a70f  call 0x47E8F0
    // 0xe82a714  nop
    // 0xe82a715  jmp 0xE82BACD
    {
        // placeholder for branch cluster 0xe82a6a6..0xe82a71a
    }

    // 0xe82a71a..0xe82a7eb: loc_e82a71a..loc_e82a7e6 sub_47e8f0 (draw call setup)
    // 0xe82a71a  mov ecx,[r14+r15*8+0x14]
    // 0xe82a71f  cmp cx,4
    // 0xe82a723  mov edx,4
    // 0xe82a728  cmovae ecx,edx
    // 0xe82a72b  mov r12d,[r14+r15*8+0x10]
    // 0xe82a730  shl ecx,4
    // 0xe82a733  movzx edi,cx
    // 0xe82a736  test al,0x10
    // 0xe82a738  jne 0xE82B61A
    // 0xe82a73e  lea rdx,[rdi+r12]
    // 0xe82a742  mov rax,[rbx+0x98]
    // 0xe82a749  mov rax,[rax]
    // 0xe82a74c  mov rcx,[r13]
    // 0xe82a750  mov r9,rax
    // 0xe82a753  sub r9,rcx
    // 0xe82a756  mov r8,rdx
    // 0xe82a759  sub r8,r9
    // 0xe82a75c  jbe 0xE82BB0A
    // 0xe82a762  mov r9,[rbx+0xA0]
    // 0xe82a769  mov r9,[r9+0x38]
    // 0xe82a76d  sub r9,rcx
    // 0xe82a770  cmp rdx,r9
    // 0xe82a773  jbe 0xE82BAE7
    // 0xe82a779  mov rcx,r13
    // 0xe82a77c  lea r8,[rbx+0x3B0]
    // 0xe82a783  call 0x47E8F0
    // 0xe82a788  nop
    // 0xe82a789  jmp 0xE82BAFF
    // 0xe82a78e  mov edi,[r14+r15*8+0x10]
    // 0xe82a793  test al,0x10
    // 0xe82a795  jne 0xE82B673
    // 0xe82a79b  lea rdx,[rdi+0x10]
    // 0xe82a79f  mov rax,[rbx+0x98]
    // 0xe82a7a6  mov rcx,[rax]
    // 0xe82a7a9  mov r12,[r13]
    // 0xe82a7ad  mov rax,rcx
    // 0xe82a7b0  sub rax,r12
    // 0xe82a7b3  mov r8,rdx
    // 0xe82a7b6  sub r8,rax
    // 0xe82a7b9  jbe 0xE82BB79
    // 0xe82a7bf  mov rax,[rbx+0xA0]
    // 0xe82a7c6  mov rax,[rax+0x38]
    // 0xe82a7ca  sub rax,r12
    // 0xe82a7cd  cmp rdx,rax
    // 0xe82a7d0  jbe 0xE82BB59
    // 0xe82a7d6  mov rcx,r13
    // 0xe82a7d9  lea r8,[rbx+0x3B0]
    // 0xe82a7e0  call 0x47E8F0
    // 0xe82a7e5  nop
    // 0xe82a7e6  jmp 0xE82BB6E
    {
        // placeholder for branch cluster 0xe82a71a..0xe82a7eb
    }

    // 0xe82a7eb..0xe82a912: loc_e82a7eb..loc_e82a912 sub_47e8f0 + exit condition
    // 0xe82a7eb  movzx ecx,word ptr [r14+r15*8+0x14]
    // 0xe82a7f1  movzx edi,word ptr [r12+0x5E]
    // 0xe82a7f7  shl edi,2
    // 0xe82a7fa  cmp edi,ecx
    // 0xe82a7fc  cmovae edi,ecx
    // 0xe82a7ff  mov r12d,[r12+0x3C]
    // 0xe82a804  mov r13d,[r14+r15*8+0x10]
    // 0xe82a809  shl edi,4
    // 0xe82a80c  test al,0x10
    // 0xe82a80e  jne 0xE82B6CE
    // 0xe82a814  lea rdx,[rdi+r13]
    // 0xe82a818  mov rax,[rbx+0x98]
    // 0xe82a81f  mov rax,[rax]
    // 0xe82a822  mov rcx,[rbx+0xA8]
    // 0xe82a829  mov rcx,[rcx]
    // 0xe82a82c  mov r9,rax
    // 0xe82a82f  sub r9,rcx
    // 0xe82a832  mov r8,rdx
    // 0xe82a835  sub r8,r9
    // 0xe82a838  jbe 0xE82BBDC
    // 0xe82a83e  mov r9,[rbx+0xA0]
    // 0xe82a845  mov r9,[r9+0x38]
    // 0xe82a849  sub r9,rcx
    // 0xe82a84c  cmp rdx,r9
    // 0xe82a84f  jbe 0xE82BBBA
    // 0xe82a855  mov rcx,[rbx+0xA8]
    // 0xe82a85c  lea r8,[rbx+0x3B0]
    // 0xe82a863  call 0x47E8F0
    // 0xe82a868  nop
    // 0xe82a869  jmp 0xE82BBD2
    // 0xe82a86e  mov ecx,[r14+r15*8+0x14]
    // 0xe82a873  cmp cx,4
    // 0xe82a877  mov edx,4
    // 0xe82a87c  cmovae ecx,edx
    // 0xe82a87f  mov rdi,[rbx+0x1E8]
    // 0xe82a886  shl edi,6
    // 0xe82a889  add rdi,[rbx+0x90A0]
    // 0xe82a890  mov r13d,[r14+r15*8+0x10]
    // 0xe82a895  shl ecx,4
    // 0xe82a898  movzx r12d,cx
    // 0xe82a89c  test al,0x10
    // 0xe82a89e  jne 0xE82B72E
    // 0xe82a8a4  lea rdx,[r12+r13]
    // 0xe82a8a8  mov rax,[rbx+0x98]
    // 0xe82a8af  mov rax,[rax]
    // 0xe82a8b2  mov rcx,[rbx+0xA8]
    // 0xe82a8b9  mov rcx,[rcx]
    // 0xe82a8bc  mov r9,rax
    // 0xe82a8bf  sub r9,rcx
    // 0xe82a8c2  mov r8,rdx
    // 0xe82a8c5  sub r8,r9
    // 0xe82a8c8  jbe 0xE82BC4B
    // 0xe82a8ce  mov r9,[rbx+0xA0]
    // 0xe82a8d5  mov r9,[r9+0x38]
    // 0xe82a8d9  sub r9,rcx
    // 0xe82a8dc  cmp rdx,r9
    // 0xe82a8df  jbe 0xE82BC29
    // 0xe82a8e5  mov rcx,[rbx+0xA8]
    // 0xe82a8ec  lea r8,[rbx+0x3B0]
    // 0xe82a8f3  call 0x47E8F0
    // 0xe82a8f8  nop
    // 0xe82a8f9  jmp 0xE82BC41
    // 0xe82a8fe  movzx ecx,word ptr [rbx+0x10E]
    // 0xe82a905  cmp cx,[rbx+0xE174]
    // 0xe82a90c  je 0xE82ABB8
    // 0xe82a912  movzx ecx,word ptr [rbx+0x10E]
    {
        // placeholder for branch cluster 0xe82a7eb..0xe82a912
    }

    s.r15 = r15; s.rsi = rsi; s.rdi = rdi;

} } // namespace