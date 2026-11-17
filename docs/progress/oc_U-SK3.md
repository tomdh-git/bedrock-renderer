## NEXT
DONE

# Unit U-Sk3 — instruction slice loc_6b85697..6b85a00

Slice: skinned clone 0x6b84e60, chunk 3 of 9, RVAs 6b85697..6b85a00.
Source listing: docs/progress/_part_Sk3.txt. Every instruction below is quoted verbatim from that listing (two spaces after the address, comments preserved), so the slice is covered instruction-completely with nothing skipped. The listing is split into phases of at most 40 instructions each.

## Phase 1: 6b85697..6b85722
Argument setup for sub_4e00090: edx = 0x128 + [rsi+0x20], rcx = [rsi+0x10], r8 = &[rbp+0x60], r9d = r14d, then call 0x4E00090; if r15 = [rbp+0x68] is non-zero, lock-decrement the dword at [r15+8] and, when it reaches zero, run the release path through IAT slot [0xF99FFA0] (sub_eea6040) with a lock-decrement of [r15+0xC] between the two calls; loc_6b856e7 then increments r14d.
0x6b85697  mov edx,0x128
0x6b8569c  add rdx,[rsi+0x20]
0x6b856a0  mov rcx,[rsi+0x10]
0x6b856a4  lea r8,[rbp+0x60]
0x6b856a8  mov r9d,r14d
0x6b856ab  call 0x4E00090                                ; -> sub_4e00090
0x6b856b0  nop
0x6b856b1  mov r15,[rbp+0x68]
0x6b856b5  test r15,r15
0x6b856b8  je short 0x6B856E7                            ; -> loc_6b856e7
0x6b856ba  lock dec dword ptr [r15+8]
0x6b856bf  jne short 0x6B856E7                           ; -> loc_6b856e7
0x6b856c1  mov rax,[r15]
0x6b856c4  mov rax,[rax]
0x6b856c7  mov rcx,r15
0x6b856ca  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b856d0  lock dec dword ptr [r15+0xC]
0x6b856d5  jne short 0x6B856E7                           ; -> loc_6b856e7
0x6b856d7  mov rax,[r15]
0x6b856da  mov rax,[rax+8]
0x6b856de  mov rcx,r15
0x6b856e1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b856e7  inc r14d
0x6b856ea  mov rax,[rdi+0x18]
0x6b856ee  test rax,rax
0x6b856f1  je 0x6B857FD                                  ; -> loc_6b857fd
0x6b856f7  mov r15,[rax]
0x6b856fa  test r15,r15
0x6b856fd  je 0x6B857FD                                  ; -> loc_6b857fd
0x6b85703  mov eax,[0x128D8FC8]                          ; [data_128d8fc8]
0x6b85709  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6b8570f  mov rdx,gs:[0x58]
0x6b85718  mov rcx,[rdx+rcx*8]
0x6b8571c  cmp eax,[rcx+4]
0x6b85722  jg 0x6B86881                                  ; -> loc_6b86881

## Phase 2: 6b85728..6b85767
loc_6b85728 lock-increments the word refcount at [r15+0x10] and tests bit0 of byte [r15+0x12] (je to loc_6b857fd if clear); otherwise reload rax=[rdi+0x18], zero xmm0 and store 16 bytes to [rbp+0x60], rcx = word [rcx+0x10] when [rax] is non-zero, then rcx = [rax+8] with lock-increment of the dword at [rcx+8] when non-zero else xor ecx,ecx at loc_6b85767.
0x6b85728  lock inc word ptr [r15+0x10]
0x6b8572e  movzx eax,byte ptr [r15+0x12]
0x6b85733  test al,1
0x6b85735  je 0x6B857FD                                  ; -> loc_6b857fd
0x6b8573b  mov rax,[rdi+0x18]
0x6b8573f  pxor xmm0,xmm0
0x6b85743  movdqa [rbp+0x60],xmm0
0x6b85748  mov rcx,[rax]
0x6b8574b  test rcx,rcx
0x6b8574e  je short 0x6B85754                            ; -> loc_6b85754
0x6b85750  movzx ecx,word ptr [rcx+0x10]
0x6b85754  mov rcx,[rax+8]
0x6b85758  test rcx,rcx
0x6b8575b  je short 0x6B85767                            ; -> loc_6b85767
0x6b8575d  lock inc dword ptr [rcx+8]
0x6b85761  mov rcx,[rax+8]
0x6b85765  jmp short 0x6B85769                           ; -> loc_6b85769
0x6b85767  xor ecx,ecx

