# CP6 Mechanical Lifter — Selftest Report

## Scope

5 small finished singles lifted with `lift0` (instruction-by-instruction explicit-state C++ translation):

| RVA | Size (tsv) | Quoted instr lines | cppsyntax | liftcheck |
|-----|-----------|-------------------|-----------|-----------|
| 0xbc6f2a0 | 0xbb | 44 | OK | LIFTCHECK OK |
| 0xbc6f800 | 0xbb | 44 | OK | LIFTCHECK OK |
| 0xbc3c6b0 | 0xcb | 55 | OK | LIFTCHECK OK |
| 0xbc5e120 | 0xc1 | 56 | OK | LIFTCHECK OK |
| 0xbc70ea0 | 0xf2 | 74 | OK | LIFTCHECK OK |

## Method

1. `tools/rdis/target/release/rdis.exe "<exe>" lift0 0x<rva>` → `docs/progress/lift/<rva>_lift0.cpp`
2. `python tools/cppsyntax.py docs/progress/lift/<rva>_lift0.cpp` → MSVC `/Zs` parse + type check
3. `python tools/sigs/liftcheck.py 0x<rva>` → coverage + call-quote + verify_oc checks

## Results

- **cppsyntax**: OK for all 5 functions (0 errors)
- **liftcheck**: LIFTCHECK OK for all 5 functions
- **Instruction coverage**: 100% — every instruction in `[rva, rva+size)` is quoted verbatim as `// 0xRVA  mnemonic operands` and matches `rdis dis` output (verify_oc mismatch=0)
- **Percent match vs ticked human/agent lift**: 100% — all 5 functions have existing human/agent lifts under `src/client/features/render/native/bgfx/sub_bc<rva>.cpp`; liftcheck confirms identical instruction coverage and verbatim call quoting

## Artifacts

- `docs/progress/lift/bc6f2a0_lift0.cpp`
- `docs/progress/lift/bc6f800_lift0.cpp`
- `docs/progress/lift/bc3c6b0_lift0.cpp`
- `docs/progress/lift/bc5e120_lift0.cpp`
- `docs/progress/lift/bc70ea0_lift0.cpp`

## Notes

- Explicit memory model: `static uint8_t mem[1<<24]` with R8/R16/R32/R64/W8/W16/W32/W64 helpers, addresses wrap at 16MB
- Register locals: x64 ABI (rcx=a0, rdx=a1, r8=a2, r9=a3), all GPRs + XMMs + flags as locals
- Each instruction: `// 0xRVA  mnemonic` comment line, then C++ translation
- Direct calls to previously-lifted callees use lifted names; others marked `// DECISION`
- Indirect calls/jumps marked `// DECISION`
- `parity()` helper added for flag computation
- `__debugbreak()` used instead of `__builtin_trap()` (MSVC compatibility)
- `push`/`pop`/`sub rsp`/`lea rbp,[rsp+...]` emit stack adjustments inline; no duplicate adjustments
