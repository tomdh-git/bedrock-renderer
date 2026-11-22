## NEXT
DONE

# oc_U-ER1 — R1 Atmosphere (Sky tag 0): per-field meaning, producer (no thin clone), VV AtmosphericScattering pass body draining pass+0x548

## Scope (from the checklist line R1)

Pending parts of R1 (BGFX_MAP 6ih, 6ik):
1. per-field meaning of RenderAtmosphereDescription (read-widths only; the Sky statics SkyColor/FogColor/... belong to tags 5/6, NOT tag 0 — do not map them onto Atmosphere)
2. the producer: Atmosphere has NO thin insert clone; find the Sky-group insert with tag 0 that builds it
3. the VV AtmosphericScattering pass body that drains the queue at pass+0x548

Explicitly out of scope: tags 5/6 (Sky/Stars) statics; anything beyond read-widths.

## Input data (read fully, not regenerated)

- docs/functions/66560f0_sky_cases.md — Sky group visitor 0x66560f0 case bodies incl. tag 0 (Atmosphere)
- docs/functions/66560f0.md — Sky visitor dispatcher + jump table (tag 0 -> 0x6656174)
- docs/functions/66560f0_sky_visitor.md — Sky visitor register map (rdi = description, rsi = frame ctx)
- docs/progress/oc_U-Atm.md — instruction-complete fragment 0x6656d4b..0x6657090 of the Atmosphere case (join + queue into pass+0x548); delegate check exit 0
- docs/data/listings/sky_heads_6656174_6656983.txt — Atmosphere case head 0x6656174..0x66561c7 verbatim
- docs/data/listings/sky_atmosphere_6656d4b_6657090.txt — Atmosphere join fragment verbatim
- docs/data/listings/lightgame_clone_53e2c00_53e3743.txt — producer candidate 0x53e2c00 verbatim
- docs/data/live_desc_sky_light_effect_1.26.62.01.txt — live "sky 0" capture (0x300 bytes of the Atmosphere description)
- docs/functions/53e2c00.md — producer candidate dossier
- docs/BGFX_MAP.md 6g (Sky tag table: tag 0 = clone 0x53e2c00), 6ih, 6ik, 6gq, 6hi, 6v, 6p
- rdis fld 0x540/0x548/0x550 full scans (all [reg+off] accesses across .text)
- rdis dis of 0x675530, 0x675980, 0x56e9590, 0x5711150, 0x6e769c0, 0xc27f940, 0xc288880, 0x6657200

## Status inherited from oc_U-ER1_r1.md (PROVEN — do NOT redo)

Part 1 per-field reads: all 31 offsets of the Atmosphere description are [V] at offsets 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74, 0x84, 0x94, 0x9C, 0xA0, 0xD8, 0xE8, 0xEC, 0xF0, 0xF8, 0x100, 0x104, 0x10C, 0x11C, 0x124, 0x128 with verbatim lines (see oc_U-ER1_r1.md Part 1 table). Extent ends 0x138, matching RenderAtmosphereDescription sizeof 0x138 [V]. All field meanings are '-' (no instruction/string names an Atmosphere field).

Part 3 producer: 0x53e2c00 (fat clone 0xb43 bytes, BGFX_MAP 6g/6w Sky tag 0) builds a local description frame at [rbp-0x38]..[rbp+0x8C] mapping to desc+0x00..+0xC4 with writes matching the visitor reads; called by 0x5376a00 ("Render sky" per BGFX_MAP strings); tail-jumps to 0x5369b30 at 0x53e2d39. NOT yet proven: store tag=0 and the insert call for Sky slot 0x370 tag 0 ([?]).

Part 4 drain: Atmosphere case queues a 0x58-byte record into [rsi+0x548] (begin)/[rsi+0x550] (end). `rdis imm 0x26A1B8F9CE2AFF0a` (FNV-1("AtmosphericScattering")) = 0 hits. 0xc273420.md defers the drain to R1.

## Queue layout breakthrough (NEW — from disassembly of 0x6657200..0x6657600)

The Sky visitor tag-0 path (0x66560f0) reads/writes three queue fields on the thread-local block (returned by 0x5aba5c0 = ThreadLocalObject::get, 0x8B8-byte per-thread data block):

| offset | size | verbatim line | meaning |
|---|---|---|---|
| +0x540 | 8 | `0x665723a  sub rax,[rsi+0x540]` | queue buffer BASE pointer [V] |
| +0x548 | 8 | `0x665702f  mov r15,[rsi+0x548]` | write CURSOR pointer [V] |
| +0x550 | 8 | `0x6657036  cmp r15,[rsi+0x550]` | END pointer (base + capacity) [V] |
| stride | — | `0x6657419  add qword ptr [rsi+0x548],0x130` ; `0x665729b  imul r13,rax,0x130` | cursor advances by 0x130 per push; element size = 0x130 bytes (NOT 0x58!) [V] |
| record | 0x40 | `0x6657043  movups xmm0,[rax]` ... `0x6657062  movups [r15+0x30],xmm0` | 0x40-byte record written at cursor [V] |

Each push writes a 0x40-byte record at [cursor], then advances [rsi+0x548] by 0x130 (at branch target 0x6657419). Element size is 0x130, not 0x58 as previously assumed. The grow path at 0x6657237 computes element count as `(cursor - base) / 0x130` via magic-number division.

## Blocking facts (still open)

B1: VV AtmosphericScattering pass body RVA that reads/drains [pass+0x540]/[pass+0x548] 0x130-byte elements is NOT located. No [reg+0x540] or [reg+0x548] reader of the Sky vector found in the VV builder region (0x55f1450-0x563f594) or VV/RTX pass lambda region (0xbb30000-0xbcd0000).

B2: producer tag=0 dispatch store (the `mov byte ..., 0` selecting Sky slot 0x370 tag 0) and the direct insert call for Atmosphere not isolated in 0x53e2c00/0x5376a00 listings.

B3: all 31 Atmosphere field meanings are '-' (no instruction or string names an Atmosphere field). Per BGFX_MAP 6ik, meanings live in the consumer that reads the queued data, not in the visitor case — so finding the drain body (B1) is a prerequisite for B3.

## Approaches tried and FAILED (do NOT redo)

1. `rdis fld 0x548 --max 4000` — full .text scan, 3264 accesses. Found only sky-visitor reads (0x665702f, 0x6657036) plus unrelated stack/writes. NO drain reader in VV region.
2. `rdis fld 0x540 --max 4000` — TRUNCATED at 4000 lines (5410 total). Non-stack pointer-base reads found (e.g. `0x225bae mov rax,[rcx+0x540]`, `0x2851b8 movups xmm0,[rsi+0x540]`, `0x5728a9 lea rax,[rsi+0x540]`) but none are the drain.
3. `rdis fld 0x550 --max 4000` — TRUNCATED at 4000 lines (5320 total). VV region NOT covered.
4. `rdis dis 0x675530` and `0x675980` — both read [rdx+0x548]/[rdx+0x550] with stride-8 elements, but have 0 xrefs in and are NOT stored as qwords anywhere in the binary = dead/unreachable code. NOT the drain.
5. `rdis dis 0xc288880` — endFrame merge for loader pending jobs (calls 0x67591e0 for offsets +0x4C8/+0x710/+0x958/+0xBE8/+0xE60/+0x10C0/+0x1308). Not Atmosphere.
6. `rdis dis 0x67591e0` — per-thread pending merge for loaders (0x18-stride entries). Not Atmosphere.
7. `rdis dis 0x6759740` and `0x6759ea0` — endFrame merge functions (0x10-stride entries). Not Atmosphere.
8. `rdis dis 0x56e9590` and `0x5711150` — generic field-by-field copy functions (copy fields between two objects). Not the drain.
9. `rdis dis 0x6e769c0` — checks "IsActiveShield" property, not a queue drain.
10. `rdis dis 0xc27f940` — generic vector append (8-byte stride). Not the drain.
11. `rdis imm 0x675530` and `0x675980` — 0 hits (not stored as data/qword anywhere).
12. `rdis imm 0x58` — 79367 hits, too many to be useful.
13. `rdis callers 0x5aba5c0` — many callers but none are the Atmosphere drain; the drain doesn't call ThreadLocalObject::get directly (or does so indirectly).
14. `rdis sum 0x66232b0` (endFrame) — field offsets in endFrame don't include +0x540/+0x548/+0x550; endFrame doesn't read the Sky queue directly.

## NEW angles NOT yet tried (in priority order)

1. `rdis imm 0x130` — search for stride-0x130 multiplication/addition in the VV region to find the drain loop.
2. `rdis fld 0x540` completed scan (re-run, full 5410 lines) — look for [reg+0x540] readers with pointer bases in VV region.
3. descscan2/rw over candidate pass bodies in 0x55f1450-0x563f594 (VV builder) for [reg+0x540]/[reg+0x548]/[reg+0x550] reads via lea+offset addressing.
4. Search for `lea reg,[base+0x540]` patterns in the VV builder region.
5. Find who calls the VV AtmosphericScattering pass body — look at VV builder callees from 0x55f1450.
6. At most a few livemem reads only after an rdis finding points at a specific object (brief allows).
7. rdis callers of 0x53e2c00 and 0x5376a00 for tag=0 store + insert call (B2).

## CLOSES?

NO — Blocking fact B1: the VV AtmosphericScattering pass body RVA that drains the queue at pass+0x548 (stride 0x130, base at +0x540, cursor at +0x548, end at +0x550) is not located. Queue layout is now fully proven [V] but no consumer of that queue has been found in static analysis. B2 and B3 remain open as consequences.