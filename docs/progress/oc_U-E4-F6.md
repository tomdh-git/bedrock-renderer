# U-E4-F6: sub_67762e0 chunk builder — garbled-area redo + continuation from 0x677bb27

Unit: U-E4-F6
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation of U-E4-F5
RVAs: garbled redo at 0x677b1e0..0x677b203; continuation starts 0x677bb27 (Phase 144); function span [0x67762e0..0x677e166)
Source: `rdis dis` on Minecraft.Windows.exe 1.26.62.01 (version 1.26.62.01), RVAs relative to image base
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
COMPLETE — all work done (no further phases). Garbled area 0x677b1e0..0x677b200 redone (see section below); continuation from 0x677bb27 ran Phases 144-163 = 800 instructions, ending at RVA 0x677ca98. Running NEXT marker (kept during edits) at end of file mirrors this state.

## Redo — garbled area 0x677b1e0..0x677b200 (between Phase 131 end 0x677b1dd and Phase 132 start 0x677b1e3)

Re-disassembled with `rdis dis 0x677b1e0`. Previous Phase 132 doc started at 0x677b1e3 and never assigned bytes 0x677b1e0..0x677b1e2. Exact rdis lines:

```
  677b1e0  nop                                           
  677b1e1  add al,0                                      
  677b1e3  add [rsi-0x77],ah                             
  677b1e6  test [rax+0x48000002],ebp                     
  677b1ec  mov eax,[rbp+0x768]                           
  677b1f2  mov r8,[rax+0x480]                            
  677b1f9  mov rax,[rax+0x488]                           
  677b200  mov rdx,rax                                   
```

// Interpretation: 0x677b1e0 `nop` + 0x677b1e1 `add al,0` are two orphaned instructions (3 bytes) lying between Phase 131's last instruction at 0x677b1dd (`movzx eax,word [rbp+0x490]`) and Phase 132's previously recorded start at 0x677b1e3. 0x677b1e3 `add [rsi-0x77],ah` and 0x677b1e6 `test [rax+0x48000002],ebp` are the "weird opens" Phase 132 flagged as [?] — meaning unknown, likely embedded data/padding between real code; never invent meaning. Real code resumes at 0x677b1ec `mov eax,[rbp+0x768]` (size-math pattern: r8=[rax+0x480] begin, rax=[rax+0x488] end, rdx=rax-r8 size), continuing into Phase 132's guards. Range ends at 0x677b200 `mov rdx,rax` (instruction starts at 0x677b200, size 3 bytes → next at 0x677b203).

// tag: [?] for nop/add al,0/add [rsi-0x77],ah/test [rax+0x48000002],ebp (meaning undetermined); [V] for exact lines and RVAs.

## Phase 144 — [0x677bb27..0x677bbc9) 40 instructions (`rdis dis 0x677bb27 41`)

Exact rdis lines:

```
  677bb27  or [rax],al                                   
  677bb29  add bh,bh                                     
  677bb2b  adc eax,0x9224470                             
  677bb30  nop                                           
  677bb31  cmp byte ptr [rbp+0x6D8],1                    
  677bb38  jne short 0x677BB8C                           ; -> loc_677bb8c
  677bb3a  mov rcx,[rbp+0x698]                           
  677bb41  test rcx,rcx                                  
  677bb44  je short 0x677BB8C                            ; -> loc_677bb8c
  677bb46  mov rdx,[rbp+0x6A8]                           
  677bb4d  sub rdx,rcx                                   
  677bb50  cmp rdx,0x1000                                
  677bb57  jb short 0x677BB75                            ; -> loc_677bb75
  677bb59  mov rax,[rcx-8]                               
  677bb5d  add rcx,0xFFFFFFFFFFFFFFF8                    
  677bb61  sub rcx,rax                                   
  677bb64  cmp rcx,0x20                                  
  677bb68  jae 0x677E039                                 ; -> sub_677e039
  677bb6e  or rdx,0x27                                   
  677bb72  mov rcx,rax                                   

loc_677bb75:  ; from 677bb57
  677bb75  call 0xE935700                                ; -> sub_e935700
  677bb7a  lea rax,[rbp+0x698]                           
  677bb81  movups [rax],xmm6                             
  677bb84  mov qword ptr [rax+0x10],0                    

loc_677bb8c:  ; from 677bb38, 677bb44
  677bb8c  mov rcx,r12                                   
  677bb8f  call 0x6792810                                ; -> sub_6792810
  677bb94  mov r14,[rbp+0x780]                           
  677bb9b  mov r15d,[rbp+0x788]                          
  677bba2  test r15,r15                                  
  677bba5  je short 0x677BBE6                            ; -> loc_677bbe6
  677bba7  shl r15,5                                     
  677bbab  xor r13d,r13d                                 
  677bbae  jmp short 0x677BBB9                           ; -> loc_677bbb9

loc_677bbb0:  ; from 677bbc1, 677bbc7, 677bbd6
  677bbb0  add r13,0x20                                  
  677bbb4  cmp r15,r13                                   
  677bbb7  je short 0x677BBD8                            ; -> loc_677bbd8

loc_677bbb9:  ; from 677bbae
  677bbb9  mov rcx,[r14+r13+8]                           
  677bbbe  test rcx,rcx                                  
  677bbc1  je short 0x677BBB0                            ; -> loc_677bbb0
  677bbc3  lock dec dword ptr [rcx+0xC]                  
  677bbc7  jne short 0x677BBB0                           ; -> loc_677bbb0
```

// Interpretation: Opens with four weird instructions ([?], same embedded-data/padding class as prior phases): `or [rax],al`, `add bh,bh`, `adc eax,0x9224470`, `nop`. Then `cmp byte ptr [rbp+0x6D8],1`; `jne loc_677bb8c`; `mov rcx,[rbp+0x698]`; `test rcx,rcx`; `je loc_677bb8c`. Heap-chunk validation: `rdx=[rbp+0x6A8]`; `sub rdx,rcx` (size); `cmp rdx,0x1000`; `jb loc_677bb75` (small → call 0xE935700 path); else `rax=[rcx-8]` (chunk size field); `rcx+=0xFFFFFFFFFFFFFFF8` (-8); `sub rcx,rax`; `cmp rcx,0x20`; `jae sub_677e039` (heap-corruption fail); else `rdx|=0x27`; `rcx=rax`. loc_677bb75: `call 0xE935700`; `lea rax,[rbp+0x698]`; `movups [rax],xmm6`; `[rax+0x10]=0` (zero 24-byte block). loc_677bb8c (join): `mov rcx,r12`; `call 0x6792810`; `r14=[rbp+0x780]`; `r15d=[rbp+0x788]`; `test r15,r15`; `je loc_677bbe6`; else `r15<<=5` (×32); `r13=0`; `jmp loc_677bbb9`. loc_677bbb9: `rcx=[r14+r13+8]`; `test rcx,rcx`; `je loc_677bbb0`; `lock dec dword ptr [rcx+0xC]`; `jne loc_677bbb0` (refcounted-release loop). loc_677bbb0: `r13+=0x20`; `cmp r15,r13`; `je loc_677bbd8`. Range ends at `jne short loc_677bbb0` (0x677bbc7, 2 bytes); next instruction at 0x677bbc9.
// tag: [?] for the four opening weird instructions; [V] for all RVAs/lines/call targets.

## Phase 145 — [0x677bbc9..0x677bc70) 40 instructions (`rdis dis 0x677bbc9 41`)

Exact rdis lines:

```
  677bbc9  mov rax,[rcx]                                 ; R a0+0x0
  677bbcc  mov rax,[rax+8]                               ; R *(a0+0x0)+0x8
  677bbd0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bbd6  jmp short 0x677BBB0                           ; -> loc_677bbb0
  677bbd8  mov r14,[rbp+0x780]                           
  677bbdf  lea r13,[rbp+0x300]                           
  677bbe6  lea rax,[rbp+0x790]                           
  677bbed  cmp rax,r14                                   
  677bbf0  je short 0x677BC0F                            ; -> loc_677bc0f
  677bbf2  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  677bbf9  test r14,r14                                  
  677bbfc  je short 0x677BC0F                            ; -> loc_677bc0f
  677bbfe  mov rax,[rcx]                                 
  677bc01  mov rax,[rax+0x10]                            
  677bc05  mov rdx,r14                                   
  677bc08  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bc0e  nop                                           

loc_677bc0f:  ; from 677bbf0, 677bbfc
  677bc0f  mov r14,[rbp+0x7C0]                           
  677bc16  mov r15d,[rbp+0x7C8]                          
  677bc1d  test r15,r15                                  
  677bc20  je short 0x677BC66                            ; -> loc_677bc66
  677bc22  shl r15,5                                     
  677bc26  xor r13d,r13d                                 
  677bc29  jmp short 0x677BC39                           ; -> loc_677bc39
  677bc2b  nop [rax+rax]                                 

loc_677bc30:  ; from 677bc41, 677bc47, 677bc56
  677bc30  add r13,0x20                                  
  677bc34  cmp r15,r13                                   
  677bc37  je short 0x677BC58                            ; -> loc_677bc58

loc_677bc39:  ; from 677bc29
  677bc39  mov rcx,[r14+r13+8]                           
  677bc3e  test rcx,rcx                                  
  677bc41  je short 0x677BC30                            ; -> loc_677bc30
  677bc43  lock dec dword ptr [rcx+0xC]                  
  677bc47  jne short 0x677BC30                           ; -> loc_677bc30
  677bc49  mov rax,[rcx]                                 
  677bc4c  mov rax,[rax+8]                               
  677bc50  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bc56  jmp short 0x677BC30                           ; -> loc_677bc30

loc_677bc58:  ; from 677bc37
  677bc58  mov r14,[rbp+0x7C0]                           
  677bc5f  lea r13,[rbp+0x300]                           

loc_677bc66:  ; from 677bc20
  677bc66  lea rax,[rbp+0x7D0]                           
  677bc6d  cmp rax,r14                                   
```

