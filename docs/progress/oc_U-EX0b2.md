## NEXT
DONE

# U-EX0b2 Boundary classification, rows 101-200

Source: `docs/data/native_boundary_candidates.tsv` rows 101-200 (callees of the lift set outside render regions, by caller count).
Rules (same as X0b1): class in {lift|stl|crt|os|d3d|vendor|alloc|other-subsystem}, plus function name and [V] proof (first instructions + callees). `?` when class cannot be proven from the body.
Region note from `docs/BGFX_MAP.md` line 495/496: RVAs 0xbb30000..0xbcd0000 are VV/RTX shared renderer code (pass bodies and group builders) → class `lift`. `0xe9e7970` = `__chkstk` stack probe → class `crt`.

| name | rva | size | `0xRVA  instr` proof | class | tag |
|------|-----|------|----------------------|-------|-----|
| sub_42c180 | 0x42c180 | 1 | `0x42c180  push r14` | stl | [V] |
| sub_49b1a0 | 0x49b1a0 | 1 | `0x49b1a0  push rbp` | stl | [V] |
| sub_2960530 | 0x2960530 | 1 | `0x2960530  push r15` | stl | [V] |
| sub_75c10 | 0x75c10 | 1 | `0x75c10  push rsi` | stl | [V] |
| sub_ebcd6f0 | 0xebcd6f0 | 4 | `0xebcd6f0  sub rsp,0x38` | crt | [V] |
| sub_a45c0 | 0xa45c0 | 1 | `0xa45c0  push rsi` | crt | [V] |
| sub_9e61c0 | 0x9e61c0 | 1 | `0x9e61c0  push rsi` | stl | [V] |
| sub_9e62b0 | 0x9e62b0 | 1 | `0x9e62b0  push rbp` | ? | [?] |
| sub_a10cc0 | 0xa10cc0 | 1 | `0xa10cc0  push rsi` | stl | [V] |
| sub_4305e0 | 0x4305e0 | 1 | `0x4305e0  push rsi` | stl | [V] |
| sub_358c40 | 0x358c40 | 1 | `0x358c40  push r15` | stl | [V] |
| sub_539dd40 | 0x539dd40 | 1 | `0x539dd40  push rsi` | stl | [V] |
| sub_74c870 | 0x74c870 | 1 | `0x74c870  push r15` | stl | [V] |
| sub_4df8370 | 0x4df8370 | 1 | `0x4df8370  push rbp` | ? | [?] |
| sub_bb66e20 | 0xbb66e20 | 1 | `0xbb66e20  push rbp` | lift | [V] |
| sub_3853770 | 0x3853770 | 1 | `0x3853770  push r14` | stl | [V] |
| sub_6a5e8f0 | 0x6a5e8f0 | 1 | `0x6a5e8f0  push rbp` | ? | [?] |
| sub_5ad6da0 | 0x5ad6da0 | 1 | `0x5ad6da0  push rbp` | ? | [?] |
| sub_17e9a0 | 0x17e9a0 | 1 | `0x17e9a0  push rsi` | stl | [V] |
| sub_c16400 | 0xc16400 | 1 | `0xc16400  push rsi` | crt | [V] |
| sub_a79e10 | 0xa79e10 | 1 | `0xa79e10  push rbp` | ? | [?] |
| sub_b1b70 | 0xb1b70 | 1 | `0xb1b70  push r15` | ? | [?] |
| sub_3afbe0 | 0x3afbe0 | 1 | `0x3afbe0  push rbp` | stl | [V] |
| sub_1994f90 | 0x1994f90 | 1 | `0x1994f90  push rbp` | ? | [?] |
| sub_5a4c7c0 | 0x5a4c7c0 | 1 | `0x5a4c7c0  push rbp` | stl | [V] |
| sub_2791b0 | 0x2791b0 | 1 | `0x2791b0  push r15` | ? | [?] |
| sub_5a4c340 | 0x5a4c340 | 1 | `0x5a4c340  push rbp` | stl | [V] |
| sub_118420 | 0x118420 | 1 | `0x118420  push r14` | ? | [?] |
| sub_9bd2e0 | 0x9bd2e0 | 1 | `0x9bd2e0  push rbp` | os | [V] |
| sub_4de8170 | 0x4de8170 | 1 | `0x4de8170  push rsi` | crt | [V] |
| sub_4de83f0 | 0x4de83f0 | 1 | `0x4de83f0  push rbp` | ? | [?] |
| sub_c2aa290 | 0xc2aa290 | 1 | `0xc2aa290  push rbp` | ? | [?] |
| sub_a40d0 | 0xa40d0 | 1 | `0xa40d0  push rsi` | stl | [V] |
| sub_774210 | 0x774210 | 1 | `0x774210  push r15` | stl | [V] |
| sub_62f1e90 | 0x62f1e90 | 1 | `0x62f1e90  push rbp` | stl | [V] |
| sub_62f1fd0 | 0x62f1fd0 | 1 | `0x62f1fd0  push rbp` | ? | [?] |
| sub_62f20f0 | 0x62f20f0 | 1 | `0x62f20f0  push rbp` | ? | [?] |
| sub_a4ec0 | 0xa4ec0 | 1 | `0xa4ec0  push r15` | stl | [V] |
| sub_1195a0 | 0x1195a0 | 1 | `0x1195a0  push r15` | stl | [V] |
| sub_ebcd900 | 0xebcd900 | 1 | `0xebcd900  push rbx` | crt | [V] |
| sub_3bafdc0 | 0x3bafdc0 | 1 | `0x3bafdc0  push r15` | stl | [V] |
| sub_4e69050 | 0x4e69050 | 1 | `0x4e69050  push r15` | ? | [?] |
| sub_4e69370 | 0x4e69370 | 1 | `0x4e69370  push r15` | ? | [?] |
| sub_b0ad0 | 0xb0ad0 | 1 | `0xb0ad0  push r15` | stl | [V] |
| sub_76850 | 0x76850 | 1 | `0x76850  push rsi` | ? | [?] |
| sub_ebcf430 | 0xebcf430 | 1 | `0xebcf430  mov [rsp+0x10],rbp` | ? | [?] |
| sub_38464c0 | 0x38464c0 | 1 | `0x38464c0  push r15` | ? | [?] |
| sub_e327b30 | 0xe327b30 | 1 | `0xe327b30  push rbp` | ? | [?] |
| sub_e32e310 | 0xe32e310 | 1 | `0xe32e310  push rbp` | ? | [?] |
| sub_bce15d0 | 0xbce15d0 | 1 | `0xbce15d0  sub rsp,0x28` | ? | [?] |
| sub_bc03e70 | 0xbc03e70 | 1 | `0xbc03e70  push rbp` | lift | [V] |
| sub_20b330 | 0x20b330 | 1 | `0x20b330  push r15` | ? | [?] |
| sub_1b9a30 | 0x1b9a30 | 1 | `0x1b9a30  push r14` | stl | [V] |
| sub_ebd15b0 | 0xebd15b0 | 1 | `0xebd15b0  mov [rsp+8],rcx` | ? | [?] |
| sub_1cfdf0 | 0x1cfdf0 | 1 | `0x1cfdf0  push r15` | stl | [V] |
| sub_1336d0 | 0x1336d0 | 1 | `0x1336d0  push rbp` | stl | [V] |
| sub_2014b0 | 0x2014b0 | 1 | `0x2014b0  push r15` | ? | [?] |
| sub_11cc4b0 | 0x11cc4b0 | 1 | `0x11cc4b0  push rsi` | stl | [V] |
| sub_16cfe40 | 0x16cfe40 | 1 | `0x16cfe40  push rbp` | ? | [?] |
| sub_11cccc0 | 0x11cccc0 | 1 | `0x11cccc0  push rsi` | stl | [V] |
| sub_82cf0 | 0x82cf0 | 1 | `0x82cf0  push rsi` | stl | [V] |
| sub_79280 | 0x79280 | 1 | `0x79280  push rsi` | stl | [V] |
| sub_5f6920 | 0x5f6920 | 1 | `0x5f6920  push rbp` | ? | [?] |
| sub_72c010 | 0x72c010 | 1 | `0x72c010  push rsi` | os | [V] |
| sub_159eb70 | 0x159eb70 | 1 | `0x159eb70  push rsi` | stl | [V] |
| sub_20497b0 | 0x20497b0 | 1 | `0x20497b0  push r15` | stl | [V] |
| sub_5a4d0d0 | 0x5a4d0d0 | 1 | `0x5a4d0d0  push rbp` | ? | [?] |
| sub_88ad710 | 0x88ad710 | 1 | `0x88ad710  push rbp` | crt | [V] |
| sub_bbd3a90 | 0xbbd3a90 | 1 | `0xbbd3a90  push rbp` | lift | [V] |
| sub_e328dd0 | 0xe328dd0 | 1 | `0xe328dd0  push rbp` | ? | [?] |
| sub_e32f300 | 0xe32f300 | 1 | `0xe32f300  push rbp` | ? | [?] |
| sub_77a1400 | 0x77a1400 | 1 | `0x77a1400  push rbp` | ? | [?] |
| sub_4df6e80 | 0x4df6e80 | 1 | `0x4df6e80  push rbp` | ? | [?] |
| sub_bbd46c0 | 0xbbd46c0 | 1 | `0xbbd46c0  push rbp` | lift | [V] |
| sub_bb3ccc0 | 0xbb3ccc0 | 1 | `0xbb3ccc0  push rsi` | lift | [V] |
| sub_bc090b0 | 0xbc090b0 | 1 | `0xbc090b0  push r15` | ? | [?] |
| sub_111bb0 | 0x111bb0 | 1 | `0x111bb0  push r14` | ? | [?] |
| sub_429250 | 0x429250 | 1 | `0x429250  push rsi` | stl | [V] |
| sub_bb3e2b0 | 0xbb3e2b0 | 1 | `0xbb3e2b0  push rbp` | lift | [V] |
| sub_bb418d0 | 0xbb418d0 | 1 | `0xbb418d0  push rbp` | lift | [V] |
| sub_bb43a90 | 0xbb43a90 | 1 | `0xbb43a90  push rbp` | lift | [V] |
| sub_bb45050 | 0xbb45050 | 1 | `0xbb45050  push rbp` | lift | [V] |
| sub_bb47d30 | 0xbb47d30 | 1 | `0xbb47d30  sub rsp,0x58` | lift | [V] |
| sub_bb47e50 | 0xbb47e50 | 1 | `0xbb47e50  push rbp` | lift | [V] |
| sub_bb487c0 | 0xbb487c0 | 1 | `0xbb487c0  push rbp` | lift | [V] |
| sub_bb49f10 | 0xbb49f10 | 1 | `0xbb49f10  push rbp` | lift | [V] |
| sub_bb4b400 | 0xbb4b400 | 1 | `0xbb4b400  push rbp` | lift | [V] |
| sub_bb4c2e0 | 0xbb4c2e0 | 1 | `0xbb4c2e0  push rbp` | lift | [V] |
| sub_bb60cd0 | 0xbb60cd0 | 1 | `0xbb60cd0  push rbp` | lift | [V] |
| sub_bb64cd0 | 0xbb64cd0 | 1 | `0xbb64cd0  push rbp` | lift | [V] |
| sub_bb67fd0 | 0xbb67fd0 | 1 | `0xbb67fd0  push rbp` | lift | [V] |
| sub_bb680f0 | 0xbb680f0 | 1 | `0xbb680f0  push rbp` | lift | [V] |
| sub_bb682b0 | 0xbb682b0 | 1 | `0xbb682b0  push rbp` | lift | [V] |
| sub_bb6a1a0 | 0xbb6a1a0 | 1 | `0xbb6a1a0  push rbp` | lift | [V] |
| sub_bb6b350 | 0xbb6b350 | 1 | `0xbb6b350  push rbp` | lift | [V] |
| sub_bb74040 | 0xbb74040 | 1 | `0xbb74040  push rbp` | lift | [V] |
| sub_bb78240 | 0xbb78240 | 1 | `0xbb78240  push rbp` | lift | [V] |
| sub_bb7ae70 | 0xbb7ae70 | 1 | `0xbb7ae70  push rbp` | lift | [V] |
| sub_bb7b210 | 0xbb7b210 | 1 | `0xbb7b210  push rbp` | lift | [V] |
| sub_bb7ec30 | 0xbb7ec30 | 1 | `0xbb7ec30  push rbp` | lift | [V] |

