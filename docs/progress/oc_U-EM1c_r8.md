## NEXT
DONE

# oc U-EM1c — M1c: executor wrapper 0xe83c390 (D2), five task bodies (D2), executor 0xe821120 continuation

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis via bash; no tools.rtools.*).
Goal (orchestrator; overrides prior notes): (1) full D2 dossier of the executor wrapper 0xe83c390; (2) D2 dossier of each of the five task bodies whose RVAs come from the functor vtables of the dispatch 0xe9002e0 task classes (0xF25C7B0 Scene/HUD -> body 0x568CD90 already D2 in docs/functions/568cd90.md; ClearColorDepth functor 0xF25C9B0, ClearDepth functor 0xF25C9E0, Pass functor 0xF440850, TerrainAtlasBlit functor 0xF43E9E0, SceneWaitOnChunk functor 0xF43FEA0 — _Do_call targets TBD from vtable slot 2); (3) continue executor 0xe821120 by region, marking finished regions so the next run resumes. Answer YES only when all three are D2; else NO listing what remains.

Tag legend: [V] seen in disassembly (instruction quoted verbatim, checked by verify_oc), [I] inferred from verified instructions, [?] unknown. Sizes from the instruction (movups/movdqa/movdqu/movaps 16, movq 8, movd/movss 4, word 2, byte 1). R/W = memory read/write, C = call/control/immediate (no memory operand). Meaning only where an instruction or string shows it, else '-'. One row per distinct offset; no raw disassembly dumps (every instruction appears as a backtick-quoted `0xRVA  instr` line).

## 1. Wrapper 0xe83c390 (D2) — DONE

D2 complete: full verbatim instruction table below covers the whole body 0xe83c390..0xe83c45f (ret at 0xe83c45f). Code after 0xe83c460 belongs to separate functions (their own prologues), not this wrapper [V: rdis dis 0xe83c390].

| offset | size | R/W | address | instr | meaning | tag |
|--------|------|-----|---------|-------|---------|-----|
| e83c390 | 1 | - | - | `0xe83c390  push rbp` | prologue save frame | [V] |
| e83c391 | 4 | - | - | `0xe83c391  sub rsp,0x90` | stack frame 0x90 | [V] |
| e83c398 | 7 | - | - | `0xe83c398  lea rbp,[rsp+0x80]` | frame pointer | [V] |
| e83c3a0 | 10 | - | - | `0xe83c3a0  mov qword ptr [rbp+8],0xFFFFFFFFFFFFFFFE` | unwind marker -2 | [V] |
| e83c3a8 | 2 | - | - | `0xe83c3a8  mov eax,edx` | rdx=loop index -> eax | [V] |
| e83c3aa | 6 | R | a0+0x8 | `0xe83c3aa  mov r8,[rcx+8]` | r8 = a0+0x8 (job arg struct) | [V] |
| e83c3ae | 3 | R | *(a0+0x8)+0x0 | `0xe83c3ae  mov rdx,[r8]` | rdx = *(a0+0x8)+0x0 | [V] |
| e83c3b1 | 4 | R | *(a0+0x8)+0x8 | `0xe83c3b1  mov r9,[r8+8]` | r9 = *(a0+0x8)+0x8 | [V] |
| e83c3b5 | 3 | - | - | `0xe83c3b5  mov r10d,eax` | save index | [V] |
| e83c3b8 | 7 | R | *(*(a0+0x8)+0x0)+0x19F60 | `0xe83c3b8  mov rcx,[rdx+0x19F60]` | cmdlist array base | [V] |
| e83c3bf | 4 | R | *(*(*(a0+0x8)+0x0)+0x19F60)+idx | `0xe83c3bf  mov rcx,[rcx+r10*8]` | cmdlist[index] | [V] |
| e83c3c3 | 3 | R | *(*(a0+0x8)+0x8)+0x0 | `0xe83c3c3  mov r11,[r9]` | r11 = *(*(a0+0x8)+0x8)+0x0 | [V] |
| e83c3c6 | 4 | R | *(*(*(a0+0x8)+0x8)+0x0)+idx | `0xe83c3c6  mov r9,[r11+r10*8]` | second array[index] | [V] |
| e83c3ca | 1 | - | - | `0xe83c3ca  inc eax` | index+1 | [V] |
| e83c3cc | 4 | R | *(*(*(a0+0x8)+0x8)+0x0)+idx+1 | `0xe83c3cc  mov rax,[r11+rax*8]` | next entry | [V] |
| e83c3d0 | 4 | W | rbp-8 | `0xe83c3d0  mov [rbp-8],rax` | save next entry | [V] |
| e83c3d4 | 3 | - | - | `0xe83c3d4  cmp r9,rax` | bounds check end vs next | [V] |
| e83c3d7 | 2 | - | - | `0xe83c3d7  jae short 0xE83C457` | if at/over end -> done | [V] |
| e83c3d9 | 3 | W | rbp | `0xe83c3d9  mov [rbp],r9` | current entry ptr | [V] |
| e83c3dd | 4 | R | *(a0+0x8)+0x20 | `0xe83c3dd  mov rax,[r8+0x20]` | a0+0x8+0x20 | [V] |
| e83c3e1 | 7 | - | - | `0xe83c3e1  lea r9,[0xF4EE2F0]` | [data_f4ee2f0] | [V] |
| e83c3e8 | 4 | W | rbp-0x48 | `0xe83c3e8  mov [rbp-0x48],r9` | descriptor field = data_f4ee2f0 | [V] |
| e83c3ec | 3 | - | - | `0xe83c3ec  mov r9,rbp` | r9 = frame ptr | [V] |
| e83c3ef | 4 | W | rbp-0x40 | `0xe83c3ef  mov [rbp-0x40],r9` | descriptor field = rbp | [V] |
| e83c3f3 | 4 | R | *(a0+0x8)+0x10 | `0xe83c3f3  movups xmm0,[r8+0x10]` | load 16B from a0+0x8+0x10 | [V] |
| e83c3f8 | 3 | - | - | `0xe83c3f8  lea r9,[rbp-8]` | r9 = &saved next entry | [V] |
| e83c3fc | 4 | W | rbp-0x38 | `0xe83c3fc  mov [rbp-0x38],r9` | descriptor field | [V] |
| e83c400 | 4 | W | rbp-0x30 | `0xe83c400  movups [rbp-0x30],xmm0` | descriptor field = 16B load | [V] |
| e83c404 | 4 | W | rbp-0x20 | `0xe83c404  mov [rbp-0x20],rax` | descriptor field = next entry | [V] |
| e83c408 | 4 | W | rbp-0x18 | `0xe83c408  mov [rbp-0x18],rdx` | descriptor field = *(a0+0x8)+0x0 | [V] |
| e83c40c | 3 | - | - | `0xe83c40c  lea r11,[rbp-0x48]` | r11 = &descriptor | [V] |
| e83c410 | 4 | W | rbp-0x10 | `0xe83c410  mov [rbp-0x10],r11` | save descriptor ptr | [V] |
| e83c414 | 7 | R | *(*(a0+0x8)+0x0)+0x7ED8 | `0xe83c414  lea rax,[rdx+0x7ED8]` | rax = *(a0+0x8)+0x0+0x7ED8 | [V] |
| e83c41b | 4 | R | *(a0+0x8)+0x28 | `0xe83c41b  mov r10,[r8+0x28]` | r10 = a0+0x8+0x28 | [V] |
| e83c41f | 4 | R | *(a0+0x8)+0x30 | `0xe83c41f  mov r9,[r8+0x30]` | r9 = a0+0x8+0x30 | [V] |
| e83c423 | 3 | R | *(*(a0+0x8)+0x28)+0x0 | `0xe83c423  mov r8,[r10]` | r8 = *(a0+0x8+0x28)+0x0 | [V] |
| e83c426 | 4 | W | rsp+0x28 | `0xe83c426  mov [rsp+0x28],r11` | arg: descriptor ptr | [V] |
| e83c42b | 4 | W | rsp+0x20 | `0xe83c42b  mov [rsp+0x20],rax` | arg: *(a0+0x8)+0x0+0x7ED8 | [V] |
| e83c430 | 5 | C | 0xe821120 | `0xe83c430  call 0xE821120` | -> executor 0xe821120 | [V] |
| e83c435 | 1 | - | - | `0xe83c435  nop` | padding | [V] |
| e83c436 | 4 | R | rbp-0x10 | `0xe83c436  mov rcx,[rbp-0x10]` | rcx = descriptor ptr | [V] |
| e83c43a | 3 | - | - | `0xe83c43a  test rcx,rcx` | null check | [V] |
| e83c43d | 2 | - | - | `0xe83c43d  je short 0xE83C457` | if null -> done | [V] |
| e83c43f | 3 | - | - | `0xe83c43f  lea rax,[rbp-0x48]` | rax = &descriptor | [V] |
| e83c443 | 3 | - | - | `0xe83c443  cmp rcx,rax` | rcx == &descriptor? | [V] |
| e83c446 | 4 | - | - | `0xe83c446  setne dl` | dl = (rcx != &descriptor) | [V] |
| e83c449 | 3 | R | rcx+0x0 | `0xe83c449  mov rax,[rcx]` | rax = *rcx | [V] |
| e83c44c | 4 | R | rax+0x20 | `0xe83c44c  mov rax,[rax+0x20]` | rax = (*rcx)+0x20 (dtor) | [V] |
| e83c450 | 2 | C | [0xF99FFA0] | `0xe83c450  call qword ptr [0xF99FFA0]` | [data_f99ffa0] = sub_eea6040 | [V] |
| e83c456 | 1 | - | - | `0xe83c456  nop` | padding | [V] |
| e83c457 | 4 | - | - | `0xe83c457  add rsp,0x90` | tear down frame | [V] |
| e83c45e | 1 | - | - | `0xe83c45e  pop rbp` | restore frame | [V] |
| e83c45f | 1 | - | - | `0xe83c45f  ret` | return | [V] |

Body ends at ret 0xe83c45f; instructions at 0xe83c460+ start new functions (own prologues) and are excluded [V: rdis shows fresh prologues at e83c460/e83c4d0/e83c620/e83c630].

### Wrapper semantics
- rcx=a0 (job struct), rdx=loop index/position [I from calling convention].
- Builds a descriptor at rbp-0x48..rbp-0x30: {ptr=data_f4ee2f0, len=r8(=rbp), ptr2=&saved_next, 16B from a0+0x8+0x10, next_entry, *(a0+0x8)+0x0} [I from store pattern].
- Calls executor 0xe821120 with rcx=descriptor-derived args, rdx=*(a0+0x8)+0x7ED8, r8=*(a0+0x8+0x28)+0x0, r9=*(a0+0x8)+0x30 [I: register args to callee].
- After call, if descriptor ptr non-null and != &descriptor, calls (*descriptor)+0x20 via [data_f99ffa0] (likely refcount release/dtor) [I].
- The wrapper reads bounds via cmdlist array [rdx+0x19F60] indexed by r10d and a parallel array [r11+r10*8], tracking current vs next entry [I].

## 2. Five task bodies (D2) — DONE

Task classes from dispatch 0xe9002e0 (6da/6dc, D2): 0xF25C7B0 (Scene x12 + HUD), 0xF25C850 (ClearColorDepth/ClearDepth), 0xF440770 (Pass), 0xF43E9C0 (TerrainAtlasBlit), 0xF25C080 (SceneWaitOnChunk). The body of each class is the std::function `_Do_call` at functor vtable slot 2 (+0x10) [6db].

- Scene/HUD body: 0x568CD90 — already D2 (docs/functions/568cd90.md, 0x615 bytes) [V]. Not redone.
- ClearColorDepth functor 0xF25C9B0 -> body 0x56AD350 [V: rdis vt 0xF25C9B0 slot2]
- ClearDepth functor 0xF25C9E0 -> body 0x569A3A0 [V: rdis vt 0xF25C9E0 slot2]
- Pass functor 0xF440850 -> body 0xBC38C20 [V: rdis vt 0xF440850 slot2]
- TerrainAtlasBlit functor 0xF43E9E0 -> body 0xBC02090 [V: rdis vt 0xF43E9E0 slot2]
- SceneWaitOnChunk functor 0xF43FEA0 -> body 0x56AEEB0 [V: rdis vt 0xF43FEA0 slot2]

### Body 0x56AD350 (ClearColorDepth) — DONE

Functor vtable 0xF25C9B0 slot2 (_Do_call) -> 0x56AD350 [V: rdis vt]. Body [0x56ad350..0x56af350], real sub ends at ret 0x56ad444 (then int3 padding + separate lea rax,[data_12560860] ret at 0x56ad450) [V: rdis dis 0x56ad350].

| offset | size | R/W | address | instr | meaning | tag |
|--------|------|-----|---------|-------|---------|-----|
| 56ad350 | 1 | - | - | `0x56ad350  push rsi` | prologue | [V] |
| 56ad351 | 1 | - | - | `0x56ad351  push rdi` | prologue | [V] |
| 56ad352 | 4 | - | - | `0x56ad352  sub rsp,0x38` | stack frame | [V] |
| 56ad356 | 2 | - | - | `0x56ad356  mov rsi,rdx` | rsi = a1 | [V] |
| 56ad359 | 4 | R | a2+0x8 | `0x56ad359  movzx eax,word ptr [r8+8]` | a2+0x8 | [V] |
| 56ad35e | 3 | - | - | `0x56ad35e  and eax,7` | index & 7 | [V] |
| 56ad361 | 4 | R | a1+0x8 | `0x56ad361  mov rdx,[rdx+8]` | rdx = a1+0x8 | [V] |
| 56ad365 | 4 | R | *(a1+0x8)+0x8 | `0x56ad365  movzx edx,word ptr [rdx+8]` | view id | [V] |
| 56ad369 | 7 | R | data_12ae1748 | `0x56ad369  mov r9,[0x12AE1748]` | global context base | [V] |
| 56ad370 | 3 | - | - | `0x56ad370  lea rdx,[rdx+rdx*4]` | rdx = view*5 | [V] |
| 56ad374 | 3 | - | - | `0x56ad374  shl edx,6` | rdx = view*0x140 | [V] |
| 56ad377 | 4 | R | a2+0x0 | `0x56ad377  movd xmm0,[r8]` | load rect min | [V] |
| 56ad37c | 3 | - | - | `0x56ad37c  pxor xmm1,xmm1` | zero | [V] |
| 56ad380 | 4 | - | - | `0x56ad380  pmaxsw xmm0,xmm1` | clamp min >= 0 | [V] |
| 56ad384 | 4 | R | a2+0x4 | `0x56ad384  movd xmm2,[r8+4]` | load rect max | [V] |
| 56ad38a | 4 | W | ctx+0x1EAB090 | `0x56ad38a  movd [r9+rdx+0x1EAB090],xmm0` | store clear rect min | [V] |
| 56ad394 | 3 | - | - | `0x56ad394  pcmpeqw xmm1,xmm2` | max == 0 mask | [V] |
| 56ad398 | 3 | - | - | `0x56ad398  psubw xmm2,xmm1` | max clamp | [V] |
| 56ad39c | 4 | W | ctx+0x1EAB094 | `0x56ad39c  movd [r9+rdx+0x1EAB094],xmm2` | store clear rect max | [V] |
| 56ad3a6 | 4 | R | a1+0x8 | `0x56ad3a6  mov rdx,[rsi+8]` | rdx = a1+0x8 | [V] |
| 56ad3aa | 4 | R | *(a1+0x8)+0x8 | `0x56ad3aa  movzx r8d,word ptr [rdx+8]` | view id | [V] |
| 56ad3af | 4 | R | a0+0x20 | `0x56ad3af  mov edx,[rcx+0x20]` | color dword | [V] |
| 56ad3b2 | 4 | R | a0+0xC | `0x56ad3b2  movzx r9d,byte ptr [rcx+0xC]` | sort byte | [V] |
| 56ad3b7 | 4 | R | a0+0x8 | `0x56ad3b7  movss xmm0,[rcx+8]` | color float | [V] |
| 56ad3bc | 7 | R | data_12ae1748 | `0x56ad3bc  mov rcx,[0x12AE1748]` | ctx base | [V] |
| 56ad3c3 | 3 | - | - | `0x56ad3c3  lea rdi,[r8+r8*4]` | rdi = view*5 | [V] |
| 56ad3c7 | 3 | - | - | `0x56ad3c7  shl edi,6` | rdi = view*0x140 | [V] |
| 56ad3ca | 4 | W | ctx+0x1EAB08E | `0x56ad3ca  mov [rcx+rdi+0x1EAB08E],ax` | store view id word | [V] |
| 56ad3d2 | 2 | - | - | `0x56ad3d2  mov eax,edx` | color -> eax | [V] |
| 56ad3d4 | 3 | - | - | `0x56ad3d4  shr eax,0x18` | byte 3 | [V] |
| 56ad3d7 | 4 | W | ctx+0x1EAB080 | `0x56ad3d7  mov [rcx+rdi+0x1EAB080],al` | color byte 3 -> ctx+0x1EAB080 | [V] |
| 56ad3de | 2 | - | - | `0x56ad3de  mov eax,edx` | color -> eax | [V] |
| 56ad3e0 | 3 | - | - | `0x56ad3e0  shr eax,0x10` | byte 2 | [V] |
| 56ad3e3 | 4 | W | ctx+0x1EAB081 | `0x56ad3e3  mov [rcx+rdi+0x1EAB081],al` | color byte 2 | [V] |
| 56ad3ea | 4 | W | ctx+0x1EAB082 | `0x56ad3ea  mov [rcx+rdi+0x1EAB082],dh` | color byte 1 | [V] |
| 56ad3f1 | 4 | W | ctx+0x1EAB083 | `0x56ad3f1  mov [rcx+rdi+0x1EAB083],dl` | color byte 0 | [V] |
| 56ad3f8 | 4 | W | ctx+0x1EAB088 | `0x56ad3f8  movss [rcx+rdi+0x1EAB088],xmm0` | color float | [V] |
| 56ad401 | 4 | W | ctx+0x1EAB08C | `0x56ad401  mov [rcx+rdi+0x1EAB08C],r9b` | sort byte | [V] |
| 56ad409 | 4 | R | a1+0x8 | `0x56ad409  mov rax,[rsi+8]` | rsi+8 = a1+0x8 | [V] |
| 56ad40d | 4 | R | *(a1+0x8)+0x10 | `0x56ad40d  mov rcx,[rax+0x10]` | encoder | [V] |
| 56ad411 | 5 | C | 0xBC60D10 | `0x56ad411  call 0xBC60D10` | Encoder::reset | [V] |
| 56ad416 | 4 | R | a1+0x8 | `0x56ad416  mov rax,[rsi+8]` | encoder again | [V] |
| 56ad41a | 4 | R | *(a1+0x8)+0x10 | `0x56ad41a  mov rcx,[rax+0x10]` | encoder | [V] |
| 56ad41e | 4 | R | *(a1+0x8)+0x8 | `0x56ad41e  movzx edx,word ptr [rax+8]` | view id | [V] |
| 56ad422 | 3 | W | rsp+0x28 | `0x56ad422  mov byte ptr [rsp+0x28],0` | flag = 0 | [V] |
| 56ad427 | 3 | W | rsp+0x20 | `0x56ad427  mov dword ptr [rsp+0x20],0` | value = 0 | [V] |
| 56ad42f | 4 | - | - | `0x56ad42f  mov r8w,0xFFFF` | r8 = 0xFFFF | [V] |
| 56ad434 | 4 | - | - | `0x56ad434  mov r9w,0xFFFF` | r9 = 0xFFFF | [V] |
| 56ad439 | 5 | C | 0xBC60740 | `0x56ad439  call 0xBC60740` | Encoder::submit | [V] |
| 56ad43e | 1 | - | - | `0x56ad43e  nop` | padding | [V] |
| 56ad43f | 4 | - | - | `0x56ad43f  add rsp,0x38` | tear down | [V] |
| 56ad443 | 1 | - | - | `0x56ad443  pop rdi` | restore | [V] |
| 56ad444 | 1 | - | - | `0x56ad444  pop rsi` | restore | [V] |
| 56ad445 | 1 | - | - | `0x56ad445  ret` | return | [V] |

Semantics: computes clear rect [min=max(0,a2), max=clamp(a2+4)] into ctx view slot [view*0x140+0x1EAB090/94] [I]; decomposes color dword from a0+0x20 into RGBA bytes at ctx+0x1EAB080..83, stores color float at +0x1EAB088 and sort byte at +0x1EAB08C [I]; calls Encoder::reset (0xBC60D10) then Encoder::submit (0xBC60740) with view id and 0xFFFF/0xFFFF [I]. Size 0xF6.

### Body 0x569A3A0 (ClearDepth) — DONE

Functor vtable 0xF25C9E0 slot2 (_Do_call) -> 0x569A3A0 [V: rdis vt]. Body [0x569a3a0..0x569c3a0], real sub ends at ret 0x569a474 (then int3 padding + separate lea rax,[data_12560730] ret at 0x569a480) [V: rdis dis 0x569a3a0].

