## NEXT
DONE

## Unit
U-EX1.bc55ea0 — LIFT sub_bc55ea0 (0xbc55ea0, 0x105 bytes, depth 2, D0, 0 callees in set) — BgfxFrameBuilder::endFrame helper.

## What it does
`sub_bc55ea0(Slot* a /*rcx*/, Slot* b /*rdx*/) -> void` swaps the contents of two Slots ({void* raw @+0x00, RefCounted* ref @+0x08}), keeping each referenced RefCounted alive across the swap with lock-prefixed strong/weak refcount addref/release, and running the object's vtable[0] (destroy) / vtable[1] (dealloc) through the indirect-call gadget at data slot 0xF99FFA0 when counts reach zero. Five indirect call sites, all `call qword ptr [0xF99FFA0]` (virtual dispatch on the referenced object, no static callee, no boundary wrapper).

## FILES
- docs/progress/oc_U-EX1.bc55ea0.md (this result file, created)
- src/client/features/render/native/bgfx/sub_bc55ea0.h (new: layout constants + static_asserts)
- src/client/features/render/native/bgfx/sub_bc55ea0.cpp (new: lifted source, LIFT marker, LIFT_FN registry entry)
- docs/functions/bc55ea0.md (new: dossier with Reversed source (complete))

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc55ea0` printed:
LIFTCHECK OK 0xbc55ea0

## UNRESOLVED CALL
none — every `call` target is the indirect-call gadget 0xF99FFA0 dispatching to the referenced object's own vtable (destroy/dealloc); no external/static callee, no boundary wrapper needed, no UNRESOLVED CALL.

## CLOSES? YES
