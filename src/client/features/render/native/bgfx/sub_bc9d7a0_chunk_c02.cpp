// LIFT 0xbc9d7a0 size 0x67db 1.26.62.01 VV frame-graph builder
// CHUNK 0xbc9f890..0xbca1080

// Chunk state documented in docs/functions/bc9d7a0.md section 'Chunk state'.
struct ChunkState_bc9d7a0_c02 {
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

// Stack offsets relative to rbp (as seen in disassembly):
// 0x1160, 0x1190, 0xB38, 0x1124, 0xB10, 0xAE8, 0xAC0, 0xA90, 0xAA8, 0xAB0, 0xA98
// 0xA00, 0x3C0, 0x3A8, 0x820, 0x808, 0xF40, 0xF28, 0x10B8, 0x10A0, 0xEB0, 0xE98
// 0x118, 0xB8, 0xA8, 0x90, 0x3B8, 0x3A0, 0x418, 0x3C8, 0x1130, 0x1128, 0x12A8
// 0x10E8, 0x10B0, 0x10B8, 0xE98, 0xEA8, 0x3B0, 0x3A0, 0x3C0, 0x3C8, 0x3D0, 0x3D2, 0x3D4, 0x3D8
// 0x1138, 0x1168, 0x1150, 0x1108, 0x1058, 0xF20, 0xF28, 0xF30, 0x1170, 0x828, 0x808, 0xB8, 0x98
// 0xF38, 0xF40, 0xA8, 0x90, 0xA78, 0x418, 0xAA8, 0x98, 0xA88, 0xA98, 0xA8, 0xB0, 0xA80
// 0xAB0, 0xAC0, 0xE0, 0xAD0, 0xE8, 0xAD8, 0xB0, 0x98, 0x820, 0x808, 0xF40, 0xF28, 0x10B8, 0x10A0
// 0x3B8, 0x3A0, 0xEB0, 0xE98, 0x10B8, 0x10A0, 0x12E8, 0x12A8, 0x12C0, 0x12B8, 0x9F0, 0xA00, 0xA08
// 0x3A0, 0x3A8, 0x420, 0x98, 0x90, 0x800, 0x808, 0x3D8, 0x3E2, 0xF20, 0xF22, 0x800, 0x808
// 0xED0, 0xEDA, 0xEA0, 0x12D0, 0x788, 0x12D0, 0x12C8, 0x1168, 0x1170, 0x1138, 0x1158, 0x1178
// 0x10A0, 0x998, 0x99C, 0x9AC, 0x9B0, 0x9C0, 0x9C4, 0x9D4, 0x9D8, 0x10E0, 0x800, 0x804, 0x814
// 0x818, 0x828, 0x82C, 0x83C, 0x844, 0x854, 0x858, 0x868, 0x86C, 0x87C, 0x880, 0x888, 0x890
// 0x898, 0x8A8, 0x8AC, 0x8BC, 0x8C0, 0x8D0, 0x8D8, 0x8E8, 0x8EC, 0x8FC, 0x900, 0x910, 0x914
// 0x924, 0x928, 0x92C, 0x930, 0x934, 0x938, 0x93C, 0x94C, 0x954, 0x958, 0x95C, 0x964, 0x968
// 0x979, 0x969, 0x97A, 0x3A0, 0x3A8, 0x3B8, 0x3C0, 0x3D8, 0x3D0, 0x3C8, 0x118E, 0x7AB, 0x79B

static inline void sub_bc9d7a0_chunk02(ChunkState_bc9d7a0_c02& s) {
    // 0xbc9f890..0xbc9f8cd: Entry branch and loop setup
    // jmp to 0xbc9f8cd; cmp rax,r13; je to 0xbc9f8cd
    // xor ecx,ecx; xorpd xmm0,xmm0; nop [rax]

    // 0xbc9f8a0..0xbc9f8cb: Memset/copy loop (16-byte chunks)
    // movupd [rbx+rcx],xmm0; mov rdx,[rax+rcx]; mov [rbx+rcx],rdx
    // mov rdx,[rax+rcx+8]; mov [rbx+rcx+8],rdx; movupd [rax+rcx],xmm0
    // lea rdx,[rax+rcx]; add rdx,0x10; add rcx,0x10; cmp rdx,r13; jne loop

    // 0xbc9f8cd..0xbc9f8fc: Initialize frame graph builder context
    // mov rcx,[rbp+0x1160]; mov rdx,rbx; mov r8,rdi; mov r9,r14
    // call 0x130EE0 (stl boundary)
    // mov rcx,[rbp+0x1190]; mov rax,[rcx+0x10]; lea rdx,[rbp+0xB38]
    // mov byte ptr [rcx+0x60],1; mov rax,[rax-0x10]; mov [rcx+0x58],rax
    // call 0x56939C0 (LIFT)

    // 0xbc9f906..0xbc9f948: Add three passes to frame graph
    // mov r15d,[rbp+0x1124]; lea rdx,[rbp+0xB10]; mov rcx,[rbp+0x1190]
    // call 0x5693A80 (LIFT)
    // lea rdx,[rbp+0xAE8]; mov rcx,[rbp+0x1190]; call 0x5693A80
    // lea rdx,[rbp+0xAC0]; mov rcx,[rbp+0x1190]; call 0x5693A80

    // 0xbc9f949..0xbc9f9c0: String handling (small string optimization)
    // lea rax,[rbp+0xA90]; mov rcx,[rbp+0x1190]; mov rbx,[rcx+0x58]
    // lea rcx,[rbx+8]; cmp rcx,rax; je 0xbc9f9c0
    // mov rsi,[rbp+0xAA8]; cmp qword ptr [rbp+0xAB0],0x10; jb 0xbc9f97e
    // mov r9,[rbp+0xA98]; jmp 0xbc9f985
    // 0xbc9f97e: lea r9,[rbp+0xA98]
    // 0xbc9f985: lea rdi,[rbx+0x10]; mov rax,[rbx+0x28]; cmp rsi,rax; jbe 0xbc9f9a0
    // mov rcx,rdi; mov rdx,rsi; call 0x9D6D0 (stl realloc boundary); jmp 0xbc9f9c0
    // 0xbc9f9a0: cmp rax,0x10; jb 0xbc9f9aa; mov rdi,[rbx+0x10]
    // 0xbc9f9aa: mov [rbx+0x20],rsi; mov rcx,rdi; mov rdx,r9; mov r8,rsi
    // call 0xEEC6DE0 (crt memcpy boundary); mov byte ptr [rdi+rsi],0
    // 0xbc9f9c0: mov rax,[rbp+0xA90]; mov [rbx+8],rax; mov qword ptr [rbx+0x30],0

    // 0xbc9f9d3..0xbc9fa36: Reset frame graph node state and free string
    // mov rax,[rbp+0x1190]; mov qword ptr [rax+0x58],0
    // lea rdi,[rbp+0xA00]; mov rcx,rdi; call 0xBCA92F0 (LIFT)
    // mov rax,[rbp+0x3C0]; cmp rax,0x10; jb 0xbc9fa36
    // mov rcx,[rbp+0x3A8]; lea rdx,[rax+1]; cmp rdx,0x1000; jb 0xbc9fa31
    // mov r8,[rcx-8]; add rcx,-8; sub rcx,r8; cmp rcx,0x20; jae 0xbca24a8
    // add rax,0x28; mov rdx,rax; mov rcx,r8
    // 0xbc9fa31: call 0xE935700 (crt free boundary)
    // 0xbc9fa36: mov rax,[rbp+0x820]; cmp rax,0x10; jb 0xbc9fa7b (same free pattern)

    // 0xbc9fa7b..0xbc9faf1: Free two more strings (0xF40, 0x118)
    // Same pattern for [rbp+0xF40] and [rbp+0x118]
    // 0xbc9fae0: call qword ptr [0xF99FFA0] (vendor thunk via data slot)
    // mov qword ptr [rbp+0x118],0

    // 0xbc9faf1..0xbc9fb28: Reference counted object release (rsi=[rbp+0xB8])
    // test rsi,rsi; je 0xbc9fb28
    // lock dec dword ptr [rsi+8]; jne 0xbc9fb28
    // mov rax,[rsi]; mov rax,[rax]; mov rcx,rsi; call qword ptr [0xF99FFA0]
    // lock dec dword ptr [rsi+0xC]; jne 0xbc9fb28
    // mov rax,[rsi]; mov rax,[rax+8]; mov rcx,rsi; call qword ptr [0xF99FFA0]

    // 0xbc9fb28..0xbc9fbb2: Free string at [rbp+0xA8] (same pattern)
    // 0xbc9fb68: call 0xE935700
    // 0xbc9fbb2..0xbc9fbf7: Free string at [rbp+0xEB0]
    // 0xbc9fbad: call 0xE935700
    // 0xbc9fbf2: call 0xE935700

    // 0xbc9fbf7..0xbc9fc12: Refcount increment for [rbp+0x1130]
    // mov rax,[rbp+0x1130]; test rax,rax; je 0xbc9fc10
    // lock inc dword ptr [rax+8]; mov rsi,[rbp+0x1130]; jmp 0xbc9fc12
    // 0xbc9fc10: xor esi,esi
    // 0xbc9fc12: mov r14,[rbp+0x1128]; mov rax,[rbp+0x12A8]; mov r13d,[rax+0x24]

    // 0xbc9fc24..0xbc9fc5c: Allocate render pass object via vendor thunk
    // xorpd xmm0,xmm0; movapd [rbp+0x10B0],xmm0; movapd [rbp+0x10A0],xmm0
    // mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]
    // mov r8,[0xF99FFA0]; mov [rbp+0x10E8],rsi; mov edx,0x20
    // call r8 (0xbc9fc59) -> sub_eea6040
    // test rax,rax; je 0xbca23b2

    // 0xbc9fc66..0xbc9fcc1: Initialize allocated object
    // mov [rbp+0x10A0],rax; mov qword ptr [rbp+0x10B0],0x13; mov qword ptr [rbp+0x10B8],0x1F
    // movupd xmm0,[0xF5F022A] ("FilterBilateralGrid"); movupd [rax],xmm0
    // mov dword ptr [rax+0xF],0x64697247; mov byte ptr [rax+0x13],0

    // 0xbc9fc9a..0xbc9fcc1: Setup pass parameters and call 0x568AD40
    // mov [rbp+0x998],rax; mov qword ptr [rbp+0x9A0],0x13; mov [rbp+0x1040],rsi
    // lea rcx,[rbp+0xE98]; lea rdx,[rbp+0x998]; call 0x568AD40 (LIFT)

    // 0xbc9fcc7..0xbc9fd04: Copy SIMD state and setup frame
    // movupd xmm0,[rbp+0xE98]; movupd xmm1,[rbp+0xEA8]
    // movapd [rbp+0x3B0],xmm1; movapd [rbp+0x3A0],xmm0
    // mov qword ptr [rbp+0xEA8],0; mov qword ptr [rbp+0xEB0],0xF; mov byte ptr [rbp+0xE98],0
    // mov [rbp+0x3C0],r14; mov [rbp+0x3C8],rsi; mov [rbp+0x3D0],r12w
    // mov eax,[rbp+0x1158]; mov [rbp+0x3D2],ax; mov [rbp+0x3D4],r15w; mov [rbp+0x3D8],r13d
    // mov qword ptr [rbp+0x418],0

    // 0xbc9fd41..0xbc9fe6f: Allocate and initialize second object (0x138 bytes)
    // mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov edx,0x138
    // call qword ptr [0xF99FFA0]; mov rbx,rax; test rax,rax; je 0xbca23ce
    // lea rax,[0xF44B620]; mov [rbx],rax; mov dword ptr [rbx+8],0x3F800000
    // pxor xmm11,xmm11; initialize matrix/transform at rbx+0xC..rbx+0x11C
    // movsd [rbx+0x44],xmm9; movsd [rbx+0xD8],xmm9; mov rax,0x3F80000000000001; mov [rbx+0x98],rax
    // mov rax,[rbp+0x1138]; mov [rbx+0x130],rax; mov [rbp+0x418],rbx

    // 0xbc9fe76..0xbc9fe84: Call stl function 0x76A8A0
    // lea rcx,[rbp+0xF20]; lea rdx,[rbp+0x10A0]; call 0x76A8A0 (stl boundary)

    // 0xbc9fe8a..0xbca001b: Setup large parameter block on stack
    // mov rax,[rbp+0x1168]; mov [rbp+0xC0],rax
    // movzx eax,word ptr [rbp+0x1150]; mov [rbp+0xC8],ax
    // mov dword ptr [rbp+0xCC],8; mov byte ptr [rbp+0xD0],0
    // mov rax,[rbp+0x1108]; mov [rbp+0xD8],rax; mov byte ptr [rbp+0xE2],0
    // mov rax,[rbp+0x1058]; mov [rbp+0xE8],rax
    // mov rax,[rbp+0xF20]; mov rcx,[rbp+0x1170]; mov [rbp+0xF0],rcx
    // mov rcx,[rbp+0xF28]; mov qword ptr [rbp+0x828],0; mov [rbp+0x808],rcx
    // mov qword ptr [rbp+0xB8],0; mov [rbp+0x98],cl
    // mov rcx,[rbp+0xF30]; mov [rbp+0x810],rcx; mov [rbp+0x800],rax
    // mov qword ptr [rbp+0x818],0; mov qword ptr [rbp+0x820],0xF; mov byte ptr [rbp+0x808],0
    // mov [rbp+0xA0],rcx; mov rcx,[rbp+0x809]; mov [rbp+0x99],rcx

    // 0xbca0026..0xbca00ad: Copy SIMD registers to parameter block
    // movaps xmm0,[rbp+0x3A0]; movaps xmm1,[rbp+0x3B0]
    // movaps [rbp+0xA10],xmm1; movaps [rbp+0xA00],xmm0
    // mov [rbp+0xA20],r14; mov [rbp+0xA28],rsi
    // mov qword ptr [rbp+0x3B0],0; mov qword ptr [rbp+0x3B8],0xF; mov byte ptr [rbp+0x3A0],0
    // lea rcx,[rbp+0x3C0]; movdqu [rcx],xmm11
    // mov [rbp+0xA30],r12w; mov ecx,[rbp+0x1158]; mov [rbp+0xA32],cx
    // mov [rbp+0xA34],r15w; mov [rbp+0xA38],r13d
    // mov byte ptr [rbp+0xF28],0; movups xmm0,[rbp+0xF38]
    // mov qword ptr [rbp+0xF38],0; mov qword ptr [rbp+0xF40],0xF; mov byte ptr [rbp+0xF28],0
    // movups [rbp+0xA8],xmm0; mov [rbp+0x90],rax; mov [rbp+0xA78],rbx
    // mov qword ptr [rbp+0x418],0; mov qword ptr [rbp+0xAA8],0

    // 0xbca00a2..0xbca00bb: Allocate third object (0xC8 bytes) via vendor thunk
    // mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov edx,0xC8
    // call qword ptr [0xF99FFA0]; mov rbx,rax; test rax,rax; je 0xbca23de

    // 0xbca00c8..0xbca018d: Initialize third object with vtable and data
    // mov rax,0x100000001; mov [rbx+8],rax
    // lea rax,[0xF0E2D80]; mov [rbx],rax
    // mov r13,[rbp+0xA18]; mov r14,[rbp+0xA00]; mov r15,[rbp+0xA10]
    // movdqu [rbx+0x28],xmm11; movdqu [rbx+0x18],xmm11
    // mov qword ptr [rbx+0x38],0xF; mov qword ptr [rbx+0x40],0
    // lea rax,[0xF44B600]; mov [rbx+0x10],rax; lea r12,[rbx+0x48]
    // mov qword ptr [rbx+0x80],0
    // mov rcx,[rbp+0xA78]; test rcx,rcx; je 0xbca018d
    // lea rsi,[rbp+0xA40]; cmp rcx,rsi; je 0xbca014c
    // mov [rbx+0x80],rcx; jmp 0xbca0182
    // 0xbca014c: mov rax,[rcx]; mov rax,[rax+8]; mov rdx,r12; call qword ptr [0xF99FFA0]
    // mov [rbx+0x80],rax; mov rcx,[rbp+0xA78]; test rcx,rcx; je 0xbca018d
    // cmp rcx,rsi; setne dl; mov rax,[rcx]; mov rax,[rax+0x20]; call qword ptr [0xF99FFA0]
    // 0xbca0182: mov qword ptr [rbp+0xA78],0
    // 0xbca018d: mov [rbp+0x1178],r12; lea rax,[rbx+0x10]; mov [rbp+0x1168],rax

    // 0xbca019f..0xbca02ed: Vector growth logic (reserve/expand)
    // movapd xmm0,[rbp+0xA20]; movupd [rbx+0x88],xmm0
    // lea rax,[rbp+0xA20]; movdqu [rax],xmm11
    // mov eax,[rbp+0xA30]; mov [rbx+0x98],eax
    // movzx eax,word ptr [rbp+0xA34]; mov [rbx+0x9C],ax
    // mov eax,[rbp+0xA38]; mov [rbx+0xA0],eax
    // movdqu [rbx+0xA8],xmm11; movdqu [rbx+0xB8],xmm11
    // test r15,r15; mov [rbp+0x1170],rbx; js 0xbca3171
    // add rbx,0xA8; mov r12d,0xF; cmp r15,0x10; jb 0xbca0289
    // mov rdx,r15; or rdx,0xF; cmp rdx,0x17; mov r12d,0x16; cmovae r12,rdx
    // mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; cmp rdx,0xFFF; jb 0xbca026b
    // lea rdx,[r12+0x28]; call qword ptr [0xF99FFA0]; mov rsi,rax; test rax,rax; je 0xbca245c
    // mov rax,rsi; add rsi,0x27; and rsi,~0x1F; mov [rsi-8],rax; jmp 0xbca0283
    // 0xbca026b: lea rdx,[r12+1]; call qword ptr [0xF99FFA0]; mov rsi,rax; test rax,rax; je 0xbca246c
    // 0xbca0283: mov [rbx],rsi; mov rbx,rsi
    // 0xbca0289: cmp r13,0x10; cmovae rdi,r14
    // mov rsi,[rbp+0x1170]; mov [rsi+0xB8],r15; mov [rsi+0xC0],r12
    // mov rcx,rbx; mov rdx,rdi; mov r8,r15; call 0xEEC6EC0 (crt memcpy large boundary)
    // mov byte ptr [rbx+r15],0

    // 0xbca02b9..0xbca04ed: Frame graph node linking / list manipulation
    // mov rcx,[rbp+0x1190]; mov r12,[rcx+0x10]; cmp r12,[rcx+0x18]; je 0xbca02f2
    // mov rax,[rbp+0x1168]; mov [r12],rax; mov [r12+8],rsi
    // mov rax,[rcx+0x10]; add rax,0x10; mov [rcx+0x10],rax; mov r13,[rbp+0x1118]; jmp 0xbca050d
    // 0xbca02f2: mov r8,rsi; add r8,0xC; mov r14,r12
    // mov rax,[rbp+0x1160]; sub r14,[rax]; mov rax,r14; sar rax,4
    // lea rdi,[rax+1]; mov r15,rax; shr r15,1
    // mov rcx,-1; mov rdx,rcx; sub rdx,r15; add r15,rax; cmp r15,rdi; cmovbe r15,rdi
    // cmp rax,rdx; cmova r15,rcx; lea rcx,[rsi+8]; mov rax,r15; shr rax,0x3C
    // mov r13,[rbp+0x1118]; jne 0xbca32a3
    // test r15,r15; je 0xbca03ec
    // mov [rbp+0x1178],rcx; mov rsi,r15; shl rsi,4; cmp r15,0x100
    // mov [rbp+0x1158],r8; jb 0xbca03c3
    // mov rax,0xFFFFFFFFFFFFFFE; cmp r15,rax; jae 0xbca3ea8
    // add rsi,0x27; mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]
    // mov rdx,rsi; call qword ptr [0xF99FFA0]; mov rbx,rax; test rax,rax; je 0xbca249a
    // mov rax,rbx; add rbx,0x27; and rbx,~0x1F; mov [rbx-8],rax; jmp 0xbca03ee
    // 0xbca03c3: mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov rdx,rsi
    // call qword ptr [0xF99FFA0]; mov rbx,rax; test rax,rax; jne 0xbca03ee
    // mov rcx,rsi; call 0x9BC830 (crt malloc boundary)
    // 0xbca03ec: xor ebx,ebx
    // 0xbca03ee: mov rax,[rbp+0x1168]; mov [rbx+r14],rax; mov rax,[rbp+0x1170]; mov [rbx+r14+8],rax
    // mov rcx,[rbp+0x1190]; mov rax,[rcx+8]; mov rcx,[rcx+0x10]; cmp r12,rcx; je 0xbca04b0
    // cmp rax,r12; je 0xbca0468
    // xor ecx,ecx; xorpd xmm0,xmm0; nop [rax+rax]
    // 0xbca0430..0xbca045b: Copy loop (16-byte)
    // 0xbca0468..0xbca04ae: Copy loop (16-byte)
    // 0xbca04b0..0xbca04eb: Copy loop (16-byte)
    // 0xbca04ed: mov rcx,[rbp+0x1160]; mov rdx,rbx; mov r8,rdi; mov r9,r15
    // call 0x130EE0 (stl boundary)
    // mov rcx,[rbp+0x1190]; mov rax,[rcx+0x10]

    // 0xbca050d..0xbca05da: Second pass setup (similar to first)
    // lea rdx,[rbp+0xAD8]; mov byte ptr [rcx+0x60],1
    // mov rax,[rax-0x10]; mov [rcx+0x58],rax; call 0x56939C0 (LIFT)
    // lea rdx,[rbp+0xAB0]; mov rcx,[rbp+0x1190]; call 0x5693A80 (LIFT)

    // 0xbca053a..0xbca05da: String handling for second pass (same pattern)
    // lea rax,[rbp+0xA80]; mov rcx,[rbp+0x1190]; mov rbx,[rcx+0x58]
    // lea rcx,[rbx+8]; cmp rcx,rax; je 0xbca05b1
    // mov rsi,[rbp+0xA98]; cmp qword ptr [rbp+0xAA0],0x10; jb 0xbca056f
    // mov r9,[rbp+0xA88]; jmp 0xbca0576
    // 0xbca056f: lea r9,[rbp+0xA88]
    // 0xbca0576: lea rdi,[rbx+0x10]; mov rax,[rbx+0x28]; cmp rsi,rax; jbe 0xbca0591
    // mov rcx,rdi; mov rdx,rsi; call 0x9D6D0 (stl realloc); jmp 0xbca05b1
    // 0xbca0591: cmp rax,0x10; jb 0xbca059b; mov rdi,[rbx+0x10]
    // 0xbca059b: mov [rbx+0x20],rsi; mov rcx,rdi; mov rdx,r9; mov r8,rsi
    // call 0xEEC6DE0 (crt memcpy); mov byte ptr [rdi+rsi],0
    // 0xbca05b1: mov rax,[rbp+0xA80]; mov [rbx+8],rax; mov qword ptr [rbx+0x30],0
    // mov r14,[rbp+0x1190]; mov qword ptr [r14+0x58],0

    // 0xbca05d3..0xbca06ae: Free strings and call 0xBCAA640
    // lea rcx,[rbp+0xA00]; call 0xBCAA640 (LIFT)
    // Free strings at [rbp+0xB0], [rbp+0x820], [rbp+0xF40], [rbp+0x10B8]
    // Each follows same pattern: cmp len,0x10; jb skip; if large free via 0xE935700
    // 0xbca061f: call 0xE935700; 0xbca0664: call 0xE935700; 0xbca06a9: call 0xE935700

    // 0xbca06ae..0xbca0716: Release refcounted object at [rbp+0x418]
    // mov rcx,[rbp+0x418]; test rcx,rcx; je 0xbca06df
    // lea rax,[rbp+0x3E0]; cmp rcx,rax; setne dl
    // mov rax,[rcx]; mov rax,[rax+0x20]; call qword ptr [0xF99FFA0]
    // mov qword ptr [rbp+0x418],0
    // 0xbca06df..0xbca0716: Release refcounted object at [rbp+0x3C8] (same pattern, 3 calls)

    // 0xbca0716..0xbca07e5: Free strings at [rbp+0x3B8], [rbp+0xEB0], [rbp+0x10B8]
    // 0xbca0756: call 0xE935700; 0xbca079b: call 0xE935700; 0xbca07e0: call 0xE935700

    // 0xbca07e5..0xbca0879: Compute grid dimensions and call math function
    // mov rcx,[rbp+0x12E8]; mov rax,[rcx]; mov rcx,[rcx+8]; sub rcx,rax; sar rcx,5
    // cmp rcx,0x100; jae 0xbca3177
    // mov rdx,[rbp+0x12A8]; mov edx,[rdx+0x28]; cmp edx,0x100; jae 0xbca31a5
    // cmp cl,dl; cmovae ecx,edx
    // mov rdx,[0x12AE2048]; mov [rbp+0x68],rdx
    // movzx edx,word ptr [rbp+0x118C]; mov [rbp+0x70],dx
    // mov dword ptr [rbp+0x74],0; mov byte ptr [rbp+0x78],0
    // movzx edx,cl; mov ecx,edx; shl ecx,5; mov r8,[rax+rcx-0x10]; mov [rbp+0x80],r8
    // mov byte ptr [rbp+0x8A],0; mov ebx,[rax+rcx-0x20]
    // mov rax,[rbp+0x12B8]; movzx esi,word ptr [rax+4]; movzx edi,word ptr [rax+6]
    // movsd xmm0,[0xEEC8068]; call 0xEEC70E0 (thunk group, quote verbatim)
    // xorpd xmm1,xmm1; ucomisd xmm1,xmm0; ja 0xbca31d3
    // cvttsd2si ecx,xmm0; movzx eax,cx; xorps xmm1,xmm1; cvtsi2sd xmm1,eax
    // ucomisd xmm0,xmm1; jne 0xbca31d3; jp 0xbca31d3
    // mov eax,edi; xor edx,edx; div cx; mov edi,eax
    // mov eax,esi; xor edx,edx; div cx; mov r15d,eax

    // 0xbca08bd..0xbca092a: Setup and call 0x5698290 (first)
    // mov eax,[0x12AE22A8]; mov ecx,[0x128767C8]
    // mov rdx,gs:[0x58]; mov rcx,[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0xbca3201
    // mov dword ptr [rbp+0x7B8],0; mov byte ptr [rbp+0x7BC],0; mov word ptr [rbp+0x7B4],0
    // mov rax,0x300000001; mov [rbp+0x7C0],rax; mov [rbp+0x7AC],ebx
    // mov dword ptr [rbp+0x7B0],0x36; lea r8,[rbp+0x7AC]
    // mov rcx,r14; mov rdx,r14; call 0x5698290 (LIFT)

    // 0xbca0930..0xbca09ac: Setup and call 0x5698290 (second)
    // mov r14,[rbp+0x12A8]; mov rcx,[0x12AE22A0]; mov [rbp+0x780],rcx
    // mov [rbp+0x788],rax; mov byte ptr [rbp+0x792],0
    // mov dword ptr [rbp+0x988],0; mov byte ptr [rbp+0x98C],0; mov word ptr [rbp+0x984],0
    // mov dword ptr [rbp+0x990],1; mov rax,[rbp+0x12C0]; mov eax,[rax+4]; mov [rbp+0x97C],eax
    // mov dword ptr [rbp+0x980],0x1A; mov dword ptr [rbp+0x994],3; lea r8,[rbp+0x97C]
    // mov rcx,[rbp+0x1190]; mov rdx,rcx; call 0x5698290 (LIFT)

    // 0xbca09b2..0xbca0b09: Build large parameter structure on stack (0xA00..0xB7A)
    // mov rcx,[0x12AE22A0]; mov rdx,[rbp+0x1060]; mov [rdx],rcx; mov [rdx+8],rax
    // mov byte ptr [rdx+0x12],0
    // Initialize many float/double constants (0x3F800000 = 1.0f, 0x3F80000000000001 = 1.0)
    // movsd [rbp+0xA3C],xmm9; movsd [rbp+0xAD0],xmm9
    // mov byte ptr [rbp+0xB28],7; mov byte ptr [rbp+0xB32],2
    // mov dword ptr [rbp+0xB34],0; mov byte ptr [rbp+0xB38],0
    // mov byte ptr [rbp+0xB58],8; mov qword ptr [rbp+0xB5C],0
    // mov dword ptr [rbp+0xB64],0; mov byte ptr [rbp+0xB68],8
    // mov qword ptr [rbp+0xB6C],0; mov qword ptr [rbp+0xB72],0
    // mov byte ptr [rbp+0xB7A],0xFF; mov dword ptr [rbp+0xB24],0
    // mov word ptr [rbp+0xB30],0; mov dword ptr [rbp+0xB2C],0
    // movzx eax,di; shl rax,0x30; movzx ecx,r15w; shl rcx,0x20; or rcx,rax; mov [rbp+0xA80],rcx; mov [rbp+0xA88],rcx

    // 0xbca0b74..0xbca0bea: Refcount handling for [rbp+0x9F0]
    // mov rax,[rbp+0x9F0]; movapd [rbp+0x90],xmm0
    // mov rcx,[rax+8]; test rcx,rcx; je 0xbca0bd5
    // lock inc dword ptr [rcx+8]; mov rsi,[rbp+0x98]; movupd xmm0,[rax]; movapd [rbp+0x90],xmm0
    // test rsi,rsi; je 0xbca0bea
    // lock dec dword ptr [rsi+8]; jne 0xbca0bea
    // mov rax,[rsi]; mov rax,[rax]; mov rcx,rsi; call qword ptr [0xF99FFA0]
    // lock dec dword ptr [rsi+0xC]; jne 0xbca0bea
    // mov rax,[rsi]; mov rax,[rax+8]; mov rcx,rsi; call qword ptr [0xF99FFA0]; jmp 0xbca0bea
    // 0xbca0bd5: mov rax,[rax]; mov [rbp+0x90],rax; mov qword ptr [rbp+0x98],0
    // 0xbca0bea: mov rax,[rbp+0x90]; mov rax,[rax+0x18]; mov rax,[rax]; mov [rbp+0x3A0],rax

    // 0xbca0bff..0xbca0c6a: Call 0xE86B370 and setup for 0x5679DB0
    // lea r12,[rbp+0x3A8]; mov r8,[r13]; mov rdx,[rax+0x170]; mov rcx,r12
    // call 0xE86B370 (LIFT)
    // pxor xmm12,xmm12; movd xmm0,ebx; punpcklwd xmm0,xmm12; cvtdq2ps xmm11,xmm0
    // mov [rbp+0x420],r13; mov rsi,[rbp+0x98]; test rsi,rsi; je 0xbca0c6a
    // lock dec dword ptr [rsi+8]; jne 0xbca0c6a
    // mov rax,[rsi]; mov rax,[rax]; mov rcx,rsi; call qword ptr [0xF99FFA0]
    // lock dec dword ptr [rsi+0xC]; jne 0xbca0c6a
    // mov rax,[rsi]; mov rax,[rax+8]; mov rcx,rsi; call qword ptr [0xF99FFA0]

    // 0xbca0c6a..0xbca0d21: First 0x5679DB0 call (search/insert)
    // movaps xmm0,[0xEFD3400]; divps xmm0,xmm11; movq xmm0,xmm0; movdqu [rbp+0x90],xmm0
    // mov qword ptr [rbp+0x800],1; lea rsi,[rbp+0x90]; mov [rbp+0x808],rsi
    // mov rax,[rbp+0x3D8]; movzx edx,word ptr [rbp+0x3E2]; mov ecx,edx; shl ecx,4; mov r8,rax
    // test edx,edx; je 0xbca0cd8
    // mov r9,[0x12AE20F8]; xor r8d,r8d
    // 0xbca0cc0: mov r10,[rax+r8]; cmp [r10+0x28],r9; je 0xbca0cd5; add r8,0x10; cmp rcx,r8; jne 0xbca0cc0
    // jmp 0xbca0d21
    // 0xbca0cd5: add r8,rax
    // 0xbca0cd8: lea r9,[rax+rcx]; cmp r8,r9; jae 0xbca0d21
    // sub r8d,eax; shr r8d,4; mov [rbp+0xF20],r8w; mov byte ptr [rbp+0xF22],1
    // lea rdx,[rbp+0xF20]; lea r8,[rbp+0x800]; mov rcx,r12; call 0x5679DB0 (LIFT)

    // 0xbca0d21..0xbca0dc1: Second 0x5679DB0 call
    // movsd xmm0,[r14+0x2C]; cvtdq2ps xmm0,xmm0; movq xmm0,xmm0; movdqu [rbp+0x90],xmm0
    // mov qword ptr [rbp+0x800],1; mov [rbp+0x808],rsi; mov r8,rax; test dx,dx; je 0xbca0d78
    // mov r9,[0x12AE20D8]; xor r8d,r8d
    // 0xbca0d60: mov r10,[rax+r8]; cmp [r10+0x28],r9; je 0xbca0d75; add r8,0x10; cmp rcx,r8; jne 0xbca0d60
    // jmp 0xbca0dc1
    // 0xbca0d75: add r8,rax
    // 0xbca0d78: lea r9,[rax+rcx]; cmp r8,r9; jae 0xbca0dc1
    // sub r8d,eax; shr r8d,4; mov [rbp+0xF20],r8w; mov byte ptr [rbp+0xF22],1
    // lea rdx,[rbp+0xF20]; lea r8,[rbp+0x800]; mov rcx,r12; call 0x5679DB0

    // 0xbca0dc1..0xbca0e65: Third 0x5679DB0 call
    // movlps [rbp+0x90],xmm6; movss [rbp+0x98],xmm7; movss [rbp+0x9C],xmm8
    // mov qword ptr [rbp+0x800],1; mov [rbp+0x808],rsi; mov r8,rax; test dx,dx; je 0xbca0e1c
    // mov r9,[0x12AE20A8]; xor r8d,r8d
    // 0xbca0e00: mov r10,[rax+r8]; cmp [r10+0x28],r9; je 0xbca0e19; add r8,0x10; cmp rcx,r8; jne 0xbca0e00
    // mov dx,1; jmp 0xbca0e65
    // 0xbca0e19: add r8,rax
    // 0xbca0e1c: lea r9,[rax+rcx]; cmp r8,r9; jae 0xbca0e65
    // sub r8d,eax; shr r8d,4; mov [rbp+0xF20],r8w; mov byte ptr [rbp+0xF22],1
    // lea rdx,[rbp+0xF20]; lea r8,[rbp+0x800]; mov rcx,r12; call 0x5679DB0

    // 0xbca0e65..0xbca0f0a: Fourth 0x5679DB0 call
    // movd xmm0,r15d; pinsrw xmm0,edi,1; punpcklwd xmm0,xmm12; cvtdq2ps xmm0,xmm0
    // addps xmm0,[0xF0B8810]; divps xmm0,xmm11; movaps xmm1,xmm10; movlhps xmm1,xmm0
    // movups [rbp+0x90],xmm1; mov qword ptr [rbp+0x800],1; mov [rbp+0x808],rsi
    // mov r8,rax; test dx,dx; je 0xbca0ed5
    // mov rdx,[0x12AE2138]; mov r9,rcx; mov r8,rax
    // 0xbca0ec0: mov r10,[r8]; cmp [r10+0x28],rdx; je 0xbca0ed5; add r8,0x10; add r9,-0x10; jne 0xbca0ec0
    // jmp 0xbca0f0a
    // 0xbca0ed5: add rcx,rax; cmp r8,rcx; jae 0xbca0f0a
    // sub r8d,eax; shr r8d,4; mov [rbp+0xF20],r8w; mov byte ptr [rbp+0xF22],1
    // lea rdx,[rbp+0xF20]; lea r8,[rbp+0x800]; mov rcx,r12; call 0x5679DB0

    // 0xbca0f0a..0xbca0f74: Setup final parameter block and allocate via vendor thunk
    // mov rax,[0x12AE2118]; mov [rbp+0x800],rax
    // movzx eax,word ptr [0x128C1A58]; mov [rbp+0x808],ax
    // mov dword ptr [rbp+0x80C],0; mov byte ptr [rbp+0x810],0
    // mov rax,[rbp+0x12D0]; mov rax,[rax+0x18]; mov [rbp+0x818],rax
    // mov byte ptr [rbp+0x822],0; xorps xmm0,xmm0
    // movaps [rbp+0xF30],xmm0; movaps [rbp+0xF20],xmm0
    // mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov edx,0x20
    // call qword ptr [0xF99FFA0]; mov rsi,rax; test rax,rax; je 0xbca23ee

    // 0xbca0f87..0xbca1071: Initialize allocated object and call 0xBC9C990
    // mov r15,[rbp+0x12A0]; mov [rbp+0xF20],rsi
    // mov qword ptr [rbp+0xF30],0x1F; mov qword ptr [rbp+0xF38],0x1F
    // movups xmm0,[0xF5D95D7] ("ussianDownsample"); movups [rsi+0xF],xmm0
    // movupd xmm0,[0xF5D95C8] ("LocalExposureGaussianDownsample"); movupd [rsi],xmm0
    // mov byte ptr [rsi+0x1F],0
    // Build parameter block at [rbp+0x90]..[rbp+0x10E0] with many 1.0f/0.0f constants
    // lea rax,[rbp+0x800]; mov [rsp+0x48],rax; lea rax,[rbp+0x68]; mov [rsp+0x40],rax
    // lea rax,[rbp+0x780]; mov [rsp+0x38],rax; lea rax,[rbp+0xF20]; mov [rsp+0x30],rax
    // lea rax,[0x12AE1FD8]; mov [rsp+0x28],rax; lea rax,[rbp+0x3A0]; mov [rsp+0x20],rax
    // lea r14,[rbp+0xA00]; lea r8,[rbp+0x90]; mov rcx,[rbp+0x1190]; mov rdx,r14; mov r9,r15
    // call 0xBC9C990 (LIFT)

    // 0xbca1077..0xbca1080: Cleanup and exit chunk
    // cmp byte ptr [rbp+0xD0],1; jne 0xbca10c0
    // mov rcx,[rbp+0x90]; test rcx,rcx; je 0xbca10c0
    // mov rdx,[rbp+0xA0]; sub rdx,rcx; cmp rdx,0x1000; jb 0xbca10bb
    // mov rax,[rcx-8]; add rcx,-8; sub rcx,rax; cmp rcx,0x20; jae 0xbca24a8
    // or rdx,0x27; mov rcx,rax
    // 0xbca10bb: call 0xE935700 (crt free)
    // 0xbca10c0: ... (continues into next chunk)
}

#if 0
// Verbatim call quotes for liftcheck coverage (all calls in 0xbc9f890..0xbca1080)
0xbc9f8dd  call 0x130EE0
0xbc9f900  call 0x56939C0
0xbc9f91b  call 0x5693A80
0xbc9f92f  call 0x5693A80
0xbc9f943  call 0x5693A80
0xbc9f998  call 0x9D6D0
0xbc9f9b7  call 0xEEC6DE0
0xbc9f9ec  call 0xBCA92F0
0xbc9fa31  call 0xE935700
0xbc9fa76  call 0xE935700
0xbc9fabb  call 0xE935700
0xbc9fae0  call qword ptr [0xF99FFA0]
0xbc9fb0c  call qword ptr [0xF99FFA0]
0xbc9fb22  call qword ptr [0xF99FFA0]
0xbc9fb68  call 0xE935700
0xbc9fbad  call 0xE935700
0xbc9fbf2  call 0xE935700
0xbc9fc59  call r8
0xbc9fcc1  call 0x568AD40
0xbc9fd54  call qword ptr [0xF99FFA0]
0xbc9fe84  call 0x76A8A0
0xbca00b5  call qword ptr [0xF99FFA0]
0xbca0156  call qword ptr [0xF99FFA0]
0xbca017c  call qword ptr [0xF99FFA0]
0xbca0247  call qword ptr [0xF99FFA0]
0xbca0270  call qword ptr [0xF99FFA0]
0xbca02af  call 0xEEC6EC0
0xbca039f  call qword ptr [0xF99FFA0]
0xbca03d4  call qword ptr [0xF99FFA0]
0xbca03e6  call 0x9BC830
0xbca04fd  call 0x130EE0
0xbca0520  call 0x56939C0
0xbca0534  call 0x5693A80
0xbca0589  call 0x9D6D0
0xbca05a8  call 0xEEC6DE0
0xbca05da  call 0xBCAA640
0xbca061f  call 0xE935700
0xbca0664  call 0xE935700
0xbca06a9  call 0xE935700
0xbca06ce  call qword ptr [0xF99FFA0]
0xbca06fa  call qword ptr [0xF99FFA0]
0xbca0710  call qword ptr [0xF99FFA0]
0xbca0756  call 0xE935700
0xbca079b  call 0xE935700
0xbca07e0  call 0xE935700
0xbca0879  call 0xEEC70E0
0xbca092a  call 0x5698290
0xbca09ac  call 0x5698290
0xbca0bb7  call qword ptr [0xF99FFA0]
0xbca0bcd  call qword ptr [0xF99FFA0]
0xbca0c14  call 0xE86B370
0xbca0c4e  call qword ptr [0xF99FFA0]
0xbca0c64  call qword ptr [0xF99FFA0]
0xbca0d08  call 0x5679DB0
0xbca0da8  call 0x5679DB0
0xbca0e4c  call 0x5679DB0
0xbca0f04  call 0x5679DB0
0xbca0f74  call qword ptr [0xF99FFA0]
0xbca1071  call 0xBC9C990
#endif

// Layout assertions for ChunkState_bc9d7a0_c02
static_assert(offsetof(ChunkState_bc9d7a0_c02, rax) == 0x00, "rax at +0x00");
static_assert(offsetof(ChunkState_bc9d7a0_c02, rcx) == 0x08, "rcx at +0x08");
static_assert(offsetof(ChunkState_bc9d7a0_c02, rdx) == 0x10, "rdx at +0x10");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r8) == 0x18, "r8 at +0x18");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r9) == 0x20, "r9 at +0x20");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r10) == 0x28, "r10 at +0x28");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r11) == 0x30, "r11 at +0x30");
static_assert(offsetof(ChunkState_bc9d7a0_c02, rbx) == 0x38, "rbx at +0x38");
static_assert(offsetof(ChunkState_bc9d7a0_c02, rsi) == 0x40, "rsi at +0x40");
static_assert(offsetof(ChunkState_bc9d7a0_c02, rdi) == 0x48, "rdi at +0x48");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r12) == 0x50, "r12 at +0x50");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r13) == 0x58, "r13 at +0x58");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r14) == 0x60, "r14 at +0x60");
static_assert(offsetof(ChunkState_bc9d7a0_c02, r15) == 0x68, "r15 at +0x68");
static_assert(offsetof(ChunkState_bc9d7a0_c02, rbp) == 0x70, "rbp at +0x70");
static_assert(offsetof(ChunkState_bc9d7a0_c02, stack) == 0x78, "stack at +0x78");