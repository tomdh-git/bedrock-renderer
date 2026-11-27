# sub_c2ae6c0 0xc2ae6c0 size 0x10d

## Identity
- RVA: 0xc2ae6c0, size 0x10d bytes ([0xc2ae6c0, 0xc2ae7cd)), depth 0, milestone 7, region helpers.
- Root: added 0xc2ae6c0. Callees in lift set: (none). Callees outside set: 0xc2aea90.
- Lifted at: src/client/features/render/native/helpers/sub_c2ae6c0.cpp (+ .h) [scaffold placeholder; not yet lifted].

## Signature (x64 Microsoft ABI) [open]
uintptr_t sub_c2ae6c0(sub_c2ae6c0_state* self);   // placeholder; exact return/argument types TBD

## Register / argument map [open]
- rcx is copied to rsi in the prologue (`0xc2ae6c0  mov rsi,rcx`) if that instruction is present; the 'this' register and argument meanings are [open].
- Return value in rax: [open].

## Phases (instruction-complete, [0xc2ae6c0, 0xc2ae7cd))

0xc2ae6c0..0xc2ae7cd: whole function (scaffold placeholder; split into phases during the lift).
  0xc2ae6c0  push rbp
  0xc2ae6c1  push r14
  0xc2ae6c3  push rsi
  0xc2ae6c4  push rdi
  0xc2ae6c5  push rbx
  0xc2ae6c6  sub rsp,0x40
  0xc2ae6ca  lea rbp,[rsp+0x40]
  0xc2ae6cf  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
  0xc2ae6d7  mov rsi,rcx
  0xc2ae6da  xorps xmm0,xmm0
  0xc2ae6dd  movaps [rbp-0x20],xmm0
  0xc2ae6e1  lea rdi,[rbp-0x20]
  0xc2ae6e5  nop [rax+rax]
  0xc2ae6f0  mov rcx,rsi
  0xc2ae6f3  mov rdx,rdi
  0xc2ae6f6  call 0xC2AEA90
  0xc2ae6fb  nop
  0xc2ae6fc  test al,al
  0xc2ae6fe  jne short 0xC2AE6F0
  0xc2ae700  xorps xmm0,xmm0
  0xc2ae703  movups [rsi+0x278],xmm0
  0xc2ae70a  movups [rsi+0x268],xmm0
  0xc2ae711  mov qword ptr [rsi+0x288],0
  0xc2ae71c  mov rbx,[rsi+0x290]
  0xc2ae723  mov r14,[rsi+0x298]
  0xc2ae72a  cmp rbx,r14
  0xc2ae72d  jne short 0xC2AE749
  0xc2ae72f  jmp short 0xC2AE78D
  0xc2ae731  nop [rax+rax]
  0xc2ae740  add rbx,0x10
  0xc2ae744  cmp rbx,r14
  0xc2ae747  je short 0xC2AE77F
  0xc2ae749  mov rdi,[rbx+8]
  0xc2ae74d  test rdi,rdi
  0xc2ae750  je short 0xC2AE740
  0xc2ae752  lock dec dword ptr [rdi+8]
  0xc2ae756  jne short 0xC2AE740
  0xc2ae758  mov rax,[rdi]
  0xc2ae75b  mov rax,[rax]
  0xc2ae75e  mov rcx,rdi
  0xc2ae761  call qword ptr [0xF99FFA0]
  0xc2ae767  lock dec dword ptr [rdi+0xC]
  0xc2ae76b  jne short 0xC2AE740
  0xc2ae76d  mov rax,[rdi]
  0xc2ae770  mov rax,[rax+8]
  0xc2ae774  mov rcx,rdi
  0xc2ae777  call qword ptr [0xF99FFA0]
  0xc2ae77d  jmp short 0xC2AE740
  0xc2ae77f  mov rax,[rsi+0x290]
  0xc2ae786  mov [rsi+0x298],rax
  0xc2ae78d  mov rsi,[rbp-0x18]
  0xc2ae791  test rsi,rsi
  0xc2ae794  je short 0xC2AE7C2
  0xc2ae796  lock dec dword ptr [rsi+8]
  0xc2ae79a  jne short 0xC2AE7C2
  0xc2ae79c  mov rax,[rsi]
  0xc2ae79f  mov rax,[rax]
  0xc2ae7a2  mov rcx,rsi
  0xc2ae7a5  call qword ptr [0xF99FFA0]
  0xc2ae7ab  lock dec dword ptr [rsi+0xC]
  0xc2ae7af  jne short 0xC2AE7C2
  0xc2ae7b1  mov rax,[rsi]
  0xc2ae7b4  mov rax,[rax+8]
  0xc2ae7b8  mov rcx,rsi
  0xc2ae7bb  call qword ptr [0xF99FFA0]
  0xc2ae7c1  nop
  0xc2ae7c2  add rsp,0x40
  0xc2ae7c6  pop rbx
  0xc2ae7c7  pop rdi
  0xc2ae7c8  pop rsi
  0xc2ae7c9  pop r14
  0xc2ae7cb  pop rbp
  0xc2ae7cc  ret

## Struct fields touched [open]

| offset | size | R/W | meaning | tag |
|---|---|---|---|---|
| +0x-20 | ? | ? | meaning unknown | [open] |
| +0x-18 | ? | ? | meaning unknown | [open] |
| +0x-8 | ? | ? | meaning unknown | [open] |
| +0x0 | ? | ? | meaning unknown | [open] |
| +0x8 | ? | ? | meaning unknown | [open] |
| +0xc | ? | ? | meaning unknown | [open] |
| +0x40 | ? | ? | meaning unknown | [open] |
| +0x268 | ? | ? | meaning unknown | [open] |
| +0x278 | ? | ? | meaning unknown | [open] |
| +0x288 | ? | ? | meaning unknown | [open] |
| +0x290 | ? | ? | meaning unknown | [open] |
| +0x298 | ? | ? | meaning unknown | [open] |

## Callees [V]

- 0xc2ae6f6 (sub_c2aea90) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xC2AEA90` [[V]]
- 0xc2ae761 (indirect via 0xF99FFA0) -> data-slot indirect call (boundary TBD): `call qword ptr [0xF99FFA0]` [[V]]
- 0xc2ae777 (indirect via 0xF99FFA0) -> data-slot indirect call (boundary TBD): `call qword ptr [0xF99FFA0]` [[V]]
- 0xc2ae7a5 (indirect via 0xF99FFA0) -> data-slot indirect call (boundary TBD): `call qword ptr [0xF99FFA0]` [[V]]
- 0xc2ae7bb (indirect via 0xF99FFA0) -> data-slot indirect call (boundary TBD): `call qword ptr [0xF99FFA0]` [[V]]

## DECISIONS

The following facts could not be derived by the scaffold and are [open] decisions
(never guesses). Fill them in during the lift; cite the instruction RVA for each.

- [open] signature: return type and exact argument types (currently `uintptr_t sub_sub_c2ae6c0(sub_c2ae6c0_state* self)`)
- [open] 'this' register: is rcx the this pointer (prologue `mov rsi,rcx` at 0xc2ae6c0), or is this passed elsewhere?
- [open] struct layout and sizeof: field names, meanings and offsets beyond the observed [reg+off] accesses
- [open] each observed field offset's size, direction (R/W) and semantic meaning
- [open] each callee classification: lift (in native_functions.tsv) vs boundary (native_boundary.tsv class)
- [open] indirect call targets via data slots (resolve the pointed-to function)
- [open] return value and its meaning on each exit path

## Verbatim instruction quotes (all calls in the function)

0xc2ae6f6  call 0xC2AEA90
0xc2ae761  call qword ptr [0xF99FFA0]
0xc2ae777  call qword ptr [0xF99FFA0]
0xc2ae7a5  call qword ptr [0xF99FFA0]
0xc2ae7bb  call qword ptr [0xF99FFA0]

## Reversed source (complete)

`sub_c2ae6c0(void* self)` releases a container: it drains the producer at 0xc2aea90
until it returns false, zeroes the 16-byte slots at +0x268/+0x278 and the qword at
+0x288, then walks the 16-byte elements in [+0x290, +0x298), releasing each element's
control block (strong count at +0x08, weak count at +0x0c, virtual destroy through
vtable slots 0 and 1). The array end at +0x298 is set to its begin at +0x290, and the
control block left in the 16-byte drain slot ([rbp-0x18]) is released the same way.
No path writes a return register, so the lift returns void.

Layout used by the lift (offsets straight from the instruction operands):

```cpp
static_assert(offsetof(sub_c2ae6c0_rcx, f268) == 0x268, "begin slot");
static_assert(offsetof(sub_c2ae6c0_rcx, f278) == 0x278, "second slot");
static_assert(offsetof(sub_c2ae6c0_rcx, f288) == 0x288, "count slot");
static_assert(offsetof(sub_c2ae6c0_rcx, f290) == 0x290, "element array begin");
static_assert(offsetof(sub_c2ae6c0_rcx, f298) == 0x298, "element array end");
static_assert(offsetof(sub_c2ae6c0_rdi, f8) == 0x8, "strong count");
static_assert(offsetof(sub_c2ae6c0_rdi, fc) == 0xc, "weak count");
static_assert(offsetof(sub_c2ae6c0_rbx, f8) == 0x8, "element control block");
static_assert(offsetof(sub_c2ae6c0_rax, f8) == 0x8, "vtable slot 1");
```
