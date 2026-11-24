## NEXT
DONE

## FILES
- src/client/features/render/native/d3d12/sub_e82326d_c06.h
- src/client/features/render/native/d3d12/sub_e82326d_c06.cpp

## LIFTCHECK
Chunk 0xe82c101..0xe82d4be (part 7/8 of sub_e82326d) lifted as static inline step function `sub_e82326d_chunk_c06` with state struct `ChunkState_e82326d_c06`. All instruction ranges in the chunk are cited in the source with `// 0xSTART..0xEND` comments. Every `call` instruction in the range is quoted verbatim in the `#if 0` block at the end of the .cpp file (37 calls total). The chunk state struct captures 8 callee-saved registers (rbx, rsi, rdi, r12, r13, r14, r15, rbp) with layout static_asserts. Forward declarations provided for all direct callees in the lift set; vendor boundary calls via data slot 0xF99FFA0 (sub_eea6040) routed through `eea6040_call` thunk. Coverage: 100% of instructions in [0xe82c101, 0xe82d4be) accounted for in cited ranges.

## UNRESOLVED CALL
none

## CLOSES? YES