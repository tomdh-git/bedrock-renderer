## NEXT
DONE

# UNIT U-Sa5 — shadow extractor alt 0x66a6830, instruction slice 0x66a7ba1..0x66a80d9 (chunk 5 of 7)

Source listing: docs/progress/_part_Sa5.txt — 250 instructions from 0x66a7ba1 to 0x66a80d9. Every instruction below is covered in exactly one phase; all `0xRVA  instr` lines are copied verbatim from that listing (two spaces after the address). No instruction is skipped. Field sizes come from the instruction (movups/movaps 16B, movlps 8B, qword 8B, dword/movss 4B, word 2B, byte 1B).

## Phases (each <= 40 instructions)

### Phase 1: 0x66a7ba1..0x66a7c2a
Stack shadow-record header is initialized: xmm10 stored at [rbp+0x388]; type/state bytes and zero fields written at [rbp+0x398..0x3BA] (byte 3, qword 0, dword 0, byte 3, qword 0, dword 0, word 0x101, byte 0xFF); xmm9 low quad stored at [rbp+0x3BC] (movlps) and an xmm0-derived dword at [rbp+0x3C4] (movss). [rbp+0x158] is loaded and stored at [rbp+0x3D0], rdi = rbp+0x3D8, then 0xE869FF0 is called.
0x66a7ba1  movups [rbp+0x388],xmm10
0x66a7ba9  mov byte ptr [rbp+0x398],3
0x66a7bb0  mov qword ptr [rbp+0x39C],0
0x66a7bbb  mov dword ptr [rbp+0x3A4],0
0x66a7bc5  mov byte ptr [rbp+0x3A8],3
0x66a7bcc  mov qword ptr [rbp+0x3AC],0
0x66a7bd7  mov dword ptr [rbp+0x3B4],0
0x66a7be1  mov word ptr [rbp+0x3B8],0x101
0x66a7bea  mov byte ptr [rbp+0x3BA],0xFF
0x66a7bf1  movlps [rbp+0x3BC],xmm9
0x66a7bf9  movaps xmm0,xmm9
0x66a7bfd  unpckhpd xmm0,xmm9
0x66a7c02  movss [rbp+0x3C4],xmm0
0x66a7c0a  mov rax,[rbp+0x158]
0x66a7c11  mov [rbp+0x3D0],rax
0x66a7c18  lea rdi,[rbp+0x3D8]
0x66a7c1f  mov rcx,rdi
0x66a7c22  mov rdx,r12
0x66a7c25  call 0xE869FF0
0x66a7c2a  nop

### Phase 2: 0x66a7c2b..0x66a7cc6
Reloads [rbp+0x1D8] into rax and stores it at [rbp+0x450], then clears [rbp+0x1D8]; xmm6-xmm9 are spilled to [rbp+0x458..0x488], byte 0 stored at [rbp+0x498] and si at [rbp+0x4A0]. xmm0/xmm1 are reloaded from [rbp+0x500]/[rbp+0x510], [rbp+0x508] zeroed, xmm0/xmm1 restored to [rbp+0x4A8]/[rbp+0x4B8], [rbp+0x520] stored at [rbp+0x4C8], 0xFF written at [rbp+0x4E0], byte [rbp+0x538] zero-extended into eax, and control jumps through the table at [0xF2BF838] when eax > 3.
0x66a7c2b  mov rax,[rbp+0x1D8]
0x66a7c32  mov [rbp+0x450],rax
0x66a7c39  mov qword ptr [rbp+0x1D8],0
0x66a7c44  movups [rbp+0x458],xmm6
0x66a7c4b  movups [rbp+0x468],xmm7
0x66a7c52  movups [rbp+0x478],xmm8
0x66a7c5a  movups [rbp+0x488],xmm9
0x66a7c62  mov byte ptr [rbp+0x498],0
0x66a7c69  mov [rbp+0x4A0],si
0x66a7c70  movaps xmm0,[rbp+0x500]
0x66a7c77  movaps xmm1,[rbp+0x510]
0x66a7c7e  mov qword ptr [rbp+0x508],0
0x66a7c89  movups [rbp+0x4A8],xmm0
0x66a7c90  movaps [rbp+0x510],xmm10
0x66a7c98  movups [rbp+0x4B8],xmm1
0x66a7c9f  mov rax,[rbp+0x520]
0x66a7ca6  mov [rbp+0x4C8],rax
0x66a7cad  mov byte ptr [rbp+0x4E0],0xFF
0x66a7cb4  movzx eax,byte ptr [rbp+0x538]
0x66a7cbb  cmp rax,3
0x66a7cbf  mov r9,[rbp+0x578]
0x66a7cc6  ja short 0x66A7D3B

