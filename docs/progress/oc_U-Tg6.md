## NEXT
DONE

# Unit U-Tg6 — texgroup_load 0x5421c90, slice 0x5423232..0x542359f (chunk 6 of 6)

Source: docs/progress/_part_Tg6.txt (orchestrator-computed listing). All instruction text below is copied verbatim from that listing.

## Phase 1 — 0x5423232..0x542325a

Entry block: rcx=rbx, then an unconditional jump to 0x54232CD; on the fall-through path r11=[r8+0x10] is loaded, flag byte [r11+0x18] is tested (jump to 0x54231E0 if zero), then rdx=[rcx+0x10] is loaded and rbx is compared with rdx, jumping to 0x542328D on equality or to 0x542333C otherwise.

0x5423232  mov rcx,rbx
0x5423235  jmp 0x54232CD
0x542323a  nop [rax+rax]
0x5423240  mov r11,[r8+0x10]
0x5423244  cmp byte ptr [r11+0x18],0
0x5423249  je short 0x54231E0
0x542324b  mov rdx,[rcx+0x10]
0x542324f  cmp rbx,rdx
0x5423252  je short 0x542328D
0x5423254  mov rdx,rcx
0x5423257  mov rcx,rbx
0x542325a  jmp 0x542333C

## Phase 2 — 0x542325f..0x542328b

Unlink helper: r9=[rdx+0x10], store [rcx]=r9, and if flag byte [r9+0x19]==0 store back-pointer [r9+8]=rcx; then r8=[rcx+8], store [rdx+8]=r8, load r9=[rsi], and branch on rcx vs [r9+8] (to 0x54232BB) or rcx vs [r8+0x10] (to 0x54232C1), otherwise store [r8]=rdx and jump to 0x54232C5.

0x542325f  mov r9,[rdx+0x10]
0x5423263  mov [rcx],r9
0x5423266  cmp byte ptr [r9+0x19],0
0x542326b  jne short 0x5423275
0x542326d  mov [r9+8],rcx
0x5423271  mov r8,[rcx+8]
0x5423275  mov [rdx+8],r8
0x5423279  mov r9,[rsi]
0x542327c  cmp rcx,[r9+8]
0x5423280  je short 0x54232BB
0x5423282  cmp rcx,[r8+0x10]
0x5423286  je short 0x54232C1
0x5423288  mov [r8],rdx
0x542328b  jmp short 0x54232C5

## Phase 3 — 0x542328d..0x54232bf

rcx is spliced between rdx and r8: r9=[rdx], store [rcx+0x10]=r9, and if flag byte [r9+0x19]==0 store [r9+8]=rcx; then r8=[rcx+8], store [rdx+8]=r8, load r9=[rsi]; if rcx==[r9+8] jump to 0x542332C, if rcx==[r8] jump to 0x5423332, otherwise store [r8+0x10]=rdx and jump to 0x5423335; at 0x54232BB store [r9+8]=rdx then jump to 0x54232C5.

0x542328d  mov r9,[rdx]
0x5423290  mov [rcx+0x10],r9
0x5423294  cmp byte ptr [r9+0x19],0
0x5423299  jne short 0x54232A3
0x542329b  mov [r9+8],rcx
0x542329f  mov r8,[rcx+8]
0x54232a3  mov [rdx+8],r8
0x54232a7  mov r9,[rsi]
0x54232aa  cmp rcx,[r9+8]
0x54232ae  je short 0x542332C
0x54232b0  cmp rcx,[r8]
0x54232b3  je short 0x5423332
0x54232b5  mov [r8+0x10],rdx
0x54232b9  jmp short 0x5423335
0x54232bb  mov [r9+8],rdx
0x54232bf  jmp short 0x54232C5

## Phase 4 — 0x54232c1..0x5423327

At 0x54232C1 store [r8+0x10]=rdx; at 0x54232C5 store [rdx+0x10]=rcx and [rcx+8]=rdx, set flag byte [rdx+0x18]=1; then walk rdx=[rcx+8], rdx=[rdx+8], clear flag byte [rdx+0x18]=0, repeat rdx=[rcx+8], rdx=[rdx+8], load r8=[rdx+0x10], r9=[r8], store [rdx+0x10]=r9; if flag byte [r9+0x19]==0 store [r9+8]=rdx; then r9=[rdx+8], store [r8+8]=r9, load r10=[rsi]; if rdx==[r10+8] store [r10+8]=r8, else if rdx==[r9] store [r9]=r8, else store [r9+0x10]=r8; finally store [r8]=rdx, [rdx+8]=r8, jump to 0x54231FB.

0x54232c1  mov [r8+0x10],rdx
0x54232c5  mov [rdx+0x10],rcx
0x54232c9  mov [rcx+8],rdx
0x54232cd  mov byte ptr [rdx+0x18],1
0x54232d1  mov rdx,[rcx+8]
0x54232d5  mov rdx,[rdx+8]
0x54232d9  mov byte ptr [rdx+0x18],0
0x54232dd  mov rdx,[rcx+8]
0x54232e1  mov rdx,[rdx+8]
0x54232e5  mov r8,[rdx+0x10]
0x54232e9  mov r9,[r8]
0x54232ec  mov [rdx+0x10],r9
0x54232f0  cmp byte ptr [r9+0x19],0
0x54232f5  jne short 0x54232FB
0x54232f7  mov [r9+8],rdx
0x54232fb  mov r9,[rdx+8]
0x54232ff  mov [r8+8],r9
0x5423303  mov r10,[rsi]
0x5423306  cmp rdx,[r10+8]
0x542330a  je short 0x5423317
0x542330c  cmp rdx,[r9]
0x542330f  je short 0x542331D
0x5423311  mov [r9+0x10],r8
0x5423315  jmp short 0x5423320
0x5423317  mov [r10+8],r8
0x542331b  jmp short 0x5423320
0x542331d  mov [r9],r8
0x5423320  mov [r8],rdx
0x5423323  mov [rdx+8],r8
0x5423327  jmp 0x54231FB

## Phase 5 — 0x542332c..0x542339b

Alternate splice targets: at 0x542332C store [r9+8]=rdx then jump to 0x5423335; at 0x5423332 store [r8]=rdx then at 0x5423335 store [rdx]=rcx and [rcx+8]=rdx; repeat the flag set/clear walk ([rdx+0x18]=1, rdx=[rcx+8] twice, [rdx+0x18]=0, r8=[rdx], r9=[r8+0x10], [rdx]=r9) and if flag byte [r9+0x19]==0 store [r9+8]=rdx; then r9=[rdx+8], store [r8+8]=r9, load r10=[rsi]; if rdx==[r10+8] store [r10+8]=r8 and [r8+0x10]=rdx, else if rdx==[r9+0x10] store [r9+0x10]=r8 and [r8+0x10]=rdx, else store [r9]=r8 and [r8+0x10]=rdx; all paths jump to 0x5423323.

0x542332c  mov [r9+8],rdx
0x5423330  jmp short 0x5423335
0x5423332  mov [r8],rdx
0x5423335  mov [rdx],rcx
0x5423338  mov [rcx+8],rdx
0x542333c  mov byte ptr [rdx+0x18],1
0x5423340  mov rdx,[rcx+8]
0x5423344  mov rdx,[rdx+8]
0x5423348  mov byte ptr [rdx+0x18],0
0x542334c  mov rdx,[rcx+8]
0x5423350  mov rdx,[rdx+8]
0x5423354  mov r8,[rdx]
0x5423357  mov r9,[r8+0x10]
0x542335b  mov [rdx],r9
0x542335e  cmp byte ptr [r9+0x19],0
0x5423363  jne short 0x5423369
0x5423365  mov [r9+8],rdx
0x5423369  mov r9,[rdx+8]
0x542336d  mov [r8+8],r9
0x5423371  mov r10,[rsi]
0x5423374  cmp rdx,[r10+8]
0x5423378  je short 0x5423389
0x542337a  cmp rdx,[r9+0x10]
0x542337e  je short 0x5423393
0x5423380  mov [r9],r8
0x5423383  mov [r8+0x10],rdx
0x5423387  jmp short 0x5423323
0x5423389  mov [r10+8],r8
0x542338d  mov [r8+0x10],rdx
0x5423391  jmp short 0x5423323
0x5423393  mov [r9+0x10],r8
0x5423397  mov [r8+0x10],rdx
0x542339b  jmp short 0x5423323

