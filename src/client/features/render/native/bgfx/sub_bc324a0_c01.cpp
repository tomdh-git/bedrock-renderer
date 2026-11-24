// LIFT 0xbc324a0 size 0x1e7c 1.26.62.01 sub_bc324a0
// CHUNK 0xbc332ae..0xbc3431c

// chunk state documented in docs/functions/bc324a0.md section 'Chunk state'
struct ChunkState_bc324a0_c01 {
    void* rbp_frame_base;
    void* r12_ctx;
    void* r15_scratch;
    void* rsi_scratch;
    void* rdi_scratch;
    void* rbx_scratch;
};

static inline void sub_bc324a0_chunk01(ChunkState_bc324a0_c01& s) {
    // 0xbc332ae..0xbc332c6
    // cmp rsi,0xF; jbe 0xBC332D0; lea rcx,[rbp+0xA60]; mov rdx,rsi; call 0x9D6D0; jmp 0xBC332F1
    // 0xbc332d0..0xbc332e9: mov [rbp+0xA70],rsi; lea rcx,[rbp+0xA60]; mov rdx,r9; mov r8,rsi; call 0xEEC6DE0; mov byte ptr [rbp+rsi+0xA60],0

    // 0xbc332f1..0xbc33325
    // mov [rbp+0xBD8],r14; mov r14,r12; mov r12,r15; mov rax,[rbp+0xA88]; mov [rbp+0xA58],rax; mov r15,[rbp+0xC80]; mov r13,[r15+0x10]; cmp qword ptr [r15+0x18],0x10; jb 0xBC33328; mov rax,[rbp+0xC80]; mov r15,[rax]

    // 0xbc33328..0xbc333a6
    // movaps [rbp+0xB70],xmm6; mov qword ptr [rbp+0xB80],0; mov qword ptr [rbp+0xB88],0xF; test r13,r13; je 0xBC342EB; movaps [rbp-0x50],xmm6; js 0xBC3430A; mov edi,0xF; lea rsi,[rbp-0x50]; cmp r13,0x10; jb 0xBC333DE; mov rdx,r13; or rdx,0xF; cmp rdx,0x17; mov edi,0x16; cmovae rdi,rdx; mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; cmp rdx,0xFFF; jb 0xBC333C0; lea rbx,[rdi+0x28]; mov rdx,rbx; call qword ptr [0xF99FFA0]; mov rsi,rax; test rax,rax; je 0xBC34226

    // 0xbc333ac..0xbc333bd
    // mov rax,rsi; add rsi,0x27; and rsi,0xFFFFFFFFFFFFFFE0; mov [rsi-8],rax; jmp 0xBC333DA

    // 0xbc333c0..0xbc333d4
    // lea rbx,[rdi+1]; mov rdx,rbx; call qword ptr [0xF99FFA0]; mov rsi,rax; test rax,rax; je 0xBC34234

    // 0xbc333da..0xbc333de
    // mov [rbp-0x50],rsi

    // 0xbc333de..0xbc3345f
    // mov [rbp-0x40],r13; mov [rbp-0x38],rdi; mov rcx,rsi; mov rdx,r15; mov r8,r13; call 0xEEC6EC0; mov byte ptr [rsi+r13],0; mov rax,[rbp+0xB88]; cmp rax,0x10; lea rsi,[rbp+0xA58]; mov r13,[rbp+0xBB0]; lea rdi,[rbp+0x5B0]; lea rbx,[rbp+0x400]; mov r15,r12; mov r12,r14; mov r14,[rbp+0xBD8]; jb 0xBC33467; mov rcx,[rbp+0xB70]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC33462; mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0; add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc33462
    // call 0xE935700

    // 0xbc33467..0xbc334a1
    // movaps xmm0,[rbp-0x50]; movaps xmm1,[rbp-0x40]; movaps [rbp+0xB60],xmm1; movaps [rbp+0xB50],xmm0; movaps [rbp+0x590],xmm0; movaps [rbp+0x5A0],xmm1; mov qword ptr [rbp+0xB60],0; mov qword ptr [rbp+0xB68],0xF; mov byte ptr [rbp+0xB50],0

    // 0xbc334a8..0xbc334bd
    // movaps xmm0,[rbp+0x840]; movaps [rbp+0x5B0],xmm0; mov rax,[rbp+0x850]; mov [rbp+0x5C0],rax

    // 0xbc334c4..0xbc334cf
    // movups [rsi-0x210],xmm6; movups [rdi+0x18],xmm6; mov qword ptr [rdi+0x28],0

    // 0xbc334d7..0xbc334eb
    // movzx eax,byte ptr [rbp+0x870]; movzx ecx,byte ptr [rbp+0x8A0]; mov [rbp+0x5E0],al; mov byte ptr [rbp+0x610],0

    // 0xbc334f2..0xbc33533
    // cmp cl,1; jne 0xBC3353A; mov rax,[rbp+0x898]; mov qword ptr [rbp+0x898],0; movups xmm0,[rbp+0x878]; movups xmm1,[rbp+0x888]; movups [rbp+0x5E8],xmm0; movups [rbp+0x888],xmm6; movups [rbp+0x5F8],xmm1; mov [rbp+0x608],rax; mov byte ptr [rbp+0x610],1

    // 0xbc3353a..0xbc33541
    // movups xmm0,[rsi-0x1B0]; movups [rdi+0x68],xmm0

    // 0xbc33545..0xbc33576
    // movups xmm0,[rbp+0x8B8]; movups xmm1,[rbp+0x8C8]; movups xmm2,[rbp+0x8D8]; movups xmm3,[rbp+0x8E8]; movups [rbp+0x628],xmm0; movups [rbp+0x638],xmm1; movups [rbp+0x648],xmm2; movups [rbp+0x658],xmm3

    // 0xbc3357d..0xbc335ae
    // movups xmm0,[rbp+0x8F8]; movups [rbp+0x668],xmm0; movups xmm0,[rbp+0x908]; movups [rbp+0x678],xmm0; movups xmm0,[rbp+0x918]; movups [rbp+0x688],xmm0; movups xmm0,[rbp+0x928]; movups [rbp+0x698],xmm0

    // 0xbc335b5..0xbc335bb
    // mov eax,[rsi-0x110]; mov [rdi+0x108],eax

    // 0xbc335c1..0xbc335c8
    // movups xmm0,[rsi-0x120]; movups [rdi+0xF8],xmm0

    // 0xbc335cf..0xbc335e4
    // movups xmm0,[rbp+0x94C]; movups xmm1,[rbp+0x95C]; movups [rbp+0x6BC],xmm0; movups [rbp+0x6CC],xmm1

    // 0xbc335eb..0xbc33638
    // movups xmm0,[rbp+0x96C]; movups [rbp+0x6DC],xmm0; movups xmm0,[rbp+0x97C]; movups [rbp+0x6EC],xmm0; movups xmm0,[rbp+0x98C]; movups [rbp+0x6FC],xmm0; movups xmm0,[rbp+0x99C]; movups [rbp+0x70C],xmm0; movups xmm0,[rbp+0x9AC]; movups [rbp+0x71C],xmm0; movups xmm0,[rbp+0x9BC]; movups [rbp+0x72C],xmm0

    // 0xbc3363f..0xbc33646
    // movups xmm0,[rsi-0x8C]; movups [rdi+0x18C],xmm0

    // 0xbc3364d
    // mov byte ptr [rbp+0x7C4],0

    // 0xbc33654..0xbc3365b
    // cmp byte ptr [rbp+0xA54],1; jne 0xBC336D8

    // 0xbc3365d..0xbc3366c
    // movups xmm0,[rsi-0x7C]; movups xmm1,[rsi-0x6C]; movups [rdi+0x1AC],xmm1; movups [rdi+0x19C],xmm0

    // 0xbc33673
    // mov byte ptr [rbp+0x780],0

    // 0xbc3367a..0xbc33681
    // cmp byte ptr [rbp+0xA10],1; jne 0xBC336A5

    // 0xbc33683..0xbc3369e
    // movzx eax,byte ptr [rbp+0x9FC]; mov [rbp+0x76C],al; movaps xmm0,[rbp+0xA00]; movaps [rbp+0x770],xmm0; mov byte ptr [rbp+0x780],1

    // 0xbc336a5..0xbc336ca
    // movups xmm0,[rsi-0x44]; movups xmm1,[rsi-0x34]; movups xmm2,[rsi-0x24]; movups xmm3,[rsi-0x16]; movups [rdi+0x202],xmm3; movups [rdi+0x1F4],xmm2; movups [rdi+0x1E4],xmm1; movups [rdi+0x1D4],xmm0

    // 0xbc336d1
    // mov byte ptr [rbp+0x7C4],1

    // 0xbc336d8..0xbc336f8
    // mov qword ptr [rbp+0x7F0],0; lea rax,[rbp+0xA60]; movups xmm0,[rax]; movups xmm1,[rax+0x10]; movups [rdi+0x230],xmm1; movups [rdi+0x220],xmm0

    // 0xbc336ff..0xbc33715
    // mov qword ptr [rbp+0xA70],0; mov qword ptr [rbp+0xA78],0xF; mov byte ptr [rbp+0xA60],0

    // 0xbc3371c..0xbc33723
    // mov rax,[rbp+0xA58]; mov [rbp+0x7C8],rax

    // 0xbc3372a..0xbc3373f
    // lea rax,[0xF43FCB0]; mov [rbp+0x7F8],rax; lea rax,[rbp+0x7F8]; mov [rbp+0x830],rax

    // 0xbc33746..0xbc33754
    // lea rcx,[rbp+0xAF8]; mov rdx,[rbp+0xC80]; call 0x76A8A0

    // 0xbc33759..0xbc337b0
    // mov rax,[rbp+0xAF8]; mov rdx,[rbp+0xB00]; mov rcx,[rbp+0xB18]; mov qword ptr [rbp+0xB18],0xF; mov byte ptr [rbp+0xB00],0; mov qword ptr [rbp+0xB98],0; mov [rbp+0xB78],rdx; mov [rbp+0xB70],rax; mov qword ptr [rbp+0xB88],0; mov qword ptr [rbp+0xB90],0xF; mov byte ptr [rbp+0xB78],0

    // 0xbc337b7..0xbc337da
    // mov r8,[rbp+0xCD0]; movups xmm0,[r8]; movups xmm1,[r8+0x10]; movups xmm2,[r8+0x20]; lea r10,[rbp-0x48]; movups [r10+0x48],xmm2; movups [r10+0x38],xmm1; movups [r10+0x28],xmm0

    // 0xbc337df..0xbc337fe
    // mov r8,[rbp+0xCC8]; movups xmm0,[r8]; movups xmm1,[r8+0x10]; movups xmm2,[r8+0x20]; movups [r10+0x78],xmm2; movups [r10+0x68],xmm1; movups [r10+0x58],xmm0

    // 0xbc33803..0xbc33828
    // mov r8,[rbp+0xCC0]; movups xmm0,[r8]; movups xmm1,[r8+0x10]; movups xmm2,[r8+0x20]; movups [r10+0xA8],xmm2; movups [r10+0x98],xmm1; movups [r10+0x88],xmm0

    // 0xbc33830..0xbc33855
    // mov r8,[rbp+0xCB8]; movups xmm0,[r8]; movups xmm1,[r8+0x10]; movups xmm2,[r8+0x20]; movups [r10+0xD8],xmm2; movups [r10+0xC8],xmm1; movups [r10+0xB8],xmm0

    // 0xbc3385d..0xbc33882
    // mov r8,[rbp+0xCB0]; movups xmm0,[r8]; movups xmm1,[r8+0x10]; movups xmm2,[r8+0x20]; movups [r10+0x108],xmm2; movups [r10+0xF8],xmm1; movups [r10+0xE8],xmm0

    // 0xbc3388a..0xbc338a0
    // mov r9,[rbp+0xCA8]; mov r8,[r9+0x10]; mov [r10+0x128],r8; movups xmm0,[r9]; movups [r10+0x118],xmm0

    // 0xbc338a8..0xbc338be
    // mov r9,[rbp+0xCA0]; mov r8,[r9+0x10]; mov [r10+0x140],r8; movups xmm0,[r9]; movups [r10+0x130],xmm0

    // 0xbc338c6..0xbc338d1
    // mov r8,[rbp+0xC98]; movups xmm0,[r8]; movups [r10+0x148],xmm0

    // 0xbc338d9..0xbc338f1
    // mov r8,[rbp+0xC90]; movups xmm0,[r8]; movups xmm1,[r8+0x10]; movups [r10+0x168],xmm1; movups [r10+0x158],xmm0

    // 0xbc338f9..0xbc3390f
    // mov r9,[rbp+0xC88]; mov r8,[r9+0x10]; mov [r10+0x188],r8; movups xmm0,[r9]; movups [r10+0x178],xmm0

    // 0xbc33917..0xbc33940
    // mov qword ptr [rbp-0x28],0; mov [rbp-0x48],rdx; mov rdx,[rbp+0xB08]; mov [rbp+0xB80],rdx; movups xmm0,[rbp+0xB08]; movups [rbp-0x40],xmm0; mov [rbp-0x30],rcx; mov [rbp-0x50],rax

    // 0xbc33944..0xbc33959
    // movaps xmm0,[rbp+0x590]; movaps xmm1,[rbp+0x5A0]; movaps [rbp+0x150],xmm0; movaps [rbp+0x160],xmm1

    // 0xbc33960..0xbc33976
    // mov qword ptr [rbp+0x5A0],0; mov qword ptr [rbp+0x5A8],0xF; mov byte ptr [rbp+0x590],0

    // 0xbc3397d..0xbc33992
    // movaps xmm0,[rbp+0x5B0]; movaps [rbp+0x170],xmm0; mov rax,[rbp+0x5C0]; mov [rbp+0x180],rax

    // 0xbc33999
    // mov qword ptr [rbp+0xB10],0

    // 0xbc339a4..0xbc339af
    // movups [rdi+8],xmm6; movups [rbx-0x278],xmm6; mov qword ptr [rbx-0x268],0

    // 0xbc339ba..0xbc339c1
    // movzx eax,byte ptr [rbp+0x5E0]; mov [rbp+0x1A0],al

    // 0xbc339c7..0xbc339ce
    // movzx eax,byte ptr [rbp+0x610]; mov byte ptr [rbp+0x1D0],0

    // 0xbc339d5..0xbc339d7
    // cmp al,1; jne 0xBC33A1C

    // 0xbc339d9..0xbc33a0e
    // mov rax,[rbp+0x608]; mov qword ptr [rbp+0x608],0; movups xmm0,[rbp+0x5E8]; movups xmm1,[rbp+0x5F8]; movups [rbp+0x1A8],xmm0; movups [rbp+0x5F8],xmm6; movups [rbp+0x1B8],xmm1; mov [rbp+0x1C8],rax

    // 0xbc33a15
    // mov byte ptr [rbp+0x1D0],1

    // 0xbc33a1c..0xbc33a20
    // movups xmm0,[rdi+0x68]; movups [rbx-0x228],xmm0

    // 0xbc33a27..0xbc33a58
    // movups xmm0,[rbp+0x628]; movups xmm1,[rbp+0x638]; movups xmm2,[rbp+0x648]; movups xmm3,[rbp+0x658]; movups [rbp+0x1E8],xmm0; movups [rbp+0x1F8],xmm1; movups [rbp+0x208],xmm2; movups [rbp+0x218],xmm3

    // 0xbc33a5f..0xbc33a90
    // movups xmm0,[rbp+0x668]; movups [rbp+0x228],xmm0; movups xmm0,[rbp+0x678]; movups [rbp+0x238],xmm0; movups xmm0,[rbp+0x688]; movups [rbp+0x248],xmm0; movups xmm0,[rbp+0x698]; movups [rbp+0x258],xmm0

    // 0xbc33a97..0xbc33a9d
    // mov eax,[rdi+0x108]; mov [rbx-0x188],eax

    // 0xbc33aa3..0xbc33aaa
    // movups xmm0,[rdi+0xF8]; movups [rbx-0x198],xmm0

    // 0xbc33ab1..0xbc33ac6
    // movups xmm0,[rbp+0x6BC]; movups xmm1,[rbp+0x6CC]; movups [rbp+0x27C],xmm0; movups [rbp+0x28C],xmm1

    // 0xbc33acd..0xbc33b1a
    // movups xmm0,[rbp+0x6DC]; movups [rbp+0x29C],xmm0; movups xmm0,[rbp+0x6EC]; movups [rbp+0x2AC],xmm0; movups xmm0,[rbp+0x6FC]; movups [rbp+0x2BC],xmm0; movups xmm0,[rbp+0x70C]; movups [rbp+0x2CC],xmm0; movups xmm0,[rbp+0x71C]; movups [rbp+0x2DC],xmm0; movups xmm0,[rbp+0x72C]; movups [rbp+0x2EC],xmm0

    // 0xbc33b21..0xbc33b28
    // movups xmm0,[rdi+0x18C]; movups [rbx-0x104],xmm0

    // 0xbc33b2f
    // mov byte ptr [rbp+0x384],0

    // 0xbc33b36..0xbc33b3d
    // cmp byte ptr [rbp+0x7C4],1; jne 0xBC33BD0

    // 0xbc33b43..0xbc33b58
    // movups xmm0,[rdi+0x19C]; movups xmm1,[rdi+0x1AC]; movups [rbx-0xE4],xmm1; movups [rbx-0xF4],xmm0

    // 0xbc33b5f
    // mov byte ptr [rbp+0x340],0

    // 0xbc33b66..0xbc33b6d
    // cmp byte ptr [rbp+0x780],1; jne 0xBC33B91

    // 0xbc33b6f..0xbc33b8a
    // movzx eax,byte ptr [rbp+0x76C]; mov [rbp+0x32C],al; movaps xmm0,[rbp+0x770]; movaps [rbp+0x330],xmm0; mov byte ptr [rbp+0x340],1

    // 0xbc33b91..0xbc33bc2
    // movups xmm0,[rdi+0x1D4]; movups xmm1,[rdi+0x1E4]; movups xmm2,[rdi+0x1F4]; movups xmm3,[rdi+0x202]; movups [rbx-0x8E],xmm3; movups [rbx-0x9C],xmm2; movups [rbx-0xAC],xmm1; movups [rbx-0xBC],xmm0

    // 0xbc33bc9
    // mov byte ptr [rbp+0x384],1

    // 0xbc33bd0
    // mov qword ptr [rbp+0x3B0],0

    // 0xbc33bdb..0xbc33bed
    // movups xmm0,[rdi+0x220]; movups xmm1,[rdi+0x230]; movups [rbx-0x60],xmm1; movups [rbx-0x70],xmm0

    // 0xbc33bf1..0xbc33c07
    // mov qword ptr [rbp+0x7E0],0; mov qword ptr [rbp+0x7E8],0xF; mov byte ptr [rbp+0x7D0],0

    // 0xbc33c0e..0xbc33c1c
    // mov rax,[rbp+0x7C8]; mov rcx,[rbp+0x830]; mov [rbp+0x388],rax

    // 0xbc33c23
    // mov qword ptr [rbp+0x3F0],0

    // 0xbc33c2e..0xbc33c31
    // test rcx,rcx; je 0xBC33C9C

    // 0xbc33c33..0xbc33c3d
    // lea rax,[rbp+0x7F8]; cmp rcx,rax; je 0xBC33C50

    // 0xbc33c3f..0xbc33c46
    // mov [rbp+0x3F0],rcx; jmp 0xBC33C91

    // 0xbc33c50..0xbc33c64
    // mov rax,[rcx]; mov rax,[rax+8]; lea rdx,[rbp+0x3B8]; call qword ptr [0xF99FFA0]; mov [rbp+0x3F0],rax

    // 0xbc33c6b..0xbc33c75
    // mov rcx,[rbp+0x830]; test rcx,rcx; je 0xBC33C9C

    // 0xbc33c77..0xbc33c8b
    // lea rax,[rbp+0x7F8]; cmp rcx,rax; setne dl; mov rax,[rcx]; mov rax,[rax+0x20]; call qword ptr [0xF99FFA0]

    // 0xbc33c91
    // mov qword ptr [rbp+0x830],0

    // 0xbc33c9c
    // mov qword ptr [rbp+0x420],0

    // 0xbc33ca7..0xbc33cb6
    // lea rcx,[rbp-0x48]; movups xmm0,[rcx]; movups xmm1,[rcx+0x10]; movups [rbx+0x10],xmm1; movups [rbx],xmm0

    // 0xbc33cb9..0xbc33cc9
    // mov qword ptr [rbp-0x38],0; mov qword ptr [rbp-0x30],0xF; mov byte ptr [rbp-0x48],0

    // 0xbc33ccd..0xbc33cd1
    // mov rax,[rbp-0x50]; mov [rbp+0x3F8],rax

    // 0xbc33cd8..0xbc33cec
    // movups xmm0,[rcx+0x28]; movups xmm1,[rcx+0x38]; movups xmm2,[rcx+0x48]; movups [rbx+0x48],xmm2; movups [rbx+0x38],xmm1; movups [rbx+0x28],xmm0

    // 0xbc33cf0..0xbc33d04
    // movups xmm0,[rcx+0x58]; movups xmm1,[rcx+0x68]; movups xmm2,[rcx+0x78]; movups [rbx+0x78],xmm2; movups [rbx+0x68],xmm1; movups [rbx+0x58],xmm0

    // 0xbc33d08..0xbc33d2b
    // movups xmm0,[rcx+0x88]; movups xmm1,[rcx+0x98]; movups xmm2,[rcx+0xA8]; movups [rbx+0xA8],xmm2; movups [rbx+0x98],xmm1; movups [rbx+0x88],xmm0

    // 0xbc33d32..0xbc33d55
    // movups xmm0,[rcx+0xB8]; movups xmm1,[rcx+0xC8]; movups xmm2,[rcx+0xD8]; movups [rbx+0xD8],xmm2; movups [rbx+0xC8],xmm1; movups [rbx+0xB8],xmm0

    // 0xbc33d5c..0xbc33d7f
    // movups xmm0,[rcx+0xE8]; movups xmm1,[rcx+0xF8]; movups xmm2,[rcx+0x108]; movups [rbx+0x108],xmm2; movups [rbx+0xF8],xmm1; movups [rbx+0xE8],xmm0

    // 0xbc33d86..0xbc33d9b
    // mov rax,[rcx+0x128]; mov [rbx+0x128],rax; movups xmm0,[rcx+0x118]; movups [rbx+0x118],xmm0

    // 0xbc33da2..0xbc33db7
    // mov rax,[rcx+0x140]; mov [rbx+0x140],rax; movups xmm0,[rcx+0x130]; movups [rbx+0x130],xmm0

    // 0xbc33dbe..0xbc33dc5
    // movups xmm0,[rcx+0x148]; movups [rbx+0x148],xmm0

    // 0xbc33dcc..0xbc33de1
    // movups xmm0,[rcx+0x158]; movups xmm1,[rcx+0x168]; movups [rbx+0x168],xmm1; movups [rbx+0x158],xmm0

    // 0xbc33de8..0xbc33dfd
    // mov rax,[rcx+0x188]; mov [rbx+0x188],rax; movups xmm0,[rcx+0x178]; movups [rbx+0x178],xmm0

    // 0xbc33e04..0xbc33e12
    // mov rcx,[rbp+0xB28]; lea rdx,[rbp+0x150]; call 0xBC347B0

    // 0xbc33e17..0xbc33e23
    // mov rax,[rbp+0x418]; cmp rax,0x10; jb 0xBC33E5D

    // 0xbc33e25..0xbc33e37
    // mov rcx,[rbp+0x400]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC33E58

    // 0xbc33e39..0xbc33e48
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc33e4e..0xbc33e58
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc33e58
    // call 0xE935700

    // 0xbc33e5d..0xbc33e73
    // mov qword ptr [rbp+0x410],0; mov qword ptr [rbp+0x418],0xF; mov byte ptr [rbp+0x400],0

    // 0xbc33e7a..0xbc33e9a
    // mov rcx,[rbp+0x3F0]; test rcx,rcx; je 0xBC33EAB; lea rax,[rbp+0x3B8]; cmp rcx,rax; setne dl; mov rax,[rcx]; mov rax,[rax+0x20]; call qword ptr [0xF99FFA0]

    // 0xbc33ea0
    // mov qword ptr [rbp+0x3F0],0

    // 0xbc33eab..0xbc33eb6
    // mov rax,[rbp+0x3A8]; cmp rax,0x10; jb 0xBC33EF0

    // 0xbc33eb8..0xbc33eca
    // mov rcx,[rbp+0x390]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC33EEB

    // 0xbc33ecc..0xbc33edb
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc33ee1..0xbc33eeb
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc33eeb
    // call 0xE935700

    // 0xbc33ef0..0xbc33f06
    // mov qword ptr [rbp+0x3A0],0; mov qword ptr [rbp+0x3A8],0xF; mov byte ptr [rbp+0x390],0

    // 0xbc33f0d..0xbc33f14
    // cmp byte ptr [rbp+0x1D0],1; jne 0xBC33F32

    // 0xbc33f16..0xbc33f1e
    // cmp qword ptr [rbp+0x1B8],0; je 0xBC33F32

    // 0xbc33f20..0xbc33f27
    // movups [rbx-0x248],xmm6; mov qword ptr [rbx-0x238],0

    // 0xbc33f32..0xbc33f39
    // lea rcx,[rbp+0x170]; call 0x655CEA0

    // 0xbc33f3e..0xbc33f49
    // mov rax,[rbp+0x168]; cmp rax,0x10; jb 0xBC33F83

    // 0xbc33f4b..0xbc33f5d
    // mov rcx,[rbp+0x150]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC33F7E

    // 0xbc33f5f..0xbc33f6e
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc33f74..0xbc33f7e
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc33f7e
    // call 0xE935700

    // 0xbc33f83..0xbc33f99
    // mov qword ptr [rbp+0x160],0; mov qword ptr [rbp+0x168],0xF; mov byte ptr [rbp+0x150],0

    // 0xbc33fa0..0xbc33fab
    // mov rax,[rbp+0xB90]; cmp rax,0x10; jb 0xBC33FE5

    // 0xbc33fad..0xbc33fbf
    // mov rcx,[rbp+0xB78]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC33FE0

    // 0xbc33fc1..0xbc33fd0
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc33fd6..0xbc33fe0
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc33fe0
    // call 0xE935700

    // 0xbc33fe5..0xbc33ff0
    // mov rax,[rbp+0xB18]; cmp rax,0x10; jb 0xBC3402A

    // 0xbc33ff2..0xbc34004
    // mov rcx,[rbp+0xB00]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC34025

    // 0xbc34006..0xbc34015
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc3401b..0xbc34025
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc34025
    // call 0xE935700

    // 0xbc3402a..0xbc34034
    // mov rcx,[rbp+0x830]; test rcx,rcx; je 0xBC3405B

    // 0xbc34036..0xbc3404a
    // lea rax,[rbp+0x7F8]; cmp rcx,rax; setne dl; mov rax,[rcx]; mov rax,[rax+0x20]; call qword ptr [0xF99FFA0]

    // 0xbc34050
    // mov qword ptr [rbp+0x830],0

    // 0xbc3405b..0xbc34066
    // mov rax,[rbp+0x7E8]; cmp rax,0x10; jb 0xBC340A0

    // 0xbc34068..0xbc3407a
    // mov rcx,[rbp+0x7D0]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC3409B

    // 0xbc3407c..0xbc3408b
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc34091..0xbc3409b
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc3409b
    // call 0xE935700

    // 0xbc340a0..0xbc340b6
    // mov qword ptr [rbp+0x7E0],0; mov qword ptr [rbp+0x7E8],0xF; mov byte ptr [rbp+0x7D0],0

    // 0xbc340bd..0xbc340c4
    // cmp byte ptr [rbp+0x610],1; jne 0xBC340DC

    // 0xbc340c6..0xbc340ce
    // cmp qword ptr [rbp+0x5F8],0; je 0xBC340DC

    // 0xbc340d0..0xbc340d4
    // movups [rdi+0x48],xmm6; mov qword ptr [rdi+0x58],0

    // 0xbc340dc..0xbc340df
    // mov rcx,rdi; call 0x655CEA0

    // 0xbc340e4..0xbc340f6
    // mov rax,[rbp+0x5A8]; cmp rax,0x10; mov rdi,[rbp+0xBE8]; jb 0xBC34130

    // 0xbc340f8..0xbc3410a
    // mov rcx,[rbp+0x590]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC3412B

    // 0xbc3410c..0xbc3411b
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc34121..0xbc3412b
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc3412b
    // call 0xE935700

    // 0xbc34130..0xbc34146
    // mov qword ptr [rbp+0x5A0],0; mov qword ptr [rbp+0x5A8],0xF; mov byte ptr [rbp+0x590],0

    // 0xbc3414d..0xbc34158
    // mov rax,[rbp+0xB68]; cmp rax,0x10; jb 0xBC34192

    // 0xbc3415a..0xbc3416c
    // mov rcx,[rbp+0xB50]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC3418D

    // 0xbc3416e..0xbc3417d
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc34183..0xbc3418d
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc3418d
    // call 0xE935700

    // 0xbc34192..0xbc3419d
    // mov rax,[rbp+0xA78]; cmp rax,0x10; jb 0xBC341D7

    // 0xbc3419f..0xbc341b1
    // mov rcx,[rbp+0xA60]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC341D2

    // 0xbc341b3..0xbc341c2
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc341c8..0xbc341d2
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc341d2
    // call 0xE935700

    // 0xbc341d7..0xbc341ed
    // mov qword ptr [rbp+0xA70],0; mov qword ptr [rbp+0xA78],0xF; mov byte ptr [rbp+0xA60],0

    // 0xbc341f4..0xbc341fb
    // cmp byte ptr [rbp+0x8A0],1; jne 0xBC32ED0

    // 0xbc34201..0xbc34209
    // cmp qword ptr [rbp+0x888],0; je 0xBC32ED0

    // 0xbc3420f..0xbc34216
    // movups [rsi-0x1D0],xmm6; mov qword ptr [rsi-0x1C0],0

    // 0xbc34221
    // jmp 0xBC32ED0

    // 0xbc34226..0xbc3422f
    // mov rcx,rbx; call 0x9BC830; jmp 0xBC333AC

    // 0xbc34234..0xbc3423f
    // mov rcx,rbx; call 0x9BC830; xor esi,esi; jmp 0xBC333DA

    // 0xbc34250..0xbc3425b
    // mov rax,[rbp+0xAA8]; cmp rax,0x10; jb 0xBC32520

    // 0xbc34261..0xbc34273
    // mov rcx,[rbp+0xA90]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xBC34290

    // 0xbc34275..0xbc34284
    // mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae 0xBC342F0

    // 0xbc34286..0xbc34290
    // add rax,0x28; mov rdx,rax; mov rcx,r8

    // 0xbc34290
    // call 0xE935700

    // 0xbc34295..0xbc3429c
    // add r13,0x290; jmp 0xBC32527

    // 0xbc342a1..0xbc342ab
    // mov rcx,[rbp+0xAF0]; test rcx,rcx; je 0xBC32520

    // 0xbc342b1..0xbc342c5
    // mov rax,[rcx]; lea rdx,[rbp+0xAB8]; cmp rcx,rdx; setne dl; mov rax,[rax+0x20]; call qword ptr [0xF99FFA0]

    // 0xbc342cb
    // jmp 0xBC32520

    // 0xbc342d0..0xbc342ea
    // movaps xmm6,[rbp+0xC00]; add rsp,0xC98; pop rbx; pop rdi; pop rsi; pop r12; pop r13; pop r14; pop r15; pop rbp; ret

    // 0xbc342eb
    // call 0x78ED0

    // 0xbc342f0..0xbc34309
    // mov qword ptr [rsp+0x20],0; xor ecx,ecx; xor edx,edx; xor r8d,r8d; xor r9d,r9d; call qword ptr [0xF9A8C78]

    // 0xbc3430a
    // call 0x75720

    // 0xbc34310
    // call 0x75B60

    // 0xbc34316..0xbc3431b
    // call 0x75B60; int3

    (void)s;
}

