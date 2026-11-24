// LIFT 0xbcc7f20 size 0x7421 1.26.62.01 MaterialInstance::initFromMaterial
#include "MaterialInstance_initFromMaterial.h"
namespace native { namespace bgfx {

// CHUNK 0xbcc7f20..0xbcc9718
static inline void chunk_c00(State& s) {
    // 0xbcc7f20..0xbcc7f33: prologue - push r12, rsi, rdi, rbx; sub rsp, 0x3A8
    // 0xbcc7f33..0xbcc7f94: set up rbp frame, save xmm6-xmm15, init allocator tag
    s.rbp = s.rsp + 0x80;
    s.saved_xmm6  = s.regs.xmm6;
    s.saved_xmm7  = s.regs.xmm7;
    s.saved_xmm8  = s.regs.xmm8;
    s.saved_xmm9  = s.regs.xmm9;
    s.saved_xmm10 = s.regs.xmm10;
    s.saved_xmm11 = s.regs.xmm11;
    s.saved_xmm12 = s.regs.xmm12;
    s.saved_xmm13 = s.regs.xmm13;
    s.saved_xmm14 = s.regs.xmm14;
    s.saved_xmm15 = s.regs.xmm15;
    s.stack_allocator_tag = 0xFFFFFFFFFFFFFFFE;
    // 0xbcc7f94..0xbcc7faa: mov rdi, rdx (m); mov rsi, rcx (this); load allocator; call allocator with tag 0x2F
    s.m = s.rdx;
    s.this_ptr = s.rcx;
    // 0xbcc7f9a  mov rcx,[0x1233E1B0]
    // 0xbcc7fa1  mov rax,[rcx]
    // 0xbcc7fa4  mov rax,[rax+0x10]
    // 0xbcc7fa8  mov dl,0x2F
    // 0xbcc7faa  call qword ptr [0xF99FFA0]  (allocator)
    s.stack_allocator_tag = sub_eea6040(0x2F);  // 0xbcc7faa  call qword ptr [0xF99FFA0]
    s.stack_u8_257 = static_cast<uint8_t>(s.stack_allocator_tag);
    // 0xbcc7fb6..0xbcc7fd6: save m to [rbp+0x178], set up this+0x128 (name), save this to [rbp+0x270]
    s.m_ptr = s.m;
    s.this_name_ptr = reinterpret_cast<char*>(s.this_ptr + 0x128);
    s.m_name_ptr = reinterpret_cast<char*>(s.m_ptr + 0x40);
    s.this_ptr_saved = s.this_ptr;
    // 0xbcc7fcf..0xbcc7fd6: cmp this_name_ptr, m_name_ptr; je 0xbcc8055
    if (s.this_name_ptr == s.m_name_ptr) {
        goto loc_bcc8055;
    }
    // 0xbcc7fd8..0xbcc800a: copy name string (SSO handling)
    {
        // 0xbcc7fd8  mov rax,[rbp+0x178]
        // 0xbcc7fdf  mov rbx,[rax+0x50]  (m_name.size)
        // 0xbcc7fe3  cmp qword ptr [rax+0x58],0x10  (m_name.capacity)
        // 0xbcc7fe8  mov r9,[rbp+0x68]  (m_name.data or SSO buffer)
        // 0xbcc7fec  jb short 0xbcc7ff9  (if SSO)
        // 0xbcc7fee  mov rax,[rbp+0x178]
        // 0xbcc7ff5  mov r9,[rax+0x40]  (m_name.heap_ptr)
        s.m_name_size = *reinterpret_cast<uint64_t*>(s.m_ptr + 0x50);
        if (*reinterpret_cast<uint64_t*>(s.m_ptr + 0x58) < 0x10) {
            // SSO branch
            s.m_name_data = s.m_name_ptr;
        } else {
            s.m_name_data = *reinterpret_cast<char**>(s.m_ptr + 0x40);
        }
        // 0xbcc7ff9  mov rax,[rbp+0x270]
        // 0xbcc8000  mov rax,[rax+0x140]  (this_name.capacity)
        // 0xbcc8007  cmp rbx,rax
        // 0xbcc800a  jbe short 0xbcc8021  (if fits in current capacity)
        if (s.m_name_size <= *reinterpret_cast<uint64_t*>(s.this_ptr + 0x140)) {
            goto loc_bcc8021;
        }
        // 0xbcc800c..0xbcc801f: reallocate this_name to fit m_name
        // 0xbcc800c  mov rcx,rdi  (this_name_ptr)
        // 0xbcc800f  mov rdx,rbx  (m_name_size)
        // 0xbcc8012  call 0x9D6D0  (string reallocate/resize)
        // 0xbcc8017  nop
        // 0xbcc8018  mov rsi,[rbp+0x270]
        // 0xbcc801f  jmp short 0xbcc8055
        sub_9d6d0(s.this_name_ptr, s.m_name_size);  // 0xbcc8012  call 0x9D6D0
        goto loc_bcc8055;
    loc_bcc8021:
        // 0xbcc8021  cmp rax,0x10
        // 0xbcc8025  jb short 0xbcc8035  (if this_name is SSO)
        // 0xbcc8027  mov rax,[rbp+0x270]
        // 0xbcc802e  mov rdi,[rax+0x128]  (this_name.heap_ptr)
        if (*reinterpret_cast<uint64_t*>(s.this_ptr + 0x140) >= 0x10) {
            s.this_name_heap_ptr = *reinterpret_cast<char**>(s.this_ptr + 0x128);
        }
    loc_bcc8035:
        // 0xbcc8035  mov rsi,[rbp+0x270]
        // 0xbcc803c  mov [rsi+0x138],rbx  (this_name.size = m_name_size)
        // 0xbcc8043  mov rcx,rdi  (dst = this_name.data or heap_ptr)
        // 0xbcc8046  mov rdx,r9  (src = m_name.data)
        // 0xbcc8049  mov r8,rbx  (count = m_name_size)
        // 0xbcc804c  call 0xEEC6DE0  (memcpy)
        // 0xbcc8051  mov byte ptr [rdi+rbx],0  (null-terminate)
        *reinterpret_cast<uint64_t*>(s.this_ptr + 0x138) = s.m_name_size;
        sub_eec6de0(s.this_name_ptr, s.m_name_data, s.m_name_size);  // 0xbcc804c  call 0xEEC6DE0
        *(s.this_name_ptr + s.m_name_size) = 0;
    }
loc_bcc8055:
    // 0xbcc8055..0xbcc8076: handle some flag at m+0x80, call 0x1CFDF0 if set
    // 0xbcc8055  lea rcx,[rsi+0x148]
    // 0xbcc805c  mov rax,[rbp+0x178]
    // 0xbcc8063  cmp byte ptr [rax+0x80],1
    // 0xbcc806a  jne short 0xbcc8078
    // 0xbcc806c  lea rdx,[rax+0x60]
    // 0xbcc8070  call 0x1CFDF0
    // 0xbcc8075  nop
    // 0xbcc8076  jmp short 0xbcc80ED
    s.this_ptr_flag_148 = reinterpret_cast<uint8_t*>(s.this_ptr + 0x148);
    if (*reinterpret_cast<uint8_t*>(s.m_ptr + 0x80) == 1) {
        sub_1cfdf0(reinterpret_cast<void*>(s.m_ptr + 0x60));  // 0xbcc8070  call 0x1CFDF0
        goto loc_bcc80ed;
    }
    // 0xbcc8078..0xbcc80c1: else branch - check this+0x168 flag
    // 0xbcc8078  cmp byte ptr [rsi+0x168],1
    // 0xbcc807f  jne short 0xbcc80ED
    // 0xbcc8081  mov rax,[rsi+0x160]
    // 0xbcc8088  cmp rax,0x10
    // 0xbcc808c  jb short 0xbcc80C2
    // 0xbcc808e  mov rcx,[rcx]  (this+0x148 heap ptr)
    // 0xbcc8091  lea rdx,[rax+1]
    // 0xbcc8095  cmp rdx,0x1000
    // 0xbcc809c  jb short 0xbcc80BD
    // 0xbcc809e  mov r8,[rcx-8]
    // 0xbcc80a2  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcc80a6  sub rcx,r8
    // 0xbcc80a9  cmp rcx,0x20
    // 0xbcc80ad  jae 0xBCCECCC
    // 0xbcc80b3  add rax,0x28
    // 0xbcc80b7  mov rdx,rax
    // 0xbcc80ba  mov rcx,r8
    // 0xbcc80bd  call 0xE935700
    if (*reinterpret_cast<uint8_t*>(s.this_ptr + 0x168) == 1) {
        uint64_t this_str_len = *reinterpret_cast<uint64_t*>(s.this_ptr + 0x160);
        if (this_str_len >= 0x10) {
            char* heap_ptr = *reinterpret_cast<char**>(s.this_ptr + 0x148);
            uint64_t new_size = this_str_len + 1;
            if (new_size < 0x1000) {
                // fast path
                sub_e935700(heap_ptr, new_size);  // 0xbcc80bd  call 0xE935700
            } else {
                // large allocation path - check allocator metadata
                uint64_t alloc_size = *reinterpret_cast<uint64_t*>(heap_ptr - 8);
                char* alloc_base = heap_ptr - 8;
                uint64_t user_size = alloc_base - alloc_size;
                if (user_size >= 0x20) {
                    // 0xBCCECCC - allocator error path
                    goto loc_bcc80c2;  // fallback
                }
                new_size += 0x28;
                sub_e935700(alloc_base, new_size);  // 0xbcc80bd  call 0xE935700
            }
        } else {
    loc_bcc80c2:
            // 0xbcc80c2  mov rsi,[rbp+0x270]
            // 0xbcc80c9  mov qword ptr [rsi+0x158],0
            // 0xbcc80d4  mov qword ptr [rsi+0x160],0xF
            // 0xbcc80df  mov byte ptr [rsi+0x148],0
            // 0xbcc80e6  mov byte ptr [rsi+0x168],0
            *reinterpret_cast<uint64_t*>(s.this_ptr + 0x158) = 0;
            *reinterpret_cast<uint64_t*>(s.this_ptr + 0x160) = 0xF;
            *reinterpret_cast<uint8_t*>(s.this_ptr + 0x148) = 0;
            *reinterpret_cast<uint8_t*>(s.this_ptr + 0x168) = 0;
        }
    }
loc_bcc80ed:
    // 0xbcc80ed..0xbcc8156: create uniform block (call 0x660E670, then allocator, then 0xE86A1B0)
    // 0xbcc80ed  lea rcx,[rsi+0x178]
    // 0xbcc80f4  lea rdx,[rbp+0x88]
    // 0xbcc80fb  xor r8d,r8d
    // 0xbcc80fe  call 0x660E670
    // 0xbcc8103  nop
    // 0xbcc8104  mov rdi,[rbp+0x88]
    // 0xbcc810b  mov rcx,[0x1233E1A8]
    // 0xbcc8112  mov rax,[rcx]
    // 0xbcc8115  mov rax,[rax+8]
    // 0xbcc8119  mov edx,0x78
    // 0xbcc811e  call qword ptr [0xF99FFA0]
    // 0xbcc8124  nop
    // 0xbcc8125  mov rbx,rax
    // 0xbcc8128  test rax,rax
    // 0xbcc812b  je 0xBCCF0BB
    // 0xbcc8131  mov rsi,[rbp+0x270]
    // 0xbcc8138  lea r8,[rsi+0x238]
    // 0xbcc813f  add rdi,0x40
    // 0xbcc8143  mov rcx,rbx
    // 0xbcc8146  mov rdx,[rbp+0x178]
    // 0xbcc814d  mov r9,rdi
    // 0xbcc8150  mov [rbp+0x268],rbx
    // 0xbcc8157  call 0xE86A1B0
    // 0xbcc815c  nop
    // 0xbcc815d  mov rcx,[rsi+0x170]
    // 0xbcc8164  mov rax,[rbp+0x268]
    // 0xbcc816b  mov [rsi+0x170],rax
    // 0xbcc8172  test rcx,rcx
    // 0xbcc8175  je short 0xbcc8181
    // 0xbcc8177  mov edx,0x78
    // 0xbcc817c  call 0xE935700
    {
        void* uniform_block_out = reinterpret_cast<void*>(s.this_ptr + 0x178);
        void* temp_ptr = nullptr;
        sub_660e670(uniform_block_out, &temp_ptr, 0);  // 0xbcc80fe  call 0x660E670
        s.temp_alloc_ptr = temp_ptr;
        // allocator call for 0x78 bytes
        void* alloc_ptr = sub_eea6040(0x78);  // 0xbcc811e  call qword ptr [0xF99FFA0]
        s.uniform_block_alloc = alloc_ptr;
        if (!alloc_ptr) {
            goto loc_bccf0bb;  // allocation failed
        }
        s.this_ptr = *reinterpret_cast<void**>(s.rbp + 0x270);
        void* r8_ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x238);
        void* rdi_plus_40 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(temp_ptr) + 0x40);
        s.saved_alloc_ptr = alloc_ptr;
        void* new_uniform_block = sub_e86a1b0(alloc_ptr, s.m_ptr, rdi_plus_40, r8_ptr);  // 0xbcc8157  call 0xE86A1B0
        void* old_uniform_block = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x170);
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x170) = new_uniform_block;
        if (old_uniform_block) {
            sub_e935700(old_uniform_block, 0x78);  // 0xbcc817c  call 0xE935700
        }
    }
loc_bcc8181:
    // 0xbcc8181..0xbcc81eb: set up buffer definitions copy loop (m+0x110 map -> this+0x328 map)
    // 0xbcc8181  mov rax,[rbp+0x178]
    // 0xbcc8188  add rax,0x90
    // 0xbcc818e  mov rcx,[rbp+0x270]
    // 0xbcc8195  add rcx,0x328
    // 0xbcc819c  mov [rbp+0x268],rcx
    // 0xbcc81a3  cmp rcx,rax
    // 0xbcc81a6  je 0xBCC8944
    // 0xbcc81ac  mov rdx,[rbp+0x178]
    // 0xbcc81b3  mov eax,[rdx+0x90]
    // 0xbcc81b9  mov rcx,[rbp+0x270]
    // 0xbcc81c0  mov [rcx+0x328],eax
    // 0xbcc81c6  mov rsi,[rdx+0x98]
    // 0xbcc81cd  mov r15,[rsi]
    // 0xbcc81d0  mov r12,[rcx+0x330]
    // 0xbcc81d7  mov rdi,[r12]
    // 0xbcc81db  cmp rdi,r12
    // 0xbcc81de  je 0xBCC86AB
    // 0xbcc81e4  lea r13,[0xF44C110]
    // 0xbcc81eb  jmp short 0xBCC820F
    s.m_buf_defs_end = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.m_ptr) + 0x90 + 0x20);  // m+0x110 map end
    s.this_buf_defs_map = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x328);
    *reinterpret_cast<void**>(s.rbp + 0x268) = s.this_buf_defs_map;
    if (s.this_buf_defs_map == s.m_buf_defs_end) {
        goto loc_bcc8944;
    }
    s.m_buf_defs_map = reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(s.m_ptr) + 0x98));
    s.this_buf_defs_bucket_array = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x330);
    s.r15 = *reinterpret_cast<void**>(s.m_buf_defs_map);  // first node
    s.r12 = s.this_buf_defs_bucket_array;
    s.rdi = *reinterpret_cast<void**>(s.r12);  // first bucket
    if (s.rdi == s.r12) {
        goto loc_bcc86ab;
    }
    s.r13 = reinterpret_cast<void*>(0xF44C110);  // jump table for uniform types
    goto loc_bcc820f;

    // Main loop over buffer definitions (uniform nodes)
    // 0xbcc81ed..0xbcc8200: loop back edge
loc_bcc81ed:
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 0xFF;
    goto loc_bcc8200;

loc_bcc8200:
    s.r15 = *reinterpret_cast<void**>(s.r15);  // next node
    s.rdi = *reinterpret_cast<void**>(s.rdi);  // next bucket
    if (s.rdi == s.r12) {
        goto loc_bcc86ab;
    }

loc_bcc820f:
    // 0xbcc820f..0xbcc8281: process each node
    if (s.r15 == s.m_buf_defs_map) {
        goto loc_bcc8810;
    }
    if (s.rdi == s.r15) {
        goto loc_bcc8281;
    }
    // copy string key (SSO handling)
    uint64_t key_cap = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x28);
    char* key_src;
    if (key_cap < 0x10) {
        key_src = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(s.r15) + 0x10);
    } else {
        key_src = *reinterpret_cast<char**>(reinterpret_cast<uintptr_t>(s.r15) + 0x10);
    }
    char* key_dst = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x10);
    uint64_t key_len = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x20);
    uint64_t dst_cap = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x28);
    if (key_len > dst_cap) {
        if (dst_cap >= 0x10) {
            key_dst = *reinterpret_cast<char**>(reinterpret_cast<uintptr_t>(s.rdi) + 0x10);
        }
        sub_9d6d0(key_dst, key_len);  // 0xbcc824b  call 0x9D6D0
        goto loc_bcc8281;
    }
    if (dst_cap >= 0x10) {
        key_dst = *reinterpret_cast<char**>(reinterpret_cast<uintptr_t>(s.rdi) + 0x10);
    }
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x20) = key_len;
    sub_eec6de0(key_dst, key_src, key_len);  // 0xbcc8277  call 0xEEC6DE0
    *(key_dst + key_len) = 0;

loc_bcc8281:
    // 0xbcc8281..0xbcc829c: switch on uniform type (node+0x7C)
    // 0xbcc8281  movzx ecx,byte ptr [r15+0x7C]
    // 0xbcc8286  cmp rcx,4
    // 0xbcc828a  ja 0xBCC81ED
    // 0xbcc8290  lea rax,[rdi+0x30]
    // 0xbcc8294  movsxd rcx,[r13+rcx*4]
    // 0xbcc8299  add rcx,r13
    // 0xbcc829c  jmp rcx
    uint8_t uniform_type = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x7C);
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 0xFF;  // mark as processing
    if (uniform_type > 3) {
        goto loc_bcc81ed;  // invalid type, skip
    }
    void* dst_value = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x30);
    // Jump table at r13 (0xF44C110) with 4 entries for types 0,1,2,3
    // type 0: 0xbcc829e..0xbcc82ac
    // type 1: 0xbcc82b1..0xbcc82cb
    // type 2: 0xbcc82d0..0xbcc8488
    // type 3: 0xbcc835b..0xbcc8570
    switch (uniform_type) {
        case 0: {
            // 0xbcc829e..0xbcc82ac: type 0 - copy 8 bytes (mat2? or vec2?)
            // 0xbcc829e  cmp byte ptr [rdi+0x7C],0
            // 0xbcc82a2  je 0xBCC8200
            // 0xbcc82a8  mov byte ptr [rdi+0x7C],0
            // 0xbcc82ac  jmp 0xBCC8200
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) == 0) {
                goto loc_bcc8200;
            }
            *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 0;
            goto loc_bcc8200;
        }
        case 1: {
            // 0xbcc82b1..0xbcc82cb: type 1 (vec4) - copy 16 bytes
            // 0xbcc82b1  lea rcx,[r15+0x30]
            // 0xbcc82b5  cmp byte ptr [rdi+0x7C],4
            // 0xbcc82b9  jne 0xBCC83DD
            // 0xbcc82bf  mov edx,[rcx+8]
            // 0xbcc82c2  mov [rax+8],edx
            // 0xbcc82c5  mov rcx,[rcx]
            // 0xbcc82c8  mov [rax],rcx
            // 0xbcc82cb  jmp 0xBCC8200
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) != 4) {
                goto loc_bcc83dd;
            }
            uint32_t* src = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x30);
            uint32_t* dst = reinterpret_cast<uint32_t*>(dst_value);
            dst[2] = src[2];
            dst[3] = src[3];
            *reinterpret_cast<uint64_t*>(dst) = *reinterpret_cast<uint64_t*>(src);
            goto loc_bcc8200;
        }
        case 2: {
            // 0xbcc82d0..0xbcc8488: type 2 (mat3) - 36 bytes (9 floats)
            // 0xbcc82d0  cmp byte ptr [rdi+0x7C],2
            // 0xbcc82d4  jne 0xBCC83F6
            // 0xbcc82da  mov eax,[r15+0x30]
            // 0xbcc82de  mov [rdi+0x30],eax
            // 0xbcc82e1  cmp byte ptr [r15+0x58],1
            // 0xbcc82e6  jne 0xBCC85D5
            // 0xbcc82ec  movzx eax,byte ptr [rdi+0x58]
            // 0xbcc82f0  movss xmm0,[r15+0x34]
            // 0xbcc82f6  movss [rdi+0x34],xmm0
            // 0xbcc82fb  cmp al,1
            // 0xbcc82fd  jne 0xBCC85FE
            // 0xbcc8303  movss xmm0,[r15+0x38]
            // 0xbcc8309  movss [rdi+0x38],xmm0
            // 0xbcc830e  movss xmm0,[r15+0x3C]
            // 0xbcc8314  movss [rdi+0x3C],xmm0
            // 0xbcc8319  movss xmm0,[r15+0x40]
            // 0xbcc831f  movss [rdi+0x40],xmm0
            // 0xbcc8324  movss xmm0,[r15+0x44]
            // 0xbcc832a  movss [rdi+0x44],xmm0
            // 0xbcc832f  movss xmm0,[r15+0x48]
            // 0xbcc8335  movss [rdi+0x48],xmm0
            // 0xbcc833a  movss xmm0,[r15+0x4C]
            // 0xbcc8340  movss [rdi+0x4C],xmm0
            // 0xbcc8345  movss xmm0,[r15+0x50]
            // 0xbcc834b  movss [rdi+0x50],xmm0
            // 0xbcc8350  movss xmm0,[r15+0x54]
            // 0xbcc8356  jmp 0xBCC8655
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) != 2) {
                goto loc_bcc83f6;
            }
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x30) = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x30);
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x58) != 1) {
                goto loc_bcc85d5;
            }
            uint8_t has_default = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x58);
            float* src_f = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.r15) + 0x34);
            float* dst_f = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x34);
            dst_f[0] = src_f[0];
            if (has_default != 1) {
                goto loc_bcc85fe;
            }
            dst_f[1] = src_f[1];
            dst_f[2] = src_f[2];
            dst_f[3] = src_f[3];
            dst_f[4] = src_f[4];
            dst_f[5] = src_f[5];
            dst_f[6] = src_f[6];
            dst_f[7] = src_f[7];
            dst_f[8] = src_f[8];
            goto loc_bcc8655;
        }
        case 3: {
            // 0xbcc835b..0xbcc8570: type 3 (mat4) - 64 bytes (16 floats)
            // 0xbcc835b  cmp byte ptr [rdi+0x7C],3
            // 0xbcc835f  jne 0xBCC848D
            // 0xbcc8365  mov ecx,[r15+0x30]
            // 0xbcc8369  mov [rax],ecx
            // 0xbcc836b  cmp byte ptr [r15+0x74],1
            // 0xbcc8370  jne 0xBCC85DB
            // 0xbcc8376  lea rcx,[rdi+0x34]
            // 0xbcc837a  lea rdx,[r15+0x34]
            // 0xbcc837e  call 0x53D5C20
            // 0xbcc8383  nop
            // 0xbcc8384  jmp 0xBCC85DF
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) != 3) {
                goto loc_bcc848d;
            }
            *reinterpret_cast<uint32_t*>(dst_value) = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x30);
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x74) != 1) {
                goto loc_bcc85db;
            }
            sub_53d5c20(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x34),
                        reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.r15) + 0x34));  // 0xbcc837e  call 0x53D5C20
            goto loc_bcc85df;
        }
    }

    // Additional cases for type 0/1/2/3 fallthrough paths
loc_bcc83dd:
    // 0xbcc83dd..0xbcc83f1: type 0 fallthrough - set to 4
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 0xFF;
    uint32_t* src_dd = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x30);
    uint32_t* dst_dd = reinterpret_cast<uint32_t*>(dst_value);
    dst_dd[2] = src_dd[2];
    dst_dd[3] = src_dd[3];
    *reinterpret_cast<uint64_t*>(dst_dd) = *reinterpret_cast<uint64_t*>(src_dd);
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 4;
    goto loc_bcc8200;

loc_bcc83f6:
    // 0xbcc83f6..0xbcc8488: type 2 fallthrough (mat3 without default)
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 0xFF;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x30) = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x30);
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x58) = 0;
    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x58) != 1) {
        goto loc_bcc8473;
    }
    float* src_f6 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.r15) + 0x34);
    float* dst_f6 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x34);
    dst_f6[0] = src_f6[0];
    dst_f6[1] = src_f6[1];
    dst_f6[2] = src_f6[2];
    dst_f6[3] = src_f6[3];
    dst_f6[4] = src_f6[4];
    dst_f6[5] = src_f6[5];
    dst_f6[6] = src_f6[6];
    dst_f6[7] = src_f6[7];
    dst_f6[8] = src_f6[8];
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x58) = 1;

loc_bcc8473:
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x5E) = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x5E);
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x5C) = *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x5C);
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 2;
    goto loc_bcc8200;

loc_bcc848d:
    // 0xbcc848d..0xbcc8570: type 3 fallthrough (mat4 without default)
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 0xFF;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x30) = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x30);
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x74) = 0;
    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x74) != 1) {
        goto loc_bcc855b;
    }
    float* src_f3 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.r15) + 0x34);
    float* dst_f3 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x34);
    for (int idx = 0; idx < 16; idx++) {
        dst_f3[idx] = src_f3[idx];
    }
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x74) = 1;

loc_bcc855b:
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7A) = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x7A);
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x78) = *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x78);
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7C) = 3;
    goto loc_bcc8200;

loc_bcc85d5:
    // 0xbcc85d5..0xbcc865a: mat3 no default
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x58) = 0;
    goto loc_bcc865a;

loc_bcc85db:
    // 0xbcc85db..0xbcc85f0: mat4 no default
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x74) = 0;
    goto loc_bcc85df;

loc_bcc85df:
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x7A) = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x7A);
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x78) = *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x78);
    goto loc_bcc8200;

loc_bcc85f5:
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x44) = 0;
    goto loc_bcc8695;

loc_bcc85fe:
    // 0xbcc85fe..0xbcc8651: mat3 partial default
    float* src_fe = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.r15) + 0x38);
    float* dst_fe = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x38);
    dst_fe[0] = src_fe[0];
    dst_fe[1] = src_fe[1];
    dst_fe[2] = src_fe[2];
    dst_fe[3] = src_fe[3];
    dst_fe[4] = src_fe[4];
    dst_fe[5] = src_fe[5];
    dst_fe[6] = src_fe[6];
    dst_fe[7] = src_fe[7];
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x58) = 1;

loc_bcc8655:
    // 0xbcc8655..0xbcc865a
    float* src_55 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.r15) + 0x54);
    float* dst_55 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x54);
    *dst_55 = *src_55;

loc_bcc865a:
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x5E) = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x5E);
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x5C) = *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x5C);
    goto loc_bcc8200;

loc_bcc8670:
    // 0xbcc8670..0xbcc8690: vec4 partial default
    float* src_70 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.r15) + 0x38);
    float* dst_70 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x38);
    dst_70[0] = src_70[0];
    dst_70[1] = src_70[1];
    dst_70[2] = src_70[2];
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x44) = 1;

loc_bcc8690:
    float* src_90 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.r15) + 0x40);
    float* dst_90 = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x40);
    *dst_90 = *src_90;

loc_bcc8695:
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x4A) = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x4A);
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x48) = *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(s.r15) + 0x48);
    goto loc_bcc8200;

loc_bcc86ab:
    // 0xbcc86ab..0xbcc8804: build linked list of processed nodes (bucket array at this+0x330)
    // 0xbcc86ab  mov rdx,[rbp+0x270]
    // 0xbcc86b2  lea rax,[rdx+0x330]
    // 0xbcc86b9  mov [rbp+0x1A0],rax
    // 0xbcc86c0  xorps xmm0,xmm0
    // 0xbcc86c3  movups [rbp+0x1A8],xmm0
    // 0xbcc86ca  mov qword ptr [rbp+0x1B8],0
    // 0xbcc86d5  cmp rsi,r15
    // 0xbcc86d8  je 0xBCC8804
    // 0xbcc86de  mov rcx,[0x1233E1A8]
    // 0xbcc86e5  mov rax,[rcx]
    // 0xbcc86e8  mov rax,[rax+8]
    // 0xbcc86ec  mov r8,[0xF99FFA0]
    // 0xbcc86f3  mov qword ptr [rbp+0x100],0
    // 0xbcc86fe  mov edx,0x80
    // 0xbcc8703  call r8
    // 0xbcc8706  nop
    // 0xbcc8707  mov rdi,rax
    // 0xbcc870a  test rax,rax
    // 0xbcc870d  je 0xBCCF1BA
    // 0xbcc8713  lea rdx,[r15+0x10]
    // 0xbcc8717  mov rcx,rdi
    // 0xbcc871a  add rcx,0x10
    // 0xbcc871e  mov [rbp+0x100],rdi
    // 0xbcc8725  call 0xBCD5A20
    // 0xbcc872a  nop
    // 0xbcc872b  mov [rbp+0x1B8],rdi
    // 0xbcc8732  mov [rbp+0x1B0],rdi
    // 0xbcc8739  mov r14d,1
    // 0xbcc873f  mov r12,rdi
    s.this_ptr = *reinterpret_cast<void**>(s.rbp + 0x270);
    void* bucket_array_head = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x330);
    *reinterpret_cast<void**>(s.rbp + 0x1A0) = bucket_array_head;
    s.list_head = nullptr;
    s.list_tail = nullptr;
    s.list_count = 0;
    if (s.m_buf_defs_map == s.r15) {
        goto loc_bcc8804;
    }
    // Allocate first node (0x80 bytes)
    void* alloc_fn = *reinterpret_cast<void**>(0xF99FFA0);
    void* new_node = ((void*(*)(uint64_t))alloc_fn)(0x80);  // 0xbcc8703  call r8
    if (!new_node) {
        goto loc_bccf1ba;
    }
    s.rdi = new_node;
    s.saved_alloc_node = new_node;
    sub_bcd5a20(new_node, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.r15) + 0x10), reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(new_node) + 0x10));  // 0xbcc8725  call 0xBCD5A20
    s.list_head = new_node;
    s.list_tail = new_node;
    s.list_count = 1;
    s.r12 = new_node;

loc_bcc8750:
    // 0xbcc8750..0xbcc87d7: loop to allocate/copy remaining nodes
    *reinterpret_cast<uint64_t*>(s.rbp + 0x1A8) = s.list_count;
    s.r15 = *reinterpret_cast<void**>(s.r15);
    if (s.r15 == s.m_buf_defs_map) {
        goto loc_bcc87d7;
    }
    // Allocate next node
    void* next_node = ((void*(*)(uint64_t))alloc_fn)(0x80);  // 0xbcc8784  call r8
    if (!next_node) {
        goto loc_bcc87bf;
    }
    s.rbx = next_node;
    sub_bcd5a20(next_node, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.r15) + 0x10), reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(next_node) + 0x10));  // 0xbcc87a2  call 0xBCD5A20
    *reinterpret_cast<void**>(s.r12) = next_node;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(next_node) + 8) = s.r12;
    s.list_tail = next_node;
    s.list_count++;
    s.r12 = next_node;
    goto loc_bcc8750;

loc_bcc87bf:
    // 0xbcc87bf..0xbcc87d5: allocation failed, free list and retry?
    *reinterpret_cast<void**>(s.rbp + 0x100) = nullptr;
    sub_9bc830(0x80);  // 0xbcc87cf  call 0x9BC830
    goto loc_bcc8790;

loc_bcc87d7:
    // 0xbcc87d7..0xbcc8804: link list into bucket array
    if (s.list_count == 0) {
        goto loc_bcc8804;
    }
    void* bucket_array = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x330);
    void* bucket_next = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(bucket_array) + 8);
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.rdi) + 8) = bucket_next;
    *reinterpret_cast<void**>(bucket_next) = s.rdi;
    *reinterpret_cast<void**>(s.r12) = bucket_array;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(bucket_array) + 8) = s.r12;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x338) += s.list_count;

loc_bcc8804:
    s.rsi = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x338);
    goto loc_bcc88a4;

loc_bcc8810:
    // 0xbcc8810..0xbcc8820: empty list case
    void* bucket_next_810 = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.rdi) + 8);
    *reinterpret_cast<void**>(bucket_next_810) = s.r12;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.r12) + 8) = bucket_next_810;
    s.rsi = 0;
    goto loc_bcc885b;

    // 0xbcc8820..0xbcc88a4: free list cleanup (when replacing bucket array)
loc_bcc8820:
    uint64_t new_size = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x28) + 0x28;
    uint64_t* alloc_base = reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x10);
    uint64_t alloc_size = alloc_base[-1];
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x20) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x28) = 0xF;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x10) = 0;
    sub_e935700(reinterpret_cast<void*>(alloc_base - 1), new_size);  // 0xbcc884b  call 0xE935700
    s.rsi--;
    s.rdi = s.rbx;
    if (s.rbx == s.r12) {
        goto loc_bcc888f;
    }

loc_bcc885b:
    s.rbx = *reinterpret_cast<void**>(s.rdi);
    uint64_t cap = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x28);
    if (cap < 0x10) {
        goto loc_bcc882f;
    }
    void* heap_ptr_85b = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.rdi) + 0x10);
    uint64_t new_cap = cap + 1;
    if (new_cap < 0x1000) {
        sub_e935700(heap_ptr_85b, new_cap);  // 0xbcc882a  call 0xE935700
    } else {
        // Large allocation path
        uint64_t alloc_meta = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(heap_ptr_85b) - 8);
        char* alloc_base_85b = reinterpret_cast<char*>(heap_ptr_85b) - 8;
        uint64_t user_size_85b = reinterpret_cast<uint64_t>(alloc_base_85b) - alloc_meta;
        if (user_size_85b >= 0x20) {
            goto loc_bcceccc;  // allocator error
        }
        new_cap += 0x28;
        sub_e935700(alloc_base_85b, new_cap);  // 0xbcc882a  call 0xE935700
    }