// Interpretation: Release-loop tail: `mov rax,[rcx]`; `mov rax,[rax+8]`; call via [0xF99FFA0]; `jmp loc_677bbb0`. Fall-through loc_677bbd8: `r14=[rbp+0x780]`; `lea r13,[rbp+0x300]`. loc_677bbe6: `lea rax,[rbp+0x790]`; `cmp rax,r14`; `je loc_677bc0f`; else TLS read `rcx=[0x1233E1A8]` (note: 0x1233E1A8, distinct slot from 0x1233E1B0); `test r14,r14`; `je loc_677bc0f`; `rax=[rcx]`; `rax=[rax+0x10]`; `rdx=r14`; call via [0xF99FFA0]; `nop`. loc_677bc0f: `r14=[rbp+0x7C0]`; `r15d=[rbp+0x7C8]`; `test r15,r15`; `je loc_677bc66`; else `r15<<=5`; `r13=0`; `jmp loc_677bc39`; `nop [rax+rax]` padding. loc_677bc39: `rcx=[r14+r13+8]`; `test rcx,rcx`; `je loc_677bc30`; `lock dec dword ptr [rcx+0xC]`; `jne loc_677bc30`; `rax=[rcx]`; `rax=[rax+8]`; call via [0xF99FFA0]; `jmp loc_677bc30` (second release loop with call per element). loc_677bc58: `r14=[rbp+0x7C0]`; `lea r13,[rbp+0x300]`. loc_677bc66: `lea rax,[rbp+0x7D0]`; `cmp rax,r14`. Range ends at `cmp rax,r14` (0x677bc6d, 3 bytes); next instruction at 0x677bc70.
// tag: [V] all lines; call target [0xF99FFA0]=sub_eea6040 [V]; TLS slot [0x1233E1A8] [V].

## Phase 146 — [0x677bc70..0x677bd0d) 40 instructions (`rdis dis 0x677bc70 41`)

Exact rdis lines:

```
  677bc70  je short 0x677BC8F                            ; -> loc_677bc8f
  677bc72  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  677bc79  test r14,r14                                  
  677bc7c  je short 0x677BC8F                            ; -> loc_677bc8f
  677bc7e  mov rax,[rcx]                                 
  677bc81  mov rax,[rax+0x10]                            
  677bc85  mov rdx,r14                                   
  677bc88  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bc8e  nop                                           

loc_677bc8f:  ; from 677bc70, 677bc7c
  677bc8f  mov r14,[rbp+0x800]                           
  677bc96  test r14,r14                                  
  677bc99  je short 0x677BD15                            ; -> loc_677bd15
  677bc9b  mov r15,[rbp+0x808]                           
  677bca2  cmp r14,r15                                   
  677bca5  jne short 0x677BCB9                           ; -> loc_677bcb9
  677bca7  jmp short 0x677BCDE                           ; -> loc_677bcde
  677bca9  nop [rax]                                     

loc_677bcb0:  ; from 677bcc0, 677bcc6, 677bcd5
  677bcb0  add r14,0x20                                  
  677bcb4  cmp r14,r15                                   
  677bcb7  je short 0x677BCD7                            ; -> loc_677bcd7

loc_677bcb9:  ; from 677bca5
  677bcb9  mov rcx,[r14+8]                               
  677bcbd  test rcx,rcx                                  
  677bcc0  je short 0x677BCB0                            ; -> loc_677bcb0
  677bcc2  lock dec dword ptr [rcx+0xC]                  
  677bcc6  jne short 0x677BCB0                           ; -> loc_677bcb0
  677bcc8  mov rax,[rcx]                                 
  677bccb  mov rax,[rax+8]                               
  677bccf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bcd5  jmp short 0x677BCB0                           ; -> loc_677bcb0

loc_677bcd7:  ; from 677bcb7
  677bcd7  mov r14,[rbp+0x800]                           

loc_677bcde:  ; from 677bca7
  677bcde  mov rdx,[rbp+0x810]                           
  677bce5  sub rdx,r14                                   
  677bce8  cmp rdx,0x1000                                
  677bcef  jb short 0x677BD0D                            ; -> loc_677bd0d
  677bcf1  mov rax,[r14-8]                               
  677bcf5  add r14,0xFFFFFFFFFFFFFFF8                    
  677bcf9  sub r14,rax                                   
  677bcfc  cmp r14,0x20                                  
  677bd00  jae 0x677E039                                 ; -> sub_677e039
  677bd06  add rdx,0x27                                  
  677bd0a  mov r14,rax                                   
```

// Interpretation: Fall-through from Phase 145's `cmp rax,r14`: `je loc_677bc8f`; else TLS read on slot [0x1233E1A8] with rdx=r14, call via [0xF99FFA0]. loc_677bc8f: `r14=[rbp+0x800]`; `test r14,r14`; `je loc_677bd15`; `r15=[rbp+0x808]`; `cmp r14,r15`; `jne loc_677bcb9`; else `jmp loc_677bcde`; `nop [rax]` padding. Release loop loc_677bcb9: `rcx=[r14+8]`; `test rcx,rcx`; `je loc_677bcb0`; `lock dec dword ptr [rcx+0xC]`; `jne loc_677bcb0`; `rax=[rcx]`; `rax=[rax+8]`; call via [0xF99FFA0]; `jmp loc_677bcb0`; step `loc_677bcb0`: `r14+=0x20`; `cmp r14,r15`; `je loc_677bcd7`. loc_677bcd7: `r14=[rbp+0x800]`. loc_677bcde: `rdx=[rbp+0x810]`; `sub rdx,r14` (size); `cmp rdx,0x1000`; `jb loc_677bd0d`; else `rax=[r14-8]`; `r14+=-8`; `sub r14,rax`; `cmp r14,0x20`; `jae sub_677e039` (heap-corruption fail); `rdx+=0x27`; `r14=rax`. Range ends at `mov r14,rax` (0x677bd0a, 3 bytes); next instruction at 0x677bd0d (the jb target loc_677bd0d).
// tag: [V] all lines; [0xF99FFA0]=sub_eea6040 [V]; TLS slot [0x1233E1A8] [V].

## Phase 147 — [0x677bd0d..0x677bdf0) 40 instructions (`rdis dis 0x677bd0d 41`)

Exact rdis lines:

```
  677bd0d  mov rcx,r14                                   
  677bd10  call 0xE935700                                ; -> sub_e935700
  677bd15  mov rax,[rbp+0x568]                           
  677bd1c  cmp [rbp+0x838],rax                           
  677bd23  jne 0x677C389                                 ; -> loc_677c389
  677bd29  mov rax,[rbp+0x828]                           
  677bd30  mov rcx,[rax+0x10]                            
  677bd34  mov eax,0x9D0                                 
  677bd39  add rcx,rax                                   
  677bd3c  call 0x5ABA5C0                                ; -> sub_5aba5c0
  677bd41  nop                                           
  677bd42  mov r14,rax                                   
  677bd45  movaps [rbp+0x620],xmm6                       
  677bd4c  movaps [rbp+0x610],xmm6                       
  677bd53  movaps [rbp+0x600],xmm6                       
  677bd5a  movaps [rbp+0x5F0],xmm6                       
  677bd61  movaps [rbp+0x5E0],xmm6                       
  677bd68  movaps [rbp+0x5D0],xmm6                       
  677bd6f  movaps [rbp+0x5C0],xmm6                       
  677bd76  movaps [rbp+0x5B0],xmm6                       
  677bd7d  movaps [rbp+0x5A0],xmm6                       
  677bd84  movaps [rbp+0x590],xmm6                       
  677bd8b  movaps [rbp+0x580],xmm6                       
  677bd92  movaps [rbp+0x570],xmm6                       
  677bd99  mov qword ptr [rbp+0x630],0                   
  677bda4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677bdab  mov rax,[rcx]                                 
  677bdae  mov rax,[rax+0x10]                            
  677bdb2  mov dl,0x4A                                   
  677bdb4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bdba  nop                                           
  677bdbb  mov [rbp+0x838],al                            
  677bdc1  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
  677bdc8  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
  677bdcf  je short 0x677BDE5                            ; -> loc_677bde5
  677bdd1  movzx eax,word ptr [rbp+0x2A8]                
  677bdd8  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  677bddb  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
  677bde3  jmp short 0x677BDF9                           ; -> loc_677bdf9

loc_677bde5:  ; from 677bdcf
  677bde5  lea rcx,[r14+0x8A0]                           
  677bdec  lea r8,[rbp+0x2A8]                            
```

// Interpretation: `mov rcx,r14`; `call 0xE935700` (same small-size heap path as Phase 146's loc_677bb75). `rax=[rbp+0x568]`; `cmp [rbp+0x838],rax`; `jne loc_677c389`. `rax=[rbp+0x828]`; `rcx=[rax+0x10]`; `eax=0x9D0`; `rcx+=rax`; `call 0x5ABA5C0`; `nop`; `r14=rax` (return value). Zeroing block: `movaps [rbp+0x620..0x570 step -0x10],xmm6` (12 slots: 0x620,0x610,0x600,0x5F0,0x5E0,0x5D0,0x5C0,0x5B0,0x5A0,0x590,0x580,0x570). `[rbp+0x630]=0`. TLS read slot [0x1233E1B0]: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; call via [0xF99FFA0]; `nop`; `[rbp+0x838]=al`. Cursor bounds check: `rdx=[r14+0x8A8]`; `cmp [r14+0x8B0]`; `je loc_677bde5` (grow: `lea rcx,[r14+0x8A0]`, `lea r8,[rbp+0x2A8]` — continues next phase); else `movzx eax,word [rbp+0x2A8]`; `[rdx]=ax` (u16 write); `[r14+0x8A8]+=2`; `jmp loc_677bdf9`. Range ends at grow-block `lea r8,[rbp+0x2A8]` (0x677bdec, 4 bytes); next instruction at 0x677bdf0 (expected call, mirroring Phase 135's grow block call 0x1EF6F90).
// tag: [V] all lines; call targets 0xE935700 [V], 0x5ABA5C0 [V], [0xF99FFA0]=sub_eea6040 [V].

