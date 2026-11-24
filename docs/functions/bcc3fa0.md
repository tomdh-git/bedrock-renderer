# Dossier: sub_bcc3fa0 ("")

Minecraft Windows 1.26.62.01. Function [0xbcc3fa0, 0xbcc414f), size 0x1af bytes.
Disassembly source: rdis `fn 0xbcc3fa0` / `dis 0xbcc3fa0`.
All offsets below are [V] from that listing; nothing is inferred.

## Signature (lifted)

// LIFT-BODY: fill in exact x64 Microsoft ABI signature from rdis fn
extern "C" void sub_bcc3fa0(/* LIFT-BODY: exact args */);

## Register / argument map

LIFT-BODY: document register/argument map from prologue analysis

## Phases (instruction-complete, [0xbcc3fa0, 0xbcc414f))

0xbcc3fa0..0xbcc3fce: LIFT-BODY - basic block
  0xbcc3fa0  push r15
  0xbcc3fa2  push r14
  0xbcc3fa4  push r12
  0xbcc3fa6  push rsi
  0xbcc3fa7  push rdi
  0xbcc3fa8  push rbp
  0xbcc3fa9  push rbx
  0xbcc3faa  sub rsp,0x90
  0xbcc3fb1  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  0xbcc3fb8  xor rax,rsp
  0xbcc3fbb  mov [rsp+0x88],rax
  0xbcc3fc3  test byte ptr [0x12ADFA51],8                  ; [data_12adfa51]
  0xbcc3fca  jne short 0xBCC3FD3                           ; -> loc_bcc3fd3
  0xbcc3fcc  xor eax,eax
  0xbcc3fce  jmp 0xBCC40EB                                 ; -> loc_bcc40eb

0xbcc3fd3..0xbcc404b: LIFT-BODY - basic block
  0xbcc3fd3  mov rbx,[rsp+0xF0]
  0xbcc3fdb  xor eax,eax
  0xbcc3fdd  cmp byte ptr [rbx+2],1
  0xbcc3fe1  jne 0xBCC40EB                                 ; -> loc_bcc40eb
  0xbcc3fe7  cmp word ptr [rbx],0xFFFF
  0xbcc3feb  je 0xBCC40EB                                  ; -> loc_bcc40eb
  0xbcc3ff1  mov r12,r9
  0xbcc3ff4  mov r14d,edx
  0xbcc3ff7  mov r15d,r8d
  0xbcc3ffa  mov ebp,[rsp+0xF8]
  0xbcc4001  mov rax,[rcx]
  0xbcc4004  mov rsi,[rax+0x10]
  0xbcc4008  mov dword ptr [rsp+0x48],0x3F800000
  0xbcc4010  xorps xmm0,xmm0
  0xbcc4013  movups [rsp+0x4C],xmm0
  0xbcc4018  mov dword ptr [rsp+0x5C],0x3F800000
  0xbcc4020  movups [rsp+0x60],xmm0
  0xbcc4025  mov dword ptr [rsp+0x70],0x3F800000
  0xbcc402d  movups [rsp+0x74],xmm0
  0xbcc4032  mov dword ptr [rsp+0x84],0x3F800000
  0xbcc403d  mov rcx,[rsi]
  0xbcc4040  mov eax,[rcx+0xD457C0]
  0xbcc4046  mov edx,0xFFFF
  0xbcc404b  nop [rax+rax]

0xbcc4050..0xbcc407d: LIFT-BODY - basic block
  0xbcc4050  mov edi,eax
  0xbcc4052  lea r8d,[rdi+1]
  0xbcc4056  cmp r8d,0xFFFF
  0xbcc405d  cmovae r8d,edx
  0xbcc4061  cmp eax,0xFFFF
  0xbcc4066  cmovae r8d,edx
  0xbcc406a  lock cmpxchg [rcx+0xD457C0],r8d
  0xbcc4073  cmp edi,0xFFFF
  0xbcc4079  je short 0xBCC407F                            ; -> loc_bcc407f
  0xbcc407b  cmp edi,eax
  0xbcc407d  jne short 0xBCC4050                           ; -> loc_bcc4050

0xbcc407f..0xbcc40e9: LIFT-BODY - basic block
  0xbcc407f  xor r8d,r8d
  0xbcc4082  cmp edi,0xFFFF
  0xbcc4088  setne r8b
  0xbcc408c  shl r8d,6
  0xbcc4090  mov eax,edi
  0xbcc4092  shl rax,6
  0xbcc4096  add rcx,rax
  0xbcc4099  add rcx,0x9457C0
  0xbcc40a0  lea rdx,[rsp+0x48]
  0xbcc40a5  call 0xEBCE390                                ; -> sub_ebce390
  0xbcc40aa  mov [rsi+0x7C],edi
  0xbcc40ad  mov word ptr [rsi+0x9E],1
  0xbcc40b6  mov rax,r12
  0xbcc40b9  shr rax,0x20
  0xbcc40bd  jne short 0xBCC4124                           ; -> loc_bcc4124
  0xbcc40bf  mov [rsi+0x94],r12d
  0xbcc40c6  cmp byte ptr [rbx+2],0
  0xbcc40ca  je short 0xBCC4149                            ; -> loc_bcc4149
  0xbcc40cc  mov edx,r15d
  0xbcc40cf  movzx r8d,word ptr [rbx]
  0xbcc40d3  mov [rsp+0x28],r14b
  0xbcc40d8  mov [rsp+0x20],ebp
  0xbcc40dc  mov rcx,rsi
  0xbcc40df  mov r9w,0xFFFF
  0xbcc40e4  call 0xBC60740                                ; -> sub_bc60740
  0xbcc40e9  mov al,1

0xbcc40eb..0xbcc4113: LIFT-BODY - basic block
  0xbcc40eb  mov rcx,[rsp+0x88]
  0xbcc40f3  xor rcx,rsp
  0xbcc40f6  mov rdx,[0x1230A0C0]                          ; [data_1230a0c0]
  0xbcc40fd  cmp rdx,rcx
  0xbcc4100  jne short 0xBCC4114                           ; -> loc_bcc4114
  0xbcc4102  add rsp,0x90
  0xbcc4109  pop rbx
  0xbcc410a  pop rbp
  0xbcc410b  pop rdi
  0xbcc410c  pop rsi
  0xbcc410d  pop r12
  0xbcc410f  pop r14
  0xbcc4111  pop r15
  0xbcc4113  ret

0xbcc4114..0xbcc411f: LIFT-BODY - basic block
  0xbcc4114  mov rcx,[rsp+0x88]
  0xbcc411c  xor rcx,rsp
  0xbcc411f  call 0xE951550                                ; -> sub_e951550

0xbcc4124..0xbcc4144: LIFT-BODY - basic block
  0xbcc4124  xorps xmm0,xmm0
  0xbcc4127  movups [rsp+0x38],xmm0
  0xbcc412c  lea rax,[0xF08E738]                           ; [data_f08e738]
  0xbcc4133  mov [rsp+0x30],rax
  0xbcc4138  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
  0xbcc413f  lea rcx,[rsp+0x30]
  0xbcc4144  call 0xEEC6D80                                ; -> sub_eec6d80

0xbcc4149..0xbcc414e: LIFT-BODY - basic block
  0xbcc4149  call 0x1A2800                                 ; -> sub_1a2800
  0xbcc414e  int3

## Struct fields touched

LIFT-BODY: list every struct field read/written with offset, size, R/W, meaning, tag

## Callees

| 0xebce390 (sub_ebce390) | lift set | call 0xEBCE390                                ; -> sub_ebce390 | [V] |
| 0xbc60740 (sub_bc60740) | lift set | call 0xBC60740                                ; -> sub_bc60740 | [V] |
| 0xe951550 (sub_e951550) | boundary (TBD: classify in native_boundary.tsv) | call 0xE951550                                ; -> sub_e951550 | [V] |
| 0xeec6d80 (sub_eec6d80) | lift set | call 0xEEC6D80                                ; -> sub_eec6d80 | [V] |
| 0x1a2800 (sub_1a2800) | boundary (TBD: classify in native_boundary.tsv) | call 0x1A2800                                 ; -> sub_1a2800 | [V] |

## Verbatim instruction quotes (all calls in the function)

0xbcc40a5  call 0xEBCE390                                ; -> sub_ebce390
0xbcc40e4  call 0xBC60740                                ; -> sub_bc60740
0xbcc411f  call 0xE951550                                ; -> sub_e951550
0xbcc4144  call 0xEEC6D80                                ; -> sub_eec6d80
0xbcc4149  call 0x1A2800                                 ; -> sub_1a2800

## OPEN questions

LIFT-BODY: list unknowns

## Reversed source (complete)

// Reversed from the disassembly of [0xbcc3fa0, 0xbcc414f), size 0x1af, Minecraft Windows
// 1.26.62.01 (rdis dis output). Every statement carries the instruction range it implements;
// every call instruction is quoted verbatim (pure lines below). Types: native::<area>::
//
// LIFT-BODY: fill in struct definitions and data references [V]
//

extern "C" void sub_bcc3fa0(/* LIFT-BODY: exact args */) {
    // 0xbcc3fa0..0xbcc3fce
    LIFT-BODY;  // implement basic block 0xbcc3fa0..0xbcc3fce

    // 0xbcc3fd3..0xbcc404b
    LIFT-BODY;  // implement basic block 0xbcc3fd3..0xbcc404b

    // 0xbcc4050..0xbcc407d
    LIFT-BODY;  // implement basic block 0xbcc4050..0xbcc407d

    // 0xbcc407f..0xbcc40e9
    0xbcc40a5  call 0xEBCE390                                ; -> sub_ebce390
    0xbcc40e4  call 0xBC60740                                ; -> sub_bc60740
    LIFT-BODY;  // implement basic block 0xbcc407f..0xbcc40e9

    // 0xbcc40eb..0xbcc4113
    LIFT-BODY;  // implement basic block 0xbcc40eb..0xbcc4113

    // 0xbcc4114..0xbcc411f
    0xbcc411f  call 0xE951550                                ; -> sub_e951550
    LIFT-BODY;  // implement basic block 0xbcc4114..0xbcc411f

    // 0xbcc4124..0xbcc4144
    0xbcc4144  call 0xEEC6D80                                ; -> sub_eec6d80
    LIFT-BODY;  // implement basic block 0xbcc4124..0xbcc4144

    // 0xbcc4149..0xbcc414e
    0xbcc4149  call 0x1A2800                                 ; -> sub_1a2800
    LIFT-BODY;  // implement basic block 0xbcc4149..0xbcc414e

}

// Calls out of lifted code:
//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390
//   sub_bc60740 (0xbc60740, lift set) - call 0xBC60740                                ; -> sub_bc60740
//   sub_e951550 (0xe951550, boundary) - call 0xE951550                                ; -> sub_e951550
//   sub_eec6d80 (0xeec6d80, lift set) - call 0xEEC6D80                                ; -> sub_eec6d80
//   sub_1a2800 (0x1a2800, boundary) - call 0x1A2800                                 ; -> sub_1a2800
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv