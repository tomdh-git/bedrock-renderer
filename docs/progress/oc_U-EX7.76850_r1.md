## NEXT
DONE: static reversal of sub_76850 (0x76850, size 0x78) is complete and written to docs/functions/76850.md; the unit is BLOCKED — callee 0xeec6e20 (call at 0x7688e `call 0xEEC6E20`) is in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv, so per the GOAL it is an UNRESOLVED CALL, no wrapper is invented, and the lift stops. No .cpp/.h written (an invented wrapper is forbidden; a partial lift would fail liftcheck). CLOSES? NO — see final line.

## UNIT
U-EX7.76850 LIFT sub_76850 (0x76850, 0x78 bytes, depth 0, D0, 0 callees in set). Source of truth: docs/progress/_d_U-EX7.76850.txt (row `0x76850 0x78 0 7 root D0 added 0x76850 <empty> 0xe951550`: callees_in_set empty, callees_outside_set 0xe951550).

## DISASSEMBLY (verbatim, `rdis ... dis 0x76850 0x78`, range [0x76850, 0x768c8), 30 instructions)
The function ends right after `0x768c2  call 0xE951550` (its last byte 0x768c7 = last byte of the range); the int3 padding at 0x768c8+ and the code at 0x768d0 are outside the function range.
0x76850  push rsi
0x76851  sub rsp,0x40
0x76855  mov rsi,rcx
0x76858  mov rax,[0x1230A0C0]
0x7685f  xor rax,rsp
0x76862  mov [rsp+0x38],rax
0x76867  lea rax,[0xEFC6C70]
0x7686e  mov [rcx],rax
0x76871  lea rax,[rcx+8]
0x76875  xorps xmm0,xmm0
0x76878  movups [rcx+8],xmm0
0x7687c  mov [rsp+0x28],rdx
0x76881  mov byte ptr [rsp+0x30],1
0x76886  lea rcx,[rsp+0x28]
0x7688b  mov rdx,rax
0x7688e  call 0xEEC6E20
0x76893  lea rax,[0xEFC6C70]
0x7689a  mov [rsi],rax
0x7689d  mov rax,[rsp+0x38]
0x768a2  xor rax,rsp
0x768a5  mov rcx,[0x1230A0C0]
0x768ac  cmp rcx,rax
0x768af  jne short 0x768BA
0x768b1  mov rax,rsi
0x768b4  add rsp,0x40
0x768b8  pop rsi
0x768b9  ret
0x768ba  mov rcx,[rsp+0x38]
0x768bf  xor rcx,rsp
0x768c2  call 0xE951550

## REVERSAL (complete, every instruction covered by a cited range)
Signature: `void* sub_76850(void* a0 /*RCX*/, void* a2 /*RDX*/)`; returns `a0` (RAX = RSI = incoming RCX). Frame: `sub rsp,0x40`; slots [rsp+0x28] = a2 (qword), [rsp+0x30] = 1 (byte), [rsp+0x38] = stack-cookie stash (qword).
- // 0x76850..0x76855: prologue `push rsi; sub rsp,0x40; mov rsi,rcx` — save a0 in RSI.
- // 0x76858..0x76862: `mov rax,[0x1230A0C0]  ; xor rax,rsp  ; mov [rsp+0x38],rax` — cookie stash = [data_1230a0c0] ^ rsp.
- // 0x76867..0x7686e: `lea rax,[0xEFC6C70]  ; mov [rcx],rax` — W a0+0x0 = address of data_efc6c70 (0xEFC6C70).
- // 0x76871..0x76875: `lea rax,[rcx+8]  ; xorps xmm0,xmm0` — rax = a0+8 (survives to 0x7688b).
- // 0x76878: `movups [rcx+8],xmm0` — W a0+0x8..0x18 = 0 (16 bytes).
- // 0x7687c..0x76881: `mov [rsp+0x28],rdx  ; mov byte ptr [rsp+0x30],1` — stack block {a2, 1} at [rsp+0x28].
- // 0x76886..0x7688b: `lea rcx,[rsp+0x28]  ; mov rdx,rax` — RCX = &stack block, RDX = a0+8.
- // 0x7688e: `call 0xEEC6E20` — UNRESOLVED CALL (see below). Return value discarded.
- // 0x76893..0x7689a: `lea rax,[0xEFC6C70]  ; mov [rsi],rax` — W a0+0x0 = address of data_efc6c70 again (same value; rsi == a0).
- // 0x7689d..0x768a2: `mov rax,[rsp+0x38]  ; xor rax,rsp` — decoded cookie.
- // 0x768a5..0x768ac: `mov rcx,[0x1230A0C0]  ; cmp rcx,rax` — cookie verify against [data_1230a0c0].
- // 0x768af: `jne short 0x768BA` — mismatch → noreturn path; match → fall through.
- // 0x768b1..0x768b9: `mov rax,rsi  ; add rsp,0x40  ; pop rsi  ; ret` — return a0.
- // 0x768ba..0x768bf: `mov rcx,[rsp+0x38]  ; xor rcx,rsp` — decoded cookie (possibly tampered).
- // 0x768c2: `call 0xE951550` — boundary crt stack-cookie check, noreturn on mismatch.

## FILES
- docs/progress/oc_U-EX7.76850.md (this result file)
- docs/functions/76850.md (dossier: analysis + 'Reversed source (complete)', created)

## LIFTCHECK
(not LIFTCHECK OK — the lift cannot be completed because of the UNRESOLVED CALL below; no lift source file can be written without inventing a wrapper for 0xeec6e20, which is forbidden. Ran anyway to record the mechanical state.)
Actual output of `python tools/sigs/liftcheck.py 0x76850` (exit code 1):

```
  - no source file under src/client/features/render/native whose first line is '// LIFT 0x76850 size 0x...'
LIFTCHECK FAIL 0x76850
```

## UNRESOLVED CALL
0xeec6e20 — caller instruction `0x7688e  call 0xEEC6E20` (5-byte E8 rel32, at 0x7688e..0x76893, inside [0x76850, 0x768c8)). Target 0xeec6e20: grep over docs/data found NO match in docs/data/native_functions.tsv (not a lift-set callee, no native symbol to forward-declare) and NO match in docs/data/native_boundary.tsv line 467 is 0xe951550 only (no boundary wrapper). Per GOAL: write as UNRESOLVED CALL with the address, do not invent a wrapper, stop. The only other call, `0x768c2  call 0xE951550`, resolves to the boundary crt `sub_e951550` (class crt, native_boundary.tsv line 467) and is not a blocker.

## TOOL REQUESTS
None (existing tools only: rdis dis, grep of docs/data).

CLOSES? NO — UNRESOLVED CALL: `0x7688e  call 0xEEC6E20`; target 0xeec6e20 is in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv, so there is no native symbol or boundary wrapper for it and the lift of sub_76850 cannot be completed without inventing a wrapper (forbidden).
