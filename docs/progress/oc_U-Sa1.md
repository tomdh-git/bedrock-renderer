## NEXT
DONE

# Unit U-Sa1 — shadow extractor alt 0x66a6830, slice 0x66a6830..0x66a6d17
Chunk 1 of 7 of effect_shadow_extractor_alt_66a6830_66a88c8. Every instruction of docs/progress/_part_Sa1.txt (0x66a6830..0x66a6d17, 250 instructions) is covered by the phases below; asm lines are verbatim from that listing (two spaces after each address).

## Phase 1 — 0x66a6830..0x66a6914: Prologue saves callee registers (rbp, r15, r14, r13, r12, rsi, rdi, rbx), frames rbp at rsp+0x80, spills xmm10–xmm6 to rbp+0x5D0..0x590, stores sentinel -2 at rbp+0x588 [V], copies arguments (rdx→rbp+0x580 [V]; rcx→r14 [V]; r8→r15 [V]; r9→r12 [V]), runs two stack-cookie probes ([0x129F8CC8]/[0x129F8CE0] vs gs:[0x58] cookie [I]), then builds descriptor {ptr=0xF5CF1BF, len=0xC} at rbp+0x280 [V] and stages arguments for call 0x675E440 [V].
0x66a6830  push rbp
0x66a6831  push r15
0x66a6833  push r14
0x66a6835  push r13
0x66a6837  push r12
0x66a6839  push rsi
0x66a683a  push rdi
0x66a683b  push rbx
0x66a683c  sub rsp,0x668
0x66a6843  lea rbp,[rsp+0x80]
0x66a684b  movaps [rbp+0x5D0],xmm10
0x66a6853  movaps [rbp+0x5C0],xmm9
0x66a685b  movaps [rbp+0x5B0],xmm8
0x66a6863  movaps [rbp+0x5A0],xmm7
0x66a686a  movaps [rbp+0x590],xmm6
0x66a6871  mov qword ptr [rbp+0x588],0xFFFFFFFFFFFFFFFE
0x66a687c  mov r12,r9
0x66a687f  mov r15,r8
0x66a6882  mov [rbp+0x580],rdx
0x66a6889  mov r14,rcx
0x66a688c  mov eax,[0x129F8CC8]
0x66a6892  mov ecx,[0x128767C8]
0x66a6898  mov rdx,gs:[0x58]
0x66a68a1  mov rcx,[rdx+rcx*8]
0x66a68a5  cmp eax,[rcx+4]
0x66a68ab  jg 0x66A862D
0x66a68b1  mov eax,[0x129F8CE0]
0x66a68b7  mov ecx,[0x128767C8]
0x66a68bd  mov rdx,gs:[0x58]
0x66a68c6  mov rcx,[rdx+rcx*8]
0x66a68ca  cmp eax,[rcx+4]
0x66a68d0  jg 0x66A8695
0x66a68d6  mov r9,[r14+0x40]
0x66a68da  mov rcx,[r14+0x68]
0x66a68de  xorps xmm6,xmm6
0x66a68e1  movaps [rbp+0x360],xmm6
0x66a68e8  lea rax,[0xF5CF1BF]
0x66a68ef  mov [rbp+0x280],rax
0x66a68f6  mov qword ptr [rbp+0x288],0xC
0x66a6901  lea rsi,[rbp+0x360]
0x66a6908  mov [rsp+0x28],rsi
0x66a690d  lea rdi,[rbp+0x280]
0x66a6914  mov [rsp+0x20],rdi

## Phase 2 — 0x66a6919..0x66a69c7: Rebuilds the descriptor as {ptr=0xF51E40C, len=0xD} at rbp+0x280 [V] and calls 0x675E440 again with output pointer stored at [rbp+0x270] [V]; then loads the object pointer from [rbp+0x348], cookie-checks it, requires byte [rsi+0x10]==1 [V], and begins releasing the previous object: atomic inc of [rcx+8] [V], then atomic dec of [rdi+8] with destructor calls through [0xF99FFA0] when counts reach zero [I].
0x66a6919  lea r8,[0x129F8CB8]
0x66a6920  lea rdx,[rbp+0x348]
0x66a6927  call 0x675E440
0x66a692c  mov r9,[r14+0x40]
0x66a6930  mov rcx,[r14+0x68]
0x66a6934  movaps [rbp+0x360],xmm6
0x66a693b  lea rax,[0xF51E40C]
0x66a6942  mov [rbp+0x280],rax
0x66a6949  mov qword ptr [rbp+0x288],0xD
0x66a6954  mov [rsp+0x28],rsi
0x66a6959  mov [rsp+0x20],rdi
0x66a695e  lea r8,[0x129F8CD0]
0x66a6965  lea rdx,[rbp+0x270]
0x66a696c  call 0x675E440
0x66a6971  nop
0x66a6972  mov rax,[rbp+0x348]
0x66a6979  mov rsi,[rax]
0x66a697c  test rsi,rsi
0x66a697f  je short 0x66A6A00
0x66a6981  mov eax,[0x129CA5E0]
0x66a6987  mov ecx,[0x128767C8]
0x66a698d  mov rdx,gs:[0x58]
0x66a6996  mov rcx,[rdx+rcx*8]
0x66a699a  cmp eax,[rcx+4]
0x66a69a0  jg 0x66A86FD
0x66a69a6  cmp byte ptr [rsi+0x10],1
0x66a69aa  jne short 0x66A6A00
0x66a69ac  mov rax,[rbp+0x348]
0x66a69b3  mov rcx,[rax+8]
0x66a69b7  test rcx,rcx
0x66a69ba  je short 0x66A6A04
0x66a69bc  lock inc dword ptr [rcx+8]
0x66a69c0  mov rcx,[rax]
0x66a69c3  mov rdi,[rax+8]
0x66a69c7  mov rax,[rcx+0x18]

## Phase 3 — 0x66a69cb..0x66a6a72: Finishes the first object's release (destructor via [0xF99FFA0], then atomic dec of [rdi+0xC] and a second [0xF99FFA0] call at zero [I]); on the empty path sets sil=0. Then loads the second object pointer from [rbp+0x270], cookie-checks it, requires byte [rdi+0x10]==1 [V], and starts the acquire: atomic inc of [rcx+8] [V].
0x66a69cb  mov rsi,[rax]
0x66a69ce  test rdi,rdi
0x66a69d1  je short 0x66A6A0E
0x66a69d3  lock dec dword ptr [rdi+8]
0x66a69d7  jne short 0x66A6A0E
0x66a69d9  mov rax,[rdi]
0x66a69dc  mov rax,[rax]
0x66a69df  mov rcx,rdi
0x66a69e2  call qword ptr [0xF99FFA0]
0x66a69e8  lock dec dword ptr [rdi+0xC]
0x66a69ec  jne short 0x66A6A0E
0x66a69ee  mov rax,[rdi]
0x66a69f1  mov rax,[rax+8]
0x66a69f5  mov rcx,rdi
0x66a69f8  call qword ptr [0xF99FFA0]
0x66a69fe  jmp short 0x66A6A0E
0x66a6a00  xor esi,esi
0x66a6a02  jmp short 0x66A6A15
0x66a6a04  mov rax,[rax]
0x66a6a07  mov rax,[rax+0x18]
0x66a6a0b  mov rsi,[rax]
0x66a6a0e  test rsi,rsi
0x66a6a11  setne sil
0x66a6a15  mov rax,[rbp+0x270]
0x66a6a1c  mov rdi,[rax]
0x66a6a1f  test rdi,rdi
0x66a6a22  je 0x66A8577
0x66a6a28  mov eax,[0x129CA5E0]
0x66a6a2e  mov ecx,[0x128767C8]
0x66a6a34  mov rdx,gs:[0x58]
0x66a6a3d  mov rcx,[rdx+rcx*8]
0x66a6a41  cmp eax,[rcx+4]
0x66a6a47  jg 0x66A8740
0x66a6a4d  cmp byte ptr [rdi+0x10],1
0x66a6a51  jne 0x66A8577
0x66a6a57  mov rax,[rbp+0x270]
0x66a6a5e  mov rcx,[rax+8]
0x66a6a62  test rcx,rcx
0x66a6a65  je short 0x66A6AAB
0x66a6a67  lock inc dword ptr [rcx+8]
0x66a6a6b  mov rcx,[rax]
0x66a6a6e  mov rdi,[rax+8]
0x66a6a72  mov rax,[rcx+0x18]

