# re_m1d_ih_dtree — M1d unit (2a): ItemInHand 0x6698e30 D-tree leaves 0x669be56..0x669bef8

## NEXT
- DONE for this unit: disassembled 0x669be56..0x669bef8 via `python tools/sigs/disrange.py 669be56 669bef8` [V]; cross-checked context against body disasm `python tools/sigs/disrange.py 6698e30 669edE4` written to `%TEMP%\\ih.asm` [V]. Produced leaf mapping (below). Wrote `docs/functions/0x6698e30.md` (additive D-tree leaf section). Optional header/layout_asserts edits: none required (no new numeric offsets discovered beyond already documented flags/locals in 6698e30.md). BGFX_MAP/RENDER_CHECKLIST not edited.
- Remaining for full 0x6698e30 closure (from prior notes): packet-field copies 0x669c35f..0x669c8f9 byte-level detail, shared_ptr bookkeeping 0x669bd5d..0x669c2a6, some pass-kind tails around 0x669ba27..0x669bd5d fully expanded, callee bodies not reversed.
- Resume: re-run `python tools/sigs/disrange.py 669be56 669bef8` if needed; full function dump at `%TEMP%\\ih.asm`.

## Tooling used
- `python tools/sigs/disrange.py 669be56 669bef8` [V]
- `python tools/sigs/disrange.py 6698e30 669edE4 > %TEMP%\\ih.asm` [V] (PowerShell redirect)
- Source refs: `docs/functions/6698e30.md` (existing), `docs/progress/re_m1d_clones.md` [V]

## Evidence tags
- [V] verified from disassembly (62.01 exe) via disrange/disasm output.
- [I] inferred from nearby code/context in 6698e30.md phase 3 notes.
- [?] unknown/unclear.

---

## D-tree leaf mapping: 0x669be56..0x669bef8 (D2-style) [V disasm]

Context (from `docs/functions/6698e30.md` phase 3 + this range): this block is reached in the pass-kind decision area for `ItemInHand` extractor `0x6698e30` (tag 6). Registers/locals of interest in this snippet: `r8` points to `ItemInHandDescription` (per dossier/6dz); `rbp` locals are draw-record/state flags/copies built in the extractor frame.