## Phase 6 — 0x542339d..0x54233dc

Epilogue check: rcx=rsi, rdx=rbx, r8=r14, then call 0xEEC6EB0; then xor ecx,ecx, cmp r13,rdi, setae cl, xor edx,edx, test eax,eax, setns dl, cmovne ecx,edx, cmp cl,1, jne 0x542300A; if not taken, eax=[rbp+0x1F8], rcx=[rbp+0x230], cmp eax,[rcx+0x58], jb 0x5422E20, else jmp 0x542300A.

0x542339d  mov rcx,rsi
0x54233a0  mov rdx,rbx
0x54233a3  mov r8,r14
0x54233a6  call 0xEEC6EB0
0x54233ab  xor ecx,ecx
0x54233ad  cmp r13,rdi
0x54233b0  setae cl
0x54233b3  xor edx,edx
0x54233b5  test eax,eax
0x54233b7  setns dl
0x54233ba  cmovne ecx,edx
0x54233bd  cmp cl,1
0x54233c0  jne 0x542300A
0x54233c6  mov eax,[rbp+0x1F8]
0x54233cc  mov rcx,[rbp+0x230]
0x54233d3  cmp eax,[rcx+0x58]
0x54233d6  jb 0x5422E20
0x54233dc  jmp 0x542300A

## Phase 7 — 0x54233e1..0x5423445

Error/allocation tail calls: call 0x78ED0; mov ecx,0x20, call 0x9BC830, jmp 0x5421F44; mov ecx,0x80, call 0x9BC830, jmp 0x542226E; mov ecx,0x78, call 0x9BC830, jmp 0x54225EE; mov ecx,0x80, call 0x9BC830, jmp 0x5422A7A; mov ecx,0x70, call 0x9BC830, jmp 0x5422E64; then mov rcx=r14, r14=rax, call 0x9BC830, rax=r14, jmp 0x5421D72.

0x54233e1  call 0x78ED0
0x54233e6  nop
0x54233e7  mov ecx,0x20
0x54233ec  call 0x9BC830
0x54233f1  nop
0x54233f2  jmp 0x5421F44
0x54233f7  mov ecx,0x80
0x54233fc  call 0x9BC830
0x5423401  nop
0x5423402  jmp 0x542226E
0x5423407  mov ecx,0x78
0x542340c  call 0x9BC830
0x5423411  nop
0x5423412  jmp 0x54225EE
0x5423417  mov ecx,0x80
0x542341c  call 0x9BC830
0x5423421  nop
0x5423422  jmp 0x5422A7A
0x5423427  mov ecx,0x70
0x542342c  call 0x9BC830
0x5423431  nop
0x5423432  jmp 0x5422E64
0x5423437  mov rcx,r14
0x542343a  mov r14,rax
0x542343d  call 0x9BC830
0x5423442  mov rax,r14
0x5423445  jmp 0x5421D72

## Phase 8 — 0x542344a..0x54234cd

