# Progress: U-SK2 sky visitor 0x66560f0 — Cubemap case @0x6659615 + EndSky/LegacyCubemap 0x6656b2b..0x6656d4d

## NEXT
Resume Cubemap case phase 7 at 0x6659a75 (phase C6 decoded below; case end NOT yet located — keep disassembling linearly until an exit to shared SKY-PUSH tail ~0x665a8e5 or epilogue 0x665d11d/0x665d124 is found). EndSky/LegacyCubemap 0x6656b2b..0x6656d4d is COMPLETE (phases E1-E4 below). Context: docs/functions/ext_particle_sky_callees.md, docs/progress/ext-particle-sky.md. All RVAs relative to image base; exe = Minecraft.Windows 1.26.62.01. Tags: [V]=seen in disassembly, [I]=inferred, [?]=unknown.

## Method
- `rdis ... dis <rva> <n>` linear disassembly; each phase <= 40 instructions; every instruction quoted exactly as rdis prints it (`0xRVA  mnemonic operands`, no annotation comments); interpretation on separate `//` lines after each fence. Instruction-complete: no instruction in a phase range is skipped.

## Phase C1 — Cubemap case entry 0x6659615..0x66596d5 (40 instr) [V]
```
0x6659615  mov rax,[r14]
0x6659618  mov rax,[rax+0x18]
0x665961c  mov r15,[rax]
0x665961f  test r15,r15
0x6659622  je 0x665D11D
0x6659628  mov r15,[rsi]
0x665962b  mov rax,[rbp+0x330]
0x6659632  xorps xmm0,xmm0
0x6659635  movaps [rbp+0x340],xmm0
0x665963c  mov rcx,[rax+8]
0x6659640  test rcx,rcx
0x6659643  je 0x665A0BA
0x6659649  lock inc dword ptr [rcx+8]
0x665964d  mov r14,[rbp+0x348]
0x6659654  movups xmm0,[rax]
0x6659657  movaps [rbp+0x340],xmm0
0x665965e  test r14,r14
0x6659661  je 0x665A0CF
0x6659667  lock dec dword ptr [r14+8]
0x665966c  jne 0x665A0CF
0x6659672  mov rax,[r14]
0x6659675  mov rax,[rax]
0x6659678  mov rcx,r14
0x665967b  call qword ptr [0xF99FFA0]
0x6659681  lock dec dword ptr [r14+0xC]
0x6659686  jne 0x665A0CF
0x665968c  mov rax,[r14]
0x665968f  mov rax,[rax+8]
0x6659693  mov rcx,r14
0x6659696  call qword ptr [0xF99FFA0]
0x665969c  jmp 0x665A0CF
0x66596a1  mov rax,[rax]
0x66596a4  mov [rbp+0x340],rax
0x66596ab  mov qword ptr [rbp+0x348],0
0x66596b6  mov rax,[rbp+0x340]
0x66596bd  mov rax,[rax+0x18]
0x66596c1  mov rax,[rax]
0x66596c4  mov [rbp+0x1E0],rax
0x66596cb  lea r14,[rbp+0x1E8]
0x66596d2  mov r8,[r15]
```
// INTERPRETATION [V]: Cubemap case prologue. Loads owner chain r14->[0x18]->[0] into r15; null test branches to epilogue/cold 0x665d11d [V]. r15 reset to [rsi]. Zeroes 16 bytes at rbp+0x340 [V]. Refcount retain/release on a shared_ptr: lock inc [rcx+8] (retain new owner); lock dec [r14+8] then, when strong hits 0, destroy control block via call [0xF99FFA0]=sub_eea6040; lock dec [r14+0xC] (weak) and destroy again — classic ID-SP shared_ptr assign idiom [I, cf. ext_particle_sky_callees.md]. Exits jump to shared paths 0x665a0ba / 0x665a0cf [V]. Fall-through block at 0x66596a1 captures mesh header pointer ([rax][0x18][0] -> rbp+0x1E0), lea r14=[rbp+0x1E8], r8=[r15] [V].

