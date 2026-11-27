## NEXT DONE

# UNIT U-EX7.ed35e10 — LIFT sub_ed35e10 (0xed35e10, 0x49 bytes) — CLOSED

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base. Static analysis only (rdis dis; PE/string data read via rdis). Tags: [V] = seen in disassembly/exe data (cite RVA/offset), [I] = inferred (cite basis).

## Result

Lifted sub_ed35e10: straight-line function [0xed35e10, 0xed35e59), size 0x49. Allocates a 0x88-byte frame, stores the stack cookie (global [0x1230A0C0] ^ rsp) at [rsp+0x70], calls GetCurrentProcess() through import data slot 0xF9A6FD8 (rule 68: pointer read from the slot at call time, no arguments), calls lift callee native::sub_eec5880(hProcess, &buffer, 0x48) — the 6-byte import-thunk `0xeec5880  jmp qword ptr [0xF9A7918]` -> K32GetProcessMemoryInfo — reads buffer+0x10 into RAX, runs the crt boundary sub_e951550 (/GS cookie check: argument vs global [0x1230A0C0], ret on match, jmp sub_e98e3c0 termination on mismatch) via native::Boundary, then returns RAX. No branches, no game-memory writes outside the stack frame, no argument registers read, fail fast exactly as the original.

The earlier session's blocker (UNRESOLVED CALL 0xeec5880) is resolved: 0xeec5880 is class `lift` in docs/data/native_functions.tsv (line 1641, size 0x6) and docs/data/native_boundary.tsv (line 526 `0xeec5880 lift auto-unresolved->lift`), so it is forward-declared in my header and called through its native symbol per brief rule 66; no wrapper invented. Slot contents verified [V] via `rdis str`: `f9a92d6  "GetCurrentProcess"` (slot 0xF9A6FD8 -> import-by-name RVA 0xF9A92D4) and `f9ac052  "K32GetProcessMemoryInfo"` (slot 0xF9A7918 -> import-by-name RVA 0xF9AC050). Cookie check re-verified [V] via rdis dis of 0xe951550 (`cmp rcx,[0x1230A0C0]; jne ...; ret` / `jmp 0xE98E3C0`).

## FILES

- docs/progress/oc_U-EX7.ed35e10.md (this file, rewritten)
- src/client/features/render/native/helpers/sub_ed35e10.h (new): layout constants sub_ed35e10Layout with static_asserts (frame 0x88, buffer at rsp+0x20 size 0x48, result at buffer+0x10, cookie slot at rsp+0x70, RVAs 0x1230A0C0 and 0xF9A6FD8), forward declaration `native::sub_eec5880(void*, void*, std::uint32_t)` (lift callee, rule 66), boundary `native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550")` (crt boundary), signature `std::uintptr_t sub_ed35e10(void)`.
- src/client/features/render/native/helpers/sub_ed35e10.cpp (new): first line `// LIFT 0xed35e10 size 0x49 1.26.62.01 sub_ed35e10`, full instruction-by-instruction reversal with `// 0xA..0xB` range citations beside every block, verbatim `0xRVA  call ...` quotes for all three calls, a verbatim `#if 0` instruction listing of the whole range, LIFT_FN registry entry `LIFT_FN(sub_ed35e10, "sub_ed35e10", 0xED35E10, sub_ed35e10, nullptr);`.
- docs/functions/ed35e10.md (new): mechanical facts, signature, complete 'Reversed source (complete)' section, struct fields touched, callee classification table, ownership/threading, version-stable anchors, verification; free of [?]/[I]/TODO/UNVERIFIED in the reversed-source block and the source file.

## LIFTCHECK

```
LIFTCHECK OK 0xed35e10
```

Command: `python tools/sigs/liftcheck.py 0xed35e10` (exit code 0). dossier exists with a clean 'Reversed source' section; source first line is the LIFT marker with size 0x49; no stub/TODO/[?]/[I]/UNVERIFIED; LIFT_FN registry entry present; static_assert present; every instruction of [0xed35e10, 0xed35e59) inside cited ranges or quoted verbatim; all three calls quoted verbatim; verify_oc mismatch=0, no-such-instr=0.

Note: `python tools/cppsyntax.py sub_ed35e10.cpp` reports one pre-existing environmental error, in the shared framework header src/client/features/render/native/Lift.h line 65 (`sizeof(void)` in the Boundary<void> static_assert), triggered by any void-return boundary — the same error occurs on existing units such as sub_7e6d0.cpp; no error originates from my files. No build was run and the game was not started.

## UNRESOLVED CALL

none — every call resolved: GetCurrentProcess via data-slot 0xF9A6FD8 (rule 68), sub_eec5880 via native symbol (rule 66), sub_e951550 via native::Boundary crt wrapper.

## TOOL REQUESTS

None — all evidence from rdis dis/str on the exe, liftcheck, verify_oc, cppsyntax; no helper scripts written.

CLOSES? YES
