# Progress: U-SK2b sky Cubemap case continuation 0x6659a75 -> epilogue 0x665d124

## NEXT
U-SK2b is DONE. The Cubemap case entered at 0x6659615 and continued linearly from 0x6659a75 exits to epilogue 0x665d124 via 0x665aee8 (`mov rsi,[rbp+0x328]` / `jmp 0x665d124`). Along the way it passes the shared SKY-PUSH construction (call 0x5ABA5C0 then call 0x675F3B0 at the 0x665a8e5 region, reachable copy at 0x665bb39). No further work pending for this unit.

## Method
- `rdis ... dis <rva> <n>` linear disassembly; each phase <= 40 instructions; every instruction quoted exactly as rdis prints it (`0xRVA  mnemonic operands`); interpretation on separate `//` lines after each fence. Instruction-complete: no instruction in a phase range is skipped.
- Tags: [V]=seen in disassembly, [I]=inferred, [?]=unknown. All RVAs relative to image base; exe = Minecraft.Windows 1.26.62.01.

## Fix — 0x6659815 / 0x6659817 are NOT real instructions
The previous unit's Phase C4 claimed to start at `0x6659815` with two bogus lines:
- `0x6659815  add eax,[rax]`
- `0x6659817  add [rcx+rcx*4-7],cl`
These are misaligned garbage bytes lying INSIDE the 7-byte `lea rdx,[rbp+0x340]` instruction (REX.W + 8d + ModRM 55 + disp32 = 7 bytes, 0x6659811..0x6659818). Re-disassembling the area with `rdis` from a correct boundary (0x66597f0) prints the real lines:

```
0x665980b  call 0xBBD7C70                                ; -> sub_bbd7c70
0x6659810  nop                                           
0x6659811  lea rdx,[rbp+0x340]                           
0x6659818  mov rcx,r15                                   
0x665981b  call 0x4DEDD00                                ; -> sub_4dedd00
0x6659820  nop                                           
0x6659821  mov r15,[rdi]                                 
```

Consequence: Phase C3 already ends at `0x6659811  lea rdx,[rbp+0x340]` (7 bytes). Phase C4 must start at **0x6659818**, not 0x6659815. The rest of the previous Phase C4 body (0x665981b..0x66598e4) is unchanged and instruction-complete.

