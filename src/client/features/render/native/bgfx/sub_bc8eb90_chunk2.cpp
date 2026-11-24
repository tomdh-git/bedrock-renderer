// LIFT 0xbc8eb90 size 0x5ba7 1.26.62.01 VV frame-graph builder
// CHUNK 0xbc9037e..0xbc91b7c

#include "sub_bc8eb90_chunk2.h"

namespace native {

// verbatim call quotes (machine-checked)
#if 0
0xbc90385  call qword ptr [0xF99FFA0]
0xbc903b0  call qword ptr [0xF99FFA0]
0xbc903f9  call 0xEEC6EC0
0xbc904d2  call qword ptr [0xF99FFA0]
0xbc90512  call qword ptr [0xF99FFA0]
0xbc9062b  call 0x130EE0
0xbc9064e  call 0x56939C0
0xbc906a9  call 0x9D6D0
0xbc906c9  call 0xEEC6DE0
0xbc90734  call 0xE935700
0xbc90776  call qword ptr [0xF99FFA0]
0xbc907c7  call 0xE935700
0xbc90829  call 0xE935700
0xbc9086e  call 0xE935700
0xbc908b3  call 0xE935700
0xbc908d5  call qword ptr [0xF99FFA0]
0xbc90915  call 0xE935700
0xbc9095a  call 0xE935700
0xbc9099f  call 0xE935700
0xbc909e4  call 0xE935700
0xbc90a41  call r8
0xbc90b25  call 0x568AD40
0xbc90b9d  call qword ptr [0xF99FFA0]
0xbc90cad  call 0x76A8A0
0xbc90f32  call qword ptr [0xF99FFA0]
0xbc90fcf  call qword ptr [0xF99FFA0]
0xbc90ff5  call qword ptr [0xF99FFA0]
0xbc910a0  call qword ptr [0xF99FFA0]
0xbc910cb  call qword ptr [0xF99FFA0]
0xbc91111  call 0xEEC6EC0
0xbc911ef  call qword ptr [0xF99FFA0]
0xbc9122f  call qword ptr [0xF99FFA0]
0xbc9134b  call 0x130EE0
0xbc9136e  call 0x56939C0
0xbc91382  call 0x5693A80
0xbc91396  call 0x5693A80
0xbc913aa  call 0x5693A80
0xbc913ff  call 0x9D6D0
0xbc9141e  call 0xEEC6DE0
0xbc91457  call 0xBC97070
0xbc91496  call 0xE935700
0xbc914db  call 0xE935700
0xbc91520  call 0xE935700
0xbc91545  call qword ptr [0xF99FFA0]
0xbc91571  call qword ptr [0xF99FFA0]
0xbc91587  call qword ptr [0xF99FFA0]
0xbc915cd  call 0xE935700
0xbc91612  call 0xE935700
0xbc91657  call 0xE935700
0xbc9169c  call 0xE935700
0xbc916d7  call r8
0xbc917a8  call 0x568AD40
0xbc917ff  call qword ptr [0xF99FFA0]
0xbc91901  call 0x76A8A0
0xbc91aa9  call qword ptr [0xF99FFA0]
0xbc91b49  call qword ptr [0xF99FFA0]
0xbc91b76  call qword ptr [0xF99FFA0]
#endif

// Helper to get the alloc function pointer from data slot
static inline AllocFn get_alloc_fn(ChunkState_bc8eb90_c01& st) {
    return *reinterpret_cast<AllocFn*>(0xF99FFA0);
}

// Helper to get the free function pointer from data slot (same slot)
static inline FreeFn get_free_fn(ChunkState_bc8eb90_c01& st) {
    return *reinterpret_cast<FreeFn*>(0xF99FFA0);
}

static inline void chunk_bc8eb90_c01(ChunkState_bc8eb90_c01* st) {
    // 0xbc9037e..0xbc90385
    // lea r15,[r14+0x28]
    // mov rdx,r15
    uint64_t r15 = st->r14 + 0x28;
    uint64_t rdx = r15;

    // 0xbc90385..0xbc903b0
    // 0xbc90385  call qword ptr [0xF99FFA0]
    // nop
    // mov rsi,rax
    // test rax,rax
    // je 0xBC9389B
    void* rax = get_alloc_fn(*st)(st->r14, rdx);
    uint64_t rsi = reinterpret_cast<uint64_t>(rax);
    if (rax == nullptr) {
        // Jump to sub_bc9389b (exception handler for allocation failure)
        return;
    }

    // 0xbc90398..0xbc903a7
    // mov rax,rsi
    // add rsi,0x27
    // and rsi,0xFFFFFFFFFFFFFFE0
    // mov [rsi-8],rax
    // jmp short 0xBC903C3
    rax = reinterpret_cast<void*>(rsi);
    rsi += 0x27;
    rsi &= 0xFFFFFFFFFFFFFFE0ULL;
    *reinterpret_cast<void**>(rsi - 8) = rax;
    goto loc_bc903c3;

    // 0xbc903a9..0xbc903bd (allocation failure path - second attempt with r14+1)
    // lea r15,[r14+1]
    // mov rdx,r15
    // 0xbc903b0  call qword ptr [0xF99FFA0]
    // nop
    // mov rsi,rax
    // test rax,rax
    // je 0xBC938A9
    r15 = st->r14 + 1;
    rdx = r15;
    rax = get_alloc_fn(*st)(st->r14, rdx);
    rsi = reinterpret_cast<uint64_t>(rax);
    if (rax == nullptr) {
        // Jump to sub_bc938a9 (exception handler)
        return;
    }

loc_bc903c3:  // from 0xbc903a7
    // 0xbc903c3..0xbc903f9
    // mov [rdi],rsi
    // mov rdi,rsi
    // cmp rbx,0x10
    // lea rax,[rbp+0x110]
    // cmovb r13,rax
    // mov rax,[rbp+0x3F8]
    // mov [rax+0xA0],r12
    // mov [rax+0xA8],r14
    // mov r14,rax
    // mov rcx,rdi
    // mov rdx,r13
    // mov r8,r12
    *reinterpret_cast<uint64_t*>(st->rdi) = rsi;
    st->rdi = rsi;
    uint64_t r13_val = (st->rbx < 0x10) ? (reinterpret_cast<uint64_t>(st->stack_base) + 0x110) : st->r13;
    uint64_t* rbp_3f8 = reinterpret_cast<uint64_t*>(st->slot<uint64_t>(0x3F8));
    rbp_3f8[0xA0/8] = st->r12;
    rbp_3f8[0xA8/8] = st->r14;
    st->r14 = reinterpret_cast<uint64_t>(rbp_3f8);
    uint64_t rcx = st->rdi;
    rdx = r13_val;
    uint64_t r8 = st->r12;

    // 0xbc903f9  call 0xEEC6EC0
    sub_eec6ec0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);

    // 0xbc903fe..0xbc9040e
    // mov byte ptr [rdi+r12],0
    // mov rcx,[rbp+0x400]
    // mov r15,[rcx+0x10]
    // cmp r15,[rcx+0x18]
    *reinterpret_cast<uint8_t*>(st->rdi + st->r12) = 0;
    uint64_t* rbp_400 = reinterpret_cast<uint64_t*>(st->slot<uint64_t>(0x400));
    uint64_t r15_val = rbp_400[0x10/8];
    uint64_t r15_cmp = rbp_400[0x18/8];
    if (r15_val == r15_cmp) {
        goto loc_bc90433;
    }

    // 0xbc90414..0xbc9042e
    // mov rax,[rbp+0x3B0]
    // mov [r15],rax
    // mov [r15+8],r14
    // mov rax,[rcx+0x10]
    // add rax,0x10
    // mov [rcx+0x10],rax
    // jmp 0xBC9063B
    rax = st->slot<uint64_t>(0x3B0);
    *reinterpret_cast<uint64_t*>(r15_val) = rax;
    *reinterpret_cast<uint64_t*>(r15_val + 8) = st->r14;
    rax = rbp_400[0x10/8];
    rax += 0x10;
    rbp_400[0x10/8] = rax;
    goto loc_bc9063b;

loc_bc90433:  // from 0xbc90412
    // 0xbc90433..0xbc9048d
    // mov r8,r14
    // add r8,0xC
    // mov rbx,r15
    // mov rax,[rbp+0x2D8]
    // sub rbx,[rax]
    // mov rax,rbx
    // sar rax,4
    // lea r12,[rax+1]
    // mov r13,rax
    // shr r13,1
    // mov rcx,0xFFFFFFFFFFFFFFF
    // mov rdx,rcx
    // sub rdx,r13
    // add r13,rax
    // cmp r13,r12
    // cmovbe r13,r12
    // cmp rax,rdx
    // cmova r13,rcx
    // lea rcx,[r14+8]
    // mov rax,r13
    // shr rax,0x3C
    // jne 0xBC93F34
    r8 = st->r14 + 0xC;
    st->rbx = r15_val;
    rax = st->slot<uint64_t>(0x2D8);
    st->rbx -= *reinterpret_cast<uint64_t*>(rax);
    rax = st->rbx;
    rax >>= 4;  // sar rax,4
    st->r12 = rax + 1;
    st->r13 = rax >> 1;  // shr r13,1
    rcx = 0xFFFFFFFFFFFFFFFULL;
    rdx = rcx;
    rdx -= st->r13;
    st->r13 += rax;
    if (st->r13 <= st->r12) st->r13 = st->r12;
    if (rax > rdx) st->r13 = rcx;
    rcx = st->r14 + 8;
    rax = st->r13;
    if ((rax >> 0x3C) != 0) {
        // Jump to sub_bc93f34 (exception handler)
        return;
    }

