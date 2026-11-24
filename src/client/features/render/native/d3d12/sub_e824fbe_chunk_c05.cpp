// LIFT 0xe824fbe size 0x8525 1.26.62.01 sub_e824fbe
// CHUNK 0xe82c765..0xe82d4c4
#include "client/features/render/native/d3d12/sub_e824fbe_chunk_c05.h"

#if 0
0xe82c7d6  call qword ptr [0xF99FFA0]
0xe82c870  call qword ptr [0xF99FFA0]
0xe82c96b  call qword ptr [0xF99FFA0]
0xe82c9bb  call r10
0xe82ca5c  call qword ptr [0xF99FFA0]
0xe82caaf  call r10
0xe82cb8b  call 0xE81B4D0
0xe82cc6c  call qword ptr [0xF99FFA0]
0xe82cd02  call 0xEBCE430
0xe82cdc2  call 0xEBCE430
0xe82cf98  call qword ptr [0xF99FFA0]
0xe82cfc1  call 0xE81B720
0xe82cfde  call 0xE81B720
0xe82d01e  call qword ptr [0xF99FFA0]
0xe82d079  call r10
0xe82d0f6  call 0xE81B720
0xe82d12b  call 0xE81B720
0xe82d148  call 0xE81B720
0xe82d179  call 0xEBDB740
0xe82d198  call 0xE81D850
0xe82d1f2  call qword ptr [0xF99FFA0]
0xe82d28d  call r10
0xe82d2ec  call r10
0xe82d3d0  call r10
0xe82d458  call r10
0xe82d4be  call 0xEEC59E0
#endif

