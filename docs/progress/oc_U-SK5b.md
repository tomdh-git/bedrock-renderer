# Unit U-SK5b — sky visitor 0x66560f0, Stars base draw range 0x6658ffc..0x6659615

Source: docs/OPENCODE_BRIEF.md. Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base. Static analysis only; exe is closed.

## NEXT (top)
Resume at RVA 0x6658ffc. Run `rdis.exe "<exe>" dis <rva> 40`; append each phase as a fenced block of `0xRVA  mnemonic operands` lines followed by a `//` line noting every `[reg+off]` field read and which register holds the description; advance to the address after the last instruction printed (restart after any `(bad)` at the next address); stop once the current address passes 0x6659615.

## Phase 1 — 0x6658ffc (40 instructions)

```
0x6658ffc  mov rax,[rbp+0x50]
0x6659000  mov [rbp+0x3A0],rax
0x6659007  lea rdi,[rbp+0x3A8]
0x665900e  mov rcx,rdi
0x6659011  mov rdx,r13
0x6659014  call 0xE869FF0
0x6659019  nop
0x665901a  mov rax,[rbp+0xD0]
0x6659021  mov [rbp+0x420],rax
0x6659028  mov qword ptr [rbp+0xD0],0
0x6659033  mov byte ptr [rbp+0x468],0xFF
0x665903a  movzx eax,byte ptr [rbp+0x1B0]
0x6659041  movzx ecx,al
0x6659044  cmp ecx,1
0x6659047  jg short 0x665908E
0x6659049  test ecx,ecx
0x665904b  jne 0x66594B5
0x6659051  movaps xmm0,[rbp+0x170]
0x6659058  movaps xmm1,[rbp+0x180]
0x665905f  movaps xmm2,[rbp+0x190]
0x6659066  movaps xmm3,[rbp+0x1A0]
0x665906d  movups [rbp+0x428],xmm0
0x6659074  movups [rbp+0x438],xmm1
0x665907b  movups [rbp+0x448],xmm2
0x6659082  movups [rbp+0x458],xmm3
0x6659089  jmp 0x66594E6
0x665908e  cmp ecx,2
0x6659091  jne 0x66594EC
0x6659097  mov rcx,[rbp+0x170]
0x665909e  mov [rbp+0x428],rcx
0x66590a5  jmp 0x66594E6
0x66590aa  add r8,rax
0x66590ad  lea r9,[rax+rcx]
0x66590b1  cmp r8,r9
0x66590b4  jae short 0x66590F6
0x66590b6  sub r8d,eax
0x66590b9  shr r8d,4
0x66590bd  mov [rbp+0x4E0],r8w
0x66590c5  mov byte ptr [rbp+0x4E2],1
0x66590cc  lea rdx,[rbp+0x4E0]
```
// [reg+off] field reads/writes — rbp holds the description/object base (all memory operands are [rbp+off]). Reads: [rbp+0x50]->rax; [rbp+0xD0]; [rbp+0x1B0]->al/ecx; [rbp+0x170],[rbp+0x180],[rbp+0x190],[rbp+0x1A0] into xmm0-xmm3; [rbp+0x170]->rcx. Writes: [rbp+0x3A0]=rax; [rbp+0x420]=rax; [rbp+0xD0]=0; [rbp+0x468]=0xFF; [rbp+0x428..0x458]=xmm0-xmm3; [rbp+0x428]=rcx; [rbp+0x4E0]=r8w; [rbp+0x4E2]=1. lea address computations: [rbp+0x3A8]->rdi; [rbp+0x4E0]->rdx. No (bad) instructions; last insn at 0x66590cc (7 bytes) -> resume at 0x66590d3.

## Phase 2 — 0x66590d3 (40 instructions)

