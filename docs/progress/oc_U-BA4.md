# Unit U-BA4 — bodyActor function 0x66d0a00 (1.26.62.01), continued from 0x66d42ae

## NEXT [current]
Resume at RVA 0x66d4951 (after phase 9, instructions 0x66d4881..0x66d494a; next instruction at 0x66d4951). Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d4951 40`
Scope: 1200 instructions from 0x66d42ae in 40-instruction phases (~30 phases total; 9 done, 358 instructions). On any `(bad)` line, restart the phase at the next address until the phase start is on a boundary: phase 3 had `(bad)` at 0x66d440b then garbage decodes at 0x66d440d/0x66d4410; real code resumes at 0x66d4416 [V]. Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Context [V]
- Continuation of U-BA3 (docs/progress/oc_U-BA3.md), phases 1-26 covering 0x66d2d50..0x66d42a9 of bodyActor 0x66d0a00.
- State carried in (from U-BA3): [rbp+0x4D0]/[rbp+0x4D2] index+flag (0x10-stride scans, callee 0x5679DB0); [rbp+0x7E0]/[rbp+0x7E2] index+flag (0x30-stride scans, callee 0x56D56A0 once + 0x5679DB0); value struct at [rbp+0xA50..0xA5C]; out ctx [rbp+0xCE0]; work buffer [rbp+0x400]/[rbp+0x410]; node list walked via [r12] with sentinel r13=[rbp+0xA58]; node data ptr [r12+0x10]; callee 0x66D93C0(rcx=&rbp+0xCE0, rdx=&rbp+0x400, r8=&rbp+0x7E0, r9=r12+0x18); sub_e935700 for small/oversized results; indirect call qword ptr [0xF9A8C78] at loop exit; TLS gate pattern eax=[data global]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg <fallback> [V, U-BA3 phases 1-26].
- Callee inventory (U-BA3): 0xE935700 (free), 0x5679DB0 (index registration), 0xBBD7C70, 0x4DEDD00, 0x66B2B30, 0x6698060, 0x6694660, 0x5AC2420, 0x67612A0, 0x6761590, 0x6761970, 0x67627D0, 0x6762900, 0x6764990, 0x6764400, 0x6765C00, 0x6765020, qword ptr [0xF99FFA0]=sub_eea6040 (alloc/free), qword ptr [0xF9A8C78].
- Fallback targets seen: 0x66D64F8, 0x66D6108, 0x66D6187, 0x66D6ADD, 0x66D72A0, 0x66d2d40, 0x66d438e/0x66d4390.
- Roadata strings seen: [0xF5C6AD8] "UIStructureVolumeCapture texture", [0xF5C6AE8] "eCapture texture"; GUID const 0x8D29EAE11B764987; jump tables [0xF2BFB00] (4 entries) and [0xF2BE878].

## Phase 1 — 0x66d42ae, 40 instructions [V]
```
66d42ae  test rcx,rcx                                   
66d42b1  je short 0x66D42A0                            
66d42b3  lock dec dword ptr [rcx+0xC]                  
66d42b7  jne short 0x66D42A0                           
66d42b9  mov rax,[rcx]                                 
66d42bc  mov rax,[rax+8]                               
66d42c0  call qword ptr [0xF99FFA0]                    
66d42c6  jmp short 0x66D42A0                           
66d42c8  mov rsi,[rbp+0xC20]                           
66d42cf  lea rax,[rbp+0xC30]                           
66d42d6  cmp rax,rsi                                   
66d42d9  je short 0x66D42F8                            
66d42db  mov rcx,[0x1233E1A8]                          
66d42e2  test rsi,rsi                                  
66d42e5  je short 0x66D42F8                            
66d42e7  mov rax,[rcx]                                 
66d42ea  mov rax,[rax+0x10]                            
66d42ee  mov rdx,rsi                                   
66d42f1  call qword ptr [0xF99FFA0]                    
66d42f7  nop                                           
66d42f8  mov rcx,rbx                                   
66d42fb  call 0x67627D0                                
66d4300  mov rsi,[rbp+0x9A8]                           
66d4307  mov edi,[rbp+0x9B0]                           
66d430d  test rdi,rdi                                  
66d4310  je short 0x66D434F                            
66d4312  shl rdi,5                                     
66d4316  xor ebx,ebx                                   
66d4318  jmp short 0x66D4329                           
66d431a  nop [rax+rax]                                 
66d4320  add rbx,0x20                                  
66d4324  cmp rdi,rbx                                   
66d4327  je short 0x66D4348                            
66d4329  mov rcx,[rsi+rbx+8]                           
66d432e  test rcx,rcx                                  
66d4331  je short 0x66D4320                            
66d4333  lock dec dword ptr [rcx+0xC]                  
66d4337  jne short 0x66D4320                           
66d4339  mov rax,[rcx]                                 
66d433c  mov rax,[rax+8]                               
```
// [V] Phase 1 is the tail of release loop #5 from U-BA3 phase 26: entry test rcx,rcx at 0x66d42ae; zero →0x66d42a0 [V]; else `lock dec dword [rcx+0xC]`; nonzero →0x66d42a0 [V]; zero → rax=[rcx]; rax=[rax+8]; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V]; jmp 0x66d42a0 [V]. loc_66d42a0 (loop head from phase 26): rsi=[rbp+0xC20]; rax=&rbp+0xC30; if rax==rsi →0x66d42f8 else allocator teardown: rcx=[0x1233E1A8]; if rsi==0 →0x66d42f8; rax=[rcx]; rax=[rax+0x10]; rdx=rsi; call qword ptr [0xF99FFA0](rdx=rsi) free [V]; nop. loc_66d42f8: rcx=rbx; call 0x67627D0(rcx=rbx) value teardown [V] (4th call-0x67627D0). Release loop #6 head: rsi=[rbp+0x9A8]; edi=[rbp+0x9B0] count; if 0 →0x66d434f; rdi<<=5 (0x20 stride); ebx=0; loc_66d4329: rcx=[rsi+rbx+8]; if 0 →next; lock dec dword [rcx+0xC]; nonzero →next; else rax=[rcx]; rax=[rax+8] (continues phase 2 — free call at 0x66d4340). Ends at 0x66d433c mid-loop; next instruction 0x66d4340 (verified via `dis 0x66d433c 8`: `call qword ptr [0xF99FFA0]` at 0x66d4340; a start at 0x66d4341 mis-decodes the call's ModRM byte as `adc eax,...`).

## Phase 2 — 0x66d4340, 40 instructions [V]
```
66d4340  call qword ptr [0xF99FFA0]                    
66d4346  jmp short 0x66D4320                           
66d4348  mov rsi,[rbp+0x9A8]                           
66d434f  cmp r12,rsi                                   
66d4352  je short 0x66D4371                            
66d4354  mov rcx,[0x1233E1A8]                          
66d435b  test rsi,rsi                                  
66d435e  je short 0x66D4371                            
66d4360  mov rax,[rcx]                                 
66d4363  mov rax,[rax+0x10]                            
66d4367  mov rdx,rsi                                   
66d436a  call qword ptr [0xF99FFA0]                    
66d4370  nop                                           
66d4371  lea rcx,[rbp+0x7E0]                           
66d4378  call 0x67627D0                                
66d437d  lea rcx,[rbp+0x208]                           
66d4384  call 0x67627D0                                
66d4389  jmp 0x66D6108                                 
66d438e  xor eax,eax                                   
66d4390  mov [rbp+0x7B0],rbx                           
66d4397  mov [rbp+0x7B8],rax                           
66d439e  mov [rbp+0x7C0],esi                           
66d43a4  mov [rbp+0x7C4],r15d                          
66d43ab  mov dword ptr [rbp+0x7C8],0x1C                
66d43b5  movzx ecx,byte ptr [rbp+0xD8E]                
66d43bc  mov [rbp+0x7CE],cl                            
66d43c2  movzx ecx,word ptr [rbp+0xD8C]                
66d43c9  mov [rbp+0x7CC],cx                            
66d43d0  mov [rbp+0x7D0],r12                           
66d43d7  movaps [rbp+0x770],xmm0                       
66d43de  mov rcx,[r14+0x1A8]                           
66d43e5  test rcx,rcx                                  
66d43e8  je short 0x66D43FE                            
66d43ea  lock inc dword ptr [rcx+8]                    
66d43ee  mov rcx,[r14+0x1A8]                           
66d43f5  mov rax,[rbp+0x7B8]                           
66d43fc  jmp short 0x66D4400                           
66d43fe  xor ecx,ecx                                   
66d4400  mov rbx,[rbp+0xCD8]                           
66d4407  lea rdx,[rbp+0x7C0]                           
```
// [V] Phase 2 completes release loop #6 body: `call qword ptr [0xF99FFA0]` (sub_eea6040 free) at 0x66d4340 [V]; `jmp short 0x66d4320` loop head [V]. Loop exit path at 0x66d4348: rsi=[rbp+0x9A8]; cmp r12,rsi; je 0x66d4371 if entries exhausted [V]; else release head: rcx=[0x1233E1A8]; test rsi,rsi; je 0x66d4371 if null; rax=[rcx]; rax=[rax+0x10] (allocator free fn); rdx=rsi; call qword ptr [0xF99FFA0](rdx=rsi) free [V]; nop. loc_66d4371: call 0x67627D0(rcx=&rbp+0x7E0) [V] (5th call-0x67627D0); call 0x67627D0(rcx=&rbp+0x208) [V] (6th call); jmp 0x66d6108 fallback [V]. Fall-through join (from phase-19 `je 0x66d438e`): xor eax,eax; value struct at [rbp+0x7B0..0x7D0]: [0x7B0]=rbx, [0x7B8]=rax, [0x7C0]=esi, [0x7C4]=r15d, [0x7C8]=0x1C dword, [0x7CE]=byte [rbp+0xD8E], [0x7CC]=word [rbp+0xD8C], [0x7D0]=r12 [V]; [rbp+0x770]=xmm0 [V]; rcx=[r14+0x1A8]; test rcx,rcx; je 0x66d43fe (ecx=0 null); else `lock inc dword [rcx+8]` refcount bump [V]; rcx=[r14+0x1A8]; rax=[rbp+0x7B8]; jmp 0x66d4400 [V]. loc_66d43fe: xor ecx,ecx [V]. loc_66d4400: rbx=[rbp+0xCD8]; lea rdx,&rbp+0x7C0 (continues phase 3). Next address: 0x66d440b → garbage fill, real code at 0x66d4416.

## Phase 3 — 0x66d4416, 38 instructions [V] (restarted at 0x66d4416 after `(bad)` at 0x66d440b and garbage decodes `add [rbp-0x75],cl` / `xchg [rax+0x4C000001],ah` at 0x66d440d/0x66d4410; rdis output capped at 38 lines, last instruction at 0x66d44cf)
```
66d4416  mov [rbp+0x770],eax                           
66d441c  mov [rbp+0x778],rcx                           
66d4423  movaps [rbp+0x780],xmm0                       
66d442a  test rax,rax                                  
66d442d  je short 0x66D4443                            ; -> loc_66d4443
66d442f  lock inc dword ptr [rax+8]                    
66d4433  mov rax,[rbp+0x7B8]                           
66d443a  mov rcx,[rbp+0x778]                           
66d4441  jmp short 0x66D4445                           ; -> loc_66d4445

