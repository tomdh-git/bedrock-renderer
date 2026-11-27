# Function 0xEBD18F0 (sub_ebd18f0)

## Signature
```cpp
// LIFT 0xebd18f0 size 0xb9 1.26.62.01 sub_ebd18f0
extern "C" void sub_ebd18f0(
    void* dest,           // RCX
    int dest_stride,      // RDX
    uint32_t inner_count, // R8  (element count per row, must be multiple of 4 for fast path)
    uint32_t outer_count, // R9  (row count)
    void* unused_arg5,    // [RSP+0x20] home space (overwritten to save RBX)
    const void* src,      // [RSP+0x28] arg6
    int src_stride        // [RSP+0x30] arg7 (low 32 bits used)
);
```

## Register/Argument Map
| Register | Meaning | Source |
|----------|---------|--------|
| RCX | dest pointer | [V] 0xEBD18FC `mov rbx,rcx` |
| RDX | dest_stride (bytes per row) | [V] 0xEBD1949 `mov edi,edx` / 0xEBD1993 `add rbx,rdi` |
| R8 | inner_count (elements per row) | [V] 0xEBD18FF `mov esi,r8d` / 0xEBD1938 `shr esi,2` |
| R9 | outer_count (rows) | [V] 0xEBD193B `test r9d,r9d` / 0xEBD19C0 `mov ebp,r9d` |
| [RSP+0x28] entry | src pointer | [V] 0xEBD18F7 `mov r11,[rsp+0x38]` (post-push = entry+0x28) |
| [RSP+0x30] entry | src_stride (int32) | [V] 0xEBD1944 `mov r10d,[rsp+0x40]` (post-push = entry+0x30) |

## Reversed source (complete)

### 0xEBD18F0..0xEBD1938: Prologue & Alignment Checks
```cpp
// 0xEBD18F0..0xEBD1938
// Save non-volatile registers, check alignment and minimum count for fast path
mov [rsp+0x20], rbx        // 0xEBD18F0  mov [rsp+0x20],rbx
push rsi                   // 0xEBD18F5  push rsi
push rdi                   // 0xEBD18F6  push rdi
mov r11, [rsp+0x38]        // 0xEBD18F7  mov r11,[rsp+0x38]  ; src (arg6)
mov rbx, rcx               // 0xEBD18FC  mov rbx,rcx         ; dest
mov esi, r8d               // 0xEBD18FF  mov esi,r8d         ; inner_count
test r8b, 3                // 0xEBD1902  test r8b,3          ; inner_count % 4 != 0?
jne 0xEBD19A4              // 0xEBD1906  jne 0xEBD19A4       ; -> slow path
cmp esi, 4                 // 0xEBD190C  cmp esi,4           ; inner_count < 4?
jb 0xEBD19A4               // 0xEBD190F  jb 0xEBD19A4        ; -> slow path
test r11b, 0xF             // 0xEBD1915  test r11b,0xF       ; src % 16 != 0?
jne 0xEBD19A4              // 0xEBD1919  jne 0xEBD19A4       ; -> slow path
test cl, 0xF               // 0xEBD191F  test cl,0xF         ; dest % 16 != 0?
jne 0xEBD19A4              // 0xEBD1922  jne 0xEBD19A4       ; -> slow path
movdqa xmm3, [0xEECB5D0]   // 0xEBD1928  movdqa xmm3,[0xEECB5D0] ; mask 0xFF00FF00...
movdqa xmm4, [0xEF40D90]   // 0xEBD1930  movdqa xmm4,[0xEF40D90] ; mask 0x00FF00FF...
shr esi, 2                 // 0xEBD1938  shr esi,2           ; inner_count /= 4 (dword chunks)
```

### 0xEBD193B..0xEBD194E: Fast Path Setup / Early Exit
```cpp
// 0xEBD193B..0xEBD194E
test r9d, r9d              // 0xEBD193B  test r9d,r9d        ; outer_count == 0?
je 0xEBD1A1B               // 0xEBD193E  je 0xEBD1A1B        ; -> early exit
mov r10d, [rsp+0x40]       // 0xEBD1944  mov r10d,[rsp+0x40] ; src_stride (arg7)
mov edi, edx               // 0xEBD1949  mov edi,edx         ; dest_stride
mov r8d, r9d               // 0xEBD194B  mov r8d,r9d         ; outer_count loop counter
xchg ax, ax                // 0xEBD194E  xchg ax,ax          ; nop alignment
```

### 0xEBD1950..0xEBD199A: Fast Path (Aligned SIMD)
```cpp
// 0xEBD1950..0xEBD199A
// Outer loop: for each row (r8d times)
loc_ebd1950:               // 0xEBD1950  mov rax,r11         ; rax = src
    mov rax, r11
    test esi, esi          // 0xEBD1953  test esi,esi        ; inner_chunks == 0?
    je short 0xEBD1990     // 0xEBD1955  je short 0xEBD1990  ; skip inner loop
    mov rcx, rbx           // 0xEBD1957  mov rcx,rbx         ; rcx = dest
    mov edx, esi           // 0xEBD195A  mov edx,esi         ; edx = inner_chunks
    sub rcx, r11           // 0xEBD195C  sub rcx,r11         ; rcx = dest - src
    nop                    // 0xEBD195F  nop

// Inner loop: process 4 dwords (16 bytes) per iteration
loc_ebd1960:               // 0xEBD1960  movups xmm1,[rax]   ; load 16 bytes from src
    movups xmm1, [rax]
    lea rax, [rax+0x10]    // 0xEBD1963  lea rax,[rax+0x10]  ; src += 16
    movdqa xmm2, xmm1      // 0xEBD1967  movdqa xmm2,xmm1
    movdqa xmm0, xmm1      // 0xEBD196B  movdqa xmm0,xmm1
    pslld xmm2, 0x10       // 0xEBD196F  pslld xmm2,0x10     ; swap 16-bit halves (<<16)
    andps xmm1, xmm3       // 0xEBD1974  andps xmm1,xmm3     ; xmm1 &= 0xFF00FF00...
    psrld xmm0, 0x10       // 0xEBD1977  psrld xmm0,0x10     ; swap 16-bit halves (>>16)
    orps xmm2, xmm0        // 0xEBD197C  orps xmm2,xmm0      ; xmm2 = swapped halves
    andps xmm2, xmm4       // 0xEBD197F  andps xmm2,xmm4     ; xmm2 &= 0x00FF00FF...
    orps xmm2, xmm1        // 0xEBD1982  orps xmm2,xmm1      ; combine
    movups [rcx+rax-0x10], xmm2 // 0xEBD1985  movups [rcx+rax-0x10],xmm2 ; store to dest
    sub rdx, 1             // 0xEBD198A  sub rdx,1
    jne short 0xEBD1960    // 0xEBD198E  jne short 0xEBD1960 ; next chunk

// End of row: advance pointers
loc_ebd1990:               // 0xEBD1990  add r11,r10         ; src += src_stride
    add r11, r10
    add rbx, rdi           // 0xEBD1993  add rbx,rdi         ; dest += dest_stride
    sub r8, 1              // 0xEBD1996  sub r8,1            ; outer_count--
    jne short 0xEBD1950    // 0xEBD199A  jne short 0xEBD1950 ; next row
```

### 0xEBD199C..0xEBD19A3: Epilogue (Fast Path Return)
```cpp
// 0xEBD199C..0xEBD19A3
mov rbx, [rsp+0x30]       // 0xEBD199C  mov rbx,[rsp+0x30]  ; restore RBX
pop rdi                   // 0xEBD19A1  pop rdi
pop rsi                   // 0xEBD19A2  pop rsi
ret                       // 0xEBD19A3  ret
```

### 0xEBD19A4..0xEBD1A1A: Slow Path (Unaligned Scalar)
```cpp
// 0xEBD19A4..0xEBD1A1A
// Entry from alignment check failures
loc_ebd19a4:               // 0xEBD19A4  test r9d,r9d        ; outer_count == 0?
    test r9d, r9d
    je short 0xEBD1A1B    // 0xEBD19A7  je short 0xEBD1A1B  ; -> early exit
    mov [rsp+0x18], rbp   // 0xEBD19A9  mov [rsp+0x18],rbp  ; save RBP
    mov [rsp+0x20], r14   // 0xEBD19AE  mov [rsp+0x20],r14  ; save R14
    mov r14d, [rsp+0x40]  // 0xEBD19B3  mov r14d,[rsp+0x40] ; src_stride
    mov [rsp+0x28], r15   // 0xEBD19B8  mov [rsp+0x28],r15  ; save R15
    mov r15d, edx         // 0xEBD19BD  mov r15d,edx        ; dest_stride
    mov ebp, r9d          // 0xEBD19C0  mov ebp,r9d         ; outer_count

// Outer loop
loc_ebd19c3:               // 0xEBD19C3  test esi,esi        ; inner_count == 0?
    test esi, esi
    je short 0xEBD1A00    // 0xEBD19C5  je short 0xEBD1A00  ; skip inner
    mov rdi, r11          // 0xEBD19C7  mov rdi,r11         ; rdi = src
    lea rax, [rbx+2]      // 0xEBD19CA  lea rax,[rbx+2]     ; rax = dest + 2
    sub rdi, rbx          // 0xEBD19CE  sub rdi,rbx         ; rdi = src - dest
    mov r10, rsi          // 0xEBD19D1  mov r10,rsi         ; inner loop counter

// Inner loop: process 4 bytes per iteration with byte permutation
loc_ebd19d4:               // 0xEBD19D4  movzx r9d,byte ptr [rdi+rax-2] ; src[0]
    movzx r9d, byte ptr [rdi+rax-2]
    movzx edx, byte ptr [rdi+rax-1] // 0xEBD19DA  movzx edx,byte ptr [rdi+rax-1] ; src[1]
    movzx r8d, byte ptr [rdi+rax+1] // 0xEBD19DF  movzx r8d,byte ptr [rdi+rax+1] ; src[3]
    movzx ecx, byte ptr [rdi+rax]   // 0xEBD19E5  movzx ecx,byte ptr [rdi+rax]   ; src[2]
    mov [rax-2], cl       // 0xEBD19E9  mov [rax-2],cl      ; dest[0] = src[2]
    mov [rax-1], dl       // 0xEBD19EC  mov [rax-1],dl      ; dest[1] = src[1]
    mov [rax], r9b        // 0xEBD19EF  mov [rax],r9b       ; dest[2] = src[0]
    mov [rax+1], r8b      // 0xEBD19F2  mov [rax+1],r8b     ; dest[3] = src[3]
    lea rax, [rax+4]      // 0xEBD19F6  lea rax,[rax+4]     ; dest += 4
    sub r10, 1            // 0xEBD19FA  sub r10,1
    jne short 0xEBD19D4   // 0xEBD19FE  jne short 0xEBD19D4 ; next chunk

// End of row
loc_ebd1a00:               // 0xEBD1A00  add r11,r14         ; src += src_stride
    add r11, r14
    add rbx, r15          // 0xEBD1A03  add rbx,r15         ; dest += dest_stride
    sub rbp, 1            // 0xEBD1A06  sub rbp,1           ; outer_count--
    jne short 0xEBD19C3   // 0xEBD1A0A  jne short 0xEBD19C3 ; next row

// Slow path epilogue
    mov r15, [rsp+0x28]   // 0xEBD1A0C  mov r15,[rsp+0x28]  ; restore R15
    mov r14, [rsp+0x20]   // 0xEBD1A11  mov r14,[rsp+0x20]  ; restore R14
    mov rbp, [rsp+0x18]   // 0xEBD1A16  mov rbp,[rsp+0x18]  ; restore RBP
```

### 0xEBD1A1B..0xEBD1A22: Common Exit
```cpp
// 0xEBD1A1B..0xEBD1A22
loc_ebd1a1b:               // 0xEBD1A1B  mov rbx,[rsp+0x30]  ; restore RBX (saved at entry)
    mov rbx, [rsp+0x30]
    pop rdi                // 0xEBD1A20  pop rdi
    pop rsi                // 0xEBD1A21  pop rsi
    ret                    // 0xEBD1A22  ret
```

## Constants
| RVA | Value (16 bytes) | Use |
|-----|------------------|-----|
| 0xEECB5D0 | `00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF` (xmm3 = 0xFF00FF00 per dword) | Fast path mask for high byte of each 16-bit word |
| 0xEF40D90 | `FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00 FF 00` (xmm4 = 0x00FF00FF per dword) | Fast path mask for low byte of each 16-bit word |

## Struct Fields Touched
None (raw pointer manipulation only).

## Callees
None in the 0xEBD18F0..0xEBD19A9 range. The chained fragments at 0xEBD19A9+ contain calls to:
- 0xEBCE3A0 (sub_ebce3a0, classified `lift`)
- 0xEBCD6F0 (sub_ebcd6f0, classified `crt`)
- 0xEBD15B0 (sub_ebd15b0, classified `lift`)
- 0xEBCE390 (sub_ebce390, classified `lift` per auto-unresolved)

But these are **outside** the 0xB9-byte function body and belong to a different function (sub_ebd1a30 at 0xEBD1A30).

## Callers
- 0xE7F5380 (sub_e7f5380)
- 0xE803640 (sub_e803640)
- 0xE818050 (sub_e818050)
- 0xE85E5C0 (sub_e85e5c0)
- 0xE868120 (sub_e868120)
- 0xEBD21C0 (sub_ebd21c0)

## Ownership / Threading
Pure memory transformation function. No locks, no shared state. Reads from `src` (const), writes to `dest`. Safe for concurrent use on disjoint buffers.

## Verification
- Instruction coverage: 0xEBD18F0..0xEBD19A9 (0xB9 bytes) fully covered.
- No calls within this range.
- All constants verified from exe data sections.
- Alignment checks match fast/slow path selection logic.

## Layout Assertions
```cpp
// Verified from exe .rdata section
static_assert(sizeof(__m128i) == 16, "__m128i must be 16 bytes");
// Shuffle mask at 0xEECB5D0: each dword = 0xFF00FF00 (high byte of each 16-bit word)
// Shuffle mask at 0xEF40D90: each dword = 0x00FF00FF (low byte of each 16-bit word)
// These are loaded at runtime from the exe image base.
```