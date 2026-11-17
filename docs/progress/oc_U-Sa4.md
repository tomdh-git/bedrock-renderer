## NEXT
DONE
# U-Sa4 field map — effect_shadow_extractor_alt_66a6830, chunk 4 of 7 (slice 0x66a7721..0x66a7b99, 250 instructions)

Phases hold at most 40 instructions each; each phase header gives the RVA range and one or two sentences, followed by the verbatim `0xRVA  instr` lines it covers (copied exactly from docs/progress/_part_Sa4.txt). lea, absolute/[gs:]/scaled operands and direct calls do not load or store a [reg+off] field. The field map of every [reg+off] load/store follows the phases.

## Phase 0x66a7721..0x66a77e6
An indirect tail call jumps to r10+rcx; on the fall-through path [rbp+0x2A8] is loaded into rcx and stored at [rbp+0x4C0]. When the short jump is not taken, a 16-byte block is loaded from [rcx] (= [rbp+0x2A8]) and stored at [rcx+0x15C] (= [rbp+0x4C0] via rcx=&[rbp+0x364]); if the object at [rbp+0x2B0] is non-null its +8 dword is locked-incremented, then [rbp+0x4D0] := al, [rbp+0x4E8] := [rbp+0x2D0], and [rbp+0x4D8] := the 16-byte block from [rbp+0x2C0].
0x66a7721  add r10,rcx
0x66a7724  jmp r10
0x66a7727  mov rcx,[rbp+0x2A8]
0x66a772e  mov [rbp+0x4C0],rcx
0x66a7735  jmp short 0x66A778F
0x66a7737  lea rcx,[rbp+0x2A8]
0x66a773e  movups xmm0,[rcx]
0x66a7741  lea rcx,[rbp+0x364]
0x66a7748  movups [rcx+0x15C],xmm0
0x66a774f  jmp short 0x66A778F
0x66a7751  lea rcx,[rbp+0x364]
0x66a7758  movups [rcx+0x15C],xmm0
0x66a775f  mov rcx,[rbp+0x2B0]
0x66a7766  test rcx,rcx
0x66a7769  je short 0x66A7778
0x66a776b  lock inc dword ptr [rcx+8]
0x66a776f  mov rcx,[rbp+0x2B0]
0x66a7776  jmp short 0x66A777A
0x66a7778  xor ecx,ecx
0x66a777a  mov r10,[rbp+0x2A8]
0x66a7781  mov [rbp+0x4C0],r10
0x66a7788  mov [rbp+0x4C8],rcx
0x66a778f  mov [rbp+0x4D0],al
0x66a7795  mov rax,[rbp+0x2D0]
0x66a779c  mov [rbp+0x4E8],rax
0x66a77a3  movaps xmm0,[rbp+0x2C0]
0x66a77aa  movups [rbp+0x4D8],xmm0
0x66a77b1  mov ecx,0x9D0
0x66a77b6  add rcx,[r12+0x10]
0x66a77bb  mov [rsp+0x30],r15
0x66a77c0  lea rax,[rbp+0x364]
0x66a77c7  mov [rsp+0x28],rax
0x66a77cc  mov [rsp+0x20],r14
0x66a77d1  call 0x67D50C0
0x66a77d6  nop
0x66a77d7  lea r15,[rbp+0x360]
0x66a77de  mov rcx,r15
0x66a77e1  call 0x66A9AD0
0x66a77e6  cmp byte ptr [rbp+0x2B8],3

