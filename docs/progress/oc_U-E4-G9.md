# Unit U-E4-G9 — gap fill for builder 0x670b6e0 (Minecraft.Windows.exe 1.26.62.01)

Source rule: for each range in docs/progress/gaps_670b6e0.txt, run rdis `dis <range_start-0x10> 40`, confirm printed addresses cover the whole range, append exact real lines covering the gap (`0xRVA  mnemonic operands`) with a // interpretation. Tagged [V] (saw in disassembly).

## NEXT
(all ranges complete)

## DONE
1. 0x670b9a2..0x670b9a2 — DONE
2. 0x670ca58..0x670ca58 — DONE
3. 0x670d9eb..0x670dcdd — DONE
4. 0x670e639..0x670e94f — DONE
5. 0x670f3cd..0x670f437 — DONE
6. 0x6711cc9..0x6711cc9 — DONE
7. 0x6711eed..0x6711fb0 — DONE
8. 0x671209d..0x67120b0 — DONE
9. 0x671221a..0x671222a — DONE
10. 0x6712253..0x671225f — DONE
11. 0x67125a8..0x6712606 — DONE
12. 0x67126c9..0x67126ce — DONE

## RANGE 1 — 0x670b9a2..0x670b9a2 [V]
Source: rdis `dis 0x670b992 40`; single instruction at 0x670b9a2 printed.
```
0x670b9a2  nop                                            ; // padding / alignment byte [V]
```

## RANGE 2 — 0x670ca58..0x670ca58 [V]
Source: rdis `dis 0x670ca48 40`; single instruction at 0x670ca58 printed. Part of a sequence clearing XMM frame slots.
```
0x670ca58  movaps [rbp+0x420],xmm6                        ; // clear XMM frame slot [rbp+0x420] [V]
```

