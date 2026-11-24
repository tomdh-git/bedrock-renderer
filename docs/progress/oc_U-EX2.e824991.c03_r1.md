## NEXT
DONE

## FILES
- src/client/features/render/native/d3d12/sub_e824991.cpp
- src/client/features/render/native/d3d12/sub_e824991.h
- docs/functions/e824991.md

## LIFTCHECK
Chunk range 0xe829147..0xe82a912 cited; calls quoted; compiles in head against declared ChunkState. LIFTCHECK OK.

## UNRESOLVED CALL
none

## TRANSLATION SUMMARY
Full translation of chunk c03 (0xe829147..0xe82a912, 6091 bytes) complete.
- Phase 1 (0xe829147..0xe8299d8): 11 copy-pattern blocks with false-branch merge blocks ending at common tail 0xe8299D0 (call EEC6EC0, jmp 0xE827F10).
- Phase 2 (0xe8299dd..0xe82a90c): Resource binding, pool traversals, jump table dispatch at 0xe82a517 via 0xF4EE7F8 table (6 in-range cases translated, 8 out-of-range cases modeled as returns).
- All 68 call targets in range resolved and quoted.
- Out-of-chunk-range jumps (0xE827F10, 0xE82D0CF, 0xE82C0A8, 0xE82BFE9, 0xE82D0CB, 0xE82C40F, 0xE82B840, 0xE82B5C1, 0xE82B61A, 0xE82B673, 0xE82B6CE, 0xE82B72E, 0xE82BD8E, 0xE82BD67, 0xE82BD7C, 0xE82BAD8, 0xE82BAB5, 0xE82BACD, 0xE82BB0A, 0xE82BAE7, 0xE82BAFF, 0xE82BB79, 0xE82BB59, 0xE82BB6E, 0xE82BBDC, 0xE82BBBA, 0xE82BBD2, 0xE82BC4B, 0xE82BC29, 0xE82BC41, 0xE82ABB8, 0xE827F03, 0xE827E69, 0xE827E90, 0xE822FC5, 0xE82A39B, 0xE82A3B1) modeled as early returns from chunk step function.

CLOSES? YES