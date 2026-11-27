## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_675b350.cpp (rewritten: full lift)
- src/client/features/render/native/helpers/sub_675b350.h (rewritten: typed state structs, static_asserts, signature)
- docs/functions/675b350.md (rewritten: Reversed source section, struct table, callees, decisions)

## LIFTCHECK
LIFTCHECK OK 0x675b350 (via python tools/sigs/liftcheck.py 0x675b350)
GATE OK 0x675B350 (via python tools/ctx/gate.py 0x675b350)

## UNRESOLVED CALL
none

## Notes
- Calls: 0x675b380 `call 0xE935700` (sub_e935700, lift set, native symbol `native::sub_e935700`); 0x675b41d `jmp 0xE935700` (tail call to sub_e935700); 0x675b444 `call qword ptr [0xF9A8C78]` (data-slot fail handler per rule 69, four zero args, noreturn with following int3). All resolved; none are UNRESOLVED CALL.
- Return type `void*`; block 14 returns sub_e935700's RAX, block 15 returns the probe value in RAX, block 0's null-self path returns rax (modeled as nullptr).
- xmm6 held as a local zero constant; its [rsp+0x30] save/restore is not observable across the tail call and is not modeled.
- No null guards or SEH beyond the original's explicit test/je checks.
- Field semantics reconstructed from instruction operands (best-effort); offsets/widths proven and asserted via offsetof static_asserts.
- D-rank not derivable from static data [open].

CLOSES? YES