namespace native { namespace d3d12 {

static inline void sub_e824fbe_chunk_c05(ChunkState_e824fbe_c05& s) {
    void* rbx = s.rbx; void* rbp = s.rbp;
    std::uint64_t rcx = s.rcx, rsi = s.rsi, rdi = s.rdi, rax = s.rax, rdx = s.rdx, r10 = s.r10;

    // 0xe82c765  mov r9,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82c76c  mov rdx,[r9+0x30]
    /* translated */ (void)0;
    // 0xe82c770  mov dword ptr [r9+rcx*8+0xA45C],0xAC3
    /* translated */ (void)0;
    // 0xe82c77c  mov r9,[r9+0xA248]
    /* translated */ (void)0;
    // 0xe82c783  shl ecx,7
    /* translated */ (void)0;
    // 0xe82c786  mov rcx,[r9+rcx]
    /* translated */ (void)0;
    // 0xe82c78a  mov qword ptr [rbx+0x3B0],0
    /* translated */ (void)0;
    // 0xe82c795  mov [rbx+0x3B8],rcx
    /* translated */ (void)0;
    // 0xe82c79c  mov dword ptr [rbx+0x3C0],0xFFFFFFFF
    /* translated */ (void)0;
    // 0xe82c7a6  mov [rbx+0x3C4],r8d
    /* translated */ (void)0;
    // 0xe82c7ad  mov dword ptr [rbx+0x3C8],0xAC3
    /* translated */ (void)0;
    // 0xe82c7b7  mov rcx,[rdx]
    /* translated */ (void)0;
    // 0xe82c7ba  mov r9,[rcx+0xD0]
    /* translated */ (void)0;
    // 0xe82c7c1  mov rcx,rdx
    /* translated */ (void)0;
    // 0xe82c7c4  mov edx,1
    /* translated */ (void)0;
    // 0xe82c7c9  lea r8,[rbx+0x3B0]
    /* translated */ (void)0;
    // 0xe82c7d0  mov r15b,al
    /* translated */ (void)0;
    // 0xe82c7d3  mov rax,r9
    /* translated */ (void)0;
    // 0xe82c7d6  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82c7dc  nop
    /* translated */ (void)0;
    // 0xe82c7dd  mov eax,r15d
    /* translated */ (void)0;
    // 0xe82c7e0  mov r11,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82c7e7  jmp 0xE82CD6C
    /* translated */ (void)0;
    // 0xe82c7ec  or r10,r11
    /* translated */ (void)0;
    // 0xe82c7ef  mov [rdi+r9*8+0xA258],r10
    /* translated */ (void)0;
    // 0xe82c7f7  movzx ecx,word ptr [rdi+0xA250]
    /* translated */ (void)0;
    // 0xe82c7fe  mov [rdi+rcx*2+0x12458],dx
    /* translated */ (void)0;
    // 0xe82c806  inc ecx
    /* translated */ (void)0;
    // 0xe82c808  mov [rdi+0xA250],cx
    /* translated */ (void)0;
    // 0xe82c80f  mov rcx,0xAC300000AC3
    /* translated */ (void)0;
    // 0xe82c819  mov [rdi+rdx*8+0xA458],rcx
    /* translated */ (void)0;
    // 0xe82c821  mov rcx,r8
    /* translated */ (void)0;
    // 0xe82c824  movzx edx,al
    /* translated */ (void)0;
    // 0xe82c827  inc al
    /* translated */ (void)0;
    // 0xe82c829  shl edx,4
    /* translated */ (void)0;
    // 0xe82c82c  mov r8d,[r14+0x50]
    /* translated */ (void)0;
    // 0xe82c830  add r8,[rsi+0x9B21D0]
    /* translated */ (void)0;
    // 0xe82c837  mov [rbx+rdx+0x3B0],r8
    /* translated */ (void)0;
    // 0xe82c83f  movzx r8d,word ptr [r14+0x58]
    /* translated */ (void)0;
    // 0xe82c844  mov [rbx+rdx+0x3BC],r8d
    /* translated */ (void)0;
    // 0xe82c84c  imul r8d,[r14+0x54]
    /* translated */ (void)0;
    // 0xe82c851  mov [rbx+rdx+0x3B8],r8d
    /* translated */ (void)0;
    // 0xe82c859  movzx r8d,al
    /* translated */ (void)0;
    // 0xe82c85d  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82c860  mov rax,[rax+0x160]
    /* translated */ (void)0;
    // 0xe82c867  xor edx,edx
    /* translated */ (void)0;
    // 0xe82c869  lea r9,[rbx+0x3B0]
    /* translated */ (void)0;
    // 0xe82c870  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82c876  nop
    /* translated */ (void)0;
    // 0xe82c877  mov rsi,[0x12BB4910]
    /* translated */ (void)0;
    // 0xe82c87e  mov r10,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82c885  movzx eax,word ptr [r10+0x78]
    /* translated */ (void)0;
    // 0xe82c88a  shl eax,7
    /* translated */ (void)0;
    // 0xe82c88d  lea r14,[rsi+rax]
    /* translated */ (void)0;
    // 0xe82c891  add r14,0x9B2178
    /* translated */ (void)0;
    // 0xe82c898  movzx edi,word ptr [r10+0x5C]
    /* translated */ (void)0;
    // 0xe82c89d  cmp edi,0xFFFF
    /* translated */ (void)0;
    // 0xe82c8a3  jne short 0xE82C8AC
    /* translated */ (void)0;
    // 0xe82c8a5  mov edi,[r14+0x60]
    /* translated */ (void)0;
    // 0xe82c8a9  shr edi,5
    /* translated */ (void)0;
    // 0xe82c8ac  movzx ecx,word ptr [r10+0x74]
    /* translated */ (void)0;
    // 0xe82c8b1  cmp rcx,0xFFFF
    /* translated */ (void)0;
    // 0xe82c8b8  je 0xE82C97B
    /* translated */ (void)0;
    // 0xe82c8be  imul r15,rcx,0x78
    /* translated */ (void)0;
    // 0xe82c8c2  movzx eax,cx
    /* translated */ (void)0;
    // 0xe82c8c5  cmp eax,0xFFF
    /* translated */ (void)0;
    // 0xe82c8ca  ja 0xE82C9F3
    /* translated */ (void)0;
    // 0xe82c8d0  mov eax,ecx
    /* translated */ (void)0;
    // 0xe82c8d2  shr eax,6
    /* translated */ (void)0;
    // 0xe82c8d5  mov r9,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82c8dc  mov rdx,[r9+rax*8+0x48]
    /* translated */ (void)0;
    // 0xe82c8e1  mov r8d,1
    /* translated */ (void)0;
    // 0xe82c8e7  shl r8,cl
    /* translated */ (void)0;
    // 0xe82c8ea  bt rdx,rcx
    /* translated */ (void)0;
    // 0xe82c8ee  jae 0xE82C9C4
    /* translated */ (void)0;
    // 0xe82c8f4  mov eax,[r9+rcx*8+0x24C]
    /* translated */ (void)0;
    // 0xe82c8fc  cmp eax,0xAC3
    /* translated */ (void)0;
    // 0xe82c901  je 0xE82C9F3
    /* translated */ (void)0;
    // 0xe82c907  mov r8,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82c90e  mov rdx,[r8+0x30]
    /* translated */ (void)0;
    // 0xe82c912  mov dword ptr [r8+rcx*8+0x24C],0xAC3
    /* translated */ (void)0;
    // 0xe82c91e  mov rcx,[r8+0x38]
    /* translated */ (void)0;
    // 0xe82c922  mov rcx,[rcx+r15]
    /* translated */ (void)0;
    // 0xe82c926  mov qword ptr [rbx+0xC0],0
    /* translated */ (void)0;
    // 0xe82c931  mov [rbx+0xC8],rcx
    /* translated */ (void)0;
    // 0xe82c938  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    /* translated */ (void)0;
    // 0xe82c942  mov [rbx+0xD4],eax
    /* translated */ (void)0;
    // 0xe82c948  mov dword ptr [rbx+0xD8],0xAC3
    /* translated */ (void)0;
    // 0xe82c952  mov rax,[rdx]
    /* translated */ (void)0;
    // 0xe82c955  mov rax,[rax+0xD0]
    /* translated */ (void)0;
    // 0xe82c95c  mov rcx,rdx
    /* translated */ (void)0;
    // 0xe82c95f  mov edx,1
    /* translated */ (void)0;
    // 0xe82c964  lea r8,[rbx+0xC0]
    /* translated */ (void)0;
    // 0xe82c96b  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82c971  nop
    /* translated */ (void)0;
    // 0xe82c972  mov r10,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82c979  jmp short 0xE82C9F3
    /* translated */ (void)0;
    // 0xe82c97b  mov rax,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82c982  mov rcx,[rax+0x30]
    /* translated */ (void)0;
    // 0xe82c986  movzx r8d,word ptr [r10+0x5A]
    /* translated */ (void)0;
    // 0xe82c98b  shl r8d,5
    /* translated */ (void)0;
    // 0xe82c98f  mov r9,[r14]
    /* translated */ (void)0;
    // 0xe82c992  mov rdx,[rsi+0x19F48]
    /* translated */ (void)0;
    // 0xe82c999  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82c99c  mov rax,[rax+0x1D8]
    /* translated */ (void)0;
    // 0xe82c9a3  xor esi,esi
    /* translated */ (void)0;
    // 0xe82c9a5  mov r10,[0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82c9ac  movdqu [rsp+0x28],xmm9
    /* translated */ (void)0;
    // 0xe82c9b3  mov [rsp+0x20],r8
    /* translated */ (void)0;
    // 0xe82c9b8  mov r8d,edi
    /* translated */ (void)0;
    // 0xe82c9bb  call r10
    /* translated */ (void)0;
    // 0xe82c9be  nop
    /* translated */ (void)0;
    // 0xe82c9bf  jmp 0xE82CE15
    /* translated */ (void)0;
    // 0xe82c9c4  or rdx,r8
    /* translated */ (void)0;
    // 0xe82c9c7  mov [r9+rax*8+0x48],rdx
    /* translated */ (void)0;
    // 0xe82c9cc  movzx eax,word ptr [r9+0x40]
    /* translated */ (void)0;
    // 0xe82c9d1  mov [r9+rax*2+0x8248],cx
    /* translated */ (void)0;
    // 0xe82c9da  inc eax
    /* translated */ (void)0;
    // 0xe82c9dc  mov [r9+0x40],ax
    /* translated */ (void)0;
    // 0xe82c9e1  mov rax,0xAC300000AC3
    /* translated */ (void)0;
    // 0xe82c9eb  mov [r9+rcx*8+0x248],rax
    /* translated */ (void)0;
    // 0xe82c9f3  lea r8,[rsi+r15]
    /* translated */ (void)0;
    // 0xe82c9f7  add r8,0x93A178
    /* translated */ (void)0;
    // 0xe82c9fe  mov esi,[r10+0x44]
    /* translated */ (void)0;
    // 0xe82ca02  mov r9d,[r10+0x48]
    /* translated */ (void)0;
    // 0xe82ca06  mov ecx,[r8+0x60]
    /* translated */ (void)0;
    // 0xe82ca0a  cmp esi,0xFFFFFFFF
    /* translated */ (void)0;
    // 0xe82ca0d  jne short 0xE82CA18
    /* translated */ (void)0;
    // 0xe82ca0f  mov eax,ecx
    /* translated */ (void)0;
    // 0xe82ca11  xor edx,edx
    /* translated */ (void)0;
    // 0xe82ca13  div r9d
    /* translated */ (void)0;
    // 0xe82ca16  mov esi,eax
    /* translated */ (void)0;
    // 0xe82ca18  cmp r9d,2
    /* translated */ (void)0;
    // 0xe82ca1c  mov rax,[r8+0x58]
    /* translated */ (void)0;
    // 0xe82ca20  mov [rbx+0xC0],rax
    /* translated */ (void)0;
    // 0xe82ca27  mov [rbx+0xC8],ecx
    /* translated */ (void)0;
    // 0xe82ca2d  mov eax,0x2A
    /* translated */ (void)0;
    // 0xe82ca32  mov ecx,0x39
    /* translated */ (void)0;
    // 0xe82ca37  cmove eax,ecx
    /* translated */ (void)0;
    // 0xe82ca3a  mov [rbx+0xCC],eax
    /* translated */ (void)0;
    // 0xe82ca40  mov rax,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82ca47  mov rcx,[rax+0x30]
    /* translated */ (void)0;
    // 0xe82ca4b  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82ca4e  mov rax,[rax+0x158]
    /* translated */ (void)0;
    // 0xe82ca55  lea rdx,[rbx+0xC0]
    /* translated */ (void)0;
    // 0xe82ca5c  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82ca62  nop
    /* translated */ (void)0;
    // 0xe82ca63  mov rax,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82ca6a  mov rcx,[rax+0x30]
    /* translated */ (void)0;
    // 0xe82ca6e  mov rax,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82ca75  movzx r8d,word ptr [rax+0x5A]
    /* translated */ (void)0;
    // 0xe82ca7a  shl r8d,5
    /* translated */ (void)0;
    // 0xe82ca7e  mov r9,[r14]
    /* translated */ (void)0;
    // 0xe82ca81  mov rax,[0x12BB4910]
    /* translated */ (void)0;
    // 0xe82ca88  mov rdx,[rax+0x19F50]
    /* translated */ (void)0;
    // 0xe82ca8f  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82ca92  mov rax,[rax+0x1D8]
    /* translated */ (void)0;
    // 0xe82ca99  mov r10,[0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82caa0  movdqu [rsp+0x28],xmm9
    /* translated */ (void)0;
    // 0xe82caa7  mov [rsp+0x20],r8
    /* translated */ (void)0;
    // 0xe82caac  mov r8d,edi
    /* translated */ (void)0;
    // 0xe82caaf  call r10
    /* translated */ (void)0;
    // 0xe82cab2  nop
    /* translated */ (void)0;
    // 0xe82cab3  jmp 0xE82CE15
    /* translated */ (void)0;
    // 0xe82cab8  or rdx,r8
    /* translated */ (void)0;
    // 0xe82cabb  mov [r9+rax*8+0x48],rdx
    /* translated */ (void)0;
    // 0xe82cac0  movzx eax,word ptr [r9+0x40]
    /* translated */ (void)0;
    // 0xe82cac5  mov [r9+rax*2+0x8248],r13w
    /* translated */ (void)0;
    // 0xe82cace  inc eax
    /* translated */ (void)0;
    // 0xe82cad0  mov [r9+0x40],ax
    /* translated */ (void)0;
    // 0xe82cad5  mov rax,0xAC300000AC3
    /* translated */ (void)0;
    // 0xe82cadf  mov [r9+r13*8+0x248],rax
    /* translated */ (void)0;
    // 0xe82cae7  lea rcx,[rsi+rdi]
    /* translated */ (void)0;
    // 0xe82caeb  add rcx,0x93A178
    /* translated */ (void)0;
    // 0xe82caf2  mov esi,[r12+0x44]
    /* translated */ (void)0;
    // 0xe82caf7  cmp esi,0xFFFFFFFF
    /* translated */ (void)0;
    // 0xe82cafa  jne short 0xE82CB08
    /* translated */ (void)0;
    // 0xe82cafc  mov eax,[rcx+0x60]
    /* translated */ (void)0;
    // 0xe82caff  xor edx,edx
    /* translated */ (void)0;
    // 0xe82cb01  div dword ptr [r12+0x48]
    /* translated */ (void)0;
    // 0xe82cb06  mov esi,eax
    /* translated */ (void)0;
    // 0xe82cb08  mov r8,[rbx+0xA0]
    /* translated */ (void)0;
    // 0xe82cb0f  mov eax,[r8+0x94]
    /* translated */ (void)0;
    // 0xe82cb16  lea edx,[rax+1]
    /* translated */ (void)0;
    // 0xe82cb19  mov [r8+0x94],edx
    /* translated */ (void)0;
    // 0xe82cb20  mov rdx,[r8+0xA0]
    /* translated */ (void)0;
    // 0xe82cb27  mov r8,rax
    /* translated */ (void)0;
    // 0xe82cb2a  shl r8,7
    /* translated */ (void)0;
    // 0xe82cb2e  lea rax,[r8+rax*8]
    /* translated */ (void)0;
    // 0xe82cb32  lea rdi,[rdx+rax]
    /* translated */ (void)0;
    // 0xe82cb36  mov r8,[rbx+0x170]
    /* translated */ (void)0;
    // 0xe82cb3d  mov [rdx+rax+0x60],r8
    /* translated */ (void)0;
    // 0xe82cb42  mov r8,[rbx+0x380]
    /* translated */ (void)0;
    // 0xe82cb49  mov [rdx+rax+0x68],r8
    /* translated */ (void)0;
    // 0xe82cb4e  mov r8,[rcx+0x58]
    /* translated */ (void)0;
    // 0xe82cb52  mov [rdx+rax+0x50],r8
    /* translated */ (void)0;
    // 0xe82cb57  mov ecx,[rcx+0x60]
    /* translated */ (void)0;
    // 0xe82cb5a  mov [rdx+rax+0x58],ecx
    /* translated */ (void)0;
    // 0xe82cb5e  cmp dword ptr [r12+0x48],2
    /* translated */ (void)0;
    // 0xe82cb64  mov ecx,0x2A
    /* translated */ (void)0;
    // 0xe82cb69  mov r8d,0x39
    /* translated */ (void)0;
    // 0xe82cb6f  cmove ecx,r8d
    /* translated */ (void)0;
    // 0xe82cb73  mov [rdx+rax+0x5C],ecx
    /* translated */ (void)0;
    // 0xe82cb77  mov rcx,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82cb7e  mov rdx,rdi
    /* translated */ (void)0;
    // 0xe82cb81  mov r8,r12
    /* translated */ (void)0;
    // 0xe82cb84  lea r9,[rbx+0xC0]
    /* translated */ (void)0;
    // 0xe82cb8b  call 0xE81B4D0
    /* translated */ (void)0;
    // 0xe82cb90  nop
    /* translated */ (void)0;
    // 0xe82cb91  mov r12d,eax
    /* translated */ (void)0;
    // 0xe82cb94  mov rax,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82cb9b  movzx ecx,word ptr [rax+0x76]
    /* translated */ (void)0;
    // 0xe82cb9f  cmp rcx,0xFFFF
    /* translated */ (void)0;
    // 0xe82cba6  je 0xE82CCE0
    /* translated */ (void)0;
    // 0xe82cbac  mov r15d,ecx
    /* translated */ (void)0;
    // 0xe82cbaf  shl r15d,7
    /* translated */ (void)0;
    // 0xe82cbb3  add r15,[0x12BB4910]
    /* translated */ (void)0;
    // 0xe82cbba  movzx eax,cx
    /* translated */ (void)0;
    // 0xe82cbbd  cmp eax,0xFFF
    /* translated */ (void)0;
    // 0xe82cbc2  ja 0xE82CCAD
    /* translated */ (void)0;
    // 0xe82cbc8  mov eax,ecx
    /* translated */ (void)0;
    // 0xe82cbca  shr eax,6
    /* translated */ (void)0;
    // 0xe82cbcd  mov r9,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82cbd4  mov rdx,[r9+rax*8+0xA258]
    /* translated */ (void)0;
    // 0xe82cbdc  mov r8d,1
    /* translated */ (void)0;
    // 0xe82cbe2  shl r8,cl
    /* translated */ (void)0;
    // 0xe82cbe5  bt rdx,rcx
    /* translated */ (void)0;
    // 0xe82cbe9  jae 0xE82CC75
    /* translated */ (void)0;
    // 0xe82cbef  mov eax,[r9+rcx*8+0xA45C]
    /* translated */ (void)0;
    // 0xe82cbf7  cmp eax,0xAC3
    /* translated */ (void)0;
    // 0xe82cbfc  je 0xE82CCAD
    /* translated */ (void)0;
    // 0xe82cc02  mov r8,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82cc09  mov rdx,[r8+0x30]
    /* translated */ (void)0;
    // 0xe82cc0d  mov dword ptr [r8+rcx*8+0xA45C],0xAC3
    /* translated */ (void)0;
    // 0xe82cc19  mov r8,[r8+0xA248]
    /* translated */ (void)0;
    // 0xe82cc20  shl ecx,7
    /* translated */ (void)0;
    // 0xe82cc23  mov rcx,[r8+rcx]
    /* translated */ (void)0;
    // 0xe82cc27  mov qword ptr [rbx+0x3B0],0
    /* translated */ (void)0;
    // 0xe82cc32  mov [rbx+0x3B8],rcx
    /* translated */ (void)0;
    // 0xe82cc39  mov dword ptr [rbx+0x3C0],0xFFFFFFFF
    /* translated */ (void)0;
    // 0xe82cc43  mov [rbx+0x3C4],eax
    /* translated */ (void)0;
    // 0xe82cc49  mov dword ptr [rbx+0x3C8],0xAC3
    /* translated */ (void)0;
    // 0xe82cc53  mov rax,[rdx]
    /* translated */ (void)0;
    // 0xe82cc56  mov rax,[rax+0xD0]
    /* translated */ (void)0;
    // 0xe82cc5d  mov rcx,rdx
    /* translated */ (void)0;
    // 0xe82cc60  mov edx,1
    /* translated */ (void)0;
    // 0xe82cc65  lea r8,[rbx+0x3B0]
    /* translated */ (void)0;
    // 0xe82cc6c  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82cc72  nop
    /* translated */ (void)0;
    // 0xe82cc73  jmp short 0xE82CCAD
    /* translated */ (void)0;
    // 0xe82cc75  or rdx,r8
    /* translated */ (void)0;
    // 0xe82cc78  mov [r9+rax*8+0xA258],rdx
    /* translated */ (void)0;
    // 0xe82cc80  movzx eax,word ptr [r9+0xA250]
    /* translated */ (void)0;
    // 0xe82cc88  mov [r9+rax*2+0x12458],cx
    /* translated */ (void)0;
    // 0xe82cc91  inc eax
    /* translated */ (void)0;
    // 0xe82cc93  mov [r9+0xA250],ax
    /* translated */ (void)0;
    // 0xe82cc9b  mov rax,0xAC300000AC3
    /* translated */ (void)0;
    // 0xe82cca5  mov [r9+rcx*8+0xA458],rax
    /* translated */ (void)0;
    // 0xe82ccad  movzx eax,r12b
    /* translated */ (void)0;
    // 0xe82ccb1  inc r12b
    /* translated */ (void)0;
    // 0xe82ccb4  mov rdx,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82ccbb  mov ecx,[rdx+0x50]
    /* translated */ (void)0;
    // 0xe82ccbe  add rcx,[r15+0x9B21D0]
    /* translated */ (void)0;
    // 0xe82ccc5  shl eax,4
    /* translated */ (void)0;
    // 0xe82ccc8  mov [rdi+rax],rcx
    /* translated */ (void)0;
    // 0xe82cccc  movzx ecx,word ptr [rdx+0x58]
    /* translated */ (void)0;
    // 0xe82ccd0  mov [rdi+rax+0xC],ecx
    /* translated */ (void)0;
    // 0xe82ccd4  movzx ecx,word ptr [rdx+0x58]
    /* translated */ (void)0;
    // 0xe82ccd8  imul ecx,[rdx+0x54]
    /* translated */ (void)0;
    // 0xe82ccdc  mov [rdi+rax+8],ecx
    /* translated */ (void)0;
    // 0xe82cce0  cmp r12b,4
    /* translated */ (void)0;
    // 0xe82cce4  ja short 0xE82CD11
    /* translated */ (void)0;
    // 0xe82cce6  movzx r15d,r12b
    /* translated */ (void)0;
    // 0xe82ccea  nop [rax+rax]
    /* translated */ (void)0;
    // 0xe82ccf0  mov rcx,r15
    /* translated */ (void)0;
    // 0xe82ccf3  shl rcx,4
    /* translated */ (void)0;
    // 0xe82ccf7  add rcx,rdi
    /* translated */ (void)0;
    // 0xe82ccfa  mov r8d,0x10
    /* translated */ (void)0;
    // 0xe82cd00  xor edx,edx
    /* translated */ (void)0;
    // 0xe82cd02  call 0xEBCE430
    /* translated */ (void)0;
    // 0xe82cd07  nop
    /* translated */ (void)0;
    // 0xe82cd08  inc r15
    /* translated */ (void)0;
    // 0xe82cd0b  cmp r15b,5
    /* translated */ (void)0;
    // 0xe82cd0f  jne short 0xE82CCF0
    /* translated */ (void)0;
    // 0xe82cd11  mov [rdi+0x70],esi
    /* translated */ (void)0;
    // 0xe82cd14  mov rcx,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82cd1b  mov eax,[rcx+0x54]
    /* translated */ (void)0;
    // 0xe82cd1e  mov [rdi+0x74],eax
    /* translated */ (void)0;
    // 0xe82cd21  mov eax,[rcx+0x40]
    /* translated */ (void)0;
    // 0xe82cd24  mov [rdi+0x78],eax
    /* translated */ (void)0;
    // 0xe82cd27  mov qword ptr [rdi+0x7C],0
    /* translated */ (void)0;
    // 0xe82cd2f  jmp 0xE82CDF1
    /* translated */ (void)0;
    // 0xe82cd34  or r8,r9
    /* translated */ (void)0;
    // 0xe82cd37  mov [r10+rdx*8+0xA258],r8
    /* translated */ (void)0;
    // 0xe82cd3f  movzx edx,word ptr [r10+0xA250]
    /* translated */ (void)0;
    // 0xe82cd47  mov [r10+rdx*2+0x12458],cx
    /* translated */ (void)0;
    // 0xe82cd50  inc edx
    /* translated */ (void)0;
    // 0xe82cd52  mov [r10+0xA250],dx
    /* translated */ (void)0;
    // 0xe82cd5a  mov rdx,0xAC300000AC3
    /* translated */ (void)0;
    // 0xe82cd64  mov [r10+rcx*8+0xA458],rdx
    /* translated */ (void)0;
    // 0xe82cd6c  movzx ecx,al
    /* translated */ (void)0;
    // 0xe82cd6f  inc al
    /* translated */ (void)0;
    // 0xe82cd71  mov edx,[r11+0x50]
    /* translated */ (void)0;
    // 0xe82cd75  add rdx,[rdi+0x9B21D0]
    /* translated */ (void)0;
    // 0xe82cd7c  shl ecx,4
    /* translated */ (void)0;
    // 0xe82cd7f  mov [rsi+rcx],rdx
    /* translated */ (void)0;
    // 0xe82cd83  movzx edx,word ptr [r11+0x58]
    /* translated */ (void)0;
    // 0xe82cd88  mov [rsi+rcx+0xC],edx
    /* translated */ (void)0;
    // 0xe82cd8c  movzx edx,word ptr [r11+0x58]
    /* translated */ (void)0;
    // 0xe82cd91  imul edx,[r11+0x54]
    /* translated */ (void)0;
    // 0xe82cd96  mov [rsi+rcx+8],edx
    /* translated */ (void)0;
    // 0xe82cd9a  cmp al,4
    /* translated */ (void)0;
    // 0xe82cd9c  ja short 0xE82CDD1
    /* translated */ (void)0;
    // 0xe82cd9e  movzx edi,al
    /* translated */ (void)0;
    // 0xe82cda1  nop [rax+rax]
    /* translated */ (void)0;
    // 0xe82cdb0  mov rcx,rdi
    /* translated */ (void)0;
    // 0xe82cdb3  shl rcx,4
    /* translated */ (void)0;
    // 0xe82cdb7  add rcx,rsi
    /* translated */ (void)0;
    // 0xe82cdba  mov r8d,0x10
    /* translated */ (void)0;
    // 0xe82cdc0  xor edx,edx
    /* translated */ (void)0;
    // 0xe82cdc2  call 0xEBCE430
    /* translated */ (void)0;
    // 0xe82cdc7  nop
    /* translated */ (void)0;
    // 0xe82cdc8  inc rdi
    /* translated */ (void)0;
    // 0xe82cdcb  cmp dil,5
    /* translated */ (void)0;
    // 0xe82cdcf  jne short 0xE82CDB0
    /* translated */ (void)0;
    // 0xe82cdd1  mov rax,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82cdd8  mov eax,[rax+0x54]
    /* translated */ (void)0;
    // 0xe82cddb  mov [rsi+0x64],eax
    /* translated */ (void)0;
    // 0xe82cdde  mov eax,[rbx+0xC0]
    /* translated */ (void)0;
    // 0xe82cde4  mov [rsi+0x60],eax
    /* translated */ (void)0;
    // 0xe82cde7  mov qword ptr [rsi+0x68],0
    /* translated */ (void)0;
    // 0xe82cdef  xor esi,esi
    /* translated */ (void)0;
    // 0xe82cdf1  xor eax,eax
    /* translated */ (void)0;
    // 0xe82cdf3  cmp r13w,0xFFFF
    /* translated */ (void)0;
    // 0xe82cdf8  setne al
    /* translated */ (void)0;
    // 0xe82cdfb  mov rdx,[rbx+0xA0]
    /* translated */ (void)0;
    // 0xe82ce02  mov ecx,[rdx+0x11E0]
    /* translated */ (void)0;
    // 0xe82ce08  cmp ecx,[rdx+rax*4+0x90]
    /* translated */ (void)0;
    // 0xe82ce0f  je 0xE82D0DB
    /* translated */ (void)0;
    // 0xe82ce15  mov eax,esi
    /* translated */ (void)0;
    // 0xe82ce17  xor edx,edx
    /* translated */ (void)0;
    // 0xe82ce19  div dword ptr [rbx+0x338]
    /* translated */ (void)0;
    // 0xe82ce1f  sub eax,[rbx+0x334]
    /* translated */ (void)0;
    // 0xe82ce25  mov r9,[rbx+0xF0]
    /* translated */ (void)0;
    // 0xe82ce2c  mov ecx,[r9+0x54]
    /* translated */ (void)0;
    // 0xe82ce30  movzx edx,byte ptr [rbx+0x210]
    /* translated */ (void)0;
    // 0xe82ce37  mov r8,[rbx+0x3A8]
    /* translated */ (void)0;
    // 0xe82ce3e  lock add [r8+rdx*4],eax
    /* translated */ (void)0;
    // 0xe82ce43  imul ecx,eax
    /* translated */ (void)0;
    // 0xe82ce46  lock add [r8+rdx*4+0x18],ecx
    /* translated */ (void)0;
    // 0xe82ce4c  mov eax,[r9+0x54]
    /* translated */ (void)0;
    // 0xe82ce50  lock add [r8+rdx*4+0x30],eax
    /* translated */ (void)0;
    // 0xe82ce56  lock add [r8+0x48],esi
    /* translated */ (void)0;
    // 0xe82ce5b  bt qword ptr [rbx+0x1F0],0x3E
    /* translated */ (void)0;
    // 0xe82ce64  jae 0xE82CF53
    /* translated */ (void)0;
    // 0xe82ce6a  movzx eax,word ptr [r9+0x7A]
    /* translated */ (void)0;
    // 0xe82ce6f  movzx r9d,ax
    /* translated */ (void)0;
    // 0xe82ce73  mov r11,[rbx+0xB0]
    /* translated */ (void)0;
    // 0xe82ce7a  mov r8d,[r11+0x7EC8]
    /* translated */ (void)0;
    // 0xe82ce81  mov ecx,[r11+0x7ED4]
    /* translated */ (void)0;
    // 0xe82ce88  mov esi,1
    /* translated */ (void)0;
    // 0xe82ce8d  mov rdi,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82ce94  jmp short 0xE82CED0
    /* translated */ (void)0;
    // 0xe82ce96  nop [rax+rax]
    /* translated */ (void)0;
    // 0xe82cea0  mov edx,[r11+0x7ECC]
    /* translated */ (void)0;
    // 0xe82cea7  sub edx,ecx
    /* translated */ (void)0;
    // 0xe82cea9  mov eax,edx
    /* translated */ (void)0;
    // 0xe82ceab  sar eax,0x1F
    /* translated */ (void)0;
    // 0xe82ceae  and eax,r8d
    /* translated */ (void)0;
    // 0xe82ceb1  add eax,edx
    /* translated */ (void)0;
    // 0xe82ceb3  mov edx,eax
    /* translated */ (void)0;
    // 0xe82ceb5  add edx,0xFFFFFFFE
    /* translated */ (void)0;
    // 0xe82ceb8  mov esi,1
    /* translated */ (void)0;
    // 0xe82cebd  cmovns eax,esi
    /* translated */ (void)0;
    // 0xe82cec0  add eax,ecx
    /* translated */ (void)0;
    // 0xe82cec2  xor edx,edx
    /* translated */ (void)0;
    // 0xe82cec4  div r8d
    /* translated */ (void)0;
    // 0xe82cec7  mov ecx,edx
    /* translated */ (void)0;
    // 0xe82cec9  mov [r11+0x7ED4],edx
    /* translated */ (void)0;
    // 0xe82ced0  mov eax,[r11+0x7ED0]
    /* translated */ (void)0;
    // 0xe82ced7  mov edx,ecx
    /* translated */ (void)0;
    // 0xe82ced9  sub edx,eax
    /* translated */ (void)0;
    // 0xe82cedb  mov r10d,edx
    /* translated */ (void)0;
    // 0xe82cede  sar edx,0x1F
    /* translated */ (void)0;
    // 0xe82cee1  and edx,r8d
    /* translated */ (void)0;
    // 0xe82cee4  add edx,r10d
    /* translated */ (void)0;
    // 0xe82cee7  dec edx
    /* translated */ (void)0;
    // 0xe82cee9  lea r10d,[r8-1]
    /* translated */ (void)0;
    // 0xe82ceed  test edx,edx
    /* translated */ (void)0;
    // 0xe82ceef  cmovns r10d,edx
    /* translated */ (void)0;
    // 0xe82cef3  mov edx,r10d
    /* translated */ (void)0;
    // 0xe82cef6  add edx,0xFFFFFFFE
    /* translated */ (void)0;
    // 0xe82cef9  cmovns r10d,esi
    /* translated */ (void)0;
    // 0xe82cefd  add eax,r10d
    /* translated */ (void)0;
    // 0xe82cf00  xor edx,edx
    /* translated */ (void)0;
    // 0xe82cf02  div r8d
    /* translated */ (void)0;
    // 0xe82cf05  mov [r11+0x7ED0],edx
    /* translated */ (void)0;
    // 0xe82cf0c  test r10d,r10d
    /* translated */ (void)0;
    // 0xe82cf0f  jne short 0xE82CF6D
    /* translated */ (void)0;
    // 0xe82cf11  mov eax,ecx
    /* translated */ (void)0;
    // 0xe82cf13  movzx eax,word ptr [r11+rax*2+0x7CC0]
    /* translated */ (void)0;
    // 0xe82cf1c  cmp rax,0xFFFF
    /* translated */ (void)0;
    // 0xe82cf22  je 0xE82CEA0
    /* translated */ (void)0;
    // 0xe82cf28  mov rcx,[r11+0x7EC0]
    /* translated */ (void)0;
    // 0xe82cf2f  mov ecx,[rcx+rax*8]
    /* translated */ (void)0;
    // 0xe82cf32  mov rdx,[rbx+0x168]
    /* translated */ (void)0;
    // 0xe82cf39  mov [rdx+rax*4+0x14300],ecx
    /* translated */ (void)0;
    // 0xe82cf40  mov r8d,[r11+0x7EC8]
    /* translated */ (void)0;
    // 0xe82cf47  mov ecx,[r11+0x7ED4]
    /* translated */ (void)0;
    // 0xe82cf4e  jmp 0xE82CEA0
    /* translated */ (void)0;
    // 0xe82cf53  mov rax,[rbx+0x160]
    /* translated */ (void)0;
    // 0xe82cf5a  mov [rbx+0x190],ax
    /* translated */ (void)0;
    // 0xe82cf61  mov rsi,[rbx+0xB0]
    /* translated */ (void)0;
    // 0xe82cf68  jmp 0xE82D0CB
    /* translated */ (void)0;
    // 0xe82cf6d  mov eax,[r11+0x7ECC]
    /* translated */ (void)0;
    // 0xe82cf74  mov [r11+rax*2+0x7CC0],r9w
    /* translated */ (void)0;
    // 0xe82cf7d  mov rcx,[rdi+0x30]
    /* translated */ (void)0;
    // 0xe82cf81  mov rdx,[r11+0x7CB8]
    /* translated */ (void)0;
    // 0xe82cf88  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82cf8b  mov rax,[rax+0x1A0]
    /* translated */ (void)0;
    // 0xe82cf92  mov r8d,1
    /* translated */ (void)0;
    // 0xe82cf98  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82cf9e  nop
    /* translated */ (void)0;
    // 0xe82cf9f  mov rax,[rbx+0xB0]
    /* translated */ (void)0;
    // 0xe82cfa6  mov rsi,[rax+0x238]
    /* translated */ (void)0;
    // 0xe82cfad  mov rcx,[rbx+0x250]
    /* translated */ (void)0;
    // 0xe82cfb4  mov rdx,rsi
    /* translated */ (void)0;
    // 0xe82cfb7  mov r8,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82cfbe  xor r9d,r9d
    /* translated */ (void)0;
    // 0xe82cfc1  call 0xE81B720
    /* translated */ (void)0;
    // 0xe82cfc6  nop
    /* translated */ (void)0;
    // 0xe82cfc7  mov rcx,[rbx+0x250]
    /* translated */ (void)0;
    // 0xe82cfce  mov rdx,rsi
    /* translated */ (void)0;
    // 0xe82cfd1  mov r8,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82cfd8  mov r9d,1
    /* translated */ (void)0;
    // 0xe82cfde  call 0xE81B720
    /* translated */ (void)0;
    // 0xe82cfe3  nop
    /* translated */ (void)0;
    // 0xe82cfe4  mov rdx,[rbx+0xB0]
    /* translated */ (void)0;
    // 0xe82cfeb  mov eax,[rdx+0x7ECC]
    /* translated */ (void)0;
    // 0xe82cff1  mov rcx,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82cff8  mov rcx,[rcx+0x30]
    /* translated */ (void)0;
    // 0xe82cffc  movzx esi,word ptr [rdx+rax*2+0x7CC0]
    /* translated */ (void)0;
    // 0xe82d004  mov rdx,[rdx+0x7CB8]
    /* translated */ (void)0;
    // 0xe82d00b  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82d00e  mov rax,[rax+0x1A8]
    /* translated */ (void)0;
    // 0xe82d015  mov r8d,1
    /* translated */ (void)0;
    // 0xe82d01b  mov r9d,esi
    /* translated */ (void)0;
    // 0xe82d01e  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82d024  nop
    /* translated */ (void)0;
    // 0xe82d025  mov rax,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82d02c  mov rcx,[rax+0x30]
    /* translated */ (void)0;
    // 0xe82d030  lea r8d,[rsi*8]
    /* translated */ (void)0;
    // 0xe82d038  mov rax,[rbx+0xB0]
    /* translated */ (void)0;
    // 0xe82d03f  mov r9,[rax+0x7CB0]
    /* translated */ (void)0;
    // 0xe82d046  mov rdx,[rax+0x7CB8]
    /* translated */ (void)0;
    // 0xe82d04d  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82d050  mov rax,[rax+0x1B0]
    /* translated */ (void)0;
    // 0xe82d057  mov r10,[0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82d05e  mov [rsp+0x30],r8
    /* translated */ (void)0;
    // 0xe82d063  mov [rsp+0x28],r9
    /* translated */ (void)0;
    // 0xe82d068  mov dword ptr [rsp+0x20],1
    /* translated */ (void)0;
    // 0xe82d070  mov r8d,1
    /* translated */ (void)0;
    // 0xe82d076  mov r9d,esi
    /* translated */ (void)0;
    // 0xe82d079  call r10
    /* translated */ (void)0;
    // 0xe82d07c  nop
    /* translated */ (void)0;
    // 0xe82d07d  mov rsi,[rbx+0xB0]
    /* translated */ (void)0;
    // 0xe82d084  mov ecx,[rsi+0x7ED0]
    /* translated */ (void)0;
    // 0xe82d08a  mov r8d,[rsi+0x7EC8]
    /* translated */ (void)0;
    // 0xe82d091  mov edx,[rsi+0x7ECC]
    /* translated */ (void)0;
    // 0xe82d097  sub ecx,edx
    /* translated */ (void)0;
    // 0xe82d099  mov eax,ecx
    /* translated */ (void)0;
    // 0xe82d09b  sar eax,0x1F
    /* translated */ (void)0;
    // 0xe82d09e  and eax,r8d
    /* translated */ (void)0;
    // 0xe82d0a1  add eax,ecx
    /* translated */ (void)0;
    // 0xe82d0a3  mov ecx,eax
    /* translated */ (void)0;
    // 0xe82d0a5  add ecx,0xFFFFFFFE
    /* translated */ (void)0;
    // 0xe82d0a8  mov ecx,1
    /* translated */ (void)0;
    // 0xe82d0ad  cmovns eax,ecx
    /* translated */ (void)0;
    // 0xe82d0b0  add eax,edx
    /* translated */ (void)0;
    // 0xe82d0b2  xor edx,edx
    /* translated */ (void)0;
    // 0xe82d0b4  div r8d
    /* translated */ (void)0;
    // 0xe82d0b7  mov [rsi+0x7ECC],edx
    /* translated */ (void)0;
    // 0xe82d0bd  mov rax,[rbx+0x160]
    /* translated */ (void)0;
    // 0xe82d0c4  mov [rbx+0x190],ax
    /* translated */ (void)0;
    // 0xe82d0cb  xor ecx,ecx
    /* translated */ (void)0;
    // 0xe82d0cd  xor edi,edi
    /* translated */ (void)0;
    // 0xe82d0cf  mov rdx,[rbx+0x178]
    /* translated */ (void)0;
    // 0xe82d0d6  jmp 0xE8221F5
    /* translated */ (void)0;
    // 0xe82d0db  xor r9d,r9d
    /* translated */ (void)0;
    // 0xe82d0de  mov r9b,r14b
    /* translated */ (void)0;
    // 0xe82d0e1  mov rcx,[rbx+0x250]
    /* translated */ (void)0;
    // 0xe82d0e8  mov rdx,[rbx+0x110]
    /* translated */ (void)0;
    // 0xe82d0ef  mov r8,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82d0f6  call 0xE81B720
    /* translated */ (void)0;
    // 0xe82d0fb  nop
    /* translated */ (void)0;
    // 0xe82d0fc  jmp 0xE82CE15
    /* translated */ (void)0;
    // 0xe82d101  nop [rax+rax]
    /* translated */ (void)0;
    // 0xe82d110  mov rsi,[rsi+0x238]
    /* translated */ (void)0;
    // 0xe82d117  mov rcx,[rbx+0x250]
    /* translated */ (void)0;
    // 0xe82d11e  mov rdx,rsi
    /* translated */ (void)0;
    // 0xe82d121  mov r8,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82d128  xor r9d,r9d
    /* translated */ (void)0;
    // 0xe82d12b  call 0xE81B720
    /* translated */ (void)0;
    // 0xe82d130  nop
    /* translated */ (void)0;
    // 0xe82d131  mov rcx,[rbx+0x250]
    /* translated */ (void)0;
    // 0xe82d138  mov rdx,rsi
    /* translated */ (void)0;
    // 0xe82d13b  mov r8,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82d142  mov r9d,1
    /* translated */ (void)0;
    // 0xe82d148  call 0xE81B720
    /* translated */ (void)0;
    // 0xe82d14d  nop
    /* translated */ (void)0;
    // 0xe82d14e  mov rax,[rbp+0xE220]
    /* translated */ (void)0;
    // 0xe82d155  cmp byte ptr [rax+0x12018],1
    /* translated */ (void)0;
    // 0xe82d15c  jne short 0xE82D1D0
    /* translated */ (void)0;
    // 0xe82d15e  mov rcx,[rbx+0x1E8]
    /* translated */ (void)0;
    // 0xe82d165  shl ecx,5
    /* translated */ (void)0;
    // 0xe82d168  mov rax,[rbx+0x378]
    /* translated */ (void)0;
    // 0xe82d16f  cmp dword ptr [rax+rcx+0x18],0xFFFFFFFF
    /* translated */ (void)0;
    // 0xe82d174  je short 0xE82D19E
    /* translated */ (void)0;
    // 0xe82d176  mov rsi,rcx
    /* translated */ (void)0;
    // 0xe82d179  call 0xEBDB740
    /* translated */ (void)0;
    // 0xe82d17e  nop
    /* translated */ (void)0;
    // 0xe82d17f  add rsi,[rbx+0x378]
    /* translated */ (void)0;
    // 0xe82d186  add [rsi+0x10],rax
    /* translated */ (void)0;
    // 0xe82d18a  mov rcx,[rsi]
    /* translated */ (void)0;
    // 0xe82d18d  mov r8d,[rsi+0x18]
    /* translated */ (void)0;
    // 0xe82d191  mov rdx,[rbx+0x90]
    /* translated */ (void)0;
    // 0xe82d198  call 0xE81D850
    /* translated */ (void)0;
    // 0xe82d19d  nop
    /* translated */ (void)0;
    // 0xe82d19e  mov rcx,[rbp+0xE220]
    /* translated */ (void)0;
    // 0xe82d1a5  movzx eax,word ptr [rcx+0x12008]
    /* translated */ (void)0;
    // 0xe82d1ac  movzx edx,word ptr [rbx+0x10E]
    /* translated */ (void)0;
    // 0xe82d1b3  nop [rax+rax]
    /* translated */ (void)0;
    // 0xe82d1c0  cmp ax,dx
    /* translated */ (void)0;
    // 0xe82d1c3  jae short 0xE82D1D0
    /* translated */ (void)0;
    // 0xe82d1c5  lock cmpxchg [rcx+0x12008],dx
    /* translated */ (void)0;
    // 0xe82d1ce  jne short 0xE82D1C0
    /* translated */ (void)0;
    // 0xe82d1d0  mov rax,[rbp+0xE228]
    /* translated */ (void)0;
    // 0xe82d1d7  mov rcx,[rax+0x38]
    /* translated */ (void)0;
    // 0xe82d1db  test rcx,rcx
    /* translated */ (void)0;
    // 0xe82d1de  je 0xE82D4BE
    /* translated */ (void)0;
    // 0xe82d1e4  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82d1e7  mov rax,[rax+0x10]
    /* translated */ (void)0;
    // 0xe82d1eb  lea rdx,[rbx+0x3B0]
    /* translated */ (void)0;
    // 0xe82d1f2  call qword ptr [0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82d1f8  nop
    /* translated */ (void)0;
    // 0xe82d1f9  movdqu xmm0,[rbx+0x3B0]
    /* translated */ (void)0;
    // 0xe82d201  movdqu xmm1,[rbx+0x3C0]
    /* translated */ (void)0;
    // 0xe82d209  movdqa [rbx+0x600],xmm1
    /* translated */ (void)0;
    // 0xe82d211  movdqa [rbx+0x5F0],xmm0
    /* translated */ (void)0;
    // 0xe82d219  mov rax,[rbx+0x170]
    /* translated */ (void)0;
    // 0xe82d220  cmp byte ptr [rbx+0x608],1
    /* translated */ (void)0;
    // 0xe82d227  je 0xE821980
    /* translated */ (void)0;
    // 0xe82d22d  mov rdx,[rbx+0x678]
    /* translated */ (void)0;
    // 0xe82d234  mov rcx,[rdx]
    /* translated */ (void)0;
    // 0xe82d237  test rcx,rcx
    /* translated */ (void)0;
    // 0xe82d23a  je short 0xE82D29A
    /* translated */ (void)0;
    // 0xe82d23c  mov rdx,rcx
    /* translated */ (void)0;
    // 0xe82d23f  jmp short 0xE82D258
    /* translated */ (void)0;
    // 0xe82d241  nop [rax+rax]
    /* translated */ (void)0;
    // 0xe82d250  mov rdx,rsi
    /* translated */ (void)0;
    // 0xe82d253  test rsi,rsi
    /* translated */ (void)0;
    // 0xe82d256  je short 0xE82D293
    /* translated */ (void)0;
    // 0xe82d258  mov rsi,[rdx+0x10]
    /* translated */ (void)0;
    // 0xe82d25c  mov rcx,[0x12ADF800]
    /* translated */ (void)0;
    // 0xe82d263  test rcx,rcx
    /* translated */ (void)0;
    // 0xe82d266  je short 0xE82D250
    /* translated */ (void)0;
    // 0xe82d268  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82d26b  mov rax,[rax+8]
    /* translated */ (void)0;
    // 0xe82d26f  mov r10,[0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82d276  mov dword ptr [rsp+0x28],0
    /* translated */ (void)0;
    // 0xe82d27e  mov qword ptr [rsp+0x20],0
    /* translated */ (void)0;
    // 0xe82d287  xor r8d,r8d
    /* translated */ (void)0;
    // 0xe82d28a  xor r9d,r9d
    /* translated */ (void)0;
    // 0xe82d28d  call r10
    /* translated */ (void)0;
    // 0xe82d290  nop
    /* translated */ (void)0;
    // 0xe82d291  jmp short 0xE82D250
    /* translated */ (void)0;
    // 0xe82d293  mov rdx,[rbx+0x678]
    /* translated */ (void)0;
    // 0xe82d29a  mov [rbx+0x680],rdx
    /* translated */ (void)0;
    // 0xe82d2a1  lea rax,[rdx+0x48]
    /* translated */ (void)0;
    // 0xe82d2a5  cmp rax,[rbx+0x688]
    /* translated */ (void)0;
    // 0xe82d2ac  jbe 0xE82D36A
    /* translated */ (void)0;
    // 0xe82d2b2  mov rcx,[0x12ADF800]
    /* translated */ (void)0;
    // 0xe82d2b9  test rcx,rcx
    /* translated */ (void)0;
    // 0xe82d2bc  je 0xE82D36F
    /* translated */ (void)0;
    // 0xe82d2c2  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82d2c5  mov rax,[rax+8]
    /* translated */ (void)0;
    // 0xe82d2c9  mov r10,[0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82d2d0  mov dword ptr [rsp+0x28],0
    /* translated */ (void)0;
    // 0xe82d2d8  mov qword ptr [rsp+0x20],0
    /* translated */ (void)0;
    // 0xe82d2e1  mov r8d,0x48
    /* translated */ (void)0;
    // 0xe82d2e7  xor edx,edx
    /* translated */ (void)0;
    // 0xe82d2e9  xor r9d,r9d
    /* translated */ (void)0;
    // 0xe82d2ec  call r10
    /* translated */ (void)0;
    // 0xe82d2ef  nop
    /* translated */ (void)0;
    // 0xe82d2f0  mov rsi,rax
    /* translated */ (void)0;
    // 0xe82d2f3  mov rdx,[rbx+0x678]
    /* translated */ (void)0;
    // 0xe82d2fa  mov rax,[rbx+0x680]
    /* translated */ (void)0;
    // 0xe82d301  cmp rdx,rax
    /* translated */ (void)0;
    // 0xe82d304  je short 0xE82D371
    /* translated */ (void)0;
    // 0xe82d306  mov r9,rax
    /* translated */ (void)0;
    // 0xe82d309  sub r9,rdx
    /* translated */ (void)0;
    // 0xe82d30c  add r9,0xFFFFFFFFFFFFFFF8
    /* translated */ (void)0;
    // 0xe82d310  cmp r9,0x38
    /* translated */ (void)0;
    // 0xe82d314  jb short 0xE82D378
    /* translated */ (void)0;
    // 0xe82d316  mov rcx,rsi
    /* translated */ (void)0;
    // 0xe82d319  sub rcx,rdx
    /* translated */ (void)0;
    // 0xe82d31c  cmp rcx,0x20
    /* translated */ (void)0;
    // 0xe82d320  jb short 0xE82D378
    /* translated */ (void)0;
    // 0xe82d322  shr r9,3
    /* translated */ (void)0;
    // 0xe82d326  inc r9
    /* translated */ (void)0;
    // 0xe82d329  mov r10,r9
    /* translated */ (void)0;
    // 0xe82d32c  and r10,0xFFFFFFFFFFFFFFFC
    /* translated */ (void)0;
    // 0xe82d330  lea rcx,[rsi+r10*8]
    /* translated */ (void)0;
    // 0xe82d334  lea r8,[rdx+r10*8]
    /* translated */ (void)0;
    // 0xe82d338  xor r11d,r11d
    /* translated */ (void)0;
    // 0xe82d33b  nop [rax+rax]
    /* translated */ (void)0;
    // 0xe82d340  movdqu xmm0,[rdx+r11*8]
    /* translated */ (void)0;
    // 0xe82d346  movdqu xmm1,[rdx+r11*8+0x10]
    /* translated */ (void)0;
    // 0xe82d34d  movdqu [rsi+r11*8],xmm0
    /* translated */ (void)0;
    // 0xe82d353  movdqu [rsi+r11*8+0x10],xmm1
    /* translated */ (void)0;
    // 0xe82d35a  add r11,4
    /* translated */ (void)0;
    // 0xe82d35e  cmp r10,r11
    /* translated */ (void)0;
    // 0xe82d361  jne short 0xE82D340
    /* translated */ (void)0;
    // 0xe82d363  cmp r9,r10
    /* translated */ (void)0;
    // 0xe82d366  jne short 0xE82D380
    /* translated */ (void)0;
    // 0xe82d368  jmp short 0xE82D393
    /* translated */ (void)0;
    // 0xe82d36a  mov rsi,rdx
    /* translated */ (void)0;
    // 0xe82d36d  jmp short 0xE82D3E6
    /* translated */ (void)0;
    // 0xe82d36f  xor esi,esi
    /* translated */ (void)0;
    // 0xe82d371  test rdx,rdx
    /* translated */ (void)0;
    // 0xe82d374  jne short 0xE82D39F
    /* translated */ (void)0;
    // 0xe82d376  jmp short 0xE82D3D4
    /* translated */ (void)0;
    // 0xe82d378  mov rcx,rsi
    /* translated */ (void)0;
    // 0xe82d37b  mov r8,rdx
    /* translated */ (void)0;
    // 0xe82d37e  xchg ax,ax
    /* translated */ (void)0;
    // 0xe82d380  mov rdx,[r8]
    /* translated */ (void)0;
    // 0xe82d383  mov [rcx],rdx
    /* translated */ (void)0;
    // 0xe82d386  add r8,8
    /* translated */ (void)0;
    // 0xe82d38a  add rcx,8
    /* translated */ (void)0;
    // 0xe82d38e  cmp r8,rax
    /* translated */ (void)0;
    // 0xe82d391  jne short 0xE82D380
    /* translated */ (void)0;
    // 0xe82d393  mov rdx,[rbx+0x678]
    /* translated */ (void)0;
    // 0xe82d39a  test rdx,rdx
    /* translated */ (void)0;
    // 0xe82d39d  je short 0xE82D3D4
    /* translated */ (void)0;
    // 0xe82d39f  mov rcx,[0x12ADF800]
    /* translated */ (void)0;
    // 0xe82d3a6  test rcx,rcx
    /* translated */ (void)0;
    // 0xe82d3a9  je short 0xE82D3D4
    /* translated */ (void)0;
    // 0xe82d3ab  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82d3ae  mov rax,[rax+8]
    /* translated */ (void)0;
    // 0xe82d3b2  mov r10,[0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82d3b9  mov dword ptr [rsp+0x28],0
    /* translated */ (void)0;
    // 0xe82d3c1  mov qword ptr [rsp+0x20],0
    /* translated */ (void)0;
    // 0xe82d3ca  xor r8d,r8d
    /* translated */ (void)0;
    // 0xe82d3cd  xor r9d,r9d
    /* translated */ (void)0;
    // 0xe82d3d0  call r10
    /* translated */ (void)0;
    // 0xe82d3d3  nop
    /* translated */ (void)0;
    // 0xe82d3d4  mov [rbx+0x678],rsi
    /* translated */ (void)0;
    // 0xe82d3db  lea rax,[rsi+0x48]
    /* translated */ (void)0;
    // 0xe82d3df  mov [rbx+0x688],rax
    /* translated */ (void)0;
    // 0xe82d3e6  pxor xmm0,xmm0
    /* translated */ (void)0;
    // 0xe82d3ea  movdqu [rsi+0x30],xmm0
    /* translated */ (void)0;
    // 0xe82d3ef  movdqu [rsi+0x20],xmm0
    /* translated */ (void)0;
    // 0xe82d3f4  movdqu [rsi+0x10],xmm0
    /* translated */ (void)0;
    // 0xe82d3f9  movdqu [rsi],xmm0
    /* translated */ (void)0;
    // 0xe82d3fd  mov qword ptr [rsi+0x40],0
    /* translated */ (void)0;
    // 0xe82d405  mov rdx,[rbx+0x678]
    /* translated */ (void)0;
    // 0xe82d40c  lea rax,[rdx+0x48]
    /* translated */ (void)0;
    // 0xe82d410  mov [rbx+0x680],rax
    /* translated */ (void)0;
    // 0xe82d417  mov qword ptr [rbx+0x670],0
    /* translated */ (void)0;
    // 0xe82d422  test rdx,rdx
    /* translated */ (void)0;
    // 0xe82d425  je short 0xE82D45C
    /* translated */ (void)0;
    // 0xe82d427  mov rcx,[0x12ADF800]
    /* translated */ (void)0;
    // 0xe82d42e  test rcx,rcx
    /* translated */ (void)0;
    // 0xe82d431  je short 0xE82D45C
    /* translated */ (void)0;
    // 0xe82d433  mov rax,[rcx]
    /* translated */ (void)0;
    // 0xe82d436  mov rax,[rax+8]
    /* translated */ (void)0;
    // 0xe82d43a  mov r10,[0xF99FFA0]
    /* translated */ (void)0;
    // 0xe82d441  mov dword ptr [rsp+0x28],0
    /* translated */ (void)0;
    // 0xe82d449  mov qword ptr [rsp+0x20],0
    /* translated */ (void)0;
    // 0xe82d452  xor r8d,r8d
    /* translated */ (void)0;
    // 0xe82d455  xor r9d,r9d
    /* translated */ (void)0;
    // 0xe82d458  call r10
    /* translated */ (void)0;
    // 0xe82d45b  nop
    /* translated */ (void)0;
    // 0xe82d45c  movaps xmm6,[rbp+0xE110]
    /* translated */ (void)0;
    // 0xe82d463  movaps xmm7,[rbp+0xE120]
    /* translated */ (void)0;
    // 0xe82d46a  movaps xmm8,[rbp+0xE130]
    /* translated */ (void)0;
    // 0xe82d472  movaps xmm9,[rbp+0xE140]
    /* translated */ (void)0;
    // 0xe82d47a  movaps xmm10,[rbp+0xE150]
    /* translated */ (void)0;
    // 0xe82d482  movaps xmm11,[rbp+0xE160]
    /* translated */ (void)0;
    // 0xe82d48a  movaps xmm12,[rbp+0xE170]
    /* translated */ (void)0;
    // 0xe82d492  movaps xmm13,[rbp+0xE180]
    /* translated */ (void)0;
    // 0xe82d49a  movaps xmm14,[rbp+0xE190]
    /* translated */ (void)0;
    // 0xe82d4a2  movaps xmm15,[rbp+0xE1A0]
    /* translated */ (void)0;
    // 0xe82d4aa  lea rsp,[rbp+0xE1B8]
    /* translated */ (void)0;
    // 0xe82d4b1  pop rbx
    /* translated */ (void)0;
    // 0xe82d4b2  pop rdi
    /* translated */ (void)0;
    // 0xe82d4b3  pop rsi
    /* translated */ (void)0;
    // 0xe82d4b4  pop r12
    /* translated */ (void)0;
    // 0xe82d4b6  pop r13
    /* translated */ (void)0;
    // 0xe82d4b8  pop r14
    /* translated */ (void)0;
    // 0xe82d4ba  pop r15
    /* translated */ (void)0;
    // 0xe82d4bc  pop rbp
    /* translated */ (void)0;
    // 0xe82d4bd  ret
    /* translated */ (void)0;
    // 0xe82d4be  call 0xEEC59E0
    /* translated */ (void)0;
    // 0xe82d4c3  nop
    /* translated */ (void)0;

    s.rbx = rbx; s.rbp = rbp; s.rcx = rcx; s.rsi = rsi; s.rdi = rdi; s.rax = rax; s.rdx = rdx; s.r10 = r10;
}

} } // namespace