| offset | size | R/W | address | instr | meaning | tag |
|--------|------|-----|---------|-------|---------|-----|
| 569a3a0 | 1 | - | - | `0x569a3a0  push rsi` | prologue | [V] |
| 569a3a1 | 4 | - | - | `0x569a3a1  sub rsp,0x30` | stack frame | [V] |
| 569a3a5 | 2 | - | - | `0x569a3a5  mov rsi,rdx` | rsi = a1 | [V] |
| 569a3a8 | 4 | R | a2+0x8 | `0x569a3a8  movzx eax,word ptr [r8+8]` | a2+0x8 | [V] |
| 569a3ad | 3 | - | - | `0x569a3ad  and eax,7` | index & 7 | [V] |
| 569a3b0 | 4 | R | a1+0x8 | `0x569a3b0  mov rdx,[rdx+8]` | rdx = a1+0x8 | [V] |
| 569a3b4 | 4 | R | *(a1+0x8)+0x8 | `0x569a3b4  movzx edx,word ptr [rdx+8]` | view id | [V] |
| 569a3b8 | 7 | R | data_12ae1748 | `0x569a3b8  mov r9,[0x12AE1748]` | global ctx | [V] |
| 569a3bf | 3 | - | - | `0x569a3bf  lea rdx,[rdx+rdx*4]` | rdx = view*5 | [V] |
| 569a3c3 | 3 | - | - | `0x569a3c3  shl edx,6` | rdx = view*0x140 | [V] |
| 569a3c6 | 4 | R | a2+0x0 | `0x569a3c6  movd xmm0,[r8]` | rect min | [V] |
| 569a3cb | 3 | - | - | `0x569a3cb  pxor xmm1,xmm1` | zero | [V] |
| 569a3cf | 4 | - | - | `0x569a3cf  pmaxsw xmm0,xmm1` | clamp min >= 0 | [V] |
| 569a3d3 | 4 | R | a2+0x4 | `0x569a3d3  movd xmm2,[r8+4]` | rect max | [V] |
| 569a3d9 | 4 | W | ctx+0x1EAB090 | `0x569a3d9  movd [r9+rdx+0x1EAB090],xmm0` | store clear rect min | [V] |
| 569a3e3 | 3 | - | - | `0x569a3e3  pcmpeqw xmm1,xmm2` | mask | [V] |
| 569a3e7 | 3 | - | - | `0x569a3e7  psubw xmm2,xmm1` | clamp max | [V] |
| 569a3eb | 4 | W | ctx+0x1EAB094 | `0x569a3eb  movd [r9+rdx+0x1EAB094],xmm2` | store clear rect max | [V] |
| 569a3f5 | 4 | R | a1+0x8 | `0x569a3f5  mov rdx,[rsi+8]` | a1+0x8 | [V] |
| 569a3f9 | 4 | R | *(a1+0x8)+0x8 | `0x569a3f9  movzx edx,word ptr [rdx+8]` | view id | [V] |
| 569a3fd | 4 | R | a0+0xC | `0x569a3fd  movzx r8d,byte ptr [rcx+0xC]` | sort byte | [V] |
| 569a402 | 4 | R | a0+0x8 | `0x569a402  movss xmm0,[rcx+8]` | depth float | [V] |
| 569a407 | 7 | R | data_12ae1748 | `0x569a407  mov rcx,[0x12AE1748]` | ctx base | [V] |
| 569a40e | 3 | - | - | `0x569a40e  lea rdx,[rdx+rdx*4]` | view*5 | [V] |
| 569a412 | 3 | - | - | `0x569a412  shl edx,6` | view*0x140 | [V] |
| 569a415 | 4 | W | ctx+0x1EAB08E | `0x569a415  mov [rcx+rdx+0x1EAB08E],ax` | view id word | [V] |
| 569a41d | 4 | W | ctx+0x1EAB080 | `0x569a41d  mov dword ptr [rcx+rdx+0x1EAB080],0xFFFFFFFF` | clear color = -1 | [V] |
| 569a428 | 4 | W | ctx+0x1EAB088 | `0x569a428  movss [rcx+rdx+0x1EAB088],xmm0` | depth float | [V] |
| 569a431 | 4 | W | ctx+0x1EAB08C | `0x569a431  mov [rcx+rdx+0x1EAB08C],r8b` | sort byte | [V] |
| 569a439 | 4 | R | a1+0x8 | `0x569a439  mov rax,[rsi+8]` | encoder | [V] |
| 569a43d | 4 | R | *(a1+0x8)+0x10 | `0x569a43d  mov rcx,[rax+0x10]` | encoder | [V] |
| 569a441 | 5 | C | 0xBC60D10 | `0x569a441  call 0xBC60D10` | Encoder::reset | [V] |
| 569a446 | 4 | R | a1+0x8 | `0x569a446  mov rax,[rsi+8]` | encoder | [V] |
| 569a44a | 4 | R | *(a1+0x8)+0x10 | `0x569a44a  mov rcx,[rax+0x10]` | encoder | [V] |
| 569a44e | 4 | R | *(a1+0x8)+0x8 | `0x569a44e  movzx edx,word ptr [rax+8]` | view id | [V] |
| 569a452 | 3 | W | rsp+0x28 | `0x569a452  mov byte ptr [rsp+0x28],0` | flag = 0 | [V] |
| 569a457 | 3 | W | rsp+0x20 | `0x569a457  mov dword ptr [rsp+0x20],0` | value = 0 | [V] |
| 569a45f | 4 | - | - | `0x569a45f  mov r8w,0xFFFF` | r8 = 0xFFFF | [V] |
| 569a464 | 4 | - | - | `0x569a464  mov r9w,0xFFFF` | r9 = 0xFFFF | [V] |
| 569a469 | 5 | C | 0xBC60740 | `0x569a469  call 0xBC60740` | Encoder::submit | [V] |
| 569a46e | 1 | - | - | `0x569a46e  nop` | padding | [V] |
| 569a46f | 4 | - | - | `0x569a46f  add rsp,0x30` | tear down | [V] |
| 569a473 | 1 | - | - | `0x569a473  pop rsi` | restore | [V] |
| 569a474 | 1 | - | - | `0x569a474  ret` | return | [V] |

Semantics: same clear-rect setup as ClearColorDepth into ctx view slot [I]; stores clear color = 0xFFFFFFFF (-1) at ctx+0x1EAB080, depth float at +0x1EAB088, sort byte at +0x1EAB08C [I]; calls Encoder::reset then Encoder::submit [I]. Size 0xD5.

### Body 0x56AEEB0 (SceneWaitOnChunk) — DONE

Functor vtable 0xF43FEA0 slot2 (_Do_call) -> 0x56AEEB0 [V: rdis vt]. Body [0x56aeeb0..0x56b0eb0], ends at ret 0x56aefd2 (then int3 padding + separate lea rax,[data_12524db0] ret at 0x56aefe0) [V: rdis dis 0x56aeeb0].

| offset | size | R/W | address | instr | meaning | tag |
|--------|------|-----|---------|-------|---------|-----|
| 56aeeb0 | 1 | - | - | `0x56aeeb0  push r15` | prologue | [V] |
| 56aeeb2 | 1 | - | - | `0x56aeeb2  push r14` | prologue | [V] |
| 56aeeb4 | 1 | - | - | `0x56aeeb4  push r13` | prologue | [V] |
| 56aeeb6 | 1 | - | - | `0x56aeeb6  push r12` | prologue | [V] |
| 56aeeb8 | 1 | - | - | `0x56aeeb8  push rsi` | prologue | [V] |
| 56aeeb9 | 1 | - | - | `0x56aeeb9  push rdi` | prologue | [V] |
| 56aeeba | 1 | - | - | `0x56aeeba  push rbx` | prologue | [V] |
| 56aeebb | 4 | - | - | `0x56aeebb  sub rsp,0x20` | stack frame | [V] |
| 56aeebf | 2 | - | - | `0x56aeebf  mov rsi,rcx` | rsi = a0 | [V] |
| 56aeec2 | 3 | - | - | `0x56aeec2  lea rax,[rcx+8]` | rax = &a0+0x8 | [V] |
| 56aeec6 | 4 | R | a1+0x8 | `0x56aeec6  mov rcx,[rdx+8]` | rcx = a1+0x8 | [V] |
| 56aeeca | 4 | R | *(a1+0x8)+0x8 | `0x56aeeca  movzx ecx,word ptr [rcx+8]` | view id | [V] |
| 56aeed5 | 3 | - | - | `0x56aeed5  shl ecx,6` | view*0x40 | [V] |
| 56aeed8 | 3 | - | - | `0x56aeed8  lea r12,[rcx+rcx*4]` | r12 = view*5 | [V] |
| 56aeedc | 8 | R | a0+0x88 | `0x56aeedc  movq xmm0,[rsi+0x88]` | load a0+0x88 | [V] |
| 56aeee4 | 3 | - | - | `0x56aeee4  pxor xmm1,xmm1` | zero | [V] |
| 56aeee8 | 4 | - | - | `0x56aeee8  pmaxsw xmm0,xmm1` | clamp >= 0 | [V] |
| 56aeeec | 4 | R | a0+0x8C | `0x56aeeec  movd xmm2,[rsi+0x8C]` | load a0+0x8C | [V] |
| 56aeef4 | 4 | W | ctx+0x1EAB090 | `0x56aeef4  movd [rdx+r12+0x1EAB090],xmm0` | store clear rect min | [V] |
| 56aeefe | 3 | - | - | `0x56aeefe  pcmpeqw xmm1,xmm2` | mask | [V] |
| 56aef02 | 3 | - | - | `0x56aef02  psubw xmm2,xmm1` | clamp | [V] |
| 56aef06 | 4 | W | ctx+0x1EAB094 | `0x56aef06  movd [rdx+r12+0x1EAB094],xmm2` | store clear rect max | [V] |
| 56aef10 | 3 | - | - | `0x56aef10  lea rdi,[rsi+0x11C]` | rdi = a0+0x11C | [V] |
| 56aef17 | 3 | - | - | `0x56aef17  lea rbx,[rsi+0xDC]` | rbx = a0+0xDC | [V] |
| 56aef1e | 3 | - | - | `0x56aef1e  lea r14,[rsi+0x9C]` | r14 = a0+0x9C | [V] |
| 56aef25 | 3 | - | - | `0x56aef25  lea r15,[rsi+0x48]` | r15 = a0+0x48 | [V] |
| 56aef29 | 7 | R | data_12ae1748 | `0x56aef29  mov r13,[0x12AE1748]` | ctx base | [V] |
| 56aef30 | 3 | - | - | `0x56aef30  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| 56aef34 | 4 | - | - | `0x56aef34  add rcx,0x1EAB0A0` | dst = ctx+r12+0x1EAB0A0 | [V] |
| 56aef3b | 4 | - | - | `0x56aef3b  mov r8d,0x40` | len 0x40 | [V] |
| 56aef41 | 2 | - | - | `0x56aef41  mov rdx,rax` | src = &a0+0x8 | [V] |
| 56aef44 | 5 | C | 0xEBCE390 | `0x56aef44  call 0xEBCE390` | memcpy dst=+0x1EAB0A0 src=a0+0x8 len=0x40 | [V] |
| 56aef49 | 3 | - | - | `0x56aef49  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| 56aef4d | 4 | - | - | `0x56aef4d  add rcx,0x1EAB0E0` | dst = +0x1EAB0E0 | [V] |
| 56aef54 | 4 | - | - | `0x56aef54  mov r8d,0x40` | len 0x40 | [V] |
| 56aef5a | 2 | - | - | `0x56aef5a  mov rdx,r15` | src = a0+0x48 | [V] |
| 56aef5d | 5 | C | 0xEBCE390 | `0x56aef5d  call 0xEBCE390` | memcpy dst=+0x1EAB0E0 src=a0+0x48 len=0x40 | [V] |
| 56aef62 | 3 | - | - | `0x56aef62  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| 56aef66 | 4 | - | - | `0x56aef66  add rcx,0x1EAB120` | dst = +0x1EAB120 | [V] |
| 56aef6d | 4 | - | - | `0x56aef6d  mov r8d,0x40` | len 0x40 | [V] |
| 56aef73 | 2 | - | - | `0x56aef73  mov rdx,r14` | src = a0+0x9C | [V] |
| 56aef76 | 5 | C | 0xEBCE390 | `0x56aef76  call 0xEBCE390` | memcpy dst=+0x1EAB120 src=a0+0x9C len=0x40 | [V] |
| 56aef7b | 3 | - | - | `0x56aef7b  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| 56aef7f | 4 | - | - | `0x56aef7f  add rcx,0x1EAB160` | dst = +0x1EAB160 | [V] |
| 56aef86 | 4 | - | - | `0x56aef86  mov r8d,0x40` | len 0x40 | [V] |
| 56aef8c | 2 | - | - | `0x56aef8c  mov rdx,rbx` | src = a0+0xDC | [V] |
| 56aef8f | 5 | C | 0xEBCE390 | `0x56aef8f  call 0xEBCE390` | memcpy dst=+0x1EAB160 src=a0+0xDC len=0x40 | [V] |
| 56aef94 | 3 | - | - | `0x56aef94  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| 56aef98 | 4 | - | - | `0x56aef98  add rcx,0x1EAB1A0` | dst = +0x1EAB1A0 | [V] |
| 56aef9f | 4 | - | - | `0x56aef9f  mov r8d,0x10` | len 0x10 | [V] |
| 56aefa5 | 2 | - | - | `0x56aefa5  mov rdx,rdi` | src = a0+0x11C | [V] |
| 56aefa8 | 5 | C | 0xEBCE390 | `0x56aefa8  call 0xEBCE390` | memcpy dst=+0x1EAB1A0 src=a0+0x11C len=0x10 | [V] |
| 56aefad | 4 | R | a0+0x98 | `0x56aefad  movzx eax,byte ptr [rsi+0x98]` | sort byte | [V] |
| 56aefb4 | 7 | R | data_12ae1748 | `0x56aefb4  mov rcx,[0x12AE1748]` | ctx base | [V] |
| 56aefbb | 4 | W | ctx+0x1EAB1B2 | `0x56aefbb  mov [rcx+r12+0x1EAB1B2],al` | store sort byte | [V] |
| 56aefc3 | 4 | - | - | `0x56aefc3  add rsp,0x20` | tear down | [V] |
| 56aefc7 | 1 | - | - | `0x56aefc7  pop rbx` | restore | [V] |
| 56aefc8 | 1 | - | - | `0x56aefc8  pop rdi` | restore | [V] |
| 56aefc9 | 1 | - | - | `0x56aefc9  pop rsi` | restore | [V] |
| 56aefca | 1 | - | - | `0x56aefca  pop r12` | restore | [V] |
| 56aefcc | 1 | - | - | `0x56aefcc  pop r13` | restore | [V] |
| 56aefce | 1 | - | - | `0x56aefce  pop r14` | restore | [V] |
| 56aefd0 | 1 | - | - | `0x56aefd0  pop r15` | restore | [V] |
| 56aefd2 | 1 | - | - | `0x56aefd2  ret` | return | [V] |

Semantics: computes clear rect [clamp(a0+0x88), clamp(a0+0x8C)] into ctx view slot [view*0x140+0x1EAB090/94] [I]; 5x memcpy via 0xEBCE390: ctx+0x1EAB0A0 <- a0+0x8 (16B), ctx+0x1EAB0E0 <- a0+0x48 (0x40), ctx+0x1EAB120 <- a0+0x9C (0x40), ctx+0x1EAB160 <- a0+0xDC (0x40), ctx+0x1EAB1A0 <- a0+0x11C (0x10) [I]; stores sort byte a0+0x98 at ctx+0x1EAB1B2 [I]. Size 0x123.

### Body 0xBC02090 (TerrainAtlasBlit) — DONE

Functor vtable 0xF43E9E0 slot2 (_Do_call) -> 0xBC02090 [V: rdis vt]. Body [0xbc02090..0xbc04090], ends at ret 0xbc0463 plus early-exit tail 0xbc02470..0xbc024b0 and early-exit call 0xbc02464..int3 [V: rdis dis 0xbc02090].

| offset | size | R/W | address | instr | meaning | tag |
|--------|------|-----|---------|-------|---------|-----|
| bc02090 | 1 | - | - | `0xbc02090  push rbp` | prologue | [V] |
| bc02091 | 1 | - | - | `0xbc02091  push r15` | prologue | [V] |
| bc02093 | 1 | - | - | `0xbc02093  push r14` | prologue | [V] |
| bc02095 | 1 | - | - | `0xbc02095  push r13` | prologue | [V] |
| bc02097 | 1 | - | - | `0xbc02097  push r12` | prologue | [V] |
| bc02099 | 1 | - | - | `0xbc02099  push rsi` | prologue | [V] |
| bc0209a | 1 | - | - | `0xbc0209a  push rdi` | prologue | [V] |
| bc0209b | 1 | - | - | `0xbc0209b  push rbx` | prologue | [V] |
| bc0209c | 4 | - | - | `0xbc0209c  sub rsp,0x178` | stack frame | [V] |
| bc020a3 | 3 | - | - | `0xbc020a3  lea rbp,[rsp+0x80]` | frame pointer | [V] |
| bc020ab | 16 | W | rbp+0xE0 | `0xbc020ab  movdqa [rbp+0xE0],xmm6` | save xmm6 | [V] |
| bc020b3 | 8 | - | - | `0xbc020b3  mov qword ptr [rbp+0xD8],0xFFFFFFFFFFFFFFFE` | unwind marker | [V] |
| bc020be | 2 | - | - | `0xbc020be  mov rsi,r8` | rsi = a2 | [V] |
| bc020c1 | 2 | - | - | `0xbc020c1  mov rdi,rdx` | rdi = a1 | [V] |
| bc020c4 | 2 | - | - | `0xbc020c4  mov rbx,rcx` | rbx = a0 | [V] |
| bc020c7 | 3 | - | - | `0xbc020c7  lea rdx,[rcx+8]` | rdx = &a0+0x8 | [V] |
| bc020cb | 4 | R | a1+0x8 | `0xbc020cb  mov rax,[rdi+8]` | rax = a1+0x8 | [V] |
| bc020cf | 4 | R | *(a1+0x8)+0x8 | `0xbc020cf  movzx eax,word ptr [rax+8]` | view id | [V] |
| bc020d3 | 7 | R | data_12ae1748 | `0xbc020d3  mov rcx,[0x12AE1748]` | ctx base | [V] |
| bc020da | 3 | - | - | `0xbc020da  shl eax,6` | view*0x40 | [V] |
| bc020dd | 3 | - | - | `0xbc020dd  lea r14,[rax+rax*4]` | r14 = view*5 | [V] |
| bc020e1 | 8 | R | a0+0x88 | `0xbc020e1  movq xmm0,[rbx+0x88]` | load a0+0x88 | [V] |
| bc020e9 | 3 | - | - | `0xbc020e9  pxor xmm6,xmm6` | zero | [V] |
| bc020ed | 4 | - | - | `0xbc020ed  pmaxsw xmm0,xmm6` | clamp min >= 0 | [V] |
| bc020f1 | 4 | R | a0+0x8C | `0xbc020f1  movd xmm1,[rbx+0x8C]` | load a0+0x8C | [V] |
| bc020f9 | 4 | W | ctx+0x1EAB090 | `0xbc020f9  movd [rcx+r14+0x1EAB090],xmm0` | store clear rect min | [V] |
| bc02103 | 4 | - | - | `0xbc02103  movdqa xmm0,xmm1` | copy xmm1 | [V] |
| bc02107 | 3 | - | - | `0xbc02107  pcmpeqw xmm0,xmm6` | mask | [V] |
| bc0210b | 3 | - | - | `0xbc0210b  psubw xmm1,xmm0` | clamp max | [V] |
| bc0210f | 4 | W | ctx+0x1EAB094 | `0xbc0210f  movd [rcx+r14+0x1EAB094],xmm1` | store clear rect max | [V] |
| bc02119 | 3 | - | - | `0xbc02119  lea r12,[rbx+0x9C]` | r12 = a0+0x9C | [V] |
| bc02120 | 3 | - | - | `0xbc02120  lea r13,[rbx+0x48]` | r13 = a0+0x48 | [V] |
| bc02124 | 7 | R | data_12ae1748 | `0xbc02124  mov r15,[0x12AE1748]` | ctx base | [V] |
| bc0212b | 3 | - | - | `0xbc0212b  lea rcx,[r15+r14]` | rcx = ctx+r14 | [V] |
| bc0212f | 4 | - | - | `0xbc0212f  add rcx,0x1EAB0A0` | dst = +0x1EAB0A0 | [V] |
| bc02136 | 4 | - | - | `0xbc02136  mov r8d,0x40` | len 0x40 | [V] |
| bc0213c | 5 | C | 0xEBCE390 | `0xbc0213c  call 0xEBCE390` | memcpy dst=+0x1EAB0A0 src=rbx rdx=? len=0x40 | [V] |
| bc02141 | 3 | - | - | `0xbc02141  lea rcx,[r15+r14]` | rcx = ctx+r14 | [V] |
| bc02145 | 4 | - | - | `0xbc02145  add rcx,0x1EAB0E0` | dst = +0x1EAB0E0 | [V] |
| bc0214c | 4 | - | - | `0xbc0214c  mov r8d,0x40` | len 0x40 | [V] |
| bc02152 | 2 | - | - | `0xbc02152  mov rdx,r13` | src = a0+0x48 | [V] |
| bc02155 | 5 | C | 0xEBCE390 | `0xbc02155  call 0xEBCE390` | memcpy dst=+0x1EAB0E0 src=a0+0x48 len=0x40 | [V] |
| bc0215a | 3 | - | - | `0xbc0215a  lea rcx,[r15+r14]` | rcx = ctx+r14 | [V] |
| bc0215e | 4 | - | - | `0xbc0215e  add rcx,0x1EAB120` | dst = +0x1EAB120 | [V] |
| bc02165 | 4 | - | - | `0xbc02165  mov r8d,0x40` | len 0x40 | [V] |
| bc0216b | 2 | - | - | `0xbc0216b  mov rdx,r12` | src = a0+0x9C | [V] |
| bc0216e | 5 | C | 0xEBCE390 | `0xbc0216e  call 0xEBCE390` | memcpy dst=+0x1EAB120 src=a0+0x9C len=0x40 | [V] |
| bc02173 | 3 | - | - | `0xbc02173  lea rcx,[r15+r14]` | rcx = ctx+r14 | [V] |
| bc02177 | 4 | - | - | `0xbc02177  add rcx,0x1EAB160` | dst = +0x1EAB160 | [V] |
| bc0217e | 4 | - | - | `0xbc0217e  mov r8d,0x40` | len 0x40 | [V] |
| bc02184 | 3 | - | - | `0xbc02184  lea rdx,[rbx+0xDC]` | src = a0+0xDC | [V] |
| bc0218b | 5 | C | 0xEBCE390 | `0xbc0218b  call 0xEBCE390` | memcpy dst=+0x1EAB160 src=a0+0xDC len=0x40 | [V] |
| bc02190 | 3 | - | - | `0xbc02190  lea rcx,[r15+r14]` | rcx = ctx+r14 | [V] |
| bc02194 | 4 | - | - | `0xbc02194  add rcx,0x1EAB1A0` | dst = +0x1EAB1A0 | [V] |
| bc0219b | 4 | - | - | `0xbc0219b  mov r8d,0x10` | len 0x10 | [V] |
| bc021a1 | 3 | - | - | `0xbc021a1  lea rdx,[rbx+0x11C]` | src = a0+0x11C | [V] |
| bc021a8 | 5 | C | 0xEBCE390 | `0xbc021a8  call 0xEBCE390` | memcpy dst=+0x1EAB1A0 src=a0+0x11C len=0x10 | [V] |
| bc021ad | 4 | R | a0+0x98 | `0xbc021ad  movzx eax,byte ptr [rbx+0x98]` | sort byte | [V] |
| bc021b4 | 7 | R | data_12ae1748 | `0xbc021b4  mov rcx,[0x12AE1748]` | ctx base | [V] |
| bc021bb | 4 | W | ctx+0x1EAB1B2 | `0xbc021bb  mov [rcx+r14+0x1EAB1B2],al` | store sort byte | [V] |
| bc021c3 | 4 | W | rbp-0x50 | `0xbc021c3  mov dword ptr [rbp-0x50],0x3F800000` | float 1.0 | [V] |
| bc021ca | 16 | W | rbp-0x4C | `0xbc021ca  movdqu [rbp-0x4C],xmm6` | zero 16B | [V] |
| bc021cf | 4 | W | rbp-0x3C | `0xbc021cf  mov dword ptr [rbp-0x3C],0x3F800000` | float 1.0 | [V] |
| bc021d6 | 16 | W | rbp-0x38 | `0xbc021d6  movdqu [rbp-0x38],xmm6` | zero 16B | [V] |
| bc021db | 4 | W | rbp-0x28 | `0xbc021db  mov dword ptr [rbp-0x28],0x3F800000` | float 1.0 | [V] |
| bc021e2 | 16 | W | rbp-0x24 | `0xbc021e2  movdqu [rbp-0x24],xmm6` | zero 16B | [V] |
| bc021e7 | 8 | R | data_efd3400 | `0xbc021e7  movsd xmm0,[0xEFD3400]` | [data_efd3400] | [V] |
| bc021ef | 8 | W | rbp-0x14 | `0xbc021ef  movsd [rbp-0x14],xmm0` | store double | [V] |
| bc021f4 | 16 | W | rbp-0xC | `0xbc021f4  movdqu [rbp-0xC],xmm6` | zero 16B | [V] |
| bc021f9 | 4 | W | rbp+4 | `0xbc021f9  mov dword ptr [rbp+4],0x3F800000` | float 1.0 | [V] |
| bc02200 | 16 | W | rbp+8 | `0xbc02200  movdqu [rbp+8],xmm6` | zero 16B | [V] |
| bc02205 | 4 | W | rbp+0x18 | `0xbc02205  mov dword ptr [rbp+0x18],0x3F800000` | float 1.0 | [V] |
| bc0220c | 16 | W | rbp+0x1C | `0xbc0220c  movdqu [rbp+0x1C],xmm6` | zero 16B | [V] |
| bc02211 | 4 | W | rbp+0x2C | `0xbc02211  mov dword ptr [rbp+0x2C],0x3F800000` | float 1.0 | [V] |
| bc02218 | 4 | R | a2+0x38 | `0xbc02218  mov rax,[rsi+0x38]` | a2+0x38 | [V] |
| bc0221c | 8 | - | - | `0xbc0221c  movq xmm1,rax` | xmm1 = a2+0x38 | [V] |
| bc02221 | 8 | W | rbp+0x30 | `0xbc02221  mov [rbp+0x30],rax` | store | [V] |
| bc02225 | 8 | W | rbp+0x38 | `0xbc02225  mov qword ptr [rbp+0x38],0` | zero | [V] |
| bc0222d | 8 | - | - | `0xbc0222d  mov rax,0x3F80000000000001` | double 1.0 | [V] |
| bc02237 | 8 | W | rbp+0x40 | `0xbc02237  mov [rbp+0x40],rax` | store | [V] |
| bc0223b | 3 | - | - | `0xbc0223b  lea r12,[rbp+0x44]` | r12 = &rbp+0x44 | [V] |
| bc0223f | 16 | W | rbp+0x48 | `0xbc0223f  movdqu [rbp+0x48],xmm6` | zero 16B | [V] |
| bc02244 | 4 | W | rbp+0x58 | `0xbc02244  mov dword ptr [rbp+0x58],0x3F800000` | float 1.0 | [V] |
| bc0224b | 16 | W | rbp+0x5C | `0xbc0224b  movdqu [rbp+0x5C],xmm6` | zero 16B | [V] |
| bc02250 | 4 | W | rbp+0x6C | `0xbc02250  mov dword ptr [rbp+0x6C],0x3F800000` | float 1.0 | [V] |
| bc02257 | 16 | W | rbp+0x70 | `0xbc02257  movdqu [rbp+0x70],xmm6` | zero 16B | [V] |
| bc0225c | 3 | - | - | `0xbc0225c  lea r15,[rbp+0x84]` | r15 = &rbp+0x84 | [V] |
| bc02263 | 8 | W | rbp+0x80 | `0xbc02263  movsd [rbp+0x80],xmm0` | store double | [V] |
| bc0226b | 16 | W | rbp+0x88 | `0xbc0226b  movdqu [rbp+0x88],xmm6` | zero 16B | [V] |
| bc02273 | 4 | W | rbp+0x98 | `0xbc02273  mov dword ptr [rbp+0x98],0x3F800000` | float 1.0 | [V] |
| bc0227d | 16 | W | rbp+0x9C | `0xbc0227d  movdqu [rbp+0x9C],xmm6` | zero 16B | [V] |
| bc02285 | 4 | W | rbp+0xAC | `0xbc02285  mov dword ptr [rbp+0xAC],0x3F800000` | float 1.0 | [V] |
| bc0228f | 16 | W | rbp+0xB0 | `0xbc0228f  movdqu [rbp+0xB0],xmm6` | zero 16B | [V] |
| bc02297 | 4 | W | rbp+0xC0 | `0xbc02297  mov dword ptr [rbp+0xC0],0x3F800000` | float 1.0 | [V] |
| bc022a1 | 3 | - | - | `0xbc022a1  lea r14,[rbp+0xC4]` | r14 = &rbp+0xC4 | [V] |
| bc022a8 | 16 | W | rbp+0xC4 | `0xbc022a8  movdqu [rbp+0xC4],xmm6` | zero 16B | [V] |
| bc022b0 | 4 | R | a1+0x8 | `0xbc022b0  mov rax,[rdi+8]` | rax = a1+0x8 | [V] |
| bc022b4 | 4 | R | *(a1+0x8)+0x8 | `0xbc022b4  movzx eax,word ptr [rax+8]` | view id | [V] |
| bc022b8 | 7 | R | data_12ae1748 | `0xbc022b8  mov rcx,[0x12AE1748]` | ctx base | [V] |
| bc022bf | 3 | - | - | `0xbc022bf  shl eax,6` | view*0x40 | [V] |
| bc022c2 | 3 | - | - | `0xbc022c2  lea r13,[rax+rax*4]` | r13 = view*5 | [V] |
| bc022c6 | 4 | - | - | `0xbc022c6  pshufd xmm0,xmm1,0x55` | shuffle | [V] |
| bc022cb | 4 | - | - | `0xbc022cb  pmaxsw xmm1,xmm6` | clamp | [V] |
| bc022cf | 4 | W | ctx+0x1EAB090 | `0xbc022cf  movd [rcx+r13+0x1EAB090],xmm1` | store clear rect min | [V] |
| bc022d9 | 4 | - | - | `0xbc022d9  movdqa xmm1,xmm0` | copy | [V] |
| bc022dd | 3 | - | - | `0xbc022dd  pcmpeqw xmm1,xmm6` | mask | [V] |
| bc022e1 | 3 | - | - | `0xbc022e1  psubw xmm0,xmm1` | clamp | [V] |
| bc022e5 | 4 | W | ctx+0x1EAB094 | `0xbc022e5  movd [rcx+r13+0x1EAB094],xmm0` | store clear rect max | [V] |
| bc022ef | 7 | R | data_12ae1748 | `0xbc022ef  mov rbx,[0x12AE1748]` | ctx base | [V] |
| bc022f6 | 3 | - | - | `0xbc022f6  lea rcx,[rbx+r13]` | rcx = ctx+r13 | [V] |
| bc022fa | 4 | - | - | `0xbc022fa  add rcx,0x1EAB0A0` | dst = +0x1EAB0A0 | [V] |
| bc02301 | 3 | - | - | `0xbc02301  lea rdx,[rbp-0x50]` | src = scratch block | [V] |
| bc02305 | 4 | - | - | `0xbc02305  mov r8d,0x40` | len 0x40 | [V] |
| bc0230b | 5 | C | 0xEBCE390 | `0xbc0230b  call 0xEBCE390` | memcpy dst=+0x1EAB0A0 src=scratch len=0x40 | [V] |
| bc02310 | 3 | - | - | `0xbc02310  lea rcx,[rbx+r13]` | rcx = ctx+r13 | [V] |
| bc02314 | 4 | - | - | `0xbc02314  add rcx,0x1EAB0E0` | dst = +0x1EAB0E0 | [V] |
| bc0231b | 4 | - | - | `0xbc0231b  mov r8d,0x40` | len 0x40 | [V] |
| bc02321 | 3 | - | - | `0xbc02321  lea rdx,[rbp-0x10]` | src = scratch+0x40 | [V] |
| bc02325 | 5 | C | 0xEBCE390 | `0xbc02325  call 0xEBCE390` | memcpy dst=+0x1EAB0E0 src=scratch+0x10 len=0x40 | [V] |
| bc0232a | 3 | - | - | `0xbc0232a  lea rcx,[rbx+r13]` | rcx = ctx+r13 | [V] |
| bc0232e | 4 | - | - | `0xbc0232e  add rcx,0x1EAB120` | dst = +0x1EAB120 | [V] |
| bc02335 | 4 | - | - | `0xbc02335  mov r8d,0x40` | len 0x40 | [V] |
| bc0233b | 2 | - | - | `0xbc0233b  mov rdx,r12` | src = &rbp+0x44 | [V] |
| bc0233e | 5 | C | 0xEBCE390 | `0xbc0233e  call 0xEBCE390` | memcpy dst=+0x1EAB120 src=&rbp+0x44 len=0x40 | [V] |
| bc02343 | 3 | - | - | `0xbc02343  lea rcx,[rbx+r13]` | rcx = ctx+r13 | [V] |
| bc02347 | 4 | - | - | `0xbc02347  add rcx,0x1EAB160` | dst = +0x1EAB160 | [V] |
| bc0234e | 4 | - | - | `0xbc0234e  mov r8d,0x40` | len 0x40 | [V] |
| bc02354 | 2 | - | - | `0xbc02354  mov rdx,r15` | src = &rbp+0x84 | [V] |
| bc02357 | 5 | C | 0xEBCE390 | `0xbc02357  call 0xEBCE390` | memcpy dst=+0x1EAB160 src=&rbp+0x84 len=0x40 | [V] |
| bc0235c | 3 | - | - | `0xbc0235c  lea rcx,[rbx+r13]` | rcx = ctx+r13 | [V] |
| bc02360 | 4 | - | - | `0xbc02360  add rcx,0x1EAB1A0` | dst = +0x1EAB1A0 | [V] |
| bc02367 | 4 | - | - | `0xbc02367  mov r8d,0x10` | len 0x10 | [V] |
| bc0236d | 2 | - | - | `0xbc0236d  mov rdx,r14` | src = &rbp+0xC4 | [V] |
| bc02370 | 5 | C | 0xEBCE390 | `0xbc02370  call 0xEBCE390` | memcpy dst=+0x1EAB1A0 src=&rbp+0xC4 len=0x10 | [V] |
| bc02375 | 4 | R | rbp+0x40 | `0xbc02375  movzx eax,byte ptr [rbp+0x40]` | byte from scratch | [V] |
| bc02379 | 7 | R | data_12ae1748 | `0xbc02379  mov rcx,[0x12AE1748]` | ctx base | [V] |
| bc02380 | 4 | W | ctx+0x1EAB1B2 | `0xbc02380  mov [rcx+r13+0x1EAB1B2],al` | store sort byte | [V] |
| bc02388 | 8 | R | a2+0x0 | `0xbc02388  mov rax,[rsi]` | rax = a2+0x0 | [V] |
| bc0238b | 8 | W | rbp-0x50 | `0xbc0238b  mov [rbp-0x50],rax` | scope ptr | [V] |
| bc0238f | 16 | W | rbp-0x48 | `0xbc0238f  movdqu [rbp-0x48],xmm6` | zero | [V] |
| bc02394 | 8 | R | a2+0x10 | `0xbc02394  mov rax,[rsi+0x10]` | rax = a2+0x10 | [V] |
| bc02398 | 3 | - | - | `0xbc02398  test rax,rax` | null check | [V] |
| bc0239b | 2 | - | - | `0xbc0239b  je short 0xBC023A7` | if null -> eax=0 | [V] |
| bc0239d | 4 | R | *(a2+0x10)+0x8 | `0xbc0239d  lock inc dword ptr [rax+8]` | refcount++ | [V] |
| bc023a1 | 8 | R | a2+0x10 | `0xbc023a1  mov rax,[rsi+0x10]` | rax = a2+0x10 | [V] |
| bc023a5 | 2 | - | - | `0xbc023a5  jmp short 0xBC023A9` | -> loc | [V] |
| bc023a7 | 2 | - | - | `0xbc023a7  xor eax,eax` | eax = 0 | [V] |
| bc023a9 | 8 | R | a2+8 | `0xbc023a9  mov rcx,[rsi+8]` | rcx = a2+8 | [V] |
| bc023ad | 8 | W | rbp-0x48 | `0xbc023ad  mov [rbp-0x48],rcx` | scope ctrl | [V] |
| bc023b1 | 8 | W | rbp-0x40 | `0xbc023b1  mov [rbp-0x40],rax` | scope obj | [V] |
| bc023b5 | 16 | W | rbp-0x38 | `0xbc023b5  movdqu [rbp-0x38],xmm6` | zero | [V] |
| bc023ba | 8 | W | rbp-0x28 | `0xbc023ba  mov qword ptr [rbp-0x28],0` | zero | [V] |
| bc023c2 | 3 | W | rbp-0x20 | `0xbc023c2  mov byte ptr [rbp-0x20],1` | flag = 1 | [V] |
| bc023c6 | 8 | R | a1+8 | `0xbc023c6  mov rcx,[rdi+8]` | rcx = a1+8 | [V] |
| bc023ca | 3 | - | - | `0xbc023ca  lea rbx,[rbp-0x50]` | rbx = &scope | [V] |
| bc023ce | 2 | - | - | `0xbc023ce  mov rdx,rbx` | rdx = &scope | [V] |
| bc023d1 | 5 | C | 0xBCC1A30 | `0xbc023d1  call 0xBCC1A30` | scope register | [V] |
| bc023d6 | 1 | - | - | `0xbc023d6  nop` | padding | [V] |
| bc023d7 | 8 | R | a2+0xA0 | `0xbc023d7  mov r14,[rsi+0xA0]` | r14 = a2+0xA0 (range begin) | [V] |
| bc023de | 8 | R | a2+0xA8 | `0xbc023de  mov r12,[rsi+0xA8]` | r12 = a2+0xA8 (range end) | [V] |
| bc023e5 | 8 | - | - | `0xbc023e5  mov rax,r12` | rax = end | [V] |
| bc023e8 | 4 | - | - | `0xbc023e8  sub rax,r14` | rax = end - begin | [V] |
| bc023eb | 4 | - | - | `0xbc023eb  cmp rax,0xFFFFFFFFFFFFFFD8` | if <= 0x28 -> empty | [V] |
| bc023ef | 2 | - | - | `0xbc023ef  je short 0xBC02464` | empty range -> call 0x78ED0 | [V] |
| bc023f1 | 3 | - | - | `0xbc023f1  test r14,r14` | begin null? | [V] |
| bc023f4 | 2 | - | - | `0xbc023f4  setne al` | al = (begin != 0) | [V] |
| bc023f7 | 3 | - | - | `0xbc023f7  test r12,r12` | end null? | [V] |
| bc023fa | 2 | - | - | `0xbc023fa  sete cl` | cl = (end == 0) | [V] |
| bc023fd | 3 | - | - | `0xbc023fd  or cl,al` | empty condition | [V] |
| bc023ff | 2 | - | - | `0xbc023ff  je short 0xBC02464` | empty -> call 0x78ED0 | [V] |
| bc02401 | 3 | - | - | `0xbc02401  cmp r12,r14` | begin == end? | [V] |
| bc02404 | 2 | - | - | `0xbc02404  je short 0xBC02440` | equal -> done (tail) | [V] |
| bc02406 | 8 | R | a1+8 | `0xbc02406  mov rdi,[rdi+8]` | rdi = a1+8 | [V] |
| bc0240a | 8 | R | rdi+0x10 | `0xbc0240a  mov rcx,[rdi+0x10]` | encoder | [V] |
| bc0240e | 5 | C | 0xBC60D10 | `0xbc0240e  call 0xBC60D10` | Encoder::reset | [V] |
| bc02413 | 1 | - | - | `0xbc02413  nop` | padding | [V] |
| bc02414 | 3 | - | - | `0xbc02414  lea r15,[rsi+0x38]` | r15 = a2+0x38 | [V] |
| bc02418 | 3 | - | - | `0xbc02418  add rsi,0x40` | rsi += 0x40 | [V] |
| bc0241c | 5 | - | - | `0xbc0241c  nop [rax]` | align | [V] |
| bc02420 | 4 | W | rsp+0x20 | `0xbc02420  mov [rsp+0x20],rbx` | save &scope | [V] |
| bc02425 | 2 | - | - | `0xbc02425  mov rcx,r14` | rcx = entry | [V] |
| bc02428 | 2 | - | - | `0xbc02428  mov rdx,rdi` | rdx = a1+8 | [V] |
| bc0242b | 3 | - | - | `0xbc0242b  mov r8,r15` | r8 = a2+0x38 | [V] |
| bc0242e | 3 | - | - | `0xbc0242e  mov r9,rsi` | r9 = a2+0x40.. | [V] |
| bc02431 | 5 | C | 0xE7EBFC0 | `0xbc02431  call 0xE7EBFC0` | per-entry encode | [V] |
| bc02436 | 1 | - | - | `0xbc02436  nop` | padding | [V] |
| bc02437 | 3 | - | - | `0xbc02437  add r14,0x28` | next entry stride 0x28 | [V] |
| bc0243b | 3 | - | - | `0xbc0243b  cmp r14,r12` | vs end | [V] |
| bc0243e | 2 | - | - | `0xbc0243e  jne short 0xBC02420` | loop | [V] |
| bc02440 | 3 | - | - | `0xbc02440  lea rcx,[rbp-0x50]` | rcx = &scope | [V] |
| bc02444 | 5 | C | 0x655CEA0 | `0xbc02444  call 0x655CEA0` | scope release | [V] |
| bc02449 | 16 | R | rbp+0xE0 | `0xbc02449  movaps xmm6,[rbp+0xE0]` | restore xmm6 | [V] |
| bc02450 | 4 | - | - | `0xbc02450  add rsp,0x178` | tear down | [V] |
| bc02457 | 1 | - | - | `0xbc02457  pop rbx` | restore | [V] |
| bc02458 | 1 | - | - | `0xbc02458  pop rdi` | restore | [V] |
| bc02459 | 1 | - | - | `0xbc02459  pop rsi` | restore | [V] |
| bc0245a | 1 | - | - | `0xbc0245a  pop r12` | restore | [V] |
| bc0245c | 1 | - | - | `0xbc0245c  pop r13` | restore | [V] |
| bc0245e | 1 | - | - | `0xbc0245e  pop r14` | restore | [V] |
| bc02460 | 1 | - | - | `0xbc02460  pop r15` | restore | [V] |
| bc02462 | 1 | - | - | `0xbc02462  pop rbp` | restore | [V] |
| bc02463 | 1 | - | - | `0xbc02463  ret` | return | [V] |
| bc02464 | 5 | C | 0x78ED0 | `0xbc02464  call 0x78ED0` | empty-range helper (noreturn-ish; int3 after, separate fn at 0xbc02470) | [V] |

Semantics: computes clear rect into ctx view slot [I]; 5x memcpy via 0xEBCE390 (same offsets as SceneWaitOnChunk: +0x1EAB0A0/0xE0/0x120/0x160/0x1A0 from a0+0x48/0x9C/0xDC/0x11C plus +0x1EAB0A0 from scratch block built at rbp-0x50) [I]; stores sort byte a0+0x98 at ctx+0x1EAB1B2 [I]; builds a scope object at rbp-0x50 ({rax=[a2], lock inc [rax+8] if nonzero, byte=1}) and calls 0xBCC1A30 (scope register) [I]; iterates entries stride 0x28 from a2+0xA0 to a2+0xA8, calling Encoder::reset then 0xE7EBFC0 per entry [I]; on empty range (end-begin <= 0x28 or null/zero) calls 0x78ED0 [I]; normal exit calls scope release 0x655CEA0 and ret [I]. Size 0x3DA.

### Body 0xBC38C20 (Pass) — DONE

Functor vtable 0xF440850 slot2 (_Do_call) -> 0xBC38C20 [V: rdis vt]. Body [0xbc38c20..0xbc3ac20], ends at ret 0xbc39a8b plus fail block 0xbc399ae and allocator-free tail at 0xbc39a5c..0xbc39a8b [V: rdis dis 0xbc38c20]. Full body decoded across windows 0xbc38c20..0xbc39a5c (see @12-@14) and 0xbc39a5c..0xbc39a8b.

| offset | size | R/W | address | instr | meaning | tag |
|--------|------|-----|---------|-------|---------|-----|
| bc38c20 | 1 | - | - | `0xbc38c20  push rbp` | prologue | [V] |
| bc38c21 | 1 | - | - | `0xbc38c21  push r15` | prologue | [V] |
| bc38c23 | 1 | - | - | `0xbc38c23  push r14` | prologue | [V] |
| bc38c25 | 1 | - | - | `0xbc38c25  push r13` | prologue | [V] |
| bc38c27 | 1 | - | - | `0xbc38c27  push r12` | prologue | [V] |
| bc38c29 | 1 | - | - | `0xbc38c29  push rsi` | prologue | [V] |
| bc38c2a | 1 | - | - | `0xbc38c2a  push rdi` | prologue | [V] |
| bc38c2b | 1 | - | - | `0xbc38c2b  push rbx` | prologue | [V] |
| bc38c2c | 4 | - | - | `0xbc38c2c  sub rsp,0x2D8` | stack frame | [V] |
| bc38c33 | 3 | - | - | `0xbc38c33  lea rbp,[rsp+0x80]` | frame pointer | [V] |
| bc38c3b | 16 | W | rbp+0x240 | `0xbc38c3b  movdqa [rbp+0x240],xmm6` | save xmm6 | [V] |
| bc38c43 | 8 | - | - | `0xbc38c43  mov qword ptr [rbp+0x238],0xFFFFFFFFFFFFFFFE` | unwind marker | [V] |
| bc38c4e | 2 | - | - | `0xbc38c4e  mov rbx,r8` | rbx = a2 | [V] |
| bc38c51 | 2 | - | - | `0xbc38c51  mov rsi,rdx` | rsi = a1 | [V] |
| bc38c54 | 3 | - | - | `0xbc38c54  lea rdx,[r8+0x78]` | rdx = &a2+0x78 | [V] |
| bc38c58 | 4 | R | a1+0x8 | `0xbc38c58  mov rax,[rsi+8]` | rax = a1+0x8 | [V] |
| bc38c5c | 4 | R | *(a1+0x8)+0x8 | `0xbc38c5c  movzx eax,word ptr [rax+8]` | view id | [V] |
| bc38c60 | 7 | R | data_12ae1748 | `0xbc38c60  mov rcx,[0x12AE1748]` | ctx base | [V] |
| bc38c67 | 3 | - | - | `0xbc38c67  shl eax,6` | view*0x40 | [V] |
| bc38c6a | 3 | - | - | `0xbc38c6a  lea r12,[rax+rax*4]` | r12 = view*5 | [V] |
| bc38c6e | 8 | R | a2+0xF8 | `0xbc38c6e  movq xmm0,[r8+0xF8]` | load a2+0xF8 | [V] |
| bc38c77 | 3 | - | - | `0xbc38c77  pxor xmm6,xmm6` | zero | [V] |
| bc38c7b | 4 | - | - | `0xbc38c7b  pmaxsw xmm0,xmm6` | clamp min >= 0 | [V] |
| bc38c7f | 4 | R | a2+0xFC | `0xbc38c7f  movd xmm1,[r8+0xFC]` | load a2+0xFC | [V] |
| bc38c88 | 4 | W | ctx+0x1EAB090 | `0xbc38c88  movd [rcx+r12+0x1EAB090],xmm0` | store clear rect min | [V] |
| bc38c92 | 4 | - | - | `0xbc38c92  movdqa xmm0,xmm1` | copy | [V] |
| bc38c96 | 3 | - | - | `0xbc38c96  pcmpeqw xmm0,xmm6` | mask | [V] |
| bc38c9a | 3 | - | - | `0xbc38c9a  psubw xmm1,xmm0` | clamp max | [V] |
| bc38c9e | 4 | W | ctx+0x1EAB094 | `0xbc38c9e  movd [rcx+r12+0x1EAB094],xmm1` | store clear rect max | [V] |
| bc38ca8 | 3 | - | - | `0xbc38ca8  lea rdi,[r8+0x14C]` | rdi = a2+0x14C | [V] |
| bc38caf | 3 | - | - | `0xbc38caf  lea r14,[r8+0x10C]` | r14 = a2+0x10C | [V] |
| bc38cb6 | 3 | - | - | `0xbc38cb6  lea r15,[r8+0xB8]` | r15 = a2+0xB8 | [V] |
| bc38cbd | 7 | R | data_12ae1748 | `0xbc38cbd  mov r13,[0x12AE1748]` | ctx base | [V] |
| bc38cc4 | 3 | - | - | `0xbc38cc4  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| bc38cc8 | 4 | - | - | `0xbc38cc8  add rcx,0x1EAB0A0` | dst = +0x1EAB0A0 | [V] |
| bc38ccf | 4 | - | - | `0xbc38ccf  mov r8d,0x40` | len 0x40 | [V] |
| bc38cd5 | 5 | C | 0xEBCE390 | `0xbc38cd5  call 0xEBCE390` | memcpy dst=+0x1EAB0A0 src=a2+0xB8 len=0x40 | [V] |
| bc38cda | 3 | - | - | `0xbc38cda  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| bc38cde | 4 | - | - | `0xbc38cde  add rcx,0x1EAB0E0` | dst = +0x1EAB0E0 | [V] |
| bc38ce5 | 4 | - | - | `0xbc38ce5  mov r8d,0x40` | len 0x40 | [V] |
| bc38ceb | 2 | - | - | `0xbc38ceb  mov rdx,r15` | src = a2+0xB8 | [V] |
| bc38cee | 5 | C | 0xEBCE390 | `0xbc38cee  call 0xEBCE390` | memcpy dst=+0x1EAB0E0 src=a2+0xB8 len=0x40 | [V] |
| bc38cf3 | 3 | - | - | `0xbc38cf3  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| bc38cf7 | 4 | - | - | `0xbc38cf7  add rcx,0x1EAB120` | dst = +0x1EAB120 | [V] |
| bc38cfe | 4 | - | - | `0xbc38cfe  mov r8d,0x40` | len 0x40 | [V] |
| bc38d04 | 2 | - | - | `0xbc38d04  mov rdx,r14` | src = a2+0x10C | [V] |
| bc38d07 | 5 | C | 0xEBCE390 | `0xbc38d07  call 0xEBCE390` | memcpy dst=+0x1EAB120 src=a2+0x10C len=0x40 | [V] |
| bc38d0c | 3 | - | - | `0xbc38d0c  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| bc38d10 | 4 | - | - | `0xbc38d10  add rcx,0x1EAB160` | dst = +0x1EAB160 | [V] |
| bc38d17 | 4 | - | - | `0xbc38d17  mov r8d,0x40` | len 0x40 | [V] |
| bc38d1d | 2 | - | - | `0xbc38d1d  mov rdx,rdi` | src = a2+0x14C | [V] |
| bc38d20 | 5 | C | 0xEBCE390 | `0xbc38d20  call 0xEBCE390` | memcpy dst=+0x1EAB160 src=a2+0x14C len=0x40 | [V] |
| bc38d25 | 3 | - | - | `0xbc38d25  lea rcx,[r12+r13]` | rcx = ctx+r12 | [V] |
| bc38d29 | 4 | - | - | `0xbc38d29  add rcx,0x1EAB1A0` | dst = +0x1EAB1A0 | [V] |
| bc38d30 | 4 | - | - | `0xbc38d30  mov r8d,0x10` | len 0x10 | [V] |
| bc38d36 | 3 | - | - | `0xbc38d36  lea rdx,[rbx+0x18C]` | src = a2+0x18C | [V] |
| bc38d3d | 5 | C | 0xEBCE390 | `0xbc38d3d  call 0xEBCE390` | memcpy dst=+0x1EAB1A0 src=a2+0x18C len=0x10 | [V] |
| bc38d42 | 4 | R | a2+0x108 | `0xbc38d42  movzx eax,byte ptr [rbx+0x108]` | sort byte | [V] |
| bc38d49 | 7 | R | data_12ae1748 | `0xbc38d49  mov rcx,[0x12AE1748]` | ctx base | [V] |
| bc38d50 | 4 | W | ctx+0x1EAB1B2 | `0xbc38d50  mov [rcx+r12+0x1EAB1B2],al` | store sort byte | [V] |
| bc38d58 | 4 | R | a1+0x8 | `0xbc38d58  mov rcx,[rsi+8]` | rcx = a1+0x8 | [V] |
| bc38d5c | 8 | R | a2+0x0 | `0xbc38d5c  mov rax,[rbx]` | rax = a2+0x0 | [V] |
| bc38d5f | 8 | W | rbp+0xE0 | `0xbc38d5f  mov [rbp+0xE0],rax` | scope ptr | [V] |
| bc38d66 | 16 | W | rbp+0xE8 | `0xbc38d66  movdqu [rbp+0xE8],xmm6` | zero | [V] |
| bc38d6e | 8 | R | a2+0x10 | `0xbc38d6e  mov rax,[rbx+0x10]` | rax = a2+0x10 | [V] |
| bc38d72 | 3 | - | - | `0xbc38d72  test rax,rax` | null check | [V] |
| bc38d75 | 2 | - | - | `0xbc38d75  je short 0xBC38D81` | if null -> eax=0 | [V] |
| bc38d77 | 4 | R | *(a2+0x10)+0x8 | `0xbc38d77  lock inc dword ptr [rax+8]` | refcount++ | [V] |
| bc38d7b | 8 | R | a2+0x10 | `0xbc38d7b  mov rax,[rbx+0x10]` | rax = a2+0x10 | [V] |
| bc38d7f | 2 | - | - | `0xbc38d7f  jmp short 0xBC38D83` | -> loc | [V] |
| bc38d81 | 2 | - | - | `0xbc38d81  xor eax,eax` | eax = 0 | [V] |
| bc38d83 | 8 | R | a2+8 | `0xbc38d83  mov rdx,[rbx+8]` | rdx = a2+8 | [V] |
| bc38d87 | 8 | W | rbp+0xE8 | `0xbc38d87  mov [rbp+0xE8],rdx` | scope ctrl | [V] |
| bc38d8e | 8 | W | rbp+0xF0 | `0xbc38d8e  mov [rbp+0xF0],rax` | scope obj | [V] |
| bc38d95 | 16 | W | rbp+0xF8 | `0xbc38d95  movdqu [rbp+0xF8],xmm6` | zero | [V] |
| bc38d9d | 8 | W | rbp+0x108 | `0xbc38d9d  mov qword ptr [rbp+0x108],0` | zero | [V] |
| bc38da8 | 3 | W | rbp+0x110 | `0xbc38da8  mov byte ptr [rbp+0x110],1` | flag = 1 | [V] |
| bc38daf | 3 | - | - | `0xbc38daf  lea rdx,[rbp+0xE0]` | rdx = &scope | [V] |
| bc38db6 | 2 | - | - | `0xbc38db6  mov r14,rcx` | r14 = a1+0x8 (saved) | [V] |
| bc38db9 | 5 | C | 0xBCC1A30 | `0xbc38db9  call 0xBCC1A30` | scope register | [V] |
| bc38dbe | 1 | - | - | `0xbc38dbe  nop` | padding | [V] |
| bc38dbf | 8 | R | a2+0x70 | `0xbc38dbf  mov rdi,[rbx+0x70]` | rdi = a2+0x70 (entries base) | [V] |
| bc38dc3 | 8 | R | a2+0x48 | `0xbc38dc3  mov rsi,[rbx+0x48]` | rsi = a2+0x48 | [V] |
| bc38dc7 | 8 | W | rbp+0x218 | `0xbc38dc7  mov [rbp+0x218],rbx` | save a0 | [V] |
| bc38dce | 8 | R | a2+0x68 | `0xbc38dce  mov rbx,[rbx+0x68]` | rbx = a2+0x68 (entries end) | [V] |
| bc38dd2 | 8 | W | rbp+0x38 | `0xbc38dd2  mov [rbp+0x38],r14` | save a1+0x8 | [V] |
| bc38dd6 | 3 | - | - | `0xbc38dd6  pxor xmm0,xmm0` | zero | [V] |
| bc38dda | 16 | W | rbp+0x40 | `0xbc38dda  movdqu [rbp+0x40],xmm0` | zero | [V] |
| bc38ddf | 16 | W | rbp+0x50 | `0xbc38ddf  movdqu [rbp+0x50],xmm0` | zero | [V] |
| bc38de4 | 16 | W | rbp+0x60 | `0xbc38de4  movdqu [rbp+0x60],xmm0` | zero | [V] |
| bc38de9 | 16 | W | rbp+0x70 | `0xbc38de9  movdqu [rbp+0x70],xmm0` | zero | [V] |
| bc38dee | 8 | W | rbp+0x80 | `0xbc38dee  mov qword ptr [rbp+0x80],0` | zero | [V] |
| bc38df9 | 8 | W | rbp+0x228 | `0xbc38df9  mov [rbp+0x228],r14` | save a1+0x8 | [V] |
| bc38e00 | 8 | R | r14+0x10 | `0xbc38e00  mov rcx,[r14+0x10]` | rcx = (a1+0x8)+0x10 | [V] |
| bc38e04 | 5 | C | 0xBC60D10 | `0xbc38e04  call 0xBC60D10` | Encoder::reset | [V] |
| bc38e09 | 1 | - | - | `0xbc38e09  nop` | padding | [V] |
| bc38e0a | 3 | - | - | `0xbc38e0a  cmp rdi,rbx` | base == end? | [V] |
| bc38e0d | 8 | R | rbp+0x228 | `0xbc38e0d  mov rdx,[rbp+0x228]` | rdx = a1+0x8 | [V] |
| bc38e14 | 2 | - | - | `0xbc38e14  jne short 0xBC38E80` | if not empty -> loop setup | [V] |
| bc38e16 | 3 | - | - | `0xbc38e16  lea rcx,[rbp+0x58]` | rcx = &local | [V] |
| bc38e1a | 5 | C | 0x568DA90 | `0xbc38e1a  call 0x568DA90` | helper | [V] |
| bc38e1f | 8 | R | rbp+0x40 | `0xbc38e1f  mov rcx,[rbp+0x40]` | rcx = local | [V] |
| bc38e23 | 3 | - | - | `0xbc38e23  test rcx,rcx` | null? | [V] |
| bc38e26 | 2 | - | - | `0xbc38e26  je short 0xBC38E59` | if null -> tail | [V] |
| bc38e28 | 8 | R | rbp+0x50 | `0xbc38e28  mov rdx,[rbp+0x50]` | rdx = end | [V] |
| bc38e2c | 3 | - | - | `0xbc38e2c  sub rdx,rcx` | rdx = size | [V] |
| bc38e2f | 3 | - | - | `0xbc38e2f  cmp rdx,0x1000` | if >= 0x1000 -> free path | [V] |
| bc38e36 | 2 | - | - | `0xbc38e36  jb short 0xBC38E54` | if < 0x1000 -> call free | [V] |
| bc38e38 | 8 | R | rcx-8 | `0xbc38e38  mov rax,[rcx-8]` | heap header | [V] |
| bc38e3c | 3 | - | - | `0xbc38e3c  add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 | [V] |
| bc38e40 | 3 | - | - | `0xbc38e40  sub rcx,rax` | rcx = size - header | [V] |
| bc38e43 | 3 | - | - | `0xbc38e43  cmp rcx,0x20` | | [V] |
| bc38e47 | 5 | - | - | `0xbc38e47  jae 0xBC399AE` | -> fail block | [V] |
| bc38e4d | 3 | - | - | `0xbc38e4d  add rdx,0x27` | rdx += 0x27 | [V] |
| bc38e51 | 2 | - | - | `0xbc38e51  mov rcx,rax` | rcx = header | [V] |
| bc38e54 | 5 | C | 0xE935700 | `0xbc38e54  call 0xE935700` | heap free | [V] |
| bc38e59 | 3 | - | - | `0xbc38e59  lea rcx,[rbp+0xE0]` | rcx = &scope | [V] |
| bc38e60 | 5 | C | 0x655CEA0 | `0xbc38e60  call 0x655CEA0` | scope release | [V] |
| bc38e65 | 16 | R | rbp+0x240 | `0xbc38e65  movaps xmm6,[rbp+0x240]` | restore xmm6 | [V] |
| bc38e6c | 4 | - | - | `0xbc38e6c  add rsp,0x2D8` | tear down | [V] |
| bc38e73 | 1 | - | - | `0xbc38e73  pop rbx` | restore | [V] |
| bc38e74 | 1 | - | - | `0xbc38e74  pop rdi` | restore | [V] |
| bc38e75 | 1 | - | - | `0xbc38e75  pop rsi` | restore | [V] |
| bc38e76 | 1 | - | - | `0xbc38e76  pop r12` | restore | [V] |
| bc38e78 | 1 | - | - | `0xbc38e78  pop r13` | restore | [V] |
| bc38e7a | 1 | - | - | `0xbc38e7a  pop r14` | restore | [V] |
| bc38e7c | 1 | - | - | `0xbc38e7c  pop r15` | restore | [V] |
| bc38e7e | 1 | - | - | `0xbc38e7e  pop rbp` | restore | [V] |
| bc38e7f | 1 | - | - | `0xbc38e7f  ret` | return | [V] |

(Loop body 0xBC38E80..0xBC39A5C decoded in prior windows @12-@14: bucket build via word [entry+0x2C]<<7 + 3*word into 0x88-stride table at [rax+0x750]; chain walk comparing entry+0x78; per-instance call 0x568DB90; material dedup stride 0x18 over 0x58-byte records at [r9+0x738]; per-material calls 0xBC05AF0 / 0xC4BBA0 / 0xBCC1910 / 0xBCC24F0 / 0xBCC3190; per-item calls 0xBCC2B00 / 0xBCC2EB0 / conditional 0xBCC38E0 when word [rbx+0x42]; all-ones tail at 0xBC39A5C: call 0xE935700, zero locals, then ret path 0xBC39A75: movdqa xmm6,[rsp+0x30]; add rsp,0x48; pop rbx,rdi,rsi,r12,r13,r14,r15,rbp; ret.)

Semantics: computes clear rect into ctx view slot [I]; 5x memcpy via 0xEBCE390 (offsets +0x1EAB0A0/0xE0/0x120/0x160/0x1A0 from a2+0xB8/0x10C/0x14C/0x18C) [I]; stores sort byte a2+0x108 at ctx+0x1EAB1B2 [I]; builds scope object at rbp+0xE0 ({rax=[a2], lock inc [rax+8], byte=1}) and calls 0xBCC1A30 [I]; iterates 0x28-stride entries from a2+0x70 to a2+0x68, calling Encoder::reset then bucketing/draw logic with per-instance 0x568DB90, material bind 0xE86D7F0, state apply 0xBCC1910/0xBCC24F0/0xBCC3190, stream bind 0xBCC2B00/0xBCC2EB0, conditional submit 0xBCC38E0 [I]; empty range -> tail scope release + ret; heap free 0xE935700 on local buffer [I]. Size 0xDA8.

