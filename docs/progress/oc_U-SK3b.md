# U-SK3b: fixups for docs/progress/oc_U-SK3.md (1.26.62.01)

## NEXT
Nothing — unit complete. File written: docs/progress/oc_U-SK3b.md only. oc_U-SK3.md NOT edited (per instructions).

## Notes
All RVAs checked against the exe with rdis (dis from a verified boundary ~8+ instructions earlier). Static analysis only; exe = Minecraft.Windows 1.26.62.01. Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown.

Key finding: several blocks in oc_U-SK3.md were disassembled starting at mid-instruction RVAs, so their quoted lines are fabrications of the misaligned decoder (the bytes get re-synchronized into different mnemonics). The real instruction boundary is ~1-3 bytes earlier, and the real flow contains `je`/`call` control flow that the misaligned listing skipped. Each neighborhood below gives exact rdis lines from a verified boundary, then interpretation.

## Phase 48 — Tail 0x6657da4..0x6657e4a (epilogue release loop + heap check) [V]
Exact rdis lines from `dis 0x6657da4 55` (0x6657da4 is a verified boundary: fall-through of `jmp 0x6657C80` at 0x6657d9f):
```
6657da4  mov r14,[rsi+0x540]
6657dab  test r14,r14
6657dae  mov r13,[rbp-0x28]
6657db2  je 0x6657E52
6657db8  mov rdi,[rsi+0x548]
6657dbf  cmp r14,rdi
6657dc2  jne short 0x6657DDC
6657dc4  jmp short 0x6657E1B
6657dc6  nop [rax+rax]
6657dd0  add r14,0x130
6657dd7  cmp r14,rdi
6657dda  je short 0x6657E14
6657ddc  mov r15,[r14+0x38]
6657de0  test r15,r15
6657de3  je short 0x6657DD0
6657de5  lock dec dword ptr [r15+8]
6657dea  jne short 0x6657DD0
6657dec  mov rax,[r15]
6657def  mov rax,[rax]
6657df2  mov rcx,r15
6657df5  call qword ptr [0xF99FFA0]   ; sub_eea6040
6657dfb  lock dec dword ptr [r15+0xC]
6657e00  jne short 0x6657DD0
6657e02  mov rax,[r15]
6657e05  mov rax,[rax+8]
6657e09  mov rcx,r15
6657e0c  call qword ptr [0xF99FFA0]   ; sub_eea6040
6657e12  jmp short 0x6657DD0
6657e14  mov r14,[rsi+0x540]
6657e1b  mov rdx,[rsi+0x550]
6657e22  sub rdx,r14
6657e25  cmp rdx,0x1000
6657e2c  jb short 0x6657E4A
6657e2e  mov rax,[r14-8]
6657e32  add r14,0xFFFFFFFFFFFFFFF8
6657e36  sub r14,rax
6657e39  cmp r14,0x20
6657e3d  jae 0x665D43A
6657e43  add rdx,0x27
6657e47  mov r14,rax
6657e4a  mov rcx,r14
6657e4d  call 0xE935700   ; sub_e935700
```
// [V] 0x6657da4..0x6657e4a: epilogue release loop. r14=[rsi+0x540] = stride-0x130 table base; r13=[rbp-0x28]; if r14==0 → loc_6657E52 (skip release). rdi=[rsi+0x548] = table end cursor. Loop loc_6657ddc..loc_6657dd0: r15=[r14+0x38] (entry's +0x38 ref pointer); if r15==0 → advance r14+=0x130; lock dec dword ptr [r15+8]; if !=0 → advance; else two-stage destroy: call sub_eea6040 (stage-1); lock dec dword ptr [r15+0xC]; if !=0 → advance; call sub_eea6040 (stage-2/free). Loop until r14==rdi → loc_6657e14 (r14 re-based to [rsi+0x540]). [V] 0x6657e1b..0x6657e4d: rdx=[rsi+0x550]-[rsi+0x540] (allocated size); if rdx<0x1000 → loc_6657e4a; else rax=[r14-8] (heap size header); r14 = (r14-8)-rax; if r14>=0x20 → sub_665d43a (heap-consistency check); rdx+=0x27; r14=rax; rcx=r14; call sub_e935700 [I] free(final buffer). loc_6657e4a ends exactly at `mov rcx,r14` / `call sub_e935700`. [I] Releases every AddRef taken by the case ([r12+8]@0x665714e, entry +0x38 refs in loops) then frees the buffer — final case wind-down.

## Bad-RVA neighborhoods — exact real lines from verified boundaries

### 0x6656b81 (quoted: `6656b81 mov ecx,[rax+8]`) — MID-INSTRUCTION [V]
From `dis 0x6656b79 14` (0x6656b79 `mov rax,[rbp+0x330]` is 7 bytes → real boundary 0x6656b80):
```
6656b79  mov rax,[rbp+0x330]
6656b80  mov rcx,[rax+8]
6656b84  test rcx,rcx
6656b87  je 0x6657444
6656b8d  lock inc dword ptr [rcx+8]
6656b91  mov rcx,[rax]
6656b94  mov rbx,[rax+8]
6656b98  mov rax,[rcx+0x18]
6656b9c  mov r14,[rax]
6656b9f  test rbx,rbx
6656ba2  je 0x665744E
6656ba8  lock dec dword ptr [rbx+8]
6656bac  jne 0x665744E
6656bb2  mov rax,[rbx]
6656bb5  mov rax,[rax]
6656bb8  mov rcx,rbx
6656bbb  call qword ptr [0xF99FFA0]
6656bc1  lock dec dword ptr [rbx+0xC]
6656bc5  jne 0x665744E
6656bcb  mov rax,[rbx]
6656bce  mov rax,[rax+8]
6656bd2  mov rcx,rbx
6656bd5  call qword ptr [0xF99FFA0]
6656bdb  jmp 0x665744E
```
// [V] 0x6656b81 is byte 1 of `mov rcx,[rax+8]` at 0x6656b80 — NOT a real boundary. Real line: `6656b80 mov rcx,[rax+8]` (4 bytes, ends 0x6656b84), then `6656b84 test rcx,rcx`, `6656b87 je 0x6657444`. The file's `6656b81 mov ecx,[rax+8]` is a 1-byte-off misaligned re-decode (wrong width `ecx`, wrong RVA). Rest of the block matches the file's listing except RVAs shifted by +1. This is the LegacyCubemap object release (VolumetricFog phase 24 Block A), tailing into SkyAmbientSamples loc_6657444/loc_665744E.

### 0x6656d0a / 0x6656d0d / 0x6656d0f (quoted: `test byte ptr [rdi],0x84` / `fisttp qword ptr [rax],st` / `add [rax],al`) — ALL MID-INSTRUCTION [V]
From `dis 0x6656d05 10` (0x6656d05 `mov r15,[rax]` is verified boundary):
```
6656d05  mov r15,[rax]
6656d08  test r14,r14
6656d0b  je 0x66575EE
6656d11  lock dec dword ptr [r14+8]
6656d16  jne 0x66575EE
6656d1c  mov rax,[r14]
6656d1f  mov rax,[rax]
6656d22  mov rcx,r14
6656d25  call qword ptr [0xF99FFA0]
6656d2b  lock dec dword ptr [r14+0xC]
6656d30  jne 0x66575EE
6656d36  mov rax,[r14]
6656d39  mov rax,[rax+8]
6656d3d  mov rcx,r14
6656d40  call qword ptr [0xF99FFA0]
6656d46  jmp 0x66575EE
6656d4b  xor eax,eax
6656d4d  mov rcx,[rdi+0xD8]
6656d54  mov [rbp+0x210],rcx
6656d5b  mov [rbp+0x218],rax
```
```
// [V] 0x6656d08 `test r14,r14` is 3 bytes (ends 0x6656d0b); 0x6656d0b `je 0x66575EE` is 6 bytes (ends 0x6656d11). So 0x6656d0a (last byte of test), 0x6656d0d/0x6656d0f (inside the je displacement) are NOT real boundaries. Real lines: `6656d08 test r14,r14`, `6656d0b je 0x66575EE`, then `6656d11 lock dec dword ptr [r14+8]`. The file's `test byte ptr [rdi],0x84` / `fisttp qword ptr [rax],st` / `add [rax],al` at 0x6656d0a/0x6656d0d/0x6656d0f are misdecodes of those bytes. The missing `je 0x66575EE` is the refcount-still-alive short-circuit (identical to SkyAmbientSamples phase-9 Block L tail). This is VolumetricFog phase 26 Block A release, tailing into loc_66575EE.
```

