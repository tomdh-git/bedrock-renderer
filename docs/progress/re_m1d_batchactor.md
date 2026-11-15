# Progress: re_m1d_batchactor (M1d unit 1 — BatchActor extractor 0x66d9af0 callee map)

## NEXT
- None (unit complete). If extending: disassemble full 0x66d9af0 bodies for Phase 4/5 jump-table target semantics beyond existing notes; confirm builder→pass-pool mapping by cross-checking each builder’s byte-pool tables against extracted DrawItem fields in submit/flush code (not done here).

## Meta
- Repo: `C:\Users\Atomi\Desktop\BlueySenseV2`
- Target exe (static): `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe` [V]
- Tools used: `tools/rdis/target/release/rdis.exe` (`callees 0x66d9af0`, `sum 0x66d9af0`, `dis 0x66d9af0`), prior dossiers `docs/functions/66d9af0.md`, `docs/functions/66d9af0_builders.md`, `docs/progress/re_m1d_clones.md` [V]
- Date: 2026-11-15 [V]

## Log
- 2026-11-15: Read `docs/AGENT_BRIEF.md`, `tools/README.md`. Checked `docs/progress/re_m1d_clones.md` (NEXT points to this unit) and existing `docs/functions/66d9af0*.md`. Ran `graphify query ...` (CLI not available in shell) [I/tooling note]. Used rdis: `callees 0x66d9af0` (batched) captured full callee + string list; `sum 0x66d9af0` and `dis 0x66d9af0` (truncated dis via rdis) inspected for prologue/phase shape. Compiled callee one-liners (tagged). Produced D2-style phase map summary for 0x66d9af0 (from existing Phase map + rdis context). Updated `docs/functions/66d9af0.md` (additive callee map section). This file created (additive). Did NOT edit `BGFX_MAP.md`/`RENDER_CHECKLIST.md`. [V]

## Final report (unit 1)

### Function identity [V]
- `sub_66d9af0` (BatchActor extractor), range in rdis: `[0x66d9af0..0x66e26a7)` (per `callees` header context in prior dossier: size 0x8bb7). Dossier: `docs/functions/66d9af0.md`. Reached via Item group visitor for tag 10 (BatchActor) in practice (not direct callers) [V from existing docs].

### rdis `callees 0x66d9af0` (full list) with one-line meanings
Counts are call-site counts reported by rdis (`xN`) [V].