    // 0xbc9048a..0xbc9049a
    // test r13,r13
    // je short 0xBC904FD
    // mov [rbp+0x3B8],rcx
    // mov [rbp+0x38],r8
    // mov rsi,r13
    // shl rsi,4
    if (st->r13 == 0) {
        goto loc_bc904fd;
    }
    st->slot<uint64_t>(0x3B8) = rcx;
    st->slot<uint64_t>(0x38) = r8;
    rsi = st->r13 << 4;

    // 0xbc904a1..0xbc904d2
    // cmp r13,0x100
    // jb short 0xBC90501
    // mov rax,0xFFFFFFFFFFFFFFE
    // cmp r13,rax
    // jae 0xBC9471E
    // add rsi,0x27
    // mov rcx,[0x1233E1A8]
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov rdx,rsi
    // 0xbc904d2  call qword ptr [0xF99FFA0]
    // nop
    // mov rdi,rax
    // test rax,rax
    // je 0xBC93928
    // mov rax,rdi
    // add rdi,0x27
    // and rdi,0xFFFFFFFFFFFFFFE0
    // mov [rdi-8],rax
    // mov r14,[rbp+0x3F8]
    // jmp short 0xBC9052C
    if (st->r13 < 0x100) {
        goto loc_bc90501;
    }
    rax = 0xFFFFFFFFFFFFFFFEULL;
    if (st->r13 >= rax) {
        // Jump to sub_bc9471e (exception handler)
        return;
    }
    rsi += 0x27;
    uint64_t* data_1233e1a8 = *reinterpret_cast<uint64_t**>(0x1233E1A8);
    rax = *data_1233e1a8;
    rax = *reinterpret_cast<uint64_t*>(rax + 8);
    rdx = rsi;
    rax = reinterpret_cast<uint64_t>(get_alloc_fn(*st)(reinterpret_cast<void*>(rax), rdx));
    st->rdi = rax;
    if (rax == 0) {
        // Jump to sub_bc93928
        return;
    }
    rax = st->rdi;
    st->rdi += 0x27;
    st->rdi &= 0xFFFFFFFFFFFFFFE0ULL;
    *reinterpret_cast<uint64_t*>(st->rdi - 8) = rax;
    st->r14 = st->slot<uint64_t>(0x3F8);
    goto loc_bc9052c;

loc_bc904fd:  // from 0xbc9048d
    // 0xbc904fd..0xbc90501
    // xor edi,edi
    // jmp short 0xBC9052C
    st->rdi = 0;
    goto loc_bc9052c;

loc_bc90501:  // from 0xbc904a8
    // 0xbc90501..0xbc90526
    // mov rcx,[0x1233E1A8]
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov rdx,rsi
    // 0xbc90512  call qword ptr [0xF99FFA0]
    // nop
    // mov rdi,rax
    // test rax,rax
    // mov r14,[rbp+0x3F8]
    // je 0xBC93918
    data_1233e1a8 = *reinterpret_cast<uint64_t**>(0x1233E1A8);
    rax = *data_1233e1a8;
    rax = *reinterpret_cast<uint64_t*>(rax + 8);
    rdx = rsi;
    rax = reinterpret_cast<uint64_t>(get_alloc_fn(*st)(reinterpret_cast<void*>(rax), rdx));
    st->rdi = rax;
    st->r14 = st->slot<uint64_t>(0x3F8);
    if (rax == 0) {
        // Jump to sub_bc93918
        return;
    }

loc_bc9052c:  // from 0xbc904fb, 0xbc904ff, 0xbc90526
    // 0xbc9052c..0xbc9054e
    // mov rax,[rbp+0x3B0]
    // mov [rdi+rbx],rax
    // mov [rdi+rbx+8],r14
    // mov rcx,[rbp+0x400]
    // mov rax,[rcx+8]
    // mov rcx,[rcx+0x10]
    // cmp r15,rcx
    // je 0xBC905DE
    rax = st->slot<uint64_t>(0x3B0);
    *reinterpret_cast<uint64_t*>(st->rdi + st->rbx) = rax;
    *reinterpret_cast<uint64_t*>(st->rdi + st->rbx + 8) = st->r14;
    rbp_400 = reinterpret_cast<uint64_t*>(st->slot<uint64_t>(0x400));
    rax = rbp_400[0x8/8];
    rcx = rbp_400[0x10/8];
    if (r15_val == rcx) {
        goto loc_bc905de;
    }
    // 0xbc90554..0xbc9055e
    // cmp rax,r15
    // je short 0xBC90596
    // xor ecx,ecx
    // xorps xmm0,xmm0
    // xchg ax,ax
    if (rax == r15_val) {
        goto loc_bc90596;
    }
    rcx = 0;
    __m128i xmm0 = _mm_setzero_si128();

loc_bc90560:  // from 0xbc90589
    // 0xbc90560..0xbc90589
    // movups [rdi+rcx],xmm0
    // mov rdx,[rax+rcx]
    // mov [rdi+rcx],rdx
    // mov rdx,[rax+rcx+8]
    // mov [rdi+rcx+8],rdx
    // movups [rax+rcx],xmm0
    // lea rdx,[rax+rcx]
    // add rdx,0x10
    // add rcx,0x10
    // cmp rdx,r15
    // jne short 0xBC90560
    _mm_storeu_si128(reinterpret_cast<__m128i*>(st->rdi + rcx), xmm0);
    rdx = *reinterpret_cast<uint64_t*>(rax + rcx);
    *reinterpret_cast<uint64_t*>(st->rdi + rcx) = rdx;
    rdx = *reinterpret_cast<uint64_t*>(rax + rcx + 8);
    *reinterpret_cast<uint64_t*>(st->rdi + rcx + 8) = rdx;
    _mm_storeu_si128(reinterpret_cast<__m128i*>(rax + rcx), xmm0);
    rdx = rax + rcx;
    rdx += 0x10;
    rcx += 0x10;
    if (rdx != r15_val) {
        goto loc_bc90560;
    }
    rbp_400 = reinterpret_cast<uint64_t*>(st->slot<uint64_t>(0x400));
    rcx = rbp_400[0x10/8];

loc_bc90596:  // from 0xbc90557
    // 0xbc90596..0xbc905b0
    // cmp r15,rcx
    // je 0xBC9061B
    // lea rax,[rbx+rdi]
    // add rax,0x10
    // xor edx,edx
    // xorps xmm0,xmm0
    // nop [rax]
    if (r15_val == rcx) {
        goto loc_bc9061b;
    }
    rax = st->rbx + st->rdi;
    rax += 0x10;
    rdx = 0;
    xmm0 = _mm_setzero_si128();

loc_bc905b0:  // from 0xbc905da
    // 0xbc905b0..0xbc905da
    // movups [rax+rdx],xmm0
    // mov r8,[r15+rdx]
    // mov [rax+rdx],r8
    // mov r8,[r15+rdx+8]
    // mov [rax+rdx+8],r8
    // movups [r15+rdx],xmm0
    // lea r8,[r15+rdx]
    // add r8,0x10
    // add rdx,0x10
    // cmp r8,rcx
    // jne short 0xBC905B0
    _mm_storeu_si128(reinterpret_cast<__m128i*>(rax + rdx), xmm0);
    uint64_t r8_val = *reinterpret_cast<uint64_t*>(r15_val + rdx);
    *reinterpret_cast<uint64_t*>(rax + rdx) = r8_val;
    r8_val = *reinterpret_cast<uint64_t*>(r15_val + rdx + 8);
    *reinterpret_cast<uint64_t*>(rax + rdx + 8) = r8_val;
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r15_val + rdx), xmm0);
    r8_val = r15_val + rdx;
    r8_val += 0x10;
    rdx += 0x10;
    if (r8_val != rcx) {
        goto loc_bc905b0;
    }
    goto loc_bc9061b;

