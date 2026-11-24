# Dossier: sub_bc6abd0 ("")

Minecraft Windows 1.26.62.01. Function [0xbc6abd0, 0xbc6aeaf), size 0x2df bytes.
Disassembly source: rdis `fn 0xbc6abd0` / `dis 0xbc6abd0`.
All offsets below are [V] from that listing; nothing is inferred.

## Signature (lifted)

// LIFT-BODY: fill in exact x64 Microsoft ABI signature from rdis fn
extern "C" void sub_bc6abd0(/* LIFT-BODY: exact args */);

## Register / argument map

LIFT-BODY: document register/argument map from prologue analysis

## Phases (instruction-complete, [0xbc6abd0, 0xbc6aeaf))

0xbc6abd0..0xbc6ac33: LIFT-BODY - basic block
  0xbc6abd0  push r15
  0xbc6abd2  push r14
  0xbc6abd4  push r13
  0xbc6abd6  push r12
  0xbc6abd8  push rsi
  0xbc6abd9  push rdi
  0xbc6abda  push rbp
  0xbc6abdb  push rbx
  0xbc6abdc  sub rsp,0x78
  0xbc6abe0  mov rsi,rdx
  0xbc6abe3  mov rbx,rcx
  0xbc6abe6  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  0xbc6abed  xor rax,rsp
  0xbc6abf0  mov [rsp+0x70],rax
  0xbc6abf5  lea rdi,[rcx+0x1EBF300]                       ; R a0+0x1EBF300
  0xbc6abfc  mov rcx,rdi
  0xbc6abff  call 0xBC6AEB0                                ; -> sub_bc6aeb0
  0xbc6ac04  test al,al
  0xbc6ac06  je 0xBC6AE7C                                  ; -> loc_bc6ae7c
  0xbc6ac0c  mov r14d,[rsi]                                ; R a1+0x0
  0xbc6ac0f  mov ebp,[rdi]                                 ; R a0+0x1EBF300+0x0
  0xbc6ac11  test rbp,rbp
  0xbc6ac14  je 0xBC6AE73                                  ; -> loc_bc6ae73
  0xbc6ac1a  mov [rsp+0x4C],r14d
  0xbc6ac1f  lea rdi,[rsi+8]                               ; R a1+0x8
  0xbc6ac23  mov r15d,0xFFFFFFFF
  0xbc6ac29  xor r14d,r14d
  0xbc6ac2c  lea r13,[rsp+0x64]
  0xbc6ac31  jmp short 0xBC6AC4C                           ; -> loc_bc6ac4c
  0xbc6ac33  nop [rax+rax]                                 ; R ret@bc6aeb0+0x0+idx

0xbc6ac40..0xbc6ac46: LIFT-BODY - basic block
  0xbc6ac40  inc r14
  0xbc6ac43  cmp rbp,r14
  0xbc6ac46  je 0xBC6AE4A                                  ; -> loc_bc6ae4a

