# sub_bcd4c30 0xbcd4c30 size 0xed

## Identity
- RVA: 0xbcd4c30, size 0xed bytes ([0xbcd4c30, 0xbcd4d1d)), depth 0, milestone 7, region helpers.
- Root: added 0xbcd4c30. Callees in lift set: (none). Callees outside set: (none).
- Lifted at: src/client/features/render/native/helpers/sub_bcd4c30.cpp (+ .h) [scaffold placeholder; not yet lifted].

## Signature (x64 Microsoft ABI) [open]
uintptr_t sub_bcd4c30(sub_bcd4c30_state* self);   // placeholder; exact return/argument types TBD

## Register / argument map [open]
- rcx is copied to rsi in the prologue (`0xbcd4c30  mov rsi,rcx`) if that instruction is present; the 'this' register and argument meanings are [open].
- Return value in rax: [open].

## Phases (instruction-complete, [0xbcd4c30, 0xbcd4d1d))

0xbcd4c30..0xbcd4d1d: whole function (scaffold placeholder; split into phases during the lift).
  0xbcd4c30  push rsi
  0xbcd4c31  sub rsp,0x30
  0xbcd4c35  cmp rcx,2
  0xbcd4c39  jb 0xBCD4CFD
  0xbcd4c3f  cmp rcx,3
  0xbcd4c43  jne short 0xBCD4CA4
  0xbcd4c45  mov rax,[r8+0x38]
  0xbcd4c49  cmp rax,0x10
  0xbcd4c4d  jb short 0xBCD4C8F
  0xbcd4c4f  mov rcx,[r8+0x20]
  0xbcd4c53  lea rdx,[rax+1]
  0xbcd4c57  cmp rdx,0x1000
  0xbcd4c5e  jb short 0xBCD4C84
  0xbcd4c60  mov r9,[rcx-8]
  0xbcd4c64  add rcx,0xFFFFFFFFFFFFFFF8
  0xbcd4c68  sub rcx,r9
  0xbcd4c6b  cmp rcx,0x20
  0xbcd4c6f  jae 0xBCD4D03
  0xbcd4c75  mov rsi,r8
  0xbcd4c78  add rax,0x28
  0xbcd4c7c  mov rdx,rax
  0xbcd4c7f  mov rcx,r9
  0xbcd4c82  jmp short 0xBCD4C87
  0xbcd4c84  mov rsi,r8
  0xbcd4c87  call 0xE935700
  0xbcd4c8c  mov r8,rsi
  0xbcd4c8f  mov qword ptr [r8+0x30],0
  0xbcd4c97  mov qword ptr [r8+0x38],0xF
  0xbcd4c9f  mov byte ptr [r8+0x20],0
  0xbcd4ca4  mov rax,[r8+0x18]
  0xbcd4ca8  cmp rax,0x10
  0xbcd4cac  jb short 0xBCD4CE9
  0xbcd4cae  mov rcx,[r8]
  0xbcd4cb1  lea rdx,[rax+1]
  0xbcd4cb5  cmp rdx,0x1000
  0xbcd4cbc  jb short 0xBCD4CDE
  0xbcd4cbe  mov r9,[rcx-8]
  0xbcd4cc2  add rcx,0xFFFFFFFFFFFFFFF8
  0xbcd4cc6  sub rcx,r9
  0xbcd4cc9  cmp rcx,0x20
  0xbcd4ccd  jae short 0xBCD4D03
  0xbcd4ccf  mov rsi,r8
  0xbcd4cd2  add rax,0x28
  0xbcd4cd6  mov rdx,rax
  0xbcd4cd9  mov rcx,r9
  0xbcd4cdc  jmp short 0xBCD4CE1
  0xbcd4cde  mov rsi,r8
  0xbcd4ce1  call 0xE935700
  0xbcd4ce6  mov r8,rsi
  0xbcd4ce9  mov qword ptr [r8+0x10],0
  0xbcd4cf1  mov qword ptr [r8+0x18],0xF
  0xbcd4cf9  mov byte ptr [r8],0
  0xbcd4cfd  add rsp,0x30
  0xbcd4d01  pop rsi
  0xbcd4d02  ret
  0xbcd4d03  mov qword ptr [rsp+0x20],0
  0xbcd4d0c  xor ecx,ecx
  0xbcd4d0e  xor edx,edx
  0xbcd4d10  xor r8d,r8d
  0xbcd4d13  xor r9d,r9d
  0xbcd4d16  call qword ptr [0xF9A8C78]
  0xbcd4d1c  int3

## Struct fields touched [open]

| offset | size | R/W | meaning | tag |
|---|---|---|---|---|
| +0x10 | ? | ? | meaning unknown | [open] |
| +0x18 | ? | ? | meaning unknown | [open] |
| +0x20 | ? | ? | meaning unknown | [open] |
| +0x30 | ? | ? | meaning unknown | [open] |
| +0x38 | ? | ? | meaning unknown | [open] |

## Callees [V]

- 0xbcd4c87 (sub_e935700) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xE935700` [[V]]
- 0xbcd4ce1 (sub_e935700) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xE935700` [[V]]
- 0xbcd4d16 (indirect via 0xF9A8C78) -> data-slot indirect call (boundary TBD): `call qword ptr [0xF9A8C78]` [[V]]

