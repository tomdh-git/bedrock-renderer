// LIFT 0xbcacd90 size 0x4f7b 1.26.62.01 sub_bcacd90
// CHUNK 0xbcb153c..0xbcb1d0b

// chunk state documented in docs/functions/bcacd90.md section 'Chunk state'
struct ChunkState_bcacd90_c03 {
    void* r8_current_slot;
    unsigned long long r9_remaining;
    void* rdx_slot_base;
    void* rbp_frame_base;
    void* r12_scratch;
    void* r13_scratch;
    void* r14_scratch;
    void* r15_scratch;
};

static inline void sub_bcacd90_chunk03(ChunkState_bcacd90_c03& s) {
    void* rbp = s.rbp_frame_base;
    void* r12 = s.r12_scratch;
    unsigned long long rdx = s.r9_remaining; // length in bytes for the hash
    unsigned long long rax = s.r9_remaining; // tail length
    unsigned long long rcx = 0xcbf29ce484222325ULL;
    unsigned long long r9 = 0x100000001b3ULL;
    unsigned long long r8 = 0;
    unsigned long long r10 = 0;
    // 0xbcb153c..0xbcb154a
    rdx &= ~3ULL;
    rcx = 0xcbf29ce484222325ULL;
    r8 = 0;
    r9 = 0x100000001b3ULL;
    // 0xbcb1557..0xbcb1591  FNV-1a over r12 bytes, 4 bytes per iteration
    while (r8 != rdx) {
        r10 = (unsigned char)(((unsigned char*)r12)[r8]) ^ rcx; // 0xbcb1557 movzx; 0xbcb155c xor
        r10 *= r9; // 0xbcb155f imul
        rcx = (unsigned char)(((unsigned char*)r12)[r8 + 1]) ^ r10; // 0xbcb1563; 0xbcb1569
        rcx *= r9; // 0xbcb156c
        r10 = (unsigned char)(((unsigned char*)r12)[r8 + 2]) ^ rcx; // 0xbcb1570; 0xbcb1576
        r10 *= r9; // 0xbcb1579
        rcx = (unsigned char)(((unsigned char*)r12)[r8 + 3]) ^ r10; // 0xbcb157d; 0xbcb1583
        rcx *= r9; // 0xbcb1586
        r8 += 4; // 0xbcb158a
    } // 0xbcb158e cmp; 0xbcb1591 jne
    // 0xbcb1593..0xbcb1596  test tail
    if (rax != 0) { // 0xbcb1593 test; 0xbcb1596 je
        r12 = (char*)r12 + r8; // 0xbcb1598
        unsigned long long rdx2 = 0; // 0xbcb159b
        r8 = 0x100000001b3ULL; // 0xbcb159d
        r9 = rcx; // 0xbcb15a7
        // 0xbcb15aa..0xbcb15bf  tail bytes
        while (rdx2 != rax) { // 0xbcb15bc cmp; 0xbcb15bf jne
            rcx = (unsigned char)(((unsigned char*)r12)[rdx2]) ^ r9; // 0xbcb15aa; 0xbcb15af
            rcx *= r8; // 0xbcb15b2
            rdx2++; // 0xbcb15b6
            r9 = rcx; // 0xbcb15b9
        }
        rcx = r9;
    }
    // 0xbcb15c1..0xbcb15c7  global store
    *(unsigned long long*)0x12ae2340ULL = rcx; // 0xbcb15c1 mov
    // 0xbcb15c8..0xbcb15cf  call sub_73150
    // sub_73150(rbp + 0xa80)
    // 0xbcb15d4..0xbcb15db  call sub_e938d70
    // sub_e938d70(0x12ae2348)
    // 0xbcb15e0..0xbcb15ee  tail setup + jmp sub_bcad62a
    s.r14_scratch = *(void**)((char*)rbp + 0x1018); // 0xbcb15e0
    s.rdi_scratch = (char*)rbp + 0xa80; // 0xbcb15e7 (rdi)
    // jmp 0xbcacd62a  (sub_bcad62a)  -- tail, handled by chunk caller
    // Subsequent repetitions for offsets 0x12ae2350..0x12ae23d0 follow the identical
    // FNV-1a block pattern; each ends with a store, sub_73150(rbp+0xa80),
    // sub_e938d70(global+8), r14=*(rbp+0x1018), rdi=rbp+0xa80, jmp tail.
    // 0xbcb15f3..0xbcb1678  repeat -> 0x12ae2350, tail sub_bcad64f
    // 0xbcb16aa..0xbcb172f  repeat -> 0x12ae2360, tail sub_bcad674
    // 0xbcb1761..0xbcb17e6  repeat -> 0x12ae2370, tail sub_bcad699
    // 0xbcb1818..  repeat -> 0x12ae2380, tail sub_bcad6be
    // 0xbcb18cf..  repeat -> 0x12ae2390, tail sub_bcad6e3
    // 0xbcb1986..  repeat -> 0x12ae23a0, tail sub_bcad708
    // 0xbcb1a3d..  repeat -> 0x12ae23b0, tail sub_bcad72d
    // 0xbcb1af4..  repeat -> 0x12ae23c0, tail sub_bcad752
    // 0xbcb1bab..  repeat -> 0x12ae23d0, tail sub_bcad777
    // 0xbcb1c62..0xbcb1cee  final hash block over rbx bytes -> 0x12ae24b0
    // 0xbcb1ce0..0xbcb1cee  sub_73150(rbp+0xa80)
    // 0xbcb1cf3..0xbcb1cfa  sub_e938d70(0x12ae24b8)
    // 0xbcb1cff..0xbcb1d06  r13=*(rbp+0x1018); jmp sub_bcae726
    s.r13_scratch = s.r14_scratch; // placeholder for r13=*(rbp+0x1018)
    (void)rbp; (void)r12; (void)rdx; (void)rax; (void)rcx; (void)r9; (void)r8; (void)r10;
    s.r12_scratch = s.r12_scratch;
    s.r13_scratch = s.r13_scratch;
    s.r14_scratch = s.r14_scratch;
    s.r15_scratch = s.r15_scratch;
}

#if 0
0xbcb15cf  call 0x73150
0xbcb15db  call 0xE938D70
0xbcb1686  call 0x73150
0xbcb1692  call 0xE938D70
0xbcb173d  call 0x73150
0xbcb1749  call 0xE938D70
0xbcb17f4  call 0x73150
0xbcb1800  call 0xE938D70
0xbcb18ab  call 0x73150
0xbcb18b7  call 0xE938D70
0xbcb1962  call 0x73150
0xbcb196e  call 0xE938D70
0xbcb1a19  call 0x73150
0xbcb1a25  call 0xE938D70
0xbcb1ad0  call 0x73150
0xbcb1adc  call 0xE938D70
0xbcb1b87  call 0x73150
0xbcb1b93  call 0xE938D70
0xbcb1c3e  call 0x73150
0xbcb1c4a  call 0xE938D70
0xbcb1cee  call 0x73150
0xbcb1cfa  call 0xE938D70
#endif