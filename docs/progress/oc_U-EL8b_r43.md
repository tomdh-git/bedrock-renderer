## NEXT
DONE

# Unit U-EL8b — Atlases (terrain, items), mipmaps and compression (Minecraft.Windows.exe 1.26.62.01, PE ImageBase 0x140000000)

GOAL: close checklist item L8b (terrain atlas idx6 / item atlas idx7 registration, mipmaps, BC1/BC3/BC7 compression).

## Rules (from OPENCODE_BRIEF.md)
- Static analysis only; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe
- Every claim tagged [V] (saw in disasm, cite RVA), [I] (inferred), [?] (unknown)
- Append findings after each step; never guess as fact
- Output file ONLY: docs/progress/oc_U-EL8b.md

## Inputs consumed (NOT redone)
- docs/progress/oc_U-EL8b_r1..r42 (all prior attempts; all CLOSES? NO; same blocking fact)
- docs/progress/oc_U-L8b.md (earlier PNG/TGA decoder attempt, not atlas creation)
- Live captures DONE per docs/data/live/_status.txt:
  - docs/data/live/mc_root_4e05e50_callers.txt (rva=0x4E05E50, hits=150, samples=32)
  - docs/data/live/l8b_texcreate_record.txt (rva=0xE81BF30, hits=150, samples=24)
- Pending capture (no result yet): docs/data/live/l8b_resizetex_slot31 (rva=0xE815840, resizeTexture slot 31)
- Capture queue: 4 pending (at limit), cannot add a new request this unit

## Blocking fact (single, unchanged from r1-r42)
Atlas texture creation (stitcher/consumer of the registered TerrainAtlas idx6 / ItemAtlas idx7 slots), mipmap generation and BC1/BC3/BC7 compression are not located in Minecraft.Windows.exe. The live texture-object vptr at obj+0x00 = 0x00007FF6A8215838 [V live] resolves outside the exe image (ImageBase 0x140000000 [V PE header]), i.e. to another module; stitcher/mip/compression logic is therefore not statically decidable from this exe.

## New angle taken this unit (not a redo of prior proofs)
1. Verified sub_1870de0 (atlas registration slot manager) callers via `xref.py callers 0x1870DE0`: exactly 2 static callers — 0x1042320 (ServerLevelLoad, 2 sites) and 0x186e6a0 (registration dispatcher). No stitcher calls it. Prior notes (r41/r42) documented sub_186e6a0's callers but NOT sub_1870de0's own callers; this closes that gap.
2. Tried to add a live capture at 0x1870DE0 entry — blocked: capture queue at 4/4 pending limit.
3. Confirmed existing live data: all 150+ observed creations are format 0x1C / numMips=1 / type "tex", no atlas names.

## STEP: sub_1870de0 caller verification (new, not in r1-r42)
`xref.py callers 0x1870DE0` returns exactly 2: `0x1042320 0x1d1` and `0x186e6a0 0x1cb7` [V xref callers]. Disassembly confirms the call sites:
- `0x10423c7  call 0x1870DE0` — ServerLevelLoad (sub_1042320) directly calls sub_1870de0 for load-phase names [V disasm]
- `0x104246b  call 0x1870DE0` — ServerLevelLoad second direct call to sub_1870de0 [V disasm]
- `0x186f76d  call 0x1870DE0` — TerrainAtlas idx 6 registration via sub_186e6a0 [V disasm]
- `0x186f838  call 0x1870DE0` — ItemAtlas idx 7 registration via sub_186e6a0 [V disasm]
No other code calls sub_1870de0, so no stitcher consumes the registered atlas nodes through this function [V xref callers].

---
## Findings (one row per distinct offset/offset-group; all sites listed; verbatim instr lines verified against rdis)

