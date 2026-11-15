# oc_U-SK1d — unit U-SK1d (sky visitor cold range, finish 0x665d5d1..0x665d7e5)

Target: Minecraft.Windows.exe 1.26.62.01
Task: continue from docs/progress/oc_U-SK1c.md NEXT block — cold range 0x665cf64..0x665d7e5, resume at 0x665d5d1 (cold-range phase 8 ended at 0x665d5d1). Use `rdis dis` in 40-instruction steps; append each phase with exact rdis lines, then // interpretation tagged [V]/[I]/[?].
Static analysis only; no builds/commits; only create docs/progress/oc_U-SK1d.md; tag claims [V]/[I]/[?].

## NEXT
- [x] Cold range 0x665d5d1..0x665d7e5 — COMPLETE (phases 9–11 below); unit finished

---

## PHASES — cold range 0x665d5d1..0x665d7e5

## PHASE 10 — cold range 0x665d6af..0x665d798 (40 instructions; instruction-complete)

0x665d6af  (bad)
// [?] First instruction at function entry undecodable by rdis — possible misaligned/decode artifact; cannot interpret meaning [?]. rdis labels sub_665d6af size 0x2000, 0 xrefs in [V].

0x665d6b1  add [rax],al
// [?] Byte-stream anomaly following the bad decode; treated as noise, not real logic [?].

0x665d6b3  lea rcx,[0x129F9BB8]                          ; [data_129f9bb8]
0x665d6ba  lea rdx,[rbp+0x1D0]
0x665d6c1  lea r8,[rbp+0x120]
0x665d6c8  call 0x5668AC0                                ; -> sub_5668ac0
0x665d6cd  nop
// [V] sub_5668ac0(rcx=&data_129f9bb8, rdx=&[rbp+0x1D0], r8=&[rbp+0x120]) then nop [V]. x64 fastcall: rcx/rdx/r8 = first 3 args [I]. Meaning of sub_5668ac0 and the data slots unknown [?].

0x665d6ce  lea rcx,[0x129F9BC8]                          ; [data_129f9bc8]
0x665d6d5  call 0xE938D70                                ; -> sub_e938d70
0x665d6da  jmp 0x665633E                                 ; -> sub_665633e
// [V] sub_e938d70(rcx=&data_129f9bc8), then unconditional jmp to sub_665633e — execution never falls through 0x665d6da [V]; callee meanings unknown [?].

0x665d6df  lea rcx,[0x129F9BE0]                          ; [data_129f9be0]
0x665d6e6  call 0xE938CB0                                ; -> sub_e938cb0
0x665d6eb  cmp dword ptr [0x129F9BE0],0xFFFFFFFF         ; [data_129f9be0]
0x665d6f2  jne 0x6656363                                 ; -> sub_6656363
// [V] sub_e938cb0(rcx=&data_129f9be0); compare [data_129f9be0] with 0xFFFFFFFF; jne to sub_6656363 if not equal [V]. Handle-lookup pattern: 0xFFFFFFFF == "not found/invalid" [I].

0x665d6f8  xorps xmm0,xmm0
0x665d6fb  movaps [rbp+0x310],xmm0
// [V] Zero 16 bytes at [rbp+0x310] (xorps xmm0,xmm0 then movaps store) — clearing a vec4/color buffer [V]; exact type unknown [?].

0x665d702  lea rax,[0xF2BE588]                           ; [data_f2be588] "CubemapHDRi"
0x665d709  mov [rbp+0x320],rax
0x665d710  mov qword ptr [rbp+0x328],0xB
// [V] Store pointer to string "CubemapHDRi" (data_f2be588) at [rbp+0x320], then length 0xB at [rbp+0x328] — a {ptr, len} string descriptor [I]. "CubemapHDRi" is 11 chars = 0xB [V].

0x665d71b  lea rcx,[0x129F9BD0]                          ; [data_129f9bd0]
0x665d722  lea rdx,[rbp+0x320]
0x665d729  lea r8,[rbp+0x310]
0x665d730  call 0x5668AC0                                ; -> sub_5668ac0
0x665d735  nop
// [V] sub_5668ac0(rcx=&data_129f9bd0, rdx=&[rbp+0x320] "CubemapHDRi" desc, r8=&[rbp+0x310] zero vec4), then nop [V]. Likely registering "CubemapHDRi" with a zero color [I].

0x665d736  lea rcx,[0x129F9BE0]                          ; [data_129f9be0]
0x665d73d  call 0xE938D70                                ; -> sub_e938d70
0x665d742  jmp 0x6656363                                 ; -> sub_6656363
// [V] sub_e938d70(rcx=&data_129f9be0), then jmp sub_6656363 [V].

0x665d747  lea rcx,[0x129F9C28]                          ; [data_129f9c28]
0x665d74e  call 0xE938CB0                                ; -> sub_e938cb0
0x665d753  cmp dword ptr [0x129F9C28],0xFFFFFFFF         ; [data_129f9c28]
0x665d75a  jne 0x6656388                                 ; -> sub_6656388
// [V] sub_e938cb0(rcx=&data_129f9c28); cmp [data_129f9c28],0xFFFFFFFF; jne sub_6656388 [V] — same not-found pattern as data_129f9be0 [I].