## Phase 0x66a77ed..0x66a783b
If [rbp+0x2B8] == 3 and rdi = [rbp+0x2B0] is non-null, [rdi+8] and [rdi+0xC] are locked-decremented and [rdi] and [rdi+8] are called through [0xF99FFA0]. Control merges at 0x66a7826, where rsi := [rbp+0x288] and rbx := [rbp+0x290] bracket a list that rsi walks in 0x28 steps.
0x66a77ed  jne short 0x66A7826
0x66a77ef  mov rdi,[rbp+0x2B0]
0x66a77f6  test rdi,rdi
0x66a77f9  je short 0x66A7826
0x66a77fb  lock dec dword ptr [rdi+8]
0x66a77ff  jne short 0x66A7826
0x66a7801  mov rax,[rdi]
0x66a7804  mov rax,[rax]
0x66a7807  mov rcx,rdi
0x66a780a  call qword ptr [0xF99FFA0]
0x66a7810  lock dec dword ptr [rdi+0xC]
0x66a7814  jne short 0x66A7826
0x66a7816  mov rax,[rdi]
0x66a7819  mov rax,[rax+8]
0x66a781d  mov rcx,rdi
0x66a7820  call qword ptr [0xF99FFA0]
0x66a7826  mov rsi,[rbp+0x288]
0x66a782d  test rsi,rsi
0x66a7830  je short 0x66A789A
0x66a7832  mov rbx,[rbp+0x290]
0x66a7839  jmp short 0x66A7844
0x66a783b  nop [rax+rax]
## Phase 0x66a7840..0x66a78ce
The walk loads [rsi+0x18] and continues unless it equals 2; on match rdi := [rsi+8] is released ([rdi+8] and [rdi+0xC] locked-decremented, [rdi] and [rdi+8] called via [0xF99FFA0]) before rsi advances by 0x28 toward rbx. At 0x66a7885 xmm0 is zeroed and [rbp+0x288] (rax=&[rbp+0x288]) is cleared with movups plus a dword 0 at [rax+0x10]; then [rcx-8] is loaded from rcx = [rbp+0x500] and the adjusted size is compared against 0x1000.
0x66a7840  add rsi,0x28
0x66a7844  cmp rsi,rbx
0x66a7847  je short 0x66A7885
0x66a7849  cmp byte ptr [rsi+0x18],2
0x66a784d  jne short 0x66A7840
0x66a784f  mov rdi,[rsi+8]
0x66a7853  test rdi,rdi
0x66a7856  je short 0x66A7840
0x66a7858  lock dec dword ptr [rdi+8]
0x66a785c  jne short 0x66A7840
0x66a785e  mov rax,[rdi]
0x66a7861  mov rax,[rax]
0x66a7864  mov rcx,rdi
0x66a7867  call qword ptr [0xF99FFA0]
0x66a786d  lock dec dword ptr [rdi+0xC]
0x66a7871  jne short 0x66A7840
0x66a7873  mov rax,[rdi]
0x66a7876  mov rax,[rax+8]
0x66a787a  mov rcx,rdi
0x66a787d  call qword ptr [0xF99FFA0]
0x66a7883  jmp short 0x66A7840
0x66a7885  xorps xmm0,xmm0
0x66a7888  lea rax,[rbp+0x288]
0x66a788f  movups [rax],xmm0
0x66a7892  mov qword ptr [rax+0x10],0
0x66a789a  lea rcx,[rbp+0x158]
0x66a78a1  call 0x1751590
0x66a78a6  cmp byte ptr [rbp+0x540],1
0x66a78ad  jne short 0x66A78EF
0x66a78af  mov rcx,[rbp+0x500]
0x66a78b6  test rcx,rcx
0x66a78b9  je short 0x66A78EF
0x66a78bb  mov rdx,[rbp+0x510]
0x66a78c2  sub rdx,rcx
0x66a78c5  cmp rdx,0x1000
0x66a78cc  jb short 0x66A78EA
0x66a78ce  mov rax,[rcx-8]

