// LIFT 0xe83b8c0 size 0x121 1.26.62.01 sub_e83b8c0
#include "sub_e83b8c0.h"
static_assert(sizeof(void*) == 8, "ptr");

#if 0
0xe83b8c0  mov rax,[rcx+0x50]
0xe83b8c4  mov r9,[rcx+0x58]
0xe83b8c8  sub rax,r9
0xe83b8cb  add rax,[rcx+0x48]
0xe83b8cf  add rax,[rcx+0x68]
0xe83b8d3  mov r9,[rcx+0x70]
0xe83b8d7  sub rax,r9
0xe83b8da  add rax,[rcx+0x60]
0xe83b8de  cmp r8,rax
0xe83b8e1  ja short 0xE83B913
0xe83b8e3  lock inc word ptr [rcx+0x80]
0xe83b8eb  mov rax,[rcx+0x50]
0xe83b8ef  mov r9,[rcx+0x58]
0xe83b8f3  sub rax,r9
0xe83b8f6  add rax,[rcx+0x48]
0xe83b8fa  cmp r8,rax
0xe83b8fd  jbe short 0xE83B920
0xe83b8ff  mov rax,[rcx+0x68]
0xe83b903  mov r9,[rcx+0x70]
0xe83b907  sub rax,r9
0xe83b90a  add rax,[rcx+0x60]
0xe83b90e  cmp r8,rax
0xe83b911  jbe short 0xE83B950
0xe83b913  xor eax,eax
0xe83b915  jmp 0xE83B9DA
0xe83b920  mov r9,[rcx+0x58]
0xe83b924  lea r10,[r9+0xFF]
0xe83b92b  and r10,0xFFFFFFFFFFFFFF00
0xe83b932  lea r11,[r10+r8]
0xe83b936  mov rax,[rcx+0x50]
0xe83b93a  add rax,[rcx+0x48]
0xe83b93e  cmp r11,rax
0xe83b941  ja short 0xE83B8FF
0xe83b943  mov rax,r9
0xe83b946  lock cmpxchg [rcx+0x58],r11
0xe83b94c  jne short 0xE83B920
0xe83b94e  jmp short 0xE83B97E
0xe83b950  mov r9,[rcx+0x70]
0xe83b954  lea r10,[r9+0xFF]
0xe83b95b  and r10,0xFFFFFFFFFFFFFF00
0xe83b962  lea r11,[r10+r8]
0xe83b966  mov rax,[rcx+0x68]
0xe83b96a  add rax,[rcx+0x60]
0xe83b96e  cmp r11,rax
0xe83b971  ja short 0xE83B913
0xe83b973  mov rax,r9
0xe83b976  lock cmpxchg [rcx+0x70],r11
0xe83b97c  jne short 0xE83B950
0xe83b97e  mov rax,r10
0xe83b981  sub rax,r9
0xe83b984  lea r9,[rax+r8]
0xe83b988  lock add [rcx+0x78],r9
0xe83b98d  lock add [rcx+0x40],r9
0xe83b992  mov r11,[rcx+8]
0xe83b996  mov r9,[rcx+0x88]
0xe83b99d  mov [rcx+0x90],r9
0xe83b9a4  mov byte ptr [rcx+0x98],1
0xe83b9ab  test r11,r11
0xe83b9ae  je short 0xE83B9BB
0xe83b9b0  lock inc dword ptr [r11+8]
0xe83b9b5  mov r11,[rcx+8]
0xe83b9b9  jmp short 0xE83B9BE
0xe83b9bb  xor r11d,r11d
0xe83b9be  mov rcx,[rcx]
0xe83b9c1  mov [rdx],rcx
0xe83b9c4  mov [rdx+8],r11
0xe83b9c8  mov [rdx+0x10],r10
0xe83b9cc  mov [rdx+0x18],r8
0xe83b9d0  mov [rdx+0x20],rax
0xe83b9d4  mov [rdx+0x28],r9
0xe83b9d8  mov al,1
0xe83b9da  mov [rdx+0x30],al
0xe83b9dd  mov rax,rdx
0xe83b9e0  ret
#endif

