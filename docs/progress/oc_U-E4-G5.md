# U-E4-G5 — Unit 5 of builder 0x670b6e0 (ends 0x6713c64)

## NEXT block at TOP — resume at 0x67108da

Unit range covered: 0x670f92b .. 0x67108d4 (800 instructions, phases 1-20)
Resume address after this unit: 0x67108da (instr[800] = `nop`)

Method: linear `rdis dis` listing, 40-instruction steps per phase.
Tags: [V] = saw in disasm (cite RVA), [I] = inferred, [?] = unknown.
Direct jumps written as `jmp <addr>` (not `jmp qword ptr`).

---

### Phase 1 — instructions #1-#40 (0x670f92b .. 0x670f9db)

  670f92b  mov rax,[rcx]                                 ; R a0+0x0
  670f92e  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  670f932  mov dl,0x4A                                   
  670f934  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670f93a  nop                                           
  670f93b  mov [rbp+0x848],al                            
  670f941  mov rdx,[r15+0x638]                           
  670f948  cmp rdx,[r15+0x640]                           
  670f94f  je 0x670FB6D                                  ; -> loc_670fb6d
  670f955  mov eax,[rbp+0x580]                           
  670f95b  mov [rdx],eax                                 
  670f95d  add qword ptr [r15+0x638],4                   
  670f965  jmp 0x670FB80                                 ; -> loc_670fb80
  670f96a  mov rcx,r15                                   
  670f96d  mov r8,r12                                    
  670f970  call 0x5ABA6D0                                ; -> sub_5aba6d0
  670f975  nop                                           
  670f976  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  670f97d  mov rax,[rcx]                                 
  670f980  mov rax,[rax+0x10]                            
  670f984  movzx edx,byte ptr [rbp+0x848]                
  670f98b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670f991  nop                                           
  670f992  mov rcx,r13                                   
  670f995  call 0x67E1660                                ; -> sub_67e1660
  670f99a  lea rcx,[rbp+0x120]                           
  670f9a1  jmp 0x67139A0                                 ; -> sub_67139a0
  670f9a6  mov rcx,r12                                   
  670f9a9  lea r8,[rbp+0x3E0]                            
  670f9b0  call 0x5ABA6D0                                ; -> sub_5aba6d0
  670f9b5  nop                                           
  670f9b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  670f9bd  mov rax,[rcx]                                 
  670f9c0  mov rax,[rax+0x10]                            
  670f9c4  movzx edx,byte ptr [rbp+0x848]                
  670f9cb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670f9d1  nop                                           
  670f9d2  cmp byte ptr [rbp+0x6F8],1                    
  670f9d9  jne short 0x670FA2D                           ; -> loc_670fa2d
  670f9db  mov rcx,[rbp+0x6B8]                           

### Phase 2 — instructions #41-#80 (0x670f9e2 .. 0x670fa83)

  670f9e2  test rcx,rcx                                  
  670f9e5  je short 0x670FA2D                            ; -> loc_670fa2d
  670f9e7  mov rdx,[rbp+0x6C8]                           
  670f9ee  sub rdx,rcx                                   
  670f9f1  cmp rdx,0x1000                                
  670f9f8  jb short 0x670FA16                            ; -> loc_670fa16
  670f9fa  mov rax,[rcx-8]                               
  670f9fe  add rcx,0xFFFFFFFFFFFFFFF8                    
  670fa02  sub rcx,rax                                   
  670fa05  cmp rcx,0x20                                  
  670fa09  jae 0x6713B37                                 ; -> sub_6713b37
  670fa0f  or rdx,0x27                                   
  670fa13  mov rcx,rax                                   
  670fa16  call 0xE935700                                ; -> sub_e935700
  670fa1b  lea rax,[rbp+0x6B8]                           
  670fa22  movups [rax],xmm6                             
  670fa25  mov qword ptr [rax+0x10],0                    
  670fa2d  mov rcx,r13                                   
  670fa30  call 0x6791730                                ; -> sub_6791730
  670fa35  lea rcx,[rbp+0x120]                           
  670fa3c  call 0x67E1660                                ; -> sub_67e1660
  670fa41  test r15,r15                                  
  670fa44  je short 0x670FA73                            ; -> loc_670fa73
  670fa46  lock dec dword ptr [r15+8]                    
  670fa4b  jne short 0x670FA73                           ; -> loc_670fa73
  670fa4d  mov rax,[r15]                                 
  670fa50  mov rax,[rax]                                 
  670fa53  mov rcx,r15                                   
  670fa56  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fa5c  lock dec dword ptr [r15+0xC]                  
  670fa61  jne short 0x670FA73                           ; -> loc_670fa73
  670fa63  mov rax,[r15]                                 
  670fa66  mov rax,[rax+8]                               
  670fa6a  mov rcx,r15                                   
  670fa6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fa73  mov rsi,[rbp+0x318]                           
  670fa7a  test rsi,rsi                                  
  670fa7d  je short 0x670FAAA                            ; -> loc_670faaa
  670fa7f  lock dec dword ptr [rsi+8]                    
  670fa83  jne short 0x670FAAA                           ; -> loc_670faaa

### Phase 3 — instructions #81-#120 (0x670fa85 .. 0x670fb12)

  670fa85  mov rax,[rsi]                                 
  670fa88  mov rax,[rax]                                 
  670fa8b  mov rcx,rsi                                   
  670fa8e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fa94  lock dec dword ptr [rsi+0xC]                  
  670fa98  jne short 0x670FAAA                           ; -> loc_670faaa
  670fa9a  mov rax,[rsi]                                 
  670fa9d  mov rax,[rax+8]                               
  670faa1  mov rcx,rsi                                   
  670faa4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670faaa  mov rsi,[rbp+0x7E8]                           
  670fab1  test rsi,rsi                                  
  670fab4  je short 0x670FAE1                            ; -> loc_670fae1
  670fab6  lock dec dword ptr [rsi+8]                    
  670faba  jne short 0x670FAE1                           ; -> loc_670fae1
  670fabc  mov rax,[rsi]                                 
  670fabf  mov rax,[rax]                                 
  670fac2  mov rcx,rsi                                   
  670fac5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670facb  lock dec dword ptr [rsi+0xC]                  
  670facf  jne short 0x670FAE1                           ; -> loc_670fae1
  670fad1  mov rax,[rsi]                                 
  670fad4  mov rax,[rax+8]                               
  670fad8  mov rcx,rsi                                   
  670fadb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fae1  mov rsi,[rbp+0x7D8]                           
  670fae8  test rsi,rsi                                  
  670faeb  je short 0x670FB18                            ; -> loc_670fb18
  670faed  lock dec dword ptr [rsi+8]                    
  670faf1  jne short 0x670FB18                           ; -> loc_670fb18
  670faf3  mov rax,[rsi]                                 
  670faf6  mov rax,[rax]                                 
  670faf9  mov rcx,rsi                                   
  670fafc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fb02  lock dec dword ptr [rsi+0xC]                  
  670fb06  jne short 0x670FB18                           ; -> loc_670fb18
  670fb08  mov rax,[rsi]                                 
  670fb0b  mov rax,[rax+8]                               
  670fb0f  mov rcx,rsi                                   
  670fb12  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

### Phase 4 — instructions #121-#160 (0x670fb18 .. 0x670fbd5)

  670fb18  mov rsi,[rbp+0x798]                           
  670fb1f  test rsi,rsi                                  
  670fb22  je 0x6710C2C                                  ; -> loc_6710c2c
  670fb28  lock dec dword ptr [rsi+8]                    
  670fb2c  jne 0x6710C2C                                 ; -> loc_6710c2c
  670fb32  mov rax,[rsi]                                 
  670fb35  mov rax,[rax]                                 
  670fb38  mov rcx,rsi                                   
  670fb3b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fb41  lock dec dword ptr [rsi+0xC]                  
  670fb45  jne 0x6710C2C                                 ; -> loc_6710c2c
  670fb4b  mov rax,[rsi]                                 
  670fb4e  mov rax,[rax+8]                               
  670fb52  mov rcx,rsi                                   
  670fb55  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fb5b  cmp byte ptr [rbp+0x80],3                     
  670fb62  je 0x67139AE                                  ; -> sub_67139ae
  670fb68  jmp 0x67139F0                                 ; -> sub_67139f0
  670fb6d  mov rcx,r15                                   
  670fb70  add rcx,0x630                                 
  670fb77  mov r8,r13                                    
  670fb7a  call 0x14DB710                                ; -> sub_14db710
  670fb7f  nop                                           
  670fb80  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  670fb87  mov rax,[rcx]                                 
  670fb8a  mov rax,[rax+0x10]                            
  670fb8e  movzx edx,byte ptr [rbp+0x848]                
  670fb95  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fb9b  nop                                           
  670fb9c  mov rax,0x10000000EC07049                     
  670fba6  mov [rbp+0x3E0],rax                           
  670fbad  mov eax,[r15+0x638]                           
  670fbb4  sub eax,[r15+0x630]                           
  670fbbb  shr eax,2                                     
  670fbbe  dec eax                                       
  670fbc0  mov [rbp+0x424],ax                            
  670fbc7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  670fbce  mov rax,[rcx]                                 
  670fbd1  mov rax,[rax+0x10]                            
  670fbd5  mov dl,0x4A                                   

### Phase 5 — instructions #161-#200 (0x670fbd7 .. 0x670fc80)

  670fbd7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fbdd  nop                                           
  670fbde  mov [rbp+0x848],al                            
  670fbe4  mov rdx,[r15+8]                               
  670fbe8  cmp rdx,[r15+0x10]                            
  670fbec  je short 0x670FC09                            ; -> loc_670fc09
  670fbee  mov r8d,0xC8                                  
  670fbf4  mov rcx,rdx                                   
  670fbf7  mov rdx,r12                                   
  670fbfa  call 0xEEC6EC0                                ; -> sub_eec6ec0
  670fbff  add qword ptr [r15+8],0xC8                    
  670fc07  jmp short 0x670FC15                           ; -> loc_670fc15
  670fc09  mov rcx,r15                                   
  670fc0c  mov r8,r12                                    
  670fc0f  call 0x5ABA6D0                                ; -> sub_5aba6d0
  670fc14  nop                                           
  670fc15  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  670fc1c  mov rax,[rcx]                                 
  670fc1f  mov rax,[rax+0x10]                            
  670fc23  movzx edx,byte ptr [rbp+0x848]                
  670fc2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fc30  nop                                           
  670fc31  mov rcx,r13                                   
  670fc34  call 0x67E40A0                                ; -> sub_67e40a0
  670fc39  jmp 0x6710C20                                 ; -> loc_6710c20
  670fc3e  lea rcx,[rbp+0x2D0]                           
  670fc45  mov rdx,r12                                   
  670fc48  call 0x67E2190                                ; -> sub_67e2190
  670fc4d  nop                                           
  670fc4e  lea rcx,[rbp+0x120]                           
  670fc55  lea rdx,[rbp+0x4C0]                           
  670fc5c  lea r8,[rbp+0x468]                            
  670fc63  mov r9,r12                                    
  670fc66  call 0x678F640                                ; -> sub_678f640
  670fc6b  nop                                           
  670fc6c  lea rcx,[rbp+0x4C0]                           
  670fc73  mov eax,[rcx+0x68]                            
  670fc76  lea rdx,[rbp+0x260]                           
  670fc7d  mov [rdx+0x10],eax                            
  670fc80  movups xmm0,[rcx+0x58]                        

