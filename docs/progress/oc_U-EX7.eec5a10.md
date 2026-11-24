## NEXT
DONE

## UNIT
U-EX7.eec5a10 | function 0xeec5a10 | size 0x6 bytes | depth 0 | milestone D0 | region root | name sub_eec5a10 | callees in set: 0

## SUMMARY
Lifted sub_eec5a10: a single-instruction import thunk, `0xeec5a10  jmp qword ptr [0xF9A75B8]` (size 0x6, ends at 0xeec5a16; int3 padding after). Slot 0xF9A75B8 (.rdata) holds the imported address of MSVCP140!_Mtx_unlock (`void _Mtx_unlock(struct _Mtx*)`) per the IAT table in docs/progress/oc_U-EX0b1.md (peimports.py). Lifted body tail-calls `::_Mtx_unlock(mtx)` with rcx = mtx, matching call-site evidence (`0xe81d7d4  mov rcx,[rbp-8]` / `0xe81d7d8  call 0xEEC5A10`, return value discarded). Follows the accepted twin pattern sub_eec59f0/_Mtx_lock (docs/functions/eec59e0.md, sub_eec59f0.cpp/.h). No call instruction in the function; no struct fields touched; no prologue/frame.

## FILES
docs/progress/oc_U-EX7.eec5a10.md (this unit's result file)
docs/functions/eec5a10.md (new dossier, with Reversed source (complete))
src/client/features/render/native/helpers/sub_eec5a10.h (new: layout constants + static_asserts, signature, _Mtx_unlock forward declaration)
src/client/features/render/native/helpers/sub_eec5a10.cpp (new: LIFT marker first line, lifted body, verbatim #if 0 quote, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xeec5a10

## UNRESOLVED CALL
none

## VERIFICATION
- rdis dis 0xeec5a10: 1 instruction, jmp qword ptr [0xF9A75B8]; function size 0x6 per data file (0xeec5a10..0xeec5a16), int3 padding follows.
- Call sites checked: 0xe81d7d8 / 0xe81d82d `call 0xEEC5A10` with rcx = [rbp-8] (lock), return value discarded → void (struct _Mtx*).
- liftcheck: dossier exists, Reversed source section free of [?]/[I]/TODO/UNVERIFIED, LIFT marker size 0x6 matches native_functions.tsv, LIFT_FN entry present, static_assert present, coverage 1/1 instructions in cited range 0xeec5a10..0xeec5a16, no call instructions to quote, verify_oc mismatch=0 no-such-instr=0 on the verbatim quote `0xeec5a10  jmp qword ptr [0xF9A75B8]`.

CLOSES? YES