## Verbatim instruction quotes (all calls in the function)

0xbcd4c87  call 0xE935700
0xbcd4ce1  call 0xE935700
0xbcd4d16  call qword ptr [0xF9A8C78]

## Reversed source (complete)

Lifted into src/client/features/render/native/helpers/sub_bcd4c30.cpp (+ .h).
Signature: uintptr_t sub_bcd4c30(uint64_t count, uint64_t unused_rdx, sub_bcd4c30_state* state);
count arrives in RCX, the state pointer in R8; RDX is passed but unread by the original.
RAX is dead at ret in the original, so the lift returns 0.

Control flow: count < 2 returns immediately (0xbcd4c35 cmp rcx,2 ; 0xbcd4c39 jb 0xBCD4CFD).
Otherwise the state's two small-string buffers are released in order:
buffer 1 (ptr +0x20, size +0x30, cap +0x38) only when count == 3
(0xbcd4c3f cmp rcx,3 ; 0xbcd4c43 jne 0xBCD4CA4 skips it), then buffer 0
(ptr +0x00, size +0x10, cap +0x18) whenever count >= 2 (0xbcd4ca4..0xbcd4cfd).

Per buffer (release path):
- 0xbcd4c45 cmp rax,[r8+0x38],0x10 ; jb -> reset when cap < 0x10 (inline/empty state,
  no heap allocation): size = 0 (0xbcd4c8f / 0xbcd4ce9), cap = 0xF (0xbcd4c97 / 0xbcd4cf1),
  low byte of the pointer field = 0 (0xbcd4c9f / 0xbcd4cf9).
- Otherwise the pointer (0xbcd4c4f [r8+0x20] / 0xbcd4cae [r8]) is heap-backed.
  If cap + 1 < 0x1000 (0xbcd4c57 / 0xbcd4cb5) the buffer is released directly:
  0xbcd4c87 / 0xbcd4ce1 call 0xE935700 -> native::sub_e935700(void*) with RCX = buffer
  (RDX = cap + 1, dead inside the callee; the state pointer in R8 is restored after).
- Otherwise (cap + 1 >= 0x1000) the heap block is validated:
  bias = (ptr - 8) - *(uint64_t*)(ptr - 8) (0xbcd4c60 mov r9,[rcx-8] / 0xbcd4cbe,
  0xbcd4c64 add rcx,-8 / 0xbcd4cc2, 0xbcd4c68 sub rcx,r9 / 0xbcd4cc6);
  bias >= 0x20 (0xbcd4c6b / 0xbcd4cc9 cmp rcx,0x20 ; jae) takes the failfast path:
  0xbcd4d03 mov [rsp+0x20],0 (dead store), zeroed arguments, 0xbcd4d16 call qword ptr
  [0xF9A8C78] (target read from the data slot at call time), 0xbcd4d1c int3 trap if it returns.
  When valid, 0xbcd4c87 / 0xbcd4ce1 call 0xE935700 with RCX = *(uint64_t*)(ptr - 8),
  RDX = cap + 0x28 (dead inside the callee).
- After the release (or directly in the inline case): size = 0, cap = 0xF,
  pointer low byte = 0, in that write order (0xbcd4c8f..0xbcd4c9f / 0xbcd4ce9..0xbcd4cf9).

Epilogue: 0xbcd4cfd add rsp,0x30 ; 0xbcd4d01 pop rsi ; 0xbcd4d02 ret.

## DECISIONS (resolved during the lift)

- Signature: uintptr_t sub_bcd4c30(uint64_t count, uint64_t unused_rdx, sub_bcd4c30_state* state);
  count in RCX, state pointer in R8, RDX unread; returns 0. Cited: 0xbcd4c35 (count compare) and the
  [r8 + off] field accesses throughout.
- 'this' register: there is no conventional this pointer; the state is the third argument (R8),
  and RCX is the buffer count, not a pointer.
- Struct layout: sub_bcd4c30_state with buffer 0 (+0x00 ptr, +0x10 size, +0x18 cap) and
  buffer 1 (+0x20 ptr, +0x30 size, +0x38 cap); cap < 0x10 denotes the inline/empty state.
  Offset static_asserts for every field read or written are in the .h and .cpp.
- Callees: call 0xE935700 (0xbcd4c87, 0xbcd4ce1) -> native::sub_e935700(void*), a lift-set
  callee called directly through its native symbol; only RCX is read inside the callee, so the
  RDX/R8 call-site values are dead there. call qword ptr [0xF9A8C78] (0xbcd4d16) ->
  data-slot failfast with four zeroed arguments, target read from the slot at call time
  (no static target by design; not an unresolved direct call).
- Heap validation: bias = (ptr - 8) - *(uint64_t*)(ptr - 8); bias >= 0x20 takes the failfast
  path. Cited: 0xbcd4c60..0xbcd4c6f and 0xbcd4cbe..0xbcd4ccd.
- Release condition per buffer: cap >= 0x10 and heap-backed -> release through sub_e935700
  (small release passes cap + 1 in RDX; validated release passes cap + 0x28 in RDX,
  both dead inside the callee); otherwise inline reset only.
- Return value: undefined in the original (nothing stored to RAX before ret); the lift
  returns 0.
