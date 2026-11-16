## NEXT
COMPLETE - All 37 gaps filled, instruction-complete reversal of FullscreenEffect visitor body (0x666b5cf..0x667005b)

---

## Gap fill

### Gap 1: 0x666b7cf..0x666b800 (shared_ref cleanup)
```
0x666b7cf  test rsi,rsi                                  
0x666b7d2  je short 0x666B800                            ; -> loc_666b800
0x666b7d4  lock dec dword ptr [rsi+8]                    
0x666b7d8  jne short 0x666B800                           ; -> loc_666b800
0x666b7da  mov rax,[rsi]                                 
0x666b7dd  mov rax,[rax]                                 
0x666b7e0  mov rcx,rsi                                   
0x666b7e3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666b7e9  lock dec dword ptr [rsi+0xC]                  
0x666b7ed  jne short 0x666B800                           ; -> loc_666b800
0x666b7ef  mov rax,[rsi]                                 
0x666b7f2  mov rax,[rax+8]                               
0x666b7f6  mov rcx,rsi                                   
0x666b7f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666b7ff  nop                                           
```

### Gap 2: 0x666b9d1..0x666ba25 (shared_ref cleanup + zero xmm slots + desc+0x08 handling)
```
0x666b9d1  test rsi,rsi                                  
0x666b9d4  je short 0x666BA25                            ; -> loc_666ba25
0x666b9d6  lock dec dword ptr [rsi+8]                    
0x666b9da  jne short 0x666BA25                           ; -> loc_666ba25
0x666b9dc  mov rax,[rsi]                                 
0x666b9df  mov rax,[rax]                                 
0x666b9e2  mov rcx,rsi                                   
0x666b9e5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666b9eb  lock dec dword ptr [rsi+0xC]                  
0x666b9ef  jne short 0x666BA25                           ; -> loc_666ba25
0x666b9f1  mov rax,[rsi]                                 
0x666b9f4  mov rax,[rax+8]                               
0x666b9f8  mov rcx,rsi                                   
0x666b9fb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666ba01  jmp short 0x666BA25                           ; -> loc_666ba25
0x666ba03  nop [rax+rax]                                 
0x666ba10  mov rax,[r15]                                 ; desc+0x00
0x666ba13  mov [rbp+0x300],rax                           
0x666ba1a  mov qword ptr [rbp+0x308],0                   
```

### Gap 3: 0x666bac5..0x666bb00 (shared_ref cleanup + render-state mapper setup)
```
0x666bac5  test rsi,rsi                                  
0x666bac8  je short 0x666BB00                            ; -> loc_666bb00
0x666baca  lock dec dword ptr [rsi+8]                    
0x666bace  jne short 0x666BB00                           ; -> loc_666bb00
0x666bad0  mov rax,[rsi]                                 
0x666bad3  mov rax,[rax]                                 
0x666bad6  mov rcx,rsi                                   
0x666bad9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666badf  lock dec dword ptr [rsi+0xC]                  
0x666bae3  jne short 0x666BB00                           ; -> loc_666bb00
0x666bae5  mov rax,[rsi]                                 
0x666bae8  mov rax,[rax+8]                               
0x666baec  mov rcx,rsi                                   
0x666baef  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666baf5  nop [rax+rax]                                 

loc_666bb00:  ; from 666bac8, 666bace, 666bae3
0x666bb00  mov r8,[rbx+0x3B8]                            ; visitor+0x3B8
```

### Gap 4: 0x666bb6c..0x666bcf9 (pass record construction + mode flag logic + jump table)
```
0x666bb6c  movups [rax],xmm6                             
0x666bb6f  mov rax,[rbp+0x308]                           
0x666bb76  test rax,rax                                  
0x666bb79  je short 0x666BB90                            ; -> loc_666bb90
0x666bb7b  lock inc dword ptr [rax+8]                    
0x666bb7f  mov rax,[rbp+0x308]                           
0x666bb86  jmp short 0x666BB92                           ; -> loc_666bb92
0x666bb88  nop [rax+rax]                                 

loc_666bb90:  ; from 666bb79
0x666bb90  xor eax,eax                                   

loc_666bb92:  ; from 666bb86
0x666bb92  mov rcx,[rbp+0x300]                           
0x666bb99  mov [rbp+0x88],rcx                            
0x666bba0  mov [rbp+0x90],rax                            
0x666bba7  lea rax,[rbp+0x88]                            
0x666bbae  movups [rax+0x10],xmm6                        
0x666bbb2  mov rax,[rbp+0x318]                           
0x666bbb9  test rax,rax                                  
0x666bbbc  je short 0x666BBD0                            ; -> loc_666bbd0
0x666bbbe  lock inc dword ptr [rax+8]                    
0x666bbc2  mov rax,[rbp+0x318]                           
0x666bbc9  jmp short 0x666BBD2                           ; -> loc_666bbd2
0x666bbcb  nop [rax+rax]                                 

loc_666bbd0:  ; from 666bbbc
0x666bbd0  xor eax,eax                                   

loc_666bbd2:  ; from 666bbc9
0x666bbd2  mov rcx,[rbp+0x310]                           
0x666bbd9  mov [rbp+0x98],rcx                            
0x666bbe0  mov [rbp+0xA0],rax                            
0x666bbe7  movaps xmm0,[rbp+0x320]                       
0x666bbee  movups [rbp+0xA8],xmm0                        
0x666bbf5  movaps xmm0,[rbp+0x330]                       
0x666bbfc  movups [rbp+0xB8],xmm0                        
0x666bc03  mov byte ptr [rbp+0x108],0xFF                 
0x666bc0a  movzx eax,byte ptr [rbp+0x620]                ; mode flag
0x666bc11  movzx ecx,al                                  
0x666bc14  cmp ecx,1                                     
0x666bc17  jg short 0x666BC60                            ; -> loc_666bc60
0x666bc19  test ecx,ecx                                  
0x666bc1b  jne short 0x666BC75                           ; -> loc_666bc75
0x666bc1d  movaps xmm0,[rbp+0x5E0]                       
0x666bc24  movaps xmm1,[rbp+0x5F0]                       
0x666bc2b  movaps xmm2,[rbp+0x600]                       
0x666bc32  movaps xmm3,[rbp+0x610]                       
0x666bc39  movups [rbp+0xC8],xmm0                        
0x666bc40  movups [rbp+0xD8],xmm1                        
0x666bc47  movups [rbp+0xE8],xmm2                        
0x666bc4e  movups [rbp+0xF8],xmm3                        
0x666bc55  jmp short 0x666BCA3                           ; -> loc_666bca3
0x666bc57  nop [rax+rax]                                 

loc_666bc60:  ; from 666bc17
0x666bc60  cmp ecx,2                                     
0x666bc63  jne short 0x666BCA9                           ; -> loc_666bca9
0x666bc65  mov rcx,[rbp+0x5E0]                           
0x666bc6c  mov [rbp+0xC8],rcx                            
0x666bc73  jmp short 0x666BCA3                           ; -> loc_666bca3

loc_666bc75:  ; from 666bc1b
0x666bc75  mov rcx,[rbp+0x5F0]                           
0x666bc7c  mov qword ptr [rbp+0x5F0],0                   
0x666bc87  movaps xmm0,[rbp+0x5E0]                       
0x666bc8e  movaps [rbp+0x5E0],xmm6                       
0x666bc95  movups [rbp+0xC8],xmm0                        
0x666bc9c  mov [rbp+0xD8],rcx                            

loc_666bca3:  ; from 666bc55, 666bc73
0x666bca3  mov [rbp+0x108],al                            

loc_666bca9:  ; from 666bc63
0x666bca9  movaps xmm0,[rbp+0x2A0]                       
0x666bcb0  movaps xmm1,[rbp+0x2B0]                       
0x666bcb7  mov qword ptr [rbp+0x2A8],0                   
0x666bcc2  movups [rbp+0x110],xmm0                       
0x666bcc9  movaps [rbp+0x2B0],xmm6                       
0x666bcd0  movups [rbp+0x120],xmm1                       
0x666bcd7  mov rax,[rbp+0x2C0]                           
0x666bcde  mov [rbp+0x130],rax                           
0x666bce5  mov byte ptr [rbp+0x148],0xFF                 
0x666bcec  movzx eax,byte ptr [rbp+0x2D8]                ; jump table index
0x666bcf3  cmp rax,3                                     
0x666bcf7  ja short 0x666BD77                            ; -> loc_666bd77
0x666bcf9  lea rdx,[0xF2BF500]                           ; [data_f2bf500] jump table
```

### Gap 5: 0x666bd94..0x666bf8d (jump table cases 0-3 + record setup + second jump table)
```
0x666bd94  movups [rcx+0xC8],xmm0                        ; W a0+0xC8
0x666bd9b  mov qword ptr [rbp-0x10],0                    
0x666bda3  mov dword ptr [rbp-8],0                       
0x666bdaa  lea rax,[rbp+0x5C3]                           
0x666bdb1  mov qword ptr [rax+6],0                       
0x666bdb9  mov qword ptr [rax],0                         
0x666bdc0  mov rax,[rbp]                                 
0x666bdc4  mov [rbp+0x3F0],rax                           
0x666bdcb  lea rcx,[rbp+0x3F8]                           
0x666bdd2  lea rdx,[rbp+8]                               
0x666bdd6  call 0xE869FF0                                ; -> sub_e869ff0
0x666bddb  nop                                           
0x666bddc  mov rax,[rbp+0x80]                            
0x666bde3  mov [rbp+0x470],rax                           
0x666bdea  mov qword ptr [rbp+0x80],0                    
0x666bdf5  lea rax,[rbp+0x478]                           
0x666bdfc  movups [rax],xmm6                             
0x666bdff  mov rax,[rbp+0x90]                            
0x666be06  test rax,rax                                  
0x666be09  je short 0x666BE20                            ; -> loc_666be20
0x666be0b  lock inc dword ptr [rax+8]                    
0x666be0f  mov rax,[rbp+0x90]                            
0x666be16  jmp short 0x666BE22                           ; -> loc_666be22
0x666be18  nop [rax+rax]                                 

loc_666be20:  ; from 666be09
0x666be20  xor eax,eax                                   

loc_666be22:  ; from 666be16
0x666be22  mov rcx,[rbp+0x88]                            
0x666be29  mov [rbp+0x478],rcx                           
0x666be30  mov [rbp+0x480],rax                           
0x666be37  lea rax,[rbp+0x478]                           
0x666be3e  movups [rax+0x10],xmm6                        
0x666be42  mov rax,[rbp+0xA0]                            
0x666be49  test rax,rax                                  
0x666be4c  je short 0x666BE60                            ; -> loc_666be60
0x666be4e  lock inc dword ptr [rax+8]                    
0x666be52  mov rax,[rbp+0xA0]                            
0x666be59  jmp short 0x666BE62                           ; -> loc_666be62
0x666be5b  nop [rax+rax]                                 

loc_666be60:  ; from 666be4c
0x666be60  xor eax,eax                                   

loc_666be62:  ; from 666be59
0x666be62  mov rcx,[rbp+0x98]                            
0x666be69  mov [rbp+0x488],rcx                           
0x666be70  mov [rbp+0x490],rax                           
0x666be77  movups xmm0,[rbp+0xA8]                        
0x666be7e  movups [rbp+0x498],xmm0                       
0x666be85  movups xmm0,[rbp+0xB8]                        
0x666be8c  movups [rbp+0x4A8],xmm0                       
0x666be93  mov byte ptr [rbp+0x4F8],0xFF                 
0x666be9a  movzx eax,byte ptr [rbp+0x108]                
0x666bea1  movzx ecx,al                                  
0x666bea4  cmp ecx,1                                     
0x666bea7  jg short 0x666BEF0                            ; -> loc_666bef0
0x666bea9  test ecx,ecx                                  
0x666beab  jne short 0x666BF05                           ; -> loc_666bf05
0x666bead  movups xmm0,[rbp+0xC8]                        
0x666beb4  movups xmm1,[rbp+0xD8]                        
0x666bebb  movups xmm2,[rbp+0xE8]                        
0x666bec2  movups xmm3,[rbp+0xF8]                        
0x666bec9  movups [rbp+0x4B8],xmm0                       
0x666bed0  movups [rbp+0x4C8],xmm1                       
0x666bed7  movups [rbp+0x4D8],xmm2                       
0x666bede  movups [rbp+0x4E8],xmm3                       
0x666bee5  jmp short 0x666BF33                           ; -> loc_666bf33
0x666bee7  nop [rax+rax]                                 

loc_666bef0:  ; from 666bea7
0x666bef0  cmp ecx,2                                     
0x666bef3  jne short 0x666BF39                           ; -> loc_666bf39
0x666bef5  mov rcx,[rbp+0xC8]                            
0x666befc  mov [rbp+0x4B8],rcx                           
0x666bf03  jmp short 0x666BF33                           ; -> loc_666bf33

loc_666bf05:  ; from 666beab
0x666bf05  mov rcx,[rbp+0xD8]                            
0x666bf0c  mov qword ptr [rbp+0xD8],0                    
0x666bf17  movups xmm0,[rbp+0xC8]                        
0x666bf1e  movups [rbp+0xC8],xmm6                        
0x666bf25  movups [rbp+0x4B8],xmm0                       
0x666bf2c  mov [rbp+0x4C8],rcx                           

loc_666bf33:  ; from 666bee5, 666bf03
0x666bf33  mov [rbp+0x4F8],al                            

loc_666bf39:  ; from 666bef3
0x666bf39  movups xmm0,[rbp+0x110]                       
0x666bf40  movups xmm1,[rbp+0x120]                       
0x666bf47  mov qword ptr [rbp+0x118],0                   
0x666bf52  movups [rbp+0x500],xmm0                       
0x666bf59  movups [rbp+0x120],xmm6                       
0x666bf60  movups [rbp+0x510],xmm1                       
0x666bf67  mov rax,[rbp+0x130]                           
0x666bf6e  mov [rbp+0x520],rax                           
0x666bf75  mov byte ptr [rbp+0x538],0xFF                 
0x666bf7c  movzx eax,byte ptr [rbp+0x148]                
0x666bf83  cmp rax,3                                     
0x666bf87  ja 0x666C00F                                  ; -> loc_666c00f
0x666bf8d  lea rdx,[0xF2BF510]                           ; [data_f2bf510] jump table 2
```

### Gap 6: 0x666c0f2..0x666c13f (zero xmm stack area)
```
0x666c0f2  movaps [rbp+0x270],xmm6                       
0x666c0f9  movaps [rbp+0x260],xmm6                       
0x666c100  movaps [rbp+0x250],xmm6                       
0x666c107  movaps [rbp+0x240],xmm6                       
0x666c10e  movaps [rbp+0x230],xmm6                       
0x666c115  movaps [rbp+0x220],xmm6                       
0x666c11c  movaps [rbp+0x210],xmm6                       
0x666c123  movaps [rbp+0x200],xmm6                       
0x666c12a  movaps [rbp+0x1F0],xmm6                       
0x666c131  movaps [rbp+0x1E0],xmm6                       
0x666c138  movaps [rbp+0x1D0],xmm6                       
0x666c13f  mov qword ptr [rbp+0x290],0                   
```

### Gap 7: 0x666c8a8..0x666c90e (shared_ref cleanup + thread-local checks)
```
0x666c8a8  je 0x666CF35                                  ; -> loc_666cf35
0x666c8ae  lock dec dword ptr [rsi+8]                    
0x666c8b2  jne 0x666CF35                                 ; -> loc_666cf35
0x666c8b8  mov rax,[rsi]                                 
0x666c8bb  mov rax,[rax]                                 
0x666c8be  mov rcx,rsi                                   
0x666c8c1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666c8c7  lock dec dword ptr [rsi+0xC]                  
0x666c8cb  jne 0x666CF35                                 ; -> loc_666cf35
0x666c8d1  mov rax,[rsi]                                 
0x666c8d4  mov rax,[rax+8]                               
0x666c8d8  mov rcx,rsi                                   
0x666c8db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666c8e1  jmp 0x666CF35                                 ; -> loc_666cf35
0x666c8e6  mov rax,[rax]                                 
0x666c8e9  mov rax,[rax+0x18]                            
0x666c8ed  mov rdi,[rax]                                 
0x666c8f0  test rdi,rdi                                  
0x666c8f3  je 0x666EEBE                                  ; -> sub_666eebe
0x666c8f9  mov eax,[0x129FA150]                          ; [data_129fa150]
0x666c8ff  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x666c905  mov rdx,gs:[0x58]                             
0x666c90e  mov rcx,[rdx+rcx*8]                           
```

### Gap 8: 0x666c99f..0x666ca0c (shared_ref handling + alloc)
```
0x666c99f  lock inc dword ptr [rcx+8]                    
0x666c9a3  mov rsi,[rbp+0x3F8]                           
0x666c9aa  movups xmm0,[rax]                             
0x666c9ad  movaps [rbp+0x3F0],xmm0                       
0x666c9b4  test rsi,rsi                                  
0x666c9b7  je 0x666D269                                  ; -> loc_666d269
0x666c9bd  lock dec dword ptr [rsi+8]                    
0x666c9c1  jne 0x666D269                                 ; -> loc_666d269
0x666c9c7  mov rax,[rsi]                                 
0x666c9ca  mov rax,[rax]                                 
0x666c9cd  mov rcx,rsi                                   
0x666c9d0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666c9d6  lock dec dword ptr [rsi+0xC]                  
0x666c9da  jne 0x666D269                                 ; -> loc_666d269
0x666c9e0  mov rax,[rsi]                                 
0x666c9e3  mov rax,[rax+8]                               
0x666c9e7  mov rcx,rsi                                   
0x666c9ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666c9f0  jmp 0x666D269                                 ; -> loc_666d269
0x666c9f5  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666c9fc  mov rax,[rcx]                                 
0x666c9ff  mov rax,[rax+8]                               
0x666ca03  mov rdx,r15                                   
0x666ca06  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666ca0c  nop                                           
```

### Gap 9: 0x666cf6b..0x666cfa2 (shared_ref cleanup + call 0xBBD7F70 + thread-local check + lookup)
```
0x666cf6b  mov rsi,[rbp+0x3F8]                           
0x666cf72  test rsi,rsi                                  
0x666cf75  je short 0x666CFA2                            ; -> loc_666cfa2
0x666cf77  lock dec dword ptr [rsi+8]                    
0x666cf7b  jne short 0x666CFA2                           ; -> loc_666cfa2
0x666cf7d  mov rax,[rsi]                                 
0x666cf80  mov rax,[rax]                                 
0x666cf83  mov rcx,rsi                                   
0x666cf86  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666cf8c  lock dec dword ptr [rsi+0xC]                  
0x666cf90  jne short 0x666CFA2                           ; -> loc_666cfa2
0x666cf92  mov rax,[rsi]                                 
0x666cf95  mov rax,[rax+8]                               
0x666cf99  mov rcx,rsi                                   
0x666cf9c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_666cfa2:  ; from 666cf75, 666cf7b, 666cf90
0x666cfa2  mov r9,[r15]                                  
0x666cfa5  lea rcx,[rbp+0x340]                           
0x666cfac  lea r8,[rbp+0x1D0]                            
0x666cfb3  mov rdx,r12                                   
0x666cfb6  call 0xBBD7F70                                ; -> sub_bbd7f70
0x666cfbb  nop                                           
0x666cfbc  mov eax,[0x129FA128]                          ; [data_129fa128]
0x666cfc2  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x666cfc8  mov rdx,gs:[0x58]                             
0x666cfd1  mov rcx,[rdx+rcx*8]                           
0x666cfd5  cmp eax,[rcx+4]                               
0x666cfdb  jg 0x6670FE9                                  ; -> sub_6670fe9
0x666cfe1  movss xmm0,[r15+8]                            
0x666cfe7  mov qword ptr [rbp+0x3F0],0                   
0x666cff2  mov dword ptr [rbp+0x3F8],0                   
0x666cffc  movss [rbp+0x3FC],xmm0                        
0x666d004  mov qword ptr [rbp],1                         
0x666d00c  mov [rbp+8],rdi                               
0x666d010  mov rax,[rbp+0x208]                           
0x666d017  movzx r8d,word ptr [rbp+0x212]                
0x666d01f  mov edx,r8d                                   
0x666d022  shl edx,4                                     
0x666d025  mov rcx,rax                                   
0x666d028  test r8d,r8d                                  
0x666d02b  je short 0x666D055                            ; -> loc_666d055
0x666d02d  mov r8,[0x129FA120]                           ; [data_129fa120]
0x666d034  mov r9,rdx                                    
0x666d037  mov rcx,rax                                   
0x666d03a  nop [rax+rax]                                 

loc_666d040:  ; from 666d051
0x666d040  mov r10,[rcx]                                 
0x666d043  cmp [r10+0x28],r8                             
0x666d047  je short 0x666D055                            ; -> loc_666d055
0x666d049  add rcx,0x10                                  
0x666d04d  add r9,0xFFFFFFFFFFFFFFF0                     
0x666d051  jne short 0x666D040                           ; -> loc_666d040
0x666d053  jmp short 0x666D083                           ; -> loc_666d083

loc_666d055:  ; from 666d02b, 666d047
0x666d055  add rdx,rax                                   
0x666d058  cmp rcx,rdx                                   
0x666d05b  jae short 0x666D083                           ; -> loc_666d083
0x666d05d  sub ecx,eax                                   
0x666d05f  shr ecx,4                                     
0x666d062  mov [rbp+0x2A0],cx                            
0x666d069  mov byte ptr [rbp+0x2A2],1                    
0x666d070  lea rdx,[rbp+0x2A0]                           
0x666d077  mov r8,rbp                                    
0x666d07a  mov rcx,rbx                                   
0x666d07d  call 0x5679DB0                                ; -> sub_5679db0
0x666d082  nop                                           

loc_666d083:  ; from 666d053, 666d05b
0x666d083  cmp byte ptr [rbp+0x398],1                    
0x666d08a  jne 0x666FB78                                 ; -> sub_666fb78
0x666d090  movups xmm0,[r15+0xC]                         
0x666d095  movaps [rbp+0x2A0],xmm0                       
0x666d09c  movups xmm1,[r15+0x1C]                        
0x666d0a1  movaps [rbp+0x2B0],xmm1                       
0x666d0a8  movups xmm2,[r15+0x2C]                        
0x666d0ad  movaps [rbp+0x2C0],xmm2                       
0x666d0b4  movups xmm3,[r15+0x3C]                        
0x666d0b9  movaps [rbp+0x2D0],xmm3                       
0x666d0c0  mov byte ptr [rbp+0x2E0],0                    
0x666d0c7  movzx eax,word ptr [r15+0x4C]                 
0x666d0cc  movups [rbp+0x3F8],xmm0                       
0x666d0d3  movups [rbp+0x408],xmm1                       
0x666d0da  movups [rbp+0x418],xmm2                       
0x666d0e1  movups [rbp+0x428],xmm3                       
0x666d0e8  mov byte ptr [rbp+0x438],0                    
```

### Gap 10: 0x666d299..0x666d2d0 (shared_ref cleanup + desc+0x68 restore)
```
0x666d299  mov rsi,[rbp+0x3F8]                           
0x666d2a0  test rsi,rsi                                  
0x666d2a3  je short 0x666D2D0                            ; -> loc_666d2d0
0x666d2a5  lock dec dword ptr [rsi+8]                    
0x666d2a9  jne short 0x666D2D0                           ; -> loc_666d2d0
0x666d2ab  mov rax,[rsi]                                 
0x666d2ae  mov rax,[rax]                                 
0x666d2b1  mov rcx,rsi                                   
0x666d2b4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666d2ba  lock dec dword ptr [rsi+0xC]                  
0x666d2be  jne short 0x666D2D0                           ; -> loc_666d2d0
0x666d2c0  mov rax,[rsi]                                 
0x666d2c3  mov rax,[rax+8]                               
0x666d2c7  mov rcx,rsi                                   
0x666d2ca  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_666d2d0:  ; from 666d2a3, 666d2a9, 666d2be
0x666d2d0  mov r11,[rbp+0x668]                           ; SHARED SPILL SLOT = description
0x666d2d7  lea rax,[r11+0x68]                            ; desc+0x68
0x666d2db  mov [rbp+0x670],rax                           
```

### Gap 11: 0x666d5a2..0x666d5d2 (shared_ref cleanup)

### Gap 11: 0x666d5a2..0x666d5d2 (shared_ref cleanup + render-state mapper setup)
```
0x666d5a2  test rsi,rsi                                  
0x666d5a5  je short 0x666D5D2                            ; -> loc_666d5d2
0x666d5a7  lock dec dword ptr [rsi+8]                    
0x666d5ab  jne short 0x666D5D2                           ; -> loc_666d5d2
0x666d5ad  mov rax,[rsi]                                 
0x666d5b0  mov rax,[rax]                                 
0x666d5b3  mov rcx,rsi                                   
0x666d5b6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666d5bc  lock dec dword ptr [rsi+0xC]                  
0x666d5c0  jne short 0x666D5D2                           ; -> loc_666d5d2
0x666d5c2  mov rax,[rsi]                                 
0x666d5c5  mov rax,[rax+8]                               
0x666d5c9  mov rcx,rsi                                   
0x666d5cc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_666d5d2:  ; from 666d5a5, 666d5ab, 666d5c0
0x666d5d2  mov rax,[rbp+0x648]                           
0x666d5d9  mov r8,[rax+0x3B8]                            
0x666d5e0  mov rdx,[r12]                                 
0x666d5e4  mov [rsp+0x20],r14d                           
0x666d5e9  mov dword ptr [rsp+0x30],0                    
0x666d5f1  mov dword ptr [rsp+0x28],0                    
0x666d5f9  lea rcx,[rbp+0x1D0]                           
0x666d600  lea r9,[rbp+0x630]                            
0x666d607  call 0x66A0F60                                ; -> sub_66a0f60
```

### Gap 12: 0x666de6b..0x666dea5 (buffer grow check + free)
```
0x666de6b  jb short 0x666DEA5                            ; -> loc_666dea5
0x666de6d  mov rcx,[rbp+0x3F0]                           
0x666de74  lea rdx,[rax+1]                               
0x666de78  cmp rdx,0x1000                                
0x666de7f  jb short 0x666DEA0                            ; -> loc_666dea0
0x666de81  mov r8,[rcx-8]                                
0x666de85  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666de89  sub rcx,r8                                    
0x666de8c  cmp rcx,0x20                                  
0x666de90  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666de96  add rax,0x28                                  
0x666de9a  mov rdx,rax                                   
0x666de9d  mov rcx,r8                                    

loc_666dea0:  ; from 666de7f
0x666dea0  call 0xE935700                                ; -> sub_e935700

loc_666dea5:  ; from 666de6b
0x666dea5  lea rax,[rbp+0x5E8]                           
0x666deac  cmp rsi,rdi                                   
0x666deaf  je 0x666DFDF                                  ; -> loc_666dfdf
0x666deb5  mov [rbp+0x3F0],rax                           
0x666debc  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666dec3  mov rax,[rcx]                                 
0x666dec6  mov rax,[rax+8]                               
0x666deca  mov r8,[0xF99FFA0]                            ; [data_f99ffa0] = sub_eea6040
0x666ded1  mov qword ptr [rbp+0x1C8],0                   
0x666dedc  mov edx,0x50                                  
0x666dee1  call r8                                       
```

### Gap 13: 0x666dfe6..0x666e0ad (alloc + string "On_DiscardValueBased" + FNV hash setup)
```
0x666dfe6  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666dfed  mov rax,[rcx]                                 
0x666dff0  mov rax,[rax+8]                               
0x666dff4  mov r8,[0xF99FFA0]                            ; [data_f99ffa0] = sub_eea6040
0x666dffb  mov qword ptr [rbp+0x1C0],0                   
0x666e006  mov edx,0x50                                  
0x666e00b  call r8                                       
0x666e00e  nop                                           
0x666e00f  mov rsi,rax                                   
0x666e012  test rax,rax                                  
0x666e015  je 0x6670A41                                  ; -> sub_6670a41
0x666e01b  mov [rbp+0x3F8],rsi                           
0x666e022  mov rax,rsi                                   
0x666e025  add rax,0x10                                  
0x666e029  mov [rbp+0x660],rax                           
0x666e030  mov qword ptr [rsi+0x18],0                    
0x666e038  mov qword ptr [rsi+0x20],9                    
0x666e040  mov qword ptr [rsi+0x28],0xF                  
0x666e048  mov rax,0x7365546168706C41                    ; "ABlksBase"
0x666e052  mov [rsi+0x10],rax                            
0x666e056  mov byte ptr [rsi+0x18],0x74                  
0x666e05a  xorps xmm0,xmm0                               
0x666e05d  movups [rsi+0x30],xmm0                        
0x666e061  mov [rbp+0x658],rsi                           
0x666e068  movups [rsi+0x40],xmm0                        
0x666e06c  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666e073  mov rax,[rcx]                                 
0x666e076  mov rax,[rax+8]                               
0x666e07a  mov edx,0x20                                  
0x666e07f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666e085  nop                                           
0x666e086  mov rsi,rax                                   
0x666e089  test rax,rax                                  
0x666e08c  je 0x6670A5C                                  ; -> sub_6670a5c
0x666e092  mov r14,[rbp+0x658]                           
0x666e099  mov [r14+0x30],rsi                            
0x666e09d  mov qword ptr [r14+0x40],0x14                 
0x666e0a5  mov qword ptr [r14+0x48],0x1F                 
0x666e0ad  movups xmm0,[0xF5F4D16]                       ; [data_f5f4d16] "On_DiscardValueBased"
```

### Gap 14: 0x666e0be..0x666e0f1 (FNV hash remainder bytes + jump)
```
0x666e0be  mov byte ptr [rsi+0x14],0                     
0x666e0c2  mov r12,[r14+0x20]                            
0x666e0c6  cmp qword ptr [r14+0x28],0x10                 
0x666e0cb  mov r13,[rbp+0x660]                           
0x666e0d2  jb short 0x666E0D8                            ; -> loc_666e0d8
0x666e0d4  mov r13,[r14+0x10]                            

loc_666e0d8:  ; from 666e0d2
0x666e0d8  test r12,r12                                  
0x666e0db  je 0x666F03F                                  ; -> loc_666f03f
0x666e0e1  mov eax,r12d                                  
0x666e0e4  and eax,3                                     
0x666e0e7  cmp r12,4                                     
0x666e0eb  jae 0x666F04E                                 ; -> loc_666f04e
0x666e0f1  mov rdi,0xCBF29CE484222325                    ; FNV offset basis
0x666e0fb  xor ecx,ecx                                   
0x666e0fd  jmp 0x666F0AD                                 ; -> loc_666f0ad
```

### Gap 15: 0x666e13b..0x666e197 (shared_ref handling + inc/dec refcount)
```
0x666e13b  je 0x666EED3                                  ; -> loc_666eed3
0x666e141  lock inc dword ptr [rcx+8]                    
0x666e145  mov rsi,[rbp+0x3F8]                           
0x666e14c  movups xmm0,[rax]                             
0x666e14f  movaps [rbp+0x3F0],xmm0                       
0x666e156  test rsi,rsi                                  
0x666e159  je 0x666EEE8                                  ; -> loc_666eee8
0x666e15f  lock dec dword ptr [rsi+8]                    
0x666e163  jne 0x666EEE8                                 ; -> loc_666eee8
0x666e169  mov rax,[rsi]                                 
0x666e16c  mov rax,[rax]                                 
0x666e16f  mov rcx,rsi                                   
0x666e172  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666e178  lock dec dword ptr [rsi+0xC]                  
0x666e17c  jne 0x666EEE8                                 ; -> loc_666eee8
0x666e182  mov rax,[rsi]                                 
0x666e185  mov rax,[rax+8]                               
0x666e189  mov rcx,rsi                                   
0x666e18c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666e192  jmp 0x666EEE8                                 ; -> loc_666eee8
```

### Gap 16: 0x666e197..0x666e1ce (shared_ref cleanup)
```
0x666e197  mov rsi,[rbp+0x638]                           
0x666e19e  test rsi,rsi                                  
0x666e1a1  je short 0x666E1CE                            ; -> loc_666e1ce
0x666e1a3  lock dec dword ptr [rsi+8]                    
0x666e1a7  jne short 0x666E1CE                           ; -> loc_666e1ce
0x666e1a9  mov rax,[rsi]                                 
0x666e1ac  mov rax,[rax]                                 
0x666e1af  mov rcx,rsi                                   
0x666e1b2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666e1b8  lock dec dword ptr [rsi+0xC]                  
0x666e1bc  jne short 0x666E1CE                           ; -> loc_666e1ce
0x666e1be  mov rax,[rsi]                                 
0x666e1c1  mov rax,[rax+8]                               
0x666e1c5  mov rcx,rsi                                   
0x666e1c8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

### Gap 17: 0x666e1eb..0x666e209 (buffer free)
```
loc_666e1eb:  ; from 666e1eb
0x666e1eb  jb short 0x666E209                            ; -> loc_666e209
0x666e1ed  mov rax,[rcx-8]                               
0x666e1f1  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666e1f5  sub rcx,rax                                   
0x666e1f8  cmp rcx,0x20                                  
0x666e1fc  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666e202  add rdx,0x27                                  
0x666e206  mov rcx,rax                                   

loc_666e209:  ; from 666e1eb
0x666e209  call 0xE935700                                ; -> sub_e935700
0x666e20e  xorps xmm0,xmm0                               
0x666e211  movups [rdi],xmm0                             
0x666e214  mov qword ptr [rdi+0x10],0                    
```

### Gap 18: 0x666e295..0x666e2bf (buffer free + jump to 0x666F4ED)
```
0x666e295  jb 0x667002D                                  ; -> loc_667002d
0x666e29b  mov r8,[rcx-8]                                
0x666e29f  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666e2a3  sub rcx,r8                                    
0x666e2a6  cmp rcx,0x20                                  
0x666e2aa  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666e2b0  add rax,0x28                                  
0x666e2b4  mov rdx,rax                                   
0x666e2b7  mov rcx,r8                                    
0x666e2ba  jmp 0x667002D                                 ; -> loc_667002d
0x666e2bf  lea rdx,[rbp+0x368]                           
0x666e2c6  movups xmm0,[rdx]                             
0x666e2c9  movups [rcx],xmm0                             
0x666e2cc  jmp 0x666F4ED                                 ; -> loc_666f4ed
0x666e2d1  xorps xmm0,xmm0                               
0x666e2d4  movups [rcx],xmm0                             
0x666e2d7  mov rcx,[rbp+0x370]                           
0x666e2de  test rcx,rcx                                  
0x666e2e1  je 0x666F4D6                                  ; -> loc_666f4d6
0x666e2e7  lock inc dword ptr [rcx+8]                    
0x666e2eb  mov rcx,[rbp+0x370]                           
0x666e2f2  jmp 0x666F4D8                                 ; -> loc_666f4d8
```

### Gap 19: 0x666e7aa..0x666e7e1 (shared_ref cleanup)

### Gap 17: 0x666e1eb..0x666e209 (buffer free)

### Gap 18: 0x666e295..0x666e2bf (buffer free + jump to 0x666F4ED)

### Gap 19: 0x666e7aa..0x666e7e1 (shared_ref cleanup + lookup table stride 0x30)
```
0x666e7aa  mov rsi,[rbp+0x3F8]                           
0x666e7b1  test rsi,rsi                                  
0x666e7b4  je short 0x666E7E1                            ; -> loc_666e7e1
0x666e7b6  lock dec dword ptr [rsi+8]                    
0x666e7ba  jne short 0x666E7E1                           ; -> loc_666e7e1
0x666e7bc  mov rax,[rsi]                                 
0x666e7bf  mov rax,[rax]                                 
0x666e7c2  mov rcx,rsi                                   
0x666e7c5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666e7cb  lock dec dword ptr [rsi+0xC]                  
0x666e7cf  jne short 0x666E7E1                           ; -> loc_666e7e1
0x666e7d1  mov rax,[rsi]                                 
0x666e7d4  mov rax,[rax+8]                               
0x666e7d8  mov rcx,rsi                                   
0x666e7db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_666e7e1:  ; from 666e7b4, 666e7ba, 666e7cf
0x666e7e1  mov rax,[rbp+0x48]                            
0x666e7e5  movzx r8d,word ptr [rbp+0x52]                 
0x666e7ea  mov ecx,r8d                                   
0x666e7ed  shl ecx,4                                     
0x666e7f0  lea rdx,[rcx+rcx*2]                           
0x666e7f4  mov rcx,rax                                   
0x666e7f7  test r8,r8                                    
0x666e7fa  je short 0x666E825                            ; -> loc_666e825
0x666e7fc  mov r8,[0x129FA148]                           ; [data_129fa148]
0x666e803  mov r9,rdx                                    
0x666e806  mov rcx,rax                                   
0x666e809  nop [rax]                                     

loc_666e810:  ; from 666e821
0x666e810  mov r10,[rcx]                                 
0x666e813  cmp [r10+0x28],r8                             
0x666e817  je short 0x666E825                            ; -> loc_666e825
0x666e819  add rcx,0x30                                  
0x666e81d  add r9,0xFFFFFFFFFFFFFFD0                     
0x666e821  jne short 0x666E810                           ; -> loc_666e810
0x666e823  jmp short 0x666E873                           ; -> loc_666e873

loc_666e825:  ; from 666e7fa, 666e817
0x666e825  add rdx,rax                                   
0x666e828  cmp rcx,rdx                                   
0x666e82b  jae short 0x666E873                           ; -> loc_666e873
0x666e82d  sub ecx,eax                                   
0x666e82f  shr ecx,4                                     
0x666e832  imul eax,ecx,0xFFFFAAAB                       
0x666e838  mov [rbp+0x1D0],ax                            
0x666e83f  mov byte ptr [rbp+0x1D2],1                    
0x666e846  mov byte ptr [rbp+0x3FC],0                    
0x666e84d  mov dword ptr [rsp+0x20],0                    
0x666e855  mov rcx,rbp                                   
0x666e858  lea rdx,[rbp+0x1D0]                           
0x666e85f  lea r9,[rbp+0x3F0]                            
0x666e866  mov r8,[rbp+0x670]                            
0x666e86d  call 0xBCABA00                                ; -> sub_bcaba00
```

### Gap 20: 0x666ea9b..0x666ead2 (shared_ref cleanup + render-state mapper setup)
```
0x666ea9b  mov [rbp+0x3D8],rax                           
0x666eaa2  test rsi,rsi                                  
0x666eaa5  je short 0x666EAD2                            ; -> loc_666ead2
0x666eaa7  lock dec dword ptr [rsi+8]                    
0x666eaab  jne short 0x666EAD2                           ; -> loc_666ead2
0x666eaad  mov rax,[rsi]                                 
0x666eab0  mov rax,[rax]                                 
0x666eab3  mov rcx,rsi                                   
0x666eab6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666eabc  lock dec dword ptr [rsi+0xC]                  
0x666eac0  jne short 0x666EAD2                           ; -> loc_666ead2
0x666eac2  mov rax,[rsi]                                 
0x666eac5  mov rax,[rax+8]                               
0x666eac9  mov rcx,rsi                                   
0x666eacc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_666ead2:  ; from 666eaa5, 666eaab, 666eac0
0x666ead2  mov rax,[rbp+0x648]                           
0x666ead9  mov r8,[rax+0x3B8]                            
0x666eae0  mov rdx,[r13]                                 
0x666eae4  mov [rsp+0x20],r14d                           
0x666eae9  mov dword ptr [rsp+0x30],0                    
0x666eaf1  mov dword ptr [rsp+0x28],0                    
0x666eaf9  lea rcx,[rbp+0x1D0]                           
0x666eb00  lea r9,[rbp+0x3D0]                            
0x666eb07  call 0x66A0F60                                ; -> sub_66a0f60
```

### Gap 21: 0x666eb26..0x666ecfc (record setup + mode flag logic + jump table)
```
0x666eb26  movss [rbp+0x3FC],xmm6                        
0x666eb2e  mov dword ptr [rbp+0x404],2                   
0x666eb38  mov byte ptr [rbp+0x408],7                    
0x666eb3f  mov dword ptr [rbp+0x40C],0                   
0x666eb49  mov word ptr [rbp+0x410],1                    
0x666eb52  mov byte ptr [rbp+0x412],2                    
0x666eb59  mov dword ptr [rbp+0x414],0                   
0x666eb63  mov byte ptr [rbp+0x418],0                    
0x666eb6a  xorps xmm0,xmm0                               
0x666eb6d  movups [rbp+0x41C],xmm0                       
0x666eb74  mov [rbp+0x42C],r15d                          
0x666eb7b  mov qword ptr [rbp+0x430],0                   
0x666eb86  mov byte ptr [rbp+0x438],8                    
0x666eb8d  mov qword ptr [rbp+0x43C],0                   
0x666eb98  mov dword ptr [rbp+0x444],0                   
0x666eba2  mov byte ptr [rbp+0x448],8                    
0x666eba9  mov qword ptr [rbp+0x44C],0                   
0x666ebb4  mov qword ptr [rbp+0x452],0                   
0x666ebbf  mov byte ptr [rbp+0x45A],0xFF                 
0x666ebc6  mov rax,[rbp]                                 
0x666ebca  mov [rbp+0x460],rax                           
0x666ebd1  lea rcx,[rbp+0x468]                           
0x666ebd8  mov rdx,rbx                                   
0x666ebdb  call 0xE869FF0                                ; -> sub_e869ff0
0x666ebe0  nop                                           
0x666ebe1  mov rax,[rbp+0x80]                            
0x666ebe8  mov [rbp+0x4E0],rax                           
0x666ebef  mov qword ptr [rbp+0x80],0                    
0x666ebfa  mov byte ptr [rbp+0x528],0xFF                 
0x666ec01  movzx eax,byte ptr [rbp+0x380]                
0x666ec08  movzx ecx,al                                  
0x666ec0b  cmp ecx,1                                     
0x666ec0e  lea r10,[rbp+0x404]                           
0x666ec15  lea r11,[rbp+0x460]                           
0x666ec1c  jg short 0x666EC5C                            ; -> loc_666ec5c
0x666ec1e  test ecx,ecx                                  
0x666ec20  jne short 0x666EC71                           ; -> loc_666ec71
0x666ec22  movaps xmm0,[rbp+0x340]                       
0x666ec29  movaps xmm1,[rbp+0x350]                       
0x666ec30  movaps xmm2,[rbp+0x360]                       
0x666ec37  movaps xmm3,[rbp+0x370]                       
0x666ec3e  movups [rbp+0x4E8],xmm0                       
0x666ec45  movups [rbp+0x4F8],xmm1                       
0x666ec4c  movups [rbp+0x508],xmm2                       
0x666ec53  movups [rbp+0x518],xmm3                       
0x666ec5a  jmp short 0x666ECA2                           ; -> loc_666eca2

loc_666ec5c:  ; from 666ec1c
0x666ec5c  cmp ecx,2                                     
0x666ec5f  jne short 0x666ECA8                           ; -> loc_666eca8
0x666ec61  mov rcx,[rbp+0x340]                           
0x666ec68  mov [rbp+0x4E8],rcx                           
0x666ec6f  jmp short 0x666ECA2                           ; -> loc_666eca2

loc_666ec71:  ; from 666ec20
0x666ec71  mov rcx,[rbp+0x350]                           
0x666ec78  mov qword ptr [rbp+0x350],0                   
0x666ec83  movaps xmm0,[rbp+0x340]                       
0x666ec8a  xorps xmm1,xmm1                               
0x666ec8d  movaps [rbp+0x340],xmm1                       
0x666ec94  movups [rbp+0x4E8],xmm0                       
0x666ec9b  mov [rbp+0x4F8],rcx                           

loc_666eca2:  ; from 666ec5a, 666ec6f
0x666eca2  mov [rbp+0x528],al                            

loc_666eca8:  ; from 666ec5f
0x666eca8  lea r9,[rbp+0x4E8]                            
0x666ecaf  lea r8,[rbp+0x530]                            
0x666ecb6  movaps xmm0,[rbp+0x1D0]                       
0x666ecbd  movaps xmm1,[rbp+0x1E0]                       
0x666ecc4  mov qword ptr [rbp+0x1D8],0                   
0x666eccf  movups [rbp+0x530],xmm0                       
0x666ecd6  xorps xmm0,xmm0                               
0x666ecd9  movaps [rbp+0x1E0],xmm0                       
0x666ece0  movups [rbp+0x540],xmm1                       
0x666ece7  mov rax,[rbp+0x1F0]                           
0x666ecee  mov [rbp+0x550],rax                           
0x666ecf5  mov byte ptr [rbp+0x568],0xFF                 
0x666ecfc  movzx eax,byte ptr [rbp+0x208]                
0x666ed03  cmp rax,3                                     
0x666ed07  ja short 0x666ED79                            ; -> loc_666ed79
0x666ed09  lea rcx,[0xF2BF4E0]                           ; [data_f2bf4e0]
0x666ed10  movsxd rdx,[rcx+rax*4]                        
0x666ed14  add rdx,rcx                                   
0x666ed17  jmp rdx                                       
```

### Gap 22: 0x666ef18..0x666ef4f (shared_ref cleanup + call 0xBBD7F70 + thread-local checks)
```
0x666ef18  mov rsi,[rbp+0x3F8]                           
0x666ef1f  test rsi,rsi                                  
0x666ef22  je short 0x666EF4F                            ; -> loc_666ef4f
0x666ef24  lock dec dword ptr [rsi+8]                    
0x666ef28  jne short 0x666EF4F                           ; -> loc_666ef4f
0x666ef2a  mov rax,[rsi]                                 
0x666ef2d  mov rax,[rax]                                 
0x666ef30  mov rcx,rsi                                   
0x666ef33  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666ef39  lock dec dword ptr [rsi+0xC]                  
0x666ef3d  jne short 0x666EF4F                           ; -> loc_666ef4f
0x666ef3f  mov rax,[rsi]                                 
0x666ef42  mov rax,[rax+8]                               
0x666ef46  mov rcx,rsi                                   
0x666ef49  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_666ef4f:  ; from 666ef22, 666ef28, 666ef3d
0x666ef4f  mov rax,[rbp+0x668]                           
0x666ef56  mov r9,[rax]                                  
0x666ef59  lea rcx,[rbp+0x1D0]                           
0x666ef60  mov r8,rbp                                    
0x666ef63  mov rdx,r15                                   
0x666ef66  call 0xBBD7F70                                ; -> sub_bbd7f70
0x666ef6b  nop                                           
0x666ef6c  cmp byte ptr [rbp+0x228],0                    
0x666ef73  je 0x66708EE                                  ; -> loc_66708ee
0x666ef79  mov rax,[rbp+0x668]                           
0x666ef80  lea r9,[rax+8]                                
0x666ef84  lea rax,[rbp+0x3E0]                           
0x666ef8b  mov [rsp+0x20],rax                            
0x666ef90  mov dword ptr [rsp+0x28],0                    
0x666ef98  lea r8,[0x129F8318]                           ; [data_129f8318]
0x666ef9f  mov rcx,rbp                                   
0x666efa2  lea rdx,[rbp+0x3F0]                           
0x666efa9  call 0xBCAB8F0                                ; -> sub_bcab8f0
```

### Gap 23: 0x666f744..0x666f761 (shared_ref destroy x3)

### Gap 23: 0x666f744..0x666f761 (shared_ref destroy x3 + buffer check)
```
0x666f744  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666f74b  mov rax,[rcx]                                 
0x666f74e  mov rax,[rax+0x10]                            
0x666f752  mov dl,0x4A                                   
0x666f754  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666f75a  nop                                           
0x666f75b  mov [rbp+0x670],al                            
0x666f761  mov rdx,[rsi+0x8A8]                           
```

### Gap 24: 0x666f799..0x666f7e5 (shared_ref destroy x3 + buffer count + call 0x675FB30)
```
0x666f799  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666f7a0  mov rax,[rcx]                                 
0x666f7a3  mov rax,[rax+0x10]                            
0x666f7a7  movzx edx,byte ptr [rbp+0x670]                
0x666f7ae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666f7b4  nop                                           
0x666f7b5  mov eax,[rsi+0x8A8]                           
0x666f7bb  sub eax,[rsi+0x8A0]                           
0x666f7c1  shr eax,1                                     
0x666f7c3  dec eax                                       
0x666f7c5  mov [rbp+0x10],ax                             
0x666f7c9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666f7d0  mov rax,[rcx]                                 
0x666f7d3  mov rax,[rax+0x10]                            
0x666f7d7  mov dl,0x4A                                   
0x666f7d9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666f7df  mov [rbp+0x670],al                            
0x666f7e5  lea rdx,[rbp+0x3F8]                           
```

### Gap 25: 0x666f7fc..0x666f818 (shared_ref destroy x3 + buffer count)
```
0x666f7fc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666f803  mov rax,[rcx]                                 
0x666f806  mov rax,[rax+0x10]                            
0x666f80a  movzx edx,byte ptr [rbp+0x670]                
0x666f811  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666f817  nop                                           
0x666f818  mov eax,[rsi+0x650]                           
```

### Gap 26: 0x666f833..0x666f84a (shared_ref destroy x3 + buffer count)
```
0x666f833  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666f83a  mov rax,[rcx]                                 
0x666f83d  mov rax,[rax+0x10]                            
0x666f841  mov dl,0x4A                                   
0x666f843  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666f849  nop                                           
0x666f84a  mov edx,eax                                   
```

### Gap 27: 0x666f9da..0x666f9ef (shared_ref destroy + draw key)
```
0x666f9da  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666f9e1  mov rax,[rcx]                                 
0x666f9e4  mov rax,[rax+0x10]                            
0x666f9e8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666f9ee  nop                                           
0x666f9ef  mov rax,0x8002007001                          ; draw key
0x666f9f9  mov [rbp],rax                                 
```

### Gap 28: 0x666fa0f..0x666fa2c (shared_ref destroy + draw record emit stride 0xC8)
```
0x666fa0f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666fa16  mov rax,[rcx]                                 
0x666fa19  mov rax,[rax+0x10]                            
0x666fa1d  mov dl,0x4A                                   
0x666fa1f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fa25  nop                                           
0x666fa26  mov [rbp+0x670],al                            
0x666fa2c  mov rax,[rsi+8]                               
```

### Gap 29: 0x666fa60..0x666fa7c (shared_ref destroy + call 0x66E5B10)
```
0x666fa60  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666fa67  mov rax,[rcx]                                 
0x666fa6a  mov rax,[rax+0x10]                            
0x666fa6e  movzx edx,byte ptr [rbp+0x670]                
0x666fa75  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fa7b  nop                                           
0x666fa7c  lea rcx,[rbp+0x3F0]                           
```

### Gap 30: 0x666fa8f..0x666fad1 (mode flag checks + buffer free check)
```
0x666fa8f  jne short 0x666FAD1                           ; -> loc_666fad1
0x666fa91  mov rcx,[rbp+0x2A0]                           
0x666fa98  test rcx,rcx                                  
0x666fa9b  je short 0x666FAD1                            ; -> loc_666fad1
0x666fa9d  mov rdx,[rbp+0x2B0]                           
0x666faa4  sub rdx,rcx                                   
0x666faa7  cmp rdx,0x1000                                
0x666faae  jb short 0x666FACC                            ; -> loc_666facc
0x666fab0  mov rax,[rcx-8]                               
0x666fab4  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666fab8  sub rcx,rax                                   
0x666fabb  cmp rcx,0x20                                  
0x666fabf  jae 0x6670A7A                                 ; -> loc_6670a7a
0x666fac5  or rdx,0x27                                   
0x666fac9  mov rcx,rax                                   

loc_666facc:  ; from 666faae
0x666facc  call 0xE935700                                ; -> sub_e935700
```

### Gap 31: 0x666fae7..0x666fb1e (shared_ref cleanup + array cleanup setup)
```
0x666fae7  mov rsi,[rbp+0x370]                           
0x666faee  test rsi,rsi                                  
0x666faf1  je short 0x666FB1E                            ; -> loc_666fb1e
0x666faf3  lock dec dword ptr [rsi+8]                    
0x666faf7  jne short 0x666FB1E                           ; -> loc_666fb1e
0x666faf9  mov rax,[rsi]                                 
0x666fafc  mov rax,[rax]                                 
0x666faff  mov rcx,rsi                                   
0x666fb02  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fb08  lock dec dword ptr [rsi+0xC]                  
0x666fb0c  jne short 0x666FB1E                           ; -> loc_666fb1e
0x666fb0e  mov rax,[rsi]                                 
0x666fb11  mov rax,[rax+8]                               
0x666fb15  mov rcx,rsi                                   
0x666fb18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_666fb1e:  ; from 666faf1, 666faf7, 666fb0c
0x666fb1e  mov rdi,[rbp+0x348]                           
0x666fb25  test rdi,rdi                                  
0x666fb28  je short 0x666FB78                            ; -> loc_666fb78
0x666fb2a  mov rbx,[rbp+0x350]                           
```

### Gap 32: 0x666fb2a..0x666fb78 (array cleanup stride 0x28 filter byte+0x18==2)
```
0x666fb2a  mov rbx,[rbp+0x350]                           
0x666fb31  jmp short 0x666FB37                           ; -> loc_666fb37

loc_666fb33:  ; from 666fb40, 666fb49, 666fb4f, 666fb64, 666fb76
0x666fb33  add rdi,0x28                                  

loc_666fb37:  ; from 666fb31
0x666fb37  cmp rdi,rbx                                   
0x666fb3a  je short 0x666FB78                            ; -> loc_666fb78
0x666fb3c  cmp byte ptr [rdi+0x18],2                     
0x666fb40  jne short 0x666FB33                           ; -> loc_666fb33
0x666fb42  mov rsi,[rdi+8]                               
0x666fb46  test rsi,rsi                                  
0x666fb49  je short 0x666FB33                            ; -> loc_666fb33
0x666fb4b  lock dec dword ptr [rsi+8]                    
0x666fb4f  jne short 0x666FB33                           ; -> loc_666fb33
0x666fb51  mov rax,[rsi]                                 
0x666fb54  mov rax,[rax]                                 
0x666fb57  mov rcx,rsi                                   
0x666fb5a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fb60  lock dec dword ptr [rsi+0xC]                  
0x666fb64  jne short 0x666FB33                           ; -> loc_666fb33
0x666fb66  mov rax,[rsi]                                 
0x666fb69  mov rax,[rax+8]                               
0x666fb6d  mov rcx,rsi                                   
0x666fb70  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fb76  jmp short 0x666FB33                           ; -> loc_666fb33

loc_666fb78:  ; from 666fb28, 666fb3a
0x666fb78  mov rsi,[rbp+0x638]                           
```

### Gap 33: 0x666fb8c..0x666fbc0 (shared_ref cleanup + hash table link update)
```
0x666fb8c  jne 0x6670032                                 ; -> loc_6670032
0x666fb92  mov rax,[rsi]                                 
0x666fb95  mov rax,[rax]                                 
0x666fb98  mov rcx,rsi                                   
0x666fb9b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fba1  lock dec dword ptr [rsi+0xC]                  
0x666fba5  jne 0x6670032                                 ; -> loc_6670032
0x666fbab  mov rax,[rsi]                                 
0x666fbae  mov rax,[rax+8]                               
0x666fbb2  mov rcx,rsi                                   
0x666fbb5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fbbb  jmp 0x6670032                                 ; -> loc_6670032
0x666fbc0  mov rax,[rbx]                                 
```

### Gap 34: 0x666fbea..0x666fc9e (hash table link update + cleanup + alloc)
```
0x666fbea  mov [rax+8],r14                               
0x666fbee  mov rcx,[rbp+0x5F8]                           
0x666fbf5  and rdi,[rbp+0x610]                           
0x666fbfc  shl rdi,4                                     
0x666fc00  mov r8,[rcx+rdi]                              
0x666fc04  cmp r8,[rbp+0x5E8]                            
0x666fc0b  je short 0x666FC73                            ; -> loc_666fc73
0x666fc0d  cmp r8,rax                                    
0x666fc10  je short 0x666FC6D                            ; -> loc_666fc6d

loc_666fc12:  ; from 666fc6b
0x666fc12  cmp [rcx+rdi+8],rdx                           
0x666fc17  jne short 0x666FC7C                           ; -> loc_666fc7c
0x666fc19  jmp short 0x666FC77                           ; -> loc_666fc77
0x666fc1b  mov rax,rbx                                   
0x666fc1e  mov r14,[rbp+0x658]                           
0x666fc25  mov qword ptr [rbp+0x3F8],0                   
0x666fc30  mov rdx,[rax+8]                               
0x666fc34  inc qword ptr [rbp+0x5F0]                     
0x666fc3b  mov [r14],rax                                 
0x666fc3e  mov [r14+8],rdx                               
0x666fc42  mov [rdx],r14                                 
0x666fc45  mov [rax+8],r14                               
0x666fc49  mov rcx,[rbp+0x5F8]                           
0x666fc50  and rdi,[rbp+0x610]                           
0x666fc57  shl rdi,4                                     
0x666fc5b  mov r8,[rcx+rdi]                              
0x666fc5f  cmp r8,[rbp+0x5E8]                            
0x666fc66  je short 0x666FC73                            ; -> loc_666fc73
0x666fc68  cmp r8,rax                                    
0x666fc6b  jne short 0x666FC12                           ; -> loc_666fc12

loc_666fc6d:  ; from 666fc10
0x666fc6d  mov [rcx+rdi],r14                             
0x666fc71  jmp short 0x666FC7C                           ; -> loc_666fc7c

loc_666fc73:  ; from 666fc0b, 666fc66
0x666fc73  mov [rcx+rdi],r14                             

loc_666fc77:  ; from 666fc19
0x666fc77  mov [rcx+rdi+8],r14                           

loc_666fc7c:  ; from 666fc17, 666fc71
0x666fc7c  mov r14,[rbp+0x3F8]                           
0x666fc83  test r14,r14                                  
0x666fc86  je short 0x666FC9E                            ; -> loc_666fc9e
0x666fc88  lea rcx,[r14+0x10]                            
0x666fc8c  call 0x9B250                                  ; -> sub_9b250
0x666fc91  mov edx,0x50                                  
0x666fc96  mov rcx,r14                                   
0x666fc99  call 0xE935700                                ; -> sub_e935700

loc_666fc9e:  ; from 666fc86
0x666fc9e  cmp qword ptr [0x129F9240],0x10               ; [data_129f9240]
```

### Gap 35: 0x666fca6..0x666ff60 (cleanup + element processing + return path)
```
0x666fca6  jb short 0x666FCB1                            ; -> loc_666fcb1
0x666fca8  mov r13,[0x129F9228]                          ; [data_129f9228]
0x666fcaf  jmp short 0x666FCB8                           ; -> loc_666fcb8

loc_666fcb1:  ; from 666fca6
0x666fcb1  lea r13,[0x129F9228]                          ; [data_129f9228]

loc_666fcb8:  ; from 666fcaf
0x666fcb8  mov rax,[rbp+0x650]                           
0x666fcbf  mov rbx,[rax+0x40]                            
0x666fcc3  mov r15,[rax+0x68]                            
0x666fcc7  mov rdi,[0x129F9238]                          ; [data_129f9238]
0x666fcce  mov eax,[rbp+0x5E0]                           
0x666fcd4  mov [rbp+0x300],eax                           
0x666fcda  xorps xmm0,xmm0                               
0x666fcdd  movups [rbp+0x308],xmm0                       
0x666fce4  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666fceb  mov rax,[rcx]                                 
0x666fcee  mov rax,[rax+8]                               
0x666fcf2  mov edx,0x50                                  
0x666fcf7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fcfd  nop                                           
0x666fcfe  mov rsi,rax                                   
0x666fd01  test rax,rax                                  
0x666fd04  je 0x66709C7                                  ; -> loc_66709c7

loc_666fd0a:  ; from 66709d2
0x666fd0a  mov [rbp+0x660],rdi                           
0x666fd11  mov [rsi],rsi                                 
0x666fd14  mov [rsi+8],rsi                               
0x666fd18  mov [rbp+0x308],rsi                           
0x666fd1f  lea rcx,[rbp+0x318]                           
0x666fd26  xorps xmm0,xmm0                               
0x666fd29  movups [rbp+0x318],xmm0                       
0x666fd30  mov qword ptr [rbp+0x328],0                   
0x666fd3b  movups xmm0,[rbp+0x610]                       
0x666fd42  movups [rbp+0x330],xmm0                       
0x666fd49  mov rdx,[rbp+0x600]                           
0x666fd50  sub rdx,[rbp+0x5F8]                           
0x666fd57  sar rdx,3                                     
0x666fd5b  mov r8,rsi                                    
0x666fd5e  call 0x76B30                                  ; -> sub_76b30
0x666fd63  nop                                           
0x666fd64  mov r14,[rbp+0x5E8]                           
0x666fd6b  mov r12,[r14]                                 
0x666fd6e  cmp r12,r14                                   
0x666fd71  je short 0x666FDAA                            ; -> loc_666fdaa
0x666fd73  lea rsi,[rbp+0x300]                           
0x666fd7a  lea rdi,[rbp+0x3F0]                           
0x666fd81  nop [rax+rax]                                 ; R ret@76b30+0x0+idx

loc_666fd90:  ; from 666fda8
0x666fd90  lea r8,[r12+0x10]                             
0x666fd95  mov rcx,rsi                                   
0x666fd98  mov rdx,rdi                                   
0x666fd9b  call 0xAA840                                  ; -> sub_aa840
0x666fda0  nop                                           
0x666fda1  mov r12,[r12]                                 
0x666fda5  cmp r12,r14                                   
0x666fda8  jne short 0x666FD90                           ; -> loc_666fd90

loc_666fdaa:  ; from 666fd71
0x666fdaa  cmp qword ptr [0x129F9240],0x10               ; [data_129f9240]
0x666fdb2  jb short 0x666FDBD                            ; -> loc_666fdbd
0x666fdb4  mov rax,[0x129F9228]                          ; [data_129f9228]
0x666fdbb  jmp short 0x666FDC4                           ; -> loc_666fdc4

loc_666fdbd:  ; from 666fdb2
0x666fdbd  lea rax,[0x129F9228]                          ; [data_129f9228]

loc_666fdc4:  ; from 666fdbb
0x666fdc4  mov r14,[rbp+0x650]                           
0x666fdcb  mov rsi,rbx                                   
0x666fdce  mov rbx,[rbp+0x660]                           
0x666fdd5  mov rcx,[0x129F9238]                          ; [data_129f9238]
0x666fddc  mov [rbp+0x630],rax                           
0x666fde3  mov [rbp+0x638],rcx                           
0x666fdea  mov rcx,rbp                                   
0x666fded  lea rdx,[rbp+0x630]                           
0x666fdf4  lea r8,[rbp+0x300]                            
0x666fdfb  call 0x66A02D0                                ; -> sub_66a02d0
0x666fe00  nop                                           
0x666fe01  mov [rbp+0x3F0],r13                           
0x666fe08  mov [rbp+0x3F8],rbx                           
0x666fe0f  lea rax,[rbp+0x5E0]                           
0x666fe16  mov [rsp+0x28],rax                            
0x666fe1b  lea rax,[rbp+0x3F0]                           
0x666fe22  mov [rsp+0x20],rax                            
0x666fe27  lea rdx,[rbp+0x5C0]                           
0x666fe2e  mov r8,rbp                                    
0x666fe31  mov rcx,r15                                   
0x666fe34  mov r9,rsi                                    
0x666fe37  call 0x67CFD80                                ; -> sub_67cfd80
0x666fe3c  nop                                           
0x666fe3d  lea rdi,[rbp+0x5F8]                           
0x666fe44  mov rsi,[rbp+0x5C0]                           
0x666fe4b  mov rbx,[rsi]                                 
0x666fe4e  test rbx,rbx                                  
0x666fe51  mov r12,[rbp+0x648]                           
0x666fe58  je 0x666FF60                                  ; -> loc_666ff60
```

### Gap 35b: 0x666fe58..0x666ff60 (thread-local check + shared_ref chain walk + buffer free path)
```
0x666fe5e  mov eax,[0x129CA5E0]                          ; [data_129ca5e0]
0x666fe64  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x666fe6a  mov rdx,gs:[0x58]                             
0x666fe73  mov rcx,[rdx+rcx*8]                           
0x666fe77  cmp eax,[rcx+4]                               
0x666fe7d  jg 0x66710A5                                  ; -> loc_66710a5

loc_666fe83:  ; from 66710b8, 66710f1
0x666fe83  cmp byte ptr [rbx+0x10],1                     
0x666fe87  jne 0x666FF60                                 ; -> loc_666ff60
0x666fe8d  mov rax,[rsi+8]                               
0x666fe91  test rax,rax                                  
0x666fe94  je short 0x666FEDA                            ; -> loc_666feda
0x666fe96  lock inc dword ptr [rax+8]                    
0x666fe9a  mov rax,[rsi]                                 
0x666fe9d  mov rsi,[rsi+8]                               
0x666fea1  mov rax,[rax+0x18]                            
0x666fea5  mov rbx,[rax]                                 
0x666fea8  test rsi,rsi                                  
0x666feab  je short 0x666FEE4                            ; -> loc_666fee4
0x666fead  lock dec dword ptr [rsi+8]                    
0x666feb1  jne short 0x666FEE4                           ; -> loc_666fee4
0x666feb3  mov rax,[rsi]                                 
0x666feb6  mov rax,[rax]                                 
0x666feb9  mov rcx,rsi                                   
0x666febc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fec2  lock dec dword ptr [rsi+0xC]                  
0x666fec6  jne short 0x666FEE4                           ; -> loc_666fee4
0x666fec8  mov rax,[rsi]                                 
0x666fecb  mov rax,[rax+8]                               
0x666fecf  mov rcx,rsi                                   
0x666fed2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666fed8  jmp short 0x666FEE4                           ; -> loc_666fee4

loc_666feda:  ; from 666fe94
0x666feda  mov rax,[rsi]                                 
0x666fedd  mov rax,[rax+0x18]                            
0x666fee1  mov rbx,[rax]                                 

loc_666fee4:  ; from 666feab, 666feb1, 666fec6, 666fed8
0x666fee4  test rbx,rbx                                  
0x666fee7  je short 0x666FF60                            ; -> loc_666ff60
0x666fee9  mov rbx,[r14]                                 
0x666feec  mov rax,[rbp+0x5C0]                           
0x666fef3  xorps xmm0,xmm0                               
0x666fef6  movaps [rbp+0x3F0],xmm0                       
0x666fefd  mov rcx,[rax+8]                               
0x666ff01  test rcx,rcx                                  
0x666ff04  je 0x667005C                                  ; -> loc_667005c
0x666ff0a  lock inc dword ptr [rcx+8]                    
0x666ff0e  mov rsi,[rbp+0x3F8]                           
0x666ff15  movups xmm0,[rax]                             
0x666ff18  movaps [rbp+0x3F0],xmm0                       
0x666ff1f  test rsi,rsi                                  
0x666ff22  je 0x6670071                                  ; -> loc_6670071
0x666ff28  lock dec dword ptr [rsi+8]                    
0x666ff2c  jne 0x6670071                                 ; -> loc_6670071
0x666ff32  mov rax,[rsi]                                 
0x666ff35  mov rax,[rax]                                 
0x666ff38  mov rcx,rsi                                   
0x666ff3b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666ff41  lock dec dword ptr [rsi+0xC]                  
0x666ff45  jne 0x6670071                                 ; -> loc_6670071
0x666ff4b  mov rax,[rsi]                                 
0x666ff4e  mov rax,[rax+8]                               
0x666ff52  mov rcx,rsi                                   
0x666ff55  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666ff5b  jmp 0x6670071                                 ; -> loc_6670071
```

### Gap 36: 0x666ff60..0x666ff97 (shared_ref cleanup)
```
0x666ff60  mov rsi,[rbp+0x5C8]                           
0x666ff67  test rsi,rsi                                  
0x666ff6a  je short 0x666FF97                            ; -> loc_666ff97
0x666ff6c  lock dec dword ptr [rsi+8]                    
0x666ff70  jne short 0x666FF97                           ; -> loc_666ff97
0x666ff72  mov rax,[rsi]                                 
0x666ff75  mov rax,[rax]                                 
0x666ff78  mov rcx,rsi                                   
0x666ff7b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666ff81  lock dec dword ptr [rsi+0xC]                  
0x666ff85  jne short 0x666FF97                           ; -> loc_666ff97
0x666ff87  mov rax,[rsi]                                 
0x666ff8a  mov rax,[rax+8]                               
0x666ff8e  mov rcx,rsi                                   
0x666ff91  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

### Gap 37: 0x666ff97..0x6670032 (buffer free + list cleanup + return)
```
0x666ff97  mov rcx,[rbp+0x5F8]                           
0x666ff9e  test rcx,rcx                                  
0x666ffa1  je short 0x666FFE5                            ; -> loc_666ffe5
0x666ffa3  mov rdx,[rbp+0x608]                           
0x666ffaa  sub rdx,rcx                                   
0x666ffad  cmp rdx,0x1000                                
0x666ffb4  jb short 0x666FFD2                            ; -> loc_666ffd2
0x666ffb6  mov rax,[rcx-8]                               
0x666ffba  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666ffbe  sub rcx,rax                                   
0x666ffc1  cmp rcx,0x20                                  
0x666ffc5  jae 0x6670A7A                                 ; -> loc_6670a7a
0x666ffcb  add rdx,0x27                                  
0x666ffcf  mov rcx,rax                                   

loc_666ffd2:  ; from 666ffb4
0x666ffd2  call 0xE935700                                ; -> sub_e935700
0x666ffd7  xorps xmm0,xmm0                               
0x666ffda  movups [rdi],xmm0                             
0x666ffdd  mov qword ptr [rdi+0x10],0                    

loc_666ffe5:  ; from 666ffa1
0x666ffe5  mov rax,[rbp+0x5E8]                           
0x666ffec  mov rcx,[rax+8]                               
0x666fff0  mov qword ptr [rcx],0                         
0x666fff7  mov rsi,[rax]                                 
0x666fffa  test rsi,rsi                                  
0x666fffd  je short 0x6670021                            ; -> loc_6670021
0x666ffff  nop                                           

loc_6670000:  ; from 667001f
0x6670000  mov rdi,[rsi]                                 
0x6670003  lea rcx,[rsi+0x10]                            
0x6670007  call 0x9B250                                  ; -> sub_9b250
0x667000c  mov edx,0x50                                  
0x6670011  mov rcx,rsi                                   
0x6670014  call 0xE935700                                ; -> sub_e935700
0x6670019  mov rsi,rdi                                   
0x667001c  test rdi,rdi                                  
0x667001f  jne short 0x6670000                           ; -> loc_6670000

loc_6670021:  ; from 666fffd, 6670745, 667076c
0x6670021  mov rcx,[rbp+0x5E8]                           
0x6670028  mov edx,0x50                                  
0x667002d  call 0xE935700                                ; -> sub_e935700
0x6670032  movaps xmm6,[rbp+0x680]                       
0x6670039  movaps xmm7,[rbp+0x690]                       
0x6670040  movaps xmm8,[rbp+0x6A0]                       
0x6670048  add rsp,0x738                                 
0x667004f  pop rbx                                       
0x6670050  pop rdi                                       
0x6670051  pop rsi                                       
0x6670052  pop r12                                       
0x6670054  pop r13                                       
0x6670056  pop r14                                       
0x6670058  pop r15                                       
0x667005a  pop rbp                                       
0x667005b  ret
```

---

### Description fields READ in gap fill (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|

---

### Verification
Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-D7c.md`

---

### Description fields READ in gap fill (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|

---

### Verification
Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-D7c.md`

## FullscreenEffect (Effect tag 7) visitor body reversal
Target: 0x666b5cf, ~3700 instructions (Effect group tag 7 visitor body)
Checklist: D7c in docs/RENDER_CHECKLIST.md
Existing knowledge: docs/functions/effect_descriptions.md (section 8), src/sdk/mc/deps/minecraft_renderer/framebuilder/EffectDescriptions.h (FullscreenEffectDescriptionReads)
BGFX_MAP: 6ee

Known from prior work:
- Clone 0x530A1B0 -> ctor 0x668BF20, tag 7, vslot 0x360
- Visitor head 0x666ae72: `mov rax,[r15+0x78]`, pointee +0x40 must be non-zero, then 0x66B2B30, then 0x666b5cf
- Reads attributed to tag 7 by exclusive control-flow reach: +0x00, +0x08, +0x18/+0x28/+0x38/+0x48 (four vec4), +0x58, +0x5C, +0x64 (vec4), +0x78 (Mesh-like), +0x88 (u16), +0xC8, +0xC9
- Spill slot [rbp+0x668] shared with tags 1 and 6
- Strings: "ALPHA_TEST", "fullscreen_cube_overlay"

Register convention (from effect_descriptions.md):
- r15 = description
- r12 = frame ctx
- rbx = rcx (visitor this)

---

### Chunk 1: 0x666b5cf..0x666bfad (500 instructions)

**Phase 1: 0x666b5cf..0x666b6fd — Entry setup and early exits**
```
0x666b5cf  mov qword ptr [rbp+0x3F8],0                   
0x666b5da  mov qword ptr [rbp+0x400],0xA                 
0x666b5e5  mov qword ptr [rbp+0x408],0xF                 
0x666b5f0  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
0x666b5f7  mov [rbp+0x3F0],rax                           
0x666b5fe  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
0x666b605  mov [rbp+0x3F8],ax                            
0x666b60c  lea rcx,[rdi+0x98]                            
0x666b613  lea rdx,[rbp+0x3F0]                           
0x666b61a  call 0x358C40                                 ; -> sub_358c40
0x666b61f  mov sil,1                                     
0x666b622  cmp rax,[rdi+0x98]                            
0x666b629  jne 0x666D8A2                                 ; -> sub_666d8a2 (exit)
0x666b62f  mov rdi,rbx                                   
0x666b632  mov rax,[r12]                                 
0x666b636  lea rcx,[rax+0x10]                            
0x666b63a  test rax,rax                                  
0x666b63d  lea rsi,[0x1232E708]                          ; [data_1232e708] fallback
0x666b644  cmovne rsi,rcx                                
0x666b648  mov rbx,[rsi+0x18]                            
0x666b64c  cmp rbx,0x17                                  
0x666b650  jae 0x666CF0C                                 ; -> loc_666cf0c (exit)
0x666b656  xor esi,esi                                   
0x666b658  jmp 0x666D89F                                 ; -> sub_666d89f (exit)
```

**Phase 2: 0x666b65d..0x666b6fd — Return from sub_66a6830 (alt Shadow extractor) + loop init**
```
0x666b65d  mov [rsp+0x20],rax                            
0x666b662  mov rcx,r12                                   
0x666b665  mov r8,r15                                    
0x666b668  call 0x66A6830                                ; -> sub_66a6830 (alt Shadow extractor)
0x666b66d  jmp 0x6670032                                 ; -> sub_6670032 (exit)
0x666b672  mov rax,[rax]                                 ; R ret@66a6830+0x0
0x666b675  mov rax,[rax+0x18]                            ; R *(ret@66a6830+0x0)+0x18
0x666b679  mov rdi,[rax]                                 ; R *(*(ret@66a6830+0x0)+0x18)+0x0
0x666b67c  test rdi,rdi                                  
0x666b67f  je 0x666C846                                  ; -> loc_666c846 (loop exit)
0x666b685  mov eax,[0x129FA0F0]                          ; [data_129fa0f0]
0x666b68b  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x666b691  mov rdx,gs:[0x58]                             
0x666b69a  mov rcx,[rdx+rcx*8]                           
0x666b69e  cmp eax,[rcx+4]                               
0x666b6a4  jg 0x6670D60                                  ; -> sub_6670d60 (exit)
0x666b6aa  mov eax,[0x129FA100]                          ; [data_129fa100]
0x666b6b0  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x666b6b6  mov rdx,gs:[0x58]                             
0x666b6bf  mov rcx,[rdx+rcx*8]                           
0x666b6c3  cmp eax,[rcx+4]                               
0x666b6c9  jg 0x6670DD2                                  ; -> sub_6670dd2 (exit)
0x666b6cf  mov rax,[r15+0x10]                            ; desc+0x10 (count)
0x666b6d3  mov r14,[r15+0x18]                            ; desc+0x18 (elements ptr)
0x666b6d7  shl rax,6                                     
0x666b6db  add rax,r14                                   
0x666b6de  mov [rbp+0x660],rax                           
0x666b6e5  xorps xmm6,xmm6                               
0x666b6e8  mov [rbp+0x650],r12                           
0x666b6ef  mov [rbp+0x668],r15                           ; SHARED SPILL SLOT [rbp+0x668] = description
0x666b6f6  mov [rbp+0x648],rbx                           
0x666b6fd  jmp short 0x666B704                           ; -> loc_666b704
```

**Phase 3: 0x666b700..0x666b890 — Element loop (BlitFlipbook-like stride 0x40)**
```
loc_666b700:  ; from 666c7fa, 666c804, 666c81d, 666c833
0x666b700  add r14,0x40                                  ; next element (stride 0x40)

loc_666b704:  ; from 666b6fd
0x666b704  cmp r14,[rbp+0x660]                           ; end of elements?
0x666b70b  je 0x666C846                                  ; -> loc_666c846 (loop exit)
0x666b711  mov rdi,[r12]                                 ; frame ctx
0x666b715  mov rax,[rbp+0x3E0]                           ; shared_ref from earlier?
0x666b71c  movaps [rbp+0x3F0],xmm6                       ; zero
0x666b723  mov rcx,[rax+8]                               ; ctrl block
0x666b727  test rcx,rcx                                  
0x666b72a  je short 0x666B780                            ; -> loc_666b780
0x666b72c  lock inc dword ptr [rcx+8]                    ; inc refcount
0x666b730  mov rsi,[rbp+0x3F8]                           ; old shared_ref
0x666b737  movups xmm0,[rax]                             ; copy shared_ref
0x666b73a  movaps [rbp+0x3F0],xmm0                       ; store new
0x666b741  test rsi,rsi                                  
0x666b744  je short 0x666B795                            ; -> loc_666b795
0x666b746  lock dec dword ptr [rsi+8]                    ; dec old refcount
0x666b74a  jne short 0x666B795                           ; -> loc_666b795
0x666b74c  mov rax,[rsi]                                 
0x666b74f  mov rax,[rax]                                 
0x666b752  mov rcx,rsi                                   
0x666b755  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (destroy)
0x666b75b  lock dec dword ptr [rsi+0xC]                  
0x666b75f  jne short 0x666B795                           ; -> loc_666b795
0x666b761  mov rax,[rsi]                                 
0x666b764  mov rax,[rax+8]                               
0x666b768  mov rcx,rsi                                   
0x666b76b  call qword ptr [0xF99FFA0]                    ; destroy ctrl
0x666b771  jmp short 0x666B795                           ; -> loc_666b795

loc_666b780:  ; from 666b72a
0x666b780  mov rax,[rax]                                 
0x666b783  mov [rbp+0x3F0],rax                           
0x666b78a  mov qword ptr [rbp+0x3F8],0                   

loc_666b795:  ; from 666b744, 666b74a, 666b75f, 666b771
0x666b795  mov rax,[rbp+0x3F0]                           
0x666b79c  mov rax,[rax+0x18]                            
0x666b7a0  mov rax,[rax]                                 
0x666b7a3  mov [rbp+0x340],rax                           
0x666b7aa  mov r8,[rdi]                                  ; rdi = frame ctx
0x666b7ad  mov rdx,[rax+0x170]                           ; +0x170 from mesh-like object
0x666b7b4  lea rcx,[rbp+0x348]                           
0x666b7bb  call 0xE86B370                                ; -> sub_e86b370
0x666b7c0  nop                                           
0x666b7c1  mov [rbp+0x3C0],rdi                           
0x666b7c8  mov rsi,[rbp+0x3F8]                           ; cleanup shared_ref
0x666b7cf  test rsi,rsi                                  
... (similar refcount cleanup to 0x666b7d2..0x666b7ff)
```

**Phase 4: 0x666b800..0x666b890 — Mesh/material lookup (two tables)**
```
0x666b800  mov rax,[rbp+0x388]                           
0x666b807  movzx r8d,word ptr [rbp+0x392]                
0x666b80f  mov ecx,r8d                                   
0x666b812  shl ecx,4                                     
0x666b815  lea rdx,[rcx+rcx*2]                           ; *0x30 stride
0x666b819  mov rcx,rax                                   
0x666b81c  test r8,r8                                    
0x666b81f  je short 0x666B850                            ; -> loc_666b850
0x666b821  mov r8,[0x129FA0E8]                           ; [data_129fa0e8] table 1
0x666b828  mov r9,rdx                                    
0x666b82b  mov rcx,rax                                   
0x666b82e  xchg ax,ax                                    

loc_666b830:  ; from 666b841
0x666b830  mov r10,[rcx]                                 
0x666b833  cmp [r10+0x28],r8                             
0x666b837  je short 0x666B850                            ; -> loc_666b850 (found)
0x666b839  add rcx,0x30                                  
0x666b83d  add r9,0xFFFFFFFFFFFFFFD0                     ; -0x30
0x666b841  jne short 0x666B830                           ; -> loop

loc_666b843  jmp short 0x666B891                           ; -> loc_666b891 (not found)

loc_666b850:  ; from 666b81f, 666b837
0x666b850  add rdx,rax                                   
0x666b853  cmp rcx,rdx                                   
0x666b856  jae short 0x666B891                           ; -> loc_666b891
0x666b858  lea r8,[r14+8]                                ; element+8 = texture ref
0x666b85c  sub ecx,eax                                   
0x666b85e  shr ecx,4                                     
0x666b861  imul eax,ecx,0xFFFFAAAB                       ; /0x30
0x666b867  mov [rbp],ax                                  
0x666b86b  mov byte ptr [rbp+2],1                        
0x666b86f  mov byte ptr [rbp+0x3FC],0                    
0x666b876  mov dword ptr [rsp+0x20],0                    
0x666b87e  lea rcx,[rbp+0x340]                           
0x666b885  mov rdx,rbp                                   
0x666b888  mov r9,r13                                    
0x666b88b  call 0xBCABA00                                ; -> sub_bcaba00 (texture bind setup)
```

**Phase 5: 0x666b891..0x666b941 — Element field reads + second table lookup**
```
loc_666b891:  ; from 666b843, 666b856
0x666b891  movss xmm0,[r14+0x20]                         ; element+0x20 (frame lerp)
0x666b897  movsd xmm1,[r14+0x18]                         ; element+0x18 (frame position)
0x666b89d  movsd [rbp+0x3F0],xmm1                        
0x666b8a5  movss [rbp+0x3F8],xmm0                        
0x666b8ad  mov dword ptr [rbp+0x3FC],0                   
0x666b8b7  mov qword ptr [rbp],1                         
0x666b8bf  mov [rbp+8],r13                               
0x666b8c3  mov rax,[rbp+0x378]                           
0x666b8ca  movzx r8d,word ptr [rbp+0x382]                
0x666b8d2  mov edx,r8d                                   
0x666b8d5  shl edx,4                                     
0x666b8d8  mov rcx,rax                                   
0x666b8db  test r8d,r8d                                  
0x666b8de  je short 0x666B910                            ; -> loc_666b910
0x666b8e0  mov r8,[0x129FA0F8]                           ; [data_129fa0f8] table 2
0x666b8e7  mov r9,rdx                                    
0x666b8ea  mov rcx,rax                                   
0x666b8ed  nop [rax]                                     

loc_666b8f0:  ; from 666b901
0x666b8f0  mov r10,[rcx]                                 
0x666b8f3  cmp [r10+0x28],r8                             
0x666b8f7  je short 0x666B910                            ; -> loc_666b910 (found)
0x666b8f9  add rcx,0x10                                  
0x666b8fd  add r9,0xFFFFFFFFFFFFFFF0                     ; -0x10
0x666b901  jne short 0x666B8F0                           ; -> loop

loc_666b903  jmp short 0x666B942                           ; -> loc_666b942 (not found)

loc_666b910:  ; from 666b8de, 666b8f7
0x666b910  add rdx,rax                                   
0x666b913  cmp rcx,rdx                                   
0x666b916  jae short 0x666B942                           ; -> loc_666b942
0x666b918  sub ecx,eax                                   
0x666b91a  shr ecx,4                                     
0x666b91d  mov [rbp+0x1D0],cx                            
0x666b924  mov byte ptr [rbp+0x1D2],1                    
0x666b92b  lea rcx,[rbp+0x348]                           
0x666b932  lea rdx,[rbp+0x1D0]                           
0x666b939  mov r8,rbp                                    
0x666b93c  call 0x5679DB0                                ; -> sub_5679db0
```

**Phase 6: 0x666b942..0x666ba24 — Mesh draw setup + shared_ref handling (desc+0x08)**
```
loc_666b942:  ; from 666b903, 666b916
0x666b942  mov rsi,[r14]                                 ; element+0x00 = object
0x666b945  mov rax,[rsi+0x60]                            ; +0x60 - +0x58 >> 2 * 0xAAAAAAAB (index count?)
0x666b949  sub rax,[rsi+0x58]                            
0x666b94d  shr rax,2                                     
0x666b951  imul eax,0xAAAAAAAB                           
0x666b957  test eax,eax                                  
0x666b959  je short 0x666B985                            ; -> loc_666b985
0x666b95b  mov rdx,[rbp+0x340]                           
0x666b962  mov eax,0x250                                 
0x666b967  add rdx,rax                                   
0x666b96a  mov rcx,r13                                   
0x666b96d  xor r8d,r8d                                   
0x666b970  call 0xBBD7C70                                ; -> sub_bbd7c70
0x666b975  nop                                           
0x666b976  mov rcx,rsi                                   
0x666b979  mov rdx,r13                                   
0x666b97c  call 0x4DEDD00                                ; -> sub_4dedd00
0x666b981  nop                                           
0x666b982  mov rsi,[r14]                                 

loc_666b985:  ; from 666b959
0x666b985  xor edi,edi                                   
0x666b987  cmp byte ptr [rsi+0x1D4],0                    ; object+0x1D4 flag
0x666b98e  je short 0x666B996                            ; -> loc_666b996
0x666b990  mov edi,[rsi+0x1D0]                           ; object+0x1D0 value -> edi

loc_666b996:  ; from 666b98e
0x666b996  movaps [rbp+0x330],xmm6                       ; zero 4 xmm slots
0x666b99d  movaps [rbp+0x320],xmm6                       
0x666b9a4  movaps [rbp+0x310],xmm6                       
0x666b9ab  movaps [rbp+0x300],xmm6                       
0x666b9b2  mov rax,[r15+8]                               ; desc+0x08 (shared_ref)
0x666b9b6  test rax,rax                                  
0x666b9b9  je short 0x666BA10                            ; -> loc_666ba10
0x666b9bb  lock inc dword ptr [rax+8]                    ; inc refcount
0x666b9bf  mov rsi,[rbp+0x308]                           ; old ref
0x666b9c6  movups xmm0,[r15]                             ; copy desc+0x00..0x0F (shared_ref pair)
0x666b9ca  movaps [rbp+0x300],xmm0                       
0x666b9d1  test rsi,rsi                                  
... (refcount cleanup similar to above, to 0x666ba24)
```

**Phase 7: 0x666ba25..0x666bb2e — Uniform setup + render-state mapper (0x66A0F60)**
```
loc_666ba25:  ; from 666b9d4, 666b9da, 666b9ef, 666ba01
0x666ba25  movups xmm0,[r14+0x24]                        ; element+0x24 (16 bytes)
0x666ba2a  shufps xmm0,xmm0,0x4E                         ; swizzle
0x666ba2e  movaps [rbp+0x320],xmm0                       
0x666ba35  mov dword ptr [rbp+0x5E0],0x3F800000          ; 1.0f
0x666ba3f  lea rax,[rbp+0x5E4]                           
0x666ba46  movups [rax],xmm6                             
0x666ba49  mov dword ptr [rbp+0x5F4],0x3F800000          ; 1.0f
0x666ba53  movups [rax+0x14],xmm6                        
0x666ba57  mov dword ptr [rbp+0x608],0x3F800000          ; 1.0f
0x666ba61  movups [rax+0x28],xmm6                        
0x666ba65  mov dword ptr [rbp+0x61C],0x3F800000          ; 1.0f
0x666ba6f  mov byte ptr [rbp+0x620],0                    
0x666ba76  mov rax,[r14]                                 ; element object
0x666ba79  movaps [rbp-0x20],xmm6                        ; zero temp
0x666ba7d  mov rcx,[rax+0x1B0]                           ; object+0x1B0
0x666ba84  test rcx,rcx                                  
0x666ba87  je short 0x666BA8D                            ; -> loc_666ba8d
0x666ba89  movzx ecx,word ptr [rcx+0x10]                 

loc_666ba8d:  ; from 666ba87
0x666ba8d  mov rcx,[rax+0x1B8]                           ; object+0x1B8
0x666ba94  test rcx,rcx                                  
0x666ba97  je short 0x666BAB0                            ; -> loc_666bab0
0x666ba99  lock inc dword ptr [rcx+8]                    ; inc refcount
0x666ba9d  mov rcx,[rax+0x1B8]                           
0x666baa4  jmp short 0x666BAB2                           ; -> loc_666bab2

loc_666bab0:  ; from 666ba97
0x666bab0  xor ecx,ecx                                   

loc_666bab2:  ; from 666baa4
0x666bab2  mov rax,[rax+0x1B0]                           ; object+0x1B0
0x666bab9  mov [rbp-0x20],rax                            
0x666babd  mov rsi,[rbp-0x18]                            
0x666bac1  mov [rbp-0x18],rcx                            
0x666bac5  test rsi,rsi                                  
... (refcount cleanup to 0x666bb00)

loc_666bb00:  ; from 666bac8, 666bace, 666bae3
0x666bb00  mov r8,[rbx+0x3B8]                            ; visitor+0x3B8
0x666bb07  mov rdx,[r12]                                 ; frame ctx
0x666bb0b  mov [rsp+0x20],edi                            ; saved from object+0x1D0
0x666bb0f  mov dword ptr [rsp+0x30],0                    
0x666bb17  mov dword ptr [rsp+0x28],0                    
0x666bb1f  lea rcx,[rbp+0x2A0]                           ; output
0x666bb26  lea r9,[rbp-0x20]                             ; input (object+0x1B0/0x1B8)
0x666bb2a  call 0x66A0F60                                ; -> sub_66a0f60 (render-state mapper)
```

**Phase 8: 0x666bb30..0x666bcfc — Pass record construction (multiple 0xC8 records)**
```
0x666bb30  mov rax,[rbp+0x340]                           
0x666bb37  mov [rbp],rax                                 
0x666bb3b  lea rcx,[rbp+8]                               
0x666bb3f  lea rdx,[rbp+0x348]                           
0x666bb46  call 0xE869FF0                                ; -> sub_e869ff0
0x666bb4b  nop                                           
0x666bb4c  mov rax,[rbp+0x3C0]                           
0x666bb53  mov [rbp+0x80],rax                            ; record 1 base
0x666bb5a  mov qword ptr [rbp+0x3C0],0                   
0x666bb65  lea rax,[rbp+0x88]                            
0x666bb6c  movups [rax],xmm6                             ; zero
... (builds records at rbp+0x80, rbp+0x470 with shared_refs from rbp+0x308, 0x318, matrices from 0x300/0x310/0x320/0x330)
... conditional logic on [rbp+0x620] (0/1/2) selecting different matrix sources
... jump table at 0x666bcf9 on [rbp+0x2D8] (0..3)
```

**Phase 9: 0x666bcf9..0x666bfad — Jump table on byte [rbp+0x2D8] (4 cases)**
```
0x666bcf9  lea rdx,[0xF2BF500]                           ; [data_f2bf500] jump table
0x666bd00  movsxd rcx,[rdx+rax*4]                        
0x666bd04  add rcx,rdx                                   
0x666bd07  jmp rcx                                       
0x666bd09  mov rcx,[rbp+0x2C8]                           ; case 0
0x666bd10  mov [rbp+0x138],rcx                           
0x666bd17  jmp short 0x666BD71                           
0x666bd19  lea rcx,[rbp+0x2C8]                           ; case 1
0x666bd20  movups xmm0,[rcx]                             
0x666bd23  lea rcx,[rbp+0x88]                            
0x666bd2a  movups [rcx+0xB0],xmm0                        
0x666bd31  jmp short 0x666BD71                           
0x666bd33  lea rcx,[rbp+0x88]                            ; case 2
0x666bd3a  movups [rcx+0xB0],xmm6                        ; zero
0x666bd41  mov rcx,[rbp+0x2D0]                           
0x666bd48  test rcx,rcx                                  
0x666bd4b  je short 0x666BD5A                            
0x666bd4d  lock inc dword ptr [rcx+8]                    
0x666bd51  mov rcx,[rbp+0x2D0]                           
0x666bd58  jmp short 0x666BD5C                           
0x666bd5a  xor ecx,ecx                                   ; case 2 cont
0x666bd5c  mov rdx,[rbp+0x2C8]                           
0x666bd63  mov [rbp+0x138],rdx                           
0x666bd6a  mov [rbp+0x140],rcx                           
0x666bd71  mov [rbp+0x148],al                            

loc_666bd77:  ; from 666bcf7
0x666bd77  lea rdx,[rbp+0x2C8]                           
0x666bd7e  mov rax,[rdx+0x28]                            
0x666bd82  lea rcx,[rbp+0x88]                            
0x666bd89  mov [rcx+0xD8],rax                            
0x666bd90  movups xmm0,[rdx+0x18]                        
0x666bd94  movups [rcx+0xC8],xmm0                        
... (builds more records at rbp+0x470.., jump table at 0x666bf8d on [rbp+0x148])
0x666bf8d  lea rdx,[0xF2BF510]                           ; [data_f2bf510] jump table 2
0x666bf94  movsxd rcx,[rdx+rax*4]                        
0x666bf98  add rcx,rdx                                   
0x666bf9b  jmp rcx                                       
0x666bf9d  mov rcx,[rbp+0x138]                           ; case 0
...
0x666bfad  lea rcx,[rbp+0x88]                            ; case 1 (mid-instruction, chunk boundary)
```

---

### Description fields READ in this chunk (from EffectDescriptions.h FullscreenEffectDescriptionReads + NEW)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x00  | 8    | R      | object pointer, passed to 0x66B2B30, 0xBBD7F70 | 7 | 0x666ae98, 0x666ef56 (prior), this chunk: [r15] copied to [rbp+0x300] at 0x666b9c6 |
| +0x08  | 16   | R      | SharedRefPair (sampler data for 0xBCAB8F0/0xBCABA00) | 7 | 0x666b9b2 `mov rax,[r15+8]`, 0x666b9c6 `movups xmm0,[r15]` |
| +0x10  | 8    | R      | count (element count) | 7 | 0x666b6cf `mov rax,[r15+0x10]` |
| +0x18  | 8    | R      | elements pointer | 7 | 0x666b6d3 `mov r14,[r15+0x18]` |
| +0x78  | 8    | R      | Mesh-like pointer (pointee +0x40 checked) | 7 | 0x666ae72 (prior head), this chunk: via r14 element loop |
| +0x88  | 2    | R      | u16 word | 7 | 0x666f36e (prior), this chunk: not directly read yet |

**NEW fields from element structure (BlitFlipbookElementLayout-like, stride 0x40):**
| Offset (from element base) | Size | Access | Use |
|----------------------------|------|--------|-----|
| +0x00 | 8 | R | object pointer (mesh) |
| +0x08 | 16 | R | SharedRefPair (texture) -> passed to 0xBCABA00 |
| +0x18 | 8 | R | frame position (movsd) |
| +0x20 | 4 | R | frame lerp (movss) |
| +0x24 | 16 | R | 16 bytes -> shufps -> [rbp+0x320] |

**Frame ctx / visitor fields read:**
- [r12] = frame ctx (used throughout)
- [rbx+0x3B8] at 0x666bb00
- [rdi+0x98] at 0x666b622 (early check)
- [r12] at 0x666b632 (frame ctx for fallback)

**Global data reads:**
- 0xF7C86B5 "ALPHA_TEST" string
- 0xF7C86BD word (sub_d005453)
- 0x1232E708 fallback pointer
- 0x129FA0F0, 0x129FA100, 0x128767C8 (thread-local comparands)
- 0x129FA0E8, 0x129FA0F8 (lookup tables)
- 0xF2BF500, 0xF2BF510 (jump tables)

**Callees:**
- 0x358C40 (sub_358c40) - early check
- 0x66A6830 (alt Shadow extractor) - from tag 4 path
- 0xEEA6040 (via 0xF99FFA0) - shared_ref destroy
- 0xE86B370 (sub_e86b370)
- 0xBCABA00 (sub_bcaba00) - texture bind setup
- 0x5679DB0 (sub_5679db0)
- 0xBBD7C70 (sub_bbd7c70)
- 0x4DEDD00 (sub_4dedd00)
- 0x66A0F60 (sub_66a0f60) - render-state mapper
- 0xE869FF0 (sub_e869ff0) - called twice

**Exits from this chunk:**
- 0x666D8A2 (early exit)
- 0x666CF0C (fallback bounds check)
- 0x666D89F (early exit)
- 0x6670032 (after Shadow extractor)
- 0x666C846 (loop exit)
- 0x6670D60, 0x6670DD2 (thread-local checks)
- 0x666C00F (jump table 2 case >3) - continues in next chunk

---

### UNVERIFIED items in this chunk
- [UNVERIFIED: 0x666b60c] What is sub_358c40? (string "ALPHA_TEST" lookup?)
- [UNVERIFIED: 0x666b629] sub_666d8a2 - what exit path?
- [UNVERIFIED: 0x666b650] loc_666cf0c - what exit path?
- [UNVERIFIED: 0x666b658] sub_666d89f - what exit path?
- [UNVERIFIED: 0x666b668] sub_66a6830 - confirmed as alt Shadow extractor, but why called here?
- [UNVERIFIED: 0x666b7bb] sub_e86b370 - purpose?
- [UNVERIFIED: 0x666b88b] sub_bcaba00 - texture bind, but what exactly?
- [UNVERIFIED: 0x666b93c] sub_5679db0 - purpose?
- [UNVERIFIED: 0x666b970] sub_bbd7c70 - purpose?
- [UNVERIFIED: 0x666b97c] sub_4dedd00 - purpose?
- [UNVERIFIED: 0x666bb2a] sub_66a0f60 - render-state mapper, input/output layout?
- [UNVERIFIED: 0x666bb46] sub_e869ff0 - purpose?
- [UNVERIFIED: 0x666bdd6] sub_e869ff0 (second call) - purpose?
- [UNVERIFIED: 0x666bcf9] Jump table 0xF2BF500 - 4 cases, case 3 not shown (ja at 0x666bcf7)
- [UNVERIFIED: 0x666bf8d] Jump table 0xF2BF510 - 4 cases, case 3 not shown (ja at 0x666bf87)
- [UNVERIFIED: 0x666bfad] Chunk boundary mid-instruction - need next chunk

---

---

### Chunk 2: 0x666bfad..0x666dfad (500 instructions)

**Phase 10: 0x666bfad..0x666c00e — Jump table 2 case 1..3 completion + record setup**
```
0x666bfad  lea rcx,[rbp+0x88]                            ; case 1: copy [rbp+0x88+0xB0] -> [rbp+0x478+0xB0]
0x666bfb4  movups xmm0,[rcx+0xB0]                        
0x666bfbb  lea rcx,[rbp+0x478]                           
0x666bfc2  movups [rcx+0xB0],xmm0                        
0x666bfc9  jmp short 0x666C009                           ; -> loc_666c009
0x666bfcb  lea rcx,[rbp+0x478]                            ; case 2: zero [rbp+0x478+0xB0], handle [rbp+0x140] ref
0x666bfd2  movups [rcx+0xB0],xmm6                        
0x666bfd9  mov rcx,[rbp+0x140]                           
0x666bfe0  test rcx,rcx                                  
0x666bfe3  je short 0x666BFF2                            ; -> loc_666bff2
0x666bfe5  lock inc dword ptr [rcx+8]                    
0x666bfe9  mov rcx,[rbp+0x140]                           
0x666bff0  jmp short 0x666BFF4                           ; -> loc_666bff4

loc_666bff2:  ; from 666bfe3
0x666bff2  xor ecx,ecx                                   

loc_666bff4:  ; from 666bff0
0x666bff4  mov rdx,[rbp+0x138]                           
0x666bffb  mov [rbp+0x528],rdx                           
0x666c002  mov [rbp+0x530],rcx                           

loc_666c009:  ; from 666bfc9
0x666c009  mov [rbp+0x538],al                            
0x666c00f  lea rcx,[rbp+0x88]                            
0x666c016  mov rax,[rcx+0xD8]                            
0x666c01d  lea rdx,[rbp+0x478]                           
0x666c024  mov [rdx+0xD8],rax                            
0x666c02b  movups xmm0,[rcx+0xC8]                        
0x666c032  movups [rdx+0xC8],xmm0                        
```

**Phase 11: 0x666c039..0x666c0e7 — Draw record initialization (0x58-byte records at rbx+0x758)**
```
0x666c039  mov dword ptr [rbp+0x560],0                   
0x666c043  mov byte ptr [rbp+0x564],0xF                  
0x666c04a  mov dword ptr [rbp+0x568],0                   
0x666c054  mov word ptr [rbp+0x56C],0                    
0x666c05d  mov byte ptr [rbp+0x56E],2                    
0x666c064  mov dword ptr [rbp+0x570],0                   
0x666c06e  mov byte ptr [rbp+0x574],0                    
0x666c075  movups [rdx+0x100],xmm6                       ; rdx = rbx+0x478 area
0x666c07c  mov eax,[rbp-8]                               
0x666c07f  mov [rdx+0x118],eax                           
0x666c085  mov rax,[rbp-0x10]                            
0x666c089  mov [rdx+0x110],rax                           
0x666c090  mov byte ptr [rbp+0x594],8                    
0x666c097  mov qword ptr [rbp+0x598],0                   
0x666c0a2  mov dword ptr [rbp+0x5A0],0                   
0x666c0ac  mov byte ptr [rbp+0x5A4],8                    
0x666c0b3  movzx eax,byte ptr [rbp+0x5D0]                
0x666c0ba  mov [rdx+0x13D],al                            
0x666c0c0  movups xmm0,[rbp+0x5C0]                       
0x666c0c7  movups [rdx+0x12D],xmm0                       
0x666c0ce  mov byte ptr [rbp+0x5B6],0xFF                 
0x666c0d5  mov rcx,[r12+0x10]                            ; frame ctx +0x10
0x666c0da  mov eax,0x9D0                                 
0x666c0df  add rcx,rax                                   
0x666c0e2  call 0x5ABA5C0                                ; -> sub_5aba5c0 (passLookup / render target)
0x666c0e7  nop                                           
0x666c0e8  mov rbx,rax                                    ; rbx = passLookup result
```

**Phase 12: 0x666c0eb..0x666c1fc — First draw record emit (stride 0x58 at rbx+0x758)**
```
0x666c0eb  movaps [rbp+0x280],xmm6                       ; zero large stack area (0x200..0x290)
0x666c0f2  movaps [rbp+0x270],xmm6                       
... (zeros 0x200..0x290)
0x666c13f  mov qword ptr [rbp+0x290],0                   
0x666c14a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0] global
0x666c151  mov rax,[rcx]                                 
0x666c154  mov rax,[rax+0x10]                            
0x666c158  mov dl,0x4A                                   
0x666c15a  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (shared_ref destroy, tag 0x4A)
0x666c160  nop                                           
0x666c161  mov [rbp+0x670],al                            
0x666c167  mov rdx,[rbx+0x758]                           ; current write ptr
0x666c16e  cmp rdx,[rbx+0x760]                           ; end ptr
0x666c175  je 0x666C200                                  ; -> loc_666c200 (full, slow path)
0x666c17b  lea rcx,[rbp+0x560]                           ; fast path: write 0x58 bytes directly
0x666c182  mov eax,[rcx+0x10]                            
0x666c185  mov [rdx+0x10],eax                           
0x666c188  movups xmm0,[rcx]                             
0x666c18b  movups [rdx],xmm0                             ; +0x00..0x0F
0x666c18e  movzx eax,byte ptr [rbp+0x574]                
0x666c195  mov [rdx+0x14],al                            
0x666c198  movss xmm0,[rbp+0x578]                        
0x666c1a0  movss [rdx+0x18],xmm0                        
0x666c1a5  movss xmm0,[rbp+0x57C]                        
0x666c1ad  movss [rdx+0x1C],xmm0                        
0x666c1b2  movss xmm0,[rbp+0x580]                        
0x666c1ba  movss [rdx+0x20],xmm0                        
0x666c1bf  movss xmm0,[rbp+0x584]                        
0x666c1c7  movss [rdx+0x24],xmm0                        
0x666c1cc  lea rax,[rbp+0x478]                           
0x666c1d3  movups xmm0,[rax+0x110]                       ; matrices from record area
0x666c1da  movups xmm1,[rax+0x120]                       
0x666c1e1  movups xmm2,[rax+0x12F]                       ; unaligned +0x12F
0x666c1e8  movups [rdx+0x28],xmm0                        ; +0x28..0x37
0x666c1ec  movups [rdx+0x38],xmm1                        ; +0x38..0x47
0x666c1f0  movups [rdx+0x47],xmm2                        ; +0x47..0x56 (overlaps)
0x666c1f4  add qword ptr [rbx+0x758],0x58                ; advance write ptr
0x666c1fc  jmp short 0x666C214                           ; -> loc_666c214
```

**Phase 13: 0x666c200..0x666c26c — Slow path / record count + second draw record setup**
```
loc_666c200:  ; from 666c175
0x666c200  lea rcx,[rbx+0x750]                           ; buffer base
0x666c207  lea r8,[rbp+0x560]                            ; source record
0x666c20e  call 0x6760A80                                ; -> sub_6760a80 (grow/flush)
0x666c213  nop                                           

loc_666c214:  ; from 666c1fc
0x666c214  mov rcx,[0x1233E1B0]                          ; shared_ref destroy (tag 0x4A)
0x666c21b  mov rax,[rcx]                                 
0x666c21e  mov rax,[rax+0x10]                            
0x666c222  movzx edx,byte ptr [rbp+0x670]                
0x666c229  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c22f  nop                                           
0x666c230  mov eax,[rbx+0x758]                           ; write ptr
0x666c236  sub eax,[rbx+0x750]                           ; - base
0x666c23c  shr eax,3                                      ; /8
0x666c23f  imul eax,0xFFFF8BA3                           ; *0xFFFF8BA3 (divide by 0x58? 1/0x58 = 0xFFFF8BA3)
0x666c245  dec eax                                       
0x666c247  mov [rbp+0x1FC],ax                            ; record count - 1
0x666c24e  mov rcx,[0x1233E1B0]                          ; shared_ref destroy (tag 0x4A)
0x666c255  mov rax,[rcx]                                 
0x666c258  mov rax,[rax+0x10]                            
0x666c25c  mov dl,0x4A                                   
0x666c25e  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c264  nop                                           
0x666c265  mov edx,eax                                   
0x666c267  mov rax,r12                                   
0x666c26a  mov r12,r14                                   
0x666c26d  mov r14,[rbx+0x878]                           ; second buffer write ptr
0x666c274  cmp r14,[rbx+0x880]                           ; second buffer end
0x666c27b  je short 0x666C2A0                            ; -> loc_666c2a0 (full)
```

**Phase 14: 0x666c27d..0x666c3c3 — Second draw record emit (stride 0x58 at rbx+0x878) + buffer management**
```
0x666c27d  inc r14                                       
0x666c280  mov [rbx+0x878],r14                           ; advance
0x666c287  mov r14,r12                                   
0x666c28a  mov r12,rax                                   
0x666c28d  jmp 0x666C44A                                 ; -> loc_666c44a (skip buffer alloc)

loc_666c2a0:  ; from 666c27b (buffer full, need alloc)
0x666c2a0  mov r15,r14                                   
0x666c2a3  sub r15,[rbx+0x870]                           ; current size
0x666c2aa  mov rcx,0x7FFFFFFFFFFFFFFF                    
0x666c2b4  cmp r15,rcx                                   
0x666c2b7  mov [rbp+0x670],dl                            
0x666c2bd  je 0x6670A94                                  ; -> sub_6670a94 (overflow)
0x666c2c3  lea r8,[r15+1]                                
0x666c2c7  mov r13,r15                                   
0x666c2ca  shr r13,1                                     
0x666c2cd  mov rax,r13                                   
0x666c2d0  xor rax,rcx                                   
0x666c2d3  add r13,r15                                   
0x666c2d6  cmp r13,r8                                    
0x666c2d9  mov [rbp+0x658],r8                            ; new capacity
0x666c2e0  cmovbe r13,r8                                 
0x666c2e4  cmp r15,rax                                   
0x666c2e7  cmova r13,rcx                                 
0x666c2eb  test r13,r13                                  
0x666c2ee  je 0x666C3A9                                  ; -> loc_666c3a9 (zero size)
0x666c2f4  cmp r13,0x1000                                
0x666c2fb  jb short 0x666C349                            ; -> loc_666c349 (small alloc)
0x666c2fd  cmp r13,0xFFFFFFFFFFFFFFD9                    
0x666c301  jae 0x6670C3B                                 ; -> sub_6670c3b (too large)
0x666c307  lea rdi,[r13+0x27]                            ; size + 0x27, align 0x20
0x666c30b  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8] allocator
0x666c312  mov rax,[rcx]                                 
0x666c315  mov rax,[rax+8]                               
0x666c319  mov rdx,rdi                                   
0x666c31c  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (allocate)
0x666c322  nop                                           
0x666c323  mov rsi,rax                                   
0x666c326  test rax,rax                                  
0x666c329  je 0x666C838                                  ; -> loc_666c838 (alloc failed)

loc_666c32f:  ; from 666c841
0x666c32f  mov rax,rsi                                   
0x666c332  add rsi,0x27                                  
0x666c336  and rsi,0xFFFFFFFFFFFFFFE0                    ; align down 0x20
0x666c33a  mov [rsi-8],rax                               
0x666c33e  cmp r14,[rbx+0x878]                           ; check if write ptr moved
0x666c345  jne short 0x666C372                           ; -> loc_666c372 (concurrent mod)
0x666c347  jmp short 0x666C3B4                           ; -> loc_666c3b4

loc_666c349:  ; from 666c2fb (small alloc, stack/inline)
0x666c349  mov rcx,[0x1233E1A8]                          ; allocator
0x666c350  mov rax,[rcx]                                 
0x666c353  mov rax,[rax+8]                               
0x666c357  mov rdx,r13                                   
0x666c35a  call qword ptr [0xF99FFA0]                    ; allocate
0x666c360  nop                                           
0x666c361  mov rsi,rax                                   
0x666c364  test rax,rax                                  
0x666c367  je short 0x666C3A0                            ; -> loc_666c3a0
0x666c369  cmp r14,[rbx+0x878]                           
0x666c370  je short 0x666C3B4                            ; -> loc_666c3b4

loc_666c372:  ; from 666c345, 666c3b2 (concurrent modification retry)
0x666c372  lea rdi,[rsi+r15]                             ; dst = new + old_size
0x666c376  inc rdi                                       
0x666c379  mov rdx,[rbx+0x870]                           ; old base
0x666c380  mov r8,r14                                    
0x666c383  sub r8,rdx                                    
0x666c386  mov rcx,rsi                                   
0x666c389  call 0xEEC6DE0                                ; -> sub_eec6de0 (memmove)
0x666c38e  mov r8,[rbx+0x878]                            ; old write ptr
0x666c395  sub r8,r14                                    
0x666c398  mov rcx,rdi                                   
0x666c39b  mov rdx,r14                                   
0x666c39e  jmp short 0x666C3C4                           ; -> loc_666c3c4

loc_666c3a0:  ; from 666c367 (alloc failed small)
0x666c3a0  mov rcx,r13                                   
0x666c3a3  call 0x9BC830                                 ; -> sub_9bc830
0x666c3a8  nop                                           

loc_666c3a9:  ; from 666c2ee (zero size)
0x666c3a9  xor esi,esi                                   
0x666c3ab  cmp r14,[rbx+0x878]                           
0x666c3b2  jne short 0x666C372                           ; -> loc_666c372

loc_666c3b4:  ; from 666c347, 666c370 (normal path)
0x666c3b4  mov rdx,[rbx+0x870]                           ; old base
0x666c3bb  sub r14,rdx                                   
0x666c3be  mov rcx,rsi                                   
0x666c3c1  mov r8,r14                                    

loc_666c3c4:  ; from 666c39e
0x666c3c4  call 0xEEC6DE0                                ; -> sub_eec6de0 (memmove old to new)
0x666c3c9  mov r15,[rbp+0x668]                           ; RESTORE description from SHARED SPILL SLOT
0x666c3d0  mov rcx,[rbx+0x870]                           ; old base
0x666c3d7  test rcx,rcx                                  
0x666c3da  mov r14,r12                                   
0x666c3dd  je short 0x666C413                            ; -> loc_666c413 (no old buffer)
0x666c3df  mov rdx,[rbx+0x880]                           ; old end
0x666c3e6  sub rdx,rcx                                   
0x666c3e9  cmp rdx,0x1000                                
0x666c3f0  jb short 0x666C40E                            ; -> loc_666c40e (small, free via sub_e935700)
0x666c3f2  mov rax,[rcx-8]                               
0x666c3f6  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666c3fa  sub rcx,rax                                   
0x666c3fd  cmp rcx,0x20                                  
0x666c401  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666c407  add rdx,0x27                                  
0x666c40b  mov rcx,rax                                   

loc_666c40e:  ; from 666c3f0
0x666c40e  call 0xE935700                                ; -> sub_e935700 (free)
```

**Phase 15: 0x666c413..0x666c449 — Install new buffer + third draw record setup**
```
loc_666c413:  ; from 666c3dd
0x666c413  mov [rbx+0x870],rsi                           ; new base
0x666c41a  mov rax,[rbp+0x658]                           ; new capacity
0x666c421  add rax,rsi                                   
0x666c424  mov [rbx+0x878],rax                           ; new write ptr
0x666c42b  add r13,rsi                                   
0x666c42e  mov [rbx+0x880],r13                           ; new end
0x666c435  mov r12,[rbp+0x650]                           ; restore frame ctx
0x666c43c  lea r13,[rbp+0x3F0]                           ; record source
0x666c443  movzx edx,byte ptr [rbp+0x670]                ; shared_ref tag
0x666c44a  mov rcx,[0x1233E1B0]                          ; shared_ref destroy (tag 0x4A)
0x666c451  mov rax,[rcx]                                 
0x666c454  mov rax,[rax+0x10]                            
0x666c458  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c45e  nop                                           
0x666c45f  mov eax,[rbx+0x870]                           ; base
0x666c465  not eax                                       
0x666c467  add eax,[rbx+0x878]                           ; write ptr - base
0x666c46d  mov [rbp+0x1E4],ax                            ; count
0x666c474  lea rcx,[rbx+0x780]                           ; third buffer
0x666c47b  lea rdx,[rbp+0x500]                           ; source (rbp+0x500 area)
0x666c482  call 0x675F3B0                                ; -> sub_675f3b0 (emit to third buffer)
0x666c487  nop                                           
0x666c488  mov qword ptr [rbp+0x1D0],0x5004              ; draw key / flags
0x666c493  mov eax,[rbx+0x788]                           ; third buffer write ptr
0x666c499  sub eax,[rbx+0x780]                           ; - base
0x666c49f  shr eax,3                                     
0x666c4a2  imul eax,0xFFFF8BA3                           ; /0x58
0x666c4a8  dec eax                                       
0x666c4aa  mov [rbp+0x1F8],ax                            ; count
0x666c4b1  mov rcx,[0x1233E1B0]                          ; shared_ref destroy (tag 0x4A)
0x666c4b8  mov rax,[rcx]                                 
0x666c4bb  mov rax,[rax+0x10]                            
0x666c4bf  mov dl,0x4A                                   
0x666c4c1  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c4c7  mov [rbp+0x670],al                            
```

**Phase 16: 0x666c4cd..0x666c5d5 — Fourth + fifth draw records (buffers at rbx+0x648, rbx+0x720)**
```
0x666c4cd  lea rcx,[rbx+0x648]                           ; fourth buffer
0x666c4d4  lea rdx,[rbp+0x4B8]                           ; source
0x666c4db  call 0x675FB30                                ; -> sub_675fb30
0x666c4e0  nop                                           
0x666c4e1  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666c4e8  mov rax,[rcx]                                 
0x666c4eb  mov rax,[rax+0x10]                            
0x666c4ef  movzx edx,byte ptr [rbp+0x670]                
0x666c4f6  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c4fc  nop                                           
0x666c4fd  mov eax,[rbx+0x650]                           ; fourth buffer write ptr
0x666c503  sub eax,[rbx+0x648]                           ; - base
0x666c509  shr eax,3                                     
0x666c50c  imul eax,0xFFFF8E39                           ; /0x70? (different stride)
0x666c512  dec eax                                       
0x666c514  mov [rbp+0x212],ax                            ; count
0x666c51b  lea rcx,[rbx+0x720]                           ; fifth buffer
0x666c522  lea rdx,[rbp+0x478]                           ; source
0x666c529  call 0x67D7410                                ; -> sub_67d7410
0x666c52e  nop                                           
0x666c52f  mov eax,[rbx+0x728]                           ; fifth buffer write ptr
0x666c535  sub eax,[rbx+0x720]                           ; - base
0x666c53b  shr eax,6                                      ; /0x40
0x666c53e  dec eax                                       
0x666c540  mov [rbp+0x200],ax                            ; count
0x666c547  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666c54e  mov rax,[rcx]                                 
0x666c551  mov rax,[rax+0x10]                            
0x666c555  mov dl,0x4A                                   
0x666c557  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c55d  nop                                           
0x666c55e  mov [rbp+0x670],al                            
```

**Phase 17: 0x666c564..0x666c67f — Sixth draw record (buffer at rbx+0x770) + cleanup**
```
0x666c564  mov rsi,[rbx+0x770]                           ; sixth buffer write ptr
0x666c56b  cmp rsi,[rbx+0x778]                           ; end
0x666c572  je short 0x666C5C0                            ; -> loc_666c5c0 (full)
0x666c574  mov rax,[rbp+0x3F0]                           ; fast path
0x666c57b  mov [rsi],rax                                 
0x666c57e  lea rcx,[rsi+8]                               
0x666c582  lea rdx,[rbp+0x3F8]                           
0x666c589  call 0xE869FF0                                ; -> sub_e869ff0
0x666c58e  nop                                           
0x666c58f  mov rax,[rbp+0x470]                           
0x666c596  mov [rsi+0x80],rax                            
0x666c59d  mov qword ptr [rbp+0x470],0                   
0x666c5a8  add qword ptr [rbx+0x770],0x88                ; stride 0x88
0x666c5b3  jmp short 0x666C5D6                           ; -> loc_666c5d6

loc_666c5c0:  ; from 666c572 (full, slow path)
0x666c5c0  mov rcx,rbx                                   
0x666c5c3  add rcx,0x768                                 
0x666c5ca  mov rdx,rsi                                   
0x666c5cd  mov r8,r13                                    
0x666c5d0  call 0x6760710                                ; -> sub_6760710 (grow)
0x666c5d5  nop                                           

loc_666c5d6:  ; from 666c5b3
0x666c5d6  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666c5dd  mov rax,[rcx]                                 
0x666c5e0  mov rax,[rax+0x10]                            
0x666c5e4  movzx edx,byte ptr [rbp+0x670]                
0x666c5eb  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c5f1  nop                                           
0x666c5f2  mov qword ptr [rbp+0x1D0],0x2017004           ; draw key
0x666c5fd  mov eax,[rbx+0x770]                           ; sixth buffer count
0x666c603  sub eax,[rbx+0x768]                           ; - base
0x666c609  shr eax,3                                     
0x666c60c  imul eax,0xFFFFF0F1                           ; /0xC8?
0x666c612  dec eax                                       
0x666c614  mov [rbp+0x1FA],ax                            ; count
0x666c61b  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666c622  mov rax,[rcx]                                 
0x666c625  mov rax,[rax+0x10]                            
0x666c629  mov dl,0x4A                                   
0x666c62b  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c631  nop                                           
0x666c632  mov [rbp+0x670],al                            
0x666c638  mov rdx,[rbx+8]                               ; seventh buffer (rbx+8)
0x666c63c  cmp rdx,[rbx+0x10]                            ; end
0x666c640  je short 0x666C670                            ; -> loc_666c670 (full)
0x666c642  mov r8d,0xC8                                  
0x666c648  mov rcx,rdx                                   
0x666c64b  lea rdx,[rbp+0x1D0]                           
0x666c652  call 0xEEC6EC0                                ; -> sub_eec6ec0 (memcpy)
0x666c657  add qword ptr [rbx+8],0xC8                    ; stride 0xC8
0x666c65f  jmp short 0x666C680                           ; -> loc_666c680

loc_666c670:  ; from 666c640 (full, slow path)
0x666c670  mov rcx,rbx                                   
0x666c673  lea r8,[rbp+0x1D0]                            
0x666c67a  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x666c67f  nop                                           
```

**Phase 18: 0x666c680..0x666c75f — Shared_ref cleanup + loop back to element loop**
```
loc_666c680:  ; from 666c65f
0x666c680  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666c687  mov rax,[rcx]                                 
0x666c68a  mov rax,[rax+0x10]                            
0x666c68e  movzx edx,byte ptr [rbp+0x670]                
0x666c695  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c69b  nop                                           
0x666c69c  mov rcx,r13                                   
0x666c69f  call 0x674A1D0                                ; -> sub_674a1d0
0x666c6a4  mov rcx,rbp                                   
0x666c6a7  call 0x674A1D0                                ; -> sub_674a1d0
0x666c6ac  cmp byte ptr [rbp+0x2D8],3                    ; check jump table index
0x666c6b3  jne short 0x666C6F0                           ; -> loc_666c6f0
0x666c6b5  mov rsi,[rbp+0x2D0]                           ; case 3 had extra ref
0x666c6bc  test rsi,rsi                                  
0x666c6bf  je short 0x666C6F0                            ; -> loc_666c6f0
0x666c6c1  lock dec dword ptr [rsi+8]                    ; cleanup
0x666c6c5  jne short 0x666C6F0                           ; -> loc_666c6f0
0x666c6c7  mov rax,[rsi]                                 
0x666c6ca  mov rax,[rax]                                 
0x666c6cd  mov rcx,rsi                                   
0x666c6d0  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c6d6  lock dec dword ptr [rsi+0xC]                  
0x666c6da  jne short 0x666C6F0                           ; -> loc_666c6f0
0x666c6dc  mov rax,[rsi]                                 
0x666c6df  mov rax,[rax+8]                               
0x666c6e3  mov rcx,rsi                                   
0x666c6e6  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c6ec  nop [rax]                                     

loc_666c6f0:  ; from 666c6b3, 666c6bf, 666c6c5, 666c6da
0x666c6f0  mov rdi,[rbp+0x2A8]                           ; array base
0x666c6f7  test rdi,rdi                                  
0x666c6fa  je short 0x666C760                            ; -> loc_666c760
0x666c6fc  mov rbx,[rbp+0x2B0]                           ; array end
0x666c703  jmp short 0x666C714                           ; -> loc_666c714

loc_666c710:  ; from 666c71d, 666c726, 666c72c, 666c741, 666c753
0x666c710  add rdi,0x28                                  ; stride 0x28

loc_666c714:  ; from 666c703
0x666c714  cmp rdi,rbx                                   
0x666c717  je short 0x666C760                            ; -> loc_666c760
0x666c719  cmp byte ptr [rdi+0x18],2                     ; filter by byte +0x18 == 2
0x666c71d  jne short 0x666C710                           ; -> next
0x666c71f  mov rsi,[rdi+8]                               ; shared_ref at +8
0x666c723  test rsi,rsi                                  
0x666c726  je short 0x666C710                            ; -> next
0x666c728  lock dec dword ptr [rsi+8]                    ; cleanup refs
0x666c72c  jne short 0x666C710                           ; -> next
0x666c72e  mov rax,[rsi]                                 
0x666c731  mov rax,[rax]                                 
0x666c734  mov rcx,rsi                                   
0x666c737  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c73d  lock dec dword ptr [rsi+0xC]                  
0x666c741  jne short 0x666C710                           ; -> next
0x666c743  mov rax,[rsi]                                 
0x666c746  mov rax,[rax+8]                               
0x666c74a  mov rcx,rsi                                   
0x666c74d  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c753  jmp short 0x666C710                           ; -> next
```

**Phase 19: 0x666c760..0x666c845 — Final cleanup + loop back (je 0x666B700)**
```
loc_666c760:  ; from 666c6fa, 666c717
0x666c760  cmp byte ptr [rbp+0x620],1                    ; mode flag
0x666c767  mov rbx,[rbp+0x648]                           ; restore visitor this
0x666c76e  jne short 0x666C7B0                           ; -> loc_666c7b0
0x666c770  mov rcx,[rbp+0x5E0]                           ; buffer base
0x666c777  test rcx,rcx                                  
0x666c77a  je short 0x666C7B0                            ; -> loc_666c7b0
0x666c77c  mov rdx,[rbp+0x5F0]                           ; buffer end
0x666c783  sub rdx,rcx                                   
0x666c786  cmp rdx,0x1000                                
0x666c78d  jb short 0x666C7AB                            ; -> loc_666c7ab
0x666c78f  mov rax,[rcx-8]                               
0x666c793  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666c797  sub rcx,rax                                   
0x666c79a  cmp rcx,0x20                                  
0x666c79e  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666c7a4  or rdx,0x27                                   
0x666c7a8  mov rcx,rax                                   

loc_666c7ab:  ; from 666c78d
0x666c7ab  call 0xE935700                                ; -> sub_e935700 (free)

loc_666c7b0:  ; from 666c76e, 666c77a
0x666c7b0  mov rsi,[rbp+0x318]                           ; shared_ref cleanup
0x666c7b7  test rsi,rsi                                  
0x666c7ba  je short 0x666C7F0                            ; -> loc_666c7f0
0x666c7bc  lock dec dword ptr [rsi+8]                    
0x666c7c0  jne short 0x666C7F0                           ; -> loc_666c7f0
0x666c7c2  mov rax,[rsi]                                 
0x666c7c5  mov rax,[rax]                                 
0x666c7c8  mov rcx,rsi                                   
0x666c7cb  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c7d1  lock dec dword ptr [rsi+0xC]                  
0x666c7d5  jne short 0x666C7F0                           ; -> loc_666c7f0
0x666c7d7  mov rax,[rsi]                                 
0x666c7da  mov rax,[rax+8]                               
0x666c7de  mov rcx,rsi                                   
0x666c7e1  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c7e7  nop [rax+rax]                                 

loc_666c7f0:  ; from 666c7ba, 666c7c0, 666c7d5
0x666c7f0  mov rsi,[rbp+0x308]                           ; shared_ref cleanup (desc+0x08)
0x666c7f7  test rsi,rsi                                  
0x666c7fa  je 0x666B700                                  ; -> LOOP BACK to element loop
0x666c800  lock dec dword ptr [rsi+8]                    
0x666c804  jne 0x666B700                                 ; -> LOOP BACK
0x666c80a  mov rax,[rsi]                                 
0x666c80d  mov rax,[rax]                                 
0x666c810  mov rcx,rsi                                   
0x666c813  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c819  lock dec dword ptr [rsi+0xC]                  
0x666c81d  jne 0x666B700                                 ; -> LOOP BACK
0x666c823  mov rax,[rsi]                                 
0x666c826  mov rax,[rax+8]                               
0x666c82a  mov rcx,rsi                                   
0x666c82d  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666c833  jmp 0x666B700                                 ; -> LOOP BACK
```

**Phase 20: 0x666c838..0x666c90d — Alloc failure paths + next element loop entry**
```
loc_666c838:  ; from 666c329 (large alloc failed)
0x666c838  mov rcx,rdi                                   
0x666c83b  call 0x9BC830                                 ; -> sub_9bc830
0x666c840  nop                                           
0x666c841  jmp 0x666C32F                                 ; -> retry

loc_666c846:  ; from 0x666b70b, 0x666b67f (element loop exit)
0x666c846  mov rsi,[rbp+0x3E8]                           ; shared_ref
0x666c84d  test rsi,rsi                                  
0x666c850  jne 0x666FB88                                 ; -> sub_666fb88
0x666c856  jmp 0x6670032                                 ; -> sub_6670032 (exit)

loc_666c85b:  ; from 0x666FB88 return?
0x666c85b  mov rax,[rsi]                                 
0x666c85e  mov rax,[rax+0x18]                            
0x666c862  mov rbx,[rax]                                 
0x666c865  test rbx,rbx                                  
0x666c868  je 0x666FB78                                  ; -> sub_666fb78
0x666c86e  mov r14,[r12]                                 
0x666c872  mov rax,[rbp+0x630]                           
0x666c879  xorps xmm0,xmm0                               
0x666c87c  movaps [rbp+0x3F0],xmm0                       
0x666c883  mov rcx,[rax+8]                               
0x666c887  test rcx,rcx                                  
0x666c88a  je 0x666CF20                                  ; -> loc_666cf20
0x666c890  lock inc dword ptr [rcx+8]                    
0x666c894  mov rsi,[rbp+0x3F8]                           
0x666c89b  movups xmm0,[rax]                             
0x666c89e  movaps [rbp+0x3F0],xmm0                       
0x666c8a5  test rsi,rsi                                  
0x666c8a8  je 0x666CF35                                  ; -> loc_666cf35
... (shared_ref handling continues)
```

---

### Description fields READ in chunk 2 (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x2D8 | 1    | R      | Jump table index (0..3) for first jump table | 7 | 0x666bcf3 `cmp rax,3`, 0x666c6ac `cmp byte [rbp+0x2D8],3` |
| +0x2C8 | 8    | R      | Pointer used in jump table cases 0/1 | 7 | 0x666bd09, 0x666bd19, 0x666bd7e |
| +0x2D0 | 8    | R      | SharedRef for jump table case 2 | 7 | 0x666bd41, 0x666c6b5 |
| +0x148 | 1    | R      | Jump table index (0..3) for second jump table | 7 | 0x666bf83 `cmp rax,3`, 0x666bd71 `mov [rbp+0x148],al` |
| +0x138 | 8    | R/W    | Pointer from jump table case 0 | 7 | 0x666bd10, 0x666bd63, 0x666bf9d |
| +0x140 | 8    | R/W    | SharedRef from jump table case 2 | 7 | 0x666bd6a, 0x666bfd9 |
| +0x620 | 1    | R      | Mode flag (0/1/2) for matrix selection | 7 | 0x666bc14, 0x666c760 |

**Visitor/frame ctx fields (rbx = visitor this):**
- rbx+0x3B8 at 0x666bb00 (phase 7)
- rbx+8, rbx+0x10 at 0x666c638 (seventh buffer)
- rbx+0x750, rbx+0x758, rbx+0x760 at 0x666c200, 0x666c167 (first draw buffer)
- rbx+0x870, rbx+0x878, rbx+0x880 at 0x666c26d, 0x666c2a3 (second draw buffer)
- rbx+0x780, rbx+0x788 at 0x666c474, 0x666c493 (third draw buffer)
- rbx+0x648, rbx+0x650 at 0x666c4cd, 0x666c4fd (fourth draw buffer)
- rbx+0x720, rbx+0x728 at 0x666c51b, 0x666c52f (fifth draw buffer)
- rbx+0x768, rbx+0x770, rbx+0x778 at 0x666c5c3, 0x666c564 (sixth draw buffer)

**Global data:**
- 0x1233E1B0 (shared_ref destroy vtable, tag 0x4A)
- 0x1233E1A8 (allocator vtable)
- 0xF99FFA0 -> sub_eea6040 (shared_ref destroy)
- 0xF2BF500, 0xF2BF510 (jump tables)

**Callees (new in chunk 2):**
- 0x5ABA5C0 (sub_5aba5c0) - passLookup / render target
- 0xEEA6040 (via 0xF99FFA0) - shared_ref destroy (many calls, tag 0x4A)
- 0x6760A80 (sub_6760a80) - buffer grow/flush
- 0xEEC6DE0 (sub_eec6de0) - memmove
- 0xE935700 (sub_e935700) - free
- 0x9BC830 (sub_9bc830) - alloc failed handler
- 0x675F3B0 (sub_675f3b0) - emit to third buffer
- 0x675FB30 (sub_675fb30) - emit to fourth buffer
- 0x67D7410 (sub_67d7410) - emit to fifth buffer
- 0x6760710 (sub_6760710) - grow sixth buffer
- 0xEEC6EC0 (sub_eec6ec0) - memcpy
- 0x5ABA6D0 (sub_5aba6d0) - slow path seventh buffer
- 0x674A1D0 (sub_674a1d0) - called twice (r13, rbp)
- 0x6670A94, 0x6670C3B, 0x6670A7A - error/overflow handlers
- 0x666FB88, 0x666FB78, 0x666CF20, 0x666CF35, 0x666EEBE - exit paths

**Key insight:** This chunk emits **6 draw records** to 6 different ring buffers in the visitor (rbx), each with different strides (0x58, 0x58, 0x58, 0x70, 0x40, 0x88, 0xC8). The element loop (Phase 3 in chunk 1) iterates BlitFlipbook-like elements (stride 0x40), and for each element, emits a batch of draw records. The loop back at 0x666c7fa/0x666c804/0x666c81d/0x666c833 goes to 0x666B700 (loc_666b700: `add r14,0x40`).

**SHARED SPILL SLOT:** [rbp+0x668] holds the description (r15) across buffer reallocation (0x666c3c9 `mov r15,[rbp+0x668]`), confirming it's shared with tags 1 and 6.

---

### UNVERIFIED items in chunk 2
- [UNVERIFIED: 0x666c0e2] sub_5aba5c0 - passLookup, returns what?
- [UNVERIFIED: 0x666c15a] sub_eea6040 with tag 0x4A - shared_ref destroy, what object?
- [UNVERIFIED: 0x666c20e] sub_6760a80 - buffer grow, signature?
- [UNVERIFIED: 0x666c389] sub_eec6de0 - memmove, signature?
- [UNVERIFIED: 0x666c40e] sub_e935700 - free, signature?
- [UNVERIFIED: 0x666c3a3] sub_9bc830 - alloc failed, signature?
- [UNVERIFIED: 0x666c482] sub_675f3b0 - emit to buffer, signature?
- [UNVERIFIED: 0x666c4db] sub_675fb30 - emit to buffer, signature?
- [UNVERIFIED: 0x666c529] sub_67d7410 - emit to buffer, signature?
- [UNVERIFIED: 0x666c5d0] sub_6760710 - grow buffer, signature?
- [UNVERIFIED: 0x666c652] sub_eec6ec0 - memcpy, signature?
- [UNVERIFIED: 0x666c67a] sub_5aba6d0 - slow path, signature?
- [UNVERIFIED: 0x666c69f] sub_674a1d0 - called twice, purpose?
- [UNVERIFIED: 0x666c7fa] Loop back to 0x666B700 - confirms element loop
- [UNVERIFIED: 0x666c846] Loop exit -> 0x666FB88 / 0x6670032
- [UNVERIFIED: 0x666c85b] Path from 0x666FB88 return
- [UNVERIFIED: 0x666c88a] je 0x666CF20 - next phase

---

### Chunk 3: 0x666c90e..0x666d203 (500 instructions)

**Phase 21: 0x666c90e..0x666ca20 — Thread-local checks + alloc + buffer init (rsi+0x330)**
```
0x666c90e  mov rcx,[rdx+rcx*8]                           ; thread-local check 3
0x666c912  cmp eax,[rcx+4]                               
0x666c918  jg 0x6670E44                                  ; -> sub_6670e44
0x666c91e  mov eax,[0x129FA160]                          ; [data_129fa160]
0x666c924  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x666c92a  mov rdx,gs:[0x58]                             
0x666c933  mov rcx,[rdx+rcx*8]                           
0x666c937  cmp eax,[rcx+4]                               
0x666c93d  jg 0x6670EB6                                  ; -> sub_6670eb6
0x666c943  mov eax,[0x129FA170]                          ; [data_129fa170]
0x666c949  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x666c94f  mov rdx,gs:[0x58]                             
0x666c958  mov rcx,[rdx+rcx*8]                           
0x666c95c  cmp eax,[rcx+4]                               
0x666c962  jg 0x6670F28                                  ; -> sub_6670f28
0x666c968  mov [rbp+0x668],r15                           ; SHARED SPILL SLOT restore description
0x666c96f  mov edi,[r15+0x84]                            ; desc+0x84 (u32)
0x666c976  mov r15,[r12]                                 ; r15 = frame ctx (r12)
0x666c97a  mov rax,[rbp+0x5C0]                           ; shared_ref
0x666c981  xorps xmm0,xmm0                               
0x666c984  movaps [rbp+0x3F0],xmm0                       
0x666c98b  mov rcx,[rax+8]                               ; ctrl
0x666c98f  test rcx,rcx                                  
0x666c992  mov [rbp+0x648],rbx                           ; save visitor this
0x666c999  je 0x666D254                                  ; -> loc_666d254
0x666c99f  lock inc dword ptr [rcx+8]                    ; inc ref
... (refcount handling to 0x666ca0c)
0x666ca0c  nop                                           
0x666ca0d  mov r14,rax                                   ; r14 = allocated buffer
0x666ca10  test rax,rax                                  
0x666ca13  jne short 0x666CA21                           ; -> loc_666ca21
0x666ca15  mov rcx,r15                                   ; frame ctx
0x666ca18  call 0x9BC830                                 ; -> sub_9bc830 (alloc fail)
0x666ca1d  nop                                           
0x666ca1e  xor r14d,r14d                                 
```

**Phase 22: 0x666ca21..0x666cb02 — Buffer write (stride 0x14) + memmove + shared_ref destroy (tag 0x4A)**
```
loc_666ca21:  ; from 666ca13
0x666ca21  mov [r14+rbx],r13b                            ; write byte
0x666ca25  movups [r14+rbx+4],xmm6                       ; zero 16 bytes
0x666ca2b  cmp rdi,[rsi+0x338]                           ; compare write ptr
0x666ca32  je short 0x666CA62                            ; -> loc_666ca62
0x666ca34  add rbx,r14                                   ; dst = base + offset
0x666ca37  add rbx,0x14                                  ; +0x14 stride
0x666ca3b  mov rdx,[rsi+0x330]                           ; old base
0x666ca42  mov r8,rdi                                    ; old write ptr
0x666ca45  sub r8,rdx                                    ; old size
0x666ca48  mov rcx,r14                                   ; new base
0x666ca4b  call 0xEEC6DE0                                ; -> sub_eec6de0 (memmove)
0x666ca50  mov r8,[rsi+0x338]                            ; old write ptr
0x666ca57  sub r8,rdi                                    ; remaining
0x666ca5a  mov rcx,rbx                                   ; dst
0x666ca5d  mov rdx,rdi                                   ; src
0x666ca60  jmp short 0x666CA72                           ; -> loc_666ca72

loc_666ca62:  ; from 666ca32
0x666ca62  mov rdx,[rsi+0x330]                           ; old base
0x666ca69  sub rdi,rdx                                   ; offset
0x666ca6c  mov rcx,r14                                   ; new base
0x666ca6f  mov r8,rdi                                    ; size

loc_666ca72:  ; from 666ca60
0x666ca72  call 0xEEC6DE0                                ; -> sub_eec6de0 (memmove)
0x666ca77  mov rcx,[rsi+0x330]                           ; old base
0x666ca7e  test rcx,rcx                                  
0x666ca81  je short 0x666CAB7                            ; -> loc_666cab7
0x666ca83  mov rdx,[rsi+0x340]                           ; old end
0x666ca8a  sub rdx,rcx                                   ; old capacity
0x666ca8d  cmp rdx,0x1000                               
0x666ca94  jb short 0x666CAB2                            ; -> loc_666cab2
0x666ca96  mov rax,[rcx-8]                               ; alloc header
0x666ca9a  add rcx,0xFFFFFFFFFFFFFFF8                    ; align
0x666ca9e  sub rcx,rax                                   
0x666caa1  cmp rcx,0x20                                  
0x666caa5  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666caab  add rdx,0x27                                  
0x666caaf  mov rcx,rax                                   

loc_666cab2:  ; from 666ca94
0x666cab2  call 0xE935700                                ; -> sub_e935700 (free old)

loc_666cab7:  ; from 666ca81
0x666cab7  mov [rsi+0x330],r14                           ; new base
0x666cabe  mov rax,[rbp+0x648]                           ; visitor this
0x666cac5  lea rax,[rax+rax*4]                           ; *5
0x666cac9  lea rax,[r14+rax*4]                           ; new write ptr = base + visitor*5*4?
0x666cacd  mov [rsi+0x338],rax                           ; new write ptr
0x666cad4  lea rax,[r12+r12*4]                           ; *5 (frame ctx)
0x666cad8  lea rax,[r14+rax*4]                           ; new end = base + ctx*5*4?
0x666cadc  mov [rsi+0x340],rax                           ; new end
0x666cae3  movzx r8d,byte ptr [rbp+0x670]                ; shared_ref tag
0x666caeb  mov rcx,[0x1233E1B0]                          ; shared_ref destroy vtable
0x666caf2  mov rax,[rcx]                                 
0x666caf5  mov rax,[rax+0x10]                            
0x666caf9  mov edx,r8d                                   
0x666cafc  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (tag 0x4A)
0x666cb02  nop                                           
```

**Phase 23: 0x666cb03..0x666cbab — Draw record emit (stride 0xC8 at rsi+8) + exit**
```
0x666cb03  mov rax,0x400000000000000                     ; constant
0x666cb0d  mov [rbp+0x3F0],rax                           
0x666cb14  mov eax,[rsi+0x338]                           ; write ptr
0x666cb1a  sub eax,[rsi+0x330]                           ; - base
0x666cb20  shr eax,2                                     ; /4
0x666cb23  imul eax,0xFFFFCCCD                           ; /0x14 (stride)
0x666cb29  dec eax                                       
0x666cb2b  mov [rbp+0x474],ax                            ; count
0x666cb32  mov rcx,[0x1233E1B0]                          ; shared_ref destroy (tag 0x4A)
0x666cb39  mov rax,[rcx]                                 
0x666cb3c  mov rax,[rax+0x10]                            
0x666cb40  mov dl,0x4A                                   
0x666cb42  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666cb48  mov [rbp+0x670],al                            
0x666cb4e  mov rax,[rsi+8]                               ; draw buffer write ptr
0x666cb52  cmp rax,[rsi+0x10]                            ; end
0x666cb56  je short 0x666CB77                            ; -> loc_666cb77 (full)
0x666cb58  lea rdx,[rbp+0x3F0]                           ; fast path: write 0xC8 bytes
0x666cb5f  mov r8d,0xC8                                  
0x666cb65  mov rcx,rax                                   
0x666cb68  call 0xEEC6EC0                                ; -> sub_eec6ec0 (memcpy)
0x666cb6d  add qword ptr [rsi+8],0xC8                    ; advance (stride 0xC8)
0x666cb75  jmp short 0x666CB8A                           ; -> loc_666cb8a

loc_666cb77:  ; from 666cb56
0x666cb77  lea r8,[rbp+0x3F0]                            ; slow path
0x666cb7e  mov rcx,rsi                                   
0x666cb81  mov rdx,rax                                   
0x666cb84  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x666cb89  nop                                           

loc_666cb8a:  ; from 666cb75
0x666cb8a  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666cb91  mov rax,[rcx]                                 
0x666cb94  mov rax,[rax+0x10]                            
0x666cb98  movzx edx,byte ptr [rbp+0x670]                
0x666cb9f  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666cba5  nop                                           
0x666cba6  jmp 0x6670032                                 ; -> sub_6670032 (EXIT)
```

**Phase 24: 0x666cbab..0x666ce2b — Second buffer alloc (rsi+0x78) + memmove/copy loop (stride 0x58)**
```
0x666cbab  mov rcx,[0x1233E1A8]                          ; allocator
0x666cbb2  mov rax,[rcx]                                 
0x666cbb5  mov rax,[rax+8]                               
0x666cbb9  mov rdx,r12                                   ; frame ctx
0x666cbbc  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc)
0x666cbc2  nop                                           
0x666cbc3  mov r14,rax                                   ; new buffer
0x666cbc6  test rax,rax                                  
0x666cbc9  jne short 0x666CBD7                           ; -> loc_666cbd7
0x666cbcb  mov rcx,r12                                   ; frame ctx
0x666cbce  call 0x9BC830                                 ; -> sub_9bc830 (alloc fail)
0x666cbd3  nop                                           
0x666cbd4  xor r14d,r14d                                 

loc_666cbd7:  ; from 666cbc9
0x666cbd7  lea rax,[r14+r13]                             ; dst = new + r13
0x666cbdb  xorps xmm0,xmm0                               
0x666cbde  movups [r14+r13],xmm0                         ; zero
0x666cbe3  mov rcx,[rbx+8]                               ; visitor+8 shared_ref
0x666cbe7  test rcx,rcx                                  
0x666cbea  je short 0x666CBF0                            ; -> loc_666cbf0
0x666cbec  lock inc dword ptr [rcx+8]                    ; inc ref

loc_666cbf0:  ; from 666cbea
0x666cbf0  mov rcx,[rbx]                                 ; visitor base
0x666cbf3  mov [rax],rcx                                 ; copy visitor fields to new buffer
0x666cbf6  mov rcx,[rbx+8]                               
0x666cbfa  mov [rax+8],rcx                               
0x666cc02  mov [rax+0x50],rcx                            
0x666cc06  movups xmm0,[rbx+0x10]                        ; copy 4 xmm registers (matrices)
0x666cc0a  movups xmm1,[rbx+0x20]                        
0x666cc0e  movups xmm2,[rbx+0x30]                        
0x666cc12  movups xmm3,[rbx+0x40]                        
0x666cc16  movups [rax+0x40],xmm3                        
0x666cc1a  movups [rax+0x30],xmm2                        
0x666cc1e  movups [rax+0x20],xmm1                        
0x666cc22  movups [rax+0x10],xmm0                        
0x666cc26  mov rdi,[rsi+0x78]                            ; old buffer base
0x666cc2a  mov rax,[rsi+0x80]                            ; old buffer write ptr
0x666cc31  cmp r15,rax                                   ; r15 = old end?
0x666cc34  je 0x666CD29                                  ; -> loc_666cd29
0x666cc3a  cmp rdi,r15                                   ; old base == old end?
0x666cc3d  je short 0x666CCAC                            ; -> loc_666ccac
0x666cc3f  xorps xmm0,xmm0                               
0x666cc42  mov rax,r14                                   ; dst = new buffer
0x666cc45  jmp short 0x666CC93                           ; -> loc_666cc93

loc_666cc50:  ; from 666cc9d, 666cca3 (copy loop stride 0x58)
0x666cc50  mov rcx,[rdi]                                 
0x666cc53  mov [rax],rcx                                 
0x666cc56  mov rcx,[rdi+8]                               
0x666cc5a  mov [rax+8],rcx                        
0x666cc62  movups xmm2,[rdi+0x20]                        
0x666cc66  movups xmm3,[rdi+0x30]                        
0x666cc6a  movups xmm4,[rdi+0x40]                        
0x666cc6e  movups [rax+0x10],xmm1                        
0x666cc72  movups [rax+0x20],xmm2                        
0x666cc76  movups [rax+0x30],xmm3                        
0x666cc7a  movups [rax+0x40],xmm4                        
0x666cc7e  mov rcx,[rdi+0x50]                            
0x666cc82  mov [rax+0x50],rcx                            
0x666cc86  add rax,0x58                                  ; stride 0x58
0x666cc8a  add rdi,0x58                                 
0x666cc8e  cmp rdi,r15                                   ; until src == old end
0x666cc91  je short 0x666CCA5                            ; -> loc_666cca5

loc_666cc93:  ; from 666cc45
0x666cc93  movups [rax],xmm0                             ; zero first 16 bytes
0x666cc96  mov rcx,[rdi+8]                               ; shared_ref at +8
0x666cc9a  test rcx,rcx                                  
0x666cc9d  je short 0x666CC50                            ; -> copy loop
0x666cc9f  lock inc dword ptr [rcx+8]                    ; inc ref for each element
0x666cca3  jmp short 0x666CC50                           ; -> copy loop
```

**Phase 25: 0x666cca5..0x666cd98 — Copy loop completion + shared_ref cleanup (stride 0x58)**
```
loc_666cca5:  ; from 666cc91
0x666cca5  mov rax,[rsi+0x80]                            ; old write ptr

loc_666ccac:  ; from 666cc3d
0x666ccac  cmp r15,rax                                   ; old end == old write ptr?
0x666ccaf  je 0x666CD95                                  ; -> loc_666cd95
0x666ccb5  lea rcx,[r14+r13]                             ; dst = new + r13
0x666ccb9  add rcx,0x58                                  ; +0x58
0x666ccbd  xorps xmm0,xmm0                               
0x666ccc0  jmp short 0x666CD17                           ; -> loc_666cd17

loc_666ccd0:  ; from 666cd21, 666cd27 (copy from r15)
0x666ccd0  mov rdx,[r15]                                 ; src = r15
0x666ccd3  mov [rcx],rdx                                 
0x666ccd6  mov rdx,[r15+8]                               
0x666ccda  mov [rcx+8],rdx                               
0x666ccde  movups xmm1,[r15+0x10]                        ; copy 4 matrices
0x666cce3  movups xmm2,[r15+0x20]                        
0x666cce8  movups xmm3,[r15+0x30]                        
0x666cced  movups xmm4,[r15+0x40]                        
0x666ccf2  movups [rcx+0x10],xmm1                        
0x666ccf6  movups [rcx+0x20],xmm2                        
0x666ccfa  movups [rcx+0x30],xmm3                        
0x666ccfe  movups [rcx+0x40],xmm4                        
0x666cd02  mov rdx,[r15+0x50]                            
0x666cd06  mov [rcx+0x50],rdx                            
0x666cd0a  add r15,0x58                                  ; stride 0x58
0x666cd0e  add rcx,0x58                                 
0x666cd12  cmp r15,rax                                   ; until r15 == old write ptr
0x666cd15  je short 0x666CD95                            ; -> loc_666cd95

loc_666cd17:  ; from 666ccc0
0x666cd17  movups [rcx],xmm0                             ; zero
0x666cd1a  mov rdx,[r15+8]                               ; shared_ref
0x666cd1e  test rdx,rdx                                  
0x666cd21  je short 0x666CCD0                            ; -> copy loop
0x666cd23  lock inc dword ptr [rdx+8]                    ; inc ref
0x666cd27  jmp short 0x666CCD0                           ; -> copy loop

loc_666cd29:  ; from 666cc34 (old base == old write ptr, empty)
0x666cd29  cmp rdi,r15                                   ; old base == old end?
0x666cd2c  je short 0x666CD99                            ; -> loc_666cd99
0x666cd2e  xorps xmm0,xmm0                               
0x666cd31  mov rax,r14                                   ; dst = new
0x666cd34  jmp short 0x666CD83                           ; -> loc_666cd83

loc_666cd40:  ; from 666cd8d, 666cd93 (copy loop from old base)
0x666cd40  mov rcx,[rdi]                                 
0x666cd43  mov [rax],rcx                                 
0x666cd46  mov rcx,[rdi+8]                               
0x666cd4a  mov [rax+8],rcx                        
0x666cd52  movups xmm2,[rdi+0x20]                        
0x666cd56  movups xmm3,[rdi+0x30]                        
0x666cd5a  movups xmm4,[rdi+0x40]                        
0x666cd5e  movups [rax+0x10],xmm1                        
0x666cd62  movups [rax+0x20],xmm2                        
0x666cd66  movups [rax+0x30],xmm3                        
0x666cd6a  movups [rax+0x40],xmm4                        
0x666cd6e  mov rcx,[rdi+0x50]                            
0x666cd72  mov [rax+0x50],rcx                            
0x666cd76  add rax,0x58                                 
0x666cd7a  add rdi,0x58                                 
0x666cd7e  cmp rdi,r15                                   ; until src == old end
0x666cd81  je short 0x666CD95                            ; -> loc_666cd95

loc_666cd83:  ; from 666cd34
0x666cd83  movups [rax],xmm0                             ; zero
0x666cd86  mov rcx,[rdi+8]                               ; shared_ref
0x666cd8a  test rcx,rcx                                  
0x666cd8d  je short 0x666CD40                            ; -> copy loop
0x666cd8f  lock inc dword ptr [rcx+8]                    ; inc ref
0x666cd93  jmp short 0x666CD40                           ; -> copy loop
```

**Phase 26: 0x666cd95..0x666ceeb — Old buffer cleanup + new buffer install + draw record emit**
```
loc_666cd95:  ; from 666ccaf, 666cd15, 666cd81
0x666cd95  mov rdi,[rsi+0x78]                            ; old base

loc_666cd99:  ; from 666cd2c
0x666cd99  test rdi,rdi                                  
0x666cd9c  je 0x666CE2C                                  ; -> loc_666ce2c
0x666cda2  mov r13,[rsi+0x80]                            ; old write ptr
0x666cda9  cmp rdi,r13                                   ; base == write ptr?
0x666cdac  jne short 0x666CDB9                           ; -> loc_666cdb9
0x666cdae  jmp short 0x666CDF5                           ; -> loc_666cdf5

loc_666cdb0:  ; from 666cdc0, 666cdc7, 666cddd, 666cdef (cleanup loop stride 0x58)
0x666cdb0  add rdi,0x58                                 
0x666cdb4  cmp rdi,r13                                   ; until base == write ptr
0x666cdb7  je short 0x666CDF1                            ; -> loc_666cdf1

loc_666cdb9:  ; from 666cdac
0x666cdb9  mov r15,[rdi+8]                               ; shared_ref at +8
0x666cdbd  test r15,r15                                  
0x666cdc0  je short 0x666CDB0                            ; -> next
0x666cdc2  lock dec dword ptr [r15+8]                    ; dec ref
0x666cdc7  jne short 0x666CDB0                           ; -> next
0x666cdc9  mov rax,[r15]                                 
0x666cdcc  mov rax,[rax]                                 
0x666cdcf  mov rcx,r15                                   
0x666cdd2  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (destroy)
0x666cdd8  lock dec dword ptr [r15+0xC]                  
0x666cddd  jne short 0x666CDB0                           ; -> next
0x666cddf  mov rax,[r15]                                 
0x666cde2  mov rax,[rax+8]                               
0x666cde6  mov rcx,r15                                   
0x666cde9  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (destroy ctrl)
0x666cdef  jmp short 0x666CDB0                           ; -> next

loc_666cdf1:  ; from 666cdb7
0x666cdf1  mov rdi,[rsi+0x78]                            ; old base

loc_666cdf5:  ; from 666cdae
0x666cdf5  mov rdx,[rsi+0x88]                            ; old end
0x666cdfc  sub rdx,rdi                                   ; old capacity
0x666cdff  cmp rdx,0x1000                               
0x666ce06  jb short 0x666CE24                            ; -> loc_666ce24
0x666ce08  mov rax,[rdi-8]                               ; alloc header
0x666ce0c  add rdi,0xFFFFFFFFFFFFFFF8                    ; align
0x666ce10  sub rdi,rax                                   
0x666ce13  cmp rdi,0x20                                  
0x666ce17  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666ce1d  add rdx,0x27                                  
0x666ce21  mov rdi,rax                                   

loc_666ce24:  ; from 666ce06
0x666ce24  mov rcx,rdi                                   
0x666ce27  call 0xE935700                                ; -> sub_e935700 (free old)

loc_666ce2c:  ; from 666cd9c (no old buffer)
0x666ce2c  mov [rsi+0x78],r14                            ; new base
0x666ce30  imul rax,[rbp+0x648],0x58                     ; visitor * 0x58
0x666ce38  add rax,r14                                   ; new write ptr
0x666ce3b  mov [rsi+0x80],rax                            ; write ptr
0x666ce42  add r12,r14                                   ; frame ctx + new base
0x666ce45  mov [rsi+0x88],r12                            ; new end
0x666ce4c  mov edi,0x800000                              ; constant
0x666ce51  movzx r9d,byte ptr [rbp+0x670]                ; shared_ref tag
0x666ce59  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666ce60  mov rax,[rcx]                                 
0x666ce63  mov rax,[rax+0x10]                            
0x666ce67  mov edx,r9d                                   
0x666ce6a  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (tag 0x4A)
0x666ce70  nop                                           
0x666ce71  mov [rbp+0x3F8],rdi                           ; save old write ptr?
0x666ce78  mov eax,[rsi+0x80]                            ; write ptr
0x666ce7e  sub eax,[rsi+0x78]                            ; - base
0x666ce81  shr eax,3                                     ; /8
0x666ce84  imul eax,0xFFFF8BA3                           ; /0x58
0x666ce8a  dec eax                                       
0x666ce8c  mov [rbp+0x4AE],ax                            ; count
0x666ce93  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666ce9a  mov rax,[rcx]                                 
0x666ce9d  mov rax,[rax+0x10]                            
0x666cea1  mov dl,0x4A                                   
0x666cea3  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666cea9  mov [rbp+0x670],al                            
0x666ceaf  mov rax,[rsi+8]                               ; draw buffer write ptr
0x666ceb3  cmp rax,[rsi+0x10]                            ; end
0x666ceb7  je short 0x666CED8                            ; -> loc_666ced8 (full)
0x666ceb9  lea rdx,[rbp+0x3F0]                           ; fast path
0x666cec0  mov r8d,0xC8                                  
0x666cec6  mov rcx,rax                                   
0x666cec9  call 0xEEC6EC0                                ; -> sub_eec6ec0 (memcpy 0xC8)
0x666cece  add qword ptr [rsi+8],0xC8                    ; advance (stride 0xC8)
0x666ced6  jmp short 0x666CEEB                           ; -> loc_666ceeb

loc_666ced8:  ; from 666ceb7
0x666ced8  lea r8,[rbp+0x3F0]                            ; slow path
0x666cedf  mov rcx,rsi                                   
0x666cee2  mov rdx,rax                                   
0x666cee5  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x666ceea  nop                                           

loc_666ceeb:  ; from 666ced6
0x666ceeb  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666cef2  mov rax,[rcx]                                 
0x666cef5  mov rax,[rax+0x10]                            
0x666cef9  movzx edx,byte ptr [rbp+0x670]                
0x666cf00  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666cf06  nop                                           
0x666cf07  jmp 0x6670032                                 ; -> sub_6670032 (EXIT)
```

**Phase 27: 0x666cf0c..0x666d203 — Alternate path (rsi+0x20 check) + sub_e86b370 + record setup**
```
0x666cf0c  cmp qword ptr [rsi+0x20],0x10                 ; check capacity
0x666cf11  jb 0x666D86C                                  ; -> loc_666d86c
0x666cf17  mov rsi,[rsi+8]                               ; shared_ref
0x666cf1b  jmp 0x666D870                                 ; -> loc_666d870

loc_666cf20:  ; from 0x666c88a (je 0x666CF20)
0x666cf20  mov rax,[rax]                                 
0x666cf23  mov [rbp+0x3F0],rax                           
0x666cf2a  mov qword ptr [rbp+0x3F8],0                   
0x666cf35  mov rax,[rbp+0x3F0]                           
0x666cf3c  mov rax,[rax+0x18]                            
0x666cf40  mov rax,[rax]                                 
0x666cf43  mov [rbp+0x1D0],rax                           
0x666cf4a  lea rbx,[rbp+0x1D8]                           
0x666cf51  mov r8,[r14]                                  ; r14 = element object
0x666cf54  mov rdx,[rax+0x170]                           ; +0x170 from mesh
0x666cf5b  mov rcx,rbx                                   
0x666cf5e  call 0xE86B370                                ; -> sub_e86b370
0x666cf63  nop                                           
0x666cf64  mov [rbp+0x250],r14                           
0x666cf6b  mov rsi,[rbp+0x3F8]                           ; shared_ref cleanup
... (refcount cleanup to 0x666cfa2)

loc_666cfa2:  ; from 666cf75, 666cf7b, 666cf90
0x666cfa2  mov r9,[r15]                                  ; r15 = frame ctx
0x666cfa5  lea rcx,[rbp+0x340]                           
0x666cfac  lea r8,[rbp+0x1D0]                            
0x666cfb3  mov rdx,r12                                   
0x666cfb6  call 0xBBD7F70                                ; -> sub_bbd7f70
0x666cfbb  nop                                           
0x666cfbc  mov eax,[0x129FA128]                          ; thread-local check
0x666cfc2  mov ecx,[0x128767C8]                          
0x666cfc8  mov rdx,gs:[0x58]                             
0x666cfd1  mov rcx,[rdx+rcx*8]                           
0x666cfd5  cmp eax,[rcx+4]                               
0x666cfdb  jg 0x6670FE9                                  ; -> sub_6670fe9
0x666cfe1  movss xmm0,[r15+8]                            ; frame ctx+8 float
0x666cfe7  mov qword ptr [rbp+0x3F0],0                   
0x666cff2  mov dword ptr [rbp+0x3F8],0                   
0x666cffc  movss [rbp+0x3FC],xmm0                        
0x666d004  mov qword ptr [rbp],1                         
0x666d00c  mov [rbp+8],rdi                               
0x666d010  mov rax,[rbp+0x208]                           
0x666d017  movzx r8d,word ptr [rbp+0x212]                
0x666d01f  mov edx,r8d                                   
0x666d022  shl edx,4                                     
0x666d025  mov rcx,rax                                   
0x666d028  test r8d,r8d                                  
0x666d02b  je short 0x666D055                            ; -> loc_666d055
0x666d02d  mov r8,[0x129FA120]                           ; lookup table
0x666d034  mov r9,rdx                                    
0x666d037  mov rcx,rax                                   
0x666d03a  nop [rax+rax]                                 

loc_666d040:  ; from 666d051
0x666d040  mov r10,[rcx]                                 
0x666d043  cmp [r10+0x28],r8                             
0x666d047  je short 0x666D055                            ; -> loc_666d055
0x666d049  add rcx,0x10                                  
0x666d04d  add r9,0xFFFFFFFFFFFFFFF0                     ; -0x10
0x666d051  jne short 0x666D040                           ; -> loop

loc_666d053  jmp short 0x666D083                           ; -> loc_666d083

loc_666d055:  ; from 666d02b, 666d047
0x666d055  add rdx,rax                                   
0x666d058  cmp rcx,rdx                                   
0x666d05b  jae short 0x666D083                           ; -> loc_666d083
0x666d05d  sub ecx,eax                                   
0x666d05f  shr ecx,4                                     
0x666d062  mov [rbp+0x2A0],cx                            
0x666d069  mov byte ptr [rbp+0x2A2],1                    
0x666d070  lea rdx,[rbp+0x2A0]                           
0x666d077  mov r8,rbp                                    
0x666d07a  mov rcx,rbx                                   
0x666d07d  call 0x5679DB0                                ; -> sub_5679db0
0x666d082  nop                                           

loc_666d083:  ; from 666d053, 666d05b
0x666d083  cmp byte ptr [rbp+0x398],1                    ; flag check
0x666d08a  jne 0x666FB78                                 ; -> sub_666fb78
0x666d090  movups xmm0,[r15+0xC]                         ; frame ctx +0xC..+0x1B (mat4)
0x666d095  movaps [rbp+0x2A0],xmm0                       
0x666d09c  movups xmm1,[r15+0x1C]                        
0x666d0a1  movaps [rbp+0x2B0],xmm1                       
0x666d0a8  movups xmm2,[r15+0x2C]                        
0x666d0ad  movaps [rbp+0x2C0],xmm2                       
0x666d0b4  movups xmm3,[r15+0x3C]                        
0x666d0b9  movaps [rbp+0x2D0],xmm3                       
0x666d0c0  mov byte ptr [rbp+0x2E0],0                    
0x666d0c7  movzx eax,word ptr [r15+0x4C]                 
0x666d0cc  movups [rbp+0x3F8],xmm0                       
0x666d0d3  movups [rbp+0x408],xmm1                       
0x666d0da  movups [rbp+0x418],xmm2                       
0x666d0e1  movups [rbp+0x428],xmm3                       
0x666d0e8  mov byte ptr [rbp+0x438],0                    
0x666d0ef  mov [rbp+0x440],ax                            
0x666d0f6  mov dword ptr [rbp+0x448],2                   
0x666d100  mov byte ptr [rbp+0x44C],7                    
0x666d107  mov dword ptr [rbp+0x450],0                   
0x666d111  mov word ptr [rbp+0x454],0                    
0x666d11a  mov byte ptr [rbp+0x456],2                    
0x666d121  mov dword ptr [rbp+0x458],0                   
0x666d12b  mov byte ptr [rbp+0x45C],0                    
0x666d132  xorps xmm6,xmm6                               
0x666d135  movups [rbp+0x460],xmm6                       
0x666d13c  mov rax,[rbp+0x3D0]                           
0x666d143  mov [rbp+0x470],rax                           
0x666d14a  mov eax,[rbp+0x3D8]                           
0x666d150  mov [rbp+0x478],eax                           
0x666d156  mov byte ptr [rbp+0x47C],8                    
0x666d15d  mov qword ptr [rbp+0x480],0                   
0x666d168  mov dword ptr [rbp+0x488],0                   
0x666d172  mov byte ptr [rbp+0x48C],8                    
0x666d179  movzx eax,byte ptr [rbp+0x5F0]                
0x666d180  mov [rbp+0x49D],al                            
0x666d186  movups xmm0,[rbp+0x5E0]                       
0x666d18d  movups [rbp+0x48D],xmm0                       
0x666d194  mov byte ptr [rbp+0x49E],0xFF                 
0x666d19b  mov rax,[rbp+0x1D0]                           
0x666d1a2  mov [rbp+0x4A0],rax                           
0x666d1a9  lea rdi,[rbp+0x4A8]                           
0x666d1b0  mov rcx,rdi                                   
0x666d1b3  mov rdx,rbx                                   
0x666d1b6  call 0xE869FF0                                ; -> sub_e869ff0
0x666d1bb  nop                                           
0x666d1bc  mov rax,[rbp+0x250]                           
0x666d1c3  mov [rbp+0x520],rax                           
0x666d1ca  mov qword ptr [rbp+0x250],0                   
0x666d1dc  movaps xmm1,[rbp+0x350]                       
0x666d1e3  mov qword ptr [rbp+0x348],0                   
0x666d1ee  movups [rbp+0x528],xmm0                   
0x666d1fc  movups [rbp+0x528],xmm0                       
0x666d1f5  movaps [rbp+0x350],xmm6                       
0x666d1fc  movups [rbp+0x538],xmm1                       
0x666d203  mov rax,[rbp+0x360]                           
0x666d20a  mov [rbp+0x548],rax                           
```

---

### Description fields READ in chunk 3 (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x84  | 4    | R      | u32 value -> edi | 7 | 0x666c96f `mov edi,[r15+0x84]` |
| +0x0C  | 16   | R      | frame ctx +0xC (mat4 row 0) | 7 | 0x666d090 `movups xmm0,[r15+0xC]` |
| +0x1C  | 16   | R      | frame ctx +0x1C (mat4 row 1) | 7 | 0x666d09c `movups xmm1,[r15+0x1C]` |
| +0x2C  | 16   | R      | frame ctx +0x2C (mat4 row 2) | 7 | 0x666d0a8 `movups xmm2,[r15+0x2C]` |
| +0x3C  | 16   | R      | frame ctx +0x3C (mat4 row 3) | 7 | 0x666d0b4 `movups xmm3,[r15+0x3C]` |
| +0x4C  | 2    | R      | frame ctx +0x4C (u16) | 7 | 0x666d0c7 `movzx eax,word ptr [r15+0x4C]` |
| +0x5F0 | 1    | R      | frame ctx +0x5F0 (byte) | 7 | 0x666d179 `movzx eax,byte ptr [rbp+0x5F0]` |
| +0x5E0 | 16   | R      | frame ctx +0x5E0 (vec4) | 7 | 0x666d186 `movups xmm0,[rbp+0x5E0]` |
| +0x08  | 4    | R      | frame ctx +0x8 (float) | 7 | 0x666cfe1 `movss xmm0,[r15+8]` |
| +0x398 | 1    | R      | flag byte (rbp+0x398) | 7 | 0x666d083 `cmp byte ptr [rbp+0x398],1` |

**Element object (r14) fields:**
- +0x00: object pointer (0x666cfa2 `mov r9,[r15]` - wait, r15 is frame ctx here, r14 is element object)
- Actually at 0x666cfa2 `mov r9,[r15]` - r15 was set to frame ctx at 0x666c976, so this is frame ctx +0x00
- r14 (element object) used at 0x666cf51 `mov r8,[r14]`

**Visitor (rbx) fields:**
- rbx+0x00, +0x08, +0x10..+0x50 (matrices) copied at 0x666cbf0..0x666cc22

**Frame ctx (r12/r15) fields:**
- r12+0x10 at 0x666c0d5 (passLookup), r12+0x330/0x338/0x340 (buffer management)
- r12+0x78/0x80/0x88 (buffer base/write/end) at 0x666cc26, 0x666ce2c
- r12+8 at 0x666cfe1 (float), r12+0xC..0x4C (mat4), r12+0x4C (u16), r12+0x5E0 (vec4), r12+0x5F0 (byte)

**Global data:**
- 0x129FA160, 0x129FA170, 0x129FA128, 0x129FA120 (thread-local comparands / lookup tables)
- 0x1233E1A8 (allocator), 0x1233E1B0 (shared_ref destroy vtable, tag 0x4A)
- 0xF99FFA0 -> sub_eea6040

**Callees (new in chunk 3):**
- 0x6670E44, 0x6670EB6, 0x6670F28, 0x6670FE9 - thread-local check exits
- 0x9BC830 (sub_9bc830) - alloc fail handler
- 0xEEC6DE0 (sub_eec6de0) - memmove
- 0xE935700 (sub_e935700) - free
- 0xEEC6EC0 (sub_eec6ec0) - memcpy
- 0x5ABA6D0 (sub_5aba6d0) - slow path draw emit
- 0xBBD7F70 (sub_bbd7f70) - called with r9=[r15], r8=[rbp+0x1D0], rdx=r12
- 0x5679DB0 (sub_5679db0) - called again
- 0xE86B370 (sub_e86b370) - called again
- 0xE869FF0 (sub_e869ff0) - called again
- 0x6670A7A - overflow check
- 0x666D86C, 0x666D870, 0x666FB78 - alternate exits

**Key insight:** This chunk handles **buffer management for two ring buffers** (at rsi+0x330 and rsi+0x78), each with different strides (0x14 and 0x58). It allocates new buffers, moves old data (with shared_ref refcount handling), frees old buffers, then emits draw records (stride 0xC8) to a draw buffer at rsi+8. The path at 0x666cf0c checks rsi+0x20 >= 0x10 before taking an alternate route. The final section (0x666cf20+) appears to be a different code path (from je 0x666CF20 at 0x666c88a) that sets up a complex record with matrices from frame ctx.

**SHARED SPILL SLOT:** [rbp+0x668] = description (r15) restored at 0x666c968.

---

### UNVERIFIED items in chunk 3
- [UNVERIFIED: 0x666c918] sub_6670e44 - thread-local exit
- [UNVERIFIED: 0x666c93d] sub_6670eb6 - thread-local exit
- [UNVERIFIED: 0x666c962] sub_6670f28 - thread-local exit
- [UNVERIFIED: 0x666ca18] sub_9bc830 - alloc fail, signature
- [UNVERIFIED: 0x666ca4b] sub_eec6de0 - memmove, signature
- [UNVERIFIED: 0x666cab2] sub_e935700 - free, signature
- [UNVERIFIED: 0x666cb68] sub_eec6ec0 - memcpy, signature
- [UNVERIFIED: 0x666cb84] sub_5aba6d0 - slow path, signature
- [UNVERIFIED: 0x666cbbe] sub_eea6040 alloc - what does it allocate?
- [UNVERIFIED: 0x666cc9f] lock inc on element shared_ref - purpose
- [UNVERIFIED: 0x666cdc2] lock dec + destroy - cleanup loop
- [UNVERIFIED: 0x666ce27] sub_e935700 free - signature
- [UNVERIFIED: 0x666cfbc] sub_6670fe9 - thread-local exit
- [UNVERIFIED: 0x666cfb6] sub_bbd7f70 - signature, purpose
- [UNVERIFIED: 0x666d02d] lookup table 0x129FA120 - what table?
- [UNVERIFIED: 0x666d07d] sub_5679db0 - signature
- [UNVERIFIED: 0x666d08a] sub_666fb78 - exit
- [UNVERIFIED: 0x666d1b6] sub_e869ff0 - signature
- [UNVERIFIED: 0x666d203] Chunk boundary - continues

---

### Chunk 4: 0x666d203..0x666db90 (500 instructions)

**Phase 28: 0x666d203..0x666d2d6 — Jump table on [rbp+0x378] (4 cases) + shared_ref cleanup + desc+0x68 lookup**
```
0x666d203  mov rax,[rbp+0x360]                           
0x666d20a  mov [rbp+0x548],rax                           
0x666d211  mov byte ptr [rbp+0x560],0xFF                 
0x666d218  movzx eax,byte ptr [rbp+0x378]                
0x666d21f  cmp rax,3                                     
0x666d223  ja 0x666F4F3                                  ; -> sub_666f4f3
0x666d229  lea rcx,[rbp+0x550]                           
0x666d230  lea rdx,[0xF2BF4F0]                           ; [data_f2bf4f0] jump table
0x666d237  movsxd r8,[rdx+rax*4]                         
0x666d23b  add r8,rdx                                    
0x666d23e  jmp r8                                        
0x666d241  mov rcx,[rbp+0x368]                           ; case 0
0x666d248  mov [rbp+0x550],rcx                           
0x666d24f  jmp 0x666F4ED                                 ; -> sub_666f4ed
0x666d254  mov rax,[rax]                                 ; case 1 (from je 0x666CF20 path)
0x666d257  mov [rbp+0x3F0],rax                           
0x666d25e  mov qword ptr [rbp+0x3F8],0                   
0x666d269  mov rax,[rbp+0x3F0]                           
0x666d270  mov rax,[rax+0x18]                            
0x666d274  mov rax,[rax]                                 
0x666d277  mov [rbp],rax                                 
0x666d27b  lea rbx,[rbp+8]                               
0x666d27f  mov r8,[r15]                                  ; r15 = frame ctx
0x666d282  mov rdx,[rax+0x170]                           ; mesh +0x170
0x666d289  mov rcx,rbx                                   
0x666d28c  call 0xE86B370                                ; -> sub_e86b370
0x666d291  nop                                           
0x666d292  mov [rbp+0x80],r15                            
0x666d299  mov rsi,[rbp+0x3F8]                           ; shared_ref cleanup
... (refcount cleanup to 0x666d2cf)

loc_666d2d0:  ; from 666d2a3, 666d2a9, 666d2be
0x666d2d0  mov r11,[rbp+0x668]                           ; RESTORE description from SHARED SPILL SLOT
0x666d2d7  lea rax,[r11+0x68]                            ; desc+0x68
0x666d2db  mov [rbp+0x670],rax                           
```

**Phase 29: 0x666d2e2..0x666d379 — desc+0x48/+0x52 lookup (stride 0x30) + call 0xBCABA00**
```
0x666d2e2  mov rax,[rbp+0x48]                            ; base
0x666d2e6  movzx r8d,word ptr [rbp+0x52]                 ; count
0x666d2eb  mov ecx,r8d                                   
0x666d2ee  shl ecx,4                                     
0x666d2f1  lea rdx,[rcx+rcx*2]                           ; *0x30 stride
0x666d2f5  mov rcx,rax                                   
0x666d2f8  test r8,r8                                    
0x666d2fb  je short 0x666D325                            ; -> loc_666d325
0x666d2fd  mov r8,[0x129FA148]                           ; [data_129fa148] lookup table
0x666d304  mov r9,rdx                                    
0x666d307  mov rcx,rax                                   

loc_666d310:  ; from 666d321
0x666d310  mov r10,[rcx]                                 
0x666d313  cmp [r10+0x28],r8                             
0x666d317  je short 0x666D325                            ; -> loc_666d325 (found)
0x666d319  add rcx,0x30                                  
0x666d31d  add r9,0xFFFFFFFFFFFFFFD0                     ; -0x30
0x666d321  jne short 0x666D310                           ; -> loop

loc_666d323  jmp short 0x666D37A                           ; -> loc_666d37a (not found)

loc_666d325:  ; from 666d2fb, 666d317
0x666d325  add rdx,rax                                   
0x666d328  cmp rcx,rdx                                   
0x666d32b  jae short 0x666D37A                           ; -> loc_666d37a
0x666d32d  sub ecx,eax                                   
0x666d32f  shr ecx,4                                     
0x666d332  imul eax,ecx,0xFFFFAAAB                       ; /0x30
0x666d338  mov [rbp+0x1D0],ax                            
0x666d33f  mov byte ptr [rbp+0x1D2],1                    
0x666d346  mov byte ptr [rbp+0x3FC],0                    
0x666d34d  mov dword ptr [rsp+0x20],0                    
0x666d355  mov rcx,rbp                                   
0x666d358  lea rdx,[rbp+0x1D0]                           
0x666d35f  lea r9,[rbp+0x3F0]                            
0x666d366  mov r8,[rbp+0x670]                            
0x666d36d  call 0xBCABA00                                ; -> sub_bcaba00
0x666d372  nop                                           
0x666d373  mov r11,[rbp+0x668]                           ; restore description
```

**Phase 30: 0x666d37a..0x666d4a9 — desc+0x18/+0x38/+0x58/+0x78 (four vec4) + second lookup (stride 0x10)**
```
loc_666d37a:  ; from 666d323, 666d32b
0x666d37a  movups xmm0,[r11+0x18]                        ; desc+0x18 (vec4)
0x666d37f  movaps [rbp+0x3F0],xmm0                       
0x666d386  mov qword ptr [rbp+0x1D0],1                   
0x666d391  mov [rbp+0x1D8],r14                           
0x666d398  mov rax,[rbp+0x38]                            
0x666d39c  movzx edx,word ptr [rbp+0x42]                 
0x666d3a0  mov ecx,edx                                   
0x666d3a2  shl ecx,4                                     
0x666d3a5  mov r8,rax                                    
0x666d3a8  test edx,edx                                  
0x666d3aa  je short 0x666D3DC                            ; -> loc_666d3dc
0x666d3ac  mov r9,[0x129FA158]                           ; [data_129fa158] lookup table
0x666d3b3  xor r8d,r8d                                   

loc_666d3c0:  ; from 666d3d1
0x666d3c0  mov r10,[rax+r8]                              
0x666d3c4  cmp [r10+0x28],r9                             
0x666d3c8  je short 0x666D3D9                            ; -> loc_666d3d9 (found)
0x666d3ca  add r8,0x10                                   
0x666d3ce  cmp rcx,r8                                    
0x666d3d1  jne short 0x666D3C0                           ; -> loop

loc_666d3d3  mov dx,1                                    
0x666d3d7  jmp short 0x666D41F                           ; -> loc_666d41f

loc_666d3d9:  ; from 666d3c8
0x666d3d9  add r8,rax                                    

loc_666d3dc:  ; from 666d3aa
0x666d3dc  lea r9,[rax+rcx]                              
0x666d3e0  cmp r8,r9                                     
0x666d3e3  jae short 0x666D41F                           ; -> loc_666d41f
0x666d3e5  sub r8d,eax                                   
0x666d3e8  shr r8d,4                                     
0x666d3ec  mov [rbp+0x340],r8w                           
0x666d3f4  mov byte ptr [rbp+0x342],1                    
0x666d3fb  lea rdx,[rbp+0x340]                           
0x666d402  lea r8,[rbp+0x1D0]                            
0x666d409  mov rcx,rbx                                   
0x666d40c  call 0x5679DB0                                ; -> sub_5679db0
0x666d411  nop                                           
0x666d412  mov rax,[rbp+0x38]                            
0x666d416  movzx edx,word ptr [rbp+0x42]                 
0x666d41a  mov ecx,edx                                   
0x666d41c  shl ecx,4                                     

loc_666d41f:  ; from 666d3d7, 666d3e3
0x666d41f  movaps xmm0,[0xEF40DC0]                       ; [data_ef40dc0] constant
0x666d426  movaps [rbp+0x3F0],xmm0                       
0x666d42d  mov qword ptr [rbp+0x1D0],1                   
0x666d438  mov [rbp+0x1D8],r14                           
0x666d43f  mov r8,rax                                    
0x666d442  test dx,dx                                    
0x666d445  je short 0x666D475                            ; -> loc_666d475
0x666d447  mov rdx,[0x129FA168]                          ; [data_129fa168] lookup table
0x666d44e  mov r9,rcx                                    
0x666d451  mov r8,rax                                    

loc_666d460:  ; from 666d471
0x666d460  mov r10,[r8]                                  
0x666d463  cmp [r10+0x28],rdx                            
0x666d467  je short 0x666D475                            ; -> loc_666d475 (found)
0x666d469  add r8,0x10                                   
0x666d46d  add r9,0xFFFFFFFFFFFFFFF0                     
0x666d471  jne short 0x666D460                           ; -> loop

loc_666d473  jmp short 0x666D4AA                           ; -> loc_666d4aa (not found)

loc_666d475:  ; from 666d445, 666d467
0x666d475  add rcx,rax                                   
0x666d478  cmp r8,rcx                                    
0x666d47b  jae short 0x666D4AA                           ; -> loc_666d4aa
0x666d47d  sub r8d,eax                                   
0x666d480  shr r8d,4                                     
0x666d484  mov [rbp+0x340],r8w                           
0x666d48c  mov byte ptr [rbp+0x342],1                    
0x666d493  lea rdx,[rbp+0x340]                           
0x666d49a  lea r8,[rbp+0x1D0]                            
0x666d4a1  mov rcx,rbx                                   
0x666d4a4  call 0x5679DB0                                ; -> sub_5679db0
0x666d4a9  nop                                           
```

**Phase 31: 0x666d4aa..0x666d60b — Mesh draw setup (desc+0x78) + render-state mapper (0x66A0F60)**
```
loc_666d4aa:  ; from 666d473, 666d47b
0x666d4aa  mov r15,[rbp+0x668]                           ; restore description
0x666d4b1  mov rsi,[r15+0x78]                            ; desc+0x78 (Mesh-like)
0x666d4b5  mov rax,[rsi+0x60]                            ; index count calc
0x666d4b9  sub rax,[rsi+0x58]                            
0x666d4bd  shr rax,2                                     
0x666d4c1  imul eax,0xAAAAAAAB                           
0x666d4c7  test eax,eax                                  
0x666d4c9  je short 0x666D4FF                            ; -> loc_666d4ff
0x666d4cb  mov edx,0x250                                 
0x666d4d0  add rdx,[rbp]                                 
0x666d4d4  lea rcx,[rbp+0x3F0]                           
0x666d4db  xor r8d,r8d                                   
0x666d4de  call 0xBBD7C70                                ; -> sub_bbd7c70
0x666d4e3  nop                                           
0x666d4e4  lea rdx,[rbp+0x3F0]                           
0x666d4eb  mov rcx,rsi                                   
0x666d4ee  call 0x4DEDD00                                ; -> sub_4dedd00
0x666d4f3  nop                                           
0x666d4f4  mov r15,[rbp+0x668]                           ; restore description
0x666d4fb  mov rsi,[r15+0x78]                            ; desc+0x78

loc_666d4ff:  ; from 666d4c9
0x666d4ff  xor r14d,r14d                                 
0x666d502  cmp byte ptr [rsi+0x1D4],0                    ; object+0x1D4 flag
0x666d509  je short 0x666D512                            ; -> loc_666d512
0x666d50b  mov r14d,[rsi+0x1D0]                          ; object+0x1D0 -> r14d

loc_666d512:  ; from 666d509
0x666d512  movaps xmm0,[rbp+0x2A0]                       ; copy 4 matrices
0x666d519  movaps xmm1,[rbp+0x2B0]                       
0x666d520  movaps xmm2,[rbp+0x2C0]                       
0x666d527  movaps xmm3,[rbp+0x2D0]                       
0x666d52e  movaps [rbp+0x340],xmm0                       
0x666d535  movaps [rbp+0x350],xmm1                       
0x666d53c  movaps [rbp+0x360],xmm2                       
0x666d543  movaps [rbp+0x370],xmm3                       
0x666d54a  mov byte ptr [rbp+0x380],0                    
0x666d551  xorps xmm0,xmm0                               
0x666d554  movaps [rbp+0x630],xmm0                       
0x666d55b  mov rax,[rsi+0x1B0]                           ; object+0x1B0
0x666d562  test rax,rax                                  
0x666d565  je short 0x666D56B                            ; -> loc_666d56b
0x666d567  movzx eax,word ptr [rax+0x10]                 

loc_666d56b:  ; from 666d565
0x666d56b  mov rax,[rsi+0x1B8]                           ; object+0x1B8
0x666d572  test rax,rax                                  
0x666d575  je short 0x666D584                            ; -> loc_666d584
0x666d577  lock inc dword ptr [rax+8]                    
0x666d57b  mov rax,[rsi+0x1B8]                           
0x666d582  jmp short 0x666D586                           ; -> loc_666d586

loc_666d584:  ; from 666d575
0x666d584  xor eax,eax                                   

loc_666d586:  ; from 666d582
0x666d586  mov rcx,[rsi+0x1B0]                           ; object+0x1B0
0x666d58d  mov [rbp+0x630],rcx                           
0x666d594  mov rsi,[rbp+0x638]                           ; shared_ref cleanup
0x666d59b  mov [rbp+0x638],rax                           
0x666d5a2  test rsi,rsi                                  
... (refcount cleanup to 0x666d5d2)

loc_666d5d2:  ; from 666d5a5, 666d5ab, 666d5c0
0x666d5d2  mov rax,[rbp+0x648]                           ; visitor this
0x666d5d9  mov r8,[rax+0x3B8]                            ; visitor+0x3B8
0x666d5e0  mov rdx,[r12]                                 ; frame ctx
0x666d5e4  mov [rsp+0x20],r14d                           ; saved from object+0x1D0
0x666d5e9  mov dword ptr [rsp+0x30],0                    
0x666d5f1  mov dword ptr [rsp+0x28],0                    
0x666d5f9  lea rcx,[rbp+0x1D0]                           ; output
0x666d600  lea r9,[rbp+0x630]                            ; input (object+0x1B0/0x1B8)
0x666d607  call 0x66A0F60                                ; -> sub_66a0f60 (render-state mapper)
```

**Phase 32: 0x666d60d..0x666d78b — Complex record setup + conditional matrix selection ([rbp+0x380])**
```
0x666d60d  add edi,0xFFFFFFE0                            ; edi = r14d - 0x20
0x666d610  mov si,[r15+0x80]                             ; desc+0x80 (u16)
0x666d618  movlps [rbp+0x3F4],xmm7                       ; partial xmm7
0x666d61f  movss [rbp+0x3FC],xmm6                        ; zero
0x666d627  mov dword ptr [rbp+0x404],2                   
0x666d631  mov byte ptr [rbp+0x408],7                    
0x666d638  mov dword ptr [rbp+0x40C],0                   
0x666d642  mov word ptr [rbp+0x410],1                    
0x666d64b  mov byte ptr [rbp+0x412],5                    
0x666d652  mov dword ptr [rbp+0x414],0                   
0x666d65c  mov byte ptr [rbp+0x418],1                    
0x666d663  xorps xmm0,xmm0                               
0x666d666  movups [rbp+0x41C],xmm0                       
0x666d66d  mov [rbp+0x42C],edi                           
0x666d673  mov qword ptr [rbp+0x430],0                   
0x666d67e  mov byte ptr [rbp+0x438],8                    
0x666d685  mov qword ptr [rbp+0x43C],0                   
0x666d690  mov dword ptr [rbp+0x444],0                   
0x666d69a  mov byte ptr [rbp+0x448],8                    
0x666d6a1  mov qword ptr [rbp+0x44C],0                   
0x666d6ac  mov qword ptr [rbp+0x452],0                   
0x666d6b7  mov byte ptr [rbp+0x45A],0xFF                 
0x666d6be  mov rax,[rbp]                                 
0x666d6c2  mov [rbp+0x460],rax                           
0x666d6c9  lea rcx,[rbp+0x468]                           
0x666d6d0  mov rdx,rbx                                   
0x666d6d3  call 0xE869FF0                                ; -> sub_e869ff0
0x666d6d8  nop                                           
0x666d6d9  mov rax,[rbp+0x80]                            
0x666d6e0  mov [rbp+0x4E0],rax                           
0x666d6e7  mov qword ptr [rbp+0x80],0                    
0x666d6f2  mov byte ptr [rbp+0x528],0xFF                 
0x666d6f9  movzx eax,byte ptr [rbp+0x380]                ; mode flag
0x666d700  movzx ecx,al                                  
0x666d703  cmp ecx,1                                     
0x666d706  jg short 0x666D746                            ; -> loc_666d746
0x666d708  test ecx,ecx                                  
0x666d70a  jne short 0x666D75B                           ; -> loc_666d75b
0x666d70c  movaps xmm0,[rbp+0x340]                       ; mode 0: copy 4 matrices
0x666d713  movaps xmm1,[rbp+0x350]                       
0x666d71a  movaps xmm2,[rbp+0x360]                       
0x666d721  movaps xmm3,[rbp+0x370]                       
0x666d728  movups [rbp+0x4E8],xmm0                       
0x666d72f  movups [rbp+0x4F8],xmm1                       
0x666d736  movups [rbp+0x508],xmm2                       
0x666d73d  movups [rbp+0x518],xmm3                       
0x666d744  jmp short 0x666D78C                           ; -> loc_666d78c

loc_666d746:  ; from 666d706
0x666d746  cmp ecx,2                                     
0x666d749  jne short 0x666D792                           ; -> loc_666d792
0x666d74b  mov rcx,[rbp+0x340]                           ; mode 2: only first matrix
0x666d752  mov [rbp+0x4E8],rcx                           
0x666d759  jmp short 0x666D78C                           ; -> loc_666d78c

loc_666d75b:  ; from 666d70a
0x666d75b  mov rcx,[rbp+0x350]                           ; mode 1: first matrix + zero rest
0x666d762  mov qword ptr [rbp+0x350],0                   
0x666d76d  movaps xmm0,[rbp+0x340]                       
0x666d774  xorps xmm1,xmm1                               
0x666d777  movaps [rbp+0x340],xmm1                       
0x666d77e  movups [rbp+0x4E8],xmm0                       
0x666d785  mov [rbp+0x4F8],rcx                           

loc_666d78c:  ; from 666d744, 666d759
0x666d78c  mov [rbp+0x528],al                            
```

**Phase 33: 0x666d792..0x666d86b — Jump table on [rbp+0x208] (4 cases) + string "fullscreen_cube_overlay"**
```
loc_666d792:  ; from 666d749
0x666d792  lea rdi,[rbp+0x3F4]                           
0x666d799  lea r10,[rbp+0x404]                           
0x666d7a0  lea r11,[rbp+0x460]                           
0x666d7a7  lea r9,[rbp+0x4E8]                            
0x666d7ae  lea r8,[rbp+0x530]                            
0x666d7b5  movaps xmm0,[rbp+0x1D0]                       ; record data
0x666d7bc  movaps xmm1,[rbp+0x1E0]                       
0x666d7c3  mov qword ptr [rbp+0x1D8],0                   
0x666d7ce  movups [rbp+0x530],xmm0                       
0x666d7d5  xorps xmm0,xmm0                               
0x666d7d8  movaps [rbp+0x1E0],xmm0                       
0x666d7df  movups [rbp+0x540],xmm1                       
0x666d7e6  mov rax,[rbp+0x1F0]                           
0x666d7ed  mov [rbp+0x550],rax                           
0x666d7f4  mov byte ptr [rbp+0x568],0xFF                 
0x666d7fb  movzx eax,byte ptr [rbp+0x208]                ; jump table index
0x666d802  cmp rax,3                                     
0x666d806  ja 0x666E5B2                                  ; -> loc_666e5b2
0x666d80c  lea rcx,[0xF2BF4D0]                           ; [data_f2bf4d0] jump table
0x666d813  movsxd rdx,[rcx+rax*4]                        
0x666d817  add rdx,rcx                                   
0x666d81a  jmp rdx                                       
0x666d81c  mov rcx,[rbp+0x1F8]                           ; case 0
0x666d823  mov [rbp+0x558],rcx                           
0x666d82a  jmp 0x666E5AC                                 ; -> loc_666e5ac
0x666d82f  lea rcx,[rbp+0x1F8]                           ; case 1
0x666d836  movups xmm0,[rcx]                             
0x666d839  movups [rdi+0x164],xmm0                       
0x666d840  jmp 0x666E5AC                                 ; -> loc_666e5ac
0x666d845  movups [rdi+0x164],xmm0                       
0x666d84c  mov rcx,[rbp+0x200]                           ; case 2
0x666d853  test rcx,rcx                                  
0x666d856  je 0x666E595                                  ; -> loc_666e595
0x666d85c  lock inc dword ptr [rcx+8]                    
0x666d860  mov rcx,[rbp+0x200]                           
0x666d867  jmp 0x666E597                                 ; -> loc_666e597

loc_666d86c:  ; from 0x666cf0c (alternate path)
0x666d86c  add rsi,8                                     
0x666d870  add rbx,rsi                                   
0x666d873  lea r8,[0xF51E3D7]                            ; [data_f51e3d7] "fullscreen_cube_overlay"
0x666d87a  mov r9d,0x17                                  
0x666d880  mov rcx,rsi                                   
0x666d883  mov rdx,rbx                                   
0x666d886  call 0xE93BF00                                ; -> sub_e93bf00
0x666d88b  cmp rax,rbx                                   
0x666d88e  setne cl                                      
0x666d891  sub rax,rsi                                   
0x666d894  cmp rax,0xFFFFFFFFFFFFFFFF                    
0x666d898  setne sil                                     
0x666d89c  and sil,cl                                    
0x666d89f  mov rbx,rdi                                   
0x666d8a2  mov rax,[rbp+0x408]                           
0x666d8a9  cmp rax,0x10                                  
0x666d8ad  jb short 0x666D8E7                            ; -> loc_666d8e7
0x666d8af  mov rcx,[rbp+0x3F0]                           
0x666d8b6  lea rdx,[rax+1]                               
0x666d8ba  cmp rdx,0x1000                                
0x666d8c1  jb short 0x666D8E2                            ; -> loc_666d8e2
0x666d8c3  mov r8,[rcx-8]                                
0x666d8c7  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666d8cb  sub rcx,r8                                    
0x666d8ce  cmp rcx,0x20                                  
0x666d8d2  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666d8d8  add rax,0x28                                  
0x666d8dc  mov rdx,rax                                   
0x666d8df  mov rcx,r8                                    

loc_666d8e2:  ; from 666d8c1
0x666d8e2  call 0xE935700                                ; -> sub_e935700
```

**Phase 34: 0x666d8e7..0x666db8f — desc+0xC8/+0xC9 checks + frame ctx+0x1AD..0x1AF flag parsing + alloc**
```
loc_666d8e7:  ; from 666d8ad
0x666d8e7  mov rax,[r12]                                 ; frame ctx
0x666d8eb  test rax,rax                                  
0x666d8ee  je short 0x666D8F6                            ; -> loc_666d8f6
0x666d8f0  mov rcx,[rax+0x40]                            ; frame ctx+0x40
0x666d8f4  jmp short 0x666D8F8                           ; -> loc_666d8f8

loc_666d8f6:  ; from 666d8ee
0x666d8f6  xor ecx,ecx                                   

loc_666d8f8:  ; from 666d8f4
0x666d8f8  mov word ptr [rbp+0x3E0],0                    
0x666d901  mov dword ptr [rbp+0x3E4],0                   
0x666d90b  mov byte ptr [rbp+0x3E8],0                    
0x666d912  movzx eax,byte ptr [rcx+0x1AD]                ; frame ctx+0x1AD
0x666d919  test eax,eax                                  
0x666d91b  je short 0x666D926                            ; -> loc_666d926
0x666d91d  cmp eax,1                                     
0x666d920  jne short 0x666D930                           ; -> loc_666d930
0x666d922  xor eax,eax                                   
0x666d924  jmp short 0x666D928                           ; -> loc_666d928

loc_666d926:  ; from 666d91b
0x666d926  mov al,1                                      

loc_666d928:  ; from 666d924
0x666d928  mov [rbp+0x3E0],al                            
0x666d92e  jmp short 0x666D932                           ; -> loc_666d932

loc_666d930:  ; from 666d920
0x666d930  xor eax,eax                                   

loc_666d932:  ; from 666d92e
0x666d932  movzx edx,byte ptr [rcx+0x1AE]                ; frame ctx+0x1AE
0x666d939  cmp edx,1                                     
0x666d93c  je short 0x666D944                            ; -> loc_666d944
0x666d93e  test edx,edx                                  
0x666d940  jne short 0x666D94A                           ; -> loc_666d94a
0x666d942  or al,4                                       

loc_666d944:  ; from 666d93c
0x666d944  mov [rbp+0x3E0],al                            

loc_666d94a:  ; from 666d940
0x666d94a  movzx edx,byte ptr [rcx+0x1AF]                ; frame ctx+0x1AF
0x666d951  cmp edx,1                                     
0x666d954  je short 0x666D95C                            ; -> loc_666d95c
0x666d956  test edx,edx                                  
0x666d958  jne short 0x666D962                           ; -> loc_666d962
0x666d95a  or al,0x10                                    

loc_666d95c:  ; from 666d954
0x666d95c  mov [rbp+0x3E0],al                            

loc_666d962:  ; from 666d958
0x666d962  movzx ecx,byte ptr [rcx+0x1AC]                ; frame ctx+0x1AC
0x666d969  cmp ecx,4                                     
0x666d96c  je short 0x666D977                            ; -> loc_666d977
0x666d96e  cmp ecx,1                                     
0x666d971  je short 0x666D97D                            ; -> loc_666d97d
0x666d973  test ecx,ecx                                  
0x666d975  jne short 0x666D98B                           ; -> loc_666d98b

loc_666d977:  ; from 666d96c
0x666d977  or al,0x40                                    
0x666d979  mov cl,5                                      
0x666d97b  jmp short 0x666D97F                           ; -> loc_666d97f

loc_666d97d:  ; from 666d971
0x666d97d  xor ecx,ecx                                   

loc_666d97f:  ; from 666d97b
0x666d97f  mov [rbp+0x3E0],al                            
0x666d985  mov [rbp+0x3E1],cl                            

loc_666d98b:  ; from 666d975
0x666d98b  mov rax,[rbp+0x650]                           
0x666d992  mov eax,[rax+0x70]                            
0x666d995  mov [rbp+0x670],eax                           
0x666d99b  mov eax,[0x129F9248]                          ; [data_129f9248] thread-local
0x666d9a1  mov ecx,[0x128767C8]                          
0x666d9a7  mov rdx,gs:[0x58]                             
0x666d9b0  mov rcx,[rdx+rcx*8]                           
0x666d9b4  cmp eax,[rcx+4]                               
0x666d9ba  jg 0x6670D0A                                  ; -> sub_6670d0a
0x666d9c0  cmp byte ptr [r15+0xC8],1                     ; desc+0xC8 == 1?
0x666d9c8  mov [rbp+0x668],r15                           ; SHARED SPILL SLOT
0x666d9cf  jne 0x666DA92                                 ; -> loc_666da92
0x666d9d5  mov [rbp+0x648],rbx                           ; save visitor
0x666d9dc  mov eax,[0x129F9270]                          ; [data_129f9270] thread-local
0x666d9e2  mov ecx,[0x128767C8]                          
0x666d9e8  mov rdx,gs:[0x58]                             
0x666d9f1  mov rcx,[rdx+rcx*8]                           
0x666d9f5  cmp eax,[rcx+4]                               
0x666d9fb  jg 0x6670F9A                                  ; -> sub_6670f9a
0x666da01  cmp dword ptr [rbp+0x670],1                   
0x666da08  lea rax,[0x129F9250]                          ; [data_129f9250]
0x666da0f  lea rsi,[0x129F9228]                          ; [data_129f9228]
0x666da16  cmove rsi,rax                                 
0x666da1a  xorps xmm0,xmm0                               
0x666da1d  movaps [rbp+0x5D0],xmm0                       
0x666da24  lea rax,[0x129F9260]                          ; [data_129f9260]
0x666da2b  lea rcx,[0x129F9238]                          ; [data_129f9238]
0x666da32  cmove rcx,rax                                 
0x666da36  movaps [rbp+0x5C0],xmm0                       
0x666da3d  mov rbx,[rcx]                                 
0x666da40  lea rax,[0x129F9268]                          ; [data_129f9268]
0x666da47  lea rcx,[0x129F9240]                          ; [data_129f9240]
0x666da4e  cmove rcx,rax                                 
0x666da52  cmp qword ptr [rcx],0x10                      
0x666da56  mov r15,[rbp+0x650]                           ; r15 = frame ctx
0x666da5d  jb short 0x666DA62                            ; -> loc_666da62
0x666da5f  mov rsi,[rsi]                                 

loc_666da62:  ; from 666da5d
0x666da62  test rbx,rbx                                  
0x666da65  js 0x6670FE4                                  ; -> sub_6670fe4
0x666da6b  cmp rbx,0xF                                   
0x666da6f  ja short 0x666DAA1                            ; -> loc_666daa1
0x666da71  mov [rbp+0x5D0],rbx                           
0x666da78  mov qword ptr [rbp+0x5D8],0xF                 
0x666da83  movups xmm0,[rsi]                             
0x666da86  movaps [rbp+0x5C0],xmm0                       
0x666da8d  jmp 0x666DB78                                 ; -> loc_666db78

loc_666da92:  ; from 666d9cf (desc+0xC8 != 1)
0x666da92  mov rax,[r12]                                 ; frame ctx
0x666da96  test rax,rax                                  
0x666da99  je short 0x666DAF4                            ; -> loc_666daf4
0x666da9b  mov rax,[rax+0x40]                            ; frame ctx+0x40
0x666da9f  jmp short 0x666DAF6                           ; -> loc_666daf6

loc_666daa1:  ; from 666da6f (rbx > 0xF)
0x666daa1  mov rdx,rbx                                   
0x666daa4  or rdx,0xF                                    
0x666daa8  cmp rdx,0x17                                  
0x666daac  mov r14d,0x16                                 
0x666dab2  cmovae r14,rdx                                
0x666dab6  mov rcx,[0x1233E1A8]                          ; allocator
0x666dabd  mov rax,[rcx]                                 
0x666dac0  mov rax,[rax+8]                               
0x666dac4  cmp rdx,0xFFF                                 
0x666dacb  jb short 0x666DB3C                            ; -> loc_666db3c
0x666dacd  lea rdi,[r14+0x28]                            ; size + 0x28
0x666dad1  mov rdx,rdi                                   
0x666dad4  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc)
0x666dada  test rax,rax                                  
0x666dadd  je 0x6670A2E                                  ; -> sub_6670a2e
0x666dae3  mov rcx,rax                                   
0x666dae6  add rcx,0x27                                  
0x666daea  and rcx,0xFFFFFFFFFFFFFFE0                    ; align 0x20
0x666daee  mov [rcx-8],rax                               
0x666daf2  jmp short 0x666DB55                           ; -> loc_666db55

loc_666daf4:  ; from 666da99
0x666daf4  xor eax,eax                                   

loc_666daf6:  ; from 666da9f
0x666daf6  mov [rbp+0x648],rax                           
0x666dafd  mov dword ptr [rbp+0x3F0],0                   
0x666db07  lea rcx,[rbp+0x5E0]                           
0x666db0e  lea rdx,[rbp+0x3F0]                           
0x666db15  mov r8,rbp                                    
0x666db18  call 0x9B020                                  ; -> sub_9b020
0x666db1d  test sil,sil                                  
0x666db20  je 0x666FC9E                                  ; -> sub_666fc9e
0x666db26  mov rax,[r12]                                 ; frame ctx
0x666db2a  test rax,rax                                  
0x666db2d  je 0x666DDD1                                  ; -> loc_666ddd1
0x666db33  mov rdi,[rax+0x40]                            ; frame ctx+0x40
0x666db37  jmp 0x666DDD3                                 ; -> loc_666ddd3

loc_666db3c:  ; from 666dacb (rdx < 0xFFF)
0x666db3c  lea rdi,[r14+1]                               
0x666db40  mov rdx,rdi                                   
0x666db43  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc)
0x666db49  mov rcx,rax                                   
0x666db4c  test rax,rax                                  
0x666db4f  je 0x6671913                                  ; -> sub_6671913

loc_666db55:  ; from 666daf2
0x666db55  mov [rbp+0x5C0],rcx                           
0x666db5c  mov [rbp+0x5D0],rbx                           
0x666db63  mov [rbp+0x5D8],r14                           
0x666db6a  inc rbx                                       
0x666db6d  mov rdx,rsi                                   
0x666db70  mov r8,rbx                                    
0x666db73  call 0xEEC6EC0                                ; -> sub_eec6ec0 (memcpy)

loc_666db78:  ; from 666da8d
0x666db78  mov dword ptr [rbp+0x3F0],0                   
0x666db82  lea rcx,[rbp+0x5E0]                           
0x666db89  lea rdx,[rbp+0x3F0]                           
0x666db90  mov r8,rbp                                    
```

---

### Description fields READ in chunk 4 (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x378 | 1    | R      | Jump table index (0..3) | 7 | 0x666d218 `movzx eax,byte ptr [rbp+0x378]` |
| +0x368 | 8    | R      | Pointer for case 0 | 7 | 0x666d241 `mov rcx,[rbp+0x368]` |
| +0x360 | 8    | R      | Pointer | 7 | 0x666d203 `mov rax,[rbp+0x360]` |
| +0x68  | 8    | R      | Address taken for 0xBCABA00 | 7 | 0x666d2d7 `lea rax,[r11+0x68]` |
| +0x48  | 8    | R      | Base for lookup (stride 0x30) | 7 | 0x666d2e2 `mov rax,[rbp+0x48]` |
| +0x52  | 2    | R      | Count for lookup | 7 | 0x666d2e6 `movzx r8d,word ptr [rbp+0x52]` |
| +0x18  | 16   | R      | Vec4 (first of four) | 7 | 0x666d37a `movups xmm0,[r11+0x18]` |
| +0x28  | 16   | R      | Vec4 (second) - implied by pattern | 7 | [I] pattern from prior chunks |
| +0x38  | 16   | R      | Vec4 (third) - implied | 7 | [I] |
| +0x48  | 16   | R      | Vec4 (fourth) - implied | 7 | [I] |
| +0x38  | 8    | R      | Base for lookup (stride 0x10) | 7 | 0x666d398 `mov rax,[rbp+0x38]` |
| +0x42  | 2    | R      | Count for lookup | 7 | 0x666d39c `movzx edx,word ptr [rbp+0x42]` |
| +0x78  | 8    | R      | Mesh-like pointer (confirmed) | 7 | 0x666d4b1 `mov rsi,[r15+0x78]` |
| +0x80  | 2    | R      | u16 | 7 | 0x666d610 `mov si,[r15+0x80]` |
| +0xC8  | 1    | R      | Byte flag (==1 check) | 7 | 0x666d9c0 `cmp byte ptr [r15+0xC8],1` |
| +0xC9  | 1    | R      | Byte - implied by EffectDescriptions.h | 7 | [I] from header |

**Frame ctx (r12/r15) fields:**
- r12+0x40 at 0x666d8f0, 0x666da9b
- r12+0x70 at 0x666d992 `mov eax,[rax+0x70]`
- r12+0x1AC..0x1AF (flag bytes) at 0x666d912, 0x666d932, 0x666d94a, 0x666d962
- r12+0x1AD (byte) -> al bit 0
- r12+0x1AE (byte) -> al bit 2 (or 4)
- r12+0x1AF (byte) -> al bit 4 (or 0x10)
- r12+0x1AC (byte) -> cl (5 or 0)

**Element object (rsi) fields:**
- rsi+0x58, +0x60 (index buffer range) at 0x666d4b5
- rsi+0x1B0, +0x1B8 (shared_refs) at 0x666d55b, 0x666d56b
- rsi+0x1D0, +0x1D4 (flag + value) at 0x666d502, 0x666d50b

**Visitor (rbx) fields:**
- rbx+0x3B8 at 0x666d5d9

**Global data / tables:**
- 0xF2BF4F0, 0xF2BF4D0 (jump tables)
- 0x129FA148, 0x129FA158, 0x129FA168 (lookup tables, stride 0x30/0x10)
- 0xEF40DC0 (constant xmm)
- 0xF51E3D7 "fullscreen_cube_overlay" string
- 0x129F9228, 0x129F9238, 0x129F9240, 0x129F9248, 0x129F9250, 0x129F9260, 0x129F9268, 0x129F9270 (thread-local / constant data)
- 0x1233E1A8 (allocator), 0x1233E1B0 (shared_ref destroy)
- 0xF99FFA0 -> sub_eea6040

**Callees (new in chunk 4):**
- 0x666F4F3, 0x666F4ED - jump table exits
- 0xBCABA00 (sub_bcaba00) - called again
- 0x5679DB0 (sub_5679db0) - called again (3x in this chunk)
- 0xBBD7C70 (sub_bbd7c70) - called again
- 0x4DEDD00 (sub_4dedd00) - called again
- 0x66A0F60 (sub_66a0f60) - render-state mapper, called again
- 0xE86B370 (sub_e86b370) - called again
- 0xE869FF0 (sub_e869ff0) - called again
- 0xE93BF00 (sub_e93bf00) - string-related
- 0xE935700 (sub_e935700) - free
- 0x9B020 (sub_9b020) - new
- 0x6670D0A, 0x6670F9A, 0x6670FE4, 0x6670A2E, 0x6671913 - error/exit paths
- 0x666FC9E, 0x666DDD1, 0x666DDD3, 0x666E5B2, 0x666E5AC, 0x666E595, 0x666E597 - alternate paths
- 0xEEC6EC0 (sub_eec6ec0) - memcpy

**Key insights:**
1. **SHARED SPILL SLOT [rbp+0x668]** used 4x in this chunk (0x666d2d0, 0x666d373, 0x666d4aa, 0x666d9c8) - confirms it holds the description across complex control flow.
2. **Four vec4 at desc+0x18/+0x28/+0x38/+0x48** - only +0x18 explicitly read at 0x666d37a; others inferred from pattern in prior chunks (EffectDescriptions.h has mMatrix18 at +0x18 as four vec4).
3. **Two lookup tables** with different strides: 0x30 (desc+0x48/+0x52) and 0x10 (desc+0x38/+0x42, and again at +0x38/+0x42).
4. **desc+0xC8 byte flag** controls major branching at 0x666d9c0.
5. **String "fullscreen_cube_overlay"** at 0xF51E3D7 used in alternate path from 0x666cf0c.
6. **Frame ctx flag bytes at +0x1AC..0x1AF** parsed into bits at [rbp+0x3E0]/[rbp+0x3E1].
7. **Alloc paths** for rbx > 0xF (large) vs rbx <= 0xF (small inline).

---

### UNVERIFIED items in chunk 4
- [UNVERIFIED: 0x666d223] sub_666f4f3 - jump table exit
- [UNVERIFIED: 0x666d24f] sub_666f4ed - jump table exit
- [UNVERIFIED: 0x666d36d] sub_bcaba00 - signature, purpose
- [UNVERIFIED: 0x666d40c] sub_5679db0 - signature
- [UNVERIFIED: 0x666d4a4] sub_5679db0 - signature
- [UNVERIFIED: 0x666d4de] sub_bbd7c70 - signature
- [UNVERIFIED: 0x666d4ee] sub_4dedd00 - signature
- [UNVERIFIED: 0x666d607] sub_66a0f60 - render-state mapper, signature
- [UNVERIFIED: 0x666d6d3] sub_e869ff0 - signature
- [UNVERIFIED: 0x666d81a] jump table 0xF2BF4D0 - 4 cases
- [UNVERIFIED: 0x666d867] sub_e93bf00 - string "fullscreen_cube_overlay" processing
- [UNVERIFIED: 0x666d8e2] sub_e935700 - free
- [UNVERIFIED: 0x666d9ba] sub_6670d0a - thread-local exit
- [UNVERIFIED: 0x666d9fb] sub_6670f9a - thread-local exit
- [UNVERIFIED: 0x666dad4] sub_eea6040 alloc - large alloc
- [UNVERIFIED: 0x666dae3] sub_eea6040 alloc - small alloc
- [UNVERIFIED: 0x666db18] sub_9b020 - signature, purpose
- [UNVERIFIED: 0x666db20] sub_666fc9e - exit
- [UNVERIFIED: 0x666db2d] sub_666ddd1 - exit
- [UNVERIFIED: 0x666db37] sub_666ddd3 - exit
- [UNVERIFIED: 0x666db4f] sub_6671913 - exit
- [UNVERIFIED: 0x666db73] sub_eec6ec0 - memcpy
- [UNVERIFIED: 0x666db90] Chunk boundary - continues

---

### Chunk 5: 0x666db90..0x666e4a1 (500 instructions)

**Phase 35: 0x666db90..0x666dc97 — Pipeline setup (sub_9b020) + linked list init + element iteration**
```
0x666db90  mov r8,rbp                                    
0x666db93  call 0x9B020                                  ; -> sub_9b020 (pipeline setup)
0x666db98  nop                                           
0x666db99  cmp qword ptr [rbp+0x5D8],0x10                
0x666dba1  jb short 0x666DBAC                            ; -> loc_666dbac
0x666dba3  mov rax,[rbp+0x5C0]                           
0x666dbaa  jmp short 0x666DBB3                           ; -> loc_666dbb3

loc_666dbac:  ; from 666dba1
0x666dbac  lea rax,[rbp+0x5C0]                           

loc_666dbb3:  ; from 666dbaa
0x666dbb3  mov [rbp+0x660],rax                           
0x666dbba  mov r13,[r15+0x40]                            ; frame ctx+0x40
0x666dbbe  mov r12,[r15+0x68]                            ; frame ctx+0x68
0x666dbc2  mov rbx,[rbp+0x5D0]                           
0x666dbc9  mov eax,[rbp+0x5E0]                           
0x666dbcf  mov [rbp+0x300],eax                           
0x666dbd5  xorps xmm0,xmm0                               
0x666dbd8  movups [rbp+0x308],xmm0                       ; zero list head
0x666dbdf  mov rcx,[0x1233E1A8]                          ; allocator
0x666dbe6  mov rax,[rcx]                                 
0x666dbe9  mov rax,[rax+8]                               
0x666dbed  mov edx,0x50                                  
0x666dbf2  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc 0x50)
0x666dbf8  nop                                           
0x666dbf9  mov rsi,rax                                   
0x666dbfc  test rax,rax                                  
0x666dbff  je 0x66709B7                                  ; -> sub_66709b7
0x666dc05  mov [rsi],rsi                                 ; init circular list
0x666dc08  mov [rsi+8],rsi                               
0x666dc0c  mov [rbp+0x308],rsi                           ; list head
0x666dc13  lea rcx,[rbp+0x318]                           
0x666dc1a  xorps xmm0,xmm0                               
0x666dc1d  movups [rbp+0x318],xmm0                       ; zero
0x666dc24  mov qword ptr [rbp+0x328],0                   
0x666dc2f  movups xmm0,[rbp+0x610]                       ; copy xmm
0x666dc36  movups [rbp+0x330],xmm0                       
0x666dc3d  mov rdx,[rbp+0x600]                           ; buffer end
0x666dc44  sub rdx,[rbp+0x5F8]                           ; - buffer start
0x666dc4b  sar rdx,3                                     ; /8 (element count)
0x666dc4f  mov r8,rsi                                    
0x666dc52  call 0x76B30                                  ; -> sub_76b30 (process elements)
0x666dc57  nop                                           
0x666dc58  mov r14,[rbp+0x5E8]                           ; element list
0x666dc5f  mov r15,[r14]                                 ; first element
0x666dc62  cmp r15,r14                                   ; empty?
0x666dc65  je short 0x666DC98                            ; -> loc_666dc98
0x666dc67  lea rsi,[rbp+0x300]                           ; src
0x666dc6e  lea rdi,[rbp+0x3F0]                           ; dst

loc_666dc80:  ; from 666dc96 (element processing loop)
0x666dc80  lea r8,[r15+0x10]                             ; element+0x10
0x666dc84  mov rcx,rsi                                   
0x666dc87  mov rdx,rdi                                   
0x666dc8a  call 0xAA840                                  ; -> sub_aa840 (process element)
0x666dc8f  nop                                           
0x666dc90  mov r15,[r15]                                 ; next element (linked list)
0x666dc93  cmp r15,r14                                   ; back to head?
0x666dc96  jne short 0x666DC80                           ; -> loc_666dc80
```

**Phase 36: 0x666dc98..0x666dd70 — Pipeline execute (sub_66a02d0 + sub_67cfd80) + shared_ref chain**
```
loc_666dc98:  ; from 666dc65
0x666dc98  mov rax,[rbp+0x5D0]                           
0x666dc9f  cmp qword ptr [rbp+0x5D8],0x10                
0x666dca7  jb short 0x666DCB2                            ; -> loc_666dcb2
0x666dca9  mov rcx,[rbp+0x5C0]                           
0x666dcb0  jmp short 0x666DCB9                           ; -> loc_666dcb9

loc_666dcb2:  ; from 666dca7
0x666dcb2  lea rcx,[rbp+0x5C0]                           

loc_666dcb9:  ; from 666dcb0
0x666dcb9  lea rsi,[rbp+0x5E0]                           
0x666dcc0  lea rdi,[rbp+0x3F0]                           
0x666dcc7  mov [rbp+0x3D0],rcx                           
0x666dcce  mov [rbp+0x3D8],rax                           
0x666dcd5  mov rcx,rbp                                   
0x666dcd8  lea rdx,[rbp+0x3D0]                           
0x666dcdf  lea r8,[rbp+0x300]                            
0x666dce6  call 0x66A02D0                                ; -> sub_66a02d0 (pipeline exec)
0x666dceb  nop                                           
0x666dcec  mov rax,[rbp+0x660]                           
0x666dcf3  mov [rbp+0x3F0],rax                           
0x666dcfa  mov [rbp+0x3F8],rbx                           
0x666dd01  mov [rsp+0x28],rsi                            
0x666dd06  mov [rsp+0x20],rdi                            
0x666dd0b  lea rdx,[rbp+0x630]                           
0x666dd12  mov r8,rbp                                    
0x666dd15  mov rcx,r12                                   
0x666dd18  mov r9,r13                                    
0x666dd1b  call 0x67CFD80                                ; -> sub_67cfd80
0x666dd20  nop                                           
0x666dd21  lea rdi,[rbp+0x5F8]                           
0x666dd28  mov rsi,[rbp+0x630]                           ; shared_ref
0x666dd2f  mov rbx,[rsi]                                 
0x666dd32  test rbx,rbx                                  
0x666dd35  mov r15,[rbp+0x650]                           ; r15 = frame ctx
0x666dd3c  je 0x666E197                                  ; -> loc_666e197
0x666dd42  mov eax,[0x129CA5E0]                          ; thread-local
0x666dd48  mov ecx,[0x128767C8]                          
0x666dd4e  mov rdx,gs:[0x58]                             
0x666dd57  mov rcx,[rdx+rcx*8]                           
0x666dd5b  cmp eax,[rcx+4]                               
0x666dd61  jg 0x667105B                                  ; -> sub_667105b
0x666dd67  cmp byte ptr [rbx+0x10],1                     ; shared_ref+0x10 == 1?
0x666dd6b  jne 0x666E197                                 ; -> loc_666e197
0x666dd71  mov rax,[rsi+8]                               ; shared_ref chain
```

**Phase 37: 0x666dd71..0x666de56 — Shared_ref chain walk + string "ENABLE_VERTEX_TINT_MASK" + pipeline create**
```
0x666dd71  mov rax,[rsi+8]                               
0x666dd75  test rax,rax                                  
0x666dd78  je 0x666E111                                  ; -> loc_666e111
0x666dd7e  lock inc dword ptr [rax+8]                    
0x666dd82  mov rax,[rsi]                                 
0x666dd85  mov rsi,[rsi+8]                               
0x666dd89  mov rax,[rax+0x18]                            
0x666dd8d  mov rbx,[rax]                                 
0x666dd90  test rsi,rsi                                  
0x666dd93  je 0x666E11B                                  ; -> loc_666e11b
0x666dd99  lock dec dword ptr [rsi+8]                    
0x666dd9d  jne 0x666E11B                                 ; -> loc_666e11b
0x666dda3  mov rax,[rsi]                                 
0x666dda6  mov rax,[rax]                                 
0x666dda9  mov rcx,rsi                                   
0x666ddac  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666ddb2  lock dec dword ptr [rsi+0xC]                  
0x666ddb6  jne 0x666E11B                                 ; -> loc_666e11b
0x666ddbc  mov rax,[rsi]                                 
0x666ddbf  mov rax,[rax+8]                               
0x666ddc3  mov rcx,rsi                                   
0x666ddc6  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666ddcc  jmp 0x666E11B                                 ; -> loc_666e11b
```

**Phase 38: 0x666ddd1..0x666dfdf — Alternate path: alloc 0x20 + string "ENABLE_VERTEX_TINT_MASK" + hash "INT_MAP_TEXTURE"**
```
loc_666ddd1:  ; from 666db2d
0x666ddd1  xor edi,edi                                   
0x666ddd3  xorps xmm0,xmm0                               
0x666ddd6  movaps [rbp+0x400],xmm0                       
0x666dddd  movaps [rbp+0x3F0],xmm0                       
0x666dde4  mov rcx,[0x1233E1A8]                          ; allocator
0x666ddeb  mov rax,[rcx]                                 
0x666ddee  mov rax,[rax+8]                               
0x666ddf2  mov edx,0x20                                  
0x666ddf7  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc 0x20)
0x666ddfd  nop                                           
0x666ddfe  mov rsi,rax                                   
0x666de01  test rax,rax                                  
0x666de04  je 0x66709F3                                  ; -> sub_66709f3
0x666de0a  mov [rbp+0x3F0],rsi                           
0x666de11  mov qword ptr [rbp+0x400],0x17                
0x666de1c  mov qword ptr [rbp+0x408],0x1F                
0x666de27  movups xmm0,[0xF7CB18D]                       ; [data_f7cb18d] "ENABLE_VERTEX_TINT_MASK"
0x666de2e  movups [rsi],xmm0                             
0x666de31  mov rax,0x4B53414D5F544E49                    ; "INT_MAP_TEXTURE" (little-endian)
0x666de3b  mov [rsi+0xF],rax                             
0x666de3f  mov byte ptr [rsi+0x17],0                     
0x666de43  lea rcx,[rdi+0x98]                            
0x666de4a  lea rdx,[rbp+0x3F0]                           
0x666de51  call 0x358C40                                 ; -> sub_358c40 (hash lookup)
```

**Phase 39: 0x666de56..0x666dfdf — Buffer management + alloc 0x50 + string "On_VertexTintMaskBased" + hash "ABlksBase"**
```
0x666de56  mov rsi,rax                                   
0x666de59  mov rdi,[rdi+0x98]                            
0x666de60  mov rax,[rbp+0x408]                           
0x666de67  cmp rax,0x10                                  
0x666de6b  jb short 0x666DEA5                            ; -> loc_666dea5
... (buffer grow check to 0x666dea5)

loc_666dea5:  ; from 666de6b
0x666dea5  lea rax,[rbp+0x5E8]                           
0x666deac  cmp rsi,rdi                                   
0x666deaf  je 0x666DFDF                                  ; -> loc_666dfdf
0x666deb5  mov [rbp+0x3F0],rax                           
0x666debc  mov rcx,[0x1233E1A8]                          ; allocator
0x666dec3  mov rax,[rcx]                                 
0x666dec6  mov rax,[rax+8]                               
0x666deca  mov r8,[0xF99FFA0]                            ; sub_eea6040
0x666ded1  mov qword ptr [rbp+0x1C8],0                   
0x666dedc  mov edx,0x50                                  
0x666dee1  call r8                                       
0x666dee4  nop                                           
0x666dee5  mov rsi,rax                                   
0x666dee8  test rax,rax                                  
0x666deeb  je 0x6670A03                                  ; -> sub_6670a03
0x666def1  mov [rbp+0x3F8],rsi                           
0x666def8  mov rax,rsi                                   
0x666defb  add rax,0x10                                  
0x666deff  mov [rbp+0x660],rax                           
0x666df06  mov qword ptr [rsi+0x18],0                    
0x666df0e  mov qword ptr [rsi+0x20],9                    
0x666df16  mov qword ptr [rsi+0x28],0xF                  
0x666df1e  mov rax,0x7365546168706C41                    ; "ABlksBase"
0x666df28  mov [rsi+0x10],rax                            
0x666df2c  mov byte ptr [rsi+0x18],0x74                  
0x666df30  xorps xmm0,xmm0                               
0x666df33  movups [rsi+0x30],xmm0                        
0x666df37  mov [rbp+0x658],rsi                           
0x666df3e  movups [rsi+0x40],xmm0                        
0x666df42  mov rcx,[0x1233E1A8]                          ; allocator
0x666df49  mov rax,[rcx]                                 
0x666df4c  mov rax,[rax+8]                               
0x666df50  mov edx,0x20                                  
0x666df55  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc 0x20)
0x666df5b  nop                                           
0x666df5c  mov rsi,rax                                   
0x666df5f  test rax,rax                                  
0x666df62  je 0x6670A1E                                  ; -> sub_6670a1e
0x666df68  mov r14,[rbp+0x658]                           
0x666df6f  mov [r14+0x30],rsi                            
0x666df73  mov qword ptr [r14+0x40],0x16                 
0x666df7b  mov qword ptr [r14+0x48],0x1F                 
0x666df83  movups xmm0,[0xF5F4CFF]                       ; [data_f5f4cff] "On_VertexTintMaskBased"
0x666df8a  movups [rsi],xmm0                             
0x666df8d  mov rax,0x64657361426B7361                    ; "aBsakdes" (part of hash)
0x666df97  mov [rsi+0xE],rax                             
0x666df9b  mov byte ptr [rsi+0x16],0                     
0x666df9f  mov r12,[r14+0x20]                            
0x666dfa3  cmp qword ptr [r14+0x28],0x10                 
0x666dfa8  mov r13,[rbp+0x660]                           
0x666dfaf  jb short 0x666DFB5                            ; -> loc_666dfb5
0x666dfb1  mov r13,[r14+0x10]                            

loc_666dfb5:  ; from 666dfaf
0x666dfb5  test r12,r12                                  
0x666dfb8  je 0x666E102                                  ; -> loc_666e102
0x666dfbe  mov eax,r12d                                  
0x666dfc1  and eax,3                                     
0x666dfc4  cmp r12,4                                     
0x666dfc8  jae 0x666E2F7                                 ; -> loc_666e2f7
0x666dfce  mov rdi,0xCBF29CE484222325                    ; FNV offset basis
0x666dfd8  xor ecx,ecx                                   
0x666dfda  jmp 0x666E356                                 ; -> loc_666e356
```

**Phase 40: 0x666dfdf..0x666e102 — Alternate path: alloc + string "On_DiscardValueBased" + hash "aBdes"**
```
loc_666dfdf:  ; from 666deaf
0x666dfdf  mov [rbp+0x3F0],rax                           
0x666dfe6  mov rcx,[0x1233E1A8]                          ; allocator
... (similar alloc 0x50 + 0x20 pattern)
0x666e0ad  movups xmm0,[0xF5F4D16]                       ; [data_f5f4d16] "On_DiscardValueBased"
0x666e0b4  movups [rsi],xmm0                             
0x666e0b7  mov dword ptr [rsi+0x10],0x64657361           ; "ades" (part of hash)
0x666e0be  mov byte ptr [rsi+0x14],0                     
... (similar FNV hash computation)
0x666e0f1  mov rdi,0xCBF29CE484222325                    ; FNV offset basis
0x666e0fb  xor ecx,ecx                                   
0x666e0fd  jmp 0x666F0AD                                 ; -> loc_666f0ad

loc_666e102:  ; from 666dfb8
0x666e102  mov rdi,0xCBF29CE484222325                    ; FNV offset basis
0x666e10c  jmp 0x666E37E                                 ; -> loc_666e37e
```

**Phase 41: 0x666e111..0x666e21c — Shared_ref chain cleanup + buffer free (sub_e935700) + list cleanup (sub_9b250)**
```
loc_666e111:  ; from 666dd78
0x666e111  mov rax,[rsi]                                 
0x666e114  mov rax,[rax+0x18]                            
0x666e118  mov rbx,[rax]                                 

loc_666e11b:  ; from 666dd93, 666dd9d, 666ddb6, 666ddcc
0x666e11b  test rbx,rbx                                  
0x666e11e  je short 0x666E197                            ; -> loc_666e197
0x666e120  mov r14,[r15]                                 
0x666e123  mov rax,[rbp+0x630]                           
0x666e12a  xorps xmm0,xmm0                               
0x666e12d  movaps [rbp+0x3F0],xmm0                       
0x666e134  mov rcx,[rax+8]                               
0x666e138  test rcx,rcx                                  
0x666e13b  je 0x666EED3                                  ; -> loc_666eed3
... (shared_ref handling to 0x666e197)

loc_666e197:  ; from 666dd3c, 666dd6b, 666e11e
0x666e197  mov rsi,[rbp+0x638]                           ; shared_ref cleanup
... (refcount cleanup to 0x666e1ce)

loc_666e1ce:  ; from 666e1a1, 666e1a7, 666e1bc
0x666e1ce  mov rcx,[rbp+0x5F8]                           ; buffer base
0x666e1d5  test rcx,rcx                                  
0x666e1d8  je short 0x666E21C                            ; -> loc_666e21c
0x666e1da  mov rdx,[rbp+0x608]                           ; buffer end
0x666e1e1  sub rdx,rcx                                   
0x666e1e4  cmp rdx,0x1000                                
0x666e1eb  jb short 0x666E209                            ; -> loc_666e209
... (free large buffer via sub_e935700)

loc_666e209:  ; from 666e1eb
0x666e209  call 0xE935700                                ; -> sub_e935700
0x666e20e  xorps xmm0,xmm0                               
0x666e211  movups [rdi],xmm0                             
0x666e214  mov qword ptr [rdi+0x10],0                    

loc_666e21c:  ; from 666e1d8
0x666e21c  mov rax,[rbp+0x5E8]                           ; list head
0x666e223  mov rcx,[rax+8]                               
0x666e227  mov qword ptr [rcx],0                         
0x666e22e  mov rsi,[rax]                                 
0x666e231  test rsi,rsi                                  

loc_666e240:  ; from 666e25f (list cleanup loop)
0x666e240  mov rdi,[rsi]                                 
0x666e243  lea rcx,[rsi+0x10]                            
0x666e247  call 0x9B250                                  ; -> sub_9b250 (cleanup element)
0x666e24c  mov edx,0x50                                  
0x666e251  mov rcx,rsi                                   
0x666e254  call 0xE935700                                ; -> sub_e935700 (free element)
0x666e259  mov rsi,rdi                                   
0x666e25c  test rdi,rdi                                  
0x666e25f  jne short 0x666E240                           ; -> loc_666e240
```

**Phase 42: 0x666e261..0x666e4a1 — Final buffer free + FNV hash computation + hash table lookup**
```
loc_666e261:  ; from 666e234
0x666e261  mov rcx,[rbp+0x5E8]                           ; list head
0x666e268  mov edx,0x50                                  
0x666e26d  call 0xE935700                                ; -> sub_e935700 (free head)
0x666e272  mov rax,[rbp+0x5D8]                           ; size
0x666e279  cmp rax,0x10                                  
0x666e27d  jb 0x6670032                                  ; -> sub_6670032 (EXIT)
0x666e283  mov rcx,[rbp+0x5C0]                           ; buffer base
0x666e28a  lea rdx,[rax+1]                               
0x666e28e  cmp rdx,0x1000                                
0x666e295  jb 0x667002D                                  ; -> sub_667002d
... (free large buffer)

0x666e2bf  lea rdx,[rbp+0x368]                           
0x666e2c6  movups xmm0,[rdx]                             
0x666e2c9  movups [rcx],xmm0                             
0x666e2cc  jmp 0x666F4ED                                 ; -> loc_666f4ed
0x666e2d1  xorps xmm0,xmm0                               
0x666e2d4  movups [rcx],xmm0                             
0x666e2d7  mov rcx,[rbp+0x370]                           
0x666e2de  test rcx,rcx                                  
0x666e2e1  je 0x666F4D6                                  ; -> loc_666f4d6
0x666e2e7  lock inc dword ptr [rcx+8]                    
0x666e2eb  mov rcx,[rbp+0x370]                           
0x666e2f2  jmp 0x666F4D8                                 ; -> loc_666f4d8

loc_666e2f7:  ; from 666dfc8, 666e0eb (FNV-1a 64 hash computation)
0x666e2f7  mov rdx,r12                                   
0x666e2fa  and rdx,0xFFFFFFFFFFFFFFFC                    ; align 4
0x666e2fe  mov rdi,0xCBF29CE484222325                    ; FNV offset basis
0x666e308  xor ecx,ecx                                   
0x666e30a  mov r8,0x100000001B3                          ; FNV prime

loc_666e314:  ; from 666e34f (hash loop, 4 bytes at a time)
0x666e314  movzx r9d,byte ptr [r13+rcx]                  
0x666e31a  xor r9,rdi                                    
0x666e31d  imul r9,r8                                    
0x666e321  movzx r10d,byte ptr [r13+rcx+1]               
0x666e327  xor r10,r9                                    
0x666e32a  imul r10,r8                                   
0x666e32e  movzx r9d,byte ptr [r13+rcx+2]                
0x666e334  xor r9,r10                                    
0x666e337  imul r9,r8                                    
0x666e33b  movzx edi,byte ptr [r13+rcx+3]                
0x666e341  xor rdi,r9                                    
0x666e344  imul rdi,r8                                   
0x666e348  add rcx,4                                     
0x666e34c  cmp rdx,rcx                                   
0x666e34f  jne short 0x666E314                           ; -> loc_666e314
0x666e351  test rax,rax                                  
0x666e354  je short 0x666E37E                            ; -> loc_666e37e

loc_666e356:  ; from 666dfda, 666e0fd (hash remainder bytes)
0x666e356  add rcx,r13                                   
0x666e359  xor edx,edx                                   
0x666e35b  mov r8,0x100000001B3                          ; FNV prime
0x666e365  mov r9,rdi                                    

loc_666e368:  ; from 666e37c
0x666e368  movzx edi,byte ptr [rcx+rdx]                  
0x666e36c  xor rdi,r9                                    
0x666e36f  imul rdi,r8                                   
0x666e373  inc rdx                                       
0x666e376  mov r9,rdi                                    
0x666e379  cmp rax,rdx                                   
0x666e37c  jne short 0x666E368                           ; -> loc_666e368

loc_666e37e:  ; from 666e10c, 666e354 (hash table lookup)
0x666e37e  mov rcx,[rbp+0x610]                           ; hash mask
0x666e385  and rcx,rdi                                   
0x666e388  mov rax,[rbp+0x5E8]                           ; table base
0x666e38f  mov rdx,[rbp+0x5F8]                           ; table
0x666e396  shl rcx,4                                     ; *16 (entry size)
0x666e39a  mov rsi,[rdx+rcx+8]                           ; entry.value
0x666e39f  cmp rsi,rax                                   
0x666e3a2  je short 0x666E400                            ; -> loc_666e400 (found)
0x666e3a4  mov rbx,[rdx+rcx]                             
0x666e3a8  test r12,r12                                  
0x666e3ab  je short 0x666E3F1                            ; -> loc_666e3f1
0x666e3ad  cmp r12,[rsi+0x20]                            

loc_666e3b3:  ; from 666e3e4 (collision chain walk)
0x666e3b3  cmp qword ptr [rsi+0x28],0x10                 
0x666e3b8  jb short 0x666E3C0                            ; -> loc_666e3c0
0x666e3ba  mov rdx,[rsi+0x10]                            
0x666e3be  jmp short 0x666E3C4                           ; -> loc_666e3c4

loc_666e3c0:  ; from 666e3b8
0x666e3c0  lea rdx,[rsi+0x10]                            

loc_666e3c4:  ; from 666e3be
0x666e3c4  mov rcx,r13                                   
0x666e3c7  mov r8,r12                                    
0x666e3ca  call 0xEEC6EB0                                ; -> sub_eec6eb0 (memcmp)
0x666e3cf  test eax,eax                                  
0x666e3d1  je 0x666FC88                                  ; -> sub_666fc88

loc_666e3d7:  ; from 666e3b1, 666e3e6 (next in chain)
0x666e3d7  cmp rsi,rbx                                   
0x666e3da  je short 0x666E3FD                            ; -> loc_666e3fd
0x666e3dc  mov rsi,[rsi+8]                               
0x666e3e0  cmp r12,[rsi+0x20]                            
0x666e3e4  je short 0x666E3B3                            ; -> loc_666e3b3
0x666e3e6  jmp short 0x666E3D7                           ; -> loc_666e3d7

loc_666e3e8:  ; from 666e3f6
0x666e3e8  cmp rsi,rbx                                   
0x666e3eb  je short 0x666E3FD                            ; -> loc_666e3fd
0x666e3ed  mov rsi,[rsi+8]                               

loc_666e3f1:  ; from 666e3ab
0x666e3f1  cmp qword ptr [rsi+0x20],0                    
0x666e3f6  jne short 0x666E3E8                           ; -> loc_666e3e8
0x666e3f8  jmp 0x666FC88                                 ; -> sub_666fc88

loc_666e3fd:  ; from 666e3da, 666e3eb
0x666e3fd  mov rax,rsi                                   

loc_666e400:  ; from 666e3a2 (found)
0x666e400  mov rcx,[rbp+0x5F0]                           ; counter
0x666e407  mov rdx,0x333333333333333                     
0x666e411  cmp rcx,rdx                                   
0x666e414  je 0x6671102                                  ; -> sub_6671102
0x666e41a  inc rcx                                       
0x666e41d  js short 0x666E429                            ; -> loc_666e429
0x666e41f  xorps xmm0,xmm0                               
0x666e422  cvtsi2ss xmm0,rcx                             
0x666e427  jmp short 0x666E441                           ; -> loc_666e441

loc_666e429:  ; from 666e41d
0x666e429  mov rdx,rcx                                   
0x666e42c  shr rdx,1                                     
0x666e42f  and ecx,1                                     
0x666e432  or rcx,rdx                                    
0x666e435  xorps xmm0,xmm0                               
0x666e438  cvtsi2ss xmm0,rcx                             
0x666e43d  addss xmm0,xmm0                               

loc_666e441:  ; from 666e427
0x666e441  movss xmm1,[rbp+0x5E0]                        ; threshold
0x666e449  mov rsi,[rbp+0x618]                           ; signed counter
0x666e450  test rsi,rsi                                  
0x666e453  js short 0x666E45C                            ; -> loc_666e45c
0x666e455  cvtsi2ss xmm2,rsi                             
0x666e45a  jmp short 0x666E473                           ; -> loc_666e473

loc_666e45c:  ; from 666e453
0x666e45c  mov rcx,rsi                                   
0x666e45f  shr rcx,1                                     
0x666e462  mov edx,esi                                   
0x666e464  and edx,1                                     
0x666e467  or rdx,rcx                                    
0x666e46a  cvtsi2ss xmm2,rdx                             
0x666e46f  addss xmm2,xmm2                               

loc_666e473:  ; from 666e45a
0x666e473  movaps xmm3,xmm0                              
0x666e476  divss xmm3,xmm2                               
0x666e47a  ucomiss xmm3,xmm1                             
0x666e47d  jbe 0x666FBCA                                 ; -> sub_666fbca
0x666e483  divss xmm0,xmm1                               
0x666e487  call 0xEEC73F0                                ; -> sub_eec73f0
0x666e48c  cvttss2si rax,xmm0                            
0x666e491  mov rcx,rax                                   
0x666e494  subss xmm0,[0xEEE6700]                        ; [data_eee6700] constant
0x666e49c  cvttss2si rdx,xmm0                            
0x666e4a1  sar rcx,0x3F                                  
```

---

### Description fields READ in chunk 5 (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x40  | 8    | R      | frame ctx+0x40 -> r13 | 7 | 0x666dbba `mov r13,[r15+0x40]` |
| +0x68  | 8    | R      | frame ctx+0x68 -> r12 | 7 | 0x666dbbe `mov r12,[r15+0x68]` |
| +0x5D0 | 8    | R      | rbp+0x5D0 -> rbx | 7 | 0x666dbc2 `mov rbx,[rbp+0x5D0]` |
| +0x5E0 | 4    | R      | rbp+0x5E0 -> eax | 7 | 0x666dbc9 `mov eax,[rbp+0x5E0]` |
| +0x610 | 16   | R      | rbp+0x610 -> xmm0 | 7 | 0x666dc2f `movups xmm0,[rbp+0x610]` |
| +0x600 | 8    | R      | rbp+0x600 (buffer end) | 7 | 0x666dc3d `mov rdx,[rbp+0x600]` |
| +0x5F8 | 8    | R      | rbp+0x5F8 (buffer start) | 7 | 0x666dc44 `sub rdx,[rbp+0x5F8]` |
| +0x5E8 | 8    | R      | rbp+0x5E8 (element list head) | 7 | 0x666dc58 `mov r14,[rbp+0x5E8]` |
| +0x630 | 8    | R      | rbp+0x630 (shared_ref) | 7 | 0x666dd28 `mov rsi,[rbp+0x630]` |
| +0x650 | 8    | R      | rbp+0x650 (frame ctx) | 7 | 0x666dd35 `mov r15,[rbp+0x650]` |
| +0x5F0 | 8    | R      | rbp+0x5F0 (counter) | 7 | 0x666e400 `mov rcx,[rbp+0x5F0]` |
| +0x5E0 | 4    | R      | rbp+0x5E0 (threshold float) | 7 | 0x666e441 `movss xmm1,[rbp+0x5E0]` |
| +0x618 | 8    | R      | rbp+0x618 (signed counter) | 7 | 0x666e449 `mov rsi,[rbp+0x618]` |
| +0x368 | 16   | R      | rbp+0x368 (xmm) | 7 | 0x666e2c6 `movups xmm0,[rdx]` |
| +0x370 | 8    | R      | rbp+0x370 (shared_ref) | 7 | 0x666e2d7 `mov rcx,[rbp+0x370]` |

**Frame ctx (r15) fields:**
- r15+0x40 at 0x666dbba
- r15+0x68 at 0x666dbbe

**Global strings / constants:**
- 0xF7CB18D "ENABLE_VERTEX_TINT_MASK"
- 0xF5F4CFF "On_VertexTintMaskBased"
- 0xF5F4D16 "On_DiscardValueBased"
- 0xCBF29CE484222325 FNV-1a 64 offset basis
- 0x100000001B3 FNV-1a 64 prime
- 0xEEE6700 constant for subss

**Callees (new in chunk 5):**
- 0x9B020 (sub_9b020) - pipeline setup
- 0x76B30 (sub_76b30) - element processing
- 0xAA840 (sub_aa840) - per-element callback
- 0x66A02D0 (sub_66a02d0) - pipeline execute
- 0x67CFD80 (sub_67cfd80) - pipeline stage
- 0x358C40 (sub_358c40) - hash lookup
- 0x9B250 (sub_9b250) - element cleanup
- 0xEEC6EB0 (sub_eec6eb0) - memcmp for hash
- 0xEEC73F0 (sub_eec73f0) - float math
- 0x66709B7, 0x667105B, 0x66709F3, 0x6670A03, 0x6670A1E, 0x6670A41, 0x6670A5C, 0x6671102, 0x666EED3, 0x666EEE8, 0x666E11B, 0x666E197, 0x666E102, 0x666E2F7, 0x666E37E, 0x666F0AD, 0x666F4ED, 0x666F4D6, 0x666F4D8, 0x666FC88, 0x666FB CA - various exits
- 0xE935700 (sub_e935700) - free (many)
- 0xEEA6040 (via 0xF99FFA0) - alloc/destroy

**Key insights:**
1. **FNV-1a 64 hash computation** at 0x666e2f7..0x666e37d - standard algorithm with offset basis 0xCBF29CE484222325 and prime 0x100000001B3
2. **Hash table lookup** at 0x666e37e..0x666e4a1 with chaining (entry size 0x10, value at +8, key at +0x10 or +0x18)
3. **Two pipeline paths** with different strings: "ENABLE_VERTEX_TINT_MASK" -> "INT_MAP_TEXTURE" -> "ABlksBase" / "On_VertexTintMaskBased" and "On_DiscardValueBased" -> "ades"
4. **Element linked list** at rbp+0x5E8 processed via sub_76b30 and sub_aa840
5. **Buffer management** with small (<=0x10) inline vs large (heap) allocation
6. **Shared_ref chain walk** at 0x666dd71..0x666ddcc with refcount handling
7. **Threshold comparison** using float division at 0x666e473..0x666e4a1

---

### UNVERIFIED items in chunk 5
- [UNVERIFIED: 0x666db93] sub_9b020 - pipeline setup, signature
- [UNVERIFIED: 0x666dc52] sub_76b30 - element processing, signature
- [UNVERIFIED: 0x666dc8a] sub_aa840 - per-element callback, signature
- [UNVERIFIED: 0x666dce6] sub_66a02d0 - pipeline execute, signature
- [UNVERIFIED: 0x666dd1b] sub_67cfd80 - pipeline stage, signature
- [UNVERIFIED: 0x666de51] sub_358c40 - hash lookup, signature
- [UNVERIFIED: 0x666e247] sub_9b250 - element cleanup, signature
- [UNVERIFIED: 0x666e3ca] sub_eec6eb0 - memcmp, signature
- [UNVERIFIED: 0x666e487] sub_eec73f0 - float math, signature
- [UNVERIFIED: 0x666e4a1] Chunk boundary - continues

---

### Chunk 6: 0x666e4a1..0x666edd6 (500 instructions)

**Phase 43: 0x666e4a1..0x666e5b1 — Hash table clamp + second hash lookup (sub_77d80) + collision chain walk**
```
0x666e4a1  sar rcx,0x3F                                  
0x666e4a5  and rdx,rcx                                   
0x666e4a8  or rdx,rax                                    
0x666e4ab  cmp rdx,9                                     
0x666e4af  mov eax,8                                     
0x666e4b4  cmovae rax,rdx                                
0x666e4b8  cmp rsi,rax                                   
0x666e4bb  jae short 0x666E4DA                           ; -> loc_666e4da
0x666e4bd  lea rcx,[rsi*8]                               
0x666e4c5  cmp rcx,rax                                   
0x666e4c8  cmovbe rcx,rax                                
0x666e4cc  cmp rsi,0x200                                 
0x666e4d3  cmovae rcx,rax                                
0x666e4d7  mov rsi,rcx                                   

loc_666e4da:  ; from 666e4bb
0x666e4da  lea rcx,[rbp+0x5E0]                           
0x666e4e1  mov rdx,rsi                                   
0x666e4e4  call 0x77D80                                  ; -> sub_77d80
0x666e4e9  nop                                           
0x666e4ea  mov rcx,[rbp+0x610]                           ; hash mask
0x666e4f1  and rcx,rdi                                   
0x666e4f4  mov rax,[rbp+0x5E8]                           ; table base
0x666e4fb  mov rdx,[rbp+0x5F8]                           ; table
0x666e502  shl rcx,4                                     ; *16 (entry size)
0x666e506  mov rbx,[rdx+rcx+8]                           ; entry.value
0x666e50b  cmp rbx,rax                                   
0x666e50e  je 0x666FBCA                                  ; -> loc_666fbca
0x666e514  mov rsi,[r14+0x20]                            
0x666e518  cmp qword ptr [r14+0x28],0x10                 
0x666e51d  jb short 0x666E531                            ; -> loc_666e531
0x666e51f  mov rax,[rbp+0x658]                           
0x666e526  mov rax,[rax+0x10]                            
0x666e52a  mov [rbp+0x660],rax                           

loc_666e531:  ; from 666e51d
0x666e531  mov r15,[rdx+rcx]                             
0x666e535  test rsi,rsi                                  
0x666e538  je short 0x666E57D                            ; -> loc_666e57d
0x666e53a  cmp rsi,[rbx+0x20]                            
0x666e53e  jne short 0x666E568                           ; -> loc_666e568

loc_666e540:  ; from 666e575
0x666e540  cmp qword ptr [rbx+0x28],0x10                 
0x666e545  jb short 0x666E54D                            ; -> loc_666e54d
0x666e547  mov rdx,[rbx+0x10]                            
0x666e54b  jmp short 0x666E551                           ; -> loc_666e551

loc_666e54d:  ; from 666e545
0x666e54d  lea rdx,[rbx+0x10]                            

loc_666e551:  ; from 666e54b
0x666e551  mov rcx,[rbp+0x660]                           
0x666e558  mov r8,rsi                                    
0x666e55b  call 0xEEC6EB0                                ; -> sub_eec6eb0 (memcmp)
0x666e560  test eax,eax                                  
0x666e562  je 0x666FBC0                                  ; -> loc_666fbc0

loc_666e568:  ; from 666e53e, 666e577
0x666e568  cmp rbx,r15                                   
0x666e56b  je short 0x666E58D                            ; -> loc_666e58d
0x666e56d  mov rbx,[rbx+8]                               
0x666e571  cmp rsi,[rbx+0x20]                            
0x666e575  je short 0x666E540                            ; -> loc_666e540
0x666e577  jmp short 0x666E568                           ; -> loc_666e568

loc_666e579:  ; from 666e58b
0x666e579  mov rbx,[rbx+8]                               

loc_666e57d:  ; from 666e538
0x666e57d  cmp qword ptr [rbx+0x20],0                    
0x666e582  je 0x666FBC0                                  ; -> loc_666fbc0
0x666e588  cmp rbx,r15                                   
0x666e58b  jne short 0x666E579                           ; -> loc_666e579

loc_666e58d:  ; from 666e56b
0x666e58d  mov rax,rbx                                   
0x666e590  jmp 0x666FBC3                                 ; -> loc_666fbc3
```

**Phase 44: 0x666e595..0x666e649 — Jump table case 2 (from 0x666d84c) + sub_67eab80 + sub_66a6470 + shared_ref cleanup**
```
0x666e595  xor ecx,ecx                                   ; case 2 entry
0x666e597  mov rdx,[rbp+0x1F8]                           
0x666e59e  mov [rbp+0x558],rdx                           
0x666e5a5  mov [rbp+0x560],rcx                           
0x666e5ac  mov [rbp+0x568],al                            
0x666e5b2  mov rax,[rbp+0x220]                           
0x666e5b9  mov [rbp+0x580],rax                           
0x666e5c0  movaps xmm0,[rbp+0x210]                       
0x666e5c7  movups [rbp+0x570],xmm0                       
0x666e5ce  lea rdx,[rbp+0x588]                           
0x666e5d5  mov [rbp+0x588],si                            
0x666e5dc  mov ecx,0x9D0                                 
0x666e5e1  add rcx,[r12+0x10]                            
0x666e5e6  mov [rsp+0x30],rdi                            
0x666e5eb  mov [rsp+0x28],r10                            
0x666e5f0  mov [rsp+0x20],r11                            
0x666e5f5  call 0x67EAB80                                ; -> sub_67eab80
0x666e5fa  nop                                           
0x666e5fb  lea r14,[rbp+0x3F0]                           
0x666e602  mov rcx,r14                                   
0x666e605  call 0x66A6470                                ; -> sub_66a6470
0x666e60a  cmp byte ptr [rbp+0x208],3                    
0x666e611  jne short 0x666E64A                           ; -> loc_666e64a
0x666e613  mov rsi,[rbp+0x200]                           
0x666e61a  test rsi,rsi                                  
0x666e61d  je short 0x666E64A                            ; -> loc_666e64a
0x666e61f  lock dec dword ptr [rsi+8]                    
0x666e623  jne short 0x666E64A                           ; -> loc_666e64a
0x666e625  mov rax,[rsi]                                 
0x666e628  mov rax,[rax]                                 
0x666e62b  mov rcx,rsi                                   
0x666e62e  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666e634  lock dec dword ptr [rsi+0xC]                  
0x666e638  jne short 0x666E64A                           ; -> loc_666e64a
0x666e63a  mov rax,[rsi]                                 
0x666e63d  mov rax,[rax+8]                               
0x666e641  mov rcx,rsi                                   
0x666e644  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
```

**Phase 45: 0x666e64a..0x666e6f4 — Array cleanup (rbp+0x1D8, stride 0x28, filter byte+0x18==2) + buffer free**
```
loc_666e64a:  ; from 666e611, 666e61d, 666e623, 666e638
0x666e64a  mov rbx,[rbp+0x1D8]                           
0x666e651  test rbx,rbx                                  
0x666e654  je short 0x666E6A5                            ; -> loc_666e6a5
0x666e656  mov r15,[rbp+0x1E0]                           
0x666e65d  jmp short 0x666E664                           ; -> loc_666e664
0x666e65f  nop                                           

loc_666e660:  ; from 666e66d, 666e676, 666e67c, 666e691, 666e6a3
0x666e660  add rbx,0x28                                  ; stride 0x28

loc_666e664:  ; from 666e65d
0x666e664  cmp rbx,r15                                   
0x666e667  je short 0x666E6A5                            ; -> loc_666e6a5
0x666e669  cmp byte ptr [rbx+0x18],2                     ; filter: byte+0x18 == 2
0x666e66d  jne short 0x666E660                           ; -> loc_666e660
0x666e66f  mov rsi,[rbx+8]                               ; shared_ref at +8
0x666e673  test rsi,rsi                                  
0x666e676  je short 0x666E660                            ; -> loc_666e660
0x666e678  lock dec dword ptr [rsi+8]                    ; cleanup
0x666e67c  jne short 0x666E660                           ; -> loc_666e660
0x666e67e  mov rax,[rsi]                                 
0x666e681  mov rax,[rax]                                 
0x666e684  mov rcx,rsi                                   
0x666e687  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666e68d  lock dec dword ptr [rsi+0xC]                  
0x666e691  jne short 0x666E660                           ; -> loc_666e660
0x666e693  mov rax,[rsi]                                 
0x666e696  mov rax,[rax+8]                               
0x666e69a  mov rcx,rsi                                   
0x666e69d  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666e6a3  jmp short 0x666E660                           ; -> loc_666e660

loc_666e6a5:  ; from 666e654, 666e667
0x666e6a5  cmp byte ptr [rbp+0x380],1                    
0x666e6ac  mov rsi,[rbp+0x668]                           ; SHARED SPILL SLOT = description
0x666e6b3  jne short 0x666E6F5                           ; -> loc_666e6f5
0x666e6b5  mov rcx,[rbp+0x340]                           ; buffer base
0x666e6bc  test rcx,rcx                                  
0x666e6bf  je short 0x666E6F5                            ; -> loc_666e6f5
0x666e6c1  mov rdx,[rbp+0x350]                           ; buffer end
0x666e6c8  sub rdx,rcx                                   
0x666e6cb  cmp rdx,0x1000                                
0x666e6d2  jb short 0x666E6F0                            ; -> loc_666e6f0
0x666e6d4  mov rax,[rcx-8]                               
0x666e6d8  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666e6dc  sub rcx,rax                                   
0x666e6df  cmp rcx,0x20                                  
0x666e6e3  jae 0x6670A7A                                 ; -> sub_6670a7a
0x666e6e9  or rdx,0x27                                   
0x666e6ed  mov rcx,rax                                   

loc_666e6f0:  ; from 666e6d2
0x666e6f0  call 0xE935700                                ; -> sub_e935700 (free)
```

**Phase 46: 0x666e6f5..0x666e7e0 — desc+0x84 -> r15d + desc+0x48/+0x52 lookup (stride 0x30) + call 0xBCABA00**
```
loc_666e6f5:  ; from 666e6b3, 666e6bf
0x666e6f5  mov r15d,[rsi+0x84]                           ; description+0x84
0x666e6fc  mov r13,r12                                   ; r13 = frame ctx
0x666e6ff  mov r12,[r12]                                 ; r12 = frame ctx+0
0x666e703  mov rax,[rbp+0x5C0]                           ; shared_ref
0x666e70a  xorps xmm0,xmm0                               
0x666e70d  movaps [rbp+0x3F0],xmm0                       
0x666e714  mov rcx,[rax+8]                               ; ctrl
0x666e718  test rcx,rcx                                  
0x666e71b  je short 0x666E764                            ; -> loc_666e764
0x666e71d  lock inc dword ptr [rcx+8]                    
0x666e721  mov rsi,[rbp+0x3F8]                           ; old ref
0x666e728  movups xmm0,[rax]                             ; copy shared_ref
0x666e72b  movaps [rbp+0x3F0],xmm0                       
0x666e732  test rsi,rsi                                  
0x666e735  je short 0x666E779                            ; -> loc_666e779
0x666e737  lock dec dword ptr [rsi+8]                    
0x666e73b  jne short 0x666E779                           ; -> loc_666e779
0x666e73d  mov rax,[rsi]                                 
0x666e740  mov rax,[rax]                                 
0x666e743  mov rcx,rsi                                   
0x666e746  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666e74c  lock dec dword ptr [rsi+0xC]                  
0x666e750  jne short 0x666E779                           ; -> loc_666e779
0x666e752  mov rax,[rsi]                                 
0x666e755  mov rax,[rax+8]                               
0x666e759  mov rcx,rsi                                   
0x666e75c  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666e762  jmp short 0x666E779                           ; -> loc_666e779

loc_666e764:  ; from 666e71b
0x666e764  mov rax,[rax]                                 
0x666e767  mov [rbp+0x3F0],rax                           
0x666e76e  mov qword ptr [rbp+0x3F8],0                   

loc_666e779:  ; from 666e735, 666e73b, 666e750, 666e762
0x666e779  mov rax,[rbp+0x3F0]                           
0x666e780  mov rax,[rax+0x18]                            
0x666e784  mov rax,[rax]                                 
0x666e787  mov [rbp],rax                                 
0x666e78b  lea rbx,[rbp+8]                               
0x666e78f  mov r8,[r12]                                  ; r12 = frame ctx
0x666e793  mov rdx,[rax+0x170]                           ; mesh+0x170
0x666e79a  mov rcx,rbx                                   
0x666e79d  call 0xE86B370                                ; -> sub_e86b370
0x666e7a2  nop                                           
0x666e7a3  mov [rbp+0x80],r12                            
0x666e7aa  mov rsi,[rbp+0x3F8]                           ; shared_ref cleanup
... (refcount cleanup to 0x666e7e1)

loc_666e7e1:  ; from 666e7b4, 666e7ba, 666e7cf
0x666e7e1  mov rax,[rbp+0x48]                            ; base for lookup
0x666e7e5  movzx r8d,word ptr [rbp+0x52]                 ; count
0x666e7ea  mov ecx,r8d                                   
0x666e7ed  shl ecx,4                                     
0x666e7f0  lea rdx,[rcx+rcx*2]                           ; *0x30 stride
0x666e7f4  mov rcx,rax                                   
0x666e7f7  test r8,r8                                    
0x666e7fa  je short 0x666E825                            ; -> loc_666e825
0x666e7fc  mov r8,[0x129FA148]                           ; [data_129fa148] lookup table
0x666e803  mov r9,rdx                                    
0x666e806  mov rcx,rax                                   
0x666e809  nop [rax]                                     

loc_666e810:  ; from 666e821
0x666e810  mov r10,[rcx]                                 
0x666e813  cmp [r10+0x28],r8                             
0x666e817  je short 0x666E825                            ; -> loc_666e825 (found)
0x666e819  add rcx,0x30                                  
0x666e81d  add r9,0xFFFFFFFFFFFFFFD0                     
0x666e821  jne short 0x666E810                           ; -> loop

loc_666e823  jmp short 0x666E873                           ; -> loc_666e873 (not found)

loc_666e825:  ; from 666e7fa, 666e817
0x666e825  add rdx,rax                                   
0x666e828  cmp rcx,rdx                                   
0x666e82b  jae short 0x666E873                           ; -> loc_666e873
0x666e82d  sub ecx,eax                                   
0x666e82f  shr ecx,4                                     
0x666e832  imul eax,ecx,0xFFFFAAAB                       ; /0x30
0x666e838  mov [rbp+0x1D0],ax                            
0x666e83f  mov byte ptr [rbp+0x1D2],1                    
0x666e846  mov byte ptr [rbp+0x3FC],0                    
0x666e84d  mov dword ptr [rsp+0x20],0                    
0x666e855  mov rcx,rbp                                   
0x666e858  lea rdx,[rbp+0x1D0]                           
0x666e85f  lea r9,[rbp+0x3F0]                            
0x666e866  mov r8,[rbp+0x670]                            
0x666e86d  call 0xBCABA00                                ; -> sub_bcaba00
0x666e872  nop                                           
```

**Phase 47: 0x666e873..0x666e9a9 — desc+0x18/+0x38/+0x58/+0x78 (four vec4) + second lookup (stride 0x10) + third lookup (stride 0x10)**
```
loc_666e873:  ; from 666e823, 666e82b
0x666e873  mov rax,[rbp+0x668]                           ; restore description
0x666e87a  movups xmm0,[rax+0x18]                        ; desc+0x18 (first vec4)
0x666e87e  movaps [rbp+0x3F0],xmm0                       
0x666e885  mov qword ptr [rbp+0x1D0],1                   
0x666e890  mov [rbp+0x1D8],r14                           
0x666e897  mov rax,[rbp+0x38]                            
0x666e89b  movzx edx,word ptr [rbp+0x42]                 
0x666e89f  mov ecx,edx                                   
0x666e8a1  shl ecx,4                                     
0x666e8a4  mov r8,rax                                    
0x666e8a7  test edx,edx                                  
0x666e8a9  je short 0x666E8DC                            ; -> loc_666e8dc
0x666e8ab  mov r9,[0x129FA158]                           ; [data_129fa158] lookup table
0x666e8b2  xor r8d,r8d                                   

loc_666e8c0:  ; from 666e8d1
0x666e8c0  mov r10,[rax+r8]                              
0x666e8c4  cmp [r10+0x28],r9                             
0x666e8c8  je short 0x666E8D9                            ; -> loc_666e8d9 (found)
0x666e8ca  add r8,0x10                                   
0x666e8ce  cmp rcx,r8                                    
0x666e8d1  jne short 0x666E8C0                           ; -> loop

loc_666e8d3  mov dx,1                                    
0x666e8d7  jmp short 0x666E91F                           ; -> loc_666e91f

loc_666e8d9:  ; from 666e8c8
0x666e8d9  add r8,rax                                    

loc_666e8dc:  ; from 666e8a9
0x666e8dc  lea r9,[rax+rcx]                              
0x666e8e0  cmp r8,r9                                     
0x666e8e3  jae short 0x666E91F                           ; -> loc_666e91f
0x666e8e5  sub r8d,eax                                   
0x666e8e8  shr r8d,4                                     
0x666e8ec  mov [rbp+0x340],r8w                           
0x666e8f4  mov byte ptr [rbp+0x342],1                    
0x666e8fb  lea rdx,[rbp+0x340]                           
0x666e902  lea r8,[rbp+0x1D0]                            
0x666e909  mov rcx,rbx                                   
0x666e90c  call 0x5679DB0                                ; -> sub_5679db0
0x666e911  nop                                           
0x666e912  mov rax,[rbp+0x38]                            
0x666e916  movzx edx,word ptr [rbp+0x42]                 
0x666e91a  mov ecx,edx                                   
0x666e91c  shl ecx,4                                     

loc_666e91f:  ; from 666e8d7, 666e8e3
0x666e91f  movaps xmm0,[0xEF40DE0]                       ; [data_ef40de0] constant
0x666e926  movaps [rbp+0x3F0],xmm0                       
0x666e92d  mov qword ptr [rbp+0x1D0],1                   
0x666e938  mov [rbp+0x1D8],r14                           
0x666e93f  mov r8,rax                                    
0x666e942  test dx,dx                                    
0x666e945  je short 0x666E975                            ; -> loc_666e975
0x666e947  mov rdx,[0x129FA168]                          ; [data_129fa168] lookup table
0x666e94e  mov r9,rcx                                    
0x666e951  mov r8,rax                                    

loc_666e960:  ; from 666e971
0x666e960  mov r10,[r8]                                  
0x666e963  cmp [r10+0x28],rdx                            
0x666e967  je short 0x666E975                            ; -> loc_666e975 (found)
0x666e969  add r8,0x10                                   
0x666e96d  add r9,0xFFFFFFFFFFFFFFF0                     
0x666e971  jne short 0x666E960                           ; -> loop

loc_666e973  jmp short 0x666E9AA                           ; -> loc_666e9aa (not found)

loc_666e975:  ; from 666e945, 666e967
0x666e975  add rcx,rax                                   
0x666e978  cmp r8,rcx                                    
0x666e97b  jae short 0x666E9AA                           ; -> loc_666e9aa
0x666e97d  sub r8d,eax                                   
0x666e980  shr r8d,4                                     
0x666e984  mov [rbp+0x340],r8w                           
0x666e98c  mov byte ptr [rbp+0x342],1                    
0x666e993  lea rdx,[rbp+0x340]                           
0x666e99a  lea r8,[rbp+0x1D0]                            
0x666e9a1  mov rcx,rbx                                   
0x666e9a4  call 0x5679DB0                                ; -> sub_5679db0
0x666e9a9  nop                                           
```

**Phase 48: 0x666e9aa..0x666edd5 — Mesh draw setup (desc+0x78) + render-state mapper (0x66A0F60) + record setup + jump table on [rbp+0x208]**
```
loc_666e9aa:  ; from 666e973, 666e97b
0x666e9aa  mov rax,[rbp+0x668]                           ; restore description
0x666e9b1  mov rsi,[rax+0x78]                            ; desc+0x78 (Mesh-like)
0x666e9b5  mov rax,[rsi+0x60]                            ; index count
0x666e9b9  sub rax,[rsi+0x58]                            
0x666e9bd  shr rax,2                                     
0x666e9c1  imul eax,0xAAAAAAAB                           
0x666e9c7  test eax,eax                                  
0x666e9c9  je short 0x666E9FF                            ; -> loc_666e9ff
0x666e9cb  mov edx,0x250                                 
0x666e9d0  add rdx,[rbp]                                 
0x666e9d4  lea rcx,[rbp+0x3F0]                           
0x666e9db  xor r8d,r8d                                   
0x666e9de  call 0xBBD7C70                                ; -> sub_bbd7c70
0x666e9e3  nop                                           
0x666e9e4  lea rdx,[rbp+0x3F0]                           
0x666e9eb  mov rcx,rsi                                   
0x666e9ee  call 0x4DEDD00                                ; -> sub_4dedd00
0x666e9f3  nop                                           
0x666e9f4  mov rax,[rbp+0x668]                           ; restore description
0x666e9fb  mov rsi,[rax+0x78]                            ; desc+0x78

loc_666e9ff:  ; from 666e9c9
0x666e9ff  xor r14d,r14d                                 
0x666ea02  cmp byte ptr [rsi+0x1D4],0                    
0x666ea09  je short 0x666EA12                            ; -> loc_666ea12
0x666ea0b  mov r14d,[rsi+0x1D0]                          

loc_666ea12:  ; from 666ea09
0x666ea12  movaps xmm0,[rbp+0x2A0]                       ; copy 4 matrices
0x666ea19  movaps xmm1,[rbp+0x2B0]                       
0x666ea20  movaps xmm2,[rbp+0x2C0]                       
0x666ea27  movaps xmm3,[rbp+0x2D0]                       
0x666ea2e  movaps [rbp+0x340],xmm0                       
0x666ea35  movaps [rbp+0x350],xmm1                       
0x666ea3c  movaps [rbp+0x360],xmm2                       
0x666ea43  movaps [rbp+0x370],xmm3                       
0x666ea4a  mov byte ptr [rbp+0x380],0                    
0x666ea51  xorps xmm0,xmm0                               
0x666ea54  movaps [rbp+0x3D0],xmm0                       
0x666ea5b  mov rax,[rsi+0x1B0]                           ; object+0x1B0
0x666ea62  test rax,rax                                  
0x666ea65  je short 0x666EA6B                            ; -> loc_666ea6b
0x666ea67  movzx eax,word ptr [rax+0x10]                 

loc_666ea6b:  ; from 666ea65
0x666ea6b  mov rax,[rsi+0x1B8]                           ; object+0x1B8
0x666ea72  test rax,rax                                  
0x666ea75  je short 0x666EA84                            ; -> loc_666ea84
0x666ea77  lock inc dword ptr [rax+8]                    
0x666ea7b  mov rax,[rsi+0x1B8]                           
0x666ea82  jmp short 0x666EA86                           ; -> loc_666ea86

loc_666ea84:  ; from 666ea75
0x666ea84  xor eax,eax                                   

loc_666ea86:  ; from 666ea82
0x666ea86  mov rcx,[rsi+0x1B0]                           ; object+0x1B0
0x666ea8d  mov [rbp+0x3D0],rcx                           
0x666ea94  mov rsi,[rbp+0x3D8]                           ; shared_ref cleanup
0x666ea9b  mov [rbp+0x3D8],rax                           
... (refcount cleanup to 0x666ead2)

loc_666ead2:  ; from 666eaa5, 666eaab, 666eac0
0x666ead2  mov rax,[rbp+0x648]                           ; visitor this
0x666ead9  mov r8,[rax+0x3B8]                            ; visitor+0x3B8
0x666eae0  mov rdx,[r13]                                 ; frame ctx
0x666eae4  mov [rsp+0x20],r14d                           ; saved from object+0x1D0
0x666eae9  mov dword ptr [rsp+0x30],0                    
0x666eaf1  mov dword ptr [rsp+0x28],0                    
0x666eaf9  lea rcx,[rbp+0x1D0]                           ; output
0x666eb00  lea r9,[rbp+0x3D0]                            ; input (object+0x1B0/0x1B8)
0x666eb07  call 0x66A0F60                                ; -> sub_66a0f60 (render-state mapper)
0x666eb0c  nop                                           
0x666eb0d  add r15d,0xFFFFFFE0                           ; r15d -= 0x20
0x666eb11  mov rax,[rbp+0x668]                           ; restore description
0x666eb18  mov si,[rax+0x80]                             ; desc+0x80 (u16)
0x666eb1f  movlps [rbp+0x3F4],xmm7                       ; partial xmm7
0x666eb26  movss [rbp+0x3FC],xmm6                        ; zero
... (record setup similar to prior chunks)
0x666ecfc  movzx eax,byte ptr [rbp+0x208]                ; jump table index
0x666ed03  cmp rax,3                                     
0x666ed07  ja short 0x666ED79                            ; -> loc_666ed79
0x666ed09  lea rcx,[0xF2BF4E0]                           ; [data_f2bf4e0] jump table
0x666ed10  movsxd rdx,[rcx+rax*4]                        
0x666ed14  add rdx,rcx                                   
0x666ed17  jmp rdx                                       
0x666ed19  mov rcx,[rbp+0x1F8]                           ; case 0
0x666ed20  mov [rbp+0x558],rcx                           
0x666ed27  jmp short 0x666ED73                           ; -> loc_666ed73
0x666ed29  lea rcx,[rbp+0x1F8]                           ; case 1
0x666ed30  movups xmm0,[rcx]                             
0x666ed33  movups [rdi+0x164],xmm0                       
0x666ed3a  jmp short 0x666ED73                           ; -> loc_666ed73
0x666ed3c  movups [rdi+0x164],xmm0                       
0x666ed43  mov rcx,[rbp+0x200]                           ; case 2
0x666ed4a  test rcx,rcx                                  
0x666ed4d  je short 0x666ED5C                            ; -> loc_666ed5c
0x666ed4f  lock inc dword ptr [rcx+8]                    
0x666ed53  mov rcx,[rbp+0x200]                           
0x666ed5a  jmp short 0x666ED5E                           ; -> loc_666ed5e

loc_666ed5c:  ; from 666ed4d
0x666ed5c  xor ecx,ecx                                   

loc_666ed5e:  ; from 666ed5a
0x666ed5e  mov rdx,[rbp+0x1F8]                           
0x666ed65  mov [rbp+0x558],rdx                           
0x666ed6c  mov [rbp+0x560],rcx                           

loc_666ed73:  ; from 666ed27, 666ed3a
0x666ed73  mov [rbp+0x568],al                            

loc_666ed79:  ; from 666ed07
0x666ed79  mov rax,[rbp+0x220]                           
0x666ed80  mov [rbp+0x580],rax                           
0x666ed87  movaps xmm0,[rbp+0x210]                       
0x666ed8e  movups [rbp+0x570],xmm0                       
0x666ed95  lea rdx,[rbp+0x588]                           
0x666ed9c  mov [rbp+0x588],si                            
0x666eda3  mov ecx,0x9D0                                 
0x666eda8  add rcx,[r13+0x10]                            
0x666edac  mov [rsp+0x30],rdi                            
0x666edb1  mov [rsp+0x28],r10                            
0x666edb6  mov [rsp+0x20],r11                            
0x666edbb  call 0x67EAB80                                ; -> sub_67eab80
0x666edc0  nop                                           
0x666edc1  lea rcx,[rbp+0x3F0]                           
0x666edc8  call 0x66A6470                                ; -> sub_66a6470
0x666edcd  cmp byte ptr [rbp+0x208],3                    
0x666edd4  jne short 0x666EE0D                           ; -> loc_666ee0d
0x666edd6  mov rsi,[rbp+0x200]                           
```

---

### Description fields READ in chunk 6 (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x84  | 4    | R      | description+0x84 -> r15d | 7 | 0x666e6f5 `mov r15d,[rsi+0x84]` |
| +0x48  | 8    | R      | Base for lookup (stride 0x30) | 7 | 0x666e7e1 `mov rax,[rbp+0x48]` |
| +0x52  | 2    | R      | Count for lookup | 7 | 0x666e7e5 `movzx r8d,word ptr [rbp+0x52]` |
| +0x18  | 16   | R      | Vec4 (first of four) | 7 | 0x666e87a `movups xmm0,[rax+0x18]` |
| +0x38  | 8    | R      | Base for lookup (stride 0x10) | 7 | 0x666e897 `mov rax,[rbp+0x38]` |
| +0x42  | 2    | R      | Count for lookup | 7 | 0x666e89b `movzx edx,word ptr [rbp+0x42]` |
| +0x78  | 8    | R      | Mesh-like pointer (confirmed) | 7 | 0x666e9b1 `mov rsi,[rax+0x78]` |
| +0x80  | 2    | R      | u16 | 7 | 0x666eb18 `mov si,[rax+0x80]` |
| +0x208 | 1    | R      | Jump table index (0..3) | 7 | 0x666ecfc `movzx eax,byte ptr [rbp+0x208]` |

**Frame ctx fields:**
- r12 (frame ctx) at 0x666e6fc, 0x666e6ff
- r13 (frame ctx) at 0x666e6fc, 0x666edac
- r12+0x10 at 0x666e5dc, 0x666edac

**Visitor fields:**
- rbx+0x3B8 at 0x666ead9
- rbp+0x668 (SHARED SPILL SLOT = description) at 0x666e6ac, 0x666e873, 0x666e9aa, 0x666e9f4, 0x666eb11

**Global data:**
- 0x129FA148, 0x129FA158, 0x129FA168 (lookup tables)
- 0xEF40DE0 (constant xmm)
- 0xF2BF4E0 (jump table)
- 0xF99FFA0 -> sub_eea6040

**Callees (new in chunk 6):**
- 0x77D80 (sub_77d80) - hash table clamp
- 0x67EAB80 (sub_67eab80) - called twice
- 0x66A6470 (sub_66a6470) - called twice
- 0xBCABA00 (sub_bcaba00) - called again
- 0x5679DB0 (sub_5679db0) - called 3x
- 0xBBD7C70 (sub_bbd7c70) - called again
- 0x4DEDD00 (sub_4dedd00) - called again
- 0x66A0F60 (sub_66a0f60) - render-state mapper, called again
- 0xE86B370 (sub_e86b370) - called again
- 0xE869FF0 (sub_e869ff0) - called again
- 0xE935700 (sub_e935700) - free
- 0x666FBCA, 0x666FBC0, 0x666FBC3, 0x666EE0D - exits

**Key insights:**
1. **SHARED SPILL SLOT [rbp+0x668]** used 5x in this chunk - holds description across all phases
2. **Three lookup tables** with strides 0x30, 0x10, 0x10 (same pattern as chunk 4)
3. **desc+0x18 vec4** read at 0x666e87a (only first of four explicitly shown)
4. **desc+0x84** read at 0x666e6f5 (new field)
5. **Array cleanup** at rbp+0x1D8 stride 0x28 filtering by byte+0x18==2
6. **Two calls to sub_67eab80 and sub_66a6470** - appears to be a repeated pattern for two different render passes
7. **Jump table at 0xF2BF4E0** with 4 cases (0..3)

---

### UNVERIFIED items in chunk 6
- [UNVERIFIED: 0x666e4e4] sub_77d80 - hash table clamp, signature
- [UNVERIFIED: 0x666e55b] sub_eec6eb0 - memcmp, signature
- [UNVERIFIED: 0x666e5f5] sub_67eab80 - signature
- [UNVERIFIED: 0x666e605] sub_66a6470 - signature
- [UNVERIFIED: 0x666e6f0] sub_e935700 - free
- [UNVERIFIED: 0x666e86d] sub_bcaba00 - signature
- [UNVERIFIED: 0x666e90c] sub_5679db0 - signature
- [UNVERIFIED: 0x666e9de] sub_bbd7c70 - signature
- [UNVERIFIED: 0x666e9ee] sub_4dedd00 - signature
- [UNVERIFIED: 0x666eb07] sub_66a0f60 - render-state mapper
- [UNVERIFIED: 0x666edbb] sub_67eab80 - second call
- [UNVERIFIED: 0x666edc8] sub_66a6470 - second call
- [UNVERIFIED: 0x666edd6] Chunk boundary - continues

---

### Chunk 7: 0x666edd6..0x666f705 (500 instructions)

**Phase 49: 0x666edd6..0x666eece — Shared_ref cleanup (rbp+0x200) + array cleanup (rbp+0x1D8, stride 0x28) + buffer free**
```
0x666edd6  mov rsi,[rbp+0x200]                           ; shared_ref
0x666eddd  test rsi,rsi                                  
0x666ede0  je short 0x666EE0D                            ; -> loc_666ee0d
0x666ede2  lock dec dword ptr [rsi+8]                    ; cleanup
0x666ede6  jne short 0x666EE0D                           ; -> loc_666ee0d
0x666ede8  mov rax,[rsi]                                 
0x666edeb  mov rax,[rax]                                 
0x666edee  mov rcx,rsi                                   
0x666edf1  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666edf7  lock dec dword ptr [rsi+0xC]                  
0x666edfb  jne short 0x666EE0D                           ; -> loc_666ee0d
0x666edfd  mov rax,[rsi]                                 
0x666ee00  mov rax,[rax+8]                               
0x666ee04  mov rcx,rsi                                   
0x666ee07  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040

loc_666ee0d:  ; from 666ede0, 666ede6, 666edfb
0x666ee0d  mov rdi,[rbp+0x1D8]                           ; array base
0x666ee14  test rdi,rdi                                  
0x666ee17  je short 0x666EE75                            ; -> loc_666ee75
0x666ee19  mov rbx,[rbp+0x1E0]                           ; array end
0x666ee20  jmp short 0x666EE34                           ; -> loc_666ee34

loc_666ee30:  ; from 666ee3d, 666ee46, 666ee4c, 666ee61, 666ee73
0x666ee30  add rdi,0x28                                  ; stride 0x28

loc_666ee34:  ; from 666ee20
0x666ee34  cmp rdi,rbx                                   
0x666ee37  je short 0x666EE75                            ; -> loc_666ee75
0x666ee39  cmp byte ptr [rdi+0x18],2                     ; filter byte+0x18 == 2
0x666ee3d  jne short 0x666EE30                           ; -> loc_666ee30
0x666ee3f  mov rsi,[rdi+8]                               ; shared_ref at +8
0x666ee43  test rsi,rsi                                  
0x666ee46  je short 0x666EE30                            ; -> loc_666ee30
0x666ee48  lock dec dword ptr [rsi+8]                    ; cleanup
0x666ee4c  jne short 0x666EE30                           ; -> loc_666ee30
0x666ee4e  mov rax,[rsi]                                 
0x666ee51  mov rax,[rax]                                 
0x666ee54  mov rcx,rsi                                   
0x666ee57  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666ee5d  lock dec dword ptr [rsi+0xC]                  
0x666ee61  jne short 0x666EE30                           ; -> loc_666ee30
0x666ee63  mov rax,[rsi]                                 
0x666ee66  mov rax,[rax+8]                               
0x666ee6a  mov rcx,rsi                                   
0x666ee6d  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666ee73  jmp short 0x666EE30                           ; -> loc_666ee30

loc_666ee75:  ; from 666ee17, 666ee37
0x666ee75  cmp byte ptr [rbp+0x380],1                    ; mode flag
0x666ee7c  jne short 0x666EEBE                           ; -> loc_666eebe
0x666ee7e  mov rcx,[rbp+0x340]                           ; buffer base
0x666ee85  test rcx,rcx                                  
0x666ee88  je short 0x666EEBE                            ; -> loc_666eebe
0x666ee8a  mov rdx,[rbp+0x350]                           ; buffer end
0x666ee91  sub rdx,rcx                                   
0x666ee94  cmp rdx,0x1000                                
0x666ee9b  jb short 0x666EEB9                            ; -> loc_666eeb9
0x666ee9d  mov rax,[rcx-8]                               
0x666eea1  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666eea5  sub rcx,rax                                   
0x666eea8  cmp rcx,0x20                                  
0x666eeac  jae 0x6670A7A                                 ; -> loc_6670a7a
0x666eeb2  or rdx,0x27                                   
0x666eeb6  mov rcx,rax                                   

loc_666eeb9:  ; from 666ee9b
0x666eeb9  call 0xE935700                                ; -> sub_e935700 (free)

loc_666eebe:  ; from 666ee7c, 666ee88
0x666eebe  mov rsi,[rbp+0x5C8]                           ; shared_ref
0x666eec5  test rsi,rsi                                  
0x666eec8  jne 0x666FB88                                 ; -> loc_666fb88
0x666eece  jmp 0x6670032                                 ; -> loc_6670032 (EXIT)
```

**Phase 50: 0x666ee0d..0x666efaf — Alternate path: sub_e86b370 + sub_bbd7f70 + sub_bcab8f0 + thread-local checks**
```
0x666eed3  mov rax,[rax]                                 ; R ret@e935700+0x0
0x666eed6  mov [rbp+0x3F0],rax                           
0x666eedd  mov qword ptr [rbp+0x3F8],0                   
0x666eee8  mov rax,[rbp+0x3F0]                           
0x666eeef  mov rax,[rax+0x18]                            
0x666eef3  mov rax,[rax]                                 
0x666eef6  mov [rbp],rax                                 
0x666eefa  lea rbx,[rbp+8]                               
0x666eefe  mov r8,[r14]                                  ; r14 = element object
0x666ef01  mov rdx,[rax+0x170]                           ; mesh+0x170
0x666ef08  mov rcx,rbx                                   
0x666ef0b  call 0xE86B370                                ; -> sub_e86b370
0x666ef10  nop                                           
0x666ef11  mov [rbp+0x80],r14                            
0x666ef18  mov rsi,[rbp+0x3F8]                           ; shared_ref cleanup
... (refcount cleanup to 0x666ef4f)

loc_666ef4f:  ; from 666ef22, 666ef28, 666ef3d
0x666ef4f  mov rax,[rbp+0x668]                           ; SHARED SPILL SLOT = description
0x666ef56  mov r9,[rax]                                  ; desc+0x00
0x666ef59  lea rcx,[rbp+0x1D0]                           
0x666ef60  mov r8,rbp                                    
0x666ef63  mov rdx,r15                                   
0x666ef66  call 0xBBD7F70                                ; -> sub_bbd7f70
0x666ef6b  nop                                           
0x666ef6c  cmp byte ptr [rbp+0x228],0                    ; flag
0x666ef73  je 0x66708EE                                  ; -> loc_66708ee
0x666ef79  mov rax,[rbp+0x668]                           ; description
0x666ef80  lea r9,[rax+8]                                ; desc+0x08 (shared_ref)
0x666ef84  lea rax,[rbp+0x3E0]                           
0x666ef8b  mov [rsp+0x20],rax                            
0x666ef90  mov dword ptr [rsp+0x28],0                    
0x666ef98  lea r8,[0x129F8318]                           ; [data_129f8318]
0x666ef9f  mov rcx,rbp                                   
0x666efa2  lea rdx,[rbp+0x3F0]                           
0x666efa9  call 0xBCAB8F0                                ; -> sub_bcab8f0
0x666efae  nop                                           
0x666efaf  mov eax,[0x128767C8]                          ; thread-local
```

**Phase 51: 0x666efaf..0x666f03a — Thread-local checks + sub_66a0820 + sub_6692d10 + sub_bcac390 + sub_7e6d0**
```
0x666efb5  mov rcx,gs:[0x58]                             
0x666efbe  mov rax,[rcx+rax*8]                           
0x666efc2  mov eax,[rax+4]                               
0x666efc8  cmp dword ptr [rbp+0x670],1                   
0x666efcf  jne 0x666F2EB                                 ; -> loc_666f2eb
0x666efd5  cmp [0x129F9280],eax                          ; thread-local compare
0x666efdb  jg 0x6671603                                  ; -> sub_6671603
0x666efe1  mov rcx,[rbp+0x648]                           ; visitor this
0x666efe8  add rcx,0x430                                 
0x666efef  call 0x66A0820                                ; -> sub_66a0820
0x666eff4  lea rsi,[rbp+0x3F0]                           
0x666effb  mov rcx,rsi                                   
0x666effe  mov rdx,rax                                   
0x666f001  call 0x6692D10                                ; -> sub_6692d10
0x666f006  nop                                           
0x666f007  mov dword ptr [rsp+0x28],0                    
0x666f00f  mov byte ptr [rsp+0x20],1                     
0x666f014  lea r8,[0x129F9278]                           ; [data_129f9278]
0x666f01b  mov rcx,rbp                                   
0x666f01e  lea rdx,[rbp+0x340]                           
0x666f025  mov r9,rsi                                    
0x666f028  call 0xBCAC390                                ; -> sub_bcac390
0x666f02d  nop                                           
0x666f02e  lea rcx,[rbp+0x3F0]                           
0x666f035  call 0x7E6D0                                  ; -> sub_7e6d0
0x666f03a  jmp 0x666F327                                 ; -> loc_666f327
```

**Phase 52: 0x666f03f..0x666f156 — FNV-1a 64 hash computation + hash table lookup (second instance)**
```
0x666f03f  mov rdi,0xCBF29CE484222325                    ; FNV offset basis
0x666f049  jmp 0x666F0D5                                 ; -> loc_666f0d5
0x666f04e  mov rdx,r12                                   
0x666f051  and rdx,0xFFFFFFFFFFFFFFFC                    ; align 4
0x666f055  mov rdi,0xCBF29CE484222325                    ; FNV offset basis
0x666f05f  xor ecx,ecx                                   
0x666f061  mov r8,0x100000001B3                          ; FNV prime

loc_666f06b:  ; from 666f0a6 (hash loop, 4 bytes at a time)
0x666f06b  movzx r9d,byte ptr [r13+rcx]                  
0x666f071  xor r9,rdi                                    
0x666f074  imul r9,r8                                    
0x666f078  movzx r10d,byte ptr [r13+rcx+1]               
0x666f07e  xor r10,r9                                    
0x666f081  imul r10,r8                                   
0x666f085  movzx r9d,byte ptr [r13+rcx+2]                
0x666f08b  xor r9,r10                                    
0x666f08e  imul r9,r8                                    
0x666f092  movzx edi,byte ptr [r13+rcx+3]                
0x666f098  xor rdi,r9                                    
0x666f09b  imul rdi,r8                                   
0x666f09f  add rcx,4                                     
0x666f0a3  cmp rdx,rcx                                   
0x666f0a6  jne short 0x666F06B                           ; -> loc_666f06b
0x666f0a8  test rax,rax                                  
0x666f0ab  je short 0x666F0D5                            ; -> loc_666f0d5
0x666f0ad  add rcx,r13                                   
0x666f0b0  xor edx,edx                                   
0x666f0b2  mov r8,0x100000001B3                          ; FNV prime
0x666f0bc  mov r9,rdi                                    

loc_666f0bf:  ; from 666f0d3 (hash remainder bytes)
0x666f0bf  movzx edi,byte ptr [rcx+rdx]                  
0x666f0c3  xor rdi,r9                                    
0x666f0c6  imul rdi,r8                                   
0x666f0ca  inc rdx                                       
0x666f0cd  mov r9,rdi                                    
0x666f0d0  cmp rax,rdx                                   
0x666f0d3  jne short 0x666F0BF                           ; -> loc_666f0bf

loc_666f0d5:  ; from 666f049, 666f0ab (hash table lookup)
0x666f0d5  mov rcx,[rbp+0x610]                           ; hash mask
0x666f0dc  and rcx,rdi                                   
0x666f0df  mov rax,[rbp+0x5E8]                           ; table base
0x666f0e6  mov rdx,[rbp+0x5F8]                           ; table
0x666f0ed  shl rcx,4                                     ; *16 (entry size)
0x666f0f1  mov rsi,[rdx+rcx+8]                           ; entry.value
0x666f0f6  cmp rsi,rax                                   
0x666f0f9  je short 0x666F156                            ; -> loc_666f156 (found)
0x666f0fb  mov rbx,[rdx+rcx]                             
0x666f0ff  test r12,r12                                  
0x666f102  je short 0x666F143                            ; -> loc_666f143
0x666f104  cmp r12,[rsi+0x20]                            

loc_666f10a:  ; from 666f13b (collision chain walk)
0x666f10a  cmp qword ptr [rsi+0x28],0x10                 
0x666f10f  jb short 0x666F117                            ; -> loc_666f117
0x666f111  mov rdx,[rsi+0x10]                            
0x666f115  jmp short 0x666F11B                           ; -> loc_666f11b

loc_666f117:  ; from 666f10f
0x666f117  lea rdx,[rsi+0x10]                            

loc_666f11b:  ; from 666f115
0x666f11b  mov rcx,r13                                   
0x666f11e  mov r8,r12                                    
0x666f121  call 0xEEC6EB0                                ; -> sub_eec6eb0 (memcmp)
0x666f126  test eax,eax                                  
0x666f128  je 0x666FC88                                  ; -> loc_666fc88

loc_666f12e:  ; from 666f108, 666f13d (next in chain)
0x666f12e  cmp rsi,rbx                                   
0x666f131  je short 0x666F153                            ; -> loc_666f153
0x666f133  mov rsi,[rsi+8]                               
0x666f137  cmp r12,[rsi+0x20]                            
0x666f13b  je short 0x666F10A                            ; -> loc_666f10a
0x666f13d  jmp short 0x666F12E                           ; -> loc_666f12e

loc_666f13f:  ; from 666f151
0x666f13f  mov rsi,[rsi+8]                               

loc_666f143:  ; from 666f102
0x666f143  cmp qword ptr [rsi+0x20],0                    
0x666f148  je 0x666FC88                                  ; -> loc_666fc88
0x666f14e  cmp rsi,rbx                                   
0x666f151  jne short 0x666F13F                           ; -> loc_666f13f

loc_666f153:  ; from 666f131
0x666f153  mov rax,rsi                                   

loc_666f156:  ; from 666f0f9 (found)
0x666f156  mov rcx,[rbp+0x5F0]                           ; counter
0x666f15d  mov rdx,0x333333333333333                     
0x666f167  cmp rcx,rdx                                   
0x666f16a  je 0x66711EC                                  ; -> sub_66711ec
0x666f170  inc rcx                                       
0x666f173  js short 0x666F17F                            ; -> loc_666f17f
0x666f175  xorps xmm0,xmm0                               
0x666f178  cvtsi2ss xmm0,rcx                             
0x666f17d  jmp short 0x666F197                           ; -> loc_666f197

loc_666f17f:  ; from 666f173
0x666f17f  mov rdx,rcx                                   
0x666f182  shr rdx,1                                     
0x666f185  and ecx,1                                     
0x666f188  or rcx,rdx                                    
0x666f18b  xorps xmm0,xmm0                               
0x666f18e  cvtsi2ss xmm0,rcx                             
0x666f193  addss xmm0,xmm0                               

loc_666f197:  ; from 666f17d
0x666f197  movss xmm1,[rbp+0x5E0]                        ; threshold
0x666f19f  mov rsi,[rbp+0x618]                           ; signed counter
0x666f1a6  test rsi,rsi                                  
0x666f1a9  js short 0x666F1B2                            ; -> loc_666f1b2
0x666f1ab  cvtsi2ss xmm2,rsi                             
0x666f1b0  jmp short 0x666F1C9                           ; -> loc_666f1c9

loc_666f1b2:  ; from 666f1a9
0x666f1b2  mov rcx,rsi                                   
0x666f1b5  shr rcx,1                                     
0x666f1b8  mov edx,esi                                   
0x666f1ba  and edx,1                                     
0x666f1bd  or rdx,rcx                                    
0x666f1c0  cvtsi2ss xmm2,rdx                             
0x666f1c5  addss xmm2,xmm2                               

loc_666f1c9:  ; from 666f1b0
0x666f1c9  movaps xmm3,xmm0                              
0x666f1cc  divss xmm3,xmm2                               
0x666f1d0  ucomiss xmm3,xmm1                             
0x666f1d3  jbe 0x666FC25                                 ; -> loc_666fc25
0x666f1d9  divss xmm0,xmm1                               
0x666f1dd  call 0xEEC73F0                                ; -> sub_eec73f0
0x666f1e2  cvttss2si rax,xmm0                            
0x666f1e7  mov rcx,rax                                   
0x666f1ea  subss xmm0,[0xEEE6700]                        ; [data_eee6700]
0x666f1f2  cvttss2si rdx,xmm0                            
0x666f1f7  sar rcx,0x3F                                  
0x666f1fb  and rdx,rcx                                   
0x666f1fe  or rdx,rax                                    
0x666f201  cmp rdx,9                                     
0x666f205  mov eax,8                                     
0x666f20a  cmovae rax,rdx                                
0x666f20e  cmp rsi,rax                                   
0x666f211  jae short 0x666F230                           ; -> loc_666f230
0x666f213  lea rcx,[rsi*8]                               
0x666f21b  cmp rcx,rax                                   
0x666f21e  cmovbe rcx,rax                                
0x666f222  cmp rsi,0x200                                 
0x666f229  cmovae rcx,rax                                
0x666f22d  mov rsi,rcx                                   

loc_666f230:  ; from 666f211
0x666f230  lea rcx,[rbp+0x5E0]                           
0x666f237  mov rdx,rsi                                   
0x666f23a  call 0x77D80                                  ; -> sub_77d80
0x666f23f  nop                                           
0x666f240  mov rcx,[rbp+0x610]                           ; hash mask
0x666f247  and rcx,rdi                                   
0x666f24a  mov rax,[rbp+0x5E8]                           ; table base
0x666f251  mov rdx,[rbp+0x5F8]                           ; table
0x666f258  shl rcx,4                                     ; *16 (entry size)
0x666f25c  mov rbx,[rdx+rcx+8]                           ; entry.value
0x666f261  cmp rbx,rax                                   
0x666f264  je 0x666FC25                                  ; -> loc_666fc25
0x666f26a  mov rsi,[r14+0x20]                            
0x666f26e  cmp qword ptr [r14+0x28],0x10                 
0x666f273  jb short 0x666F287                            ; -> loc_666f287
0x666f275  mov rax,[rbp+0x658]                           
0x666f27c  mov rax,[rax+0x10]                            
0x666f280  mov [rbp+0x660],rax                           
```

**Phase 53: 0x666f287..0x666f326 — Hash collision chain walk (second instance) + sub_66a0ec0**
```
loc_666f287:  ; from 666f273
0x666f287  mov r15,[rdx+rcx]                             
0x666f28b  test rsi,rsi                                  
0x666f28e  je short 0x666F2DC                            ; -> loc_666f2dc
0x666f290  cmp rsi,[rbx+0x20]                            
0x666f294  jne short 0x666F2BA                           ; -> loc_666f2ba

loc_666f296:  ; from 666f2cb
0x666f296  cmp qword ptr [rbx+0x28],0x10                 
0x666f29b  jb short 0x666F2A3                            ; -> loc_666f2a3
0x666f29d  mov rdx,[rbx+0x10]                            
0x666f2a1  jmp short 0x666F2A7                           ; -> loc_666f2a7

loc_666f2a3:  ; from 666f29b
0x666f2a3  lea rdx,[rbx+0x10]                            

loc_666f2a7:  ; from 666f2a1
0x666f2a7  mov rcx,[rbp+0x660]                           
0x666f2ae  mov r8,rsi                                    
0x666f2b1  call 0xEEC6EB0                                ; -> sub_eec6eb0 (memcmp)
0x666f2b6  test eax,eax                                  
0x666f2b8  je short 0x666F2E3                            ; -> loc_666f2e3

loc_666f2ba:  ; from 666f294, 666f2cd (next in chain)
0x666f2ba  cmp rbx,r15                                   
0x666f2bd  je 0x666FC1B                                  ; -> loc_666fc1b
0x666f2c3  mov rbx,[rbx+8]                               
0x666f2c7  cmp rsi,[rbx+0x20]                            
0x666f2cb  je short 0x666F296                            ; -> loc_666f296
0x666f2cd  jmp short 0x666F2BA                           ; -> loc_666f2ba

loc_666f2cf:  ; from 666f2e1
0x666f2cf  cmp rbx,r15                                   
0x666f2d2  je 0x666FC1B                                  ; -> loc_666fc1b
0x666f2d8  mov rbx,[rbx+8]                               

loc_666f2dc:  ; from 666f28e
0x666f2dc  cmp qword ptr [rbx+0x20],0                    
0x666f2e1  jne short 0x666F2CF                           ; -> loc_666f2cf

loc_666f2e3:  ; from 666f2b8
0x666f2e3  mov rax,[rbx]                                 
0x666f2e6  jmp 0x666FC1E                                 ; -> loc_666fc1e

loc_666f2eb:  ; from 666efcf
0x666f2eb  cmp [0x129F9290],eax                          ; thread-local
0x666f2f1  jg 0x6671675                                  ; -> sub_6671675
0x666f2f7  mov rax,[rbp+0x668]                           ; description
0x666f2fe  movups xmm0,[rax+0x64]                        ; desc+0x64 (vec4)
0x666f302  movaps [rbp+0x3F0],xmm0                       
0x666f309  lea r8,[0x129F9288]                           ; [data_129f9288]
0x666f310  mov rcx,rbp                                   
0x666f313  lea rdx,[rbp+0x340]                           
0x666f31a  lea r9,[rbp+0x3F0]                            
0x666f321  call 0x66A0EC0                                ; -> sub_66a0ec0
0x666f326  nop                                           
```

**Phase 54: 0x666f327..0x666f50e — desc+0x18/+0x28/+0x38/+0x48 (four vec4) + record setup + jump table on [rbp+0x208] (4 cases)**
```
loc_666f327:  ; from 666f03a
0x666f327  mov rax,[rbp+0x668]                           ; description
0x666f32e  movups xmm0,[rax+0x18]                        ; desc+0x18 (first vec4)
0x666f332  movaps [rbp+0x340],xmm0                       
0x666f339  movups xmm1,[rax+0x28]                        ; desc+0x28 (second vec4)
0x666f33d  movaps [rbp+0x350],xmm1                       
0x666f344  movups xmm2,[rax+0x38]                        ; desc+0x38 (third vec4)
0x666f348  movaps [rbp+0x360],xmm2                       
0x666f34f  movups xmm3,[rax+0x48]                        ; desc+0x48 (fourth vec4)
0x666f353  movaps [rbp+0x370],xmm3                       
0x666f35a  mov byte ptr [rbp+0x380],0                    
0x666f361  cmp byte ptr [rbp+0x228],0                    
0x666f368  je 0x66715F7                                  ; -> loc_66715f7
0x666f36e  mov si,[rax+0x88]                             ; desc+0x88 (u16)
0x666f375  movups [rbp+0x3F8],xmm0                       
0x666f37c  movups [rbp+0x408],xmm1                       
0x666f383  movups [rbp+0x418],xmm2                       
0x666f38a  movups [rbp+0x428],xmm3                       
0x666f391  mov byte ptr [rbp+0x438],0                    
0x666f398  movups xmm0,[rbp+0x2A0]                       
0x666f39f  movups [rbp+0x440],xmm0                       
0x666f3a6  mov eax,[rbp+0x2B0]                           
0x666f3ac  mov [rbp+0x450],eax                           
0x666f3b2  movzx eax,byte ptr [rbp+0x2B4]                
0x666f3b9  mov [rbp+0x454],al                            
0x666f3bf  movups xmm0,[rbp+0x2B8]                       
0x666f3c6  movups [rbp+0x458],xmm0                       
0x666f3cd  movups xmm0,[rbp+0x2C8]                       
0x666f3d4  movups [rbp+0x468],xmm0                       
0x666f3db  movups xmm0,[rbp+0x2D8]                       
0x666f3e2  movups [rbp+0x478],xmm0                       
0x666f3e9  movups xmm0,[rbp+0x2E7]                       
0x666f3f0  movups [rbp+0x487],xmm0                       
0x666f3f7  mov rax,[rbp]                                 
0x666f3fb  mov [rbp+0x498],rax                           
0x666f402  lea rcx,[rbp+0x4A0]                           
0x666f409  mov rdx,rbx                                   
0x666f40c  call 0xE869FF0                                ; -> sub_e869ff0
0x666f411  nop                                           
0x666f412  lea rax,[rbp+0x3F8]                           
0x666f419  lea r10,[rbp+0x440]                           
0x666f420  lea r9,[rbp+0x498]                            
0x666f427  mov rcx,[rbp+0x80]                            
0x666f42e  mov [rbp+0x518],rcx                           
0x666f435  mov qword ptr [rbp+0x80],0                    
0x666f440  lea r8,[rbp+0x520]                            
0x666f447  mov [rbp+0x520],si                            
0x666f44e  lea rdx,[rbp+0x528]                           
0x666f455  movaps xmm0,[rbp+0x1D0]                       
0x666f45c  movaps xmm1,[rbp+0x1E0]                       
0x666f463  mov qword ptr [rbp+0x1D8],0                   
0x666f46e  movups [rbp+0x528],xmm0                       
0x666f475  xorps xmm0,xmm0                               
0x666f478  movaps [rbp+0x1E0],xmm0                       
0x666f47f  movups [rbp+0x538],xmm1                       
0x666f486  mov rcx,[rbp+0x1F0]                           
0x666f48d  mov [rbp+0x548],rcx                           
0x666f494  mov byte ptr [rbp+0x560],0xFF                 
0x666f49b  movzx ecx,byte ptr [rbp+0x208]                ; jump table index
0x666f4a2  cmp rcx,3                                     
0x666f4a6  ja 0x66707BD                                  ; -> loc_66707bd
0x666f4ac  lea r11,[rbp+0x550]                           
0x666f4b3  lea rsi,[0xF2BF4C0]                           ; [data_f2bf4c0] jump table
0x666f4ba  movsxd rbx,[rsi+rcx*4]                        
0x666f4be  add rbx,rsi                                   
0x666f4c1  jmp rbx                                       
0x666f4c3  mov r11,[rbp+0x1F8]                           ; case 0
0x666f4ca  mov [rbp+0x550],r11                           
0x666f4d1  jmp 0x66707B7                                 ; -> loc_66707b7
0x666f4d6  xor ecx,ecx                                   ; case 1
0x666f4d8  mov rdx,[rbp+0x368]                           
0x666f4df  mov [rbp+0x550],rdx                           
0x666f4e6  mov [rbp+0x558],rcx                           
0x666f4ed  mov [rbp+0x560],al                            
```

**Phase 55: 0x666f4f3..0x666f705 — Jump table case 3 (from 0x666d223) + sub_5aba5c0 + draw record emit (stride 0x58/0x88)**
```
loc_666f4f3:  ; from 0x666d223 (ja 0x666F4F3)
0x666f4f3  mov rax,[rbp+0x390]                           
0x666f4fa  mov [rbp+0x578],rax                           
0x666f501  movaps xmm0,[rbp+0x380]                       
0x666f508  movups [rbp+0x568],xmm0                       
0x666f50f  mov ecx,0x9D0                                 
0x666f514  add rcx,[r12+0x10]                            
0x666f519  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x666f51e  nop                                           
0x666f51f  mov rsi,rax                                   
0x666f522  lea rdx,[rbp+0x528]                           
0x666f529  xorps xmm0,xmm0                               
0x666f52c  movups [rbp+0xB8],xmm0                        
0x666f533  movups [rbp+0xA8],xmm0                        
0x666f53a  movups [rbp+0x98],xmm0                        
0x666f541  movups [rbp+0x88],xmm0                        
0x666f548  movups [rbp+0x78],xmm0                        
0x666f54c  movups [rbp+0x68],xmm0                        
0x666f550  movups [rbp+0x58],xmm0                        
0x666f554  movups [rbp+0x48],xmm0                        
0x666f558  movups [rbp+0x38],xmm0                        
0x666f55c  movups [rbp+0x28],xmm0                        
0x666f560  movups [rbp+0x18],xmm0                        
0x666f564  movups [rbp+8],xmm0                           
0x666f568  lea rcx,[rax+0x780]                           ; R ret@5aba5c0+0x780
0x666f56f  call 0x675F3B0                                ; -> sub_675f3b0
0x666f574  nop                                           
0x666f575  mov qword ptr [rbp],0x1000                    
0x666f57d  mov eax,[rsi+0x788]                           ; write ptr
0x666f583  sub eax,[rsi+0x780]                           ; - base
0x666f589  shr eax,3                                     
0x666f58c  imul eax,0xFFFF8BA3                           ; /0x58
0x666f592  dec eax                                       
0x666f594  mov [rbp+0x28],ax                             
0x666f598  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666f59f  mov rax,[rcx]                                 
0x666f5a2  mov rax,[rax+0x10]                            
0x666f5a6  mov dl,0x4A                                   
0x666f5a8  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666f5ae  nop                                           
0x666f5af  mov [rbp+0x670],al                            
0x666f5b5  mov rbx,[rsi+0x770]                           ; draw buffer write ptr
0x666f5bc  cmp rbx,[rsi+0x778]                           ; end
0x666f5c3  je short 0x666F602                            ; -> loc_666f602
0x666f5c5  mov rax,[rbp+0x4A0]                           ; fast path: write 0x88 bytes
0x666f5cc  mov [rbx],rax                                 
0x666f5cf  lea rcx,[rbx+8]                               
0x666f5d3  mov rdx,rdi                                   
0x666f5d6  call 0xE869FF0                                ; -> sub_e869ff0
0x666f5db  nop                                           
0x666f5dc  mov rax,[rbp+0x520]                           
0x666f5e3  mov [rbx+0x80],rax                            
0x666f5ea  mov qword ptr [rbp+0x520],0                   
0x666f5f5  add qword ptr [rsi+0x770],0x88                ; stride 0x88
0x666f600  jmp short 0x666F619                           ; -> loc_666f619

loc_666f602:  ; from 666f5c3 (slow path)
0x666f602  lea r8,[rbp+0x4A0]                            
0x666f609  lea rcx,[rsi+0x768]                           
0x666f610  mov rdx,rbx                                   
0x666f613  call 0x6760710                                ; -> sub_6760710
0x666f618  nop                                           

loc_666f619:  ; from 666f600
0x666f619  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666f620  mov rax,[rcx]                                 
0x666f623  mov rax,[rax+0x10]                            
0x666f627  movzx edx,byte ptr [rbp+0x670]                
0x666f62e  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666f634  nop                                           
0x666f635  mov eax,[rsi+0x770]                           ; count
0x666f63b  sub eax,[rsi+0x768]                           ; - base
0x666f641  shr eax,3                                     
0x666f644  imul eax,0xFFFFF0F1                           ; /0xC8?
0x666f64a  dec eax                                       
0x666f64c  mov [rbp+0x2A],ax                             
0x666f650  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
0x666f657  mov rax,[rcx]                                 
0x666f65a  mov rax,[rax+0x10]                            
0x666f65e  mov dl,0x4A                                   
0x666f660  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x666f666  nop                                           
0x666f667  mov [rbp+0x670],al                            
0x666f66d  lea r8,[rbp+0x448]                            
0x666f674  mov rdx,[rsi+0x758]                           ; draw buffer write ptr
0x666f67b  cmp rdx,[rsi+0x760]                           ; end
0x666f682  je short 0x666F6F8                            ; -> loc_666f6f8
0x666f684  lea rax,[rbp+0x470]                           ; fast path: write 0x58 bytes
0x666f68b  mov ecx,[r8+0x10]                             
0x666f68f  mov [rdx+0x10],ecx                            
0x666f692  movups xmm0,[r8]                              
0x666f696  movups [rdx],xmm0                             
0x666f699  movzx ecx,byte ptr [rbp+0x45C]                
0x666f6a0  mov [rdx+0x14],cl                             
0x666f6a3  movss xmm0,[rbp+0x460]                        
0x666f6ab  movss [rdx+0x18],xmm0                         
0x666f6b0  movss xmm0,[rbp+0x464]                        
0x666f6b8  movss [rdx+0x1C],xmm0                         
0x666f6bd  movss xmm0,[rbp+0x468]                        
0x666f6c5  movss [rdx+0x20],xmm0                         
0x666f6ca  movss xmm0,[rbp+0x46C]                        
0x666f6d2  movss [rdx+0x24],xmm0                         
0x666f6d7  movups xmm0,[rax]                             
0x666f6da  movups xmm1,[rax+0x10]                        
0x666f6de  movups xmm2,[rax+0x1F]                        
0x666f6e2  movups [rdx+0x28],xmm0                        
0x666f6e6  movups [rdx+0x38],xmm1                        
0x666f6ea  movups [rdx+0x47],xmm2                        
0x666f6ee  add qword ptr [rsi+0x758],0x58                ; stride 0x58
0x666f6f6  jmp short 0x666F705                           ; -> loc_666f705

loc_666f6f8:  ; from 666f682 (slow path)
0x666f6f8  lea rcx,[rsi+0x750]                           
0x666f6ff  call 0x6760A80                                ; -> sub_6760a80
0x666f704  nop                                           

loc_666f705:  ; from 666f6f6
0x666f705  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
```

---

### Description fields READ in chunk 7 (additional)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x00  | 8    | R      | desc+0x00 -> r9 | 7 | 0x666ef56 `mov r9,[rax]` |
| +0x08  | 16   | R      | desc+0x08 (shared_ref) -> r9 | 7 | 0x666ef80 `lea r9,[rax+8]` |
| +0x18  | 16   | R      | desc+0x18 (first vec4) | 7 | 0x666f32e `movups xmm0,[rax+0x18]` |
| +0x28  | 16   | R      | desc+0x28 (second vec4) | 7 | 0x666f339 `movups xmm1,[rax+0x28]` |
| +0x38  | 16   | R      | desc+0x38 (third vec4) | 7 | 0x666f344 `movups xmm2,[rax+0x38]` |
| +0x48  | 16   | R      | desc+0x48 (fourth vec4) | 7 | 0x666f34f `movups xmm3,[rax+0x48]` |
| +0x64  | 16   | R      | desc+0x64 (vec4) | 7 | 0x666f2fe `movups xmm0,[rax+0x64]` |
| +0x88  | 2    | R      | desc+0x88 (u16) -> si | 7 | 0x666f36e `mov si,[rax+0x88]` |
| +0x200 | 8    | R      | rbp+0x200 (shared_ref) | 7 | 0x666edd6 `mov rsi,[rbp+0x200]` |
| +0x1D8 | 8    | R      | rbp+0x1D8 (array base) | 7 | 0x666ee0d `mov rdi,[rbp+0x1D8]` |
| +0x1E0 | 8    | R      | rbp+0x1E0 (array end) | 7 | 0x666ee19 `mov rbx,[rbp+0x1E0]` |
| +0x228 | 1    | R      | rbp+0x228 (flag byte) | 7 | 0x666ef6c `cmp byte ptr [rbp+0x228],0` |
| +0x3E0 | 8    | R      | rbp+0x3E0 (pointer) | 7 | 0x666ef8b `mov [rsp+0x20],rax` |
| +0x380 | 16   | R      | rbp+0x380 (xmm) | 7 | 0x666f501 `movaps xmm0,[rbp+0x380]` |
| +0x390 | 8    | R      | rbp+0x390 (pointer) | 7 | 0x666f4f3 `mov rax,[rbp+0x390]` |
| +0x2A0 | 16   | R      | rbp+0x2A0 (xmm) | 7 | 0x666f398 `movups xmm0,[rbp+0x2A0]` |
| +0x2B0 | 4    | R      | rbp+0x2B0 (dword) | 7 | 0x666f3a6 `mov eax,[rbp+0x2B0]` |
| +0x2B4 | 1    | R      | rbp+0x2B4 (byte) | 7 | 0x666f3b2 `movzx eax,byte ptr [rbp+0x2B4]` |
| +0x2B8 | 16   | R      | rbp+0x2B8 (xmm) | 7 | 0x666f3bf `movups xmm0,[rbp+0x2B8]` |
| +0x2C8 | 16   | R      | rbp+0x2C8 (xmm) | 7 | 0x666f3cd `movups xmm0,[rbp+0x2C8]` |
| +0x2D8 | 16   | R      | rbp+0x2D8 (xmm) | 7 | 0x666f3db `movups xmm0,[rbp+0x2D8]` |
| +0x2E7 | 16   | R      | rbp+0x2E7 (unaligned xmm) | 7 | 0x666f3e9 `movups xmm0,[rbp+0x2E7]` |
| +0x5C8 | 8    | R      | rbp+0x5C8 (shared_ref) | 7 | 0x666eebe `mov rsi,[rbp+0x5C8]` |

**Frame ctx / visitor fields:**
- r12 (frame ctx) at 0x666ef63, 0x666efe1, 0x666f514
- r13 at 0x666f04e, 0x666f287
- r14 (element object) at 0x666eefe, 0x666f26a
- rbx (visitor this) at 0x666efae, 0x666f409
- rbp+0x668 (SHARED SPILL SLOT = description) at 0x666ef4f, 0x666ef79, 0x666f2f7, 0x666f327

**Global data:**
- 0x129F8318, 0x129F9278, 0x129F9280, 0x129F9288, 0x129F9290 (thread-local / constant)
- 0xF2BF4C0 (jump table)
- 0x1233E1B0 (shared_ref destroy vtable, tag 0x4A)
- 0xEEE6700 (constant)
- 0xF99FFA0 -> sub_eea6040

**Callees (new in chunk 7):**
- 0xBBD7F70 (sub_bbd7f70) - called again
- 0xBCAB8F0 (sub_bcab8f0) - new
- 0x66A0820 (sub_66a0820) - new
- 0x6692D10 (sub_6692d10) - new
- 0xBCAC390 (sub_bcac390) - new
- 0x7E6D0 (sub_7e6d0) - new
- 0x66A0EC0 (sub_66a0ec0) - new
- 0x5ABA5C0 (sub_5aba5c0) - called again
- 0x675F3B0 (sub_675f3b0) - called again
- 0x6760710 (sub_6760710) - called again
- 0x6760A80 (sub_6760a80) - called again
- 0xE869FF0 (sub_e869ff0) - called again
- 0xE935700 (sub_e935700) - free
- 0xEEA6040 (via 0xF99FFA0) - shared_ref destroy
- 0x666FB88, 0x6670032, 0x66708EE, 0x6671603, 0x666F2EB, 0x66711EC, 0x666FC25, 0x666FC1B, 0x666FC1E, 0x6671675, 0x66715F7, 0x66707BD, 0x66707B7 - exits

**Key insights:**
1. **SHARED SPILL SLOT [rbp+0x668]** used 4x in this chunk - holds description throughout
2. **Four vec4 at desc+0x18/+0x28/+0x38/+0x48** explicitly read at 0x666f32e..0x666f34f (confirms EffectDescriptions.h mMatrix18)
3. **desc+0x64 vec4** read at 0x666f2fe (new field)
4. **desc+0x88 u16** read at 0x666f36e (confirms EffectDescriptions.h mWord88)
5. **Second FNV-1a hash computation** at 0x666f04e..0x666f0d5 (identical to first at 0x666e2f7)
6. **Second hash table lookup** at 0x666f0d5..0x666f2e6 (identical structure to first)
7. **Jump table at 0xF2BF4C0** with 4 cases (0..3), case 3 at 0x666f4f3 (from ja at 0x666d223)
8. **Draw record emit** with two strides: 0x88 (rbp+0x4A0) and 0x58 (rbp+0x448/0x470)
9. **Shared_ref destroy (tag 0x4A)** called 3x in this chunk
10. **Buffer management** for draw buffers at rsi+0x758/0x760 (stride 0x58) and rsi+0x770/0x778 (stride 0x88)

---

### UNVERIFIED items in chunk 7
- [UNVERIFIED: 0x666ef66] sub_bbd7f70 - signature
- [UNVERIFIED: 0x666efae] sub_bcab8f0 - signature
- [UNVERIFIED: 0x666efef] sub_66a0820 - signature
- [UNVERIFIED: 0x666f001] sub_6692d10 - signature
- [UNVERIFIED: 0x666f028] sub_bcac390 - signature
- [UNVERIFIED: 0x666f035] sub_7e6d0 - signature
- [UNVERIFIED: 0x666f321] sub_66a0ec0 - signature
- [UNVERIFIED: 0x666f519] sub_5aba5c0 - signature
- [UNVERIFIED: 0x666f56f] sub_675f3b0 - signature
- [UNVERIFIED: 0x666f5a8] sub_eea6040 - shared_ref destroy tag 0x4A
- [UNVERIFIED: 0x666f613] sub_6760710 - grow buffer
- [UNVERIFIED: 0x666f62e] sub_eea6040 - shared_ref destroy
- [UNVERIFIED: 0x666f68f] sub_e869ff0 - signature
- [UNVERIFIED: 0x666f6ff] sub_6760a80 - grow buffer
- [UNVERIFIED: 0x666f705] Chunk boundary - continues to visitor return

---

### Chunk 8: 0x666f705..0x6670032 (500+ instructions, final cleanup and return)

**Phase 56: 0x666f705..0x666f86a — Final draw record emits (6 buffers) + shared_ref destroy (tag 0x4A)**
```
0x666f705  mov rcx,[0x1233E1B0]                          ; shared_ref destroy vtable
0x666f70c  mov rax,[rcx]                                 
0x666f70f  mov rax,[rax+0x10]                            
0x666f713  movzx edx,byte ptr [rbp+0x670]                
0x666f71a  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (tag 0x4A)
0x666f720  nop                                           
0x666f721  mov qword ptr [rbp],0x7000                    ; draw key
0x666f729  mov eax,[rsi+0x758]                           ; buffer write ptr
0x666f72f  sub eax,[rsi+0x750]                           ; - base
0x666f735  shr eax,3                                     
0x666f738  imul eax,0xFFFF8BA3                           ; /0x58
0x666f73e  dec eax                                       
0x666f740  mov [rbp+0x2C],ax                             
0x666f744  mov rcx,[0x1233E1B0]                          ; shared_ref destroy (x3 more)
... (3 more shared_ref destroy calls with tag 0x4A)
0x666f761  mov rdx,[rsi+0x8A8]                           ; 7th buffer
0x666f768  cmp rdx,[rsi+0x8B0]                           ; end
0x666f76f  je short 0x666F785                            ; -> loc_666f785
0x666f771  movzx eax,word ptr [rbp+0x440]                ; fast path: write 2 bytes
0x666f778  mov [rdx],ax                                  
0x666f77b  add qword ptr [rsi+0x8A8],2                   ; stride 2
0x666f783  jmp short 0x666F799                           ; -> loc_666f799

loc_666f785:  ; from 666f76f
0x666f785  lea r8,[rbp+0x440]                            ; slow path
0x666f78c  lea rcx,[rsi+0x8A0]                           
0x666f793  call 0x1EF6F90                                ; -> sub_1ef6f90
0x666f798  nop                                           

loc_666f799:  ; from 666f783
0x666f799  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
... (3 more shared_ref destroy calls)
0x666f7e5  lea rdx,[rbp+0x3F8]                           
0x666f7ec  mov rcx,rsi                                   
0x666f7ef  add rcx,0x648                                 
0x666f7f6  call 0x675FB30                                ; -> sub_675fb30
0x666f7fb  nop                                           
0x666f7fc  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
... (3 more shared_ref destroy calls)
0x666f818  mov eax,[rsi+0x650]                           ; 8th buffer count
0x666f81e  sub eax,[rsi+0x648]                           ; - base
0x666f824  shr eax,3                                     
0x666f827  imul eax,0xFFFF8E39                           ; /0x70?
0x666f82d  dec eax                                       
0x666f82f  mov [rbp+0x42],ax                             
0x666f833  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
... (3 more shared_ref destroy calls)
0x666f84a  mov edx,eax                                   
0x666f84c  mov rbx,[rsi+0x500]                           ; 9th buffer
0x666f853  cmp rbx,[rsi+0x508]                           ; end
0x666f85a  je short 0x666F86B                            ; -> loc_666f86b
0x666f85c  inc rbx                                       
0x666f85f  mov [rsi+0x500],rbx                           
0x666f866  jmp 0x666F9DA                                 ; -> loc_666f9da
```

**Phase 57: 0x666f86b..0x666f9d9 — 9th buffer reallocation (grow) + memmove + free old**
```
loc_666f86b:  ; from 666f85a
0x666f86b  mov r13,rbx                                   ; current size
0x666f86e  sub r13,[rsi+0x4F8]                           ; - base
0x666f875  mov rax,0x7FFFFFFFFFFFFFFF                    ; max size check
0x666f87f  cmp r13,rax                                   
0x666f882  mov [rbp+0x670],dl                            
0x666f888  je 0x667118C                                  ; -> loc_667118c
0x666f88e  lea r12,[r13+1]                               ; new size
0x666f892  mov rdi,r13                                   
0x666f895  shr rdi,1                                     
0x666f898  mov rcx,rdi                                   
0x666f89b  xor rcx,rax                                   
0x666f89e  add rdi,r13                                   
0x666f8a1  cmp rdi,r12                                   
0x666f8a4  cmovbe rdi,r12                                
0x666f8a8  cmp r13,rcx                                   
0x666f8ab  cmova rdi,rax                                 
0x666f8af  test rdi,rdi                                  
0x666f8b2  je short 0x666F929                            ; -> loc_666f929
0x666f8b4  cmp rdi,0x1000                                
0x666f8bb  jb short 0x666F900                            ; -> loc_666f900
0x666f8bd  cmp rdi,0xFFFFFFFFFFFFFFD9                    
0x666f8c1  jae 0x66715FD                                 ; -> loc_66715fd
0x666f8c7  lea r15,[rdi+0x27]                            ; size + 0x27, align 0x20
0x666f8cb  mov rcx,[0x1233E1A8]                          ; allocator
0x666f8d2  mov rax,[rcx]                                 
0x666f8d5  mov rax,[rax+8]                               
0x666f8d9  mov rdx,r15                                   
0x666f8dc  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc)
0x666f8e2  nop                                           
0x666f8e3  mov r14,rax                                   
0x666f8e6  test rax,rax                                  
0x666f8e9  je 0x6670A6C                                  ; -> loc_6670a6c

loc_666f8ef:  ; from 6670a75 (alloc success)
0x666f8ef  mov rax,r14                                   
0x666f8f2  add r14,0x27                                  
0x666f8f6  and r14,0xFFFFFFFFFFFFFFE0                    ; align
0x666f8fa  mov [r14-8],rax                               
0x666f8fe  jmp short 0x666F92C                           ; -> loc_666f92c

loc_666f900:  ; from 666f8bb (small alloc)
0x666f900  mov rcx,[0x1233E1A8]                          ; allocator
0x666f907  mov rax,[rcx]                                 
0x666f90a  mov rax,[rax+8]                               
0x666f90e  mov rdx,rdi                                   
0x666f911  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc)
0x666f917  nop                                           
0x666f918  mov r14,rax                                   
0x666f91b  test rax,rax                                  
0x666f91e  jne short 0x666F92C                           ; -> loc_666f92c
0x666f920  mov rcx,rdi                                   
0x666f923  call 0x9BC830                                 ; -> sub_9bc830
0x666f928  nop                                           

loc_666f929:  ; from 666f8b2
0x666f929  xor r14d,r14d                                 

loc_666f92c:  ; from 666f8fe, 666f91e
0x666f92c  cmp rbx,[rsi+0x500]                           ; check concurrent mod
0x666f933  je short 0x666F963                            ; -> loc_666f963
0x666f935  lea r15,[r14+r13]                             ; dst = new + old_size
0x666f939  inc r15                                       
0x666f93c  mov rdx,[rsi+0x4F8]                           ; old base
0x666f943  mov r8,rbx                                    
0x666f946  sub r8,rdx                                    
0x666f949  mov rcx,r14                                   
0x666f94c  call 0xEEC6DE0                                ; -> sub_eec6de0 (memmove)
0x666f951  mov r8,[rsi+0x500]                            ; old write ptr
0x666f958  sub r8,rbx                                    
0x666f95b  mov rcx,r15                                   
0x666f95e  mov rdx,rbx                                   
0x666f961  jmp short 0x666F973                           ; -> loc_666f973

loc_666f963:  ; from 666f933 (no concurrent mod)
0x666f963  mov rdx,[rsi+0x4F8]                           ; old base
0x666f96a  sub rbx,rdx                                   
0x666f96d  mov rcx,r14                                   
0x666f970  mov r8,rbx                                    

loc_666f973:  ; from 666f961
0x666f973  call 0xEEC6DE0                                ; -> sub_eec6de0 (memmove)
0x666f978  mov rcx,[rsi+0x4F8]                           ; old base
0x666f97f  test rcx,rcx                                  
0x666f982  je short 0x666F9B8                            ; -> loc_666f9b8
0x666f984  mov rdx,[rsi+0x508]                           ; old end
0x666f98b  sub rdx,rcx                                   
0x666f98e  cmp rdx,0x1000                                
0x666f995  jb short 0x666F9B3                            ; -> loc_666f9b3
0x666f997  mov rax,[rcx-8]                               
0x666f99b  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666f99f  sub rcx,rax                                   
0x666f9a2  cmp rcx,0x20                                  
0x666f9a6  jae 0x6670A7A                                 ; -> loc_6670a7a
0x666f9ac  add rdx,0x27                                  
0x666f9b0  mov rcx,rax                                   

loc_666f9b3:  ; from 666f995
0x666f9b3  call 0xE935700                                ; -> sub_e935700 (free old)

loc_666f9b8:  ; from 666f982
0x666f9b8  mov [rsi+0x4F8],r14                           ; new base
0x666f9bf  add r12,r14                                   
0x666f9c2  mov [rsi+0x500],r12                           ; new write ptr
0x666f9c9  add rdi,r14                                   
0x666f9cc  mov [rsi+0x508],rdi                           ; new end
0x666f9d3  movzx edx,byte ptr [rbp+0x670]                ; shared_ref tag
```

**Phase 58: 0x666f9da..0x666fb77 — 10th buffer emit + shared_ref cleanup + final array cleanups**
```
loc_666f9da:  ; from 666f866
0x666f9da  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
... (shared_ref destroy tag 0x4A)
0x666f9ef  mov rax,0x8002007001                          ; draw key
0x666f9f9  mov [rbp],rax                                 
0x666fa03  not eax                                       
0x666fa05  add eax,[rsi+0x500]                           ; write ptr - base
0x666fa0b  mov [rbp+0x5E],ax                             
0x666fa0f  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
... (3 more shared_ref destroy)
0x666fa2c  mov rax,[rsi+8]                               ; 10th buffer (rbx+8)
0x666fa30  cmp rax,[rsi+0x10]                            ; end
0x666fa34  je short 0x666FA51                            ; -> loc_666fa51
0x666fa36  mov rdx,rbp                                   
0x666fa39  mov r8d,0xC8                                  
0x666fa3f  mov rcx,rax                                   
0x666fa42  call 0xEEC6EC0                                ; -> sub_eec6ec0 (memcpy 0xC8)
0x666fa47  add qword ptr [rsi+8],0xC8                    ; stride 0xC8
0x666fa4f  jmp short 0x666FA60                           ; -> loc_666fa60

loc_666fa51:  ; from 666fa34
0x666fa51  mov r8,rbp                                    
0x666fa54  mov rcx,rsi                                   
0x666fa57  mov rdx,rax                                   
0x666fa5a  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x666fa5f  nop                                           

loc_666fa60:  ; from 666fa4f
0x666fa60  mov rcx,[0x1233E1B0]                          ; shared_ref destroy
... (shared_ref destroy tag 0x4A)
0x666fa7c  lea rcx,[rbp+0x3F0]                           
0x666fa83  call 0x66E5B10                                ; -> sub_66e5b10
0x666fa88  cmp byte ptr [rbp+0x2E0],1                    ; mode flag
0x666fa8f  jne short 0x666FAD1                           ; -> loc_666fad1
... (buffer free if mode 1)

loc_666fad1:  ; from 666fa8f, 666fa9b
0x666fad1  cmp byte ptr [rbp+0x398],1                    ; flag
0x666fad8  jne 0x666FB78                                 ; -> loc_666fb78
0x666fade  cmp byte ptr [rbp+0x378],3                    ; jump table index
0x666fae5  jne short 0x666FB1E                           ; -> loc_666fb1e
0x666fae7  mov rsi,[rbp+0x370]                           ; shared_ref cleanup
... (shared_ref cleanup)

loc_666fb1e:  ; from 666fae5, 666faf1, 666faf7, 666fb0c
0x666fb1e  mov rdi,[rbp+0x348]                           ; array base (stride 0x28)
0x666fb25  test rdi,rdi                                  
0x666fb28  je short 0x666FB78                            ; -> loc_666fb78
0x666fb2a  mov rbx,[rbp+0x350]                           ; array end
... (cleanup loop: stride 0x28, filter byte+0x18==2, shared_ref dec)

loc_666fb78:  ; from 666fad8, 666fb28, 666fb3a
0x666fb78  mov rsi,[rbp+0x638]                           ; shared_ref cleanup
... (shared_ref cleanup)

0x666fb88  lock dec dword ptr [rsi+8]                    
0x666fb8c  jne 0x6670032                                 ; -> loc_6670032 (RETURN)
... (full shared_ref cleanup to 0x666fbb5)

loc_666fbbb  jmp 0x6670032                               ; -> loc_6670032 (RETURN)
```

**Phase 59: 0x666fbc0..0x6670032 — Hash table insert (success paths) + final return**
```
loc_666fbc0:  ; from 0x666f562, 0x666f582 (hash table insert success)
0x666fbc0  mov rax,[rbx]                                 
0x666fbc3  mov r14,[rbp+0x658]                           
0x666fbca  mov qword ptr [rbp+0x3F8],0                   
0x666fbd5  mov rdx,[rax+8]                               
0x666fbd9  inc qword ptr [rbp+0x5F0]                     
0x666fbe0  mov [r14],rax                                 
0x666fbe3  mov [r14+8],rdx                               
0x666fbe7  mov [rdx],r14                                 
0x666fbea  mov [rax+8],r14                               
... (hash table link update)

loc_666fc9e:  ; from 0x666fc86 (alloc fail path cleanup)
0x666fc9e  cmp qword ptr [0x129F9240],0x10               ; check inline capacity
0x666fca6  jb short 0x666FCB1                            ; -> loc_666fcb1
... (cleanup and return via 0x6670032)

loc_666ff60:  ; from 0x666fe58, 0x666fe87, 0x666fee7 (another exit path)
0x666ff60  mov rsi,[rbp+0x5C8]                           ; shared_ref cleanup
... (shared_ref cleanup)

loc_666ff97:  ; from 0x666ff6a, 0x666ff70, 0x666ff85
0x666ff97  mov rcx,[rbp+0x5F8]                           ; buffer free
... (buffer free)

0x6670032:  ; MAIN RETURN - from 0x666b66d, 0x666c856, 0x666cba6, 0x666cb07, 0x666ceeb, 0x666cf07, 0x666db07, 0x666e1ce, 0x666e27d, 0x666e31a, 0x666e455, 0x666e6ce, 0x666e7ce, 0x666eb12, 0x666ec04, 0x666ed08, 0x666eece, 0x666f6ce, 0x666f7ce, 0x666f8ce, 0x666f9ce, 0x666face, 0x666fb7c, 0x666fc9e, 0x666fd02, 0x666fe0a, 0x666ff97, 0x666ffbb
0x6670032  movaps xmm6,[rbp+0x680]                       
0x6670039  movaps xmm7,[rbp+0x690]                       
0x6670040  movaps xmm8,[rbp+0x6A0]                       
0x6670048  add rsp,0x738                                 
0x667004f  pop rbx                                       
0x6670050  pop rdi                                       
0x6670051  pop rsi                                       
0x6670052  pop r12                                       
0x6670054  pop r13                                       
0x6670056  pop r14                                       
0x6670058  pop r15                                       
0x667005a  pop rbp                                       
0x667005b  ret                                           
```

---

### Description fields READ in chunk 8 (final)

| Offset | Size | Access | Use | Tag | Source |
|--------|------|--------|-----|-----|--------|
| +0x440 | 2    | R      | rbp+0x440 (word) | 7 | 0x666f771 `movzx eax,word ptr [rbp+0x440]` |
| +0x470 | 16   | R      | rbp+0x470 (xmm) | 7 | 0x666f684 `lea rax,[rbp+0x470]` |
| +0x4A0 | 8    | R      | rbp+0x4A0 (ptr) | 7 | 0x666f5c5 `mov rax,[rbp+0x4A0]` |
| +0x448 | 16   | R      | rbp+0x448 (xmm) | 7 | 0x666f66d `lea r8,[rbp+0x448]` |
| +0x45C | 1    | R      | rbp+0x45C (byte) | 7 | 0x666f699 `movzx ecx,byte ptr [rbp+0x45C]` |
| +0x460 | 4    | R      | rbp+0x460 (float) | 7 | 0x666f6a3 `movss xmm0,[rbp+0x460]` |
| +0x464 | 4    | R      | rbp+0x464 (float) | 7 | 0x666f6b0 `movss xmm0,[rbp+0x464]` |
| +0x468 | 4    | R      | rbp+0x468 (float) | 7 | 0x666f6bd `movss xmm0,[rbp+0x468]` |
| +0x46C | 4    | R      | rbp+0x46C (float) | 7 | 0x666f6ca `movss xmm0,[rbp+0x46C]` |

**Visitor (rsi/rbx) buffer pointers:**
- rsi+0x750/0x758/0x760 (buffer 1, stride 0x58)
- rsi+0x770/0x778 (buffer 2, stride 0x88)
- rsi+0x8A0/0x8A8/0x8B0 (buffer 3, stride 2)
- rsi+0x648/0x650 (buffer 4, stride 0x70)
- rsi+0x4F8/0x500/0x508 (buffer 5, stride 0x58? growable)
- rsi+0x8/0x10 (buffer 6, stride 0xC8)
- rsi+0x758/0x760 (buffer 7, stride 0x58)
- rsi+0x5C8, 0x638 (shared_refs for cleanup)

**Global data:**
- 0x1233E1B0 (shared_ref destroy vtable, tag 0x4A)
- 0x1233E1A8 (allocator)
- 0xF99FFA0 -> sub_eea6040
- 0x1EF6F90, 0x675FB30, 0x6760710, 0x6760A80, 0x5ABA6D0, 0x66E5B10, 0x66A02D0, 0x67CFD80, 0xEEC6DE0, 0xE935700, 0xEEC6EC0, 0x9BC830, 0x76B30, 0xAA840, 0x129CA5E0, 0x128767C8, 0x129F9240, 0x129F9228, 0x129F9238

**Callees (final):**
- 0xEEA6040 (via 0xF99FFA0) - shared_ref destroy (tag 0x4A, called 15+ times)
- 0x1EF6F90 (sub_1ef6f90) - slow path buffer write
- 0x675FB30 (sub_675fb30) - buffer emit
- 0x6760710 (sub_6760710) - buffer grow
- 0x6760A80 (sub_6760a80) - buffer grow
- 0x5ABA6D0 (sub_5aba6d0) - slow path
- 0x66E5B10 (sub_66e5b10) - new
- 0x66A02D0 (sub_66a02d0) - called again
- 0x67CFD80 (sub_67cfd80) - called again
- 0xEEC6DE0 (sub_eec6de0) - memmove
- 0xE935700 (sub_e935700) - free
- 0xEEC6EC0 (sub_eec6ec0) - memcpy
- 0x9BC830 (sub_9bc830) - alloc fail
- 0x76B30 (sub_76b30) - element processing
- 0xAA840 (sub_aa840) - per-element
- 0x6670032 - **MAIN RETURN** (epilog + ret)

**Key insights:**
1. **10 draw buffers** emitted in final phase with varying strides (0x58, 0x88, 2, 0x70, 0x58, 0xC8)
2. **Shared_ref destroy (tag 0x4A)** called 15+ times in this chunk alone
3. **Buffer 5 (rsi+0x4F8)** is growable - reallocation with memmove/free pattern
4. **Final return at 0x6670032** - epilog restores all callee-saved registers (rbx, rsi, rdi, r12-r15, rbp) and returns
5. **Multiple exit paths** all converge to 0x6670032
6. **SHARED SPILL SLOT [rbp+0x668]** not used in this final chunk (description no longer needed)

---

### COMPLETE FIELD READ SUMMARY (Effect tag 7 - FullscreenEffect)

Combining all chunks, the FullscreenEffect description (EffectDescriptions.h RenderFullscreenEffectDescriptionReads, size 0xD0) has the following fields READ by the visitor. Meaning inferred ONLY from code context at first read site; [UNVERIFIED] = not directly observed as a read in any chunk.

| Offset | Size | Type | Description (code-inferred) | First Read Site | Verified |
|--------|------|------|-----------------------------|-----------------|----------|
| +0x00  | 8    | ptr  | mObject00 - object pointer, passed to 0xBBD7F70/0x66B2B30 | 0x666b9c6 `movups xmm0,[r15]` | V |
| +0x08  | 16   | SharedRefPair | mPad08 - sampler data for 0xBCAB8F0/0xBCABA00 | 0x666b9b2 `mov rax,[r15+8]` | V |
| +0x10  | 8    | u64  | mCount - element count | 0x666b6cf `mov rax,[r15+0x10]` | V |
| +0x18  | 16   | vec4 | mMatrix18[0] - first matrix row | 0x666d37a `movups xmm0,[r11+0x18]` | V |
| +0x28  | 16   | vec4 | mMatrix18[1] - second matrix row | 0x666f339 `movups xmm1,[rax+0x28]` | V |
| +0x38  | 16   | vec4 | mMatrix18[2] - third matrix row | 0x666f344 `movups xmm2,[rax+0x38]` | V |
| +0x48  | 16   | vec4 | mMatrix18[3] - fourth matrix row | 0x666f34f `movups xmm3,[rax+0x48]` | V |
| +0x58  | 12   | vec3+float | mVec58 - vec3 (+0x58, +0x5C) + padding | 0x666b891/0x666b897 `movss/movsd [r14+0x20/0x18]` | V |
| +0x64  | 16   | vec4 | mVec64 - uniform data (static 0x129F9288) | 0x666f2fe `movups xmm0,[rax+0x64]` | V |
| +0x78  | 8    | ptr  | mMesh78 - Mesh-like pointer (pointee+0x40 checked) | 0x666d4b1 `mov rsi,[r15+0x78]` | V |
| +0x80  | 2    | u16  | (unnamed in header) - used as lookup count | 0x666d610 `mov si,[r15+0x80]` | V |
| +0x88  | 2    | u16  | mWord88 - record word | 0x666f36e `mov si,[rax+0x88]` | V |
| +0xC8  | 1    | byte | mByteC8 - flag (==1 check) | 0x666d9c0 `cmp byte ptr [r15+0xC8],1` | V |
| +0xC9  | 1    | byte | mByteC9 - flag | [UNVERIFIED] not directly read in any chunk | [UNVERIFIED] |

**Element structure (BlitFlipbookElementLayout-like, stride 0x40):**
| Offset | Size | Type | Description (code-inferred) | First Read Site | Verified |
|--------|------|------|-----------------------------|-----------------|----------|
| +0x00  | 8    | ptr  | mObject - mesh object | 0x666b942 `mov rsi,[r14]` | V |
| +0x08  | 16   | SharedRefPair | mTexture - texture reference | 0x666b858 `lea r8,[r14+8]` | V |
| +0x18  | 8    | double | mFrameU - frame position | 0x666b897 `movsd xmm1,[r14+0x18]` | V |
| +0x20  | 4    | float | mFrameLerp - frame lerp | 0x666b891 `movss xmm0,[r14+0x20]` | V |
| +0x24  | 16   | bytes | mBlock24 - 16 bytes data | 0x666ba25 `movups xmm0,[r14+0x24]` | V |

**Frame ctx / visitor fields READ (not part of description):**
| Location | Size | Use | First Read Site |
|----------|------|-----|-----------------|
| [r12] | 8 | frame ctx | throughout |
| [rbx+0x3B8] | 8 | visitor field | 0x666bb00 |
| [rdi+0x98] | 8 | early check | 0x666b622 |
| [rbp+0x668] | 8 | SHARED SPILL SLOT = description | 0x666b6ef |
| [r15+0x40] | 8 | frame ctx+0x40 | 0x666dbba |
| [r15+0x68] | 8 | frame ctx+0x68 | 0x666dbbe |
| [r15+0x84] | 4 | frame ctx+0x84 | 0x666c96f |
| [r15+0x0C] | 16 | frame ctx+0x0C mat4 row0 | 0x666d090 |
| [r15+0x1C] | 16 | frame ctx+0x1C mat4 row1 | 0x666d09c |
| [r15+0x2C] | 16 | frame ctx+0x2C mat4 row2 | 0x666d0a8 |
| [r15+0x3C] | 16 | frame ctx+0x3C mat4 row3 | 0x666d0b4 |
| [r15+0x4C] | 2 | frame ctx+0x4C u16 | 0x666d0c7 |
| [r15+0x5F0] | 1 | frame ctx+0x5F0 byte | 0x666d179 |
| [r15+0x5E0] | 16 | frame ctx+0x5E0 vec4 | 0x666d186 |
| [r15+0x08] | 4 | frame ctx+0x08 float | 0x666cfe1 |
| [r15+0x1AC..0x1AF] | 4 | frame ctx flag bytes | 0x666d912/0x666d932/0x666d94a/0x666d962 |

---

### COMPLETE VERIFICATION
Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-D7c.md` → 3994/3994 match