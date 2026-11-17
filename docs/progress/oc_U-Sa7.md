## NEXT
step 2

# UNIT U-Sa7 — instruction slice 0x66a8518..0x66a88c7

Slice: chunk 7 of 7 of effect_shadow_extractor_alt_66a6830_66a88c8 (shadow extractor alt 0x66a6830), RVAs relative to the 1.26.62.01 image base.
Input: docs/progress/_part_Sa7.txt (208 instructions). All 208 instructions are quoted verbatim in the phases below — none skipped — and every [reg+off] load/store is re-indexed by offset in the field map. The `(bad)` line at 0x66a882e is quoted exactly as the listing prints it; no instruction decodes there. Field-map meaning is "-" unless an instruction or string in the slice shows it. Claims cite the instruction RVA [V].

## Phase 1: 0x66a8518..0x66a8572 — Allocation free/check tail [V]: if rcx < 0x20 jump to the error path at 0x66A87F8, otherwise rdx |= 0x27, rcx = rax and call 0xE935700; then lea rcx,[rbp-8] and call 0x1751590 on the local at [rbp-8] (rcx is reloaded from [rbp+0x560] right after); if [rbp+0x560] is non-NULL, rdx = [rbp+0x570] - rcx and, when rdx >= 0x1000, the allocation total size is recomputed from its header as rcx = (rcx - 8) - [rcx-8]; if that size >= 0x20 jump 0x66A87F8, otherwise rdx |= 0x27, rcx = rax, call 0xE935700.
0x66a8518  cmp rcx,0x20
0x66a851c  jae 0x66A87F8
0x66a8522  or rdx,0x27
0x66a8526  mov rcx,rax
0x66a8529  call 0xE935700
0x66a852e  lea rcx,[rbp-8]
0x66a8532  call 0x1751590
0x66a8537  mov rcx,[rbp+0x560]
0x66a853e  test rcx,rcx
0x66a8541  je short 0x66A8577
0x66a8543  mov rdx,[rbp+0x570]
0x66a854a  sub rdx,rcx
0x66a854d  cmp rdx,0x1000
0x66a8554  jb short 0x66A8572
0x66a8556  mov rax,[rcx-8]
0x66a855a  add rcx,0xFFFFFFFFFFFFFFF8
0x66a855e  sub rcx,rax
0x66a8561  cmp rcx,0x20
0x66a8565  jae 0x66A87F8
0x66a856b  or rdx,0x27
0x66a856f  mov rcx,rax
0x66a8572  call 0xE935700

## Phase 2: 0x66a8577..0x66a85ae — Release refcounted object rsi = [rbp+0x278], skipped if NULL [V]: lock dec dword [rsi+8]; if the result is non-zero jump to 0x66A85AE; rax = [rsi], rax = [rax] and call qword ptr [0xF99FFA0] (rcx = rsi); lock dec dword [rsi+0xC]; if non-zero jump to 0x66A85AE; rax = [rsi], rax = [rax+8] and call qword ptr [0xF99FFA0].
0x66a8577  mov rsi,[rbp+0x278]
0x66a857e  test rsi,rsi
0x66a8581  je short 0x66A85AE
0x66a8583  lock dec dword ptr [rsi+8]
0x66a8587  jne short 0x66A85AE
0x66a8589  mov rax,[rsi]
0x66a858c  mov rax,[rax]
0x66a858f  mov rcx,rsi
0x66a8592  call qword ptr [0xF99FFA0]
0x66a8598  lock dec dword ptr [rsi+0xC]
0x66a859c  jne short 0x66A85AE
0x66a859e  mov rax,[rsi]
0x66a85a1  mov rax,[rax+8]
0x66a85a5  mov rcx,rsi
0x66a85a8  call qword ptr [0xF99FFA0]

## Phase 3: 0x66a85ae..0x66a85e5 — Identical two-stage release for rsi = [rbp+0x350] with skip target 0x66A85E5 [V].
0x66a85ae  mov rsi,[rbp+0x350]
0x66a85b5  test rsi,rsi
0x66a85b8  je short 0x66A85E5
0x66a85ba  lock dec dword ptr [rsi+8]
0x66a85be  jne short 0x66A85E5
0x66a85c0  mov rax,[rsi]
0x66a85c3  mov rax,[rax]
0x66a85c6  mov rcx,rsi
0x66a85c9  call qword ptr [0xF99FFA0]
0x66a85cf  lock dec dword ptr [rsi+0xC]
0x66a85d3  jne short 0x66A85E5
0x66a85d5  mov rax,[rsi]
0x66a85d8  mov rax,[rax+8]
0x66a85dc  mov rcx,rsi
0x66a85df  call qword ptr [0xF99FFA0]

## Phase 4: 0x66a85e5..0x66a861e — Epilogue [V]: movaps reloads xmm6-xmm10 from [rbp+0x590..0x5D0], add rsp,0x668, pop rbx/rdi/rsi/r12-r15/rbp, ret.
0x66a85e5  movaps xmm6,[rbp+0x590]
0x66a85ec  movaps xmm7,[rbp+0x5A0]
0x66a85f3  movaps xmm8,[rbp+0x5B0]
0x66a85fb  movaps xmm9,[rbp+0x5C0]
0x66a8603  movaps xmm10,[rbp+0x5D0]
0x66a860b  add rsp,0x668
0x66a8612  pop rbx
0x66a8613  pop rdi
0x66a8614  pop rsi
0x66a8615  pop r12
0x66a8617  pop r13
0x66a8619  pop r14
0x66a861b  pop r15
0x66a861d  pop rbp
0x66a861e  ret

## Phase 5: 0x66a861f..0x66a8690 — Cold tail and first one-time init [V]: mov rcx,r15, call 0x9BC830, nop, jmp 0x66A82A3; then lock global 0x129F8CC8 (call 0xE938CB0); if dword [0x129F8CC8] != -1 jump 0x66A68B1; otherwise xmm0 = 0, movaps [rbp+0x1E0] = 0, [rbp+0x248] = pointer 0xF5CF1BF, qword [rbp+0x250] = 0xC, call 0x5668AC0 (rcx = &0x129F8CB8, rdx = &[rbp+0x248], r8 = &[rbp+0x1E0]), unlock via call 0xE938D70, jmp 0x66A68B1.
0x66a861f  mov rcx,r15
0x66a8622  call 0x9BC830
0x66a8627  nop
0x66a8628  jmp 0x66A82A3
0x66a862d  lea rcx,[0x129F8CC8]
0x66a8634  call 0xE938CB0
0x66a8639  cmp dword ptr [0x129F8CC8],0xFFFFFFFF
0x66a8640  jne 0x66A68B1
0x66a8646  xorps xmm0,xmm0
0x66a8649  movaps [rbp+0x1E0],xmm0
0x66a8650  lea rax,[0xF5CF1BF]
0x66a8657  mov [rbp+0x248],rax
0x66a865e  mov qword ptr [rbp+0x250],0xC
0x66a8669  lea rcx,[0x129F8CB8]
0x66a8670  lea rdx,[rbp+0x248]
0x66a8677  lea r8,[rbp+0x1E0]
0x66a867e  call 0x5668AC0
0x66a8683  nop
0x66a8684  lea rcx,[0x129F8CC8]
0x66a868b  call 0xE938D70
0x66a8690  jmp 0x66A68B1

## Phase 6: 0x66a8695..0x66a86f8 — Same init shape for global 0x129F8CE0 with jump target 0x66A68D6 [V]: [rbp+0x1F0] = 0 (movaps), [rbp+0x258] = pointer 0xF51E40C, qword [rbp+0x260] = 0xD, call 0x5668AC0 (rcx = &0x129F8CD0, rdx = &[rbp+0x258], r8 = &[rbp+0x1F0]), unlock, jmp 0x66A68D6.
0x66a8695  lea rcx,[0x129F8CE0]
0x66a869c  call 0xE938CB0
0x66a86a1  cmp dword ptr [0x129F8CE0],0xFFFFFFFF
0x66a86a8  jne 0x66A68D6
0x66a86ae  xorps xmm0,xmm0
0x66a86b1  movaps [rbp+0x1F0],xmm0
0x66a86b8  lea rax,[0xF51E40C]
0x66a86bf  mov [rbp+0x258],rax
0x66a86c6  mov qword ptr [rbp+0x260],0xD
0x66a86d1  lea rcx,[0x129F8CD0]
0x66a86d8  lea rdx,[rbp+0x258]
0x66a86df  lea r8,[rbp+0x1F0]
0x66a86e6  call 0x5668AC0
0x66a86eb  nop
0x66a86ec  lea rcx,[0x129F8CE0]
0x66a86f3  call 0xE938D70
0x66a86f8  jmp 0x66A68D6

## Phase 7: 0x66a86fd..0x66a873b — One-time init of global 0x129CA5E0, jump target 0x66A69A6 [V]: lock; if dword [0x129CA5E0] != -1 jump 0x66A69A6; call 0x567DB00 (rcx = &0x129CA568); call 0xE935740 (rcx = &0x567DBA0); unlock; jmp 0x66A69A6.
0x66a86fd  lea rcx,[0x129CA5E0]
0x66a8704  call 0xE938CB0
0x66a8709  cmp dword ptr [0x129CA5E0],0xFFFFFFFF
0x66a8710  jne 0x66A69A6
0x66a8716  lea rcx,[0x129CA568]
0x66a871d  call 0x567DB00
0x66a8722  nop
0x66a8723  lea rcx,[0x567DBA0]
0x66a872a  call 0xE935740
0x66a872f  lea rcx,[0x129CA5E0]
0x66a8736  call 0xE938D70
0x66a873b  jmp 0x66A69A6

## Phase 8: 0x66a8740..0x66a877e — Same init shape again, jump target 0x66A6A4D [V].
0x66a8740  lea rcx,[0x129CA5E0]
0x66a8747  call 0xE938CB0
0x66a874c  cmp dword ptr [0x129CA5E0],0xFFFFFFFF
0x66a8753  jne 0x66A6A4D
0x66a8759  lea rcx,[0x129CA568]
0x66a8760  call 0x567DB00
0x66a8765  nop
0x66a8766  lea rcx,[0x567DBA0]
0x66a876d  call 0xE935740
0x66a8772  lea rcx,[0x129CA5E0]
0x66a8779  call 0xE938D70
0x66a877e  jmp 0x66A6A4D

## Phase 9: 0x66a8783..0x66a87cb — One-time init of global 0x129F8CF0, jump target 0x66A7A06 [V]; then rdx = string 0xF5638D6, rdi = &[rbp+0x360] (lea only, address computation), call 0x79580; r8 = [rbp+0x370]; if qword [rbp+0x378] < 0x10 jump 0x66A87CB else rdi = [rbp+0x360]; if r8 == 0 jump 0x66A881E.
0x66a8783  lea rcx,[0x129F8CF0]
0x66a878a  call 0xE938CB0
0x66a878f  cmp dword ptr [0x129F8CF0],0xFFFFFFFF
0x66a8796  jne 0x66A7A06
0x66a879c  lea rdx,[0xF5638D6]
0x66a87a3  lea rdi,[rbp+0x360]
0x66a87aa  mov rcx,rdi
0x66a87ad  call 0x79580
0x66a87b2  nop
0x66a87b3  mov r8,[rbp+0x370]
0x66a87ba  cmp qword ptr [rbp+0x378],0x10
0x66a87c2  jb short 0x66A87CB
0x66a87c4  mov rdi,[rbp+0x360]
0x66a87cb  test r8,r8
0x66a87ce  je short 0x66A881E

## Phase 10: 0x66a87d0..0x66a8818 — FNV-1a 64-bit hash setup [V]: eax = r8d & 3; rcx = prime 0x100000001B3; if r8 >= 4 jump to 0x66A882A; else rdx = basis 0xCBF29CE484222325, r9d = 0, jmp 0x66A887C. Cold error path (from the 0x20-size checks) at 0x66a87f8: [rsp+0x20] = 0, ecx = edx = r8d = r9d = 0, call qword ptr [0xF9A8C78], nop, call 0x75B60, nop, call 0x75B60.
0x66a87d0  mov eax,r8d
0x66a87d3  and eax,3
0x66a87d6  mov rcx,0x100000001B3
0x66a87e0  cmp r8,4
0x66a87e4  jae short 0x66A882A
0x66a87e6  mov rdx,0xCBF29CE484222325
0x66a87f0  xor r9d,r9d
0x66a87f3  jmp 0x66A887C
0x66a87f8  mov qword ptr [rsp+0x20],0
0x66a8801  xor ecx,ecx
0x66a8803  xor edx,edx
0x66a8805  xor r8d,r8d
0x66a8808  xor r9d,r9d
0x66a880b  call qword ptr [0xF9A8C78]
0x66a8811  nop
0x66a8812  call 0x75B60
0x66a8817  nop
0x66a8818  call 0x75B60
0x66a881d  nop

## Phase 11: 0x66a881e..0x66a889a — Hash body [V]: rdx = basis, jmp to 0x66A889C. At 0x66a882a: and r8,~3; then the bytes at 0x66a882e are listed `(bad)` and the following mov edx,0x84222325 / in al,0x9C / ret far are quoted as-is (misdecoded region). Main dword loop at 0x66a8838: xor r9d,r9d, hash 4 bytes per iteration (movzx byte [rdi+r9+0..3], xor, imul with rcx), r9 += 4, loop while r8 != r9; if rax == 0 jump 0x66A889C; else tail loop from 0x66a887c (rdi += r9, r8d = 0): movzx byte [rdi+r8], xor rdx,r9, imul rdx,rcx, r8++, r9 = rdx until r8 == rax.
0x66a881e  mov rdx,0xCBF29CE484222325
0x66a8828  jmp short 0x66A889C
0x66a882a  and r8,0xFFFFFFFFFFFFFFFC
0x66a882e  (bad)
0x66a882f  mov edx,0x84222325
0x66a8834  in al,0x9C
0x66a8836  ret far
0x66a8838  xor r9d,r9d
0x66a883b  movzx r10d,byte ptr [rdi+r9]
0x66a8840  xor r10,rdx
0x66a8843  imul r10,rcx
0x66a8847  movzx edx,byte ptr [rdi+r9+1]
0x66a884d  xor rdx,r10
0x66a8850  imul rdx,rcx
0x66a8854  movzx r10d,byte ptr [rdi+r9+2]
0x66a885a  xor r10,rdx
0x66a885d  imul r10,rcx
0x66a8861  movzx edx,byte ptr [rdi+r9+3]
0x66a8867  xor rdx,r10
0x66a886a  imul rdx,rcx
0x66a886e  add r9,4
0x66a8872  cmp r8,r9
0x66a8875  jne short 0x66A883B
0x66a8877  test rax,rax
0x66a887a  je short 0x66A889C
0x66a887c  add rdi,r9
0x66a887f  xor r8d,r8d
0x66a8882  mov r9,rdx
0x66a8885  movzx edx,byte ptr [rdi+r8]
0x66a888a  xor rdx,r9
0x66a888d  imul rdx,rcx
0x66a8891  inc r8
0x66a8894  mov r9,rdx
0x66a8897  cmp rax,r8
0x66a889a  jne short 0x66A8885

## Phase 12: 0x66a889c..0x66a88c7 — Finish [V]: qword [0x129F8CE8] = rdx (final hash; absolute store, not [reg+off]); lea rcx,[rbp+0x360], call 0x73150; lea rcx,[0x129F8CF0], call 0xE938D70 unlock; jmp 0x66A7A06. Trailing cold bytes after the jmp: call 0x75740, nop, int3, nop [rax+rax] (slice end).
0x66a889c  mov [0x129F8CE8],rdx
0x66a88a3  lea rcx,[rbp+0x360]
0x66a88aa  call 0x73150
0x66a88af  lea rcx,[0x129F8CF0]
0x66a88b6  call 0xE938D70
0x66a88bb  jmp 0x66A7A06
0x66a88c0  call 0x75740
0x66a88c5  nop
0x66a88c6  int3
0x66a88c7  nop [rax+rax]

## Field map — every [reg+off] load/store in the slice, one row per distinct offset, all sites listed.

Offset is the displacement as written in the instruction ("-8" = [reg-8], "0" = bare [reg]). Size is the access size of the instruction (movaps 16, qword 8, dword 4, byte 1). lock dec counts as W. `lea` address computations (e.g. [rbp-8], [rbp+0x360], [rbp+0x248], [rbp+0x1E0]) are not loads/stores and the absolute store `mov [0x129F8CE8],rdx` (0x66a889c) is not [reg+off]; both are covered in the phase text instead. Meaning is "-" unless an instruction or string in the slice shows it.

| offset | size | read/store address (sites) | verbatim instruction lines | meaning |
| -8 | 8 | R [rcx-8] (0x66a8556) | 0x66a8556  mov rax,[rcx-8] | - |
| 0 | 8 | R [rax] (0x66a858c, 0x66a85c3); R [rsi] (0x66a8589, 0x66a859e, 0x66a85c0, 0x66a85d5) | 0x66a8589  mov rax,[rsi] ; 0x66a858c  mov rax,[rax] ; 0x66a859e  mov rax,[rsi] ; 0x66a85c0  mov rax,[rsi] ; 0x66a85c3  mov rax,[rax] ; 0x66a85d5  mov rax,[rsi] | - |
| 8 | 8/4 | R [rax+8] (0x66a85a1, 0x66a85d8); W [rsi+8] dword lock (0x66a8583, 0x66a85ba) | 0x66a8583  lock dec dword ptr [rsi+8] ; 0x66a85a1  mov rax,[rax+8] ; 0x66a85ba  lock dec dword ptr [rsi+8] ; 0x66a85d8  mov rax,[rax+8] | - |
| 0xC | 4 | W [rsi+0xC] dword lock (0x66a8598, 0x66a85cf) | 0x66a8598  lock dec dword ptr [rsi+0xC] ; 0x66a85cf  lock dec dword ptr [rsi+0xC] | - |
| 0x20 | 8 | W [rsp+0x20] (0x66a87f8) | 0x66a87f8  mov qword ptr [rsp+0x20],0 | - |
| 0x1E0 | 16 | W [rbp+0x1E0] (0x66a8649) | 0x66a8649  movaps [rbp+0x1E0],xmm0 | - |
| 0x1F0 | 16 | W [rbp+0x1F0] (0x66a86b1) | 0x66a86b1  movaps [rbp+0x1F0],xmm0 | - |
| 0x248 | 8 | W [rbp+0x248] (0x66a8657) | 0x66a8657  mov [rbp+0x248],rax | - |
| 0x250 | 8 | W [rbp+0x250] (0x66a865e) | 0x66a865e  mov qword ptr [rbp+0x250],0xC | - |
| 0x258 | 8 | W [rbp+0x258] (0x66a86bf) | 0x66a86bf  mov [rbp+0x258],rax | - |
| 0x260 | 8 | W [rbp+0x260] (0x66a86c6) | 0x66a86c6  mov qword ptr [rbp+0x260],0xD | - |
| 0x278 | 8 | R [rbp+0x278] (0x66a8577) | 0x66a8577  mov rsi,[rbp+0x278] | - |
| 0x350 | 8 | R [rbp+0x350] (0x66a85ae) | 0x66a85ae  mov rsi,[rbp+0x350] | - |
| 0x360 | 8 | R [rbp+0x360] (0x66a87c4) | 0x66a87c4  mov rdi,[rbp+0x360] | - |
| 0x370 | 8 | R [rbp+0x370] (0x66a87b3) | 0x66a87b3  mov r8,[rbp+0x370] | - |
| 0x378 | 8 | R [rbp+0x378] (0x66a87ba) | 0x66a87ba  cmp qword ptr [rbp+0x378],0x10 | - |
| 0x560 | 8 | R [rbp+0x560] (0x66a8537) | 0x66a8537  mov rcx,[rbp+0x560] | - |
| 0x570 | 8 | R [rbp+0x570] (0x66a8543) | 0x66a8543  mov rdx,[rbp+0x570] | - |
| 0x590 | 16 | R [rbp+0x590] (0x66a85e5) | 0x66a85e5  movaps xmm6,[rbp+0x590] | - |
| 0x5A0 | 16 | R [rbp+0x5A0] (0x66a85ec) | 0x66a85ec  movaps xmm7,[rbp+0x5A0] | - |
| 0x5B0 | 16 | R [rbp+0x5B0] (0x66a85f3) | 0x66a85f3  movaps xmm8,[rbp+0x5B0] | - |
| 0x5C0 | 16 | R [rbp+0x5C0] (0x66a85fb) | 0x66a85fb  movaps xmm9,[rbp+0x5C0] | - |
| 0x5D0 | 16 | R [rbp+0x5D0] (0x66a8603) | 0x66a8603  movaps xmm10,[rbp+0x5D0] | - |

## TOOL REQUESTS

None | — | No helper scripts were needed; the input listing was precomputed by the orchestrator and `python tools/delegate.py check` (verify_oc against the exe) confirms the verbatim quoting.
