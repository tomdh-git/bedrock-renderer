## NEXT
DONE — liftcheck OK, verify_oc 0 mismatches, no unresolved calls, GATE OK 0x56CC4F0.

Disassembly of [0x56cc4f0, 0x56cc5df) (size 0xef) captured from rdis dis 0x56cc4f0 0xef:
- 0x56cc4f0 push r14 / 0x56cc4f2 push rsi / 0x56cc4f3 push rdi / 0x56cc4f4 push rbx / 0x56cc4f5 sub rsp,0x28
- 0x56cc4f9 mov rsi,rcx / 0x56cc4fc mov rcx,[rcx+0x18] / 0x56cc500 test rcx,rcx / 0x56cc503 je short 0x56CC548
- 0x56cc505 mov rdx,[rsi+0x28] / 0x56cc509 sub rdx,rcx / 0x56cc50c cmp rdx,0x1000 / 0x56cc513 jb short 0x56CC531
- 0x56cc515 mov rax,[rcx-8] / 0x56cc519 add rcx,0xFFFFFFFFFFFFFFF8 / 0x56cc51d sub rcx,rax / 0x56cc520 cmp rcx,0x20 / 0x56cc524 jae 0x56CC5C5
- 0x56cc52a add rdx,0x27 / 0x56cc52e mov rcx,rax / 0x56cc531 lea rdi,[rsi+0x18] / 0x56cc535 call 0xE935700
- 0x56cc53a xorps xmm0,xmm0 / 0x56cc53d movups [rdi],xmm0 / 0x56cc540 mov qword ptr [rdi+0x10],0
- 0x56cc548 mov rax,[rsi+8] / 0x56cc54c mov rcx,[rax+8] / 0x56cc550 mov qword ptr [rcx],0 / 0x56cc557 mov r14,[rax]
- 0x56cc55a jmp short 0x56CC56D / 0x56cc55c nop [rax]
- 0x56cc560 mov edx,0x28 / 0x56cc565 mov rcx,rdi / 0x56cc568 call 0xE935700
- 0x56cc56d test r14,r14 / 0x56cc570 je short 0x56CC5AE / 0x56cc572 mov rdi,r14 / 0x56cc575 mov r14,[r14]
- 0x56cc578 mov rbx,[rdi+0x18] / 0x56cc57c test rbx,rbx / 0x56cc57f je short 0x56CC560
- 0x56cc581 lock dec dword ptr [rbx+8] / 0x56cc585 jne short 0x56CC560
- 0x56cc587 mov rax,[rbx] / 0x56cc58a mov rax,[rax] / 0x56cc58d mov rcx,rbx / 0x56cc590 call qword ptr [0xF99FFA0]
- 0x56cc596 lock dec dword ptr [rbx+0xC] / 0x56cc59a jne short 0x56CC560
- 0x56cc59c mov rax,[rbx] / 0x56cc59f mov rax,[rax+8] / 0x56cc5a3 mov rcx,rbx / 0x56cc5a6 call qword ptr [0xF99FFA0]
- 0x56cc5ac jmp short 0x56CC560 / 0x56cc5ae mov rcx,[rsi+8] / 0x56cc5b2 mov edx,0x28 / 0x56cc5b7 add rsp,0x28
- 0x56cc5bb pop rbx / 0x56cc5bc pop rdi / 0x56cc5bd pop rsi / 0x56cc5be pop r14 / 0x56cc5c0 jmp 0xE935700
- 0x56cc5c5 mov qword ptr [rsp+0x20],0 / 0x56cc5ce xor ecx,ecx / 0x56cc5d0 xor edx,edx / 0x56cc5d2 xor r8d,r8d / 0x56cc5d5 xor r9d,r9d / 0x56cc5d8 call qword ptr [0xF9A8C78] / 0x56cc5de int3

Callees: sub_e935700 (0xe935700, lift set, forward-declared `namespace native { void* sub_e935700(void*); }`, called directly x2 plus tail call x1); sub_eea6040 via data slot 0xF99FFA0 (vendor destructor thunk, `native::Boundary<std::uintptr_t,void*,void*>`, called x2 with vfptr[0] and vfptr[1]); _invoke_watson via data slot 0xF9A8C78 (noreturn, read slot at call time via RewriteRegistry::imageBase()+kRvaFailSlot, then int3). edx=0x28 settings before sub_e935700 calls are dead (sub_392960 overwrites rdx).

Object layout (offsetof static_asserts in sub_56cc4f0.h + layout block in .cpp):
- RefObj: +0x00 vfptr, +0x08 uint32 f8 (lock-dec refcount), +0x0c uint32 fc (lock-dec refcount), size 0x10.
- Node: +0x00 void* f0 (next node), +0x18 RefObj* f18, size 0x20.
- ListHead: +0x00 void* f0 (first node), +0x08 void** f8 (slot nulled), size 0x10.
- State: +0x08 ListHead* f8, +0x18 void* f18 (heap buffer), +0x28 uint64 f28 (buffer end), size 0x30.

Returns void*: sub_e935700(freeArg) on the buffer-release path, sub_e935700(node) per loop iteration, sub_e935700(head) as the tail return. Noreturn watson+int3 path when delta>=0x20. No return value on the small-buffer path differs — freeArg=buffer then sub_e935700.

## FILES
- docs/progress/oc_U-EX5.56cc4f0.md (this file)
- src/client/features/render/native/helpers/sub_56cc4f0.h
- src/client/features/render/native/helpers/sub_56cc4f0.cpp
- docs/functions/56cc4f0.md

## LIFTCHECK
LIFTCHECK OK 0x56cc4f0
GATE OK 0x56CC4F0

## UNRESOLVED CALL
none

## TOOL REQUESTS
none

CLOSES? YES
