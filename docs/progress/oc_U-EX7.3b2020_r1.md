## NEXT
DONE

UNIT U-EX7.3b2020: LIFT sub_3b2020 (0x3b2020, 0xac bytes, depth 0, milestone 7, region D0, root, 0 callees already in the lift set).
Contract: docs/RENDER_NATIVE_SPEC.md; hard rules: docs/OPENCODE_BRIEF.md. All work static analysis only; the exe was passed only to rdis.exe.

## FILES
- docs/progress/oc_U-EX7.3b2020.md (this result file; created)
- docs/functions/3b2020.md (created: dossier — signature, register/argument map, per-phase disassembly with // 0xA..0xB citations, Reversed source (complete), struct fields touched, callees with [V], version anchors, ownership/threading, open questions)
- src/client/features/render/native/helpers/sub_3b2020.cpp (created: first line `// LIFT 0x3b2020 size 0xac 1.26.62.01 sub_3b2020`; lifted C++; verbatim call quotes in #if 0 block; LIFT_FN registry entry; repeated layout static_asserts)
- src/client/features/render/native/helpers/sub_3b2020.h (created: sub_3b2020_state layout constants at +0x08/+0x18/+0x4C/+0x60 with static_asserts; opaque struct _Mtx; forward declarations of lift callees sub_eec59f0/sub_eec5a00/sub_eec5a10 in namespace native per hard rule 66; sub_3b2020 signature)

No other files created or changed (Sigs.json, shared headers, CMake, hooks, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, docs/data/* untouched; no builds, no game started).

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x3b2020` printed:
LIFTCHECK OK 0x3b2020

(All mechanical checks pass: dossier with Reversed source section free of [?]/[I]/TODO/UNVERIFIED; source first-line LIFT marker size 0xac == function size 0xac; no stub/TODO language; LIFT_FN registry entry; layout static_asserts; all 47 instructions of [0x3b2020, 0x3b20cc) inside cited ranges; all 6 call instructions quoted verbatim and verify_oc mismatch=0, no-such-instr=0.)

## UNRESOLVED CALL
The following call targets of 0x3b2020 are in NEITHER docs/data/native_functions.tsv NOR docs/data/native_boundary.tsv (and not in Sigs.json), so they are blockers per the hard rules: the calls are quoted verbatim but not translated into C++, and no wrapper was invented.
- 0xE943170: `0x3b2056  call 0xE943170` (RCX = self; runs between the refcount xadd and the lock and)
- 0xE943194: `0x3b206d  call 0xE943194` (RCX = self; runs after the lock and clears the destroying bit)
- 0xEEC5B90: `0x3b2092  call 0xEEC5B90` (RCX = self+0x18; runs in the destroy path before the tail call)

The lift-classified callees (in native_boundary.tsv as "lift") were called through their native symbols: 0xEEC59F0 at 0x3b2079 (native::sub_eec59f0, _Mtx_lock via data slot 0xF9A75A8), 0xEEC5A00 at 0x3b20b3 and 0x3b20c5 (native::sub_eec5a00, std::_Throw_Cpp_error via slot 0xF9A72F0, never returns), 0xEEC5A10 via tail jmp at 0x3b20a1 (native::sub_eec5a10, _Mtx_unlock via slot 0xF9A75B8). These are not blockers.

Lifted semantics (same reads/writes/calls/return as the exe, x64 Microsoft ABI, void, RCX=self): atomic refcount at self+0x60 decremented with lock xadd (-1); unless the old value was exactly 0x8000000000000001 the function returns; otherwise the destroying bit is cleared (lock and 0x7FFFFFFFFFFFFFFF), the embedded mutex at self+0x8 is locked via sub_eec59f0, EAX is tested (jne -> fatal path), the state dword at self+0x4C is compared with 0x7FFFFFFF (je -> fatal path: write 0x7FFFFFFE, sub_eec5a00(6), int3), otherwise &self+0x18 is passed to sub_eec5b90 and the function tail-calls sub_eec5a10(mtx) (_Mtx_unlock). Fatal path: sub_eec5a00(5) (_Throw_Cpp_error, never returns; the subsequent 0x7FFFFFFE write/sub_eec5a00(6)/int3 are dead in the original too, mirrored for layout fidelity).

## TOOL REQUESTS
None.

CLOSES? NO UNRESOLVED CALL: 0x3b2020 calls 0xE943170 (0x3b2056), 0xE943194 (0x3b206d) and 0xEEC5B90 (0x3b2092); none are in native_functions.tsv or native_boundary.tsv, so the calls cannot be translated (no wrappers invented) per the hard rules.
