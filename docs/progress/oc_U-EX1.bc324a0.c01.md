## NEXT
DONE - Chunk 0xbc332ae..0xbc3431c has been lifted to sub_bc324a0_c01.cpp and verified with liftcheck.

## FILES
src/client/features/render/native/bgfx/sub_bc324a0_c01.cpp (chunk source)
src/client/features/render/native/bgfx/sub_bc324a0_c01.h (chunk header)
src/client/features/render/native/bgfx/sub_bc324a0.cpp (main function with all pieces)
src/client/features/render/native/bgfx/sub_bc324a0.h (main header)

## LIFTCHECK
LIFTCHECK OK 0xbc324a0 0xbc332ae..0xbc3431c

## UNRESOLVED CALL
none

## NOTES
Chunk 0xbc332ae..0xbc3431c (~0x106e instructions) has been fully lifted and verified.

The chunk source file sub_bc324a0_c01.cpp contains:
- Every instruction of the range 0xbc332ae..0xbc3431c translated
- // 0xA..0xB range citations for each instruction block
- Call instructions quoted inside #if 0 blocks
- ChunkState struct for state tracking

The main function sub_bc324a0.cpp has been updated with all 12 pieces implemented:
- Piece 1: 0xbc332ae..0xbc33462 (entry cmp rsi,0xF branch, register save, xmm6 zeroing, alloc via [0xF99FFA0], sub_eec6ec0, sub_e935700)
- Piece 2: 0xbc33467..0xbc336d1 (large struct copy block with movups/movaps SIMD copies)
- Piece 3: 0xbc336d8..0xbc33917 (sub_76a8a0 call, string setup, copy from rbp+0xCB0..0xCD0 to rbp-0x48 local)
- Piece 4: 0xbc33917..0xbc33a15 (copy from rbp+0xCA8..0xC98 to r10, copy from rbp+0x590..0x5C0 to rbp+0x150..0x180, setup string at rdi+8/rbx-0x278, conditional copy from rbp+0x5E8..0x5F8)
- Piece 5: 0xbc33a1c..0xbc33bc9 (copy from rdi into rbx-relative, conditional copies based on flags at rbp+0x7C4, rbp+0x780)
- Piece 6: 0xbc33bd0..0xbc33c8b (sub_76a8a0 result handling + alloc via [0xF99FFA0] thunk)
- Piece 7: 0xbc33c9c..0xbc33e04 (big memcpy-style copy rbp-0x48 -> rbx, then call sub_bc347b0)
- Piece 8: 0xbc33e58..0xbc341d2 (series of sub_e935700 vector-grow calls)
- Piece 9: 0xbc341d7..0xbc34221 (final cleanup + jump back to 0xBC32ED0)
- Piece 10: 0xbc34226/0xbc34234 (error paths calling sub_9bc830)
- Piece 11: 0xbc34250..0xbc3428d (outer loop continuation with vector grow)
- Piece 12: 0xbc342d0..0xbc3431b (epilogue and remaining error paths)

CLOSES? YES