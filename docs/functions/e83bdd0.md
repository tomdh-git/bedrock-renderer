# Dossier: sub_e83bdd0 ("")

Minecraft Windows 1.26.62.01. Function [0xe83bdd0, 0xe83c383), size 0x5b3 bytes.
Disassembly source: rdis `fn 0xe83bdd0` / `dis 0xe83bdd0`.
All offsets below are [V] from that listing; nothing is inferred.

## Signature (lifted)

// LIFT-BODY: fill in exact x64 Microsoft ABI signature from rdis fn
extern "C" void sub_e83bdd0(/* LIFT-BODY: exact args */);

## Register / argument map

LIFT-BODY: document register/argument map from prologue analysis

## Phases (instruction-complete, [0xe83bdd0, 0xe83c383))

0xe83bdd0..0xe83bea6: LIFT-BODY - basic block
  0xe83bdd0  push r15
  0xe83bdd2  push r14
  0xe83bdd4  push r13
  0xe83bdd6  push r12
  0xe83bdd8  push rsi
  0xe83bdd9  push rdi
  0xe83bdda  push rbx
  0xe83bddb  sub rsp,0x30
  0xe83bddf  mov r14,r8
  0xe83bde2  mov rsi,rdx
  0xe83bde5  mov rbx,rcx
  0xe83bde8  mov byte ptr [rdx+8],0                        ; W a1+0x8
  0xe83bdec  mov rcx,[rcx+8]                               ; R a0+0x8
  0xe83bdf0  mov rdx,[rbx+0x10]                            ; R a0+0x10
  0xe83bdf4  sub rdx,rcx
  0xe83bdf7  shr rdx,3
  0xe83bdfb  mov rax,[r8]                                  ; R a2+0x0
  0xe83bdfe  movsx r8,al
  0xe83be02  mov r9d,eax
  0xe83be05  shr r9d,8
  0xe83be09  movsx r9,r9b
  0xe83be0d  imul r8,0x1003F
  0xe83be14  add r8,r9
  0xe83be17  mov r9d,eax
  0xe83be1a  shr r9d,0x10
  0xe83be1e  movsx r9,r9b
  0xe83be22  imul r8,0x1003F
  0xe83be29  add r8,r9
  0xe83be2c  mov r9d,eax
  0xe83be2f  shr r9d,0x18
  0xe83be33  movsx r9,r9b
  0xe83be37  imul r8,0x1003F
  0xe83be3e  add r8,r9
  0xe83be41  mov r9,rax
  0xe83be44  shr r9,0x20
  0xe83be48  movsx r9,r9b
  0xe83be4c  imul r8,0x1003F
  0xe83be53  add r8,r9
  0xe83be56  mov r9,rax
  0xe83be59  shr r9,0x28
  0xe83be5d  movsx r9,r9b
  0xe83be61  imul r8,0x1003F
  0xe83be68  add r8,r9
  0xe83be6b  mov r9,rax
  0xe83be6e  shr r9,0x30
  0xe83be72  movsx r9,r9b
  0xe83be76  imul r8,0x1003F
  0xe83be7d  add r8,r9
  0xe83be80  mov r9,rax
  0xe83be83  sar r9,0x38
  0xe83be87  imul r8,0x1003F
  0xe83be8e  add r8,r9
  0xe83be91  add rdx,0xFFFFFFFFFFFFFFFE
  0xe83be95  and rdx,r8
  0xe83be98  mov r8,[rcx+rdx*8]                            ; R *(a0+0x8)+0x0+idx
  0xe83be9c  mov rcx,[rcx+rdx*8+8]                         ; R *(a0+0x8)+0x8+idx
  0xe83bea1  cmp r8,rcx
  0xe83bea4  je short 0xE83BEC2                            ; -> loc_e83bec2
  0xe83bea6  nop [rax+rax]                                 ; R *(a2+0x0)+0x0+idx

0xe83beb0..0xe83bec0: LIFT-BODY - basic block
  0xe83beb0  cmp [r8],rax                                  ; R *(*(a0+0x8)+0x0+idx)+0x0
  0xe83beb3  je 0xE83BFE6                                  ; -> loc_e83bfe6
  0xe83beb9  mov r8,[r8+0x10]                              ; R *(*(a0+0x8)+0x0+idx)+0x10
  0xe83bebd  cmp r8,rcx
  0xe83bec0  jne short 0xE83BEB0                           ; -> loc_e83beb0

0xe83bec2..0xe83bfe4: LIFT-BODY - basic block
  0xe83bec2  mov qword ptr [rsi],0                         ; W a1+0x0
  0xe83bec9  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  0xe83bed0  mov rax,[rcx]
  0xe83bed3  mov rax,[rax+8]
  0xe83bed7  mov dword ptr [rsp+0x28],0
  0xe83bedf  mov qword ptr [rsp+0x20],0
  0xe83bee8  mov r8d,0x20
  0xe83beee  xor edx,edx
  0xe83bef0  xor r9d,r9d
  0xe83bef3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  0xe83bef9  mov rdi,rax
  0xe83befc  mov rax,[r14]                                 ; R a2+0x0
  0xe83beff  mov [rdi],rax
  0xe83bf02  mov rax,[r14+8]                               ; R a2+0x8
  0xe83bf06  mov [rdi+8],rax
  0xe83bf0a  xorps xmm0,xmm0
  0xe83bf0d  movups [rdi+0x10],xmm0
  0xe83bf11  mov rcx,[rbx+8]                               ; R a0+0x8
  0xe83bf15  mov rax,[rbx+0x10]                            ; R a0+0x10
  0xe83bf19  sub rax,rcx
  0xe83bf1c  mov rdx,rax
  0xe83bf1f  sar rdx,3
  0xe83bf23  mov r8,[r14]                                  ; R a2+0x0
  0xe83bf26  movsx r9,r8b
  0xe83bf2a  mov r10d,r8d
  0xe83bf2d  shr r10d,8
  0xe83bf31  movsx r10,r10b
  0xe83bf35  imul r9,0x1003F
  0xe83bf3c  add r9,r10
  0xe83bf3f  mov r10d,r8d
  0xe83bf42  shr r10d,0x10
  0xe83bf46  movsx r10,r10b
  0xe83bf4a  imul r9,0x1003F
  0xe83bf51  add r9,r10
  0xe83bf54  mov r10d,r8d
  0xe83bf57  shr r10d,0x18
  0xe83bf5b  movsx r10,r10b
  0xe83bf5f  imul r9,0x1003F
  0xe83bf66  add r9,r10
  0xe83bf69  mov r10,r8
  0xe83bf6c  shr r10,0x20
  0xe83bf70  movsx r10,r10b
  0xe83bf74  imul r9,0x1003F
  0xe83bf7b  add r9,r10
  0xe83bf7e  mov r10,r8
  0xe83bf81  shr r10,0x28
  0xe83bf85  movsx r10,r10b
  0xe83bf89  imul r9,0x1003F
  0xe83bf90  add r9,r10
  0xe83bf93  mov r10,r8
  0xe83bf96  shr r10,0x30
  0xe83bf9a  movsx r10,r10b
  0xe83bf9e  imul r9,0x1003F
  0xe83bfa5  add r9,r10
  0xe83bfa8  sar r8,0x38
  0xe83bfac  imul r9,0x1003F
  0xe83bfb3  add r9,r8
  0xe83bfb6  add rdx,0xFFFFFFFFFFFFFFFE
  0xe83bfba  and rdx,r9
  0xe83bfbd  mov r8,[rcx+rdx*8+8]                          ; R *(a0+0x8)+0x8+idx
  0xe83bfc2  mov [rdi+0x10],r8
  0xe83bfc6  test r8,r8
  0xe83bfc9  je short 0xE83BFEE                            ; -> loc_e83bfee
  0xe83bfcb  mov r9,[r8+0x18]                              ; R *(*(a0+0x8)+0x8+idx)+0x18
  0xe83bfcf  mov [rdi+0x18],r9
  0xe83bfd3  mov [r8+0x18],rdi                             ; W *(*(a0+0x8)+0x8+idx)+0x18
  0xe83bfd7  mov r9,[rdi+0x18]
  0xe83bfdb  test r9,r9
  0xe83bfde  je short 0xE83C050                            ; -> loc_e83c050
  0xe83bfe0  mov [r9+0x10],rdi
  0xe83bfe4  jmp short 0xE83C050                           ; -> loc_e83c050

