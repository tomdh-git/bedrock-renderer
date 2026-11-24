## NEXT
DONE - sub_bc82ad0 fully lifted (chunks c00-c03)

## FILES
- src/client/features/render/native/bgfx/sub_bc82ad0_chunk_c02.h
- src/client/features/render/native/bgfx/sub_bc82ad0_chunk_c02.cpp
- src/client/features/render/native/bgfx/sub_bc82ad0_chunk_c03.h
- src/client/features/render/native/bgfx/sub_bc82ad0_chunk_c03.cpp

## LIFTCHECK
Range 0xbc85abd..0xbc864bb (c02): 7 FNV-1a iterations, each: hash null-terminated string from rsi, store to data_12ae19d0..data_12ae1a00, call sub_73150([rbp+0x4A0]), call sub_e938d70(data), jmp to sub_bc82db0/sub_bc82dd5/sub_bc82dfa/sub_bc82e1f/sub_bc82e44/sub_bc831c4/sub_bc831e9.
Range 0xbc864bb..0xbc864df (c03): mov [data_12ae1ac0],rdx; call sub_73150([rbp+0x770]); call sub_e938d70(data_12ae1ac8); jmp sub_bc83aee.
All instructions cited; forward declarations for 14 jump targets in c02.h.

## UNRESOLVED CALL
none

CLOSES? YES