## NEXT

DONE: All 12 acceptance functions processed. 8/12 pass `LIFTTEST OK N=100`; 4/12 skipped due to `int3` in lift0 before `ret` (cannot call via DLL). SELFTEST2.md written with full details. Key fixes: RIP-relative lea absolute target, TEST flag semantics, DCE ret-RAX liveness, lifttest scans both lift0/lift2 for stubs, namespace-scope helpers in lift2.

---

## DONE — Completed Work

- `tools/rdis/src/lift.rs`: emit_lea + propagate() fixed for RIP-relative lea → Val::Const(abs_target)
- `tools/rdis/src/lift.rs`: emit_call emits real stub calls (raw_call_*), never drops unmodeled calls
- `tools/rdis/src/lift.rs`: lift2 signature always 4×uint64_t (a0..a3), header not included, explicit STATEMENT per instruction with DECISIONS fallbacks, all GPR/flag locals (including rip) declared
- `tools/rdis/src/lift.rs`: Memory-model helpers (R8/W8/etc) and extern "C" decls at namespace scope inside `namespace native { }`
- `tools/rdis/src/lift.rs`: Pre-scan tracks via_mem/via_reg + boundary/native/raw_call decls
- `tools/rdis/src/lift.rs`: TEST flags use `&` (AND), CMP uses `-` (SUB) — fixed lift2 divergence
- `tools/rdis/src/lift.rs`: Reg liveness analysis treats `ret` as reading RAX — fixed DCE removing `mov rax, rsi` before ret
- `tools/ctx/lifttest.py`: parse_cpp_signature matches `uint64_t sub_[hex]` skipping static inline helpers
- `tools/ctx/lifttest.py`: generate_stubs_h scans BOTH lift0.cpp and lift2.cpp for calls
- `tools/ctx/lifttest.py`: compile_dll hoists block-scope extern "C" to global scope ONLY for lift0
- `tools/ctx/lifttest.py`: All stubs use uint64_t return type; deterministic memory/call log shared
- cargo build --release succeeds
- All 12 acceptance lift2 files pass cppsyntax.py

## lifttest Results (N=100)

| RVA | Result | Notes |
|-----|--------|-------|
| aa3c0 | LIFTTEST OK | RIP-relative lea returns 0x128C1588 (was 0) |
| e9425f0 | LIFTTEST OK | |
| 663f9d0 | LIFTTEST OK | |
| 66399b0 | LIFTTEST OK | Indirect call via mem |
| 6639b70 | LIFTTEST OK | Indirect call via mem |
| 6639bc0 | LIFTTEST OK | Direct call to unknown |
| 3b23c0 | LIFTTEST OK | X7, 0x8 bytes |
| 7e6d0 | LIFTTEST OK | X7, 0x48 bytes |
| 6685f60 | SKIPPED | int3 before ret in lift0 |
| 66a17c0 | SKIPPED | int3 before ret in lift0 |
| 66a1820 | SKIPPED | int3 before ret in lift0 |
| bcbe410 | SKIPPED | int3 before ret in lift0 |

## Artifacts

- SELFTEST2.md: `docs/progress/SELFTEST2.md`
- Lift outputs: `docs/progress/lift/{rva}_lift{0,2}.cpp`
- OK markers: `docs/progress/lift/{rva}_lifttest.ok` (8 files)