### Phase 6 — instructions #201-#240 (0x670fc84 .. 0x670fd60)

  670fc84  movups [rdx],xmm0                             
  670fc87  movzx eax,byte ptr [rbp+0x52C]                
  670fc8e  mov [rbp+0x274],al                            
  670fc94  movups xmm0,[rbp+0x530]                       
  670fc9b  movups [rbp+0x278],xmm0                       
  670fca2  movups xmm0,[rcx+0x80]                        
  670fca9  movups xmm1,[rcx+0x90]                        
  670fcb0  movups xmm2,[rcx+0x9F]                        
  670fcb7  movups [r14+0xA7],xmm2                        
  670fcbf  movups [r14+0x98],xmm1                        
  670fcc7  movups [r14+0x88],xmm0                        
  670fccf  movzx eax,word ptr [rbp+0x570]                
  670fcd6  mov [rbp+0x2B8],ax                            
  670fcdd  mov rax,[rbp+0x778]                           
  670fce4  mov r8,[rax+0x480]                            
  670fceb  mov rax,[rax+0x488]                           
  670fcf2  mov rdx,rax                                   
  670fcf5  sub rdx,r8                                    
  670fcf8  cmp rdx,0xFFFFFFFFFFFFFFD0                    
  670fcfc  je 0x6713B0F                                  ; -> sub_6713b0f
  670fd02  test r8,r8                                    
  670fd05  setne cl                                      
  670fd08  test rax,rax                                  
  670fd0b  sete r9b                                      
  670fd0f  or r9b,cl                                     
  670fd12  je 0x6713B0F                                  ; -> sub_6713b0f
  670fd18  cmp rax,r8                                    
  670fd1b  je 0x6711829                                  ; -> loc_6711829
  670fd21  mov rax,[rbp+0x788]                           
  670fd28  cmp qword ptr [rax],0                         
  670fd2c  je 0x6711829                                  ; -> loc_6711829
  670fd32  sar rdx,4                                     
  670fd36  mov rax,0xAAAAAAAAAAAAAAAB                    
  670fd40  imul rdx,rax                                  
  670fd44  mov dword ptr [rsp+0x20],0x41800000           
  670fd4c  lea rcx,[rbp+0x810]                           
  670fd53  lea r9,[rbp+0x2F0]                            
  670fd5a  call 0x6769EE0                                ; -> sub_6769ee0
  670fd5f  nop                                           
  670fd60  mov rax,[rbp+0x810]                           

### Phase 7 — instructions #241-#280 (0x670fd67 .. 0x670fe27)

  670fd67  mov rcx,[rbp+0x818]                           
  670fd6e  mov r15,rax                                   
  670fd71  mov [rbp+0x848],rax                           
  670fd78  mov [rbp+0x578],rcx                           
  670fd7f  cmp rax,rcx                                   
  670fd82  je 0x6711796                                  ; -> loc_6711796
  670fd88  mov rax,[rbp+0x788]                           
  670fd8f  mov rcx,[rax]                                 
  670fd92  mov rax,[rcx]                                 
  670fd95  mov rax,[rax+0x48]                            
  670fd99  lea rdx,[rbp+0x310]                           
  670fda0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670fda6  nop                                           
  670fda7  mov r15,[rbp+0x810]                           
  670fdae  mov rsi,[rbp+0x818]                           
  670fdb5  mov rax,rsi                                   
  670fdb8  sub rax,r15                                   
  670fdbb  cmp rax,0xFFFFFFFFFFFFFFE0                    
  670fdbf  je 0x6713B0F                                  ; -> sub_6713b0f
  670fdc5  test r15,r15                                  
  670fdc8  setne al                                      
  670fdcb  test rsi,rsi                                  
  670fdce  sete cl                                       
  670fdd1  or cl,al                                      
  670fdd3  je 0x6713B0F                                  ; -> sub_6713b0f
  670fdd9  test r15,r15                                  
  670fddc  setne al                                      
  670fddf  cmp rsi,r15                                   
  670fde2  sete cl                                       
  670fde5  or cl,al                                      
  670fde7  je 0x6713B0F                                  ; -> sub_6713b0f
  670fded  lea rax,[rbp+0x7E0]                           
  670fdf4  mov [rbp+0x7D0],rax                           
  670fdfb  mov rax,0x100000000                           
  670fe05  mov [rbp+0x7D8],rax                           
  670fe0c  cmp rsi,r15                                   
  670fe0f  je short 0x670FE3C                            ; -> loc_670fe3c
  670fe11  nop [rax+rax]                                 
  670fe20  lea rcx,[rbp+0x7D0]                           
  670fe27  mov rdx,r13                                   

