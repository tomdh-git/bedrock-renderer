## NEXT
DONE

## GOAL
Lift BgfxFrameBuilder::endFrame (0x675b450, size 0xc8, depth 2, framebuilder region, D0). Returns self (RAX=RSI=RCX entry). Callee 0xb0ad0 (stl boundary).

## SUMMARY
Lifted sub_675b450 (BgfxFrameBuilder::endFrame, size 0xc8, [0x675b450, 0x675b518)) faithfully: same reads, writes, calls in the same order, same return. Verified with liftcheck and gate.

The function appends one 0x58-byte element to the growable buffer at self+0x18 (cur)/self+0x20 (end), using self+0x10 as the vector object:
- cur != end: write the element (from 16-byte globals [0xF2BE848]/[0xF2BE838]) at cur, advance cur by 0x58.
- cur == end: call sub_b0ad0 (stl boundary) with &self+0x10, cur, &elem; it reallocates/copy-constructs/advances. elem.flag is 0 so the dead size-handling block is skipped.
Returns self.
Dead code replicated for faithfulness: [rbp+0x10] = -2 dead store, the unreachable size block ([rbp-0x18]/[rbp-0x30] garbage), and the noreturn watson path via call qword ptr [0xF9A8C78] (data slot read at call time, 5 zero args, int3).

## FILES
- docs/progress/oc_U-EX4.675b450.md (this result file)
- src/client/features/render/native/framebuilder/sub_675b450.h (layout constants + static_asserts + declarations + LIFT_FN registry)
- src/client/features/render/native/framebuilder/sub_675b450.cpp (lifted body, first line `// LIFT 0x675b450 size 0xc8 1.26.62.01 BgfxFrameBuilder::endFrame`)
- docs/functions/675b450.md (dossier with Reversed source (complete))

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x675b450` printed:
LIFTCHECK OK 0x675b450

## UNRESOLVED CALL
none. All three call targets are resolved:
- 0x675b4aa  call 0xB0AD0 -> sub_b0ad0 (stl boundary, native_boundary.tsv row 0xb0ad0), called through its native symbol.
- 0x675b4ec  call 0xE935700 -> sub_e935700 (lift, already lifted in helpers/sub_e935700.cpp), called through its native symbol.
- 0x675b511  call qword ptr [0xF9A8C78] -> indirect through data slot 0xF9A8C78 read at call time (hard rule 69), not a blocker; noreturn watson-like fail handler with five zero args.

## Gate
`python tools/ctx/gate.py 0x675b450` printed: GATE OK 0x675B450 (cppsyntax clean, liftcheck OK, layout static_assert present).

CLOSES? YES
