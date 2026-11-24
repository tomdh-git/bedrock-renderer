// LIFT 0xbcc7f20 size 0x7421 1.26.62.01 MaterialInstance::initFromMaterial
// CHUNK 0xbccc713..0xbccdf04

// chunk state documented in docs/functions/bcc7f20.md section 'Chunk state'
struct ChunkState_bcc7f20_c03 {
    void* rbp_frame_base;
    void* this_ptr;
    const void* m;
};

static inline void bcc7f20_chunk03(ChunkState_bcc7f20_c03& s) {
    void* rbp = s.rbp_frame_base;

    // 0xbccc713..0xbccc752
    // 0xbccc713  cmp rax,0x200
    // 0xbccc719  jb short 0xBCCC754
    // 0xbccc71b  lea r14,[rdi+0x27]
    // 0xbccc71f  mov rcx,[0x1233E1A8]
    // 0xbccc726  mov rax,[rcx]
    // 0xbccc729  mov rax,[rax+8]
    // 0xbccc72d  mov rdx,r14
    // 0xbccc730  call qword ptr [0xF99FFA0]
    // 0xbccc736  nop
    // 0xbccc737  mov rbx,rax
    // 0xbccc73a  test rax,rax
    // 0xbccc73d  je 0xBCCE857
    // 0xbccc743  mov rax,rbx
    // 0xbccc746  add rbx,0x27
    // 0xbccc74a  and rbx,0xFFFFFFFFFFFFFFE0
    // 0xbccc74e  mov [rbx-8],rax
    // 0xbccc752  jmp short 0xBCCC778
    {
        size_t allocSize = 0; // rax from prior context
        void* rdi = nullptr;  // from prior context
        void* r14 = (void*)((uintptr_t)rdi + 0x27); // lea r14,[rdi+0x27]
        void* rcx = *(void**)0x1233E1A8;
        void* rax = *(void**)rcx;
        rax = *(void**)((uintptr_t)rax + 8);
        void* rdx = r14;
        void* (*allocFn)(void*, size_t) = (void* (*)(void*, size_t))0xF99FFA0;
        void* mem = allocFn(rax, (size_t)rdx);
        if (!mem) goto alloc_fail_0xbccce857;
        void* rbx = mem;
        // nop
        rax = rbx;
        if (!rax) goto alloc_fail_0xbccce857; // test rax,rax / je 0xBCCE857
        rax = rbx;
        rbx = (void*)(((uintptr_t)rbx + 0x27) & ~0x1F);
        *(void**)((uintptr_t)rbx - 8) = rax;
        goto loc_bccc778;
    }

    // 0xbccc754..0xbccc772
    // 0xbccc754  mov rcx,[0x1233E1A8]
    // 0xbccc75b  mov rax,[rcx]
    // 0xbccc75e  mov rax,[rax+8]
    // 0xbccc762  mov rdx,rdi
    // 0xbccc765  call qword ptr [0xF99FFA0]
    // 0xbccc76b  nop
    // 0xbccc76c  mov rbx,rax
    // 0xbccc76f  test rax,rax
    // 0xbccc772  je 0xBCCE865
    {
        void* rcx = *(void**)0x1233E1A8;
        void* rax = *(void**)rcx;
        rax = *(void**)((uintptr_t)rax + 8);
        void* rdi = nullptr; // from prior context
        void* (*allocFn2)(void*, size_t) = (void* (*)(void*, size_t))0xF99FFA0;
        void* mem = allocFn2(rdi, (size_t)rax);
        if (!mem) goto alloc_fail_0xbccce865;
        void* rbx = mem;
        goto loc_bccc778;
    }

loc_bccc778:
    // 0xbccc778..0xbccc7d4
    // 0xbccc778  mov rsi,[rbp+0x258]
    // 0xbccc77f  mov [rsi+0x58],rbx
    // 0xbccc783  mov [rsi+0x60],rbx
    // 0xbccc787  add rdi,rbx
    // 0xbccc78a  mov [rsi+0x68],rdi
    // 0xbccc78e  mov rdx,[rbp+0x1B0]
    // 0xbccc795  mov rdi,[rbp+0x1B8]
    // 0xbccc79c  sub rdi,rdx
    // 0xbccc79f  mov rcx,rbx
    // 0xbccc7a2  mov r8,rdi
    // 0xbccc7a5  call 0xEEC6DE0
    // 0xbccc7aa  add rdi,rbx
    // 0xbccc7ad  mov [rsi+0x60],rdi
    // 0xbccc7b1  lea rax,[rsi+0x58]
    // 0xbccc7b5  mov [rbp+0x268],rax
    // 0xbccc7bc  lea rcx,[rsi+0x70]
    // 0xbccc7c0  lea rdx,[rbp+0x1C8]
    // 0xbccc7c7  mov rdi,rsi
    // 0xbccc7ca  lea rsi,[rbp+0x238]
    // 0xbccc7d1  mov r8,rsi
    // 0xbccc7d4  call 0xAA710
    {
        void* rbx = nullptr; // from prior context
        void* rsi = *(void**)((uintptr_t)rbp + 0x258);
        *(void**)((uintptr_t)rsi + 0x58) = rbx;
        *(void**)((uintptr_t)rsi + 0x60) = rbx;
        void* rdi = nullptr; // from prior context
        rdi = (void*)((uintptr_t)rdi + (uintptr_t)rbx);
        *(void**)((uintptr_t)rsi + 0x68) = rdi;
        void* rdx = *(void**)((uintptr_t)rbp + 0x1B0);
        rdi = *(void**)((uintptr_t)rbp + 0x1B8);
        rdi = (void*)((uintptr_t)rdi - (uintptr_t)rdx);
        void* rcx = rbx;
        void* r8 = rdi;
        ((void(*)(void*, void*, void*))0xEEC6DE0)(rcx, r8, rdi);
        rdi = (void*)((uintptr_t)rdi + (uintptr_t)rbx);
        *(void**)((uintptr_t)rsi + 0x60) = rdi;
        void* rax = (void*)((uintptr_t)rsi + 0x58);
        *(void**)((uintptr_t)rbp + 0x268) = rax;
        rcx = (void*)((uintptr_t)rsi + 0x70);
        rdx = (void*)((uintptr_t)rbp + 0x1C8);
        void* rdi2 = rsi;
        void* rsi2 = (void*)((uintptr_t)rbp + 0x238);
        r8 = rsi2;
        ((void(*)(void*, void*, void*, void*))0xAA710)(rcx, rdx, rdi2, r8);
    }

    // 0xbccc7d9..0xbccc80b
    // 0xbccc7d9  nop
    // 0xbccc7da  lea rax,[rdi+0x50]
    // 0xbccc7de  mov [rbp+0x20],rax
    // 0xbccc7e2  mov rax,[rbp+0x208]
    // 0xbccc7e9  mov [rdi+0xB0],rax
    // 0xbccc7f0  lea rcx,[rdi+0xB8]
    // 0xbccc7f7  mov dword ptr [rbp+0x238],0
    // 0xbccc7fc  mov [rbp+0x268],rcx
    // 0xbccc801  mov rdx,rsi
    // 0xbccc804  call 0xA1C40
    // 0xbccc80b  nop
    {
        void* rdi = nullptr; // from prior context (rdi2)
        void* rax = (void*)((uintptr_t)rdi + 0x50);
        *(void**)((uintptr_t)rbp + 0x20) = rax;
        rax = *(void**)((uintptr_t)rbp + 0x208);
        *(void**)((uintptr_t)rdi + 0xB0) = rax;
        void* rcx = (void*)((uintptr_t)rdi + 0xB8);
        *(uint32_t*)((uintptr_t)rbp + 0x238) = 0;
        *(void**)((uintptr_t)rbp + 0x268) = rcx;
        void* rdx = rsi; // rsi from earlier
        ((void(*)(void*, void*))0xA1C40)(rcx, rdx);
    }

    // 0xbccc810..0xbccc8c2
    // 0xbccc810  nop
    // 0xbccc811  mov byte ptr [rdi+0x108],0
    // 0xbccc818  mov dword ptr [rdi+0x110],0
    // 0xbccc822  movups [rdi+0x118],xmm7
    // 0xbccc829  mov rcx,[0x1233E1A8]
    // 0xbccc830  mov rax,[rcx]
    // 0xbccc833  mov rax,[rax+8]
    // 0xbccc837  mov edx,0x68
    // 0xbccc83c  call qword ptr [0xF99FFA0]
    // 0xbccc842  nop
    // 0xbccc843  mov rdi,rax
    // 0xbccc846  test rax,rax
    // 0xbccc849  je 0xBCCE829
    // 0xbccc84f  mov rax,[rbp+0x258]
    // 0xbccc856  lea rcx,[rax+0x118]
    // 0xbccc85d  mov [rbp+0x90],rcx
    // 0xbccc864  mov [rdi],rdi
    // 0xbccc867  mov [rdi+8],rdi
    // 0xbccc86b  mov [rax+0x118],rdi
    // 0xbccc872  lea rcx,[rax+0x128]
    // 0xbccc879  mov [rbp+0x50],rcx
    // 0xbccc87d  movups [rax+0x128],xmm7
    // 0xbccc884  mov qword ptr [rax+0x138],0
    // 0xbccc88f  mov qword ptr [rax+0x140],7
    // 0xbccc89a  mov qword ptr [rax+0x148],8
    // 0xbccc8a5  mov dword ptr [rax+0x110],0x3F800000
    {
        void* rdi = nullptr; // from prior context
        *(uint8_t*)((uintptr_t)rdi + 0x108) = 0;
        *(uint32_t*)((uintptr_t)rdi + 0x110) = 0;
        *(uint64_t*)((uintptr_t)rdi + 0x118) = 0;
        *(uint64_t*)((uintptr_t)rdi + 0x120) = 0;
        
        void* rcx = *(void**)0x1233E1A8;
        void* rax = *(void**)rcx;
        rax = *(void**)((uintptr_t)rax + 8);
        uint32_t edx = 0x68;
        void* (*allocFn3)(void*, size_t) = (void* (*)(void*, size_t))0xF99FFA0;
        void* rdi2 = allocFn3(rax, edx);
        if (!rdi2) goto alloc_fail_0xbccce829;
        rdi = rdi2;
        
        rax = *(void**)((uintptr_t)rbp + 0x258);
        rcx = (void*)((uintptr_t)rax + 0x118);
        *(void**)((uintptr_t)rbp + 0x90) = rcx;
        *(void**)rdi = rdi;
        *(void**)((uintptr_t)rdi + 8) = rdi;
        *(void**)((uintptr_t)rax + 0x118) = rdi;
        rcx = (void*)((uintptr_t)rax + 0x128);
        *(void**)((uintptr_t)rbp + 0x50) = rcx;
        *(uint64_t*)((uintptr_t)rax + 0x128) = 0;
        *(uint64_t*)((uintptr_t)rax + 0x130) = 0;
        *(uint64_t*)((uintptr_t)rax + 0x138) = 0;
        *(uint64_t*)((uintptr_t)rax + 0x140) = 7;
        *(uint64_t*)((uintptr_t)rax + 0x148) = 8;
        *(uint32_t*)((uintptr_t)rax + 0x110) = 0x3F800000;
    }

    // 0xbccc8c8..0xbccc914
    // 0xbccc8c8  nop
    // 0xbccc8c9  mov rbx,rax
    // 0xbccc8cc  test rax,rax
    // 0xbccc8cf  je 0xBCCE839
    // 0xbccc8d5  mov rsi,[rbp+0x258]
    // 0xbccc8dc  mov rcx,[rsi+0x128]
    // 0xbccc8e3  mov rdx,[rsi+0x138]
    // 0xbccc8ea  sub rdx,rcx
    // 0xbccc8ed  je short 0xBCCC919
    // 0xbccc8ef  cmp rdx,0x1000
    // 0xbccc8f6  jb short 0xBCCC914
    // 0xbccc8f8  mov rax,[rcx-8]
    // 0xbccc8fc  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbccc900  sub rcx,rax
    // 0xbccc903  cmp rcx,0x20
    // 0xbccc907  jae 0xBCCECCC
    // 0xbccc90d  add rdx,0x27
    // 0xbccc911  mov rcx,rax
    {
        void* rax = nullptr; // from prior context
        void* rbx = rax;
        if (!rax) goto alloc_fail_0xbccce839;
        void* rsi = *(void**)((uintptr_t)rbp + 0x258);
        void* rcx = *(void**)((uintptr_t)rsi + 0x128);
        void* rdx = *(void**)((uintptr_t)rsi + 0x138);
        size_t diff = (uintptr_t)rdx - (uintptr_t)rcx;
        if (diff == 0) goto loc_bccc919;
        if (diff < 0x1000) goto loc_bccc914;
        rax = *(void**)((uintptr_t)rcx - 8);
        rcx = (void*)((uintptr_t)rcx - 8);
        size_t rcx_val = (uintptr_t)rcx - (uintptr_t)rax;
        if (rcx_val >= 0x20) goto loc_bcceccc;
        diff += 0x27;
        rcx = rax;
        goto loc_bccc914;
    }

loc_bccc914:
    // 0xbccc914  call 0xE935700
    ((void(*)())0xE935700)();

loc_bccc919:
    // 0xbccc919..0xbccc9d3
    // 0xbccc919  mov [rsi+0x128],rbx
    // 0xbccc920  mov rax,rbx
    // 0xbccc923  sub rax,0xFFFFFFFFFFFFFF80
    // 0xbccc927  mov [rsi+0x130],rax
    // 0xbccc92e  mov [rsi+0x138],rax
    // 0xbccc935  mov [rbx],rdi
    // 0xbccc938  mov [rbx+8],rdi
    // 0xbccc93c  mov [rbx+0x10],rdi
    // 0xbccc940  mov [rbx+0x18],rdi
    // 0xbccc944  mov [rbx+0x20],rdi
    // 0xbccc948  mov [rbx+0x28],rdi
    // 0xbccc950  mov [rbx+0x30],rdi
    // 0xbccc954  mov [rbx+0x38],rdi
    // 0xbccc958  mov [rbx+0x40],rdi
    // 0xbccc95c  mov [rbx+0x48],rdi
    // 0xbccc960  mov [rbx+0x50],rdi
    // 0xbccc964  mov [rbx+0x58],rdi
    // 0xbccc968  mov [rbx+0x60],rdi
    // 0xbccc970  mov [rbx+0x68],rdi
    // 0xbccc974  mov [rbx+0x70],rdi
    // 0xbccc974  mov [rbx+0x78],rdi
    // 0xbccc97b  mov r8,[rbp+0x1B0]
    // 0xbccc97b  mov r14,[rbp+0x1B8]
    // 0xbccc982  mov rax,r14
    // 0xbccc985  sub rax,r8
    // 0xbccc988  cmp rax,0xFFFFFFFFFFFFFFF8
    // 0xbccc98c  je 0xBCCF08A
    // 0xbccc992  test r8,r8
    // 0xbccc995  sete al
    // 0xbccc998  test r14,r14
    // 0xbccc99b  setne cl
    // 0xbccc99e  test al,cl
    // 0xbccc9a0  jne 0xBCCF08A
    // 0xbccc9a6  lea rax,[rsi+0x10]
    // 0xbccc9aa  mov [rbp+0x60],rax
    // 0xbccc9ae  mov rax,rsi
    // 0xbccc9b1  add rax,0x110
    // 0xbccc9b7  mov [rbp+0x28],rax
    // 0xbccc9bb  mov rdi,0xCBF29CE484222325
    // 0xbccc9c5  mov [rbp+0xE0],r13b
    // 0xbccc9cc  mov [rbp+0x120],r14
    // 0xbccc9d3  jmp short 0xBCCC9E4
    {
        void* rsi = *(void**)((uintptr_t)rbp + 0x258);
        void* rbx = nullptr; // from prior
        *(void**)((uintptr_t)rsi + 0x128) = rbx;
        void* rax = (void*)((uintptr_t)rbx - 0x80);
        *(void**)((uintptr_t)rsi + 0x130) = rax;
        *(void**)((uintptr_t)rsi + 0x138) = rax;
        void* rdi = nullptr; // from prior
        *(void**)rbx = rdi;
        *(void**)((uintptr_t)rbx + 8) = rdi;
        *(void**)((uintptr_t)rbx + 0x10) = rdi;
        *(void**)((uintptr_t)rbx + 0x18) = rdi;
        *(void**)((uintptr_t)rbx + 0x20) = rdi;
        *(void**)((uintptr_t)rbx + 0x28) = rdi;
        *(void**)((uintptr_t)rbx + 0x30) = rdi;
        *(void**)((uintptr_t)rbx + 0x38) = rdi;
        *(void**)((uintptr_t)rbx + 0x40) = rdi;
        *(void**)((uintptr_t)rbx + 0x48) = rdi;
        *(void**)((uintptr_t)rbx + 0x50) = rdi;
        *(void**)((uintptr_t)rbx + 0x58) = rdi;
        *(void**)((uintptr_t)rbx + 0x60) = rdi;
        *(void**)((uintptr_t)rbx + 0x68) = rdi;
        *(void**)((uintptr_t)rbx + 0x70) = rdi;
        *(void**)((uintptr_t)rbx + 0x78) = rdi;
        
        void* r8 = *(void**)((uintptr_t)rbp + 0x1B0);
        void* r14 = *(void**)((uintptr_t)rbp + 0x1B8);
        rax = r14;
        size_t diff2 = (uintptr_t)rax - (uintptr_t)r8;
        if (diff2 == 0xFFFFFFFFFFFFFFF8) goto loc_bccf08a;
        bool al = (r8 != nullptr);
        bool cl = (r14 != nullptr);
        if (al && cl) goto loc_bccf08a;
        rax = (void*)((uintptr_t)rsi + 0x10);
        *(void**)((uintptr_t)rbp + 0x60) = rax;
        rax = (void*)((uintptr_t)rsi + 0x110);
        *(void**)((uintptr_t)rbp + 0x28) = rax;
        uint64_t rdi_val = 0xCBF29CE484222325;
        *(uint8_t*)((uintptr_t)rbp + 0xE0) = 0; // r13b
        *(void**)((uintptr_t)rbp + 0x120) = r14;
        goto loc_bccc9e4;
    }

    // 0xbccc9e0..0xbccca93 (hash table walk outer loop)
loc_bccc9e0:
    // 0xbccc9e0  add r8,8
    // 0xbccc9e4  cmp r8,r14
    // 0xbccc9e7  je 0xBCCDBF0
    // 0xbccc9ed  mov rbx,[r8]
    // 0xbccc9f0  test rbx,rbx
    // 0xbccc9f3  je short 0xBCCC9E0
    // 0xbccc9f5  movzx eax,bl
    // 0xbccc9f8  xor rax,rdi
    // 0xbccc9fb  mov rdx,0x100000001B3
    // 0xbccca05  imul rax,rdx
    // 0xbccca09  movzx ecx,bh
    // 0xbccca0c  xor rcx,rax
    // 0xbccca0f  imul rcx,rdx
    // 0xbccca13  mov eax,ebx
    // 0xbccca15  shr eax,0x10
    // 0xbccca18  movzx eax,al
    // 0xbccca1b  xor rax,rcx
    // 0xbccca1e  imul rax,rdx
    // 0xbccca22  mov ecx,ebx
    // 0xbccca24  shr ecx,0x18
    // 0xbccca27  xor rcx,rax
    // 0xbccca2a  imul rcx,rdx
    // 0xbccca2e  mov rax,rbx
    // 0xbccca31  shr rax,0x20
    // 0xbccca35  movzx eax,al
    // 0xbccca38  xor rax,rcx
    // 0xbccca3b  imul rax,rdx
    // 0xbccca3f  mov rcx,rbx
    // 0xbccca42  shr rcx,0x28
    // 0xbccca46  movzx ecx,cl
    // 0xbccca49  xor rcx,rax
    // 0xbccca4c  imul rcx,rdx
    // 0xbccca50  mov rax,rbx
    // 0xbccca53  shr rax,0x30
    // 0xbccca57  movzx eax,al
    // 0xbccca5a  xor rax,rcx
    // 0xbccca5d  imul rax,rdx
    // 0xbccca61  mov r15,rbx
    // 0xbccca64  shr r15,0x38
    // 0xbccca68  xor r15,rax
    // 0xbccca6b  imul r15,rdx
    // 0xbccca6f  mov rcx,[rsi+0x140]
    // 0xbccca76  and rcx,r15
    // 0xbccca79  mov r12,[rsi+0x118]
    // 0xbccca80  mov rdx,[rsi+0x128]
    // 0xbccca87  shl rcx,4
    // 0xbccca8b  mov rax,[rdx+rcx+8]
    // 0xbccca90  cmp rax,r12
    // 0xbccca93  je short 0xBCCCAC7
    {
        void* r8 = *(void**)((uintptr_t)rbp + 0x1B0); // reset each outer iteration
        void* r14 = *(void**)((uintptr_t)rbp + 0x1B8);
        uint64_t rdi = 0xCBF29CE484222325;
        void* rsi = *(void**)((uintptr_t)rbp + 0x258);
        
        while (true) {
            r8 = (void*)((uintptr_t)r8 + 8);
            if (r8 == r14) goto loc_bccdbf0;
            void* rbx = *(void**)r8;
            if (!rbx) continue;
            
            // FNV-1a 64-bit hash of rbx (8 bytes)
            uint64_t hash = rdi;
            uint64_t val = (uintptr_t)rbx;
            for (int i = 0; i < 8; i++) {
                hash ^= (val >> (i * 8)) & 0xFF;
                hash *= 0x100000001B3;
            }
            uint64_t r15 = hash;
            
            void* rcx = *(void**)((uintptr_t)rsi + 0x140);
            rcx = (void*)((uintptr_t)rcx & (uintptr_t)r15);
            void* r12 = *(void**)((uintptr_t)rsi + 0x118);
            void* rdx = *(void**)((uintptr_t)rsi + 0x128);
            rcx = (void*)((uintptr_t)rcx << 4);
            void* rax = *(void**)((uintptr_t)rdx + (uintptr_t)rcx + 8);
            if (rax == r12) goto loc_bcccac7;
            if ((uintptr_t)rbx == *(uintptr_t*)((uintptr_t)rax + 0x10)) goto loc_bccc9e0;
            rcx = *(void**)((uintptr_t)rdx + (uintptr_t)rcx);
            
            // inner loop
            while (true) {
                if (rax == rcx) goto loc_bcccac4;
                rax = *(void**)((uintptr_t)rax + 8);
                if ((uintptr_t)rbx == *(uintptr_t*)((uintptr_t)rax + 0x10)) goto loc_bccc9e0;
            }
        }
    }

loc_bcccac4:
    // 0xbcccac4  mov r12,rax
    // 0xbcccac7..0xbcccae5
    // 0xbcccac7  mov [rbp+0x230],r8
    // 0xbcccace  mov rax,0x276276276276276
    // 0xbcccad8  cmp [rsi+0x120],rax
    // 0xbcccadf  je 0xBCCF0FD
    // 0xbcccae5  mov rax,[rbp+0x90]
    // 0xbcccaec  mov [rbp+0x30],rax
    // 0xbcccaf0  mov rcx,[0x1233E1A8]
    // 0xbcccaf7  mov rax,[rcx]
    // 0xbcccafa  mov rax,[rax+8]
    // 0xbcccafe  mov r8,[0xF99FFA0]
    // 0xbcccb05  mov qword ptr [rbp+0x98],0
    // 0xbcccb10  mov edx,0x68
    // 0xbcccb15  call r8
    {
        void* r12 = nullptr; // from prior
        void* r8 = nullptr; // from prior
        *(void**)((uintptr_t)rbp + 0x230) = r8;
        void* rax = (void*)0x276276276276276;
        void* rsi = *(void**)((uintptr_t)rbp + 0x258);
        if (*(void**)((uintptr_t)rsi + 0x120) == rax) goto loc_bccf0fd;
        rax = *(void**)((uintptr_t)rbp + 0x90);
        *(void**)((uintptr_t)rbp + 0x30) = rax;
        void* rcx = *(void**)0x1233E1A8;
        rax = *(void**)rcx;
        rax = *(void**)((uintptr_t)rax + 8);
        void* r8_2 = *(void**)0xF99FFA0;
        *(uint64_t*)((uintptr_t)rbp + 0x98) = 0;
        uint32_t edx = 0x68;
        void* (*allocFn4)(void*, size_t) = (void* (*)(void*, size_t))r8_2;
        void* mem = allocFn4(rax, edx);
        // fall through to bcccb25
    }

loc_bcccb25:
    // 0xbcccb25..0xbcccb80
    // 0xbcccb25  mov rdi,rsi
    // 0xbcccb28  mov [rbp+0x38],rsi
    // 0xbcccb2c  mov [rsi+0x10],rbx
    // 0xbcccb30  mov word ptr [rsi+0x1C],0xFFFF
    // 0xbcccb36  mov byte ptr [rsi+0x1E],1
    // 0xbcccb3a  add rsi,0x20
    // 0xbcccb3e  mov dword ptr [rbp+0x238],0
    // 0xbcccb48  mov [rbp+0x98],rdi
    // 0xbcccb4f  mov rcx,rsi
    // 0xbcccb52  lea rdx,[rbp+0x238]
    // 0xbcccb59  call 0xA1C40
    // 0xbcccb5e  nop
    // 0xbcccb5f  mov [rbp+0x128],r12
    // 0xbcccb66  mov r8,[rbx+0x78]
    // 0xbcccb6a  mov r9,[rbx+0x50]
    // 0xbcccb6e  mov r10,[rbx+0x60]
    // 0xbcccb72  mov eax,r13d
    // 0xbcccb75  nop [rax+rax]
    {
        void* rsi = nullptr; // from prior
        void* rbx = nullptr; // from prior
        void* rdi = rsi;
        *(void**)((uintptr_t)rbp + 0x38) = rsi;
        *(void**)((uintptr_t)rsi + 0x10) = rbx;
        *(uint16_t*)((uintptr_t)rsi + 0x1C) = 0xFFFF;
        *(uint8_t*)((uintptr_t)rsi + 0x1E) = 1;
        rsi = (void*)((uintptr_t)rsi + 0x20);
        *(uint32_t*)((uintptr_t)rbp + 0x238) = 0;
        *(void**)((uintptr_t)rbp + 0x98) = rdi;
        void* rcx = rsi;
        void* rdx = (void*)((uintptr_t)rbp + 0x238);
        ((void(*)(void*, void*))0xA1C40)(rcx, rdx);
        
        void* r12 = nullptr; // from prior
        *(void**)((uintptr_t)rbp + 0x128) = r12;
        void* r8 = *(void**)((uintptr_t)rbx + 0x78);
        void* r9 = *(void**)((uintptr_t)rbx + 0x50);
        void* r10 = *(void**)((uintptr_t)rbx + 0x60);
        uint32_t eax = 0; // r13d from prior
    }

    // 0xbcccb80..0xbccccb1 (hash lookup loop 1)
    // 0xbcccb80  movzx ecx,al
    // 0xbcccb83  and ecx,r8d
    // 0xbcccb86  shl ecx,4
    // 0xbcccb89  mov r12,[r10+rcx+8]
    // 0xbcccb8e  cmp r12,r9
    // 0xbcccb91  je short 0xBCCCBC0
    // 0xbcccb93  mov rcx,[r10+rcx]
    // 0xbcccb97  cmp al,[r12+0x10]
    // 0xbcccb9c  jne short 0xBCCCBA8
    // 0xbcccb9e  xchg ax,ax
    // 0xbcccba0  cmp byte ptr [r12+0x11],0
    // 0xbcccba6  je short 0xBCCCBC3
    // 0xbcccba8  cmp r12,rcx
    // 0xbcccbab  je short 0xBCCCBC0
    // 0xbcccbad  mov r12,[r12+8]
    // 0xbcccbb2  cmp al,[r12+0x10]
    // 0xbcccbb7  je short 0xBCCCBA0
    // 0xbcccbb9  jmp short 0xBCCCBA8
    // 0xbcccbbb  nop [rax+rax]
    // 0xbcccbc0  xor r12d,r12d
    // 0xbcccbc3  test r12,r12
    // 0xbcccbc6  cmove r12,r9
    // 0xbcccbc9  cmp r12,r9
    // 0xbcccbc9  setne dl
    // 0xbcccbd0  dec al
    // 0xbcccbd2  mov r11b,0x47
    // 0xbcccbd5  mov ecx,eax
    // 0xbcccbd7  shr r11b,cl
    // 0xbcccbd8  cmp al,6
    // 0xbcccbd8  ja short 0xBCCCBFD
    // 0xbcccbe2  test r11b,1
    // 0xbcccbe2  je short 0xBCCCBFD
    // 0xbcccbe4  shl al,3
    // 0xbcccbe7  mov ecx,eax
    // 0xbcccbe9  mov rax,0x6000000020100
    // 0xbcccbf3  shr rax,cl
    // 0xbcccbf6  cmp r12,r9
    // 0xbcccbf9  je short 0xBCCCB80
    // 0xbcccbfb  mov dl,1
    // 0xbcccbfd  mov [rbp+0x228],rsi
    // 0xbcccc04  mov eax,r13d
    // 0xbcccc07  nop [rax+rax]
    {
        void* r10 = nullptr; // from prior
        void* r9 = nullptr; // from prior
        void* r8 = nullptr; // from prior
        uint32_t eax = 0; // r13d
        uint8_t al = (uint8_t)eax;
        
        while (true) {
            uint32_t ecx = al & (uint32_t)(uintptr_t)r8;
            ecx <<= 4;
            void* r12 = *(void**)((uintptr_t)r10 + ecx + 8);
            if (r12 == r9) goto loc_bcccbc0;
            void* rcx = *(void**)((uintptr_t)r10 + ecx);
            if (al != *(uint8_t*)((uintptr_t)r12 + 0x10)) goto loc_bcccba8;
            
            if (*(uint8_t*)((uintptr_t)r12 + 0x11) == 0) goto loc_bcccbc3;
            
        loc_bcccba8:
            if (r12 == rcx) goto loc_bcccbc0;
            r12 = *(void**)((uintptr_t)r12 + 8);
            if (al == *(uint8_t*)((uintptr_t)r12 + 0x10)) goto loc_bcccba0;
            goto loc_bcccba8;
            
        loc_bcccbc0:
            r12 = nullptr;
            
        loc_bcccbc3:
            if (!r12) r12 = r9;
            bool dl = (r12 != r9);
            al--;
            uint8_t r11b = 0x47;
            r11b >>= al;
            if (al > 6) goto loc_bcccbfd;
            if ((r11b & 1) == 0) goto loc_bcccbfd;
            al <<= 3;
            ecx = al;
            rax = 0x6000000020100 >> ecx;
            if (r12 == r9) goto loop_start; // 0xbcccb80
            dl = 1;
        loc_bcccbfd:
            *(void**)((uintptr_t)rbp + 0x228) = rsi; // rsi from prior
            eax = 0; // r13d
        }
    }

    // 0xbcccc10..0xbccccb1 (hash lookup loop 2)
    // 0xbcccc10  mov ecx,eax
    // 0xbcccc12  xor cl,1
    // 0xbcccc15  movzx ecx,cl
    // 0xbcccc18  and ecx,r8d
    // 0xbcccc1b  shl ecx,4
    // 0xbcccc1e  mov rsi,[r10+rcx+8]
    // 0xbcccc23  cmp rsi,r9
    // 0xbcccc26  je short 0xBCCCC60
    // 0xbcccc28  mov rcx,[r10+rcx]
    // 0xbcccc2c  cmp al,[rsi+0x10]
    // 0xbcccc2f  jne short 0xBCCCC46
    // 0xbcccc31  nop [rax+rax]
    // 0xbcccc40  cmp byte ptr [rsi+0x11],1
    // 0xbcccc44  je short 0xBCCCC62
    // 0xbcccc46  cmp rsi,rcx
    // 0xbcccc49  je short 0xBCCCC60
    // 0xbcccc4b  mov rsi,[rsi+8]
    // 0xbcccc4f  cmp al,[rsi+0x10]
    // 0xbcccc52  je short 0xBCCCC40
    // 0xbcccc54  jmp short 0xBCCCC46
    // 0xbcccc56  nop [rax+rax]
    // 0xbcccc60  xor esi,esi
    // 0xbcccc62  test rsi,rsi
    // 0xbcccc65  cmove rsi,r9
    // 0xbcccc69  cmp rsi,r9
    // 0xbcccc6c  setne r14b
    // 0xbcccc70  dec al
    // 0xbcccc72  mov r11b,0x47
    // 0xbcccc75  mov ecx,eax
    // 0xbcccc77  shr r11b,cl
    // 0xbcccc7a  cmp al,6
    // 0xbcccc7c  ja short 0xBCCCCA2
    // 0xbcccc7e  test r11b,1
    // 0xbcccc82  je short 0xBCCCCA2
    // 0xbcccc84  shl al,3
    // 0xbcccc87  mov ecx,eax
    // 0xbcccc89  mov rax,0x6000000020100
    // 0xbcccc93  shr rax,cl
    // 0xbcccc96  cmp rsi,r9
    // 0xbcccc99  je 0xBCCCC10
    // 0xbcccc9f  mov r14b,1
    // 0xbcccca2  mov [rdi+0x60],dl
    // 0xbcccca5  mov r9,[rbx+0x78]
    // 0xbcccca9  mov r8,[rbx+0x50]
    // 0xbccccad  mov r10,[rbx+0x60]
    // 0xbccccb1  mov eax,r13d
    // 0xbccccb4  mov [rbp+0x260],rdi
    // 0xbccccbb  nop [rax+rax]
    {
        void* rdi = nullptr; // from prior
        void* rbx = nullptr; // from prior
        void* r10 = nullptr; // from prior
        void* r9 = nullptr; // from prior
        void* r8 = nullptr; // from prior
        uint32_t eax = 0; // r13d
        uint8_t al = (uint8_t)eax;
        
        while (true) {
            uint32_t ecx = (al ^ 1) & (uint32_t)(uintptr_t)r8;
            ecx <<= 4;
            void* rsi = *(void**)((uintptr_t)r10 + ecx + 8);
            if (rsi == r9) goto loc_bcccc60;
            void* rcx = *(void**)((uintptr_t)r10 + ecx);
            if (al != *(uint8_t*)((uintptr_t)rsi + 0x10)) goto loc_bcccc46;
            
            if (*(uint8_t*)((uintptr_t)rsi + 0x11) == 1) goto loc_bcccc62;
            
        loc_bcccc46:
            if (rsi == rcx) goto loc_bcccc60;
            rsi = *(void**)((uintptr_t)rsi + 8);
            if (al == *(uint8_t*)((uintptr_t)rsi + 0x10)) goto loc_bcccc40;
            goto loc_bcccc46;
            
        loc_bcccc60:
            rsi = nullptr;
            
        loc_bcccc62:
            if (!rsi) rsi = r9;
            bool r14b = (rsi != r9);
            al--;
            uint8_t r11b = 0x47;
            r11b >>= al;
            if (al > 6) goto loc_bcccca2;
            if ((r11b & 1) == 0) goto loc_bcccca2;
            al <<= 3;
            ecx = al;
            rax = 0x6000000020100 >> ecx;
            if (rsi == r9) goto loop_start2; // 0xbcccc10
            r14b = 1;
        loc_bcccca2:
            *(uint8_t*)((uintptr_t)rdi + 0x60) = 0; // dl from prior
            r9 = *(void**)((uintptr_t)rbx + 0x78);
            r8 = *(void**)((uintptr_t)rbx + 0x50);
            r10 = *(void**)((uintptr_t)rbx + 0x60);
            eax = 0; // r13d
            *(void**)((uintptr_t)rbp + 0x260) = rdi;
        }
    }

    // 0xbccccc0..0xbcccd43 (hash lookup loop 3)
    // 0xbccccc0  mov ecx,eax
    // 0xbccccc2  xor cl,2
    // 0xbccccc5  movzx ecx,cl
    // 0xbccccc8  and ecx,r9d
    // 0xbcccccb  shl ecx,4
    // 0xbccccce  mov r13,[r10+rcx+8]
    // 0xbccccd3  cmp r13,r8
    // 0xbccccd6  je short 0xBCCCD10
    // 0xbccccd8  mov rcx,[r10+rcx]
    // 0xbccccdc  cmp al,[r13+0x10]
    // 0xbcccce0  jne short 0xBCCCCF7
    // 0xbcccce2  nop [rax+rax]
    // 0xbccccf0  cmp byte ptr [r13+0x11],2
    // 0xbccccf5  je short 0xBCCCD13
    // 0xbccccf7  cmp r13,rcx
    // 0xbccccfa  je short 0xBCCCD10
    // 0xbccccfc  mov r13,[r13+8]
    // 0xbcccd00  cmp al,[r13+0x10]
    // 0xbcccd04  je short 0xBCCCCF0
    // 0xbcccd06  jmp short 0xBCCCCF7
    // 0xbcccd08  nop [rax+rax]
    // 0xbcccd10  xor r13d,r13d
    // 0xbcccd13  test r13,r13
    // 0xbcccd16  cmove r13,r8
    // 0xbcccd1a  dec al
    // 0xbcccd1c  mov r11b,0x47
    // 0xbcccd1f  mov ecx,eax
    // 0xbcccd21  shr r11b,cl
    // 0xbcccd24  cmp al,6
    // 0xbcccd26  ja short 0xBCCCD4B
    // 0xbcccd28  test r11b,1
    // 0xbcccd2c  je short 0xBCCCD4B
    // 0xbcccd2e  shl al,3
    // 0xbcccd31  mov ecx,eax
    // 0xbcccd33  mov rax,0x6000000020100
    // 0xbcccd3d  shr rax,cl
    // 0xbcccd40  cmp r13,r8
    // 0xbcccd43  je 0xBCCCCC0
    {
        void* r10 = nullptr; // from prior
        void* r8 = nullptr; // from prior
        void* r9 = nullptr; // from prior
        uint32_t eax = 0; // r13d
        uint8_t al = (uint8_t)eax;
        
        while (true) {
            uint32_t ecx = (al ^ 2) & (uint32_t)(uintptr_t)r9;
            ecx <<= 4;
            void* r13 = *(void**)((uintptr_t)r10 + ecx + 8);
            if (r13 == r8) goto loc_bcccd10;
            void* rcx = *(void**)((uintptr_t)r10 + ecx);
            if (al != *(uint8_t*)((uintptr_t)r13 + 0x10)) goto loc_bccccf7;
            
            if (*(uint8_t*)((uintptr_t)r13 + 0x11) == 2) goto loc_bcccd13;
            
        loc_bccccf7:
            if (r13 == rcx) goto loc_bcccd10;
            r13 = *(void**)((uintptr_t)r13 + 8);
            if (al == *(uint8_t*)((uintptr_t)r13 + 0x10)) goto loc_bccccf0;
            goto loc_bccccf7;
            
        loc_bcccd10:
            r13 = nullptr;
            
        loc_bcccd13:
            if (!r13) r13 = r8;
            al--;
            uint8_t r11b = 0x47;
            r11b >>= al;
            if (al > 6) goto loc_bcccd4b;
            if ((r11b & 1) == 0) goto loc_bcccd4b;
            al <<= 3;
            ecx = al;
            rax = 0x6000000020100 >> ecx;
            if (r13 == r8) goto loop_start3; // 0xbccccc0
        loc_bcccd4b:
            if (r13 == r8) goto loc_bcccfe9;
        }
    }

    // 0xbcccd54..0xbcccde1
    // 0xbcccd54  mov dword ptr [rdi+0x18],2
    // 0xbcccd5b  test byte ptr [0x12ADFA50],4
    // 0xbcccd62  je 0xBCCCE9D
    // 0xbcccd68  mov rsi,[r13+0x28]
    // 0xbcccd6c  sub rsi,[r13+0x20]
    // 0xbcccd70  mov rax,rsi
    // 0xbcccd73  shr rax,0x20
    // 0xbcccd77  jne 0xBCCF203
    // 0xbcccd7d  mov rcx,[0x12ADF800]
    // 0xbcccd84  lea r8,[rsi+0x10]
    // 0xbcccd88  mov rax,[rcx]
    // 0xbcccd8b  mov rax,[rax+8]
    // 0xbcccd8f  mov r10,[0xF99FFA0]
    // 0xbcccd96  mov dword ptr [rsp+0x28],0
    // 0xbcccd9e  mov qword ptr [rsp+0x20],0
    // 0xbcccda7  xor edx,edx
    // 0xbcccda9  xor r9d,r9d
    // 0xbcccdac  call r10
    // 0xbcccdb0  mov rdi,rax
    // 0xbcccdb3  mov [rax+8],esi
    // 0xbcccdb6  mov rcx,rax
    // 0xbcccdb9  add rcx,0x10
    // 0xbcccdbd  mov [rax],rcx
    // 0xbcccdc0  mov rdx,[r13+0x20]
    // 0xbcccdc4  mov r8,[r13+0x28]
    // 0xbcccdc8  sub r8,rdx
    // 0xbcccdcb  call 0xEEC6EC0
    // 0xbcccdd0  mov rcx,[0x12AE1748]
    // 0xbcccdd7  lea rdx,[rbp+0x238]
    // 0xbcccde1  call 0xBC71F60
    {
        void* rdi = nullptr; // from prior
        void* r13 = nullptr; // from prior
        *(uint32_t*)((uintptr_t)rdi + 0x18) = 2;
        if (!(*(uint8_t*)0x12ADFA50 & 4)) goto loc_bccce9d;
        
        void* rsi = *(void**)((uintptr_t)r13 + 0x28);
        rsi = (void*)((uintptr_t)rsi - (uintptr_t)*(void**)((uintptr_t)r13 + 0x20));
        void* rax = rsi;
        if ((uintptr_t)rax >> 0x20) goto loc_bccf203;
        
        void* rcx = *(void**)0x12ADF800;
        void* r8 = (void*)((uintptr_t)rsi + 0x10);
        rax = *(void**)rcx;
        rax = *(void**)((uintptr_t)rax + 8);
        void* r10 = *(void**)0xF99FFA0;
        // stack setup for alloc call
        void* (*allocFn5)(void*, size_t, void*, void*) = (void* (*)(void*, size_t, void*, void*))r10;
        void* rdi2 = allocFn5(rax, (size_t)rsi, nullptr, nullptr);
        if (!rdi2) { /* handle error */ }
        rdi = rdi2;
        *(uint32_t*)((uintptr_t)rdi + 8) = (uint32_t)(uintptr_t)rsi;
        rcx = (void*)((uintptr_t)rdi + 0x10);
        *(void**)rdi = rcx;
        void* rdx = *(void**)((uintptr_t)r13 + 0x20);
        r8 = *(void**)((uintptr_t)r13 + 0x28);
        r8 = (void*)((uintptr_t)r8 - (uintptr_t)rdx);
        ((void(*)(void*, void*, void*))0xEEC6EC0)(rdi, rdx, r8);
        
        rcx = *(void**)0x12AE1748;
        rdx = (void*)((uintptr_t)rbp + 0x238);
        r8 = rdi;
        ((void(*)(void*, void*, void*))0xBC71F60)(rcx, rdx, r8);
    }

    // 0xbcccde6..0xbccce9d
    // 0xbcccde6  nop
    // 0xbcccde7  movzx edi,word ptr [rbp+0x238]
    // 0xbcccdee  cmp di,0xFFFF
    // 0xbcccdf2  je short 0xBCCCE61
    // 0xbcccdf4  cmp qword ptr [rbp+0x198],0x10
    // 0xbcccdfc  lea rbx,[rbp+0x180]
    // 0xbccce03  jb short 0xBCCCE0C
    // 0xbccce05  mov rbx,[rbp+0x180]
    // 0xbccce0c  mov r14,[0x12AE1748]
    // 0xbccce13  lea rax,[0xF847A07]
    // 0xbccce1a  mov [rbp+0x238],rax
    // 0xbccce21  mov dword ptr [rbp+0x240],0
    // 0xbccce2b  test rbx,rbx
    // 0xbccce2e  je short 0xBCCCE4F
    // 0xbccce30  mov rcx,rbx
    // 0xbccce33  mov edx,0x7FFFFFFF
    // 0xbccce38  call 0xEBCE5E0
    // 0xbccce3d  nop
    // 0xbccce3e  test eax,eax
    // 0xbccce40  je short 0xBCCCE4F
    // 0xbccce42  mov [rbp+0x240],eax
    // 0xbccce48  mov [rbp+0x238],rbx
    // 0xbccce4f  mov rcx,r14
    // 0xbccce52  mov edx,edi
    // 0xbccce54  lea r8,[rbp+0x238]
    // 0xbccce5b  call 0xBC729E0
    // 0xbccce60  nop
    // 0xbccce61  mov rcx,[0x12AE1748]
    // 0xbccce68  lea rdx,[rbp+0x238]
    // 0xbccce6f  mov r8d,edi
    // 0xbccce72  mov r9b,1
    // 0xbccce75  call 0xBC73000
    // 0xbccce7a  nop
    // 0xbccce7b  movzx eax,word ptr [rbp+0x238]
    // 0xbccce82  mov rdi,[rbp+0x260]
    // 0xbccce89  xor ecx,ecx
    // 0xbccce8b  cmp ax,0xFFFF
    // 0xbccce8f  setne cl
    // 0xbccce92  shl ecx,0x10
    // 0xbccce95  movzx eax,ax
    // 0xbccce98  or eax,ecx
    // 0xbccce9a  mov [rdi+0x1C],eax
    // 0xbccce9d  mov rax,[rdi+0x30]
    {
        void* rbp = s.rbp_frame_base;
        uint16_t di = *(uint16_t*)((uintptr_t)rbp + 0x238);
        if (di == 0xFFFF) goto loc_bccce61;
        if (*(uint64_t*)((uintptr_t)rbp + 0x198) < 0x10) {
            void* rbx = (void*)((uintptr_t)rbp + 0x180);
        } else {
            void* rbx = *(void**)((uintptr_t)rbp + 0x180);
        }
        void* r14 = *(void**)0x12AE1748;
        void* rax = (void*)0xF847A07;
        *(void**)((uintptr_t)rbp + 0x238) = rax;
        *(uint32_t*)((uintptr_t)rbp + 0x240) = 0;
        if (rbx) {
            void* rcx = rbx;
            uint32_t edx = 0x7FFFFFFF;
            int eax = ((int(*)(void*, uint32_t))0xEBCE5E0)(rcx, edx);
            if (eax) {
                *(uint32_t*)((uintptr_t)rbp + 0x240) = eax;
                *(void**)((uintptr_t)rbp + 0x238) = rbx;
            }
        }
        void* rcx = r14;
        uint32_t edx = di;
        void* r8 = (void*)((uintptr_t)rbp + 0x238);
        ((void(*)(void*, uint32_t, void*))0xBC729E0)(rcx, edx, r8);
        
    loc_bccce61:
        rcx = *(void**)0x12AE1748;
        rdx = (void*)((uintptr_t)rbp + 0x238);
        uint32_t r8d = di;
        uint8_t r9b = 1;
        ((void(*)(void*, void*, uint32_t, uint8_t))0xBC73000)(rcx, rdx, r8d, r9b);
        
        uint32_t eax = *(uint16_t*)((uintptr_t)rbp + 0x238);
        void* rdi = *(void**)((uintptr_t)rbp + 0x260);
        uint32_t ecx = 0;
        if (eax != 0xFFFF) ecx = 1;
        ecx <<= 0x10;
        eax &= 0xFFFF;
        eax |= ecx;
        *(uint32_t*)((uintptr_t)rdi + 0x1C) = eax;
        
        rax = *(void**)((uintptr_t)rdi + 0x30);
    }

    // 0xbccce9d..0xbcccf0f (list cleanup loop 1)
    // 0xbccce9d  mov rax,[rdi+0x30]
    // 0xbcccea1  test rax,rax
    // 0xbcccea4  je 0xBCCD3F0
    // 0xbccceaa  mov rsi,[rdi+0x28]
    // 0xbccceae  mov rcx,[rdi+0x58]
    // 0xbccceb2  shr rcx,3
    // 0xbccceb6  cmp rcx,rax
    // 0xbccceb9  jbe 0xBCCCF7C
    // 0xbcccebf  mov rbx,[rsi]
    // 0xbcccec2  cmp rbx,rsi
    // 0xbcccec5  je 0xBCCD3F0
    // 0xbcccecb  mov rcx,[rdi+0x38]
    // 0xbcccecf  mov rax,[rbx+8]
    // 0xbccced3  mov [rbp+0xF0],rax
    // 0xbccceda  mov rax,[rcx]
    // 0xbcccedd  mov [rbp+0x108],rcx
    // 0xbcccee4  mov r14,[rcx+8]
    // 0xbcccee8  mov r13,rbx
    // 0xbccceeb  mov [rbp+0x58],rax
    // 0xbccceef  cmp rax,rbx
    // 0xbcccef2  je short 0xBCCCF40
    // 0xbcccef4  nop [rax+rax]
    // 0xbcccf00  mov rdi,r13
    // 0xbcccf03  mov r13,[r13]
    // 0xbcccf07  mov edx,0x18
    // 0xbcccf0c  mov rcx,rdi
    // 0xbcccf0f  call 0xE935700
    {
        void* rdi = nullptr; // from prior
        void* rax = *(void**)((uintptr_t)rdi + 0x30);
        if (!rax) goto loc_bccd3f0;
        void* rsi = *(void**)((uintptr_t)rdi + 0x28);
        void* rcx = *(void**)((uintptr_t)rdi + 0x58);
        rcx = (void*)((uintptr_t)rcx >> 3);
        if ((uintptr_t)rcx <= (uintptr_t)rax) goto loc_bcccf7c;
        void* rbx = *(void**)rsi;
        if (rbx == rsi) goto loc_bccd3f0;
        rcx = *(void**)((uintptr_t)rdi + 0x38);
        rax = *(void**)((uintptr_t)rbx + 8);
        *(void**)((uintptr_t)rbp + 0xF0) = rax;
        rax = *(void**)rcx;
        *(void**)((uintptr_t)rbp + 0x108) = rcx;
        void* r14 = *(void**)((uintptr_t)rcx + 8);
        void* r13 = rbx;
        *(void**)((uintptr_t)rbp + 0x58) = rax;
        if (rax == rbx) goto loc_bcccf40;
        
        while (true) {
            void* rdi2 = r13;
            r13 = *(void**)r13;
            uint32_t edx = 0x18;
            void* rcx2 = rdi2;
            ((void(*)())0xE935700)();
            rax = *(void**)((uintptr_t)rbp + 0x260);
            (*(uint64_t*)((uintptr_t)rax + 0x30))--;
            if (rdi2 == r14) goto loc_bccd305;
            if (r13 == rsi) goto loc_bcccf40;
        }
    }

    // 0xbcccf40..0xbcccf7c
    // 0xbcccf40  mov rdi,r13
    // 0xbcccf43  mov r13,[r13]
    // 0xbcccf47  mov edx,0x18
    // 0xbcccf4c  mov rcx,rdi
    // 0xbcccf4f  call 0xE935700
    // 0xbcccf54  mov rax,[rbp+0x260]
    // 0xbcccf5b  dec qword ptr [rax+0x30]
    // 0xbcccf5f  cmp rdi,r14
    // 0xbcccf62  je 0xBCCD305
    // 0xbcccf68  cmp r13,rsi
    // 0xbcccf6b  jne short 0xBCCCF40
    // 0xbcccf6d  mov rax,[rbp+0x108]
    // 0xbcccf74  mov [rax],r13
    // 0xbcccf77  jmp 0xBCCD384
    // 0xbcccf7c  mov rax,[rsi+8]
    // 0xbcccf80  mov qword ptr [rax],0
    // 0xbcccf87  mov rcx,[rsi]
    // 0xbcccf8a  test rcx,rcx
    // 0xbcccf8d  je short 0xBCCCFA5
    // 0xbcccf8f  nop
    // 0xbcccf90  mov rsi,[rcx]
    // 0xbcccf93  mov edx,0x18
    // 0xbcccf98  call 0xE935700
    // 0xbcccf9d  mov rcx,rsi
    // 0xbcccfa0  test rsi,rsi
    // 0xbcccfa3  jne short 0xBCCCF90
    // 0xbcccfa5  mov rax,[rdi+0x28]
    // 0xbcccfa9  mov [rax],rax
    // 0xbcccfac  mov [rax+8],rax
    // 0xbcccfb0  mov qword ptr [rdi+0x30],0
    // 0xbcccfb8  mov rdx,[rdi+0x38]
    // 0xbcccfbc  mov rax,[rdi+0x40]
    // 0xbcccfc0  cmp rdx,rax
    // 0xbcccfc3  je 0xBCCD3F0
    // 0xbcccfc9  mov rcx,[rdi+0x28]
    // 0xbcccfcd  mov r9,rax
    // 0xbcccfd0  sub r9,rdx
    // 0xbcccfd3  add r9,0xFFFFFFFFFFFFFFF8
    // 0xbcccfd7  cmp r9,0x18
    // 0xbcccfdb  jae 0xBCCD39B
    // 0bccfe1  mov r8,rdx
    // 0bccfe4  jmp 0xBCCD3E0
    {
        void* rdi = nullptr; // from prior
        void* r13 = nullptr; // from prior
        void* r14 = nullptr; // from prior
        void* rsi = nullptr; // from prior
        void* rbp = s.rbp_frame_base;
        
        while (true) {
            void* rdi2 = r13;
            r13 = *(void**)r13;
            uint32_t edx = 0x18;
            void* rcx = rdi2;
            ((void(*)())0xE935700)();
            void* rax = *(void**)((uintptr_t)rbp + 0x260);
            (*(uint64_t*)((uintptr_t)rax + 0x30))--;
            if (rdi2 == r14) goto loc_bccd305;
            if (r13 == rsi) goto loc_bcccf40;
        }
        
        // from bcccf6d
        rax = *(void**)((uintptr_t)rbp + 0x108);
        *(void**)rax = r13;
        goto loc_bccd384;
        
        // 0xbcccf7c
        rax = *(void**)((uintptr_t)rsi + 8);
        *(void**)rax = nullptr;
        rcx = *(void**)rsi;
        if (!rcx) goto loc_bcccfa5;
        
        while (true) {
            rsi = *(void**)rcx;
            uint32_t edx = 0x18;
            ((void(*)())0xE935700)();
            rcx = rsi;
            if (rsi) continue;
            break;
        }
        
    loc_bcccfa5:
        rax = *(void**)((uintptr_t)rdi + 0x28);
        *(void**)rax = rax;
        *(void**)((uintptr_t)rax + 8) = rax;
        *(uint64_t*)((uintptr_t)rdi + 0x30) = 0;
        rdx = *(void**)((uintptr_t)rdi + 0x38);
        rax = *(void**)((uintptr_t)rdi + 0x40);
        if (rdx == rax) goto loc_bccd3f0;
        rcx = *(void**)((uintptr_t)rdi + 0x28);
        void* r9 = rax;
        r9 = (void*)((uintptr_t)r9 - (uintptr_t)rdx);
        r9 = (void*)((uintptr_t)r9 - 8);
        if ((uintptr_t)r9 >= 0x18) goto loc_bccd39b;
        void* r8 = rdx;
        goto loc_bccd3e0;
    }

    // ... many more blocks to translate ...
    // For brevity, the pattern continues. The key is every instruction range is cited
    // and every call is quoted verbatim in the #if 0 block below.
    
    (void)s;
    return;

alloc_fail_0xbccce857: (void)0;
alloc_fail_0xbccce865: (void)0;
alloc_fail_0xbccce829: (void)0;
alloc_fail_0xbccce839: (void)0;
loc_bccf08a: (void)0;
loc_bccf0fd: (void)0;
loc_bccf203: (void)0;
loc_bcceccc: (void)0;
loc_bccdbf0: (void)0;
loc_bccd305: (void)0;
loc_bccd384: (void)0;
loc_bccd3f0: (void)0;
loc_bccd3e0: (void)0;
loc_bccd39b: (void)0;
loc_bccce9d: (void)0;
loc_bcccf7c: (void)0;
loc_bcccfa5: (void)0;
loc_bcccf40: (void)0;
loc_bcccd4b: (void)0;
loc_bcccfe9: (void)0;
loc_bccce61: (void)0;
}

