## NEXT
step 2: write lifted source + dossier, run cppsyntax + liftcheck, fix failures, close.

DONE so far:
- Read contract (RENDER_NATIVE_SPEC.md), OPENCODE_BRIEF.md hard rules, input data (_d_U-EX5.5699be0.txt: 0x5699be0 size 0x95, 0 callees in set, pass encode B).
- Disassembled sub_5699be0 body [0x5699be0, 0x5699c75), 0x95 bytes, 35 instructions (rdis dis 0x5699be0 80).
- Classifications: 0xeea6040 = vendor boundary ("thunk via data slot 0xF99FFA0", body `jmp rax`); 0xbc61560 = lift bgfx D2; 0x5699e30 = lift pass body B D2. Sibling template: passes/sub_568b9e0.cpp/.h (encode A, offsets 0x2E0/2E8/2F0 vs ours 0xA8/0xB0/0xB8).
- Created docs/functions/5699be0.md (dossier with 'Reversed source (complete)' section).
- Created src/client/features/render/native/passes/sub_5699be0.h (offset constants, structs, static_asserts, forward declarations of sub_5699e30 and bgfx::sub_bc61560).
- Created src/client/features/render/native/passes/sub_5699be0.cpp (first line // LIFT 0x5699be0 size 0x95 1.26.62.01 sub_5699be0; full per-instruction reversal with // 0xA..0xB citations; boundary gate calls via native::Boundary sub_eea6040("sub_eea6040"); tail call bgfx::sub_bc61560; LIFT_FN; #if 0 verbatim block of all 35 instructions).
- Next: cppsyntax.py on the .cpp, then liftcheck.py 0x5699be0, fix every failure, paste final output under ## LIFTCHECK.

## FILES
- docs/functions/5699be0.md (created)
- src/client/features/render/native/passes/sub_5699be0.h (created)
- src/client/features/render/native/passes/sub_5699be0.cpp (created)

## NEXT
step 2 continued: run cppsyntax.py + liftcheck.py 0x5699be0.