## Phase 148 — [0x677bdf0..0x677bea7) 40 instructions (`rdis dis 0x677bdf0 41`)

Exact rdis lines:

```
  677bdf0  add al,[rax]                                  
  677bdf2  add al,ch                                     
  677bdf4  cwde                                          
  677bdf5  mov cl,0x77                                   
  677bdf7  sti                                           
  677bdf8  nop                                           
  677bdf9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677be00  mov rax,[rcx]                                 
  677be03  mov rax,[rax+0x10]                            
  677be07  movzx edx,byte ptr [rbp+0x838]                
  677be0e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677be14  nop                                           
  677be15  mov eax,[r14+0x8A8]                           
  677be1c  sub eax,[r14+0x8A0]                           
  677be23  shr eax,1                                     
  677be25  dec eax                                       
  677be27  mov [rbp+0x580],ax                            
  677be2e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677be35  mov rax,[rcx]                                 
  677be38  mov rax,[rax+0x10]                            
  677be3c  mov dl,0x4A                                   
  677be3e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677be44  nop                                           
  677be45  mov [rbp+0x838],al                            
  677be4b  mov rdx,[r14+0x758]                           
  677be52  cmp rdx,[r14+0x760]                           
  677be59  je short 0x677BED7                            ; -> loc_677bed7
  677be5b  lea rcx,[rbp+0x250]                           
  677be62  mov eax,[rcx+0x10]                            
  677be65  mov [rdx+0x10],eax                            
  677be68  movups xmm0,[rcx]                             
  677be6b  movups [rdx],xmm0                             
  677be6e  movzx eax,byte ptr [rbp+0x264]                
  677be75  mov [rdx+0x14],al                             
  677be78  movss xmm0,[rbp+0x268]                        
  677be80  movss [rdx+0x18],xmm0                         
  677be85  movss xmm0,[rbp+0x26C]                        
  677be8d  movss [rdx+0x1C],xmm0                         
  677be92  movss xmm0,[rbp+0x270]                        
  677be9a  movss [rdx+0x20],xmm0                         
  677be9f  movss xmm0,[rbp+0x274]                        
```

// Interpretation: 0x677bdf0..0x677bdf8 are weird instructions ([?], embedded-data class): `add al,[rax]`, `add al,ch`, `cwde`, `mov cl,0x77`, `sti`, `nop` — note the grow path (Phase 147's `je loc_677bde5` → `lea rcx,[r14+0x8A0]`, `lea r8,[rbp+0x2A8]`) falls straight into these bytes with no call; no call target seen here. TLS read at 0x677bdf9: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x838]`; call via [0xF99FFA0]; `nop`. Counter: `eax=[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax`; `[rbp+0x580]=ax`. TLS again: `rcx=[0x1233E1B0]`→`[rax]`→`[rax+0x10]`; `mov dl,0x4A`; call via [0xF99FFA0]; `[rbp+0x838]=al`. Cursor record append: `rdx=[r14+0x758]`; `cmp [r14+0x760]`; `je loc_677bed7` (grow block continues next phase); else store record at cursor: `eax=[rbp+0x250+0x10]`; `[rdx+0x10]=eax`; `movups [rbp+0x250]→[rdx]`; `movzx eax,byte [rbp+0x264]`; `[rdx+0x14]=al`; `movss [rbp+0x268]→[rdx+0x18]`; `[rbp+0x26C]→[rdx+0x1C]`; `[rbp+0x270]→[rdx+0x20]`; `movss xmm0=[rbp+0x274]` continues next phase (expects 3 more movss stores to [rdx+0x24],[rdx+0x33],[rdx+0x42] per Phase 136's [rbp+0x574+0x1A4/0x1B4/0x1C3] pattern — here sourced from [rbp+0x274..] instead).
// tag: [?] for six opening weird instructions; [V] for all RVAs/lines; [0xF99FFA0]=sub_eea6040 [V].

## Phase 149 — [0x677bea7..0x677bf77) 40 instructions (`rdis dis 0x677bea7 41`)

Exact rdis lines:

```
  677bea7  movss [rdx+0x24],xmm0                         ; W a1+0x24
  677beac  movups xmm0,[rbx+0x88]                        
  677beb3  movups xmm1,[rbx+0x98]                        
  677beba  movups xmm2,[rbx+0xA7]                        
  677bec1  movups [rdx+0x28],xmm0                        ; W a1+0x28
  677bec5  movups [rdx+0x38],xmm1                        ; W a1+0x38
  677bec9  movups [rdx+0x47],xmm2                        ; W a1+0x47
  677becd  add qword ptr [r14+0x758],0x58                
  677bed5  jmp short 0x677BEEB                           ; -> loc_677beeb

loc_677bed7:  ; from 677be59
  677bed7  lea rcx,[r14+0x750]                           
  677bede  lea r8,[rbp+0x250]                            
  677bee5  call 0x6760A80                                ; -> sub_6760a80
  677beea  nop                                           

loc_677beeb:  ; from 677bed5
  677beeb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677bef2  mov rax,[rcx]                                 
  677bef5  mov rax,[rax+0x10]                            
  677bef9  movzx edx,byte ptr [rbp+0x838]                
  677bf00  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bf06  nop                                           
  677bf07  mov qword ptr [rbp+0x570],0x4001              
  677bf12  mov eax,[r14+0x758]                           
  677bf19  sub eax,[r14+0x750]                           
  677bf20  shr eax,3                                     
  677bf23  imul eax,0xFFFF8BA3                           
  677bf29  dec eax                                       
  677bf2b  mov [rbp+0x59C],ax                            
  677bf32  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677bf39  mov rax,[rcx]                                 
  677bf3c  mov rax,[rax+0x10]                            
  677bf40  mov dl,0x4A                                   
  677bf42  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bf48  nop                                           
  677bf49  mov [rbp+0x838],al                            
  677bf4f  mov rdx,[r14+0x890]                           
  677bf56  cmp rdx,[r14+0x898]                           
  677bf5d  je short 0x677BF6B                            ; -> loc_677bf6b
  677bf5f  inc rdx                                       
  677bf62  mov [r14+0x890],rdx                           
  677bf69  jmp short 0x677BF78                           ; -> loc_677bf78

loc_677bf6b:  ; from 677bf5d
  677bf6b  lea rcx,[r14+0x888]                           
  677bf72  call 0x6760E60                                ; -> sub_6760e60
```

// Interpretation: Tail of the record append from Phase 148: `movss [rdx+0x24],xmm0`; then `movups xmm0=[rbx+0x88]`, `xmm1=[rbx+0x98]`, `xmm2=[rbx+0xA7]`; `[rdx+0x28]=xmm0`, `[rdx+0x38]=xmm1`, `[rdx+0x47]=xmm2`; `[r14+0x758]+=0x58`; `jmp loc_677beeb`. Grow block loc_677bed7: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x250]`; `call 0x6760A80` (same grow helper as Phase 136); `nop`. loc_677beeb: TLS read `rcx=[0x1233E1B0]`→`[rax]`→`[rax+0x10]`; `movzx edx,byte [rbp+0x838]`; call via [0xF99FFA0]; `nop`; `[rbp+0x570]=0x4001` (u64 state tag). Counter: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `[rbp+0x59C]=ax` (matches Phase 137's [rbp+0x4CC] pattern). TLS flag read again: `rcx=[0x1233E1B0]`→`[rax]`→`[rax+0x10]`; `mov dl,0x4A`; call via [0xF99FFA0]; `[rbp+0x838]=al`. Cursor bounds check: `rdx=[r14+0x890]`; `cmp [r14+0x898]`; `je loc_677bf6b` (grow: `lea rcx,[r14+0x888]`, `call 0x6760E60` — call continues next phase, expected `nop` then inc path mirroring Phase 137); else `inc rdx`; `[r14+0x890]=rdx`; `jmp loc_677bf78`. Range ends at `call 0x6760E60` (0x677bf72, 5 bytes); next instruction at 0x677bf77.
// tag: [V] all lines; call targets 0x6760A80 [V], 0x6760E60 [V], [0xF99FFA0]=sub_eea6040 [V].

## Phase 150 — [0x677bf77..0x677c034) 40 instructions (`rdis dis 0x677bf77 41`)

Exact rdis lines:

```
  677bf77  nop                                           
  677bf78  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677bf7f  mov rax,[rcx]                                 
  677bf82  mov rax,[rax+0x10]                            
  677bf86  movzx edx,byte ptr [rbp+0x838]                
  677bf8d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bf93  nop                                           
  677bf94  mov eax,[r14+0x888]                           
  677bf9b  not eax                                       
  677bf9d  add eax,[r14+0x890]                           
  677bfa4  mov [rbp+0x582],ax                            
  677bfab  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677bfb2  mov rax,[rcx]                                 
  677bfb5  mov rax,[rax+0x10]                            
  677bfb9  mov dl,0x4A                                   
  677bfbb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677bfc1  nop                                           
  677bfc2  mov [rbp+0x838],al                            
  677bfc8  mov rdx,[r14+0x7A0]                           
  677bfcf  cmp rdx,[r14+0x7A8]                           
  677bfd6  je short 0x677BFE4                            ; -> loc_677bfe4
  677bfd8  inc rdx                                       
  677bfdb  mov [r14+0x7A0],rdx                           
  677bfe2  jmp short 0x677BFF1                           ; -> loc_677bff1

loc_677bfe4:  ; from 677bfd6
  677bfe4  lea rcx,[r14+0x798]                           
  677bfeb  call 0x6760E60                                ; -> sub_6760e60
  677bff0  nop                                           

loc_677bff1:  ; from 677bfe2
  677bff1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677bff8  mov rax,[rcx]                                 
  677bffb  mov rax,[rax+0x10]                            
  677bfff  movzx edx,byte ptr [rbp+0x838]                
  677c006  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c00c  nop                                           
  677c00d  mov eax,[r14+0x798]                           
  677c014  not eax                                       
  677c016  add eax,[r14+0x7A0]                           
  677c01d  mov [rbp+0x596],ax                            
  677c024  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c02b  mov rax,[rcx]                                 
  677c02e  mov rax,[rax+0x10]                            
  677c032  mov dl,0x4A                                   
```

