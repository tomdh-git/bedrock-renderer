# Dossier: sub_e82dcc0 ("")

Minecraft Windows 1.26.62.01. Function [0xe82dcc0, 0xe82de8f), size 0x1cf bytes.
Disassembly source: rdis `fn 0xe82dcc0` / `dis 0xe82dcc0`.
All offsets below are [V] from that listing; nothing is inferred.

## Signature (lifted)

// LIFT-BODY: fill in exact x64 Microsoft ABI signature from rdis fn
extern "C" void sub_e82dcc0(/* LIFT-BODY: exact args */);

## Register / argument map

LIFT-BODY: document register/argument map from prologue analysis

## Phases (instruction-complete, [0xe82dcc0, 0xe82de8f))

0xe82dcc0..0xe82dd31: LIFT-BODY - basic block
  0xe82dcc0  push rsi
  0xe82dcc1  sub rsp,0x50
  0xe82dcc5  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  0xe82dccc  xor rax,rsp
  0xe82dccf  mov [rsp+0x48],rax
  0xe82dcd4  cmp byte ptr [rcx+0x13],1                     ; R a0+0x13
  0xe82dcd8  movzx eax,word ptr [rcx+0xA]                  ; R a0+0xA
  0xe82dcdc  movzx ecx,ax
  0xe82dcdf  mov r9,[rdx+0x30]                             ; R a1+0x30
  0xe82dce3  jne short 0xE82DD33                           ; -> loc_e82dd33
  0xe82dce5  cmp ecx,0xFFF
  0xe82dceb  ja 0xE82DE67                                  ; -> loc_e82de67
  0xe82dcf1  mov r10d,ecx
  0xe82dcf4  shr r10d,6
  0xe82dcf8  mov r11,[rdx+r10*8+0x48]                      ; R a1+0x48+idx
  0xe82dcfd  mov esi,1
  0xe82dd02  shl rsi,cl
  0xe82dd05  bt r11,rcx
  0xe82dd09  jae 0xE82DD97                                 ; -> loc_e82dd97
  0xe82dd0f  mov eax,[rdx+rcx*8+0x24C]                     ; R a1+0x24C+idx
  0xe82dd16  cmp eax,r8d
  0xe82dd19  jne 0xE82DE03                                 ; -> loc_e82de03
  0xe82dd1f  cmp r8d,8
  0xe82dd23  jne 0xE82DE67                                 ; -> loc_e82de67
  0xe82dd29  mov rax,[rdx+0x38]                            ; R a1+0x38
  0xe82dd2d  imul rcx,0x78
  0xe82dd31  jmp short 0xE82DD80                           ; -> loc_e82dd80

0xe82dd33..0xe82dd7d: LIFT-BODY - basic block
  0xe82dd33  cmp ecx,0xFFF
  0xe82dd39  ja 0xE82DE67                                  ; -> loc_e82de67
  0xe82dd3f  mov r10d,ecx
  0xe82dd42  shr r10d,6
  0xe82dd46  mov r11,[rdx+r10*8+0xA258]
  0xe82dd4e  mov esi,1
  0xe82dd53  shl rsi,cl
  0xe82dd56  bt r11,rcx
  0xe82dd5a  jae short 0xE82DDCA                           ; -> loc_e82ddca
  0xe82dd5c  mov eax,[rdx+rcx*8+0xA45C]
  0xe82dd63  cmp eax,r8d
  0xe82dd66  jne 0xE82DE15                                 ; -> loc_e82de15
  0xe82dd6c  cmp r8d,8
  0xe82dd70  jne 0xE82DE67                                 ; -> loc_e82de67
  0xe82dd76  mov rax,[rdx+0xA248]
  0xe82dd7d  shl ecx,7

0xe82dd80..0xe82dd92: LIFT-BODY - basic block
  0xe82dd80  mov rax,[rax+rcx]
  0xe82dd84  mov qword ptr [rsp+0x28],2
  0xe82dd8d  mov [rsp+0x30],rax
  0xe82dd92  jmp 0xE82DE4A                                 ; -> loc_e82de4a

0xe82dd97..0xe82ddc5: LIFT-BODY - basic block
  0xe82dd97  or r11,rsi
  0xe82dd9a  mov [rdx+r10*8+0x48],r11
  0xe82dd9f  movzx r9d,word ptr [rdx+0x40]
  0xe82dda4  mov [rdx+r9*2+0x8248],ax
  0xe82ddad  inc r9d
  0xe82ddb0  mov [rdx+0x40],r9w
  0xe82ddb5  mov [rdx+rcx*8+0x248],r8d
  0xe82ddbd  mov [rdx+rcx*8+0x24C],r8d
  0xe82ddc5  jmp 0xE82DE67                                 ; -> loc_e82de67

0xe82ddca..0xe82de01: LIFT-BODY - basic block
  0xe82ddca  or r11,rsi
  0xe82ddcd  mov [rdx+r10*8+0xA258],r11
  0xe82ddd5  movzx r9d,word ptr [rdx+0xA250]
  0xe82dddd  mov [rdx+r9*2+0x12458],ax
  0xe82dde6  inc r9d
  0xe82dde9  mov [rdx+0xA250],r9w
  0xe82ddf1  mov [rdx+rcx*8+0xA458],r8d
  0xe82ddf9  mov [rdx+rcx*8+0xA45C],r8d
  0xe82de01  jmp short 0xE82DE67                           ; -> loc_e82de67

0xe82de03..0xe82de13: LIFT-BODY - basic block
  0xe82de03  mov [rdx+rcx*8+0x24C],r8d
  0xe82de0b  mov rdx,[rdx+0x38]
  0xe82de0f  imul rcx,0x78
  0xe82de13  jmp short 0xE82DE27                           ; -> loc_e82de27

0xe82de15..0xe82de24: LIFT-BODY - basic block
  0xe82de15  mov [rdx+rcx*8+0xA45C],r8d
  0xe82de1d  mov rdx,[rdx+0xA248]
  0xe82de24  shl ecx,7

0xe82de27..0xe82de45: LIFT-BODY - basic block
  0xe82de27  mov rcx,[rdx+rcx]
  0xe82de2b  mov qword ptr [rsp+0x28],0
  0xe82de34  mov [rsp+0x30],rcx
  0xe82de39  mov dword ptr [rsp+0x38],0xFFFFFFFF
  0xe82de41  mov [rsp+0x3C],eax
  0xe82de45  mov [rsp+0x40],r8d

0xe82de4a..0xe82de61: LIFT-BODY - basic block
  0xe82de4a  mov rax,[r9]
  0xe82de4d  mov rax,[rax+0xD0]
  0xe82de54  lea r8,[rsp+0x28]
  0xe82de59  mov rcx,r9
  0xe82de5c  mov edx,1
  0xe82de61  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

0xe82de67..0xe82de80: LIFT-BODY - basic block
  0xe82de67  mov rax,[rsp+0x48]
  0xe82de6c  xor rax,rsp
  0xe82de6f  mov rcx,[0x1230A0C0]                          ; [data_1230a0c0]
  0xe82de76  cmp rcx,rax
  0xe82de79  jne short 0xE82DE81                           ; -> loc_e82de81
  0xe82de7b  add rsp,0x50
  0xe82de7f  pop rsi
  0xe82de80  ret

0xe82de81..0xe82de8e: LIFT-BODY - basic block
  0xe82de81  mov rcx,[rsp+0x48]
  0xe82de86  xor rcx,rsp
  0xe82de89  call 0xE951550                                ; -> sub_e951550
  0xe82de8e  int3

## Struct fields touched

LIFT-BODY: list every struct field read/written with offset, size, R/W, meaning, tag

## Callees

| 0xe82de61 (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xe951550 (sub_e951550) | boundary (TBD: classify in native_boundary.tsv) | call 0xE951550                                ; -> sub_e951550 | [V] |

## Verbatim instruction quotes (all calls in the function)

0xe82de61  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82de89  call 0xE951550                                ; -> sub_e951550

## OPEN questions

LIFT-BODY: list unknowns

## Reversed source (complete)

// Reversed from the disassembly of [0xe82dcc0, 0xe82de8f), size 0x1cf, Minecraft Windows
// 1.26.62.01 (rdis dis output). Every statement carries the instruction range it implements;
// every call instruction is quoted verbatim (pure lines below). Types: native::<area>::
//
// LIFT-BODY: fill in struct definitions and data references [V]
//

extern "C" void sub_e82dcc0(/* LIFT-BODY: exact args */) {
    // 0xe82dcc0..0xe82dd31
    LIFT-BODY;  // implement basic block 0xe82dcc0..0xe82dd31

    // 0xe82dd33..0xe82dd7d
    LIFT-BODY;  // implement basic block 0xe82dd33..0xe82dd7d

    // 0xe82dd80..0xe82dd92
    LIFT-BODY;  // implement basic block 0xe82dd80..0xe82dd92

    // 0xe82dd97..0xe82ddc5
    LIFT-BODY;  // implement basic block 0xe82dd97..0xe82ddc5

    // 0xe82ddca..0xe82de01
    LIFT-BODY;  // implement basic block 0xe82ddca..0xe82de01

    // 0xe82de03..0xe82de13
    LIFT-BODY;  // implement basic block 0xe82de03..0xe82de13

    // 0xe82de15..0xe82de24
    LIFT-BODY;  // implement basic block 0xe82de15..0xe82de24

    // 0xe82de27..0xe82de45
    LIFT-BODY;  // implement basic block 0xe82de27..0xe82de45

    // 0xe82de4a..0xe82de61
    0xe82de61  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe82de4a..0xe82de61

    // 0xe82de67..0xe82de80
    LIFT-BODY;  // implement basic block 0xe82de67..0xe82de80

    // 0xe82de81..0xe82de8e
    0xe82de89  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xe82de81..0xe82de8e

}

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv