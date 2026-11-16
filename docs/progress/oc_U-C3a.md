# UNIT U-C3a — RenderDragon task scheduler 0xc25b1a0 call map (BGFX_MAP 6ac, 6ad)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Raw artifacts: docs/progress/oc_U-C3a_listing_utf8.txt, oc_U-C3a_callees.txt, oc_U-C3a_callers_rdis.txt, oc_U-C3a_descscan2_rsi.txt, oc_U-C3a_struct.txt.

## NEXT
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-C3a.md` to validate every quoted `0xRVA  instr` line; then finalize unit.

## (1) `rdis fn 0xc25b1a0` size; register map at entry

`rdis fn 0xc25b1a0` → `sub_c25b1a0 [0xc25b1a0..0xc25bb00) size 0x960`, 1 xref in. `rdis struct` returns an empty/derived field list (trust=derived only). [V rdis]

Entry register map (x64 Microsoft fastcall, arg0=rcx, arg1=rdx, arg2=r8, arg3=r9):
- rcx = arg0 = `a0` → scheduler object pointer (`this`), copied to rsi at c25b1d3. [V]
- rdx = arg1 = `a1` → stored at `a0+0x10` (c25b1e9), copied to r13 at c25b1d0. [V]
- r8  = arg2 = `a2` → `[r8]`→rax (c25b1ed), `[r8+8]`→r15 (vtable ptr 0xF0E4640, c25b1f0), copied to rdi at c25b1cd. [V]
- r9  = arg3 = `a3` → copied to r14 at c25b1ca, used as fill data at `[rsi+0x30]` (c25b2a9). [V]

Entry prologue (quoted verbatim):
```
c25b1a0  push rbp                                      
c25b1a1  push r15                                      
c25b1a3  push r14                                      
c25b1a5  push r13                                      
c25b1a7  push r12                                      
c25b1a9  push rsi                                      
c25b1aa  push rdi                                      
c25b1ab  push rbx                                      
c25b1ac  sub rsp,0x118                                 
c25b1b3  lea rbp,[rsp+0x80]                            
c25b1bb  movaps [rbp+0x80],xmm6                        
c25b1c2  mov qword ptr [rbp+0x78],0xFFFFFFFFFFFFFFFE    ; stack cookie = -1
c25b1ca  mov r14,r9                                     ; r14 = a3
c25b1cd  mov rdi,r8                                     ; rdi = a2
c25b1d0  mov r13,rdx                                    ; r13 = a1
c25b1d3  mov rsi,rcx                                    ; rsi = a0 = scheduler obj
c25b1d6  mov dword ptr [rcx],0                          ; W a0+0x0 = 0
c25b1dc  mov word ptr [rcx+4],0                         ; W a0+0x4 = 0
c25b1e2  mov dword ptr [rcx+8],0                        ; W a0+0x8 = 0
c25b1e9  mov [rcx+0x10],rdx                             ; W a0+0x10 = rdx (a1)
c25b1ed  mov rax,[r8]                                   ; R a2+0x0 -> rax
c25b1f0  mov r15,[r8+8]                                 ; R a2+0x8 -> r15 (vtable ptr 0xF0E4640)
c25b1f4  xorps xmm0,xmm0                               
c25b1f7  movups [rcx+0x18],xmm0                         ; W a0+0x18 = 0
c25b1fb  mov qword ptr [rcx+0x28],0                     ; W a0+0x28 = 0
```
Stack cookie global `[0x1233E1A8]`. Import thunk `[0xF99FFA0]` = `sub_eea6040` (heap allocator entry). [V]

## (2) Phases (<=40 instructions each, every instruction covered, quoted `0xRVA  instr`)

Phase A — prologue + scheduler init + read a2 (c25b1a0..c25b1fb): 23 instrs [V]
Meaning: save callee regs, frame/cookie, zero a0+0x0/+0x4/+0x8, store a1 at a0+0x10, read `[a2]`/`[a2+8]` (vtable 0xF0E4640), zero a0+0x18 (16B) and a0+0x28.
```
c25b1a0  push rbp                                      
c25b1a1  push r15                                      
c25b1a3  push r14                                      
c25b1a5  push r13                                      
c25b1a7  push r12                                      
c25b1a9  push rsi                                      
c25b1aa  push rdi                                      
c25b1ab  push rbx                                      
c25b1ac  sub rsp,0x118                                 
c25b1b3  lea rbp,[rsp+0x80]                            
c25b1bb  movaps [rbp+0x80],xmm6                        
c25b1c2  mov qword ptr [rbp+0x78],0xFFFFFFFFFFFFFFFE   
c25b1ca  mov r14,r9                                    
c25b1cd  mov rdi,r8                                    
c25b1d0  mov r13,rdx                                   
c25b1d3  mov rsi,rcx                                   
c25b1d6  mov dword ptr [rcx],0                         
c25b1dc  mov word ptr [rcx+4],0                        
c25b1e2  mov dword ptr [rcx+8],0                       
c25b1e9  mov [rcx+0x10],rdx                            
c25b1ed  mov rax,[r8]                                  
c25b1f0  mov r15,[r8+8]                                
c25b1f4  xorps xmm0,xmm0                               
c25b1f7  movups [rcx+0x18],xmm0                        
c25b1fb  mov qword ptr [rcx+0x28],0                    
```

Phase B — heap alloc for a0+0x18 block via import thunk + memcpy (c25b203..c25b29d): ~40 instrs [V]
Meaning: test rax (=[a2]); size = rax*8; if >0x200 call `[0xF99FFA0]((size+0x27)&~0x20)`→rbx else `[0xF99FFA0](size)`→rcx; store begin/end/cap (cap=[rcx-8]=rbx), end=begin+size; memcpy dst=a0+0x18 size=r12 via sub_eec6de0; store end back at a0+0x20.
```
c25b203  test rax,rax                                  
c25b206  je 0xC25B2A1                                  
c25b20c  mov rcx,rax                                   
c25b20f  shr rcx,0x3D                                  
c25b213  jne 0xC25BAFA                                 
c25b219  lea r12,[rax*8]                               
c25b221  cmp rax,0x200                                 
c25b227  jb short 0xC25B25F                            
c25b229  lea rdx,[r12+0x27]                            
c25b22e  mov rcx,[0x1233E1A8]                          
c25b235  mov rax,[rcx]                                 
c25b238  mov rax,[rax+8]                               
c25b23c  call qword ptr [0xF99FFA0]                    
c25b242  mov rbx,rax                                   
c25b245  test rax,rax                                  
c25b248  je 0xC25BAC3                                  
c25b24e  mov rcx,rbx                                   
c25b251  add rcx,0x27                                  
c25b255  and rcx,0xFFFFFFFFFFFFFFE0                    
c25b259  mov [rcx-8],rbx                               
c25b25d  jmp short 0xC25B282                           
c25b25f  mov rcx,[0x1233E1A8]                          
c25b266  mov rax,[rcx]                                 
c25b269  mov rax,[rax+8]                               
c25b26d  mov rdx,r12                                   
c25b270  call qword ptr [0xF99FFA0]                    
c25b276  mov rcx,rax                                   
c25b279  test rax,rax                                  
c25b27c  je 0xC25BAD2                                  
c25b282  mov [rsi+0x18],rcx                            
c25b286  mov [rsi+0x20],rcx                            
c25b28a  lea rbx,[rcx+r12]                             
c25b28e  mov [rsi+0x28],rbx                            
c25b292  mov rdx,r15                                   
c25b295  mov r8,r12                                    
c25b298  call 0xEEC6DE0                                
c25b29d  mov [rsi+0x20],rbx                            
```

Phase C — alloc 5 identical sub-buffers at a0+0x38..0x80 (c25b2a1..c25b4c2): split into C1..C5 each <=40 instrs [V]
Meaning: per slot (a0+0x38/0x48/0x58/0x68/0x78): `[0xF99FFA0](0x278)`→r14; `[r14+8]=0x100000001`; `[r14]=r15` (vtable 0xF0E4640); memzero 0x268 at r14 via sub_eec6ed0; sub_1d2c10(r14,0x400) profiler; link r14 into `a0+slot` and back-ref r14 at `a0+slot+0x10`. Then zero a0+0x88..0x98 (movups), load trace scope obj r15=rsi+0xA8.

C1 (c25b2a1..c25b326):
```
c25b2a1  lea rax,[rsi+0x18]                            
c25b2a5  mov [rbp-0x48],rax                            
c25b2a9  mov [rsi+0x30],r14                            
c25b2ad  mov rcx,[0x1233E1A8]                          
c25b2b4  mov rax,[rcx]                                 
c25b2b7  mov rax,[rax+8]                               
c25b2bb  mov edx,0x278                                 
c25b2c0  call qword ptr [0xF99FFA0]                    
c25b2c6  nop                                           
c25b2c7  mov r14,rax                                   
c25b2ca  test rax,rax                                  
c25b2cd  je 0xC25BA33                                  
c25b2d3  mov rbx,0x100000001                           
c25b2dd  mov [r14+8],rbx                               
c25b2e1  lea r15,[0xF0E4640]                           
c25b2e8  mov [r14],r15                                 
c25b2eb  mov [rbp+0x70],r14                            
c25b2ef  add r14,0x10                                  
c25b2f3  mov r8d,0x268                                 
c25b2f9  mov rcx,r14                                   
c25b2fc  xor edx,edx                                   
c25b2fe  call 0xEEC6ED0                                
c25b303  nop                                           
c25b304  mov edx,0x400                                 
c25b309  mov rcx,r14                                   
c25b30c  call 0x1D2C10                                 
c25b311  nop                                           
c25b312  lea rax,[rsi+0x38]                            
c25b316  mov [rbp-0x40],rax                            
c25b31a  mov [rsi+0x38],r14                            
c25b31e  mov rax,[rbp+0x70]                            
c25b322  mov [rsi+0x40],rax                            
```

C2 (c25b326..c25b38e):
```
c25b326  mov rcx,[0x1233E1A8]                          
c25b32d  mov rax,[rcx]                                 
c25b330  mov rax,[rax+8]                               
c25b334  mov edx,0x278                                 
c25b339  call qword ptr [0xF99FFA0]                    
c25b33f  nop                                           
c25b340  mov r14,rax                                   
c25b343  test rax,rax                                  
c25b346  je 0xC25BA43                                  
c25b34c  mov [r14+8],rbx                               
c25b350  mov [r14],r15                                 
c25b353  mov [rbp+0x70],r14                            
c25b357  add r14,0x10                                  
c25b35b  mov r8d,0x268                                 
c25b361  mov rcx,r14                                   
c25b364  xor edx,edx                                   
c25b366  call 0xEEC6ED0                                
c25b36b  nop                                           
c25b36c  mov edx,0x400                                 
c25b371  mov rcx,r14                                   
c25b374  call 0x1D2C10                                 
c25b379  nop                                           
c25b37a  lea rax,[rsi+0x48]                            
c25b37e  mov [rbp-0x38],rax                            
c25b382  mov [rsi+0x48],r14                            
c25b386  mov rax,[rbp+0x70]                            
c25b38a  mov [rsi+0x50],rax                            
```

C3 (c25b38e..c25b41c):
```
c25b38e  mov rcx,[0x1233E1A8]                          
c25b395  mov rax,[rcx]                                 
c25b398  mov rax,[rax+8]                               
c25b39c  mov edx,0x278                                 
c25b3a1  call qword ptr [0xF99FFA0]                    
c25b3a7  nop                                           
c25b3a8  mov r14,rax                                   
c25b3ab  test rax,rax                                  
c25b3ae  je 0xC25BA53                                  
c25b3b4  mov [r14+8],rbx                               
c25b3b8  mov [r14],r15                                 
c25b3bb  mov [rbp+0x70],r14                            
c25b3bf  add r14,0x10                                  
c25b3c3  mov r8d,0x268                                 
c25b3c9  mov rcx,r14                                   
c25b3cc  xor edx,edx                                   
c25b3ce  call 0xEEC6ED0                                
c25b3d3  nop                                           
c25b3d4  mov edx,0x400                                 
c25b3d9  mov rcx,r14                                   
c25b3dc  call 0x1D2C10                                 
c25b3e1  nop                                           
c25b3e2  lea rax,[rsi+0x58]                            
c25b3e6  mov [rbp-0x30],rax                            
c25b3ea  mov [rsi+0x58],r14                            
c25b3ee  mov rax,[rbp+0x70]                            
c25b3f2  mov [rsi+0x60],rax                            
```

C4 (c25b3f6..c25b45e):
```
c25b3f6  mov rcx,[0x1233E1A8]                          
c25b3fd  mov rax,[rcx]                                 
c25b400  mov rax,[rax+8]                               
c25b404  mov edx,0x278                                 
c25b409  call qword ptr [0xF99FFA0]                    
c25b40f  nop                                           
c25b410  mov r14,rax                                   
c25b413  test rax,rax                                  
c25b416  je 0xC25BA63                                  
c25b41c  mov [r14+8],rbx                               
c25b420  mov [r14],r15                                 
c25b423  mov [rbp+0x70],r14                            
c25b427  add r14,0x10                                  
c25b42b  mov r8d,0x268                                 
c25b431  mov rcx,r14                                   
c25b434  xor edx,edx                                   
c25b436  call 0xEEC6ED0                                
c25b43b  nop                                           
c25b43c  mov edx,0x400                                 
c25b441  mov rcx,r14                                   
c25b444  call 0x1D2C10                                 
c25b449  nop                                           
c25b44a  lea rax,[rsi+0x68]                            
c25b44e  mov [rbp-0x28],rax                            
c25b452  mov [rsi+0x68],r14                            
c25b456  mov rax,[rbp+0x70]                            
c25b45a  mov [rsi+0x70],rax                            
```

C5 (c25b45e..c25b4f0):
```
c25b45e  mov rcx,[0x1233E1A8]                          
c25b465  mov rax,[rcx]                                 
c25b468  mov rax,[rax+8]                               
c25b46c  mov edx,0x278                                 
c25b471  call qword ptr [0xF99FFA0]                    
c25b477  nop                                           
c25b478  mov r14,rax                                   
c25b47b  test rax,rax                                  
c25b47e  je 0xC25BA73                                  
c25b484  mov [r14+8],rbx                               
c25b488  mov [r14],r15                                 
c25b48b  mov [rbp+0x70],r14                            
c25b48f  add r14,0x10                                  
c25b493  mov r8d,0x268                                 
c25b499  mov rcx,r14                                   
c25b49c  xor edx,edx                                   
c25b49e  call 0xEEC6ED0                                
c25b4a3  nop                                           
c25b4a4  mov edx,0x400                                 
c25b4a9  mov rcx,r14                                   
c25b4ac  call 0x1D2C10                                 
c25b4b1  nop                                           
c25b4b2  lea rax,[rsi+0x78]                            
c25b4b6  mov [rbp-0x20],rax                            
c25b4ba  mov [rsi+0x78],r14                            
c25b4be  mov rax,[rbp+0x70]                            
c25b4c2  mov [rsi+0x80],rax                            
c25b4c9  lea rax,[rsi+0x88]                            
c25b4d0  mov [rbp-0x18],rax                            
c25b4d4  lea rax,[rsi+0x98]                            
c25b4db  mov [rbp-0x10],rax                            
c25b4df  lea r15,[rsi+0xA8]                            
c25b4e6  xorps xmm6,xmm6                               
c25b4e9  movups [rsi+0x88],xmm6                        
c25b4f0  movups [rsi+0x98],xmm6                        
```

Phase D — trace scope "GraphicsTasks Scheduler" (c25b4f7..c25b54b): 12 instrs [V]
Meaning: load string 0xF56AF2B, len 0x17 at [rbp-0x50], call sub_7709c0(r15=&scope at a0+0xA8, rdx=&desc, r8w=0x3C) to open trace/profiler scope.
```
c25b4f7  lea rax,[0xF56AF2B]                            
c25b4fe  mov [rbp-0x58],rax                            
c25b502  mov qword ptr [rbp-0x50],0x17                 
c25b50a  lea rdx,[rbp-0x58]                            
c25b50e  mov rcx,r15                                   
c25b511  mov r8w,0x3C                                  
c25b516  call 0x7709C0                                 
c25b51b  nop                                           
c25b51c  movaps [rbp+0x10],xmm6                        
c25b520  mov qword ptr [rbp+0x20],0                    
c25b528  mov r14,[rdi]                                 
c25b52b  mov rbx,[rdi+8]                               
c25b52f  movaps [rbp+0x30],xmm6                        
c25b533  mov qword ptr [rbp+0x40],0                    
c25b53b  mov [rbp+0x50],r13                            
c25b53f  mov [rbp-8],r15                               
c25b543  mov [rbp+0x58],r15                            
c25b547  mov byte ptr [rbp+0x60],0                     
```

Phase E — copy first list [rdi,rdi+8) → a0+0x30.. via sub_7cd250 (c25b54b..c25b5cf): ~40 instrs [V]
Meaning: r14=[rdi] (begin), rbx=[rdi+8] (end); sub_7cd250(&[rbp+0x30],&[rbp+0x50],edx=0) copy/append; loop while rbx!=r12(=rbx+r14*8): store [rbp+0x60] at [rdx+0x10], movups copy 16B [rbp+0x50]→[rdx], advance [rbp+0x38]+=0x18, rbx+=8; call sub_7cd250 again, rbx+=8.
```
c25b54b  lea rcx,[rbp+0x30]                            
c25b54f  lea r8,[rbp+0x50]                             
c25b553  xor edx,edx                                   
c25b555  call 0x7CD250                                 
c25b55a  nop                                           
c25b55b  lea rax,[rsi+0x118]                           
c25b562  mov [rbp],rax                                 
c25b566  lea r12,[rbx+r14*8]                           
c25b56a  lea r14,[rbp+0x30]                            
c25b56e  lea r15,[rbp+0x50]                            
c25b572  jmp short 0xC25B598                           
c25b574  nop [rax+rax]                                 
c25b580  mov rax,[rbp+0x60]                            
c25b584  mov [rdx+0x10],rax                            
c25b588  movups xmm0,[rbp+0x50]                        
c25b58c  movups [rdx],xmm0                             
c25b58f  add qword ptr [rbp+0x38],0x18                 
c25b594  add rbx,8                                     
c25b598  cmp rbx,r12                                   
c25b59b  lea rcx,[rsi+0xA8]                            
c25b5a2  je short 0xC25B5CF                            
c25b5a4  mov rax,[rbx]                                 
c25b5a7  mov [rbp+0x50],rax                            
c25b5ab  mov [rbp+0x58],rcx                            
c25b5af  mov byte ptr [rbp+0x60],1                     
c25b5b3  mov rdx,[rbp+0x38]                            
c25b5b7  cmp rdx,[rbp+0x40]                            
c25b5bb  jne short 0xC25B580                           
c25b5bd  mov rcx,r14                                   
c25b5c0  mov r8,r15                                    
c25b5c3  call 0x7CD250                                 
c25b5c8  nop                                           
c25b5c9  add rbx,8                                     
c25b5cd  jmp short 0xC25B598                           
```

Phase F — alloc two 0x20 blocks, fill "GraphicsTasks Group", self-link, sub_c264090 push → a0+0x118, frees (c25b5cf..c25b6c4): ~40 instrs [V]
Meaning: `[0xF99FFA0](0x20)`→rbx; `[0xF99FFA0](0x20)`→r14; [rbp+0x60]=0x13, [rbp+0x68]=0x1F; movups "GraphicsTasks Group" 0xF573001→[r14]; dword [r14+0xF]=0x70756F72 ("rou"); byte [r14+0x13]=0; rbx=[rbp+0x70]; self-link [rbx+8]=rbx; sub_c264090(rcx=&[rbp+0x10], rdx=rbx, r8=&[rbp+0x50], r9=&[rbp+0x30]); [rsi+0x118]=rbx; cap check → sub_e935700 if cap>=0x10 && remaining<0x20; dword [rsi+0x120]=0.
```
c25b5cf  mov rcx,[0x1233E1A8]                          
c25b5d6  mov rax,[rcx]                                 
c25b5d9  mov rax,[rax+8]                               
c25b5dd  mov edx,0x20                                  
c25b5e2  call qword ptr [0xF99FFA0]                    
c25b5e8  nop                                           
c25b5e9  mov rbx,rax                                   
c25b5ec  test rax,rax                                  
c25b5ef  je 0xC25BA83                                  
c25b5f5  mov [rbp+0x70],rbx                            
c25b5f9  xorps xmm0,xmm0                               
c25b5fc  movaps [rbp+0x50],xmm0                        
c25b600  mov rcx,[0x1233E1A8]                          
c25b607  mov rax,[rcx]                                 
c25b60a  mov rax,[rax+8]                               
c25b60e  mov edx,0x20                                  
c25b613  call qword ptr [0xF99FFA0]                    
c25b619  nop                                           
c25b61a  mov r14,rax                                   
c25b61d  test rax,rax                                  
c25b620  je 0xC25BA93                                  
c25b626  mov [rbp+0x50],r14                            
c25b62a  mov qword ptr [rbp+0x60],0x13                 
c25b632  mov qword ptr [rbp+0x68],0x1F                 
c25b63a  movups xmm0,[0xF573001]                       
c25b641  movups [r14],xmm0                             
c25b645  mov dword ptr [r14+0xF],0x70756F72            
c25b64d  mov byte ptr [r14+0x13],0                     
c25b652  mov rbx,[rbp+0x70]                            
c25b656  mov [rbx+8],rbx                               
c25b65a  mov rcx,rbx                                   
c25b65d  add rcx,0x10                                  
c25b661  lea r15,[rbp+0x10]                            
c25b665  mov [rsp+0x20],r15                            
c25b66a  lea r8,[rbp+0x50]                             
c25b66e  lea r9,[rbp+0x30]                             
c25b672  mov rdx,rbx                                   
c25b675  call 0xC264090                                
c25b67a  nop                                           
c25b67b  lea rax,[rsi+0x118]                           
c25b682  mov [rax],rbx                                 
c25b685  mov rax,[rbp+0x68]                            
c25b689  cmp rax,0x10                                  
c25b68d  jb short 0xC25B6C4                            
c25b68f  mov rcx,[rbp+0x50]                            
c25b693  lea rdx,[rax+1]                               
c25b697  cmp rdx,0x1000                                
c25b69e  jb short 0xC25B6BF                            
c25b6a0  mov r8,[rcx-8]                                
c25b6a4  add rcx,0xFFFFFFFFFFFFFFF8                    
c25b6a8  sub rcx,r8                                    
c25b6ab  cmp rcx,0x20                                  
c25b6af  jae 0xC25BAE1                                 
c25b6b5  add rax,0x28                                  
c25b6b9  mov rdx,rax                                   
c25b6bc  mov rcx,r8                                    
c25b6bf  call 0xE935700                                
c25b6c4  mov dword ptr [rsi+0x120],0                   
```

Phase G — copy second list [rdi,rdi+8) → a0+0x30.. via sub_7cd250, alloc two 0x20 blocks, fill "GraphicsTasks Parallel Group", sub_c264090 push → a0+0x128, frees (c25b708..c25b8b2): ~40 instrs [V]
Meaning: same list-copy as Phase E; then alloc two 0x20 blocks; movups "s Parallel Group" 0xF57337D→[rbx+0xC] and "GraphicsTasks Parallel Group" 0xF573371→[rbx]; byte [rbx+0x1C]=0; self-link [rbx+8]=rbx; sub_c264090; [rsi+0x128]=rbx; dword [rsi+0x130]=0.
```
c25b708  mov rbx,[rdi]                                 
c25b70b  mov r12,[rdi+8]                               
c25b70f  xorps xmm0,xmm0                               
c25b712  movaps [rbp+0x10],xmm0                        
c25b716  mov qword ptr [rbp+0x20],0                    
c25b71e  movaps [rbp+0x30],xmm0                        
c25b722  mov qword ptr [rbp+0x40],0                    
c25b72a  mov [rbp+0x50],r13                            
c25b72e  lea rax,[rsi+0xA8]                            
c25b735  mov [rbp+0x58],rax                            
c25b739  mov byte ptr [rbp+0x60],0                     
c25b73d  lea rcx,[rbp+0x30]                            
c25b741  lea r8,[rbp+0x50]                             
c25b745  xor edx,edx                                   
c25b747  call 0x7CD250                                 
c25b74c  nop                                           
c25b74d  lea rax,[rsi+0x128]                           
c25b754  mov [rbp+8],rax                               
c25b758  lea r13,[r12+rbx*8]                           
c25b75c  lea rbx,[rbp+0x30]                            
c25b760  lea r14,[rbp+0x50]                            
c25b764  jmp short 0xC25B788                           
c25b766  nop [rax+rax]                                 
c25b770  mov rax,[rbp+0x60]                            
c25b774  mov [rdx+0x10],rax                            
c25b778  movups xmm0,[rbp+0x50]                        
c25b77c  movups [rdx],xmm0                             
c25b77f  add qword ptr [rbp+0x38],0x18                 
c25b784  add r12,8                                     
c25b788  cmp r12,r13                                   
c25b78b  lea rcx,[rsi+0xA8]                            
c25b792  je short 0xC25B7C0                            
c25b794  mov rax,[r12]                                 
c25b798  mov [rbp+0x50],rax                            
c25b79c  mov [rbp+0x58],rcx                            
c25b7a0  mov byte ptr [rbp+0x60],1                     
c25b7a4  mov rdx,[rbp+0x38]                            
c25b7a8  cmp rdx,[rbp+0x40]                            
c25b7ac  jne short 0xC25B770                           
c25b7ae  mov rcx,rbx                                   
c25b7b1  mov r8,r14                                    
c25b7b4  call 0x7CD250                                 
c25b7b9  nop                                           
c25b7ba  add r12,8                                     
c25b7be  jmp short 0xC25B788                           
c25b7c0  mov rcx,[0x1233E1A8]                          
c25b7c7  mov rax,[rcx]                                 
c25b7ca  mov rax,[rax+8]                               
c25b7ce  mov edx,0x20                                  
c25b7d3  call qword ptr [0xF99FFA0]                    
c25b7d9  nop                                           
c25b7da  mov rbx,rax                                   
c25b7dd  test rax,rax                                  
c25b7e0  je 0xC25BAA3                                  
c25b7e6  mov [rbp+0x70],rbx                            
c25b7ea  xorps xmm0,xmm0                               
c25b7ed  movaps [rbp+0x50],xmm0                        
c25b7f1  mov rcx,[0x1233E1A8]                          
c25b7f8  mov rax,[rcx]                                 
c25b7fb  mov rax,[rax+8]                               
c25b7ff  mov edx,0x20                                  
c25b804  call qword ptr [0xF99FFA0]                    
c25b80a  nop                                           
c25b80b  mov rbx,rax                                   
c25b80e  test rax,rax                                  
c25b811  je 0xC25BAB3                                  
c25b817  mov [rbp+0x50],rbx                            
c25b81b  mov qword ptr [rbp+0x60],0x1C                 
c25b823  mov qword ptr [rbp+0x68],0x1F                 
c25b82b  movups xmm0,[0xF57337D]                       
c25b832  movups [rbx+0xC],xmm0                         
c25b836  movups xmm0,[0xF573371]                       
c25b83d  movups [rbx],xmm0                             
c25b840  mov byte ptr [rbx+0x1C],0                     
c25b844  mov rbx,[rbp+0x70]                            
c25b848  mov [rbx+8],rbx                               
c25b84c  mov rcx,rbx                                   
c25b84f  add rcx,0x10                                  
c25b853  mov [rsp+0x20],r15                            
c25b858  lea r8,[rbp+0x50]                             
c25b85c  lea r9,[rbp+0x30]                             
c25b860  mov rdx,rbx                                   
c25b863  call 0xC264090                                
c25b868  nop                                           
c25b869  lea rax,[rsi+0x128]                           
c25b870  mov [rax],rbx                                 
c25b873  mov rax,[rbp+0x68]                            
c25b877  cmp rax,0x10                                  
c25b87b  jb short 0xC25B8B2                            
c25b87d  mov rcx,[rbp+0x50]                            
c25b881  lea rdx,[rax+1]                               
c25b885  cmp rdx,0x1000                                
c25b88c  jb short 0xC25B8AD                            
c25b88e  mov r8,[rcx-8]                                
c25b892  add rcx,0xFFFFFFFFFFFFFFF8                    
c25b896  sub rcx,r8                                    
c25b899  cmp rcx,0x20                                  
c25b89d  jae 0xC25BAE1                                 
c25b8a3  add rax,0x28                                  
c25b8a7  mov rdx,rax                                   
c25b8aa  mov rcx,r8                                    
c25b8ad  call 0xE935700                                
c25b8b2  mov dword ptr [rsi+0x130],0                   
```

Phase H — queue-count accumulation + epilog (c25b8f6..c25ba32): ~40 instrs [V]
Meaning: rcx=[rsi+0x10]; zero [rsi+0x138]/[rsi+0x140]; movups [rsi+0x148]=0; sub_775d90(rdx=&[rbp+0x50])→rax perf value stored at [rsi]; rax=([rcx+0x28]-[rcx+0x20])>>3 added to [rsi+0x148]; if [rdi]!=0: rdi=[rdi], rax=([rdi+8+0x28]-[rdi+8+0x20])>>3 added to [rsi+0x148]; loop over rdi stride 8 adding same delta each time. Epilog: rax=rsi; restore xmm6/rsp/pops; ret.
```
c25b8f6  mov rcx,[rsi+0x10]                            
c25b8fa  lea rax,[rsi+0x138]                           
c25b901  mov [rbp+0x70],rax                            
c25b905  mov qword ptr [rsi+0x138],0                   
c25b910  mov dword ptr [rsi+0x140],0                   
c25b91a  xorps xmm0,xmm0                               
c25b91d  movups [rsi+0x148],xmm0                       
c25b924  lea rdx,[rbp+0x50]                            
c25b928  call 0x775D90                                 
c25b92d  nop                                           
c25b92e  mov rcx,[rbp+0x50]                            
c25b932  mov eax,[rcx]                                 
c25b934  mov [rsi],eax                                 
c25b936  mov rdx,[rsi+0x10]                            
c25b93a  mov rax,[rdx+0x28]                            
c25b93e  sub rax,[rdx+0x20]                            
c25b942  sar rax,3                                     
c25b946  add rax,[rsi+0x148]                           
c25b94d  mov [rsi+0x148],rax                           
c25b954  mov r9,[rdi]                                  
c25b957  test r9,r9                                    
c25b95a  je 0xC25B9E4                                  
c25b960  lea rdx,[rsi+0x148]                           
c25b967  mov r10,[rdi+8]                               
c25b96b  lea r11,[r9*8]                                
c25b973  add r11,0xFFFFFFFFFFFFFFF8                    
c25b977  test r11b,8                                   
c25b97b  jne short 0xC25B99D                           
c25b97d  mov r8,[r10]                                  
c25b980  mov rdi,[r8+0x28]                             
c25b984  sub rdi,[r8+0x20]                             
c25b988  sar rdi,3                                     
c25b98c  add rax,rdi                                   
c25b98f  mov [rdx],rax                                 
c25b992  lea r8,[r10+8]                                
c25b996  test r11,r11                                  
c25b999  jne short 0xC25B9A5                           
c25b99b  jmp short 0xC25B9E4                           
c25b99d  mov r8,r10                                    
c25b9a0  test r11,r11                                  
c25b9a3  je short 0xC25B9E4                           
c25b9a5  lea r9,[r10+r9*8]                             
c25b9a9  nop [rax]                                     
c25b9b0  mov r10,[r8]                                  
c25b9b3  mov r11,[r10+0x28]                            
c25b9b7  sub r11,[r10+0x20]                            
c25b9bb  sar r11,3                                     
c25b9bf  add r11,rax                                   
c25b9c2  mov [rdx],r11                                 
c25b9c5  mov r10,[r8+8]                                
c25b9c9  mov rax,[r10+0x28]                            
c25b9cd  sub rax,[r10+0x20]                            
c25b9d1  sar rax,3                                     
c25b9d5  add rax,r11                                   
c25b9d8  mov [rdx],rax                                 
c25b9db  add r8,0x10                                   
c25b9df  cmp r8,r9                                     
c25b9e2  jne short 0xC25B9B0                           
c25b9e4  mov rdx,[rbp+0x60]                            
c25b9e8  sub rdx,rcx                                   
c25b9eb  cmp rdx,0x1000                                
c25b9f2  jb short 0xC25BA10                            
c25b9f4  mov rax,[rcx-8]                               
c25b9f8  add rcx,0xFFFFFFFFFFFFFFF8                    
c25b9fc  sub rcx,rax                                   
c25b9ff  cmp rcx,0x20                                  
c25ba03  jae 0xC25BAE1                                 
c25ba09  add rdx,0x27                                  
c25ba0d  mov rcx,rax                                   
c25ba10  call 0xE935700                                
c25ba15  mov rax,rsi                                   
c25ba18  movaps xmm6,[rbp+0x80]                        
c25ba1f  add rsp,0x118                                 
c25ba26  pop rbx                                       
c25ba27  pop rdi                                       
c25ba28  pop rsi                                       
c25ba29  pop r12                                       
c25ba2b  pop r13                                       
c25ba2d  pop r14                                       
c25ba2f  pop r15                                       
c25ba31  pop rbp                                       
c25ba32  ret                                           
```

Cold paths (alloc failure → sub_9bc830 retry; final failure → call `[0xF9A8C78]` then sub_75b60; int3 at c25baff; next fn starts c25bb00):
```
c25ba33  mov ecx,0x278         call 0x9BC830   c25ba3d  nop          c25ba3e  jmp 0xC25B2D3
c25ba43  mov ecx,0x278         call 0x9BC830   c25ba4d  nop          c25ba4e  jmp 0xC25B34C
c25ba53  mov ecx,0x278         call 0x9BC830   c25ba5d  nop          c25ba5e  jmp 0xC25B3B4
c25ba63  mov ecx,0x278         call 0x9BC830   c25ba6d  nop          c25ba6e  jmp 0xC25B41C
c25ba73  mov ecx,0x278         call 0x9BC830   c25ba7d  nop          c25ba7e  jmp 0xC25B484
c25ba83  mov ecx,0x20          call 0x9BC830   c25ba8d  nop          c25ba8e  jmp 0xC25B5F5
c25ba93  mov ecx,0x20          call 0x9BC830   c25ba9d  nop          c25ba9e  jmp 0xC25B626
c25baa3  mov ecx,0x20          call 0x9BC830   c25baad  nop          c25baae  jmp 0xC25B7E6
c25bab3  mov ecx,0x20          call 0x9BC830   c25babd  nop          c25babe  jmp 0xC25B817
c25bac3  lea rcx,[r12+0x27]    call 0x9BC830   c25bacd  jmp 0xC25B24E
c25bad2  mov rcx,r12           call 0x9BC830   c25bada  xor ecx,ecx  c25badc  jmp 0xC25B282
c25bae1  mov qword ptr [rsp+0x20],0
c25baea  xor ecx,ecx           c25baec  xor edx,edx    c25baee  xor r8d,r8d    c25baf1  xor r9d,r9d
c25baf4  call qword ptr [0xF9A8C78]
c25bafa  call 0x75B60
c25baff  int3
```
Listing asserts function end at 0xc25bb00; c25bb00+ is the NEXT function's prologue (NOT part of 0xc25b1a0). [V listing]

## (3) Callees — every distinct callee in order of first call

`rdis callees 0xc25b1a0` + listing call sites. Counts = distinct call sites observed in the body (cold-path retry sites counted separately). None appear individually in docs/data/functions.tsv — identification from rdis output + disassembly + BGFX_MAP context. [V unless tagged]

| # | Callee RVA | Count | First site | Identification | Tag |
|---|------------|-------|------------|----------------|-----|
| 1 | `sub_eea6040` | 13 | `c25b23c` `call qword ptr [0xF99FFA0]` | Import thunk `[0xF99FFA0]` = jmp rax → heap allocator entry. Size 0x278 (5× sub-buffers), 0x20 (4× group blocks), aligned (size+0x27)&~0x1f for main block. | [V] |
| 2 | `sub_eec6de0` | 3 | `c25b298` `call 0xEEC6DE0` | memcpy/copy helper: `sub_eec6de0(rdx=r15=src, rcx=[rsi+0x18]=dst, r8=r12=size)`. | [V] |
| 3 | `sub_9bc830` | 11 | `c25ba38` `call 0x9BC830` | Allocator failure / small-vector push retry helper (BGFX_MAP 6cz/6n). Retries each alloc site. | [V] |
| 4 | `sub_1d2c10` | 5 | `c25b30c` `call 0x1D2C10` | Profiler/marker helper (BGFX_MAP L198). `sub_1d2c10(r14, 0x400)` after each sub-buffer init. | [V] |
| 5 | `sub_eec6ed0` | 5 | `c25b2fe` `call 0xEEC6ED0` | memzero/init helper: `sub_eec6ed0(rcx=r14+0x10, rdx=0, r8d=0x268)`. Zeroes 0x268 bytes per sub-buffer. | [V] |
| 6 | `sub_7709c0` | 1 | `c25b516` `call 0x7709C0` | Trace scope begin: `sub_7709c0(rcx=r15=&scope obj at a0+0xA8, rdx=&desc at [rbp-0x58], r8w=0x3C)`. String 0xF56AF2B. | [V] |
| 7 | `sub_7cd250` | 4 | `c25b555` `call 0x7CD250` | Vector append/grow helper: `sub_7cd250(rcx=&dst, r8=&src, edx=0)`. Twice per list-copy phase (E, G). BGFX_MAP 6ac cites `0x7cd250 x4`. | [V] |
| 8 | `sub_c264090` | 2 | `c25b675` `call 0xC264090` | Task queue push: `sub_c264090(rcx=&[rbp+0x10], rdx=rbx=node, r8=&[rbp+0x50], r9=&[rbp+0x30])`. inventory_L3_dragon.tsv L364: `0xc264090` caller of 0xc25b1a0 (D0). | [V] |
| 9 | `sub_e935700` | 5 | `c25b6bf` `call 0xE935700` | free helper; cap-grow/release path when `[cap]>=0x10 && remaining<0x20`. Frees 0x20 blocks. BGFX_MAP cites free x5. | [V] |
| 10 | `sub_775d90` | 1 | `c25b928` `call 0x775D90` | Perf counter reader: `sub_775d90(rdx=&[rbp+0x50])`→rax stored at [rsi]. | [V] |
| 11 | `sub_75b60` | 1 | `c25bafa` `call 0x75B60` | Failure/noreturn path after `[0xF9A8C78]` report. | [V] |
| 12 | `call qword ptr [0xF9A8C78]` | 1 | `c25baf4` `call qword ptr [0xF9A8C78]` | MSVC invalid-parameter/runtime-report (data_f9a8c78). Precedes sub_75b60 on failure path. | [V] |

Strings referenced (`xref.py str` matched to listing call sites):
- `0xF56AF2B` "GraphicsTasks Scheduler" — ref at c25b4f7 (`lea rax,[0xF56AF2B]`). Trace scope name. [V]
- `0xF573001` "GraphicsTasks Group" — ref at c25b63a (`movups xmm0,[0xF573001]`→[r14]). Group-object name (16B). [V]
- `0xF57337D` "s Parallel Group" — ref at c25b82b (`movups xmm0,[0xF57337D]`→[rbx+0xC]); continues into `0xF573371` "GraphicsTasks Parallel Group" — ref at c25b836 (`movups xmm0,[0xF573371]`→[rbx]). Parallel group name. [V]
- `0xF575FF8` source `"D:\\a\\_work\\1\\s\\handheld\\src-external\\RenderDragon\\src\\Tasks\\GraphicsTasks.cpp"` — debug/source path (string-table adjacency, not directly referenced by an instruction in this body). [I]
- `0xF0E4640` — vtable pointer stored into each sub-buffer `[r14]=r15` (c25b2e8 etc.). Not a string; a code vtable. [V]

UNVERIFIED callees: none remaining — all 12 direct/indirect call targets accounted for in the body.

## (4) Scheduler object fields read/written

`a0` = rcx at entry = rsi throughout. `descscan2.py --start 0xc25b1a0 --end 0xc25bb00 --reg rsi --events` read map + listing write sites. Direction: R = read, W = write. Queue/vector fields and atomic/lock ops noted. [V descscan2 + listing]

| Offset | Size | Direction | Meaning (from context) | Evidence (RVA) | Tag |
|---|---|---|---|---|-----|
| +0x000 | dword | W | scheduler state/counter, zeroed at entry | `mov dword ptr [rcx],0` c25b1d6; read `mov [rsi],eax` c25b934 (perf value from sub_775d90) | [V] |
| +0x004 | word | W | zeroed at entry | `mov word ptr [rcx+4],0` c25b1dc | [V] |
| +0x008 | dword | W | zeroed at entry | `mov dword ptr [rcx+8],0` c25b1e2 | [V] |
| +0x010 | qword | W/R | stored arg1 (a1) pointer | `mov [rcx+0x10],rdx` c25b1e9; read `mov rcx,[rsi+0x10]` c25b8f6 | [V] |
| +0x018 | xmmword (16B) | W | zeroed | `movups [rcx+0x18],xmm0` c25b1f7 | [V] |
| +0x018 | qword | W | vector begin ptr | `mov [rsi+0x18],rcx` c25b282; `mov [rsi+0x20],rcx` c25b286 (end=begin initially) | [V] |
| +0x020 | qword | W | vector end ptr | `mov [rsi+0x20],rcx` c25b286; `mov [rsi+0x20],rbx` c25b29d | [V] |
| +0x028 | qword | W | vector cap ptr (=begin+size) | `mov qword ptr [rcx+0x28],0` c25b1fb; `mov [rsi+0x28],rbx` c25b28e (rbx=rcx+r12) | [V] |
| +0x030 | qword | W | sub-buffer[0] ptr (alloc size 0x278) | `mov [rsi+0x30],r14` c25b2a9 | [V] |
| +0x038 | qword | W/R | sub-buffer[0] end/back-ptr | `mov [rsi+0x38],r14` c25b31a; `lea rax,[rsi+0x38]` c25b312 | [V] |
| +0x040 | qword | W | sub-buffer[0] +0x10 back-ref | `mov [rsi+0x40],rax` c25b322 | [V] |
| +0x048 | qword | W/R | sub-buffer[1] ptr | `mov [rsi+0x48],r14` c25b382; `lea rax,[rsi+0x48]` c25b37a | [V] |
| +0x050 | qword | W | sub-buffer[1] +0x10 back-ref | `mov [rsi+0x50],rax` c25b38a | [V] |
| +0x058 | qword | W/R | sub-buffer[2] ptr | `mov [rsi+0x58],r14` c25b3ea; `lea rax,[rsi+0x58]` c25b3e2 | [V] |
| +0x060 | qword | W | sub-buffer[2] +0x10 back-ref | `mov [rsi+0x60],rax` c25b3f2 | [V] |
| +0x068 | qword | W/R | sub-buffer[3] ptr | `mov [rsi+0x68],r14` c25b452; `lea rax,[rsi+0x68]` c25b44a | [V] |
| +0x070 | qword | W | sub-buffer[3] +0x10 back-ref | `mov [rsi+0x70],rax` c25b45a | [V] |
| +0x078 | qword | W/R | sub-buffer[4] ptr | `mov [rsi+0x78],r14` c25b4ba; `lea rax,[rsi+0x78]` c25b4b2 | [V] |
| +0x080 | qword | W | sub-buffer[4] +0x10 back-ref | `mov [rsi+0x80],rax` c25b4c2 | [V] |
| +0x088 | xmmword (16B) | W | zeroed | `movups [rsi+0x88],xmm6` c25b4e9; `lea rax,[rsi+0x88]` c25b4c9 | [V] |
| +0x098 | xmmword (16B) | W | zeroed | `movups [rsi+0x98],xmm6` c25b4f0; `lea rax,[rsi+0x98]` c25b4d4 | [V] |
| +0x0A8 | addr (8B) | W/R | trace scope object address (r15=rsi+0xA8) | `lea r15,[rsi+0xA8]` c25b4df (x4: c25b4df,c25b59b,c25b72e,c25b78b) | [V] |
| +0x118 | qword | W/R | task queue #1 head ptr | `lea rax,[rsi+0x118]` c25b55b; `mov [rax],rbx` c25b682 (`[rsi+0x118]=rbx`) | [V] |
| +0x120 | dword | W | counter reset after queue #1 | `mov dword ptr [rsi+0x120],0` c25b6c4 | [V] |
| +0x128 | qword | W/R | task queue #2 head ptr | `lea rax,[rsi+0x128]` c25b74d; `mov [rax],rbx` c25b870 (`[rsi+0x128]=rbx`) | [V] |
| +0x130 | dword | W | counter reset after queue #2 | `mov dword ptr [rsi+0x130],0` c25b8b2 | [V] |
| +0x138 | qword | W | zeroed at phase H | `mov qword ptr [rsi+0x138],0` c25b905; `lea rax,[rsi+0x138]` c25b8fa | [V] |
| +0x140 | dword | W | zeroed at phase H | `mov dword ptr [rsi+0x140],0` c25b910 | [V] |
| +0x148 | qword/xmmword | W | queue-count accumulator = (end-begin)>>3 summed across queues | `movups [rsi+0x148],xmm0` c25b91d; `mov [rsi+0x148],rax` c25b94d; `mov [rdx],rax` c25b98f/9c2/9d8 where rdx=&[rsi+0x148] | [V] |

descscan2 read-byte summary: reads 0x0-0x4, 0x10-0xa8, 0x120-0x124, 0x130-0x134, 0x138-0x144, 0x148-0x158. GAPS (unread inside [0,0x158)): 0x4-0x10, 0xa8-0x120, 0x124-0x130, 0x134-0x138, 0x144-0x148. `copy rax <- rsi at c25ba15` (return value = scheduler obj). [V descscan2]

Queue/vector fields: +0x18/+0x20/+0x28 form a begin/end/cap triad (std::vector-like). Grow pattern: size via `rax*8`, if >0x200 use `(size+0x27)&~0x20` aligned alloc via sub_eea6040, store cap at `[rcx-8]=rbx` (c25b259), end=begin+size (c25b28a). Each of the 5 sub-buffers (0x38..0x80) is allocated 0x278 bytes, memzeroed 0x268, profiler-marked 0x400, and carries vtable 0xF0E4640 at +0x0 and count 0x100000001 at +0x8.

Atomic/lock operations: NONE in 0xc25b1a0 body — grep for `lock`/`cmpxchg`/`xadd` over docs/progress/oc_U-C3a_listing_utf8.txt returns 0 matches. [V] (lock inc appears in CALLER 0x660d940 at 0x660da70 `lock inc dword [r14+8]` and 0x660db7d `lock inc [rax+8]`, NOT in the scheduler itself — flagged for the caller unit.)

[UNVERIFIED: 0xc25b1a0] exact semantic of +0x0 dword (perf counter? flag?) — written by sub_775d90 result at c25b934, meaning not pinned by disassembly alone.
[UNVERIFIED: 0xc25b1a0] +0x4/+0x8 zeroed at entry but never read in this body; purpose unknown (padding or used by caller/callee).
[UNVERIFIED: 0xc25b1a0] vtable 0xF0E4640 stored into each sub-buffer +0x0 — interface identity not resolved from static analysis.

## (5) Callers

`rdis callers 0xc25b1a0` → one direct caller: `sub_660d940`. `xref.py callers 0xc25b1a0` → 0x660d940 (1 call site). inventory_L3_dragon.tsv L213: `0xc25b1a0 0x960 L3 plain 1 0x660d940 7 GraphicsTasks Scheduler task scheduler D1`. functions.tsv L35: `0xc25b1a0 L3 task scheduler D1 6ac`. BGFX_MAP 6ac L570: "0xc25b1a0 (0x960) GraphicsTasks Scheduler: allocation heavy (0x9bc830 x11, free x5), uses 0x1d2c10 x5, 0x7cd250 x4, 0xc264090 x2 (task queue)." [V]

| # | Caller RVA | Size | Call site in caller | Identification | Args at call site | Tag |
|---|------------|------|---------------------|----------------|-------------------|-----|
| 1 | 0x660d940 | 0x98b | `0x660daef` `call sub_c25b1a0` | BgfxFrameBuilder task-submit helper; single direct caller of the scheduler | rcx=r14 (scheduler obj), rdx=rdi (desc ptr), r8=rsi, r9=rdx (a3) | [V rdis callers + xref] |

Only 1 direct caller total (rdis callers returns exactly one entry; "1 xrefs in" from rdis fn matches). No indirect/vtable/thunk callers of 0xc25b1a0 found. [V]

## Verification artifacts
- docs/progress/oc_U-C3a_listing_utf8.txt — `rdis ... dis 0xc25b1a0` (full body 0xc25b1a0..0xc25bb00)
- docs/progress/oc_U-C3a_callees.txt — `rdis callees 0xc25b1a0`
- docs/progress/oc_U-C3a_callers_rdis.txt — `rdis callers 0xc25b1a0`
- docs/progress/oc_U-C3a_descscan2_rsi.txt — `python tools/sigs/descscan2.py --start 0xc25b1a0 --end 0xc25bb00 --reg rsi --events`
- docs/progress/oc_U-C3a_struct.txt — `rdis struct 0xc25b1a0` (derived, empty field list)

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-C3a.md`

## TOOL REQUESTS
None — all required data gathered with existing rdis/descscan2/xref tools; no throwaway scripts written.
