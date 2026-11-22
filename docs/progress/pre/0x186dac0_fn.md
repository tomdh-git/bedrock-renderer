sub_186dac0  [0x186dac0..0x186dffc)  size 0x53c  2 xrefs in
  186dac0  push rbp                                      
  186dac1  push r15                                      
  186dac3  push r14                                      
  186dac5  push rsi                                      
  186dac6  push rdi                                      
  186dac7  push rbx                                      
  186dac8  sub rsp,0x198                                 
  186dacf  lea rbp,[rsp+0x80]                            
  186dad7  movaps [rbp+0x100],xmm6                       
  186dade  mov qword ptr [rbp+0xF8],0xFFFFFFFFFFFFFFFE   
  186dae9  mov rsi,rdx                                   
  186daec  mov rbx,rcx                                   
  186daef  mov eax,[rbp+0x170]                           
  186daf5  mov rdi,[rcx+0x10]                            ; R a0+0x10
  186daf9  mov rcx,[rdi+0x48]                            ; R *(a0+0x10)+0x48
  186dafd  cmp qword ptr [rdi+0x50],0x10                 ; R *(a0+0x10)+0x50
  186db02  jb short 0x186DB0A                            ; -> loc_186db0a
  186db04  mov rdx,[rdi+0x38]                            ; R *(a0+0x10)+0x38
  186db08  jmp short 0x186DB0E                           ; -> loc_186db0e

loc_186db0a:  ; from 186db02
  186db0a  lea rdx,[rdi+0x38]                            

loc_186db0e:  ; from 186db08
  186db0e  mov [rbp-0x20],rdx                            
  186db12  mov [rbp-0x18],rcx                            
  186db16  xorps xmm0,xmm0                               
  186db19  movups [rbp-0x10],xmm0                        
  186db1d  mov qword ptr [rbp],0                         
  186db25  mov dword ptr [rbp+0xC],0xFFFFFFFF            
  186db2c  mov byte ptr [rbp+0x10],0                     
  186db30  mov qword ptr [rbp+0x18],0                    
  186db38  mov [rbp+8],eax                               
  186db3b  mov rax,[r8]                                  
  186db3e  test rax,rax                                  
  186db41  mov [rbp+0xF0],r9                             
  186db48  mov [rbp+0xE8],r8                             
  186db4f  je 0x186DBFC                                  ; -> loc_186dbfc
  186db55  movaps [rbp+0xA0],xmm0                        
  186db5c  mov rax,[rax]                                 
  186db5f  lea r14,[rbp+0xA0]                            
  186db66  mov rcx,r8                                    
  186db69  mov rdx,r14                                   
  186db6c  mov r15,r8                                    
  186db6f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186db75  mov rax,[r15]                                 
  186db78  mov qword ptr [r15],0                         
  186db7f  mov [rbp+0xA0],rax                            
  186db86  mov [rbp+0xE0],rbx                            
  186db8d  mov qword ptr [rbp+0x48],0                    
  186db95  lea rax,[0xF0FC660]                           ; [data_f0fc660]
  186db9c  mov [rbp+0x40],rax                            
  186dba0  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  186dba7  mov rax,[rcx]                                 
  186dbaa  mov rax,[rax+8]                               
  186dbae  mov edx,0x48                                  
  186dbb3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dbb9  nop                                           
  186dbba  mov r15,rax                                   
  186dbbd  test rax,rax                                  
  186dbc0  je 0x186DFCC                                  ; -> loc_186dfcc

loc_186dbc6:  ; from 186dfd7
  186dbc6  xorps xmm6,xmm6                               
  186dbc9  movups [r15],xmm6                             
  186dbcd  mov rax,[rbp+0xA0]                            
  186dbd4  test rax,rax                                  
  186dbd7  je 0x186DCAE                                  ; -> loc_186dcae
  186dbdd  mov rax,[rax]                                 
  186dbe0  lea rcx,[rbp+0xA0]                            
  186dbe7  mov rdx,r15                                   
  186dbea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dbf0  mov rax,[rbp+0xA0]                            
  186dbf7  jmp 0x186DCB0                                 ; -> loc_186dcb0