// Interpretation: `nop` padding; TLS flag call `rcx=[0x1233E1B0]`→`[rax]`→`[rax+0x10]`; `movzx edx,byte [rbp+0x838]`; call via [0xF99FFA0]; `nop`. Counter: `eax=[r14+0x888]`; `not eax`; `add eax,[r14+0x890]`; `[rbp+0x582]=ax`. TLS flag call again; `[rbp+0x838]=al`. Cursor bounds check: `rdx=[r14+0x7A0]`; `cmp [r14+0x7A8]`; `je loc_677bfe4` (grow: `lea rcx,[r14+0x798]`, `call 0x6760E60`, `nop`); else `inc rdx`; `[r14+0x7A0]=rdx`; `jmp loc_677bff1`. loc_677bff1: TLS read; `movzx edx,byte [rbp+0x838]`; call via [0xF99FFA0]; `nop`. Counter: `eax=[r14+0x798]`; `not eax`; `add eax,[r14+0x7A0]`; `[rbp+0x596]=ax`. TLS read continues: `rcx=[0x1233E1B0]`→`[rax]`→`[rax+0x10]`; `mov dl,0x4A` — range ends mid-call-setup at 0x677c032; next instruction at 0x677c034 (expected `call qword ptr [0xF99FFA0]`).
// tag: [V] all lines; call targets 0x6760E60 [V], [0xF99FFA0]=sub_eea6040 [V].

## Phase 151 — [0x677c034..0x677c108) 40 instructions (`rdis dis 0x677c034 41`)

Exact rdis lines:

```
  677c034  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c03a  mov [rbp+0x838],al                            
  677c040  lea rcx,[r14+0x648]                           
  677c047  lea rdx,[rbp+0x1F8]                           
  677c04e  call 0x675FB30                                ; -> sub_675fb30
  677c053  nop                                           
  677c054  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c05b  mov rax,[rcx]                                 
  677c05e  mov rax,[rax+0x10]                            
  677c062  movzx edx,byte ptr [rbp+0x838]                
  677c069  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c06f  nop                                           
  677c070  mov eax,[r14+0x650]                           
  677c077  sub eax,[r14+0x648]                           
  677c07e  shr eax,3                                     
  677c081  imul eax,0xFFFF8E39                           
  677c087  dec eax                                       
  677c089  mov [rbp+0x5B2],ax                            
  677c090  lea rcx,[r14+0x780]                           
  677c097  lea rdx,[rbp+0x1A0]                           
  677c09e  call 0x675F3B0                                ; -> sub_675f3b0
  677c0a3  nop                                           
  677c0a4  mov qword ptr [rbp+0x570],0x2005803           
  677c0af  mov eax,[r14+0x788]                           
  677c0b6  sub eax,[r14+0x780]                           
  677c0bd  shr eax,3                                     
  677c0c0  imul eax,0xFFFF8BA3                           
  677c0c6  dec eax                                       
  677c0c8  mov [rbp+0x598],ax                            
  677c0cf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c0d6  mov rax,[rcx]                                 
  677c0d9  mov rax,[rax+0x10]                            
  677c0dd  mov dl,0x4A                                   
  677c0df  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c0e5  mov [rbp+0x838],al                            
  677c0eb  mov r15,[r14+0x770]                           
  677c0f2  cmp r15,[r14+0x778]                           
  677c0f9  je short 0x677C13C                            ; -> loc_677c13c
  677c0fb  mov rax,[rbp+0x118]                           
  677c102  mov [r15],rax                                 
  677c105  lea rcx,[r15+8]                               
```

// Interpretation: Completes Phase 150's `mov dl,0x4A`: `call qword ptr [0xF99FFA0]`; `[rbp+0x838]=al`. Then `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x1F8]`; `call 0x675FB30` (same callee as Phases 138/139, rdx=&[rbp+0x1F8] vs 0x698/0x640 before). TLS read; `movzx edx,byte [rbp+0x838]`; call via [0xF99FFA0]; `nop`. Counter 1: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `[rbp+0x5B2]=ax` (matches Phase 139 counter 1, stored at 0x5B2 vs 0x4E2). `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x1A0]`; `call 0x675F3B0`; `nop`; `[rbp+0x570]=0x2005803` (u64 state tag). Counter 2: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `[rbp+0x598]=ax`. TLS flag read → `[rbp+0x838]=al`. Element append: `r15=[r14+0x770]`; `cmp [r14+0x778]`; `je loc_677c13c` (grow block continues next phase); else `[r15]=[rbp+0x118]`; `lea rcx,[r15+8]` continues next phase (expected rdx=&[rbp+...] then call 0xE869FF0 mirroring Phase 139).
// tag: [V] all lines; call targets 0x675FB30 [V], 0x675F3B0 [V], [0xF99FFA0]=sub_eea6040 [V].

## Phase 152 — [0x677c108..0x677c1c8) 40 instructions (`rdis dis 0x677c108 41`)

Exact rdis lines:

```
  677c108  or [rax-0x73],cl                              
  677c10b  xchg ebp,eax                                  
  677c10c  and [rcx],al                                  ; W a0+0x0
  677c10e  add [rax],al                                  
  677c110  call 0xE869FF0                                ; -> sub_e869ff0
  677c115  nop                                           
  677c116  mov rax,[rbp+0x198]                           
  677c11d  mov [r15+0x80],rax                            
  677c124  mov qword ptr [rbp+0x198],0                   
  677c12f  add qword ptr [r14+0x770],0x88                
  677c13a  jmp short 0x677C153                           ; -> loc_677c153
  677c13c  lea rcx,[r14+0x768]                           
  677c143  mov rdx,r15                                   
  677c146  lea r8,[rbp+0x118]                            
  677c14d  call 0x6760710                                ; -> sub_6760710
  677c152  nop                                           

loc_677c153:  ; from 677c13a
  677c153  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c15a  mov rax,[rcx]                                 
  677c15d  mov rax,[rax+0x10]                            
  677c161  movzx edx,byte ptr [rbp+0x838]                
  677c168  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c16e  nop                                           
  677c16f  mov eax,[r14+0x770]                           
  677c176  sub eax,[r14+0x768]                           
  677c17d  shr eax,3                                     
  677c180  imul eax,0xFFFFF0F1                           
  677c186  dec eax                                       
  677c188  mov [rbp+0x59A],ax                            
  677c18f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c196  mov rax,[rcx]                                 
  677c199  mov rax,[rax+0x10]                            
  677c19d  mov dl,0x4A                                   
  677c19f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c1a5  nop                                           
  677c1a6  mov [rbp+0x838],al                            
  677c1ac  mov rdx,[r14+0x2D8]                           
  677c1b3  cmp rdx,[r14+0x2E0]                           
  677c1ba  je short 0x677C1C8                            ; -> loc_677c1c8
  677c1bc  inc rdx                                       
  677c1bf  mov [r14+0x2D8],rdx                           
  677c1c6  jmp short 0x677C1D5                           ; -> loc_677c1d5
```

// Interpretation: Element append continues from Phase 151 (`lea rcx,[r15+8]`): the fast path runs `call 0xE869FF0` [I: append element to chunk, mirrors Phase 139]; `nop`; `mov rax,[rbp+0x198]`; `mov [r15+0x80],rax` (store appended value); `mov qword ptr [rbp+0x198],0` (clear state slot); `add qword ptr [r14+0x770],0x88` (element cursor += 0x88 = element size [I]); `jmp loc_677c153`. Slow path at 0x677c13c (space exhausted): `lea rcx,[r14+0x768]`; `mov rdx,r15`; `lea r8,[rbp+0x118]`; `call 0x6760710` (same grow helper as earlier phases [V]); `nop`. At loc_677c153: TLS read `mov rcx,[0x1233E1B0]`; `mov rax,[rcx+0x10]`; `movzx edx,byte [rbp+0x838]`; `call qword ptr [0xF99FFA0]` (= sub_eea6040 [V]); `nop`. Counter 3: `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `[rbp+0x59A]=ax` (stored at 0x59A, vs 0x5B2 Phase 151 / 0x4E2 Phase 139). TLS flag again: `mov dl,0x4A`; call [0xF99FFA0]; `[rbp+0x838]=al`. Second append slot: `rdx=[r14+0x2D8]`; `cmp [r14+0x2E0]`; `je loc_677c1c8`; else `inc rdx`; `[r14+0x2D8]=rdx`; `jmp loc_677c1d5` (continues next phase).
// tag: [V] all lines; calls 0xE869FF0 [V], 0x6760710 [V], [0xF99FFA0]=sub_eea6040 [V].

## Phase 153 — [0x677c1c8..0x677c292) 40 instructions (`rdis dis 0x677c1c8 41`)

Exact rdis lines:

