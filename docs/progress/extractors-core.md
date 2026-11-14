# Progress: extractors-core (E2/L5e BatchActor builders, E4/L5g chunk extractor, E7/L5k, H4/L9f)

## NEXT
Unit in progress: E2/L5e helpers 0x66d9710 / 0x66c11b0 / 0x66a0f60 / 0x66c17e0 (read-only disassembly, `python tools/sigs/disrange.py <lo> <hi>`), then write docs/functions/66d9af0_builders.md (D2 dossier) + header src/sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorBuilders.h.
Scratch (regenerable): $TEMP/ec/{a..j}.asm = builders (a=66bf290 b=66c1920 c=66c3840 d=66ce8d0 e=66c5760 f=66cc7a0 g=66c7680 h=66c98e0 i=66bb7b0 j=66bd430), diffb.py = rip-normalising diff.
Then: E4 chunk extractor (0x66ea3d0 bodies A..D), E7, H4 (all still OPEN, see entries).

---

### E2 / L5e - IN PROGRESS (pairing CONFIRMED, builder family decoded; entry below is partial until the dossier is written)
Pairing, confirmed by following the jump targets in 0x66d9af0 (disasm 0x66e0f08..0x66e2217) [V]. CONTRADICTS docs/functions/66d9af0.md phase 5 table (that table labelled the second-level branches wrongly). P = material pass record [rbp+0x718], P50 = byte P+0x50, P51 = byte P+0x51, F = byte [rbp+0x7c8], edi = (instance count != 0), C = (bl | ((r13d>>12)&1)) (bl = running AND of two earlier flags):
| builder | call site | condition [V] |
|---|---|---|
| 0x66bf290 | 0x66e1406 | P50==1, F==0, edi!=0, P51==1 |
| 0x66c1920 | 0x66e1aea | P50==1, F==0, edi!=0, P51!=1 |
| 0x66c3840 | 0x66e1a38 | P50==1, F==0, edi==0, P51==1 |
| 0x66c5760 | 0x66e1c4e | P50==1, F==0, edi==0, P51!=1 |
| 0x66bb7b0 (+0x66a65b0) | 0x66e20cf | P50==2, F==0, edi!=0 (via variant-copy table 0xf2bfb30, case target 0x66e2022) |
| 0x66bd430 | 0x66e21b3 | P50==2, F==0, edi==0 (via table 0xf2bfb20, case target 0x66e2106) |
| 0x66c7680 | 0x66e1e65 | P50 not in {1,2}, C==1, P51==1 (after 0x67743c0) |
| 0x66c98e0 | 0x66e1f42 | P50 not in {1,2}, C==1, P51!=1 (after 0x67743c0) |
| 0x66cc7a0 | 0x66e1770 | P50 not in {1,2}, C!=1, F==0, P51==1 |
| 0x66ce8d0 | 0x66e1b9c | P50 not in {1,2}, C!=1, F==0, P51!=1 |
Case P50 not in {1,2}, C!=1, F!=0 (0x66e157d) calls 0x66cc400 / 0x66cba10 / 0x66cc660 directly (no builder). F!=0 with P50 in {1,2} skips to the loop tail 0x66e1f58 (no draw).
Common call shape of every builder [V]: build(rcx = per-frame ctx [rbp+0x7b0], rdx = &{u64 count (=(end-begin)/0x30 of builder+0x480/+0x488), const T* begin}, r8 = [rbp+0x778], r9 = &vec3 copy of P+0x30..0x3B, stack5 = &DrawItem prototype (built by 0x66c11b0 at rbp+0x4a0), stack6 = float distance*scale (xmm8)). Pre-calls per site: 0x66d9710(&ctx3c8,&rec110) then 0x66c11b0(&rec4a0,&rec110); post-call 0x66c17e0(&rec4a0) (destroy).
