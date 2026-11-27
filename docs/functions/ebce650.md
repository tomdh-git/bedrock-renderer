# sub_ebce650 (0xebce650, size 0x6b, 1.26.62.01)

Source: src/client/features/render/native/helpers/sub_ebce650.cpp with header
src/client/features/render/native/helpers/sub_ebce650.h. First line of the .cpp:
`// LIFT 0xebce650 size 0x6b 1.26.62.01 sub_ebce650`. Registry entry:
`LIFT_FN(sub_ebce650, "sub_ebce650", 0xEBCE650, sub_ebce650_lifted, nullptr)`.

## Signature (x64 Microsoft ABI)

extern "C" int sub_ebce650(char* dst, int dstSize, SrcDesc* srcdesc, int maxlen);

Register/argument map [V] from the disassembly of 0xebce650 (rdis dis 0xebce650 0x6b):
- rcx = char* dst: output buffer, written at dst[count] after the copy (0xebce668 mov rsi,rcx; 0xebce6a5 mov byte ptr [rbx+rsi],0 with rsi == dst).
- rdx = int dstSize: copy bound; at most dstSize-1 bytes are copied (0xebce663 mov edi,edx; 0xebce693 dec edi).
- r8 = SrcDesc* srcdesc: source string at +0x00 (0xebce665 mov rdx,[r8]), length cap (int32) at +0x08 (0xebce65f cmp [r8+8],r9d; 0xebce66b cmovl r9d,[r8+8]).
- r9 = int maxlen: second length cap; bound = min(maxlen, srcdesc->maxlen).
- return = int: number of bytes copied, not counting the terminator (0xebce6a9 mov eax,edi).
- rbx, rsi, rdi are callee-saved: saved at 0xebce650..0xebce65a, restored at 0xebce6ab..0xebce6b9.

## Reversed source (complete)

// 0xebce650..0xebce670: prologue, argument copies, bound = min(maxlen, srcdesc->maxlen) (signed compare).
//   0xebce650  mov [rsp+8],rbx        ; save callee-saved registers
//   0xebce655  mov [rsp+0x10],rsi
//   0xebce65a  push rdi
//   0xebce65b  sub rsp,0x20
//   0xebce65f  cmp [r8+8],r9d         ; srcdesc->maxlen vs maxlen
//   0xebce663  mov edi,edx            ; count limit = dstSize
//   0xebce665  mov rdx,[r8]           ; src = srcdesc->ptr
//   0xebce668  mov rsi,rcx            ; save dst
//   0xebce66b  cmovl r9d,[r8+8]       ; bound = srcdesc->maxlen if smaller
field8 = srcdesc->maxlen;              // 0xebce65f  cmp [r8+8],r9d  (read +0x08 first)
src = srcdesc->ptr;                    // 0xebce665  mov rdx,[r8]     (read +0x00 second)
bound = maxlen;
if (field8 < bound) bound = field8;    // 0xebce66b  cmovl r9d,[r8+8]  (read +0x08 third)

// 0xebce670..0xebce693: null test and strnlen_s-style scan of src, bounded by `bound`.
//   0xebce670  test rdx,rdx
//   0xebce673  jne short 0xEBCE679
//   0xebce675  xor eax,eax              ; len = 0 when src == 0
//   0xebce677  jmp short 0xEBCE693
//   0xebce679  mov rax,rdx              ; p = src
//   0xebce67c  test r9d,r9d
//   0xebce67f  jle short 0xEBCE691      ; skip scan when bound <= 0
//   0xebce681  cmp byte ptr [rax],0     ; stop at NUL byte
//   0xebce684  je short 0xEBCE691
//   0xebce686  inc rax
//   0xebce689  dec r9d
//   0xebce68c  test r9d,r9d
//   0xebce68f  jg short 0xEBCE681
//   0xebce691  sub eax,edx              ; len = p - src (32-bit pointer difference)
if (src == nullptr) len = 0;
else {
    p = src; n = bound;
    if (n > 0) {
        do {
            if (*p == 0) break;
            ++p;
            --n;
        } while (n > 0);
    }
    len = (int32_t)(p - src);
}

// 0xebce693..0xebce6a0: copy count = min(dstSize - 1, len) (signed), sign-extend for the call.
//   0xebce693  dec edi             ; count = dstSize - 1
//   0xebce695  cmp eax,edi
//   0xebce697  cmovl edi,eax       ; count = min(count, len)
//   0xebce69a  movsxd rbx,edi
//   0xebce69d  mov r8,rbx         ; call argument 3 = count
count = dstSize - 1;
if (len < count) count = len;
count64 = (int64_t)count;

// 0xebce6a0..0xebce6bb: call the lift-set copy helper, write the terminator, return.
//   0xebce6a0  call 0xEBCE390         ; sub_ebce390(dst, src, count)
0xebce6a0  call 0xEBCE390
sub_ebce390(dst, src, (uint32_t)count);
//   0xebce6a5  mov byte ptr [rbx+rsi],0   ; dst[count] = 0 (rsi == dst)
dst[count64] = 0;
//   0xebce6a9  mov eax,edi             ; return count
//   0xebce6ab  mov rbx,[rsp+0x30]
//   0xebce6b0  mov rsi,[rsp+0x38]
//   0xebce6b5  add rsp,0x20
//   0xebce6b9  pop rdi
//   0xebce6ba  ret
return count;

// Full verbatim instruction listing of [0xebce650, 0xebce6bb) (size 0x6b), rdis dis 0xebce650 0x6b:
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

Every instruction of [0xebce650, 0xebce6bb) is inside one of the cited ranges above (or quoted
verbatim), and the only `call` instruction (0xebce6a0) is quoted verbatim.

## Struct fields touched

| field | offset | size | dir | meaning | tag |
|---|---|---|---|---|---|
| SrcDesc::ptr | 0x00 | 8 | R | source string pointer | [V] 0xebce665 mov rdx,[r8] |
| SrcDesc::maxlen | 0x08 | 4 | R | source length cap, signed-compared against maxlen | [V] 0xebce65f cmp [r8+8],r9d; 0xebce66b cmovl r9d,[r8+8] |

Writes: dst[0..count) by sub_ebce390 (the callee), dst[count] = 0 by this function (0xebce6a5).
No struct field is written by this function.

## Callees

- 0xEBCE390 sub_ebce390 (0xebce390, size 0x5): lift set ([V] docs/data/native_functions.tsv and
  docs/data/native_boundary.tsv class `lift`; lifted source sub_ebce390.cpp/h). Called directly as
  `sub_ebce390(dst, src, count)` with the same register arguments; the fourth register (r9 = maxlen)
  is set by the caller but unread by the tail-forwarding callee (its signature is (void*, void*, uint32_t)).
  Not a boundary wrapper, not unresolved.

No other calls; the function is otherwise a leaf.

## Open questions

none.

## Version anchors

Minecraft Bedrock 1.26.62.01; RVAs relative to the image base. Evidence: `rdis dis 0xebce650 0x6b`;
docs/data/native_functions.tsv row `0xebce650 0x6b 0 7 root D0 added 0xebce650`; the function ends at
the `ret` at 0xebce6ba, followed by int3 padding at 0xebce6bb (size 0x6b = [0xebce650, 0xebce6bb)).