### 0x6656f06 (quoted: `6656f06 adc [rbp+0x368],ebx`) — MID-INSTRUCTION [V]
From `dis 0x6656ee2 50` (0x6656ee2 `movaps xmm1,[rbp+0x1E0]` verified boundary):
```
6656ef7  movups [rbp+0x348],xmm1
6656efe  movups [rbp+0x358],xmm2
6656f05  movups [rbp+0x368],xmm3
6656f0c  movups [rbp+0x378],xmm0
6656f13  test rax,rax
6656f16  mov [rbp+0x1C8],r9w
6656f1e  je short 0x6656F2D
6656f20  lock inc dword ptr [rax+8]
6656f24  mov r14,[rbp+0x218]
6656f2b  jmp short 0x6656F30
6656f2d  xor r14d,r14d
6656f30  mov rdi,[rbp+0x210]
```
```
// [V] movups instructions here are 7 bytes each: 0x6656ef7→0x6656efe→0x6656f05→0x6656f0c→0x6656f13. So 0x6656f06 is byte 1 of `movups [rbp+0x368],xmm3` at 0x6656f05 — NOT a real boundary. Real lines: `6656f05 movups [rbp+0x368],xmm3`, `6656f0c movups [rbp+0x378],xmm0`, `6656f13 test rax,rax`. The file's `6656f06 adc [rbp+0x368],ebx` is a misaligned re-decode (fabricated). The file's phase 28 also dropped 0x6656f05 entirely. This is the VolumetricFog record-template build (phase 28): store fog param fields [rbp+0x348..0x378] from xmm1/xmm2/xmm3/xmm0.
```

### 0x6656fef (quoted: `6656fef adc [rbp+0xA8],eax`) — MID-INSTRUCTION [V]
From `dis 0x6656fb8 22` (0x6656fb8 `call 0x5ABA5C0` verified boundary):
```
6656fb8  call 0x5ABA5C0
6656fbd  nop
6656fbe  mov rsi,rax
6656fc1  xorps xmm0,xmm0
6656fc4  movups [rbp+0x108],xmm0
6656fcb  movups [rbp+0xF8],xmm0
6656fd2  movups [rbp+0xE8],xmm0
6656fd9  movups [rbp+0xD8],xmm0
6656fe0  movups [rbp+0xC8],xmm0
6656fe7  movups [rbp+0xB8],xmm0
6656fee  movups [rbp+0xA8],xmm0
6656ff5  movups [rbp+0x98],xmm0
6656ffc  movups [rbp+0x88],xmm0
6657003  movups [rbp+0x78],xmm0
6657007  movups [rbp+0x68],xmm0
665700b  movups [rbp+0x58],xmm0
665700f  mov rcx,[0x1233E1B0]
6657016  mov rax,[rcx]
6657019  mov rax,[rax+0x10]
665701d  mov dl,0x4A
665701f  call qword ptr [0xF99FFA0]
6657025  nop
```
```
// [V] movups are 7 bytes: 0x6656fe7→0x6656fee→0x6656ff5→...→0x665700b→0x665700f. So 0x6656fef is byte 1 of `movups [rbp+0xA8],xmm0` at 0x6656fee — NOT a real boundary. Real lines: `6656fee movups [rbp+0xA8],xmm0`, `6656ff5 movups [rbp+0x98],xmm0`, ... The file's `6656fef adc [rbp+0xA8],eax` is a misaligned re-decode (fabricated). The file's phase 29 dropped 0x6656fee and started at 0x6656fef. These are the final zero-init movups of the second buffer scratch ([rbp+0x108..0x58]) then the dl=0x4A global count call — exactly like SkyAmbientSamples phase 1.
```

### 0x665721c / 0x665721f / 0x6657222 (quoted: `ror byte ptr [rdi],0x84` / `mov bl,[rdi]` / `add [rcx+rcx*4-8],cl`) — ALL MID-INSTRUCTION [V]
From `dis 0x665721a 8` (0x665721a `test rax,rax` verified boundary, 3 bytes → 0x665721d):
```
665721a  test rax,rax
665721d  je 0x665D1AD
6657223  mov rax,r15
6657226  add r15,0x27
665722a  and r15,0xFFFFFFFFFFFFFFE0
665722e  mov [r15-8],rax
6657232  jmp 0x665769C
6657237  mov rax,r15
665723a  sub rax,[rsi+0x540]
6657241  mov [rbp+0x540],rax
6657248  sar rax,4
665724c  mov rcx,0x86BCA1AF286BCA1B
```
```
// [V] 0x665721c is the last byte of `test rax,rax` (0x665721a..0x665721d); 0x665721f/0x6657222 are inside the `je 0x665D1AD` displacement (0x665721d..0x6657223). NONE of 0x665721c/0x665721f/0x6657222 are real boundaries. Real lines: `665721a test rax,rax`, `665721d je 0x665D1AD`, `6657223 mov rax,r15`, `6657226 add r15,0x27`, ... The file's phase-3 Block A (`ror byte ptr [rdi],0x84` / `mov bl,[rdi]` / `add [rcx+rcx*4-8],cl`) is entirely fabricated from a misaligned decode starting at 0x665721c — those instructions do not exist here. The real code is a hash-fail branch `je sub_665d1ad` followed by the 32-byte-aligned bucket insert (`movups`-free: r15+=0x27, align down 32, [r15-8]=rax) then jmp loc_665769C. This affects SkyAmbientSamples phase 3 Block A and VolumetricFog phase 31 (the mirrored block).
```

### 0x6657387 (quoted: `6657387 lea edx,[rax+0x27]`) — OFF BY ONE [V]
From `dis 0x665737f 6` (0x665737f `mov rax,[rbp+0x540]` verified boundary, 7 bytes → 0x6657386):
```
665737f  mov rax,[rbp+0x540]
6657386  lea edx,[rax+0x27]
665738a  mov rcx,[0x1233E1A8]
6657391  mov rax,[rcx]
6657394  mov rax,[rax+8]
6657398  mov [rbp+0x48],rdx
665739c  call qword ptr [0xF99FFA0]
66573a2  nop
66573a3  mov rbx,rax
66573a6  test rax,rax
66573a9  je 0x665D1CB
```
```
// [V] 0x6657386 `lea edx,[rax+0x27]` is 4 bytes (ends 0x665738a). So 0x6657387 is byte 1 — NOT a real boundary. Real line: `6657386 lea edx,[rax+0x27]`, then `665738a mov rcx,[0x1233E1A8]`. The file's `6657387 lea edx,[rax+0x27]` is off-by-one in the RVA label (the instruction mnemonic is right, the address is wrong). This is the empty-list index path's second hash call (SkyAmbientSamples phase 5 Block E tail / VolumetricFog phase 34).
```

### 0x665746c (quoted: `665746c mov ecx,[rax+8]`) — OFF BY ONE [V]
From `dis 0x665746b 4` (0x665746b `mov rcx,[rax+8]` verified boundary):
```
665746b  mov rcx,[rax+8]
665746f  test rcx,rcx
6657472  je 0x6658355
6657478  lock inc dword ptr [rcx+8]
```
```
// [V] 0x665746b `mov rcx,[rax+8]` is 4 bytes (ends 0x665746f). So 0x665746c is byte 1 — NOT a real boundary. Real line: `665746b mov rcx,[rax+8]` (note rcx not ecx), then `665746f test rcx,rcx`, `6657472 je 0x6658355`. The file's `665746c mov ecx,[rax+8]` is off-by-one (wrong width `ecx`, wrong RVA). This is SkyAmbientSamples phase 6 Block H / VolumetricFog phase 35 release Block H (AddRef [rcx+8]).
```

### 0x66574f6 (quoted: `66574f6 mov ecx,[rax+8]`) — OFF BY ONE [V]
From `dis 0x66574f5 4` (0x66574f5 `mov rcx,[rax+8]` verified boundary):
```
66574f5  mov rcx,[rax+8]
66574f9  test rcx,rcx
66574fc  je 0x6658445
6657502  lock inc dword ptr [rcx+8]
```
```
// [V] 0x66574f5 `mov rcx,[rax+8]` is 4 bytes (ends 0x66574f9). So 0x66574f6 is byte 1 — NOT a real boundary. Real line: `66574f5 mov rcx,[rax+8]`, then `66574f9 test rcx,rcx`, `66574fc je 0x6658445`. The file's `66574f6 mov ecx,[rax+8]` is off-by-one. This is SkyAmbientSamples phase 7 Block J / VolumetricFog phase 35 release (second object AddRef).
```

## Additional misdecodes found in the same neighborhoods [V]
These also appear in oc_U-SK3.md as quoted lines but are mid-instruction bytes of real control-flow instructions; exact real lines confirmed by rdis:

- `6656fec add [rax],al` — byte 1 of `movups [rbp+0xA8],xmm0` at 0x6656fee (see 0x6656fef neighborhood above).
- `66575a6 (bad)` / `66575a8 add [rax],al` — bytes of `je 0x66585C9` at 0x66575a4 (6 bytes, ends 0x66575aa); real flow resumes `66575aa lock dec dword ptr [r14+8]`. (SkyAmbientSamples phase 8 / VolumetricFog phase 36.)
- `665751c cmp cl,[rdi]` / `665751e add [rax],al` — bytes of `je 0x665845A` at 0x665751a (6 bytes, ends 0x6657520); real flow resumes `6657520 lock dec dword ptr [rbx+8]`. (SkyAmbientSamples phase 8 / VolumetricFog phase 36.)
- `66575c8 or al,0xF` / `66575ca test edx,edi` / `66575cc sldt [rax]` — bytes spanning `lock dec dword ptr [r14+0xC]` (0x66575c4, 6 bytes) / `je 0x66585C9` (0x66575c9); real flow resumes `66575cf mov rax,[r14]` / stage-2 destroy. (SkyAmbientSamples phase 9 / VolumetricFog phase 37.)
- `6657afe or cl,ch` / `6657b00 fdiv st(6),st` / `6657b02 (bad)` — bytes of `jmp 0x66579E0` at 0x6657aff (5 bytes, ends 0x6657b04); real flow resumes `6657b04 mov rdi,[rsi+0x548]`. (SkyAmbientSamples phase 15 / VolumetricFog phase 44.)
- `6657bdc loopne 0x6657BD0` / `6657bde xchg [rax],cl` — displacement bytes of `call 0xEEC6EC0` at 0x6657bdb (5 bytes, ends 0x6657be0); real flow resumes `6657be0 movss xmm0,[r13+0x120]`. (SkyAmbientSamples phase 16 / VolumetricFog phase 45.)

RVAs confirmed as REAL (match the file's quoted lines exactly): none of the listed 0x6656b81/0x6656d0a/0x6656d0d/0x6656d0f/0x6656f06/0x6656fef/0x665721c/0x665721f/0x6657222/0x6657387/0x665746c/0x66574f6 are real boundaries — every one is mid-instruction or off-by-one, as verified above.

## Files created
- docs/progress/oc_U-SK3b.md (this file only; oc_U-SK3.md not edited per instructions).
