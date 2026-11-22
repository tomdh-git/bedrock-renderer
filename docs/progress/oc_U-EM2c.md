## NEXT
DONE Atmosphere queue at pass+0x548 verified: element size 0x130 bytes (not 0x58), bounds +0x540/+0x548/+0x550, element field map; pass+0x548 consumer not located — M2c not closeable yet

# U-EM2c — M2c description types: Atmosphere queue at pass+0x548 (element-size correction) + BlitFlipbook 0xA0/[?] tails

## Scope — pending part of the M2c progress line

The M2c line (RENDER_CHECKLIST.md) leaves two decodes pending:
- (a) RenderBlitFlipbookDescription 0xA0 with 0x40-byte elements, unread tails marked [?].
- (b) Atmosphere: "repacked into a stack block by the visitor" was corrected to "queued into a Sky-pass vector (pass+0x548, 0x58-byte elements...)" — the queue wiring and element size were never instruction-verified, and the pass consumer that would name the fields was never located.

This unit verifies (b) at instruction level and records the status of (a). Only docs/progress/oc_U-EM2c.md is created; no src/, header, Sigs.json, CMake, or hook edits. Static analysis only; no build, no game launch or attach.

## Input data read in full

- docs/data/producer_fields.txt (6if raw producer stores for the thin clones).
- docs/BGFX_MAP.md, 6ih sections (Atmosphere/EditorHighlight/Light visitor reads, ~lines 1840-1856).
- docs/progress/oc_U-Atm.md (delegate-checked DONE: instruction-complete fragment 0x6656d4b..0x665708f).
- docs/progress/re_atmosphere.md, docs/progress/re_blitflipbook.md.

## Answer: Atmosphere queue at pass+0x548

Corrected reading of the cut-off 6ih line: the Atmosphere case does NOT leave a stack block. The fragment 0x6656d4b..0x665708f ends by jumping to 0x66573C3/0x66573C5 (handoff targets outside the listing), which build a queue element on the pass object returned by `0x5aba5c0(0x9D0 + [frameCtx+0x10])` and append it at pass+0x548. Every claim below carries a verbatim instruction proof line.

### Answer table (offset | size | site | verbatim `0xRVA  instr` proof | name/meaning [tag])

| offset | size | site | instr | name/meaning [tag] |
|---|---|---|---|---|
| 0x540 | 8 | R | `0x6657237  mov rax,r15`; `0x665723a  sub rax,[rsi+0x540]` | pass+0x540: queue base/begin read by grow path 0x6657237 (end − begin) [V] |
| 0x548 | 8 | R, W | `0x665702f  mov r15,[rsi+0x548]`; `0x6657419  add qword ptr [rsi+0x548],0x130` | pass+0x548: queue end/write cursor — read yields slot r15 for the new element [V]; write advances end by 0x130 per push → element size = 0x130 bytes, NOT 0x58 as the line claims; claim refuted [V] |
| 0x550 | 8 | R | `0x6657036  cmp r15,[rsi+0x550]` | pass+0x550: capacity end — end == cap jumps to grow path 0x6657237 [V] |
| 0x00 | 16 | W | `0x665705b  movups [r15],xmm0`; `0x6657056  movups [r15+0x10],xmm1`; `0x6657051  movups [r15+0x20],xmm2` | element+0x00..+0x2F: 0x30-byte block copied from rbp+0x348 (record of pre-set locals 0x1E0/0x1F0/0x200) [V]; field meaning [?] |
| 0x30 | 8 | W | `0x66573c5  mov [r15+0x30],rdi` | element+0x30: object pointer, image of desc+0xD8 via local 0x210 [V]; slot was pre-zeroed by a 16-byte movups at 0x6657062 (overwritten by this qword store at +0x30..+0x37); +0x38 handled in next row |
| 0x38 | 8 | W | `0x66573c9  mov [r15+0x38],rax` | element+0x38: control-block pointer (0 in this path); refcount path `0x6657070  lock inc dword ptr [r14+8]` exists for the r14!=0 variant (skipped here: `0x6657067  test r14,r14`; `0x665706a  je 0x66573C3`) [V instruction exists, path not taken in this instance] |
| 0x40 | 4 | W | `0x66573cd  movss [r15+0x40],xmm6` | element+0x40: low 4B of desc+0xE8 [V]; uniform name/meaning [?] |
| 0x44 | 4 | W | `0x66573d3  movss [r15+0x44],xmm12` | element+0x44: desc+0xEC [V]; meaning [?] |
| 0x48 | 4 | W | `0x66573d9  movss [r15+0x48],xmm9` | element+0x48: low 4B of desc+0x100 [V]; meaning [?] |
| 0x4C | 8 | W | `0x66573df  movlps [r15+0x4C],xmm7` | element+0x4C..+0x53: low 8B of desc+0x104 [V]; meaning [?] |
| 0x54 | 16 | R, W | `0x66573e4  movups xmm0,[rcx+0x54]` (rcx = rbp+0x234 = image of desc+0x10C); `0x66573e8  movups [r15+0x54],xmm0` | element+0x54..+0x63: desc+0x10C block [V]; meaning [?] |
| 0x64 | 8 | W | `0x66573ed  movlps [r15+0x64],xmm8` | element+0x64..+0x6B: low 8B of desc+0x11C [V]; meaning [?] |
| 0x6C | 4 | W | `0x66573f2  movss [r15+0x6C],xmm10` | element+0x6C..+0x6F: desc+0x124 [V]; meaning [?] |
| 0x70 | 173 | W | `0x66573f8  lea rcx,[r15+0x70]`; `0x66573fc  mov r8d,0xAD`; `0x6657402  mov rdx,r13` (r13 = rbp+0x250, image of desc+0x128); `0x6657405  call 0xEEC6EC0` | element+0x70..+0x11C: 0xAD-byte block copy of desc+0x128 image (r8d=0xAD=173) [V shape]; byte meaning [?]; +0x11D..+0x11F not separately written (pad/block interior) [?] |
| 0x120 | 8 | W | `0x665740a  movlps [r15+0x120],xmm11` | element+0x120..+0x127: desc+0xF0 [V]; meaning [?] |
| 0x128 | 8 | W | `0x6657412  mov [r15+0x128],r12` (r12 = image of desc+0xF8) | element+0x128..+0x12F: desc+0xF8 [V]; last store ends at +0x12F → element span 0x130 bytes, matches `add [rsi+0x548],0x130` [V] |

