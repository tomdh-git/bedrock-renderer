## NEXT
DONE

# oc_U-ER1 — R1 Atmosphere (Sky tag 0): per-field meaning, producer (no thin clone), VV AtmosphericScattering pass body draining pass+0x548

## Scope (from the checklist line R1)

Pending parts of R1 (BGFX_MAP 6ih, 6ik):
1. per-field meaning of RenderAtmosphereDescription (read-widths only; the Sky statics SkyColor/FogColor/... belong to tags 5/6, NOT tag 0 — do not map them onto Atmosphere)
2. the producer: Atmosphere has NO thin insert clone; find the Sky-group insert with tag 0 that builds it
3. the VV AtmosphericScattering pass body that drains the queue at pass+0x548

Explicitly out of scope: tags 5/6 (Sky/Stars) statics; anything beyond read-widths.

## Status inherited (PROVEN — do NOT redo)

- Part 1 per-field description reads: all 31 offsets proven [V] in prior input listings (offsets 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74, 0x84, 0x94, 0x9C, 0xA0, 0xD8, 0xE0, 0xE8, 0xEC, 0xF0, 0xF8, 0x100, 0x104, 0x10C, 0x11C, 0x124, 0x128). All verbatim lines re-checked against the exe in Part A below. Highest read +0x128 (movups 16B) → description extent ends at 0x138 = sizeof(RenderAtmosphereDescription) [V].
- Queue mechanics (not desc fields): tag-0 path queues into the pass object at [rsi+0x540]=queue base, [rsi+0x548]=write cursor, [rsi+0x550]=end, stride 0x130 per push, 0x40-byte record copied to [cursor] [V: 0x665723a/0x665702f/0x6657036/0x6657043/0x6657062/0x6657419/0x665729b].
- Producer: 0x53e2c00 (fat clone 0xb43 bytes, BGFX_MAP 6g/6w, Sky tag 0 = Atmosphere per BGFX_MAP 6w/503; shared with Light tag 0 per BGFX_MAP line 1324) builds a local description frame at [rbp-0x38]..[rbp+0x4C] mapping to desc+0x00..+0x84 [I base mapping; individual writes verified [V] below]; sole caller sub_5376a00, 1 call site [V: rdis callers 0x53e2c00]; tail-jumps to 0x5369b30 at 0x53e2d39 [V]. Tag=0 dispatch byte-store and the direct insert call NOT isolated [?]. No thin insert clone exists (BGFX_MAP 6gj: Sky case 0 is inline code) [V].

## Still open (blocking facts)

B1: VV AtmosphericScattering pass body RVA that reads/drains [pass+0x540]/[pass+0x548] (0x130-byte elements) is NOT located. No [reg+0x540]/[reg+0x548] drain reader found in static analysis.
B2: producer tag=0 dispatch store (byte store selecting Sky slot 0x370 tag 0) and the direct insert call for Atmosphere not isolated in 0x53e2c00/0x5376a00.
B3: all 31 Atmosphere description field meanings are '-' — no instruction or string names an Atmosphere field; per the checklist meanings live in the consumer that reads the queued data, so B3 is blocked by B1.

## Live data used (existing result — no new capture requested)

docs/data/live/sky_visitor.txt (capture of sky visitor entry 0x66560F0, kind=visitor, size=0x300) line 1: tag 0 = Atmosphere, description pointer 0x14A468, 768 bytes dumped [V live]. Bytes exist at every proven desc offset with widths matching the reads [V live]; representative decodes: 0x00 u16=0 (dword bits 1.0f), 0x24 vec4={0.02f,0.02f,0.02f,1.0f}, 0x54 vec4={0.1f,0.1f,0.1f,1.0f}, 0xA0 byte=0, 0xD8 qword=0 (null), 0xE8=1.0f, 0xEC=1.0f, 0xF0=0.5625f, 0xF8=0.5625f, 0x100=-1.0f, 0x128=1.0f. No names or strings appear in the dump, so [V live] confirms sizes/presence only, never field meanings. No new capture requested: a function-entry capture dumps register data + pointee bytes, not code — it cannot locate the drain body (B1), the producer builds its description on its own stack (no description pointer in entry registers), and the visitor entry is already covered by sky_visitor.txt.

## NEW static angles tried in this unit (all negative)

- rdis imm 0x130 across .text: 2959 hits, all stack probes (sub/add rsp,0x130) and unrelated imul/add; no `[reg+0x548],0x130` drain and none in the VV builder region 0x55f1450-0x563f594 [V].
- rdis callers 0x53e2c00: sole caller sub_5376a00, 1 call site [V] (producer side only).
- xref str "AtmosphericScattering": string 0xf5b4998 referenced only from 0x563594a inside VV builder 0x55f1450 (pass-name hash site, hashed via 0x79580); no pass-body cross-reference [V].
- BGFX_MAP 6v pass-body table has no "AtmosphericScattering" body; "VolumeScattering 0xbc7c7d3" and "Scattering 0xbc7e6e1" exist — disassembled 0xbc7e6e1 (scat.txt): reads [rbx+0x2F8/0x300/0x310], hashes "VolumeDimensions"/"VolumeNearFar" via 0x79580, no [reg+0x540]/[reg+0x548]/[reg+0x550] queue read [V].
- rdis fld 0x540/0x548/0x550 scans: truncated at 4000/5410 lines; VV builder region not covered; nothing found outside it [V].
- rdis imm FNV-1("AtmosphericScattering") 0x26A1B8F9CE2AFF0a: 0 hits (name hashed at runtime via 0x79580) [V: prior note].

