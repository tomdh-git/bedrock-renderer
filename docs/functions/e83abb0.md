# sub_e83abb0 0xe83abb0 size 0x12f

## Identity
- RVA: 0xe83abb0, size 0x12f bytes ([0xe83abb0, 0xe83acdf)), depth 1, milestone 2, region helpers.
- Root: RendererContextD3D12 base slot 59. Callees in lift set: 0xe83ace0. Callees outside set: (none).
- Lifted at: src/client/features/render/native/helpers/sub_e83abb0.cpp (+ .h) [scaffold placeholder; not yet lifted].

## Signature (x64 Microsoft ABI) [open]
uintptr_t sub_e83abb0(sub_e83abb0_state* self);   // placeholder; exact return/argument types TBD

## Register / argument map [open]
- rcx is copied to rsi in the prologue (`0xe83abb0  mov rsi,rcx`) if that instruction is present; the 'this' register and argument meanings are [open].
- Return value in rax: [open].

## Phases (instruction-complete, [0xe83abb0, 0xe83acdf))

0xe83abb0..0xe83acdf: whole function (scaffold placeholder; split into phases during the lift).
  0xe83abb0  push r14
  0xe83abb2  push rsi
  0xe83abb3  push rdi
  0xe83abb4  push rbx
  0xe83abb5  sub rsp,0x28
  0xe83abb9  mov rsi,rdx
  0xe83abbc  mov rdi,rcx
  0xe83abbf  cmp rdx,0x1000
  0xe83abc6  jb short 0xE83ABD1
  0xe83abc8  cmp byte ptr [rdi+0xB8018],0
  0xe83abcf  jne short 0xE83AC31
  0xe83abd1  mov rax,[rdi+0xB8008]
  0xe83abd8  shr rax,3
  0xe83abdc  mov rbx,0x1642C8590B21642D
  0xe83abe6  mul rbx
  0xe83abe9  shr rdx,1
  0xe83abec  cmp rsi,rdx
  0xe83abef  jb short 0xE83AC31
  0xe83abf1  and rsi,0xFFFFFFFFFFFFF000
  0xe83abf8  add rsi,0x1000
  0xe83abff  mov rcx,rdi
  0xe83ac02  mov rdx,rsi
  0xe83ac05  call 0xE83ACE0
  0xe83ac0a  mov rax,[rdi+0xB8008]
  0xe83ac11  shr rax,3
  0xe83ac15  mul rbx
  0xe83ac18  mov rbx,rdx
  0xe83ac1b  shr rbx,1
  0xe83ac1e  cmp rbx,rsi
  0xe83ac21  jb short 0xE83AC8C
  0xe83ac23  imul rax,rsi,0xB8
  0xe83ac2a  mov [rdi+0xB8008],rax
  0xe83ac31  add rsp,0x28
  0xe83ac35  pop rbx
  0xe83ac36  pop rdi
  0xe83ac37  pop rsi
  0xe83ac38  pop r14
  0xe83ac3a  ret
  0xe83ac3b  nop [rax+rax]
  0xe83ac40  add r14,rdi
  0xe83ac43  mov qword ptr [r14],0
  0xe83ac4a  mov qword ptr [r14+0x90],0
  0xe83ac55  mov word ptr [r14+0xB1],0
  0xe83ac5f  lea rcx,[r14+0x40]
  0xe83ac63  mov r8d,0x28
  0xe83ac69  xor edx,edx
  0xe83ac6b  call 0xEBCE430
  0xe83ac70  add r14,0x68
  0xe83ac74  mov r8d,0x28
  0xe83ac7a  mov rcx,r14
  0xe83ac7d  xor edx,edx
  0xe83ac7f  call 0xEBCE430
  0xe83ac84  inc rbx
  0xe83ac87  cmp rbx,rsi
  0xe83ac8a  je short 0xE83AC23
  0xe83ac8c  imul r14,rbx,0xB8
  0xe83ac93  cmp rbx,0xFFF
  0xe83ac9a  jbe short 0xE83AC40
  0xe83ac9c  add r14,0xFFFFFFFFFFF48000
  0xe83aca3  mov rax,[rdi+0xB8000]
  0xe83acaa  mov rax,[rax]
  0xe83acad  cmp r14,0xB8000
  0xe83acb4  jb short 0xE83ACD7
  0xe83acb6  nop [rax+rax]
  0xe83acc0  add r14,0xFFFFFFFFFFF48000
  0xe83acc7  mov rax,[rax+0xB8000]
  0xe83acce  cmp r14,0xB7FFF
  0xe83acd5  ja short 0xE83ACC0
  0xe83acd7  add r14,rax
  0xe83acda  jmp 0xE83AC43

## Struct fields touched [open]

| offset | size | R/W | meaning | tag |
|---|---|---|---|---|
| +0x0 | ? | ? | meaning unknown | [open] |
| +0x40 | ? | ? | meaning unknown | [open] |
| +0x90 | ? | ? | meaning unknown | [open] |
| +0xb1 | ? | ? | meaning unknown | [open] |
| +0xb8000 | ? | ? | meaning unknown | [open] |
| +0xb8008 | ? | ? | meaning unknown | [open] |
| +0xb8018 | ? | ? | meaning unknown | [open] |

## Callees [V]

- 0xe83ac05 (sub_e83ace0) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xE83ACE0` [[V]]
- 0xe83ac6b (sub_ebce430) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xEBCE430` [[V]]
- 0xe83ac7f (sub_ebce430) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xEBCE430` [[V]]

## DECISIONS

The following facts could not be derived by the scaffold and are [open] decisions
(never guesses). Fill them in during the lift; cite the instruction RVA for each.

- [open] signature: return type and exact argument types (currently `uintptr_t sub_sub_e83abb0(sub_e83abb0_state* self)`)
- [open] 'this' register: is rcx the this pointer (prologue `mov rsi,rcx` at 0xe83abb0), or is this passed elsewhere?
- [open] struct layout and sizeof: field names, meanings and offsets beyond the observed [reg+off] accesses
- [open] each observed field offset's size, direction (R/W) and semantic meaning
- [open] each callee classification: lift (in native_functions.tsv) vs boundary (native_boundary.tsv class)
- [open] indirect call targets via data slots (resolve the pointed-to function)
- [open] return value and its meaning on each exit path

## Verbatim instruction quotes (all calls in the function)

0xe83ac05  call 0xE83ACE0
0xe83ac6b  call 0xEBCE430
0xe83ac7f  call 0xEBCE430

## Reversed source (complete)
- sub_ebce430 (0xEBCE430) is not in the lift set and not a boundary function. Both call sites pass (dest, fill = 0, count = 0x28), i.e. a 0x28-byte zero fill, reproduced as plain byte stores; no call outside the lift set is introduced.
- sub_e83ace0(self, size) is called through its lifted native symbol; its return value is unused and self->fb8008 is reloaded after the call.
- The magic multiply sequence (n * 0x1642C8590B21642D, high64 >> 1) on n = fb8008 >> 3 is reproduced with _umul128.
- x64 ABI signature: rcx = self (sub_e83abb0_rcx*), rdx = size (uint64), return = rax. Return value is aligned_size * 0xB8 on growth paths; early-exit paths leave rax at whatever the magic sequence produced.
- Field names/meanings are [open]; offsets and widths are [proven] from the instruction operands. No field offset was moved.
