## NEXT
DONE. Unit X1.bc76610 closed: CLOSES? YES.

Unit: X1.bc76610 LIFT bx::HashMurmur2A::add(data, len) (0xbc76610, 0x1dc bytes, depth 1, D1, 0 callees in set)
Input data: docs/functions/bc76610.md (dossier), docs/progress/_d_U-EX1.bc76610.txt (function row: size 0x1dc, callees none)

SUMMARY:
- Lifted bx::HashMurmur2A::add(data, len) by hand from the disassembly of [0xbc76610, 0xbc767ec) (125 instructions, size 0x1dc, verified against the function row).
- rcx = this (HashMurmur2A state), rdx = data, r8 = len, r9 never read. State fields [V]: +0x00 m_hash, +0x04 m_tail, +0x08 m_nbytesInTail (0..3), +0x0C m_nbytes (+= len at 0xbc7661e).
- 0xbc76615  test dl,3 ; 0xbc76618  jne 0xBC767E2 tails to a cloned copy of the same body at 0xbc767f0 (separate function, size 0x1c2; in neither native_functions.tsv nor native_boundary.tsv). Both bodies are instruction-identical (same reads/writes/order, no calls), so the alignment test is behaviorally a no-op and the shared body covers both paths. The function contains no `call` (0 callees), so there is no callee to resolve and no UNRESOLVED CALL.
- MurmurHash2A mix with m = 0x5BD1E995: k *= m; k ^= k >> 24; k *= m; hash *= m; hash ^= k. No return value written (epilogue pop rbx/pop rsi/ret).
- Every instruction cited with `// 0xA..0xB` ranges and verbatim `0xRVA  instr` quotes; no [?]/[I]/TODO/UNVERIFIED/stub anywhere.

## FILES
- created src/client/features/render/native/bgfx/HashMurmur2A_add.h (layout constants + static_asserts + signature)
- created src/client/features/render/native/bgfx/HashMurmur2A_add.cpp (first line `// LIFT 0xbc76610 size 0x1dc 1.26.62.01 bx::HashMurmur2A::add(data, len)`, lifted body, LIFT_FN registry entry)
- changed docs/functions/bc76610.md (analyst sections filled, 'Reversed source (complete)' section added)
- changed docs/progress/oc_U-EX1.bc76610.md (this file)

## LIFTCHECK
LIFTCHECK OK 0xbc76610

## UNRESOLVED CALL
none

## TOOL REQUESTS
None (only rdis.exe dis and tools/sigs/liftcheck.py were used; no helper scripts written).

CLOSES? YES