0xbc6ac4c..0xbc6ad57: LIFT-BODY - basic block
  0xbc6ac4c  mov edx,[rbx+r14*4+0x1EBF704]                 ; R a0+0x1EBF704+idx
  0xbc6ac54  inc edx
  0xbc6ac56  and edx,0xFFFFFFFE
  0xbc6ac59  mov [rsi],edx                                 ; W a1+0x0
  0xbc6ac5b  add rdx,rdi
  0xbc6ac5e  mov r8d,2
  0xbc6ac64  lea rcx,[rsp+0x6E]
  0xbc6ac69  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6ac6e  mov edx,[rsi]                                 ; R a1+0x0
  0xbc6ac70  add edx,2
  0xbc6ac73  mov [rsi],edx                                 ; W a1+0x0
  0xbc6ac75  add rdx,rdi
  0xbc6ac78  mov r8d,1
  0xbc6ac7e  lea rcx,[rsp+0x6D]
  0xbc6ac83  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6ac88  mov edx,[rsi]                                 ; R a1+0x0
  0xbc6ac8a  inc edx
  0xbc6ac8c  mov [rsi],edx                                 ; W a1+0x0
  0xbc6ac8e  add rdx,rdi
  0xbc6ac91  mov r8d,1
  0xbc6ac97  lea rcx,[rsp+0x6C]
  0xbc6ac9c  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6aca1  mov edx,[rsi]                                 ; R a1+0x0
  0xbc6aca3  and edx,0xFFFFFFFE
  0xbc6aca6  add edx,2
  0xbc6aca9  mov [rsi],edx                                 ; W a1+0x0
  0xbc6acab  add rdx,rdi
  0xbc6acae  mov r8d,8
  0xbc6acb4  mov rcx,r13
  0xbc6acb7  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6acbc  mov edx,[rsi]                                 ; R a1+0x0
  0xbc6acbe  add edx,9
  0xbc6acc1  and edx,0xFFFFFFFE
  0xbc6acc4  mov [rsi],edx                                 ; W a1+0x0
  0xbc6acc6  add rdx,rdi
  0xbc6acc9  mov r8d,2
  0xbc6accf  lea rcx,[rsp+0x62]
  0xbc6acd4  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6acd9  mov edx,[rsi]                                 ; R a1+0x0
  0xbc6acdb  add edx,3
  0xbc6acde  and edx,0xFFFFFFFE
  0xbc6ace1  mov [rsi],edx                                 ; W a1+0x0
  0xbc6ace3  add rdx,rdi
  0xbc6ace6  mov r8d,2
  0xbc6acec  lea rcx,[rsp+0x60]
  0xbc6acf1  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6acf6  mov edx,[rsi]                                 ; R a1+0x0
  0xbc6acf8  add edx,3
  0xbc6acfb  and edx,0xFFFFFFFE
  0xbc6acfe  mov [rsi],edx                                 ; W a1+0x0
  0xbc6ad00  add rdx,rdi
  0xbc6ad03  mov r8d,2
  0xbc6ad09  lea rcx,[rsp+0x5E]
  0xbc6ad0e  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6ad13  mov edx,[rsi]                                 ; R a1+0x0
  0xbc6ad15  add edx,9
  0xbc6ad18  and edx,0xFFFFFFF8
  0xbc6ad1b  mov [rsi],edx                                 ; W a1+0x0
  0xbc6ad1d  add rdx,rdi
  0xbc6ad20  mov r8d,8
  0xbc6ad26  lea rcx,[rsp+0x50]
  0xbc6ad2b  call 0xEBCE390                                ; -> sub_ebce390
  0xbc6ad30  add dword ptr [rsi],8                         ; W a1+0x0
  0xbc6ad33  mov r12d,[rbx+r14*4+0x1EBF304]                ; R a0+0x1EBF304+idx
  0xbc6ad3b  cmp r12d,r15d
  0xbc6ad3e  je short 0xBC6AD88                            ; -> loc_bc6ad88
  0xbc6ad40  cmp r15d,0xFFFFFFFF
  0xbc6ad44  je short 0xBC6AD5D                            ; -> loc_bc6ad5d
  0xbc6ad46  mov rcx,[rbx+0x1EBF2D0]                       ; R a0+0x1EBF2D0
  0xbc6ad4d  mov rax,[rcx]                                 ; R *(a0+0x1EBF2D0)+0x0
  0xbc6ad50  mov rax,[rax+0xE8]                            ; R *(*(a0+0x1EBF2D0)+0x0)+0xE8
  0xbc6ad57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

0xbc6ad5d..0xbc6ad85: LIFT-BODY - basic block
  0xbc6ad5d  mov rcx,[rbx+0x1EBF2D0]                       ; R a0+0x1EBF2D0
  0xbc6ad64  movzx r9d,byte ptr [rsp+0x6C]
  0xbc6ad6a  movzx r8d,byte ptr [rsp+0x6D]
  0xbc6ad70  movzx edx,word ptr [rsp+0x6E]
  0xbc6ad75  mov rax,[rcx]                                 ; R *(a0+0x1EBF2D0)+0x0
  0xbc6ad78  mov rax,[rax+0xD8]                            ; R *(*(a0+0x1EBF2D0)+0x0)+0xD8
  0xbc6ad7f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  0xbc6ad85  mov r15d,r12d

