## NEXT
DONE

# Unit U-EL12c — L12c Hands / held items (1.26.62 re-check)

Source line: docs/RENDER_CHECKLIST.md line 374:
`- [ ] L12c Hands / held items — docs/first-person-hand-notes-1.26.60.md (6bh); 1.26.62 re-check pending`
Prior-work index: docs/BGFX_MAP.md 6bh ("I2c hands / held items ... RVAs are 1.26.60.05 and need re-checking on 1.26.62 (6w gives the 1.26.62 ItemInHand clone 0x531b180 and 0x531b120 held-item lead)").

Pending part closed here: the **1.26.62 re-check** of every RVA/claim in docs/first-person-hand-notes-1.26.60.md.
Base exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (image-base RVAs). Static analysis only.
Method: rdis dis at each claimed RVA + xref.py callers + ripscan.py for call sites; every row carries a verbatim `0xRVA  instr` proof line copied from the exe disassembly. Earlier note oc_U-EI2c.md was treated as a lead only (a note is not proof).

## Answer table (name | rva or offset | size | meaning | verbatim `0xRVA  instr` proof line(s) | [V]/[I]/[?])

| Name | RVA / offset | Size | Meaning | Verbatim proof `0xRVA  instr` | Tag |
|---|---|---|---|---|---|
| BobHurt | 0x53a1320 | - | view-model hurt shake (was 0x53a0fb0; +0x370) | `0x53a1320  push rsi` | [V] |
| BobHurt call site | 0x4e0e331 | - | sub_4e0df90 (view-model render) calls BobHurt | `0x4e0e331  call 0x53A1320` | [V] |
| intermediate 0x4e0f7a0 | 0x4e0f7a0 | - | BobHurt -> this fn -> renderFirstPerson (was 0x4e0f610) | `0x4e0e340  call 0x4E0F7A0`; `0x4e102b6  call 0x532B5A0` | [V] |
| ItemInHandRenderer::renderFirstPerson | 0x532b5a0 | - | entry (was 0x532b230; +0x370) | `0x532b5a0  push rbp`; `0x532b5ac  sub rsp,0x268` | [V] |
| renderFirstPerson -> renderItem | 0x532eafb | - | held-item draw called from renderFirstPerson | `0x532eafb  call 0x531A580` | [V] |
| renderFirstPerson -> renderItemFull | 0x5331634 | - | renderItemFull called from renderFirstPerson | `0x5331634  call 0x531B490` | [V] |
| ItemInHandRenderer::renderItem | 0x531a580 | - | entry (was 0x531a210; +0x370); 6 xrefs incl. renderFirstPerson | `0x531a580  push rbp`; `0x531a5ba  mov rdi,[rdx+0x28]` | [V] |
| ItemInHandRenderer::renderItemFull | 0x531b490 | - | entry (was 0x531b120; +0x370); 11 xrefs incl. renderFirstPerson | `0x531b490  push rbp` | [V] |
| renderItemFull -> renderItem | 0x531cf16 | - | renderItemFull internally calls renderItem | `0x531cf16  call 0x531A580` | [V] |
| insert<ItemInHand> thin clone call sites | 0x531adb2 / 0x531ae8d | - | both inside renderItem (2 call sites) | `0x531adb2  call 0x531B180`; `0x531ae8d  call 0x531B180` | [V] |
| ItemInHandRenderer::renderItem thin clone | 0x531b180 | - | insert<ItemInHand>, Item tag 6, builder vslot 0x378 (same RVA on 62.01) | `0x531b180  push rbp`; `0x531b1f4  mov byte ptr [rbp+0x18],6`; `0x531b1fb  mov rax,[rax+0x378]` | [V] |
| ItemInHandDescription ctor | 0x668cb70 | 0x180 | description struct size 0x180; stores +0x00..+0x17F | `0x668cb70  push rbp`; last write `0x668d24d  movups [rsi+0x170],xmm2` (covers 0x170..0x17F => size 0x180) | [V] |
| ItemInHand extractor (tag-6 handler) | 0x6698e30 | - | tag-6 handler reached via forwarder; stack frame 0x2158 | `0x6698e30  push rbp`; `0x6698e3c  mov eax,0x2158` | [V] |
| Item visitor tag-6 forwarder | 0x6647320 | - | tail-calls the ItemInHand extractor | `0x664737e  jmp 0x6698E30` | [V] |
| ItemInHandRenderer::renderArm | 0x530ab10 | - | arm animation state machine; calls drawArm x2 (was 0x530a7a0; +0x370) | `0x530ab10  push rbp`; `0x530b563  call 0x530A1B0`; `0x530c2c8  call 0x530A1B0` | [V] |
| renderArm call site | 0x4e0e5e0 | - | sole caller: sub_4e0df90 (view-model render) | `0x4e0e5e0  call 0x530AB10` | [V] |
| renderHands | 0x530c700 | - | entry; exactly one caller: sub_4e0df90 (was 0x530c390; +0x370) | `0x530c700  push rbp`; caller `0x4e0e459  call 0x530C700` | [V] |
| drawArm | 0x530a1b0 | - | entry; 5 xrefs: renderHands x3, renderArm x2 (was 0x5309e40; +0x370) | `0x530a1b0  push rbp`; `0x530c9ec  call 0x530A1B0` | [V] |
| drawArm sites 2 and 3 in renderHands | 0x530cd9c / 0x530d3a9 | - | the other two renderHands drawArm call sites | `0x530cd9c  call 0x530A1B0`; `0x530d3a9  call 0x530A1B0` | [V] |
| S = renderHands ctx+0x18 | off 0x18 | 8 | S = render context owning the matrix-stack ring (rsi = renderHands ctx arg) | `0x530ca14  mov r15,[rsi+0x18]` | [V] |
| ring data pointer | S+0x48 | 8 | ring data pointer | `0x530ca2f  mov rcx,[r15+0x48]` | [V] |
| ring capacity | S+0x50 | 8 | ring capacity | `0x530ca33  mov rdx,[r15+0x50]` | [V] |
| ring first index | S+0x58 | 8 | ring first index | `0x530ca25  mov rcx,[r15+0x58]` | [V] |
| ring count | S+0x60 | 8 | ring count | `0x530ca21  mov rax,[r15+0x60]` | [V] |
| ring dirty flag | S+0x78 | 1 | ring dirty/use flag byte | `0x530ca1c  mov byte ptr [r15+0x78],1` | [V] |
| ring top index math | - | - | top = ring[(first + count - 1) & (cap - 1)], 8-byte entries | `0x530ca29  add rax,rcx`; `0x530ca2c  dec rax`; `0x530ca3a  and rdx,rax`; `0x530ca3d  mov rdx,[rcx+rdx*8]` | [V] |
| drawArm arg1 | ctx+0x10 | 8 | drawArm arg1 = ctx+0x10 (i.e. ctx = arg1 - 0x10) | `0x530c9b9  lea rcx,[rsi+0x10]` | [V] |
| ActorAnimationControllerPlayer::applyToPose | 0x617a100 | - | (was 0x6179500; +0x100) reads this+0x40 (mActor per header); no direct xref (indirect/virtual call) | `0x617a100  push rbp`; `0x617a161  movzx edx,byte ptr [rdi+0x40]` | [V] |