## Phase 0x66a78d2..0x66a7930
If adjusted rcx >= 0x20 control jumps to 0x66A87F8; otherwise rdx |= 0x27, rcx := rax, and 0xE935700 is called. Then rax := [rbp+0x580], r13 := [rax+0x38], rsi := [r12], rax := [rbp+0x270], [rbp+0x360] is zeroed, rcx := [rax+8] is locked-incremented when non-null, and rdi := [rbp+0x368].
0x66a78d2  add rcx,0xFFFFFFFFFFFFFFF8
0x66a78d6  sub rcx,rax
0x66a78d9  cmp rcx,0x20
0x66a78dd  jae 0x66A87F8
0x66a78e3  or rdx,0x27
0x66a78e7  mov rcx,rax
0x66a78ea  call 0xE935700
0x66a78ef  mov rax,[rbp+0x580]
0x66a78f6  mov r13,[rax+0x38]
0x66a78fa  mov rsi,[r12]
0x66a78fe  mov rax,[rbp+0x270]
0x66a7905  xorps xmm0,xmm0
0x66a7908  movaps [rbp+0x360],xmm0
0x66a790f  mov rcx,[rax+8]
0x66a7913  test rcx,rcx
0x66a7916  je short 0x66A795F
0x66a7918  lock inc dword ptr [rcx+8]
0x66a791c  mov rdi,[rbp+0x368]
0x66a7923  movups xmm0,[rax]
0x66a7926  movaps [rbp+0x360],xmm0
0x66a792d  test rdi,rdi
0x66a7930  je short 0x66A7974
## Phase 0x66a7932..0x66a79d4
A non-null rdi = [rbp+0x368] is released ([rdi+8] and [rdi+0xC] locked-decremented, [rdi] and [rdi+8] called via [0xF99FFA0]); on the null-rcx path [rbp+0x360] := [rax] and [rbp+0x368] := 0. Converging at 0x66a7974, [rbp+0x360] is reloaded, rax := [[rax+0x18]] is stored at [rbp+0x158], r12 := &[rbp+0x160], r8 := [rsi], rdx := [rax+0x170] and 0xE86B370 is called; [rbp+0x1D8] := rsi, rdi = [rbp+0x368] is released once more, and the phase ends with rax := [rax+8].
0x66a7932  lock dec dword ptr [rdi+8]
0x66a7936  jne short 0x66A7974
0x66a7938  mov rax,[rdi]
0x66a793b  mov rax,[rax]
0x66a793e  mov rcx,rdi
0x66a7941  call qword ptr [0xF99FFA0]
0x66a7947  lock dec dword ptr [rdi+0xC]
0x66a794b  jne short 0x66A7974
0x66a794d  mov rax,[rdi]
0x66a7950  mov rax,[rax+8]
0x66a7954  mov rcx,rdi
0x66a7957  call qword ptr [0xF99FFA0]
0x66a795d  jmp short 0x66A7974
0x66a795f  mov rax,[rax]
0x66a7962  mov [rbp+0x360],rax
0x66a7969  mov qword ptr [rbp+0x368],0
0x66a7974  mov rax,[rbp+0x360]
0x66a797b  mov rax,[rax+0x18]
0x66a797f  mov rax,[rax]
0x66a7982  mov [rbp+0x158],rax
0x66a7989  lea r12,[rbp+0x160]
0x66a7990  mov r8,[rsi]
0x66a7993  mov rdx,[rax+0x170]
0x66a799a  mov rcx,r12
0x66a799d  call 0xE86B370
0x66a79a2  nop
0x66a79a3  mov [rbp+0x1D8],rsi
0x66a79aa  mov rdi,[rbp+0x368]
0x66a79b1  test rdi,rdi
0x66a79b4  je short 0x66A79E1
0x66a79b6  lock dec dword ptr [rdi+8]
0x66a79ba  jne short 0x66A79E1
0x66a79bc  mov rax,[rdi]
0x66a79bf  mov rax,[rax]
0x66a79c2  mov rcx,rdi
0x66a79c5  call qword ptr [0xF99FFA0]
0x66a79cb  lock dec dword ptr [rdi+0xC]
0x66a79cf  jne short 0x66A79E1
0x66a79d1  mov rax,[rdi]
0x66a79d4  mov rax,[rax+8]

