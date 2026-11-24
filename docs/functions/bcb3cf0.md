# sub_bcb3cf0

- RVA: 0xbcb3cf0, size 0x2119 (per data file), name: VV frame-graph builder
- Frame: push rbp,r15,r14,r13,r12,rsi,rdi,rbx; sub rsp,0x988; lea rbp,[rsp+0x80]; movaps [rbp+0x8F0],xmm6; qword [rbp+0x8E8]=0xFFFFFFFFFFFFFFFE.
- Args (x64 ABI): rcx=a0, rdx=a1 (rbx), r8=a2 (rsi), r9=a3 (saved [rbp+0x8E0]); stack args [rbp+0x970]=a4 (r13), [rbp+0x978]=a5 (r15).
- Saved/locals: rbp frame; local slots rbp-0x50 (16 bytes from a1), rbp+0x40, rbp+0x7D0/7D8, rbp+0x7E0/7E8, rbp+0x7F0.., rbp+0x800/808/810/818, rbp+0x838/840, rbp+0x8B0, rbp+0x8E0/8E8/8F0 (xmm6). r12 from [r15+8]; r13 from [a4+8].
- Jump tables: none identified in this plan pass (TBD by chunk units).
- Chunk boundaries: see docs/data/native_chunks/bcb3cf0.tsv.

## Chunk state (for chunk lifting)

Per docs/data/native_chunks/bcb3cf0.tsv, chunk 2 is range 0xbcb54d0..0xbcb5e09.

Live state at chunk entry (0xbcb54d0):
- rbp = rsp+0x80 (frame base, established in prologue)
- rbx = a1 (arg 1, preserved)
- rsi = a2 (arg 2, preserved)
- r12, r13, r14, r15 (preserved regs)
- xmm6 saved at [rbp+0x8F0]
- Stack frame: 0x988 bytes below rbp+0x80 (i.e., rsp at entry to chunk)
- Local slots accessible via rbp: rbp-0x50, rbp+0x40, rbp+0x7D0/7D8, rbp+0x7E0/7E8, rbp+0x7F0.., rbp+0x800/808/810/818, rbp+0x838/840, rbp+0x8B0, rbp+0x8E0/8E8/8F0 (xmm6)
- r12 from [r15+8]; r13 from [a4+8]

ChunkState_bcb3cf0_c2 struct models this state (stack as byte array, register aliases).

## Reversed source (complete)

### Chunk 2: 0xbcb54d0..0xbcb5e09

First instruction: 0xbcb54d0  movups [rax+rdx],xmm0
Last instruction: 0xbcb5e08  int3 (padding after ret at 0xbcb5d29)

This chunk implements:
1. Two vector swap loops (16-byte element swaps between two vectors)
2. A call to sub_130ee0 followed by sub_5693a80 setup
3. Multiple std::string buffer operations (SSO checks, copies, destructors)
4. Multiple string cleanup sequences with sub_e935700 (vector/string destructor)
5. Indirect calls via data slot 0xF99FFA0 (sub_eea6040, vendor thunk)
6. Two more vector swap loops
7. A call to sub_130ee0, sub_568c420, sub_5693a80
8. More string operations and cleanup
9. Function epilogue (restore xmm6, rsp, pop regs, ret)
10. Cold paths with calls to sub_78ed0, sub_9bc830, [0xF9A8C78], sub_75720, sub_75740

Calls in this chunk (all quoted verbatim):
- 0xbcb5548  call 0x130EE0 (lift, in callees_in_set)
- 0xbcb556b  call 0x5693A80 (lift, in callees_in_set)
- 0xbcb558d  call 0x5693A80 (lift, in callees_in_set)
- 0xbcb55e2  call 0x9D6D0 (stl, boundary)
- 0xbcb5601  call 0xEEC6DE0 (UNRESOLVED, not in lift set or boundary)
- 0xbcb566c  call 0xE935700 (lift, auto-unresolved->lift per native_boundary.tsv line 505)
- 0xbcb56a7  call qword ptr [0xF99FFA0] (vendor thunk sub_eea6040, boundary line 506)
- 0xbcb56f8  call 0xE935700 (lift)
- 0xbcb575a  call 0xE935700 (lift)
- 0xbcb579f  call 0xE935700 (lift)
- 0xbcb5806  call qword ptr [0xF99FFA0] (vendor thunk, boundary)
- 0xbcb582d  call qword ptr [0xF99FFA0] (vendor thunk, boundary)
- 0xbcb583f  call 0x9BC830 (alloc, boundary)
- 0xbcb5958  call 0x130EE0 (lift)
- 0xbcb597b  call 0x568C420 (lift, in callees_in_set)
- 0xbcb599d  call 0x5693A80 (lift)
- 0xbcb59f2  call 0x9D6D0 (stl, boundary)
- 0xbcb5a01  call 0xEEC6DE0 (UNRESOLVED, not in lift set or boundary)
- 0xbcb5a7c  call 0xE935700 (lift)
- 0xbcb5ab7  call qword ptr [0xF99FFA0] (vendor thunk, boundary)
- 0xbcb5b08  call 0xE935700 (lift)
- 0xbcb5b6a  call 0xE935700 (lift)
- 0xbcb5baf  call 0xE935700 (lift)
- 0xbcb5c12  call qword ptr [0xF99FFA0] (vendor thunk, boundary)
- 0xbcb5c63  call 0xE935700 (lift)
- 0xbcb5cc5  call 0xE935700 (lift)
- 0xbcb5d0a  call 0xE935700 (lift)
- 0xbcb5d2a  call 0x78ED0 (crt, boundary)
- 0xbcb5ddd  call qword ptr [0xF9A8C78] (UNRESOLVED, not in boundary.tsv)
- 0xbcb5de4  call 0x75720 (stl, boundary)
- 0xbcb5dea  call 0x75720 (stl, boundary)
- 0xbcb5df0  call 0x75740 (stl, boundary)
- 0xbcb5df6  call 0x75740 (stl, boundary)
- 0xbcb5dfc  call 0x75740 (stl, boundary)
- 0xbcb5e02  call 0x75740 (stl, boundary)

Source files:
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.h (chunk state, layout constants, static_asserts, ABI signature)
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.cpp (implementation with LIFT marker)