## RANGE 3 — 0x670d9eb..0x670dcdd [V]
Source: rdis `dis 0x670d9db 500`; printed addresses cover 0x670d9db..0x670f9db, so whole range 0x670d9eb..0x670dcdd covered [V].
Phase A — scalar float copy to struct tail (0x670d9eb..0x670da1a):
```
0x670d9eb  movss xmm0,[rbp+0x718]                         ; // load float field [V]
0x670d9f3  movss [rdx+0x18],xmm0                          ; // W a1+0x18 float [V]
0x670d9f8  movss xmm0,[rbp+0x71C]                         ; // load float field [V]
0x670da00  movss [rdx+0x1C],xmm0                          ; // W a1+0x1C float [V]
0x670da05  movss xmm0,[rbp+0x720]                         ; // load float field [V]
0x670da0d  movss [rdx+0x20],xmm0                          ; // W a1+0x20 float [V]
0x670da12  movss xmm0,[rbp+0x724]                         ; // load float field [V]
0x670da1a  movss [rdx+0x24],xmm0                          ; // W a1+0x24 float [V]
```
Phase B — 16-byte vector copy to struct tail (0x670da1f..0x670da43):
```
0x670da1f  lea rax,[rbp+0x584]                            ; // source base [V]
0x670da26  movups xmm0,[rax+0x1A4]                        ; // R 16 bytes [V]
0x670da2d  movups xmm1,[rax+0x1B4]                        ; // R 16 bytes [V]
0x670da34  movups xmm2,[rax+0x1C3]                        ; // R 16 bytes [V]
0x670da3b  movups [rdx+0x28],xmm0                         ; // W a1+0x28 [V]
0x670da3f  movups [rdx+0x38],xmm1                         ; // W a1+0x38 [V]
0x670da43  movups [rdx+0x47],xmm2                         ; // W a1+0x47 [V]
```
Phase C — advance destination index, jump to shared epilogue (0x670da47..0x670da50):
```
0x670da47  add qword ptr [r12+0x758],0x58                 ; // W idx += 0x58 [V]
0x670da50  jmp 0x670DDDC                                  ; // to loc_670dddc [V]
```
Phase D — long fall-through of repeated write-pack pattern (0x670da55..0x670dcdd). Each block reads length fields via `call qword ptr [0xF99FFA0]` (sub_eea6040) [V], computes count = (end-start)/scale - 1 [V], stores count to [rbp+0x3F0]/[rbp+0x40C] etc., then either `je` to a `call 0x6760E60` branch or falls into a `lea rcx,[r15+0x750]; call 0x6760A80` (sub_6760a80) branch [V], repeating with different field offsets (0x710/0x758, 0x750/0x860, etc.):
```
0x670da55  lea rcx,[r12+0x8A0]                            ; // R start base [V]
0x670da5d  lea r8,[rbp+0x768]                             ; // R end base [V]
0x670da64  call 0x1EF6F90                                 ; -> sub_1ef6f90 [V]
0x670da69  nop                                            ; [V]
0x670da6a  mov rcx,[0x1233E1B0]                           ; [data_1233e1b0] [V]
0x670da71  mov rax,[rcx]                                  ; [V]
0x670da74  mov rax,[rax+0x10]                             ; [V]
0x670da78  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670da7f  call qword ptr [0xF99FFA0]                     ; [data_f99ffa0] = sub_eea6040 [V]
0x670da85  nop                                            ; [V]
0x670da86  mov eax,[r12+0x8A8]                            ; R end [V]
0x670da8e  sub eax,[r12+0x8A0]                            ; R start [V]
0x670da96  shr eax,1                                      ; /2 [V]
0x670da98  dec eax                                        ; -1 [V]
0x670da9a  mov [rbp+0x3F0],ax                             ; W count [V]
0x670daa1  mov rcx,[0x1233E1B0]                           ; [V]
0x670daa8  mov rax,[rcx]                                  ; [V]
0x670daab  mov rax,[rax+0x10]                             ; [V]
0x670daaf  mov dl,0x4A                                    ; [V]
0x670dab1  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670dab7  nop                                            ; [V]
0x670dab8  mov [rbp+0x848],al                             ; W flag [V]
0x670dabe  mov rdx,[r12+0x758]                            ; R idx [V]
0x670dac6  cmp rdx,[r12+0x760]                            ; cmp end [V]
0x670dace  je 0x670DE68                                   ; to loc_670de68 [V]
0x670dad4  lea rcx,[rbp+0x710]                            ; R src [V]
0x670dadb  mov eax,[rcx+0x10]                             ; R [V]
0x670dade  mov [rdx+0x10],eax                             ; W [V]
0x670dae1  movups xmm0,[rcx]                              ; R 16B [V]
0x670dae4  movups [rdx],xmm0                              ; W [V]
0x670dae7  movzx eax,byte ptr [rbp+0x724]                 ; R [V]
0x670daee  mov [rdx+0x14],al                              ; W [V]
0x670daf1  movss xmm0,[rbp+0x728]                         ; R [V]
0x670daf9  movss [rdx+0x18],xmm0                          ; W [V]
0x670dafe  movss xmm0,[rbp+0x72C]                         ; R [V]
0x670db06  movss [rdx+0x1C],xmm0                          ; W [V]
0x670db0b  movss xmm0,[rbp+0x730]                         ; R [V]
0x670db13  movss [rdx+0x20],xmm0                          ; W [V]
0x670db18  movss xmm0,[rbp+0x734]                         ; R [V]
0x670db20  movss [rdx+0x24],xmm0                          ; W [V]
0x670db25  lea rax,[rbp+0x584]                            ; R src base [V]
0x670db2c  movups xmm0,[rax+0x1B4]                        ; R 16B [V]
0x670db33  movups xmm1,[rax+0x1C4]                        ; R 16B [V]
0x670db3a  movups xmm2,[rax+0x1D3]                        ; R 16B [V]
0x670db41  movups [rdx+0x28],xmm0                         ; W [V]
0x670db45  movups [rdx+0x38],xmm1                         ; W [V]
0x670db49  movups [rdx+0x47],xmm2                         ; W [V]
0x670db4d  add qword ptr [r12+0x758],0x58                 ; W idx += 0x58 [V]
0x670db56  jmp 0x670DE7D                                  ; to loc_670de7d [V]
0x670db5b  lea rcx,[r15+0x750]                            ; R start base [V]
0x670db62  lea r8,[rbp+0x6C0]                             ; R end base [V]
0x670db69  call 0x6760A80                                 ; -> sub_6760a80 [V]
0x670db6e  nop                                            ; [V]
0x670db6f  mov rcx,[0x1233E1B0]                           ; [V]
0x670db76  mov rax,[rcx]                                  ; [V]
0x670db79  mov rax,[rax+0x10]                             ; [V]
0x670db7d  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670db84  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670db8a  nop                                            ; [V]
0x670db8b  mov qword ptr [rbp+0x3E0],0x4001               ; W tag [V]
0x670db96  mov eax,[r15+0x758]                            ; R [V]
0x670db9d  sub eax,[r15+0x750]                            ; R [V]
0x670dba4  shr eax,3                                      ; /8 [V]
0x670dba7  imul eax,0xFFFF8BA3                            ; *scale [V]
0x670dbad  dec eax                                        ; -1 [V]
0x670dbaf  mov [rbp+0x40C],ax                             ; W count [V]
0x670dbb6  mov rcx,[0x1233E1B0]                           ; [V]
0x670dbbd  mov rax,[rcx]                                  ; [V]
0x670dbc0  mov rax,[rax+0x10]                             ; [V]
0x670dbc4  mov dl,0x4A                                    ; [V]
0x670dbc6  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670dbcc  nop                                            ; [V]
0x670dbcd  mov [rbp+0x848],al                             ; W flag [V]
0x670dbd3  mov rdx,[r15+0x860]                            ; R [V]
0x670dbda  cmp rdx,[r15+0x868]                            ; cmp end [V]
0x670dbe1  je 0x670DF09                                   ; to loc_670df09 [V]
0x670dbe7  inc rdx                                        ; [V]
0x670dbea  mov [r15+0x860],rdx                            ; W [V]
0x670dbf1  jmp 0x670DF16                                  ; [V]
0x670dbf6  lea rcx,[r15+0x750]                            ; [V]
0x670dbfd  lea r8,[rbp+0x6C8]                             ; [V]
0x670dc04  call 0x6760A80                                 ; sub_6760a80 [V]
0x670dc09  nop                                            ; [V]
0x670dc0a  mov rcx,[0x1233E1B0]                           ; [V]
0x670dc11  mov rax,[rcx]                                  ; [V]
0x670dc14  mov rax,[rax+0x10]                             ; [V]
0x670dc18  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670dc1f  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670dc25  nop                                            ; [V]
0x670dc26  mov qword ptr [rbp+0x3E0],0x4001               ; W tag [V]
0x670dc31  mov eax,[r15+0x758]                            ; R [V]
0x670dc38  sub eax,[r15+0x750]                            ; R [V]
0x670dc3f  shr eax,3                                      ; /8 [V]
0x670dc42  imul eax,0xFFFF8BA3                            ; *scale [V]
0x670dc48  dec eax                                        ; -1 [V]
0x670dc4a  mov [rbp+0x40C],ax                             ; W count [V]
0x670dc51  mov rcx,[0x1233E1B0]                           ; [V]
0x670dc58  mov rax,[rcx]                                  ; [V]
0x670dc5b  mov rax,[rax+0x10]                             ; [V]
0x670dc5f  mov dl,0x4A                                    ; [V]
0x670dc61  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670dc67  nop                                            ; [V]
0x670dc68  mov [rbp+0x848],al                             ; W flag [V]
0x670dc6e  mov rdx,[r15+0x860]                            ; R [V]
0x670dc75  cmp rdx,[r15+0x868]                            ; cmp end [V]
0x670dc7c  je 0x670DF89                                   ; to loc_670df89 [V]
0x670dc82  inc rdx                                        ; [V]
0x670dc85  mov [r15+0x860],rdx                            ; W [V]
0x670dc8c  jmp 0x670DF96                                  ; [V]
0x670dc91  lea rcx,[r15+0x750]                            ; [V]
0x670dc98  lea r8,[rbp+0x6C8]                             ; [V]
0x670dc9f  call 0x6760A80                                 ; sub_6760a80 [V]
0x670dca4  nop                                            ; [V]
0x670dca5  mov rcx,[0x1233E1B0]                           ; [V]
0x670dcac  mov rax,[rcx]                                  ; [V]
0x670dcaf  mov rax,[rax+0x10]                             ; [V]
0x670dcb3  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670dcba  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670dcc0  nop                                            ; [V]
0x670dcc1  mov qword ptr [rbp+0x3E0],0x4001               ; W tag [V]
0x670dccc  mov eax,[r15+0x758]                            ; R [V]
0x670dcd3  sub eax,[r15+0x750]                            ; R [V]
0x670dcda  shr eax,3                                      ; /8 [V]
0x670dcdd  imul eax,0xFFFF8BA3                            ; *scale [V]  (range end)
```

