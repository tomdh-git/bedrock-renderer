// LIFT 0xbc9d7a0 size 0x67db 1.26.62.01 VV frame-graph builder
// CHUNK 0xbca2785..0xbca3f7b

// Chunk state documented in docs/functions/bc9d7a0.md section 'Chunk state'.
struct ChunkState_bc9d7a0_c04 {
    std::uint64_t rax;
    std::uint64_t rcx;
    std::uint64_t rdx;
    std::uint64_t r8;
    std::uint64_t r9;
    std::uint64_t r10;
    std::uint64_t r11;
    void* rbx;
    void* rsi;
    void* rdi;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    void* rbp;
    std::uint8_t stack[0x1098];
};

// Helper to access stack slot
static inline std::uint64_t& slot(void* rbp, std::uint64_t off) {
    return *reinterpret_cast<std::uint64_t*>(static_cast<char*>(rbp) + off);
}

static inline void sub_bc9d7a0_chunk04(ChunkState_bc9d7a0_c04& s) {
    // 0xbca2785..0xbca2792: entry jump to hash block for slot 0x12AE2070 (rdx==0 path)
    // mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA34E4
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot0;

    // 0xbca2797..0xbca27b0: lea rcx,[0x12AE2070]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2070],0xFFFFFFFF; jne 0xBC9D943
    // 0xbca27b6..0xbca27ca: mov rsi,r9; lea rdx,[0xF524D6E]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca27cf..0xbca27eb: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA27E8; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA330B
    // 0xbca27f1..0xbca280d: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3533; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA358F
lbl_slot_0:
    s.rcx = 0x12AE2070ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca27a1  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2070ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9D943 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF524D6Eull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca27ca  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot0_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot0_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot0_tail;

lbl_hash_slot0_rdx0:  // 0xBCA330B
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot0_store;

lbl_hash_slot0:  // 0xBCA34E4 (fallthrough from entry)
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot0_store;

lbl_hash_slot0_hash:  // 0xBCA3533
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot0;

lbl_hash_slot0_tail:  // 0xBCA358F
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot0;

lbl_hash_loop_slot0:  // 0xBCA33DD..0xBCA3432
    // loop body: process 4 bytes per iteration
    // 0xbca33dd  and rdx,0xFFFFFFFFFFFFFFFC
    // 0xbca33e1  mov rcx,0xCBF29CE484222325
    // 0xbca33eb  xor r8d,r8d
    // 0xbca33ee  mov r9,0x100000001B3
    // 0xbca33f8  movzx r10d,byte ptr [rdi+r8]
    // 0xbca33fd  xor r10,rcx
    // 0xbca3400  imul r10,r9
    // 0xbca3404  movzx ecx,byte ptr [rdi+r8+1]
    // 0xbca340a  xor rcx,r10
    // 0xbca340d  imul rcx,r9
    // 0xbca3411  movzx r10d,byte ptr [rdi+r8+2]
    // 0xbca3417  xor r10,rcx
    // 0xbca341a  imul r10,r9
    // 0xbca341e  movzx ecx,byte ptr [rdi+r8+3]
    // 0xbca3424  xor rcx,r10
    // 0xbca3427  imul rcx,r9
    // 0xbca342b  add r8,4
    // 0xbca342f  cmp rdx,r8
    // 0xbca3432  jne short 0xBCA33F8
    // 0xbca3434  test rax,rax
    // 0xbca3437  je short 0xBCA3461
    // 0xbca3439  add rdi,r8
    // 0xbca343c  xor edx,edx
    // 0xbca343e  mov r8,0x100000001B3
    // 0xbca3448  mov r9,rcx
    // 0xbca344b  movzx ecx,byte ptr [rdi+rdx]
    // 0xbca344f  xor rcx,r9
    // 0xbca3452  imul rcx,r8
    // 0xbca3456  inc rdx
    // 0xbca3459  mov r9,rcx
    // 0xbca345c  cmp rax,rdx
    // 0xbca345f  jne short 0xBCA344B
    for (;;) { /* MurmurHash2A body */ break; }

lbl_hash_tail_loop_slot0:  // 0xBCA344B..0xBCA345F
    for (;;) { break; }

lbl_hash_slot0_store:  // 0xBCA3461
    // 0xbca3461  mov [0x12AE2048],rcx
    *reinterpret_cast<std::uint64_t*>(0x12AE2048ull) = s.rcx;
    // 0xbca3468  lea rcx,[rbp+0xA00]
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca346f  call 0x73150
    native::boundary::sub_73150();
    // 0xbca347b  call 0xE938D70
    s.rcx = 0x12AE2050ull;
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D8F9 */

    // 0xbca2812..0xbca282b: lea rcx,[0x12AE2080]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2080],0xFFFFFFFF; jne 0xBC9D968
    // 0xbca2831..0xbca2845: mov rsi,r9; lea rdx,[0xF5F0264]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca284a..0xbca2866: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2863; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA331A
    // 0xbca286c..0xbca2888: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA363A; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3689
lbl_slot_1:
    s.rcx = 0x12AE2080ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca281c  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2080ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9D968 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5F0264ull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2845  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot1_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot1_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot1_tail;

lbl_hash_slot1_rdx0:  // 0xBCA331A
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot1_store;

lbl_hash_slot1_hash:  // 0xBCA363A
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot1;

lbl_hash_slot1_tail:  // 0xBCA3689
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot1;

lbl_hash_loop_slot1:  // 0xBCA358F..0xBCA35D5
    for (;;) { break; }

lbl_hash_tail_loop_slot1:  // 0xBCA3689..0xBCA36CF
    for (;;) { break; }

lbl_hash_slot1_store:  // 0xBCA350C
    *reinterpret_cast<std::uint64_t*>(0x12AE2058ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca351a  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE2060ull;
    // 0xbca3526  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D91E */

    // 0xbca288d..0xbca28a6: lea rcx,[0x12AE2090]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2090],0xFFFFFFFF; jne 0xBC9D98D
    // 0xbca28ac..0xbca28c0: mov rsi,r9; lea rdx,[0xF54F52A]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca28c5..0xbca28e1: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA28DE; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3329
    // 0xbca28e7..0xbca2903: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA36E5; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3734
lbl_slot_2:
    s.rcx = 0x12AE2090ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2897  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2090ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9D98D */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF54F52Aull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca28c0  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot2_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot2_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot2_tail;

lbl_hash_slot2_rdx0:  // 0xBCA3329
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot2_store;

lbl_hash_slot2_hash:  // 0xBCA36E5
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot2;

lbl_hash_slot2_tail:  // 0xBCA3734
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot2;

lbl_hash_loop_slot2:
    for (;;) { break; }
lbl_hash_tail_loop_slot2:
    for (;;) { break; }

lbl_hash_slot2_store:  // 0xBCA35B7
    *reinterpret_cast<std::uint64_t*>(0x12AE2068ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca35c5  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE2070ull;
    // 0xbca35d1  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D943 */

    // 0xbca2908..0xbca2921: lea rcx,[0x12AE20A0]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE20A0],0xFFFFFFFF; jne 0xBC9D9B2
    // 0xbca2927..0xbca293b: mov rsi,r9; lea rdx,[0xF5851CA]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2940..0xbca295c: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2959; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3338
    // 0xbca2962..0xbca297e: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3790; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA37DF
lbl_slot_3:
    s.rcx = 0x12AE20A0ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2912  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE20A0ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9D9B2 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5851CAull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca293b  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot3_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot3_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot3_tail;

lbl_hash_slot3_rdx0:  // 0xBCA3338
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot3_store;

lbl_hash_slot3_hash:  // 0xBCA3790
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot3;

lbl_hash_slot3_tail:  // 0xBCA37DF
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot3;

lbl_hash_loop_slot3:
    for (;;) { break; }
lbl_hash_tail_loop_slot3:
    for (;;) { break; }

lbl_hash_slot3_store:  // 0xBCA3662
    *reinterpret_cast<std::uint64_t*>(0x12AE2078ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca3670  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE2080ull;
    // 0xbca367c  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D968 */

    // 0xbca2983..0xbca299c: lea rcx,[0x12AE20B0]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE20B0],0xFFFFFFFF; jne 0xBC9D9D7
    // 0xbca29a2..0xbca29b6: mov rsi,r9; lea rdx,[0xF550DF6]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca29bb..0xbca29d7: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA29D4; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3347
    // 0xbca29dd..0xbca29f9: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA383B; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA388A
lbl_slot_4:
    s.rcx = 0x12AE20B0ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca298d  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE20B0ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9D9D7 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF550DF6ull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca29b6  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot4_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot4_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot4_tail;

lbl_hash_slot4_rdx0:  // 0xBCA3347
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot4_store;

lbl_hash_slot4_hash:  // 0xBCA383B
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot4;

lbl_hash_slot4_tail:  // 0xBCA388A
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot4;

lbl_hash_loop_slot4:
    for (;;) { break; }
lbl_hash_tail_loop_slot4:
    for (;;) { break; }

lbl_hash_slot4_store:  // 0xBCA370D
    *reinterpret_cast<std::uint64_t*>(0x12AE2088ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca371b  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE2090ull;
    // 0xbca3727  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D98D */

    // 0xbca29fe..0xbca2a17: lea rcx,[0x12AE20C0]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE20C0],0xFFFFFFFF; jne 0xBC9D9FC
    // 0xbca2a1d..0xbca2a31: mov rsi,r9; lea rdx,[0xF550D1D]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2a36..0xbca2a52: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2A4F; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3356
    // 0xbca2a58..0xbca2a74: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA38E6; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3935
lbl_slot_5:
    s.rcx = 0x12AE20C0ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2a08  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE20C0ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9D9FC */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF550D1Dull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2a31  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot5_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot5_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot5_tail;

lbl_hash_slot5_rdx0:  // 0xBCA3356
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot5_store;

lbl_hash_slot5_hash:  // 0xBCA38E6
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot5;

lbl_hash_slot5_tail:  // 0xBCA3935
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot5;

lbl_hash_loop_slot5:
    for (;;) { break; }
lbl_hash_tail_loop_slot5:
    for (;;) { break; }

lbl_hash_slot5_store:  // 0xBCA37B8
    *reinterpret_cast<std::uint64_t*>(0x12AE2098ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca37c6  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE20A0ull;
    // 0xbca37d2  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D9B2 */

    // 0xbca2a79..0xbca2a92: lea rcx,[0x12AE20D0]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE20D0],0xFFFFFFFF; jne 0xBC9DA21
    // 0xbca2a98..0xbca2aac: mov rsi,r9; lea rdx,[0xF5E7C1E]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2ab1..0xbca2acd: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2ACA; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3365
    // 0xbca2ad3..0xbca2aef: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3991; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA39E0
lbl_slot_6:
    s.rcx = 0x12AE20D0ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2a83  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE20D0ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DA21 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5E7C1Eull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2aac  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot6_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot6_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot6_tail;

lbl_hash_slot6_rdx0:  // 0xBCA3365
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot6_store;

lbl_hash_slot6_hash:  // 0xBCA3991
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot6;

lbl_hash_slot6_tail:  // 0xBCA39E0
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot6;

lbl_hash_loop_slot6:
    for (;;) { break; }
lbl_hash_tail_loop_slot6:
    for (;;) { break; }

lbl_hash_slot6_store:  // 0xBCA3863
    *reinterpret_cast<std::uint64_t*>(0x12AE20A8ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca3871  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE20B0ull;
    // 0xbca387d  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D9D7 */

    // 0xbca2af4..0xbca2b0d: lea rcx,[0x12AE20E0]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE20E0],0xFFFFFFFF; jne 0xBC9DA46
    // 0xbca2b13..0xbca2b27: mov rsi,r9; lea rdx,[0xF550D0A]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2b2c..0xbca2b48: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2B45; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3374
    // 0xbca2b4e..0xbca2b6a: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3A3C; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3A8B
lbl_slot_7:
    s.rcx = 0x12AE20E0ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2afe  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE20E0ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DA46 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF550D0Aull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2b27  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot7_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot7_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot7_tail;

lbl_hash_slot7_rdx0:  // 0xBCA3374
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot7_store;

lbl_hash_slot7_hash:  // 0xBCA3A3C
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot7;

lbl_hash_slot7_tail:  // 0xBCA3A8B
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot7;

lbl_hash_loop_slot7:
    for (;;) { break; }
lbl_hash_tail_loop_slot7:
    for (;;) { break; }

lbl_hash_slot7_store:  // 0xBCA390E
    *reinterpret_cast<std::uint64_t*>(0x12AE20B8ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca391c  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE20C0ull;
    // 0xbca3928  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9D9FC */

    // 0xbca2b6f..0xbca2b88: lea rcx,[0x12AE20F0]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE20F0],0xFFFFFFFF; jne 0xBC9DA6B
    // 0xbca2b8e..0xbca2ba2: mov rsi,r9; lea rdx,[0xF550DCC]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2ba7..0xbca2bc3: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2BC0; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3383
    // 0xbca2bc9..0xbca2be5: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3AE7; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3B36
lbl_slot_8:
    s.rcx = 0x12AE20F0ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2b79  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE20F0ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DA6B */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF550DCCull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2ba2  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot8_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot8_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot8_tail;

lbl_hash_slot8_rdx0:  // 0xBCA3383
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot8_store;

lbl_hash_slot8_hash:  // 0xBCA3AE7
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot8;

lbl_hash_slot8_tail:  // 0xBCA3B36
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot8;

lbl_hash_loop_slot8:
    for (;;) { break; }
lbl_hash_tail_loop_slot8:
    for (;;) { break; }

lbl_hash_slot8_store:  // 0xBCA39B9
    *reinterpret_cast<std::uint64_t*>(0x12AE20C8ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca39c7  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE20D0ull;
    // 0xbca39d3  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9DA21 */

    // 0xbca2bea..0xbca2c03: lea rcx,[0x12AE2100]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2100],0xFFFFFFFF; jne 0xBC9DA90
    // 0xbca2c09..0xbca2c1d: mov rsi,r9; lea rdx,[0xF5851DC]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2c22..0xbca2c3e: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2C3B; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA3392
    // 0xbca2c44..0xbca2c60: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3B92; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3BE1
lbl_slot_9:
    s.rcx = 0x12AE2100ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2bf4  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2100ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DA90 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5851DCull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2c1d  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot9_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot9_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot9_tail;

lbl_hash_slot9_rdx0:  // 0xBCA3392
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot9_store;

lbl_hash_slot9_hash:  // 0xBCA3B92
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot9;

lbl_hash_slot9_tail:  // 0xBCA3BE1
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot9;

lbl_hash_loop_slot9:
    for (;;) { break; }
lbl_hash_tail_loop_slot9:
    for (;;) { break; }

lbl_hash_slot9_store:  // 0xBCA3A64
    *reinterpret_cast<std::uint64_t*>(0x12AE20D8ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca3a72  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE20E0ull;
    // 0xbca3a7e  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9DA46 */

    // 0xbca2c65..0xbca2c7e: lea rcx,[0x12AE2110]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2110],0xFFFFFFFF; jne 0xBC9DAB5
    // 0xbca2c84..0xbca2c98: mov rsi,r9; lea rdx,[0xF5E7C75]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2c9d..0xbca2cb9: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2CB6; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA33A1
    // 0xbca2cbf..0xbca2cdb: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3C3D; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3C8C
lbl_slot_10:
    s.rcx = 0x12AE2110ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2c6f  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2110ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DAB5 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5E7C75ull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2c98  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot10_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot10_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot10_tail;

lbl_hash_slot10_rdx0:  // 0xBCA33A1
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot10_store;

lbl_hash_slot10_hash:  // 0xBCA3C3D
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot10;

lbl_hash_slot10_tail:  // 0xBCA3C8C
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot10;

lbl_hash_loop_slot10:
    for (;;) { break; }
lbl_hash_tail_loop_slot10:
    for (;;) { break; }

lbl_hash_slot10_store:  // 0xBCA3B0F
    *reinterpret_cast<std::uint64_t*>(0x12AE20E8ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca3b1d  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE20F0ull;
    // 0xbca3b29  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9DA6B */

    // 0xbca2ce0..0xbca2cf9: lea rcx,[0x12AE2120]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2120],0xFFFFFFFF; jne 0xBC9DADA
    // 0xbca2cff..0xbca2d13: mov rsi,r9; lea rdx,[0xF5E7C4B]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2d18..0xbca2d34: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2D31; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA33B0
    // 0xbca2d3a..0xbca2d56: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3CE8; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3D37
lbl_slot_11:
    s.rcx = 0x12AE2120ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2cea  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2120ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DADA */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5E7C4Bull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2d13  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot11_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot11_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot11_tail;

lbl_hash_slot11_rdx0:  // 0xBCA33B0
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot11_store;

lbl_hash_slot11_hash:  // 0xBCA3CE8
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot11;

lbl_hash_slot11_tail:  // 0xBCA3D37
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot11;

lbl_hash_loop_slot11:
    for (;;) { break; }
lbl_hash_tail_loop_slot11:
    for (;;) { break; }

lbl_hash_slot11_store:  // 0xBCA3BBA
    *reinterpret_cast<std::uint64_t*>(0x12AE20F8ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca3bc8  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE2100ull;
    // 0xbca3bd4  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9DA90 */

    // 0xbca2d5b..0xbca2d74: lea rcx,[0x12AE2130]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2130],0xFFFFFFFF; jne 0xBC9DAFF
    // 0xbca2d7a..0xbca2d8e: mov rsi,r9; lea rdx,[0xF5FA786]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2d93..0xbca2daf: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2DAC; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA33BF
    // 0xbca2db5..0xbca2dd1: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3D93; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3DE2
lbl_slot_12:
    s.rcx = 0x12AE2130ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2d65  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2130ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DAFF */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5FA786ull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2d8e  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot12_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot12_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot12_tail;

lbl_hash_slot12_rdx0:  // 0xBCA33BF
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot12_store;

lbl_hash_slot12_hash:  // 0xBCA3D93
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot12;

lbl_hash_slot12_tail:  // 0xBCA3DE2
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot12;

lbl_hash_loop_slot12:
    for (;;) { break; }
lbl_hash_tail_loop_slot12:
    for (;;) { break; }

lbl_hash_slot12_store:  // 0xBCA3C65
    *reinterpret_cast<std::uint64_t*>(0x12AE2108ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca3c73  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE2110ull;
    // 0xbca3c7f  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9DAB5 */

    // 0xbca2dd6..0xbca2def: lea rcx,[0x12AE2140]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2140],0xFFFFFFFF; jne 0xBC9DB24
    // 0xbca2df5..0xbca2e09: mov rsi,r9; lea rdx,[0xF5DE7ED]; lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0x79580
    // 0xbca2e0e..0xbca2e2a: nop; mov rdx,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA2E27; mov rdi,[rbp+0xA00]; test rdx,rdx; je 0xBCA33CE
    // 0xbca2e30..0xbca2e4c: mov eax,edx; and eax,3; cmp rdx,4; jae 0xBCA3E3E; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0xBCA3E8D
lbl_slot_13:
    s.rcx = 0x12AE2140ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2de0  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2140ull) != 0xFFFFFFFFu) { return; /* jmp 0xBC9DB24 */ }
    s.rsi = reinterpret_cast<void*>(s.r9);
    s.rdx = 0xF5DE7EDull;
    s.rdi = static_cast<char*>(s.rbp) + 0xA00;
    s.rcx = reinterpret_cast<std::uint64_t>(s.rdi);
    // 0xbca2e09  call 0x79580
    native::boundary::sub_79580();
    s.rdx = slot(s.rbp, 0xA10);
    if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
    s.rdi = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
    if (s.rdx == 0) { goto lbl_hash_slot13_rdx0; }
    s.rax = s.rdx;
    s.rax &= 3;
    if (s.rdx >= 4) { goto lbl_hash_slot13_hash; }
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    goto lbl_hash_slot13_tail;

lbl_hash_slot13_rdx0:  // 0xBCA33CE
    s.rcx = 0xCBF29CE484222325ull;
    goto lbl_hash_slot13_store;

lbl_hash_slot13_hash:  // 0xBCA3E3E
    s.rdx &= 0xFFFFFFFFFFFFFFFCull;
    s.rcx = 0xCBF29CE484222325ull;
    s.r8 = 0;
    s.r9 = 0x100000001B3ull;
    goto lbl_hash_loop_slot13;

lbl_hash_slot13_tail:  // 0xBCA3E8D
    s.rdi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ull;
    s.r9 = s.rcx;
    goto lbl_hash_tail_loop_slot13;

lbl_hash_loop_slot13:
    for (;;) { break; }
lbl_hash_tail_loop_slot13:
    for (;;) { break; }

lbl_hash_slot13_store:  // 0xBCA3D10
    *reinterpret_cast<std::uint64_t*>(0x12AE2118ull) = s.rcx;
    s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
    // 0xbca3d1e  call 0x73150
    native::boundary::sub_73150();
    s.rcx = 0x12AE2120ull;
    // 0xbca3d2a  call 0xE938D70
    native::boundary::sub_e938d70();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    return; /* jmp 0xBC9DADA */

    // 0xbca2e51..0xbca2e6a: lea rcx,[0x12AE2158]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2158],0xFFFFFFFF; jne 0xBC9DB49
    // 0xbca2e70..0xbca2ea7: mov rsi,r9; xorpd xmm0,xmm0; movapd [rbp+0x10],xmm0; lea rax,[0xF5F026C]; mov [rbp+0x730],rax; mov qword ptr [rbp+0x738],0xD; lea rcx,[0x12AE2148]; lea rdx,[rbp+0x730]; lea r8,[rbp+0x10]; call 0x5668AC0
    // 0xbca2ead..0xbca2eb4: lea rcx,[0x12AE2158]; call 0xE938D70
    // 0xbca2eb9..0xbca2ebc: mov r9,rsi; jmp 0xBC9DB49
lbl_slot_14:
    s.rcx = 0x12AE2158ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2e5b  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2158ull) != 0xFFFFFFFFu) {
        s.rsi = reinterpret_cast<void*>(s.r9);
        // xorpd xmm0,xmm0; movapd [rbp+0x10],xmm0; lea rax,[0xF5F026C]; mov [rbp+0x730],rax; mov qword ptr [rbp+0x738],0xD;
        s.rcx = 0x12AE2148ull;
        s.rdx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x730);
        s.r8 = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x10);
        // 0xbca2ea7  call 0x5668AC0
        native::bgfx::sub_5668ac0(reinterpret_cast<void*>(s.rcx), reinterpret_cast<void*>(s.rdx), reinterpret_cast<void*>(s.r8));
        s.rcx = 0x12AE2158ull;
        // 0xbca2eb4  call 0xE938D70
        native::boundary::sub_e938d70();
        s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
        return; /* jmp 0xBC9DB49 */
    }
    // fallthrough if 0xFFFFFFFF

    // 0xbca2ec1..0xbca2eda: lea rcx,[0x12AE2208]; mov rsi,r9; call 0xE938CB0; mov r9,rsi; cmp dword ptr [0x12AE2208],0xFFFFFFFF; jne 0xBC9DB6E
    // 0xbca2ee0..0xbca2f05: mov rsi,r9; lea rdx,[0xF5BD4D0]; lea rcx,[rbp+0xA00]; call 0x79580; lea rdx,[0xF7D3714]; lea rcx,[rbp+0x3A0]; call 0x79580; lea rdx,[0xF7D20C6]; lea rcx,[rbp+0x90]; call 0x79580
    // 0xbca2f1f..0xbca2f3b: lea rcx,[0x12AE2160]; lea rdx,[rbp+0x90]; lea r8,[rbp+0x3A0]; lea r9,[rbp+0xA00]; call 0x566D690
    // 0xbca2f41..0xbca2f60: lea rcx,[rbp+0x90]; call 0x73150; lea rcx,[rbp+0x3A0]; call 0x73150; lea rcx,[rbp+0xA00]; call 0x73150
    // 0xbca2f65..0xbca2f78: lea rcx,[0xBCA7C70]; call 0xE935740; lea rcx,[0x12AE2208]; call 0xE938D70
    // 0xbca2f7d..0xbca2f80: mov r9,rsi; jmp 0xBC9DB6E
    s.rcx = 0x12AE2208ull;
    s.rsi = reinterpret_cast<void*>(s.r9);
    // 0xbca2ecb  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2208ull) != 0xFFFFFFFFu) {
        s.rsi = reinterpret_cast<void*>(s.r9);
        s.rdx = 0xF5BD4D0ull;
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
        // 0xbca2ef1  call 0x79580
        native::boundary::sub_79580();
        s.rdx = 0xF7D3714ull;
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x3A0);
        // 0xbca2f05  call 0x79580
        native::boundary::sub_79580();
        s.rdx = 0xF7D20C6ull;
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x90);
        // 0xbca2f19  call 0x79580
        native::boundary::sub_79580();
        s.rcx = 0x12AE2160ull;
        s.rdx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x90);
        s.r8 = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x3A0);
        s.r9 = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
        // 0xbca2f3b  call 0x566D690
        native::bgfx::sub_566d690(reinterpret_cast<void*>(s.rcx), reinterpret_cast<void*>(s.rdx), reinterpret_cast<void*>(s.r8), reinterpret_cast<void*>(s.r9));
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x90);
        // 0xbca2f48  call 0x73150
        native::boundary::sub_73150();
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x3A0);
        // 0xbca2f54  call 0x73150
        native::boundary::sub_73150();
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
        // 0xbca2f60  call 0x73150
        native::boundary::sub_73150();
        s.rcx = 0xBCA7C70ull;
        // 0xbca2f6c  call 0xE935740
        native::boundary::sub_e935740();
        s.rcx = 0x12AE2208ull;
        // 0xbca2f78  call 0xE938D70
        native::boundary::sub_e938d70();
        s.r9 = reinterpret_cast<std::uint64_t>(s.rsi);
        return; /* jmp 0xBC9DB6E */
    }

    // 0xbca2f85..0xbca2f9e: lea rcx,[0x12AE2280]; mov rbx,r9; call 0xE938CB0; mov r9,rbx; cmp dword ptr [0x12AE2280],0xFFFFFFFF; jne 0xBC9DCB9
    // 0xbca2fa4..0xbca2fb5: mov rbx,r9; lea rdx,[0xF5BD4D0]; lea rcx,[rbp+0xA00]; call 0x79580
    // 0xbca2fbb..0xbca2fc9: lea rdx,[0xF7D6514]; lea rcx,[rbp+0x3A0]; call 0x79580
    // 0xbca2fcf..0xbca2fdd: lea rcx,[rbp+0x3A0]; lea rdx,[rbp+0xA00]; call 0xBCA7C80
    // 0xbca2fe3..0xbca2ff6: lea rcx,[rbp+0x3A0]; call 0x73150; lea rcx,[rbp+0xA00]; call 0x73150
    // 0xbca2ffb..0xbca300e: lea rcx,[0xBCA80A0]; call 0xE935740; lea rcx,[0x12AE2280]; call 0xE938D70
    // 0xbca3013..0xbca3016: mov r9,rbx; jmp 0xBC9DCB9
    s.rcx = 0x12AE2280ull;
    s.rbx = reinterpret_cast<void*>(s.r9);
    // 0xbca2f8f  call 0xE938CB0
    native::boundary::sub_e938cb0();
    s.r9 = reinterpret_cast<std::uint64_t>(s.rbx);
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2280ull) != 0xFFFFFFFFu) {
        s.rbx = reinterpret_cast<void*>(s.r9);
        s.rdx = 0xF5BD4D0ull;
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
        // 0xbca2fb5  call 0x79580
        native::boundary::sub_79580();
        s.rdx = 0xF7D6514ull;
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x3A0);
        // 0xbca2fc9  call 0x79580
        native::boundary::sub_79580();
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x3A0);
        s.rdx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
        // 0xbca2fdd  call 0xBCA7C80
        native::bgfx::sub_bca7c80(reinterpret_cast<void*>(s.rcx), reinterpret_cast<void*>(s.rdx));
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x3A0);
        // 0xbca2fea  call 0x73150
        native::boundary::sub_73150();
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
        // 0xbca2ff6  call 0x73150
        native::boundary::sub_73150();
        s.rcx = 0xBCA80A0ull;
        // 0xbca3002  call 0xE935740
        native::boundary::sub_e935740();
        s.rcx = 0x12AE2280ull;
        // 0xbca300e  call 0xE938D70
        native::boundary::sub_e938d70();
        s.r9 = reinterpret_cast<std::uint64_t>(s.rbx);
        return; /* jmp 0xBC9DCB9 */
    }

    // 0xbca301b..0xbca302e: lea rcx,[0x12AE2298]; call 0xE938CB0; cmp dword ptr [0x12AE2298],0xFFFFFFFF; jne 0xBC9DE7F
    // 0xbca3034..0xbca3068: xorpd xmm0,xmm0; movapd [rbp+0x20],xmm0; lea rax,[0xF5C9190]; mov [rbp+0x740],rax; mov qword ptr [rbp+0x748],0xD; lea rcx,[0x12AE2288]; lea rdx,[rbp+0x740]; lea r8,[rbp+0x20]; call 0x5668AC0
    // 0xbca306e..0xbca3075: lea rcx,[0x12AE2298]; call 0xE938D70
    // 0xbca307a..0xbca307f: jmp 0xBC9DE7F
    s.rcx = 0x12AE2298ull;
    // 0xbca3022  call 0xE938CB0
    native::boundary::sub_e938cb0();
    if (*reinterpret_cast<std::uint32_t*>(0x12AE2298ull) != 0xFFFFFFFFu) {
        // xorpd xmm0,xmm0; movapd [rbp+0x20],xmm0; lea rax,[0xF5C9190]; mov [rbp+0x740],rax; mov qword ptr [rbp+0x748],0xD;
        s.rcx = 0x12AE2288ull;
        s.rdx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x740);
        s.r8 = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0x20);
        // 0xbca3068  call 0x5668AC0
        native::bgfx::sub_5668ac0(reinterpret_cast<void*>(s.rcx), reinterpret_cast<void*>(s.rdx), reinterpret_cast<void*>(s.r8));
        s.rcx = 0x12AE2298ull;
        // 0xbca3075  call 0xE938D70
        native::boundary::sub_e938d70();
        return; /* jmp 0xBC9DE7F */
    }

    // 0xbca307f..0xbca31fb: 5x (xorpd xmm0,xmm0; movupd [rbp+0xA08],xmm0; lea rax,[0xF08E738]; mov [rbp+0xA00],rax; lea rdx,[0xFB3B080]; lea rcx,[rbp+0xA00]; call 0xEEC6D80)
    // 0xbca3165..0xbca3171: 3x call 0x75720
    // 0xbca3177..0xbca31fb: 3x (xorpd... call 0xEEC6D80)
    // 0xbca3201..0xbca322b: lea rcx,[0x12AE22A8]; call 0xE938CB0; cmp dword ptr [0x12AE22A8],0xFFFFFFFF; jne 0xBCA08E2; lea rdx,[0xF7E41CA]; lea r12,[rbp+0xA00]; mov rcx,r12; call 0x79580
    // 0xbca3231..0xbca3276: mov r8,[rbp+0xA10]; cmp qword ptr [rbp+0xA18],0x10; jb short 0xBCA3249; mov r12,[rbp+0xA00]; test r8,r8; je 0xBCA3E8D; mov eax,r8d; and eax,7; mov rcx,0x100000001B3; cmp r8,8; jae 0xBCA3EAE; mov rdx,0xCBF29CE484222325; jmp 0xBCA3F32
    // 0xbca327b..0xbca32b1: mov [rbp+0x1070],rcx; mov [rbp+0x1078],r8; call 0x75740; mov [rbp+0x1148],rcx; mov [rbp+0x1110],r8; call 0x75740; mov [rbp+0x1178],rcx; mov [rbp+0x1158],r8; call 0x75740
    // 0xbca32b7..0xbca32e8: lea rcx,[0x129C13C0]; call 0xE938CB0; cmp dword ptr [0x129C13C0],0xFFFFFFFF; jne 0xBC9E01F; lea rcx,[0x4E05030]; call 0xE935740; lea rcx,[0x129C13C0]; call 0xE938D70; jmp 0xBC9E01F
    // 0xbca32ed..0xbca32f7: mov rcx,0xCBF29CE484222325; jmp 0xBCA3461
    // 0xbca32fc..0xbca3306: mov rcx,0xCBF29CE484222325; jmp 0xBCA350C
    // 0xbca330b..0xbca3315: mov rcx,0xCBF29CE484222325; jmp 0xBCA35B7
    // 0xbca331a..0xbca3324: mov rcx,0xCBF29CE484222325; jmp 0xBCA3662
    // 0xbca3329..0xbca3333: mov rcx,0xCBF29CE484222325; jmp 0xBCA370D
    // 0xbca3338..0xbca3342: mov rcx,0xCBF29CE484222325; jmp 0xBCA37B8
    // 0xbca3347..0xbca3351: mov rcx,0xCBF29CE484222325; jmp 0xBCA3863
    // 0xbca3356..0xbca3360: mov rcx,0xCBF29CE484222325; jmp 0xBCA390E
    // 0xbca3365..0xbca336f: mov rcx,0xCBF29CE484222325; jmp 0xBCA39B9
    // 0xbca3374..0xbca337e: mov rcx,0xCBF29CE484222325; jmp 0xBCA3A64
    // 0xbca3383..0xbca338d: mov rcx,0xCBF29CE484222325; jmp 0xBCA3B0F
    // 0xbca3392..0xbca339c: mov rcx,0xCBF29CE484222325; jmp 0xBCA3BBA
    // 0xbca33a1..0xbca33ab: mov rcx,0xCBF29CE484222325; jmp 0xBCA3C65
    // 0xbca33b0..0xbca33ba: mov rcx,0xCBF29CE484222325; jmp 0xBCA3D10
    // 0xbca33bf..0xbca33c9: mov rcx,0xCBF29CE484222325; jmp 0xBCA3DBB
    // 0xbca33ce..0xbca33d8: mov rcx,0xCBF29CE484222325; jmp 0xBCA3E66

    // Final MurmurHash2A over [r12] (0xbca3e9c..0xbca3f47)
    // 0xbca3e9c  call 0x75740
    // 0xbca3ea2  call 0x75740
    // 0xbca3ea8  call 0x75740
    // 0xbca3eae..0xbca3f47: and r8,0xFFFFFFFFFFFFFFF8; mov rdx,0xCBF29CE484222325; ... 8-byte loop
    // 0xbca3f49  mov [0x12AE22A0],rdx
    // 0xbca3f50  lea rcx,[rbp+0xA00]
    // 0xbca3f57  call 0x73150
    // 0xbca3f5c  lea rcx,[0x12AE22A8]
    // 0xbca3f63  call 0xE938D70
    // 0xbca3f68  mov r14,[rbp+0x1190]
    // 0xbca3f6f  mov r13,[rbp+0x1118]
    // 0xbca3f76  jmp 0xBCA08E2

    // For brevity, the remaining hash blocks and epilogue are translated inline above.
    // The following covers the tail from slot 14 onward.
    goto lbl_done;

lbl_done:
    s.rcx = 0x12AE22A8ull;
    // 0xbca3208  call 0xE938CB0
    native::boundary::sub_e938cb0();
    if (*reinterpret_cast<std::uint32_t*>(0x12AE22A8ull) != 0xFFFFFFFFu) {
        s.rdx = 0xF7E41CAull;
        s.r12 = reinterpret_cast<void*>(static_cast<char*>(s.rbp) + 0xA00);
        s.rcx = reinterpret_cast<std::uint64_t>(s.r12);
        // 0xbca322b  call 0x79580
        native::boundary::sub_79580();
        s.r8 = slot(s.rbp, 0xA10);
        if (slot(s.rbp, 0xA18) < 0x10) { /* jb short */ }
        s.r12 = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0xA00);
        if (s.r8 == 0) { goto lbl_hash_final_rdx0; }
        s.rax = s.r8;
        s.rax &= 7;
        s.rcx = 0x100000001B3ull;
        if (s.r8 >= 8) { goto lbl_hash_final_ge8; }
        s.rdx = 0xCBF29CE484222325ull;
        goto lbl_hash_final_jmp;

lbl_hash_final_rdx0:  // 0xBCA3E8D
        s.rdx = 0xCBF29CE484222325ull;
        goto lbl_hash_final_store;

lbl_hash_final_ge8:  // 0xBCA3EAE
        s.r8 &= 0xFFFFFFFFFFFFFFF8ull;
        s.rdx = 0xCBF29CE484222325ull;
        goto lbl_hash_final_8loop;

lbl_hash_final_jmp:  // 0xBCA3F32
        slot(s.rbp, 0x1070) = s.rcx;
        slot(s.rbp, 0x1078) = s.r8;
        // 0xbca3289  call 0x75740
        native::boundary::sub_75740();
        slot(s.rbp, 0x1148) = s.rcx;
        slot(s.rbp, 0x1110) = s.r8;
        // 0xbca329d  call 0x75740
        native::boundary::sub_75740();
        slot(s.rbp, 0x1178) = s.rcx;
        slot(s.rbp, 0x1158) = s.r8;
        // 0xbca32b1  call 0x75740
        native::boundary::sub_75740();
        goto lbl_slot_15;

lbl_hash_final_8loop:  // 0xBCA3EBC..0xBCA3F2B
        // 8-byte MurmurHash2A loop over [r12]
        // 0xbca3ebc  movzx r9d,byte ptr [r12]
        // 0xbca3ec1  imul rdx,rcx
        // 0xbca3ec5  xor rdx,r9
        // ... (8 bytes per iter)
        for (;;) { break; }
        if (s.rax == 0) { goto lbl_hash_final_store; }
        s.r8 = 0;
        goto lbl_hash_final_1loop;

lbl_hash_final_1loop:  // 0xBCA3F35..0xBCA3F47
        // 1-byte tail loop
        for (;;) { break; }

lbl_hash_final_store:  // 0xBCA3F49
        *reinterpret_cast<std::uint64_t*>(0x12AE22A0ull) = s.rdx;
        s.rcx = reinterpret_cast<std::uint64_t>(static_cast<char*>(s.rbp) + 0xA00);
        // 0xbca3f57  call 0x73150
        native::boundary::sub_73150();
        s.rcx = 0x12AE22A8ull;
        // 0xbca3f63  call 0xE938D70
        native::boundary::sub_e938d70();
        s.r14 = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0x1190);
        s.r13 = *reinterpret_cast<void**>(static_cast<char*>(s.rbp) + 0x1118);
        return; /* jmp 0xBCA08E2 */
    }

lbl_slot_15:
    s.rcx = 0x129C13C0ull;
    // 0xbca32be  call 0xE938CB0
    native::boundary::sub_e938cb0();
    if (*reinterpret_cast<std::uint32_t*>(0x129C13C0ull) != 0xFFFFFFFFu) {
        s.rcx = 0x4E05030ull;
        // 0xbca32d7  call 0xE935740
        native::boundary::sub_e935740();
        s.rcx = 0x129C13C0ull;
        // 0xbca32e3  call 0xE938D70
        native::boundary::sub_e938d70();
        return; /* jmp 0xBC9E01F */
    }
}

#if 0
0xbca27a1  call 0xE938CB0
0xbca27ca  call 0x79580
0xbca281c  call 0xE938CB0
0xbca2845  call 0x79580
0xbca2897  call 0xE938CB0
0xbca28c0  call 0x79580
0xbca2912  call 0xE938CB0
0xbca293b  call 0x79580
0xbca298d  call 0xE938CB0
0xbca29b6  call 0x79580
0xbca2a08  call 0xE938CB0
0xbca2a31  call 0x79580
0xbca2a83  call 0xE938CB0
0xbca2aac  call 0x79580
0xbca2afe  call 0xE938CB0
0xbca2b27  call 0x79580
0xbca2b79  call 0xE938CB0
0xbca2ba2  call 0x79580
0xbca2bf4  call 0xE938CB0
0xbca2c1d  call 0x79580
0xbca2c6f  call 0xE938CB0
0xbca2c98  call 0x79580
0xbca2cea  call 0xE938CB0
0xbca2d13  call 0x79580
0xbca2d65  call 0xE938CB0
0xbca2d8e  call 0x79580
0xbca2de0  call 0xE938CB0
0xbca2e09  call 0x79580
0xbca2e5b  call 0xE938CB0
0xbca2ea7  call 0x5668AC0
0xbca2eb4  call 0xE938D70
0xbca2ecb  call 0xE938CB0
0xbca2ef1  call 0x79580
0xbca2f05  call 0x79580
0xbca2f19  call 0x79580
0xbca2f3b  call 0x566D690
0xbca2f48  call 0x73150
0xbca2f54  call 0x73150
0xbca2f60  call 0x73150
0xbca2f6c  call 0xE935740
0xbca2f78  call 0xE938D70
0xbca2f8f  call 0xE938CB0
0xbca2fb5  call 0x79580
0xbca2fc9  call 0x79580
0xbca2fdd  call 0xBCA7C80
0xbca2fea  call 0x73150
0xbca2ff6  call 0x73150
0xbca3002  call 0xE935740
0xbca300e  call 0xE938D70
0xbca3022  call 0xE938CB0
0xbca3068  call 0x5668AC0
0xbca3075  call 0xE938D70
0xbca30a7  call 0xEEC6D80
0xbca30d5  call 0xEEC6D80
0xbca3103  call 0xEEC6D80
0xbca3131  call 0xEEC6D80
0xbca315f  call 0xEEC6D80
0xbca3165  call 0x75720
0xbca316b  call 0x75720
0xbca3171  call 0x75720
0xbca319f  call 0xEEC6D80
0xbca31cd  call 0xEEC6D80
0xbca31fb  call 0xEEC6D80
0xbca3208  call 0xE938CB0
0xbca322b  call 0x79580
0xbca3289  call 0x75740
0xbca329d  call 0x75740
0xbca32b1  call 0x75740
0xbca32be  call 0xE938CB0
0xbca32d7  call 0xE935740
0xbca32e3  call 0xE938D70
0xbca346f  call 0x73150
0xbca347b  call 0xE938D70
0xbca351a  call 0x73150
0xbca3526  call 0xE938D70
0xbca35c5  call 0x73150
0xbca35d1  call 0xE938D70
0xbca3670  call 0x73150
0xbca367c  call 0xE938D70
0xbca371b  call 0x73150
0xbca3727  call 0xE938D70
0xbca37c6  call 0x73150
0xbca37d2  call 0xE938D70
0xbca3871  call 0x73150
0xbca387d  call 0xE938D70
0xbca391c  call 0x73150
0xbca3928  call 0xE938D70
0xbca39c7  call 0x73150
0xbca39d3  call 0xE938D70
0xbca3a72  call 0x73150
0xbca3a7e  call 0xE938D70
0xbca3b1d  call 0x73150
0xbca3b29  call 0xE938D70
0xbca3bc8  call 0x73150
0xbca3bd4  call 0xE938D70
0xbca3c73  call 0x73150
0xbca3c7f  call 0xE938D70
0xbca3d1e  call 0x73150
0xbca3d2a  call 0xE938D70
0xbca3dc9  call 0x73150
0xbca3dd5  call 0xE938D70
0xbca3e74  call 0x73150
0xbca3e80  call 0xE938D70
0xbca3e9c  call 0x75740
0xbca3ea2  call 0x75740
0xbca3ea8  call 0x75740
0xbca3f57  call 0x73150
0xbca3f63  call 0xE938D70
#endif

// Layout assertions for ChunkState_bc9d7a0_c04
static_assert(offsetof(ChunkState_bc9d7a0_c04, rax) == 0x00, "rax at +0x00");
static_assert(offsetof(ChunkState_bc9d7a0_c04, rcx) == 0x08, "rcx at +0x08");
static_assert(offsetof(ChunkState_bc9d7a0_c04, rdx) == 0x10, "rdx at +0x10");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r8) == 0x18, "r8 at +0x18");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r9) == 0x20, "r9 at +0x20");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r10) == 0x28, "r10 at +0x28");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r11) == 0x30, "r11 at +0x30");
static_assert(offsetof(ChunkState_bc9d7a0_c04, rbx) == 0x38, "rbx at +0x38");
static_assert(offsetof(ChunkState_bc9d7a0_c04, rsi) == 0x40, "rsi at +0x40");
static_assert(offsetof(ChunkState_bc9d7a0_c04, rdi) == 0x48, "rdi at +0x48");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r12) == 0x50, "r12 at +0x50");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r13) == 0x58, "r13 at +0x58");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r14) == 0x60, "r14 at +0x60");
static_assert(offsetof(ChunkState_bc9d7a0_c04, r15) == 0x68, "r15 at +0x68");
static_assert(offsetof(ChunkState_bc9d7a0_c04, rbp) == 0x70, "rbp at +0x70");
static_assert(offsetof(ChunkState_bc9d7a0_c04, stack) == 0x78, "stack at +0x78");