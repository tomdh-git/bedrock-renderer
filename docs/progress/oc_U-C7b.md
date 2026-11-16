# Unit U-C7b: per-pass loop in frame generator 0xc273420, range 0xc277e8c..0xc2793fe

## Source
- exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base [V brief]
- listing: docs/progress/pre/0xc277e8c.md (preflight python tools/preflight.py 0xc277e8c --n 400, 400 instr, truncated at 0xc278645) + rdis extension to 0xc2793fe [V preflight]
- context: 0xc277e8c and 0xc2793fe are the two call sites of sub_c27ec60 bracketing the per-pass loop (BGFX_MAP 6cz); loop iterates the moved-out declared vector and fills the 24/40-byte dependency record vectors [V BGFX_MAP.md 6cz]
- declared entry d: [d+8] u64, [d+0x10] u32, [d+0x18], [d+0x28] [V BGFX_MAP.md 6cz]
- 24-byte element = {u64 handle/hash, shared_ptr{ptr, ctrl}} (lock inc [ctrl+8]); 40-byte element adds {u32, u16/u8 flags} (flag bytes: 1 = bound, 0 = unbound at mov [rbp+0x1fe4], 0 / byte [rbp+0x1fd8]=1) [V BGFX_MAP.md 6cz]
- vectors: 40-byte at rbp+0x3330/begin, +0x3338/end, +0x3340/cap (growth sites 0xc278508/0xc27859e/0xc278625 -> sub_c27f940); 24-byte at rbp+0x3348/+0x3350/+0x3358 (growth sites 0xc27881d/0xc278882 -> sub_c27fcc0) [V BGFX_MAP.md 6cz]

## NEXT
All work complete: 34 phases covering 0xc277e8c..0xc2793fe instruction-complete (1139 instructions, verified by verify_oc.py: 1139 match, 0 mismatch, 0 missing). Dependency record vectors and per-pass body fields documented. TOOL REQUESTS listed below. Ready for orchestrator review.

## Phases

### Phase 1 (0xc277e8c - 0xc277f67)
0xc277e8c  call 0xC27EC60
0xc277e91  mov qword ptr [rbp+0x1FB0],0
0xc277e9c  movd xmm8,[0xF4788B0]
0xc277ea5  movdqa xmm9,[0xF1333A0]
0xc277eae  movdqa xmm10,[0xF27AAE0]
0xc277eb7  movdqa xmm11,[0xF2F03B0]
0xc277ec0  movdqa xmm12,[0xEF7B810]
0xc277ec9  movaps xmm13,[0xF4788C0]
0xc277ed1  movaps xmm14,[0xF4788D0]
0xc277ed9  movaps xmm15,[0xF4788E0]
0xc277ee1  mov rax,[rbp+0x3450]
0xc277ee8  jmp short 0xC277F10
0xc277eea  nop [rax+rax]
0xc277ef0  lea rcx,[rbp+0x3310]
0xc277ef7  call 0xC27ED70
0xc277efc  mov rax,[rbp+0x3450]
0xc277f03  add rax,0x10
0xc277f07  test dil,dil
0xc277f0a  je 0xC27A772
0xc277f10  mov [rbp+0x3450],rax
0xc277f17  cmp rax,[rbp+0x3418]
0xc277f1e  je 0xC27A63A
0xc277f24  mov rdi,[rbp+0x3290]
0xc277f2b  mov rdx,[rdi+8]
0xc277f2f  xor r14d,r14d
0xc277f32  cmp byte ptr [rdx+0x19],0
0xc277f36  je short 0xC277F50
0xc277f38  mov rbx,rdx
0xc277f3b  mov rsi,rdi
0xc277f3e  cmp byte ptr [rsi+0x19],0
0xc277f42  jne short 0xC277FA4
0xc277f44  jmp short 0xC277F90
0xc277f46  nop [rax+rax]
0xc277f50  mov rax,[rbp+0x3450]
0xc277f57  mov rax,[rax]
0xc277f5a  mov rsi,rdi
0xc277f5d  nop [rax]
0xc277f60  mov rbx,rdx
0xc277f63  mov rcx,[rdx+0x20]
0xc277f67  xor edx,edx

### Phase 2 (0xc277f69 - 0xc278020)
0xc277f69  cmp rcx,rax
0xc277f6c  setb dl
0xc277f6f  cmovae rsi,rbx
0xc277f73  shl edx,4
0xc277f76  mov rdx,[rbx+rdx]
0xc277f7a  cmp byte ptr [rdx+0x19],0
0xc277f7e  je short 0xC277F60
0xc277f80  xor r14d,r14d
0xc277f83  cmp rcx,rax
0xc277f86  setae r14b
0xc277f8a  cmp byte ptr [rsi+0x19],0
0xc277f8e  jne short 0xC277FA4
0xc277f90  mov rax,[rbp+0x3450]
0xc277f97  mov rax,[rax]
0xc277f9a  cmp rax,[rsi+0x20]
0xc277f9e  jae 0xC278084
0xc277fa4  mov rax,0x492492492492492
0xc277fae  cmp [rbp+0x3298],rax
0xc277fb5  je 0xC27BDC7
0xc277fbb  mov rax,[rbp+0x3288]
0xc277fc2  mov rcx,[rax]
0xc277fc5  mov r8d,0x38
0xc277fcb  mov r9d,1
0xc277fd1  lea rdx,[rbp+0x1FC0]
0xc277fd8  call 0xA78940
0xc277fdd  nop
0xc277fde  mov r15,[rbp+0x1FD0]
0xc277fe5  mov rax,[rbp+0x1FC0]
0xc277fec  mov rsi,[rbp+0x1FC8]
0xc277ff3  mov r12,[rax]
0xc277ff6  test rsi,rsi
0xc277ff9  je short 0xC278030
0xc277ffb  lock dec dword ptr [rsi+8]
0xc277fff  jne short 0xC278030
0xc278001  mov rax,[rsi]
0xc278004  mov rax,[rax]
0xc278007  mov rcx,rsi
0xc27800a  call qword ptr [0xF99FFA0]
0xc278010  lock dec dword ptr [rsi+0xC]
0xc278014  jne short 0xC278030
0xc278016  mov rax,[rsi]
0xc278019  mov rax,[rax+8]
0xc27801d  mov rcx,rsi
0xc278020  call qword ptr [0xF99FFA0]

### Phase 3 (0xc278026 - 0xc2780ff)
0xc278026  nop [rax+rax]
0xc278030  lea rsi,[r12+r15]
0xc278034  mov rax,[rbp+0x3450]
0xc27803b  mov rax,[rax]
0xc27803e  mov [r12+r15+0x20],rax
0xc278043  movdqu [r12+r15+0x28],xmm7
0xc27804a  mov [r12+r15],rdi
0xc27804e  mov [r12+r15+8],rdi
0xc278053  mov [r12+r15+0x10],rdi
0xc278058  mov word ptr [r12+r15+0x18],0
0xc278060  mov [rbp+0x1FC0],rbx
0xc278067  mov [rbp+0x1FC8],r14d
0xc27806e  lea rcx,[rbp+0x3290]
0xc278075  lea rdx,[rbp+0x1FC0]
0xc27807c  mov r8,rsi
0xc27807f  call 0xA4C70
0xc278084  mov [rbp+0x3460],rsi
0xc27808b  movdqa [rbp+0x3310],xmm7
0xc278093  mov byte ptr [rbp+0x3322],0
0xc27809a  mov byte ptr [rbp+0x3328],0
0xc2780a1  lea rax,[rbp+0x3330]
0xc2780a8  movdqu [rax+0x30],xmm7
0xc2780ad  movdqu [rax+0x20],xmm7
0xc2780b2  movdqu [rax+0x10],xmm7
0xc2780b7  movdqu [rax],xmm7
0xc2780bb  mov qword ptr [rax+0x40],0
0xc2780c3  mov rax,[rbp+0x3450]
0xc2780ca  mov r13,[rax+8]
0xc2780ce  mov r15b,1
0xc2780d1  cmp byte ptr [r13+1],1
0xc2780d6  jne short 0xC2780DD
0xc2780d8  movzx r15d,byte ptr [r13]
0xc2780dd  cmp byte ptr [r13+0x230],0
0xc2780e5  je 0xC2781B0
0xc2780eb  lea r12,[r13+0x28]
0xc2780ef  movzx eax,byte ptr [r13+0x228]
0xc2780f7  test eax,eax
0xc2780f9  je 0xC278260
0xc2780ff  cmp eax,1

