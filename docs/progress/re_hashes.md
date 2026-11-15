# re_hashes — C5/F5 hash inventory (agent: coder)

## Context
Task: inventory hash/mixer routines in BS_EXE (`Minecraft.Windows.exe` 1.26.62.01) BEYOND the three known:
- HashedString FNV-1a 64 (basis 0xcbf29ce484222325, prime 0x100000001b3; h^=b; h*=prime) [V per BGFX_MAP 6ez/6p]
- pass-name FNV-1 64 (h*=prime; h^=b) + 752 hashes in docs/data/render_hashes.txt [V per 6p]
- MurmurHash2 (m=0x5bd1e995): bind hash +0x514/Encoder+0x654, uniform registry keys [V per 6ah/6cq]

Also already documented (not "new" but relevant): XXH64 0x19932c0 [V per 6u], program-signature hash `*0x1003F ... *0xFC5D1543EC5F01` at 0xe8224c1 [V per 6ao], boost hash_combine `h ^ (x + 0x9e3779b9 + (h<<6) + (h>>2))` at ShaderBuffer content hash 0x5679db0+0x70 [V per 6ca].

Target areas to hunt:
- non-FNV/non-Murmur hash routines
- hash combiners
- sort-key bit packing (Frame::sort 0xbc61220 / 0xc280010 / 0xc280ca0; 6io: sort keys bits 16-61)
- bind-hash grouping (+0x514)
- description hash
- material hash
- asset path hash

Per hash: rdis `dis <rva>` + `path`/`sum`; identify algorithm, constants, output width, callers. D2-style table where feasible. Write docs/functions/<rva>.md per hash. Additive SDK header edits under src (bgfx core header; static_asserts on constants). Optional docs/data/layout_asserts.json additions (unique names).

Deliverable: docs/progress/re_hashes.md (this file) + final report + FULL PROPOSED BGFX_MAP ENTRY TEXT at bottom. Do NOT edit BGFX_MAP.md or RENDER_CHECKLIST.md.

## NEXT
1. Confirm rdis.exe built (tools/rdis/target/release/rdis.exe); if not, `cargo build --release` in tools/rdis.
2. Confirm python + PYTHONUTF8=1; list tools/sigs/*.py and check exe path exists.
3. Disassemble candidate hash RVAs found via constant scanning (0x5bd1e995 Murmur, 0x9e3779b9/0x9e3779b9... combine, 0x1003F/0xFC5D1543EC5F01 PSO, XXH primes) plus a .text scan for mixers.
4. For each new hash: docs/functions/<rva>.md dossier + static_assert + layout_asserts.json entry (unique names).
5. Write final report + proposed BGFX_MAP entry text at bottom of this file.

## DONE / OPEN
- OPEN: rdis build status (not yet checked)
- OPEN: exe path verification
- OPEN: hash candidate enumeration

[V] = verified in disassembly, [I] = inferred, [?] = unknown
