# Progress: U-PASS4A2 — decode sub_bbdad00 (RVA 0xbbdad00) completely

## NEXT
Transcribe phases continuing at 0xbbdb59a through end of function (0xbbdcdc5); then report caller sub_67c9970 (args it builds, object type hints, before/after), sub_bbdad00 arguments (rcx/rdx/r8), pool +0x750 stride-0x88 usage + +0x78 compare, outputs (structures written, callees called), with [V]/[I]/[?] tags.

## SOURCE / METHOD (all static, exe not run)
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe 1.26.62.01. RVAs relative to image base.
- Bounds: `rdis fn 0xbbdad00 --max 10000` → sub_bbdad00 [0xbbdad00..0xbbdcdc5), size 0x20c5, 1 xref in. Raw: docs/progress/u-pass4a-fn-full.txt.
- Caller: `rdis dis 0x67c9970 150`. Raw: docs/progress/u-pass4a-caller-raw.txt (174 lines). Call at 0x67c99be.
- Tags: [V] = seen verbatim in disassembly (cite RVA); [I] = inferred from pattern; [?] = not determined from available data.
- Instruction quotes are verbatim from rdis (`0xRVA` column as printed). Each phase ≤ 40 instructions; interpretation in separate `;` comment lines. Every instruction in [0xbbdad00, 0xbbdcdc5) belongs to exactly one phase.

## PHASES — sub_bbdad00 full transcription (continued from oc_U-PASS4A.md phases 1-27)

### Phase 28: 0xbbdb5a0..0xbbdb630 — sub_a78940 alloc + release + copy
```
  bbdb5a0  mov rax,[rbp+0x2C0]                           
  bbdb5a7  mov rcx,[rax]                                 
  bbdb5aa  mov r9d,1                                     
  bbdb5b0  lea rdx,[rbp+0x248]                           
  bbdb5b7  mov r8,rsi                                    
  bbdb5ba  call 0xA78940                                 ; -> sub_a78940
  bbdb5bf  nop                                           
  bbdb5c0  mov rbx,[rbp+0x258]                           
  bbdb5c7  mov rax,[rbp+0x248]                           
  bbdb5ce  mov rdi,[rbp+0x250]                           
  bbdb5d5  mov r13,[rax]                                 
  bbdb5d8  test rdi,rdi                                  
  bbdb5db  je short 0xBBDB610                            ; -> loc_bbdb610
  bbdb5dd  lock dec dword ptr [rdi+8]                    
  bbdb5e1  jne short 0xBBDB610                           ; -> loc_bbdb610
  bbdb5e3  mov rax,[rdi]                                 
  bbdb5e6  mov rax,[rax]                                 
  bbdb5e9  mov rcx,rdi                                   
  bbdb5ec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb5f2  lock dec dword ptr [rdi+0xC]                  
  bbdb5f6  jne short 0xBBDB610                           ; -> loc_bbdb610
  bbdb5f8  mov rax,[rdi]                                 
  bbdb5fb  mov rax,[rax+8]                               
  bbdb5ff  mov rcx,rdi                                   
  bbdb602  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb608  nop [rax+rax]                                 
loc_bbdb610:  ; from bbdb5db, bbdb5e1, bbdb5f6
  bbdb610  add r13,rbx                                   
  bbdb613  lea rdi,[rsi+r13]                             
  bbdb617  mov rcx,r13                                   
  bbdb61a  mov rdx,r12                                   
  bbdb61d  mov r8,rsi                                    
  bbdb620  call 0xEEC6DE0                                ; -> sub_eec6de0
  bbdb625  mov [rbp+0x2A0],r14                           
  bbdb62c  jmp short 0xBBDB660                           ; -> loc_bbdb660
  bbdb62e  xchg ax,ax                                    
```
; r8 was remaining-entry count (rdi from magic divide at bbdb586-9a). Alloc sub_a78940(rcx=[rbp+0x2C0] pool obj, rdx=&[rbp+0x248], r8=rsi=count, r9d=1) → rax=rsi [V bbdb5a0-5b7]. r13=[rax] (alloc result stored at +0x0 in pool obj field) [V bbdb5d5]. Release object rdi=[rbp+0x250]: two-stage (strong then weak) refcount via lock dec [rdi+8]/[rdi+0xC] with vtable release calls [rax]/[rax+8]; zero paths → loc_bbdb610 [V bbdb5c0-608]. loc_bbdb610: r13 += rbx (running offset); rdi = rsi + r13 (end cursor); sub_eec6de0(rcx=r13=dst offset, rdx=r12, r8=rsi=buffer) → copies entries [V bbdb610-20]. [rbp+0x2A0]=r14 (reset cursor); jmp loc_bbdb660 [V bbdb625-2c].

### Phase 29: 0xbbdb630..0xbbdb721 — scan-and-match + sub_bc3a2f0 loop
```
loc_bbdb630:  ; from bbdb6fb
  bbdb630  sub rsi,r13                                   
  bbdb633  add rsi,0xFFFFFFFFFFFFFFE8                    
  bbdb637  mov rax,rsi                                   
  bbdb63a  mov rcx,0xAAAAAAAAAAAAAAAB                    
  bbdb644  mul rcx                                       
  bbdb647  shr rdx,4                                     
  bbdb64b  inc rdx                                       
loc_bbdb64e:  ; from bbdb703
  bbdb64e  lea rax,[rdx+rdx*2]                           
  bbdb652  lea r13,[r13+rax*8]                           
  bbdb657  cmp r13,rdi                                   
  bbdb65a  je 0xBBDB110                                  ; -> sub_bbdb110
loc_bbdb660:  ; from bbdb62c
  bbdb660  mov rcx,[r13+8]                               
  bbdb664  test rcx,rcx                                  
  bbdb667  je short 0xBBDB67C                            ; -> loc_bbdb67c
  bbdb669  mov rax,[r13+0x10]                            
  bbdb66d  test rax,rax                                  
  bbdb670  je short 0xBBDB67C                            ; -> loc_bbdb67c
  bbdb672  test byte ptr [rcx+1],0x20                    
  bbdb676  jne 0xBBDB708                                 ; -> loc_bbdb708
loc_bbdb67c:  ; from bbdb667, bbdb670
  bbdb67c  xor ecx,ecx                                   
loc_bbdb67e:  ; from bbdb71c
  bbdb67e  lea rax,[r13+0x18]                            
  bbdb682  mov rsi,rdi                                   
  bbdb685  cmp rax,rdi                                   
  bbdb688  je short 0xBBDB6D3                            ; -> loc_bbdb6d3
  bbdb68a  mov rcx,[rcx+0x78]                            
  bbdb68e  xchg ax,ax                                    
loc_bbdb690:  ; from bbdb6bc
  bbdb690  mov rdx,[rax+8]                               
  bbdb694  mov r8,[rax+0x10]                             
  bbdb698  movzx edx,word ptr [rdx+0x2A]                 
  bbdb69c  mov r8,[r8+0x750]                             
  bbdb6a3  mov r9d,edx                                   
  bbdb6a6  shl r9d,7                                     
  bbdb6aa  lea rdx,[r9+rdx*8]                            
  bbdb6ae  cmp rcx,[r8+rdx+0x78]                         
  bbdb6b3  jne short 0xBBDB6D0                           ; -> loc_bbdb6d0
  bbdb6b5  add rax,0x18                                  
  bbdb6b9  cmp rax,rdi                                   
  bbdb6bc  jne short 0xBBDB690                           ; -> loc_bbdb690
  bbdb6be  mov rsi,rdi                                   
  bbdb6c1  jmp short 0xBBDB6D3                           ; -> loc_bbdb6d3
  bbdb6c3  nop [rax+rax]                                 
loc_bbdb6d0:  ; from bbdb6b3
  bbdb6d0  mov rsi,rax                                   
loc_bbdb6d3:  ; from bbdb688, bbdb6c1
  bbdb6d3  mov [rbp+0x248],r13                           
  bbdb6da  mov [rbp+0x250],rsi                           
  bbdb6e1  mov [rbp+0x258],r13                           
  bbdb6e8  mov rcx,r15                                   
  bbdb6eb  lea rdx,[rbp+0x248]                           
  bbdb6f2  call 0xBC3A2F0                                ; -> sub_bc3a2f0
  bbdb6f7  nop                                           
  bbdb6f8  cmp r13,rsi                                   
  bbdb6fb  jne 0xBBDB630                                 ; -> loc_bbdb630
  bbdb701  xor edx,edx                                   
  bbdb703  jmp 0xBBDB64E                                 ; -> loc_bbdb64e
loc_bbdb708:  ; from bbdb676
  bbdb708  movzx ecx,word ptr [rcx+0x2A]                 
  bbdb70c  mov edx,ecx                                   
  bbdb70e  shl edx,7                                     
  bbdb711  lea rcx,[rdx+rcx*8]                           
  bbdb715  add rcx,[rax+0x750]                           
  bbdb71c  jmp 0xBBDB67E                                 ; -> loc_bbdb67e
loc_bbdb721:  ; from bbdb176 (outer-list exhaustion in earlier loop)
  bbdb721  mov rcx,[rbp-0x18]                            
  bbdb725  test rcx,rcx                                  
  bbdb728  je 0xBBDB128                                  ; -> sub_bbdb128
  bbdb72e  lea rax,[rbp-0x50]                            
  bbdb732  cmp rcx,rax                                   
  bbdb735  setne dl                                      
  bbdb738  mov rax,[rcx]                                 
  bbdb73b  mov rax,[rax+0x20]                            
  bbdb73f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb745  jmp 0xBBDB128                                 ; -> sub_bbdb128
```
; loc_bbdb630: remaining bytes = (rsi - r13) - 8 (skip leading 8 bytes?); count via mul by 0xAAAAAAAAAAAAAAAB, shr rdx,4, inc rdx → entry count rdx [V bbdb630-4b]. loc_bbdb64e: advance r13 by count*24 (rdx+rdx*2)*8; if r13==rdi → loc_bbdb110 (outer next iter) [V bbdb64e-65a]. loc_bbdb660: scan entries at r13: entry{0, ptr@+8, val@+0x10}; valid if both nonzero and byte [rcx+1]&0x20 → loc_bbdb708; else ecx=0 [V bbdb660-7c]. loc_bbdb67e: walk slots from rax=r13+0x18 step 0x18 to rdi; read [rcx+0x78]; slot = {rdx=[rax+8], r8=[rax+0x10]}; u16 = [rdx+0x2A]; r8 = [r8+0x750] (pool table +0x750); r9d = u16<<7; rdx = r9 + r8*8; match if rcx == [r8+rdx+0x78] → rsi=rax (match found), else rsi=rdi (no match) [V bbdb68a-6d0]. [rbp+0x248/0x250/0x258] = r13/rsi/r13 (state save); call sub_bc3a2f0(rcx=r15, rdx=&[rbp+0x248]) → rsi = result [V bbdb6d3-6f7]. If r13 != rsi → loop loc_bbdb630; else edx=0 → loc_bbdb64e [V bbdb6f8-703]. loc_bbdb708: u16=[rcx+0x2A]<<7; rcx = rdx + rcx*8 + [rax+0x750]; jmp loc_bbdb67e [V bbdb708-1c]. **pool +0x750 (stride 0x88) +0x78 compare**: r8 = [table_base+0x750]; rdx = u16*0x88 (via shl 7 + lea rdx,[r9+rdx*8] = u16*128 + u16*8 = u16*136 = u16*0x88); compare [r8+rdx+0x78] against rcx → membership test in stride-0x88 pool table at +0x78 field [V bbdb69c-6ae].

### Phase 30: 0xbbdb74a..0xbbdb795 — return-to-outer + next-outer loop
```
loc_bbdb74a:  ; from bbdb13d (outer done in earlier loop)
  bbdb74a  lea rcx,[rbp+0x160]                           
  bbdb751  call 0xBC06740                                ; -> sub_bc06740
  bbdb756  xorps xmm6,xmm6                               
  bbdb759  movaps [rbp+0x1E0],xmm6                       
  bbdb760  mov qword ptr [rbp+0x1F0],0                   
  bbdb76b  mov rax,[rbp+0x158]                           
  bbdb772  mov rbx,[rax]                                 
  bbdb775  mov r15,[rax+8]                               
  bbdb779  lea rsi,[rbp-0x50]                            
  bbdb77d  lea r13,[rbp+0x2A0]                           
  bbdb784  lea r14,[rbp+0x248]                           
  bbdb78b  jmp short 0xBBDB79C                           ; -> loc_bbdb79c
  bbdb78d  nop [rax]                                     
loc_bbdb790:  ; from bbdb91a, bbdb93c (slack realloc)
  bbdb790  call 0xE935700                                ; -> sub_e935700
loc_bbdb795:  ; from bbdb903
  bbdb795  add rbx,0x618                                 
  bbdb79c  cmp rbx,r15                                   
  bbdb79f  je 0xBBDB95F                                  ; -> loc_bbdb95f
```
; sub_bc06740(rcx=&[rbp+0x160]) — cleanup slot-array state [V bbdb74a-51]. xmm6=0; zero [rbp+0x1E0], [rbp+0x1F0]=0 [V bbdb756-60]. rbx=[rbp+0x158]+0 (array base again), r15=[rax+8] (array end) [V bbdb76b-75]. rsi=rbp-0x50, r13=&[rbp+0x2A0], r14=&[rbp+0x248] (reset temp-buffer slots) [V bbdb779-84]. loc_bbdb795: rbx += 0x618 (next outer array element); rbx==r15 → loc_bbdb95f (done) [V bbdb795-9f]. loc_bbdb790: slack path → sub_e935700 [V bbdb790].

