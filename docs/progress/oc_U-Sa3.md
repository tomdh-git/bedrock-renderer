## NEXT
DONE

# U-Sa3 — shadow extractor alt 0x66a6830, chunk 3 slice 0x66a71ce..0x66a771d

Source: docs/progress/_part_Sa3.txt (250 instructions, 0x66a71ce..0x66a771d).
Every instruction line below is quoted verbatim from that listing (two spaces after the address). The slice is split into phases of at most 40 instructions; every listed instruction belongs to exactly one phase. All 250 listed instructions are covered; no offsets are skipped.

## Phases

### Phase 1: 0x66a71ce..0x66a72cb (40 instructions)
Spills the 32-byte block at [rbp+0x500..0x530] (four xmm vectors) down to [rbp+0x448..0x478], then branches on ecx: if ecx==2 it copies [rbp+0x500] to [rbp+0x448] and jumps to the shared tail; otherwise it moves [rbp+0x510] into rcx, zeroes [rbp+0x510], reloads [rbp+0x500] into xmm0, zeroes [rbp+0x500], and stores xmm0 to [rbp+0x448] and rcx to [rbp+0x458]. The shared tail at 0x66a724e stores al to [rbp+0x488], then begins resetting a second block: leas r14/r9/r8/rdx to [rbp+0x3C0/0x448/0x490/0x498], stores si to [rbp+0x490], loads [rbp+0x280]->xmm0 and [rbp+0x290]->xmm1, zeroes [rbp+0x288] and [rbp+0x290], copies xmm0->[rbp+0x498] and xmm1->[rbp+0x4A8], loads [rbp+0x2A0]->rax to [rbp+0x4B8], leas r11=[rbp+0x2A8], stores tag byte [rbp+0x4D0]=0xFF, and zero-extends the tag byte [rbp+0x2B8] into eax comparing it to 3.

0x66a71ce  movaps xmm0,[rbp+0x500]
0x66a71d5  movaps xmm1,[rbp+0x510]
0x66a71dc  movaps xmm2,[rbp+0x520]
0x66a71e3  movaps xmm3,[rbp+0x530]
0x66a71ea  movups [rbp+0x448],xmm0
0x66a71f1  movups [rbp+0x458],xmm1
0x66a71f8  movups [rbp+0x468],xmm2
0x66a71ff  movups [rbp+0x478],xmm3
0x66a7206  jmp short 0x66A724E
0x66a7208  cmp ecx,2
0x66a720b  jne short 0x66A7254
0x66a720d  mov rcx,[rbp+0x500]
0x66a7214  mov [rbp+0x448],rcx
0x66a721b  jmp short 0x66A724E
0x66a721d  mov rcx,[rbp+0x510]
0x66a7224  mov qword ptr [rbp+0x510],0
0x66a722f  movaps xmm0,[rbp+0x500]
0x66a7236  xorps xmm1,xmm1
0x66a7239  movaps [rbp+0x500],xmm1
0x66a7240  movups [rbp+0x448],xmm0
0x66a7247  mov [rbp+0x458],rcx
0x66a724e  mov [rbp+0x488],al
0x66a7254  lea r14,[rbp+0x3C0]
0x66a725b  lea r9,[rbp+0x448]
0x66a7262  lea r8,[rbp+0x490]
0x66a7269  mov [rbp+0x490],si
0x66a7270  lea rdx,[rbp+0x498]
0x66a7277  movaps xmm0,[rbp+0x280]
0x66a727e  movaps xmm1,[rbp+0x290]
0x66a7285  mov qword ptr [rbp+0x288],0
0x66a7290  movups [rbp+0x498],xmm0
0x66a7297  xorps xmm0,xmm0
0x66a729a  movaps [rbp+0x290],xmm0
0x66a72a1  movups [rbp+0x4A8],xmm1
0x66a72a8  mov rax,[rbp+0x2A0]
0x66a72af  mov [rbp+0x4B8],rax
0x66a72b6  lea r11,[rbp+0x2A8]
0x66a72bd  mov byte ptr [rbp+0x4D0],0xFF
0x66a72c4  movzx eax,byte ptr [rbp+0x2B8]
0x66a72cb  cmp rax,3

### Phase 2: 0x66a72cf..0x66a7398 (40 instructions)
Jump-table dispatch on the zero-extended byte tag [rbp+0x2B8] with table base 0xF2BF818 (cases 0..3): case 0 stores [rbp+0x2A8] to [rbp+0x4C0]; case 1 loads 16 bytes from [r11]=[rbp+0x2A8] into xmm0 and stores them at [rcx+0x15C]=[rbp+0x4C0]; case 2 stores xmm0 at [rbp+0x4C0], then manipulates the refcounted object pointer [rbp+0x2B0] via lock inc/dec dword [rdi+8] ([rbp+0x2B8]) and records [rbp+0x2A8] to [rbp+0x4C0] plus rcx to [rbp+0x4C8]. All cases converge at 0x66a7344 storing al to [rbp+0x4D0], then [rbp+0x2D0]->[rbp+0x4E8], [rbp+0x2C0]->[rbp+0x4D8], sets ecx=0x9D0 plus [rbp+0x578+0x10], builds three outgoing [rsp] argument slots from [rbp+0x360], [rbp+0x364] and r14, and calls 0x67D50C0.