### Phase 4 (0xc278102 - 0xc2781e1)
0xc278102  jne 0xC27BE1D
0xc278108  mov [rbp+0x3200],r12
0xc27810f  mov rax,[r13+0x28]
0xc278113  mov rcx,[r13+0x30]
0xc278117  mov rsi,rcx
0xc27811a  sub rsi,rax
0xc27811d  mov [rbp+0x2FD0],rax
0xc278124  lea rdx,[rbp+0x3200]
0xc27812b  mov [rbp+0x2FD8],rdx
0xc278132  movdqa [rbp+0x33F0],xmm7
0xc27813a  mov qword ptr [rbp+0x3400],0
0xc278145  sub rcx,rax
0xc278148  je 0xC278FEE
0xc27814e  js 0xC27BE29
0xc278154  sar rsi,3
0xc278158  mov rax,0xCCCCCCCCCCCCCCCD
0xc278162  imul rsi,rax
0xc278166  cmp rsi,0x1000
0xc27816d  jb 0xC2790A0
0xc278173  lea rbx,[rsi+0x27]
0xc278177  mov rcx,[0x1233E1A8]
0xc27817e  mov rax,[rcx]
0xc278181  mov rax,[rax+8]
0xc278185  mov rdx,rbx
0xc278188  call qword ptr [0xF99FFA0]
0xc27818e  nop
0xc27818f  mov rdi,rax
0xc278192  test rax,rax
0xc278195  je 0xC2794B4
0xc27819b  mov rax,rdi
0xc27819e  add rdi,0x27
0xc2781a2  and rdi,0xFFFFFFFFFFFFFFE0
0xc2781a6  mov [rdi-8],rax
0xc2781aa  jmp 0xC2790C4
0xc2781af  nop
0xc2781b0  mov byte ptr [rbp+0x3008],0
0xc2781b7  mov byte ptr [rbp+0x3028],0
0xc2781be  mov byte ptr [rbp+0x3048],0
0xc2781c5  mov byte ptr [rbp+0x3068],0
0xc2781cc  mov byte ptr [rbp+0x3088],0
0xc2781d3  mov byte ptr [rbp+0x30A8],0
0xc2781da  mov byte ptr [rbp+0x30C8],0
0xc2781e1  mov byte ptr [rbp+0x30E8],0

### Phase 5 (0xc2781e8 - 0xc27829a)
0xc2781e8  mov byte ptr [rbp+0x3108],0
0xc2781ef  mov byte ptr [rbp+0x3128],0
0xc2781f6  mov byte ptr [rbp+0x3148],0
0xc2781fd  mov byte ptr [rbp+0x3168],0
0xc278204  mov byte ptr [rbp+0x3188],0
0xc27820b  mov byte ptr [rbp+0x31A8],0
0xc278212  mov byte ptr [rbp+0x31C8],0
0xc278219  mov byte ptr [rbp+0x31E8],0
0xc278220  xor ebx,ebx
0xc278222  test r15b,r15b
0xc278225  je 0xC279A33
0xc27822b  cmp byte ptr [r13+4],1
0xc278230  jne 0xC278340
0xc278236  movzx eax,word ptr [r13+2]
0xc27823b  cmp byte ptr [rbp+0x3322],0
0xc278242  jne short 0xC27824B
0xc278244  mov byte ptr [rbp+0x3322],1
0xc27824b  mov [rbp+0x3320],ax
0xc278252  jmp 0xC278347
0xc278257  nop [rax+rax]
0xc278260  xor eax,eax
0xc278262  jmp short 0xC278286
0xc278264  nop [rax+rax]
0xc278270  movups xmm0,[r8]
0xc278274  movups [rdx],xmm0
0xc278277  mov [rdx+0x18],cl
0xc27827a  add rax,0x20
0xc27827e  cmp rax,0x200
0xc278284  je short 0xC278220
0xc278286  mov byte ptr [rbp+rax+0x3008],0xFF
0xc27828e  movzx ecx,byte ptr [r12+rax+0x18]
0xc278294  cmp rcx,4
0xc278298  ja short 0xC27827A
0xc27829a  lea rdx,[rax+rbp]

### Phase 6 (0xc27829e - 0xc278377)
0xc27829e  add rdx,0x2FF0
0xc2782a5  lea r8,[r12+rax]
0xc2782a9  lea r10,[0xF478E3C]
0xc2782b0  movsxd r9,[r10+rcx*4]
0xc2782b4  add r9,r10
0xc2782b7  jmp r9
0xc2782ba  movdqu [rdx],xmm7
0xc2782be  mov r9,[r12+rax+8]
0xc2782c3  test r9,r9
0xc2782c6  je short 0xC278319
0xc2782c8  lock inc dword ptr [r9+8]
0xc2782cd  mov r9,[r12+rax+8]
0xc2782d2  jmp short 0xC27831C
0xc2782d4  movdqu [rdx],xmm7
0xc2782d8  mov r8,[r12+rax+8]
0xc2782dd  test r8,r8
0xc2782e0  je short 0xC2782EE
0xc2782e2  lock inc dword ptr [r8+8]
0xc2782e7  mov r8,[r12+rax+8]
0xc2782ec  jmp short 0xC2782F1
0xc2782ee  xor r8d,r8d
0xc2782f1  mov r9,[r12+rax]
0xc2782f5  mov [rbp+rax+0x2FF0],r9
0xc2782fd  mov [rbp+rax+0x2FF8],r8
0xc278305  movzx r8d,word ptr [r12+rax+0x10]
0xc27830b  mov [rbp+rax+0x3000],r8w
0xc278314  jmp 0xC278277
0xc278319  xor r9d,r9d
0xc27831c  mov r8,[r8]
0xc27831f  mov [rbp+rax+0x2FF0],r8
0xc278327  mov [rbp+rax+0x2FF8],r9
0xc27832f  jmp 0xC278277
0xc278334  nop [rax+rax]
0xc278340  mov byte ptr [rbp+0x3322],0
0xc278347  mov eax,[rbp+0x33E8]
0xc27834d  or rbx,rax
0xc278350  mov [rbp+0x3324],rbx
0xc278357  mov rdi,[r13+0x250]
0xc27835e  mov rbx,[r13+0x258]
0xc278365  jmp short 0xC278374
0xc278367  nop [rax+rax]
0xc278370  add rdi,0x38
0xc278374  cmp rdi,rbx
0xc278377  je 0xC2786A0

### Phase 7 (0xc27837d - 0xc27844b)
0xc27837d  movzx eax,byte ptr [rdi+0x30]
0xc278381  cmp eax,1
0xc278384  je 0xC278490
0xc27838a  cmp eax,2
0xc27838d  je 0xC278450
0xc278393  cmp eax,3
0xc278396  jne short 0xC278370
0xc278398  mov rax,[rdi+0x18]
0xc27839c  lea rcx,[rax+rax*4]
0xc2783a0  shl rcx,3
0xc2783a4  mov rdx,[rbp+0x3468]
0xc2783ab  mov rax,rdx
0xc2783ae  add rcx,[r13+0x238]
0xc2783b5  mov rdx,[rdx+8]
0xc2783b9  cmp byte ptr [rdx+0x19],0
0xc2783bd  jne short 0xC2783ED
0xc2783bf  mov r8,[rcx+0x20]
0xc2783c3  mov rax,[rbp+0x3468]
0xc2783ca  nop [rax+rax]
0xc2783d0  xor r9d,r9d
0xc2783d3  cmp [rdx+0x20],r8
0xc2783d7  setb r9b
0xc2783db  cmovae rax,rdx
0xc2783df  shl r9d,4
0xc2783e3  mov rdx,[rdx+r9]
0xc2783e7  cmp byte ptr [rdx+0x19],0
0xc2783eb  je short 0xC2783D0
0xc2783ed  cmp byte ptr [rax+0x19],0
0xc2783f1  jne 0xC278FA6
0xc2783f7  cmp rax,[rbp+0x3468]
0xc2783fe  je 0xC278FA6
0xc278404  mov rdx,[rax+0x20]
0xc278408  cmp [rcx+0x20],rdx
0xc27840c  jb 0xC278FA6
0xc278412  mov rcx,[rdi]
0xc278415  mov [rbp+0x1FC0],rcx
0xc27841c  cmp byte ptr [rax+0x38],0
0xc278420  jne 0xC27BD7D
0xc278426  lea rdx,[rbp+0x1FC8]
0xc27842d  movdqu [rdx],xmm7
0xc278431  mov rdx,[rax+0x30]
0xc278435  test rdx,rdx
0xc278438  je 0xC2785A9
0xc27843e  lock inc dword ptr [rdx+8]
0xc278442  mov rsi,[rax+0x30]
0xc278446  jmp 0xC2785AB
0xc27844b  nop [rax+rax]

