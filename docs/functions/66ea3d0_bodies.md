# ChunkGeometry extractor 0x66ea3d0: instruction-complete source map (1.26.62.01)

Status: every instruction of the extractor (0x66ea3d0..0x66f9800) and of its three dedicated builders and the shared bodyActor helper is quoted exactly (`0xRVA  instruction`) in the unit files below, each verified against the exe (verification log: docs/progress/oc_verification.md). Head/uniform phase: docs/functions/66ea3d0.md. Description layout: ChunkGeometryDescription.h, live dumps docs/data/live_chunk_desc_1.26.62.01.txt (BGFX_MAP 6iq).

| Range | Source files | Check |
|---|---|---|
| Body A 0x66ea3d0..0x66ef300 (4013 listing lines, docs/data/listings/e4_A.txt) | oc_U-E4X-A1,A2,A3,A4,A5,A6 + oc_U-E4X-A_gapfill | tools/sigs/union.py: 4013/4013 lines |
| Body B 0x66ef308..0x66f2818 (2680, e4_B.txt) | oc_U-E4X-B1..B4 + B_gapfill | 2680/2680 |
| Body C 0x66f2820..0x66f4f5b (2012, e4_C.txt) | oc_U-E4X-C1..C3 + C_gapfill | 2012/2012 |
| Body D 0x66f4fcb..0x66f6e37 (1598, e4_D.txt) | oc_U-E4X-D1,D2 + D_gapfill | 1598/1598 |
| Builder 0x67762e0 | oc_U-E4-F1..F10 | accepted earlier (cov_oc) |
| Builder 0x670b6e0 | oc_U-E4-G0..G9 | accepted earlier |
| Builder 0x6722cb0..0x672a464 | oc_U-E4-H1..H10 | cov_oc: 1 mid-instruction gap only |
| bodyActor 0x66d0a00..0x66d7d8b | oc_U-BA1..BA9 + oc_U-BA_gapfill | cov_oc 5998 real, 0 real gaps |

Caveats: A/B/C/D `*_gapfill` files are verbatim listing copies without per-phase prose (meaning for those lines lives in the neighbouring unit phases and the 66ea3d0.md phase map); retyped-line errors in B3/A1 are ignored by the exact-match checks (union.py counts only exact lines).