| Callee RVA | xN | One-line meaning [tag] |
|---|---:|---|
| 0x73150 | 18 | Small runtime/memory helper (allocator/growth/shim used in hot loops) [I] |
| 0x75740 | 8 | Error/overflow or bounds throw helper (common path on size checks) [I] |
| 0x75b60 | 4 | Error/overflow or bounds throw helper (common path on size checks) [I] |
| 0x78ed0 | 1 | Small utility/helper (not decoded here) [I] |
| 0x79580 | 18 | Small utility/helper (often string/format or range helper in this binary) [I] |
| 0x47e8f0 | 1 | Helper (callee not decoded; invoked once) [I/?] |
| 0x74c870 | 1 | Container/vector reserve/grow helper invoked early (matches dossier note around prologue reserve path) [I, consistent with disasm `call 0x74c870`] |
| 0x74c9c0 | 2 | Container/vector helper (related growth/append path) [I] |
| 0x9bc830 | 12 | Utility/helper (hash/container or math-adjacent in some modules; not decoded) [I/?] |
| 0xb432e0 | 1 | Error/fail path helper (used in guarded branch, e.g. invalid record index path mentioned in phase notes context) [I] |
| 0x19932c0 | 30 | XXH64-style hash/update helper used for group keys / hashing paths (documented in 66d9af0.md as XXH64 x30) [V] |
| 0x4dedd00 | 1 | Phase/helper in BatchActor pipeline (not decoded) [I/?] |
| 0x4df8370 | 1 | Per-group cached-handle / material-mode selection helper (documented in Phase 2 of 66d9af0.md) [V] |
| 0x4e019a0 | 1 | Copies/fills per-group record data after 4df8370 (Phase 2 of 66d9af0.md) [V] |
| 0x567db00 | 1 | Phase 3/helper (context near Bones/PrevBones/PrevWorld paths per 66d9af0.md) [I] |
| 0x66a08b0 | 1 | Terrain/material setup helper in Phase 4 (66d9af0.md) [V] |
| 0x66a0f60 | 1 | Builds draw geometry/state: `DrawItemGeometry*` init + index-buffer resolution path (66d9af0_builders.md) [V] |
| 0x66a65b0 | 1 | Proto destructor/cleanup alias in family (same as 0x66c17e0 family) [V] |
| 0x66b2b30 | 1 | Registry emplace/helper for material-name/node records (shared with other handlers; used in Phase 5) [V] |
| 0x66bb7b0 | 1 | Variant builder (one of ten) — pass/pool variant (66d9af0_builders.md table) [V] |
| 0x66bd430 | 1 | Variant builder (one of ten) — pass/pool variant (66d9af0_builders.md table) [V] |
| 0x66bf150 | 3 | Proto/DrawItem cleanup helper (alias family; also called in flush/cleanup paths) [V] |
| 0x66bf290 | 1 | Variant builder (one of ten) — 0x12e6B family variant (66d9af0_builders.md) [V] |
| 0x66c11b0 | 6 | `DrawItemProtoPacked* -> DrawItemProto*` copy/move packer (66d9af0_builders.md) [V] |
| 0x66c17e0 | 8 | `DrawItemProto` destructor/cleanup (frees transform vec/matrix storage, releases geometry shared-ptr/streams per header notes) [V] |
| 0x66c1920 | 1 | Variant builder (one of ten) [V] |
| 0x66c3840 | 1 | Variant builder (one of ten) [V] |
| 0x66c5760 | 1 | Variant builder (one of ten) [V] |
| 0x66c7680 | 1 | Variant builder (one of ten, 0x13f2B family) [V] |
| 0x66c98e0 | 1 | Variant builder (one of ten, 0x13f2B family) [V] |
| 0x66cc400 | 1 | Builder/helper in family neighborhood (not expanded in builders doc) [I/?] |
| 0x66cba10 | 1 | Builder/helper in family neighborhood (not expanded in builders doc) [I/?] |
| 0x66cc660 | 1 | Cleanup/flush helper alias (same family as 66bf150/66c17e0 context) [V] |
| 0x66cc7a0 | 1 | Variant builder (one of ten, 0x13f2B family) [V] |
| 0x66ce8d0 | 1 | Variant builder (one of ten, 0x13f2B family) [V] |
| 0x66d8f60 | 1 | Phase 3 helper (uniform-name hash/binding path noted in 66d9af0.md) [V context] |
| 0x66d9710 | 9 | `DrawProtoSources* -> DrawItemProtoPacked*` pack/copy (66d9af0_builders.md) [V] |
| 0x67743c0 | 2 | Helper (not decoded) [I/?] |
| 0x67da040 | 1 | Phase 3 helper (uniform path noted in 66d9af0.md) [V context] |
| 0xbb68930 | 1 | Creates/obtains cached handle/resource handle in group setup (Phase 2: `h = 0xbb68930(...)`) [V from 66d9af0.md] |
| 0xbbd7c70 | 1 | Phase 5 helper before draw-state build (not decoded) [I/?] |
| 0xbcaba00 | 5 | Registry emplace/push into pass/registry structures (Phase 4 notes `0xbcaba00 x5`) [V context] |
| 0xe869ff0 | 11 | Copies/moves shader-head/owned block data into pools (seen in builders: pushes shader head +0x78 block via this helper) [V from 66d9af0_builders.md] |
| 0xe86b370 | 1 | Helper (not decoded) [I/?] |
| 0xe935700 | 12 | Memory/copy or container helper (frequent small helper) [I] |
| 0xe935740 | 6 | Memory/copy or container helper [I] |
| 0xe938cb0 | 24 | Memory/copy or container helper (very frequent) [I] |
| 0xe938d70 | 24 | Memory/copy or container helper (very frequent) [I] |
| 0xeec6de0 | 4 | `memmove`/block move helper (used in key insert path in Phase 1) [V from 66d9af0.md] |
| 0xeec6ec0 | 2 | `memcpy`/block copy helper (used when copying DrawItem/pushing items) [V from 66d9af0_builders.md context] |
| 0xeec6ed0 | 3 | `memset`/zero helper for scratch arrays (Phase 2) [V from 66d9af0.md] |

