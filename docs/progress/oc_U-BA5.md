# Unit U-BA5 — bodyActor function 0x66d0a00 (1.26.62.01), continued from 0x66d4951

## NEXT [current]
Resume at RVA 0x66d5195 (after phase 20, instructions 0x66d50e0..0x66d5191; next instruction at 0x66d5195 — continuation of field-parse case). Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d5195 40`
Scope: 20 consecutive phases of 40 instructions each (800 instructions) from 0x66d4951; 14 of 20 done (560 instructions). Unit U-BA5 ends here per brief (phases 19-20 written). On any `(bad)` line, restart the phase at the next address until the phase start is on a boundary. Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Phase 14 — 0x66d4c91, 40 instructions [V]
```
66d4c91  mov rax,[rax]                                 
66d4c94  mov rcx,rbx                                   
66d4c97  call qword ptr [0xF99FFA0]                    
66d4c9d  lock dec dword ptr [rbx+0xC]                  
66d4ca1  jne short 0x66D4CB3                           
66d4ca3  mov rax,[rbx]                                 
66d4ca6  mov rax,[rax+8]                               
66d4caa  mov rcx,rbx                                   
66d4cad  call qword ptr [0xF99FFA0]                    

loc_66d4cb3:  ; from 66d4ca1
  66d4cb3  mov rax,[rbp+0xD70]                           
  66d4cba  mov r8,[rax+0x3B8]                            
  66d4cc1  mov rdx,[r15]                                 
  66d4cc4  mov [rsp+0x20],r12d                           
  66d4cc9  mov dword ptr [rsp+0x30],0                    
  66d4cd1  mov dword ptr [rsp+0x28],0                    
  66d4cd9  lea rcx,[rbp+0x470]                           
  66d4ce0  lea r9,[rbp+0x420]                            
  66d4ce7  call 0x66A0F60                                
  66d4cec  nop                                           
  66d4ced  movaps xmm0,[rbp+0x470]                       
  66d4cf4  movaps xmm1,[rbp+0x480]                       
  66d4cfb  mov qword ptr [rbp+0x478],0                   
  66d4d06  movaps [rbp+0xA50],xmm0                       
  66d4d0d  xorps xmm0,xmm0                               
  66d4d10  movaps [rbp+0x480],xmm0                       
  66d4d17  movaps [rbp+0xA60],xmm1                       
  66d4d1e  mov rax,[rbp+0x490]                           
  66d4d25  mov [rbp+0xA70],rax                           
  66d4d2c  mov byte ptr [rbp+0xA88],0xFF                 
  66d4d33  movzx eax,byte ptr [rbp+0x4A8]                
  66d4d3a  cmp rax,3                                     
  66d4d3e  ja short 0x66D4DB0                            
  66d4d40  lea rcx,[rbp+0xA78]                           
  66d4d47  lea rdx,[0xF2BFAE0]                           
  66d4d4e  movsxd r8,[rdx+rax*4]                         
  66d4d52  add r8,rdx                                    
  66d4d55  jmp r8                                        
```
// [V] Phase 14 finishes release of rbx (=[rbp+0x428] old value) from phase 13: fallthrough `mov rax,[rax]` vtable[0] at 0x66d4c91; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rbx+0xC]; jne 0x66d4cb3; else rax=[rbx]; rax=[rax+8]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — dtor+free on [rbp+0x428] [V]. loc_66d4cb3: rax=[rbp+0xD70]; r8=[rax+0x3B8]; rdx=[r15]; [rsp+0x20]=r12d; [rsp+0x30]=0; [rsp+0x28]=0; lea rcx,&rbp+0x470; lea r9,&rbp+0x420; call 0x66A0F60(rcx=&rbp+0x470 out, rdx=[r15], r8=[rbp+0xD70+0x3B8], r9=&rbp+0x420, [rsp+0x28]=0, [rsp+0x30]=0, [rsp+0x20]=r12d) [V] — new callee sub_66a0f60, signature [I] (fills [rbp+0x470..0x4A8] result struct). Then rebuilds value struct at [rbp+0xA50..0xA88]: movaps xmm0=[rbp+0x470]; xmm1=[rbp+0x480]; [rbp+0x478]=0; [rbp+0xA50]=xmm0; [rbp+0x480]=xmm0 zero; [rbp+0xA60]=xmm1; rax=[rbp+0x490]; [rbp+0xA70]=rax; [rbp+0xA88]=0xFF [V]. Type dispatch: eax=byte [rbp+0x4A8]; cmp rax,3; ja 0x66d4db0 default [V]; lea rcx,&rbp+0xA78; lea rdx,[0xF2BFAE0] jump-table base [V]; movsxd r8,[rdx+rax*4]; add r8,rdx; jmp r8 [V] — 4-case jump table [0xF2BFAE0]: case 0→0x66d4d58, case 1→0x66d4d68, case 2→0x66d4d77, case 3→? [?] (not yet located; cases 0-2 verified by disassembly). Next address: 0x66d4d58 (case 0).

## Phase 12 — 0x66d4b40, 40 instructions [V]
```
66d4b40  mov rax,[rax+8]                               
66d4b44  mov rcx,rsi                                   
66d4b47  call qword ptr [0xF99FFA0]                    
66d4b4d  mov rsi,[rbp+0x7B8]                           
66d4b54  test rsi,rsi                                  
66d4b57  je short 0x66D4B84                            
66d4b59  lock dec dword ptr [rsi+8]                    
66d4b5d  jne short 0x66D4B84                           
66d4b5f  mov rax,[rsi]                                 
66d4b62  mov rax,[rax]                                 
66d4b65  mov rcx,rsi                                   
66d4b68  call qword ptr [0xF99FFA0]                    
66d4b6e  lock dec dword ptr [rsi+0xC]                  
66d4b72  jne short 0x66D4B84                           
66d4b74  mov rax,[rsi]                                 
66d4b77  mov rax,[rax+8]                               
66d4b7b  mov rcx,rsi                                   
66d4b7e  call qword ptr [0xF99FFA0]                    

loc_66d4b84:  ; from 66d4b57, 66d4b5d, 66d4b72
  66d4b84  lea rcx,[rbp+0x208]                           
  66d4b8b  call 0x67627D0                                
  66d4b90  mov rsi,[rbp+0x768]                           
  66d4b97  test rsi,rsi                                  
66d4b9a  je 0x66D6108                                  
66d4ba0  lock dec dword ptr [rsi+8]                    
66d4ba4  jne 0x66D6108                                 
66d4baa  mov rax,[rsi]                                 
66d4bad  mov rax,[rax]                                 
66d4bb0  mov rcx,rsi                                   
66d4bb3  call qword ptr [0xF99FFA0]                    
66d4bb9  lock dec dword ptr [rsi+0xC]                  
66d4bbd  jne 0x66D6108                                 
66d4bc3  mov rax,[rsi]                                 
66d4bc6  mov rax,[rax+8]                               
66d4bca  mov rcx,rsi                                   
66d4bcd  call qword ptr [0xF99FFA0]                    
66d4bd3  jmp 0x66D6108                                 
```
// [V] Phase 12 finishes release of rsi=[rbp+0x778] from phase 11: fallthrough `mov rax,[rax+8]` at 0x66d4b40; rcx=rsi; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — completes dtor+free on [rbp+0x778]. Release rsi=[rbp+0x7B8]: test rsi,rsi; je 0x66d4b84; lock dec dword [rsi+8]; jne 0x66d4b84; else rax=[rsi]; rax=[rax] vtable[0]; rcx=rsi; call qword ptr [0xF99FFA0] destroy [V]; lock dec dword [rsi+0xC]; jne 0x66d4b84; else rax=[rsi]; rax=[rax+8]; rcx=rsi; call qword ptr [0xF99FFA0] free [V] — dtor+free on [rbp+0x7B8] [V]. loc_66d4b84: lea rcx,&rbp+0x208; call 0x67627D0(rcx=&rbp+0x208) value teardown [V] (9th call-0x67627D0); then release rsi=[rbp+0x768]: test rsi,rsi; je 0x66d6108 fallback; lock dec dword [rsi+8]; jne 0x66d6108; else rax=[rsi]; rax=[rax] vtable[0]; rcx=rsi; call qword ptr [0xF99FFA0] destroy [V]; lock dec dword [rsi+0xC]; jne 0x66d6108; else rax=[rsi]; rax=[rax+8]; rcx=rsi; call qword ptr [0xF99FFA0] free [V] — dtor+free on [rbp+0x768] [V]; jmp 0x66d6108 fallback [V]. New basic block at 0x66d4bd8: `add rdx,rax; cmp rcx,rdx; jae 0x66d4c0e; sub ecx,eax` — a pointer/size range check not part of the release cascade [V, meaning I]. Next address: 0x66d4bd8.

## Phase 11 — 0x66d4aac, 40 instructions [V]
```
66d4aac  jne short 0x66D4AD3                           
66d4aae  mov rax,[rsi]                                 
66d4ab1  mov rax,[rax]                                 
66d4ab4  mov rcx,rsi                                   
66d4ab7  call qword ptr [0xF99FFA0]                    
66d4abd  lock dec dword ptr [rsi+0xC]                  
66d4ac1  jne short 0x66D4AD3                           
66d4ac3  mov rax,[rsi]                                 
66d4ac6  mov rax,[rax+8]                               
66d4aca  mov rcx,rsi                                   
66d4acd  call qword ptr [0xF99FFA0]                    

loc_66d4ad3:  ; from 66d4aac, 66d4ac1
  66d4ad3  lea rcx,[rbp+0x7E0]                           
  66d4ada  call 0x67627D0                                
  66d4adf  mov rsi,[rbp+0x788]                           
  66d4ae6  test rsi,rsi                                  
  66d4ae9  je short 0x66D4B16                            
  66d4aeb  lock dec dword ptr [rsi+8]                    
  66d4aef  jne short 0x66D4B16                           
  66d4af1  mov rax,[rsi]                                 
  66d4af4  mov rax,[rax]                                 
  66d4af7  mov rcx,rsi                                   
  66d4afa  call qword ptr [0xF99FFA0]                    
  66d4b00  lock dec dword ptr [rsi+0xC]                  
  66d4b04  jne short 0x66D4B16                           
  66d4b06  mov rax,[rsi]                                 
  66d4b09  mov rax,[rax+8]                               
  66d4b0d  mov rcx,rsi                                   
  66d4b10  call qword ptr [0xF99FFA0]                    

loc_66d4b16:  ; from 66d4ae9, 66d4aef, 66d4b04
  66d4b16  mov rsi,[rbp+0x778]                           
  66d4b1d  test rsi,rsi                                  
  66d4b20  je short 0x66D4B4D                            
  66d4b22  lock dec dword ptr [rsi+8]                    
  66d4b26  jne short 0x66D4B4D                           
  66d4b28  mov rax,[rsi]                                 
  66d4b2b  mov rax,[rax]                                 
  66d4b2e  mov rcx,rsi                                   
  66d4b31  call qword ptr [0xF99FFA0]                    
  66d4b37  lock dec dword ptr [rsi+0xC]                  
  66d4b3b  jne short 0x66D4B4D                           
  66d4b3d  mov rax,[rsi]                                 
```
// [V] Phase 11 is the tail of the release cascade on rsi=[rbp+0x9B0] begun in phase 10: fallthrough from `lock dec dword [rsi+8]` at 0x66d4aa8; nonzero → loc_66d4ad3 (skip destroy) [V]; else rax=[rsi]; rax=[rax] vtable[0]; rcx=rsi; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rsi+0xC]; jne 0x66d4ad3; else rax=[rsi]; rax=[rax+8]; rcx=rsi; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — dtor+free double call on [rbp+0x9B0] [V]. loc_66d4ad3: lea rcx,&rbp+0x7E0; call 0x67627D0(rcx=&rbp+0x7E0) value teardown [V] (8th call-0x67627D0); then release rsi=[rbp+0x788]: test rsi,rsi; je 0x66d4b16; lock dec dword [rsi+8]; jne 0x66d4b16; else rax=[rsi]; rax=[rax] vtable[0]; rcx=rsi; call qword ptr [0xF99FFA0] destroy [V]; lock dec dword [rsi+0xC]; jne 0x66d4b16; else rax=[rsi]; rax=[rax+8]; rcx=rsi; call qword ptr [0xF99FFA0] free [V] — dtor+free on [rbp+0x788] [V]. loc_66d4b16: release rsi=[rbp+0x778]: test rsi,rsi; je 0x66d4b4d; lock dec dword [rsi+8]; jne 0x66d4b4d; else rax=[rsi]; rax=[rax] vtable[0]; rcx=rsi; call qword ptr [0xF99FFA0] destroy [V]; lock dec dword [rsi+0xC]; jne 0x66d4b4d; else rax=[rsi] (continues phase 12 — vtable[0]+free at 0x66d4b40). Next address: 0x66d4b40.

## Context [V]
- Continuation of U-BA4 (docs/progress/oc_U-BA4.md), phases 1-9 covering 0x66d42ae..0x66d494a of bodyActor 0x66d0a00.
- State carried in (from U-BA4): nested context struct at [rbp+0xC00..0xC48] (type tag [0xC00], [0xC08], [0xC10], [0xC18], ptr [0xC20], refcounted ptr [0xC28], tail [0xC38]/[0xC48]); nested value struct at [rbp+0x710..0x740]; index slot [rbp+0x7E0] (0x30-stride, callee 0x6761590); value struct at [rbp+0xA50..0xA5C]; out ctx [rbp+0xCE0]; work buffer [rbp+0x400]/[rbp+0x410]; node list walked via [r12] with sentinel r13=[rbp+0xA58]; node data ptr [r12+0x10]; callee 0x66D93C0(rcx=&rbp+0xCE0, rdx=&rbp+0x400, r8=&rbp+0x7E0, r9=r12+0x18); sub_e935700 for small/oversized results; indirect call qword ptr [0xF9A8C78] at loop exit; TLS gate pattern eax=[data global]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg <fallback> [V, U-BA3 phases 1-26].
- Callee inventory (U-BA3): 0xE935700 (free), 0x5679DB0 (index registration), 0xBBD7C70, 0x4DEDD00, 0x66B2B30, 0x6698060, 0x6694660, 0x5AC2420, 0x67612A0, 0x6761590, 0x6761970, 0x67627D0, 0x6762900, 0x6764400, 0x6764990, 0x6764400, 0x6765C00, 0x6765020, qword ptr [0xF99FFA0]=sub_eea6040 (alloc/free), qword ptr [0xF9A8C78].
- Fallback targets seen: 0x66D64F8, 0x66D6108, 0x66D6187, 0x66D6ADD, 0x66D72A0, 0x66d2d40, 0x66d438e/0x66d4390.
- Roadata strings seen: [0xF5C6AD8] "UIStructureVolumeCapture texture", [0xF5C6AE8] "eCapture texture"; GUID const 0x8D29EAE11B764987; jump tables [0xF2BFB00] (4 entries) and [0xF2BE878].

## Phase 15 — 0x66d4d58, 40 instructions [V]
```
66d4d58  mov rcx,[rbp+0x498]                           
66d4d5f  mov [rbp+0xA78],rcx                           
66d4d66  jmp short 0x66D4DAA                           ; -> loc_66d4daa
66d4d68  lea rdx,[rbp+0x498]                           
66d4d6f  movups xmm0,[rdx]                             
66d4d72  movups [rcx],xmm0                             
66d4d75  jmp short 0x66D4DAA                           ; -> loc_66d4daa
66d4d77  movups [rcx],xmm0                             
66d4d7a  mov rcx,[rbp+0x4A0]                           
66d4d81  test rcx,rcx                                  
66d4d84  je short 0x66D4D93                            ; -> loc_66d4d93
66d4d86  lock inc dword ptr [rcx+8]                    
66d4d8a  mov rcx,[rbp+0x4A0]                           
66d4d91  jmp short 0x66D4D95                           ; -> loc_66d4d95

loc_66d4d93:  ; from 66d4d84
  66d4d93  xor ecx,ecx                                   

loc_66d4d95:  ; from 66d4d91
  66d4d95  mov rdx,[rbp+0x498]                           
  66d4d9c  mov [rbp+0xA78],rdx                           
  66d4da3  mov [rbp+0xA80],rcx                           

loc_66d4daa:  ; from 66d4d66, 66d4d75
  66d4daa  mov [rbp+0xA88],al                            
  66d4db0  mov rax,[rbp+0x4C0]                           
  66d4db7  mov [rbp+0xAA0],rax                           
  66d4dbe  movaps xmm0,[rbp+0x4B0]                       
  66d4dc5  movaps [rbp+0xA90],xmm0                       
  66d4dcc  lea rcx,[rbp+0x930]                           
  66d4dd3  lea rdx,[rbp+0xA50]                           
  66d4dda  call 0x67D0750                                ; -> sub_67d0750
  66d4ddf  cmp byte ptr [rbp+0xA88],3                    
  66d4de6  jne short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4de8  mov rbx,[rbp+0xA80]                           
  66d4def  test rbx,rbx                                  
  66d4df2  je short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4df4  lock dec dword ptr [rbx+8]                    
  66d4df8  jne short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4dfa  mov rax,[rbx]                                 
  66d4dfd  mov rax,[rax]                                 
  66d4e00  mov rcx,rbx                                   
  66d4e03  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4e09  lock dec dword ptr [rbx+0xC]                  
  66d4e0d  jne short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4e0f  mov rax,[rbx]                                 
```
// [V] Phase 15 is jump-table case 0 (type tag 0 at [rbp+0x4A8]): rcx=[rbp+0x498]; [rbp+0xA78]=rcx [V]; jmp 0x66d4daa join [V]. Case 1 at 0x66d4d68: lea rdx,&rbp+0x498; movups xmm0=[rdx]; movups [rcx]=xmm0; jmp 0x66d4daa [V]. Case 2 at 0x66d4d77: movups [rcx],xmm0; rcx=[rbp+0x4A0]; test rcx,rcx; je 0x66d4d93 (ecx=0); else lock inc dword [rcx+8] refcount [V]; rcx=[rbp+0x4A0]; jmp 0x66d4d95 [V]. loc_66d4d93: xor ecx,ecx [V]. loc_66d4d95: rdx=[rbp+0x498]; [rbp+0xA78]=rdx; [rbp+0xA80]=rcx [V]. Join loc_66d4daa: [rbp+0xA88]=al (type tag) [V]; rax=[rbp+0x4C0]; [rbp+0xAA0]=rax [V]; movaps xmm0=[rbp+0x4B0]; [rbp+0xA90]=xmm0 [V]; lea rcx,&rbp+0x930; lea rdx,&rbp+0xA50; call 0x67D0750(rcx=&rbp+0x930, rdx=&rbp+0xA50) [V] — new callee sub_67d0750 [V]. cmp byte [rbp+0xA88],3; jne 0x66d4e1f (skip case-3 cleanup) [V]. rbx=[rbp+0xA80]; test rbx,rbx; je 0x66d4e1f; lock dec dword [rbx+8]; jne 0x66d4e1f; else rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rbx+0xC]; jne 0x66d4e1f (continues phase 16 — free call at 0x66d4e0f→0x66d4e12). Jump table (resolved via raw rdata at 0xF2BFAE0): case 0→0x66d4d58, case 1→0x66d4d68, case 2→0x66d4d77, case 3→0x66d4daa [V]. Next address: 0x66d4e12 (after 0x66d4e0f free-call tail).

## Phase 16 — 0x66d4e12, 40 instructions [V]
```
66d4e12  mov rax,[rax+8]                               
66d4e16  mov rcx,rbx                                   
66d4e19  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d4e1f  mov r12,[rbp+0xA58]                           
66d4e26  test r12,r12                                  
66d4e29  je short 0x66D4E7C                            ; -> loc_66d4e7c
66d4e2b  mov r15,[rbp+0xA60]                           
66d4e32  jmp short 0x66D4E38                           ; -> loc_66d4e38

loc_66d4e34:  ; from 66d4e43, 66d4e4d, 66d4e53, 66d4e68, 66d4e7a
  66d4e34  add r12,0x28                                  

