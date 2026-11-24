## NEXT
DONE — lift complete; liftcheck printed LIFTCHECK OK 0xeec5ae0; CLOSES? YES.

## UNIT
U-EX7.eec5ae0 — lift sub_eec5ae0 at 0xeec5ae0, size 0x6, depth 0, milestone 7, region root, status D0, 0 callees in set. Checklist line: X7.eec5ae0 LIFT sub_eec5ae0 (0xeec5ae0, 0x6 bytes, depth 0, D0, 0 callees in set).

## STATUS
Step 1 done (result file created with ## NEXT + step 2). Next: disassemble 0xeec5ae0 (done — see below), resolve the data slot, write the dossier + lifted .cpp/.h in src/client/features/render/native/helpers/, run liftcheck, close with CLOSES? YES/NO.

## DISASSEMBLY (rdis dis 0xeec5ae0 800) — verbatim
Function header line: `sub_eec5ae0  [0xeec5ae0..0xeec7ae0)  size 0x2000  39 xrefs in`
- `eec5ae0  jmp qword ptr [0xF9A7318]                     ; [data_f9a7318]`
- `eec5ae6  int3`
(Function size per data file: 0x6 bytes, i.e. exactly the single `jmp` instruction at 0xeec5ae0..0xeec5ae6. The int3 at eec5ae6 is padding after the function end.)

## KEY FACT
0xeec5ae0 is a 6-byte tail-forwarder: a single `jmp qword ptr [0xF9A7318]` (indirect jump through data slot 0xF9A7318). No calls, no callees in the lift set, no reads/writes of structs. Per the OPENCODE_BRIEF indirect-call rule: a `jmp`/`call [0xRVA]` through a data slot is not a blocker — forward-declare the target as a function pointer, read the pointer from the slot at call time, forward the same arguments, document the slot RVA.

## OPEN QUESTIONS
- Signature/ABI of the slot target at 0xF9A7318: unknown; need to read the qword at slot 0xF9A7318 (rdis rw/imm or similar) to learn the target RVA and its signature, else declare via the slot as function pointer with the same args forwarded.
- Whether 0xF9A7318 points into a lift-set function, boundary, or unresolved target.

## NEXT
DONE — lift complete; liftcheck printed LIFTCHECK OK 0xeec5ae0; CLOSES? YES below.

## DONE
- docs/progress/oc_U-EX7.eec5ae0.md created (## NEXT + step 2) [step 1]
- 0xeec5ae0 disassembled: single instruction `0xeec5ae0  jmp qword ptr [0xF9A7318]  ; [data_f9a7318]`, size 0x6 (eec5ae6 = int3 padding), 39 xrefs in [V: rdis dis 0xeec5ae0 800]
- Data slot resolved: `0F9A7318  MSVCP140.dll !?_Xinvalid_argument@std@@YAXPEBD@Z` = std::_Xinvalid_argument(const char*) [V: python tools/sigs/peimports.py on Minecraft.Windows.exe]
- Caller contract verified: 39 sites, all `lea rcx,[<string>]; call 0xEEC5AE0`, return unused [V: rdis xr 0xeec5ae0; e.g. 0x275314 lea rcx,["invalid stoi argument"]; 0x27531b call 0xEEC5AE0]
- docs/functions/eec5ae0.md written (dossier; 'Reversed source (complete)' section, no stub tags)
- src/client/features/render/native/helpers/sub_eec5ae0.h written (layout static_asserts, std::_Xinvalid_argument declaration, native::sub_eec5ae0 signature)
- src/client/features/render/native/helpers/sub_eec5ae0.cpp written (first line `// LIFT 0xeec5ae0 size 0x6 1.26.62.01 sub_eec5ae0`, verbatim quote block, cited body, LIFT_FN(eec5ae0,...) registry entry)
- No callees in lift set; no boundary wrapper needed — data-slot tail jump per indirect-call rule; the slot target is a CRT import called directly

## FILES
- docs/progress/oc_U-EX7.eec5ae0.md (result file, this file)
- docs/functions/eec5ae0.md (dossier, new)
- src/client/features/render/native/helpers/sub_eec5ae0.h (new: layout constants + static_asserts, signature, target declaration)
- src/client/features/render/native/helpers/sub_eec5ae0.cpp (new: lifted body + LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xeec5ae0

## UNRESOLVED CALL
none — the only control transfer is the tail jump `0xeec5ae0  jmp qword ptr [0xF9A7318]` through data slot 0xF9A7318; the slot holds MSVCP140!std::_Xinvalid_argument(const char*) [V: peimports.py] and the lift calls it directly; there are no `call` instructions in the function and no callees in the lift set.

CLOSES? YES
