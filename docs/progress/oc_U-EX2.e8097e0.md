## NEXT
DONE. U-EX2.e8097e0 lifted; liftcheck printed LIFTCHECK OK 0xe8097e0. Files: docs/functions/e8097e0.md, src/client/features/render/native/d3d12/sub_e8097e0.cpp, src/client/features/render/native/d3d12/sub_e8097e0.h.

X2.e8097e0 LIFT sub_e8097e0 (0xe8097e0, 0x195 bytes, depth 1, D0, 0 callees in set)

## FILES
- docs/functions/e8097e0.md (created — dossier with "Reversed source (complete)")
- src/client/features/render/native/d3d12/sub_e8097e0.cpp (created — LIFT marker, body, #if 0 call quotes, LIFT_FN)
- src/client/features/render/native/d3d12/sub_e8097e0.h (created — layout constants + static_asserts + signatures)
- docs/progress/oc_U-EX2.e8097e0.md (this result file)

## LIFTCHECK
```
$ python tools/sigs/liftcheck.py 0xe8097e0
LIFTCHECK OK 0xe8097e0
```
verify_oc on the dossier alone: `claimed=8 match=8 mismatch=0 no-such-instr=0` (all 8 call lines match the exe).

## UNRESOLVED CALL
none.

Notes on the three call targets (all resolved, no invented wrapper):
- 0xe80980b  call 0xEEC6EC0 — sub_eec6ec0, class `lift` (docs/data/native_boundary.tsv). Forward-declared `extern "C" void sub_eec6ec0(void*, const void*, std::int32_t)` in the header and called directly (rcx=table, rdx=template, r8d=0xA8).
- 0xe809824, 0xe80985a, 0xe809890, 0xe8098c6, 0xe8098fc, 0xe809932  call 0x4687B0 — sub_4687b0 is a 4-instruction vtable-dispatch thunk (`mov rax,[rcx]; mov rax,[rax+0xD0]; mov r10,[0xF99FFA0](=sub_eea6040 "jmp rax"); jmp r10`), i.e. a virtual call to vtable slot 0xD0 with (this, &buf, 1, 1). Reproduced inline as that vtable[0xD0] call, per the OPENCODE_BRIEF indirect-call / tiny-forwarder rule and the sub_e806560/sub_e809f40 precedent. Not a blocker.
- 0xe80996f  call 0xE951550 — sub_e951550 (__report_gsfailure), class `crt` (native_boundary.tsv). Called through native::Boundary<void, std::uintptr_t>("sub_e951550").

## Summary
sub_e8097e0 template-initialises the 7-entry (stride 0x18, 0xA8 bytes) table at RVA 0x1285DBE0 from the template at RVA 0xF4EDE20 via sub_eec6ec0, then for entries 0,1,2,3,5,6 (entry 4 at 0x1285DC40 is NOT touched) fetches a value through this->vtable[0xD0] and stores it (dword at +0x10 first, then 16-byte block at +0x00) when the entry's first dword != 4; then the /GS cookie check (fail -> sub_e951550) and return.

CLOSES? YES