0x66a72cf  ja short 0x66A734A
0x66a72d1  lea rcx,[0xF2BF818]
0x66a72d8  movsxd r10,[rcx+rax*4]
0x66a72dc  add r10,rcx
0x66a72df  jmp r10
0x66a72e2  mov rcx,[rbp+0x2A8]
0x66a72e9  mov [rbp+0x4C0],rcx
0x66a72f0  jmp short 0x66A7344
0x66a72f2  movups xmm0,[r11]
0x66a72f6  lea rcx,[rbp+0x364]
0x66a72fd  movups [rcx+0x15C],xmm0
0x66a7304  jmp short 0x66A7344
0x66a7306  lea rcx,[rbp+0x364]
0x66a730d  movups [rcx+0x15C],xmm0
0x66a7314  mov rcx,[rbp+0x2B0]
0x66a731b  test rcx,rcx
0x66a731e  je short 0x66A732D
0x66a7320  lock inc dword ptr [rcx+8]
0x66a7324  mov rcx,[rbp+0x2B0]
0x66a732b  jmp short 0x66A732F
0x66a732d  xor ecx,ecx
0x66a732f  mov r10,[rbp+0x2A8]
0x66a7336  mov [rbp+0x4C0],r10
0x66a733d  mov [rbp+0x4C8],rcx
0x66a7344  mov [rbp+0x4D0],al
0x66a734a  mov rax,[rbp+0x2D0]
0x66a7351  mov [rbp+0x4E8],rax
0x66a7358  movaps xmm0,[rbp+0x2C0]
0x66a735f  movups [rbp+0x4D8],xmm0
0x66a7366  mov ecx,0x9D0
0x66a736b  mov rax,[rbp+0x578]
0x66a7372  add rcx,[rax+0x10]
0x66a7376  lea rax,[rbp+0x360]
0x66a737d  mov [rsp+0x30],rax
0x66a7382  lea rax,[rbp+0x364]
0x66a7389  mov [rsp+0x28],rax
0x66a738e  mov [rsp+0x20],r14
0x66a7393  call 0x67D50C0
0x66a7398  nop

### Phase 3: 0x66a7399..0x66a742d (40 instructions)
Calls 0x66A9AD0 with rcx=r15=[rbp+0x360], then if tag byte [rbp+0x2B8]==3 it releases the object [rbp+0x2B0]: lock dec dword [rdi+8] ([rbp+0x2B8]), vtable destructor through qword ptr [0xF99FFA0], lock dec dword [rdi+0xC] ([rbp+0x2BC]), and delete through [rax+8]. Otherwise skips to 0x66a73e8 where it loads [rbp+0x288]->rsi and, if nonzero, walks the 0x28-strided array [rsi..r13] ([rbp+0x290]), releasing each element whose byte tag [rsi+0x18]==2 via decref [rdi+8], vtable destructor [0xF99FFA0], and delete [rax+8].

0x66a7399  lea r15,[rbp+0x360]
0x66a73a0  mov rcx,r15
0x66a73a3  call 0x66A9AD0
0x66a73a8  cmp byte ptr [rbp+0x2B8],3
0x66a73af  jne short 0x66A73E8
0x66a73b1  mov rdi,[rbp+0x2B0]
0x66a73b8  test rdi,rdi
0x66a73bb  je short 0x66A73E8
0x66a73bd  lock dec dword ptr [rdi+8]
0x66a73c1  jne short 0x66A73E8
0x66a73c3  mov rax,[rdi]
0x66a73c6  mov rax,[rax]
0x66a73c9  mov rcx,rdi
0x66a73cc  call qword ptr [0xF99FFA0]
0x66a73d2  lock dec dword ptr [rdi+0xC]
0x66a73d6  jne short 0x66A73E8
0x66a73d8  mov rax,[rdi]
0x66a73db  mov rax,[rax+8]
0x66a73df  mov rcx,rdi
0x66a73e2  call qword ptr [0xF99FFA0]
0x66a73e8  mov rsi,[rbp+0x288]
0x66a73ef  test rsi,rsi
0x66a73f2  je short 0x66A745A
0x66a73f4  mov r13,[rbp+0x290]
0x66a73fb  jmp short 0x66A7404
0x66a73fd  nop [rax]
0x66a7400  add rsi,0x28
0x66a7404  cmp rsi,r13
0x66a7407  je short 0x66A7445
0x66a7409  cmp byte ptr [rsi+0x18],2
0x66a740d  jne short 0x66A7400
0x66a740f  mov rdi,[rsi+8]
0x66a7413  test rdi,rdi
0x66a7416  je short 0x66A7400
0x66a7418  lock dec dword ptr [rdi+8]
0x66a741c  jne short 0x66A7400
0x66a741e  mov rax,[rdi]
0x66a7421  mov rax,[rax]
0x66a7424  mov rcx,rdi
0x66a7427  call qword ptr [0xF99FFA0]
0x66a742d  lock dec dword ptr [rdi+0xC]

### Phase 4: 0x66a7431..0x66a74f0 (40 instructions)
Loops back to 0x66a7400, then at 0x66a7445 zeroes xmm0 and clears the 16-byte field [rbp+0x288] (movups [rax]=xmm0 where rax=[rbp+0x288]) plus its upper qword [rax+0x10]=[rbp+0x298]. Calls 0x1751590 with [rbp+0x158]; if byte [rbp+0x540]==1 and [rbp+0x500] is nonzero it computes length [rbp+0x510]-[rbp+0x500], and if length>=0x1000 reads the heap size [rcx-8]=[rbp+0x4F8] and takes a checked path (call 0xE935700) else jumps to 0x66A87F8. Then zeroes [rbp+0x500] and [rbp+0x510], and calls 0x6760560 with the range ([rbp+0x568]-[rbp+0x560])>>6 and pointers [rbp+0x500], [rbp+0x560], [rbp+0x568].

0x66a7431  jne short 0x66A7400
0x66a7433  mov rax,[rdi]
0x66a7436  mov rax,[rax+8]
0x66a743a  mov rcx,rdi
0x66a743d  call qword ptr [0xF99FFA0]
0x66a7443  jmp short 0x66A7400
0x66a7445  xorps xmm0,xmm0
0x66a7448  lea rax,[rbp+0x288]
0x66a744f  movups [rax],xmm0
0x66a7452  mov qword ptr [rax+0x10],0
0x66a745a  lea rcx,[rbp+0x158]
0x66a7461  call 0x1751590
0x66a7466  cmp byte ptr [rbp+0x540],1
0x66a746d  jne short 0x66A74AF
0x66a746f  mov rcx,[rbp+0x500]
0x66a7476  test rcx,rcx
0x66a7479  je short 0x66A74AF
0x66a747b  mov rdx,[rbp+0x510]
0x66a7482  sub rdx,rcx
0x66a7485  cmp rdx,0x1000
0x66a748c  jb short 0x66A74AA
0x66a748e  mov rax,[rcx-8]
0x66a7492  add rcx,0xFFFFFFFFFFFFFFF8
0x66a7496  sub rcx,rax
0x66a7499  cmp rcx,0x20
0x66a749d  jae 0x66A87F8
0x66a74a3  or rdx,0x27
0x66a74a7  mov rcx,rax
0x66a74aa  call 0xE935700
0x66a74af  xorps xmm0,xmm0
0x66a74b2  movaps [rbp+0x500],xmm0
0x66a74b9  mov qword ptr [rbp+0x510],0
0x66a74c4  mov rdx,[rbp+0x568]
0x66a74cb  sub rdx,[rbp+0x560]
0x66a74d2  sar rdx,6
0x66a74d6  lea rcx,[rbp+0x500]
0x66a74dd  lea r8,[rbp+0x560]
0x66a74e4  lea r9,[rbp+0x568]
0x66a74eb  call 0x6760560
0x66a74f0  nop

### Phase 5: 0x66a74f1..0x66a75ee (40 instructions)
Stores mode byte [rbp+0x540]=1, loads [rbp+0x358]->rax then mov si,[rax+0x18], lea rdx=[rbp+0x158], mov rcx=r12 and calls 0x4DE9FA0. After a nop it sets r12=[rbp+0x578], mov rdx=[r12], lea rcx=[rbp+0x280], lea r8=[rbp+0x158], calls 0x66A6190, then nop. It then initializes the descriptor at [rbp+0x360..0x3BA] (word/dword/byte fields 1,0,8,1,1,2,0,0, zeroes 16 bytes at 0x37C, dword[0x38C]=0, movlps [rbp+0x390]=low8(xmm6), byte[0x398]=8, qword[0x39C]=rbx, dword[0x3A4]=0, byte[0x3A8]=8, qword[0x3AC]=rbx, dword[0x3B4]=0, word[0x3B8]=1, byte[0x3BA]=1), copies [rbp+0x48] to [rbp+0x3C0], calls 0xE869FF0 with rcx=[rbp+0x3C8] and rdx=[rbp+0x50], and moves [rbp+0xC8] into rax.

