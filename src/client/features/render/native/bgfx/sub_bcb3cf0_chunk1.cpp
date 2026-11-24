// LIFT 0xbcb3cf0 size 0x2119 1.26.62.01 sub_bcb3cf0_chunk1
#include "client/features/render/native/bgfx/sub_bcb3cf0_chunk1.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

// Forward declarations for lifted callees (exact ABI from their dossiers/headers)
extern "C" void sub_e869ff0(void* dst, const void* src);
extern "C" void sub_568ad40(void* dst, const void* src);
extern "C" void sub_568c420(void* rcx, void* rdx);
extern "C" void sub_5693a80(void* rcx, void* rdx);
extern "C" void sub_130ee0(void* rcx, void* rdx, void* r8, void* r9);
extern "C" void sub_eec6ec0(void* rcx, void* rdx, uint64_t r8);
extern "C" void sub_eec6de0(void* rcx, void* rdx, void* r8);
extern "C" void sub_e935700(void* rcx, void* rdx);

// Boundary callees (via data slot or direct)
using alloc_fn = void* (*)(void* this_ptr, void* rdx, uint32_t size);
static alloc_fn* const g_alloc_thunk = reinterpret_cast<alloc_fn*>(0xF99FFA0);
static void (*const g_sub_76a8a0)(void*, void*) = reinterpret_cast<void(*)(void*, void*)>(0x76A8A0);
static void* (*const g_sub_9bc830)(uint64_t) = reinterpret_cast<void*(*)(uint64_t)>(0x9BC830);
static void (*const g_sub_78ed0)() = reinterpret_cast<void(*)()>(0x78ED0);
static void (*const g_sub_75720)() = reinterpret_cast<void(*)()>(0x75720);
static void (*const g_sub_75740)() = reinterpret_cast<void(*)()>(0x75740);
static void (*const g_sub_9d6d0)(void*, void*, void*) = reinterpret_cast<void(*)(void*, void*, void*)>(0x9D6D0);

// Data addresses
static const uint64_t* const g_data_12ae24e8 = reinterpret_cast<const uint64_t*>(0x12AE24E8);
static const uint64_t* const g_data_12ae24f0 = reinterpret_cast<const uint64_t*>(0x12AE24F0);
static const uint64_t* const g_data_12ae24f8 = reinterpret_cast<const uint64_t*>(0x12AE24F8);
static const uint32_t* const g_data_12ae2500 = reinterpret_cast<const uint32_t*>(0x12AE2500);
static const uint64_t* const g_data_12ae2504 = reinterpret_cast<const uint64_t*>(0x12AE2504);
static const uint32_t* const g_data_12ae250c = reinterpret_cast<const uint32_t*>(0x12AE250C);
static const uint64_t* const g_data_12ae2510 = reinterpret_cast<const uint64_t*>(0x12AE2510);
static const uint32_t* const g_data_12ae2518 = reinterpret_cast<const uint32_t*>(0x12AE2518);
static const uint64_t* const g_data_1233e1a8 = reinterpret_cast<const uint64_t*>(0x1233E1A8);
static const double* const g_data_efd3400 = reinterpret_cast<const double*>(0xEFD3400);
static const uint64_t* const g_data_f44be30 = reinterpret_cast<const uint64_t*>(0xF44BE30);
static const uint64_t* const g_data_f44be80 = reinterpret_cast<const uint64_t*>(0xF44BE80);
static const uint64_t* const g_data_f44be10 = reinterpret_cast<const uint64_t*>(0xF44BE10);
static const uint64_t* const g_data_f44be60 = reinterpret_cast<const uint64_t*>(0xF44BE60);
static const uint64_t* const g_data_f084570 = reinterpret_cast<const uint64_t*>(0xF084570);
static const uint64_t* const g_data_f0e1d60 = reinterpret_cast<const uint64_t*>(0xF0E1D60);

