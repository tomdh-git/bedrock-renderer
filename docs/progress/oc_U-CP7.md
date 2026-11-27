## NEXT DONE

## DONE
- Created tools/ctx/difftest.py (CP7): emulator diff test for lifted functions
- Runs original function bytes from Minecraft.Windows.exe (1.26.62.01) in unicorn emulator
- Finds and compiles lifted C++ via MSVC clean cmd.exe (same pattern as cppsyntax.py), with Lift.h include and LIFT_FN line stripped
- Compares return value (rax) on N random inputs between emulated original and compiled lift
- SKIPs functions with external calls, unmapped memory, or compilation failures
- Prints: DIFFTEST TESTED <rva> N=<count> OK or first diverging input / SKIPPED with reason
- Selftest on 3 pure small lifted functions: 0xbc76610 OK (N=10), 0xbc771f0 SKIPPED (goto-crossing-init compile error), 0xbcc24f0 SKIPPED (missing header)
- Verified: DIFFTEST TESTED 0xbc76610 N=10 OK

## BLOCKING
- Only 1 of 3 pure small lifted functions compiles (0xbc76610). 0xbc771f0 has goto-crossing-initialization C2362 error. 0xbcc24f0 has missing sub_bcc24f0.h header. These are pre-existing issues in the lifted sources, not difftest bugs.