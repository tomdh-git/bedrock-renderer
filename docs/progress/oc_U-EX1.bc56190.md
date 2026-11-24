## NEXT
DONE

Unit: U-EX1.bc56190 — lift sub_0xbc56190 (size 0x477, [0xbc56190, 0xbc56607), depth 2, D0, bgfx region). LIFTCHECK OK 0xbc56190; CLOSES? YES.

## FILES
- src/client/features/render/native/bgfx/sub_bc56190.cpp (rewritten; first line `// LIFT 0xbc56190 size 0x477 1.26.62.01 sub_bc56190`)
- src/client/features/render/native/bgfx/sub_bc56190.h (rewritten; layout constants + static_asserts, signature, forward decl of sub_e935700, kFailSlotAddr)
- docs/functions/bc56190.md (kept analysis; replaced 'Reversed source (complete)' with full cited source; updated callees table)
- docs/progress/oc_U-EX1.bc56190.md (this file)

## LIFTCHECK
LIFTCHECK OK 0xbc56190

## UNRESOLVED CALL
none

## Summary of resolutions (all from the disassembly, no guesses)
- 0xE935700 is classified `lift` in docs/data/native_boundary.tsv (line 505) and present in docs/data/native_functions.tsv (line 1616, size 0x5, `jmp 0x392960` forwarder) -> forward-declared `extern "C" void sub_e935700(uintptr_t, uintptr_t)` in sub_bc56190.h and called directly as native::sub_e935700 at the 0xbc56577 site; not a blocker.
- 0xF9A8C78 is in neither table -> data-slot indirect call per the hard rule: function pointer read from slot 0xF9A8C78 at call time, 5 zero args, `__debugbreak()` (int3) after; not a blocker.
- 0x3BAFDC0 boundary (stl) -> `native::Boundary<void,void*,void*,void*,void*>{"sub_3bafdc0"}(&out->f_e8, flagptr, qptr2, a3)`.
- The inherited dossier phase C had errors vs the disassembly, all corrected in the lift: fcd = d1*inv1 (not 0), fb8 = d0*inv1*a[1] - e0*inv1*a[0] (uses a[1], not b[2]), fb0/fb4 include both cross terms, T2 = NUM/LEN1 = inv1, T3 = NUM/LEN3, f58 = t3*C, f68 = A*t3, f78 = B*t3, f80 = bitxor(d1*inv1, mask0), f60/f70 = bitxor(v1/t2, mask0), f88/f8c = bitxor(..., mask0) with full register-traced operand order. Every instruction of [0xbc56190, 0xbc56607) is inside a cited `// 0xA..0xB` range; every call is quoted verbatim; verify_oc mismatch=0, no-such-instr=0.

CLOSES? YES
