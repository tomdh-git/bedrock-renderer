# U-E4-F5: Chunk builder at 0x67762e0 — continuation of U-E4-F4

Unit: U-E4-F5
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation
RVAs: 0x677b05d .. 800 instructions (function ends 0x677e166)
Source: `rdis dis 0x677b05d 40` etc. on Minecraft.Windows.exe 1.26.62.01
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume at 0x677bb27 (Phase 144) — function span: [0x67762e0..0x677e166). Instructions done: 560/800 (Phases 130–143).

## Phase 130 — Cursor store + grow path (0x6760E60) + TLS flag stores + counter not+add [rbp+0x35C] + cursor [r14+8] vs [r14+0x10] (grow loc_677b0fc / push call 0xEEC6EC0) (0x677b05d..0x677b10f)

Stores the incremented cursor from Phase 129's inc path, then either takes the grow path (loc_677b066 → call 0x6760E60) or falls through to TLS reads, a u64 store [rbp+0x300]=0x4002807803, a not+add counter → [rbp+0x35C], another TLS flag store, and a cursor bounds check [r14+8] vs [r14+0x10]: equal → grow loc_677b0fc (call 0x5ABA6D0); else shared_ptr push call 0xEEC6EC0 with r8d=0xC8, then [r14+8]+=0xC8 and jmp loc_677b108. Range ends at 0x677b108 `mov rcx,[0x1233E1B0]` (TLS read continues in next phase); next instruction at 0x677b10f.

```
  677b05d  mov [r14+0x518],rdx                           
  677b064  jmp short 0x677B076                           ; -> loc_677b076
  677b066  mov rcx,r14                                   
  677b069  add rcx,0x510                                 
  677b070  call 0x6760E60                                ; -> sub_6760e60
  677b075  nop                                           

loc_677b076:  ; from 677b064
  677b076  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b07d  mov rax,[rcx]                                 
  677b080  mov rax,[rax+0x10]                            
  677b084  movzx edx,byte ptr [rbp+0x838]                
  677b08b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b091  nop                                           
  677b092  mov rax,0x4002807803                          
  677b09c  mov [rbp+0x300],rax                           
  677b0a3  mov eax,[r14+0x510]                           
  677b0aa  not eax                                       
  677b0ac  add eax,[r14+0x518]                           
  677b0b3  mov [rbp+0x35C],ax                            
  677b0ba  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b0c1  mov rax,[rcx]                                 
  677b0c4  mov rax,[rax+0x10]                            
  677b0c8  mov dl,0x4A                                   
  677b0ca  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b0d0  nop                                           
  677b0d1  mov [rbp+0x838],al                            
  677b0d7  mov rdx,[r14+8]                               
  677b0db  cmp rdx,[r14+0x10]                            
  677b0df  je short 0x677B0FC                            ; -> loc_677b0fc
  677b0e1  mov r8d,0xC8                                  
  677b0e7  mov rcx,rdx                                   
  677b0ea  mov rdx,r13                                   
  677b0ed  call 0xEEC6EC0                                ; -> sub_eec6ec0
  677b0f2  add qword ptr [r14+8],0xC8                    
  677b0fa  jmp short 0x677B108                           ; -> loc_677b108

loc_677b0fc:  ; from 677b0df
  677b0fc  mov rcx,r14                                   
  677b0ff  mov r8,r13                                    
  677b102  call 0x5ABA6D0                                ; -> sub_5aba6d0
  677b107  nop                                           

loc_677b108:  ; from 677b0fa
  677b108  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
```

Interpretation: `mov [r14+0x518],rdx` — stores the incremented cursor produced by Phase 129's `inc rdx` path, then `jmp short loc_677b076`. loc_677b066 (the grow target of Phase 129's `je loc_677b066`): `mov rcx,r14`, `add rcx,0x510`, call 0x6760E60 (grow helper), `nop`. loc_677b076: TLS read `rcx=[0x1233E1B0]`, `rax=[rcx]`, `rax=[rax+0x10]`, `movzx edx,byte [rbp+0x838]`, call via [0xF99FFA0]. Then `mov rax,0x4002807803`; `[rbp+0x300]=rax` (u64 state tag). Counter: `eax=[r14+0x510]`, `not eax`, `add eax,[r14+0x518]`, `[rbp+0x35C]=ax`. Second TLS read; `mov dl,0x4A`; call via [0xF99FFA0]; `[rbp+0x838]=al`. Cursor bounds check: `rdx=[r14+8]`; `cmp [r14+0x10]`; if equal jump to loc_677b0fc (grow path: `mov rcx,r14`, `mov r8,r13`, call 0x5ABA6D0). Otherwise `r8d=0xC8`, `rcx=rdx`, `rdx=r13`, call 0xEEC6EC0 (shared_ptr push, same shape as Phase 118/121), `add qword ptr [r14+8],0xC8`, `jmp short loc_677b108`. loc_677b108: `mov rcx,[0x1233E1B0]` — TLS read continues into next phase. Range ends there; next instruction at 0x677b10f.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0x5ABA6D0 (sub_5aba6d0, grow target via je), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [r14+0x518], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838] (x2), [r14+0x510], [r14+8], [r14+0x10], r13. Fields written: [r14+0x518], [rbp+0x300], [rbp+0x35C], [rbp+0x838] (x2), [r14+8].

## Phase 131 — TLS tail (mov rax,[rcx]/[rax+0x10] + flag call) + call 0x67E1660 x2 + cmp byte [rbp+0x80],3 (je sub_677deae / jmp sub_677def0) + call 0x678CF10 + call 0x678F640 + copy block tail [rbp+0x3E0]→[rbp+0x250] + [rbx+0xA7/0x98/0x88] + movzx word [rbp+0x490] (0x677b10f..0x677b1e3)

Completes the TLS read opened at 0x677b108 (Phase 130), calls 0x67E1660 twice (rcx=r12, then rcx=&[rbp+0x110]), then `cmp byte [rbp+0x80],3` (je sub_677deae / jmp sub_677def0 — same branch pair as Phase 117, entered here via those earlier jumps). Fall-through block at 0x677b14e: call 0x678CF10(rcx=&[rbp+0x2C0], rdx=r13), then call 0x678F640(rcx=r12, rdx=&[rbp+0x3E0], r8=&[rbp+0x388], r9=r13). Copy-block tail mirrors Phase 118's tail: eax=[r14+0x68]; [rbp+0x250+0x10]=eax; [rbp+0x250]=16 bytes from [r14+0x58]; byte [rbp+0x44C]→[rbp+0x264]; [rbp+0x450]→[rbp+0x268]; [r14+0x80],[r14+0x90],[r14+0x9F]→[rbx+0xA7],[rbx+0x98],[rbx+0x88]; ends `movzx eax,word [rbp+0x490]`; next instruction 0x677b1e3.

```
  677b10f  mov rax,[rcx]                                 ; R a0+0x0
  677b112  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  677b116  movzx edx,byte ptr [rbp+0x838]                
  677b11d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b123  nop                                           
  677b124  mov rcx,r12                                   
  677b127  call 0x67E1660                                ; -> sub_67e1660
  677b12c  nop [rax]                                     ; R ret@67e1660+0x0
  677b130  lea rcx,[rbp+0x110]                           
  677b137  call 0x67E1660                                ; -> sub_67e1660
  677b13c  cmp byte ptr [rbp+0x80],3                     
  677b143  je 0x677DEAE                                  ; -> sub_677deae
  677b149  jmp 0x677DEF0                                 ; -> sub_677def0
  677b14e  lea rcx,[rbp+0x2C0]                           
  677b155  mov rdx,r13                                   
  677b158  call 0x678CF10                                ; -> sub_678cf10
  677b15d  nop                                           
  677b15e  lea rcx,[rbp+0x110]                           
  677b165  lea r14,[rbp+0x3E0]                           
  677b16c  mov rdx,r14                                   
  677b16f  lea r8,[rbp+0x388]                            
  677b176  mov r9,r13                                    
  677b179  call 0x678F640                                ; -> sub_678f640
  677b17e  nop                                           
  677b17f  mov eax,[r14+0x68]                            
  677b183  lea rcx,[rbp+0x250]                           
  677b18a  mov [rcx+0x10],eax                            
  677b18d  movups xmm0,[r14+0x58]                        
  677b192  movups [rcx],xmm0                             
  677b195  movzx eax,byte ptr [rbp+0x44C]                
  677b19c  mov [rbp+0x264],al                            
  677b1a2  movups xmm0,[rbp+0x450]                       
  677b1a9  movups [rbp+0x268],xmm0                       
  677b1b0  movups xmm0,[r14+0x80]                        
  677b1b8  movups xmm1,[r14+0x90]                        
  677b1c0  movups xmm2,[r14+0x9F]                        
  677b1c8  movups [rbx+0xA7],xmm2                        
  677b1cf  movups [rbx+0x98],xmm1                        
  677b1d6  movups [rbx+0x88],xmm0                        
  677b1dd  movzx eax,word ptr [rbp+0x490]                
```

Interpretation: `mov rax,[rcx]`; `mov rax,[rax+0x10]` completes the TLS slot read (rcx was [0x1233E1B0] at 0x677b108); `movzx edx,byte [rbp+0x838]`; call via [0xF99FFA0]; `nop`. `mov rcx,r12`; call 0x67E1660; `nop [rax]`. `lea rcx,[rbp+0x110]`; call 0x67E1660. `cmp byte ptr [rbp+0x80],3`; `je 0x677DEAE` (sub_677deae); `jmp 0x677DEF0` (sub_677def0) — identical branch pair to Phase 117's `cmp byte [rbp+0x80],3` at 0x677a631. Fall-through at 0x677b14e (landing pad): `lea rcx,[rbp+0x2C0]`; `mov rdx,r13`; call 0x678CF10; `nop`; `lea rcx,[rbp+0x110]`; `lea r14,[rbp+0x3E0]`; `mov rdx,r14`; `lea r8,[rbp+0x388]`; `mov r9,r13`; call 0x678F640; `nop`. Copy tail: `mov eax,[r14+0x68]` ([rbp+0x3E0+0x68]); `lea rcx,[rbp+0x250]`; `mov [rcx+0x10],eax` ([rbp+0x250+0x10]); `movups xmm0,[r14+0x58]`; `movups [rcx],xmm0` ([rbp+0x250], 16 bytes); `movzx eax,byte [rbp+0x44C]`; `mov [rbp+0x264],al`; `movups xmm0,[rbp+0x450]`; `movups [rbp+0x268],xmm0`; `movups xmm0,[r14+0x80]`; `movups xmm1,[r14+0x90]`; `movups xmm2,[r14+0x9F]`; `movups [rbx+0xA7],xmm2`; `movups [rbx+0x98],xmm1`; `movups [rbx+0x88],xmm0`; `movzx eax,word [rbp+0x490]`; range ends there; next instruction at 0x677b1e3 (continues Phase 118's `mov [rbp+0x2A8],ax` pattern).

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x67E1660 (sub_67e1660, 2x), sub_677deae (via je), sub_677def0 (via jmp), 0x678CF10 (sub_678cf10), 0x678F640 (sub_678f640).
Fields read: [rcx] (= [[0x1233E1B0]]), [rax+0x10], [rbp+0x838], r12, [rbp+0x110] (lea addr), [rbp+0x80], [rbp+0x2C0] (lea addr), r13, [rbp+0x110] (2nd lea), [rbp+0x3E0] (r14), [[rbp+0x3E0]+0x68], [rbp+0x250] (lea addr), [[rbp+0x3E0]+0x58], [rbp+0x44C], [rbp+0x450], [[rbp+0x3E0]+0x80], [[rbp+0x3E0]+0x90], [[rbp+0x3E0]+0x9F], rbx. Fields written: [rbp+0x838], [rbp+0x250] (via [rcx+0x10] and [rcx]), [rbp+0x264], [rbp+0x268], [rbx+0xA7], [rbx+0x98], [rbx+0x88], eax (movzx).

## Phase 132 — Weird opens ([?]) + block size/16 magic-mul + call 0x6769EE0 + range begin/end store + virtual call [rax+0x48] setup (0x677b1e3..0x677b2ae)

Opens with two unusual instructions (`add [rsi-0x77],ah`, `test [rax+0x48000002],ebp`) whose meaning is unclear ([?] — possibly embedded data or real code with odd addressing). Then the same size-math pattern as Phase 119: eax=[rbp+0x768]; r8=[rax+0x480] (begin); rax=[rax+0x488] (end); rdx=rax-r8 (size); cmp rdx,0xFFFFFFFFFFFFFFD0 (-48) → je sub_677e011; test r8,r8/setne cl; test rax,rax/sete r9b; or r9b,cl → je sub_677e011 if either pointer null; cmp rax,r8 → je sub_677d8a9 (sub_677d8a9 — different target than Phase 119's loc_677bd29); mov rax,[rbp+0x778]; cmp qword ptr [rax],0 → je sub_677d8a9 if null; sar rdx,4; mov rax,0xAAAAAAAAAAAAAAAB; imul rdx,rax (magic-mul size/16); mov dword ptr [rsp+0x20],0x41800000; lea rcx,[rbp+0x800]; lea r9,[rbp+0x2E0]; call 0x6769EE0 (rdx=index, rcx=&[rbp+0x800], r9=&[rbp+0x2E0]); mov rax,[rbp+0x800]; mov rcx,[rbp+0x808]; mov r14,rax; [rbp+0x838]=rax; [rbp+0x568]=rcx (range begin/end stored); cmp rax,rcx → je sub_677d816 (sub_677d816 — different target than Phase 119's loc_677bc96); mov rax,[rbp+0x778]; mov rcx,[rax]; mov rax,[rcx]; mov rax,[rax+0x48] (vtable+0x48); lea rdx,[rbp+0x4A0] — virtual call setup continues next phase. Range ends at `lea rdx,[rbp+0x4A0]`; next instruction 0x677b2ae (expected `call qword ptr [0xF99FFA0]`).

```
  677b1e3  add [rsi-0x77],ah                             
  677b1e6  test [rax+0x48000002],ebp                     
  677b1ec  mov eax,[rbp+0x768]                           
  677b1f2  mov r8,[rax+0x480]                            
  677b1f9  mov rax,[rax+0x488]                           
  677b200  mov rdx,rax                                   
  677b203  sub rdx,r8                                    
  677b206  cmp rdx,0xFFFFFFFFFFFFFFD0                    
  677b20a  je 0x677E011                                  ; -> sub_677e011
  677b210  test r8,r8                                    
  677b213  setne cl                                      
  677b216  test rax,rax                                  
  677b219  sete r9b                                      
  677b21d  or r9b,cl                                     
  677b220  je 0x677E011                                  ; -> sub_677e011
  677b226  cmp rax,r8                                    
  677b229  je 0x677D8A9                                  ; -> sub_677d8a9
  677b22f  mov rax,[rbp+0x778]                           
  677b236  cmp qword ptr [rax],0                         
  677b23a  je 0x677D8A9                                  ; -> sub_677d8a9
  677b240  sar rdx,4                                     
  677b244  mov rax,0xAAAAAAAAAAAAAAAB                    
  677b24e  imul rdx,rax                                  
  677b252  mov dword ptr [rsp+0x20],0x41800000           
  677b25a  lea rcx,[rbp+0x800]                           
  677b261  lea r9,[rbp+0x2E0]                            
  677b268  call 0x6769EE0                                ; -> sub_6769ee0
  677b26d  nop                                           
  677b26e  mov rax,[rbp+0x800]                           
  677b275  mov rcx,[rbp+0x808]                           
  677b27c  mov r14,rax                                   
  677b27f  mov [rbp+0x838],rax                           
  677b286  mov [rbp+0x568],rcx                           
  677b28d  cmp rax,rcx                                   
  677b290  je 0x677D816                                  ; -> sub_677d816
  677b296  mov rax,[rbp+0x778]                           
  677b29d  mov rcx,[rax]                                 
  677b2a0  mov rax,[rcx]                                 
  677b2a3  mov rax,[rax+0x48]                            
  677b2a7  lea rdx,[rbp+0x4A0]                           
```

Interpretation: `add [rsi-0x77],ah`; `test [rax+0x48000002],ebp` — unusual instructions at phase start ([?]). Then `mov eax,[rbp+0x768]`; `mov r8,[rax+0x480]`; `mov rax,[rax+0x488]`; `mov rdx,rax`; `sub rdx,r8` (size = end - begin); `cmp rdx,0xFFFFFFFFFFFFFFD0`; `je sub_677e011`; `test r8,r8`; `setne cl`; `test rax,rax`; `sete r9b`; `or r9b,cl`; `je sub_677e011` if either pointer is null; `cmp rax,r8`; `je sub_677d8a9` if empty range; `mov rax,[rbp+0x778]`; `cmp qword ptr [rax],0`; `je sub_677d8a9` if vtable object null; `sar rdx,4`; `mov rax,0xAAAAAAAAAAAAAAAB`; `imul rdx,rax` (count = size/16 via magic multiply); `mov dword ptr [rsp+0x20],0x41800000`; `lea rcx,[rbp+0x800]`; `lea r9,[rbp+0x2E0]`; call 0x6769EE0; `nop`; `mov rax,[rbp+0x800]`; `mov rcx,[rbp+0x808]`; `mov r14,rax`; `[rbp+0x838]=rax`; `[rbp+0x568]=rcx`; `cmp rax,rcx`; `je sub_677d816` if range empty after call; `mov rax,[rbp+0x778]`; `mov rcx,[rax]`; `mov rax,[rcx]`; `mov rax,[rax+0x48]` (vtable+0x48); `lea rdx,[rbp+0x4A0]`. Range ends there; next instruction at 0x677b2ae (expected virtual call via [0xF99FFA0]).

Callees: sub_677e011 (via je x2), sub_677d8a9 (via je x2), 0x6769EE0 (sub_6769ee0), sub_677d816 (via je).
Fields read: [rbp+0x768], [[rbp+0x768]+0x480], [[rbp+0x768]+0x488], [rbp+0x778], [[rbp+0x778]] (vtable ptr), [rcx] (= [[rbp+0x778]]->vtable), [rax+0x48] (vtable+0x48), [rbp+0x4A0] (lea addr), [rbp+0x800], [rbp+0x808], [rsp+0x20] (addr only). Fields written: [rsp+0x20], [rbp+0x838], [rbp+0x568], r14.

## Phase 133 — Virtual call [rax+0x48] tail + range guards (je sub_677e011 x3) + [rbp+0x7C0/0x7C8] setup + 0x20-step loop call 0x676A670 (loc_677b320) + [rbp+0x780/0x788] setup (0x677b2ae..0x677b362)

Completes the virtual call from Phase 132: `call qword ptr [0xF99FFA0]`; `nop`. Then r14=[rbp+0x800] (begin), r15=[rbp+0x808] (end); rax=r15-r14; guards: size != 0xFFFFFFE0 (-32), both pointers non-null, end > start — each failure je sub_677e011. Setup: [rbp+0x7C0]=&[rbp+0x7D0]; [rbp+0x7C8]=0x100000000 (u64 4294967296). If begin==end jump to loc_677b33c; else loop loc_677b320: lea rcx,[rbp+0x7C0]; mov rdx,r12; mov r8,r14; call 0x676A670; add r14,0x20; cmp r14,r15; jne loc_677b320. loc_677b33c: lea rax,[rbp+0x790]; [rbp+0x780]=rax (&[rbp+0x790]); mov rax,0x100000000; [rbp+0x788]=rax; lea r14,[rbp+0x780] (&[rbp+0x780] — mirrors Phase 121's loop setup, continues next phase). Range ends at `lea r14,[rbp+0x780]`; next instruction 0x677b362.

```
  677b2ae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b2b4  nop                                           
  677b2b5  mov r14,[rbp+0x800]                           
  677b2bc  mov r15,[rbp+0x808]                           
  677b2c3  mov rax,r15                                   
  677b2c6  sub rax,r14                                   
  677b2c9  cmp rax,0xFFFFFFFFFFFFFFE0                    
  677b2cd  je 0x677E011                                  ; -> sub_677e011
  677b2d3  test r14,r14                                  
  677b2d6  setne al                                      
  677b2d9  test r15,r15                                  
  677b2dc  sete cl                                       
  677b2df  or cl,al                                      
  677b2e1  je 0x677E011                                  ; -> sub_677e011
  677b2e7  test r14,r14                                  
  677b2ea  setne al                                      
  677b2ed  cmp r15,r14                                   
  677b2f0  sete cl                                       
  677b2f3  or cl,al                                      
  677b2f5  je 0x677E011                                  ; -> sub_677e011
  677b2fb  lea rax,[rbp+0x7D0]                           
  677b302  mov [rbp+0x7C0],rax                           
  677b309  mov rax,0x100000000                           
  677b313  mov [rbp+0x7C8],rax                           
  677b31a  cmp r15,r14                                   
  677b31d  je short 0x677B33C                            ; -> loc_677b33c
  677b31f  nop                                           

loc_677b320:  ; from 677b33a
  677b320  lea rcx,[rbp+0x7C0]                           
  677b327  mov rdx,r12                                   
  677b32a  mov r8,r14                                    
  677b32d  call 0x676A670                                ; -> sub_676a670
  677b332  nop                                           
  677b333  add r14,0x20                                  
  677b337  cmp r14,r15                                   
  677b33a  jne short 0x677B320                           ; -> loc_677b320

loc_677b33c:  ; from 677b31d
  677b33c  lea rax,[rbp+0x790]                           
  677b343  mov [rbp+0x780],rax                           
  677b34a  mov rax,0x100000000                           
  677b354  mov [rbp+0x788],rax                           
  677b35b  lea r14,[rbp+0x780]                           
```

Interpretation: `call qword ptr [0xF99FFA0]` — virtual call via vtable+0x48 (rcx=[rbp+0x778]'s vtable, rdx=&[rbp+0x4A0] set in Phase 132). `nop`. `mov r14,[rbp+0x800]`; `mov r15,[rbp+0x808]`; `rax=r15-r14`; `cmp rax,0xFFFFFFFFFFFFFFE0` (-32); `je sub_677e011`; `test r14,r14`; `setne al`; `test r15,r15`; `sete cl`; `or cl,al`; `je sub_677e011` if either pointer null; `test r14,r14`; `setne al`; `cmp r15,r14`; `sete cl` (end > start unsigned); `or cl,al`; `je sub_677e011` if not. `lea rax,[rbp+0x7D0]`; `[rbp+0x7C0]=rax` (pointer to local); `mov rax,0x100000000`; `[rbp+0x7C8]=rax`. `cmp r15,r14`; if equal `je loc_677b33c` (skip loop). `nop`. loc_677b320: `lea rcx,[rbp+0x7C0]`; `mov rdx,r12`; `mov r8,r14`; call 0x676A670; `nop`; `add r14,0x20`; `cmp r14,r15`; `jne loc_677b320`. loc_677b33c: `lea rax,[rbp+0x790]`; `[rbp+0x780]=rax`; `mov rax,0x100000000`; `[rbp+0x788]=rax`; `lea r14,[rbp+0x780]` (&[rbp+0x780] as rcx arg for next call). Range ends there; next instruction at 0x677b362 (expected `mov rcx,r14; lea rdx,[rbp+0x7C0]; call 0x6764990`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect), sub_677e011 (via je x3), loc_677b33c (via je), loc_677b320 (loop back-edge via jne), 0x676A670 (sub_676a670).
Fields read: [rbp+0x800], [rbp+0x808], r14, r15, [rbp+0x7D0] (lea addr), r15/r14 (loop). Fields written: [rbp+0x7C0], [rbp+0x7C8], [rbp+0x780], [rbp+0x788], r14 (loop induction), r15.

## Phase 134 — call 0x6764990 + call 0x6792160 (differs from Phase 121's 0x6792570) + copy block [rbp+0x250]→[rbp+0x6E8], [rbx+0x88/0x98/0xA7]→[rbp+0x574+0x1BB/0x1AC/0x19C] + word [rbp+0x2A8]→[rbp+0x740] + call 0x5ABA5C0 + movaps zero slots start (0x677b362..0x677b43a)

Mirrors Phase 121/122's head: `mov rcx,r14` (&[rbp+0x780] from Phase 133); `lea rdx,[rbp+0x7C0]`; call 0x6764990; `mov [rsp+0x20],r14`. Then `mov rcx,r12`; `lea rdx,[rbp+0x1F8]`; `lea r8,[rbp+0x1A0]`; `lea r9,[rbp+0x118]`; call 0x6792160 (note: Phase 121 called 0x6792570 here — different callee). Copy block: `lea rcx,[rbp+0x250]`; `mov eax,[rcx+0x10]` ([rbp+0x250+0x10]); `lea rdx,[rbp+0x6E8]`; `[rdx+0x10]=eax` ([rbp+0x6E8+0x10] — Phase 121 used [rbp+0x6F0]); `movups xmm0,[rcx]` ([rbp+0x250]); `movups [rdx],xmm0` ([rbp+0x6E8], 16 bytes); `movzx eax,byte [rbp+0x264]`; `[rbp+0x6FC]=al` (Phase 121: [rbp+0x704]); `movups xmm0,[rbp+0x268]`; `[rbp+0x700]=xmm0` (Phase 121: [rbp+0x708]); `movups xmm0,[rbx+0x88]`; `movups xmm1,[rbx+0x98]`; `movups xmm2,[rbx+0xA7]`; `lea rax,[rbp+0x574]`; `[rax+0x1BB]=xmm2` ([rbp+0x574+0x1BB] — Phase 121: 0x1C3); `[rax+0x1AC]=xmm1` ([rbp+0x574+0x1AC] — Phase 121: 0x1B4); `[rax+0x19C]=xmm0` ([rbp+0x574+0x19C] — Phase 121: 0x1A4); `movzx eax,word [rbp+0x2A8]`; `[rbp+0x740]=ax` (Phase 121: [rbp+0x748]). Then `mov rax,[rbp+0x828]`; `mov rcx,[rax+0x10]`; `mov eax,0x9D0`; `add rcx,rax`; call 0x5ABA5C0; `nop`; `mov r14,rax`; then zeroing: `movaps [rbp+0x550],xmm6`; `movaps [rbp+0x540],xmm6`; `movaps [rbp+0x530],xmm6`; phase ends there; next instruction 0x677b43a.

```
  677b362  mov rcx,r14                                   
  677b365  lea rdx,[rbp+0x7C0]                           
  677b36c  call 0x6764990                                ; -> sub_6764990
  677b371  nop                                           
  677b372  mov [rsp+0x20],r14                            
  677b377  mov rcx,r12                                   
  677b37a  lea rdx,[rbp+0x1F8]                           
  677b381  lea r8,[rbp+0x1A0]                            
  677b388  lea r9,[rbp+0x118]                            
  677b38f  call 0x6792160                                ; -> sub_6792160
  677b394  nop                                           
  677b395  lea rcx,[rbp+0x250]                           
  677b39c  mov eax,[rcx+0x10]                            
  677b39f  lea rdx,[rbp+0x6E8]                           
  677b3a6  mov [rdx+0x10],eax                            
  677b3a9  movups xmm0,[rcx]                             
  677b3ac  movups [rdx],xmm0                             
  677b3af  movzx eax,byte ptr [rbp+0x264]                
  677b3b6  mov [rbp+0x6FC],al                            
  677b3bc  movups xmm0,[rbp+0x268]                       
  677b3c3  movups [rbp+0x700],xmm0                       
  677b3ca  movups xmm0,[rbx+0x88]                        
  677b3d1  movups xmm1,[rbx+0x98]                        
  677b3d8  movups xmm2,[rbx+0xA7]                        
  677b3df  lea rax,[rbp+0x574]                           
  677b3e6  movups [rax+0x1BB],xmm2                       
  677b3ed  movups [rax+0x1AC],xmm1                       
  677b3f4  movups [rax+0x19C],xmm0                       
  677b3fb  movzx eax,word ptr [rbp+0x2A8]                
  677b402  mov [rbp+0x740],ax                            
  677b409  mov rax,[rbp+0x828]                           
  677b410  mov rcx,[rax+0x10]                            
  677b414  mov eax,0x9D0                                 
  677b419  add rcx,rax                                   
  677b41c  call 0x5ABA5C0                                ; -> sub_5aba5c0
  677b421  nop                                           
  677b422  mov r14,rax                                   
  677b425  movaps [rbp+0x550],xmm6                       
  677b42c  movaps [rbp+0x540],xmm6                       
  677b433  movaps [rbp+0x530],xmm6                       
```

Interpretation: `mov rcx,r14`; `lea rdx,[rbp+0x7C0]`; call 0x6764990 (rcx=&[rbp+0x780], rdx=&[rbp+0x7C0]). `nop`. `[rsp+0x20]=r14` (spill). `mov rcx,r12`; `lea rdx,[rbp+0x1F8]`; `lea r8,[rbp+0x1A0]`; `lea r9,[rbp+0x118]`; call 0x6792160 (4-arg; note Phase 121's equivalent call was 0x6792570 — distinct callee). Copy sequence: `lea rcx,[rbp+0x250]`; `mov eax,[rcx+0x10]`; `lea rdx,[rbp+0x6E8]`; `[rdx+0x10]=eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0`; `movzx eax,byte [rbp+0x264]`; `[rbp+0x6FC]=al`; `movups xmm0,[rbp+0x268]`; `[rbp+0x700]=xmm0`; `movups xmm0,[rbx+0x88]`; `movups xmm1,[rbx+0x98]`; `movups xmm2,[rbx+0xA7]`; `lea rax,[rbp+0x574]`; `[rax+0x1BB]=xmm2`; `[rax+0x1AC]=xmm1`; `[rax+0x19C]=xmm0`; `movzx eax,word [rbp+0x2A8]`; `[rbp+0x740]=ax`. `mov rax,[rbp+0x828]`; `mov rcx,[rax+0x10]`; `mov eax,0x9D0`; `add rcx,rax`; call 0x5ABA5C0; `nop`; `mov r14,rax` (result→r14 for zeroing). Zeroing: `movaps [rbp+0x550],xmm6`; `movaps [rbp+0x540],xmm6`; `movaps [rbp+0x530],xmm6` (xmm6 presumed zero; continues next phase). Range ends there; next instruction at 0x677b43a.

Callees: 0x6764990 (sub_6764990), 0x6792160 (sub_6792160), 0x5ABA5C0 (sub_5aba5c0).
Fields read: r14 (&[rbp+0x780]), [rbp+0x7C0] (addr), r12, [rbp+0x1F8], [rbp+0x1A0], [rbp+0x118] (addrs only), [rbp+0x250], [[rbp+0x250]+0x10], [rbp+0x264], [rbp+0x268], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x574] (addr), [rbp+0x2A8], [rbp+0x828], [[rbp+0x828]+0x10], xmm6 (zero source). Fields written: [rsp+0x20], [rbp+0x6E8], [[rbp+0x6E8]+0x10], [rbp+0x6FC], [rbp+0x700], [[rbp+0x574]+0x1BB], [[rbp+0x574]+0x1AC], [[rbp+0x574]+0x19C], [rbp+0x740], r14 (call result), [rbp+0x550], [rbp+0x540], [rbp+0x530].

## Phase 135 — Zero slots tail [rbp+0x520..0x4A0] + [rbp+0x560]=0 + TLS flag [rbp+0x847]=al + cursor u16 write [rbp+0x740]→[r14+0x8A8] (grow loc_677c49a) + call 0x1EF6F90 + TLS + counter shr1/dec [rbp+0x4B0] + TLS read continues (0x677b43a..0x677b51c)

Finishes the zeroing loop from Phase 134: movaps [rbp+0x520],xmm6; [rbp+0x510]; [rbp+0x500]; [rbp+0x4F0]; [rbp+0x4E0]; [rbp+0x4D0]; [rbp+0x4C0]; [rbp+0x4B0]; [rbp+0x4A0] (9 slots), then `mov qword ptr [rbp+0x560],0`. TLS read: rcx=[0x1233E1B0]→[rax]→[rax+0x10], mov dl,0x4A, call via [0xF99FFA0]; `[rbp+0x847]=al` (Phase 124 used [rbp+0x838]). Cursor bounds check: rdx=[r14+0x8A8]; cmp [r14+0x8B0]; if equal jump to loc_677c49a (grow: lea rcx,[r14+0x8A0], lea r8,[rbp+0x748], call 0x1EF6F90). Else movzx eax,word [rbp+0x740] (Phase 124 used [rbp+0x748]); [rdx]=ax (u16 write at cursor); [r14+0x8A8]+=2; jmp loc_677c4ae. loc_677c4ae: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x847], call via [0xF99FFA0]; counter: eax=[r14+0x8A8], sub [r14+0x8A0], shr 1, dec, `[rbp+0x4B0]=ax` (Phase 124: [rbp+0x310]); TLS read continues: `mov rcx,[0x1233E1B0]`; range ends there; next instruction 0x677b51c.

```
  677b43a  movaps [rbp+0x520],xmm6                       
  677b441  movaps [rbp+0x510],xmm6                       
  677b448  movaps [rbp+0x500],xmm6                       
  677b44f  movaps [rbp+0x4F0],xmm6                       
  677b456  movaps [rbp+0x4E0],xmm6                       
  677b45d  movaps [rbp+0x4D0],xmm6                       
  677b464  movaps [rbp+0x4C0],xmm6                       
  677b46b  movaps [rbp+0x4B0],xmm6                       
  677b472  movaps [rbp+0x4A0],xmm6                       
  677b479  mov qword ptr [rbp+0x560],0                   
  677b484  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b48b  mov rax,[rcx]                                 
  677b48e  mov rax,[rax+0x10]                            
  677b492  mov dl,0x4A                                   
  677b494  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b49a  nop                                           
  677b49b  mov [rbp+0x847],al                            
  677b4a1  mov rdx,[r14+0x8A8]                           
  677b4a8  cmp rdx,[r14+0x8B0]                           
  677b4af  je 0x677C49A                                  ; -> loc_677c49a
  677b4b5  movzx eax,word ptr [rbp+0x740]                
  677b4bc  mov [rdx],ax                                  
  677b4bf  add qword ptr [r14+0x8A8],2                   
  677b4c7  jmp 0x677C4AE                                 ; -> loc_677c4ae
  677b4cc  lea rcx,[r14+0x8A0]                           
  677b4d3  lea r8,[rbp+0x748]                            
  677b4da  call 0x1EF6F90                                ; -> sub_1ef6f90
  677b4df  nop                                           
  677b4e0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b4e7  mov rax,[rcx]                                 
  677b4ea  mov rax,[rax+0x10]                            
  677b4ee  movzx edx,byte ptr [rbp+0x847]                
  677b4f5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b4fb  nop                                           
  677b4fc  mov eax,[r14+0x8A8]                           
  677b503  sub eax,[r14+0x8A0]                           
  677b50a  shr eax,1                                     
  677b50c  dec eax                                       
  677b50e  mov [rbp+0x4B0],ax                            
  677b515  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```

Interpretation: completes zeroing of 12 slots total ([rbp+0x550]..[rbp+0x4A0] across Phases 134-135), then [rbp+0x560]=0. TLS feature flag → [rbp+0x847]. Cursor check [r14+0x8A8] vs [r14+0x8B0]: full → grow loc_677c49a (call 0x1EF6F90 with rcx=[r14+0x8A0], r8=[rbp+0x748]); else u16 write [rbp+0x740]→[r14+0x8A8], [r14+0x8A8]+=2, jmp loc_677c4ae. loc_677c4ae: TLS flag call, [rbp+0x847]=al (re-read at 677b4ee), counter (([r14+0x8A8]-[r14+0x8A0])>>1 - 1) → [rbp+0x4B0]=ax, then TLS read `mov rcx,[0x1233E1B0]` continues next phase.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0x1EF6F90 (sub_1ef6f90, grow via je), loc_677c4ae (via jmp).
Fields read: xmm6, [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x847] (x2), [r14+0x8A8], [r14+0x8B0], [rbp+0x740], [r14+0x8A0], r14. Fields written: [rbp+0x520], [rbp+0x510], [rbp+0x500], [rbp+0x4F0], [rbp+0x4E0], [rbp+0x4D0], [rbp+0x4C0], [rbp+0x4B0], [rbp+0x4A0] (movaps x9), [rbp+0x560], [rbp+0x847] (x2), [r14+0x8A8] (u16 write via [rdx]), [r14+0x8A8] (add 2), [rbp+0x4B0].

## Phase 136 — TLS tail (mov rax,[rcx]/[rax+0x10] + flag store [rbp+0x847]) + cursor record append at [r14+0x758] ([rbp+0x6F0] source: dword+byte+4 floats+3 movups) (grow loc_677b5c9 → 0x6760A80) + [r14+0x758]+=0x58 + jmp loc_677b5dd + TLS read continues (0x677b51c..0x677b5ea)

Completes Phase 135's TLS read: `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `mov dl,0x4A`; call via [0xF99FFA0]; `nop`; `[rbp+0x847]=al`. Cursor bounds check: rdx=[r14+0x758]; cmp [r14+0x760]; if equal jump to loc_677b5c9 (grow: `lea rcx,[r14+0x750]`, `lea r8,[rbp+0x6F0]`, call 0x6760A80). Else append record: `lea rcx,[rbp+0x6F0]`; `eax=[rcx+0x10]` ([rbp+0x6F0+0x10]); `[rdx+0x10]=eax` ([r14+0x758+0x10]); `movups xmm0,[rcx]` ([rbp+0x6F0]); `movups [rdx],xmm0` ([r14+0x758], 16 bytes); `movzx eax,byte [rbp+0x704]`; `[rdx+0x14]=al` ([r14+0x758+0x14]); `movss [rdx+0x18]=[rbp+0x708]`; `[rdx+0x1C]=[rbp+0x70C]`; `[rdx+0x20]=[rbp+0x710]`; `[rdx+0x24]=[rbp+0x714]`; then from [rbp+0x574]: `xmm0=[rbp+0x574+0x1A4]`, `xmm1=[rbp+0x574+0x1B4]`, `xmm2=[rbp+0x574+0x1C3]`; `[rdx+0x28]=xmm0`, `[rdx+0x38]=xmm1`, `[rdx+0x47]=xmm2`; `add qword ptr [r14+0x758],0x58`; `jmp short loc_677b5dd`. loc_677b5dd: TLS read `mov rcx,[0x1233E1B0]`; `mov rax,[rcx]`; `mov rax,[rax+0x10]`; range ends there; next instruction 0x677b5ea.

```
  677b51c  mov rax,[rcx]                                 ; R a0+0x0
  677b51f  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  677b523  mov dl,0x4A                                   
  677b525  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b52b  nop                                           
  677b52c  mov [rbp+0x847],al                            
  677b532  mov rdx,[r14+0x758]                           
  677b539  cmp rdx,[r14+0x760]                           
  677b540  je 0x677B5C9                                  ; -> loc_677b5c9
  677b546  lea rcx,[rbp+0x6F0]                           
  677b54d  mov eax,[rcx+0x10]                            
  677b550  mov [rdx+0x10],eax                            
  677b553  movups xmm0,[rcx]                             
  677b556  movups [rdx],xmm0                             
  677b559  movzx eax,byte ptr [rbp+0x704]                
  677b560  mov [rdx+0x14],al                             
  677b563  movss xmm0,[rbp+0x708]                        
  677b56b  movss [rdx+0x18],xmm0                         
  677b570  movss xmm0,[rbp+0x70C]                        
  677b578  movss [rdx+0x1C],xmm0                         
  677b57d  movss xmm0,[rbp+0x710]                        
  677b585  movss [rdx+0x20],xmm0                         
  677b58a  movss xmm0,[rbp+0x714]                        
  677b592  movss [rdx+0x24],xmm0                         
  677b597  lea rax,[rbp+0x574]                           
  677b59e  movups xmm0,[rax+0x1A4]                       
  677b5a5  movups xmm1,[rax+0x1B4]                       
  677b5ac  movups xmm2,[rax+0x1C3]                       
  677b5b3  movups [rdx+0x28],xmm0                        
  677b5b7  movups [rdx+0x38],xmm1                        
  677b5bb  movups [rdx+0x47],xmm2                        
  677b5bf  add qword ptr [r14+0x758],0x58                
  677b5c7  jmp short 0x677B5DD                           ; -> loc_677b5dd

loc_677b5c9:  ; from 677b540
  677b5c9  lea rcx,[r14+0x750]                           
  677b5d0  lea r8,[rbp+0x6F0]                            
  677b5d7  call 0x6760A80                                ; -> sub_6760a80
  677b5dc  nop                                           

loc_677b5dd:  ; from 677b5c7
  677b5dd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b5e4  mov rax,[rcx]                                 
  677b5e7  mov rax,[rax+0x10]                            ; next instruction 0x677b5ea
```

Interpretation: `mov rax,[rcx]`; `mov rax,[rax+0x10]` completes the TLS slot read (rcx=[0x1233E1B0] from Phase 135's end); `mov dl,0x4A`; call via [0xF99FFA0]; `nop`; `[rbp+0x847]=al` (flag store). Cursor record append at rdx=[r14+0x758] vs end [r14+0x760]: full → grow loc_677b5c9 (`lea rcx,[r14+0x750]`, `lea r8,[rbp+0x6F0]`, call 0x6760A80 — same grow helper as Phase 125). Else store record at cursor: dword [rbp+0x6F0+0x10]→[rdx+0x10], 16 bytes [rbp+0x6F0]→[rdx], byte [rbp+0x704]→[rdx+0x14], floats [rbp+0x708],[rbp+0x70C],[rbp+0x710],[rbp+0x714]→[rdx+0x18..0x24], then [rbp+0x574+0x1A4],[rbp+0x574+0x1B4],[rbp+0x574+0x1C3]→[rdx+0x28],[rdx+0x38],[rdx+0x47]; advance cursor [r14+0x758]+=0x58; jmp loc_677b5dd. loc_677b5dd: TLS read `mov rcx,[0x1233E1B0]`, `mov rax,[rcx]`, `mov rax,[rax+0x10]`; range ends there; next instruction 0x677b5ea.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x6760A80 (sub_6760a80, grow via je), loc_677b5dd (via jmp).
Fields read: [rcx] (= [[0x1233E1B0]]), [rax+0x10] (x2), [rbp+0x847], [r14+0x758], [r14+0x760], [rbp+0x6F0] (lea addr), [[rbp+0x6F0]+0x10], [rbp+0x704], [rbp+0x708], [rbp+0x70C], [rbp+0x710], [rbp+0x714], [rbp+0x574] (addr), [[rbp+0x574]+0x1A4], [[rbp+0x574]+0x1B4], [[rbp+0x574]+0x1C3]. Fields written: [rbp+0x847], [r14+0x758+0x10], [r14+0x758] (movups x3), [r14+0x758+0x14], [r14+0x758+0x18], [r14+0x758+0x1C], [r14+0x758+0x20], [r14+0x758+0x24], [r14+0x758+0x28], [r14+0x758+0x38], [r14+0x758+0x47], [r14+0x758] (add 0x58).

## Phase 137 — Weird opens ([?]: adc/mov/or/add/adc) + [rbp+0x4A0]=0x4001 + counter shr3/imul 0xFFFF8BA3 [rbp+0x4CC] + TLS flag [rbp+0x847] + cursor [r14+0x890] inc/grow (0x6760E60) + not+add counter [rbp+0x4B2] + TLS read continues (0x677b5ea..0x677b6a4)

Opens with five unusual instructions (`adc [rdi],cl`, `mov dh,0x95`, `or [r8],r8b`, `add bh,bh`, `adc eax,0x92249A8`) — meaning unclear ([?], likely embedded data). Then `mov qword ptr [rbp+0x4A0],0x4001` (u64 state tag). Counter: `eax=[r14+0x758]`, `sub [r14+0x750]`, `shr 3`, `imul 0xFFFF8BA3`, `dec`, `[rbp+0x4CC]=ax`. TLS flag read → `[rbp+0x847]=al`. Cursor bounds check: rdx=[r14+0x890]; cmp [r14+0x898]; if equal jump loc_677b65d (grow: `lea rcx,[r14+0x888]`, call 0x6760E60); else `inc rdx`; `[r14+0x890]=rdx`; `jmp loc_677b66a`. loc_677b65d: `lea rcx,[r14+0x888]`, call 0x6760E60 (grow), nop. loc_677b66a: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x847], call via [0xF99FFA0]; counter: `eax=[r14+0x888]`, `not eax`, `add eax,[r14+0x890]`, `[rbp+0x4B2]=ax`; TLS read continues: `mov rcx,[0x1233E1B0]`; range ends there; next instruction 0x677b6a4.

```
  677b5ea  adc [rdi],cl                                  
  677b5ec  mov dh,0x95                                   
  677b5ee  or [r8],r8b                                   ; W a2+0x0
  677b5f1  add bh,bh                                     
  677b5f3  adc eax,0x92249A8                             
  677b5f8  nop                                           
  677b5f9  mov qword ptr [rbp+0x4A0],0x4001              
  677b604  mov eax,[r14+0x758]                           
  677b60b  sub eax,[r14+0x750]                           
  677b612  shr eax,3                                     
  677b615  imul eax,0xFFFF8BA3                           
  677b61b  dec eax                                       
  677b61d  mov [rbp+0x4CC],ax                            
  677b624  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b62b  mov rax,[rcx]                                 
  677b62e  mov rax,[rax+0x10]                            
  677b632  mov dl,0x4A                                   
  677b634  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b63a  nop                                           
  677b63b  mov [rbp+0x847],al                            
  677b641  mov rdx,[r14+0x890]                           
  677b648  cmp rdx,[r14+0x898]                           
  677b64f  je short 0x677B65D                            ; -> loc_677b65d
  677b651  inc rdx                                       
  677b654  mov [r14+0x890],rdx                           
  677b65b  jmp short 0x677B66A                           ; -> loc_677b66a

loc_677b65d:  ; from 677b64f
  677b65d  lea rcx,[r14+0x888]                           
  677b664  call 0x6760E60                                ; -> sub_6760e60
  677b669  nop                                           

loc_677b66a:  ; from 677b65b
  677b66a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b671  mov rax,[rcx]                                 
  677b674  mov rax,[rax+0x10]                            
  677b678  movzx edx,byte ptr [rbp+0x847]                
  677b67f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b685  nop                                           
  677b686  mov eax,[r14+0x888]                           
  677b68d  not eax                                       
  677b68f  add eax,[r14+0x890]                           
  677b696  mov [rbp+0x4B2],ax                            
  677b69d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```

Interpretation: `adc [rdi],cl`; `mov dh,0x95`; `or [r8],r8b`; `add bh,bh`; `adc eax,0x92249A8` — unusual instructions at phase start ([?]). Then `mov qword ptr [rbp+0x4A0],0x4001`. Counter: `eax=[r14+0x758]`, `sub eax,[r14+0x750]`, `shr eax,3`, `imul eax,0xFFFF8BA3`, `dec eax`, `[rbp+0x4CC]=ax`. TLS: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], [rbp+0x847]=al. Cursor: rdx=[r14+0x890], cmp [r14+0x898]; je loc_677b65d; else inc rdx, [r14+0x890]=rdx, jmp loc_677b66a. loc_677b65d: `lea rcx,[r14+0x888]`, call 0x6760E60 (grow), nop. loc_677b66a: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x847], call via [0xF99FFA0]; counter: eax=[r14+0x888], not eax, add eax,[r14+0x890], [rbp+0x4B2]=ax. TLS continues: `mov rcx,[0x1233E1B0]`; range ends there; next instruction at 0x677b6a4 (expected `mov rax,[rcx]`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0x6760E60 (sub_6760e60, grow via je), loc_677b66a (via jmp).
Fields read: [rdi] (adc), [r8] (or), [rbp+0x758], [rbp+0x750], [0x1233E1B0] (x3), [rcx] (x3), [rax+0x10] (x3), [rbp+0x847] (x2), [r14+0x890], [r14+0x898], [r14+0x890] (2nd), [r14+0x888], [r14+0x890] (add). Fields written: [rbp+0x4A0], [rbp+0x4CC], [rbp+0x847] (x2), [r14+0x890], [rbp+0x4B2].

## Phase 138 — TLS tail (mov rax,[rcx]/[rax+0x10] + flag store [rbp+0x847]) + cursor [r14+0x7A0] inc/grow (0x6760E60) + [rbp+0x4A0]=0x4803 + not+add counter [rbp+0x4C6] + call 0x675FB30 + TLS read continues (0x677b6a4..0x677b766)

Completes Phase 137's TLS read: `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `mov dl,0x4A`; call via [0xF99FFA0]; `nop`; `[rbp+0x847]=al`. Cursor bounds check: rdx=[r14+0x7A0]; cmp [r14+0x7A8]; if equal jump loc_677b6d6 (grow: `lea rcx,[r14+0x798]`, call 0x6760E60); else `inc rdx`; `[r14+0x7A0]=rdx`; `jmp loc_677b6e3`. loc_677b6e3: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10]; `movzx edx,byte [rbp+0x847]`; call via [0xF99FFA0]; `nop`; `mov qword ptr [rbp+0x4A0],0x4803` (u64 state tag). Counter: `eax=[r14+0x798]`, `not eax`, `add eax,[r14+0x7A0]`, `[rbp+0x4C6]=ax`. TLS read again; `[rbp+0x847]=al`. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x698]`; call 0x675FB30 (rcx=&[r14+0x648], rdx=&[rbp+0x698] — same callee as Phase 127's first call but different rdx). TLS read continues: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x847]; range ends there; next instruction 0x677b766 (expected `call qword ptr [0xF99FFA0]`).

```
  677b6a4  mov rax,[rcx]                                 ; R a0+0x0
  677b6a7  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  677b6ab  mov dl,0x4A                                   
  677b6ad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b6b3  nop                                           
  677b6b4  mov [rbp+0x847],al                            
  677b6ba  mov rdx,[r14+0x7A0]                           
  677b6c1  cmp rdx,[r14+0x7A8]                           
  677b6c8  je short 0x677B6D6                            ; -> loc_677b6d6
  677b6ca  inc rdx                                       
  677b6cd  mov [r14+0x7A0],rdx                           
  677b6d4  jmp short 0x677B6E3                           ; -> loc_677b6e3

loc_677b6d6:  ; from 677b6c8
  677b6d6  lea rcx,[r14+0x798]                           
  677b6dd  call 0x6760E60                                ; -> sub_6760e60
  677b6e2  nop                                           

loc_677b6e3:  ; from 677b6d4
  677b6e3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b6ea  mov rax,[rcx]                                 
  677b6ed  mov rax,[rax+0x10]                            
  677b6f1  movzx edx,byte ptr [rbp+0x847]                
  677b6f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b6fe  nop                                           
  677b6ff  mov qword ptr [rbp+0x4A0],0x4803              
  677b70a  mov eax,[r14+0x798]                           
  677b711  not eax                                       
  677b713  add eax,[r14+0x7A0]                           
  677b71a  mov [rbp+0x4C6],ax                            
  677b721  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b728  mov rax,[rcx]                                 
  677b72b  mov rax,[rax+0x10]                            
  677b72f  mov dl,0x4A                                   
  677b731  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b737  mov [rbp+0x847],al                            
  677b73d  lea rcx,[r14+0x648]                           
  677b744  lea rdx,[rbp+0x698]                           
  677b74b  call 0x675FB30                                ; -> sub_675fb30
  677b750  nop                                           
  677b751  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b758  mov rax,[rcx]                                 
  677b75b  mov rax,[rax+0x10]                            
  677b75f  movzx edx,byte ptr [rbp+0x847]                
```

Interpretation: `mov rax,[rcx]`; `mov rax,[rax+0x10]` completes the TLS slot read (rcx=[0x1233E1B0] from Phase 137's end); `mov dl,0x4A`; call via [0xF99FFA0]; `nop`; `[rbp+0x847]=al` (flag store). Cursor: rdx=[r14+0x7A0], cmp [r14+0x7A8]; je loc_677b6d6; else inc rdx, [r14+0x7A0]=rdx, jmp loc_677b6e3. loc_677b6d6: `lea rcx,[r14+0x798]`, call 0x6760E60 (grow), nop. loc_677b6e3: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x847], call via [0xF99FFA0], `mov qword ptr [rbp+0x4A0],0x4803` (u64 state tag). Counter: `eax=[r14+0x798]`, `not eax`, `add eax,[r14+0x7A0]`, `[rbp+0x4C6]=ax`. TLS: rcx=[0x1233E1B0]→[rax]→[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], `[rbp+0x847]=al`. `lea rcx,[r14+0x648]`, `lea rdx,[rbp+0x698]`, call 0x675FB30. TLS continues: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x847]; range ends there; next instruction at 0x677b766 (expected `call qword ptr [0xF99FFA0]`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 3x), 0x6760E60 (sub_6760e60, grow via je), loc_677b6e3 (via jmp), 0x675FB30 (sub_675fb30).
Fields read: [rcx] (= [[0x1233E1B0]]) x3, [rax+0x10] x3, [rbp+0x847] (x3), [r14+0x7A0], [r14+0x7A8], [r14+0x7A0] (2nd), [r14+0x798], [r14+0x798] (2nd), r14+0x648 (lea addr), rbp+0x698 (lea addr). Fields written: [rbp+0x847] (x3), [r14+0x7A0], [rbp+0x4A0] (0x4803), [rbp+0x4C6].

## Phase 139 — TLS tail (call [0xF99FFA0] + nop) + counter shr3/imul 0xFFFF8E39 [rbp+0x4E2] + call 0x675F3B0 + counter shr3/imul 0xFFFF8BA3 [rbp+0x4C8] + TLS flag [rbp+0x847] + element append at [r14+0x770] ([rbp+0x5B8] qword, [rbp+0x5C0] bytes, [rbp+0x638]→[r15+0x80], [rbp+0x638]=0, +0x88) + grow path loc_677b82e (0x677b766..0x677b838)

Completes Phase 138's final TLS call: `call qword ptr [0xF99FFA0]`; `nop`. Counter 1: `eax=[r14+0x650]`, `sub [r14+0x648]`, `shr 3`, `imul 0xFFFF8E39`, `dec`, `[rbp+0x4E2]=ax`. `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x640]`; call 0x675F3B0. Counter 2: `eax=[r14+0x788]`, `sub [r14+0x780]`, `shr 3`, `imul 0xFFFF8BA3`, `dec`, `[rbp+0x4C8]=ax`. TLS flag: rcx=[0x1233E1B0]→[rax]→[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], `[rbp+0x847]=al`. Element append: r15=[r14+0x770]; cmp [r14+0x778]; if equal jump loc_677b82e (grow: `lea rcx,[r14+0x768]`, `mov rdx,r15`, ...continues next phase). Else `[r15]=[rbp+0x5B8]`; `lea rcx,[r15+8]`; `lea rdx,[rbp+0x5C0]`; call 0xE869FF0; `mov rax,[rbp+0x638]`; `[r15+0x80]=rax`; `[rbp+0x638]=0`; `[r14+0x770]+=0x88`; `jmp short loc_677b845`. Range ends at `mov rdx,r15` (start of grow block's arg setup); next instruction 0x677b838 (expected `lea r8,[rbp+0x5B8]` then call 0x6760710 — same shape as Phase 128's grow).

```
  677b766  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b76c  nop                                           
  677b76d  mov eax,[r14+0x650]                           
  677b774  sub eax,[r14+0x648]                           
  677b77b  shr eax,3                                     
  677b77e  imul eax,0xFFFF8E39                           
  677b784  dec eax                                       
  677b786  mov [rbp+0x4E2],ax                            
  677b78d  lea rcx,[r14+0x780]                           
  677b794  lea rdx,[rbp+0x640]                           
  677b79b  call 0x675F3B0                                ; -> sub_675f3b0
  677b7a0  nop                                           
  677b7a1  mov eax,[r14+0x788]                           
  677b7a8  sub eax,[r14+0x780]                           
  677b7af  shr eax,3                                     
  677b7b2  imul eax,0xFFFF8BA3                           
  677b7b8  dec eax                                       
  677b7ba  mov [rbp+0x4C8],ax                            
  677b7c1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b7c8  mov rax,[rcx]                                 
  677b7cb  mov rax,[rax+0x10]                            
  677b7cf  mov dl,0x4A                                   
  677b7d1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b7d7  mov [rbp+0x847],al                            
  677b7dd  mov r15,[r14+0x770]                           
  677b7e4  cmp r15,[r14+0x778]                           
  677b7eb  je short 0x677B82E                            ; -> loc_677b82e
  677b7ed  mov rax,[rbp+0x5B8]                           
  677b7f4  mov [r15],rax                                 
  677b7f7  lea rcx,[r15+8]                               
  677b7fb  lea rdx,[rbp+0x5C0]                           
  677b802  call 0xE869FF0                                ; -> sub_e869ff0
  677b807  nop                                           
  677b808  mov rax,[rbp+0x638]                           
  677b80f  mov [r15+0x80],rax                            
  677b816  mov qword ptr [rbp+0x638],0                   
  677b821  add qword ptr [r14+0x770],0x88                
  677b82c  jmp short 0x677B845                           ; -> loc_677b845

loc_677b82e:  ; from 677b7eb
  677b82e  lea rcx,[r14+0x768]                           
  677b835  mov rdx,r15                                   
```

Interpretation: `call qword ptr [0xF99FFA0]`; `nop` — completes the TLS flag call opened at Phase 138's end. Counter 1: `eax=[r14+0x650]`, `sub eax,[r14+0x648]`, `shr eax,3`, `imul eax,0xFFFF8E39`, `dec eax`, `[rbp+0x4E2]=ax`. `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x640]`; call 0x675F3B0 (same callee as Phase 127's second call). Counter 2: `eax=[r14+0x788]`, `sub eax,[r14+0x780]`, `shr eax,3`, `imul eax,0xFFFF8BA3`, `dec eax`, `[rbp+0x4C8]=ax`. TLS: rcx=[0x1233E1B0]→[rax]→[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], `[rbp+0x847]=al`. Append element: r15=[r14+0x770], cmp [r14+0x778]; full → grow loc_677b82e (`lea rcx,[r14+0x768]`, `mov rdx,r15`, continues next phase). Else store [rbp+0x5B8] at [r15], call 0xE869FF0(rcx=r15+8, rdx=&[rbp+0x5C0]), store [rbp+0x638] at [r15+0x80], zero [rbp+0x638], advance [r14+0x770] by 0x88, jmp loc_677b845. Range ends at grow-block `mov rdx,r15`; next instruction 0x677b838.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0x675F3B0 (sub_675f3b0), 0xE869FF0 (sub_e869ff0), loc_677b82e (grow via je), loc_677b845 (via jmp).
Fields read: [r14+0x650], [r14+0x648], r14+0x780 (lea addr), rbp+0x640 (lea addr), [r14+0x788], [r14+0x780], [0x1233E1B0] (x2), [rcx] (x2), [rax+0x10] (x2), [rbp+0x847], [r14+0x770], [r14+0x778], [rbp+0x5B8], r15, [rbp+0x5C0] (addr), [rbp+0x638], [r14+0x770] (2nd). Fields written: [rbp+0x4E2], [rbp+0x4C8], [rbp+0x847], [r15], [r15+0x80], [rbp+0x638], [r14+0x770].

## Phase 140 — Grow call 0x6760710 + TLS flag [rbp+0x847] + counter shr3/imul 0xFFFFF0F1 [rbp+0x4CA] + cursor [r14+0x2D8] inc/grow (0x6760E60) + not+add counter start (ends at not eax) (0x677b838..0x677b8f7)

Completes Phase 139's grow block: `lea r8,[rbp+0x5B8]`, call 0x6760710 (grow helper — same shape as Phase 139's grow), `nop`. loc_677b845: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10]; `movzx edx,byte [rbp+0x847]`; call via [0xF99FFA0]; `mov qword ptr [rbp+0x4A0],0x2007803` (u64 state tag). Counter: `eax=[r14+0x770]`, `sub eax,[r14+0x768]`, `shr eax,3`, `imul eax,0xFFFFF0F1`, `dec eax`, `[rbp+0x4CA]=ax`. TLS flag again → `[rbp+0x847]=al`. Cursor bounds check: `rdx=[r14+0x2D8]`; `cmp [r14+0x2E0]`; je loc_677b8c5 (grow: `lea rcx,[r14+0x2D0]`, call 0x6760E60); else `inc rdx`; `[r14+0x2D8]=rdx`; `jmp loc_677b8d2`. loc_677b8d2: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10]; `movzx edx,byte [rbp+0x847]`; call via [0xF99FFA0]; `mov eax,[r14+0x2D0]`; `not eax` — phase ends mid-not at 0x677b8f5; next instruction 0x677b8f7 (expected `add eax,[r14+0x2D8]` then `mov [rbp+0x4C?],ax` mirroring Phase 138's not+add pattern).

```
  677b838  lea r8,[rbp+0x5B8]                            
  677b83f  call 0x6760710                                ; -> sub_6760710
  677b844  nop                                           
  677b845  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b84c  mov rax,[rcx]                                 
  677b84f  mov rax,[rax+0x10]                            
  677b853  movzx edx,byte ptr [rbp+0x847]                
  677b85a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b860  nop                                           
  677b861  mov qword ptr [rbp+0x4A0],0x2007803           
  677b86c  mov eax,[r14+0x770]                           
  677b873  sub eax,[r14+0x768]                           
  677b87a  shr eax,3                                     
  677b87d  imul eax,0xFFFFF0F1                           
  677b883  dec eax                                       
  677b885  mov [rbp+0x4CA],ax                            
  677b88c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b893  mov rax,[rcx]                                 
  677b896  mov rax,[rax+0x10]                            
  677b89a  mov dl,0x4A                                   
  677b89c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b8a2  nop                                           
  677b8a3  mov [rbp+0x847],al                            
  677b8a9  mov rdx,[r14+0x2D8]                           
  677b8b0  cmp rdx,[r14+0x2E0]                           
  677b8b7  je short 0x677B8C5                            ; -> loc_677b8c5
  677b8b9  inc rdx                                       
  677b8bc  mov [r14+0x2D8],rdx                           
  677b8c3  jmp short 0x677B8D2                           ; -> loc_677b8d2

loc_677b8c5:  ; from 677b8b7
  677b8c5  lea rcx,[r14+0x2D0]                           
  677b8cc  call 0x6760E60                                ; -> sub_6760e60
  677b8d1  nop                                           

loc_677b8d2:  ; from 677b8c3
  677b8d2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b8d9  mov rax,[rcx]                                 
  677b8dc  mov rax,[rax+0x10]                            
  677b8e0  movzx edx,byte ptr [rbp+0x847]                
  677b8e7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b8ed  nop                                           
  677b8ee  mov eax,[r14+0x2D0]                           
  677b8f5  not eax                                       
```

Interpretation: `lea r8,[rbp+0x5B8]`; call 0x6760710 (grow helper — same shape as Phase 139's grow block lea r8,[rbp+0x5B8]). loc_677b845: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10]; movzx edx,byte [rbp+0x847]; call via [0xF99FFA0]; `[rbp+0x4A0]=0x2007803` (u64 state tag). Counter: `eax=[r14+0x770]`, `sub eax,[r14+0x768]`, `shr eax,3`, `imul eax,0xFFFFF0F1`, `dec eax`, `[rbp+0x4CA]=ax`. TLS flag again → `[rbp+0x847]=al`. Cursor bounds check: `rdx=[r14+0x2D8]`, `cmp [r14+0x2E0]`; je loc_677b8c5; else `inc rdx`, `[r14+0x2D8]=rdx`, `jmp loc_677b8d2`. loc_677b8c5: `lea rcx,[r14+0x2D0]`, call 0x6760E60 (grow), nop. loc_677b8d2: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x847], call via [0xF99FFA0], `mov eax,[r14+0x2D0]`, `not eax` — phase ends there; next instruction 0x677b8f7.

Callees: 0x6760710 (sub_6760710), [0xF99FFA0] = sub_eea6040 (indirect, 3x), 0x6760E60 (sub_6760e60, grow via je), loc_677b8d2 (via jmp).
Fields read: [rbp+0x5B8] (lea addr), [0x1233E1B0] (x4), [rcx] (x4), [rax+0x10] (x4), [rbp+0x847] (x3), [rbp+0x770], [rbp+0x768], [r14+0x2D8], [r14+0x2E0], [r14+0x2D0]. Fields written: [rbp+0x4A0] (0x2007803), [rbp+0x4CA], [rbp+0x847] (x2), [r14+0x2D8].

## Phase 141 — not+add counter tail [rbp+0x52C] + TLS flag [rbp+0x847] + cursor [r14+0x6C8] inc/grow (0x6760E60) + [rbp+0x4A0]=0x4000000002107803 + not+add counter [rbp+0x4D8] + TLS flag + cursor [r14+0x6B0] vs [r14+0x6B8] (ends at je) (0x677b8f7..0x677b9be)

Completes Phase 140's `not eax` at 0x677b8f5: `add eax,[r14+0x2D8]`; `[rbp+0x52C]=ax` (mirrors Phase 138's [rbp+0x4C6]). TLS flag call → `[rbp+0x847]=al`. Cursor bounds check: `rdx=[r14+0x6C8]`; `cmp [r14+0x6D0]`; je loc_677b93e (grow: `lea rcx,[r14+0x6C0]`, call 0x6760E60); else `inc rdx`; `[r14+0x6C8]=rdx`; `jmp loc_677b94b`. loc_677b94b: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10]; `movzx edx,byte [rbp+0x847]`; call via [0xF99FFA0]; `mov rax,0x4000000002107803`; `[rbp+0x4A0]=rax` (u64 state tag, distinct from Phase 140's 0x2007803). Counter: `eax=[r14+0x6C0]`, `not eax`, `add eax,[r14+0x6C8]`, `[rbp+0x4D8]=ax`. TLS flag call → `[rbp+0x847]=al`. Cursor bounds check: `rdx=[r14+0x6B0]`; `cmp [r14+0x6B8]`; je short loc_677b9c8 — phase ends at the je; next instruction 0x677b9be (expected loc_677b9c8 grow block or inc path mirroring prior cursor checks).

```
  677b8f7  add eax,[r14+0x2D8]                           
  677b8fe  mov [rbp+0x52C],ax                            
  677b905  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b90c  mov rax,[rcx]                                 
  677b90f  mov rax,[rax+0x10]                            
  677b913  mov dl,0x4A                                   
  677b915  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b91b  nop                                           
  677b91c  mov [rbp+0x847],al                            
  677b922  mov rdx,[r14+0x6C8]                           
  677b929  cmp rdx,[r14+0x6D0]                           
  677b930  je short 0x677B93E                            ; -> loc_677b93e
  677b932  inc rdx                                       
  677b935  mov [r14+0x6C8],rdx                           
  677b93c  jmp short 0x677B94B                           ; -> loc_677b94b

loc_677b93e:  ; from 677b930
  677b93e  lea rcx,[r14+0x6C0]                           
  677b945  call 0x6760E60                                ; -> sub_6760e60
  677b94a  nop                                           

loc_677b94b:  ; from 677b93c
  677b94b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b952  mov rax,[rcx]                                 
  677b955  mov rax,[rax+0x10]                            
  677b959  movzx edx,byte ptr [rbp+0x847]                
  677b960  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b966  nop                                           
  677b967  mov rax,0x4000000002107803                    
  677b971  mov [rbp+0x4A0],rax                           
  677b978  mov eax,[r14+0x6C0]                           
  677b97f  not eax                                       
  677b981  add eax,[r14+0x6C8]                           
  677b988  mov [rbp+0x4D8],ax                            
  677b98f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b996  mov rax,[rcx]                                 
  677b999  mov rax,[rax+0x10]                            
  677b99d  mov dl,0x4A                                   
  677b99f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b9a5  nop                                           
  677b9a6  mov [rbp+0x847],al                            
  677b9ac  mov rdx,[r14+0x6B0]                           
  677b9b3  cmp rdx,[r14+0x6B8]                           
  677b9ba  je short 0x677B9C8                            ; -> loc_677b9c8
```

Interpretation: `add eax,[r14+0x2D8]` completes Phase 140's `not eax`; `[rbp+0x52C]=ax`. TLS: rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x847], call via [0xF99FFA0], `[rbp+0x847]=al`. Cursor: rdx=[r14+0x6C8], cmp [r14+0x6D0]; je loc_677b93e; else inc rdx, [r14+0x6C8]=rdx, jmp loc_677b94b. loc_677b93e: `lea rcx,[r14+0x6C0]`, call 0x6760E60 (grow), nop. loc_677b94b: TLS read, movzx edx,byte [rbp+0x847], call via [0xF99FFA0], `mov rax,0x4000000002107803`, `[rbp+0x4A0]=rax`. Counter: `eax=[r14+0x6C0]`, `not eax`, `add eax,[r14+0x6C8]`, `[rbp+0x4D8]=ax`. TLS: rcx=[0x1233E1B0]→[rax]→[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], `[rbp+0x847]=al`. Cursor: rdx=[r14+0x6B0], cmp [r14+0x6B8], je short loc_677b9c8; phase ends at je; next instruction 0x677b9be.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 4x), 0x6760E60 (sub_6760e60, grow via je), loc_677b94b (via jmp).
Fields read: [r14+0x2D8], [rbp+0x847], [r14+0x6C8], [r14+0x6D0], [0x1233E1B0] (x4), [rcx] (x4), [rax+0x10] (x4), [rbp+0x847] (x2), [r14+0x6C0], [r14+0x6C8] (add), [r14+0x6B0], [r14+0x6B8]. Fields written: [rbp+0x52C], [rbp+0x847] (x3), [r14+0x6C8], [rbp+0x4A0], [rbp+0x4D8].

## Phase 142 — Weird opens [?] (ret/xchg/mov/add/jmp) + grow target loc_677b9c8 (0x6760E60) + not+add counter [rbp+0x4DA] + TLS flag [rbp+0x847] + record append at [r14+0x590] (qword+0x100000000, call 0x6764990, +0x30) + grow loc_677ba5f (continues next phase) (0x677b9be..0x677ba6c)

Opens with 5 unusual instructions at fall-through of Phase 141's je (`ret 0x8949`, `xchg esi,eax`, `mov al,6`, `add [rax],al`, `jmp short 0x677B9D5`) — meaning unclear ([?], embedded data/padding between fall-through and the je target at 0x677b9c8, same class as Phase 132/137 [?] clusters). loc_677b9c8 (jump target of Phase 141's je): `lea rcx,[r14+0x6A8]`, call 0x6760E60 (grow), nop. loc_677b9d5: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10]; `movzx edx,byte [rbp+0x847]`; call via [0xF99FFA0]; `[rbp+0x847]=al`. Counter: `eax=[r14+0x6A8]`, `not eax`, `add eax,[r14+0x6B0]`, `[rbp+0x4DA]=ax`. TLS flag again → `[rbp+0x847]=al`. Record append: `rdx=[r14+0x590]`; `cmp [r14+0x598]`; je loc_677ba5f (grow block: `mov rcx,r14`, `add rcx,0x588`, `mov r8,r12` — continues next phase); else `lea rax,[rdx+0x10]`; `[rdx]=rax`; `mov rax,0x100000000`; `[rdx+8]=rax`; `mov rcx,rdx`; `mov rdx,r12`; call 0x6764990; `add qword ptr [r14+0x590],0x30`; `jmp short loc_677ba72`. Phase ends at grow-block `mov r8,r12` (0x677ba69); next instruction 0x677ba6c (expected call, mirroring Phase 140's grow-block call 0x6760710).

```
  677b9be  ret 0x8949                                    
  677b9c1  xchg esi,eax                                  
  677b9c2  mov al,6                                      
  677b9c4  add [rax],al                                  
  677b9c6  jmp short 0x677B9D5                           ; -> loc_677b9d5
  677b9c8  lea rcx,[r14+0x6A8]                           
  677b9cf  call 0x6760E60                                ; -> sub_6760e60
  677b9d4  nop                                           

loc_677b9d5:  ; from 677b9c6
  677b9d5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677b9dc  mov rax,[rcx]                                 
  677b9df  mov rax,[rax+0x10]                            
  677b9e3  movzx edx,byte ptr [rbp+0x847]                
  677b9ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677b9f0  nop                                           
  677b9f1  mov eax,[r14+0x6A8]                           
  677b9f8  not eax                                       
  677b9fa  add eax,[r14+0x6B0]                           
  677ba01  mov [rbp+0x4DA],ax                            
  677ba08  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677ba0f  mov rax,[rcx]                                 
  677ba12  mov rax,[rax+0x10]                            
  677ba16  mov dl,0x4A                                   
  677ba18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677ba1e  nop                                           
  677ba1f  mov [rbp+0x847],al                            
  677ba25  mov rdx,[r14+0x590]                           
  677ba2c  cmp rdx,[r14+0x598]                           
  677ba33  je short 0x677BA5F                            ; -> loc_677ba5f
  677ba35  lea rax,[rdx+0x10]                            
  677ba39  mov [rdx],rax                                 
  677ba3c  mov rax,0x100000000                           
  677ba46  mov [rdx+8],rax                               
  677ba4a  mov rcx,rdx                                   
  677ba4d  mov rdx,r12                                   
  677ba50  call 0x6764990                                ; -> sub_6764990
  677ba55  add qword ptr [r14+0x590],0x30                
  677ba5d  jmp short 0x677BA72                           ; -> loc_677ba72

loc_677ba5f:  ; from 677ba33
  677ba5f  mov rcx,r14                                   
  677ba62  add rcx,0x588                                 
  677ba69  mov r8,r12                                    
```

Interpretation: `ret 0x8949`; `xchg esi,eax`; `mov al,6`; `add [rax],al`; `jmp short 0x677B9D5` — unusual instructions at phase start ([?], likely embedded data/padding; never invent meaning). loc_677b9c8: `lea rcx,[r14+0x6A8]`, call 0x6760E60 (grow helper), nop — jump target of Phase 141's `je short 0x677B9C8`. loc_677b9d5: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10]; movzx edx,byte [rbp+0x847]; call via [0xF99FFA0]; `[rbp+0x847]=al` (flag store). Counter: `eax=[r14+0x6A8]`, `not eax`, `add eax,[r14+0x6B0]`, `[rbp+0x4DA]=ax`. TLS again → `[rbp+0x847]=al`. Append record at rdx=[r14+0x590] vs end [r14+0x598]: full → je loc_677ba5f; else `[rdx]=rax` (rax=[rdx+0x10]), `[rdx+8]=0x100000000`, call 0x6764990(rcx=rdx, rdx=r12), `[r14+0x590]+=0x30`, jmp loc_677ba72. loc_677ba5f (grow path): `mov rcx,r14`, `add rcx,0x588`, `mov r8,r12`; phase ends there; next instruction 0x677ba6c (expected call — same grow-block shape as Phase 140's lea r8,[rbp+0x5B8] + call 0x6760710).

Callees: 0x6760E60 (sub_6760e60, grow via je), [0xF99FFA0] = sub_eea6040 (indirect, 3x), 0x6764990 (sub_6764990), loc_677ba72 (via jmp).
Fields read: [rbp+0x847] (x3), [r14+0x6A8], [r14+0x6B0], [r14+0x590], [r14+0x598], [0x1233E1B0] (x4), [rcx] (x4), [rax+0x10] (x4), r14 (lea rcx,r14), r12, [r14+0x590] (lea rax,[rdx+0x10] + add). Fields written: [rax] (add [rax],al — [?]), [rbp+0x4DA], [rbp+0x847] (x2), [rdx] ([r14+0x590]), [[r14+0x590]+8], [r14+0x590] (add 0x30).