```
0x66590d3  lea r8,[rbp+0x1E0]
0x66590da  mov rcx,rbx
0x66590dd  call 0x5679DB0
0x66590e2  nop
0x66590e3  mov rax,[rbp+0x88]
0x66590ea  movzx edx,word ptr [rbp+0x92]
0x66590f1  mov ecx,edx
0x66590f3  shl ecx,4
0x66590f6  movups xmm0,[rdi+8]
0x66590fa  movaps [rbp+0x340],xmm0
0x6659101  mov qword ptr [rbp+0x1E0],1
0x665910c  mov [rbp+0x1E8],r15
0x6659113  mov r8,rax
0x6659116  test dx,dx
0x6659119  je short 0x665913D
0x665911b  mov rdx,[0x129F9F40]
0x6659122  mov r9,rcx
0x6659125  mov r8,rax
0x6659128  mov r10,[r8]
0x665912b  cmp [r10+0x28],rdx
0x665912f  je short 0x665913D
0x6659131  add r8,0x10
0x6659135  add r9,0xFFFFFFFFFFFFFFF0
0x6659139  jne short 0x6659128
0x665913b  jmp short 0x6659172
0x665913d  add rcx,rax
0x6659140  cmp r8,rcx
0x6659143  jae short 0x6659172
0x6659145  sub r8d,eax
0x6659148  shr r8d,4
0x665914c  mov [rbp+0x4E0],r8w
0x6659154  mov byte ptr [rbp+0x4E2],1
0x665915b  lea rdx,[rbp+0x4E0]
0x6659162  lea r8,[rbp+0x1E0]
0x6659169  mov rcx,rbx
0x665916c  call 0x5679DB0
0x6659171  nop
0x6659172  lea rcx,[rbp+0x50]
0x6659176  call 0x66A08B0
0x665917b  nop
```
// [reg+off] field reads/writes — rbp holds the description/object base (all [rbp+off] operands). rdi (set to rbp+0x3A8 in phase 1) is also used as a base. Reads: [rbp+0x1E0] (lea addr); [rbp+0x88]->rax; [rbp+0x92]->edx (word); [rdi+8]->xmm0; [0x129F9F40]->rdx (absolute data); [r8]->r10; [r10+0x28] (cmp vs rdx). Writes: [rbp+0x1E0]=1(qword); [rbp+0x1E8]=r15; [rbp+0x340]=xmm0; [rbp+0x4E0]=r8w; [rbp+0x4E2]=1. lea address computations: [rbp+0x1E0]->r8; [rbp+0x4E0]->rdx; [rbp+0x50]->rcx. No (bad) instructions; last insn at 0x665917b (nop, 1 byte) -> resume at 0x665917c.

## Phase 3 — 0x665917c (40 instructions)