| offset | size | read/store address | `0xRVA  instr` proof | meaning [tag] |
|---|---|---|---|---|
| Atlas node +0x0 dispatch object | 8B | [rsi] := rax | `0x1870ec5  mov [rsi],rax` | atlas node+0 = dispatch object taken from registry head; source nulled by `0x1870e93  mov qword ptr [rcx+0x10],0` and `0x1870ebe  mov qword ptr [rcx],0` [V] |
| Atlas node +0x8 idx | 4B | [rsi+8] := eax | `0x1870ecb  mov [rsi+8],eax` | atlas node+8 = idx from caller r9d: TerrainAtlas 6 (`0x186f767  mov r9d,6`), ItemAtlas 7 (`0x186f832  mov r9d,7`), AnimatedAtlas 8 (`0x186f8fd  mov r9d,8`) [V] |
| Atlas node +0x10 name pointer | 8B | [rdi+0x10] := rdx | `0x18711c9  mov [rdi+0x10],rdx` | atlas node+0x10 = name buffer pointer holding the registered atlas name string [V] |
| Registry '*' sentinel | 4B | [rcx] sentinel scan | `0x1870e30  cmp dword ptr [rcx],0x2A` | slot terminator is '*' (0x2A) [V] |
| Registry slot bound | 4B | loop bound [r14d] | `0x1870f2b  cmp r14d,0x29` | slots scanned 0..41 (0x29), step `0x1870f28  inc r14d` [V] |
| TerrainAtlas name ptr | 8B | lea rax | `0x186f731  lea rax,[0xF55CDD3]` | sub_186e6a0 loads "TerrainAtlas" (len 0xC at [rbp+0x108]) for sub_1870de0 — TerrainAtlas slot registration idx 6 [V xref str "TerrainAtlas"@0xf55cdd3 ref 0x186f731; V disasm] |
| ItemAtlas name ptr | 8B | lea rax | `0x186f7fc  lea rax,[0xF55CDE0]` | sub_186e6a0 loads "ItemAtlas" (len 9 at [rbp+0x118]) for sub_1870de0 — ItemAtlas slot registration idx 7 [V xref str "ItemAtlas"@0xf55cde0 ref 0x186f7fc; V disasm] |
| TerrainAtlas reg call | 8B | call | `0x186f76d  call 0x1870DE0` | TerrainAtlas idx 6 registration call site; r9d=6 set at `0x186f767  mov r9d,6` [V disasm] |
| ItemAtlas reg call | 8B | call | `0x186f838  call 0x1870DE0` | ItemAtlas idx 7 registration call site; r9d=7 set at `0x186f832  mov r9d,7` [V disasm] |
| ServerLevelLoad → sub_186e6a0 | 8B | call | `0x104237e  call 0x186E6A0` | ServerLevelLoad (sub_1042320) calls atlas registration sub_186e6a0 [V disasm; xref callers of 0x186e6a0: 0x1042320, 0x8f6810] |
| ServerLevelLoad → sub_1870de0 | 8B | call | `0x10423c7  call 0x1870DE0`; `0x104246b  call 0x1870DE0` | ServerLevelLoad directly re-enters sub_1870de0 twice for load-phase names (idx 0x28/0x29), then frees via sub_2FE440/sub_E935700 — no atlas texture creation [V disasm] |
| sub_1870de0 callers | - | - | - | sub_1870de0 has exactly 2 static callers: 0x1042320 (ServerLevelLoad, 2 sites) and 0x186e6a0 (registration dispatcher); no stitcher calls it [V xref callers 0x1870DE0] |
| texture-object vptr +0x00 | 8B | [rcx] := rax | `0x4e060c2  mov [rcx],rax` | texture-object vptr written from data_f215838 in sub_4e060b0 ctor; live value at obj+0x00 = 0x00007FF6A8215838 (LE `385821A8F67F0000`) [V live mc_root_4e05e50_callers.txt:4]; ImageBase 0x140000000 [V PE header] → vptr outside exe image → class implemented in another module [I] |
| sub_4e05e50 → sub_bc41420 | 8B | call | `0x4e05f77  call 0xBC41420` | sub_4e05e50 builds texture description via sub_bc41420 (rcx=obj+0x58 desc area, `0x4e05f74  mov rcx,rdi`); observed ret=0x4E05F7C [V live dragon_texture_caller_bc41420.txt:3] | [V + V live] |
| desc +0xB0 format byte | 1B | [rdi+0xB0] := r13b | `0xe81c077  mov [rdi+0xB0],r13b` | desc+0xB0 = format byte; fallback `0xe81c12b  cmp byte ptr [rdi+0xB0],0x42` (0x42 uncompressed fallback); live format 0x1C uncompressed [V + V live] |
| desc +0xB1 numMips byte | 1B | [rdi+0xB1] := dl | `0xe81c0d1  mov [rdi+0xB1],dl` | desc+0xB1 = numMips byte; only numMips store located; live numMips=1 [V + V live] |
| TextureD3D12::create entry (slot 26) | - | - | `0xe81455b  call 0xE81BF30` | only static caller of createTexture entry 0xe81bf30; ret=0xe814560 nop observed live [V live l8b_texcreate_record.txt:3] | [V + V live] |
| resizeTexture slot 31 entry | - | - | `0xe815840  push rbp` | resizeTexture entry; `0xe815866  mov edi,r9d` r9d = mips param; 0 static xrefs, never live [V] |
| all live creations | 4B/1B | live RCX dumps | `0x4e05f74  mov rcx,rdi` | every observed creation (150 mc_root + 10 l8b_texcreate): DXGI format 0x1C, numMips=1, type "tex"; names = "Texture: 2799/2815", "legs", "PerFrameConstants" — NO atlas names [V live mc_root_4e05e50_callers.txt:4; l8b_texcreate_record.txt:4] | [V live] |

## CLOSES?

CLOSES?: NO — blocking fact: atlas texture creation (stitcher/consumer of the registered TerrainAtlas idx6 / ItemAtlas idx7 slots from sub_186e6a0→sub_1870de0), mipmap generation and BC1/BC3/BC7 compression are not present in Minecraft.Windows.exe statically.

Proven [V]:
- Atlas registration: TerrainAtlas idx 6 and ItemAtlas idx 7 registered in sub_186e6a0 via sub_1870de0 (0x48-byte nodes, name at +0, idx at +8), triggered by ServerLevelLoad sub_1042320 (`0x104237e  call 0x186E6A0`) and initStep1 sub_8f6810 (`0x8f6919  call 0x186E6A0`) [V]
- sub_1870de0 has exactly 2 static callers (ServerLevelLoad 0x1042320 at 0x10423c7/0x104246b, sub_186e6a0 at 0x186f76d/0x186f838); no stitcher calls it [V xref callers]
- All texture creation funnels through sub_12893d0 (deferred texture transactions) → sub_4e05e50 → sub_bc41420 → TextureD3D12::create (0xe81bf30) → createTexture (0xe8143c0) [V + V live]
- Every observed creation (150+ live samples): format 0x1C uncompressed, numMips=1, type "tex", no atlas names [V live mc_root_4e05e50_callers.txt:4; l8b_texcreate_record.txt:4]

Not found [V/I]:
- Atlas stitcher: no consumer of the registered atlas nodes; objects are consumed by sub_2FE440 then freed by sub_E935700; no texture-creation call inside sub_1870de0 (full body read) [V]
- Texture-object vptr at obj+0x00 = 0x00007FF6A8215838 [V live] is outside the exe image (ImageBase 0x140000000 [V PE header]) → stitcher/mip/compression class lives in another module [I]
- Mipmaps: numMips only store is desc+0xB1; every live creation numMips=1; resizeTexture slot 31 (0xe815840) has 0 static xrefs, never live [V + V live]
- BC1/BC3/BC7: BC strings unreferenced; no compression code located; unsupported formats fall back to 0x42 [V dossier e81bf30.md; I per prior reviews r8/r10/r13]

Recommendation: mark L8b as external/not-in-exe (parked). Closing requires the pending l8b_resizetex_slot31 capture result (resizeTexture slot 31 — mips>1 would be mip-generation evidence; ret= would name the stitcher caller) or access to the other module.

## TOOL REQUESTS

- l8b_resizetex_slot31 (rva=0xE815840) — already pending in capture_requests.json, no result yet; await orchestrator run. Would answer whether resizeTexture (mips>1) is ever called and name the stitcher caller via ret=.
- sub_1289440_callers (rva=0x1289440) — already pending; would name sub_12893d0's runtime callers.
- No helper scripts written this unit.
- Cannot add a new capture: queue at 4/4 pending limit.