0xe83bfe6..0xe83bfe9: LIFT-BODY - basic block
  0xe83bfe6  mov [rsi],r8
  0xe83bfe9  jmp 0xE83C370                                 ; -> loc_e83c370

0xe83bfee..0xe83bff6: LIFT-BODY - basic block
  0xe83bfee  test rdx,rdx
  0xe83bff1  je short 0xE83C00C                            ; -> loc_e83c00c
  0xe83bff3  mov r9,rdx
  0xe83bff6  nop [rax+rax]

0xe83c000..0xe83c00a: LIFT-BODY - basic block
  0xe83c000  cmp qword ptr [rcx+r9*8],0
  0xe83c005  jne short 0xE83C00F                           ; -> loc_e83c00f
  0xe83c007  dec r9
  0xe83c00a  jne short 0xE83C000                           ; -> loc_e83c000

0xe83c00c..0xe83c00c: LIFT-BODY - basic block
  0xe83c00c  xor r9d,r9d

0xe83c00f..0xe83c013: LIFT-BODY - basic block
  0xe83c00f  mov r10,[rcx+r9*8]
  0xe83c013  nop [rax+rax]

0xe83c020..0xe83c039: LIFT-BODY - basic block
  0xe83c020  test r10,r10
  0xe83c023  je short 0xE83C03B                            ; -> loc_e83c03b
  0xe83c025  mov r9,r10
  0xe83c028  mov r10,[r10+0x10]
  0xe83c02c  test r10,r10
  0xe83c02f  jne short 0xE83C020                           ; -> loc_e83c020
  0xe83c031  mov [rdi+0x18],r9
  0xe83c035  mov [r9+0x10],rdi
  0xe83c039  jmp short 0xE83C050                           ; -> loc_e83c050

0xe83c03b..0xe83c043: LIFT-BODY - basic block
  0xe83c03b  mov qword ptr [rdi+0x18],0
  0xe83c043  nop [rax+rax]

0xe83c050..0xe83c05e: LIFT-BODY - basic block
  0xe83c050  cmp r8,[rcx+rdx*8]
  0xe83c054  jne short 0xE83C060                           ; -> loc_e83c060
  0xe83c056  mov [rcx+rdx*8],rdi
  0xe83c05a  sub rdx,1
  0xe83c05e  jae short 0xE83C050                           ; -> loc_e83c050

0xe83c060..0xe83c126: LIFT-BODY - basic block
  0xe83c060  mov rcx,[rbx]
  0xe83c063  lea rdx,[rcx+1]
  0xe83c067  mov [rbx],rdx
  0xe83c06a  add rcx,2
  0xe83c06e  sar rax,1
  0xe83c071  cmp rcx,rax
  0xe83c074  jbe 0xE83C369                                 ; -> loc_e83c369
  0xe83c07a  mov rcx,[rbx+8]
  0xe83c07e  mov r14,[rbx+0x10]
  0xe83c082  mov r15,[rcx]
  0xe83c085  sub r14,rcx
  0xe83c088  mov [rbx+0x10],rcx
  0xe83c08c  lea r12,[r14-7]
  0xe83c090  lea rax,[rcx+r14*8]
  0xe83c094  add rax,0xFFFFFFFFFFFFFFC8
  0xe83c098  cmp rax,[rbx+0x18]
  0xe83c09c  jbe 0xE83C1C1                                 ; -> loc_e83c1c1
  0xe83c0a2  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  0xe83c0a9  test rcx,rcx
  0xe83c0ac  je 0xE83C156                                  ; -> loc_e83c156
  0xe83c0b2  lea r8,[r12*8]
  0xe83c0ba  mov rax,[rcx]
  0xe83c0bd  mov rax,[rax+8]
  0xe83c0c1  mov dword ptr [rsp+0x28],0
  0xe83c0c9  mov qword ptr [rsp+0x20],0
  0xe83c0d2  xor edx,edx
  0xe83c0d4  xor r9d,r9d
  0xe83c0d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  0xe83c0dd  mov rcx,rax
  0xe83c0e0  mov rdx,[rbx+8]
  0xe83c0e4  mov rax,[rbx+0x10]
  0xe83c0e8  cmp rdx,rax
  0xe83c0eb  je 0xE83C177                                  ; -> loc_e83c177
  0xe83c0f1  mov r10,rax
  0xe83c0f4  sub r10,rdx
  0xe83c0f7  add r10,0xFFFFFFFFFFFFFFF8
  0xe83c0fb  cmp r10,0x38
  0xe83c0ff  jb short 0xE83C15A                            ; -> loc_e83c15a
  0xe83c101  mov r8,rcx
  0xe83c104  sub r8,rdx
  0xe83c107  cmp r8,0x20
  0xe83c10b  jb short 0xE83C15A                            ; -> loc_e83c15a
  0xe83c10d  shr r10,3
  0xe83c111  inc r10
  0xe83c114  mov r11,r10
  0xe83c117  and r11,0xFFFFFFFFFFFFFFFC
  0xe83c11b  lea r8,[rcx+r11*8]
  0xe83c11f  lea r9,[rdx+r11*8]
  0xe83c123  xor r13d,r13d
  0xe83c126  nop [rax+rax]

0xe83c130..0xe83c154: LIFT-BODY - basic block
  0xe83c130  movups xmm0,[rdx+r13*8]
  0xe83c135  movups xmm1,[rdx+r13*8+0x10]
  0xe83c13b  movups [rcx+r13*8],xmm0
  0xe83c140  movups [rcx+r13*8+0x10],xmm1
  0xe83c146  add r13,4
  0xe83c14a  cmp r11,r13
  0xe83c14d  jne short 0xE83C130                           ; -> loc_e83c130
  0xe83c14f  cmp r10,r11
  0xe83c152  jne short 0xE83C160                           ; -> loc_e83c160
  0xe83c154  jmp short 0xE83C173                           ; -> loc_e83c173

0xe83c156..0xe83c158: LIFT-BODY - basic block
  0xe83c156  xor ecx,ecx
  0xe83c158  jmp short 0xE83C1B5                           ; -> loc_e83c1b5

0xe83c15a..0xe83c15d: LIFT-BODY - basic block
  0xe83c15a  mov r8,rcx
  0xe83c15d  mov r9,rdx

0xe83c160..0xe83c171: LIFT-BODY - basic block
  0xe83c160  mov rdx,[r9]
  0xe83c163  mov [r8],rdx
  0xe83c166  add r9,8
  0xe83c16a  add r8,8
  0xe83c16e  cmp r9,rax
  0xe83c171  jne short 0xE83C160                           ; -> loc_e83c160

0xe83c173..0xe83c173: LIFT-BODY - basic block
  0xe83c173  mov rdx,[rbx+8]

0xe83c177..0xe83c1b2: LIFT-BODY - basic block
  0xe83c177  test rdx,rdx
  0xe83c17a  je short 0xE83C1B5                            ; -> loc_e83c1b5
  0xe83c17c  mov r8,[0x12ADF800]                           ; [data_12adf800]
  0xe83c183  test r8,r8
  0xe83c186  je short 0xE83C1B5                            ; -> loc_e83c1b5
  0xe83c188  mov rax,[r8]
  0xe83c18b  mov rax,[rax+8]
  0xe83c18f  mov dword ptr [rsp+0x28],0
  0xe83c197  mov qword ptr [rsp+0x20],0
  0xe83c1a0  mov r13,rcx
  0xe83c1a3  mov rcx,r8
  0xe83c1a6  xor r8d,r8d
  0xe83c1a9  xor r9d,r9d
  0xe83c1ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  0xe83c1b2  mov rcx,r13

0xe83c1b5..0xe83c1bd: LIFT-BODY - basic block
  0xe83c1b5  mov [rbx+8],rcx
  0xe83c1b9  lea rax,[rcx+r12*8]
  0xe83c1bd  mov [rbx+0x18],rax

