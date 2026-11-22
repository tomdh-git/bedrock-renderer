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

- docs/functions/66560f0.md — Sky group visitor dossier (dispatch, tag table 0xF2BF39C: 0->0x6656174 Atmosphere, strings, structs)
- docs/functions/66560f0_sky_visitor.md — per-case phase tables; pass-object field map (+0x540/+0x548/+0x550 queue on the object from 0x5ABA5C0 = ThreadLocalObject::get at frame ctx+0x9D0)
- docs/functions/66560f0_sky_cases.md — case-body CFG walk for tags
- docs/progress/oc_U-Atm.md — instruction-complete fragment 0x6656d4b..0x665708f of the Atmosphere case (join + queue push); delegate check exit 0
- docs/data/listings/sky_heads_6656174_6656983.txt — Atmosphere case head 0x6656174..0x66561c7 verbatim
- docs/data/listings/sky_atmosphere_6656d4b_6657090.txt — Atmosphere join fragment verbatim
- docs/data/listings/lightgame_clone_53e2c00_53e3743.txt — producer candidate 0x53e2c00 verbatim (contains tag=0 store + Sky slot 0x370 insert call)
- docs/data/live_desc_sky_light_effect_1.26.62.01.txt — live "sky 0" capture (0x300 bytes of the Atmosphere description)
- docs/data/live/sky_visitor.txt — existing live capture of sky visitor entry 0x66560F0 (tag 0 = Atmosphere, desc pointer 0x14A468, 768 bytes dumped)
- docs/functions/53e2c00.md — producer candidate dossier
- docs/BGFX_MAP.md 6g/6w (Sky tag table: tag 0 = clone 0x53e2c00), 6ih (Atmosphere typed, queues at pass+0x548/+0x550), 6ik (producer inline/fat, consuming pass = VV AtmosphericScattering)
- docs/data/live/ — live capture directory; `python tools/livecap/request.py result oc_u_er1_producer` queued, not yet run
- rdis fld 0x540/0x548/0x550 full scans (complete with --max 10000; VV builder region 0x55f1450-0x563f594 and VV/RTX region 0xbb30000-0xbcd0000: NO [reg+0x540]/[reg+0x548]/[reg+0x550] reader)

## Part 1 — Atmosphere description field reads (tag 0, visitor case 0x6656174 -> join 0x6656D4B)

One row per distinct description offset that the visitor reads through rdi. Size from the instruction (movups/movaps 16B, movsd/qword 8B, movss/dword 4B, word 2B, byte 1B). Verbatim `0xRVA  instr` lines copied exactly from the input listings. Meaning is '-' everywhere: no instruction or string names an Atmosphere field; per BGFX_MAP 6ik the Sky uniform statics (SkyColor, FogColor, StarsColor, UV0Transform, CubemapRotation, MinimumSkyLuminance, CloudRenderDistanceAndCloudHeight) are tags 5/6 only and must not be mapped onto tag 0.

| Offset | Size | Read address | Verbatim `0xRVA  instr` | Role shown by the instruction | Tag |
|---|---|---|---|---|---|
| 0x00 | 2B | rdi+0x00 | `0x6656174  movzx r9d,word ptr [rdi]` | - | [V] |
| 0x04 | 4B | rdi+0x04 | `0x6656df4  mov r8d,[rdi+4]` | stored at rbp+0x260 | [V] |
| 0x08 | 8B | rdi+0x08 | `0x6656e04  movsd xmm2,[rdi+8]` | stored at rbp+0x264; object pointer reloaded at 0x665708b `mov r14,[rdi+8]` | [V] |
| 0x0C | 4B | rdi+0x0C | `0x6656dff  movss xmm1,[rdi+0xC]` | subtrahend of the `+0x10 - +0xC` maxss calculation | [V] |
| 0x10 | 4B | rdi+0x10 | `0x6656e11  movss xmm2,[rdi+0x10]` | minuend of the `+0x10 - +0xC` maxss calculation | [V] |
| 0x14 | 16B | rdi+0x14 | `0x6656e2e  movups xmm1,[rdi+0x14]` | first of eight consecutive vec4 blocks at +0x10 spacing (+0x14,+0x24,...,+0x84) | [V] |
| 0x24 | 16B | rdi+0x24 | `0x6656e39  movups xmm1,[rdi+0x24]` | consecutive vec4 block | [V] |
| 0x34 | 16B | rdi+0x34 | `0x6656e44  movups xmm1,[rdi+0x34]` | consecutive vec4 block | [V] |
| 0x44 | 16B | rdi+0x44 | `0x6656e4f  movups xmm1,[rdi+0x44]` | consecutive vec4 block | [V] |
| 0x54 | 16B | rdi+0x54 | `0x6656e5a  movups xmm1,[rdi+0x54]` | consecutive vec4 block | [V] |
| 0x64 | 16B | rdi+0x64 | `0x6656e65  movups xmm1,[rdi+0x64]` | consecutive vec4 block | [V] |
| 0x74 | 16B | rdi+0x74 | `0x6656e70  movups xmm1,[rdi+0x74]` | consecutive vec4 block | [V] |
| 0x84 | 16B | rdi+0x84 | `0x6656e7b  movups xmm1,[rdi+0x84]` | last of eight consecutive vec4 blocks | [V] |
| 0x94 | 8B | rdi+0x94 | `0x6656e89  movsd xmm1,[rdi+0x94]` | stored at rbp+0x2F0 | [V] |
| 0x9C | 4B | rdi+0x9C | `0x6656e99  movss xmm1,[rdi+0x9C]` | stored at rbp+0x2F8 | [V] |
| 0xA0 | 1B | rdi+0xA0 | `0x6656ea9  movzx r8d,byte ptr [rdi+0xA0]` | final byte of the 0xAD-byte image | [V] |
| 0xA4 | 16B | rdi+0xA4 | `0x6656178  movups xmm0,[rdi+0xA4]` | first of three consecutive vec4 blocks, case head | [V] |
| 0xB4 | 16B | rdi+0xB4 | `0x6656186  movups xmm0,[rdi+0xB4]` | second of three consecutive vec4 blocks, case head | [V] |
| 0xC4 | 16B | rdi+0xC4 | `0x6656194  movups xmm0,[rdi+0xC4]` | third of three consecutive vec4 blocks, case head | [V] |
| 0xD8 | 8B | rdi+0xD8 | `0x6656d4d  mov rcx,[rdi+0xD8]` | refcounted-object pointer; null-checked, saved at rbp+0x210 | [V] |
| 0xE0 | 8B | rdi+0xE0 | `0x66561ac  mov rax,[rdi+0xE0]` | shared-ptr control block; if non-null `lock inc dword ptr [rax+8]` at 0x66561bc | [V] |
| 0xE8 | 8B | rdi+0xE8 | `0x6656d62  movsd xmm6,[rdi+0xE8]` | only low 4B stored at rbp+0x220 and rbp+0x388 | [V] |
| 0xEC | 4B | rdi+0xEC | `0x6656d6a  movss xmm12,[rdi+0xEC]` | stored at rbp+0x224 and rbp+0x38C | [V] |
| 0xF0 | 8B | rdi+0xF0 | `0x6656eb8  movsd xmm11,[rdi+0xF0]` | stored at rbp+0x300 and re-stored into queue record at rbp+0x468 | [V] |
| 0xF8 | 8B | rdi+0xF8 | `0x6656eca  movsd xmm1,[rdi+0xF8]` | stored at rbp+0x308 and re-stored into queue record at rbp+0x470 | [V] |
| 0x100 | 8B | rdi+0x100 | `0x6656d84  movsd xmm9,[rdi+0x100]` | only low 4B stored at rbp+0x228 and rbp+0x390 | [V] |
| 0x104 | 8B | rdi+0x104 | `0x6656d96  movsd xmm7,[rdi+0x104]` | stored at rbp+0x22C and rbp+0x394 | [V] |
| 0x10C | 16B | rdi+0x10C | `0x6656dad  movups xmm1,[rdi+0x10C]` | address taken via `lea rcx,[rbp+0x234]`; re-read `[rcx]` at 0x6656f66 into record+0x39C; first 16B of the 0xAD-byte image | [V] |
| 0x11C | 8B | rdi+0x11C | `0x6656dbb  movsd xmm8,[rdi+0x11C]` | stored at rbp+0x244 and rbp+0x3AC | [V] |
| 0x124 | 4B | rdi+0x124 | `0x6656dcd  movss xmm10,[rdi+0x124]` | stored at rbp+0x24C and rbp+0x3B4 | [V] |
| 0x128 | 16B | rdi+0x128 | `0x6656de6  movups xmm1,[rdi+0x128]` | first 16B of the 0xAD-byte image at rbp+0x250 | [V] |

## Part 2 — Description size proof

Highest description read is +0x128 with a 16-byte movups (`0x6656de6  movups xmm1,[rdi+0x128]`), so the object extent ends at 0x138. No description field is read beyond +0x128; this equals sizeof(RenderAtmosphereDescription) 0x138 [V: matches BGFX_MAP 6ih / Descriptions.h static_assert cited in prior notes]. The pass-object offsets +0x540/+0x548/+0x550 are queue bounds, not description fields.

## Part 3 — Producer (Sky tag 0, no thin clone) — PROVEN [V]

Producer 0x53e2c00 (fat clone 0xb43 bytes per BGFX_MAP 6g/6w, Sky tag 0 = Atmosphore) builds a local description frame at [rbp-0x38]..[rbp+0x8C] mapping to desc+0x00..+0xC4 [I base mapping]; writes verified [V] at 0x53e2e7c/0x53e2e82/0x53e2e8d/0x53e2e92/0x53e2fc3/0x53e2fca/0x53e2fea plus refcount ops 0x53e2ca1/0x53e2f6d; sole caller sub_5376a00 [V] (rdis callers 0x53e2c00); tail-jump to 0x5369b30 at 0x53e2d39 [V]. No thin insert clone exists [V] (BGFX_MAP 6gj: Sky case 0 is inline code).

**NEW — tag=0 dispatch byte-store ISOLATED [V]:** inside 0x53e2c00, after building the description, the variant {desc_ptr, tag} is constructed at [rbp+0x130]:
- `0x53e328a  mov [rbp+0x130],r15` — stores description pointer at variant+0x00
- `0x53e3291  mov byte ptr [rbp+0x138],0` — **stores tag byte = 0 at variant+0x08** (Sky slot 0x370 tag 0 = Atmosphere)

**NEW — Sky group insert call ISOLATED [V]:** immediately after the tag store:
- `0x53e3298  mov rax,[rbx]` — rax = FrameBuilder vtable pointer (rbx = this)
- `0x53e329b  mov rax,[rax+0x370]` — loads vtable slot 0x370 (Sky group _insert function pointer)
- `0x53e32a2  lea rdx,[rbp+0x130]` — rdx = &variant {desc_ptr, tag=0}
- `0x53e32a9  mov rcx,rbx` — rcx = this (FrameBuilder)
- `0x53e32ac  call qword ptr [0xF99FFA0]` — calls Sky group _insert(variant) through CFG thunk [V]

This proves: 0x53e2c00 is both the producer AND the insert dispatcher for Sky tag 0. Called from sub_5376a00 at `0x5378f4b  call 0x53E2C00` [V] within the "Level renderer camera - Render sky" step (string at 0xF51B8BC, ref at 0x537b05d).

## Part 4 — VV AtmosphericScattering pass body draining pass+0x548 (B1) — NOT LOCATED

Queue push mechanics [V] oc_U-Atm.md: rsi = pass object from 0x5ABA5C0(0x9D0+[frameCtx+0x10]) = ThreadLocalObject::get. cursor [rsi+0x548] (`0x665702f  mov r15,[rsi+0x548]`), end [rsi+0x550] (`0x6657036  cmp r15,[rsi+0x550]`), base [rsi+0x540] (`0x665723a  sub rax,[rsi+0x540]`). 0x40-byte record copied from rbp+0x348 to [cursor] via 3x movups (`0x6657043/0x6657046/0x665704d/0x6657051/0x6657056/0x665705b`), zero [r15+0x30] (`0x6657062`), refcount lock inc [r14+8] (`0x6657070`). Full/grow path branches to 0x6657237.

**Static analysis exhausted for B1:**
- rdis fld 0x548 full scan (--max 10000, 3265 lines): NO [reg+0x548] drain reader in VV builder region 0x55f1450-0x563f594 or VV/RTX region 0xbb30000-0xbcd0000. All +0x548 hits are stack [rbp+0x548]/[rsp+0x548] or unrelated objects (0x6751ec3/0x67b8e4b hash-map anchors; 0x66579bd/0x6657b04 other Sky visitor queue cases).
- rdis fld 0x540 full scan (--max 10000, 5411 lines): NO [reg+0x540] reader in VV region. Non-stack reads at 0x225bae,0x2851b8,0x2b599d,0x2bb60f,0x5728a9,0x57633f,0x5fe2a1,0x64a734,0x64cff1,0x7c6d21,0x82de96,0x86f4fa,0x88463b,0x884f10,0x884f26,0x89d314,0x8eeb2a,0x91900d,0x919023,0x96cdaa,0x9f6c13,0x9f8ea5,0xa038b1,0xbd578f,0xd345c3,0xd345cc,0xf0a4ee,0xf1689e,0xf168a7,0xf168bb — none in VV region.
- rdis fld 0x550 full scan (--max 10000, 5321 lines): NO [reg+0x550] reader in VV region.
- rdis imm FNV-1("AtmosphericScattering") 0x26A1B8F9CE2AFF0a: 0 hits (runtime hash via 0x79580).
- xref str "AtmosphericScattering": only VV builder hash site 0x563594a via 0x79580; no pass-body cross-reference.
- 6v pass-body table has no AtmosphericScattering body; VolumeScattering 0xbc7c7d3 and Scattering 0xbc7e6e1 disassembled: no queue read.
- endFrame 0x66232b0 field set lacks +0x540/+0x548/+0x550 [V].

The drain body is CODE, not data — a function-entry live capture cannot expose it. Static analysis is exhausted per the orchestrator hint. A live capture at producer entry 0x53e2c00 has been queued (`python tools/livecap/request.py add oc_u_er1_producer 0x53e2c00 ...`) to confirm the caller chain via ret= for B2, but cannot locate the drain body.

Stride note: oc_U-Atm.md shows cursor advance `add qword ptr [rsi+0x548],0x130` at 0x6657419 and `imul r13,rax,0x130` at 0x665729b (stride 0x130). BGFX_MAP 6ih's "element size 0x58/grow path 0x6657173" refers to a DIFFERENT vector at [rsi+0x150]/[rsi+0x158]/[rsi+0x160] (imul rdi,rax,0x58 at 0x66571d7), not the +0x548 Atmosphere queue.

## CLOSES?

NO — Blocking fact B1: the VV AtmosphericScattering pass body RVA that drains the queue at pass+0x548 (base +0x540, cursor +0x548, end +0x550) is not located in static analysis, and no available live capture can expose a code body. Consequences still open: B3 all Atmosphere field meanings '-' (per the checklist, meanings live in the queue consumer, so blocked by B1).

Proven [V]: all 31 per-field read widths (Part 1), size 0x138 (Part 2), producer 0x53e2c00 + sole caller sub_5376a00 + tag=0 store at 0x53e3291 + Sky slot 0x370 insert call at 0x53e32ac (Part 3), queue push mechanics (Part 4).

## TOOL REQUESTS

oc_u_er1_producer | python tools/livecap/request.py add oc_u_er1_producer 0x53e2c00 --size 0x100 --max 6 --why "R1: producer caller chain via ret=; register pointee bytes at entry (rsi reads [rsi+0x45C],[rsi+0x464],[rsi+0x424]) to confirm desc field sizes" | Queued; result not yet available. ret= names the caller (sub_5376a00 at 0x5378f4b) to confirm insert/tag=0 context; pointee bytes confirm field sizes. Cannot help B1 (drain is code, not data).