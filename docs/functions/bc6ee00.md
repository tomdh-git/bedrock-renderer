# sub_bc6ee00 (0xbc6ee00, size 0x122) - lift dossier

Minecraft Windows 1.26.62.01. Region bgfx, milestone D0, depth 5 ("VV frame-graph builder"). [0xbc6ee00, 0xbc6ef22). Source: src/client/features/render/native/bgfx/sub_bc6ee00.cpp + .h.

## Signature

void* sub_bc6ee00(uint8_t* a0, void* a1);   // x64 Microsoft ABI: rcx = a0, rdx = a1, return rax = a1 [V]

## Register / argument map

- rcx = a0: object base (uint8_t*). Copied to rbx at 0xbc6ee1a and used as the base for every direct a0 offset read. [V]
- rdx = a1: destination object base. Copied to rsi at 0xbc6ee17; written at 0x74..0x88, 0x90, 0xD0, 0xD4; returned in rax. [V]
- rdi = a0 + 0x1C0 [V: lea rdi,[rcx+0x1C0] at 0xbc6ee1d]; passed in rcx to sub_ebdbf10 (0xbc6ee27) and sub_ebdbf20 (0xbc6ef0e).
- r14 = *(uint8_t**)(a0 + 0x1CFD0C8) [V: 0xbc6ee2c]; byte base for reads at 0xE60DE8, 0xDC5808, 0xE60DE0.
- No /GS cookie read/write and no SEH handlers in this function [V: prologue 0xbc6ee00..0xbc6ee16 writes [rbp-8] = -2 only, an EH state slot never read].

## Reversed source (complete)

0xbc6ee00..0xbc6ee16: prologue — 5 push frame, sub rsp,0x30, rbp frame, EH state slot [rbp-8] = -2 (never read).
   void* rsi = a1;                 // 0xbc6ee17  mov rsi,rdx
   uint8_t* rbx = a0;              // 0xbc6ee1a  mov rbx,rcx
   void* rdi = (void*)(a0 + 0x1C0); // 0xbc6ee1d  lea rdi,[rcx+0x1C0]
   // 0xbc6ee00  push rbp
   // 0xbc6ee01  push r14
   // 0xbc6ee03  push rsi
   // 0xbc6ee04  push rdi
   // 0xbc6ee05  push rbx
   // 0xbc6ee06  sub rsp,0x30
   // 0xbc6ee0a  lea rbp,[rsp+0x30]
   // 0xbc6ee0f  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
   // 0xbc6ee17  mov rsi,rdx
   // 0xbc6ee1a  mov rbx,rcx
   // 0xbc6ee1d  lea rdi,[rcx+0x1C0]

0xbc6ee24..0xbc6ee2b: sub_ebdbf10(a0 + 0x1C0); the return value in rax is dead (never read before being overwritten).
   sub_ebdbf10(rdi);
   // 0xbc6ee24  mov rcx,rdi
   // 0xbc6ee27  call 0xEBDBF10

0xbc6ee2c..0xbc6ee39: r14 = *(uint8_t**)(a0 + 0x1CFD0C8); rdx = r14 + 0xE60DE8; r8d = 0xD0.
   uint8_t* r14 = *(uint8_t**)(rbx + 0x1CFD0C8);   // 0xbc6ee2c  mov r14,[rbx+0x1CFD0C8]
   void* rdx = r14 + 0xE60DE8;                     // 0xbc6ee33  lea rdx,[r14+0xE60DE8]
   uint32_t r8d = 0xD0u;                           // 0xbc6ee3a  mov r8d,0xD0
   // 0xbc6ee2c  mov r14,[rbx+0x1CFD0C8]
   // 0xbc6ee33  lea rdx,[r14+0xE60DE8]
   // 0xbc6ee3a  mov r8d,0xD0

0xbc6ee40..0xbc6ee43: rcx = rsi (= a1), then sub_eec6ec0(a1, r14 + 0xE60DE8, 0xD0); return value in rax is dead.
   sub_eec6ec0(rsi, rdx, r8d);
   // 0xbc6ee40  mov rcx,rsi
   // 0xbc6ee43  call 0xEEC6EC0

