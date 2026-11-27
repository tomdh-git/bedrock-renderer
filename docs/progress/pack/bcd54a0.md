# ctxpack build 0xbcd54a0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:4aa79c0fe0403206218642539e682a39a0af5f62d67d032bda989fd61bce04cd,data=native_deps.tsv:1fe4952061656732bfc6db3f2d9fd9cab2b08869dc95b7037670b5bec4910ae4,data=native_boundary.tsv:6e7ad029f069c6b1fb5e2798ef91f760a7586073ba5e6351050cf30070171607,data=native_boundary_candidates.tsv:8bb54e181419c9c42374be3142e4291934993a869d499a2b80e595610c86b8d9

## HEADER
  rva        : 0xbcd54a0
  size       : 0xb9 (185 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 1 (direct), depth 1
  callers    : 4

## EXACT LISTING (0xbcd54a0..0xbcd5559)
```
sub_bcd54a0  [0xbcd54a0..0xbcd74a0)  size 0x2000  4 xrefs in
  bcd54a0  push rsi                                      
  bcd54a1  push rdi                                      
  bcd54a2  sub rsp,0x28                                  
  bcd54a6  mov rsi,rcx                                   
  bcd54a9  mov rdi,[rcx+0x40]                            ; R a0+0x40
  bcd54ad  test rdi,rdi                                  
  bcd54b0  je short 0xBCD54DD                            ; -> loc_bcd54dd
  bcd54b2  lock dec dword ptr [rdi+8]                    ; W *(a0+0x40)+0x8
  bcd54b6  jne short 0xBCD54DD                           ; -> loc_bcd54dd
  bcd54b8  mov rax,[rdi]                                 ; R *(a0+0x40)+0x0
  bcd54bb  mov rax,[rax]                                 ; R *(*(a0+0x40)+0x0)+0x0
  bcd54be  mov rcx,rdi                                   
  bcd54c1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcd54c7  lock dec dword ptr [rdi+0xC]                  ; W *(a0+0x40)+0xC
  bcd54cb  jne short 0xBCD54DD                           ; -> loc_bcd54dd
  bcd54cd  mov rax,[rdi]                                 ; R *(a0+0x40)+0x0
  bcd54d0  mov rax,[rax+8]                               ; R *(*(a0+0x40)+0x0)+0x8
  bcd54d4  mov rcx,rdi                                   
  bcd54d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bcd54dd:  ; from bcd54b0, bcd54b6, bcd54cb
  bcd54dd  mov rax,[rsi+0x28]                            ; R a0+0x28
  bcd54e1  cmp rax,0x10                                  
  bcd54e5  jb short 0xBCD5518                            ; -> loc_bcd5518
  bcd54e7  mov rcx,[rsi+0x10]                            ; R a0+0x10
  bcd54eb  lea rdx,[rax+1]                               ; R *(a0+0x28)+0x1
  bcd54ef  cmp rdx,0x1000                                
  bcd54f6  jb short 0xBCD5513                            ; -> loc_bcd5513
  bcd54f8  mov r8,[rcx-8]                                ; R *(a0+0x10)-0x8
  bcd54fc  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd5500  sub rcx,r8                                    
  bcd5503  cmp rcx,0x20                                  
  bcd5507  jae short 0xBCD553F                           ; -> loc_bcd553f
  bcd5509  add rax,0x28                                  
  bcd550d  mov rdx,rax                                   
  bcd5510  mov rcx,r8                                    

loc_bcd5513:  ; from bcd54f6
  bcd5513  call 0xE935700                                ; -> sub_e935700

loc_bcd5518:  ; from bcd54e5
  bcd5518  mov qword ptr [rsi+0x20],0                    ; W a0+0x20
  bcd5520  mov qword ptr [rsi+0x28],0xF                  ; W a0+0x28
  bcd5528  mov byte ptr [rsi+0x10],0                     ; W a0+0x10
  bcd552c  mov edx,0x48                                  
  bcd5531  mov rcx,rsi                                   
  bcd5534  add rsp,0x28                                  
  bcd5538  pop rdi                                       
  bcd5539  pop rsi                                       
  bcd553a  jmp 0xE935700                                 ; -> sub_e935700

loc_bcd553f:  ; from bcd5507
  bcd553f  mov qword ptr [rsp+0x20],0                    
  bcd5548  xor ecx,ecx                                   
  bcd554a  xor edx,edx                                   
  bcd554c  xor r8d,r8d                                   
  bcd554f  xor r9d,r9d                                   
  bcd5552  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd5558  int3                                          
  bcd5559  int3                                          
  bcd555a  int3                                          
  bcd555b  int3                                          
  bcd555c  int3                                          
  bcd555d  int3                                          
  bcd555e  int3                                          
  bcd555f  int3                                          
  bcd5560  push rsi                                      
  bcd5561  sub rsp,0x20                                  
  bcd5565  mov rsi,rcx                                   
  bcd5568  mov rcx,[rcx+8]                               
  bcd556c  test rcx,rcx                                  
  bcd556f  je short 0xBCD5592                            ; -> loc_bcd5592
  bcd5571  add rcx,0x18                                  
  bcd5575  call 0xBCC7B00                                ; -> sub_bcc7b00
  bcd557a  mov rcx,[rsi+8]                               
  bcd557e  test rcx,rcx                                  
  bcd5581  je short 0xBCD5592                            ; -> loc_bcd5592
  bcd5583  mov edx,0x68                                  
  bcd5588  add rsp,0x20                                  
  bcd558c  pop rsi                                       
  bcd558d  jmp 0xE935700                                 ; -> sub_e935700

loc_bcd5592:  ; from bcd556f, bcd5581
  bcd5592  add rsp,0x20                                  
  bcd5596  pop rsi                                       
  bcd5597  ret                                           
  bcd5598  int3                                          
  bcd5599  int3                                          
  bcd559a  int3                                          
  bcd559b  int3                                          
  bcd559c  int3                                          
  bcd559d  int3                                          
  bcd559e  int3                                          
  bcd559f  int3                                          
  bcd55a0  push rbp                                      
  bcd55a1  push rsi                                      
  bcd55a2  push rdi                                      
  bcd55a3  push rbx                                      
  bcd55a4  sub rsp,0x58                                  
  bcd55a8  lea rbp,[rsp+0x50]                            
  bcd55ad  movaps [rbp-0x10],xmm6                        
  bcd55b1  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE   
  bcd55b9  mov rsi,rcx                                   
  bcd55bc  mov eax,[rdx]                                 
  bcd55be  mov [rcx],eax                                 
  bcd55c0  xorps xmm6,xmm6                               
  bcd55c3  movups [rcx+8],xmm6                           
  bcd55c7  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bcd55ce  mov rax,[rcx]                                 
  bcd55d1  mov rax,[rax+8]                               
  bcd55d5  mov edx,0x80                                  
  bcd55da  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcd55e0  mov rdi,rax                                   
  bcd55e3  test rax,rax                                  
  bcd55e6  je 0xBCD56E8                                  ; -> loc_bcd56e8

loc_bcd55ec:  ; from bcd56f2
  bcd55ec  lea rax,[rsi+8]                               
  bcd55f0  mov [rbp-0x28],rax                            
  bcd55f4  mov [rdi],rdi                                 
  bcd55f7  mov [rdi+8],rdi                               
  bcd55fb  mov [rsi+8],rdi                               
  bcd55ff  lea rax,[rsi+0x18]                            
  bcd5603  mov [rbp-0x20],rax                            
  bcd5607  movups [rsi+0x18],xmm6                        
  bcd560b  mov qword ptr [rsi+0x28],0                    
  bcd5613  mov qword ptr [rsi+0x30],7                    
  bcd561b  mov qword ptr [rsi+0x38],8                    
  bcd5623  mov dword ptr [rsi],0x3F800000                
  bcd5629  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bcd5630  mov rax,[rcx]                                 
  bcd5633  mov rax,[rax+8]                               
  bcd5637  mov edx,0x80                                  
  bcd563c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcd5642  nop                                           
  bcd5643  mov rbx,rax                                   
  bcd5646  test rax,rax                                  
  bcd5649  je 0xBCD56F7                                  ; -> loc_bcd56f7

loc_bcd564f:  ; from bcd5702
  bcd564f  mov rcx,[rsi+0x18]                            
  bcd5653  mov rdx,[rsi+0x28]                            
  bcd5657  sub rdx,rcx                                   
  bcd565a  je short 0xBCD5686                            ; -> loc_bcd5686
  bcd565c  cmp rdx,0x1000                                
  bcd5663  jb short 0xBCD5681                            ; -> loc_bcd5681
  bcd5665  mov rax,[rcx-8]                               
  bcd5669  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd566d  sub rcx,rax                                   
  bcd5670  cmp rcx,0x20                                  
  bcd5674  jae 0xBCD5707                                 ; -> loc_bcd5707
  bcd567a  add rdx,0x27                                  
  bcd567e  mov rcx,rax                                   

loc_bcd5681:  ; from bcd5663
  bcd5681  call 0xE935700                                ; -> sub_e935700

loc_bcd5686:  ; from bcd565a
  bcd5686  mov [rsi+0x18],rbx                            
  bcd568a  mov rax,rbx                                   
  bcd568d  sub rax,0xFFFFFFFFFFFFFF80                    
  bcd5691  mov [rsi+0x20],rax                            
  bcd5695  mov [rsi+0x28],rax                            
  bcd5699  mov [rbx],rdi                                 
  bcd569c  mov [rbx+8],rdi                               
  bcd56a0  mov [rbx+0x10],rdi                            
  bcd56a4  mov [rbx+0x18],rdi                            
  bcd56a8  mov [rbx+0x20],rdi                            
  bcd56ac  mov [rbx+0x28],rdi                            
  bcd56b0  mov [rbx+0x30],rdi                            
  bcd56b4  mov [rbx+0x38],rdi                            
  bcd56b8  mov [rbx+0x40],rdi                            
  bcd56bc  mov [rbx+0x48],rdi                            
  bcd56c0  mov [rbx+0x50],rdi                            
  bcd56c4  mov [rbx+0x58],rdi                            
  bcd56c8  mov [rbx+0x60],rdi                            
  bcd56cc  mov [rbx+0x68],rdi                            
  bcd56d0  mov [rbx+0x70],rdi                            
  bcd56d4  mov [rbx+0x78],rdi                            
  bcd56d8  mov rax,rsi                                   
  bcd56db  movaps xmm6,[rbp-0x10]                        
  bcd56df  add rsp,0x58                                  
  bcd56e3  pop rbx                                       
  bcd56e4  pop rdi                                       
  bcd56e5  pop rsi                                       
  bcd56e6  pop rbp                                       
  bcd56e7  ret                                           

loc_bcd56e8:  ; from bcd55e6
  bcd56e8  mov ecx,0x80                                  
  bcd56ed  call 0x9BC830                                 ; -> sub_9bc830
  bcd56f2  jmp 0xBCD55EC                                 ; -> loc_bcd55ec

loc_bcd56f7:  ; from bcd5649
  bcd56f7  mov ecx,0x80                                  
  bcd56fc  call 0x9BC830                                 ; -> sub_9bc830
  bcd5701  nop                                           
  bcd5702  jmp 0xBCD564F                                 ; -> loc_bcd564f

loc_bcd5707:  ; from bcd5674
  bcd5707  mov qword ptr [rsp+0x20],0                    
  bcd5710  xor ecx,ecx                                   
  bcd5712  xor edx,edx                                   
  bcd5714  xor r8d,r8d                                   
  bcd5717  xor r9d,r9d                                   
  bcd571a  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd5720  int3                                          
  bcd5721  nop [rax+rax]                                 
  bcd5730  mov [rsp+0x10],rdx                            
  bcd5735  push rbp                                      
  bcd5736  push rsi                                      
  bcd5737  push rdi                                      
  bcd5738  push rbx                                      
  bcd5739  sub rsp,0x38                                  
  bcd573d  lea rbp,[rdx+0x50]                            
  bcd5741  movaps [rsp+0x20],xmm6                        
  bcd5746  mov rcx,[rbp-0x20]                            
  bcd574a  call 0x75D00                                  ; -> sub_75d00
  bcd574f  mov rcx,[rbp-0x28]                            
  bcd5753  call 0xBCD40F0                                ; -> sub_bcd40f0
  bcd5758  movaps xmm6,[rsp+0x20]                        
  bcd575d  add rsp,0x38                                  
  bcd5761  pop rbx                                       
  bcd5762  pop rdi                                       
  bcd5763  pop rsi                                       
  bcd5764  pop rbp                                       
  bcd5765  ret                                           
  bcd5766  int3                                          
  bcd5767  int3                                          
  bcd5768  int3                                          
  bcd5769  int3                                          
  bcd576a  int3                                          
  bcd576b  int3                                          
  bcd576c  int3                                          
  bcd576d  int3                                          
  bcd576e  int3                                          
  bcd576f  int3                                          
  bcd5770  push rbp                                      
  bcd5771  push rsi                                      
  bcd5772  push rdi                                      
  bcd5773  push rbx                                      
  bcd5774  sub rsp,0x58                                  
  bcd5778  lea rbp,[rsp+0x50]                            
  bcd577d  movaps [rbp-0x10],xmm6                        
  bcd5781  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE   
  bcd5789  mov rsi,rcx                                   
  bcd578c  mov eax,[rdx]                                 
  bcd578e  mov [rcx],eax                                 
  bcd5790  xorps xmm6,xmm6                               
  bcd5793  movups [rcx+8],xmm6                           
  bcd5797  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bcd579e  mov rax,[rcx]                                 
  bcd57a1  mov rax,[rax+8]                               
  bcd57a5  mov edx,0x138                                 
  bcd57aa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcd57b0  mov rdi,rax                                   
  bcd57b3  test rax,rax                                  
  bcd57b6  je 0xBCD58B8                                  ; -> loc_bcd58b8

loc_bcd57bc:  ; from bcd58c2
  bcd57bc  lea rax,[rsi+8]                               
  bcd57c0  mov [rbp-0x28],rax                            
  bcd57c4  mov [rdi],rdi                                 
  bcd57c7  mov [rdi+8],rdi                               
  bcd57cb  mov [rsi+8],rdi                               
  bcd57cf  lea rax,[rsi+0x18]                            
  bcd57d3  mov [rbp-0x20],rax                            
  bcd57d7  movups [rsi+0x18],xmm6                        
  bcd57db  mov qword ptr [rsi+0x28],0                    
  bcd57e3  mov qword ptr [rsi+0x30],7                    
  bcd57eb  mov qword ptr [rsi+0x38],8                    
  bcd57f3  mov dword ptr [rsi],0x3F800000                
  bcd57f9  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bcd5800  mov rax,[rcx]                                 
  bcd5803  mov rax,[rax+8]                               
  bcd5807  mov edx,0x80                                  
  bcd580c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcd5812  nop                                           
  bcd5813  mov rbx,rax                                   
  bcd5816  test rax,rax                                  
  bcd5819  je 0xBCD58C7                                  ; -> loc_bcd58c7

loc_bcd581f:  ; from bcd58d2
  bcd581f  mov rcx,[rsi+0x18]                            
  bcd5823  mov rdx,[rsi+0x28]                            
  bcd5827  sub rdx,rcx                                   
  bcd582a  je short 0xBCD5856                            ; -> loc_bcd5856
  bcd582c  cmp rdx,0x1000                                
  bcd5833  jb short 0xBCD5851                            ; -> loc_bcd5851
  bcd5835  mov rax,[rcx-8]                               
  bcd5839  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd583d  sub rcx,rax                                   
  bcd5840  cmp rcx,0x20                                  
  bcd5844  jae 0xBCD58D7                                 ; -> loc_bcd58d7
  bcd584a  add rdx,0x27                                  
  bcd584e  mov rcx,rax                                   

loc_bcd5851:  ; from bcd5833
  bcd5851  call 0xE935700                                ; -> sub_e935700

loc_bcd5856:  ; from bcd582a
  bcd5856  mov [rsi+0x18],rbx                            
  bcd585a  mov rax,rbx                                   
  bcd585d  sub rax,0xFFFFFFFFFFFFFF80                    
  bcd5861  mov [rsi+0x20],rax                            
  bcd5865  mov [rsi+0x28],rax                            
  bcd5869  mov [rbx],rdi                                 
  bcd586c  mov [rbx+8],rdi                               
  bcd5870  mov [rbx+0x10],rdi                            
  bcd5874  mov [rbx+0x18],rdi                            
  bcd5878  mov [rbx+0x20],rdi                            
  bcd587c  mov [rbx+0x28],rdi                            
  bcd5880  mov [rbx+0x30],rdi                            
  bcd5884  mov [rbx+0x38],rdi                            
  bcd5888  mov [rbx+0x40],rdi                            
  bcd588c  mov [rbx+0x48],rdi                            
  bcd5890  mov [rbx+0x50],rdi                            
  bcd5894  mov [rbx+0x58],rdi                            
  bcd5898  mov [rbx+0x60],rdi                            
  bcd589c  mov [rbx+0x68],rdi                            
  bcd58a0  mov [rbx+0x70],rdi                            
  bcd58a4  mov [rbx+0x78],rdi                            
  bcd58a8  mov rax,rsi                                   
  bcd58ab  movaps xmm6,[rbp-0x10]                        
  bcd58af  add rsp,0x58                                  
  bcd58b3  pop rbx                                       
  bcd58b4  pop rdi                                       
  bcd58b5  pop rsi                                       
  bcd58b6  pop rbp                                       
  bcd58b7  ret                                           

loc_bcd58b8:  ; from bcd57b6
  bcd58b8  mov ecx,0x138                                 
  bcd58bd  call 0x9BC830                                 ; -> sub_9bc830
  bcd58c2  jmp 0xBCD57BC                                 ; -> loc_bcd57bc

loc_bcd58c7:  ; from bcd5819
  bcd58c7  mov ecx,0x80                                  
  bcd58cc  call 0x9BC830                                 ; -> sub_9bc830
  bcd58d1  nop                                           
  bcd58d2  jmp 0xBCD581F                                 ; -> loc_bcd581f

loc_bcd58d7:  ; from bcd5844
  bcd58d7  mov qword ptr [rsp+0x20],0                    
  bcd58e0  xor ecx,ecx                                   
  bcd58e2  xor edx,edx                                   
  bcd58e4  xor r8d,r8d                                   
  bcd58e7  xor r9d,r9d                                   
  bcd58ea  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd58f0  int3                                          
  bcd58f1  nop [rax+rax]                                 
  bcd5900  mov [rsp+0x10],rdx                            
  bcd5905  push rbp                                      
  bcd5906  push rsi                                      
  bcd5907  push rdi                                      
  bcd5908  push rbx                                      
  bcd5909  sub rsp,0x38                                  
  bcd590d  lea rbp,[rdx+0x50]                            
  bcd5911  movaps [rsp+0x20],xmm6                        
  bcd5916  mov rcx,[rbp-0x20]                            
  bcd591a  call 0x75D00                                  ; -> sub_75d00
  bcd591f  mov rcx,[rbp-0x28]                            
  bcd5923  call 0xBCD3E70                                ; -> sub_bcd3e70
  bcd5928  movaps xmm6,[rsp+0x20]                        
  bcd592d  add rsp,0x38                                  
  bcd5931  pop rbx                                       
  bcd5932  pop rdi                                       
  bcd5933  pop rsi                                       
  bcd5934  pop rbp                                       
  bcd5935  ret                                           
  bcd5936  int3                                          
  bcd5937  int3                                          
  bcd5938  int3                                          
  bcd5939  int3                                          
  bcd593a  int3                                          
  bcd593b  int3                                          
  bcd593c  int3                                          
  bcd593d  int3                                          
  bcd593e  int3                                          
  bcd593f  int3                                          
  bcd5940  add rcx,0x10                                  
  bcd5944  jmp 0xBCD2930                                 ; -> sub_bcd2930
  bcd5949  int3                                          
  bcd594a  int3                                          
  bcd594b  int3                                          
  bcd594c  int3                                          
  bcd594d  int3                                          
  bcd594e  int3                                          
  bcd594f  int3                                          
  bcd5950  push rsi                                      
  bcd5951  push rdi                                      
  bcd5952  sub rsp,0x28                                  
  bcd5956  cmp qword ptr [rcx+8],0                       
  bcd595b  je short 0xBCD597D                            ; -> loc_bcd597d
  bcd595d  mov rax,[rcx+0x18]                            
  bcd5961  mov qword ptr [rax+8],0                       
  bcd5969  mov rax,[rcx+0x10]                            
  bcd596d  mov qword ptr [rax],0                         
  bcd5974  mov rsi,[rcx+0x18]                            
  bcd5978  test rsi,rsi                                  
  bcd597b  jne short 0xBCD59BE                           ; -> loc_bcd59be

loc_bcd597d:  ; from bcd595b, bcd59bc
  bcd597d  add rsp,0x28                                  
  bcd5981  pop rdi                                       
  bcd5982  pop rsi                                       
  bcd5983  ret                                           
  bcd5984  nop [rax+rax]                                 

loc_bcd5990:  ; from bcd59da, bcd59f7
  bcd5990  call 0xE935700                                ; -> sub_e935700

loc_bcd5995:  ; from bcd59c9
  bcd5995  mov qword ptr [rsi+0x20],0                    
  bcd599d  mov qword ptr [rsi+0x28],0xF                  
  bcd59a5  mov byte ptr [rsi+0x10],0                     
  bcd59a9  mov edx,0x80                                  
  bcd59ae  mov rcx,rsi                                   
  bcd59b1  call 0xE935700                                ; -> sub_e935700
  bcd59b6  mov rsi,rdi                                   
  bcd59b9  test rdi,rdi                                  
  bcd59bc  je short 0xBCD597D                            ; -> loc_bcd597d

loc_bcd59be:  ; from bcd597b
  bcd59be  mov rdi,[rsi]                                 
  bcd59c1  mov rax,[rsi+0x28]                            
  bcd59c5  cmp rax,0x10                                  
  bcd59c9  jb short 0xBCD5995                            ; -> loc_bcd5995
  bcd59cb  mov rcx,[rsi+0x10]                            
  bcd59cf  lea rdx,[rax+1]                               
  bcd59d3  cmp rdx,0x1000                                
  bcd59da  jb short 0xBCD5990                            ; -> loc_bcd5990
  bcd59dc  mov r8,[rcx-8]                                
  bcd59e0  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd59e4  sub rcx,r8                                    
  bcd59e7  cmp rcx,0x20                                  
  bcd59eb  jae short 0xBCD59F9                           ; -> loc_bcd59f9
  bcd59ed  add rax,0x28                                  
  bcd59f1  mov rdx,rax                                   
  bcd59f4  mov rcx,r8                                    
  bcd59f7  jmp short 0xBCD5990                           ; -> loc_bcd5990

loc_bcd59f9:  ; from bcd59eb
  bcd59f9  mov qword ptr [rsp+0x20],0                    
  bcd5a02  xor ecx,ecx                                   
  bcd5a04  xor edx,edx                                   
  bcd5a06  xor r8d,r8d                                   
  bcd5a09  xor r9d,r9d                                   
  ... (--max 400)
```

## CALLERS
```
  0xbcc7f20 sub_bcc7f20 size 0x7421
  0xbccfb60 sub_bccfb60 size 0xd7
  0xbcd3420 sub_bcd3420 size 0xae
  0xbcd5450 sub_bcd5450 size 0x43
  -- 4 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0xe935700   sub_e935700       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_e935700.cpp;src\client\features\render\native\helpers\sub_e935700.h

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  56c85c0.md  size 0x95  callees~60  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\56c85c0.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

