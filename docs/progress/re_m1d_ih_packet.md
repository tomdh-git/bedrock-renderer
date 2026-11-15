# re_m1d_ih_packet — M1d unit (2b): ItemInHand 0x6698e30 packet field copies 0x669c35f..0x669c8f9

## NEXT
- **Unit:** M1d (2b) packet field copies 0x669c35f..0x669c8f9 — **DONE (structural/byte-level map)**; semantic/type meaning of most staged locals and packet fields remains **OPEN [?]** pending producer tracing and callee reversal (`0x67d14e0`, `0x6764990`, `0xe869ff0`).
- **Exact resume (next meaningful unit for 0x6698e30):**
  1. Reverse/characterize callees used in/around packet submit: `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "sum 0x67d14e0"` (large; focus on arg consumption of packet ptrs), and `sum 0x6764990`, `sum 0xe869ff0` for inline/blob copy semantics. [V tools available]
  2. Trace producers of staged locals `rbp+0x18c0..0x1ba8` (esp. gates at `0x1900,0x1970,0x19f4,0x1a0c,0x1a68,0x1ab8,0x1b48,0x1ba8`) back to desc/mesh/material sources within 0x6698e30 to attach meanings to packet fields.
  3. Map shared_ptr bookkeeping/secondary geometry `0x669bd5d..0x669c2a6` (still partly described).
- **Commands run this unit:** see “Tooling used”.
- **Half-done:** none. All bytes in requested range 0x669c35f..0x669c8f9 mapped to src/dst/size/gate [V]; semantics unresolved [?].

## Progress log

### M1d-IH-PACKET-0x669c35f..0x669c8f9 - DONE (structural byte-level mapping) | OPEN (semantic meanings/types) [V/I/?]
- **Scope:** Item-in-hand clone/extractor `0x6698e30`, submit-packet assembly region G `0x669c35f..0x669c8f9` (byte-level field copies into call-arg packet blocks for `0x67d14e0`).
- **Evidence / commands [V]:**
  - `python tools/sigs/disrange.py 669c35f 669c8f9`
  - `python tools/sigs/disrange.py 669c2e0 669ca00` (surrounding context incl. arg setup to `call 0x67d14e0` at `0x669c9bb`)
  - Prior context: `docs/functions/0x6698e30.md`, `docs/functions/6698e30.md` (notes call `0x67d14e0` arg layout), `docs/progress/re_m1d_ih_dtree.md`
  - `graphify query "item-in-hand clone 0x6698e30 packet field copies 0x669c35f..0x669c8f9"` attempted but `graphify` not found in PATH [V env blocker for that tool only; proceeded with static disasm/docs].
  - `Select-String` over docs found existing references to `0x67d14e0`/packet ptrs in `docs/functions/6698e30.md:235` and BGFX_MAP.
  - `tools\rdis\target\release\rdis.exe "<BS_EXE>" -c "sum 0x67d14e0"` run (very large output; confirms complex callee, not reversed here).
- **Findings [V]:** range is stack-to-stack marshalling from staged locals `rbp+0x18xx..0x1bxx` to packet blocks `rbp+0x1bf8..0x1ee0+`. Contains unconditional scalar copies, gated optional blocks (validity bytes `1c38,1ca8,1d2c,1d44,1da0,1df0,1e80,1ee0`), inline SSO/buffer construction + `call 0x6764990`, composite refcounted/shared_ptr-like copies with `lock inc [ctrl+8]`, tagged variant copies (type byte at `1ab0`), blob copy/construct + move via `call 0xe869ff0` and source clears, and selector jump table at `0xf2bf7b8` (cases 1-3) for block `1e88..`. Prepares args and calls `0x67d14e0(rcx=[ctx+0x10]+0x9d0, ...)` at `0x669c9bb`. No direct deref of ItemInHandDescription `r8` in this range.
- **What remains OPEN [?]:** semantic names/types for most packet fields and their staged sources; precise parameter-struct layout consumed by `0x67d14e0`; behavior of `0x6764990`/`0xe869ff0`.
- **Files edited:** `docs/functions/0x6698e30.md` (appended packet-copy mapping + updated Pending/Verification), `docs/progress/re_m1d_ih_packet.md` (this file). **Not edited:** `docs/BGFX_MAP.md`, `docs/RENDER_CHECKLIST.md`. No SDK headers or `docs/data/layout_asserts.json` changed (no verified Sigs-anchored immediates/displacements suitable for layout asserts discovered).

## Final report

