// LIFT 0xebce650 size 0x6b 1.26.62.01 sub_ebce650
#include "sub_ebce650.h"
#include "client/features/render/native/Lift.h"

#if 0
// Verbatim instructions of sub_ebce650 from the exe, [0xebce650, 0xebce6bb) (size 0x6b),
// disassembly source: rdis dis 0xebce650 0x6b. Every call in the function is quoted here.
0xebce650  mov [rsp+8],rbx
0xebce655  mov [rsp+0x10],rsi
0xebce65a  push rdi
0xebce65b  sub rsp,0x20
0xebce65f  cmp [r8+8],r9d
0xebce663  mov edi,edx
0xebce665  mov rdx,[r8]
0xebce668  mov rsi,rcx
0xebce66b  cmovl r9d,[r8+8]
0xebce670  test rdx,rdx
0xebce673  jne short 0xEBCE679
0xebce675  xor eax,eax
0xebce677  jmp short 0xEBCE693
0xebce679  mov rax,rdx
0xebce67c  test r9d,r9d
0xebce67f  jle short 0xEBCE691
0xebce681  cmp byte ptr [rax],0
0xebce684  je short 0xEBCE691
0xebce686  inc rax
0xebce689  dec r9d
0xebce68c  test r9d,r9d
0xebce68f  jg short 0xEBCE681
0xebce691  sub eax,edx
0xebce693  dec edi
0xebce695  cmp eax,edi
0xebce697  cmovl edi,eax
0xebce69a  movsxd rbx,edi
0xebce69d  mov r8,rbx
0xebce6a0  call 0xEBCE390
0xebce6a5  mov byte ptr [rbx+rsi],0
0xebce6a9  mov eax,edi
0xebce6ab  mov rbx,[rsp+0x30]
0xebce6b0  mov rsi,[rsp+0x38]
0xebce6b5  add rsp,0x20
0xebce6b9  pop rdi
0xebce6ba  ret
#endif

namespace native {

// Lifted body of sub_ebce650 (0xebce650, size 0x6b, 1.26.62.01): same reads, same writes, the same
// single call in the same place, same return. The exe function is a leaf apart from the call to
// the lift-set helper sub_ebce390; it saves/restores rbx, rsi, rdi itself (callee-saved registers),
// which the C++ prologue/epilogue handles the same way.
//
// Phase 1, 0xebce650..0xebce670: prologue, argument copies, bound = min(maxlen, srcdesc->maxlen).
//
//   0xebce650  mov [rsp+8],rbx        ; save callee-saved registers
//   0xebce655  mov [rsp+0x10],rsi
//   0xebce65a  push rdi
//   0xebce65b  sub rsp,0x20
//   0xebce65f  cmp [r8+8],r9d         ; srcdesc->maxlen vs maxlen (signed)
//   0xebce663  mov edi,edx            ; count limit = dstSize
//   0xebce665  mov rdx,[r8]           ; src = srcdesc->ptr
//   0xebce668  mov rsi,rcx            ; save dst in rsi (callee-saved across the call)
//   0xebce66b  cmovl r9d,[r8+8]       ; bound = srcdesc->maxlen if smaller
int sub_ebce650_lifted(char* dst, int dstSize, SrcDesc* srcdesc, int maxlen) {
    // 0xebce650..0xebce65b: register saves are the compiler's prologue; nothing to express.
    static_assert(offsetof(SrcDesc, ptr) == 0x00, "sub_ebce650: SrcDesc::ptr at +0x00");
    static_assert(offsetof(SrcDesc, maxlen) == 0x08, "sub_ebce650: SrcDesc::maxlen at +0x08");

    // 0xebce65f  cmp [r8+8],r9d   (read +0x08 first)
    // 0xebce665  mov rdx,[r8]      (read +0x00 second)
    // 0xebce66b  cmovl r9d,[r8+8]  (read +0x08 third)
    std::int32_t field8 = srcdesc->maxlen;   // 0xebce65f  cmp [r8+8],r9d
    char* src = srcdesc->ptr;                // 0xebce665  mov rdx,[r8]
    std::int32_t bound = maxlen;             // r9d on entry
    if (field8 < bound) bound = field8;      // 0xebce66b  cmovl r9d,[r8+8]

    // Phase 2, 0xebce670..0xebce693: null test and strnlen_s-style scan of src, bounded by `bound`.
    //
    //   0xebce670  test rdx,rdx
    //   0xebce673  jne short 0xEBCE679
    //   0xebce675  xor eax,eax              ; len = 0 when src == 0
    //   0xebce677  jmp short 0xEBCE693
    //   0xebce679  mov rax,rdx              ; p = src
    //   0xebce67c  test r9d,r9d
    //   0xebce67f  jle short 0xEBCE691      ; skip scan when bound <= 0
    //   0xebce681  cmp byte ptr [rax],0     ; stop at NUL
    //   0xebce684  je short 0xEBCE691
    //   0xebce686  inc rax
    //   0xebce689  dec r9d
    //   0xebce68c  test r9d,r9d
    //   0xebce68f  jg short 0xEBCE681
    //   0xebce691  sub eax,edx              ; len = p - src (32-bit)
    std::int32_t len;
    if (src == nullptr) {                    // 0xebce670  test rdx,rdx ; jne short 0xEBCE679
        len = 0;                             // 0xebce675  xor eax,eax
    } else {                                 // 0xebce679  mov rax,rdx
        const char* p = src;
        std::int32_t n = bound;              // r9d
        if (n > 0) {                         // 0xebce67c  test r9d,r9d ; jle short 0xEBCE691
            do {                             // 0xebce681..0xebce68f scan loop
                if (*p == '\0') break;       // 0xebce681  cmp byte ptr [rax],0 ; je short 0xEBCE691
                ++p;                         // 0xebce686  inc rax
                --n;                         // 0xebce689  dec r9d
            } while (n > 0);                 // 0xebce68c  test r9d,r9d ; jg short 0xEBCE681
        }
        // 0xebce691  sub eax,edx   (eax holds the end pointer, edx holds src)
        len = static_cast<std::int32_t>(p - src);
    }

    // Phase 3, 0xebce693..0xebce6a0: copy count = min(dstSize - 1, len), sign-extend for the call.
    //
    //   0xebce693  dec edi             ; count = dstSize - 1
    //   0xebce695  cmp eax,edi
    //   0xebce697  cmovl edi,eax       ; count = min(count, len) (signed)
    //   0xebce69a  movsxd rbx,edi
    //   0xebce69d  mov r8,rbx         ; call argument 3 = count
    std::int32_t count = dstSize - 1;        // 0xebce693  dec edi
    if (len < count) count = len;            // 0xebce695  cmp eax,edi ; cmovl edi,eax
    std::int64_t count64 = static_cast<std::int64_t>(count);  // 0xebce69a  movsxd rbx,edi

    // Phase 4, 0xebce6a0..0xebce6bb: call the copy helper, write the terminator, return.
    //
    //   0xebce6a0  call 0xEBCE390         ; sub_ebce390(dst, src, count)  -- verbatim quote above
    //   0xebce6a5  mov byte ptr [rbx+rsi],0   ; dst[count] = 0 (rsi == dst)
    //   0xebce6a9  mov eax,edi             ; return count
    //   0xebce6ab  mov rbx,[rsp+0x30]
    //   0xebce6b0  mov rsi,[rsp+0x38]
    //   0xebce6b5  add rsp,0x20
    //   0xebce6b9  pop rdi
    //   0xebce6ba  ret
    sub_ebce390(dst, src, static_cast<std::uint32_t>(count));  // 0xebce6a0  call 0xEBCE390
    dst[count64] = '\0';                       // 0xebce6a5  mov byte ptr [rbx+rsi],0
    return count;                              // 0xebce6a9  mov eax,edi ; epilogue ; ret
}

} // namespace native

LIFT_FN(sub_ebce650, "sub_ebce650", 0xEBCE650, sub_ebce650_lifted, nullptr);
