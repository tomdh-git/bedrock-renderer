## NEXT
DONE

# U-Am7 — atlas_meta_parse slice 0x4e1bc37..0x4e1bff2 (Minecraft.Windows.exe 1.26.62.01, image-base RVAs)

All 230 instructions from docs/progress/_part_Am7.txt (slice 0x4e1bc37..0x4e1bff2, chunk 7 of 7 of atlas_meta_parse_4e1a0a0_4e1bff4) are covered below,
split into 12 phases of at most 40 instructions each. Every instruction line is quoted verbatim from the input data; no instruction is skipped.
No live data was used; this is static analysis only. Meanings in the field map are '-' unless an instruction or string shows them.

### Phase 1: 0x4E1BC37..0x4E1BC5E: Two exit tails of the surrounding function sit at the head of this slice: with rdx=0 it calls 0xEEC6ED0 and jumps back to 0x4E1BAC4; with rdx=1 it calls 0x4E5F790 on [rbp+0x2F8] and jumps to 0x4E1BAD6.

0x4E1BC37  mov rdi,rdx
0x4E1BC3A  xor edx,edx
0x4E1BC3C  mov r8,rsi
0x4E1BC3F  call 0xEEC6ED0
0x4E1BC44  add rsi,rdi
0x4E1BC47  jmp 0x4E1BAC4
0x4E1BC4C  mov edx,1
0x4E1BC51  lea rcx,[rbp+0x2F8]
0x4E1BC58  call 0x4E5F790
0x4E1BC5D  nop
0x4E1BC5E  jmp 0x4E1BAD6

### Phase 2: 0x4E1BC63..0x4E1BCB2: The main block zeroes [rbp+0x320] with movups, then releases [rbp+0x328]: lock-dec [rsi+8]; if nonzero it jumps to 0x4E1BCB2, otherwise the first destructor slot runs through indirect call [0xF99FFA0] and lock-dec [rsi+0xC] follows.

0x4E1BC63  xorps xmm0,xmm0
0x4E1BC66  mov rsi,[rbp+0x328]
0x4E1BC6D  movups [rbp+0x320],xmm0
0x4E1BC74  test rsi,rsi
0x4E1BC77  mov rdi,[rbp+0x338]
0x4E1BC7E  mov r14,[rbp+0x2C0]
0x4E1BC85  je short 0x4E1BCF4
0x4E1BC87  lock dec dword ptr [rsi+8]
0x4E1BC8B  jne short 0x4E1BCB2
0x4E1BC8D  mov rax,[rsi]
0x4E1BC90  mov rax,[rax]
0x4E1BC93  mov rcx,rsi
0x4E1BC96  call qword ptr [0xF99FFA0]
0x4E1BC9C  lock dec dword ptr [rsi+0xC]
0x4E1BCA0  jne short 0x4E1BCB2
0x4E1BCA2  mov rax,[rsi]
0x4E1BCA5  mov rax,[rax+8]
0x4E1BCA9  mov rcx,rsi
0x4E1BCAC  call qword ptr [0xF99FFA0]
0x4E1BCB2  mov rsi,[rbp+0x328]

--- end of piece 1/4 (31 instructions) ---

### Phase 3: 0x4E1BCB9..0x4E1BCFB: At 0x4E1BCB2 [rbp+0x328] is reloaded and [rbp+0x330] is null-stored; if still non-null, [rsi+8] is lock-decremented and on zero both destructor slots run ([rax] then [rax+8]) before lock-dec [rsi+0xC]; all paths merge at 0x4E1BCF4 where byte [rbp+0x318] is compared to 1.

0x4E1BCB9  mov qword ptr [rbp+0x330],0
0x4E1BCC4  test rsi,rsi
0x4E1BCC7  je short 0x4E1BCF4
0x4E1BCC9  lock dec dword ptr [rsi+8]
0x4E1BCCD  jne short 0x4E1BCF4
0x4E1BCCF  mov rax,[rsi]
0x4E1BCD2  mov rax,[rax]
0x4E1BCD5  mov rcx,rsi
0x4E1BCD8  call qword ptr [0xF99FFA0]
0x4E1BCDE  lock dec dword ptr [rsi+0xC]
0x4E1BCE2  jne short 0x4E1BCF4
0x4E1BCE4  mov rax,[rsi]
0x4E1BCE7  mov rax,[rax+8]
0x4E1BCEB  mov rcx,rsi
0x4E1BCEE  call qword ptr [0xF99FFA0]
0x4E1BCF4  cmp byte ptr [rbp+0x318],1
0x4E1BCFB  jne short 0x4E1BD09