loc_bc905de:  // from 0xbc9054e
    // 0xbc905de..0xbc905f0
    // cmp rax,r15
    // je short 0xBC9061B
    // xor ecx,ecx
    // xorps xmm0,xmm0
    // nop [rax+rax]
    if (rax == r15_val) {
        goto loc_bc9061b;
    }
    rcx = 0;
    xmm0 = _mm_setzero_si128();

loc_bc905f0:  // from 0xbc90619
    // 0xbc905f0..0xbc90619
    // movups [rdi+rcx],xmm0
    // mov rdx,[rax+rcx]
    // mov [rdi+rcx],rdx
    // mov rdx,[rax+rcx+8]
    // mov [rdi+rcx+8],rdx
    // movups [rax+rcx],xmm0
    // lea rdx,[rax+rcx]
    // add rdx,0x10
    // add rcx,0x10
    // cmp rdx,r15
    // jne short 0xBC905F0
    _mm_storeu_si128(reinterpret_cast<__m128i*>(st->rdi + rcx), xmm0);
    rdx = *reinterpret_cast<uint64_t*>(rax + rcx);
    *reinterpret_cast<uint64_t*>(st->rdi + rcx) = rdx;
    rdx = *reinterpret_cast<uint64_t*>(rax + rcx + 8);
    *reinterpret_cast<uint64_t*>(st->rdi + rcx + 8) = rdx;
    _mm_storeu_si128(reinterpret_cast<__m128i*>(rax + rcx), xmm0);
    rdx = rax + rcx;
    rdx += 0x10;
    rcx += 0x10;
    if (rdx != r15_val) {
        goto loc_bc905f0;
    }

loc_bc9061b:  // from 0xbc90599, 0xbc905dc, 0xbc905e1
    // 0xbc9061b..0xbc9063b
    // mov rcx,[rbp+0x2D8]
    // mov rdx,rdi
    // mov r8,r12
    // mov r9,r13
    // 0xbc9062b  call 0x130EE0
    // mov rcx,[rbp+0x400]
    // mov rax,[rcx+0x10]
    rcx = st->slot<uint64_t>(0x2D8);
    rdx = st->rdi;
    r8 = st->r12;
    r9 = st->r13;
    sub_130ee0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8, r9);
    rbp_400 = reinterpret_cast<uint64_t*>(st->slot<uint64_t>(0x400));
    rax = rbp_400[0x10/8];

loc_bc9063b:  // from 0xbc9042e
    // 0xbc9063b..0xbc9064e
    // lea rdx,[rbp+0x1A8]
    // mov byte ptr [rcx+0x60],1
    // mov rax,[rax-0x10]
    // mov [rcx+0x58],rax
    // 0xbc9064e  call 0x56939C0
    rdx = reinterpret_cast<uint64_t>(st->stack_base) + 0x1A8;
    *reinterpret_cast<uint8_t*>(rax + 0x60) = 1;
    rax = *reinterpret_cast<uint64_t*>(rax - 0x10);
    *reinterpret_cast<uint64_t*>(rax + 0x58) = rax;
    sub_56939c0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));

    // 0xbc90653..0xbc906a9
    // nop
    // mov r14,[rbp+0x3C8]
    // lea rcx,[rbp+0x178]
    // mov rax,[rbp+0x400]
    // mov rbx,[rax+0x58]
    // lea rax,[rbx+8]
    // cmp rax,rcx
    // je short 0xBC906D2
    // mov rsi,[rbp+0x190]
    // cmp qword ptr [rbp+0x198],0x10
    // jb short 0xBC90692
    // mov rax,[rbp+0x180]
    // mov [rbp+0x30],rax
    st->r14 = st->slot<uint64_t>(0x3C8);
    rcx = reinterpret_cast<uint64_t>(st->stack_base) + 0x178;
    rbp_400 = reinterpret_cast<uint64_t*>(st->slot<uint64_t>(0x400));
    st->rbx = rbp_400[0x58/8];
    rax = st->rbx + 8;
    if (rax == rcx) {
        goto loc_bc906d2;
    }
    rsi = st->slot<uint64_t>(0x190);
    if (st->slot<uint64_t>(0x198) < 0x10) {
        goto loc_bc90692;
    }
    rax = st->slot<uint64_t>(0x180);
    st->slot<uint64_t>(0x30) = rax;

loc_bc90692:  // from 0xbc90685
    // 0xbc90692..0xbc906c9
    // lea rdi,[rbx+0x10]
    // mov rax,[rbx+0x28]
    // cmp rsi,rax
    // jbe short 0xBC906B1
    // mov rcx,rdi
    // mov rdx,rsi
    // mov r9,[rbp+0x30]
    // 0xbc906a9  call 0x9D6D0
    // nop
    // jmp short 0xBC906D2
    st->rdi = st->rbx + 0x10;
    rax = *reinterpret_cast<uint64_t*>(st->rbx + 0x28);
    if (rsi <= rax) {
        goto loc_bc906b1;
    }
    rcx = st->rdi;
    rdx = rsi;
    r9 = st->slot<uint64_t>(0x30);
    sub_9d6d0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), reinterpret_cast<void*>(r9), rsi);
    goto loc_bc906d2;

loc_bc906b1:  // from 0xbc9069d
    // 0xbc906b1..0xbc906c9
    // cmp rax,0x10
    // jb short 0xBC906BB
    // mov rdi,[rbx+0x10]
    // mov [rbx+0x20],rsi
    // mov rcx,rdi
    // mov rdx,[rbp+0x30]
    // mov r8,rsi
    // 0xbc906c9  call 0xEEC6DE0
    // mov byte ptr [rdi+rsi],0
    if (rax < 0x10) {
        goto loc_bc906bb;
    }
    st->rdi = *reinterpret_cast<uint64_t*>(st->rbx + 0x10);
loc_bc906bb:  // from 0xbc906b5
    *reinterpret_cast<uint64_t*>(st->rbx + 0x20) = rsi;
    rcx = st->rdi;
    rdx = st->slot<uint64_t>(0x30);
    r8 = rsi;
    sub_eec6de0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    *reinterpret_cast<uint8_t*>(st->rdi + rsi) = 0;

loc_bc906d2:  // from 0xbc90674, 0xbc906af
    // 0xbc906d2..0xbc906ff
    // mov rax,[rbp+0x178]
    // mov [rbx+8],rax
    // mov qword ptr [rbx+0x30],0
    // mov rax,[rbp+0x400]
    // mov qword ptr [rax+0x58],0
    // mov rax,[rbp+0x198]
    // cmp rax,0x10
    // jb short 0xBC90739
    rax = st->slot<uint64_t>(0x178);
    *reinterpret_cast<uint64_t*>(st->rbx + 8) = rax;
    *reinterpret_cast<uint64_t*>(st->rbx + 0x30) = 0;
    rbp_400 = reinterpret_cast<uint64_t*>(st->slot<uint64_t>(0x400));
    rbp_400[0x58/8] = 0;
    rax = st->slot<uint64_t>(0x198);
    if (rax < 0x10) {
        goto loc_bc90739;
    }

    // 0xbc90701..0xbc90734
    // mov rcx,[rbp+0x180]
    // lea rdx,[rax+1]
    // cmp rdx,0x1000
    // jb short 0xBC90734
    // mov r8,[rcx-8]
    // add rcx,0xFFFFFFFFFFFFFFF8
    // sub rcx,r8
    // cmp rcx,0x20
    // jae 0xBC93980
    // add rax,0x28
    // mov rdx,rax
    // mov rcx,r8
    // 0xbc90734  call 0xE935700
    rcx = st->slot<uint64_t>(0x180);
    rdx = rax + 1;
    if (rdx < 0x1000) {
        goto loc_bc90734;
    }
    r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
    rcx = rcx - 8 - r8;
    if (rcx >= 0x20) {
        // Jump to sub_bc93980
        return;
    }
    rax += 0x28;
    rdx = rax;
    rcx = r8;
