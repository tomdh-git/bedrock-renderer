## NEXT
DONE

## UNIT
U-EX7.ebce5e0: function 0xebce5e0, size 0x8 bytes, depth 0, milestone 7, region root, status D0, 0 callees in set, 0 callees outside set.

## SUMMARY
Lifted sub_ebce5e0, a bounded C-string length (strnlen-like): rcx=str (const char*), rdx=maxlen (std::int32_t), returns eax=length (std::int32_t); null string -> return 0, otherwise count non-NUL bytes up to maxlen.
- Disassembly verbatim (rdis): [0xebce5e0, 0xebce601): test rcx,rcx / jne short 0xEBCE5E8 / xor eax,eax / ret / mov rax,rcx / test edx,edx / jle short 0xEBCE5FE / nop / cmp byte ptr [rax],0 / je short 0xEBCE5FE / inc rax / dec edx / test edx,edx / jg short 0xEBCE5F0 / sub eax,ecx / ret.
- No `call` instructions; all control flow is direct branches (jne/je/jg/jle). No callees, no unresolved calls, no struct fields touched (only a byte read at [rax]).
- Lifted body replicates the guard + bounded-length loop exactly, with all three exits reaching `0xebce5fe  sub eax,ecx` then `0xebce600  ret`.

## FILES
- docs/progress/oc_U-EX7.ebce5e0.md (this progress file)
- docs/functions/ebce5e0.md (dossier with analysis + 'Reversed source (complete)')
- src/client/features/render/native/helpers/sub_ebce5e0.cpp (first line: // LIFT 0xebce5e0 size 0x8 1.26.62.01 sub_ebce5e0; verbatim quotes in #if 0; lifted body; LIFT_FN registry entry)
- src/client/features/render/native/helpers/sub_ebce5e0.h (SubEbce5e0Layout static_asserts, extern "C" sub_ebce5e0 signature)

## C++ syntax check
`python tools/cppsyntax.py sub_ebce5e0.cpp`: 0 errors in sub_ebce5e0.cpp (the 112 reported errors are pre-existing framework-header include quirks in Detour.h/Profiler.h, identical to the already-accepted sub_ebce390.cpp).

## LIFTCHECK
LIFTCHECK OK 0xebce5e0

## UNRESOLVED CALL
none (the function has no `call` instructions)

## CLOSES?
CLOSES? YES
