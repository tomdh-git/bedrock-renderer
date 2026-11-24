## NEXT
DONE: unit U-EX1.bc962c0 fully lifted; liftcheck printed LIFTCHECK OK 0xbc962c0; see ## FILES, ## LIFTCHECK and CLOSES? line below.

## SUMMARY
Lifted function 0xbc962c0 "frame-graph builder" (size 0x12f bytes, range [0xbc962c0, 0xbc963ef), depth 2, milestone bgfx, previously D0). The function takes `self` in rcx (a `sub_bc962c0_state*` with two inline buffers: A @+0x00/+0x10/+0x18 and B @+0x78/+0x88/+0x90, plus refcounted object pointers @+0x28 and @+0x68), releases each heap buffer through lift-set callee sub_e935700 (0xbc96306 / 0xbc963b6, `call 0xE935700`, `jmp sub_392960` forwarder verified at entry), releases object C via vtable[4] and object B via strong/weak lock-decremented refcount with vtable[0]/vtable[1] (all three indirect calls go through `call qword ptr [0xF99FFA0]`, the jmp-rax thunk data slot), resets both buffers to small empty state (size 0, capacity 0xF), and takes a bounds-check failure path through `call qword ptr [0xF9A8C78]` (_invoke_watson import slot, noreturn) then int3. Returns void.

## FILES
- docs/progress/oc_U-EX1.bc962c0.md — this result file (created)
- docs/functions/bc962c0.md — dossier (signature, arg map, phase-by-phase reversed source with verbatim call quotes, fields-touched table, callees table, verification notes; created)
- src/client/features/render/native/bgfx/sub_bc962c0.h — layout constants (RefObj/sub_bc962c0_state), offset + sizeof static_asserts, signature, sub_e935700 forward declaration (created)
- src/client/features/render/native/bgfx/sub_bc962c0.cpp — lifted source; first line `// LIFT 0xbc962c0 size 0x12f 1.26.62.01 sub_bc962c0`; every instruction of [0xbc962c0, 0xbc963ef) inside cited ranges; every call quoted verbatim; LIFT_FN registry entry `LIFT_FN(sub_bc962c0, "sub_bc962c0", 0xbc962c0, sub_bc962c0, sub_bc962c0_footprint)` (created)
No other files created or changed (Sigs.json, CMake, shared headers, hooks, other units untouched; no build run).

## LIFTCHECK
LIFTCHECK OK 0xbc962c0

## UNRESOLVED CALL
none — sub_e935700 is a lift-set callee (forward-declared, native symbol); the three `call qword ptr [0xF99FFA0]` and the `call qword ptr [0xF9A8C78]` are indirect calls through documented data slots read at call time (slots 0xF99FFA0 / 0xF9A8C78), per the indirect-call rule; no callee is outside the lift set / boundary.

## TOOL REQUESTS
None.

CLOSES? YES
