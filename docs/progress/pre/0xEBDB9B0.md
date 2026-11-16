# preflight 0xEBDB9B0

## fn
```
sub_ebdb9b0  [0xebdb9b0..0xebdba21)  size 0x71  1 xrefs in
  ebdb9b0  push rbx                                      
  ebdb9b2  sub rsp,0x30                                  
  ebdb9b6  mov [rcx+0x50],rdx                            ; W a0+0x50
  ebdb9ba  xor eax,eax                                   
  ebdb9bc  mov [rcx+0x1C0],r9d                           ; W a0+0x1C0
  ebdb9c3  mov rbx,rcx                                   
  ebdb9c6  mov [rcx+0x58],r8                             ; W a0+0x58
  ebdb9ca  lea r8,[0xEBDBBE0]                            ; [sub_ebdbbe0]
  ebdb9d1  mov edx,r9d                                   
  ebdb9d4  mov r9,rcx                                    
  ebdb9d7  mov byte ptr [rcx+0x1C8],1                    ; W a0+0x1C8
  ebdb9de  xor ecx,ecx                                   
  ebdb9e0  mov [rsp+0x28],rax                            
  ebdb9e5  mov [rsp+0x20],eax                            
  ebdb9e9  call qword ptr [0xF9A6FD0]                    ; [data_f9a6fd0]
  ebdb9ef  lea rcx,[rbx+0x140]                           ; R a0+0x140
  ebdb9f6  mov edx,0xFFFFFFFF                            
  ebdb9fb  mov [rbx+0x10],rax                            ; W a0+0x10
  ebdb9ff  call 0xEBDBC60                                ; -> sub_ebdbc60
  ebdba04  mov rdx,[rsp+0x60]                            
  ebdba09  test rdx,rdx                                  
  ebdba0c  je short 0xEBDBA1B                            ; -> loc_ebdba1b
  ebdba0e  mov rcx,rbx                                   
  ebdba11  add rsp,0x30                                  
  ebdba15  pop rbx                                       
  ebdba16  jmp 0xEBDBA90                                 ; -> sub_ebdba90

loc_ebdba1b:  ; from ebdba0c
  ebdba1b  add rsp,0x30                                  
  ebdba1f  pop rbx                                       
  ebdba20  ret                                           

```

## callers
```
  sub_bc63690                  1 call site(s)
-- 1 calling function(s)

```

## callees
```
sub_ebdb9b0  [0xebdb9b0..0xebdba21)
  call sub_ebdbc60                  x1

```

## stores into [reg+off] (non-stack)
```
  ebdb9b6  mov [rcx+0x50],rdx                            ; W a0+0x50
  ebdb9bc  mov [rcx+0x1C0],r9d                           ; W a0+0x1C0
  ebdb9c6  mov [rcx+0x58],r8                             ; W a0+0x58
  ebdb9d7  mov byte ptr [rcx+0x1C8],1                    ; W a0+0x1C8
  ebdb9fb  mov [rbx+0x10],rax                            ; W a0+0x10
  ebdba63  mov qword ptr [rbx+0x10],0xFFFFFFFFFFFFFFFF   
  ebdba6b  mov byte ptr [rbx+0x1C8],0                    
```

