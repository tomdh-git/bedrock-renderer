# SELFTEST2 — lift0 vs lift2 Equivalence Gate Results

**Date:** 2026-11-24  
**Exe:** Minecraft.Windows.exe 1.26.62.01  
**N per function:** 100 random 64-bit inputs (seed = 0xC0FFEE ^ rva)

## Summary

| RVA | Size | Section | Result | Notes |
|-----|------|---------|--------|-------|
| aa3c0 | 0x8 | X7 | **LIFTTEST OK** | RIP-relative lea fixed; returns 0x128C1588 |
| e9425f0 | 0x12 | X? | **LIFTTEST OK** | |
| 663f9d0 | 0x54 | X4 | **LIFTTEST OK** | |
| 66399b0 | 0x34 | X4 | **LIFTTEST OK** | Indirect call via mem; TEST flag fix applied |
| 6639b70 | 0x42 | X4 | **LIFTTEST OK** | Indirect call via mem; TEST flag fix applied |
| 6639bc0 | 0x24 | X4 | **LIFTTEST OK** | Direct call to unknown; DCE ret-rax fix applied |
| 6685f60 | 0x25 | X4 | **SKIPPED** | lift0 has `int3` before `ret` — cannot call via DLL |
| 66a17c0 | 0x51 | X4 | **SKIPPED** | lift0 has `int3` before `ret` — cannot call via DLL |
| 66a1820 | 0x36 | X4 | **SKIPPED** | lift0 has `int3` before `ret` — cannot call via DLL |
| bcbe410 | 0x11 | X1 | **SKIPPED** | lift0 has `int3` before `ret` — cannot call via DLL |
| 3b23c0 | 0x8 | X7 | **LIFTTEST OK** | Minimal function (likely `ret` only) |
| 7e6d0 | 0x48 | X7 | **LIFTTEST OK** | |

**Passed:** 8/12  
**Skipped (int3 in lift0):** 4/12

## Key Fixes Applied

1. **RIP-relative `lea`**: `emit_lea` + `propagate()` now compute absolute target (`next_ip + disp32`), not `rip + disp32` with rip=0. Verified by aa3c0 returning 0x128C1588 (was 0).

2. **`emit_call` never drops calls**: Both lift0 and lift2 emit real external-call stubs (`raw_call_XXXX`, `raw_call_via_mem`, `raw_call_via_reg`) matching the lifttest harness.

3. **lift2 signature**: Always `uint64_t(a0,a1,a2,a3)` like lift0; header return types ignored; forward declarations for native::boundary::sub_X and native::sub_X.

4. **TEST instruction flags**: lift2 now uses `&` (AND) for TEST, `-` (SUB) for CMP — matches lift0. Fixed 66399b0/6639b70 divergences.

5. **DCE ret-value tracking**: Reg liveness analysis now treats `ret` as reading RAX (RAX has no operands in iced-x86). Fixed 6639bc0 divergence where `mov rax, rsi` before `ret` was incorrectly removed.

6. **lifttest harness**:
   - Scans both lift0.cpp and lift2.cpp for calls (was only lift2)
   - Hoists block-scope `extern "C"` to global scope for lift0 only
   - All stubs use `uint64_t` return type
   - Deterministic memory pattern (LIFTTST_MEM) and call log shared between DLLs

## lift0 Fallbacks (Unhandled Instructions)

For the 8 passing functions, lift0 emits `// DECISIONS` comments for:
- Stack frame base unknown (rsp initial value not modeled)
- Memory model wraps at 16MB (addresses >0xFFFFFF alias)
- XMM operations partially modeled (mov, xorps only)
- Flag computations exact for ADD/SUB/CMP/TEST/AND/OR/XOR/INC/DEC/NEG/SHL/SHR/SAR; approximate for others
- Indirect calls/jumps: target unknown at lift time (DECISION)
- Some CMP/TEST with memory operands marked unhandled

These fallbacks are identical in lift0 and lift2 (both use deterministic zero-initialized memory model and external-call stubs), so equivalence holds under the test harness.

## Files

- Lift outputs: `docs/progress/lift/{rva}_lift{0,2}.cpp`
- OK markers: `docs/progress/lift/{rva}_lifttest.ok` (for 8 passing functions)
- Harness: `tools/ctx/lifttest.py`
- Core edits: `tools/rdis/src/lift.rs` (emit_lea, propagate, emit_call, emit_lift2 body, reg liveness)