loc_66d4443:  ; from 66d442d
  66d4443  xor eax,eax                                   

loc_66d4445:  ; from 66d4441
  66d4445  mov r8,[rbp+0x7B0]                            
  66d444c  mov [rbp+0x780],r8                            
  66d4453  mov [rbp+0x788],rax                           
  66d445a  movups xmm1,[rdx]                             
  66d445d  movaps [rbp+0x790],xmm1                       
  66d4464  mov rdx,[rdx+0x10]                            
  66d4468  mov [rbp+0x7A0],rdx                           
  66d446f  movaps [rbp+0x6D0],xmm0                       
  66d4476  test rcx,rcx                                  
  66d4479  je short 0x66D448F                            ; -> loc_66d448f
  66d447b  lock inc dword ptr [rcx+8]                    
  66d447f  mov rcx,[rbp+0x778]                           
  66d4486  mov rax,[rbp+0x788]                           
  66d448d  jmp short 0x66D4491                           ; -> loc_66d4491

loc_66d448f:  ; from 66d4479
  66d448f  xor ecx,ecx                                   

loc_66d4491:  ; from 66d448d
  66d4491  lea rdx,[rbp+0x790]                           
  66d4498  mov r8,[rbp+0x770]                            
  66d449f  mov [rbp+0x6D0],r8                            
  66d44a6  mov [rbp+0x6D8],rcx                           
  66d44ad  movaps [rbp+0x6E0],xmm0                       
  66d44b4  test rax,rax                                  
  66d44b7  je short 0x66D44CD                            ; -> loc_66d44cd
  66d44b9  lock inc dword ptr [rax+8]                    
  66d44bd  mov rax,[rbp+0x788]                           
  66d44c4  mov rcx,[rbp+0x6D8]                           
  66d44cb  jmp short 0x66D44CF                           ; -> loc_66d44cf

loc_66d44cd:  ; from 66d44b7
  66d44cd  xor eax,eax                                   

loc_66d44cf:  ; from 66d44cb
  66d44cf  mov r8,[rbp+0x780]                            
```
// [V] Phase 3 resumes real code at 0x66d4416 (after `(bad)` byte at 0x66d440b and garbage decodes at 0x66d440d-0x66d4415): builds value struct at [rbp+0x770..0x7A0]: [0x770]=eax, [0x778]=rcx, [0x780]=xmm0 [V]; test rax,rax; je 0x66d4443 (eax=0); else lock inc dword [rax+8] refcount [V]; rax=[rbp+0x7B8]; rcx=[rbp+0x778]; jmp 0x66d4445 [V]. loc_66d4443: xor eax,eax [V]. loc_66d4445: r8=[rbp+0x7B0]; [rbp+0x780]=r8; [rbp+0x788]=rax [V]; movups xmm1=[rdx]; [rbp+0x790]=xmm1; rdx=[rdx+0x10]; [rbp+0x7A0]=rdx [V]; [rbp+0x6D0]=xmm0 [V]; test rcx,rcx; je 0x66d448f (ecx=0); else lock inc dword [rcx+8] [V]; rcx=[rbp+0x778]; rax=[rbp+0x788]; jmp 0x66d4491 [V]. loc_66d448f: xor ecx,ecx [V]. loc_66d4491: lea rdx,&rbp+0x790; r8=[rbp+0x770]; [rbp+0x6D0]=r8; [rbp+0x6D8]=rcx [V]; [rbp+0x6E0]=xmm0 [V]; test rax,rax; je 0x66d44cd (eax=0); else lock inc dword [rax+8] [V]; rax=[rbp+0x788]; rcx=[rbp+0x6D8]; jmp 0x66d44cf [V]. loc_66d44cd: xor eax,eax [V]. loc_66d44cf: mov r8,[rbp+0x780] (continues phase 4 at 0x66d44d6). Next address: 0x66d44d6.

## Phase 4 — 0x66d44d6, 40 instructions [V]
```
66d44d6  mov [rbp+0x6E0],r8                            
66d44dd  mov [rbp+0x6E8],rax                           
66d44e4  movdqu xmm1,[rdx]                             
66d44e8  movdqa [rbp+0x6F0],xmm1                       
66d44f0  mov rdx,[rdx+0x10]                            
66d44f4  mov [rbp+0x700],rdx                           
66d44fb  movaps [rbp+0x710],xmm0                       
66d4502  test rcx,rcx                                  
66d4505  je short 0x66D451B                            ; -> loc_66d451b
66d4507  lock inc dword ptr [rcx+8]                    
66d450b  mov rdx,[rbp+0x6D8]                           
66d4512  mov rax,[rbp+0x6E8]                           
66d4519  jmp short 0x66D451D                           ; -> loc_66d451d

