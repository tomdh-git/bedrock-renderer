## NEXT
DONE (orchestrator-written from stores.py and casewalk.py; joined D9c field map)

# GameplayMetadata and ServerGraphicsOverrideParameters field map (checklist D9c)

All lines below are verbatim from the listing. Call: stores.py lists every store into [reg+off] of the clone/producer listing; casewalk.py lists every [rdi+off] read on the visitor path from 0x6c2e820 rdi; joined as: offset | size | store site | read site | name only if an instruction/string shows it.

## Stores from gameplaymeta clone listing (lightgame_gameplaymeta_clone_53e5910_53e6114.txt)
Stores.py found 2 store instructions into [reg+off]:

    0x53e5f51  mov dword ptr [0],0xDEADC0DE
    0x53e6000  movups [rax],xmm0

## Reads from serveroverride producer casewalk (lightgame_serveroverride_producer_6c2e820_6c2f87e.txt 0x6c2e820 rdi)
Casewalk found 829 reachable [rdi+off] read instructions:

    0x6c2ee9d  lea rcx,[rdi+0x80]
    0x6c2eeb4  lea rcx,[rdi+0xC0]
    0x6c2eecb  lea rcx,[rdi+0x100]
    0x6c2eee2  lea rcx,[rdi+0x140]
    0x6c2eef9  lea rcx,[rdi+0x180]
    0x6c2ef13  lea rcx,[rdi+0x1C0]
    0x6c2ef2d  lea rcx,[rdi+0x200]
    0x6c2ef47  lea rcx,[rdi+0x240]
    0x6c2ef61  lea rcx,[rdi+0x280]
    0x6c2ef78  lea rcx,[rdi+0x2C0]
    0x6c2ef8f  lea rcx,[rdi+0x300]
    0x6c2efa6  lea rcx,[rdi+0x340]
    0x6c2efbd  lea rcx,[rdi+0x380]
    0x6c2efd4  lea rcx,[rdi+0x3C0]
    0x6c2efeb  lea rcx,[rdi+0x400]
    0x6c2f002  lea rcx,[rdi+0x440]
    0x6c2f019  lea rcx,[rdi+0x480]
    0x6c2f030  mov r15,[rdi+0x4C8]
    0x6c2f15a  lea rcx,[rdi+0x500]
    0x6c2f171  lea rcx,[rdi+0x540]
    0x6c2f188  lea rcx,[rdi+0x580]
    0x6c2f19f  lea rcx,[rdi+0x5C0]
    0x6c2f1b6  lea rcx,[rdi+0x600]
    0x6c2f1cd  lea rcx,[rdi+0x640]
    0x6c2f1e4  lea rcx,[rdi+0x680]
    0x6c2f1fb  lea rcx,[rdi+0x6C0]
    0x6c2f212  lea rcx,[rdi+0x700]
    0x6c2f229  lea rcx,[rdi+0x740]
    0x6c2f240  lea rcx,[rdi+0x780]
    0x6c2f257  lea rcx,[rdi+0x7C0]
    0x6c2f26e  lea rcx,[rdi+0x800]
    0x6c2f285  lea rcx,[rdi+0x840]
    0x6c2f29c  lea rcx,[rdi+0x880]
    0x6c2f2b3  lea rcx,[rdi+0x8C0]
    0x6c2f2ca  lea rcx,[rdi+0x900]
    0x6c2f2e1  lea rcx,[rdi+0x940]
    0x6c2f2f8  lea rcx,[rdi+0x980]
    0x6c2f30f  lea rcx,[rdi+0x9C0]
    0x6c2f326  lea rcx,[rdi+0xA00]
    0x6c2f33d  mov r14,[rdi+0xBC8]
    0x6c2f4e0  lea rcx,[rdi+0xC00]
    0x6c2f4fa  lea rcx,[rdi+0xC80]
    0x6c2f514  lea rcx,[rdi+0xCC0]
    0x6c2f63e  mov rax,[rdi]
    0x6c2f6e3  mov rax,[rdi]

## Field join table: offset | size | store site | read site | name
| offset | size | store site | read site | name |
|---|---|---|---|---|
| 0x00 | 4-dword | 0x53e5f51 mov dword ptr [0],0xDEADC0DE | | |
| 0x00 | 16-xmm | 0x53e6000 movups [rax],xmm0 | | |
| 0x80 | - | | 0x6c2ee9d lea rcx,[rdi+0x80] | |
| 0xC0 | - | | 0x6c2eeb4 lea rcx,[rdi+0xC0] | |
| 0x100 | - | | 0x6c2eecb lea rcx,[rdi+0x100] | |
| 0x140 | - | | 0x6c2eee2 lea rcx,[rdi+0x140] | |
| 0x180 | - | | 0x6c2eef9 lea rcx,[rdi+0x180] | |
| 0x1C0 | - | | 0x6c2ef13 lea rcx,[rdi+0x1C0] | |
| 0x200 | - | | 0x6c2ef2d lea rcx,[rdi+0x200] | |
| 0x240 | - | | 0x6c2ef47 lea rcx,[rdi+0x240] | |
| 0x280 | - | | 0x6c2ef61 lea rcx,[rdi+0x280] | |
| 0x2C0 | - | | 0x6c2ef78 lea rcx,[rdi+0x2C0] | |
| 0x300 | - | | 0x6c2ef8f lea rcx,[rdi+0x300] | |
| 0x340 | - | | 0x6c2efa6 lea rcx,[rdi+0x340] | |
| 0x380 | - | | 0x6c2efbd lea rcx,[rdi+0x380] | |
| 0x3C0 | - | | 0x6c2efd4 lea rcx,[rdi+0x3C0] | |
| 0x400 | - | | 0x6c2efeb lea rcx,[rdi+0x400] | |
| 0x440 | - | | 0x6c2f002 lea rcx,[rdi+0x440] | |
| 0x480 | - | | 0x6c2f019 lea rcx,[rdi+0x480] | |
| 0x4C8 | 8-qword | | 0x6c2f030 mov r15,[rdi+0x4C8] | |
| 0x500 | - | | 0x6c2f15a lea rcx,[rdi+0x500] | |
| 0x540 | - | | 0x6c2f171 lea rcx,[rdi+0x540] | |
| 0x580 | - | | 0x6c2f188 lea rcx,[rdi+0x580] | |
| 0x5C0 | - | | 0x6c2f19f lea rcx,[rdi+0x5C0] | |
| 0x600 | - | | 0x6c2f1b6 lea rcx,[rdi+0x600] | |
| 0x640 | - | | 0x6c2f1cd lea rcx,[rdi+0x640] | |
| 0x680 | - | | 0x6c2f1e4 lea rcx,[rdi+0x680] | |
| 0x6C0 | - | | 0x6c2f1fb lea rcx,[rdi+0x6C0] | |
| 0x700 | - | | 0x6c2f212 lea rcx,[rdi+0x700] | |
| 0x740 | - | | 0x6c2f229 lea rcx,[rdi+0x740] | |
| 0x780 | - | | 0x6c2f240 lea rcx,[rdi+0x780] | |
| 0x7C0 | - | | 0x6c2f257 lea rcx,[rdi+0x7C0] | |
| 0x800 | - | | 0x6c2f26e lea rcx,[rdi+0x800] | |
| 0x840 | - | | 0x6c2f285 lea rcx,[rdi+0x840] | |
| 0x880 | - | | 0x6c2f29c lea rcx,[rdi+0x880] | |
| 0x8C0 | - | | 0x6c2f2b3 lea rcx,[rdi+0x8C0] | |
| 0x900 | - | | 0x6c2f2ca lea rcx,[rdi+0x900] | |
| 0x940 | - | | 0x6c2f2e1 lea rcx,[rdi+0x940] | |
| 0x980 | - | | 0x6c2f2f8 lea rcx,[rdi+0x980] | |
| 0x9C0 | - | | 0x6c2f30f lea rcx,[rdi+0x9C0] | |
| 0xA00 | - | | 0x6c2f326 lea rcx,[rdi+0xA00] | |
| 0xBC8 | 8-qword | | 0x6c2f33d mov r14,[rdi+0xBC8] | |
| 0xC00 | - | | 0x6c2f4e0 lea rcx,[rdi+0xC00] | |
| 0xC80 | - | | 0x6c2f4fa lea rcx,[rdi+0xC80] | |
| 0xCC0 | - | | 0x6c2f514 lea rcx,[rdi+0xCC0] | |

## Verbatim instruction disassembly from both listings (continued from above)

    0x6c2f5ab lea rcx,[0x128C4FD0]
    0x6c2f5b7 cmp byte ptr [rbp+0xAF8],1
    0x6c2f5be jne short 0x6C2F5CC
    0x6c2f5c0 mov rcx,[rbp+0xAF0]
    0x6c2f5c7 call 0x3B2020
    0x6c2f5cc lea rcx,[rbp-0x50]
    0x6c2f5d0 call 0x67B8030
    0x6c2f5d5 movaps xmm6,[rbp+0xB60]
    0x6c2f5dc movaps xmm7,[rbp+0xB70]
    0x6c2f5e3 movaps xmm8,[rbp+0xB80]
    0x6c2f5eb add rsp,0xC18
    0x6c2f5f2 pop rbx
    0x6c2f5f3 pop rdi
    0x6c2f5f4 pop rsi
    0x6c2f5f5 pop r12
    0x6c2f5f7 pop r13
    0x6c2f5f9 pop r14
    0x6c2f5fb pop r15
    0x6c2f5fd pop rbp
    0x6c2f5fe ret
    0x6c2f5ff xor esi,esi
    0x6c2f601 mov rdi,[0x128C5048]
    0x6c2f608 mov [rbp+0xAF0],rbx
    0x6c2f60f mov byte ptr [rbp+0xAF8],1
    0x6c2f616 mov [rbp+0xB00],r14
    0x6c2f61d mov [rbp+0xB08],rsi
    0x6c2f624 mov [rbp+0xB10],rdi
    0x6c2f62b test r14,r14
    0x6c2f62e je 0x6C2F722
    0x6c2f634 cmp byte ptr [r14],1
    0x6c2f638 jne 0x6C2F722
    0x6c2f63e mov rax,[rdi]
    0x6c2f641 mov rax,[rax+8]
    0x6c2f645 mov rcx,rdi
    0x6c2f648 call qword ptr [0xF99FFA0]
    0x6c2f64e nop
    0x6c2f64f test al,al
    0x6c2f651 je 0x6C2F722
    0x6c2f657 cmp byte ptr [r14],0
    0x6c2f65b jne short 0x6C2F668
    0x6c2f65d mov dword ptr [0],0xDEADC0DE
    0x6c2f668 mov eax,[0x12A00448]
    0x6c2f66e mov ecx,[0x128767C8]
    0x6c2f674 mov rdx,gs:[0x58]
    0x6c2f67d mov rcx,[rdx+rcx*8]
    0x6c2f681 cmp eax,[rcx+4]
    0x6c2f687 jg 0x6C2F7EF
    0x6c2f68d lea rcx,[0x12A00310]
    0x6c2f694 mov byte ptr [rbp+0xAD8],0
    0x6c2f6a2 lea rbx,[rbp+0xAE0]
    0x6c2f6a9 mov qword ptr [rbp+0xAE8],0
    0x6c2f6b4 mov byte ptr [rbp+0xB50],0
    0x6c2f6bb lea r8,[rbp+0xB18]
    0x6c2f6c2 mov rdx,rbx
    0x6c2f6c5 call 0x39A7D40
    0x6c2f6ca nop
    0x6c2f6cb mov [rbp+0xAD8],al
    0x6c2f6d1 lea rax,[rbp-0x50]
    0x6c2f6d5 mov [rbp+0xB18],rax
    0x6c2f6dc mov byte ptr [rbp+0xB20],5
    0x6c2f6e3 mov rax,[rdi]
    0x6c2f6e6 mov rax,[rax+0x380]
    0x6c2f6ed lea rdx,[rbp+0xB18]
    0x6c2f6f4 mov rcx,rdi
    0x6c2f6f7 call qword ptr [0xF99FFA0]
    0x6c2f6fd nop
    0x6c2f6fe cmp byte ptr [rbp+0xAD8],1
    0x6c2f705 jne short 0x6C2F722
    0x6c2f707 mov r8,[rbp+0xAD0]
    0x6c2f70e add r8,0x60
    0x6c2f712 lea rcx,[0x1244FD00]
    0x6c2f719 mov rdx,rbx
    0x6c2f71c call 0x77A2500
    0x6c2f721 nop
    0x6c2f722 lea rax,[rbp+0xB00]
    0x6c2f729 xorps xmm0,xmm0
    0x6c2f72c movups [rax],xmm0
    0x6c2f72f test rsi,rsi
    0x6c2f732 je 0x6C2F5B7
    0x6c2f738 lock dec dword ptr [rsi+8]
    0x6c2f73c jne short 0x6C2F763
    0x6c2f73e mov rax,[rsi]
    0x6c2f741 mov rax,[rax]
    0x6c2f744 mov rcx,rsi
    0x6c2f747 call qword ptr [0xF99FFA0]
    0x6c2f74d lock dec dword ptr [rsi+0xC]
    0x6c2f751 jne short 0x6C2F763
    0x6c2f753 mov rax,[rsi]
    0x6c2f756 mov rax,[rax+8]
    0x6c2f75a mov rcx,rsi
    0x6c2f75d call qword ptr [0xF99FFA0]
    0x6c2f763 mov rsi,[rbp+0xB08]
    0x6c2f76a mov qword ptr [rbp+0xB10],0
    0x6c2f775 test rsi,rsi
    0x6c2f778 je 0x6C2F5B7
    0x6c2f77e lock dec dword ptr [rsi+8]
    0x6c2f782 jne 0x6C2F5B7
    0x6c2f788 mov rax,[rsi]
    0x6c2f78b mov rax,[rax]
    0x6c2f78e mov rcx,rsi
    0x6c2f791 call qword ptr [0xF99FFA0]
    0x6c2f797 lock dec dword ptr [rsi+0xC]
    0x6c2f79b jne 0x6C2F5B7
    0x6c2f7a1 mov rax,[rsi]
    0x6c2f7a4 mov rax,[rax+8]
    0x6c2f7a8 mov rcx,rsi
    0x6c2f7ab call qword ptr [0xF99FFA0]
    0x6c2f7b1 jmp 0x6C2F5B7
    0x6c2f7b6 mov ecx,0x18
    0x6c2f7bb call 0x9BC830
    0x6c2f7c0 nop
    0x6c2f7c1 jmp 0x6C2EA90
    0x6c2f7c6 mov ecx,0x80
    0x6c2f7cb call 0x9BC830
    0x6c2f7d0 nop
    0x6c2f7d1 jmp 0x6C2EAF9
    0x6c2f7d6 mov qword ptr [rsp+0x20],0
    0x6c2f7df xor ecx,ecx
    0x6c2f7e1 xor edx,edx
    0x6c2f7e3 xor r8d,r8d
    0x6c2f7e6 xor r9d,r9d
    0x6c2f7e9 call qword ptr [0xF9A8C78]
    0x6c2f7ef lea rcx,[0x12A00448]
    0x6c2f7f6 call 0xE938CB0
    0x6c2f7fb cmp dword ptr [0x12A00448],0xFFFFFFFF
    0x6c2f802 jne 0x6C2F68D
    0x6c2f808 lea rax,[0xF52E07A]
    0x6c2f80f mov [rbp+0xAC0],rax
    0x6c2f816 mov qword ptr [rbp+0xAC8],0x15
    0x6c2f821 movups xmm0,[0xF0BCBF8]
    0x6c2f828 movaps [rbp+0xAB0],xmm0
    0x6c2f82f lea rax,[0xF2D30F0]
    0x6c2f836 mov [rsp+0x28],rax
    0x6c2f83b mov dword ptr [rsp+0x20],0
    0x6c2f843 lea rcx,[0x12A00310]
    0x6c2f84a lea rdx,[rbp+0xAB0]
    0x6c2f851 lea r9,[rbp+0xAC0]
    0x6c2f858 mov r8b,1
    0x6c2f85b call 0x2FE330
    0x6c2f860 nop
    0x6c2f861 lea rcx,[0x6C40430]
    0x6c2f868 call 0xE935740
    0x6c2f86d lea rcx,[0x12A00448]
    0x6c2f874 call 0xE938D70
    0x6c2f879 jmp 0x6C2F68D