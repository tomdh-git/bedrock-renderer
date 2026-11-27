# ctxpack build 0xbcc24f0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bcc24f0.md:b626c1d6de96bc75100dd2007b66fb7d50ae46a30e86efcd258e74d24b2aae33,liftsrc=sub_bcc24f0.cpp:921052267cd3cf3803412ccb040bf0c36568695efd0288dacfe8ab15ea20e6c4,liftsrc=sub_bcc24f0.h:4c79cd5197f4d88149855281d409539b8827b8955503581b3be9a725942bbb98,data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xbcc24f0
  size       : 0x1f1 (497 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 0 (direct), depth 1
  callers    : 18

## EXACT LISTING (0xbcc24f0..0xbcc26e1)
```
sub_bcc24f0  [0xbcc24f0..0xbcc44f0)  size 0x2000  19 xrefs in
  bcc24f0  push rsi                                      
  bcc24f1  mov rax,[rcx]                                 ; R a0+0x0
  bcc24f4  mov r9,[rax+0x10]                             ; R *(a0+0x0)+0x10
  bcc24f8  cmp byte ptr [r8+0x38],1                      ; R a2+0x38
  bcc24fd  jne 0xBCC259F                                 ; -> loc_bcc259f
  bcc2503  movd xmm0,[rdx+4]                             ; R a1+0x4
  bcc2508  pxor xmm1,xmm1                                
  bcc250c  punpcklwd xmm0,xmm1                           
  bcc2510  cvtdq2ps xmm2,xmm0                            
  bcc2513  movsd xmm0,[r8+0x44]                          ; R a2+0x44
  bcc2519  mulps xmm0,xmm2                               
  bcc251c  cvttps2dq xmm0,xmm0                           
  bcc2520  pshuflw xmm3,xmm0,0xA0                        
  bcc2525  pshufd xmm3,xmm3,0x50                         
  bcc252a  pcmpeqw xmm3,xmm1                             
  bcc252e  movmskpd eax,xmm3                             
  bcc2532  xor eax,3                                     
  bcc2535  cmp eax,3                                     
  bcc2538  jne 0xBCC262B                                 ; -> loc_bcc262b
  bcc253e  pshuflw xmm1,xmm0,0xE8                        
  bcc2543  movd xmm0,[rdx]                               ; R a1+0x0
  bcc2547  movsd xmm3,[r8+0x3C]                          ; R a2+0x3C
  bcc254d  mov r10,[r9]                                  ; R *(*(a0+0x0)+0x10)+0x0
  bcc2550  mov eax,[r10+0xDC57D0]                        ; R *(*(*(a0+0x0)+0x10)+0x0)+0xDC57D0
  bcc2557  mov r11d,0xFFFF                               
  bcc255d  nop [rax]                                     ; R *(*(*(*(a0+0x0)+0x10)+0x0)+0xDC57D0)+0x0

loc_bcc2560:  ; from bcc258b
  bcc2560  mov edx,eax                                   
  bcc2562  lea esi,[rdx+1]                               ; R *(*(*(*(a0+0x0)+0x10)+0x0)+0xDC57D0)+0x1
  bcc2565  cmp esi,0xFFFF                                
  bcc256b  cmovae esi,r11d                               
  bcc256f  cmp eax,0xFFFF                                
  bcc2574  cmovae esi,r11d                               
  bcc2578  lock cmpxchg [r10+0xDC57D0],esi               ; R *(*(*(a0+0x0)+0x10)+0x0)+0xDC57D0
  bcc2581  cmp edx,0xFFFF                                
  bcc2587  je short 0xBCC258D                            ; -> loc_bcc258d
  bcc2589  cmp edx,eax                                   
  bcc258b  jne short 0xBCC2560                           ; -> loc_bcc2560

loc_bcc258d:  ; from bcc2587
  bcc258d  mulps xmm3,xmm2                               
  bcc2590  cvttps2dq xmm2,xmm3                           
  bcc2594  pshuflw xmm2,xmm2,0xE8                        
  bcc2599  paddw xmm0,xmm2                               
  bcc259d  jmp short 0xBCC260D                           ; -> loc_bcc260d

loc_bcc259f:  ; from bcc24fd
  bcc259f  movzx r11d,word ptr [rdx+4]                   
  bcc25a4  test r11w,r11w                                
  bcc25a8  je 0xBCC262B                                  ; -> loc_bcc262b
  bcc25ae  movzx esi,word ptr [rdx+6]                    
  bcc25b2  test si,si                                    
  bcc25b5  je short 0xBCC262B                            ; -> loc_bcc262b
  bcc25b7  movd xmm0,[rdx]                               
  bcc25bb  mov r10,[r9]                                  
  bcc25be  mov eax,[r10+0xDC57D0]                        
  bcc25c5  movd xmm1,r11d                                
  bcc25ca  pinsrw xmm1,esi,1                             
  bcc25cf  mov r11d,0xFFFF                               
  bcc25d5  nop [rax+rax]                                 

loc_bcc25e0:  ; from bcc260b
  bcc25e0  mov edx,eax                                   
  bcc25e2  lea esi,[rdx+1]                               
  bcc25e5  cmp esi,0xFFFF                                
  bcc25eb  cmovae esi,r11d                               
  bcc25ef  cmp eax,0xFFFF                                
  bcc25f4  cmovae esi,r11d                               
  bcc25f8  lock cmpxchg [r10+0xDC57D0],esi               
  bcc2601  cmp edx,0xFFFF                                
  bcc2607  je short 0xBCC260D                            ; -> loc_bcc260d
  bcc2609  cmp edx,eax                                   
  bcc260b  jne short 0xBCC25E0                           ; -> loc_bcc25e0

loc_bcc260d:  ; from bcc259d, bcc2607
  bcc260d  mov eax,edx                                   
  bcc260f  movd [r10+rax*8+0xD457D0],xmm0                
  bcc2619  movd [r10+rax*8+0xD457D4],xmm1                
  bcc2623  mov [r9+0xA0],dx                              

loc_bcc262b:  ; from bcc2538, bcc25a8, bcc25b5
  bcc262b  mov rax,[rcx]                                 
  bcc262e  mov rax,[rax+0x10]                            
  bcc2632  mov edx,[r8+0x4C]                             
  bcc2636  movsd xmm0,[r8+0x50]                          
  bcc263c  mov [rax+0xA8],edx                            
  bcc2642  movsd [rax+0xAC],xmm0                         
  bcc264a  mov rax,[rcx]                                 
  bcc264d  mov rax,[rax+0x10]                            
  bcc2651  movdqu xmm0,[r8]                              
  bcc2656  movdqu xmm1,[r8+0x10]                         
  bcc265c  por xmm1,xmm0                                 
  bcc2660  pshufd xmm0,xmm1,0xEE                         
  bcc2665  por xmm0,xmm1                                 
  bcc2669  movq rdx,xmm0                                 
  bcc266e  or rdx,[r8+0x20]                              
  bcc2672  or rdx,[r8+0x28]                              
  bcc2676  mov r9d,edx                                   
  bcc2679  shr r9d,0xC                                   
  bcc267d  and r9d,0xF                                   
  bcc2681  mov r10d,edx                                  
  bcc2684  and r10d,0xFF000                              
  bcc268b  lea r11,[0xF8479DA]                           ; [data_f8479da]
  bcc2692  add r11,r9                                    
  bcc2695  cmp r10,1                                     
  bcc2699  sbb r11,0xFFFFFFFFFFFFFFFF                    
  bcc269d  movzx r9d,byte ptr [r11]                      
  bcc26a1  mov r10,0xFF0000000000                        
  bcc26ab  and r10,rdx                                   
  bcc26ae  cmp r10,1                                     
  bcc26b2  sbb r9b,0xFF                                  
  bcc26b6  mov [rax+0x14],r9b                            
  bcc26ba  mov [rax+0x60],rdx                            
  bcc26be  mov dword ptr [rax+0x70],0                    
  bcc26c5  mov rax,[rcx]                                 
  bcc26c8  mov rax,[rax+0x10]                            
  bcc26cc  mov ecx,[r8+0x30]                             
  bcc26d0  mov edx,[r8+0x34]                             
  bcc26d4  shl rcx,0x20                                  
  bcc26d8  or rcx,rdx                                    
  bcc26db  mov [rax+0x68],rcx                            
  bcc26df  pop rsi                                       
  bcc26e0  ret                                           
  bcc26e1  int3                                          
  bcc26e2  int3                                          
  bcc26e3  int3                                          
  bcc26e4  int3                                          
  bcc26e5  int3                                          
  bcc26e6  int3                                          
  bcc26e7  int3                                          
  bcc26e8  int3                                          
  bcc26e9  int3                                          
  bcc26ea  int3                                          
  bcc26eb  int3                                          
  bcc26ec  int3                                          
  bcc26ed  int3                                          
  bcc26ee  int3                                          
  bcc26ef  int3                                          
  bcc26f0  push rbp                                      
  bcc26f1  push r15                                      
  bcc26f3  push r14                                      
  bcc26f5  push r12                                      
  bcc26f7  push rsi                                      
  bcc26f8  push rdi                                      
  bcc26f9  push rbx                                      
  bcc26fa  sub rsp,0xC0                                  
  bcc2701  lea rbp,[rsp+0x80]                            
  bcc2709  mov qword ptr [rbp+0x38],0xFFFFFFFFFFFFFFFE   
  bcc2711  mov rbx,[rdx+8]                               
  bcc2715  mov r12,[rdx+0x10]                            
  bcc2719  mov sil,1                                     
  bcc271c  cmp rbx,r12                                   
  bcc271f  je 0xBCC27AD                                  ; -> loc_bcc27ad
  bcc2725  mov rdi,r8                                    
  bcc2728  mov rax,[rcx]                                 
  bcc272b  mov r14,[rax+0x20]                            
  bcc272f  lea r15,[rbp-0x60]                            
  bcc2733  jmp short 0xBCC2749                           ; -> loc_bcc2749
  bcc2735  nop [rax+rax]                                 

loc_bcc2740:  ; from bcc2781, bcc2794
  bcc2740  add rbx,0x28                                  
  bcc2744  cmp rbx,r12                                   
  bcc2747  je short 0xBCC27AD                            ; -> loc_bcc27ad

loc_bcc2749:  ; from bcc2733
  bcc2749  mov rcx,r15                                   
  bcc274c  mov rdx,r14                                   
  bcc274f  mov r8,rbx                                    
  bcc2752  call 0xBCC2820                                ; -> sub_bcc2820
  bcc2757  cmp byte ptr [rbp+0x30],1                     
  bcc275b  jne short 0xBCC27AB                           ; -> loc_bcc27ab
  bcc275d  mov r8,[rbp-0x58]                             
  bcc2761  mov rcx,[r14+0x20]                            
  bcc2765  mov rdx,rdi                                   
  bcc2768  call 0xC2AC940                                ; -> sub_c2ac940
  bcc276d  nop                                           
  bcc276e  mov rcx,[rbp+0x20]                            
  bcc2772  test rcx,rcx                                  
  bcc2775  setne dl                                      
  bcc2778  and dl,[rbp+0x28]                             
  bcc277b  test al,al                                    
  bcc277d  je short 0xBCC2796                            ; -> loc_bcc2796
  bcc277f  test dl,dl                                    
  bcc2781  je short 0xBCC2740                            ; -> loc_bcc2740
  bcc2783  mov rax,[rcx]                                 
  bcc2786  mov rax,[rax]                                 
  bcc2789  mov edx,1                                     
  bcc278e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcc2794  jmp short 0xBCC2740                           ; -> loc_bcc2740

loc_bcc2796:  ; from bcc277d
  bcc2796  test dl,dl                                    
  bcc2798  je short 0xBCC27AB                            ; -> loc_bcc27ab
  bcc279a  mov rax,[rcx]                                 
  bcc279d  mov rax,[rax]                                 
  bcc27a0  mov edx,1                                     
  bcc27a5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bcc27ab:  ; from bcc275b, bcc2798
  bcc27ab  xor esi,esi                                   

loc_bcc27ad:  ; from bcc271f, bcc2747
  bcc27ad  mov eax,esi                                   
  bcc27af  add rsp,0xC0                                  
  bcc27b6  pop rbx                                       
  bcc27b7  pop rdi                                       
  bcc27b8  pop rsi                                       
  bcc27b9  pop r12                                       
  bcc27bb  pop r14                                       
  bcc27bd  pop r15                                       
  bcc27bf  pop rbp                                       
  bcc27c0  ret                                           
  bcc27c1  nop [rax+rax]                                 
  bcc27d0  mov [rsp+0x10],rdx                            
  bcc27d5  push rbp                                      
  bcc27d6  push r15                                      
  bcc27d8  push r14                                      
  bcc27da  push r12                                      
  bcc27dc  push rsi                                      
  bcc27dd  push rdi                                      
  bcc27de  push rbx                                      
  bcc27df  sub rsp,0x20                                  
  bcc27e3  lea rbp,[rdx+0x80]                            
  bcc27ea  mov rcx,[rbp+0x20]                            
  bcc27ee  test rcx,rcx                                  
  bcc27f1  setne al                                      
  bcc27f4  and al,[rbp+0x28]                             
  bcc27f7  cmp al,1                                      
  bcc27f9  jne short 0xBCC280D                           ; -> loc_bcc280d
  bcc27fb  mov rax,[rcx]                                 
  bcc27fe  mov rax,[rax]                                 
  bcc2801  mov edx,1                                     
  bcc2806  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcc280c  nop                                           

loc_bcc280d:  ; from bcc27f9
  bcc280d  add rsp,0x20                                  
  bcc2811  pop rbx                                       
  bcc2812  pop rdi                                       
  bcc2813  pop rsi                                       
  bcc2814  pop r12                                       
  bcc2816  pop r14                                       
  bcc2818  pop r15                                       
  bcc281a  pop rbp                                       
  bcc281b  ret                                           
  bcc281c  int3                                          
  bcc281d  int3                                          
  bcc281e  int3                                          
  bcc281f  int3                                          
  bcc2820  push r15                                      
  bcc2822  push r14                                      
  bcc2824  push r12                                      
  bcc2826  push rsi                                      
  bcc2827  push rdi                                      
  bcc2828  push rbp                                      
  bcc2829  push rbx                                      
  bcc282a  sub rsp,0xA0                                  
  bcc2831  movzx eax,byte ptr [r8+0x18]                  
  bcc2836  cmp eax,1                                     
  bcc2839  jg short 0xBCC2873                            ; -> loc_bcc2873
  bcc283b  test eax,eax                                  
  bcc283d  jne short 0xBCC28AD                           ; -> loc_bcc28ad
  bcc283f  mov rax,[r8]                                  
  bcc2842  test rax,rax                                  
  bcc2845  je 0xBCC2AF3                                  ; -> loc_bcc2af3
  bcc284b  lea rdx,[rax+0x10]                            
  bcc284f  movzx r8d,word ptr [rax+0xC]                  
  bcc2854  mov [rcx],r8w                                 
  bcc2858  mov [rcx+8],rdx                               
  bcc285c  mov [rcx+0x10],rax                            
  bcc2860  mov byte ptr [rcx+0x88],0                     
  bcc2867  mov byte ptr [rcx+0x90],1                     
  bcc286e  jmp 0xBCC2AE1                                 ; -> loc_bcc2ae1

loc_bcc2873:  ; from bcc2839
  bcc2873  cmp eax,2                                     
  bcc2876  jne 0xBCC2AF8                                 ; -> loc_bcc2af8
  bcc287c  mov rax,[r8]                                  
  bcc287f  test rax,rax                                  
  bcc2882  je short 0xBCC28F2                            ; -> loc_bcc28f2
  bcc2884  mov rax,[rax+0x18]                            
  bcc2888  test rax,rax                                  
  bcc288b  je short 0xBCC28F2                            ; -> loc_bcc28f2
  bcc288d  lea rdx,[rax+0x10]                            
  bcc2891  movzx r8d,word ptr [rax+0xC]                  
  bcc2896  mov [rcx],r8w                                 
  bcc289a  mov [rcx+8],rdx                               
  bcc289e  mov [rcx+0x10],rax                            
  bcc28a2  mov byte ptr [rcx+0x88],0                     
  bcc28a9  mov al,1                                      
  bcc28ab  jmp short 0xBCC28F4                           ; -> loc_bcc28f4

loc_bcc28ad:  ; from bcc283d
  bcc28ad  mov rdi,rcx                                   
  bcc28b0  mov rax,[r8]                                  
  bcc28b3  mov rbx,r8                                    
  bcc28b6  movzx r9d,byte ptr [r8+8]                     
  bcc28bb  mov rsi,rdx                                   
  bcc28be  mov rcx,[rdx+0x28]                            
  bcc28c2  mov byte ptr [rsp+0x20],1                     
  bcc28c7  lea rdx,[rsp+0x28]                            
  bcc28cc  mov r8,rax                                    
  bcc28cf  call 0xE327B30                                ; -> sub_e327b30
  bcc28d4  cmp byte ptr [rsp+0x98],0                     
  bcc28dc  je short 0xBCC28FF                            ; -> loc_bcc28ff
  bcc28de  mov ebp,[rbx+0x10]                            
  bcc28e1  test ebp,0x10000                              
  bcc28e7  jne short 0xBCC290B                           ; -> loc_bcc290b
  bcc28e9  mov al,1                                      
  bcc28eb  xor ecx,ecx                                   
  bcc28ed  jmp 0xBCC2AB8                                 ; -> loc_bcc2ab8

loc_bcc28f2:  ; from bcc2882, bcc288b
  bcc28f2  xor eax,eax                                   

loc_bcc28f4:  ; from bcc28ab
  bcc28f4  mov [rcx+0x90],al                             
  bcc28fa  jmp 0xBCC2AE1                                 ; -> loc_bcc2ae1

loc_bcc28ff:  ; from bcc28dc
  bcc28ff  mov byte ptr [rdi+0x90],0                     
  bcc2906  jmp 0xBCC2AE1                                 ; -> loc_bcc2ae1

loc_bcc290b:  ; from bcc28e7
  bcc290b  mov r15,[rsi+0x20]                            
  bcc290f  movzx r12d,bp                                 
  bcc2913  shr r12d,8                                    
  bcc2917  lea rsi,[r15+0x88]                            
  bcc291e  mov rcx,rsi                                   
  bcc2921  call 0xE943178                                ; -> sub_e943178
  bcc2926  movzx eax,bpl                                 
  bcc292a  mov rcx,0xBF29CE484222325                     
  bcc2934  xor rcx,rax                                   
  bcc2937  mov rax,0x100000001B3                         
  bcc2941  imul rcx,rax                                  
  bcc2945  xor r12,rcx                                   
  bcc2948  imul r12,rax                                  
  bcc294c  and r12,[r15+0x78]                            
  bcc2950  mov r14,[r15+0x50]                            
  bcc2954  mov rax,[r15+0x60]                            
  bcc2958  shl r12,4                                     
  bcc295c  mov r15,[rax+r12+8]                           
  bcc2961  cmp r15,r14                                   
  bcc2964  je short 0xBCC2992                            ; -> loc_bcc2992
  bcc2966  cmp [r15+0x10],bp                             
  bcc296b  je short 0xBCC2995                            ; -> loc_bcc2995
  bcc296d  mov rax,[rax+r12]                             
  bcc2971  nop [rax+rax]                                 

loc_bcc2980:  ; from bcc298e
  bcc2980  cmp r15,rax                                   
  bcc2983  je short 0xBCC2992                            ; -> loc_bcc2992
  bcc2985  mov r15,[r15+8]                               
  bcc2989  cmp [r15+0x10],bp                             
  bcc298e  jne short 0xBCC2980                           ; -> loc_bcc2980
  bcc2990  jmp short 0xBCC2995                           ; -> loc_bcc2995

loc_bcc2992:  ; from bcc2964, bcc2983
  bcc2992  xor r15d,r15d                                 

loc_bcc2995:  ; from bcc296b, bcc2990
  bcc2995  mov rcx,rsi                                   
  bcc2998  call 0xE94319C                                ; -> sub_e94319c
  bcc299d  xor ecx,ecx                                   
  bcc299f  movzx eax,byte ptr [rsp+0x98]                 
  bcc29a7  test r15,r15                                  
  bcc29aa  je 0xBCC2AB8                                  ; -> loc_bcc2ab8
  bcc29b0  cmp r15,r14                                   
  bcc29b3  je 0xBCC2AB8                                  ; -> loc_bcc2ab8
  bcc29b9  mov rcx,[r15+0x18]                            
  bcc29bd  add rcx,4                                     
  bcc29c1  mov r8d,[rbx+0x10]                            
  bcc29c5  mov r9d,r8d                                   
  bcc29c8  and r9d,0x10000                               
  bcc29cf  xor edx,edx                                   
  bcc29d1  cmp r9d,1                                     
  bcc29d5  sbb edx,edx                                   
  bcc29d7  or edx,r8d                                    
  bcc29da  test al,al                                    
  bcc29dc  je 0xBCC2AA0                                  ; -> loc_bcc2aa0
  bcc29e2  movsd xmm0,[rsp+0x28]                         
  bcc29e8  movzx ebp,byte ptr [rsp+0x2A]                 
  bcc29ed  mov r10d,[rsp+0x30]                           
  bcc29f2  movzx r11d,word ptr [rsp+0x34]                
  bcc29f8  mov esi,[rsp+0x38]                            
  bcc29fc  movzx ebx,word ptr [rsp+0x3C]                 
  bcc2a01  lea r9,[rsp+0x3E]                             
  bcc2a06  mov r8,[rsp+0x90]                             
  bcc2a0e  mov qword ptr [rsp+0x90],0                    
  bcc2a1a  test ebp,ebp                                  
  bcc2a1c  je short 0xBCC2A23                            ; -> loc_bcc2a23
  bcc2a1e  mov byte ptr [rsp+0x2A],0                     

loc_bcc2a23:  ; from bcc2a1c
  bcc2a23  mov word ptr [rsp+0x28],0xFFFF                
  bcc2a2a  mov word ptr [rsp+0x34],0                     
  bcc2a31  mov word ptr [rsp+0x3C],0                     
  bcc2a38  mov qword ptr [rsp+0x2C],0                    
  bcc2a41  mov [rdi],dx                                  
  bcc2a44  mov [rdi+8],rcx                               
  bcc2a48  mov qword ptr [rdi+0x10],0                    
  bcc2a50  movlps [rdi+0x18],xmm0                        
  bcc2a54  mov [rdi+0x20],r10d                           
  bcc2a58  mov [rdi+0x24],r11w                           
  bcc2a5d  mov [rdi+0x28],esi                            
  bcc2a60  mov [rdi+0x2C],bx                             
  bcc2a64  movups xmm0,[r9]                              
  bcc2a68  movups xmm1,[r9+0x10]                         
  bcc2a6d  movups xmm2,[r9+0x20]                         
  bcc2a72  movups xmm3,[r9+0x30]                         
  bcc2a77  movups [rdi+0x2E],xmm0                        
  bcc2a7b  movups [rdi+0x3E],xmm1                        
  bcc2a7f  movups [rdi+0x4E],xmm2                        
  bcc2a83  movups [rdi+0x5E],xmm3                        
  bcc2a87  movups xmm0,[r9+0x3E]                         
  bcc2a8c  movups [rdi+0x6C],xmm0                        
  bcc2a90  mov [rdi+0x80],r8                             
  bcc2a97  mov byte ptr [rdi+0x88],1                     
  bcc2a9e  jmp short 0xBCC2AB6                           ; -> loc_bcc2ab6

loc_bcc2aa0:  ; from bcc29dc
  bcc2aa0  mov [rdi],dx                                  
  bcc2aa3  mov [rdi+8],rcx                               
  bcc2aa7  mov qword ptr [rdi+0x10],0                    
  bcc2aaf  mov byte ptr [rdi+0x88],0                     

loc_bcc2ab6:  ; from bcc2a9e
  bcc2ab6  mov cl,1                                      

loc_bcc2ab8:  ; from bcc28ed, bcc29aa, bcc29b3
  bcc2ab8  mov [rdi+0x90],cl                             
  bcc2abe  test al,al                                    
  bcc2ac0  je short 0xBCC2AE1                            ; -> loc_bcc2ae1
  bcc2ac2  mov rcx,[rsp+0x90]                            
  bcc2aca  test rcx,rcx                                  
  bcc2acd  je short 0xBCC2AE1                            ; -> loc_bcc2ae1
  bcc2acf  mov rax,[rcx]                                 
  bcc2ad2  mov rax,[rax]                                 
  bcc2ad5  mov edx,1                                     
  bcc2ada  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcc2ae0  nop                                           

loc_bcc2ae1:  ; from bcc286e, bcc28fa, bcc2906, bcc2ac0, bcc2acd
  bcc2ae1  add rsp,0xA0                                  
  bcc2ae8  pop rbx                                       
  bcc2ae9  pop rbp                                       
  bcc2aea  pop rdi                                       
  bcc2aeb  pop rsi                                       
  bcc2aec  pop r12                                       
  bcc2aee  pop r14                                       
  ... (--max 400)
```

## CALLERS
```
  0x568d750 sub_568d750 size 0x339
  0x56ae230 sub_56ae230 size 0x545
  0x56ca9c0 sub_56ca9c0 size 0x648
  0x56d16a0 sub_56d16a0 size 0x6b3
  0xbc04dc0 sub_bc04dc0 size 0x5d3
  0xbc0f130 sub_bc0f130 size 0x648
  0xbc2c590 sub_bc2c590 size 0x558
  0xbc2cd20 sub_bc2cd20 size 0x5f2
  0xbc2d550 sub_bc2d550 size 0x5e4
  0xbc2dd20 sub_bc2dd20 size 0x5db
  0xbc2eb50 sub_bc2eb50 size 0x54c
  0xbc2f4a0 sub_bc2f4a0 size 0x85b
  0xbc36140 sub_bc36140 size 0x5aa
  0xbc38c20 sub_bc38c20 size 0xda8
  0xbc82400 sub_bc82400 size 0x5df
  0xbc8cfd0 sub_bc8cfd0 size 0x1775
  0xbcb7e70 sub_bcb7e70 size 0x447
  0xe7ebfc0 sub_e7ebfc0 size 0x1ce
  -- 18 calling function(s)
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
  e81d850.md  size 0x1cd  callees~72  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\e81d850.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