- **Mapped (D2-style, instruction-level) 0x669c35f..0x669c8f9 [V]:**
  - `+0x1bf8`/`+0x1c00`: u32/u16 from staged `0x18c0/0x18c8`.
  - `+0x1c08..` (flag `+0x1c38`): gated (`0x1900==1`) SSO init `{ptr=&1c18, 0x00000001_00000000}` + `call 0x6764990(&1c08,&0x18d0)`.
  - `+0x1c40`: u16 from `0x1908`.
  - `+0x1c48..0x1ca8` (flag `+0x1ca8`): gated (`0x1970==1`) composite block with 4 shared_ptr-like pairs copied with `lock inc [ctrl+8]` from `(1910,1918),(1938,1940),(1948,1950),(1958,1960)`, plus xmm/qword/u16 fields from `1920,1930,1968`.
  - `+0x1cb0..0x1cf8`: straight qword/u16 run from `1978,1980,1988,1990,1998,19a0,19a8,19b0,19b8,19c0` (arg ptrs r12/r13 and stack `+0x88..+0x40`).
  - `+0x1d00..0x1d2c` (flag `+0x1d2c`): gated (`0x19f4==1`) tagged payload from `19c8/19d8/19e0/19e4` -> `1d00/1d10/1d18/1d1c`.
  - `+0x1d30`: u32 from `0x19f8`.
  - `+0x1d38..0x1d44` (flag `+0x1d44`): gated (`0x1a0c==1`) qword+f32 from `0x1a00/0x1a08` (locals linked to desc+0x68/+0x6C by earlier D-tree [I]).
  - `+0x1d48..0x1da0` (flag `+0x1da0`): gated (`0x1a68==1`) packed struct/blob copy from `0x1a10..0x1a57` region (including unaligned tail at `0x1a57 -> 0x1d8f`).
  - `+0x1da8..0x1df0` (flag `+0x1df0`, tag `+0x1de8`): gated (`0x1ab8==1`) variant union from `0x1a70..0x1ab0` (type 0: 4×xmm, type 1: moved xmm+qword with source clear, type 2: qword).
  - `+0x1df8..0x1e80` (flag `+0x1e80`): gated (`0x1b48==1`) qword + `call 0xe869ff0(&1e00,&0x1ac8)` + moved qword `0x1b40 -> 0x1e78` with source clear.
  - `+0x1e88..0x1ee0` (flag `+0x1ee0`): gated (`0x1ba8==1`) variant/dispatch copy with jump table `0xf2bf7b8` on selector `0x1b88` (cases 1 qword, 2 xmm, 3 shared_ptr-like pair with refcount inc; tag stored to `0x1ec0`), plus surrounding fields from `0x1b50/60/70/90/a0`.
  - Call prep in-range: `rcx=[rbx+0x10]+0x9d0`, arg ptr regs/pointers to blocks; stack args and `call 0x67d14e0` at `0x669c9bb` (just after range) consume these packet addresses [V, consistent with existing call note].
- **OPEN:** no per-field high-level semantics/types confirmed; no new SDK struct offsets/static_asserts added. `graphify` CLI unavailable in this environment [V].

## FULL PROPOSED BGFX_MAP ENTRY TEXT (entry IDs TBD)

```text
### 6dz (M1d, additive) — ItemInHand extractor 0x6698e30 packet field copies / submit marshalling 0x669c35f..0x669c8f9 [V]
- Range 0x669c35f..0x669c8f9 (static disasm, 62.01; `tools/sigs/disrange.py 669c35f 669c8f9`, ctx `669c2e0..669ca00`): assembles stack-resident packet/argument blocks `rbp+0x1bf8..0x1ee0+` from staged locals `rbp+0x18xx..0x1bxx` for submit `call 0x67d14e0` at 0x669c9bb (`rcx=[ctx+0x10]+0x9d0`). Byte-level map (all [V]):
  - Scalars/headers: `18c0(d)->1bf8`, `18c8(w)->1c00`, `1908(w)->1c40`, `1978(q)->1cb0`, `1980/88/90/98/a0/a8/b0/b8/c0(w)->1cb8..1cf8`, `19f8(d)->1d30`.
  - Gated optional blocks with validity flags: `1900==1` -> SSO/buffer init at 1c08 (ptr &1c18, 0x1_00000000) + `call 0x6764990(&1c08,&18d0)`, set 1c38; `1970==1` -> composite 1c48..1ca8 (4 shared_ptr-like pairs from 1910/18,1938/40,1948/50,1958/60 copied with `lock inc [ctrl+8]` when non-null, plus 1920/1930/1968), set 1ca8; `19f4==1` -> tagged 1d00..1d2c from 19c8/d8/e0/e4, set 1d2c; `1a0c==1` -> 1d38(q)+1d40(f) from 1a00/1a08, set 1d44 (sources linked to desc+0x68/+0x6C by earlier D-tree [I]); `1a68==1` -> packed 1d48..1d9f from 1a10/20/24/28/38/48/57 (unaligned tail), set 1da0; `1ab8==1` -> variant 1da8..1de8 by type@1ab0 (0: 4×xmm 1a70..1aa0, 1: moved xmm/qword from 1a70/80 clearing source, 2: qword 1a70), set 1df0; `1b48==1` -> 1df8(q)+`call 0xe869ff0(&1e00,&1ac8)`+move 1b40->1e78(clear src), set 1e80.
  - `1ba8==1` -> 1e88..1ee0 from 1b50/60/70/90/a0 plus selector@1b88 via jump table 0xf2bf7b8: case1 qword 1b78->1eb0, case2 xmm 1b78->1eb0, case3 shared_ptr-like (1b78,1b80 ctrl w/ `lock inc`) -> (1eb0,1eb8), tag 1ec0=selector, else 1ee0=0.
  - No direct ItemInHandDescription (`r8`) reads in this range. Field/packet semantics and callee layouts (`0x67d14e0`, `0x6764990`, `0xe869ff0`) remain [?]/OPEN.
- Evidence: [V] static disassembly 62.01; [I] limited cross-ref to prior 6698e30 phase notes for desc+0x68/+0x6C and call-site arg pointers. Details: `docs/progress/re_m1d_ih_packet.md`, `docs/functions/0x6698e30.md`.
```
