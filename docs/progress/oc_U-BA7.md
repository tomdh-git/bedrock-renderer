# Unit U-BA7 — bodyActor function 0x66d0a00 (1.26.62.01), continued from oc_U-BA6.md

## NEXT [current]
Unit scope complete: 15/15 phases written (0x66d5904..0x66d6558, last quoted RVA 0x66d6558). Resume RVA (instruction 41 of phase 15 `dis 0x66d6486 41`): 0x66d6562 `xor r8d,r8d` — taken directly from rdis output via `dis 0x66d6552 4`; no further phases needed per unit scope.
Next call (if resuming):
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6562 41`
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Phase 1 — 0x66d5904, 40 instructions [V]
```
0x66d5904  call 0x67D1120                                ; -> sub_67d1120
0x66d5909  mov rdi,[rbp+0xAA0]                           
0x66d5910  jmp 0x66D5A28                                 ; -> loc_66d5a28
0x66d5915  pxor xmm0,xmm0                                
0x66d5919  movdqu [rcx],xmm0                             
0x66d591d  mov rax,[rbp+0xA58]                           
0x66d5924  test rax,rax                                  
0x66d5927  je short 0x66D5936                            ; -> loc_66d5936
0x66d5929  lock inc dword ptr [rax+8]                    
0x66d592d  mov rax,[rbp+0xA58]                           
0x66d5934  jmp short 0x66D5938                           ; -> loc_66d5938
0x66d5936  xor eax,eax                                   
0x66d5938  mov rcx,[rbp+0xA50]                           
0x66d593f  mov [rbp+0x868],rcx                           
0x66d5946  mov [rbp+0x870],rax                           
0x66d594d  movdqu xmm1,[rbp+0xA60]                       
0x66d5955  movdqu [rbp+0x878],xmm1                       
0x66d595d  movzx eax,word ptr [rbp+0xA70]                
0x66d5964  mov [rbp+0x888],ax                            
0x66d596b  movdqu [rbp+0x890],xmm0                       
0x66d5973  mov rax,[rbp+0xA80]                           
0x66d597a  test rax,rax                                  
0x66d597d  je short 0x66D598C                            ; -> loc_66d598c
0x66d597f  lock inc dword ptr [rax+8]                    
0x66d5983  mov rax,[rbp+0xA80]                           
0x66d598a  jmp short 0x66D598E                           ; -> loc_66d598e
0x66d598c  xor eax,eax                                   
0x66d598e  mov rdx,[rbp+0xA78]                           
0x66d5995  mov rcx,[rbp+0xA90]                           
0x66d599c  mov [rbp+0x890],rdx                           
0x66d59a3  mov [rbp+0x898],rax                           
0x66d59aa  movdqu [rbp+0x8A0],xmm0                       
0x66d59b2  test rcx,rcx                                  
0x66d59b5  je short 0x66D59C4                            ; -> loc_66d59c4
0x66d59b7  lock inc dword ptr [rcx+8]                    
0x66d59bb  mov rax,[rbp+0xA90]                           
0x66d59c2  jmp short 0x66D59C6                           ; -> loc_66d59c6
0x66d59c4  xor eax,eax                                   
0x66d59c6  mov rdx,[rbp+0xA88]                           
0x66d59cd  mov rcx,[rbp+0xAA0]                           
```
// [V] Phase 1 continues straight out of U-BA6 phase 12 at the `call 0x67D1120` (sub_67d1120, rcx=&rbp+0x868, rdx=&rbp+0xA50, gated on [rbp+0x8C8]==1) [V]. `jmp 0x66d5a28` skips the target block at 0x66d5915 [V]. Block at 0x66d5915 (target of phase-12's `jne 0x66d5915`): `pxor xmm0,xmm0; movdqu [rcx],xmm0` zeroes 16 bytes at rcx=&rbp+0x868 [V]. Then three null-safe intrusive addref patterns, each `mov rax,[rbp+0xA58]; test rax,rax; je short 0x66d5936 (else lock inc dword ptr [rax+8]); ... loc_66d5936: xor eax,eax` — refcounted pointer [rbp+0xA58] with [rax+8] R/W addref, null path yields eax=0 [V]; same shape for [rbp+0xA80] at 0x66d5973..0x66d598a (null exit 0x66d598c `xor eax,eax`) [V]; same for [rbp+0xA90] held in rcx at 0x66d59b2..0x66d59c2 (`lock inc dword ptr [rcx+8]`, null exit 0x66d59c4 `xor eax,eax`) [V]. Field stores between: `[rbp+0x868]=[rbp+0xA50]`; `[rbp+0x870]=rax` (addref result #1) [V]; `movdqu xmm1=[rbp+0xA60]; [rbp+0x878]=xmm1` (16-byte copy) [V]; `movzx eax,word ptr [rbp+0xA70]; [rbp+0x888]=ax` (word copy) [V]; `[rbp+0x890]=xmm0` (zero 16 bytes) [V]; `[rbp+0x890]=[rbp+0xA78]`; `[rbp+0x898]=rax` (addref result #2) [V]; `[rbp+0x8A0]=xmm0` (zero 16 bytes); `[rbp+0x8A0]=[rbp+0xA88]`; `rcx=[rbp+0xAA0]` (consistent with `mov rdi,[rbp+0xAA0]` at 0x66d5909) [V]. Fields touched: [rbp+0x868]/[rbp+0x870]/[rbp+0x878]/[rbp+0x888]/[rbp+0x890]/[rbp+0x898]/[rbp+0x8A0] W (zero-init block) [V]; [rbp+0xA58]/[rbp+0xA80]/[rbp+0xA90] R, [rax+8]/[rcx+8] R/W addref [V]; [rbp+0xA60]/[rbp+0xA70]/[rbp+0xA78]/[rbp+0xA88]/[rbp+0xAA0] R [V]. Callee: sub_67d1120 (0x67D1120) [V] role/signature [?]. rdis instruction 41 = `0x66d59d4 mov [rbp+0x8A0],rdx` → next phase starts at 0x66d59d4 [V].

## Phase 2 — 0x66d59d4, 40 instructions [V]
```
0x66d59d4  mov [rbp+0x8A0],rdx                           
0x66d59db  mov [rbp+0x8A8],rax                           
0x66d59e2  movdqu [rbp+0x8B0],xmm0                       
0x66d59ea  test rcx,rcx                                  
0x66d59ed  je short 0x66D59FC                            ; -> loc_66d59fc
0x66d59ef  lock inc dword ptr [rcx+8]                    ; W a0+0x8
0x66d59f3  mov rdi,[rbp+0xAA0]                           
0x66d59fa  jmp short 0x66D59FE                           ; -> loc_66d59fe
0x66d59fc  xor edi,edi                                   
0x66d59fe  mov rax,[rbp+0xA98]                           
0x66d5a05  mov rcx,[rbp+0xAA8]                           
0x66d5a0c  mov [rbp+0x8B0],rax                           
0x66d5a13  mov [rbp+0x8B8],rdi                           
0x66d5a1a  mov [rbp+0x8C0],rcx                           
0x66d5a21  mov byte ptr [rbp+0x8C8],1                    
0x66d5a28  test rdi,rdi                                  
0x66d5a2b  je short 0x66D5A58                            ; -> loc_66d5a58
0x66d5a2d  lock dec dword ptr [rdi+8]                    
0x66d5a31  jne short 0x66D5A58                           ; -> loc_66d5a58
0x66d5a33  mov rax,[rdi]                                 
0x66d5a36  mov rax,[rax]                                 
0x66d5a39  mov rcx,rdi                                   
0x66d5a3c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5a42  lock dec dword ptr [rdi+0xC]                  
0x66d5a46  jne short 0x66D5A58                           ; -> loc_66d5a58
0x66d5a48  mov rax,[rdi]                                 
0x66d5a4b  mov rax,[rax+8]                               
0x66d5a4f  mov rcx,rdi                                   
0x66d5a52  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5a58  mov rdi,[rbp+0xA90]                           
0x66d5a5f  test rdi,rdi                                  
0x66d5a62  je short 0x66D5A8F                            ; -> loc_66d5a8f
0x66d5a64  lock dec dword ptr [rdi+8]                    
0x66d5a68  jne short 0x66D5A8F                           ; -> loc_66d5a8f
0x66d5a6a  mov rax,[rdi]                                 
0x66d5a6d  mov rax,[rax]                                 
0x66d5a70  mov rcx,rdi                                   
0x66d5a73  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5a79  lock dec dword ptr [rdi+0xC]                  
0x66d5a7d  jne short 0x66D5A8F                           ; -> loc_66d5a8f
```
// [V] Phase 2 completes the init block: `mov [rbp+0x8A0],rdx` ([rbp+0xA88]) and `mov [rbp+0x8A8],rax` (addref result of [rbp+0xA90] chain) [V]; fourth null-safe addref on `rcx=[rbp+0xAA0]`: `test rcx,rcx; je 0x66d59fc (xor edi,edi); else lock inc dword ptr [rcx+8]; mov rdi,[rbp+0xAA0]` — result in rdi ([rbp+0xAA0] or 0) [V]. Store phase: `[rbp+0x8B0]=[rbp+0xA98]` (overwrites the xmm0 zero at 0x66d59e2) [V]; `[rbp+0x8B8]=rdi`; `[rbp+0x8C0]=[rbp+0xAA8]`; `mov byte ptr [rbp+0x8C8],1` — this is the flag that gated the phase-1 `call 0x67D1120` [V]. Release #1 (intrusive dtor+free via qword ptr [0xF99FFA0]=sub_eea6040 [V], roles [I]) on old rdi=[rbp+0xAA0]: `test rdi,rdi; je 0x66d5a58; lock dec dword ptr [rdi+8]; jne 0x66d5a58; else rax=[rdi]; rax=[rax] vtable[0]; rcx=rdi; call sub_eea6040 dtor [I] (0x66d5a3c); lock dec dword ptr [rdi+0xC]; jne 0x66d5a58; else rax=[rdi]; rax=[rax+8]; rcx=rdi; call sub_eea6040 free [I] (0x66d5a52)` [V]. Release #2 begins on `rdi=[rbp+0xA90]`: `test rdi,rdi; je short 0x66d5a8f; lock dec dword ptr [rdi+8]; jne short 0x66d5a8f; else rax=[rdi]; rax=[rax]; rcx=rdi; call sub_eea6040 dtor [I] (0x66d5a73 — last quoted insn); lock dec dword ptr [rdi+0xC]; jne short 0x66d5a8f` — free tail continues phase 3 [V]. Fields touched: [rbp+0x8A0] W, [rbp+0x8A8] W, [rbp+0x8B0] W, [rbp+0x8B8] W, [rbp+0x8C0] W, [rbp+0x8C8] W=1 [V]; [rbp+0xA98]/[rbp+0xAA8]/[rbp+0xAA0] R, [rcx+8] R/W addref [V]; [rbp+0xA90] R→rdi, [rdi+8]/[rdi+0xC] R/W dec [V]. Callees: sub_eea6040 via [0xF99FFA0] [V], dtor+free roles [I]. rdis instruction 41 = `0x66d5a7f mov rax,[rdi]` → next phase starts at 0x66d5a7f [V].

## Phase 3 — 0x66d5a7f, 40 instructions [V]
```
0x66d5a7f  mov rax,[rdi]                                 
0x66d5a82  mov rax,[rax+8]                               
0x66d5a86  mov rcx,rdi                                   
0x66d5a89  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5a8f  mov rdi,[rbp+0xA80]                           
0x66d5a96  test rdi,rdi                                  
0x66d5a99  je short 0x66D5AC6                            ; -> loc_66d5ac6
0x66d5a9b  lock dec dword ptr [rdi+8]                    
0x66d5a9f  jne short 0x66D5AC6                           ; -> loc_66d5ac6
0x66d5aa1  mov rax,[rdi]                                 
0x66d5aa4  mov rax,[rax]                                 
0x66d5aa7  mov rcx,rdi                                   
0x66d5aaa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5ab0  lock dec dword ptr [rdi+0xC]                  
0x66d5ab4  jne short 0x66D5AC6                           ; -> loc_66d5ac6
0x66d5ab6  mov rax,[rdi]                                 
0x66d5ab9  mov rax,[rax+8]                               
0x66d5abd  mov rcx,rdi                                   
0x66d5ac0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5ac6  mov rdi,[rbp+0xA58]                           
0x66d5acd  test rdi,rdi                                  
0x66d5ad0  je short 0x66D5AFD                            ; -> loc_66d5afd
0x66d5ad2  lock dec dword ptr [rdi+8]                    
0x66d5ad6  jne short 0x66D5AFD                           ; -> loc_66d5afd
0x66d5ad8  mov rax,[rdi]                                 
0x66d5adb  mov rax,[rax]                                 
0x66d5ade  mov rcx,rdi                                   
0x66d5ae1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5ae7  lock dec dword ptr [rdi+0xC]                  
0x66d5aeb  jne short 0x66D5AFD                           ; -> loc_66d5afd
0x66d5aed  mov rax,[rdi]                                 
0x66d5af0  mov rax,[rax+8]                               
0x66d5af4  mov rcx,rdi                                   
0x66d5af7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5afd  mov rdi,[rbp+0x478]                           
0x66d5b04  test rdi,rdi                                  
0x66d5b07  je short 0x66D5B34                            ; -> loc_66d5b34
0x66d5b09  lock dec dword ptr [rdi+8]                    
0x66d5b0d  jne short 0x66D5B34                           ; -> loc_66d5b34
0x66d5b0f  mov rax,[rdi]                                 
```
// [V] Phase 3 is a chain of four intrusive release sequences (dtor call = rax=[rdi]; rax=[rax] vtable[0]; rcx=rdi; call sub_eea6040 via [0xF99FFA0] [V] role [I]; free call = rax=[rdi]; rax=[rax+8]; rcx=rdi; call sub_eea6040 [I]), each guarded by `test rdi,rdi; je <skip>; lock dec dword ptr [rdi+8]; jne <skip>` (refcount != 0 → skip destroy) [V]. Release #2 free completes phase-2 tail on rdi=[rbp+0xA90]: `mov rax,[rdi]; rax=[rax+8]; mov rcx,rdi; call sub_eea6040 free [I] (0x66d5a7f..0x66d5a89)` [V]. Release #3 on `rdi=[rbp+0xA80]` (0x66d5a8f..0x66d5ac0): dec, dtor call 0x66d5aaa, dec [rdi+0xC], free call 0x66d5ac0 [V]. Release #4 on `rdi=[rbp+0xA58]` (0x66d5ac6..0x66d5af7): dec, dtor call 0x66d5ae1, dec [rdi+0xC], free call 0x66d5af7 [V]. Release #5 begins on `rdi=[rbp+0x478]` (0x66d5afd..): `test rdi,rdi; je short 0x66d5b34; lock dec dword ptr [rdi+8]; jne short 0x66d5b34; else mov rax,[rdi]; mov rax,[rax] vtable[0]` — dtor call continues phase 4 [V]. Fields touched: rdi W chain; [rbp+0xA90] R→rdi, [rdi+8]/[rdi+0xC] R/W [V]; [rbp+0xA80] R→rdi [V]; [rbp+0xA58] R→rdi [V]; [rbp+0x478] R→rdi [V]. Callees: sub_eea6040 via [0xF99FFA0] [V], dtor+free roles [I]. rdis instruction 41 = `0x66d5b12 mov rax,[rax]` → next phase starts at 0x66d5b12 [V].

## Phase 4 — 0x66d5b12, 40 instructions [V]
```
0x66d5b12  mov rax,[rax]                                 
0x66d5b15  mov rcx,rdi                                   
0x66d5b18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5b1e  lock dec dword ptr [rdi+0xC]                  
0x66d5b22  jne short 0x66D5B34                           ; -> loc_66d5b34
0x66d5b24  mov rax,[rdi]                                 
0x66d5b27  mov rax,[rax+8]                               
0x66d5b2b  mov rcx,rdi                                   
0x66d5b2e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5b34  lea rax,[0xF2BEEB0]                           ; [data_f2beeb0]
0x66d5b3b  mov [rbp+0xA50],rax                           
0x66d5b42  movzx eax,byte ptr [rbp+0x7E0]                
0x66d5b49  mov [rbp+0xA58],al                            
0x66d5b4f  movzx eax,byte ptr [rbp+0x7E1]                
0x66d5b56  mov [rbp+0xA59],al                            
0x66d5b5c  mov rax,[rbp+0x7E2]                           
0x66d5b63  mov [rbp+0xA5A],rax                           
0x66d5b6a  mov eax,[rbp+0x7EA]                           
0x66d5b70  mov [rbp+0xA62],eax                           
0x66d5b76  movzx eax,word ptr [rbp+0x7EE]                
0x66d5b7d  mov [rbp+0xA66],ax                            
0x66d5b84  mov byte ptr [rbp+0xAB0],0                    
0x66d5b8b  cmp byte ptr [rbp+0x838],1                    
0x66d5b92  jne 0x66D5C49                                 ; -> loc_66d5c49
0x66d5b98  mov byte ptr [rbp+0xAA8],0xFF                 
0x66d5b9f  movzx eax,byte ptr [rbp+0x830]                
0x66d5ba6  movzx ecx,al                                  
0x66d5ba9  cmp ecx,1                                     
0x66d5bac  jg short 0x66D5BF2                            ; -> loc_66d5bf2
0x66d5bae  test ecx,ecx                                  
0x66d5bb0  jne short 0x66D5C07                           ; -> loc_66d5c07
0x66d5bb2  movdqu xmm0,[rbp+0x7F0]                       
0x66d5bba  movdqu xmm1,[rbp+0x800]                       
0x66d5bc2  movdqu xmm2,[rbp+0x810]                       
0x66d5bca  movups xmm3,[rbp+0x820]                       
0x66d5bd1  movdqu [rbp+0xA68],xmm0                       
0x66d5bd9  movdqu [rbp+0xA78],xmm1                       
0x66d5be1  movdqu [rbp+0xA88],xmm2                       
0x66d5be9  movups [rbp+0xA98],xmm3                       
0x66d5bf0  jmp short 0x66D5C3C                           ; -> loc_66d5c3c
```
// [V] Phase 4 finishes release #5's free on rdi=[rbp+0x478] (from phase 3): `mov rax,[rdi]; rax=[rax+8]; mov rcx,rdi; call sub_eea6040 via [0xF99FFA0] free [I] (0x66d5b12..0x66d5b2e)` [V]. loc_66d5b34: `lea rax,[0xF2BEEB0]` ([data_f2beeb0], annotated rodata/vtable pointer); `[rbp+0xA50]=rax` — object/vtable pointer store [V]; then field copy block: `[rbp+0xA58]=byte [rbp+0x7E0]`; `[rbp+0xA59]=byte [rbp+0x7E1]`; `[rbp+0xA5A]=[rbp+0x7E2]`; `[rbp+0xA62]=[rbp+0x7EA]`; `[rbp+0xA66]=word [rbp+0x7EE]` [V]; `mov byte [rbp+0xAB0],0` [V]; `cmp byte [rbp+0x838],1; jne 0x66d5c49` — if ==1: `mov byte [rbp+0xAA8],0xFF; movzx eax,byte [rbp+0x830]; movzx ecx,al; cmp ecx,1; jg short 0x66d5bf2` (value>1 → 0x66d5bf2, instruction 41) [V]; `test ecx,ecx; jne short 0x66d5c07` (value!=0 → 0x66d5c07) [V]; else (ecx==0): 64-byte struct copy `movdqu xmm0=[rbp+0x7F0]; xmm1=[rbp+0x800]; xmm2=[rbp+0x810]; movups xmm3=[rbp+0x820]; [rbp+0xA68]=xmm0; [rbp+0xA78]=xmm1; [rbp+0xA88]=xmm2; [rbp+0xA98]=xmm3` ([rbp+0x7F0..0x82F]→[rbp+0xA68..0xAB7]) [V]; `jmp short 0x66d5c3c` join [V]. Fields touched: rdi/rax W, [rbp+0x478] R (release tail) [V]; [rbp+0xA50] W, [rbp+0xA58] W, [rbp+0xA59] W, [rbp+0xA5A] W, [rbp+0xA62] W, [rbp+0xA66] W, [rbp+0xAB0] W=0, [rbp+0xAA8] W=0xFF, [rbp+0x838] R cmp, [rbp+0x830] R→ecx, [rbp+0x7F0]/[rbp+0x800]/[rbp+0x810]/[rbp+0x820] R copy src [V]; [rbp+0xA68]/[rbp+0xA78]/[rbp+0xA88]/[rbp+0xA98] W copy dst [V]; [rbp+0x7E0]/[rbp+0x7E1]/[rbp+0x7E2]/[rbp+0x7EA]/[rbp+0x7EE] R [V]. Callee: sub_eea6040 via [0xF99FFA0] [V] free role [I]. rdis instruction 41 = `0x66d5bf2 cmp ecx,2` → next phase starts at 0x66d5bf2 [V].

## Phase 5 — 0x66d5bf2, 40 instructions [V]
```
0x66d5bf2  cmp ecx,2                                     
0x66d5bf5  jne short 0x66D5C42                           ; -> loc_66d5c42
0x66d5bf7  mov rcx,[rbp+0x7F0]                           
0x66d5bfe  mov [rbp+0xA68],rcx                           
0x66d5c05  jmp short 0x66D5C3C                           ; -> loc_66d5c3c
0x66d5c07  mov rcx,[rbp+0x800]                           
0x66d5c0e  mov qword ptr [rbp+0x800],0                   
0x66d5c19  movdqu xmm0,[rbp+0x7F0]                       
0x66d5c21  pxor xmm1,xmm1                                
0x66d5c25  movdqu [rbp+0x7F0],xmm1                       
0x66d5c2d  movdqu [rbp+0xA68],xmm0                       
0x66d5c35  mov [rbp+0xA78],rcx                           
0x66d5c3c  mov [rbp+0xAA8],al                            
0x66d5c42  mov byte ptr [rbp+0xAB0],1                    
0x66d5c49  mov byte ptr [rbp+0xAC4],0                    
0x66d5c50  cmp byte ptr [rbp+0x84C],1                    
0x66d5c57  jne short 0x66D5C80                           ; -> loc_66d5c80
0x66d5c59  movsd xmm0,[rbp+0x840]                        
0x66d5c61  movsd [rbp+0xAB8],xmm0                        
0x66d5c69  movd xmm0,[rbp+0x848]                         
0x66d5c71  movd [rbp+0xAC0],xmm0                         
0x66d5c79  mov byte ptr [rbp+0xAC4],1                    
0x66d5c80  mov eax,[rbp+0x850]                           
0x66d5c86  mov [rbp+0xAC8],eax                           
0x66d5c8c  movzx eax,word ptr [rbp+0x858]                
0x66d5c93  mov [rbp+0xAD0],ax                            
0x66d5c9a  movzx eax,word ptr [rbp+0x860]                
0x66d5ca1  mov [rbp+0xAD8],ax                            
0x66d5ca8  lea rax,[rbp+0xAE0]                           
0x66d5caf  mov byte ptr [rbp+0xB40],0                    
0x66d5cb6  cmp byte ptr [rbp+0x8C8],1                    
0x66d5cbd  jne 0x66D5DD6                                 ; -> loc_66d5dd6
0x66d5cc3  pxor xmm0,xmm0                                
0x66d5cc7  movdqu [rax],xmm0                             
0x66d5ccb  mov rax,[rbp+0x870]                           
0x66d5cd2  test rax,rax                                  
0x66d5cd5  je short 0x66D5CE4                            ; -> loc_66d5ce4
0x66d5cd7  lock inc dword ptr [rax+8]                    
0x66d5cdb  mov rax,[rbp+0x870]                           
0x66d5ce2  jmp short 0x66D5CE6                           ; -> loc_66d5ce6
```
// [V] Phase 5 branches on ecx (from [rbp+0x830]): `cmp ecx,2; jne short 0x66d5c42` — ecx==2 path: `mov rcx,[rbp+0x7F0]; [rbp+0xA68]=rcx; jmp 0x66d5c3c` (qword copy) [V]; ecx==1 path (from phase-4 `jne 0x66d5c07`): pointer steal `mov rcx,[rbp+0x800]; mov qword ptr [rbp+0x800],0` [V]; `movdqu xmm0=[rbp+0x7F0]; pxor xmm1,xmm1; movdqu [rbp+0x7F0],xmm1` (zero [rbp+0x7F0]) [V]; `movdqu [rbp+0xA68]=xmm0; [rbp+0xA78]=rcx` — [rbp+0xA68]=16 bytes from [rbp+0x7F0], [rbp+0xA78]=stolen pointer [V]; ecx==0 path (phase-4 fallthrough) did the 64-byte copy and `jmp 0x66d5c3c` [V]. Join 0x66d5c3c: `mov [rbp+0xAA8],al` — al = low byte of ecx (0/1/2 per path) [V]; `mov byte [rbp+0xAB0],1` unconditional [V]. Then `mov byte [rbp+0xAC4],0; cmp byte [rbp+0x84C],1; jne short 0x66d5c80` — if ==1: `movsd xmm0=[rbp+0x840]; [rbp+0xAB8]=xmm0` (f64 copy) [V]; `movd xmm0=[rbp+0x848]; [rbp+0xAC0]=xmm0` (dword copy) [V]; `mov byte [rbp+0xAC4],1` [V]. Common 0x66d5c80: `[rbp+0xAC8]=[rbp+0x850]`; `[rbp+0xAD0]=word [rbp+0x858]`; `[rbp+0xAD8]=word [rbp+0x860]` [V]; `lea rax,[rbp+0xAE0]; mov byte [rbp+0xB40],0` [V]; `cmp byte [rbp+0x8C8],1; jne 0x66d5dd6` — if ==1: `pxor xmm0,xmm0; movdqu [rax],xmm0` (zero 16 bytes at [rbp+0xAE0]) [V]; null-safe addref on `rax=[rbp+0x870]`: `test rax,rax; je 0x66d5ce4 (xor eax,eax)` [V]; else `lock inc dword ptr [rax+8]; mov rax,[rbp+0x870]` — addref result in rax [V]. Fields touched: ecx R (switch) [V]; [rbp+0xA68] W, [rbp+0xA78] W, [rbp+0x7F0] R then W=0 (ecx==1 path), [rbp+0x800] R then W=0 (pointer steal) [V]; [rbp+0xAA8] W=al, [rbp+0xAB0] W=1 [V]; [rbp+0xAC4] W=0 then cond W=1, [rbp+0x84C] R, [rbp+0x840] R→[rbp+0xAB8] W, [rbp+0x848] R→[rbp+0xAC0] W [V]; [rbp+0x850] R→[rbp+0xAC8] W, [rbp+0x858] R→[rbp+0xAD0] W, [rbp+0x860] R→[rbp+0xAD8] W [V]; rax=&rbp+0xAE0, [rbp+0xAE0] W zero 16 bytes, [rbp+0xB40] W=0, [rbp+0x8C8] R, [rbp+0x870] R (+[rax+8] R/W addref), rax W [V]. Callees: none [V]. rdis instruction 41 = `0x66d5ce4 xor eax,eax` → next phase starts at 0x66d5ce4 [V].

## Phase 6 — 0x66d5ce4, 40 instructions [V]
```
0x66d5ce4  xor eax,eax                                   
0x66d5ce6  mov rcx,[rbp+0x868]                           
0x66d5ced  mov [rbp+0xAE0],rcx                           
0x66d5cf4  mov [rbp+0xAE8],rax                           
0x66d5cfb  movdqu xmm1,[rbp+0x878]                       
0x66d5d03  movdqu [rbp+0xAF0],xmm1                       
0x66d5d0b  movzx eax,word ptr [rbp+0x888]                
0x66d5d12  mov [rbp+0xB00],ax                            
0x66d5d19  movdqu [rbp+0xB08],xmm0                       
0x66d5d21  mov rax,[rbp+0x898]                           
0x66d5d28  test rax,rax                                  
0x66d5d2b  je short 0x66D5D3A                            ; -> loc_66d5d3a
0x66d5d2d  lock inc dword ptr [rax+8]                    
0x66d5d31  mov rax,[rbp+0x898]                           
0x66d5d38  jmp short 0x66D5D3C                           ; -> loc_66d5d3c
0x66d5d3a  xor eax,eax                                   
0x66d5d3c  mov rdx,[rbp+0x890]                           
0x66d5d43  mov rcx,[rbp+0x8A8]                           
0x66d5d4a  mov [rbp+0xB08],rdx                           
0x66d5d51  mov [rbp+0xB10],rax                           
0x66d5d58  movdqu [rbp+0xB18],xmm0                       
0x66d5d60  test rcx,rcx                                  
0x66d5d63  je short 0x66D5D72                            ; -> loc_66d5d72
0x66d5d65  lock inc dword ptr [rcx+8]                    
0x66d5d69  mov rax,[rbp+0x8A8]                           
0x66d5d70  jmp short 0x66D5D74                           ; -> loc_66d5d74
0x66d5d72  xor eax,eax                                   
0x66d5d74  mov rdx,[rbp+0x8A0]                           
0x66d5d7b  mov rcx,[rbp+0x8B8]                           
0x66d5d82  mov [rbp+0xB18],rdx                           
0x66d5d89  mov [rbp+0xB20],rax                           
0x66d5d90  movdqu [rbp+0xB28],xmm0                       
0x66d5d98  test rcx,rcx                                  
0x66d5d9b  je short 0x66D5DAA                            ; -> loc_66d5daa
0x66d5d9d  lock inc dword ptr [rcx+8]                    
0x66d5da1  mov rax,[rbp+0x8B8]                           
0x66d5da8  jmp short 0x66D5DAC                           ; -> loc_66d5dac
0x66d5daa  xor eax,eax                                   
0x66d5dac  mov rcx,[rbp+0x8B0]                           
0x66d5db3  mov rdx,[rbp+0x8C0]                           
```
// [V] Phase 6 completes the phase-5 addref on `rax=[rbp+0x870]` (null path `xor eax,eax` at 0x66d5ce4; join 0x66d5ce6): `mov rcx=[rbp+0x868]; [rbp+0xAE0]=rcx; [rbp+0xAE8]=rax` — entry #1 {ptr [rbp+0x868], addref result or 0} [V]; `movdqu xmm1=[rbp+0x878]; [rbp+0xAF0]=xmm1` (16-byte copy) [V]; `movzx eax,word ptr [rbp+0x888]; [rbp+0xB00]=ax` [V]; `[rbp+0xB08]=xmm0` (zero 16 bytes, placeholder) [V]. Then a repeated null-safe addref+pair-store pattern builds an array at [rbp+0xAE0..]: entry #2 on `rax=[rbp+0x898]`: `test rax,rax; je 0x66d5d3a (xor eax,eax); else lock inc dword ptr [rax+8]; mov rax=[rbp+0x898]` [V]; `mov rdx=[rbp+0x890]; mov rcx=[rbp+0x8A8]; [rbp+0xB08]=rdx` (ptr #2, overwrites the zero) [V]; `[rbp+0xB10]=rax` (addref #2); `[rbp+0xB18]=xmm0` zero [V]. Entry #3 on `rcx=[rbp+0x8A8]`: `test rcx,rcx; je 0x66d5d72; lock inc dword ptr [rcx+8]; mov rax=[rbp+0x8A8]` [V]; `mov rdx=[rbp+0x8A0]; mov rcx=[rbp+0x8B8]; [rbp+0xB18]=rdx` (ptr #3) [V]; `[rbp+0xB20]=rax` (addref #3); `[rbp+0xB28]=xmm0` zero [V]. Entry #4 begins on `rcx=[rbp+0x8B8]`: `test rcx,rcx; je 0x66d5daa; lock inc dword ptr [rcx+8]; mov rax=[rbp+0x8B8]` [V]; then `mov rcx=[rbp+0x8B0]; mov rdx=[rbp+0x8C0]` — instruction 41 `0x66d5dba mov [rbp+0xB28],rcx` (ptr #4) continues phase 7 [V]. Fields touched: rax/rcx/rdx W chain [V]; [rbp+0x868] R→[rbp+0xAE0] W, [rbp+0x878] R→[rbp+0xAF0] W, [rbp+0x888] R→[rbp+0xB00] W, [rbp+0x898] R (+[rax+8] R/W addref), [rbp+0x890] R→[rbp+0xB08] W, [rbp+0x8A8] R→rcx then [rbp+0xB10] W via rax, [rbp+0x8A0] R→[rbp+0xB18] W, [rbp+0x8B8] R→rcx then rax (+[rcx+8] R/W addref) [V]; [rbp+0xAE0]/[rbp+0xAE8]/[rbp+0xAF0]/[rbp+0xB00]/[rbp+0xB08]/[rbp+0xB10]/[rbp+0xB18]/[rbp+0xB20]/[rbp+0xB28] W (pair array) [V]. Callees: none [V]. rdis instruction 41 = `0x66d5dba mov [rbp+0xB28],rcx` → next phase starts at 0x66d5dba [V].

## Phase 7 — 0x66d5dba, 40 instructions [V]
```
0x66d5dba  mov [rbp+0xB28],rcx                           
0x66d5dc1  mov [rbp+0xB30],rax                           
0x66d5dc8  mov [rbp+0xB38],rdx                           
0x66d5dcf  mov byte ptr [rbp+0xB40],1                    
0x66d5dd6  mov byte ptr [rbp+0xBA0],0                    
0x66d5ddd  cmp byte ptr [rbp+0x928],1                    
0x66d5de4  jne short 0x66D5E4E                           ; -> loc_66d5e4e
0x66d5de6  mov eax,[rbp+0x8E0]                           
0x66d5dec  mov [rbp+0xB58],eax                           
0x66d5df2  movups xmm0,[rbp+0x8D0]                       
0x66d5df9  movups [rbp+0xB48],xmm0                       
0x66d5e00  movzx eax,byte ptr [rbp+0x8E4]                
0x66d5e07  mov [rbp+0xB5C],al                            
0x66d5e0d  movups xmm0,[rbp+0x8E8]                       
0x66d5e14  movups [rbp+0xB60],xmm0                       
0x66d5e1b  movups xmm0,[rbp+0x8F8]                       
0x66d5e22  movups [rbp+0xB70],xmm0                       
0x66d5e29  movups xmm0,[rbp+0x908]                       
0x66d5e30  movups [rbp+0xB80],xmm0                       
0x66d5e37  movdqu xmm0,[rbp+0x917]                       
0x66d5e3f  movdqu [rbp+0xB8F],xmm0                       
0x66d5e47  mov byte ptr [rbp+0xBA0],1                    
0x66d5e4e  mov byte ptr [rbp+0xC00],0                    
0x66d5e55  cmp byte ptr [rbp+0x988],1                    
0x66d5e5c  jne 0x66D5F5B                                 ; -> loc_66d5f5b
0x66d5e62  movups xmm0,[rbp+0x930]                       
0x66d5e69  movdqu xmm1,[rbp+0x940]                       
0x66d5e71  mov qword ptr [rbp+0x938],0                   
0x66d5e7c  movups [rbp+0xBA8],xmm0                       
0x66d5e83  xorps xmm0,xmm0                               
0x66d5e86  movups [rbp+0x940],xmm0                       
0x66d5e8d  movdqu [rbp+0xBB8],xmm1                       
0x66d5e95  mov rax,[rbp+0x950]                           
0x66d5e9c  mov [rbp+0xBC8],rax                           
0x66d5ea3  mov byte ptr [rbp+0xBE0],0xFF                 
0x66d5eaa  movzx eax,byte ptr [rbp+0x968]                
0x66d5eb1  cmp rax,3                                     
0x66d5eb5  ja short 0x66D5F36                            ; -> loc_66d5f36
0x66d5eb7  lea rcx,[rbp+0xBD0]                           
0x66d5ebe  lea rdx,[0xF2BFAF0]                           ; [data_f2bfaf0]
```
// [V] Phase 7 completes array entry #4: `[rbp+0xB28]=rcx` ([rbp+0x8B0]) [V]; `[rbp+0xB30]=rax` (addref #4 result of [rbp+0x8B8]) [V]; `[rbp+0xB38]=rdx` ([rbp+0x8C0]) [V]; `mov byte [rbp+0xB40],1` (flag, was 0 at 0x66d5caf) [V]. Then `mov byte [rbp+0xBA0],0; cmp byte [rbp+0x928],1; jne short 0x66d5e4e` — if ==1: ~27-byte copy `[rbp+0x8D0..0x926]` → `[rbp+0xB48..0xBA2]`: `[rbp+0xB58]=[rbp+0x8E0]` (dword) [V]; `movups xmm0=[rbp+0x8D0]; [rbp+0xB48]=xmm0` [V]; `movzx eax,byte [rbp+0x8E4]; [rbp+0xB5C]=al` [V]; `movups xmm0=[rbp+0x8E8]; [rbp+0xB60]=xmm0` [V]; `movups xmm0=[rbp+0x8F8]; [rbp+0xB70]=xmm0` [V]; `movups xmm0=[rbp+0x908]; [rbp+0xB80]=xmm0` [V]; `movdqu xmm0=[rbp+0x917]; [rbp+0xB8F]=xmm0` [V]; `mov byte [rbp+0xBA0],1` [V]. Common 0x66d5e4e: `mov byte [rbp+0xC00],0` [V]; `cmp byte [rbp+0x988],1; jne 0x66d5f5b` — if ==1: `movups xmm0=[rbp+0x930]; movdqu xmm1=[rbp+0x940]; mov qword ptr [rbp+0x938],0` (null field) [V]; `movups [rbp+0xBA8]=xmm0` [V]; `xorps xmm0,xmm0; movups [rbp+0x940]=xmm0` (zero [rbp+0x940]) [V]; `movdqu [rbp+0xBB8]=xmm1` [V]; `mov rax=[rbp+0x950]; [rbp+0xBC8]=rax` [V]; `mov byte [rbp+0xBE0],0xFF` [V]; `movzx eax,byte [rbp+0x968]; cmp rax,3; ja short 0x66d5f36` (unsigned >3 → 0x66d5f36) [V]; `lea rcx,[rbp+0xBD0]; lea rdx,[0xF2BFAF0]` ([data_f2bfaf0] rodata jump table) [V]; `movsxd r8,[rdx+rax*4]` — table dispatch indexed by byte [rbp+0x968] (instruction 41, continues phase 8) [V]. Fields touched: [rbp+0xB28]/[rbp+0xB30]/[rbp+0xB38] W, [rbp+0xB40] W=1, [rbp+0xBA0] W=0 then W=1 [V]; [rbp+0x928] R cmp [V]; [rbp+0x8E0] R→[rbp+0xB58] W, [rbp+0x8D0] R→[rbp+0xB48] W, [rbp+0x8E4] R→[rbp+0xB5C] W, [rbp+0x8E8] R→[rbp+0xB60] W, [rbp+0x8F8] R→[rbp+0xB70] W, [rbp+0x908] R→[rbp+0xB80] W, [rbp+0x917] R→[rbp+0xB8F] W [V]; [rbp+0xC00] W=0, [rbp+0x988] R cmp [V]; [rbp+0x930] R→[rbp+0xBA8] W, [rbp+0x940] R→[rbp+0xBB8] W then W=0, [rbp+0x938] W=0, [rbp+0x950] R→[rbp+0xBC8] W, [rbp+0xBE0] W=0xFF, [rbp+0x968] R→eax jump index [V]; [rbp+0xBD0] W=lea target, rodata [0xF2BFAF0] R [V]. Callees: none [V]. rdis instruction 41 = `0x66d5ec5 movsxd r8,[rdx+rax*4]` → next phase starts at 0x66d5ec5 [V].


## Phase 8 — 0x66d5ec5, 40 instructions [V]
```
0x66d5ec5  movsxd r8,[rdx+rax*4]                         ; R a1+0x0+idx
0x66d5ec9  add r8,rdx                                    
0x66d5ecc  jmp r8                                        
0x66d5ecf  mov rcx,[rbp+0x958]                           
0x66d5ed6  mov [rbp+0xBD0],rcx                           
0x66d5edd  jmp short 0x66D5F30                           ; -> loc_66d5f30
0x66d5edf  lea rdx,[rbp+0x958]                           
0x66d5ee6  movups xmm0,[rdx]                             
0x66d5ee9  movups [rcx],xmm0                             
0x66d5eec  jmp short 0x66D5F30                           ; -> loc_66d5f30
0x66d5eee  movups [rcx],xmm0                             
0x66d5ef1  mov rcx,[rbp+0x960]                           
0x66d5ef8  test rcx,rcx                                  
0x66d5efb  je short 0x66D5F19                            ; -> loc_66d5f19
0x66d5efd  lock inc dword ptr [rcx+8]                    
0x66d5f01  mov rcx,[rbp+0x960]                           
0x66d5f08  jmp short 0x66D5F1B                           ; -> loc_66d5f1b
0x66d5f0a  mov r10w,0x800                                
0x66d5f0f  jmp 0x66D583C                                 ; -> sub_66d583c
0x66d5f14  call 0x78ED0                                  ; -> sub_78ed0
0x66d5f19  xor ecx,ecx                                   
0x66d5f1b  mov rdx,[rbp+0x958]                           
0x66d5f22  mov [rbp+0xBD0],rdx                           
0x66d5f29  mov [rbp+0xBD8],rcx                           
0x66d5f30  mov [rbp+0xBE0],al                            
0x66d5f36  mov rax,[rbp+0x980]                           
0x66d5f3d  mov [rbp+0xBF8],rax                           
0x66d5f44  movdqu xmm0,[rbp+0x970]                       
0x66d5f4c  movdqu [rbp+0xBE8],xmm0                       
0x66d5f54  mov byte ptr [rbp+0xC00],1                    
0x66d5f5b  mov byte ptr [rbp+0xC90],0                    
0x66d5f62  cmp byte ptr [rbp+0xA18],1                    
0x66d5f69  jne short 0x66D5FAD                           ; -> loc_66d5fad
0x66d5f6b  mov rax,[rbp+0x990]                           
0x66d5f72  mov [rbp+0xC08],rax                           
0x66d5f79  lea rcx,[rbp+0xC10]                           
0x66d5f80  lea rdx,[rbp+0x998]                           
0x66d5f87  call 0xE869FF0                                ; -> sub_e869ff0
0x66d5f8c  nop                                           
0x66d5f8d  mov rax,[rbp+0xA10]
```
// [V] Phase 8 is the indexed jump-table dispatch entered from phase 7's `movsxd r8,[rdx+rax*4]` (rdx=&rodata [data_f2bfaf0] jump table, rax=zero-extended byte [rbp+0x968] after `cmp rax,3; ja short 0x66d5f36` at 0x66d5eb1/0x66d5eb5) [V]: `movsxd r8,[rdx+rax*4]` (signed 32-bit table entry → r8) [V]; `add r8,rdx` (table-relative → absolute target) [V]; `jmp r8` (indirect branch through computed address) [V]. Four table entries follow, each ending `jmp short 0x66d5f30` to the common join: entry 0x66d5ecf: `mov rcx,[rbp+0x958]; mov [rbp+0xBD0],rcx` (ptr copy) [V]; entry 0x66d5edf: `lea rdx,[rbp+0x958]; movups xmm0,[rdx]; movups [rcx],xmm0` (16-byte unaligned copy &rbp+0x958→[rcx]) [V]; entry 0x66d5eee: `movups [rcx],xmm0` (store xmm0 to [rcx]) [V]; entry 0x66d5ef1: null-safe addref on `rcx=[rbp+0x960]`: `test rcx,rcx; je short 0x66d5f19 (loc_66d5f19: xor ecx,ecx); else lock inc dword ptr [rcx+8]; mov rcx,[rbp+0x960]` (addref result in rcx) [V] — dead `call 0x78ED0` (sub_78ed0) at 0x66d5f14 sits after the unconditional `jmp 0x66d583c` at 0x66d5f0f and is not reached on this path [V,I]. Join loc_66d5f1b: `mov rdx=[rbp+0x958]; [rbp+0xBD0]=rdx; [rbp+0xBD8]=rcx` [V]; join loc_66d5f30: `mov [rbp+0xBE0],al` (index byte stored) [V]; then init block: `mov rax=[rbp+0x980]; [rbp+0xBF8]=rax` [V]; `movdqu xmm0=[rbp+0x970]; [rbp+0xBE8]=xmm0` (16-byte copy) [V]; `mov byte [rbp+0xC00],1` (flag) [V]; `mov byte [rbp+0xC90],0` [V]; `cmp byte [rbp+0xA18],1; jne short 0x66d5fad` — if ==1: `mov rax=[rbp+0x990]; [rbp+0xC08]=rax` [V]; `lea rcx,[rbp+0xC10]; lea rdx,[rbp+0x998]; call 0xE869FF0(rcx=&rbp+0xC10, rdx=&rbp+0x998)` (sub_e869ff0, known callee from U-BA6) [V]; nop; `mov rax=[rbp+0xA10]; [rbp+0xC88]=rax` — instruction 41 (not quoted), continues phase 9 [V]. Fields touched: r8 W (jump target), rcx/rdx W chain [V]; [rbp+0x958] R→[rbp+0xBD0] W (entries/join) and R as 16-byte src via rdx (entry 2); [rcx] W (entries 2/3 store target) [V]; [rbp+0x960] R (+[rcx+8] R/W addref entry 4), rcx W [V]; [rbp+0xBD0] W (entry 1 + join), [rbp+0xBD8] W=rcx (join) [V]; [rbp+0xBE0] W=al (join loc_66d5f30), [rbp+0x980] R→[rbp+0xBF8] W, [rbp+0x970] R→[rbp+0xBE8] W [V]; [rbp+0xC00] W=1, [rbp+0xC90] W=0, [rbp+0xA18] R cmp [V]; [rbp+0x990] R→[rbp+0xC08] W, [rbp+0xC10] W (call out-ptr), [rbp+0x998] R (call arg), [rbp+0xA10] R→[rbp+0xC88] W [V]. Callees: 0xE869FF0 sub_e869ff0 [V] role/signature [?]; indirect `jmp r8` via rodata jump table [data_f2bfaf0] [V]; dead `call 0x78ED0` sub_78ed0 [V], unreachable [I]. rdis instruction 41 = `0x66d5f94 mov [rbp+0xC88],rax` → next phase starts at 0x66d5f94 [V].


## Phase 9 — 0x66d5f94, 40 instructions [V]
```
0x66d5f94  mov [rbp+0xC88],rax                           
0x66d5f9b  mov qword ptr [rbp+0xA10],0                   
0x66d5fa6  mov byte ptr [rbp+0xC90],1                    
0x66d5fad  lea rdi,[rbp+0xA5A]                           
0x66d5fb4  lea rbx,[rbp+0xA5C]                           
0x66d5fbb  lea r14,[rbp+0xA5E]                           
0x66d5fc2  lea r15,[rbp+0xA60]                           
0x66d5fc9  lea r12,[rbp+0xA62]                           
0x66d5fd0  lea r13,[rbp+0xA64]                           
0x66d5fd7  lea rsi,[rbp+0xA68]                           
0x66d5fde  lea r10,[rbp+0xAD0]                           
0x66d5fe5  lea r11,[rbp+0xAD8]                           
0x66d5fec  mov byte ptr [rbp+0xCC4],0                    
0x66d5ff3  cmp byte ptr [rbp+0xA4C],1                    
0x66d5ffa  jne short 0x66D6048                           ; -> loc_66d6048
0x66d5ffc  mov byte ptr [rbp+0xCB0],0xFF                 
0x66d6003  cmp byte ptr [rbp+0xA38],0xFF                 
0x66d600a  je short 0x66D6031                           ; -> loc_66d6031
0x66d600c  movups xmm0,[rbp+0xA20]                       
0x66d6013  movups [rbp+0xC98],xmm0                       
0x66d601a  movq xmm0,[rbp+0xA30]                         
0x66d6022  movq [rbp+0xCA8],xmm0                         
0x66d602a  mov byte ptr [rbp+0xCB0],0                    
0x66d6031  movdqu xmm0,[rbp+0xA3C]                       
0x66d6039  movdqu [rbp+0xCB4],xmm0                       
0x66d6041  mov byte ptr [rbp+0xCC4],1                    
0x66d6048  mov ecx,0x9D0                                 
0x66d604d  mov rax,[rbp+0xCD8]                           
0x66d6054  add rcx,[rax+0x10]                            
0x66d6058  lea rax,[rbp+0xAB8]                           
0x66d605f  lea rdx,[rbp+0xB48]                           
0x66d6066  lea r9,[rbp+0xBA8]                            
0x66d606d  lea r8,[rbp+0xC08]                            
0x66d6074  mov [rsp+0x80],rdi                            
0x66d607c  mov [rsp+0x78],rbx                            
0x66d6081  mov [rsp+0x70],r14                            
0x66d6086  mov [rsp+0x68],r15                            
0x66d608b  mov [rsp+0x60],r12                            
0x66d6090  mov [rsp+0x58],r13                            
0x66d6095  mov [rsp+0x50],rsi
```
// [V] Phase 9 continues from phase 8: `mov [rbp+0xC88],rax` (rax=[rbp+0xA10] from phase 8's instruction 40) [V]; `mov qword ptr [rbp+0xA10],0` (null it) [V]; `mov byte [rbp+0xC90],1` (flag) [V]; then 9 `lea` instructions gather out-pointers into registers: `rdi=&rbp+0xA5A; rbx=&rbp+0xA5C; r14=&rbp+0xA5E; r15=&rbp+0xA60; r12=&rbp+0xA62; r13=&rbp+0xA64; rsi=&rbp+0xA68; r10=&rbp+0xAD0; r11=&rbp+0xAD8` — pointer args to fields [rbp+0xA5A..0xA68] and [rbp+0xAD0..0xAD8] [V]; `mov byte [rbp+0xCC4],0` (flag) [V]; `cmp byte [rbp+0xA4C],1; jne short 0x66d6048` — if ==1: `mov byte [rbp+0xCB0],0xFF` [V]; `cmp byte [rbp+0xA38],0xFF; je short 0x66d6031` — if [rbp+0xA38] != 0xFF: `movups xmm0=[rbp+0xA20]; [rbp+0xC98]=xmm0` (16-byte copy) [V]; `movq xmm0=[rbp+0xA30]; [rbp+0xCA8]=xmm0` (8-byte copy) [V]; `mov byte [rbp+0xCB0],0` [V]. loc_66d6031: `movdqu xmm0=[rbp+0xA3C]; [rbp+0xCB4]=xmm0` (16-byte copy) [V]; `mov byte [rbp+0xCC4],1` [V]. loc_66d6048 (join): `mov ecx,0x9D0` [V]; `mov rax=[rbp+0xCD8]; add rcx,[rax+0x10]` — rcx = 0x9D0 + qword at [rbp+0xCD8+0x10] (pointer-chained field add) [V]; `lea rax,[rbp+0xAB8]; lea rdx,[rbp+0xB48]; lea r9,[rbp+0xBA8]; lea r8,[rbp+0xC08]` — 4 more out-pointers [V]; spill slots for an upcoming call: `mov [rsp+0x80]=rdi; [rsp+0x78]=rbx; [rsp+0x70]=r14; [rsp+0x68]=r15; [rsp+0x60]=r12; [rsp+0x58]=r13; [rsp+0x50]=rsi; mov [rsp+0x48]=rax` — instruction 41 (not quoted), continues phase 10 [V]. Summary [I]: this phase builds a multi-pointer argument block (13 lea'd out-pointers total) spilled to [rsp+0x48..0x80], with flag-gated field copies ([rbp+0xA20→0xC98], [rbp+0xA30→0xCA8], [rbp+0xA3C→0xCB4]) gated on [rbp+0xA4C]==1 and [rbp+0xA38]!=0xFF, plus a base+field offset computation (ecx=0x9D0 + [rbp+0xCD8+0x10]). Fields touched: [rbp+0xC88] W=rax, [rbp+0xA10] W=0, [rbp+0xC90] W=1 [V]; rdi/rbx/r14/r15/r12/r13/rsi/r10/r11 W (out-pointers) [V]; [rbp+0xCC4] W=0 then W=1 [V]; [rbp+0xA4C] R cmp [V]; [rbp+0xCB0] W=0xFF then W=0, [rbp+0xA38] R cmp 0xFF [V]; [rbp+0xA20] R→[rbp+0xC98] W, [rbp+0xA30] R→[rbp+0xCA8] W [V]; [rbp+0xA3C] R→[rbp+0xCB4] W [V]; ecx W=0x9D0, [rbp+0xCD8] R, [rbp+0xCD8+0x10] R [V]; rax/rdx/r8/r9 W (out-pointers) [V]; [rsp+0x48]/[rsp+0x50]/[rsp+0x58]/[rsp+0x60]/[rsp+0x68]/[rsp+0x70]/[rsp+0x78]/[rsp+0x80] W spill slots [V]. Callees: none in this phase (call target set up by spill slots, continues phase 10) [I]. rdis instruction 41 = `0x66d609a mov [rsp+0x48],rax` → next phase starts at 0x66d609a [V].


## Phase 10 — 0x66d609a, 40 instructions [V]
```
0x66d609a  mov [rsp+0x48],rax                            
0x66d609f  lea rax,[rbp+0xAC8]                           
0x66d60a6  mov [rsp+0x40],rax                            
0x66d60ab  mov [rsp+0x38],r10                            
0x66d60b0  mov [rsp+0x30],r11                            
0x66d60b5  lea rax,[rbp+0xAE0]                           
0x66d60bc  mov [rsp+0x28],rax                            
0x66d60c1  mov [rsp+0x20],rdx                            
0x66d60c6  lea rax,[rbp+0xA58]                           
0x66d60cd  mov [rsp+0x88],rax                            
0x66d60d5  lea rdx,[rbp+0xC98]                           
0x66d60dc  call 0x67D9080                                ; -> sub_67d9080
0x66d60e1  nop                                           
0x66d60e2  lea rax,[0xF2BEEB0]                           ; [data_f2beeb0]
0x66d60e9  mov [rbp+0xA50],rax                           
0x66d60f0  lea rcx,[rbp+0xA58]                           
0x66d60f7  call 0x6774650                                ; -> sub_6774650
0x66d60fc  lea rcx,[rbp+0x7E0]                           
0x66d6103  call 0x6774650                                ; -> sub_6774650
0x66d6108  mov rsi,[rbp+0x468]                           
0x66d610f  test rsi,rsi                                  
0x66d6112  je short 0x66D613F                           ; -> loc_66d613f
0x66d6114  lock dec dword ptr [rsi+8]                    
0x66d6118  jne short 0x66D613F                           ; -> loc_66d613f
0x66d611a  mov rax,[rsi]                                 
0x66d611d  mov rax,[rax]                                 
0x66d6120  mov rcx,rsi                                   
0x66d6123  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d6129  lock dec dword ptr [rsi+0xC]                  
0x66d612d  jne short 0x66D613F                           ; -> loc_66d613f
0x66d612f  mov rax,[rsi]                                 
0x66d6132  mov rax,[rax+8]                               
0x66d6136  mov rcx,rsi                                   
0x66d6139  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d613f  mov rdx,[rbp+0x118]                           
0x66d6146  lea rax,[rbp+0x128]                           
0x66d614d  cmp rax,rdx                                   
0x66d6150  je short 0x66D616C                           ; -> loc_66d616c
0x66d6152  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x66d6159  test rdx,rdx
```
// [V] Phase 10 finishes the call-argument spill area started in phase 9, then calls and releases: `mov [rsp+0x48],rax` (from phase-9 `lea rax,[rbp+0xAB8]`) [V]; `lea rax,[rbp+0xAC8]; [rsp+0x40]=rax` [V]; `[rsp+0x38]=r10; [rsp+0x30]=r11` [V]; `lea rax,[rbp+0xAE0]; [rsp+0x28]=rax` [V]; `[rsp+0x20]=rdx` (rdx=&rbp+0xC98 from phase 9) [V]; `lea rax,[rbp+0xA58]; [rsp+0x88]=rax` [V]; `call 0x67D9080` (sub_67d9080) with stacked args ([rsp+0x20..0x88]) and rdx=&rbp+0xC98; rcx/r8/r9 not re-established in this phase so first-register args are carried/inferrable only [I] — role/signature [?]; `nop` [V]; `lea rax,[0xF2BEEB0] ([data_f2beeb0]); [rbp+0xA50]=rax` — same object/vtable-pointer store as phase 4 [V]; `lea rcx,[rbp+0xA58]; call 0x6774650` (sub_6774650, arg &rbp+0xA58) [V]; `lea rcx,[rbp+0x7E0]; call 0x6774650` (sub_6774650 again, arg &rbp+0x7E0) [V] — same callee, different struct arg [I]; release on `rsi=[rbp+0x468]`: `test rsi,rsi; je short 0x66d613f; lock dec dword ptr [rsi+8]; jne short 0x66d613f; else rax=[rsi]; rax=[rax] vtable[0]; rcx=rsi; call sub_eea6040 dtor [I] (0x66d6123); lock dec dword ptr [rsi+0xC]; jne short 0x66d613f; else rax=[rsi]; rax=[rax+8]; rcx=rsi; call sub_eea6040 free [I] (0x66d6139 — last quoted insn) [V]. loc_66d613f (join): `mov rdx=[rbp+0x118]; lea rax,[rbp+0x128]; cmp rax,rdx; je short 0x66d616c` — end-pointer vs &rbp+0x128 range/bounds check [V]; `mov rcx,[0x1233E1A8] ([data_1233e1a8])` (absolute data pointer load) [V]; `test rdx,rdx; je short 0x66d616c` — instruction 41 (not quoted), continues phase 11 [V]. Fields touched: [rsp+0x20]/[rsp+0x28]/[rsp+0x30]/[rsp+0x38]/[rsp+0x40]/[rsp+0x48]/[rsp+0x88] W spill [V]; [rbp+0xC98] R→rdx [V]; [rbp+0xA50] W [V]; [rbp+0xA58] R, [rbp+0x7E0] R (call args) [V]; [rbp+0x468] R→rsi, [rsi+8]/[rsi+0xC] R/W dec [V]; [rbp+0x118] R→rdx, [rbp+0x128] R (lea) [V]; rax/rcx/rdx W [V]; rodata [0xF2BEEB0] R, [data_1233e1a8] R [V]. Callees: 0x67D9080 sub_67d9080 [V] role/signature [?]; 0x6774650 sub_6774650 [V] ×2 role [?]; sub_eea6040 via [0xF99FFA0] [V] dtor+free [I]. rdis instruction 41 = `0x66d615c je short 0x66D616C` → next phase starts at 0x66d615c [V].


## Phase 11 — 0x66d615c, 40 instructions [V]
```
0x66d615c  je short 0x66D616C                            ; -> loc_66d616c
0x66d615e  mov rax,[rcx]                                 ; R a0+0x0
0x66d6161  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
0x66d6165  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d616b  nop                                           
0x66d616c  movaps xmm6,[rbp+0xDA0]                       
0x66d6173  add rsp,0xE38                                 
0x66d617a  pop rbx                                       
0x66d617b  pop rdi                                       
0x66d617c  pop rsi                                       
0x66d617d  pop r12                                       
0x66d617f  pop r13                                       
0x66d6181  pop r14                                       
0x66d6183  pop r15                                       
0x66d6185  pop rbp                                       
0x66d6186  ret                                           
0x66d6187  mov ecx,0x30                                  
0x66d618c  call 0x9BC830                                 ; -> sub_9bc830
0x66d6191  nop                                           
0x66d6192  jmp 0x66D3C48                                 ; -> sub_66d3c48
0x66d6197  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x66d619e  call 0xE938CB0                                ; -> sub_e938cb0
0x66d61a3  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
0x66d61aa  jne 0x66D0C27                                 ; -> sub_66d0c27
0x66d61b0  lea rcx,[0x129CA568]                          ; [data_129ca568]
0x66d61b7 call 0x567DB00                                ; -> sub_567db00
0x66d61bc  nop                                           
0x66d61bd  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
0x66d61c4  call 0xE935740                                ; -> sub_e935740
0x66d61c9  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x66d61d0  call 0xE938D70                                ; -> sub_e938d70
0x66d61d5  jmp 0x66D0C27                                 ; -> sub_66d0c27
0x66d61da  lea rcx,[0x129F9040]                          ; [data_129f9040]
0x66d61e1  call 0xE938CB0                                ; -> sub_e938cb0
0x66d61e6  cmp dword ptr [0x129F9040],0xFFFFFFFF         ; [data_129f9040]
0x66d61ed  jne 0x66D1D07                                 ; -> sub_66d1d07
0x66d61f3  lea rdx,[0xF5FA1D7]                           ; [data_f5fa1d7] "TintedAlphaTestEnabled"
0x66d61fa  lea r13,[rbp+0xA50]                           
0x66d6201  mov rcx,r13                                   
0x66d6204  call 0x79580                                  ; -> sub_79580
0x66d6209  nop                                           
```
// [V] Phase 11 is the end of bodyActor: entry from phase-10's `test rdx,rdx; je short 0x66d616c` — `je short 0x66d616c` (instruction 1, branch taken) [V]; fallthrough (rdx != 0): `mov rax,[rcx]; mov rax,[rax+0x10]; call qword ptr [0xF99FFA0] (sub_eea6040)` — release on [rcx] chain (dtor candidate via vtable[0]) [I]; `nop` [V]. loc_66d616c: function epilogue — `movaps xmm6,[rbp+0xDA0]` (restore callee-saved xmm6) [V]; `add rsp,0xE38` (deallocate stack frame) [V]; `pop rbx,rdi,rsi,r12,r13,r14,r15,rbp` [V]; `ret` — bodyActor return [V] — END OF FUNCTION 0x66d0a00 DECODE. Post-`ret` linear code (unreachable from function entry, compiler cold/init blocks, seen in linear rdis walk only) [I]: `mov ecx,0x30; call 0x9BC830 (sub_9bc830); nop; jmp 0x66D3C48 (sub_66d3c48)` [V]; `lea rcx,[0x129CA5E0] ([data_129ca5e0]); call 0xE938CB0 (sub_e938cb0); cmp dword ptr [0x129CA5E0],0xFFFFFFFF; jne 0x66D0C27 (sub_66d0c27)` [V]; `lea rcx,[0x129CA568] ([data_129ca568]); call 0x567DB00 (sub_567db00); nop; lea rcx,[0x567DBA0] ([sub_567dba0]); call 0xE935740 (sub_e935740); lea rcx,[0x129CA5E0]; call 0xE938D70 (sub_e938d70); jmp 0x66D0C27` [V]; `lea rcx,[0x129F9040] ([data_129f9040]); call 0xE938CB0; cmp dword ptr [0x129F9040],0xFFFFFFFF; jne 0x66D1D07 (sub_66d1d07)` [V]; `lea rdx,[0xF5FA1D7] ([data_f5fa1d7] "TintedAlphaTestEnabled" rodata string) [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call 0x79580 (sub_79580); nop` — instruction 41 (not quoted), continues phase 12 [V]. Fields touched: rcx/rax W (release chain), [rcx], [rax+0x10] R [V]; xmm6 R ([rbp+0xDA0]) [V]; rsp W (add rsp,0xE38) [V]; rbx/rdi/rsi/r12/r13/r14/r15/rbp R (pops) [V]; ecx W=0x30 [V]; rodata [data_129ca5e0] R (ptr + dword cmp 0xFFFFFFFF), [data_129ca568] R, [data_129f9040] R (ptr + dword cmp), [data_f5fa1d7] R ("TintedAlphaTestEnabled") [V]; [rbp+0xA50] R→r13→rcx [V]. Callees: sub_eea6040 via [0xF99FFA0] [V] dtor [I]; sub_9bc830 [V], sub_e938cb0 [V] ×2, sub_66d3c48 [V], sub_567db00 [V], sub_e935740 [V], sub_e938d70 [V], sub_66d0c27 [V] ×2, sub_66d1d07 [V], sub_79580 [V] — all roles/signatures [?] (post-ret cold code, outside bodyActor proper) [I]. rdis instruction 41 = `0x66d6209 nop` → next phase starts at 0x66d6209 [V].