## Phase 4 — 0x66a6a76..0x66a6b0c: Completes the second object's release ([rdi+8] dec, destructor via [0xF99FFA0], [rdi+0xC] dec, second [0xF99FFA0] at zero [I]), then tests sil&al and bails to 0x66A8577 if clear [V]. Otherwise loads [rbp+0x650], initializes rbp+0x360 and rbp+0x374 to float 1.0 (0x3F800000) [V], zeroes xmm7, and begins vector math: xmm1=[rax] scaled by constant [0xF0A4080] [V], horizontal-added via shufps/addss, with xmm4=[rax+8] [V].
0x66a6a76  mov rbx,[rax]
0x66a6a79  test rdi,rdi
0x66a6a7c  je short 0x66A6AB5
0x66a6a7e  lock dec dword ptr [rdi+8]
0x66a6a82  jne short 0x66A6AB5
0x66a6a84  mov rax,[rdi]
0x66a6a87  mov rax,[rax]
0x66a6a8a  mov rcx,rdi
0x66a6a8d  call qword ptr [0xF99FFA0]
0x66a6a93  lock dec dword ptr [rdi+0xC]
0x66a6a97  jne short 0x66A6AB5
0x66a6a99  mov rax,[rdi]
0x66a6a9c  mov rax,[rax+8]
0x66a6aa0  mov rcx,rdi
0x66a6aa3  call qword ptr [0xF99FFA0]
0x66a6aa9  jmp short 0x66A6AB5
0x66a6aab  mov rax,[rax]
0x66a6aae  mov rax,[rax+0x18]
0x66a6ab2  mov rbx,[rax]
0x66a6ab5  test rbx,rbx
0x66a6ab8  setne al
0x66a6abb  test sil,al
0x66a6abe  je 0x66A8577
0x66a6ac4  mov rax,[rbp+0x650]
0x66a6acb  mov dword ptr [rbp+0x360],0x3F800000
0x66a6ad5  xorps xmm7,xmm7
0x66a6ad8  movups [rbp+0x364],xmm7
0x66a6adf  mov dword ptr [rbp+0x374],0x3F800000
0x66a6ae9  movups [rbp+0x378],xmm7
0x66a6af0  movsd xmm1,[rax]
0x66a6af4  movaps xmm0,[0xF0A4080]
0x66a6afb  movaps xmm2,xmm1
0x66a6afe  mulps xmm2,xmm0
0x66a6b01  movaps xmm3,xmm2
0x66a6b04  shufps xmm3,xmm2,0x55
0x66a6b08  addss xmm3,xmm2
0x66a6b0c  movss xmm4,[rax+8]

## Phase 5 — 0x66a6b11..0x66a6b5f: Vector math continues: xmm5=[0xEF5EAAC]*xmm4 [V]; xmm6=xmm5+xmm3; xmm3=xmm3-xmm4 then interleaved with xmm6 via unpcklps; xmm2 rotated and subtracted from xmm1; xmm5 unpcklps-duplicated and added to xmm2; xmm0 merged via movlhps then bias [0xEEC8060] added [V], stored to rbp+0x388 [V]; xmm3 low part stored to rbp+0x398 via movlps [V]. Then addresses rbp-0x48 and rbp+0x360 staged for call 0xAA6580 [V].
0x66a6b11  movss xmm5,[0xEF5EAAC]
0x66a6b19  mulss xmm5,xmm4
0x66a6b1d  movaps xmm6,xmm5
0x66a6b20  addss xmm6,xmm3
0x66a6b24  subss xmm3,xmm4
0x66a6b28  shufps xmm2,xmm2,0xE1
0x66a6b2c  unpcklps xmm3,xmm6
0x66a6b2f  addps xmm3,[0xEFD32F0]
0x66a6b36  subps xmm2,xmm1
0x66a6b39  unpcklps xmm5,xmm5
0x66a6b3c  addps xmm5,xmm2
0x66a6b3f  movlhps xmm0,xmm5
0x66a6b42  movss xmm6,[0xEEC8060]
0x66a6b4a  addps xmm0,xmm6
0x66a6b4d  movups [rbp+0x388],xmm0
0x66a6b54  movlps [rbp+0x398],xmm3
0x66a6b5b  lea rcx,[rbp-0x48]
0x66a6b5f  lea r8,[rbp+0x360]

