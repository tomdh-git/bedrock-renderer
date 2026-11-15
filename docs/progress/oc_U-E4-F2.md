# U-E4-F2: Chunk builder at 0x677736e — continuation of U-E4-F1

Unit: U-E4-F2
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation
RVAs: 0x677736e .. (800 instructions from 0x677736e)
Source: `rdis dis 0x677736e <n>` on Minecraft.Windows.exe 1.26.62.01
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume at 0x6778c1a (Phase 41) — after `inc rdx`, before `mov [r14+0x7A0],rdx` / `jmp 0x6779146` target region. Covered 0x677736e..0x6778c1a (~700 instructions of 800).

---

## Phase 1 — Call 0x678F640 + copy [rbx+0x68..0x9F] to [rbp+0x6B0..0x574] (0x677736e..0x67773e8)

Calls 0x678F640, then copies fields from [rbx+0x68..0x9F] into [rbp+0x6B0..] with u16 save at [rbp+0x708].

```
0x677736e  lea edx,[rbp+0x1F0]                           
0x6777374  lea r8,[rbp+0x198]                            
0x677737b  lea r9,[rbp+0x110]                            
0x6777382  call 0x678F640                                ; -> sub_678f640
0x6777387  nop                                           
0x6777388  mov eax,[rbx+0x68]                            
0x677738b  lea rcx,[rbp+0x6B0]                           
0x6777392  mov [rcx+0x10],eax                            
0x6777395  movups xmm0,[rbx+0x58]                        
0x6777399  movups [rcx],xmm0                             
0x677739c  movzx eax,byte ptr [rbp+0x25C]                
0x67773a3  mov [rbp+0x6C4],al                            
0x67773a9  movups xmm0,[rbp+0x260]                       
0x67773b0  movups [rbp+0x6C8],xmm0                       
0x67773b7  movups xmm0,[rbx+0x80]                        
0x67773be  movups xmm1,[rbx+0x90]                        
0x67773c5  movups xmm2,[rbx+0x9F]                        
0x67773cc  lea rax,[rbp+0x574]                           
0x67773d3  movups [rax+0x183],xmm2                       
0x67773da  movups [rax+0x174],xmm1                       
0x67773e1  movups [rax+0x164],xmm0                       
0x67773e8  movzx eax,word ptr [rbp+0x2A0]                
```

Interpretation: Call 0x678F640(rcx=&[rbp+0x1F0], r8=&[rbp+0x198], r9=&[rbp+0x110]). Then: eax=[rbx+0x68] stored at [rcx+0x10]=[rbp+0x6C0]. xmm0=[rbx+0x58] stored at [rcx]=[rbp+0x6B0]. al=byte [rbp+0x25C] stored at [rbp+0x6C4]. xmm0=[rbp+0x260] stored at [rbp+0x6C8]. xmm0=[rbx+0x80], xmm1=[rbx+0x90], xmm2=[rbx+0x9F]. rax=&[rbp+0x574]. Store xmm2 at [rax+0x183]=[rbp+0x6F7], xmm1 at [rax+0x174]=[rbp+0x6E8], xmm0 at [rax+0x164]=[rbp+0x6D8]. ax=word [rbp+0x2A0] loaded.

Callees: 0x678F640 (sub_678f640).
Fields read: [rbx+0x68], [rbx+0x58], [rbp+0x25C], [rbp+0x260], [rbx+0x80], [rbx+0x90], [rbx+0x9F], [rbp+0x2A0]. Fields written: [rbp+0x6C0], [rbp+0x6B0], [rbp+0x6C4], [rbp+0x6C8], [rbp+0x6F7], [rbp+0x6E8], [rbp+0x6D8].

---

## Phase 2 — Save u16 + range check on [rbp+0x768]+0x480 (0x67773ef..0x6777443)

Saves u16 [rbp+0x2A0] at [rbp+0x708], loads [rbp+0x768]+0x480 and +0x488, computes difference, range-checks against 0xFFFFFFD0.

```
0x67773ef  mov [rbp+0x708],ax                            
0x67773f6  mov rcx,[rbp+0x768]                           
0x67773fd  mov rax,[rcx+0x480]                           
0x6777404  mov rdx,[rcx+0x488]                           
0x677740b  mov rcx,rdx                                   
0x677740e  sub rcx,rax                                   
0x6777411  cmp rcx,0xFFFFFFFFFFFFFFD0                    
0x6777415  je 0x677E011                                  ; -> sub_677e011
0x677741b  test rax,rax                                  
0x677741e  setne r8b                                     
0x6777422  test rdx,rdx                                  
0x6777425  sete dl                                       
0x6777428  or dl,r8b                                     
0x677742b  je 0x677E011                                  ; -> sub_677e011
0x6777431  sar rcx,4                                     
0x6777435  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x677743f  imul rcx,rdx                                  
0x6777443  mov [rbp+0xE0],rcx                            
```

Interpretation: [rbp+0x708]=ax (u16 from [rbp+0x2A0]). rcx=[rbp+0x768], rax=[rcx+0x480], rdx=[rcx+0x488]. rcx=rdx, rcx-=rax (difference). If difference==0xFFFFFFD0 (-48), jump to 0x677E011 (error). test rax,rax -> setne r8b (rax!=0). test rdx,rdx -> sete dl (rdx==0). or dl,r8b. If result==0, jump to 0x677E011. Otherwise: sar rcx,4 (divide by 16), imul rcx, 0xAAAAAAAAAAAAAAAB (multiply by magic for divide-by-15), store result at [rbp+0xE0].

Callees: none.
Fields read: [rbp+0x2A0], [rbp+0x768], [rcx+0x480], [rcx+0x488]. Fields written: [rbp+0x708], [rbp+0xE0].

---

## Phase 3 — Store [rbp+0xE8] + call 0x678F950 + jump to 0x677ABBA (0x677744a..0x6777478)

Stores rax at [rbp+0xE8], saves r12, calls 0x678F950 with computed args, then jumps to 0x677ABBA.

```
0x677744a  mov [rbp+0xE8],rax                            
0x6777451  mov [rsp+0x20],r12                            
0x6777456  mov rcx,[rbp+0x828]                           
0x677745d  lea rdx,[rbp+0xE0]                            
0x6777464  mov r8,[rbp+0x778]                            
0x677746b  lea r9,[rbp+0x2E0]                            
0x6777472  call 0x678F950                                ; -> sub_678f950
0x6777477  nop                                           
0x6777478  jmp 0x677ABBA                                 ; -> sub_677abba
```

Interpretation: [rbp+0xE8]=rax. [rsp+0x20]=r12. rcx=[rbp+0x828] (BuilderSpan*). rdx=&[rbp+0xE0]. r8=[rbp+0x778] (loop start). r9=&[rbp+0x2E0]. Call 0x678F950. Then unconditional jump to 0x677ABBA.

Callees: 0x678F950 (sub_678f950).
Fields read: [rbp+0xE8], [rsp+0x20], [rbp+0x828], [rbp+0xE0], [rbp+0x778], [rbp+0x2E0]. Fields written: [rbp+0xE8], [rsp+0x20].

---

## Phase 4 — Alternative path: movlps [rbp+0x4A0],xmm15 + movss [rbp+0x4A8],xmm12 + calls 0x678CF10, 0x678E1D0 (0x677747d..0x67774ca)

Stores xmm15/xmm12 to locals, calls 0x678CF10 then 0x678E1D0.

```
0x677747d  movlps [rbp+0x4A0],xmm15                      
0x6777485  movss [rbp+0x4A8],xmm12                       
0x677748e  lea rcx,[rbp+0x2C0]                           
0x6777495  mov rdx,r13                                   
0x6777498  call 0x678CF10                                ; -> sub_678cf10
0x677749d  nop                                           
0x677749e  lea rax,[rbp+0x4A0]                           
0x67774a5  mov [rsp+0x20],rax                            
0x67774aa  lea r14,[rbp+0x110]                           
0x67774b1  mov rcx,r14                                   
0x67774b4  lea rdx,[rbp+0x3E0]                           
0x67774bb  lea r8,[rbp+0x388]                            
0x67774c2  mov r9,r13                                    
0x67774c5  call 0x678E1D0                                ; -> sub_678e1d0
0x67774ca  nop                                           
```

Interpretation: [rbp+0x4A0]=low64(xmm15), [rbp+0x4A8]=low32(xmm12). rcx=&[rbp+0x2C0], rdx=r13 (&[rbp+0x300]). Call 0x678CF10. [rsp+0x20]=&[rbp+0x4A0]. r14=&[rbp+0x110]. Call 0x678E1D0(rcx=r14, rdx=&[rbp+0x3E0], r8=&[rbp+0x388], r9=r13).

Callees: 0x678CF10 (sub_678cf10), 0x678E1D0 (sub_678e1d0).
Fields read: xmm15, xmm12, [rbp+0x2C0], r13, [rbp+0x110], [rbp+0x3E0], [rbp+0x388]. Fields written: [rbp+0x4A0], [rbp+0x4A8], [rsp+0x20].

---

## Phase 5 — Copy [rcx+0x68..0x9F] to [rbx+0x78..0xAF] + save [rbp+0x44C] and u16 [rbp+0x490] (0x67774cb..0x677752c)

Copies fields from [rbp+0x3E0] struct to [rbx+0x78..0xAF], saves byte and u16 locals.

```
0x67774cb  lea rcx,[rbp+0x3E0]                           
0x67774d2  mov eax,[rcx+0x68]                            
0x67774d5  mov [rbx+0x78],eax                            
0x67774d8  movups xmm0,[rcx+0x58]                        
0x67774dc  movups [rbx+0x68],xmm0                        
0x67774e0  movzx eax,byte ptr [rbp+0x44C]                
0x67774e7  mov [rbp+0x26C],al                            
0x67774ed  movups xmm0,[rbp+0x450]                       
0x67774f4  movups [rbp+0x270],xmm0                       
0x67774fb  movups xmm0,[rcx+0x80]                        
0x6777502  movups xmm1,[rcx+0x90]                        
0x6777509  movups xmm2,[rcx+0x9F]                        
0x6777510  movups [rbx+0xAF],xmm2                        
0x6777517  movups [rbx+0xA0],xmm1                        
0x677751e  movups [rbx+0x90],xmm0                        
0x6777525  movzx eax,word ptr [rbp+0x490]                
0x677752c  mov [rbp+0x2B0],ax                            
```

Interpretation: rcx=&[rbp+0x3E0]. eax=[rcx+0x68] stored at [rbx+0x78]. xmm0=[rcx+0x58] stored at [rbx+0x68]. al=byte [rbp+0x44C] stored at [rbp+0x26C]. xmm0=[rbp+0x450] stored at [rbp+0x270]. xmm0=[rcx+0x80], xmm1=[rcx+0x90], xmm2=[rcx+0x9F]. Store xmm2 at [rbx+0xAF], xmm1 at [rbx+0xA0], xmm0 at [rbx+0x90]. ax=word [rbp+0x490] stored at [rbp+0x2B0].

Callees: none.
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x44C], [rbp+0x450], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x490]. Fields written: [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0xAF], [rbx+0xA0], [rbx+0x90], [rbp+0x2B0].

---

## Phase 6 — Call 0x67E23F0 + call 0x678E420 (0x6777533..0x677755e)

Calls 0x67E23F0 with r13, then 0x678E420 with output pointers.

```
0x6777533  mov rcx,r13                                   
0x6777536  call 0x67E23F0                                ; -> sub_67e23f0
0x677753b  nop                                           
0x677753c  mov [rsp+0x20],r14                            
0x6777541  mov rcx,r12                                   
0x6777544  lea rdx,[rbp+0x200]                           
0x677754b  lea r8,[rbp+0x1A8]                            
0x6777552  lea r9,[rbp+0x120]                            
0x6777559  call 0x678E420                                ; -> sub_678e420
0x677755e  nop                                           
```