0xbc6ee48..0xbc6ee56: xmm0 = movq [r14+0xDC5808] (8 bytes); pshuflw xmm0,xmm0,0xE8 keeps words {w0,w2,w3,w3};
   a1+0xD0 = low dword of xmm0 = {w0, w2} (4 bytes).
   uint16_t loaded[4]; memcpy(loaded, r14 + 0xDC5808, 8); // 0xbc6ee48  movq xmm0,[r14+0xDC5808]
   uint16_t shuffle[2] = {loaded[0], loaded[2]};           // 0xbc6ee51  pshuflw xmm0,xmm0,0xE8
   memcpy((uint8_t*)a1 + 0xD0, shuffle, 4);               // 0xbc6ee56  movd [rsi+0xD0],xmm0
   // 0xbc6ee48  movq xmm0,[r14+0xDC5808]
   // 0xbc6ee51  pshuflw xmm0,xmm0,0xE8
   // 0xbc6ee56  movd [rsi+0xD0],xmm0

0xbc6ee5e..0xbc6ee68: p = *(uint8_t**)(r14 + 0xE60DE0); a1+0xD4 = *(uint32_t*)(p + 0xC).
   uint8_t* p = *(uint8_t**)(r14 + 0xE60DE0);         // 0xbc6ee5e  mov rax,[r14+0xE60DE0]
   *(uint32_t*)((uint8_t*)a1 + 0xD4) = *(uint32_t*)(p + 0xC); // 0xbc6ee65  mov eax,[rax+0xC] / 0xbc6ee68  mov [rsi+0xD4],eax
   // 0xbc6ee5e  mov rax,[r14+0xE60DE0]
   // 0xbc6ee65  mov eax,[rax+0xC]
   // 0xbc6ee68  mov [rsi+0xD4],eax

0xbc6ee6e..0xbc6ee99: a1+0x74..0x7A = words from a0+0x1DDD308, a0+0x1DE1348, a0+0x1DFB48C, a0+0x1DE534C (in this order).
   *(uint16_t*)((uint8_t*)a1 + 0x74) = *(uint16_t*)(rbx + 0x1DDD308); // 0xbc6ee6e / 0xbc6ee75
   *(uint16_t*)((uint8_t*)a1 + 0x76) = *(uint16_t*)(rbx + 0x1DE1348); // 0xbc6ee79 / 0xbc6ee80
   *(uint16_t*)((uint8_t*)a1 + 0x78) = *(uint16_t*)(rbx + 0x1DFB48C); // 0xbc6ee84 / 0xbc6ee8b
   *(uint16_t*)((uint8_t*)a1 + 0x7A) = *(uint16_t*)(rbx + 0x1DE534C); // 0xbc6ee8f / 0xbc6ee96
   // 0xbc6ee6e  movzx eax,word ptr [rbx+0x1DDD308]
   // 0xbc6ee75  mov [rsi+0x74],ax
   // 0xbc6ee79  movzx eax,word ptr [rbx+0x1DE1348]
   // 0xbc6ee80  mov [rsi+0x76],ax
   // 0xbc6ee84  movzx eax,word ptr [rbx+0x1DFB48C]
   // 0xbc6ee8b  mov [rsi+0x78],ax
   // 0xbc6ee8f  movzx eax,word ptr [rbx+0x1DE534C]
   // 0xbc6ee96  mov [rsi+0x7A],ax

0xbc6ee9a..0xbc6eebd: a1+0x7C..0x82 = words from a0+0x1DFBE94, a0+0x1DF145C, a0+0x1DED458, a0+0x1DF7478 (in this order).
   *(uint16_t*)((uint8_t*)a1 + 0x7C) = *(uint16_t*)(rbx + 0x1DFBE94); // 0xbc6ee9a / 0xbc6eea1
   *(uint16_t*)((uint8_t*)a1 + 0x7E) = *(uint16_t*)(rbx + 0x1DF145C); // 0xbc6eea5 / 0xbc6eeac
   *(uint16_t*)((uint8_t*)a1 + 0x80) = *(uint16_t*)(rbx + 0x1DED458); // 0xbc6eeb0 / 0xbc6eeb7
   *(uint16_t*)((uint8_t*)a1 + 0x82) = *(uint16_t*)(rbx + 0x1DF7478); // 0xbc6eebe / 0xbc6eec5
   // 0xbc6ee9a  movzx eax,word ptr [rbx+0x1DFBE94]
   // 0xbc6eea1  mov [rsi+0x7C],ax
   // 0xbc6eea5  movzx eax,word ptr [rbx+0x1DF145C]
   // 0xbc6eeac  mov [rsi+0x7E],ax
   // 0xbc6eeb0  movzx eax,word ptr [rbx+0x1DED458]
   // 0xbc6eeb7  mov [rsi+0x80],ax
   // 0xbc6eebe  movzx eax,word ptr [rbx+0x1DF7478]
   // 0xbc6eec5  mov [rsi+0x82],ax

0xbc6eecc..0xbc6eef5: a1+0x84..0x88 = words from a0+0x1DFB690, a0+0x1DE9454, a0+0x1DE9350 (in this order).
   *(uint16_t*)((uint8_t*)a1 + 0x84) = *(uint16_t*)(rbx + 0x1DFB690); // 0xbc6eecc / 0xbc6eed3
   *(uint16_t*)((uint8_t*)a1 + 0x86) = *(uint16_t*)(rbx + 0x1DE9454); // 0xbc6eeda / 0xbc6eee1
   *(uint16_t*)((uint8_t*)a1 + 0x88) = *(uint16_t*)(rbx + 0x1DE9350); // 0xbc6eee8 / 0xbc6eeef
   // 0xbc6eecc  movzx eax,word ptr [rbx+0x1DFB690]
   // 0xbc6eed3  mov [rsi+0x84],ax
   // 0xbc6eeda  movzx eax,word ptr [rbx+0x1DE9454]
   // 0xbc6eee1  mov [rsi+0x86],ax
   // 0xbc6eee8  movzx eax,word ptr [rbx+0x1DE9350]
   // 0xbc6eeef  mov [rsi+0x88],ax

0xbc6eef6..0xbc6ef03: xmm0 = movdqu [a0+0x1EBF1D8] (16 bytes); pshufd xmm0,xmm0,0x4E = {d2,d3,d0,d1};
   a1+0x90 = all 16 bytes (rotate by 8 bytes).
   uint32_t block[4]; memcpy(block, rbx + 0x1EBF1D8, 16);        // 0xbc6eef6  movdqu xmm0,[rbx+0x1EBF1D8]
   uint32_t rotated[4] = {block[2], block[3], block[0], block[1]}; // 0xbc6eefe  pshufd xmm0,xmm0,0x4E
   memcpy((uint8_t*)a1 + 0x90, rotated, 16);                     // 0xbc6ef03  movdqu [rsi+0x90],xmm0
   // 0xbc6eef6  movdqu xmm0,[rbx+0x1EBF1D8]
   // 0xbc6eefe  pshufd xmm0,xmm0,0x4E
   // 0xbc6ef03  movdqu [rsi+0x90],xmm0

0xbc6ef0b..0xbc6ef0e: sub_ebdbf20(a0 + 0x1C0); return value in rax is dead (mov rax,rsi follows).
   sub_ebdbf20(rdi);
   // 0xbc6ef0b  mov rcx,rdi
   // 0xbc6ef0e  call 0xEBDBF20

0xbc6ef13..0xbc6ef21: rax = rsi (= a1); epilogue; ret.
   return rsi;                                       // 0xbc6ef14  mov rax,rsi
   // 0xbc6ef13  nop
   // 0xbc6ef14  mov rax,rsi
   // 0xbc6ef17  add rsp,0x30
   // 0xbc6ef1b  pop rbx
   // 0xbc6ef1c  pop rdi
   // 0xbc6ef1d  pop rsi
   // 0xbc6ef1e  pop r14
   // 0xbc6ef20  pop rbp
   // 0xbc6ef21  ret

## Call claims verified against the exe

The three call instructions, verbatim from the disassembly:

0xbc6ee27  call 0xEBDBF10
0xbc6ee43  call 0xEEC6EC0
0xbc6ef0e  call 0xEBDBF20

## Struct fields touched

| object | offset | size | dir | meaning | tag |
| a0 | 0x1C0 | 8 | R | address taken (lea), argument to sub_ebdbf10/sub_ebdbf20, never dereferenced | [V] |
| a0 | 0x1CFD0C8 | 8 | R | loaded pointer → r14 byte base | [V] |
| r14 (= *a0+0x1CFD0C8) | 0xE60DE8 | 0xD0 | R | source buffer of sub_eec6ec0 copy | [V] |
| r14 | 0xDC5808 | 8 | R | 8 bytes; shuffled (pshuflw 0xE8), low dword → a1+0xD0 | [V] |
| r14 | 0xE60DE0 | 8 | R | loaded pointer p; *(uint32_t*)(p + 0xC) read | [V] |
| a0 | 0x1DDD308 | 2 | R | → a1+0x74 | [V] |
| a0 | 0x1DE1348 | 2 | R | → a1+0x76 | [V] |
| a0 | 0x1DFB48C | 2 | R | → a1+0x78 | [V] |
| a0 | 0x1DE534C | 2 | R | → a1+0x7A | [V] |
| a0 | 0x1DFBE94 | 2 | R | → a1+0x7C | [V] |
| a0 | 0x1DF145C | 2 | R | → a1+0x7E | [V] |
| a0 | 0x1DED458 | 2 | R | → a1+0x80 | [V] |
| a0 | 0x1DF7478 | 2 | R | → a1+0x82 | [V] |
| a0 | 0x1DFB690 | 2 | R | → a1+0x84 | [V] |
| a0 | 0x1DE9454 | 2 | R | → a1+0x86 | [V] |
| a0 | 0x1DE9350 | 2 | R | → a1+0x88 | [V] |
| a0 | 0x1EBF1D8 | 16 | R | rotated (pshufd 0x4E) → a1+0x90 | [V] |
| a1 | 0x74..0x88 | 2 each | W | 12 uint16 stores from a0 words, in the order above | [V] |
| a1 | 0x90 | 16 | W | rotated dwords from a0+0x1EBF1D8 | [V] |
| a1 | 0xD0 | 4 | W | {w0,w2} of shuffled r14+0xDC5808 | [V] |
| a1 | 0xD4 | 4 | W | *(uint32_t*)(*(r14+0xE60DE0) + 0xC) | [V] |

## Callees

| callee | call site | arguments (registers, observed) | return | class | tag |
| sub_ebdbf10 (0xEBDBF10) | 0xbc6ee27  call 0xEBDBF10 | rcx = a0 + 0x1C0 | unused (rax dead) | lift — docs/data/native_boundary.tsv line 510 [V] | called directly via namespace-native forward declaration in sub_bc6ee00.h [V] |
| sub_eec6ec0 (0xEEC6EC0) | 0xbc6ee43  call 0xEEC6EC0 | rcx = a1, rdx = r14 + 0xE60DE8, r8d = 0xD0 | unused (rax dead) | lift — docs/data/native_boundary.tsv line 512 [V] | called directly via namespace-native forward declaration in sub_bc6ee00.h [V] |
| sub_ebdbf20 (0xEBDBF20) | 0xbc6ef0e  call 0xEBDBF20 | rcx = a0 + 0x1C0 | unused (rax dead) | lift — docs/data/native_boundary.tsv line 511 [V] | called directly via namespace-native forward declaration in sub_bc6ee00.h [V] |

## OPEN questions

None. All three callees are `lift`-classified in docs/data/native_boundary.tsv (lines 510-512) [V] and are called directly through the namespace-native forward declarations in sub_bc6ee00.h (hard rule 66); no wrapper, no unresolved call, nothing blocks the lift.
