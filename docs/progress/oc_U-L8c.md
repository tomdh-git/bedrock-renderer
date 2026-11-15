# Unit U-L8c — Image decoder sub_777ed0 direct callers (0x7647c0, 0x764950) and their callers (0x19944b0, 0x1994f90, 0x167d050)

## NEXT
Run rdis dis 0x7647c0 120, then 0x764950 120, then 0x19944b0 120, then 0x1994f90 120; analyze args/returns/calls; then xref.py callers on the image-returning function (2 levels), identify resource-pack texture loader via strings.

## Rules (from OPENCODE_BRIEF.md)
- Static analysis only; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe
- Every claim tagged [V] (saw in disasm, cite RVA), [I] (inferred), [?] (unknown)
- Append findings after each step; never guess as fact
- Do not edit any other file; create only docs/progress/oc_U-L8c.md

## Context from U-L8b (prior unit, read-only)
- sub_777ed0 = image decoder entry (PNG magic 0x89 check at 777f55; "bad png sig" error at 0x7784be; multi-format incl. BMP "BM"/"M" checks at 778567/7785f0). [V via U-L8b]
- Direct callers of sub_777ed0: 0x7647c0 (+0x18e), 0x764950 (+0x4f9) [V via U-L8b xref callers]
- Callers of those: 0x7647c0 ← 0x167d050 (+0x11d), 0x19944b0 (+0x906), 0x1994f90 (+0xac5); 0x764950 ← 0x19944b0 (+0x906), 0x1994f90 (+0xac5) [V via U-L8b]
- Decoder context struct (r15 = rcx of sub_777ed0): [r15+0x0]=width, [r15+0x4]=height (abs()'d), [r15+0x8]=format/component count, [r15+0xB8]=bytes consumed, [r15+0xC0]=stream cursor, [r15+0xC8]=stream end [V via U-L8b]
- rdis command: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis <rva> 120`

## Step (1): disassemble 0x7647c0 (120 instructions, 3 phases of 40) — DONE

`rdis dis 0x7647c0 120` → sub_7647c0 [0x7647c0..0x7667c0) nominal size 0x2000, but real body ends at `ret` 0x76493f; int3 padding then sub_764950 begins at 0x764950. 3 xrefs in [V via rdis header].

### Phase 1: 0x7647c0..0x764870 (instr 1-40) — prologue, arg shuffle, call decoder
```
7647c0  push r14                                      
7647c2  push rsi                                      
7647c3  push rdi                                      
7647c4  push rbp                                      
7647c5  push rbx                                      
7647c6  sub rsp,0x50                                  
7647ca  mov r14,r9                                    
7647cd  mov rbx,r8                                    
7647d0  mov rdi,rdx                                   
7647d3  mov ebp,[rsp+0xA0]                            
7647da  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
7647e1  xor rax,rsp                                   
7647e4  mov [rsp+0x48],rax                            
7647e9  lea rax,[rsp+0x3C]                            
7647ee mov [rsp+0x28],rax                            
7647f3 mov [rsp+0x20],ebp                            
7647f7 call 0x777ED0                                 ; -> sub_777ed0
7647fc test rax,rax                                  
7647ff je short 0x764840                             ; -> loc_764840
764801 mov rsi,rax                                   
764804 cmp dword ptr [rsp+0x3C],8                    
764809 je 0x76491E                                   ; -> loc_76491e
76480f test ebp,ebp                                  
764811 jne short 0x764816                            ; -> loc_764816
764813 mov ebp,[r14]                                 ; R a3+0x0
loc_764816:  ; from 764811
764816 imul ebp,[rbx]                                ; R a2+0x0
764819 imul ebp,[rdi]                                ; R a1+0x0
76481c movsxd rcx,ebp                                
76481f call qword ptr [0xF9A6FA0]                    ; [data_f9a6fa0] allocator
764825 test rax,rax                                  
764828 je short 0x764847                             ; -> loc_764847
76482a test ebp,ebp                                  
76482c jle 0x764912                                  ; -> loc_764912
764832 mov ecx,ebp                                   
764834 cmp ebp,4                                     
764837 jae short 0x76486D                            ; -> loc_76486d
764839 xor edx,edx                                   
76483b jmp 0x764900                                  ; -> loc_764900
loc_76486d:  ; from 764837
76486d cmp ebp,0x10                                  
764870 jae short 0x764876                            ; -> loc_764876
```
// [V] x64 args: rcx=a0 (decoder context, passed straight to sub_777ed0), rdx=a1→rdi ([a1+0] = dim1), r8=a2→rbx ([a2+0] = dim2), r9=a3→r14 ([a3+0] = comp count if a4==0), [rsp+0xA0]=a4 (requested comp count; 0 means use *a3) [V via 7647ca/7647cd/7647d0/7647d3/764813]
// [V] stack cookie via data_1230a0c0 at 7647da/764929; out-param pointer &[rsp+0x3C] passed at [rsp+0x28], a4 at [rsp+0x20] as 5th/6th stack args to sub_777ed0 [V via 7647e9-7647f3]
// [V] call sub_777ed0 at 7647f7; if rax==0 → return 0 (7647ff je 0x764840 → 764840 xor eax,eax)
// [V] rsi = decoder result (image data pointer); dword [rsp+0x3C] (decoder out-param: format/bpp) compared to 8; if ==8 skip conversion, return decoder pointer as-is (764809 je 0x76491E → 76491e mov rax,rsi)
// [I] ebp = count = (a4 != 0 ? a4 : *a3) * *a2 * *a1 → pixel component count (w*h*comp) [V via 76480f-764819 imul chain]
// [V] heap alloc via [data_f9a6fa0] (size rcx=count) at 76481f; on NULL → data_f59fac1 "outofmem" stored at [tls data_128767C8 + 0xC98] (764847-764861); if count<=0 jump to free path (76482c jle 0x764912)
// [I] data_f9a6fa0 is same-heap-allocator family as data_f99ffa0 (=sub_eea6040 per U-L8b); not re-verified here [I]

### Phase 2: 0x764872..0x764910 (instr 41-80) — 16-bit→8-bit conversion bulk loops
```
loc_76486d cont.:
764872 xor edx,edx                                   
764874 jmp short 0x7648C3                            ; -> loc_7648c3
loc_764876:  ; from 764870
764876 mov edx,ecx                                   
764878 and edx,0x7FFFFFF0                            
76487e xor r8d,r8d                                   
764881 nop [rax+rax]                                 
loc_764890:  ; from 7648b8
764890 movdqu xmm0,[rsi+r8*2]                        
764896 movdqu xmm1,[rsi+r8*2+0x10]                   
76489d psrlw xmm0,8                                  
7648a2 psrlw xmm1,8                                  
7648a7 packuswb xmm0,xmm1                            
7648ab movdqu [rax+r8],xmm0                          
7648b1 add r8,0x10                                   
7648b5 cmp rdx,r8                                    
7648b8 jne short 0x764890                            ; -> loc_764890
7648ba cmp edx,ecx                                   
7648bc je short 0x764912                             ; -> loc_764912
7648be test cl,0xC                                   
7648c1 je short 0x764900                             ; -> loc_764900
loc_7648c3:  ; from 764874
7648c3 mov r8,rdx                                    
7648c6 mov edx,ecx                                   
7648c8 and edx,0x7FFFFFFC                            
7648ce xchg ax,ax                                    
loc_7648d0:  ; from 7648ec
7648d0 movq xmm0,[rsi+r8*2]                          
7648d6 psrlw xmm0,8                                  
7648db packuswb xmm0,xmm0                            
7648df movd [rax+r8],xmm0                            
7648e5 add r8,4                                      
7648e9 cmp rdx,r8                                    
7648ec jne short 0x7648D0                            ; -> loc_7648d0
7648ee cmp edx,ecx                                   
7648f0 je short 0x764912                             ; -> loc_764912
7648f2 nop [rax+rax]                                 
loc_764900:  ; from 76483b, 7648c1, 764910
764900 movzx r8d,byte ptr [rsi+rdx*2+1]              
764906 mov [rax+rdx],r8b                             
76490a inc rdx                                       
76490d cmp rcx,rdx                                   
764910 jne short 0x764900                            ; -> loc_764900
```
// [V] 16-bit→8-bit down-conversion: source read stride 2 bytes ([rsi+r8*2], [rsi+r8*2+1]), dest 1 byte; takes high byte of each 16-bit element (psrlw 8 + packuswb, or movzx byte+1 scalar) [V via 764890-764906]
// [V] 3 loops: 16-byte SIMD (edx = count & 0x7FFFFFF0), 4-byte SIMD (count & 0x7FFFFFFC), scalar tail [V via 764878/7648c8]
// [V] ecx = total count loop bound; r8 = index; rax = dest buffer (alloc), rsi = source (decoder 16-bit data)

// Phase 3: 0x76490d..0x764974 (instr 81-116) — free original, return new buffer, cookie check, sub_764950 prologue
```
loc_764912:  ; from 76482c, 7648bc, 7648f0
764912 mov rcx,rsi                                   
764915 mov rsi,rax                                   
764918 call qword ptr [0xF9A6F98]                    ; [data_f9a6f98] freer
loc_76491e:  ; from 764809
76491e mov rax,rsi                                   
loc_764921:  ; from 764842, 764868
764921 mov rcx,[rsp+0x48]                            
764926 xor rcx,rsp                                   
764929 mov rdx,[0x1230A0C0]                          ; [data_1230a0c0]
764930 cmp rdx,rcx                                   
764933 jne short 0x764940                            ; -> loc_764940
764935 add rsp,0x50                                  
764939 pop rbx                                       
76493a pop rbp                                       
76493b pop rdi                                       
76493c pop rsi                                       
76493d pop r14                                       
76493f ret                                           
loc_764940:  ; from 764933
764940 mov rcx,[rsp+0x48]                            
764945 xor rcx,rsp                                   
764948 call 0xE951550                                ; -> sub_e951550 (stack-check fail)
76494d int3                                          
76494e int3                                          
76494f int3                                          
764950 push r15                                       ; start of sub_764950 (next function)
764952 push r14                                      
764954 push r13                                      
764956 push r12                                      
764958 push rsi                                      
764959 push rdi                                      
76495a push rbp                                      
76495b push rbx                                      
76495c sub rsp,0xA8                                  
764963 movaps [rsp+0x90],xmm7                        
76496b movdqa [rsp+0x80],xmm6                        
764974 mov r14,r9                                    
```
- Signature guess: `uint8_t* sub_7647c0(void* a0 /*rcx decoder ctx*/, void* a1 /*rdx dim ptr*/, void* a2 /*r8 dim ptr*/, void* a3 /*r9 comp ptr*/, int a4 /*req comp*/)` [I]
- Returns: rax = pointer to 8-bit pixel buffer (w*h*comp bytes) or NULL [I via return paths 764840/76491e]
- Calls: sub_777ed0 (decoder) at 7647f7 [V]; heap alloc [data_f9a6fa0] at 76481f [V]; heap free [data_f9a6f98] at 764918 [V]; stack-fail 0xE951550 at 764948 [V]
- Fields touched: [rsp+0x3C] R (decoder format out-param) [V]; [a1+0] R [V]; [a2+0] R [V]; [a3+0] R (if a4==0) [V]; data_f59fac1 "outofmem" → [tls+0xC98] W on alloc failure [V via 764861]
- OPEN: whether rax from sub_777ed0 is an image object or raw pixel data; [rsp+0x3C] exact meaning (format vs bpp) [?]

## Step (2): disassemble 0x764950 (120 instructions, 3 phases of 40) — DONE

`rdis dis 0x764950 120` → sub_764950 [0x764950..0x766950) nominal size 0x2000, 2 xrefs in [V via rdis header]. Output cut at instr 120 (0x764af3); body continues beyond.

### Phase 1: 0x764950..0x7649e0 (instr 1-40) — prologue, sub_764E50 guard, tail call to sub_77f0b0
```
764950  push r15                                      
764952  push r14                                      
764954  push r13                                      
764956  push r12                                      
764958  push rsi                                      
764959  push rdi                                      
76495a  push rbp                                      
76495b  push rbx                                      
76495c  sub rsp,0xA8                                  
764963  movaps [rsp+0x90],xmm7                        
76496b  movdqa [rsp+0x80],xmm6                        
764974  mov r14,r9                                    
764977  mov rdi,r8                                    
76497a  mov rbx,rdx                                   
76497d mov rsi,rcx                                   
764980 mov ebp,[rsp+0x110]                            
764987 mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
76498e xor rax,rsp                                   
764991 mov [rsp+0x78],rax                            
764996 call 0x764E50                                 ; -> sub_764e50
76499b test eax,eax                                  
76499d je short 0x7649EB                             ; -> loc_7649eb
76499f mov rax,[rsp+0x78]                            
7649a4 xor rax,rsp                                   
7649a7 mov rcx,[0x1230A0C0]                          ; [data_1230a0c0]
7649ae cmp rcx,rax                                   
7649b1 jne 0x764E3B                                  ; -> loc_764e3b (stack fail)
7649b7 mov rcx,rsi                                   
7649ba mov rdx,rbx                                   
7649bd mov r8,rdi                                    
7649c0 mov r9,r14                                    
7649c3 movaps xmm6,[rsp+0x80]                        
7649cb movaps xmm7,[rsp+0x90]                        
7649d3 add rsp,0xA8                                  
7649da pop rbx                                       
7649db pop rbp                                       
7649dc pop rdi                                       
7649dd pop rsi                                       
7649de pop r12                                       
7649e0 pop r13                                       
```
// [V] x64 args: rcx=a1, rdx=a2→rbx, r8=a3→rdi, r9=a4→r14, [rsp+0x110]=a5→ebp [V via 764974-764980]
// [V] call sub_764E50 at 764996; if eax!=0 → restore regs, `jmp 0x77F0B0` tail call forwarding (rcx,rdx,r8,r9) = original args (7649b7-7649e6) [V]
// [V] if eax==0 → fall to decoder path at loc_7649eb

### Phase 2: 0x7649e2..0x764a5a (instr 41-80) — decoder call, format check, dimension overflow validation
```
7649e2 pop r14                                       
7649e4 pop r15                                       
7649e6 jmp 0x77F0B0                                  ; -> sub_77f0b0 (end of phase-1 path)
loc_7649eb:  ; from 76499d
7649eb lea rax,[rsp+0x6C]                            ; out-param ptr
7649f0 mov [rsp+0x28],rax                            ; 6th stack arg to decoder
7649f5 mov [rsp+0x20],ebp                            ; 5th stack arg = a5
7649f9 mov rcx,rsi                                   ; a1
7649fc mov rdx,rbx                                   ; a2
7649ff mov r8,rdi                                    ; a3
764a02 mov r9,r14                                    ; a4
764a05 call 0x777ED0                                 ; -> sub_777ed0 (image decoder)
764a0a test rax,rax                                  
764a0d je 0x764B48                                   ; -> loc_764b48 (decoder NULL)
764a13 cmp dword ptr [rsp+0x6C],8                    ; decoder format out-param
764a18 jne 0x764B67                                  ; -> loc_764b67 if format != 8
764a1e mov rsi,rax                                   ; rsi = decoder data pointer
764a21 test ebp,ebp                                  
764a23 jne short 0x764A28                            ; if a5 != 0 skip
764a25 mov ebp,[r14]                                 ; ebp = *a4 (file comp count)
loc_764a28:  ; from 764a23, 764d7a
764a28 mov ecx,[rdi]                                  ; ecx = *a3 (dim1)
764a2a mov edi,[rbx]                                  ; edi = *a2 (dim2)
764a2c mov eax,edi                                   
764a2e or eax,ecx                                    
764a30 js 0x764B19                                   ; fail if either negative
764a36 test ecx,ecx                                  
764a38 je short 0x764A4B                             ; if dim1==0 skip div check
764a3a mov eax,0x7FFFFFFF                           
764a3f xor edx,edx                                   
764a41 div ecx                                       
764a43 cmp edi,eax                                   
764a45 jg 0x764B19                                   ; fail if dim2 > max/dim1 (overflow guard)
loc_764a4b:  ; from 764a38
764a4b imul edi,ecx                                   ; edi = dim1*dim2
764a4e mov eax,edi                                   
764a50 or eax,ebp                                    
764a52 js 0x764B19                                   ; fail if negative
764a58 test ebp,ebp                                  
764a5a je short 0x764A6D                             ; if comp==0 skip
```
// [V] decoder called with (rcx=a1, rdx=a2, r8=a3, r9=a4, stack a5, stack &[rsp+0x6C]); if rax==0 → loc_764b48; dword [rsp+0x6C] compared to 8; if !=8 → loc_764b67 (alternate path, unseen) [V via 764a13]
// [V] rsi = decoder return (source pixel data)
// [V] ebp = comp = (a5 != 0 ? a5 : *a4) [V via 764a21-764a25]
// [V] ecx = *a3, edi = *a2; overflow checks: both >=0 (764a30 js); dim2 <= 0x7FFFFFFF/dim1 via div (764a3a-764a45); edi = dim1*dim2 (764a4b imul); then w*h <= 0x7FFFFFFF/comp via second div (764a5c-764a67) [V]

### Phase 3: 0x764a5c..0x764af3 (instr 81-120) — size computation, allocation, conversion setup
```
764a5c mov eax,0x7FFFFFFF                           
764a61 xor edx,edx                                   
764a63 div ebp                                       
764a65 cmp edi,eax                                   
764a67 jg 0x764B19                                   ; -> loc_764b19 (fail)
loc_764a6d:  ; from 764a5a
764a6d mov ecx,edi                                   
764a6f imul ecx,ebp                                   ; ecx = w*h*comp
764a72 cmp ecx,0x1FFFFFFF                            ; 536,870,911 cap
764a78 ja 0x764B19                                   ; fail if over
764a7e shl ecx,2                                      ; bytes = count*4
764a81 call qword ptr [0xF9A6FA0]                    ; [data_f9a6fa0] allocator
764a87 test rax,rax                                  
764a8a je 0x764B19                                   ; fail if alloc NULL
764a90 mov r14,rax                                    ; r14 = new buffer
764a93 mov eax,ebp                                   
764a95 and eax,1                                     
764a98 cmp eax,1                                     
764a9b mov ecx,ebp                                   
764a9d sbb ecx,0                                      ; ecx = comp rounded down to even
764aa0 test edi,edi                                   ; w*h > 0?
764aa2 jle 0x764E2D                                  ; -> loc_764e2d if not
764aa8 mov [rsp+0x30],rsi                             ; save src ptr
764aad mov [rsp+0x50],ebp                             ; save comp
764ab1 movsxd r10,ebp                                
764ab4 mov [rsp+0x4C],edi                             ; save w*h
764ab8 mov eax,edi                                   
764aba mov [rsp+0x38],rax                             ; save w*h
764abf test ecx,ecx                                  
764ac1 mov [rsp+0x40],r10                             ; save comp
764ac6 mov esi,ecx                                   
764ac8 jle 0x764D85                                  ; -> loc_764d85 if even-comp==0
764ace mov r13d,esi                                  
764ad1 mov [rsp+0x58],r13                            
764ad6 and r13d,0x7FFFFFFE                           
764add lea r15,[r14+4]                                ; dst = buf+4
764ae1 lea rax,[r10*4]                                ; comp*4
764ae9 mov [rsp+0x60],rax                             ; row stride = comp*4
764aee mov rax,[rsp+0x30]                             ; src
764af3 lea r12,[rax+1]                                ; src+1
```
// [V] ecx = w*h*comp; capped at 0x1FFFFFFF (764a72); bytes = ecx << 2 (764a7e) → alloc size = w*h*comp*4 [V]
// [V] alloc via [data_f9a6fa0] at 764a81; fail → loc_764b19 [V]; r14 = result buffer [V]
// [V] ecx = comp rounded down to even (sbb after cmp eax,1 where eax = comp&1) [V via 764a93-764a9d]
// [V] conversion setup: src=[rsp+0x30], comp=[rsp+0x50], w*h=[rsp+0x4C], even-comp=[rsp+0x40], stride=comp*4 [rsp+0x60], dst=r14+4, scan ptr src+1 (r12), index ebp=0 [V via 764aa8-764af3]
// [V] constants loaded: [data_ef40d58]→xmm7 (764af9), [data_f08eb90]→xmm6 (764b01), [data_f9a8f28]→rbx (764b09) — float/UNORM conversion constants likely [I]
- Signature guess: `uint32_t* sub_764950(void* a1 /*rcx decoder ctx*/, void* a2 /*rdx dim ptr*/, void* a3 /*r8 dim ptr*/, void* a4 /*r9 comp ptr*/, int a5 /*req comp*/)` [I]
- Returns: rax = pointer to 32-bit pixel buffer (w*h*4 bytes), or NULL; alternate path tail-calls sub_77f0b0 if sub_764E50 != 0 [I]
- Calls: sub_764E50 at 764996 [V]; sub_77f0b0 tail call at 7649e6 [V]; sub_777ed0 decoder at 764a05 [V]; alloc [data_f9a6fa0] at 764a81 [V]
- Fields touched: [rsp+0x6C] W decoder format out-param then R (cmp to 8) [V]; [*a3] R [V]; [*a2] R [V]; [*a4] R if a5==0 [V]
- OPEN: loc_764b48/loc_764b67/loc_764b19/loc_764e2d/loc_764d85 targets unseen (beyond 120 instr); exact pixel format of output [?]

## Step (3): disassemble 0x19944b0 (120 instructions, 3 phases of 40) — DONE

`rdis dis 0x19944b0 120` → sub_19944b0 [0x19944b0..0x19964b0) nominal size 0x2000, 4 xrefs in [V via rdis header]. Output cut at instr 120 (0x1994757); no ret/epilogue seen in range.

### Phase 1: 0x19944b0..0x199457f (instr 1-40) — prologue, copy *a2 into frame, allocator call setup
```
19944b0  push rbp                                      
19944b1  push r15                                      
19944b3  push r14                                      
19944b5  push r13                                      
19944b7  push r12                                      
19944b9  push rsi                                      
19944ba  push rdi                                      
19944bb  push rbx                                      
19944bc  sub rsp,0x298                                 
19944c3  lea rbp,[rsp+0x80]                            
19944cb  movaps [rbp+0x200],xmm6                       
19944d2 mov qword ptr [rbp+0x1F8],0xFFFFFFFFFFFFFFFE  
19944dd mov rbx,rdx                                   
19944e0 mov rsi,rcx                                   
19944e3 mov dword ptr [rbp+0x1F4],0                   
19944ed mov dword ptr [rbp+0x1EC],0                   
19944f7 mov dword ptr [rbp+0x1F0],0                   
1994501 xorps xmm0,xmm0                               
1994504 movaps [rbp+0x1A0],xmm0                       
199450b movups xmm0,[rdx]                             ; R a1+0x0 (a2 = rdx = rbx)
199450e movaps [rbp+0x10],xmm0                        
1994512 mov eax,[0x128D09C0]                          ; [data_128d09c0]
1994518 mov ecx,[0x128767C8]                          ; [data_128767c8]
199451e mov rdx,gs:[0x58]                             
1994527 mov rcx,[rdx+rcx*8]                           
199452b cmp eax,[rcx+4]                               
1994531 jg 0x1994D73                                  ; -> loc_1994d73 (security check fail)
loc_1994537:  ; from 1994d86, 1994db1
1994537 movaps xmm0,[rbp+0x10]                        
199453b movaps [rbp+0xA0],xmm0                        
1994542 lea rcx,[0x128D09A0]                          ; [data_128d09a0]
1994549 mov rax,[0x128D09A0]                          ; [data_128d09a0]
1994550 mov rax,[rax+8]                               
1994554 mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
199455b mov dword ptr [rsp+0x28],0                    
1994563 mov word ptr [rsp+0x20],0x121                 
199456a lea rdx,[rbp-0x38]                            
199456e lea r8,[rbp+0xA0]                             
1994575 lea r9,[rbp+0x1A0]                            
199457c call r10                                      
199457f nop                                           
```
// [V] x64 args: rcx=a1→rsi, rdx=a2→rbx (and [rdx] 16-byte struct copied to [rbp+0x10]/[rbp+0xA0]) [V via 19944dd/19944e0/199450b]
// [V] frame locals zeroed [rbp+0x1F4]/[rbp+0x1EC]/[rbp+0x1F0] [V]; stack cookie data_1230a0c0 pattern (data_128d09c0 vs TLS here) [V via 1994512-199452b]
// [V] call r10 = [data_f99ffa0] = sub_eea6040 (allocator, per U-L8b convention) at 199457c with rcx=[rbp-0x38], rdx..., r8=[rbp+0xA0] (the *a2 copy), r9=[rbp+0x1A0] — constructing an object [V/I]
// [V] word [rsp+0x20] = 0x121 (size/flags?), dword [rsp+0x28]=0 [V]

### Phase 2: 0x1994580..0x199467f (instr 41-80) — object init: vtable-ish slots, callbacks, string refs
```
1994580 mov rdi,0x29AAF7A7645E47FD                    ; constant
199458a mov [rbp+0x20],rdi                            
199458e lea r12,[0xF81EDF7]                           ; [data_f81edf7] (string/object ref)
1994595 mov [rbp+0x28],r12                            
1994599 mov qword ptr [rbp+0x30],1                    
19945a1 mov dword ptr [rbp+0x38],0xBB                 
19945a8 lea r14,[0xAA6D0]                             ; [sub_aa6d0] callback
19945af mov [rbp+0x40],r14                            
19945b3 lea r13,[0x3AFCB0]                            ; [sub_3afcb0] callback
19945ba mov [rbp+0x48],r13                            
19945be lea rax,[rbp+0x20]                            
19945c2 mov [rsp+0x20],rax                            
19945c7 lea rcx,[rbp-0x38]                            
19945cb lea r9,[rbp+0x40]                             
19945cf mov edx,2                                     
19945d4 mov r8d,0x2D                                  
19945da call 0x3AFBE0                                 ; -> sub_3afbe0
19945df cmp byte ptr [rax+0x40],1                     ; R ret@3afbe0+0x40
19945e3 jne 0x199472A                                 ; -> loc_199472a
19945e9 mov [rbp+0x98],rbx                             ; save a2
19945f0 movaps xmm0,[rbp+0x1A0]                       
19945f7 mov rcx,[rbp+0x1A0]                           
19945fe mov qword ptr [rbp+0x1A0],0                   
1994609 movaps [rbp+0x1D0],xmm0                       
1994610 mov qword ptr [rbp+0x1A8],0                   
199461b mov rax,[0xF0FF760]                           ; [data_f0ff760] = sub_199b080
1994622 mov [rbp+0xC0],rax                            
1994629 movups xmm6,[0xF0FF750]                       ; [data_f0ff750] = sub_199ae80
1994630 movups [rbp+0xB0],xmm6                        
1994637 lea rax,[rbp+0x1D0]                           
199463e mov [rbp+0xC8],rax                            
1994645 mov rax,0x8000000001                          
199464f mov [rbp+0xD0],rax                            
1994656 mov dword ptr [rbp+0x158],0                   
1994660 mov r15,r14                                    ; r15 = sub_aa6d0
1994663 lea r14,[rbp+0xD8]                             ; r14 = buffer ptr
199466a mov [rbp+0x170],r14                           
1994671 mov [rbp+0x160],r14                           
1994678 lea rax,[rbp+0x1B8]                           
199467f mov [rsp+0x20],rax                            
```
// [V] object slots: [rbp+0x20]=const 0x29AAF7A7645E47FD; [rbp+0x28]=data_f81edf7; [rbp+0x30]=1; [rbp+0x38]=0xBB; [rbp+0x40]=sub_aa6d0; [rbp+0x48]=sub_3afcb0 [V]
// [V] call sub_3afbe0 at 19945da; require byte [rax+0x40]==1 else → loc_199472a (edi=0 path) [V]
// [V] [rbp+0x98]=rbx (a2 saved); [rbp+0x1D0] = copy of [rbp+0x1A0] (*a2 content), [rbp+0x1A0]=0 [V]
// [V] [rbp+0xC0]=sub_199b080 (data_f0ff760); [rbp+0xB0]=sub_199ae80 (data_f0ff750); [rbp+0xC8]=&[rbp+0x1D0]; [rbp+0xD0]=0x8000000001; [rbp+0x158]=0 (byte counter) [V]
// [V] stream state: r14=&[rbp+0xD8] (buffer); [rbp+0x170]=[rbp+0x160]=&[rbp+0xD8] (pos/end init to buffer start) [V]
// [I] layout = stream/reader object wrapping a2: callbacks sub_aa6d0/sub_3afcb0/sub_199b080/sub_199ae80, buffer at +0xD8 relative to frame base

### Phase 3: 0x1994684..0x1994757 (instr 81-120) — fill buffer via sub_45e6f0, parse value, sub_87440, position bookkeeping
```
1994684 lea rbx,[rbp+0x50]                            
1994688 mov r9d,0x80                                  
199468e mov rdx,rbx                                   
1994691 mov r8,r14                                     ; &[rbp+0xD8]
1994694 call 0x45E6F0                                 ; -> sub_45e6f0 (read up to 0x80 bytes)
1994699 mov [rbp+0x180],rdi                            ; result/bytes
19946a0 mov [rbp+0x188],r12                            ; data_f81edf7
19946a7 mov qword ptr [rbp+0x190],1                    
19946b2 mov dword ptr [rbp+0x198],0x26                
19946bc mov [rbp+0x1C0],r15                            ; sub_aa6d0
19946c3 mov [rbp+0x1C8],r13                            ; sub_3afcb0
19946ca lea rax,[rbp+0x180]                            
19946d1 mov [rsp+0x20],rax                            
19946d6 lea r9,[rbp+0x1C0]                            
19946dd mov rcx,rbx                                   
19946e0 mov edx,2                                     
19946e5 mov r8d,0x2D                                  
19946eb call 0x3AFBE0                                 ; -> sub_3afbe0
19946f0 cmp byte ptr [rax+0x40],0                     
19946f4 mov r15d,0xFFFFFFFF                            ; default = -1
19946fa je short 0x1994703                             ; if byte==0
19946fc mov r15d,[rbp+0x1B8]                           ; else r15d = parsed value
loc_1994703:  ; from 19946fa
1994703 mov rcx,rbx                                   
1994706 call 0x87440                                  ; -> sub_87440
199470b mov eax,[rbp+0x160]                           
1994711 sub eax,[rbp+0x170]                           
1994717 add [rbp+0x158],eax                            ; byte counter += delta
199471d test r15d,r15d                                
1994720 je short 0x1994731                             ; if r15d==0
1994722 movsxd rax,r15d                               
1994725 add rax,r14                                    ; rax = buffer + r15d
1994728 jmp short 0x1994749                            ; -> loc_1994749
loc_199472a:  ; from 19945e3
199472a xor edi,edi                                   
199472c jmp 0x1994CE9                                 ; -> loc_1994ce9 (unseen)
loc_1994731:  ; from 1994720
1994731 mov dword ptr [rbp+0xD0],0                    
199473b lea rax,[rbp+0xD9]                            
1994742 mov byte ptr [rbp+0xD8],0                     
loc_1994749:  ; from 1994728
1994749 mov [rbp+0x160],r14                           
1994750 mov [rbp+0x168],rax                           
1994757 mov [rbp+0x178],rax                            ; (--max 120 cut here)
```
// [V] lea rbx,[rbp+0x50]; call sub_45e6f0(rcx=rbx, rdx=rbx, r8=&[rbp+0xD8], r9d=0x80) — read up to 0x80 bytes into buffer [V via 1994684-1994694]; [rbp+0x180]=rdi result
// [V] more slots: [rbp+0x188]=data_f81edf7, [rbp+0x190]=1, [rbp+0x198]=0x26, [rbp+0x1C0]=sub_aa6d0, [rbp+0x1C8]=sub_3afcb0 [V]
// [V] second sub_3afbe0 call at 19946eb; r15d = -1 default, else [rbp+0x1B8] [V]
// [V] call sub_87440 at 1994706; [rbp+0x158] += [rbp+0x160]-[rbp+0x170] (bytes consumed) [V]
// [V] if r15d!=0: rax = &[rbp+0xD8] + r15d; else [rbp+0xD0]=0, [rbp+0xD8]=0, rax=&[rbp+0xD9]; then [rbp+0x160]=&[rbp+0xD8], [rbp+0x168]=[rbp+0x178]=rax [V]
- Signature guess: `object* sub_19944b0(void* a1 /*rcx*/, void* a2 /*rdx: source struct w/ 16-byte header*/)` [I] — constructs stream/reader object around a2
- Returns: rax = ? (constructed object ptr or 0 via loc_199472a path); epilogue not in range [?]
- Calls: sub_eea6040 [data_f99ffa0] at 199457c [V]; sub_3afbe0 at 19945da and 19946eb [V]; sub_45e6f0 at 1994694 [V]; sub_87440 at 1994706 [V]
- Refs: data_f81edf7 (likely string) [V via 199458e]; sub_aa6d0, sub_3afcb0, sub_199b080, sub_199ae80 as callbacks [V]
- OPEN: exact return value; whether this object is the decoder context consumed by sub_777ed0 (rcx of decoder has cursor/end at +0xC0/+0xC8 per U-L8b — this frame's buffer at rbp+0xD8 doesn't obviously match) [?]
- OPEN: loc_1994ce9, loc_1994d73 targets unseen [?]

## Step (4): disassemble 0x1994f90 (120 instructions, 3 phases of 40) — DONE

`rdis dis 0x1994f90 120` → sub_1994f90 [0x1994f90..0x1996f90) nominal size 0x2000, 30 xrefs in [V via rdis header]. Output cut at instr 120 (indirect `jmp rax` via jump table at 19951d0).

### Phase 1: 0x1994f90..0x1995049 (instr 1-40) — prologue, arg save, bad-arg fast path with magic checks
```
1994f90  push rbp                                      
1994f91  push r15                                      
1994f93  push r14                                      
1994f95  push r13                                      
1994f97  push r12                                      
1994f99  push rsi                                      
1994f9a  push rdi                                      
1994f9b  push rbx                                      
1994f9c  sub rsp,0x1B8                                 
1994fa3  lea rbp,[rsp+0x80]                            
1994fab mov qword ptr [rbp+0x130],0xFFFFFFFFFFFFFFFE  
1994fb6 mov r12,r9                                     ; a4 = buffer ptr
1994fb9 mov ebx,r8d                                    ; a3 = component request
1994fbc mov rdi,rdx                                    ; a2
1994fbf mov r13,rcx                                    ; a1
1994fc2 mov r15,[rbp+0x1A0]                            ; a5 = buffer size (5th stack arg)
1994fc9 mov qword ptr [rbp+0xE0],0                    
1994fd4 mov qword ptr [rbp+0xD0],0                    
1994fdf mov dword ptr [rbp+0xD8],0                    
1994fe9 mov qword ptr [rbp+0xC0],0                    
1994ff4 mov qword ptr [rbp+0xC5],0                    
1994fff test r9,r9                                    
1995002 sete al                                        ; al = (a4==0)
1995005 cmp r15,0x40                                  
1995009 setb cl                                        ; cl = (a5 < 0x40)
199500c or cl,al                                      
199500e jne short 0x199502F                            ; if a4==0 or a5<0x40 → main path
1995010 mov rax,[r12]                                 ; R a3+0x0 = *a4
1995014 xor rax,[0xF4DE65C]                           ; [data_f4de65c]
199501b mov ecx,[r12+8]                               ; R a3+0x8 = *(a4+8)
1995020 xor ecx,[0xF4DE664]                           ; [data_f4de664]
1995026 or rcx,rax                                    
1995029 je 0x1995148                                  ; if obfuscated *a4 == 0 → alternate path loc_1995148
// [V] x64 args: rcx=a1→r13, rdx=a2→rdi, r8d=a3→ebx (comp request), r9=a4→r12 (buffer ptr), stack [rbp+0x1A0]=a5→r15 (buffer size) [V]
// [V] if !(a4==0 || a5<0x40): rax = *a4 xor data_f4de65c; ecx = *(a4+8) xor data_f4de664; if both zero → loc_1995148 (alternate/format-probe path)

// loc_199502f (main path):
199502f mov [rbp+0x120],r13                            ; save a1
1995036 xor r13d,r13d                                 
1995039 mov sil,1                                     
199503c cmp ebx,4                                      ; a3 <= 4?
199503f ja short 0x1995050                            
1995041 mov eax,0x1A                                   ; bitmask 00011010b → valid comp counts {1,3,4}
1995046 bt eax,ebx                                    
1995049 jae short 0x1995050                            ; if bit not set → invalid
```

### Phase 2: 0x1995049..0x199511e (instr 41-80) — comp validation, stream range setup, sub_764E50 guard
```
1995049 jae short 0x1995050                            (from phase 1)
199504b xor esi,esi                                    ; esi = 0 (valid comp)
199504d mov r13d,ebx                                   ; r13d = a3 (req_comp)
loc_1995050:  ; from 199503f, 1995049
1995050 mov dword ptr [rbp+0x10C],0                    ; out: comp = 0
199505a mov dword ptr [rbp+0x11C],0                    ; out: dim1 = 0
1995064 mov dword ptr [rbp+0x12C],0                    ; out: dim2 = 0
199506e movsxd rax,r15d                               
1995071 cmp rax,r15                                    ; size must fit int32
1995074 jne 0x1995A31                                  ; -> loc_1995a31 (fail)
199507a mov eax,r15d                                  
199507d and eax,0x80000000                            
1995082 jne 0x1995A31                                  ; fail if size negative
1995088 mov qword ptr [rbp-0x10],0                    
1995090 mov dword ptr [rbp+0x10],0                    
1995097 mov dword ptr [rbp+0x98],0                    
19950a1 mov [rbp+0xB0],r12                             ; stream start = a4
19950a8 mov [rbp+0xA0],r12                            
19950af add r15,r12                                    ; stream end = a4 + a5
19950b2 mov [rbp+0xB8],r15                            
19950b9 mov [rbp+0xA8],r15                            
19950c0 lea r14,[rbp-0x20]                             ; ctx local
19950c4 mov rcx,r14                                   
19950c7 call 0x764E50                                 ; -> sub_764e50 (context init/guard)
19950cc test sil,sil                                  
19950cf je short 0x19950E1                             ; if sil==0
19950d1 test eax,eax                                  
19950d3 je 0x1995239                                  ; -> loc_1995239
19950d9 mov r13d,3                                     ; r13d = 3 (default comp)
19950df jmp short 0x19950E9                            ; -> loc_19950e9
loc_19950e1:  ; from 19950cf
19950e1 test eax,eax                                  
19950e3 je 0x19952A0                                  ; -> loc_19952a0
loc_19950e9:  ; from 19950df
19950e9 mov qword ptr [rbp-0x10],0                    
19950f1 mov dword ptr [rbp+0x10],0                    
19950f8 mov dword ptr [rbp+0x98],0                    
1995102 mov [rbp+0xB0],r12                             ; (re)store stream start/end
1995109 mov [rbp+0xA0],r12                            
1995110 mov [rbp+0xB8],r15                            
1995117 mov [rbp+0xA8],r15                            
199511e mov [rsp+0x20],r13d                            ; stack arg to sub_764950 = req_comp
// [V] valid comp counts {1,3,4} via bt 0x1A,ebx; r13d = a3 if valid else 0; invalid size → loc_1995a31 [V]
// [V] stream range [r12, r12+r15) = [a4, a4+a5) stored at [rbp+0xA0..0xB8] [V]
// [V] call sub_764E50 at 19950c7 with rcx=&[rbp-0x20] (decoder/stream context) [V]; branches on sil/eax to loc_1995239 / loc_19952a0 / req_comp=3
```

### Phase 3: 0x1995123..0x19951d0 (instr 81-120) — call sub_764950 (image producer); alternate format-probe path + jump table
```
1995123 lea rcx,[rbp-0x20]                             ; a1 = ctx
1995127 lea rdx,[rbp+0x11C]                            ; a2 = &dim1 out
199512e lea r8,[rbp+0x12C]                             ; a3 = &dim2 out
1995135 lea r9,[rbp+0x10C]                             ; a4 = &comp out
199513c call 0x764950                                 ; -> sub_764950 (returns pixel buffer in rax)
1995141 xor edx,edx                                    ; status = 0
1995143 jmp 0x19952FA                                 ; -> loc_19952fa (exit)
loc_1995148:  ; from 1995029 (bad-arg alternate path)
1995148 lea r14,[rbp-0x20]                            
199514c mov rcx,r14                                   
199514f mov rdx,r12                                   
1995152 call 0xE335C80                                ; -> sub_e335c80
1995157 nop                                           
1995158 mov eax,[rbp-0x14]                            
199515b cmp eax,0x4030201                              ; magic #1
1995160 je short 0x199516D                           
1995162 cmp eax,0x1020304                              ; magic #2
1995167 jne 0x199502F                                 ; neither → retry main path
loc_199516d:  ; from 1995160
199516d cmp dword ptr [rbp+8],0                       
1995171 je 0x199502F                                  ; field checks: [rbp+8]==0, [rbp+0xC]==0, [rbp+0x14]==1, [rbp+0x10]==0
1995177 cmp dword ptr [rbp+0xC],0                     
199517b jne 0x199502F                                
1995181 cmp dword ptr [rbp+0x14],1                    
1995185 jne 0x199502F                                
199518b cmp dword ptr [rbp+0x10],0                    
199518f jne 0x199502F                                
1995195 lea rcx,[rbp+0xE0]                            
199519c lea rdx,[rbp+0xC0]                            
19951a3 mov r8,r12                                    
19951a6 mov r9,r15                                    
19951a9 call 0xE336840                                ; -> sub_e336840
19951ae nop                                           
19951af test al,al                                    
19951b1 je 0x199502F                                  ; if sub_e336840 fails → main path
19951b7 cmp ebx,4                                     
19951ba ja 0x1995912                                  ; -> loc_1995912 if a3 > 4
19951c0 mov eax,ebx                                   
19951c2 lea rcx,[0xF0FFB74]                           ; [data_f0ffb74] jump table base
19951c9 movsxd rax,[rcx+rax*4]                        ; table[a3]
19951cd add rax,rcx                                   
19951d0 jmp rax                                       ; indirect jump (--max 120 cut here)
// [V] call sub_764950(rcx=&[rbp-0x20] ctx, rdx=&[rbp+0x11C] dim1, r8=&[rbp+0x12C] dim2, r9=&[rbp+0x10C] comp, stack req_comp=r13d); returns rax = pixel buffer [V]; edx=0 status; jmp loc_19952fa
// [V] alternate path: sub_e335c80 at 1995152; magic [rbp-0x14] == 0x4030201 or 0x1020304 [V]; field validations [V]; sub_e336840 at 19951a9(rcx=&[rbp+0xE0], rdx=&[rbp+0xC0], r8=r12, r9=r15) [V]; jump table via data_f0ffb74 indexed by a3 [V]
- Signature guess: `uint8_t* sub_1994f90(void* a1, void* a2, int a3 /*req comp in {1,3,4}*/, void* a4 /*file bytes ptr*/, size_t a5 /*file bytes size*/)` with out-params dim1=[rbp+0x11C], dim2=[rbp+0x12C], comp=[rbp+0x10C] [I]
- Returns: rax = loaded pixel buffer (from sub_764950, 32-bit w*h*4 per its analysis); edx = status [I]
- Calls: sub_764E50 at 19950c7 [V]; sub_764950 at 199513c [V]; sub_e335c80 at 1995152 [V]; sub_e336840 at 19951a9 [V]; indirect jmp via [data_f0ffb74+a3*4] at 19951c9 [V]
- Fields written: [rbp+0x10C] comp out, [rbp+0x11C] dim1 out, [rbp+0x12C] dim2 out (consumed by sub_764950 call) [V]; stream range [rbp+0xA0..0xB8] [V]
- OPEN: what sub_764E50 writes into ctx &[rbp-0x20]; whether dim out-slots are filled by sub_764E50/sub_777ed0 or sub_764950 (sub_764950 reads [*a2]/[*a3] as INPUTS per its own disasm — tension noted) [?]
- This is the file-bytes→image loader: most likely the resource-pack texture-loader entry point among the four functions [I]

## Step (5): xref.py callers on image-returning function — DONE

Image-returning function chosen: **sub_764950** — it allocates (`[data_f9a6fa0]`, size w*h*comp*4 at 764a7e-764a81 [V]) and returns the finished 32-bit pixel buffer in rax (sub_7647c0 only converts 16→8-bit and can pass the decoder pointer straight through; sub_1994f90 is the file-bytes wrapper that delegates to sub_764950; sub_19944b0 constructs a stream object, not an image) [I for the choice; V for the return-path code].

### Level 1 (direct callers of sub_764950) — `python tools/sigs/xref.py callers 0x764950`
```
0x19944b0 0x906
0x1994f90 0xac5
```
- 0x19944b0 calls sub_764950 at +0x906 [V via xref]; in our 120-instr window sub_19944b0 calls the decoder sub_777ed0 directly at ...wait, no: sub_19944b0's window shows sub_3afbe0/sub_45e6f0/sub_87440, no sub_764950 — the +0x906 call site (0x1994DB6) is beyond the 120-instr cut [V via xref; window cut at 0x1994757].
- 0x1994f90 calls sub_764950 at 199513c (+0xac5) [V via both xref and direct disasm 199513c].

### Level 2 (callers of the level-1 functions)

Callers of 0x19944b0 (`xref.py callers 0x19944b0`):
```
0x327530 0x5f
0x69d4d0 0x1e68
0x2265160 0x1576
0x23f3f20 0x10a8
```
Callers of 0x1994f90 (`xref.py callers 0x1994f90`):
```
0x108c90 0x1afa  0x398fc0 0x611  0xa08dd0 0x81b  0xfc4760 0x3a1
0xfcb2d0 0x5ad  0xfd26e0 0x7b7  0x1679d40 0x9d3  0x17c5040 0x27f
0x1f4df80 0x22d  0x1f4e5b0 0x38e  0x1f506b0 0x7af  0x1f5cd70 0x20f
0x1f5d110 0x182  0x25cf6f0 0xba4  0x4e8b8f0 0x352  0x541bf00 0x7a0
0x541cb30 0x83d  0x5420c20 0x309  0x5421230 0x328  0x5a31160 0x345
0x6632fd0 0x1531 0x668a140 0x3f6  0x69dd7b0 0x87d  0x69e11a0 0x47f
0x6c0f490 0x9db  0x6dbf280 0x1579
```
(matches U-L8b level-3 list for 0x1994f90) [V via xref]

### Texture-loader identification (strings "Failed to load the contents of file", ".png", "textures/")
- "Failed to load the contents of file %s; it will be skipped." at data 0xf80e3c7; only xref ref is 0x779b101 **inside sub_0x779adf0 itself** [V via xref str]. `xref.py callers 0x779adf0` → empty (no callers found) [V via xref]. So no level-1/2 caller of sub_764950 directly calls the failure printer per xref [V].
- ".png": xref refs inside sub_0x399700 (0x3997ef/0x3998e9/0x399b16), sub_0x69c9570 (0x69c989d) — neither is a level-1/2 caller [V via xref str]. BUT "look_up_tables.png" at 0xf5b2ae6 has ref 0x6633ebf **inside sub_0x6632fd0** [V via xref str], and sub_0x6632fd0 is a level-2 caller of sub_1994f90 (0x1994f90+0x1531) [V via xref callers].
- "textures/": `xref.py str "textures/"` timed out at 300s (same as U-L8b) [V via tool timeout] — could not complete that check.
- Context: 0x5a31160 (level 2 via 0x1994f90) sits next to texture_set JSON loaders 0x5a321f0/0x5a46e60/0x5a47a90 from U-L8b [I via U-L8b].

Conclusion: **0x6632fd0** is the strongest resource-pack texture-loader candidate in the caller tree: level 2 (→0x1994f90→sub_764950→decoder sub_777ed0), and it references a PNG texture name ("look_up_tables.png") [V]. None of the level-1 functions (0x19944b0, 0x1994f90) themselves contain the "Failed to load" string or a ".png" ref [V]. The "textures/" check could not be completed (tool timeout) [?].

## Unit U-L8c — DONE
File: docs/progress/oc_U-L8c.md (only file created; no other file edited).
- sub_7647c0: decoder wrapper + 16-bit→8-bit pixel conversion; returns uint8_t* buffer (w*h*comp) or NULL; calls sub_777ed0, alloc [data_f9a6fa0], free [data_f9a6f98].
- sub_764950: decoder wrapper + 32-bit pixel buffer; returns uint32_t* (w*h*4); calls sub_764E50 (guard), sub_77f0b0 (tail), sub_777ed0, alloc [data_f9a6fa0]. = the image-returning function.
- sub_19944b0: stream/reader-object constructor around source struct a2; callbacks sub_aa6d0/sub_3afcb0/sub_199b080/sub_199ae80; alloc sub_eea6040.
- sub_1994f90: file-bytes loader [a4, a4+a5); validates comp {1,3,4} via bitmask 0x1A; calls sub_764E50 then sub_764950; returns pixel buffer + dim/comp out-slots; alternate magic-probe path (0x4030201/0x1020304) via sub_e335c80/sub_e336840 + jump table data_f0ffb74.
- Callers of sub_764950: L1 = 0x19944b0, 0x1994f90; L2 as listed above; texture-loader candidate = 0x6632fd0 ("look_up_tables.png" ref).
- OPEN: "textures/" xref timed out (300s); exact return value of sub_19944b0; whether dim out-slots are filled by sub_764E50/decoder vs sub_764950 (tension: sub_764950 reads [*a2]/[*a3] as inputs).

## Step (2): disassemble 0x764950 (120 instructions) — PENDING

## Step (3): disassemble 0x19944b0 (120 instructions) — PENDING

## Step (4): disassemble 0x1994f90 (120 instructions) — PENDING

## Step (5): xref.py callers on image-returning function (2 levels); identify resource-pack texture loader — PENDING

## DONE: none yet