**Strings referenced (rdis list, selection relevant to uniforms/textures):** `TintedAlphaTestEnabled`, `MetalnessUniform`, `EmissiveUniform`, `RoughnessUniform`, `SubsurfaceUniform`, `PBRTextureFlags`, `ActorFPEpsilon`, `DitheringEnabledToggle`, `MultiplicativeTintColor`, `UVScale`, `GlintColor`, `UseAlphaRewrite`, `PrevBones`, `PrevWorld`, `MERSTexture`, `NormalTexture`, `MatTexture1`, `MatTexture2` [V]. Also stray/format strings appear in tail (`"b\\"B\\""` etc. in dossier) [V].

### D2-style instruction/map summary (0x66d9af0), feasible from static notes
> Not line-by-line D2 of every instruction (function is ~35KB); this is a structured phase map in D2-like blocks. [V where cited from existing docs, I where inferred.]

```d2
direction: down
title: "0x66d9af0 BatchActor extractor (1.26.62.01) — phase map [V/I]"

prologue: "Prologue\nsub rsp,0x908; save xmm6..xmm15; locals: rbp+0x7A8 desc(r8), rbp+0x7A0 builder(rcx), rbp+0x7B0 ctx(ptr in rdx copy) [V]" {
  shape: rectangle
}
p1: "Phase 1: group instances by model key\nn=desc+0xE0, insts+0xE8 (stride 0x48)\nkeys vec @rbp+0x6D0.., slot u16 vec @rbp+0x480..\nper inst: key = insts[i].+0x08->+0x40; lower_bound+insert (eec6de0); push slot\ncals: 74c870?, eec6de0, alloc/throw helpers [V]" {
  shape: rectangle
}
p2: "Phase 2: per-group cached handle + mode\nheap arrays (eec6ed0); for each key: if +0x25C valid use +0x258 else bb68930 sets handle; mode from ctx+0x70/+r15\ncalls: bb68930, 4df8370, 4e019a0, eec6ed0 [V]" {
  shape: rectangle
}
p3: "Phase 3: uniform binding loops\nhash/assign uniform names (TintedAlphaTestEnabled..MatTexture2), Bone/PrevBones/PrevWorld related; shl4 loops over 0x10 binding arrays; uses 19932c0, 66d8f60, 67da040, 567db00, e869ff0* etc. [V strings/calls; body not line-decoded]" {
  shape: rectangle
}
p4: "Phase 4: per-group material/pass build\ncalls: bcaba00 x5 (registry emplace), 66a08b0 (TerrainInfo), eec6ec0 memcpy [V from notes]" {
  shape: rectangle
}
p5: "Phase 5: per-group draw build + dispatch\nbuild DrawProtoSources->Packed (66d9710), pack (66c11b0), build geometry/state (66a0f60), registry (66b2b30), select 1 of 10 builders by (P+0x50,P+0x51,edi,flag) then cleanup (66c17e0/66bf150 family); 4 jump tables for variant copies [V calls/skeleton; some condition pairing I]" {
  shape: rectangle
}
epilogue: "Epilogue/teardown\nreleases, restores xmm, stack frame cleanup [I from prologue symmetry]" {
  shape: rectangle
}

prologue -> p1 -> p2 -> p3 -> p4 -> p5 -> epilogue
```

### Notes / blockers
- `rdis path 0x66d9af0` returned `{"error":"missing address"}` in this invocation context [V observed]; path/choke exploration not produced here (not required by task). `sum 0x66d9af0` produced large memory-access JSON (not fully pasted) [V observed]. Disassembly via rdis `dis` was truncated to first ~2KB window by tool output limits; full disassembly was also inspected earlier via `python tools/sigs/xref.py dis 0x66d9af0` (truncated in conversation) but the authoritative full bytes/range remain in exe and prior dossier files [I].
- One-line meanings for many non-BatchActor-specific callees (0x73xxx/0x75xxx/0x79xxx/0x9bc830/0xe93*/0xeec6* runtime helpers, 0x47e8f0, 0x67743c0, 0x6xxxx helpers not yet reversed) are **inferred** from naming patterns/common usage in this codebase style unless cited from existing docs [I/?].
- No edits to `docs/BGFX_MAP.md`, `docs/RENDER_CHECKLIST.md` (forbidden) [V].

## FULL PROPOSED BGFX_MAP ENTRY TEXT (entry IDs TBD)
> Do NOT paste into BGFX_MAP.md. Proposed draft text for a future entry describing `sub_66d9af0` (BatchActor extractor). IDs/titles TBD by maintainer.

### Proposed entry (draft)
- **ID/Title (TBD):** `M1d-BatchActor-Extractor-0x66d9af0`
- **RVA/Sig anchor:** `0x66d9af0` in `Minecraft.Windows.exe` 1.26.62.01 (LeviLauncher instance path as in AGENT_BRIEF) [V]. No direct callers observed (reached via Item group visitor / dispatch) [V from dossier].
- **Role (one line):** Extractor for `RenderBatchActorDescription` (Item group tag 10, BatchActor): groups actor model instances by model key, prepares per-group cached handles/material mode, binds actor/PBR/uniform slots and textures by name, then builds and enqueues draw items into pass queues via variant builders (Opaque/AlphaTest/Transparent family) [V from docs/functions/66d9af0.md, 66d9af0_builders.md].
- **Key data (static/live notes):** Description head uses `+0xE0` instance count, `+0xE8` instance array (stride `0x48`); instance/record layout summarized in 66d9af0.md (RenderBatchActorDescription/instance/record notes) [V]. Uniform/texture name strings include `TintedAlphaTestEnabled`, `MetalnessUniform`, `EmissiveUniform`, `RoughnessUniform`, `SubsurfaceUniform`, `PBRTextureFlags`, `ActorFPEpsilon`, `DitheringEnabledToggle`, `MultiplicativeTintColor`, `UVScale`, `GlintColor`, `UseAlphaRewrite`, `PrevBones`, `PrevWorld`, `MERSTexture`, `NormalTexture`, `MatTexture1`, `MatTexture2` [V].
- **Notable callees (high-signal):** `0x19932c0` (XXH64-like hashing, x30) [V]; group/handle path `0xbb68930`, `0x4df8370`, `0x4e019a0` [V]; pack/copy `0x66d9710`, `0x66c11b0`, `0x66a0f60` [V]; registry/queues `0x66b2b30`, `0xbcaba00` [V]; variant builders `0x66bf290,0x66c1920,0x66c3840,0x66c5760,0x66cc7a0,0x66ce8d0,0x66c7680,0x66c98e0,0x66bb7b0,0x66bd430` [V]; cleanup `0x66c17e0`/aliases [V]. Full list with one-liners: `docs/progress/re_m1d_batchactor.md` (this file) and `docs/functions/66d9af0.md` (updated).
- **Evidence files:** `docs/functions/66d9af0.md`, `docs/functions/66d9af0_builders.md`, `docs/progress/re_m1d_batchactor.md`, `docs/progress/re_m1d_clones.md` [V].
- **Open/[?]:** Full line-complete decode of Phase 3/4/5 body branches beyond skeleton; exact semantic names for several small helpers (0x47e8f0, 0x66cc400, 0x66cba10, etc.) [I/?].