## Phase C2 — Cubemap case 0x66596d5..0x6659779 (40 instr) [V]
```
0x66596d5  mov rdx,[rax+0x170]
0x66596dc  mov rcx,r14
0x66596df  call 0xE86B370
0x66596e4  nop
0x66596e5  mov [rbp+0x260],r15
0x66596ec  mov r15,[rbp+0x348]
0x66596f3  test r15,r15
0x66596f6  je short 0x6659726
0x66596f8  lock dec dword ptr [r15+8]
0x66596fd  jne short 0x6659726
0x66596ff  mov rax,[r15]
0x6659702  mov rax,[rax]
0x6659705  mov rcx,r15
0x6659708  call qword ptr [0xF99FFA0]
0x665970e  lock dec dword ptr [r15+0xC]
0x6659713  jne short 0x6659726
0x6659715  mov rax,[r15]
0x6659718  mov rax,[rax+8]
0x665971c  mov rcx,r15
0x665971f  call qword ptr [0xF99FFA0]
0x6659725  nop
0x6659726  lea rcx,[rbp+0x1E0]
0x665972d  call 0x66A08B0
0x6659732  nop
0x6659733  cmp dword ptr [rsi+0x70],2
0x6659737  jne 0x66597DC
0x665973d  mov r9,[rdi]
0x6659740  lea rcx,[rbp+0x50]
0x6659744  lea r8,[rbp+0x1E0]
0x665974b  mov rdx,rsi
0x665974e  call 0xBBD7F70
0x6659753  nop
0x6659754  mov r8,[rdi]
0x6659757  mov eax,[r8+0x1D0]
0x665975e  xor r14d,r14d
0x6659761  cmp byte ptr [r8+0x1D4],0
0x6659769  cmovne r14,rax
0x665976d  movzx eax,byte ptr [rbp+0xA8]
0x6659774  mov ecx,eax
0x6659776  xor cl,1
```
// INTERPRETATION [V]: Calls material helper 0xE86B370(rdx=[rax+0x170], rcx=r14) [V] — 0xe86b370 is the material-pair getter used by the Sky/SunMoon/cubemap family [I]. Releases shared_ptr r15=[rbp+0x348] (lock dec + destroy strong+weak) [V]. Calls mesh-header builder 0x66A08B0(out=&rbp+0x1E0) [V] (geometry_resolvers.md). If [rsi+0x70]==2 calls 0xBBD7F70(rdx=rsi, rcx=&rbp+0x50, r8=&rbp+0x1E0, r9=[rdi]) — VertexFormat-family helper (cf. 0xbbd7c70) [V,I]. Instance count from mesh [r8+0x1d0] if [r8+0x1D4]!=0 via cmovne — matches Mesh::bind +0x1d0 [V,I]. Ends by flipping flag byte [rbp+0xA8] bit0 (`xor cl,1`) [V].

## Phase C3 — Cubemap case 0x6659779..0x6659815 (40 instr) [V]
```
0x6659779  test r14,r14
0x665977c  sete dl
0x665977f  or dl,cl
0x6659781  jne 0x665CEC8
0x6659787  xorps xmm6,xmm6
0x665978a  movaps [rbp+0x30],xmm6
0x665978e  lea rcx,[rbp+0x30]
0x6659792  mov rdx,rsi
0x6659795  mov r9d,r14d
0x6659798  call 0x6693320
0x665979d  nop
0x665979e  movaps [rbp-0x20],xmm6
0x66597a2  movaps [rbp-0x10],xmm6
0x66597a6  xor eax,eax
0x66597a8  test dword ptr [rdi+0x6C],0xFFFFFFFD
0x66597af  setne al
0x66597b2  shl eax,9
0x66597b5  add eax,0x200
0x66597ba  lea rcx,[rdi+8]
0x66597be  movaps [rbp+0x10],xmm6
0x66597c2  mov rdx,[rbp+0x38]
0x66597c6  test rdx,rdx
0x66597c9  je 0x665B736
0x66597cf  lock inc dword ptr [rdx+8]
0x66597d3  mov rdx,[rbp+0x38]
0x66597d7  jmp 0x665B738
0x66597dc  mov r15,[rdi]
0x66597df  mov rax,[r15+0x60]
0x66597e3  sub rax,[r15+0x58]
0x66597e7  shr rax,2
0x66597eb  imul eax,0xAAAAAAAB
0x66597f1  test eax,eax
0x66597f3  je short 0x6659824
0x66597f5  mov edx,0x250
0x66597fa  add rdx,[rbp+0x1E0]
0x6659801  lea rcx,[rbp+0x340]
0x6659808  xor r8d,r8d
0x665980b  call 0xBBD7C70
0x6659810  nop
0x6659811  lea rdx,[rbp+0x340]
```
// INTERPRETATION [V]: dl = (r14!=0)|cl; branches to 0x665cec8 if nonzero [V]. Zeroes xmm6 temps at [rbp+0x30],[rbp-0x20],[rbp-0x10] [V]. Calls mesh-object cache helper 0x6693320(rcx=&rbp+0x30, rdx=rsi, r9d=instance count r14d) [V] — 0x6693320 is used by the 0x6693850 cache get-or-create path [I]. Computes flags from [rdi+0x6C] (test 0xFFFFFFFD, setne, shl 9, add 0x200) [V]. rcx=rdi+8 (material2+) [V]. Retains shared_ptr [rbp+0x38] (lock inc) and jumps to 0x665b738 [V]. Else (target 0x66597dc): itemCount = (([rdi+0x60]-[rdi+0x58])>>2) * 0xAAAAAAAB => /12, matches Mesh::bind itemCount [V,I]; if zero jump 0x6659824. Calls 0xBBD7C70(rcx=&rbp+0x340 VertexFmtDesc out, rdx=[rbp+0x1E0]+0x250 material inputs, r8=0 packed=false) — matches 0xbbd7c70(&tmp, m2+0x250, 0) [V,I]. Case continues at 0x6659815.

## Phase C4 — Cubemap case 0x6659815..0x66598e4 (40 instr) [V]
```
0x6659815  add eax,[rax]
0x6659817  add [rcx+rcx*4-7],cl
0x665981b  call 0x4DEDD00
0x6659820  nop
0x6659821  mov r15,[rdi]
0x6659824  xor r13d,r13d
0x6659827  cmp byte ptr [r15+0x1D4],0
0x665982f  je short 0x6659838
0x6659831  mov r13d,[r15+0x1D0]
0x6659838  mov eax,[0x129F9FC8]
0x665983e  mov ecx,[0x128767C8]
0x6659844  mov rdx,gs:[0x58]
0x665984d  mov rcx,[rdx+rcx*8]
0x6659851  cmp eax,[rcx+4]
0x6659857  jg 0x665DC77
0x665985d  mov eax,[0x129F9FD8]
0x6659863  mov ecx,[0x128767C8]
0x6659869  mov rdx,gs:[0x58]
0x6659872  mov rcx,[rdx+rcx*8]
0x6659876  cmp eax,[rcx+4]
0x665987c  jg 0x665DCE9
0x6659882  mov eax,[0x129F9FE8]
0x6659888  mov ecx,[0x128767C8]
0x665988e  mov rdx,gs:[0x58]
0x6659897  mov rcx,[rdx+rcx*8]
0x665989b  cmp eax,[rcx+4]
0x66598a1  jg 0x665DD5B
0x66598a7  movaps [rbp+0x340],xmm6
0x66598ae  mov qword ptr [rbp+0x50],1
0x66598b6  mov [rbp+0x58],r12
0x66598ba  mov rax,[rbp+0x218]
0x66598c1  movzx r8d,word ptr [rbp+0x222]
0x66598c9  mov edx,r8d
0x66598cc  shl edx,4
0x66598cf  mov rcx,rax
0x66598d2  test r8d,r8d
0x66598d5  je short 0x66598F9
0x66598d7  mov r8,[0x129F9FC0]
0x66598de  mov r9,rdx
0x66598e1  mov rcx,rax
```
// INTERPRETATION [V]: eax+=eax (x2) then `add cl,[rcx+rcx*4-7]` — building a vertex attribute offset table [V,I]. Calls Mesh::bind 0x4DEDD00(mesh=rdi, fmt=&rbp+0x340) [V] per callee doc. r13 = instance count ([r15+0x1d0] if [r15+0x1D4]!=0) [V]. Three TLS registry lookups (slot ids at data_129f9fc8/9fd8/9fe8, base data_128767c8, tls=gs:[0x58]); each `cmp eax,[rcx+4]; jg -> cold` (0x665dc77/0x665dce9/0x665dd5b) — per-thread registry slot reservation, the 0x9bd4a0 pattern [V,I]. Sets [rbp+0x50]=1, [rbp+0x58]=r12 [V]. r8d = u16 [rbp+0x222]; edx = r8d<<4; if zero jump 0x66598f9 [V]. Loads r8 = global [0x129f9fc0] [V]. Cubemap case does NOT end here — continues at 0x66598e4 [V].

## Phase C5 — Cubemap case 0x66598e4..0x665997e (40 instr) [V]
```
0x66598e4  mov r10,[rcx]
0x66598e7  cmp [r10+0x28],r8
0x66598eb  je short 0x66598F9
0x66598ed  add rcx,0x10
0x66598f1  add r9,0xFFFFFFFFFFFFFFF0
0x66598f5  jne short 0x66598E4
0x66598f7  jmp short 0x6659928
0x66598f9  add rdx,rax
0x66598fc  cmp rcx,rdx
0x66598ff  jae short 0x6659928
0x6659901  sub ecx,eax
0x6659903  shr ecx,4
0x6659906  mov [rbp+0x4E0],cx
0x665990d  mov byte ptr [rbp+0x4E2],1
0x6659914  lea rdx,[rbp+0x4E0]
0x665991b  lea r8,[rbp+0x50]
0x665991f  mov rcx,r14
0x6659922  call 0x5679DB0
0x6659927  nop
0x6659928  mov rax,[rbp+0x228]
0x665992f  movzx r8d,word ptr [rbp+0x232]
0x6659937  mov ecx,r8d
0x665993a  shl ecx,4
0x665993d  lea rdx,[rcx+rcx*2]
0x6659941  mov rcx,rax
0x6659944  test r8,r8
0x6659947  je 0x6659D74
0x665994d  mov r8,[0x129F9FD0]
0x6659954  mov r9,rdx
0x6659957  mov rcx,rax
0x665995a  mov r10,[rcx]
0x665995d  cmp [r10+0x28],r8
0x6659961  je 0x6659D74
0x6659967  add rcx,0x30
0x665996b  add r9,0xFFFFFFFFFFFFFFD0
0x665996f  jne short 0x665995A
0x6659971  jmp 0x6659DBA
0x6659976  add rdx,rax
0x6659979  cmp rcx,rdx
0x665997c  jae short 0x66599A8
```
// INTERPRETATION [V]: Two back-to-back table lookups over arrays of descriptor-like entries.
Search 1 (0x66598e4..0x66598f7): rcx walks an array (stride 0x10 via add rcx,0x10 / add r9,-0x10) [V]; entry r10=[rcx]; compares [r10+0x28] with r8 (= u16 [rbp+0x222]<<4 from C4) [V]; je on match to found block 0x66598f9 [V]; exhausted (r9==0) -> jmp 0x6659928 [V]. r8 is the search key; r9 is remaining byte count [I].
Found block 1 (0x66598f9..0x6659927): add rdx,rax; bounds cmp rcx,rdx; jae -> 0x6659928 [V]; else index = (ecx-eax)>>4 stored at [rbp+0x4E0], flag byte [rbp+0x4E2]=1 [V]; calls 0x5679DB0(rcx=r14, rdx=&rbp+0x4E0 out-index, r8=&rbp+0x50) [V]. (0x5679DB0 body undecoded [I].)
Common join 0x6659928: rax=[rbp+0x228] (second table base) [V]; r8d = u16 [rbp+0x232]; edx2 = r8d*0x30 (lea rdx,[rcx+rcx*2] after shl 4 => *48) [V]; rcx=rax; test r8,r8; je 0x6659D74 if zero count [V].
Search 2 (0x665995a..0x6659971): walks array stride 0x30 [V]; entry r10=[rcx]; cmp [r10+0x28], r8 where r8=global [0x129F9FD0] [V]; je 0x6659D74 on match [V]; not found (r9==0) -> jmp 0x6659DBA [V]. Linearly-placed bytes 0x6659976..0x66599a7 (add rdx,rax; bounds; index->[rbp+0x170]; [rbp+0x172]=1; call 0x5679DB0(rcx=rbx, rdx=&rbp+0x170, r8=&rbp+0x1E0)) sit after the unconditional jmp 0x6659971 — reachability via fall-through is uncertain / likely a cold block [?].
rdis reports this whole region as one function `sub_66598e4 [0x66598e4..0x665b8e4)` size 0x2000, 0 xrefs in [V].