0x66a74f1  mov byte ptr [rbp+0x540],1
0x66a74f8  mov rax,[rbp+0x358]
0x66a74ff  mov si,[rax+0x18]
0x66a7503  lea rdx,[rbp+0x158]
0x66a750a  mov rcx,r12
0x66a750d  call 0x4DE9FA0
0x66a7512  nop
0x66a7513  mov r12,[rbp+0x578]
0x66a751a  mov rdx,[r12]
0x66a751e  lea rcx,[rbp+0x280]
0x66a7525  lea r8,[rbp+0x158]
0x66a752c  call 0x66A6190
0x66a7531  nop
0x66a7532  mov word ptr [rbp+0x360],1
0x66a753b  mov dword ptr [rbp+0x364],0
0x66a7545  mov byte ptr [rbp+0x368],8
0x66a754c  mov dword ptr [rbp+0x36C],1
0x66a7556  mov word ptr [rbp+0x370],1
0x66a755f  mov byte ptr [rbp+0x372],2
0x66a7566  mov dword ptr [rbp+0x374],0
0x66a7570  mov byte ptr [rbp+0x378],0
0x66a7577  xorps xmm0,xmm0
0x66a757a  movups [rbp+0x37C],xmm0
0x66a7581  mov dword ptr [rbp+0x38C],0
0x66a758b  movlps [rbp+0x390],xmm6
0x66a7592  mov byte ptr [rbp+0x398],8
0x66a7599  mov [rbp+0x39C],rbx
0x66a75a0  mov dword ptr [rbp+0x3A4],0
0x66a75aa  mov byte ptr [rbp+0x3A8],8
0x66a75b1  mov [rbp+0x3AC],rbx
0x66a75b8  mov dword ptr [rbp+0x3B4],0
0x66a75c2  mov word ptr [rbp+0x3B8],1
0x66a75cb  mov byte ptr [rbp+0x3BA],1
0x66a75d2  mov rax,[rbp+0x48]
0x66a75d6  mov [rbp+0x3C0],rax
0x66a75dd  lea rcx,[rbp+0x3C8]
0x66a75e4  lea rdx,[rbp+0x50]
0x66a75e8  call 0xE869FF0
0x66a75ed  nop
0x66a75ee  mov rax,[rbp+0xC8]

### Phase 6: 0x66a75f5..0x66a76e3 (40 instructions)
Stores rax ([rbp+0xC8]) to [rbp+0x440], clears [rbp+0xC8], sets [rbp+0x488]=0xFF, then loads the mode byte [rbp+0x540] into eax/ecx and compares it to 1. Branches on the mode: if ecx==0 it reloads the four-vector block [rbp+0x500..0x530] to [rbp+0x448..0x478] and jumps to 0x66a76A1; if ecx==2 it copies [rbp+0x500] to [rbp+0x448]; otherwise (the 0x66a7670 path) it moves [rbp+0x510] to rcx, zeroes [rbp+0x510], reloads [rbp+0x500] into xmm0, zeroes [rbp+0x500], stores xmm0 to [rbp+0x448] and rcx to [rbp+0x458]. All paths store al to [rbp+0x488] at 0x66a76a1, then repeat the second-block reset: lea r9=[rbp+0x448], r8=[rbp+0x490], store si to [rbp+0x490], lea rdx=[rbp+0x498], load [rbp+0x280]->xmm0 and [rbp+0x290]->xmm1, zero [rbp+0x288], copy xmm0->[rbp+0x498], and zero xmm0 (xorps xmm0,xmm0) ready for the next store.

0x66a75f5  mov [rbp+0x440],rax
0x66a75fc  mov qword ptr [rbp+0xC8],0
0x66a7607  mov byte ptr [rbp+0x488],0xFF
0x66a760e  movzx eax,byte ptr [rbp+0x540]
0x66a7615  movzx ecx,al
0x66a7618  cmp ecx,1
0x66a761b  jg short 0x66A765B
0x66a761d  test ecx,ecx
0x66a761f  jne short 0x66A7670
0x66a7621  movaps xmm0,[rbp+0x500]
0x66a7628  movaps xmm1,[rbp+0x510]
0x66a762f  movaps xmm2,[rbp+0x520]
0x66a7636  movaps xmm3,[rbp+0x530]
0x66a763d  movups [rbp+0x448],xmm0
0x66a7644  movups [rbp+0x458],xmm1
0x66a764b  movups [rbp+0x468],xmm2
0x66a7652  movups [rbp+0x478],xmm3
0x66a7659  jmp short 0x66A76A1
0x66a765b  cmp ecx,2
0x66a765e  jne short 0x66A76A7
0x66a7660  mov rcx,[rbp+0x500]
0x66a7667  mov [rbp+0x448],rcx
0x66a766e  jmp short 0x66A76A1
0x66a7670  mov rcx,[rbp+0x510]
0x66a7677  mov qword ptr [rbp+0x510],0
0x66a7682  movaps xmm0,[rbp+0x500]
0x66a7689  xorps xmm1,xmm1
0x66a768c  movaps [rbp+0x500],xmm1
0x66a7693  movups [rbp+0x448],xmm0
0x66a769a  mov [rbp+0x458],rcx
0x66a76a1  mov [rbp+0x488],al
0x66a76a7  lea r9,[rbp+0x448]
0x66a76ae  lea r8,[rbp+0x490]
0x66a76b5  mov [rbp+0x490],si
0x66a76bc  lea rdx,[rbp+0x498]
0x66a76c3  movaps xmm0,[rbp+0x280]
0x66a76ca  movaps xmm1,[rbp+0x290]
0x66a76d1  mov qword ptr [rbp+0x288],0
0x66a76dc  movups [rbp+0x498],xmm0
0x66a76e3  xorps xmm0,xmm0

