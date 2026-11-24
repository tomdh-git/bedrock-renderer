## NEXT
DONE

## UNIT
U-EX1.bc97070 | sub_bc97070 [0xbc97070..0xbc971a5), size 0x135, depth 2, milestone D0, region bgfx, root "VV frame-graph builder", callee set empty.

## SUMMARY
Lifted sub_bc97070 (frame-graph builder destructor/clear) into C++ that does exactly what the exe does: same reads/writes in the same order, same calls in the same order, void return (rax dead at ret). Structure: string 2 at +0x80 (+0x90 size, +0x98 cap), interface at +0x70 (vtable slot 4 release with bool = (iface != self+0x38)), refcounted object at +0x30 (lock dec +8 -> vtable[0] destroy; lock dec +0xC -> vtable[1] dealloc), string 1 at +0x00 (+0x10 size, +0x18 cap). Heap free via sub_e935700 (lift forwarder jmp 0x392960, called directly); virtual calls via vtable slots through the [0xF99FFA0] jmp-rax thunk; validation failure calls data slot [0xF9A8C78] (holds 0xF9B055E on disk, loader-patched at runtime) with 5 zero args, noreturn (int3 padding after). No stubs, no skipped branches, no null guards/SEH beyond the original.

## FILES
- src/client/features/render/native/bgfx/sub_bc97070.h (new): layout constants VvFrameGraphBuilder / Bc97070RefCounted with static_asserts, signature, forward declaration of native::sub_e935700
- src/client/features/render/native/bgfx/sub_bc97070.cpp (new): first line `// LIFT 0xbc97070 size 0x135 1.26.62.01 VV frame-graph builder`, complete lifted body with verbatim call quotes and `// 0xA..0xB` range citations, LIFT_FN registry entry + footprint
- docs/functions/bc97070.md (new): dossier with mechanical facts, argument map, instruction-complete phases, 'Reversed source (complete)', struct fields touched, callees, STATUS
- docs/progress/oc_U-EX1.bc97070.md (rewritten): this result file

No other files edited (no Sigs.json, no shared headers, no CMake, no hooks, no builds).

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc97070` printed:

LIFTCHECK OK 0xbc97070

## UNRESOLVED CALL
none. All six calls resolved: `call 0xE935700` x2 (lift callee sub_e935700, forward-declared and called directly), `call qword ptr [0xF99FFA0]` x3 (vtable slots 4/0/1 through the jmp-rax thunk, no static target by design), `call qword ptr [0xF9A8C78]` x1 (data-slot function-pointer call, rule 69, documented with slot RVA).

## TOOL REQUESTS
None (no repo scripts added; a throwaway PE pointer reader was used only in the local temp folder and is not part of the unit).

CLOSES? YES
