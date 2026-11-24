## NEXT
step 2

## DONE
Chunk c01 (0xe8248aa..0xe82609e) of sub_e8230c8 lifted as `sub_e8230c8_chunk_c01` in `src/client/features/render/native/d3d12/sub_e8230c8_c01.cpp` (chunk state struct `ChunkState_e8230c8_c01` in the same file). Every instruction in the range is translated into C++ (>= ~1 source line per 20 bytes of range); every `call` is quoted verbatim inside `#if 0 ... #endif`; marker `// CHUNK 0xe8248aa..0xe82609e` present. No UNRESOLVED CALL: all call targets are in the CALLEES list (lift-classified: sub_ebce390, sub_e82dcc0, sub_e82d960, sub_ebd1560, sub_e820500, sub_e935700, sub_e835b50, sub_eec6ed0, sub_e82de90) or the vendor thunk slot `0xF99FFA0` (loader-resolved to sub_eea6040, class vendor), or the `call r10` indirect (r10 = scratch pointer carried in chunk state). All other instructions (non-call) are cited with `// 0xA..0xB` ranges.

## FILES
- src/client/features/render/native/d3d12/sub_e8230c8_c01.cpp (created, full chunk body + verbatim call quotes)
- src/client/features/render/native/d3d12/sub_e8230c8_c01.h (unchanged; no layout constants asserted for this chunk — no struct offsets are read/written outside the chunk-state struct)

## LIFTCHECK
$ python tools/sigs/liftcheck.py --range 0xe8230c8 0xe8248aa 0xe82609e
LIFTCHECK OK 0xe8230c8 0xe8248aa..0xe82609e

## UNRESOLVED CALL
none

CLOSES? YES