### Phase 7: 0x66a76e6..0x66a771d (10 instructions)
Stores the zeroed xmm0 to [rbp+0x290] (clearing the 16-byte field), copies xmm1 to [rbp+0x4A8], loads [rbp+0x2A0]->rax and stores to [rbp+0x4B8], sets tag [rbp+0x4D0]=0xFF, then zero-extends the tag byte [rbp+0x2B8] into eax, compares to 3, and if above jumps to 0x66A7795; otherwise loads jump-table base 0xF2BF828 and executes movsxd r10,[rcx+rax*4] (slice ends before the indirect jump, targets not resolved here).

0x66a76e6  movaps [rbp+0x290],xmm0
0x66a76ed  movups [rbp+0x4A8],xmm1
0x66a76f4  mov rax,[rbp+0x2A0]
0x66a76fb  mov [rbp+0x4B8],rax
0x66a7702  mov byte ptr [rbp+0x4D0],0xFF
0x66a7709  movzx eax,byte ptr [rbp+0x2B8]
0x66a7710  cmp rax,3
0x66a7714  ja short 0x66A7795
0x66a7716  lea rcx,[0xF2BF828]
0x66a771d  movsxd r10,[rcx+rax*4]

## Field table — every [reg+off] field stored or loaded

Sizes are taken from the instruction (movups/movaps 16, qword 8, dword/movss/movlps 4 or 8 as encoded, word 2, byte 1). Direction R = load, W = store. Meaning is "-" unless an instruction or string in the listing shows it. One annotated row per distinct offset, with all its sites listed. rbp-relative offsets are the stack-frame fields; Table B lists non-rbp [reg+off] object/header fields with the base register shown.

### Table A — rbp-relative stack-frame fields