loc_66d4e38:  ; from 66d4e32
  66d4e38  cmp r12,r15                                   
  66d4e3b  je short 0x66D4E7C                            ; -> loc_66d4e7c
  66d4e3d  cmp byte ptr [r12+0x18],2                     
  66d4e43  jne short 0x66D4E34                           ; -> loc_66d4e34
  66d4e45  mov rbx,[r12+8]                               
  66d4e4a  test rbx,rbx                                  
  66d4e4d  je short 0x66D4E34                           ; -> loc_66d4e34
  66d4e4f  lock dec dword ptr [rbx+8]                    
  66d4e53  jne short 0x66D4E34                           ; -> loc_66d4e34
  66d4e55  mov rax,[rbx]                                 
  66d4e58  mov rax,[rax]                                 
  66d4e5b  mov rcx,rbx                                   
  66d4e5e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4e64  lock dec dword ptr [rbx+0xC]                  
  66d4e68  jne short 0x66D4E34                           ; -> loc_66d4e34
  66d4e6a  mov rax,[rbx]                                 
  66d4e6d  mov rax,[rax+8]                               
  66d4e71  mov rcx,rbx                                   
  66d4e74  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4e7a  jmp short 0x66D4E34                           ; -> loc_66d4e34

loc_66d4e7c:  ; from 66d4e29, 66d4e3b
  66d4e7c  mov rax,[rdi]                                 
  66d4e7f  movzx ecx,word ptr [rax+0x1CC]                
  66d4e86  cmp byte ptr [rbp+0x7EE],0                    
  66d4e8d  jne short 0x66D4E96                           ; -> loc_66d4e96
  66d4e8f  mov byte ptr [rbp+0x7EE],1                    

loc_66d4e96:  ; from 66d4e8d
  66d4e96  mov [rbp+0x7EC],cx                            
  66d4e9d  movups xmm0,[rax]                             
  66d4ea0  movdqu xmm1,[rax+0x10]                        
  66d4ea5  movdqu xmm2,[rax+0x20]                        
  66d4eaa  movups xmm3,[rax+0x30]                        
  66d4eae  movaps [rbp+0xA50],xmm0                       
```
// [V] Phase 16 finishes case-3 free (rbx=[rbp+0xA80]): fallthrough mov rax,[rax+8] at 0x66d4e12; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — completes dtor+free double call [V]. Joins node-release loop head at 0x66d4e1f: r12=[rbp+0xA58] (list head); test r12,r12; je 0x66d4e7c (empty list) [V]; r15=[rbp+0xA60] (sentinel end); jmp 0x66d4e38 [V]. loc_66d4e34: add r12,0x28 (advance 0x28-stride node) [V]. loc_66d4e38: cmp r12,r15; je 0x66d4e7c (done) [V]; cmp byte [r12+0x18],2; jne 0x66d4e34 (skip non-type-2 nodes) [V]; rbx=[r12+8] (node value ptr); test rbx,rbx; je 0x66d4e34 (skip null) [V]; lock dec dword [rbx+8]; jne 0x66d4e34 (refcount nonzero → skip destroy) [V]; else rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rbx+0xC]; jne 0x66d4e34; else rax=[rbx]; rax=[rax+8]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V]; jmp 0x66d4e34 loop [V] — dtor+free on each type-2 node's value. loc_66d4e7c (list done): rax=[rdi]; movzx ecx,word [rax+0x1CC] (vtable field at 0x1CC) [V]; cmp byte [rbp+0x7EE],0; jne 0x66d4e96; else mov byte [rbp+0x7EE],1 (one-time flag set) [V]. loc_66d4e96: [rbp+0x7EC]=cx [V]; movups xmm0=[rax]; movdqu xmm1=[rax+0x10]; movdqu xmm2=[rax+0x20]; movups xmm3=[rax+0x30]; movaps [rbp+0xA50]=xmm0 (continues phase 17 — copy rdi value struct into [rbp+0xA50..0xA90]). Next address: 0x66d4eb5.

## Phase 17 — 0x66d4eb5, 40 instructions [V]
```
66d4eb5  movdqa [rbp+0xA60],xmm1                       
66d4ebd  movdqa [rbp+0xA70],xmm2                       
66d4ec5  movaps [rbp+0xA80],xmm3                       
66d4ecc  mov byte ptr [rbp+0xA90],0                    
66d4ed3  lea rcx,[rbp+0x7F0]                           
66d4eda  lea rdx,[rbp+0xA50]                           
66d4ee1  call 0x67D0B00                                ; -> sub_67d0b00
66d4ee6  cmp byte ptr [rbp+0xA90],1                    
66d4eed  jne short 0x66D4F2F                           ; -> loc_66d4f2f
66d4eef  mov rcx,[rbp+0xA50]                           
66d4ef6  test rcx,rcx                                  
66d4ef9  je short 0x66D4F2F                           ; -> loc_66d4f2f
66d4efb  mov rdx,[rbp+0xA60]                           
66d4f02  sub rdx,rcx                                   
66d4f05  cmp rdx,0x1000                                
66d4f0c  jb short 0x66D4F2A                            ; -> loc_66d4f2a
66d4f0e  mov rax,[rcx-8]                               
66d4f12  add rcx,0xFFFFFFFFFFFFFFF8                    
66d4f16  sub rcx,rax                                   
66d4f19  cmp rcx,0x20                                  
66d4f1d  jae 0x66D2D40                                 ; -> sub_66d2d40
66d4f23  or rdx,0x27                                   
66d4f27  mov rcx,rax                                   

loc_66d4f2a:  ; from 66d4f0c
  66d4f2a  call 0xE935700                                ; -> sub_e935700

loc_66d4f2f:  ; from 66d4eed, 66d4ef9
  66d4f2f  mov rax,[rdi]                                 
  66d4f32  cmp byte ptr [rax+0x98],0xFF                  
  66d4f39  je short 0x66D4F7E                           ; -> loc_66d4f7e
  66d4f3b  movdqu xmm2,[rax+0x80]                        
  66d4f43  movq xmm1,[rax+0x90]                          
  66d4f4b  movdqu xmm0,[rax+0x9C]                        
  66d4f53  cmp byte ptr [rbp+0xA4C],1                    
  66d4f5a  jne short 0x66D4FA0                           ; -> loc_66d4fa0
  66d4f5c  cmp byte ptr [rbp+0xA38],0                    
  66d4f63  movdqu [rbp+0xA20],xmm2                       
  66d4f6b  movq [rbp+0xA30],xmm1                         
  66d4f73  je short 0x66D4F96                           ; -> loc_66d4f96
  66d4f75  mov byte ptr [rbp+0xA38],0                    
  66d4f7c  jmp short 0x66D4F96                           ; -> loc_66d4f96

loc_66d4f7e:  ; from 66d4f39
  66d4f7e  movdqu xmm0,[rax+0x9C]                        
  66d4f86  mov byte ptr [rbp+0xA38],0xFF                 