Interpretation: rcx=r13 (&[rbp+0x300]). Call 0x67E23F0. [rsp+0x20]=r14. rcx=r12 (&[rbp+0x570]). rdx=&[rbp+0x200]. r8=&[rbp+0x1A8]. r9=&[rbp+0x120]. Call 0x678E420.

Callees: 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420).
Fields read: none (registers only). Fields written: [rsp+0x20].

---

## Phase 7 — Copy [rbx+0x78..0xAF] to [rbp+0x6B8..0x710] + save u16 [rbp+0x2B0] (0x677755f..0x67775be)

Copies fields from [rbx+0x78..0xAF] to [rbp+0x6B8..] region, saves u16 at [rbp+0x710].

```
0x677755f  mov eax,[rbx+0x78]                            
0x6777562  lea r8,[rbp+0x6B8]                            
0x6777569  mov [r8+0x10],eax                             
0x677756d  movups xmm0,[rbx+0x68]                        
0x6777571  movups [r8],xmm0                              
0x6777575  movzx eax,byte ptr [rbp+0x26C]                
0x677757c  mov [rbp+0x6CC],al                            
0x6777582  movups xmm0,[rbp+0x270]                       
0x6777589  movups [rbp+0x6D0],xmm0                       
0x6777590  movups xmm0,[rbx+0x90]                        
0x6777597  movups xmm1,[rbx+0xA0]                        
0x677759e  movups xmm2,[rbx+0xAF]                        
0x67775a5  lea rax,[rbp+0x6E0]                           
0x67775ac  movups [rax+0x1F],xmm2                        
0x67775b0  movups [rax+0x10],xmm1                        
0x67775b4  movups [rax],xmm0                             
0x67775b7  movzx eax,word ptr [rbp+0x2B0]                
0x67775be  mov [rbp+0x710],ax                            
```

Interpretation: eax=[rbx+0x78] stored at [r8+0x10]=[rbp+0x6C8]. xmm0=[rbx+0x68] stored at [r8]=[rbp+0x6B8]. al=byte [rbp+0x26C] stored at [rbp+0x6CC]. xmm0=[rbp+0x270] stored at [rbp+0x6D0]. xmm0=[rbx+0x90], xmm1=[rbx+0xA0], xmm2=[rbx+0xAF]. rax=&[rbp+0x6E0]. Store xmm2 at [rax+0x1F]=[rbp+0x6FF], xmm1 at [rax+0x10]=[rbp+0x6F0], xmm0 at [rax]=[rbp+0x6E0]. ax=word [rbp+0x2B0] stored at [rbp+0x710].

Callees: none.
Fields read: [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0x90], [rbx+0xA0], [rbx+0xAF], [rbp+0x2B0]. Fields written: [rbp+0x6C8], [rbp+0x6B8], [rbp+0x6CC], [rbp+0x6D0], [rbp+0x6FF], [rbp+0x6F0], [rbp+0x6E0], [rbp+0x710].

---

## Phase 8 — Call 0x5ABA5C0 + setup stack args + call 0x678E670 + 0x67E1660 + jump 0x677B130 (0x67775c5..0x6777618)

Calls 0x5ABA5C0 to get pass object, sets up stack args, calls 0x678E670 then 0x67E1660, jumps to 0x677B130.

```
0x67775c5  mov rax,[rbp+0x828]                           
0x67775cc  mov rcx,[rax+0x10]                            
0x67775d0  mov eax,0x9D0                                 
0x67775d5  add rcx,rax                                   
0x67775d8  lea rax,[rbp+0x574]                           
0x67775df  mov [rsp+0x30],rax                            
0x67775e4  lea rax,[rbp+0x580]                           
0x67775eb  mov [rsp+0x28],rax                            
0x67775f0  lea rax,[rbp+0x608]                           
0x67775f7  mov [rsp+0x20],rax                            
0x67775fc  lea rdx,[rbp+0x710]                           
0x6777603  lea r9,[rbp+0x660]                            
0x677760a  call 0x678E670                                ; -> sub_678e670
0x677760f  nop                                           
0x6777610  mov rcx,r12                                   
0x6777613  call 0x67E1660                                ; -> sub_67e1660
0x6777618  jmp 0x677B130                                 ; -> sub_677b130
```

Interpretation: rax=[rbp+0x828] (BuilderSpan*), rcx=[rax+0x10], rcx+=0x9D0. [rsp+0x30]=&[rbp+0x574], [rsp+0x28]=&[rbp+0x580], [rsp+0x20]=&[rbp+0x608]. rdx=&[rbp+0x710], r9=&[rbp+0x660]. Call 0x678E670(rcx, rdx, r8, r9, [rsp+0x20], [rsp+0x28], [rsp+0x30]). Then rcx=r12, call 0x67E1660. Jump to 0x677B130.

Callees: 0x678E670 (sub_678e670), 0x67E1660 (sub_67e1660).
Fields read: [rbp+0x828], [rax+0x10]. Fields written: [rsp+0x30], [rsp+0x28], [rsp+0x20].

---

## Phase 9 — test al,2 / test al,1 / [rbp+0x836] check + conditional calls 0x678CF10, 0x678F640 (0x677761d..0x6777667)

Tests al bits, checks [rbp+0x836], conditionally calls 0x678CF10 and 0x678F640.

```
0x677761d  test al,2                                     
0x677761f  jne 0x677AA9C                                 ; -> sub_677aa9c
0x6777625  test al,1                                     
0x6777627  je 0x677B13C                                  ; -> sub_677b13c
0x677762d  cmp byte ptr [rbp+0x836],0                    
0x6777634  je 0x677B14E                                  ; -> sub_677b14e
0x677763a  lea rcx,[rbp+0x2C0]                           
0x6777641  mov rdx,r13                                   
0x6777644  call 0x678CF10                                ; -> sub_678cf10
0x6777649  nop                                           
0x677764a  lea rcx,[rbp+0x110]                           
0x6777651  lea rdx,[rbp+0x3E0]                           
0x6777658  lea r8,[rbp+0x388]                            
0x677765f  mov r9,r13                                    
0x6777662  call 0x678F640                                ; -> sub_678f640
0x6777667  nop                                           
```

Interpretation: test al,2; if nonzero jump to 0x677AA9C. test al,1; if zero jump to 0x677B13C. cmp byte [rbp+0x836],0; if zero jump to 0x677B14E. Otherwise: rcx=&[rbp+0x2C0], rdx=r13. Call 0x678CF10. Then rcx=&[rbp+0x110], rdx=&[rbp+0x3E0], r8=&[rbp+0x388], r9=r13. Call 0x678F640.

Callees: 0x678CF10 (sub_678cf10), 0x678F640 (sub_678f640).
Fields read: [rbp+0x836], [rbp+0x2C0], r13, [rbp+0x110], [rbp+0x3E0], [rbp+0x388]. Fields written: none.

---

## Phase 10 — Copy [rcx+0x68..0x9F] to [rbp+0x250..] + save byte/u16 locals (0x6777668..0x67776cf)

Copies from [rbp+0x3E0] to [rbp+0x250..] and [rbx+0x88..0xA7], saves byte [rbp+0x44C] and u16 [rbp+0x490].

```
0x6777668  lea rcx,[rbp+0x3E0]                           
0x677766f  mov eax,[rcx+0x68]                            
0x6777672  lea rdx,[rbp+0x250]                           
0x6777679  mov [rdx+0x10],eax                            
0x677767c  movups xmm0,[rcx+0x58]                        
0x6777680  movups [rdx],xmm0                             
0x6777683  movzx eax,byte ptr [rbp+0x44C]                
0x677768a  mov [rbp+0x264],al                            
0x6777690  movups xmm0,[rbp+0x450]                       
0x6777697  movups [rbp+0x268],xmm0                       
0x677769e  movups xmm0,[rcx+0x80]                        
0x67776a5  movups xmm1,[rcx+0x90]                        
0x67776ac  movups xmm2,[rcx+0x9F]                        
0x67776b3  movups [rbx+0xA7],xmm2                        
0x67776ba  movups [rbx+0x98],xmm1                        
0x67776c1  movups [rbx+0x88],xmm0                        
0x67776c8  movzx eax,word ptr [rbp+0x490]                
0x67776cf  mov [rbp+0x2A8],ax                            
```

Interpretation: rcx=&[rbp+0x3E0]. eax=[rcx+0x68] stored at [rdx+0x10]=[rbp+0x260]. xmm0=[rcx+0x58] stored at [rdx]=[rbp+0x250]. al=byte [rbp+0x44C] stored at [rbp+0x264]. xmm0=[rbp+0x450] stored at [rbp+0x268]. xmm0=[rcx+0x80], xmm1=[rcx+0x90], xmm2=[rcx+0x9F]. Store xmm2 at [rbx+0xA7], xmm1 at [rbx+0x98], xmm0 at [rbx+0x88]. ax=word [rbp+0x490] stored at [rbp+0x2A8].

Callees: none.
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x44C], [rbp+0x450], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x490]. Fields written: [rbp+0x260], [rbp+0x250], [rbp+0x264], [rbp+0x268], [rbx+0xA7], [rbx+0x98], [rbx+0x88], [rbp+0x2A8].

---

## Phase 11 — Range check on [rbp+0x768]+0x480/0x488 + call 0x6769EE0 (0x67776d6..0x6777758)

Computes difference of [rbp+0x768]+0x480/+0x488, range-checks, divides by 15 via magic multiply, calls 0x6769EE0.

```
0x67776d6  mov rax,[rbp+0x768]                           
0x67776dd  mov r8,[rax+0x480]                            
0x67776e4  mov rax,[rax+0x488]                           
0x67776eb  mov rdx,rax                                   
0x67776ee  sub rdx,r8                                    
0x67776f1  cmp rdx,0xFFFFFFFFFFFFFFD0                    
0x67776f5  je 0x677E011                                  ; -> sub_677e011
0x67776fb  test r8,r8                                    
0x67776fe  setne cl                                      
0x6777701  test rax,rax                                  
0x6777704  sete r9b                                      
0x6777708  or r9b,cl                                     
0x677770b  je 0x677E011                                  ; -> sub_677e011
0x6777711  cmp rax,r8                                    
0x6777714  je 0x677D069                                  ; -> sub_677d069
0x677771a  mov rax,[rbp+0x778]                           
0x6777721  cmp qword ptr [rax],0                         
0x6777725  je 0x677D069                                  ; -> sub_677d069
0x677772b  sar rdx,4                                     
0x677772f  mov rax,0xAAAAAAAAAAAAAAAB                    
0x6777739  imul rdx,rax                                  
0x677773d  mov dword ptr [rsp+0x20],0x41800000           
0x6777745  lea rcx,[rbp+0x800]                           
0x677774c  lea r9,[rbp+0x2E0]                            
0x6777753  call 0x6769EE0                                ; -> sub_6769ee0
0x6777758  nop                                           
```

Interpretation: rax=[rbp+0x768], r8=[rax+0x480], rax=[rax+0x488], rdx=rax, rdx-=r8. If difference==0xFFFFFFD0, jump to 0x677E011. test r8,r8 -> setne cl. test rax,rax -> sete r9b. or r9b,cl. If 0, jump to 0x677E011. cmp rax,r8; if equal jump to 0x677D069. rax=[rbp+0x778]; if [rax]==0 jump to 0x677D069. sar rdx,4 (div by 16). imul rdx, 0xAAAAAAAAAAAAAAAB (magic div by 15). [rsp+0x20]=0x41800000 (float 31.0). rcx=&[rbp+0x800], r9=&[rbp+0x2E0]. Call 0x6769EE0.

Callees: 0x6769EE0 (sub_6769ee0).
Fields read: [rbp+0x768], [rax+0x480], [rax+0x488], [rbp+0x778], [rax]. Fields written: [rsp+0x20].

---

## Phase 12 — Load [rbp+0x800]/[rbp+0x808] + call vtable [0xF99FFA0] + bounds checks (0x6777759..0x67777e0)

Loads [rbp+0x800] and [rbp+0x808], stores in r14/r15, calls vtable function, performs multiple bounds checks.

```
0x6777759  mov rax,[rbp+0x800]                           
0x6777760  mov rcx,[rbp+0x808]                           
0x6777767  mov r14,rax                                   
0x677776a  mov [rbp+0x838],rax                           
0x6777771  mov [rbp+0x568],rcx                           
0x6777778  cmp rax,rcx                                   
0x677777b  je 0x677CFD6                                  ; -> sub_677cfd6
0x6777781  mov rax,[rbp+0x778]                           
0x6777788  mov rcx,[rax]                                 
0x677778b  mov rax,[rcx]                                 
0x677778e  mov rax,[rax+0x48]                            
0x6777792  lea rdx,[rbp+0x4A0]                           
0x6777799  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677779f  nop                                           
0x67777a0  mov r14,[rbp+0x800]                           
0x67777a7  mov r15,[rbp+0x808]                           
0x67777ae  mov rax,r15                                   
0x67777b1  sub rax,r14                                   
0x67777b4  cmp rax,0xFFFFFFFFFFFFFFE0                    
0x67777b8  je 0x677E011                                  ; -> sub_677e011
0x67777be  test r14,r14                                  
0x67777c1  setne al                                      
0x67777c4  test r15,r15                                  
0x67777c7  sete cl                                       
0x67777ca  or cl,al                                      
0x67777cc  je 0x677E011                                  ; -> sub_677e011
0x67777d2  test r14,r14                                  
0x67777d5  setne al                                      
0x67777d8  cmp r15,r14                                   
0x67777db  sete cl                                       
0x67777de  or cl,al                                      
0x67777e0  je 0x677E011                                  ; -> sub_677e011
```

Interpretation: rax=[rbp+0x800], rcx=[rbp+0x808], r14=rax, [rbp+0x838]=rax, [rbp+0x568]=rcx. If rax==rcx jump to 0x677CFD6. rax=[rbp+0x778], rcx=[rax], rax=[rcx], rax=[rax+0x48] (vtable+0x48). rdx=&[rbp+0x4A0]. Call via [0xF99FFA0]. r14=[rbp+0x800], r15=[rbp+0x808]. rax=r15-r14. If rax==0xFFFFFFE0 (-32), jump to 0x677E011. test r14,r14 -> setne al. test r15,r15 -> sete cl. or cl,al. If 0 jump to 0x677E011. test r14,r14 -> setne al. cmp r15,r14 -> sete cl. or cl,al. If 0 jump to 0x677E011.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, vtable+0x48).
Fields read: [rbp+0x800], [rbp+0x808], [rbp+0x778], [rax], [rcx], [rax+0x48], [rbp+0x4A0]. Fields written: [rbp+0x838], [rbp+0x568].

---

## Phase 13 — Setup loop region [rbp+0x7D0..0x7C8] + loop calling 0x676A670 (0x67777e6..0x677782a)

Sets up [rbp+0x7C0]=[rbp+0x7D0], [rbp+0x7C8]=0x100000000, loops r14 from current to r15 calling 0x676A670.

```
0x67777e6  lea rax,[rbp+0x7D0]                           
0x67777ed  mov [rbp+0x7C0],rax                           
0x67777f4  mov rax,0x100000000                           
0x67777fe  mov [rbp+0x7C8],rax                           
0x6777805  cmp r15,r14                                   
0x6777808  je short 0x677782C                            ; -> loc_677782c
0x677780a  nop [rax+rax]                                 

loc_6777810:  ; from 677782a
0x6777810  lea rcx,[rbp+0x7C0]                           
0x6777817  mov rdx,r12                                   
0x677781a  mov r8,r14                                    
0x677781d  call 0x676A670                                ; -> sub_676a670
0x6777822  nop                                           
0x6777823  add r14,0x20                                  
0x6777827  cmp r14,r15                                   
0x677782a  jne short 0x6777810                           ; -> loc_6777810
```

Interpretation: rax=&[rbp+0x7D0], [rbp+0x7C0]=rax, rax=0x100000000, [rbp+0x7C8]=rax. If r15==r14 jump to loc_677782c. Loop: rcx=&[rbp+0x7C0], rdx=r12, r8=r14. Call 0x676A670. r14+=0x20. If r14!=r15, loop.

Callees: 0x676A670 (sub_676a670).
Fields read: r15, r14, r12. Fields written: [rbp+0x7C0], [rbp+0x7C8].

---

## Phase 14 — Setup second loop region + call 0x6764990 + call 0x6792980 (0x677782c..0x6777884)

Sets up [rbp+0x780..0x788], calls 0x6764990 then 0x6792980.

```
loc_677782c:  ; from 6777808
0x677782c  lea rax,[rbp+0x790]                           
0x6777833  mov [rbp+0x780],rax                           
0x677783a  mov rax,0x100000000                           
0x6777844  mov [rbp+0x788],rax                           
0x677784b  lea r14,[rbp+0x780]                           
0x6777852  mov rcx,r14                                   
0x6777855  lea rdx,[rbp+0x7C0]                           
0x677785c  call 0x6764990                                ; -> sub_6764990
0x6777861  nop                                           
0x6777862  mov [rsp+0x20],r14                            
0x6777867  mov rcx,r12                                   
0x677786a  lea rdx,[rbp+0x1F8]                           
0x6777871  lea r8,[rbp+0x1A0]                            
0x6777878  lea r9,[rbp+0x118]                            
0x677787f  call 0x6792980                                ; -> sub_6792980
0x6777884  nop                                           
```

Interpretation: rax=&[rbp+0x790], [rbp+0x780]=rax, rax=0x100000000, [rbp+0x788]=rax. r14=&[rbp+0x780]. Call 0x6764990(rcx=r14, rdx=&[rbp+0x7C0]). [rsp+0x20]=r14. Call 0x6792980(rcx=r12, rdx=&[rbp+0x1F8], r8=&[rbp+0x1A0], r9=&[rbp+0x118]).

Callees: 0x6764990 (sub_6764990), 0x6792980 (sub_6792980).
Fields read: [rbp+0x780], [rbp+0x788], [rbp+0x7C0], [rbp+0x1F8], [rbp+0x1A0], [rbp+0x118]. Fields written: [rbp+0x780], [rbp+0x788], [rsp+0x20].

---

## Phase 15 — Copy [rcx+0x10..0x9F] from [rbp+0x250] to [rbp+0x6E0..] + save byte/u16 locals (0x6777885..0x67778f2)

Copies from [rbp+0x250] struct to [rbp+0x6E0..] region, saves byte [rbp+0x264] and u16 [rbp+0x2A8].

```
0x6777885  lea rcx,[rbp+0x250]                           
0x677788c  mov eax,[rcx+0x10]                            
0x677788f  lea rdx,[rbp+0x6E0]                           
0x6777896  mov [rdx+0x10],eax                            
0x6777899  movups xmm0,[rcx]                             
0x677789c  movups [rdx],xmm0                             
0x677789f  movzx eax,byte ptr [rbp+0x264]                
0x67778a6  mov [rbp+0x6F4],al                            
0x67778ac  movups xmm0,[rbp+0x268]                       
0x67778b3  movups [rbp+0x6F8],xmm0                       
0x67778ba  movups xmm0,[rbx+0x88]                        
0x67778c1  movups xmm1,[rbx+0x98]                        
0x67778c8  movups xmm2,[rbx+0xA7]                        
0x67778cf  lea rax,[rbp+0x574]                           
0x67778d6  movups [rax+0x1B3],xmm2                       
0x67778dd  movups [rax+0x1A4],xmm1                       
0x67778e4  movups [rax+0x194],xmm0                       
0x67778eb  movzx eax,word ptr [rbp+0x2A8]                
0x67778f2  mov [rbp+0x738],ax                            
```

Interpretation: rcx=&[rbp+0x250]. eax=[rcx+0x10] stored at [rdx+0x10]=[rbp+0x6F0]. xmm0=[rcx] stored at [rdx]=[rbp+0x6E0]. al=byte [rbp+0x264] stored at [rbp+0x6F4]. xmm0=[rbp+0x268] stored at [rbp+0x6F8]. xmm0=[rbx+0x88], xmm1=[rbx+0x98], xmm2=[rbx+0xA7]. rax=&[rbp+0x574]. Store xmm2 at [rax+0x1B3]=[rbp+0x727], xmm1 at [rax+0x1A4]=[rbp+0x718], xmm0 at [rax+0x194]=[rbp+0x708]. ax=word [rbp+0x2A8] stored at [rbp+0x738].

Callees: none.
Fields read: [rcx+0x10], [rcx], [rbp+0x264], [rbp+0x268], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x2A8]. Fields written: [rbp+0x6F0], [rbp+0x6E0], [rbp+0x6F4], [rbp+0x6F8], [rbp+0x727], [rbp+0x718], [rbp+0x708], [rbp+0x738].

---

## Phase 16 — Call 0x5ABA5C0 + zero xmm regs [rbp+0x4A0..0x560] (0x67778f9..0x6777969)

Calls 0x5ABA5C0 to get pass object, zeros xmm registers [rbp+0x4A0..0x560].

```
0x67778f9  mov rax,[rbp+0x828]                           
0x6777900  mov rcx,[rax+0x10]                            
0x6777904  mov eax,0x9D0                                 
0x6777909  add rcx,rax                                   
0x677790c  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6777911  nop                                           
0x6777912  mov r14,rax                                   
0x6777915  movaps [rbp+0x550],xmm6                       
0x677791c  movaps [rbp+0x540],xmm6                       
0x6777923  movaps [rbp+0x530],xmm6                       
0x677792a  movaps [rbp+0x520],xmm6                       
0x6777931  movaps [rbp+0x510],xmm6                       
0x6777938  movaps [rbp+0x500],xmm6                       
0x677793f  movaps [rbp+0x4F0],xmm6                       
0x6777946  movaps [rbp+0x4E0],xmm6                       
0x677794d  movaps [rbp+0x4D0],xmm6                       
0x6777954  movaps [rbp+0x4C0],xmm6                       
0x677795b  movaps [rbp+0x4B0],xmm6                       
0x6777962  movaps [rbp+0x4A0],xmm6                       
0x6777969  mov qword ptr [rbp+0x560],0                   
```

Interpretation: rax=[rbp+0x828] (BuilderSpan*), rcx=[rax+0x10], rcx+=0x9D0. Call 0x5ABA5C0(rcx). Result in r14 (pass object). Zero xmm6 into [rbp+0x550], [rbp+0x540], [rbp+0x530], [rbp+0x520], [rbp+0x510], [rbp+0x500], [rbp+0x4F0], [rbp+0x4E0], [rbp+0x4D0], [rbp+0x4C0], [rbp+0x4B0], [rbp+0x4A0]. [rbp+0x560]=0.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x828], [rax+0x10], xmm6. Fields written: [rbp+0x550], [rbp+0x540], [rbp+0x530], [rbp+0x520], [rbp+0x510], [rbp+0x500], [rbp+0x4F0], [rbp+0x4E0], [rbp+0x4D0], [rbp+0x4C0], [rbp+0x4B0], [rbp+0x4A0], [rbp+0x560].

---

## Phase 17 — TLS/cookie read + feature flag [rbp+0x847] + shared_ptr items write (0x6777974..0x67779b7)

Reads TLS via [0xF99FFA0] with dl=0x4A, stores at [rbp+0x847], writes u16 [rbp+0x738] to pass items buffer.

```
0x6777974  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677797b  mov rax,[rcx]                                 
0x677797e  mov rax,[rax+0x10]                            
0x6777982  mov dl,0x4A                                   
0x6777984  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677798a  nop                                           
0x677798b  mov [rbp+0x847],al                            
0x6777991  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6777998  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x677799f  je 0x677C39A                                  ; -> sub_677c39a
0x67779a5  movzx eax,word ptr [rbp+0x738]                
0x67779ac  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x67779af  add qword ptr [r14+0x8A8],2                   
0x67779b7  jmp 0x677C3AE                                 ; -> sub_677c3ae
```

Interpretation: rcx=[0x1233E1B0] (TLS base). rax=[rcx], rax=[rax+0x10]. dl=0x4A. Call via [0xF99FFA0] (sub_eea6040). [rbp+0x847]=al (feature flag). rdx=[r14+0x8A8] (items write cursor). Compare with [r14+0x8B0] (items end). If equal jump to 0x677C39A (grow). Otherwise: eax=word [rbp+0x738], store ax at [rdx] (write u16 to items buffer), [r14+0x8A8]+=2. Jump to 0x677C3AE.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x738]. Fields written: [rbp+0x847], [rdx] (items buffer), [r14+0x8A8].

---

## Phase 18 — Shared_ptr refcount path at 0x67779bc (0x67779bc..0x6777a3b)

Sets up [rbp+0x780..0x7A4] from locals, refcounts [rsi+0xD0] if non-null, stores [rsi+0xC8] at [rbp+0x7C0].

```
0x67779bc  xor edx,edx                                   
0x67779be  mov rcx,[rbp+0x2F0]                           
0x67779c5  mov [rbp+0x780],rcx                           
0x67779cc  mov [rbp+0x788],rdx                           
0x67779d3  mov ecx,[rbp+0x824]                           
0x67779d9  mov [rbp+0x790],ecx                           
0x67779df  mov ecx,[rbp+0x820]                           
0x67779e5  mov [rbp+0x794],ecx                           
0x67779eb  mov ecx,[rbp+0x774]                           
0x67779f1  mov [rbp+0x798],ecx                           
0x67779f7  mov rcx,0x100000000                           
0x6777a01  mov [rbp+0x79C],rcx                           
0x6777a08  mov dword ptr [rbp+0x7A4],1                   
0x6777a12  movaps [rbp+0x7C0],xmm6                       
0x6777a19  mov rcx,[rsi+0xD0]                            
0x6777a20  test rcx,rcx                                  
0x6777a23  je 0x6777ABA                                  ; -> loc_6777aba
0x6777a29  lock inc dword ptr [rcx+8]                    
0x6777a2d  mov rcx,[rsi+0xD0]                            
0x6777a34  mov rdx,[rbp+0x788]                           
0x6777a3b  jmp short 0x6777ABC                           ; -> loc_6777abc
```

Interpretation: edx=0. rcx=[rbp+0x2F0], [rbp+0x780]=rcx, [rbp+0x788]=rdx (0). ecx=[rbp+0x824] -> [rbp+0x790]. ecx=[rbp+0x820] -> [rbp+0x794]. ecx=[rbp+0x774] -> [rbp+0x798]. rcx=0x100000000 -> [rbp+0x79C]. [rbp+0x7A4]=1. [rbp+0x7C0]=xmm6 (zero). rcx=[rsi+0xD0]. If rcx==0 jump to loc_6777aba. Otherwise lock inc dword [rcx+8] (shared_ptr refcount). rcx=[rsi+0xD0], rdx=[rbp+0x788]. Jump to loc_6777abc.

Callees: none.
Fields read: [rbp+0x2F0], [rbp+0x824], [rbp+0x820], [rbp+0x774], [rsi+0xD0], [rcx+8]. Fields written: [rbp+0x780], [rbp+0x788], [rbp+0x790], [rbp+0x794], [rbp+0x798], [rbp+0x79C], [rbp+0x7A4], [rbp+0x7C0], [rcx+8].

---

## Phase 19 — loc_6777aba / loc_6777abc: store [rsi+0xC8] at [rbp+0x7C0] + setup [rbp+0x7D0] (0x6777aba..0x6777b1a)

Handles null [rsi+0xD0], stores [rsi+0xC8] and rcx at [rbp+0x7C0/0x7C8], zeros [rbp+0x7D0], refcounts rdx if non-null.

```
loc_6777aba:  ; from 6777a23
0x6777aba  xor ecx,ecx                                   

loc_6777abc:  ; from 6777a3b
0x6777abc  mov r8,[rsi+0xC8]                             
0x6777ac3  mov [rbp+0x7C0],r8                            
0x6777aca  mov [rbp+0x7C8],rcx                           
0x6777ad1  lea r8,[rbp+0x7D0]                            
0x6777ad8  movups [r8],xmm6                              
0x6777adc  test rdx,rdx                                  
0x6777adf  je short 0x6777B30                            ; -> loc_6777b30
0x6777ae1  lock inc dword ptr [rdx+8]                    
0x6777ae5  mov rdx,[rbp+0x788]                           
0x6777aec  mov rcx,[rbp+0x7C8]                           
0x6777af3  jmp short 0x6777B32                           ; -> loc_6777b32

loc_6777af5:  ; from 6777aa4
0x6777af5  xor ecx,ecx                                   

loc_6777af7:  ; from 6777ab8
0x6777af7  mov r8,[rsi+0xC8]                             
0x6777afe  mov [rbp+0x7C0],r8                            
0x6777b05  mov [rbp+0x7C8],rcx                           
0x6777b0c  lea r8,[rbp+0x7D0]                            
0x6777b13  movups [r8],xmm6                              
0x6777b17  test rdx,rdx                                  
0x6777b1a  je short 0x6777B86                            ; -> loc_6777b86
```

Interpretation: loc_6777aba: ecx=0. loc_6777abc: r8=[rsi+0xC8], [rbp+0x7C0]=r8, [rbp+0x7C8]=rcx. r8=&[rbp+0x7D0], [r8]=xmm6 (zero 16 bytes). test rdx,rdx; if zero jump to loc_6777b30. Otherwise lock inc dword [rdx+8]. rdx=[rbp+0x788], rcx=[rbp+0x7C8]. Jump to loc_6777b32.

loc_6777af5: ecx=0 (alternate null path). loc_6777af7: same pattern - r8=[rsi+0xC8], [rbp+0x7C0]=r8, [rbp+0x7C8]=rcx, [rbp+0x7D0]=0, test rdx,rdx; if zero jump to loc_6777b86.

Callees: none.
Fields read: [rsi+0xD0], [rsi+0xC8], [rbp+0x788], [rbp+0x7C8], [rdx+8]. Fields written: [rbp+0x7C0], [rbp+0x7C8], [rbp+0x7D0], [rdx+8].

---

## Phase 20 — loc_6777b30 / loc_6777b32: store [rbp+0x780] at [rbp+0x7D0], refcount rcx, setup xmm store (0x6777b30..0x6777bc3)

Stores [rbp+0x780] at [rbp+0x7D0], [rbp+0x7D8]=rdx, builds 16-byte struct at [rbp+0x7D0..0x7DF], refcounts rcx if non-null, stores xmm0 at [rbp+0x4A0].

```
loc_6777b30:  ; from 6777adf
0x6777b30  xor edx,edx                                   

loc_6777b32:  ; from 6777af3
0x6777b32  mov r8,[rbp+0x780]                            
0x6777b39  mov [rbp+0x7D0],r8                            
0x6777b40  mov [rbp+0x7D8],rdx                           
0x6777b47  lea r10,[rbp+0x790]                           
0x6777b4e  mov r8,[r10+0x10]                             
0x6777b52  lea r9,[rbp+0x7D0]                            
0x6777b59  mov [r9+0x20],r8                              
0x6777b5d  movups xmm0,[r10]                             
0x6777b61  movups [r9+0x10],xmm0                         
0x6777b66  movaps [rbp+0x4A0],xmm6                       
0x6777b6d  test rcx,rcx                                  
0x6777b70  je short 0x6777BDC                            ; -> loc_6777bdc
0x6777b72  lock inc dword ptr [rcx+8]                    
0x6777b76  mov rcx,[rbp+0x7C8]                           
0x6777b7d  mov rdx,[rbp+0x7D8]                           
0x6777b84  jmp short 0x6777BDE                           ; -> loc_6777bde

loc_6777b86:  ; from 6777b1a
0x6777b86  xor edx,edx                                   

loc_6777b88:  ; from 6777b2e
0x6777b88  mov r8,[rbp+0x780]                            
0x6777b8f  mov [rbp+0x7D0],r8                            
0x6777b96  mov [rbp+0x7D8],rdx                           
0x6777b9d  lea r10,[rbp+0x790]                           
0x6777ba4  mov r8,[r10+0x10]                             
0x6777ba8  lea r9,[rbp+0x7D0]                            
0x6777baf  mov [r9+0x20],r8                              
0x6777bb3  movups xmm0,[r10]                             
0x6777bb7  movups [r9+0x10],xmm0                         
0x6777bbc  movaps [rbp+0x4A0],xmm6                       
0x6777bc3  test rcx,rcx                                  
```

Interpretation: loc_6777b30: edx=0. loc_6777b32: r8=[rbp+0x780], [rbp+0x7D0]=r8, [rbp+0x7D8]=rdx. r10=&[rbp+0x790]. r8=[r10+0x10] = [rbp+0x7A0]. r9=&[rbp+0x7D0]. [r9+0x20]=[rbp+0x7F0]=r8. xmm0=[r10] = 16 bytes at [rbp+0x790..0x79F], stored at [r9+0x10]=[rbp+0x7E0]. [rbp+0x4A0]=xmm6 (zero). test rcx,rcx; if zero jump to loc_6777bdc. Otherwise lock inc dword [rcx+8]. rcx=[rbp+0x7C8], rdx=[rbp+0x7D8]. Jump to loc_6777bde.

loc_6777b86: edx=0 (alternate). loc_6777b88: same pattern as b32 but jumps to loc_6777c10 if rcx==0 instead of bdc.

Callees: none.
Fields read: [rbp+0x780], [rbp+0x790], [rbp+0x7A0], [rbp+0x7C8], [rbp+0x7D8], rcx+8. Fields written: [rbp+0x7D0], [rbp+0x7D8], [rbp+0x7F0], [rbp+0x7E0], [rbp+0x4A0], [rcx+8].

---

## Phase 21 — loc_6777bdc / loc_6777bde / loc_6777c10 / loc_6777c12: store [rbp+0x7C0] at [rbp+0x4A0], [rbp+0x4A8]=rcx, setup [rbp+0x4A4], refcount rdx (0x6777bdc..0x6777c4e)

Stores [rbp+0x7C0] at [rbp+0x4A0], rcx at [rbp+0x4A8], zeros [rbp+0x4A4+0xC], refcounts rdx if non-null, stores r14=[rbp+0x7D8].

```
loc_6777bdc:  ; from 6777b70
0x6777bdc  xor ecx,ecx                                   

loc_6777bde:  ; from 6777b84
0x6777bde  mov r8,[rbp+0x7C0]                            
0x6777be5  mov [rbp+0x4A0],r8                            
0x6777bec  mov [rbp+0x4A8],rcx                           
0x6777bf3  lea rcx,[rbp+0x4A4]                           
0x6777bfa  movups [rcx+0xC],xmm6                         
0x6777bfe  test rdx,rdx                                  
0x6777c01  je short 0x6777C4B                            ; -> loc_6777c4b
0x6777c03  lock inc dword ptr [rdx+8]                    
0x6777c07  mov r14,[rbp+0x7D8]                           
0x6777c0e  jmp short 0x6777C4E                           ; -> loc_6777c4e

loc_6777c10:  ; from 6777bc6
0x6777c10  xor ecx,ecx                                   

loc_6777c12:  ; from 6777bda
0x6777c12  mov r8,[rbp+0x7C0]                            
0x6777c19  mov [rbp+0x4A0],r8                            
0x6777c20  mov [rbp+0x4A8],rcx                           
0x6777c27  lea rcx,[rbp+0x4A4]                           
0x6777c2e  movups [rcx+0xC],xmm6                         
0x6777c32  test rdx,rdx                                  
0x6777c35  je 0x6777ED5                                  ; -> loc_6777ed5
0x6777c3b  lock inc dword ptr [rdx+8]                    
0x6777c3f  mov r14,[rbp+0x7D8]                           
0x6777c46  jmp 0x6777ED8                                 ; -> loc_6777ed8

loc_6777c4b:  ; from 6777c01
0x6777c4b  xor r14d,r14d                                 

loc_6777c4e:  ; from 6777c0e
0x6777c4e  mov rcx,[rbp+0x7D0]                           
0x6777c55  mov [rbp+0x4B0],rcx                           
0x6777c5c  mov [rbp+0x4B8],r14                           
```

Interpretation: loc_6777bdc: ecx=0. loc_6777bde: r8=[rbp+0x7C0], [rbp+0x4A0]=r8, [rbp+0x4A8]=rcx. rcx=&[rbp+0x4A4], [rcx+0xC]=[rbp+0x4B0]=xmm6 (zero). test rdx,rdx; if zero jump to loc_6777c4b. Otherwise lock inc dword [rdx+8]. r14=[rbp+0x7D8]. Jump to loc_6777c4e.

loc_6777c10: ecx=0 (alternate). loc_6777c12: same pattern, but if rdx==0 jump to loc_6777ed5 instead of c4b.

loc_6777c4b: r14d=0 (xor). loc_6777c4e: rcx=[rbp+0x7D0], [rbp+0x4B0]=rcx, [rbp+0x4B8]=r14.

Callees: none.
Fields read: [rbp+0x7C0], rcx, [rbp+0x4A4], rdx, [rdx+8], [rbp+0x7D8], [rbp+0x7D0]. Fields written: [rbp+0x4A0], [rbp+0x4A8], [rbp+0x4B0], [rdx+8], [rbp+0x4B8], [rbp+0x4B0+...].

---

## Phase 22 — Store [rbp+0x4B0+0x2C] from [rbp+0x7D0+0x20], [rbp+0x4A4+0x1C] from [rbp+0x7D0+0x10], save [rbp+0x7BC] and ax at [rbp+0x4E0] (0x6777c5c..0x6777c8e)

Copies fields from [rbp+0x7D0] struct to [rbp+0x4A4] struct, saves [rbp+0x7BC] and ax.

```
0x6777c5c  mov [rbp+0x4B8],r14                           
0x6777c63  lea rdx,[rbp+0x7D0]                           
0x6777c6a  mov rcx,[rdx+0x20]                            
0x6777c6e  lea r8,[rbp+0x4A4]                            
0x6777c75  mov [r8+0x2C],rcx                             
0x6777c79  movups xmm0,[rdx+0x10]                        
0x6777c7d  movups [r8+0x1C],xmm0                         
0x6777c82  mov ecx,[rbp+0x7BC]                           
0x6777c88  mov [rbp+0x4D8],ecx                           
0x6777c8e  mov [rbp+0x4E0],ax                            
```

Interpretation: [rbp+0x4B8]=r14. rdx=&[rbp+0x7D0]. rcx=[rdx+0x20]=[rbp+0x7F0]. r8=&[rbp+0x4A4]. [r8+0x2C]=[rbp+0x4D0]=rcx. xmm0=[rdx+0x10]=[rbp+0x7E0], stored at [r8+0x1C]=[rbp+0x4C0]. ecx=[rbp+0x7BC], [rbp+0x4D8]=ecx. [rbp+0x4E0]=ax (lower 16 bits of eax from [rbp+0x7BC] load, zero-extended).

Callees: none.
Fields read: [rbp+0x7D0], [rdx+0x20], [rdx+0x10], [rbp+0x7BC]. Fields written: [rbp+0x4B8], [rbp+0x4D0], [rbp+0x4C0], [rbp+0x4D8], [rbp+0x4E0].

---

## Phase 23 — addss xmm12,xmm13 / addps xmm15,xmm14 + store to [rbp+0x800/0x808] + calls 0x678CF10, 0x678E1D0 (0x6777c95..0x6777ceb)

Adds xmm13 to xmm12, xmm14 to xmm15, stores to [rbp+0x800/0x808], calls 0x678CF10 and 0x678E1D0.

```
0x6777c95  addss xmm12,xmm13                             
0x6777c9a  addps xmm15,xmm14                             
0x6777c9e  movlps [rbp+0x800],xmm15                      
0x6777ca6  movss [rbp+0x808],xmm12                       
0x6777caf  lea rcx,[rbp+0x2C0]                           
0x6777cb6  mov rdx,r13                                   
0x6777cb9  call 0x678CF10                                ; -> sub_678cf10
0x6777cbe  nop                                           
0x6777cbf  lea rax,[rbp+0x800]                           
0x6777cc6  mov [rsp+0x20],rax                            
0x6777ccb  lea r15,[rbp+0x110]                           
0x6777cd2  mov rcx,r15                                   
0x6777cd5  lea rdx,[rbp+0x3E0]                           
0x6777cdc  lea r8,[rbp+0x388]                            
0x6777ce3  mov r9,r13                                    
0x6777ce6  call 0x678E1D0                                ; -> sub_678e1d0
0x6777ceb  nop                                           
```

Interpretation: xmm12 += xmm13 (addss). xmm15 += xmm14 (addps). [rbp+0x800]=low64(xmm15), [rbp+0x808]=low32(xmm12). rcx=&[rbp+0x2C0], rdx=r13. Call 0x678CF10. [rsp+0x20]=&[rbp+0x800]. r15=&[rbp+0x110]. Call 0x678E1D0(rcx=r15, rdx=&[rbp+0x3E0], r8=&[rbp+0x388], r9=r13).

Callees: 0x678CF10 (sub_678cf10), 0x678E1D0 (sub_678e1d0).
Fields read: xmm12, xmm13, xmm15, xmm14, [rbp+0x2C0], r13, [rbp+0x110], [rbp+0x3E0], [rbp+0x388]. Fields written: [rbp+0x800], [rbp+0x808], [rsp+0x20].

---

## Phase 24 — Copy [rcx+0x68..0x9F] from [rbp+0x3E0] to [rbx+0x78..0xAF] + save byte/u16 locals (0x6777cec..0x6777d4d)

Copies fields from [rbp+0x3E0] to [rbx+0x78..0xAF], saves byte [rbp+0x44C] and u16 [rbp+0x490].

```
0x6777cec  lea rcx,[rbp+0x3E0]                           
0x6777cf3  mov eax,[rcx+0x68]                            
0x6777cf6  mov [rbx+0x78],eax                            
0x6777cf9  movups xmm0,[rcx+0x58]                        
0x6777cfd  movups [rbx+0x68],xmm0                        
0x6777d01  movzx eax,byte ptr [rbp+0x44C]                
0x6777d08  mov [rbp+0x26C],al                            
0x6777d0e  movups xmm0,[rbp+0x450]                       
0x6777d15  movups [rbp+0x270],xmm0                       
0x6777d1c  movups xmm0,[rcx+0x80]                        
0x6777d23  movups xmm1,[rcx+0x90]                        
0x6777d2a  movups xmm2,[rcx+0x9F]                        
0x6777d31  movups [rbx+0xAF],xmm2                        
0x6777d38  movups [rbx+0xA0],xmm1                        
0x6777d3f  movups [rbx+0x90],xmm0                        
0x6777d46  movzx eax,word ptr [rbp+0x490]                
0x6777d4d  mov [rbp+0x2B0],ax                            
```

Interpretation: rcx=&[rbp+0x3E0]. eax=[rcx+0x68] stored at [rbx+0x78]. xmm0=[rcx+0x58] stored at [rbx+0x68]. al=byte [rbp+0x44C] stored at [rbp+0x26C]. xmm0=[rbp+0x450] stored at [rbp+0x270]. xmm0=[rcx+0x80], xmm1=[rcx+0x90], xmm2=[rcx+0x9F]. Store xmm2 at [rbx+0xAF], xmm1 at [rbx+0xA0], xmm0 at [rbx+0x90]. ax=word [rbp+0x490] stored at [rbp+0x2B0].

Callees: none.
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x44C], [rbp+0x450], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x490]. Fields written: [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0xAF], [rbx+0xA0], [rbx+0x90], [rbp+0x2B0].

---

## Phase 25 — Call 0x67E23F0 + setup stack args + call 0x6791420 (0x6777d54..0x6777da3)

Calls 0x67E23F0 with r13, sets up 4 stack args, calls 0x6791420.

```
0x6777d54  mov rcx,r13                                   
0x6777d57  call 0x67E23F0                                ; -> sub_67e23f0
0x6777d5c  nop                                           
0x6777d5d  lea rax,[rbp+0x4A0]                           
0x6777d64  mov [rsp+0x38],rax                            
0x6777d69  lea rax,[rbp+0x4D8]                           
0x6777d70  mov [rsp+0x30],rax                            
0x6777d75  lea rax,[rbp+0x4E0]                           
0x6777d7c  mov [rsp+0x28],rax                            
0x6777d81  mov [rsp+0x20],r15                            
0x6777d86  mov rcx,r12                                   
0x6777d89  lea rdx,[rbp+0x200]                           
0x6777d90  lea r8,[rbp+0x1A8]                            
0x6777d97  lea r9,[rbp+0x120]                            
0x6777d9e  call 0x6791420                                ; -> sub_6791420
0x6777da3  nop                                           
```

Interpretation: rcx=r13 (&[rbp+0x300]). Call 0x67E23F0. [rsp+0x38]=&[rbp+0x4A0], [rsp+0x30]=&[rbp+0x4D8], [rsp+0x28]=&[rbp+0x4E0], [rsp+0x20]=r15. rcx=r12, rdx=&[rbp+0x200], r8=&[rbp+0x1A8], r9=&[rbp+0x120]. Call 0x6791420(rcx, rdx, r8, r9, [rsp+0x20], [rsp+0x28], [rsp+0x30], [rsp+0x38]).

Callees: 0x67E23F0 (sub_67e23f0), 0x6791420 (sub_6791420).
Fields read: none (registers only). Fields written: [rsp+0x38], [rsp+0x30], [rsp+0x28], [rsp+0x20].

---

## Phase 26 — Copy [rbx+0x78..0xAF] to [rbp+0x700..] region + save byte/u16 locals (0x6777da4..0x6777e0b)

Copies from [rbx+0x78..0xAF] to [rbp+0x700..] region via [rbp+0x574], saves byte [rbp+0x26C] and u16 [rbp+0x2B0].

```
0x6777da4  mov eax,[rbx+0x78]                            
0x6777da7  lea rcx,[rbp+0x700]                           
0x6777dae  mov [rcx+0x10],eax                            
0x6777db1  movups xmm0,[rbx+0x68]                        
0x6777db5  movups [rcx],xmm0                             
0x6777db8  movzx eax,byte ptr [rbp+0x26C]                
0x6777dbf  mov [rbp+0x714],al                            
0x6777dc5  movups xmm0,[rbp+0x270]                       
0x6777dcc  movups [rbp+0x718],xmm0                       
0x6777dd3  movups xmm0,[rbx+0x90]                        
0x6777dda  movups xmm1,[rbx+0xA0]                        
0x6777de1  movups xmm2,[rbx+0xAF]                        
0x6777de8  lea rax,[rbp+0x574]                           
0x6777def  movups [rax+0x1D3],xmm2                       
0x6777df6  movups [rax+0x1C4],xmm1                       
0x6777dfd  movups [rax+0x1B4],xmm0                       
0x6777e04  movzx eax,word ptr [rbp+0x2B0]                
0x6777e0b  mov [rbp+0x758],ax                            
```

Interpretation: eax=[rbx+0x78] stored at [rcx+0x10]=[rbp+0x710]. xmm0=[rbx+0x68] stored at [rcx]=[rbp+0x700]. al=byte [rbp+0x26C] stored at [rbp+0x714]. xmm0=[rbp+0x270] stored at [rbp+0x718]. xmm0=[rbx+0x90], xmm1=[rbx+0xA0], xmm2=[rbx+0xAF]. rax=&[rbp+0x574]. Store xmm2 at [rax+0x1D3]=[rbp+0x747], xmm1 at [rax+0x1C4]=[rbp+0x738], xmm0 at [rax+0x1B4]=[rbp+0x728]. ax=word [rbp+0x2B0] stored at [rbp+0x758].

Callees: none.
Fields read: [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0x90], [rbx+0xA0], [rbx+0xAF], [rbp+0x2B0]. Fields written: [rbp+0x710], [rbp+0x700], [rbp+0x714], [rbp+0x718], [rbp+0x747], [rbp+0x738], [rbp+0x728], [rbp+0x758].

---

## Phase 27 — Call 0x5ABA5C0 + zero xmm regs [rbp+0x300..0x3C0] (0x6777e12..0x6777e82)

Calls 0x5ABA5C0 to get pass object, zeros xmm registers [rbp+0x300..0x3C0].

```
0x6777e12  mov rax,[rbp+0x828]                           
0x6777e19  mov rcx,[rax+0x10]                            
0x6777e1d  mov eax,0x9D0                                 
0x6777e22  add rcx,rax                                   
0x6777e25  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6777e2a  nop                                           
0x6777e2b  mov r13,rax                                   
0x6777e2e  movaps [rbp+0x3B0],xmm6                       
0x6777e35  movaps [rbp+0x3A0],xmm6                       
0x6777e3c  movaps [rbp+0x390],xmm6                       
0x6777e43  movaps [rbp+0x380],xmm6                       
0x6777e4a  movaps [rbp+0x370],xmm6                       
0x6777e51  movaps [rbp+0x360],xmm6                       
0x6777e58  movaps [rbp+0x350],xmm6                       
0x6777e5f  movaps [rbp+0x340],xmm6                       
0x6777e66  movaps [rbp+0x330],xmm6                       
0x6777e6d  movaps [rbp+0x320],xmm6                       
0x6777e74  movaps [rbp+0x310],xmm6                       
0x6777e7b  movaps [rbp+0x300],xmm6                       
0x6777e82  mov qword ptr [rbp+0x3C0],0                   
```

Interpretation: rax=[rbp+0x828] (BuilderSpan*), rcx=[rax+0x10], rcx+=0x9D0. Call 0x5ABA5C0(rcx). Result in r13 (pass object). Zero xmm6 into [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300]. [rbp+0x3C0]=0.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x828], [rax+0x10], xmm6. Fields written: [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0].

---

## Phase 28 — TLS/cookie read + feature flag [rbp+0x838] + shared_ptr items write u16 [rbp+0x758] (0x6777e8d..0x6777ed0)

Reads TLS via [0xF99FFA0] with dl=0x4A, stores at [rbp+0x838], writes u16 [rbp+0x758] to pass items buffer.

```
0x6777e8d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6777e94  mov rax,[rcx]                                 
0x6777e97  mov rax,[rax+0x10]                            
0x6777e9b  mov dl,0x4A                                   
0x6777e9d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6777ea3  nop                                           
0x6777ea4  mov [rbp+0x838],al                            
0x6777eaa  mov rdx,[r13+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6777eb1  cmp rdx,[r13+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6777eb8  je 0x6778587                                  ; -> loc_6778587
0x6777ebe  movzx eax,word ptr [rbp+0x758]                
0x6777ec5  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6777ec8  add qword ptr [r13+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6777ed0  jmp 0x677859B                                 ; -> loc_677859b
```

Interpretation: rcx=[0x1233E1B0] (TLS base). rax=[rcx], rax=[rax+0x10]. dl=0x4A. Call via [0xF99FFA0] (sub_eea6040). [rbp+0x838]=al (feature flag). rdx=[r13+0x8A8] (items write cursor). Compare with [r13+0x8B0] (items end). If equal jump to 0x6778587 (grow). Otherwise: eax=word [rbp+0x758], store ax at [rdx] (write u16 to items buffer), [r13+0x8A8]+=2. Jump to 0x677859B.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [r13+0x8A8], [r13+0x8B0], [rbp+0x758]. Fields written: [rbp+0x838], [rdx] (items buffer), [r13+0x8A8].

---

## Phase 29 — loc_6777ed5 / loc_6777ed8: alternate store [rbp+0x7D0] fields + call 0x678CF10 + call 0x6791AF0 (0x6777ed5..0x6777f73)

Alternate path: r14d=0, stores [rbp+0x7D0] at [rbp+0x4B0], [rbp+0x4B8]=r14, copies [rdx+0x20] and [rdx+0x10] to [rbp+0x4A4], saves [rbp+0x7BC] and ax, calls 0x678CF10 then 0x6791AF0.

```
loc_6777ed5:  ; from 6777c35
0x6777ed5  xor r14d,r14d                                 

loc_6777ed8:  ; from 6777c46
0x6777ed8  mov rcx,[rbp+0x7D0]                           
0x6777edf  mov [rbp+0x4B0],rcx                           
0x6777ee6  mov [rbp+0x4B8],r14                           
0x6777eed  lea rdx,[rbp+0x7D0]                           
0x6777ef4  mov rcx,[rdx+0x20]                            
0x6777ef8  lea r8,[rbp+0x4A4]                            
0x6777eff  mov [r8+0x2C],rcx                             
0x6777f03  movups xmm0,[rdx+0x10]                        
0x6777f07  movups [r8+0x1C],xmm0                         
0x6777f0c  mov ecx,[rbp+0x7BC]                           
0x6777f12  mov [rbp+0x4D8],ecx                           
0x6777f18  mov [rbp+0x4E0],ax                            
0x6777f1f  lea rcx,[rbp+0x2C0]                           
0x6777f26  lea r15,[rbp+0x110]                           
0x6777f2d  mov rdx,r15                                   
0x6777f30  call 0x678CF10                                ; -> sub_678cf10
0x6777f35  nop                                           
0x6777f36  lea rax,[rbp+0x4A0]                           
0x6777f3d  mov [rsp+0x30],rax                            
0x6777f42  lea rax,[rbp+0x4D8]                           
0x6777f49  mov [rsp+0x28],rax                            
0x6777f4e  lea rax,[rbp+0x4E0]                           
0x6777f55  mov [rsp+0x20],rax                            
0x6777f5a  mov rcx,r12                                   
0x6777f5d  lea rdx,[rbp+0x1F0]                           
0x6777f64  lea r8,[rbp+0x198]                            
0x6777f6b  mov r9,r15                                    
0x6777f6e  call 0x6791AF0                                ; -> sub_6791af0
0x6777f73  nop                                           
```

Interpretation: loc_6777ed5: r14d=0. loc_6777ed8: rcx=[rbp+0x7D0], [rbp+0x4B0]=rcx, [rbp+0x4B8]=r14. rdx=&[rbp+0x7D0]. rcx=[rdx+0x20]=[rbp+0x7F0]. r8=&[rbp+0x4A4]. [r8+0x2C]=[rbp+0x4D0]=rcx. xmm0=[rdx+0x10]=[rbp+0x7E0], stored at [r8+0x1C]=[rbp+0x4C0]. ecx=[rbp+0x7BC], [rbp+0x4D8]=ecx. [rbp+0x4E0]=ax. rcx=&[rbp+0x2C0], r15=&[rbp+0x110], rdx=r15. Call 0x678CF10. [rsp+0x30]=&[rbp+0x4A0], [rsp+0x28]=&[rbp+0x4D8], [rsp+0x20]=&[rbp+0x4E0]. rcx=r12, rdx=&[rbp+0x1F0], r8=&[rbp+0x198], r9=r15. Call 0x6791AF0.

Callees: 0x678CF10 (sub_678cf10), 0x6791AF0 (sub_6791af0).
Fields read: [rbp+0x7D0], [rdx+0x20], [rdx+0x10], [rbp+0x7BC], [rbp+0x2C0], [rbp+0x1F0], [rbp+0x198], [rbp+0x110]. Fields written: [rbp+0x4B0], [rbp+0x4B8], [rbp+0x4D0], [rbp+0x4C0], [rbp+0x4D8], [rbp+0x4E0], [rsp+0x30], [rsp+0x28], [rsp+0x20].

---

## Phase 30 — Copy [rbx+0x68..0x9F] to [rbp+0x6F0..] + save byte/u16 locals + call 0x5ABA5C0 + zero xmm [rbp+0x370..0x3C0] (0x6777f74..0x677801a)

Copies from [rbx+0x68..0x9F] to [rbp+0x6F0..] region via [rbp+0x574], saves byte [rbp+0x25C] and u16 [rbp+0x2A0], calls 0x5ABA5C0, zeros xmm [rbp+0x370..0x3C0].

```
0x6777f74  mov eax,[rbx+0x68]                            
0x6777f77  lea rcx,[rbp+0x6F0]                           
0x6777f7e  mov [rcx+0x10],eax                            
0x6777f81  movups xmm0,[rbx+0x58]                        
0x6777f85  movups [rcx],xmm0                             
0x6777f88  movzx eax,byte ptr [rbp+0x25C]                
0x6777f8f  mov [rbp+0x704],al                            
0x6777f95  movups xmm0,[rbp+0x260]                       
0x6777f9c  movups [rbp+0x708],xmm0                       
0x6777fa3  movups xmm0,[rbx+0x80]                        
0x6777faa  movups xmm1,[rbx+0x90]                        
0x6777fb1  movups xmm2,[rbx+0x9F]                        
0x6777fb8  lea rax,[rbp+0x574]                           
0x6777fbf  movups [rax+0x1C3],xmm2                       
0x6777fc6  movups [rax+0x1B4],xmm1                       
0x6777fcd  movups [rax+0x1A4],xmm0                       
0x6777fd4  movzx eax,word ptr [rbp+0x2A0]                
0x6777fdb  mov [rbp+0x748],ax                            
0x6777fe2  mov rax,[rbp+0x828]                           
0x6777fe9  mov rcx,[rax+0x10]                            
0x6777fed  mov eax,0x9D0                                 
0x6777ff2  add rcx,rax                                   
0x6777ff5  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6777ffa  nop                                           
0x6777ffb  mov r13,rax                                   
0x6777ffe  movaps [rbp+0x3B0],xmm6                       
0x6778005  movaps [rbp+0x3A0],xmm6                       
0x677800c  movaps [rbp+0x390],xmm6                       
0x6778013  movaps [rbp+0x380],xmm6                       
0x677801a  movaps [rbp+0x370],xmm6                       
```

Interpretation: eax=[rbx+0x68] stored at [rcx+0x10]=[rbp+0x700]. xmm0=[rbx+0x58] stored at [rcx]=[rbp+0x6F0]. al=byte [rbp+0x25C] stored at [rbp+0x704]. xmm0=[rbp+0x260] stored at [rbp+0x708]. xmm0=[rbx+0x80], xmm1=[rbx+0x90], xmm2=[rbx+0x9F]. rax=&[rbp+0x574]. Store xmm2 at [rax+0x1C3]=[rbp+0x737], xmm1 at [rax+0x1B4]=[rbp+0x728], xmm0 at [rax+0x1A4]=[rbp+0x718]. ax=word [rbp+0x2A0] stored at [rbp+0x748]. rax=[rbp+0x828], rcx=[rax+0x10], rcx+=0x9D0. Call 0x5ABA5C0(rcx). Result in r13. Zero xmm6 into [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370].

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbx+0x68], [rbx+0x58], [rbp+0x25C], [rbp+0x260], [rbx+0x80], [rbx+0x90], [rbx+0x9F], [rbp+0x2A0], [rbp+0x828], [rax+0x10]. Fields written: [rbp+0x700], [rbp+0x6F0], [rbp+0x704], [rbp+0x708], [rbp+0x737], [rbp+0x728], [rbp+0x718], [rbp+0x748], [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370].

---

## Phase 31 — Zero xmm [rbp+0x360..0x300] + TLS read + feature flag [rbp+0x838] (0x677801a..0x6778074)

Continues zeroing xmm [rbp+0x360..0x300], stores [rbp+0x3C0]=0, reads TLS via [0xF99FFA0] dl=0x4A, stores at [rbp+0x838].

```
0x677801a  movaps [rbp+0x370],xmm6                       
0x6778021  movaps [rbp+0x360],xmm6                       
0x6778028  movaps [rbp+0x350],xmm6                       
0x677802f  movaps [rbp+0x340],xmm6                       
0x6778036  movaps [rbp+0x330],xmm6                       
0x677803d  movaps [rbp+0x320],xmm6                       
0x6778044  movaps [rbp+0x310],xmm6                       
0x677804b  movaps [rbp+0x300],xmm6                       
0x6778052  mov qword ptr [rbp+0x3C0],0                   
0x677805d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778064  mov rax,[rcx]                                 
0x6778067  mov rax,[rax+0x10]                            
0x677806b  mov dl,0x4A                                   
0x677806d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778073  nop                                           
0x6778074  mov [rbp+0x838],al                            
```

Interpretation: Continue zeroing xmm6 into [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300]. [rbp+0x3C0]=0. rcx=[0x1233E1B0] (TLS base). rax=[rcx], rax=[rax+0x10]. dl=0x4A. Call via [0xF99FFA0]. [rbp+0x838]=al (feature flag).

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0], [rbp+0x838].

---

## Phase 32 — Shared_ptr items write u16 [rbp+0x748] + grow path loc_6778487 (0x677807a..0x677849a)

Writes u16 [rbp+0x748] to pass items buffer, or jumps to grow path if buffer full.

```
0x677807a  mov rdx,[r13+0x8A8]                           
0x6778081  cmp rdx,[r13+0x8B0]                           
0x6778088  je 0x6778487                                  ; -> loc_6778487
0x677808e  movzx eax,word ptr [rbp+0x748]                
0x6778095  mov [rdx],ax                                  
0x6778098  add qword ptr [r13+0x8A8],2                   
0x67780a0  jmp 0x677849B                                 ; -> loc_677849b

loc_6778487:  ; from 6778088
0x6778487  lea rcx,[r13+0x8A0]                           
0x677848e  lea r8,[rbp+0x748]                            
0x6778495  call 0x1EF6F90                                ; -> sub_1ef6f90
0x677849a  nop                                           
```

Interpretation: rdx=[r13+0x8A8] (items write cursor). Compare with [r13+0x8B0] (items end). If equal jump to loc_6778487 (grow via 0x1EF6F90). Otherwise: eax=word [rbp+0x748], store ax at [rdx] (write u16), [r13+0x8A8]+=2. Jump to loc_677849b.

Callees: 0x1EF6F90 (sub_1ef6f90).
Fields read: [r13+0x8A8], [r13+0x8B0], [rbp+0x748]. Fields written: [rdx] (items buffer), [r13+0x8A8].

---

## Phase 33 — loc_677849b: TLS read + feature flag + shared_ptr refcount + items write u16 [rbp+0x748] (0x677849b..0x6778582)

Reads TLS feature flag, computes item index, writes u16 [rbp+0x748] to items buffer, advances cursor.

```
loc_677849b:  ; from 67780a0
0x677849b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67784a2  mov rax,[rcx]                                 
0x67784a5  mov rax,[rax+0x10]                            
0x67784a9  movzx edx,byte ptr [rbp+0x838]                
0x67784b0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67784b6  nop                                           
0x67784b7  mov eax,[r13+0x8A8]                           
0x67784be  sub eax,[r13+0x8A0]                           
0x67784c5  shr eax,1                                     
0x67784c7  dec eax                                       
0x67784c9  mov [rbp+0x310],ax                            
0x67784d0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67784d7  mov rax,[rcx]                                 
0x67784da  mov rax,[rax+0x10]                            
0x67784de  mov dl,0x4A                                   
0x67784e0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67784e6  nop                                           
0x67784e7  mov [rbp+0x838],al                            
0x67784ed  mov rdx,[r13+0x758]                           
0x67784f4  cmp rdx,[r13+0x760]                           
0x67784fb  je 0x67788F3                                  ; -> loc_67788f3
0x6778501  lea rcx,[rbp+0x6F0]                           
0x6778508  mov eax,[rcx+0x10]                            
0x677850b  mov [rdx+0x10],eax                            
0x677850e  movups xmm0,[rcx]                             
0x6778511  movups [rdx],xmm0                             
0x6778514  movzx eax,byte ptr [rbp+0x704]                
0x677851b  mov [rdx+0x14],al                             
0x677851e  movss xmm0,[rbp+0x708]                        
0x6778526  movss [rdx+0x18],xmm0                         
0x677852b  movss xmm0,[rbp+0x70C]                        
0x6778533  movss [rdx+0x1C],xmm0                         
0x6778538  movss xmm0,[rbp+0x710]                        
0x6778540  movss [rdx+0x20],xmm0                         
0x6778545  movss xmm0,[rbp+0x714]                        
0x677854d  movss [rdx+0x24],xmm0                         
0x6778552  lea rax,[rbp+0x574]                           
0x6778559  movups xmm0,[rax+0x1A4]                       
0x6778560  movups xmm1,[rax+0x1B4]                       
0x6778567  movups xmm2,[rax+0x1C3]                       
0x677856e  movups [rdx+0x28],xmm0                        
0x6778572  movups [rdx+0x38],xmm1                        
0x6778576  movups [rdx+0x47],xmm2                        
0x677857a  add qword ptr [r13+0x758],0x58                
0x6778582  jmp 0x6778907                                 ; -> loc_6778907
```

Interpretation: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=[rbp+0x838]. Call via [0xF99FFA0]. [rbp+0x838]=al. eax=[r13+0x8A8]-[r13+0x8A0] (item count*2), shr 1, dec eax, [rbp+0x310]=ax (item index-1). Second TLS read, [rbp+0x838]=al. rdx=[r13+0x758] (items cursor). Compare with [r13+0x760] (items end). If equal jump to loc_67788f3 (grow). Otherwise: rcx=&[rbp+0x6F0], copy 16 bytes [rcx..rcx+0xF] to [rdx..rdx+0xF], eax=[rcx+0x10] to [rdx+0x10], al=byte [rbp+0x704] to [rdx+0x14], xmm0=[rbp+0x708] to [rdx+0x18], [rbp+0x70C] to [rdx+0x1C], [rbp+0x710] to [rdx+0x20], [rbp+0x714] to [rdx+0x24]. rax=&[rbp+0x574], xmm0=[rax+0x1A4], xmm1=[rax+0x1B4], xmm2=[rax+0x1C3] to [rdx+0x28/0x38/0x47]. [r13+0x758]+=0x58. Jump to loc_6778907.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x8A8], [r13+0x8A0], [r13+0x758], [r13+0x760], [rbp+0x6F0], [rbp+0x704], [rbp+0x708], [rbp+0x70C], [rbp+0x710], [rbp+0x714], [rbp+0x574], [rax+0x1A4], [rax+0x1B4], [rax+0x1C3]. Fields written: [rbp+0x838], [rbp+0x310], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r13+0x758].

---

## Phase 34 — Grow path loc_6778587 + loc_677859b TLS read + copy path start (0x6778587..0x677861b)

Grow path for items buffer, then TLS feature flag read, then copy [rbp+0x700..] to items buffer.

```
  6778587  lea rcx,[r13+0x8A0]                           
  677858e  lea r8,[rbp+0x758]                            
  6778595  call 0x1EF6F90                                ; -> sub_1ef6f90
  677859a  nop                                           

loc_677859b:  ; from 67780a0
  677859b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67785a2  mov rax,[rcx]                                 
  67785a5  mov rax,[rax+0x10]                            
  67785a9  movzx edx,byte ptr [rbp+0x838]                
  67785b0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67785b6  nop                                           
  67785b7  mov [rbp+0x838],al                            
  67785ed  mov rdx,[r13+0x758]                           
  67785f4  cmp rdx,[r13+0x760]                           
  67785fb  je 0x677898E                                  ; -> loc_677898e
  6778601  lea rcx,[rbp+0x700]                           
  6778608  mov eax,[rcx+0x10]                            
  677860b  mov [rdx+0x10],eax                            
  677860e  movups xmm0,[rcx]                             
  6778611  movups [rdx],xmm0                             
  6778614  movzx eax,byte ptr [rbp+0x714]                
  677861b  mov [rdx+0x14],al                             ; W a1+0x14
```

Interpretation: loc_6778587: rcx=&[r13+0x8A0], r8=&[rbp+0x758]. Call 0x1EF6F90 (grow items buffer). loc_677859b: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=[rbp+0x838]. Call via [0xF99FFA0]. [rbp+0x838]=al. rdx=[r13+0x758] (items cursor). Compare with [r13+0x760] (items end). If equal jump to loc_677898E (grow). Otherwise: rcx=&[rbp+0x700], eax=[rcx+0x10] to [rdx+0x10], xmm0=[rcx] to [rdx], al=byte [rbp+0x714] to [rdx+0x14].

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [r13+0x8A0], [rbp+0x758], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x758], [r13+0x760], [rbp+0x700], [rbp+0x714]. Fields written: [rbp+0x838], [rdx+0x10], [rdx], [rdx+0x14].

---

## Phase 35 — Copy path continuation: movss stores + xmm stores + add qword + jmp loc_67789a2 (0x677861e..0x6778682)

Continues storing [rbp+0x718..0x724] and xmm data to items buffer, advances cursor by 0x58.

```
  677861e  movss xmm0,[rbp+0x718]                        
  6778626  movss [rdx+0x18],xmm0                         ; W a1+0x18
  677862b  movss xmm0,[rbp+0x71C]                        
  6778633  movss [rdx+0x1C],xmm0                         ; W a1+0x1C
  6778638  movss xmm0,[rbp+0x720]                        
  6778640  movss [rdx+0x20],xmm0                         ; W a1+0x20
  6778645  movss xmm0,[rbp+0x724]                        
  677864d  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6778652  lea rax,[rbp+0x574]                           
  6778659  movups xmm0,[rax+0x1B4]                       
  6778660  movups xmm1,[rax+0x1C4]                       
  6778667  movups xmm2,[rax+0x1D3]                       
  677866e  movups [rdx+0x28],xmm0                        ; W a1+0x28
  6778672  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6778676  movups [rdx+0x47],xmm2                        ; W a1+0x47
  677867a  add qword ptr [r13+0x758],0x58                
  6778682  jmp 0x67789A2                                 ; -> loc_67789a2
```

Interpretation: xmm0=[rbp+0x718] to [rdx+0x18], [rbp+0x71C] to [rdx+0x1C], [rbp+0x720] to [rdx+0x20], [rbp+0x724] to [rdx+0x24]. rax=&[rbp+0x574]. xmm0=[rax+0x1B4] to [rdx+0x28], xmm1=[rax+0x1C4] to [rdx+0x38], xmm2=[rax+0x1D3] to [rdx+0x47]. [r13+0x758]+=0x58. Jump to loc_67789a2.

Callees: none.
Fields read: [rbp+0x718], [rbp+0x71C], [rbp+0x720], [rbp+0x724], [rbp+0x574], [rax+0x1B4], [rax+0x1C4], [rax+0x1D3], [r13+0x758]. Fields written: [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r13+0x758].

---

## Phase 36 — Grow path loc_6778687 + call 0x6760A80 + TLS read + feature flag [rbp+0x838] (0x6778687..0x6778074)

Grow path for [r14+0x750]/[r14+0x758], call 0x6760A80, then TLS read and feature flag store.

```
  6778687  lea rcx,[r14+0x750]                           
  677868e  lea r8,[rbp+0x6B0]                            
  6778695  call 0x6760A80                                ; -> sub_6760a80
  677869a  nop                                           
  677869b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67786a2  mov rax,[rcx]                                 
  67786a5  mov rax,[rax+0x10]                            
  67786a9  movzx edx,byte ptr [rbp+0x838]                
  67786b0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67786b6  nop                                           
  67786b7  mov qword ptr [rbp+0x300],0x4001              
  67786c2  mov eax,[r14+0x758]                           
  67786c9  sub eax,[r14+0x750]                           
  67786d0  shr eax,3                                     
  67786d3  imul eax,0xFFFF8BA3                           
  67786d9  dec eax                                       
  67786db  mov [rbp+0x32C],ax                            
```

Interpretation: loc_6778687: rcx=&[r14+0x750], r8=&[rbp+0x6B0]. Call 0x6760A80. Then rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=[rbp+0x838]. Call via [0xF99FFA0]. [rbp+0x300]=0x4001 (u64). eax=[r14+0x758]-[r14+0x750] (byte count), shr 3 (divide by 8), imul eax, 0xFFFF8BA3 (magic multiply), dec eax, [rbp+0x32C]=ax.

Callees: 0x6760A80 (sub_6760a80), [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [r14+0x750], [rbp+0x6B0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x758], [r14+0x750]. Fields written: [rbp+0x300], [rbp+0x32C].

---

## Phase 37 — TLS read + feature flag + shared_ptr counter increment (0x67786e2..0x6778752)

Second TLS read, feature flag store, then shared_ptr counter [r14+0x890] increment with bounds check.

```
  67786e2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67786e9  mov rax,[rcx]                                 
  67786ec  mov rax,[rax+0x10]                            
  67786f0  mov dl,0x4A                                   
  67786f2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67786f8  nop                                           
  67786f9  mov [rbp+0x838],al                            
  67786ff  mov rdx,[r14+0x890]                           
  6778706  cmp rdx,[r14+0x898]                           
  677870d  je 0x6778A29                                  ; -> loc_6778a29
  6778713  inc rdx                                       
  6778716  mov [r14+0x890],rdx                           
  677871d  jmp 0x6778A36                                 ; -> loc_6778a36
```

Interpretation: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A. Call via [0xF99FFA0]. [rbp+0x838]=al. rdx=[r14+0x890] (shared_ptr cursor). Compare with [r14+0x898] (shared_ptr end). If equal jump to loc_6778a29 (grow). Otherwise rdx++ (increment cursor), [r14+0x890]=rdx. Jump to loc_6778a36.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x890], [r14+0x898]. Fields written: [rbp+0x838], [r14+0x890].

---

## Phase 38 — Grow path loc_6778a29 + call 0x6760E60 + loc_6778a36: not+add + TLS read + feature flag (0x6778a29..0x6778aa4)

Grow path: call 0x6760E60. Then loc_6778a36: not eax, add to [r14+0x890], store at [rbp+0x312]. TLS read, feature flag, shared_ptr [r14+0x7A0] increment.

```
  6778a29  lea rcx,[r14+0x888]                           
  6778a30  call 0x6760E60                                ; -> sub_6760e60
  6778a35  nop                                           

loc_6778a36:  ; from 677871d
  6778a36  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6778a3d  mov rax,[rcx]                                 
  6778a40  mov rax,[rax+0x10]                            
  6778a44  movzx edx,byte ptr [rbp+0x838]                
  6778a4b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6778a51  nop                                           
  6778a52  mov eax,[r14+0x888]                           
  6778a59  not eax                                       
  6778a5b  add eax,[r14+0x890]                           
  6778a62  mov [rbp+0x312],ax                            
  6778a69  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6778a70  mov rax,[rcx]                                 
  6778a73  mov rax,[rax+0x10]                            
  6778a77  mov dl,0x4A                                   
  6778a79  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6778a7f  nop                                           
  6778a80  mov [rbp+0x838],al                            
  6778a86  mov rdx,[r14+0x7A0]                           
  6778a8d  cmp rdx,[r14+0x7A8]                           
  6778a94  je 0x6778D29                                  ; -> loc_6778d29
  6778a9a  inc rdx                                       
  6778a9d  mov [r14+0x7A0],rdx                           
  6778aa4  jmp 0x6778D36                                 ; -> loc_6778d36
```

Interpretation: loc_6778a29: rcx=&[r14+0x888]. Call 0x6760E60. loc_6778a36: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=[rbp+0x838]. Call via [0xF99FFA0]. [rbp+0x838]=al. eax=[r14+0x888], not eax, add eax,[r14+0x890], [rbp+0x312]=ax. Second TLS read, [rbp+0x838]=al. rdx=[r14+0x7A0]. Compare with [r14+0x7A8]. If equal jump to loc_6778D29 (grow). Otherwise rdx++, [r14+0x7A0]=rdx. Jump to loc_6778d36.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect call, twice).
Fields read: [r14+0x888], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x890], [r14+0x7A0], [r14+0x7A8]. Fields written: [rbp+0x838], [rbp+0x312], [r14+0x7A0].

---

## Phase 39 — Grow paths loc_6778aa9 / loc_6778ab6 + loc_6778b36: not+add pattern repeated (0x6778aa9..0x6778bb6)

Three grow paths with not+add pattern, each followed by TLS read and feature flag store.

```
loc_6778aa9:  ; from 67787a8
  6778aa9  lea rcx,[r14+0x888]                           
  6778ab0  call 0x6760E60                                ; -> sub_6760e60
  6778ab5  nop                                           

loc_6778ab6:  ; from 67787b8
  6778ab6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6778abd  mov rax,[rcx]                                 
  6778ac0  mov rax,[rax+0x10]                            
  6778ac4  movzx edx,byte ptr [rbp+0x838]                
  6778acb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6778ad1  nop                                           
  6778ad2  mov eax,[r14+0x888]                           
  6778ad9  not eax                                       
  6778adb  add eax,[r14+0x890]                           
  6778ae2  mov [rbp+0x312],ax                            
  6778ae9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6778af0  mov rax,[rcx]                                 
  6778af3  mov rax,[rax+0x10]                            
  6778af7  mov dl,0x4A                                   
  6778af9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6778aff  nop                                           
  6778b00  mov [rbp+0x838],al                            
  6778b06  mov rdx,[r14+0x7A0]                           
  6778b0d  cmp rdx,[r14+0x7A8]                           
  6778b14  je 0x6778E88                                  ; -> loc_6778e88
  6778b1a  inc rdx                                       
  6778b1d  mov [r14+0x7A0],rdx                           
  6778b24  jmp 0x6778E95                                 ; -> loc_6778e95

loc_6778b29:  ; from 6778843
  6778b29  lea rcx,[r14+0x888]                           
  6778b30  call 0x6760E60                                ; -> sub_6760e60
  6778b35  nop                                           

loc_6778b36:  ; from 6778853
  6778b36  mov rcx,[0x1233E1B0]                          ; [data_1233E1b0]
  6778b3d  mov rax,[rcx]                                 
  6778b40  mov rax,[rax+0x10]                            
  6778b44  movzx edx,byte ptr [rbp+0x838]                
  6778b4b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6778b51  nop                                           
  6778b52  mov eax,[r14+0x888]                           
  6778b59  not eax                                       
  6778b5b  add eax,[r14+0x890]                           
  6778b62  mov [rbp+0x312],ax                            
```

Interpretation: loc_6778aa9: grow path call 0x6760E60. loc_6778ab6: TLS read, [rbp+0x838]=al, eax=[r14+0x888] not eax add [r14+0x890] -> [rbp+0x312]. TLS read again, [rbp+0x838]=al. rdx=[r14+0x7A0], cmp with [r14+0x7A8], if equal jump to loc_6778e88. Otherwise inc rdx, [r14+0x7A0]=rdx, jump to loc_6778e95.

loc_6778b29: grow path call 0x6760E60. loc_6778b36: same not+add pattern, TLS read twice, [rbp+0x838]=al, [rbp+0x312]=ax.

Callees: 0x6760E60 (sub_6760e60, three times), [0xF99FFA0] = sub_eea6040 (indirect, multiple times).
Fields read: [r14+0x888], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x890], [r14+0x7A0], [r14+0x7A8]. Fields written: [rbp+0x838], [rbp+0x312], [r14+0x7A0].

---

## Phase 40 — Grow path loc_6778ba9 + loc_6778bb6: not+add + TLS read + shared_ptr [r14+0x7A0] (0x6778ba9..0x6778c1a)

Grow path call 0x6760E60, then not+add pattern, TLS read, feature flag, shared_ptr [r14+0x7A0] increment with bounds check.

```
loc_6778ba9:  ; from 67788de
  6778ba9  lea rcx,[r14+0x888]                           
  6778bb0  call 0x6760E60                                ; -> sub_6760e60
  6778bb5  nop                                           

loc_6778bb6:  ; from 67788ee
  6778bb6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6778bbd  mov rax,[rcx]                                 
  6778bc0  mov rax,[rax+0x10]                            
  6778bc4  movzx edx,byte ptr [rbp+0x838]                
  6778bcb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6778bd1  nop                                           
  6778bd2  mov eax,[r14+0x888]                           
  6778bd9  not eax                                       
  6778bdb  add eax,[r14+0x890]                           
  6778be2  mov [rbp+0x312],ax                            
  6778be9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6778bf0  mov rax,[rcx]                                 
  6778bf3  mov rax,[rax+0x10]                            
  6778bf7  mov dl,0x4A                                   
  6778bf9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6778bff  nop                                           
  6778c00  mov [rbp+0x838],al                            
  6778c06  mov rdx,[r14+0x7A0]                           
  6778c0d  cmp rdx,[r14+0x7A8]                           
  6778c14  je 0x6779146                                  ; -> loc_6779146
  6778c1a  inc rdx                                       
```

Interpretation: loc_6778ba9: rcx=&[r14+0x888]. Call 0x6760E60. loc_6778bb6: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=[rbp+0x838]. Call via [0xF99FFA0]. eax=[r14+0x888], not eax, add [r14+0x890], [rbp+0x312]=ax. TLS read again, [rbp+0x838]=al. rdx=[r14+0x7A0], cmp with [r14+0x7A8]. If equal jump to loc_6779146 (grow). Otherwise rdx++.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r14+0x888], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x890], [r14+0x7A0], [r14+0x7A8]. Fields written: [rbp+0x838], [rbp+0x312], [r14+0x7A0].

---

---

---