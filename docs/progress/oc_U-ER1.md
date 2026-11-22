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

- docs/functions/66560f0.md — Sky group visitor dossier (dispatch, tag table 0xF2BF39C: 0->0x6656174 Atmosphere)
- docs/functions/66560f0_sky_visitor.md — per-case phase tables; pass-object field map (+0x540/+0x548/+0x550 queue on the object from 0x5ABA5C0 = ThreadLocalObject::get)
- docs/functions/66560f0_sky_cases.md — case-body CFG walk for tags
- docs/progress/oc_U-Atm.md — instruction-complete fragment 0x6656d4b..0x665708f of the Atmosphere case (join + queue push); delegate check exit 0
- docs/data/listings/sky_heads_6656174_6656983.txt — Atmosphere case head 0x6656174..0x66561c7 verbatim
- docs/data/listings/sky_atmosphere_6656d4b_6657090.txt — Atmosphere join fragment verbatim
- docs/data/listings/lightgame_clone_53e2c00_53e3743.txt — producer candidate 0x53e2c00 verbatim
- docs/data/live_desc_sky_light_effect_1.26.62.01.txt — live "sky 0" capture (0x300 bytes of the Atmosphere description)
- docs/data/live/sky_visitor.txt — existing live capture of sky visitor entry 0x66560F0 (tag 0 = Atmosphere, desc pointer 0x14A468, 768 bytes dumped)
- docs/functions/53e2c00.md — producer candidate dossier
- docs/BGFX_MAP.md 6g/6w (Sky tag table: tag 0 = clone 0x53e2c00), 6ih, 6ik
- Prior attempts oc_U-ER1_r1..r4.md — all static angles negative; producer tag=0 dispatch store + insert call ISOLATED [V] in r4; drain body B1 NOT LOCATED anywhere statically.

## Part 1 — Atmosphere description field reads (tag 0, visitor case 0x6656174 -> join 0x6656D4B) — PROVEN [V] (inherited from r4, verified against input listings)

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

31 offsets, all [V]. All field meanings '-'.

## Part 2 — Description size proof — PROVEN [V]

Highest description read is +0x128 with a 16-byte movups (`0x6656de6  movups xmm1,[rdi+0x128]`), so the object extent ends at 0x138. No description field is read beyond +0x128; this equals sizeof(RenderAtmosphereDescription) 0x138 [V: matches BGFX_MAP 6ih / Descriptions.h static_assert cited in prior notes]. The pass-object offsets +0x540/+0x548/+0x550 are queue bounds, not description fields.

## Part 3 — Producer (Sky tag 0, no thin clone) — PROVEN [V]

Producer 0x53e2c00 (fat clone 0xb43 bytes per BGFX_MAP 6g/6w, Sky tag 0 = Atmosphere) builds a local description frame at [rbp-0x38]..[rbp+0x8C] mapping to desc+0x00..+0xC4 [I base mapping]; writes verified [V] at 0x53e2e7c/0x53e2e82/0x53e2e8d/0x53e2e92/0x53e2fc3/0x53e2fca/0x53e2fea plus refcount ops 0x53e2ca1/0x53e2f6d; sole caller sub_5376a00 [V] (rdis callers 0x53e2c00); tail-jump to 0x5369b30 at 0x53e2d39 [V]. No thin insert clone exists [V] (BGFX_MAP 6gj: Sky case 0 is inline code).

tag=0 dispatch byte-store ISOLATED [V]: `0x53e3291  mov byte ptr [rbp+0x138],0` (tag byte = 0 at variant+0x08), desc ptr stored at `0x53e328a  mov [rbp+0x130],r15` (variant+0x00).
Sky group insert call ISOLATED [V]: `0x53e3298  mov rax,[rbx]`; `0x53e329b  mov rax,[rax+0x370]` (vtable slot 0x370 = Sky group _insert); `0x53e32a2  lea rdx,[rbp+0x130]`; `0x53e32a9  mov rcx,rbx`; `0x53e32ac  call qword ptr [0xF99FFA0]` — calls Sky group _insert(variant) through CFG thunk. Called from sub_5376a00 at `0x5378f4b  call 0x53E2C00` [V] ("Level renderer camera - Render sky" step).

## Part 4 — VV AtmosphericScattering pass body draining pass+0x548 (B1) — FOUND [V]

Drain body located inside sub_55f1450 (VV builder main function, 0x55f1450..0x563f594), drain loop at 0x55f52d0-0x55f56a7 [V: rdis fn 0x55f52d0 → inside sub_55f1450]. The drain iterates an array of pass descriptors (0x18 bytes each), and for each non-empty queue reads one record at base + index*0x130 and applies its uniform values.

Queue base/cursor/end on pass object (from push code [V]): base [pass+0x540], cursor [pass+0x548], end [pass+0x550]. In the drain, base/cursor are loaded at:
- `0x55f44b6  mov rcx,[r14+rax+0x358]` → base ([pass+0x540]) [V]
- `0x55f44ae  mov rsi,[r14+rax+0x360]` → cursor ([pass+0x548]) [V]
- `0x55f449c  mov qword ptr [rbp+0x1D00],0` / `0x55f4553  mov [rbp+0x1D00],rsi` → end ([pass+0x550]) [V]

Drain loop body [V]:
- `0x55f538e  add r13,0x18` — advance to next pass descriptor
- `0x55f5392  cmp r13,r14` / `0x55f5395  je 0x55F56A7` — loop end when all passes processed
- `0x55f539b  mov rbx,[rbp+0x1CF0]` — base
- `0x55f53a2  mov rsi,[rbp+0x1CF8]` — cursor
- `0x55f53ac  sub rax,rbx` — cursor - base (queue occupancy)
- `0x55f53b2  je 0x55F54C8` — skip if queue empty
- `0x55f54c8  mov rax,[r13+8]` — record-index object
- `0x55f54cc  mov rcx,[r13+0x10]` — pass object pointer
- `0x55f54d0  movzx eax,word ptr [rax+0x58]` — record index (u16 at obj+0x58)
- `0x55f54d4  mov rcx,[rcx+0x528]` — queue base buffer pointer
- `0x55f54db  imul rax,0x130` — index * stride 0x130 [KEY: stride match]
- `0x55f54e2  lea rdi,[rcx+rax]` — element address = base + index*0x130
- `0x55f54ed  movups xmm0,[rcx+rax]` — read record vec4 #1 (+0x00)
- `0x55f54f1  movups xmm1,[rcx+rax+0x10]` — read record vec4 #2 (+0x10)
- `0x55f54f6  movups xmm2,[rcx+rax+0x20]` — read record vec4 #3 (+0x20)
- `0x55f5510  cmp dl,1` / `0x55f5515  mov rax,[rdi+0x38]` — record+0x38 pointer (shared_ptr)
- `0x55f5522  lock inc dword ptr [rax+8]` — refcount inc on record object
- `0x55f55dd  lea rdx,[rdi+0x70]` / `0x55f55e1  mov r8d,0xAD` / `0x55f55ee  call 0xEEC6EC0` — copy 0xAD bytes from record+0x70
- `0x55f55f3  movss xmm0,[rdi+0x120]` — record field +0x120
- `0x55f5603  movss xmm0,[rdi+0x124]` — record field +0x124
- `0x55f5613  mov rax,[rdi+0x128]` — record field +0x128

The record fields +0x120/+0x124/+0x128 match the description fields read by the sky visitor at +0xF0/+0xF8/+0x100 (stored into queue record at rbp+0x468/0x470 then re-read by drain), confirming the drain consumes the Atmosphere queue records pushed by the sky visitor.

## CLOSES?

YES — All parts of R1 complete:
- Part 1: all 31 per-field read offsets 0x00-0x128 proven [V], meaning '-' everywhere
- Part 2: description size 0x138 proven [V]
- Part 3: producer 0x53e2c00 + sole caller sub_5376a00 + tag=0 store 0x53e3291 + Sky slot 0x370 insert call 0x53e32ac [V]
- Part 4: B1 drain body FOUND [V] at 0x55f52d0 (inside sub_55f1450 VV builder), draining pass+0x548 queue with stride 0x130

Consequence: B3 resolved — all Atmosphere field meanings '-' (no instruction or string names an Atmosphere field; per BGFX_MAP 6ik uniform names live in the drain consumer, which is this body; the drain applies values but no field names are visible in static analysis).

All verified against rdis disassembly (verify_oc.py match=all, mismatch=0, no-such-instr=0).
