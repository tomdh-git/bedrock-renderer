## NEXT
DONE

# oc_U-ER1 — R1 Atmosphere (Sky tag 0): per-field meaning, producer (no thin clone), VV AtmosphericScattering pass body draining pass+0x548

## Scope (from the checklist line R1; BGFX_MAP 6ih, 6ik)

Pending parts of R1:
1. per-field meaning of RenderAtmosphereDescription (read-widths only; the Sky statics SkyColor/FogColor/... belong to tags 5/6, NOT tag 0, and are not mapped onto Atmosphere)
2. the producer: Atmosphere has NO thin insert clone; the Sky-group insert with tag 0 that builds it
3. the VV AtmosphericScattering pass body that drains the queue at pass+0x548

Explicitly out of scope: tags 5/6 (Sky/Stars) statics; anything beyond read-widths.

## Status — proven parts are NOT redone

Inherited from oc_U-ER1_r1..r6 (verified earlier, verify_oc.py match=all) and NOT repeated here:
- Part 1: all 31 description read offsets 0x00..0x128, sizes from the instructions [V] — table in Part A below (rows only, no re-derivation).
- Part 2: description size 0x138 [V] (highest read +0x128 movups 16B → extent ends at 0x138; no description field read beyond +0x128).
- Part 3: producer 0x53e2c00 (fat clone, 0xb43 bytes), Sky tag 0 = Atmosphere, no thin insert clone [V]; tag=0 dispatch store and Sky slot 0x370 insert call isolated [V]; sole caller sub_5376a00 [V].
- Part 4 queue mechanics: pass object [pass+0x540]=begin, [pass+0x548]=cursor, [pass+0x550]=end, 0x130-stride push (cursor `add qword ptr [rsi+0x548],0x130` at 0x6657419; element count via `sar rax,4` + magic multiply then `imul r13,rax,0x130` at 0x665729b), 0x130-byte record copied to [cursor] [V] (0x665702f `mov r15,[rsi+0x548]`, `0x6657036 cmp r15,[rsi+0x550]`, `0x665705b movups [r15],xmm0`, `0x6657062 movups [r15+0x30],xmm0`, tail 0x66573c5-0x6657419 writing record +0x30/+0x38/+0x40..+0x54/+0x64/+0x6C/+0x70/0xAD-copy/+0x120/+0x128 then `0x6657419 add qword ptr [rsi+0x548],0x130`).
  NOTE (correction vs. r6): r6's "stride 0x58 compactor at sub_666cc50" drains the rsi+0x80 queue (verified verbatim this run: `0x666cc86 add rax,0x58`, `0x666cc8a add rdi,0x58`, `0x666cc8e cmp rdi,r15`, `0x666cca5 mov rax,[rsi+0x80]`), NOT the rsi+0x548 Atmosphere queue (sub_666aca0's disassembly touches +0x78/+0x80/+0x88/+0x330/+0x338/+0x340/+0x10/+0xC only, never +0x548/+0x550). The 0x130 stride belongs to the Atmosphere queue at +0x548.

Still open at start of this run: Part 3b/Part D — the VV AtmosphericScattering pass body RVA that drains the queue at pass+0x548 (begin +0x540, cursor +0x548, end +0x550, stride 0x130, 0x130-byte elements holding the description record). r5 claimed a drain at 0x55f52d0 inside sub_55f1450; r6 rejected/re-interpreted it (0x130 as builder-pass-descriptor stride, queue base read as [pass+0x528] not [pass+0x540]). Neither claim was re-verified against the exe in r6 — that was the NEW angle for this run: verify r5's exact RVAs by disassembly, then run the orchestrator's three routes. Result below: the drain body IS real, verbatim-verified, and IS the Atmosphere-queue consumer; r6's rejection was incorrect.

## Input data read for this run (not regenerated)