## Phase 6 — 0x66a6b66..0x66a6c09: Call 0xAA6580 with rdx=r12 and rcx=rbp-0x48 [V]; then stores r12→rbp+0x268 [V], r15→rbp+0x358 [V], r14→rbp+0x578 [V], zeroes xmm7 to rbp+0x560 [V] and qword rbp+0x570 [V]. Computes the element count of [rbp+0x580]: rsi=[rax+0x10] [V], r15=[rax+0x18] [V], count=(r15-rsi)/4 via magic multiply (0xCCCCCCCCCCCCCCCD, shr 0x3A) [V], stored at rbp+0x360 [V]; calls 0x4E69050 if range non-empty [V]; reloads rsi/r15 [V] and enters loop setup: r14=rbp+0xD4 [V], xmm7=[0xEFD32F0] [V], xmm8=0, xmm9=[0xF0A4080] [V], r12=rbp+0x48, r13=rbp-0x48, rdi=rbp+0xD0, rbx=rbp+0x280 [V]; skips loop body if rsi==r15 [V].
0x66a6b66  mov rdx,r12
0x66a6b69  call 0xAA6580
0x66a6b6e  nop
0x66a6b6f  mov [rbp+0x268],r12
0x66a6b76  mov [rbp+0x358],r15
0x66a6b7d  mov [rbp+0x578],r14
0x66a6b84  movaps [rbp+0x560],xmm7
0x66a6b8b  mov qword ptr [rbp+0x570],0
0x66a6b96  mov rax,[rbp+0x580]
0x66a6b9d  mov rsi,[rax+0x10]
0x66a6ba1  mov r15,[rax+0x18]
0x66a6ba5  mov rcx,r15
0x66a6ba8  sub rcx,rsi
0x66a6bab  sar rcx,2
0x66a6baf  mov rax,0xCCCCCCCCCCCCCCCD
0x66a6bb9  imul rax,rcx
0x66a6bbd  mov [rbp+0x360],rax
0x66a6bc4  cmp r15,rsi
0x66a6bc7  je short 0x66A6BF6
0x66a6bc9  shr rax,0x3A
0x66a6bcd  jne 0x66A8812
0x66a6bd3  lea rcx,[rbp+0x560]
0x66a6bda  lea rdx,[rbp+0x360]
0x66a6be1  call 0x4E69050
0x66a6be6  nop
0x66a6be7  mov rax,[rbp+0x580]
0x66a6bee  mov rsi,[rax+0x10]
0x66a6bf2  mov r15,[rax+0x18]
0x66a6bf6  lea r14,[rbp+0xD4]
0x66a6bfd  movsd xmm7,[0xEFD32F0]
0x66a6c05  xorps xmm8,xmm8
0x66a6c09  movaps xmm9,[0xF0A4080]

## Phase 7 — 0x66a6c11..0x66a6c80: Loop setup continues: r12=rbp+0x48 [V] (write cursor into output vector at rbp+0x48), r13=rbp-0x48 [V] (scratch vector), rdi=rbp+0xD0 [V], rbx=rbp+0x280 [V]. Loop body begins at 0x66a6c24 target: if rsi==r15 jumps to 0x66A6E30 [V]. Each iteration copies 16 dwords (64 bytes) from rbp+0x360..0x39C to [rdx]..[rdx+0x3C] via movss stores [V] (rdx=r12 current write cursor), then advances rbp+0x568 by 0x40 [V] and rsi by 0x14 [V] (20 bytes per source element). Note rdx is not reloaded inside the shown slice, so consecutive iterations appear to target the same [rdx] base; the update of rdx is beyond this slice [UNVERIFIED: 0x66a6d17 does rdx get updated before next iteration?].
0x66a6c11  lea r12,[rbp+0x48]
0x66a6c15  lea r13,[rbp-0x48]
0x66a6c19  lea rdi,[rbp+0xD0]
0x66a6c20  lea rbx,[rbp+0x280]
0x66a6c27  cmp rsi,r15
0x66a6c2a  jne 0x66A6D24
0x66a6c30  jmp 0x66A6E30
0x66a6c35  nop [rax+rax]
0x66a6c40  movss xmm0,[rbp+0x360]
0x66a6c48  movss [rdx],xmm0
0x66a6c4c  movss xmm0,[rbp+0x364]
0x66a6c54  movss [rdx+4],xmm0
0x66a6c59  movss xmm0,[rbp+0x368]
0x66a6c61  movss [rdx+8],xmm0
0x66a6c66  movss xmm0,[rbp+0x36C]
0x66a6c6e  movss [rdx+0xC],xmm0
0x66a6c73  movss xmm0,[rbp+0x370]
0x66a6c7b  movss [rdx+0x10],xmm0
0x66a6c80  movss xmm0,[rbp+0x374]
0x66a6c88  movss [rdx+0x14],xmm0

