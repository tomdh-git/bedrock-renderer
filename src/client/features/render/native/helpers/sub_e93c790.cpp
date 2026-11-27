// LIFT 0xe93c790 size 0x101 1.26.62.01 sub_e93c790
#include "client/features/render/native/helpers/sub_e93c790.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>
#include <immintrin.h>

namespace native::helpers {

LIFT_FN(sub_e93c790, "sub_e93c790", 0xe93c790, sub_e93c790, nullptr);

// Verbatim instruction quotes from the disassembly of [0xe93c790, 0xe93c891) (rdis `fn` output).
// This function is a leaf: there are no call instructions, so no call quotes are needed.
// UNRESOLVED CALL = none.
// Bare lines below (inside #if 0) are counted by verify_oc; they must match rdis exactly.
#if 0
0xe93c790  mov [rsp+8],rbx
0xe93c795  mov eax,[0x1230A11C]
0xe93c79b  mov r10,rdx
0xe93c79e  sub r10,rcx
0xe93c7a1  mov ebx,r8d
0xe93c7a4  mov r11,rdx
0xe93c7a7  mov r9,rcx
0xe93c7aa  test al,0x20
0xe93c7ac  je short 0xE93C807
0xe93c7ae  cmp r10,0x20
0xe93c7b2  jb short 0xE93C807
0xe93c7b4  vmovd xmm3,ebx
0xe93c7b8  vpshufd xmm3,xmm3,0
0xe93c7bd  and r10,0xFFFFFFFFFFFFFFE0
0xe93c7c1  lea r8,[0]
0xe93c7c8  vinsertf128 ymm3,ymm3,xmm3,1
0xe93c7ce  add r10,rcx
0xe93c7d1  vpcmpeqd ymm0,ymm3,[rcx]
0xe93c7d5  vmovmskps edx,ymm0
0xe93c7d9  vpmovzxbd ymm1,[r8+rdx*8+0xEECAA20]
0xe93c7e3  vpermd ymm2,ymm1,[rcx]
0xe93c7e8  vmovdqu [r9],ymm2
0xe93c7ed  movzx eax,byte ptr [rdx+r8+0xEECB220]
0xe93c7f6  add rcx,0x20
0xe93c7fa  add r9,rax
0xe93c7fd  cmp rcx,r10
0xe93c800  jne short 0xE93C7D1
0xe93c802  vzeroupper
0xe93c805  jmp short 0xE93C86D
0xe93c807  test al,4
0xe93c809  je short 0xE93C86D
0xe93c80b  cmp r10,0x10
0xe93c80f  jb short 0xE93C86D
0xe93c811  movd xmm2,ebx
0xe93c815  lea r8,[0]
0xe93c81c  and r10,0xFFFFFFFFFFFFFFF0
0xe93c820  pshufd xmm2,xmm2,0
0xe93c825  add r10,rcx
0xe93c828  nop [rax+rax]
0xe93c830  movdqu xmm1,[rcx]
0xe93c834  add rcx,0x10
0xe93c838  movdqa xmm0,xmm1
0xe93c83c  pcmpeqd xmm0,xmm2
0xe93c840  movmskps edx,xmm0
0xe93c843  mov eax,edx
0xe93c845  add rax,rax
0xe93c848  movdqu xmm0,[r8+rax*8+0xEECA910]
0xe93c852  pshufb xmm1,xmm0
0xe93c857  movdqu [r9],xmm1
0xe93c85c  movzx eax,byte ptr [rdx+r8+0xEECAA10]
0xe93c865  add r9,rax
0xe93c868  cmp rcx,r10
0xe93c86b  jne short 0xE93C830
0xe93c86d  cmp rcx,r11
0xe93c870  je short 0xE93C888
0xe93c872  mov eax,[rcx]
0xe93c874  cmp eax,ebx
0xe93c876  je short 0xE93C87F
0xe93c878  mov [r9],eax
0xe93c87b  add r9,4
0xe93c87f  add rcx,4
0xe93c883  cmp rcx,r11
0xe93c886  jne short 0xE93C872
0xe93c888  mov rbx,[rsp+8]
0xe93c88d  mov rax,r9
0xe93c890  ret
#endif

// Ranges: every instruction of [0xe93c790, 0xe93c891) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

// Game-image data-table base (the exe is read at these RVAs, matching the original's
// RIP-relative absolute-address operands).
static std::uint8_t* imageData(std::uintptr_t rva) {
    return reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase() + rva);
}

static constexpr std::uintptr_t kData_EECAA20 = 0xEECAA20; // 8-byte shuffle control, indexed mask*8
static constexpr std::uintptr_t kData_EECB220 = 0xEECB220; // 1-byte advance, indexed mask
static constexpr std::uintptr_t kData_EECA910 = 0xEECA910; // 16-byte shuffle control, indexed mask*16
static constexpr std::uintptr_t kData_EECAA10 = 0xEECAA10; // 1-byte advance, indexed mask
static constexpr std::uintptr_t kData_1230A11C = 0x1230A11C; // 4-byte flag dword (low byte tested)

std::uintptr_t sub_e93c790(std::uint8_t* a0, std::uint8_t* a1, std::uint32_t fill) {
    // x64 Microsoft ABI: RCX = a0 (src), RDX = a1 (end), R8 = fill (32-bit).
    // Return: RAX = r9 (destination pointer after processing).
    // RBX is callee-saved: spilled to [rsp+8] in the prologue and reloaded in the epilogue.

    std::uint8_t* src = a0;          // RCX
    std::uint8_t* end = a1;          // RDX (original end)
    std::uint32_t fillVal = fill;    // EBX = R8D zero-extended
    std::uint8_t* savedEnd = a1;     // R11 = saved RDX (original end, used by the scalar tail)
    std::uintptr_t len = end - src;  // R10 = RDX - RCX
    std::uint8_t* dst = a0;          // R9 = copy of RCX, advanced as bytes are written

    // Flag dword (4 bytes read at data_1230A11C; low byte used for phase selection).
    const std::uint32_t flags = *reinterpret_cast<const std::uint32_t*>(
        imageData(kData_1230A11C));

    // ------------------------------------------------------------------
    // 0xe93c790..0xe93c7ae: basic block 0 (prologue + flag 0x20 test)
    //   mov [rsp+8],rbx        ; spill RBX (callee-saved)
    //   mov eax,[0x1230A11C]   ; flags
    //   mov r10,rdx            ; len = end - src  (computed below)
    //   sub r10,rcx
    //   mov ebx,r8d            ; fillVal = fill
    //   mov r11,rdx            ; savedEnd = end
    //   mov r9,rcx             ; dst = src
    //   test al,0x20
    //   je short 0xE93C807     ; if !(flags & 0x20) goto block 5
    // (RBX spill/reload is a callee-save bookkeeping artifact; no observable effect in C++.)

    if ((flags & 0x20u) != 0u) {
        // 0xe93c7ae..0xe93c7b4: basic block 1 (length >= 0x20 test)
        //   cmp r10,0x20
        //   jb short 0xE93C807 ; if len <u 0x20 goto block 5
        if (len >= 0x20u) {
            // 0xe93c7b4..0xe93c7d1: basic block 2 (AVX setup)
            //   vmovd xmm3,ebx          ; ymm3 = broadcast dword fillVal
            //   vpshufd xmm3,xmm3,0
            //   and r10,0x...E0         ; r10 = len & ~0x1F
            //   lea r8,[0]              ; table base = 0
            //   vinsertf128 ymm3,ymm3,xmm3,1
            //   add r10,rcx             ; r10 = simdEnd = src + (len & ~0x1F)
            const __m256i ymm3 = _mm256_set1_epi32(static_cast<int>(fillVal));
            const std::uintptr_t simdLen = len & ~0x1FULL;
            std::uint8_t* simdEnd = src + simdLen;   // R10

            // 0xe93c7d1..0xe93c802: basic block 3 (AVX loop body)
            //   vpcmpeqd ymm0,ymm3,[rcx]        ; compare 8 dwords with fill
            //   vmovmskps edx,ymm0              ; mask = sign bits
            //   vpmovzxbd ymm1,[r8+rdx*8+0xEECAA20]   ; 8 bytes at table+mask*8 -> 8 dwords
            //   vpermd   ymm2,ymm1,[rcx]        ; permute using [rcx] dwords as index
            //   vmovdqu  [r9],ymm2              ; store 32 bytes
            //   movzx    eax,byte [rdx+r8+0xEECB220]  ; advance = table[mask]
            //   add rcx,0x20                    ; src += 32
            //   add r9,rax                      ; dst += advance
            //   cmp rcx,r10 / jne 0xE93C7D1     ; loop while src != simdEnd
            while (src != simdEnd) {
                const __m256i src32 = *reinterpret_cast<const __m256i*>(src);   // [rcx] 32B
                const __m256i cmp = _mm256_cmpeq_epi32(ymm3, src32);            // vpcmpeqd
                const int mask = _mm256_movemask_ps(reinterpret_cast<const __m256&>(cmp)); // vmovmskps
                // vpmovzxbd ymm1, [table + mask*8] : load 8 bytes, zero-extend to 8 dwords
                const __m128i tbl8 = *reinterpret_cast<const __m128i*>(
                    imageData(kData_EECAA20) + static_cast<std::uintptr_t>(mask) * 8);
                const __m256i ymm1 = _mm256_cvtepi8_epi32(tbl8);
                // vpermd ymm2, ymm1, [rcx] : permute ymm1 dwords using src32 dwords as index
                const __m256i ymm2 = _mm256_permutevar8x32_epi32(ymm1, src32);
                *reinterpret_cast<__m256i*>(dst) = ymm2;                       // vmovdqu [r9], 32B
                const std::uint8_t advance = imageData(kData_EECB220)[mask];   // movzx byte
                src += 0x20;
                dst += advance;
            }

            // 0xe93c802..0xe93c807: basic block 4
            //   vzeroupper
            //   jmp short 0xE93C86D              ; goto block 9
            _mm256_zeroupper();
            // fall through to block 9 (0xe93c86d)
        }
        // else (len < 0x20): fall through to block 5 (0xe93c807)
    }
    // else (flags & 0x20 == 0): block 5 (0xe93c807)

    // 0xe93c807..0xe93c80b: basic block 5 (flag 0x04 test)
    //   test al,4
    //   je short 0xE93C86D    ; if !(flags & 0x04) goto block 9
    if ((flags & 0x04u) != 0u) {
        // 0xe93c80b..0xe93c811: basic block 6 (length >= 0x10 test)
        //   cmp r10,0x10
        //   jb short 0xE93C86D ; if len <u 0x10 goto block 9
        if (len >= 0x10u) {
            // 0xe93c811..0xe93c830: basic block 7 (SSE setup)
            //   movd xmm2,ebx             ; xmm2 = fillVal in low dword
            //   lea r8,[0]                ; table base = 0
            //   and r10,0x...F0           ; r10 = len & ~0x0F
            //   pshufd xmm2,xmm2,0        ; broadcast fillVal to all 4 dwords
            //   add r10,rcx               ; r10 = simdEnd = src + (len & ~0x0F)
            const __m128i xmm2 = _mm_set1_epi32(static_cast<int>(fillVal));
            const std::uintptr_t simdLen = len & ~0x0FULL;
            std::uint8_t* simdEnd = src + simdLen;   // R10

            // 0xe93c830..0xe93c86d: basic block 8 (SSE loop body)
            //   movdqu xmm1,[rcx]                ; load 16 bytes
            //   add rcx,0x10                     ; src += 16
            //   movdqa xmm0,xmm1
            //   pcmpeqd xmm0,xmm2                ; compare 4 dwords with fill
            //   movmskps edx,xmm0                ; mask = sign bits (4 bits)
            //   mov eax,edx
            //   add rax,rax                      ; rax = mask*2
            //   movdqu xmm0,[r8+rax*8+0xEECA910] ; 16 bytes at table + mask*16
            //   pshufb xmm1,xmm0                 ; shuffle src bytes by control
            //   movdqu [r9],xmm1                 ; store 16 bytes
            //   movzx eax,byte [rdx+r8+0xEECAA10]; advance = table[mask]
            //   add r9,rax                       ; dst += advance
            //   cmp rcx,r10 / jne 0xE93C830      ; loop while src != simdEnd
            while (src != simdEnd) {
                const __m128i src16 = *reinterpret_cast<const __m128i*>(src);   // [rcx] 16B
                src += 0x10;
                const __m128i cmp = _mm_cmpeq_epi32(src16, xmm2);               // pcmpeqd
                const int mask = _mm_movemask_ps(reinterpret_cast<const __m128&>(cmp)); // movmskps (4 bits)
                const std::uintptr_t tblOff = static_cast<std::uintptr_t>(mask) * 16; // rax*8 = mask*2*8 = mask*16
                const __m128i tbl16 = *reinterpret_cast<const __m128i*>(
                    imageData(kData_EECA910) + tblOff);
                const __m128i shuffled = _mm_shuffle_epi8(src16, tbl16);        // pshufb
                *reinterpret_cast<__m128i*>(dst) = shuffled;                    // movdqu [r9], 16B
                const std::uint8_t advance = imageData(kData_EECAA10)[mask];    // movzx byte
                dst += advance;
            }
        }
        // else (len < 0x10): fall through to block 9 (0xe93c86d)
    }
    // else (flags & 0x04 == 0): block 9 (0xe93c86d)

    // 0xe93c86d..0xe93c872: basic block 9 (tail length test)
    //   cmp rcx,r11
    //   je short 0xE93C888   ; if src == savedEnd goto block 13 (return)
    // fall through to block 10 (0xe93c872)

    // 0xe93c872..0xe93c87f: basic blocks 10/11/12 (scalar tail)
    //   mov eax,[rcx]                ; dword = *src
    //   cmp eax,ebx                  ; if dword == fillVal skip write
    //   je short 0xE93C87F
    //   mov [r9],eax                 ; *dst = dword
    //   add r9,4                     ; dst += 4
    //   add rcx,4                    ; src += 4
    //   cmp rcx,r11 / jne 0xE93C872  ; loop while src != savedEnd
    while (src != savedEnd) {
        const std::uint32_t dword = *reinterpret_cast<const std::uint32_t*>(src);  // [rcx] 4B
        if (dword != fillVal) {
            *reinterpret_cast<std::uint32_t*>(dst) = dword;     // [r9] = eax
            dst += 4;                                           // r9 += 4
        }
        src += 4;                                               // rcx += 4
    }

    // 0xe93c888..0xe93c891: basic block 13 (epilogue)
    //   mov rbx,[rsp+8]     ; reload RBX
    //   mov rax,r9          ; return dst
    //   ret
    return reinterpret_cast<std::uintptr_t>(dst);  // RAX = R9
}

} // namespace native::helpers