### Conclusion on the element size

The push epilogue writes element bytes through [r15+0x128] and then `0x6657419  add qword ptr [rsi+0x548],0x130`. The queued element is therefore **0x130 bytes**, not 0x58 bytes as the progress line and BGFX_MAP.md:1843 claim. The 0x58 stride belongs to a different queue (EditorHighlight at pass+0x80 per BGFX_MAP.md:1854) and was conflated with the Atmosphere queue. Queue model now: pass+0x540 = begin, pass+0x548 = end (write cursor), pass+0x550 = capacity, element stride 0x130 — all [V].

### Status of part (a): BlitFlipbook

Superseded on disk: docs/progress/re_blitflipbook.md verifies RenderBlitFlipbookDescription = 0x20 bytes `{SharedRef +0x00, u64 count +0x10, Element* +0x18}`, element stride 0x40 copied by `0x5acb9c0`, consumer loop `0x666b704..0x666c846` reads element +0x00/+0x08/+0x18/+0x20/+0x24 [V]; element bytes +0x28..+0x3C are stored but unread in that loop [? meaning]. The M2c line's "0xA0 with unread tails" comes from over-wide producer stack-store windows in docs/data/producer_fields.txt (clone 0x5acbe20: last store +0x98) that write beyond the 0x20 description object — there are no description tails; the description is 0x20 [V per re_blitflipbook.md RVAs].

### Open (blocking)

- No consumer/reader of the pass+0x548 Atmosphere queue (0x130-byte elements) is located: a scan of 0x6600000-0x6800000 for `[reg+0x548]` found only other objects (BGFX_MAP.md:1844; re_atmosphere.md). Per-field uniform names therefore unresolved — Atmosphere fields are placement-[V] but meaning-[?].
- M2c overall: 35 of 62 description types remain untyped.

## What changed

Created: docs/progress/oc_U-EM2c.md (this note). No other file created or edited.

## CLOSES?

NO — M2c requires all 62 description types as structs with confirmed fields. RenderAtmosphereDescription cannot be confirmed as fully typed: its field meanings/uniform names are unresolved because the pass+0x548 queue consumer (reader of the 0x130-byte elements) is not located (scan 0x6600000-0x6800000 negative, BGFX_MAP.md:1844), and 35 of 62 types remain untyped.

## TOOL REQUESTS

None — existing rdis dis and delegate.py/verify_oc only.