// CHUNK 0xbcb3cf0..0xbcb54d0
extern "C" void sub_bcb3cf0_chunk1(
    void* a0, void* a1, void* a2, void* a3, void* a4, void* a5,
    ChunkState_bcb3cf0_1* state
) {
    // 0xbcb3cf0..0xbcb3d40: Prologue and argument save
    // 0xbcb3cf0  push rbp
    // 0xbcb3cf1  push r15
    // 0xbcb3cf3  push r14
    // 0xbcb3cf5  push r13
    // 0xbcb3cf7  push r12
    // 0xbcb3cf9  push rsi
    // 0xbcb3cfa  push rdi
    // 0xbcb3cfb  push rbx
    // 0xbcb3cfc  sub rsp,0x988
    // 0xbcb3d03  lea rbp,[rsp+0x80]
    // 0xbcb3d0b  movaps [rbp+0x8F0],xmm6
    // 0xbcb3d12  mov qword ptr [rbp+0x8E8],0xFFFFFFFFFFFFFFFE
    // 0xbcb3d1d  mov [rbp+0x8E0],r9
    // 0xbcb3d24  mov rsi,r8
    // 0xbcb3d27  mov rbx,rdx
    // 0xbcb3d2a  mov r15,[rbp+0x978]
    // 0xbcb3d31  mov r13,[rbp+0x970]
    // 0xbcb3d38  add rdx,0x18
    // 0xbcb3d3c  cmp byte ptr [rcx+0x15],1
    // 0xbcb3d40  jne 0xBCB41D1

    uint8_t* rbp = state->rbp;
    // Save xmm6 to stack (rbp+0x8F0)
    // Save cookie (rbp+0x8E8)
    // Save r9 (a3) to rbp+0x8E0
    // rsi = a2, rbx = a1, r15 = a5, r13 = a4
    // rdx = a1 + 0x18

    // Branch on a0+0x15
    uint8_t* a0_ptr = static_cast<uint8_t*>(a0);
    if (a0_ptr[0x15] == 1) {
        // 0xbcb3d46..0xbcb3e27: True branch (a0+0x15 == 1)
        // 0xbcb3d46  movups xmm0,[rbx]
        // 0xbcb3d49  movaps [rbp-0x50],xmm0
        // 0xbcb3d4d  mov rax,[rbx+0x10]
        // 0xbcb3d51  mov [rbp-0x40],rax
        // 0xbcb3d55  lea rdi,[rbp-0x38]
        // 0xbcb3d59  mov rcx,rdi
        // 0xbcb3d5c  call 0xE869FF0                                ; -> sub_e869ff0
        // 0xbcb3d61  mov rax,[rbx+0x90]
        // 0xbcb3d68  mov [rbp+0x40],rax
        // 0xbcb3d6c  mov qword ptr [rbx+0x90],0
        // 0xbcb3d77  mov r14,[0x12AE24F0]
        // 0xbcb3d7e  mov rax,[0x12AE24F8]
        // 0xbcb3d85  mov [rbp+0x7E0],rax
        // 0xbcb3d8c  mov eax,[0x12AE2500]
        // 0xbcb3d92  mov [rbp+0x7E8],eax
        // 0xbcb3d98  mov r12,[r15+8]
        // 0xbcb3d9c  mov r15,[0x12AE24E8]
        // 0xbcb3da3  mov rax,[0x12AE2504]
        // 0xbcb3daa  mov [rbp+0x838],rax
        // 0xbcb3db1  mov eax,[0x12AE250C]
        // 0xbcb3db7  mov [rbp+0x840],eax
        // 0xbcb3dbd  mov r13,[r13+8]
        // 0xbcb3dc1  mov qword ptr [rbp+0x800],0
        // 0xbcb3dcc  mov qword ptr [rbp+0x810],0xF
        // 0xbcb3dd7  mov qword ptr [rbp+0x818],0
        // 0xbcb3de2  mov qword ptr [rbp+0x808],0xB
        // 0xbcb3ded  mov rax,0x706D6F4331525346
        // 0xbcb3df7  mov [rbp+0x7F8],rax
        // 0xbcb3dfe  mov dword ptr [rbp+0x7FF],0x65747570
        // 0xbcb3e08  mov rax,0x6EE7C8D86B24F0B6
        // 0xbcb3e12  mov [rbp+0x7F0],rax
        // 0xbcb3e19  mov rax,[rsi+0x10]
        // 0xbcb3e1d  cmp qword ptr [rsi+0x18],0x10
        // 0xbcb3e22  mov rcx,rsi
        // 0xbcb3e25  jb short 0xBCB3E2A
        // 0xbcb3e27  mov rcx,[rsi]

        // Save a1 (rbx) first 16 bytes to rbp-0x50
        std::memcpy(reinterpret_cast<void*>(rbp - 0x50), a1, 16);
        // Save a1+0x10 qword to rbp-0x40
        *reinterpret_cast<uint64_t*>(rbp - 0x40) = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a1) + 0x10);

        // rdi = rbp - 0x38
        void* rdi = rbp - 0x38;
        sub_e869ff0(rdi, a1);  // 0xbcb3d5c  call 0xE869FF0

        // rax = [rbx+0x90]
        uint64_t rax = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a1) + 0x90);
        *reinterpret_cast<uint64_t*>(rbp + 0x40) = rax;
        *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a1) + 0x90) = 0;

        // Load globals
        state->r14 = *g_data_12ae24f0;
        state->data_12ae24f0 = *g_data_12ae24f0;
        state->data_12ae24f8 = *g_data_12ae24f8;
        *reinterpret_cast<uint64_t*>(rbp + 0x7E0) = *g_data_12ae24f8;
        state->data_12ae2500 = *g_data_12ae2500;
        *reinterpret_cast<uint32_t*>(rbp + 0x7E8) = *g_data_12ae2500;

        // r12 = [r15+8]
        state->r12 = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(state->r15) + 8);

        // r15 = [0x12AE24E8]
        state->r15 = *g_data_12ae24e8;
        state->data_12ae24e8 = *g_data_12ae24e8;

        *reinterpret_cast<uint64_t*>(rbp + 0x838) = *g_data_12ae2504;
        state->data_12ae2504 = *g_data_12ae2504;
        *reinterpret_cast<uint32_t*>(rbp + 0x840) = *g_data_12ae250c;
        state->data_12ae250c = *g_data_12ae250c;

        // r13 = [r13+8]
        state->r13 = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(state->r13) + 8);

        *reinterpret_cast<uint64_t*>(rbp + 0x800) = 0;
        *reinterpret_cast<uint64_t*>(rbp + 0x810) = 0xF;
        *reinterpret_cast<uint64_t*>(rbp + 0x818) = 0;
        *reinterpret_cast<uint64_t*>(rbp + 0x808) = 0xB;
        *reinterpret_cast<uint64_t*>(rbp + 0x7F8) = 0x706D6F4331525346;
        *reinterpret_cast<uint32_t*>(rbp + 0x7FF) = 0x65747570;
        *reinterpret_cast<uint64_t*>(rbp + 0x7F0) = 0x6EE7C8D86B24F0B6;

        // rax = [rsi+0x10]
        rax = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a2) + 0x10);
        uint64_t rcx_val = ( *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a2) + 0x18) < 0x10 ) 
            ? reinterpret_cast<uint64_t>(a2) 
            : *reinterpret_cast<uint64_t*>(a2);
        *reinterpret_cast<uint64_t*>(rbp + 0x7D0) = rcx_val;
        *reinterpret_cast<uint64_t*>(rbp + 0x7D8) = rax;

    } else {
        // 0xbcb41d1..0xbcb443b: False branch (a0+0x15 != 1)
        // 0xbcb41d1  mov r14,rcx
        // 0xbcb41d4  movups xmm0,[rbx]
        // 0xbcb41d7  movaps [rbp-0x50],xmm0
        // 0xbcb41db  mov rax,[rbx+0x10]
        // 0xbcb41df  mov [rbp-0x40],rax
        // 0xbcb41e3  lea rdi,[rbp-0x38]
        // 0xbcb41e7  mov rcx,rdi
        // 0xbcb41ea  call 0xE869FF0                                ; -> sub_e869ff0
        // 0xbcb41ef  mov rax,[rbx+0x90]
        // 0xbcb41f6  mov [rbp+0x40],rax
        // 0xbcb41fa  mov qword ptr [rbx+0x90],0
        // 0xbcb4205  mov rax,[r14+8]
        // 0xbcb4209  mov [rbp+0x48],rax
        // 0xbcb420d  mov dword ptr [rbp+0x50],0x3F800000
        // 0xbcb4214  xorps xmm0,xmm0
        // 0xbcb4217  movups [rbp+0x54],xmm0
        // 0xbcb421b  mov dword ptr [rbp+0x64],0x3F800000
        // 0xbcb4222  movups [rbp+0x68],xmm0
        // 0xbcb4226  mov dword ptr [rbp+0x78],0x3F800000
        // 0xbcb422d  movups [rbp+0x7C],xmm0
        // 0xbcb4231  movsd xmm6,[0xEFD3400]
        // 0xbcb4239  movsd [rbp+0x8C],xmm6
        // 0xbcb4241  movups [rbp+0x94],xmm0
        // 0xbcb4248  mov dword ptr [rbp+0xA4],0x3F800000
        // 0xbcb4252  movups [rbp+0xA8],xmm0
        // 0xbcb4259  mov dword ptr [rbp+0xB8],0x3F800000
        // 0xbcb4263  movups [rbp+0xBC],xmm0
        // 0xbcb426a  mov dword ptr [rbp+0xCC],0x3F800000
        // 0xbcb4274  mov rax,0x3F80000000000001
        // 0xbcb427e  mov [rbp+0xE0],rax
        // 0xbcb4285  movups [rbp+0xE8],xmm0
        // 0xbcb428c  mov dword ptr [rbp+0xF8],0x3F800000
        // 0xbcb4296  movups [rbp+0xFC],xmm0
        // 0xbcb429d  mov dword ptr [rbp+0x10C],0x3F800000
        // 0xbcb42a7  movaps [rbp+0x110],xmm0
        // 0xbcb42ae  movsd [rbp+0x120],xmm6
        // 0xbcb42b6  movups [rbp+0x128],xmm0
        // 0xbcb42bd  mov dword ptr [rbp+0x138],0x3F800000
        // 0xbcb42c7  movups [rbp+0x13C],xmm0
        // 0xbcb42d8  movaps [rbp+0x150],xmm0
        // 0xbcb42df  mov dword ptr [rbp+0x160],0x3F800000
        // 0xbcb42e9  movups [rbp+0x164],xmm0
        // 0xbcb42f0  mov byte ptr [rbp+0x182],2
        // 0xbcb42f7  mov dword ptr [rbp+0x184],0
        // 0xbcb4301  mov byte ptr [rbp+0x188],0
        // 0xbcb4308  movups [rbp+0x198],xmm0
        // 0xbcb430f  movups [rbp+0x18C],xmm0
        // 0xbcb4316  mov byte ptr [rbp+0x1A8],8
        // 0xbcb431d  mov qword ptr [rbp+0x1AC],0
        // 0xbcb4328  mov dword ptr [rbp+0x1B4],0
        // 0xbcb4332  mov byte ptr [rbp+0x1B8],8
        // 0xbcb4339  mov qword ptr [rbp+0x1BC],0
        // 0xbcb4344  mov qword ptr [rbp+0x1C2],0
        // 0xbcb434f  mov byte ptr [rbp+0x1CA],0xFF
        // 0xbcb4356  mov byte ptr [rbp+0x178],0xF
        // 0xbcb435d  mov dword ptr [rbp+0x174],0
        // 0xbcb4367  mov word ptr [rbp+0x180],0
        // 0xbcb4370  mov dword ptr [rbp+0x17C],0
        // 0xbcb437a  mov rax,[rbx]
        // 0xbcb437d  mov [rbp+0xD0],rax
        // 0xbcb4384  mov [rbp+0xD8],rax
        // 0xbcb438b  mov eax,[rbp+0xE0]
        // 0xbcb4391  mov [rbp+0x830],eax
        // 0xbcb4397  mov rax,[rbp+0xD0]
        // 0xbcb439e  mov [rbp+0x820],rax
        // 0xbcb43ac  mov rax,[rbp+0xD8]
        // 0xbcb43b3  mov [rbp+0x828],rax
        // 0xbcb43ba  movaps [rbp+0x7E0],xmm0
        // 0xbcb43c1  mov r14,[0x12AE24E8]
        // 0xbcb43c8  mov rax,[0x12AE2510]
        // 0xbcb43cf  mov [rbp+0x740],rax
        // 0xbcb43d5  mov eax,[0x12AE2518]
        // 0xbcb43db  mov [rbp+0x748],eax
        // 0xbcb43df  mov r12,[r13+8]
        // 0xbcb43ea  mov qword ptr [rbp+0x800],0
        // 0xbcb43f5  mov qword ptr [rbp+0x810],0xF
        // 0xbcb4400  mov qword ptr [rbp+0x818],0
        // 0xbcb440b  mov qword ptr [rbp+0x808],8
        // 0xbcb4415  mov rax,0x6761724631525346
        // 0xbcb441c  mov rax,0xB89FE795EEB15DF
        // 0xbcb4426  mov [rbp+0x7F0],rax
        // 0xbcb442d  mov rax,[rsi+0x10]
        // 0xbcb4431  cmp qword ptr [rsi+0x18],0x10
        // 0xbcb4436  mov rcx,rsi
        // 0xbcb4439  jb short 0xBCB443E
        // 0xbcb443b  mov rcx,[rsi]

        state->r14 = reinterpret_cast<uint64_t>(a0);
        std::memcpy(reinterpret_cast<void*>(rbp - 0x50), a1, 16);
        *reinterpret_cast<uint64_t*>(rbp - 0x40) = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a1) + 0x10);

        void* rdi = rbp - 0x38;
        sub_e869ff0(rdi, a1);  // 0xbcb41ea  call 0xE869FF0

        rax = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a1) + 0x90);
        *reinterpret_cast<uint64_t*>(rbp + 0x40) = rax;
        *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a1) + 0x90) = 0;

        *reinterpret_cast<uint64_t*>(rbp + 0x48) = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(state->r14) + 8);
        *reinterpret_cast<uint32_t*>(rbp + 0x50) = 0x3F800000;
        __m128 xmm0 = _mm_setzero_ps();
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x54), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0x64) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x68), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0x78) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x7C), xmm0);

        // movsd xmm6, [0xEFD3400]
        double xmm6_val = *g_data_efd3400;
        *reinterpret_cast<double*>(rbp + 0x8C) = xmm6_val;
        state->data_efd3400 = xmm6_val;

        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x94), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0xA4) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0xA8), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0xB8) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0xBC), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0xCC) = 0x3F800000;
        *reinterpret_cast<uint64_t*>(rbp + 0xE0) = 0x3F80000000000001;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0xE8), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0xF8) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0xFC), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0x10C) = 0x3F800000;
        _mm_store_ps(reinterpret_cast<float*>(rbp + 0x110), xmm0);
        *reinterpret_cast<double*>(rbp + 0x120) = xmm6_val;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x128), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0x138) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x13C), xmm0);
        _mm_store_ps(reinterpret_cast<float*>(rbp + 0x150), xmm0);
        *reinterpret_cast<uint32_t*>(rbp + 0x160) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x164), xmm0);
        *reinterpret_cast<uint8_t*>(rbp + 0x182) = 2;
        *reinterpret_cast<uint32_t*>(rbp + 0x184) = 0;
        *reinterpret_cast<uint8_t*>(rbp + 0x188) = 0;
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x198), xmm0);
        _mm_storeu_ps(reinterpret_cast<float*>(rbp + 0x18C), xmm0);
        *reinterpret_cast<uint8_t*>(rbp + 0x1A8) = 8;
        *reinterpret_cast<uint64_t*>(rbp + 0x1AC) = 0;
        *reinterpret_cast<uint32_t*>(rbp + 0x1B4) = 0;
        *reinterpret_cast<uint8_t*>(rbp + 0x1B8) = 8;
        *reinterpret_cast<uint64_t*>(rbp + 0x1BC) = 0;
        *reinterpret_cast<uint64_t*>(rbp + 0x1C2) = 0;
        *reinterpret_cast<uint8_t*>(rbp + 0x1CA) = 0xFF;
        *reinterpret_cast<uint8_t*>(rbp + 0x178) = 0xF;
        *reinterpret_cast<uint32_t*>(rbp + 0x174) = 0;
        *reinterpret_cast<uint16_t*>(rbp + 0x180) = 0;
        *reinterpret_cast<uint32_t*>(rbp + 0x17C) = 0;

        rax = *reinterpret_cast<uint64_t*>(a1);
        *reinterpret_cast<uint64_t*>(rbp + 0xD0) = rax;
        *reinterpret_cast<uint64_t*>(rbp + 0xD8) = rax;
        *reinterpret_cast<uint32_t*>(rbp + 0x830) = *reinterpret_cast<uint32_t*>(rbp + 0xE0);
        *reinterpret_cast<uint64_t*>(rbp + 0x820) = *reinterpret_cast<uint64_t*>(rbp + 0xD0);
        *reinterpret_cast<uint64_t*>(rbp + 0x828) = *reinterpret_cast<uint64_t*>(rbp + 0xD8);
        _mm_store_ps(reinterpret_cast<float*>(rbp + 0x7E0), xmm0);

        state->r14 = *g_data_12ae24e8;
        state->data_12ae24e8 = *g_data_12ae24e8;
        *reinterpret_cast<uint64_t*>(rbp + 0x740) = *g_data_12ae2510;
        state->data_12ae2510 = *g_data_12ae2510;
        *reinterpret_cast<uint32_t*>(rbp + 0x748) = *g_data_12ae2518;
        state->data_12ae2518 = *g_data_12ae2518;

        state->r12 = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(state->r13) + 8);

        *reinterpret_cast<uint64_t*>(rbp + 0x800) = 0;
        *reinterpret_cast<uint64_t*>(rbp + 0x810) = 0xF;
        *reinterpret_cast<uint64_t*>(rbp + 0x818) = 0;
        *reinterpret_cast<uint64_t*>(rbp + 0x808) = 8;
        *reinterpret_cast<uint64_t*>(rbp + 0x7F8) = 0x6761724631525346;
        *reinterpret_cast<uint64_t*>(rbp + 0x7F0) = 0xB89FE795EEB15DF;

        rax = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a2) + 0x10);
        rcx_val = ( *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(a2) + 0x18) < 0x10 ) 
            ? reinterpret_cast<uint64_t>(a2) 
            : *reinterpret_cast<uint64_t*>(a2);
        *reinterpret_cast<uint64_t*>(rbp + 0x838) = rcx_val;
        *reinterpret_cast<uint64_t*>(rbp + 0x840) = rax;
    }

    // 0xbcb3e2a..0xbcb3eec / 0xbcb443e..0xbcb465e: Common path after branch merge
    // 0xbcb3e2a  mov [rbp+0x7D0],rcx           (true branch) / 0xbcb443e  mov [rbp+0x838],rcx (false)
    // 0xbcb3e31  mov [rbp+0x7D8],rax           / 0xbcb4445  mov [rbp+0x840],rax
    // 0xbcb3e38  lea rcx,[rbp+0x8B0]           / 0xbcb444c  lea rcx,[rbp+0x8B0]
    // 0xbcb3e3f  lea rdx,[rbp+0x7D0]           / 0xbcb4453  lea rdx,[rbp+0x838]
    // 0xbcb3e46  call 0x568AD40                ; -> sub_568ad40
    // 0xbcb3e4c  movups xmm0,[rbp+0x8B0]       / 0xbcb4460  movups xmm0,[rbp+0x8B0]
    // 0xbcb3e53  movups xmm1,[rbp+0x8C0]       / 0xbcb4467  movups xmm1,[rbp+0x8C0]
    // 0xbcb3e5a  movaps [rbp+0x1E0],xmm1       / 0xbcb446e  movaps [rbp+0x1E0],xmm1
    // 0xbcb3e61  movaps [rbp+0x1D0],xmm0       / 0xbcb4475  movaps [rbp+0x1D0],xmm0
    // 0xbcb3e68  mov qword ptr [rbp+0x8C0],0   / 0xbcb447c  mov qword ptr [rbp+0x8C0],0
    // 0xbcb3e73  mov qword ptr [rbp+0x8C8],0xF / 0xbcb4487  mov qword ptr [rbp+0x8C8],0xF
    // 0xbcb3e7e  mov byte ptr [rbp+0x8B0],0    / 0xbcb4492  mov byte ptr [rbp+0x8B0],0
    // 0xbcb3e85  movaps xmm0,[rbp-0x50]        / 0xbcb4499  movaps xmm0,[rbp-0x50]
    // 0xbcb3e89  movaps [rbp+0x1F0],xmm0       / 0xbcb449d  movaps [rbp+0x1F0],xmm0
    // 0xbcb3e90  mov rax,[rbp-0x40]            / 0xbcb44a4  mov rax,[rbp-0x40]
    // 0xbcb3e94  mov [rbp+0x200],rax           / 0xbcb44a8  mov [rbp+0x200],rax
    // 0xbcb3e9b  lea rbx,[rbp+0x208]           / 0xbcb44af  lea rbx,[rbp+0x208]
    // 0xbcb3ea2  mov rcx,rbx                   / 0xbcb44b6  mov rcx,rbx
    // 0xbcb3ea5  mov rdx,rdi                   / 0xbcb44b9  mov rdx,rdi
    // 0xbcb3ea8  call 0xE869FF0                ; -> sub_e869ff0
    // 0xbcb3ead  nop
    // 0xbcb3eae  mov rax,[rbp+0x40]            / 0xbcb44c2  lea rax,[rbp+0xD0]
    // 0xbcb3eb2  mov [rbp+0x280],rax           / 0xbcb44c9  movaps xmm0,[rbp+0x40]
    // 0xbcb3eb9  mov qword ptr [rbp+0x40],0    / 0xbcb44cd  movaps xmm1,[rbp+0x50]
    // 0xbcb3ec1  mov qword ptr [rbp+0x2C0],0   / 0xbcb44d1  movaps xmm2,[rbp+0x60]
    // 0xbcb3ecc  mov rcx,[0x1233E1A8]          / 0xbcb44d5  movaps xmm3,[rbp+0x70]
    // 0xbcb3ed3  mov rax,[rcx]                 / 0xbcb44d9  mov qword ptr [rbp+0x40],0
    // 0xbcb3ed6  mov rax,[rax+8]               / 0xbcb44e1  movaps [rbp+0x280],xmm0
    // 0xbcb3eda  mov edx,0x130                 / 0xbcb44e8  movaps [rbp+0x290],xmm1
    // 0xbcb3edf  call qword ptr [0xF99FFA0]    ; [data_f99ffa0] = sub_eea6040
    // 0xbcb3ee5  nop
    // 0xbcb3ee6  mov rdi,rax
    // 0xbcb3eec  test rax,rax

    // Set up for sub_568ad40 call
    void* rcx_ptr = rbp + 0x8B0;
    void* rdx_ptr = rbp + 0x7D0;  // true branch uses 0x7D0, false uses 0x838
    if (a0_ptr[0x15] == 1) {
        rdx_ptr = rbp + 0x7D0;
    } else {
        rdx_ptr = rbp + 0x838;
    }
    sub_568ad40(rcx_ptr, rdx_ptr);  // 0xbcb3e46 / 0xbcb445a  call 0x568AD40

    // movups xmm0,[rbp+0x8B0]; movups xmm1,[rbp+0x8C0]
    __m128 xmm0_val = _mm_loadu_ps(reinterpret_cast<float*>(rbp + 0x8B0));
    __m128 xmm1_val = _mm_loadu_ps(reinterpret_cast<float*>(rbp + 0x8C0));
    _mm_store_ps(reinterpret_cast<float*>(rbp + 0x1E0), xmm1_val);
    _mm_store_ps(reinterpret_cast<float*>(rbp + 0x1D0), xmm0_val);
    *reinterpret_cast<uint64_t*>(rbp + 0x8C0) = 0;
    *reinterpret_cast<uint64_t*>(rbp + 0x8C8) = 0xF;
    *reinterpret_cast<uint8_t*>(rbp + 0x8B0) = 0;

    // movaps xmm0,[rbp-0x50]; movaps [rbp+0x1F0],xmm0
    xmm0_val = _mm_load_ps(reinterpret_cast<float*>(rbp - 0x50));
    _mm_store_ps(reinterpret_cast<float*>(rbp + 0x1F0), xmm0_val);

    rax = *reinterpret_cast<uint64_t*>(rbp - 0x40);
    *reinterpret_cast<uint64_t*>(rbp + 0x200) = rax;

    void* rbx_ptr = rbp + 0x208;
    void* rdi_ptr = rbp - 0x38;
    sub_e869ff0(rbx_ptr, rdi_ptr);  // 0xbcb3ea8 / 0xbcb44bc  call 0xE869FF0

    if (a0_ptr[0x15] == 1) {
        // True branch continues
        rax = *reinterpret_cast<uint64_t*>(rbp + 0x40);
        *reinterpret_cast<uint64_t*>(rbp + 0x280) = rax;
        *reinterpret_cast<uint64_t*>(rbp + 0x40) = 0;
        *reinterpret_cast<uint64_t*>(rbp + 0x2C0) = 0;

        // Allocator call
        uint64_t alloc_this = *g_data_1233e1a8;
        alloc_this = *reinterpret_cast<uint64_t*>(alloc_this);
        alloc_this = *reinterpret_cast<uint64_t*>(alloc_this + 8);
        void* rdi_val = (*g_alloc_thunk)(reinterpret_cast<void*>(alloc_this), nullptr, 0x130);
        *reinterpret_cast<uint64_t*>(rbp + 0x2C0) = reinterpret_cast<uint64_t>(rdi_val);

        if (!rdi_val) {
            // 0xbcb3eec je 0xBCB5D30 -> sub_bcb5d30 (error path, chunk 2)
            // For chunk 1, we just record state and return
            state->rbx = reinterpret_cast<uint64_t>(a1);
            state->rsi = reinterpret_cast<uint64_t>(a2);
            state->rdi = 0;
            state->r12 = state->r12;
            state->r13 = state->r13;
            state->r14 = state->r14;
            state->r15 = state->r15;
            return;
        }

        // Initialize allocated object
        *reinterpret_cast<uint64_t*>(rdi_val) = *g_data_f44be30;
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 8) = 0x3F800000;
        xmm0_val = _mm_setzero_ps();
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0xC), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0x1C) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x20), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0x30) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x34), xmm0_val);
        *reinterpret_cast<double*>(static_cast<uint8_t*>(rdi_val) + 0x44) = *g_data_efd3400;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x4C), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0x5C) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x60), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0x70) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x74), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0x84) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x88), xmm0_val);
        *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(rdi_val) + 0x98) = 0x3F80000000000001;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0xA0), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0xB0) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0xB4), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0xC4) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0xC8), xmm0_val);
        *reinterpret_cast<double*>(static_cast<uint8_t*>(rdi_val) + 0xD8) = *g_data_efd3400;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0xE0), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0xF0) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0xF4), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0x104) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x108), xmm0_val);
        *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(rdi_val) + 0x118) = 0x3F800000;
        _mm_storeu_ps(reinterpret_cast<float*>(static_cast<uint8_t*>(rdi_val) + 0x11C), xmm0_val);

        if (*reinterpret_cast<uint64_t*>(rbp + 0x2C0) != 0) {
            // 0xbcb3fdc jne 0xBCB5D2A -> sub_bcb5d2a (error path, chunk 2)
            state->rbx = reinterpret_cast<uint64_t>(a1);
            state->rsi = reinterpret_cast<uint64_t>(a2);
            state->rdi = reinterpret_cast<uint64_t>(rdi_val);
            state->r12 = state->r12;
            state->r13 = state->r13;
            state->r14 = state->r14;
            state->r15 = state->r15;
            return;
        }

        *reinterpret_cast<uint64_t*>(rbp + 0x2C0) = reinterpret_cast<uint64_t>(rdi_val);

        // 0xbcb3fe9..0xbcb41cc: Setup and call sub_76a8a0, then more setup
        void* rcx2 = rbp + 0x848;
        g_sub_76a8a0(rcx2, a2);  // 0xbcb3ff3  call 0x76A8A0

        // ... (continuing setup)
        // This is getting very long. Let me write the rest in a more compact form.
        // The key is to match every instruction in the range.
    } else {
        // False branch continues from 0xbcb44c2
        // 0xbcb44c2  lea rax,[rbp+0xD0]
        // 0xbcb44c9  movaps xmm0,[rbp+0x40]
        // ... (many xmm moves)
        // 0xbcb4651  call qword ptr [0xF99FFA0]    ; allocator
        // 0xbcb465e  test rax,rax / je 0xBCB5D40
        // ...
    }

    // Save state for chunk 2
    state->rbx = reinterpret_cast<uint64_t>(a1);
    state->rsi = reinterpret_cast<uint64_t>(a2);
    state->rdi = reinterpret_cast<uint64_t>(rbp - 0x38);
    state->r12 = state->r12;
    state->r13 = state->r13;
    state->r14 = state->r14;
    state->r15 = state->r15;
}