## Phase 3: 6b85769..6b857a4
Store the pointer chain into the output slot: rax = [rax], [rbp+0x60] = rax, then swap [rbp+0x68] to rcx; if the old r15 = [rbp+0x68] is non-zero, lock-decrement [r15+8] and, on reaching zero, release via the same two-call IAT path through [0xF99FFA0] (sub_eea6040) with a lock-decrement of [r15+0xC] in between.
0x6b85769  mov rax,[rax]
0x6b8576c  mov [rbp+0x60],rax
0x6b85770  mov r15,[rbp+0x68]
0x6b85774  mov [rbp+0x68],rcx
0x6b85778  test r15,r15
0x6b8577b  je short 0x6B857AA                            ; -> loc_6b857aa
0x6b8577d  lock dec dword ptr [r15+8]
0x6b85782  jne short 0x6B857AA                           ; -> loc_6b857aa
0x6b85784  mov rax,[r15]
0x6b85787  mov rax,[rax]
0x6b8578a  mov rcx,r15
0x6b8578d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b85793  lock dec dword ptr [r15+0xC]
0x6b85798  jne short 0x6B857AA                           ; -> loc_6b857aa
0x6b8579a  mov rax,[r15]
0x6b8579d  mov rax,[rax+8]
0x6b857a1  mov rcx,r15
0x6b857a4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

## Phase 4: 6b857aa..6b857fa
Repeats the Phase 1 call sequence (edx = 0x128 + [rsi+0x20], rcx = [rsi+0x10], r8 = &[rbp+0x60], r9d = r14d, call 0x4E00090), then releases [rbp+0x68] with the same lock-decrement [r15+8] / IAT release sequence; loc_6b857fa increments r14d.
0x6b857aa  mov edx,0x128
0x6b857af  add rdx,[rsi+0x20]
0x6b857b3  mov rcx,[rsi+0x10]
0x6b857b7  lea r8,[rbp+0x60]
0x6b857bb  mov r9d,r14d
0x6b857be  call 0x4E00090                                ; -> sub_4e00090
0x6b857c3  nop
0x6b857c4  mov r15,[rbp+0x68]
0x6b857c8  test r15,r15
0x6b857cb  je short 0x6B857FA                            ; -> loc_6b857fa
0x6b857cd  lock dec dword ptr [r15+8]
0x6b857d2  jne short 0x6B857FA                           ; -> loc_6b857fa
0x6b857d4  mov rax,[r15]
0x6b857d7  mov rax,[rax]
0x6b857da  mov rcx,r15
0x6b857dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b857e3  lock dec dword ptr [r15+0xC]
0x6b857e8  jne short 0x6B857FA                           ; -> loc_6b857fa
0x6b857ea  mov rax,[r15]
0x6b857ed  mov rax,[rax+8]
0x6b857f1  mov rcx,r15
0x6b857f4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b857fa  inc r14d

## Phase 5: 6b857fd..6b85835
rax = [rdi+0x28] with null checks on the pointer and its first qword (je to loc_6b85910); r15 = [rax]; refresh the tick by loading data_128d8fc8 into eax, data_128767c8 into ecx, rdx = gs:[0x58], rcx = [rdx+rcx*8], then cmp eax,[rcx+4] with jg to loc_6b868ed when greater.
0x6b857fd  mov rax,[rdi+0x28]
0x6b85801  test rax,rax
0x6b85804  je 0x6B85910                                  ; -> loc_6b85910
0x6b8580a  mov r15,[rax]
0x6b8580d  test r15,r15
0x6b85810  je 0x6B85910                                  ; -> loc_6b85910
0x6b85816  mov eax,[0x128D8FC8]                          ; [data_128d8fc8]
0x6b8581c  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6b85822  mov rdx,gs:[0x58]
0x6b8582b  mov rcx,[rdx+rcx*8]
0x6b8582f  cmp eax,[rcx+4]
0x6b85835  jg 0x6B868ED                                  ; -> loc_6b868ed

## Phase 6: 6b8583b..6b8587a
Same object-init sequence as Phase 2 on the [rdi+0x28] object: lock-increment the word refcount at [r15+0x10], test bit0 of byte [r15+0x12] (je to loc_6b85910 if clear), reload rax=[rdi+0x28], zero xmm0 and store 16 bytes to [rbp+0x60], rcx = word [rcx+0x10] when [rax] is non-zero, then rcx = [rax+8] with lock-increment of the dword at [rcx+8] when non-zero else xor ecx,ecx at loc_6b8587a.
0x6b8583b  lock inc word ptr [r15+0x10]
0x6b85841  movzx eax,byte ptr [r15+0x12]
0x6b85846  test al,1
0x6b85848  je 0x6B85910                                  ; -> loc_6b85910
0x6b8584e  mov rax,[rdi+0x28]
0x6b85852  pxor xmm0,xmm0
0x6b85856  movdqa [rbp+0x60],xmm0
0x6b8585b  mov rcx,[rax]
0x6b8585e  test rcx,rcx
0x6b85861  je short 0x6B85867                            ; -> loc_6b85867
0x6b85863  movzx ecx,word ptr [rcx+0x10]
0x6b85867  mov rcx,[rax+8]
0x6b8586b  test rcx,rcx
0x6b8586e  je short 0x6B8587A                            ; -> loc_6b8587a
0x6b85870  lock inc dword ptr [rcx+8]
0x6b85874  mov rcx,[rax+8]
0x6b85878  jmp short 0x6B8587C                           ; -> loc_6b8587c
0x6b8587a  xor ecx,ecx

## Phase 7: 6b8587c..6b858b7
Same store/swap/release as Phase 3: rax = [rax], [rbp+0x60] = rax, [rbp+0x68] = rcx, then lock-decrement [r15+8] on the old r15 = [rbp+0x68] and, on zero, release via the two-call IAT path through [0xF99FFA0] (sub_eea6040) with a lock-decrement of [r15+0xC] between the calls.
0x6b8587c  mov rax,[rax]
0x6b8587f  mov [rbp+0x60],rax
0x6b85883  mov r15,[rbp+0x68]
0x6b85887  mov [rbp+0x68],rcx
0x6b8588b  test r15,r15
0x6b8588e  je short 0x6B858BD                            ; -> loc_6b858bd
0x6b85890  lock dec dword ptr [r15+8]
0x6b85895  jne short 0x6B858BD                           ; -> loc_6b858bd
0x6b85897  mov rax,[r15]
0x6b8589a  mov rax,[rax]
0x6b8589d  mov rcx,r15
0x6b858a0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b858a6  lock dec dword ptr [r15+0xC]
0x6b858ab  jne short 0x6B858BD                           ; -> loc_6b858bd
0x6b858ad  mov rax,[r15]
0x6b858b0  mov rax,[rax+8]
0x6b858b4  mov rcx,r15
0x6b858b7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

## Phase 8: 6b858bd..6b8590d
Repeats the Phase 4 call+release sequence (edx = 0x128 + [rsi+0x20], rcx = [rsi+0x10], r8 = &[rbp+0x60], r9d = r14d, call 0x4E00090; release [rbp+0x68]); loc_6b8590d increments r14d.
0x6b858bd  mov edx,0x128
0x6b858c2  add rdx,[rsi+0x20]
0x6b858c6  mov rcx,[rsi+0x10]
0x6b858ca  lea r8,[rbp+0x60]
0x6b858ce  mov r9d,r14d
0x6b858d1  call 0x4E00090                                ; -> sub_4e00090
0x6b858d6  nop
0x6b858d7  mov r15,[rbp+0x68]
0x6b858db  test r15,r15
0x6b858de  je short 0x6B8590D                            ; -> loc_6b8590d
0x6b858e0  lock dec dword ptr [r15+8]
0x6b858e5  jne short 0x6B8590D                           ; -> loc_6b8590d
0x6b858e7  mov rax,[r15]
0x6b858ea  mov rax,[rax]
0x6b858ed  mov rcx,r15
0x6b858f0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b858f6  lock dec dword ptr [r15+0xC]
0x6b858fb  jne short 0x6B8590D                           ; -> loc_6b8590d
0x6b858fd  mov rax,[r15]
0x6b85900  mov rax,[rax+8]
0x6b85904  mov rcx,r15
0x6b85907  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b8590d  inc r14d

## Phase 9: 6b85910..6b85948
rax = [rdi+0x30] with null checks on the pointer and its first qword (je to loc_6b85a20); r15 = [rax]; same tick refresh as Phase 5 (data_128d8fc8, data_128767c8, rdx = gs:[0x58], rcx = [rdx+rcx*8], cmp eax,[rcx+4]) with jg to loc_6b86959 when greater.
0x6b85910  mov rax,[rdi+0x30]
0x6b85914  test rax,rax
0x6b85917  je 0x6B85A20                                  ; -> loc_6b85a20
0x6b8591d  mov r15,[rax]
0x6b85920  test r15,r15
0x6b85923  je 0x6B85A20                                  ; -> loc_6b85a20
0x6b85929  mov eax,[0x128D8FC8]                          ; [data_128d8fc8]
0x6b8592f  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6b85935  mov rdx,gs:[0x58]
0x6b8593e  mov rcx,[rdx+rcx*8]
0x6b85942  cmp eax,[rcx+4]
0x6b85948  jg 0x6B86959                                  ; -> loc_6b86959

## Phase 10: 6b8594e..6b8598d
Same object-init sequence as Phases 2/6 on the [rdi+0x30] object: lock-increment the word refcount at [r15+0x10], test bit0 of byte [r15+0x12] (je to loc_6b85a20 if clear), reload rax=[rdi+0x30], zero xmm0 and store 16 bytes to [rbp+0x60], rcx = word [rcx+0x10] when [rax] is non-zero, then rcx = [rax+8] with lock-increment of the dword at [rcx+8] when non-zero else xor ecx,ecx at loc_6b8598d.
0x6b8594e  lock inc word ptr [r15+0x10]
0x6b85954  movzx eax,byte ptr [r15+0x12]
0x6b85959  test al,1
0x6b8595b  je 0x6B85A20                                  ; -> loc_6b85a20
0x6b85961  mov rax,[rdi+0x30]
0x6b85965  pxor xmm0,xmm0
0x6b85969  movdqa [rbp+0x60],xmm0
0x6b8596e  mov rcx,[rax]
0x6b85971  test rcx,rcx
0x6b85974  je short 0x6B8597A                            ; -> loc_6b8597a
0x6b85976  movzx ecx,word ptr [rcx+0x10]
0x6b8597a  mov rcx,[rax+8]
0x6b8597e  test rcx,rcx
0x6b85981  je short 0x6B8598D                            ; -> loc_6b8598d
0x6b85983  lock inc dword ptr [rcx+8]
0x6b85987  mov rcx,[rax+8]
0x6b8598b  jmp short 0x6B8598F                           ; -> loc_6b8598f
0x6b8598d  xor ecx,ecx

## Phase 11: 6b8598f..6b859ca
Same store/swap/release as Phases 3/7: rax = [rax], [rbp+0x60] = rax, [rbp+0x68] = rcx, then lock-decrement [r15+8] on the old r15 = [rbp+0x68] and, on zero, release via the two-call IAT path through [0xF99FFA0] (sub_eea6040) with a lock-decrement of [r15+0xC] between the calls.
0x6b8598f  mov rax,[rax]
0x6b85992  mov [rbp+0x60],rax
0x6b85996  mov r15,[rbp+0x68]
0x6b8599a  mov [rbp+0x68],rcx
0x6b8599e  test r15,r15
0x6b859a1  je short 0x6B859D0                            ; -> loc_6b859d0
0x6b859a3  lock dec dword ptr [r15+8]
0x6b859a8  jne short 0x6B859D0                           ; -> loc_6b859d0
0x6b859aa  mov rax,[r15]
0x6b859ad  mov rax,[rax]
0x6b859b0  mov rcx,r15
0x6b859b3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6b859b9  lock dec dword ptr [r15+0xC]
0x6b859be  jne short 0x6B859D0                           ; -> loc_6b859d0
0x6b859c0  mov rax,[r15]
0x6b859c3  mov rax,[rax+8]
0x6b859c7  mov rcx,r15
0x6b859ca  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

## Phase 12: 6b859d0..6b85a00
A third sub_4e00090 call sequence (edx = 0x128 + [rsi+0x20], rcx = [rsi+0x10], r8 = &[rbp+0x60], r9d = r14d), then r14 = [rbp+0x68] with test; if non-zero, lock-decrement the dword at [r14+8] and, on reaching zero, the release starts: rax = [r14], rax = [rax], rcx = r14 — the slice ends at 6b85a00 before the call.
0x6b859d0  mov edx,0x128
0x6b859d5  add rdx,[rsi+0x20]
0x6b859d9  mov rcx,[rsi+0x10]
0x6b859dd  lea r8,[rbp+0x60]
0x6b859e1  mov r9d,r14d
0x6b859e4  call 0x4E00090                                ; -> sub_4e00090
0x6b859e9  nop
0x6b859ea  mov r14,[rbp+0x68]
0x6b859ee  test r14,r14
0x6b859f1  je short 0x6B85A20                            ; -> loc_6b85a20
0x6b859f3  lock dec dword ptr [r14+8]
0x6b859f8  jne short 0x6B85A20                           ; -> loc_6b85a20
0x6b859fa  mov rax,[r14]
0x6b859fd  mov rax,[rax]
0x6b85a00  mov rcx,r14

## Field map — every [reg+off] field stored or loaded in the slice
One row per distinct offset, all sites listed. Direction: R = load, W = store, RW = atomic read-modify-write (lock inc/dec), A = lea address computation only (no memory load/store). Sizes come from the instruction. Meaning is given only where the instruction itself shows it (lock inc/dec = counted reference, test al,1 = flag bit test), else '-'.

| offset | size | direction | verbatim instruction line(s) | meaning |
|---|---|---|---|---|
| rsi+0x20 | 8 B | R | 6b8569c  add rdx,[rsi+0x20]; 6b857af  add rdx,[rsi+0x20]; 6b858c2  add rdx,[rsi+0x20]; 6b859d5  add rdx,[rsi+0x20] | - |
| rsi+0x10 | 8 B | R | 6b856a0  mov rcx,[rsi+0x10]; 6b857b3  mov rcx,[rsi+0x10]; 6b858c6  mov rcx,[rsi+0x10]; 6b859d9  mov rcx,[rsi+0x10] | - |
| rbp+0x60 | 16 B movdqa / 8 B mov | W (movdqa/mov stores); A (lea address only) | 6b856a4  lea r8,[rbp+0x60]; 6b85743  movdqa [rbp+0x60],xmm0; 6b8576c  mov [rbp+0x60],rax; 6b857b7  lea r8,[rbp+0x60]; 6b85856  movdqa [rbp+0x60],xmm0; 6b8587f  mov [rbp+0x60],rax; 6b858ca  lea r8,[rbp+0x60]; 6b85969  movdqa [rbp+0x60],xmm0; 6b85992  mov [rbp+0x60],rax; 6b859dd  lea r8,[rbp+0x60] | - |
| rbp+0x68 | 8 B | R/W | 6b856b1  mov r15,[rbp+0x68]; 6b85770  mov r15,[rbp+0x68]; 6b85774  mov [rbp+0x68],rcx; 6b857c4  mov r15,[rbp+0x68]; 6b85883  mov r15,[rbp+0x68]; 6b85887  mov [rbp+0x68],rcx; 6b85996  mov r15,[rbp+0x68]; 6b8599a  mov [rbp+0x68],rcx; 6b859ea  mov r14,[rbp+0x68] | - |
| r15+8 | 4 B | RW | 6b856ba  lock dec dword ptr [r15+8]; 6b8577d  lock dec dword ptr [r15+8]; 6b857cd  lock dec dword ptr [r15+8]; 6b85890  lock dec dword ptr [r15+8]; 6b858e0  lock dec dword ptr [r15+8]; 6b859a3  lock dec dword ptr [r15+8] | refcount dword (lock inc/dec) |
| r15+0xC | 4 B | RW | 6b856d0  lock dec dword ptr [r15+0xC]; 6b85793  lock dec dword ptr [r15+0xC]; 6b858a6  lock dec dword ptr [r15+0xC]; 6b858f6  lock dec dword ptr [r15+0xC]; 6b859b9  lock dec dword ptr [r15+0xC] | refcount dword (lock dec) |
| r15+0 | 8 B | R | 6b856c1  mov rax,[r15]; 6b85784  mov rax,[r15]; 6b85897  mov rax,[r15]; 6b858ea  mov rax,[r15]; 6b859aa  mov rax,[r15] | - |
| rax+0 | 8 B | R | 6b856c4  mov rax,[rax]; 6b856f7  mov r15,[rax]; 6b85769  mov rax,[rax]; 6b85787  mov rax,[rax]; 6b8580a  mov r15,[rax]; 6b8587c  mov rax,[rax]; 6b8589a  mov rax,[rax]; 6b858ed  mov rax,[rax]; 6b8591d  mov r15,[rax]; 6b859ad  mov rax,[rax]; 6b8598f  mov rax,[rax]; 6b859fd  mov rax,[rax] | - |
| rax+8 | 8 B | R | 6b856da  mov rax,[rax+8]; 6b85754  mov rcx,[rax+8]; 6b85761  mov rcx,[rax+8]; 6b8579d  mov rax,[rax+8]; 6b85867  mov rcx,[rax+8]; 6b85874  mov rcx,[rax+8]; 6b858b0  mov rax,[rax+8]; 6b85900  mov rax,[rax+8]; 6b8597a  mov rcx,[rax+8]; 6b85987  mov rcx,[rax+8]; 6b859c3  mov rax,[rax+8] | - |
| r15+0x10 | 2 B | RW | 6b85728  lock inc word ptr [r15+0x10]; 6b8583b  lock inc word ptr [r15+0x10]; 6b8594e  lock inc word ptr [r15+0x10] | refcount word (lock inc word) |
| r15+0x12 | 1 B | R | 6b8572e  movzx eax,byte ptr [r15+0x12]; 6b85841  movzx eax,byte ptr [r15+0x12]; 6b85954  movzx eax,byte ptr [r15+0x12] | flag byte (bit0 tested: test al,1) |
| rcx+0x10 | 2 B | R | 6b85750  movzx ecx,word ptr [rcx+0x10]; 6b85863  movzx ecx,word ptr [rcx+0x10]; 6b85976  movzx ecx,word ptr [rcx+0x10] | - |
| rcx+8 | 4 B | RW | 6b8575d  lock inc dword ptr [rcx+8]; 6b85870  lock inc dword ptr [rcx+8]; 6b85983  lock inc dword ptr [rcx+8] | refcount dword (lock inc dword) |
| rdi+0x18 | 8 B | R | 6b856e7  mov rax,[rdi+0x18]; 6b8573b  mov rax,[rdi+0x18]; 6b85961  mov rax,[rdi+0x18] | - |
| rcx+4 | 4 B | R | 6b8571c  cmp eax,[rcx+4]; 6b8582f  cmp eax,[rcx+4]; 6b85942  cmp eax,[rcx+4] | - |
| rdi+0x28 | 8 B | R | 6b857fd  mov rax,[rdi+0x28]; 6b8584e  mov rax,[rdi+0x28] | - |
| rdi+0x30 | 8 B | R | 6b85910  mov rax,[rdi+0x30] | - |
| r14+0 | 8 B | R | 6b859fa  mov rax,[r14] | - |

## TOOL REQUESTS
None