### Phase 4: 0x4E1BCFD..0x4E1BD44: If [rbp+0x318]==1, 0x3B2020 is called with [rbp+0x310]; [rbp+0x288] is then zeroed with movups and [rbp+0x290] is released: lock-dec [rsi+8], jumping to 0x4E1BD4A when nonzero, otherwise both destructor slots run.

0x4E1BCFD  mov rcx,[rbp+0x310]
0x4E1BD04  call 0x3B2020
0x4E1BD09  xorps xmm0,xmm0
0x4E1BD0C  mov rsi,[rbp+0x290]
0x4E1BD13  movups [rbp+0x288],xmm0
0x4E1BD1A  test rsi,rsi
0x4E1BD1D  je short 0x4E1BD8C
0x4E1BD1F  lock dec dword ptr [rsi+8]
0x4E1BD23  jne short 0x4E1BD4A
0x4E1BD25  mov rax,[rsi]
0x4E1BD28  mov rax,[rax]
0x4E1BD2B  mov rcx,rsi
0x4E1BD2E  call qword ptr [0xF99FFA0]
0x4E1BD34  lock dec dword ptr [rsi+0xC]
0x4E1BD38  jne short 0x4E1BD4A
0x4E1BD3A  mov rax,[rsi]
0x4E1BD3D  mov rax,[rax+8]
0x4E1BD41  mov rcx,rsi
0x4E1BD44  call qword ptr [0xF99FFA0]

### Phase 5: 0x4E1BD4A..0x4E1BD9C: [rbp+0x290] is reloaded, [rbp+0x298] is null-stored, and on the zero path [rsi+0xC] is lock-decremented with both destructors before merging at 0x4E1BD8C; byte [rbp+0x280] is then compared to 1 and, if equal, 0x3B2020 is called on [rbp+0x278].

0x4E1BD4A  mov rsi,[rbp+0x290]
0x4E1BD51  mov qword ptr [rbp+0x298],0
0x4E1BD5C  test rsi,rsi
0x4E1BD5F  je short 0x4E1BD8C
0x4E1BD61  lock dec dword ptr [rsi+8]
0x4E1BD65  jne short 0x4E1BD8C
0x4E1BD67  mov rax,[rsi]
0x4E1BD6A  mov rax,[rax]
0x4E1BD6D  mov rcx,rsi
0x4E1BD70  call qword ptr [0xF99FFA0]
0x4E1BD76  lock dec dword ptr [rsi+0xC]
0x4E1BD7A  jne short 0x4E1BD8C
0x4E1BD7C  mov rax,[rsi]
0x4E1BD7F  mov rax,[rax+8]
0x4E1BD83  mov rcx,rsi
0x4E1BD86  call qword ptr [0xF99FFA0]
0x4E1BD8C  cmp byte ptr [rbp+0x280],1
0x4E1BD93  jne short 0x4E1BDA1
0x4E1BD95  mov rcx,[rbp+0x278]
0x4E1BD9C  call 0x3B2020

### Phase 6: 0x4E1BDA1..0x4E1BDF0: [rbp+0x2B8] is released the same way (test, lock-dec [rsi+8], destructors via [0xF99FFA0] on zero, merge at 0x4E1BDD8); [rbp+0xE0] is zeroed with movaps and [rbp+0x428] is loaded so [rcx+8] can be lock-incremented if nonzero.

0x4E1BDA1  mov rsi,[rbp+0x2B8]
0x4E1BDA8  test rsi,rsi
0x4E1BDAB  je short 0x4E1BDD8
0x4E1BDAD  lock dec dword ptr [rsi+8]
0x4E1BDB1  jne short 0x4E1BDD8
0x4E1BDB3  mov rax,[rsi]
0x4E1BDB6  mov rax,[rax]
0x4E1BDB9  mov rcx,rsi
0x4E1BDBC  call qword ptr [0xF99FFA0]
0x4E1BDC2  lock dec dword ptr [rsi+0xC]
0x4E1BDC6  jne short 0x4E1BDD8
0x4E1BDC8  mov rax,[rsi]
0x4E1BDCB  mov rax,[rax+8]
0x4E1BDCF  mov rcx,rsi
0x4E1BDD2  call qword ptr [0xF99FFA0]
0x4E1BDD8  xorps xmm0,xmm0
0x4E1BDDB  movaps [rbp+0xE0],xmm0
0x4E1BDE2  mov rcx,[rbp+0x428]
0x4E1BDE9  mov rax,[rcx+8]
0x4E1BDED  test rax,rax
0x4E1BDF0  je short 0x4E1BDFC

--- end of piece 2/4 (108 instructions) ---

### Phase 7: 0x4E1BDF2..0x4E1BE43: The [rcx+8] increment result (or zero) is stored: [rbp+0xE0]=[rcx], [rbp+0xE8]=rax; [rbp+0xF0] is zeroed with movaps and the same reference-count increment is performed for [rbp+0x420]'s [rcx+8], stored into [rbp+0xF0] and [rbp+0xF8].

0x4E1BDF2  lock inc dword ptr [rax+8]
0x4E1BDF6  mov rax,[rcx+8]
0x4E1BDFA  jmp short 0x4E1BDFE
0x4E1BDFC  xor eax,eax
0x4E1BDFE  mov rdx,[rbp+0x400]
0x4E1BE05  mov rcx,[rcx]
0x4E1BE08  mov [rbp+0xE0],rcx
0x4E1BE0F  mov [rbp+0xE8],rax
0x4E1BE16  movaps [rbp+0xF0],xmm0
0x4E1BE1D  mov rcx,[rbp+0x420]
0x4E1BE24  mov rax,[rcx+8]
0x4E1BE28  test rax,rax
0x4E1BE2B  je short 0x4E1BE37
0x4E1BE2D  lock inc dword ptr [rax+8]
0x4E1BE31  mov rax,[rcx+8]
0x4E1BE35  jmp short 0x4E1BE39
0x4E1BE37  xor eax,eax
0x4E1BE39  mov rcx,[rcx]
0x4E1BE3C  mov [rbp+0xF0],rcx
0x4E1BE43  mov [rbp+0xF8],rax

### Phase 8: 0x4E1BE4A..0x4E1BE99: [rbp+0x60] is zeroed, then [rdx+0x38] (rdx=[rbp+0x400]) is called indirectly through [0xF99FFA0] with rdx=[rbp+0x28], result stored at [rbp+0x60]; similarly [rbp+0x338]->[rdi+0x38] is called with rdx=[rbp-0x30] and stored at [rbp+8] after zeroing it.

0x4E1BE4A  mov qword ptr [rbp+0x60],0
0x4E1BE52  mov rcx,[rdx+0x38]
0x4E1BE56  test rcx,rcx
0x4E1BE59  je short 0x4E1BE77
0x4E1BE5B  mov rax,[rcx]
0x4E1BE5E  mov rax,[rax]
0x4E1BE61  lea rdx,[rbp+0x28]
0x4E1BE65  call qword ptr [0xF99FFA0]
0x4E1BE6B  nop
0x4E1BE6C  mov [rbp+0x60],rax
0x4E1BE70  mov rdi,[rbp+0x338]
0x4E1BE77  mov qword ptr [rbp+8],0
0x4E1BE7F  mov rcx,[rdi+0x38]
0x4E1BE83  test rcx,rcx
0x4E1BE86  je short 0x4E1BE9D
0x4E1BE88  mov rax,[rcx]
0x4E1BE8B  mov rax,[rax]
0x4E1BE8E  lea rdx,[rbp-0x30]
0x4E1BE92  call qword ptr [0xF99FFA0]
0x4E1BE98  nop
0x4E1BE99  mov [rbp+8],rax

### Phase 9: 0x4E1BE9D..0x4E1BEFB: [rbp+0xD0] is zeroed with movaps; [rbp+0x408] is refcount-incremented and stored as [rbp+0xD0]=[rcx], [rbp+0xD8]=rax; four call arguments are staged on the stack: [rsp+0x38]=[rbp+0xE0], [rsp+0x30]=[rbp+0xF0], byte [rbp+0x410]->[rsp+0x28], [rbp+0x28]->[rsp+0x20].

0x4E1BE9D  xorps xmm0,xmm0
0x4E1BEA0  movaps [rbp+0xD0],xmm0
0x4E1BEA7  mov rcx,[rbp+0x408]
0x4E1BEAE  mov rax,[rcx+8]
0x4E1BEB2  test rax,rax
0x4E1BEB5  je short 0x4E1BEC1
0x4E1BEB7  lock inc dword ptr [rax+8]
0x4E1BEBB  mov rax,[rcx+8]
0x4E1BEBF  jmp short 0x4E1BEC3
0x4E1BEC1  xor eax,eax
0x4E1BEC3  mov rcx,[rcx]
0x4E1BEC6  mov [rbp+0xD0],rcx
0x4E1BECD  mov [rbp+0xD8],rax
0x4E1BED4  lea rax,[rbp+0xE0]
0x4E1BEDB  mov [rsp+0x38],rax
0x4E1BEE0  lea rax,[rbp+0xF0]
0x4E1BEE7  mov [rsp+0x30],rax
0x4E1BEEC  movzx eax,byte ptr [rbp+0x410]
0x4E1BEF3  mov [rsp+0x28],al
0x4E1BEF7  lea rax,[rbp+0x28]
0x4E1BEFB  mov [rsp+0x20],rax

--- end of piece 3/4 (170 instructions) ---

### Phase 10: 0x4E1BF00..0x4E1BF5F: Arguments finish with r8=[rbp+0xD0], r9=[rbp-0x30], rcx=[rbp+0x358], rdx=r14 and call 0x4E1F300; then a small-string path compares [rbp+0xA0] with 0x10, computes length+1 vs 0x1000, checks buffer metadata [rcx-8] against 0x20, and calls 0xE935700.

0x4E1BF00  lea r8,[rbp+0xD0]
0x4E1BF07  lea r9,[rbp-0x30]
0x4E1BF0B  mov rcx,[rbp+0x358]
0x4E1BF12  mov rdx,r14
0x4E1BF15  call 0x4E1F300
0x4E1BF1A  nop
0x4E1BF1B  mov rax,[rbp+0xA0]
0x4E1BF22  cmp rax,0x10
0x4E1BF26  movzx r14d,byte ptr [rbp+0x367]
0x4E1BF2E  jb short 0x4E1BF64
0x4E1BF30  mov rcx,[rbp+0x88]
0x4E1BF37  lea rdx,[rax+1]
0x4E1BF3B  cmp rdx,0x1000
0x4E1BF42  jb short 0x4E1BF5F
0x4E1BF44  mov r8,[rcx-8]
0x4E1BF48  add rcx,0xFFFFFFFFFFFFFFF8
0x4E1BF4C  sub rcx,r8
0x4E1BF4F  cmp rcx,0x20
0x4E1BF53  jae short 0x4E1BFC5
0x4E1BF55  add rax,0x28
0x4E1BF59  mov rdx,rax
0x4E1BF5C  mov rcx,r8
0x4E1BF5F  call 0xE935700

### Phase 11: 0x4E1BF64..0x4E1BFC0: The same small-string sequence runs for [rbp+0x80]/[rbp+0x68] (with [rbp+0x338]->rbx and [rbp+0x2C0]->r15 also loaded), then lea rcx=[rbp+0x10]; call 0x3D3110; rsi=[rbp+0x120]; jmp 0x4E1A277.

0x4E1BF64  mov rax,[rbp+0x80]
0x4E1BF6B  cmp rax,0x10
0x4E1BF6F  mov rbx,[rbp+0x338]
0x4E1BF76  mov r15,[rbp+0x2C0]
0x4E1BF7D  jb short 0x4E1BFB0
0x4E1BF7F  mov rcx,[rbp+0x68]
0x4E1BF83  lea rdx,[rax+1]
0x4E1BF87  cmp rdx,0x1000
0x4E1BF8E  jb short 0x4E1BFAB
0x4E1BF90  mov r8,[rcx-8]
0x4E1BF94  add rcx,0xFFFFFFFFFFFFFFF8
0x4E1BF98  sub rcx,r8
0x4E1BF9B  cmp rcx,0x20
0x4E1BF9F  jae short 0x4E1BFC5
0x4E1BFA1  add rax,0x28
0x4E1BFA5  mov rdx,rax
0x4E1BFA8  mov rcx,r8
0x4E1BFAB  call 0xE935700
0x4E1BFB0  lea rcx,[rbp+0x10]
0x4E1BFB4  call 0x3D3110
0x4E1BFB9  mov rsi,[rbp+0x120]
0x4E1BFC0  jmp 0x4E1A277

### Phase 12: 0x4E1BFC5..0x4E1BFF2: Failure path: [rsp+0x20] is zeroed, ecx/edx/r8d/r9d are cleared, qword ptr [0xF9A8C78] is called, then 0x75720 is called three times, followed by int3 and nop.

0x4E1BFC5  mov qword ptr [rsp+0x20],0
0x4E1BFCE  xor ecx,ecx
0x4E1BFD0  xor edx,edx
0x4E1BFD2  xor r8d,r8d
0x4E1BFD5  xor r9d,r9d
0x4E1BFD8  call qword ptr [0xF9A8C78]
0x4E1BFDE  nop
0x4E1BFDF  call 0x75720
0x4E1BFE4  nop
0x4E1BFE5  call 0x75720
0x4E1BFEA  nop
0x4E1BFEB  call 0x75720
0x4E1BFF0  nop
0x4E1BFF1  int3
0x4E1BFF2  nop [rax+rax]

--- end of piece 4/4 (230 instructions) ---

## Field map: every [reg+off] field stored or loaded (one row per distinct offset, all sites listed)

| offset | size | direction | verbatim sites | meaning |
|------|------|-----------|----------------|---------|
| rbp+0x2F8 | 8 | addr | 0x4E1BC51  lea rcx,[rbp+0x2F8] | - |
| rbp+0x328 | 8 | read | 0x4E1BC66  mov rsi,[rbp+0x328]; 0x4E1BCB2  mov rsi,[rbp+0x328] | - |
| rbp+0x320 | 16 | store | 0x4E1BC6D  movups [rbp+0x320],xmm0 | 16-byte xmm zero store |
| rbp+0x338 | 8 | read | 0x4E1BC77  mov rdi,[rbp+0x338]; 0x4E1BE70  mov rdi,[rbp+0x338]; 0x4E1BF6F  mov rbx,[rbp+0x338] | - |
| rbp+0x2C0 | 8 | read | 0x4E1BC7E  mov r14,[rbp+0x2C0]; 0x4E1BF76  mov r15,[rbp+0x2C0] | - |
| rsi+0x0 | 8 | read | 0x4E1BC8D  mov rax,[rsi]; 0x4E1BCA2  mov rax,[rsi]; 0x4E1BCCF  mov rax,[rsi]; 0x4E1BCE4  mov rax,[rsi]; 0x4E1BD25  mov rax,[rsi]; 0x4E1BD3A  mov rax,[rsi]; 0x4E1BD67  mov rax,[rsi]; 0x4E1BD7C  mov rax,[rsi]; 0x4E1BDB3  mov rax,[rsi]; 0x4E1BDC8  mov rax,[rsi] | - |
| rax+0x0 | 8 | read | 0x4E1BC90  mov rax,[rax]; 0x4E1BCD2  mov rax,[rax]; 0x4E1BD28  mov rax,[rax]; 0x4E1BD6A  mov rax,[rax]; 0x4E1BDB6  mov rax,[rax]; 0x4E1BE5E  mov rax,[rax]; 0x4E1BE8B  mov rax,[rax] | - |
| rsi+0xC | 4 | R/W | 0x4E1BC9C  lock dec dword ptr [rsi+0xC]; 0x4E1BCDE  lock dec dword ptr [rsi+0xC]; 0x4E1BD34  lock dec dword ptr [rsi+0xC]; 0x4E1BD76  lock dec dword ptr [rsi+0xC]; 0x4E1BDC2  lock dec dword ptr [rsi+0xC] | locked dword decrement |
| rbp+0x330 | 8 | store | 0x4E1BCB9  mov qword ptr [rbp+0x330],0 | - |
| rbp+0x318 | 1 | read | 0x4E1BCF4  cmp byte ptr [rbp+0x318],1 | byte flag compared to 1 |
| rbp+0x310 | 8 | read | 0x4E1BCFD  mov rcx,[rbp+0x310] | - |
| rbp+0x290 | 8 | read | 0x4E1BD0C  mov rsi,[rbp+0x290]; 0x4E1BD4A  mov rsi,[rbp+0x290] | - |
| rbp+0x288 | 16 | store | 0x4E1BD13  movups [rbp+0x288],xmm0 | 16-byte xmm zero store |
| rbp+0x298 | 8 | store | 0x4E1BD51  mov qword ptr [rbp+0x298],0 | - |
| rbp+0x280 | 1 | read | 0x4E1BD8C  cmp byte ptr [rbp+0x280],1 | byte flag compared to 1 |
| rbp+0x278 | 8 | read | 0x4E1BD95  mov rcx,[rbp+0x278] | - |
| rbp+0x2B8 | 8 | read | 0x4E1BDA1  mov rsi,[rbp+0x2B8] | - |
| rbp+0xE0 | 16,8 | store | 0x4E1BDDB  movaps [rbp+0xE0],xmm0; 0x4E1BE08  mov [rbp+0xE0],rcx; 0x4E1BED4  lea rax,[rbp+0xE0] | 16-byte xmm zero store, then 8-byte store |
| rbp+0x428 | 8 | read | 0x4E1BDE2  mov rcx,[rbp+0x428] | - |
| rbp+0x400 | 8 | read | 0x4E1BDFE  mov rdx,[rbp+0x400] | - |
| rcx+0x0 | 8 | read | 0x4E1BE05  mov rcx,[rcx]; 0x4E1BE39  mov rcx,[rcx]; 0x4E1BE5B  mov rax,[rcx]; 0x4E1BE88  mov rax,[rcx]; 0x4E1BEC3  mov rcx,[rcx] | capacity metadata ([rcx-8] checked against 0x20) |
| rbp+0xE8 | 8 | store | 0x4E1BE0F  mov [rbp+0xE8],rax | - |
| rbp+0xF0 | 16,8 | store | 0x4E1BE16  movaps [rbp+0xF0],xmm0; 0x4E1BE3C  mov [rbp+0xF0],rcx; 0x4E1BEE0  lea rax,[rbp+0xF0] | 16-byte xmm zero store, then 8-byte store |
| rbp+0x420 | 8 | read | 0x4E1BE1D  mov rcx,[rbp+0x420] | - |
| rbp+0xF8 | 8 | store | 0x4E1BE43  mov [rbp+0xF8],rax | - |
| rbp+0x60 | 8 | store | 0x4E1BE4A  mov qword ptr [rbp+0x60],0; 0x4E1BE6C  mov [rbp+0x60],rax | - |
| rdx+0x38 | 8 | read | 0x4E1BE52  mov rcx,[rdx+0x38] | - |
| rbp+0x28 | 8 | addr | 0x4E1BE61  lea rdx,[rbp+0x28]; 0x4E1BEF7  lea rax,[rbp+0x28] | - |
| rdi+0x38 | 8 | read | 0x4E1BE7F  mov rcx,[rdi+0x38] | - |
| rbp-0x30 | 8 | addr | 0x4E1BE8E  lea rdx,[rbp-0x30]; 0x4E1BF07  lea r9,[rbp-0x30] | - |
| rbp+0xD0 | 16,8 | store | 0x4E1BEA0  movaps [rbp+0xD0],xmm0; 0x4E1BEC6  mov [rbp+0xD0],rcx; 0x4E1BF00  lea r8,[rbp+0xD0] | 16-byte xmm zero store, then 8-byte store |
| rbp+0x408 | 8 | read | 0x4E1BEA7  mov rcx,[rbp+0x408] | - |
| rbp+0xD8 | 8 | store | 0x4E1BECD  mov [rbp+0xD8],rax | - |
| rsp+0x38 | 8 | store | 0x4E1BEDB  mov [rsp+0x38],rax | - |
| rsp+0x30 | 8 | store | 0x4E1BEE7  mov [rsp+0x30],rax | - |
| rbp+0x410 | 1 | read | 0x4E1BEEC  movzx eax,byte ptr [rbp+0x410] | byte flag loaded (movzx) |
| rsp+0x28 | 1 | store | 0x4E1BEF3  mov [rsp+0x28],al | - |
| rsp+0x20 | 8 | store | 0x4E1BEFB  mov [rsp+0x20],rax; 0x4E1BFC5  mov qword ptr [rsp+0x20],0 | - |
| rbp+0x358 | 8 | read | 0x4E1BF0B  mov rcx,[rbp+0x358] | - |
| rbp+0xA0 | 8 | read | 0x4E1BF1B  mov rax,[rbp+0xA0] | length compared with 0x10 |
| rbp+0x367 | 1 | read | 0x4E1BF26  movzx r14d,byte ptr [rbp+0x367] | byte flag loaded (movzx) |
| rbp+0x88 | 8 | read | 0x4E1BF30  mov rcx,[rbp+0x88] | string buffer; metadata [rcx-8] checked against 0x20 |
| rbp+0x80 | 8 | read | 0x4E1BF64  mov rax,[rbp+0x80] | length compared with 0x10 |
| rbp+0x68 | 8 | read | 0x4E1BF7F  mov rcx,[rbp+0x68] | string buffer; metadata [rcx-8] checked against 0x20 |
| rbp+0x10 | 8 | addr | 0x4E1BFB0  lea rcx,[rbp+0x10] | - |
| rbp+0x120 | 8 | read | 0x4E1BFB9  mov rsi,[rbp+0x120] | - |

## TOOL REQUESTS

None