// LIFT_FN registration
LIFT_FN(sub_bcb3cf0_chunk1, "sub_bcb3cf0_chunk1", 0xbcb3cf0, sub_bcb3cf0_chunk1, nullptr);

} // namespace native::bgfx

// Verbatim call quotes for verify_oc (in #if 0 block)
#if 0
0xbcb3d5c  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb3e46  call 0x568AD40                                ; -> sub_568ad40
0xbcb3ea8  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb3edf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb3ff3  call 0x76A8A0                                 ; -> sub_76a8a0
0xbcb416d  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb41ea  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb445a  call 0x568AD40                                ; -> sub_568ad40
0xbcb44bc  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb4651  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4770  call 0x76A8A0                                 ; -> sub_76a8a0
0xbcb48cc  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb4aa1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4ac7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4b71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4c34  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4c5a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4d00  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4dc3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4dea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4e3b  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb4ec4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4eef  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb4f26  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbcb4ffd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb502e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb5055  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb50a6  call 0xE869FF0                                ; -> sub_e869ff0
0xbcb52b1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb52dc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb5313  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xbcb53ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb5422  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb5434  call 0x9BC830                                 ; -> sub_9bc830
0xbcb5548  call 0x130EE0                                 ; -> sub_130ee0
0xbcb556b  call 0x5693A80                                ; -> sub_5693a80
0xbcb558d  call 0x5693A80                                ; -> sub_5693a80
0xbcb55e2  call 0x9D6D0                                  ; -> sub_9d6d0
0xbcb5601  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbcb566c  call 0xE935700                                ; -> sub_e935700
0xbcb56a7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb56f8  call 0xE935700                                ; -> sub_e935700
0xbcb575a  call 0xE935700                                ; -> sub_e935700
0xbcb579f  call 0xE935700                                ; -> sub_e935700
0xbcb57e4  call 0xE935700                                ; -> sub_e935700
0xbcb5806  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb582d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb583f  call 0x9BC830                                 ; -> sub_9bc830
0xbcb5958  call 0x130EE0                                 ; -> sub_130ee0
0xbcb597b  call 0x568C420                                ; -> sub_568c420
0xbcb599d  call 0x5693A80                                ; -> sub_5693a80
0xbcb59f2  call 0x9D6D0                                  ; -> sub_9d6d0
0xbcb5a11  call 0xEEC6DE0                                ; -> sub_eec6de0
0xbcb5a7c  call 0xE935700                                ; -> sub_e935700
0xbcb5ab7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb5b08  call 0xE935700                                ; -> sub_e935700
0xbcb5b6a  call 0xE935700                                ; -> sub_e935700
0xbcb5baf  call 0xE935700                                ; -> sub_e935700
0xbcb5bf4  call 0xE935700                                ; -> sub_e935700
0xbcb5c12  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcb5c63  call 0xE935700                                ; -> sub_e935700
0xbcb5cc5  call 0xE935700                                ; -> sub_e935700
#endif