### Phase 8 — instructions #281-#320 (0x670fe2a .. 0x670fefe)

  670fe2a  mov r8,r15                                    
  670fe2d  call 0x676A670                                ; -> sub_676a670
  670fe32  nop                                           
  670fe33  add r15,0x20                                  
  670fe37  cmp r15,rsi                                   
  670fe3a  jne short 0x670FE20                           ; -> loc_670fe20
  670fe3c  lea rax,[rbp+0x7A0]                           
  670fe43  mov [rbp+0x790],rax                           
  670fe4a  mov rax,0x100000000                           
  670fe54  mov [rbp+0x798],rax                           
  670fe5b  lea rsi,[rbp+0x790]                           
  670fe62  mov rcx,rsi                                   
  670fe65  lea rdx,[rbp+0x7D0]                           
  670fe6c  call 0x6764990                                ; -> sub_6764990
  670fe71  nop                                           
  670fe72  mov [rsp+0x20],rsi                            
  670fe77  mov rcx,r13                                   
  670fe7a  lea rdx,[rbp+0x208]                           
  670fe81  lea r8,[rbp+0x1B0]                            
  670fe88  lea r9,[rbp+0x128]                            
  670fe8f  call 0x6792570                                ; -> sub_6792570
  670fe94  nop                                           
  670fe95  lea rcx,[rbp+0x260]                           
  670fe9c  mov eax,[rcx+0x10]                            
  670fe9f  lea rdx,[rbp+0x700]                           
  670fea6  mov [rdx+0x10],eax                            
  670fea9  movups xmm0,[rcx]                             
  670feac  movups [rdx],xmm0                             
  670feaf  movzx eax,byte ptr [rbp+0x274]                
  670feb6  mov [rbp+0x714],al                            
  670febc  movups xmm0,[rbp+0x278]                       
  670fec3  movups [rbp+0x718],xmm0                       
  670feca  movups xmm0,[r14+0x88]                        
  670fed2  movups xmm1,[r14+0x98]                        
  670feda  movups xmm2,[r14+0xA7]                        
  670fee2  lea rax,[rbp+0x584]                           
  670fee9  movups [rax+0x1C3],xmm2                       
  670fef0  movups [rax+0x1B4],xmm1                       
  670fef7  movups [rax+0x1A4],xmm0                       
  670fefe  movzx eax,word ptr [rbp+0x2B8]                

### Phase 9 — instructions #321-#360 (0x670ff05 .. 0x670ffe3)

  670ff05  mov [rbp+0x758],ax                            
  670ff0c  mov rax,[rbp+0x838]                           
  670ff13  mov rcx,[rax+0x10]                            
  670ff17  mov eax,0x9D0                                 
  670ff1c  add rcx,rax                                   
  670ff1f  call 0x5ABA5C0                                ; -> sub_5aba5c0
  670ff24  nop                                           
  670ff25  mov r15,rax                                   
  670ff28  movaps [rbp+0x3C0],xmm6                       
  670ff2f  movaps [rbp+0x3B0],xmm6                       
  670ff36  movaps [rbp+0x3A0],xmm6                       
  670ff3d  movaps [rbp+0x390],xmm6                       
  670ff44  movaps [rbp+0x380],xmm6                       
  670ff4b  movaps [rbp+0x370],xmm6                       
  670ff52  movaps [rbp+0x360],xmm6                       
  670ff59  movaps [rbp+0x350],xmm6                       
  670ff60  movaps [rbp+0x340],xmm6                       
  670ff67  movaps [rbp+0x330],xmm6                       
  670ff6e  movaps [rbp+0x320],xmm6                       
  670ff75  movaps [rbp+0x310],xmm6                       
  670ff7c  mov qword ptr [rbp+0x3D0],0                   
  670ff87  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  670ff8e  mov rax,[rcx]                                 
  670ff91  mov rax,[rax+0x10]                            
  670ff95  mov dl,0x4A                                   
  670ff97  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  670ff9d  nop                                           
  670ff9e  mov [rbp+0x857],al                            
  670ffa4  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
  670ffab  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
  670ffb2  je 0x6710FBF                                  ; -> loc_6710fbf
  670ffb8  movzx eax,word ptr [rbp+0x758]                
  670ffbf  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  670ffc2  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
  670ffca  jmp 0x6710FD3                                 ; -> loc_6710fd3
  670ffcf  lea rcx,[rbp+0x2D0]                           
  670ffd6  lea rdx,[rbp+0x120]                           
  670ffdd  call 0x67E2190                                ; -> sub_67e2190
  670ffe2  nop                                           
  670ffe3  mov rcx,r13                                   

### Phase 10 — instructions #361-#400 (0x670ffe6 .. 0x67100bd)

  670ffe6  mov rdx,r14                                   
  670ffe9  lea r8,[rbp+0x1A8]                            
  670fff0  lea r9,[rbp+0x120]                            
  670fff7  call 0x678F640                                ; -> sub_678f640
  670fffc  nop                                           
  670fffd  mov eax,[r14+0x68]                            
  6710001  lea rcx,[rbp+0x6C0]                           
  6710008  mov [rcx+0x10],eax                            
  671000b  movups xmm0,[r14+0x58]                        
  6710010  movups [rcx],xmm0                             
  6710013  movzx eax,byte ptr [rbp+0x26C]                
  671001a  mov [rbp+0x6D4],al                            
  6710020  movups xmm0,[rbp+0x270]                       
  6710027  movups [rbp+0x6D8],xmm0                       
  671002e  movups xmm0,[r14+0x80]                        
  6710036  movups xmm1,[r14+0x90]                        
  671003e  movups xmm2,[r14+0x9F]                        
  6710046  lea rax,[rbp+0x584]                           
  671004d  movups [rax+0x183],xmm2                       
  6710054  movups [rax+0x174],xmm1                       
  671005b  movups [rax+0x164],xmm0                       
  6710062  movzx eax,word ptr [rbp+0x2B0]                
  6710069  mov [rbp+0x718],ax                            
  6710070  mov rcx,[rbp+0x778]                           
  6710077  mov rax,[rcx+0x480]                           
  671007e  mov rdx,[rcx+0x488]                           
  6710085  mov rcx,rdx                                   
  6710088  sub rcx,rax                                   
  671008b  cmp rcx,0xFFFFFFFFFFFFFFD0                    
  671008f  je 0x6713B0F                                  ; -> sub_6713b0f
  6710095  test rax,rax                                  
  6710098  setne r8b                                     
  671009c  test rdx,rdx                                  
  671009f  sete dl                                       
  67100a2  or dl,r8b                                     
  67100a5  je 0x6713B0F                                  ; -> sub_6713b0f
  67100ab  sar rcx,4                                     
  67100af  mov rdx,0xAAAAAAAAAAAAAAAB                    
  67100b9  imul rcx,rdx                                  
  67100bd  mov [rbp+0xF0],rcx                            

### Phase 11 — instructions #401-#440 (0x67100c4 .. 0x671018a)

  67100c4  mov [rbp+0xF8],rax                            
  67100cb  mov [rsp+0x20],r13                            
  67100d0  mov rcx,[rbp+0x838]                           
  67100d7  lea rdx,[rbp+0xF0]                            
  67100de  mov r8,[rbp+0x788]                            
  67100e5  lea r9,[rbp+0x2F0]                            
  67100ec  call 0x67E2540                                ; -> sub_67e2540
  67100f1  nop                                           
  67100f2  mov rcx,r13                                   
  67100f5  call 0x67E1840                                ; -> sub_67e1840
  67100fa  lea rcx,[rbp+0x120]                           
  6710101  jmp 0x67139A0                                 ; -> sub_67139a0
  6710106  lea rcx,[r15+0x8A0]                           ; R ret@5aba5c0+0x8A0
  671010d  lea r8,[rbp+0x720]                            
  6710114  call 0x1EF6F90                                ; -> sub_1ef6f90
  6710119  nop                                           
  671011a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710121  mov rax,[rcx]                                 
  6710124  mov rax,[rax+0x10]                            
  6710128  movzx edx,byte ptr [rbp+0x848]                
  671012f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710135  nop                                           
  6710136  mov eax,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
  671013d  sub eax,[r15+0x8A0]                           ; R ret@5aba5c0+0x8A0
  6710144  shr eax,1                                     
  6710146  dec eax                                       
  6710148  mov [rbp+0x3F0],ax                            
  671014f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710156  mov rax,[rcx]                                 
  6710159  mov rax,[rax+0x10]                            
  671015d  mov dl,0x4A                                   
  671015f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710165  nop                                           
  6710166  mov [rbp+0x848],al                            
  671016c  mov rdx,[r15+0x758]                           ; R ret@5aba5c0+0x758
  6710173  cmp rdx,[r15+0x760]                           ; R ret@5aba5c0+0x760
  671017a  je 0x67102F2                                  ; -> loc_67102f2
  6710180  lea rcx,[rbp+0x6C8]                           
  6710187  mov eax,[rcx+0x10]                            
  671018a  mov [rdx+0x10],eax                            ; W *(ret@5aba5c0+0x758)+0x10

### Phase 12 — instructions #441-#480 (0x671018d .. 0x6710253)

  671018d  movups xmm0,[rcx]                             
  6710190  movups [rdx],xmm0                             ; W *(ret@5aba5c0+0x758)+0x0
  6710193  movzx eax,byte ptr [rbp+0x6DC]                
  671019a  mov [rdx+0x14],al                             ; W *(ret@5aba5c0+0x758)+0x14
  671019d  movss xmm0,[rbp+0x6E0]                        
  67101a5  movss [rdx+0x18],xmm0                         ; W *(ret@5aba5c0+0x758)+0x18
  67101aa  movss xmm0,[rbp+0x6E4]                        
  67101b2  movss [rdx+0x1C],xmm0                         ; W *(ret@5aba5c0+0x758)+0x1C
  67101b7  movss xmm0,[rbp+0x6E8]                        
  67101bf  movss [rdx+0x20],xmm0                         ; W *(ret@5aba5c0+0x758)+0x20
  67101c4  movss xmm0,[rbp+0x6EC]                        
  67101cc  movss [rdx+0x24],xmm0                         ; W *(ret@5aba5c0+0x758)+0x24
  67101d1  lea rax,[rbp+0x6F0]                           
  67101d8  movups xmm0,[rax]                             
  67101db  movups xmm1,[rax+0x10]                        
  67101df  movups xmm2,[rax+0x1F]                        
  67101e3  movups [rdx+0x28],xmm0                        ; W *(ret@5aba5c0+0x758)+0x28
  67101e7  movups [rdx+0x38],xmm1                        ; W *(ret@5aba5c0+0x758)+0x38
  67101eb  movups [rdx+0x47],xmm2                        ; W *(ret@5aba5c0+0x758)+0x47
  67101ef  add qword ptr [r15+0x758],0x58                ; W ret@5aba5c0+0x758
  67101f7  jmp 0x6710306                                 ; -> loc_6710306
  67101fc  lea rcx,[r15+0x8A0]                           ; R ret@5aba5c0+0x8A0
  6710203  lea r8,[rbp+0x720]                            
  671020a  call 0x1EF6F90                                ; -> sub_1ef6f90
  671020f  nop                                           
  6710210  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710217  mov rax,[rcx]                                 
  671021a  mov rax,[rax+0x10]                            
  671021e  movzx edx,byte ptr [rbp+0x848]                
  6710225  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671022b  nop                                           
  671022c  mov eax,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
  6710233  sub eax,[r15+0x8A0]                           ; R ret@5aba5c0+0x8A0
  671023a  shr eax,1                                     
  671023c  dec eax                                       
  671023e  mov [rbp+0x3F0],ax                            
  6710245  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671024c  mov rax,[rcx]                                 
  671024f  mov rax,[rax+0x10]                            
  6710253  mov dl,0x4A                                   

### Phase 13 — instructions #481-#520 (0x6710255 .. 0x6710321)

  6710255  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671025b  nop                                           
  671025c  mov [rbp+0x848],al                            
  6710262  mov rdx,[r15+0x758]                           ; R ret@5aba5c0+0x758
  6710269  cmp rdx,[r15+0x760]                           ; R ret@5aba5c0+0x760
  6710270  je 0x671038D                                  ; -> loc_671038d
  6710276  lea rcx,[rbp+0x6C8]                           
  671027d  mov eax,[rcx+0x10]                            
  6710280  mov [rdx+0x10],eax                            ; W *(ret@5aba5c0+0x758)+0x10
  6710283  movups xmm0,[rcx]                             
  6710286  movups [rdx],xmm0                             ; W *(ret@5aba5c0+0x758)+0x0
  6710289  movzx eax,byte ptr [rbp+0x6DC]                
  6710290  mov [rdx+0x14],al                             ; W *(ret@5aba5c0+0x758)+0x14
  6710293  movss xmm0,[rbp+0x6E0]                        
  671029b  movss [rdx+0x18],xmm0                         ; W *(ret@5aba5c0+0x758)+0x18
  67102a0  movss xmm0,[rbp+0x6E4]                        
  67102a8  movss [rdx+0x1C],xmm0                         ; W *(ret@5aba5c0+0x758)+0x1C
  67102ad  movss xmm0,[rbp+0x6E8]                        
  67102b5  movss [rdx+0x20],xmm0                         ; W *(ret@5aba5c0+0x758)+0x20
  67102ba  movss xmm0,[rbp+0x6EC]                        
  67102c2  movss [rdx+0x24],xmm0                         ; W *(ret@5aba5c0+0x758)+0x24
  67102c7  lea rax,[rbp+0x6F0]                           
  67102ce  movups xmm0,[rax]                             
  67102d1  movups xmm1,[rax+0x10]                        
  67102d5  movups xmm2,[rax+0x1F]                        
  67102d9  movups [rdx+0x28],xmm0                        ; W *(ret@5aba5c0+0x758)+0x28
  67102dd  movups [rdx+0x38],xmm1                        ; W *(ret@5aba5c0+0x758)+0x38
  67102e1  movups [rdx+0x47],xmm2                        ; W *(ret@5aba5c0+0x758)+0x47
  67102e5  add qword ptr [r15+0x758],0x58                ; W ret@5aba5c0+0x758
  67102ed  jmp 0x67103A1                                 ; -> loc_67103a1
  67102f2  lea rcx,[r15+0x750]                           
  67102f9  lea r8,[rbp+0x6C8]                            
  6710300  call 0x6760A80                                ; -> sub_6760a80
  6710305  nop                                           
  6710306  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671030d  mov rax,[rcx]                                 
  6710310  mov rax,[rax+0x10]                            
  6710314  movzx edx,byte ptr [rbp+0x848]                
  671031b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710321  nop                                           

### Phase 14 — instructions #521-#560 (0x6710322 .. 0x67103f2)

  6710322  mov qword ptr [rbp+0x3E0],0x4001              
  671032d  mov eax,[r15+0x758]                           
  6710334  sub eax,[r15+0x750]                           
  671033b  shr eax,3                                     
  671033e  imul eax,0xFFFF8BA3                           
  6710344  dec eax                                       
  6710346  mov [rbp+0x40C],ax                            
  671034d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710354  mov rax,[rcx]                                 
  6710357  mov rax,[rax+0x10]                            
  671035b  mov dl,0x4A                                   
  671035d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710363  nop                                           
  6710364  mov [rbp+0x848],al                            
  671036a  mov rdx,[r15+0x860]                           
  6710371  cmp rdx,[r15+0x868]                           
  6710378  je 0x6710428                                  ; -> loc_6710428
  671037e  inc rdx                                       
  6710381  mov [r15+0x860],rdx                           
  6710388  jmp 0x6710435                                 ; -> loc_6710435
  671038d  lea rcx,[r15+0x750]                           
  6710394  lea r8,[rbp+0x6C8]                            
  671039b  call 0x6760A80                                ; -> sub_6760a80
  67103a0  nop                                           
  67103a1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67103a8  mov rax,[rcx]                                 
  67103ab  mov rax,[rax+0x10]                            
  67103af  movzx edx,byte ptr [rbp+0x848]                
  67103b6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67103bc  nop                                           
  67103bd  mov qword ptr [rbp+0x3E0],0x4001              
  67103c8  mov eax,[r15+0x758]                           
  67103cf  sub eax,[r15+0x750]                           
  67103d6  shr eax,3                                     
  67103d9  imul eax,0xFFFF8BA3                           
  67103df  dec eax                                       
  67103e1  mov [rbp+0x40C],ax                            
  67103e8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67103ef  mov rax,[rcx]                                 
  67103f2  mov rax,[rax+0x10]                            

### Phase 15 — instructions #561-#600 (0x67103f6 .. 0x67104b5)

  67103f6  mov dl,0x4A                                   
  67103f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67103fe  nop                                           
  67103ff  mov [rbp+0x848],al                            
  6710405  mov rdx,[r15+0x860]                           
  671040c  cmp rdx,[r15+0x868]                           
  6710413  je 0x67104A8                                  ; -> loc_67104a8
  6710419  inc rdx                                       
  671041c  mov [r15+0x860],rdx                           
  6710423  jmp 0x67104B5                                 ; -> loc_67104b5
  6710428  lea rcx,[r15+0x858]                           
  671042f  call 0x6760E60                                ; -> sub_6760e60
  6710434  nop                                           
  6710435  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671043c  mov rax,[rcx]                                 
  671043f  mov rax,[rax+0x10]                            
  6710443  movzx edx,byte ptr [rbp+0x848]                
  671044a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710450  nop                                           
  6710451  mov eax,[r15+0x858]                           
  6710458  not eax                                       
  671045a  add eax,[r15+0x860]                           
  6710461  mov [rbp+0x3F6],ax                            
  6710468  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671046f  mov rax,[rcx]                                 
  6710472  mov rax,[rax+0x10]                            
  6710476  mov dl,0x4A                                   
  6710478  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671047e  nop                                           
  671047f  mov [rbp+0x848],al                            
  6710485  mov rdx,[r15+0x620]                           
  671048c  cmp rdx,[r15+0x628]                           
  6710493  je 0x6710528                                  ; -> loc_6710528
  6710499  inc rdx                                       
  671049c  mov [r15+0x620],rdx                           
  67104a3  jmp 0x6710535                                 ; -> loc_6710535
  67104a8  lea rcx,[r15+0x858]                           
  67104af  call 0x6760E60                                ; -> sub_6760e60
  67104b4  nop                                           
  67104b5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]

### Phase 16 — instructions #601-#640 (0x67104bc .. 0x6710581)

  67104bc  mov rax,[rcx]                                 
  67104bf  mov rax,[rax+0x10]                            
  67104c3  movzx edx,byte ptr [rbp+0x848]                
  67104ca  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67104d0  nop                                           
  67104d1  mov eax,[r15+0x858]                           
  67104d8  not eax                                       
  67104da  add eax,[r15+0x860]                           
  67104e1  mov [rbp+0x3F6],ax                            
  67104e8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67104ef  mov rax,[rcx]                                 
  67104f2  mov rax,[rax+0x10]                            
  67104f6  mov dl,0x4A                                   
  67104f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67104fe  nop                                           
  67104ff  mov [rbp+0x848],al                            
  6710505  mov rdx,[r15+0x620]                           
  671050c  cmp rdx,[r15+0x628]                           
  6710513  je 0x6710687                                  ; -> loc_6710687
  6710519  inc rdx                                       
  671051c  mov [r15+0x620],rdx                           
  6710523  jmp 0x6710694                                 ; -> loc_6710694
  6710528  lea rcx,[r15+0x618]                           
  671052f  call 0x6760E60                                ; -> sub_6760e60
  6710534  nop                                           
  6710535  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671053c  mov rax,[rcx]                                 
  671053f  mov rax,[rax+0x10]                            
  6710543  movzx edx,byte ptr [rbp+0x848]                
  671054a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710550  nop                                           
  6710551  mov qword ptr [rbp+0x3E0],0x8004009           
  671055c  mov eax,[r15+0x618]                           
  6710563  not eax                                       
  6710565  add eax,[r15+0x620]                           
  671056c  mov [rbp+0x426],ax                            
  6710573  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671057a  mov rax,[rcx]                                 
  671057d  mov rax,[rax+0x10]                            
  6710581  mov dl,0x4A                                   

### Phase 17 — instructions #641-#680 (0x6710583 .. 0x671064d)

  6710583  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710589  mov [rbp+0x848],al                            
  671058f  lea rcx,[r15+0x648]                           
  6710596  lea rdx,[rbp+0x670]                           
  671059d  call 0x675FB30                                ; -> sub_675fb30
  67105a2  nop                                           
  67105a3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67105aa  mov rax,[rcx]                                 
  67105ad  mov rax,[rax+0x10]                            
  67105b1  movzx edx,byte ptr [rbp+0x848]                
  67105b8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67105be  nop                                           
  67105bf  mov eax,[r15+0x650]                           
  67105c6  sub eax,[r15+0x648]                           
  67105cd  shr eax,3                                     
  67105d0  imul eax,0xFFFF8E39                           
  67105d6  dec eax                                       
  67105d8  mov [rbp+0x422],ax                            
  67105df  lea rcx,[r15+0x780]                           
  67105e6  lea rdx,[rbp+0x618]                           
  67105ed  call 0x675F3B0                                ; -> sub_675f3b0
  67105f2  nop                                           
  67105f3  mov eax,[r15+0x788]                           
  67105fa  sub eax,[r15+0x780]                           
  6710601  shr eax,3                                     
  6710604  imul eax,0xFFFF8BA3                           
  671060a  dec eax                                       
  671060c  mov [rbp+0x408],ax                            
  6710613  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671061a  mov rax,[rcx]                                 
  671061d  mov rax,[rax+0x10]                            
  6710621  mov dl,0x4A                                   
  6710623  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710629  mov [rbp+0x848],al                            
  671062f  mov rsi,[r15+0x770]                           
  6710636  cmp rsi,[r15+0x778]                           
  671063d  je 0x67107E6                                  ; -> loc_67107e6
  6710643  mov rax,[rbp+0x590]                           
  671064a  mov [rsi],rax                                 
  671064d  lea rcx,[rsi+8]                               