## Phase 8 — 0x66a6c8d..0x66a6d17: Loop body tail: stores rbp+0x378..0x39C to [rdx+0x18]..[rdx+0x3C] via movss [V]; then rbp+0x568 += 0x40 [V] and rsi += 0x14 (20 bytes per source element) [V]; slice ends at 0x66a6d17.
0x66a6c8d  movss xmm0,[rbp+0x378]
0x66a6c95  movss [rdx+0x18],xmm0
0x66a6c9a  movss xmm0,[rbp+0x37C]
0x66a6ca2  movss [rdx+0x1C],xmm0
0x66a6ca7  movss xmm0,[rbp+0x380]
0x66a6caf  movss [rdx+0x20],xmm0
0x66a6cb4  movss xmm0,[rbp+0x384]
0x66a6cbc  movss [rdx+0x24],xmm0
0x66a6cc1  movss xmm0,[rbp+0x388]
0x66a6cc9  movss [rdx+0x28],xmm0
0x66a6cce  movss xmm0,[rbp+0x38C]
0x66a6cd6  movss [rdx+0x2C],xmm0
0x66a6cdb  movss xmm0,[rbp+0x390]
0x66a6ce3  movss [rdx+0x30],xmm0
0x66a6ce8  movss xmm0,[rbp+0x394]
0x66a6cf0  movss [rdx+0x34],xmm0
0x66a6cf5  movss xmm0,[rbp+0x398]
0x66a6cfd  movss [rdx+0x38],xmm0
0x66a6d02  movss xmm0,[rbp+0x39C]
0x66a6d0a  movss [rdx+0x3C],xmm0
0x66a6d0f  add qword ptr [rbp+0x568],0x40
0x66a6d17  add rsi,0x14

## Field table — every [reg+off] field stored or loaded in the slice (one row per distinct offset, all sites listed)
| offset | size | direction | verbatim `0xRVA  instr` line | meaning |
| rbp+0x5D0 | 16 | W | 0x66a684b  movaps [rbp+0x5D0],xmm10 | - |
| rbp+0x5C0 | 16 | W | 0x66a6853  movaps [rbp+0x5C0],xmm9 | - |
| rbp+0x5B0 | 16 | W | 0x66a685b  movaps [rbp+0x5B0],xmm8 | - |
| rbp+0x5A0 | 16 | W | 0x66a6863  movaps [rbp+0x5A0],xmm7 | - |
| rbp+0x590 | 16 | W | 0x66a686a  movaps [rbp+0x590],xmm6 | - |
| rbp+0x588 | 8 | W | 0x66a6871  mov qword ptr [rbp+0x588],0xFFFFFFFFFFFFFFFE | - |
| rbp+0x580 | 8 | W | 0x66a6882  mov [rbp+0x580],rdx | - |
| gs:0x58 | 8 | R | 0x66a6898  mov rdx,gs:[0x58] ; 0x66a68bd  mov rdx,gs:[0x58] ; 0x66a698d  mov rdx,gs:[0x58] ; 0x66a6a34  mov rdx,gs:[0x58] | - |
| rcx+4 | 4 | R | 0x66a68a5  cmp eax,[rcx+4] ; 0x66a68ca  cmp eax,[rcx+4] ; 0x66a699a  cmp eax,[rcx+4] ; 0x66a6a41  cmp eax,[rcx+4] | - |
| r14+0x40 | 8 | R | 0x66a68d6  mov r9,[r14+0x40] | - |
| r14+0x68 | 8 | R | 0x66a68da  mov rcx,[r14+0x68] | - |
| rbp+0x360 | 16 | R/W | 0x66a68e1  movaps [rbp+0x360],xmm6 ; 0x66a6934  movaps [rbp+0x360],xmm6 ; 0x66a6acb  mov dword ptr [rbp+0x360],0x3F800000 ; 0x66a6bbd  mov [rbp+0x360],rax ; 0x66a6c40  movss xmm0,[rbp+0x360] | - |
| rbp+0x280 | 8 | W | 0x66a68ef  mov [rbp+0x280],rax ; 0x66a6942  mov [rbp+0x280],rax | - |
| rbp+0x288 | 8 | W | 0x66a68f6  mov qword ptr [rbp+0x288],0xC ; 0x66a6949  mov qword ptr [rbp+0x288],0xD | - |
| rsp+0x28 | 8 | W | 0x66a6908  mov [rsp+0x28],rsi ; 0x66a6954  mov [rsp+0x28],rsi | - |
| rsp+0x20 | 8 | W | 0x66a6914  mov [rsp+0x20],rdi ; 0x66a6959  mov [rsp+0x20],rdi | - |
| rbp+0x348 | 8 | R | 0x66a6972  mov rax,[rbp+0x348] ; 0x66a69ac  mov rax,[rbp+0x348] | - |
| rax | 8 | R | 0x66a6979  mov rsi,[rax] ; 0x66a69cb  mov rsi,[rax] ; 0x66a6a04  mov rax,[rax] ; 0x66a69dc  mov rax,[rax] ; 0x66a6af0  movsd xmm1,[rax] | - |
| rax+8 | 4 | R | 0x66a69b3  mov rcx,[rax+8] ; 0x66a69c3  mov rdi,[rax+8] ; 0x66a6a07  mov rax,[rax+8] ; 0x66a6a5e  mov rcx,[rax+8] ; 0x66a6a6e  mov rdi,[rax+8] ; 0x66a6a9c  mov rax,[rax+8] ; 0x66a6aae  mov rax,[rax+8] ; 0x66a6b0c  movss xmm4,[rax+8] | - |
| rcx+8 | 4 | RW | 0x66a69bc  lock inc dword ptr [rcx+8] ; 0x66a6a67  lock inc dword ptr [rcx+8] | - |
| rdi+8 | 4 | RW | 0x66a69d3  lock dec dword ptr [rdi+8] ; 0x66a6a7e  lock dec dword ptr [rdi+8] | - |
| rdi | 8 | R | 0x66a69d9  mov rax,[rdi] ; 0x66a69ee  mov rax,[rdi] ; 0x66a6a84  mov rax,[rdi] ; 0x66a6a99  mov rax,[rdi] | - |
| rcx+0x18 | 8 | R | 0x66a69c7  mov rax,[rcx+0x18] ; 0x66a6a72  mov rax,[rcx+0x18] | - |
| rdi+0xC | 4 | RW | 0x66a69e8  lock dec dword ptr [rdi+0xC] ; 0x66a6a93  lock dec dword ptr [rdi+0xC] | - |
| rsi+0x10 | 1 | R | 0x66a69a6  cmp byte ptr [rsi+0x10],1 | - |
| rdi+0x10 | 1 | R | 0x66a6a4d  cmp byte ptr [rdi+0x10],1 | - |
| rbp+0x270 | 8 | R | 0x66a6a15  mov rax,[rbp+0x270] | - |
| rbp+0x650 | 8 | R | 0x66a6ac4  mov rax,[rbp+0x650] | - |
| rbp+0x364 | 16 | R/W | 0x66a6ad8  movups [rbp+0x364],xmm7 ; 0x66a6c4c  movss xmm0,[rbp+0x364] | - |
| rbp+0x368 | 4 | R | 0x66a6c59  movss xmm0,[rbp+0x368] | - |
| rbp+0x36C | 4 | R | 0x66a6c66  movss xmm0,[rbp+0x36C] | - |
| rbp+0x370 | 4 | R | 0x66a6c73  movss xmm0,[rbp+0x370] | - |
| rbp+0x374 | 4 | R/W | 0x66a6adf  mov dword ptr [rbp+0x374],0x3F800000 ; 0x66a6c80  movss xmm0,[rbp+0x374] | - |
| rbp+0x378 | 16 | R/W | 0x66a6ae9  movups [rbp+0x378],xmm7 ; 0x66a6c8d  movss xmm0,[rbp+0x378] | - |
| rbp+0x37C | 4 | R | 0x66a6c9a  movss xmm0,[rbp+0x37C] | - |
| rbp+0x380 | 4 | R | 0x66a6ca7  movss xmm0,[rbp+0x380] | - |
| rbp+0x384 | 4 | R | 0x66a6cb4  movss xmm0,[rbp+0x384] | - |
| rbp+0x388 | 16 | R/W | 0x66a6b4d  movups [rbp+0x388],xmm0 ; 0x66a6cc1  movss xmm0,[rbp+0x388] | - |
| rbp+0x38C | 4 | R | 0x66a6cce  movss xmm0,[rbp+0x38C] | - |
| rbp+0x390 | 4 | R | 0x66a6cdb  movss xmm0,[rbp+0x390] | - |
| rbp+0x394 | 4 | R | 0x66a6ce8  movss xmm0,[rbp+0x394] | - |
| rbp+0x398 | 4 | R/W | 0x66a6b54  movlps [rbp+0x398],xmm3 ; 0x66a6cf5  movss xmm0,[rbp+0x398] | - |
| rbp+0x39C | 4 | R | 0x66a6d02  movss xmm0,[rbp+0x39C] | - |
| rbp+0x268 | 8 | W | 0x66a6b6f  mov [rbp+0x268],r12 | - |
| rbp+0x358 | 8 | W | 0x66a6b76  mov [rbp+0x358],r15 | - |
| rbp+0x578 | 8 | W | 0x66a6b7d  mov [rbp+0x578],r14 | - |
| rbp+0x560 | 16 | W | 0x66a6b84  movaps [rbp+0x560],xmm7 | - |
| rbp+0x570 | 8 | W | 0x66a6b8b  mov qword ptr [rbp+0x570],0 | - |
| rbp+0x568 | 8 | RW | 0x66a6d0f  add qword ptr [rbp+0x568],0x40 | - |
| rdx+0x0 | 4 | W | 0x66a6c48  movss [rdx],xmm0 | - |
| rdx+0x4 | 4 | W | 0x66a6c54  movss [rdx+4],xmm0 | - |
| rdx+0x8 | 4 | W | 0x66a6c61  movss [rdx+8],xmm0 | - |
| rdx+0xC | 4 | W | 0x66a6c6e  movss [rdx+0xC],xmm0 | - |
| rdx+0x10 | 4 | W | 0x66a6c7b  movss [rdx+0x10],xmm0 | - |
| rdx+0x14 | 4 | W | 0x66a6c88  movss [rdx+0x14],xmm0 | - |
| rdx+0x18 | 4 | W | 0x66a6c95  movss [rdx+0x18],xmm0 | - |
| rdx+0x1C | 4 | W | 0x66a6ca2  movss [rdx+0x1C],xmm0 | - |
| rdx+0x20 | 4 | W | 0x66a6caf  movss [rdx+0x20],xmm0 | - |
| rdx+0x24 | 4 | W | 0x66a6cbc  movss [rdx+0x24],xmm0 | - |
| rdx+0x28 | 4 | W | 0x66a6cc9  movss [rdx+0x28],xmm0 | - |
| rdx+0x2C | 4 | W | 0x66a6cd6  movss [rdx+0x2C],xmm0 | - |
| rdx+0x30 | 4 | W | 0x66a6ce3  movss [rdx+0x30],xmm0 | - |
| rdx+0x34 | 4 | W | 0x66a6cf0  movss [rdx+0x34],xmm0 | - |
| rdx+0x38 | 4 | W | 0x66a6cfd  movss [rdx+0x38],xmm0 | - |
| rdx+0x3C | 4 | W | 0x66a6d0a  movss [rdx+0x3C],xmm0 | - |

## OPEN questions
- [UNVERIFIED: 0x66a6d17] does rdx get updated before the next loop iteration? The shown slice stores to [rdx+0x0..0x3C] every iteration with no visible rdx update; the rdx update must be at 0x66a6d18+ (beyond slice end).
- Meaning of constants 0xF5CF1BF / 0xF51E40C (descriptor ptrs) and 0xF0A4080 / 0xEF5EAAC / 0xEFD32F0 / 0xEEC8060 (vector math constants) — not resolved by instructions alone.
- Targets of calls 0x675E440, 0xAA6580, 0x4E69050 and indirect [0xF99FFA0] are outside this slice; not resolved here.
- Meaning of [rbp+0x650] object fields (+0x0 vector, +0x8 z) inferred from usage only.

## TOOL REQUESTS
None — all content transcribed verbatim from docs/progress/_part_Sa1.txt; no helper script needed.