loc_186dbfc:  ; from 186db4f
  186dbfc  mov rax,[r9]                                  
  186dbff  test rax,rax                                  
  186dc02  je 0x186DF5D                                  ; -> loc_186df5d
  186dc08  movaps [rbp+0xA0],xmm0                        
  186dc0f  mov rax,[rax]                                 
  186dc12  lea r14,[rbp+0xA0]                            
  186dc19  mov rcx,r9                                    
  186dc1c  mov rdx,r14                                   
  186dc1f  mov r15,r9                                    
  186dc22  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dc28  mov rax,[r15]                                 
  186dc2b  mov qword ptr [r15],0                         
  186dc32  mov [rbp+0xA0],rax                            
  186dc39  mov [rbp+0xE0],rbx                            
  186dc40  mov qword ptr [rbp+0x48],0                    
  186dc48  lea rax,[0xF0FC678]                           ; [data_f0fc678]
  186dc4f  mov [rbp+0x40],rax                            
  186dc53  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  186dc5a  mov rax,[rcx]                                 
  186dc5d  mov rax,[rax+8]                               
  186dc61  mov edx,0x48                                  
  186dc66  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dc6c  nop                                           
  186dc6d  mov rbx,rax                                   
  186dc70  test rax,rax                                  
  186dc73  je 0x186DFEC                                  ; -> loc_186dfec

loc_186dc79:  ; from 186dff7
  186dc79  xorps xmm6,xmm6                               
  186dc7c  movups [rbx],xmm6                             
  186dc7f  mov rax,[rbp+0xA0]                            
  186dc86  test rax,rax                                  
  186dc89  je 0x186DF68                                  ; -> loc_186df68
  186dc8f  mov rax,[rax]                                 
  186dc92  lea rcx,[rbp+0xA0]                            
  186dc99  mov rdx,rbx                                   
  186dc9c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dca2  mov rax,[rbp+0xA0]                            
  186dca9  jmp 0x186DF6A                                 ; -> loc_186df6a

loc_186dcae:  ; from 186dbd7
  186dcae  xor eax,eax                                   

loc_186dcb0:  ; from 186dbf7
  186dcb0  mov [r15],rax                                 
  186dcb3  mov rax,[rbp+0xE0]                            
  186dcba  mov [r15+0x40],rax                            
  186dcbe  mov [rbp+0x48],r15                            
  186dcc2  movaps [rbp+0xA0],xmm6                        
  186dcc9  mov rax,[rdi]                                 
  186dccc  mov rax,[rax+0x40]                            
  186dcd0  mov rcx,rdi                                   
  186dcd3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dcd9  nop                                           
  186dcda  lea r15,[rbp+0x40]                            
  186dcde  mov [rsp+0x28],r15                            
  186dce3  mov [rsp+0x20],r14                            
  186dce8  lea rdx,[rbp+0x80]                            
  186dcef  lea r8,[rbp-0x20]                             
  186dcf3  mov rcx,rdi                                   
  186dcf6  mov r9d,eax                                   
  186dcf9  call 0x58CA10                                 ; -> sub_58ca10
  186dcfe  nop                                           
  186dcff  mov rax,[rbp+0x40]                            
  186dd03  test rax,rax                                  
  186dd06  je short 0x186DD16                            ; -> loc_186dd16
  186dd08  mov rax,[rax+8]                               
  186dd0c  lea rcx,[rbp+0x40]                            
  186dd10  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_186dd16:  ; from 186dd06
  186dd16  mov rdi,[rbp+0xF0]                            
  186dd1d  mov rax,[rdi]                                 
  186dd20  test rax,rax                                  
  186dd23  je 0x186DF07                                  ; -> loc_186df07
  186dd29  xorps xmm0,xmm0                               
  186dd2c  movaps [rbp+0xA0],xmm0                        
  186dd33  mov rax,[rax]                                 
  186dd36  lea rdx,[rbp+0xA0]                            
  186dd3d  mov rcx,rdi                                   
  186dd40  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dd46  mov rax,[rdi]                                 
  186dd49  mov qword ptr [rdi],0                         
  186dd50  mov [rbp+0xA0],rax                            
  186dd57  mov [rbp+0xE0],rbx                            
  186dd5e  lea rax,[0xF0FC678]                           ; [data_f0fc678]
  186dd65  mov [rbp+0x40],rax                            
  186dd69  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  186dd70  mov rax,[rcx]                                 
  186dd73  mov rax,[rax+8]                               
  186dd77  mov edx,0x48                                  
  186dd7c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dd82  nop                                           
  186dd83  mov rdi,rax                                   
  186dd86  test rax,rax                                  
  186dd89  je 0x186DFDC                                  ; -> loc_186dfdc

