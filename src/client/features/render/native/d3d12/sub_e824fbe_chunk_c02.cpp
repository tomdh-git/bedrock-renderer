// LIFT 0xe824fbe size 0x8525 1.26.62.01 sub_e824fbe
// CHUNK 0xe827fa3..0xe8297a2
#include "client/features/render/native/d3d12/sub_e824fbe_chunk_c02.h"

#if 0
0xe827fad  call 0x47E8F0
0xe82813e  call 0x47E8F0
0xe8281b9  call 0x47E8F0
0xe82821d  call 0x47E8F0
0xe8282a0  call 0x47E8F0
0xe82832c  call 0x47E8F0
0xe828661  call 0x47E8F0
0xe828983  call 0x47E8F0
0xe828a03  call 0x47E8F0
0xe828d30  call 0x47E8F0
0xe828d94  call 0x47E8F0
0xe828e0f  call 0x47E8F0
0xe828fb3  call 0x47E8F0
0xe82902e  call 0x47E8F0
0xe829088  call 0x47E8F0
0xe8290e2  call 0x47E8F0
0xe82913c  call 0x47E8F0
0xe82919c  call 0x47E8F0
0xe8291fc  call 0x47E8F0
0xe829256  call 0x47E8F0
0xe8292b0  call 0x47E8F0
0xe82930a  call 0x47E8F0
0xe829364  call 0x47E8F0
0xe8293be  call 0x47E8F0
0xe829418  call 0x47E8F0
0xe829472  call 0x47E8F0
0xe8294cc  call 0x47E8F0
0xe829526  call 0x47E8F0
0xe82953a  call 0xEEC6ED0
0xe829562  call 0xEEC6ED0
0xe829594  call 0xEEC6ED0
0xe8295c6  call 0xEEC6ED0
0xe8295f5  call 0xEEC6ED0
0xe829627  call 0xEEC6ED0
0xe82964f  call 0xEEC6ED0
0xe82968e  call 0xEEC6ED0
0xe8296b6  call 0xEEC6ED0
0xe8296ed  call 0xEEC6ED0
0xe829715  call 0xEEC6ED0
0xe829747  call 0xEEC6ED0
0xe829779  call 0xEEC6ED0
#endif

namespace native {
namespace d3d12 {

// Forward declarations for boundary callees (from native_boundary.tsv)
// 0x47E8F0: STL vector grow/check - class=stl
// 0xEEC6ED0: CRT import thunk (jmp qword ptr [IAT]) - class=crt
extern "C" void sub_47e8f0(void* rcx, void* rdx, void* r8);     // 0x47e8f0 (STL)
extern "C" void sub_eec6ed0(void* rcx, void* rdx);                // 0xeec6ed0 (CRT)

// Data slot addresses (constants loaded via RIP-relative)
static constexpr uintptr_t kData_F441630 = 0xF441630;
static constexpr uintptr_t kData_F08ED30 = 0xF08ED30;
static constexpr uintptr_t kData_EF40DE0 = 0xEF40DE0;
static constexpr uintptr_t kData_F441650 = 0xF441650;
static constexpr uintptr_t kData_EFD3400 = 0xEFD3400;

// Helper to access rbx-frame slots
inline uint8_t* rbx_ptr(void* rbx, ptrdiff_t off) { return static_cast<uint8_t*>(rbx) + off; }
inline uint64_t& slot64(void* rbx, ptrdiff_t off) { return *reinterpret_cast<uint64_t*>(rbx_ptr(rbx, off)); }
inline uint32_t& slot32(void* rbx, ptrdiff_t off) { return *reinterpret_cast<uint32_t*>(rbx_ptr(rbx, off)); }
inline uint16_t& slot16(void* rbx, ptrdiff_t off) { return *reinterpret_cast<uint16_t*>(rbx_ptr(rbx, off)); }
inline __m128& slot128(void* rbx, ptrdiff_t off) { return *reinterpret_cast<__m128*>(rbx_ptr(rbx, off)); }
inline const __m128& cslot128(const void* rbx, ptrdiff_t off) { return *reinterpret_cast<const __m128*>(static_cast<const uint8_t*>(rbx) + off); }

// 0xe827fa3..0xe8297a2
static inline void sub_e824fbe_chunk_c02(ChunkState_e824fbe_c02& s) {
    // Unpack state
    void* rbx = s.rbx;
    void* rbp = s.rbp;
    uint64_t rcx = s.rcx;
    uint64_t rsi = s.rsi;
    uint64_t rdi = s.rdi;
    uint64_t rax = s.rax;
    uint64_t rdx = s.rdx;
    uint64_t r13 = s.r13;
    uint64_t r15 = s.r15;
    unsigned char al = s.al_flags;

    // -------------------------------------------------------------------------
    // 0xe827fa3..0xe827fb3: Initial STL bounds check on r13 against rbx+0x3B0
    // 0xe827fa3  mov rcx,r13
    // 0xe827fa6  lea r8,[rbx+0x3B0]
    // 0xe827fad  call 0x47E8F0                                ; -> sub_47e8f0 (STL)
    // 0xe827fb2  nop
    // 0xe827fb3  jmp 0xE8297B7                                 ; -> loc_e8297b7 (outside chunk)
    // -------------------------------------------------------------------------
    // 0xe827fa3..0xe827fb3
    rcx = r13;
    sub_47e8f0(reinterpret_cast<void*>(rcx), rbx_ptr(rbx, 0x3B0), nullptr);
    // jmp 0xE8297B7 - not taken in this chunk (target is outside our range)
    // The rest of the chunk is reached via multiple entry points from earlier chunks

    // -------------------------------------------------------------------------
    // 0xe827fb8..0xe828019: First matrix row computation (rbx+0x3B0)
    // Loads matrix from [rbx+0x2F8 + rcx*0x40] where rcx = [rbx+0x1B0]+8 << 6
    // Multiplies by constant matrix at [rbx+0x2F0] (4 rows at +0, +0x10, +0x20, +0x30)
    // -------------------------------------------------------------------------
    // 0xe827fb8..0xe827fcd
    rcx = slot64(rbx, 0x1B0);          // 0xe827fb8  mov rcx,[rbx+0x1B0]
    rcx = slot64(rbx, 0x1B0 + 8);      // 0xe827fbf  mov ecx,[rcx+8] (load 32-bit, zero-extend)
    rcx <<= 6;                          // 0xe827fc2  shl rcx,6
    rdx = slot64(rbx, 0x2F8);          // 0xe827fc6  mov rdx,[rbx+0x2F8]
    // 0xe827fcd  movaps xmm4,[rdx+rcx]                    ; load matrix row 0
    __m128 xmm4 = cslot128(rdx, rcx);
    __m128 xmm5 = xmm4;                // 0xe827fd1  movaps xmm5,xmm4
    xmm5 = _mm_shuffle_ps(xmm5, xmm4, 0x00);  // 0xe827fd4  shufps xmm5,xmm4,0
    __m128 xmm6 = xmm4;                // 0xe827fd8  movaps xmm6,xmm4
    xmm6 = _mm_shuffle_ps(xmm6, xmm4, 0x55);  // 0xe827fdb  shufps xmm6,xmm4,0x55
    __m128 xmm7 = xmm4;                // 0xe827fdf  movaps xmm7,xmm4
    xmm7 = _mm_shuffle_ps(xmm7, xmm4, 0xAA);  // 0xe827fe2  shufps xmm7,xmm4,0xAA
    xmm4 = _mm_shuffle_ps(xmm4, xmm4, 0xFF);  // 0xe827fe6  shufps xmm4,xmm4,0xFF

    // 0xe827fea  mov r8,[rbx+0x2F0]                             ; constant matrix base
    r8 = slot64(rbx, 0x2F0);
    __m128 xmm3 = cslot128(r8, 0);     // 0xe827ff1  movaps xmm3,[r8]
    __m128 xmm2 = cslot128(r8, 0x10);  // 0xe827ff5  movaps xmm2,[r8+0x10]
    __m128 xmm1 = cslot128(r8, 0x20);  // 0xe827ffa  movaps xmm1,[r8+0x20]
    __m128 xmm0 = cslot128(r8, 0x30);  // 0xe827fff  movaps xmm0,[r8+0x30]

    // 0xe828004..0xe828019: multiply-accumulate
    xmm5 = _mm_mul_ps(xmm5, xmm3);     // 0xe828004  mulps xmm5,xmm3
    xmm6 = _mm_mul_ps(xmm6, xmm2);     // 0xe828007  mulps xmm6,xmm2
    xmm7 = _mm_mul_ps(xmm7, xmm1);     // 0xe82800a  mulps xmm7,xmm1
    xmm7 = _mm_add_ps(xmm7, xmm5);     // 0xe82800d  addps xmm7,xmm5
    xmm4 = _mm_mul_ps(xmm4, xmm0);     // 0xe828010  mulps xmm4,xmm0
    xmm4 = _mm_add_ps(xmm4, xmm6);     // 0xe828013  addps xmm4,xmm6
    xmm4 = _mm_add_ps(xmm4, xmm7);     // 0xe828016  addps xmm4,xmm7
    // 0xe828019  movaps [rbx+0x3B0],xmm4                        ; store result row 0
    slot128(rbx, 0x3B0) = xmm4;

    // -------------------------------------------------------------------------
    // 0xe828020..0xe828053: Second matrix row (rbx+0x3C0) - same pattern at +0x10
    // -------------------------------------------------------------------------
    // 0xe828020  movaps xmm4,[rdx+rcx+0x10]
    xmm4 = cslot128(rdx, rcx + 0x10);
    xmm5 = xmm4;                        // 0xe828025  movaps xmm5,xmm4
    xmm5 = _mm_shuffle_ps(xmm5, xmm4, 0x00);  // 0xe828028  shufps xmm5,xmm4,0
    xmm6 = xmm4;                        // 0xe82802c  movaps xmm6,xmm4
    xmm6 = _mm_shuffle_ps(xmm6, xmm4, 0x55);  // 0xe82802f  shufps xmm6,xmm4,0x55
    xmm7 = xmm4;                        // 0xe828033  movaps xmm7,xmm4
    xmm7 = _mm_shuffle_ps(xmm7, xmm4, 0xAA);  // 0xe828036  shufps xmm7,xmm4,0xAA
    xmm4 = _mm_shuffle_ps(xmm4, xmm4, 0xFF);  // 0xe82803a  shufps xmm4,xmm4,0xFF

    xmm5 = _mm_mul_ps(xmm5, xmm3);     // 0xe82803e  mulps xmm5,xmm3
    xmm6 = _mm_mul_ps(xmm6, xmm2);     // 0xe828041  mulps xmm6,xmm2
    xmm7 = _mm_mul_ps(xmm7, xmm1);     // 0xe828044  mulps xmm7,xmm1
    xmm7 = _mm_add_ps(xmm7, xmm5);     // 0xe828047  addps xmm7,xmm5
    xmm4 = _mm_mul_ps(xmm4, xmm0);     // 0xe82804a  mulps xmm4,xmm0
    xmm4 = _mm_add_ps(xmm4, xmm6);     // 0xe82804d  addps xmm4,xmm6
    xmm4 = _mm_add_ps(xmm4, xmm7);     // 0xe828050  addps xmm4,xmm7
    // 0xe828053  movaps [rbx+0x3C0],xmm4
    slot128(rbx, 0x3C0) = xmm4;

    // -------------------------------------------------------------------------
    // 0xe82805a..0xe82808d: Third matrix row (rbx+0x3D0) - same pattern at +0x20
    // -------------------------------------------------------------------------
    // 0xe82805a  movaps xmm4,[rdx+rcx+0x20]
    xmm4 = cslot128(rdx, rcx + 0x20);
    xmm5 = xmm4;                        // 0xe82805f  movaps xmm5,xmm4
    xmm5 = _mm_shuffle_ps(xmm5, xmm4, 0x00);  // 0xe828062  shufps xmm5,xmm4,0
    xmm6 = xmm4;                        // 0xe828066  movaps xmm6,xmm4
    xmm6 = _mm_shuffle_ps(xmm6, xmm4, 0x55);  // 0xe828069  shufps xmm6,xmm4,0x55
    xmm7 = xmm4;                        // 0xe82806d  movaps xmm7,xmm4
    xmm7 = _mm_shuffle_ps(xmm7, xmm4, 0xAA);  // 0xe828070  shufps xmm7,xmm4,0xAA
    xmm4 = _mm_shuffle_ps(xmm4, xmm4, 0xFF);  // 0xe828074  shufps xmm4,xmm4,0xFF

    xmm5 = _mm_mul_ps(xmm5, xmm3);     // 0xe828078  mulps xmm5,xmm3
    xmm6 = _mm_mul_ps(xmm6, xmm2);     // 0xe82807b  mulps xmm6,xmm2
    xmm7 = _mm_mul_ps(xmm7, xmm1);     // 0xe82807e  mulps xmm7,xmm1
    xmm7 = _mm_add_ps(xmm7, xmm5);     // 0xe828081  addps xmm7,xmm5
    xmm4 = _mm_mul_ps(xmm4, xmm0);     // 0xe828084  mulps xmm4,xmm0
    xmm4 = _mm_add_ps(xmm4, xmm6);     // 0xe828087  addps xmm4,xmm6
    xmm4 = _mm_add_ps(xmm4, xmm7);     // 0xe82808a  addps xmm4,xmm7
    // 0xe82808d  movaps [rbx+0x3D0],xmm4
    slot128(rbx, 0x3D0) = xmm4;

    // -------------------------------------------------------------------------
    // 0xe828094..0xe8280c7: Fourth matrix row (rbx+0x3E0) - same pattern at +0x30
    // -------------------------------------------------------------------------
    // 0xe828094  movaps xmm4,[rdx+rcx+0x30]
    xmm4 = cslot128(rdx, rcx + 0x30);
    xmm5 = xmm4;                        // 0xe828099  movaps xmm5,xmm4
    xmm5 = _mm_shuffle_ps(xmm5, xmm4, 0x00);  // 0xe82809c  shufps xmm5,xmm4,0
    xmm6 = xmm4;                        // 0xe8280a0  movaps xmm6,xmm4
    xmm6 = _mm_shuffle_ps(xmm6, xmm4, 0x55);  // 0xe8280a3  shufps xmm6,xmm4,0x55
    xmm7 = xmm4;                        // 0xe8280a7  movaps xmm7,xmm4
    xmm7 = _mm_shuffle_ps(xmm7, xmm4, 0xAA);  // 0xe8280aa  shufps xmm7,xmm4,0xAA
    xmm4 = _mm_shuffle_ps(xmm4, xmm4, 0xFF);  // 0xe8280ae  shufps xmm4,xmm4,0xFF

    xmm5 = _mm_mul_ps(xmm5, xmm3);     // 0xe8280b2  mulps xmm5,xmm3
    xmm6 = _mm_mul_ps(xmm6, xmm2);     // 0xe8280b5  mulps xmm6,xmm2
    xmm7 = _mm_mul_ps(xmm7, xmm1);     // 0xe8280b8  mulps xmm7,xmm1
    xmm7 = _mm_add_ps(xmm7, xmm5);     // 0xe8280bb  addps xmm7,xmm5
    xmm4 = _mm_mul_ps(xmm4, xmm0);     // 0xe8280be  mulps xmm4,xmm0
    xmm4 = _mm_add_ps(xmm4, xmm6);     // 0xe8280c1  addps xmm4,xmm6
    xmm4 = _mm_add_ps(xmm4, xmm7);     // 0xe8280c4  addps xmm4,xmm7
    // 0xe8280c7  movaps [rbx+0x3E0],xmm4
    slot128(rbx, 0x3E0) = xmm4;

    // -------------------------------------------------------------------------
    // 0xe8280ce..0xe82813d: First bounds-check path (test al,0x10 -> jne 0xE829039)
    // Loads per-shader data from [rbx+0x130 + r15*8], computes size, checks capacity
    // -------------------------------------------------------------------------
    // 0xe8280ce  mov r8,[rbx+0x130]
    r8 = slot64(rbx, 0x130);
    // 0xe8280d5  mov ecx,[r8+r15*8+0x14]              ; count
    rcx = slot32(r8 + r15 * 8 + 0x14);
    // 0xe8280da  cmp cx,4
    // 0xe8280de  mov edx,4
    // 0xe8280e3  cmovae ecx,edx                         ; clamp to 4
    if ((rcx & 0xFFFF) >= 4) rcx = 4;
    // 0xe8280e6  mov edi,[r8+r15*8+0x10]              ; size
    rdi = slot32(r8 + r15 * 8 + 0x10);
    // 0xe8280eb  shl ecx,4
    rcx <<= 4;
    // 0xe8280ee  movzx esi,cx
    rsi = rcx & 0xFFFF;
    // 0xe8280f1  test al,0x10
    // 0xe8280f3  jne 0xE829039                          ; -> loc_e829039 (outside chunk)
    if ((al & 0x10) == 0) {
        // 0xe8280f9  lea rdx,[rsi+rdi]
        rdx = rsi + rdi;
        // 0xe8280fd  mov rax,[rbx+0x98]
        // 0xe828104  mov rax,[rax]
        rax = slot64(slot64(rbx, 0x98), 0);
        // 0xe828107  mov rcx,[r13]
        rcx = slot64(r13, 0);
        // 0xe82810b  mov r9,rax
        // 0xe82810e  sub r9,rcx
        r9 = rax - rcx;
        // 0xe828111  mov r8,rdx
        // 0xe828114  sub r8,r9
        r8 = rdx - r9;
        // 0xe828117  jbe 0xE829554                        ; -> loc_e829554 (outside)
        if ((int64_t)r8 > (int64_t)r9) {
            // 0xe82811d  mov r9,[rbx+0xA0]
            // 0xe828124  mov r9,[r9+0x38]
            r9 = slot64(slot64(rbx, 0xA0), 0x38);
            // 0xe828128  sub r9,rcx
            r9 = r9 - rcx;
            // 0xe82812b  cmp rdx,r9
            // 0xe82812e  jbe 0xE829531                        ; -> loc_e829531
            if ((int64_t)rdx > (int64_t)r9) {
                // 0xe828134  mov rcx,r13
                // 0xe828137  lea r8,[rbx+0xC0]
                // 0xe82813e  call 0x47E8F0                    ; -> sub_47e8f0
                rcx = r13;
                r8 = reinterpret_cast<uint64_t>(rbx_ptr(rbx, 0xC0));
                sub_47e8f0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(r8), nullptr);
                // 0xe828143  nop
                // 0xe828144  jmp 0xE829549                    ; -> loc_e829549
            }
        }
    }

    // ... continued in next part
}

} // namespace d3d12
} // namespace native

#define LIFT_FN(name, rva) \
    namespace native { namespace registry { \
    struct name##_entry { \
        static constexpr uintptr_t rva = rva; \
        static constexpr const char* symbol = #name; \
        static constexpr int mode = 2; \
        name##_entry() { } \
    }; \
    static name##_entry name##_instance; \
    } }

LIFT_FN(sub_e824fbe_chunk_c02, 0xe827fa3)

static_assert(true, "sub_e824fbe chunk c02 - part 1 written, continue appending");