## Phase 12 - 0x66d6209, 40 instructions [V]
````
0x66d6209  nop
0x66d620a  mov rdx,[rbp+0xA60]
0x66d6211  cmp qword ptr [rbp+0xA68],0x10
0x66d6219  jb short 0x66D6222                            ; -> loc_66d6222
0x66d621b  mov r13,[rbp+0xA50]
0x66d6222  test rdx,rdx
0x66d6225  je 0x66D6CAB                                  ; -> loc_66d6cab
0x66d622b  mov eax,edx
0x66d622d  and eax,3
0x66d6230  cmp rdx,4

0x66d6234  jae 0x66D6D23                                 ; -> loc_66d6d23
0x66d623a  mov rcx,0xCBF29CE484222325
0x66d6244  xor r8d,r8d
0x66d6247  jmp 0x66D6D80                                 ; -> loc_66d6d80
0x66d624c  lea rcx,[0x129F9050]                          ; [data_129f9050]
0x66d6253  call 0xE938CB0                                ; -> sub_e938cb0
0x66d6258  cmp dword ptr [0x129F9050],0xFFFFFFFF         ; [data_129f9050]
0x66d625f  jne 0x66D1E78                                 ; -> sub_66d1e78
0x66d6265  lea rdx,[0xF59991C]                           ; [data_f59991c] "MetalnessUniform"
0x66d626c  lea r13,[rbp+0xA50]

0x66d6273  mov rcx,r13
0x66d6276  call 0x79580                                  ; -> sub_79580
0x66d627b  nop
0x66d627c  mov rdx,[rbp+0xA60]
0x66d6283  cmp qword ptr [rbp+0xA68],0x10
0x66d628b  jb short 0x66D6294                            ; -> loc_66d6294
0x66d628d  mov r13,[rbp+0xA50]
0x66d6294  test rdx,rdx
0x66d6297  je 0x66D6CBA                                  ; -> loc_66d6cba
0x66d629d  mov eax,edx
0x66d629f  and eax,3

0x66d62a2  cmp rdx,4
0x66d62a6  jae 0x66D6DD5                                 ; -> loc_66d6dd5
0x66d62ac  mov rcx,0xCBF29CE484222325
0x66d62b6  xor r8d,r8d
0x66d62b9  jmp 0x66D6E32                                 ; -> loc_66d6e32
0x66d62be  lea rcx,[0x129F9060]                          ; [data_129f9060]
0x66d62c5  call 0xE938CB0                                ; -> sub_e938cb0
0x66d62ca  cmp dword ptr [0x129F9060],0xFFFFFFFF         ; [data_129f9060]
0x66d62d1  jne 0x66D1E9D                                 ; -> sub_66d1e9d
```



// [V] Phase 12 is post-`ret` cold code continuing from the phase-11 nop at 0x66d6209 (not part of bodyActor live flow, seen in linear rdis walk) [I]. First uniform lookup: mov rdx,[rbp+0xA60] (data ptr); cmp qword ptr [rbp+0xA68],0x10 (size vs 16-byte threshold); jb short 0x66d6222 (small path); mov r13,[rbp+0xA50] (ctx) [V]. loc_66d6222: test rdx,rdx; je 0x66d6cab (empty->exit) [V]; mov eax,edx; and eax,3 (len mod 4) [V]; cmp rdx,4; jae 0x66d6d23 (len>=4 -> long hash path) [V]; short path: mov rcx,0xCBF29CE484222325 (FNV-1a 64-bit offset basis) [I]; xor r8d,r8d (hash accumulator=0); jmp 0x66d6d80 (hash loop) [V]. Not-taken cold block 0x66d624c: lea rcx,[0x129F9050] ([data_129f9050]); call sub_e938cb0; cmp dword ptr [0x129f9050],0xFFFFFFFF; jne 0x66d1e78 - global-id init then branch out [V]. Then lea rdx,[0xF59991C] ([data_f59991c] "MetalnessUniform") [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580 (uniform lookup by name, ctx=&rbp+0xA50) [V]; nop [V].

Second lookup repeats: mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6294; mov r13,[rbp+0xA50] [V]; loc_66d6294: test rdx,rdx; je 0x66d6cba [V]; mov eax,edx; and eax,3; cmp rdx,4; jae 0x66d6dd5 [V]; short path: mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0x66d6e32 [V]; then 0x66d62be: lea rcx,[0x129F9060] ([data_129f9060]); call sub_e938cb0; cmp dword ptr [0x129f9060],0xFFFFFFFF; jne sub_66d1e9d [V]. Instruction 41 (next phase start, taken directly from rdis output): 0x66d62d7 lea rdx,[0xF599951] ([data_f599951] "EmissiveUniform") - third uniform name, not quoted here [V]. Fields touched: [rbp+0xA60] R, [rbp+0xA68] R cmp, [rbp+0xA50] R->r13/rcx [V]. Roadata: [data_129f9050] R (ptr + dword cmp 0xFFFFFFFF), [data_f59991c] R ("MetalnessUniform"), [data_129f9060] R (ptr + dword cmp), [data_f599951] R ("EmissiveUniform") [V]. Callees: sub_e938cb0 [V] x2 role [?], sub_79580 [V] role [?], sub_66d1e78/sub_66d1e9d branch targets [V] role [?].

## Phase 13 - 0x66d62d7, 40 instructions [V]
```
0x66d62d7  lea rdx,[0xF599951]                           ; [data_f599951] "EmissiveUniform"
0x66d62de  lea r13,[rbp+0xA50]
0x66d62e5  mov rcx,r13
0x66d62e8  call 0x79580                                  ; -> sub_79580
0x66d62ed  nop
0x66d62ee  mov rdx,[rbp+0xA60]
0x66d62f5  cmp qword ptr [rbp+0xA68],0x10
0x66d62fd  jb short 0x66D6306                            ; -> loc_66d6306
0x66d6306  test rdx,rdx
0x66d6309  je 0x66D6CC9                                  ; -> loc_66d6cc9
0x66d630f  mov eax,edx
0x66d6311  and eax,3
0x66d6314  cmp rdx,4
0x66d6318  jae 0x66D6E80                                 ; -> loc_66d6e80
0x66d631e  mov rcx,0xCBF29CE484222325
0x66d6328  xor r8d,r8d
0x66d632b  jmp 0x66D6EDD                                 ; -> loc_66d6edd
0x66d6330  lea rcx,[0x129F9070]                          ; [data_129f9070]
0x66d6337  call 0xE938CB0                                ; -> sub_e938cb0
0x66d633c  cmp dword ptr [0x129F9070],0xFFFFFFFF         ; [data_129f9070]
0x66d6343  jne 0x66D1EC2                                 ; -> sub_66d1ec2
0x66d6349  lea rdx,[0xF59992D]                           ; [data_f59992d] "RoughnessUniform"
0x66d6350  lea r13,[rbp+0xA50]
0x66d6357  mov rcx,r13
0x66d635a  call 0x79580                                  ; -> sub_79580
0x66d635f  nop
0x66d6360  mov rdx,[rbp+0xA60]
0x66d6367  cmp qword ptr [rbp+0xA68],0x10
0x66d636f  jb short 0x66D6378                            ; -> loc_66d6378
0x66d6378  test rdx,rdx
0x66d637b  je 0x66D6CD8                                  ; -> loc_66d6cd8
0x66d6381  mov eax,edx
0x66d6383  and eax,3
0x66d6386  cmp rdx,4
0x66d638a  jae 0x66D6F2B                                 ; -> loc_66d6f2b
0x66d6390  mov rcx,0xCBF29CE484222325
0x66d639a  xor r8d,r8d
0x66d639d  jmp 0x66D6F88                                 ; -> loc_66d6f88
0x66d63a2  lea rcx,[0x129F9080]                          ; [data_129f9080]
0x66d63a9  call 0xE938CB0                                ; -> sub_e938cb0
```
// [V] Phase 13 is post-`ret` cold code continuing the uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. Third uniform lookup: lea rdx,[0xF599951] ([data_f599951] "EmissiveUniform") [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580 (rcx=&rbp+0xA50 — uniform lookup by name) [V]; nop [V]; mov rdx,[rbp+0xA60] (data ptr); cmp qword ptr [rbp+0xA68],0x10 (size vs 16-byte threshold); jb short 0x66d6306 (small path) [V]; loc_66d6306: test rdx,rdx; je 0x66d6cc9 (empty->exit) [V]; mov eax,edx; and eax,3 (len mod 4) [V]; cmp rdx,4; jae 0x66d6e80 (len>=4 -> long hash path) [V]; short path: mov rcx,0xCBF29CE484222325 (FNV-1a 64-bit offset basis) [I]; xor r8d,r8d (hash accumulator=0); jmp 0x66d6edd (hash loop entry) [V]. Not-taken cold block 0x66d6330: lea rcx,[0x129F9070] ([data_129f9070]); call sub_e938cb0; cmp dword ptr [0x129f9070],0xFFFFFFFF; jne 0x66d1ec2 - global-id init then branch out [V]. Fourth lookup repeats: lea rdx,[0xF59992D] ([data_f59992d] "RoughnessUniform") [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580 [V]; nop; mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6378; mov r13,[rbp+0xA50] [V]; loc_66d6378: test rdx,rdx; je 0x66d6cd8 [V]; mov eax,edx; and eax,3; cmp rdx,4; jae 0x66d6f2b [V]; short path: mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0x66d6f88 [V]; then 0x66d63a2: lea rcx,[0x129F9080] ([data_129f9080]); call sub_e938cb0 [V] — continues phase 14 (instruction 41: cmp dword ptr [0x129f9080],0xFFFFFFFF). Fields touched: [rbp+0xA60] R, [rbp+0xA68] R cmp, [rbp+0xA50] R->r13/rcx [V]. Roadata: [data_129f9070] R (ptr + dword cmp 0xFFFFFFFF), [data_f599951] R ("EmissiveUniform"), [data_f59992d] R ("RoughnessUniform"), [data_129f9080] R (ptr + dword cmp) [V]. Callees: sub_79580 x2 [V] role [?], sub_e938cb0 x2 [V] role [?], sub_66d1ec2 [V] branch target role [?].

## Phase 14 - 0x66d63ae, 40 instructions [V]
```
0x66d63ae  cmp dword ptr [0x129F9080],0xFFFFFFFF         ; [data_129f9080]
0x66d63b5  jne 0x66D1EE7                                 ; -> sub_66d1ee7
0x66d63bb  lea rdx,[0xF599961]                           ; [data_f599961] "SubsurfaceUniform"
0x66d63c2  lea r13,[rbp+0xA50]
0x66d63c9  mov rcx,r13
0x66d63cc  call 0x79580                                  ; -> sub_79580
0x66d63d1  nop
0x66d63d2  mov rdx,[rbp+0xA60]
0x66d63d9  cmp qword ptr [rbp+0xA68],0x10
0x66d63e1  jb short 0x66D63EA                            ; -> loc_66d63ea
0x66d63ea  test rdx,rdx
0x66d63ed  je 0x66D6CE7                                  ; -> loc_66d6ce7
0x66d63f3  mov eax,edx
0x66d63f5  and eax,3
0x66d63f8  cmp rdx,4
0x66d63fc  jae 0x66D6FD6                                 ; -> loc_66d6fd6
0x66d6402  mov rcx,0xCBF29CE484222325
0x66d640c  xor r8d,r8d
0x66d640f  jmp 0x66D7033                                 ; -> loc_66d7033
0x66d6414  lea rcx,[0x129F90B0]                          ; [data_129f90b0]
0x66d641b  call 0xE938CB0                                ; -> sub_e938cb0
0x66d6420  cmp dword ptr [0x129F90B0],0xFFFFFFFF         ; [data_129f90b0]
0x66d6427  jne 0x66D28CA                                 ; -> sub_66d28ca
0x66d642d  lea rdx,[0xF5551FF]                           ; [data_f5551ff] "PBRTextureFlags"
0x66d6434  lea r13,[rbp+0xA50]
0x66d643b  mov rcx,r13
0x66d643e  call 0x79580                                  ; -> sub_79580
0x66d6443  nop
0x66d6444  mov rdx,[rbp+0xA60]
0x66d644b  cmp qword ptr [rbp+0xA68],0x10
0x66d6453  jb short 0x66D645C                            ; -> loc_66d645c
0x66d645c  test rdx,rdx
0x66d645f  je 0x66D6CF6                                  ; -> loc_66d6cf6
0x66d6465  mov eax,edx
0x66d6467  and eax,3
0x66d646a  cmp rdx,4
0x66d646e  jae 0x66D7081                                 ; -> loc_66d7081
0x66d6474  mov rcx,0xCBF29CE484222325
0x66d647e  xor r8d,r8d
0x66d6481  jmp 0x66D70DE                                 ; -> loc_66d70de
```
// [V] Phase 14 is post-`ret` cold code continuing the uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. Guard: cmp dword ptr [0x129f9080],0xFFFFFFFF; jne 0x66d1ee7 (follows phase-13 sub_e938cb0 call) [V]. Fifth uniform lookup: lea rdx,[0xF599961] ([data_f599961] "SubsurfaceUniform") [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580 (rcx=&rbp+0xA50 — uniform lookup by name) [V]; nop [V]; mov rdx,[rbp+0xA60] (data ptr); cmp qword ptr [rbp+0xA68],0x10 (size vs 16-byte threshold); jb short 0x66d63ea (small path) [V]; loc_66d63ea: test rdx,rdx; je 0x66d6ce7 (empty->exit) [V]; mov eax,edx; and eax,3 (len mod 4) [V]; cmp rdx,4; jae 0x66d6fd6 (len>=4 -> long hash path) [V]; short path: mov rcx,0xCBF29CE484222325 (FNV-1a 64-bit offset basis) [I]; xor r8d,r8d (hash accumulator=0); jmp 0x66d7033 (hash loop entry) [V]. Not-taken cold block 0x66d6414: lea rcx,[0x129F90B0] ([data_129f90b0]); call sub_e938cb0; cmp dword ptr [0x129f90b0],0xFFFFFFFF; jne 0x66d28ca - global-id init then branch out [V]. Sixth lookup repeats: lea rdx,[0xF5551FF] ([data_f5551ff] "PBRTextureFlags") [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580 [V]; nop; mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d645c; mov r13,[rbp+0xA50] [V]; loc_66d645c: test rdx,rdx; je 0x66d6cf6 [V]; mov eax,edx; and eax,3; cmp rdx,4; jae 0x66d7081 [V]; short path: mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp 0x66d70de [V] — continues phase 15 (instruction 41: lea rcx,[0x129f90e0]). Fields touched: [rbp+0xA60] R, [rbp+0xA68] R cmp, [rbp+0xA50] R->r13/rcx [V]. Roadata: [data_129f9080] R (dword cmp 0xFFFFFFFF), [data_f599961] R ("SubsurfaceUniform"), [data_129f90b0] R (ptr + dword cmp 0xFFFFFFFF), [data_f5551ff] R ("PBRTextureFlags"), [data_129f90e0] R (ptr) [V]. Callees: sub_79580 x2 [V] role [?], sub_e938cb0 x2 [V] role [?], sub_66d1ee7/sub_66d28ca [V] branch targets role [?].

## Phase 15 - 0x66d6486, 40 instructions [V]
```
0x66d6486  lea rcx,[0x129F90E0]                          ; [data_129f90e0]
0x66d648d  call 0xE938CB0                                ; -> sub_e938cb0
0x66d6492  cmp dword ptr [0x129F90E0],0xFFFFFFFF         ; [data_129f90e0]
0x66d6499  jne 0x66D2B9E                                 ; -> sub_66d2b9e
0x66d649f  lea rdx,[0xF584FB4]                           ; [data_f584fb4] "ActorFPEpsilon"
0x66d64a6  lea r13,[rbp+0xA50]
0x66d64ad  mov rcx,r13
0x66d64b0  call 0x79580                                  ; -> sub_79580
0x66d64b5  nop
0x66d64b6  mov rdx,[rbp+0xA60]
0x66d64bd  cmp qword ptr [rbp+0xA68],0x10
0x66d64c5  jb short 0x66D64CE                            ; -> loc_66d64ce
0x66d64ce  test rdx,rdx
0x66d64d1  je 0x66D6D05                                  ; -> loc_66d6d05
0x66d64d7  mov eax,edx
0x66d64d9  and eax,3
0x66d64dc  cmp rdx,4
0x66d64e0  jae 0x66D712C                                 ; -> loc_66d712c
0x66d64e6  mov rcx,0xCBF29CE484222325
0x66d64f0  xor r8d,r8d
0x66d64f3  jmp 0x66D7189                                 ; -> loc_66d7189
0x66d64f8  lea rcx,[0x129F90F0]                          ; [data_129f90f0]
0x66d64ff  call 0xE938CB0                                ; -> sub_e938cb0
0x66d6504  cmp dword ptr [0x129F90F0],0xFFFFFFFF         ; [data_129f90f0]
0x66d650b  jne 0x66D2DF7                                 ; -> sub_66d2df7
0x66d6511  lea rdx,[0xF5DAB0B]                           ; [data_f5dab0b] "DitheringEnabledToggle"
0x66d6518  lea r13,[rbp+0xA50]
0x66d651f  mov rcx,r13
0x66d6522  call 0x79580                                  ; -> sub_79580
0x66d6527  nop
0x66d6528  mov rdx,[rbp+0xA60]
0x66d652f  cmp qword ptr [rbp+0xA68],0x10
0x66d6537  jb short 0x66D6540                            ; -> loc_66d6540
0x66d6540  test rdx,rdx
0x66d6543 je 0x66D6D14                                  ; -> loc_66d6d14
0x66d6549  mov eax,edx
0x66d654b  and eax,3
0x66d654e  cmp rdx,4
0x66d6552  jae 0x66D71D7                                 ; -> loc_66d71d7
0x66d6558  mov rcx,0xCBF29CE484222325
```
// [V] Phase 15 (final phase of unit scope) is post-`ret` cold code continuing the uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. Guard: lea rcx,[0x129f90e0]; call sub_e938cb0; cmp dword ptr [0x129f90e0],0xFFFFFFFF; jne 0x66d2b9e (follows phase-14 sub_e938cb0 call) [V]. Seventh uniform lookup: lea rdx,[0xF584fb4] ([data_f584fb4] "ActorFPEpsilon") [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580 (rcx=&rbp+0xA50 — uniform lookup by name) [V]; nop [V]; mov rdx,[rbp+0xA60] (data ptr); cmp qword ptr [rbp+0xA68],0x10 (size vs 16-byte threshold); jb short 0x66d64ce (small path) [V]; loc_66d64ce: test rdx,rdx; je 0x66d6d05 (empty->exit) [V]; mov eax,edx; and eax,3 (len mod 4) [V]; cmp rdx,4; jae 0x66d712c (len>=4 -> long hash path) [V]; short path: mov rcx,0xCBF29CE484222325 (FNV-1a 64-bit offset basis) [I]; xor r8d,r8d (hash accumulator=0); jmp 0x66d7189 (hash loop entry) [V]. Not-taken cold block 0x66d64f8: lea rcx,[0x129f90f0] ([data_129f90f0]); call sub_e938cb0; cmp dword ptr [0x129f90f0],0xFFFFFFFF; jne 0x66d2df7 - global-id init then branch out [V]. Eighth lookup begins: lea rdx,[0xF5dab0b] ([data_f5dab0b] "DitheringEnabledToggle") [V]; lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580 [V]; nop; mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6540; test rdx,rdx; je 0x66d6d14; mov eax,edx; and eax,3; cmp rdx,4; jae 0x66d71d7 [V]; then 0x66d6558: mov rcx,0xCBF29CE484222325 [V] — unit scope ends here (15 phases); continuation would be xor r8d,r8d at 0x66d6562 (instruction 41, taken directly from rdis output `dis 0x66d6552 4`) [V]. Fields touched: [rbp+0xA60] R, [rbp+0xA68] R cmp, [rbp+0xA50] R->r13/rcx [V]. Roadata: [data_129f90e0] R (dword cmp 0xFFFFFFFF), [data_f584fb4] R ("ActorFPEpsilon"), [data_129f90f0] R (ptr + dword cmp 0xFFFFFFFF), [data_f5dab0b] R ("DitheringEnabledToggle") [V]. Callees: sub_79580 x2 [V] role [?], sub_e938cb0 x2 [V] role [?], sub_66d2b9e/sub_66d2df7 [V] branch targets role [?].