## Phase 0x66a79d8..0x66a7a45
The release of rdi finishes ([rdi], [rdi+8] via [0xF99FFA0]), then eax := [0x129F8CF0], ecx := [0x128767C8], rdx := gs:[0x58], rcx := [rdx+rcx*8], and control jumps to 0x66A8783 when eax > [rcx+4]. Otherwise [rbp+0x360] := the 16-byte block at [rax+0x70] ([rbp+0x580]), [rbp+0x280] := 1, [rbp+0x288] := r15, rax := [rbp+0x190], r8d := word [rbp+0x19A] zero-extended, edx := r8d << 4, rcx := rax, and if r8d == 0 control jumps to 0x66A7A75.
0x66a79d8  mov rcx,rdi
0x66a79db  call qword ptr [0xF99FFA0]
0x66a79e1  mov eax,[0x129F8CF0]
0x66a79e7  mov ecx,[0x128767C8]
0x66a79ed  mov rdx,gs:[0x58]
0x66a79f6  mov rcx,[rdx+rcx*8]
0x66a79fa  cmp eax,[rcx+4]
0x66a7a00  jg 0x66A8783
0x66a7a06  mov rax,[rbp+0x580]
0x66a7a0d  movups xmm0,[rax+0x70]
0x66a7a11  movaps [rbp+0x360],xmm0
0x66a7a18  mov qword ptr [rbp+0x280],1
0x66a7a23  mov [rbp+0x288],r15
0x66a7a2a  mov rax,[rbp+0x190]
0x66a7a31  movzx r8d,word ptr [rbp+0x19A]
0x66a7a39  mov edx,r8d
0x66a7a3c  shl edx,4
0x66a7a3f  mov rcx,rax
0x66a7a42  test r8d,r8d
0x66a7a45  je short 0x66A7A75
## Phase 0x66a7a47..0x66a7ae3
r8 := [0x129F8CE8] and the code walks the table at rcx (step 0x10, bound edx) comparing each entry's [r10+0x28] with r8 until a match; on match cx := (rcx - rax) >> 1 is stored at [rbp+0x500], [rbp+0x502] := 1, and 0x5679DB0 is called with rdx = &[rbp+0x500] and r8 = &[rbp+0x280]. Then rax := ([r13+0x60] - [r13+0x58]) >> 2 * 0xAAAAAAAB (shr rax,2 then imul eax,0xAAAAAAAB); 0x4DE9FA0 (rcx = r13, rdx = &[rbp-8]) is always reached — control jumps straight to it when eax == 0, otherwise 0xBBD7C70 (rdx = [rbp+0x158] + 0x250, rcx = &[rbp+0x360]) and then 0x4DEDD00 (rcx = r13, rdx = &[rbp+0x360]) run first.
0x66a7a47  mov r8,[0x129F8CE8]
0x66a7a4e  mov r9,rdx
0x66a7a51  mov rcx,rax
0x66a7a54  nop [rax+rax]
0x66a7a60  mov r10,[rcx]
0x66a7a63  cmp [r10+0x28],r8
0x66a7a67  je short 0x66A7A75
0x66a7a69  add rcx,0x10
0x66a7a6d  add r9,0xFFFFFFFFFFFFFFF0
0x66a7a71  jne short 0x66A7A60
0x66a7a73  jmp short 0x66A7AA7
0x66a7a75  add rdx,rax
0x66a7a78  cmp rcx,rdx
0x66a7a7b  jae short 0x66A7AA7
0x66a7a7d  sub ecx,eax
0x66a7a7f  shr ecx,4
0x66a7a82  mov [rbp+0x500],cx
0x66a7a89  mov byte ptr [rbp+0x502],1
0x66a7a90  lea rdx,[rbp+0x500]
0x66a7a97  lea r8,[rbp+0x280]
0x66a7a9e  mov rcx,r12
0x66a7aa1  call 0x5679DB0
0x66a7aa6  nop
0x66a7aa7  mov rax,[r13+0x60]
0x66a7aab  sub rax,[r13+0x58]
0x66a7aaf  shr rax,2
0x66a7ab3  imul eax,0xAAAAAAAB
0x66a7ab9  test eax,eax
0x66a7abb  je short 0x66A7AE9
0x66a7abd  mov edx,0x250
0x66a7ac2  add rdx,[rbp+0x158]
0x66a7ac9  lea rcx,[rbp+0x360]
0x66a7ad0  xor r8d,r8d
0x66a7ad3  call 0xBBD7C70
0x66a7ad8  nop
0x66a7ad9  lea rdx,[rbp+0x360]
0x66a7ae0  mov rcx,r13
0x66a7ae3  call 0x4DEDD00