```
// [V] Phase 17 completes copy of rdi value struct into [rbp+0xA50..0xA90]: movdqa [rbp+0xA60]=xmm1, [rbp+0xA70]=xmm2; movaps [rbp+0xA80]=xmm3; mov byte [rbp+0xA90],0 [V]; then callee 0x67D0B00(rcx=&rbp+0x7F0, rdx=&rbp+0xA50) [V] — new callee sub_67d0b00 [V]; cmp byte [rbp+0xA90],1; jne 0x66d4f2f (skip size check) [V]. rcx=[rbp+0xA50]; test rcx,rcx; je 0x66d4f2f; else rdx=[rbp+0xA60]; sub rdx,rcx (size); cmp rdx,0x1000; jb 0x66d4f2a (oversize → skip) [V]; else rax=[rcx-8] (alloc header size); rcx+=0xFFFFFFFFFFFFFFF8 (rcx-8); sub rcx,rax (delta); cmp rcx,0x20; jae 0x66d2d40 (sub_66d2d40 — U-BA3 fallback target [V]) [V]; else or rdx,0x27; rcx=rax [V]. loc_66d4f2a: call 0xE935700(rcx) [V] — free (U-BA3 callee) [V]. loc_66d4f2f: rax=[rdi]; cmp byte [rax+0x98],0xFF; je 0x66d4f7e [V]; movdqu xmm2=[rax+0x80]; movq xmm1=[rax+0x90]; movdqu xmm0=[rax+0x9C] [V]; cmp byte [rbp+0xA4C],1; jne 0x66d4fa0 [V]; cmp byte [rbp+0xA38],0; movdqu [rbp+0xA20]=xmm2; movq [rbp+0xA30]=xmm1 [V]; je 0x66d4f96; else mov byte [rbp+0xA38],0; jmp 0x66d4f96 [V]. loc_66d4f7e ([rax+0x98]==0xFF): movdqu xmm0=[rax+0x9C]; mov byte [rbp+0xA38],0xFF [V] (continues phase 18). NEXT set to 0x66d4f8e.

## Phase 18 — 0x66d4f8e, 40 instructions [V]
```
66d4f8e  mov ebp,0xA4C                                 
66d4f93  add [rcx-0xD],dh                              ; W a0-0xD
66d4f97  movq [rbp+0xA3C],mm0                          
66d4f9e  jmp short 0x66D4FC6                           ; -> loc_66d4fc6
66d4fa0  movdqu [rbp+0xA20],xmm2                       
66d4fa8  movq [rbp+0xA30],xmm1                         
66d4fb0  mov byte ptr [rbp+0xA38],0                    
66d4fb7  movdqu [rbp+0xA3C],xmm0                       
66d4fbf  mov byte ptr [rbp+0xA4C],1                    

loc_66d4fc6:  ; from 66d4f9e
  66d4fc6  cmp byte ptr [rbp+0x4A8],3                    
  66d4fcd  jne short 0x66D5006                           ; -> loc_66d5006
  66d4fcf  mov rbx,[rbp+0x4A0]                           
  66d4fd6  test rbx,rbx                                  
  66d4fd9  je short 0x66D5006                            ; -> loc_66d5006
  66d4fdb  lock dec dword ptr [rbx+8]                    
  66d4fdf  jne short 0x66D5006                           ; -> loc_66d5006
  66d4fe1  mov rax,[rbx]                                 
  66d4fe4  mov rax,[rax]                                 
  66d4fe7  mov rcx,rbx                                   
  66d4fea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4ff0  lock dec dword ptr [rbx+0xC]                  
  66d4ff4  jne short 0x66D5006                           ; -> loc_66d5006
  66d4ff6  mov rax,[rbx]                                 
  66d4ff9  mov rax,[rax+8]                               
  66d4ffd  mov rcx,rbx                                   
  66d5000  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_66d5006:  ; from 66d4fcd, 66d4fd9, 66d4fdf, 66d4ff4
  66d5006  mov r12,[rbp+0x478]                           
  66d500d  test r12,r12                                  
  66d5010  je short 0x66D5063                            ; -> loc_66d5063
  66d5012  mov r15,[rbp+0x480]                           
  66d5019  jmp short 0x66D501F                           ; -> loc_66d501f

loc_66d501b:  ; from 66d502a, 66d5034, 66d503a, 66d504f, 66d5061
  66d501b  add r12,0x28                                  

loc_66d501f:  ; from 66d5019
  66d501f  cmp r12,r15                                   
  66d5022  je short 0x66D5063                            ; -> loc_66d5063
  66d5024  cmp byte ptr [r12+0x18],2                     
  66d502a  jne short 0x66D501B                           ; -> loc_66d501b
  66d502c  mov rbx,[r12+8]                               
  66d5031  test rbx,rbx                                  
  66d5034  je short 0x66D501B                            ; -> loc_66d501b
  66d5036  lock dec dword ptr [rbx+8]                    
```
// [V] Phase 18 handles [rbp+0x98]==0xFF case: mov ebp,0xA4C; add [rcx-0xD],dh (odd leftover) [V]; movq [rbp+0xA3C],mm0; jmp 0x66d4fc6 [V]. Alternate path (0x66d4fa0, [rbp+0xA4C]!=1): movdqu [rbp+0xA20]=xmm2; movq [rbp+0xA30]=xmm1; mov byte [rbp+0xA38],0; movdqu [rbp+0xA3C]=xmm0; mov byte [rbp+0xA4C],1 [V]. Join loc_66d4fc6: cmp byte [rbp+0x4A8],3; jne 0x66d5006 [V]; rbx=[rbp+0x4A0]; test rbx,rbx; je 0x66d5006; lock dec dword [rbx+8]; jne 0x66d5006; else rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rbx+0xC]; jne 0x66d5006; else rax=[rbx]; rax=[rax+8]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — dtor+free on [rbp+0x4A0] [V]. loc_66d5006: starts another node-release loop: r12=[rbp+0x478]; test r12,r12; je 0x66d5063; r15=[rbp+0x480]; jmp 0x66d501f [V]. loc_66d501b: add r12,0x28 (advance 0x28-stride node) [V]. loc_66d501f: cmp r12,r15; je 0x66d5063; cmp byte [r12+0x18],2; jne 0x66d501b; rbx=[r12+8]; test rbx,rbx; je 0x66d501b; lock dec dword [rbx+8] (continues phase 19 — dtor+free on type-2 nodes of [rbp+0x478] list). NEXT set to 0x66d503b.


## Phase 15 — 0x66d4d58, 40 instructions [V]
```
66d4d58  mov rcx,[rbp+0x498]                           
66d4d5f  mov [rbp+0xA78],rcx                           
66d4d66  jmp short 0x66D4DAA                           ; -> loc_66d4daa
66d4d68  lea rdx,[rbp+0x498]                           
66d4d6f  movups xmm0,[rdx]                             
66d4d72  movups [rcx],xmm0                             
66d4d75  jmp short 0x66D4DAA                           ; -> loc_66d4daa
66d4d77  movups [rcx],xmm0                             
66d4d7a  mov rcx,[rbp+0x4A0]                           
66d4d81  test rcx,rcx                                  
66d4d84  je short 0x66D4D93                            ; -> loc_66d4d93
66d4d86  lock inc dword ptr [rcx+8]                    
66d4d8a  mov rcx,[rbp+0x4A0]                           
66d4d91  jmp short 0x66D4D95                           ; -> loc_66d4d95

