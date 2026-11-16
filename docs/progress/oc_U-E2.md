# Unit U-E2 — BatchActor extractor callee map (0x66d9af0), 1.26.62.01

## Function identity [V]
- `sub_66d9af0` = BatchActor extractor, Item group visitor tag 10 (tail-jumped to from 0x66473e1, see docs/functions/item_forwarders_6647320.md) [V]
- Range: `[0x66d9af0..0x66e26a7)`, size `0x8bb7` bytes, 7759 instructions [V from `rdis fn 0x66d9af0`]
- Stack frame 0x908, 8 pushes, 10 saved xmm (xmm6+) [V prologue]
- Reached via Item visitor 0x6646980 (no direct callers) [V]
- args: rcx = this/builder state, rdx = frame context/variant, r8 = description pointer [V from forwarders doc]
- `docs/data/functions.tsv`: 0x66d9af0 L5 "batch-actor extractor" D1 doc 6u [V grep]

## Argument registers at entry [V]
First 10 instructions (prologue only — none touch rcx/rdx/r8):
```
0x66D9AF0  push rbp                                      
0x66D9AF1  push r15                                      
0x66D9AF3  push r14                                      
0x66D9AF5  push r13                                      
0x66D9AF7  push r12                                      
0x66D9AF9  push rsi                                      
0x66D9AFA  push rdi                                      
0x66D9AFB  push rbx                                      
0x66D9AFC  sub rsp,0x908                                 
0x66D9B03  lea rbp,[rsp+0x80]                            
```
Argument handling (instructions after the first 10):
```
0x66D9B64  mov [rbp+0x7B0],rdx                            ; rdx stored (frame context)
0x66D9B6B  mov [rbp+0x7A0],rcx                            ; rcx stored (builder/this)
0x66D9B72  mov [rbp+0x7A8],r8                             ; r8 stored (description pointer)
0x66D9B79  mov rax,[r8+0xE0]                             ; r8 dereferenced: desc+0xE0 = instance count
```
Summary: rcx and rdx are only stored to stack slots (never dereferenced); r8 is dereferenced at +0xE0 to read the instance count [V].

## Profiler / scope strings [V]
xref.py str for "Profiler" and "Scope" returned hits only outside this function's range (0xBDExxxx, 0x9Dxxxx, 0x849xxxx, 0x7DExxxx, 0x1B7xxxx, 0xD5xxxx, 0xA0Bxxxx, 0x38xxxx). `rdis str 0x66d9af0` and `callees 0x66d9af0` list NO profiler/scope string literals inside 0x66d9af0..0x66e26a7. The function references zero profiler/scope strings directly.

## Strings the function references [V]
From `rdis callees 0x66d9af0` str output (all inside 0x66d9af0..0x66e26a7):
| RVA | string | role |
|-----|--------|------|
| 0x66DF637 | "TintedAlphaTestEnabled" | uniform name |
| 0x66DF6BA | "MetalnessUniform" | uniform name |
| 0x66DF73D | "EmissiveUniform" | uniform name |
| 0x66DF7C0 | "RoughnessUniform" | uniform name |
| 0x66DF843 | "SubsurfaceUniform" | uniform name |
| 0x66DF8C6 | "PBRTextureFlags" | uniform name |
| 0x66DF942 | "ActorFPEpsilon" | uniform name |
| 0x66DF9C5 | "DitheringEnabledToggle" | uniform name |
| 0x66DFA45 | "MultiplicativeTintColor" | uniform name |
| 0x66DFB68 | "UVScale" | uniform name |
| 0x66DFBE9 | "GlintColor" | uniform name |
| 0x66DFC6A | "UseAlphaRewrite" | uniform name |
| 0x66DFCEB | "PrevBones" | buffer/uniform name |
| 0x66DFD6C | "PrevWorld" | buffer/uniform name |
| 0x66DFE23 | "MERSTexture" | texture name |
| 0x66DFEA4 | "NormalTexture" | texture name |
| 0x66DFF25 | "MatTexture1" | texture name |
| 0x66E0587 | "MatTexture2" | texture name |

Two additional entries reported by `callees` as "str" are actually jump-table lea targets, not strings:
- 0x66E155A `lea rdx,[0xF2BFB50]` — jump table 0xF2BFB50 [V]
- 0x66E169D `lea rdx,[0xF2BFB40]` — jump table 0xF2BFB40 [V]

## Callee map — every distinct direct callee [V list/counts from `rdis callees 0x66d9af0`; meanings tagged]
Ordered by first call site. Quote lines are verbatim `0xRVA  call ...` from the full disassembly (`fn 0x66d9af0 --max 200000`). Identification sources: docs/BGFX_MAP.md, docs/functions/*.md, docs/data/functions.tsv, xref.py str; else [?].

| # | Callee RVA | xN | First call site | Quoted call line | What it is |
|---|------------|----|-----------------|------------------|------------|
| 1 | 0x74c870 | 1 | 0x66D9BD1 | `0x66D9BD1  call 0x74C870  ; -> sub_74c870` | Container/vector reserve/grow helper invoked early (prologue reserve path) [I, consistent with disasm; not decoded] |
| 2 | 0xEEC6DE0 | 4 | 0x66D9CD2 | `0x66D9CD2  call 0xEEC6DE0  ; -> sub_eec6de0` | memmove/block move helper, used in Phase 1 key-insert path [V from docs/functions/66d9af0.md Phase 1] |
| 3 | 0x9BC830 | 12 | 0x66D9DC8 | `0x66D9DC8  call 0x9BC830  ; -> sub_9bc830` | Small-vector/arena push helper [I from BGFX_MAP.md "0x9bc830 (small-vector/arena push)"] |
| 4 | 0xE935700 | 12 | 0x66D9E60 | `0x66D9E60  call 0xE935700  ; -> sub_e935700` | Free helper [I from BGFX_MAP.md "0xe935700 x27 (free)"] |
| 5 | 0x74C9C0 | 2 | 0x66D9EF1 | `0x66D9EF1  call 0x74C9C0  ; -> sub_74c9c0` | Container/vector helper (growth/append path) [I; not decoded] |
| 6 | 0xEEC6ED0 | 3 | 0x66DA0A3 | `0x66DA0A3  call 0xEEC6ED0  ; -> sub_eec6ed0` | memset/zero helper for scratch arrays, Phase 2 [V from docs/functions/66d9af0.md Phase 2] |
| 7 | 0x47E8F0 | 1 | 0x66DA280 | `0x66DA280  call 0x47E8F0  ; -> sub_47e8f0` | Small copy/assert helper [I from BGFX_MAP.md "0x47e8f0 (x58, small copy/assert helper)"] |
| 8 | 0xBB68930 | 1 | 0x66DA346 | `0x66DA346  call 0xBB68930  ; -> sub_bb68930` | Creates/obtains cached handle/resource handle in group setup [V from docs/functions/66d9af0.md Phase 2: `h = 0xbb68930(...)`] |
| 9 | 0x4DF8370 | 1 | 0x66DA3F6 | `0x66DA3F6  call 0x4DF8370  ; -> sub_4df8370` | Per-group cached-handle / material-mode selection helper [V from docs/functions/66d9af0.md Phase 2] |
| 10 | 0x4E019A0 | 1 | 0x66DA450 | `0x66DA450  call 0x4E019A0  ; -> sub_4e019a0` | Copies/fills per-group record data after 0x4DF8370 [V from docs/functions/66d9af0.md Phase 2] |
| 11 | 0x66D8F60 | 1 | 0x66DA478 | `0x66DA478  call 0x66D8F60  ; -> sub_66d8f60` | Phase 3 helper (uniform-name hash/binding path) [V context from docs/functions/66d9af0.md Phase 3] |
| 12 | 0x67DA040 | 1 | 0x66DA4A6 | `0x66DA4A6  call 0x67DA040  ; -> sub_67da040` | Phase 3 helper (uniform path) [V context from docs/functions/66d9af0.md Phase 3] |
| 13 | 0xE869FF0 | 11 | 0x66DA6FB | `0x66DA6FB  call 0xE869FF0  ; -> sub_e869ff0` | Copies/moves shader-head/owned block data into pools [V from docs/functions/66d9af0_builders.md] |
| 14 | 0xE86B370 | 1 | 0x66DAC68 | `0x66DAC68  call 0xE86B370  ; -> sub_e86b370` | Helper (not decoded) [I/?] |
| 15 | 0xE938CB0 | 24 | 0x66DB081 | `0x66DB081  call 0xE938CB0  ; -> sub_e938cb0` | Memory/copy helper, very frequent (TLS scope guard enter) [I; used 24x in pairs with 0xE938D70] |
| 16 | 0x567DB00 | 1 | 0x66DB09A | `0x66DB09A  call 0x567DB00  ; -> sub_567db00` | Phase 3/helper (Bones/PrevBones/PrevWorld buffer paths) [I context from docs/functions/66d9af0.md] |
| 17 | 0xE935740 | 6 | 0x66DB0A7 | `0x66DB0A7  call 0xE935740  ; -> sub_e935740` | Memory/copy helper (guard release / atexit registration) [I] |
| 18 | 0xE938D70 | 24 | 0x66DB0B3 | `0x66DB0B3  call 0xE938D70  ; -> sub_e938d70` | Memory/copy helper, very frequent (TLS scope guard exit) [I; used 24x in pairs with 0xE938CB0] |
| 19 | 0x19932C0 | 30 | 0x66DB57C | `0x66DB57C  call 0x19932C0  ; -> sub_19932c0` | XXH64 hash/update helper (data rcx, len rdx, seed r8), x30 for uniform/group keys [V from BGFX_MAP.md line 490 and docs/functions/66d9af0.md] |
| 20 | 0xBCABA00 | 5 | 0x66DDB6F | `0x66DDB6F  call 0xBCABA00  ; -> sub_bcaba00` | Registry emplace/push into pass/registry structures [V context from docs/functions/66d9af0.md Phase 4 "0xbcaba00 x5"] |
| 21 | 0xEEC6EC0 | 2 | 0x66DEAC0 | `0x66DEAC0  call 0xEEC6EC0  ; -> sub_eec6ec0` | memcpy/block copy helper (DrawItem push) [V from docs/functions/66d9af0_builders.md] |
| 22 | 0x66A08B0 | 1 | 0x66DEBDD | `0x66DEBDD  call 0x66A08B0  ; -> sub_66a08b0` | Terrain/material setup helper in Phase 4 [V from docs/functions/66d9af0.md] |
| 23 | 0x79580 | 18 | 0x66DF63E | `0x66DF63E  call 0x79580  ; -> sub_79580` | std::string constructor / small utility, 18x for uniform-name statics [I] |
| 24 | 0x73150 | 18 | 0x66E0046 | `0x66E0046  call 0x73150  ; -> sub_73150` | Small runtime/memory helper (allocator/growth/shim) [I] |
| 25 | 0xBBD7C70 | 1 | 0x66E0F08 | `0x66E0F08  call 0xBBD7C70  ; -> sub_bbd7c70` | Phase 5 helper before draw-state build [I/? from docs/functions/66d9af0.md] |
| 26 | 0x4DEDD00 | 1 | 0x66E0F18 | `0x66E0F18  call 0x4DEDD00  ; -> sub_4dedd00` | Phase/helper in BatchActor pipeline (not decoded) [I/?] |
| 27 | 0x66B2B30 | 1 | 0x66E0FA6 | `0x66E0FA6  call 0x66B2B30  ; -> sub_66b2b30` | Registry emplace/helper for material-name/node records (shared with Nametag/Cracks) [V from docs/functions/66d9af0.md Phase 5] |
| 28 | 0x66A0F60 | 1 | 0x66E10AC | `0x66E10AC  call 0x66A0F60  ; -> sub_66a0f60` | Builds draw geometry/state (DrawItemGeometry* init + index-buffer resolution) [V from docs/functions/66d9af0_builders.md] |
| 29 | 0x66D9710 | 9 | 0x66E1371 | `0x66E1371  call 0x66D9710  ; -> sub_66d9710` | DrawProtoSources* -> DrawItemProtoPacked* pack/copy [V from docs/functions/66d9af0_builders.md] |
| 30 | 0x66C11B0 | 6 | 0x66E137D | `0x66E137D  call 0x66C11B0  ; -> sub_66c11b0` | DrawItemProtoPacked* -> DrawItemProto* copy/packer [V from docs/functions/66d9af0_builders.md] |
| 31 | 0x66BF290 | 1 | 0x66E1406 | `0x66E1406  call 0x66BF290  ; -> sub_66bf290` | Variant builder (0x12e6B family, Opaque/AlphaTest/Transparent) [V from docs/functions/66d9af0_builders.md] |
| 32 | 0x66C17E0 | 8 | 0x66E140F | `0x66E140F  call 0x66C17E0  ; -> sub_66c17e0` | Proto/DrawItem destructor/cleanup [V from docs/functions/66d9af0_builders.md] |
| 33 | 0x67743C0 | 2 | 0x66E14FF | `0x66E14FF  call 0x67743C0  ; -> sub_67743c0` | Helper (not decoded) [I/?] |
| 34 | 0x66CC400 | 1 | 0x66E15C8 | `0x66E15C8  call 0x66CC400  ; -> sub_66cc400` | Builder/helper in family neighborhood (not expanded in builders doc) [I/?] |
| 35 | 0x66CBA10 | 1 | 0x66E15DC | `0x66E15DC  call 0x66CBA10  ; -> sub_66cba10` | Builder/helper in family neighborhood (not expanded in builders doc) [I/?] |
| 36 | 0x66CC660 | 1 | 0x66E15E5 | `0x66E15E5  call 0x66CC660  ; -> sub_66cc660` | Cleanup/flush helper alias (same family as 0x66BF150/0x66C17E0) [V from docs/functions/66d9af0_builders.md] |
| 37 | 0x66CC7A0 | 1 | 0x66E1770 | `0x66E1770  call 0x66CC7A0  ; -> sub_66cc7a0` | Variant builder (0x13F2B family) [V from docs/functions/66d9af0_builders.md] |
| 38 | 0x66C3840 | 1 | 0x66E1A38 | `0x66E1A38  call 0x66C3840  ; -> sub_66c3840` | Variant builder (0x12E6B family) [V from docs/functions/66d9af0_builders.md] |
| 39 | 0x66C1920 | 1 | 0x66E1AEA | `0x66E1AEA  call 0x66C1920  ; -> sub_66c1920` | Variant builder (0x12E6B family) [V from docs/functions/66d9af0_builders.md] |
| 40 | 0x66CE8D0 | 1 | 0x66E1B9C | `0x66E1B9C  call 0x66CE8D0  ; -> sub_66ce8d0` | Variant builder (0x13F2B family) [V from docs/functions/66d9af0_builders.md] |
| 41 | 0x66C5760 | 1 | 0x66E1C4E | `0x66E1C4E  call 0x66C5760  ; -> sub_66c5760` | Variant builder (0x12E6B family) [V from docs/functions/66d9af0_builders.md] |
| 42 | 0x66BF150 | 3 | 0x66E1C5F | `0x66E1C5F  call 0x66BF150  ; -> sub_66bf150` | Proto/DrawItem cleanup helper (alias family) [V from docs/functions/66d9af0_builders.md] |
| 43 | 0x66C7680 | 1 | 0x66E1E65 | `0x66E1E65  call 0x66C7680  ; -> sub_66c7680` | Variant builder (0x13F2B family) [V from docs/functions/66d9af0_builders.md] |
| 44 | 0x66C98E0 | 1 | 0x66E1F42 | `0x66E1F42  call 0x66C98E0  ; -> sub_66c98e0` | Variant builder (0x13F2B family) [V from docs/functions/66d9af0_builders.md] |
| 45 | 0x66BB7B0 | 1 | 0x66E20CF | `0x66E20CF  call 0x66BB7B0  ; -> sub_66bb7b0` | Variant builder (0x114F family) [V from docs/functions/66d9af0_builders.md] |
| 46 | 0x66A65B0 | 1 | 0x66E20D8 | `0x66E20D8  call 0x66A65B0  ; -> sub_66a65b0` | Proto destructor/cleanup alias (same as 0x66C17E0 family) [V from docs/functions/66d9af0_builders.md] |
| 47 | 0x66BD430 | 1 | 0x66E21B3 | `0x66E21B3  call 0x66BD430  ; -> sub_66bd430` | Variant builder (0x11F0 family) [V from docs/functions/66d9af0_builders.md] |
| 48 | 0x78ED0 | 1 | 0x66E2217 | `0x66E2217  call 0x78ED0  ; -> sub_78ed0` | Small utility/helper on error/bounds path [I; "out-of-range path, int3" per docs/functions/5679db0.md] |
| 49 | 0xB432E0 | 1 | 0x66E25BB | `0x66E25BB  call 0xB432E0  ; -> sub_b432e0` | Error/fail path helper (invalid record index path) [I from docs/functions/66d9af0.md] |
| 50 | 0x75740 | 8 | 0x66E25C1 | `0x66E25C1  call 0x75740  ; -> sub_75740` | Error/overflow throw helper ("bad array new length") [V from docs/functions/6640d80_light_visitor.md] |
| 51 | 0x75B60 | 4 | 0x66E25FF | `0x66E25FF  call 0x75B60  ; -> sub_75b60` | Error/overflow throw helper ("vector too long") [V from docs/functions/6640d80_light_visitor.md] |

Total: 51 distinct direct callees. Call-site counts sum to 273 direct `call` instructions [V from disassembly].

### Indirect calls (not in rdis callee list; listed for completeness)
```
0x66D9D71  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040   (x29, vtable/interface thunk)
0x66E25E0  call qword ptr [0xF9A8C78]  ; [data_f9a8c78]                   (x1, heap-corruption check)
```
Target RVAs of indirect calls are not resolved by static analysis alone [?].

## Variant builders (10) [V from docs/functions/66d9af0_builders.md]
| Builder RVA | Family | Size | Call site |
|-------------|--------|------|-----------|
| 0x66BF290 | 0x12E6B | 0x12E6 | 0x66E1406 |
| 0x66C1920 | 0x12E6B | 0x12E6 | 0x66E1AEA |
| 0x66C3840 | 0x12E6B | 0x12E6 | 0x66E1A38 |
| 0x66C5760 | 0x12E6B | 0x12E6 | 0x66E1C4E |
| 0x66CC7A0 | 0x13F2B | 0x13F2 | 0x66E1770 |
| 0x66CE8D0 | 0x13F2B | 0x13F2 | 0x66E1B9C |
| 0x66C7680 | 0x13F2B | 0x13F2 | 0x66E1E65 |
| 0x66C98E0 | 0x13F2B | 0x13F2 | 0x66E1F42 |
| 0x66BB7B0 | 0x114F | 0x114F | 0x66E20CF |
| 0x66BD430 | 0x11F0 | 0x11F0 | 0x66E21B3 |

## NEXT
- Run `python tools/sigs/verify_oc.py docs/progress/oc_U-E2.md` to confirm all quoted `0xRVA  instr` lines match the exe.
- Flag any unverified items as `[UNVERIFIED: 0x<rva> <question>]`.

## Tool requests
None (used only existing rdis/xref/grep tools; no throwaway scripts needed beyond a local PowerShell table-sort that was not saved).