## Phase C7 — Cubemap case 0x6659a75..0x6659b86 (32 instr) [V]
```
0x6659a75  mov byte ptr [rbp+0x388],8                    
0x6659a7c  mov qword ptr [rbp+0x38C],0                   
0x6659a87  mov qword ptr [rbp+0x392],0                   
0x6659a92  mov byte ptr [rbp+0x39A],0xFF                 
0x6659a99  mov rax,[rbp+0x50]                            
0x6659a9d  mov [rbp+0x3A0],rax                           
0x6659aa4  lea rcx,[rbp+0x3A8]                           
0x6659aab  mov rdx,rbx                                   
0x6659aae  call 0xE869FF0                                ; -> sub_e869ff0
0x6659ab3  nop                                           
0x6659ab4  lea rax,[rbp+0x344]                           
0x6659abb  lea r10,[rbp+0x3A0]                           
0x6659ac2  mov rcx,[rbp+0xD0]                            
0x6659ac9  mov [rbp+0x420],rcx                           
0x6659ad0  mov qword ptr [rbp+0xD0],0                    
0x6659adb  lea r9,[rbp+0x428]                            
0x6659ae2  movups [rbp+0x428],xmm6                       
0x6659ae9  movups [rbp+0x438],xmm7                       
0x6659af0  movups [rbp+0x448],xmm8                       
0x6659af8  movups [rbp+0x458],xmm9                       
0x6659b00  mov byte ptr [rbp+0x468],0                    
0x6659b07  lea r8,[rbp+0x470]                            
0x6659b0e  mov [rbp+0x470],di                            
0x6659b15  lea rdx,[rbp+0x478]                           
0x6659b1c  movaps xmm0,[rbp+0x4E0]                       
0x6659b23  movaps xmm1,[rbp+0x4F0]                       
0x6659b2a  mov qword ptr [rbp+0x4E8],0                   
0x6659b35  movups [rbp+0x478],xmm0                       
0x6659b3c  movaps [rbp+0x4F0],xmm10                      
0x6659b44  movups [rbp+0x488],xmm1                       
0x6659b4b  mov rcx,[rbp+0x500]                           
0x6659b52  mov [rbp+0x498],rcx                           
0x6659b59  mov byte ptr [rbp+0x4B0],0xFF                 
0x6659b60  movzx ecx,byte ptr [rbp+0x518]                
0x6659b67  cmp rcx,3                                     
0x6659b6b  ja 0x665CF8B                                  ; -> sub_665cf8b
0x6659b71  lea r11,[rbp+0x4A0]                           
0x6659b78  lea rdi,[0xF2BF428]                           ; [data_f2bf428]
0x6659b7f  movsxd rbx,[rdi+rcx*4]                        
0x6659b83  add rbx,rdi                                   
0x6659b86  jmp rbx                                       
```
// INTERPRETATION [V]: Finishes the fixed descriptor at rbp+0x388..0x39A (begun in C6: [rbp+0x344]=3,[rbp+0x348]=7,[rbp+0x34C]=1,[rbp+0x350]=1,[rbp+0x352]=2,[rbp+0x354]=0,[rbp+0x358]=0,[rbp+0x378]=8,[rbp+0x37C]=0,[rbp+0x384]=0). rax=[rbp+0x50] stored at [rbp+0x3A0] (0x50 was set to 1 at 0x66598ae) [V]. call 0xE869FF0(rcx=&rbp+0x3A8, rdx=rbx) — material-pair setter of the 0xe86b370 family [V,I]. Builds an args block at rbp+0x420..0x4B0: [rbp+0x420]=[rbp+0xD0], [rbp+0xD0]=0, xmm6..xmm9 copied to [rbp+0x428..0x468], [rbp+0x470]=di (=u16 [rdi+0x3C] from C6), [rbp+0x4F0]=xmm10 (from [rbp+0x4E0]), [rbp+0x488]=xmm1, [rbp+0x498]=[rbp+0x500], [rbp+0x4B0]=0xFF [V]. Then a switch on byte [rbp+0x518] (`cmp rcx,3; ja 0x665CF8B`) with jump table at [0xF2BF428] (8 entries, rel32): [0]=0x665cf85, [1]=0x6659b88, [2]=0x665baa6, [3]=0x665bacc, [4]=0x665aefb, [5]=0x6659553, [6]=0x66595d0, [7]=0x66595e2 — resolved targets via PE section mapping [V]. `jmp rbx` dispatches [V]. Cases 5..7 (0x6659553/0x66595d0/0x66595e2) sit before 0x6659a75 (earlier function region) and are not re-decoded here [I].

## Phase C8 — Cubemap case switch case 1 0x6659b88..0x6659b96 (3 instr) [V]
```
0x6659b88  mov r11,[rbp+0x508]                           
0x6659b8f  mov [rbp+0x4A0],r11                           
0x6659b96  jmp 0x665CF85                                 ; -> sub_665cf85
```
// INTERPRETATION [V]: case 1 of the first switch (table[1]=0x6659b88): stores [rbp+0x508] into [rbp+0x4A0], jumps to cold join 0x665CF85 [V].

