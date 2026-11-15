# Unit U-BA3 — bodyActor function 0x66d0a00 (1.26.62.01), continued from 0x66d2d50

## NEXT [current]
Resume at RVA 0x66d36de (after phase 11, 0x66d35f7..0x66d36dd). Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d36de 40`
Scope: 1200 instructions from 0x66d2d50 in 40-instruction phases (~30 phases total; phases 1-11 done, 440 instructions). On any `(bad)` line, restart the phase at the next address after it. Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Context [V]
- Continuation of U-BA2 (docs/progress/oc_U-BA2.md), which covered 0x66d23a3..0x66d2d59 (phases 1-14) of bodyActor 0x66d0a00.
- State carried in: table-scan index/flag slots [rbp+0x4D0]/[rbp+0x4D2] (0x10-stride scans, callee 0x5679DB0) and [rbp+0x7E0]/[rbp+0x7E2] (0x30-stride scans, callee 0xBCABA00); value struct at [rbp+0xA50..0xA5C]; out ctx [rbp+0xCE0]; work buffer [rbp+0x400]/[rbp+0x410]; node list walked via [r12] with sentinel r13=[rbp+0xA58]; node data ptr [r12+0x10]; callee 0x66D93C0(rcx=&rbp+0xCE0, rdx=&rbp+0x400, r8=&rbp+0x7E0, r9=r12+0x18); sub_e935700 for small/oversized results; indirect call qword ptr [0xF9A8C78] at loop exit; TLS gate pattern eax=[data global]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg <fallback> [V, U-BA2 phases 1-14].

## Gap fills [V]
Real lines from `rdis dis ~0x10 before each gap` (each gap is the single instruction that was missing/misaligned in U-BA2).

### Gap at 0x66d2513 (from `rdis dis 0x66d2503 40`)
```
66d2511  test al,0xFB                                  
66d2513  jne short 0x66D2520                           ; -> loc_66d2520
66d2515  or r14b,0x40                                  
66d2519  mov r13w,0x500                                
66d251e  jmp short 0x66D2523                           ; -> loc_66d2523
loc_66d2520:  ; from 66d2513
  66d2520  xor r13d,r13d                                 
```
`//` [V] Gap 0x66d2513 = `jne short 0x66D2520` (2 bytes): after `test al,0xFB` at 0x66d2511, non-zero jumps to `xor r13d,r13d` at 0x66d2520; fall-through `or r14b,0x40` at 0x66d2515 then `mov r13w,0x500` at 0x66d2519 [V]. Replaces U-BA2 phase-3's garbled `or eax,[rcx-0x80]`/`(bad)` at 0x66d2514-0x66d2517 [I].

### Gap at 0x66d275f (from `rdis dis 0x66d274f 40`)
```
66d2759  mov eax,[rax+4]                               
66d275f  mov r15,[r8+0x108]                            ; R a2+0x108
66d2766  test r15,r15                                  
66d2769  je 0x66D28BE                                  ; -> loc_66d28be
```
`//` [V] Gap 0x66d275f = `mov r15,[r8+0x108]` (4 bytes): entered from `je 0x66d275f`/`jne 0x66d275f` (phases 5-6); then `test r15,r15; je 0x66d28be` [V]. U-BA2 phase 7's listed start 0x66d275e was 1 byte into misaligned pad bytes; real code starts at 0x66d275f [I].

### Gap at 0x66d2ca0 (from `rdis dis 0x66d2c90 40`)
```
66d2c9f  in al,dx                                      
66d2ca0  je 0x66D2D59                                  ; -> loc_66d2d59
66d2ca6  lea r15,[rbp+0xCE0]                           
66d2cad  lea r14,[rbp+0x400]                           
```
`//` [V] Gap 0x66d2ca0 = `je 0x66D2D59` (rel32, 6 bytes spanning 0x66d2ca0..0x66d2ca6): if flag (byte [rdi+0x100]==1 test) zero → 0x66d2d59 loop-exit block [V]. U-BA2 phase 14 really starts at 0x66d2ca6 `lea r15,[rbp+0xCE0]`; its `mov bl,0`/`add [rax],al` at 0x66d2ca2-0x66d2ca5 were misaligned bytes inside this je [I].

### Gap at 0x66d2d3e (from `rdis dis 0x66d2d2e 40`)
```
66d2d37  sub rcx,rax                                   
66d2d3a  cmp rcx,0x20                                  
66d2d3e  jb short 0x66D2CC0                            ; -> sub_66d2cc0
loc_66d2d40:  ; from 66d2d87, 66d3d39
  66d2d40  mov qword ptr [rsp+0x20],0                    
```
`//` [V] Gap 0x66d2d3e = `jb short 0x66D2CC0` (2 bytes): after `cmp rcx,0x20` at 0x66d2d3a, below-unsigned → 0x66d2cc0 (`sub_e935700` path); else fall to 0x66d2d40 [V]. U-BA2 phase 14's `jb` at 0x66d2d3a was misaligned; real `cmp rcx,0x20` at 0x66d2d3a [I].

## Phase 1 — 0x66d2d50, 40 instructions [V]
```
66d2d50  xor r9d,r9d                                   
66d2d53  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
66d2d59  mov rcx,[rbp+0xA68]                           
66d2d60  test rcx,rcx                                  
66d2d63  je short 0x66D2D95                            ; -> loc_66d2d95
66d2d65  mov rdx,[rbp+0xA78]                           
66d2d6c  sub rdx,rcx                                   
66d2d6f  cmp rdx,0x1000                                
66d2d76  jb short 0x66D2D90                            ; -> loc_66d2d90
66d2d78  mov rax,[rcx-8]                               
66d2d7c  add rcx,0xFFFFFFFFFFFFFFF8                    
66d2d80  sub rcx,rax                                   
66d2d83  cmp rcx,0x20                                  
66d2d87  jae short 0x66D2D40                           ; -> sub_66d2d40
66d2d89  add rdx,0x27                                  
66d2d8d  mov rcx,rax                                   

loc_66d2d90:  ; from 66d2d76
  66d2d90  call 0xE935700                                ; -> sub_e935700

loc_66d2d95:  ; from 66d2d63
  66d2d95  mov rax,[r13+8]                               
  66d2d99  mov qword ptr [rax],0                         
  66d2da0  mov rcx,[r13]                                 
  66d2da4  test rcx,rcx                                  
  66d2da7  je short 0x66D2DC5                            ; -> loc_66d2dc5
  66d2da9  nop [rax]                                     

loc_66d2db0:  ; from 66d2dc3
  66d2db0  mov rbx,[rcx]                                 
  66d2db3  mov edx,0x28                                  
  66d2db8  call 0xE935700                                ; -> sub_e935700
  66d2dbd  mov rcx,rbx                                   
  66d2dc0  test rbx,rbx                                  
  66d2dc3  jne short 0x66D2DB0                           ; -> loc_66d2db0

loc_66d2dc5:  ; from 66d2da7
  66d2dc5  mov edx,0x28                                  
  66d2dca  mov rcx,r13                                   
  66d2dcd  call 0xE935700                                ; -> sub_e935700
  66d2dd2  mov eax,[0x129F90F0]                          ; [data_129f90f0]
  66d2dd8  mov ecx,[0x128767C8]                          ; [data_128767c8]
  66d2dde  mov rdx,gs:[0x58]                             
  66d2de7  mov rcx,[rdx+rcx*8]                           
  66d2deb  cmp eax,[rcx+4]                               
  66d2df1  jg 0x66D64F8                                  ; -> sub_66d64f8
  66d2df7  mov ebx,[rbp+0xCD4]                           
  66d2dfd  test bl,bl                                    
```
`//` [V] Phase 1 is the tail of the node-list free loop from U-BA2 phase 14: `xor r9d,r9d; call qword ptr [0xF9A8C78]` (indirect exit call) [V]; then iterate r13=[rbp+0xA68] list: `mov rcx,[rbp+0xA68]; test rcx,rcx; je 0x66d2d95`; size = [rbp+0xA78]-[rbp+0xA68]; if <0x1000 →0x66d2d90 `call 0xE935700` [V]; else heap-header arithmetic `rax=[rcx-8]; rcx-=8; rcx-=rax; cmp rcx,0x20; jae 0x66d2d40` (shared block) [V], else `add rdx,0x27; rcx=rax` →0x66d2d90 [V]. loc_66d2d95: `[rax]=0` where rax=[r13+8] (null-terminate node payload) [V]; walk `rcx=[r13]`, `je 0x66d2dc5` if null [V]; loc_66d2db0 free loop: `rbx=[rcx]; mov edx,0x28; call 0xE935700; rcx=rbx; test rbx,rbx; jne 0x66d2db0` — free each node with size 0x28 [V]; loc_66d2dc5: `mov edx,0x28; mov rcx,r13; call 0xE935700` free head [V]. Then TLS gate: eax=[0x129F90F0]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d64f8 [V] (new fallback); ebx=[rbp+0xCD4]; test bl,bl (phase 2) [V]. [I]: list teardown frees every node (0x28 bytes each) then runs a TLS version gate; 0xF9A8C78 call is likely an allocator/free IAT entry.

## Phase 2 — 0x66d2dff, 40 instructions [V]
```
66d2dff  jne short 0x66D2E06                           ; -> loc_66d2e06
66d2e01  xorps xmm0,xmm0                               
66d2e04  jmp short 0x66D2E0E                           ; -> loc_66d2e0e

loc_66d2e06:  ; from 66d2dff
  66d2e06  movss xmm0,[0xEEC8060]                        ; [data_eec8060]

loc_66d2e0e:  ; from 66d2e04
  66d2e0e  shufps xmm0,xmm0,0                            
  66d2e12  movaps [rbp+0xA50],xmm0                       
  66d2e19  mov qword ptr [rbp+0x7E0],1                   
  66d2e24  lea rax,[rbp+0xA50]                           
  66d2e2b  mov [rbp+0x7E8],rax                           
  66d2e32  mov rax,[rbp+0xD18]                           
  66d2e39  movzx r8d,word ptr [rbp+0xD22]                
  66d2e41  mov edx,r8d                                   
  66d2e44  shl edx,4                                     
  66d2e47  mov rcx,rax                                   
  66d2e4a  test r8d,r8d                                  
  66d2e4d  je short 0x66D2E75                            ; -> loc_66d2e75
  66d2e4f  mov r8,[0x129F90E8]                           ; [data_129f90e8]
  66d2e56  mov r9,rdx                                    
  66d2e59  mov rcx,rax                                   
  66d2e5c  nop [rax]                                     

loc_66d2e60:  ; from 66d2e71
  66d2e60  mov r10,[rcx]                                 
  66d2e63  cmp [r10+0x28],r8                             
  66d2e67  je short 0x66D2E75                            ; -> loc_66d2e75
  66d2e69  add rcx,0x10                                  
  66d2e6d  add r9,0xFFFFFFFFFFFFFFF0                     
  66d2e71  jne short 0x66D2E60                           ; -> loc_66d2e60
  66d2e73  jmp short 0x66D2EAB                           ; -> loc_66d2eab

loc_66d2e75:  ; from 66d2e4d, 66d2e67
  66d2e75  add rdx,rax                                   
  66d2e78  cmp rcx,rdx                                   
  66d2e7b  jae short 0x66D2EAB                           ; -> loc_66d2eab
  66d2e7d  sub ecx,eax                                   
  66d2e7f  shr ecx,4                                     
  66d2e82  mov [rbp+0x4D0],cx                            
  66d2e89  mov byte ptr [rbp+0x4D2],1                    
  66d2e90  lea rdx,[rbp+0x4D0]                           
  66d2e97  lea r8,[rbp+0x7E0]                            
  66d2e9e  lea rcx,[rbp+0xCE8]                           
  66d2ea5  call 0x5679DB0                                ; -> sub_5679db0
  66d2eaa  nop                                           

loc_66d2eab:  ; from 66d2e73, 66d2e7b
  66d2eab  cmp byte ptr [rbp+0xD8B],0                    
```
`//` [V] Phase 2: `test bl,bl` (tail of phase 1) → `jne short 0x66d2e06` at 0x66d2dff; if zero: `xorps xmm0`; jmp 0x66d2e0e [V]. loc_66d2e06: `movss xmm0,[0xEEC8060]` (.rodata float const) [V]; `shufps` broadcast lo dword; `movaps [rbp+0xA50],xmm0` (16-byte float value) [V]; `mov qword ptr [rbp+0x7E0],1`; `[rbp+0x7E8]=&rbp+0xA50` [V]. 0x10-stride table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22] (count); edx=r8d<<4; rcx=rax; if r8d==0 →0x66d2e75; else key r8=[0x129F90E8] (31st global); loop 0x66d2e60: r10=[rcx]; cmp [r10+0x28],r8; je 0x66d2e75; rcx+=0x10; r9-=0x10 jne; no match →jmp 0x66d2eab [V]. Match-end 0x66d2e75: add rdx,rax; cmp rcx,rdx; jae 0x66d2eab; else index=(ecx-rax)>>4→[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (39th call-0x5679DB0); nop. Converge 0x66d2eab: `cmp byte ptr [rbp+0xD8B],0` (phase 3) [V]. [I]: value = broadcast float const [0xEEC8060]; scan key = global [0x129F90E8].

## Phase 3 — 0x66d2eb2, 40 instructions [V]
```
66d2eb2  je 0x66D31E0                                  ; -> loc_66d31e0
66d2eb8  mov rdx,[rdi]                                 
66d2ebb  mov rbx,[rdx+0xB0]                            
66d2ec2  mov rax,[rbx+0x60]                            
66d2ec6  sub rax,[rbx+0x58]                            
66d2eca  shr rax,2                                     
66d2ece  imul eax,0xAAAAAAAB                           
66d2ed4  test eax,eax                                  
66d2ed6  je short 0x66D2F0E                            ; -> loc_66d2f0e
66d2ed8  mov edx,0x250                                 
66d2edd  add rdx,[rbp+0xCE0]                           
66d2ee4  lea rcx,[rbp+0xA50]                           
66d2eeb  xor r8d,r8d                                   
66d2eee  call 0xBBD7C70                                ; -> sub_bbd7c70
66d2ef3  nop                                           
66d2ef4  lea rdx,[rbp+0xA50]                           
66d2efb  mov rcx,rbx                                   
66d2efe  call 0x4DEDD00                                ; -> sub_4dedd00
66d2f03  nop                                           
66d2f04  mov rdx,[rdi]                                 
66d2f07  mov rbx,[rdx+0xB0]                            

loc_66d2f0e:  ; from 66d2ed6
  66d2f0e  mov ecx,[rdx+0xB8]                            
  66d2f14  xor eax,eax                                   
  66d2f16  cmp byte ptr [rbx+0x1D4],0                    
  66d2f1d  je short 0x66D2F25                            ; -> loc_66d2f25
  66d2f1f  mov eax,[rbx+0x1D0]                           

loc_66d2f25:  ; from 66d2f1d
  66d2f25  test ecx,ecx                                  
  66d2f27  jle short 0x66D2F3B                           ; -> loc_66d2f3b
  66d2f29  mov ecx,ecx                                   
  66d2f2b  mov eax,0xAAAAAAAB                            
  66d2f30  imul rax,rcx                                  
  66d2f34  shr rax,0x20                                  
  66d2f38  and eax,0xFFFFFFFE                            

loc_66d2f3b:  ; from 66d2f27
  66d2f3b  mov [rbp+0x754],eax                           
  66d2f41  test eax,eax                                  
  66d2f43  je 0x66D6108                                  ; -> sub_66d6108
  66d2f49  movzx r8d,byte ptr [rbx+0x39]                 
  66d2f4e  add rdx,0x140                                 
  66d2f55  lea r13,[rbp+0x470]                           
  66d2f5c  mov rcx,r13                                   
```
`//` [V] Phase 3: `cmp byte [rbp+0xD8B],0; je 0x66d31e0` (phase-2 tail) [V]. Fall-through: rdx=[rdi]; rbx=[rdx+0xB0] (obj payload) [V]; count=(rbx+0x60)-(rbx+0x58)>>2; eax=count*0xAAAAAAAB low32 (magic multiply, /5-ish) [V]; test eax,eax; je 0x66d2f0e if zero [V]. Else: edx=0x250; rdx=[rbp+0xCE0]+0x250; rcx=&rbp+0xA50; r8d=0; call 0xBBD7C70(rdx=&rbp+0xCE0+0x250, rcx=&rbp+0xA50, r8=0) [V] (new callee); nop; lea rdx,&rbp+0xA50; rcx=rbx; call 0x4DEDD00(rcx=rbx, rdx=&rbp+0xA50) [V] (new callee); nop; rdx=[rdi]; rbx=[rdx+0xB0] (reload) [V]. loc_66d2f0e: ecx=[rdx+0xB8] ([rdi+0xB8]) [V]; eax=0; if byte [rbx+0x1D4]==0 →0x66d2f25 else eax=[rbx+0x1D0] [V]. test ecx,ecx; jle 0x66d2f3b; else eax=0xAAAAAAAB; imul rax,rcx; rax>>=0x20; eax&=0xFFFFFFFE (ecx/5 rounded to even) [V]; [rbp+0x754]=eax; test eax,eax; je 0x66d6108 [V] (new fallback); r8d=byte [rbx+0x39]; rdx+=0x140; r13=&rbp+0x470; rcx=r13 (phase 4) [V]. [I]: per-index bucket loop; [rbp+0x754] holds index count; 0x470 block is a per-index work area; two new callees 0xBBD7C70/0x4DEDD00 consume the float value.

## Phase 4 — 0x66d2f5f, 40 instructions [V]
```
66d2f5f  call 0x66B2B30                                ; -> sub_66b2b30
66d2f64  nop                                           
66d2f65  and byte ptr [rbp+0x474],0xF7                 
66d2f6c  mov rax,[rdi]                                 
66d2f6f  cmp byte ptr [rax+0x1C8],1                    
66d2f76  jne short 0x66D2F8D                           ; -> loc_66d2f8d
66d2f78  mov byte ptr [rbp+0x484],1                    
66d2f7f  movups xmm0,[rax+0x1B8]                       
66d2f86  movups [rbp+0x488],xmm0                       

loc_66d2f8d:  ; from 66d2f76
  66d2f8d  mov dword ptr [rbp+0x4D0],0x3F800000          
  66d2f97  xorps xmm0,xmm0                               
  66d2f9a  movups [rbp+0x4D4],xmm0                       
  66d2fa1  mov dword ptr [rbp+0x4E4],0x3F800000          
  66d2fab  movups [rbp+0x4E8],xmm0                       
  66d2fb2  mov dword ptr [rbp+0x4F8],0x3F800000          
  66d2fbc  movups [rbp+0x4FC],xmm0                       
  66d2fc3  movq xmm1,[0xEFD3400]                         ; [data_efd3400]
  66d2fcb  movq [rbp+0x50C],xmm1                         
  66d2fd3  movups [rbp+0x514],xmm0                       
  66d2fda  mov dword ptr [rbp+0x524],0x3F800000          
  66d2fe4  movups [rbp+0x528],xmm0                       
  66d2feb  mov dword ptr [rbp+0x538],0x3F800000          
  66d2ff5  movups [rbp+0x53C],xmm0                       
  66d2ffc  movq [rbp+0x54C],xmm1                         
  66d3004  movups [rbp+0x554],xmm0                       
  66d300b  mov dword ptr [rbp+0x564],0x3F800000          
  66d3015  movups [rbp+0x568],xmm0                       
  66d301c  mov dword ptr [rbp+0x578],0x3F800000          
  66d3026  movups [rbp+0x57C],xmm0                       
  66d302d  movq [rbp+0x58C],xmm1                         
  66d3035  movups [rbp+0x594],xmm0                       
  66d303c  mov dword ptr [rbp+0x5A4],0x3F800000          
  66d3046  movups [rbp+0x5A8],xmm0                       
  66d304d  mov dword ptr [rbp+0x5B8],0x3F800000          
  66d3057  movups [rbp+0x5BC],xmm0                       
  66d305e  movq [rbp+0x5CC],xmm1                         
  66d3066  movups [rbp+0x5D4],xmm0                       
  66d306d  mov dword ptr [rbp+0x5E4],0x3F800000          
  66d3077  movups [rbp+0x5E8],xmm0                       
  66d307e  mov dword ptr [rbp+0x5F8],0x3F800000          
```
`//` [V] Phase 4: call 0x66B2B30; nop [V] (new callee); `and byte ptr [rbp+0x474],0xF7` (clear bits 3 and 0 of flag byte) [V]; rax=[rdi]; if byte [rax+0x1C8]==1: [rbp+0x484]=1; movups xmm0=[rax+0x1B8]; [rbp+0x488]=xmm0 (16 bytes) [V]. loc_66d2f8d: float-struct initializer at [rbp+0x4D0..0x602]: repeated 0x14-stride blocks `[base+0]=0x3F800000 (1.0f), [base+4..base+0x13]=0` with xmm1=[0xEFD3400] written as qword at 0x50C, 0x54C, 0x58C, 0x5CC [V]; xmm0=0 zeroes 16-byte slots between [V]. Last write [rbp+0x5F8]=0x3F800000 ends phase [V]. [I]: r13=&rbp+0x470 (phase 3) anchors a per-instance float-param block; defaults are 1.0f with selected fields carrying the [0xEFD3400] constant. Callee 0x66B2B30 ran before the flag clear [I].

## Phase 5 — 0x66d3088, 40 instructions [V]
```
66d3088  movups [rbp+0x5FC],xmm0                       
66d308f  movq [rbp+0x60C],xmm1                         
66d3097  movups [rbp+0x614],xmm0                       
66d309e  mov dword ptr [rbp+0x624],0x3F800000          
66d30a8  movups [rbp+0x628],xmm0                       
66d30af  mov dword ptr [rbp+0x638],0x3F800000          
66d30b9  movups [rbp+0x63C],xmm0                       
66d30c0  movq [rbp+0x64C],xmm1                         
66d30c8  movups [rbp+0x654],xmm0                       
66d30cf  mov dword ptr [rbp+0x664],0x3F800000          
66d30d9  movups [rbp+0x668],xmm0                       
66d30e0  mov dword ptr [rbp+0x678],0x3F800000          
66d30ea  movups [rbp+0x67C],xmm0                       
66d30f1  movq [rbp+0x68C],xmm1                         
66d30f9  movups [rbp+0x694],xmm0                       
66d3100  mov dword ptr [rbp+0x6A4],0x3F800000          
66d310a  movups [rbp+0x6A8],xmm0                       
66d3111  mov dword ptr [rbp+0x6B8],0x3F800000          
66d311b  movups [rbp+0x6BC],xmm0                       
66d3122  mov dword ptr [rbp+0x6CC],0x3F800000          
66d312c  mov rcx,[rax+0xC0]                            
66d3133  cmp rcx,0xFFFFFFFFFFFFFFFF                    
66d3137  je 0x66D5F14                                  ; -> sub_66d5f14
66d313d  mov rax,[rax+0xC8]                            
66d3144  mov [rbp+0x3F0],rcx                           
66d314b  mov [rbp+0x3F8],rax                           
66d3152  test rax,rax                                  
66d3155  setne al                                      
66d3158  test rcx,rcx                                  
66d315b  sete cl                                       
66d315e  or cl,al                                      
66d3160  je 0x66D5F14                                  ; -> sub_66d5f14
66d3166  lea rcx,[rbp+0x3F0]                           
66d316d  lea r14,[rbp+0x4D0]                           
66d3174  mov rdx,r14                                   
66d3177  call 0x6698060                                ; -> sub_6698060
66d317c  nop                                           
66d317d  mov qword ptr [rbp+0xA50],8                   
66d3188  mov [rbp+0xA58],r14                           
66d318f  mov rax,[rbp+0xD18]                           
```
`//` [V] Phase 5: float-struct init continues: [rbp+0x5FC]=0, [rbp+0x60C]=xmm1, [rbp+0x614]=0, [rbp+0x624]=1.0f, [rbp+0x628]=0, [rbp+0x638]=1.0f, [rbp+0x63C]=0, [rbp+0x64C]=xmm1, [rbp+0x654]=0, [rbp+0x664]=1.0f, [rbp+0x668]=0, [rbp+0x678]=1.0f, [rbp+0x67C]=0, [rbp+0x68C]=xmm1, [rbp+0x694]=0, [rbp+0x6A4]=1.0f, [rbp+0x6A8]=0, [rbp+0x6B8]=1.0f, [rbp+0x6BC]=0, [rbp+0x6CC]=1.0f [V]. Then rcx=[rax+0xC0] (rax=[rdi]) [V]; if rcx==-1 →0x66d5f14 [V]; rax=[rax+0xC8] [V]; [rbp+0x3F0]=rcx; [rbp+0x3F8]=rax ({ptr,len} pair) [V]; flag=([rax]!=0)||([rcx]!=0) via setne/sete+or [V]; if flag==0 →0x66d5f14 [V]. rcx=&rbp+0x3F0; r14=&rbp+0x4D0; rdx=r14; call 0x6698060(rcx={ptr,len}@rbp+0x3F0, rdx=&rbp+0x4D0) [V] (new callee); nop; [rbp+0xA50]=8 (qword, value size); [rbp+0xA58]=r14=&rbp+0x4D0 (value ptr) [V] — value struct now points at the float block; rax=[rbp+0xD18] (phase 6) [V]. [I]: [rbp+0x3F0..0x3F8] is a {ptr,len} from [rdi+0xC0/+0xC8]; 0x6698060 parses/converts it into floats at [rbp+0x4D0]; value struct [rbp+0xA50]=8 bytes, [rbp+0xA58]=&rbp+0x4D0 set up for a pending value-consuming call (likely 0xBCABA00).

## Phase 6 — 0x66d3196, 40 instructions [V]
```
66d3196  movzx edx,word ptr [rbp+0xD22]                
66d319d  mov ecx,edx                                   
66d319f  shl ecx,4                                     
66d31a2  mov r8,rax                                    
66d31a5  test edx,edx                                  
66d31a7  je 0x66D36E7                                  ; -> loc_66d36e7
66d31ad  mov r9,[0x129F8310]                           ; [data_129f8310]
66d31b4  xor r8d,r8d                                   
66d31b7  nop [rax+rax]                                 

loc_66d31c0:  ; from 66d31d5
  66d31c0  mov r10,[rax+r8]                              
  66d31c4  cmp [r10+0x28],r9                             
  66d31c8  je 0x66D36E4                                  ; -> loc_66d36e4
  66d31ce  add r8,0x10                                   
  66d31d2  cmp rcx,r8                                    
  66d31d5  jne short 0x66D31C0                           ; -> loc_66d31c0
  66d31d7  mov dx,1                                      
  66d31db  jmp 0x66D3734                                 ; -> loc_66d3734

loc_66d31e0:  ; from 66d2eb2 (phase 3 je)
  66d31e0  movd xmm0,[rdi+0x88]                          
  66d31e8  movq xmm1,[rdi+0x80]                          
  66d31f0  movq [rbp+0xA50],xmm1                         
  66d31f8  movd [rbp+0xA58],xmm0                         
  66d3200  mov dword ptr [rbp+0xA5C],0                   
  66d320a  mov qword ptr [rbp+0x7E0],1                   
  66d3215  lea rax,[rbp+0xA50]                           
  66d321c  mov [rbp+0x7E8],rax                           
  66d3223  mov rax,[rbp+0xD18]                           
  66d322a  movzx r8d,word ptr [rbp+0xD22]                
  66d3232  mov edx,r8d                                   
  66d3235  shl edx,4                                     
  66d3238  mov rcx,rax                                   
  66d323b  test r8d,r8d                                  
  66d323e  je short 0x66D3265                            ; -> loc_66d3265
  66d3240  mov r8,[0x129F8350]                           ; [data_129f8350]
  66d3247  mov r9,rdx                                    
  66d324a  mov rcx,rax                                   
  66d324d  nop [rax]                                     

loc_66d3250:  ; from 66d3261
  66d3250  mov r10,[rcx]                                 
  66d3253  cmp [r10+0x28],r8                             
  66d3257  je short 0x66D3265                            ; -> loc_66d3265
  66d3259  add rcx,0x10                                  
```
`//` [V] Phase 6: rax=[rbp+0xD18] (phase-5 tail) [V]; edx=[rbp+0xD22] count; ecx=edx<<4; r8=rax base; if count==0 →0x66d36e7 [V]; key r9=[0x129F8310]; r8d=0; 0x10-stride scan loop 0x66d31c0: r10=[rax+r8]; cmp [r10+0x28],r9; je 0x66d36e4; r8+=0x10; cmp rcx,r8; jne 0x66d31c0 [V]; no match: dx=1; jmp 0x66d3734 [V]. loc_66d31e0 (join target from phase 3's `je 0x66d31e0`): value struct from obj: movd xmm0=[rdi+0x88]; movq xmm1=[rdi+0x80]; [rbp+0xA50]=xmm1 (qword); movd [rbp+0xA58]=xmm0 (dword); [rbp+0xA5C]=0 [V]; [rbp+0x7E0]=1 (qword); [rbp+0x7E8]=&rbp+0xA50 [V]. Second scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx=r8d<<4; rcx=rax; if r8d==0 →0x66d3265; else key r8=[0x129F8350] (32nd global); r9=rdx; loop 0x66d3250: r10=[rcx]; cmp [r10+0x28],r8; je 0x66d3265; rcx+=0x10 (phase 7) [V]. [I]: first scan reports match via dx=1 to 0x66d3734; value struct = {qword [rdi+0x80], dword [rdi+0x88], 0} at [rbp+0xA50..0xA5C], likely consumed by a 0xBCABA00-style call later.

## Phase 7 — 0x66d325d, 40 instructions [V]
```
66d325d  add r9,0xFFFFFFFFFFFFFFF0                     
66d3261  jne short 0x66D3250                           ; -> sub_66d3250
66d3263  jmp short 0x66D329B                           ; -> loc_66d329b
66d3265  add rdx,rax                                   
66d3268  cmp rcx,rdx                                   
66d326b  jae short 0x66D329B                           ; -> loc_66d329b
66d326d  sub ecx,eax                                   
66d326f  shr ecx,4                                     
66d3272  mov [rbp+0x4D0],cx                            
66d3279  mov byte ptr [rbp+0x4D2],1                    
66d3280  lea rdx,[rbp+0x4D0]                           
66d3287  lea r8,[rbp+0x7E0]                            
66d328e  lea rcx,[rbp+0xCE8]                           
66d3295  call 0x5679DB0                                ; -> sub_5679db0
66d329a  nop                                           

loc_66d329b:  ; from 66d3263, 66d326b
  66d329b  mov rdx,[rbp+0xCD8]                           
  66d32a2  cmp byte ptr [rdx+0x75],0                     
  66d32a6  je 0x66D3698                                  ; -> loc_66d3698
  66d32ac  mov rax,[rdi]                                 
  66d32af  mov rcx,[rax+0x140]                           
  66d32b6  lea r8,[rcx+0x10]                             
  66d32ba  test rcx,rcx                                  
  66d32bd  lea r13,[0x1232E708]                          ; [data_1232e708]
  66d32c4  cmove r8,r13                                  
  66d32c8  mov rbx,[rax+0xB0]                            
  66d32cf  mov rax,[rbx+0x60]                            
  66d32d3  sub rax,[rbx+0x58]                            
  66d32d7  mov r14,[r8]                                  
  66d32da  shr rax,2                                     
  66d32de  imul eax,0xAAAAAAAB                           
  66d32e4  test eax,eax                                  
  66d32e6  je short 0x66D3365                            ; -> loc_66d3365
  66d32e8  mov r12,rdx                                   
  66d32eb  mov edx,0x250                                 
  66d32f0  add rdx,[rbp+0xCE0]                           
  66d32f7  lea rcx,[rbp+0xA50]                           
  66d32fe  xor r8d,r8d                                   
  66d3301  call 0xBBD7C70                                ; -> sub_bbd7c70
  66d3306  nop                                           
  66d3307  movzx r15d,word ptr [rbp+0xA50]               
```
`//` [V] Phase 7: second 0x10-stride scan tail: add r9,-0x10; jne 0x66d3250; no match →jmp 0x66d329b [V]. Match-end 0x66d3265: add rdx,rax; cmp rcx,rdx; jae 0x66d329b; else index=(ecx-rax)>>4→[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (40th call-0x5679DB0); nop [V]. loc_66d329b: rdx=[rbp+0xCD8]; if byte [rdx+0x75]==0 →0x66d3698 [V]; rax=[rdi]; rcx=[rax+0x140]; r8=rcx+0x10; if rcx==0 →r8=[0x1232E708] via cmove (default string) [V]; rbx=[rax+0xB0]; count=(rbx+0x60)-(rbx+0x58)>>2; r14=[r8]; eax=count*0xAAAAAAAB low32; je 0x66d3365 if zero [V]; r12=rdx; edx=0x250; rdx=[rbp+0xCE0]+0x250; rcx=&rbp+0xA50; r8d=0; call 0xBBD7C70(rdx=&rbp+0xCE0+0x250, rcx=&rbp+0xA50, r8=0) [V] (2nd call); nop; r15d=word [rbp+0xA50] (phase 8) [V]. [I]: cmove selects default string [0x1232E708] when [rax+0x140]==0; [r8] derefed into r14; second 0xBBD7C70 call consumes updated value struct; per-bucket count loop continues.

## Phase 8 — 0x66d330e, 40 instructions [V]
```
66d330e  add [rax-0x73],cl                             
66d3311  lea edx,[rax+0xA]                             
66d3314  add [rax],al                                  
66d3316  mov dx,9                                      
66d331a  call 0x5AC2420                                ; -> sub_5ac2420
66d331f  nop                                           
66d3320  test r15d,0x200                               
66d3327  jne short 0x66D3352                           ; -> loc_66d3352
66d3329  movzx ecx,word ptr [rbp+0xA70]                
66d3330  mov [rbp+0xA64],cx                            
66d3337  movzx eax,ax                                  
66d333a  add eax,ecx                                   
66d333c  add eax,3                                     
66d333f  and eax,0xFFFC                                
66d3344  mov [rbp+0xA70],ax                            
66d334b  or byte ptr [rbp+0xA51],2                     

loc_66d3352:  ; from 66d3327
  66d3352  lea rdx,[rbp+0xA50]                           
  66d3359  mov rcx,rbx                                   
  66d335c  call 0x4DEDD00                                ; -> sub_4dedd00
  66d3361  nop                                           
  66d3362  mov rdx,r12                                   
  66d3365  mov rax,0x8D29EAE11B764987                    
  66d336f  cmp r14,rax                                   
  66d3372  je 0x66D6108                                  ; -> sub_66d6108
  66d3378  mov r8,[rdi]                                  
  66d337b  mov rax,[r8+0xB0]                             
  66d3382  test byte ptr [rax+0x1D9],1                   
  66d3389  je 0x66D6108                                  ; -> sub_66d6108
  66d338f  mov rax,[rbp+0xD70]                           
  66d3396  lea r9,[rax+0x120]                            
  66d339d  add rax,0x90                                  
  66d33a3  cmp dword ptr [rdx+0x70],2                    
  66d33a7  cmove r9,rax                                  
  66d33ab  lea rcx,[rbp+0xA50]                           
  66d33b2  call 0x6694660                                ; -> sub_6694660
  66d33b7  nop                                           
  66d33b8  cmp byte ptr [rbp+0xA58],1                    
  66d33bf  jne 0x66D6108                                 ; -> sub_66d6108
  66d33c5  mov rcx,[rbp+0xA50]                           
  66d33cc  mov rdx,[rdi]                                 
```
`//` [V] Phase 8: `add [rax-0x73],cl` (byte store into computed addr [V]); `lea edx,[rax+0xA]`; `add [rax],al`; `mov dx,9`; call 0x5AC2420 (new callee); nop [V]; `test r15d,0x200` (r15d=value low word from phase 7); jne 0x66d3352 [V]. Fall-through: ecx=[rbp+0xA70] (word); [rbp+0xA64]=cx; eax=ax+ecx+3; eax&=0xFFFC (align-up-4); [rbp+0xA70]=ax; [rbp+0xA51]|=2 [V]. loc_66d3352: lea rdx,&rbp+0xA50; rcx=rbx; call 0x4DEDD00(rcx=rbx, rdx=&rbp+0xA50) [V] (2nd call); nop; rdx=r12; rax=0x8D29EAE11B764987 (GUID-like const); if r14==rax →0x66d6108 [V]. r8=[rdi]; rax=[r8+0xB0]; if byte [rax+0x1D9]&1==0 →0x66d6108 [V]; rax=[rbp+0xD70]; r9=rax+0x120; rax+=0x90; if dword [rdx+0x70]==2 →r9=rax+0x90 via cmove [V]; rcx=&rbp+0xA50; call 0x6694660(rcx=&rbp+0xA50 value struct) [V] (new callee); nop; if byte [rbp+0xA58]!=1 →0x66d6108 [V]; rcx=[rbp+0xA50]; rdx=[rdi] (phase 9) [V]. [I]: r14 compared to a type GUID; [rdx+0x70]==2 selects +0x90 vs +0x120 base; [rbp+0xA58]==1 gate; multiple 0x66d6108 fallbacks.

## Phase 9 — 0x66d33cf, 40 instructions [V]
```
66d33cf  mov eax,[rdx+0xB8]                            ; R a1+0xB8
66d33d5  xor r12d,r12d                                 
66d33d8  cmp byte ptr [rcx+0x1E4],0                    ; R a0+0x1E4
66d33df  je short 0x66D33E8                            ; -> loc_66d33e8
66d33e1  mov r12d,[rcx+0x1E0]                          ; R a0+0x1E0

loc_66d33e8:  ; from 66d33df
  66d33e8  test eax,eax                                  
  66d33ea  jle short 0x66D3400                           ; -> loc_66d3400
  66d33ec  mov eax,eax                                   
  66d33ee  mov r12d,0xAAAAAAAB                           
  66d33f4  imul r12,rax                                  
  66d33f8  shr r12,0x20                                  
  66d33fc  and r12d,0xFFFFFFFE                           

loc_66d3400:  ; from 66d33ea
  66d3400  test r12d,r12d                                
  66d3403  je 0x66D6108                                  ; -> sub_66d6108
  66d3409  mov [rbp+0xD80],rcx                           
  66d3410  movzx r8d,byte ptr [rcx+0x49]                 ; R a0+0x49
  66d3415  add rdx,0x140                                 
  66d341c  lea rcx,[rbp+0x208]                           
  66d3423  call 0x66B2B30                                ; -> sub_66b2b30
  66d3428  nop                                           
  66d3429  mov rax,[rdi]                                 
  66d342c  cmp byte ptr [rax+0x1C8],1                    
  66d3433  jne short 0x66D344C                           ; -> loc_66d344c
  66d3435  mov byte ptr [rbp+0x21C],1                    
  66d343c  movdqu xmm0,[rax+0x1B8]                       
  66d3444  movdqu [rbp+0x220],xmm0                       

loc_66d344c:  ; from 66d3433
  66d344c  mov rax,[rbp+0xD90]                           
  66d3453  shr eax,0xE                                   
  66d3456  mov [rbp+0xCD4],eax                           
  66d345c  and al,[rbp+0xD6C]                            
  66d3462  cmp al,1                                      
  66d3464  mov rax,[rbp+0xD78]                           
  66d346b  jne short 0x66D347D                           ; -> loc_66d347d
  66d346d  cmp byte ptr [rax+0x130],0                    
  66d3474  jne short 0x66D347D                           ; -> loc_66d347d
  66d3476  mov byte ptr [rbp+0x20C],0xF                  

loc_66d347d:  ; from 66d346b, 66d3474
  66d347d  mov dword ptr [rbp+0x4D0],0x3F800000          
  66d3487  pxor xmm0,xmm0                                
  66d348b  movdqu [rbp+0x4D4],xmm0                       
  66d3493  mov dword ptr [rbp+0x4E4],0x3F800000          
```
`//` [V] Phase 9: rdx=[rdi] (phase-8 tail); eax=[rdx+0xB8] (count) [V]; r12d=0; if byte [rcx+0x1E4]!=0 (rcx=[rbp+0xA50] value ptr) →r12d=[rcx+0x1E0] [V]. test eax,eax; jle 0x66d3400; else eax=eax (movzx); r12d=0xAAAAAAAB; imul r12,rax; r12>>=0x20; r12d&=0xFFFFFFFE (count/5 even) [V]. test r12d,r12d; je 0x66d6108 if zero [V]. [rbp+0xD80]=rcx (save value ptr) [V]; r8d=byte [rcx+0x49] [V]; rdx+=0x140; rcx=&rbp+0x208; call 0x66B2B30(rcx=&rbp+0x208, rdx=&rbp+0xCE0+0x250, r8=byte [rcx+0x49]) [V] (2nd call); nop. rax=[rdi]; if byte [rax+0x1C8]==1: [rbp+0x21C]=1; movdqu xmm0=[rax+0x1B8]; [rbp+0x220]=xmm0 (16 bytes) [V]. rax=[rbp+0xD90]; eax=eax>>0xE; [rbp+0xCD4]=eax; al&=[rbp+0xD6C]; if al==1 and byte [rbp+0xD78+0x130]==0 →[rbp+0x20C]=0xF [V]. loc_66d347d: float init: [rbp+0x4D0]=1.0f; pxor xmm0; [rbp+0x4D4]=0; [rbp+0x4E4]=1.0f (phase 10) [V]. [I]: count field of value struct drives /5 loop bound; [rbp+0xD80] holds value ptr for later; [rbp+0xCD4] = ([rbp+0xD90]>>14) & [rbp+0xD6C].

## Phase 10 — 0x66d349d, 40 instructions [V]
```
66d349d  movdqu [rbp+0x4E8],xmm0                       
66d34a5  mov dword ptr [rbp+0x4F8],0x3F800000          
66d34af  movdqu [rbp+0x4FC],xmm0                       
66d34b7  movq xmm1,[0xEFD3400]                         ; [data_efd3400]
66d34bf  movq [rbp+0x50C],xmm1                         
66d34c7  movdqu [rbp+0x514],xmm0                       
66d34cf  mov dword ptr [rbp+0x524],0x3F800000          
66d34d9  movdqu [rbp+0x528],xmm0                       
66d34e1  mov dword ptr [rbp+0x538],0x3F800000          
66d34eb  movdqu [rbp+0x53C],xmm0                       
66d34f3  movq [rbp+0x54C],xmm1                         
66d34fb  movdqu [rbp+0x554],xmm0                       
66d3503  mov dword ptr [rbp+0x564],0x3F800000          
66d350d  movdqu [rbp+0x568],xmm0                       
66d3515  mov dword ptr [rbp+0x578],0x3F800000          
66d351f  movdqu [rbp+0x57C],xmm0                       
66d3527  movq [rbp+0x58C],xmm1                         
66d352f  movdqu [rbp+0x594],xmm0                       
66d3537  mov dword ptr [rbp+0x5A4],0x3F800000          
66d3541  movdqu [rbp+0x5A8],xmm0                       
66d3549  mov dword ptr [rbp+0x5B8],0x3F800000          
66d3553  movdqu [rbp+0x5BC],xmm0                       
66d355b  movq [rbp+0x5CC],xmm1                         
66d3563  movdqu [rbp+0x5D4],xmm0                       
66d356b  mov dword ptr [rbp+0x5E4],0x3F800000          
66d3575  movdqu [rbp+0x5E8],xmm0                       
66d357d  mov dword ptr [rbp+0x5F8],0x3F800000          
66d3587  movdqu [rbp+0x5FC],xmm0                       
66d358f  movq [rbp+0x60C],xmm1                         
66d3597  movdqu [rbp+0x614],xmm0                       
66d359f  mov dword ptr [rbp+0x624],0x3F800000          
66d35a9  movdqu [rbp+0x628],xmm0                       
66d35b1  mov dword ptr [rbp+0x638],0x3F800000          
66d35bb  movdqu [rbp+0x63C],xmm0                       
66d35c3  movq [rbp+0x64C],xmm1                         
66d35cb  movdqu [rbp+0x654],xmm0                       
66d35d3  mov dword ptr [rbp+0x664],0x3F800000          
66d35dd  movdqu [rbp+0x668],xmm0                       
66d35e5  mov dword ptr [rbp+0x678],0x3F800000          
66d35ef  movdqu [rbp+0x67C],xmm0                       
```
`//` [V] Phase 10: float-struct init continues with movdqu: [rbp+0x4E8]=0, [rbp+0x4F8]=1.0f, [rbp+0x4FC]=0, [rbp+0x50C]=xmm1=[0xEFD3400], [rbp+0x514]=0, [rbp+0x524]=1.0f, [rbp+0x528]=0, [rbp+0x538]=1.0f, [rbp+0x53C]=0, [rbp+0x54C]=xmm1, [rbp+0x554]=0, [rbp+0x564]=1.0f, [rbp+0x568]=0, [rbp+0x578]=1.0f, [rbp+0x57C]=0, [rbp+0x58C]=xmm1, [rbp+0x594]=0, [rbp+0x5A4]=1.0f, [rbp+0x5A8]=0, [rbp+0x5B8]=1.0f, [rbp+0x5BC]=0, [rbp+0x5CC]=xmm1, [rbp+0x5D4]=0, [rbp+0x5E4]=1.0f, [rbp+0x5E8]=0, [rbp+0x5F8]=1.0f, [rbp+0x5FC]=0, [rbp+0x60C]=xmm1, [rbp+0x614]=0, [rbp+0x624]=1.0f, [rbp+0x628]=0, [rbp+0x638]=1.0f, [rbp+0x63C]=0, [rbp+0x64C]=xmm1, [rbp+0x654]=0, [rbp+0x664]=1.0f, [rbp+0x668]=0, [rbp+0x678]=1.0f, [rbp+0x67C]=0 (ends phase) [V]. Same 0x14-stride pattern as phase 4: dword 1.0f at block starts, xmm1 at 0x50C/0x54C/0x58C/0x60C/0x64C, zeros elsewhere [V]. [I]: one big float-param block at [rbp+0x4D0..] being default-initialized; phase 9/10 together span [rbp+0x4D0..~0x688].

## Phase 11 — 0x66d35f7, 40 instructions [V]
```
66d35f7  movq [rbp+0x68C],xmm1                         
66d35ff  movdqu [rbp+0x694],xmm0                       
66d3607  mov dword ptr [rbp+0x6A4],0x3F800000          
66d3611  movdqu [rbp+0x6A8],xmm0                       
66d3619  mov dword ptr [rbp+0x6B8],0x3F800000          
66d3623  movdqu [rbp+0x6BC],xmm0                       
66d362b  mov dword ptr [rbp+0x6CC],0x3F800000          
66d3635  mov qword ptr [rbp+0xA50],8                   
66d3640  lea rax,[rbp+0x4D0]                           
66d3647  mov [rbp+0xA58],rax                           
66d364e  mov rax,[rbp+0xD18]                           
66d3655  movzx r8d,word ptr [rbp+0xD22]                
66d365d  mov edx,r8d                                   
66d3660  shl edx,4                                     
66d3663  mov rcx,rax                                   
66d3666  test r8d,r8d                                  
66d3669  je 0x66D4BD8                                  ; -> loc_66d4bd8
66d366f  mov r8,[0x129F8310]                           ; [data_129f8310]
66d3676  mov r9,rdx                                    
66d3679  mov rcx,rax                                   

loc_66d367c:  ; from 66d3691
  66d367c  mov r10,[rcx]                                 
  66d367f  cmp [r10+0x28],r8                             
  66d3683  je 0x66D4BD8                                  ; -> loc_66d4bd8
  66d3689  add rcx,0x10                                  
  66d368d  add r9,0xFFFFFFFFFFFFFFF0                     
  66d3691  jne short 0x66D367C                           ; -> loc_66d367c
  66d3693  jmp 0x66D4C0E                                 ; -> loc_66d4c0e
  66d3698  mov rax,[rbp+0xD78]                           
  66d369f  mov [rsp+0x40],rax                            
  66d36a4  mov [rsp+0x38],bl                             
  66d36a8  mov eax,[rbp+0xD68]                           
  66d36ae  mov [rsp+0x30],al                             
  66d36b2  mov eax,[rbp+0xD6C]                           
  66d36b8  mov [rsp+0x28],al                             
  66d36bc  lea rax,[rbp+0x75C]                           
  66d36c3  mov [rsp+0x20],rax                            
  66d36c8  lea r9,[rbp+0xCE0]                            
  66d36cf  mov rcx,[rbp+0xD70]                           
  66d36d6  mov r8,rdi                                    
  66d36d9  call 0x66B2DE0                                ; -> sub_66b2de0
```
`//` [V] Phase 11: float init ends: [rbp+0x68C]=xmm1, [rbp+0x694]=0, [rbp+0x6A4]=1.0f, [rbp+0x6A8]=0, [rbp+0x6B8]=1.0f, [rbp+0x6BC]=0, [rbp+0x6CC]=1.0f — block [rbp+0x4D0..~0x6D8] fully initialized [V]. [rbp+0xA50]=8 (value size); [rbp+0xA58]=&rbp+0x4D0 (value ptr = float block) [V]. rax=[rbp+0xD18]; r8d=[rbp+0xD22] count; edx=r8d<<4; rcx=rax; if count==0 →0x66d4bd8 [V]; else key r8=[0x129F8310]; r9=rdx; 0x10-stride scan loop 0x66d367c: r10=[rcx]; cmp [r10+0x28],r8; je 0x66d4bd8; rcx+=0x10; r9-=0x10 jne; no match →jmp 0x66d4c0e [V]. loc_66d3698 (from phase-8 `je 0x66d3698` when byte [rbp+0xCD8+0x75]==0): rax=[rbp+0xD78]; stack block: [rsp+0x40]=rax, [rsp+0x38]=bl, [rsp+0x30]=byte [rbp+0xD68], [rsp+0x28]=byte [rbp+0xD6C], [rsp+0x20]=&rbp+0x75C; r9=&rbp+0xCE0; rcx=[rbp+0xD70]; r8=rdi; call 0x66B2DE0(r8=rdi, rcx=[rbp+0xD70], r9=&rbp+0xCE0) [V] (new callee; 3rd 0x66B2* callee after 0x66B2B30). [I]: float block becomes the value struct; table scan key [0x129F8310]; stack struct passed to 0x66B2DE0.

## Phase 12 — 0x66d36de, 40 instructions [V]
```
66d36de  nop                                           
66d36df  jmp 0x66D6108                                 ; -> sub_66d6108
66d36e4  add r8,rax                                    
66d36e7  lea r9,[rax+rcx]                              
66d36eb  cmp r8,r9                                     
66d36ee  jae short 0x66D3734                           ; -> loc_66d3734
66d36f0  sub r8d,eax                                   
66d36f3  shr r8d,4                                     
66d36f7  mov [rbp+0x7E0],r8w                           
66d36ff  mov byte ptr [rbp+0x7E2],1                    
66d3706  lea rdx,[rbp+0x7E0]                           
66d370d  lea r8,[rbp+0xA50]                            
66d3714  lea rcx,[rbp+0xCE8]                           
66d371b  call 0x56D56A0                                ; -> sub_56d56a0
66d3720  nop                                           
66d3721  mov rax,[rbp+0xD18]                           
66d3728  movzx edx,word ptr [rbp+0xD22]                
66d372f  mov ecx,edx                                   
66d3731  shl ecx,4                                     

loc_66d3734:  ; from 66d36ee
  66d3734  movss xmm0,[rdi+0x88]                         
  66d373c  movq xmm1,[0xEFD32F0]                         ; [data_efd32f0]
  66d3744  movq [rbp+0xA50],xmm1                         
  66d374c  movss [rbp+0xA58],xmm0                        
  66d3754  mov dword ptr [rbp+0xA5C],0                   
  66d375e  mov qword ptr [rbp+0x7E0],1                   
  66d3769  lea r8,[rbp+0xA50]                            
  66d3770  mov [rbp+0x7E8],r8                            
  66d3777  mov r8,rax                                    
  66d377a  test dx,dx                                    
  66d377d  je short 0x66D37A5                            ; -> loc_66d37a5
  66d377f  mov rdx,[0x129F8350]                          ; [data_129f8350]
  66d3786  mov r9,rcx                                    
  66d3789  mov r8,rax                                    
  66d378c  nop [rax]                                     

loc_66d3790:  ; from 66d37a1
  66d3790  mov r10,[r8]                                  
  66d3793  cmp [r10+0x28],rdx                            
  66d3797  je short 0x66D37A5                            ; -> loc_66d37a5
  66d3799  add r8,0x10                                   
  66d379d  add r9,0xFFFFFFFFFFFFFFF0                     
  66d37a1  jne short 0x66D3790                           ; -> loc_66d3790
```
`//` [V] Phase 12 closes the 0x30-stride (index [rbp+0x7E0]) table-scan match path: `add r8,rax; lea r9,[rax+rcx]; cmp r8,r9; jae 0x66d3734` ends index math; else `sub r8d,eax; shr r8d,4` → index→[rbp+0x7E0]; byte [rbp+0x7E2]=1; call 0x56D56A0(rdx=&rbp+0x7E0, r8=&rbp+0xA50, rcx=&rbp+0xCE8) [V] — new callee, the [rbp+0x7E0]-slot variant of the 0x5679DB0 pattern. loc_66d3734 (joined by `jae`, phase-6 `jmp 0x66d3734`, phase-6 `dx=1`): value struct from obj — movss xmm0=[rdi+0x88]; movq xmm1=[0xEFD32F0]; [rbp+0xA50]=xmm1 (qword const); movss [rbp+0xA58]=xmm0 (dword [rdi+0x88]); [rbp+0xA5C]=0; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V] — same shape as phase-6 value struct, float const [0xEFD32F0] this time. Third 0x10-stride scan: rax=[rbp+0xD18]; r8=rax base; edx=[rbp+0xD22] count; test dx,dx; je 0x66d37a5 if zero; else key rdx=[0x129F8350], r9=rcx end; loop 0x66d3790: r10=[r8]; cmp [r10+0x28],rdx; je 0x66d37a5; r8+=0x10; r9-=0x10 jne [V]. Next address: 0x66d37a5.

## Phase 13 — 0x66d37a5, 40 instructions [V]
```
66d37a5  add rcx,rax                                   
66d37a8  cmp r8,rcx                                    
66d37ab  jae short 0x66D37DE                           ; -> loc_66d37de
66d37ad  sub r8d,eax                                   
66d37b0  shr r8d,4                                     
66d37b4  mov [rbp+0x208],r8w                           
66d37bc  mov byte ptr [rbp+0x20A],1                    
66d37c3  lea rdx,[rbp+0x208]                           
66d37ca  lea r8,[rbp+0x7E0]                            
66d37d1  lea rcx,[rbp+0xCE8]                           
66d37d8  call 0x5679DB0                                ; -> sub_5679db0
66d37dd  nop                                           

loc_66d37de:  ; from 66d37ab
  66d37de  test dword ptr [rbp+0xD90],0x2000             
  66d37e8  je 0x66D389B                                  ; -> loc_66d389b
  66d37ee  movups xmm0,[rdi+0xB4]                        
  66d37f5  shufps xmm0,xmm0,0                            
  66d37f9  movaps [rbp+0xA50],xmm0                       
  66d3800  mov qword ptr [rbp+0x7E0],1                   
  66d380b  lea rax,[rbp+0xA50]                           
  66d3812  mov [rbp+0x7E8],rax                           
  66d3819  mov rax,[rbp+0xD18]                           
  66d3820  movzx r8d,word ptr [rbp+0xD22]                
  66d3828  mov edx,r8d                                   
  66d382b  shl edx,4                                     
  66d382e  mov rcx,rax                                   
  66d3831  test r8d,r8d                                  
  66d3834  je short 0x66D3865                            ; -> loc_66d3865
  66d3836  mov r8,[0x129F8358]                           ; [data_129f8358]
  66d383d  mov r9,rdx                                    
  66d3840  mov rcx,rax                                   
  66d3843  nop [rax+rax]                                 

loc_66d3850:  ; from 66d3861
  66d3850  mov r10,[rcx]                                 
  66d3853  cmp [r10+0x28],r8                             
  66d3857  je short 0x66D3865                            ; -> loc_66d3865
  66d3859  add rcx,0x10                                  
  66d385d  add r9,0xFFFFFFFFFFFFFFF0                     
  66d3861  jne short 0x66D3850                           ; -> loc_66d3850
  66d3863  jmp short 0x66D389B                           ; -> loc_66d389b

loc_66d3865:  ; from 66d3834, 66d3857
  66d3865  add rdx,rax                                   
  66d3868  cmp rcx,rdx                                   
```
`//` [V] Phase 13 closes phase-12's third 0x10-stride scan: `add rcx,rax; cmp r8,rcx; jae 0x66d37de` ends scan; match-end `sub r8d,eax; shr r8d,4` → index→[rbp+0x208]; byte [rbp+0x20A]=1; call 0x5679DB0(rdx=&rbp+0x208, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] — index now lands at [rbp+0x208] (new slot, not [rbp+0x4D0]/[rbp+0x7E0]). loc_66d37de: test dword [rbp+0xD90],0x2000; je 0x66d389b [V]; else value = broadcast float [rdi+0xB4]: movups/shufps/movaps [rbp+0xA50]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]. Fourth 0x10-stride scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx=r8d<<4; rcx=rax; je 0x66d3865 if count==0; else key r8=[0x129F8358] (33rd global); loop 0x66d3850: r10=[rcx]; cmp [r10+0x28],r8; je 0x66d3865; rcx+=0x10; r9-=0x10 jne; no match →jmp 0x66d389b [V]. Match-end 0x66d3865: add rdx,rax; cmp rcx,rdx (continues phase 14). Next address: 0x66d386b.

## Phase 14 — 0x66d386b, 40 instructions [V]
```
66d386b  jae short 0x66D389B                           ; -> loc_66d389b
66d386d  sub ecx,eax                                   
66d386f  shr ecx,4                                     
66d3872  mov [rbp+0x208],cx                            
66d3879  mov byte ptr [rbp+0x20A],1                    
66d3880  lea rdx,[rbp+0x208]                           
66d3887  lea r8,[rbp+0x7E0]                            
66d388e  lea rcx,[rbp+0xCE8]                           
66d3895  call 0x5679DB0                                ; -> sub_5679db0
66d389a  nop                                           

loc_66d389b:  ; from 66d386b
  66d389b  mov eax,[0x129F8F70]                          ; [data_129f8f70]
  66d38a1  mov ecx,[0x128767C8]                          ; [data_128767c8]
  66d38a7  mov rdx,gs:[0x58]                             
  66d38b0  mov rcx,[rdx+rcx*8]                           
  66d38b4  cmp eax,[rcx+4]                               
  66d38ba  jg 0x66D6ADD                                  ; -> sub_66d6add
  66d38c0  movaps xmm0,[0xEF40DE0]                       ; [data_ef40de0]
  66d38c7  movaps [rbp+0xA50],xmm0                       
  66d38ce  mov qword ptr [rbp+0x7E0],1                   
  66d38d9  lea rax,[rbp+0xA50]                           
  66d38e0  mov [rbp+0x7E8],rax                           
  66d38e7  mov rax,[rbp+0xD18]                           
  66d38ee  movzx r8d,word ptr [rbp+0xD22]                
  66d38f6  mov edx,r8d                                   
  66d38f9  shl edx,4                                     
  66d38fc  mov rcx,rax                                   
  66d38ff  test r8d,r8d                                  
  66d3902  je short 0x66D3935                            ; -> loc_66d3935
  66d3904  mov r8,[0x129F8F68]                           ; [data_129f8f68]
  66d390b  mov r9,rdx                                    
  66d390e  mov rcx,rax                                   
  66d3911  nop [rax+rax]                                 

loc_66d3920:  ; from 66d3931
  66d3920  mov r10,[rcx]                                 
  66d3923  cmp [r10+0x28],r8                             
  66d3927  je short 0x66D3935                            ; -> loc_66d3935
  66d3929  add rcx,0x10                                  
  66d392d  add r9,0xFFFFFFFFFFFFFFF0                     
  66d3931  jne short 0x66D3920                           ; -> loc_66d3920
  66d3933  jmp short 0x66D396B                           ; -> loc_66d396b

loc_66d3935:  ; from 66d3902, 66d3927
  66d3935  add rdx,rax                                   
```
`//` [V] Phase 14 closes phase-13's fourth 0x10-stride scan match-end: `jae 0x66d389b` ends scan; else `sub ecx,eax; shr ecx,4` → index→[rbp+0x208]; byte [rbp+0x20A]=1; call 0x5679DB0(rdx=&rbp+0x208, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (41st call-0x5679DB0). loc_66d389b: TLS gate — eax=[0x129F8F70]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d6add (new fallback) [V]. Value = movaps xmm0=[0xEF40DE0]; [rbp+0xA50]=xmm0; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]. Fifth 0x10-stride scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx=r8d<<4; rcx=rax; je 0x66d3935 if count==0; else key r8=[0x129F8F68] (34th global); loop 0x66d3920: r10=[rcx]; cmp [r10+0x28],r8; je 0x66d3935; rcx+=0x10; r9-=0x10 jne; no match →jmp 0x66d396b [V]. Match-end 0x66d3935: add rdx,rax (continues phase 15). Next address: 0x66d3938.

## Phase 15 — 0x66d3938, 40 instructions [V]
```
66d3938  cmp rcx,rdx                                   
66d393b  jae short 0x66D396B                           ; -> loc_66d396b
66d393d  sub ecx,eax                                   
66d393f  shr ecx,4                                     
66d3942  mov [rbp+0x208],cx                            
66d3949  mov byte ptr [rbp+0x20A],1                    
66d3950  lea rdx,[rbp+0x208]                           
66d3957  lea r8,[rbp+0x7E0]                            
66d395e  lea rcx,[rbp+0xCE8]                           
66d3965  call 0x5679DB0                                ; -> sub_5679db0
66d396a  nop                                           

loc_66d396b:  ; from 66d393b
  66d396b  mov eax,[rbp+0xD68]                           
  66d3971  xor al,1                                      
  66d3973  movzx eax,al                                  
  66d3976  lea eax,[rax+rax*2]                           
  66d3979  cmp byte ptr [rbp+0xD6C],0                    
  66d3980  mov ecx,1                                     
  66d3985  cmove ecx,eax                                 
  66d3988  mov [rbp+0x758],ecx                           
  66d398e  mov rdx,[rbp+0xCD8]                           
  66d3995  mov [rbp+0x420],rdx                           
  66d399c  mov rax,[rbp+0xD70]                           
  66d39a3  mov [rbp+0x428],rax                           
  66d39aa  mov [rbp+0x430],rbx                           
  66d39b1  lea rax,[rbp+0x754]                           
  66d39b8  mov [rbp+0x438],rax                           
  66d39bf  mov [rbp+0x440],rdi                           
  66d39c6  lea rax,[rbp+0xCE0]                           
  66d39cd  mov [rbp+0x448],rax                           
  66d39d4  mov [rbp+0x450],r13                           
  66d39db  lea rax,[rbp+0x758]                           
  66d39e2  mov [rbp+0x458],rax                           
  66d39e9  mov r14,[rdi]                                 
  66d39ec  movzx eax,byte ptr [r14+0x1B0]                
  66d39f4  cmp rax,3                                     
  66d39f8  ja 0x66D72A0                                  ; -> sub_66d72a0
  66d39fe  lea rcx,[0xF2BFB00]                           ; [data_f2bfb00]
  66d3a05  movsxd rax,[rcx+rax*4]                        
  66d3a09  add rax,rcx                                   
  66d3a0c  jmp rax                                       
```
`//` [V] Phase 15 closes phase-14's fifth 0x10-stride scan match-end: cmp rcx,rdx; jae 0x66d396b ends scan; else index→[rbp+0x208]; call 0x5679DB0(rdx=&rbp+0x208, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (42nd call-0x5679DB0). loc_66d396b: ecx=([rbp+0xD68]^1)*3; if byte [rbp+0xD6C]==0 →ecx=eax else 1 via cmove; [rbp+0x758]=ecx [V]. Context struct built at [rbp+0x420..0x458]: [0x420]=[rbp+0xCD8], [0x428]=[rbp+0xD70], [0x430]=rbx, [0x438]=&rbp+0x754, [0x440]=rdi, [0x448]=&rbp+0xCE0, [0x450]=r13, [0x458]=&rbp+0x758 [V]. Switch on byte [r14+0x1B0] (r14=[rdi]): if >3 →0x66d72a0; else jump table at [0xF2BFB00]: movsxd rax,[rcx+rax*4]; rax+=rcx; jmp rax (4 entries) [V]. Next address: 0x66d3a0e.

## Phase 16 — 0x66d3a0e, 40 instructions [V]
```
66d3a0e  mov rsi,rdx                                   
66d3a11  lea rcx,[rbp+0x420]                           
66d3a18  lea rdx,[rbp+0x7E0]                           
66d3a1f  call 0x67612A0                                ; -> sub_67612a0
66d3a24  nop                                           
66d3a25  mov rsi,[rsi+0x10]                            ; R a1+0x10
66d3a29  lea rax,[0xF2BE878]                           ; [data_f2be878]
66d3a30  mov [rbp+0xA50],rax                           
66d3a37  lea rdi,[rbp+0xA58]                           
66d3a3e  lea rdx,[rbp+0x7E0]                           
66d3a45  mov rcx,rdi                                   
66d3a48  call 0x6761590                                ; -> sub_6761590
66d3a4d  nop                                           
66d3a4e  lea r9,[rbp+0xC08]                            
66d3a55  mov eax,[rbp+0x990]                           
66d3a5b  mov [rbp+0xC08],eax                           
66d3a61  lea r8,[rbp+0xC10]                            
66d3a68  movzx eax,word ptr [rbp+0x998]                
66d3a6f  mov [rbp+0xC10],ax                            
66d3a76  lea rdx,[rbp+0xC18]                           
66d3a7d  movzx eax,word ptr [rbp+0x9A0]                
66d3a84  mov [rbp+0xC18],ax                            
66d3a8b  movzx eax,byte ptr [rbp+0x9A8]                
66d3a92  mov [rbp+0xC20],al                            
66d3a98  movzx eax,byte ptr [rbp+0x9B0]                
66d3a9f  mov [rbp+0xC28],al                            
66d3aa5  add rsi,0x9D0                                 
66d3aac  lea rax,[rbp+0xAB0]                           
66d3ab3  lea rcx,[rbp+0xAF8]                           
66d3aba  lea r10,[rbp+0xB28]                           
66d3ac1  lea r11,[rbp+0xBB0]                           
66d3ac8  mov [rsp+0x40],rdi                            
66d3acd  mov [rsp+0x38],rax                            
66d3ad2  mov [rsp+0x30],rcx                            
66d3ad7  mov [rsp+0x28],r10                            
66d3adc  mov [rsp+0x20],r11                            
66d3ae1  mov rcx,rsi                                   
66d3ae4  call 0x6761970                                ; -> sub_6761970
66d3ae9  nop                                           
66d3aea  jmp 0x66D3BCB                                 ; -> loc_66d3bcb
```
`//` [V] Phase 16 (jump-table entry): rsi=rdx (table target); call 0x67612A0(rcx=&rbp+0x420 ctx struct, rdx=&rbp+0x7E0, rsi=target) [V] new callee; nop; rsi=[rsi+0x10]; [rbp+0xA50]=0xF2BE878 (qword addr); rdi=&rbp+0xA58; rdx=&rbp+0x7E0; rcx=rdi; call 0x6761590(rcx=&rbp+0xA58, rdx=&rbp+0x7E0) [V] new callee; nop; copy [rbp+0x990..0x9B0] dword/word/byte fields →[rbp+0xC08..0xC28] [V]; rsi+=0x9D0; stack frame [rsp+0x20..0x40] = {&rbp+0xBB0, &rbp+0xB28, &rbp+0xAF8, &rbp+0xAB0, rdi}; rcx=rsi; call 0x6761970(rcx=rsi+0x9D0, r9=&rbp+0xC08) [V] new callee; nop; jmp 0x66d3bcb [V]. Next address: 0x66d3aef.

## Phase 17 — 0x66d3aef, 40 instructions [V]
```
66d3aef  mov rsi,rdx                                   
66d3af2  lea rcx,[rbp+0x420]                           
66d3af9  lea rdx,[rbp+0x7E0]                           
66d3b00  call 0x67612A0                                ; -> sub_67612a0
66d3b05  nop                                           
66d3b06  mov rsi,[rsi+0x10]                            ; R a1+0x10
66d3b0a  lea rax,[0xF2BE878]                           ; [data_f2be878]
66d3b11  mov [rbp+0xA50],rax                           
66d3b18  lea rdi,[rbp+0xA58]                           
66d3b1f  lea rdx,[rbp+0x7E0]                           
66d3b26  mov rcx,rdi                                   
66d3b29  call 0x6761590                                ; -> sub_6761590
66d3b2e  nop                                           
66d3b2f  lea r9,[rbp+0xC08]                            
66d3b36  mov eax,[rbp+0x990]                           
66d3b3c  mov [rbp+0xC08],eax                           
66d3b42  lea r8,[rbp+0xC10]                            
66d3b49  movzx eax,word ptr [rbp+0x998]                
66d3b50  mov [rbp+0xC10],ax                            
66d3b57  lea rdx,[rbp+0xC18]                           
66d3b5e  movzx eax,word ptr [rbp+0x9A0]                
66d3b65  mov [rbp+0xC18],ax                            
66d3b6c  movzx eax,byte ptr [rbp+0x9A8]                
66d3b73  mov [rbp+0xC20],al                            
66d3b79  movzx eax,byte ptr [rbp+0x9B0]                
66d3b80  mov [rbp+0xC28],al                            
66d3b86  add rsi,0x9D0                                 
66d3b8d  lea rax,[rbp+0xAB0]                           
66d3b94  lea rcx,[rbp+0xAF8]                           
66d3b9b  lea r10,[rbp+0xB28]                           
66d3ba2  lea r11,[rbp+0xBB0]                           
66d3ba9  mov [rsp+0x40],rdi                            
66d3bae  mov [rsp+0x38],rax                            
66d3bb3  mov [rsp+0x30],rcx                            
66d3bb8  mov [rsp+0x28],r10                            
66d3bbd  mov [rsp+0x20],r11                            
66d3bc2  mov rcx,rsi                                   
66d3bc5  call 0x6761970                                ; -> sub_6761970
66d3bca  nop                                           
66d3bcb  lea rax,[0xF2BE878]                           ; [data_f2be878]
```
`//` [V] Phase 17: duplicate tail path of phase 16 (reached via fall-through into loc_66d3bcb): call 0x67612A0(rcx=&rbp+0x420, rdx=&rbp+0x7E0, rsi=rdx) [V]; rsi=[rsi+0x10]; [rbp+0xA50]=0xF2BE878; call 0x6761590(rcx=&rbp+0xA58, rdx=&rbp+0x7E0) [V]; copy [rbp+0x990..0x9B0] →[rbp+0xC08..0xC28] [V]; rsi+=0x9D0; stack frame [rsp+0x20..0x40]; call 0x6761970(rcx=rsi+0x9D0, r9=&rbp+0xC08) [V]; nop; lea rax,[0xF2BE878] (continues phase 18). Next address: 0x66d3bd2.

## Phase 18 — 0x66d3bd2, 40 instructions [V]
```
66d3bd2  mov [rbp+0xA50],rax                           
66d3bd9  lea rcx,[rbp+0xA58]                           
66d3be0  call 0x67627D0                                ; -> sub_67627d0
66d3be5  lea rcx,[rbp+0x7E0]                           
66d3bec  call 0x67627D0                                ; -> sub_67627d0
66d3bf1  jmp 0x66D6108                                 ; -> sub_66d6108
66d3bf6  mov byte ptr [rbp+0xD8E],0                    
66d3bfd  mov word ptr [rbp+0xD8C],0                    
66d3c06  xorps xmm0,xmm0                               
66d3c09  movaps [rbp+0x760],xmm0                       
66d3c10  mov esi,[r14+0x198]                           
66d3c17  mov r15d,[r14+0x19C]                          
66d3c1e  mov rdi,[rdx+0x48]                            
66d3c22  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
66d3c29  mov rax,[rcx]                                 
66d3c2c  mov rax,[rax+8]                               
66d3c30  mov edx,0x30                                  
66d3c35  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d3c3b  nop                                           
66d3c3c  mov rbx,rax                                   
66d3c3f  test rax,rax                                  
66d3c42  je 0x66D6187                                  ; -> sub_66d6187
66d3c48  movups xmm0,[0xF5C6AE8]                       ; [data_f5c6ae8] "eCapture texture"
66d3c4f  movups [rbx+0x10],xmm0                        
66d3c53  movups xmm0,[0xF5C6AD8]                       ; [data_f5c6ad8] "UIStructureVolumeCapture texture"
66d3c5a  movups [rbx],xmm0                             
66d3c5d  mov byte ptr [rbx+0x20],0                     
66d3c61  mov [rbp+0xA50],esi                           
66d3c67  mov [rbp+0xA54],r15d                          
66d3c6e  mov dword ptr [rbp+0xA58],0x1C                
66d3c78  movzx eax,word ptr [rbp+0xD8C]                
66d3c7f  mov [rbp+0xA5C],ax                            
66d3c86  movzx eax,byte ptr [rbp+0xD8E]                
66d3c8d  mov [rbp+0xA5E],al                            
66d3c93  mov r12,0x100000001                           
66d3c9d  mov [rbp+0xA60],r12                           
66d3ca4  mov [rbp+0xA68],rbx                           
66d3cab  mov qword ptr [rbp+0xA70],0                   
66d3cb6  mov qword ptr [rbp+0xA78],0x20                
66d3cc1  mov qword ptr [rbp+0xA80],0x2F                
```
`//` [V] Phase 18: loc_66d3bd2 (from lea rax,[0xF2BE878]): [rbp+0xA50]=rax; call 0x67627D0(rcx=&rbp+0xA58) [V] new callee; call 0x67627D0(rcx=&rbp+0x7E0) [V] 2nd call; jmp 0x66d6108 [V] fallback. loc_66d3bf6: [rbp+0xD8E]=0; [rbp+0xD8C]=0; [rbp+0x760]=0 [V]. esi=[r14+0x198]; r15d=[r14+0x19C]; rdi=[rdx+0x48] [V]. Heap alloc: rcx=[0x1233E1A8]; rax=[rcx]; rax=[rax+8]; edx=0x30; rbx=call qword ptr [0xF99FFA0](=sub_eea6040) [V]; je 0x66d6187 if null [V]. Object init: movups [rbx+0x10]=[0xF5C6AE8] ("eCapture texture"); movups [rbx]=[0xF5C6AD8] ("UIStructureVolumeCapture texture"); byte [rbx+0x20]=0 [V] (rodata strings cited as data). Value struct at [rbp+0xA50..0xA80]: [0xA50]=esi, [0xA54]=r15d, [0xA58]=0x1C, [0xA5C]=[rbp+0xD8C], [0xA5E]=[rbp+0xD8E], [0xA60]=0x100000001, [0xA68]=rbx (alloc obj), [0xA70]=0, [0xA78]=0x20, [0xA80]=0x2F [V]. Next address: 0x66d3cc8.

## Phase 19 — 0x66d3cca, 40 instructions [V] (restarted at 0x66d3cca after 1-byte `(bad)` pad at 0x66d3cc8)
```
66d3cca  add [rax],al                                  
66d3ccc  lea rdx,[rbp+0x7E0]                           
66d3cd3  lea r8,[rbp+0xA50]                            
66d3cda  mov rcx,rdi                                   
66d3cdd  call 0x5AB9970                                ; -> sub_5ab9970
66d3ce2  nop                                           
66d3ce3  mov rbx,[rbp+0x7E0]                           
66d3cea  mov r13,[rbp+0x7E8]                           
66d3cf1  xorps xmm0,xmm0                               
66d3cf4  movaps [rbp+0x7E0],xmm0                       
66d3cfb  mov [rbp+0x760],rbx                           
66d3d02  mov [rbp+0x768],r13                           
66d3d09  mov rax,[rbp+0xA80]                           
66d3d10  cmp rax,0x10                                  
66d3d14  jb short 0x66D3D4F                            ; -> loc_66d3d4f
66d3d16  mov rcx,[rbp+0xA68]                           
66d3d1d  lea rdx,[rax+1]                               
66d3d21  cmp rdx,0x1000                                
66d3d28  jb short 0x66D3D49                            ; -> loc_66d3d49
66d3d2a  mov r8,[rcx-8]                                
66d3d2e  add rcx,0xFFFFFFFFFFFFFFF8                    
66d3d32  sub rcx,r8                                    
66d3d35  cmp rcx,0x20                                  
66d3d39  jae 0x66D2D40                                 ; -> sub_66d2d40
66d3d3f  add rax,0x28                                  
66d3d43  mov rdx,rax                                   
66d3d46  mov rcx,r8                                    

loc_66d3d49:  ; from 66d3d28
  66d3d49  call 0xE935700                                ; -> sub_e935700
  66d3d4e  nop                                           

loc_66d3d4f:  ; from 66d3d14
  66d3d4f  lea rcx,[rbp+0x420]                           
  66d3d56  lea rdi,[rbp+0x208]                           
  66d3d5d  mov rdx,rdi                                   
  66d3d60  call 0x6762900                                ; -> sub_6762900
  66d3d65  nop                                           
  66d3d66  xorps xmm0,xmm0                               
  66d3d69  movaps [rbp+0x7B0],xmm0                       
  66d3d70  test r13,r13                                  
  66d3d73  je 0x66D438E                                  ; -> loc_66d438e
  66d3d79  lock inc dword ptr [r13+8]                    
```
`//` [V] Phase 19: 1-byte `(bad)` pad at 0x66d3cc8 — phase restarted at 0x66d3cca per convention. `add [rax],al` at 0x66d3cca (end of prior fall-through/pad) [V]. `call 0x5AB9970(rcx=rdi, rdx=&rbp+0x7E0, r8=&rbp+0xA50)` [V] new callee; rbx=[rbp+0x7E0], r13=[rbp+0x7E8] (value pair) [V]. [rbp+0x7E0]=0; [rbp+0x760]=rbx; [rbp+0x768]=r13 — save slot. rax=[rbp+0xA80] (=0x2F); if <0x10 →0x66d3d4f; else heap block check: rcx=[rbp+0xA68]; rdx=rax+1; if <0x1000 →0x66d3d49 `call 0xE935700`; else `r8=[rcx-8]; rcx-=8; rcx-=r8; cmp rcx,0x20; jae 0x66d2d40` shared free block; else `add rax,0x28; rdx=rax; rcx=r8` →0x66d3d49 [V] (free the 0x2F-sized block). loc_66d3d4f: call 0x6762900(rcx=&rbp+0x420 ctx, rdx=&rbp+0x208) [V] new callee; [rbp+0x7B0]=0; if r13==0 →0x66d438e; else `lock inc dword ptr [r13+8]` (refcount bump) [V] — continues phase 20. Next address: 0x66d3d7f.

## Phase 20 — 0x66d3d7f, 40 instructions [V]
```
66d3d7f  mov ebx,[rbp+0x760]                           
66d3d85  mov rax,[rbp+0x768]                           
66d3d8c  jmp 0x66D4390                                 ; -> loc_66d4390
66d3d91  mov rax,[rdx+0x10]                            ; R a1+0x10
66d3d95  mov [rbp+0xD90],rax                           
66d3d9c  mov rax,[rbp+0xD70]                           
66d3da3  mov rcx,[rax+0x470]                           
66d3daa  mov rax,[rcx]                                 
66d3dad  mov rax,[rax+0x48]                            
66d3db1  lea rdx,[rbp+0x760]                           
66d3db8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d3dbe  nop                                           
66d3dbf  mov rsi,[r14+0x198]                           
66d3dc6  mov byte ptr [rbp+0x474],0xF                  
66d3dcd  lea rcx,[rbp+0x420]                           
66d3dd4  lea rdi,[rbp+0x208]                           
66d3ddb  mov rdx,rdi                                   
66d3dde  call 0x6762900                                ; -> sub_6762900
66d3de3  nop                                           
66d3de4  xorps xmm0,xmm0                               
66d3de7  movaps [rbp+0x7B0],xmm0                       
66d3dee  mov rax,[rsi+8]                               
66d3df2  test rax,rax                                  
66d3df5  je short 0x66D3E0C                            ; -> loc_66d3e0c
66d3df7  mov rcx,[rsi]                                 
66d3dfa  mov [rbp+0x7B0],rcx                           
66d3e01  mov [rbp+0x7B8],rax                           
66d3e08  lock inc dword ptr [rax+0xC]                  

loc_66d3e0c:  ; from 66d3df5
  66d3e0c  movups xmm0,[rsi+0x10]                        
  66d3e10  movaps [rbp+0x7C0],xmm0                       
  66d3e17  lea r8,[rbp+0x7D0]                            
  66d3e1e  lea rax,[rbp+0x780]                           
  66d3e25  mov [rbp+0x770],rax                           
  66d3e2c  mov r13,0x100000000                           
  66d3e36  mov [rbp+0x778],r13                           
  66d3e3d  lea rcx,[rbp+0x770]                           
  66d3e44  lea rdx,[rbp+0x7B0]                           
  66d3e4b  call 0x6765C00                                ; -> sub_6765c00
  66d3e50  nop                                           
  66d3e51  lea r15,[rbp+0x6E0]                           
```
`//` [V] Phase 20: ebx=[rbp+0x760]; rax=[rbp+0x768]; jmp 0x66d4390 [V]. Linear sweep continues past jmp (likely jump-table target block): rax=[rdx+0x10]; [rbp+0xD90]=rax; rax=[rbp+0xD70]; rcx=[rax+0x470]; rax=[rcx]; rax=[rax+0x48]; call qword ptr [0xF99FFA0](=sub_eea6040, rdx=&rbp+0x760) [V] alloc; nop; rsi=[r14+0x198]; byte [rbp+0x474]=0xF; call 0x6762900(rcx=&rbp+0x420, rdx=&rbp+0x208) [V] (2nd call). [rbp+0x7B0]=0; rax=[rsi+8]; test rax,rax; je 0x66d3e0c; else [rbp+0x7B0]=[rsi]; [rbp+0x7B8]=rax; lock inc dword ptr [rax+0xC] (refcount) [V]. loc_66d3e0c: [rbp+0x7C0]=[rsi+0x10] (movups); [rbp+0x770]=&rbp+0x780; [rbp+0x778]=0x100000000 (qword); call 0x6765C00(rcx=&rbp+0x770, rdx=&rbp+0x7B0) [V] new callee; nop; r15=&rbp+0x6E0 (continues phase 21). Next address: 0x66d3e58.

## Phase 21 — 0x66d3e58, 40 instructions [V]
```
66d3e58  mov [rbp+0x6D0],r15                           
66d3e5f  mov [rbp+0x6D8],r13                           
66d3e66  lea rbx,[rbp+0x6D0]                           
66d3e6d  lea rdx,[rbp+0x770]                           
66d3e74  mov rcx,rbx                                   
66d3e77  call 0x6764990                                ; -> sub_6764990
66d3e7c  lea r12,[rbp+0x720]                           
66d3e83  mov [rbp+0x710],r12                           
66d3e8a  mov [rbp+0x718],r13                           
66d3e91  lea rcx,[rbp+0x710]                           
66d3e98  mov rdx,rbx                                   
66d3e9b  call 0x6764990                                ; -> sub_6764990
66d3ea0  lea rdx,[rbp+0x360]                           
66d3ea7  lea r8,[rbp+0x2D8]                            
66d3eae  lea r9,[rbp+0x2A8]                            
66d3eb5  lea rax,[rbp+0x260]                           
66d3ebc  mov [rsp+0x28],rdi                            
66d3ec1  mov [rsp+0x20],rax                            
66d3ec6  lea rcx,[rbp+0xA50]                           
66d3ecd  call 0x6764400                                ; -> sub_6764400
66d3ed2  nop                                           
66d3ed3  mov eax,[rbp+0x3B8]                           
66d3ed9  mov [rbp+0xC00],eax                           
66d3edf  movzx eax,word ptr [rbp+0x3C0]                
66d3ee6  mov [rbp+0xC08],ax                            
66d3eed  movzx eax,word ptr [rbp+0x3C8]                
66d3ef4  mov [rbp+0xC10],ax                            
66d3efb  lea rbx,[rbp+0xC18]                           
66d3f02  lea r14,[rbp+0xC28]                           
66d3f09  mov [rbp+0xC18],r14                           
66d3f10  mov [rbp+0xC20],r13                           
66d3f17  lea rdx,[rbp+0x710]                           
66d3f1e  mov rcx,rbx                                   
66d3f21  call 0x6764990                                ; -> sub_6764990
66d3f26  nop                                           
66d3f27  lea rcx,[rbp+0x7E0]                           
66d3f2e  lea rdx,[rbp+0xA50]                           
66d3f35  call 0x6761590                                ; -> sub_6761590
66d3f3a  nop                                           
66d3f3b  mov eax,[rbp+0xC00]                           
```
`//` [V] Phase 21: [rbp+0x6D0]=r15 (&rbp+0x6E0); [rbp+0x6D8]=r13 (0x100000000); rbx=&rbp+0x6D0; call 0x6764990(rcx=&rbp+0x6D0, rdx=&rbp+0x770) [V] new callee — list link; [rbp+0x710]=r12(&rbp+0x720); [rbp+0x718]=r13; call 0x6764990(rcx=&rbp+0x710, rdx=&rbp+0x6D0) [V] (2nd call, bidirectional link). Call 0x6764400(rcx=&rbp+0xA50, rdx=&rbp+0x360, r8=&rbp+0x2D8, r9=&rbp+0x2A8, [rsp+0x20]=&rbp+0x260, [rsp+0x28]=rdi) [V] new callee (6-arg struct copy). [rbp+0xC00]=[rbp+0x3B8]; [rbp+0xC08]=[rbp+0x3C0]; [rbp+0xC10]=[rbp+0x3C8] [V]. rbx=&rbp+0xC18; r14=&rbp+0xC28; [rbp+0xC18]=r14; [rbp+0xC20]=r13 (self-linked node) [V]. call 0x6764990(rcx=&rbp+0xC18, rdx=&rbp+0x710) [V] (3rd call); call 0x6761590(rcx=&rbp+0x7E0, rdx=&rbp+0xA50) [V] (2nd call, args swapped vs phase 16); eax=[rbp+0xC00] (continues phase 22). Next address: 0x66d3f41.

## Phase 22 — 0x66d3f41, 40 instructions [V]
```
66d3f41  mov [rbp+0x990],eax                           
66d3f47  movzx eax,word ptr [rbp+0xC08]                
66d3f4e  mov [rbp+0x998],ax                            
66d3f55  movzx eax,word ptr [rbp+0xC10]                
66d3f5c  mov [rbp+0x9A0],ax                            
66d3f63  lea rcx,[rbp+0x9A8]                           
66d3f6a  lea rax,[rbp+0x9B8]                           
66d3f71  mov [rbp+0x9A8],rax                           
66d3f78  mov [rbp+0x9B0],r13                           
66d3f7f  mov rdx,rbx                                   
66d3f82  call 0x6764990                                ; -> sub_6764990
66d3f87  mov rbx,[rbp+0xC18]                           
66d3f8e  mov esi,[rbp+0xC20]                           
66d3f94  test rsi,rsi                                  
66d3f97  je short 0x66D3FDF                            ; -> loc_66d3fdf
66d3f99  shl rsi,5                                     
66d3f9d  xor edi,edi                                   
66d3f9f  jmp short 0x66D3FB9                           ; -> loc_66d3fb9
66d3fa1  nop [rax+rax]                                 ; R ret@6764990+0x0+idx

loc_66d3fb0:  ; from 66d3fc1, 66d3fc7, 66d3fd6
  66d3fb0  add rdi,0x20                                  
  66d3fb4  cmp rsi,rdi                                   
  66d3fb7  je short 0x66D3FD8                            ; -> loc_66d3fd8

loc_66d3fb9:  ; from 66d3f9f
  66d3fb9  mov rcx,[rbx+rdi+8]                           
  66d3fbe  test rcx,rcx                                  
  66d3fc1  je short 0x66D3FB0                            ; -> loc_66d3fb0
  66d3fc3  lock dec dword ptr [rcx+0xC]                  
  66d3fc7  jne short 0x66D3FB0                           ; -> loc_66d3fb0
  66d3fc9  mov rax,[rcx]                                 
  66d3fcc  mov rax,[rax+8]                               
  66d3fd0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d3fd6  jmp short 0x66D3FB0                           ; -> loc_66d3fb0

loc_66d3fd8:  ; from 66d3fb7
  66d3fd8  mov rbx,[rbp+0xC18]                           

loc_66d3fdf:  ; from 66d3f97
  66d3fdf  cmp r14,rbx                                   
  66d3fe2  je short 0x66D4001                            ; -> loc_66d4001
  66d3fe4  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  66d3feb  test rbx,rbx                                  
  66d3fee  je short 0x66D4001                            ; -> loc_66d4001
  66d3ff0  mov rax,[rcx]                                 
  66d3ff3  mov rax,[rax+0x10]                            
  66d3ff7  mov rdx,rbx                                   
```
`//` [V] Phase 22: store copied fields back: [rbp+0x990]=eax, [rbp+0x998]=[rbp+0xC08], [rbp+0x9A0]=[rbp+0xC10], [rbp+0x9A8]=[rbp+0x9B8], [rbp+0x9B0]=r13 [V]. call 0x6764990(rdx=rbx, rcx=&rbp+0x9A8) [V] (4th call-0x6764990). Release loop: rbx=[rbp+0xC18]; esi=[rbp+0xC20] count; if 0 →0x66d3fdf; else rsi=esi<<5 (entry stride 0x20); edi=0; loc_66d3fb9: rcx=[rbx+rdi+8]; if rcx==0 →skip; lock dec dword [rcx+0xC]; if nonzero →next; else rax=[rcx]; rax=[rax+8]; call qword ptr [0xF99FFA0](sub_eea6040) free [V]; loc_66d3fb0: rdi+=0x20; if rdi<rsi loop. r14=rdi@loop-boundary... nop [rax+rax] padding at 0x66d3fa1 (ret@6764990+idx annotation) [V]. loc_66d3fd8: rbx=[rbp+0xC18] relink. loc_66d3fdf: if r14==rbx →0x66d4001; if rbx==0 →0x66d4001; else rcx=[0x1233E1A8]; rax=[rcx]; rax=[rax+0x10] (allocator free fn); rdx=rbx (continues phase 23 — free rbx). Next address: 0x66d3ffa.

## Phase 23 — 0x66d3ffa, 40 instructions [V]
```
66d3ffa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d4000  nop                                           
66d4001  lea rcx,[rbp+0xA50]                           
66d4008  call 0x67627D0                                ; -> sub_67627d0
66d400d  mov rbx,[rbp+0x710]                           
66d4014  mov esi,[rbp+0x718]                           
66d401a  test rsi,rsi                                  
66d401d  je short 0x66D405F                            ; -> loc_66d405f
66d401f  shl rsi,5                                     
66d4023  xor edi,edi                                   
66d4025  jmp short 0x66D4039                           ; -> loc_66d4039
66d4027  nop [rax+rax]                                 ; R ret@67627d0+0x0+idx

loc_66d4030:  ; from 66d4041, 66d4047, 66d4056
  66d4030  add rdi,0x20                                  
  66d4034  cmp rsi,rdi                                   
  66d4037  je short 0x66D4058                            ; -> loc_66d4058

loc_66d4039:  ; from 66d4025
  66d4039  mov rcx,[rbx+rdi+8]                           
  66d403e  test rcx,rcx                                  
  66d4041  je short 0x66D4030                            ; -> loc_66d4030
  66d4043  lock dec dword ptr [rcx+0xC]                  
  66d4047  jne short 0x66D4030                           ; -> loc_66d4030
  66d4049  mov rax,[rcx]                                 
  66d404c  mov rax,[rax+8]                               
  66d4050  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4056  jmp short 0x66D4030                           ; -> loc_66d4030

loc_66d4058:  ; from 66d4037
  66d4058  mov rbx,[rbp+0x710]                           

loc_66d405f:  ; from 66d401d
  66d405f  cmp r12,rbx                                   
  66d4062  je short 0x66D4081                            ; -> loc_66d4081
  66d4064  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  66d406b  test rbx,rbx                                  
  66d406e  je short 0x66D4081                            ; -> loc_66d4081
  66d4070  mov rax,[rcx]                                 
  66d4073  mov rax,[rax+0x10]                            
  66d4077  mov rdx,rbx                                   
  66d407a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d4080  nop                                           

loc_66d4081:  ; from 66d4062, 66d406e
  66d4081  mov rbx,[rbp+0x6D0]                           
  66d4088  mov esi,[rbp+0x6D8]                           
  66d408e  test rsi,rsi                                  
  66d4091  je short 0x66D40CF                            ; -> loc_66d40cf
  66d4093  shl rsi,5                                     
```
`//` [V] Phase 23: call qword ptr [0xF99FFA0](rdx=rbx) free rbx [V]; call 0x67627D0(rcx=&rbp+0xA50) value teardown [V] (3rd call-0x67627D0). Release loop #2: rbx=[rbp+0x710]; esi=[rbp+0x718]; if 0 →0x66d405f; rsi<<=5; edi=0; loc_66d4039: rcx=[rbx+rdi+8]; lock dec dword [rcx+0xC]; zero →free via [0xF99FFA0]; loc_66d4030: rdi+=0x20; loop until rdi==rsi →0x66d4058; rbx=[rbp+0x710] relink [V] — identical pattern to phase 22 (0x20-stride entry arrays, refcount at +0xC). loc_66d405f: if r12==rbx →0x66d4081; if rbx==0 →0x66d4081; else free rbx via allocator [0xF99FFA0] [V]. loc_66d4081: rbx=[rbp+0x6D0]; esi=[rbp+0x6D8]; release loop #3 begins: shl rsi,5 (continues phase 24). Next address: 0x66d4097.

## Phase 24 — 0x66d4097, 40 instructions [V]
```
66d4097  xor edi,edi                                   
66d4099  jmp short 0x66D40A9                           ; -> loc_66d40a9
66d409b  nop [rax+rax]                                 

loc_66d40a0:  ; from 66d40b1, 66d40b7, 66d40c6
  66d40a0  add rdi,0x20                                  
  66d40a4  cmp rsi,rdi                                   
  66d40a7  je short 0x66D40C8                            ; -> loc_66d40c8

loc_66d40a9:  ; from 66d4099
  66d40a9  mov rcx,[rbx+rdi+8]                           
  66d40ae  test rcx,rcx                                  
  66d40b1  je short 0x66D40A0                            ; -> loc_66d40a0
  66d40b3  lock dec dword ptr [rcx+0xC]                  
  66d40b7  jne short 0x66D40A0                           ; -> loc_66d40a0
  66d40b9  mov rax,[rcx]                                 
  66d40bc  mov rax,[rax+8]                               
  66d40c0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d40c6  jmp short 0x66D40A0                           ; -> loc_66d40a0

loc_66d40c8:  ; from 66d40a7
  66d40c8  mov rbx,[rbp+0x6D0]                           
  66d40cf  cmp r15,rbx                                   
  66d40d2  je short 0x66D40F1                            ; -> loc_66d40f1
  66d40d4  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  66d40db  test rbx,rbx                                  
  66d40de  je short 0x66D40F1                            ; -> loc_66d40f1
  66d40e0  mov rax,[rcx]                                 
  66d40e3  mov rax,[rax+0x10]                            
  66d40e7  mov rdx,rbx                                   
  66d40ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  66d40f0  nop                                           

loc_66d40f1:  ; from 66d40d2, 66d40de
  66d40f1  mov rbx,[rbp+0x770]                           
  66d40f8  mov esi,[rbp+0x778]                           
  66d40fe  test rsi,rsi                                  
  66d4101  je short 0x66D413F                            ; -> loc_66d413f
  66d4103  shl rsi,5                                     
  66d4107  xor edi,edi                                   
  66d4109  jmp short 0x66D4119                           ; -> loc_66d4119
  66d410b  nop [rax+rax]                                 

loc_66d4110:  ; from 66d4121, 66d4127, 66d4136
  66d4110  add rdi,0x20                                  
  66d4114  cmp rsi,rdi                                   
  66d4117  je short 0x66D4138                            ; -> loc_66d4138

loc_66d4119:  ; from 66d4109
  66d4119  mov rcx,[rbx+rdi+8]                           
  66d411e  test rcx,rcx                                  
  66d4121  je short 0x66D4110                            ; -> loc_66d4110
```
`//` [V] Phase 24: release loop #3 (rbx=[rbp+0x6D0], esi=[rbp+0x6D8]): rcx=[rbx+rdi+8]; lock dec dword [rcx+0xC]; zero →free via [0xF99FFA0](rdx=[rax+8]); rdi+=0x20; loop until rdi==rsi →0x66d40c8; rbx=[rbp+0x6D0] relink; if r15==rbx →0x66d40f1; if rbx==0 →0x66d40f1; else free rbx via [0xF99FFA0] [V]. Fourth identical release-loop pattern (0x20-stride, refcount +0xC). Release loop #4: rbx=[rbp+0x770]; esi=[rbp+0x778]; if 0 →0x66d413f; rsi<<=5; edi=0; loc_66d4119: rcx=[rbx+rdi+8]; lock dec... (continues phase 25). Next address: 0x66d4123.

## Phase 25 — 0x66d4123, 40 instructions [V]
```
66d4123  lock dec dword ptr [rcx+0xC]                  ; W a0+0xC
66d4127  jne short 0x66D4110                           ; -> sub_66d4110
66d4129  mov rax,[rcx]                                 ; R a0+0x0
66d412c  mov rax,[rax+8]                               ; R *(a0+0x0)+0x8
66d4130  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d4136  jmp short 0x66D4110                           ; -> sub_66d4110
66d4138  mov rbx,[rbp+0x770]                           
66d413f  lea rax,[rbp+0x780]                           
66d4146  cmp rax,rbx                                   
66d4149  je short 0x66D4168                            ; -> loc_66d4168
66d414b  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
66d4152  test rbx,rbx                                  
66d4155  je short 0x66D4168                            ; -> loc_66d4168
66d4157  mov rax,[rcx]                                 
66d415a  mov rax,[rax+0x10]                            
66d415e  mov rdx,rbx                                   
66d4161  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d4167  nop                                           

loc_66d4168:  ; from 66d4149, 66d4155
  66d4168  mov rcx,[rbp+0x7B8]                           
  66d416f  test rcx,rcx                                  
  66d4172  je short 0x66D4187                            ; -> loc_66d4187
  66d4174  lock dec dword ptr [rcx+0xC]                  
  66d4178  jne short 0x66D4187                           ; -> loc_66d4187
  66d417a  mov rax,[rcx]                                 
  66d417d  mov rax,[rax+8]                               
  66d4181  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_66d4187:  ; from 66d4172, 66d4178
  66d4187  lea rsi,[0xF2BE888]                           ; [data_f2be888]
  66d418e  mov [rbp+0xA50],rsi                           
  66d4195  lea rbx,[rbp+0xA58]                           
  66d419c  lea rdx,[rbp+0x7E0]                           
  66d41a3  mov rcx,rbx                                   
  66d41a6  call 0x6761590                                ; -> sub_6761590
  66d41ab  nop                                           
  66d41ac  lea rdi,[rbp+0xC08]                           
  66d41b3  mov eax,[rbp+0x990]                           
  66d41b9  mov [rbp+0xC08],eax                           
  66d41bf  lea r14,[rbp+0xC10]                           
  66d41c6  movzx eax,word ptr [rbp+0x998]                
  66d41cd  mov [rbp+0xC10],ax                            
  66d41d4  lea r15,[rbp+0xC18]                           
```
`//` [V] Phase 25: release loop #4 tail: lock dec [rcx+0xC]; zero →free via [0xF99FFA0](rdx=[rax+8]); rbx=[rbp+0x770]; if [rbp+0x780]==rbx →0x66d4168 else free rbx via [0xF99FFA0] (release list head) [V]. loc_66d4168: rcx=[rbp+0x7B8]; lock dec [rcx+0xC]; zero →free via [0xF99FFA0] (final refcount release) [V]. loc_66d4187: [rbp+0xA50]=0xF2BE888 (qword addr); call 0x6761590(rcx=&rbp+0xA58, rdx=&rbp+0x7E0) [V] (3rd call-0x6761590); copy [rbp+0x990→0xC08 dword, 0x998→0xC10 word] [V]; rdi=&rbp+0xC08; r14=&rbp+0xC10; r15=&rbp+0xC18 (continues phase 26). Next address: 0x66d41db.

## Phase 26 — 0x66d41db, 40 instructions [V]
```
66d41db  movzx eax,word ptr [rbp+0x9A0]                
66d41e2  mov [rbp+0xC18],ax                            
66d41e9  lea r12,[rbp+0xC20]                           
66d41f0  lea rax,[rbp+0xC30]                           
66d41f7  mov [rbp+0xC20],rax                           
66d41fe  mov [rbp+0xC28],r13                           
66d4205  mov rcx,r12                                   
66d4208  lea rdx,[rbp+0x9A8]                           
66d420f  call 0x6764990                                ; -> sub_6764990
66d4214  mov rcx,[rbp+0xD90]                           
66d421b  add rcx,0x9D0                                 
66d4222  lea rax,[rbp+0xAB0]                           
66d4229  lea r9,[rbp+0xAF8]                            
66d4230  lea rdx,[rbp+0xB28]                           
66d4237  lea r8,[rbp+0xBB0]                            
66d423e  mov [rsp+0x48],rbx                            
66d4243  mov [rsp+0x40],rax                            
66d4248  mov [rsp+0x38],r9                             
66d424d  mov [rsp+0x30],rdx                            
66d4252  mov [rsp+0x28],r8                             
66d4257  mov [rsp+0x20],rdi                            
66d425c  mov rdx,r12                                   
66d425f  mov r8,r15                                    
66d4262  mov r9,r14                                    
66d4265  call 0x6765020                                ; -> sub_6765020
66d426a  nop                                           
66d426b  mov [rbp+0xA50],rsi                           
66d4272  mov rsi,[rbp+0xC20]                           
66d4279  mov r14d,[rbp+0xC28]                          
66d4280  test r14,r14                                  
66d4283  lea r12,[rbp+0x9B8]                           
66d428a  je short 0x66D42CF                            ; -> loc_66d42cf
66d428c  shl r14,5                                     
66d4290  xor r15d,r15d                                 
66d4293  jmp short 0x66D42A9                           ; -> loc_66d42a9
66d4295  nop [rax+rax]                                 ; R ret@6765020+0x0+idx

loc_66d42a0:  ; from 66d42b1, 66d42b7, 66d42c6
  66d42a0  add r15,0x20                                  
  66d42a4  cmp r14,r15                                   
  66d42a7  je short 0x66D42C8                            ; -> loc_66d42c8

loc_66d42a9:  ; from 66d4293
  66d42a9  mov rcx,[rsi+r15+8]                           
```
`//` [V] Phase 26: [rbp+0xC18]=[rbp+0x9A0]; [rbp+0xC20]=[rbp+0xC30]; [rbp+0xC28]=r13 (node self-link) [V]; call 0x6764990(rcx=&rbp+0xC20, rdx=&rbp+0x9A8) [V] (5th call-0x6764990). Big call: rcx=[rbp+0xD90]+0x9D0; stack [rsp+0x20..0x48]={rdi, &rbp+0xBB0, &rbp+0xB28, &rbp+0xAF8, &rbp+0xAB0, rbx}; rdx=&rbp+0xC20; r8=&rbp+0xC18; r9; call 0x6765020(rcx=[rbp+0xD90]+0x9D0, rdx=&rbp+0xC20, r8=&rbp+0xC18, r9) [V] new callee — largest arg frame yet. [rbp+0xA50]=rsi (result) [V]. Release loop #5: rsi=[rbp+0xC20]; r14d=[rbp+0xC28]; if 0 →0x66d42cf; r14<<=5; r15=0; loc_66d42a9: rcx=[rsi+r15+8] (continues phase 27). Next address: 0x66d42b0.

## NEXT [current]
Resume at RVA 0x66d42b0 (after phase 26, 0x66d41db..0x66d42a9). 1040 of 1200 instructions done (~160 remaining, 4 phases). Next call: `rdis ... dis 0x66d42b0 40`.