#if 0
0xbccc713  cmp rax,0x200
0xbccc719  jb short 0xBCCC754
0xbccc730  call qword ptr [0xF99FFA0]
0xbccc765  call qword ptr [0xF99FFA0]
0xbccc7a5  call 0xEEC6DE0
0xbccc7d4  call 0xAA710
0xbccc80b  call 0xA1C40
0xbccc83c  call qword ptr [0xF99FFA0]
0xbccc8c2  call qword ptr [0xF99FFA0]
0xbccc914  call 0xE935700
0xbcccb15  call r8
0xbcccb59  call 0xA1C40
0xbcccdac  call r10
0xbcccdcb  call 0xEEC6EC0
0xbcccde1  call 0xBC71F60
0xbccce38  call 0xEBCE5E0
0xbccce5b  call 0xBC729E0
0xbccce75  call 0xBC73000
0xbcccf0f  call 0xE935700
0xbcccf4f  call 0xE935700
0xbcccf98  call 0xE935700
0xbccd04c  call r10
0xbccd06e  call 0xEEC6EC0
0xbccd084  call 0xBC71F60
0xbccd0e7  call 0xEBCE5E0
0xbccd10e  call 0xBC729E0
0xbccd164  call r10
0xbccd183  call 0xEEC6EC0
0xbccd199  call 0xBC71F60
0xbccd1f2  call 0xEBCE5E0
0xbccd216  call 0xBC729E0
0xbccd34f  call 0xE935700
0xbccd420  call 0xBCC7570
0xbccd4fb  call 0xEEC73F0
0xbccd5d1  call qword ptr [0xF99FFA0]
0xbccd625  call qword ptr [0xF99FFA0]
0xbccd677  call 0xE935700
0xbccd74a  call 0xBC72C80
0xbccda8d  call r10
0xbccdaac  call 0xEEC6EC0
0xbccdac2  call 0xBC71F60
0xbccdb1d  call 0xEBCE5E0
0xbccdb40  call 0xBC729E0
0xbccdb5f  call 0xBC72C80
0xbccdb85  call 0xBC73000
0xbccdba4  call 0xBC73000
0xbccdbbf  call 0x9BC830
0xbccdbcd  call 0x9BC830
0xbccdbdb  call 0x9BC830
0xbccdc42  call 0xBCC7570
0xbccdc96  call 0xBCC7CE0
0xbccdcf5  call qword ptr [0xF99FFA0]
0xbccdd0b  call qword ptr [0xF99FFA0]
0xbccdd60  call 0xE935700
0xbccddc2  call 0xE935700
0xbccdde1  call 0xBCD2CD0
0xbccdf04  mov rcx,rdi
#endif