| offset | size | site | instr | meaning |
|--------|------|------|-------|---------|
| 0x48 | 8 | R [rbp+0x48] | 0x66a75d2  mov rax,[rbp+0x48] | - |
| 0xC8 | 8 | R/W [rbp+0xC8] | 0x66a75ee  mov rax,[rbp+0xC8]; 0x66a75fc  mov qword ptr [rbp+0xC8],0 | R then cleared after copy to 0x440 |
| 0x280 | 16 | R [rbp+0x280] | 0x66a7277  movaps xmm0,[rbp+0x280]; 0x66a76c3  movaps xmm0,[rbp+0x280] | copied to [rbp+0x498] |
| 0x288 | 16/8 | R/W [rbp+0x288] | 0x66a7285  mov qword ptr [rbp+0x288],0; 0x66a73e8  mov rsi,[rbp+0x288]; 0x66a744f  movups [rax],xmm0 (rax=[rbp+0x288]); 0x66a76d1  mov qword ptr [rbp+0x288],0 | loop cursor / low qword of 16-byte field; array base cursor; 16-byte field zeroed |
| 0x290 | 16 | R/W [rbp+0x290] | 0x66a727e  movaps xmm1,[rbp+0x290]; 0x66a73f4  mov r13,[rbp+0x290]; 0x66a729a  movaps [rbp+0x290],xmm0; 0x66a76ca  movaps xmm1,[rbp+0x290]; 0x66a76e6  movaps [rbp+0x290],xmm0 | copied to [rbp+0x4A8]; array end; 16-byte field zeroed |
| 0x298 | 8 | W [rbp+0x298] | 0x66a7452  mov qword ptr [rax+0x10],0 (rax=[rbp+0x288]) | upper qword of 0x288 field cleared |
| 0x2A0 | 8 | R [rbp+0x2A0] | 0x66a72a8  mov rax,[rbp+0x2A0]; 0x66a76f4  mov rax,[rbp+0x2A0] | stored to [rbp+0x4B8] |
| 0x2A8 | 16/8 | R [rbp+0x2A8] | 0x66a72e2  mov rcx,[rbp+0x2A8]; 0x66a72f2  movups xmm0,[r11] (r11=[rbp+0x2A8]); 0x66a732f  mov r10,[rbp+0x2A8] | stored to [rbp+0x4C0] |
| 0x2B0 | 8 | R [rbp+0x2B0] | 0x66a7314  mov rcx,[rbp+0x2B0]; 0x66a7324  mov rcx,[rbp+0x2B0]; 0x66a73b1  mov rdi,[rbp+0x2B0] | refcounted object pointer |
| 0x2B8 | 1/4 | R/W [rbp+0x2B8] | 0x66a72c4  movzx eax,byte ptr [rbp+0x2B8]; 0x66a7320  lock inc dword ptr [rcx+8] (rcx=[rbp+0x2B0]); 0x66a73a8  cmp byte ptr [rbp+0x2B8],3; 0x66a73bd  lock dec dword ptr [rdi+8] (rdi=[rbp+0x2B0]); 0x66a7418  lock dec dword ptr [rdi+8] | tag byte (compared to 3); refcount (lock inc/dec) |
| 0x2BC | 4 | W [rbp+0x2BC] | 0x66a73d2  lock dec dword ptr [rdi+0xC] (rdi=[rbp+0x2B0]); 0x66a742d  lock dec dword ptr [rdi+0xC] | second refcount/destroy flag |
| 0x2C0 | 16 | R [rbp+0x2C0] | 0x66a7358  movaps xmm0,[rbp+0x2C0] | copied to [rbp+0x4D8] |
| 0x2D0 | 8 | R [rbp+0x2D0] | 0x66a734a  mov rax,[rbp+0x2D0] | stored to [rbp+0x4E8] |
| 0x358 | 8 | R [rbp+0x358] | 0x66a74f8  mov rax,[rbp+0x358] | source pointer (rax used for [rax+0x18]) |
| 0x360 | 2 | W [rbp+0x360] | 0x66a7532  mov word ptr [rbp+0x360],1 | - |
| 0x364 | 4 | W [rbp+0x364] | 0x66a753b  mov dword ptr [rbp+0x364],0 | - |
| 0x368 | 1 | W [rbp+0x368] | 0x66a7545  mov byte ptr [rbp+0x368],8 | - |
| 0x36C | 4 | W [rbp+0x36C] | 0x66a754c  mov dword ptr [rbp+0x36C],1 | - |
| 0x370 | 2 | W [rbp+0x370] | 0x66a7556  mov word ptr [rbp+0x370],1 | - |
| 0x372 | 1 | W [rbp+0x372] | 0x66a755f  mov byte ptr [rbp+0x372],2 | - |
| 0x374 | 4 | W [rbp+0x374] | 0x66a7566  mov dword ptr [rbp+0x374],0 | - |
| 0x378 | 1 | W [rbp+0x378] | 0x66a7570  mov byte ptr [rbp+0x378],0 | - |
| 0x37C | 16 | W [rbp+0x37C] | 0x66a757a  movups [rbp+0x37C],xmm0 (xmm0 zeroed) | 16 bytes zeroed (0x37C-0x38B) |
| 0x38C | 4 | W [rbp+0x38C] | 0x66a7581  mov dword ptr [rbp+0x38C],0 | - |
| 0x390 | 8 | W [rbp+0x390] | 0x66a758b  movlps [rbp+0x390],xmm6 | low 8 bytes of xmm6 |
| 0x398 | 1 | W [rbp+0x398] | 0x66a7592  mov byte ptr [rbp+0x398],8 | - |
| 0x39C | 8 | W [rbp+0x39C] | 0x66a7599  mov [rbp+0x39C],rbx | - |
| 0x3A4 | 4 | W [rbp+0x3A4] | 0x66a75a0  mov dword ptr [rbp+0x3A4],0 | - |
| 0x3A8 | 1 | W [rbp+0x3A8] | 0x66a75aa  mov byte ptr [rbp+0x3A8],8 | - |
| 0x3AC | 8 | W [rbp+0x3AC] | 0x66a75b1  mov [rbp+0x3AC],rbx | - |
| 0x3B4 | 4 | W [rbp+0x3B4] | 0x66a75b8  mov dword ptr [rbp+0x3B4],0 | - |
| 0x3B8 | 2 | W [rbp+0x3B8] | 0x66a75c2  mov word ptr [rbp+0x3B8],1 | - |
| 0x3BA | 1 | W [rbp+0x3BA] | 0x66a75cb  mov byte ptr [rbp+0x3BA],1 | - |
| 0x3C0 | 8 | W [rbp+0x3C0] | 0x66a75d6  mov [rbp+0x3C0],rax (rax=[rbp+0x48]) | - |
| 0x440 | 8 | W [rbp+0x440] | 0x66a75f5  mov [rbp+0x440],rax (rax=[rbp+0xC8]) | - |
| 0x448 | 16/8 | W [rbp+0x448] | 0x66a71ea  movups [rbp+0x448],xmm0; 0x66a7214  mov [rbp+0x448],rcx; 0x66a7240  movups [rbp+0x448],xmm0; 0x66a763d  movups [rbp+0x448],xmm0; 0x66a7667  mov [rbp+0x448],rcx; 0x66a7693  movups [rbp+0x448],xmm0 | spill slot / first field of copied block |
| 0x458 | 16/8 | W [rbp+0x458] | 0x66a71f1  movups [rbp+0x458],xmm1; 0x66a7247  mov [rbp+0x458],rcx; 0x66a7644  movups [rbp+0x458],xmm1; 0x66a769a  mov [rbp+0x458],rcx | spill slot / second field |
| 0x468 | 16 | W [rbp+0x468] | 0x66a71f8  movups [rbp+0x468],xmm2; 0x66a764b  movups [rbp+0x468],xmm2 | spill slot |
| 0x478 | 16 | W [rbp+0x478] | 0x66a71ff  movups [rbp+0x478],xmm3; 0x66a7652  movups [rbp+0x478],xmm3 | spill slot |
| 0x488 | 1 | W [rbp+0x488] | 0x66a724e  mov [rbp+0x488],al; 0x66a7607  mov byte ptr [rbp+0x488],0xFF; 0x66a76a1  mov [rbp+0x488],al | flag byte |
| 0x490 | 2 | W [rbp+0x490] | 0x66a7269  mov [rbp+0x490],si; 0x66a76b5  mov [rbp+0x490],si | - |
| 0x498 | 16 | W [rbp+0x498] | 0x66a7290  movups [rbp+0x498],xmm0; 0x66a76dc  movups [rbp+0x498],xmm0 | - |
| 0x4A8 | 16 | W [rbp+0x4A8] | 0x66a72a1  movups [rbp+0x4A8],xmm1; 0x66a76ed  movups [rbp+0x4A8],xmm1 | - |
| 0x4B8 | 8 | W [rbp+0x4B8] | 0x66a72af  mov [rbp+0x4B8],rax; 0x66a76fb  mov [rbp+0x4B8],rax | - |
| 0x4C0 | 16/8 | W [rbp+0x4C0] | 0x66a72e9  mov [rbp+0x4C0],rcx; 0x66a72fd  movups [rcx+0x15C],xmm0 (rcx=[rbp+0x364] -> [rbp+0x4C0]); 0x66a730d  movups [rcx+0x15C],xmm0; 0x66a7336  mov [rbp+0x4C0],r10 | switch-case destination; case-1 vector store target |
| 0x4C8 | 8 | W [rbp+0x4C8] | 0x66a733d  mov [rbp+0x4C8],rcx | - |
| 0x4D0 | 1 | W [rbp+0x4D0] | 0x66a72bd  mov byte ptr [rbp+0x4D0],0xFF; 0x66a7344  mov [rbp+0x4D0],al; 0x66a7702  mov byte ptr [rbp+0x4D0],0xFF | tag byte |
| 0x4D8 | 16 | W [rbp+0x4D8] | 0x66a735f  movups [rbp+0x4D8],xmm0 | - |
| 0x4E8 | 8 | W [rbp+0x4E8] | 0x66a7351  mov [rbp+0x4E8],rax | - |
| 0x4F8 | 8 | R [rbp+0x4F8] | 0x66a748e  mov rax,[rcx-8] (rcx=[rbp+0x500] -> [rbp+0x4F8]) | heap chunk size preceding the 0x500 allocation |
| 0x500 | 16/8 | R/W [rbp+0x500] | 0x66a71ce  movaps xmm0,[rbp+0x500]; 0x66a720d  mov rcx,[rbp+0x500]; 0x66a722f  movaps xmm0,[rbp+0x500]; 0x66a7239  movaps [rbp+0x500],xmm1; 0x66a74b2  movaps [rbp+0x500],xmm0; 0x66a7621  movaps xmm0,[rbp+0x500]; 0x66a7660  mov rcx,[rbp+0x500]; 0x66a7682  movaps xmm0,[rbp+0x500]; 0x66a768c  movaps [rbp+0x500],xmm1 | 32-byte block spill source/target, zeroed after use |
| 0x510 | 16/8 | R/W [rbp+0x510] | 0x66a71d5  movaps xmm1,[rbp+0x510]; 0x66a721d  mov rcx,[rbp+0x510]; 0x66a7224  mov qword ptr [rbp+0x510],0; 0x66a74b9  mov qword ptr [rbp+0x510],0; 0x66a7628  movaps xmm1,[rbp+0x510]; 0x66a7670  mov rcx,[rbp+0x510]; 0x66a7677  mov qword ptr [rbp+0x510],0 | second 16-byte vector, zeroed after use |
| 0x520 | 16 | R [rbp+0x520] | 0x66a71dc  movaps xmm2,[rbp+0x520]; 0x66a762f  movaps xmm2,[rbp+0x520] | spill source |
| 0x530 | 16 | R [rbp+0x530] | 0x66a71e3  movaps xmm3,[rbp+0x530]; 0x66a7636  movaps xmm3,[rbp+0x530] | spill source |
| 0x540 | 1 | R/W [rbp+0x540] | 0x66a7466  cmp byte ptr [rbp+0x540],1; 0x66a74f1  mov byte ptr [rbp+0x540],1; 0x66a760e  movzx eax,byte ptr [rbp+0x540] | mode flag (compared to 1); mode set to 1 |
| 0x560 | 8 | R [rbp+0x560] | 0x66a74cb  sub rdx,[rbp+0x560] | end of range |
| 0x568 | 8 | R [rbp+0x568] | 0x66a74c4  mov rdx,[rbp+0x568] | start of range |
| 0x578 | 8 | R [rbp+0x578] | 0x66a736b  mov rax,[rbp+0x578]; 0x66a7513  mov r12,[rbp+0x578] | object base ([rax+0x10], [r12+0] used) |

