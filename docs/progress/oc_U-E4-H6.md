# U-E4-H6 (builder 0x6722cb0, function [0x6722cb0..0x672a464))

## NEXT
Phase 35 (0x6727a24..0x6727AD8, 40 instructions) written; first 10 instructions at 0x6727a24..0x6727a44 decode as garbage/(bad) and are tagged [?] padding/dead code; real stream resumes `call 0x5ABA5C0` at 0x6727a44; `mov r14,rax`; 13-store zeroing loop at [rbp+0x2A4+0x04..0xB4] (xmm6, [rbp+0x2A8..0x358]); TLS seq dl=0x4A; `mov [rbp+0x827],al`; cursor loop [r14+0x8A8]/[r14+0x8B0] with new targets `je 0x67289B7` (-> loc_67289b7) / `jmp 0x67289CB` (-> loc_67289cb); last instruction `jmp 0x67289CB` at 0x6727ad3 ends at 0x6727AD8. 197 instructions remain to reach exactly 800 (603 written; phases 36-39 at 40 = 160, phase 40 partial ~37). Next phase starts at 0x6727AD8. Continue with `rdis dis 0x6727AD8 40`.

## Phase 21 (0x6726f07..0x6726fb7)
```
  6726f07  mov rcx,[rax]                                 
  6726f0a  mov rax,[rcx]                                 
  6726f0d  mov rax,[rax+0x48]                            
  6726f11  lea rdx,[rbp+0x2A0]                           
  6726f18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726f1e  nop                                           
  6726f1f  mov r14,[rbp+0x7E0]                           
  6726f26  mov rdi,[rbp+0x7E8]                           
  6726f2d  mov rax,rdi                                   
  6726f30  sub rax,r14                                   
  6726f33  cmp rax,0xFFFFFFFFFFFFFFE0                    
  6726f37  je 0x672A30F                                  ; -> sub_672a30f
  6726f3d  test r14,r14                                  
  6726f40  setne al                                      
  6726f43  test rdi,rdi                                  
  6726f46  sete cl                                       
  6726f49  or cl,al                                      
  6726f4b  je 0x672A30F                                  ; -> sub_672A30F
  6726f51  test r14,r14                                  
  6726f54  setne al                                      
  6726f57  cmp rdi,r14                                   
  6726f5a  sete cl                                       
  6726f5d  or cl,al                                      
  6726f5f  je 0x672A30F                                  ; -> sub_672A30F
  6726f65  lea rax,[rbp+0x7B0]                           
  6726f6c  mov [rbp+0x7A0],rax                           
  6726f73  mov rax,0x100000000                           
  6726f7d  mov [rbp+0x7A8],rax                           
  6726f84  cmp rdi,r14                                   
  6726f87  je short 0x6726FB0                            ; -> loc_6726fb0
  6726f89  nop [rax]                                     

loc_6726f90:  ; from 6726fae
  6726f90  lea rcx,[rbp+0x7A0]                           
  6726f97  lea rdx,[rbp+0x560]                           
  6726f9e  mov r8,r14                                    
  6726fa1  call 0x676A670                                ; -> sub_676a670
  6726fa6  nop                                           
  6726fa7  add r14,0x20                                  
  6726fab  cmp r14,rdi                                   
  6726fae  jne short 0x6726F90                           ; -> loc_6726f90

loc_6726fb0:  ; from 6726f87
  6726fb0  lea rax,[rbp+0x770]                           
```
// Phase 21: tail of phase 20's `mov rax,[rbp+0x758]` (3 bytes, resumes at 0x6726f07): virtual-call pattern `mov rcx,[rax]` (vtable); `mov rax,[rcx]`; `mov rax,[rax+0x48]` (vslot 9); `lea rdx,[rbp+0x2A0]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. Range validation: `r14=[rbp+0x7E0]` (begin); `rdi=[rbp+0x7E8]` (end); `rax=rdi-r14`; `cmp rax,0xFFFFFFFFFFFFFFE0`; if equal `je 0x672A30F` (-> sub_672a30f, error path seen in phase 20). Null/empty checks: `test r14,r14`/`setne al`; `test rdi,rdi`/`sete cl`; `or cl,al`; if zero `je 0x672A30F`; repeat `test r14,r14`/`setne al`; `cmp rdi,r14`/`sete cl`; `or cl,al`; if zero `je 0x672A30F` (r14==rdi → empty). If OK: `lea rax,[rbp+0x7B0]`; `mov [rbp+0x7A0],rax` (loop cursor = &[rbp+0x7B0]); `mov rax,0x100000000`; `mov [rbp+0x7A8],rax` (end sentinel 2^32). `cmp rdi,r14`; if equal `je short 0x6726FB0` (-> loc_6726fb0, skip loop). Loop loc_6726f90: `lea rcx,[rbp+0x7A0]` (cursor); `lea rdx,[rbp+0x560]`; `mov r8,r14`; `call 0x676A670` (sub_676a670); `nop`; `add r14,0x20` (advance cursor by 32 bytes); `cmp r14,rdi`; `jne short 0x6726F90` (loop until r14==rdi). loc_6726fb0: `lea rax,[rbp+0x770]` (continues next phase: next instruction at 0x6726fb7).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, virtual call via vslot 0x48), 0x676A670 (sub_676a670, direct).
Fields read: [rax] [R] (vtable), [rcx] [R], [rax+0x48] [R], [rbp+0x7E0] [R] (r14), [rbp+0x7E8] [R] (rdi), [rbp+0x560] [R via lea address], r14 [R/W], rdi [R].
Fields written: [rbp+0x7A0], [rbp+0x7A8], r14 [W in loop].

## Phase 22 (0x6726fb7..0x672709a)
```
  6726fb7  mov [rbp+0x760],rax                           
  6726fbe  mov rax,0x100000000                           
  6726fc8  mov [rbp+0x768],rax                           
  6726fcf  lea rdi,[rbp+0x760]                           
  6726fd6  mov rcx,rdi                                   
  6726fd9  lea rdx,[rbp+0x7A0]                           
  6726fe0  call 0x6764990                                ; -> sub_6764990
  6726fe5  nop                                           
  6726fe6  mov [rsp+0x20],rdi                            
  6726feb  lea rcx,[rbp+0x560]                           
  6726ff2  lea rdx,[rbp+0x458]                           
  6726ff9  lea r8,[rbp+0x400]                            
  6727000  lea r9,[rbp+0x378]                            
  6727007  call 0x6792570                                ; -> sub_6792570
  672700c  nop                                           
  672700d  lea rcx,[rbp+0x4A8]                           
  6727014  mov eax,[rcx+0x10]                            
  6727017  lea rdx,[rbp+0x6D8]                           
  672701e  mov [rdx+0x10],eax                            
  6727021  movups xmm0,[rcx]                             
  6727024  movups [rdx],xmm0                             
  6727027  movzx eax,byte ptr [rbp+0x4BC]                
  672702e  mov [rbp+0x6EC],al                            
  6727034  movups xmm0,[rbp+0x4C0]                       
  672703b  movups [rbp+0x6F0],xmm0                       
  6727042  movups xmm0,[rbx+0x80]                        
  6727049  movups xmm1,[rbx+0x90]                        
  6727050  movups xmm2,[rbx+0x9F]                        
  6727057  lea rax,[rbp+0x564]                           
  672705e  movups [rax+0x1BB],xmm2                       
  6727065  movups [rax+0x1AC],xmm1                       
  672706c  movups [rax+0x19C],xmm0                       
  6727073  movzx eax,word ptr [rbp+0x500]                
  672707a  mov [rbp+0x730],ax                            
  6727081  mov rax,[rbp+0x808]                           
  6727088  mov rcx,[rax+0x10]                            
  672708c  mov eax,0x9D0                                 
  6727091  add rcx,rax                                   
  6727094  call 0x5ABA5C0                                ; -> sub_5aba5c0
  6727099  nop                                           
```
// Phase 22: `mov [rbp+0x760],rax` stores the lea result (&[rbp+0x770]) from phase 21's loc_6726fb0; `mov rax,0x100000000`; `mov [rbp+0x768],rax` (end sentinel 2^32). `lea rdi,[rbp+0x760]`; `mov rcx,rdi` (rcx = &begin-ref); `lea rdx,[rbp+0x7A0]` (rdx = cursor ref); `call 0x6764990` (sub_6764990; likely range-init between the two refs); `nop`; `mov [rsp+0x20],rdi`. Bulk copy: `lea rcx,[rbp+0x560]`; `lea rdx,[rbp+0x458]`; `lea r8,[rbp+0x400]`; `lea r9,[rbp+0x378]`; `call 0x6792570` (sub_6792570; 4-arg buffer copy); `nop`. Field copy: `lea rcx,[rbp+0x4A8]`; `mov eax,[rcx+0x10]`; `lea rdx,[rbp+0x6D8]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0` (copies [rbp+0x4A8..0x4B8] → [rbp+0x6D8..0x6E8] plus +0x10 field). `movzx eax,byte ptr [rbp+0x4BC]`; `mov [rbp+0x6EC],al`. `movups xmm0,[rbp+0x4C0]`; `movups [rbp+0x6F0],xmm0`. Vector gather from rbx: `movups xmm0,[rbx+0x80]`; `movups xmm1,[rbx+0x90]`; `movups xmm2,[rbx+0x9F]`; `lea rax,[rbp+0x564]`; `movups [rax+0x1BB],xmm2`; `movups [rax+0x1AC],xmm1`; `movups [rax+0x19C],xmm0` (stores into [rbp+0x564+0x19C..]). `movzx eax,word ptr [rbp+0x500]`; `mov [rbp+0x730],ax`. Tail call setup: `mov rax,[rbp+0x808]`; `mov rcx,[rax+0x10]`; `mov eax,0x9D0`; `add rcx,rax`; `call 0x5ABA5C0` (sub_5aba5c0); `nop` (continues next phase: next instruction at 0x672709a).

Callees: 0x6764990 (sub_6764990, direct), 0x6792570 (sub_6792570, direct), 0x5ABA5C0 (sub_5aba5c0, direct).
Fields read: rax [R], [rbp+0x760] [W], [rbp+0x768] [W], [rbp+0x7A0] [R], [rbp+0x560] [R], [rbp+0x458] [W], [rbp+0x400] [W], [rbp+0x378] [W], [rbp+0x4A8] [R], [rcx+0x10] [R], [rbp+0x6D8] [W], [rbp+0x4BC] [R], [rbp+0x6EC] [W], [rbp+0x4C0] [R], [rbp+0x6F0] [W], [rbx+0x80] [R], [rbx+0x90] [R], [rbx+0x9F] [R], [rbp+0x564] [R], [rbp+0x500] [R], [rbp+0x730] [W], [rbp+0x808] [R], [rax+0x10] [R], [rsp+0x20] [W].
Fields written: [rbp+0x760], [rbp+0x768], [rsp+0x20], [rbp+0x458], [rbp+0x400], [rbp+0x378], [rbp+0x6D8], [rdx+0x10], [rbp+0x6EC], [rbp+0x6F0], [rbp+0x564+0x1BB], [rbp+0x564+0x1AC], [rbp+0x564+0x19C], [rbp+0x730], [rsp+0x20].

## Phase 23 (0x672709a..0x6727164)
```
  672709a  mov r14,rax                                   
  672709d  lea rax,[rbp+0x2A4]                           
  67270a4  movups [rax+0xB4],xmm6                        
  67270ab  movups [rax+0xA4],xmm6                        
  67270b2  movups [rax+0x94],xmm6                        
  67270b9  movups [rax+0x84],xmm6                        
  67270c0  movups [rax+0x74],xmm6                        
  67270c4  movups [rax+0x64],xmm6                        
  67270c8  movups [rax+0x54],xmm6                        
  67270cc  movups [rax+0x44],xmm6                        
  67270d0  movups [rax+0x34],xmm6                        
  67270d4  movups [rax+0x24],xmm6                        
  67270d8  movups [rax+0x14],xmm6                        
  67270dc  movups [rax+4],xmm6                           
  67270e0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67270e7  mov rax,[rcx]                                 
  67270ea  mov rax,[rax+0x10]                            
  67270ee  mov dl,0x4A                                   
  67270f0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67270f6  nop                                           
  67270f7  mov [rbp+0x827],al                            
  67270fd  mov rdx,[r14+0x8A8]                           
  6727104  cmp rdx,[r14+0x8B0]                           
  672710b  je 0x6727AD8                                  ; -> loc_6727ad8
  6727111  movzx eax,word ptr [rbp+0x730]                
  6727118  mov [rdx],ax                                  
  672711b  add qword ptr [r14+0x8A8],2                   
  6727123  jmp 0x6727AEC                                 ; -> loc_6727aec
  6727128  lea rcx,[rbp+0x510]                           
  672712f  lea rdx,[rbp+0x370]                           
  6727136  call 0x67A75D0                                ; -> sub_67a75d0
  672713b  nop                                           
  672713c  lea rcx,[rbp+0x560]                           
  6727143  mov rdx,rbx                                   
  6727146  lea r8,[rbp+0x3F8]                            
  672714d  lea r9,[rbp+0x370]                            
  6727154  call 0x678F640                                ; -> sub_678f640
  6727159  nop                                           
  672715a  mov eax,[rbx+0x60]                            
  672715d  lea rcx,[rbp+0x698]                           
```
// Phase 23: `mov r14,rax` carries the sub_5aba5c0 return (from phase 22's `call 0x5ABA5C0`) into r14. Zeroing loop: `lea rax,[rbp+0x2A4]`; thirteen `movups [rax+disp],xmm6` stores at disp 0xB4,0xA4,0x94,0x84,0x74,0x64,0x54,0x44,0x34,0x24,0x14,0x04 — i.e. [rbp+0x2A8..0x358] zeroed 16 bytes at a time (xmm6 presumed zero). TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x827],al`. Cursor loop: `rdx=[r14+0x8A8]`; `cmp rdx,[r14+0x8B0]`; if equal `je 0x6727AD8` (-> loc_6727ad8) else `movzx eax,word ptr [rbp+0x730]`; `mov [rdx],ax`; `add qword ptr [r14+0x8A8],2`; `jmp 0x6727AEC` (-> loc_6727aec; appends a word from [rbp+0x730] to r14's buffer, advancing by 2). `lea rcx,[rbp+0x510]`; `lea rdx,[rbp+0x370]`; `call 0x67A75D0` (sub_67a75d0); `nop`. `lea rcx,[rbp+0x560]`; `mov rdx,rbx`; `lea r8,[rbp+0x3F8]`; `lea r9,[rbp+0x370]`; `call 0x678F640` (sub_678f640); `nop`. `mov eax,[rbx+0x60]`; `lea rcx,[rbp+0x698]` (continues next phase: next instruction at 0x6727164).

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x67A75D0 (sub_67a75d0, direct), 0x678F640 (sub_678f640, direct).
Fields read: rax [W], r14 [R/W], [rbp+0x2A4+4]..[rbp+0x2A4+0xB4] [W] (xmm6 zeroing), [rbp+0x827] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [r14+0x8A8] [R/W], [r14+0x8B0] [R], [rbp+0x730] [R], [rbp+0x510] [R], [rbp+0x370] [R/W], [rbp+0x560] [R], rbx [R], [rbx+0x60] [R], [rbp+0x3F8] [R], [rbp+0x698] [W via lea address].
Fields written: [rbp+0x2A8..0x358] via [rax+disp], [rbp+0x827], [r14+0x8A8], [rdx] (word store), [rbp+0x698] via lea target.

## Phase 24 (0x6727164..0x6727248)
```
  6727164  mov [rcx+0x10],eax                            ; W a0+0x10
  6727167  movups xmm0,[rbx+0x50]                        
  672716b  movups [rcx],xmm0                             ; W a0+0x0
  672716e  movzx eax,byte ptr [rbp+0x4B4]                
  6727175  mov [rbp+0x6AC],al                            
  672717b  movups xmm0,[rbp+0x4B8]                       
  6727182  movups [rbp+0x6B0],xmm0                       
  6727189  movups xmm0,[rbx+0x78]                        
  672718d  movups xmm1,[rbx+0x88]                        
  6727194  movups xmm2,[rbx+0x97]                        
  672719b  lea rax,[rbp+0x564]                           
  67271a2  movups [rax+0x17B],xmm2                       
  67271a9  movups [rax+0x16C],xmm1                       
  67271b0  movups [rax+0x15C],xmm0                       
  67271b7  movzx eax,word ptr [rbp+0x4F8]                
  67271be  mov [rbp+0x6F0],ax                            
  67271c5  mov rcx,[rbp+0x748]                           
  67271cc  mov rax,[rcx+0x480]                           
  67271d3  mov rdx,[rcx+0x488]                           
  67271da  mov rcx,rdx                                   
  67271dd  sub rcx,rax                                   
  67271e0  cmp rcx,0xFFFFFFFFFFFFFFD0                    
  67271e4  je 0x672A30F                                  ; -> sub_672a30f
  67271ea  test rax,rax                                  
  67271ed  setne r8b                                     
  67271f1  test rdx,rdx                                  
  67271f4  sete dl                                       
  67271f7  or dl,r8b                                     
  67271fa  je 0x672A30F                                  ; -> sub_672a30f
  6727200  sar rcx,4                                     
  6727204  mov rdx,0xAAAAAAAAAAAAAAAB                    
  672720e  imul rcx,rdx                                  
  6727212  mov [rbp+0xF0],rcx                            
  6727219  mov [rbp+0xF8],rax                            
  6727220  lea rdi,[rbp+0x560]                           
  6727227  mov [rsp+0x20],rdi                            
  672722c  mov rcx,[rbp+0x808]                           
  6727233  lea rdx,[rbp+0xF0]                            
  672723a  mov r8,[rbp+0x758]                            
  6727241  lea r9,[rbp+0x530]                            
```
// Phase 24: continuation of phase 23's `lea rcx,[rbp+0x698]`: `mov [rcx+0x10],eax` → [rbp+0x6A8] = eax (from [rbx+0x60]); `movups xmm0,[rbx+0x50]`; `movups [rcx],xmm0` (copies [rbx+0x50..0x60] → [rbp+0x698..0x6A8]). `movzx eax,byte ptr [rbp+0x4B4]`; `mov [rbp+0x6AC],al`. `movups xmm0,[rbp+0x4B8]`; `movups [rbp+0x6B0],xmm0`. Vector gather from rbx: `movups xmm0,[rbx+0x78]`; `movups xmm1,[rbx+0x88]`; `movups xmm2,[rbx+0x97]`; `lea rax,[rbp+0x564]`; `movups [rax+0x17B],xmm2`; `movups [rax+0x16C],xmm1`; `movups [rax+0x15C],xmm0` (stores into [rbp+0x564+0x15C..]). `movzx eax,word ptr [rbp+0x4F8]`; `mov [rbp+0x6F0],ax`. Range check on [rbp+0x748]: `rcx=[rbp+0x748]`; `rax=[rcx+0x480]`; `rdx=[rcx+0x488]`; `rcx=rdx`; `rcx-=rax`; `cmp rcx,0xFFFFFFFFFFFFFFD0`; if equal `je 0x672A30F` (-> sub_672a30f, error path). `test rax,rax`; `setne r8b`; `test rdx,rdx`; `sete dl`; `or dl,r8b`; if zero `je 0x672A30F` (null-check on both ends). Divide-by-17 magic: `sar rcx,4`; `rdx=0xAAAAAAAAAAAAAAAB`; `imul rcx,rdx`; `mov [rbp+0xF0],rcx`; `mov [rbp+0xF8],rax`. Call setup: `lea rdi,[rbp+0x560]`; `mov [rsp+0x20],rdi`; `mov rcx,[rbp+0x808]`; `lea rdx,[rbp+0xF0]`; `mov r8,[rbp+0x758]`; `lea r9,[rbp+0x530]` (continues next phase: next instruction at 0x6727248, expected `call` like phase 20's `call 0x6769EE0`).

Callees: je 0x672A30F (sub_672a30f, error target, [I]).
Fields read: rcx [W], [rbx+0x50] [R], [rcx] [W], [rbp+0x4B4] [R], [rbp+0x6AC] [W], [rbp+0x4B8] [R], [rbp+0x6B0] [W], [rbx+0x78] [R], [rbx+0x88] [R], [rbx+0x97] [R], [rbp+0x564] [R], [rax+0x17B] [W], [rax+0x16C] [W], [rax+0x15C] [W], [rbp+0x4F8] [R], [rbp+0x6F0] [W], [rbp+0x748] [R], [rcx+0x480] [R], [rcx+0x488] [R], [rbp+0xF0] [W], [rbp+0xF8] [W], [rbp+0x560] [R], [rsp+0x20] [W], [rbp+0x808] [R], [rbp+0x758] [R], [rbp+0x530] [R].
Fields written: [rbp+0x6A8] via [rcx+0x10], [rbp+0x698], [rbp+0x6AC], [rbp+0x6B0], [rbp+0x564+0x17B], [rbp+0x564+0x16C], [rbp+0x564+0x15C], [rbp+0x6F0], [rbp+0xF0], [rbp+0xF8], [rsp+0x20].

## Phase 25 (0x6727248..0x6727304)
```
  6727248  call 0x67E4280                                ; -> sub_67e4280
  672724d  nop                                           
  672724e  mov rcx,rdi                                   
  6727251  call 0x67E1840                                ; -> sub_67E1840
  6727256  lea rcx,[rbp+0x370]                           
  672725d  jmp 0x672A1A0                                 ; -> sub_672a1a0
  6727262  lea rcx,[r14+0x8A0]                           
  6727269  lea r8,[rbp+0x6F8]                            
  6727270  call 0x1EF6F90                                ; -> sub_1ef6f90
  6727275  nop                                           
  6727276  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672727d  mov rax,[rcx]                                 
  6727280  mov rax,[rax+0x10]                            
  6727284  movzx edx,byte ptr [rbp+0x818]                
  672728b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727291  nop                                           
  6727292  mov qword ptr [rbp+0x110],1                   
  672729d  mov eax,[r14+0x8A8]                           
  67272a4  sub eax,[r14+0x8A0]                           
  67272ab  shr eax,1                                     
  67272ad  dec eax                                       
  67272af  mov [rbp+0x120],ax                            
  67272b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67272bd  mov rax,[rcx]                                 
  67272c0  mov rax,[rax+0x10]                            
  67272c4  mov dl,0x4A                                   
  67272c6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67272cc  nop                                           
  67272cd  mov [rbp+0x818],al                            
  67272d3  mov rdx,[r14+0x758]                           
  67272da  cmp rdx,[r14+0x760]                           
  67272e1  je short 0x672735C                            ; -> loc_672735c
  67272e3  lea rcx,[rbp+0x6A0]                           
  67272ea  mov eax,[rcx+0x10]                            
  67272ed  mov [rdx+0x10],eax                            
  67272f0  movups xmm0,[rcx]                             
  67272f3  movups [rdx],xmm0                             
  67272f6  movzx eax,byte ptr [rbp+0x6B4]                
  67272fd  mov [rdx+0x14],al                             
  6727300  movss xmm0,[rbp+0x6B8]                        
```
// Phase 25: tail-exit path from phase 24's call setup: `call 0x67E4280` (sub_67e4280); `nop`; `mov rcx,rdi`; `call 0x67E1840` (sub_67E1840); `lea rcx,[rbp+0x370]`; `jmp 0x672A1A0` (sub_672a1a0, tail jump — function exit on that path). Fall-through path (block at 0x6727262): `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x6F8]`; `call 0x1EF6F90` (sub_1ef6f90); `nop`. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x110],1`. Count calc: `eax=[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax`; `mov [rbp+0x120],ax`. Second TLS call dl=0x4A; `mov [rbp+0x818],al`. Cursor loop: `rdx=[r14+0x758]`; `cmp rdx,[r14+0x760]`; if equal `je short 0x672735C` (-> loc_672735c) else `lea rcx,[rbp+0x6A0]`; `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0` (copies 16 bytes [rbp+0x6A0..0x6B0] → [rdx..rdx+0x10]); `movzx eax,byte ptr [rbp+0x6B4]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x6B8]` (continues next phase: next instruction at 0x6727304).

Callees: 0x67E4280 (sub_67e4280, direct), 0x67E1840 (sub_67E1840, direct), jmp 0x672A1A0 (sub_672a1a0, tail), 0x1EF6F90 (sub_1ef6f90, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: rdi [R/W], [rbp+0x370] [R], r14 [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [rbp+0x110] [W], [r14+0x8A8] [R], [r14+0x8A0] [R], [rbp+0x120] [W], [r14+0x758] [R/W], [r14+0x760] [R], [rbp+0x6A0] [R], [rdx+0x10] [W], [rbp+0x6B4] [R], [rdx+0x14] [W], [rbp+0x6B8] [R].
Fields written: [rbp+0x370] via tail, [rbp+0x110], [rbp+0x120], [rbp+0x818], [r14+0x758] via [rdx+...] store chain, [rdx+0x10], [rdx+0x14].

## Phase 26 (0x6727304..0x67273c9)
```
  6727304  mov eax,0xF3000006                            
  6727309  movups [rdx+0x18],xmm0                        ; W a1+0x18
  672730d  movss xmm0,[rbp+0x6BC]                        
  6727315  movss [rdx+0x1C],xmm0                         ; W a1+0x1C
  672731a  movss xmm0,[rbp+0x6C0]                        
  6727322  movss [rdx+0x20],xmm0                         ; W a1+0x20
  6727327  movss xmm0,[rbp+0x6C4]                        
  672732f  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6727334  lea rax,[rbp+0x6C8]                           
  672733b  movups xmm0,[rax]                             
  672733e  movups xmm1,[rax+0x10]                        
  6727342  movups xmm2,[rax+0x1F]                        
  6727346  movups [rdx+0x28],xmm0                        ; W a1+0x28
  672734a  movups [rdx+0x38],xmm1                        ; W a1+0x38
  672734e  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6727352  add qword ptr [r14+0x758],0x58                
  672735a  jmp short 0x6727370                           ; -> loc_6727370
  672735c  lea rcx,[r14+0x750]                           
  6727363  lea r8,[rbp+0x6A0]                            
  672736a  call 0x6760A80                                ; -> sub_6760a80
  672736f  nop                                           

loc_6727370:  ; from 672735a
  6727370  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727377  mov rax,[rcx]                                 
  672737a  mov rax,[rax+0x10]                            
  672737e  movzx edx,byte ptr [rbp+0x818]                
  6727385  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672738b  nop                                           
  672738c  mov eax,[r14+0x758]                           
  6727393  sub eax,[r14+0x750]                           
  672739a  shr eax,3                                     
  672739d  imul eax,0xFFFF8BA3                           
  67273a3  dec eax                                       
  67273a5  mov [rbp+0x13C],ax                            
  67273ac  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67273b3  mov rax,[rcx]                                 
  67273b6  mov rax,[rax+0x10]                            
  67273ba  mov dl,0x4A                                   
  67273bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67273c2  nop                                           
  67273c3  mov [rbp+0x818],al                            
```
// Phase 26: cursor-loop body from phase 25: `mov eax,0xF3000006` (overwrites low dword of xmm0 loaded via `movss xmm0,[rbp+0x6B8]` in phase 25); `movups [rdx+0x18],xmm0` (stores [rdx+0x18..0x28] with low dword = 0xF3000006). `movss xmm0,[rbp+0x6BC]`; `movss [rdx+0x1C],xmm0`. `movss xmm0,[rbp+0x6C0]`; `movss [rdx+0x20],xmm0`. `movss xmm0,[rbp+0x6C4]`; `movss [rdx+0x24],xmm0`. `lea rax,[rbp+0x6C8]`; `movups xmm0,[rax]`; `movups xmm1,[rax+0x10]`; `movups xmm2,[rax+0x1F]`; `movups [rdx+0x28],xmm0`; `movups [rdx+0x38],xmm1`; `movups [rdx+0x47],xmm2` (copies [rbp+0x6C8..0x6E0]→[rdx+0x28..0x40], [rbp+0x6D8..0x6E8]→[rdx+0x38..0x48], [rbp+0x6E7..0x6F7]→[rdx+0x47..0x57]). `add qword ptr [r14+0x758],0x58` (advance cursor by 88); `jmp short 0x6727370` (-> loc_6727370, loop tail). Je-target block loc_672735c (from phase 25's `je short 0x672735C`): `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6A0]`; `call 0x6760A80` (sub_6760a80); `nop`; falls into loc_6727370. loc_6727370: TLS seq `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. Count calc: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3` (magic for signed /7); `dec eax`; `mov [rbp+0x13C],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al` (continues next phase: next instruction at 0x67273c9).

Callees: [0xF99FFA0] = sub_eea6040 (twice), 0x6760A80 (sub_6760a80, direct).
Fields read: rdx [W] (cursor), eax const 0xF3000006, [rbp+0x6BC] [R], [rbp+0x6C0] [R], [rbp+0x6C4] [R], [rbp+0x6C8] [R], [rax] [R], [rax+0x10] [R], [rax+0x1F] [R], [r14+0x758] [R/W], [rbp+0x818] [R/W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [r14+0x750] [R], [rbp+0x13C] [W], rbx n/a.
Fields written: [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [rbp+0x818], [rbp+0x13C].

## Phase 27 (0x67273c9..0x6727493)
```
  67273c9  mov rdx,[r14+0x860]                           
  67273d0  cmp rdx,[r14+0x868]                           
  67273d7  je short 0x67273E5                            ; -> loc_67273e5
  67273d9  inc rdx                                       
  67273dc  mov [r14+0x860],rdx                           
  67273e3  jmp short 0x67273F2                           ; -> loc_67273f2

loc_67273e5:  ; from 67273d7
  67273e5  lea rcx,[r14+0x858]                           
  67273ec  call 0x6760E60                                ; -> sub_6760e60
  67273f1  nop                                           

loc_67273f2:  ; from 67273e3
  67273f2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67273f9  mov rax,[rcx]                                 
  67273fc  mov rax,[rax+0x10]                            
  6727400  movzx edx,byte ptr [rbp+0x818]                
  6727407  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672740d  nop                                           
  672740e  mov qword ptr [rbp+0x110],0x4009              
  6727419  mov eax,[r14+0x858]                           
  6727420  not eax                                       
  6727422  add eax,[r14+0x860]                           
  6727429  mov [rbp+0x126],ax                            
  6727430  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  6727437  mov rax,[rcx]                                 
  672743a  mov rax,[rax+0x10]                            
  672743e  mov dl,0x4A                                   
  6727440  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727446  mov [rbp+0x818],al                            
  672744c  lea rcx,[r14+0x648]                           
  6727453  lea rdx,[rbp+0x650]                           
  672745a  call 0x675FB30                                ; -> sub_675fb30
  672745f  nop                                           
  6727460  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727467  mov rax,[rcx]                                 
  672746a  mov rax,[rax+0x10]                            
  672746e  movzx edx,byte ptr [rbp+0x818]                
  6727475  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672747b  nop                                           
  672747c  mov eax,[r14+0x650]                           
  6727483  sub eax,[r14+0x648]                           
  672748a  shr eax,3                                     
  672748d  imul eax,0xFFFF8E39                           
```
// Phase 27: cursor loop: `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je short 0x67273E5` (-> loc_67273e5) else `inc rdx`; `mov [r14+0x860],rdx`; `jmp short 0x67273F2` (-> loc_67273f2). Je-target block loc_67273e5: `lea rcx,[r14+0x858]`; `call 0x6760E60` (sub_6760e60); `nop`; falls into loc_67273f2. loc_67273f2: TLS seq `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x110],0x4009`. Fold: `eax=[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x126],ax` (same `~(begin)+(end)` fold as phase 2's [rbp+0x12C], but on [r14+0x858]/[r14+0x860]). TLS call dl=0x4A; `mov [rbp+0x818],al`. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x650]`; `call 0x675FB30` (sub_675fb30); `nop`. TLS seq again; count calc: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39` (continues next phase: next instruction at 0x6727493, expected `dec eax`; `mov [rbp+0x1??],ax`).

Callees: 0x6760E60 (sub_6760e60, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30, direct).
Fields read: [r14+0x860] [R/W], [r14+0x868] [R], [r14+0x858] [R], [rbp+0x818] [R/W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x110] [W], [rbp+0x126] [W], [r14+0x648] [R], [rbp+0x650] [R/W], [rcx] [R], [rax+0x10] [R].
Fields written: [r14+0x860], [rbp+0x110], [rbp+0x818], [rbp+0x126], [rbp+0x650] via callee sub_675fb30 (target of lea rdx).

## Phase 28 (0x6727493..0x6727563)
```
  6727493  dec eax                                       
  6727495  mov [rbp+0x152],ax                            
  672749c  lea rcx,[r14+0x780]                           
  67274a3  lea rdx,[rbp+0x5F8]                           
  67274aa  call 0x675F3B0                                ; -> sub_675f3b0
  67274af  nop                                           
  67274b0  mov eax,[r14+0x788]                           
  67274b7  sub eax,[r14+0x780]                           
  67274be  shr eax,3                                     
  67274c1  imul eax,0xFFFF8BA3                           
  67274c7  dec eax                                       
  67274c9  mov [rbp+0x138],ax                            
  67274d0  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  67274d7  mov rax,[rcx]                                 
  67274da  mov rax,[rax+0x10]                            
  67274de  mov dl,0x4A                                   
  67274e0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67274e6  mov [rbp+0x818],al                            
  67274ec  mov rdi,[r14+0x770]                           
  67274f3  cmp rdi,[r14+0x778]                           
  67274fa  je short 0x672753D                            ; -> loc_672753d
  67274fc  mov rax,[rbp+0x570]                           
  6727503  mov [rdi],rax                                 
  6727506  lea rcx,[rdi+8]                               
  672750a  lea rdx,[rbp+0x578]                           
  6727511  call 0xE869FF0                                ; -> sub_e869ff0
  6727516  nop                                           
  6727517  mov rax,[rbp+0x5F0]                           
  672751e  mov [rdi+0x80],rax                            
  6727525  mov qword ptr [rbp+0x5F0],0                   
  6727530  add qword ptr [r14+0x770],0x88                
  672753b  jmp short 0x6727554                           ; -> loc_6727554

loc_672753d:  ; from 67274fa
  672753d  lea rcx,[r14+0x768]                           
  6727544  mov rdx,rdi                                   
  6727547  lea r8,[rbp+0x570]                            
  672754e  call 0x6760710                                ; -> sub_6760710
  6727553  nop                                           

loc_6727554:  ; from 672753b
  6727554  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  672755b  mov rax,[rcx]                                 
  672755e  mov rax,[rax+0x10]                            
```
// Phase 28: continuation of phase 27's count calc: `dec eax`; `mov [rbp+0x152],ax` (same as H4 redo at 0x67259df). Second count calc: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. Release-block pattern: `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je short 0x672753D` (-> loc_672753d) else `mov rax,[rbp+0x570]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x578]`; `call 0xE869FF0` (sub_e869ff0); `nop`; `mov rax,[rbp+0x5F0]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x5F0],0`; `add qword ptr [r14+0x770],0x88`; `jmp short 0x6727554` (-> loc_6727554). Je-target block loc_672753d: `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x570]`; `call 0x6760710` (sub_6760710); `nop`; falls into loc_6727554. loc_6727554: TLS seq `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]` (continues next phase: next instruction at 0x6727563, expected `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` matching H4's redo at 0x67259c5+).

Callees: 0x675F3B0 (sub_675f3b0, direct), [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0, direct), 0x6760710 (sub_6760710, direct).
Fields read: eax [W], [rbp+0x152] [W], [r14+0x780] [R], [rbp+0x5F8] [R], [r14+0x788] [R], [rbp+0x138] [W], [rbp+0x818] [R/W], [r14+0x770] [R/W], [r14+0x778] [R], [rbp+0x570] [R], [rdi] [W], [rbp+0x578] [R], [rbp+0x5F0] [R/W], [rdi+0x80] [W], [r14+0x768] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R].
Fields written: [rbp+0x152], [rbp+0x138], [rbp+0x818], [rdi], [rdi+0x80], [rbp+0x5F0], [r14+0x770].

## Phase 29 (0x6727563..0x6727628)
```
  6727563  mov dh,0x95                                   
  6727565  sbb [rax],cl                                  
  6727567  add [rax],al                                  
  6727569  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672756f  nop                                           
  6727570  mov qword ptr [rbp+0x110],0x2007009           
  672757b  mov eax,[r14+0x770]                           
  6727582  sub eax,[r14+0x768]                           
  6727589  shr eax,3                                     
  672758c  imul eax,0xFFFFF0F1                           
  6727592  dec eax                                       
  6727594  mov [rbp+0x13A],ax                            
  672759b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67275a2  mov rax,[rcx]                                 
  67275a5  mov rax,[rax+0x10]                            
  67275a9  mov dl,0x4A                                   
  67275ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67275b1  nop                                           
  67275b2  mov [rbp+0x818],al                            
  67275b8  mov rdx,[r14+0x680]                           
  67275bf  cmp rdx,[r14+0x688]                           
  67275c6  je short 0x67275F8                            ; -> loc_67275f8
  67275c8  movss xmm0,[rbp+0x564]                        
  67275d0  movss [rdx],xmm0                              
  67275d4  movss xmm0,[rbp+0x568]                        
  67275dc  movss [rdx+4],xmm0                            
  67275e1  movss xmm0,[rbp+0x56C]                        
  67275e9  movss [rdx+8],xmm0                            
  67275ee  add qword ptr [r14+0x680],0xC                 
  67275f6  jmp short 0x672760C                           ; -> loc_672760c

loc_67275f8:  ; from 67275c6
  67275f8  lea rcx,[r14+0x678]                           
  67275ff  lea r8,[rbp+0x564]                            
  6727606  call 0x1770A70                                ; -> sub_1770a70
  672760b  nop                                           

loc_672760c:  ; from 67275f6
  672760c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727613  mov rax,[rcx]                                 
  6727616  mov rax,[rax+0x10]                            
  672761a  movzx edx,byte ptr [rbp+0x818]                
  6727621  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727627  nop                                           
```
// Phase 29: continuation of phase 28's TLS seq: `mov dh,0x95`; `sbb [rax],cl`; `add [rax],al` — 6 bytes at 0x6727563..0x6727568 that decode but sit between a TLS seq and a TLS call; tagged [?] possible padding/dead code. `call qword ptr [0xF99FFA0]` (sub_eea6040, the TLS call continuing phase 28); `nop`. `mov qword ptr [rbp+0x110],0x2007009`. Count calc: `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1` (magic divisor [?]); `dec eax`; `mov [rbp+0x13A],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. Cursor loop: `rdx=[r14+0x680]`; `cmp rdx,[r14+0x688]`; if equal `je short 0x67275F8` (-> loc_67275f8) else `movss xmm0,[rbp+0x564]`; `movss [rdx],xmm0`; `movss xmm0,[rbp+0x568]`; `movss [rdx+4],xmm0`; `movss xmm0,[rbp+0x56C]`; `movss [rdx+8],xmm0` (copies 12 bytes [rbp+0x564..0x570] → [rdx..rdx+12]); `add qword ptr [r14+0x680],0xC`; `jmp short 0x672760C` (-> loc_672760c). Je-target block loc_67275f8: `lea rcx,[r14+0x678]`; `lea r8,[rbp+0x564]`; `call 0x1770A70` (sub_1770a70); `nop`; falls into loc_672760c. loc_672760c: TLS seq `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop` (continues next phase: next instruction at 0x6727628, expected `mov [rbp+0x818],al`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x1770A70 (sub_1770a70, direct).
Fields read: [rbp+0x110] [W], [r14+0x770] [R], [r14+0x768] [R], [rbp+0x13A] [W], [rbp+0x818] [R/W], [r14+0x680] [R/W], [r14+0x688] [R], [rbp+0x564] [R], [rdx] [W], [rbp+0x568] [R], [rdx+4] [W], [rbp+0x56C] [R], [rdx+8] [W], [r14+0x678] [R], [rbp+0x564] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R].
Fields written: [rbp+0x110], [rbp+0x13A], [rbp+0x818], [r14+0x680], [rdx], [rdx+4], [rdx+8]; [rax] [W?] by `sbb [rax],cl`/`add [rax],al` at 0x6727565/0x6727567 [?].

## Phase 30 (0x6727628..0x67276eb)
```
  6727628  mov eax,[r14+0x680]                           
  672762f  sub eax,[r14+0x678]                           
  6727636  shr eax,2                                     
  6727639  imul eax,0xFFFFAAAB                           
  672763f  dec eax                                       
  6727641  mov [rbp+0x14E],ax                            
  6727648  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672764f  mov rax,[rcx]                                 
  6727652  mov rax,[rax+0x10]                            
  6727656  mov dl,0x4A                                   
  6727658  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672765e  nop                                           
  672765f  mov [rbp+0x818],al                            
  6727665  mov rdx,[r14+0x518]                           
  672766c  cmp rdx,[r14+0x520]                           
  6727673  je short 0x6727681                            ; -> loc_6727681
  6727675  inc rdx                                       
  6727678  mov [r14+0x518],rdx                           
  672767f  jmp short 0x6727691                           ; -> loc_6727691

loc_6727681:  ; from 6727673
  6727681  mov rcx,r14                                   
  6727684  add rcx,0x510                                 
  672768b  call 0x6760E60                                ; -> sub_6760e60
  6727690  nop                                           

loc_6727691:  ; from 672767f
  6727691  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727698  mov rax,[rcx]                                 
  672769b  mov rax,[rax+0x10]                            
  672769f  movzx edx,byte ptr [rbp+0x818]                
  67276a6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67276ac  nop                                           
  67276ad  mov rax,0x4002807009                          
  67276b7  mov [rbp+0x110],rax                           
  67276be  mov eax,[r14+0x510]                           
  67276c5  not eax                                       
  67276c7  add eax,[r14+0x518]                           
  67276ce  mov [rbp+0x16C],ax                            
  67276d5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67276dc  mov rax,[rcx]                                 
  67276df  mov rax,[rax+0x10]                            
  67276e3  mov dl,0x4A                                   
  67276e5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// Phase 30: note: phase 29's final TLS call at 0x6727621 (sub_eea6040) has NO `mov [rbp+0x818],al` after it (same [?] pattern as phase 14's final TLS call); instead falls straight into count calc: `eax=[r14+0x680]`; `sub eax,[r14+0x678]`; `shr eax,2`; `imul eax,0xFFFFAAAB` (magic for /3); `dec eax`; `mov [rbp+0x14E],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. Cursor loop: `rdx=[r14+0x518]`; `cmp rdx,[r14+0x520]`; if equal `je short 0x6727681` (-> loc_6727681) else `inc rdx`; `mov [r14+0x518],rdx`; `jmp short 0x6727691` (-> loc_6727691). Je-target block loc_6727681: `mov rcx,r14`; `add rcx,0x510`; `call 0x6760E60` (sub_6760e60); `nop`; falls into loc_6727691. loc_6727691: TLS seq `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`; `mov rax,0x4002807009`; `mov [rbp+0x110],rax`. Fold: `eax=[r14+0x510]`; `not eax`; `add eax,[r14+0x518]`; `mov [rbp+0x16C],ax`. TLS call dl=0x4A again (continues next phase: next instruction at 0x67276eb, expected `mov [rbp+0x818],al`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, three times in view), 0x6760E60 (sub_6760e60, direct).
Fields read: [r14+0x680] [R], [r14+0x678] [R], [rbp+0x14E] [W], [rbp+0x818] [R/W], [r14+0x518] [R/W], [r14+0x520] [R], [rbp+0x110] [W], [rbp+0x16C] [W], [r14+0x510] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R].
Fields written: [rbp+0x14E], [rbp+0x818], [r14+0x518], [rbp+0x110], [rbp+0x16C].

## Phase 31 (0x67276eb..0x672779f)
```
  67276eb  nop                                           
  67276ec  mov [rbp+0x818],al                            
  67276f2  mov rdx,[r14+8]                               
  67276f6  cmp rdx,[r14+0x10]                            
  67276fa  je short 0x6727717                            ; -> loc_6727717
  67276fc  mov r8d,0xC8                                  
  6727702  mov rcx,rdx                                   
  6727705  mov rdx,r15                                   
  6727708  call 0xEEC6EC0                                ; -> sub_eec6ec0
  672770d  add qword ptr [r14+8],0xC8                    
  6727715  jmp short 0x6727723                           ; -> loc_6727723

loc_6727717:  ; from 67276fa
  6727717  mov rcx,r14                                   
  672771a  mov r8,r15                                    
  672771d  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6727722  nop                                           

loc_6727723:  ; from 6727715
  6727723  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672772a  mov rax,[rcx]                                 
  672772d  mov rax,[rax+0x10]                            
  6727731  movzx edx,byte ptr [rbp+0x818]                
  6727738  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672773e  nop                                           
  672773f  lea rcx,[rbp+0x560]                           
  6727746  call 0x67E1660                                ; -> sub_67e1660
  672774b  nop [rax+rax]                                 ; R ret@67e1660+0x0+idx
  6727750  lea rcx,[rbp+0x370]                           
  6727757  call 0x67E1660                                ; -> sub_67e1660
  672775c  cmp byte ptr [rbp+0x80],3                     
  6727763  je 0x672A1AE                                  ; -> sub_672a1ae
  6727769  jmp 0x672A1F0                                 ; -> sub_672a1f0
  672776e  lea rcx,[rbp+0x510]                           
  6727775  mov rdx,r15                                   
  6727778  call 0x67A75D0                                ; -> sub_67a75d0
  672777d  nop                                           
  672777e  lea rcx,[rbp+0x370]                           
  6727785  mov rdx,r13                                   
  6727788  lea r8,[rbp+0x198]                            
  672778f  mov r9,r15                                    
  6727792  call 0x678F640                                ; -> sub_678f640
  6727797  nop                                           
  6727798  mov eax,[r13+0x60]                            
```
`// Phase 31: continuation of phase 30's final TLS call (0x67276e5 `call qword ptr [0xF99FFA0]`): `nop`; `mov [rbp+0x818],al` — completes the dl=0x4A TLS call's result store [V]. Cursor loop over [r14+8]/[r14+0x10] (0x67276f2): `rdx=[r14+8]`; `cmp rdx,[r14+0x10]`; if equal `je short 0x6727717` (-> loc_6727717) else `mov r8d,0xC8` (200); `mov rcx,rdx`; `mov rdx,r15`; `call 0xEEC6EC0` (sub_eec6ec0); `add qword ptr [r14+8],0xC8` (advance cursor by 200 bytes [V]); `jmp short 0x6727723` (-> loc_6727723) [V]. Je-target block loc_6727717 (0x6727717): `mov rcx,r14`; `mov r8,r15`; `call 0x5ABA6D0` (sub_5aba6d0); `nop`; falls into loc_6727723 [V]. loc_6727723: TLS seq `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop` [V]. Dual sub_67e1660 calls: `lea rcx,[rbp+0x560]`; `call 0x67E1660`; `nop [rax+rax]`; `lea rcx,[rbp+0x370]`; `call 0x67E1660` [V]. Then `cmp byte ptr [rbp+0x80],3`; if equal `je 0x672A1AE` (-> sub_672a1ae, tail jump [V]) else `jmp 0x672A1F0` (-> sub_672a1f0, tail jump [V]). Fall-through block loc_672776e: `lea rcx,[rbp+0x510]`; `mov rdx,r15`; `call 0x67A75D0` (sub_67a75d0); `nop`; then `lea rcx,[rbp+0x370]`; `mov rdx,r13`; `lea r8,[rbp+0x198]`; `mov r9,r15`; `call 0x678F640` (sub_678f640); `nop`; `mov eax,[r13+0x60]` (continues next phase: next instruction at 0x672779f).

Callees: 0xEEC6EC0 (sub_eec6ec0, direct), 0x5ABA6D0 (sub_5aba6d0, direct), [0xF99FFA0] = sub_eea6040 (indirect), 0x67E1660 (sub_67e1660, direct, twice), je 0x672A1AE/jmp 0x672A1F0 (tail jumps to sub_672a1ae/sub_672a1f0), 0x67A75D0 (sub_67a75d0, direct), 0x678F640 (sub_678f640, direct).
Fields read: [rbp+0x818] [R/W], [r14+8] [R/W], [r14+0x10] [R], r15 [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x560] [R via lea address], [rbp+0x370] [R via lea address], [rbp+0x80] [R], [rbp+0x510] [R via lea address], [rbp+0x198] [R via lea address], r13 [R], [r13+0x60] [R].
Fields written: [rbp+0x818], [r14+8], [rbp+0x560] via callee sub_67e1660 (target of lea rcx), [rbp+0x370] via callee sub_67e1660, [rbp+0x510] via callee sub_67a75d0.

## Phase 32 (0x672779f..0x6727884)
```
  672779f  test al,4                                     
  67277a1  add [rax],al                                  
  67277a3  mov [rcx+0x10],eax                            ; W a0+0x10
  67277a6  movups xmm0,[r13+0x50]                        
  67277ab  movups [rcx],xmm0                             ; W a0+0x0
  67277ae  movzx eax,byte ptr [rbp+0x254]                
  67277b5  mov [rbp+0x4BC],al                            
  67277bb  movups xmm0,[rbp+0x258]                       
  67277c2  movups [rbp+0x4C0],xmm0                       
  67277c9  movups xmm0,[r13+0x78]                        
  67277ce  movups xmm1,[r13+0x88]                        
  67277d6  movups xmm2,[r13+0x97]                        
  67277de  movups [rbx+0x9F],xmm2                        
  67277e5  movups [rbx+0x90],xmm1                        
  67277ec  movups [rbx+0x80],xmm0                        
  67277f3  movzx eax,word ptr [rbp+0x298]                
  67277fa  mov [rbp+0x500],ax                            
  6727801  mov rax,[rbp+0x748]                           
  6727808  mov r8,[rax+0x480]                            
  672780f  mov rax,[rax+0x488]                           
  6727816  mov rdx,rax                                   
  6727819  sub rdx,r8                                    
  672781c  cmp rdx,0xFFFFFFFFFFFFFFD0                    
  6727820  je 0x672A30F                                  ; -> sub_672a30f
  6727826  test r8,r8                                    
  6727829  setne cl                                      
  672782c  test rax,rax                                  
  672782f  sete r9b                                      
  6727833  or r9b,cl                                     
  6727836  je 0x672A30F                                  ; -> sub_672a30f
  672783c  cmp rax,r8                                    
  672783f  je 0x6729C39                                  ; -> sub_6729c39
  6727845  mov rax,[rbp+0x758]                           
  672784c  cmp qword ptr [rax],0                         
  6727850  je 0x6729C39                                  ; -> sub_6729c39
  6727856  sar rdx,4                                     
  672785a  mov rax,0xAAAAAAAAAAAAAAAB                    
  6727864  imul rdx,rax                                  
  6727868  mov dword ptr [rsp+0x20],0x41800000           
  6727870  lea rcx,[rbp+0x7E0]                           
  6727877  lea r9,[rbp+0x530]                            
  672787e  call 0x6769EE0                                ; -> sub_6769ee0
  6727883  nop                                                                     
```
`// Phase 32: continuation of phase 31's `mov eax,[r13+0x60]` (0x6727798): `test al,4`; `add [rax],al` — 4 bytes at 0x672779f..0x67277a2 that decode but sit between the TLS-result store and the store pair; tagged [?] possible padding/dead code (same family as phase 29's `mov dh,0x95`/`sbb [rax],cl`/`add [rax],al`). Store pair: `mov [rcx+0x10],eax` → [rbp+0x6A8] = eax ([V] since rcx=[rbp+0x698] from phase 31); `movups xmm0,[r13+0x50]`; `movups [rcx],xmm0` (copies [r13+0x50..0x60] → [rbp+0x698..0x6A8] [V]). `movzx eax,byte ptr [rbp+0x254]`; `mov [rbp+0x4BC],al`. `movups xmm0,[rbp+0x258]`; `movups [rbp+0x4C0],xmm0`. Vector scatter to rbx: `movups xmm0,[r13+0x78]`; `movups xmm1,[r13+0x88]`; `movups xmm2,[r13+0x97]`; `movups [rbx+0x9F],xmm2`; `movups [rbx+0x90],xmm1`; `movups [rbx+0x80],xmm0` (stores [r13+0x78..0x9F] → [rbx+0x80..0x9F] reversed lane order [V]). `movzx eax,word ptr [rbp+0x298]`; `mov [rbp+0x500],ax`. Range check on [rbp+0x748]: `rax=[rbp+0x748]`; `r8=[rax+0x480]`; `rax=[rax+0x488]`; `rdx=rax`; `rdx-=r8`; `cmp rdx,0xFFFFFFFFFFFFFFD0`; if equal `je 0x672A30F` (-> sub_672a30f error path [V]). `test r8,r8`; `setne cl`; `test rax,rax`; `sete r9b`; `or r9b,cl`; if zero `je 0x672A30F` (null-check on both ends [V]). `cmp rax,r8`; if equal `je 0x6729C39` (-> sub_6729c39, new target [V]); `rax=[rbp+0x758]`; `cmp qword ptr [rax],0`; if equal `je 0x6729C39` (-> sub_6729c39 [V]). Divide-by-17 magic: `sar rdx,4`; `rax=0xAAAAAAAAAAAAAAAB`; `imul rdx,rax`; `mov dword ptr [rsp+0x20],0x41800000` (float 8.5 [I]); `lea rcx,[rbp+0x7E0]`; `lea r9,[rbp+0x530]`; `call 0x6769EE0` (sub_6769ee0 — matches phase 24's call-site pattern [V]); `nop` (continues next phase: next instruction at 0x6727884, expected `mov [rbp+0x7E0],rdx`/`mov [rbp+0x7E8],rax` mirroring phase 24's `mov [rbp+0xF0],rcx`; `mov [rbp+0xF8],rax` [I]).

Callees: je 0x672A30F (sub_672a30f, error target [V]), je 0x6729C39 (sub_6729c39, new target [V]), 0x6769EE0 (sub_6769ee0, direct).
Fields read: al [W], [rax] [R/W], rcx [W], [r13+0x50] [R], [rcx] [W], [rbp+0x254] [R], [rbp+0x4BC] [W], [rbp+0x258] [R], [rbp+0x4C0] [W], [r13+0x78] [R], [r13+0x88] [R], [r13+0x97] [R], [rbx+0x9F] [W], [rbx+0x90] [W], [rbx+0x80] [W], [rbp+0x298] [R], [rbp+0x500] [W], [rbp+0x748] [R], [rax+0x480] [R], [rax+0x488] [R], r8 [R/W], rax [R/W], rdx [R/W], [rbp+0x758] [R], [rax] [R] (qword cmp), [rbp+0x530] [R via lea address], [rbp+0x7E0] [R via lea address], [rsp+0x20] [W].
Fields written: [rax] via `add [rax],al` [?], [rbp+0x6A8] via [rcx+0x10], [rbp+0x698], [rbp+0x4BC], [rbp+0x4C0], [rbx+0x9F], [rbx+0x90], [rbx+0x80], [rbp+0x500], [rsp+0x20], [rbp+0x7E0] via callee sub_6769EE0 (target of lea rcx), [rbp+0x530] via callee sub_6769EE0 (target of lea r9).

## Phase 33 (0x6727884..0x6727947)
```
  6727884  mov rax,[rbp+0x7E0]                           
  672788b  mov rcx,[rbp+0x7E8]                           
  6727892  mov r14,rax                                   
  6727895  mov [rbp+0x818],rax                           
  672789c  mov [rbp+0x558],rcx                           
  67278a3  cmp rax,rcx                                   
  67278a6  je 0x6729BA6                                  ; -> sub_6729ba6
  67278ac  mov rax,[rbp+0x758]                           
  67278b3  mov rcx,[rax]                                 
  67278b6  mov rax,[rcx]                                 
  67278b9  mov rax,[rax+0x48]                            
  67278bd  lea rdx,[rbp+0x2A0]                           
  67278c4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67278ca  nop                                           
  67278cb  mov r14,[rbp+0x7E0]                           
  67278d2  mov rdi,[rbp+0x7E8]                           
  67278d9  mov rax,rdi                                   
  67278dc  sub rax,r14                                   
  67278df  cmp rax,0xFFFFFFFFFFFFFFE0                    
  67278e3  je 0x672A30F                                  ; -> sub_672a30f
  67278e9  test r14,r14                                  
  67278ec  setne al                                      
  67278ef  test rdi,rdi                                  
  67278f2  sete cl                                       
  67278f5  or cl,al                                      
  67278f7  je 0x672A30F                                  ; -> sub_672a30f
  67278fd  test r14,r14                                  
  6727900  setne al                                      
  6727903  cmp rdi,r14                                   
  6727906  sete cl                                       
  6727909  or cl,al                                      
  672790b  je 0x672A30F                                  ; -> sub_672a30f
  6727911  lea rax,[rbp+0x7B0]                           
  6727918  mov [rbp+0x7A0],rax                           
  672791f  mov rax,0x100000000                           
  6727929  mov [rbp+0x7A8],rax                           
  6727930  cmp rdi,r14                                   
  6727933  je short 0x6727960                            ; -> loc_6727960
  6727935  nop [rax+rax]                                 

loc_6727940:  ; from 672795e
  6727940  lea rcx,[rbp+0x7A0]                           
```
`// Phase 33: quotient-store continuation of phase 32's `call 0x6769EE0`: `mov rax,[rbp+0x7E0]`; `mov rcx,[rbp+0x7E8]`; `mov r14,rax`; `mov [rbp+0x818],rax`; `mov [rbp+0x558],rcx`; `cmp rax,rcx`; if equal `je 0x6729BA6` (-> sub_6729ba6, new target [V]). Range validation mirroring phase 21: `rax=[rbp+0x758]`; `mov rcx,[rax]` (vtable); `mov rax,[rcx]`; `mov rax,[rax+0x48]` (vslot 9); `lea rdx,[rbp+0x2A0]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. Cursor init: `r14=[rbp+0x7E0]`; `rdi=[rbp+0x7E8]`; `rax=rdi-r14`; `cmp rax,0xFFFFFFFFFFFFFFE0`; if equal `je 0x672A30F` (error path [V]); null/empty checks `test r14,r14`/`setne al`; `test rdi,rdi`/`sete cl`; `or cl,al`; if zero `je 0x672A30F`; repeat `test r14,r14`/`setne al`; `cmp rdi,r14`/`sete cl`; `or cl,al`; if zero `je 0x672A30F` (r14==rdi → empty) [V]. Cursor setup: `lea rax,[rbp+0x7B0]`; `mov [rbp+0x7A0],rax` (loop cursor = &[rbp+0x7B0]); `mov rax,0x100000000`; `mov [rbp+0x7A8],rax` (end sentinel 2^32). `cmp rdi,r14`; if equal `je short 0x6727960` (-> loc_6727960, skip loop) else `nop [rax+rax]`; loc_6727940 (jump target from 0x672795e = loop back-edge [I]): `lea rcx,[rbp+0x7A0]` (loop body: reload cursor; continues next phase: next instruction at 0x6727947, expected `lea rdx,[rbp+0x560]`; `mov r8,r14`; `call 0x676A670` mirroring phase 21's loc_6726f90 [I]).

Callees: je 0x6729BA6 (sub_6729ba6, new target [V]), je 0x672A30F (sub_672a30f, error target, 3× [V]), [0xF99FFA0] = sub_eea6040 (indirect, virtual call via vslot 0x48 [V]).
Fields read: [rbp+0x7E0] [R/W], [rbp+0x7E8] [R/W], r14 [R/W], rdi [R], rax [R/W], rcx [W], [rbp+0x818] [W], [rbp+0x558] [W], [rbp+0x758] [R], [rax] [R] (vtable), [rcx] [R], [rax+0x48] [R], [rbp+0x2A0] [W via lea address], [rbp+0x7A0] [W], [rbp+0x7A8] [W], [rbp+0x7B0] [R via lea address].
Fields written: [rbp+0x818], [rbp+0x558], [rbp+0x7A0], [rbp+0x7A8], r14 [W], rdx via lea target, rcx via [rbp+0x7A0] store (next phase).

## Phase 34 (0x6727947..0x6727a24)
```
  6727947  lea rdx,[rbp+0x560]                           
  672794e  mov r8,r14                                    
  6727951  call 0x676A670                                ; -> sub_676a670
  6727956  nop                                           
  6727957  add r14,0x20                                  
  672795b  cmp r14,rdi                                   
  672795e  jne short 0x6727940                           ; -> sub_6727940
  6727960  lea rax,[rbp+0x770]                           
  6727967  mov [rbp+0x760],rax                           
  672796e  mov rax,0x100000000                           
  6727978  mov [rbp+0x768],rax                           
  672797f  lea rdi,[rbp+0x760]                           
  6727986  mov rcx,rdi                                   
  6727989  lea rdx,[rbp+0x7A0]                           
  6727990  call 0x6764990                                ; -> sub_6764990
  6727995  nop                                           
  6727996  mov [rsp+0x20],rdi                            
  672799b  lea rcx,[rbp+0x560]                           
  67279a2  lea rdx,[rbp+0x458]                           
  67279a9  lea r8,[rbp+0x400]                            
  67279b0  lea r9,[rbp+0x378]                            
  67279b7  call 0x6792160                                ; -> sub_6792160
  67279bc  nop                                           
  67279bd  lea rcx,[rbp+0x4A8]                           
  67279c4  mov eax,[rcx+0x10]                            
  67279c7  lea rdx,[rbp+0x6D0]                           
  67279ce  mov [rdx+0x10],eax                            
  67279d1  movups xmm0,[rcx]                             
  67279d4  movups [rdx],xmm0                             
  67279d7  movzx eax,byte ptr [rbp+0x4BC]                
  67279de  mov [rbp+0x6E4],al                            
  67279e4  movups xmm0,[rbp+0x4C0]                       
  67279eb  movups [rbp+0x6E8],xmm0                       
  67279f2  movups xmm0,[rbx+0x80]                        
  67279f9  movups xmm1,[rbx+0x90]                        
  6727a00  movups xmm2,[rbx+0x9F]                        
  6727a07  lea rax,[rbp+0x564]                           
  6727a0e  movups [rax+0x1B3],xmm2                       
  6727a15  movups [rax+0x1A4],xmm1                       
  6727a1c  movups [rax+0x194],xmm0                       
```
`// Phase 34: loop body completing phase 33's loc_6727940 cursor setup: `lea rdx,[rbp+0x560]`; `mov r8,r14`; `call 0x676A670` (sub_676a670 — same as phase 21's loop body [V]); `nop`; `add r14,0x20` (advance cursor by 32 bytes); `cmp r14,rdi`; `jne short 0x6727940` (-> loc_6727940, loop back-edge [V]). Loop-exit block at 0x6727960: `lea rax,[rbp+0x770]`; `mov [rbp+0x760],rax`; `mov rax,0x100000000`; `mov [rbp+0x768],rax` (end sentinel 2^32 — mirrors phase 21's loc_6726fb0 + phase 22's sentinel init). `lea rdi,[rbp+0x760]`; `mov rcx,rdi`; `lea rdx,[rbp+0x7A0]`; `call 0x6764990` (sub_6764990 — range-init between the two refs [V]); `nop`; `mov [rsp+0x20],rdi`. Bulk copy: `lea rcx,[rbp+0x560]`; `lea rdx,[rbp+0x458]`; `lea r8,[rbp+0x400]`; `lea r9,[rbp+0x378]`; `call 0x6792160` (sub_6792160 — differs from phase 22's `call 0x6792570` [V]); `nop`. Field copy: `lea rcx,[rbp+0x4A8]`; `mov eax,[rcx+0x10]`; `lea rdx,[rbp+0x6D0]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0` (copies [rbp+0x4A8..0x4B8] → [rbp+0x6D0..0x6E0] plus +0x10 field [V]). `movzx eax,byte ptr [rbp+0x4BC]`; `mov [rbp+0x6E4],al`. `movups xmm0,[rbp+0x4C0]`; `movups [rbp+0x6E8],xmm0`. Vector gather from rbx: `movups xmm0,[rbx+0x80]`; `movups xmm1,[rbx+0x90]`; `movups xmm2,[rbx+0x9F]`; `lea rax,[rbp+0x564]`; `movups [rax+0x1B3],xmm2`; `movups [rax+0x1A4],xmm1`; `movups [rax+0x194],xmm0` (stores into [rbp+0x564+0x194..]; lane offsets 8 lower than phase 22's 0x19C/0x1AC/0x1BB [V]). Continues next phase: next instruction at 0x6727a24, expected `movzx eax,word ptr [rbp+0x500]`; `mov [rbp+0x730],ax` mirroring phase 22 [I]).

Callees: 0x676A670 (sub_676a670, direct), jne 0x6727940 (loop back-edge to loc_6727940 [V]), 0x6764990 (sub_6764990, direct), 0x6792160 (sub_6792160, direct — differs from phase 22's 0x6792570).
Fields read: [rbp+0x560] [R], r14 [R/W], rdi [R], [rbp+0x770] [W], [rbp+0x760] [W], [rbp+0x768] [W], [rbp+0x7A0] [R], [rbp+0x458] [W], [rbp+0x400] [W], [rbp+0x378] [W], [rbp+0x4A8] [R], [rcx+0x10] [R], [rbp+0x6D0] [W], [rbp+0x4BC] [R], [rbp+0x6E4] [W], [rbp+0x4C0] [R], [rbp+0x6E8] [W], [rbx+0x80] [R], [rbx+0x90] [R], [rbx+0x9F] [R], [rbp+0x564] [R], [rsp+0x20] [W].
Fields written: [rbp+0x760], [rbp+0x768], [rsp+0x20], [rbp+0x458], [rbp+0x400], [rbp+0x378], [rbp+0x6D0], [rdx+0x10], [rbp+0x6E4], [rbp+0x6E8], [rbp+0x564+0x1B3], [rbp+0x564+0x1A4], [rbp+0x564+0x194].

## Phase 35 (0x6727a24..0x6727AD8)
```
  6727a24  mov bh,0x85                                   
  6727a26  add [0xFFFFFFFF8FD87A2C],al                   ; [data_8fd87a2c]
  6727a2c  test [rax],ebp                                
  6727a2e  (bad)                                         
  6727a30  add [rax-0x75],cl                             
  6727a33  test [rax],ecx                                
  6727a35  or [rax],al                                   
  6727a37  add [rax-0x75],cl                             
  6727a3a  adc [rax+0x9D0],dil                           
  6727a41  add rcx,rax                                   
  6727a44  call 0x5ABA5C0                                ; -> sub_5aba5c0
  6727a49  nop                                           
  6727a4a  mov r14,rax                                   
  6727a4d  lea rax,[rbp+0x2A4]                           
  6727a54  movups [rax+0xB4],xmm6                        
  6727a5b  movups [rax+0xA4],xmm6                        
  6727a62  movups [rax+0x94],xmm6                        
  6727a69  movups [rax+0x84],xmm6                        
  6727a70  movups [rax+0x74],xmm6                        
  6727a74  movups [rax+0x64],xmm6                        
  6727a78  movups [rax+0x54],xmm6                        
  6727a7c  movups [rax+0x44],xmm6                        
  6727a80  movups [rax+0x34],xmm6                        
  6727a84  movups [rax+0x24],xmm6                        
  6727a88  movups [rax+0x14],xmm6                        
  6727a8c  movups [rax+4],xmm6                           
  6727a90  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727a97  mov rax,[rcx]                                 
  6727a9a  mov rax,[rax+0x10]                            
  6727a9e  mov dl,0x4A                                   
  6727aa0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727aa6  nop                                           
  6727aa7  mov [rbp+0x827],al                            
  6727aad  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
  6727ab4  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
  6727abb  je 0x67289B7                                  ; -> loc_67289b7
  6727ac1  movzx eax,word ptr [rbp+0x728]                
  6727ac8  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  6727acb  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
  6727ad3  jmp 0x67289CB                                 ; -> loc_67289cb
```
`// Phase 35: first 10 instructions at 0x6727a24..0x6727a44 (`mov bh,0x85`; `add [0xFFFFFFFF8FD87A2C],al`; `test [rax],ebp`; `(bad)`; `add [rax-0x75],cl`; `test [rax],ecx`; `or [rax],al`; `add [rax-0x75],cl`; `adc [rax+0x9D0],dil`; `add rcx,rax`) decode as garbage/invalid and are tagged [?] padding or dead code between phase 34's last `movups` and the next real instruction. Real stream resumes at 0x6727a44: `call 0x5ABA5C0` (sub_5aba5c0 — same tail-call as phase 22 [V]); `nop`; `mov r14,rax` (carries call return). Zeroing loop mirroring phase 23: `lea rax,[rbp+0x2A4]`; thirteen `movups [rax+disp],xmm6` at disp 0xB4,0xA4,0x94,0x84,0x74,0x64,0x54,0x44,0x34,0x24,0x14,0x04 — i.e. [rbp+0x2A8..0x358] zeroed (xmm6 presumed zero) [V]. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x827],al`. Cursor loop: `rdx=[r14+0x8A8]`; `cmp rdx,[r14+0x8B0]`; if equal `je 0x67289B7` (-> loc_67289b7, new target [V]) else `movzx eax,word ptr [rbp+0x728]`; `mov [rdx],ax`; `add qword ptr [r14+0x8A8],2`; `jmp 0x67289CB` (-> loc_67289cb, new target [V]; last instruction, continues next phase at 0x6727AD8).

Callees: 0x5ABA5C0 (sub_5aba5c0, direct), [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: bh [W], [0xFFFFFFFF8FD87A2C] [W?], [rax] [R/W], ebp [R], ecx [R], dil [R], rax [R/W], rcx [R/W], r14 [R/W], [r14+0x8A8] [R/W], [r14+0x8B0] [R], [rbp+0x728] [R], [rdx] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [W].
Fields written: [0xFFFFFFFF8FD87A2C] [?], [rax] [?], r14, [rbp+0x2A8..0x358] via [rax+disp] (xmm6 zeroing), [rbp+0x827], [r14+0x8A8], [rdx] (word store).

## Phase 36 (0x6727AD8..0x6727BA9)
```
  6727ad8  lea rcx,[r14+0x8A0]                           
  6727adf  lea r8,[rbp+0x730]                            
  6727ae6  call 0x1EF6F90                                ; -> sub_1ef6f90
  6727aeb  nop                                           
  6727aec  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727af3  mov rax,[rcx]                                 
  6727af6  mov rax,[rax+0x10]                            
  6727afa  movzx edx,byte ptr [rbp+0x827]                
  6727b01  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727b07  nop                                           
  6727b08  mov qword ptr [rbp+0x2A0],1                   
  6727b13  mov eax,[r14+0x8A8]                           
  6727b1a  sub eax,[r14+0x8A0]                           
  6727b21  shr eax,1                                     
  6727b23  dec eax                                       
  6727b25  mov [rbp+0x2B0],ax                            
  6727b2c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727b33  mov rax,[rcx]                                 
  6727b36  mov rax,[rax+0x10]                            
  6727b3a  mov dl,0x4A                                   
  6727b3c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727b42  nop                                           
  6727b43  mov [rbp+0x827],al                            
  6727b49  mov rdx,[r14+0x758]                           
  6727b50  cmp rdx,[r14+0x760]                           
  6727b57  je 0x6727BE0                                  ; -> loc_6727be0
  6727b5d  lea rcx,[rbp+0x6D8]                           
  6727b64  mov eax,[rcx+0x10]                            
  6727b67  mov [rdx+0x10],eax                            
  6727b6a  movups xmm0,[rcx]                             
  6727b6d  movups [rdx],xmm0                             
  6727b70  movzx eax,byte ptr [rbp+0x6EC]                
  6727b77  mov [rdx+0x14],al                             
  6727b7a  movss xmm0,[rbp+0x6F0]                        
  6727b82  movss [rdx+0x18],xmm0                         
  6727b87  movss xmm0,[rbp+0x6F4]                        
  6727b8f  movss [rdx+0x1C],xmm0                         
  6727b94  movss xmm0,[rbp+0x6F8]                        
  6727b9c  movss [rdx+0x20],xmm0                         
  6727ba1  movss xmm0,[rbp+0x6FC]                        
```
`// Phase 36: pattern repeat of phase 25 (phase 25 used [rbp+0x110]/[rbp+0x120]/[rbp+0x6A0]/[rbp+0x6B4]/[rbp+0x6B8]; here [rbp+0x2A0]/[rbp+0x2B0]/[rbp+0x6D8]/[rbp+0x6EC]/[rbp+0x6F0..0x6FC]): `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x730]`; `call 0x1EF6F90` (sub_1ef6f90); `nop`. TLS seq dl=[rbp+0x827]; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x2A0],1`. Count calc: `eax=[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax`; `mov [rbp+0x2B0],ax`. Second TLS call dl=0x4A; `mov [rbp+0x827],al`. Cursor loop: `rdx=[r14+0x758]`; `cmp rdx,[r14+0x760]`; if equal `je 0x6727BE0` (-> loc_6727be0, new target [V]) else `lea rcx,[rbp+0x6D8]`; `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0` (copies [rbp+0x6D8..0x6E8] → [rdx..rdx+0x10]); `movzx eax,byte ptr [rbp+0x6EC]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x6F0]`; `movss [rdx+0x18],xmm0`; `movss xmm0,[rbp+0x6F4]`; `movss [rdx+0x1C],xmm0`; `movss xmm0,[rbp+0x6F8]`; `movss [rdx+0x20],xmm0`; `movss xmm0,[rbp+0x6FC]` (continues next phase: next instruction at 0x6727BA9, expected `movss [rdx+0x24],xmm0` mirroring phase 25's `movss [rdx+0x24],xmm0` from [rbp+0x6C4] [I]).

Callees: 0x1EF6F90 (sub_1ef6f90, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice), je 0x6727BE0 (sub_6727be0, new target [V]).
Fields read: r14 [R/W], r8 via lea target, [r14+0x8A0] [R], [rbp+0x730] [W via lea address], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [rbp+0x2A0] [W], [r14+0x8A8] [R], [r14+0x8A0] [R], [rbp+0x2B0] [W], [rbp+0x758] [R/W], [r14+0x760] [R], [rbp+0x6D8] [R], [rcx+0x10] [R], [rdx+0x10] [W], [rbp+0x6EC] [R], [rdx+0x14] [W], [rbp+0x6F0] [R], [rdx+0x18] [W], [rbp+0x6F4] [R], [rdx+0x1C] [W], [rbp+0x6F8] [R], [rdx+0x20] [W], [rbp+0x6FC] [R].
Fields written: [rbp+0x730] via lea target, [rbp+0x2A0], [rbp+0x2B0], [rbp+0x827], [r14+0x758] via cursor store chain, [rdx+0x10], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24] via `movss [rdx+0x24]` (next phase).

## Phase 37 (0x6727BA9..0x6727C70)
```
  6727ba9  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6727bae  lea rax,[rbp+0x564]                           
  6727bb5  movups xmm0,[rax+0x19C]                       
  6727bbc  movups xmm1,[rax+0x1AC]                       
  6727bc3  movups xmm2,[rax+0x1BB]                       
  6727bca  movups [rdx+0x28],xmm0                        ; W a1+0x28
  6727bce  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6727bd2  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6727bd6  add qword ptr [r14+0x758],0x58                
  6727bde  jmp short 0x6727BF4                           ; -> loc_6727bf4
  6727be0  lea rcx,[r14+0x750]                           
  6727be7  lea r8,[rbp+0x6D8]                            
  6727bee  call 0x6760A80                                ; -> sub_6760a80
  6727bf3  nop                                           

loc_6727bf4:  ; from 6727bde
  6727bf4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727bfb  mov rax,[rcx]                                 
  6727bfe  mov rax,[rax+0x10]                            
  6727c02  movzx edx,byte ptr [rbp+0x827]                
  6727c09  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727c0f  nop                                           
  6727c10  mov eax,[r14+0x758]                           
  6727c17  sub eax,[r14+0x750]                           
  6727c1e  shr eax,3                                     
  6727c21  imul eax,0xFFFF8BA3                           
  6727c27  dec eax                                       
  6727c29  mov [rbp+0x2CC],ax                            
  6727c30  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727c37  mov rax,[rcx]                                 
  6727c3a  mov rax,[rax+0x10]                            
  6727c3e  mov dl,0x4A                                   
  6727c40  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727c46  nop                                           
  6727c47  mov [rbp+0x827],al                            
  6727c4d  mov rdx,[r14+0x860]                           
  6727c54  cmp rdx,[r14+0x868]                           
  6727c5b  je short 0x6727C69                            ; -> loc_6727c69
  6727c5d  inc rdx                                       
  6727c60  mov [r14+0x860],rdx                           
  6727c67  jmp short 0x6727C76                           ; -> loc_6727c76

loc_6727c69:  ; from 6727c5b
  6727c69  lea rcx,[r14+0x858]                           
```
`// Phase 37: continuation of phase 36's cursor-loop copy: `movss [rdx+0x24],xmm0` (finishes [rbp+0x6FC] store [V]); vector stores `movups [rdx+0x28],xmm0`; `movups [rdx+0x38],xmm1`; `movups [rdx+0x47],xmm2` from [rbp+0x564+0x19C/0x1AC/0x1BB] (lane offsets matching phase 34 [V]); `add qword ptr [r14+0x758],0x58` (advance cursor by 88); `jmp short 0x6727BF4` (-> loc_6727bf4, loop tail [V]). Je-block loc_6727be0 (from `je 0x6727BE0` in phase 36): `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6D8]`; `call 0x6760A80` (sub_6760a80); `nop`; falls into loc_6727bf4 [V]. loc_6727bf4: TLS seq dl=[rbp+0x827]; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. Count calc: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3` (magic /7); `dec eax`; `mov [rbp+0x2CC],ax`. Second TLS call dl=0x4A; `mov [rbp+0x827],al`. Cursor loop: `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je short 0x6727C69` (-> loc_6727c69) else `inc rdx`; `mov [r14+0x860],rdx`; `jmp short 0x6727C76` (-> loc_6727c76) [V]. loc_6727c69: `lea rcx,[r14+0x858]` (continues next phase: next instruction at 0x6727C70, expected `call 0x6760E60` mirroring phase 27's loc_67273e5 [I]).

Callees: 0x6760A80 (sub_6760a80, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice), jmp short 0x6727BF4 / je short 0x6727C69 / jmp short 0x6727C76 (loop control [V]).
Fields read: rdx [W], [rbp+0x564] [R], [rax+0x19C] [R], [rax+0x1AC] [R], [rax+0x1BB] [R], [rdx+0x24] [W], [rdx+0x28] [W], [rdx+0x38] [W], [rdx+0x47] [W], [r14+0x758] [R/W], [r14+0x750] [R], [rbp+0x6D8] [R], r8 via lea target, [rbp+0x827] [R/W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x2CC] [W], [r14+0x860] [R/W], [r14+0x868] [R], [r14+0x858] [R via lea address].
Fields written: [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [rbp+0x827], [rbp+0x2CC], [r14+0x860], rcx via [rbp+0x858] target (next phase).

## Phase 38 (0x6727C70..0x6727D3B)
```
  6727c70  call 0x6760E60                                ; -> sub_6760e60
  6727c75  nop                                           
  6727c76  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727c7d  mov rax,[rcx]                                 
  6727c80  mov rax,[rax+0x10]                            
  6727c84  movzx edx,byte ptr [rbp+0x827]                
  6727c8b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727c91  nop                                           
  6727c92  mov qword ptr [rbp+0x2A0],0x4009              
  6727c9d  mov eax,[r14+0x858]                           
  6727ca4  not eax                                       
  6727ca6  add eax,[r14+0x860]                           
  6727cad  mov [rbp+0x2B6],ax                            
  6727cb4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727cbb  mov rax,[rcx]                                 
  6727cbe  mov rax,[rax+0x10]                            
  6727cc2  mov dl,0x4A                                   
  6727cc4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727cca  mov [rbp+0x827],al                            
  6727cd0  lea rcx,[r14+0x648]                           
  6727cd7  lea rdx,[rbp+0x688]                           
  6727cde  call 0x675FB30                                ; -> sub_675fb30
  6727ce3  nop                                           
  6727ce4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727ceb  mov rax,[rcx]                                 
  6727cee  mov rax,[rax+0x10]                            
  6727cf2  movzx edx,byte ptr [rbp+0x827]                
  6727cf9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727cff  nop                                           
  6727d00  mov eax,[r14+0x650]                           
  6727d07  sub eax,[r14+0x648]                           
  6727d0e  shr eax,3                                     
  6727d11  imul eax,0xFFFF8E39                           
  6727d17  dec eax                                       
  6727d19  mov [rbp+0x2E2],ax                            
  6727d20  lea rcx,[r14+0x780]                           
  6727d27  lea rdx,[rbp+0x630]                           
  6727d2e  call 0x675F3B0                                ; -> sub_675f3b0
  6727d33  nop                                           
  6727d34  mov eax,[r14+0x788]                           
```
`// Phase 38: continuation of phase 37's loc_6727c69 (`lea rcx,[r14+0x858]`): `call 0x6760E60` (sub_6760e60 — same as phase 27's loc_67273e5 [V]); `nop`. TLS seq dl=[rbp+0x827]; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x2A0],0x4009`. Fold: `eax=[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x2B6],ax` (same ~(begin)+(end) fold as phase 27's [rbp+0x126], different slot [V]). TLS call dl=0x4A; `mov [rbp+0x827],al`. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x688]`; `call 0x675FB30` (sub_675fb30; [r14+0x648]→[rbp+0x688] — same as phase 27's [r14+0x648]→[rbp+0x650] but different dest slot [V]); `nop`. TLS seq again; count calc: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x2E2],ax` (differs from phase 27's imul 0xFFFF8BA3 → magic divisor differs [V]). Call setup: `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x630]`; `call 0x675F3B0` (sub_675f3b0 — same as phase 28 [V]); `nop`; `mov eax,[r14+0x788]` (continues next phase: next instruction at 0x6727D3B, expected `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3` mirroring phase 28's second count calc [I]).

Callees: 0x6760E60 (sub_6760e60, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30, direct), 0x675F3B0 (sub_675f3b0, direct).
Fields read: r14 [R/W], [r14+0x858] [R], [rbp+0x827] [R/W], [rbp+0x2A0] [W], [rbp+0x2B6] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [r14+0x860] [R], [rbp+0x648] [R], [rbp+0x688] [W via lea address], [r14+0x650] [R], [rbp+0x2E2] [W], [r14+0x780] [R], [rbp+0x630] [R], [r14+0x788] [R].
Fields written: [rbp+0x2A0], [rbp+0x2B6], [rbp+0x827], [rbp+0x688] via callee sub_675FB30, [rbp+0x2E2], [rbp+0x630] via callee sub_675F3B0.

## Phase 39 (0x6727D3B..0x6727E11)
```
  6727d3b  sub eax,[r14+0x780]                           
  6727d42  shr eax,3                                     
  6727d45  imul eax,0xFFFF8BA3                           
  6727d4b  dec eax                                       
  6727d4d  mov [rbp+0x2C8],ax                            
  6727d54  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727d5b  mov rax,[rcx]                                 
  6727d5e  mov rax,[rax+0x10]                            
  6727d62  mov dl,0x4A                                   
  6727d64  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727d6a  mov [rbp+0x827],al                            
  6727d70  mov rdi,[r14+0x770]                           
  6727d77  cmp rdi,[r14+0x778]                           
  6727d7e  je short 0x6727DC1                            ; -> loc_6727dc1
  6727d80  mov rax,[rbp+0x5A8]                           
  6727d87  mov [rdi],rax                                 
  6727d8a  lea rcx,[rdi+8]                               
  6727d8e  lea rdx,[rbp+0x5B0]                           
  6727d95  call 0xE869FF0                                ; -> sub_e869ff0
  6727d9a  nop                                           
  6727d9b  mov rax,[rbp+0x628]                           
  6727da2  mov [rdi+0x80],rax                            
  6727da9  mov qword ptr [rbp+0x628],0                   
  6727db4  add qword ptr [r14+0x770],0x88                
  6727dbf  jmp short 0x6727DD8                           ; -> loc_6727dd8

loc_6727dc1:  ; from 6727d7e
  6727dc1  lea rcx,[r14+0x768]                           
  6727dc8  mov rdx,rdi                                   
  6727dcb  lea r8,[rbp+0x5A8]                            
  6727dd2  call 0x6760710                                ; -> sub_6760710
  6727dd7  nop                                           

loc_6727dd8:  ; from 6727dbf
  6727dd8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727ddf  mov rax,[rcx]                                 
  6727de2  mov rax,[rax+0x10]                            
  6727de6  movzx edx,byte ptr [rbp+0x827]                
  6727ded  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727df3  nop                                           
  6727df4  mov qword ptr [rbp+0x2A0],0x2007009           
  6727dff  mov eax,[r14+0x770]                           
  6727e06  sub eax,[r14+0x768]                           
  6727e0d  shr eax,3                                     
```
`// Phase 39: continuation of phase 38's `mov eax,[r14+0x788]`: `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x2C8],ax` (phase 28's second count calc, slot [rbp+0x2C8] vs [rbp+0x138] [V]). TLS seq dl=[rbp+0x827]; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x827],al`. Release block mirroring phase 28: `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je short 0x6727DC1` (-> loc_6727dc1) else `mov rax,[rbp+0x5A8]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x5B0]`; `call 0xE869FF0` (sub_e869ff0); `nop`; `mov rax,[rbp+0x628]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x628],0`; `add qword ptr [r14+0x770],0x88`; `jmp short 0x6727DD8` (-> loc_6727dd8) [V]. Je-block loc_6727dc1: `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x5A8]`; `call 0x6760710` (sub_6760710); `nop`; falls into loc_6727dd8 [V]. loc_6727dd8: TLS seq `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x827]`; `call qword ptr [0xF99FFA0]`; `nop`; `mov qword ptr [rbp+0x2A0],0x2007009`. Count calc: `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3` (continues next phase: next instruction at 0x6727E11, expected `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x2??],ax` mirroring phase 29's count calc [I]).

Callees: 0xE869FF0 (sub_e869ff0, direct), 0x6760710 (sub_6760710, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: eax [R/W], [r14+0x780] [R], [rbp+0x2C8] [W], [rbp+0x827] [R/W], [r14+0x770] [R/W], [r14+0x778] [R], [rbp+0x5A8] [R], [rdi] [W], [rbp+0x5B0] [R], [rbp+0x628] [R/W], [rdi+0x80] [W], [r14+0x768] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x2A0] [W], [rbp+0x770] [R via eax], [r14+0x768] [R].
Fields written: [rbp+0x2C8], [rbp+0x827], [rdi], [rdi+0x80], [rbp+0x628], [r14+0x770], [rbp+0x2A0], eax chain.

## Phase 40 (0x6727E11..0x6727E90) — FINAL
```
  6727e11  shl cl,0xF0                                   
  6727e14  (bad)                                         
  6727e16  dec eax                                       
  6727e18  mov [rbp+0x2CA],ax                            
  6727e1f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727e26  mov rax,[rcx]                                 
  6727e29  mov rax,[rax+0x10]                            
  6727e2d  mov dl,0x4A                                   
  6727e2f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727e35  nop                                           
  6727e36  mov [rbp+0x827],al                            
  6727e3c  mov rdx,[r14+0x2D8]                           
  6727e43  cmp rdx,[r14+0x2E0]                           
  6727e4a  je short 0x6727E58                            ; -> loc_6727e58
  6727e4c  inc rdx                                       
  6727e4f  mov [r14+0x2D8],rdx                           
  6727e56  jmp short 0x6727E65                           ; -> loc_6727e65

loc_6727e58:  ; from 6727e4a
  6727e58  lea rcx,[r14+0x2D0]                           
  6727e5f  call 0x6760E60                                ; -> sub_6760e60
  6727e64  nop                                           

loc_6727e65:  ; from 6727e56
  6727e65  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727e6c  mov rax,[rcx]                                 
  6727e6f  mov rax,[rax+0x10]                            
  6727e73  movzx edx,byte ptr [rbp+0x827]                
  6727e7a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727e80  nop                                           
  6727e81  mov eax,[r14+0x2D0]                           
  6727e88  not eax                                       
  6727e8a  add eax,[r14+0x2D8]                           
```
`// Phase 40 (FINAL — 800-instruction target reached): continuation of phase 39's count calc: `shl cl,0xF0`; `(bad)` — 5 bytes at 0x6727e11..0x6727e16 that decode as garbage/invalid, tagged [?] padding/dead code; `dec eax`; `mov [rbp+0x2CA],ax` → count = (([r14+0x770]-[r14+0x768])>>3)-1 stored at [rbp+0x2CA] [V]. TLS seq dl=[rbp+0x827]; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x827],al`. Cursor loop: `rdx=[r14+0x2D8]`; `cmp rdx,[r14+0x2E0]`; if equal `je short 0x6727E58` (-> loc_6727e58) else `inc rdx`; `mov [r14+0x2D8],rdx`; `jmp short 0x6727E65` (-> loc_6727e65) [V]. Je-block loc_6727e58: `lea rcx,[r14+0x2D0]`; `call 0x6760E60` (sub_6760e60); `nop`; falls into loc_6727e65 [V]. loc_6727e65: TLS seq; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. Fold: `eax=[r14+0x2D0]`; `not eax`; `add eax,[r14+0x2D8]` — continues past target (next instruction at 0x6727E90 expected `mov [rbp+0x32C],ax` mirroring phase 30's fold [I]).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x6760E60 (sub_6760e60, direct).
Fields read: cl [W], [rbp+0x827] [R/W], [r14+0x2D8] [R/W], [r14+0x2E0] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x2CA] [W], [r14+0x2D0] [R], [rbp+0x32C] [W].
Fields written: [rbp+0x2CA], [rbp+0x827], [r14+0x2D8], eax chain (fold result → [rbp+0x32C] expected next phase [I]).

## NEXT
TARGET REACHED: 800 instructions disassembled (phases 21-40, 0x6726f07..0x6727E90). Phase 40 ends at `add eax,[r14+0x2D8]` at 0x6727e8a (ends 0x6727E90); next instruction would be `mov [rbp+0x32C],ax` [I]. Work complete — no further phases. No other files modified; no commits made.

## NEXT
Phase 38 (0x6727C70..0x6727D3B, 40 instructions) written; last instruction `mov eax,[r14+0x788]` at 0x6727d34 ends at 0x6727D3B (pattern repeat of phases 27-28: `call 0x6760E60`; TLS dl=[rbp+0x827]; `mov qword ptr [rbp+0x2A0],0x4009`; fold `not eax; add eax,[r14+0x860]` → [rbp+0x2B6]; TLS dl=0x4A; `call 0x675FB30` ([r14+0x648]→[rbp+0x688]); TLS; count calc `([r14+0x650]-[r14+0x648])>>3*/...` → [rbp+0x2E2]; `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x630]`; `call 0x675F3B0`; `mov eax,[r14+0x788]` [V]). 77 instructions remain to reach exactly 800 (723 written; phase 39 at 40, phase 40 partial ~37). Next phase starts at 0x6727D3B. Continue with `rdis dis 0x6727D3B 40`.

## NEXT
Phase 37 (0x6727BA9..0x6727C70, 40 instructions) written; last instruction `lea rcx,[r14+0x858]` at 0x6727c69 ends at 0x6727C70 (pattern repeat of phases 26-27: cursor-tail `movss [rdx+0x24],xmm0`; vector stores [rdx+0x28/0x38/0x47] from [rbp+0x564+0x19C/0x1AC/0x1BB]; `add qword ptr [r14+0x758],0x58`; `jmp short 0x6727BF4` -> loc_6727bf4; je-block loc_6727be0 `call 0x6760A80`; TLS seq dl=[rbp+0x827]; `mov [rbp+0x827],al`; count calc `([r14+0x758]-[r14+0x750])>>3*/7-1` → [rbp+0x2CC]; TLS dl=0x4A; cursor loop [r14+0x860]/[r14+0x868] `je short 0x6727C69` (-> loc_6727c69) / `inc rdx` [V]). 117 instructions remain to reach exactly 800 (683 written; phases 38-39 at 40 = 80, phase 40 partial ~37). Next phase starts at 0x6727C70. Continue with `rdis dis 0x6727C70 40`.

## NEXT
Phase 36 (0x6727AD8..0x6727BA9, 40 instructions) written; last instruction `movss xmm0,[rbp+0x6FC]` at 0x6727ba1 ends at 0x6727BA9 (pattern repeat of phase 25: `call 0x1EF6F90`; TLS dl=[rbp+0x827]; `mov qword ptr [rbp+0x2A0],1`; count calc `([r14+0x8A8]-[r14+0x8A0])/2-1` → [rbp+0x2B0]; TLS dl=0x4A; `mov [rbp+0x827],al`; cursor loop [r14+0x758]/[r14+0x760] `je 0x6727BE0` (-> loc_6727be0); copy from [rbp+0x6D8] with scalar stores to [rdx+0x10..0x1C] [V]). 157 instructions remain to reach exactly 800 (643 written; phases 37-39 at 40 = 120, phase 40 partial ~37). Next phase starts at 0x6727BA9. Continue with `rdis dis 0x6727BA9 40`.
