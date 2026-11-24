## NEXT
step 2

## FILES
- docs/functions/bcb3cf0.md (extended)
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.cpp
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.h

## LIFTCHECK
Chunk 0xbcb54d0..0xbcb5e09 covers instructions:
- 0xbcb54d0..0xbcb54fe: vector swap loop 1 (rax/rdx/r13)
- 0xbcb5500..0xbcb553a: vector swap loop 2 (r15/rax/rcx/r13)
- 0xbcb553c..0xbcb556b: call sub_130ee0, setup, call sub_5693a80
- 0xbcb5571..0xbcb560a: string buffer setup, SSO check, call sub_9d6d0 or memcpy (sub_eec6de0)
- 0xbcb560a..0xbcb566c: cleanup, call sub_e935700 (vector destructor)
- 0xbcb5671..0xbcb56ad: another string buffer cleanup, indirect call via [0xF99FFA0] (sub_eea6040)
- 0xbcb56b8..0xbcb56f8: string buffer cleanup, call sub_e935700
- 0xbcb56fd..0xbcb575a: string buffer cleanup, call sub_e935700
- 0xbcb575f..0xbcb579f: string buffer cleanup, call sub_e935700
- 0xbcb57a4..0xbcb580c: string buffer cleanup, indirect call via [0xF99FFA0]
- 0xbcb5817..0xbcb5848: indirect call via [0xF99FFA0], call sub_9bc830
- 0xbcb5848..0xbcb5871: store to r15+rsi, compare r13 with rcx/rax
- 0xbcb58c7..0xbcb590e: vector swap loop 3 (rax/rdx/r13)
- 0xbcb5910..0xbcb594a: vector swap loop 4 (r15/rax/rcx/r13)
- 0xbcb594c..0xbcb597b: call sub_130ee0, setup, call sub_568c420
- 0xbcb5981..0xbcb59f8: string buffer setup, SSO check, call sub_9d6d0 or memcpy
- 0xbcb59fa..0xbcb5a1a: cleanup, call sub_e935700
- 0xbcb5a1a..0xbcb5a7c: string buffer cleanup, call sub_e935700
- 0xbcb5a81..0xbcb5abd: string buffer cleanup, indirect call via [0xF99FFA0]
- 0xbcb5ac8..0xbcb5b08: string buffer cleanup, call sub_e935700
- 0xbcb5b0d..0xbcb5b6a: string buffer cleanup, call sub_e935700
- 0xbcb5b6f..0xbcb5baf: string buffer cleanup, call sub_e935700
- 0xbcb5bb4..0xbcb5c12: string buffer cleanup, indirect call via [0xF99FFA0]
- 0xbcb5c23..0xbcb5c63: string buffer cleanup, call sub_e935700
- 0xbcb5c68..0xbcb5cc5: string buffer cleanup, call sub_e935700
- 0xbcb5cca..0xbcb5d0a: string buffer cleanup, call sub_e935700
- 0xbcb5d0f..0xbcb5d29: epilogue (restore xmm6, rsp, pop regs, ret)
- 0xbcb5d2a..0xbcb5e09: cold paths (error handlers with calls to sub_78ed0, sub_9bc830, data slot [0xF9A8C78], sub_75720, sub_75740)

Every call in range quoted verbatim:
  0xbcb5548  call 0x130EE0
  0xbcb556b  call 0x5693A80
  0xbcb558d  call 0x5693A80
  0xbcb55e2  call 0x9D6D0
  0xbcb5601  call 0xEEC6DE0
  0xbcb566c  call 0xE935700
  0xbcb56a7  call qword ptr [0xF99FFA0]
  0xbcb56f8  call 0xE935700
  0xbcb575a  call 0xE935700
  0xbcb579f  call 0xE935700
  0xbcb5806  call qword ptr [0xF99FFA0]
  0xbcb582d  call qword ptr [0xF99FFA0]
  0xbcb583f  call 0x9BC830
  0xbcb5958  call 0x130EE0
  0xbcb597b  call 0x568C420
  0xbcb599d  call 0x5693A80
  0xbcb59f2  call 0x9D6D0
  0xbcb5a01  call 0xEEC6DE0
  0xbcb5a7c  call 0xE935700
  0xbcb5ab7  call qword ptr [0xF99FFA0]
  0xbcb5b08  call 0xE935700
  0xbcb5b6a  call 0xE935700
  0xbcb5baf  call 0xE935700
  0xbcb5c12  call qword ptr [0xF99FFA0]
  0xbcb5c63  call 0xE935700
  0xbcb5cc5  call 0xE935700
  0xbcb5d0a  call 0xE935700
  0xbcb5d2a  call 0x78ED0
  0xbcb5ddd  call qword ptr [0xF9A8C78]
  0xbcb5de4  call 0x75720
  0xbcb5dea  call 0x75720
  0xbcb5df0  call 0x75740
  0xbcb5df6  call 0x75740
  0xbcb5dfc  call 0x75740
  0xbcb5e02  call 0x75740

Calls classification:
- sub_130ee0 (0x130EE0): lift (in callees_in_set)
- sub_5693a80 (0x5693A80): lift (in callees_in_set)
- sub_9d6d0 (0x9D6D0): stl (boundary, native_boundary.tsv)
- sub_eec6de0 (0xEEC6DE0): UNRESOLVED (not in lift set or boundary)
- sub_e935700 (0xE935700): lift (auto-unresolved->lift per native_boundary.tsv line 505)
- sub_eea6040 via [0xF99FFA0]: vendor thunk (boundary, native_boundary.tsv line 506)
- sub_568c420 (0x568C420): lift (in callees_in_set)
- sub_9bc830 (0x9BC830): alloc (boundary, native_boundary.tsv line 149)
- sub_78ed0 (0x78ED0): crt (boundary, native_boundary.tsv line 11)
- sub_75720 (0x75720): stl (boundary, native_boundary.tsv line 3)
- sub_75740 (0x75740): stl (boundary, native_boundary.tsv line 4)
- data slot [0xF9A8C78]: UNRESOLVED (not in boundary.tsv)

## UNRESOLVED CALL
0xEEC6DE0 at 0xbcb5601 and 0xbcb5a01 (direct call, not in lift set or boundary.tsv)
0xF9A8C78 at 0xbcb5ddd (indirect call via data slot, not in boundary.tsv)

CLOSES? NO UNRESOLVED CALL: 0xEEC6DE0 (direct) and 0xF9A8C78 (data slot) are neither in lift set nor boundary.tsv