## Call chain confirmed on 1.26.62 (all [V])

sub_4e0df90 (view-model render, 0x4e0df90, size 0x77b) calls in order:
1. BobHurt 0x53a1320 at `0x4e0e331  call 0x53A1320`
2. 0x4e0f7a0 at `0x4e0e340  call 0x4E0F7A0`, which calls renderFirstPerson 0x532b5a0 at `0x4e102b6  call 0x532B5A0`
3. renderHands 0x530c700 at `0x4e0e459  call 0x530C700`
4. renderArm 0x530ab10 at `0x4e0e5e0  call 0x530AB10`

renderFirstPerson itself calls renderItem (0x531a580) at `0x532eafb` and renderItemFull (0x531b490) at `0x5331634`; renderItemFull calls renderItem at `0x531cf16`. drawArm (0x530a1b0) is called from renderHands at `0x530c9ec`, `0x530cd9c`, `0x530d3a9` and from renderArm at `0x530b563`, `0x530c2c8`.

## Delta 1.26.60.05 -> 1.26.62.01 (all [V], uniform +0x370 except applyToPose +0x100)

BobHurt 0x53a0fb0->0x53a1320; 0x4e0f610->0x4e0f7a0; renderFirstPerson 0x532b230->0x532b5a0; renderHands 0x530c390->0x530c700; drawArm 0x5309e40->0x530a1b0 (all 5 sites +0x370: 0x530c67c->0x530c9ec, 0x530ca2c->0x530cd9c, 0x530d039->0x530d3a9, outside callers 0x530b1f3->0x530b563, 0x530bf58->0x530c2c8); renderItem 0x531a210->0x531a580; renderItemFull 0x531b120->0x531b490; renderArm 0x530a7a0->0x530ab10; applyToPose 0x6179500->0x617a100. Clone 0x531b180 unchanged. ItemInHandDescription ctor 0x668cb70, size 0x180 (max store +0x17F). Matrix-stack offsets unchanged: S=[ctx+0x18], ring data S+0x48, cap S+0x50, first S+0x58, count S+0x60, dirty S+0x78, drawArm arg1 = ctx+0x10.