```
  677c1c8  lea rcx,[r14+0x2D0]                           
  677c1cf  call 0x6760E60                                ; -> sub_6760e60
  677c1d4  nop                                           
  677c1d5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c1dc  mov rax,[rcx]                                 
  677c1df  mov rax,[rax+0x10]                            
  677c1e3  movzx edx,byte ptr [rbp+0x838]                
  677c1ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c1f0  nop                                           
  677c1f1  mov rax,0x4000000002007803                    
  677c1fb  mov [rbp+0x570],rax                           
  677c202  mov eax,[r14+0x2D0]                           
  677c209  not eax                                       
  677c20b  add eax,[r14+0x2D8]                           
  677c212  mov [rbp+0x5FC],ax                            
  677c219  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c220  mov rax,[rcx]                                 
  677c223  mov rax,[rax+0x10]                            
  677c227  mov dl,0x4A                                   
  677c229  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c22f  nop                                           
  677c230  mov [rbp+0x838],al                            
  677c236  mov rdx,[r14+0x6C8]                           
  677c23d  cmp rdx,[r14+0x6D0]                           
  677c244  je short 0x677C252                            ; -> loc_677c252
  677c246  inc rdx                                       
  677c249  mov [r14+0x6C8],rdx                           
  677c250  jmp short 0x677C25F                           ; -> loc_677c25f

loc_677c252:  ; from 677c244
  677c252  lea rcx,[r14+0x6C0]                           
  677c259  call 0x6760E60                                ; -> sub_6760e60
  677c25e  nop                                           

loc_677c25f:  ; from 677c250
  677c25f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c266  mov rax,[rcx]                                 
  677c269  mov rax,[rax+0x10]                            
  677c26d  movzx edx,byte ptr [rbp+0x838]                
  677c274  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c27a  nop                                           
  677c27b  mov eax,[r14+0x6C0]                           
  677c282  not eax                                       
  677c284  add eax,[r14+0x6C8]                           
  677c28b  mov [rbp+0x5A8],ax                            
```

// Interpretation: Slow-path tail of second append: `lea rcx,[r14+0x2D0]`; `call 0x6760E60` (grow helper #2, seen earlier [V]); `nop`. Then TLS + call [0xF99FFA0]; `mov rax,0x4000000002007803`; `[rbp+0x570]=rax` (same state-tag u64 as Phase 152). Size/sum: `eax=[r14+0x2D0]`; `not eax`; `add eax,[r14+0x2D8]`; `[rbp+0x5FC]=ax` ([I: checksum/count field at 0x5FC]). TLS + call [0xF99FFA0]; `[rbp+0x838]=al`. Third append slot: `rdx=[r14+0x6C8]`; `cmp [r14+0x6D0]`; `je loc_677c252`; else `inc rdx`; `[r14+0x6C8]=rdx`; `jmp loc_677c25f`. Slow path loc_677c252: `lea rcx,[r14+0x6C0]`; `call 0x6760E60`; `nop`. At loc_677c25f: TLS + call [0xF99FFA0] (two consecutive); `mov eax,[r14+0x6C0]`; `not eax`; `add eax,[r14+0x6C8]`; `[rbp+0x5A8]=ax` (counter/checksum at 0x5A8).
// tag: [V] all lines; calls 0x6760E60 [V] x2, [0xF99FFA0]=sub_eea6040 [V] x3.

## Phase 154 — [0x677c292..0x677c34f) 40 instructions (`rdis dis 0x677c292 41`)

Exact rdis lines:

```
  677c292  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c299  mov rax,[rcx]                                 
  677c29c  mov rax,[rax+0x10]                            
  677c2a0  mov dl,0x4A                                   
  677c2a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c2a8  nop                                           
  677c2a9  mov [rbp+0x838],al                            
  677c2af  mov rdx,[r14+0x6B0]                           
  677c2b6  cmp rdx,[r14+0x6B8]                           
  677c2bd  je short 0x677C2CB                            ; -> loc_677c2cb
  677c2bf  inc rdx                                       
  677c2c2  mov [r14+0x6B0],rdx                           
  677c2c9  jmp short 0x677C2DB                           ; -> loc_677c2db

loc_677c2cb:  ; from 677c2bd
  677c2cb  mov rcx,r14                                   
  677c2ce  add rcx,0x6A8                                 
  677c2d5  call 0x6760E60                                ; -> sub_6760e60
  677c2da  nop                                           

loc_677c2db:  ; from 677c2c9
  677c2db  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c2e2  mov rax,[rcx]                                 
  677c2e5  mov rax,[rax+0x10]                            
  677c2e9  movzx edx,byte ptr [rbp+0x838]                
  677c2f0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c2f6  nop                                           
  677c2f7  mov rax,0x4000000002307803                    
  677c301  mov [rbp+0x570],rax                           
  677c308  mov eax,[r14+0x6A8]                           
  677c30f  not eax                                       
  677c311  add eax,[r14+0x6B0]                           
  677c318  mov [rbp+0x5AA],ax                            
  677c31f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c326  mov rax,[rcx]                                 
  677c329  mov rax,[rax+0x10]                            
  677c32d  mov dl,0x4A                                   
  677c32f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c335  nop                                           
  677c336  mov [rbp+0x838],al                            
  677c33c  mov rdx,[r14+8]                               
  677c340  cmp rdx,[r14+0x10]                            
  677c344  je short 0x677C361                            ; -> loc_677c361
  677c346  mov r8d,0xC8                                  
  677c34c  mov rcx,rdx                                   
```

// Interpretation: Fourth append slot continues from Phase 153: TLS + call [0xF99FFA0]; `[rbp+0x838]=al`. `rdx=[r14+0x6B0]`; `cmp [r14+0x6B8]`; `je loc_677c2cb`; else `inc rdx`; `[r14+0x6B0]=rdx`; `jmp loc_677c2db`. Slow path loc_677c2cb: `mov rcx,r14`; `add rcx,0x6A8`; `call 0x6760E60` (grow helper #2 [V]); `nop`. At loc_677c2db: TLS + call [0xF99FFA0] (two consecutive); `mov rax,0x4000000002307803`; `[rbp+0x570]=rax` (state-tag u64, tag byte 0x03 vs Phase 153's 0x2007803 [I]). `eax=[r14+0x6A8]`; `not eax`; `add eax,[r14+0x6B0]`; `[rbp+0x5AA]=ax` (counter/checksum at 0x5AA). TLS + call [0xF99FFA0]; `[rbp+0x838]=al`. Fifth append slot: `rdx=[r14+8]`; `cmp [r14+0x10]`; `je loc_677c361`; else fall-through `mov r8d,0xC8` (0xC8=200 [I]); `mov rcx,rdx` continues next phase (expected lea rdx,... then call grow/append helper).
// tag: [V] all lines; calls 0x6760E60 [V], [0xF99FFA0]=sub_eea6040 [V] x4.

## Phase 155 — [0x677c34f..0x677c40a) 40 instructions (`rdis dis 0x677c34f 41`)

Exact rdis lines:

```
  677c34f  mov rdx,r12                                   
  677c352  call 0xEEC6EC0                                ; -> sub_eec6ec0
  677c357  add qword ptr [r14+8],0xC8                    
  677c35f  jmp short 0x677C36D                           ; -> loc_677c36d
  677c361  mov rcx,r14                                   
  677c364  mov r8,r12                                    
  677c367  call 0x5ABA6D0                                ; -> sub_5aba6d0
  677c36c  nop                                           

loc_677c36d:  ; from 677c35f
  677c36d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c374  mov rax,[rcx]                                 
  677c377  mov rax,[rax+0x10]                            
  677c37b  movzx edx,byte ptr [rbp+0x838]                
  677c382  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c388  nop                                           
  677c389  lea rcx,[rbp+0x110]                           
  677c390  call 0x67E1840                                ; -> sub_67e1840
  677c395  jmp 0x677DE96                                 ; -> loc_677de96 (tail jump out of this phase window)
  677c39a  lea rcx,[r14+0x8A0]                           
  677c3a1  lea r8,[rbp+0x738]                            
  677c3a8  call 0x1EF6F90                                ; -> sub_1ef6f90
  677c3ad  nop                                           
  677c3ae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c3b5  mov rax,[rcx]                                 
  677c3b8  mov rax,[rax+0x10]                            
  677c3bc  movzx edx,byte ptr [rbp+0x847]                
  677c3c3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c3c9  nop                                           
  677c3ca  mov eax,[r14+0x8A8]                           
  677c3d1  sub eax,[r14+0x8A0]                           
  677c3d8  shr eax,1                                     
  677c3da  dec eax                                       
  677c3dc  mov [rbp+0x4B0],ax                            
  677c3e3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c3ea  mov rax,[rcx]                                 
  677c3ed  mov rax,[rax+0x10]                            
  677c3f1  mov dl,0x4A                                   
  677c3f3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c3f9  nop                                           
  677c3fa  mov [rbp+0x847],al                            
  677c400  mov rdx,[r14+0x758]                           
  677c407  cmp rdx,[r14+0x760]                           
```

// Interpretation: Fifth append slot completes: fast path `mov rdx,r12`; `call 0xEEC6EC0` [I: append/copy element]; `add qword ptr [r14+8],0xC8` (cursor += 0xC8); `jmp loc_677c36d`. Slow path: `mov rcx,r14`; `mov r8,r12`; `call 0x5ABA6D0` [I: grow]; `nop`. loc_677c36d: TLS `mov rcx,[0x1233E1B0]`; `mov rax,[rcx+0x10]`; `movzx edx,byte [rbp+0x838]`; `call qword ptr [0xF99FFA0]` (= sub_eea6040 [V]); `nop`; `lea rcx,[rbp+0x110]`; `call 0x67E1840` [I: finalize/hash]; `jmp 0x677DE96` (tail jump to function tail region). Code after the tail jump (cold/unreachable-from-here [?]): `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x738]`; `call 0x1EF6F90`; `nop`; TLS flag at [rbp+0x847] (different slot flag [I]); `call qword ptr [0xF99FFA0]`; `nop`. Counter: `eax=[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax`; `[rbp+0x4B0]=ax` (element count/2 at 0x4B0, shr 1 = /2 vs /8 before). TLS flag store `[rbp+0x847]=al`. Sixth append slot: `rdx=[r14+0x758]`; `cmp [r14+0x760]` continues next phase.
/never-invent: the `jmp 0x677DE96` target lies beyond this phase window; meaning of code at 0x677c39a..0x677c409 relative to it is [?] (cold block or alternate entry).
// tag: [V] all lines; calls 0xEEC6EC0 [V], 0x5ABA6D0 [V], 0x67E1840 [V], 0x1EF6F90 [V], [0xF99FFA0]=sub_eea6040 [V] x4.

