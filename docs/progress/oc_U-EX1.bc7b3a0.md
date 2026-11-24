## NEXT
DONE

## FILES
- docs/progress/oc_U-EX1.bc7b3a0.md (this result file; initialized with `## NEXT` / `step 2` per GOAL step 1, now finalized)
- docs/functions/bc7b3a0.md (rewritten: analysis kept, `Reversed source (complete)` section replaced with per-phase cited lift, callee table corrected — 0xEEC75A0/0xEEC73F0 are class lift, 0x78ed0 is boundary crt; all 7 calls quoted verbatim; no [?]/[I]/TODO/UNVERIFIED)
- src/client/features/render/native/bgfx/sub_bc7b3a0.h (rewritten: TableRow layout + static_asserts, data RVA constants, callee forward declarations sub_eec75a0/sub_eec73f0, signature, footprint declaration)
- src/client/features/render/native/bgfx/sub_bc7b3a0.cpp (rewritten: full lift, first line `// LIFT 0xbc7b3a0 size 0x425 1.26.62.01 sub_bc7b3a0`, per-block `// 0xA..0xB` citations covering [0xbc7b3a0, 0xbc7b7c5), verbatim call quotes, LIFT_FN registry entry, footprint)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc7b3a0` printed:
LIFTCHECK OK 0xbc7b3a0

## UNRESOLVED CALL
none — 0xEEC75A0 and 0xEEC73F0 are class lift in docs/data/native_boundary.tsv (lines 514/513) and docs/data/native_functions.tsv (lines 1638/1637, size 6 each), called as native::sub_eec75a0 / native::sub_eec73f0 forward-declared in the header (hard rule 66); 0x78ed0 is class crt in native_boundary.tsv line 11, entered from the trap block via the slot read at 0xF9A8CF0 (hard rule 69); no call target is outside both tables.

## Behavior lifted [V] (disassembly `rdis dis 0xbc7b3a0 800`, function range [0xbc7b3a0, 0xbc7b7c5))
- rcx = out float* (rsi), rdx = in const float* (rdi), rax = out; reads in[0,4,8,0xC,0x10,0x18]; writes out[0..8) (movlps 0xbc7b753) and out[8..0xC) (movss 0xbc7b756); footprint [out, out+0xC).
- Three channels share constants [0xEFD32AC], [0xEFC6CF8], [0xEEE6700] (rnd: trunc(x) if x>=0 else trunc(x-K)), tables at 0xF449730/0xF44A0A8/0xF44A564 (row {f0@0, pad@4 reused as float, f8@8}), plus [0xEFC2540], [0xF0C8C88], [0xF1527C8], [0xEF40D44], [0xF10D440], [0xEEC8060], [0xEFD3410], [0xF246F60], [0xF0A9660], [0xF449700].
- Call order: 0xEEC75A0, 0xEEC73F0, 0xEEC75A0, 0xEEC73F0, 0xEEC75A0, 0xEEC73F0; any index >= 0x65 enters the trap block 0xbc7b7bf `call 0x78ED0` / 0xbc7b7c4 `int3`.
- Six idx >= 0x65 branches all target the trap block; original's epilogue restores xmm6-xmm15/rbx/rdi/rsi, `add rsp,0x110`, `ret` at 0xbc7b7be.

CLOSES? YES
