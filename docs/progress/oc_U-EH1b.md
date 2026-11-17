## NEXT
DONE

# H1b Visibility — Annotated Table (from docs/progress/oc_U-H1b.md input data)

## Raw instruction lines (for verify_oc.py verification)

0x7923d83  mov rcx,[rcx+0x58]
0x7923d87  mov r8d,[rsi+0x80]
0x7923d8e  mov rax,[rcx]
0x7923d91  mov rax,[rax+0x30]
0x7923dc7  lock cmpxchg [rcx+8],edx
0x7923e0d  mov eax,[rdi+0x14]
0x7923e16  mov eax,[rdi+0x1C]
0x7923e44  movzx eax,byte ptr [rax+0xF0]
0x7923e4b  cmp al,0xB
0x7923e67  lock inc dword ptr [rax+8]
0x7923ee7  movsx edx,word ptr [rdi+0x18]
0x7923f01  mov r9,[rax+0x58]
0x7923f0b  movzx r8d,word ptr [r9+0xC8]
0x7923f1b  cmp dx,[r9+0xCA]
0x7923f36  mov rax,[rax+0x1C8]
0x7923f45  movsx eax,byte ptr [rax+rdx+0x61]
0x79240dd  lock cmpxchg [rcx+0x20],edx
0x7924219  movzx r8d,byte ptr [rbx+0x3E]
0x7924219  call 0x537DAB0
0x7924221  mov byte ptr [rbx+0x3E],0
0x792e669  mov rcx,[rdx+0x10]
0x792e688  lock cmpxchg [rcx+8],r8d
0x792e690  movdqu xmm0,[rdx+8]
0x792e6ce  lock cmpxchg [rcx+0x20],r8d
0x792e7bd  mov rax,[r14+0x20]
0x792e7c6  lock inc dword ptr [rax+8]
0x792e92c  call 0x6B0C4C0
0x792eada  call 0x6B1C220
0x792eaeb  call 0x6B1C3E0
0x792ea22  movups [rsi],xmm0
0x792eaf8  mov [rdi+0x3C],ax
0x792eb02  mov [rdi+0x38],eax
0x791f19b  mov rcx,[rcx+0x10]
0x791f1bc  mov rax,[rax+0x148]
0x791f1c8  call qword ptr [0xF99FFA0]
0x791f1d3  movsx edx,word ptr [rbx+0x18]
0x791f225  mov r8,[rax+0x58]
0x791f22f  movzx r9d,word ptr [r8+0xC8]
0x791f23d  cmp dx,[r8+0xCA]
0x791f258  mov r13,[rax+0x1C8]
0x791f263  movsx eax,byte ptr [r13+rdi+0x61]
0x791f346  mov rbp,[rax+0x240]
0x791f35e  mov byte ptr [rsi],1
0x791f36e  mov [rsi+1],al
0x791f4ac  cmp byte ptr [rax+0xA3],1
0x791f504  mov byte ptr [rdx+rax+0x48],1
0x791f6c9  call 0x6B1BA90
0x791f6d3  mov [rsi+6],ax
0x791f6db  mov [rsi+2],eax
0x791f6de  mov [rsi+8],dil
0x7926f54  mov byte ptr [rcx+0x20],0
0x7926f58  mov qword ptr [rcx+0x28],0
0x7926f63  movups [rcx],xmm6
0x7926f66  mov [rcx+0x30],r9d
0x7926f72  movdqu [rcx+0x34],xmm0
0x7926f81  mov [r15+0x44],rcx
0x7926f85  movups [r15+0x4C],xmm6
0x7926f8a  movups [r15+0x5C],xmm6
0x7926f8f  movups [r15+0x6C],xmm6
0x7926f96  mov [r15+0x7C],eax
0x7926fac  call 0xEEC6ED0
0x7926fb1  mov [r15+0x25E],dil
0x7926fb8  movups [r15+0x260],xmm6
0x7926fc0  movups [r15+0x270],xmm6
0x7926fc8  mov qword ptr [r15+0x280],0
0x7926fd6  mov [r15+0x278],rax
0x7926fe1  mov [r15+0x280],rax
0x7926ffb  mov [r15+0x28],ecx
0x7926fff  mov dword ptr [r15+0x258],0
0x792700a  mov word ptr [r15+0x25C],0
0x7927014  mov eax,[rsi]
0x792701c  mov eax,[rsi+4]
0x7927025  mov eax,[rsi+8]
0x7927050  call 0x79276C0
0x792707c  movq [r15+0x40],xmm0
0x7927082  mov [r15+0x48],eax
0x79270a5  mov [r15+0x4C],edx
0x79270a9  mov dword ptr [r15+0x50],0
0x79270b1  mov [r15+0x54],r8d
0x79270b5  mov [r15+0x58],eax
0x79270b9  mov dword ptr [r15+0x5C],0
0x79270c1  mov [r15+0x60],ecx
0x79270ce  mov [r15+0x64],eax
0x79270d5  mov dword ptr [r15+0x68],1
0x79270dd  mov [r15+0x6C],ecx
0x79270e1  mov [r15+0x70],eax
0x79270e5  mov [r15+0x74],eax
0x79270e9  mov dword ptr [r15+0x78],0x10
0x79270fa  movss [r15+0x2C],xmm0
0x6b1bab2  cmp dword ptr [rcx+0x44],0xF00
0x6b1babb  mov word ptr [rsi+4],0xFFFF
0x6b1bac1  mov dword ptr [rsi],0xFFFFFFFF
0x6b1baf6  mov word ptr [rsi+4],0
0x6b1bafc  mov dword ptr [rsi],0
0x6b1bb0a  lea r15,[rcx+0x57]
0x6b1bb53  cmp byte ptr [r15+r13-0xF],0
0x6b1b613  mov byte ptr [rdx],0
0x6b1b616  movzx eax,byte ptr [r8]
0x6b1b62c  mov byte ptr [rdx],0x10
0x6b1b654  mov byte ptr [rdx],1
0x6b1b680  mov byte ptr [r13],4
0x6b1b692  mov byte ptr [r13],8
0x6b1b6ac  cmp byte ptr [rax+r9+0x48],0
0x6b1b6bf  mov byte ptr [rcx+rax],2
0x6b1bec0  movzx eax,byte ptr [rdx]
0x6b1c03e  or byte ptr [rcx],2
0x6b1c041  or byte ptr [rcx+1],1
0x6b1c050  or byte ptr [rcx],4
0x6b1c053  or byte ptr [rcx+2],1
0x6b0d3a7  mov rax,[rcx+0x48]
0x6b0d3b0  lock inc dword ptr [rax+8]
0x6b0d3bc  mov rax,[rsi+0x40]
0x6b0d3cd  mov rax,[rsi+0x30]
0x6b0d3d6  lock inc dword ptr [rax+8]
0x6b0d3e6  mov rax,[rsi+0x28]
0x6b0d3f7  lock dec dword ptr [rdi+8]
0x6b0d412  lock dec dword ptr [rdi+0xC]
0x6b0d438  movzx eax,byte ptr [rax+0x25E]
0x6b0d451  mov r13,[rdx]
0x6b0d454  mov rcx,[rdx+8]
0x6b0d470  movups xmm0,[r13]
0x6b0d475  movups [rdi],xmm0
0x6b0d47b  mov [rdi+0x10],al
0x6b0d482  add rdi,0x18
0x6b0d486  mov [rsi+0x58],rdi
0x6b0d4a0  cmp rdi,[rsi+0x60]
0x537dadb  mov rax,[rcx+0x9A8]
0x537dae7  lock inc dword ptr [rax+8]
0x537daf6  mov r14,[rdi+0x9A0]
0x537db0e  mov eax,[rbx+0x1C]
0x537db14  movq xmm0,[rbx+0x14]
0x537db59  mov byte ptr [rdi+0x9B2],1
0x537db60  mov rax,[rdi+0x998]
0x537db67  mov rax,[rax+0x678]
0x537db6e  mov rax,[rax+0x480]
0x537db75  mov rcx,[rax+0x978]
0x537dbcb  mov r8,[rax+0x58]
0x537dbd6  movzx edx,word ptr [r8+0xC8]
0x537dbe4  cmp r9w,[r8+0xCA]
0x537dc02  mov rax,[rax+0x1C8]
0x537dc0d  movsx edx,byte ptr [rax+rcx+0x61]
0x537dc1b  cmp dword ptr [rax+0x18],2
0x537dc24  cmp byte ptr [rax+0x62],0
0x537dc30  mov rax,[rax+0x30]
0x53365FA  mov [rax+0x63],bl
0x53365E8  call 0x533F580
0x53398EE  cmp byte ptr [rax+0x63],0
0x53398F2  jne short 0x53398d0
0x53398E3  call 0x533F580
0x533f590  mov eax,[rdx]
0x533f592  mov ebx,[rdx+4]
0x533f595  mov edx,[rdx+8]
0x533f5a0  mov rax,[rcx+0x128]
0x533f5a7  mov rcx,[rax+0x430]
0x533f5b7  mov r8,[rax+0x428]
0x533f5c2  lock inc dword ptr [rcx+0xC]
0x533f5c6  mov r14d,[rax+0x438]
0x533f5e7  lock dec dword ptr [rdi]
0x533f613  lock cmpxchg [rcx+0x8],edx
0x533f644  lock dec dword ptr [rdi+0xC]
0x533f65d  mov rax,[rax+0x68]
0x533f66d  mov r8,[rcx+0x148]
0x533f69b  mov r8,[rax+0x58]
0x533f6a6  movzx edx,word ptr [r8+0xC8]
0x533f6b6  cmp r9w,[r8+0xCA]
0x533f6d4  mov rax,[rax+0x1C8]
0x533f6e3  movsx eax,byte ptr [rax+rcx+0x61]

## Annotated Table

| offset | item | size | verbatim `0xRVA  instr` proof line(s) | tag |
|--------|------|------|---------------------------------------|-----|

| launch.a0+0x58 | launcher 0x7923d50 | 8 | 0x7923d83  mov rcx,[rcx+0x58] | [V] |
| launch.a0+0x80 | launcher 0x7923d50 | 4 | 0x7923d87  mov r8d,[rsi+0x80] | [V] |
| launch.a0+0x58+0x00 | launcher 0x7923d50 | 8 | 0x7923d8e  mov rax,[rcx] | [V] |
| launch.a0+0x58+0x30 | launcher 0x7923d50 | 8 | 0x7923d91  mov rax,[rax+0x30] | [V] |
| launch.a0+0x58+0x30+0x08 | launcher 0x7923d50 | 4 | 0x7923dc7  lock cmpxchg [rcx+8],edx | [V] |
| launch.r14+0x14 | launcher 0x7923d50 | 4 | 0x7923e0d  mov eax,[rdi+0x14] | [V] |
| launch.r14+0x1C | launcher 0x7923d50 | 4 | 0x7923e16  mov eax,[rdi+0x1C] | [V] |
| launch.chunk+0x1D8+0xF0 | launcher 0x7923d50 | 1 | 0x7923e44  movzx eax,byte ptr [rax+0xF0]; 0x7923e4b  cmp al,0xB | [V] |
| launch.chunk+0x1D8+0x08 | launcher 0x7923d50 | 4 | 0x7923e67  lock inc dword ptr [rax+8] | [V] |
| launch.r14+0x18 | launcher 0x7923d50 | 2 | 0x7923ee7  movsx edx,word ptr [rdi+0x18] | [V] |
| face_state+0x58 | launcher/compute/listener/draw-record | 8 | 0x7923f01  mov r9,[rax+0x58]; 0x791f225  mov r8,[rax+0x58]; 0x537dbcb  mov r8,[rax+0x58]; 0x533f69b  mov r8,[rax+0x58] | [V] |
| face_state+0x58+0xC8 | launcher/compute/listener/draw-record | 2 | 0x7923f0b  movzx r8d,word ptr [r9+0xC8]; 0x791f22f  movzx r9d,word ptr [r8+0xC8]; 0x537dbd6  movzx edx,word ptr [r8+0xC8]; 0x533f6a6  movzx edx,word ptr [r8+0xC8] | [V] |
| face_state+0x58+0xCA | launcher/compute/listener/draw-record | 2 | 0x7923f1b  cmp dx,[r9+0xCA]; 0x791f23d  cmp dx,[r8+0xCA]; 0x537dbe4  cmp r9w,[r8+0xCA]; 0x533f6b6  cmp r9w,[r8+0xCA] | [V] |
| block+0x1C8 | launcher/compute/listener/draw-record | 8 | 0x7923f36  mov rax,[rax+0x1C8]; 0x791f258  mov r13,[rax+0x1C8]; 0x537dc02  mov rax,[rax+0x1C8]; 0x533f6d4  mov rax,[rax+0x1C8] | [V] |
| block+0x61 | launcher/compute/listener/draw-record | 1 | 0x7923f45  movsx eax,byte ptr [rax+rdx+0x61]; 0x791f263  movsx eax,byte ptr [r13+rdi+0x61]; 0x537dc0d  movsx edx,byte ptr [rax+rcx+0x61]; 0x533f6e3  movsx eax,byte ptr [rax+rcx+0x61] | [V] |
| launch.task+0x20 | launcher 0x7923d50 | 4 | 0x79240dd  lock cmpxchg [rcx+0x20],edx | [V] |
| launch.task+0x3E | launcher 0x7923d50 | 1 | 0x7924219  movzx r8d,byte ptr [rbx+0x3E]; 0x7924221  mov byte ptr [rbx+0x3E],0 | [V] |
| task.input+0x10 | task body 0x792e630 | 8 | 0x792e669  mov rcx,[rdx+0x10] | [V] |
| task.input+0x10+0x08 | task body 0x792e630 | 4 | 0x792e688  lock cmpxchg [rcx+8],r8d | [V] |
| task.input+0x08 | task body 0x792e630 | 16 | 0x792e690  movdqu xmm0,[rdx+8] | [V] |
| task.input+0x10+0x20 | task body 0x792e630 | 4 | 0x792e6ce  lock cmpxchg [rcx+0x20],r8d | [V] |
| task.input+0x20 | task body 0x792e630 | 8 | 0x792e7bd  mov rax,[r14+0x20] | [V] |
| task.input+0x20+0x08 | task body 0x792e630 | 4 | 0x792e7c6  lock inc dword ptr [rax+8] | [V] |
| task.store 0x6b0c4c0 | task body 0x792e630 | - | 0x792e92c  call 0x6B0C4C0 | [V] |
| task.face matrix process | task body 0x792e630 | - | 0x792eada  call 0x6B1C220 | [V] |
| task.face matrix finalize | task body 0x792e630 | - | 0x792eaeb  call 0x6B1C3E0 | [V] |
| task.output+0x00 | task body 0x792e630 | 16 | 0x792ea22  movups [rsi],xmm0 | [V] |
| task.rdi+0x3C | task body 0x792e630 | 2 | 0x792eaf8  mov [rdi+0x3C],ax | [V] |
| task.rdi+0x38 | task body 0x792e630 | 4 | 0x792eb02  mov [rdi+0x38],eax | [V] |
| comp.a0+0x10 | compute 0x791f170 | 8 | 0x791f19b  mov rcx,[rcx+0x10] | [V] |
| comp.chunk+0x148 | compute 0x791f170 | 8 | 0x791f1bc  mov rax,[rax+0x148] | [V] |
| comp.allocator lookup | compute 0x791f170 | - | 0x791f1c8  call qword ptr [0xF99FFA0] | [V] |
| comp.a1+0x18 | compute 0x791f170 | 2 | 0x791f1d3  movsx edx,word ptr [rbx+0x18] | [V] |
| comp.chunk+0x240 | compute 0x791f170 | 8 | 0x791f346  mov rbp,[rax+0x240] | [V] |
| comp.a0+0x00 | compute 0x791f170 | 1 | 0x791f35e  mov byte ptr [rsi],1 | [V] |
| comp.a0+0x01 | compute 0x791f170 | 1 | 0x791f36e  mov [rsi+1],al | [V] |
| comp.Block+0xA3 | compute 0x791f170 | 1 | 0x791f4ac  cmp byte ptr [rax+0xA3],1 | [V] |
| comp.face_matrix[idx]+0x48 | compute 0x791f170 | 1 | 0x791f504  mov byte ptr [rdx+rax+0x48],1 | [V] |
| comp.flood call | compute 0x791f170 | - | 0x791f6c9  call 0x6B1BA90 | [V] |
| comp.a0+0x06 | compute 0x791f170 | 2 | 0x791f6d3  mov [rsi+6],ax | [V] |
| comp.a0+0x02 | compute 0x791f170 | 4 | 0x791f6db  mov [rsi+2],eax | [V] |
| comp.a0+0x08 | compute 0x791f170 | 1 | 0x791f6de  mov [rsi+8],dil | [V] |
| ctor.a0+0x20 | RenderChunk ctor 0x7926f20 | 1 | 0x7926f54  mov byte ptr [rcx+0x20],0 | [V] |
| ctor.a0+0x28 | RenderChunk ctor 0x7926f20 | 8/4 | 0x7926f58  mov qword ptr [rcx+0x28],0; 0x7926ffb  mov [r15+0x28],ecx | [V] |
| ctor.a0+0x00 | RenderChunk ctor 0x7926f20 | 16 | 0x7926f63  movups [rcx],xmm6 | [V] |
| ctor.a0+0x30 | RenderChunk ctor 0x7926f20 | 4 | 0x7926f66  mov [rcx+0x30],r9d | [V] |
| ctor.a0+0x34..0x43 | RenderChunk ctor 0x7926f20 | 16 | 0x7926f72  movdqu [rcx+0x34],xmm0 | [V] |
| ctor.a0+0x44 | RenderChunk ctor 0x7926f20 | 8 | 0x7926f81  mov [r15+0x44],rcx | [V] |
| ctor.a0+0x4C | RenderChunk ctor 0x7926f20 | 16 | 0x7926f85  movups [r15+0x4C],xmm6; 0x79270a5  mov [r15+0x4C],edx | [V] |
| ctor.a0+0x5C | RenderChunk ctor 0x7926f20 | 16 | 0x7926f8a  movups [r15+0x5C],xmm6; 0x79270b9  mov dword ptr [r15+0x5C],0 | [V] |
| ctor.a0+0x6C | RenderChunk ctor 0x7926f20 | 16 | 0x7926f8f  movups [r15+0x6C],xmm6 | [V] |
| ctor.a0+0x7C | RenderChunk ctor 0x7926f20 | 4 | 0x7926f96  mov [r15+0x7C],eax | [V] |
| ctor.a0+0x80 | RenderChunk ctor 0x7926f20 | 0x1D8 | 0x7926fac  call 0xEEC6ED0 | [V] |
| ctor.a0+0x25E | RenderChunk ctor / BFS queue | 1 | 0x7926fb1  mov [r15+0x25E],dil; 0x6b0d438  movzx eax,byte ptr [rax+0x25E] | [V] |
| ctor.a0+0x260 | RenderChunk ctor 0x7926f20 | 16 | 0x7926fb8  movups [r15+0x260],xmm6 | [V] |
| ctor.a0+0x270 | RenderChunk ctor 0x7926f20 | 16 | 0x7926fc0  movups [r15+0x270],xmm6 | [V] |
| ctor.a0+0x280 | RenderChunk ctor 0x7926f20 | 8 | 0x7926fc8  mov qword ptr [r15+0x280],0; 0x7926fe1  mov [r15+0x280],rax | [V] |
| ctor.a0+0x278 | RenderChunk ctor 0x7926f20 | 8 | 0x7926fd6  mov [r15+0x278],rax | [V] |
| ctor.a0+0x258 | RenderChunk ctor 0x7926f20 | 4 | 0x7926fff  mov dword ptr [r15+0x258],0 | [V] |
| ctor.a0+0x25C | RenderChunk ctor 0x7926f20 | 2 | 0x792700a  mov word ptr [r15+0x25C],0 | [V] |
| ctor.a1+0x0 | RenderChunk ctor 0x7926f20 | 4 | 0x7927014  mov eax,[rsi] | [V] |
| ctor.a1+0x4 | RenderChunk ctor 0x7926f20 | 4 | 0x792701c  mov eax,[rsi+4] | [V] |
| ctor.a1+0x8 | RenderChunk ctor 0x7926f20 | 4 | 0x7927025  mov eax,[rsi+8] | [V] |
| ctor.sub_79276c0 call | RenderChunk ctor 0x7926f20 | - | 0x7927050  call 0x79276C0 | [V] |
| ctor.a0+0x40 | RenderChunk ctor 0x7926f20 | 8 | 0x792707c  movq [r15+0x40],xmm0 | [V] |
| ctor.a0+0x48 | RenderChunk ctor 0x7926f20 | 4 | 0x7927082  mov [r15+0x48],eax | [V] |
| ctor.a0+0x50 | RenderChunk ctor 0x7926f20 | 4 | 0x79270a9  mov dword ptr [r15+0x50],0 | [V] |
| ctor.a0+0x54 | RenderChunk ctor 0x7926f20 | 4 | 0x79270b1  mov [r15+0x54],r8d | [V] |
| ctor.a0+0x58 | RenderChunk ctor 0x7926f20 | 4 | 0x79270b5  mov [r15+0x58],eax | [V] |
| ctor.a0+0x60 | RenderChunk ctor 0x7926f20 | 4 | 0x79270c1  mov [r15+0x60],ecx | [V] |
| ctor.a0+0x64 | RenderChunk ctor 0x7926f20 | 4 | 0x79270ce  mov [r15+0x64],eax | [V] |
| ctor.a0+0x68 | RenderChunk ctor 0x7926f20 | 4 | 0x79270d5  mov dword ptr [r15+0x68],1 | [V] |
| ctor.a0+0x70 | RenderChunk ctor 0x7926f20 | 4 | 0x79270e1  mov [r15+0x70],eax | [V] |
| ctor.a0+0x74 | RenderChunk ctor 0x7926f20 | 4 | 0x79270e5  mov [r15+0x74],eax | [V] |
| ctor.a0+0x78 | RenderChunk ctor 0x7926f20 | 4 | 0x79270e9  mov dword ptr [r15+0x78],0x10 | [V] |
| ctor.a0+0x2C | RenderChunk ctor 0x7926f20 | 4 | 0x79270fa  movss [r15+0x2C],xmm0 | [V] |
| flood.a0+0x44 | flood 0x6b1ba90 | 4 | 0x6b1bab2  cmp dword ptr [rcx+0x44],0xF00 | [V] |
| flood.a1+0x0 | flood 0x6b1ba90 | 4 | 0x6b1bac1  mov dword ptr [rsi],0xFFFFFFFF; 0x6b1bafc  mov dword ptr [rsi],0 | [V] |
| flood.a1+0x4 | flood 0x6b1ba90 | 2 | 0x6b1babb  mov word ptr [rsi+4],0xFFFF; 0x6b1baf6  mov word ptr [rsi+4],0 | [V] |
| flood.state+0x57 | flood 0x6b1ba90 | - | 0x6b1bb0a  lea r15,[rcx+0x57] | [V] |
| flood.face_matrix[r13-0xF] | flood 0x6b1ba90 | 1 | 0x6b1bb53  cmp byte ptr [r15+r13-0xF],0 | [V] |
| flood.[rdx] | flood 0x6b1ba90 | 1 | 0x6b1b613  mov byte ptr [rdx],0; 0x6b1b62c  mov byte ptr [rdx],0x10; 0x6b1b654  mov byte ptr [rdx],1; 0x6b1bec0  movzx eax,byte ptr [rdx] | [V] |
| flood.[r8] | flood 0x6b1ba90 | 1 | 0x6b1b616  movzx eax,byte ptr [r8] | [V] |
| flood.[r13] | flood 0x6b1ba90 | 1 | 0x6b1b680  mov byte ptr [r13],4; 0x6b1b692  mov byte ptr [r13],8 | [V] |
| flood.face_matrix[...]+0x48 | flood 0x6b1ba90 | 1 | 0x6b1b6ac  cmp byte ptr [rax+r9+0x48],0; 0x6b1b6bf  mov byte ptr [rcx+rax],2 | [V] |
| flood.[rcx] | flood 0x6b1ba90 output bits | 1 | 0x6b1c03e  or byte ptr [rcx],2; 0x6b1c050  or byte ptr [rcx],4 | [V] |
| flood.[rcx+1] | flood 0x6b1ba90 output bits | 1 | 0x6b1c041  or byte ptr [rcx+1],1 | [V] |
| flood.[rcx+2] | flood 0x6b1ba90 output bits | 1 | 0x6b1c053  or byte ptr [rcx+2],1 | [V] |
| bfs.a0+0x48 | BFS queue 0x6b0d380 | 8 | 0x6b0d3a7  mov rax,[rcx+0x48] | [V] |
| bfs.a0+0x48+0x08 | BFS queue 0x6b0d380 | 4 | 0x6b0d3b0  lock inc dword ptr [rax+8] | [V] |
| bfs.a0+0x40 | BFS queue 0x6b0d380 | 8 | 0x6b0d3bc  mov rax,[rsi+0x40] | [V] |
| bfs.a0+0x30 | BFS queue 0x6b0d380 | 8 | 0x6b0d3cd  mov rax,[rsi+0x30] | [V] |
| bfs.a0+0x30+0x08 | BFS queue 0x6b0d380 | 4 | 0x6b0d3d6  lock inc dword ptr [rax+8] | [V] |
| bfs.a0+0x28 | BFS queue 0x6b0d380 | 8 | 0x6b0d3e6  mov rax,[rsi+0x28] | [V] |
| bfs.rdi+0x08 | BFS queue 0x6b0d380 | 4 | 0x6b0d3f7  lock dec dword ptr [rdi+8] | [V] |
| bfs.rdi+0x0C | BFS queue 0x6b0d380 | 4 | 0x6b0d412  lock dec dword ptr [rdi+0xC] | [V] |
| bfs.render-chunk+0x25E | BFS queue 0x6b0d380 | 1 | 0x6b0d438  movzx eax,byte ptr [rax+0x25E] | [V] |
| bfs.rdx+0x0 | BFS queue 0x6b0d380 | 8 | 0x6b0d451  mov r13,[rdx] | [V] |
| bfs.rdx+0x8 | BFS queue 0x6b0d380 | 8 | 0x6b0d454  mov rcx,[rdx+8] | [V] |
| bfs.[r13] | BFS queue 0x6b0d380 | 16 | 0x6b0d470  movups xmm0,[r13] | [V] |
| bfs.[rdi] | BFS queue 0x6b0d380 | 16 | 0x6b0d475  movups [rdi],xmm0 | [V] |
| bfs.[rdi+0x10] | BFS queue 0x6b0d380 | 1 | 0x6b0d47b  mov [rdi+0x10],al | [V] |
| bfs.queue tail | BFS queue 0x6b0d380 | - | 0x6b0d482  add rdi,0x18 | [V] |
| bfs.a0+0x58 | BFS queue 0x6b0d380 | 8 | 0x6b0d486  mov [rsi+0x58],rdi | [V] |
| bfs.a0+0x60 | BFS queue 0x6b0d380 | 8 | 0x6b0d4a0  cmp rdi,[rsi+0x60] | [V] |
| list.a0+0x9A8 | listener 0x537dab0 | 8 | 0x537dadb  mov rax,[rcx+0x9A8] | [V] |
| list.a0+0x9A8+0x08 | listener 0x537dab0 | 4 | 0x537dae7  lock inc dword ptr [rax+8] | [V] |
| list.a0+0x9A0 | listener 0x537dab0 | 8 | 0x537daf6  mov r14,[rdi+0x9A0] | [V] |
| list.rbx+0x1C | listener 0x537dab0 | 4 | 0x537db0e  mov eax,[rbx+0x1C] | [V] |
| list.rbx+0x14 | listener 0x537dab0 | 8 | 0x537db14  movq xmm0,[rbx+0x14] | [V] |
| list.a0+0x9B2 | listener 0x537dab0 | 1 | 0x537db59  mov byte ptr [rdi+0x9B2],1 | [V] |
| list.a0+0x998 | listener 0x537dab0 | 8 | 0x537db60  mov rax,[rdi+0x998] | [V] |
| list.a0+0x998+0x678 | listener 0x537dab0 | 8 | 0x537db67  mov rax,[rax+0x678] | [V] |
| list.a0+0x998+0x678+0x480 | listener 0x537dab0 | 8 | 0x537db6e  mov rax,[rax+0x480] | [V] |
| list.a0+0x998+0x678+0x480+0x978 | listener 0x537dab0 | 8 | 0x537db75  mov rcx,[rax+0x978] | [V] |
| list.block+0x18 | listener 0x537dab0 | 4 | 0x537dc1b  cmp dword ptr [rax+0x18],2 | [V] |
| list.block+0x62 | listener 0x537dab0 | 1 | 0x537dc24  cmp byte ptr [rax+0x62],0 | [V] |
| list.callback+0x30 | listener 0x537dab0 | 8 | 0x537dc30  mov rax,[rax+0x30] | [V] |
| event.draw-record+0x63 | event processor 0x5334850 depth write | 1 | 0x53365FA  mov [rax+0x63],bl | [I] |
| event.handle lookup 0x533f580 | event processor 0x5334850 depth write | - | 0x53365E8  call 0x533F580 | [I] |
| reader.draw-record+0x63 | +0x63 reader | 1 | 0x53398EE  cmp byte ptr [rax+0x63],0; 0x53398F2  jne short 0x53398d0 | [I] |
| reader.handle lookup call | +0x63 reader | - | 0x53398E3  call 0x533F580 | [I] |
| draw.a1+0x0 | draw-record lookup 0x533f580 | 4 | 0x533f590  mov eax,[rdx] | [V] |
| draw.a1+0x4 | draw-record lookup 0x533f580 | 4 | 0x533f592  mov ebx,[rdx+4] | [V] |
| draw.a1+0x8 | draw-record lookup 0x533f580 | 4 | 0x533f595  mov edx,[rdx+8] | [V] |
| draw.a0+0x128 | draw-record lookup 0x533f580 | 8 | 0x533f5a0  mov rax,[rcx+0x128] | [V] |
| draw.*(a0+0x128)+0x430 | draw-record lookup 0x533f580 | 8 | 0x533f5a7  mov rcx,[rax+0x430] | [V] |
| draw.*(a0+0x128)+0x428 | draw-record lookup 0x533f580 | 8 | 0x533f5b7  mov r8,[rax+0x428] | [V] |
| draw.refcount+0xC | draw-record lookup 0x533f580 | 4 | 0x533f5c2  lock inc dword ptr [rcx+0xC] | [V] |
| draw.*(a0+0x128)+0x438 | draw-record lookup 0x533f580 | 4 | 0x533f5c6  mov r14d,[rax+0x438] | [V] |
| draw.refcount | draw-record lookup 0x533f580 | 4 | 0x533f5e7  lock dec dword ptr [rdi] | [V] |
| draw.refcount CAS | draw-record lookup 0x533f580 | 4 | 0x533f613  lock cmpxchg [rcx+0x8],edx | [V] |
| draw.weak refcount+0xC | draw-record lookup 0x533f580 | 4 | 0x533f644  lock dec dword ptr [rdi+0xC] | [V] |
| draw.draw-record+0x68 | draw-record lookup 0x533f580 | 8 | 0x533f65d  mov rax,[rax+0x68] | [V] |
| draw.(rcx+0x148) | draw-record lookup 0x533f580 | 8 | 0x533f66d  mov r8,[rcx+0x148] | [V] |

## CLOSES?

CLOSES? NO — event processor depth write at 0x53365FA (`mov [rax+0x63],bl`) and +0x63 reader at 0x53398EE/0x53398F2 (`cmp byte ptr [rax+0x63],0` / `jne short 0x53398d0`) only have [I] rows inferred from oc_U-H1c.md/oc_U-H1d.md referenced in the GOAL text; they lack [V] verbatim proof lines from the oc_U-H1b.md input data (event processor section in oc_U-H1b.md only covers up to ~0x53364c5, before 0x53365FA and 0x53398EE).

## TOOL REQUESTS

- `verify_oc.py` — used to verify all 166 claimed `0xRVA  instr` lines against the exe; all match (166/166)
- `delegate.py check` — used to validate table shape, duplicate offsets, and SIMD size consistency; passed with 135 rows
- None of the above needed new helper scripts; all existing tools sufficed
