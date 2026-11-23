## NEXT
DONE

# oc_U-ER1 — R1 Atmosphere (Sky tag 0): per-field meaning, producer (no thin clone), VV AtmosphericScattering pass body draining pass+0x548

## Scope (from the checklist line R1; BGFX_MAP 6ih, 6ik)

Pending parts of R1:
1. per-field meaning of RenderAtmosphereDescription (read-widths only; tag 0 — the Sky statics SkyColor/FogColor/... belong to tags 5/6, NOT tag 0, and are not mapped onto Atmosphere)
2. the producer: Atmosphere has NO thin insert clone; the Sky-group insert with tag 0 that builds it
3. the VV AtmosphericScattering pass body that drains the queue at pass+0x548

Explicitly out of scope: tags 5/6 (Sky/Stars) statics; anything beyond read-widths.

## Status — proven parts are NOT redone

Inherited from oc_U-ER1_r1..r5 (verified earlier, verify_oc.py match=all) and NOT repeated here:
- Part 1: all 31 description read offsets 0x00..0x128, sizes from the instructions [V] — table in Part A below (rows only, no re-derivation).
- Part 2: description size 0x138 [V] (highest read +0x128 movups 16B → extent ends at 0x138; no description field read beyond +0x128).
- Part 3: producer 0x53e2c00 (fat clone, 0xb43 bytes), Sky tag 0 = Atmosphere, no thin insert clone [V]; tag=0 dispatch store and Sky slot 0x370 insert call isolated [V]; sole caller sub_5376a00 [V].
- Part 4 queue mechanics: pass object [pass+0x540]=begin, [pass+0x548]=cursor/end, [pass+0x550]=capacity, 0x58-byte record pushed to [cursor] [V] (0x665702f `mov r15,[rsi+0x548]`, `0x6657036 cmp r15,[rsi+0x550]`, `0x665705b movups [r15],xmm0`, `0x6657062 movups [r15+0x30],xmm0`).

Still open: Part 3b — the VV AtmosphericScattering pass body RVA that drains the queue at pass+0x548 is not located statically (Part D below).

## Input data read for this run (not regenerated)

- docs/data/live/oc_u_er1_producer.txt — live capture of producer entry 0x53e2c00, kind=regs, size=0x100, 5 samples (produced 2026-11-22 14:45; already delivered, NOT re-requested).
- docs/functions/53e2c00.md — producer dossier (argument map: rcx=this, rdx/r8/r9 only forwarded).
- docs/data/listings/sky_atmosphere_6656d4b_6657090.txt — Atmosphere join fragment verbatim (push to [rsi+0x548]).
- docs/data/listings/sky_heads_6656174_6656983.txt — Atmosphere case head verbatim.
- docs/BGFX_MAP.md 6g/6w/6ih/6ik/6gj/6gq.

## Part A — Atmosphere description field reads (tag 0, visitor case 0x6656174 -> join 0x6656D4B) — table

One row per distinct description offset read through rdi. Size from the instruction (movups/movaps 16B, movsd/qword 8B, movss/dword 4B, word 2B, byte 1B). Verbatim `0xRVA  instr` lines copied exactly from the input listings. Meaning is '-' everywhere: no instruction or string names an Atmosphere field; per BGFX_MAP 6ik the Sky uniform statics (SkyColor, FogColor, StarsColor, UV0Transform, CubemapRotation, MinimumSkyLuminance, CloudRenderDistanceAndCloudHeight) are tags 5/6 only and must not be mapped onto tag 0.

| Offset | Size | Read address | Verbatim `0xRVA  instr` | Meaning | Tag |
|---|---|---|---|---|---|
| 0x00 | 2B | rdi+0x00 | `0x6656174  movzx r9d,word ptr [rdi]` | - | [V] |
| 0x04 | 4B | rdi+0x04 | `0x6656df4  mov r8d,[rdi+4]` | - | [V] |
| 0x08 | 8B | rdi+0x08 | `0x6656e04  movsd xmm2,[rdi+8]` | - | [V] |
| 0x0C | 4B | rdi+0x0C | `0x6656dff  movss xmm1,[rdi+0xC]` | - | [V] |
| 0x10 | 4B | rdi+0x10 | `0x6656e11  movss xmm2,[rdi+0x10]` | - | [V] |
| 0x14 | 16B | rdi+0x14 | `0x6656e2e  movups xmm1,[rdi+0x14]` | - | [V] |
| 0x24 | 16B | rdi+0x24 | `0x6656e39  movups xmm1,[rdi+0x24]` | - | [V] |
| 0x34 | 16B | rdi+0x34 | `0x6656e44  movups xmm1,[rdi+0x34]` | - | [V] |
| 0x44 | 16B | rdi+0x44 | `0x6656e4f  movups xmm1,[rdi+0x44]` | - | [V] |
| 0x54 | 16B | rdi+0x54 | `0x6656e5a  movups xmm1,[rdi+0x54]` | - | [V] |
| 0x64 | 16B | rdi+0x64 | `0x6656e65  movups xmm1,[rdi+0x64]` | - | [V] |
| 0x74 | 16B | rdi+0x74 | `0x6656e70  movups xmm1,[rdi+0x74]` | - | [V] |
| 0x84 | 16B | rdi+0x84 | `0x6656e7b  movups xmm1,[rdi+0x84]` | - | [V] |
| 0x94 | 8B | rdi+0x94 | `0x6656e89  movsd xmm1,[rdi+0x94]` | - | [V] |
| 0x9C | 4B | rdi+0x9C | `0x6656e99  movss xmm1,[rdi+0x9C]` | - | [V] |
| 0xA0 | 1B | rdi+0xA0 | `0x6656ea9  movzx r8d,byte ptr [rdi+0xA0]` | - | [V] |
| 0xA4 | 16B | rdi+0xA4 | `0x6656178  movups xmm0,[rdi+0xA4]` | - | [V] |
| 0xB4 | 16B | rdi+0xB4 | `0x6656186  movups xmm0,[rdi+0xB4]` | - | [V] |
| 0xC4 | 16B | rdi+0xC4 | `0x6656194  movups xmm0,[rdi+0xC4]` | - | [V] |
| 0xD8 | 8B | rdi+0xD8 | `0x6656d4d  mov rcx,[rdi+0xD8]` | - | [V] |
| 0xE0 | 8B | rdi+0xE0 | `0x66561ac  mov rax,[rdi+0xE0]` | - | [V] |
| 0xE8 | 8B | rdi+0xE8 | `0x6656d62  movsd xmm6,[rdi+0xE8]` | - | [V] |
| 0xEC | 4B | rdi+0xEC | `0x6656d6a  movss xmm12,[rdi+0xEC]` | - | [V] |
| 0xF0 | 8B | rdi+0xF0 | `0x6656eb8  movsd xmm11,[rdi+0xF0]` | - | [V] |
| 0xF8 | 8B | rdi+0xF8 | `0x6656eca  movsd xmm1,[rdi+0xF8]` | - | [V] |
| 0x100 | 8B | rdi+0x100 | `0x6656d84  movsd xmm9,[rdi+0x100]` | - | [V] |
| 0x104 | 8B | rdi+0x104 | `0x6656d96  movsd xmm7,[rdi+0x104]` | - | [V] |
| 0x10C | 16B | rdi+0x10C | `0x6656dad  movups xmm1,[rdi+0x10C]` | - | [V] |
| 0x11C | 8B | rdi+0x11C | `0x6656dbb  movsd xmm8,[rdi+0x11C]` | - | [V] |
| 0x124 | 4B | rdi+0x124 | `0x6656dcd  movss xmm10,[rdi+0x124]` | - | [V] |
| 0x128 | 16B | rdi+0x128 | `0x6656de6  movups xmm1,[rdi+0x128]` | - | [V] |

31 offsets, all [V]; all field meanings '-'. Confirmed against the exe (spot check: `0x6656174`, `0x6656178`, `0x6656186`, `0x6656194` re-disassembled identically).

## Part B — Description size proof — PROVEN [V] (inherited)

Highest description read is +0x128 with a 16-byte movups (`0x6656de6  movups xmm1,[rdi+0x128]`), so the object extent ends at 0x138. No description field is read beyond +0x128; this equals sizeof(RenderAtmosphereDescription) 0x138 [V: matches BGFX_MAP 6ih / Descriptions.h static_assert cited in prior notes]. The pass-object offsets +0x540/+0x548/+0x550 are queue bounds, not description fields.

## Part C — Producer (Sky tag 0, no thin clone) — PROVEN [V], caller chain now [V live]

Producer 0x53e2c00 builds the description on its own stack ([rbp-0x38]..[rbp+0x8C] mapping to desc+0x00..+0xC4 [I base mapping]) and is called as `0x5378f4b  call 0x53E2C00` with return address 0x5378F50, then `0x5378f50  nop` [V verbatim]. Prologue: `0x53e2c3c  mov rdi,rcx` (this = FrameBuilder), `0x53e2c3f  mov rsi,[rcx+8]` (source = sky settings) [V verbatim] — so NO entry register holds the description; it is stack-built inside the producer.

Verified writes into the local description frame [V verbatim]:
- `0x53e2e7c  mov word ptr [rbp-0x38],0` → desc+0x00 (2B); `0x53e2e82  mov [rbp-0x34],eax` → desc+0x04 (4B)
- `0x53e2e8d  movsd [rbp-0x30],xmm0` → desc+0x08 (8B), later overwritten by `0x53e2fa9  movsd xmm0,[rsi+0x45C]` (8B source read)
- `0x53e2e92  mov dword ptr [rbp-0x28],0x43FA0000` → desc+0x0C (4B), later overwritten by `0x53e2fb6  movss xmm0,[rsi+0x464]` (4B source read)
- `0x53e2fc3  movups xmm0,[rsi+0x424]` then `0x53e2fca  movups [r12],xmm0` → desc+0x74 (16B source read)
- `0x53e2fea  movups [rbp+0x4C],xmm0` → desc+0x84 (16B); tail `0x53e2d39  jmp 0x5369B30` [V]

tag=0 dispatch store + Sky insert (variant {desc_ptr, tag=0} at [rbp+0x130]/[rbp+0x138]) [V verbatim]:
- `0x53e328a  mov [rbp+0x130],r15` — description pointer at variant+0x00
- `0x53e3291  mov byte ptr [rbp+0x138],0` — tag byte = 0 at variant+0x08 (Sky slot 0x370 tag 0 = Atmosphere)
- `0x53e3298  mov rax,[rbx]`; `0x53e329b  mov rax,[rax+0x370]` (vtable slot 110 = Sky group _insert); `0x53e32a2  lea rdx,[rbp+0x130]`; `0x53e32a9  mov rcx,rbx`; `0x53e32ac  call qword ptr [0xF99FFA0]` — calls Sky group _insert(variant) through CFG thunk [V]

No thin insert clone exists [V] (BGFX_MAP 6gj: Sky case 0 is inline code).

**LIVE caller chain [V live]:** docs/data/live/oc_u_er1_producer.txt, capture of producer entry 0x53e2c00, kind=regs size=0x100:
- line 3: `CALLER ret=0x5378F50 first_hit=1`; lines 4–8 (RCX/RDX/R8/R9, RDX hit=51) all show the same `ret=0x5378F50`.
- ret=0x5378F50 is the return address of `0x5378f4b  call 0x53E2C00` (next instruction `0x5378f50  nop` [V verbatim]) — so every sample entered the producer from the same call site in the "Render sky" step. This names the producer's caller chain live, confirming the sole-caller fact [V live docs/data/live/oc_u_er1_producer.txt:3].

Entry-register pointees (none holds the description):
- RCX=0x14ac30 (+0x00 qword = 0x7FF614E291A0, a vtable/code pointer — this), RDX=0x14b1a0, R8=0x14b0b8, R9=0x7FFE4000 (SharedUserData, all zero in the dumped window).
- rsi = [rcx+8] (0x53e2c3f) is the source object; its fields [rsi+0x424] (16B), [rsi+0x45C] (8B), [rsi+0x464] (4B) lie beyond the 0x100-byte dump window (offsets > 0xFF), so they are not visible in the capture; their sizes were already proven statically above [V]. No description bytes exist at capture entry, so the capture adds the caller chain [V live] and no new description field rows — Part A rows stand on static [V] proof only.

## Part D — VV AtmosphericScattering pass body draining pass+0x548 — NOT LOCATED [?]

Queue begin/cursor/end on the pass object (+0x540/+0x548/+0x550) and the push mechanics are proven [V] (Part Status above), but the pass BODY RVA that reads the queue and drains its 0x58-byte elements is unknown.

The element size is 0x58 [V] (the push copies 0x40B `[r15]+0x00/0x10/0x20/0x30` then zeroes `[r15+0x30]`; the shared-tail/compactor uses stride 0x58: `0x666cc86 add rax,0x58`, `0x666cc8a add rdi,0x58`, `0x666cc8e cmp rdi,r15`). Note: the earlier "stride 0x130" in some notes refers to builder pass DESCRIPTORS (`0x55f54db  imul rax,0x130` over a [r13+0x10]+0x528 table), NOT the per-frame queue element — the two are unrelated.

### Route 1 — stride walkers / queue-bound readers (`rdis imm` / `fld 0x540/0x548/0x550`)

Scanned for readers of [reg+0x540]/[reg+0x548]/[reg+0x550] and for `add reg,0x58`/`cmp reg,[...+0x550]` loop walkers. Every [reg+0x540/+0x548/+0x550] hit is a small-string buffer (ptr/size/cap pattern: e.g. `mov qword ptr [rsi+0x558],0xF`), a shared_ptr release (`0x6755a7  mov rdi,[rdx+0x548]` / `0x824c75  mov rdi,[rsi+0x548]` / `0x836e48  mov rdi,[rsi+0x548]` then refcount decrement), a destructor (0x67e1c0, 0x64ce30, 0x2bb60f), or a vcall dispatch — NONE iterates the queue reading record fields at offsets 0x00..0x57. No `mov reg,[...+0x540]` begin-load followed by a 0x58-stride field-read loop exists in .text. Per the 2026-11-22 orchestrator hint, the consumer may use rebased offsets (queue object by pointer), so a direct [reg+0x548] scan cannot rule it out, but no such rebased drain was found either.

### Route 2 — name string "AtmosphericScattering" → pass declaration → vtable → execute body

`rdis str "AtmosphericScattering"` → string at f5b4998, referenced by sub_55f1450+0x444fa (0x55f58f6 `mov rax,[0x129C96B8]` → stored `[rbp+0x2440]`, then `call 0x567B570`) and sub_57d5880+0x155. `sub_567B570` is an FNV-1a name-lookup helper (constants 0xCBF29CE484222325 / 0x100000001B3 visible at `0x567b63a mov r9,0xCBF29CE484222325`, `0x567b644 mov r10,0x100000001B3`) that registers "AtmosphericScattering" as a uniform/resource NAME, NOT a pass object with a vtable. Candidate vtables near the builder (0xF440770, 0xF25C770 installed by `0xbc38ab0`) were dumped: 0xF440770 slot6 = sub_bc38c20 (a view-matrix setup body writing s_ctx view rects, not a queue drain), 0xF25C770 = refcount-only (slot1 = release thunk `jmp qword ptr [0xF9A8A78]`). No AtmosphericScattering pass execute body located.

### Route 3 — visitor drain legs (0x666aca0 / 0x666cc50 / sub_66b2b30)

`sub_666aca0` is the tag-dispatch insert function (jump table 0xF2BF49C, tags 0-8, same `0x5ABA5C0(0x9D0+[r12+0x10])` pass lookup). It contains a 0x58-stride compactor at `sub_666cc50` (`0x666cc50 mov rcx,[rdi]` … `0x666cc86 add rax,0x58`, `0x666cc8a add rdi,0x58`, `0x666cc8e cmp rdi,r15`), but it drains the queue at `rsi+0x78`/`rsi+0x80`/`rsi+0x88` — NOT `rsi+0x548`/`rsi+0x550`. `sub_666aca0` never touches +0x548/+0x550 (verified by grepping its disassembly: touches +0x78/+0x80/+0x88/+0x330/+0x338/+0x340/+0x10/+0xC only). `sub_66b2b30` (tag-0 delivery candidate) is called from `sub_666aca0` at `0x666aea7  call 0x66B2B30` inside a specific tag handler, not as a general queue drain. So tag 0's Atmosphere queue at pass+0x548 has no located consumer here either.

### Live data cannot close this

The delivered capture targets the producer entry (0x53e2c00); its ret= names the producer's caller only. A regs-at-entry capture dumps register data, not code bodies, and no drain-body entry RVA is known to queue a capture for. A live capture cannot name a code body. No new capture is queued: the missing fact is the drain body RVA itself.

## What the live capture added vs. what it could not

Added [V live]: producer caller chain — `CALLER ret=0x5378F50` on every sample of oc_u_er1_producer.txt = `0x5378f4b  call 0x53E2C00`, ret 0x5378F50 (`0x5378f50  nop`), i.e. the "Render sky" call site, all from one caller (RDX hit=51 across samples). Confirms Part C caller statically and live.
Could not add: no description bytes at producer entry (description is stack-built; rsi=[rcx+8] source object reads at +0x424/+0x45C/+0x464 are outside the 0x100-byte window), so no field meanings or sizes beyond the static [V] proof; and no drain-body RVA (code, not data).

## TOOL REQUESTS

None — oc_u_er1_producer is already delivered (docs/data/live/oc_u_er1_producer.txt) and is not re-requested. No new capture is queued: the drain body is code (a function-entry regs capture cannot expose it) and no drain entry RVA is known, so there is no meaningful target to request; the missing fact is the drain body RVA itself, named under CLOSES? below.

## CLOSES?

NO — single blocking fact: the VV AtmosphericScattering pass body RVA that drains the queue at pass+0x548 (begin +0x540, cursor +0x548, end +0x550, stride 0x58, 0x58-byte Atmosphere records) is not known. Static analysis is exhausted (routes 1/2/3 all attempted above; no `[reg+0x540]` begin-load followed by a 0x58-stride record-field read loop; no AtmosphericScattering pass execute body via vtable; sub_666aca0's compactor drains the unrelated +0x78 queue). No existing or requestable live capture can name a code body without a drain entry RVA. Everything else in R1 is proven [V] (Part A: 31/31 field reads; Part B: size 0x138; Part C: producer 0x53e2c00, tag=0 store 0x53e3291, Sky insert call 0x53e32ac, caller chain ret=0x5378F50 [V live]). Field meanings remain '-' (no instruction or string names an Atmosphere field; per BGFX_MAP 6ik names live in the queue consumer, blocked by this same unknown drain body).
