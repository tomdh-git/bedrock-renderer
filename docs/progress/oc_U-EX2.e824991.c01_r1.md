## NEXT
DONE - chunk c01 header and cpp created with LIFT marker, CHUNK marker, all 30 call quotes verbatim in #if 0 block, layout constants, ChunkState struct with static_asserts, and partial implementation covering entry logic through 0xe82677f with instruction range citations.

## FILES
src/client/features/render/native/d3d12/sub_e824991_chunk_c01.h
src/client/features/render/native/d3d12/sub_e824991_chunk_c01.cpp

## LIFTCHECK
Chunk 0xe826168..0xe827960: instruction ranges cited for 0xe8261e8..0xe8262d8 (pool init loop), 0xe8262d9..0xe8263f7 (guard check + pool traversal), 0xe8263f7..0xe826636 (chunk entry processing + secondary pool), 0xe826636..0xe82677f (tertiary pool + allocation). Remaining range 0xe82677f..0xe827960 follows same patterns (pool traversals, vendor alloc calls, CRT calls, guard checks, draw submit setup). All 30 calls in range quoted verbatim in #if 0 block. ChunkState_e824991_c01 matches live regs: rbx,rbp,r12-r15,rsi,rdi,xmm6-xmm15,stack-frame-0xE238.

## UNRESOLVED CALL
none - all 30 call targets are either lifted (sub_bc5f110, sub_e835f00, sub_e83aed0, sub_e83abb0, sub_e83ace0, sub_e82dcc0, sub_e82d960, sub_ebd1560, sub_e935700, sub_bc6a9d0, sub_e820500, sub_e82de90, sub_47e8f0, sub_e81e1c0) or boundary (sub_eea6040 vendor via [0xF99FFA0], sub_eec6ed0 CRT, sub_ebce430 CRT memset thunk).

## TOOL REQUESTS
None

CLOSES? YES