## Phase E1 — EndSky/LegacyCubemap 0x6656b2b..0x6656bec (40 instr) [V]
```
0x6656b2b  lea rdx,[rbp+0x330]
0x6656b32  call 0x675E440
0x6656b37  mov rax,[rbp+0x330]
0x6656b3e  mov rbx,[rax]
0x6656b41  test rbx,rbx
0x6656b44  je 0x665D11D
0x6656b4a  mov eax,[0x129CA5E0]
0x6656b50  mov ecx,[0x128767C8]
0x6656b56  mov rdx,gs:[0x58]
0x6656b5f  mov rcx,[rdx+rcx*8]
0x6656b63  cmp eax,[rcx+4]
0x6656b69  jg 0x665D489
0x6656b6f  cmp byte ptr [rbx+0x10],1
0x6656b73  jne 0x665D11D
0x6656b79  mov rax,[rbp+0x330]
0x6656b80  mov rcx,[rax+8]
0x6656b84  test rcx,rcx
0x6656b87  je 0x6657444
0x6656b8d  lock inc dword ptr [rcx+8]
0x6656b91  mov rcx,[rax]
0x6656b94  mov rbx,[rax+8]
0x6656b98  mov rax,[rcx+0x18]
0x6656b9c  mov r14,[rax]
0x6656b9f  test rbx,rbx
0x6656ba2  je 0x665744E
0x6656ba8  lock dec dword ptr [rbx+8]
0x6656bac  jne 0x665744E
0x6656bb2  mov rax,[rbx]
0x6656bb5  mov rax,[rax]
0x6656bb8  mov rcx,rbx
0x6656bbb  call qword ptr [0xF99FFA0]
0x6656bc1  lock dec dword ptr [rbx+0xC]
0x6656bc5  jne 0x665744E
0x6656bcb  mov rax,[rbx]
0x6656bce  mov rax,[rax+8]
0x6656bd2  mov rcx,rbx
0x6656bd5  call qword ptr [0xF99FFA0]
0x6656bdb  jmp 0x665744E
0x6656be0  lea r12,[rbp+0x120]
0x6656be7  mov eax,0xF
```
// INTERPRETATION [V]: EndSky/LegacyCubemap entry. call 0x675E440 [V] (helper, undecoded [?]). rbx=[rbp+0x330][0]; null -> epilogue 0x665d11d [V]. TLS registry lookup (slot data_129ca5e0, base data_128767c8, tls=gs:[0x58]); `cmp eax,[rcx+4]; jg -> cold 0x665d489` — 0x9bd4a0 pattern [V,I]. `cmp byte [rbx+0x10],1; jne -> 0x665d11d` — ready/loaded flag ==1 check [V,I]. Retain shared_ptr [rax+8] (lock inc); null [rax+8] -> 0x6657444 [V]. Release old rbx (lock dec [rbx+8]; destroy strong then weak via eea6040) [V]. jmp 0x665744e [V]. Then lea r12=[rbp+0x120]; mov eax,0xF — starts building a 0x10-byte block at rbp+0x120 ([rbp+0x130]=r15=0, [rbp+0x138]=0xF size) [V].

## Phase E2 — EndSky/LegacyCubemap 0x6656bec..0x6656c54 (20 instr) [V]
```
0x6656bec  mov [rbp+0x130],r15
0x6656bf3  mov [rbp+0x138],rax
0x6656bfa  mov rcx,r12
0x6656bfd  mov rdx,r14
0x6656c00  mov r8,r15
0x6656c03  call 0xEEC6EC0
0x6656c08  mov byte ptr [r12+r13],0
0x6656c0d  mov eax,[0x129F9D00]
0x6656c13  mov ecx,[0x128767C8]
0x6656c19  mov rdx,gs:[0x58]
0x6656c22  mov rcx,[rdx+rcx*8]
0x6656c26  cmp eax,[rcx+4]
0x6656c2c  jg 0x665D2AA
0x6656c32  mov r9,[rsi+0x40]
0x6656c36  mov rcx,[rsi+0x68]
0x6656c3a  mov rax,[rbp+0x130]
0x6656c41  cmp qword ptr [rbp+0x138],0x10
0x6656c49  jb short 0x6656C54
0x6656c4b  mov rdx,[rbp+0x120]
0x6656c52  jmp short 0x6656C5B
```
// INTERPRETATION [V]: [rbp+0x130]=r15(0), [rbp+0x138]=0xF (size/stride) [V]. call 0xEEC6EC0(rcx=&rbp+0x120, rdx=r14, r8=r15) — 0xeec6ec0 is the small memcpy; copies 0xF bytes; `byte [r12+r13]=0` null-terminates [V]. Second TLS lookup (slot data_129f9d00, same base/gs pattern; jg -> cold 0x665d2aa) [V,I]. r9=[rsi+0x40], rcx=[rsi+0x68], rax=[rbp+0x130]; `cmp qword [rbp+0x138],0x10; jb short 0x6656c54` else rdx=[rbp+0x120]; `jmp short 0x6656c5b` — SSO/small-string branch (size<=0x10 uses inline buffer rbp+0x120 else heap ptr) [V,I]. Falls into phase E3 at 0x6656c54.

## Phase E3 — EndSky/LegacyCubemap 0x6656c54..0x6656d22 (40 instr) [V]
```
0x6656c54  lea rdx,[rbp+0x120]
0x6656c5b  xorps xmm0,xmm0
0x6656c5e  movaps [rbp+0x340],xmm0
0x6656c65  mov [rbp+0x1E0],rdx
0x6656c6c  mov [rbp+0x1E8],rax
0x6656c73  lea r12,[rbp+0x340]
0x6656c7a  mov [rsp+0x28],r12
0x6656c7f  lea rax,[rbp+0x1E0]
0x6656c86  mov [rsp+0x20],rax
0x6656c8b  lea r8,[0x129F9CF0]
0x6656c92  lea rdx,[rbp+0x320]
0x6656c99  call 0x675E440
0x6656c9e  nop
0x6656c9f  mov rax,[rbp+0x320]
0x6656ca6  mov r14,[rax]
0x6656ca9  test r14,r14
0x6656cac  je 0x665B56E
0x6656cb2  mov eax,[0x129CA5E0]
0x6656cb8  mov ecx,[0x128767C8]
0x6656cbe  mov rdx,gs:[0x58]
0x6656cc7  mov rcx,[rdx+rcx*8]
0x6656ccb  cmp eax,[rcx+4]
0x6656cd1  jg 0x665D552
0x6656cd7  cmp byte ptr [r14+0x10],1
0x6656cdc  jne 0x665B56E
0x6656ce2  mov rax,[rbp+0x320]
0x6656ce9  mov rcx,[rax+8]
0x6656ced  test rcx,rcx
0x6656cf0  je 0x66575E4
0x6656cf6  lock inc dword ptr [rcx+8]
0x6656cfa  mov rcx,[rax]
0x6656cfd  mov r14,[rax+8]
0x6656d01  mov rax,[rcx+0x18]
0x6656d05  mov r15,[rax]
0x6656d08  test r14,r14
0x6656d0b  je 0x66575EE
0x6656d11  lock dec dword ptr [r14+8]
0x6656d16  jne 0x66575EE
0x6656d1c  mov rax,[r14]
0x6656d1f  mov rax,[rax]
```
// INTERPRETATION [V]: Builds args at rbp+0x1E0.. (string ptr [rbp+0x1E0]=[rbp+0x120], [rbp+0x1E8]=rax) and calls 0x675E440(rcx=&rbp+0x1E0, rdx=&rbp+0x320, r8=global [0x129f9cf0]) — 0x675e440 again (string/format consumer) [V,I]. rax=[rbp+0x320]; r14=[rax]; null -> 0x665b56e [V]. TLS lookup slot data_129ca5e0 (same pattern; jg -> cold 0x665d552) [V,I]. `cmp byte [r14+0x10],1; jne -> 0x665b56E` ready-flag check [V,I]. Retain [rax+8]; null -> 0x66575e4 [V]. Release old r14 (lock dec [r14+8]; destroy strong+weak via eea6040) [V]. jmp 0x66575ee [V]. Continues at 0x6656d22.

## Phase E4 — EndSky/LegacyCubemap 0x6656d22..0x6656d4d (10 instr, range boundary reached) [V]
```
0x6656d22  mov rcx,r14
0x6656d25  call qword ptr [0xF99FFA0]
0x6656d2b  lock dec dword ptr [r14+0xC]
0x6656d30  jne 0x66575EE
0x6656d36  mov rax,[r14]
0x6656d39  mov rax,[rax+8]
0x6656d3d  mov rcx,r14
0x6656d40  call qword ptr [0xF99FFA0]
0x6656d46  jmp 0x66575EE
0x6656d4b  xor eax,eax
0x6656d4d  mov rcx,[rdi+0xD8]
```
// INTERPRETATION [V]: Completes the r14 shared_ptr release (destroy strong via eea6040, lock dec [r14+0xC] weak, destroy again) then jmp 0x66575ee [V]. `xor eax,eax`; `mov rcx,[rdi+0xD8]` — this is exactly the range end boundary 0x6656d4d [V]; flow continues past the boundary (outside this unit's range). EndSky/LegacyCubemap 0x6656b2b..0x6656d4d is INSTRUCTION-COMPLETE [V].