## Phase C9 — Cubemap case switch case 2 0x6659b9b..0x6659cad (40 instr) [V]
```
0x6659b9b  movsd xmm0,[rdi+0x30]                         
0x6659ba0  movss xmm1,[rdi+0x38]                         
0x6659ba5  mov rax,[rdi+0x18]                            
0x6659ba9  movups xmm6,[rax]                             
0x6659bac  movaps [rbp+0x170],xmm6                       
0x6659bb3  movups xmm7,[rax+0x10]                        
0x6659bb7  movaps [rbp+0x180],xmm7                       
0x6659bbe  movups xmm8,[rax+0x20]                        
0x6659bc3  movaps [rbp+0x190],xmm8                       
0x6659bcb  movups xmm9,[rax+0x30]                        
0x6659bd0  movaps [rbp+0x1A0],xmm9                       
0x6659bd8  mov byte ptr [rbp+0x1B0],0                    
0x6659bdf  cmp byte ptr [rbp+0x538],0                    
0x6659be6  je 0x665DE4A                                  ; -> sub_665de4a
0x6659bec  mov r14w,[rdi+0x3C]                           
0x6659bf1  mov dword ptr [rbp+0x344],3                   
0x6659bfb  mov byte ptr [rbp+0x348],7                    
0x6659c02  mov dword ptr [rbp+0x34C],1                   
0x6659c0c  mov word ptr [rbp+0x350],1                    
0x6659c15  mov byte ptr [rbp+0x352],2                    
0x6659c1c  mov dword ptr [rbp+0x354],0                   
0x6659c26  mov byte ptr [rbp+0x358],0                    
0x6659c2d  xorps xmm10,xmm10                             
0x6659c31  movups [rbp+0x35C],xmm10                      
0x6659c39  movups [rbp+0x368],xmm10                      
0x6659c41  mov byte ptr [rbp+0x378],8                    
0x6659c48  mov qword ptr [rbp+0x37C],0                   
0x6659c53  mov dword ptr [rbp+0x384],0                   
0x6659c5d  mov byte ptr [rbp+0x388],8                    
0x6659c64  mov qword ptr [rbp+0x38C],0                   
0x6659c6f  mov qword ptr [rbp+0x392],0                   
0x6659c7a  mov byte ptr [rbp+0x39A],0xFF                 
0x6659c81  movlps [rbp+0x3A0],xmm0                       
0x6659c88  movss [rbp+0x3A8],xmm1                        
0x6659c90  mov rax,[rbp+0x50]                            
0x6659c94  mov [rbp+0x3B0],rax                           
0x6659c9b  lea rdi,[rbp+0x3B8]                           
0x6659ca2  mov rcx,rdi                                   
0x6659ca5  mov rdx,rbx                                   
0x6659ca8  call 0xE869FF0                                ; -> sub_e869ff0
0x6659cad  nop                                           
```
// INTERPRETATION [V]: case 2 (table[2]=0x6659b9b): rdi still = jump-table base 0xF2BF428; loads global data ([rdi+0x30],[rdi+0x38],[rdi+0x18]) [V]. rax=[rdi+0x18]=[0xF2BF440] (pointer in .rdata); copies the 64-byte block [rax]..[rax+0x30] into xmm6..xmm9 -> [rbp+0x170],[rbp+0x180],[rbp+0x190],[rbp+0x1A0] (a matrix/transform) [V]. [rbp+0x1B0]=0; `cmp byte [rbp+0x538],0; je 0x665DE4A` (sub_665de4a, undecoded helper) [V,I]. r14w=[rdi+0x3C] [V]. Rebuilds fixed descriptor rbp+0x344..0x39A (same field values as C7) [V]. movlps [rbp+0x3A0]=xmm0; movss [rbp+0x3A8]=xmm1; rax=[rbp+0x50]; [rbp+0x3B0]=rax [V]. lea rdi,[rbp+0x3B8]; call 0xE869FF0(rcx=&rbp+0x3B8, rdx=rbx=jump-table-target addr) [V].

## Phase C10 — Cubemap case case-2 cont. + second switch 0x6659cae..0x6659d5e (25 instr) [V]
```
0x6659cae  mov rax,[rbp+0xD0]                            
0x6659cb5  mov [rbp+0x430],rax                           
0x6659cbc  mov qword ptr [rbp+0xD0],0                    
0x6659cc7  movups [rbp+0x438],xmm6                       
0x6659cce  movups [rbp+0x448],xmm7                       
0x6659cd5  movups [rbp+0x458],xmm8                       
0x6659cdd  movups [rbp+0x468],xmm9                       
0x6659ce5  mov byte ptr [rbp+0x478],0                    
0x6659cec  mov [rbp+0x480],r14w                          
0x6659cf4  movaps xmm0,[rbp+0x4E0]                       
0x6659cfb  movaps xmm1,[rbp+0x4F0]                       
0x6659d02  mov qword ptr [rbp+0x4E8],0                   
0x6659d0d  movups [rbp+0x488],xmm0                       
0x6659d14  movaps [rbp+0x4F0],xmm10                      
0x6659d1c  movups [rbp+0x498],xmm1                       
0x6659d23  mov rax,[rbp+0x500]                           
0x6659d2a  mov [rbp+0x4A8],rax                           
0x6659d31  mov byte ptr [rbp+0x4C0],0xFF                 
0x6659d38  movzx eax,byte ptr [rbp+0x518]                
0x6659d3f  cmp rax,3                                     
0x6659d43  ja 0x665BB39                                  ; -> sub_665bb39
0x6659d49  lea rcx,[rbp+0x4B0]                           
0x6659d50  lea rdx,[0xF2BF408]                           ; [data_f2bf408]
0x6659d57  movsxd r8,[rdx+rax*4]                         
0x6659d5b  add r8,rdx                                    
0x6659d5e  jmp r8                                        
```
// INTERPRETATION [V]: Builds second args block rbp+0x430..0x4C0 ([rbp+0x430]=[rbp+0xD0], [rbp+0xD0]=0, xmm6..xmm9 -> [rbp+0x438..0x468], [rbp+0x480]=r14w, [rbp+0x4F0]=xmm10, [rbp+0x498]=[rbp+0x500], [rbp+0x4C0]=0xFF) [V]. Second switch on byte [rbp+0x518] (`cmp rax,3; ja 0x665BB39`) with jump table [0xF2BF408]: [0]=0x665bb33, [1]=0x6659d61, [2]=0x665b6cc, [3]=0x665b6de, [4]=0x665cfd6, [5]=0x665a097, [6]=0x665baa9, [7]=0x665bae4 [V]. `jmp r8` dispatches [V]. Case 0 = 0x665bb33 (common join), case 1 = 0x6659d61; cases 2..7 not taken by fall-through here [I].

## Phase C11 — second switch case 1 0x6659d61..0x6659d6f (3 instr) [V]
```
0x6659d61  mov rcx,[rbp+0x508]                           
0x6659d68  mov [rbp+0x4B0],rcx                           
0x6659d6f  jmp 0x665BB33                                 ; -> loc_665bb33
```
// INTERPRETATION [V]: case 1 of second switch: stores [rbp+0x508] into [rbp+0x4B0], jumps to common join 0x665BB33 [V].

## Phase C12 — common join / SKY-PUSH entry 0x665bb33..0x665bb63 (11 instr) [V]
```
0x665bb33  mov [rbp+0x4C0],al                            
0x665bb39  mov rax,[rbp+0x530]                           
0x665bb40  mov [rbp+0x4D8],rax                           
0x665bb47  movaps xmm0,[rbp+0x520]                       
0x665bb4e  movups [rbp+0x4C8],xmm0                       
0x665bb55  mov ecx,0x9D0                                 
0x665bb5a  add rcx,[rsi+0x10]                            
0x665bb5e  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x665bb63  nop                                           
0x665bb64  mov rsi,rax                                   
0x665bb67  lea rdx,[rbp+0x488]                           
```
// INTERPRETATION [V]: Common join reached from both switch tables (0x665bb33 case-0 target; 0x665bb39 is the `ja` default target, 6 bytes later). Sets [rbp+0x4C0]=al, [rbp+0x4D8]=[rbp+0x530], [rbp+0x4C8]=[rbp+0x520] [V]. `mov ecx,0x9D0; add rcx,[rsi+0x10]; call 0x5ABA5C0` — 0x9D0 is a component/ECS type hash (ActorRotationComponent-family) added to [rsi+0x10]; this is the shared SKY-PUSH submit call matching ext_particle_sky_callees.md section D (~0x665a8e5 region) [V,I]. rsi=rax (return ptr); lea rdx,[rbp+0x488] begins building push commands [V,I].

## Phase C13 — shared SKY-PUSH tail / exit 0x665a8e5..0x665aee8 [V]
The reachable SKY-PUSH body runs 0x665a8e5 (`mov [rbp+0x4B0],al` ... `call 0x5ABA5C0` ... `call 0x675F3B0`) then builds per-slot push commands ([rbp+0x208], [rbp+0x222] item counts via shr/imul of range diffs, retain/release of shared_ptrs via call [0xF99FFA0]=sub_eea6040, u16 writes to [rsi+0x8A8] etc.) [V]. All sub-paths converge at:

```
0x665a8a5  cmp byte ptr [rbp+0x520],1                    
0x665a8ac  jne 0x665AEE8                                 ; -> loc_665aee8
0x665a8b2  mov rcx,[rbp+0x4E0]                           
0x665a8b9  test rcx,rcx                                  
0x665a8bc  je 0x665AEE8                                  ; -> loc_665aee8
0x665a8c2  mov rdx,[rbp+0x4F0]                           
0x665a8c9  jmp 0x665AEBB                                 ; -> loc_665aebb
0x665aebb  sub rdx,rcx                                   
0x665aebe  cmp rdx,0x1000                                
0x665aec5  jb short 0x665AEE3                            ; -> loc_665aee3
0x665aec7  mov rax,[rcx-8]                               
0x665aecb  add rcx,0xFFFFFFFFFFFFFFF8                    
0x665aecf  sub rcx,rax                                   
0x665aed2  cmp rcx,0x20                                  
0x665aed6  jae 0x665D43A                                 ; -> sub_665d43a
0x665aedc  or rdx,0x27                                   
0x665aee0  mov rcx,rax                                   
0x665aee3  call 0xE935700                                ; -> sub_e935700
0x665aee8  mov rsi,[rbp+0x328]                           
0x665aeef  jmp 0x665D124                                 ; -> sub_665d124
```
// INTERPRETATION [V]: 0x665a8a5 branches: if [rbp+0x520]!=1 -> exit; else rcx=[rbp+0x4E0], if rcx==0 -> exit; else rdx=[rbp+0x4F0], jmp 0x665aebb (heap/alloc bounds check vs 0x1000; jae -> cold 0x665d43a; else or rdx,0x27) then call 0xE935700 (undecoded helper) [V,I]. Exit block 0x665aee8: `mov rsi,[rbp+0x328]` then `jmp 0x665D124` [V]. 0x665d124 is the function epilogue (sub_66560f0 spans 0x66560f0..0x665e7ae) [V]. Cubemap case EXIT CONFIRMED -> epilogue 0x665d124 [V].

## OPEN
- Exact selector value of byte [rbp+0x518] for the Cubemap case (set earlier in sub_66560f0, not within 0x6659615..0x665aee8) — determines which switch case is taken; all reachable paths converge at 0x665aee8 -> epilogue 0x665d124 regardless [?].
- Helper bodies undecoded: 0xE869FF0, 0x5ABA5C0, 0x675F3B0, 0xE935700, 0x6760710/0x6760A80/0x6760E60, 0xBCABA00, 0x5679DB0, 0x1751590, 0x1EF6F90, 0x66A6190, 0x66A9AD0, 0x5ABA6D0 [?].
- 0x665a8ce..0x665a8e5 block (`xor ecx,ecx; ...; call 0x5ABA5C0`) sits after `0x665a8c9 jmp 0x665AEBB` and is not a jump target anywhere in sub_66560f0 — treated as dead/compiler-placed code; the reachable SKY-PUSH body is at 0x665bb39/0x665bb64 [I].
- Exact meaning of flag bits / descriptor offsets [?].