loc_186dd8f:  ; from 186dfe7
  186dd8f  movups [rdi],xmm6                             
  186dd92  mov rax,[rbp+0xA0]                            
  186dd99  test rax,rax                                  
  186dd9c  je short 0x186DDBA                            ; -> loc_186ddba
  186dd9e  mov rax,[rax]                                 
  186dda1  lea rcx,[rbp+0xA0]                            
  186dda8  mov rdx,rdi                                   
  186ddab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186ddb1  mov rax,[rbp+0xA0]                            
  186ddb8  jmp short 0x186DDBC                           ; -> loc_186ddbc

loc_186ddba:  ; from 186dd9c
  186ddba  xor eax,eax                                   

loc_186ddbc:  ; from 186ddb8
  186ddbc  mov [rdi],rax                                 
  186ddbf  mov rax,[rbp+0xE0]                            
  186ddc6  mov [rdi+0x40],rax                            
  186ddca  mov [rbp+0x48],rdi                            
  186ddce  lea rax,[0xF820C35]                           ; [data_f820c35] "Bedrock::Threading::Async<void> __cdecl ResourceLoadManager:..."
  186ddd5  mov [rbp+0xA0],rax                            
  186dddc  mov qword ptr [rbp+0xA8],0x95                 
  186dde7  lea rax,[0xF578B2C]                           ; [data_f578b2c] "D:\a\_work\1\s\src/engine/PackInfrastructure/src/resources/R..."
  186ddee  mov [rbp+0xB0],rax                            
  186ddf5  mov qword ptr [rbp+0xB8],0x52                 
  186de00  movaps xmm0,[0xF0FBCD0]                       ; [data_f0fbcd0]
  186de07  movups [rbp+0xC0],xmm0                        
  186de0e  mov qword ptr [rbp+0xD8],0                    
  186de19  mov byte ptr [rbp+0xD0],1                     
  186de20  mov rcx,[rbp+0x90]                            
  186de27  movaps xmm0,[rbp+0x80]                        
  186de2e  movaps [rbp+0x80],xmm6                        
  186de35  movaps [rbp-0x30],xmm0                        
  186de39  mov [rsp+0x28],r15                            
  186de3e  lea rax,[rbp-0x30]                            
  186de42  mov [rsp+0x20],rax                            
  186de47  lea rdx,[rbp+0x20]                            
  186de4b  lea r8,[rbp+0xA0]                             
  186de52  xor r9d,r9d                                   
  186de55  call 0x71BC70                                 ; -> sub_71bc70
  186de5a  nop                                           
  186de5b  movaps xmm0,[rbp+0x20]                        
  186de5f  xorps xmm1,xmm1                               
  186de62  movaps [rbp+0x20],xmm1                        
  186de66  mov rdi,[rbp+0x88]                            
  186de6d  movaps [rbp+0x80],xmm0                        
  186de74  test rdi,rdi                                  
  186de77  je short 0x186DEE5                            ; -> loc_186dee5
  186de79  lock dec dword ptr [rdi+8]                    
  186de7d  jne short 0x186DEA4                           ; -> loc_186dea4
  186de7f  mov rax,[rdi]                                 
  186de82  mov rax,[rax]                                 
  186de85  mov rcx,rdi                                   
  186de88  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186de8e  lock dec dword ptr [rdi+0xC]                  
  186de92  jne short 0x186DEA4                           ; -> loc_186dea4
  186de94  mov rax,[rdi]                                 
  186de97  mov rax,[rax+8]                               
  186de9b  mov rcx,rdi                                   
  186de9e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_186dea4:  ; from 186de7d, 186de92
  186dea4  mov rdi,[rbp+0x28]                            
  186dea8  mov rax,[rbp+0x30]                            
  186deac  mov [rbp+0x90],rax                            
  186deb3  test rdi,rdi                                  
  186deb6  je short 0x186DEF0                            ; -> loc_186def0
  186deb8  lock dec dword ptr [rdi+8]                    
  186debc  jne short 0x186DEF0                           ; -> loc_186def0
  186debe  mov rax,[rdi]                                 
  186dec1  mov rax,[rax]                                 
  186dec4  mov rcx,rdi                                   
  186dec7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186decd  lock dec dword ptr [rdi+0xC]                  
  186ded1  jne short 0x186DEF0                           ; -> loc_186def0
  186ded3  mov rax,[rdi]                                 
  186ded6  mov rax,[rax+8]                               
  186deda  mov rcx,rdi                                   
  186dedd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dee3  jmp short 0x186DEF0                           ; -> loc_186def0