### Phase 8 (0xc278450 - 0xc2784f8)
0xc278450  cmp byte ptr [rdi+0x29],0
0xc278454  jne 0xC2791B1
0xc27845a  mov rax,[rdi]
0xc27845d  mov [rbp+0x1FC0],rax
0xc278464  lea rcx,[rbp+0x1FC8]
0xc27846b  movdqu [rcx],xmm7
0xc27846f  mov rcx,[rdi+0x20]
0xc278473  test rcx,rcx
0xc278476  je 0xC278513
0xc27847c  lock inc dword ptr [rcx+8]
0xc278480  mov rsi,[rdi+0x20]
0xc278484  jmp 0xC278515
0xc278489  nop [rax]
0xc278490  mov rax,[rdi]
0xc278493  mov [rbp+0x1FC0],rax
0xc27849a  lea rcx,[rbp+0x1FC8]
0xc2784a1  movdqu [rcx],xmm7
0xc2784a5  mov rcx,[rdi+0x20]
0xc2784a9  test rcx,rcx
0xc2784ac  je short 0xC2784B8
0xc2784ae  lock inc dword ptr [rcx+8]
0xc2784b2  mov rsi,[rdi+0x20]
0xc2784b6  jmp short 0xC2784BA
0xc2784b8  xor esi,esi
0xc2784ba  mov rcx,[rdi+0x18]
0xc2784be  mov [rbp+0x1FC8],rcx
0xc2784c5  mov [rbp+0x1FD0],rsi
0xc2784cc  mov edx,[rdi+0x10]
0xc2784cf  lea r8,[rbp+0x1FD8]
0xc2784d6  mov [r8+8],edx
0xc2784da  mov rdx,[rdi+8]
0xc2784de  mov [r8],rdx
0xc2784e1  mov word ptr [rbp+0x1FE4],0
0xc2784ea  mov rdx,[rbp+0x3338]
0xc2784f1  cmp rdx,[rbp+0x3340]
0xc2784f8  jne short 0xC27855D

### Phase 9 (0xc2784fa - 0xc278587)
0xc2784fa  lea rcx,[rbp+0x3330]
0xc278501  lea r8,[rbp+0x1FC0]
0xc278508  call 0xC27F940
0xc27850d  nop
0xc27850e  jmp 0xC278655
0xc278513  xor esi,esi
0xc278515  mov rcx,[rdi+0x18]
0xc278519  mov [rbp+0x1FC8],rcx
0xc278520  mov [rbp+0x1FD0],rsi
0xc278527  mov edx,[rdi+0x10]
0xc27852a  lea r8,[rbp+0x1FD8]
0xc278531  mov [r8+8],edx
0xc278535  mov rdx,[rdi+8]
0xc278539  mov [r8],rdx
0xc27853c  movzx edx,byte ptr [rdi+0x28]
0xc278540  mov [rbp+0x1FE4],dl
0xc278546  mov byte ptr [rbp+0x1FE5],0
0xc27854d  mov rdx,[rbp+0x3338]
0xc278554  cmp rdx,[rbp+0x3340]
0xc27855b  je short 0xC278590
0xc27855d  mov [rdx],rax
0xc278560  movdqu [rdx+8],xmm7
0xc278565  test rsi,rsi
0xc278568  je short 0xC278585
0xc27856a  lock inc dword ptr [rsi+8]
0xc27856e  mov rcx,[rbp+0x1FC8]
0xc278575  mov rsi,[rbp+0x1FD0]
0xc27857c  mov [rdx+8],rcx
0xc278580  jmp 0xC278633
0xc278585  xor esi,esi
0xc278587  mov [rdx+8],rcx

### Phase 10 (0xc27858b - 0xc27862d)
0xc27858b  jmp 0xC278633
0xc278590  lea rcx,[rbp+0x3330]
0xc278597  lea r8,[rbp+0x1FC0]
0xc27859e  call 0xC27F940
0xc2785a3  nop
0xc2785a4  jmp 0xC278655
0xc2785a9  xor esi,esi
0xc2785ab  mov rax,[rax+0x28]
0xc2785af  mov [rbp+0x1FC8],rax
0xc2785b6  mov [rbp+0x1FD0],rsi
0xc2785bd  mov edx,[rdi+0x10]
0xc2785c0  lea r8,[rbp+0x1FD8]
0xc2785c7  mov [r8+8],edx
0xc2785cb  mov rdx,[rdi+8]
0xc2785cf  mov [r8],rdx
0xc2785d2  movzx edx,byte ptr [rdi+0x20]
0xc2785d6  mov [rbp+0x1FE4],dl
0xc2785dc  movzx edx,byte ptr [rdi+0x21]
0xc2785e0  mov [rbp+0x1FE5],dl
0xc2785e6  mov rdx,[rbp+0x3338]
0xc2785ed  cmp rdx,[rbp+0x3340]
0xc2785f4  je short 0xC278617
0xc2785f6  mov [rdx],rcx
0xc2785f9  movdqu [rdx+8],xmm7
0xc2785fe  test rsi,rsi
0xc278601  je short 0xC27862D
0xc278603  lock inc dword ptr [rsi+8]
0xc278607  mov rax,[rbp+0x1FC8]
0xc27860e  mov rsi,[rbp+0x1FD0]
0xc278615  jmp short 0xC27862F
0xc278617  lea rcx,[rbp+0x3330]
0xc27861e  lea r8,[rbp+0x1FC0]
0xc278625  call 0xC27F940
0xc27862a  nop
0xc27862b  jmp short 0xC278655
0xc27862d  xor esi,esi

### Phase 11 (0xc27862f - 0xc278691)
0xc27862f  mov [rdx+8],rax
0xc278633  mov [rdx+0x10],rsi
0xc278637  lea rcx,[rbp+0x1FD8]
0xc27863e  mov rax,[rcx]
0xc278641  mov rcx,[rcx+6]
0xc278645  mov [rdx+0x18],rax
0xc278649  mov [rdx+0x1E],rcx
0xc27864d  add qword ptr [rbp+0x3338],0x28
0xc278655  test rsi,rsi
0xc278658  je 0xC278370
0xc27865e  lock dec dword ptr [rsi+8]
0xc278662  jne 0xC278370
0xc278668  mov rax,[rsi]
0xc27866b  mov rax,[rax]
0xc27866e  mov rcx,rsi
0xc278671  call qword ptr [0xF99FFA0]
0xc278677  lock dec dword ptr [rsi+0xC]
0xc27867b  jne 0xC278370
0xc278681  mov rax,[rsi]
0xc278684  mov rax,[rax+8]
0xc278688  mov rcx,rsi
0xc27868b  call qword ptr [0xF99FFA0]
0xc278691  jmp 0xC278370

### Phase 12 (0xc2786a0 - 0xc278755)
0xc2786a0  mov rdi,[r13+0x268]
0xc2786a7  mov rbx,[r13+0x270]
0xc2786ae  jmp short 0xC2786B4
0xc2786b0  add rdi,0x20
0xc2786b4  cmp rdi,rbx
0xc2786b7  je 0xC2788F0
0xc2786bd  movzx eax,byte ptr [rdi+0x18]
0xc2786c1  cmp eax,2
0xc2786c4  je 0xC278790
0xc2786ca  cmp eax,1
0xc2786cd  jne short 0xC2786B0
0xc2786cf  mov rax,[rdi+8]
0xc2786d3  lea rcx,[rax+rax*4]
0xc2786d7  shl rcx,3
0xc2786db  mov rdx,[rbp+0x3468]
0xc2786e2  mov rax,rdx
0xc2786e5  add rcx,[r13+0x238]
0xc2786ec  mov rdx,[rdx+8]
0xc2786f0  cmp byte ptr [rdx+0x19],0
0xc2786f4  jne short 0xC27872D
0xc2786f6  mov r8,[rcx+0x20]
0xc2786fa  mov rax,[rbp+0x3468]
0xc278701  nop [rax+rax]
0xc278710  xor r9d,r9d
0xc278713  cmp [rdx+0x20],r8
0xc278717  setb r9b
0xc27871b  cmovae rax,rdx
0xc27871f  shl r9d,4
0xc278723  mov rdx,[rdx+r9]
0xc278727  cmp byte ptr [rdx+0x19],0
0xc27872b  je short 0xC278710
0xc27872d  cmp byte ptr [rax+0x19],0
0xc278731  jne 0xC278F82
0xc278737  cmp rax,[rbp+0x3468]
0xc27873e  je 0xC278F82
0xc278744  mov rdx,[rax+0x20]
0xc278748  cmp [rcx+0x20],rdx
0xc27874c  jb 0xC278F82
0xc278752  mov rcx,[rdi]
0xc278755  mov [rbp+0x1FC0],rcx