Tail-call splash (each is lea/mov rcx, call 0x9BC830, then jmp or xor esi,esi then jmp): lea rcx,[rdi+0x28], call 0x9BC830, jmp 0x542215A; lea rcx,[rdi+1], call 0x9BC830, jmp 0x542219B (esi=0); mov rcx=rbx, call 0x9BC830, jmp 0x542236E; mov rcx=rbx, call 0x9BC830, jmp 0x5422399 (esi=0); mov rcx=r14, call 0x9BC830, jmp 0x54224FF; mov rcx=r14, call 0x9BC830, jmp 0x542252A (esi=0); mov rcx=r12, call 0x9BC830, jmp 0x54226F0; mov rcx=r12, call 0x9BC830, jmp 0x542271B (esi=0); mov rcx=r13, call 0x9BC830, jmp 0x5422956; mov rcx=r13, call 0x9BC830, jmp 0x5422981 (esi=0).

0x542344a  lea rcx,[rdi+0x28]
0x542344e  call 0x9BC830
0x5423453  nop
0x5423454  jmp 0x542215A
0x5423459  lea rcx,[rdi+1]
0x542345d  call 0x9BC830
0x5423462  nop
0x5423463  xor esi,esi
0x5423465  jmp 0x542219B
0x542346a  mov rcx,rbx
0x542346d  call 0x9BC830
0x5423472  nop
0x5423473  jmp 0x542236E
0x5423478  mov rcx,rbx
0x542347b  call 0x9BC830
0x5423480  nop
0x5423481  xor esi,esi
0x5423483  jmp 0x5422399
0x5423488  mov rcx,r14
0x542348b  call 0x9BC830
0x5423490  nop
0x5423491  jmp 0x54224FF
0x5423496  mov rcx,r14
0x5423499  call 0x9BC830
0x542349e  nop
0x542349f  xor esi,esi
0x54234a1  jmp 0x542252A
0x54234a6  mov rcx,r12
0x54234a9  call 0x9BC830
0x54234ae  nop
0x54234af  jmp 0x54226F0
0x54234b4  mov rcx,r12
0x54234b7  call 0x9BC830
0x54234bc  nop
0x54234bd  xor esi,esi
0x54234bf  jmp 0x542271B
0x54234c4  mov rcx,r13
0x54234c7  call 0x9BC830
0x54234cc  nop
0x54234cd  jmp 0x5422956

## Phase 9 — 0x54234d2..0x5423551

More tail calls and frame stores: mov rcx=rbx, call 0x9BC830, jmp 0x5422981; mov rcx=rbx, call 0x9BC830, jmp 0x5422B4D; mov rcx=rbx, call 0x9BC830, jmp 0x5422B78 (esi=0); mov rcx=rbx, call 0x9BC830, jmp 0x5422F14; mov rcx=rbx, call 0x9BC830, jmp 0x5422F3F (esi=0); call 0xA4710; call 0x75720; call 0x75720; store [rbp+0x210]=rcx and [rbp+0x220]=rbx; call 0x75720; call 0x75720; store [rbp+0x220]=rsi and [rbp+0x210]=rdi; call 0x75720; call 0x75720.

0x54234d2  mov rcx,r13
0x54234d5  call 0x9BC830
0x54234da  nop
0x54234db  xor esi,esi
0x54234dd  jmp 0x5422981
0x54234e2  mov rcx,rbx
0x54234e5  call 0x9BC830
0x54234ea  nop
0x54234eb  jmp 0x5422B4D
0x54234f0  mov rcx,rbx
0x54234f3  call 0x9BC830
0x54234f8  nop
0x54234f9  xor esi,esi
0x54234fb  jmp 0x5422B78
0x5423500  mov rcx,rbx
0x5423503  call 0x9BC830
0x5423508  nop
0x5423509  jmp 0x5422F14
0x542350e  mov rcx,rbx
0x5423511  call 0x9BC830
0x5423516  nop
0x5423517  xor esi,esi
0x5423519  jmp 0x5422F3F
0x542351e  call 0xA4710
0x5423523  nop
0x5423524  call 0x75720
0x5423529  nop
0x542352a  call 0x75720
0x542352f  nop
0x5423530  mov [rbp+0x210],rcx
0x5423537  mov [rbp+0x220],rbx
0x542353e  call 0x75720
0x5423543  nop
0x5423544  call 0x75720
0x5423549  nop
0x542354a  mov [rbp+0x220],rsi
0x5423551  mov [rbp+0x210],rdi