loc_66d4d93:  ; from 66d4d84
  66d4d93  xor ecx,ecx                                   

loc_66d4d95:  ; from 66d4d91
  66d4d95  mov rdx,[rbp+0x498]                           
  66d4d9c  mov [rbp+0xA78],rdx                           
  66d4da3  mov [rbp+0xA80],rcx                           

loc_66d4daa:  ; from 66d4d66, 66d4d75
  66d4daa  mov [rbp+0xA88],al                            
  66d4db0  mov rax,[rbp+0x4C0]                           
  66d4db7  mov [rbp+0xAA0],rax                           
  66d4dbe  movaps xmm0,[rbp+0x4B0]                       
  66d4dc5  movaps [rbp+0xA90],xmm0                       
  66d4dcc  lea rcx,[rbp+0x930]                           
  66d4dd3  lea rdx,[rbp+0xA50]                           
  66d4dda  call 0x67D0750                                ; -> sub_67d0750
  66d4ddf  cmp byte ptr [rbp+0xA88],3                    
  66d4de6  jne short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4de8  mov rbx,[rbp+0xA80]                           
  66d4def  test rbx,rbx                                  
  66d4df2  je short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4df4  lock dec dword ptr [rbx+8]                    
  66d4df8  jne short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4dfa  mov rax,[rbx]                                 
  66d4dfd  mov rax,[rax]                                 
  66d4e00  mov rcx,rbx                                   
  66d4e03  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4e09  lock dec dword ptr [rbx+0xC]                  
  66d4e0d  jne short 0x66D4E1F                           ; -> loc_66d4e1f
  66d4e0f  mov rax,[rbx]                                 
```
// [V] Phase 15 is jump-table case 0 (type tag 0 at [rbp+0x4A8]): rcx=[rbp+0x498]; [rbp+0xA78]=rcx [V]; jmp 0x66d4daa join [V]. Case 1 at 0x66d4d68: lea rdx,&rbp+0x498; movups xmm0=[rdx]; movups [rcx]=xmm0; jmp 0x66d4daa [V]. Case 2 at 0x66d4d77: movups [rcx],xmm0; rcx=[rbp+0x4A0]; test rcx,rcx; je 0x66d4d93 (ecx=0); else lock inc dword [rcx+8] refcount [V]; rcx=[rbp+0x4A0]; jmp 0x66d4d95 [V]. loc_66d4d93: xor ecx,ecx [V]. loc_66d4d95: rdx=[rbp+0x498]; [rbp+0xA78]=rdx; [rbp+0xA80]=rcx [V]. Join loc_66d4daa: [rbp+0xA88]=al (type tag) [V]; rax=[rbp+0x4C0]; [rbp+0xAA0]=rax [V]; movaps xmm0=[rbp+0x4B0]; [rbp+0xA90]=xmm0 [V]; lea rcx,&rbp+0x930; lea rdx,&rbp+0xA50; call 0x67D0750(rcx=&rbp+0x930, rdx=&rbp+0xA50) [V] — new callee sub_67d0750 [V]. cmp byte [rbp+0xA88],3; jne 0x66d4e1f (skip case-3 cleanup) [V]. rbx=[rbp+0xA80]; test rbx,rbx; je 0x66d4e1f; lock dec dword [rbx+8]; jne 0x66d4e1f; else rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rbx+0xC]; jne 0x66d4e1f (continues phase 16 — free call at 0x66d4e0f→0x66d4e12). Jump table (resolved via raw rdata at 0xF2BFAE0): case 0→0x66d4d58, case 1→0x66d4d68, case 2→0x66d4d77, case 3→0x66d4daa [V]. Next address: 0x66d4e12 (after 0x66d4e0f free-call tail).

## Phase 16 — 0x66d4e12, 40 instructions [V]
```
66d4e12  mov rax,[rax+8]                               
66d4e16  mov rcx,rbx                                   
66d4e19  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d4e1f  mov r12,[rbp+0xA58]                           
66d4e26  test r12,r12                                  
66d4e29  je short 0x66D4E7C                            ; -> loc_66d4e7c
66d4e2b  mov r15,[rbp+0xA60]                           
66d4e32  jmp short 0x66D4E38                           ; -> loc_66d4e38

loc_66d4e34:  ; from 66d4e43, 66d4e4d, 66d4e53, 66d4e68, 66d4e7a
  66d4e34  add r12,0x28                                  

loc_66d4e38:  ; from 66d4e32
  66d4e38  cmp r12,r15                                   
  66d4e3b  je short 0x66D4E7C                            ; -> loc_66d4e7c
  66d4e3d  cmp byte ptr [r12+0x18],2                     
  66d4e43  jne short 0x66D4E34                           ; -> loc_66d4e34
  66d4e45  mov rbx,[r12+8]                               
  66d4e4a  test rbx,rbx                                  
  66d4e4d  je short 0x66D4E34                           ; -> loc_66d4e34
  66d4e4f  lock dec dword ptr [rbx+8]                    
  66d4e53  jne short 0x66D4E34                           ; -> loc_66d4e34
  66d4e55  mov rax,[rbx]                                 
  66d4e58  mov rax,[rax]                                 
  66d4e5b  mov rcx,rbx                                   
  66d4e5e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4e64  lock dec dword ptr [rbx+0xC]                  
  66d4e68  jne short 0x66D4E34                           ; -> loc_66d4e34
  66d4e6a  mov rax,[rbx]                                 
  66d4e6d  mov rax,[rax+8]                               
  66d4e71  mov rcx,rbx                                   
  66d4e74  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4e7a  jmp short 0x66D4E34                           ; -> loc_66d4e34

loc_66d4e7c:  ; from 66d4e29, 66d4e3b
  66d4e7c  mov rax,[rdi]                                 
  66d4e7f  movzx ecx,word ptr [rax+0x1CC]                
  66d4e86  cmp byte ptr [rbp+0x7EE],0                    
  66d4e8d  jne short 0x66D4E96                           ; -> loc_66d4e96
  66d4e8f  mov byte ptr [rbp+0x7EE],1                    

loc_66d4e96:  ; from 66d4e8d
  66d4e96  mov [rbp+0x7EC],cx                            
  66d4e9d  movups xmm0,[rax]                             
  66d4ea0  movdqu xmm1,[rax+0x10]                        
  66d4ea5  movdqu xmm2,[rax+0x20]                        
  66d4eaa  movups xmm3,[rax+0x30]                        
  66d4eae  movaps [rbp+0xA50],xmm0                       
```
// [V] Phase 16 finishes case-3 free (rbx=[rbp+0xA80]): fallthrough mov rax,[rax+8] at 0x66d4e12; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V] — completes dtor+free double call [V]. Joins node-release loop head at 0x66d4e1f: r12=[rbp+0xA58] (list head); test r12,r12; je 0x66d4e7c (empty list) [V]; r15=[rbp+0xA60] (sentinel end); jmp 0x66d4e38 [V]. loc_66d4e34: add r12,0x28 (advance 0x28-stride node) [V]. loc_66d4e38: cmp r12,r15; je 0x66d4e7c (done) [V]; cmp byte [r12+0x18],2; jne 0x66d4e34 (skip non-type-2 nodes) [V]; rbx=[r12+8] (node value ptr); test rbx,rbx; je 0x66d4e34 (skip null) [V]; lock dec dword [rbx+8]; jne 0x66d4e34 (refcount nonzero → skip destroy) [V]; else rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 destroy) [V]; lock dec dword [rbx+0xC]; jne 0x66d4e34; else rax=[rbx]; rax=[rax+8]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040 free) [V]; jmp 0x66d4e34 loop [V] — dtor+free on each type-2 node's value. loc_66d4e7c (list done): rax=[rdi]; movzx ecx,word [rax+0x1CC] (vtable field at 0x1CC) [V]; cmp byte [rbp+0x7EE],0; jne 0x66d4e96; else mov byte [rbp+0x7EE],1 (one-time flag set) [V]. loc_66d4e96: [rbp+0x7EC]=cx [V]; movups xmm0=[rax]; movdqu xmm1=[rax+0x10]; movdqu xmm2=[rax+0x20]; movups xmm3=[rax+0x30]; movaps [rbp+0xA50]=xmm0 (continues phase 17 — copy rdi value struct into [rbp+0xA50..0xA90]). Next address: 0x66d4eb5.

## Phase 17 — 0x66d4eb5, 40 instructions [V]
```
66d4eb5  movdqa [rbp+0xA60],xmm1                       
66d4ebd  movdqa [rbp+0xA70],xmm2                       
66d4ec5  movaps [rbp+0xA80],xmm3                       
66d4ecc  mov byte ptr [rbp+0xA90],0                    
66d4ed3  lea rcx,[rbp+0x7F0]                           
66d4eda  lea rdx,[rbp+0xA50]                           
66d4ee1  call 0x67D0B00                                ; -> sub_67d0b00
66d4ee6  cmp byte ptr [rbp+0xA90],1                    
66d4eed  jne short 0x66D4F2F                           ; -> loc_66d4f2f
66d4eef  mov rcx,[rbp+0xA50]                           
66d4ef6  test rcx,rcx                                  
66d4ef9  je short 0x66D4F2F                           ; -> loc_66d4f2f
66d4efb  mov rdx,[rbp+0xA60]                           
66d4f02  sub rdx,rcx                                   
66d4f05  cmp rdx,0x1000                                
66d4f0c  jb short 0x66D4F2A                            ; -> loc_66d4f2a
66d4f0e  mov rax,[rcx-8]                               
66d4f12  add rcx,0xFFFFFFFFFFFFFFF8                    
66d4f16  sub rcx,rax                                   
66d4f19  cmp rcx,0x20                                  
66d4f1d  jae 0x66D2D40                                 ; -> sub_66d2d40
66d4f23  or rdx,0x27                                   
66d4f27  mov rcx,rax                                   

loc_66d4f2a:  ; from 66d4f0c
  66d4f2a  call 0xE935700                                ; -> sub_e935700

loc_66d4f2f:  ; from 66d4eed, 66d4ef9
  66d4f2f  mov rax,[rdi]                                 
  66d4f32  cmp byte ptr [rax+0x98],0xFF                  
  66d4f39  je short 0x66D4F7E                           ; -> loc_66d4f7e
  66d4f3b  movdqu xmm2,[rax+0x80]                        
  66d4f43  movq xmm1,[rax+0x90]                          
  66d4f4b  movdqu xmm0,[rax+0x9C]                        
  66d4f53  cmp byte ptr [rbp+0xA4C],1                    
  66d4f5a  jne short 0x66D4FA0                           ; -> loc_66d4fa0
  66d4f5c  cmp byte ptr [rbp+0xA38],0                    
  66d4f63  movdqu [rbp+0xA20],xmm2                       
  66d4f6b  movq [rbp+0xA30],xmm1                         
  66d4f73  je short 0x66D4F96                           ; -> loc_66d4f96
  66d4f75  mov byte ptr [rbp+0xA38],0                    
  66d4f7c  jmp short 0x66D4F96                           ; -> loc_66d4f96

loc_66d4f7e:  ; from 66d4f39
  66d4f7e  movdqu xmm0,[rax+0x9C]                        
  66d4f86  mov byte ptr [rbp+0xA38],0xFF                 
```
// [V] Phase 17 completes copy of rdi value struct into [rbp+0xA50..0xA90]: movdqa [rbp+0xA60]=xmm1, [rbp+0xA70]=xmm2; movaps [rbp+0xA80]=xmm3; mov byte [rbp+0xA90],0 [V]; then callee 0x67D0B00(rcx=&rbp+0x7F0, rdx=&rbp+0xA50) [V] — new callee sub_67d0b00 [V]; cmp byte [rbp+0xA90],1; jne 0x66d4f2f (skip size check) [V]. rcx=[rbp+0xA50]; test rcx,rcx; je 0x66d4f2f; else rdx=[rbp+0xA60]; sub rdx,rcx (size); cmp rdx,0x1000; jb 0x66d4f2a (oversize → skip) [V]; else rax=[rcx-8] (alloc header size); rcx+=0xFFFFFFFFFFFFFFF8 (rcx-8); sub rcx,rax (delta); cmp rcx,0x20; jae 0x66d2d40 (sub_66d2d40 — U-BA3 fallback target [V]) [V]; else or rdx,0x27; rcx=rax [V]. loc_66d4f2a: call 0xE935700(rcx) [V] — free (U-BA3 callee) [V]. loc_66d4f2f: rax=[rdi]; cmp byte [rax+0x98],0xFF; je 0x66d4f7e [V]; movdqu xmm2=[rax+0x80]; movq xmm1=[rax+0x90]; movdqu xmm0=[rax+0x9C] [V]; cmp byte [rbp+0xA4C],1; jne 0x66d4fa0 [V]; cmp byte [rbp+0xA38],0; movdqu [rbp+0xA20]=xmm2; movq [rbp+0xA30]=xmm1 [V]; je 0x66d4f96; else mov byte [rbp+0xA38],0; jmp 0x66d4f96 [V]. loc_66d4f7e ([rax+0x98]==0xFF): movdqu xmm0=[rax+0x9C]; mov byte [rbp+0xA38],0xFF [V] (continues phase 18). NEXT set to 0x66d4f8e. NEXT block already updated above.

## Phase 19 — 0x66d503b, 40 instructions [V]
```
66d503b  add [rbp+0x6D],dl                              ; [?] desync tail — end of prior region (1-byte off)
66d503e  (bad)                                          ; rdis desync marker; real stream shifted 1 byte
66d503f  add rcx,rdx                                    ; [?] (bad at 0x66d503e shifts display by 1)
66d5042  jmp rcx                                        ; [?] indirect jump — control leaves linear flow

66d5044  xorps xmm0,xmm0                                ; new basic block (jump target)
66d5047  lea rdx,[0x9625098]                           ; [data_9625098] "conditional_bit"
66d504e  xor ebx,ebx                                   
66d5050  lea rcx,[rbp-0x20]                             ; out buffer
66d5054  mov r8d,0xF                                    ; field size
66d505a  mov [rbp-0x10],rbx                             ; 0
66d505e  movups [rbp-0x20],xmm0                         ; clear buffer
66d5062  mov [rbp-8],rbx                                ; 0
66d5066  call 0x16BD40                                 ; -> sub_16bd40 field getter [V]
66d506b  xor r8d,r8d                                   

loc_66d506e:  ; from 66d5364 [V]
  66d506e  lea rdx,[rbp-0x20]                            
  66d5072  mov rcx,rdi                                   
  66d5075  call 0x6EA5350                                ; -> sub_6ea5350 [V]
  66d507a  xorps xmm0,xmm0                               
  66d507d  mov [rbp-0x10],rbx                            
  66d5081  mov r8d,0x10                                 
  66d5087  mov [rbp-8],rbx                              
  66d508b  lea rdx,[0x9624CE8]                           ; [data_9624ce8] "facing_direction"
  66d5092  lea rcx,[rbp-0x20]                            
  66d5096  movups [rbp-0x20],xmm0                        
  66d509a  call 0x16BD40                                 ; -> sub_16bd40 [V]
  66d509f  xor r8d,r8d                                   
  66d50a2  jmp 0x66D54E4                                 ; -> loc_66d54e4 common join [V]
  66d50a7  xorps xmm0,xmm0                               
  66d50aa  lea rdx,[0x9625098]                           ; "conditional_bit" again — separate case entry [I]
  66d50b1  xor ebx,ebx                                   
  66d50b3  lea rcx,[rbp-0x20]                            
  66d50b7  mov r8d,0xF                                   
  66d50bd  mov [rbp-0x10],rbx                            
  66d50c1  movups [rbp-0x20],xmm0                        
  66d50c5  mov [rbp-8],rbx                               
  66d50c9  call 0x16BD40                                 ; -> sub_16bd40 [V]
  66d50ce  xor r8d,r8d                                   

loc_66d50d1:  ; from 66d5393 [V]
  66d50d1  lea rdx,[rbp-0x20]                            
  66d50d5  mov rcx,rdi                                   
  66d50d8  call 0x6EA5350                                ; -> sub_6ea5350 [V]
  66d50dd  xorps xmm0,xmm0                               
```
## Phase 20 — 0x66d50e0, 40 instructions [V]
```
66d50e0  mov [rbp-0x10],rbx                             ; 0 (continuation of field-parse case)
66d50e4  mov r8d,0x10                                   ; field size 16
66d50ea  mov [rbp-8],rbx                                ; 0
66d50ee  lea rdx,[0x9624CE8]                           ; [data_9624ce8] "facing_direction"
66d50f5  lea rcx,[rbp-0x20]                             ; out buffer
66d50f9  movups [rbp-0x20],xmm0                         ; clear buffer
66d50fd  call 0x16BD40                                 ; -> sub_16bd40 field getter [V]
66d5102  mov r8d,1                                     
66d5108  jmp 0x66D54E4                                 ; -> loc_66d54e4 common join [V]
66d510d  xorps xmm0,xmm0                                ; next case entry
66d5110  lea rdx,[0x9625098]                           ; [data_9625098] "conditional_bit"
66d5117  xor ebx,ebx                                   
66d5119  lea rcx,[rbp-0x20]                            
66d511d  mov r8d,0xF                                   
66d5123  mov [rbp-0x10],rbx                            
66d5127  movups [rbp-0x20],xmm0                        
66d512b  mov [rbp-8],rbx                               
66d512f  call 0x16BD40                                 ; -> sub_16bd40 [V]
66d5134  xor r8d,r8d                                   

loc_66d5137:  ; from 66d53c2 [V]
  66d5137  lea rdx,[rbp-0x20]                            
  66d513b  mov rcx,rdi                                   
  66d513e  call 0x6EA5350                                ; -> sub_6ea5350 [V]
  66d5143  xorps xmm0,xmm0                               
  66d5146  mov [rbp-0x10],rbx                            
  66d514a  mov r8d,0x10                                  
  66d5150  mov [rbp-8],rbx                              
  66d5154  lea rdx,[0x9624CE8]                           ; [data_9624ce8] "facing_direction"
  66d515b  lea rcx,[rbp-0x20]                            
  66d515f  movups [rbp-0x20],xmm0                        
  66d5163  call 0x16BD40                                 ; -> sub_16bd40 [V]
  66d5168  mov r8d,2                                     
  66d516e  jmp 0x66D54E4                                 ; -> loc_66d54e4 common join [V]
  66d5173  xorps xmm0,xmm0                               
  66d5176  lea rdx,[0x9625098]                           ; [data_9625098] "conditional_bit"
  66d517d  xor ebx,ebx                                   
  66d517f  lea rcx,[rbp-0x20]                            
  66d5183  mov r8d,0xF                                   
  66d5189  mov [rbp-0x10],rbx                            
  66d518d  movups [rbp-0x20],xmm0                        
  66d5191  mov [rbp-8],rbx                               
```
// [V] Phase 20 continues the field-parse jump-table at 0x66d50e0 (continuation of prior case: [rbp-0x10]=0; r8d=0x10; [rbp-8]=0; lea rdx,"facing_direction" [0x9624CE8]; buffer [rbp-0x20]; movups clear; call 0x16BD40 [V]; mov r8d,1; jmp 0x66d54e4 common join [V]). Then three more case-entry blocks (loc_66d5137 entered from jump target 0x66d53c2 [V]): each = xorps; lea rdx,"conditional_bit" [0x9625098] / "facing_direction" [0x9624CE8]; zero [rbp-0x10]/[rbp-8]; mov r8d field size (0xF/0x10/2); movups clear buffer; call 0x16BD40 [V]; xor r8d,r8d; lea rdx,&rbp-0x20; mov rcx,rdi; call 0x6EA5350(rcx=rdi, rdx=&parsed field) [V]; mov r8d=N; jmp 0x66d54e4 [V]. Pattern [I]: sub_16BD40+sub_6EA5350 field-parse cases (r8d = field width) all join loc_66d54e4 — entity field dispatch (conditional_bit, facing_direction). Roadata strings [V]: [0x9624CE8] "facing_direction", [0x9625098] "conditional_bit". Ends at 0x66d5195 mid-case (rdis --max 40 cap). Unit U-BA5 ends here per brief (phases 19-20 written; 14 of 20 planned phases, 560 instructions).