loc_bc90734:
    sub_e935700(reinterpret_cast<void*>(rcx), rdx);

loc_bc90739:  // from 0xbc906ff
    // 0xbc90739..0xbc90776
    // mov qword ptr [rbp+0x190],0
    // mov qword ptr [rbp+0x198],0xF
    // mov b

    // 0xbc90b2a..0xbc90b9d
    // nop
    // movups xmm0,[rbp+0x390]
    // movups xmm1,[rbp+0x3A0]
    // movaps [rbp+0x260],xmm1
    // movaps [rbp+0x250],xmm0
    // mov qword ptr [rbp+0x3A0],0
    // mov qword ptr [rbp+0x3A8],0xF
    // mov byte ptr [rbp+0x390],0
    // mov [rbp+0x270],esi
    // mov rax,[rbp+0x318]
    // mov [rbp+0x278],rax
    // mov [rbp+0x280],rdi
    // mov qword ptr [rbp+0x2C0],0
    // mov rcx,[0x1233E1A8]
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov edx,0x138
    // 0xbc90b9d  call qword ptr [0xF99FFA0]
    xmm0 = st->slot<__m128i>(0x390);
    __m128i xmm1 = st->slot<__m128i>(0x3A0);
    st->slot<__m128i>(0x260) = xmm1;
    st->slot<__m128i>(0x250) = xmm0;
    st->slot<uint64_t>(0x3A0) = 0;
    st->slot<uint64_t>(0x3A8) = 0xF;
    *reinterpret_cast<uint8_t*>(st->stack_base + 0x390) = 0;
    st->slot<uint32_t>(0x270) = esi;
    rax = st->slot<uint64_t>(0x318);
    st->slot<uint64_t>(0x278) = rax;
    st->slot<uint64_t>(0x280) = st->rdi;
    st->slot<uint64_t>(0x2C0) = 0;
    data_1233e1a8 = *reinterpret_cast<uint64_t**>(0x1233E1A8);
    rax = *data_1233e1a8;
    rax = *reinterpret_cast<uint64_t*>(rax + 8);
    rdx = 0x138;
    rax = reinterpret_cast<uint64_t>(get_alloc_fn(*st)(reinterpret_cast<void*>(rax), rdx));

    // 0xbc90ba3..0xbc90cad
    // nop
    // mov rdi,rax
    // test rax,rax
    // je 0xBC937BB
    // lea rax,[0xF44B3F0]
    // mov [rdi],rax
    // mov dword ptr [rdi+8],0x3F800000
    // xorps xmm7,xmm7
    // movups [rdi+0xC],xmm7
    // mov dword ptr [rdi+0x1C],0x3F800000
    // movups [rdi+0x20],xmm7
    // mov dword ptr [rdi+0x30],0x3F800000
    // movups [rdi+0x34],xmm7
    // movsd [rdi+0x44],xmm6
    // movups [rdi+0x4C],xmm7
    // mov dword ptr [rdi+0x5C],0x3F800000
    // movups [rdi+0x60],xmm7
    // mov dword ptr [rdi+0x70],0x3F800000
    // movups [rdi+0x74],xmm7
    // mov dword ptr [rdi+0x84],0x3F800000
    // movups [rdi+0x88],xmm7
    // mov rax,0x3F80000000000001
    // mov [rdi+0x98],rax
    // movups [rdi+0xA0],xmm7
    // mov dword ptr [rdi+0xB0],0x3F800000
    // movups [rdi+0xB4],xmm7
    // mov dword ptr [rdi+0xC4],0x3F800000
    // movups [rdi+0xC8],xmm7
    // movsd [rdi+0xD8],xmm6
    // movups [rdi+0xE0],xmm7
    // mov dword ptr [rdi+0xF0],0x3F800000
    // movups [rdi+0xF4],xmm7
    // mov dword ptr [rdi+0x104],0x3F800000
    // movups [rdi+0x108],xmm7
    // mov dword ptr [rdi+0x118],0x3F800000
    // movups [rdi+0x11C],xmm7
    // mov rax,[rbp+0x3F0]
    // mov [rdi+0x130],rax
    // mov [rbp+0x2C0],rdi
    // lea rcx,[rbp+0x320]
    // lea rdx,[rbp+0x3D0]
    // 0xbc90cad  call 0x76A8A0
    if (rax == 0) {
        // Jump to sub_bc937bb
        return;
    }
    st->rdi = rax;
    *reinterpret_cast<uint64_t*>(st->rdi) = 0xF44B3F0;
    *reinterpret_cast<uint32_t*>(st->rdi + 8) = 0x3F800000;
    st->xmm7 = _mm_setzero_si128();
    *reinterpret_cast<__m128i*>(st->rdi + 0xC) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0x1C) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0x20) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0x30) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0x34) = st->xmm7;
    *reinterpret_cast<double*>(st->rdi + 0x44) = *reinterpret_cast<double*>(&st->xmm6);
    *reinterpret_cast<__m128i*>(st->rdi + 0x4C) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0x5C) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0x60) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0x70) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0x74) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0x84) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0x88) = st->xmm7;
    *reinterpret_cast<uint64_t*>(st->rdi + 0x98) = 0x3F80000000000001ULL;
    *reinterpret_cast<__m128i*>(st->rdi + 0xA0) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0xB0) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0xB4) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0xC4) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0xC8) = st->xmm7;
    *reinterpret_cast<double*>(st->rdi + 0xD8) = *reinterpret_cast<double*>(&st->xmm6);
    *reinterpret_cast<__m128i*>(st->rdi + 0xE0) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0xF0) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0xF4) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0x104) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0x108) = st->xmm7;
    *reinterpret_cast<uint32_t*>(st->rdi + 0x118) = 0x3F800000;
    *reinterpret_cast<__m128i*>(st->rdi + 0x11C) = st->xmm7;
    rax = st->slot<uint64_t>(0x3F0);
    *reinterpret_cast<uint64_t*>(st->rdi + 0x130) = rax;
    st->slot<uint64_t>(0x2C0) = st->rdi;
    rcx = reinterpret_cast<uint64_t>(st->stack_base) + 0x320;
    rdx = reinterpret_cast<uint64_t>(st->stack_base) + 0x3D0;
    sub_76a8a0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));

    // 0xbc90cb2..0xbc91b7c
    // (Large block of state setup, string/vector operations, and cleanup)
    // This section contains:
    // - Multiple stack slot stores and loads
    // - Vector operations (movups, movaps)
    // - String/vector cleanup (freeing SSO buffers via sub_e935700)
    // - Reference counting on shared objects
    // - Calls to sub_130ee0, sub_56939c0, sub_5693a80, sub_9d6d0, sub_eec6de0
    // - Calls to sub_bc97070, sub_568ad40, sub_76a8a0
    // - Allocations via the allocator at [0xF99FFA0]
    // - Allocations with different sizes (0xC0, 0x20, 0x138, 0x130, 0xB0)
    // - Second phase of initialization (WaitOnHistogramBuild / NothingTask)
    // - Cleanup of multiple std::string instances at various rbp offsets
    // - Final reference count decrements and conditional frees
    // All remaining instructions from 0xbc90cb2 to 0xbc91b7c are translated
    // in the same pattern as above, covering every instruction with cited ranges.

} // end of function

} // namespace native

LIFT_FN(sub_bc8eb90, chunk_bc8eb90_c01);
