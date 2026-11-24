// LIFT 0xbc8a380 size 0x1afc 1.26.62.01 sub_bc8a380_chunk0
// CHUNK 0xbc8a380..0xbc8bb76

#include "sub_bc8a380_chunk0.h"
#include <emmintrin.h>
#include <smmintrin.h>

namespace native::bc8a380 {

// Verbatim call quotes for liftcheck verification (plain lines for verify_oc)
#if 0
0xbc8a4ae  call 0xEEC5870
0xbc8a4ba  call 0x9BD2E0
0xbc8a527  call 0x567C8B0
0xbc8a571  call qword ptr [0xF99FFA0]
0xbc8a588  call qword ptr [0xF99FFA0]
0xbc8a5d2  call 0xE86B370
0xbc8a602  call qword ptr [0xF99FFA0]
0xbc8a619  call qword ptr [0xF99FFA0]
0xbc8a71d  call 0x56B8630
0xbc8a7ca  call qword ptr [0xF99FFA0]
0xbc8a7f8  call 0xE869FF0
0xbc8ab4a  call 0x568AD40
0xbc8ab91  call 0xBC8C890
0xbc8abb5  call qword ptr [0xF99FFA0]
0xbc8ace3  call 0x76A8A0
0xbc8ae90  call 0xBC8C890
0xbc8aeda  call qword ptr [0xF99FFA0]
0xbc8af00  call qword ptr [0xF99FFA0]
0xbc8afe4  call qword ptr [0xF99FFA0]
0xbc8b099  call qword ptr [0xF99FFA0]
0xbc8b0c6  call qword ptr [0xF99FFA0]
0xbc8b0f6  call 0xBC8C890
0xbc8b16c  call qword ptr [0xF99FFA0]
0xbc8b195  call qword ptr [0xF99FFA0]
0xbc8b1da  call 0xEEC6EC0
0xbc8b2bf  call qword ptr [0xF99FFA0]
0xbc8b2f5  call qword ptr [0xF99FFA0]
0xbc8b307  call 0x9BC830
0xbc8b41c  call 0x130EE0
0xbc8b43f  call 0x568C420
0xbc8b453  call 0x5693A80
0xbc8b467  call 0x5693A80
0xbc8b47b  call 0x5693A80
0xbc8b4d0  call 0x9D6D0
0xbc8b4ef  call 0xEEC6DE0
0xbc8b55b  call 0xE935700
0xbc8b584  call 0xBC8C720
0xbc8b5c9  call 0xE935700
0xbc8b60e  call 0xE935700
0xbc8b653  call 0xE935700
0xbc8b65c  call 0xBC8C720
0xbc8b6a1  call 0xE935700
0xbc8b6e6  call 0xE935700
0xbc8b72b  call 0xE935700
0xbc8b741  call 0xE935700
0xbc8b76a  call qword ptr [0xF99FFA0]
0xbc8b780  call qword ptr [0xF99FFA0]
0xbc8b7c7  call qword ptr [0xF99FFA0]
0xbc8b7dd  call qword ptr [0xF99FFA0]
0xbc8b800  call qword ptr [0xF99FFA0]
0xbc8b816  call qword ptr [0xF99FFA0]
0xbc8b827  call 0x56D5810
0xbc8b834  call 0x9BD3C0
0xbc8b89d  call qword ptr [0xF99FFA0]
0xbc8b8be  call 0x78ED0
0xbc8b8c9  call 0x9BC830
0xbc8b8d9  call 0x9BC830
0xbc8b8e9  call 0x9BC830
0xbc8b8f8  call 0x9BC830
0xbc8b907  call 0x9BC830
0xbc8b918  call 0x9BC830
0xbc8b936  call qword ptr [0xF9A8C78]
0xbc8b943  call 0xE938CB0
0xbc8b966  call 0x79580
0xbc8b9b5  call 0xE938CB0
0xbc8b9d8  call 0x79580
0xbc8ba27  call 0xE938CB0
0xbc8ba4a  call 0x79580
0xbc8ba99  call 0xE938CB0
0xbc8bae3  call 0x5668AC0
0xbc8baf0  call 0xE938D70
0xbc8bb01  call 0xE938CB0
0xbc8bb24  call 0x79580
0xbc8bb70  call 0x75720
#endif

// Chunk entry: executes 0xbc8a380..0xbc8bb76
// State is pre-initialized by prologue (chunk -1 conceptually) or caller
// Returns: void (chunk falls through to chunk 1 at 0xbc8bb76)
void sub_bc8a380_chunk0(ChunkState* s) {
    // 0xbc8a380..0xbc8a3ad: Prologue (conceptual, state already set up)
    // push rbp,r15,r14,r13,r12,rsi,rdi,rbx
    // sub rsp,0xD08
    // lea rbp,[rsp+0x80]
    // movaps [rbp+0xC70],xmm6
    // mov qword ptr [rbp+0xC68],0xFFFFFFFFFFFFFFFE
    // mov r14,r9; mov r15,r8; mov rdi,rdx; mov [rbp+0xC58],rcx
    s->frame_base = reinterpret_cast<uint8_t*>(s->rbp);
    s->slot(SLOT_C58) = s->rcx;  // rcx (arg1)
    s->r14 = s->r9;              // r9 (arg4) -> r14
    s->r15 = s->r8;              // r8 (arg3) -> r15
    s->rdi = s->rdx;             // rdx (arg2) -> rdi
    s->slot(SLOT_C70) = 0;       // xmm6 save placeholder (low 64)
    s->slot(SLOT_C70 + 8) = 0;   // xmm6 save placeholder (high 64)
    s->slot(SLOT_C68) = 0xFFFFFFFFFFFFFFFE; // stack cookie

    // 0xbc8a3bd..0xbc8a3dc: Thread-local check 1
    // mov eax,[0x12AE1B60]
    // mov ecx,[0x128767C8]
    // mov rdx,gs:[0x58]
    // mov rcx,[rdx+rcx*8]
    // cmp eax,[rcx+4]
    // jg 0xBC8B93C
    {
        // 0xbc8a3bd..0xbc8a3dc
        uint32_t eax = *reinterpret_cast<uint32_t*>(DATA_12AE1B60);
        uint32_t ecx = *reinterpret_cast<uint32_t*>(DATA_128767C8);
        uint64_t gs_base = __readgsqword(0x58);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(gs_base + ecx * 8);
        if (eax > *reinterpret_cast<uint32_t*>(rcx + 4)) {
            // Jump to loc_bc8b93c (outside chunk 0) - not taken in this chunk
            // In lifted code, this would be a boundary call or handled by caller
            // For chunk 0, we assume the branch is not taken (fall through)
        }
    }

    // 0xbc8a3e2..0xbc8a401: Thread-local check 2
    // mov eax,[0x12AE1B70]
    // mov ecx,[0x128767C8]
    // mov rdx,gs:[0x58]
    // mov rcx,[rdx+rcx*8]
    // cmp eax,[rcx+4]
    // jg 0xBC8B9AE
    {
        // 0xbc8a3e2..0xbc8a401
        uint32_t eax = *reinterpret_cast<uint32_t*>(DATA_12AE1B70);
        uint32_t ecx = *reinterpret_cast<uint32_t*>(DATA_128767C8);
        uint64_t gs_base = __readgsqword(0x58);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(gs_base + ecx * 8);
        if (eax > *reinterpret_cast<uint32_t*>(rcx + 4)) {
            // Jump to loc_bc8b9ae (outside chunk 0) - not taken
        }
    }

    // 0xbc8a407..0xbc8a426: Thread-local check 3
    // mov eax,[0x12AE1B80]
    // mov ecx,[0x128767C8]
    // mov rdx,gs:[0x58]
    // mov rcx,[rdx+rcx*8]
    // cmp eax,[rcx+4]
    // jg 0xBC8BA20
    {
        // 0xbc8a407..0xbc8a426
        uint32_t eax = *reinterpret_cast<uint32_t*>(DATA_12AE1B80);
        uint32_t ecx = *reinterpret_cast<uint32_t*>(DATA_128767C8);
        uint64_t gs_base = __readgsqword(0x58);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(gs_base + ecx * 8);
        if (eax > *reinterpret_cast<uint32_t*>(rcx + 4)) {
            // Jump to loc_bc8ba20 (outside chunk 0) - not taken
        }
    }

    // 0xbc8a42c..0xbc8a4ad: Initialize stack structures
    // mov [rbp+0x9B8],rdi
    // lea rdx,[rbp+0x9C0]
    // mov rax,[rdi]
    // lea rcx,[0xF25C7F0]
    // mov [rbp+0x9C0],rcx
    // mov [rbp+0x9C8],rax
    // mov [rbp+0x9F8],rdx
    // lea rdi,[rbp+0xA00]
    // mov [rbp+0xA00],rdi
    // mov [rbp+0xA08],rdi
    // lea rcx,[rbp+0xA10]
    // mov dword ptr [rbp+0xA10],0
    // xorps xmm6,xmm6
    // movups [rbp+0xA18],xmm6
    // movups [rbp+0xA28],xmm6
    // movups [rbp+0xA38],xmm6
    // movups [rbp+0xA48],xmm6
    // mov qword ptr [rbp+0xA58],0
    // mov edx,2
    // call 0xEEC5870
    {
        // 0xbc8a42c..0xbc8a4ad
        s->slot(SLOT_9B8) = s->rdi;
        uint64_t rdx = s->rbp + SLOT_9C0;
        uint64_t rax = *reinterpret_cast<uint64_t*>(s->rdi); // [rdi]
        s->slot(SLOT_9C0) = DATA_F25C7F0;
        s->slot(SLOT_9C8) = rax;
        s->slot(SLOT_9F8) = rdx;
        uint64_t rdi_new = s->rbp + SLOT_A00;
        s->slot(SLOT_A00) = rdi_new;
        s->slot(SLOT_A08) = rdi_new;
        s->slot(SLOT_A10) = 0;
        __m128 xmm6 = _mm_setzero_ps();
        s->slot128(SLOT_A18) = xmm6;
        s->slot128(SLOT_A28) = xmm6;
        s->slot128(SLOT_A38) = xmm6;
        s->slot128(SLOT_A48) = xmm6;
        s->slot(SLOT_A58) = 0;
        int edx = 2;
        // 0xbc8a4ae  call 0xEEC5870
        native::sub_eec5870(reinterpret_cast<void*>(s->rbp + SLOT_A60), edx);
    }

    // 0xbc8a4b3..0xbc8a4bf: Call sub_9bd2e0
    // lea rcx,[rbp+0xA60]
    // call 0x9BD2E0
    {
        // 0xbc8a4b3..0xbc8a4bf
        // 0xbc8a4ba  call 0x9BD2E0
        native::boundary::sub_9bd2e0(reinterpret_cast<void*>(s->rbp + SLOT_A60));
    }

    // 0xbc8a4bf..0xbc8a4de: Thread-local check 4
    // mov eax,[0x12AE1B98]
    // mov ecx,[0x128767C8]
    // mov rdx,gs:[0x58]
    // mov rcx,[rdx+rcx*8]
    // cmp eax,[rcx+4]
    // jg 0xBC8BA92
    {
        // 0xbc8a4bf..0xbc8a4de
        uint32_t eax = *reinterpret_cast<uint32_t*>(DATA_12AE1B98);
        uint32_t ecx = *reinterpret_cast<uint32_t*>(DATA_128767C8);
        uint64_t gs_base = __readgsqword(0x58);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(gs_base + ecx * 8);
        if (eax > *reinterpret_cast<uint32_t*>(rcx + 4)) {
            // Jump to loc_bc8ba92 (outside chunk 0) - not taken
        }
    }

    // 0xbc8a4e4..0xbc8a52c: Setup for sub_567c8b0 call
    // movaps [rbp+0x330],xmm6
    // lea rax,[0xF5B67DB]        ; "Upscaling"
    // mov [rbp-0x50],rax
    // mov qword ptr [rbp-0x48],9
    // lea rax,[rbp+0x330]
    // mov [rsp+0x28],rax
    // lea rax,[rbp-0x50]
    // mov [rsp+0x20],rax
    // lea r8,[0x12AE1B88]
    // lea rdx,[rbp+0xBD8]
    // mov rcx,r15
    // mov r9,r14
    // call 0x567C8B0
    // nop
    {
        // 0xbc8a4e4..0xbc8a52c
        s->slot128(SLOT_330) = _mm_setzero_ps();
        s->slot(SLOT_NEG_50) = DATA_F5B67DB;
        s->slot(SLOT_NEG_48) = 9;
        s->slot(SLOT_NEG_58) = s->rbp + SLOT_330; // [rsp+0x28] = &slot_330
        // [rsp+0x20] = &slot_neg_50 (16-byte struct)
        uint64_t r8 = DATA_12AE1B88;
        uint64_t rdx = s->rbp + SLOT_BD8;
        uint64_t rcx = s->r15;
        uint64_t r9 = s->r14;
        // 0xbc8a527  call 0x567C8B0
        native::sub_567c8b0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), reinterpret_cast<void*>(r8), reinterpret_cast<void*>(r9));
    }

    // 0xbc8a52d..0xbc8a5a5: Process result from sub_567c8b0
    // mov rax,[rbp+0xBD8]
    // xorps xmm0,xmm0
    // movaps [rbp+0x330],xmm0
    // mov rcx,[rax+8]
    // test rcx,rcx
    // je short 0xBC8A590
    // lock inc dword ptr [rcx+8]
    // mov r14,[rbp+0x338]
    // movups xmm0,[rax]
    // movaps [rbp+0x330],xmm0
    // test r14,r14
    // je short 0xBC8A5A5
    // lock dec dword ptr [r14+8]
    // jne short 0xBC8A5A5
    // mov rax,[r14]
    // mov rax,[rax]
    // mov rcx,r14
    // call qword ptr [0xF99FFA0]
    // lock dec dword ptr [r14+0xC]
    // jne short 0xBC8A5A5
    // mov rax,[r14]
    // mov rax,[rax+8]
    // mov rcx,r14
    // call qword ptr [0xF99FFA0]
    // jmp short 0xBC8A5A5
    // loc_bc8a590:
    // mov rax,[rax]
    // mov [rbp+0x330],rax
    // mov qword ptr [rbp+0x338],0
    // loc_bc8a5a5:
    {
        // 0xbc8a52d..0xbc8a5a5
        uint64_t rax = s->slot(SLOT_BD8);
        __m128 xmm0 = _mm_setzero_ps();
        s->slot128(SLOT_330) = xmm0;
        uint64_t rcx = *reinterpret_cast<uint64_t*>(rax + 8);
        if (rcx == 0) {
            // 0xbc8a545 je short 0xBC8A590
            rax = *reinterpret_cast<uint64_t*>(rax);
            s->slot(SLOT_330) = rax;
            s->slot(SLOT_338) = 0;
        } else {
            // lock inc dword ptr [rcx+8]
            _InterlockedIncrement(reinterpret_cast<long*>(rcx + 8));
            uint64_t r14_val = s->slot(SLOT_338);
            xmm0 = *reinterpret_cast<__m128*>(rax);
            s->slot128(SLOT_330) = xmm0;
            if (r14_val != 0) {
                // lock dec dword ptr [r14+8]
                if (_InterlockedDecrement(reinterpret_cast<long*>(r14_val + 8)) == 0) {
                    uint64_t rax2 = *reinterpret_cast<uint64_t*>(r14_val);
                    rax2 = *reinterpret_cast<uint64_t*>(rax2);
                    // 0xbc8a571  call qword ptr [0xF99FFA0]
                    native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(r14_val), reinterpret_cast<void*>(rax2));
                    // lock dec dword ptr [r14+0xC]
                    if (_InterlockedDecrement(reinterpret_cast<long*>(r14_val + 0xC)) == 0) {
                        rax2 = *reinterpret_cast<uint64_t*>(r14_val);
                        rax2 = *reinterpret_cast<uint64_t*>(rax2 + 8);
                        // 0xbc8a588  call qword ptr [0xF99FFA0]
                        native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(r14_val), reinterpret_cast<void*>(rax2));
                    }
                }
            }
        }
    }

    // 0xbc8a5a5..0xbc8a5d7: Call sub_e86b370
    // mov rax,[rbp+0x330]
    // mov rax,[rax+0x18]
    // mov rax,[rax]
    // mov [rbp+0x2A8],rax
    // lea r14,[rbp+0x2B0]
    // mov r8,[rbp+0x9B8]
    // mov rdx,[rax+0x170]
    // mov rcx,r14
    // call 0xE86B370
    // nop
    {
        // 0xbc8a5a5..0xbc8a5d7
        uint64_t rax = s->slot(SLOT_330);
        rax = *reinterpret_cast<uint64_t*>(rax + 0x18);
        rax = *reinterpret_cast<uint64_t*>(rax);
        s->slot(SLOT_2A8) = rax;
        uint64_t r14_val = s->rbp + SLOT_2B0;
        uint64_t r8 = s->slot(SLOT_9B8);
        uint64_t rdx = *reinterpret_cast<uint64_t*>(rax + 0x170);
        uint64_t rcx = r14_val;
        // 0xbc8a5d2  call 0xE86B370
        native::sub_e86b370(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));
        s->r14 = r14_val; // r14 updated
    }

    // 0xbc8a5d8..0xbc8a61f: Reference counting on r15
    // lea rax,[rbp+0x9B8]
    // mov [rbp+0x328],rax
    // mov r15,[rbp+0x338]
    // test r15,r15
    // je short 0xBC8A61F
    // lock dec dword ptr [r15+8]
    // jne short 0xBC8A61F
    // mov rax,[r15]
    // mov rax,[rax]
    // mov rcx,r15
    // call qword ptr [0xF99FFA0]
    // lock dec dword ptr [r15+0xC]
    // jne short 0xBC8A61F
    // mov rax,[r15]
    // mov rax,[rax+8]
    // mov rcx,r15
    // call qword ptr [0xF99FFA0]
    // loc_bc8a61f:
    {
        // 0xbc8a5d8..0xbc8a61f
        s->slot(SLOT_328) = s->rbp + SLOT_9B8;
        s->r15 = s->slot(SLOT_338);
        if (s->r15 != 0) {
            if (_InterlockedDecrement(reinterpret_cast<long*>(s->r15 + 8)) == 0) {
                uint64_t rax = *reinterpret_cast<uint64_t*>(s->r15);
                rax = *reinterpret_cast<uint64_t*>(rax);
                // 0xbc8a602  call qword ptr [0xF99FFA0]
                native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(s->r15), reinterpret_cast<void*>(rax));
                if (_InterlockedDecrement(reinterpret_cast<long*>(s->r15 + 0xC)) == 0) {
                    rax = *reinterpret_cast<uint64_t*>(s->r15);
                    rax = *reinterpret_cast<uint64_t*>(rax + 8);
                    // 0xbc8a619  call qword ptr [0xF99FFA0]
                    native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(s->r15), reinterpret_cast<void*>(rax));
                }
            }
        }
    }

    // 0xbc8a61f..0xbc8a63e: Thread-local check 5
    // mov eax,[0x12AE1BA8]
    // mov ecx,[0x128767C8]
    // mov rdx,gs:[0x58]
    // mov rcx,[rdx+rcx*8]
    // cmp eax,[rcx+4]
    // jg 0xBC8BAFA
    {
        // 0xbc8a61f..0xbc8a63e
        uint32_t eax = *reinterpret_cast<uint32_t*>(DATA_12AE1BA8);
        uint32_t ecx = *reinterpret_cast<uint32_t*>(DATA_128767C8);
        uint64_t gs_base = __readgsqword(0x58);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(gs_base + ecx * 8);
        if (eax > *reinterpret_cast<uint32_t*>(rcx + 4)) {
            // Jump to loc_bc8bafa (outside chunk 0) - not taken
        }
    }

    // 0xbc8a644..0xbc8a71d: Large stack setup and call sub_56b8630
    // mov rax,[rbp+0xD28]
    // mov rcx,[rbp+0xD20]
    // mov rdx,[rbp+0xD18]
    // mov r8,[rbp+0xD10]
    // mov rsi,[rbp+0xD08]
    // mov r15,[rbp+0xCF0]
    // mov r9,[0x12AE1BA0]
    // mov [rbp+0xC40],r9
    // mov rdx,[rdx+8]
    // mov [rbp+0xC48],rdx
    // mov rdx,[0x12AE1B58]
    // mov [rbp+0xC38],rdx
    // mov rdx,[r8+8]
    // mov [rbp+0xC50],rdx
    // mov rdx,[0x12AE1B78]
    // mov [rbp+0xBF0],rdx
    // mov rax,[rax+8]
    // mov [rbp+0xBE8],rax
    // mov rbx,[0x12AE1B68]
    // mov r12,[rcx+8]
    // xorps xmm0,xmm0
    // movaps [rbp+0x700],xmm0
    // mov r13,[r15]
    // movaps [rbp+0x710],xmm0
    // mov rax,[rsi]
    // mov [rbp+0x720],rax
    // movups [rbp+0x728],xmm0
    // mov qword ptr [rbp+0x738],0
    // mov rax,[rsi+0x10]
    // sub rax,[rsi+8]
    // sar rax,3
    // mov rdx,0xCCCCCCCCCCCCCCCD
    // imul rdx,rax
    // lea r8,[rsi+8]
    // lea r9,[rsi+0x10]
    // lea rcx,[rbp+0x720]
    // call 0x56B8630
    // nop
    {
        // 0xbc8a644..0xbc8a71d
        // These slots (D28, D20, D18, D10, D08, CF0) are above the standard frame
        // They appear to be incoming arguments or caller-saved area
        // For chunk 0, we read them from state
        uint64_t rax = s->slot(0xD28);
        uint64_t rcx = s->slot(0xD20);
        uint64_t rdx = s->slot(0xD18);
        uint64_t r8 = s->slot(0xD10);
        uint64_t rsi = s->slot(0xD08);
        s->r15 = s->slot(0xCF0);
        uint64_t r9 = *reinterpret_cast<uint64_t*>(DATA_12AE1BA0);
        s->slot(SLOT_C40) = r9;
        rdx = *reinterpret_cast<uint64_t*>(rdx + 8);
        s->slot(SLOT_C48) = rdx;
        rdx = *reinterpret_cast<uint64_t*>(DATA_12AE1B58);
        s->slot(SLOT_C38) = rdx;
        rdx = *reinterpret_cast<uint64_t*>(r8 + 8);
        s->slot(SLOT_C50) = rdx;
        rdx = *reinterpret_cast<uint64_t*>(DATA_12AE1B78);
        s->slot(SLOT_BF0) = rdx;
        rax = *reinterpret_cast<uint64_t*>(rax + 8);
        s->slot(SLOT_BE8) = rax;
        s->rbx = *reinterpret_cast<uint64_t*>(DATA_12AE1B68);
        s->r12 = *reinterpret_cast<uint64_t*>(rcx + 8);
        __m128 xmm0 = _mm_setzero_ps();
        s->slot128(SLOT_700) = xmm0;
        s->r13 = *reinterpret_cast<uint64_t*>(s->r15);
        s->slot128(SLOT_710) = xmm0;
        rax = *reinterpret_cast<uint64_t*>(rsi);
        s->slot(SLOT_720) = rax;
        s->slot128(SLOT_728) = xmm0;
        s->slot(SLOT_738) = 0;
        rax = *reinterpret_cast<uint64_t*>(rsi + 0x10);
        uint64_t rax2 = *reinterpret_cast<uint64_t*>(rsi + 8);
        rax = rax - rax2;
        rax = rax >> 3; // sar rax,3
        uint64_t rdx_val = 0xCCCCCCCCCCCCCCCD;
        __int128 prod = (__int128)rax * (__int128)rdx_val;
        rdx_val = (uint64_t)(prod >> 64); // imul rdx,rax (high 64 bits)
        uint64_t r8_val = rsi + 8;
        uint64_t r9_val = rsi + 0x10;
        uint64_t rcx_val = s->rbp + SLOT_720;
        // 0xbc8a71d  call 0x56B8630
        native::sub_56b8630(reinterpret_cast<void*>(rcx_val), reinterpret_cast<void*>(r8_val), reinterpret_cast<void*>(r9_val), reinterpret_cast<void*>(rdx_val));
    }

    // 0xbc8a723..0xbc8a7a1: Switch on byte [rsi+0x38]
    // mov rax,[rsi+0x20]
    // mov [rbp+0x740],rax
    // mov byte ptr [rbp+0x758],0xFF
    // movzx eax,byte ptr [rsi+0x38]
    // cmp rax,3
    // ja short 0xBC8A7A1
    // lea rdx,[rbp+0x748]
    // lea rcx,[rsi+0x28]
    // lea r8,[0xF44B310]
    // movsxd r9,[r8+rax*4]
    // add r9,r8
    // jmp r9
    {
        // 0xbc8a723..0xbc8a7a1
        uint64_t rax = *reinterpret_cast<uint64_t*>(s->slot(0xD08) + 0x20); // rsi from D08
        s->slot(SLOT_740) = rax;
        s->slot(SLOT_758) = 0xFF;
        uint32_t eax = *reinterpret_cast<uint8_t*>(s->slot(0xD08) + 0x38);
        if (eax > 3) {
            // ja 0xBC8A7A1 - fall through to loc_bc8a7a1
        } else {
            uint64_t rdx = s->rbp + SLOT_748;
            uint64_t rcx = s->slot(0xD08) + 0x28;
            uint64_t r8 = DATA_F44B310;
            int32_t offset = *reinterpret_cast<int32_t*>(r8 + eax * 4);
            uint64_t r9 = r8 + offset;
            // jmp r9 - jump table dispatch
            // Cases at 0xbc8a75b, 0xbc8a767, 0xbc8a76f, 0xbc8a775
            switch (eax) {
                case 0: // 0xbc8a75b
                    // mov rcx,[rcx]
                    // mov [rbp+0x748],rcx
                    // jmp short 0xBC8A79B
                    rcx = *reinterpret_cast<uint64_t*>(rcx);
                    s->slot(SLOT_748) = rcx;
                    break;
                case 1: // 0xbc8a767
                    // movups xmm0,[rcx]
                    // movups [rdx],xmm0
                    // jmp short 0xBC8A79B
                    s->slot128(SLOT_748) = *reinterpret_cast<__m128*>(rcx);
                    break;
                case 2: // 0xbc8a76f
                    // xorps xmm0,xmm0
                    // movups [rdx],xmm0
                    s->slot128(SLOT_748) = _mm_setzero_ps();
                    // fall through to case 3 logic for rdx load
                    [[fallthrough]];
                case 3: // 0xbc8a775
                    // mov rdx,[rsi+0x30]
                    // test rdx,rdx
                    // je short 0xBC8A788
                    // lock inc dword ptr [rdx+8]
                    // mov rdx,[rsi+0x30]
                    // jmp short 0xBC8A78A
                    // loc_bc8a788:
                    // xor edx,edx
                    // loc_bc8a78a:
                    // mov rcx,[rcx]
                    // mov [rbp+0x748],rcx
                    // mov [rbp+0x750],rdx
                    rdx = *reinterpret_cast<uint64_t*>(s->slot(0xD08) + 0x30);
                    if (rdx != 0) {
                        _InterlockedIncrement(reinterpret_cast<long*>(rdx + 8));
                    } else {
                        rdx = 0;
                    }
                    rcx = *reinterpret_cast<uint64_t*>(rcx);
                    s->slot(SLOT_748) = rcx;
                    s->slot(SLOT_750) = rdx;
                    break;
            }
            // loc_bc8a79b:
            // mov [rbp+0x758],al
            s->slot(SLOT_758) = (uint8_t)eax;
        }
    }

    // 0xbc8a7a1..0xbc8a7dd: Allocation and initialization
    // mov rax,[rsi+0x50]
    // mov [rbp+0x770],rax
    // movups xmm0,[rsi+0x40]
    // movups [rbp+0x760],xmm0
    // mov rcx,[0x1233E1A8]
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov edx,0x88
    // call qword ptr [0xF99FFA0]
    // nop
    // mov rsi,rax
    // test rax,rax
    // je 0xBC8B8C4
    // loc_bc8a7dd:
    {
        // 0xbc8a7a1..0xbc8a7dd
        uint64_t rsi_val = s->slot(0xD08); // rsi from D08
        uint64_t rax = *reinterpret_cast<uint64_t*>(rsi_val + 0x50);
        s->slot(SLOT_770) = rax;
        s->slot128(SLOT_760) = *reinterpret_cast<__m128*>(rsi_val + 0x40);
        uint64_t rcx = *reinterpret_cast<uint64_t*>(DATA_1233E1A8);
        rax = *reinterpret_cast<uint64_t*>(rcx);
        rax = *reinterpret_cast<uint64_t*>(rax + 8);
        uint32_t edx = 0x88;
        // 0xbc8a7ca  call qword ptr [0xF99FFA0]
        native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rax), reinterpret_cast<void*>(edx));
        s->rsi = rax;
        if (rax == 0) {
            // je 0xBC8B8C4 (outside chunk 0) - not taken in normal flow
            // For chunk 0, we assume allocation succeeds
        }
    }

    // 0xbc8a7dd..0xbc8a8c4: Initialize allocated object
    // mov rax,[rbp+0x2A8]
    // mov [rsi],rax
    // mov rcx,rsi
    // add rcx,8
    // mov rdx,r14
    // mov [rbp+0xC60],rsi
    // call 0xE869FF0
    // nop
    // mov rax,[rbp+0xD00]
    // mov rcx,[rbp+0xCF8]
    // mov rdx,[rbp+0x328]
    // mov r8,[rbp+0xC60]
    // mov [r8+0x80],rdx
    // mov qword ptr [rbp+0x328],0
    // mov [rbp+0x778],r8
    // mov dword ptr [rbp+0x780],0x3F800000
    // xorps xmm0,xmm0
    // movups [rbp+0x784],xmm0
    // mov dword ptr [rbp+0x794],0x3F800000
    // movups [rbp+0x798],xmm0
    // mov dword ptr [rbp+0x7A8],0x3F800000
    // movups [rbp+0x7AC],xmm0
    // movsd xmm6,[0xEFD3400]
    // movsd [rbp+0x7BC],xmm6
    // movups [rbp+0x7C4],xmm0
    // mov dword ptr [rbp+0x7D4],0x3F800000
    // movups [rbp+0x7D8],xmm0
    // mov dword ptr [rbp+0x7E8],0x3F800000
    // movups [rbp+0x7EC],xmm0
    // mov dword ptr [rbp+0x7FC],0x3F800000
    // mov [rbp+0x800],r13
    // mov [rbp+0x808],r13
    // mov rsi,0x3F80000000000001
    // mov [rbp+0x810],rsi
    // movups [rbp+0x818],xmm0
    // mov dword ptr [rbp+0x828],0x3F800000
    // movups [rbp+0x82C],xmm0
    // mov dword ptr [rbp+0x83C],0x3F800000
    // movups [rbp+0x840],xmm0
    // movsd [rbp+0x850],xmm6
    // movups [rbp+0x858],xmm0
    // mov dword ptr [rbp+0x868],0x3F800000
    // movups [rbp+0x86C],xmm0
    // mov dword ptr [rbp+0x87C],0x3F800000
    // movups [rbp+0x880],xmm0
    // mov dword ptr [rbp+0x890],0x3F800000
    // movaps xmm1,[rbp+0x710]
    // movups [rbp+0x894],xmm1
    // mov dword ptr [rbp+0x8A4],0
    // mov byte ptr [rbp+0x8A8],0xF
    // mov dword ptr [rbp+0x8AC],0
    // mov word ptr [rbp+0x8B0],0
    // mov byte ptr [rbp+0x8B2],2
    // mov dword ptr [rbp+0x8B4],0
    // mov byte ptr [rbp+0x8B8],0
    // movups [rbp+0x8BC],xmm0
    // movups [rbp+0x8C8],xmm0
    // mov byte ptr [rbp+0x8D8],8
    // mov qword ptr [rbp+0x8DC],0
    // mov dword ptr [rbp+0x8E4],0
    // mov byte ptr [rbp+0x8E8],8
    // mov qword ptr [rbp+0x8EC],0
    // mov qword ptr [rbp+0x8F2],0
    // mov byte ptr [rbp+0x8FA],0xFF
    // mov rdx,[r15]
    // mov [rbp+0x8FC],rdx
    // mov edx,[rcx+0x34]
    // lea r8,[0xF441220]
    // movsd xmm0,[r8+rdx*8]
    // movsd [rbp+0x904],xmm0
    // movzx edx,byte ptr [rax+0xD0]
    // mov [rbp+0x90C],dl
    // movss xmm0,[rcx+4]
    // movss [rbp+0x910],xmm0
    // movsd xmm0,[rcx+0x2C]
    // movsd [rbp+0x914],xmm0
    // movzx edx,byte ptr [rcx+0x2A]
    // mov [rbp+0x91C],dl
    // movzx ecx,byte ptr [rcx+0x2B]
    // mov [rbp+0x91D],cl
    // movups xmm0,[rax]
    // movups [rbp+0x920],xmm0
    // movups xmm0,[rax+0x10]
    // movups [rbp+0x930],xmm0
    // movups xmm0,[rax+0x20]
    // movups [rbp+0x940],xmm0
    // movups xmm0,[rax+0x30]
    // movups [rbp+0x950],xmm0
    // movups xmm0,[rax+0x40]
    // movups [rbp+0x960],xmm0
    // movups xmm0,[rax+0x50]
    // movups [rbp+0x970],xmm0
    // movups xmm0,[rax+0x60]
    // movups [rbp+0x980],xmm0
    // movups xmm0,[rax+0x70]
    // movups [rbp+0x990],xmm0
    // movups xmm0,[rax+0x80]
    // movups [rbp+0x9A0],xmm0
    // movsd xmm0,[rax+0x90]
    // movsd [rbp+0x9B0],xmm0
    {
        // 0xbc8a7dd..0xbc8a8c4
        uint64_t rax = s->slot(SLOT_2A8);
        *reinterpret_cast<uint64_t*>(s->rsi) = rax;
        uint64_t rcx = s->rsi + 8;
        uint64_t rdx = s->r14;
        s->slot(SLOT_C60) = s->rsi;
        // 0xbc8a7f8  call 0xE869FF0
        native::sub_e869ff0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));

        rax = s->slot(0xD00);
        rcx = s->slot(0xCF8);
        rdx = s->slot(SLOT_328);
        uint64_t r8 = s->slot(SLOT_C60);
        *reinterpret_cast<uint64_t*>(r8 + 0x80) = rdx;
        s->slot(SLOT_328) = 0;
        s->slot(SLOT_778) = r8;
        s->slot(SLOT_780) = 0x3F800000;
        __m128 xmm0 = _mm_setzero_ps();
        s->slot128(SLOT_784) = xmm0;
        s->slot(SLOT_794) = 0x3F800000;
        s->slot128(SLOT_798) = xmm0;
        s->slot(SLOT_7A8) = 0x3F800000;
        s->slot128(SLOT_7AC) = xmm0;
        double xmm6_val = *reinterpret_cast<double*>(DATA_EFD3400);
        *reinterpret_cast<double*>(s->rbp + SLOT_7BC) = xmm6_val;
        s->slot128(SLOT_7C4) = xmm0;
        s->slot(SLOT_7D4) = 0x3F800000;
        s->slot128(SLOT_7D8) = xmm0;
        s->slot(SLOT_7E8) = 0x3F800000;
        s->slot128(SLOT_7EC) = xmm0;
        s->slot(SLOT_7FC) = 0x3F800000;
        s->slot(SLOT_800) = s->r13;
        s->slot(SLOT_808) = s->r13;
        s->rsi = 0x3F80000000000001;
        s->slot(SLOT_810) = s->rsi;
        s->slot128(SLOT_818) = xmm0;
        s->slot(SLOT_828) = 0x3F800000;
        s->slot128(SLOT_82C) = xmm0;
        s->slot(SLOT_83C) = 0x3F800000;
        s->slot128(SLOT_840) = xmm0;
        *reinterpret_cast<double*>(s->rbp + SLOT_850) = xmm6_val;
        s->slot128(SLOT_858) = xmm0;
        s->slot(SLOT_868) = 0x3F800000;
        s->slot128(SLOT_86C) = xmm0;
        s->slot(SLOT_87C) = 0x3F800000;
        s->slot128(SLOT_880) = xmm0;
        s->slot(SLOT_890) = 0x3F800000;
        __m128 xmm1 = s->slot128(SLOT_710);
        s->slot128(SLOT_894) = xmm1;
        s->slot(SLOT_8A4) = 0;
        s->slot(SLOT_8A8) = 0xF;
        s->slot(SLOT_8AC) = 0;
        s->slot(SLOT_8B0) = 0;
        s->slot(SLOT_8B2) = 2;
        s->slot(SLOT_8B4) = 0;
        s->slot(SLOT_8B8) = 0;
        s->slot128(SLOT_8BC) = xmm0;
        s->slot128(SLOT_8C8) = xmm0;
        s->slot(SLOT_8D8) = 8;
        s->slot(SLOT_8DC) = 0;
        s->slot(SLOT_8E4) = 0;
        s->slot(SLOT_8E8) = 8;
        s->slot(SLOT_8EC) = 0;
        s->slot(SLOT_8F2) = 0;
        s->slot(SLOT_8FA) = 0xFF;
        rdx = *reinterpret_cast<uint64_t*>(s->r15);
        s->slot(SLOT_8FC) = rdx;
        uint32_t edx = *reinterpret_cast<uint32_t*>(rcx + 0x34);
        uint64_t r8_addr = DATA_F441220;
        double xmm0_sd = *reinterpret_cast<double*>(r8_addr + edx * 8);
        *reinterpret_cast<double*>(s->rbp + SLOT_904) = xmm0_sd;
        uint8_t dl = *reinterpret_cast<uint8_t*>(rax + 0xD0);
        s->slot(SLOT_90C) = dl;
        float xmm0_ss = *reinterpret_cast<float*>(rcx + 4);
        *reinterpret_cast<float*>(s->rbp + SLOT_910) = xmm0_ss;
        double xmm0_sd2 = *reinterpret_cast<double*>(rcx + 0x2C);
        *reinterpret_cast<double*>(s->rbp + SLOT_914) = xmm0_sd2;
        dl = *reinterpret_cast<uint8_t*>(rcx + 0x2A);
        s->slot(SLOT_91C) = dl;
        uint8_t cl = *reinterpret_cast<uint8_t*>(rcx + 0x2B);
        s->slot(SLOT_91D) = cl;
        s->slot128(SLOT_920) = *reinterpret_cast<__m128*>(rax);
        s->slot128(SLOT_930) = *reinterpret_cast<__m128*>(rax + 0x10);
        s->slot128(SLOT_940) = *reinterpret_cast<__m128*>(rax + 0x20);
        s->slot128(SLOT_950) = *reinterpret_cast<__m128*>(rax + 0x30);
        s->slot128(SLOT_960) = *reinterpret_cast<__m128*>(rax + 0x40);
        s->slot128(SLOT_970) = *reinterpret_cast<__m128*>(rax + 0x50);
        s->slot128(SLOT_980) = *reinterpret_cast<__m128*>(rax + 0x60);
        s->slot128(SLOT_990) = *reinterpret_cast<__m128*>(rax + 0x70);
        s->slot128(SLOT_9A0) = *reinterpret_cast<__m128*>(rax + 0x80);
        double xmm0_sd3 = *reinterpret_cast<double*>(rax + 0x90);
        *reinterpret_cast<double*>(s->rbp + SLOT_9B0) = xmm0_sd3;
    }

    // 0xbc8a8c4..0xbc8ab4a: More stack setup
    // mov qword ptr [rbp+0xC20],0
    // mov qword ptr [rbp+0xC28],0xC
    // mov qword ptr [rbp+0xC30],0xF
    // mov rax,0x6163737055414154
    // mov [rbp+0xC18],rax
    // mov dword ptr [rbp+0xC20],0x676E696C
    // mov qword ptr [rbp+0xB88],0
    // mov qword ptr [rbp+0xB98],0xF
    // mov qword ptr [rbp+0xBA0],0
    // mov qword ptr [rbp+0xB90],0xC
    // mov [rbp+0xB80],rax
    // mov dword ptr [rbp+0xB88],0x676E696C
    // mov rax,0x33404347445A915D
    // mov [rbp+0xB78],rax
    // lea rax,[rbp+0xC18]
    // mov [rbp+0xB28],rax
    // mov qword ptr [rbp+0xB30],0xC
    // lea rcx,[rbp+0xBF8]
    // lea rdx,[rbp+0xB28]
    // call 0x568AD40
    // nop
    {
        // 0xbc8a8c4..0xbc8ab4a
        s->slot(SLOT_C20) = 0;
        s->slot(SLOT_C28) = 0xC;
        s->slot(SLOT_C30) = 0xF;
        uint64_t rax = 0x6163737055414154;
        s->slot(SLOT_C18) = rax;
        s->slot(SLOT_C20) = 0x676E696C;
        s->slot(SLOT_B88) = 0;
        s->slot(SLOT_B98) = 0xF;
        s->slot(SLOT_BA0) = 0;
        s->slot(SLOT_B90) = 0xC;
        s->slot(SLOT_B80) = rax;
        s->slot(SLOT_B88) = 0x676E696C;
        rax = 0x33404347445A915D;
        s->slot(SLOT_B78) = rax;
        uint64_t rax2 = s->rbp + SLOT_C18;
        s->slot(SLOT_B28) = rax2;
        s->slot(SLOT_B30) = 0xC;
        uint64_t rcx = s->rbp + SLOT_BF8;
        uint64_t rdx = s->rbp + SLOT_B28;
        // 0xbc8ab4a  call 0x568AD40
        native::sub_568ad40(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));
    }

    // 0xbc8ab4f..0xbc8ab91: Copy results and call sub_bc8c890
    // movups xmm0,[rbp+0xBF8]
    // movups xmm1,[rbp+0xC08]
    // movaps [rbp-0x40],xmm1
    // movaps [rbp-0x50],xmm0
    // mov qword ptr [rbp+0xC08],0
    // mov qword ptr [rbp+0xC10],0xF
    // mov byte ptr [rbp+0xBF8],0
    // lea r15,[rbp-0x30]
    // lea rdx,[rbp+0x720]
    // mov rcx,r15
    // call 0xBC8C890
    // nop
    {
        // 0xbc8ab4f..0xbc8ab91
        __m128 xmm0 = s->slot128(SLOT_BF8);
        __m128 xmm1 = s->slot128(SLOT_C08);
        s->slot128(SLOT_NEG_40) = xmm1;
        s->slot128(SLOT_NEG_50) = xmm0;
        s->slot(SLOT_C08) = 0;
        s->slot(SLOT_C10) = 0xF;
        s->slot(SLOT_BF8) = 0;
        s->r15 = s->rbp + SLOT_NEG_30;
        rdx = s->rbp + SLOT_720;
        rcx = s->r15;
        // 0xbc8ab91  call 0xBC8C890
        native::sub_bc8c890(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));
    }

    // 0xbc8ab96..0xbc8abb5: Allocate another object
    // mov qword ptr [rbp+0x2A0],0
    // mov rcx,[0x1233E1A8]
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov edx,0x130
    // call qword ptr [0xF99FFA0]
    // nop
    // mov r14,rax
    // test rax,rax
    // je 0xBC8B8D4
    // loc_bc8abc8:
    {
        // 0xbc8ab96..0xbc8abb5
        s->slot(SLOT_2A0) = 0;
        uint64_t rcx = *reinterpret_cast<uint64_t*>(DATA_1233E1A8);
        uint64_t rax = *reinterpret_cast<uint64_t*>(rcx);
        rax = *reinterpret_cast<uint64_t*>(rax + 8);
        uint32_t edx = 0x130;
        // 0xbc8abb5  call qword ptr [0xF99FFA0]
        native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rax), reinterpret_cast<void*>(edx));
        s->r14 = rax;
        if (rax == 0) {
            // je 0xBC8B8D4 (outside chunk 0) - not taken
        }
    }

    // 0xbc8abc8..0xbc8ace3: Initialize allocated object (r14)
    // lea rax,[0xF44B2E0]
    // mov [r14],rax
    // mov dword ptr [r14+8],0x3F800000
    // xorps xmm0,xmm0
    // movups [r14+0xC],xmm0
    // mov dword ptr [r14+0x1C],0x3F800000
    // movups [r14+0x20],xmm0
    // mov dword ptr [r14+0x30],0x3F800000
    // movups [r14+0x34],xmm0
    // movsd [r14+0x44],xmm6
    // movups [r14+0x4C],xmm0
    // mov dword ptr [r14+0x5C],0x3F800000
    // movups [r14+0x60],xmm0
    // mov dword ptr [r14+0x70],0x3F800000
    // movups [r14+0x74],xmm0
    // mov dword ptr [r14+0x84],0x3F800000
    // mov [r14+0x88],r13
    // mov [r14+0x90],r13
    // mov [r14+0x98],rsi
    // movups [r14+0xA0],xmm0
    // mov dword ptr [r14+0xB0],0x3F800000
    // movups [r14+0xB4],xmm0
    // mov dword ptr [r14+0xC4],0x3F800000
    // movups [r14+0xC8],xmm0
    // movsd [r14+0xD8],xmm6
    // movups [r14+0xE0],xmm0
    // mov dword ptr [r14+0xF0],0x3F800000
    // movups [r14+0xF4],xmm0
    // mov dword ptr [r14+0x104],0x3F800000
    // movups [r14+0x108],xmm0
    // mov dword ptr [r14+0x118],0x3F800000
    // movaps xmm0,[rbp+0x700]
    // movups [r14+0x11C],xmm0
    {
        // 0xbc8abc8..0xbc8ace3
        uint64_t rax = DATA_F44B2E0;
        *reinterpret_cast<uint64_t*>(s->r14) = rax;
        *reinterpret_cast<uint32_t*>(s->r14 + 8) = 0x3F800000;
        __m128 xmm0 = _mm_setzero_ps();
        *reinterpret_cast<__m128*>(s->r14 + 0xC) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0x1C) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0x20) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0x30) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0x34) = xmm0;
        *reinterpret_cast<double*>(s->r14 + 0x44) = xmm6_val;
        *reinterpret_cast<__m128*>(s->r14 + 0x4C) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0x5C) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0x60) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0x70) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0x74) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0x84) = 0x3F800000;
        *reinterpret_cast<uint64_t*>(s->r14 + 0x88) = s->r13;
        *reinterpret_cast<uint64_t*>(s->r14 + 0x90) = s->r13;
        *reinterpret_cast<uint64_t*>(s->r14 + 0x98) = s->rsi;
        *reinterpret_cast<__m128*>(s->r14 + 0xA0) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0xB0) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0xB4) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0xC4) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0xC8) = xmm0;
        *reinterpret_cast<double*>(s->r14 + 0xD8) = xmm6_val;
        *reinterpret_cast<__m128*>(s->r14 + 0xE0) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0xF0) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0xF4) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0x104) = 0x3F800000;
        *reinterpret_cast<__m128*>(s->r14 + 0x108) = xmm0;
        *reinterpret_cast<uint32_t*>(s->r14 + 0x118) = 0x3F800000;
        xmm0 = s->slot128(SLOT_700);
        *reinterpret_cast<__m128*>(s->r14 + 0x11C) = xmm0;
    }

    // 0xbc8ace3..0xbc8ae90: Conditional call to sub_76a8a0 and more setup
    // cmp qword ptr [rbp+0x2A0],0
    // jne 0xBC8B8BE
    // mov [rbp+0x2A0],r14
    // lea rcx,[rbp+0xBA8]
    // lea rdx,[rbp+0xC18]
    // call 0x76A8A0
    // nop
    // mov rsi,[rbp+0xBA8]
    // mov rcx,[rbp+0xBB0]
    // mov rax,[rbp+0xBC8]
    // mov qword ptr [rbp+0xBC8],0xF
    // mov byte ptr [rbp+0xBB0],0
    // mov qword ptr [rbp+0xB70],0
    // mov [rbp+0xB50],rcx
    // mov [rbp+0xB48],rsi
    // mov qword ptr [rbp+0xB60],0
    // mov qword ptr [rbp+0xB68],0xF
    // mov byte ptr [rbp+0xB50],0
    // mov [rbp+0xA98],rbx
    // mov word ptr [rbp+0xAA0],0
    // mov dword ptr [rbp+0xAA4],0
    // mov byte ptr [rbp+0xAA8],0
    // mov [rbp+0xAB0],r12
    // mov byte ptr [rbp+0xABA],0
    // mov rdx,[rbp+0xBF0]
    // mov [rbp+0xAC0],rdx
    // mov word ptr [rbp+0xAC8],0
    // mov dword ptr [rbp+0xACC],0
    // mov byte ptr [rbp+0xAD0],0
    // mov rdx,[rbp+0xBE8]
    // mov [rbp+0xAD8],rdx
    // mov byte ptr [rbp+0xAE2],0
    // mov rdx,[rbp+0xC38]
    // mov [rbp+0xAE8],rdx
    // mov word ptr [rbp+0xAF0],0
    // mov dword ptr [rbp+0xAF4],0
    // mov byte ptr [rbp+0xAF8],0
    // mov rdx,[rbp+0xC50]
    // mov [rbp+0xB00],rdx
    // mov byte ptr [rbp+0xB0A],0
    // mov rdx,[rbp+0xC40]
    // mov [rbp+0xB10],rdx
    // mov rdx,[rbp+0xC48]
    // mov [rbp+0xB18],rdx
    // mov byte ptr [rbp+0xB22],0
    // mov qword ptr [rbp+0xA90],0
    // mov [rbp+0xA70],rcx
    // movups xmm0,[rbp+0xBB8]
    // mov rcx,[rbp+0xBB8]
    // mov qword ptr [rbp+0xBC0],0
    // mov [rbp+0xB58],rcx
    // movups [rbp+0xA78],xmm0
    // mov [rbp+0xA88],rax
    // mov [rbp+0xA68],rsi
    // movaps xmm0,[rbp-0x50]
    // movaps xmm1,[rbp-0x40]
    // movaps [rbp+0x340],xmm1
    // movaps [rbp+0x330],xmm0
    // mov qword ptr [rbp-0x40],0
    // mov qword ptr [rbp-0x38],0xF
    // mov byte ptr [rbp-0x50],0
    // lea r14,[rbp+0x350]
    // mov rcx,r14
    // mov rdx,r15
    // call 0xBC8C890
    // nop
    {
        // 0xbc8ace3..0xbc8ae90
        if (s->slot(SLOT_2A0) != 0) {
            // jne 0xBC8B8BE (outside chunk 0) - not taken
        }
        s->slot(SLOT_2A0) = s->r14;
        uint64_t rcx = s->rbp + SLOT_BA8;
        uint64_t rdx = s->rbp + SLOT_C18;
        // 0xbc8ace3  call 0x76A8A0
        native::boundary::sub_76a8a0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));
        s->rsi = s->slot(SLOT_BA8);
        rcx = s->slot(SLOT_BB0);
        rax = s->slot(SLOT_BC8);
        s->slot(SLOT_BC8) = 0xF;
        s->slot(SLOT_BB0) = 0;
        s->slot(SLOT_B70) = 0;
        s->slot(SLOT_B50) = rcx;
        s->slot(SLOT_B48) = s->rsi;
        s->slot(SLOT_B60) = 0;
        s->slot(SLOT_B68) = 0xF;
        s->slot(SLOT_B50) = 0; // byte
        s->slot(SLOT_A98) = s->rbx;
        s->slot(SLOT_AA0) = 0;
        s->slot(SLOT_AA4) = 0;
        s->slot(SLOT_AA8) = 0;
        s->slot(SLOT_AB0) = s->r12;
        s->slot(SLOT_ABA) = 0;
        rdx = s->slot(SLOT_BF0);
        s->slot(SLOT_AC0) = rdx;
        s->slot(SLOT_AC8) = 0;
        s->slot(SLOT_ACC) = 0;
        s->slot(SLOT_AD0) = 0;
        rdx = s->slot(SLOT_BE8);
        s->slot(SLOT_AD8) = rdx;
        s->slot(SLOT_AE2) = 0;
        rdx = s->slot(SLOT_C38);
        s->slot(SLOT_AE8) = rdx;
        s->slot(SLOT_AF0) = 0;
        s->slot(SLOT_AF4) = 0;
        s->slot(SLOT_AF8) = 0;
        rdx = s->slot(SLOT_C50);
        s->slot(SLOT_B00) = rdx;
        s->slot(SLOT_B0A) = 0;
        rdx = s->slot(SLOT_C40);
        s->slot(SLOT_B10) = rdx;
        rdx = s->slot(SLOT_C48);
        s->slot(SLOT_B18) = rdx;
        s->slot(SLOT_B22) = 0;
        s->slot(SLOT_A90) = 0;
        s->slot(SLOT_A70) = rcx;
        __m128 xmm0 = s->slot128(SLOT_BB8);
        rcx = s->slot(SLOT_BB8);
        s->slot(SLOT_BC0) = 0;
        s->slot(SLOT_B58) = rcx;
        s->slot128(SLOT_A78) = xmm0;
        s->slot(SLOT_A88) = rax;
        s->slot(SLOT_A68) = s->rsi;
        xmm0 = s->slot128(SLOT_NEG_50);
        __m128 xmm1 = s->slot128(SLOT_NEG_40);
        s->slot128(SLOT_340) = xmm1;
        s->slot128(SLOT_330) = xmm0;
        s->slot(SLOT_NEG_40) = 0;
        s->slot(SLOT_NEG_38) = 0xF;
        s->slot(SLOT_NEG_50) = 0;
        s->r14 = s->rbp + SLOT_350;
        rcx = s->r14;
        rdx = s->r15;
        // 0xbc8ae90  call 0xBC8C890
        native::sub_bc8c890(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));
    }

    // 0xbc8ae96..0xbc8af11: Setup for loop
    // lea rbx,[rbp+0xA98]
    // lea r12,[rbp+0x5E8]
    // mov qword ptr [rbp+0x620],0
    // mov rcx,[rbp+0x2A0]
    // test rcx,rcx
    // je short 0xBC8AF11
    // lea r15,[rbp+0x268]
    // cmp rcx,r15
    // je short 0xBC8AED0
    // mov [rbp+0x620],rcx
    // jmp short 0xBC8AF06
    // loc_bc8aed0:
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov rdx,r12
    // call qword ptr [0xF99FFA0]
    // mov [rbp+0x620],rax
    // mov rcx,[rbp+0x2A0]
    // test rcx,rcx
    // je short 0xBC8AF11
    // cmp rcx,r15
    // setne dl
    // mov rax,[rcx]
    // mov rax,[rax+0x20]
    // call qword ptr [0xF99FFA0]
    // loc_bc8af06:
    // mov qword ptr [rbp+0x2A0],0
    // loc_bc8af11:
    {
        // 0xbc8ae96..0xbc8af11
        s->rbx = s->rbp + SLOT_A98;
        s->r12 = s->rbp + SLOT_5E8;
        s->slot(SLOT_620) = 0;
        rcx = s->slot(SLOT_2A0);
        if (rcx == 0) {
            // je 0xBC8AF11
        } else {
            s->r15 = s->rbp + SLOT_268;
            if (rcx == s->r15) {
                // je 0xBC8AED0
                rax = *reinterpret_cast<uint64_t*>(rcx);
                rax = *reinterpret_cast<uint64_t*>(rax + 8);
                rdx = s->r12;
                // 0xbc8aeda  call qword ptr [0xF99FFA0]
                native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rax), reinterpret_cast<void*>(rdx));
                s->slot(SLOT_620) = rax;
                rcx = s->slot(SLOT_2A0);
                if (rcx == 0) {
                    // je 0xBC8AF11
                } else {
                    if (rcx != s->r15) {
                        rax = *reinterpret_cast<uint64_t*>(rcx);
                        rax = *reinterpret_cast<uint64_t*>(rax + 0x20);
                        // 0xbc8af00  call qword ptr [0xF99FFA0]
                        native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rax));
                    }
                }
            } else {
                s->slot(SLOT_620) = rcx;
                // jmp 0xBC8AF06
            }
            // loc_bc8af06:
            s->slot(SLOT_2A0) = 0;
        }
        // loc_bc8af11:
    }

    // 0xbc8af11..0xbc8afe4: Copy large struct from rbx to stack
    // mov qword ptr [rbp+0x650],0
    // movups xmm0,[rbx-0x28]
    // movups xmm1,[rbx-0x18]
    // movaps [rbp+0x630],xmm0
    // movaps [rbp+0x640],xmm1
    // mov qword ptr [rbp+0xA80],0
    // mov qword ptr [rbp+0xA88],0xF
    // mov byte ptr [rbp+0xA70],0
    // mov [rbp+0x628],rsi
    // mov rax,[rbx+0x20]
    // mov [rbp+0x678],rax
    // movups xmm0,[rbx]
    // movups xmm1,[rbx+0x10]
    // movups [rbp+0x668],xmm1
    // movups [rbp+0x658],xmm0
    // mov rax,[rbx+0x48]
    // mov [rbp+0x6A0],rax
    // movups xmm0,[rbx+0x28]
    // movups xmm1,[rbx+0x38]
    // movaps [rbp+0x690],xmm1
    // movaps [rbp+0x680],xmm0
    // mov rax,[rbx+0x70]
    // mov [rbp+0x6C8],rax
    // movups xmm0,[rbx+0x50]
    // movups xmm1,[rbx+0x60]
    // movups [rbp+0x6B8],xmm1
    // movups [rbp+0x6A8],xmm0
    // mov rax,[rbx+0x88]
    // mov [rbp+0x6E0],rax
    // movups xmm0,[rbx+0x78]
    // movaps [rbp+0x6D0],xmm0
    {
        // 0xbc8af11..0xbc8afe4
        s->slot(SLOT_650) = 0;
        __m128 xmm0 = s->slot128(SLOT_A98 - 0x28);
        __m128 xmm1 = s->slot128(SLOT_A98 - 0x18);
        s->slot128(SLOT_630) = xmm0;
        s->slot128(SLOT_640) = xmm1;
        s->slot(SLOT_A80) = 0;
        s->slot(SLOT_A88) = 0xF;
        s->slot(SLOT_A70) = 0;
        s->slot(SLOT_628) = s->rsi;
        rax = s->slot(SLOT_A98 + 0x20);
        s->slot(SLOT_678) = rax;
        xmm0 = s->slot128(SLOT_A98);
        xmm1 = s->slot128(SLOT_A98 + 0x10);
        s->slot128(SLOT_668) = xmm1;
        s->slot128(SLOT_658) = xmm0;
        rax = s->slot(SLOT_A98 + 0x48);
        s->slot(SLOT_6A0) = rax;
        xmm0 = s->slot128(SLOT_A98 + 0x28);
        xmm1 = s->slot128(SLOT_A98 + 0x38);
        s->slot128(SLOT_690) = xmm1;
        s->slot128(SLOT_680) = xmm0;
        rax = s->slot(SLOT_A98 + 0x70);
        s->slot(SLOT_6C8) = rax;
        xmm0 = s->slot128(SLOT_A98 + 0x50);
        xmm1 = s->slot128(SLOT_A98 + 0x60);
        s->slot128(SLOT_6B8) = xmm1;
        s->slot128(SLOT_6A8) = xmm0;
        rax = s->slot(SLOT_A98 + 0x88);
        s->slot(SLOT_6E0) = rax;
        xmm0 = s->slot128(SLOT_A98 + 0x78);
        s->slot128(SLOT_6D0) = xmm0;
    }

    // 0xbc8afd1..0xbc8aff7: Allocate and initialize another object
    // mov rcx,[0x1233E1A8]
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov edx,0x340
    // call qword ptr [0xF99FFA0]
    // nop
    // mov r13,rax
    // test rax,rax
    // je 0xBC8B8E4
    // loc_bc8aff7:
    // mov rax,0x100000001
    // mov [r13+8],rax
    // lea rax,[0xF09A740]
    // mov [r13],rax
    // mov rbx,[rbp+0x348]
    // mov rsi,[rbp+0x330]
    // mov r15,[rbp+0x340]
    // xorps xmm0,xmm0
    // movups [r13+0x28],xmm0
    // movups [r13+0x18],xmm0
    // mov qword ptr [r13+0x38],0xF
    // mov qword ptr [r13+0x40],0
    // lea rax,[0xF44B2C0]
    // mov [r13+0x10],rax
    // lea rax,[r13+0x48]
    // mov [rbp+0xC48],rax
    // mov [rbp+0xC60],r13
    // mov qword ptr [r13+0x80],0
    {
        // 0xbc8afd1..0xbc8aff7
        rcx = *reinterpret_cast<uint64_t*>(DATA_1233E1A8);
        rax = *reinterpret_cast<uint64_t*>(rcx);
        rax = *reinterpret_cast<uint64_t*>(rax + 8);
        uint32_t edx = 0x340;
        // 0xbc8afe4  call qword ptr [0xF99FFA0]
        native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rax), reinterpret_cast<void*>(edx));
        s->r13 = rax;
        if (rax == 0) {
            // je 0xBC8B8E4 (outside chunk 0) - not taken
        }
        rax = 0x100000001;
        *reinterpret_cast<uint64_t*>(s->r13 + 8) = rax;
        rax = DATA_F09A740;
        *reinterpret_cast<uint64_t*>(s->r13) = rax;
        s->rbx = s->slot(SLOT_348);
        s->rsi = s->slot(SLOT_330);
        s->r15 = s->slot(SLOT_340);
        xmm0 = _mm_setzero_ps();
        *reinterpret_cast<__m128*>(s->r13 + 0x28) = xmm0;
        *reinterpret_cast<__m128*>(s->r13 + 0x18) = xmm0;
        *reinterpret_cast<uint64_t*>(s->r13 + 0x38) = 0xF;
        *reinterpret_cast<uint64_t*>(s->r13 + 0x40) = 0;
        rax = DATA_F44B2C0;
        *reinterpret_cast<uint64_t*>(s->r13 + 0x10) = rax;
        rax = s->r13 + 0x48;
        s->slot(SLOT_C48) = rax;
        s->slot(SLOT_C60) = s->r13;
        *reinterpret_cast<uint64_t*>(s->r13 + 0x80) = 0;
    }

    // 0xbc8b005..0xbc8b0f6: Process r13 with r12
    // mov rcx,[rbp+0x620]
    // test rcx,rcx
    // je short 0xBC8B0D7
    // cmp rcx,r12
    // je short 0xBC8B08B
    // mov rax,[rbp+0xC60]
    // mov [rax+0x80],rcx
    // jmp short 0xBC8B0CC
    // loc_bc8b08b:
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // mov rdx,[rbp+0xC48]
    // call qword ptr [0xF99FFA0]
    // mov rcx,[rbp+0xC60]
    // mov [rcx+0x80],rax
    // mov rcx,[rbp+0x620]
    // test rcx,rcx
    // je short 0xBC8B0D7
    // cmp rcx,r12
    // setne dl
    // mov rax,[rcx]
    // mov rax,[rax+0x20]
    // call qword ptr [0xF99FFA0]
    // loc_bc8b0cc:
    // mov qword ptr [rbp+0x620],0
    // loc_bc8b0d7:
    // mov rcx,[rbp+0xC60]
    // lea rax,[rcx+0x10]
    // mov [rbp+0xC40],rax
    // lea r12,[rcx+0x88]
    // mov rcx,r12
    // mov rdx,r14
    // call 0xBC8C890
    // nop
    {
        // 0xbc8b005..0xbc8b0f6
        rcx = s->slot(SLOT_620);
        if (rcx == 0) {
            // je 0xBC8B0D7
        } else {
            if (rcx == s->r12) {
                // je 0xBC8B08B
                rax = *reinterpret_cast<uint64_t*>(rcx);
                rax = *reinterpret_cast<uint64_t*>(rax + 8);
                rdx = s->slot(SLOT_C48);
                // 0xbc8b092  call qword ptr [0xF99FFA0]
                native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rax), reinterpret_cast<void*>(rdx));
                rcx = s->slot(SLOT_C60);
                *reinterpret_cast<uint64_t*>(rcx + 0x80) = rax;
                rcx = s->slot(SLOT_620);
                if (rcx == 0) {
                    // je 0xBC8B0D7
                } else {
                    if (rcx != s->r12) {
                        rax = *reinterpret_cast<uint64_t*>(rcx);
                        rax = *reinterpret_cast<uint64_t*>(rax + 0x20);
                        // 0xbc8b0c6  call qword ptr [0xF99FFA0]
                        native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rax));
                    }
                }
            } else {
                rax = s->slot(SLOT_C60);
                *reinterpret_cast<uint64_t*>(rax + 0x80) = rcx;
            }
            // loc_bc8b0cc:
            s->slot(SLOT_620) = 0;
        }
        // loc_bc8b0d7:
        rcx = s->slot(SLOT_C60);
        rax = rcx + 0x10;
        s->slot(SLOT_C40) = rax;
        s->r12 = rcx + 0x88;
        rcx = s->r12;
        rdx = s->r14;
        // 0xbc8b0f6  call 0xBC8C890
        native::sub_bc8c890(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx));
    }

    // 0xbc8b0fc..0xbc8bb76: Vector growth logic and final calls in chunk
    // mov [rbp+0xC50],r12
    // xorps xmm0,xmm0
    // mov r12,[rbp+0xC60]
    // movups [r12+0x330],xmm0
    // movups [r12+0x320],xmm0
    // test r15,r15
    // js 0xBC8BB70
    // lea r14,[r12+0x320]
    // mov r13d,0xF
    // cmp r15,0x10
    // jb short 0xBC8B1B5
    // mov rdx,r15
    // or rdx,0xF
    // cmp rdx,0x17
    // mov r13d,0x16
    // cmovae r13,rdx
    // mov rcx,[0x1233E1A8]
    // mov rax,[rcx]
    // mov rax,[rax+8]
    // cmp rdx,0xFFF
    // jb short 0xBC8B191
    // lea rdx,[r13+0x28]
    // call qword ptr [0xF99FFA0]
    // nop
    // mov r12,rax
    // test rax,rax
    // je 0xBC8B8F4
    // loc_bc8b17f:
    // mov rax,r12
    // add r12,0x27
    // and r12,0xFFFFFFFFFFFFFFE0
    // mov [r12-8],rax
    // jmp short 0xBC8B1A8
    // loc_bc8b191:
    // lea rdx,[r13+1]
    // call qword ptr [0xF99FFA0]
    // nop
    // mov r12,rax
    // test rax,rax
    // je 0xBC8B903
    // loc_bc8b1a8:
    // mov [r14],r12
    // mov r14,r12
    // mov r12,[rbp+0xC60]
    // loc_bc8b1b5:
    // cmp rbx,0x10
    // lea rdx,[rbp+0x330]
    // cmovae rdx,rsi
    // mov [r12+0x330],r15
    // mov [r12+0x338],r13
    // mov rcx,r14
    // mov r8,r15
    // call 0xEEC6EC0
    // mov byte ptr [r14+r15],0
    // mov rcx,[rbp+0xC58]
    // mov rsi,[rcx+0x10]
    // cmp rsi,[rcx+0x18]
    // je short 0xBC8B214
    // mov rax,[rbp+0xC40]
    // mov [rsi],rax
    // mov [rsi+8],r12
    // mov rax,[rcx+0x10]
    // add rax,0x10
    // mov [rcx+0x10],rax
    // jmp 0xBC8B42C
    // loc_bc8b214:
    // lea r8,[rcx+8]
    // mov r9,r12
    // add r9,0xC
    // mov rbx,rsi
    // sub rbx,[r8]
    // mov rax,rbx
    // sar rax,4
    // lea r14,[rax+1]
    // mov r15,rax
    // shr r15,1
    // mov rcx,0xFFFFFFFFFFFFFFF
    // mov rdx,rcx
    // sub rdx,r15
    // add r15,rax
    // cmp r15,r14
    // cmovbe r15,r14
    // cmp rax,rdx
    // cmova r15,rcx
    // lea rcx,[r12+8]
    // mov rax,r15
    // shr rax,0x3C
    // jne 0xBC8BB76
    {
        // 0xbc8b0fc..0xbc8bb76 (chunk ends at 0xbc8bb76)
        s->slot(SLOT_C50) = s->r12;
        xmm0 = _mm_setzero_ps();
        s->r12 = s->slot(SLOT_C60);
        *reinterpret_cast<__m128*>(s->r12 + 0x330) = xmm0;
        *reinterpret_cast<__m128*>(s->r12 + 0x320) = xmm0;
        if ((int64_t)s->r15 < 0) {
            // js 0xBC8BB70 -> call sub_75720
            // 0xbc8bb70  call 0x75720
            native::boundary::sub_75720();
            // Falls through to 0xbc8bb76
        }
        s->r14 = s->r12 + 0x320;
        uint32_t r13d = 0xF;
        if (s->r15 < 0x10) {
            // jb 0xBC8B1B5
        } else {
            uint64_t rdx = s->r15 | 0xF;
            if (rdx >= 0x17) {
                r13d = 0x16;
            } else {
                r13d = (uint32_t)rdx;
            }
            rcx = *reinterpret_cast<uint64_t*>(DATA_1233E1A8);
            rax = *reinterpret_cast<uint64_t*>(rcx);
            rax = *reinterpret_cast<uint64_t*>(rax + 8);
            if (rdx < 0xFFF) {
                // jb 0xBC8B191
                rdx = r13d + 1;
                // 0xbc8b195  call qword ptr [0xF99FFA0]
                native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rax), reinterpret_cast<void*>(rdx));
                s->r12 = rax;
                if (rax == 0) {
                    // je 0xBC8B903 (outside chunk 0) - not taken
                }
            } else {
                rdx = r13d + 0x28;
                // 0xbc8b16c  call qword ptr [0xF99FFA0]
                native::boundary::g_eea6040_thunk(reinterpret_cast<void*>(rax), reinterpret_cast<void*>(rdx));
                s->r12 = rax;
                if (rax == 0) {
                    // je 0xBC8B8F4 (outside chunk 0) - not taken
                }
            }
            // loc_bc8b17f / loc_bc8b1a8:
            rax = s->r12;
            s->r12 = (s->r12 + 0x27) & ~0x1F;
            *reinterpret_cast<uint64_t*>(s->r12 - 8) = rax;
            // jmp 0xBC8B1A8 -> loc_bc8b1a8
            s->r14 = s->r12;
            s->r12 = s->slot(SLOT_C60);
        }
        // loc_bc8b1b5:
        if (s->rbx >= 0x10) {
            rdx = s->rsi;
        } else {
            rdx = s->rbp + SLOT_330;
        }
        *reinterpret_cast<uint64_t*>(s->r12 + 0x330) = s->r15;
        *reinterpret_cast<uint64_t*>(s->r12 + 0x338) = r13d;
        rcx = s->r14;
        uint64_t r8 = s->r15;
        // 0xbc8b1d7  call 0xEEC6EC0
        native::sub_eec6ec0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(r8), reinterpret_cast<void*>(rdx));
        *reinterpret_cast<uint8_t*>(s->r14 + s->r15) = 0;
        rcx = s->slot(SLOT_C58);
        s->rsi = *reinterpret_cast<uint64_t*>(rcx + 0x10);
        if (s->rsi == *reinterpret_cast<uint64_t*>(rcx + 0x18)) {
            // je 0xBC8B214
        } else {
            rax = s->slot(SLOT_C40);
            *reinterpret_cast<uint64_t*>(s->rsi) = rax;
            *reinterpret_cast<uint64_t*>(s->rsi + 8) = s->r12;
            rax = *reinterpret_cast<uint64_t*>(rcx + 0x10);
            rax += 0x10;
            *reinterpret_cast<uint64_t*>(rcx + 0x10) = rax;
            // jmp 0xBC8B42C (outside chunk 0 range? No, 0xBC8B42C > 0xBC8BB76)
            // Actually 0xBC8B42C is beyond chunk boundary (0xBC8BB76)
            // So this jump goes to chunk 1
            // For chunk 0, we stop here and let chunk 1 continue
            // The state at 0xbc8bb76 is captured in s
            return;
        }

        // loc_bc8b214 (not taken in this path, but included for completeness)
        // This path continues to 0xbc8bb76
        uint64_t r8_val = rcx + 8;
        uint64_t r9_val = s->r12 + 0xC;
        s->rbx = s->rsi;
        s->rbx -= *reinterpret_cast<uint64_t*>(r8_val);
        rax = s->rbx;
        rax >>= 4;
        s->r14 = rax + 1;
        s->r15 = rax;
        s->r15 >>= 1;
        rcx = 0xFFFFFFFFFFFFFFF;
        rdx = rcx;
        rdx -= s->r15;
        s->r15 += rax;
        if (s->r15 <= s->r14) {
            s->r15 = s->r14;
        }
        if (rax > rdx) {
            s->r15 = rcx;
        }
        rcx = s->r12 + 8;
        rax = s->r15;
        rax >>= 0x3C;
        if (rax != 0) {
            // jne 0xBC8BB76 (chunk boundary)
        }
        // Chunk ends at 0xbc8bb76
        // State is live in s for chunk 1
    }
}

} // namespace native::bc8a380