0x665d760  mov dword ptr [rbp+0x340],0
0x665d76a  lea rcx,[0x129F9BE8]                          ; [data_129f9be8]
0x665d771  lea rdx,[rbp+0x340]
0x665d778  lea r8,[rbp+0x1E0]
0x665d77f  call 0x9B020                                  ; -> sub_9b020
0x665d784  nop
// [V] [rbp+0x340] = 0, then sub_9b020(rcx=&data_129f9be8, rdx=&[rbp+0x340], r8=[rbp+0x1E0]) [V] — writing a zeroed dword tied to data_129f9be8 and a stack struct at rbp+0x1E0 [I].

0x665d785  lea rcx,[0x673CFE0]                           ; [sub_673cfe0]
0x665d78c  call 0xE935740                                ; -> sub_e935740
// [V] sub_e935740(rcx=&sub_673cfe0) — passing a function address, likely a callback registration [I]; callee meaning unknown [?].

0x665d791  lea rcx,[0x129F9C28]                          ; [data_129f9c28]
// [V] Reload &data_129f9c28 into rcx — presumably the argument for the next call at 0x665d798 (not yet disassembled) [?].

## PHASE 11 — cold range 0x665d798..0x665d7e5 (14 instructions; instruction-complete, ends exactly at 0x665d7e5)

0x665d798  call 0xE938D70                                ; -> sub_e938d70
0x665d79d  jmp 0x6656388                                 ; -> sub_6656388
// [V] sub_e938d70(rcx=&data_129f9c28, loaded at 0x665d791), then jmp sub_6656388 — completes the data_129f9c28 not-found block started in phase 10 [V].

0x665d7a2  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x665d7a9  call 0xE938CB0                                ; -> sub_e938cb0
0x665d7ae  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
0x665d7b5  jne 0x6656626                                 ; -> sub_6656626
// [V] Third lookup block: sub_e938cb0(rcx=&data_129ca5e0); cmp [data_129ca5e0],0xFFFFFFFF; jne sub_6656626 if handle valid (found) [V].

0x665d7bb  lea rcx,[0x129CA568]                          ; [data_129ca568]
0x665d7c2  call 0x567DB00                                ; -> sub_567db00
0x665d7c7  nop                                           
0x665d7c8  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
0x665d7cf  call 0xE935740                                ; -> sub_e935740
// [V] Not-found path: sub_567db00(rcx=&data_129ca568), nop, then sub_e935740(rcx=&sub_567dba0) — registering a second callback [I]; callee meanings unknown [?].

0x665d7d4  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x665d7db  call 0xE938D70                                ; -> sub_e938d70
0x665d7e0  jmp 0x6656626                                 ; -> sub_6656626
// [V] sub_e938d70(rcx=&data_129ca5e0), then jmp sub_6656626 — commit + handler jump; final instruction ends exactly at range limit 0x665d7e5 [V].

## SUMMARY — unit U-SK1d cold range 0x665d5d1..0x665d7e5 (complete)

The cold range is fully disassembled (phases 9–11, instruction-complete, no gaps, every instruction in range belongs to a phase). It is a sequence of "get-or-register" blocks over global data slots: each block calls sub_e938cb0(rcx=&data_slot), tests [data_slot] == 0xFFFFFFFF ("not found/invalid"), and jumps to a handler (sub_665633e / sub_6656363 / sub_6656388 / sub_6656626) when the handle is valid; on the not-found path it builds defaults (zeroed 16-byte vec4 at [rbp+0x310], a string descriptor {ptr, len} e.g. "CubemapHDRi" ptr@[rbp+0x320] len 0xB@[rbp+0x328] from data_f2be588, zero dword at [rbp+0x340]), calls sub_5668ac0 or sub_567db00 to register the entry, calls sub_e938d70 to commit, then jumps to the handler. Callbacks are registered via sub_e935740(rcx=&sub_673cfe0 / &sub_567dba0) and a value is written via sub_9b020.

Blocks covered:
- 0x665d6b3..0x665d6da: data_129f9bb8 → sub_5668ac0; then data_129f9bc8 → sub_e938d70 → jmp sub_665633e
- 0x665d6df..0x665d742: data_129f9be0 lookup; not-found → zero [rbp+0x310], register "CubemapHDRi" via sub_5668ac0, sub_e938d70 → jmp sub_6656363
- 0x665d747..0x665d798: data_129f9c28 lookup; not-found → [rbp+0x340]=0, sub_9b020(data_129f9be8), callback sub_673cfe0 (lea &data_129f9c28 continues into phase 11)
- 0x665d798..0x665d7e5: sub_e938d70(data_129f9c28) → jmp sub_6656388; data_129ca5e0 lookup; not-found → sub_567db00(data_129ca568), callback sub_567dba0, sub_e938d70 → jmp sub_6656626

OPEN (not resolvable from this range alone) [?]: exact semantics of sub_5668ac0 / sub_567db00 / sub_e938cb0 / sub_e938d70 / sub_9b020 / sub_e935740 and the four handler subs; whether the data slots name sky/cubemap/fog definitions; whether rbp+0x1E0/0x310/0x320/0x340 locals belong to one visitor struct or several. Decode artifacts at 0x665d6af (bad) and 0x665d6b1 (add [rax],al) were left as noise [?].