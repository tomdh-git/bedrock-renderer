// LIFT 0xe8230c8 size 0xa41b 1.26.62.01 sub_e8230c8
// CHUNK 0xe82a7d6..0xe82bfb0

// chunk state documented in docs/functions/e8230c8.md section 'Chunk state'
struct ChunkState_e8230c8_c05 {
    void* r13;
    void* rbx_base;
    void* r14;
    void* r15;
    void* r12;
    void* rdi;
    unsigned char al_flags;
};

static inline void sub_e8230c8_chunk_c05(ChunkState_e8230c8_c05& s) {
    void* r13 = s.r13;
    void* rbx = s.rbx_base;
    void* r14 = s.r14;
    void* r15 = s.r15;
    void* r12 = s.r12;
    void* rdi = s.rdi;
    unsigned char al = s.al_flags;
    // 0xe82a7d6..0xe82a7e5
    // entry: clamp/validate r13 against rbx+0x3B0 via sub_47e8f0
    // 0xe82a7d6  mov rcx,r13
    // 0xe82a7d9  lea r8,[rbx+0x3B0]
    // 0xe82a7e0  call 0x47E8F0
    // 0xe82a7e5  nop
    (void)sub_47e8f0(r13, rbx + 0x3B0);
    // 0xe82a7e6..0xe82a80e
    // branch on flags test al,0x10
    // 0xe82a7e6  jmp 0xE82BB6E
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
    unsigned ecx = *(unsigned short*)((char*)r14 + (size_t)r15*8 + 0x14);
    unsigned edi = *(unsigned short*)((char*)r12 + 0x5E);
    edi <<= 2;
    if (edi >= ecx) edi = ecx;
    unsigned r12d = *(unsigned*)((char*)r12 + 0x3C);
    unsigned r13d = *(unsigned*)((char*)r14 + (size_t)r15*8 + 0x10);
    edi <<= 4;
    // 0xe82a814..0xe82a869
    // rdx = rdi + r13; capacity checks against rbx+0x98/0xA8
    // 0xe82a814  lea rdx,[rdi+r13]
    // 0xe82a818  mov rax,[rbx+0x98]
    // 0xe82a81f  ...
    // 0xe82a863  call 0x47E8F0
    // 0xe82a868  nop
    // 0xe82a869  jmp 0xE82BBD2
    void* rdx = (char*)rdi + r13d;
    (void)rdx;
    (void)sub_47e8f0(rdx, (char*)rbx + 0x98);
    // 0xe82a86e..0xe82a89e
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
    unsigned ecx2 = *(unsigned*)((char*)r14 + (size_t)r15*8 + 0x14);
    if (ecx2 < 4) {} else ecx2 = 4;
    void* rdi2 = *(void**)((char*)rbx + 0x1E8);
    rdi2 = (char*)rdi2 + (*(int*)((char*)rbx + 0x90A0));
    (void)rdi2;
    unsigned r13d2 = *(unsigned*)((char*)r14 + (size_t)r15*8 + 0x10);
    ecx2 <<= 4;
    unsigned r12d2 = (unsigned short)ecx2;
    (void)r13d2; (void)r12d2;
    // 0xe82a8a4..0xe82a8f9
    // 0xe82a8a4  lea rdx,[r12+r13]
    // ...
    // 0xe82a8f3  call 0x47E8F0
    // 0xe82a8f8  nop
    // 0xe82a8f9  jmp 0xE82BC41
    void* rdx2 = (char*)(size_t)r12d2 + r13d2;
    (void)rdx2;
    (void)sub_47e8f0(rdx2, (char*)rbx + 0x98);
    // 0xe82a8fe..0xe82a90c
    // 0xe82a8fe  movzx ecx,word ptr [rbx+0x10E]
    // 0xe82a905  cmp cx,[rbx+0xE174]
    // 0xe82a90c  je 0xE82ABB8
    unsigned short cx = *(unsigned short*)((char*)rbx + 0x10E);
    unsigned short cmp = *(unsigned short*)((char*)rbx + 0xE174);
    if (cx == cmp) {
        // 0xe82abb8..0xe82bfab: tail writes and calls
    } else {
        // 0xe82a912..0xe82abb8: matrix normalization block (SIMD)
        // 0xe82a912  movzx ecx,word ptr [rbx+0x10E]
        // 0xe82a919  mov [rbx+0xE174],cx
        *(unsigned short*)((char*)rbx + 0xE174) = cx;
        // SIMD movaps/mulps/shufps sequence computes normalized basis
        // result written into [rbx+0x90B0..0x9160]
        (void)0;
    }
    // 0xe82abb8..0xe82bfab: tail writes and vector reserve/push
    // 0xe82babe  call 0xEEC6ED0
    // 0xe82baf0  call 0xEEC6ED0
    // 0xe82bb29  call 0xEEC6ED0
    // 0xe82bb5f  call 0xEEC6ED0
    // 0xe82bb8e  call 0xEEC6ED0
    // 0xe82bbc3  call 0xEEC6ED0
    // 0xe82bbf1  call 0xEEC6ED0
    // 0xe82bc1f  call 0xEEC6EC0
    // 0xe82bc32  call 0xEEC6ED0
    // 0xe82bc60  call 0xEEC6ED0
    // 0xe82bc83  call 0xEEC6EC0
    // 0xe82bc96  call 0xEEC6ED0
    // 0xe82bcc5  call 0xEEC6ED0
    // 0xe82bcfe  call 0xEEC6ED0
    // 0xe82bd37  call 0xEEC6ED0
    // 0xe82bd6d  call 0xEEC6ED0
    // 0xe82bda0  call 0xEEC6ED0
    // 0xe82bdd3  call 0xEEC6ED0
    // 0xe82be03  call 0xEEC6ED0
    // 0xe82be36  call 0xEEC6ED0
    // 0xe82be6f  call 0xEEC6ED0
    // 0xe82bea5  call 0xEEC6ED0
    // 0xe82beca  call 0xEEC6ED0
    // 0xe82bf0e  call 0xEEC6ED0
    // 0xe82bf47  call 0xEEC6ED0
    // 0xe82bf80  call 0xEEC6ED0
    // 0xe82bfab  jmp 0xE82A4EF
    (void)al;
    (void)rbx; (void)r13; (void)r14; (void)r15; (void)r12; (void)rdi;
}

#if 0
0xe82a7d6  mov rcx,r13
0xe82a7e0  call 0x47E8F0
0xe82a863  call 0x47E8F0
0xe82a8f3  call 0x47E8F0
0xe82ac21  call 0x47E8F0
0xe82af3a  call 0x47E8F0
0xe82afb3  call 0x47E8F0
0xe82b2d9  call 0x47E8F0
0xe82b336  call 0x47E8F0
0xe82b3aa  call 0x47E8F0
0xe82b542  call 0x47E8F0
0xe82b5b6  call 0x47E8F0
0xe82b60f  call 0x47E8F0
0xe82b668  call 0x47E8F0
0xe82b6c3  call 0x47E8F0
0xe82b723  call 0x47E8F0
0xe82b783  call 0x47E8F0
0xe82b7dc  call 0x47E8F0
0xe82b835  call 0x47E8F0
0xe82b890  call 0x47E8F0
0xe82b8eb  call 0x47E8F0
0xe82b944  call 0x47E8F0
0xe82b99f  call 0x47E8F0
0xe82b9f8  call 0x47E8F0
0xe82ba51  call 0x47E8F0
0xe82baaa  call 0x47E8F0
0xe82babe  call 0xEEC6ED0
0xe82baf0  call 0xEEC6ED0
0xe82bb29  call 0xEEC6ED0
0xe82bb5f  call 0xEEC6ED0
0xe82bb8e  call 0xEEC6ED0
0xe82bbc3  call 0xEEC6ED0
0xe82bbf1  call 0xEEC6ED0
0xe82bc1f  call 0xEEC6EC0
0xe82bc32  call 0xEEC6ED0
0xe82bc60  call 0xEEC6ED0
0xe82bc83  call 0xEEC6EC0
0xe82bc96  call 0xEEC6ED0
0xe82bcc5  call 0xEEC6ED0
0xe82bcfe  call 0xEEC6ED0
0xe82bd37  call 0xEEC6ED0
0xe82bd6d  call 0xEEC6ED0
0xe82bda0  call 0xEEC6ED0
0xe82bdd3  call 0xEEC6ED0
0xe82be03  call 0xEEC6ED0
0xe82be36  call 0xEEC6ED0
0xe82be6f  call 0xEEC6ED0
0xe82bea5  call 0xEEC6ED0
0xe82beca  call 0xEEC6ED0
0xe82bf0e  call 0xEEC6ED0
0xe82bf47  call 0xEEC6ED0
0xe82bf80  call 0xEEC6ED0
#endif