## Phase 10 — 0x5423558..0x542359f

Tail: call 0x75720; call 0x75720; store [rbp+0x230]=rbx; call 0x75720; call 0xA4EA0; store qword [rsp+0x20]=0; xor ecx,ecx; xor edx,edx; xor r8d,r8d; xor r9d,r9d; call qword ptr [0xF9A8C78]; mov rcx=r14; call 0x9BC830; int3; nop.

0x5423558  call 0x75720
0x542355d  nop
0x542355e  call 0x75720
0x5423563  nop
0x5423564  mov [rbp+0x230],rbx
0x542356b  call 0x75720
0x5423570  nop
0x5423571  call 0xA4EA0
0x5423576  nop
0x5423577  call 0x75720
0x542357c  nop
0x542357d  mov qword ptr [rsp+0x20],0
0x5423586  xor ecx,ecx
0x5423588  xor edx,edx
0x542358a  xor r8d,r8d
0x542358d  xor r9d,r9d
0x5423590  call qword ptr [0xF9A8C78]
0x5423596  mov rcx,r14
0x5423599  call 0x9BC830
0x542359e  int3
0x542359f  nop

## Field map — every [reg+off] field stored or loaded in the slice

Sizes come from the instruction (qword=8, byte ptr=1, dword/mov eax=4). Direction R=load, W=store. Meaning is `-` because no instruction or string in the slice documents what any field represents.

