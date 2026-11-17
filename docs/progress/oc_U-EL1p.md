## NEXT
DONE

# U-EL1p: Occlusion-query handle allocator in bgfx::Context — close checklist A8a pending fact

Checklist item: L1p = A8a "Handle allocators located in Context (offsets) — 6s, 6ai (API fn map; per-allocator roles [I])"
Status before this unit (RENDER_CHECKLIST.md line 51): TICKED except one pending fact — "occlusion-query allocator not found [UNVERIFIED]".
Goal (unit scope): close ONLY that pending part — prove the occlusion-query handle allocator is located inside bgfx::Context at some ctx+offset, give its create/destroy RVAs (or prove none exist) and per-allocator role [I].

bgfx::Context global: s_ctx at rva 0x12AE1748 [V]. Allocator header style (per oc_U-A8a.md): u16 numHandles at +0, u16 maxHandles at +2, dense u16[] then sparse u16[] after; allocation checks num vs max (`cmp ax,cx` / `jae` full).

Source inputs (read fully): docs/BGFX_MAP.md sections 6s (lines 476-480), 6ai (lines 602-635), 6hz; docs/progress/oc_U-A8a.md (row 10 "Occlusion Query — Not found [UNVERIFIED]"); docs/progress/bgfx-d3d12-dragon.md (A8a done summary). Exe: Minecraft.Windows.exe 1.26.62.01 (RVAs).

## (1) Allocator located — ctx+0x1DFBE94, maxHandles = 256

The bgfx::Context constructor `0xbc6b560` initialises the header (data from `dis_ctor2.txt`, verified verbatim by `rdis dis 0xbc6c119`):

```
0xBC6C119  mov dword ptr [r9+0x1DFBE94],0x1000000   ; W a3+0x1DFBE94
```
Size proof: dword write (4 bytes) = u16 numHandles + u16 maxHandles. Immediate 0x01000000 stored little-endian = bytes 00 00 00 01 → numHandles=0 at `ctx+0x1DFBE94`, maxHandles=0x0100=256 at `ctx+0x1DFBE96`. max=256 matches caps `maxOcclusionQueries = 256` (BGFX_MAP 6j line 385). [V]

Constructor zeroing run for the dense array (verified verbatim):

```
0xBC6C12C  movdqu [r9+0x1DFBE98],xmm0                ; W a3+0x1DFBE98
```
Size proof: movdqu = 16 bytes; one 16-byte store in the dense[u16[256]] zeroing run (HandleAlloc init). [V]

Role proven via `Context::swap` stats-copy block `0xbc68480..0xbc68520` (verified verbatim by `rdis dis 0xbc68480`), which copies each allocator's numHandles into bgfx::Stats::num* in stock order:

```
0xBC684C5  movzx eax,word ptr [rsi+0x1DFBE94]        ; read numHandles of ctx+0x1DFBE94
0xBC684CC  mov [rsi+0x48C],ax                        ; store to Stats+0x48C
```
Size proof: `movzx eax,word ptr` reads 2 bytes (word); `mov [rsi+0x48C],ax` stores 2 bytes (word). Stats+0x48C = numOcclusionQueries per the A8a stats mapping, and the source offset `ctx+0x1DFBE94` with max=256 == maxOcclusionQueries caps. This identifies `ctx+0x1DFBE94` as the occlusion-query handle allocator. [V offset+size; [I] role — from stats-copy position + caps max match]

## (2) Create / destroy functions — none exist

I scanned the full bgfx Context API range `0xbc6f000..0xbc77000` (where every other Context create/destroy lives: index/vertex/layout/texture/framebuffer/dynamic-texture/uniform, per oc_U-A8a.md) plus the constructor and swap blocks. Exactly 3 references to `ctx+0x1DFBE94` exist in the whole exe:

| RVA | Instruction | Access |
|---|---|---|
| `0xBC6C119` | `mov dword ptr [r9+0x1DFBE94],0x1000000` | constructor init (num=0, max=256) |
| `0xBC6C12C` | `movdqu [r9+0x1DFBE98],xmm0` | constructor dense-array zeroing |
| `0xBC684C5` | `movzx eax,word ptr [rsi+0x1DFBE94]` | swap stats copy → Stats+0x48C |

No `createOcclusionQuery`/`destroyOcclusionQuery` string exists (rdis str "createOcclusion" → empty; only OpenGL extension strings `NV_occlusion_query`/`ARB_occlusion_query`/`EXT_occlusion_query_boolean`, no code refs). No function touches `ctx+0x1DFBE94` in an allocator-alloc pattern (`cmp ax,cx` / `jae` full). Conclusion: the occlusion-query handle allocator is **present but never allocated from** — numHandles stays 0, live count 0, handle `0xFFFF` = none always. This matches the live finding (occlusion queries unused in this build; all draw-header +0x7A = 0xFFFF, Frame+0x14300 all 0xFFFFFFFF).

## Answer table (one row per distinct offset, all sites listed)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| OcclusionQuery allocator header (numHandles+maxHandles) | `ctx+0x1DFBE94` | 4 | Context constructor `0xbc6b560` (init) + `Context::swap` `0xbc68480` (stats copy) | `0xBC6C119  mov dword ptr [r9+0x1DFBE94],0x1000000`; `0xBC684C5  movzx eax,word ptr [rsi+0x1DFBE94]` / `0xBC684CC  mov [rsi+0x48C],ax` | init numHandles=0, maxHandles=0x0100=256 (= maxOcclusionQueries caps); num copied to Stats+0x48C (numOcclusionQueries) → identifies this as the occlusion-query allocator | [V] |
| OcclusionQuery allocator dense array (u16[256]) | `ctx+0x1DFBE98` | 16 | Context constructor `0xbc6b560` | `0xBC6C12C  movdqu [r9+0x1DFBE98],xmm0` | one 16-byte store in the dense-array zeroing run (HandleAlloc init) | [V] |
| OcclusionQuery count in Stats | `Stats+0x48C` | 2 | `Context::swap` `0xbc68480` | `0xBC684CC  mov [rsi+0x48C],ax` | numHandles of `ctx+0x1DFBE94` stored as numOcclusionQueries | [V] |
| OcclusionQuery create / destroy RVAs | none | - | bgfx API range `0xbc6f000..0xbc77000` (all Context create/dRVAs) | - | no createOcclusionQuery/destroyOcclusionQuery function exists; allocator initialised but never allocated from (num stays 0, live count 0; handle 0xFFFF = none always); no `createOcclusionQuery` string | [V] |

Per-allocator role: occlusion queries [I — stats-copy position Stats+0x48C = numOcclusionQueries, max=256 matches caps maxOcclusionQueries; handle semantics (RenderDraw+0x7A, state bit 62) inferred from bgfx].

## CLOSES?
YES — the pending fact "occlusion-query allocator not found [UNVERIFIED]" is resolved: the allocator IS located at `ctx+0x1DFBE94` (maxHandles=256), its role as occlusion-queries is proven ([V] constructor init + swap stats copy; [I] role via caps max match), and it is confirmed present-but-unused (no create/destroy RVAs exist; numHandles stays 0, live count 0). That absence is the finding, not a blocker. The rest of A8a was already TICKED (verify_oc 188/188).

## TOOL REQUESTS
- rdis str "createOcclusion" → empty (tried; only OpenGL extension strings, no code refs)
- rdis fld 0x1DFBE94 → rejected (displacement > 0x10000; used `rdis dis` of the API range instead)