### Phase 18 — instructions #681-#720 (0x6710651 .. 0x6710725)

  6710651  lea rdx,[rbp+0x598]                           
  6710658  call 0xE869FF0                                ; -> sub_e869ff0
  671065d  nop                                           
  671065e  mov rax,[rbp+0x610]                           
  6710665  mov [rsi+0x80],rax                            
  671066c  mov qword ptr [rbp+0x610],0                   
  6710677  add qword ptr [r15+0x770],0x88                
  6710682  jmp 0x67107FD                                 ; -> loc_67107fd
  6710687  lea rcx,[r15+0x618]                           
  671068e  call 0x6760E60                                ; -> sub_6760e60
  6710693  nop                                           
  6710694  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671069b  mov rax,[rcx]                                 
  671069e  mov rax,[rax+0x10]                            
  67106a2  movzx edx,byte ptr [rbp+0x848]                
  67106a9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67106af  nop                                           
  67106b0  mov qword ptr [rbp+0x3E0],0x8004009           
  67106bb  mov eax,[r15+0x618]                           
  67106c2  not eax                                       
  67106c4  add eax,[r15+0x620]                           
  67106cb  mov [rbp+0x426],ax                            
  67106d2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67106d9  mov rax,[rcx]                                 
  67106dc  mov rax,[rax+0x10]                            
  67106e0  mov dl,0x4A                                   
  67106e2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67106e8  mov [rbp+0x848],al                            
  67106ee  lea rcx,[r15+0x648]                           
  67106f5  lea rdx,[rbp+0x670]                           
  67106fc  call 0x675FB30                                ; -> sub_675fb30
  6710701  nop                                           
  6710702  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710709  mov rax,[rcx]                                 
  671070c  mov rax,[rax+0x10]                            
  6710710  movzx edx,byte ptr [rbp+0x848]                
  6710717  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671071d  nop                                           
  671071e  mov eax,[r15+0x650]                           
  6710725  sub eax,[r15+0x648]                           

### Phase 19 — instructions #721-#760 (0x671072c .. 0x67107fd)

  671072c  shr eax,3                                     
  671072f  imul eax,0xFFFF8E39                           
  6710735  dec eax                                       
  6710737  mov [rbp+0x422],ax                            
  671073e  lea rcx,[r15+0x780]                           
  6710745  lea rdx,[rbp+0x618]                           
  671074c  call 0x675F3B0                                ; -> sub_675f3b0
  6710751  nop                                           
  6710752  mov eax,[r15+0x788]                           
  6710759  sub eax,[r15+0x780]                           
  6710760  shr eax,3                                     
  6710763  imul eax,0xFFFF8BA3                           
  6710769  dec eax                                       
  671076b  mov [rbp+0x408],ax                            
  6710772  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710779  mov rax,[rcx]                                 
  671077c  mov rax,[rax+0x10]                            
  6710780  mov dl,0x4A                                   
  6710782  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710788  mov [rbp+0x848],al                            
  671078e  mov rsi,[r15+0x770]                           
  6710795  cmp rsi,[r15+0x778]                           
  671079c  je 0x67108A8                                  ; -> loc_67108a8
  67107a2  mov rax,[rbp+0x590]                           
  67107a9  mov [rsi],rax                                 
  67107ac  lea rcx,[rsi+8]                               
  67107b0  lea rdx,[rbp+0x598]                           
  67107b7  call 0xE869FF0                                ; -> sub_e869ff0
  67107bc  nop                                           
  67107bd  mov rax,[rbp+0x610]                           
  67107c4  mov [rsi+0x80],rax                            
  67107cb  mov qword ptr [rbp+0x610],0                   
  67107d6  add qword ptr [r15+0x770],0x88                
  67107e1  jmp 0x67108BF                                 ; -> loc_67108bf
  67107e6  lea rcx,[r15+0x768]                           
  67107ed  mov rdx,rsi                                   
  67107f0  lea r8,[rbp+0x590]                            
  67107f7  call 0x6760710                                ; -> sub_6760710
  67107fc  nop                                           
  67107fd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]

### Phase 20 — instructions #761-#800 (0x6710804 .. 0x67108d4)

  6710804  mov rax,[rcx]                                 
  6710807  mov rax,[rax+0x10]                            
  671080b  movzx edx,byte ptr [rbp+0x848]                
  6710812  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710818  nop                                           
  6710819  mov qword ptr [rbp+0x3E0],0xA007009           
  6710824  mov eax,[r15+0x770]                           
  671082b  sub eax,[r15+0x768]                           
  6710832  shr eax,3                                     
  6710835  imul eax,0xFFFFF0F1                           
  671083b  dec eax                                       
  671083d  mov [rbp+0x40A],ax                            
  6710844  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671084b  mov rax,[rcx]                                 
  671084e  mov rax,[rax+0x10]                            
  6710852  mov dl,0x4A                                   
  6710854  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671085a  nop                                           
  671085b  mov [rbp+0x848],al                            
  6710861  mov rdx,[r15+0x680]                           
  6710868  cmp rdx,[r15+0x688]                           
  671086f  je 0x671096A                                  ; -> loc_671096a
  6710875  movss xmm0,[rbp+0x584]                        
  671087d  movss [rdx],xmm0                              
  6710881  movss xmm0,[rbp+0x588]                        
  6710889  movss [rdx+4],xmm0                            
  671088e  movss xmm0,[rbp+0x58C]                        
  6710896  movss [rdx+8],xmm0                            
  671089b  add qword ptr [r15+0x680],0xC                 
  67108a3  jmp 0x671097E                                 ; -> loc_671097e
  67108a8  lea rcx,[r15+0x768]                           
  67108af  mov rdx,rsi                                   
  67108b2  lea r8,[rbp+0x590]                            
  67108b9  call 0x6760710                                ; -> sub_6760710
  67108be  nop                                           
  67108bf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67108c6  mov rax,[rcx]                                 
  67108c9  mov rax,[rax+0x10]                            
  67108cd  movzx edx,byte ptr [rbp+0x848]                
  67108d4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

## NEXT: resume at 0x67108da