## Phase 0x66a7ae8..0x66a7b99
rax := [rbp+0x268] and four 16-byte blocks are loaded from [rax], [rax+0x10], [rax+0x20], [rax+0x30] and stored at [rbp+0x200], [rbp+0x210], [rbp+0x220], [rbp+0x230]; [rbp+0x240] := 0. rax := [rbp+0x358], si := word [rax+0x18], rax := [rbp+0x578], rdx := [rax], 0x66A6190 is called with rcx = &[rbp+0x500] and r8 = &[rbp-8]; finally [rbp+0x364] := 8, [rbp+0x368] := 7, [rbp+0x36C] := 0, [rbp+0x370] := 0, [rbp+0x372] := 2, [rbp+0x374] := 0, [rbp+0x378] := 0, and [rbp+0x37C] := a zeroed 16-byte block.
0x66a7ae8  nop
0x66a7ae9  lea rdx,[rbp-8]
0x66a7aed  mov rcx,r13
0x66a7af0  call 0x4DE9FA0
0x66a7af5  nop
0x66a7af6  mov rax,[rbp+0x268]
0x66a7afd  movups xmm6,[rax]
0x66a7b00  movaps [rbp+0x200],xmm6
0x66a7b07  movups xmm7,[rax+0x10]
0x66a7b0b  movaps [rbp+0x210],xmm7
0x66a7b12  movups xmm8,[rax+0x20]
0x66a7b17  movaps [rbp+0x220],xmm8
0x66a7b1f  movups xmm9,[rax+0x30]
0x66a7b24  movaps [rbp+0x230],xmm9
0x66a7b2c  mov byte ptr [rbp+0x240],0
0x66a7b33  mov rax,[rbp+0x358]
0x66a7b3a  mov si,[rax+0x18]
0x66a7b3e  mov rax,[rbp+0x578]
0x66a7b45  mov rdx,[rax]
0x66a7b48  lea rcx,[rbp+0x500]
0x66a7b4f  lea r8,[rbp-8]
0x66a7b53  call 0x66A6190
0x66a7b58  nop
0x66a7b59  mov dword ptr [rbp+0x364],8
0x66a7b63  mov byte ptr [rbp+0x368],7
0x66a7b6a  mov dword ptr [rbp+0x36C],0
0x66a7b74  mov word ptr [rbp+0x370],0
0x66a7b7d  mov byte ptr [rbp+0x372],2
0x66a7b84  mov dword ptr [rbp+0x374],0
0x66a7b8e  mov byte ptr [rbp+0x378],0
0x66a7b95  xorps xmm10,xmm10
0x66a7b99  movups [rbp+0x37C],xmm10
## Field map — every [reg+off] load/store in slice 0x66a7721..0x66a7b99

One row per distinct [reg+off] field; all sites of that field are listed verbatim. Direction is the access performed by the listed instruction(s). Size is taken from the instruction (movups/movaps 16, qword 8, dword/movss 4, word 2, byte 1). Meanings are stated only where the instruction itself shows them, otherwise '-'.