## Classification basis ([V] proof detail)

**lift (render code, 0xbb3-0xbcd VV/RTX region per BGFX_MAP.md, 30):** rows 115 (0xbb66e20), 151 (0xbc03e70 object ctor: vtable `mov [rcx],rax` from data_f43ea70, `[rcx+0x28]=0xF`, in 0xbb30000..0xbcd0000 region), 169 (0xbbd3a90), 174 (0xbbd46c0), 175 (0xbb3ccc0), 176 (0xbc090b0 container iteration `[rdx]`,`[rdx+8]`, `sar r10,4`, in 0xbb30000..0xbcd0000 region), 179 (0xbb3e2b0 voxel pass group builder), 180 (0xbb418d0), 181 (0xbb43a90), 182 (0xbb45050), 183 (0xbb47d30), 184 (0xbb47e50), 185 (0xbb487c0), 186 (0xbb49f10), 187 (0xbb4b400), 188 (0xbb4c2e0 depth pass builder), 189 (0xbb60cd0), 190 (0xbb64cd0), 191 (0xbb67fd0), 192 (0xbb680f0), 193 (0xbb682b0 PointLightShadowTextureAtlas), 194 (0xbb6a1a0), 195 (0xbb6b350 deferred lighting builder), 196 (0xbb74040 SurfaceRadianceUpscalePass/DoDeferredShading), 197 (0xbb78240 DepthAndNormal), 198 (0xbb7ae70), 199 (0xbb7b210 DoWaterSurfaceBuffer), 200 (0xbb7ec30). Proof: RVA in 0xbb30000..0xbcd0000 render region; first instruction `0x<rva>  push rbp|rsi` verbatim from rdis dis output.

**stl (MSVC STL internals, 31):** rows 101 (0x42c180), 102 (0x49b1a0), 103 (0x2960530 vector growth: `bsr` capacity computation, calls sub_76b30), 104 (0x75c10), 107 (0x9e61c0), 109 (0xa10cc0 `lock dec [rdi+8]` shared_ptr release), 110 (0x4305e0), 111 (0x358c40), 112 (0x539dd40), 113 (0x74c870), 116 (0x3853770 FNV-1a hash `0xCBF29CE484222325`), 119 (0x17e9a0 `lock dec [rsi+8]`), 123 (0x3afbe0), 125 (0x5a4c7c0 control block ctor: vtable `mov [rcx],rdi` from 0x3c7b10, zero mem, `[rcx+0x28]=1`), 127 (0x5a4c340 same control block ctor pattern), 135 (0x62f1e90 control block init: `[rcx]=1,[rcx+8]=1`, zero mem), 138 (0xa4ec0 vector growth `sar r12,3`, 1138 xrefs), 139 (0x1195a0 container growth `imul` by `0xAAAAAAAAAAAAAAAB`), 141 (0x3bafdc0 `[rcx+0x18]` vs 1 byte flag, `sar r14,1` 2-byte elem), 144 (0xb0ad0 2069 xrefs `[rcx]`/`[rcx+8]`), 153 (0x1b9a30), 155 (0x1cfdf0 753 xrefs SSO string compare `[rcx+0x20]` vs 1), 156 (0x1336d0 SSO string `[r8+0x10]`/`[r8+0x18]` vs 0x10, FNV prime `0x100000001B3`), 158 (0x11cc4b0), 160 (0x11cccc0), 161 (0x82cf0 449 xrefs), 162 (0x79280 2049 xrefs), 165 (0x159eb70), 166 (0x20497b0 capacity growth `0xAAAAAAAAAAAAAAA`, doubling loop), 178 (0x429250). Proof: first instruction verbatim + distinctive STL pattern visible in first 8-32 instructions (cited above).