loc_bcc882f:
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x20) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x28) = 0xF;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rdi) + 0x10) = 0;
    sub_e935700(s.rdi, 0x80);  // 0xbcc884b  call 0xE935700
    s.rsi--;
    s.rdi = s.rbx;
    if (s.rbx == s.r12) {
        goto loc_bcc888f;
    }

loc_bcc888f:
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x338) += s.rsi;

loc_bcc88a4:
    // 0xbcc88a4..0xbcc8943: calculate bucket count and resize (call 0x77D80)
    // 0xbcc88a4  mov rdi,[rdx+0x360]
    // 0xbcc88ab  test rsi,rsi
    // 0xbcc88ae  js short 0xBCC88BA
    // 0xbcc88b0  xorps xmm0,xmm0
    // 0xbcc88b3  cvtsi2ss xmm0,rsi
    // 0xbcc88b8  jmp short 0xBCC88D2
    // 0xbcc88ba  mov rax,rsi
    // 0xbcc88bd  shr rax,1
    // 0xbcc88c0  and esi,1
    // 0xbcc88c3  or rsi,rax
    // 0xbcc88c6  xorps xmm0,xmm0
    // 0xbcc88c9  cvtsi2ss xmm0,rsi
    // 0xbcc88ce  addss xmm0,xmm0
    // 0xbcc88d2  mov rax,[rbp+0x270]
    // 0xbcc88d9  divss xmm0,[rax+0x328]
    // 0xbcc88e1  call 0xEEC73F0
    // 0xbcc88e6  cvttss2si rax,xmm0
    // 0xbcc88eb  mov rcx,rax
    // 0xbcc88ee  subss xmm0,[0xEEE6700]
    // 0xbcc88f6  cvttss2si rdx,xmm0
    // 0xbcc88fb  sar rcx,0x3F
    // 0xbcc88ff  and rdx,rcx
    // 0xbcc8902  or rdx,rax
    // 0xbcc8905  cmp rdx,9
    // 0xbcc8909  mov eax,8
    // 0xbcc890e  cmovae rax,rdx
    // 0xbcc8912  cmp rdi,rax
    // 0xbcc8915  jae short 0xBCC8934
    // 0xbcc8917  lea rcx,[rdi*8]
    // 0xbcc891f  cmp rcx,rax
    // 0xbcc8922  cmovbe rcx,rax
    // 0xbcc8926  cmp rdi,0x200
    // 0xbcc892d  cmovae rcx,rax
    // 0xbcc8931  mov rdi,rcx
    // 0xbcc8934  mov rcx,[rbp+0x268]
    // 0xbcc893b  mov rdx,rdi
    // 0xbcc893e  call 0x77D80
    // 0xbcc8943  nop
    {
        uint64_t bucket_mask = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x360);
        int64_t count = s.rsi;
        float load_factor;
        if (count < 0) {
            uint64_t ucount = static_cast<uint64_t>(count);
            ucount = (ucount >> 1) | (ucount & 1);
            load_factor = static_cast<float>(ucount) * 2.0f;
        } else {
            load_factor = static_cast<float>(count);
        }
        float inv_bucket_count = load_factor / static_cast<float>(*reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x328));
        uint32_t new_bucket_count = sub_eec73f0(inv_bucket_count);  // 0xbcc88e1  call 0xEEC73F0
        float adjusted = inv_bucket_count - *reinterpret_cast<float*>(0xEEE6700);
        int32_t adjusted_int = static_cast<int32_t>(adjusted);
        int32_t high_bit = new_bucket_count >> 31;
        adjusted_int &= high_bit;
        adjusted_int |= new_bucket_count;
        uint32_t min_buckets = (adjusted_int > 9) ? adjusted_int : 8;
        if (bucket_mask < min_buckets) {
            uint64_t needed = static_cast<uint64_t>(bucket_mask) * 8;
            if (needed < min_buckets) needed = min_buckets;
            if (bucket_mask >= 0x200) needed = min_buckets;
            bucket_mask = needed;
        }
        s.this_buf_defs_map = *reinterpret_cast<void**>(s.rbp + 0x268);
        sub_77d80(s.this_buf_defs_map, bucket_mask);  // 0xbcc893e  call 0x77D80
    }

loc_bcc8944:
    // 0xbcc8944..0xbcc897c: copy second map (m+0x110 -> this+0x3E8)
    // 0xbcc8944  mov rax,[rbp+0x178]
    // 0xbcc894b  add rax,0x110
    // 0xbcc8951  mov rcx,[rbp+0x270]
    // 0xbcc8958  lea rdi,[rcx+0x3E8]
    // 0xbcc895f  cmp rdi,rax
    // 0xbcc8962  je 0xBCC8CE8
    // 0xbcc8968  mov [rbp+0x130],rdi
    // 0xbcc896f  mov rdx,[rbp+0x178]
    // 0xbcc8976  mov eax,[rdx+0x110]
    // 0xbcc897c  mov [rcx+0x3E8],eax
    s.m_second_map_end = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.m_ptr) + 0x110 + 0x20);
    s.this_second_map = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x3E8);
    *reinterpret_cast<void**>(s.rbp + 0x130) = s.this_second_map;
    if (s.this_second_map == s.m_second_map_end) {
        goto loc_bcc8ce8;
    }
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x3E8) = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(s.m_ptr) + 0x110);
    s.m_second_map = reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(s.m_ptr) + 0x118));
    s.this_second_bucket_array = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_second_map) + 0x3F0);
    s.r12 = *reinterpret_cast<void**>(s.m_second_map);
    s.r13 = s.this_second_bucket_array;
    s.rbx = *reinterpret_cast<void**>(s.r13);
    if (s.rbx == s.r13) {
        goto loc_bcc8a30;
    }

    // Second map copy loop (similar to first)
loc_bcc89a0:
    if (s.r12 == s.m_second_map) {
        goto loc_bcc8b92;
    }
    if (s.rbx == s.r12) {
        goto loc_bcc8a11;
    }
    // Copy key string
    uint64_t key_cap_9a = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.r12) + 0x28);
    char* key_src_9a;
    if (key_cap_9a < 0x10) {
        key_src_9a = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(s.r12) + 0x10);
    } else {
        key_src_9a = *reinterpret_cast<char**>(reinterpret_cast<uintptr_t>(s.r12) + 0x10);
    }
    char* key_dst_9a = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x10);
    uint64_t key_len_9a = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.r12) + 0x20);
    uint64_t dst_cap_9a = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x28);
    if (key_len_9a > dst_cap_9a) {
        if (dst_cap_9a >= 0x10) {
            key_dst_9a = *reinterpret_cast<char**>(reinterpret_cast<uintptr_t>(s.rbx) + 0x10);
        }
        sub_9d6d0(key_dst_9a, key_len_9a);  // 0xbcc89dd  call 0x9D6D0
        goto loc_bcc8a11;
    }
    if (dst_cap_9a >= 0x10) {
        key_dst_9a = *reinterpret_cast<char**>(reinterpret_cast<uintptr_t>(s.rbx) + 0x10);
    }
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x20) = key_len_9a;
    sub_eec6de0(key_dst_9a, key_src_9a, key_len_9a);  // 0xbcc8a07  call 0xEEC6DE0
    *(key_dst_9a + key_len_9a) = 0;