| offset | size | read/store address | verbatim `0xRVA  instr` line(s) | meaning |
|---|---|---|---|---|
| 0x00 | 8 | [rcx] W; [rsi] R (×4); [r8] W (×3) + R; [rdx] R (×2) + W (×2); [r9] R + W (×2) | `0x5423263  mov [rcx],r9`<br>`0x5423279  mov r9,[rsi]`<br>`0x54232a7  mov r9,[rsi]`<br>`0x5423288  mov [r8],rdx`<br>`0x54232e9  mov r9,[r8]`<br>`0x542328d  mov r9,[rdx]`<br>`0x5423335  mov [rdx],rcx`<br>`0x5423303  mov r10,[rsi]`<br>`0x542330c  cmp rdx,[r9]`<br>`0x542331d  mov [r9],r8`<br>`0x5423320  mov [r8],rdx`<br>`0x5423332  mov [r8],rdx`<br>`0x5423354  mov r8,[rdx]`<br>`0x542335b  mov [rdx],r9`<br>`0x5423371  mov r10,[rsi]`<br>`0x5423380  mov [r9],r8` | - |
| 0x08 | 8 | [r9+8] W (×6); [rcx+8] R (×6); [rdx+8] W (×2) + R (×6); [r8+8] W (×2); [r10+8] W (×2) + R (×2) | `0x542326d  mov [r9+8],rcx`<br>`0x5423271  mov r8,[rcx+8]`<br>`0x5423275  mov [rdx+8],r8`<br>`0x542327c  cmp rcx,[r9+8]`<br>`0x542329b  mov [r9+8],rcx`<br>`0x542329f  mov r8,[rcx+8]`<br>`0x54232a3  mov [rdx+8],r8`<br>`0x54232aa  cmp rcx,[r9+8]`<br>`0x54232bb  mov [r9+8],rdx`<br>`0x54232c9  mov [rcx+8],rdx`<br>`0x54232d1  mov rdx,[rcx+8]`<br>`0x54232d5  mov rdx,[rdx+8]`<br>`0x54232dd  mov rdx,[rcx+8]`<br>`0x54232e1  mov rdx,[rdx+8]`<br>`0x54232fb  mov r9,[rdx+8]`<br>`0x54232f7  mov [r9+8],rdx`<br>`0x54232ff  mov [r8+8],r9`<br>`0x5423306  cmp rdx,[r10+8]`<br>`0x5423317  mov [r10+8],r8`<br>`0x5423323  mov [rdx+8],r8`<br>`0x542332c  mov [r9+8],rdx`<br>`0x5423340  mov rdx,[rcx+8]`<br>`0x5423344  mov rdx,[rdx+8]`<br>`0x542334c  mov rdx,[rcx+8]`<br>`0x5423350  mov rdx,[rdx+8]`<br>`0x5423365  mov [r9+8],rdx`<br>`0x5423369  mov r9,[rdx+8]`<br>`0x542336d  mov [r8+8],r9`<br>`0x5423374  cmp rdx,[r10+8]`<br>`0x5423389  mov [r10+8],r8` | - |
| 0x10 | 8 | [r8+0x10] R (×3) + W (×5); [rcx+0x10] R; [rdx+0x10] R (×2) + W (×2); [r9+0x10] W (×2) + R | `0x5423240  mov r11,[r8+0x10]`<br>`0x542324b  mov rdx,[rcx+0x10]`<br>`0x542325f  mov r9,[rdx+0x10]`<br>`0x5423282  cmp rcx,[r8+0x10]`<br>`0x5423290  mov [rcx+0x10],r9`<br>`0x54232b5  mov [r8+0x10],rdx`<br>`0x54232c1  mov [r8+0x10],rdx`<br>`0x54232c5  mov [rdx+0x10],rcx`<br>`0x54232e5  mov r8,[rdx+0x10]`<br>`0x54232ec  mov [rdx+0x10],r9`<br>`0x5423311  mov [r9+0x10],r8`<br>`0x5423357  mov r9,[r8+0x10]`<br>`0x542337a  cmp rdx,[r9+0x10]`<br>`0x5423383  mov [r8+0x10],rdx`<br>`0x542338d  mov [r8+0x10],rdx`<br>`0x5423393  mov [r9+0x10],r8`<br>`0x5423397  mov [r8+0x10],rdx` | - |
| 0x18 | 1 | [r11+0x18] R; [rdx+0x18] W (×4) | `0x5423244  cmp byte ptr [r11+0x18],0`<br>`0x54232cd  mov byte ptr [rdx+0x18],1`<br>`0x54232d9  mov byte ptr [rdx+0x18],0`<br>`0x542333c  mov byte ptr [rdx+0x18],1`<br>`0x5423348  mov byte ptr [rdx+0x18],0` | - |
| 0x19 | 1 | [r9+0x19] R (×4) | `0x5423266  cmp byte ptr [r9+0x19],0`<br>`0x5423294  cmp byte ptr [r9+0x19],0`<br>`0x54232f0  cmp byte ptr [r9+0x19],0`<br>`0x542335e  cmp byte ptr [r9+0x19],0` | - |
| 0x58 | 4 | [rcx+0x58] R | `0x54233d3  cmp eax,[rcx+0x58]` | - |
| 0x1F8 | 4 | [rbp+0x1F8] R | `0x54233c6  mov eax,[rbp+0x1F8]` | - |
| 0x210 | 8 | [rbp+0x210] W (×2) | `0x5423530  mov [rbp+0x210],rcx`<br>`0x5423551  mov [rbp+0x210],rdi` | - |
| 0x220 | 8 | [rbp+0x220] W (×2) | `0x5423537  mov [rbp+0x220],rbx`<br>`0x542354a  mov [rbp+0x220],rsi` | - |
| 0x230 | 8 | [rbp+0x230] R + W | `0x54233cc  mov rcx,[rbp+0x230]`<br>`0x5423564  mov [rbp+0x230],rbx` | - |
| 0x20 | 8 | [rsp+0x20] W (rsp-based) | `0x542357d  mov qword ptr [rsp+0x20],0` | - |

## Coverage

All 248 instructions of the slice 0x5423232..0x542359f are covered by Phases 1–10 (each phase ≤40 instructions); every [reg+off] load/store address in the slice appears in the field map above; no offset is omitted.
