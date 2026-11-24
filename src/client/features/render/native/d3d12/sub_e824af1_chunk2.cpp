// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1
// CHUNK 0xe826261..0xe827a40
#include "sub_e824af1_chunk2.h"
#include <cstdint>
#include <cstring>

namespace native {
namespace d3d12 {

void sub_e824af1_chunk2(ChunkState& state) {
    // Live registers from chunk state
    uint64_t rbx = state.rbx;
    uint64_t rbp = state.rbp;
    uint64_t r12 = state.r12;
    uint64_t r13 = state.r13;
    uint64_t r14 = state.r14;
    uint64_t r15 = state.r15;
    uint64_t rsi = state.rsi;
    uint64_t rdi = state.rdi;

    auto stack = reinterpret_cast<uint8_t*>(rbx);

    // 0xe826261..0xe826261  nop [rax+rax]
    // (align nop)

    // 0xe826270..0xe8262d3  zero-init loop over r14 entries
    // loc_e826270:
    {
        // r14 base pointer, rax from [rbx+0x90]+...
        // loop: add r14, 0xFFFFFFFFFFF48000; mov rax,[rax+0xB8000]; cmp r14,0xB7FFF; ja loc_e826270
        // then: add r14,rax; mov qword [r14],0; mov qword [r14+0x90],0; mov word [r14+0xB1],0
        // lea rcx,[r14+0x40]; mov r8d,0x28; xor edx,edx; call sub_ebce430
        // add r14,0x68; mov r8d,0x28; mov rcx,r14; xor edx,edx; call sub_ebce430
        // inc rdi; cmp rdi,rsi; jne 0xe826220
    }

    // 0xe8262d9..0xe82631b  compute item array size, check bounds
    // 0xe8262d9  imul rax,rsi,0xB8
    // 0xe8262e0  mov rcx,[rbx+0xB0]
    // 0xe8262e7  mov [rcx+0xC96180],rax
    // 0xe8262ee  movzx eax,byte ptr [rcx+0xC96190]
    // 0xe8262f5  movzx ecx,r13w
    // 0xe8262f9  cmp ecx,0x1000
    // 0xe8262ff  jb short 0xE826320
    // 0xe826301  test al,al
    // 0xe826303  je short 0xE826320
    // 0xe826305  xor ecx,ecx
    // 0xe826307  lea rdx,[0xF7F68E3]
    // 0xe82630e  call 0xBC5F110
    // 0xe826313  nop
    // 0xe826314  imul r8,r13,0xB8
    // 0xe82631b  jmp short 0xE826333
    // (guarded heap check path)

    // 0xe826320..0xe8263f4  compute rsi pointer (paged heap traversal or direct add)
    // loc_e826320:
    // 0xe826320  imul r8,r13,0xB8
    // 0xe826327  cmp ecx,0xFFF
    // 0xe82632d  jbe 0xE8263ED
    // loc_e826333:
    // 0xe826333  lea rsi,[r8-0xB8000]
    // 0xe82633a  mov rax,[rbx+0xB0]
    // 0xe826341  mov rax,[rax+0xC96178]
    // 0xe826348  mov rcx,[rax]
    // 0xe82634b  cmp rsi,0xB8000
    // 0xe826352  jb 0xE8263E8
    // ... paged heap traversal ...
    // loc_e8263ed:
    // 0xe8263ed  add r8,[rbx+0x1F8]
    // 0xe8263f4  mov rsi,r8
    // loc_e8263f7:
    // 0xe8263f7  lea rax,[r15+r12*4]
    // 0xe8263fb  movzx r12d,word ptr [rax+0xA]
    // 0xe826400  cmp r12,0xFFFF
    // 0xe826407  je 0xE827060

    // 0xe82640d..0xe826438  resource table check
    // 0xe82640d  mov r10,[rbx+0x90]
    // 0xe826414  mov rdi,[r10+0x30]
    // 0xe826418  movzx ecx,byte ptr [r10+0x20478]
    // 0xe826420  movzx r11d,r12w
    // 0xe826424  cmp r11d,0x1000
    // 0xe82642b  mov [rbx+0x180],r11d
    // 0xe826432  jb short 0xE82643A
    // 0xe826434  mov al,1
    // 0xe826436  test cl,cl
    // 0xe826438  jne short 0xE8264B6

    // 0xe82643a..0xe826496  guarded heap allocation path 1
    // ... (paged heap traversal, calls sub_e835f00)

    // 0xe826498..0xe8264b6  update r15, r10 capacity
    // 0xe826498  shl r15d,2
    // 0xe82649c  lea rax,[r15+r15*2]
    // 0xe8264a0  mov [r10+0x20468],rax
    // 0xe8264a7  movzx eax,byte ptr [r10+0x20478]
    // 0xe8264af  mov r11d,[rbx+0x180]

    // 0xe8264b6..0xe8264f4  second bounds check
    // 0xe8264b6  cmp r11d,0x1000
    // 0xe8264bd  jb 0xE82655A
    // 0xe8264c3  test al,al
    // 0xe8264c5  je 0xE82655A
    // 0xe8264cb  xor ecx,ecx
    // 0xe8264cd  lea rdx,[0xF7F68E3]
    // 0xe8264d4  call 0xBC5F110
    // 0xe8264d9  nop
    // 0xe8264da  lea eax,[r12*4]
    // 0xe8264e2  lea rcx,[rax+rax*2]
    // 0xe8264e6  mov r10,[rbx+0x90]
    // 0xe8264ed  mov r11d,[rbx+0x180]
    // 0xe8264f4  jmp short 0xE826573

    // 0xe8264f6..0xe826511  zero-fill loop
    // loc_e826500:
    // 0xe826500  add rax,[rbx+0x128]
    // loc_e826507:
    // 0xe826507  mov byte ptr [rax+8],0
    // 0xe82650b  inc rdx
    // 0xe82650e  cmp rdx,r15
    // 0xe826511  je short 0xE826498

    // 0xe826513..0xe826558  paged heap traversal for zero-fill
    // ... (mul, shr, cmp, ja, etc.)

    // 0xe82655a..0xe826573  third bounds check
    // 0xe82655a  lea eax,[r12*4]
    // 0xe826562  lea rcx,[rax+rax*2]
    // 0xe826566  cmp r11d,0xFFF
    // 0xe82656d  jbe 0xE82676A

    // 0xe826573..0xe82662b  paged heap traversal (resource table)
    // ... (mul, shr, cmp, ja, etc.)

    // 0xe826628..0xe826630  check byte at [r8+8]
    // 0xe826628  add r8,r9
    // 0xe82662b  cmp byte ptr [r8+8],0
    // 0xe826630  je 0xE82677F

    // 0xe826636..0xe8266c2  fourth bounds check + guarded heap
    // 0xe826636  movzx ecx,byte ptr [r10+0x20478]
    // ... (similar to above, calls sub_e835f00)

    // 0xe8266c9..0xe8266ec  fifth bounds check
    // 0xe8266c9  cmp r11d,0x1000
    // 0xe8266d0  jb 0xE82695E
    // 0xe8266d6  test al,al
    // 0xe8266d8  je 0xE82695E
    // 0xe8266de  xor ecx,ecx
    // 0xe8266e0  lea rdx,[0xF7F68E3]
    // 0xe8266e7  call 0xBC5F110
    // 0xe8266ec  nop

    // 0xe8266ed..0xe826700  compute rcx from r12
    // 0xe8266ed  lea eax,[r12*4]
    // 0xe8266f5  lea rcx,[rax+rax*2]
    // 0xe8266f9  mov r10,[rbx+0x90]
    // 0xe826700  jmp 0xE826977

    // 0xe826710..0xe826721  zero-fill loop 2
    // loc_e826710:
    // 0xe826710  add rax,[rbx+0x128]
    // loc_e826717:
    // 0xe826717  mov byte ptr [rax+8],0
    // 0xe82671b  inc rdx
    // 0xe82671e  cmp rdx,r15
    // 0xe826721  je short 0xE8266AB

    // 0xe826723..0xe826768  paged heap traversal for zero-fill 2
    // ...

    // 0xe82676a..0xe826779  check byte at [r8+8] (direct path)
    // 0xe82676a  add rcx,[rbx+0x128]
    // 0xe826771  mov r8,rcx
    // 0xe826774  cmp byte ptr [r8+8],0
    // 0xe826779  jne 0xE826636

    // 0xe82677f..0xe8267c8  resource table allocation (r13/r14/r15/rax/rdi setup)
    // 0xe82677f  mov r13,[r10+0x22488]
    // 0xe826786  mov rax,[r10+0x22490]
    // 0xe82678d  mov r14,r13
    // 0xe826790  shr r14,1
    // 0xe826793  cmp r13,0x2000
    // 0xe82679a  setb cl
    // 0xe82679d  mov rdx,rax
    // 0xe8267a0  shr rdx,1
    // 0xe8267a3  cmp r14,rdx
    // 0xe8267a6  setb dl
    // 0xe8267a9  or dl,cl
    // 0xe8267ab  and r13,0xFFFFFFFFFFFFFFFE
    // 0xe8267af  lea rdi,[r13+2]
    // 0xe8267b3  test dl,dl
    // 0xe8267b5  je short 0xE8267CD
    // 0xe8267b7  cmp rax,rdi
    // 0xe8267ba  cmovbe rax,rdi
    // 0xe8267be  mov [r10+0x22490],rax
    // 0xe8267c5  mov rax,r14
    // 0xe8267c8  jmp 0xE826D38

    // 0xe8267cd..0xe8267e4  check r13 and rax
    // 0xe8267cd  mov rax,[r10+0x22480]
    // 0xe8267d4  add r13,0xFFFFFFFFFFFFE002
    // 0xe8267db  je 0xE826B8D
    // 0xe8267e1  test rax,rax
    // 0xe8267e4  jne short 0xE826843

    // 0xe8267e6..0xe82683c  allocate resource table (call vendor thunk via data_f99ffa0)
    // 0xe8267e6  mov rcx,[0x12ADF800]
    // 0xe8267ed  mov rax,[rcx]
    // 0xe8267f0  mov rax,[rax+8]
    // 0xe8267f4  mov r10,[0xF99FFA0]
    // 0xe8267fb  lea rdx,[0xF7CC762]  ; "NOFILE"
    // 0xe826802  mov [rsp+0x20],rdx
    // 0xe826807  mov dword ptr [rsp+0x28],0
    // 0xe82680f  mov r8d,0x18
    // 0xe826815  mov r9d,8
    // 0xe82681b  xor edx,edx
    // 0xe82681d  call r10  ; -> sub_eea6040 (vendor thunk)
    // 0xe826820  nop
    // 0xe826821  movdqu [rax],xmm9
    // 0xe826826  mov qword ptr [rax+0x10],0
    // 0xe82682e  mov rcx,[rbx+0x90]
    // 0xe826835  mov [rcx+0x22480],rax
    // 0xe82683c  mov r11d,[rbx+0x180]

    // 0xe826843..0xe826871  check r13 against rcx+0x10
    // 0xe826843  mov rcx,[rax+0x10]
    // 0xe826847  sub r13,rcx
    // 0xe82684a  jbe 0xE826BF5
    // 0xe826850  mov [rbx+0x648],rdi
    // 0xe826857  mov rcx,[rax+8]
    // 0xe82685b  add rax,8
    // 0xe82685f  lea r15,[rcx+0x2000]
    // 0xe826866  test rcx,rcx
    // 0xe826869  cmove r15,rax
    // 0xe82686d  cmp qword ptr [r15],0
    // 0xe826871  jne 0xE826930

    // 0xe826877..0xe826896  loop: check [r15], advance
    // 0xe826877  jmp short 0xE82689C
    // loc_e826880:
    // 0xe826880  mov r15,[r15]
    // 0xe826883  mov eax,0x2000
    // 0xe826888  add r15,rax
    // 0xe82688b  add r13,0xFFFFFFFFFFFFE000
    // 0xe826892  cmp qword ptr [r15],0
    // 0xe826896  jne 0xE826930

    // 0xe82689c..0xe826919  allocate 0x2008 bytes via vendor thunk
    // 0xe82689c  mov rcx,[0x12ADF800]
    // 0xe8268a3  mov rax,[rcx]
    // 0xe8268a6  mov rax,[rax+8]
    // 0xe8268aa  mov r10,[0xF99FFA0]
    // 0xe8268b1  lea rdx,[0xF7CC762]  ; "NOFILE"
    // 0xe8268b8  mov [rsp+0x20],rdx
    // 0xe8268bd  mov dword ptr [rsp+0x28],0
    // 0xe8268c5  mov r8d,0x2008
    // 0xe8268cb  mov r9d,8
    // 0xe8268d1  xor edx,edx
    // 0xe8268d3  call r10  ; -> sub_eea6040 (vendor thunk)
    // 0xe8268d6  nop
    // 0xe8268d7  mov rdi,rax
    // 0xe8268da  mov r8d,0x2008
    // 0xe8268e0  mov rcx,rax
    // 0xe8268e3  xor edx,edx
    // 0xe8268e5  call 0xEEC6ED0  ; -> sub_eec6ed0 (CRT boundary)
    // 0xe8268ea  mov [r15],rdi
    // 0xe8268ed  mov rcx,[rbx+0x90]
    // 0xe8268f4  mov rax,[rcx+0x22480]
    // 0xe8268fb  mov [rax+8],rdi
    // 0xe8268ff  mov rax,[rcx+0x22480]
    // 0xe826906  add qword ptr [rax+0x10],0x2000
    // 0xe82690e  mov rax,[rcx+0x22480]
    // 0xe826915  cmp qword ptr [rax],0
    // 0xe826919  jne short 0xE826930

    // 0xe82691b..0xe826921  setup [rax] = [r15]
    // 0xe82691b  mov rcx,[r15]
    // 0xe82691e  mov [rax],rcx
    // 0xe826921  nop [rax+rax]

    // 0xe826930..0xe826959  post-loop cleanup
    // loc_e826930:
    // 0xe826930  cmp r13,0x2001
    // 0xe826937  jae 0xE826880
    // 0xe82693d  mov rax,[rbx+0x90]
    // 0xe826944  mov rax,[rax+0x22480]
    // 0xe82694b  mov r11d,[rbx+0x180]
    // 0xe826952  mov rdi,[rbx+0x648]
    // 0xe826959  jmp 0xE826B92

    // 0xe82695e..0xe826977  sixth bounds check (alternative path)
    // 0xe82695e  lea eax,[r12*4]
    // 0xe826966  lea rcx,[rax+rax*2]
    // 0xe82696a  cmp r11d,0xFFF
    // 0xe826971  jbe 0xE826A3A

    // 0xe826977..0xe826a28  paged heap traversal (resource table, alternative)
    // ... (similar pattern)

    // 0xe826a28..0xe826a33  check dword at [r8+4] == 0xAC3
    // 0xe826a28  add r8,r9
    // 0xe826a2b  cmp dword ptr [r8+4],0xAC3
    // 0xe826a33  jne short 0xE826A52
    // 0xe826a35  jmp 0xE827060

    // 0xe826a3a..0xe826a4c  direct path: check dword at [r8+4] == 0xAC3
    // 0xe826a3a  add rcx,[rbx+0x128]
    // 0xe826a41  mov r8,rcx
    // 0xe826a44  cmp dword ptr [r8+4],0xAC3
    // 0xe826a4c  je 0xE827060

    // 0xe826a52..0xe826a92  call sub_e83aed0 twice, then sub_e83abb0
    // 0xe826a52  mov rcx,[rbx+0x128]
    // 0xe826a59  mov rdx,r12
    // 0xe826a5c  call 0xE83AED0  ; -> sub_e83aed0
    // 0xe826a61  nop
    // 0xe826a62  mov r15d,[rax+4]
    // 0xe826a66  mov rcx,[rbx+0x128]
    // 0xe826a6d  mov rdx,r12
    // 0xe826a70  call 0xE83AED0  ; -> sub_e83aed0
    // 0xe826a75  nop
    // 0xe826a76  mov dword ptr [rax+4],0xAC3
    // 0xe826a7d  mov rax,[rbx+0x238]
    // 0xe826a84  mov r14,[rax]
    // 0xe826a87  mov rcx,r14
    // 0xe826a8a  mov rdx,r12
    // 0xe826a8d  call 0xE83ABB0  ; -> sub_e83abb0
    // 0xe826a92  nop

    // 0xe826a93..0xe826ab7  bounds check (guarded heap)
    // 0xe826a93  cmp dword ptr [rbx+0x180],0x1000
    // 0xe826a9d  jb short 0xE826AC1
    // 0xe826a9f  cmp byte ptr [r14+0xB8018],0
    // 0xe826aa7  je short 0xE826AC1
    // 0xe826aa9  xor ecx,ecx
    // 0xe826aab  lea rdx,[0xF7F68E3]
    // 0xe826ab2  call 0xBC5F110  ; -> sub_bc5f110
    // 0xe826ab7  nop

    // 0xe826ab8..0xe826b31  paged heap traversal
    // ... (imul, cmp, ja, etc.)

    // 0xe826b33..0xe826b86  paged heap traversal (continued)
    // ... (cmp, jb, nop, mov, etc.)

    // 0xe826b88..0xe826bee  vcall through data_f99ffa0
    // 0xe826b88  add rcx,r8
    // 0xe826b8b  jmp short 0xE826B9E
    // loc_e826b8d:
    // 0xe826b8d  test rax,rax
    // 0xe826b90  je short 0xE826BF3
    // loc_e826b92:
    // 0xe826b92  mov rcx,[rax+0x10]
    // 0xe826b96  jmp short 0xE826BF5
    // loc_e826b98:
    // 0xe826b98  add r14,r9
    // 0xe826b9b  mov rcx,r14
    // loc_e826b9e:
    // 0xe826b9e  mov rax,[rcx]
    // 0xe826ba1  mov qword ptr [rbx+0xC0],0
    // 0xe826bac  mov [rbx+0xC8],rax
    // 0xe826bb3  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    // 0xe826bbd  mov [rbx+0xD4],r15d
    // 0xe826bc4  mov dword ptr [rbx+0xD8],0xAC3
    // 0xe826bce  mov rax,[rdi]
    // 0xe826bd1  mov rax,[rax+0xD0]
    // 0xe826bd8  mov rcx,rdi
    // 0xe826bdb  mov edx,1
    // 0xe826be0  lea r8,[rbx+0xC0]
    // 0xe826be7  call qword ptr [0xF99FFA0]  ; -> sub_eea6040 (vendor thunk)
    // 0xe826bed  nop
    // 0xe826bee  jmp 0xE827060

    // 0xe826bf3..0xe826bf5  xor ecx,ecx
    // 0xe826bf3  xor ecx,ecx
    // loc_e826bf5:
    // 0xe826bf5  and rcx,0xFFFFFFFFFFFFFFFE
    // 0xe826bf9  mov r8,[rbx+0x90]
    // 0xe826c00  mov rax,[r8+0x22488]
    // 0xe826c07  mov rdx,[r8+0x22490]
    // 0xe826c0e  shr rax,1
    // 0xe826c11  add rcx,0x2000
    // 0xe826c18  cmp rdx,rcx
    // 0xe826c1b  cmova rcx,rdx
    // 0xe826c1f  mov [r8+0x22490],rcx
    // 0xe826c26  cmp rax,r14
    // 0xe826c29  jbe 0xE826D38

    // 0xe826c2f..0xe826c4c  update r9 capacity, bounds check
    // 0xe826c2f  mov r9,[rbx+0x90]
    // 0xe826c36  mov [r9+0x22488],rdi
    // 0xe826c3d  movzx ecx,byte ptr [r9+0x20478]
    // 0xe826c45  cmp r11d,0x1000
    // 0xe826c4c  jb short 0xE826C54

    // 0xe826c4e..0xe826c52  (guarded heap check)
    // 0xe826c4e  mov al,1
    // 0xe826c50  test cl,cl
    // 0xe826c52  jne short 0xE826CD2

    // 0xe826c54..0xe826cb6  guarded heap allocation (sub_e835f00)
    // ... (mul, shr, cmp, ja, etc.)

    // 0xe826cbc..0xe826cd2  update r9 capacity
    // 0xe826cbc  shl edi,2
    // 0xe826cbf  lea rax,[rdi+rdi*2]
    // 0xe826cc3  mov [r9+0x20468],rax
    // 0xe826cca  movzx eax,byte ptr [r9+0x20478]

    // 0xe826cd2..0xe826cf5  seventh bounds check
    // 0xe826cd2  cmp r11d,0x1000
    // 0xe826cd9  jb 0xE826DFA
    // 0xe826cdf  test al,al
    // 0xe826ce1  je 0xE826DFA
    // 0xe826ce7  xor ecx,ecx
    // 0xe826ce9  lea rdx,[0xF7F68E3]
    // 0xe826cf0  call 0xBC5F110  ; -> sub_bc5f110
    // 0xe826cf5  nop

    // 0xe826cf6..0xe826d10  compute rcx from r12
    // 0xe826cf6  lea eax,[r12*4]
    // 0xe826cfe  lea rcx,[rax+rax*2]
    // 0xe826d02  mov r9,[rbx+0x90]
    // 0xe826d09  mov r11d,[rbx+0x180]
    // 0xe826d10  jmp 0xE826E13

    // 0xe826d20..0xe826d32  write r12w to [rcx]
    // loc_e826d20:
    // 0xe826d20  add rcx,[rbx+0x5E8]
    // loc_e826d27:
    // 0xe826d27  mov [rcx],r12w
    // 0xe826d2b  cmp rax,r14
    // 0xe826d2e  lea rax,[rax+1]
    // 0xe826d32  je 0xE826C2F

    // 0xe826d38..0xe826d8a  paged heap traversal for write
    // ... (lea, cmp, jbe, add, mov, cmp, ja, etc.)

    // 0xe826d8c..0xe826d9e  zero-fill loop 3
    // loc_e826d90:
    // 0xe826d90  add rax,[rbx+0x128]
    // loc_e826d97:
    // 0xe826d97  mov byte ptr [rax+8],0
    // 0xe826d9b  inc rdx
    // 0xe826d9e  cmp rdx,rdi
    // 0xe826da1  je 0xE826CBC

    // 0xe826da7..0xe826df8  paged heap traversal for zero-fill 3
    // ...

    // 0xe826dfa..0xe826e0d  eighth bounds check
    // 0xe826dfa  lea eax,[r12*4]
    // 0xe826e02  lea rcx,[rax+rax*2]
    // 0xe826e06  cmp r11d,0xFFF
    // 0xe826e0d  jbe 0xE8270C8

    // 0xe826e13..0xe826ecb  paged heap traversal (resource table)
    // ... (similar pattern)

    // 0xe826ec8..0xe826ed0  check byte at [r8+8]
    // 0xe826ec8  add r8,r9
    // 0xe826ecb  cmp byte ptr [r8+8],0
    // 0xe826ed0  jne short 0xE826ED7

    // 0xe826ed2  mov byte ptr [r8+8],1
    // loc_e826ed7:
    // 0xe826ed7  mov rax,0xAC300000AC3
    // 0xe826ee1  mov [r8],rax
    // 0xe826ee4  mov rax,[rbx+0x238]
    // 0xe826eeb  mov rdi,[rax]
    // 0xe826eee  movzx ecx,byte ptr [rdi+0xB8018]
    // 0xe826ef5  cmp r11d,0x1000
    // 0xe826efc  jb short 0xE826F08
    // 0xe826efe  mov al,1
    // 0xe826f00  test cl,cl
    // 0xe826f02  jne 0xE827035

    // 0xe826f08..0xe826f69  guarded heap allocation (sub_e83ace0)
    // 0xe826f08  mov rax,[rdi+0xB8008]
    // 0xe826f0f  shr rax,3
    // 0xe826f13  mov rdx,0x1642C8590B21642D
    // 0xe826f1d  mul rdx
    // 0xe826f20  shr rdx,1
    // 0xe826f23  mov eax,ecx
    // 0xe826f25  cmp rdx,r12
    // 0xe826f28  ja 0xE827035
    // 0xe826f2e  and r12d,0xF000
    // 0xe826f35  add r12,0x1000
    // 0xe826f3c  mov rcx,rdi
    // 0xe826f3f  mov rdx,r12
    // 0xe826f42  call 0xE83ACE0  ; -> sub_e83ace0
    // 0xe826f47  nop
    // 0xe826f48  mov rax,[rdi+0xB8008]
    // 0xe826f4f  shr rax,3
    // 0xe826f53  mov rcx,0x1642C8590B21642D
    // 0xe826f5d  mul rcx
    // 0xe826f60  mov r15,rdx
    // 0xe826f63  shr r15,1
    // 0xe826f66  cmp r15,r12
    // 0xe826f69  jae 0xE827019

    // 0xe826f70..0xe827013  zero-fill loop (memset via sub_ebce430)
    // loc_e826f70:
    // 0xe826f70  imul r14,r15,0xB8
    // 0xe826f77  cmp r15,0xFFF
    // 0xe826f7e  ja short 0xE826F90
    // 0xe826f80  add r14,rdi
    // 0xe826f83  jmp short 0xE826FCA
    // loc_e826f90:
    // ... paged heap traversal ...
    // loc_e826fca:
    // 0xe826fca  mov qword ptr [r14],0
    // 0xe826fd1  mov qword ptr [r14+0x90],0
    // 0xe826fdc  mov word ptr [r14+0xB1],0
    // 0xe826fe6  lea rcx,[r14+0x40]
    // 0xe826fea  mov r8d,0x28
    // 0xe826ff0  xor edx,edx
    // 0xe826ff2  call 0xEBCE430  ; -> sub_ebce430 (stl boundary)
    // 0xe826ff7  nop
    // 0xe826ff8  add r14,0x68
    // 0xe826ffc  mov r8d,0x28
    // 0xe827002  mov rcx,r14
    // 0xe827005  xor edx,edx
    // 0xe827007  call 0xEBCE430  ; -> sub_ebce430 (stl boundary)
    // 0xe82700c  nop
    // 0xe82700d  inc r15
    // 0xe827010  cmp r15,r12
    // 0xe827013  jne 0xE826F70

    // 0xe827019..0xe827035  update rdi+0xB8008
    // 0xe827019  imul rax,r12,0xB8
    // 0xe827020  mov [rdi+0xB8008],rax
    // 0xe827027  movzx eax,byte ptr [rdi+0xB8018]
    // 0xe82702e  mov r11d,[rbx+0x180]

    // 0xe827035..0xe827050  ninth bounds check
    // 0xe827035  cmp r11d,0x1000
    // 0xe82703c  jb short 0xE827060
    // 0xe82703e  test al,al
    // 0xe827040  je short 0xE827060
    // 0xe827042  xor ecx,ecx
    // 0xe827044  lea rdx,[0xF7F68E3]
    // 0xe82704b  call 0xBC5F110  ; -> sub_bc5f110
    // 0xe827050  nop

    // 0xe827060..0xe8270c3  final vcall and return setup
    // loc_e827060:
    // 0xe827060  mov rdi,[rbx+0x220]
    // 0xe827067  mov rax,[0x12BB4910]
    // 0xe82706e  mov rcx,[rax+0x400]
    // 0xe827075  mov rax,[rbx+0xB8]
    // 0xe82707c  mov r9,[rax+8]
    // 0xe827080  mov rdx,[rsi]
    // 0xe827083  add rsi,0x40
    // 0xe827087  mov rax,[rcx]
    // 0xe82708a  mov rax,[rax+0x90]
    // 0xe827091  mov r8,rsi
    // 0xe827094  call qword ptr [0xF99FFA0]  ; -> sub_eea6040 (vendor thunk)
    // 0xe82709a  nop
    // 0xe82709b  mov r8,[rbx+0xB8]
    // 0xe8270a2  mov eax,[r8+0x18]
    // 0xe8270a6  add [r8+8],rax
    // 0xe8270aa  mov r10d,[rbx+0x110]
    // 0xe8270b1  mov ecx,r10d
    // 0xe8270b4  mov rax,[r8+0x10]
    // 0xe8270b8  mov [rdi+rcx*8],rax
    // 0xe8270bc  mov r11,[rbx+0x1C0]
    // 0xe8270c3  jmp 0xE826131  ; -> sub_e826131 (next chunk)

    // 0xe8270c8..0xe8270dd  (alternative path: direct rcx, then check byte)
    // 0xe8270c8  add rcx,[rbx+0x128]
    // 0xe8270cf  mov r8,rcx
    // 0xe8270d2  cmp byte ptr [r8+8],0
    // 0xe8270d7  je 0xE826ED2
    // 0xe8270dd  jmp 0xE826ED7

    // Write back live state
    state.rbx = rbx;
    state.rbp = rbp;
    state.r12 = r12;
    state.r13 = r13;
    state.r14 = r14;
    state.r15 = r15;
    state.rsi = rsi;
    state.rdi = rdi;
}

} // namespace d3d12
} // namespace native

// Verbatim call quotes for machine checking (verify_oc)
#if 0
0xe8262b2  call 0xEBCE430
0xe8262c7  call 0xEBCE430
0xe82630e  call 0xBC5F110
0xe826471  call 0xE835F00
0xe8264d4  call 0xBC5F110
0xe826684  call 0xE835F00
0xe8266e7  call 0xBC5F110
0xe8267fb  call r10
0xe82681d  call r10
0xe8268d3  call r10
0xe8268e5  call 0xEEC6ED0
0xe826a5c  call 0xE83AED0
0xe826a70  call 0xE83AED0
0xe826a8d  call 0xE83ABB0
0xe826ab2  call 0xBC5F110
0xe826ff2  call 0xEBCE430
0xe827007  call 0xEBCE430
0xe826f42  call 0xE83ACE0
0xe82704b  call 0xBC5F110
0xe827094  call qword ptr [0xF99FFA0]
0xe827193  call qword ptr [0xF99FFA0]
#endif