0xe83c1c1..0xe83c1f1: LIFT-BODY - basic block
  0xe83c1c1  test r12,r12
  0xe83c1c4  je short 0xE83C1F5                            ; -> loc_e83c1f5
  0xe83c1c6  lea rax,[rcx+r14*8]
  0xe83c1ca  add rax,0xFFFFFFFFFFFFFFC8
  0xe83c1ce  lea rdx,[rcx+8]
  0xe83c1d2  cmp rax,rdx
  0xe83c1d5  cmova rdx,rax
  0xe83c1d9  mov r8,rcx
  0xe83c1dc  not r8
  0xe83c1df  add r8,rdx
  0xe83c1e2  and r8,0xFFFFFFFFFFFFFFF8
  0xe83c1e6  add r8,8
  0xe83c1ea  xor edx,edx
  0xe83c1ec  call 0xEEC6ED0                                ; -> sub_eec6ed0
  0xe83c1f1  mov rcx,[rbx+8]

0xe83c1f5..0xe83c20f: LIFT-BODY - basic block
  0xe83c1f5  lea rax,[rcx+r12*8]
  0xe83c1f9  mov [rbx+0x10],rax
  0xe83c1fd  test r15,r15
  0xe83c200  je 0xE83C369                                  ; -> loc_e83c369
  0xe83c206  add r14,0xFFFFFFFFFFFFFFF7
  0xe83c20a  xorps xmm0,xmm0
  0xe83c20d  jmp short 0xE83C219                           ; -> loc_e83c219
  0xe83c20f  nop

0xe83c210..0xe83c213: LIFT-BODY - basic block
  0xe83c210  test r15,r15
  0xe83c213  je 0xE83C369                                  ; -> loc_e83c369

0xe83c219..0xe83c2e3: LIFT-BODY - basic block
  0xe83c219  mov rax,r15
  0xe83c21c  mov r8,[r15]
  0xe83c21f  mov r15,[r15+0x10]
  0xe83c223  movups [rax+0x10],xmm0
  0xe83c227  movsx rdx,r8b
  0xe83c22b  mov r9d,r8d
  0xe83c22e  shr r9d,8
  0xe83c232  movsx r9,r9b
  0xe83c236  imul rdx,0x1003F
  0xe83c23d  add rdx,r9
  0xe83c240  mov r9d,r8d
  0xe83c243  shr r9d,0x10
  0xe83c247  movsx r9,r9b
  0xe83c24b  imul rdx,0x1003F
  0xe83c252  add rdx,r9
  0xe83c255  mov r9d,r8d
  0xe83c258  shr r9d,0x18
  0xe83c25c  movsx r9,r9b
  0xe83c260  imul rdx,0x1003F
  0xe83c267  add rdx,r9
  0xe83c26a  mov r9,r8
  0xe83c26d  shr r9,0x20
  0xe83c271  movsx r9,r9b
  0xe83c275  imul rdx,0x1003F
  0xe83c27c  add rdx,r9
  0xe83c27f  mov r9,r8
  0xe83c282  shr r9,0x28
  0xe83c286  movsx r9,r9b
  0xe83c28a  imul rdx,0x1003F
  0xe83c291  add rdx,r9
  0xe83c294  mov r9,r8
  0xe83c297  shr r9,0x30
  0xe83c29b  movsx r9,r9b
  0xe83c29f  imul rdx,0x1003F
  0xe83c2a6  add rdx,r9
  0xe83c2a9  sar r8,0x38
  0xe83c2ad  imul rdx,0x1003F
  0xe83c2b4  add rdx,r8
  0xe83c2b7  and rdx,r14
  0xe83c2ba  mov r8,[rcx+rdx*8+8]
  0xe83c2bf  mov [rax+0x10],r8
  0xe83c2c3  test r8,r8
  0xe83c2c6  je short 0xE83C2F0                            ; -> loc_e83c2f0
  0xe83c2c8  mov r9,[r8+0x18]
  0xe83c2cc  mov [rax+0x18],r9
  0xe83c2d0  mov [r8+0x18],rax
  0xe83c2d4  mov r9,[rax+0x18]
  0xe83c2d8  test r9,r9
  0xe83c2db  je short 0xE83C350                            ; -> loc_e83c350
  0xe83c2dd  mov [r9+0x10],rax
  0xe83c2e1  jmp short 0xE83C350                           ; -> loc_e83c350
  0xe83c2e3  nop [rax+rax]