## Phase 156 — [0x677c40a..0x677c4db) 40 instructions (`rdis dis 0x677c40a 41`)

Exact rdis lines:

```
  677c40a  (bad)                                         
  677c40c  add [rax],al                                  
  677c40e  je 0x677C59A                                  ; -> loc_677c59a
  677c414  lea rcx,[rbp+0x6E0]                           
  677c41b  mov eax,[rcx+0x10]                            
  677c41e  mov [rdx+0x10],eax                            ; W a1+0x10
  677c421  movups xmm0,[rcx]                             
  677c424  movups [rdx],xmm0                             ; W a1+0x0
  677c427  movzx eax,byte ptr [rbp+0x6F4]                
  677c42e  mov [rdx+0x14],al                             ; W a1+0x14
  677c431  movss xmm0,[rbp+0x6F8]                        
  677c439  movss [rdx+0x18],xmm0                         ; W a1+0x18
  677c43e  movss xmm0,[rbp+0x6FC]                        
  677c446  movss [rdx+0x1C],xmm0                         ; W a1+0x1C
  677c44b  movss xmm0,[rbp+0x700]                        
  677c453  movss [rdx+0x20],xmm0                         ; W a1+0x20
  677c458  movss xmm0,[rbp+0x704]                        
  677c460  movss [rdx+0x24],xmm0                         ; W a1+0x24
  677c465  lea rax,[rbp+0x574]                           
  677c46c  movups xmm0,[rax+0x194]                       
  677c473  movups xmm1,[rax+0x1A4]                       
  677c47a  movups xmm2,[rax+0x1B3]                       
  677c481  movups [rdx+0x28],xmm0                        ; W a1+0x28
  677c485  movups [rdx+0x38],xmm1                        ; W a1+0x38
  677c489  movups [rdx+0x47],xmm2                        ; W a1+0x47
  677c48d  add qword ptr [r14+0x758],0x58                
  677c495  jmp 0x677C5AE                                 ; -> loc_677c5ae
  677c49a  lea rcx,[r14+0x8A0]                           
  677c4a1  lea r8,[rbp+0x740]                            
  677c4a8  call 0x1EF6F90                                ; -> sub_1ef6f90
  677c4ad  nop                                           
  677c4ae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c4b5  mov rax,[rcx]                                 
  677c4b8  mov rax,[rax+0x10]                            
  677c4bc  movzx edx,byte ptr [rbp+0x847]                
  677c4c3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c4c9  nop                                           
  677c4ca  mov eax,[r14+0x8A8]                           
  677c4d1  sub eax,[r14+0x8A0]                           
  677c4d8  shr eax,1                                     
  677c4da  dec eax                                       
```

// Interpretation: Sixth append slot fast path: `cmp rdx,[r14+0x760]` (from Phase 155); `je 0x677c59a` (grow path loc_677c59a [I]); else rdis shows 1 bad byte at 0x677c40a then `add [rax],al` at 0x677c40c (misalign/data byte [?] — record exactly as rdis emitted; never invent). Element copy: `lea rcx,[rbp+0x6E0]`; `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups [rdx],xmm0` from [rcx] (32-byte struct copy); scalars: byte [rbp+0x6F4]→[rdx+0x14]; movss [rbp+0x6F8]→[rdx+0x18]; [rbp+0x6FC]→[rdx+0x1C]; [rbp+0x700]→[rdx+0x20]; [rbp+0x704]→[rdx+0x24]; then from `rax=[rbp+0x574]`: movups [rax+0x194]→[rdx+0x28], [rax+0x1A4]→[rdx+0x38], [rax+0x1B3]→[rdx+0x47]. `add qword ptr [r14+0x758],0x58` (cursor += 0x58 [I]); `jmp loc_677c5ae`. Cold block: `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x740]`; `call 0x1EF6F90`; `nop`; TLS flag [rbp+0x847] via call [0xF99FFA0]; `nop`. Counter: `eax=[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax` (store continues next phase).
// tag: [V] all lines; `677c40a (bad)` recorded exactly as rdis emitted it ([?] meaning); calls 0x1EF6F90 [V], [0xF99FFA0]=sub_eea6040 [V].

## Phase 157 — [0x677c4db..0x677c5ae) 40 instructions (`rdis dis 0x677c4db 41`)

Exact rdis lines:

```
  677c4db  enter 0x8966,0x85                             
  677c4df  mov al,4                                      
  677c4e1  add [rax],al                                  
  677c4e3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c4ea  mov rax,[rcx]                                 
  677c4ed  mov rax,[rax+0x10]                            
  677c4f1  mov dl,0x4A                                   
  677c4f3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c4f9  nop                                           
  677c4fa  mov [rbp+0x847],al                            
  677c500  mov rdx,[r14+0x758]                           
  677c507  cmp rdx,[r14+0x760]                           
  677c50e  je 0x677C635                                  ; -> loc_677c635
  677c514  lea rcx,[rbp+0x6E8]                           
  677c51b  mov eax,[rcx+0x10]                            
  677c51e  mov [rdx+0x10],eax                            
  677c521  movups xmm0,[rcx]                             
  677c524  movups [rdx],xmm0                             
  677c527  movzx eax,byte ptr [rbp+0x6FC]                
  677c52e  mov [rdx+0x14],al                             
  677c531  movss xmm0,[rbp+0x700]                        
  677c539  movss [rdx+0x18],xmm0                         
  677c53e  movss xmm0,[rbp+0x704]                        
  677c546  movss [rdx+0x1C],xmm0                         
  677c54b  movss xmm0,[rbp+0x708]                        
  677c553  movss [rdx+0x20],xmm0                         
  677c558  movss xmm0,[rbp+0x70C]                        
  677c560  movss [rdx+0x24],xmm0                         
  677c565  lea rax,[rbp+0x574]                           
  677c56c  movups xmm0,[rax+0x19C]                       
  677c573  movups xmm1,[rax+0x1AC]                       
  677c57a  movups xmm2,[rax+0x1BB]                       
  677c581  movups [rdx+0x28],xmm0                        
  677c585  movups [rdx+0x38],xmm1                        
  677c589  movups [rdx+0x47],xmm2                        
  677c58d  add qword ptr [r14+0x758],0x58                
  677c595  jmp 0x677C649                                 ; -> loc_677c649
  677c59a  lea rcx,[r14+0x750]                           
  677c5a1  lea r8,[rbp+0x6E0]                            
  677c5a8  call 0x6760A80                                ; -> sub_6760a80
  677c5ad  nop                                           
```

// Interpretation: `enter 0x8966,0x85` [V] (large frame; inline mid-function [?] — possibly rdis boundary artifact since rdis headers this as sub_677c4db; never invent meaning). `mov al,4`; `add [rax],al`. TLS flag [rbp+0x847]: read via TLS [0x1233E1B0]+0x10; `movzx edx,byte [rbp+0x847]`; `call qword ptr [0xF99FFA0]` (= sub_eea6040 [V]); `nop`; `[rbp+0x847]=al`. Seventh append slot: `rdx=[r14+0x758]`; `cmp [r14+0x760]`; `je loc_677c635` (grow); else fast copy from `lea rcx,[rbp+0x6E8]`: `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups [rdx],xmm0` (32-byte struct copy); scalars: byte [rbp+0x6FC]→[rdx+0x14]; movss [rbp+0x700]→[rdx+0x18]; [rbp+0x704]→[rdx+0x1C]; [rbp+0x708]→[rdx+0x20]; [rbp+0x70C]→[rdx+0x24]; `lea rax,[rbp+0x574]`; movups [rax+0x19C]→[rdx+0x28], [rax+0x1AC]→[rdx+0x38], [rax+0x1BB]→[rdx+0x47] (offsets differ vs Phase 156's 0x194/0x1A4/0x1B3 [I: different element layout]). `add qword ptr [r14+0x758],0x58` (cursor += 0x58); `jmp loc_677c649`. Grow path loc_677c635: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6E0]`; `call 0x6760A80` (grow helper #3 [V]); `nop` (falls to loc_677c5ae = next phase start).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V], 0x6760A80 [V].

## Phase 158 — [0x677c5ae..0x677c687) 40 instructions (`rdis dis 0x677c5ae 41`)

Exact rdis lines:

```
  677c5ae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c5b5  mov rax,[rcx]                                 
  677c5b8  mov rax,[rax+0x10]                            
  677c5bc  movzx edx,byte ptr [rbp+0x847]                
  677c5c3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c5c9  nop                                           
  677c5ca  mov qword ptr [rbp+0x4A0],0x4001              
  677c5d5  mov eax,[r14+0x758]                           
  677c5dc  sub eax,[r14+0x750]                           
  677c5e3  shr eax,3                                     
  677c5e6  imul eax,0xFFFF8BA3                           
  677c5ec  dec eax                                       
  677c5ee  mov [rbp+0x4CC],ax                            
  677c5f5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c5fc  mov rax,[rcx]                                 
  677c5ff  mov rax,[rax+0x10]                            
  677c603  mov dl,0x4A                                   
  677c605  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c60b  nop                                           
  677c60c  mov [rbp+0x847],al                            
  677c612  mov rdx,[r14+0x890]                           
  677c619  cmp rdx,[r14+0x898]                           
  677c620  je 0x677C6D0                                  ; -> loc_677c6d0
  677c626  inc rdx                                       
  677c629  mov [r14+0x890],rdx                           
  677c630  jmp 0x677C6DD                                 ; -> loc_677c6dd
  677c635  lea rcx,[r14+0x750]                           
  677c63c  lea r8,[rbp+0x6E8]                            
  677c643  call 0x6760A80                                ; -> sub_6760a80
  677c648  nop                                           
  677c649  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c650  mov rax,[rcx]                                 
  677c653  mov rax,[rax+0x10]                            
  677c657  movzx edx,byte ptr [rbp+0x847]                
  677c65e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c664  nop                                           
  677c665  mov qword ptr [rbp+0x4A0],0x4001              
  677c670  mov eax,[r14+0x758]                           
  677c677  sub eax,[r14+0x750]                           
  677c67e  shr eax,3                                     
  677c681  imul eax,0xFFFF8BA3                           
```

// Interpretation: loc_677c5ae (Phase 157's jmp target): TLS flag [rbp+0x847] via call [0xF99FFA0] (= sub_eea6040 [V]); `nop`; `mov qword ptr [rbp+0x4A0],0x4001` (state tag [I]). Counter: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `[rbp+0x4CC]=ax`. TLS flag again + call [0xF99FFA0]; `[rbp+0x847]=al`. Eighth append slot: `rdx=[r14+0x890]`; `cmp [r14+0x898]`; `je loc_677c6d0` (grow); else `inc rdx`; `[r14+0x890]=rdx`; `jmp loc_677c6dd`. Grow path loc_677c635: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6E8]`; `call 0x6760A80` [V] (grow helper #3); `nop`. loc_677c649 (fall-through after grow): TLS flag + call [0xF99FFA0]; `mov qword ptr [rbp+0x4A0],0x4001`; counter `eax=[r14+0x758]-[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3` (continues next phase: dec eax; store).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0x6760A80 [V].

## Phase 159 — [0x677c687..0x677c750) 40 instructions (`rdis dis 0x677c687 41`)

Exact rdis lines:

```
  677c687  dec eax                                       
  677c689  mov [rbp+0x4CC],ax                            
  677c690  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c697  mov rax,[rcx]                                 
  677c69a  mov rax,[rax+0x10]                            
  677c69e  mov dl,0x4A                                   
  677c6a0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c6a6  nop                                           
  677c6a7  mov [rbp+0x847],al                            
  677c6ad  mov rdx,[r14+0x890]                           
  677c6b4  cmp rdx,[r14+0x898]                           
  677c6bb  je 0x677C750                                  ; -> loc_677c750
  677c6c1  inc rdx                                       
  677c6c4  mov [r14+0x890],rdx                           
  677c6cb  jmp 0x677C75D                                 ; -> loc_677c75d
  677c6d0  lea rcx,[r14+0x888]                           
  677c6d7  call 0x6760E60                                ; -> sub_6760e60
  677c6dc  nop                                           
  677c6dd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c6e4  mov rax,[rcx]                                 
  677c6e7  mov rax,[rax+0x10]                            
  677c6eb  movzx edx,byte ptr [rbp+0x847]                
  677c6f2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c6f8  nop                                           
  677c6f9  mov eax,[r14+0x888]                           
  677c700  not eax                                       
  677c702  add eax,[r14+0x890]                           
  677c709  mov [rbp+0x4B2],ax                            
  677c710  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c717  mov rax,[rcx]                                 
  677c71a  mov rax,[rax+0x10]                            
  677c71e  mov dl,0x4A                                   
  677c720  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c726  nop                                           
  677c727  mov [rbp+0x847],al                            
  677c72d  mov rdx,[r14+0x7A0]                           
  677c734  cmp rdx,[r14+0x7A8]                           
  677c73b  je 0x677C7D0                                  ; -> loc_677c7d0
  677c741  inc rdx                                       
  677c744  mov [r14+0x7A0],rdx                           
  677c74b  jmp 0x677C7DD                                 ; -> loc_677c7dd
```

// Interpretation: Completes Phase 158's counter: `dec eax`; `mov [rbp+0x4CC],ax` (rdis output line 2 displayed target as [rbp-0x2B34] due to signed disp; same store as 0x677c5ee [V]). TLS flag [rbp+0x847]: read via TLS [0x1233E1B0]+0x10; `call qword ptr [0xF99FFA0]` (= sub_eea6040 [V]); `nop`; `[rbp+0x847]=al`. Eighth append slot tail: `rdx=[r14+0x890]`; `cmp [r14+0x898]`; `je loc_677c750` (grow); else `inc rdx`; `[r14+0x890]=rdx`; `jmp loc_677c75d`. Grow loc_677c6d0: `lea rcx,[r14+0x888]`; `call 0x6760E60` [V] (grow helper #2); `nop`. loc_677c6dd: TLS flag + call [0xF99FFA0]; `nop`. Checksum: `eax=[r14+0x888]`; `not eax`; `add eax,[r14+0x890]`; `[rbp+0x4B2]=ax`. TLS flag again + call [0xF99FFA0]; `[rbp+0x847]=al`. Ninth append slot: `rdx=[r14+0x7A0]`; `cmp [r14+0x7A8]`; `je loc_677c7d0` (grow); else `inc rdx`; `[r14+0x7A0]=rdx`; `jmp loc_677c7dd`.
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0x6760E60 [V].

## Phase 160 — [0x677c750..0x677c822) 40 instructions (`rdis dis 0x677c750 41`)

Exact rdis lines:

```
  677c750  lea rcx,[r14+0x888]                           
  677c757  call 0x6760E60                                ; -> sub_6760e60
  677c75c  nop                                           
  677c75d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c764  mov rax,[rcx]                                 
  677c767  mov rax,[rax+0x10]                            
  677c76b  movzx edx,byte ptr [rbp+0x847]                
  677c772  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c778  nop                                           
  677c779  mov eax,[r14+0x888]                           
  677c780  not eax                                       
  677c782  add eax,[r14+0x890]                           
  677c789  mov [rbp+0x4B2],ax                            
  677c790  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c797  mov rax,[rcx]                                 
  677c79a  mov rax,[rax+0x10]                            
  677c79e  mov dl,0x4A                                   
  677c7a0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c7a6  nop                                           
  677c7a7  mov [rbp+0x847],al                            
  677c7ad  mov rdx,[r14+0x7A0]                           
  677c7b4  cmp rdx,[r14+0x7A8]                           
  677c7bb  je 0x677C92F                                  ; -> loc_677c92f
  677c7c1  inc rdx                                       
  677c7c4  mov [r14+0x7A0],rdx                           
  677c7cb  jmp 0x677C93C                                 ; -> loc_677c93c
  677c7d0  lea rcx,[r14+0x798]                           
  677c7d7  call 0x6760E60                                ; -> sub_6760e60
  677c7dc  nop                                           
  677c7dd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c7e4  mov rax,[rcx]                                 
  677c7e7  mov rax,[rax+0x10]                            
  677c7eb  movzx edx,byte ptr [rbp+0x847]                
  677c7f2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c7f8  nop                                           
  677c7f9  mov qword ptr [rbp+0x4A0],0x4803              
  677c804  mov eax,[r14+0x798]                           
  677c80b  not eax                                       
  677c80d  add eax,[r14+0x7A0]                           
  677c814  mov [rbp+0x4C6],ax                            
  677c81b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```

// Interpretation: loc_677c750 (Phase 159's grow target): `lea rcx,[r14+0x888]`; `call 0x6760E60` [V] (grow helper #2); `nop`. loc_677c75d: TLS flag [rbp+0x847] via call [0xF99FFA0] (= sub_eea6040 [V]); `nop`. Checksum: `eax=[r14+0x888]`; `not eax`; `add eax,[r14+0x890]`; `[rbp+0x4B2]=ax`. TLS flag again + call [0xF99FFA0]; `[rbp+0x847]=al`. Ninth append slot tail: `rdx=[r14+0x7A0]`; `cmp [r14+0x7A8]`; `je loc_677c92f` (grow); else `inc rdx`; `[r14+0x7A0]=rdx`; `jmp loc_677c93c`. Grow loc_677c7d0: `lea rcx,[r14+0x798]`; `call 0x6760E60` [V]; `nop`. loc_677c7dd: TLS flag + call [0xF99FFA0]; `mov qword ptr [rbp+0x4A0],0x4803` (state tag [I], tag byte 0x03); `eax=[r14+0x798]`; `not eax`; `add eax,[r14+0x7A0]`; `[rbp+0x4C6]=ax`; TLS read continues next phase.
/never-invent: targets loc_677c92f / loc_677c93C lie beyond this phase window; not yet disassembled.
// tag: [V] all lines; calls 0x6760E60 [V] x2, [0xF99FFA0]=sub_eea6040 [V] x3.

## Phase 161 — [0x677c822..0x677c8f2) 40 instructions (`rdis dis 0x677c822 41`)

Exact rdis lines:

```
  677c822  mov rax,[rcx]                                 ; R a0+0x0
  677c825  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  677c829  mov dl,0x4A                                   
  677c82b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c831  mov [rbp+0x847],al                            
  677c837  lea rcx,[r14+0x648]                           
  677c83e  lea rdx,[rbp+0x688]                           
  677c845  call 0x675FB30                                ; -> sub_675fb30
  677c84a  nop                                           
  677c84b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c852  mov rax,[rcx]                                 
  677c855  mov rax,[rax+0x10]                            
  677c859  movzx edx,byte ptr [rbp+0x847]                
  677c860  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c866  nop                                           
  677c867  mov eax,[r14+0x650]                           
  677c86e  sub eax,[r14+0x648]                           
  677c875  shr eax,3                                     
  677c878  imul eax,0xFFFF8E39                           
  677c87e  dec eax                                       
  677c880  mov [rbp+0x4E2],ax                            
  677c887  lea rcx,[r14+0x780]                           
  677c88e  lea rdx,[rbp+0x630]                           
  677c895  call 0x675F3B0                                ; -> sub_675f3b0
  677c89a  nop                                           
  677c89b  mov eax,[r14+0x788]                           
  677c8a2  sub eax,[r14+0x780]                           
  677c8a9  shr eax,3                                     
  677c8ac  imul eax,0xFFFF8BA3                           
  677c8b2  dec eax                                       
  677c8b4  mov [rbp+0x4C8],ax                            
  677c8bb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c8c2  mov rax,[rcx]                                 
  677c8c5  mov rax,[rax+0x10]                            
  677c8c9  mov dl,0x4A                                   
  677c8cb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c8d1  mov [rbp+0x847],al                            
  677c8d7  mov r15,[r14+0x770]                           
  677c8de  cmp r15,[r14+0x778]                           
  677c8e5  je 0x677CA8E                                  ; -> loc_677ca8e
  677c8eb  mov rax,[rbp+0x5A8]                           
```

// Interpretation: Completes Phase 160's TLS read: `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (= sub_eea6040 [V]); `[rbp+0x847]=al`. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x688]`; `call 0x675FB30` [V] (scan/size helper, same as Phases 138/139/151). TLS flag + call [0xF99FFA0]. Counter 1: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `[rbp+0x4E2]=ax` (matches Phase 139's counter-1 store at 0x4E2 [V]; Phase 151 used 0x5B2). `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x630]`; `call 0x675F3B0` [V]; `nop`. Counter 2: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `[rbp+0x4C8]=ax`. TLS flag + call [0xF99FFA0]; `[rbp+0x847]=al`. Element append (11th slot): `r15=[r14+0x770]`; `cmp r15,[r14+0x778]`; `je loc_677ca8e` (grow); else `mov rax,[rbp+0x5A8]` continues next phase (expected `[r15]=rax; lea rcx,[r15+8]` mirroring Phase 152).
// tag: [V] all lines; calls 0x675FB30 [V], 0x675F3B0 [V], [0xF99FFA0]=sub_eea6040 [V] x4.

## Phase 162 — [0x677c8f2..0x677c9c5) 40 instructions (`rdis dis 0x677c8f2 41`)

Exact rdis lines:

```
  677c8f2  mov [r15],rax                                 
  677c8f5  lea rcx,[r15+8]                               
  677c8f9  lea rdx,[rbp+0x5B0]                           
  677c900  call 0xE869FF0                                ; -> sub_e869ff0
  677c905  nop                                           
  677c906  mov rax,[rbp+0x628]                           
  677c90d  mov [r15+0x80],rax                            
  677c914  mov qword ptr [rbp+0x628],0                   
  677c91f  add qword ptr [r14+0x770],0x88                
  677c92a  jmp 0x677CAA5                                 ; -> loc_677caa5
  677c92f  lea rcx,[r14+0x798]                           
  677c936  call 0x6760E60                                ; -> sub_6760e60
  677c93b  nop                                           
  677c93c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c943  mov rax,[rcx]                                 
  677c946  mov rax,[rax+0x10]                            
  677c94a  movzx edx,byte ptr [rbp+0x847]                
  677c951  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c957  nop                                           
  677c958  mov eax,[r14+0x798]                           
  677c95f  not eax                                       
  677c961  add eax,[r14+0x7A0]                           
  677c968  mov [rbp+0x4C6],ax                            
  677c96f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c976  mov rax,[rcx]                                 
  677c979  mov rax,[rax+0x10]                            
  677c97d  mov dl,0x4A                                   
  677c97f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c985  mov [rbp+0x847],al                            
  677c98b  lea rcx,[r14+0x648]                           
  677c992  lea rdx,[rbp+0x690]                           
  677c999  call 0x675FB30                                ; -> sub_675fb30
  677c99e  nop                                           
  677c99f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677c9a6  mov rax,[rcx]                                 
  677c9a9  mov rax,[rax+0x10]                            
  677c9ad  movzx edx,byte ptr [rbp+0x847]                
  677c9b4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677c9ba  nop                                           
  677c9bb  mov eax,[r14+0x650]                           
  677c9c2  sub eax,[r14+0x648]                           
```

// Interpretation: Phase 161's append completes: `mov [r15],rax`; `lea rcx,[r15+8]`; `lea rdx,[rbp+0x5B0]`; `call 0xE869FF0` [I: append element, mirrors Phase 152]; `nop`; `mov rax,[rbp+0x628]`; `mov [r15+0x80],rax`; `mov qword ptr [rbp+0x628],0`; `add qword ptr [r14+0x770],0x88` (element cursor += 0x88); `jmp loc_677caa5`. Grow path loc_677c92f: `lea rcx,[r14+0x798]`; `call 0x6760E60` [V] (grow helper #2); `nop`. loc_677c93c: TLS flag [rbp+0x847] via call [0xF99FFA0] (= sub_eea6040 [V]); `nop`. Checksum: `eax=[r14+0x798]`; `not eax`; `add eax,[r14+0x7A0]`; `[rbp+0x4C6]=ax`. TLS flag again + call [0xF99FFA0]; `[rbp+0x847]=al`. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x690]`; `call 0x675FB30` [V] (scan helper); `nop`; TLS flag + call [0xF99FFA0]; `nop`. Counter: `eax=[r14+0x650]`; `sub eax,[r14+0x648]` continues next phase (shr 3; imul 0xFFFF8E39; dec; store).
// tag: [V] all lines; calls 0xE869FF0 [V], 0x6760E60 [V], 0x675FB30 [V], [0xF99FFA0]=sub_eea6040 [V] x4.

## Phase 163 — [0x677c9c5..0x677ca98) 40 instructions (`rdis dis 0x677c9c5 41`) — FINAL (800 instructions total, Phases 144-163 complete)

Exact rdis lines:

```
  677c9c5  (bad)                                         
  677c9c8  add cl,al                                     
  677c9ca  call 0x403832D2                               ; -> data_403832d2
  677c9cf  (bad)                                         
  677c9d1  (bad)                                         
  677c9d3  enter 0x8966,0x85                             
  677c9d7  loop 0x677C9DD                                ; -> loc_677c9dd
  677c9d9  add [rax],al                                  ; W ret@403832d2+0x0
  677c9db  lea rcx,[r14+0x780]                           
  677c9e2  lea rdx,[rbp+0x638]                           
  677c9e9  call 0x675F3B0                                ; -> sub_675f3b0
  677c9ee  nop                                           
  677c9ef  mov qword ptr [rbp+0x4A0],0x2005803           
  677c9fa  mov eax,[r14+0x788]                           
  677ca01  sub eax,[r14+0x780]                           
  677ca08  shr eax,3                                     
  677ca0b  imul eax,0xFFFF8BA3                           
  677ca11  dec eax                                       
  677ca13  mov [rbp+0x4C8],ax                            
  677ca1a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677ca21  mov rax,[rcx]                                 
  677ca24  mov rax,[rax+0x10]                            
  677ca28  mov dl,0x4A                                   
  677ca2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677ca30  mov [rbp+0x847],al                            
  677ca36  mov r15,[r14+0x770]                           
  677ca3d  cmp r15,[r14+0x778]                           
  677ca44  je 0x677CB2C                                  ; -> loc_677cb2c
  677ca4a  mov rax,[rbp+0x5B0]                           
  677ca51  mov [r15],rax                                 
  677ca54  lea rcx,[r15+8]                               
  677ca58  lea rdx,[rbp+0x5B8]                           
  677ca5f  call 0xE869FF0                                ; -> sub_e869ff0
  677ca64  nop                                           
  677ca65  mov rax,[rbp+0x630]                           
  677ca6c  mov [r15+0x80],rax                            
  677ca73  mov qword ptr [rbp+0x630],0                   
  677ca7e  add qword ptr [r14+0x770],0x88                
  677ca89  jmp 0x677CB43                                 ; -> loc_677cb43
  677ca8e  lea rcx,[r14+0x768]                           
  677ca95  mov rdx,r15                                   
```

// Interpretation: 3 bad bytes at 0x677c9c5, 0x677c9cf, 0x677c9d1 and `call 0x403832D2` (rdis resolves target to data_403832d2) — embedded-data/misdecode zone [?], recorded exactly as rdis emitted; never invent. `enter 0x8966,0x85`; `loop 0x677c9dd`; `add [rax],al`. `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x638]`; `call 0x675F3B0` [V] (scan helper); `nop`; `[rbp+0x4A0]=0x2005803` (state tag [I], same as Phase 152). Counter 2: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `[rbp+0x4C8]=ax`. TLS flag + call [0xF99FFA0] (= sub_eea6040 [V]); `[rbp+0x847]=al`. Element append (12th): `r15=[r14+0x770]`; `cmp [r14+0x778]`; `je loc_677cb2c`; else `mov rax,[rbp+0x5B0]`; `mov [r15],rax`; `lea rcx,[r15+8]`; `lea rdx,[rbp+0x5B8]`; `call 0xE869FF0` [I: append element]; `nop`; `mov rax,[rbp+0x630]`; `mov [r15+0x80],rax`; `[rbp+0x630]=0`; `add qword ptr [r14+0x770],0x88`; `jmp loc_677cb43`. Grow path loc_677ca8e: `lea rcx,[r14+0x768]`; `mov rdx,r15` continues beyond 800-instruction limit (next RVA 0x677ca98, not disassembled).
// tag: [V] all decodable lines; `(bad)` x3 and call 0x403832D2 [?]; calls 0x675F3B0 [V], 0xE869FF0 [V], [0xF99FFA0]=sub_eea6040 [V].

## NEXT
COMPLETE: 800 instructions disassembled (Phases 144-163, [0x677bb27..0x677ca98)). Final RVA 0x677ca98 (grow path loc_677ca8e tail, `mov rdx,r15` at 0x677ca95, next insn at 0x677ca98 — not disassembled per 800-instruction limit). No further phases scheduled.
