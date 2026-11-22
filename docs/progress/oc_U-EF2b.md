## NEXT
DONE

# Unit U-EF2b — Scene[0..11] -> pass-name map (pending part of F2b / L6d / 6dd)

## Source context (from docs/progress/oc_U-F2b.md + docs/RENDER_CHECKLIST.md L152/L326)

Pending item (the only part still open for F2b): **"Scene[0..11] -> pass-name map still open"**.
Already proven elsewhere [V]: task body 0x568CD90 per-view setup (view rect V+0x00/+0x04, 4 mat4 at V+0x10/+0x50/+0x90/+0xD0, sortMode V+0x110, byte V+0x122); all 13 std::function _Copy slots share _Do_call 0x568CD70 (thunk `jmp 0x568CD90`), lambdas differ only by captured state; 0xBCC1A30 capture handler and 0xBC60D10 (Encoder reset, not iterator) handled in oc_U-F2c.md.

This unit decodes the Scene[0..11] dispatch (jump table 0xF25D03C used by 0x568DB90) and attempts to recover the Scene[0..11] pass NAMES.

## Method
- `rdis dis 0x568DB90`, `dis 0x5698490`, `dis 0x5698710`, `dis 0x568CFF5` (rest of task body: item loop).
- `jt.py` decode of jump tables 0xF25D03C / 0xF25D050 / 0xF25D070 / 0xF25D084.
- `xref.py callers 0x568cd90/0x568cd70`, `ripscan.py 0x568cd70/0x568cd90/0xf43fe10` for lambda construction (all indirect via std::function vtable, no name-carrying construction found).
- `passhash2.py 0x5680000 0x56b0000` + `docs/data/render_hashes.txt` for pass names (BGFX_MAP.md 6o/6p: pass names are FNV-1 hash immediates, NOT .rdata strings).

## Result 1 — 0x568DB90 jump-table dispatch (item loop) [V]

Index derivation (per render item, stride 0x18 over [rbx+0x68]):
- 0x568D210 `movsx rcx,byte ptr [r12+0x18]`   read item pass/type byte
- 0x568D216 `inc rcx`                         index = byte + 1
- 0x568D21F `call 0x568DB90`                  dispatch

Jump table (20 relative int32 entries, base 0xF25D03C) used at:
- 0x568DB95 `lea rax,[0xF25D03C]`
- 0x568DB9C `movsxd rcx,[rax+rcx*4]`
- 0x568DBA0 `add rcx,rax`
- 0x568DBA3 `jmp rcx`

Decoded entries (tag -> target RVA) [V via jt.py + disassembly]:

| Tag | Target RVA | Handler |
|-----|------------|---------|
| 0 | 0x568dbf0 | epilogue (`add rsp,0x30; pop rsi; ret`) |
| 1 | 0x568dba5 | default item processing (bounds check, call 0xE935700, zero 16B) |
| 2 | 0x568dba5 | default item processing (same as tag 1) |
| 3 | 0x568dbf0 | epilogue (ret) |
| 4 | 0x568dbf0 | epilogue (ret) |
| 5 | 0x56984ec | sub_5698490 case -> calls 0x5698A40 |
| 6 | 0x5698494 | sub_5698490 case -> calls 0x5698510 |
| 7 | 0x56984a9 | sub_5698490 header/cmp case |
| 8 | 0x56984bd | sub_5698490 case (`add r8,8; call 0x5698510`) |
| 9 | 0x56984d1 | sub_5698490 case (`add r8,0x20; call 0x5698850`) |
| 10 | 0x5698494 | sub_5698490 case -> calls 0x5698510 |
| 11 | 0x5698494 | sub_5698490 case -> calls 0x5698510 |
| 12 | 0x5698494 | sub_5698490 case -> calls 0x5698510 |
| 13 | 0x5698758 | sub_5698710 case |
| 14 | 0x56987af | sub_5698710 epilogue (ret) |
| 15 | 0x56987af | sub_5698710 epilogue (ret) |
| 16 | 0x5698758 | sub_5698710 case |
| 17 | 0x5698758 | sub_5698710 case |
| 18 | 0x569875e | sub_5698710 case (`add qword ptr [rdx+8],0x28; jmp 0x569878c`) |
| 19 | 0x5698765 | sub_5698710 internal-dispatch case (jump tables 0xF25D070/0xF25D084) |

Tags 5–12 (8 entries) route into sub_5698490 (0x5698490..0x5698506); tags 13–19 (7 entries) route into sub_5698710 (0x5698710..0x569881C).

## Result 2 — sub-dispatch tables [V]

sub_5698490(rcx=out, rdx=subindex) dispaces via table 0xF25D050:
- 0x5698498 `lea rax,[0xF25D050]`
- 0x569849F `movsxd rcx,[rax+rdx*4]`
- 0x56984A3 `add rcx,rax`
- 0x56984A6 `jmp rcx`
Entries: 0->0x5698500(fallback call 0x1166E0), 1->0x56984a8, 2->0x56984bd(`add r8,8;call 0x5698510`), 3->0x56984d1(`add r8,0x20;call 0x5698850`), 4->0x56984e5(`add r8,0x38;call 0x5698A40`), 5-7->0x56984a8, 8->0x569876c, 9-10->0x56987c3, 11-12->0x569876c, 13->0x5698772, 14-15->0x5698779, 16-17->0x5698772, 18->0x569898e, 19->0x569894e.

sub_5698710 internal tables 0xF25D070 (indexed by byte [rbp-0x18]) and 0xF25D084 (indexed by byte [rbp-0x38]):
- 0x569877C `lea rcx,[0xF25D070]` / 0x5698783 `movsxd rax,[rcx+rax*4]` / 0x569878a `jmp rax`
- 0x5698796 `lea rcx,[0xF25D084]` / 0x569879D `movsxd rax,[rcx+rax*4]` / 0x56987A4 `jmp rax`

## Result 3 — Scene[0..11] -> pass-name map

- 13 std::function lambdas total = 12 Scene passes + 1 HUD task [V from oc_U-F2b.md Part B: 13 _Copy slots 0xBC36B10..0xBC37300 + 0x56AE9C0].
- All share _Do_call 0x568CD70 (`mov rcx,rdx; mov rdx,r8; jmp 0x568CD90`); lambdas differ only by captured state [V].
- Scene[0..7] = jump-table tags 5..12 (sub_5698490 family); Scene[8..11] = tags 13..16 (sub_5698710 family). Tags 0-4 are local/epilogue/default; tags 17-19 are remaining sub_5698710 entries (HUD/extra). [I: 12 scenes fit tags 5-16; exact per-tag scene number not name-proven.]
- Handler targets per tag are listed in Result 1 [V].
- Pass NAMES: NOT FOUND [?].
  - passhash2.py over 0x5680000-0x56b0000: 0 Scene names (only 3 deferred names at 0x56a1xxx: DoDeferredShading @0x56a14c8, DoSkyProbeDeferredShading @0x56a1a97, ForwardPBRTransparentSkyProbe @0x56a29e3 — unrelated to Scene); 372 unresolved hash immediates with no name match.
  - docs/data/render_hashes.txt (whole-binary scan): 0 Scene[0..11] names in this region.
  - Scene dispatch code (0x568CD90 / 0x568DB90 / 0x5698490 / 0x5698710) contains NO string references (no `lea ..., [rip+...]` to a pass name).
  - BGFX_MAP.md 6o/6p: pass names are stored only as FNV-1 64 hash immediates (offset 0xcbf29ce484222325), not as .rdata strings; no Scene pass hash is matched to a name.

### Annotated instruction map (verbatim proof lines)

| Name | Offset | Size | Read/Store addr | Verbatim `0xRVA  instr` | Meaning | Tag |
|------|--------|------|-----------------|-------------------------|---------|-----|
| jump-table base load | 0x568DB95 | 7 | [0xF25D03C] | `0x568DB95  lea rax,[0xF25D03C]` | load jump-table base | [V] |
| load table entry | 0x568DB9C | 4 | [rax+rcx*4] | `0x568DB9C  movsxd rcx,[rax+rcx*4]` | signed int32 table entry | [V] |
| compute target | 0x568DBA0 | 3 | - | `0x568DBA0  add rcx,rax` | target = base + entry | [V] |
| indirect jump | 0x568DBA3 | 2 | - | `0x568DBA3  jmp rcx` | jump to handler | [V] |
| item pass byte read | 0x568D210 | 1 | [r12+0x18] | `0x568D210  movsx rcx,byte ptr [r12+0x18]` | read item type/pass byte | [V] |
| index + 1 | 0x568D216 | 2 | - | `0x568D216  inc rcx` | jump-table index | [V] |
| dispatch call | 0x568D21F | 5 | - | `0x568D21F  call 0x568DB90` | enter jump-table dispatch | [V] |
| sub-dispatch base | 0x5698498 | 7 | [0xF25D050] | `0x5698498  lea rax,[0xF25D050]` | sub_5698490 table base | [V] |
| sub-table entry load | 0x569849F | 4 | [rax+rdx*4] | `0x569849F  movsxd rcx,[rax+rdx*4]` | signed int32 sub-entry | [V] |
| sub-target add | 0x56984A3 | 3 | - | `0x56984A3  add rcx,rax` | | [V] |
| sub-jump | 0x56984A6 | 2 | - | `0x56984A6  jmp rcx` | | [V] |
| internal table 1 base | 0x569877C | 7 | [0xF25D070] | `0x569877C  lea rcx,[0xF25D070]` | sub_5698710 inner table | [V] |
| internal entry load 1 | 0x5698783 | 4 | [rcx+rax*4] | `0x5698783  movsxd rax,[rcx+rax*4]` | | [V] |
| internal table 2 base | 0x5698796 | 7 | [0xF25D084] | `0x5698796  lea rcx,[0xF25D084]` | sub_5698710 inner table | [V] |
| internal entry load 2 | 0x569879D | 4 | [rcx+rax*4] | `0x569879D  movsxd rax,[rcx+rax*4]` | | [V] |

## CLOSES?

NO — Scene[0..11] pass names are not stored as strings or resolvable inline immediates in the binary. Per BGFX_MAP.md 6o/6p they exist only as FNV-1 64 hash immediates, and no Scene pass hash matches a name (passhash2/render_hashes scan of 0x5680000-0x56b0000 found zero Scene names; Scene dispatch code has no string references). Only the index->handler mapping via 0xF25D03C (tags 5-16 = Scene[0..11] [I], handler targets [V]) is proven. Blocking fact: pass-name source is absent from static disassembly, so no [V] pass-name row exists for any Scene[N].

## TOOL REQUESTS

None — all work done with existing tools (rdis, jt.py, xref.py, ripscan.py, passhash2.py, render_hashes.txt).
