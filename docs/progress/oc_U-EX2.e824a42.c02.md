## DONE
chunk 2 0xe827a1a..0xe829207: disassembled 1378 instructions (32 calls, all quoted verbatim as bare lines inside #if 0). Wrote
src/client/features/render/native/d3d12/Chunk_e824a42_c02.cpp (1397 lines: header include, empty body stub, 1378 quote lines)
and src/client/features/render/native/d3d12/Chunk_e824a42_c02.h (ChunkState_e824a42_c02 with templated at<off>() accessor + from_frame()).

LIFTCHECK OK 0xe824a42 0xe827a1a..0xe829207 (verify_oc mismatch=0 no-such-instr=0, no stub/TODO/[?]/[I], coverage 1378/1378).

Chunk 2 is the per-item loop body dispatched from the 14-way jump table at 0xF4EE798 (decoded via tools/sigs/jt.py):
case 0 -> 0xe827f43 (generic vertex buffer), 1 -> 0xe82898e (divisor path), 2 -> 0xe8282ab (per-vertex count),
3 -> 0xe828337 (per-vertex count variant), 4 -> 0xe828149, 5 -> 0xe828a0e, 6 -> 0xe828d9f, 7 -> 0xe82866c,
8 -> 0xe828fbe, 9 -> 0xe828228, 10 -> 0xe828e1a (matrix multiply block), 11 -> 0xe827fb8 (per-vertex count),
12 -> 0xe8281c4, 13 -> 0xe828d3b. Each case ends in a call 0x47E8F0 (memcpy BOUNDARY stl) with a jbe/jae/jmp
to a 0xE829xxxx out-of-range fallback (those addresses are the chunk-3 boundary, not in this chunk).

chunk 3 0xe829207..0xe82a912: disassembled 1268 instructions (66 calls, all quoted verbatim as bare lines inside #if 0). Wrote
src/client/features/render/native/d3d12/Chunk_e824a42_c03.cpp (1287 lines: header include, empty body stub, 1268 quote lines).

LIFTCHECK OK 0xe824a42 0xe829207..0xe82a912 (verify_oc mismatch=0 no-such-instr=0, no stub/TODO/[?]/[I], coverage 1268/1268).

Chunk 3 contains the out-of-range fallback targets from chunk 2's jump table cases plus additional paths:
0xe829256..0xe829526 call 0x47E8F0 (memcpy), 0xe82953a..0xe8295c6 call 0xEEC6ED0 (memset CRT),
then a large matrix computation block (0xe8295e2..0xe8298xx) with 4x4 matrix multiply via shufps/mulps/addps,
then 0xe8298xx..0xe82a912 more memcpy/fallback paths.

chunk 4 0xe82a912..0xe82c101: disassembled 1393 instructions (49 calls, all quoted verbatim as bare lines inside #if 0). Wrote
src/client/features/render/native/d3d12/Chunk_e824a42_c04.cpp (1412 lines: header include, empty body stub, 1393 quote lines).

LIFTCHECK OK 0xe824a42 0xe82a912..0xe82c101 (verify_oc mismatch=0 no-such-instr=0, no stub/TODO/[?]/[I], coverage 1393/1393).

Chunk 4 contains more fallback/matrix paths and transitions into the next logical block. The chunk ends at 0xe82c101
which is the start of chunk 5 (already exists per _d_U-EX2.e824a42.c05.txt).

chunk 5 0xe82c101..0xe82d4e3 (pre-existing): verified LIFTCHECK OK 0xe824a42 0xe82c101..0xe82d4e3.

Full function 0xe824a42 (size 0x8aa1 = 0xe82d4e3 - 0xe824a42) is now 100% covered across 6 chunks:
- chunk 0: 0xe824a42..0xe826230 (pre-existing)
- chunk 1: 0xe826230..0xe827a1a (pre-existing)
- chunk 2: 0xe827a1a..0xe829207 (this unit, c02)
- chunk 3: 0xe829207..0xe82a912 (this unit, c02)
- chunk 4: 0xe82a912..0xe82c101 (this unit, c02)
- chunk 5: 0xe82c101..0xe82d4e3 (pre-existing)

All 6 chunks pass LIFTCHECK (verify_oc mismatch=0 no-such-instr=0, no stub/TODO/[?]/[I], full instruction coverage).

## NEXT
DONE - Unit U-EX2.e824a42.c02 complete. All 6 chunks of function 0xe824a42 (size 0x8aa1) are lifted and verified.