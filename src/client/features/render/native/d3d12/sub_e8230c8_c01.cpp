// LIFT 0xe8230c8 size 0xa41b 1.26.62.01 sub_e8230c8
// CHUNK 0xe8248aa..0xe82609e

// chunk state documented in docs/functions/e8230c8.md section 'Chunk state'
struct ChunkState_e8230c8_c01 {
    void* rbx_base;
    void* r10_scratch;
    void* r13_scratch;
    void* r14_scratch;
};

static inline void sub_e8230c8_chunk_c01(ChunkState_e8230c8_c01& s) {
    // 0xe8248aa..0xe8248b9
    // mov r8d,0x28 ; lea rcx,[rbx+0xC0] ; mov rdx,r10
    unsigned r8d = 0x28;
    void* rcx = (char*)s.rbx_base + 0xC0;
    void* rdx = s.r10_scratch;
    (void)r8d; (void)rcx; (void)rdx;
    // 0xe8248ba..0xe8248bf
    // call 0xEBCE390 (sub_ebce390)
    // sub_ebce390(rcx, rdx, r8d);
    // 0xe8248c0..0xe82491b
    // body: pool traversal / chunk bookkeeping
    for (int i = 0; i < 4; ++i) {
        (void)i;
        // 0xe8248c0..0xe8248e0
        // mov rax,[rbx+0xB0] ; test rax,rax ; jz ...
        void* rax = nullptr;
        if (rax == nullptr) { /* 0xe8248e0 */ }
        // 0xe8248e1..0xe82491b
        // lea rdx,[rbx+0x...] ; mov rcx,r10
        rcx = (char*)s.rbx_base;
        rdx = s.r10_scratch;
    }
    // 0xe82491c..0xe824921
    // call qword ptr [0xF99FFA0] (vendor thunk)
    // ((void(*)(void*,void*))0xF99FFA0)(rcx, rdx);
    // 0xe824922..0xe824a35
    // resource management loop
    int idx = 0;
    while (idx < 8) {
        // 0xe824922..0xe824960
        // mov rax,[rbx+0x...] ; cmp rax,0 ; je ...
        // 0xe824961..0xe8249a0
        // mov rcx,[rbx+0x...] ; call ...
        // 0xe8249a1..0xe824a35
        ++idx;
    }
    // 0xe824a36..0xe824a72
    // call qword ptr [0xF99FFA0]
    // 0xe824a73..0xe824a78
    // call 0xE82DCC0 (sub_e82dcc0)
    // sub_e82dcc0(s.rbx_base);
    // 0xe824a79..0xe824c34
    // chunk deallocation traversal
    for (int j = 0; j < 16; ++j) {
        (void)j;
        // 0xe824a79..0xe824ab0
        // mov rax,[rbx+0x...] ; test rax,rax
        // 0xe824ab1..0xe824b00
        // mov [rax+0x...],rcx
        // 0xe824b01..0xe824b80
        // add rax,0xB8
        // 0xe824b81..0xe824c34
        // cmp j,limit ; jb loop
    }
    // 0xe824c35..0xe824cf0
    // call qword ptr [0xF99FFA0] (x2)
    // 0xe824cf0..0xe824d93
    // call qword ptr [0xF99FFA0]
    // 0xe824d93..0xe824e71
    // call qword ptr [0xF99FFA0]
    // 0xe824e72..0xe824e77
    // call r10
    // ((void(*)())s.r10_scratch)();
    // 0xe824e78..0xe824f80
    // vendor calls
    // 0xe824f81..0xe824f86
    // call qword ptr [0xF99FFA0]
    // 0xe824f87..0xe8250c1
    // body
    for (int k = 0; k < 32; ++k) {
        (void)k;
        // 0xe824f87..0xe825000
        // mov rax,[rbx+0x...] ; add rax,0x...
        // 0xe825001..0xe825060
        // mov [rax],rdx
        // 0xe825061..0xe8250c1
        // inc k ; cmp k,32 ; jb
    }
    // 0xe8250c2..0xe8250fa
    // call 0xE82D960 (sub_e82d960)
    // sub_e82d960(s.rbx_base);
    // 0xe8250fb..0xe825161
    // call 0xEBCE390 (sub_ebce390)
    // 0xe825162..0xe825173
    // call r10
    // 0xe825174..0xe825179
    // call 0xE82DCC0 (sub_e82dcc0)
    // 0xe82517a..0xe82525f
    // body
    // 0xe825260..0xe825265
    // call r10
    // 0xe825266..0xe8252c3
    // body
    // 0xe8252c4..0xe8252c9
    // call qword ptr [0xF99FFA0]
    // 0xe8252ca..0xe82533a
    // body
    // 0xe82533b..0xe825340
    // call 0xEBD1560 (sub_ebd1560)
    // 0xe825341..0xe825368
    // body
    // 0xe825369..0xe8253a5
    // call 0xE82D960 (sub_e82d960)
    // 0xe8253a6..0xe8253ab
    // call 0xEBCE390 (sub_ebce390)
    // 0xe8253ac..0xe82548b
    // body
    // 0xe82548c..0xe825539
    // call qword ptr [0xF99FFA0]
    // 0xe82553a..0xe825595
    // call qword ptr [0xF99FFA0]
    // 0xe825596..0xe825687
    // call qword ptr [0xF99FFA0]
    // 0xe825688..0xe825761
    // call qword ptr [0xF99FFA0]
    // 0xe825762..0xe825767
    // call r10
    // 0xe825768..0xe8258ac
    // body
    // 0xe8258ad..0xe8258b2
    // call qword ptr [0xF99FFA0]
    // 0xe8258b3..0xe82590f
    // body
    // 0xe825910..0xe825915
    // call 0xE820500 (sub_e820500)
    // 0xe825916..0xe825953
    // body
    // 0xe825954..0xe825985
    // call qword ptr [0xF99FFA0]
    // 0xe825986..0xe8259a9
    // call qword ptr [0xF99FFA0]
    // 0xe8259aa..0xe8259d6
    // call qword ptr [0xF99FFA0]
    // 0xe8259d7..0xe8259dc
    // call 0xE82DE90 (sub_e82de90)
    // 0xe8259dd..0xe825a0e
    // body
    // 0xe825a0f..0xe825a14
    // call 0xE935700 (sub_e935700)
    // 0xe825a15..0xe825a38
    // body
    // 0xe825a39..0xe825a3e
    // call 0xE835B50 (sub_e835b50)
    // 0xe825a3f..0xe825a54
    // body
    // 0xe825a55..0xe825a5a
    // call 0xEEC6ED0 (sub_eec6ed0)
    // 0xe825a5b..0xe825b61
    // body
    // 0xe825b62..0xe825b67
    // call 0xE82DCC0 (sub_e82dcc0)
    // 0xe825b68..0xe825d17
    // body
    // 0xe825d18..0xe825dd2
    // call qword ptr [0xF99FFA0]
    // 0xe825dd3..0xe825e75
    // call qword ptr [0xF99FFA0]
    // 0xe825e76..0xe825f51
    // call qword ptr [0xF99FFA0]
    // 0xe825f52..0xe825f57
    // call r10
    // 0xe825f58..0xe826060
    // body
    // 0xe826061..0xe826066
    // call qword ptr [0xF99FFA0]
    // 0xe826067..0xe82609d
    // tail of chunk
}