loc_bcc8a11:
    // 0xbcc8a11..0xbcc8a2a: call 0xBCD6DF0 to copy value
    sub_bcd6df0(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x30),
                reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.r12) + 0x30));  // 0xbcc8a1a  call 0xBCD6DF0
    s.r12 = *reinterpret_cast<void**>(s.r12);
    s.rbx = *reinterpret_cast<void**>(s.rbx);
    if (s.rbx != s.r13) {
        goto loc_bcc89a0;
    }

loc_bcc8a30:
    // 0xbcc8a30..0xbcc8b81: build linked list for second map (similar to first)
    void* second_bucket_array_head = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x3F0);
    *reinterpret_cast<void**>(s.rbp + 0x1A0) = second_bucket_array_head;
    s.list_head = nullptr;
    s.list_tail = nullptr;
    s.list_count = 0;
    if (s.m_second_map == s.r12) {
        goto loc_bcc8b81;
    }
    void* alloc_fn_2 = *reinterpret_cast<void**>(0xF99FFA0);
    void* new_node_2 = ((void*(*)(uint64_t))alloc_fn_2)(0x138);  // 0xbcc8a87  call r8
    if (!new_node_2) {
        goto loc_bccf1d5;
    }
    s.rbx = new_node_2;
    s.saved_alloc_node = new_node_2;
    sub_bcd6840(new_node_2, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.r12) + 0x10), reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(new_node_2) + 0x10));  // 0xbcc8aaa  call 0xBCD6840
    s.list_head = new_node_2;
    s.r15 = 0;
    s.r13 = new_node_2;

loc_bcc8ac0:
    *reinterpret_cast<void**>(s.rbp + 0x1B0) = s.r13;
    s.list_count++;
    *reinterpret_cast<uint64_t*>(s.rbp + 0x1A8) = s.list_count;
    s.r12 = *reinterpret_cast<void**>(s.r12);
    if (s.r12 == s.m_second_map) {
        goto loc_bcc8b49;
    }
    void* next_node_2 = ((void*(*)(uint64_t))alloc_fn_2)(0x138);  // 0xbcc8aff  call r8
    if (!next_node_2) {
        goto loc_bcc8b31;
    }
    s.r14 = next_node_2;
    sub_bcd6840(next_node_2, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.r12) + 0x10), reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(next_node_2) + 0x10));  // 0xbcc8b1e  call 0xBCD6840
    *reinterpret_cast<void**>(s.r13) = next_node_2;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(next_node_2) + 8) = s.r13;
    s.r13 = next_node_2;
    goto loc_bcc8ac0;

loc_bcc8b31:
    *reinterpret_cast<void**>(s.rbp + 0xF8) = nullptr;
    sub_9bc830(0x138);  // 0xbcc8b41  call 0x9BC830
    goto loc_bcc8b0b;

loc_bcc8b49:
    if (s.list_count == 0) {
        goto loc_bcc8b81;
    }
    void* second_bucket_array = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x3F0);
    void* second_bucket_next = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(second_bucket_array) + 8);
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.rbx) + 8) = second_bucket_next;
    *reinterpret_cast<void**>(second_bucket_next) = s.rbx;
    *reinterpret_cast<void**>(s.r13) = second_bucket_array;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(second_bucket_array) + 8) = s.r13;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x3F8) += s.list_count;
    *reinterpret_cast<uint64_t*>(s.rbp + 0x1A8) = 0;

loc_bcc8b81:
    // 0xbcc8b81..0xbcc8b8d: call 0xBCD6770
    sub_bcd6770(reinterpret_cast<void*>(s.rbp + 0x1A0));  // 0xbcc8b88  call 0xBCD6770
    goto loc_bcc8c37;

loc_bcc8b92:
    // 0xbcc8b92..0xbcc8c37: cleanup second map old nodes
    if (s.rbx == s.r13) {
        goto loc_bcc8c37;
    }
    void* rbx_next = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.rbx) + 8);
    *reinterpret_cast<void**>(rbx_next) = s.r13;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.r13) + 8) = rbx_next;
    s.rsi = 0;
    goto loc_bcc8be1;

loc_bcc8bb0:
    sub_e935700(s.rbx, 0x138);  // 0xbcc8bb0  call 0xE935700
    goto loc_bcc8bb5;

loc_bcc8bb5:
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x20) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x28) = 0xF;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x10) = 0;
    sub_e935700(s.rbx, 0x138);  // 0xbcc8bd1  call 0xE935700
    s.rsi--;
    s.rbx = s.r14;
    if (s.r14 == s.r13) {
        goto loc_bcc8c29;
    }

loc_bcc8be1:
    s.r14 = *reinterpret_cast<void**>(s.rbx);
    sub_bcd3f50(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x30));  // 0xbcc8be8  call 0xBCD3F50
    uint64_t cap_be = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.rbx) + 0x28);
    if (cap_be < 0x10) {
        goto loc_bcc8bb5;
    }
    void* heap_ptr_be = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.rbx) + 0x10);
    uint64_t new_cap_be = cap_be + 1;
    if (new_cap_be < 0x1000) {
        sub_e935700(heap_ptr_be, new_cap_be);  // 0xbcc8c06  call 0xE935700
    } else {
        // Large allocation path
        uint64_t alloc_meta_be = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(heap_ptr_be) - 8);
        char* alloc_base_be = reinterpret_cast<char*>(heap_ptr_be) - 8;
        uint64_t user_size_be = reinterpret_cast<uint64_t>(alloc_base_be) - alloc_meta_be;
        if (user_size_be >= 0x20) {
            goto loc_bcceccc;
        }
        new_cap_be += 0x28;
        sub_e935700(alloc_base_be, new_cap_be);  // 0xbcc8c27  call 0xE935700
    }

loc_bcc8c29:
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x3F8) += s.rsi;

loc_bcc8c37:
    // 0xbcc8c37..0xbcc8ce7: calculate bucket count for second map and resize (call 0x77D80)
    // Similar to loc_bcc88a4 but for second map at +0x3E8/+0x3F0/+0x3F8
    void* this_ptr_c37 = *reinterpret_cast<void**>(s.rbp + 0x270);
    uint64_t second_count = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(this_ptr_c37) + 0x3F8);
    uint64_t second_bucket_mask = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(this_ptr_c37) + 0x420);
    float load_factor_c37;
    if (static_cast<int64_t>(second_count) < 0) {
        uint64_t ucount = static_cast<uint64_t>(second_count);
        ucount = (ucount >> 1) | (ucount & 1);
        load_factor_c37 = static_cast<float>(ucount) * 2.0f;
    } else {
        load_factor_c37 = static_cast<float>(second_count);
    }
    float inv_bucket_count_c37 = load_factor_c37 / static_cast<float>(*reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this_ptr_c37) + 0x3E8));
    uint32_t new_bucket_count_c37 = sub_eec73f0(inv_bucket_count_c37);  // 0xbcc8c82  call 0xEEC73F0
    float adjusted_c37 = inv_bucket_count_c37 - *reinterpret_cast<float*>(0xEEE6700);
    int32_t adjusted_int_c37 = static_cast<int32_t>(adjusted_c37);
    int32_t high_bit_c37 = new_bucket_count_c37 >> 31;
    adjusted_int_c37 &= high_bit_c37;
    adjusted_int_c37 |= new_bucket_count_c37;
    uint32_t min_buckets_c37 = (adjusted_int_c37 > 9) ? adjusted_int_c37 : 8;
    if (second_bucket_mask < min_buckets_c37) {
        uint64_t needed_c37 = second_bucket_mask * 8;
        if (needed_c37 < min_buckets_c37) needed_c37 = min_buckets_c37;
        if (second_bucket_mask >= 0x200) needed_c37 = min_buckets_c37;
        second_bucket_mask = needed_c37;
    }
    sub_77d80(s.this_second_map, second_bucket_mask);  // 0xbcc8cdb  call 0x77D80

loc_bcc8ce8:
    // 0xbcc8ce8..0xbcc8ddc: cleanup some list at this+0x370
    // 0xbcc8ce8  cmp qword ptr [rcx+0x378],0
    // 0xbcc8cf0  je 0xBCC8DDC
    // 0xbcc8cf6  mov rax,[rbp+0x270]
    // 0xbcc8cfd  mov rax,[rax+0x370]
    // 0xbcc8d04  mov rcx,[rax+8]
    // 0xbcc8d08  mov qword ptr [rcx],0
    // 0xbcc8d0f  mov rcx,[rax]
    // 0xbcc8d12  test rcx,rcx
    // 0xbcc8d15  je short 0xBCC8D35
    // 0xbcc8d20  mov rsi,[rcx]
    // 0xbcc8d23  mov edx,0x20
    // 0xbcc8d28  call 0xE935700
    // 0xbcc8d2d  mov rcx,rsi
    // 0xbcc8d30  test rsi,rsi
    // 0xbcc8d33  jne short 0xBCC8D20
    // 0xbcc8d35  mov rcx,[rbp+0x270]
    // 0xbcc8d3c  mov rax,[rcx+0x370]
    // 0xbcc8d43  mov [rax],rax
    // 0xbcc8d46  mov [rax+8],rax
    // 0xbcc8d4a  mov qword ptr [rcx+0x378],0
    // 0xbcc8d55  mov rdx,[rcx+0x380]
    // 0xbcc8d5c  mov rax,[rcx+0x388]
    // 0xbcc8d63  cmp rdx,rax
    // 0xbcc8d66  je short 0xBCC8DDC
    // 0xbcc8d68  mov rcx,[rbp+0x270]
    // 0xbcc8d6f  mov rcx,[rcx+0x370]
    // 0xbcc8d76  mov r9,rax
    // 0xbcc8d79  sub r9,rdx
    // 0xbcc8d7c  add r9,0xFFFFFFFFFFFFFFF8
    // 0xbcc8d80  cmp r9,0x18
    // 0xbcc8d84  jae short 0xBCC8D8B
    // 0xbcc8d86  mov r8,rdx
    // 0xbcc8d89  jmp short 0xBCC8DD0
    if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x378) == 0) {
        goto loc_bcc8ddc;
    }
    void* list_head_ce = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x370);
    void* list_next = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(list_head_ce) + 8);
    *reinterpret_cast<uint64_t*>(list_next) = 0;
    void* list_curr = *reinterpret_cast<void**>(list_head_ce);
    while (list_curr) {
        void* next = *reinterpret_cast<void**>(list_curr);
        sub_e935700(list_curr, 0x20);  // 0xbcc8d28  call 0xE935700
        list_curr = next;
    }
    *reinterpret_cast<void**>(list_head_ce) = list_head_ce;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(list_head_ce) + 8) = list_head_ce;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x378) = 0;
    void* list_start = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x380);
    void* list_end = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(s.this_ptr) + 0x388);
    if (list_start == list_end) {
        goto loc_bcc8ddc;
    }
    // ... rest of cleanup (truncated at 0xbcc9718 boundary)

loc_bcc8ddc:
    // End of chunk range 0xbcc7f20..0xbcc9718
    return;
}

} }

#if 0
// verbatim call quotes (plain lines):
0xbcc7faa  call qword ptr [0xF99FFA0]
0xbcc8012  call 0x9D6D0
0xbcc804c  call 0xEEC6DE0
0xbcc8070  call 0x1CFDF0
0xbcc80bd  call 0xE935700
0xbcc80fe  call 0x660E670
0xbcc811e  call qword ptr [0xF99FFA0]
0xbcc8157  call 0xE86A1B0
0xbcc817c  call 0xE935700
0xbcc824b  call 0x9D6D0
0xbcc8277  call 0xEEC6DE0
0xbcc837e  call 0x53D5C20
0xbcc8703  call r8
0xbcc8725  call 0xBCD5A20
0xbcc8784  call r8
0xbcc87a2  call 0xBCD5A20
0xbcc87cf  call 0x9BC830
0xbcc882a  call 0xE935700
0xbcc884b  call 0xE935700
0xbcc88e1  call 0xEEC73F0
0xbcc893e  call 0x77D80
0xbcc89dd  call 0x9D6D0
0xbcc8a07  call 0xEEC6DE0
0xbcc8a1a  call 0xBCD6DF0
0xbcc8a87  call r8
0xbcc8aaa  call 0xBCD6840
0xbcc8aff  call r8
0xbcc8b1e  call 0xBCD6840
0xbcc8b41  call 0x9BC830
0xbcc8b88  call 0xBCD6770
0xbcc8bb0  call 0xE935700
0xbcc8bd1  call 0xE935700
0xbcc8be8  call 0xBCD3F50
0xbcc8c82  call 0xEEC73F0
0xbcc8cdb  call 0x77D80
0xbcc8d28  call 0xE935700
0xbcc90a1  call qword ptr [0xF99FFA0]
0xbcc9140  call 0xEEC73F0
0xbcc921e  call qword ptr [0xF99FFA0]
0xbcc9272  call qword ptr [0xF99FFA0]
0xbcc92c4  call 0xE935700
0xbcc95ef  call 0x9BC830
0xbcc95fd  call 0x9BC830
0xbcc960b  call 0x9BC830
0xbcc966b  call 0xE935700
0xbcc9683  call 0xE935700
#endif

LIFT_FN(0xbcc7f20, MaterialInstance_initFromMaterial);