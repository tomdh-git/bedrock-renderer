## NEXT
DONE

## FILES
- docs/progress/oc_U-EX7.ebce390.md (this result file; created)
- src/client/features/render/native/helpers/sub_ebce390.h (new: layout constants, static_asserts, ABI signature, forward declaration of lift-set callee native::sub_eec6ec0)
- src/client/features/render/native/helpers/sub_ebce390.cpp (new: first line `// LIFT 0xebce390 size 0x5 1.26.62.01 sub_ebce390`, lifted body, LIFT_FN registry entry)
- docs/functions/ebce390.md (new: dossier with Reversed source (complete))

## LIFTCHECK
LIFTCHECK OK 0xebce390

## UNRESOLVED CALL
none: the function [0xebce390, 0xebce395) contains a single instruction, `0xebce390  jmp 0xEEC6EC0` (no `call`); its tail target sub_eec6ec0 (0xeec6ec0) is class `lift` in docs/data/native_boundary.tsv and is called directly through its forward declaration, linked by its own LIFT_FN at the milestone gate.

## Verification summary (static, read-only)
- Function 0xebce390, size 0x5 (docs/data/native_functions.tsv), depth 0, 0 callees in lift set.
- Disassembly [V]: `0xebce390  jmp 0xEEC6EC0  ; -> sub_eec6ec0`, followed by int3 padding at 0xebce395 (outside the function). Cited range `// 0xebce390..0xebce395` covers the sole instruction.
- Signature [V] from call sites (0x568ce40-0x568ce51, 0x56ae2d7-0x56ae2e8 and others): rcx = pointer argument, rdx = pointer argument, r8d = 32-bit count argument (0x40 / 0x10 observed), return unobserved (rax never read after the call) -> `void sub_ebce390(void* dst, void* src, std::uint32_t count)`.
- Lifted body is one tail call `return sub_eec6ec0(dst, src, count);`: same reads (none), same writes (none in this frame; the forwarded callee owns memory effects), same calls in the same order (none), same return.
- struct fields touched: none; SubEbce390Layout static_asserts assert sizeof(void*)==8 and sizeof(std::uint32_t)==4.
- verify_oc on source: claimed=1 match=1 mismatch=0 no-such-instr=0; on dossier: claimed=2 match=2 mismatch=0 no-such-instr=0.
- No [?]/[I]/TODO/UNVERIFIED/stub/incomplete in source or dossier; no null guards or SEH (original has none).
- cppsyntax.py: no errors in sub_ebce390.cpp (the 112 cl /Zs diagnostics are pre-existing std:: header noise in Detour.h/Profiler.h, identical for existing units such as sub_bc76380.cpp: 111 errors; no build was run).
- No edits to Sigs.json, CMake, shared headers, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, or any other unit's files; no game started.

CLOSES? YES