## 3. Executor 0xe821120 continuation — NOT STARTED

D2-partial: body not instruction-complete [V: e821120.md status]. Decoded regions so far (verbatim from e821120.md):
- item loop head/draw path head 0xe8221f5..0xe822834 [V]
- state reset/root sig/streams 0xe822830..0xe822c68 [V]
- layouts/PSO/batch-compat/bind cache 0xe822c68..0xe822fd0 [V]
- descriptor tables/stencil/blend/topology/scissor/PSO bind 0xe829cd2..0xe82a172 [V]
- uniforms/program constants 0xe82a140..0xe82a4b0 [V]
- indirect draws/append 0xe82c40f..0xe82cd2f [V]
- predefined uniforms dispatch 0xe82a49e..0xe82bfe9 [V]
- bind-cache miss descriptor build 0xe825a19.. [V structure, cases partly]

Not decoded: prologue/job-state setup (0xe821120..0xe8221f5), branch A program-variant resolve 0xe822480..0xe822a40, branch B 0xe829b50..0xe829cd2, descriptor build bodies, constant commit helpers, clear/RT handling, RT branch, tail. Continuation proceeds by `rdis dis` windows; finished regions are listed above so the next run resumes at the first undecoded region.

## ANSWER — COMPLETE

All three D2? YES — wrapper 0xe83c390 D2, five task bodies D2 (0x56AD350 ClearColorDepth, 0x569A3A0 ClearDepth, 0xBC38C20 Pass, 0xBC02090 TerrainAtlasBlit, 0x56AEEB0 SceneWaitOnChunk; Scene/HUD 0x568CD90 already D2 and not redone). Executor 0xe821120 continuation NOT decoded this run (remains D2-partial; decoded regions listed above).