loc_66d451b:  ; from 66d4505
  66d451b  xor edx,edx                                   

loc_66d451d:  ; from 66d4519
  66d451d  lea rcx,[rbp+0x6F0]                           
  66d4524  mov r8,[rbp+0x6D0]                            
  66d452b  mov [rbp+0x710],r8                            
  66d4532  mov [rbp+0x718],rdx                           
  66d4539  movaps [rbp+0x720],xmm0                       
  66d4540  test rax,rax                                  
  66d4543  je short 0x66D4552                            ; -> loc_66d4552
  66d4545  lock inc dword ptr [rax+8]                    
  66d4549  mov rsi,[rbp+0x6E8]                           
  66d4550  jmp short 0x66D4554                           ; -> loc_66d4554

loc_66d4552:  ; from 66d4543
  66d4552  xor esi,esi                                   

loc_66d4554:  ; from 66d4550
  66d4554  mov rax,[rbp+0x6E0]                           
  66d455b  mov [rbp+0x720],rax                           
  66d4562  mov [rbp+0x728],rsi                           
  66d4569  movups xmm0,[rcx]                             
  66d456c  movaps [rbp+0x730],xmm0                       
  66d4573  mov rax,[rcx+0x10]                            
  66d4577  mov [rbp+0x740],rax                           
  66d457e  lea rdx,[rbp+0x360]                           
  66d4585  lea r8,[rbp+0x2D8]                            
  66d458c  lea r9,[rbp+0x2A8]                            
  66d4593  lea rax,[rbp+0x260]                           
  66d459a  mov [rsp+0x28],rdi                            
  66d459f  mov [rsp+0x20],rax                            
  66d45a4  lea rcx,[rbp+0xA50]                           
  66d45ab  call 0x6764400                                ; -> sub_6764400
```
// [V] Phase 4 continues nested value-struct build: [rbp+0x6E0]=r8, [rbp+0x6E8]=rax [V]; movdqu xmm1=[rdx]; [rbp+0x6F0]=xmm1; rdx=[rdx+0x10]; [rbp+0x700]=rdx [V]; [rbp+0x710]=xmm0 [V]; test rcx,rcx; je 0x66d451b (edx=0); else lock inc dword [rcx+8] refcount [V]; rdx=[rbp+0x6D8]; rax=[rbp+0x6E8]; jmp 0x66d451d [V]. loc_66d451b: xor edx,edx [V]. loc_66d451d: lea rcx,&rbp+0x6F0; r8=[rbp+0x6D0]; [rbp+0x710]=r8; [rbp+0x718]=rdx [V]; [rbp+0x720]=xmm0 [V]; test rax,rax; je 0x66d4552 (esi=0); else lock inc dword [rax+8] refcount [V]; rsi=[rbp+0x6E8]; jmp 0x66d4554 [V]. loc_66d4552: xor esi,esi [V]. loc_66d4554: rax=[rbp+0x6E0]; [rbp+0x720]=rax; [rbp+0x728]=rsi [V]; movups xmm0=[rcx]; [rbp+0x730]=xmm0; rax=[rcx+0x10]; [rbp+0x740]=rax ({ptr,len} from [rcx]) [V]; call 0x6764400(rcx=&rbp+0xA50, rdx=&rbp+0x360, r8=&rbp+0x2D8, r9=&rbp+0x2A8, [rsp+0x20]=&rbp+0x260, [rsp+0x28]=rdi) — same 6-arg struct-copy as phase 21 [V] (continues phase 5 after call). Next address: 0x66d45b0.

## Phase 5 — 0x66d45b0, 40 instructions [V]
```
66d45b0  nop                                            
66d45b1  mov eax,[rbp+0x3B8]                            
66d45b7  mov [rbp+0xC00],eax                            
66d45bd  movzx eax,word ptr [rbp+0x3C0]                 
66d45c4  mov [rbp+0xC08],ax                             
66d45cb  movzx eax,word ptr [rbp+0x3C8]                 
66d45d2  mov [rbp+0xC10],ax                             
66d45d9  xorps xmm0,xmm0                                
66d45dc  movups [rbp+0xC18],xmm0                        
66d45e3  mov rax,[rbp+0x718]                            
66d45ea  test rax,rax                                   
66d45ed  je short 0x66D4603                            ; -> loc_66d4603
66d45ef  lock inc dword ptr [rax+8]                     
66d45f3  mov rcx,[rbp+0x718]                            
66d45fa  mov rsi,[rbp+0x728]                            
66d4601  jmp short 0x66D4605                           ; -> loc_66d4605