loc_186dee5:  ; from 186de77
  186dee5  mov rax,[rbp+0x30]                            
  186dee9  mov [rbp+0x90],rax                            

loc_186def0:  ; from 186deb6, 186debc, 186ded1, 186dee3
  186def0  mov rax,[rbp+0x40]                            
  186def4  test rax,rax                                  
  186def7  je short 0x186DF07                            ; -> loc_186df07
  186def9  mov rax,[rax+8]                               
  186defd  lea rcx,[rbp+0x40]                            
  186df01  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_186df07:  ; from 186dd23, 186def7
  186df07  movaps xmm0,[rbp+0x80]                        
  186df0e  movups [rsi],xmm0                             

loc_186df11:  ; from 186df66, 186dfb3, 186dfc7
  186df11  mov rcx,[rbp+0xE8]                            
  186df18  mov rax,[rcx]                                 
  186df1b  test rax,rax                                  
  186df1e  je short 0x186DF2A                            ; -> loc_186df2a
  186df20  mov rax,[rax+8]                               
  186df24  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_186df2a:  ; from 186df1e
  186df2a  mov rcx,[rbp+0xF0]                            
  186df31  mov rax,[rcx]                                 
  186df34  test rax,rax                                  
  186df37  je short 0x186DF43                            ; -> loc_186df43
  186df39  mov rax,[rax+8]                               
  186df3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_186df43:  ; from 186df37
  186df43  mov rax,rsi                                   
  186df46  movaps xmm6,[rbp+0x100]                       
  186df4d  add rsp,0x198                                 
  186df54  pop rbx                                       
  186df55  pop rdi                                       
  186df56  pop rsi                                       
  186df57  pop r14                                       
  186df59  pop r15                                       
  186df5b  pop rbp                                       
  186df5c  ret                                           

loc_186df5d:  ; from 186dc02
  186df5d  mov rcx,rsi                                   
  186df60  call 0x76AF20                                 ; -> sub_76af20
  186df65  nop                                           
  186df66  jmp short 0x186DF11                           ; -> loc_186df11

loc_186df68:  ; from 186dc89
  186df68  xor eax,eax                                   

loc_186df6a:  ; from 186dca9
  186df6a  mov [rbx],rax                                 
  186df6d  mov rax,[rbp+0xE0]                            
  186df74  mov [rbx+0x40],rax                            
  186df78  mov [rbp+0x48],rbx                            
  186df7c  movaps [rbp+0xA0],xmm6                        
  186df83  lea rax,[rbp+0x40]                            
  186df87  mov [rsp+0x28],rax                            
  186df8c  mov [rsp+0x20],r14                            
  186df91  lea rdx,[rbp-0x50]                            
  186df95  lea r8,[rbp-0x20]                             
  186df99  mov rcx,rdi                                   
  186df9c  xor r9d,r9d                                   
  186df9f  call 0x71BC70                                 ; -> sub_71bc70
  186dfa4  nop                                           
  186dfa5  movaps xmm0,[rbp-0x50]                        
  186dfa9  movups [rsi],xmm0                             
  186dfac  mov rax,[rbp+0x40]                            
  186dfb0  test rax,rax                                  
  186dfb3  je 0x186DF11                                  ; -> loc_186df11
  186dfb9  mov rax,[rax+8]                               
  186dfbd  lea rcx,[rbp+0x40]                            
  186dfc1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  186dfc7  jmp 0x186DF11                                 ; -> loc_186df11

loc_186dfcc:  ; from 186dbc0
  186dfcc  mov ecx,0x48                                  
  186dfd1  call 0x9BC830                                 ; -> sub_9bc830
  186dfd6  nop                                           
  186dfd7  jmp 0x186DBC6                                 ; -> loc_186dbc6

loc_186dfdc:  ; from 186dd89
  186dfdc  mov ecx,0x48                                  
  186dfe1  call 0x9BC830                                 ; -> sub_9bc830
  186dfe6  nop                                           
  186dfe7  jmp 0x186DD8F                                 ; -> loc_186dd8f

loc_186dfec:  ; from 186dc73
  186dfec  mov ecx,0x48                                  
  186dff1  call 0x9BC830                                 ; -> sub_9bc830
  186dff6  nop                                           
  186dff7  jmp 0x186DC79                                 ; -> loc_186dc79