### Phase 13 (0xc27875c - 0xc27880f)
0xc27875c  cmp byte ptr [rax+0x38],1
0xc278760  jne 0xC27BD77
0xc278766  lea rdx,[rbp+0x1FC8]
0xc27876d  movdqu [rdx],xmm7
0xc278771  mov rdx,[rax+0x30]
0xc278775  test rdx,rdx
0xc278778  je 0xC278828
0xc27877e  lock inc dword ptr [rdx+8]
0xc278782  mov rsi,[rax+0x30]
0xc278786  jmp 0xC27882A
0xc27878b  nop [rax+rax]
0xc278790  mov rax,[rdi]
0xc278793  mov [rbp+0x1FC0],rax
0xc27879a  lea rcx,[rbp+0x1FC8]
0xc2787a1  movdqu [rcx],xmm7
0xc2787a5  mov rcx,[rdi+0x10]
0xc2787a9  test rcx,rcx
0xc2787ac  je short 0xC2787B8
0xc2787ae  lock inc dword ptr [rcx+8]
0xc2787b2  mov rsi,[rdi+0x10]
0xc2787b6  jmp short 0xC2787BA
0xc2787b8  xor esi,esi
0xc2787ba  mov rcx,[rdi+8]
0xc2787be  mov [rbp+0x1FC8],rcx
0xc2787c5  mov [rbp+0x1FD0],rsi
0xc2787cc  mov byte ptr [rbp+0x1FD8],1
0xc2787d3  mov rdx,[rbp+0x3350]
0xc2787da  cmp rdx,[rbp+0x3358]
0xc2787e1  je short 0xC27880F
0xc2787e3  mov [rdx],rax
0xc2787e6  movdqu [rdx+8],xmm7
0xc2787eb  test rsi,rsi
0xc2787ee  je 0xC27888A
0xc2787f4  lock inc dword ptr [rsi+8]
0xc2787f8  mov rcx,[rbp+0x1FC8]
0xc2787ff  mov rsi,[rbp+0x1FD0]
0xc278806  mov [rdx+8],rcx
0xc27880a  jmp 0xC278898
0xc27880f  lea rcx,[rbp+0x3348]

### Phase 14 (0xc278816 - 0xc27888a)
0xc278816  lea r8,[rbp+0x1FC0]
0xc27881d  call 0xC27FCC0
0xc278822  nop
0xc278823  jmp 0xC2788A8
0xc278828  xor esi,esi
0xc27882a  mov rax,[rax+0x28]
0xc27882e  mov [rbp+0x1FC8],rax
0xc278835  mov [rbp+0x1FD0],rsi
0xc27883c  mov byte ptr [rbp+0x1FD8],1
0xc278843  mov rdx,[rbp+0x3350]
0xc27884a  cmp rdx,[rbp+0x3358]
0xc278851  je short 0xC278874
0xc278853  mov [rdx],rcx
0xc278856  movdqu [rdx+8],xmm7
0xc27885b  test rsi,rsi
0xc27885e  je short 0xC278892
0xc278860  lock inc dword ptr [rsi+8]
0xc278864  mov rax,[rbp+0x1FC8]
0xc27886b  mov rsi,[rbp+0x1FD0]
0xc278872  jmp short 0xC278894
0xc278874  lea rcx,[rbp+0x3348]
0xc27887b  lea r8,[rbp+0x1FC0]
0xc278882  call 0xC27FCC0
0xc278887  nop
0xc278888  jmp short 0xC2788A8
0xc27888a  xor esi,esi

### Phase 15 (0xc27888c - 0xc2788e4)
0xc27888c  mov [rdx+8],rcx
0xc278890  jmp short 0xC278898
0xc278892  xor esi,esi
0xc278894  mov [rdx+8],rax
0xc278898  mov [rdx+0x10],rsi
0xc27889c  mov byte ptr [rdx+0x18],1
0xc2788a0  add qword ptr [rbp+0x3350],0x20
0xc2788a8  test rsi,rsi
0xc2788ab  je 0xC2786B0
0xc2788b1  lock dec dword ptr [rsi+8]
0xc2788b5  jne 0xC2786B0
0xc2788bb  mov rax,[rsi]
0xc2788be  mov rax,[rax]
0xc2788c1  mov rcx,rsi
0xc2788c4  call qword ptr [0xF99FFA0]
0xc2788ca  lock dec dword ptr [rsi+0xC]
0xc2788ce  jne 0xC2786B0
0xc2788d4  mov rax,[rsi]
0xc2788d7  mov rax,[rax+8]
0xc2788db  mov rcx,rsi
0xc2788de  call qword ptr [0xF99FFA0]
0xc2788e4  jmp 0xC2786B0

### Phase 16 (0xc2788e9 - 0xc2789bf)
0xc2788e9  nop [rax]
0xc2788f0  mov r15,[r13+0x280]
0xc2788f7  mov rbx,[r13+0x288]
0xc2788fe  cmp r15,rbx
0xc278901  mov rdi,[rbp+0x3460]
0xc278908  je 0xC278E60
0xc27890e  mov [rbp+0x3430],rbx
0xc278915  jmp short 0xC27892D
0xc278917  nop [rax+rax]
0xc278920  add r15,0x30
0xc278924  cmp r15,rbx
0xc278927  je 0xC278E60
0xc27892d  cmp byte ptr [r15+0x28],4
0xc278932  jne 0xC2791D2
0xc278938  mov rax,[r15+0x10]
0xc27893c  lea rcx,[rax+rax*4]
0xc278940  shl rcx,3
0xc278944  mov rdx,[rbp+0x3468]
0xc27894b  mov rax,rdx
0xc27894e  add rcx,[r13+0x238]
0xc278955  mov rdx,[rdx+8]
0xc278959  cmp byte ptr [rdx+0x19],0
0xc27895d  jne short 0xC27898D
0xc27895f  mov r8,[rcx+0x20]
0xc278963  mov rax,[rbp+0x3468]
0xc27896a  nop [rax+rax]
0xc278970  xor r9d,r9d
0xc278973  cmp [rdx+0x20],r8
0xc278977  setb r9b
0xc27897b  cmovae rax,rdx
0xc27897f  shl r9d,4
0xc278983  mov rdx,[rdx+r9]
0xc278987  cmp byte ptr [rdx+0x19],0
0xc27898b  je short 0xC278970
0xc27898d  cmp byte ptr [rax+0x19],0
0xc278991  jne 0xC278FCA
0xc278997  cmp rax,[rbp+0x3468]
0xc27899e  je 0xC278FCA
0xc2789a4  mov rdx,[rax+0x20]
0xc2789a8  cmp [rcx+0x20],rdx
0xc2789ac  jb 0xC278FCA
0xc2789b2  mov r14,r13
0xc2789b5  mov r13,[r15]
0xc2789b8  mov [rbp+0x1FC0],r13
0xc2789bf  cmp byte ptr [rax+0x38],2

### Phase 17 (0xc2789c3 - 0xc278a50)
0xc2789c3  jne 0xC27BD83
0xc2789c9  lea rcx,[rbp+0x1FC8]
0xc2789d0  movdqu [rcx],xmm7
0xc2789d4  mov rcx,[rax+0x30]
0xc2789d8  test rcx,rcx
0xc2789db  je short 0xC2789F0
0xc2789dd  lock inc dword ptr [rcx+8]
0xc2789e1  mov r12,[rax+0x30]
0xc2789e5  jmp short 0xC2789F3
0xc2789e7  nop [rax+rax]
0xc2789f0  xor r12d,r12d
0xc2789f3  mov rcx,[rax+0x28]
0xc2789f7  mov [rbp+0x1FC8],rcx
0xc2789fe  mov [rbp+0x1FD0],r12
0xc278a05  mov eax,[r15+8]
0xc278a09  mov [rbp+0x1FD8],eax
0xc278a0f  mov rdi,[rbp+0x3368]
0xc278a16  cmp rdi,[rbp+0x3370]
0xc278a1d  je short 0xC278A50
0xc278a1f  mov [rdi],r13
0xc278a22  movdqu [rdi+8],xmm7
0xc278a27  test r12,r12
0xc278a2a  je 0xC278B20
0xc278a30  lock inc dword ptr [r12+8]
0xc278a36  mov rcx,[rbp+0x1FC8]
0xc278a3d  mov rsi,[rbp+0x1FD0]
0xc278a44  jmp 0xC278B22
0xc278a49  nop [rax]
0xc278a50  mov [rbp+0x3428],rcx

### Phase 18 (0xc278a57 - 0xc278abe)
0xc278a57  mov [rbp+0x3438],eax
0xc278a5d  mov rsi,rdi
0xc278a60  sub rsi,[rbp+0x3360]
0xc278a67  mov rcx,rsi
0xc278a6a  sar rcx,5
0xc278a6e  lea r9,[rcx+1]
0xc278a72  mov rax,rcx
0xc278a75  shr rax,1
0xc278a78  mov r8,0x7FFFFFFFFFFFFFF
0xc278a82  mov rdx,r8
0xc278a85  sub rdx,rax
0xc278a88  add rax,rcx
0xc278a8b  cmp rax,r9
0xc278a8e  cmovbe rax,r9
0xc278a92  cmp rcx,rdx
0xc278a95  cmova rax,r8
0xc278a99  mov rcx,rax
0xc278a9c  shr rcx,0x3B
0xc278aa0  jne 0xC27BDD3
0xc278aa6  mov rdx,rax
0xc278aa9  shl rdx,5
0xc278aad  test rax,rax
0xc278ab0  mov [rbp+0x3458],r9
0xc278ab7  mov [rbp+0x3470],rdx
0xc278abe  je 0xC278B77

### Phase 19 (0xc278ac4 - 0xc278b48)
0xc278ac4  cmp rax,0x80
0xc278aca  jb 0xC278B4D
0xc278ad0  mov rcx,0x7FFFFFFFFFFFFFF
0xc278ada  cmp rax,rcx
0xc278add  je 0xC27BE23
0xc278ae3  add rdx,0x27
0xc278ae7  mov rcx,[0x1233E1A8]
0xc278aee  mov rax,[rcx]
0xc278af1  mov rax,[rax+8]
0xc278af5  mov [rbp+0x3440],rdx
0xc278afc  call qword ptr [0xF99FFA0]
0xc278b02  nop
0xc278b03  mov rbx,rax
0xc278b06  test rax,rax
0xc278b09  je 0xC278E42
0xc278b0f  mov rax,rbx
0xc278b12  add rbx,0x27
0xc278b16  and rbx,0xFFFFFFFFFFFFFFE0
0xc278b1a  mov [rbx-8],rax
0xc278b1e  jmp short 0xC278B79
0xc278b20  xor esi,esi
0xc278b22  mov r13,r14
0xc278b25  mov [rdi+8],rcx
0xc278b29  mov [rdi+0x10],rsi
0xc278b2d  mov [rdi+0x18],eax
0xc278b30  add qword ptr [rbp+0x3368],0x20
0xc278b38  mov rdi,[rbp+0x3460]
0xc278b3f  test rsi,rsi
0xc278b42  jne 0xC278E0A
0xc278b48  jmp 0xC278920

### Phase 20 (0xc278b4d - 0xc278bd0)
0xc278b4d  mov rcx,[0x1233E1A8]
0xc278b54  mov rax,[rcx]
0xc278b57  mov rax,[rax+8]
0xc278b5b  call qword ptr [0xF99FFA0]
0xc278b61  nop
0xc278b62  mov rbx,rax
0xc278b65  test rax,rax
0xc278b68  jne short 0xC278B79
0xc278b6a  mov rcx,[rbp+0x3470]
0xc278b71  call 0x9BC830
0xc278b76  nop
0xc278b77  xor ebx,ebx
0xc278b79  mov [rbx+rsi],r13
0xc278b7d  movdqu [rbx+rsi+8],xmm7
0xc278b83  test r12,r12
0xc278b86  je short 0xC278BA1
0xc278b88  lock inc dword ptr [r12+8]
0xc278b8e  mov rdx,[rbp+0x1FC8]
0xc278b95  mov rax,[rbp+0x1FD0]
0xc278b9c  mov r13,r14
0xc278b9f  jmp short 0xC278BAD
0xc278ba1  xor eax,eax
0xc278ba3  mov r13,r14
0xc278ba6  mov rdx,[rbp+0x3428]
0xc278bad  lea rcx,[rbx+rsi]
0xc278bb1  mov [rcx+8],rdx
0xc278bb5  mov [rcx+0x10],rax
0xc278bb9  mov eax,[rbp+0x3438]
0xc278bbf  mov [rcx+0x18],eax
0xc278bc2  mov r12,[rbp+0x3360]
0xc278bc9  mov rax,[rbp+0x3368]
0xc278bd0  cmp rdi,rax

### Phase 21 (0xc278bd3 - 0xc278c57)
0xc278bd3  je 0xC278CAF
0xc278bd9  cmp r12,rdi
0xc278bdc  je short 0xC278C42
0xc278bde  xor eax,eax
0xc278be0  jmp short 0xC278C1D
0xc278be2  nop [rax+rax]
0xc278bf0  lea rcx,[r12+rax]
0xc278bf4  lea rdx,[rbx+rax]
0xc278bf8  mov r8,[rcx+8]
0xc278bfc  mov [rdx+8],r8
0xc278c00  mov r8,[rcx+0x10]
0xc278c04  mov [rdx+0x10],r8
0xc278c08  mov r8d,[rcx+0x18]
0xc278c0c  mov [rdx+0x18],r8d
0xc278c10  add rax,0x20
0xc278c14  add rcx,0x20
0xc278c18  cmp rcx,rdi
0xc278c1b  je short 0xC278C3B
0xc278c1d  mov rcx,[r12+rax]
0xc278c21  mov [rbx+rax],rcx
0xc278c25  movdqu [rbx+rax+8],xmm7
0xc278c2b  mov rcx,[r12+rax+0x10]
0xc278c30  test rcx,rcx
0xc278c33  je short 0xC278BF0
0xc278c35  lock inc dword ptr [rcx+8]
0xc278c39  jmp short 0xC278BF0
0xc278c3b  mov rax,[rbp+0x3368]
0xc278c42  cmp rdi,rax
0xc278c45  je 0xC278D10
0xc278c4b  lea rcx,[rbx+rsi]
0xc278c4f  add rcx,0x38
0xc278c53  xor edx,edx
0xc278c55  jmp short 0xC278C8F
0xc278c57  nop [rax+rax]

### Phase 22 (0xc278c60 - 0xc278cf5)
0xc278c60  lea r8,[rdi+rdx]
0xc278c64  mov r9,[r8+8]
0xc278c68  mov [rcx+rdx-0x10],r9
0xc278c6d  mov r9,[r8+0x10]
0xc278c71  mov [rcx+rdx-8],r9
0xc278c76  mov r9d,[r8+0x18]
0xc278c7a  mov [rcx+rdx],r9d
0xc278c7e  add rdx,0x20
0xc278c82  add r8,0x20
0xc278c86  cmp r8,rax
0xc278c89  je 0xC278D10
0xc278c8f  mov r8,[rdi+rdx]
0xc278c93  mov [rcx+rdx-0x18],r8
0xc278c98  movdqu [rcx+rdx-0x10],xmm7
0xc278c9e  mov r8,[rdi+rdx+0x10]
0xc278ca3  test r8,r8
0xc278ca6  je short 0xC278C60
0xc278ca8  lock inc dword ptr [r8+8]
0xc278cad  jmp short 0xC278C60
0xc278caf  cmp r12,rdi
0xc278cb2  je short 0xC278D17
0xc278cb4  xor eax,eax
0xc278cb6  jmp short 0xC278CED
0xc278cb8  nop [rax+rax]
0xc278cc0  lea rcx,[r12+rax]
0xc278cc4  lea rdx,[rbx+rax]
0xc278cc8  mov r8,[rcx+8]
0xc278ccc  mov [rdx+8],r8
0xc278cd0  mov r8,[rcx+0x10]
0xc278cd4  mov [rdx+0x10],r8
0xc278cd8  mov r8d,[rcx+0x18]
0xc278cdc  mov [rdx+0x18],r8d
0xc278ce0  add rax,0x20
0xc278ce4  add rcx,0x20
0xc278ce8  cmp rcx,rdi
0xc278ceb  je short 0xC278D10
0xc278ced  mov rcx,[r12+rax]
0xc278cf1  mov [rbx+rax],rcx
0xc278cf5  movdqu [rbx+rax+8],xmm7

### Phase 23 (0xc278cfb - 0xc278d9f)
0xc278cfb  mov rcx,[r12+rax+0x10]
0xc278d00  test rcx,rcx
0xc278d03  je short 0xC278CC0
0xc278d05  lock inc dword ptr [rcx+8]
0xc278d09  jmp short 0xC278CC0
0xc278d0b  nop [rax+rax]
0xc278d10  mov r12,[rbp+0x3360]
0xc278d17  test r12,r12
0xc278d1a  mov rdi,[rbp+0x3460]
0xc278d21  je 0xC278DC6
0xc278d27  mov rdi,[rbp+0x3368]
0xc278d2e  cmp r12,rdi
0xc278d31  jne short 0xC278D49
0xc278d33  jmp short 0xC278D87
0xc278d35  nop [rax+rax]
0xc278d40  add r12,0x20
0xc278d44  cmp r12,rdi
0xc278d47  je short 0xC278D80
0xc278d49  mov rsi,[r12+0x10]
0xc278d4e  test rsi,rsi
0xc278d51  je short 0xC278D40
0xc278d53  lock dec dword ptr [rsi+8]
0xc278d57  jne short 0xC278D40
0xc278d59  mov rax,[rsi]
0xc278d5c  mov rax,[rax]
0xc278d5f  mov rcx,rsi
0xc278d62  call qword ptr [0xF99FFA0]
0xc278d68  lock dec dword ptr [rsi+0xC]
0xc278d6c  jne short 0xC278D40
0xc278d6e  mov rax,[rsi]
0xc278d71  mov rax,[rax+8]
0xc278d75  mov rcx,rsi
0xc278d78  call qword ptr [0xF99FFA0]
0xc278d7e  jmp short 0xC278D40
0xc278d80  mov r12,[rbp+0x3360]
0xc278d87  mov rdx,[rbp+0x3370]
0xc278d8e  sub rdx,r12
0xc278d91  cmp rdx,0x1000
0xc278d98  mov rdi,[rbp+0x3460]
0xc278d9f  jb short 0xC278DBE

### Phase 24 (0xc278da1 - 0xc278e04)
0xc278da1  mov rax,[r12-8]
0xc278da6  add r12,0xFFFFFFFFFFFFFFF8
0xc278daa  sub r12,rax
0xc278dad  cmp r12,0x20
0xc278db1  jae 0xC27BCD1
0xc278db7  add rdx,0x27
0xc278dbb  mov r12,rax
0xc278dbe  mov rcx,r12
0xc278dc1  call 0xE935700
0xc278dc6  mov [rbp+0x3360],rbx
0xc278dcd  mov rax,[rbp+0x3458]
0xc278dd4  shl rax,5
0xc278dd8  add rax,rbx
0xc278ddb  mov [rbp+0x3368],rax
0xc278de2  mov rax,[rbp+0x3470]
0xc278de9  add rax,rbx
0xc278dec  mov [rbp+0x3370],rax
0xc278df3  mov rsi,[rbp+0x1FD0]
0xc278dfa  mov rbx,[rbp+0x3430]
0xc278e01  test rsi,rsi
0xc278e04  je 0xC278920

### Phase 25 (0xc278e0a - 0xc278e7b)
0xc278e0a  lock dec dword ptr [rsi+8]
0xc278e0e  jne 0xC278920
0xc278e14  mov rax,[rsi]
0xc278e17  mov rax,[rax]
0xc278e1a  mov rcx,rsi
0xc278e1d  call qword ptr [0xF99FFA0]
0xc278e23  lock dec dword ptr [rsi+0xC]
0xc278e27  jne 0xC278920
0xc278e2d  mov rax,[rsi]
0xc278e30  mov rax,[rax+8]
0xc278e34  mov rcx,rsi
0xc278e37  call qword ptr [0xF99FFA0]
0xc278e3d  jmp 0xC278920
0xc278e42  mov rcx,[rbp+0x3440]
0xc278e49  call 0x9BC830
0xc278e4e  nop
0xc278e4f  jmp 0xC278B0F
0xc278e54  nop [rax+rax]
0xc278e60  add rdi,0x28
0xc278e64  mov rcx,[rdi]
0xc278e67  mov rax,[rcx]
0xc278e6a  mov rax,[rax+0x10]
0xc278e6e  lea rdx,[rbp+0x1FC0]
0xc278e75  call qword ptr [0xF99FFA0]
0xc278e7b  nop

### Phase 26 (0xc278e7c - 0xc278f7d)
0xc278e7c  movups xmm0,[rbp+0x1FC0]
0xc278e83  mov rax,[rbp+0x1FB0]
0xc278e8a  shl rax,4
0xc278e8e  movups [rbp+rax-0x50],xmm0
0xc278e93  inc qword ptr [rbp+0x1FB0]
0xc278e9a  movaps [rbp+0x3310],xmm0
0xc278ea1  mov r14,[rbp+0x32E8]
0xc278ea8  cmp r14,[rbp+0x32F0]
0xc278eaf  je 0xC278FF7
0xc278eb5  movdqu [r14],xmm7
0xc278eba  mov rcx,[rbp+0x3460]
0xc278ec1  mov rax,[rcx+0x28]
0xc278ec5  mov [r14],rax
0xc278ec8  mov rax,[rcx+0x30]
0xc278ecc  mov [r14+8],rax
0xc278ed0  movdqu [rdi],xmm7
0xc278ed4  movups xmm0,[rbp+0x331C]
0xc278edb  movups [r14+0x1C],xmm0
0xc278ee0  movaps xmm0,[rbp+0x3310]
0xc278ee7  movups [r14+0x10],xmm0
0xc278eec  mov rax,[rbp+0x3340]
0xc278ef3  mov qword ptr [rbp+0x3340],0
0xc278efe  movaps xmm0,[rbp+0x3330]
0xc278f05  movdqa [rbp+0x3330],xmm7
0xc278f0d  movups [r14+0x30],xmm0
0xc278f12  mov [r14+0x40],rax
0xc278f16  mov rax,[rbp+0x3358]
0xc278f1d  mov qword ptr [rbp+0x3358],0
0xc278f28  movups xmm0,[rbp+0x3348]
0xc278f2f  movdqu [rbp+0x3348],xmm7
0xc278f37  movups [r14+0x48],xmm0
0xc278f3c  mov [r14+0x58],rax
0xc278f40  mov rax,[rbp+0x3370]
0xc278f47  mov qword ptr [rbp+0x3370],0
0xc278f52  movaps xmm0,[rbp+0x3360]
0xc278f59  movdqa [rbp+0x3360],xmm7
0xc278f61  movups [r14+0x60],xmm0
0xc278f66  mov [r14+0x70],rax
0xc278f6a  mov qword ptr [r14+0x78],0
0xc278f72  sub r14,0xFFFFFFFFFFFFFF80
0xc278f76  mov [rbp+0x32E8],r14
0xc278f7d  jmp 0xC279403

### Phase 27 (0xc278f82 - 0xc27900b)
0xc278f82  mov rax,[rbp+0x3450]
0xc278f89  mov rcx,[rax]
0xc278f8c  mov rax,[rcx]
0xc278f8f  mov rax,[rax+0x10]
0xc278f93  lea rdx,[rbp+0x1FC0]
0xc278f9a  call qword ptr [0xF99FFA0]
0xc278fa0  nop
0xc278fa1  jmp 0xC279CB7
0xc278fa6  mov rax,[rbp+0x3450]
0xc278fad  mov rcx,[rax]
0xc278fb0  mov rax,[rcx]
0xc278fb3  mov rax,[rax+0x10]
0xc278fb7  lea rdx,[rbp+0x1FC0]
0xc278fbe  call qword ptr [0xF99FFA0]
0xc278fc4  nop
0xc278fc5  jmp 0xC279CB7
0xc278fca  mov rax,[rbp+0x3450]
0xc278fd1  mov rcx,[rax]
0xc278fd4  mov rax,[rcx]
0xc278fd7  mov rax,[rax+0x10]
0xc278fdb  lea rdx,[rbp+0x1FC0]
0xc278fe2  call qword ptr [0xF99FFA0]
0xc278fe8  nop
0xc278fe9  jmp 0xC279CB7
0xc278fee  xor edi,edi
0xc278ff0  xor edx,edx
0xc278ff2  jmp 0xC2790ED
0xc278ff7  mov r12,[rbp+0x32E0]
0xc278ffe  mov r13,r14
0xc279001  sub r13,r12
0xc279004  mov rax,r13
0xc279007  sar rax,7
0xc27900b  lea r8,[rax+1]

