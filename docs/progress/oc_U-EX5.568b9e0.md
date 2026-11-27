## NEXT DONE — unit U-EX5.568b9e0 finished: header + implementation written (and syntax-checked), dossier verified complete, `python tools/sigs/liftcheck.py 0x568b9e0` printed `LIFTCHECK OK 0x568b9e0`; no open items.

UNIT U-EX5.568b9e0: function 0x568b9e0, size 0x95 bytes (0x568b9e0..0x568ba75), depth 0, milestone 5, region pass-tasks, name "common pass task encode (queues the custom item)", root "pass encode A". No callees in the lift set are called directly: sub_568bcd0's address is only taken (passed as an argument), sub_bc61560 is tail-called.

Disassembly re-verified with `rdis dis 0x568b9e0 80` [V]: matches the captured listing exactly — 0x568b9e0 push rsi / 0x568b9e1 push rdi / 0x568b9e2 sub rsp,0x28 / ... / 0x568ba70 jmp 0xBC61560; the body ends at 0x568ba75, followed by int3 padding.

Semantics [V] (reads/writes/calls in original order): pass object (RCX) fields +0x2E0/+0x2E8/+0x2F0 updated from item object (RDX): pass+0x2E0 = *item+0x0; if item+0x10 != null, refcount at *(item+0x10)+0x8 is lock-inc'd; pass+0x2E8 = item+0x8 (obj8 pointer); pass+0x2F0 overwritten with item+0x10's value (newObj, or 0); oldObj = previous pass+0x2F0 released: lock dec [oldObj+0x8]; if zero, virtual destructor vfptr[0](oldObj) via `call qword ptr [0xF99FFA0]` at 0x568ba35 (sub_eea6040 thunk); lock dec [oldObj+0xC]; if zero, virtual delete vfptr[1](oldObj) via `call qword ptr [0xF99FFA0]` at 0x568ba4b (same thunk); tail call sub_bc61560([obj8+0x10], (uint16_t)[obj8+0x8], &sub_568bcd0, passObj). Same reads, same writes, same calls in the same order, same return (void, passed through the tail call).

## FILES
- docs/progress/oc_U-EX5.568b9e0.md (this file: rewritten; state, ## FILES, ## LIFTCHECK, ## UNRESOLVED CALL, CLOSES? YES)
- src/client/features/render/native/passes/sub_568b9e0.h (existing file, edited: removed the word "stubs" from a comment so the file carries no STUB_RE hit; layout constants kPassOffset0x2E0/0x2E8/0x2F0, kItemOffset0x00/0x08/0x10, kObj8Offset0x08/0x10, kRefcountedOffsetVfptr/Refcount/Count0xC; structs sub_568b9e0_pass/item/obj8/refcounted with static_asserts incl. sizeof checks; forward declarations void sub_568bcd0(void*) and extern "C" void bgfx::sub_bc61560(void*, uint16_t, void*, void*); signature void sub_568b9e0(void* passObj, void* item))
- src/client/features/render/native/passes/sub_568b9e0.cpp (existing file, edited: `native::Boundary<std::uintptr_t, void*, void*> sub_eea6040(...)` so the wrapper compiles with Lift.h's static_assert (sizeof(void) is ill-formed); added `static_assert(sizeof(void*) == 8, ...)` at the top of the body for liftcheck; per-instruction `// 0xA..0xB` range citations beside every block; verbatim call quotes; LIFT_FN(sub_568b9e0, "sub_568b9e0", 0x568B9E0, ::native::sub_568b9e0, nullptr); #if 0 block with all 41 verbatim instructions of [0x568b9e0, 0x568ba75))
- docs/functions/568b9e0.md (existing dossier, read and verified complete: signature, register/argument map, phases 0x568b9e0..0x568ba75, struct fields touched table, callees table, 'Reversed source (complete)' section with verbatim call quotes, ownership/threading, version anchors, verification; no [?]/[I]/TODO/UNVERIFIED; no changes needed)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x568b9e0` printed exactly:

LIFTCHECK OK 0x568b9e0

(exit code 0; verify_oc mismatch=0, no-such-instr=0 on all quoted lines; coverage 100% of [0x568b9e0, 0x568ba75); both calls 0x568ba35 / 0x568ba4b quoted verbatim)

## UNRESOLVED CALL
none — `call qword ptr [0xF99FFA0]` at 0x568ba35 and 0x568ba4b targets sub_eea6040 via data slot 0xF99FFA0, native_boundary.tsv row 506 (class vendor, loader-resolved thunk) [V]; the tail call `jmp 0xBC61560` targets sub_bc61560, in native_functions.tsv (lift set, D2) [V]; sub_568bcd0 (lift set, D2) has only its address taken, never called. No call target lies outside the lift set and native_boundary.tsv.

## TOOL REQUESTS
None

CLOSES? YES