extern "C" void* sub_e83b8c0(void* rcx, void* rdx, unsigned long long r8) {
    // 0xe83b8c0..0xe83b8e1
    unsigned long long rax = *(unsigned long long*)((char*)rcx + 0x50);
    unsigned long long r9 = *(unsigned long long*)((char*)rcx + 0x58);
    rax -= r9;
    rax += *(unsigned long long*)((char*)rcx + 0x48);
    rax += *(unsigned long long*)((char*)rcx + 0x68);
    r9 = *(unsigned long long*)((char*)rcx + 0x70);
    rax -= r9;
    rax += *(unsigned long long*)((char*)rcx + 0x60);
    if (r8 > rax) { // ja
        // 0xe83b913..0xe83b915
        // xor eax,eax ; jmp
        unsigned char al = 0;
        *(unsigned char*)((char*)rdx + 0x30) = al;
        return rdx;
    }
    // 0xe83b8e3
    // lock inc word ptr [rcx+0x80]
    __atomic_fetch_add((unsigned short*)((char*)rcx + 0x80), 1, __ATOMIC_SEQ_CST);
    // 0xe83b8eb..0xe83b8fd
    rax = *(unsigned long long*)((char*)rcx + 0x50);
    r9 = *(unsigned long long*)((char*)rcx + 0x58);
    rax -= r9;
    rax += *(unsigned long long*)((char*)rcx + 0x48);
    if (r8 <= rax) { // jbe
        // path A: 0xe83b920..
        unsigned long long r10, r11;
        for (;;) {
            r9 = *(unsigned long long*)((char*)rcx + 0x58);
            r10 = r9 + 0xFF;
            r10 &= ~0xFFULL;
            r11 = r10 + r8;
            rax = *(unsigned long long*)((char*)rcx + 0x50);
            rax += *(unsigned long long*)((char*)rcx + 0x48);
            if (r11 > rax) { // ja -> 0xe83b8ff
                // 0xe83b8ff..0xe83b911
                rax = *(unsigned long long*)((char*)rcx + 0x68);
                r9 = *(unsigned long long*)((char*)rcx + 0x70);
                rax -= r9;
                rax += *(unsigned long long*)((char*)rcx + 0x60);
                if (r8 <= rax) { // jbe -> 0xe83b950
                    // path B
                    for (;;) {
                        r9 = *(unsigned long long*)((char*)rcx + 0x70);
                        r10 = r9 + 0xFF;
                        r10 &= ~0xFFULL;
                        r11 = r10 + r8;
                        rax = *(unsigned long long*)((char*)rcx + 0x68);
                        rax += *(unsigned long long*)((char*)rcx + 0x60);
                        if (r11 > rax) { // ja -> 0xe83b913
                            unsigned char al2 = 0;
                            *(unsigned char*)((char*)rdx + 0x30) = al2;
                            return rdx;
                        }
                        rax = r9;
                        // lock cmpxchg [rcx+0x70], r11
                        unsigned long long expected = r9;
                        if (!__atomic_compare_exchange_n((unsigned long long*)((char*)rcx + 0x70), &expected, r11, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
                            continue; // jne
                        }
                        break;
                    }
                    break;
                } else {
                    unsigned char al2 = 0;
                    *(unsigned char*)((char*)rdx + 0x30) = al2;
                    return rdx;
                }
            }
            rax = r9; // mov rax,r9
            // lock cmpxchg [rcx+0x58], r11
            unsigned long long expected2 = r9;
            if (!__atomic_compare_exchange_n((unsigned long long*)((char*)rcx + 0x58), &expected2, r11, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
                continue; // jne -> 0xe83b920
            }
            break;
        }
    } else {
        // 0xe83b8ff path (r8 > rax after first check)
        goto second_check;
    }
    // fall through to 0xe83b97e normally; but if we took second path need handle. Use label.
second_check:
    // This label handles the case where first jbe failed; recompute like 0xe83b8ff
    {
        rax = *(unsigned long long*)((char*)rcx + 0x68);
        r9 = *(unsigned long long*)((char*)rcx + 0x70);
        rax -= r9;
        rax += *(unsigned long long*)((char*)rcx + 0x60);
        if (r8 <= rax) { // jbe -> 0xe83b950
            for (;;) {
                unsigned long long r9b = *(unsigned long long*)((char*)rcx + 0x70);
                unsigned long long r10b = r9b + 0xFF; r10b &= ~0xFFULL;
                unsigned long long r11b = r10b + r8;
                unsigned long long raxb = *(unsigned long long*)((char*)rcx + 0x68);
                raxb += *(unsigned long long*)((char*)rcx + 0x60);
                if (r11b > raxb) {
                    unsigned char al2 = 0;
                    *(unsigned char*)((char*)rdx + 0x30) = al2;
                    return rdx;
                }
                unsigned long long exp = r9b;
                if (!__atomic_compare_exchange_n((unsigned long long*)((char*)rcx + 0x70), &exp, r11b, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
                    continue;
                }
                r10 = r10b; r9 = r9b;
                break;
            }
        } else {
            unsigned char al2 = 0;
            *(unsigned char*)((char*)rdx + 0x30) = al2;
            return rdx;
        }
    }

    // 0xe83b97e common tail
    // rax = r10 - r9 (saved); r9 = rax + r8
    // Need r10, r9 from path. For path A, after loop r10 and r9 set. For path B too.
    // Recompute not safe; instead track via variables already in scope: r10, r9.
    unsigned long long r10tail = r10;
    unsigned long long r9tail = r9;
    unsigned long long raxtail = r10tail - r9tail;
    unsigned long long r9final = raxtail + r8;
    __atomic_fetch_add((unsigned long long*)((char*)rcx + 0x78), r9final, __ATOMIC_SEQ_CST);
    __atomic_fetch_add((unsigned long long*)((char*)rcx + 0x40), r9final, __ATOMIC_SEQ_CST);
    void* r11p = *(void**)((char*)rcx + 0x8);
    unsigned long long r9v = *(unsigned long long*)((char*)rcx + 0x88);
    *(unsigned long long*)((char*)rcx + 0x90) = r9v;
    *(unsigned char*)((char*)rcx + 0x98) = 1;
    if (r11p) {
        __atomic_fetch_add((unsigned int*)((char*)r11p + 0x8), 1, __ATOMIC_SEQ_CST);
        r11p = *(void**)((char*)rcx + 0x8);
    } else {
        r11p = nullptr;
    }
    void* rcx0 = *(void**)rcx;
    *(void**)rdx = rcx0;
    *(void**)((char*)rdx + 0x8) = r11p;
    *(unsigned long long*)((char*)rdx + 0x10) = r10tail;
    *(unsigned long long*)((char*)rdx + 0x18) = r8;
    *(unsigned long long*)((char*)rdx + 0x20) = raxtail;
    *(unsigned long long*)((char*)rdx + 0x28) = r9v;
    unsigned char al = 1;
    *(unsigned char*)((char*)rdx + 0x30) = al;
    return rdx;
}

// LIFT_FN registry entry
// native::registry::register_fn("sub_e83b8c0", 0xe83b8c0, &sub_e83b8c0);