loc_66d4603:  ; from 66d45ed
  66d4603  xor ecx,ecx                                   

loc_66d4605:  ; from 66d4601
  66d4605  lea rax,[rbp+0x730]                           
  66d460c  mov rdx,[rbp+0x710]                           
  66d4613  mov [rbp+0xC18],rdx                           
  66d461a  mov [rbp+0xC20],rcx                           
  66d4621  movups [rbp+0xC28],xmm0                       
  66d4628  test rsi,rsi                                  
  66d462b  je short 0x66D463A                            ; -> loc_66d463a
  66d462d  lock inc dword ptr [rsi+8]                    
  66d4631  mov rcx,[rbp+0x728]                           
  66d4638  jmp short 0x66D463C                           ; -> loc_66d463c

loc_66d463a:  ; from 66d462b
  66d463a  xor ecx,ecx                                   

loc_66d463c:  ; from 66d4638
  66d463c  mov rdx,[rbp+0x720]                           
  66d4643  mov [rbp+0xC28],rdx                           
  66d464a  mov [rbp+0xC30],rcx                           
  66d4651  movups xmm0,[rax]                             
  66d4654  movups [rbp+0xC38],xmm0                       
  66d465b  mov rax,[rax+0x10]                            
  66d465f  mov [rbp+0xC48],rax                           
  66d4666  lea rcx,[rbp+0x7E0]                           
  66d466d  lea rdx,[rbp+0xA50]                           
  66d4674  call 0x6761590                                ; -> sub_6761590
  66d4679  nop                                           
  66d467a  mov eax,[rbp+0xC00]                           
```
// [V] Phase 5 initializes context struct at [rbp+0xC00..0xC48]: [0xC00]=eax from [rbp+0x3B8] [V]; [0xC08]=ax from [rbp+0x3C0] [V]; [0xC10]=ax from [rbp+0x3C8] [V]; xorps xmm0,xmm0; [rbp+0xC18]=xmm0 zero [V]; then copies nested value struct from [rbp+0x710..0x740]: rax=[rbp+0x718]; test rax,rax; je 0x66d4603 (ecx=0); else lock inc dword [rax+8] refcount [V]; rcx=[rbp+0x718]; rsi=[rbp+0x728]; jmp 0x66d4605 [V]. loc_66d4603: xor ecx,ecx [V]. loc_66d4605: lea rax,&rbp+0x730; rdx=[rbp+0x710]; [rbp+0xC18]=rdx (ptr) [V]; [rbp+0xC20]=rcx ([rbp+0x718] refcounted ptr or 0) [V]; [rbp+0xC28]=xmm0 zero [V]; test rsi,rsi; je 0x66d463a (ecx=0); else lock inc dword [rsi+8] refcount [V]; rcx=[rbp+0x728]; jmp 0x66d463c [V]. loc_66d463a: xor ecx,ecx [V]. loc_66d463c: rdx=[rbp+0x720]; [rbp+0xC28]=rdx [V]; [rbp+0xC30]=rcx ([rbp+0x728]) [V]; movups xmm0=[rax] ([rbp+0x730], 16 bytes) [V]; [rbp+0xC38]=xmm0; rax=[rax+0x10] ([rbp+0x740]); [rbp+0xC48]=rax ({ptr,len} tail) [V]; lea rcx,&rbp+0x7E0; lea rdx,&rbp+0xA50; call 0x6761590(rcx=&rbp+0x7E0 index slot, rdx=&rbp+0xA50 value struct) [V]; nop; eax=[rbp+0xC00] type tag (continues phase 6 — likely type dispatch). Next address: 0x66d4680.

## Phase 6 — 0x66d4680, 40 instructions [V]
```
66d4680  mov [rbp+0x990],eax                           
66d4686  movzx eax,word ptr [rbp+0xC08]                
66d468d  mov [rbp+0x998],ax                            
66d4694  movzx eax,word ptr [rbp+0xC10]                
66d469b  mov [rbp+0x9A0],ax                            
66d46a2  xorps xmm0,xmm0                               
66d46a5  movups [rbp+0x9A8],xmm0                       
66d46ac  mov rax,[rbp+0xC20]                           
66d46b3  test rax,rax                                  
66d46b6  je short 0x66D46C5                            ; -> loc_66d46c5
66d46b8  lock inc dword ptr [rax+8]                    
66d46bc  mov rcx,[rbp+0xC20]                           
66d46c3  jmp short 0x66D46C7                           ; -> loc_66d46c7