#if 0
0xbc332be  call 0x9D6D0
0xbc332e4  call 0xEEC6DE0
0xbc33399  call qword ptr [0xF99FFA0]
0xbc333c7  call qword ptr [0xF99FFA0]
0xbc333ef  call 0xEEC6EC0
0xbc33462  call 0xE935700
0xbc33754  call 0x76A8A0
0xbc33c5e  call qword ptr [0xF99FFA0]
0xbc33c8b  call qword ptr [0xF99FFA0]
0xbc33e12  call 0xBC347B0
0xbc33e58  call 0xE935700
0xbc33e9a  call qword ptr [0xF99FFA0]
0xbc33eeb  call 0xE935700
0xbc33f39  call 0x655CEA0
0xbc33f7e  call 0xE935700
0xbc33fe0  call 0xE935700
0xbc34025  call 0xE935700
0xbc3404a  call qword ptr [0xF99FFA0]
0xbc3409b  call 0xE935700
0xbc340df  call 0x655CEA0
0xbc3412b  call 0xE935700
0xbc3418d  call 0xE935700
0xbc341d2  call 0xE935700
0xbc34229  call 0x9BC830
0xbc34237  call 0x9BC830
0xbc34290  call 0xE935700
0xbc342c5  call qword ptr [0xF99FFA0]
0xbc342eb  call 0x78ED0
0xbc34303  call qword ptr [0xF9A8C78]
0xbc3430a  call 0x75720
0xbc34310  call 0x75B60
0xbc34316  call 0x75B60
#endif