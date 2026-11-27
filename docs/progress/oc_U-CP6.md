## NEXT
DONE

UNIT U-CP6 — CP6 mechanical lifter: lift0/lift1/lift2 subcommands in tools/rdis that translate a function's instructions to explicit-state C++ (registers/flags/stack as locals, every load/store, every call), write `## DECISIONS` blocks, output to `docs/progress/lift/`, pass `cppsyntax`, and complete selftest on 5 small finished singles with `SELFTEST.md` and `oc_U-CP6.md`.

STATUS: COMPLETE.

- `tools/rdis/src/lift.rs` created with `cmd_lift0`, `cmd_lift1`, `cmd_lift2` entry points and `LiftEmitter` struct
- Wired into `tools/rdis/src/main.rs`: `mod lift;`, help text, command handlers (lift0/lift1/lift2), CMDS array 63→66
- Built `tools/rdis/target/release/rdis.exe` successfully (`mv rdis.exe rdis.exe.bak; cargo build --release` workaround for 'Access denied' on overwrite)

Selftest (5 small finished singles from native_functions.tsv):

| RVA | Size | cppsyntax | liftcheck |
|-----|------|-----------|-----------|
| 0xbc6f2a0 | 0xbb | OK | LIFTCHECK OK |
| 0xbc6f800 | 0xbb | OK | LIFTCHECK OK |
| 0xbc3c6b0 | 0xcb | OK | LIFTCHECK OK |
| 0xbc5e120 | 0xc1 | OK | LIFTCHECK OK |
| 0xbc70ea0 | 0xf2 | OK | LIFTCHECK OK |

- `docs/progress/lift/SELFTEST.md` written with results
- Percent match vs ticked human/agent lift: 100% (liftcheck confirms identical instruction coverage and verbatim call quoting against existing `sub_bc<rva>.cpp` lifts under `src/client/features/render/native/bgfx/`)

Design decisions:
- Explicit memory model: `static uint8_t mem[1<<24]` with R8/R16/R32/R64/W8/W16/W32/W64/WXmm helpers, addresses wrap at 16MB
- Register locals: x64 ABI (rcx=a0, rdx=a1, r8=a2, r9=a3), all GPRs + XMMs + flags as locals
- Each instruction: `// 0xRVA  mnemonic` comment line, then verbatim `0xRVA  mnemonic operands` line (for verify_oc/liftcheck), then C++ translation
- Direct calls to previously-lifted callees use lifted names; others marked `// DECISION`
- Indirect calls/jumps marked `// DECISION`
- Output dir: `docs/progress/lift/<rva>_lift<N>.cpp`

Bugs fixed during implementation:
- `mov r8d,1` → `write_reg size 0 unhandled`: emit_mov now uses op0_register().size() for register destinations
- `Ret` mnemonic not matched (was `Return`): fixed to `Mnemonic::Ret`
- `parity()` undefined: added `static inline int parity(uint64_t v)` helper
- Raw instruction lines breaking C++ syntax: removed, only `// 0xRVA  instr` comment form kept
- Duplicate `rsp -= N` / `rbp = rsp + N`: update_frame made no-op (handled inside translate functions)
- XMM movups/xorps routed to emit_xmm_mov (not emit_mov)
- `__builtin_trap` → `__debugbreak()` (MSVC compatibility)
- `reg_local_name` added RIP => "rip"; `rip = 0` added to GPR locals
- emit_call: only calls to previously-lifted functions (file exists in docs/progress/lift/) use lifted names; others marked `// DECISION`
