## NEXT
DONE — unit complete, LIFTCHECK OK 0x568cd70, CLOSES? YES.

## UNIT
U-EX5.568cd70: function 0x568cd70, size 0xc bytes, depth 0, milestone 5 (pass-tasks), region D0, name sub_568cd70, 0 callees in set. Checklist line: X5.568cd70 LIFT sub_568cd70 (0x568cd70, 0xc bytes, depth 0, D0, 0 callees in set). CLOSES? YES.

## Disassembly (verified [V] from rdis.exe, 1.26.62.01)
```
568cd70  mov rcx,rdx
568cd73  mov rdx,r8
568cd76  jmp 0x568CD90   ; -> loc_568cd90
568cd7b  int3            (pad byte inside the 0xc-byte body; unreachable)
```
Function [0x568cd70, 0x568cd7c): drops arg1 (rcx), sets target rcx = rdx (view object), target rdx = r8 (pass state object), tail-jumps to 0x568cd90 (sub_568cd90 / FrameGraph::viewSetupTask, lift set D2, docs/functions/568cd90.md). r8, r9 and stack args pass through unchanged; void return passes through. No memory reads/writes; no `call` instruction (jmp). No callees outside the lift set: no UNRESOLVED CALL.

## Analysis
The thunk forwards to the already-lifted view-setup task body (native_functions.tsv: 0x568cd90 D2, native symbol FrameGraph::viewSetupTask). Forward-declared in the unit header as native::sub_568cd90(void* view, void* state) per the lift-set callee rule; called like any lifted function. Exact types of the view/state objects are not recovered anywhere (no callers pin them) so they are declared as opaque void* — no guessing of meaning.

## Step status
- Step 1 (write file "## NEXT" / "step 2"): DONE.
- Step 2 (disassemble 0x568cd70): DONE — 0xc bytes, 4 instructions.
- Step 3 (write docs/functions/568cd70.md + passes/sub_568cd70.h + passes/sub_568cd70.cpp): DONE.
- Step 4 (cppsyntax + liftcheck): cppsyntax.py fails identically on existing known-good lifted files (framework header PCH issue, no errors in my code); liftcheck 0x568cd70 -> LIFTCHECK OK.

## FILES
- docs/progress/oc_U-EX5.568cd70.md (this result file, written)
- docs/functions/568cd70.md (dossier with Reversed source (complete) section, written)
- src/client/features/render/native/passes/sub_568cd70.h (layout constants, static_asserts, signature, forward declaration, written)
- src/client/features/render/native/passes/sub_568cd70.cpp (LIFT marker first line, lifted body, LIFT_FN registry entry, written)
No other files created or changed; Sigs.json, shared headers, CMake, hooks untouched; no builds run.

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x568cd70` printed:
LIFTCHECK OK 0x568cd70
(exit code 0)

## UNRESOLVED CALL
none — the only control-flow transfer is the jmp to 0x568cd90, which is in the lift set (native_functions.tsv, D2); there are no `call` instructions in the function.

## TOOL REQUESTS
None.

CLOSES? YES