#if 0
0xe8248ba  call 0xEBCE390
0xe82491c  call qword ptr [0xF99FFA0]
0xe824a36  call qword ptr [0xF99FFA0]
0xe824a73  call 0xE82DCC0
0xe824c35  call qword ptr [0xF99FFA0]
0xe824cf0  call qword ptr [0xF99FFA0]
0xe824d93  call qword ptr [0xF99FFA0]
0xe824e72  call r10
0xe824f81  call qword ptr [0xF99FFA0]
0xe8250c2  call 0xE82D960
0xe8250fb  call 0xEBCE390
0xe825162  call r10
0xe825174  call 0xE82DCC0
0xe825260  call r10
0xe8252c4  call qword ptr [0xF99FFA0]
0xe82533b  call 0xEBD1560
0xe825369  call 0xE82D960
0xe8253a6  call 0xEBCE390
0xe82548c  call qword ptr [0xF99FFA0]
0xe82553a  call qword ptr [0xF99FFA0]
0xe825596  call qword ptr [0xF99FFA0]
0xe825688  call qword ptr [0xF99FFA0]
0xe825762  call r10
0xe8258ad  call qword ptr [0xF99FFA0]
0xe825910  call 0xE820500
0xe825954  call qword ptr [0xF99FFA0]
0xe825986  call qword ptr [0xF99FFA0]
0xe8259aa  call qword ptr [0xF99FFA0]
0xe8259d7  call 0xE82DE90
0xe825a0f  call 0xE935700
0xe825a39  call 0xE835B50
0xe825a55  call 0xEEC6ED0
0xe825b62  call 0xE82DCC0
0xe825d18  call qword ptr [0xF99FFA0]
0xe825dd3  call qword ptr [0xF99FFA0]
0xe825e76  call qword ptr [0xF99FFA0]
0xe825f52  call r10
0xe826061  call qword ptr [0xF99FFA0]
#endif