| offset | size | address (access) | `0xRVA  instr` sites | meaning |
|---|---|---|---|---|
| rbp+0x2A8 | 8 | [rbp+0x2A8] (load) | 0x66a7727  mov rcx,[rbp+0x2A8] | shadow object pointer loaded into rcx |
| rbp+0x4C0 | 16 (movups); 8 (mov) | [rbp+0x4C0] (store) | 0x66a772e  mov [rbp+0x4C0],rcx<br>0x66a7748  movups [rcx+0x15C],xmm0<br>0x66a7758  movups [rcx+0x15C],xmm0<br>0x66a7781  mov [rbp+0x4C0],r10 | 16-byte copy destination of the [rbp+0x2A8] block (effective [rbp+0x4C0] via rcx=&[rbp+0x364]); direct 8-byte pointer stores |
| rcx+0x0 | 16 (movups); 8 (mov) | [rcx] (load) | 0x66a773e  movups xmm0,[rcx]<br>0x66a7a60  mov r10,[rcx] | 16-byte load of the [rbp+0x2A8] block (rcx=&[rbp+0x2A8]); table-entry load while rcx walks the [rbp+0x190] table |
| rcx+0x15C | 16 | [rcx+0x15C] (store) | 0x66a7748  movups [rcx+0x15C],xmm0<br>0x66a7758  movups [rcx+0x15C],xmm0 | 16-byte store at effective [rbp+0x4C0] (rcx=&[rbp+0x364]) |
| rcx+0x8 | 4 | [rcx+8] (store, locked inc) | 0x66a776b  lock inc dword ptr [rcx+8] | locked 4-byte increment of the object refcount dword (rcx = [rbp+0x2B0]) |
| rbp+0x4C8 | 8 | [rbp+0x4C8] (store) | 0x66a7788  mov [rbp+0x4C8],rcx | rcx stored (zero or the [rbp+0x2B0] object pointer) |
| rbp+0x4D0 | 1 | [rbp+0x4D0] (store) | 0x66a778f  mov [rbp+0x4D0],al | flag byte := al |
| rbp+0x2D0 | 8 | [rbp+0x2D0] (load) | 0x66a7795  mov rax,[rbp+0x2D0] | - |
| rbp+0x4E8 | 8 | [rbp+0x4E8] (store) | 0x66a779c  mov [rbp+0x4E8],rax | - |
| rbp+0x2C0 | 16 | [rbp+0x2C0] (load) | 0x66a77a3  movaps xmm0,[rbp+0x2C0] | 16-byte block loaded |
| rbp+0x4D8 | 16 | [rbp+0x4D8] (store) | 0x66a77aa  movups [rbp+0x4D8],xmm0 | - |
| r12+0x10 | 8 | [r12+0x10] (load) | 0x66a77b6  add rcx,[r12+0x10] | - |
| rsp+0x30 | 8 | [rsp+0x30] (store) | 0x66a77bb  mov [rsp+0x30],r15 | stack spill slot (r15) |
| rsp+0x28 | 8 | [rsp+0x28] (store) | 0x66a77c7  mov [rsp+0x28],rax | stack spill slot (&[rbp+0x364]) |
| rsp+0x20 | 8 | [rsp+0x20] (store) | 0x66a77cc  mov [rsp+0x20],r14 | stack spill slot (r14) |
| rbp+0x2B8 | 1 | [rbp+0x2B8] (load) | 0x66a77e6  cmp byte ptr [rbp+0x2B8],3 | discriminant byte compared against 3 |
| rdi+0x8 | 4 | [rdi+8] (store, locked dec RMW) | 0x66a77fb  lock dec dword ptr [rdi+8]<br>0x66a7858  lock dec dword ptr [rdi+8]<br>0x66a7932  lock dec dword ptr [rdi+8]<br>0x66a79b6  lock dec dword ptr [rdi+8] | locked 4-byte decrement of an object refcount (rdi = [rbp+0x2B0] / [rsi+8] / [rbp+0x368]) |
| rdi+0x0 | 8 | [rdi] (load) | 0x66a7801  mov rax,[rdi]<br>0x66a7816  mov rax,[rdi]<br>0x66a785e  mov rax,[rdi]<br>0x66a7873  mov rax,[rdi]<br>0x66a7938  mov rax,[rdi]<br>0x66a794d  mov rax,[rdi]<br>0x66a79bc  mov rax,[rdi]<br>0x66a79d1  mov rax,[rdi] | object pointer / vtable loaded from object rdi |
| rax+0x0 | 16 (movups); 8 (mov) | [rax] (load/store) | 0x66a7804  mov rax,[rax]<br>0x66a7861  mov rax,[rax]<br>0x66a788f  movups [rax],xmm0<br>0x66a793b  mov rax,[rax]<br>0x66a7954  mov rax,[rax]<br>0x66a797f  mov rax,[rax]<br>0x66a79bf  mov rax,[rax]<br>0x66a7b45  mov rdx,[rax] | vtable/interface pointer chain ([rax]=[rdi] or [rax]=[rbp+0x360+0x18]); 16-byte clear of [rbp+0x288] (rax=&[rbp+0x288]) |
| rdi+0xC | 4 | [rdi+0xC] (store, locked dec RMW) | 0x66a7810  lock dec dword ptr [rdi+0xC]<br>0x66a786d  lock dec dword ptr [rdi+0xC]<br>0x66a7947  lock dec dword ptr [rdi+0xC]<br>0x66a79cb  lock dec dword ptr [rdi+0xC] | locked 4-byte decrement of the object's second refcount dword |
| rax+0x8 | 8 | [rax+8] (load) | 0x66a7819  mov rax,[rax+8]<br>0x66a7876  mov rax,[rax+8]<br>0x66a790f  mov rcx,[rax+8]<br>0x66a7950  mov rax,[rax+8]<br>0x66a79d4  mov rax,[rax+8] | [vtable+8] or object field at +8 loaded (rax = vtable pointer or [rbp+0x270]) |
| rbp+0x288 | 8 | [rbp+0x288] (load/store) | 0x66a7826  mov rsi,[rbp+0x288]<br>0x66a7a23  mov [rbp+0x288],r15 | list head: loaded as walk start (rsi), stored as &[rbp+0x360] (r15) |
| rbp+0x290 | 8 | [rbp+0x290] (load) | 0x66a7832  mov rbx,[rbp+0x290] | list end bound (rbx) |
| rsi+0x18 | 1 | [rsi+0x18] (load) | 0x66a7849  cmp byte ptr [rsi+0x18],2 | node type byte compared against 2 |
| rsi+0x8 | 8 | [rsi+8] (load) | 0x66a784f  mov rdi,[rsi+8] | node object pointer loaded into rdi |
| rax+0x10 | 16 (movups load); 8 (qword store) | [rax+0x10] (load/store) | 0x66a7892  mov qword ptr [rax+0x10],0<br>0x66a7b07  movups xmm7,[rax+0x10] | 16-byte load while copying [rbp+0x268]; qword 0 store at [rbp+0x298] (rax=&[rbp+0x288]) |
| rcx-8 | 8 | [rcx-8] (load) | 0x66a78ce  mov rax,[rcx-8] | heap metadata qword below [rbp+0x500] loaded into rax |
| rax+0x38 | 8 | [rax+0x38] (load) | 0x66a78f6  mov r13,[rax+0x38] | +0x38 field of [rbp+0x270] object loaded into r13 |
| r12+0x0 | 8 | [r12] (load) | 0x66a78fa  mov rsi,[r12] | - |
| rbp+0x270 | 8 | [rbp+0x270] (load) | 0x66a78fe  mov rax,[rbp+0x270] | object pointer loaded into rax |
| rbp+0x360 | 16 (movaps); 8 (mov) | [rbp+0x360] (store/load) | 0x66a7908  movaps [rbp+0x360],xmm0<br>0x66a7926  movaps [rbp+0x360],xmm0<br>0x66a7962  mov [rbp+0x360],rax<br>0x66a7974  mov rax,[rbp+0x360]<br>0x66a7a11  movaps [rbp+0x360],xmm0 | shadow struct zeroed by 16-byte stores, then object pointer stored and reloaded |
| rbp+0x368 | 8/1 | [rbp+0x368] (load/store) | 0x66a791c  mov rdi,[rbp+0x368]<br>0x66a7969  mov qword ptr [rbp+0x368],0<br>0x66a79aa  mov rdi,[rbp+0x368]<br>0x66a7b63  mov byte ptr [rbp+0x368],7 | release-target slot loaded as rdi, cleared to 0, reloaded, then set to 7 |
| rax+0x18 | 8 (mov rax); 2 (mov si) | [rax+0x18] (load) | 0x66a797b  mov rax,[rax+0x18]<br>0x66a7b3a  mov si,[rax+0x18] | +0x18 field loaded as qword (interface dispatch) and as word |
| rbp+0x158 | 8 | [rbp+0x158] (store/load) | 0x66a7982  mov [rbp+0x158],rax<br>0x66a7ac2  add rdx,[rbp+0x158] | result pointer stored, then added to rdx ([rbp+0x158] + 0x250) |
| rsi+0x0 | 8 | [rsi] (load) | 0x66a7990  mov r8,[rsi] | - |
| rax+0x170 | 8 | [rax+0x170] (load) | 0x66a7993  mov rdx,[rax+0x170] | method pointer at +0x170 (target of 0xE86B370) |
| rbp+0x1D8 | 8 | [rbp+0x1D8] (store) | 0x66a79a3  mov [rbp+0x1D8],rsi | - |
| rcx+0x4 | 4 | [rcx+4] (load) | 0x66a79fa  cmp eax,[rcx+4] | [rcx+4] (gs:[0x58] table entry) compared with eax |
| rax+0x70 | 16 | [rax+0x70] (load) | 0x66a7a0d  movups xmm0,[rax+0x70] | 16-byte state block at [rbp+0x580+0x70] copied to [rbp+0x360] |
| rbp+0x280 | 8 | [rbp+0x280] (store) | 0x66a7a18  mov qword ptr [rbp+0x280],1 | flag qword := 1 |
| rbp+0x190 | 8 | [rbp+0x190] (load) | 0x66a7a2a  mov rax,[rbp+0x190] | table base loaded into rax |
| rbp+0x19A | 2 | [rbp+0x19A] (load) | 0x66a7a31  movzx r8d,word ptr [rbp+0x19A] | word table count zero-extended into r8d |
| r10+0x28 | 8 | [r10+0x28] (load) | 0x66a7a63  cmp [r10+0x28],r8 | table entry field compared with r8 |
| rbp+0x500 | 2 | [rbp+0x500] (store) | 0x66a7a82  mov [rbp+0x500],cx | table index cx stored; its address is passed to 0x5679DB0 |
| rbp+0x502 | 1 | [rbp+0x502] (store) | 0x66a7a89  mov byte ptr [rbp+0x502],1 | flag byte := 1 |
| r13+0x58 | 8 | [r13+0x58] (load) | 0x66a7aab  sub rax,[r13+0x58] | range start subtracted from range end |
| r13+0x60 | 8 | [r13+0x60] (load) | 0x66a7aa7  mov rax,[r13+0x60] | range end loaded into rax |
| rax+0x20 | 16 | [rax+0x20] (load) | 0x66a7b12  movups xmm8,[rax+0x20] | 16-byte block loaded while copying [rbp+0x268] |
| rax+0x30 | 16 | [rax+0x30] (load) | 0x66a7b1f  movups xmm9,[rax+0x30] | 16-byte block loaded while copying [rbp+0x268] |
| rbp+0x200 | 16 | [rbp+0x200] (store) | 0x66a7b00  movaps [rbp+0x200],xmm6 | 16-byte block from [rbp+0x268] stored |
| rbp+0x210 | 16 | [rbp+0x210] (store) | 0x66a7b0b  movaps [rbp+0x210],xmm7 | 16-byte block from [rax+0x10] stored |
| rbp+0x220 | 16 | [rbp+0x220] (store) | 0x66a7b17  movaps [rbp+0x220],xmm8 | 16-byte block from [rax+0x20] stored |
| rbp+0x230 | 16 | [rbp+0x230] (store) | 0x66a7b24  movaps [rbp+0x230],xmm9 | 16-byte block from [rax+0x30] stored |
| rbp+0x240 | 1 | [rbp+0x240] (store) | 0x66a7b2c  mov byte ptr [rbp+0x240],0 | flag byte := 0 |
| rbp+0x358 | 8 | [rbp+0x358] (load) | 0x66a7b33  mov rax,[rbp+0x358] | - |
| rbp+0x578 | 8 | [rbp+0x578] (load) | 0x66a7b3e  mov rax,[rbp+0x578] | - |
| rbp+0x364 | 4 | [rbp+0x364] (store) | 0x66a7b59  mov dword ptr [rbp+0x364],8 | dword := 8 |
| rbp+0x36C | 4 | [rbp+0x36C] (store) | 0x66a7b6a  mov dword ptr [rbp+0x36C],0 | dword := 0 |
| rbp+0x370 | 2 | [rbp+0x370] (store) | 0x66a7b74  mov word ptr [rbp+0x370],0 | word := 0 |
| rbp+0x372 | 1 | [rbp+0x372] (store) | 0x66a7b7d  mov byte ptr [rbp+0x372],2 | byte := 2 |
| rbp+0x374 | 4 | [rbp+0x374] (store) | 0x66a7b84  mov dword ptr [rbp+0x374],0 | dword := 0 |
| rbp+0x378 | 1 | [rbp+0x378] (store) | 0x66a7b8e  mov byte ptr [rbp+0x378],0 | byte := 0 |
| rbp+0x37C | 16 | [rbp+0x37C] (store) | 0x66a7b99  movups [rbp+0x37C],xmm10 | zeroed 16-byte block (xmm10 zeroed by xorps) |
