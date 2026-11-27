## NEXT
DONE

## GOAL
LIFT TASK U-EX7.ebdb760: lift sub_ebdb760 (0xebdb760, size 0x19, depth 0, D0, 0 callees in set), Minecraft Bedrock 1.26.62.01.

## SUMMARY
Disassembled sub_ebdb760 (rdis dis 0xebdb760 0x19). It is a 6-instruction leaf wrapper:

  0xebdb760  sub rsp,0x28
  0xebdb764  lea rcx,[rsp+0x30]
  0xebdb769  call qword ptr [0xF9A7CA0]   ; [data_f9a7ca0]
  0xebdb76f  mov rax,[rsp+0x30]
  0xebdb774  add rsp,0x28
  0xebdb778  ret

No register arguments on entry (RCX is overwritten by the lea before it is read), 8-byte return in RAX. It calls the loader-resolved function in data slot 0xF9A7CA0 with RCX = &buf (a stack qword buffer the callee fills), then returns the qword the callee wrote; the callee's own return value is discarded. No struct fields touched; no memory written outside its own stack frame (pure). The callee target is read from `imageBase() + 0xF9A7CA0` at call time and invoked as `uint64_t (*)(uint64_t* out)` per the data-slot indirect-call rule (hard rule #68, same pattern as sub_ebdbf10 via slot 0xF9A7B10); it is not a boundary wrapper and not a lift-set callee, and is not an UNRESOLVED CALL blocker.

Boundary: docs/data/native_boundary.tsv classifies 0xebdb760 as `lift` (line 485). Depth 0, 0 callees in set. No [?]/[I]/TODO/UNVERIFIED anywhere. No null guards/SEH (the original has none).

## FILES
- docs/progress/oc_U-EX7.ebdb760.md (this unit's result file; created)
- src/client/features/render/native/helpers/sub_ebdb760.h (created: layout constants + static_asserts + signature + callee type)
- src/client/features/render/native/helpers/sub_ebdb760.cpp (created: `// LIFT 0xebdb760 size 0x19 1.26.62.01 sub_ebdb760` first line, body, verbatim call quote in #if 0, LIFT_FN registry entry)
- docs/functions/ebdb760.md (created: dossier with analysis and 'Reversed source (complete)' section)

No other files edited (Sigs.json, shared headers, CMake, hooks, and other units' files untouched; no build, no game).

## LIFTCHECK
LIFTCHECK OK 0xebdb760

## UNRESOLVED CALL
none (the only call, 0xebdb769 `call qword ptr [0xF9A7CA0]`, is a data-slot indirect call resolved from imageBase()+0xF9A7CA0 at call time per hard rule #68; target address documented by slot RVA, not a blocker)

## CLOSES
CLOSES? YES