## listing (100 instr)
```
sub_ebdb9b0  [0xebdb9b0..0xebdd9b0)  size 0x2000  1 xrefs in
  ebdb9b0  push rbx                                      
  ebdb9b2  sub rsp,0x30                                  
  ebdb9b6  mov [rcx+0x50],rdx                            ; W a0+0x50
  ebdb9ba  xor eax,eax                                   
  ebdb9bc  mov [rcx+0x1C0],r9d                           ; W a0+0x1C0
  ebdb9c3  mov rbx,rcx                                   
  ebdb9c6  mov [rcx+0x58],r8                             ; W a0+0x58
  ebdb9ca  lea r8,[0xEBDBBE0]                            ; [sub_ebdbbe0]
  ebdb9d1  mov edx,r9d                                   
  ebdb9d4  mov r9,rcx                                    
  ebdb9d7  mov byte ptr [rcx+0x1C8],1                    ; W a0+0x1C8
  ebdb9de  xor ecx,ecx                                   
  ebdb9e0  mov [rsp+0x28],rax                            
  ebdb9e5  mov [rsp+0x20],eax                            
  ebdb9e9  call qword ptr [0xF9A6FD0]                    ; [data_f9a6fd0]
  ebdb9ef  lea rcx,[rbx+0x140]                           ; R a0+0x140
  ebdb9f6  mov edx,0xFFFFFFFF                            
  ebdb9fb  mov [rbx+0x10],rax                            ; W a0+0x10
  ebdb9ff  call 0xEBDBC60                                ; -> sub_ebdbc60
  ebdba04  mov rdx,[rsp+0x60]                            
  ebdba09  test rdx,rdx                                  
  ebdba0c  je short 0xEBDBA1B                            ; -> loc_ebdba1b
  ebdba0e  mov rcx,rbx                                   
  ebdba11  add rsp,0x30                                  
  ebdba15  pop rbx                                       
  ebdba16  jmp 0xEBDBA90                                 ; -> loc_ebdba90

loc_ebdba1b:  ; from ebdba0c
  ebdba1b  add rsp,0x30                                  
  ebdba1f  pop rbx                                       
  ebdba20  ret                                           
  ebdba21  int3                                          
  ebdba22  int3                                          
  ebdba23  int3                                          
  ebdba24  int3                                          
  ebdba25  int3                                          
  ebdba26  int3                                          
  ebdba27  int3                                          
  ebdba28  int3                                          
  ebdba29  int3                                          
  ebdba2a  int3                                          
  ebdba2b  int3                                          
  ebdba2c  int3                                          
  ebdba2d  int3                                          
  ebdba2e  int3                                          
  ebdba2f  int3                                          
  ebdba30  push rbx                                      
  ebdba32  sub rsp,0x20                                  
  ebdba36  mov rbx,rcx                                   
  ebdba39  mov edx,0xFFFFFFFF                            
  ebdba3e  mov rcx,[rcx+0x10]                            
  ebdba42  call qword ptr [0xF9A7B60]                    ; [data_f9a7b60]
  ebdba48  mov rcx,[rbx+0x10]                            
  ebdba4c  lea rdx,[rbx+0x1C4]                           
  ebdba53  call qword ptr [0xF9A7000]                    ; [data_f9a7000]
  ebdba59  mov rcx,[rbx+0x10]                            
  ebdba5d  call qword ptr [0xF9A7AD0]                    ; [data_f9a7ad0]
  ebdba63  mov qword ptr [rbx+0x10],0xFFFFFFFFFFFFFFFF   
  ebdba6b  mov byte ptr [rbx+0x1C8],0                    
  ebdba72  add rsp,0x20                                  
  ebdba76  pop rbx                                       
  ebdba77  ret                                           
  ebdba78  int3                                          
  ebdba79  int3                                          
  ebdba7a  int3                                          
  ebdba7b  int3                                          
  ebdba7c  int3                                          
  ebdba7d  int3                                          
  ebdba7e  int3                                          
  ebdba7f  int3                                          
  ebdba80  movzx eax,byte ptr [rcx+0x1C8]                
  ebdba87  ret                                           
  ebdba88  int3                                          
  ebdba89  int3                                          
  ebdba8a  int3                                          
  ebdba8b  int3                                          
  ebdba8c  int3                                          
  ebdba8d  int3                                          
  ebdba8e  int3                                          
  ebdba8f  int3                                          

loc_ebdba90:  ; from ebdba16
  ebdba90  sub rsp,0x48                                  
  ebdba94  mov dword ptr [rsp+0x20],0x1000               
  ebdba9c  mov [rsp+0x28],rdx                            
  ebdbaa1  mov eax,[rcx+0x18]                            
  ebdbaa4  mov [rsp+0x30],eax                            
  ebdbaa8  mov dword ptr [rsp+0x34],0                    
  ebdbab0  lea r9,[rsp+0x20]                             
  ebdbab5  xor edx,edx                                   
  ebdbab7  mov r8d,6                                     
  ebdbabd  mov ecx,0x406D1388                            
  ebdbac2  call qword ptr [0xF9A7648]                    ; [data_f9a7648]
  ebdbac8  jmp short 0xEBDBACA                           ; -> loc_ebdbaca

loc_ebdbaca:  ; from ebdbac8
  ebdbaca  add rsp,0x48                                  
  ebdbace  ret                                           
  ebdbacf  int3                                          
  ebdbad0  push rbx                                      
  ebdbad2  sub rsp,0x20                                  
  ebdbad6  mov rbx,rcx                                   
  ebdbad9  add rcx,0x60                                  
  ebdbadd  call 0xEA60400                                ; -> sub_ea60400
  ebdbae2  lea rcx,[rbx+0x40]                            
  ebdbae6  call 0xEBDB780                                ; -> sub_ebdb780
  ... (--max 100)

```
