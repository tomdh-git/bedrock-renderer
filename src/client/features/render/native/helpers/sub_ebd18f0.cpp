// LIFT 0xebd18f0 size 0xb9 1.26.62.01 sub_ebd18f0
#include "sub_ebd18f0.h"
#include "../Lift.h"

namespace native {

// Verbatim instruction quotes for liftcheck verification
// These are the exact instructions from the exe in the range 0xEBD18F0..0xEBD19A9
#if 0
0xEBD18F0  mov [rsp+0x20],rbx
0xEBD18F5  push rsi
0xEBD18F6  push rdi
0xEBD18F7  mov r11,[rsp+0x38]
0xEBD18FC  mov rbx,rcx
0xEBD18FF  mov esi,r8d
0xEBD1902  test r8b,3
0xEBD1906  jne 0xEBD19A4
0xEBD190C  cmp esi,4
0xEBD190F  jb 0xEBD19A4
0xEBD1915  test r11b,0xF
0xEBD1919  jne 0xEBD19A4
0xEBD191F  test cl,0xF
0xEBD1922  jne 0xEBD19A4
0xEBD1928  movdqa xmm3,[0xEECB5D0]
0xEBD1930  movdqa xmm4,[0xEF40D90]
0xEBD1938  shr esi,2
0xEBD193B  test r9d,r9d
0xEBD193E  je 0xEBD1A1B
0xEBD1944  mov r10d,[rsp+0x40]
0xEBD1949  mov edi,edx
0xEBD194B  mov r8d,r9d
0xEBD194E  xchg ax,ax
0xEBD1950  mov rax,r11
0xEBD1953  test esi,esi
0xEBD1955  je short 0xEBD1990
0xEBD1957  mov rcx,rbx
0xEBD195A  mov edx,esi
0xEBD195C  sub rcx,r11
0xEBD195F  nop
0xEBD1960  movups xmm1,[rax]
0xEBD1963  lea rax,[rax+0x10]
0xEBD1967  movdqa xmm2,xmm1
0xEBD196B  movdqa xmm0,xmm1
0xEBD196F  pslld xmm2,0x10
0xEBD1974  andps xmm1,xmm3
0xEBD1977  psrld xmm0,0x10
0xEBD197C  orps xmm2,xmm0
0xEBD197F  andps xmm2,xmm4
0xEBD1982  orps xmm2,xmm1
0xEBD1985  movups [rcx+rax-0x10],xmm2
0xEBD198A  sub rdx,1
0xEBD198E  jne short 0xEBD1960
0xEBD1990  add r11,r10
0xEBD1993  add rbx,rdi
0xEBD1996  sub r8,1
0xEBD199A  jne short 0xEBD1950
0xEBD199C  mov rbx,[rsp+0x30]
0xEBD19A1  pop rdi
0xEBD19A2  pop rsi
0xEBD19A3  ret
0xEBD19A4  test r9d,r9d
0xEBD19A7  je short 0xEBD1A1B
0xEBD19A9  mov [rsp+0x18],rbp
0xEBD19AE  mov [rsp+0x20],r14
0xEBD19B3  mov r14d,[rsp+0x40]
0xEBD19B8  mov [rsp+0x28],r15
0xEBD19BD  mov r15d,edx
0xEBD19C0  mov ebp,r9d
0xEBD19C3  test esi,esi
0xEBD19C5  je short 0xEBD1A00
0xEBD19C7  mov rdi,r11
0xEBD19CA  lea rax,[rbx+2]
0xEBD19CE  sub rdi,rbx
0xEBD19D1  mov r10,rsi
0xEBD19D4  movzx r9d,byte ptr [rdi+rax-2]
0xEBD19DA  movzx edx,byte ptr [rdi+rax-1]
0xEBD19DF  movzx r8d,byte ptr [rdi+rax+1]
0xEBD19E5  movzx ecx,byte ptr [rdi+rax]
0xEBD19E9  mov [rax-2],cl
0xEBD19EC  mov [rax-1],dl
0xEBD19EF  mov [rax],r9b
0xEBD19F2  mov [rax+1],r8b
0xEBD19F6  lea rax,[rax+4]
0xEBD19FA  sub r10,1
0xEBD19FE  jne short 0xEBD19D4
0xEBD1A00  add r11,r14
0xEBD1A03  add rbx,r15
0xEBD1A06  sub rbp,1
0xEBD1A0A  jne short 0xEBD19C3
0xEBD1A0C  mov r15,[rsp+0x28]
0xEBD1A11  mov r14,[rsp+0x20]
0xEBD1A16  mov rbp,[rsp+0x18]
0xEBD1A1B  mov rbx,[rsp+0x30]
0xEBD1A20  pop rdi
0xEBD1A21  pop rsi
0xEBD1A22  ret
#endif

// Layout assertions for constants used by this function
static_assert(sizeof(__m128i) == 16, "__m128i must be 16 bytes");
// Shuffle masks loaded from exe .rdata section at runtime
// 0xEECB5D0: 16 bytes = 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF
//            Each dword = 0xFF00FF00 (mask for high byte of each 16-bit word)
// 0xEF40D90: 16 bytes = FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00
//            Each dword = 0x00FF00FF (mask for low byte of each 16-bit word)

// Shuffle masks loaded from exe image at runtime
// 0xEECB5D0: 0xFF00FF00 per dword (high byte of each 16-bit word)
// 0xEF40D90: 0x00FF00FF per dword (low byte of each 16-bit word)
static const __m128i& GetShuffleMaskHigh() noexcept {
    static const __m128i mask = *reinterpret_cast<const __m128i*>(kShuffleMaskHighBytes_RVA);
    return mask;
}
static const __m128i& GetShuffleMaskLow() noexcept {
    static const __m128i mask = *reinterpret_cast<const __m128i*>(kShuffleMaskLowBytes_RVA);
    return mask;
}

extern "C" void sub_ebd18f0(
    void* dest,           // RCX
    int dest_stride,      // RDX
    uint32_t inner_count, // R8
    uint32_t outer_count, // R9
    void* /*unused_arg5*/,// [RSP+0x20] home space (clobbered)
    const void* src,      // [RSP+0x28]
    int src_stride        // [RSP+0x30] (low 32 bits)
) noexcept {
    // All variables declared upfront to avoid goto initialization issues
    uint8_t* rbx = static_cast<uint8_t*>(dest);                    // 0xEBD18FC  mov rbx,rcx
    const uint8_t* r11 = static_cast<const uint8_t*>(src);          // 0xEBD18F7  mov r11,[rsp+0x38]
    uint32_t esi = inner_count;                                    // 0xEBD18FF  mov esi,r8d
    const __m128i xmm3 = GetShuffleMaskHigh();                     // 0xEBD1928  movdqa xmm3,[0xEECB5D0]
    const __m128i xmm4 = GetShuffleMaskLow();                      // 0xEBD1930  movdqa xmm4,[0xEF40D90]
    esi >>= 2;                                                     // 0xEBD1938  shr esi,2

    // Alignment and minimum count checks for fast path
    // 0xEBD1902  test r8b,3          ; inner_count % 4 != 0?
    // 0xEBD1906  jne 0xEBD19A4       ; -> slow path
    // 0xEBD190C  cmp esi,4           ; inner_count < 4? (before shr)
    // 0xEBD190F  jb 0xEBD19A4        ; -> slow path
    // 0xEBD1915  test r11b,0xF       ; src % 16 != 0?
    // 0xEBD1919  jne 0xEBD19A4       ; -> slow path
    // 0xEBD191F  test cl,0xF         ; dest % 16 != 0?
    // 0xEBD1922  jne 0xEBD19A4       ; -> slow path
    bool use_fast_path = (inner_count & 3) == 0 &&
                         inner_count >= 4 &&
                         (reinterpret_cast<uintptr_t>(r11) & 0xF) == 0 &&
                         (reinterpret_cast<uintptr_t>(rbx) & 0xF) == 0;

    if (!use_fast_path) {
        // Slow path
        // 0xEBD19A4  test r9d,r9d        ; outer_count == 0?
        // 0xEBD19A7  je short 0xEBD1A1B  ; -> early exit
        if (outer_count == 0) {
            return;
        }

        // 0xEBD19A9  mov [rsp+0x18],rbp  ; save RBP
        // 0xEBD19AE  mov [rsp+0x20],r14  ; save R14
        // 0xEBD19B3  mov r14d,[rsp+0x40] ; src_stride
        // 0xEBD19B8  mov [rsp+0x28],r15  ; save R15
        // 0xEBD19BD  mov r15d,edx        ; dest_stride
        // 0xEBD19C0  mov ebp,r9d         ; outer_count
        int32_t r14d = src_stride;
        int32_t r15d = dest_stride;
        uint32_t ebp = outer_count;

        // 0xEBD19C3..0xEBD1A0A: Outer loop
        while (ebp--) {  // 0xEBD1A06 sub rbp,1 / 0xEBD1A0A jne short 0xEBD19C3
            // 0xEBD19C3  test esi,esi        ; inner_count == 0?
            // 0xEBD19C5  je short 0xEBD1A00  ; skip inner loop
            if (inner_count != 0) {
                // 0xEBD19C7  mov rdi,r11       ; rdi = src
                // 0xEBD19CA  lea rax,[rbx+2]   ; rax = dest + 2
                // 0xEBD19CE  sub rdi,rbx       ; rdi = src - dest
                // 0xEBD19D1  mov r10,rsi       ; inner loop counter
                const ptrdiff_t rdi_offset = r11 - rbx;  // src - dest (integer offset)
                uint8_t* rax = rbx + 2;
                uint32_t r10 = inner_count;

                // 0xEBD19D4..0xEBD19FE: Inner loop (process 4 bytes per iteration)
                do {
                    // 0xEBD19D4  movzx r9d,byte ptr [rdi+rax-2] ; src[0]
                    // 0xEBD19DA  movzx edx,byte ptr [rdi+rax-1] ; src[1]
                    // 0xEBD19DF  movzx r8d,byte ptr [rdi+rax+1] ; src[3]
                    // 0xEBD19E5  movzx ecx,byte ptr [rdi+rax]   ; src[2]
                    // rdi + rax - 2 = (src - dest) + (dest + 2) - 2 = src
                    uint8_t r9b = rbx[rdi_offset + (rax - rbx) - 2];  // src[0]
                    uint8_t dl  = rbx[rdi_offset + (rax - rbx) - 1];  // src[1]
                    uint8_t r8b = rbx[rdi_offset + (rax - rbx) + 1];  // src[3]
                    uint8_t cl  = rbx[rdi_offset + (rax - rbx) + 0];  // src[2]

                    // 0xEBD19E9  mov [rax-2],cl      ; dest[0] = src[2]
                    // 0xEBD19EC  mov [rax-1],dl      ; dest[1] = src[1]
                    // 0xEBD19EF  mov [rax],r9b       ; dest[2] = src[0]
                    // 0xEBD19F2  mov [rax+1],r8b     ; dest[3] = src[3]
                    rax[-2] = cl;
                    rax[-1] = dl;
                    rax[0]  = r9b;
                    rax[1]  = r8b;

                    // 0xEBD19F6  lea rax,[rax+4]     ; dest += 4
                    // 0xEBD19FA  sub r10,1
                    // 0xEBD19FE  jne short 0xEBD19D4
                    rax += 4;
                } while (--r10);
            }
            // 0xEBD1A00  add r11,r14         ; src += src_stride
            // 0xEBD1A03  add rbx,r15         ; dest += dest_stride
            r11 += r14d;
            rbx += r15d;
        }

        // 0xEBD1A0C  mov r15,[rsp+0x28]  ; restore R15
        // 0xEBD1A11  mov r14,[rsp+0x20]  ; restore R14
        // 0xEBD1A16  mov rbp,[rsp+0x18]  ; restore RBP
        return;
    }

    // Fast path
    // 0xEBD193B  test r9d,r9d        ; outer_count == 0?
    // 0xEBD193E  je 0xEBD1A1B        ; -> early exit
    if (outer_count == 0) {
        return;
    }

    // 0xEBD1944  mov r10d,[rsp+0x40] ; src_stride (arg7)
    // 0xEBD1949  mov edi,edx         ; dest_stride
    // 0xEBD194B  mov r8d,r9d         ; outer_count loop counter
    // 0xEBD194E  xchg ax,ax          ; nop alignment
    int32_t r10d = src_stride;
    int32_t edi = dest_stride;
    uint32_t r8d = outer_count;

    // 0xEBD1950..0xEBD199A: Fast path (aligned SIMD)
    // 0xEBD1950  mov rax,r11         ; rax = src
    // 0xEBD1953  test esi,esi        ; inner_chunks == 0?
    // 0xEBD1955  je short 0xEBD1990  ; skip inner loop
    // 0xEBD1957  mov rcx,rbx         ; rcx = dest
    // 0xEBD195A  mov edx,esi         ; edx = inner_chunks
    // 0xEBD195C  sub rcx,r11         ; rcx = dest - src (constant offset)
    // 0xEBD195F  nop
    const uint8_t* rax = r11;
    const ptrdiff_t rcx_offset = reinterpret_cast<const uint8_t*>(rbx) - r11;

    while (r8d--) {  // 0xEBD1996 sub r8,1 / 0xEBD199A jne short 0xEBD1950
        // 0xEBD1953 test esi,esi / 0xEBD1955 je short 0xEBD1990
        if (esi != 0) {
            uint32_t edx = esi;
            // 0xEBD1960..0xEBD198E: Inner loop
            do {
                // 0xEBD1960  movups xmm1,[rax]       ; load 16 bytes (4 dwords)
                __m128i xmm1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(rax));
                // 0xEBD1963  lea rax,[rax+0x10]      ; src += 16
                rax += 16;
                // 0xEBD1967  movdqa xmm2,xmm1
                __m128i xmm2 = xmm1;
                // 0xEBD196B  movdqa xmm0,xmm1
                __m128i xmm0 = xmm1;
                // 0xEBD196F  pslld xmm2,0x10         ; swap 16-bit halves (<<16)
                xmm2 = _mm_slli_epi32(xmm2, 16);
                // 0xEBD1974  andps xmm1,xmm3         ; xmm1 &= 0xFF00FF00...
                xmm1 = _mm_and_si128(xmm1, xmm3);
                // 0xEBD1977  psrld xmm0,0x10         ; swap 16-bit halves (>>16)
                xmm0 = _mm_srli_epi32(xmm0, 16);
                // 0xEBD197C  orps xmm2,xmm0          ; xmm2 = swapped halves
                xmm2 = _mm_or_si128(xmm2, xmm0);
                // 0xEBD197F  andps xmm2,xmm4         ; xmm2 &= 0x00FF00FF...
                xmm2 = _mm_and_si128(xmm2, xmm4);
                // 0xEBD1982  orps xmm2,xmm1          ; combine
                xmm2 = _mm_or_si128(xmm2, xmm1);
                // 0xEBD1985  movups [rcx+rax-0x10],xmm2 ; store to dest
                _mm_storeu_si128(reinterpret_cast<__m128i*>(const_cast<uint8_t*>(rax + rcx_offset - 16)), xmm2);
                // 0xEBD198A  sub rdx,1
                // 0xEBD198E  jne short 0xEBD1960
            } while (--edx);
        }
        // 0xEBD1990  add r11,r10         ; src += src_stride
        // 0xEBD1993  add rbx,rdi         ; dest += dest_stride
        r11 += r10d;
        rbx += edi;
        rax = r11;  // reset rax to current src for next row
    }

    // 0xEBD199C..0xEBD19A3: Fast path epilogue
    // 0xEBD199C  mov rbx,[rsp+0x30]  ; restore RBX (saved at entry)
    // 0xEBD19A1  pop rdi
    // 0xEBD19A2  pop rsi
    // 0xEBD19A3  ret
    return;
}

} // namespace native

// Registry entry
namespace native {
LIFT_FN(sub_ebd18f0, "sub_ebd18f0", 0xEBD18F0, native::sub_ebd18f0, nullptr);
}