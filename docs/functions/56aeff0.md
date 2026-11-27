# sub_56aeff0 0x56aeff0 size 0xff

## Identity
- RVA: 0x56aeff0, size 0xff bytes ([0x56aeff0, 0x56af0ef)), depth 1, milestone 5, region helpers.
- Root: VV frame-graph builder. Callees in lift set: 0x56aea80. Callees outside set: (none).
- Lifted at: src/client/features/render/native/helpers/sub_56aeff0.cpp (+ .h) [scaffold placeholder; not yet lifted].

## Signature (x64 Microsoft ABI) [open]
uintptr_t sub_56aeff0(sub_56aeff0_state* self);   // placeholder; exact return/argument types TBD

## Register / argument map [open]
- rcx is copied to rsi in the prologue (`0x56aeff0  mov rsi,rcx`) if that instruction is present; the 'this' register and argument meanings are [open].
- Return value in rax: [open].

## Phases (instruction-complete, [0x56aeff0, 0x56af0ef))

0x56aeff0..0x56af0ef: whole function (scaffold placeholder; split into phases during the lift).
  0x56aeff0  push rsi
  0x56aeff1  push rdi
  0x56aeff2  push rbx
  0x56aeff3  sub rsp,0x30
  0x56aeff7  mov rsi,rcx
  0x56aeffa  mov rax,[rcx+0x20]
  0x56aeffe  test rax,rax
  0x56af001  je short 0x56AF051
  0x56af003  lea rdi,[rsp+0x2F]
  0x56af008  nop [rax+rax]
  0x56af010  mov rcx,[rsi+0x18]
  0x56af014  add rax,rcx
  0x56af017  dec rax
  0x56af01a  mov rcx,[rsi+8]
  0x56af01e  mov rdx,[rsi+0x10]
  0x56af022  dec rdx
  0x56af025  and rdx,rax
  0x56af028  mov r8,[rcx+rdx*8]
  0x56af02c  movsx rcx,byte ptr [r8+0x58]
  0x56af031  inc rcx
  0x56af034  mov rdx,rdi
  0x56af037  call 0x56AEA80
  0x56af03c  mov rax,[rsi+0x20]
  0x56af040  dec rax
  0x56af043  mov [rsi+0x20],rax
  0x56af047  jne short 0x56AF010
  0x56af049  mov qword ptr [rsi+0x18],0
  0x56af051  mov rcx,[rsi+8]
  0x56af055  test rcx,rcx
  0x56af058  je short 0x56AF0CD
  0x56af05a  lea rbx,[rsi+8]
  0x56af05e  mov rdi,[rsi+0x10]
  0x56af062  test rdi,rdi
  0x56af065  jle short 0x56AF09A
  0x56af067  inc rdi
  0x56af06a  jmp short 0x56AF079
  0x56af06c  nop [rax]
  0x56af070  dec rdi
  0x56af073  cmp rdi,1
  0x56af077  jbe short 0x56AF092
  0x56af079  mov rax,[rbx]
  0x56af07c  mov rcx,[rax+rdi*8-0x10]
  0x56af081  test rcx,rcx
  0x56af084  je short 0x56AF070
  0x56af086  mov edx,0x60
  0x56af08b  call 0xE935700
  0x56af090  jmp short 0x56AF070
  0x56af092  mov rcx,[rsi+8]
  0x56af096  mov rdi,[rsi+0x10]
  0x56af09a  shl rdi,3
  0x56af09e  cmp rdi,0x1000
  0x56af0a5  jb short 0x56AF0BF
  0x56af0a7  mov rax,[rcx-8]
  0x56af0ab  add rcx,0xFFFFFFFFFFFFFFF8
  0x56af0af  sub rcx,rax
  0x56af0b2  cmp rcx,0x20
  0x56af0b6  jae short 0x56AF0D5
  0x56af0b8  add rdi,0x27
  0x56af0bc  mov rcx,rax
  0x56af0bf  mov rdx,rdi
  0x56af0c2  call 0xE935700
  0x56af0c7  xorps xmm0,xmm0
  0x56af0ca  movups [rbx],xmm0
  0x56af0cd  add rsp,0x30
  0x56af0d1  pop rbx
  0x56af0d2  pop rdi
  0x56af0d3  pop rsi
  0x56af0d4  ret
  0x56af0d5  mov qword ptr [rsp+0x20],0
  0x56af0de  xor ecx,ecx
  0x56af0e0  xor edx,edx
  0x56af0e2  xor r8d,r8d
  0x56af0e5  xor r9d,r9d
  0x56af0e8  call qword ptr [0xF9A8C78]
  0x56af0ee  int3

## Struct fields touched [open]

| offset | size | R/W | meaning | tag |
|---|---|---|---|---|
| +0x-8 | ? | ? | meaning unknown | [open] |
| +0x0 | ? | ? | meaning unknown | [open] |
| +0x8 | ? | ? | meaning unknown | [open] |
| +0x10 | ? | ? | meaning unknown | [open] |
| +0x18 | ? | ? | meaning unknown | [open] |
| +0x20 | ? | ? | meaning unknown | [open] |
| +0x2f | ? | ? | meaning unknown | [open] |
| +0x58 | ? | ? | meaning unknown | [open] |

## Callees [V]

- 0x56af037 (sub_56aea80) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0x56AEA80` [[V]]
- 0x56af08b (sub_e935700) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xE935700` [[V]]
- 0x56af0c2 (sub_e935700) -> lift set (if in native_functions.tsv, else boundary TBD): `call 0xE935700` [[V]]
- 0x56af0e8 (indirect via 0xF9A8C78) -> data-slot indirect call (boundary TBD): `call qword ptr [0xF9A8C78]` [[V]]

## DECISIONS

The following facts could not be derived by the scaffold and are [open] decisions
(never guesses). Fill them in during the lift; cite the instruction RVA for each.

- [open] signature: return type and exact argument types (currently `uintptr_t sub_sub_56aeff0(sub_56aeff0_state* self)`)
- [open] 'this' register: is rcx the this pointer (prologue `mov rsi,rcx` at 0x56aeff0), or is this passed elsewhere?
- [open] struct layout and sizeof: field names, meanings and offsets beyond the observed [reg+off] accesses
- [open] each observed field offset's size, direction (R/W) and semantic meaning
- [open] each callee classification: lift (in native_functions.tsv) vs boundary (native_boundary.tsv class)
- [open] indirect call targets via data slots (resolve the pointed-to function)
- [open] return value and its meaning on each exit path

## Verbatim instruction quotes (all calls in the function)

0x56af037  call 0x56AEA80
0x56af08b  call 0xE935700
0x56af0c2  call 0xE935700
0x56af0e8  call qword ptr [0xF9A8C78]

## Reversed source (complete)

- Table object (`rcx` = `self`): `+0x08` element-pointer array, `+0x10` capacity,
  `+0x18` hash bias, `+0x20` live count. Element records are 0x60-byte allocations
  whose signed byte at `+0x58` selects a `sub_56aea80` branch.
- Live teardown loop (`0x56af010`): index = `(count + bias - 1) & (capacity - 1)`,
  then `sub_56aea80(dispatch_state + 1, &rsp_byte, element)`; the call is repeated
  until the decremented count stored at `+0x20` is zero, then the bias is cleared.
- Dead-element sweep (`0x56af079`): from index `capacity - 1` down to 0, every
  non-null element pointer is released with `sub_e935700(element)`.
- Array release (`0x56af0bf`): for a byte size >= 0x1000 the size-prefixed header at
  `elements - 8` is validated (`(elements - 8) - header < 0x20`), otherwise the
  loader's invalid-parameter handler at data slot `0xF9A8C78` is invoked with five
  zero arguments; then `sub_e935700(base)` is called and the `elements`/`capacity`
  pair is zeroed with one 16-byte store.
- `sub_56aea80` is called with the call-site register assignment
  `rcx = selector, rdx = &local byte, r8 = element`, so its declaration carries
  three parameters; its own lifted unit reads the element from r8.
- The function writes no return value (rax at `0x56af0d4` is the last call's
  leftover), so the signature is `void sub_56aeff0(void* self)`.