0xbc6ad88..0xbc6ae08: LIFT-BODY - basic block
  0xbc6ad88  mov rcx,[rbx+0x1EBF2D0]                       ; R a0+0x1EBF2D0
  0xbc6ad8f  mov r10,[rsp+0x50]
  0xbc6ad94  movzx r11d,word ptr [rsp+0x5E]
  0xbc6ad9a  movzx r12d,word ptr [rsp+0x60]
  0xbc6ada0  movzx r13d,word ptr [rsp+0x62]
  0xbc6ada6  movzx r9d,byte ptr [rsp+0x6C]
  0xbc6adac  movzx r8d,byte ptr [rsp+0x6D]
  0xbc6adb2  movzx edx,word ptr [rsp+0x6E]
  0xbc6adb7  mov rax,[rcx]                                 ; R *(a0+0x1EBF2D0)+0x0
  0xbc6adba  mov rax,[rax+0xE0]                            ; R *(*(a0+0x1EBF2D0)+0x0)+0xE0
  0xbc6adc1  mov [rsp+0x40],r10
  0xbc6adc6  mov [rsp+0x38],r11w
  0xbc6adcc  mov [rsp+0x30],r12w
  0xbc6add2  mov [rsp+0x28],r13w
  0xbc6add8  lea r13,[rsp+0x64]
  0xbc6addd  mov [rsp+0x20],r13
  0xbc6ade2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  0xbc6ade8  mov r12,[rsp+0x50]
  0xbc6aded  mov rcx,[r12]
  0xbc6adf1  lea rax,[r12+0x10]
  0xbc6adf6  cmp rcx,rax
  0xbc6adf9  je short 0xBC6AE0E                            ; -> loc_bc6ae0e
  0xbc6adfb  mov rax,[rax]
  0xbc6adfe  test rax,rax
  0xbc6ae01  je short 0xBC6AE0E                            ; -> loc_bc6ae0e
  0xbc6ae03  mov rdx,[r12+0x18]
  0xbc6ae08  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

0xbc6ae0e..0xbc6ae45: LIFT-BODY - basic block
  0xbc6ae0e  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  0xbc6ae15  test rcx,rcx
  0xbc6ae18  je 0xBC6AC40                                  ; -> loc_bc6ac40
  0xbc6ae1e  mov rax,[rcx]
  0xbc6ae21  mov rax,[rax+8]
  0xbc6ae25  mov dword ptr [rsp+0x28],0
  0xbc6ae2d  mov qword ptr [rsp+0x20],0
  0xbc6ae36  mov rdx,r12
  0xbc6ae39  xor r8d,r8d
  0xbc6ae3c  xor r9d,r9d
  0xbc6ae3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  0xbc6ae45  jmp 0xBC6AC40                                 ; -> loc_bc6ac40

0xbc6ae4a..0xbc6ae6d: LIFT-BODY - basic block
  0xbc6ae4a  cmp r15d,0xFFFFFFFF
  0xbc6ae4e  lea rdi,[rbx+0x1EBF300]
  0xbc6ae55  mov r14d,[rsp+0x4C]
  0xbc6ae5a  je short 0xBC6AE73                            ; -> loc_bc6ae73
  0xbc6ae5c  mov rcx,[rbx+0x1EBF2D0]
  0xbc6ae63  mov rax,[rcx]
  0xbc6ae66  mov rax,[rax+0xE8]
  0xbc6ae6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

0xbc6ae73..0xbc6ae79: LIFT-BODY - basic block
  0xbc6ae73  mov dword ptr [rdi],0
  0xbc6ae79  mov [rsi],r14d

0xbc6ae7c..0xbc6aea0: LIFT-BODY - basic block
  0xbc6ae7c  mov rax,[rsp+0x70]
  0xbc6ae81  xor rax,rsp
  0xbc6ae84  mov rcx,[0x1230A0C0]                          ; [data_1230a0c0]
  0xbc6ae8b  cmp rcx,rax
  0xbc6ae8e  jne short 0xBC6AEA1                           ; -> loc_bc6aea1
  0xbc6ae90  add rsp,0x78
  0xbc6ae94  pop rbx
  0xbc6ae95  pop rbp
  0xbc6ae96  pop rdi
  0xbc6ae97  pop rsi
  0xbc6ae98  pop r12
  0xbc6ae9a  pop r13
  0xbc6ae9c  pop r14
  0xbc6ae9e  pop r15
  0xbc6aea0  ret

0xbc6aea1..0xbc6aeae: LIFT-BODY - basic block
  0xbc6aea1  mov rcx,[rsp+0x70]
  0xbc6aea6  xor rcx,rsp
  0xbc6aea9  call 0xE951550                                ; -> sub_e951550
  0xbc6aeae  int3

## Struct fields touched

LIFT-BODY: list every struct field read/written with offset, size, R/W, meaning, tag

## Callees

| 0xbc6aeb0 (sub_bc6aeb0) | lift set | call 0xBC6AEB0                                ; -> sub_bc6aeb0 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xbc6ad57 (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xbc6ad7f (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xbc6ade2 (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xbc6ae08 (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xbc6ae3f (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xbc6ae6d (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xe951550 (sub_e951550) | boundary (TBD: classify in native_boundary.tsv) | call 0xE951550                                ; -> sub_e951550 | [V] |

## Verbatim instruction quotes (all calls in the function)

0xbc6abff  call 0xBC6AEB0                                ; -> sub_bc6aeb0
0xbc6ac69  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ac83  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ac9c  call 0xEBCE390                                ; -> sub_ebce390
0xbc6acb7  call 0xEBCE390                                ; -> sub_ebce390
0xbc6acd4  call 0xEBCE390                                ; -> sub_ebce390
0xbc6acf1  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ad0e  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ad2b  call 0xEBCE390                                ; -> sub_ebce390
0xbc6ad57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ad7f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ade2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ae08  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ae3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6ae6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc6aea9  call 0xE951550                                ; -> sub_e951550

## OPEN questions

LIFT-BODY: list unknowns

## Reversed source (complete)

// Reversed from the disassembly of [0xbc6abd0, 0xbc6aeaf), size 0x2df, Minecraft Windows
// 1.26.62.01 (rdis dis output). Every statement carries the instruction range it implements;
// every call instruction is quoted verbatim (pure lines below). Types: native::<area>::
//
// LIFT-BODY: fill in struct definitions and data references [V]
//

extern "C" void sub_bc6abd0(/* LIFT-BODY: exact args */) {
    // 0xbc6abd0..0xbc6ac33
    0xbc6abff  call 0xBC6AEB0                                ; -> sub_bc6aeb0
    LIFT-BODY;  // implement basic block 0xbc6abd0..0xbc6ac33

    // 0xbc6ac40..0xbc6ac46
    LIFT-BODY;  // implement basic block 0xbc6ac40..0xbc6ac46

    // 0xbc6ac4c..0xbc6ad57
    0xbc6ac69  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ac83  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ac9c  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6acb7  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6acd4  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6acf1  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ad0e  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ad2b  call 0xEBCE390                                ; -> sub_ebce390
    0xbc6ad57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ac4c..0xbc6ad57

    // 0xbc6ad5d..0xbc6ad85
    0xbc6ad7f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ad5d..0xbc6ad85

    // 0xbc6ad88..0xbc6ae08
    0xbc6ade2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    0xbc6ae08  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ad88..0xbc6ae08

    // 0xbc6ae0e..0xbc6ae45
    0xbc6ae3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ae0e..0xbc6ae45

    // 0xbc6ae4a..0xbc6ae6d
    0xbc6ae6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xbc6ae4a..0xbc6ae6d

    // 0xbc6ae73..0xbc6ae79
    LIFT-BODY;  // implement basic block 0xbc6ae73..0xbc6ae79

    // 0xbc6ae7c..0xbc6aea0
    LIFT-BODY;  // implement basic block 0xbc6ae7c..0xbc6aea0

    // 0xbc6aea1..0xbc6aeae
    0xbc6aea9  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbc6aea1..0xbc6aeae

}

// Calls out of lifted code:
//   sub_bc6aeb0 (0xbc6aeb0, lift set) - call 0xBC6AEB0                                ; -> sub_bc6aeb0
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv