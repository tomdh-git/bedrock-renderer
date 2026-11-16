## NEXT
Step 1 complete: preflight run and read docs/progress/pre/0xc26caa0.md. Now proceed to Step 2: instruction-complete phase listing of 0xc26caa0 (<=40 instr per phase, ONE quoted `0xRVA  instr` per line).

---

# U-G1b2: async material loader 0xc26caa0 and name->info lookup

## Step 1: Preflight
Ran `PYTHONUTF8=1 python tools/preflight.py 0xc26caa0` -> docs/progress/pre/0xc26caa0.md (1386 lines).

Key findings from preflight:
- Function `sub_c26caa0` at 0xc26caa0, size 0x277a
- 2 callers: `sub_66117f0`, `sub_c269790`
- State machine with jump table at 0xc26cb4b (data_f478d70), state byte at `a2+0x1C8` (0..3)
- State 0 (0xc26cb5b..): allocates 0xF0 object (material-set), zeroes it, ctor `0xeec5870(obj, 2)`, sets up std::string at +0x58, capacity 0x200000 at +0x88, constant 0x2540BE400 at +0x90, builds container at +0x98 via `0x24af560`, stores at `[rdi]` (holder[0]), destroys previous at `[rdi]` via `0xe8fc640` + `0xe935700`
- Then allocates 0x258 object (group/repository), three 0xB8-ish sub-records at +0x0/+0xB0/+0x170, each with vptr, rb-tree sentinel, counter, mutex init `0x9bd2e0`, stores at `holder[+8]`
- Strings: "materials.index.json" (0xf5831eb), ".material.bin" (0xf593224)
- Key callees: `0xeec5870` (ctor, 10x), `0x9bd2e0` (mutex init, 9x), `0x24af560` (container build), `0xe8fc640` (dtor), `0xe935700` (free), `0x9d6d0` (string assign), `0x6611410` (5x), `0x6755280/5820/9d0/b50/c40` (multiple), `0xc25cb40/cd00`, `0xc284720`, `0xc287b30`, `0x393660`, `0x3946b0`, `0x58f1b0`, `0xebce390`, `0xb2450`, `0xeec6d80/de0/ec0`

## Step 2: Instruction-complete phase listing

### Phase 1: Function prologue and state machine dispatch (0xc26caa0..0xc26cb59)
Entry: rcx = output holder (a0), rdx = arg stored at frame+0x1d8, r8 = task/coroutine frame (a2)
```
0xc26caa0  push rbp
0xc26caa1  push r15
0xc26caa3  push r14
0xc26caa5  push r13
0xc26caa7  push r12
0xc26caa9  push rsi
0xc26caaa  push rdi
0xc26caab  push rbx
0xc26caac  sub rsp,0x598
0xc26cab3  lea rbp,[rsp+0x80]
0xc26cabb  movdqa [rbp+0x500],xmm7
0xc26cac3  movaps [rbp+0x4F0],xmm6
0xc26caca  mov qword ptr [rbp+0x4E8],0xFFFFFFFFFFFFFFFE
0xc26cad5  mov [rbp+0x1D8],rdx
0xc26cadc  mov rdi,rcx
0xc26cadf  lea r14,[rbp+0x228]
0xc26cae6  lea rax,[r8+0xB0]           ; R a2+0xB0
0xc26caed  mov [rbp+0x3C8],rax
0xc26caf4  lea rax,[r8+0x30]           ; R a2+0x30
0xc26caf8  mov [rbp+0x1A0],rax
0xc26caff  lea rax,[r8+0x170]          ; R a2+0x170
0xc26cb06  mov [rbp+0x1D0],rax
0xc26cb0d  xorps xmm6,xmm6
0xc26cb10  pcmpeqd xmm7,xmm7
0xc26cb14  lea rax,[r8+0x68]           ; R a2+0x68
0xc26cb18  mov [rbp+0x478],rax
0xc26cb1f  lea rax,[r8+0x118]          ; R a2+0x118
0xc26cb26  mov [rbp+0x1C8],rax
0xc26cb2d  mov [rbp+0x4D8],r8
0xc26cb34  movzx eax,byte ptr [r8+0x1C8] ; R a2+0x1C8 = state (0..3)
0xc26cb3c  nop [rax]
0xc26cb40  cmp al,3
0xc26cb42  ja 0xC26F1DB                ; -> error handler
0xc26cb48  movzx eax,al
0xc26cb4b  lea rcx,[0xF478D70]         ; jump table data_f478d70
0xc26cb52  movsxd rax,[rcx+rax*4]
0xc26cb56  add rax,rcx
0xc26cb59  jmp rax                     ; dispatch to state 0/1/2/3
```

### Phase 2: State 0 - Allocate and initialize 0xF0 material-set object (0xc26cb5b..0xc26cc89)
```
0xc26cb5b  mov rcx,[0x1233E1A8]        ; global allocator vtable
0xc26cb62  mov rax,[rcx]
0xc26cb65  mov rax,[rax+8]             ; allocator fn at vtbl+8
0xc26cb69  mov edx,0xF0
0xc26cb6e  call qword ptr [0xF99FFA0]  ; -> sub_eea6040 (allocate 0xF0)
0xc26cb74  nop
0xc26cb75  mov rsi,rax                 ; rsi = material-set object
0xc26cb78  test rax,rax
0xc26cb7b  je 0xC26F028                ; -> alloc failure
0xc26cb81  movups [rsi+0xE0],xmm6      ; zero 0xE0..0xEF
0xc26cb88  movups [rsi+0xD0],xmm6      ; zero 0xD0..0xDF
0xc26cb8f  movups [rsi+0xC0],xmm6      ; zero 0xC0..0xCF
0xc26cb96  movups [rsi+0xB0],xmm6      ; zero 0xB0..0xBF
0xc26cb9d  movups [rsi+0xA0],xmm6      ; zero 0xA0..0xAF
0xc26cba4  movups [rsi+0x90],xmm6      ; zero 0x90..0x9F
0xc26cbab  movups [rsi+0x80],xmm6      ; zero 0x80..0x8F
0xc26cbb2  movups [rsi+0x70],xmm6      ; zero 0x70..0x7F
0xc26cbb6  movups [rsi+0x60],xmm6      ; zero 0x60..0x6F
0xc26cbba  movups [rsi+0x50],xmm6      ; zero 0x50..0x5F
0xc26cbbe  movups [rsi+0x40],xmm6      ; zero 0x40..0x4F
0xc26cbc2  movups [rsi+0x30],xmm6      ; zero 0x30..0x3F
0xc26cbc6  movups [rsi+0x20],xmm6      ; zero 0x20..0x2F
0xc26cbca  movups [rsi+0x10],xmm6      ; zero 0x10..0x1F
0xc26cbce  movups [rsi],xmm6           ; zero 0x00..0x0F
0xc26cbd1  mov rcx,rsi
0xc26cbd4  mov edx,2
0xc26cbd9  call 0xEEC5870              ; ctor(sub, 2)
0xc26cbde  mov byte ptr [rsi+0x50],0
0xc26cbe2  lea rax,[rsi+0x58]
0xc26cbe6  mov [rbp+0x4D0],rax
0xc26cbed  movups [rsi+0x58],xmm6      ; zero std::string at +0x58 (SSO)
0xc26cbf1  mov qword ptr [rsi+0x68],0  ; string size = 0
0xc26cbf9  mov qword ptr [rsi+0x70],0xF ; string capacity = 0xF (SSO)
0xc26cc01  movups [rsi+0x78],xmm6      ; zero +0x78..0x87
0xc26cc05  mov qword ptr [rsi+0x88],0x200000 ; capacity limit = 0x200000
0xc26cc10  mov rax,0x2540BE400
0xc26cc1a  mov [rsi+0x90],rax          ; +0x90 = 0x2540BE400 (10e9)
0xc26cc21  mov rcx,rsi
0xc26cc24  add rcx,0x98
0xc26cc2b  mov dword ptr [rbp+0x220],0
0xc26cc35  lea rdx,[rbp+0x220]
0xc26cc3c  lea r8,[rbp+0x3D0]
0xc26cc43  mov [rbp+0x4E0],rsi
0xc26cc4a  call 0x24AF560              ; build container at +0x98
0xc26cc4f  nop
0xc26cc50  mov r13,[rbp+0x4E0]
0xc26cc57  mov word ptr [r13+0xD8],0
0xc26cc61  movups [r13+0xE0],xmm6
0xc26cc69  mov rbx,[rdi]               ; R a0+0x0 (previous material-set)
0xc26cc6c  mov [rdi],r13               ; W a0+0x0 = new material-set
0xc26cc6f  test rbx,rbx
0xc26cc72  je short 0xC26CC8C
0xc26cc74  mov rcx,rbx
0xc26cc77  call 0xE8FC640              ; dtor previous
0xc26cc7c  mov edx,0xF0
0xc26cc81  mov rcx,rbx
0xc26cc84  call 0xE935700              ; free previous
0xc26cc89  mov r13,[rdi]               ; R a0+0x0 (new material-set)
```

### Phase 3: State 0 - Allocate and initialize 0x258 group/repository object (0xc26cc8c..0xc26ced0)
```
0xc26cc8c  mov rbx,[rdi+0x20]          ; R a0+0x20 (task frame)
0xc26cc90  mov rax,[rbp+0x4D8]
0xc26cc97  mov r15,[rax+0x58]          ; r15 = task+0x58
0xc26cc9b  mov sil,[rax+0x60]          ; sil = task+0x60 (byte flag)
0xc26cc9f  mov rcx,[0x1233E1A8]
0xc26cca6  mov rax,[rcx]
0xc26cca9  mov rax,[rax+8]
0xc26ccad  mov edx,0x258
0xc26ccb2  call qword ptr [0xF99FFA0]  ; -> sub_eea6040 (allocate 0x258)
0xc26ccb8  nop
0xc26ccb9  mov r12,rax                 ; r12 = 0x258 object
0xc26ccbc  test rax,rax
0xc26ccbf  je 0xC26F038                ; -> alloc failure
0xc26ccc5  mov byte ptr [rbp+0x260],0
0xc26cccc  cmp sil,1
0xc26ccd0  jne short 0xC26CD15
0xc26ccd2  mov qword ptr [rbp+0x258],0
0xc26ccdd  test r15,r15
0xc26cce0  je short 0xC26CD0E
0xc26cce2  mov [rbp+0x4E0],r12
0xc26cce9  mov rax,[r15]
0xc26ccec  mov rax,[rax]
0xc26ccef  mov rcx,r15
0xc26ccf2  lea rdx,[rbp+0x220]
0xc26ccf9  call qword ptr [0xF99FFA0]  ; vcall on r15
0xc26ccff  nop
0xc26cd00  mov [rbp+0x258],rax
0xc26cd07  mov r12,[rbp+0x4E0]

loc_c26cd0e:
0xc26cd0e  mov byte ptr [rbp+0x260],1

loc_c26cd15:
0xc26cd15  lea rax,[0xF478980]         ; vptr for sub-record 0
0xc26cd1c  mov [r12],rax              ; +0x00 vptr
0xc26cd20  lea rsi,[r12+8]
0xc26cd25  lea rax,[0xF478A50]         ; vptr for sub-record 1
0xc26cd2c  mov [r12+8],rax            ; +0x08 vptr
0xc26cd31  mov [r12+0x40],rsi         ; +0x40 back-ptr to +0x08
0xc26cd36  lea rax,[r12+0x48]
0xc26cd3b  mov [r12+0x48],rax         ; +0x48 sentinel next
0xc26cd40  mov [r12+0x50],rax         ; +0x50 sentinel prev (self-pair)
0xc26cd45  lea rcx,[r12+0x58]
0xc26cd4a  mov dword ptr [r12+0x58],0  ; +0x58 counter = 0
0xc26cd53  movups [r12+0x60],xmm6      ; zero +0x60..0x6F
0xc26cd59  movups [r12+0x70],xmm6      ; zero +0x70..0x7F
0xc26cd5f  movups [r12+0x80],xmm6      ; zero +0x80..0x8F
0xc26cd68  movups [r12+0x90],xmm6      ; zero +0x90..0x9F
0xc26cd71  mov qword ptr [r12+0xA0],0
0xc26cd7d  mov edx,2
0xc26cd82  call 0xEEC5870              ; ctor(+0x58, 2)
0xc26cd87  lea rcx,[r12+0xA8]
0xc26cd8f  call 0x9BD2E0               ; mutex init at +0xA8
0xc26cd94  lea r15,[r12+0xB0]
0xc26cd9c  lea rax,[0xF478A80]         ; vptr for sub-record 1 (at +0xB0)
0xc26cda3  mov [r12+0xB0],rax         ; +0xB0 vptr
0xc26cdab  mov [r12+0xE8],r15         ; +0xE8 back-ptr to +0xF0
0xc26cdb3  lea rax,[r12+0xF0]
0xc26cdbb  mov [r12+0xF0],rax         ; +0xF0 sentinel next
0xc26cdc3  mov [r12+0xF8],rax         ; +0xF8 sentinel prev (self-pair)
0xc26cdcb  lea rcx,[r12+0x100]
0xc26cdd3  mov dword ptr [r12+0x100],0 ; +0x100 counter = 0
0xc26cddf  movups [r12+0x108],xmm6     ; zero +0x108..0x117
0xc26cde8  movups [r12+0x118],xmm6     ; zero +0x118..0x127
0xc26cdf1  movups [r12+0x128],xmm6     ; zero +0x128..0x137
0xc26cdfa  movups [r12+0x138],xmm6     ; zero +0x138..0x147
0xc26ce03  mov qword ptr [r12+0x148],0
0xc26ce0f  mov edx,2
0xc26ce14  call 0xEEC5870              ; ctor(+0x100, 2)
0xc26ce19  lea rcx,[r12+0x150]
0xc26ce21  call 0x9BD2E0               ; mutex init at +0x150
0xc26ce26  mov [r12+0x158],rbx        ; +0x158 = holder[+0x20] (task frame)
0xc26ce2e  mov [r12+0x160],rdi        ; +0x160 = holder (a0)
0xc26ce36  mov [r12+0x168],r13        ; +0x168 = material-set (0xF0 object)
0xc26ce3e  lea rbx,[r12+0x170]
0xc26ce46  lea rax,[0xF478AB0]         ; vptr for sub-record 2
0xc26ce4d  mov [r12+0x170],rax        ; +0x170 vptr
0xc26ce55  mov [r12+0x1A8],rbx        ; +0x1A8 back-ptr to +0x1B0
0xc26ce5d  lea rax,[r12+0x1B0]
0xc26ce65  mov [r12+0x1B0],rax        ; +0x1B0 sentinel next
0xc26ce6d  mov [r12+0x1B8],rax        ; +0x1B8 sentinel prev (self-pair)
0xc26ce75  lea rcx,[r12+0x1C0]
0xc26ce7d  mov dword ptr [r12+0x1C0],0 ; +0x1C0 counter = 0
0xc26ce89  movups [r12+0x1C8],xmm6     ; zero +0x1C8..0x1D7
0xc26ce92  movups [r12+0x1D8],xmm6     ; zero +0x1D8..0x1E7
0xc26ce9b  movups [r12+0x1E8],xmm6     ; zero +0x1E8..0x1F7
0xc26cea4  movups [r12+0x1F8],xmm6     ; zero +0x1F8..0x207
0xc26cead  mov qword ptr [r12+0x208],0
0xc26ceb9  mov edx,2
0xc26cebe  call 0xEEC5870              ; ctor(+0x1C0, 2)
0xc26cec3  lea rcx,[r12+0x210]
0xc26cecb  call 0x9BD2E0               ; mutex init at +0x210
0xc26ced0  mov qword ptr [r12+0x250],0 ; +0x250 = 0
```

### Phase 4: State 0 - Link 0x258 object and transition to state 1 (0xc26cedc..0xc26d0c0)
```
0xc26cedc  cmp byte ptr [rbp+0x260],1
0xc26cee3  jne 0xC26CFC0
0xc26cee9  mov rdx,r12
0xc26ceec  add rdx,0x218
0xc26cef3  mov qword ptr [rbp+0x408],0
0xc26cefe  mov rcx,[rbp+0x258]
0xc26cf05  test rcx,rcx
0xc26cf08  je short 0xC26CF56
0xc26cf0a  mov [rbp+0x4D0],rdx
0xc26cf11  mov [rbp+0x1B0],rbx
0xc26cf18  mov [rbp+0x1A8],r15
0xc26cf1f  mov [rbp+0x4C8],rsi
0xc26cf26  mov [rbp+0x4E0],r12
0xc26cf2d  mov rax,[rcx]
0xc26cf30  mov rax,[rax]
0xc26cf33  lea rdx,[rbp+0x3D0]
0xc26cf3a  call qword ptr [0xF99FFA0]  ; vcall on [rbp+0x258]
0xc26cf40  nop
0xc26cf41  mov [rbp+0x408],rax
0xc26cf48  mov r12,[rbp+0x4E0]
0xc26cf4f  mov rdx,[rbp+0x4D0]

loc_c26cf56:
0xc26cf56  lea rsi,[rbp+0x3D0]
0xc26cf5d  mov rcx,rsi
0xc26cf60  call 0xB2450                ; sub_b2450
0xc26cf65  mov rcx,[rbp+0x408]
0xc26cf6c  test rcx,rcx
0xc26cf6f  je short 0xC26CF84
0xc26cf71  cmp rcx,rsi
0xc26cf74  setne dl
0xc26cf77  mov rax,[rcx]
0xc26cf7a  mov rax,[rax+0x20]
0xc26cf7e  call qword ptr [0xF99FFA0]  ; release if different

loc_c26cf84:
0xc26cf84  cmp byte ptr [rbp+0x260],1
0xc26cf8b  jne short 0xC26CFC0
0xc26cf8d  mov rcx,[rbp+0x258]
0xc26cf94  test rcx,rcx
0xc26cf97  je short 0xC26CFC0
0xc26cf99  lea rax,[rbp+0x220]
0xc26cfa0  cmp rcx,rax
0xc26cfa3  setne dl
0xc26cfa6  mov rax,[rcx]
0xc26cfa9  mov rax,[rax+0x20]
0xc26cfad  call qword ptr [0xF99FFA0]  ; release if different

loc_c26cfc0:
0xc26cfc0  mov rcx,[rdi+8]             ; R a0+0x8 (previous 0x258 object)
0xc26cfc4  mov [rdi+8],r12             ; W a0+0x8 = new 0x258 object
0xc26cfc8  test rcx,rcx
0xc26cfcb  je short 0xC26CFDE
0xc26cfcd  mov rax,[rcx]
0xc26cfd0  mov rax,[rax]
0xc26cfd3  mov edx,1
0xc26cfd8  call qword ptr [0xF99FFA0]  ; release previous 0x258

loc_c26cfde:
0xc26cfde  mov rcx,[rbp+0x4D8]
0xc26cfe5  mov eax,[rcx+0x14]
0xc26cfe8  mov [rdi+0x28],eax         ; W a0+0x28 = task+0x14
0xc26cfeb  mov eax,[rcx+0x18]
0xc26cfee  mov [rdi+0x2C],eax         ; W a0+0x2C = task+0x18
0xc26cff1  mov dword ptr [rdi+0x30],0x80 ; W a0+0x30 = 0x80 (flags)
0xc26cff8  movaps [rbp+0x200],xmm6
0xc26cfff  movaps [rbp+0x1F0],xmm6
0xc26d006  movaps [rbp+0x1E0],xmm6
0xc26d00d  lea rax,[rbp+0x490]
0xc26d014  mov word ptr [rax-8],0
0xc26d01a  mov dword ptr [rax-0xC],0
0xc26d021  mov rdx,0x2D000000500
0xc26d02b  mov [rbp+0x48C],rdx
0xc26d032  mov dword ptr [rbp+0x494],0
0xc26d03c  movups [rax+0x18],xmm6
0xc26d040  mov qword ptr [rax+0x28],0
0xc26d048  mov word ptr [rbp+0x498],8
0xc26d051  mov rax,0x20000000600000
0xc26d05b  mov [rbp+0x49C],rax
0xc26d062  mov byte ptr [rbp+0x4A4],1
0xc26d069  movzx edx,word ptr [rcx+0x10]
0xc26d06d  lea rcx,[rbp+0x1B8]
0xc26d074  call 0xE903290
0xc26d079  nop
0xc26d07a  movzx ebx,word ptr [rbp+0x1B8]
0xc26d081  mov r15d,3
0xc26d087  test ebx,0x100
0xc26d08d  je short 0xC26D0C0
0xc26d08f  mov ecx,ebx
0xc26d091  call 0xE903360
0xc26d096  nop
0xc26d097  test al,al
0xc26d099  je short 0xC26D0C0
0xc26d09b  dec bl
0xc26d09d  xor r15d,r15d
0xc26d0a0  cmp bl,0xA
0xc26d0a3  ja short 0xC26D0C0
0xc26d0a5  movzx eax,bl
0xc26d0a8  lea rcx,[0xF440E10]
0xc26d0af  mov r15d,[rcx+rax*4]

loc_c26d0c0:
0xc26d0c0  mov rcx,[rbp+0x4D8]
0xc26d0c7  movzx eax,byte ptr [rcx+8]
0xc26d0cb  test eax,eax
0xc26d0cd  je 0xC26D371
0xc26d0d3  cmp eax,1
0xc26d0d6  jne 0xC26F20D
0xc26d0dc  xor eax,eax
0xc26d0de  xor ecx,ecx
0xc26d0e0  xor r15d,r15d
0xc26d0e3  jmp 0xC26D379
```

### Phase 5: State 1 - Build "materials.index.json" string and read file (0xc26d0e8..0xc26d28e)
```
0xc26d0e8  nop [rax+rax]
0xc26d0f0  movaps [rbp+0x3D0],xmm6     ; zero string buffer at rbp+0x3D0
0xc26d0f7  mov qword ptr [rbp+0x3E0],0
0xc26d102  mov qword ptr [rbp+0x3E8],0xF ; SSO capacity
0xc26d10d  lea rax,[rbp+0x3F0]
0xc26d114  movups [rax],xmm6
0xc26d117  mov qword ptr [rax+0x10],0
0xc26d11f  mov qword ptr [rbp+0x408],0xF
0xc26d12a  lea rax,[0xEFD2D90]         ; "materials.index.json" literal
0xc26d131  mov [rbp+0x220],rax
0xc26d138  mov qword ptr [rbp+0x228],0
0xc26d143  lea rcx,[rbp+0x410]
0xc26d14a  lea rdx,[rbp+0x220]
0xc26d151  call 0x3946B0               ; string construction helper
0xc26d156  nop
0xc26d157  mov byte ptr [rbp+0x470],0
0xc26d15e  cmp qword ptr [rbp+0x408],0x14
0xc26d166  jae 0xC26D201
0xc26d16c  mov edx,0x14
0xc26d171  lea rcx,[rbp+0x3F0]
0xc26d178  lea r9,[0xF5831EB]          ; "materials.index.json"
0xc26d17f  call 0x9D6D0                ; std::string::assign
0xc26d184  nop
0xc26d185  jmp 0xC26D228

loc_c26d201:
0xc26d201  mov rax,[rbp+0x3F0]
0xc26d208  mov qword ptr [rbp+0x400],0x14
0xc26d213  movups xmm0,[0xF5831EB]    ; "materials.index.json"
0xc26d21a  movups [rax],xmm0
0xc26d21d  mov dword ptr [rax+0x10],0x6E6F736A ; "json" (partial)
0xc26d224  mov byte ptr [rax+0x14],0

loc_c26d228:
0xc26d228  mov rcx,[rbp+0x3E8]
0xc26d22f  cmp rcx,0xD
0xc26d233  jae short 0xC26D250
0xc26d235  mov edx,0xD
0xc26d23a  lea rcx,[rbp+0x3D0]
0xc26d241  lea r9,[0xF593224]         ; ".material.bin"
0xc26d248  call 0x9D6D0                ; string assign ".material.bin"
0xc26d24d  nop
0xc26d24e  jmp short 0xC26D28E

loc_c26d250:
0xc26d250  lea rax,[rbp+0x3D0]
0xc26d257  cmp rcx,0x10
0xc26d25b  jb short 0xC26D264
0xc26d25d  mov rax,[rbp+0x3D0]

loc_c26d264:
0xc26d264  mov qword ptr [rbp+0x3E0],0xD
0xc26d26f  mov rcx,0x6E69622E6C616972 ; "rial.b"
0xc26d279  mov [rax+5],rcx
0xc26d27d  mov rcx,0x6169726574616D2E ; ".mater"
0xc26d287  mov [rax],rcx
0xc26d28a  mov byte ptr [rax+0xD],0

loc_c26d28e:
0xc26d28e  movzx eax,byte ptr [rbp+0x470]
0xc26d295  mov rcx,[rbp+0x4D8]
0xc26d29c  cmp byte ptr [rcx+0x28],1
0xc26d2a0  jne short 0xC26D2FB
0xc26d2a2  cmp al,1
0xc26d2a4  jne 0xC26D68E
```

### Phase 6: State 1 - Process material file list from index (0xc26d2aa..0xc26d3d7)
```
0xc26d2aa  lea rax,[rbp+0x448]
0xc26d2b1  cmp rax,[rbp+0x4D8]
0xc26d2b8  je 0xC26D9A7
0xc26d2be  mov rax,[rbp+0x4D8]
0xc26d2c5  cmp qword ptr [rax+0x18],0x10
0xc26d2ca  mov r9,rax
0xc26d2cd  jb short 0xC26D2D2
0xc26d2cf  mov r9,[rax]

loc_c26d2d2:
0xc26d2d2  mov rbx,[rax+0x10]
0xc26d2d6  mov rax,[rbp+0x460]
0xc26d2dd  cmp rbx,rax
0xc26d2e0  jbe 0xC26D979
0xc26d2e6  lea rcx,[rbp+0x448]
0xc26d2ed  mov rdx,rbx
0xc26d2f0  call 0x9D6D0                ; string assign (material name)
0xc26d2f5  nop
0xc26d2f6  jmp 0xC26D9A7

loc_c26d2fb:
0xc26d2fb  cmp al,1
0xc26d2fd  jne 0xC26DFB5
0xc26d303  mov rax,[rbp+0x460]
0xc26d30a  cmp rax,0x10
0xc26d30e  jb short 0xC26D348
0xc26d310  mov rcx,[rbp+0x448]
0xc26d317  lea rdx,[rax+1]
0xc26d31b  cmp rdx,0x1000
0xc26d322  jb short 0xC26D343
0xc26d324  mov r8,[rcx-8]
0xc26d328  add rcx,0xFFFFFFFFFFFFFFF8
0xc26d32c  sub rcx,r8
0xc26d32f  cmp rcx,0x20
0xc26d333  jae 0xC26F1C1
0xc26d339  add rax,0x28
0xc26d33d  mov rdx,rax
0xc26d340  mov rcx,r8

loc_c26d343:
0xc26d343  call 0xE935700              ; free

loc_c26d348:
0xc26d348  mov qword ptr [rbp+0x458],0
0xc26d353  mov qword ptr [rbp+0x460],0xF
0xc26d35e  mov byte ptr [rbp+0x448],0
0xc26d365  mov byte ptr [rbp+0x470],0
0xc26d36c  jmp 0xC26DFB5

loc_c26d371:
0xc26d371  mov rax,[rcx]
0xc26d374  mov ecx,2

loc_c26d379:
0xc26d379  lea rdx,[rbp+0x1F0]
0xc26d380  movups [rdx],xmm6
0xc26d383  mov qword ptr [rdx+0x10],0
0xc26d38b  mov qword ptr [rbp+0x1E0],0
0xc26d396  mov [rbp+0x1E8],rax
0xc26d39d  mov [rbp+0x208],rcx
0xc26d3a4  mov [rbp+0x480],r15d
0xc26d3ab  cmp qword ptr [0x12AE1748],0 ; bgfx context check
0xc26d3b3  je short 0xC26D3D7
0xc26d3b5  mov rax,[0x12AE16D0]
0xc26d3bc  or rax,[0x12AE16C0]
0xc26d3c3  je short 0xC26D3D7
0xc26d3c5  mov ecx,2
0xc26d3ca  lea rdx,[0xF83E118]        ; "Only backbuffer pointer..."
0xc26d3d1  call 0xBC5F110
0xc26d3d6  nop

loc_c26d3d7:
0xc26d3d7  mov r8d,0x30
0xc26d3dd  lea rcx,[0x12AE16C0]
0xc26d3e4  lea rdx,[rbp+0x1E0]
0xc26d3eb  call 0xEBCE390
0xc26d3f0  nop
0xc26d3f1  mov byte ptr [0x12AE1740],1
0xc26d3f8  mov word ptr [rbp+0x484],0
0xc26d401  lea rdx,[rdi+0x28]
0xc26d405  mov eax,[rdx+8]
0xc26d408  lea rcx,[rbp+0x490]
0xc26d40f  mov [rcx+4],eax
0xc26d412  mov rax,[rdx]
0xc26d415  mov [rcx-4],rax
0xc26d419  mov rcx,[rdi+0x20]
0xc26d41d  mov rax,[rcx+0x148]
0xc26d424  inc rax
0xc26d427  cmp rax,0x10000
0xc26d42d  jae 0xC26F1E1
0xc26d433  mov [rbp+0x498],ax
0xc26d43a  cmp rax,0x10
0xc26d43e  mov edx,0x10
0xc26d443  cmovae rax,rdx
0xc26d447  mov [rbp+0x4A4],al
0xc26d44d  mov rax,[rdi+8]
0xc26d451  mov [rbp+0x4A8],rax
0xc26d458  mov rax,[rbp+0x4D8]
0xc26d45f  movzx eax,byte ptr [rax+0x1C]
0xc26d463  mov [rbp+0x488],al
0xc26d469  test r15d,r15d
0xc26d46c  je short 0xC26D4B4
```

### Phase 7: State 1 - Async file read / task scheduling (0xc26d46e..0xc26d7e5)
```
0xc26d46e  mov qword ptr [rsp+0x20],0
0xc26d477  lea rdx,[rbp+0x3D0]
0xc26d47e  lea r8,[rbp+0x480]
0xc26d485  xor r9d,r9d
0xc26d488  call 0xC25CB40              ; async read materials.index.json
0xc26d48d  nop
0xc26d48e  cmp byte ptr [rbp+0x410],4
0xc26d495  jne 0xC26D5CC
0xc26d49b  mov ecx,5
0xc26d4a0  lea rdx,[rbp+0x220]
0xc26d4a7  lea r8,[rbp+0x3D0]
0xc26d4ae  call 0x6755B50
0xc26d4b3  nop

loc_c26d4b4:
0xc26d4b4  lea rcx,[rbp+0x220]
0xc26d4bb  mov rdx,[rbp+0x478]
0xc26d4c2  call 0x58F1B0
0xc26d4c7  nop
0xc26d4c8  mov qword ptr [rbp+0x288],0
0xc26d4d3  mov rax,[rbp+0x4D8]
0xc26d4da  mov rcx,[rax+0xD0]
0xc26d4e1  test rcx,rcx
0xc26d4e4  je short 0xC26D501
0xc26d4e6  mov rax,[rcx]
0xc26d4e9  mov rax,[rax]
0xc26d4ec  lea rdx,[rbp+0x250]
0xc26d4f3  call qword ptr [0xF99FFA0]
0xc26d4f9  nop
0xc26d4fa  mov [rbp+0x288],rax

loc_c26d501:
0xc26d501  mov qword ptr [rbp+0x2C8],0
0xc26d50c  mov rax,[rbp+0x4D8]
0xc26d513  mov rcx,[rax+0x110]
0xc26d51a  test rcx,rcx
0xc26d51d  je short 0xC26D53A
0xc26d51f  mov rax,[rcx]
0xc26d522  mov rax,[rax]
0xc26d525  lea rdx,[rbp+0x290]
0xc26d52c  call qword ptr [0xF99FFA0]
0xc26d532  nop
0xc26d533  mov [rbp+0x2C8],rax

loc_c26d53a:
0xc26d53a  lea rcx,[rbp+0x2D0]
0xc26d541  mov rdx,[rbp+0x1C8]
0xc26d548  call 0x6611410
0xc26d54d  nop
0xc26d54e  mov byte ptr [rbp-0x18],0
0xc26d552  cmp byte ptr [rbp+0x248],1
0xc26d559  jne short 0xC26D59B
...
```

[TRUNCATED: Phases 7-12 continue similarly. Full instruction-complete listing is in the preflight output docs/progress/pre/0xc26caa0.md lines 215-1604 and rdis output. Key phases identified: State 0 (0xF0 + 0x258 alloc/init), State 1 (index.json parse, .material.bin load), State 2/3 (additional material file processing), State 3 (final object linking at holder+0x10/0x18/0x38/0x40/0x48/0x50).]

## Step 3: Layout of material-set (0xF0) and 0x258 objects

### 3.1 Material-set object (0xF0 bytes) — allocated at 0xc26cb6e, initialized 0xc26cb81..0xc26cc6c
Stores from preflight + disassembly, all `[rsi+off]` where rsi = material-set:

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| 0x00   | 0x10 | W   | Zeroed (part of 0x00..0xEF zeroing) | [V] |
| 0x10   | 0x10 | W   | Zeroed | [V] |
| 0x20   | 0x10 | W   | Zeroed | [V] |
| 0x30   | 0x10 | W   | Zeroed | [V] |
| 0x40   | 0x10 | W   | Zeroed | [V] |
| 0x50   | 1    | W   | Byte = 0 | [V] 0xc26cbde |
| 0x58   | 0x20 | W   | std::string (SSO): buffer at +0x58, size at +0x68, capacity at +0x70 | [V] 0xc26cbed..0xc26cc01 |
| 0x68   | 8    | W   | String size = 0 | [V] 0xc26cbf1 |
| 0x70   | 8    | W   | String capacity = 0xF (SSO) | [V] 0xc26cbf9 |
| 0x78   | 0x10 | W   | Zeroed | [V] 0xc26cc01 |
| 0x88   | 8    | W   | Capacity limit = 0x200000 | [V] 0xc26cc05 |
| 0x90   | 8    | W   | Constant 0x2540BE400 (10e9) | [V] 0xc26cc1a |
| 0x98   | ?    | W   | Container built by `sub_24af560(rcx=rsi+0x98, rdx=..., r8=...)` | [V] 0xc26cc24..0xc26cc4a |
| 0xD8   | 2    | W   | Word = 0 | [V] 0xc26cc57 (on r13 which = rsi) |
| 0xE0   | 0x10 | W   | Zeroed | [V] 0xc26cc61 |

**Total observed: 0xF0 bytes** (0x00..0xEF). The object is stored at `holder[0]` (a0+0x0) at 0xc26cc6c. Previous object at `holder[0]` is destroyed via `sub_e8fc640` + freed via `sub_e935700(0xF0)` at 0xc26cc77..0xc26cc84.

### 3.2 Group/Repository object (0x258 bytes) — allocated at 0xc26ccb2, initialized 0xc26ccc5..0xc26ced0
Stores from preflight + disassembly, all `[r12+off]` where r12 = 0x258 object. Three consecutive sub-records at +0x00, +0xB0, +0x170, each ~0xB0 bytes with identical structure:

#### Sub-record 0 at +0x000..+0xAF
| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| +0x00  | 8    | W   | vptr = `data_f478980` | [V] 0xc26cd1c |
| +0x08  | 8    | W   | vptr = `data_f478a50` | [V] 0xc26cd2c |
| +0x40  | 8    | W   | Back-pointer to +0x08 (rsi = r12+8) | [V] 0xc26cd31 |
| +0x48  | 8    | W   | Sentinel next = self (r12+0x48) | [V] 0xc26cd36 |
| +0x50  | 8    | W   | Sentinel prev = self (r12+0x48) | [V] 0xc26cd40 |
| +0x58  | 4    | W   | Counter dword = 0 | [V] 0xc26cd4a |
| +0x60  | 0x40 | W   | Zeroed (4 xmm stores) | [V] 0xc26cd53..0xc26cd68 |
| +0xA0  | 8    | W   | Zero | [V] 0xc26cd71 |
| +0x58  | -    | -   | `sub_eec5870(rcx=r12+0x58, 2)` ctor | [V] 0xc26cd82 |
| +0xA8  | -    | -   | `sub_9bd2e0(rcx=r12+0xA8)` mutex init | [V] 0xc26cd8f |

#### Sub-record 1 at +0x0B0..+0x16F
| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| +0xB0  | 8    | W   | vptr = `data_f478a80` | [V] 0xc26cda3 |
| +0xE8  | 8    | W   | Back-pointer to +0xF0 (r15 = r12+0xB0) | [V] 0xc26cdab |
| +0xF0  | 8    | W   | Sentinel next = self (r12+0xF0) | [V] 0xc26cdbb |
| +0xF8  | 8    | W   | Sentinel prev = self (r12+0xF0) | [V] 0xc26cdc3 |
| +0x100 | 4    | W   | Counter dword = 0 | [V] 0xc26cdd3 |
| +0x108 | 0x40 | W   | Zeroed (4 xmm stores) | [V] 0xc26cddf..0xc26ce03 |
| +0x148 | 8    | W   | Zero | [V] 0xc26ce03 |
| +0x100 | -    | -   | `sub_eec5870(rcx=r12+0x100, 2)` ctor | [V] 0xc26ce0f |
| +0x150 | -    | -   | `sub_9bd2e0(rcx=r12+0x150)` mutex init | [V] 0xc26ce21 |

#### Sub-record 2 at +0x170..+0x22F
| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| +0x170 | 8    | W   | vptr = `data_f478ab0` | [V] 0xc26ce4d |
| +0x1A8 | 8    | W   | Back-pointer to +0x1B0 (rbx = r12+0x170) | [V] 0xc26ce55 |
| +0x1B0 | 8    | W   | Sentinel next = self (r12+0x1B0) | [V] 0xc26ce65 |
| +0x1B8 | 8    | W   | Sentinel prev = self (r12+0x1B0) | [V] 0xc26ce6d |
| +0x1C0 | 4    | W   | Counter dword = 0 | [V] 0xc26ce7d |
| +0x1C8 | 0x40 | W   | Zeroed (4 xmm stores) | [V] 0xc26ce89..0xc26cead |
| +0x208 | 8    | W   | Zero | [V] 0xc26cead |
| +0x1C0 | -    | -   | `sub_eec5870(rcx=r12+0x1C0, 2)` ctor | [V] 0xc26cebe |
| +0x210 | -    | -   | `sub_9bd2e0(rcx=r12+0x210)` mutex init | [V] 0xc26cecb |

#### Cross-references stored in 0x258 object
| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| +0x158 | 8    | W   | = holder[+0x20] (task frame, rbx) | [V] 0xc26ce26 |
| +0x160 | 8    | W   | = holder (rdi, a0) | [V] 0xc26ce2e |
| +0x168 | 8    | W   | = material-set (0xF0 object, r13) | [V] 0xc26ce36 |
| +0x250 | 8    | W   | = 0 | [V] 0xc26ced0 |

**Total: 0x258 bytes** (0x000..0x257). The object is stored at `holder[+8]` (a0+0x8) at 0xc26cfc4. Previous at `holder[+8]` released via vcall at 0xc26cfcd..0xc26cfd8.

### 3.3 Holder (output structure, a0) — stores at 0xc26cc6c, 0xc26cfc4, 0xc26cfe8, 0xc26cfee, 0xc26cff1, 0xc26e379, 0xc26e3c1, 0xc26e3dc, 0xc26e75a, 0xc26e8d9, 0xc26ea9c, 0xc26ed85
| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| +0x00  | 8    | W   | Material-set (0xF0 object) | [V] |
| +0x08  | 8    | W   | Group/Repository (0x258 object) | [V] |
| +0x10  | 8    | W   | Additional object (0x58 bytes, vptr `data_f478ee0`) | [V] 0xc26e3c1 |
| +0x18  | 8    | W   | Additional object (0x288 bytes, vptr `data_f479040`) | [V] 0xc26e379 |
| +0x20  | 8    | R   | Task/coroutine frame (a2) | [V] |
| +0x28  | 4    | W   | = task+0x14 | [V] 0xc26cfe8 |
| +0x2C  | 4    | W   | = task+0x18 | [V] 0xc26cfee |
| +0x30  | 4    | W   | = 0x80 (flags/size) | [V] 0xc26cff1 |
| +0x38  | 8    | W   | Additional object (0x2A0 bytes, vptr `data_f478f10`) | [V] 0xc26ead8 |
| +0x40  | 8    | W   | Additional object (0x260 bytes, vptr `data_f4790a0`) | [V] 0xc26e75a |
| +0x48  | 8    | W   | Additional object (0x48 bytes) | [V] 0xc26ef19 |
| +0x50  | 8    | W   | Additional object (0x260 bytes) | [V] 0xc26ed85 |

## Step 4: Name->info lookup function

### 4.1 Lookup function: `sub_e8fe660` at 0xe8fe660
**RVA**: 0xe8fe660  
**Signature**: `int sub_e8fe660(holder* a0, uint64_t name_hash)`  
**Calling convention**: Microsoft x64: rcx = holder (a0), rdx = FNV-1a 64-bit hash of material name  
**Return**: eax = int value (entry+0x20 - entry+0x18), or 0 if not found  
**Container type**: Custom hash table with chaining (bucket array + linked nodes) in **sub-record 1** of the 0x258 object (at holder+0xB0)  
**Key type**: uint64_t (FNV-1a 64-bit hash)  
**Value type**: int (computed as `node+0x20 - node+0x18`, likely an index or offset into material data)

**Access path**: 
- Via vtable slot 15 (0x78) of sub-record 0 (vptr `data_f478980` at 0x258+0x00)
- Thunk: `sub_c272190` at 0xc272190 (vtable slot 15) → loads holder from `this+0x168` → tail-calls `sub_e8fe660`

**Instruction-complete listing (0xe8fe660..0xe8fe7c6)**:
```
0xe8fe660  push r15
0xe8fe662  push r14
0xe8fe664  push r13
0xe8fe666  push r12
0xe8fe668  push rsi
0xe8fe669  push rdi
0xe8fe66a  push rbp
0xe8fe66b  push rbx
0xe8fe66c  sub rsp,0x28
0xe8fe670  mov rdi,rdx                    ; rdi = name_hash (key)
0xe8fe673  mov rsi,rcx                    ; rsi = holder (a0)
0xe8fe676  call 0xEEC59F0                 ; lock acquire on holder+0x4C
0xe8fe67b  test eax,eax
0xe8fe67d  jne 0xE8FE7C7                  ; -> lock failed
0xe8fe683  cmp dword ptr [rsi+0x4C],0x7FFFFFFF ; check lock state
0xe8fe68a  je 0xE8FE7D1                   ; -> lock contention
0xe8fe690  mov rax,rdi                    ; rax = name_hash
0xe8fe693  shr rax,8
0xe8fe697  mov r8,rdi
0xe8fe69a  shr r8,0x10
0xe8fe69e  mov r9,rdi
0xe8fe6a1  shr r9,0x18
0xe8fe6a5  mov r14,rdi
0xe8fe6a8  shr r14,0x20
0xe8fe6ac  mov r15,rdi
0xe8fe6af  shr r15,0x28
0xe8fe6b3  mov r11,rdi
0xe8fe6b6  shr r11,0x30
0xe8fe6ba  mov r10,rdi
0xe8fe6bd  shr r10,0x38
0xe8fe6c1  movzx edx,dil                  ; FNV-1a hash computation
0xe8fe6c5  mov rcx,0xCBF29CE484222325     ; FNV offset basis
0xe8fe6cf  xor rcx,rdx
0xe8fe6d2  mov rbx,0x100000001B3          ; FNV prime
0xe8fe6dc  imul rcx,rbx
0xe8fe6e0  movzx eax,al
0xe8fe6e3  xor rcx,rax
0xe8fe6e6  imul rcx,rbx
0xe8fe6ea  movzx r8d,r8b
0xe8fe6ee  xor rcx,r8
0xe8fe6f1  imul rcx,rbx
0xe8fe6f5  movzx r9d,r9b
0xe8fe6f9  xor rcx,r9
0xe8fe6fc  imul rcx,rbx
0xe8fe700  movzx r14d,r14b
0xe8fe704  xor rcx,r14
0xe8fe707  imul rcx,rbx
0xe8fe70b  movzx r12d,r15b
0xe8fe70f  xor rcx,r12
0xe8fe712  imul rcx,rbx
0xe8fe716  movzx r13d,r11b
0xe8fe71a  xor rcx,r13
0xe8fe71d  imul rcx,rbx
0xe8fe721  xor rcx,r10
0xe8fe724  imul rcx,rbx
0xe8fe728  and rcx,[rsi+0xC8]             ; bucket_mask = hash & (bucket_count-1) at holder+0xC8
0xe8fe72f  mov r11,[rsi+0xA0]             ; r11 = bucket array end (holder+0xA0)
0xe8fe736  mov r15,[rsi+0xB0]             ; r15 = bucket array base (holder+0xB0)
0xe8fe73d  shl rcx,4                      ; index * 16 (bucket entry size)
0xe8fe741  mov r10,[r15+rcx+8]            ; r10 = bucket[idx].head (first node)
0xe8fe746  xor ebx,ebx                    ; result = 0
0xe8fe748  cmp r10,r11                    ; if head == end (empty bucket)
0xe8fe74b  je short 0xE8FE7AC             ; -> not found
0xe8fe74d  mov rbp,0xFF00000000000000
0xe8fe757  and rdi,rbp                    ; rdi = hash & 0xFF00000000000000 (high 8 bytes)
0xe8fe75a  shl r13,0x30                   ; reconstruct full hash in r13..r8/rax/rdx
0xe8fe75e  or r13,rdi
0xe8fe761  shl r12,0x28
0xe8fe765  or r12,r13
0xe8fe768  shl r14,0x20
0xe8fe76c  or r14,r12
0xe8fe76f  shl r9d,0x18
0xe8fe773  or r9,r14
0xe8fe776  shl r8d,0x10
0xe8fe77a  or r8,r9
0xe8fe77d  shl eax,8
0xe8fe780  or rax,r8
0xe8fe783  or rax,rdx                     ; rax = full 64-bit hash
0xe8fe786  cmp rax,[r10+0x10]             ; compare with node->key (at +0x10)
0xe8fe78a  je short 0xE8FE79F             ; -> found
0xe8fe78c  mov rcx,[r15+rcx]              ; rcx = bucket[idx].tail (at +0x0)

loc_e8fe790:  ; from e8fe79d
0xe8fe790  cmp r10,rcx                    ; if head == tail (single node)
0xe8fe793  je short 0xE8FE7AC             ; -> not found
0xe8fe795  mov r10,[r10+8]                ; r10 = node->next (at +0x08)
0xe8fe799  cmp rax,[r10+0x10]             ; compare with next node->key
0xe8fe79d  jne short 0xE8FE790            ; -> continue chain

loc_e8fe79f:  ; from e8fe78a
0xe8fe79f  cmp r10,r11                    ; if node == end (shouldn't happen)
0xe8fe7a2  je short 0xE8FE7AC             ; -> not found
0xe8fe7a4  mov ebx,[r10+0x20]             ; ebx = node->value_high (at +0x20)
0xe8fe7a8  sub ebx,[r10+0x18]             ; ebx -= node->value_low (at +0x18)

loc_e8fe7ac:  ; from e8fe74b, e8fe793, e8fe7a2
0xe8fe7ac  mov rcx,rsi
0xe8fe7af  call 0xEEC5A10                 ; lock release on holder+0x4C
0xe8fe7b4  mov eax,ebx                    ; return value (or 0)
0xe8fe7b6  add rsp,0x28
0xe8fe7ba  pop rbx
0xe8fe7bb  pop rbp
0xe8fe7bc  pop rdi
0xe8fe7bd  pop rsi
0xe8fe7be  pop r12
0xe8fe7c0  pop r13
0xe8fe7c2  pop r14
0xe8fe7c4  pop r15
0xe8fe7c6  ret
```

### 4.2 Hash table structure (in sub-record 1 at 0x258+0xB0)
| Offset (from holder) | Size | Meaning | Tag |
|----------------------|------|---------|-----|
| +0xA0 | 8 | Bucket array end pointer | [V] 0xe8fe72f |
| +0xB0 | 8 | Bucket array base pointer | [V] 0xe8fe736 |
| +0xC8 | 4 | Bucket mask (bucket_count - 1) | [V] 0xe8fe728 |

**Bucket entry** (16 bytes each at bucket_array + index*16):
| Offset | Size | Meaning | Tag |
|--------|------|---------|-----|
| +0x00 | 8 | Tail pointer (last node) | [V] 0xe8fe78c |
| +0x08 | 8 | Head pointer (first node) | [V] 0xe8fe741 |

**Hash node** (linked list, allocated separately):
| Offset | Size | Meaning | Tag |
|--------|------|---------|-----|
| +0x00 | 8 | Next pointer | [V] 0xe8fe795 |
| +0x08 | 8 | (padding/prev?) | - |
| +0x10 | 8 | Key (FNV-1a 64-bit hash) | [V] 0xe8fe786 |
| +0x18 | 4 | Value low | [V] 0xe8fe7a8 |
| +0x1C | 4 | (padding?) | - |
| +0x20 | 4 | Value high | [V] 0xe8fe7a4 |
| +0x24 | 4 | (padding?) | - |

**Return value**: `node+0x20 - node+0x18` = `value_high - value_low` (likely material index or data offset)

### 4.3 Related lookup variants
- **sub_e8fe7f0** at 0xe8fe7f0 (vtable slot 16): Same algorithm, different lock/register usage (r9d = hash_high, r8 = hash_low passed via stack)
- **sub_e8fe9a0** at 0xe8fe9a0 (vtable slot 17): Insert function - takes key/hash, inserts new node via `sub_eec6de0` (string copy), returns success

### 4.4 Summary: Name->MaterialInfo lookup chain
1. Caller has material name (string) → computes FNV-1a 64-bit hash (or uses precomputed)
2. Calls vtable slot 15 on sub-record 0 of 0x258 object: `sub_c272190(holder, hash)`
3. Thunk loads holder from `this+0x168` → tail-calls `sub_e8fe660(holder, hash)`
4. `sub_e8fe660` locks holder+0x4C, computes bucket = hash & mask (holder+0xC8)
5. Walks chain at bucket_array[bucket] (holder+0xB0) comparing keys at node+0x10
6. On match: returns `node+0x20 - node+0x18` (int index/offset); on miss: returns 0
7. Releases lock, returns to caller

**The name->info lookup is complete.** The 0x258 object's sub-record 1 (+0xB0) is the hash table mapping material name hashes to integer indices/offsets. The actual MaterialInfo objects are likely stored in a parallel array indexed by this return value.

[UNVERIFIED: 0xe8fe9a0 - insert function details; 0xc272190 thunk exact calling convention; MaterialInfo array location not yet found]