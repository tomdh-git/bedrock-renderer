# Unit U-SK5: sky visitor 0x66560f0 — Stars base draw range 0x6658ffc..0x6659615 (instruction-complete)

Source: docs/functions/66560f0_sky_visitor.md (coverage table) + docs/OPENCODE_BRIEF.md. Exe 1.26.62.01, RVAs image-relative.
Rule: STATIC ANALYSIS ONLY. Every claim tagged [V] (seen in rdis disassembly, cite RVA), [I] (inferred), [?] (unknown).
Conventions:
- rdi = description pointer (frame map, §1.1 of the coverage table). Every description field read is noted as `[reg+off]` with the register holding the description.
- Phases are 40 instructions each, restarted at the next address after any (bad) decode.
- Format per phase: exact `0xRVA  mnemonic operands` lines, then `// interpretation` tagged [V]/[I]/[?].

## NEXT
COMPLETE: phases 1-8 appended, covering 0x6658ffc..0x6659615 inclusive (phase 8 is a short final phase stopping at the 0x6659615 boundary). Unit done.

## Phases
### Phase 1: 0x6658ffc..0x66590d3 (40 instr)
```
6658ffc  mov rax,[rbp+0x50]
6659000  mov [rbp+0x3A0],rax
6659007  lea rdi,[rbp+0x3A8]
665900e  mov rcx,rdi
6659011  mov rdx,r13
6659014  call 0xE869FF0        ; -> sub_e869ff0
6659019  nop
665901a  mov rax,[rbp+0xD0]
6659021  mov [rbp+0x420],rax
6659028  mov qword ptr [rbp+0xD0],0
6659033  mov byte ptr [rbp+0x468],0xFF
665903a  movzx eax,byte ptr [rbp+0x1B0]
6659041  movzx ecx,al
6659044  cmp ecx,1
6659047  jg short 0x665908E     ; -> loc_665908e
6659049  test ecx,ecx
665904b  jne 0x66594B5          ; -> loc_66594b5
6659051  movaps xmm0,[rbp+0x170]
6659058  movaps xmm1,[rbp+0x180]
665905f  movaps xmm2,[rbp+0x190]
6659066  movaps xmm3,[rbp+0x1A0]
665906d  movups [rbp+0x428],xmm0
6659074  movups [rbp+0x438],xmm1
665907b  movups [rbp+0x448],xmm2
6659082  movups [rbp+0x458],xmm3
6659089  jmp 0x66594E6          ; -> loc_66594e6
loc_665908e:
665908e  cmp ecx,2
6659091  jne 0x66594EC          ; -> loc_66594ec
6659097  mov rcx,[rbp+0x170]
665909e  mov [rbp+0x428],rcx
66590a5  jmp 0x66594E6          ; -> loc_66594e6
66590aa  add r8,rax
66590ad  lea r9,[rax+rcx]
66590b1  cmp r8,r9
66590b4  jae short 0x66590F6    ; -> loc_66590f6
66590b6  sub r8d,eax
66590b9  shr r8d,4
66590bd  mov [rbp+0x4E0],r8w
66590c5  mov byte ptr [rbp+0x4E2],1
66590cc  lea rdx,[rbp+0x4E0]
```
// [V] Prologue of Stars base draw: [rbp+0x50] -> [rbp+0x3A0]; call sub_e869FF0(&[rbp+0x3A8], r13) (UB/assign-style helper, same helper as Cubemap draw-state copy at 0x665a21a [I]); [rbp+0xD0] -> [rbp+0x420] then [rbp+0xD0]=0; flag byte [rbp+0x468]=0xFF; switch on selector byte [rbp+0x1B0]: 0 -> copy 4 vec4s (64 B) from [rbp+0x170..0x1A0] to [rbp+0x428..0x458], jmp 0x66594e6; 1 -> store [rbp+0x170] qword to [rbp+0x428], jmp 0x66594e6; >1 -> 0x66594ec. Shared tail block (0x66590aa..0x66590cc): computes (r8+rax) vs (rax+rcx), then (r8d-eax)>>4 stored as word [rbp+0x4E0], byte [rbp+0x4E2]=1, rdx=&[rbp+0x4E0]. All reads are frame locals via rbp; no description-field ([rdi+off]) reads — rdi is scratch &[rbp+0x3A8] here, not the description pointer [V].