## Part A — Atmosphere description field reads (tag 0, visitor case head 0x6656174 + join fragment 0x6656d4b..0x6656de6), one row per distinct offset, all sites listed

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

## Part B — Description size proof

Highest description read is +0x128 with a 16-byte movups (`0x6656de6  movups xmm1,[rdi+0x128]`), so the object extent ends at 0x138. No description field is read beyond +0x128; this equals sizeof(RenderAtmosphereDescription) 0x138 [V: matches BGFX_MAP 6ih / Descriptions.h static_assert cited in prior notes]. The pass-object offsets +0x540/+0x548/+0x550 are queue bounds, not description fields.

## Part C — Producer (Sky tag 0, no thin clone) — verbatim writes into the local description frame (base [rbp-0x38] = desc+0x00 [I offset arithmetic]; each write verified [V])

| Write target | size | Verbatim `0xRVA  instr` | Tag |
|---|---|---|---|
| [rbp-0x38] → desc+0x00 | 2B | `0x53e2e7c  mov word ptr [rbp-0x38],0` | [V] |
| [rbp-0x34] → desc+0x04 | 4B | `0x53e2e82  mov [rbp-0x34],eax` | [V] |
| [rbp-0x30] → desc+0x08 | 8B | `0x53e2e8d  movsd [rbp-0x30],xmm0`, later overwritten `0x53e2fb1  movsd [rbp-0x30],xmm0` from [rsi+0x45C] | [V] |
| [rbp-0x28] → desc+0x0C | 4B | `0x53e2e92  mov dword ptr [rbp-0x28],0x43FA0000`, later overwritten `0x53e2fbe  movss [rbp-0x28],xmm0` from [rsi+0x464] | [V] |
| [r12] → desc+0x74 (r12 = rbp+0x3C) | 16B | `0x53e2fc3  movups xmm0,[rsi+0x424]` then `0x53e2fca  movups [r12],xmm0` | [V] |
| [rbp+0x4C] → desc+0x84 | 16B | `0x53e2fea  movups [rbp+0x4C],xmm0` ([rbp+0x4C] = desc+0x84) | [V] |
| [rcx+8] (shared-ptr control block) | 4B | `0x53e2ca1  lock inc dword ptr [rcx+8]` (shared-ptr addref) | [V] |
| [r15+8] (shared-ptr control block) | 4B | `0x53e2f6d  lock dec dword ptr [r15+8]` (shared-ptr release) | [V] |
| tail jump target | — | `0x53e2d39  jmp 0x5369B30` | [V] |
| producer caller | — | `rdis callers 0x53e2c00` → sole caller sub_5376a00, 1 call site ("Render sky" level renderer per BGFX_MAP strings [I]) | [V] |

Not proven for the producer: the tag=0 dispatch byte-store (Sky slot 0x370 tag 0) and the direct insert call — neither appears in the 0x53e2c00 listing nor in its sole caller 0x5376a00 [?].

## Part D — VV AtmosphericScattering pass body draining pass+0x548 (B1) — NOT LOCATED [?]

Queue mechanics proven [V] (all verbatim from the exe):
- `0x665723a  sub rax,[rsi+0x540]` — queue base [rsi+0x540]
- `0x665702f  mov r15,[rsi+0x548]` — write cursor [rsi+0x548]
- `0x6657036  cmp r15,[rsi+0x550]` — end [rsi+0x550]
- `0x6657419  add qword ptr [rsi+0x548],0x130` — cursor advances by stride 0x130 per push
- `0x665729b  imul r13,rax,0x130` — element index math with stride 0x130
- `0x6657043  movups xmm0,[rax]` … `0x665705b  movups [r15],xmm0` … `0x6657062  movups [r15+0x30],xmm0` — 0x40-byte record copied to [cursor]

The drain itself (who reads [pass+0x540]/[pass+0x548] and consumes the 0x130-stride elements) is not in any input listing. New angles tried this unit (Part "NEW static angles"): imm 0x130, xref str "AtmosphericScattering", 6v pass-body disassembly of 0xbc7e6e1, fld 0x540/0x548/0x550 scans, imm FNV hash — all negative. endFrame (0x66232b0) field set does not include +0x540/+0x548/+0x550 [V: prior note]. No VV/RTX pass lambda reads the queue [V: prior note].

## CLOSES?

CLOSES? NO — the single blocking fact: the VV AtmosphericScattering pass body RVA that drains the queue at pass+0x548 (base +0x540, cursor +0x548, end +0x550, stride 0x130) is not located in static analysis, and no live capture can expose a code body (captures dump register/pointee data at function entry only), so B1 cannot be closed from available evidence. Consequences still open: B2 producer tag=0 dispatch store not isolated; B3 all Atmosphere field meanings '-'. Proven [V]: all 31 per-field read widths (Part A), size 0x138 (Part B), queue mechanics (Part D), producer 0x53e2c00 with sole caller 0x5376a00 (Part C).

## TOOL REQUESTS

None — no helper scripts written, no new live capture requested (rationale in the Live data section: sky_visitor.txt already covers the only capturable description, the producer's description is stack-local, and the drain is code not data).
