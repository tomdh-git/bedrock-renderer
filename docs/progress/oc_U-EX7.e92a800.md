## NEXT
DONE

## GOAL
Lift sub_e92a800 (0xe92a800, 0xbf bytes, depth 0, D0, 0 callees in set). Source: docs/progress/pack/e92a800.md listing. Callees: sub_eec59f0 (_Mtx_lock), sub_eec5a00 (_Throw_Cpp_error), sub_eec5a10 (_Mtx_unlock) are lift/set (already lifted, headers exist under src/client/features/render/native/helpers/). sub_e92a350 is NOT in native_functions.tsv and NOT in native_boundary.tsv (only boundary_candidates.tsv with class '?') => UNRESOLVED CALL blocker per GOAL rule; do not invent a wrapper.

## FILES
src/client/features/render/native/helpers/sub_e92a800.h — header with layout constants (a0+0x30 _Mtx_t, a0+0x7C state, a0+0x128 calleeArg, a0+0x178 arrayBase, a0+0x180 arrayEnd, elem+0xD8 flag) + static_asserts; includes sub_eec5a00.h only and <thread> for CRT _Mtx_t/_Thrd_result/_Mtx_lock/_Mtx_unlock; does NOT include sub_eec5a10.h or sub_eec59f0.h to avoid CRT linkage conflicts.
src/client/features/render/native/helpers/sub_e92a800.cpp — LIFT marker, full verbatim instruction listing in #if 0 block, lifted body calling ::_Mtx_lock / ::_Mtx_unlock directly (CRT signatures), sub_eec5a00 for errors, sub_e92a350 forward-declared as UNRESOLVED callee; LIFT_FN registry entry.
docs/functions/e92a800.md — dossier with Reversed source section.

## LIFTCHECK
LIFTCHECK OK 0xe92a800

## UNRESOLVED CALL
0xE92A350 sub_e92a350: called at 0xe92a87f `call 0xE92A350` with rcx=array element ([a0+0x178]+idx*8), rdx=arg2, r8=[a0+0x128]; return in eax (tested via al). Not in native_functions.tsv or native_boundary.tsv -> blocker.

## CLOSES?
NO — UNRESOLVED CALL to sub_e92a350 (not in native_functions.tsv or native_boundary.tsv; only in native_boundary_candidates.tsv with class '?'). Per GOAL rule, documented but no wrapper invented.