## Corrections vs the earlier note oc_U-EI2c.md (a note is not proof; re-verified here)

- renderArm's **sole caller is sub_4e0df90** (the view-model render fn at `0x4e0e5e0`), NOT renderFirstPerson. renderFirstPerson does not call renderArm (no direct xref; ripscan of 0x530ab10 returns one site only).
- renderHands has exactly one caller (sub_4e0df90 at `0x4e0e459`); ripscan's second hit 0x524d674 is a false positive (no such reference in the disassembly; rdis xref agrees: 1 xref).
- renderFirstPerson calls renderItem/renderItemFull directly (`0x532eafb`, `0x5331634`).

## Residual [?]/[I] items (pre-existing leads, NOT part of the pending "1.26.62 re-check" line)

- renderItemFull 0x531b490 (= old 0x531b120 held-item/scale lead): located and called from renderFirstPerson [V], but its argument list / which argument is the held-item render scale is NOT decoded [?]; the 60.05 notes say it must be recovered from disassembly before any detour.
- Bare arm is skeletal, not an ItemInHand description: [I] conclusion from CE measurements on 1.26.60.05 (renderItem makes 0 calls for a bare hand); not re-measured on 1.26.62 (no live access, static analysis only).
- applyToPose 0x617a100 callers: no direct xref found (indirect/virtual) [I]; RVA confirmed by signature match in src/sdk/Sigs.json (applyToPose sig, unique match) [V].

## CLOSES?

CLOSES? YES — the pending part of the L12c line ("1.26.62 re-check") is proven by [V] rows above: every RVA from docs/first-person-hand-notes-1.26.60.md re-checked on 1.26.62 (BobHurt 0x53a1320, 0x4e0f7a0, renderFirstPerson 0x532b5a0, renderHands 0x530c700 with sole caller, drawArm 0x530a1b0 with all 5 sites, renderItem 0x531a580, renderItemFull 0x531b490, renderArm 0x530ab10 with sole caller, applyToPose 0x617a100), matrix-stack layout (ctx+0x18 -> S; ring S+0x48/+0x50/+0x58/+0x60/+0x78; ring-top index math; drawArm arg1 = ctx+0x10), clone 0x531b180 tag 6 -> insert vslot 0x378 with both renderItem call sites, tag-6 forwarder 0x6647320 -> extractor 0x6698e30, ItemInHandDescription ctor 0x668cb70 size 0x180 with max store +0x17F. Every quoted `0xRVA  instr` line was copied verbatim from the 1.26.62 exe disassembly (rdis/xref/ripscan). Corrections vs oc_U-EI2c.md noted above. Residual [?]/[I] items are pre-existing leads outside the pending line; item-level rule (RVAs/offsets written down; no header/hook listed for I2c) is satisfied.

## TOOL REQUESTS

None (existing rdis/xref/ripscan tooling sufficed; no helper scripts written).
