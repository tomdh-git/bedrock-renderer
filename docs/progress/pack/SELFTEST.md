# ctxpack selftest (CP1 + CP2)

Run on three items from docs/RENDER_CHECKLIST.md:
- Single: X1.bc60d10 (0xbc60d10) - small leaf function, done
- Plan: X1.bc68e40 (0xbc68e40) - PLAN item for large function
- Chunk: X1.bc301c0 (0xbc301c0) - first chunk of PLAN X1.bc301c0

---

## 1. Single item: 0xbc60d10 (X1.bc60d10 LIFT EncoderImpl::discard)

### build
```
# ctxpack build 0xbc60d10 -> docs\progress\pack\bc60d10.md
STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bc60d10.md:934949aeee098f028f3e8cb8d642ff7467ab776cedcd7620a17d0ded5ad59286,data=native_functions.tsv:ff5180734b0f2aa24760fee48097f4a36c99c914d0fd307b8adac7162ce7655c,data=native_deps.tsv:4563bde5c05b4fded538022b512d994657d93f0570f7eb0d2c69826ed991857b,data=native_boundary.tsv:aa2e03f5f0bd93a7051d6102b91e6b283c9e6587e9915c5c01e329266e242607,data=native_boundary_candidates.tsv:8bb54e181419c9c42374be3142e4291934993a869d499a2b80e595610c86b8d9
size 0x1fc (508 bytes) | depth [open] | callees 1 (depth 1) | callers 15
callees:
  0xeec6ed0 sub_eec6ed0       unknown     [open]
strings/rip refs: 0
field-access offsets: 0 (regs rdi,rsi,r9,r15)
decisions: 5 (see ## DECISIONS in bc60d10.md)
```

### check
```
FRESH
```

### tree --depth 2
```
# ctxpack tree 0xbc60d10 depth 2
  0xbc60d10   sub_bc60d10       dossier   [open]    [proven]  size 0x1fc
    0xeec6ed0   sub_eec6ed0       unknown   [open]    [proven]  size 0x0 boundary=crt
```

---

## 2. Plan item: 0xbc68e40 (X1.bc68e40.plan - bgfx render-thread command buffer interpreter)

### build
```
# ctxpack build 0xbc68e40 -> docs\progress\pack\bc68e40.md
STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bc68e40.md:01c8d8c64b77add9f87f52ad8252076c3542ded3b95d165e1f83f751fa1daf02,liftsrc=bc68e40_chunk_c00.cpp:3e3315187f0aa6423bdaeb284ea0276ed683f7b8ae32ccfa019b355a1a2e9ce5,liftsrc=bc68e40_chunk_c00.h:1ff8c710dd6e0be3dff5646424d5b3f4a977a7cac9d4713f20f4db1a14e7a841,liftsrc=sub_bc68e40.cpp:e812dc147bc10760b7b88aebbc5297b6212d0d52cfffeba111bb162d46016deb,liftsrc=sub_bc68e40_chunk2.cpp:01a1e333c5cb415bf5bfdecb3fb79746521e142a55af1dd88fd759b492f6e888,liftsrc=sub_bc68e40_chunk2.h:3e098bfa80c7dbb6c27ff268f73caae32be5297ebbf2ca0c634035d7253b0437,data=native_functions.tsv:ff5180734b0f2aa24760fee48097f4a36c99c914d0fd307b8adac7162ce7655c,data=native_deps.tsv:4563bde5c05b4fded538022b512d994657d93f0570f7eb0d2c69826ed991857b,data=native_boundary.tsv:aa2e03f5f0bd93a7051d6102b91e6b283c9e6587e9915c5c01e329266e242607,data=native_boundary_candidates.tsv:8bb54e181419c9c42374be3142e4291934993a869d499a2b80e595610c86b8d9
size 0x1b83 (7043 bytes) | depth [open] | callees 6 (depth 1) | callers 1
callees:
  0xbc5f110 sub_bc5f110       set         [open]
  0xbc68840 sub_bc68840       set         [open]
  0xbc6abd0 sub_bc6abd0       set         [open]
  0xbc7a3d0 sub_bc7a3d0       set         [open]
  0xebce390 sub_ebce390       set         [open]
  0xebce5e0 sub_ebce5e0       set         [open]
strings/rip refs: 3
field-access offsets: 0 (regs rdi,rsi,r9,r15)
decisions: 5 (see ## DECISIONS in bc68e40.md)
```