### Phase 28 (0xc27900f - 0xc2790a0)
0xc27900f  mov rbx,rax
0xc279012  shr rbx,1
0xc279015  mov rdx,0x1FFFFFFFFFFFFFF
0xc27901f  mov rcx,rdx
0xc279022  sub rcx,rbx
0xc279025  add rbx,rax
0xc279028  cmp rbx,r8
0xc27902b  cmovbe rbx,r8
0xc27902f  cmp rax,rcx
0xc279032  cmova rbx,rdx
0xc279036  mov rax,rbx
0xc279039  shr rax,0x39
0xc27903d  jne 0xC27BE3B
0xc279043  test rbx,rbx
0xc279046  mov [rbp+0x3470],r8
0xc27904d  je 0xC27923C
0xc279053  mov rsi,rbx
0xc279056  shl rsi,7
0xc27905a  cmp rbx,0x20
0xc27905e  jb 0xC279213
0xc279064  or rsi,0x27
0xc279068  mov rcx,[0x1233E1A8]
0xc27906f  mov rax,[rcx]
0xc279072  mov rax,[rax+8]
0xc279076  mov rdx,rsi
0xc279079  call qword ptr [0xF99FFA0]
0xc27907f  nop
0xc279080  mov r15,rax
0xc279083  test rax,rax
0xc279086  je 0xC2794D2
0xc27908c  mov rax,r15
0xc27908f  add r15,0x27
0xc279093  and r15,0xFFFFFFFFFFFFFFE0
0xc279097  mov [r15-8],rax
0xc27909b  jmp 0xC27923F
0xc2790a0  mov rcx,[0x1233E1A8]

### Phase 29 (0xc2790a7 - 0xc279116)
0xc2790a7  mov rax,[rcx]
0xc2790aa  mov rax,[rax+8]
0xc2790ae  mov rdx,rsi
0xc2790b1  call qword ptr [0xF99FFA0]
0xc2790b7  nop
0xc2790b8  mov rdi,rax
0xc2790bb  test rax,rax
0xc2790be  je 0xC2794C2
0xc2790c4  mov [rbp+0x33F0],rdi
0xc2790cb  lea rbx,[rdi+rsi]
0xc2790cf  mov [rbp+0x3400],rbx
0xc2790d6  mov rcx,rdi
0xc2790d9  xor edx,edx
0xc2790db  mov r8,rsi
0xc2790de  call 0xEEC6ED0
0xc2790e3  mov rdx,rbx
0xc2790e6  mov [rbp+0x33F8],rbx
0xc2790ed  mov r8,rdx
0xc2790f0  sub r8,rdi
0xc2790f3  test r8,0xFFFFFFFF80000000
0xc2790fa  jne short 0xC279116

### Phase 30 (0xc279116 - 0xc2791ac)
0xc279116  cmp rdx,rdi
0xc279119  je 0xC2794EB
0xc27911f  mov rax,r8
0xc279122  and rax,0xFFFFFFFFFFFFFFE0
0xc279126  xor ecx,ecx
0xc279128  movdqa xmm0,xmm10
0xc27912d  nop [rax]
0xc279130  movdqa xmm1,xmm0
0xc279134  paddb xmm1,xmm11
0xc279139  movdqu [rdi+rcx],xmm0
0xc27913e  movdqu [rdi+rcx+0x10],xmm1
0xc279144  add rcx,0x20
0xc279148  paddb xmm0,xmm12
0xc27914d  cmp rax,rcx
0xc279150  jne short 0xC279130
0xc279152  cmp r8,rax
0xc279155  je 0xC2794EB
0xc27915b  test r8b,0x1C
0xc27915f  je 0xC279495
0xc279165  mov rcx,r8
0xc279168  and rcx,0xFFFFFFFFFFFFFFFC
0xc27916c  movzx r9d,al
0xc279170  movd xmm0,r9d
0xc279175  punpcklbw xmm0,xmm0
0xc279179  pshuflw xmm0,xmm0,0
0xc27917e  por xmm0,xmm8
0xc279183  nop [rax+rax]
0xc279190  movd [rdi+rax],xmm0
0xc279195  add rax,4
0xc279199  paddb xmm0,xmm9
0xc27919e  cmp rcx,rax
0xc2791a1  jne short 0xC279190
0xc2791a3  cmp r8,rcx
0xc2791a6  jne 0xC2794A0
0xc2791ac  jmp 0xC2794EB

### Phase 31 (0xc2791b1 - 0xc2791fd)
0xc2791b1  mov rax,[rbp+0x3450]
0xc2791b8  mov rcx,[rax]
0xc2791bb  mov rax,[rcx]
0xc2791be  mov rax,[rax+0x10]
0xc2791c2  lea rdx,[rbp+0x1FC0]
0xc2791c9  call qword ptr [0xF99FFA0]
0xc2791cf  nop
0xc2791d0  jmp short 0xC2791F1
0xc2791d2  mov rax,[rbp+0x3450]
0xc2791d9  mov rcx,[rax]
0xc2791dc  mov rax,[rcx]
0xc2791df  mov rax,[rax+0x10]
0xc2791e3  lea rdx,[rbp+0x1FC0]
0xc2791ea  call qword ptr [0xF99FFA0]
0xc2791f0  nop
0xc2791f1  mov dword ptr [rbp+0x3448],3
0xc2791fb  xor edi,edi
0xc2791fd  jmp 0xC279CC3

### Phase 32 (0xc279202 - 0xc27923f)
0xc279202  cmp r8,0x20
0xc279206  jae 0xC27940B
0xc27920c  xor eax,eax
0xc27920e  jmp 0xC279455
0xc279213  mov rcx,[0x1233E1A8]
0xc27921a  mov rax,[rcx]
0xc27921d  mov rax,[rax+8]
0xc279221  mov rdx,rsi
0xc279224  call qword ptr [0xF99FFA0]
0xc27922a  nop
0xc27922b  mov r15,rax
0xc27922e  test rax,rax
0xc279231  jne short 0xC27923F
0xc279233  mov rcx,rsi
0xc279236  call 0x9BC830
0xc27923b  nop
0xc27923c  xor r15d,r15d
0xc27923f  movdqu [r15+r13],xmm7

### Phase 33 (0xc279245 - 0xc279308)
0xc279245  mov rcx,[rbp+0x3460]
0xc27924c  mov rax,[rcx+0x28]
0xc279250  mov [r15+r13],rax
0xc279254  mov rax,[rcx+0x30]
0xc279258  mov [r15+r13+8],rax
0xc27925d  movdqu [rdi],xmm7
0xc279261  movups xmm0,[rbp+0x331C]
0xc279268  movups [r15+r13+0x1C],xmm0
0xc27926e  movaps xmm0,[rbp+0x3310]
0xc279275  movups [r15+r13+0x10],xmm0
0xc27927b  mov rax,[rbp+0x3340]
0xc279282  mov qword ptr [rbp+0x3340],0
0xc27928d  movaps xmm0,[rbp+0x3330]
0xc279294  movdqa [rbp+0x3330],xmm7
0xc27929c  movups [r15+r13+0x30],xmm0
0xc2792a2  mov [r15+r13+0x40],rax
0xc2792a7  mov rax,[rbp+0x3358]
0xc2792ae  mov qword ptr [rbp+0x3358],0
0xc2792b9  movups xmm0,[rbp+0x3348]
0xc2792c0  movdqu [rbp+0x3348],xmm7
0xc2792c8  movups [r15+r13+0x48],xmm0
0xc2792ce  mov [r15+r13+0x58],rax
0xc2792d3  mov rax,[rbp+0x3370]
0xc2792da  mov qword ptr [rbp+0x3370],0
0xc2792e5  movaps xmm0,[rbp+0x3360]
0xc2792ec  movdqa [rbp+0x3360],xmm7
0xc2792f4  movups [r15+r13+0x60],xmm0
0xc2792fa  mov [r15+r13+0x70],rax
0xc2792ff  mov qword ptr [r15+r13+0x78],0
0xc279308  cmp r12,r14

