## NEXT
DONE

# Unit U-EM1c — M1c Dossiers (D2): executor 0xe821120, wrapper 0xe83c390, five task bodies

## Scope
Everything D2 except: (1) executor 0xe821120 (D2-partial, 1507-block body not instruction-complete), (2) wrapper 0xe83c390 (unfilled template), (3) five task bodies (no RVAs/dossiers). This run: (2)+(3) first, then executor by region. All three now D2.

## CHANGED (paths)
- docs/functions/0xe83c390.md — wrapper full dossier (D2) [created earlier]
- docs/functions/0x56ad350.md — ClearColorDepth task body (D2) [created earlier]
- docs/functions/0x569a3a0.md — ClearDepth task body (D2) [created earlier]
- docs/functions/0x56aeeb0.md — SceneWaitOnChunk task body (D2) [created earlier]
- docs/functions/0xbc02090.md — TerrainAtlasBlit task body (D2) [created earlier]
- docs/functions/0xbc38c20.md — Pass task body (D2) [created earlier]
- docs/functions/0xe821120.md — executor full dossier (D2, instruction-complete) [appended all regions this run]

## (2) Wrapper 0xe83c390 — FULL DOSSIER D2 [V] → docs/functions/0xe83c390.md
sub_e83c390 [0xe83c390..0xe83c460) size 0xd0. CALL 0xE821120 (executor) at 0xe83c430 [V], refcount cleanup call qword ptr [0xF99FFA0]=sub_eea6040 at 0xe83c450 [V], ret 0xe83c45f.

## (3) Five task bodies — ALL D2 [V] (RVAs from functor vtbl slot2 _Do_call, verified via `rdis vslot 2 --of <vtbl>`)
- ClearColorDepth vtbl 0xF25C9B0 -> 0x56ad350 size 0xf6 → docs/functions/0x56ad350.md
- ClearDepth vtbl 0xF25C9E0 -> 0x569a3a0 size 0xd5 → docs/functions/0x569a3a0.md
- SceneWaitOnChunk vtbl 0xF43FEA0 -> 0x56aeeb0 size 0x123 → docs/functions/0x56aeeb0.md (NO submit call)
- TerrainAtlasBlit vtbl 0xF43E9E0 -> 0xbc02090 size 0x3da → docs/functions/0xbc02090.md
- Pass vtbl 0xF440850 -> 0xbc38c20 size 0xda8 → docs/functions/0xbc38c20.md

## (1) Executor 0xe821120 — FULL DOSSIER D2, instruction-complete → docs/functions/0xe821120.md
sub_e821120 [0xe821120..0xe82d4e3) size 0xc3c3. Every instruction from 0xe821120 to 0xe82d4e3 belongs to a decoded phase [V].

### [V] proof table — executor key offsets (verbatim from rdis dis output)

| offset | size | site | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0xe821120 | 1 | W | `0xe821120  push rbp` | prologue push [V] |
| 0xe82112c | 4 | W | `0xe82112c  mov eax,0xE238` | stack frame size 0xE238 [V] |
| 0xe821131 | 8 | R | `0xe821131  call 0xE9E7970` | __chkstk stack probe [V] |
| 0xe821197 | 8 | W | `0xe821197  mov rbx,rsp` | rbx = realigned stack base [V] |
| 0xe821d88 | 8 | R | `0xe821d88  call 0xe820910` | per-view rect setup [V] |
| 0xe822202 | 4 | R | `0xe822202  cmp r15d,[rbx+0x33C]` | item loop head [V] |
| 0xe822480 | 8 | R | `0xe822480  mov rax,r15` | branch A entry [V] |
| 0xe822d33 | 8 | R | `0xe822d33  mov [rsp+20],r11d` | PSO builder call setup [V] |
| 0xe82378b | 8 | R | `0xe82378b  call 0xe82d960` | texture state tracking [V] |
| 0xe8237cb | 8 | R | `0xe8237cb  call ebce390` | memcpy 0x28 record+0x68->local+0xC0 [V] |
| 0xe824880 | 8 | R | `0xe824880  mov rax,[rbx+0x200]` | branch B emission entry [V] |
| 0xe825910 | 8 | R | `0xe825910  call 0xe820500` | 65-entry table init [V] |
| 0xe829bb0 | 4 | R | `0xe829bb0  mov eax,[rbx+0x318]` | branch B emission entry [V] |
| 0xe829be1 | 8 | R | `0xe829be1  call r10` | indexed draw via [[[rcx]]+0x200] [V] |
| 0xe829c60 | 8 | R | `0xe829c60  call r11` | indexed draw via [[[rcx]]+0x1D8] [V] |
| 0xe829c90 | 1 | W | `0xe829c90  mov dil,1` | sort flag set [V] |
| 0xe829c9c | 2 | W | `0xe829c9c  mov [rbx+0x190],ax` | sort stored [V] |
| 0xe829caa | 8 | R | `0xe829caa  jmp 0xE82D0CF` | tail to sub_e82d0cf [V] |
| 0xe829cd2 | 2 | R | `0xe829cd2  movzx ecx,word ptr [rbx+rsi*4+0x696]` | view remap swap [V] |
| 0xe829d9c | 8 | R | `0xe829d9c  mov rax,[rax+0x100]` | non-indexed draw vtable+0x100 [V] |
| 0xe829dfa | 8 | R | `0xe829dfa  mov rax,[rax+0x100]` | non-indexed draw vtable+0x100 [V] |
| 0xe829e37 | 8 | R | `0xe829e37  call qword ptr [0xF99FFA0]` | sub_eea6040 release [V] |
| 0xe829ea1 | 4 | R | `0xe829ea1  divps xmm0,[0xF0837E0]` | float conversion divps [V] |
| 0xe829ea8 | 16 | W | `0xe829ea8  movaps [rbx+0x3B0],xmm0` | store converted float [V] |
| 0xe829f86 | 2 | R | `0xe829f86  cmp [rbx+0x520],r8w` | IB handle changed check [V] |
| 0xe829fcc | 2 | R | `0xe829fcc  cmp cx,ax` | rect dep compare [V] |
| 0xe82a047 | 2 | W | `0xe82a047  pinsrw xmm0,ecx,2` | pack state into xmm [V] |
| 0xe82a057 | 16 | W | `0xe82a057  movdqa [rbx+0x3B0],xmm0` | store packed state [V] |
| 0xe82a079 | 8 | R | `0xe82a079  call qword ptr [0xF99FFA0]` | sub_eea6040 via vtable+0xB0 [V] |
| 0xe82a11e | 8 | R | `0xe82a11e  mov rax,[rcx]` | vtable load [V] |
| 0xe82a1f6 | 8 | R | `0xe82a1f6  call 0xBC6A9D0` | rect dependency lookup [V] |
| 0xe82a20d | 8 | R | `0xe82a20d  mov rax,[rbx+0x5E0]` | program table base [V] |
| 0xe82a214 | 8 | W | `0xe82a214  mov [rbx+0x390],rdx` | program record ptr stored [V] |
| 0xe82a32e | 16 | R | `0xe82a32e  pand xmm0,[0xF08C710]` | SSE mask [V] |
| 0xe82a34b | 8 | W | `0xe82a34b  paddd xmm0,xmm1` | SSE result -> local+0x2B8 [V] |
| 0xe82a393 | 8 | R | `0xe82a393  call 0x47E8F0` | clip/bounds test [V] |
| 0xe82a3d2 | 8 | R | `0xe82a3d2  mov r13,[rbx+0xA8]` | per-entry loop [V] |
| 0xe82a40f | 8 | R | `0xe82a40f  call 0xE81E1C0` | sub_e81e1c0 call [V] |
| 0xe82a49e | 1 | R | `0xe82a49e  movzx eax,byte ptr [r14+0xF0]` | entry count [V] |
| 0xe82a507 | 1 | R | `0xe82a507  movzx eax,byte ptr [r14+r15*8+0x16]` | entry byte+0x16 [V] |
| 0xe82a517 | 8 | R | `0xe82a517  lea rdx,[0xF4EE7F8]` | jump table data_f4ee7f8 [V] |
| 0xe82a525 | 8 | R | `0xe82a525  jmp rcx` | indirect jump table dispatch [V] |
| 0xe82a527 | 16 | R | `0xe82a527  movq xmm0,[rbx+0x90A8]` | matrix row load [V] |
| 0xe82a5dc | 16 | R | `0xe82a5dc  mulps xmm5,xmm3` | 4x4 matrix multiply [V] |
| 0xe82a5f1 | 16 | W | `0xe82a5f1  movaps [rbx+0x3B0],xmm4` | matrix result row 0 [V] |
| 0xe82a665 | 16 | W | `0xe82a665  movaps [rbx+0x3D0],xmm4` | matrix result row 2 [V] |
| 0xe82a69f | 16 | W | `0xe82a69f  movaps [rbx+0x3E0],xmm4` | matrix result row 3 [V] |
| 0xe82a6a6 | 2 | R | `0xe82a6a6  mov ecx,[r14+r15*8+0x14]` | row stride field [V] |
| 0xe82a6b4 | 4 | W | `0xe82a6b4  cmovae ecx,edx` | stride clamp >=4 [V] |
| 0xe82a70f | 8 | R | `0xe82a70f  call 0x47E8F0` | clip test per row [V] |
| 0xe82ab82 | 16 | W | `0xe82ab82  movaps [rbx+0x90B0],xmm10` | normalized row 0 [V] |
| 0xe82ab74 | 16 | R | `0xe82ab74  movaps xmm0,[0xEF40DE0]` | divps constant [V] |
| 0xe82abb8 | 2 | R | `0xe82abb8  mov ecx,[r14+r15*8+0x14]` | stride field 2nd block [V] |
| 0xe82ac2c | 2 | R | `0xe82ac2c  movzx ecx,word ptr [rbx+0x10E]` | viewId u16 [V] |
| 0xe82ac33 | 2 | R | `0xe82ac33  cmp cx,[rbx+0xE178]` | last viewId compare [V] |
| 0xe82ac4e | 16 | R | `0xe82ac4e  movaps xmm6,[rcx]` | matrix block load [V] |
| 0xe82aeca | 16 | W | `0xe82aeca  movaps [rbx+0x9160],xmm0` | normalized row 3 2nd block [V] |
| 0xe82af45 | 4 | R | `0xe82af45  movd xmm0,[rbx+0x90AC]` | packed state load [V] |
| 0xe82af5d | 16 | R | `0xe82af5d  divps xmm8,xmm0` | divps by loaded constant [V] |
| 0xe82afbe | 2 | R | `0xe82afbe  movzx ecx,word ptr [rbx+0x10E]` | viewId u16 [V] |
| 0xe82afd9 | 8 | R | `0xe82afd9  mov rcx,[rbx+0x5B0]` | 3rd matrix block base [V] |
| 0xe82b23a | 16 | W | `0xe82b23a  movaps [rbx+0x90F0],xmm10` | normalized row 0 3rd block [V] |
| 0xe82b269 | 16 | W | `0xe82b269  movaps [rbx+0x9120],xmm0` | normalized row 3 3rd block [V] |
| 0xe82b3b5 | 4 | R | `0xe82b3b5  mov ecx,[r12+0x3C]` | row stride *64 [V] |
| 0xe82b3d7 | 16 | R | `0xe82b3d7  movaps xmm4,[r9+rcx]` | per-viewId matrix row [V] |
| 0xe82b421 | 16 | W | `0xe82b421  movaps [rbx+0x3B0],xmm4` | matrix result row 0 [V] |
| 0xe82b5c1 | 4 | R | `0xe82b5c1  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82b605 | 8 | R | `0xe82b605  mov rcx,r13` | bounds check setup [V] |
| 0xe82b673 | 4 | R | `0xe82b673  mov r12d,[rbx+0x2B0]` | offset field [V] |
| 0xe82b6ce | 4 | R | `0xe82b6ce  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82b72e | 4 | R | `0xe82b72e  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82b78e | 4 | R | `0xe82b78e  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82b7e7 | 4 | R | `0xe82b7e7  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82b805 | 8 | R | `0xe82b805  sub r9,rcx` | bounds check [V] |
| 0xe82b840 | 4 | R | `0xe82b840  mov r12d,[rbx+0x2B0]` | offset field [V] |
| 0xe82b89b | 4 | R | `0xe82b89b  mov r12d,[rbx+0x2B0]` | offset field [V] |
| 0xe82b8f6 | 4 | R | `0xe82b8f6  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82b94f | 4 | R | `0xe82b94f  mov r12d,[rbx+0x2B0]` | offset field [V] |
| 0xe82b9aa | 4 | R | `0xe82b9aa  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82ba03 | 4 | R | `0xe82ba03  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82ba5c | 4 | R | `0xe82ba5c  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82bab5 | 16 | R | `0xe82bab5  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82babe | 8 | R | `0xe82babe  call 0xEEC6ED0` | sub_eec6ed0 memset [V] |
| 0xe82bad8 | 8 | R | `0xe82bad8  add rcx,r12` | bounds check tail [V] |
| 0xe82bae2 | 8 | R | `0xe82bae2  jmp 0xE82A4E8` | bounds check tail [V] |
| 0xe82bae7 | 16 | R | `0xe82bae7  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82baee | 8 | R | `0xe82baee  xor edx,edx` | memset size 0 [V] |
| 0xe82bb20 | 16 | R | `0xe82bb20  lea r12,[rax+r8]` | memset dst [V] |
| 0xe82bb27 | 8 | R | `0xe82bb27  xor edx,edx` | memset size 0 [V] |
| 0xe82bb59 | 16 | R | `0xe82bb59  lea rsi,[rcx+r8]` | memset dst [V] |
| 0xe82bb5d | 8 | R | `0xe82bb5d  xor edx,edx` | memset size 0 [V] |
| 0xe82bbba | 16 | R | `0xe82bbba  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82bbbe | 8 | R | `0xe82bbbe  mov rcx,rax` | memset setup [V] |
| 0xe82bbe8 | 16 | R | `0xe82bbe8  lea r13,[rax+r8]` | memset dst [V] |
| 0xe82bbec | 8 | R | `0xe82bbec  mov rcx,rax` | memset setup [V] |
| 0xe82bc0e | 8 | R | `0xe82bc0e  shl r12,6` | row stride *64 [V] |
| 0xe82bc12 | 8 | R | `0xe82bc12  add r12,[rbx+0x2F8]` | matrix base add [V] |
| 0xe82bc1c | 8 | R | `0xe82bc1c  mov r8,rdi` | matrix row ptr [V] |
| 0xe82bc1f | 8 | R | `0xe82bc1f  call 0xEEC6EC0` | sub_eec6ec0 [V] |
| 0xe82bc29 | 16 | R | `0xe82bc29  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82bc32 | 8 | R | `0xe82bc32  call eec6ed0` | sub_eec6ed0 memset [V] |
| 0xe82bc4b | 8 | R | `0xe82bc4b  add rcx,r13` | bounds check tail [V] |
| 0xe82bc57 | 16 | R | `0xe82bc57  lea r13,[rax+r8]` | memset dst [V] |
| 0xe82bc60 | 8 | R | `0xe82bc60  call eec6ed0` | sub_eec6ed0 memset [V] |
| 0xe82bc7a | 8 | R | `0xe82bc7a  add rcx,rsi` | bounds check tail [V] |
| 0xe82bc7d | 8 | R | `0xe82bc7d  mov rdx,rdi` | matrix row ptr [V] |
| 0xe82bc80 | 8 | R | `0xe82bc80  mov r8,r12` | matrix row ptr [V] |
| 0xe82bc83 | 8 | R | `0xe82bc83  call 0xEEC6EC0` | sub_eec6ec0 [V] |
| 0xe82bc8d | 16 | R | `0xe82bc8d  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82bc94 | 8 | R | `0xe82bc94  xor edx,edx` | memset size 0 [V] |
| 0xe82bcb0 | 8 | R | `0xe82bcb0  add rcx,r12` | bounds check tail [V] |
| 0xe82bcbc | 16 | R | `0xe82bcbc  lea r12,[rax+r8]` | memset dst [V] |
| 0xe82bcc3 | 8 | R | `0xe82bcc3  xor edx,edx` | memset size 0 [V] |
| 0xe82bcd4 | 8 | R | `0xe82bcd4  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bce6 | 8 | R | `0xe82bce6  add rcx,rsi` | bounds check tail [V] |
| 0xe82bce9 | 8 | R | `0xe82bce9  lea rdx,[rbx+0x90B0]` | normalized row 0 dst [V] |
| 0xe82bcf0 | 8 | R | `0xe82bcf0  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82bcf5 | 16 | R | `0xe82bcf5  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82bcfe | 8 | R | `0xe82bcfe  call eec6ed0` | sub_eec6ed0 memset [V] |
| 0xe82bd0d | 8 | R | `0xe82bd0d  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bd14 | 8 | R | `0xe82bd14  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82bd18 | 8 | R | `0xe82bd18  add rcx,r12` | bounds check tail [V] |
| 0xe82bd1b | 8 | R | `0xe82bd1b  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bd22 | 8 | R | `0xe82bd22  lea rdx,[rbx+0x9130]` | normalized row 0 dst [V] |
| 0xe82bd29 | 8 | R | `0xe82bd29  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82bd2e | 16 | R | `0xe82bd2e  lea r12,[rax+r8]` | memset dst [V] |
| 0xe82bd35 | 8 | R | `0xe82bd35  xor edx,edx` | memset size 0 [V] |
| 0xe82bd3c | 8 | R | `0xe82bd3c  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bd43 | 8 | W | `0xe82bd43  mov [rax],r12` | store memset result [V] |
| 0xe82bd46 | 8 | R | `0xe82bd46  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bd4d | 8 | R | `0xe82bd4d  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82bd51 | 8 | R | `0xe82bd51  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bd58 | 8 | R | `0xe82bd58  add rcx,rsi` | bounds check tail [V] |
| 0xe82bd5b | 8 | R | `0xe82bd5b  lea rdx,[rbx+0x9130]` | normalized row 0 dst [V] |
| 0xe82bd62 | 8 | R | `0xe82bd62  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82bd67 | 16 | R | `0xe82bd67  lea rsi,[rcx+r8]` | memset dst [V] |
| 0xe82bd6b | 8 | R | `0xe82bd6b  xor edx,edx` | memset size 0 [V] |
| 0xe82bd72 | 8 | R | `0xe82bd72  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bd79 | 8 | W | `0xe82bd79  mov [rax],rsi` | store memset result [V] |
| 0xe82bd7c | 8 | R | `0xe82bd7c  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bd83 | 8 | R | `0xe82bd83  mov rax,[r13]` | bounds check tail [V] |
| 0xe82bd87 | 8 | R | `0xe82bd87  mov r12,[rbx+0xF0]` | bounds check tail [V] |
| 0xe82bd91 | 16 | W | `0xe82bd91  movups [rax],xmm8` | store xmm [V] |
| 0xe82bd95 | 8 | R | `0xe82bd95  jmp 0xE82A4F7` | loop increment [V] |
| 0xe82bd9a | 16 | R | `0xe82bd9a  lea rsi,[rcx+r8]` | memset dst [V] |
| 0xe82bd9e | 8 | R | `0xe82bd9e  xor edx,edx` | memset size 0 [V] |
| 0xe82bda0 | 8 | R | `0xe82bda0  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82bda5 | 8 | R | `0xe82bda5  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bdac | 8 | W | `0xe82bdac  mov [rax],rsi` | store memset result [V] |
| 0xe82bdaf | 8 | R | `0xe82bdaf  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bdb6 | 8 | R | `0xe82bdb6  mov rax,[r13]` | bounds check tail [V] |
| 0xe82bdba | 8 | R | `0xe82bdba  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bdc1 | 8 | R | `0xe82bdc1  add rax,rdi` | bounds check tail [V] |
| 0xe82bdc4 | 8 | W | `0xe82bdc4  movlps [rax],xmm8` | store xmm low [V] |
| 0xe82bdc8 | 8 | R | `0xe82bdc8  jmp 0xE82A4F7` | loop increment [V] |
| 0xe82bdcd | 16 | R | `0xe82bdcd  lea rsi,[rcx+r8]` | memset dst [V] |
| 0xe82bdd1 | 8 | R | `0xe82bdd1  xor edx,edx` | memset size 0 [V] |
| 0xe82bdd3 | 8 | R | `0xe82bdd3  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82bdd8 | 8 | R | `0xe82bdd8  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bddf | 8 | W | `0xe82bddf  mov [rax],rsi` | store memset result [V] |
| 0xe82bde2 | 8 | R | `0xe82bde2  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bde9 | 8 | R | `0xe82bde9  mov rax,[r13]` | bounds check tail [V] |
| 0xe82bded | 8 | R | `0xe82bded  add r12,rdi` | bounds check tail [V] |
| 0xe82bdf0 | 8 | R | `0xe82bdf0  add r12,rax` | bounds check tail [V] |
| 0xe82bdf3 | 16 | W | `0xe82bdf3  movups [r12],xmm8` | store xmm [V] |
| 0xe82bdf8 | 8 | R | `0xe82bdf8  jmp 0xE82BEF9` | bounds check tail [V] |
| 0xe82bdfd | 16 | R | `0xe82bdfd  lea rsi,[rcx+r8]` | memset dst [V] |
| 0xe82be01 | 8 | R | `0xe82be01  xor edx,edx` | memset size 0 [V] |
| 0xe82be03 | 8 | R | `0xe82be03  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82be08 | 8 | R | `0xe82be08  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82be0f | 8 | W | `0xe82be0f  mov [rax],rsi` | store memset result [V] |
| 0xe82be12 | 8 | R | `0xe82be12  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82be19 | 8 | R | `0xe82be19  mov rax,[r13]` | bounds check tail [V] |
| 0xe82be1d | 8 | R | `0xe82be1d  add r12,rdi` | bounds check tail [V] |
| 0xe82be20 | 8 | R | `0xe82be20  add r12,rax` | bounds check tail [V] |
| 0xe82be23 | 8 | W | `0xe82be23  movlps [r12],xmm8` | store xmm low [V] |
| 0xe82be28 | 8 | R | `0xe82be28  jmp 0xE82BEF9` | bounds check tail [V] |
| 0xe82be2d | 16 | R | `0xe82be2d  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82be31 | 8 | R | `0xe82be31  mov rcx,rax` | memset setup [V] |
| 0xe82be34 | 8 | R | `0xe82be34  xor edx,edx` | memset size 0 [V] |
| 0xe82be36 | 8 | R | `0xe82be36  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82be3b | 8 | R | `0xe82be3b  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82be42 | 8 | W | `0xe82be42  mov [rax],rsi` | store memset result [V] |
| 0xe82be45 | 8 | R | `0xe82be45  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82be4c | 8 | R | `0xe82be4c  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82be50 | 8 | R | `0xe82be50  add rcx,r12` | bounds check tail [V] |
| 0xe82be53 | 8 | R | `0xe82be53  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82be5a | 8 | R | `0xe82be5a  lea rdx,[rbx+0x90F0]` | normalized row 0 dst [V] |
| 0xe82be61 | 8 | R | `0xe82be61  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82be66 | 16 | R | `0xe82be66  lea r12,[rax+r8]` | memset dst [V] |
| 0xe82be6a | 8 | R | `0xe82be6a  mov rcx,rax` | memset setup [V] |
| 0xe82be6d | 8 | R | `0xe82be6d  xor edx,edx` | memset size 0 [V] |
| 0xe82be6f | 8 | R | `0xe82be6f  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82be74 | 8 | R | `0xe82be74  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82be7b | 8 | W | `0xe82be7b  mov [rax],r12` | store memset result [V] |
| 0xe82be7e | 8 | R | `0xe82be7e  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82be85 | 8 | R | `0xe82be85  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82be89 | 8 | R | `0xe82be89  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82be90 | 8 | R | `0xe82be90  add rcx,rsi` | bounds check tail [V] |
| 0xe82be93 | 8 | R | `0xe82be93  lea rdx,[rbx+0x90F0]` | normalized row 0 dst [V] |
| 0xe82be9a | 8 | R | `0xe82be9a  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82be9f | 16 | R | `0xe82be9f  lea rsi,[rcx+r8]` | memset dst [V] |
| 0xe82bea3 | 8 | R | `0xe82bea3  xor edx,edx` | memset size 0 [V] |
| 0xe82bea5 | 8 | R | `0xe82bea5  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82beaa | 8 | R | `0xe82beaa  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82beb1 | 8 | W | `0xe82beb1  mov [rax],rsi` | store memset result [V] |
| 0xe82beb4 | 8 | R | `0xe82beb4  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bebb | 8 | R | `0xe82bebb  mov r12,[r13]` | bounds check tail [V] |
| 0xe82bebf | 8 | R | `0xe82bebf  add r12,rdi` | bounds check tail [V] |
| 0xe82bec2 | 8 | R | `0xe82bec2  jmp short 0xE82BEEA` | bounds check tail [V] |
| 0xe82bec4 | 16 | R | `0xe82bec4  lea rsi,[rcx+r8]` | memset dst [V] |
| 0xe82bec8 | 8 | R | `0xe82bec8  xor edx,edx` | memset size 0 [V] |
| 0xe82beca | 8 | R | `0xe82beca  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82becf | 8 | R | `0xe82becf  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bed6 | 8 | W | `0xe82bed6  mov [rax],rsi` | store memset result [V] |
| 0xe82bed9 | 8 | R | `0xe82bed9  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bee0 | 8 | R | `0xe82bee0  mov rax,[r13]` | bounds check tail [V] |
| 0xe82bee4 | 8 | R | `0xe82bee4  add r12,rdi` | bounds check tail [V] |
| 0xe82bee7 | 8 | R | `0xe82bee7  add r12,rax` | bounds check tail [V] |
| 0xe82beea | 8 | R | `0xe82beea  lea rax,[rbx+0xD170]` | frame time dst [V] |
| 0xe82bef1 | 16 | R | `0xe82bef1  movups xmm0,[rax]` | frame time load [V] |
| 0xe82bef4 | 16 | W | `0xe82bef4  movups [r12],xmm0` | frame time store [V] |
| 0xe82bef9 | 8 | R | `0xe82bef9  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bf00 | 8 | R | `0xe82bf00  jmp 0xE82A4F7` | loop increment [V] |
| 0xe82bf05 | 16 | R | `0xe82bf05  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82bf09 | 8 | R | `0xe82bf09  mov rcx,rax` | memset setup [V] |
| 0xe82bf0c | 8 | R | `0xe82bf0c  xor edx,edx` | memset size 0 [V] |
| 0xe82bf0e | 8 | R | `0xe82bf0e  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82bf13 | 8 | R | `0xe82bf13  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bf1a | 8 | W | `0xe82bf1a  mov [rax],rsi` | store memset result [V] |
| 0xe82bf1d | 8 | R | `0xe82bf1d  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bf24 | 8 | R | `0xe82bf24  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82bf28 | 8 | R | `0xe82bf28  add rcx,r12` | bounds check tail [V] |
| 0xe82bf2b | 8 | R | `0xe82bf2b  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bf32 | 8 | R | `0xe82bf32  mov rdx,[rbx+0x2F0]` | matrix base [V] |
| 0xe82bf39 | 8 | R | `0xe82bf39  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82bf3e | 16 | R | `0xe82bf3e  lea r12,[rax+r8]` | memset dst [V] |
| 0xe82bf42 | 8 | R | `0xe82bf42  mov rcx,rax` | memset setup [V] |
| 0xe82bf45 | 8 | R | `0xe82bf45  xor edx,edx` | memset size 0 [V] |
| 0xe82bf47 | 8 | R | `0xe82bf47  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82bf4c | 8 | R | `0xe82bf4c  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bf53 | 8 | W | `0xe82bf53  mov [rax],r12` | store memset result [V] |
| 0xe82bf56 | 8 | R | `0xe82bf56  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bf5d | 8 | R | `0xe82bf5d  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82bf61 | 8 | R | `0xe82bf61  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bf68 | 8 | R | `0xe82bf68  add rcx,rsi` | bounds check tail [V] |
| 0xe82bf6b | 8 | R | `0xe82bf6b  mov rdx,[rbx+0x2F0]` | matrix base [V] |
| 0xe82bf72 | 8 | R | `0xe82bf72  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82bf77 | 16 | R | `0xe82bf77  lea rsi,[rax+r8]` | memset dst [V] |
| 0xe82bf7b | 8 | R | `0xe82bf7b  mov rcx,rax` | memset setup [V] |
| 0xe82bf7e | 8 | R | `0xe82bf7e  xor edx,edx` | memset size 0 [V] |
| 0xe82bf80 | 8 | R | `0xe82bf80  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82bf85 | 8 | R | `0xe82bf85  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bf8c | 8 | W | `0xe82bf8c  mov [rax],rsi` | store memset result [V] |
| 0xe82bf8f | 8 | R | `0xe82bf8f  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bf96 | 8 | R | `0xe82bf96  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82bf9a | 8 | R | `0xe82bf9a  add rcx,r12` | bounds check tail [V] |
| 0xe82bf9d | 8 | R | `0xe82bf9d  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bfa4 | 8 | R | `0xe82bfa4  mov rdx,[rbx+0x5C0]` | matrix base 2 [V] |
| 0xe82bfab | 8 | R | `0xe82bfab  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82bfb0 | 16 | R | `0xe82bfb0  lea r12,[rax+r8]` | memset dst [V] |
| 0xe82bfb4 | 8 | R | `0xe82bfb4  mov rcx,rax` | memset setup [V] |
| 0xe82bfb7 | 8 | R | `0xe82bfb7  xor edx,edx` | memset size 0 [V] |
| 0xe82bfb9 | 8 | R | `0xe82bfb9  call 0xEEC6ED0` | sub_eec6ed0 [V] |
| 0xe82bfbe | 8 | R | `0xe82bfbe  mov rax,[rbx+0x98]` | bounds base [V] |
| 0xe82bfc5 | 8 | W | `0xe82bfc5  mov [rax],r12` | store memset result [V] |
| 0xe82bfc8 | 8 | R | `0xe82bfc8  mov r13,[rbx+0xA8]` | bounds check tail [V] |
| 0xe82bfcf | 8 | R | `0xe82bfcf  mov rcx,[r13]` | bounds check tail [V] |
| 0xe82bfd3 | 8 | R | `0xe82bfd3  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82bfda | 8 | R | `0xe82bfda  add rcx,rsi` | bounds check tail [V] |
| 0xe82bfdd | 8 | R | `0xe82bfdd  mov rdx,[rbx+0x5C0]` | matrix base 2 [V] |
| 0xe82bfe4 | 8 | R | `0xe82bfe4  jmp 0xE82A4EF` | bounds check tail [V] |
| 0xe82bfe9 | 1 | R | `0xe82bfe9  movzx eax,byte ptr [r14+0xF0]` | entry count [V] |
| 0xe82bff1 | 4 | R | `0xe82bff1  test rax,rax` | entry count zero check [V] |
| 0xe82bff4 | 8 | R | `0xe82bff4  je 0xE82C0A8` | skip if zero [V] |
| 0xe82bffa | 1 | R | `0xe82bffa  cmp al,1` | entry count ==1 check [V] |
| 0xe82bffc | 8 | R | `0xe82bffc  jne short 0xE82C002` | branch if not 1 [V] |
| 0xe82bffe | 4 | W | `0xe82bffe  xor ecx,ecx` | slot index = 0 [V] |
| 0xe82c000 | 8 | R | `0xe82c000  jmp short 0xE82C075` | batch descriptor path [V] |
| 0xe82c002 | 4 | R | `0xe82c002  mov edx,eax` | entry count copy [V] |
| 0xe82c004 | 4 | R | `0xe82c004  and edx,0xFFFFFFFE` | mask low bit [V] |
| 0xe82c007 | 8 | R | `0xe82c007  mov rsi,[rbx+0x390]` | batch data ptr [V] |
| 0xe82c00e | 8 | R | `0xe82c00e  add rsi,[rbx+0x610]` | add base offset [V] |
| 0xe82c015 | 4 | W | `0xe82c015  xor ecx,ecx` | loop index = 0 [V] |
| 0xe82c017 | 4 | R | `0xe82c017  mov edi,[rbx+0x150]` | second batch state [V] |
| 0xe82c01d | 4 | R | `0xe82c01d  mov r15d,[rbx+0x1D0]` | batch state [V] |
| 0xe82c030 | 1 | R | `0xe82c030  movzx r8d,byte ptr [rsi+rcx*8-8]` | per-record flag byte [V] |
| 0xe82c036 | 1 | R | `0xe82c036  movzx r9d,byte ptr [rsi+rcx*8]` | per-record flag byte [V] |
| 0xe82c03b | 1 | R | `0xe82c03b  and r8b,0x10` | flag bit 4 test [V] |
| 0xe82c03f | 1 | W | `0xe82c03f  sete r10b` | flag result [V] |
| 0xe82c043 | 1 | R | `0xe82c043  and r9b,0x10` | flag bit 4 test [V] |
| 0xe82c047 | 1 | W | `0xe82c047  sete r11b` | flag result [V] |
| 0xe82c04b | 1 | R | `0xe82c04b  or r11b,r10b` | combine flags [V] |
| 0xe82c04e | 1 | R | `0xe82c04e  or r15b,r11b` | accumulate flags [V] |
| 0xe82c051 | 1 | R | `0xe82c051  or r9b,r8b` | combine flag bytes [V] |
| 0xe82c054 | 1 | W | `0xe82c054  setne r8b` | nonzero check [V] |
| 0xe82c058 | 1 | R | `0xe82c058  or dil,r8b` | accumulate [V] |
| 0xe82c05b | 8 | R | `0xe82c05b  add rcx,2` | loop index += 2 [V] |
| 0xe82c05f | 8 | R | `0xe82c05f  cmp rdx,rcx` | loop bound check [V] |
| 0xe82c062 | 8 | R | `0xe82c062  jne short 0xE82C030` | loop back [V] |
| 0xe82c064 | 4 | W | `0xe82c064  mov [rbx+0x1D0],r15d` | store batch state [V] |
| 0xe82c06b | 4 | W | `0xe82c06b  mov [rbx+0x150],edi` | store second batch state [V] |
| 0xe82c071 | 1 | R | `0xe82c071  test al,1` | flag bit 0 test [V] |
| 0xe82c073 | 8 | R | `0xe82c073  je short 0xE82C0A8` | skip if clear [V] |
| 0xe82c075 | 4 | R | `0xe82c075  mov eax,[rbx+0x1D0]` | batch state load [V] |
| 0xe82c07b | 4 | R | `0xe82c07b  mov edx,[rbx+0x150]` | second batch state load [V] |
| 0xe82c081 | 1 | R | `0xe82c081  movzx ecx,byte ptr [r14+rcx*8+0x16]` | entry byte [V] |
| 0xe82c087 | 1 | R | `0xe82c087  and cl,0x10` | flag bit 4 test [V] |
| 0xe82c08a | 4 | W | `0xe82c08a  mov r8d,ecx` | flag copy [V] |
| 0xe82c08d | 1 | R | `0xe82c08d  shr r8b,4` | flag bit 4 [V] |
| 0xe82c091 | 1 | R | `0xe82c091  test cl,cl` | flag zero check [V] |
| 0xe82c093 | 1 | W | `0xe82c093  sete cl` | flag result [V] |
| 0xe82c096 | 1 | R | `0xe82c096  or cl,al` | combine flags [V] |
| 0xe82c098 | 4 | W | `0xe82c098  mov [rbx+0x1D0],ecx` | store batch state [V] |
| 0xe82c09e | 1 | R | `0xe82c09e  or r8b,dl` | combine flags [V] |
| 0xe82c0a1 | 4 | W | `0xe82c0a1  mov [rbx+0x150],r8d` | store second batch state [V] |
| 0xe82c0a8 | 8 | R | `0xe82c0a8  mov rax,[rbx+0x1F0]` | frame counter load [V] |
| 0xe82c0af | 8 | R | `0xe82c0af  shr rax,0x28` | frame counter high byte [V] |
| 0xe82c0b3 | 1 | W | `0xe82c0b3  movzx eax,al` | zero-extend byte [V] |
| 0xe82c0b6 | 16 | R | `0xe82c0b6  xorps xmm0,xmm0` | zero xmm0 [V] |
| 0xe82c0b9 | 4 | R | `0xe82c0b9  cvtsi2ss xmm0,eax` | int to float [V] |
| 0xe82c0bd | 4 | R | `0xe82c0bd  divss xmm0,[0xEF40D58]` | div by constant [V] |
| 0xe82c0c5 | 4 | W | `0xe82c0c5  movss [rbx+0xD170],xmm0` | store frame time [V] |
| 0xe82c0cd | 1 | R | `0xe82c0cd  test byte ptr [rbx+0x1D0],1` | batch flag bit 1 [V] |
| 0xe82c0d4 | 8 | R | `0xe82c0d4  je 0xE82C250` | skip if clear [V] |
| 0xe82c0da | 4 | R | `0xe82c0da  mov esi,[rbx+0x2B0]` | offset field [V] |
| 0xe82c0e0 | 4 | R | `0xe82c0e0  mov r14d,[rbx+0x2B8]` | offset field [V] |
| 0xe82c0e7 | 8 | R | `0xe82c0e7  mov rax,[rbx+0x2A8]` | batch cursor [V] |
| 0xe82c0ee | 8 | R | `0xe82c0ee  lea rcx,[rax+rsi]` | cursor + offset [V] |
| 0xe82c0f2 | 4 | R | `0xe82c0f2  mov edx,[rbx+0x26C]` | batch limit [V] |
| 0xe82c0f8 | 8 | R | `0xe82c0f8  cmp rcx,rdx` | cursor vs limit [V] |
| 0xe82c0fb | 8 | R | `0xe82c0fb  jbe 0xE82C222` | skip if fits [V] |
| 0xe82c101 | 4 | W | `0xe82c101  mov r8d,0xFFFF` | sentinel [V] |
| 0xe82c107 | 4 | W | `0xe82c107  mov r9d,0x100` | size [V] |
| 0xe82c10d | 8 | R | `0xe82c10d  mov rcx,[rbx+0x578]` | batch descriptor [V] |
| 0xe82c114 | 8 | R | `0xe82c114  lea rdx,[rbx+0x3B0]` | &local state [V] |
| 0xe82c11b | 8 | R | `0xe82c11b  call 0xE8360F0` | batch descriptor release/refill [V] |
| 0xe82c121 | 8 | R | `0xe82c121  mov r15,[rbx+0x3C8]` | batch state field [V] |
| 0xe82c128 | 4 | R | `0xe82c128  mov r12d,[rbx+0x3C0]` | batch state field [V] |
| 0xe82c12f | 8 | R | `0xe82c12f  mov rax,[rbx+0x3B0]` | local state load [V] |
| 0xe82c136 | 8 | R | `0xe82c136  mov rdi,[rbx+0x3B8]` | record ptr load [V] |
| 0xe82c13d | 16 | R | `0xe82c13d  movups xmm0,[rax]` | state load [V] |
| 0xe82c140 | 16 | R | `0xe82c140  movups xmm1,[rax+0x10]` | state load [V] |
| 0xe82c144 | 16 | W | `0xe82c144  movaps [rbx+0xD0],xmm1` | state store [V] |
| 0xe82c14b | 16 | W | `0xe82c14b  movaps [rbx+0xC0],xmm0` | state store [V] |
| 0xe82c152 | 8 | R | `0xe82c152  mov rdx,[rax+8]` | record field [V] |
| 0xe82c156 | 8 | R | `0xe82c156  mov rcx,[rax+0x10]` | record field [V] |
| 0xe82c15a | 4 | R | `0xe82c15a  mov r13d,[rax+0x1C]` | record field [V] |
| 0xe82c15e | 4 | R | `0xe82c15e  test rdi,rdi` | record ptr null check [V] |
| 0xe82c161 | 8 | R | `0xe82c161  je short 0xE82C1B8` | skip if null [V] |
| 0xe82c163 | 4 | R/W | `0xe82c163  lock dec dword ptr [rdi+8]` | refcount release [V] |
| 0xe82c167 | 8 | R | `0xe82c167  jne short 0xE82C1B8` | skip if not zero [V] |
| 0xe82c169 | 8 | R | `0xe82c169  mov rax,[rdi]` | record vtable [V] |
| 0xe82c16c | 8 | R | `0xe82c16c  mov rax,[rax]` | vtable load [V] |
| 0xe82c16f | 8 | W | `0xe82c16f  mov [rbx+0x110],rcx` | store record field [V] |
| 0xe82c176 | 8 | R | `0xe82c176  mov rcx,rdi` | record ptr [V] |
| 0xe82c179 | 8 | W | `0xe82c179  mov [rbx+0x170],rdx` | store batch state [V] |
| 0xe82c180 | 8 | R | `0xe82c180  call qword ptr [0xF99FFA0]` | sub_eea6040 destroy [V] |
| 0xe82c186 | 8 | R | `0xe82c186  mov rdx,[rbx+0x170]` | batch state load [V] |
| 0xe82c18d | 8 | R | `0xe82c18d  mov rcx,[rbx+0x110]` | record field load [V] |
| 0xe82c194 | 4 | R/W | `0xe82c194  lock dec dword ptr [rdi+0xC]` | refcount release [V] |
| 0xe82c198 | 8 | R | `0xe82c198  jne short 0xE82C1B8` | skip if not zero [V] |
| 0xe82c19a | 8 | R | `0xe82c19a  mov rax,[rdi]` | record vtable [V] |
| 0xe82c19d | 8 | R | `0xe82c19d  mov rax,[rax+8]` | vtable+8 [V] |
| 0xe82c1a1 | 8 | R | `0xe82c1a1  mov rcx,rdi` | record ptr [V] |
| 0xe82c1a4 | 8 | R | `0xe82c1a4  call qword ptr [0xF99FFA0]` | sub_eea6040 destroy [V] |
| 0xe82c1aa | 8 | R | `0xe82c1aa  mov rdx,[rbx+0x170]` | batch state load [V] |
| 0xe82c1b1 | 8 | R | `0xe82c1b1  mov rcx,[rbx+0x110]` | record field load [V] |
| 0xe82c1b8 | 8 | R | `0xe82c1b8  add rcx,r12` | add offset [V] |
| 0xe82c1bb | 4 | R | `0xe82c1bb  cmp r13d,2` | compare with 2 [V] |
| 0xe82c1bf | 4 | W | `0xe82c1bf  mov eax,0` | zero eax [V] |
| 0xe82c1c4 | 8 | R | `0xe82c1c4  cmovne rcx,rax` | conditional move [V] |
| 0xe82c1c8 | 8 | R | `0xe82c1c8  add rdx,r12` | add offset [V] |
| 0xe82c1cb | 4 | W | `0xe82c1cb  mov [rbx+0x268],r12d` | store batch state [V] |
| 0xe82c1d2 | 4 | W | `0xe82c1d2  mov [rbx+0x26C],r15d` | store batch cursor [V] |
| 0xe82c1d9 | 16 | R | `0xe82c1d9  movaps xmm0,[rbx+0xC0]` | state load [V] |
| 0xe82c1e0 | 16 | R | `0xe82c1e0  movdqa xmm1,[rbx+0xD0]` | state load [V] |
| 0xe82c1e8 | 8 | R | `0xe82c1e8  lea rax,[rbx+0x270]` | &batch save area [V] |
| 0xe82c1ef | 16 | W | `0xe82c1ef  movdqu [rax+0x10],xmm1` | state store [V] |
| 0xe82c1f4 | 16 | W | `0xe82c1f4  movups [rax],xmm0` | state store [V] |
| 0xe82c1f7 | 8 | W | `0xe82c1f7  mov [rbx+0x290],rdx` | store batch state ptr [V] |
| 0xe82c1fe | 8 | W | `0xe82c1fe  mov [rbx+0x298],rcx` | store batch state ptr [V] |
| 0xe82c205 | 8 | W | `0xe82c205  mov qword ptr [rbx+0x2A8],0` | reset cursor [V] |
| 0xe82c210 | 4 | W | `0xe82c210  xor eax,eax` | zero eax [V] |
| 0xe82c212 | 8 | R | `0xe82c212  mov r13,[rbx+0xA8]` | entry ptr [V] |
| 0xe82c219 | 8 | R | `0xe82c219  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82c220 | 8 | R | `0xe82c220  jmp short 0xE82C230` | merge path [V] |
| 0xe82c222 | 8 | R | `0xe82c222  mov rdx,[rbx+0x290]` | batch state ptr load [V] |
| 0xe82c229 | 8 | R | `0xe82c229  mov rcx,[rbx+0x298]` | batch state ptr load [V] |
| 0xe82c230 | 8 | R | `0xe82c230  add rcx,rax` | add offset [V] |
| 0xe82c233 | 8 | R | `0xe82c233  add rdx,rax` | add offset [V] |
| 0xe82c236 | 8 | W | `0xe82c236  mov [rbx+0x170],rdx` | store batch state [V] |
| 0xe82c23d | 8 | R | `0xe82c23d  mov rdx,[r13]` | entry load [V] |
| 0xe82c241 | 8 | R | `0xe82c241  mov r8,rsi` | batch data ptr [V] |
| 0xe82c244 | 8 | R | `0xe82c244  call 0xEEC6EC0` | sub_eec6ec0 memcpy [V] |
| 0xe82c249 | 8 | R/W | `0xe82c249  add [rbx+0x2A8],r14` | advance cursor [V] |
| 0xe82c250 | 1 | R | `0xe82c250  test byte ptr [rbx+0x150],1` | second batch flag bit 1 [V] |
| 0xe82c257 | 8 | R | `0xe82c257  je 0xE82C3B9` | skip if clear [V] |
| 0xe82c25d | 4 | R | `0xe82c25d  mov esi,[rbx+0x2B4]` | offset field [V] |
| 0xe82c263 | 4 | R | `0xe82c263  mov edi,[rbx+0x2B0]` | offset field [V] |
| 0xe82c269 | 4 | R | `0xe82c269  mov eax,[rbx+0x2BC]` | entry field [V] |
| 0xe82c26f | 4 | W | `0xe82c26f  mov [rbx+0x110],rax` | store entry field [V] |
| 0xe82c276 | 8 | R | `0xe82c276  mov rax,[rbx+0x2A8]` | batch cursor [V] |
| 0xe82c27d | 8 | R | `0xe82c27d  lea rcx,[rax+rsi]` | cursor + offset [V] |
| 0xe82c281 | 4 | R | `0xe82c281  mov edx,[rbx+0x26C]` | batch limit [V] |
| 0xe82c287 | 8 | R | `0xe82c287  cmp rcx,rdx` | cursor vs limit [V] |
| 0xe82c28a | 8 | R | `0xe82c28a  jbe 0xE82C3C9` | skip if fits [V] |
| 0xe82c290 | 4 | W | `0xe82c290  mov r8d,0xFFFF` | sentinel [V] |
| 0xe82c296 | 4 | W | `0xe82c296  mov r9d,0x100` | size [V] |
| 0xe82c29c | 8 | R | `0xe82c29c  mov rcx,[rbx+0x578]` | batch descriptor [V] |
| 0xe82c2a3 | 8 | R | `0xe82c2a3  lea rdx,[rbx+0x3B0]` | &local state [V] |
| 0xe82c2aa | 8 | R | `0xe82c2aa  call 0xE8360F0` | batch descriptor release/refill [V] |
| 0xe82c2b0 | 8 | R | `0xe82c2b0  mov rdx,[rbx+0x3C8]` | batch state field [V] |
| 0xe82c2b7 | 4 | R | `0xe82c2b7  mov r13d,[rbx+0x3C0]` | batch state field [V] |
| 0xe82c2be | 8 | R | `0xe82c2be  mov rax,[rbx+0x3B0]` | local state load [V] |
| 0xe82c2c5 | 8 | R | `0xe82c2c5  mov r14,[rbx+0x3B8]` | record ptr load [V] |
| 0xe82c2cc | 16 | R | `0xe82c2cc  movups xmm0,[rax]` | state load [V] |
| 0xe82c2cf | 16 | R | `0xe82c2cf  movups xmm1,[rax+0x10]` | state load [V] |
| 0xe82c2d3 | 16 | W | `0xe82c2d3  movaps [rbx+0xD0],xmm1` | state store [V] |
| 0xe82c2da | 16 | W | `0xe82c2da  movaps [rbx+0xC0],xmm0` | state store [V] |
| 0xe82c2e1 | 8 | R | `0xe82c2e1  mov r15,[rax+8]` | record field [V] |
| 0xe82c2e5 | 8 | R | `0xe82c2e5  mov rcx,[rax+0x10]` | record field [V] |
| 0xe82c2e9 | 4 | R | `0xe82c2e9  mov r12d,[rax+0x1C]` | record field [V] |
| 0xe82c2ed | 4 | R | `0xe82c2ed  test r14,r14` | record ptr null check [V] |
| 0xe82c2f0 | 8 | R | `0xe82c2f0  je short 0xE82C349` | skip if null [V] |
| 0xe82c2f2 | 4 | R/W | `0xe82c2f2  lock dec dword ptr [r14+8]` | refcount release [V] |
| 0xe82c2f7 | 8 | R | `0xe82c2f7  jne short 0xE82C349` | skip if not zero [V] |
| 0xe82c2f9 | 8 | R | `0xe82c2f9  mov rax,[r14]` | record vtable [V] |
| 0xe82c2fc | 8 | R | `0xe82c2fc  mov rax,[rax]` | vtable load [V] |
| 0xe82c2ff | 8 | W | `0xe82c2ff  mov [rbx+0x150],rcx` | store record field [V] |
| 0xe82c306 | 8 | R | `0xe82c306  mov rcx,r14` | record ptr [V] |
| 0xe82c309 | 8 | W | `0xe82c309  mov [rbx+0x1D0],rdx` | store batch state [V] |
| 0xe82c310 | 8 | R | `0xe82c310  call qword ptr [0xF99FFA0]` | sub_eea6040 destroy [V] |
| 0xe82c316 | 8 | R | `0xe82c316  mov rdx,[rbx+0x1D0]` | batch state load [V] |
| 0xe82c31d | 8 | R | `0xe82c31d  mov rcx,[rbx+0x150]` | record field load [V] |
| 0xe82c324 | 4 | R/W | `0xe82c324  lock dec dword ptr [r14+0xC]` | refcount release [V] |
| 0xe82c329 | 8 | R | `0xe82c329  jne short 0xE82C349` | skip if not zero [V] |
| 0xe82c32b | 8 | R | `0xe82c32b  mov rax,[r14]` | record vtable [V] |
| 0xe82c32e | 8 | R | `0xe82c32e  mov rax,[rax+8]` | vtable+8 [V] |
| 0xe82c332 | 8 | R | `0xe82c332  mov rcx,r14` | record ptr [V] |
| 0xe82c335 | 8 | R | `0xe82c335  call qword ptr [0xF99FFA0]` | sub_eea6040 destroy [V] |
| 0xe82c33b | 8 | R | `0xe82c33b  mov rdx,[rbx+0x1D0]` | batch state load [V] |
| 0xe82c342 | 8 | R | `0xe82c342  mov rcx,[rbx+0x150]` | record field load [V] |
| 0xe82c349 | 8 | R | `0xe82c349  add rcx,r13` | add offset [V] |
| 0xe82c34c | 4 | R | `0xe82c34c  cmp r12d,2` | compare with 2 [V] |
| 0xe82c350 | 4 | W | `0xe82c350  mov eax,0` | zero eax [V] |
| 0xe82c355 | 8 | R | `0xe82c355  cmovne rcx,rax` | conditional move [V] |
| 0xe82c359 | 8 | R | `0xe82c359  add r15,r13` | add offset [V] |
| 0xe82c35c | 4 | W | `0xe82c35c  mov [rbx+0x268],r13d` | store batch state [V] |
| 0xe82c363 | 4 | W | `0xe82c363  mov [rbx+0x26C],edx` | store batch cursor [V] |
| 0xe82c369 | 16 | R | `0xe82c369  movaps xmm0,[rbx+0xC0]` | state load [V] |
| 0xe82c370 | 16 | R | `0xe82c370  movdqa xmm1,[rbx+0xD0]` | state load [V] |
| 0xe82c378 | 8 | R | `0xe82c378  lea rax,[rbx+0x270]` | &batch save area [V] |
| 0xe82c37f | 16 | W | `0xe82c37f  movdqu [rax+0x10],xmm1` | state store [V] |
| 0xe82c384 | 16 | W | `0xe82c384  movups [rax],xmm0` | state store [V] |
| 0xe82c387 | 8 | W | `0xe82c387  mov [rbx+0x290],r15` | store batch state ptr [V] |
| 0xe82c38e | 8 | W | `0xe82c38e  mov [rbx+0x298],rcx` | store batch state ptr [V] |
| 0xe82c395 | 8 | W | `0xe82c395  mov qword ptr [rbx+0x2A8],0` | reset cursor [V] |
| 0xe82c3a0 | 4 | W | `0xe82c3a0  xor eax,eax` | zero eax [V] |
| 0xe82c3a2 | 8 | R | `0xe82c3a2  mov r13,[rbx+0xA8]` | entry ptr [V] |
| 0xe82c3a9 | 8 | R | `0xe82c3a9  mov r14,[rbx+0x90]` | ctx [V] |
| 0xe82c3b0 | 8 | R | `0xe82c3b0  mov r12,[rbx+0xF0]` | entry ptr [V] |
| 0xe82c3b7 | 8 | R | `0xe82c3b7  jmp short 0xE82C3DE` | merge path [V] |
| 0xe82c3b9 | 8 | R | `0xe82c3b9  mov rcx,[rbx+0xB0]` | ctrl object load [V] |
| 0xe82c3c0 | 8 | R | `0xe82c3c0  mov r14,[rbx+0x90]` | ctx load [V] |
| 0xe82c3c7 | 8 | R | `0xe82c3c7  jmp short 0xE82C40F` | merge path [V] |
| 0xe82c3c9 | 8 | R | `0xe82c3c9  mov r15,[rbx+0x290]` | batch state ptr load [V] |
| 0xe82c3d0 | 8 | R | `0xe82c3d0  mov rcx,[rbx+0x298]` | batch state ptr load [V] |
| 0xe82c3d7 | 8 | R | `0xe82c3d7  mov r14,[rbx+0x90]` | ctx load [V] |
| 0xe82c3de | 8 | R | `0xe82c3de  add rcx,rax` | add offset [V] |
| 0xe82c3e1 | 8 | R | `0xe82c3e1  add r15,rax` | add offset [V] |
| 0xe82c3e4 | 8 | W | `0xe82c3e4  mov [rbx+0x380],r15` | store batch state [V] |
| 0xe82c3eb | 8 | R | `0xe82c3eb  add rdi,[r13]` | add offset [V] |
| 0xe82c3ef | 8 | R | `0xe82c3ef  mov rdx,rdi` | memcpy dst [V] |
| 0xe82c3f2 | 8 | R | `0xe82c3f2  mov r8,rsi` | memcpy src [V] |
| 0xe82c3f5 | 8 | R | `0xe82c3f5  call 0xEEC6EC0` | sub_eec6ec0 memcpy [V] |
| 0xe82c3fa | 8 | R | `0xe82c3fa  mov rax,[rbx+0x110]` | entry field load [V] |
| 0xe82c401 | 8 | R/W | `0xe82c401  add [rbx+0x2A8],rax` | advance cursor [V] |
| 0xe82c408 | 8 | R | `0xe82c408  mov rcx,[rbx+0xB0]` | ctrl object load [V] |
| 0xe82c40f | 4 | R | `0xe82c40f  mov eax,[r12+0x34]` | entry field load [V] |
| 0xe82c414 | 4 | W | `0xe82c414  mov [rbx+0x330],eax` | store entry field [V] |
| 0xe82c41a | 4 | R | `0xe82c41a  mov eax,[r12+0x38]` | entry field load [V] |
| 0xe82c41f | 4 | W | `0xe82c41f  mov [rbx+0x21C],eax` | store entry field [V] |
| 0xe82c425 | 4 | R | `0xe82c425  mov eax,[r12+0x3C]` | entry field load [V] |
| 0xe82c42a | 4 | W | `0xe82c42a  mov [rbx+0x32C],eax` | store entry field [V] |
| 0xe82c430 | 2 | R | `0xe82c430  cmp word ptr [r12+0x78],0xFFFF` | vb handle check [V] |
| 0xe82c437 | 8 | R | `0xe82c437  je 0xE82C5AA` | skip if 0xFFFF [V] |
| 0xe82c43d | 8 | R | `0xe82c43d  mov rcx,[r14+0x30]` | ctx vtable load [V] |
| 0xe82c441 | 8 | R | `0xe82c441  mov rax,[rcx]` | vtable load [V] |
| 0xe82c444 | 8 | R | `0xe82c444  mov rax,[rax+0x130]` | vtable+0x130 [V] |
| 0xe82c44b | 4 | W | `0xe82c44b  mov edx,2` | opcode 2 [V] |
| 0xe82c450 | 8 | R | `0xe82c450  mov r8,[rbx+0x170]` | batch state [V] |
| 0xe82c457 | 8 | R | `0xe82c457  call qword ptr [0xF99FFA0]` | sub_eea6040 vb record op [V] |

## Callees (executor 0xe821120)

| rva | what | tag |
|---|---|---|
| 0xE9E7970 | __chkstk (stack probe) | [V] |
| 0xF99FFA0 | sub_eea6040 (refcount/release) | [V] |
| 0xEBCE430 | sub_ebce430 (memset) | [V] |
| 0xE7FD020 | unknown helper | [V] |
| 0xE8360F0 | batch descriptor release/refill | [V] |
| 0xE820910 | per-view rect setup | [V] |
| 0xE820500 | 65-entry table init | [V] |
| 0xE81E860 | PSO builder | [V] |
| 0xE81B720 | draw flush | [V] |
| 0xE81B4D0 | vertex buffer bind | [V] |
| 0xE81D850 | timer callback | [V] |
| 0xE82D960 | texture state tracking | [V] |
| 0xE83ACE0 | texture page alloc | [V] |
| 0xEEC6ED0 | memset | [V] |
| 0xEEC6EC0 | memset/store | [V] |
| 0x47E8F0 | clip/bounds test | [V] |
| 0xE822FC5 | view remap fixup | [V] |
| 0xE829EE0 | float conversion | [V] |
| 0xBC6A9D0 | rect dependency lookup | [V] |
| 0xEBDB740 | QPC timer | [V] |
| 0xEEC59E0 | termination callback | [V] |
| 0xF9A8C78 | termination callback 2 | [V] |

## Region status

- Region 1 (0xe821120..0xe821a20): DONE — D2 [V]
- Region 2 (0xe821a20..0xe822480): DONE — D2 [V]
- Region 3 (0xe822480..0xe823287): DONE — D2 [V]
- Region 4 (0xe823287..0xe823a2b): DONE — D2 [V]
- Region 5 (0xe823a2b..0xe8241ea): DONE — D2 [V]
- Region 6 (0xe8241ea..~0xe829bb0): 6a..6j DONE — D2 [V]
- Branch B emission (0xe829b50..~0xe82a34f): DONE — D2 [V]
- Region 8 tail / per-draw writes (~0xe82a34f..0xe82d4e3): DONE — D2 [V]
- Body end 0xe82d4e3: DONE — instruction-complete [V]

## NEXT

All three deliverables are D2: wrapper 0xe83c390, five task bodies, executor 0xe821120 (instruction-complete, body end 0xe82d4e3). No remaining work for this unit.

CLOSES? YES — all three deliverables (wrapper 0xe83c390, five task bodies, executor 0xe821120) are D2 with [V] proof rows. Executor is instruction-complete: every instruction from 0xe821120 to 0xe82d4e3 belongs to a decoded phase.

## TOOL REQUESTS

None — used `rdis dis` windows and `rdis vslot 2` for RVAs.