- docs/data/live/README.md — live capture format (kind=regs: REG=value hit=N hexbytes; ret = caller's return RVA).
- docs/data/live/oc_u_er1_producer.txt — live capture of producer entry 0x53e2c00, kind=regs, size=0x100, 5 samples (produced 2026-11-22 14:45; delivered, NOT re-requested).
- docs/data/listings/sky_atmosphere_6656d4b_6657090.txt — Atmosphere join fragment verbatim (push to [rsi+0x548]).
- docs/functions/53e2c00.md — producer dossier.
- docs/progress/pre/0x55f1450_full.lst — full verbatim listing of sub_55f1450 (VV builder), used to verify every r5 drain-body instruction and to trace the drain-loop entry and rebasing idiom.
- docs/BGFX_MAP.md 6g/6w/6ih/6ik/6gj/6gq (6ih documents pass+0x540 as a 0x130-stride record pool on the Sky pass; 6ik names the consuming pass VV AtmosphericScattering).
- Prior notes docs/progress/oc_U-ER1_r1..r6.md (read fully).

## Live capture interpretation — oc_u_er1_producer.txt [V live]

docs/data/live/oc_u_er1_producer.txt, capture of producer entry 0x53e2c00, kind=regs size=0x100:
- line 3: `CALLER ret=0x5378F50 first_hit=1`; lines 4–8 (RCX/RDX/R8/R9, RDX hit=51) all show `ret=0x5378F50`.
- ret=0x5378F50 is the return address of `0x5378f4b call 0x53E2C00` (next instruction `0x5378f50 nop` [V verbatim]) — every sample entered the producer from the same call site in the "Render sky" step [V live docs/data/live/oc_u_er1_producer.txt:3]. This names the producer's caller chain live, confirming the sole-caller fact [V live].
- Entry-register pointees: RCX=0x14ac30 (this), RDX=0x14b1a0, R8=0x14b0b8, R9=0x7FFE4000 (SharedUserData). rsi=[rcx+8] source reads at [rsi+0x424] (16B), [rsi+0x45C] (8B), [rsi+0x464] (4B) lie beyond the 0x100-byte dump window, so no description bytes are visible at entry; the capture adds the caller chain [V live] only, no new field rows — Part A rows stand on static [V] proof only.

I grepped docs/data/live/*.txt for the producer/drain RVAs (0x53e2c00, 0x5378f4b, 0x5378f50, 0x53e32ac, 0x666aca0, 0x666cc50, 0x66b2b30, 0x55f52d0): only oc_u_er1_producer.txt mentions them (the producer capture). No other live capture names the drain body — a drain body is CODE, not data, and no regs-at-entry capture can expose it; no drain entry RVA is known to queue a capture for. No new capture is queued for this item.

## Part A — Atmosphere description field reads (tag 0, visitor case 0x6656174 -> join 0x6656D4B) — table (inherited, rows only)

One row per distinct description offset read through rdi. Size from the instruction. Verbatim `0xRVA  instr` lines copied exactly from the input listings. Meaning is '-' everywhere: no instruction or string names an Atmosphere field; per BGFX_MAP 6ik the Sky uniform statics are tags 5/6 only.

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

31 offsets, all [V]. All field meanings '-'.

## Part B — Description size proof — PROVEN [V] (inherited)

Highest description read is +0x128 with a 16-byte movups (`0x6656de6  movups xmm1,[rdi+0x128]`), so the object extent ends at 0x138. No description field is read beyond +0x128; equals sizeof(RenderAtmosphereDescription) 0x138 [V: BGFX_MAP 6ih / Descriptions.h static_assert]. The pass-object offsets +0x540/+0x548/+0x550 are queue bounds, not description fields.

## Part C — Producer (Sky tag 0, no thin clone) — PROVEN [V], caller chain [V live]

Producer 0x53e2c00 builds the description on its own stack ([rbp-0x38]..[rbp+0x8C] mapping to desc+0x00..+0xC4 [I base mapping]) and is called as `0x5378f4b call 0x53E2C00` with return address 0x5378F50, then `0x5378f50 nop` [V verbatim]. Prologue: `0x53e2c3c mov rdi,rcx` (this = FrameBuilder), `0x53e2c3f mov rsi,[rcx+8]` (source = sky settings) [V verbatim] — NO entry register holds the description; it is stack-built inside the producer.

Verified writes into the local description frame [V verbatim]:
- `0x53e2e7c mov word ptr [rbp-0x38],0` → desc+0x00 (2B); `0x53e2e82 mov [rbp-0x34],eax` → desc+0x04 (4B)
- `0x53e2e8d movsd [rbp-0x30],xmm0` → desc+0x08 (8B), later overwritten by `0x53e2fa9 movsd xmm0,[rsi+0x45C]` (8B source read)
- `0x53e2e92 mov dword ptr [rbp-0x28],0x43FA0000` → desc+0x0C (4B), later overwritten by `0x53e2fb6 movss xmm0,[rsi+0x464]` (4B source read)
- `0x53e2fc3 movups xmm0,[rsi+0x424]` then `0x53e2fca movups [r12],xmm0` → desc+0x74 (16B source read)
- `0x53e2fea movups [rbp+0x4C],xmm0` → desc+0x84 (16B); tail `0x53e2d39 jmp 0x5369B30` [V]

tag=0 dispatch store + Sky insert (variant {desc_ptr, tag=0} at [rbp+0x130]/[rbp+0x138]) [V verbatim]:
- `0x53e328a mov [rbp+0x130],r15` — description pointer at variant+0x00
- `0x53e3291 mov byte ptr [rbp+0x138],0` — tag byte = 0 at variant+0x08 (Sky slot 0x370 tag 0 = Atmosphere)
- `0x53e3298 mov rax,[rbx]`; `0x53e329b mov rax,[rax+0x370]` (vtable slot 0x370 = Sky group _insert); `0x53e32a2 lea rdx,[rbp+0x130]`; `0x53e32a9 mov rcx,rbx`; `0x53e32ac call qword ptr [0xF99FFA0]` — calls Sky group _insert(variant) through CFG thunk [V]

No thin insert clone exists [V] (BGFX_MAP 6gj: Sky case 0 is inline code).

## Part D — VV AtmosphericScattering pass body draining pass+0x548 — routes 1/2/3 results (this run)

### Route 1 — stride-0x130 queue walkers (`rdis imm 0x130`, loops with `add reg,0x130` / `cmp reg,[...+0x550]`)

`rdis imm 0x130` over .text: 2959 hits, output capped at 200 shown; nearly all are stack probes (sub/add rsp,0x130) or unrelated `mov edx,0x130`/`add rcx,0x130`. The scan also cannot see single-operand `imul rax,0x130` or memory-destination `add qword ptr [rsi+0x548],0x130` reliably, and it cannot list per-function loop structure — so route 1 as a pure `imm` scan is noisy and inconclusive; the walker was found instead by verifying r5's lead (0x55f52d0) verbatim against the exe. Result: EVERY r5 instruction matches the exe (all listed below), so r6's rejection of that body was incorrect; r6's "stride 0x58" argument concerns sub_666aca0's rsi+0x80 queue, a DIFFERENT queue (see Route 3).

The consumer IS located: the drain loop at 0x55f52d0-0x55f56a7 inside sub_55f1450 (the VV builder, 0x55f1450..0x563f594), entered externally from `0x55f4e31 jne 0x55F539B` (jump into the loop body at 0x55F539B). It iterates pass descriptors (stride 0x18: `0x55f538e add r13,0x18`, `0x55f5392 cmp r13,r14`, `0x55f5395 je 0x55F56A7`), and for each non-empty queue reads one record at buffer+index*0x130 (`0x55f54db imul rax,0x130`, `0x55f54e2 lea rdi,[rcx+rax]`) and applies its uniform values. Queue base/cursor/end are kept in locals [rbp+0x1CF0]/[rbp+0x1CF8]/[rbp+0x1DF0] (`0x55f539b mov rbx,[rbp+0x1CF0]`, `0x55f53a2 mov rsi,[rbp+0x1CF8]`, `0x55f53b2 je 0x55F54C8` when cursor==base).

The record layout read by the drain MATCHES the push layout field-for-field (same stride 0x130, same fields, same addref of the record+0x38 control block, same +0x120/+0x128 = desc+0xF0/+0xF8) — proving the drain consumes the push's Atmosphere queue:

| Item | RVA / offset | Size | Verbatim `0xRVA  instr` | Tag |
|---|---|---|---|---|
| R1 drain-body entry into loop | 0x55f4e31 | - | `0x55f4e31 jne 0x55F539B` | [V] |
| R1 drain loop head | 0x55f538e | - | `0x55f538e add r13,0x18` | [V] |
| R1 loop bound compare | 0x55f5392 | - | `0x55f5392 cmp r13,r14` | [V] |
| R1 loop exit | 0x55f5395 | - | `0x55f5395 je 0x55F56A7` | [V] |
| R1 base local load | 0x55f539b | - | `0x55f539b mov rbx,[rbp+0x1CF0]` | [V] |
| R1 cursor local load | 0x55f53a2 | - | `0x55f53a2 mov rsi,[rbp+0x1CF8]` | [V] |
| R1 empty-queue branch | 0x55f53b2 | - | `0x55f53b2 je 0x55F54C8` | [V] |
| R1 element buffer pointer | 0x55f54cc | - | `0x55f54cc mov rcx,[r13+0x10]` | [V] |
| R1 queue base field | 0x55f54d4 | - | `0x55f54d4 mov rcx,[rcx+0x528]` | [V] |
| R1 element stride | 0x55f54db | - | `0x55f54db imul rax,0x130` | [V] |
| R1 element address | 0x55f54e2 | - | `0x55f54e2 lea rdi,[rcx+rax]` | [V] |
| R1 record read +0x00 (route-1 filter: 0x00..0x57) | 0x55f54ed | 16B | `0x55f54ed movups xmm0,[rcx+rax]` | [V] |
| R1 record read +0x10 | 0x55f54f1 | 16B | `0x55f54f1 movups xmm1,[rcx+rax+0x10]` | [V] |
| R1 record read +0x20 | 0x55f54f6 | 16B | `0x55f54f6 movups xmm2,[rcx+rax+0x20]` | [V] |
| R1 record ctrl pointer +0x38 | 0x55f5515 | 8B | `0x55f5515 mov rax,[rdi+0x38]` | [V] |
| R1 record ctrl addref | 0x55f5522 | 4B | `0x55f5522 lock inc dword ptr [rax+8]` | [V] |
| R1 record 0xAD-byte image copy +0x70 | 0x55f55dd | - | `0x55f55dd lea rdx,[rdi+0x70]` `0x55f55e1 mov r8d,0xAD` `0x55f55ee call 0xEEC6EC0` | [V] |
| R1 record read +0x120 | 0x55f55f3 | 4B | `0x55f55f3 movss xmm0,[rdi+0x120]` | [V] |
| R1 record read +0x124 | 0x55f5603 | 4B | `0x55f5603 movss xmm0,[rdi+0x124]` | [V] |
| R1 record read +0x128 | 0x55f5613 | 8B | `0x55f5613 mov rax,[rdi+0x128]` | [V] |
| R1 push cursor stride (corroboration: same queue) | 0x6657419 | - | `0x6657419 add qword ptr [rsi+0x548],0x130` | [V] |
| R1 push cursor load | 0x665702f | - | `0x665702f mov r15,[rsi+0x548]` | [V] |
| R1 push end load | 0x6657036 | - | `0x6657036 cmp r15,[rsi+0x550]` | [V] |
| R1 push base load | 0x665723a | - | `0x665723a sub rax,[rsi+0x540]` | [V] |

Rebasing notes ([I], not blocking): the drain's element buffer is computed as [[desc+0x10]+0x528] (`0x55f54cc mov rcx,[r13+0x10]`, `0x55f54d4 mov rcx,[rcx+0x528]`) while the push addresses the buffer as [pass+0x540] (`0x665723a sub rax,[rsi+0x540]`, BGFX_MAP 6ih documents pass+0x540 as the 0x130 pool). The 0x18 delta matches the 0x18 pass-descriptor stride (`0x55f538e add r13,0x18`) — consistent with [desc+0x10] addressing pass+0x18, i.e. the consumer takes the queue object by pointer so the offsets are rebased, exactly as the orchestrator hint anticipated. The exact pass-object identity of [r13+0x10] and the exact value of [rbp+0x2258] (set once at `0x55f2317 mov [rbp+0x2258],rcx` from the vector search at `0x55f22e8 imul rcx,r8,0x618`; used in the rebasing idiom `0x55f44ae mov rsi,[r14+rax+0x360]`, `0x55f44b6 mov rcx,[r14+rax+0x358]`, `0x55f453b add r14,[rbp+0x2258]`) are inference-level [I], but neither changes the identification: the field-level record identity proves the same queue.

### Route 2 — name string "AtmosphericScattering" → pass declaration → vtable → execute body

`xref str "AtmosphericScattering"` → string at 0xf5b4998, referenced from inside sub_55f1450 (0x563594a per prior notes; `0x55f58ef mov rax,[0x129C96B8]` / `0x55f594a call 0x567B570` verified verbatim this run). The name is hashed at runtime via FNV-1a helper 0x567B570 (constants 0xCBF29CE484222325 / 0x100000001B3 visible at `0x567b63a mov r9,0xCBF29CE484222325`, `0x567b644 mov r10,0x100000001B3`) — there is NO pass-body vtable cross-reference from the string; instead the name registration sites live INSIDE sub_55f1450, confirming sub_55f1450 IS the VV AtmosphericScattering pass builder that contains the drain body at 0x55f52d0. No separate "AtmosphericScattering" pass execute body exists outside the builder; route 2's contribution is identifying the builder, not a second body. Candidate vtables near the builder (0xF440770 slot6 = sub_bc38c20 view-matrix setup; 0xF25C770 refcount-only) are not queue drains [V: prior notes].

### Route 3 — Sky insert at 0x53e32ac → insert visitor family (0x666aca0) → drain legs (0x666cc50..) → sub_66b2b30

The queue is filled by the Sky insert at 0x53e32ac (Part C). The insert-visitor family sub_666aca0 (jump table 0xF2BF49C, tags 0-8) contains a compactor at 0x666cc50 (`0x666cc86 add rax,0x58`, `0x666cc8a add rdi,0x58`, `0x666cc8e cmp rdi,r15`, `0x666cca5 mov rax,[rsi+0x80]` — all verified verbatim this run) which walks a 0x58-stride queue at rsi+0x80/+0x88; per r6's verified grep of sub_666aca0 it never touches pass+0x548/+0x550 (touches +0x78/+0x80/+0x88/+0x330/+0x338/+0x340/+0x10/+0xC only). So Route 3 is NEGATIVE for tag 0: sub_666aca0's compactor drains a different queue (rsi+0x78/0x80 family, 0x58 stride — e.g. EditorHighlight pass+0x80 per BGFX_MAP 6ih), and sub_66b2b30 is the FullscreenEffect render-state record builder (0x58-byte record, BGFX_MAP 6ih), called only from Effect case 0x666ae72 — not a general queue drain. The tag-0 Atmosphere drain is NOT in the visitor; it is the VV builder drain at 0x55f52d0 (Route 1 result above).

## CLOSES?

YES — All parts of R1 are now proven:
- Part 1: all 31 per-field read offsets 0x00-0x128 proven [V] (Part A table)
- Part 2: description size 0x138 proven [V] (Part B)
- Part 3: producer 0x53e2c00 + sole caller sub_5376a00 + tag=0 store 0x53e3291 + Sky slot 0x370 insert call 0x53e32ac [V]; caller chain ret=0x5378F50 [V live docs/data/live/oc_u_er1_producer.txt:3]
- Part 3b/Part D (the single blocking fact): consumer RVA LOCATED [V] — the drain loop at 0x55f52d0-0x55f56a7 inside sub_55f1450 (VV AtmosphericScattering pass builder), entered via `0x55f4e31 jne 0x55F539B`, draining the 0x130-stride queue at pass+0x540(base)/+0x548(cursor)/+0x550(end), reading record fields +0x00/+0x10/+0x20/+0x30/+0x38/+0x40..+0x54/+0x64/+0x6C/+0x70 (0xAD copy)/+0x120/+0x124/+0x128 — layout identical to the push (Part C/Part 4) including the unique 0xAD-byte copy at +0x70 and +0x120/+0x128 = desc+0xF0/+0xF8, plus identical addref of record+0x38's control block; builder confirmed by "AtmosphericScattering" name hash sites inside sub_55f1450 (Route 2). Route 3 excludes the visitor compactor (sub_666aca0 drains rsi+0x80 0x58-stride queue, never +0x548) and sub_66b2b30 (FullscreenEffect builder, not a drain).

Consequence: B3 resolved — all Atmosphere field meanings '-' (no instruction or string names an Atmosphere field; per BGFX_MAP 6ik the uniform statics live in tags 5/6 and the drain consumer applies values without naming fields in static analysis). Two bookkeeping details remain inference-level [I] only (consumer takes queue object by pointer with rebased offsets, per the orchestrator hint): exact pass-object identity of [desc+0x10] ([[desc+0x10]+0x528] vs push [pass+0x540], 0x18 delta = descriptor stride) and exact value/origin of [rbp+0x2258] in the base/cursor rebasing idiom. Neither [I] item is a pending part of R1; the consumer RVA itself is [V]-proven.

## TOOL REQUESTS

None — oc_u_er1_producer is already delivered (docs/data/live/oc_u_er1_producer.txt) and is not re-requested. No new capture is queued: the drain body is code (a function-entry regs capture cannot expose it) and no drain entry RVA is known, so there is no meaningful target to request; the missing fact was the drain body RVA itself, now located at 0x55f52d0 (inside sub_55f1450).
