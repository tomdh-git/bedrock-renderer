# U-E4-H9 (builder 0x6722cb0, function [0x6722cb0..0x672a464))

## NEXT
Phase 29 (0x6728F55..0x672901B, 40 instructions) written. 40 instructions remain in 1 phase; next phase starts at 0x672901B. Continue with `rdis dis 0x672901b 40`. (After that: 0x67291A5..0x672A464 ≈ 50 more instructions in 2 phases; then function end 0x672A464.)

## Gaps (to fill)

### Gap 1: 0x6727a44..0x6727ad3
```
  6727a44  call 0x5ABA5C0                                ; -> sub_5aba5c0
  6727a49  nop                                           
  6727a4a  mov r14,rax                                   
  6727a4d  lea rax,[rbp+0x2A4]                           
  6727a54  movups [rax+0xB4],xmm6                        
  6727a5b  movups [rax+0xA4],xmm6                        
  6727a62  movups [rax+0x94],xmm6                        
  6727a69  movups [rax+0x84],xmm6                        
  6727a70  movups [rax+0x74],xmm6                        
  6727a74  movups [rax+0x64],xmm6                        
  6727a78  movups [rax+0x54],xmm6                        
  6727a7c  movups [rax+0x44],xmm6                        
  6727a80  movups [rax+0x34],xmm6                        
  6727a84  movups [rax+0x24],xmm6                        
  6727a88  movups [rax+0x14],xmm6                        
  6727a8c  movups [rax+4],xmm6                           
  6727a90  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727a97  mov rax,[rcx]                                 
  6727a9a  mov rax,[rax+0x10]                            
  6727a9e  mov dl,0x4A                                   
  6727aa0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727aa6  nop                                           
  6727aa7  mov [rbp+0x827],al                            
  6727aad  mov rdx,[r14+0x8A8]                           
  6727ab4  cmp rdx,[r14+0x8B0]                           
  6727abb  je 0x67289B7                                  ; -> loc_67289b7
  6727ac1  movzx eax,word ptr [rbp+0x728]                
  6727ac8  mov [rdx],ax                                  
  6727acb  add qword ptr [r14+0x8A8],2                   
  6727ad3  jmp 0x67289CB                                 ; -> loc_67289cb
```
// Gap 1 [V]: `call 0x5ABA5C0` (sub_5aba5c0 — the stream's namesake callee seen in phase 11 at 0x67282dc; returns rax in r14 [I]); `nop`; `mov r14,rax`. Zero 0xC0 bytes at [rbp+0x2A4..0x364] with 13× `movups` xmm6 (xmm6 presumed zero) [V]. TLS seq dl=0x4A via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x827],al` [V]. Word append to [r14+0x8A8] buffer (2-byte records, limit [r14+0x8B0]) [V]: `rdx=[r14+0x8A8]`; `cmp rdx,[r14+0x8B0]`; if full `je 0x67289B7` (forward exit block, phase 21's entry) else `movzx eax,word ptr [rbp+0x728]`; `mov [rdx],ax`; `add qword ptr [r14+0x8A8],2`; `jmp 0x67289CB` (phase 21's loc_67289cb).

### Gap 2: 0x6727f8b..0x6727f94
```
  6727f8b  not eax                                       
  6727f8d  add eax,[r14+0x6B0]                           
  6727f94  mov [rbp+0x2DA],ax                            
```
// Gap 2 [V]: completes phase-6's carry-in `mov eax,[r14+0x6A8]` (fold not/add): `not eax`; `add eax,[r14+0x6B0]`; `mov [rbp+0x2DA],ax` (mirrors phase 7's fold → [rbp+0x2DA]).

### Gap 3: 0x67281a5
```
  67281a5  mov rdx,r14                                   
```
// Gap 3 [V]: phase-9's `mov rax,[rcx]`; `mov rax,[rax+0x10]` (TLS slot 2 [0x1233E1A8]) is followed by `mov rdx,r14` — sets rdx=r14 (the destroy-loop base pointer) before phase 10's `call qword ptr [0xF99FFA0]` (sub_eea6040 with rdx=r14 as arg [I]).

### Gap 4: 0x6728242
```
  6728242  cmp r14,rdi                                   
```
// Gap 4 [V]: phase-11's `call 0x4F72824A` (data_4f72824a) returns esi/edi [I]; then `cmp r14,rdi` (r14 = destroy-loop base carried from phase 10's `r14=[rbp+0x7E0]`; rdi = count carried [I]) — if equal skip the destroy loop via `jne short 0x6728259` / `jmp short 0x672827E`.

### Gap 5: 0x6728527
```
  6728527  mov [rbp+0x576],ax                            
```
// Gap 5 [V]: completes phase-15's carry-in fold: `mov eax,[rsi+0x858]` (rsi = r14 base [I]); `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x576],ax` (mirrors phase 14's fold → [rbp+0x58C] / phase 24's → [rbp+0x2B6]; here stored at [rbp+0x576]).

### Gap 6: 0x67286b6
```
  67286b6  mov rdx,[r14+0x2D8]                           
  67286bd  cmp rdx,[r14+0x2E0]                           
  67286c4  je short 0x67286D2                            ; -> loc_67286d2
```
// Gap 6 [V]: cursor load for the [r14+0x2D8] inc-by-1 slot (mirrors phase 5/18): `mov rdx,[r14+0x2D8]`; `cmp rdx,[r14+0x2E0]`; `je short 0x67286D2` (→ loc_67286d2 grow: `lea rcx,[r14+0x2D0]`; `call 0x6760E60`). NOTE: H7's phase-17 listing shows bogus decodes at 0x67286b3..0x67286bb (`or [rax],al` / `add [rcx-0x75],cl` / `xchg esi,eax` / `fadd st,...` / `add [rax],al`) — those addresses are mid-instruction; the real stream is aligned from 0x67286b6 (verified: 0x67286b6+7=0x67286bd matches H7's cmp).

### Gap 7: 0x67288e7..0x67288ee
```
  67288e7  mov eax,[r14+0x8A8]                           
  67288ee  sub eax,[r14+0x8A0]                           
```
// Gap 7 [V]: H7's phase-20 listing shows bogus decodes at 0x67288e6..0x67288ee (`add [rcx-0x75],al`; `xchg [rax+0x41000008],ch`) — those are mid-instruction. Real stream (verified from raw bytes 41 8b 86 a8 08 00 00 / 41 2b 86 a0 08 00 00 at file offset): word-count decode [V] `mov eax,[r14+0x8A8]`; `sub eax,[r14+0x8A0]` (phase 1/13/21 idiom; continues `shr eax,1`; `dec eax`; `mov [rbp+0x2B0],ax` in phase 20).

### Gap 8: 0x6728ce9
```
  6728ce9  mov rdi,[r14+0x770]                           
```
// Gap 8 [V]: H7's phase-25 listing shows `mov esi,0x770` at 0x6728ceb and `cmp rdi,[r14+0x778]` at 0x6728cf0; the missing instruction is the cursor load `mov rdi,[r14+0x770]` (rdi = [r14+0x770] cursor value [I]) — phase 25's record-append path uses rdi as the append pointer.

### Gap 9: 0x6728db8
```
  6728db8  mov rax,[rcx]                                 ; R a0+0x0
```
// Gap 9 [V]: H7's phase-26 listing starts at 0x6728dbb (`mov rax,[rax+0x10]`); the missing instruction is `mov rax,[rcx]` (rcx = [0x1233E1B0] loaded at 0x6728db1) — first hop of the TLS slot-1 deref chain [V].

### Gap 10: 0x6728e9b
```
  6728e9b  jmp 0x6728F55                                 ; -> loc_6728f55
```
// Gap 10 [V]: H7's phase-26 ends at `add qword ptr [r14+0x770],0x88` (0x6728e90); the missing instruction is the forward `jmp 0x6728F55` (rel32 bytes e9 b5 00 00 00, target = 0x6728e9b+5+0xb5 = 0x6728f55) — phase 26's record-append path rejoins the main stream at 0x6728F55 (phase 29's start).

## Phases (0x6728F55..0x672A464)
_pending_