### Table B — non-rbp [reg+off] object/header fields

| offset (base) | size | site | instr | meaning |
|---------------|------|------|-------|---------|
| 0 (r12) | 8 | R [r12] | 0x66a751a  mov rdx,[r12] | object base field |
| 0 (rdi) | 8 | R [rdi] | 0x66a73c3  mov rax,[rdi]; 0x66a73d8  mov rax,[rdi]; 0x66a740f  mov rdi,[rsi+8] then 0x66a741e  mov rax,[rdi]; 0x66a7433  mov rax,[rdi] | vtable pointer |
| 8 (rdi) | 4 | W [rdi+8] | 0x66a7320  lock inc dword ptr [rcx+8] (rcx=[rbp+0x2B0]); 0x66a73bd  lock dec dword ptr [rdi+8]; 0x66a7418  lock dec dword ptr [rdi+8] | refcount (lock inc/dec) |
| 0xC (rdi) | 4 | W [rdi+0xC] | 0x66a73d2  lock dec dword ptr [rdi+0xC]; 0x66a742d  lock dec dword ptr [rdi+0xC] | second refcount/destroy flag |
| 0 (rax/vtable) | 8 | R [rax=vtable] | 0x66a73c6  mov rax,[rax]; 0x66a7421  mov rax,[rax] | vtable entry |
| 8 (rax/vtable) | 8 | R [rax+8=vtable+8] | 0x66a73db  mov rax,[rax+8]; 0x66a7436  mov rax,[rax+8] | delete function pointer |
| 0x10 (rax=[rbp+0x578]) | 8 | R [rax+0x10] | 0x66a7372  add rcx,[rax+0x10] | object field |
| 0x18 (rax) | 2 | R [rax+0x18] | 0x66a74ff  mov si,[rax+0x18] | field copied to si |
| 0x18 (rsi=array elem) | 1 | R [rsi+0x18] | 0x66a7409  cmp byte ptr [rsi+0x18],2 | array element tag |
| 8 (rsi=array elem) | 8 | R [rsi+8] | 0x66a740f  mov rdi,[rsi+8] | array element object pointer |
| 0x15C (rcx=[rbp+0x364]) | 16 | W [rcx+0x15C]=[rbp+0x4C0] | 0x66a72fd  movups [rcx+0x15C],xmm0; 0x66a730d  movups [rcx+0x15C],xmm0 | effective [rbp+0x4C0] (see Table A) |
| -8 (rcx=[rbp+0x500]) | 8 | R [rcx-8]=[rbp+0x4F8] | 0x66a748e  mov rax,[rcx-8] | effective [rbp+0x4F8] (see Table A) |

## Callees (not analyzed in this slice)
0x67D50C0, 0x66A9AD0, 0x1751590, 0xE935700, 0x6760560, 0x66A6190, 0xE869FF0, 0x4DE9FA0, plus indirect qword ptr [0xF99FFA0] (vtable destructor/delete). What each does is not shown in the listing: [-].

## OPEN questions
- Jump-table targets at 0xF2BF818 and 0xF2BF828 are not resolved (slice ends at the movsxd; case targets beyond 0x66a771d are outside this unit).
- Meanings of nearly all fields are "-" because no strings or symbol names appear in the listing; only refcount-ish fields are identifiable via lock inc/dec.
- Callee semantics of 0x67D50C0, 0x66A9AD0, 0x1751590, 0xE935700, 0x6760560, 0x66A6190, 0xE869FF0, 0x4DE9FA0 are unknown [-].
- Outgoing [rsp+0x30/0x28/0x20] argument slots and per-array-element [rsi+0x18]/[rsi+8] accesses are not fixed rbp-frame fields and are not in Table A.

## NEXT
DONE