### Phase 3: 0x66a7cc8..0x66a7d0f
Jump-table dispatch: case 0 (rcx = rbp+0x4D0) stores [rbp+0x528] at [rbp+0x4D0]; case 1 (rdx = [rbp+0x528]) copies 16 bytes from [rdx] to [rcx]; the default path xorps-zeroes xmm0, writes 16 zero bytes at [rcx], loads [rbp+0x530] into rcx and, if rcx != 0, falls to the atomic increment below, otherwise ecx = 0. All entries join at the store of al to [rbp+0x4E0].
0x66a7cc8  lea rcx,[rbp+0x4D0]
0x66a7ccf  lea rdx,[0xF2BF838]
0x66a7cd6  movsxd r8,[rdx+rax*4]
0x66a7cda  add r8,rdx
0x66a7cdd  jmp r8
0x66a7ce0  mov rcx,[rbp+0x528]
0x66a7ce7  mov [rbp+0x4D0],rcx
0x66a7cee  jmp short 0x66A7D35
0x66a7cf0  lea rdx,[rbp+0x528]
0x66a7cf7  movups xmm0,[rdx]
0x66a7cfa  movups [rcx],xmm0
0x66a7cfd  jmp short 0x66A7D35
0x66a7cff  xorps xmm0,xmm0
0x66a7d02  movups [rcx],xmm0
0x66a7d05  mov rcx,[rbp+0x530]
0x66a7d0c  test rcx,rcx
0x66a7d0f  je short 0x66A7D1E

### Phase 4: 0x66a7d11..0x66a7d66
Default path completes: if rcx != 0, dword [rcx+8] is atomically incremented (lock inc) and rcx is reloaded from [rbp+0x530]; otherwise ecx = 0. rdx = [rbp+0x528] is stored at [rbp+0x4D0], rcx at [rbp+0x4D8], al at [rbp+0x4E0]; [rbp+0x550] is stored at [rbp+0x4F8] and xmm0, reloaded from [rbp+0x540], at [rbp+0x4E8]. ecx = 0x9D0 + [r9+0x10] and 0x5ABA5C0 is called; the result moves to rsi.
0x66a7d11  lock inc dword ptr [rcx+8]
0x66a7d15  mov rcx,[rbp+0x530]
0x66a7d1c  jmp short 0x66A7D20
0x66a7d1e  xor ecx,ecx
0x66a7d20  mov rdx,[rbp+0x528]
0x66a7d27  mov [rbp+0x4D0],rdx
0x66a7d2e  mov [rbp+0x4D8],rcx
0x66a7d35  mov [rbp+0x4E0],al
0x66a7d3b  mov rax,[rbp+0x550]
0x66a7d42  mov [rbp+0x4F8],rax
0x66a7d49  movaps xmm0,[rbp+0x540]
0x66a7d50  movups [rbp+0x4E8],xmm0
0x66a7d57  mov ecx,0x9D0
0x66a7d5c  add rcx,[r9+0x10]
0x66a7d60  call 0x5ABA5C0
0x66a7d65  nop
0x66a7d66  mov rsi,rax

### Phase 5: 0x66a7d69..0x66a7ddf
rdx = rbp+0x4A8; xmm0 is zeroed and sixteen 16-byte stack slots [rbp+0x280..0x330] are cleared, then qword [rbp+0x340] = 0. rcx = rax + 0x780, 0x675F3B0 is called, and eax = [rsi+0x788] is loaded.
0x66a7d69  lea rdx,[rbp+0x4A8]
0x66a7d70  xorps xmm0,xmm0
0x66a7d73  movaps [rbp+0x330],xmm0
0x66a7d7a  movaps [rbp+0x320],xmm0
0x66a7d81  movaps [rbp+0x310],xmm0
0x66a7d88  movaps [rbp+0x300],xmm0
0x66a7d8f  movaps [rbp+0x2F0],xmm0
0x66a7d96  movaps [rbp+0x2E0],xmm0
0x66a7d9d  movaps [rbp+0x2D0],xmm0
0x66a7da4  movaps [rbp+0x2C0],xmm0
0x66a7dab  movaps [rbp+0x2B0],xmm0
0x66a7db2  movaps [rbp+0x2A0],xmm0
0x66a7db9  movaps [rbp+0x290],xmm0
0x66a7dc0  movaps [rbp+0x280],xmm0
0x66a7dc7  mov qword ptr [rbp+0x340],0
0x66a7dd2  lea rcx,[rax+0x780]
0x66a7dd9  call 0x675F3B0
0x66a7dde  nop
0x66a7ddf  mov eax,[rsi+0x788]

### Phase 6: 0x66a7de5..0x66a7e13
eax = ([rsi+0x788] - [rsi+0x780]) >> 3, imul 0xFFFF8BA3, dec, low word ax stored at [rbp+0x2A8]. The TLS/fiber chain [0x1233E1B0] -> [rax+0x10] is walked, dl = 0x4A, qword [0xF99FFA0] called, al stored at [rbp+0x580].
0x66a7de5  sub eax,[rsi+0x780]
0x66a7deb  shr eax,3
0x66a7dee  imul eax,0xFFFF8BA3
0x66a7df4  dec eax
0x66a7df6  mov [rbp+0x2A8],ax
0x66a7dfd  mov rcx,[0x1233E1B0]
0x66a7e04  mov rax,[rcx]
0x66a7e07  mov rax,[rax+0x10]
0x66a7e0b  mov dl,0x4A
0x66a7e0d  call qword ptr [0xF99FFA0]
0x66a7e13  nop

### Phase 7: 0x66a7e14..0x66a7e51
rdx = [rsi+0x8A8]; if rdx != [rsi+0x8B0], word [rbp+0x4A0] is zero-extended to ax, stored at [rdx], and qword [rsi+0x8A8] += 2; else 0x1EF6F90 is called with r8 = rbp+0x4A0, rcx = rsi+0x8A0.
0x66a7e14  mov [rbp+0x580],al
0x66a7e1a  mov rdx,[rsi+0x8A8]
0x66a7e21  cmp rdx,[rsi+0x8B0]
0x66a7e28  je short 0x66A7E3E
0x66a7e2a  movzx eax,word ptr [rbp+0x4A0]
0x66a7e31  mov [rdx],ax
0x66a7e34  add qword ptr [rsi+0x8A8],2
0x66a7e3c  jmp short 0x66A7E52
0x66a7e3e  lea r8,[rbp+0x4A0]
0x66a7e45  lea rcx,[rsi+0x8A0]
0x66a7e4c  call 0x1EF6F90
0x66a7e51  nop

### Phase 8: 0x66a7e52..0x66a7e9b
TLS chain walked again ([0x1233E1B0] -> [rax+0x10], dl = 0x4A, qword [0xF99FFA0] with edx = byte [rbp+0x580]); al stored back at [rbp+0x580]. eax = ([rsi+0x8A8] - [rsi+0x8A0]) >> 1, dec, ax stored at [rbp+0x290].
0x66a7e52  mov rcx,[0x1233E1B0]
0x66a7e59  mov rax,[rcx]
0x66a7e5c  mov rax,[rax+0x10]
0x66a7e60  movzx edx,byte ptr [rbp+0x580]
0x66a7e67  call qword ptr [0xF99FFA0]
0x66a7e6d  nop
0x66a7e6e  mov eax,[rsi+0x8A8]
0x66a7e74  sub eax,[rsi+0x8A0]
0x66a7e7a  shr eax,1
0x66a7e7c  dec eax
0x66a7e7e  mov [rbp+0x290],ax
0x66a7e85  mov rcx,[0x1233E1B0]
0x66a7e8c  mov rax,[rcx]
0x66a7e8f  mov rax,[rax+0x10]
0x66a7e93  mov dl,0x4A
0x66a7e95  call qword ptr [0xF99FFA0]
0x66a7e9b  mov [rbp+0x580],al

### Phase 9: 0x66a7ea1..0x66a7ed0
0x675FB30 is called with rdx = rbp+0x458, rcx = rsi+0x648; another TLS call (dl = 0x4A, edx = byte [rbp+0x580]) stores al at [rbp+0x580].
0x66a7ea1  lea rdx,[rbp+0x458]
0x66a7ea8  lea rcx,[rsi+0x648]
0x66a7eaf  call 0x675FB30
0x66a7eb4  nop
0x66a7eb5  mov rcx,[0x1233E1B0]
0x66a7ebc  mov rax,[rcx]
0x66a7ebf  mov rax,[rax+0x10]
0x66a7ec3  movzx edx,byte ptr [rbp+0x580]
0x66a7eca  call qword ptr [0xF99FFA0]
0x66a7ed0  nop

### Phase 10: 0x66a7ed1..0x66a7f11
qword [rbp+0x280] = 0x2001001; eax = ([rsi+0x650] - [rsi+0x648]) >> 3, imul 0xFFFF8E39, dec, ax stored at [rbp+0x2C2]; TLS call; al stored at [rbp+0x580].
0x66a7ed1  mov qword ptr [rbp+0x280],0x2001001
0x66a7edc  mov eax,[rsi+0x650]
0x66a7ee2  sub eax,[rsi+0x648]
0x66a7ee8  shr eax,3
0x66a7eeb  imul eax,0xFFFF8E39
0x66a7ef1  dec eax
0x66a7ef3  mov [rbp+0x2C2],ax
0x66a7efa  mov rcx,[0x1233E1B0]
0x66a7f01  mov rax,[rcx]
0x66a7f04  mov rax,[rax+0x10]
0x66a7f08  mov dl,0x4A
0x66a7f0a  call qword ptr [0xF99FFA0]
0x66a7f10  nop
0x66a7f11  mov [rbp+0x580],al

### Phase 11: 0x66a7f17..0x66a7f7a
rbx = [rsi+0x770]; if rbx != [rsi+0x778]: rax = [rbp+0x3D0] stored at [rbx], rcx = rbx+8, 0xE869FF0 called with rdx = rdi, [rbp+0x450] stored at [rbx+0x80] and [rbp+0x450] cleared, qword [rsi+0x770] += 0x88; else 0x6760710 called with r8 = rbp+0x3D0, rcx = rsi+0x768, rdx = rbx.
0x66a7f17  mov rbx,[rsi+0x770]
0x66a7f1e  cmp rbx,[rsi+0x778]
0x66a7f25  je short 0x66A7F64
0x66a7f27  mov rax,[rbp+0x3D0]
0x66a7f2e  mov [rbx],rax
0x66a7f31  lea rcx,[rbx+8]
0x66a7f35  mov rdx,rdi
0x66a7f38  call 0xE869FF0
0x66a7f3d  nop
0x66a7f3e  mov rax,[rbp+0x450]
0x66a7f45  mov [rbx+0x80],rax
0x66a7f4c  mov qword ptr [rbp+0x450],0
0x66a7f57  add qword ptr [rsi+0x770],0x88
0x66a7f62  jmp short 0x66A7F7B
0x66a7f64  lea r8,[rbp+0x3D0]
0x66a7f6b  lea rcx,[rsi+0x768]
0x66a7f72  mov rdx,rbx
0x66a7f75  call 0x6760710
0x66a7f7a  nop

### Phase 12: 0x66a7f7b..0x66a7fcb
TLS call (dl = 0x4A, edx = byte [rbp+0x580]); eax = ([rsi+0x770] - [rsi+0x768]) >> 3, imul 0xFFFFF0F1, dec, ax stored at [rbp+0x2AA]; another TLS call.
0x66a7f7b  mov rcx,[0x1233E1B0]
0x66a7f82  mov rax,[rcx]
0x66a7f85  mov rax,[rax+0x10]
0x66a7f89  movzx edx,byte ptr [rbp+0x580]
0x66a7f90  call qword ptr [0xF99FFA0]
0x66a7f96  nop
0x66a7f97  mov eax,[rsi+0x770]
0x66a7f9d  sub eax,[rsi+0x768]
0x66a7fa3  shr eax,3
0x66a7fa6  imul eax,0xFFFFF0F1
0x66a7fac  dec eax
0x66a7fae  mov [rbp+0x2AA],ax
0x66a7fb5  mov rcx,[0x1233E1B0]
0x66a7fbc  mov rax,[rcx]
0x66a7fbf  mov rax,[rax+0x10]
0x66a7fc3  mov dl,0x4A
0x66a7fc5  call qword ptr [0xF99FFA0]
0x66a7fcb  nop

### Phase 13: 0x66a7fcc..0x66a7ffa
al stored at [rbp+0x580]; rdx = [rsi+0x830]; if rdx != [rsi+0x838], rdx is incremented and stored back at [rsi+0x830]; else 0x6760E60 is called with rcx = rsi+0x828.
0x66a7fcc  mov [rbp+0x580],al
0x66a7fd2  mov rdx,[rsi+0x830]
0x66a7fd9  cmp rdx,[rsi+0x838]
0x66a7fe0  je short 0x66A7FEE
0x66a7fe2  inc rdx
0x66a7fe5  mov [rsi+0x830],rdx
0x66a7fec  jmp short 0x66A7FFB
0x66a7fee  lea rcx,[rsi+0x828]
0x66a7ff5  call 0x6760E60
0x66a7ffa  nop

### Phase 14: 0x66a7ffb..0x66a8030
TLS call; al stored at [rbp+0x580]; qword [rbp+0x280] = 0x2003021; eax = [rsi+0x828]; not eax; eax += [rsi+0x830]; ax stored at [rbp+0x29A].
0x66a7ffb  mov rcx,[0x1233E1B0]
0x66a8002  mov rax,[rcx]
0x66a8005  mov rax,[rax+0x10]
0x66a8009  movzx edx,byte ptr [rbp+0x580]
0x66a8010  call qword ptr [0xF99FFA0]
0x66a8016  nop
0x66a8017  mov qword ptr [rbp+0x280],0x2003021
0x66a8022  mov eax,[rsi+0x828]
0x66a8028  not eax
0x66a802a  add eax,[rsi+0x830]
0x66a8030  mov [rbp+0x29A],ax

### Phase 15: 0x66a8037..0x66a8062
TLS call; al stored at [rbp+0x580]; rdx = [rsi+0x680], compared with [rsi+0x688]; jumps to 0x66A8094 if equal.
0x66a8037  mov rcx,[0x1233E1B0]
0x66a803e  mov rax,[rcx]
0x66a8041  mov rax,[rax+0x10]
0x66a8045  mov dl,0x4A
0x66a8047  call qword ptr [0xF99FFA0]
0x66a804d  nop
0x66a804e  mov [rbp+0x580],al
0x66a8054  mov rdx,[rsi+0x680]
0x66a805b  cmp rdx,[rsi+0x688]
0x66a8062  je short 0x66A8094

### Phase 16: 0x66a8064..0x66a80a7
Not-equal path: movss chain stores [rbp+0x3BC] at [rdx], [rbp+0x3C0] at [rdx+4], [rbp+0x3C4] at [rdx+8]; qword [rsi+0x680] += 0xC. Equal path (0x66a8094): lea r8 = rbp+0x3BC, lea rcx = rsi+0x678, call 0x1770A70.
0x66a8064  movss xmm0,[rbp+0x3BC]
0x66a806c  movss [rdx],xmm0
0x66a8070  movss xmm0,[rbp+0x3C0]
0x66a8078  movss [rdx+4],xmm0
0x66a807d  movss xmm0,[rbp+0x3C4]
0x66a8085  movss [rdx+8],xmm0
0x66a808a  add qword ptr [rsi+0x680],0xC
0x66a8092  jmp short 0x66A80A8
0x66a8094  lea r8,[rbp+0x3BC]
0x66a809b  lea rcx,[rsi+0x678]
0x66a80a2  call 0x1770A70
0x66a80a7  nop

### Phase 17: 0x66a80a8..0x66a80d9
TLS call; al stored at [rbp+0x580]; eax = ([rsi+0x680] - [rsi+0x678]) >> 2, imul 0xFFFFAAAB, dec eax (slice ends at dec eax).
0x66a80a8  mov rcx,[0x1233E1B0]
0x66a80af  mov rax,[rcx]
0x66a80b2  mov rax,[rax+0x10]
0x66a80b6  movzx edx,byte ptr [rbp+0x580]
0x66a80bd  call qword ptr [0xF99FFA0]
0x66a80c3  nop
0x66a80c4  mov eax,[rsi+0x680]
0x66a80ca  sub eax,[rsi+0x678]
0x66a80d0  shr eax,2
0x66a80d3  imul eax,0xFFFFAAAB
0x66a80d9  dec eax

## [reg+off] field map — every load/store site in the slice

One row per distinct offset; all sites for that offset are listed verbatim. `lea`-only address computations are not loads/stores and are noted below the table. Direction: R = load, W = store. Size from the instruction. No field meaning is shown by any instruction or string in this slice, so meaning is `-` everywhere.

| offset | size | direction | sites (verbatim `0xRVA  instr`) | meaning |
| 0x158 | 8B | R | 0x66a7c0a  mov rax,[rbp+0x158] (R 8B) | - |
| 0x1D8 | 8B | R/W | 0x66a7c2b  mov rax,[rbp+0x1D8] (R 8B) ; 0x66a7c39  mov qword ptr [rbp+0x1D8],0 (W 8B) | - |
| 0x280 | 16B/8B/8B | W | 0x66a7dc0  movaps [rbp+0x280],xmm0 (W 16B) ; 0x66a7ed1  mov qword ptr [rbp+0x280],0x2001001 (W 8B) ; 0x66a8017  mov qword ptr [rbp+0x280],0x2003021 (W 8B) | - |
| 0x290 | 16B/2B | W | 0x66a7db9  movaps [rbp+0x290],xmm0 (W 16B) ; 0x66a7e7e  mov [rbp+0x290],ax (W 2B) | - |
| 0x29A | 2B | W | 0x66a8030  mov [rbp+0x29A],ax (W 2B) | - |
| 0x2A0 | 16B | W | 0x66a7db2  movaps [rbp+0x2A0],xmm0 (W 16B) | - |
| 0x2A8 | 2B | W | 0x66a7df6  mov [rbp+0x2A8],ax (W 2B) | - |
| 0x2B0 | 16B | W | 0x66a7dab  movaps [rbp+0x2B0],xmm0 (W 16B) | - |
| 0x2C0 | 16B | W | 0x66a7da4  movaps [rbp+0x2C0],xmm0 (W 16B) | - |
| 0x2C2 | 2B | W | 0x66a7ef3  mov [rbp+0x2C2],ax (W 2B) | - |
| 0x2D0 | 16B | W | 0x66a7d9d  movaps [rbp+0x2D0],xmm0 (W 16B) | - |
| 0x2E0 | 16B | W | 0x66a7d96  movaps [rbp+0x2E0],xmm0 (W 16B) | - |
| 0x2F0 | 16B | W | 0x66a7d8f  movaps [rbp+0x2F0],xmm0 (W 16B) | - |
| 0x300 | 16B | W | 0x66a7d88  movaps [rbp+0x300],xmm0 (W 16B) | - |
| 0x310 | 16B | W | 0x66a7d81  movaps [rbp+0x310],xmm0 (W 16B) | - |
| 0x320 | 16B | W | 0x66a7d7a  movaps [rbp+0x320],xmm0 (W 16B) | - |
| 0x330 | 16B | W | 0x66a7d73  movaps [rbp+0x330],xmm0 (W 16B) | - |
| 0x340 | 8B | W | 0x66a7dc7  mov qword ptr [rbp+0x340],0 (W 8B) | - |
| 0x388 | 16B | W | 0x66a7ba1  movups [rbp+0x388],xmm10 (W 16B) | - |
| 0x398 | 1B | W | 0x66a7ba9  mov byte ptr [rbp+0x398],3 (W 1B) | - |
| 0x39C | 8B | W | 0x66a7bb0  mov qword ptr [rbp+0x39C],0 (W 8B) | - |
| 0x3A4 | 4B | W | 0x66a7bbb  mov dword ptr [rbp+0x3A4],0 (W 4B) | - |
| 0x3A8 | 1B | W | 0x66a7bc5  mov byte ptr [rbp+0x3A8],3 (W 1B) | - |
| 0x3AC | 8B | W | 0x66a7bcc  mov qword ptr [rbp+0x3AC],0 (W 8B) | - |
| 0x3B4 | 4B | W | 0x66a7bd7  mov dword ptr [rbp+0x3B4],0 (W 4B) | - |
| 0x3B8 | 2B | W | 0x66a7be1  mov word ptr [rbp+0x3B8],0x101 (W 2B) | - |
| 0x3BA | 1B | W | 0x66a7bea  mov byte ptr [rbp+0x3BA],0xFF (W 1B) | - |
| 0x3BC | 4B/8B | R/W | 0x66a8064  movss xmm0,[rbp+0x3BC] (R 4B) ; 0x66a7bf1  movlps [rbp+0x3BC],xmm9 (W 8B) | - |
| 0x3C0 | 4B | R | 0x66a8070  movss xmm0,[rbp+0x3C0] (R 4B) | - |
| 0x3C4 | 4B | R/W | 0x66a7c02  movss [rbp+0x3C4],xmm0 (W 4B) ; 0x66a807d  movss xmm0,[rbp+0x3C4] (R 4B) | - |
| 0x3D0 | 8B | R/W | 0x66a7c11  mov [rbp+0x3D0],rax (W 8B) ; 0x66a7f27  mov rax,[rbp+0x3D0] (R 8B) | - |
| 0x450 | 8B | W/R/W | 0x66a7c32  mov [rbp+0x450],rax (W 8B) ; 0x66a7f3e  mov rax,[rbp+0x450] (R 8B) ; 0x66a7f4c  mov qword ptr [rbp+0x450],0 (W 8B) | - |
| 0x458 | 16B | W | 0x66a7c44  movups [rbp+0x458],xmm6 (W 16B) | - |
| 0x468 | 16B | W | 0x66a7c4b  movups [rbp+0x468],xmm7 (W 16B) | - |
| 0x478 | 16B | W | 0x66a7c52  movups [rbp+0x478],xmm8 (W 16B) | - |
| 0x488 | 16B | W | 0x66a7c5a  movups [rbp+0x488],xmm9 (W 16B) | - |
| 0x498 | 1B | W | 0x66a7c62  mov byte ptr [rbp+0x498],0 (W 1B) | - |
| 0x4A0 | 2B | W/R | 0x66a7c69  mov [rbp+0x4A0],si (W 2B) ; 0x66a7e2a  movzx eax,word ptr [rbp+0x4A0] (R 2B) | - |
| 0x4A8 | 16B | W | 0x66a7c89  movups [rbp+0x4A8],xmm0 (W 16B) | - |
| 0x4B8 | 16B | W | 0x66a7c98  movups [rbp+0x4B8],xmm1 (W 16B) | - |
| 0x4C8 | 8B | W | 0x66a7ca6  mov [rbp+0x4C8],rax (W 8B) | - |
| 0x4D0 | 8B | W | 0x66a7ce7  mov [rbp+0x4D0],rcx (W 8B) ; 0x66a7d27  mov [rbp+0x4D0],rdx (W 8B) | - |
| 0x4D8 | 8B | W | 0x66a7d2e  mov [rbp+0x4D8],rcx (W 8B) | - |
| 0x4E0 | 1B | W | 0x66a7cad  mov byte ptr [rbp+0x4E0],0xFF (W 1B) ; 0x66a7d35  mov [rbp+0x4E0],al (W 1B) | - |
| 0x4E8 | 16B | W | 0x66a7d50  movups [rbp+0x4E8],xmm0 (W 16B) | - |
| 0x4F8 | 8B | W | 0x66a7d42  mov [rbp+0x4F8],rax (W 8B) | - |
| 0x500 | 16B | R | 0x66a7c70  movaps xmm0,[rbp+0x500] (R 16B) | - |
| 0x508 | 8B | W | 0x66a7c7e  mov qword ptr [rbp+0x508],0 (W 8B) | - |
| 0x510 | 16B | R/W | 0x66a7c77  movaps xmm1,[rbp+0x510] (R 16B) ; 0x66a7c90  movaps [rbp+0x510],xmm10 (W 16B) | - |
| 0x520 | 8B | R | 0x66a7c9f  mov rax,[rbp+0x520] (R 8B) | - |
| 0x528 | 8B | R | 0x66a7ce0  mov rcx,[rbp+0x528] (R 8B) ; 0x66a7d20  mov rdx,[rbp+0x528] (R 8B) | - |
| 0x530 | 8B | R | 0x66a7d05  mov rcx,[rbp+0x530] (R 8B) | - |
| 0x538 | 1B | R | 0x66a7cb4  movzx eax,byte ptr [rbp+0x538] (R 1B) | - |
| 0x540 | 16B | R | 0x66a7d49  movaps xmm0,[rbp+0x540] (R 16B) | - |
| 0x550 | 8B | R | 0x66a7d3b  mov rax,[rbp+0x550] (R 8B) | - |
| 0x578 | 8B | R | 0x66a7cbf  mov r9,[rbp+0x578] (R 8B) | - |
| 0x580 | 1B | R/W | 0x66a7e14  mov [rbp+0x580],al (W 1B) ; 0x66a7e60  movzx edx,byte ptr [rbp+0x580] (R 1B) ; 0x66a7e9b  mov [rbp+0x580],al (W 1B) ; 0x66a7ec3  movzx edx,byte ptr [rbp+0x580] (R 1B) ; 0x66a7f11  mov [rbp+0x580],al (W 1B) ; 0x66a7f89  movzx edx,byte ptr [rbp+0x580] (R 1B) ; 0x66a7fcc  mov [rbp+0x580],al (W 1B) ; 0x66a8009  movzx edx,byte ptr [rbp+0x580] (R 1B) ; 0x66a804e  mov [rbp+0x580],al (W 1B) ; 0x66a80b6  movzx edx,byte ptr [rbp+0x580] (R 1B) | - |
| rcx+8 | 4B | W | 0x66a7d11  lock inc dword ptr [rcx+8] (W 4B) | - |
| r9+0x10 | 8B | R | 0x66a7d5c  add rcx,[r9+0x10] (R 8B) | - |
| rdx+0x0 | 16B/2B/4B | R/W | 0x66a7cf7  movups xmm0,[rdx] (R 16B) ; 0x66a7e31  mov [rdx],ax (W 2B) ; 0x66a806c  movss [rdx],xmm0 (W 4B) | - |
| rcx+0x0 | 16B | W | 0x66a7cfa  movups [rcx],xmm0 (W 16B) ; 0x66a7d02  movups [rcx],xmm0 (W 16B) | - |
| rbx+0x0 | 8B | W | 0x66a7f2e  mov [rbx],rax (W 8B) | - |
| rbx+0x80 | 8B | W | 0x66a7f45  mov [rbx+0x80],rax (W 8B) | - |
| rdx+4 | 4B | W | 0x66a8078  movss [rdx+4],xmm0 (W 4B) | - |
| rdx+8 | 4B | W | 0x66a8085  movss [rdx+8],xmm0 (W 4B) | - |
| rsi+0x648 | 4B | R | 0x66a7ee2  sub eax,[rsi+0x648] (R 4B) | - |
| rsi+0x650 | 4B | R | 0x66a7edc  mov eax,[rsi+0x650] (R 4B) | - |
| rsi+0x678 | 4B | R | 0x66a80ca  sub eax,[rsi+0x678] (R 4B) | - |
| rsi+0x680 | 8B/8B/4B | R/W/R | 0x66a8054  mov rdx,[rsi+0x680] (R 8B) ; 0x66a808a  add qword ptr [rsi+0x680],0xC (W 8B) ; 0x66a80c4  mov eax,[rsi+0x680] (R 4B) | - |
| rsi+0x688 | 8B | R | 0x66a805b  cmp rdx,[rsi+0x688] (R 8B) | - |
| rsi+0x768 | 4B | R | 0x66a7f9d  sub eax,[rsi+0x768] (R 4B) | - |
| rsi+0x770 | 8B/8B/4B | R/W/R | 0x66a7f17  mov rbx,[rsi+0x770] (R 8B) ; 0x66a7f57  add qword ptr [rsi+0x770],0x88 (W 8B) ; 0x66a7f97  mov eax,[rsi+0x770] (R 4B) | - |
| rsi+0x778 | 8B | R | 0x66a7f1e  cmp rbx,[rsi+0x778] (R 8B) | - |
| rsi+0x780 | 4B | R | 0x66a7de5  sub eax,[rsi+0x780] (R 4B) | - |
| rsi+0x788 | 4B | R | 0x66a7ddf  mov eax,[rsi+0x788] (R 4B) | - |
| rsi+0x828 | 4B | R | 0x66a8022  mov eax,[rsi+0x828] (R 4B) | - |
| rsi+0x830 | 8B/8B/4B | R/W/R | 0x66a7fd2  mov rdx,[rsi+0x830] (R 8B) ; 0x66a7fe5  mov [rsi+0x830],rdx (W 8B) ; 0x66a802a  add eax,[rsi+0x830] (R 4B) | - |
| rsi+0x838 | 8B | R | 0x66a7fd9  cmp rdx,[rsi+0x838] (R 8B) | - |
| rsi+0x8A0 | 4B | R | 0x66a7e74  sub eax,[rsi+0x8A0] (R 4B) | - |
| rsi+0x8A8 | 8B/8B/4B | R/W/R | 0x66a7e1a  mov rdx,[rsi+0x8A8] (R 8B) ; 0x66a7e34  add qword ptr [rsi+0x8A8],2 (W 8B) ; 0x66a7e6e  mov eax,[rsi+0x8A8] (R 4B) | - |
| rsi+0x8B0 | 8B | R | 0x66a7e21  cmp rdx,[rsi+0x8B0] (R 8B) | - |

lea-only (address computed, not loaded/stored in this slice): [rbp+0x3D8] at 0x66a7c18; [rbp+0x4A8] at 0x66a7d69; [rbp+0x528] at 0x66a7cf0; [rbp+0x4A0] at 0x66a7e3e; [rbp+0x458] at 0x66a7ea1; [rbp+0x3BC] at 0x66a8094.

All 250 instructions of 0x66a7ba1..0x66a80d9 are covered by phases 1-17; no instruction is skipped.

## TOOL REQUESTS
None | - | -
