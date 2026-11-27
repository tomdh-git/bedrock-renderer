# ctxpack build 0xe83aaa0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=e83aaa0.md:f640ac06dc45b295c2fd646a9af3ddc8cf0c8ae52244ac2ee14a97d0bfa51b44,liftsrc=sub_e83aaa0.cpp:648a66d6f40c2d4501f6847113ad7a49ed8678b8dad6ca934a0e69dec5cd073f,liftsrc=sub_e83aaa0.h:e57489574cccca86938c079eacdc3372883df2dc0bfdf830d38d66e86acbee74,data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xe83aaa0
  size       : 0x10d (269 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 0 (direct), depth 1
  callers    : 2

## EXACT LISTING (0xe83aaa0..0xe83abad)
```
sub_e83aaa0  [0xe83aaa0..0xe83caa0)  size 0x2000  6 xrefs in
  e83aaa0  push r14                                      
  e83aaa2  push rsi                                      
  e83aaa3  push rdi                                      
  e83aaa4  push rbx                                      
  e83aaa5  sub rsp,0x28                                  
  e83aaa9  mov rsi,rcx                                   
  e83aaac  cmp rcx,rdx                                   
  e83aaaf  je 0xE83ABA0                                  ; -> loc_e83aba0
  e83aab5  mov rdi,rdx                                   
  e83aab8  lea rbx,[rsi+0x40]                            ; R a0+0x40
  e83aabc  mov rcx,[rsi+0x78]                            ; R a0+0x78
  e83aac0  test rcx,rcx                                  
  e83aac3  je short 0xE83AAE0                            ; -> loc_e83aae0
  e83aac5  cmp rcx,rbx                                   
  e83aac8  setne dl                                      
  e83aacb  mov rax,[rcx]                                 ; R *(a0+0x78)+0x0
  e83aace  mov rax,[rax+0x20]                            ; R *(*(a0+0x78)+0x0)+0x20
  e83aad2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  e83aad8  mov qword ptr [rsi+0x78],0                    ; W a0+0x78

loc_e83aae0:  ; from e83aac3
  e83aae0  mov rcx,[rdi+0x78]                            ; R a1+0x78
  e83aae4  test rcx,rcx                                  
  e83aae7  je short 0xE83AB30                            ; -> loc_e83ab30
  e83aae9  lea r14,[rdi+0x40]                            ; R a1+0x40
  e83aaed  cmp rcx,r14                                   
  e83aaf0  je short 0xE83AAF8                            ; -> loc_e83aaf8
  e83aaf2  mov [rsi+0x78],rcx                            ; W a0+0x78
  e83aaf6  jmp short 0xE83AB28                           ; -> loc_e83ab28

loc_e83aaf8:  ; from e83aaf0
  e83aaf8  mov rax,[rcx]                                 
  e83aafb  mov rax,[rax+8]                               
  e83aaff  mov rdx,rbx                                   
  e83ab02  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  e83ab08  mov [rsi+0x78],rax                            
  e83ab0c  mov rcx,[rdi+0x78]                            
  e83ab10  test rcx,rcx                                  
  e83ab13  je short 0xE83AB30                            ; -> loc_e83ab30
  e83ab15  cmp rcx,r14                                   
  e83ab18  setne dl                                      
  e83ab1b  mov rax,[rcx]                                 
  e83ab1e  mov rax,[rax+0x20]                            
  e83ab22  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_e83ab28:  ; from e83aaf6
  e83ab28  mov qword ptr [rdi+0x78],0                    

loc_e83ab30:  ; from e83aae7, e83ab13
  e83ab30  mov rcx,[rsi+0x38]                            
  e83ab34  test rcx,rcx                                  
  e83ab37  je short 0xE83AB54                            ; -> loc_e83ab54
  e83ab39  cmp rcx,rsi                                   
  e83ab3c  setne dl                                      
  e83ab3f  mov rax,[rcx]                                 
  e83ab42  mov rax,[rax+0x20]                            
  e83ab46  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  e83ab4c  mov qword ptr [rsi+0x38],0                    

loc_e83ab54:  ; from e83ab37
  e83ab54  mov rcx,[rdi+0x38]                            
  e83ab58  test rcx,rcx                                  
  e83ab5b  je short 0xE83ABA0                            ; -> loc_e83aba0
  e83ab5d  cmp rcx,rdi                                   
  e83ab60  je short 0xE83AB68                            ; -> loc_e83ab68
  e83ab62  mov [rsi+0x38],rcx                            
  e83ab66  jmp short 0xE83AB98                           ; -> loc_e83ab98

loc_e83ab68:  ; from e83ab60
  e83ab68  mov rax,[rcx]                                 
  e83ab6b  mov rax,[rax+8]                               
  e83ab6f  mov rdx,rsi                                   
  e83ab72  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  e83ab78  mov [rsi+0x38],rax                            
  e83ab7c  mov rcx,[rdi+0x38]                            
  e83ab80  test rcx,rcx                                  
  e83ab83  je short 0xE83ABA0                            ; -> loc_e83aba0
  e83ab85  cmp rcx,rdi                                   
  e83ab88  setne dl                                      
  e83ab8b  mov rax,[rcx]                                 
  e83ab8e  mov rax,[rax+0x20]                            
  e83ab92  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_e83ab98:  ; from e83ab66
  e83ab98  mov qword ptr [rdi+0x38],0                    

loc_e83aba0:  ; from e83aaaf, e83ab5b, e83ab83
  e83aba0  mov rax,rsi                                   
  e83aba3  add rsp,0x28                                  
  e83aba7  pop rbx                                       
  e83aba8  pop rdi                                       
  e83aba9  pop rsi                                       
  e83abaa  pop r14                                       
  e83abac  ret                                           
  e83abad  int3                                          
  e83abae  int3                                          
  e83abaf  int3                                          
  e83abb0  push r14                                      
  e83abb2  push rsi                                      
  e83abb3  push rdi                                      
  e83abb4  push rbx                                      
  e83abb5  sub rsp,0x28                                  
  e83abb9  mov rsi,rdx                                   
  e83abbc  mov rdi,rcx                                   
  e83abbf  cmp rdx,0x1000                                
  e83abc6  jb short 0xE83ABD1                            ; -> loc_e83abd1
  e83abc8  cmp byte ptr [rdi+0xB8018],0                  
  e83abcf  jne short 0xE83AC31                           ; -> loc_e83ac31

loc_e83abd1:  ; from e83abc6
  e83abd1  mov rax,[rdi+0xB8008]                         
  e83abd8  shr rax,3                                     
  e83abdc  mov rbx,0x1642C8590B21642D                    
  e83abe6  mul rbx                                       
  e83abe9  shr rdx,1                                     
  e83abec  cmp rsi,rdx                                   
  e83abef  jb short 0xE83AC31                            ; -> loc_e83ac31
  e83abf1  and rsi,0xFFFFFFFFFFFFF000                    
  e83abf8  add rsi,0x1000                                
  e83abff  mov rcx,rdi                                   
  e83ac02  mov rdx,rsi                                   
  e83ac05  call 0xE83ACE0                                ; -> sub_e83ace0
  e83ac0a  mov rax,[rdi+0xB8008]                         
  e83ac11  shr rax,3                                     
  e83ac15  mul rbx                                       
  e83ac18  mov rbx,rdx                                   
  e83ac1b  shr rbx,1                                     
  e83ac1e  cmp rbx,rsi                                   
  e83ac21  jb short 0xE83AC8C                            ; -> loc_e83ac8c

loc_e83ac23:  ; from e83ac8a
  e83ac23  imul rax,rsi,0xB8                             
  e83ac2a  mov [rdi+0xB8008],rax                         

loc_e83ac31:  ; from e83abcf, e83abef
  e83ac31  add rsp,0x28                                  
  e83ac35  pop rbx                                       
  e83ac36  pop rdi                                       
  e83ac37  pop rsi                                       
  e83ac38  pop r14                                       
  e83ac3a  ret                                           
  e83ac3b  nop [rax+rax]                                 

loc_e83ac40:  ; from e83ac9a
  e83ac40  add r14,rdi                                   

loc_e83ac43:  ; from e83acda
  e83ac43  mov qword ptr [r14],0                         
  e83ac4a  mov qword ptr [r14+0x90],0                    
  e83ac55  mov word ptr [r14+0xB1],0                     
  e83ac5f  lea rcx,[r14+0x40]                            
  e83ac63  mov r8d,0x28                                  
  e83ac69  xor edx,edx                                   
  e83ac6b  call 0xEBCE430                                ; -> sub_ebce430
  e83ac70  add r14,0x68                                  
  e83ac74  mov r8d,0x28                                  
  e83ac7a  mov rcx,r14                                   
  e83ac7d  xor edx,edx                                   
  e83ac7f  call 0xEBCE430                                ; -> sub_ebce430
  e83ac84  inc rbx                                       
  e83ac87  cmp rbx,rsi                                   
  e83ac8a  je short 0xE83AC23                            ; -> loc_e83ac23

loc_e83ac8c:  ; from e83ac21
  e83ac8c  imul r14,rbx,0xB8                             
  e83ac93  cmp rbx,0xFFF                                 
  e83ac9a  jbe short 0xE83AC40                           ; -> loc_e83ac40
  e83ac9c  add r14,0xFFFFFFFFFFF48000                    
  e83aca3  mov rax,[rdi+0xB8000]                         
  e83acaa  mov rax,[rax]                                 
  e83acad  cmp r14,0xB8000                               
  e83acb4  jb short 0xE83ACD7                            ; -> loc_e83acd7
  e83acb6  nop [rax+rax]                                 

loc_e83acc0:  ; from e83acd5
  e83acc0  add r14,0xFFFFFFFFFFF48000                    
  e83acc7  mov rax,[rax+0xB8000]                         
  e83acce  cmp r14,0xB7FFF                               
  e83acd5  ja short 0xE83ACC0                            ; -> loc_e83acc0

loc_e83acd7:  ; from e83acb4
  e83acd7  add r14,rax                                   
  e83acda  jmp 0xE83AC43                                 ; -> loc_e83ac43
  e83acdf  int3                                          
  e83ace0  push r15                                      
  e83ace2  push r14                                      
  e83ace4  push r13                                      
  e83ace6  push r12                                      
  e83ace8  push rsi                                      
  e83ace9  push rdi                                      
  e83acea  push rbx                                      
  e83aceb  sub rsp,0x30                                  
  e83acef  mov r8,rdx                                    
  e83acf2  mov rsi,rcx                                   
  e83acf5  cmp rdx,0x1001                                
  e83acfc  jb 0xE83AE9C                                  ; -> loc_e83ae9c
  e83ad02  mov rax,[rsi+0xB8010]                         
  e83ad09  shr rax,3                                     
  e83ad0d  mov rbx,0x1642C8590B21642D                    
  e83ad17  mul rbx                                       
  e83ad1a  shr rdx,1                                     
  e83ad1d  cmp r8,rdx                                    
  e83ad20  jbe 0xE83AE9C                                 ; -> loc_e83ae9c
  e83ad26  imul r14,r8,0xB8                              
  e83ad2d  mov rax,[rsi+0xB8000]                         
  e83ad34  add r14,0xFFFFFFFFFFF48000                    
  e83ad3b  je 0xE83AE71                                  ; -> loc_e83ae71
  e83ad41  test rax,rax                                  
  e83ad44  jne short 0xE83AD91                           ; -> loc_e83ad91
  e83ad46  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  e83ad4d  mov rax,[rcx]                                 
  e83ad50  mov rax,[rax+8]                               
  e83ad54  lea rdx,[0xF7CC762]                           ; [data_f7cc762] "NOFILE"
  e83ad5b  mov [rsp+0x20],rdx                            
  e83ad60  mov dword ptr [rsp+0x28],0                    
  e83ad68  mov r8d,0x18                                  
  e83ad6e  mov r9d,8                                     
  e83ad74  xor edx,edx                                   
  e83ad76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  e83ad7c  xorps xmm0,xmm0                               
  e83ad7f  movups [rax],xmm0                             
  e83ad82  mov qword ptr [rax+0x10],0                    
  e83ad8a  mov [rsi+0xB8000],rax                         

loc_e83ad91:  ; from e83ad44
  e83ad91  mov rcx,[rax+0x10]                            
  e83ad95  sub r14,rcx                                   
  e83ad98  jbe 0xE83AE85                                 ; -> loc_e83ae85
  e83ad9e  mov rcx,[rax+8]                               
  e83ada2  add rax,8                                     
  e83ada6  lea r15,[rcx+0xB8000]                         
  e83adad  test rcx,rcx                                  
  e83adb0  cmove r15,rax                                 
  e83adb4  lea r12,[0xF7CC762]                           ; [data_f7cc762] "NOFILE"
  e83adbb  mov r13d,0xB8000                              
  e83adc1  cmp qword ptr [r15],0                         
  e83adc5  jne 0xE83AE50                                 ; -> loc_e83ae50
  e83adcb  nop [rax+rax]                                 

loc_e83add0:  ; from e83ae6c
  e83add0  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  e83add7  mov rax,[rcx]                                 
  e83adda  mov rax,[rax+8]                               
  e83adde  mov [rsp+0x20],r12                            
  e83ade3  mov dword ptr [rsp+0x28],0                    
  e83adeb  mov r8d,0xB8008                               
  e83adf1  mov r9d,8                                     
  e83adf7  xor edx,edx                                   
  e83adf9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  e83adff  mov rdi,rax                                   
  e83ae02  mov r8d,0xB8008                               
  e83ae08  mov rcx,rax                                   
  e83ae0b  xor edx,edx                                   
  e83ae0d  call 0xEEC6ED0                                ; -> sub_eec6ed0
  e83ae12  mov [r15],rdi                                 
  e83ae15  mov rax,[rsi+0xB8000]                         
  e83ae1c  mov [rax+8],rdi                               
  e83ae20  mov rax,[rsi+0xB8000]                         
  e83ae27  add qword ptr [rax+0x10],0xB8000              
  e83ae2f  mov rax,[rsi+0xB8000]                         
  e83ae36  cmp qword ptr [rax],0                         
  e83ae3a  jne short 0xE83AE50                           ; -> loc_e83ae50
  e83ae3c  mov rcx,[r15]                                 
  e83ae3f  mov [rax],rcx                                 
  e83ae42  nop [rax+rax]                                 

loc_e83ae50:  ; from e83adc5, e83ae3a, e83ae6a
  e83ae50  cmp r14,0xB8001                               
  e83ae57  jb short 0xE83AE7A                            ; -> loc_e83ae7a
  e83ae59  mov r15,[r15]                                 
  e83ae5c  add r15,r13                                   
  e83ae5f  add r14,0xFFFFFFFFFFF48000                    
  e83ae66  cmp qword ptr [r15],0                         
  e83ae6a  jne short 0xE83AE50                           ; -> loc_e83ae50
  e83ae6c  jmp 0xE83ADD0                                 ; -> loc_e83add0

loc_e83ae71:  ; from e83ad3b
  e83ae71  test rax,rax                                  
  e83ae74  jne short 0xE83AE81                           ; -> loc_e83ae81
  e83ae76  xor ecx,ecx                                   
  e83ae78  jmp short 0xE83AE85                           ; -> loc_e83ae85

loc_e83ae7a:  ; from e83ae57
  e83ae7a  mov rax,[rsi+0xB8000]                         

loc_e83ae81:  ; from e83ae74
  e83ae81  mov rcx,[rax+0x10]                            

loc_e83ae85:  ; from e83ad98, e83ae78
  e83ae85  shr rcx,3                                     
  e83ae89  mov rax,rcx                                   
  e83ae8c  mul rbx                                       
  e83ae8f  mov r8,rdx                                    
  e83ae92  shr r8,1                                      
  e83ae95  add r8,0x1000                                 

loc_e83ae9c:  ; from e83acfc, e83ad20
  e83ae9c  imul rax,r8,0xB8                              
  e83aea3  mov rcx,[rsi+0xB8010]                         
  e83aeaa  cmp rcx,rax                                   
  e83aead  cmova rax,rcx                                 
  e83aeb1  mov [rsi+0xB8010],rax                         
  e83aeb8  add rsp,0x30                                  
  e83aebc  pop rbx                                       
  e83aebd  pop rdi                                       
  e83aebe  pop rsi                                       
  e83aebf  pop r12                                       
  e83aec1  pop r13                                       
  e83aec3  pop r14                                       
  e83aec5  pop r15                                       
  e83aec7  ret                                           
  e83aec8  int3                                          
  e83aec9  int3                                          
  e83aeca  int3                                          
  e83aecb  int3                                          
  e83aecc  int3                                          
  e83aecd  int3                                          
  e83aece  int3                                          
  e83aecf  int3                                          
  e83aed0  push rsi                                      
  e83aed1  push rdi                                      
  e83aed2  push rbx                                      
  e83aed3  sub rsp,0x20                                  
  e83aed7  mov rdi,rdx                                   
  e83aeda  mov rsi,rcx                                   
  e83aedd  movzx ecx,byte ptr [rcx+0xC018]               
  e83aee4  cmp rdx,0x1000                                
  e83aeeb  setae dl                                      
  e83aeee  mov al,1                                      
  e83aef0  test dl,cl                                    
  e83aef2  jne short 0xE83AF5C                           ; -> loc_e83af5c
  e83aef4  mov rax,0xAAAAAAAAAAAAAAAB                    
  e83aefe  mul qword ptr [rsi+0xC008]                    
  e83af05  shr rdx,3                                     
  e83af09  mov eax,ecx                                   
  e83af0b  cmp rdi,rdx                                   
  e83af0e  jb short 0xE83AF5C                            ; -> loc_e83af5c
  e83af10  mov rbx,rdi                                   
  e83af13  and rbx,0xFFFFFFFFFFFFF000                    
  e83af1a  add rbx,0x1000                                
  e83af21  mov rcx,rsi                                   
  e83af24  mov rdx,rbx                                   
  e83af27  call 0xE835F00                                ; -> sub_e835f00
  e83af2c  mov rax,0xAAAAAAAAAAAAAAAB                    
  e83af36  mul qword ptr [rsi+0xC008]                    
  e83af3d  shr rdx,3                                     
  e83af41  cmp rdx,rbx                                   
  e83af44  jb short 0xE83AF9F                            ; -> loc_e83af9f

loc_e83af46:  ; from e83af9d
  e83af46  shl rbx,2                                     
  e83af4a  lea rax,[rbx+rbx*2]                           
  e83af4e  mov [rsi+0xC008],rax                          
  e83af55  movzx eax,byte ptr [rsi+0xC018]               

loc_e83af5c:  ; from e83aef2, e83af0e
  e83af5c  cmp rdi,0x1000                                
  e83af63  jb 0xE83AFEA                                  ; -> loc_e83afea
  e83af69  test al,al                                    
  e83af6b  je 0xE83AFEA                                  ; -> loc_e83afea
  e83af71  lea rdx,[0xF7F68E3]                           ; [data_f7f68e3] "FAILED: accessing a guarded paged heap backed array out of b..."
  e83af78  xor ecx,ecx                                   
  e83af7a  call 0xBC5F110                                ; -> sub_bc5f110
  e83af7f  shl rdi,2                                     
  e83af83  lea rcx,[rdi+rdi*2]                           
  e83af87  jmp short 0xE83AFFF                           ; -> loc_e83afff
  e83af89  nop [rax]                                     ; R ret@bc5f110+0x0

loc_e83af90:  ; from e83afb2
  e83af90  add rax,rsi                                   

loc_e83af93:  ; from e83afe8
  e83af93  mov byte ptr [rax+8],0                        
  e83af97  inc rdx                                       
  e83af9a  cmp rdx,rbx                                   
  e83af9d  je short 0xE83AF46                            ; -> loc_e83af46

loc_e83af9f:  ; from e83af44
  e83af9f  lea rax,[rdx*4]                               
  e83afa7  lea rax,[rax+rax*2]                           
  e83afab  cmp rdx,0xFFF                                 
  e83afb2  jbe short 0xE83AF90                           ; -> loc_e83af90
  e83afb4  add rax,0xFFFFFFFFFFFF4000                    
  e83afba  mov rcx,[rsi+0xC000]                          
  e83afc1  mov rcx,[rcx]                                 
  e83afc4  cmp rax,0xC000                                
  e83afca  jb short 0xE83AFE5                            ; -> loc_e83afe5
  e83afcc  nop [rax]                                     

loc_e83afd0:  ; from e83afe3
  e83afd0  add rax,0xFFFFFFFFFFFF4000                    
  e83afd6  mov rcx,[rcx+0xC000]                          
  e83afdd  cmp rax,0xBFFF                                
  e83afe3  ja short 0xE83AFD0                            ; -> loc_e83afd0

loc_e83afe5:  ; from e83afca
  e83afe5  add rax,rcx                                   
  e83afe8  jmp short 0xE83AF93                           ; -> loc_e83af93

loc_e83afea:  ; from e83af63, e83af6b
  e83afea  lea rax,[rdi*4]                               
  e83aff2  lea rcx,[rax+rax*2]                           
  e83aff6  cmp rdi,0xFFF                                 
  e83affd  jbe short 0xE83B047                           ; -> loc_e83b047

loc_e83afff:  ; from e83af87
  e83afff  lea rax,[rcx-0xC000]                          
  e83b006  mov rdx,[rsi+0xC000]                          
  e83b00d  mov r8,[rdx]                                  
  e83b010  cmp rax,0xC000                                
  e83b016  jb 0xE83B0C6                                  ; -> loc_e83b0c6
  e83b01c  mov r9,rax                                    
  e83b01f  add rcx,0xFFFFFFFFFFFE8000                    
  e83b026  mov rdx,0xAAAAAAAAAAAAAAAB                    
  e83b030  mov rax,rcx                                   
  e83b033  mul rdx                                       
  e83b036  shr rdx,0xF                                   
  e83b03a  mov eax,edx                                   
  e83b03c  not eax                                       
  e83b03e  test al,7                                     
  e83b040  jne short 0xE83B04F                           ; -> loc_e83b04f
  e83b042  mov rax,r9                                    
  e83b045  jmp short 0xE83B072                           ; -> loc_e83b072

loc_e83b047:  ; from e83affd
  e83b047  add rsi,rcx                                   
  e83b04a  mov rax,rsi                                   
  e83b04d  jmp short 0xE83B0C9                           ; -> loc_e83b0c9

loc_e83b04f:  ; from e83b040
  e83b04f  inc edx                                       
  e83b051  and edx,7                                     
  e83b054  neg rdx                                       
  e83b057  mov rax,r9                                    
  e83b05a  nop [rax+rax]                                 

loc_e83b060:  ; from e83b070
  e83b060  add rax,0xFFFFFFFFFFFF4000                    
  e83b066  mov r8,[r8+0xC000]                            
  e83b06d  inc rdx                                       
  e83b070  jne short 0xE83B060                           ; -> loc_e83b060

loc_e83b072:  ; from e83b045
  e83b072  cmp rcx,0x54000                               
  e83b079  jb short 0xE83B0C6                            ; -> loc_e83b0c6
  e83b07b  nop [rax+rax]                                 

loc_e83b080:  ; from e83b0c4
  e83b080  mov rcx,[r8+0xC000]                           
  e83b087  mov rcx,[rcx+0xC000]                          
  e83b08e  mov rcx,[rcx+0xC000]                          
  e83b095  mov rcx,[rcx+0xC000]                          
  e83b09c  mov rcx,[rcx+0xC000]                          
  e83b0a3  mov rcx,[rcx+0xC000]                          
  e83b0aa  mov rcx,[rcx+0xC000]                          
  e83b0b1  add rax,0xFFFFFFFFFFFA0000                    
  e83b0b7  mov r8,[rcx+0xC000]                           
  e83b0be  cmp rax,0xBFFF                                
  e83b0c4  ja short 0xE83B080                            ; -> loc_e83b080

loc_e83b0c6:  ; from e83b016, e83b079
  e83b0c6  add rax,r8                                    

loc_e83b0c9:  ; from e83b04d
  e83b0c9  add rsp,0x20                                  
  e83b0cd  pop rbx                                       
  e83b0ce  pop rdi                                       
  e83b0cf  pop rsi                                       
  e83b0d0  ret                                           
  e83b0d1  int3                                          
  e83b0d2  int3                                          
  e83b0d3  int3                                          
  e83b0d4  int3                                          
  e83b0d5  int3                                          
  e83b0d6  int3                                          
  e83b0d7  int3                                          
  e83b0d8  int3                                          
  e83b0d9  int3                                          
  e83b0da  int3                                          
  e83b0db  int3                                          
  ... (--max 400)
```

## CALLERS
```
  0xe80dd60 sub_e80dd60 size 0x151
  0xe80dec0 sub_e80dec0 size 0xdad
  -- 2 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  56b67f0.md  size 0xc8  callees~22  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\56b67f0.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

