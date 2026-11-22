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
- docs/functions/66560f0.md — Sky visitor dispatcher + jump table (table 0xF2BF39C, tag 0 -> 0x6656174)
- docs/functions/66560f0_sky_visitor.md — Sky visitor register map (rdi = description, rsi = frame ctx)
- docs/progress/oc_U-Atm.md — instruction-complete fragment 0x6656d4b..0x6657090 of the Atmosphere case (join + queue into pass+0x548); delegate check exit 0
- docs/data/listings/sky_heads_6656174_6656983.txt — Atmosphere case head 0x6656174..0x66561c7 verbatim
- docs/data/listings/sky_atmosphere_6656d4b_6657090.txt — Atmosphere join fragment verbatim
- docs/data/listings/lightgame_clone_53e2c00_53e3743.txt — producer candidate 0x53e2c00 verbatim
- docs/data/live_desc_sky_light_effect_1.26.62.01.txt — live "sky 0" capture (0x300 bytes of the Atmosphere description)
- docs/functions/53e2c00.md — producer candidate dossier
- docs/BGFX_MAP.md 6g (Sky tag table: tag 0 = clone 0x53e2c00), 6ih, 6ik

## Method

One row per distinct description offset that the visitor reads through rdi; size from the instruction (movups/movaps 16B, movsd/qword 8B, movss/dword 4B, word 2B, byte 1B); verbatim `0xRVA  instr` lines copied exactly from the input listings; meaning only where an instruction or string shows it, else '-'. The pass-object offsets 0x548/0x550 are queue bounds (begin/end), not description fields. The fragment at 0x6656d4b copies desc fields into rbp locals (0x210..0x30F) and builds a 0x58-byte record at 0x348 pushed to [rsi+0x548] (stride table, cmp r15,[rsi+0x550]) — those are queue mechanics, not desc field meanings.

## Part 1 — Atmosphere description field reads (tag 0, visitor case 0x6656174 -> join 0x6656D4B)

Case head 0x6656174 (rdi = desc, from sky_heads listing):

| Name | Size | Offset | Read/store address | Verbatim `0xRVA  instr` | Meaning | Tag |
|---|---|---|---|---|---|---|
| mType | 2B | 0x00 | rdi+0x00 | `0x6656174  movzx r9d,word ptr [rdi]` | u16 type/kind word | [V] |
| mBlockA4 | 16B | 0xA4 | rdi+0xA4 | `0x6656178  movups xmm0,[rdi+0xA4]` | first of three consecutive vec4 blocks | [V] |
| mBlockB4 | 16B | 0xB4 | rdi+0xB4 | `0x6656186  movups xmm0,[rdi+0xB4]` | second of three consecutive vec4 blocks | [V] |
| mBlockC4 | 16B | 0xC4 | rdi+0xC4 | `0x6656194  movups xmm0,[rdi+0xC4]` | third of three consecutive vec4 blocks | [V] |
| mSharedCtrl | 8B | 0xE0 | rdi+0xE0 | `0x66561ac  mov rax,[rdi+0xE0]` | shared-ptr control block; if non-null `lock inc dword ptr [rax+8]` at 0x66561bc | [V] |

Join fragment 0x6656d4b..0x6656de6 (rdi = desc, from oc_U-Atm.md / listing):

| Name | Size | Offset | Read/store address | Verbatim `0xRVA  instr` | Meaning | Tag |
|---|---|---|---|---|---|---|
| mDword4 | 4B | 0x04 | rdi+0x04 | `0x6656df4  mov r8d,[rdi+4]` | stored at rbp+0x260 | [V] |
| mQword8 | 8B | 0x08 | rdi+0x08 | `0x6656e04  movsd xmm2,[rdi+8]` | stored at rbp+0x264; also used for shared-ptr refcount at [rax+8]/[r14+8] and reloaded `0x665708b  mov r14,[rdi+8]` | [V] |
| mDwordC | 4B | 0x0C | rdi+0x0C | `0x6656dff  movss xmm1,[rdi+0xC]` | subtrahend of the +0x10 - +0xC max calculation | [V] |
| mDword10 | 4B | 0x10 | rdi+0x10 | `0x6656e11  movss xmm2,[rdi+0x10]` | minuend of the +0x10 - +0xC max calculation | [V] |
| mVec14 | 16B | 0x14 | rdi+0x14 | `0x6656e2e  movups xmm1,[rdi+0x14]` | first of eight consecutive vec4 at +0x10 spacing (+0x14,+0x24,...,+0x84) | [V] |
| mVec24 | 16B | 0x24 | rdi+0x24 | `0x6656e39  movups xmm1,[rdi+0x24]` | consecutive vec4 block | [V] |
| mVec34 | 16B | 0x34 | rdi+0x34 | `0x6656e44  movups xmm1,[rdi+0x34]` | consecutive vec4 block | [V] |
| mVec44 | 16B | 0x44 | rdi+0x44 | `0x6656e4f  movups xmm1,[rdi+0x44]` | consecutive vec4 block | [V] |
| mVec54 | 16B | 0x54 | rdi+0x54 | `0x6656e5a  movups xmm1,[rdi+0x54]` | consecutive vec4 block | [V] |
| mVec64 | 16B | 0x64 | rdi+0x64 | `0x6656e65  movups xmm1,[rdi+0x64]` | consecutive vec4 block | [V] |
| mVec74 | 16B | 0x74 | rdi+0x74 | `0x6656e70  movups xmm1,[rdi+0x74]` | consecutive vec4 block | [V] |
| mVec84 | 16B | 0x84 | rdi+0x84 | `0x6656e7b  movups xmm1,[rdi+0x84]` | last of eight consecutive vec4 blocks | [V] |
| mQword94 | 8B | 0x94 | rdi+0x94 | `0x6656e89  movsd xmm1,[rdi+0x94]` | stored at rbp+0x2F0 | [V] |
| mDword9C | 4B | 0x9C | rdi+0x9C | `0x6656e99  movss xmm1,[rdi+0x9C]` | stored at rbp+0x2F8 | [V] |
| mByteA0 | 1B | 0xA0 | rdi+0xA0 | `0x6656ea9  movzx r8d,byte ptr [rdi+0xA0]` | final byte of the 0xAD-byte image | [V] |
| mQwordD8 | 8B | 0xD8 | rdi+0xD8 | `0x6656d4d  mov rcx,[rdi+0xD8]` | refcounted-object pointer; null-checked, saved at rbp+0x210, reloaded into rdi | [V] |
| mQwordE8 | 8B | 0xE8 | rdi+0xE8 | `0x6656d62  movsd xmm6,[rdi+0xE8]` | only low 4B stored at rbp+0x220 and rbp+0x388 | [V] |
| mDwordEC | 4B | 0xEC | rdi+0xEC | `0x6656d6a  movss xmm12,[rdi+0xEC]` | stored at rbp+0x224 and rbp+0x38C | [V] |
| mQwordF0 | 8B | 0xF0 | rdi+0xF0 | `0x6656eb8  movsd xmm11,[rdi+0xF0]` | stored at rbp+0x300 and re-stored into record at rbp+0x468 | [V] |
| mQwordF8 | 8B | 0xF8 | rdi+0xF8 | `0x6656eca  movsd xmm1,[rdi+0xF8]` | stored at rbp+0x308 and re-stored into record at rbp+0x470 | [V] |
| mQword100 | 8B | 0x100 | rdi+0x100 | `0x6656d84  movsd xmm9,[rdi+0x100]` | only low 4B stored at rbp+0x228 and rbp+0x390 | [V] |
| mQword104 | 8B | 0x104 | rdi+0x104 | `0x6656d96  movsd xmm7,[rdi+0x104]` | 8B image stored at rbp+0x22C and rbp+0x394 | [V] |
| mVec10C | 16B | 0x10C | rdi+0x10C | `0x6656dad  movups xmm1,[rdi+0x10C]` | address taken via `lea rcx,[rbp+0x234]` then re-read `[rcx]` at 0x6656f66; first 16B of pushed record | [V] |
| mQword11C | 8B | 0x11C | rdi+0x11C | `0x6656dbb  movsd xmm8,[rdi+0x11C]` | stored at rbp+0x244 and rbp+0x3AC | [V] |
| mDword124 | 4B | 0x124 | rdi+0x124 | `0x6656dcd  movss xmm10,[rdi+0x124]` | stored at rbp+0x24C and rbp+0x3B4 | [V] |
| mVec128 | 16B | 0x128 | rdi+0x128 | `0x6656de6  movups xmm1,[rdi+0x128]` | first 16B of the 0xAD-byte image at rbp+0x250 | [V] |

## Part 2 — Size proof

Highest description read is +0x128 with a 16-byte movups (`0x6656de6  movups xmm1,[rdi+0x128]`), so the object extent ends at 0x138. That matches `Descriptions.h` `RenderAtmosphereDescription` sizeof 0x138 [V: BGFX_MAP 6ih / Descriptions.h static_assert]. No description field is read beyond +0x128; the derived value `rbp+0x26C = max([rdi+0x10]-[rdi+0xC], [0xEEC8060])` is a local computation, not a desc field.

## Part 3 — Producer (Sky tag 0, no thin clone)

BGFX_MAP 6g/6w list `RenderAtmosphereDescription` clone `0x53e2c00` (fat, 0xb43 bytes) as Sky tag 0 [V from BGFX_MAP; BGFX_MAP is a hypothesis list, not proof]. The disassembly listing `lightgame_clone_53e2c00_53e3743.txt` shows 0x53e2c00 builds a local description frame whose base `[rbp-0x38]` maps to desc+0x00, writing fields that line up exactly with the visitor reads above:

- `[rbp-0x38]` = desc+0x00: `0x53e2e7c  mov word ptr [rbp-0x38],0` (u16 zero) then `0x53e2e82  mov [rbp-0x34],eax` (desc+0x04 dword)
- `[rbp-0x30]` = desc+0x08: `0x53e2e8d  movsd [rbp-0x30],xmm0` (qword), later overwritten by `0x53e2fa9  movsd xmm0,[rsi+0x45C]` then `0x53e2fb1  movsd [rbp-0x30],xmm0`
- `[rbp-0x28]` = desc+0x0C: `0x53e2e92  mov dword ptr [rbp-0x28],0x43FA0000` (float 3.5f) then `0x53e2fb6  movss xmm0,[rsi+0x464]` then `0x53e2fbe  movss [rbp-0x28],xmm0`
- `[rbp-0x24]` = desc+0x10: `0x53e2fc3  movups xmm0,[rsi+0x424]` then `0x53e2fca  movups [r12],xmm0` where r12 = rbp+0x3C = desc+0x74... 

Wait — the producer's local frame base is `[rbp-0x38]` but the vec4 stores go to `[rbp-0x24]`, `[rbp-0x14]`, `[rbp-4]`, `[rbp+0xC]`, `[rbp+0x1C]`, `[rbp+0x2C]` which map to desc+0x10, +0x24, +0x34, +0x44, +0x54, +0x64 — matching the visitor's consecutive vec4 reads at +0x10 spacing. And `[rbp+0x4C]` (desc+0x84) is zeroed, `[rbp+0x5C]` (desc+0x94) zeroed, `[rbp+0x64]` (desc+0x9C) = 1.0f, `[rbp+0x68]` (desc+0xA0) = 0, `[rbp+0x6C]` (desc+0xA4) zeroed, `[rbp+0x7C]` (desc+0xB4) zeroed, `[rbp+0x8C]` (desc+0xC4) zeroed.

This local frame is built from settings read via `rsi` (e.g. `[rsi+0x45C]`, `[rsi+0x464]`, `[rsi+0x424]`) and shared-ptr refcount operations (`lock inc dword ptr [rcx+8]` at 0x53e2ca1, vtable releases via `[0xF99FFA0]`). The function is called by `0x5376a00` (level renderer "Render sky" per BGFX_MAP strings) and tail-jumps to `0x5369B30` in one branch (`0x53e2d39  jmp 0x5369B30`).

**Gap:** No `store tag=0` instruction is isolated within 0x53e2c00 or its caller 0x5376a00 in the input data, and no direct insert call for tag 0 is shown. The tag-byte store that selects Sky slot 0x370 tag 0 is not proven in the input listings. Producer identity (0x53e2c00 builds the Atmosphere desc) is consistent but the tag=0 dispatch store is [?].

## Part 4 — VV AtmosphericScattering pass body draining pass+0x548

The Atmosphere case queues a 0x58-byte record into the pass object at `[rsi+0x548]` (begin) / `[rsi+0x550]` (end), stride 0x58, via `0x5aba5c0` (pass lookup) then `cmp r15,[rsi+0x550]` / copy to `[r15]` (`0x665702f  mov r15,[rsi+0x548]`, `0x6657036  cmp r15,[rsi+0x550]`, `0x6657043..0x665705b` three movups copies, `0x6657062  movups [r15+0x30],xmm0`) [V: oc_U-Atm.md].

Searches for the consumer/drain:
- BGFX_MAP 6ih reader scan: scan of `0x6600000-0x6800000` for `[reg + 0x548]` finds no reader of the Sky staging vector at the same base [I: prior note].
- `docs/functions/0xc273420.md` (frame-graph generate): explicitly defers the `pass+0x548` Atmosphere drain to R1; no instruction touching +0x548 isolated [?].
- `docs/progress/re_atmosphere.md`: consumer/drain not located beyond string/setup leads (`sub_55f1450`, `sub_57d5880`, `0x1119c10`) [?, BLOCKED].
- `rdis imm 0x26A1B8F9CE2AFF0a` (FNV-1("AtmosphericScattering")): 0 hits in .text — the name is hashed at runtime via `0x79580`, no pass-body hash immediate [V].
- The VV builder `0x55f1450` references `AtmosphericScattering` at `+0x444fa` and `AtmosphericScatteringToggles` at `+0x43f66` as uniform-key hashing (`0x79580` calls), not as a pass-body dispatch [V: listing].

**Result:** No VV AtmosphericScattering pass body RVA that reads/drains `pass+0x548` (0x58-byte elements) is present in the input data. The drain function is not located [?].

## CLOSES?

CLOSES? NO — not every pending part of R1 is proven by [V] rows. Blocking fact: the VV AtmosphericScattering pass body that drains the queue at pass+0x548 is not located in any input listing (no `[reg+0x548]` reader of the 0x58-byte Atmosphere queue found; `rdis imm` for the AtmosphericScattering hash returns 0 hits; 0xc273420.md defers it to R1), and the producer tag=0 dispatch store is not isolated in the 0x53e2c00 / 0x5376a00 listings. Per-field reads are [V] for all 31 offsets but field meanings are '-' (no instruction/string names an Atmosphere field), so "per-field meaning" is also not established as [V].

## TOOL REQUESTS

None — existing tools only (rdis.exe dis, verify_oc.py, delegate.py check).
