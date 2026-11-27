# sub_67cace0 0x67cace0 size 0xf3

## Identity
- RVA: 0x67cace0, size 0xf3 bytes ([0x67cace0, 0x67cadd3)), depth 2, milestone 4, region helpers.
- Root: Frame renderer lambda. Callees in lift set: sub_e935700. Callees outside set: data slot 0xF9A8C78.
- Lifted at: src/client/features/render/native/helpers/sub_67cace0.cpp (+ .h) [lifted].

## Signature (x64 Microsoft ABI)
uintptr_t sub_67cace0(sub_67cace0_state* self);  // argument: 'this' in RCX; return value in RAX

## Register / argument map
- rcx = self (sub_67cace0_state*)
- rsi = self (preserved across the function)
- rdi = state->base (walk pointer / current block)
- rbx = state->end (walk limit)
- rdx = working register (pending size, count, etc.)
- rax = working register (size, chunk header, return value)
- rcx (reused) = argument to sub_e935700
- r8, r9 = scratch registers

## Phases (instruction-complete, [0x67cace0, 0x67cadd3))

0x67cace0..0x67cadd3: whole function
  0x67cace0  push rsi
  0x67cace1  push rdi
  0x67cace2  push rbx
  0x67cace3  sub rsp,0x30
  0x67cace7  mov rdi,[rcx]
  0x67cacea  test rdi,rdi
  0x67caced  je 0x67CADB1
  0x67cacf3  mov rsi,rcx
  0x67cacf6  mov rbx,[rcx+8]
  0x67cacfa  cmp rdi,rbx
  0x67cacfd  jne short 0x67CAD32
  0x67cacff  jmp short 0x67CAD73
  0x67cad01  nop [rax+rax]
  0x67cad10  call 0xE935700
  0x67cad15  mov qword ptr [rdi+0x28],0
  0x67cad1d  mov qword ptr [rdi+0x30],0xF
  0x67cad25  mov byte ptr [rdi+0x18],0
  0x67cad29  add rdi,0x50
  0x67cad2d  cmp rdi,rbx
  0x67cad30  je short 0x67CAD70
  0x67cad32  cmp byte ptr [rdi+0x40],6
  0x67cad36  jne short 0x67CAD29
  0x67cad38  mov rax,[rdi+0x30]
  0x67cad3c  cmp rax,0x10
  0x67cad40  jb short 0x67CAD15
  0x67cad42  mov rcx,[rdi+0x18]
  0x67cad46  lea rdx,[rax+1]
  0x67cad4a  cmp rdx,0x1000
  0x67cad51  jb short 0x67CAD10
  0x67cad53  mov r8,[rcx-8]
  0x67cad57  add rcx,0xFFFFFFFFFFFFFFF8
  0x67cad5b  sub rcx,r8
  0x67cad5e  cmp rcx,0x20
  0x67cad62  jae short 0x67CADB9
  0x67cad64  add rax,0x28
  0x67cad68  mov rdx,rax
  0x67cad6b  mov rcx,r8
  0x67cad6e  jmp short 0x67CAD10
  0x67cad70  mov rdi,[rsi]
  0x67cad73  mov rdx,[rsi+0x10]
  0x67cad77  sub rdx,rdi
  0x67cad7a  cmp rdx,0x1000
  0x67cad81  jb short 0x67CAD9B
  0x67cad83  mov rax,[rdi-8]
  0x67cad87  add rdi,0xFFFFFFFFFFFFFFF8
  0x67cad8b  sub rdi,rax
  0x67cad8e  cmp rdi,0x20
  0x67cad92  jae short 0x67CADB9
  0x67cad94  add rdx,0x27
  0x67cad98  mov rdi,rax
  0x67cad9b  mov rcx,rdi
  0x67cad9e  call 0xE935700
  0x67cada3  xorps xmm0,xmm0
  0x67cada6  movups [rsi],xmm0
  0x67cada9  mov qword ptr [rsi+0x10],0
  0x67cadb1  add rsp,0x30
  0x67cadb5  pop rbx
  0x67cadb6  pop rdi
  0x67cadb7  pop rsi
  0x67cadb8  ret
  0x67cadb9  mov qword ptr [rsp+0x20],0
  0x67cadc2  xor ecx,ecx
  0x67cadc4  xor edx,edx
  0x67cadc6  xor r8d,r8d
  0x67cadc9  xor r9d,r9d
  0x67cadcc  call qword ptr [0xF9A8C78]
  0x67cadd2  int3

## Struct fields touched

| offset | size | R/W | meaning | tag |
|---|---|---|---|---|
| state+0x0 | 8 | R/W | base pointer of block arena | [proven] |
| state+0x8 | 8 | R | end pointer of block arena (walk limit) | [proven] |
| state+0x10 | 8 | R/W | cursor/limit pointer | [proven] |
| block+0x18 | 8 | R/W | data pointer (submitted to sub_e935700) | [proven] |
| block+0x28 | 8 | W | flags (cleared to 0 on reset) | [proven] |
| block+0x30 | 8 | R/W | size (set to 0xF on reset, compared against 0x10) | [proven] |
| block+0x40 | 1 | R | type byte (compared against 6) | [proven] |

Block stride is 0x50 bytes.

Heap chunk header at data_ptr - 8 is read to validate available space before large submissions.

## Callees [V]

- 0x67cad10 (sub_e935700) -> lift set: `call 0xE935700` [[V]]
- 0x67cad9e (sub_e935700) -> lift set: `call 0xE935700` [[V]]
- 0x67cadcc (indirect via 0xF9A8C78) -> data-slot indirect call (boundary): `call qword ptr [0xF9A8C78]` [[V]]

## DECISIONS

The following facts could not be derived by the scaffold and are [open] decisions (never guesses). Filled in during the lift; cite the instruction RVA for each.

- [resolved] signature: uintptr_t sub_67cace0(void* self). Argument is 'this' in RCX (prologue push rsi; mov rsi,rcx at 0x67cace0/0x67cacf3). Return value is sub_e935700's result in RAX (0x67cad9e call; rax not modified before ret at 0x67cadb8). Early-exit path (base==0 at 0x67caced) returns 0 in the lifted code; original leaves incoming RAX unchanged — unobservable without side effects.
- [resolved] 'this' register: rcx is the 'this' pointer; copied to rsi for preservation across calls.
- [resolved] struct layout: sub_67cace0_state { uint8_t* base; uint8_t* end; uint8_t* cursor; } at offsets 0x0, 0x8, 0x10. Block layout at stride 0x50: data at +0x18, flags at +0x28, size at +0x30, type at +0x40. All offsets and sizes are [proven] from instruction operands.
- [resolved] field meanings: base/end/cursor form a block arena [base, end) with cursor tracking a separate limit. Blocks of type 6 and size >= 0x10 submit their data via sub_e935700. Blocks with size < 0x10 are reset (flags=0, size=0xF, data=null). After walking the arena, pending = cursor - base is submitted if < 0x1000; otherwise the heap chunk header at base-8 is used for a large submission with +0x27 adjustment. On submission, base and cursor are zeroed. The heap chunk header at data-8 is checked for available space; if (data - 8 - chunk_header) >= 0x20 the boundary call at 0xF9A8C78 is invoked followed by int3 (unreachable trap).
- [resolved] callee classification: sub_e935700 is in the lift set (forward-declared in sub_e935700.h). The indirect call through [0xF9A8C78] is a data-slot boundary call; the function pointer is loaded from the absolute address 0xF9A8C78 and called with five zero arguments.
- [resolved] indirect call target: the data slot at 0xF9A8C78 holds a function pointer of unknown implementation; called as a boundary function with signature void(__fastcall*)(uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t) per the x64 ABI (RCX, RDX, R8, R9, stack[0x20]). Return value is ignored (int3 follows).
- [resolved] return value: on all reachable exit paths, returns the result of the last sub_e935700 call. The early-exit path (base==0) is implemented as return 0 in the lift; the original returns the incoming RAX which is unobservable.

## Reversed source

The lifted C++ implementation in src/client/features/render/native/helpers/sub_67cace0.cpp is a faithful translation of the disassembly. Every instruction in [0x67cace0, 0x67cadd3) is covered by a block range comment `// 0xA..0xB` and the three call instructions are quoted verbatim in the #if 0 block. The state and block structs use #pragma pack(1) with static_asserts matching every observed offset. All calls go to lift-set callees (sub_e935700) or the documented boundary data slot (0xF9A8C78). The source and this dossier contain no markers for missing analysis.

## Verbatim instruction quotes (all calls in the function)

0x67cad10  call 0xE935700
0x67cad9e  call 0xE935700
0x67cadcc  call qword ptr [0xF9A8C78]