```
0x665917c  movups xmm6,[rdi+0x28]
0x6659180  movaps [rbp+0x120],xmm6
0x6659187  movups xmm7,[rdi+0x38]
0x665918b  movaps [rbp+0x130],xmm7
0x6659192  movups xmm8,[rdi+0x48]
0x6659197  movaps [rbp+0x140],xmm8
0x665919f  movups xmm9,[rdi+0x58]
0x66591a4  movaps [rbp+0x150],xmm9
0x66591ac  mov byte ptr [rbp+0x160],0
0x66591b3  mov r14w,[rdi+0x68]
0x66591b8  mov rcx,[rdi]
0x66591bb  lea rdx,[rbp+0x170]
0x66591c2  call 0x4DE9FA0
0x66591c7  nop
0x66591c8  mov rdx,[rsi]
0x66591cb  lea rcx,[rbp+0x4E0]
0x66591d2  lea r8,[rbp+0x170]
0x66591d9  call 0x66A6190
0x66591de  nop
0x66591df  mov dword ptr [rbp+0x344],0
0x66591e9  mov byte ptr [rbp+0x348],7
0x66591f0  mov dword ptr [rbp+0x34C],1
0x66591fa  mov word ptr [rbp+0x350],1
0x6659203  mov byte ptr [rbp+0x352],2
0x665920a  mov dword ptr [rbp+0x354],0
0x6659214  mov byte ptr [rbp+0x358],0
0x665921b  xorps xmm10,xmm10
0x665921f  movups [rbp+0x35C],xmm10
0x6659227  movups [rbp+0x368],xmm10
0x665922f  mov byte ptr [rbp+0x378],8
0x6659236  mov qword ptr [rbp+0x37C],0
0x6659241  mov dword ptr [rbp+0x384],0
0x665924b  mov byte ptr [rbp+0x388],8
0x6659252  mov qword ptr [rbp+0x38C],0
0x665925d  mov qword ptr [rbp+0x392],0
0x6659268  mov byte ptr [rbp+0x39A],0xFF
0x665926f  mov rax,[rbp+0x50]
0x6659273  mov [rbp+0x3A0],rax
0x665927a  lea rdi,[rbp+0x3A8]
0x6659281  mov rcx,rdi
```
// [reg+off] field reads/writes — rbp holds the description/object base (all [rbp+off] operands). rdi (=rbp+0x3A8 from phase 1) and rsi are also used as bases. Reads: [rdi+0x28],[rdi+0x38],[rdi+0x48],[rdi+0x58] into xmm6-xmm9; [rdi+0x68]->r14w; [rdi]->rcx; [rbp+0x170] (lea->rdx); [rsi]->rdx; [rbp+0x170] (lea->r8); [rbp+0x50]->rax. Writes: [rbp+0x120]=xmm6; [rbp+0x130]=xmm7; [rbp+0x140]=xmm8; [rbp+0x150]=xmm9; [rbp+0x160]=0; [rbp+0x344]=0; [rbp+0x348]=7; [rbp+0x34C]=1; [rbp+0x350]=1; [rbp+0x352]=2; [rbp+0x354]=0; [rbp+0x358]=0; [rbp+0x35C]=xmm10; [rbp+0x368]=xmm10; [rbp+0x378]=8; [rbp+0x37C]=0; [rbp+0x384]=0; [rbp+0x388]=8; [rbp+0x38C]=0; [rbp+0x392]=0; [rbp+0x39A]=0xFF; [rbp+0x3A0]=rax. lea address computations: [rbp+0x170]->rdx; [rbp+0x4E0]->rcx; [rbp+0x170]->r8; [rbp+0x3A8]->rdi. No (bad) instructions; last insn at 0x6659281 (mov rcx,rdi, 3 bytes) -> resume at 0x6659284.

## Phase 4 — 0x6659284 (40 instructions)

```
0x6659284  mov rdx,rbx
0x6659287  call 0xE869FF0
0x665928c  nop
0x665928d  mov rax,[rbp+0xD0]
0x6659294  mov [rbp+0x420],rax
0x665929b  mov qword ptr [rbp+0xD0],0
0x66592a6  movups [rbp+0x428],xmm6
0x66592ad  movups [rbp+0x438],xmm7
0x66592b4  movups [rbp+0x448],xmm8
0x66592bc  movups [rbp+0x458],xmm9
0x66592c4  mov byte ptr [rbp+0x468],0
0x66592cb  mov [rbp+0x470],r14w
0x66592d3  movaps xmm0,[rbp+0x4E0]
0x66592da  movaps xmm1,[rbp+0x4F0]
0x66592e1  mov qword ptr [rbp+0x4E8],0
0x66592ec  movups [rbp+0x478],xmm0
0x66592f3  movaps [rbp+0x4F0],xmm10
0x66592fb  movups [rbp+0x488],xmm1
0x6659302  mov rax,[rbp+0x500]
0x6659309  mov [rbp+0x498],rax
0x6659310  mov byte ptr [rbp+0x4B0],0xFF
0x6659317  movzx eax,byte ptr [rbp+0x518]
0x665931e  cmp rax,3
0x6659322  ja 0x665A8EB
0x6659328  lea rcx,[rbp+0x4A0]
0x665932f  lea rdx,[0xF2BF3F8]
0x6659336  movsxd r8,[rdx+rax*4]
0x665933a  add r8,rdx
0x665933d  jmp r8
0x6659340  mov rcx,[rbp+0x508]
0x6659347  mov [rbp+0x4A0],rcx
0x665934e  jmp 0x665A8E5
0x6659353  mov rax,[rax]
0x6659356  mov rax,[rax+0x18]
0x665935a  mov r15,[rax]
0x665935d  test r15,r15
0x6659360  je 0x665CF64
0x6659366  mov r15,[rsi]
0x6659369  mov rax,[rbp+0x20]
0x665936d  xorps xmm0,xmm0
```
// [reg+off] field reads/writes — rbp holds the description/object base (all [rbp+off] operands). rsi is also used as a base ([rsi], [r15=[rsi]]); rbx copied to rdx. Reads: [rbp+0xD0]->rax; [rbp+0x4E0]->xmm0; [rbp+0x4F0]->xmm1; [rbp+0x500]->rax; [rbp+0x518]->eax (byte); [rbp+0x4A0] (lea->rcx); [0xF2BF3F8] (lea->rdx) + [rdx+rax*4]->r8 (jump-table entry); [rbp+0x508]->rcx; [rax]->rax; [rax+0x18]->rax; [rbp+0x20]->rax; [rsi]->r15. Writes: [rbp+0x420]=rax; [rbp+0xD0]=0; [rbp+0x428..0x458]=xmm6-xmm9; [rbp+0x468]=0; [rbp+0x470]=r14w; [rbp+0x478]=xmm0; [rbp+0x498]=rax; [rbp+0x4B0]=0xFF; [rbp+0x4A0]=rcx; [rbp+0x4E8]=0; [rbp+0x4F0]=xmm10; [rbp+0x488]=xmm1. lea address computations: [rbp+0x4A0]->rcx; [0xF2BF3F8]->rdx. No (bad) instructions; last insn at 0x665936d (xorps, 3 bytes) -> resume at 0x6659370.

## Phase 5 — 0x6659370 (40 instructions)

```
0x6659370  movaps [rbp+0x340],xmm0
0x6659377  mov rcx,[rax+8]
0x665937b  test rcx,rcx
0x665937e  je 0x66596A1
0x6659384  lock inc dword ptr [rcx+8]
0x6659388  mov r14,[rbp+0x348]
0x665938f  movups xmm0,[rax]
0x6659392  movaps [rbp+0x340],xmm0
0x6659399  test r14,r14
0x665939c  je 0x66596B6
0x66593a2  lock dec dword ptr [r14+8]
0x66593a7  jne 0x66596B6
0x66593ad  mov rax,[r14]
0x66593b0  mov rax,[rax]
0x66593b3  mov rcx,r14
0x66593b6  call qword ptr [0xF99FFA0]
0x66593bc  lock dec dword ptr [r14+0xC]
0x66593c1  jne 0x66596B6
0x66593c7  mov rax,[r14]
0x66593ca  mov rax,[rax+8]
0x66593ce  mov rcx,r14
0x66593d1  call qword ptr [0xF99FFA0]
0x66593d7  jmp 0x66596B6
0x66593dc  mov rcx,[rbp+0x4F0]
0x66593e3  mov qword ptr [rbp+0x4F0],0
0x66593ee  movaps xmm0,[rbp+0x4E0]
0x66593f5  xorps xmm1,xmm1
0x66593f8  movaps [rbp+0x4E0],xmm1
0x66593ff  movups [rbp+0x430],xmm0
0x6659406  mov [rbp+0x440],rcx
0x665940d  mov [rbp+0x470],al
0x6659413  lea rax,[rbp+0x344]
0x665941a  lea r10,[rbp+0x39C]
0x6659421  lea r11,[rbp+0x3A8]
0x6659428  lea r9,[rbp+0x430]
0x665942f  lea r8,[rbp+0x478]
0x6659436  mov [rbp+0x478],r15w
0x665943e  lea rdx,[rbp+0x480]
0x6659445  movaps xmm0,[rbp+0x50]
0x6659449  movaps xmm1,[rbp+0x60]
```
// [reg+off] field reads/writes — rbp holds the description/object base (all [rbp+off] operands). rax and r14 are object pointers dereferenced ([rax+8],[rax],[r14+8],[r14],[r14+0xC]); rcx copied to rdx earlier. Reads: [rbp+0x340] (write xmm0); [rax+8]->rcx; [rcx+8] (lock inc); [rbp+0x348]->r14; [rax]->xmm0; [r14+8] (lock dec); [r14]->rax; [rax] (vtable)->rax; [r14+0xC] (lock dec); [r14]->rax; [rax+8]->rax; [rbp+0x4F0]->rcx; [rbp+0x4E0]->xmm0; [rbp+0x50]->xmm0; [rbp+0x60]->xmm1. Writes: [rbp+0x340]=xmm0 (twice); [rcx+8] lock inc; [r14+8] lock dec; [r14+0xC] lock dec; [rbp+0x4F0]=0; [rbp+0x4E0]=xmm1; [rbp+0x430]=xmm0; [rbp+0x440]=rcx; [rbp+0x470]=al; [rbp+0x478]=r15w. lea address computations: [rbp+0x344]->rax; [rbp+0x39C]->r10; [rbp+0x3A8]->r11; [rbp+0x430]->r9; [rbp+0x478]->r8; [rbp+0x480]->rdx. No (bad) instructions; last insn at 0x6659449 (movaps, 4 bytes) -> resume at 0x665944d.

## Phase 6 — 0x665944d (40 instructions)

```
0x665944d  mov qword ptr [rbp+0x58],0
0x6659455  movups [rbp+0x480],xmm0
0x665945c  xorps xmm0,xmm0
0x665945f  movaps [rbp+0x60],xmm0
0x6659463  movups [rbp+0x490],xmm1
0x665946a  mov rcx,[rbp+0x70]
0x665946e  mov [rbp+0x4A0],rcx
0x6659475  mov byte ptr [rbp+0x4B8],0xFF
0x665947c  movzx ecx,byte ptr [rbp+0x88]
0x6659483  cmp rcx,3
0x6659487  ja 0x665A7BD
0x665948d  lea rdi,[rbp+0x4A8]
0x6659494  lea rbx,[0xF2BF3E8]
0x665949b  movsxd r14,[rbx+rcx*4]
0x665949f  add r14,rbx
0x66594a2  jmp r14
0x66594a5  mov rdi,[rbp+0x78]
0x66594a9  mov [rbp+0x4A8],rdi
0x66594b0  jmp 0x665A7B7
0x66594b5  mov rcx,[rbp+0x180]
0x66594bc  mov qword ptr [rbp+0x180],0
0x66594c7  movaps xmm0,[rbp+0x170]
0x66594ce  xorps xmm1,xmm1
0x66594d1  movaps [rbp+0x170],xmm1
0x66594d8  movups [rbp+0x428],xmm0
0x66594df  mov [rbp+0x438],rcx
0x66594e6  mov [rbp+0x468],al
0x66594ec  mov [rbp+0x470],r15w
0x66594f4  movaps xmm0,[rbp+0x4E0]
0x66594fb  movaps xmm1,[rbp+0x4F0]
0x6659502  mov qword ptr [rbp+0x4E8],0
0x665950d  movups [rbp+0x478],xmm0
0x6659514  xorps xmm0,xmm0
0x6659517  movaps [rbp+0x4F0],xmm0
0x665951e  movups [rbp+0x488],xmm1
0x6659525  mov rax,[rbp+0x500]
0x665952c  mov [rbp+0x498],rax
0x6659533  mov byte ptr [rbp+0x4B0],0xFF
0x665953a  movzx eax,byte ptr [rbp+0x518]
0x6659541  cmp rax,3
```
// [reg+off] field reads/writes — rbp holds the description/object base (all [rbp+off] operands). rbx holds jump-table base ([0xF2BF3E8]); rax/rdi hold object pointers. Reads: [rbp+0x480] (write xmm0); [rbp+0x70]->rcx; [rbp+0x88]->ecx (byte); [rbp+0x4A8] (lea->rdi); [0xF2BF3E8] (lea->rbx) + [rbx+rcx*4]->r14 (jump-table entry); [rbp+0x78]->rdi; [rbp+0x180]->rcx; [rbp+0x170]->xmm0; [rbp+0x4E0]->xmm0; [rbp+0x4F0]->xmm1; [rbp+0x500]->rax; [rbp+0x518]->eax (byte). Writes: [rbp+0x58]=0; [rbp+0x480]=xmm0; [rbp+0x60]=xmm0; [rbp+0x490]=xmm1; [rbp+0x4A0]=rcx; [rbp+0x4B8]=0xFF; [rbp+0x4A8]=rdi; [rbp+0x180]=0; [rbp+0x170]=xmm1; [rbp+0x428]=xmm0; [rbp+0x438]=rcx; [rbp+0x468]=al; [rbp+0x470]=r15w; [rbp+0x4E8]=0; [rbp+0x478]=xmm0; [rbp+0x4F0]=xmm0; [rbp+0x488]=xmm1; [rbp+0x498]=rax; [rbp+0x4B0]=0xFF. lea address computations: [rbp+0x4A8]->rdi; [0xF2BF3E8]->rbx. No (bad) instructions; last insn at 0x6659541 (cmp, 4 bytes) -> resume at 0x6659545.

## Phase 7 — 0x6659545 (40 instructions)

```
0x6659545  ja 0x665AF11
0x665954b  lea rcx,[rbp+0x4A0]
0x6659552  lea rdx,[0xF2BF438]
0x6659559  movsxd r8,[rdx+rax*4]
0x665955d  add r8,rdx
0x6659560  jmp r8
0x6659563  mov rcx,[rbp+0x508]
0x665956a  mov [rbp+0x4A0],rcx
0x6659571  jmp 0x665AF0B
0x6659576  lea rbx,[rbp+0x78]
0x665957a  movups xmm0,[rbx]
0x665957d  movups [rdi],xmm0
0x6659580  jmp 0x665A7B7
0x6659585  movups [rdi],xmm0
0x6659588  mov rdi,[rbp+0x80]
0x665958f  test rdi,rdi
0x6659592  je 0x665A7A3
0x6659598  lock inc dword ptr [rdi+8]
0x665959c  mov rdi,[rbp+0x80]
0x66595a3  jmp 0x665A7A5
0x66595a8  lea rdx,[rbp+0x508]
0x66595af  movups xmm0,[rdx]
0x66595b2  movups [rcx],xmm0
0x66595b5  jmp 0x665A8E5
0x66595ba  xorps xmm0,xmm0
0x66595bd  movups [rcx],xmm0
0x66595c0  mov rcx,[rbp+0x510]
0x66595c7  test rcx,rcx
0x66595ca  je 0x665A8CE
0x66595d0  lock inc dword ptr [rcx+8]
0x66595d4  mov rcx,[rbp+0x510]
0x66595db  jmp 0x665A8D0
0x66595e0  lea rdx,[rbp+0x508]
0x66595e7  movups xmm0,[rdx]
0x66595ea  movups [rcx],xmm0
0x66595ed  jmp 0x665AF0B
0x66595f2  movups [rcx],xmm0
0x66595f5  mov rcx,[rbp+0x510]
0x66595fc  test rcx,rcx
0x66595ff  je 0x665AEF4
```
// [reg+off] field reads/writes — rbp holds the description/object base (all [rbp+off] operands). rdi is a destination pointer for stores ([rdi]=xmm0); rcx is a destination pointer ([rcx]=xmm0). Reads: [rbp+0x4A0] (lea->rcx); [0xF2BF438] (lea->rdx) + [rdx+rax*4]->r8 (jump-table entry); [rbp+0x508]->rcx; [rbp+0x78] (lea->rbx); [rbx]->xmm0; [rbp+0x80]->rdi; [rdi+8] (lock inc); [rbp+0x508] (lea->rdx); [rdx]->xmm0; [rbp+0x510]->rcx; [rcx+8] (lock inc). Writes: [rbp+0x4A0]=rcx; [rdi]=xmm0 (twice); [rcx]=xmm0 (multiple). lea address computations: [rbp+0x4A0]->rcx; [0xF2BF438]->rdx; [rbp+0x78]->rbx; [rbp+0x508]->rdx (twice). No (bad) instructions; last insn at 0x66595ff (je near, 6 bytes) -> resume at 0x6659605.