0xe83c2f0..0xe83c2f8: LIFT-BODY - basic block
  0xe83c2f0  mov r9,rdx
  0xe83c2f3  test rdx,rdx
  0xe83c2f6  je short 0xE83C30C                            ; -> loc_e83c30c
  0xe83c2f8  nop [rax+rax]

0xe83c300..0xe83c30a: LIFT-BODY - basic block
  0xe83c300  cmp qword ptr [rcx+r9*8],0
  0xe83c305  jne short 0xE83C30F                           ; -> loc_e83c30f
  0xe83c307  dec r9
  0xe83c30a  jne short 0xE83C300                           ; -> loc_e83c300

0xe83c30c..0xe83c30c: LIFT-BODY - basic block
  0xe83c30c  xor r9d,r9d

0xe83c30f..0xe83c313: LIFT-BODY - basic block
  0xe83c30f  mov r10,[rcx+r9*8]
  0xe83c313  nop [rax+rax]

0xe83c320..0xe83c339: LIFT-BODY - basic block
  0xe83c320  test r10,r10
  0xe83c323  je short 0xE83C33B                            ; -> loc_e83c33b
  0xe83c325  mov r9,r10
  0xe83c328  mov r10,[r10+0x10]
  0xe83c32c  test r10,r10
  0xe83c32f  jne short 0xE83C320                           ; -> loc_e83c320
  0xe83c331  mov [rax+0x18],r9
  0xe83c335  mov [r9+0x10],rax
  0xe83c339  jmp short 0xE83C350                           ; -> loc_e83c350

0xe83c33b..0xe83c343: LIFT-BODY - basic block
  0xe83c33b  mov qword ptr [rax+0x18],0
  0xe83c343  nop [rax+rax]

0xe83c350..0xe83c364: LIFT-BODY - basic block
  0xe83c350  cmp r8,[rcx+rdx*8]
  0xe83c354  jne 0xE83C210                                 ; -> loc_e83c210
  0xe83c35a  mov [rcx+rdx*8],rax
  0xe83c35e  sub rdx,1
  0xe83c362  jae short 0xE83C350                           ; -> loc_e83c350
  0xe83c364  jmp 0xE83C210                                 ; -> loc_e83c210

0xe83c369..0xe83c36c: LIFT-BODY - basic block
  0xe83c369  mov [rsi],rdi
  0xe83c36c  mov byte ptr [rsi+8],1

0xe83c370..0xe83c382: LIFT-BODY - basic block
  0xe83c370  mov rax,rsi
  0xe83c373  add rsp,0x30
  0xe83c377  pop rbx
  0xe83c378  pop rdi
  0xe83c379  pop rsi
  0xe83c37a  pop r12
  0xe83c37c  pop r13
  0xe83c37e  pop r14
  0xe83c380  pop r15
  0xe83c382  ret

## Struct fields touched

LIFT-BODY: list every struct field read/written with offset, size, R/W, meaning, tag

## Callees