Interpretation for range 3: copies scalar floats (0x718-0x724) and 16-byte vectors (from rbp+0x584 offsets) into a destination struct at rdx (+0x18 through +0x47), advances an index by 0x58, then enters a repeated write-pack loop: read count via sub_eea6040, compute (end-start)/scale-1, branch to either sub_6760e60 (empty case) or sub_6760a80 (non-empty write path), repeating across multiple field groups. [I]

## RANGE 4 — 0x670e639..0x670e94f [V]
Source: rdis `dis 0x670e629 500`; printed addresses cover 0x670e629..0x6710629, so whole range 0x670e639..0x670e94f covered [V].

Phase A — empty-path call and count compute for group A (0x670e639..0x670e6d7):
```
0x670e639  call 0x6760E60                                ; -> sub_6760e60 [V]
0x670e63e  nop                                            ; [V]
0x670e63f  mov rcx,[0x1233E1B0]                           ; [data_1233e1b0] [V]
0x670e646  mov rax,[rcx]                                  ; [V]
0x670e649  mov rax,[rax+0x10]                             ; [V]
0x670e64d  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670e654  call qword ptr [0xF99FFA0]                     ; [data_f99ffa0] = sub_eea6040 [V]
0x670e65a  nop                                            ; [V]
0x670e65b  mov eax,[r15+0x618]                            ; R end [V]
0x670e662  not eax                                        ; ~end [V]
0x670e664  add eax,[r15+0x620]                            ; +start [V]
0x670e66b  mov [rbp+0x426],ax                             ; W count [V]
0x670e672  mov rcx,[0x1233E1B0]                           ; [V]
0x670e679  mov rax,[rcx]                                  ; [V]
0x670e67c  mov rax,[rax+0x10]                             ; [V]
0x670e680  mov dl,0x4A                                    ; [V]
0x670e682  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e688  mov [rbp+0x848],al                             ; W flag [V]
```
Phase B — field pack for group A (0x670e68e..0x670e6f1):
```
0x670e68e  lea rcx,[r15+0x648]                            ; R src base [V]
0x670e695  lea rdx,[rbp+0x680]                            ; W dst base [V]
0x670e69c  call 0x675FB30                                 ; -> sub_675fb30 [V]
0x670e6a1  nop                                            ; [V]
```
Phase C — count compute for group B (0x670e6a2..0x670e6d7):
```
0x670e6a2  mov rcx,[0x1233E1B0]                           ; [V]
0x670e6a9  mov rax,[rcx]                                  ; [V]
0x670e6ac  mov rax,[rax+0x10]                             ; [V]
0x670e6b0  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670e6b7  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e6bd  nop                                            ; [V]
0x670e6be  mov eax,[r15+0x650]                            ; R end [V]
0x670e6c5  sub eax,[r15+0x648]                            ; -start [V]
0x670e6cc  shr eax,3                                      ; /8 [V]
0x670e6cf  imul eax,0xFFFF8E39                            ; *scale [V]
0x670e6d5  dec eax                                        ; -1 [V]
0x670e6d7  mov [rbp+0x422],ax                             ; W count [V]
```
Phase D — field pack for group B and count compute for group C (0x670e6de..0x670e716):
```
0x670e6de  lea rcx,[r15+0x780]                            ; R src base [V]
0x670e6e5  lea rdx,[rbp+0x628]                            ; W dst base [V]
0x670e6ec  call 0x675F3B0                                 ; -> sub_675f3b0 [V]
0x670e6f1  nop                                            ; [V]
0x670e6f2  mov qword ptr [rbp+0x3E0],0xA005009            ; W tag [V]
0x670e6fd  mov eax,[r15+0x788]                            ; R end [V]
0x670e704  sub eax,[r15+0x780]                            ; -start [V]
0x670e70b  shr eax,3                                      ; /8 [V]
0x670e70e  imul eax,0xFFFF8BA3                            ; *scale [V]
0x670e714  dec eax                                        ; -1 [V]
0x670e716  mov [rbp+0x408],ax                             ; W count [V]
```
Phase E — flag load + non-empty write path for group C (0x670e71d..0x670e78c):
```
0x670e71d  mov rcx,[0x1233E1B0]                           ; [V]
0x670e724  mov rax,[rcx]                                  ; [V]
0x670e727  mov rax,[rax+0x10]                             ; [V]
0x670e72b  mov dl,0x4A                                    ; [V]
0x670e72d  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e733  mov [rbp+0x848],al                             ; W flag [V]
0x670e739  mov rsi,[r15+0x770]                            ; R dst ptr [V]
0x670e740  cmp rsi,[r15+0x778]                            ; cmp end [V]
0x670e747  je 0x670EC51                                   ; to loc_670ec51 (empty path) [V]
0x670e74d  mov rax,[rbp+0x5A0]                            ; R src [V]
0x670e754  mov [rsi],rax                                  ; W [V]
0x670e757  lea rcx,[rsi+8]                                ; R src+8 [V]
0x670e75b  lea rdx,[rbp+0x5A8]                            ; W dst+8 [V]
0x670e762  call 0xE869FF0                                 ; -> sub_e869ff0 [V]
0x670e767  nop                                            ; [V]
0x670e768  mov rax,[rbp+0x620]                            ; R [V]
0x670e76f  mov [rsi+0x80],rax                             ; W [V]
0x670e776  mov qword ptr [rbp+0x620],0                    ; W clear start [V]
0x670e781  add qword ptr [r15+0x770],0x88                 ; W dst += 0x88 [V]
0x670e78c  jmp 0x670EC68                                  ; [V]
```
Phase F — empty-path call + count compute for group D (0x670e791..0x670e7d8):
```
0x670e791  lea rcx,[r12+0x618]                            ; R start base [V]
0x670e799  call 0x6760E60                                 ; -> sub_6760e60 [V]
0x670e79e  nop                                            ; [V]
0x670e79f  mov rcx,[0x1233E1B0]                           ; [V]
0x670e7a6  mov rax,[rcx]                                  ; [V]
0x670e7a9  mov rax,[rax+0x10]                             ; [V]
0x670e7ad  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670e7b4  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e7ba  nop                                            ; [V]
0x670e7bb  mov qword ptr [rbp+0x3E0],0x8004009            ; W tag [V]
0x670e7c6  mov eax,[r12+0x618]                            ; R end [V]
0x670e7ce  not eax                                        ; ~end [V]
0x670e7d0  add eax,[r12+0x620]                            ; +start [V]
0x670e7d8  mov [rbp+0x426],ax                             ; W count [V]
```
Phase G — flag load + field pack for group D (0x670e7df..0x670e80f):
```
0x670e7df  mov rcx,[0x1233E1B0]                           ; [V]
0x670e7e6  mov rax,[rcx]                                  ; [V]
0x670e7e9  mov rax,[rax+0x10]                             ; [V]
0x670e7ed  mov dl,0x4A                                    ; [V]
0x670e7ef  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e7f5  mov [rbp+0x848],al                             ; W flag [V]
0x670e7fb  lea rcx,[r12+0x648]                            ; R src base [V]
0x670e803  lea rdx,[rbp+0x6A8]                            ; W dst base [V]
0x670e80a  call 0x675FB30                                 ; -> sub_675fb30 [V]
0x670e80f  nop                                            ; [V]
```
Phase H — count compute + flag load for group E (0x670e810..0x670e89b):
```
0x670e810  mov rcx,[0x1233E1B0]                           ; [V]
0x670e817  mov rax,[rcx]                                  ; [V]
0x670e81a  mov rax,[rax+0x10]                             ; [V]
0x670e81e  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670e825  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e82b  nop                                            ; [V]
0x670e82c  mov eax,[r12+0x650]                            ; R end [V]
0x670e834  sub eax,[r12+0x648]                            ; -start [V]
0x670e83c  shr eax,3                                      ; /8 [V]
0x670e83f  imul eax,0xFFFF8E39                            ; *scale [V]
0x670e845  dec eax                                        ; -1 [V]
0x670e847  mov [rbp+0x422],ax                             ; W count [V]
0x670e84e  lea rcx,[r12+0x780]                            ; R src base [V]
0x670e856  lea rdx,[rbp+0x650]                            ; W dst base [V]
0x670e85d  call 0x675F3B0                                 ; -> sub_675f3b0 [V]
0x670e862  nop                                            ; [V]
0x670e863  mov eax,[r12+0x788]                            ; R end [V]
0x670e86b  sub eax,[r12+0x780]                            ; -start [V]
0x670e873  shr eax,3                                      ; /8 [V]
0x670e876  imul eax,0xFFFF8BA3                            ; *scale [V]
0x670e87c  dec eax                                        ; -1 [V]
0x670e87e  mov [rbp+0x408],ax                             ; W count [V]
0x670e885  mov rcx,[0x1233E1B0]                           ; [V]
0x670e88c  mov rax,[rcx]                                  ; [V]
0x670e88f  mov rax,[rax+0x10]                             ; [V]
0x670e893  mov dl,0x4A                                    ; [V]
0x670e895  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e89b  mov [rbp+0x848],al                             ; W flag [V]
```
Phase I — non-empty write path for group E, then empty-path call + count compute for group F (0x670e8a1..0x670e94f):
```
0x670e8a1  mov rsi,[r12+0x770]                            ; R dst ptr [V]
0x670e8a9  cmp rsi,[r12+0x778]                            ; cmp end [V]
0x670e8b1  je 0x670ED08                                   ; to loc_670ed08 (empty path) [V]
0x670e8b7  mov rax,[rbp+0x5C8]                            ; R src [V]
0x670e8be  mov [rsi],rax                                  ; W [V]
0x670e8c1  lea rcx,[rsi+8]                                ; R src+8 [V]
0x670e8c5  lea rdx,[rbp+0x5D0]                            ; W dst+8 [V]
0x670e8cc  call 0xE869FF0                                 ; -> sub_e869ff0 [V]
0x670e8d1  nop                                            ; [V]
0x670e8d2  mov rax,[rbp+0x648]                            ; R [V]
0x670e8d9  mov [rsi+0x80],rax                             ; W [V]
0x670e8e0  mov qword ptr [rbp+0x648],0                    ; W clear start [V]
0x670e8eb  add qword ptr [r12+0x770],0x88                 ; W dst += 0x88 [V]
0x670e8f7  jmp 0x670ED20                                  ; [V]
0x670e8fc  lea rcx,[r12+0x618]                            ; R start base [V]
0x670e904  call 0x6760E60                                 ; -> sub_6760e60 [V]
0x670e909  nop                                            ; [V]
0x670e90a  mov rcx,[0x1233E1B0]                           ; [V]
0x670e911  mov rax,[rcx]                                  ; [V]
0x670e914  mov rax,[rax+0x10]                             ; [V]
0x670e918  movzx edx,byte ptr [rbp+0x848]                 ; [V]
0x670e91f  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x670e925  nop                                            ; [V]
0x670e926  mov eax,[r12+0x618]                            ; R end [V]
0x670e92e  not eax                                        ; ~end [V]
0x670e930  add eax,[r12+0x620]                            ; +start [V]
0x670e938  mov [rbp+0x426],ax                             ; W count [V]
0x670e93f  mov rcx,[0x1233E1B0]                           ; [V]
0x670e946  mov rax,[rcx]                                  ; [V]
0x670e949  mov rax,[rax+0x10]                             ; [V]
0x670e94d  mov dl,0x4A                                    ; [V]
0x670e94f  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]  (range end)
```

Interpretation for range 4: a sequence of write-pack groups. Each group: (1) `call sub_6760e60` empty-path, (2) `call sub_eea6040` via indirect table `[0xF99FFA0]` to load a flag byte into `[rbp+0x848]`, (3) compute count = not(end)+start (or (end-start)/scale-1) stored to `[rbp+0x426]`/`[rbp+0x408]`, (4) `call sub_675fb30`/`sub_675f3b0` field pack, (5) optional non-empty path: compare dst vs end, `je` to empty path, else write 8-byte value + 8-byte trailer via `sub_e869ff0`, clear start, advance dst by 0x88. Repeats across groups A-F with different field offsets (r15+0x618/0x620, r15+0x648/0x650, r15+0x780/0x788, r12+0x618/0x620/0x648/0x650, r12+0x770/0x778/0x5C8/0x5D0/0x648). [I]

## RANGE 5 — 0x670f3cd..0x670f437 [V]
Source: rdis `dis 0x670f3bd 40`; printed addresses cover 0x670f3bd..0x67113bd, so whole range 0x670f3cd..0x670f437 covered [V]. Contains two `(bad)` undecodable bytes at 0x670f3d2 and 0x670f3dd.
```
0x670f3cd  add [rcx-0x73],cl                             ; W a0-0x73 [V]
0x670f3cf  mov [rax+rsi],fs                              ; W [V]
0x670f3d2  (bad)                                         ; undecodable bytes [V]
0x670f3d4  add [rbp+rcx*4-0x7B],cl                       ; W [rbp+rcx*4-0x7B] [V]
0x670f3d8  mov eax,0xE8000005                            ; [V]
0x670f3dd  (bad)                                         ; undecodable bytes [V]
0x670f3df  fdiv st(2),st                                 ; x87 FP [V]
0x670f3e1  nop                                            ; [V]
0x670f3e2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0] [V]
0x670f3e9  mov rax,[rcx]                                 ; [V]
0x670f3ec  mov rax,[rax+0x10]                            ; [V]
0x670f3f0  movzx edx,byte ptr [rbp+0x848]                ; [V]
0x670f3f7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 [V]
0x670f3fd  nop                                            ; [V]
0x670f3fe  mov qword ptr [rbp+0x3E0],0xE407009           ; W tag [V]
0x670f409  mov eax,[r12+0x638]                           ; R end [V]
0x670f411  sub eax,[r12+0x630]                           ; -start [V]
0x670f419  shr eax,2                                     ; /4 [V]
0x670f41c  dec eax                                       ; -1 [V]
0x670f41e  mov [rbp+0x424],ax                            ; W count [V]
0x670f425  mov rcx,r12                                   ; [V]
0x670f428  add rcx,0x108                                 ; [V]
0x670f42f  mov rdx,r13                                   ; [V]
0x670f432  call 0x67693F0                                ; -> sub_67693f0 [V]
0x670f437  nop                                            ; (range end)
```

Interpretation for range 5: misaligned/decode-error region (two `(bad)` undecodable instructions at 0x670f3d2, 0x670f3dd), then count computation via sub_eea6040 flag load, count = (end-start)/4 - 1 stored to [rbp+0x424], tag 0xE407009 stored to [rbp+0x3E0], and a call to sub_67693f0 with rcx=r12+0x108, rdx=r13. [I]

## RANGE 6 — 0x6711cc9..0x6711cc9 [V]
Source: rdis `dis 0x6711cb9 40`; single instruction at 0x6711cc9 printed [V].
```
0x6711cc9  jmp short 0x6711CD8                           ; -> loc_6711cd8 [V]
```

Interpretation for range 6: unconditional jump to loc_6711cd8 (continues into sub_eea6040 flag-load sequence). [I]

## RANGE 7 — 0x6711eed..0x6711fb0 [V]
Source: rdis `dis 0x6711edd 40`; printed addresses cover 0x6711edd..0x6713edd, so whole range 0x6711eed..0x6711fb0 covered [V].
```
0x6711eed  mov rax,[rcx]                                  ; [data_1233e1b0] [V]
0x6711ef0  mov rax,[rax+0x10]                             ; [V]
0x6711ef4  mov dl,0x4A                                    ; [V]
0x6711ef6  call qword ptr [0xF99FFA0]                     ; [data_f99ffa0] = sub_eea6040 [V]
0x6711efc  nop                                            ; [V]
0x6711efd  mov [rbp+0x857],al                             ; W flag [V]
0x6711f03  mov rdx,[r15+0x758]                            ; R idx [V]
0x6711f0a  cmp rdx,[r15+0x760]                            ; cmp end [V]
0x6711f11  je 0x671209D                                  ; to loc_671209d (empty path) [V]
0x6711f17  lea rcx,[rbp+0x6F0]                            ; R src [V]
0x6711f1e  mov eax,[rcx+0x10]                             ; R [V]
0x6711f21  mov [rdx+0x10],eax                             ; W [V]
0x6711f24  movups xmm0,[rcx]                              ; R 16B [V]
0x6711f27  movups [rdx],xmm0                              ; W [V]
0x6711f2a  movzx eax,byte ptr [rbp+0x704]                 ; R [V]
0x6711f31  mov [rdx+0x14],al                              ; W [V]
0x6711f34  movss xmm0,[rbp+0x708]                         ; R [V]
0x6711f3c  movss [rdx+0x18],xmm0                          ; W [V]
0x6711f41  movss xmm0,[rbp+0x70C]                         ; R [V]
0x6711f49  movss [rdx+0x1C],xmm0                          ; W [V]
0x6711f4e  movss xmm0,[rbp+0x710]                         ; R [V]
0x6711f56  movss [rdx+0x20],xmm0                          ; W [V]
0x6711f5b  movss xmm0,[rbp+0x714]                         ; R [V]
0x6711f63  movss [rdx+0x24],xmm0                          ; W [V]
0x6711f68  lea rax,[rbp+0x584]                            ; R src base [V]
0x6711f6f  movups xmm0,[rax+0x194]                        ; R 16B [V]
0x6711f76  movups xmm1,[rax+0x1A4]                        ; R 16B [V]
0x6711f7d  movups xmm2,[rax+0x1B3]                        ; R 16B [V]
0x6711f84  movups [rdx+0x28],xmm0                         ; W [V]
0x6711f88  movups [rdx+0x38],xmm1                         ; W [V]
0x6711f8c  movups [rdx+0x47],xmm2                         ; W [V]
0x6711f90  add qword ptr [r15+0x758],0x58                 ; W idx += 0x58 [V]
0x6711f98  jmp 0x67120B1                                  ; to loc_67120b1 [V]
0x6711f9d  lea rcx,[r15+0x8A0]                            ; R start base [V]
0x6711fa4  lea r8,[rbp+0x750]                             ; R end base [V]
0x6711fab  call 0x1EF6F90                                 ; -> sub_1ef6f90 [V]
0x6711fb0  nop                                            ; (range end)
```

Interpretation for range 7: flag load via sub_eea6040 into [rbp+0x857], compare idx vs end at [r15+0x758]/[r15+0x760], `je` to loc_671209d (empty path), else write-pack: copy src fields (8 bytes + 16-byte vector + scalars at 0x14/0x18/0x1C/0x20/0x24, then 3x16-byte vectors from rbp+0x584+0x194/0x1A4/0x1B3) to dst at rdx (+0x10 through +0x47), advance idx by 0x58, jmp to loc_67120b1. Fall-through at 0x6711f9d calls sub_1ef6f90 with r15+0x8A0/rbp+0x750. [I]

## RANGE 8 — 0x671209d..0x67120b0 [V]
Source: rdis `dis 0x671208d 40`; printed addresses cover 0x671208d..0x671408d, so whole range 0x671209d..0x67120b0 covered [V].
```
0x671209d  lea rcx,[r15+0x750]                            ; R src base [V]
0x67120a4  lea r8,[rbp+0x6F0]                             ; W dst base [V]
0x67120ab  call 0x6760A80                                 ; -> sub_6760a80 [V]
0x67120b0  nop                                            ; (range end)
```

Interpretation for range 8: empty-path write-pack call sub_6760a80 with src=r15+0x750, dst=rbp+0x6F0. [I]

## RANGE 9 — 0x671221a..0x671222a [V]
Source: rdis `dis 0x671220a 40`; printed addresses cover 0x671220a..0x671420a, so whole range 0x671221a..0x671222a covered [V].
```
0x671221a  mov rax,[rcx]                                  ; [data_1233e1b0] [V]
0x671221d  mov rax,[rax+0x10]                             ; [V]
0x6712221  mov dl,0x4A                                    ; [V]
0x6712223  call qword ptr [0xF99FFA0]                     ; [data_f99ffa0] = sub_eea6040 [V]
0x6712229  nop                                            ; [V]
0x671222a  mov [rbp+0x857],al                             ; W flag [V]  (range end)
```

Interpretation for range 9: flag load via sub_eea6040 into [rbp+0x857]. [I]

## RANGE 10 — 0x6712253..0x671225f [V]
Source: rdis `dis 0x6712243 40`; printed addresses cover 0x6712243..0x6714243, so whole range 0x6712253..0x671225f covered [V].
```
0x6712253  lea rcx,[r15+0x858]                            ; R start base [V]
0x671225a  call 0x6760E60                                 ; -> sub_6760e60 [V]
0x671225f  nop                                            ; (range end)
```

Interpretation for range 10: empty-path call sub_6760e60 with start base r15+0x858. [I]

## RANGE 11 — 0x67125a8..0x6712606 [V]
Source: rdis `dis 0x6712598 40`; printed addresses cover 0x6712598..0x6714598, so whole range 0x67125a8..0x6712606 covered [V].
```
0x67125a8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0] [V]
0x67125af  mov rax,[rcx]                                  ; [V]
0x67125b2  mov rax,[rax+0x10]                             ; [V]
0x67125b6  movzx edx,byte ptr [rbp+0x857]                 ; [V]
0x67125bd  call qword ptr [0xF99FFA0]                     ; [data_f99ffa0] = sub_eea6040 [V]
0x67125c3  nop                                            ; [V]
0x67125c4  mov qword ptr [rbp+0x310],0xA007009            ; W tag [V]
0x67125cf  mov eax,[r15+0x770]                            ; R end [V]
0x67125d6  sub eax,[r15+0x768]                            ; -start [V]
0x67125dd  shr eax,3                                      ; /8 [V]
0x67125e0  imul eax,0xFFFFF0F1                            ; *scale [V]
0x67125e6  dec eax                                        ; -1 [V]
0x67125e8  mov [rbp+0x33A],ax                             ; W count [V]
0x67125ef  mov rcx,[0x1233E1B0]                           ; [V]
0x67125f6  mov rax,[rcx]                                  ; [V]
0x67125f9  mov rax,[rax+0x10]                             ; [V]
0x67125fd  mov dl,0x4A                                    ; [V]
0x67125ff  call qword ptr [0xF99FFA0]                     ; sub_eea6040 [V]
0x6712605  nop                                            ; [V]
0x6712606  mov [rbp+0x857],al                             ; W flag [V]  (range end)
```

Interpretation for range 11: flag load via sub_eea6040, tag 0xA007009 stored to [rbp+0x310], count = (end-start)/8*scale - 1 stored to [rbp+0x33A] (using [r15+0x770]-[r15+0x768]), second flag load via sub_eea6040 into [rbp+0x857]. [I]

## RANGE 12 — 0x67126c9..0x67126ce [V]
Source: rdis `dis 0x67126b9 40`; printed addresses cover 0x67126b9..0x67146b9, so whole range 0x67126c9..0x67126ce covered [V].
```
0x67126c9  call 0x6760E60                                ; -> sub_6760e60 [V]
0x67126ce  nop                                            ; (range end)
```

Interpretation for range 12: empty-path call sub_6760e60. [I]