### Phase 34 (0xc27930b - 0xc2793fb)
0xc27930b  je 0xC2793EA
0xc279311  xor eax,eax
0xc279313  nop [rax+rax]
0xc279320  movdqu [r15+rax],xmm7
0xc279326  mov rcx,[r12+rax]
0xc27932a  mov [r15+rax],rcx
0xc27932e  mov rcx,[r12+rax+8]
0xc279333  mov [r15+rax+8],rcx
0xc279338  movdqu [r12+rax],xmm7
0xc27933e  movups xmm0,[r12+rax+0x10]
0xc279344  movups xmm1,[r12+rax+0x1C]
0xc27934a  movups [r15+rax+0x1C],xmm1
0xc279350  movups [r15+rax+0x10],xmm0
0xc279356  mov rcx,[r12+rax+0x40]
0xc27935b  mov qword ptr [r12+rax+0x40],0
0xc279364  movups xmm0,[r12+rax+0x30]
0xc27936a  movdqu [r12+rax+0x30],xmm7
0xc279371  movups [r15+rax+0x30],xmm0
0xc279377  mov [r15+rax+0x40],rcx
0xc27937c  mov rcx,[r12+rax+0x58]
0xc279381  mov qword ptr [r12+rax+0x58],0
0xc27938a  movups xmm0,[r12+rax+0x48]
0xc279390  movdqu [r12+rax+0x48],xmm7
0xc279397  movups [r15+rax+0x48],xmm0
0xc27939d  mov [r15+rax+0x58],rcx
0xc2793a2  mov rcx,[r12+rax+0x70]
0xc2793a7  mov qword ptr [r12+rax+0x70],0
0xc2793b0  movups xmm0,[r12+rax+0x60]
0xc2793b6  movdqu [r12+rax+0x60],xmm7
0xc2793bd  movups [r15+rax+0x60],xmm0
0xc2793c3  mov [r15+rax+0x70],rcx
0xc2793c8  mov rcx,[r12+rax+0x78]
0xc2793cd  mov [r15+rax+0x78],rcx
0xc2793d2  lea rcx,[r12+rax]
0xc2793d6  add rcx,0x80
0xc2793dd  sub rax,0xFFFFFFFFFFFFFF80
0xc2793e1  cmp rcx,r14
0xc2793e4  jne 0xC279320
0xc2793ea  lea rcx,[rbp+0x32E0]
0xc2793f1  mov rdx,r15
0xc2793f4  mov r8,[rbp+0x3470]
0xc2793fb  mov r9,rbx

## Dependency record vectors

### 40-byte element vector
- base: rbp+0x3330 (begin), rbp+0x3338 (end), rbp+0x3340 (cap)
- growth sites: 0xc278508, 0xc27859e, 0xc278625 → sub_c27f940
- element stride: 0x28 (40 bytes)

| offset | size | R/W | meaning | tag |
|--------|------|-----|---------|-----|
| 0x00   | 8    | W   | element handle (from [rdi] / [rbp+0x1FC0]) | elem_handle |
| 0x08   | 8    | W   | shared_ptr control or d+0x18 (from [rbp+0x1FC8]) | elem_ctrl_or_d18 |
| 0x10   | 8    | W   | shared_ptr control/ptr (from [rbp+0x1FD0]) | elem_shared_ptr |
| 0x18   | 8    | W   | declared entry d+8 handle/hash (from [rbp+0x1FD8]) | elem_d8_hash |
| 0x1E   | 2*   | W   | flag byte from d+0x28 (low byte), zero padding | elem_bound_flag |

\* Written via 8-byte store at 0x1E from [rbp+0x1FDE]; overlaps top 2 bytes of 0x18 field.

Store sequence (Phases 8-11): mov [rdx],rax / movdqu [rdx+8],xmm7 / mov [rdx+8],rcx / mov [rdx+0x10],rsi / mov [rdx+0x18],rax / mov [rdx+0x1E],rcx. lock inc dword ptr [rsi+8] increments shared_ptr control refcount at [ctrl+8]. end += 0x28 per element (add qword ptr [rbp+0x3338],0x28).

### 24-byte element vector
- base: rbp+0x3348 (begin), rbp+0x3350 (end), rbp+0x3358 (cap)
- growth sites: 0xc27881d, 0xc278882 → sub_c27fcc0
- element stride: 0x20 (24 bytes)

| offset | size | R/W | meaning | tag |
|--------|------|-----|---------|-----|
| 0x00   | 8    | W   | element handle from [rdi] | elem_handle |
| 0x08   | 8    | W   | declared entry d+8 (from [rbp+0x1FC8] = [rdi+8]) | elem_d8_hash |
| 0x10   | 8    | W   | shared_ptr ptr or 0 (from [rbp+0x1FD0]) | elem_shared_ptr |
| 0x18   | 1    | W   | bound flag (1 = bound, 0 = unbound) | elem_bound_flag |

Store sequence (Phases 13-15): mov [rdx],rax / movdqu [rdx+8],xmm7 / mov [rdx+8],rcx / mov [rdx+0x10],rsi / mov byte ptr [rdx+0x18],1. end += 0x20 per element (add qword ptr [rbp+0x3350],0x20). byte [rbp+0x1FD8]=1 set before storing to mark bound state.

## Per-pass body fields

### 0x80-byte per-pass record (built at r14=[rbp+0x32E8], Phase 26; empty-path variant at r15+r13, Phase 33)

| offset | size | R/W | meaning | source |
|--------|------|-----|---------|--------|
| +0x00  | 8    | W   | field from declared entry ([rcx+0x28] where rcx=[rbp+0x3460]) | [rcx+0x28] |
| +0x08  | 8    | W   | field from declared entry ([rcx+0x30]) | [rcx+0x30] |
| +0x10  | 16   | W   | xmm register ([rbp+0x3310]) | [rbp+0x3310] |
| +0x1C  | 16   | W   | xmm register ([rbp+0x331C]) (overlaps +0x1C..+0x1F with +0x10) | [rbp+0x331C] |
| +0x30  | 16   | W   | xmm register ([rbp+0x3330] — 40-byte vec begin) | [rbp+0x3330] |
| +0x40  | 8    | W   | qword ([rbp+0x3340] — 40-byte vec cap) | [rbp+0x3340] |
| +0x48  | 16   | W   | xmm register ([rbp+0x3348] — 24-byte vec begin) | [rbp+0x3348] |
| +0x58  | 8    | W   | qword ([rbp+0x3358] — 24-byte vec end) | [rbp+0x3358] |
| +0x60  | 16   | W   | xmm register ([rbp+0x3360] — 0x20-stride vec begin) | [rbp+0x3360] |
| +0x70  | 8    | W   | qword ([rbp+0x3370] — 0x20-stride vec cap) | [rbp+0x3370] |
| +0x78  | 8    | W   | 0 (null terminator) | immediate 0 |

### Per-pass record construction flow (Phase 26)
1. movups xmm0,[rbp+0x1FC0] — load accumulator
2. mov rax,[rbp+0x1FB0] / shl rax,4 — pass index × 16
3. movups [rbp+rax-0x50],xmm0 — store to pass slot
4. inc qword ptr [rbp+0x1FB0] — increment pass counter
5. movaps [rbp+0x3310],xmm0 — save accumulator
6. Zero record with movdqu [r14],xmm7
7. Fill fields +0x00 through +0x78 as above
8. Zero source vectors after copying (movdqa/movdqu [rbp+0x3330],xmm7 etc.)
9. r14 += 0x80 (sub r14,0xFFFFFFFFFFFFFF80), advance to next record

### Empty-path record construction (Phase 33, at r15+r13)
Same field layout as Phase 26, then move-move loop copies 0x80-byte records from r12 to r15 (0x80 stride, zeroing source), exits at 0xc2793ea.

## TOOL REQUESTS

1. **verify_oc.py**: Run python tools/sigs/verify_oc.py docs/progress/oc_U-C7b.md to validate all 34 phases against the listing. One instruction per quoted line required.

2. **sub_c27ec60 analysis**: Determine what this loop-bracket function does (called at 0xc277e8c and 0xc2793fe). Candidate: loop setup/teardown for per-pass iteration.

3. **Switch value semantics**: 
   - First record loop: [rdi+0x30] values 1, 2, 3 — which dependency kind each maps to?
   - Second record loop: [rdi+0x18] values 1, 2 — which dependency kind each maps to?

4. **Hash table lookup**: Confirm semantics of table at [rbp+0x3468] — bucket traversal via [rdx+0x19] sentinel, [rdx+0x20] compare, [rcx+0x20] compare. How does [r13+0x238] factor into bucket index?

5. **0x80-byte record struct**: Confirm the purpose and field meanings of the 0x80-byte per-pass record (likely a dependency frame or pass summary struct).

6. **declared entry d fields**: Confirm [d+0x18] and [d+0x28] meanings — currently unknown beyond being used in switch decisions and hash lookups.