loc_66d46c5:  ; from 66d46b6
  66d46c5  xor ecx,ecx                                   

loc_66d46c7:  ; from 66d46c3
  66d46c7  lea rax,[rbp+0xC38]                           
  66d46ce  mov r8,[rbp+0xC18]                            
  66d46d5  mov rdx,[rbp+0xC30]                           
  66d46dc  mov [rbp+0x9A8],r8                            
  66d46e3  mov [rbp+0x9B0],rcx                           
  66d46ea  movups [rbp+0x9B8],xmm0                       
  66d46f1  test rdx,rdx                                  
  66d46f4  je short 0x66D4756                            ; -> loc_66d4756
  66d46f6  lock inc dword ptr [rdx+8]                    
  66d46fa  mov rdi,[rbp+0xC30]                           
  66d4701  movups xmm0,[rbp+0xC28]                       
  66d4708  movups [rbp+0x9B8],xmm0                       
  66d470f  movups xmm0,[rax]                             
  66d4712  movups [rbp+0x9C8],xmm0                       
  66d4719  mov rax,[rax+0x10]                            
  66d471d  mov [rbp+0x9D8],rax                           
  66d4724  test rdi,rdi                                  
  66d4727  je short 0x66D4784                            ; -> loc_66d4784
  66d4729  lock dec dword ptr [rdi+8]                    
  66d472d  jne short 0x66D4784                           ; -> loc_66d4784
  66d472f  mov rax,[rdi]                                 
  66d4732  mov rax,[rax]                                 
  66d4735  mov rcx,rdi                                   
  66d4738  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d473e  lock dec dword ptr [rdi+0xC]                  
  66d4742  jne short 0x66D4784                           ; -> loc_66d4784
```
// [V] Phase 6 continues context build at [rbp+0x990..0x9D8]: [0x990]=eax tag from [rbp+0xC00] [V]; [0x998]=ax from [rbp+0xC08] [V]; [0x9A0]=ax from [rbp+0xC10] [V]; xorps xmm0,xmm0; [rbp+0x9A8]=xmm0 zero [V]; moves nested value struct from [rbp+0xC18..0xC48]: rax=[rbp+0xC20]; test rax,rax; je 0x66d46c5 (ecx=0); else lock inc dword [rax+8] refcount [V]; rcx=[rbp+0xC20]; jmp 0x66d46c7 [V]. loc_66d46c5: xor ecx,ecx [V]. loc_66d46c7: lea rax,&rbp+0xC38; r8=[rbp+0xC18]; rdx=[rbp+0xC30]; [rbp+0x9A8]=r8 (ptr) [V]; [rbp+0x9B0]=rcx ([rbp+0xC20] refcounted ptr or 0) [V]; [rbp+0x9B8]=xmm0 zero [V]; test rdx,rdx; je 0x66d4756; else lock inc dword [rdx+8] refcount [V]; rdi=[rbp+0xC30]; movups xmm0=[rbp+0xC28]; [rbp+0x9B8]=xmm0; movups xmm0=[rax] ([rbp+0xC38], 16 bytes) [V]; [rbp+0x9C8]=xmm0; rax=[rax+0x10] ([rbp+0xC48]); [rbp+0x9D8]=rax [V]; then releases OLD value at rdi=[rbp+0xC30]: test rdi,rdi; je 0x66d4784; lock dec dword [rdi+8]; jne 0x66d4784 (refcount nonzero → skip destroy); else rax=[rdi]; rax=[rax] vtable[0]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rdi+0xC]; jne 0x66d4784 (continues phase 7). Next address: 0x66d4744.

## Phase 7 — 0x66d4744, 40 instructions [V]
```
66d4744  mov rax,[rdi]                                 
66d4747  mov rax,[rax+8]                               
66d474b  mov rcx,rdi                                   
66d474e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d4754  jmp short 0x66D4784                           ; -> loc_66d4784
66d4756  mov rcx,[rbp+0xC28]                           
66d475d  mov [rbp+0x9B8],rcx                           
66d4764  mov qword ptr [rbp+0x9C0],0                   
66d476f  movups xmm0,[rax]                             
66d4772  movups [rbp+0x9C8],xmm0                       
66d4779  mov rax,[rax+0x10]                            
66d477d  mov [rbp+0x9D8],rax                           

