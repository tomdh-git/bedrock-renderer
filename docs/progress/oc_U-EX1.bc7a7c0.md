## NEXT
done.

## LIFTCHECK
LIFTCHECK OK 0xbc7a7c0


## UNIT
X1.bc7a7c0 LIFT GuardedPagedArray<0x540>::ensure (RenderBind storage commit) — 0xbc7a7c0, size 0x1dc, depth 1, region bgfx.

## FILES
- docs/progress/oc_U-EX1.bc7a7c0.md (this result file)
- docs/functions/bc7a7c0.md (dossier rewritten: complete 'Reversed source (complete)', all [I]/[?] resolved to [V])
- src/client/features/render/native/bgfx/GuardedPagedArray_ensure.h (new: GuardedPagedArray layout + static_asserts, callee forward-declarations, signature)
- src/client/features/render/native/bgfx/GuardedPagedArray_ensure.cpp (new: lifted source, first line LIFT marker 0x1dc, verbatim call log, static_asserts, LIFT_FN registry entry)

## NOTES
- Calls 0xeec59f0 / 0xeec5a00 / 0xeec5a10 are IAT forwarders (`jmp qword ptr [slot]`); verified at the call site (rcx = mutex pointer; eax tested; ecx = 5/6), forward-declared per hard rule 69 (not invented wrappers).
- Calls 0x3afbe0 (stl) and 0xeec6ed0 (crt) go through native::Boundary wrappers (docs/data/native_boundary.tsv).
- `call qword ptr [0xF99FFA0]` x2: sub_eea6040 `jmp rax` CFG forwarder; caller preloads rax = [g_iface+0x28] / [g_iface+0x8], g_iface = *[0x12322E58].
- `call qword ptr [0xF9A8CB0]` at 0xbc7a97a: fail-fast import via data slot.
- ## UNRESOLVED CALL = none (see below).

## UNRESOLVED CALL
none

CLOSES? YES