### Phase 2: 0x66590d3..0x665917c (40 instr)
```
66590d3  lea r8,[rbp+0x1E0]
66590da  mov rcx,rbx
66590dd  call 0x5679DB0        ; -> sub_5679db0
66590e2  nop
66590e3  mov rax,[rbp+0x88]
66590ea  movzx edx,word ptr [rbp+0x92]
66590f1  mov ecx,edx
66590f3  shl ecx,4
66590f6  movups xmm0,[rdi+8]
66590fa  movaps [rbp+0x340],xmm0
6659101  mov qword ptr [rbp+0x1E0],1
665910c  mov [rbp+0x1E8],r15
6659113  mov r8,rax
6659116  test dx,dx
6659119  je short 0x665913D     ; -> loc_665913d
665911b  mov rdx,[0x129F9F40]   ; [data_129f9f40]
6659122  mov r9,rcx
6659125  mov r8,rax
loc_6659128:
6659128  mov r10,[r8]
665912b  cmp [r10+0x28],rdx
665912f  je short 0x665913D     ; -> loc_665913d
6659131  add r8,0x10
6659135  add r9,0xFFFFFFFFFFFFFFF0
6659139  jne short 0x6659128    ; -> loc_6659128
665913b  jmp short 0x6659172    ; -> loc_6659172
loc_665913d:
665913d  add rcx,rax
6659140  cmp r8,rcx
6659143  jae short 0x6659172    ; -> loc_6659172
6659145  sub r8d,eax
6659148  shr r8d,4
665914c  mov [rbp+0x4E0],r8w
6659154  mov byte ptr [rbp+0x4E2],1
665915b  lea rdx,[rbp+0x4E0]
6659162  lea r8,[rbp+0x1E0]
6659169  mov rcx,rbx
665916c  call 0x5679DB0        ; -> sub_5679db0
6659171  nop
```
// [V] Description register: rdi holds the description pointer; reads description field [rdi+8] (16-byte vec) -> xmm0 -> [rbp+0x340] at 0x66590f6 [V]. Sets [rbp+0x1E0]=1, [rbp+0x1E8]=r15. Walks a 16-byte-stride table (base rax = [rbp+0x88], count = [rbp+0x92]<<4 at 0x66590e3-0x66590f3), comparing [r10+0x28] of each entry to data_129F9F40 at 0x665911b/0x665912b [V]; on match or exhaustion computes index ((r8-rax)>>4) -> word [rbp+0x4E0], byte [rbp+0x4E2]=1, rdx=&[rbp+0x4E0] (0x665913d-0x665915b). Calls sub_5679DB0 twice with (&[rbp+0x1E0], rbx) at 0x66590dd and 0x665916c [V]. All other reads are rbp frame locals [V].

### Phase 3: 0x665917c..0x6659284 (40 instr)
```
665917c  movups xmm6,[rdi+0x28]
6659180  movaps [rbp+0x120],xmm6
6659187  movups xmm7,[rdi+0x38]
665918b  movaps [rbp+0x130],xmm7
6659192  movups xmm8,[rdi+0x48]
6659197  movaps [rbp+0x140],xmm8
665919f  movups xmm9,[rdi+0x58]
66591a4  movaps [rbp+0x150],xmm9
66591ac  mov byte ptr [rbp+0x160],0
66591b3  mov r14w,[rdi+0x68]
66591b8  mov rcx,[rdi]
66591bb  lea rdx,[rbp+0x170]
66591c2  call 0x4DE9FA0        ; -> sub_4de9fa0
66591c7  nop
66591c8  mov rdx,[rsi]
66591cb  lea rcx,[rbp+0x4E0]
66591d2  lea r8,[rbp+0x170]
66591d9  call 0x66A6190        ; -> sub_66a6190 (mesh-object builder per dossier)
66591de  nop
66591df  mov dword ptr [rbp+0x344],0
66591e9  mov byte ptr [rbp+0x348],7
66591f0  mov dword ptr [rbp+0x34C],1
66591fa  mov word ptr [rbp+0x350],1
6659203  mov byte ptr [rbp+0x352],2
665920a  mov dword ptr [rbp+0x354],0
6659214  mov byte ptr [rbp+0x358],0
665921b  xorps xmm10,xmm10
665921f  movups [rbp+0x35C],xmm10
6659227  movups [rbp+0x368],xmm10
665922f  mov byte ptr [rbp+0x378],8
6659236  mov qword ptr [rbp+0x37C],0
6659241  mov dword ptr [rbp+0x384],0
665924b  mov byte ptr [rbp+0x388],8
6659252  mov qword ptr [rbp+0x38C],0
665925d  mov qword ptr [rbp+0x392],0
6659268  mov byte ptr [rbp+0x39A],0xFF
665926f  mov rax,[rbp+0x50]
6659273  mov [rbp+0x3A0],rax
665927a  lea rdi,[rbp+0x3A8]
6659281  mov rcx,rdi
```
// [V] Description register: rdi holds the description pointer; reads description fields [rdi+0x28],[rdi+0x38],[rdi+0x48],[rdi+0x58] (four vecs) -> xmm6..xmm9 -> [rbp+0x120..0x15F] at 0x665917c/0x6659187/0x6659192/0x665919f [V]; [rdi+0x68] (u16) -> r14w at 0x66591b3 [V]; [rdi+0x00] qword -> rcx, then call sub_4DE9FA0(rcx=&[rbp+0x170], rdx=[rdi]) at 0x66591b8-0x66591c2 — likely transform/matrix setup from description +0x00 [I]. Call sub_66A6190(rcx=&[rbp+0x4E0], rdx=[rsi], r8=&[rbp+0x170]) at 0x66591c8-0x66591d9 — mesh-object builder, rsi=frame context [V]. DrawState init: [rbp+0x344]=0 (dword), [rbp+0x348]=7 (byte), [rbp+0x34C]=1, [rbp+0x350]=1 (word), [rbp+0x352]=2 (byte), [rbp+0x354]=0, [rbp+0x358]=0, zero xmm10 -> [rbp+0x35C],[rbp+0x368], byte [rbp+0x378]=8, qword [rbp+0x37C]=0, dword [rbp+0x384]=0, byte [rbp+0x388]=8, qword [rbp+0x38C]=0, qword [rbp+0x392]=0, byte [rbp+0x39A]=0xFF. Ends copying [rbp+0x50]->[rbp+0x3A0], lea rdi=&[rbp+0x3A8] (rdi overwritten, no longer description), rcx=rdi. rsi read at [rsi] (frame context) [V].

### Phase 4: 0x6659284..0x6659370 (40 instr)
```
6659284  mov rdx,rbx
6659287  call 0xE869FF0        ; -> sub_e869ff0 (UB copy rcx=&[rbp+0x3A8], rdx=rbx)
665928c  nop
665928d  mov rax,[rbp+0xD0]
6659294  mov [rbp+0x420],rax
665929b  mov qword ptr [rbp+0xD0],0
66592a6  movups [rbp+0x428],xmm6
66592ad  movups [rbp+0x438],xmm7
66592b4  movups [rbp+0x448],xmm8
66592bc  movups [rbp+0x458],xmm9
66592c4  mov byte ptr [rbp+0x468],0
66592cb  mov [rbp+0x470],r14w
66592d3  movaps xmm0,[rbp+0x4E0]
66592da  movaps xmm1,[rbp+0x4F0]
66592e1  mov qword ptr [rbp+0x4E8],0
66592ec  movups [rbp+0x478],xmm0
66592f3  movaps [rbp+0x4F0],xmm10
66592fb  movups [rbp+0x488],xmm1
6659302  mov rax,[rbp+0x500]
6659309  mov [rbp+0x498],rax
6659310  mov byte ptr [rbp+0x4B0],0xFF
6659317  movzx eax,byte ptr [rbp+0x518]
665931e  cmp rax,3
6659322  ja 0x665A8EB          ; -> loc_665a8eb
6659328  lea rcx,[rbp+0x4A0]
665932f  lea rdx,[0xF2BF3F8]  ; [data_f2bf3f8] selector table
6659336  movsxd r8,[rdx+rax*4]
665933a  add r8,rdx
665933d  jmp r8
6659340  mov rcx,[rbp+0x508]
6659347  mov [rbp+0x4A0],rcx
665934e  jmp 0x665A8E5         ; -> loc_665a8e5
6659353  mov rax,[rax]
6659356  mov rax,[rax+0x18]
665935a  mov r15,[rax]
665935d  test r15,r15
6659360  je 0x665CF64          ; -> sub_665cf64
6659366  mov r15,[rsi]
6659369  mov rax,[rbp+0x20]
665936d  xorps xmm0,xmm0
```
// [V] Call sub_e869FF0(&[rbp+0x3A8], rbx) UB/assign copy [V]; [rbp+0xD0]->[rbp+0x420], [rbp+0xD0]=0; stores the description vecs xmm6..9 (loaded in phase 3 from [rdi+0x28..0x58]) to [rbp+0x428..0x458] at 0x66592a6..0x66592bc [V]; [rbp+0x468]=0; [rbp+0x470]=r14w (desc+0x68 u16 from phase 3) [V]; rebuilds payload block [rbp+0x4E0/0x4F0/0x4E8/0x478/0x498]; [rbp+0x4B0]=0xFF; reads selector byte [rbp+0x518], cmp rax,3, ja 0x665A8EB; jump table data_f2bf3F8 indexed by rax -> jmp r8 (cases: 0->0x665a8e5, others land at 0x6659340/0x6659353/0x6659576/0x6659585) [V]. Case at 0x6659353 loads owner chain [rax]->[rax+0x18]->r15, null->0x665cf64; else r15=[rsi], rax=[rbp+0x20], zero xmm0 [V]. No description reads here (rdi overwritten to &[rbp+0x3A8] at 0x665927a); all reads via rbp/rsi [V].

### Phase 5: 0x6659370..0x6659483 (40 instr)
```
6659370  movaps [rbp+0x340],xmm0
6659377  mov rcx,[rax+8]
665937b  test rcx,rcx
665937e  je 0x66596A1          ; -> loc_66596a1
6659384  lock inc dword ptr [rcx+8]
6659388  mov r14,[rbp+0x348]
665938f  movups xmm0,[rax]
6659392  movaps [rbp+0x340],xmm0
6659399  test r14,r14
665939c  je 0x66596B6          ; -> loc_66596b6
66593a2  lock dec dword ptr [r14+8]
66593a7  jne 0x66596B6
66593ad  mov rax,[r14]
66593b0  mov rax,[rax]
66593b3  mov rcx,r14
66593b6  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
66593bc  lock dec dword ptr [r14+0xC]
66593c1  jne 0x66596B6
66593c7  mov rax,[r14]
66593ca  mov rax,[rax+8]
66593ce  mov rcx,r14
66593d1  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
66593d7  jmp 0x66596B6
66593dc  mov rcx,[rbp+0x4F0]
66593e3  mov qword ptr [rbp+0x4F0],0
66593ee  movaps xmm0,[rbp+0x4E0]
66593f5  xorps xmm1,xmm1
66593f8  movaps [rbp+0x4E0],xmm1
66593ff  movups [rbp+0x430],xmm0
6659406  mov [rbp+0x440],rcx
665940d  mov [rbp+0x470],al
6659413  lea rax,[rbp+0x344]
665941a  lea r10,[rbp+0x39C]
6659421  lea r11,[rbp+0x3A8]
6659428  lea r9,[rbp+0x430]
665942f  lea r8,[rbp+0x478]
6659436  mov [rbp+0x478],r15w
665943e  lea rdx,[rbp+0x480]
6659445  movaps xmm0,[rbp+0x50]
6659449  movaps xmm1,[rbp+0x60]
665944d  mov qword ptr [rbp+0x58],0
6659455  movups [rbp+0x480],xmm0
665945c  xorps xmm0,xmm0
665945f  movaps [rbp+0x60],xmm0
6659463  movups [rbp+0x490],xmm1
665946a  mov rcx,[rbp+0x70]
665946e  mov [rbp+0x4A0],rcx
6659475  mov byte ptr [rbp+0x4B8],0xFF
665947c  cmp rcx,3
```
// [V] Continues case-3 (owner-chain) from phase 4: shared-ptr retain/release of ctrl blocks — lock inc [rcx+8] (0x6659384), lock dec [r14+8] then release old r14 via calls to sub_eea6040 through [0xF99FFA0] at 0x66593b6/0x66593d1 [V]; [rbp+0x4E0]->[rbp+0x430], [rbp+0x4E0]=0, [rbp+0x440]=rcx, [rbp+0x470]=al; prepares payload pointers r10=&[rbp+0x39C], r11=&[rbp+0x3A8], r9=&[rbp+0x430], r8=&[rbp+0x478], [rbp+0x478]=r15w; [rbp+0x480]=[rbp+0x50], [rbp+0x490]=[rbp+0x60], zeroes [rbp+0x58] and [rbp+0x60]; [rbp+0x4A0]=[rbp+0x70]; [rbp+0x4B8]=0xFF; cmp rcx,3 (next selector switch). No description-field reads; rcx/rax/r14 are shared-ptr ctrl temporaries, rsi frame context [V]. Description register: none active (rdi overwritten earlier).

### Phase 6: 0x6659483..0x6659545 (40 instr)
```
6659483  ja 0x665A7BD          ; -> loc_665a7bd
665948d  lea rdi,[rbp+0x4A8]
6659494  lea rbx,[0xF2BF3E8]   ; [data_f2bf3e8] selector table
665949b  movsxd r14,[rbx+rcx*4]
665949f  add r14,rbx
66594a2  jmp r14
66594a5  mov rdi,[rbp+0x78]
66594a9  mov [rbp+0x4A8],rdi
66594b0  jmp 0x665A7B7         ; -> loc_665a7b7
66594b5  mov rcx,[rbp+0x180]
66594bc  mov qword ptr [rbp+0x180],0
66594c7  movaps xmm0,[rbp+0x170]
66594ce  xorps xmm1,xmm1
66594d1  movaps [rbp+0x170],xmm1
66594d8  movups [rbp+0x428],xmm0
66594df  mov [rbp+0x438],rcx
66594e6  mov [rbp+0x468],al
66594ec  mov [rbp+0x470],r15w
66594f4  movaps xmm0,[rbp+0x4E0]
66594fb  movaps xmm1,[rbp+0x4F0]
6659502  mov qword ptr [rbp+0x4E8],0
665950d  movups [rbp+0x478],xmm0
6659514  xorps xmm0,xmm0
6659517  movaps [rbp+0x4F0],xmm0
665951e  movups [rbp+0x488],xmm1
6659525  mov rax,[rbp+0x500]
665952c  mov [rbp+0x498],rax
6659533  mov byte ptr [rbp+0x4B0],0xFF
665953a  movzx eax,byte ptr [rbp+0x518]
6659541  cmp rax,3
```
// [V] Selector switch on rcx ([rbp+0x88] loaded in phase 4 case 3): ja 0x665A7BD if >3; jump table data_f2bf3E8 -> jmp r14 (cases: 0->0x665a7b7 via 0x66594a5 where [rbp+0x4A8]=[rbp+0x78], others 0x6659576/0x6659585). Case 0x66594b5 (selector==1 path from phase 1): [rbp+0x180]->rcx then zero [rbp+0x180]; xmm0=[rbp+0x170], zero [rbp+0x170], [rbp+0x428]=xmm0, [rbp+0x438]=rcx. Common tail 0x66594e6: [rbp+0x468]=al; 0x66594ec: [rbp+0x470]=r15w; then payload rebuild xmm0=[rbp+0x4E0], xmm1=[rbp+0x4F0], [rbp+0x4E8]=0, [rbp+0x478]=xmm0, zero xmm0->[rbp+0x4F0], [rbp+0x488]=xmm1, [rbp+0x498]=[rbp+0x500], [rbp+0x4B0]=0xFF; reads selector byte [rbp+0x518], cmp rax,3. All reads via rbp frame locals [V]; no description reads.

### Phase 7: 0x6659545..0x6659603 (40 instr)
```
6659545  ja 0x665AF11          ; -> loc_665af11
665954b  lea rcx,[rbp+0x4A0]
6659552  lea rdx,[0xF2BF438]   ; [data_f2bf438] selector table
6659559  movsxd r8,[rdx+rax*4]
665955d  add r8,rdx
6659560  jmp r8
6659563  mov rcx,[rbp+0x508]
665956a  mov [rbp+0x4A0],rcx
6659571  jmp 0x665AF0B         ; -> loc_665af0b
6659576  lea rbx,[rbp+0x78]
665957a  movups xmm0,[rbx]
665957d  movups [rdi],xmm0
6659580  jmp 0x665A7B7         ; -> loc_665a7b7
6659585  movups [rdi],xmm0
6659588  mov rdi,[rbp+0x80]
665958f  test rdi,rdi
6659592  je 0x665A7A3          ; -> loc_665a7a3
6659598  lock inc dword ptr [rdi+8]
665959c  mov rdi,[rbp+0x80]
66595a3  jmp 0x665A7A5         ; -> loc_665a7a5
66595a8  lea rdx,[rbp+0x508]
66595af  movups xmm0,[rdx]
66595b2  movups [rcx],xmm0
66595b5  jmp 0x665A8E5         ; -> loc_665a8e5
66595ba  xorps xmm0,xmm0
66595bd  movups [rcx],xmm0
66595c0  mov rcx,[rbp+0x510]
66595c7  test rcx,rcx
66595ca  je 0x665A8CE          ; -> loc_665a8ce
66595d0  lock inc dword ptr [rcx+8]
66595d4  mov rcx,[rbp+0x510]
66595db  jmp 0x665A8D0         ; -> loc_665a8d0
66595e0  lea rdx,[rbp+0x508]
66595e7  movups xmm0,[rdx]
66595ea  movups [rcx],xmm0
66595ed  jmp 0x665AF0B         ; -> loc_665af0b
66595f2  movups [rcx],xmm0
66595f5  mov rcx,[rbp+0x510]
66595fc  test rcx,rcx
66595ff  je 0x665AEF4          ; -> loc_665aef4
```
// [V] Selector switch on rax ([rbp+0x518]): ja 0x665AF11 if >3; jump table data_f2bf438 -> jmp r8. Cases: 0x6659563 sets [rbp+0x4A0]=[rbp+0x508], jmp 0x665af0b; 0x6659576 stores xmm0 to [rdi] (rdi=scratch dest buffer), jmp 0x665a7b7; 0x6659585 stores xmm0 to [rdi], then shared-ptr retain of [rbp+0x80]: lock inc [rdi+8] at 0x6659598 [V]; 0x66595a8 stores [rbp+0x508] to [rcx], jmp 0x665a8e5; 0x66595ba zeroes [rcx]; 0x66595c0 retains [rbp+0x510] via lock inc [rcx+8]; 0x66595e0 stores [rbp+0x508] to [rcx], jmp 0x665af0b; 0x66595f2 stores xmm0 to [rcx], loads [rbp+0x510] into rcx. rdi used as scratch destination and shared-ptr temp, NOT the description pointer here [V]. All reads via rbp/rsi [V]; no description-field reads.

### Phase 8: 0x6659603..0x6659618 (5 instr, final — stops at 0x6659615 inclusive)
```
6659603  add [rax],al
6659605  lock inc dword ptr [rcx+8]     ; W a0+0x8
6659609  mov rcx,[rbp+0x510]
6659610  jmp 0x665AEF6                  ; -> loc_665aef6
6659615  mov rax,[r14]                  ; unit boundary (inclusive)
```
// [V] Final case tail: add [rax],al (pointer bump), lock inc [rcx+8] retain, rcx=[rbp+0x510], jmp 0x665aef6; then 0x6659615 mov rax,[r14] begins the next case's owner-chain load — unit ends here inclusive. All reads via rbp/rax/rcx/r14 [V]; no description-field reads.