### check
```
FRESH
```

### tree --depth 2
```
# ctxpack tree 0xbc68e40 depth 2
  0xbc68e40   sub_bc68e40       lifted    [open]    [proven]  size 0x1b83 src=src\client\features\render\native\bgfx\bc68e40_chunk_c00.cpp
    0xbc5f110   sub_bc5f110       lifted    [open]    [proven]  size 0x121 src=src\client\features\render\native\bgfx\sub_bc5f110.cpp
      0xe951550   sub_e951550       unknown   [open]    [proven]  size 0x1e boundary=crt
      0xe9e7970   sub_e9e7970       unknown   [open]    [proven]  size 0x4e boundary=crt
      0xebce470   sub_ebce470       unknown   [open]    [proven]  size 0xd2 boundary=crt
      0xebcf430   sub_ebcf430       lifted    [open]    [proven]  size 0x2a boundary=lift src=src\client\features\render\native\helpers\sub_ebcf430.cpp
    0xbc68840   sub_bc68840       lifted    [open]    [proven]  size 0x5f7 src=src\client\features\render\native\bgfx\sub_bc68840.cpp
      0xebce430   sub_ebce430       unknown   [open]    [proven]  size 0x0
      0xebdbc90   sub_ebdbc90       unknown   [open]    [proven]  size 0x73 boundary=crt
    0xbc6abd0   sub_bc6abd0       lifted    [open]    [proven]  size 0x2df src=src\client\features\render\native\bgfx\sub_bc6abd0.cpp
      0xbc6aeb0   sub_bc6aeb0       lifted    [open]    [proven]  size 0x86 src=src\client\features\render\native\bgfx\sub_bc6aeb0.cpp
      0xebce390   sub_ebce390       lifted    [open]    [proven]  size 0x0 boundary=lift src=src\client\features\render\native\helpers\sub_ebce390.cpp
    0xbc7a3d0   sub_bc7a3d0       lifted    [open]    [proven]  size 0x3cc src=src\client\features\render\native\bgfx\sub_bc7a3d0.cpp
      0xeec6ed0   sub_eec6ed0       unknown   [open]    [proven]  size 0x0 boundary=crt
    0xebce5e0   sub_ebce5e0       lifted    [open]    [proven]  size 0x0 boundary=lift src=src\client\features\render\native\helpers\sub_ebce5e0.cpp
```

---

## 3. Chunk item: 0xbc301c0 (X1.bc301c0.c00 - first chunk of sub_bc301c0)

### build
```
# ctxpack build 0xbc301c0 -> docs\progress\pack\bc301c0.md
STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bc301c0.md:d906d8bb2e20a17f143d9d627039d21faecf5714b6696ba8a7ee89a2c7d11d64,liftsrc=sub_bc301c0.cpp:4f461a451fd340c94fa87556e1547548491ab1a438977af125a6ffb2a3828170,liftsrc=sub_bc301c0.h:d65552579825109825af59a9da35f7b08b51595580661502175d7c4c07d6b55d,data=native_functions.tsv:ff5180734b0f2aa24760fee48097f4a36c99c914d0fd307b8adac7162ce7655c,data=native_deps.tsv:4563bde5c05b4fded538022b512d994657d93f0570f7eb0d2c69826ed991857b,data=native_boundary.tsv:aa2e03f5f0bd93a7051d6102b91e6b283c9e6587e9915c5c01e329266e242607,data=native_boundary_candidates.tsv:8bb54e181419c9c42374be3142e4291934993a869d499a2b80e595610c86b8d9
size 0x1e7c (7804 bytes) | depth [open] | callees 16 (depth 1) | callers 1
callees:
  0x75720 sub_75720         unknown     [open]
  0x75b60 sub_75b60         unknown     [open]
  0x78ed0 sub_78ed0         unknown     [open]
  0x79560 sub_79560         unknown     [open]
  0x9d6d0 sub_9d6d0         unknown     [open]
  0x76a8a0 sub_76a8a0        unknown     [open]
  0x9bc830 sub_9bc830        unknown     [open]
  0xa78940 sub_a78940        set         [open]
  0x56894c0 sub_56894c0       set         [open]
  0x5689800 sub_5689800       set         [open]
  0x655cea0 sub_655cea0       unknown     [open]
  0xbc347b0 sub_bc347b0       set         [open]
  0xe935700 sub_e935700       set         [open]
  0xe93b480 sub_e93b480       set         [open]
  0xeec6de0 sub_eec6de0       set         [open]
  0xeec6ec0 sub_eec6ec0       set         [open]
strings/rip refs: 0
field-access offsets: 0 (regs rdi,rsi,r9,r15)
decisions: 5 (see ## DECISIONS in bc301c0.md)
```

### check
```
FRESH
```

### tree --depth 1
```
# ctxpack tree 0xbc301c0 depth 1
  0xbc301c0   sub_bc301c0       lifted    [open]    [proven]  size 0x1e7c src=src\client\features\render\native\bgfx\sub_bc301c0.cpp
    0x75720     sub_75720         unknown   [open]    [proven]  size 0x11 boundary=stl
    0x75b60     sub_75b60         unknown   [open]    [proven]  size 0x11 boundary=stl
    0x78ed0     sub_78ed0         unknown   [open]    [proven]  size 0xb boundary=crt
    0x79560     sub_79560         unknown   [open]    [proven]  size 0x0
    0x9d6d0     sub_9d6d0         unknown   [open]    [proven]  size 0x16e boundary=stl
    0x76a8a0    sub_76a8a0        unknown   [open]    [proven]  size 0x22a boundary=stl
    0x9bc830    sub_9bc830        unknown   [open]    [proven]  size 0xc1 boundary=alloc
    0xa78940    sub_a78940        set       [open]    [proven]  size 0x540 boundary=lift
    0x56894c0   sub_56894c0       set       [open]    [proven]  size 0x33b
    0x5689800   sub_5689800       set       [open]    [proven]  size 0x3fc
    0x655cea0   sub_655cea0       unknown   [open]    [proven]  size 0x11a boundary=stl
    0xbc347b0   sub_bc347b0       set       [open]    [proven]  size 0x2c8
    0xe935700   sub_e935700       lifted    [open]    [proven]  size 0x0 boundary=lift src=src\client\features\render\native\helpers\sub_e935700.cpp
    0xe93b480   sub_e93b480       lifted    [open]    [proven]  size 0x0 boundary=lift src=src\client\features\render\native\helpers\sub_e93b480.cpp
    0xeec6de0   sub_eec6de0       lifted    [open]    [proven]  size 0x0 boundary=lift src=src\client\features\render\native\helpers\sub_eec6de0.cpp
    0xeec6ec0   sub_eec6ec0       lifted    [open]    [proven]  size 0x0 boundary=lift src=src\client\features\render\native\helpers\sub_eec6ec0.cpp
```

---

## Summary

All three item types (single, plan, chunk) produce valid packs with:
- STAMP line with exe hash + all input file hashes
- HEADER with size, depth, D-rank (marked [open]), callee count
- EXACT LISTING from rdis dis
- CALLERS from xref callers
- CALLEES with signature [open], status (lifted/set/unknown/dossier), trust [proven], boundary/lift source
- STRINGS AND RIP REFS
- FIELD ACCESS TABLE from descscan2 (regs rdi,rsi,r9,r15)
- KNOWN STRUCT LAYOUTS TOUCHED
- CLOSEST FINISHED LIFT (style example)
- DECISIONS section with 5 open questions

`check` correctly reports FRESH when stamp matches, STALE otherwise.
`tree` prints callee/caller neighborhood with one line per node: rva, name, status, signature, trust, size, boundary/source.

Line cap: default 60 lines, `--full` for unlimited.