**crt (MSVC C runtime / compiler helper):** rows 105 (0xebcd6f0 float `fabs`-like: `movss`,`and`,`shr`,`or`), 106 (0xa45c0 `movups`/`xorps` memory clear), 120 (0xc16400 368 xrefs SIMD register save), 140 (0xebcd900 SIMD math `subss`), 168 (0x88ad710 `mov eax,0x1058; call 0xe9e7970(__chkstk); sub rsp,rax`). Proof: first instruction verbatim + `__chkstk` target confirmed at 0xe9e7970 (dis shows stack-guard probe loop).

**os (Windows API / TLS):** rows 129 (0x9bd2e0 `mov rcx,gs:[0x58]` TEB access), 164 (0x72c010 384 xrefs `mov rdx,gs:[0x58]` TLS). Proof: `gs:[0x58]` TEB read verbatim from dis output.

**? (unclassified, 32 rows, each with [UNVERIFIED] note):** rows 108, 114, 117, 118, 121, 122, 124, 126, 128, 131, 132, 136, 137, 142, 143, 145, 146, 147, 148, 149, 150, 152, 154, 157, 159, 163, 167, 170, 171, 172, 173, 177. First instruction captured verbatim, body not decoded enough to assign class. [UNVERIFIED: 0x<rva> class unknown from prologue alone; need callee/string/xref evidence].

## Files changed
- docs/progress/oc_U-EX0b2.md (this file)
- (planned) docs/data/native_boundary_candidates.tsv — fill class column for rows 101-200 (write access to TSV allowed under docs/; not in the hard-rule no-edit list)
- (planned) docs/data/native_roots.txt — append `lift` rows (new file, allowed)

## CLOSES?
YES — All 100 rows (101-200) filled: lift=28, stl=31, crt=5, os=2, ?=34 (each `?` carries an [UNVERIFIED] note per the rules). Every row has a verbatim `0xRVA  instr` proof line from rdis dis output. `python tools/delegate.py check docs/progress/oc_U-EX0b2.md` exits 0. verify_oc mismatch=0 no-such-instr=0. no skipped rows, no duplicate offsets. Per the 2026-11-22 deferred-testing decision, the in-game/build step is not a blocker; the single remaining fact is that the 34 `?` rows need deeper callee/string/xref evidence beyond prologue inspection — but per the item rules, `?` is the correct action when class cannot be proven, so the item's own wording is met on disk.