| RVA range | Leaf / label (synthetic) | Tests / conditions (actors/fields) | Sets / effects | Notes / jumps |
|---|---|---|---|---|
| `0x669be56`–`0x669be65` | L1: init flag `rbp+0x19a9` | `cmp byte [rbp+0x19a9], 0`; if not zero skip set | if zero sets `byte [rbp+0x19a9] = 1` | Local “seen/init” latch [V]. |
| `0x669be66`–`0x669be70` | L2: branch on description flag `d78 & 0x20` | `test byte [r8+0x78], 0x20` (r8 = desc, desc+0x78 is `d78` per 6698e30 notes) [V] | — | `jne 0x669ca19` → early/alternate tail outside this range [V]. If taken, control leaves this mapped block. |
| `0x669be71`–`0x669be87` | L3: init flag `rbp+0x18c9` + jump | `cmp byte [rbp+0x18c9], 0`; `jne 0x669ca29`; else `mov byte [rbp+0x18c9], 1; jmp 0x669ca29` | sets `rbp+0x18c9 = 1` when clear | Falls into shared tail `0x669ca29` (kind/mask selection tail referenced in phase 3) [I/V by target]. |
| `0x669be8a`–`0x669be97` | L4: set kind2/mask0x8800 | (after L2-not-taken path context in surrounding code) sets `r14b = 2`, `si = 0x8800` [V] | pass kind = 2, state mask = 0x8800 | Matches `docs/functions/6698e30.md` phase 3: “d78&0x20 -> kind 2 / mask 0x8800 (0x669be8a)…” [I]. |
| `0x669be91`–`0x669bea5` | L5: gate to secondary geometry path | `cmp byte [rbp+0x1991], 0`; if `jne 0x669bd5d`; else sets `rbp+0x1991 = 1; jmp 0x669bd5d` | sets `rbp+0x1991 = 1` when clear | Jumps to `0x669bd5d` (secondary geometry / F region per phase 3) [I/V]. |
| `0x669beaa`–`0x669becd` | L6: copy/select from desc floats + local flag `rbp+0x1a0c` | `cmp eax, 2; setae dl; or dl,cl` (uses prior regs eax/cl/dl context) [V]; `movsd xmm0, qword ptr [r8+0x6c]`; `movss xmm1, dword ptr [r8+0x68]`; loads `al = byte [rbp+0x1a0c]`; stores `xmm1 -> dword [rbp+0x1a00]` | writes `rbp+0x1a00` (float from desc+0x68) and prepares `xmm0` from desc+0x6C (qword moved) | `r8+0x68/+0x6C` correspond to vec2/float fields referenced in phase 3 (“copy desc+0x68…” in E/packet areas) [I]. |
| `0x669becd`–`0x669bee8` | L7: conditional set of `rbp+0x1a0c` and store qword pair | `test dl,1; je 0x669cad5`; `test al,al; jne 0x669bee1`; if clear sets `byte [rbp+0x1a0c]=1`; then `movlps qword ptr [rbp+0x1a04], xmm0` | may set `rbp+0x1a0c`; writes `rbp+0x1a04..+0x0B?` from `xmm0` (low 64 bits) | `je 0x669cad5` branches to tail outside range [V]. |
| `0x669bee8`–`0x669bef7` | L8: init flag `rbp+0x19b9` | `cmp byte [rbp+0x19b9], 0`; `jne 0x669bef8`; else `mov byte [rbp+0x19b9], 1` | sets `rbp+0x19b9 = 1` when clear | Falls through to `0x669bef8` (referenced in phase 3 as “kind 0 / mask 0x8000 (0x669bef8) with ctx70>=2”) [I/V]. |

**Summary (range 0x669be56..0x669bef8):** this is a small decision/flag-init + float-copy stub inside the ItemInHand pass-kind tree. It (a) sets/latches several local frame flags (`0x19a9`, `0x18c9`, `0x1991`, `0x1a0c`, `0x19b9`), (b) checks `desc.d78 & 0x20` to branch to `0x669ca19`, (c) sets kind/mask to **kind 2, mask 0x8800** in the L4 path and routes to `0x669bd5d` (secondary geometry), and (d) copies `desc+0x68/+0x6C` into locals (`rbp+0x1a00`, `rbp+0x1a04`) under a computed condition, then proceeds to `0x669bef8` (default/kind-0 path noted in phase 3). No return values from this subrange except control flow into adjacent tails; it primarily sets locals and selects the next block. [V]

---

## FULL PROPOSED BGFX_MAP ENTRY TEXT (bottom of this file; entry IDs TBD)

```text
### 6dz (M1d, additive note) — ItemInHand extractor 0x6698e30 D-tree leaves 0x669be56..0x669bef8 [V]
- Range 0x669be56..0x669bef8 (disasm via tools/sigs/disrange.py): flag inits/latches at rbp+0x19a9, rbp+0x18c9, rbp+0x1991, rbp+0x1a0c, rbp+0x19b9; tests desc.d78 (r8+0x78) bit 0x20 -> branch to 0x669ca19 (tail). L4 sets r14b=2, si=0x8800 (kind 2/mask 0x8800) and jumps to 0x669bd5d (secondary geometry path). L6–L8 copies desc+0x68 (float) -> rbp+0x1a00, desc+0x6C (qword) -> rbp+0x1a04 under conditions (uses dl/al from prior computes), then proceeds to 0x669bef8 (kind 0/mask 0x8000 tail noted in phase 3 context). Full mapping in docs/progress/re_m1d_ih_dtree.md and docs/functions/0x6698e30.md.
- Evidence: [V] static disassembly 62.01; [I] cross-referenced to docs/functions/6698e30.md phase 3 labels.
```