| 0xe83bef3 (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xe83c0d7 (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xe83c1ac (indirect) | boundary via data slot (indirect) | call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 | [V] |
| 0xeec6ed0 (sub_eec6ed0) | boundary (TBD: classify in native_boundary.tsv) | call 0xEEC6ED0                                ; -> sub_eec6ed0 | [V] |

## Verbatim instruction quotes (all calls in the function)

0xe83bef3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83c0d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83c1ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe83c1ec  call 0xEEC6ED0                                ; -> sub_eec6ed0

## OPEN questions

LIFT-BODY: list unknowns

## Reversed source (complete)

// Reversed from the disassembly of [0xe83bdd0, 0xe83c383), size 0x5b3, Minecraft Windows
// 1.26.62.01 (rdis dis output). Every statement carries the instruction range it implements;
// every call instruction is quoted verbatim (pure lines below). Types: native::<area>::
//
// LIFT-BODY: fill in struct definitions and data references [V]
//

extern "C" void sub_e83bdd0(/* LIFT-BODY: exact args */) {
    // 0xe83bdd0..0xe83bea6
    LIFT-BODY;  // implement basic block 0xe83bdd0..0xe83bea6

    // 0xe83beb0..0xe83bec0
    LIFT-BODY;  // implement basic block 0xe83beb0..0xe83bec0

    // 0xe83bec2..0xe83bfe4
    0xe83bef3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83bec2..0xe83bfe4

    // 0xe83bfe6..0xe83bfe9
    LIFT-BODY;  // implement basic block 0xe83bfe6..0xe83bfe9

    // 0xe83bfee..0xe83bff6
    LIFT-BODY;  // implement basic block 0xe83bfee..0xe83bff6

    // 0xe83c000..0xe83c00a
    LIFT-BODY;  // implement basic block 0xe83c000..0xe83c00a

    // 0xe83c00c..0xe83c00c
    LIFT-BODY;  // implement basic block 0xe83c00c..0xe83c00c

    // 0xe83c00f..0xe83c013
    LIFT-BODY;  // implement basic block 0xe83c00f..0xe83c013

    // 0xe83c020..0xe83c039
    LIFT-BODY;  // implement basic block 0xe83c020..0xe83c039

    // 0xe83c03b..0xe83c043
    LIFT-BODY;  // implement basic block 0xe83c03b..0xe83c043

    // 0xe83c050..0xe83c05e
    LIFT-BODY;  // implement basic block 0xe83c050..0xe83c05e

    // 0xe83c060..0xe83c126
    0xe83c0d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83c060..0xe83c126

    // 0xe83c130..0xe83c154
    LIFT-BODY;  // implement basic block 0xe83c130..0xe83c154

    // 0xe83c156..0xe83c158
    LIFT-BODY;  // implement basic block 0xe83c156..0xe83c158

    // 0xe83c15a..0xe83c15d
    LIFT-BODY;  // implement basic block 0xe83c15a..0xe83c15d

    // 0xe83c160..0xe83c171
    LIFT-BODY;  // implement basic block 0xe83c160..0xe83c171

    // 0xe83c173..0xe83c173
    LIFT-BODY;  // implement basic block 0xe83c173..0xe83c173

    // 0xe83c177..0xe83c1b2
    0xe83c1ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    LIFT-BODY;  // implement basic block 0xe83c177..0xe83c1b2

    // 0xe83c1b5..0xe83c1bd
    LIFT-BODY;  // implement basic block 0xe83c1b5..0xe83c1bd

    // 0xe83c1c1..0xe83c1f1
    0xe83c1ec  call 0xEEC6ED0                                ; -> sub_eec6ed0
    LIFT-BODY;  // implement basic block 0xe83c1c1..0xe83c1f1

    // 0xe83c1f5..0xe83c20f
    LIFT-BODY;  // implement basic block 0xe83c1f5..0xe83c20f

    // 0xe83c210..0xe83c213
    LIFT-BODY;  // implement basic block 0xe83c210..0xe83c213

    // 0xe83c219..0xe83c2e3
    LIFT-BODY;  // implement basic block 0xe83c219..0xe83c2e3

    // 0xe83c2f0..0xe83c2f8
    LIFT-BODY;  // implement basic block 0xe83c2f0..0xe83c2f8

    // 0xe83c300..0xe83c30a
    LIFT-BODY;  // implement basic block 0xe83c300..0xe83c30a

    // 0xe83c30c..0xe83c30c
    LIFT-BODY;  // implement basic block 0xe83c30c..0xe83c30c

    // 0xe83c30f..0xe83c313
    LIFT-BODY;  // implement basic block 0xe83c30f..0xe83c313

    // 0xe83c320..0xe83c339
    LIFT-BODY;  // implement basic block 0xe83c320..0xe83c339

    // 0xe83c33b..0xe83c343
    LIFT-BODY;  // implement basic block 0xe83c33b..0xe83c343

    // 0xe83c350..0xe83c364
    LIFT-BODY;  // implement basic block 0xe83c350..0xe83c364

    // 0xe83c369..0xe83c36c
    LIFT-BODY;  // implement basic block 0xe83c369..0xe83c36c

    // 0xe83c370..0xe83c382
    LIFT-BODY;  // implement basic block 0xe83c370..0xe83c382

}

// Calls out of lifted code:
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv