# sub_bc7f6e0

- RVA: 0xbc7f6e0
- Size: 0x1a82
- Range: 0xbc7f6e0..0xbc81162
- Name: VV frame-graph builder (data file)
- Chunks: docs/data/native_chunks/bc7f6e0.tsv (2 chunks, <=0x1800)
- Frame size / saved regs / arg map / locals / jump tables: TBD (not yet collected)

## Reversed source (complete)

### Chunk 2: 0xbc80ed3..0xbc81162

This chunk computes FNV-1a 64-bit hashes over a scratch buffer (rsi, length rdx) in four variants, then stores the hash to a global slot, resets a string object via `sub_73150` (STL), assigns a global counter via `sub_e938d70` (OS), loads a context pointer from `[rbp+0x308]`, and jumps to one of four tail functions (`sub_bc7f920`, `sub_bc7f945`, `sub_bc7f96a`, `sub_bc7f98f`).

**Entry state at 0xbc80ed3** (per docs/data/native_chunks/bc7f6e0.tsv): rbp frame established; live registers rax,rcx,rdx,r8,r9,r10,r11,rbx,rsi,rdi,r12,r13,r14,r15 and stack locals.

**Variant 1 (0xbc80ed3..0xbc80f62)**:
```
// 0xbc80ed3..0xbc80f0d: main 4-byte FNV-1a loop
while (r8 < rdx) {
    r10 = *(uint8_t*)(rsi + r8); r10 ^= rcx; r10 *= r9;
    rcx = *(uint8_t*)(rsi + r8 + 1); rcx ^= r10; rcx *= r9;
    r10 = *(uint8_t*)(rsi + r8 + 2); r10 ^= rcx; r10 *= r9;
    rcx = *(uint8_t*)(rsi + r8 + 3); rcx ^= r10; rcx *= r9;
    r8 += 4;
}
0xbc80f0f  test rax,rax
0xbc80f12  je short 0xBC80F3C

// 0xbc80f14..0xbc80f3a: tail byte loop (if rax != 0)
rsi += r8; rdx = 0; r8 = 0x100000001B3; r9 = rcx;
while (rdx < rax) {
    rcx = *(uint8_t*)(rsi + rdx); rcx ^= r9; rcx *= r8; rdx++; r9 = rcx;
}
0xbc80f3c  mov [0x12AE1868],rcx
0xbc80f43  lea rcx,[rbp+0x90]
0xbc80f4a  call 0x73150
0xbc80f4f  lea rcx,[0x12AE1870]
0xbc80f56  call 0xE938D70
0xbc80f5b  mov rdi,[rbp+0x308]
0xbc80f62  jmp 0xBC7F920
```

**Variant 2 (0xbc80f67..0xbc81010)**:
```
// 0xbc80f67..0xbc80fbc: main 4-byte loop (rdx masked to 4-byte boundary)
rdx &= ~3; rcx = 0xCBF29CE484222325; r8 = 0; r9 = 0x100000001B3;
while (r8 < rdx) {
    r10 = *(uint8_t*)(rsi + r8); r10 ^= rcx; r10 *= r9;
    rcx = *(uint8_t*)(rsi + r8 + 1); rcx ^= r10; rcx *= r9;
    r10 = *(uint8_t*)(rsi + r8 + 2); r10 ^= rcx; r10 *= r9;
    rcx = *(uint8_t*)(rsi + r8 + 3); rcx ^= r10; rcx *= r9;
    r8 += 4;
}
0xbc80fbe  test rax,rax
0xbc80fc1  je short 0xBC80FEB

// 0xbc80fc3..0xbc80fe9: tail byte loop
rsi += r8; rdx = 0; r8 = 0x100000001B3; r9 = rcx;
while (rdx < rax) {
    rcx = *(uint8_t*)(rsi + rdx); rcx ^= r9; rcx *= r8; rdx++; r9 = rcx;
}
0xbc80feb  mov [0x12AE1878],rcx
0xbc80ff2  lea rcx,[rbp+0x90]
0xbc80ff9  call 0x73150
0xbc80ffe  lea rcx,[0x12AE1880]
0xbc81005  call 0xE938D70
0xbc8100a  mov rdi,[rbp+0x308]
0xbc81011  jmp 0xBC7F945
```

**Variant 3 (0xbc81016..0xbc810bf)**:
```
// 0xbc81016..0xbc8106b: main 4-byte loop
rdx &= ~3; rcx = 0xCBF29CE484222325; r8 = 0; r9 = 0x100000001B3;
while (r8 < rdx) {
    r10 = *(uint8_t*)(rsi + r8); r10 ^= rcx; r10 *= r9;
    rcx = *(uint8_t*)(rsi + r8 + 1); rcx ^= r10; rcx *= r9;
    r10 = *(uint8_t*)(rsi + r8 + 2); r10 ^= rcx; r10 *= r9;
    rcx = *(uint8_t*)(rsi + r8 + 3); rcx ^= r10; rcx *= r9;
    r8 += 4;
}
0xbc8106d  test rax,rax
0xbc81070  je short 0xBC8109A

// 0xbc81072..0xbc81098: tail byte loop
rsi += r8; rdx = 0; r8 = 0x100000001B3; r9 = rcx;
while (rdx < rax) {
    rcx = *(uint8_t*)(rsi + rdx); rcx ^= r9; rcx *= r8; rdx++; r9 = rcx;
}
0xbc8109a  mov [0x12AE1888],rcx
0xbc810a1  lea rcx,[rbp+0x90]
0xbc810a8  call 0x73150
0xbc810ad  lea rcx,[0x12AE1890]
0xbc810b4  call 0xE938D70
0xbc810b9  mov rdi,[rbp+0x308]
0xbc810c0  jmp 0xBC7F96A
```

**Variant 4 (0xbc810c5..0xbc8115d)**:
```
// 0xbc810c5..0xbc81110: main 4-byte loop (registers swapped: r8=len, r9=hash, rcx=prime)
r8 &= ~3; rdx = 0xCBF29CE484222325; r9 = 0;
while (r9 < r8) {
    r10 = *(uint8_t*)(rsi + r9); r10 ^= rdx; r10 *= rcx;
    rdx = *(uint8_t*)(rsi + r9 + 1); rdx ^= r10; rdx *= rcx;
    r10 = *(uint8_t*)(rsi + r9 + 2); r10 ^= rdx; r10 *= rcx;
    rdx = *(uint8_t*)(rsi + r9 + 3); rdx ^= r10; rdx *= rcx;
    r9 += 4;
}
0xbc81112  test rax,rax
0xbc81115  je short 0xBC81137

// 0xbc81117..0xbc81135: tail byte loop
rsi += r9; r8 = 0; r9 = rdx;
while (r8 < rax) {
    rdx = *(uint8_t*)(rsi + r8); rdx ^= r9; rdx *= rcx; r8++; r9 = rdx;
}
0xbc81137  mov [0x12AE1898],rdx
0xbc8113e  lea rcx,[rbp+0x90]
0xbc81145  call 0x73150
0xbc8114a  lea rcx,[0x12AE18A0]
0xbc81151  call 0xE938D70
0xbc81156  mov rdi,[rbp+0x308]
0xbc8115d  jmp 0xBC7F98F
```

**Calls in chunk range [0xbc80ed3, 0xbc81162)**:
- 0xbc80f4a  call 0x73150                ; -> sub_73150 (STL string reset)
- 0xbc80f56  call 0xE938D70              ; -> sub_e938d70 (OS global counter assign)
- 0xbc80ff9  call 0x73150                ; -> sub_73150
- 0xbc80ffe  call 0xE938D70              ; -> sub_e938d70
- 0xbc810a8  call 0x73150                ; -> sub_73150
- 0xbc810b4  call 0xE938D70              ; -> sub_e938d70
- 0xbc81145  call 0x73150                ; -> sub_73150
- 0xbc81151  call 0xE938D70              ; -> sub_e938d70

All 8 calls target boundary functions (0x73150=stl, 0xe938d70=os per docs/data/native_boundary.tsv). No UNRESOLVED calls.

**Global slots written**: 0x12AE1868, 0x12AE1878, 0x12AE1888, 0x12AE1898 (FNV hash results).
**Stack slot read**: [rbp+0x308] -> rdi (context pointer passed to tail functions).

## Chunk state

Per docs/data/native_chunks/bc7f6e0.tsv, the live state at chunk boundary 0xbc80ed3 is:
- rbp frame base
- All general-purpose registers (rax,rcx,rdx,r8,r9,r10,r11,rbx,rsi,rdi,r12,r13,r14,r15) and stack locals

This is modeled in `src/client/features/render/native/bgfx/sub_bc7f6e0_chunk_c01.h` as `ChunkState_bc7f6e0_c01`.

## Callees (lift set)
- 0x9b020, 0x5668ac0, 0x5679db0, 0x567c8b0, 0x5698290, 0xbc81930, 0xe86b370

## Callees (outside, boundary)
- 0x73150 (stl), 0x79580 (stl), 0x9b250 (stl), 0x76ad00 (stl), 0x9bc830 (alloc), 0xe935740 (os), 0xe938cb0 (os), 0xe938d70 (os), 0xe935700 (lift)