## Phase C6 — Cubemap case 0x665997e..0x6659a75 (40 instr) [V]
```
0x665997e  sub ecx,eax
0x6659980  shr ecx,4
0x6659983  mov [rbp+0x170],cx
0x665998a  mov byte ptr [rbp+0x172],1
0x6659991  lea rdx,[rbp+0x170]
0x6659998  lea r8,[rbp+0x1E0]
0x665999f  mov rcx,rbx
0x66599a2  call 0x5679DB0
0x66599a7  nop
0x66599a8  movzx eax,byte ptr [rdi+0x3E]
0x66599ac  test al,al
0x66599ae  je 0x6659B9B
0x66599b4  cmp byte ptr [rdi+0x3F],1
0x66599b8  jne 0x6659EDD
0x66599be  mov rax,[rdi+0x18]
0x66599c2  movups xmm6,[rax]
0x66599c5  movaps [rbp+0x1E0],xmm6
0x66599cc  movups xmm7,[rax+0x10]
0x66599d0  movaps [rbp+0x1F0],xmm7
0x66599d7  movups xmm8,[rax+0x20]
0x66599dc  movaps [rbp+0x200],xmm8
0x66599e4  movups xmm9,[rax+0x30]
0x66599e9  movaps [rbp+0x210],xmm9
0x66599f1  mov byte ptr [rbp+0x220],0
0x66599f8  cmp byte ptr [rbp+0x538],0
0x66599ff  je 0x665DEAA
0x6659a05  mov di,[rdi+0x3C]
0x6659a09  mov dword ptr [rbp+0x344],3
0x6659a13  mov byte ptr [rbp+0x348],7
0x6659a1a  mov dword ptr [rbp+0x34C],1
0x6659a24  mov word ptr [rbp+0x350],1
0x6659a2d  mov byte ptr [rbp+0x352],2
0x6659a34  mov dword ptr [rbp+0x354],0
0x6659a3e  mov byte ptr [rbp+0x358],0
0x6659a45  xorps xmm10,xmm10
0x6659a49  movups [rbp+0x35C],xmm10
0x6659a51  movups [rbp+0x368],xmm10
0x6659a59  mov byte ptr [rbp+0x378],8
0x6659a60  mov qword ptr [rbp+0x37C],0
0x6659a6b  mov dword ptr [rbp+0x384],0
```
// INTERPRETATION [V]: Completes the dead/cold found-epilogue for search 2: index=(ecx-eax)>>4 -> [rbp+0x170], flag [rbp+0x172]=1, call 0x5679DB0(rcx=rbx, rdx=&rbp+0x170, r8=&rbp+0x1E0) [V] — reachable only by linear fall-through after the unconditional jmp 0x6659971, so treat as cold block [?].
Real flow at 0x66599a8: movzx eax,byte [rdi+0x3E]; test al,al; je 0x6659B9B if zero [V]. cmp byte [rdi+0x3F],1; jne 0x6659EDD if !=1 [V]. Else copies a 64-byte block [rax]..[rax+0x30] ([rdi+0x18]) into xmm6..xmm9 -> [rbp+0x1E0],[rbp+0x1F0],[rbp+0x200],[rbp+0x210] (4x16 bytes, likely a matrix/transform) [V]. mov byte [rbp+0x220]=0; cmp byte [rbp+0x538],0; je 0x665DEAA (sub_665deaa, undecoded helper) [V,I]. Then mov di,[rdi+0x3C] (16-bit load) and builds a fixed descriptor at rbp+0x344..0x388: [rbp+0x344]=3 dword, [rbp+0x348]=7 byte, [rbp+0x34C]=1 dword, [rbp+0x350]=1 word, [rbp+0x352]=2 byte, [rbp+0x354]=0 dword, [rbp+0x358]=0 byte; zeroes xmm10->[rbp+0x35C],[rbp+0x368]; [rbp+0x378]=8 byte, [rbp+0x37C]=0 qword, [rbp+0x384]=0 dword, [rbp+0x388]=8 byte [V]. This fixed block looks like a vertex/draw descriptor being assembled toward the SKY-PUSH tail [I].

## OPEN
- Cubemap case end not yet located; last decoded addr 0x6659a75 (phase C6). Expect exit to shared SKY-PUSH tail (~0x665a8e5 per ext_particle_sky_callees.md section D) or epilogue 0x665d11d/0x665d124 [?].
- 0x675E440, 0xBBD7F70, 0x6693320, 0x5679DB0 helper bodies undecoded [?].
- Exact meaning of flag bits / desc offsets [?].