loc_66d4784:  ; from 66d4754
  66d4784  mov rdi,[rbp+0xC20]                           
  66d478b  test rdi,rdi                                  
  66d478e  je short 0x66D47BB                            ; -> loc_66d47bb
  66d4790  lock dec dword ptr [rdi+8]                    
  66d4794  jne short 0x66D47BB                           ; -> loc_66d47bb
  66d4796  mov rax,[rdi]                                 
  66d4799  mov rax,[rax]                                 
  66d479c  mov rcx,rdi                                   
  66d479f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d47a5  lock dec dword ptr [rdi+0xC]                  
  66d47a9  jne short 0x66D47BB                           ; -> loc_66d47bb
  66d47ab  mov rax,[rdi]                                 
  66d47ae  mov rax,[rax+8]                               
  66d47b2  mov rcx,rdi                                   
  66d47b5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_66d47bb:  ; from 66d478e, 66d4794, 66d47a9
  66d47bb  lea rcx,[rbp+0xA50]                           
  66d47c2  call 0x67627D0                                ; -> sub_67627d0
  66d47c7  mov rdi,[rbp+0x728]                           
  66d47ce  test rdi,rdi                                  
  66d47d1  je short 0x66D47FE                            ; -> loc_66d47fe
  66d47d3  lock dec dword ptr [rdi+8]                    
  66d47d7  jne short 0x66D47FE                           ; -> loc_66d47fe
  66d47d9  mov rax,[rdi]                                 
  66d47dc  mov rax,[rax]                                 
  66d47df  mov rcx,rdi                                   
  66d47e2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d47e8  lock dec dword ptr [rdi+0xC]                  
  66d47ec  jne short 0x66D47FE                           ; -> loc_66d47fe
```
// [V] Phase 7 completes destruction of replaced values: fallthrough from phase-6 je (0x66d4784): mov rax,[rdi]; rax=[rax+8]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040) [V]; jmp 0x66d4784 [V]. Alternate path (0x66d4756, when [rbp+0xC30] was null): mov rcx=[rbp+0xC28]; [rbp+0x9B8]=rcx; mov qword [rbp+0x9C0],0; movups xmm0=[rax] ([rbp+0xC38]); [rbp+0x9C8]=xmm0; rax=[rax+0x10] ([rbp+0xC48]); [rbp+0x9D8]=rax [V]. Join loc_66d4784: release old value rdi=[rbp+0xC20]: test rdi,rdi; je 0x66d47bb; lock dec dword [rdi+8]; jne 0x66d47bb (skip destroy); else rax=[rdi]; rax=[rax] vtable[0]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rdi+0xC]; jne 0x66d47bb; else rax=[rdi]; rax=[rax+8]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — dtor+free double call pattern [V]. loc_66d47bb: lea rcx,&rbp+0xA50; call 0x67627D0(rcx=&rbp+0xA50) value teardown [V] (7th call) [V]; release rdi=[rbp+0x728]: test rdi,rdi; je 0x66d47fe; lock dec dword [rdi+8]; jne 0x66d47fe; else rax=[rdi]; rax=[rax]; rcx=rdi; call qword ptr [0xF99FFA0] destroy [V]; lock dec dword [rdi+0xC]; jne 0x66d47fe (continues phase 8). Next address: 0x66d47ee.

## Phase 8 — 0x66d47ee, 40 instructions [V]
```
66d47ee  mov rax,[rdi]                                 
66d47f1  mov rax,[rax+8]                               
66d47f5  mov rcx,rdi                                   
66d47f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d47fe  mov rdi,[rbp+0x718]                           
66d4805  test rdi,rdi                                  
66d4808  je short 0x66D4835                            ; -> loc_66d4835
66d480a  lock dec dword ptr [rdi+8]                    
66d480e  jne short 0x66D4835                           ; -> loc_66d4835
66d4810  mov rax,[rdi]                                 
66d4813  mov rax,[rax]                                 
66d4816  mov rcx,rdi                                   
66d4819  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d481f  lock dec dword ptr [rdi+0xC]                  
66d4823  jne short 0x66D4835                           ; -> loc_66d4835
66d4825  mov rax,[rdi]                                 
66d4828  mov rax,[rax+8]                               
66d482c  mov rcx,rdi                                   
66d482f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_66d4835:  ; from 66d4808, 66d480e, 66d4823
  66d4835  mov rdi,[rbp+0x6E8]                           
  66d483c  test rdi,rdi                                  
  66d483f  je short 0x66D486C                            ; -> loc_66d486c
  66d4841  lock dec dword ptr [rdi+8]                    
  66d4845  jne short 0x66D486C                           ; -> loc_66d486c
  66d4847  mov rax,[rdi]                                 
  66d484a  mov rax,[rax]                                 
  66d484d  mov rcx,rdi                                   
  66d4850  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4856  lock dec dword ptr [rdi+0xC]                  
  66d485a  jne short 0x66D486C                           ; -> loc_66d486c
  66d485c  mov rax,[rdi]                                 
  66d485f  mov rax,[rax+8]                               
  66d4863  mov rcx,rdi                                   
  66d4866  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_66d486c:  ; from 66d483f, 66d4845, 66d485a
  66d486c  mov rdi,[rbp+0x6D8]                           
  66d4873  test rdi,rdi                                  
  66d4876  je short 0x66D48A3                            ; -> loc_66d48a3
  66d4878  lock dec dword ptr [rdi+8]                    
  66d487c  jne short 0x66D48A3                           ; -> loc_66d48a3
  66d487e  mov rax,[rdi]                                 
```
// [V] Phase 8 continues the release cascade: finishes rdi=[rbp+0x728] teardown from phase 7 — mov rax,[rdi]; rax=[rax+8]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040) [V]. Release rdi=[rbp+0x718]: test rdi,rdi; je 0x66d4835; lock dec dword [rdi+8]; jne 0x66d4835 (skip destroy); else rax=[rdi]; rax=[rax] vtable[0]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rdi+0xC]; jne 0x66d4835; else rax=[rdi]; rax=[rax+8]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — dtor+free double call [V]. Release rdi=[rbp+0x6E8]: identical dtor+free pattern via loc_66d4835/loc_66d486c [V]; release rdi=[rbp+0x6D8]: test rdi,rdi; je 0x66d48a3; lock dec dword [rdi+8]; jne 0x66d48a3; else rax=[rdi] (continues phase 9 — vtable[0] dtor call). Next address: 0x66d4881.

## Phase 9 — 0x66d4881, 40 instructions [V]
```
66d4881  mov rax,[rax]                                  
66d4884  mov rcx,rdi                                   
66d4887  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d488d  lock dec dword ptr [rdi+0xC]                  
66d4891  jne short 0x66D48A3                           ; -> loc_66d48a3
66d4893  mov rax,[rdi]                                 
66d4896  mov rax,[rax+8]                               
66d489a  mov rcx,rdi                                   
66d489d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d48a3  mov rdi,[rbx+0x10]                            
66d48a7  lea rbx,[0xF2BE898]                           ; [data_f2be898]
66d48ae  mov [rbp+0xA50],rbx                           
66d48b5  lea rsi,[rbp+0xA58]                           
66d48bc  lea rdx,[rbp+0x7E0]                           
66d48c3  mov rcx,rsi                                   
66d48c6  call 0x6761590                                ; -> sub_6761590
66d48cb  nop                                           
66d48cc  mov eax,[rbp+0x990]                           
66d48d2  mov [rbp+0xC08],eax                           
66d48d8  movzx eax,word ptr [rbp+0x998]                
66d48df  mov [rbp+0xC10],ax                            
66d48e6  movzx eax,word ptr [rbp+0x9A0]                
66d48ed  mov [rbp+0xC18],ax                            
66d48f4  xorps xmm0,xmm0                               
66d48f7  movups [rbp+0xC20],xmm0                       
66d48fe  mov rax,[rbp+0x9B0]                           
66d4905  test rax,rax                                  
66d4908  je short 0x66D4917                            ; -> loc_66d4917
66d490a  lock inc dword ptr [rax+8]                    
66d490e  mov rcx,[rbp+0x9B0]                           
66d4915  jmp short 0x66D4919                           ; -> loc_66d4919
66d4917  xor ecx,ecx                                   
66d4919  lea rax,[rbp+0xC08]                           
66d4920  lea r9,[rbp+0xC10]                            
66d4927  lea r8,[rbp+0xC18]                            
66d492e  lea rdx,[rbp+0xC20]                           
66d4935  mov r11,[rbp+0x9A8]                           
66d493c  mov r10,[rbp+0x9C0]                           
66d4943  mov [rbp+0xC20],r11                           
66d494a  mov [rbp+0xC28],rcx
```
// [V] Phase 9 finishes rdi=[rbp+0x6D8] teardown from phase 8: mov rax,[rax] vtable[0]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rdi+0xC]; jne short 0x66d48a3; else rax=[rdi]; rax=[rax+8]; rcx=rdi; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — completes dtor+free double call [V]. loc_66d48a3: rdi=[rbx+0x10]; rbx=lea [0xF2BE898] ([data_f2be898] global const address) [V]; [rbp+0xA50]=rbx overwrites value-struct slot [V]; lea rsi,&rbp+0xA58; lea rdx,&rbp+0x7E0; mov rcx,rsi; call 0x6761590(rcx=&rbp+0xA58, rdx=&rbp+0x7E0) [V] — same callee as phase 5 with rcx/rdx swapped; nop. Then builds nested context struct at [rbp+0xC08..]: [0xC08]=eax from [rbp+0x990] [V]; [0xC10]=ax from [rbp+0x998] [V]; [0xC18]=ax from [rbp+0x9A0] [V]; xorps xmm0,xmm0; [rbp+0xC20]=xmm0 zero [V]; rax=[rbp+0x9B0]; test rax,rax; je 0x66d4917 (ecx=0); else lock inc dword [rax+8] refcount [V]; rcx=[rbp+0x9B0]; jmp 0x66d4919 [V]. loc_66d4917: xor ecx,ecx [V]. loc_66d4919: lea rax,&rbp+0xC08; lea r9,&rbp+0xC10; lea r8,&rbp+0xC18; lea rdx,&rbp+0xC20; r11=[rbp+0x9A8]; r10=[rbp+0x9C0]; [rbp+0xC20]=r11 (ptr from [rbp+0x9A8]) [V]; [rbp+0xC28]=rcx ([rbp+0x9B0] refcounted ptr or 0) [V] — continues phase 10 at [rbp+0xC30]/[rbp+0xC38]/[rbp+0xC48] tail. Next address: 0x66d4951.