## Phase 8 — 0x6659605 (40 instructions; passes the 0x6659615 range bound)

```
0x6659605  lock inc dword ptr [rcx+8]
0x6659609  mov rcx,[rbp+0x510]
0x6659610  jmp 0x665AEF6
0x6659615  mov rax,[r14]
0x6659618  mov rax,[rax+0x18]
0x665961c  mov r15,[rax]
0x665961f  test r15,r15
0x6659622  je 0x665D11D
0x6659628  mov r15,[rsi]
0x665962b  mov rax,[rbp+0x330]
0x6659632  xorps xmm0,xmm0
0x6659635  movaps [rbp+0x340],xmm0
0x665963c  mov rcx,[rax+8]
0x6659640  test rcx,rcx
0x6659643  je 0x665A0BA
0x6659649  lock inc dword ptr [rcx+8]
0x665964d  mov r14,[rbp+0x348]
0x6659654  movups xmm0,[rax]
0x6659657  movaps [rbp+0x340],xmm0
0x665965e  test r14,r14
0x6659661  je 0x665A0CF
0x6659667  lock dec dword ptr [r14+8]
0x665966c  jne 0x665A0CF
0x6659672  mov rax,[r14]
0x6659675  mov rax,[rax]
0x6659678  mov rcx,r14
0x665967b  call qword ptr [0xF99FFA0]
0x6659681  lock dec dword ptr [r14+0xC]
0x6659686  jne 0x665A0CF
0x665968c  mov rax,[r14]
0x665968f  mov rax,[rax+8]
0x6659693  mov rcx,r14
0x6659696  call qword ptr [0xF99FFA0]
0x665969c  jmp 0x665A0CF
0x66596a1  mov rax,[rax]
0x66596a4  mov [rbp+0x340],rax
0x66596ab  mov qword ptr [rbp+0x348],0
0x66596b6  mov rax,[rbp+0x340]
0x66596bd  mov rax,[rax+0x18]
0x66596c1  mov rax,[rax]
```
// [reg+off] field reads/writes — rbp holds the description/object base (all [rbp+off] operands). r14 and rax are object pointers dereferenced ([r14],[r14+8],[r14+0xC],[rax],[rax+8],[rax+0x18]); rcx is pointer for lock inc [rcx+8]. Reads: [rcx+8] (lock inc); [rbp+0x510]->rcx; [r14]->rax; [rax+0x18]->rax; [rax]->rax/r15; [rsi]->r15; [rbp+0x330]->rax; [rbp+0x340]->rax (read); [rax+8]->rcx; [r14+8] (lock dec); [rbp+0x348]->r14; [rax]->xmm0; [r14]->rax (twice); [r14+0xC] (lock dec); [rax+8]->rax. Writes: [rbp+0x340]=xmm0; [rbp+0x340]=rax; [rbp+0x348]=0. No (bad) instructions; last insn at 0x66596c1 (mov rax,[rax], 3 bytes) -> resume at 0x66596c4. Range bound 0x6659615 passed (insn at 0x6659615 included) — STOP. (40 instructions)
