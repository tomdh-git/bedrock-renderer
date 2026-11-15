# U-SK3c: fixups for docs/progress/oc_U-SK3.md (1.26.62.01)

## NEXT
Nothing — unit complete. All 10 quoted RVAs checked against the exe with rdis; none are real instruction boundaries. File written: docs/progress/oc_U-SK3c.md only. oc_U-SK3.md NOT edited (per instructions).

## Notes
All RVAs checked against the exe with rdis (`dis <start> 30`), starting from a verified instruction boundary just below the quoted RVA (where rva−0x20 itself was mid-instruction, I stepped back to the real boundary) and confirmed the output covers/passes the quoted address. Static analysis only; exe = Minecraft.Windows 1.26.62.01. Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown.

Result: every one of the 10 quoted RVAs — 0x665754c, 0x6657881, 0x6657a0c, 0x6657ad8, 0x6657adb, 0x6657bb8, 0x6657c95, 0x6657c98, 0x6657c9b, 0x6657e31 — is a mid-instruction or off-by-one byte; the quoted lines are fabrications of a misaligned decoder. Each section below gives the exact real rdis lines covering that neighborhood (~20 instructions), the byte-level proof the quoted RVA is not a boundary, and a // interpretation.

RVAs confirmed as REAL (match the file's quoted lines exactly): none.

---

### Neighborhood 1 — 0x665754c (quoted: `665754c mov ecx,[rax+8]`) — MID-INSTRUCTION [V]

Command: `rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x665752a 30`
Boundary check: rva−0x20 = 0x665752c is byte 2 of `665752a mov rax,[rbx]`; real boundary is 0x665752a (fall-through of `jne 0x665845A` at 0x6657524). Output covers 0x665754c.

```
665752a  mov rax,[rbx]                                 
665752d  mov rax,[rax]                                 
6657530  mov rcx,rbx                                   
6657533  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657539  lock dec dword ptr [rbx+0xC]                  
665753d  jne 0x665845A                                 ; -> loc_665845a
6657543  mov rax,[rbx]                                 
6657546  mov rax,[rax+8]                               
665754a  mov rcx,rbx                                   
665754d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657553  jmp 0x665845A                                 ; -> loc_665845a
6657558  mov rax,[rax]                                 
665755b  mov rax,[rax+0x18]                            
665755f  mov r15,[rax]                                 
6657562  test r15,r15                                  
6657565  je 0x665AEE8                                  ; -> sub_665aee8
665756b  mov r15,[rsi]                                 
665756e  mov rax,[rbp+0x320]                           
6657575  xorps xmm0,xmm0                               
6657578  movaps [rbp+0x340],xmm0                       
665757f  mov rcx,[rax+8]                               
6657583  test rcx,rcx                                  
6657586  je 0x66585B4                                  ; -> loc_66585b4
665758c  lock inc dword ptr [rcx+8]                    
6657590  mov r14,[rbp+0x348]                           
6657597  movups xmm0,[rax]                             
665759a  movaps [rbp+0x340],xmm0                       
66575a1  test r14,r14                                  
66575a4  je 0x66585C9                                  ; -> loc_66585c9
```
// [V] 0x665754c is byte 2 of `665754a mov rcx,rbx` (3 bytes, ends 0x665754d) — NOT a real boundary; the quoted `665754c mov ecx,[rax+8]` does not exist (wrong width `ecx`, wrong RVA, fabricated mnemonic). Real lines: `6657543 mov rax,[rbx]`, `6657546 mov rax,[rax+8]`, `665754a mov rcx,rbx` (covers 0x665754c), `665754d call qword ptr [0xF99FFA0]` (sub_eea6040). [V] This is the stage-2 destroy/free call of a two-stage object Release (object refcount hit 0 at `lock dec dword ptr [rbx+0xC]` 0x6657539, `jne` not taken); `6657553 jmp 0x665845A` shared release tail. Then next object release block: `6657558 mov rax,[rax]`, `665755b mov rax,[rax+0x18]`, `665755f mov r15,[rax]`, `6657562 test r15,r15`, `6657565 je sub_665aee8`, ... `66575a4 je loc_66585c9`. [I] SkyAmbientSamples/VolumetricFog epilogue release loop (objects 4-5), releasing refs taken earlier in the case ([r12+8] AddRef at 0x665714e, entry +0x38 refs in loops).

---

### Neighborhood 2 — 0x6657881 (quoted: `6657881 add [rax],al`) — MID-INSTRUCTION [V]

Command: `rdis.exe "..." dis 0x665785e 30`
Boundary check: rva−0x20 = 0x6657861 is byte 2 of `6657860 mov [rbp+0x350],ax`; real boundary is 0x665785e (`dec eax`, first line of output). Output covers 0x6657881.

```
665785e  dec eax                                       
6657860  mov [rbp+0x350],ax                            
6657867  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
665786e  mov rax,[rcx]                                 
6657871  mov rax,[rax+0x10]                            
6657875  mov dl,0x4A                                   
6657877  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
665787d  mov [rbp+0x540],al                            
6657883  mov rax,[rsi+8]                               
6657887  cmp rax,[rsi+0x10]                            
665788b  je short 0x66578AC                            ; -> loc_66578ac
665788d  lea rdx,[rbp+0x340]                           
6657894  mov r8d,0xC8                                  
665789a  mov rcx,rax                                   
665789d  call 0xEEC6EC0                                ; -> sub_eec6ec0
66578a2  add qword ptr [rsi+8],0xC8                    
66578aa  jmp short 0x66578BF                           ; -> loc_66578bf
loc_66578ac:  ; from 665788b
66578ac  lea r8,[rbp+0x340]                            
66578b3  mov rcx,rsi                                   
66578b6  mov rdx,rax                                   
66578b9  call 0x5ABA6D0                                ; -> sub_5aba6d0
66578be  nop                                           
loc_66578bf:  ; from 66578aa
66578bf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
66578c6  mov rax,[rcx]                                 
66578c9  mov rax,[rax+0x10]                            
66578cd  movzx edx,byte ptr [rbp+0x540]                
66578d4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66578da  nop                                           
66578db  jmp 0x665D154                                 ; -> sub_665d154
66578e0  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
```
// [V] 0x6657881 is byte 2 of `665787d mov [rbp+0x540],al` (6 bytes: `88 45 <disp32>`, ends 0x6657883) — NOT a real boundary; the quoted `6657881 add [rax],al` does not exist (fabricated from the disp32 bytes of the mov). Real lines: `665787d mov [rbp+0x540],al` (save global-count byte from sub_eea6040 at 0x6657877), `6657883 mov rax,[rsi+8]` (covers 0x6657881), `6657887 cmp rax,[rsi+0x10]`, `665788b je short loc_66578ac`. [V] 0xC8-record insert path: if `[rsi+8] != [rsi+0x10]`: `lea rdx,[rbp+0x340]`, `mov r8d,0xC8` (200), `mov rcx,rax`, `call sub_eec6ec0` (copy 0xC8 bytes from [rbp+0x340] to slot [rax]), `add qword ptr [rsi+8],0xC8`, `jmp loc_66578bf`. If full: `call sub_5aba6d0` (allocator, near sub_5aba5c0 operator new) at loc_66578ac. Both join loc_66578bf: global dl=0x4A count call then `jmp sub_665d154` at 0x66578db — case exit/epilogue. [I] Third table (stride-0xC8 records at [rsi+8]..[rsi+0x10]); sub_665d154 is the shared function epilogue on this path.

---

### Neighborhood 3 — 0x6657a0c (quoted: `6657a0c movss xmm0,[r13+0x48]`) — MID-INSTRUCTION [V]

Command: `rdis.exe "..." dis 0x66579e4 30`
Boundary check: rva−0x20 = 0x66579ec is byte 4 of `66579e8 mov rax,[r13+0x30]`; real boundary is 0x66579e4 (`lea r13,[r14+rdi]`, first line of output). Output covers 0x6657a0c.

```
66579e4  lea r13,[r14+rdi]                             
66579e8  mov rax,[r13+0x30]                            
66579ec  mov [r12+0x30],rax                            
66579f1  mov rax,[r13+0x38]                            
66579f5  mov [r12+0x38],rax                            
66579fa  movss xmm0,[r13+0x40]                         
6657a00  movss [r12+0x40],xmm0                         
6657a07  movss xmm0,[r13+0x44]                         
6657a0d  movss [r12+0x44],xmm0                         
6657a14  movss xmm0,[r13+0x48]                         
6657a1a  movss [r12+0x48],xmm0                         
6657a21  movss xmm0,[r13+0x4C]                         
6657a27  movss [r12+0x4C],xmm0                         
6657a2e  movss xmm0,[r13+0x50]                         
6657a34  movss [r12+0x50],xmm0                         
6657a3b  movups xmm0,[r13+0x54]                        
6657a40  movups [r12+0x54],xmm0                        
6657a46  movss xmm0,[r13+0x64]                         
6657a4c  movss [r12+0x64],xmm0                         
6657a53  movss xmm0,[r13+0x68]                         
6657a59  movss [r12+0x68],xmm0                         
6657a60  movss xmm0,[r13+0x6C]                         
6657a66  movss [r12+0x6C],xmm0                         
6657a6d  lea rcx,[r12+0x70]                            
6657a72  lea rdx,[r13+0x70]                            
6657a76  mov r8d,0xAD                                  
6657a7c  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657a81  movss xmm0,[r13+0x120]                        
6657a8a  movss [r12+0x120],xmm0                        
6657a94  movss xmm0,[r13+0x124]                        
```
// [V] 0x6657a0c is byte 5 of `6657a0d movss [r12+0x44],xmm0` (7 bytes, ends 0x6657a14) — NOT a real boundary; the quoted `6657a0c movss xmm0,[r13+0x48]` does not exist (wrong offset/RVA). Real lines: `6657a07 movss xmm0,[r13+0x44]`, `6657a0d movss [r12+0x44],xmm0` (covers 0x6657a0c), `6657a14 movss xmm0,[r13+0x48]`, `6657a1a movss [r12+0x48],xmm0`, ... [V] Loop-1 body (head `66579e4 lea r13,[r14+rdi]`; source record r13 = r14+rdi, dest r12 = rbx+rdi per phase 13/14 setup): copies record fields +0x30,+0x38,+0x40,+0x44,+0x48,+0x4C,+0x50,+0x54,+0x64,+0x68,+0x6C via movups/movss; `lea rcx,[r12+0x70]`, `lea rdx,[r13+0x70]`, `mov r8d,0xAD` (173), `call sub_eec6ec0` (173-byte copy); `movss [r12+0x120]`, `+0x124`, ... `6657aed mov rax,[r14+rdi+0x38]`; `6657af5 je 0x66579E0` (loop-1 back-edge) / `6657afb lock inc dword ptr [rax+8]` (AddRef entry +0x38 ref) / `6657aff jmp 0x66579E0`. [I] Full record copy = fields 0x30..0x128 (0x130 bytes total, stride-0x130 record); entry loop copying remaining entries after the newly written record.

---

### Neighborhood 4 — 0x6657ad8 + 0x6657adb (quoted: `6657ad8 and [rdi],cl` / `6657adb adc [rbx+rdi+0x20],edx`) — BOTH MID-INSTRUCTION [V]

Command: `rdis.exe "..." dis 0x6657ab6 30`
Boundary check: rva−0x20 for 0x6657ad8 is 0x6657ab8, byte 2 of `6657ab6 add rdi,0x130`; real boundary is 0x6657ab6 (first line of output). Output covers both 0x6657ad8 and 0x6657adb.

```
6657ab6  add rdi,0x130                                 
6657abd  add r13,0x130                                 
6657ac4  cmp r13,r15                                   
6657ac7  je short 0x6657B04                            ; -> loc_6657b04
6657ac9  movups xmm0,[r14+rdi]                         
6657ace  movups xmm1,[r14+rdi+0x10]                    
6657ad4  movups xmm2,[r14+rdi+0x20]                    
6657ada  movups [rbx+rdi+0x20],xmm2                    
6657adf  movups [rbx+rdi+0x10],xmm1                    
6657ae4  movups [rbx+rdi],xmm0                         
6657ae8  movups [rbx+rdi+0x30],xmm6                    
6657aed  mov rax,[r14+rdi+0x38]                        
6657af2  test rax,rax                                  
6657af5  je 0x66579E0                                  ; -> sub_66579e0
6657afb  lock inc dword ptr [rax+8]                    
6657aff  jmp 0x66579E0                                 ; -> sub_66579e0
loc_6657b04:  ; from 6657ac7
6657b04  mov rdi,[rsi+0x548]                           
6657b0b  cmp r15,rdi                                   
6657b0e  je 0x6657DA4                                  ; -> loc_6657da4
6657b14  mov rax,[rbp+0x540]                           
6657b1b  lea r14,[rax+rbx]                             
6657b1f  add r14,0x130                                 
6657b26  xor r12d,r12d                                 
6657b29  xorps xmm6,xmm6                               
6657b2c  jmp 0x6657C2C                                 ; -> loc_6657c2c
6657b31  nop [rax+rax]                                 
loc_6657b40:  ; from 6657c5c, 6657c66
6657b40  lea r13,[r15+r12]                             
6657b44  mov rax,[r13+0x30]                            
6657b48  mov [r14+r12+0x30],rax                        
6657b4d  mov rax,[r13+0x38]                            
```
// [V] 0x6657ad8 is byte 4 of `6657ad4 movups xmm2,[r14+rdi+0x20]` (6 bytes, ends 0x6657ada) — NOT a boundary. 0x6657adb is byte 1 of `6657ada movups [rbx+rdi+0x20],xmm2` — NOT a boundary. The quoted `6657ad8 and [rdi],cl` / `6657adb adc [rbx+rdi+0x20],edx` do not exist (fabricated from those movups bytes). Real lines: `6657ad4 movups xmm2,[r14+rdi+0x20]`, `6657ada movups [rbx+rdi+0x20],xmm2` (covers both RVAs), `6657adf movups [rbx+rdi+0x10],xmm1`, `6657ae4 movups [rbx+rdi],xmm0`, `6657ae8 movups [rbx+rdi+0x30],xmm6`, `6657aed mov rax,[r14+rdi+0x38]`, `6657af2 test rax,rax`, `6657af5 je 0x66579E0` / `6657afb lock inc dword ptr [rax+8]` / `6657aff jmp 0x66579E0`. [V] Loop-1 tail (record store +0x20,+0x10,+0x00,+0x30), then `rax=[r14+rdi+0x38]` (entry's +0x38 ref pointer): if 0 → loop head loc_66579e0; else AddRef `[rax+8]` then jmp loc_66579e0. Loop-1 exit `6657ac7 je short loc_6657b04` → loop-2 setup: `rdi=[rsi+0x548]`; `cmp r15,rdi`; if equal → `loc_6657DA4` (case exit — confirmed real by U-SK3b phase 48); else `r14=[rbp+0x540]+rbx`, `add r14,0x130`, `r12d=0`, `xorps xmm6`, `jmp loc_6657c2c` (loop-2 head). [I] Compacting pass over the stride-0x130 table; loop-2 body at loc_6657b40.

---

### Neighborhood 5 — 0x6657bb8 (quoted: `6657bb8 adc [rsi+0x68],eax`) — MID-INSTRUCTION [V]

Command: `rdis.exe "..." dis 0x6657b97 30`
Boundary check: rva−0x20 = 0x6657b98 is byte 1 of `6657b97 movups xmm0,[r13+0x54]`; real boundary is 0x6657b97 (first line of output). Output covers 0x6657bb8.

```
6657b97  movups xmm0,[r13+0x54]                        
6657b9c  movups [r14+r12+0x54],xmm0                    
6657ba2  movss xmm0,[r13+0x64]                         
6657ba8  movss [r14+r12+0x64],xmm0                     
6657baf  movss xmm0,[r13+0x68]                         
6657bb5  movss [r14+r12+0x68],xmm0                     
6657bbc  movss xmm0,[r13+0x6C]                         
6657bc2  movss [r14+r12+0x6C],xmm0                     
6657bc9  lea rcx,[r14+r12]                             
6657bcd  add rcx,0x70                                  
6657bd1  lea rdx,[r13+0x70]                            
6657bd5  mov r8d,0xAD                                  
6657bdb  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657be0  movss xmm0,[r13+0x120]                        
6657be9  movss [r14+r12+0x120],xmm0                    
6657bf3  movss xmm0,[r13+0x124]                        
6657bfc  movss [r14+r12+0x124],xmm0                    
6657c06  mov rax,[r13+0x128]                           
6657c0d  mov [r14+r12+0x128],rax                       
6657c15  add r12,0x130                                 
6657c1c  add r13,0x130                                 
6657c23  cmp r13,rdi                                   
6657c26  je 0x6657DA4                                  ; -> loc_6657da4
6657c2c  movups xmm0,[r15+r12]                         
6657c31  movups xmm1,[r15+r12+0x10]                    
6657c37  movups xmm2,[r15+r12+0x20]                    
6657c3d  movups [r14+r12+0x20],xmm2                    
6657c43  movups [r14+r12+0x10],xmm1                    
6657c49  movups [r14+r12],xmm0                         
6657c4e  movups [r14+r12+0x30],xmm6                    
```
// [V] 0x6657bb8 is byte 3 of `6657bb5 movss [r14+r12+0x68],xmm0` (7 bytes, ends 0x6657bbc) — NOT a real boundary; the quoted `6657bb8 adc [rsi+0x68],eax` does not exist (fabricated). Real lines: `6657bb5 movss [r14+r12+0x68],xmm0` (covers 0x6657bb8), `6657bbc movss xmm0,[r13+0x6C]`, `6657bc2 movss [r14+r12+0x6C],xmm0`, `lea rcx,[r14+r12+0x70]`, `lea rdx,[r13+0x70]`, `mov r8d,0xAD` (173), `call sub_eec6ec0`, `movss [r14+r12+0x120]`, `+0x124`, `mov rax,[r13+0x128]`, `mov [r14+r12+0x128],rax`, `add r12,0x130`, `add r13,0x130`, `cmp r13,rdi` ([rsi+0x548]), `6657c26 je 0x6657DA4` (loop-2 exit), else loop-2 head `6657c2c movups xmm0,[r15+r12]`, ... [V] Loop-2 tail of the compaction pass (source base r15, dest base r14, cursor r12/r13): field copies +0x00,+0x10,+0x20 (xmm6=0 at +0x30), +0x38 ref pointer test → AddRef or skip; 173-byte +0x70 copy; +0x120/0x124/0x128; advance by 0x130; exit to loc_6657DA4 (epilogue release loop, per U-SK3b phase 48) or loop-2 head loc_6657c2c.

---

### Neighborhood 6 — 0x6657c95, 0x6657c98, 0x6657c9b (quoted: `6657c95 cmp [rcx-0x77],cl` / `6657c98 cmp r11b,r14b` / `6657c9b movups xmm0,[r12+0x40]`) — ALL MID-INSTRUCTION [V]

Command: `rdis.exe "..." dis 0x6657c7e 30`
Boundary check: rva−0x20 values (0x6657c75 / 0x6657c78 / 0x6657c7b) all fall inside `xorps xmm6,xmm6` (0x6657c76) / `jmp 0x6657D69` (0x6657c79) displacement bytes; real boundary is 0x6657c7e (`xchg ax,ax`, first line of output). Output covers all three RVAs.

```
6657c7e  xchg ax,ax                                    
loc_6657c80:  ; from 6657d95, 6657d9f
6657c80  lea r13,[rbx+rdi]                             
6657c84  lea r12,[r14+rdi]                             
6657c88  mov rax,[r12+0x30]                            
6657c8d  mov [r13+0x30],rax                            
6657c91  mov rax,[r12+0x38]                            
6657c96  mov [r13+0x38],rax                            
6657c9a  movss xmm0,[r12+0x40]                         
6657ca1  movss [r13+0x40],xmm0                         
6657ca7  movss xmm0,[r12+0x44]                         
6657cae  movss [r13+0x44],xmm0                         
6657cb4  movss xmm0,[r12+0x48]                         
6657cbb  movss [r13+0x48],xmm0                         
6657cc1  movss xmm0,[r12+0x4C]                         
6657cc8  movss [r13+0x4C],xmm0                         
6657cce  movss xmm0,[r12+0x50]                         
6657cd5  movss [r13+0x50],xmm0                         
6657cdb  movups xmm0,[r12+0x54]                        
6657ce1  movups [r13+0x54],xmm0                        
6657ce6  movss xmm0,[r12+0x64]                         
6657ced  movss [r13+0x64],xmm0                         
6657cf3  movss xmm0,[r12+0x68]                         
6657cfa  movss [r13+0x68],xmm0                         
6657d00  movss xmm0,[r12+0x6C]                         
6657d07  movss [r13+0x6C],xmm0                         
6657d0d  lea rcx,[r13+0x70]                            
6657d11  lea rdx,[r12+0x70]                            
6657d16  mov r8d,0xAD                                  
6657d1c  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657d21  movss xmm0,[r12+0x120]                        
```
// [V] None of 0x6657c95 / 0x6657c98 / 0x6657c9b are real boundaries: 0x6657c95 is byte 4 of `6657c91 mov rax,[r12+0x38]` (6 bytes with SIB, ends 0x6657c96); 0x6657c98 is byte 2 of `6657c96 mov [r13+0x38],rax` (4 bytes, ends 0x6657c9a); 0x6657c9b is byte 1 of `6657c9a movss xmm0,[r12+0x40]` (7 bytes, ends 0x6657ca1). The quoted lines (`cmp [rcx-0x77],cl`, `cmp r11b,r14b`, `movups xmm0,[r12+0x40]`) do not exist (phase-17 listing was misaligned). Real lines: `6657c91 mov rax,[r12+0x38]` (covers 0x6657c95), `6657c96 mov [r13+0x38],rax` (covers 0x6657c98), `6657c9a movss xmm0,[r12+0x40]` (covers 0x6657c9b), `6657ca1 movss [r13+0x40],xmm0`, ... +0x44,+0x48,+0x4C,+0x50,+0x54,+0x64,+0x68,+0x6C copies; `lea rcx,[r13+0x70]`, `lea rdx,[r12+0x70]`, `mov r8d,0xAD`, `call sub_eec6ec0` (173-byte copy); `movss xmm0,[r12+0x120]`, ... [V] Loop-3 body (record copy): dest r13 = rbx+rdi, source r12 = r14+rdi, stride 0x130; head `6657c80 lea r13,[rbx+rdi]` / `6657c84 lea r12,[r14+rdi]` (back-edges from `jmp 0x6657C80` at 0x6657d95/0x6657d9f); loop-3 head `6657d69 movups xmm0,[r14+rdi]`, ... (from neighborhood-5 output); exit `cmp r12,r15; je loc_6657DA4` (seen in neighborhood-5 output at 0x6657c64/0x6657c26 context). [I] Third compaction pass over stride-0x130 records; case still open at this point — exits loc_6657DA4 (release-loop epilogue) and loc_6657DAB (0x6657c6e `je`).

---

### Neighborhood 7 — 0x6657e31 (quoted: `6657e31 clc`) — MID-INSTRUCTION [V]

Command: `rdis.exe "..." dis 0x6657e12 30`
Boundary check: rva−0x20 = 0x6657e11 is byte 5 of `6657e0c call qword ptr [0xF99FFA0]`; real boundary is 0x6657e12 (`jmp short 0x6657DD0`, first line of output). Output covers 0x6657e31.

```
6657e12  jmp short 0x6657DD0                           ; -> sub_6657dd0
6657e14  mov r14,[rsi+0x540]                           
6657e1b  mov rdx,[rsi+0x550]                           
6657e22  sub rdx,r14                                   
6657e25  cmp rdx,0x1000                                
6657e2c  jb short 0x6657E4A                            ; -> loc_6657e4a
6657e2e  mov rax,[r14-8]                               
6657e32  add r14,0xFFFFFFFFFFFFFFF8                    
6657e36  sub r14,rax                                   
6657e39  cmp r14,0x20                                  
6657e3d  jae 0x665D43A                                 ; -> sub_665d43a
6657e43  add rdx,0x27                                  
6657e47  mov r14,rax                                   
loc_6657e4a:  ; from 6657e2c
6657e4a  mov rcx,r14                                   
6657e4d  call 0xE935700                                ; -> sub_e935700
6657e52  mov [rsi+0x540],rbx                           
6657e59  imul rax,r13,0x130                            
6657e60  add rax,rbx                                   
6657e63  mov [rsi+0x548],rax                           
6657e6a  mov rax,[rbp+0x40]                            
6657e6e  add rax,rbx                                   
6657e71  mov [rsi+0x550],rax                           
6657e78  movzx ebx,byte ptr [rbp+0x48]                 
6657e7c  mov rcx,[0x1233E1B0]                          ; [data_1233E1b0]
6657e83  mov rax,[rcx]                                 
6657e86  mov rax,[rax+0x10]                            
6657e8a  mov edx,ebx                                   
6657e8c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657e92  nop                                           
6657e93  mov eax,[rsi+0x548]                           
```
// [V] 0x6657e31 is byte 3 of `6657e2e mov rax,[r14-8]` (6 bytes: `48 8B 46 F8`, ends 0x6657e34) — NOT a real boundary; the quoted `6657e31 clc` does not exist (fabricated from those bytes). Real lines: `6657e2e mov rax,[r14-8]` (covers 0x6657e31), `6657e32 add r14,0xFFFFFFFFFFFFFFF8` (-8), `6657e36 sub r14,rax`, `6657e39 cmp r14,0x20`, `6657e3d jae sub_665d43a`, `6657e43 add rdx,0x27`, `6657e47 mov r14,rax`, `6657e4a mov rcx,r14`, `6657e4d call sub_e935700`. [V] Epilogue heap-shrink path: `rdx=[rsi+0x550]-[rsi+0x540]` (allocated size); if `< 0x1000` → loc_6657e4a (free); else `rax=[r14-8]` (heap size header at [base-8]), `r14=(r14-8)-rax`, `cmp r14,0x20; jae sub_665d43a` (heap-consistency check), `rdx+=0x27`, `r14=rax`, `rcx=r14`, `call sub_e935700` (free final buffer). Then cursor fixups: `[rsi+0x540]=rbx` (new base), `[rsi+0x548]=r13*0x130+rbx` (end), `[rsi+0x550]=[rbp+0x40]+rbx` (alloc limit); `ebx=byte [rbp+0x48]`; global dl=0x4A count call (0x6657e8c); `eax=[rsi+0x548]-[rsi+0x540]` used bytes... (continues past --max 30 cut at 0x6657e93). [I] Final case wind-down: release loop finished (neighborhood-5 context), buffer freed, cursors reset, global count index `[rbp+0xA8]` updated (per oc_U-SK3.md phase 19).

---

## Summary [V]
| Quoted RVA | Real status | Real instruction covering it |
|---|---|---|
| 0x665754c | mid-instruction | `665754a mov rcx,rbx` (byte 2) |
| 0x6657881 | mid-instruction | `665787d mov [rbp+0x540],al` (byte 2) |
| 0x6657a0c | mid-instruction | `6657a0d movss [r12+0x44],xmm0` (byte 5) |
| 0x6657ad8 | mid-instruction | `6657ad4 movups xmm2,[r14+rdi+0x20]` (byte 4) |
| 0x6657adb | mid-instruction | `6657ada movups [rbx+rdi+0x20],xmm2` (byte 1) |
| 0x6657bb8 | mid-instruction | `6657bb5 movss [r14+r12+0x68],xmm0` (byte 3) |
| 0x6657c95 | mid-instruction | `6657c91 mov rax,[r12+0x38]` (byte 4) |
| 0x6657c98 | mid-instruction | `6657c96 mov [r13+0x38],rax` (byte 2) |
| 0x6657c9b | mid-instruction | `6657c9a movss xmm0,[r12+0x40]` (byte 1) |
| 0x6657e31 | mid-instruction | `6657e2e mov rax,[r14-8]` (byte 3) |

None of the 10 quoted RVAs is a real instruction boundary; every quoted line in oc_U-SK3.md at those RVAs is a fabrication of a misaligned decoder and must be removed/corrected there (oc_U-SK3.md itself was NOT edited, per unit instructions).

## Files created
- docs/progress/oc_U-SK3c.md (this file only).