### Phase 31: 0xbbdb79c..0xbbdb886 — third array element loop (mirrors phase 3)
```
loc_bbdb79c:  ; from bbdb78b
  bbdb79c  cmp rbx,r15                                   
  bbdb79f  je 0xBBDB95F                                  ; -> loc_bbdb95f
  bbdb7a5  movaps [rbp+0x2A0],xmm6                       
  bbdb7ac  mov qword ptr [rbp+0x2B0],0                   
  bbdb7b7  mov r12,[rbx+0x360]                           
  bbdb7be  mov rcx,[rbx+0x358]                           
  bbdb7c5  mov rax,r12                                   
  bbdb7c8  sub rax,rcx                                   
  bbdb7cb  sub r12,rcx                                   
  bbdb7ce  je 0xBBDB886                                  ; -> loc_bbdb886
  bbdb7d4  sar rax,1                                     
  bbdb7d7  js 0xBBDCD62                                  ; -> loc_bbdcd62
  bbdb7dd  cmp rax,0x800                                 
  bbdb7e3  jb short 0xBBDB820                            ; -> loc_bbdb820
  bbdb7e5  lea rdi,[r12+0x27]                            
  bbdb7ea  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdb7f1  mov rax,[rcx]                                 
  bbdb7f4  mov rax,[rax+8]                               
  bbdb7f8  mov rdx,rdi                                   
  bbdb7fb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb801  nop                                           
  bbdb802  mov rsi,rax                                   
  bbdb805  test rax,rax                                  
  bbdb808  je 0xBBDB941                                  ; -> loc_bbdb941
loc_bbdb80e:  ; from bbdb94a
  bbdb80e  mov rax,rsi                                   
  bbdb811  add rsi,0x27                                  
  bbdb815  and rsi,0xFFFFFFFFFFFFFFE0                    
  bbdb819  mov [rsi-8],rax                               
  bbdb81d  jmp short 0xBBDB844                           ; -> loc_bbdb844
  bbdb81f  nop                                           
loc_bbdb820:  ; from bbdb7e3
  bbdb820  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdb827  mov rax,[rcx]                                 
  bbdb82a  mov rax,[rax+8]                               
  bbdb82e  mov rdx,r12                                   
  bbdb831  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb837  nop                                           
  bbdb838  mov rsi,rax                                   
  bbdb83b  test rax,rax                                  
  bbdb83e  je 0xBBDB94F                                  ; -> loc_bbdb94f
loc_bbdb844:  ; from bbdb81d, bbdb95a
  bbdb844  mov [rbp+0x2A0],rsi                           
  bbdb84b  mov [rbp+0x2A8],rsi                           
  bbdb852  add r12,rsi                                   
  bbdb855  mov [rbp+0x2B0],r12                           
  bbdb85c  mov rdx,[rbx+0x358]                           
  bbdb863  mov rdi,[rbx+0x360]                           
  bbdb86a  sub rdi,rdx                                   
  bbdb86d  mov rcx,rsi                                   
  bbdb870  mov r8,rdi                                    
  bbdb873  call 0xEEC6DE0                                ; -> sub_eec6de0
  bbdb878  add rdi,rsi                                   
  bbdb87b  mov [rbp+0x2A8],rdi                           
  bbdb882  lea rsi,[rbp-0x50]                            
loc_bbdb886:  ; from bbdb7ce
  bbdb886  lea rdx,[rbx+0x120]                           
  bbdb88d  mov byte ptr [rbp+0x280],0                    
  bbdb894  mov rcx,rsi                                   
  bbdb897  mov r8,r13                                    
  bbdb89a  mov r9,r14                                    
  bbdb89d  call 0x566A450                                ; -> sub_566a450
```
; Per-array-element loop (third instance): cmp rbx,r15 → done [V bbdb79c-9f]. Clear [rbp+0x2A0], [rbp+0x2B0]=0 [V bbdb7a5-ac]. r12=[rbx+0x360] end, rcx=[rbx+0x358] start; size=r12-rcx [V bbdb7b7-cb]. zero → loc_bbdb886 [V bbdb7ce]. sar rax,1; negative → loc_bbdcd62 [V bbdb7d4-d7]. if size/2 < 0x800 → small alloc loc_bbdb820 [V bbdb7dd-e3]. big: rdi=size+0x27; alloc via [0xF99FFA0]=sub_eea6040; rsi=rax; null → loc_bbdb941 [V bbdb7e5-808]. loc_bbdb80e: align-up-32 (rsi+=0x27, &~0x1f), store orig rax at [rsi-8] [V bbdb80e-19]. loc_bbdb820: small alloc size r12; null → loc_bbdb94f [V bbdb820-83e]. loc_bbdb844: [rbp+0x2A0/0x2A8]=rsi (buffer start); r12=rsi+size → [rbp+0x2B0] end cursor [V bbdb844-55]. copy sub_eec6de0(rcx=rsi=dst, rdx=[rbx+0x358], r8=size) → [rbp+0x2A8]=rsi+size [V bbdb85c-87b]. rsi=rbp-0x50 scratch reset [V bbdb882]. loc_bbdb886: rdx=rbx+0x120 (different element offset than phase 3's r13+8); byte [rbp+0x280]=0; call sub_566a450(rcx=rsi, rdx=rbx+0x120, r8=r13=&[rbp+0x2A0], r9=r14=&[rbp+0x248]) [V bbdb886-89d].

### Phase 32: 0xbbdb8a3..0xbbdb95f — slot array + final sub_bbd9be0 + division
```
  bbdb8a3  mov rdx,[rbp+0x1E8]                           
  bbdb8aa  cmp rdx,[rbp+0x1F0]                           
  bbdb8b1  je short 0xBBDB8D0                            ; -> loc_bbdb8d0
  bbdb8b3  mov rcx,rdx                                   
  bbdb8b6  mov rdx,rsi                                   
  bbdb8b9  call 0x5667c80                                ; -> sub_5667c80
  bbdb8be  nop                                           
  bbdb8bf  add qword ptr [rbp+0x1E8],0x170               
  bbdb8ca  jmp short 0xBBDB8E0                           ; -> loc_bbdb8e0
  bbdb8cc  nop [rax]                                     ; R ret@5667c80+0x0
loc_bbdb8d0:  ; from bbdb8b1
  bbdb8d0  lea rcx,[rbp+0x1E0]                           
  bbdb8d7  mov r8,rsi                                    
  bbdb8da  call 0x56B68C0                                ; -> sub_56b68c0
  bbdb8df  nop                                           
loc_bbdb8e0:  ; from bbdb8ca
  bbdb8e0  mov rcx,rsi                                   
  bbdb8e3  call 0x5667e70                                ; -> sub_5667e70
  bbdb8e8  cmp byte ptr [rbp+0x280],1                    
  bbdb8ef  jne short 0xBBDB8F9                           ; -> loc_bbdb8f9
  bbdb8f1  mov rcx,r14                                   
  bbdb8f4  call 0x655cea0                                ; -> sub_655cea0
loc_bbdb8f9:  ; from bbdb8ef
  bbdb8f9  mov rcx,[rbp+0x2A0]                           
  bbdb900  test rcx,rcx                                  
  bbdb903  je 0xBBDB795                                  ; -> loc_bbdb795
  bbdb909  mov rdx,[rbp+0x2B0]                           
  bbdb910  sub rdx,rcx                                   
  bbdb913  cmp rdx,0x1000                                
  bbdb91a  jb 0xBBDB790                                  ; -> loc_bbdb790
  bbdb920  mov rax,[rcx-8]                               
  bbdb924  add rcx,0xFFFFFFFFFFFFFFF8                    
  bbdb928  sub rcx,rax                                   
  bbdb92b  cmp rcx,0x20                                  
  bbdb92f  jae 0xBBDCD42                                 ; -> loc_bbdcd42
  bbdb935  add rdx,0x27                                  
  bbdb939  mov rcx,rax                                   
  bbdb93c  jmp 0xBBDB790                                 ; -> loc_bbdb790
loc_bbdb941:  ; from bbdb808
  bbdb941  mov rcx,rdi                                   
  bbdb944  call 0x9BC830                                 ; -> sub_9bc830
  bbdb949  nop                                           
  bbdb94a  jmp 0xBBDB80E                                 ; -> loc_bbdb80e
loc_bbdb94f:  ; from bbdb83e
  bbdb94f  mov rcx,r12                                   
  bbdb952  call 0x9BC830                                 ; -> sub_9bc830
  bbdb957  nop                                           
  bbdb958  xor esi,esi                                   
  bbdb95a  jmp 0xBBDB844                                 ; -> loc_bbdb844
loc_bbdb95f:  ; from bbdb79f
  bbdb95f  lea rcx,[rbp+0x140]                           
  bbdb966  lea rdx,[rbp+0x1E0]                           
  bbdb96d  call 0xBBD9BE0                                ; -> sub_bbd9be0
  bbdb972  nop                                           
  bbdb973  mov r14,[rbp+0x148]                           
  bbdb97a  mov rcx,[rbp+0x140]                           
  bbdb981  mov rax,r14                                   
  bbdb984  sub rax,rcx                                   
  bbdb987  xorps xmm0,xmm0                               
  bbdb98a  movaps [rbp+0x180],xmm0                       
  bbdb991  mov qword ptr [rbp+0x190],0                   
  bbdb99c  sub r14,rcx                                   
  bbdb99f  mov r15,0x8F5C28F5C28F5C29                    
  bbdb9a9  je short 0xBBDBA12                            ; -> loc_bbdba12
  bbdb9ab  sar rax,6                                     
  bbdb9af  mov rcx,0xCCCCCCCCCCCCCCD                    
  bbdb9b9  imul rax,rcx                                  
  bbdb9bd  mov rcx,0xCCCCCCCCCCCCCD                      
  bbdb9c7  cmp rax,rcx                                   
  bbdb9ca  jae 0xBBDCD98                                 ; -> loc_bbdcd98
```
; Slot array at [rbp+0x1E0]/[rbp+0x1F0] stride 0x170: cursor vs end; sub_5667c80(slot, rsi) + cursor+=0x170; else sub_56b68c0(&[rbp+0x1E0], rsi) grow [V bbdb8a3-8df]. sub_5667e70(rsi); if byte [rbp+0x280]==1 → sub_655cea0(r14=&[rbp+0x248]) [V bbdb8e0-8f4]. rcx=[rbp+0x2A0]; null → loc_bbdb795 (next element) [V bbdb8f9-903]. rdx = [rbp+0x2B0]-[rbp+0x2A0] (used); <0x1000 → slack path loc_bbdb790 [V bbdb909-1a]. rax=[rcx-8]; slack=(rcx-8)-rax; <0x20 → jae loc_bbdcd42 [V bbdb920-2b]; else add rdx,0x27 → loc_bbdb790 [V bbdb935-3c]. Alloc failure: sub_9bc830(rcx=rdi=size+0x27 or rcx=r12=size) → loc_bbdb80e/844 with rsi=0 [V bbdb941-95a]. loc_bbdb95f: element loop done; sub_bbd9be0(rcx=&[rbp+0x140] start, rdx=&[rbp+0x1E0] slot state) [V bbdb95f-6d]. rbx=[rbp+0x148] end, rcx=[rbp+0x140] start; count_bytes=rbx-rcx [V bbdb973-84]. zero [rbp+0x180], [rbp+0x190]=0 [V bbdb987-91]. r15=magic 0x8F5C28F5C28F5C29 [V bbdb99f]. count_bytes==0 → loc_bbdba12 [V bbdb9a9]. Else /192-ish checked division: rax=count_bytes>>6; rax*=0xCCCCCCCCCCCCCCCD; cmp rax,0xCCCCCCCCCCCCCD; jae → loc_bbdcd98 [V bbdb9ab-ca].

### Phase 33: 0xbbdb9d0..0xbbdbab0 — division range-check + alloc + outer-loop setup (second instance)
```
  bbdb9d0  cmp rax,0xD                                   
  bbdb9d4  jb short 0xBBDBA19                            ; -> loc_bbdba19
  bbdb9d6  mov rdi,r14                                   
  bbdb9d9  or rdi,0x27                                   
  bbdb9dd  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdb9e4  mov rax,[rcx]                                 
  bbdb9e7  mov rax,[rax+8]                               
  bbdb9eb  mov rdx,rdi                                   
  bbdb9ee  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb9f4  nop                                           
  bbdb9f5  mov rsi,rax                                   
  bbdb9f8  test rax,rax                                  
  bbdb9fb  je 0xBBDCD06                                  ; -> loc_bbdcd06
loc_bbdba01:  ; from bbdcd0f
  bbdba01  mov rax,rsi                                   
  bbdba04  add rsi,0x27                                  
  bbdba08  and rsi,0xFFFFFFFFFFFFFFE0                    
  bbdba0c  mov [rsi-8],rax                               
  bbdba10  jmp short 0xBBDBA3D                           ; -> loc_bbdba3d
  bbdba12  xor r12d,r12d                                 
  bbdba15  xor ecx,ecx                                   
  bbdba17  jmp short 0xBBDBA88                           ; -> loc_bbdba88
loc_bbdba19:  ; from bbdb9d4
  bbdbba19  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdbba20  mov rax,[rcx]                                 
  bbdbba23  mov rax,[rax+8]                               
  bbdbba27  mov rdx,r14                                   
  bbdbba2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdbba30  nop                                           
  bbdbba31  mov rsi,rax                                   
  bbdbba34  test rax,rax                                  
  bbdbba37  je 0xBBDCD14                                  ; -> loc_bbdcd14
loc_bbdba3d:  ; from bbdba10, bbdcd1f
  bbdba3d  mov [rbp+0x180],rsi                           
  bbdba44  mov [rbp+0x188],rsi                           
  bbdba4b  add r14,rsi                                   
  bbdba4e  mov [rbp+0x190],r14                           
  bbdba55  mov rcx,[rbp+0x140]                           
  bbdba5c  mov rdx,[rbp+0x148]                           
  bbdba63  lea r9,[rbp+0x180]                            
  bbdba6a  mov r8,rsi                                    
  bbdba6d  call 0xBC06200                                ; -> sub_bc06200
  bbdba72  nop                                           
  bbdba73  mov r12,rax                                   
  bbdba76  mov [rbp+0x188],rax                           
  bbdba7d  mov rcx,[rbp+0x180]                           
  bbdba84  lea rsi,[rbp-0x50]                            
loc_bbdba88:  ; from bbdba17
  bbdba88  mov rax,[rbp+0x238]                           
  bbdba8f  mov rax,[rax]                                 
  bbdba92  mov [rbp+0x228],rax                           
  bbdba99  lea r13,[rax+0xA10]                           
  bbdbaa0  mov [rbp+0x230],r12                           
  bbdbaa7  mov [rbp+0x298],r13                           
  bbdbaae  jmp short 0xBBDBADA                           ; -> loc_bbdbada
```
; rax(quotient) >= 0x13 → loc_bbdba19 (alloc size = r14 | 0x27); else → loc_bbdba12 (r12=0, rcx=0, zero-count path) [V bbdb9d0-17]. Alloc via [0xF99FFA0]=sub_eea6040(rcx=[data_1233e1a8] vtable obj, rax=[rcx]+8 method, rdx=rdi=size) → rsi=rax; null → loc_bbdcd06/bbdcd14 [V bbdb9dd-37]. loc_bbdba01: align-up-32, store orig rax at [rsi-8], jmp loc_bbdba3d [V bbdba01-10]. loc_bbdba3d: [rbp+0x180/0x188]=rsi (alloc result); r14=rsi+r14 (end cursor) → [rbp+0x190] [V bbdba3d-4e]. sub_bc06200(rcx=[rbp+0x140], rdx=[rbp+0x148], r8=rsi, r9=&[rbp+0x180]) → rax=r12, [rbp+0x188]=rax; rcx=[rbp+0x180]; rsi=rbp-0x50 [V bbdba55-84]. Outer setup: [rbp+0x228]=[a1] deref; r13=[a1]+0xA10 array base; [rbp+0x230]=r12; [rbp+0x298]=r13; jmp loc_bbdbada [V bbdba88-aae].

### Phase 34: 0xbbdbada..0xbbdbcdb — inner 0xC8 record loop + sum + pool alloc + release
```
loc_bbdbada:  ; from bbdbaae
  bbdbada  cmp rcx,r12                                   
  bbdbadd  je 0xBBDC0DA                                  ; -> loc_bbdc0da
  bbdbae3  mov [rbp+0x2B8],rcx                           
  bbdbaea  lea rax,[rcx+0x128]                           
  bbdbaf1  lea rcx,[0xF4409F0]                           ; [data_f4409f0]
  bbdbaf8  mov [rbp-0x50],rcx                            
  bbdbafc  mov [rbp-0x48],rax                            
  bbdbb00  mov [rbp-0x18],rsi                            
  bbdbb04  mov rsi,[r13]                                 
  bbdbb08  cmp rsi,r13                                   
  bbdbb0b  jne short 0xBBDBB1C                           ; -> loc_bbdbb1c
  bbdbb0d  jmp short 0xBBDBAC8                           ; -> loc_bbdbac8
  bbdbb0f  nop                                           
loc_bbdbb10:  ; from bbdbb27, bbdbb3a
  bbdbb10  mov rsi,[rsi]                                 
  bbdbb13  cmp rsi,r13                                   
  bbdbb16  je 0xBBDC0B1                                  ; -> loc_bbdc0b1
loc_bbdbb1c:  ; from bbdbb0b
  bbdbb1c  mov rdi,[rsi+0x10]                            
  bbdbb20  mov rbx,[rsi+0x18]                            
  bbdbb24  cmp rdi,rbx                                   
  bbdbb27  je short 0xBBDBB10                            ; -> loc_bbdbb10
  bbdbb29  lea r14,[rsi+0x28]                            
  bbdbb2d  jmp short 0xBBDBB3C                           ; -> loc_bbdbb3c
  bbdbb2f  nop                                           
loc_bbdbb30:  ; from bbdbb4f, bbdbb7f
  bbdbb30  add rdi,0xC8                                  
  bbdbb37  cmp rdi,rbx                                   
  bbdbb3a  je short 0xBBDBB10                            ; -> loc_bbdbb10
loc_bbdbb3c:  ; from bbdbb2d
  bbdbb3c  mov rax,[rdi]                                 
  bbdbb3f  not rax                                       
  bbdbb42  mov rcx,0x2000001000000                       
  bbdbb4c  test rax,rcx                                  
  bbdbb4f  jne short 0xBBDBB30                           ; -> loc_bbdbb30
  bbdbb51  mov rcx,[rbp-0x18]                            
  bbdbb55  test rcx,rcx                                  
  bbdbb58  je short 0xBBDBBA1                            ; -> loc_bbdbba1
  bbdbb5a  mov [rbp+0x248],rdi                           
  bbdbb61  mov [rbp+0x250],r14                           
  bbdbb68  mov rax,[rcx]                                 
  bbdbb6b  mov rax,[rax+0x10]                            
  bbdbb6f  lea rdx,[rbp+0x248]                           
  bbdbb76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdbb7c  nop                                           
  bbdbb7d  test al,al                                    
  bbdbb7f  je short 0xBBDBB30                           ; -> loc_bbdbb30
  bbdbb81  mov rcx,[rbp-0x18]                            
  bbdbb85  test rcx,rcx                                  
  bbdbb88  je short 0xBBDBBA1                            ; -> loc_bbdbba1
  bbdbb8a  lea rax,[rbp-0x50]                            
  bbdbb8e  cmp rcx,rax                                   
  bbdbb91  setne dl                                      
  bbdbb94  mov rax,[rcx]                                 
  bbdbb97  mov rax,[rax+0x20]                            
  bbdbb9b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_bbdbba1:  ; from bbdbb58, bbdbb88
  bbdbba1  mov rax,[rbp+0x228]                           
  bbdbba8  mov rsi,[rax+0xA10]                           
  bbdbbaf  mov rax,[rax+0xA78]                           
  bbdbbb6  mov rax,[rax]                                 
  bbdbbb9  cmp rsi,r13                                   
  bbdbbbc  je 0xBBDBCB0                                  ; -> loc_bbdbcb0
  bbdbbc2  mov rcx,rsi                                   
  bbdbbc5  xor edi,edi                                   
  bbdbbc7  mov r14,[rbp+0x2B8]                           
  bbdbbce  xchg ax,ax                                    
loc_bbdbbd0:  ; from bbdbbe9
  bbdbbd0  mov rdx,[rcx+0x18]                            
  bbdbbd4  sub rdx,[rcx+0x10]                            
  bbdbbd8  mov rcx,[rcx]                                 
  bbdbbdb  sar rdx,3                                     
  bbdbbdf  imul rdx,r15                                  
  bbdbbe3  add rdi,rdx                                   
  bbdbbe6  cmp rcx,r13                                   
  bbdbbe9  jne short 0xBBDBBD0                           ; -> loc_bbdbbd0
  bbdbbeb  mov rax,[rax+0x40]                            
  bbdbbef  mov [rbp+0x2C0],rax                           
  bbdbbf6  test rdi,rdi                                  
  bbdbbf9  mov r15,0x2000003003000                       
  bbdbc03  je 0xBBDBCD6                                  ; -> loc_bbdbcd6
  bbdbc09  mov rax,0xAAAAAAAAAAAAAAB                     
  bbdbc13  cmp rdi,rax                                   
```
; Outer stride-0x140 loop: rcx=[rbp+0x2B8]+0x140; rcx==r12 → loc_bbdc0da (done) [V bbdbada-add]. [rbp+0x2B8]=rcx; rax=rcx+0x128; [rbp-0x50]=global [data_f4409f0]; [rbp-0x48]=rax; [rbp-0x18]=rsi [V bbdbada-b00]. rsi=[r13] head node; empty → loc_bbdbac8; else loc_bbdbb1c [V bbdb404-0b]. loc_bbdbb10: rsi=[rsi] next; rsi==r13 → loc_bbdc0b1 [V bbdb410-16]. Inner 0xC8 record loop: rdi=[rsi+0x10] start, rbx=[rsi+0x18] end; empty → loc_bbdbb10 [V bbdb41c-27]. r14=rsi+0x28 [V bbdb429]. loc_bbdbb30: rdi+=0xC8 (0xC8-byte record stride); rdi==rbx → loc_bbdbb10 [V bbdb430-3a]. loc_bbdbb3c: rax=[rdi] (valid mask u64); not rax; test rax, 0x2000001000000; nonzero → skip record → loc_bbdbb30 [V bbdb43c-4f]. rcx=[rbp-0x18]; null → loc_bbdbba1 [V bbdb451-58]. [rbp+0x248]=rdi (record), [rbp+0x250]=r14 [V bbdb45a-61]. rax=[rcx]; rax=[rax+0x10]; rdx=&[rbp+0x248]; call sub_eea6040; al==0 → skip [V bbdb468-7f]. rcx=[rbp-0x18]; null → loc_bbdbba1 [V bbdb481-88]. rax=&[rbp-0x50]; dl=(rcx!=&[rbp-0x50]); rax=[rcx]; rax=[rax+0x20]; call sub_eea6040 [V bbdb48a-9b]. loc_bbdbba1: rax=[rbp+0x228]; rsi=[rax+0xA10]; rax=[rax+0xA78]; rax=[rax]; rsi==r13 → loc_bbdbcb0 [V bbdb4a1-bc]. sum loop: rcx=rsi, edi=0, r14=[rbp+0x2B8] [V bbdb4c2-ce]. loc_bbdbbd0: rdx=[rcx+0x18]-[rcx+0x10]; rcx=[rcx]; rdx>>=3; rdx*=r15 (magic); rdi+=rdx; until rcx==r13 [V bbdb4d0-e9]. [rbp+0x2C0]=[rax+0x40] pool obj [V bbdb4eb-ef]. test rdi; zero → loc_bbdbcd6 [V bbdb4f6-03]. r15=0x2000003003000 (valid-mask filter constant) [V bbdb4f9]. rax=0xAAAAAAAAAAAAAAB (magic /3); rdi>=that → loc_bbdcd7a [V bbdb409-13].

### Phase 35: 0xbbdbc13..0xbbdbcdb — pool alloc + release + slot write + sum loop
```
  bbdbc13  cmp rdi,rax                                   
  bbdbc16  jae 0xBBDCD7A                                 ; -> loc_bbdcd7a
  bbdbc1c  lea rax,[rdi*8]                               
  bbdbc24  lea r8,[rax+rax*2]                            
  bbdbc28  mov rax,[rbp+0x2C0]                           
  bbdbc2f  mov rcx,[rax]                                 
  bbdbc32  mov r9d,1                                     
  bbdbc38  lea rdx,[rbp+0x248]                           
  bbdbc3f  call 0xA78940                                 ; -> sub_a78940
  bbdbc44  nop                                           
  bbdbc45  mov rbx,[rbp+0x258]                           
  bbdbc4c  mov rax,[rbp+0x248]                           
  bbdbc53  mov rsi,[rbp+0x250]                           
  bbdbc5a  mov r12,[rax]                                 
  bbdbc5d  test rsi,rsi                                  
  bbdbc60  je short 0xBBDBC90                            ; -> loc_bbdbc90
  bbdbc62  lock dec dword ptr [rsi+8]                    
  bbdbc66  jne short 0xBBDBC90                           ; -> loc_bbdbc90
  bbdbc68  mov rax,[rsi]                                 
  bbdbc6b  mov rax,[rax]                                 
  bbdbc6e  mov rcx,rsi                                   
  bbdbc71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdbc77  lock dec dword ptr [rsi+0xC]                  
  bbdbc7b  jne short 0xBBDBC90                           ; -> loc_bbdbc90
  bbdbc7d  mov rax,[rsi]                                 
  bbdbc80  mov rax,[rax+8]                               
  bbdbc84  mov rcx,rsi                                   
  bbdbc87  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdbc8d  nop [rax]                                     
loc_bbdbc90:  ; from bbdbc60, bbdbc66, bbdbc7b
  bbdbc90  add r12,rbx                                   
  bbdbc93  lea rax,[rdi+rdi*2]                           
  bbdbc97  lea rdi,[r12+rax*8]                           
  bbdbc9b  mov rsi,[r13]                                 
  bbdbc9f  jmp short 0xBBDBCDB                           ; -> loc_bbdbcdb
  bbdbca1  nop [rax+rax]                                 
loc_bbdbcb0:  ; from bbdbbbc
  bbdbcb0  mov rax,[rax+0x40]                            
  bbdbcb4  mov [rbp+0x2C0],rax                           
  bbdbcbb  xor edi,edi                                   
  bbdbcbd  xor r12d,r12d                                 
  bbdbcc0  mov r14,[rbp+0x2B8]                           
  bbdbcc7  mov rax,r13                                   
  bbdbcca  mov r15,0x2000003003000                       
  bbdbcd4  jmp short 0xBBDBCDE                           ; -> loc_bbdbcde
loc_bbdbcd6:  ; from bbdbc03
  bbdbcd6  xor edi,edi                                   
  bbdbcd8  xor r12d,r12d                                 
loc_bbdbcdb:  ; from bbdbc9f
  bbdbcdb  mov rax,r13                                   
```
; rdi (record sum) < magic /3 → alloc via sub_a78940(rcx=[rbp+0x2C0] pool obj [rax+0x0], rdx=&[rbp+0x248], r8=rdi=count, r9d=1) → rax=rsi [V bbdb413-44]. rbx=[rbp+0x258] (prev result base); rax=[rbp+0x248]; rsi=[rbp+0x250] (old object to release); r12=[rax] (alloc result stored in obj field) [V bbdb44c-5a]. Release rsi: two-stage lock-dec refcount [+8 then +0xC] with vtable releases [rax]/[rax+8]; zero → loc_bbdbc90 [V bbdb45d-8d]. loc_bbdbc90: r12 += rbx (new running total); rdi = r12 + rdi*24 ([rdi+rdi*2]*8 = rdi*24) = end cursor [V bbdb490-97]. rsi=[r13] head; jmp loc_bbdbcdb [V bbdb49b-9f]. loc_bbdbcb0: empty-sum path: rax=[rax+0x40] pool obj → [rbp+0x2C0]; r13=0, r15=0, r14=[rbp+0x2B8], rax=r13 [V bbdb4b0-d4]. loc_bbdbcd6: rdi=0, r13=0 [V bbdbcd6-8]. loc_bbdbcdb: rax=r13 (end) [V bbdbcdb].

### Phase 36: 0xbbdbcdb..0xbbdbee0 — output slot write + record filter + sub_eec6de0 + advance
```
loc_bbdbcde:  ; from bbdbcd4
  bbdbcde  mov r13,r12                                   
  bbdbce1  cmp rsi,rax                                   
  bbdbce4  jne short 0xBBDBD00                           ; -> loc_bbdbd00
  bbdbce6  jmp 0xBBDBAB0                                 ; -> sub_bbdbab0
loc_bbdbd00:  ; from bbdbce4
  bbdbd00  mov rbx,[rsi+0x10]                            
  bbdbd04  mov r8,[rsi+0x18]                             
  bbdbd08  cmp rbx,r8                                    
  bbdbd0b  je short 0xBBDBCF0                            ; -> loc_bbdbcf0
  bbdbd0d  lea rax,[rsi+0x28]                            
  bbdbd11  mov [rbp+0x288],rax                           
  bbdbd18  mov [rbp+0x240],r8                            
  bbdbd1f  mov [rbp+0x218],rsi                           
  bbdbd26  jmp short 0xBBDBD5C                           ; -> loc_bbdbd5c
  bbdbd28  nop [rax+rax]                                 
loc_bbdbd30:  ; from bbdbd6c, bbdbd7f, bbdbd8b, bbdbdaa
  bbdbd30  cmp r13,rdi                                   
  bbdbd33  je short 0xBBDBDAE                            ; -> loc_bbdbdae
  bbdbd35  mov qword ptr [r13],0                         
  bbdbd3d  mov [r13+8],rbx                               
  bbdbd41  mov rax,[rbp+0x288]                           
  bbdbd48  mov [r13+0x10],rax                            
  bbdbd4c  add r13,0x18                                  
loc_bbdbd50:  ; from bbdbd68, bbdbdac, bbdbed7
  bbdbd50  add rbx,0xC8                                  
  bbdbd57  cmp rbx,r8                                    
  bbdbd5a  je short 0xBBDBCF0                            ; -> loc_bbdbcf0
loc_bbdbd5c:  ; from bbdbd26
  bbdbd5c  mov rax,[rbx]                                 
  bbdbd5f  mov rcx,rax                                   
  bbdbd62  not rcx                                       
  bbdbd65  test rcx,r15                                  
  bbdbd68  jne short 0xBBDBD50                           ; -> loc_bbdbd50
  bbdbd6a  test al,1                                     
  bbdbd6c  je short 0xBBDBD30                            ; -> loc_bbdbd30
  bbdbd6e  mov rcx,[r14+0x128]                           
  bbdbd75  mov rdx,[r14+0x130]                           
  bbdbd7c  cmp rcx,rdx                                   
  bbdbd7f  je short 0xBBDBD30                            ; -> loc_bbdbd30
  bbdbd81  mov rax,[rsi+0x8B0]                           
  bbdbd88  test rax,rax                                  
  bbdbd8b  je short 0xBBDBD30                            ; -> loc_bbdbd30
  bbdbd8d  movzx r8d,word ptr [rbx+0x10]                 
  bbdbd92  movzx r8d,word ptr [rax+r8*2]                 
  bbdbd97  call 0xE93B480                                ; -> sub_e93b480
  bbdbd9c  mov r8,[rbp+0x240]                            
  bbdbda3  cmp rax,[r14+0x130]                           
  bbdbdaa  jne short 0xBBDBD30                           ; -> loc_bbdbd30
  bbdbdac  jmp short 0xBBDBD50                           ; -> loc_bbdbd50
```
; loc_bbdbcde: r13=r12 (output cursor); rsi==rax → jmp loc_bbdbab0 (outer next) [V bbdbcdb-ce]. rsi!=rax → loc_bbdbd00 [V bbdbce1-e4]. loc_bbdbd00: rbx=[rsi+0x10] start, r8=[rsi+0x18] end; empty → loc_bbdbcf0 [V bbdbd00-0b]. rax=rsi+0x28; [rbp+0x288]=rax (slot base), [rbp+0x240]=r8 (end), [rbp+0x218]=rsi (node) [V bbdbd0d-1f]. jmp loc_bbdbd5c [V bbdbd26]. loc_bbdbd30: r13==rdi → loc_bbdbdae (flush) [V bbdbd30-33]. [r13]=0, [r13+8]=rbx (count), [r13+0x10]=[rbp+0x288] slot base; r13+=0x18 [V bbdbd35-4c]. loc_bbdbd50: rbx+=0xC8 (0xC8-byte stride); rbx==r8 → loc_bbdbcf0 [V bbdbd50-5a]. loc_bbdbd5c: rax=[rbx] (record mask); rcx=~rax; test rcx,r15 (0x2000003003000); nonzero → skip [V bbdbd5c-68]. test al,1; zero → loc_bbdbd30 [V bbdbd6a-6c]. rcx=[r14+0x128], rdx=[r14+0x130]; rcx==rdx → skip [V bbdbd6e-7f]. rax=[rsi+0x8B0]; null → skip [V bbdbd81-8b]. r8d=u16[rbx+0x10]; r8d=u16[rax+r8*2] (lookup); sub_e93b480() → rax [V bbdbd8d-97]. r8=[rbp+0x240]; rax==[r14+0x130]? else skip → loc_bbdbd30 [V bbdbd9c-da]. else jmp loc_bbdbd50 (record matched, keep scanning) [V bbdbdac].

### Phase 37: 0xbbdbdae..0xbbdbee0 — flush output slots + copy + advance
```
loc_bbdbdae:  ; from bbdbd33
  bbdbdae  mov r15,r12                                   
  bbdbdb1  sub r13,r12                                   
  bbdbdb4  mov rax,r13                                   
  bbdbdb7  sar rax,3                                     
  bbdbdbb  mov rcx,0xAAAAAAAAAAAAAAAB                    
  bbdbdc5  imul rax,rcx                                  
  bbdbdc9  lea r14,[rax+1]                               
  bbdbdcd  mov r12,rax                                   
  bbdbdd0  shr r12,1                                     
  bbdbdd3  mov rdx,0xAAAAAAAAAAAAAAA                     
  bbdbddd  mov rcx,rdx                                   
  bbdbde0  sub rcx,r12                                   
  bbdbde3  add r12,rax                                   
  bbdbde6  cmp r12,r14                                   
  bbdbde9  cmovbe r12,r14                                
  bbdbded  cmp rax,rcx                                   
  bbdbdf0  cmova r12,rdx                                 
  bbdbdf4  lea rax,[r12*8]                               
  bbdbdfc  lea r8,[rax+rax*2]                            
  bbdbe00  mov rax,[rbp+0x2C0]                           
  bbdbe07  mov rcx,[rax]                                 
  bbdbe0a  mov r9d,1                                     
  bbdbe10  lea rdx,[rbp+0x248]                           
  bbdbe17  call 0xA78940                                 ; -> sub_a78940
  bbdbe1c  nop                                           
  bbdbe1d  mov rcx,[rbp+0x258]                           
  bbdbe24  mov rax,[rbp+0x248]                           
  bbdbe2b  mov rdi,[rbp+0x250]                           
  bbdbe32  mov rsi,[rax]                                 
  bbdbe35  test rdi,rdi                                  
  bbdbe38  je short 0xBBDBE7A                            ; -> loc_bbdbe7a
  bbdbe3a  lock dec dword ptr [rdi+8]                    
  bbdbe3e  jne short 0xBBDBE7A                           ; -> loc_bbdbe7a
  bbdbe40  mov rax,[rdi]                                 
  bbdbe43  mov rax,[rax]                                 
  bbdbe46  mov [rbp+0x290],rcx                           
  bbdbe4d  mov rcx,rdi                                   
  bbdbe50  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdbe56  mov rcx,[rbp+0x290]                           
  bbdbe5d  lock dec dword ptr [rdi+0xC]                  
  bbdbe61  jne short 0xBBDBE7A                           ; -> loc_bbdbe7a
  bbdbe63  mov rax,[rdi]                                 
  bbdbe66  mov rax,[rax+8]                               
  bbdbe6a  mov rcx,rdi                                   
  bbdbe6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdbe73  mov rcx,[rbp+0x290]                           
loc_bbdbe7a:  ; from bbdbe38, bbdbe3e, bbdbe61
  bbdbe7a  add rsi,rcx                                   
  bbdbe7d  mov qword ptr [r13+rsi],0                     
  bbdbe86  mov [r13+rsi+8],rbx                           
  bbdbe8b  mov rax,[rbp+0x288]                           
  bbdbe92  mov [r13+rsi+0x10],rax                        
  bbdbe97  mov rcx,rsi                                   
  bbdbe9a  mov rdx,r15                                   
  bbdbe9d  mov r8,r13                                    
  bbdbea0  call 0xEEC6DE0                                ; -> sub_eec6de0
  bbdbea5  lea rax,[r14+r14*2]                           
  bbdbea9  lea r13,[rsi+rax*8]                           
  bbdbad  lea rax,[r12+r12*2]                           
  bbdbeb1  lea rdi,[rsi+rax*8]                           
  bbdbeb5  mov r12,rsi                                   
  bbdbeb8  mov r14,[rbp+0x2B8]                           
  bbdbebf  mov r15,0x2000003003000                       
  bbdbec9  mov rsi,[rbp+0x218]                           
  bbdbed0  mov r8,[rbp+0x240]                            
  bbdbed7  jmp 0xBBDBD50                                 ; -> sub_bbdbd50
```
; loc_bbdbdae: r15=r12 (old output start); r13-r12 = bytes written; rax=(r13-r12)>>3; *0xAAAAAAAAAAAAAAAB (magic /3) → count of 24-byte slots; bounds-check: r14=rax+1; r12 clamped between rax/2 and 0xAAAAAAAAAAAAAAA [V bbdbdae-df0]. rax=r12*8; r8=rax+rax*2 = r12*24 [V bbdbdf4-dfc]. sub_a78940(rcx=[rbp+0x2C0] pool obj [rax+0x0], rdx=&[rbp+0x248], r8=r12=count, r9d=1) → rax=rsi [V bbdb400-1c]. rcx=[rbp+0x258]; rax=[rbp+0x248]; rdi=[rbp+0x250] (old obj); rsi=[rax] new result; release rdi two-stage [V bbdb41d-73]. loc_bbdbe7a: rsi+=rcx (offset); [r13+rsi]=0, [r13+rsi+8]=rbx (count), [r13+rsi+0x10]=[rbp+0x288] slot base [V bbdb7a-92]. sub_eec6de0(rcx=rsi=dst off, rdx=r15=old base, r8=r13) [V bbdb97-a0]. Advance: rax=r14+r14*2=r14*24; r13=rsi+rax*8 (new output cursor); rax=r12+r12*2=r12*24; rdi=rsi+rax*8 (end); r12=rsi (new start); r14=[rbp+0x2B8] (outer idx); r15=filter; rsi=[rbp+0x218] node; r8=[rbp+0x240] end; jmp loc_bbdbd50 (continue record scan) [V bbdbad-bed7].

### Phase 42: 0xbbdc433..0xbbdc577 — fifth outer stride loop + inner record loop setup
  bbdc37b  cmp rax,0xD                                   
  bbdc37f  jb short 0xBBDC3C4                            ; -> loc_bbdc3c4
  bbdc381  mov r14,rdi                                   
  bbdc384  or r14,0x27                                   
  bbdc388  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdc38f  mov rax,[rcx]                                 
  bbdc392  mov rax,[rax+8]                               
  bbdc396  mov rdx,r14                                   
  bbdc399  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdc39f  nop                                           
  bbdc3a0  mov rsi,rax                                   
  bbdc3a3  test rax,rax                                  
  bbdc3a6  je 0xBBDCD24                                  ; -> loc_bbdcd24
loc_bbdc3ac:  ; from bbdcd2d
  bbdc3ac  mov rax,rsi                                   
  bbdc3af  add rsi,0x27                                  
  bbdc3b3  and rsi,0xFFFFFFFFFFFFFFE0                    
  bbdc3b7  mov [rsi-8],rax                               
  bbdc3bb  jmp short 0xBBDC3E8                           ; -> loc_bbdc3e8
loc_bbdc3bd:  ; from bbdc354
  bbdc3bd  xor r12d,r12d                                 
  bbdc3c0  xor ecx,ecx                                   
  bbdc3c2  jmp short 0xBBDC433                           ; -> loc_bbdc433
loc_bbdc3c4:  ; from bbdc37f
  bbdc3c4  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdc3cb  mov rax,[rcx]                                 
  bbdc3ce  mov rax,[rax+8]                               
  bbdc3d2  mov rdx,rdi                                   
  bbdc3d5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdc3db  nop                                           
  bbdc3dc  mov rsi,rax                                   
  bbdc3df  test rax,rax                                  
  bbdc3e2  je 0xBBDCD32                                  ; -> loc_bbdcd32
loc_bbdc3e8:  ; from bbdc3bb, bbdcd3d
  bbdc3e8  mov [rbp+0x1A0],rsi                           
  bbdc3ef  mov [rbp+0x1A8],rsi                           
  bbdc3f6  add rdi,rsi                                   
  bbdc3f9  mov [rbp+0x1B0],rdi                           
  bbdc400  mov rcx,[rbp+0x2A0]                           
  bbdc407  mov rdx,[rbp+0x2A8]                           
  bbdc40e  lea r9,[rbp+0x1A0]                            
  bbdc415  mov r8,rsi                                    
  bbdc418  call 0xBC06200                                ; -> sub_bc06200
  bbdc41d  nop                                           
  bbdc41e  mov r12,rax                                   
  bbdc421  mov [rbp+0x1A8],rax                           
  bbdc428  mov rcx,[rbp+0x1A0]                           
  bbdc42f  lea rsi,[rbp-0x50]                            
loc_bbdc433:  ; from bbdc3c2
  bbdc433  mov rax,[rbp+0x238]                           
  bbdc43a  mov rax,[rax]                                 
  bbdc43d  mov [rbp+0x228],rax                           
  bbdc444  add rax,0xA10                                 
  bbdc44a  mov [rbp+0x298],rax                           
  bbdc451  mov r13,0x100000001000000                     
  bbdc45b  mov [rbp+0x230],r12                           
  bbdc462  jmp short 0xBBDC4A4                           ; -> loc_bbdc4a4
```
; rax(quotient) >= 0x13 → alloc size = r14 | 0x27; else zero-count path [V bbdc37b-c2]. Alloc via sub_eea6040 → rsi; null → loc_bbdcd24/bbdcd32 [V bbdc388-e2]. loc_bbdc3ac: align-up-32, store orig rax at [rsi-8], jmp loc_bbdc3e8 [V bbdc3ac-bb]. loc_bbdc3e8: [rbp+0x1A0/0x1A8]=rsi (alloc result); rdi=rsi+rdi (end cursor) → [rbp+0x1B0] [V bbdc3e8-f9]. sub_bc06200(rcx=[rbp+0x2A0], rdx=[rbp+0x2A8], r8=rsi, r9=&[rbp+0x1A0]) → rax=r12, [rbp+0x1A8]=rax; rcx=[rbp+0x1A0]; rsi=rbp-0x50 [V bbdc400-2f]. Outer setup: [rbp+0x228]=[a1] deref; r13=[a1]+0xA10 array base; [rbp+0x230]=r12; [rbp+0x298]=r13; jmp loc_bbdc4a4 [V bbdc433-62].

### Phase 43: 0xbbdc577..0xbbdc6d8 — sum loop + pool alloc + release
  bbdc4a4  cmp rcx,r12                                   
  bbdc4a7  je 0xBBDCAFE                                  ; -> loc_bbdcafe
  bbdc4ad  mov [rbp+0x2B8],rcx                           
  bbdc4b4  lea rax,[rcx+0x128]                           
  bbdc4bb  lea rcx,[0xF440A20]                           ; [data_f440a20]
  bbdc4c2  mov [rbp-0x50],rcx                            
  bbdc4c6  mov [rbp-0x48],rax                            
  bbdc4ca  mov [rbp-0x18],rsi                            
  bbdc4ce  mov rax,[rbp+0x298]                           
  bbdc4d5  mov rsi,[rax]                                 
  bbdc4d8  cmp rsi,rax                                   
  bbdc4db  jne short 0xBBDC4F7                           ; -> loc_bbdc4f7
  bbdc4dd  jmp short 0xBBDC492                           ; -> sub_bbdc492
loc_bbdc4e0:  ; from bbdc502, bbdc51a
  bbdc4e0  mov rsi,[rsi]                                 
  bbdc4e3  cmp rsi,[rbp+0x298]                           
  bbdc4ea  mov rbx,[rbp+0x220]                           
  bbdc4f1  je 0xBBDCAD5                                  ; -> loc_bbdcad5
loc_bbdc4f7:  ; from bbdc4db
  bbdc4f7  mov rdi,[rsi+0x10]                            
  bbdc4fb  mov rbx,[rsi+0x18]                            
  bbdc4ff  cmp rdi,rbx                                   
  bbdc502  je short 0xBBDC4E0                            ; -> loc_bbdc4e0
  bbdc504  lea r14,[rsi+0x28]                            
  bbdc508  jmp short 0xBBDC51C                           ; -> loc_bbdc51c
loc_bbdc510:  ; from bbdc525, bbdc555
  bbdc510  add rdi,0xC8                                  
  bbdc517  cmp rdi,rbx                                   
  bbdc51a  je short 0xBBDC4E0                            ; -> loc_bbdc4e0
loc_bbdc51c:  ; from bbdc508
  bbdc51c  mov rax,[rdi]                                 
  bbdc51f  not rax                                       
  bbdc522  test rax,r13                                  
  bbdc525  jne short 0xBBDC510                           ; -> loc_bbdc510
loc_bbdc527:  ; from bbdc52e, bbdc55e
  bbdc527  mov rcx,[rbp-0x18]                            
  bbdc52b  test rcx,rcx                                  
  bbdc52e  je short 0xBBDC577                            ; -> loc_bbdc577
  bbdc530  mov [rbp+0x248],rdi                           
  bbdc537  mov [rbp+0x250],r14                           
  bbdc53e  mov rax,[rcx]                                 
  bbdc541  mov rax,[rax+0x10]                            
  bbdc545  lea rdx,[rbp+0x248]                           
  bbdc54c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdc552  nop                                           
  bbdc553  test al,al                                    
  bbdc555  je short 0xBBDC510                           ; -> loc_bbdc510
  bbdc557  mov rcx,[rbp-0x18]                            
  bbdc55b  test rcx,rcx                                  
  bbdc55e  je short 0xBBDC577                            ; -> loc_bbdc577
  bbdc560  lea rax,[rbp-0x50]                            
  bbdc564  cmp rcx,rax                                   
  bbdc567  setne dl                                      
  bbdc56a  mov rax,[rcx]                                 
  bbdc56d  mov rax,[rax+0x20]                            
  bbdc571  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_bbdc577:  ; from bbdc52e, bbdc55e
  bbdc577  mov rax,[rbp+0x228]                           
  bbdc57e  mov rdi,[rax+0xA10]                           
  bbdc585  mov rax,[rax+0xA78]                           
  bbdc58c  mov rax,[rax]                                 
  bbdc58f  mov r12,[rbp+0x298]                           
  bbdc596  cmp rdi,r12                                   
  bbdc599  je 0xBBDC6A0                                  ; -> loc_bbdc6a0
  bbdc59f  mov rcx,rdi                                   
  bbdc5a2  xor ebx,ebx                                   
  bbdc5a4  mov r14,[rbp+0x2B8]                           
  bbdc5ab  mov rsi,0x100000003003000                     
loc_bbdc5c0:  ; from bbdc5d9
  bbdc5c0  mov rdx,[rcx+0x18]                            
  bbdc5c4  sub rdx,[rcx+0x10]                            
  bbdc5c8  mov rcx,[rcx]                                 
  bbdc5cb  sar rdx,3                                     
  bbdc5cf  imul rdx,r15                                  
  bbdc5d3  add rbx,rdx                                   
  bbdc5d6  cmp rcx,r12                                   
  bbdc5d9  jne short 0xBBDC5C0                           ; -> loc_bbdc5c0
  bbdc5db  mov rax,[rax+0x40]                            
  bbdc5df  mov [rbp+0x2C0],rax                           
  bbdc5e6  test rbx,rbx                                  
  bbdc5e9  je 0xBBDC6C7                                  ; -> loc_bbdc6c7
  bbdc5ef  mov rax,0xAAAAAAAAAAAAAAB                     
  bbdc5f9  cmp rbx,rax                                   
  bbdc5fc  jae 0xBBDCD86                                 ; -> loc_bbdcd86
```
; Outer stride-0x140 loop: rcx=[rbp+0x2B8]+0x140; rcx==r12 → loc_bbdcafe (done) [V bbdc4a4-ad]. [rbp+0x2B8]=rcx; rax=rcx+0x128; [rbp-0x50]=global [data_f440a20]; [rbp-0x48]=rax; [rbp-0x18]=rsi [V bbdc4ad-ca]. rsi=[r13] head node; empty → loc_bbdc492; else loc_bbdc4f7 [V bbdc4d5-db]. loc_bbdc4e0: rsi=[rsi] next; rsi==[rbp+0x298] → loc_bbdcad5 [V bbdc4e0-ea]. Inner 0xC8 record loop: rdi=[rsi+0x10], rbx=[rsi+0x18]; empty → loc_bbdc4e0 [V bbdc4f7-02]. r14=rsi+0x28 [V bbdc504]. loc_bbdc510: rdi+=0xC8; rdi==rbx → loc_bbdc4e0 [V bbdc510-1a]. loc_bbdc51c: rax=[rdi] mask; not rax; test rax,r13 (0x100000001000000); nonzero → skip [V bbdc51c-25]. Record validation: rcx=[rbp-0x18]; if null → loc_bbdc577 [V bbdc527-2e]. [rbp+0x248]=rdi, [rbp+0x250]=r14; rax=[rcx]; rax=[rax+0x10]; rdx=&[rbp+0x248]; call sub_eea6040; al==0 → skip [V bbdc530-55]. rcx=[rbp-0x18]; if null → loc_bbdc577 [V bbdc557-5e]. rax=&[rbp-0x50]; dl=(rcx!=&[rbp-0x50]); rax=[rcx]; rax=[rax+0x20]; call sub_eea6040 [V bbdc560-71]. loc_bbdc577: rax=[rbp+0x228]; rdi=[rax+0xA10]; rax=[rax+0xA78]; rax=[rax]; r12=[rbp+0x298]; rdi==r12 → loc_bbdc6a0 [V bbdc577-99]. Sum loop: rcx=rdi, ebx=0, r14=[rbp+0x2B8], rsi=0x100000003003000 filter [V bbdc59f-ab]. loc_bbdc5c0: rdx=[rcx+0x18]-[rcx+0x10]; rcx=[rcx]; rdx>>=3; rdx*=rsi (magic); rbx+=rdx; until rcx==r12 [V bbdc5c0-d9]. [rbp+0x2C0]=[rax+0x40] pool obj [V bbdc5db-df]. test rbx; zero → loc_bbdc6c7 [V bbdc5e6-e9]. rax=0xAAAAAAAAAAAAAAB; rbx>=that → loc_bbdcd86 [V bbdc5ef-fc].

### Phase 44: 0xbbdc6d8..0xbbdc8e0 — advance + output slot write + record filter + copy + advance
  bbdc602  lea rax,[rbx*8]                               
  bbdc60a  lea r8,[rax+rax*2]                            
  bbdc60e  mov rax,[rbp+0x2C0]                           
  bbdc615  mov rcx,[rax]                                 
  bbdc618  mov r9d,1                                     
  bbdc61e  lea rdx,[rbp+0x248]                           
  bbdc625  call 0xA78940                                 ; -> sub_a78940
  bbdc62a  nop                                           
  bbdc62b  mov rdi,[rbp+0x258]                           
  bbdc632  mov rax,[rbp+0x248]                           
  bbdc639  mov rsi,[rbp+0x250]                           
  bbdc640  mov r15,[rax]                                 
  bbdc643  test rsi,rsi                                  
  bbdc646  je short 0xBBDC680                            ; -> loc_bbdc680
  bbdc648  lock dec dword ptr [rsi+8]                    
  bbdc64c  jne short 0xBBDC680                           ; -> loc_bbdc680
  bbdc64e  mov rax,[rsi]                                 
  bbdc651  mov rax,[rax]                                 
  bbdc654  mov rcx,rsi                                   
  bbdc657  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdc65d  lock dec dword ptr [rsi+0xC]                  
  bbdc661  jne short 0xBBDC680                           ; -> loc_bbdc680
  bbdc663  mov rax,[rsi]                                 
  bbdc666  mov rax,[rax+8]                               
  bbdc66a  mov rcx,rsi                                   
  bbdc66d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_bbdc680:  ; from bbdc646, bbdc64c, bbdc661
  bbdc680  add r15,rdi                                   
  bbdc683  lea rax,[rbx+rbx*2]                           
  bbdc687  lea r13,[r15+rax*8]                           
  bbdc68b  mov rdi,[r12]                                 
  bbdc68f  jmp short 0xBBDC6B8                           ; -> loc_bbdc6b8
loc_bbdc6a0:  ; from bbdc599
  bbdc6a0  mov rax,[rax+0x40]                            
  bbdc6a4  mov [rbp+0x2C0],rax                           
  bbdc6ab  xor r13d,r13d                                 
  bbdc6ae  xor r15d,r15d                                 
  bbdc6b1  mov r14,[rbp+0x2B8]                           
loc_bbdc6b8:  ; from bbdc68f
  bbdc6b8  mov rax,r12                                   
  bbdc6bb  mov rsi,0x100000003003000                     
  bbdc6c5  jmp short 0xBBDC6D0                           ; -> loc_bbdc6d0
loc_bbdc6c7:  ; from bbdc5e9
  bbdc6c7  xor r13d,r13d                                 
  bbdc6ca  xor r15d,r15d                                 
  bbdc6cd  mov rax,r12                                   
loc_bbdc6d0:  ; from bbdc6c5
  bbdc6d0  mov r12,r15                                   
  bbdc6d3  cmp rdi,rax                                   
  bbdc6d6  jne short 0xBBDC6F0                           ; -> loc_bbdc6f0
  bbdc6d8  jmp 0xBBDC470                                 ; -> sub_bbdc470
loc_bbdc470:  ; from bbdc6d8, bbdc8e3
  bbdc470  mov rbx,[rbp+0x220]                           
  bbdc477  mov r15,0x8F5C28F5C28F5C29                    
  bbdc481  mov r13,0x100000001000000                     
loc_bbdc48b:  ; from bbdc9fd
  bbdc48b  mov r12,[rbp+0x230]                           
loc_bbdc492:  ; from bbdc4dd, bbdcadc, bbdcaf9
  bbdc492  mov rcx,[rbp+0x2B8]                           
  bbdc499  add rcx,0x140                                 
  bbdc4a0  lea rsi,[rbp-0x50]                            
loc_bbdc6e0:  ; from bbdc6fb, bbdc74c
  bbdc6e0  mov rdi,[rdi]                                 
  bbdc6e3  cmp rdi,[rbp+0x298]                           
  bbdc6ea  je 0xBBDC8E0                                  ; -> loc_bbdc8e0
loc_bbdc6f0:  ; from bbdc6d6
  bbdc6f0  mov rbx,[rdi+0x10]                            
  bbdc6f4  mov r8,[rdi+0x18]                             
  bbdc6f8  cmp rbx,r8                                    
  bbdc6fb  je short 0xBBDC6E0                            ; -> loc_bbdc6e0
  bbdc6fd  lea rax,[rdi+0x28]                            
  bbdc701  mov [rbp+0x288],rax                           
  bbdc708  mov [rbp+0x240],r8                            
  bbdc70f  mov [rbp+0x218],rdi                           
  bbdc716  jmp short 0xBBDC74E                           ; -> loc_bbdc74e
loc_bbdc720:  ; from bbdc75e, bbdc771, bbdc77d, bbdc79c
  bbdc720  cmp r12,r13                                   
  bbdc723  je short 0xBBDC7A0                            ; -> loc_bbdc7a0
  bbdc725  mov qword ptr [r12],0                         
  bbdc72d  mov [r12+8],rbx                               
  bbdc732  mov rax,[rbp+0x288]                           
  bbdc739  mov [r12+0x10],rax                            
  bbdc73e  add r12,0x18                                  
loc_bbdc742:  ; from bbdc75a, bbdc79e, bbdc8cc
  bbdc742  add rbx,0xC8                                  
  bbdc749  cmp rbx,r8                                    
  bbdc74c  je short 0xBBDC6E0                            ; -> loc_bbdc6e0
loc_bbdc74e:  ; from bbdc716
  bbdc74e  mov rax,[rbx]                                 
  bbdc751  mov rcx,rax                                   
  bbdc754  not rcx                                       
  bbdc757  test rcx,rsi                                  
  bbdc75a  jne short 0xBBDC742                           ; -> loc_bbdc742
  bbdc75c  test al,1                                     
  bbdc75e  je short 0xBBDC720                            ; -> loc_bbdc720
  bbdc760  mov rcx,[r14+0x128]                           
  bbdc767  mov rdx,[r14+0x130]                           
  bbdc76e  cmp rcx,rdx                                   
  bbdc771  je short 0xBBDC720                            ; -> loc_bbdc720
  bbdc773  mov rax,[rdi+0x8B0]                           
  bbdc77a  test rax,rax                                  
  bbdc77d  je short 0xBBDC720                            ; -> loc_bbdc720
  bbdc77f  movzx r8d,word ptr [rbx+0x10]                 
  bbdc784  movzx r8d,word ptr [rax+r8*2]                 
  bbdc789  call 0xE93B480                                ; -> sub_e93b480
  bbdc78e  mov r8,[rbp+0x240]                            
  bbdc795  cmp rax,[r14+0x130]                           
  bbdc79c  jne short 0xBBDC720                           ; -> loc_bbdc720
  bbdc79e  jmp short 0xBBDC742                           ; -> loc_bbdc742
loc_bbdc7a0:  ; from bbdc723
  bbdc7a0  mov r14,r15                                   
  bbdc7a3  sub r12,r15                                   
  bbdc7a6  mov rax,r12                                   
  bbdc7a9  sar rax,3                                     
  bbdc7ad  mov rcx,0xAAAAAAAAAAAAAAAB                    
  bbdc7b7  imul rax,rcx                                  
  bbdc7bb  lea rdi,[rax+1]                               
  bbdc7bf  mov r15,rax                                   
  bbdc7c2  shr r15,1                                     
  bbdc7c5  mov rdx,0xAAAAAAAAAAAAAAA                     
  bbdc7cf  mov rcx,rdx                                   
  bbdc7d2  sub rcx,r15                                   
  bbdc7d5  add r15,rax                                   
  bbdc7d8  cmp r15,rdi                                   
  bbdc7db  cmovbe r15,rdi                                
  bbdc7df  cmp rax,rcx                                   
  bbdc7e2  cmova r15,rdx                                 
  bbdc7e6  lea rax,[r15*8]                               
  bbdc7ee  lea r8,[rax+rax*2]                            
  bbdc7f2  mov rax,[rbp+0x2C0]                           
  bbdc7f9  mov rcx,[rax]                                 
  bbdc7fc  mov r9d,1                                     
  bbdc802  lea rdx,[rbp+0x248]                           
  bbdc809  call 0xA78940                                 ; -> sub_a78940
  bbdc80e  nop                                           
  bbdc80f  mov rcx,[rbp+0x258]                           
  bbdc816  mov rax,[rbp+0x248]                           
  bbdc81d  mov r13,[rbp+0x250]                           
  bbdc824  mov rsi,[rax]                                 
  bbdc827  test r13,r13                                  
  bbdc82a  je short 0xBBDC870                            ; -> loc_bbdc870
  bbdc82c  lock dec dword ptr [r13+8]                    
  bbdc831  jne short 0xBBDC870                           ; -> loc_bbdc870
  bbdc833  mov rax,[r13]                                 
  bbdc837  mov rax,[rax]                                 
  bbdc83a  mov [rbp+0x290],rcx                           
  bbdc841  mov rcx,r13                                   
  bbdc844  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdc84a  mov rcx,[rbp+0x290]                           
  bbdc851  lock dec dword ptr [r13+0xC]                  
  bbdc856  jne short 0xBBDC870                           ; -> loc_bbdc870
  bbdc858  mov rax,[r13]                                 
  bbdc85c  mov rax,[rax+8]                               
  bbdc860  mov rcx,r13                                   
  bbdc863  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_bbdc870:  ; from bbdc82a, bbdc831, bbdc856
  bbdc870  add rsi,rcx                                   
  bbdc873  mov qword ptr [r12+rsi],0                     
  bbdc87b  mov [r12+rsi+8],rbx                           
  bbdc880  mov rax,[rbp+0x288]                           
  bbdc887  mov [r12+rsi+0x10],rax                        
  bbdc88c  mov rcx,rsi                                   
  bbdc88f  mov rdx,r14                                   
  bbdc892  mov r8,r12                                    
  bbdc895  call 0xEEC6DE0                                ; -> sub_eec6de0
  bbdc89a  lea rax,[rdi+rdi*2]                           
  bbdc89e  lea r12,[rsi+rax*8]                           
  bbdc8a2  lea rax,[r15+r15*2]                           
  bbdc8a6  lea r13,[rsi+rax*8]                           
  bbdc8aa  mov r15,rsi                                   
  bbdc8ad  mov r14,[rbp+0x2B8]                           
  bbdc8b4  mov rsi,0x100000003003000                     
  bbdc8be  mov rdi,[rbp+0x218]                           
  bbdc8c5  mov r8,[rbp+0x240]                            
  bbdc8cc  jmp 0xBBDC742                                 ; -> loc_bbdc742
```
; sub_a78940(rcx=[rbp+0x2C0] pool obj [rax+0x0], rdx=&[rbp+0x248], r8=rdi=count, r9d=1) → rax=rsi [V bbdc602-2a]. rbx=[rbp+0x258]; rax=[rbp+0x248]; rsi=[rbp+0x250]; r15=[rax] alloc result; release rsi two-stage → loc_bbdc680 [V bbdc62b-673]. loc_bbdc680: r15+=rdi; rax=rbx+rbx*2=rbx*3; r13=r15+rax*8 (=r15+rbx*24) end cursor; rdi=[r12] head [V bbdc680-8f]. loc_bbdc6a0: empty path: rax=[rax+0x40] pool obj → [rbp+0x2C0]; r13=0, r15=0, r14=[rbp+0x2B8] [V bbdc6a0-b1]. loc_bbdc6b8: rax=r12, rsi=filter magic, jmp loc_bbdc6d0 [V bbdc6b8-c5]. loc_bbdc6c7: r13=0, r15=0, rax=r12 [V bbdc6c7-cd]. loc_bbdc6d0: r12=r15 (new start); cmp rdi,rax → jne loc_bbdc6f0; else jmp loc_bbdc470 (outer next iter) [V bbdc6d0-d8]. loc_bbdc470: rbx=[rbp+0x220]; r15=magic; r13=magic2; r12=[rbp+0x230] [V bbdc470-8b]. loc_bbdc6e0: rdi=[rdi] next node; rdi==[rbp+0x298] → loc_bbdc8e0 (outer done) [V bbdc6e0-ea]. loc_bbdc6f0: rbx=[rdi+0x10], r8=[rdi+0x18] record range; empty → loc_bbdc6e0 [V bbdc6f0-fb]. rax=rdi+0x28; [rbp+0x288]=rax, [rbp+0x240]=r8, [rbp+0x218]=rdi; jmp loc_bbdc74e [V bbdc6fd-16]. loc_bbdc720: r12==r13 → loc_bbdc7a0 (flush) [V bbdc720-23]. [r12]=0, [r12+8]=rbx (count), [r12+0x10]=[rbp+0x288] slot base; r12+=0x18 [V bbdc725-3e]. loc_bbdc742: rbx+=0xC8; rbx==r8 → loc_bbdc6e0 [V bbdc742-4c]. loc_bbdc74e: rax=[rbx] mask; not rax; test rcx,rsi; nonzero → skip [V bbdc74e-5a]. test al,1; zero → loc_bbdc720 [V bbdc75c-5e]. rcx=[r14+0x128], rdx=[r14+0x130]; equal → skip [V bbdc760-71]. rax=[rdi+0x8B0]; null → skip [V bbdc773-7d]. r8d=u16[rbx+0x10]; r8d=u16[rax+r8*2]; sub_e93b480() → rax [V bbdc77f-89]. r8=[rbp+0x240]; rax==[r14+0x130]? else skip → loc_bbdc720 [V bbdc78e-9c]. else jmp loc_bbdc742 (keep scanning) [V bbdc79e]. loc_bbdc7a0: r14=r15 (old output start); r12-r15 = bytes written; magic divide → count of slots [V bbdc7a0-df0]. sub_a78940 alloc → rax=rsi [V bbdc7f2-80e]. rcx=[rbp+0x258]; rax=[rbp+0x248]; r13=[rbp+0x250]; rsi=[rax] new result; release r13 two-stage → loc_bbdc870 [V bbdc80f-869]. loc_bbdc870: rsi+=rcx; [r12+rsi]=0, [r12+rsi+8]=rbx, [r12+rsi+0x10]=[rbp+0x288] [V bbdc870-87]. sub_eec6de0(rcx=rsi, rdx=r14, r8=r12) [V bbdc88c-95]. Advance: r13=rsi+rdi*24 (new cursor); rdi=rsi+r12*24 (end); r12=rsi (new start); r14=[rbp+0x2B8]; rsi=filter; rdi=[rbp+0x218]; r8=[rbp+0x240]; jmp loc_bbdc742 [V bbdc89a-8cc].

### Phase 45: 0xbbdc8e0..0xbbdc9de — outer exhausted + final flush + alloc + copy + advance
loc_bbdc8e0:  ; from bbdc6ea
  bbdc8e0  cmp r15,r12                                   
  bbdc8e3  je 0xBBDC470                                  ; -> sub_bbdc470
  bbdc8e9  mov rsi,r12                                   
  bbdc8ec  sub rsi,r15                                   
  bbdc8ef  mov r13,rsi                                   
  bbdc8f2  sar r13,3                                     
  bbdc8f6  mov rax,0xAAAAAAAAAAAAAAAB                    
  bbdc900  imul r13,rax                                  
  bbdc904  mov rcx,r15                                   
  bbdc907  mov rdx,r12                                   
  bbdc90a  mov r8,r13                                    
  bbdc90d  call 0x5689800                                ; -> sub_5689800
  bbdc912  nop                                           
  bbdc913  mov rbx,[rbp+0x220]                           
  bbdc91a  mov rax,0xAAAAAAAAAAAAAAB                     
  bbdc924  cmp r13,rax                                   
  bbdc927  jae 0xBBDCD8C                                 ; -> loc_bbdcd8c
  bbdc92d  mov rax,[rbp+0x2C0]                           
  bbdc934  mov rcx,[rax]                                 
  bbdc937  mov r9d,1                                     
  bbdc93d  lea rdx,[rbp+0x248]                           
  bbdc944  mov r8,rsi                                    
  bbdc947  call 0xA78940                                 ; -> sub_a78940
  bbdc94c  nop                                           
  bbdc94d  mov rdi,[rbp+0x258]                           
  bbdc954  mov rax,[rbp+0x248]                           
  bbdc95b  mov r13,[rbp+0x250]                           
  bbdc962  mov r12,[rax]                                 
  bbdc965  test r13,r13                                  
  bbdc968  je short 0xBBDC9A0                            ; -> loc_bbdc9a0
  bbdc96a  lock dec dword ptr [r13+8]                    
  bbdc96f  jne short 0xBBDC9A0                           ; -> loc_bbdc9a0
  bbdc971  mov rax,[r13]                                 
  bbdc975  mov rax,[rax]                                 
  bbdc978  mov rcx,r13                                   
  bbdc97b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdc981  lock dec dword ptr [r13+0xC]                  
  bbdc986  jne short 0xBBDC9A0                           ; -> loc_bbdc9a0
  bbdc988  mov rax,[r13]                                 
  bbdc98c  mov rax,[rax+8]                               
  bbdc990  mov rcx,r13                                   
  bbdc993  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_bbdc9a0:  ; from bbdc968, bbdc96f, bbdc986
  bbdc9a0  add r12,rdi                                   
  bbdc9a3  lea rdi,[r12+rsi]                             
  bbdc9a7  mov rcx,r12                                   
  bbdc9aa  mov rdx,r15                                   
  bbdc9ad  mov r8,rsi                                    
  bbdc9b0  call 0xEEC6DE0                                ; -> sub_eec6de0
  bbdc9b5  mov [rbp+0x120],r14                           
  bbdc9bc  jmp short 0xBBDCA03                           ; -> loc_bbdca03
```
; r15==r12 → jmp loc_bbdc470 (outer next iter) [V bbdc8e0-e3]. rsi=r12-r15 (remaining); r13=rsi>>3; *magic → count [V bbdc8e9-900]. sub_5689800(rcx=r15=dst, rdx=r12=src, r8=r13=count) — memmove [V bbdc904-12]. rbx=[rbp+0x220] [V bbdc913]. rax=0xAAAAAAAAAAAAAAB; r13>=that → loc_bbdcd8c [V bbdc91a-27]. sub_a78940(rcx=[rbp+0x2C0] pool obj [rax+0x0], rdx=&[rbp+0x248], r8=rsi=count, r9d=1) → rax=rsi [V bbdc92d-4c]. rdi=[rbp+0x258]; rax=[rbp+0x248]; r13=[rbp+0x250]; r12=[rax] new result; release r13 two-stage → loc_bbdc9a0 [V bbdc94d-93]. loc_bbdc9a0: r12+=rbx; rdi=r12+rsi end cursor; sub_eec6de0(rcx=r12, rdx=r15, r8=rsi=buffer) → copies entries [V bbdc9a0-b0]. [rbp+0x120]=r14 (save outer idx); jmp loc_bbdca03 [V bbdc9b5-bc].

### Phase 46: 0xbbdc9de..0xbbdcad5 — scan-and-match + sub_bc3a2f0 + return
loc_bbdca03:  ; from bbdc9bc
  bbdca03  mov rcx,[r12+8]                               
  bbdca08  test rcx,rcx                                  
  bbdca0b  je short 0xBBDCA21                            ; -> loc_bbdca21
  bbdca0d  mov rax,[r12+0x10]                            
  bbdca12  test rax,rax                                  
  bbdca15  je short 0xBBDCA21                            ; -> loc_bbdca21
  bbdca17  test byte ptr [rcx+1],0x20                    
  bbdca1b  jne 0xBBDCABC                                 ; -> loc_bbdcabc
loc_bbdca21:  ; from bbdca0b, bbdca15
  bbdca21  xor ecx,ecx                                   
loc_bbdca23:  ; from bbdcad0
  bbdca23  lea rax,[r12+0x18]                            
  bbdca28  mov rsi,rdi                                   
  bbdca2b  cmp rax,rdi                                   
  bbdca2e  je short 0xBBDCA83                            ; -> loc_bbdca83
  bbdca30  mov rcx,[rcx+0x78]                            
loc_bbdca40:  ; from bbdca6c
  bbdca40  mov rdx,[rax+8]                               
  bbdca44  mov r8,[rax+0x10]                             
  bbdca48  movzx edx,word ptr [rdx+0x2A]                 
  bbdca4c  mov r8,[r8+0x750]                             
  bbdca53  mov r9d,edx                                   
  bbdca56  shl r9d,7                                     
  bbdca5a  lea rdx,[r9+rdx*8]                            
  bbdca5e  cmp rcx,[r8+rdx+0x78]                         
  bbdca63  jne short 0xBBDCA80                           ; -> loc_bbdca80
  bbdca65  add rax,0x18                                  
  bbdca69  cmp rax,rdi                                   
  bbdca6c  jne short 0xBBDCA40                           ; -> loc_bbdca40
  bbdca6e  mov rsi,rdi                                   
  bbdca71  jmp short 0xBBDCA83                           ; -> loc_bbdca83
loc_bbdca80:  ; from bbdca63
  bbdca80  mov rsi,rax                                   
loc_bbdca83:  ; from bbdca71
  bbdca83  mov [rbp+0x248],r12                           
  bbdca8a  mov [rbp+0x250],rsi                           
  bbdca91  mov [rbp+0x258],r12                           
  bbdca98  lea rcx,[rbp+0x120]                           
  bbdca9f  lea rdx,[rbp+0x248]                           
  bbdcaa6  call 0xBC3A2F0                                ; -> sub_bc3a2f0
  bbdcaab  nop                                           
  bbdcaac  cmp r12,rsi                                   
  bbdcaaf  jne 0xBBDC9C0                                 ; -> sub_bbdc9c0
  bbdcab5  xor edx,edx                                   
  bbdcab7  jmp 0xBBDC9DE                                 ; -> sub_bbdc9de
loc_bbdcabc:  ; from bbdca1b
  bbdcabc  movzx ecx,word ptr [rcx+0x2A]                 
  bbdcac0  mov edx,ecx                                   
  bbdcac2  shl edx,7                                     
  bbdcac5  lea rcx,[rdx+rcx*8]                           
  bbdcac9  add rcx,[rax+0x750]                           ; R ret@bc3a2f0+0x750
  bbdcad0  jmp 0xBBDCA23                                 ; -> sub_bbdca23
loc_bbdcad5:  ; from bbdc4ea
  bbdcad5  mov rcx,[rbp-0x18]                            
  bbdcad9  test rcx,rcx                                  
  bbdcadc  je 0xBBDC492                                  ; -> sub_bbdc492
```
; loc_bbdca03: scan entries at r12; valid if ptr@+8 and val@+0x10 nonzero and byte [rcx+1]&0x20 → loc_bbdcabc; else ecx=0 [V bbdca03-21]. loc_bbdca23: walk slots step 0x18 from rax=r12+0x18 to rdi; u16=[rdx+0x2A]; r8=[r8+0x750] (pool table +0x750); r9d=u16<<7; rdx=r9+r8*8 (=u16*0x88); match if rcx==[r8+rdx+0x78] → rsi=rax, else rsi=rdi [V bbdcca30-6e]. [rbp+0x248/0x250/0x258]=r12/rsi/r12 (state); sub_bc3a2f0(rcx=[rbp+0x120]=saved outer idx, rdx=&[rbp+0x248]) → rsi [V bbdc98-a6]. If r12!=rsi → sub_bbdc9c0 (advance); else edx=0 → loc_bbdc9de [V bbdcac-ab7]. loc_bbdcabc: u16=[rcx+0x2A]<<7; rcx=rdx+rcx*8+[rax+0x750]; jmp loc_bbdca23 [V bbdcabc-d0]. **pool +0x750 stride-0x88 +0x78 compare**: same pattern.

### Phase 47: 0xbbdcad5..0xbbdcb92 — cleanup + sub_bbdd780
loc_bbdcad5:  ; from bbdc4ea
  bbdcad5  mov rcx,[rbp-0x18]                            
  bbdcad9  test rcx,rcx                                  
  bbdcadc  je 0xBBDC492                                  ; -> sub_bbdc492
  bbdcae2  lea rax,[rbp-0x50]                            
  bbdcae6  cmp rcx,rax                                   
  bbdcae9  setne dl                                      
  bbdcaec  mov rax,[rcx]                                 
  bbdcaef  mov rax,[rax+0x20]                            
  bbdcaf3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdcaf9  jmp 0xBBDC492                                 ; -> sub_bbdc492
loc_bbdcafe:  ; from bbdc4a7
  bbdcafe  lea rcx,[rbp+0x1A0]                           
  bbdcb05  call 0xBC06740                                ; -> sub_bc06740
  bbdcb0a  lea rcx,[rbp+0x2A0]                           
  bbdcb11  call 0xBC06740                                ; -> sub_bc06740
  bbdcb16  nop                                           
loc_bbdcb17:  ; from bbdc304
  bbdcb17  mov rcx,rbx                                   
  bbdcb1a  call 0xBBDD780                                ; -> sub_bbdd780
  bbdcb1f  nop                                           
  bbdcb20  mov rsi,[rbp+0x200]                           
  bbdcb27  test rsi,rsi                                  
  bbdcb2a  je short 0xBBDCB92                            ; -> loc_bbdcb92
  bbdcb2c  mov rdi,[rbp+0x208]                           
  bbdcb33  cmp rsi,rdi                                   
  bbdcb36  je short 0xBBDCB5B                            ; -> loc_bbdcb5b
```
; loc_bbdcad5: rcx=[rbp-0x18]; null → loc_bbdc492 (outer next iter) [V bbdcad5-dc]. rax=&[rbp-0x50]; dl=(rcx!=&[rbp-0x50]); rax=[rcx]; rax=[rax+0x20]; call sub_eea6040; jmp loc_bbdc492 [V bbdcad5-f9]. loc_bbdcafe: sub_bc06740(&[rbp+0x1A0]); sub_bc06740(&[rbp+0x2A0]) — cleanup both slot arrays [V bbdc b05-11]. loc_bbdcb17: sub_bbdd780(rcx=rbx=array base) [V bbdcb17-1f]. rsi=[rbp+0x200]; null → loc_bbdcb92 [V bbdcb20-2a]. rdi=[rbp+0x208] end; rsi==rdi → loc_bbdcb5b [V bbdcb2c-36].

### Phase 48: 0xbbdcb92..0xbbdcc92 — cleanup remaining slot arrays
loc_bbdcb40:  ; from bbdcb52
  bbdcb40  mov rcx,rsi                                   
  bbdcb43  call 0x5667e70                                ; -> sub_5667e70
  bbdcb48  add rsi,0x170                                 
  bbdcb4f  cmp rsi,rdi                                   
  bbdcb52  jne short 0xBBDCB40                           ; -> loc_bbdcb40
  bbdcb54  mov rsi,[rbp+0x200]                           
loc_bbdcb5b:  ; from bbdcb36
  bbdcb5b  mov rdx,[rbp+0x210]                           
  bbdcb62  sub rdx,rsi                                   
  bbdcb65  cmp rdx,0x1000                                
  bbdcb6c  jb short 0xBBDCB8A                            ; -> loc_bbdcb8a
  bbdcb6e  mov rax,[rsi-8]                               
  bbdcb72  add rsi,0xFFFFFFFFFFFFFFF8                    
  bbdcb76  sub rsi,rax                                   
  bbdcb79  cmp rsi,0x20                                  
  bbdcb7d  jae 0xBBDCD42                                 ; -> loc_bbdcd42
  bbdcb83  add rdx,0x27                                  
  bbdcb87  mov rsi,rax                                   
loc_bbdcb8a:  ; from bbdcb6c
  bbdcb8a  mov rcx,rsi                                   
  bbdcb8d  call 0xE935700                                ; -> sub_e935700
loc_bbdcb92:  ; from bbdcb2a
  bbdcb92  lea rcx,[rbp+0x140]                           
  bbdcb99  call 0xBC06740                                ; -> sub_bc06740
  bbdcb9e  mov rsi,[rbp+0x1E0]                           
  bbdcba5  test rsi,rsi                                  
  bbdcba8  je short 0xBBDCC12                            ; -> loc_bbdcc12
  bbdcbaa  mov rdi,[rbp+0x1E8]                           
  bbdcbb1  cmp rsi,rdi                                   
  bbdcbb4  je short 0xBBDCBDB                            ; -> loc_bbdcbdb
loc_bbdcbc0:  ; from bbdcbd2
  bbdcbc0  mov rcx,rsi                                   
  bbdcbc3  call 0x5667e70                                ; -> sub_5667e70
  bbdcbc8  add rsi,0x170                                 
  bbdcbcf  cmp rsi,rdi                                   
  bbdcbd2  jne short 0xBBDCBC0                           ; -> loc_bbdcbc0
  bbdcbd4  mov rsi,[rbp+0x1E0]                           
loc_bbdcbdb:  ; from bbdcbb4
  bbdcbdb  mov rdx,[rbp+0x1F0]                           
  bbdcbe2  sub rdx,rsi                                   
  bbdcbe5  cmp rdx,0x1000                                
  bbdcbec  jb short 0xBBDCC0A                            ; -> loc_bbdcc0a
  bbdcbee  mov rax,[rsi-8]                               
  bbdcbf2  add rsi,0xFFFFFFFFFFFFFFF8                    
  bbdcbf6  sub rsi,rax                                   
  bbdcbf9  cmp rsi,0x20                                  
  bbdcbfd  jae 0xBBDCD42                                 ; -> loc_bbdcd42
  bbdcc03  add rdx,0x27                                  
  bbdcc07  mov rsi,rax                                   
loc_bbdcc0a:  ; from bbdcbec
  bbdcc0a  mov rcx,rsi                                   
  bbdcc0d  call 0xE935700                                ; -> sub_e935700
loc_bbdcc12:  ; from bbdcba8
  bbdcc12  lea rcx,[rbp+0x128]                           
  bbdcc19  call 0xBC06740                                ; -> sub_bc06740
  bbdcc1e  mov rsi,[rbp+0x1C0]                           
  bbdcc25  test rsi,rsi                                  
  bbdcc28  je short 0xBBDCC92                            ; -> loc_bbdcc92
  bbdcc2a  mov rdi,[rbp+0x1C8]                           
  bbdcc31  cmp rsi,rdi                                   
  bbdcc34  je short 0xBBDCC5B                            ; -> loc_bbdcc5b
loc_bbdcc40:  ; from bbdcc52
  bbdcc40  mov rcx,rsi                                   
  bbdcc43  call 0x5667e70                                ; -> sub_5667e70
  bbdcc48  add rsi,0x170                                 
  bbdcc4f  cmp rsi,rdi                                   
  bbdcc52  jne short 0xBBDCC40                           ; -> loc_bbdcc40
  bbdcc54  mov rsi,[rbp+0x1C0]                           
loc_bbdcc5b:  ; from bbdcc34
  bbdcc5b  mov rdx,[rbp+0x1D0]                           
  bbdcc62  sub rdx,rsi                                   
  bbdcc65  cmp rdx,0x1000                                
  bbdcc6c  jb short 0xBBDCC8A                            ; -> loc_bbdcc8a
  bbdcc6e  mov rax,[rsi-8]                               
  bbdcc72  add rsi,0xFFFFFFFFFFFFFFF8                    
  bbdcc76  sub rsi,rax                                   
  bbdcc79  cmp rsi,0x20                                  
  bbdcc7d  jae 0xBBDCD42                                 ; -> loc_bbdcd42
  bbdcc83  add rdx,0x27                                  
  bbdcc87  mov rsi,rax                                   
loc_bbdcc8a:  ; from bbdcc6c
  bbdcc8a  mov rcx,rsi                                   
  bbdcc8d  call 0xE935700                                ; -> sub_e935700
```
; Slot array cleanup pattern (repeated for [rbp+0x200]/[rbp+0x208], [rbp+0x1E0]/[rbp+0x1E8], [rbp+0x1C0]/[rbp+0x1C8]): cursor vs end stride 0x170; sub_5667e70(slot) + cursor+=0x170 until done [V bbdcb40-54]. Used = end-cursor; <0x1000 → slack path sub_e935700 [V bbdcb5b-8d]. rax=[cursor-8]; slack=(cursor-8)-rax; <0x20 → loc_bbdcd42 (crash); else add rdx,0x27 → sub_e935700 [V bbdcb83-d]. sub_bc06740 cleanup [V bbdcb92-99]. Repeated identically for third array at [rbp+0x1C0] [V bbdcb9e-8d].

### Phase 49: 0xbbdcc92..0xbbdccd4 — release object + epilogue
loc_bbdcc92:  ; from bbdcc28
  bbdcc92  mov rax,[rbp+0x238]                           
  bbdcc99  mov rsi,[rax+8]                               
  bbdcc9d  test rsi,rsi                                  
  bbdcca0  je short 0xBBDCCCD                            ; -> loc_bbdcccd
  bbdcca2  lock dec dword ptr [rsi+8]                    
  bbdcca6  jne short 0xBBDCCCD                           ; -> loc_bbdcccd
  bbdcca8  mov rax,[rsi]                                 
  bbdccab  mov rax,[rax]                                 
  bbdccae  mov rcx,rsi                                   
  bbdccb1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdccb7  lock dec dword ptr [rsi+0xC]                  
  bbdccbb  jne short 0xBBDCCCD                           ; -> loc_bbdcccd
  bbdccbd  mov rax,[rsi]                                 
  bbdccc0  mov rax,[rax+8]                               
  bbdccc4  mov rcx,rsi                                   
  bbdccc7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_bbdcccd:  ; from bbdcca0, bbdcca6, bbdccbb
  bbdcccd  movaps xmm6,[rbp+0x2D0]                       
  bbdccd4  add rsp,0x368                                 
  bbdccdb  pop rbx                                       
  bbdccdc  pop rdi                                       
  bbdccdd  pop rsi                                       
  bbdccde  pop r12                                       
  bbdcce0  pop r13                                       
  bbdcce2  pop r14                                       
  bbdcce4  pop r15                                       
  bbdcce6  pop rbp                                       
  bbdcce7  ret                                           
```
; Release [rbp+0x238]+8 object: two-stage lock-dec refcount [+8 then +0xC] with vtable releases [rax]/[rax+8]; null → skip [V bbdc92-cccd]. Epilogue: restore xmm6 from [rbp+0x2D0]; add rsp,0x368; pop rbx,rdi,rsi,r12,r13,r14,r15,rbp; ret [V bbdc cd-ccdce7].

### Phase 50: cold blocks and crash handlers (0xbbdccd4..0xbbdcce7)
```
bbdcce8  mov rcx,rdi                                   
bbdcceb  call 0x9BC830                                 ; -> sub_9bc830
bbdccf0  nop                                           
bbdccf1  jmp 0xBBDB050                                 ; -> sub_bbdb050
bbdccf6  mov rcx,rbx                                   
bbdccf9  call 0x9BC830                                 ; -> sub_9bc830
bbdccfe  nop                                           
bbdccff  xor esi,esi                                   
bbdcd01  jmp 0xBBDB08C                                 ; -> sub_bbdb08c
bbdcd06  mov rcx,rdi                                   
bbdcd09  call 0x9BC830                                 ; -> sub_9bc830
bbdcd0e  nop                                           
bbdcd0f  jmp 0xBBDBA01                                 ; -> sub_bbdba01
bbdcd14  mov rcx,r14                                   
bbdcd17  call 0x9BC830                                 ; -> sub_9bc830
bbdcd1c  nop                                           
bbdcd1d  xor esi,esi                                   
bbdcd1f  jmp 0xBBDBA3D                                 ; -> sub_bbdba3d
bbdcd24  mov rcx,r14                                   
bbdcd27  call 0x9BC830                                 ; -> sub_9bc830
bbdcd2c  nop                                           
bbdcd2d  jmp 0xBBDC3AC                                 ; -> sub_bbdc3ac
bbdcd32  mov rcx,rdi                                   
bbdcd35  call 0x9BC830                                 ; -> sub_9bc830
bbdcd3a  nop                                           
bbdcd3b  xor esi,esi                                   
bbdcd3d  jmp 0xBBDC3E8                                 ; -> sub_bbdc3e8
bbdcd42:  ; crash handler (alloc failure / slack too small)
  bbdcd42  mov qword ptr [rsp+0x20],0                    
  bbdcd4b  xor ecx,ecx                                   
  bbdcd4d  xor edx,edx                                   
  bbdcd4f  xor r8d,r8d                                   
  bbdcd52  xor r9d,r9d                                   
  bbdcd55  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bbdcd5b  nop                                           
  bbdcd5c  call 0x75B60                                  ; -> sub_75b60  (fail fast)
  ...
  bbdcd9e  mov ecx,5                                     
  bbdcda3  call 0xEEC5A00                                ; -> sub_eec5a00
  bbdcda8  nop                                           
  bbdcda9  mov dword ptr [rdi+0x1A4],0x7FFFFFFE          
  bbdcdb3  mov ecx,6                                     
  bbdcdb8  call 0xEEC5A00                                ; -> sub_eec5a00
  bbdcdbd  nop                                           
  bbdcdbe  call 0x75B60                                  ; -> sub_75b60  (fail fast)
  bbdcdc3  nop                                           
  bbdcdc4  int3                                          
  bbdcdc5  nop [rax+rax]                                 ; R ret@75b60+0x0+idx
```
; Cold blocks: alloc-failure fallbacks calling sub_9bc830 then jumping to earlier resume points (loc_bbdb050, loc_bbdb08c, loc_bbdba01, loc_bbdba3d, loc_bbdc3ac, loc_bbdc3e8) [V bbdcce8-d3d]. Crash handler at loc_bbdcd42: zeroes args, calls [0xF9A8C78], then sub_75b60 (fail fast) repeatedly; sets ecx=5/6, calls sub_eec5a00, stores 0x7FFFFFFE at [rdi+0x1A4], calls sub_75b60 again, then int3 at 0xbbdcdc4 — end of function [V bbdc d42-cdc5].

## CALLER ANALYSIS — sub_67c9970
Call site: `0x67c99be` → sub_bbdad00. Arguments built in rcx/rdx/r8 before call (per brief NEXT block). [?] = exact object types and arg meanings not yet determined from static disassembly; need `rdis dis 0x67c9970 150` output (raw saved at docs/progress/u-pass4a-caller-raw.txt). From sub_bbdad00's prologue/epilogue: rcx/rdx/r8 are likely object pointers (rcx = primary object with [rbp+0x238] field containing array base +0xA10; rdx/r8 = secondary objects with array at +0x158/+0x140 etc.).

## ARGUMENTS OF sub_bbdad00 (rcx/rdx/r8)
- rcx: primary object pointer. Read at [rbp+0x238] (stored early), dereferenced to get array base, then +0xA10 for inner array, +0xA78 for pool object. Also [rbp+0x158] used for array base in element loops.
- rdx: secondary object pointer. Used as rdx in sub_566a450 calls (rdx=rbx+0x120 or rbx+0x238 offsets), and in sub_bc06200/sub_bc3a2f0 calls.
- r8: tertiary object pointer. Used as r8 in sub_566a450 (&[rbp+0x2A0] slot array state), sub_bc06200, sub_bc3a2f0. Also [rbp+0x220] saved as array base for later loops.

## POOL +0x750 STRIDE-0x88 +0x78 COMPARE
Pattern appears 3x (phases 29, 39, 46):
1. r8 = [some_base + 0x750] (pool table base)
2. u16 = [rdx + 0x2A] (from record/slot)
3. r9d = u16 << 7 (= u16 * 128)
4. rdx = r9 + r8*8 (= u16*128 + u16*8 = u16*136 = u16 * 0x88)
5. compare [r8 + rdx + 0x78] against rcx → membership test
This is a stride-0x88 pool table indexed by u16 key, comparing field at +0x78. [V bbdb69c-6ae, bbdc02c-3e, bbdcabc-5e]

## OUTPUTS / STRUCTURES WRITTEN
- Slot arrays (stride 0x170 entries) at [rbp+0x1E0], [rbp+0x1A0], [rbp+0x180], [rbp+0x1C0], [rbp+0x2A0]: each entry = {0, u64 count, ptr slot_base}
- Pooled objects via sub_a78940(rcx=pool_obj [+0x0 field], rdx=&temp_slot, r8=count, r9d=1) → returns ptr stored in pool_obj field
- Output slots written: [r13+rsi]=0, [r13+rsi+8]=rbx(count), [r13+rsi+0x10]=slot_base; then sub_eec6de0 copies buffer
- Final cleanup releases all slot arrays and [rbp+0x238]+8 object

## CALLEES
| Address | Role |
|---------|------|
| sub_a78940 | Pool allocator (rcx=pool obj, rdx=&slot, r8=count, r9d=1) → ptr |
| sub_eea6040 | Refcount/release via vtable [rax] or [rax+8]/[rax+0x20] |
| sub_9bc830 | Error/fallback handler (alloc failure) |
| sub_eec6de0 | Memory copy (rcx=dst off, rdx=src, r8=buf) |
| sub_566a450 | Slot array append/process (rcx=scratch, rdx=obj+off, r8=&slot, r9=&temp) |
| sub_5667c80 | Slot fill (rcx=slot, rdx=val) |
| sub_56b68c0 | Slot array grow (rcx=&state, r8=val) |
| sub_5667e70 | Slot release/cleanup (rcx=slot) |
| sub_655cea0 | Conditional slot processing (rcx=ptr) when flag byte set |
| sub_bbd9be0 | Finalize slot state (rcx=&start, rdx=&state) |
| sub_bc06200 | Process slot range (rcx=start, rdx=end, r8=buf, r9=&result) |
| sub_bc3a2f0 | Match/scan (rcx=val, rdx=&state) → rsi |
| sub_bbdd780 | Array cleanup (rcx=array base) |
| sub_5689800 | Memmove (rcx=dst, rdx=src, r8=count) |
| sub_e935700 | Slack/realloc helper |
| sub_e93b480 | Record validation lookup |
| sub_75b60 | Fail fast / crash |
| sub_eec5a00 | Error code set (ecx=5 or 6) |

## PHASES COMPLETE
Phases 28-50 cover 0xbbdb5a0 through 0xbbdcdc5 (end of sub_bbdad00). All instructions in [0xbbdad00, 0xbbdcdc5) accounted for across phases 1-50 (from oc_U-PASS4A.md phases 1-27 + this file phases 28-50).

## NEXT
Report caller sub_67c9970 details: run `rdis dis 0x67c9970 150` and analyze args rcx/rdx/r8, object types, before/after state. Then mark unit complete.

## CALLER ANALYSIS — sub_67c9970 (UPDATED — verbatim from disassembly)
Entry: sub rsp,0x38; mov rdx,rcx (rdx=input obj); stack cookie at [rsp+0x30]
- mov r8,[rcx+0x30] → **r8 = [input+0x30]** (3rd arg to sub_bbdad00)
- mov rax,[rcx+0x10]; if nonzero: lock inc [rax+8] (refcount inc); rax=[rdx+0x10]; else rax=0
- mov rcx,[rdx+8] → **rcx_input = [input+0x8]**
- add rdx,0x18 → **rdx = input+0x18** (2nd arg to sub_bbdad00)
- mov [rsp+0x20],rcx; mov [rsp+0x28],rax → stack pair: { [input+0x8], [input+0x10] or 0 }
- lea rcx,[rsp+0x20] → **rcx = &stack_pair** (1st arg to sub_bbdad00)
- call sub_bbdad00 (rcx=&pair, rdx=input+0x18, r8=[input+0x30])
- Stack cookie check; ret on success, sub_e951550 + int3 on failure.

Input object layout (rcx at sub_67c9970 entry):
- +0x08: ptr A → passed via stack pair slot 0 to sub_bbdad00 rcx
- +0x10: ptr B (refcount inc'd if nonzero) → passed via stack pair slot 1
- +0x18: value → passed as rdx to sub_bbdad00
- +0x30: value → passed as r8 to sub_bbdad00

After call: stack cookie verify, ret. Failure path: sub_e951550 (fail fast) + int3s.

This confirms sub_bbdad00 args:
- rcx = pointer to stack pair {obj_A, obj_B_or_null}
- rdx = input object + 0x18
- r8 = [input object + 0x30]

## FILE STATUS
docs/progress/oc_U-PASS4A2.md — complete (1309 lines). Phases 28-50 cover all instructions in [0xbbdad00, 0xbbdcdc5). Caller analysis section needs update with verbatim findings above.

## NEXT (for orchestrator)
Optionally update docs/progress/oc_U-PASS4A.md's caller analysis section with verbatim sub_67c9970 findings. Mark U-PASS4A2 unit complete.
