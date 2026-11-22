## NEXT
DONE

# U-EI2c: I2c Hands / held items — 1.26.62 re-check

Goal: close checklist item I2c ("Hands / held items — docs/first-person-hand-notes-1.26.60.md (6bh); 1.26.62 re-check pending", RENDER_CHECKLIST.md line 182; mirrored L12c line 374; prior-work index BGFX_MAP.md 6bh). DO ONLY the pending part = re-check every RVA/claim from the 1.26.60.05 hand notes against Minecraft.Windows.exe 1.26.62.01 (image-base RVAs). Static analysis only; every row carries a verbatim `0xRVA  instr` proof line verified against the exe.

Basis notes (1.26.60.05 RVAs): renderFirstPerson 0x532b230 -> renderItem 0x531a210, renderHands 0x530c390 (one caller); drawArm 0x5309e40 (3 sites in renderHands: 0x530c67c/0x530ca2c/0x530d039; 2 outside callers); renderArm 0x530a7a0; 0x531b120 world-wide held-item render (scale argument unknown); applyToPose 0x6179500; matrix stack ctx[+0x28]->[+0x18], ring +0x48 data / +0x50 capacity / +0x58 first / +0x60 count. 1.26.62 already known from sister unit L12c (ext-actors-hands.md): ItemInHandRenderer sigs resolve tick 0x5316030, renderFirstPerson 0x532b5a0, renderItem 0x531a580, renderArm 0x530ab10, renderItemFull 0x531b490; delta 60.05->62.01 for this class is +0x370 (renderItem 0x531a210->0x531a580), so old lead 0x531b120 = renderItemFull 0x531b490; clone 0x531b180 -> Item tag 6 -> extractor 0x6698e30; ItemInHandDescription sizeof 0x180.

## Re-checked on 1.26.62 (all rows [V], verbatim lines verified with rdis dis / callers / find against the exe)

| Name | RVA / offset | Size | Proof `0xRVA  instr` | Meaning | Tag |
|---|---|---|---|---|---|
| ItemInHandRenderer::tick | 0x5316030 | - | `0x5316030  push rbp` | entry; sig-scan match on 1.26.62 | [V] |
| ItemInHandRenderer::renderFirstPerson | 0x532b5a0 | - | `0x532b5a0  push rbp`; `0x532b5ac  sub rsp,0x268` | entry; BobHurt -> sub_4e0f7a0 -> this; calls renderItem 0x531a580, renderItemFull 0x531b490, ActorRenderDispatcher::render 0x594c5c0 | [V] |
| ItemInHandRenderer::renderItem | 0x531a580 | - | `0x531a580  push rbp`; `0x531a5ba  mov rdi,[rdx+0x28]` | entry; sole caller of thin clone 0x531b180 (2 call sites) | [V] |
| ItemInHandRenderer::renderItemFull | 0x531b490 | - | `0x531b490  push rbp` | old 60.05 lead 0x531b120 relocated (+0x370); world-wide held-item render, 11 xrefs incl. renderFirstPerson; item-scale argument NOT decoded | [V] |
| ItemInHandRenderer::renderArm | 0x530ab10 | - | `0x530ab10  push rbp`; `0x530b563  call 0x530A1B0`; `0x530c2c8  call 0x530A1B0` | animation state machine; calls drawArm x2 | [V] |
| renderHands | 0x530c700 | - | `0x530c700  push rbp`; `0x4e0e459  call 0x530C700` | exactly one caller: sub_4e0df90 (view-model render); drawArm sites 0x530c9ec, 0x530cd9c, 0x530d3a9 | [V] |
| drawArm | 0x530a1b0 | - | `0x530a1b0  push rbp`; `0x530c9ec  call 0x530A1B0` | arg1 = ctx+0x10; 5 xrefs total: renderHands x3, renderArm x2 | [V] |
| ctx+0x18 | 8 | `0x530ca14  mov r15,[rsi+0x18]` | S = render context owning the matrix-stack ring (rsi = renderHands ctx arg) | [V] |
| S+0x48 | 8 | `0x530ca2f  mov rcx,[r15+0x48]`; `0x530ca57  mov rcx,[r15+0x48]` | ring data pointer (both drawArm call-site epilogues) | [V] |
| S+0x50 | 8 | `0x530ca33  mov rdx,[r15+0x50]`; `0x530ca5b  mov rdx,[r15+0x50]` | ring capacity | [V] |
| S+0x58 | 8 | `0x530ca25  mov rcx,[r15+0x58]`; `0x530ca4d  mov rcx,[r15+0x58]` | ring first index | [V] |
| S+0x60 | 8 | `0x530ca21  mov rax,[r15+0x60]`; `0x530ca49  mov rax,[r15+0x60]` | ring count | [V] |
| S+0x78 | 1 | `0x530ca1c  mov byte ptr [r15+0x78],1` | ring dirty/use flag | [V] |
| ctx+0x10 | 8 | `0x530c9b9  lea rcx,[rsi+0x10]` | drawArm arg1 = ctx+0x10 | [V] |
| ring top index | - | `0x530ca29  add rax,rcx`; `0x530ca2c  dec rax`; `0x530ca3a  and rdx,rax`; `0x530ca3d  mov rdx,[rcx+rdx*8]` | top = ring[(first + count - 1) & (cap - 1)], 8-byte entries; matches notes layout | [V] |
| ItemInHand thin clone | 0x531b180 | - | `0x531b180  push rbp` | insert<ItemInHand>, Item group tag 6; only caller renderItem (2 sites) | [V] |
| ItemInHandDescription ctor | 0x668cb70 | 0x180 | `0x668cb70  push rbp` | description size 0x180 (ItemInHandDescription.h static_asserts, D5e) | [V] |
| ItemInHand extractor | 0x6698e30 | - | `0x6698e30  push rbp`; `0x6698e3c  mov eax,0x2158` | tag-6 handler via visitor/forwarder; stack frame 0x2158 | [V] |
| ActorAnimationControllerPlayer::applyToPose | 0x617a100 | - | `0x617a100  push rbp`; `0x617a161  movzx edx,byte ptr [rdi+0x40]` | 1.26.62 RVA (was 0x6179500; sig scan, 1 hit); reads this+0x40 (mActor per header) | [V] |
| BobHurt | 0x53a1320 | - | `0x53a1320  push rsi`; `0x4e0e331  call 0x53A1320` | view-model hurt shake; entry confirmed, called by sub_4e0df90 | [V] |

Key mappings 60.05 -> 62.01, all [V]: renderFirstPerson 0x532b230 -> 0x532b5a0; renderHands 0x530c390 -> 0x530c700; drawArm 0x5309e40 -> 0x530a1b0 (its 3 renderHands sites and renderArm's 2 sites land exactly +0x370); renderItem 0x531a210 -> 0x531a580; renderArm 0x530a7a0 -> 0x530ab10; renderItemFull 0x531b120 -> 0x531b490; applyToPose 0x6179500 -> 0x617a100; BobHurt 0x53a0fb0 -> 0x53a1320.

The matrix-stack layout quoted in the 60.05 notes is reproduced verbatim by the code: S = [ctx+0x18], ring data at S+0x48, capacity S+0x50, first S+0x58, count S+0x60, dirty byte S+0x78, top index (first+count-1)&(cap-1) over 8-byte ring entries, drawArm arg1 = [ctx+0x10].

## Residual opens (not part of the pending re-check line; listed for completeness)

- renderItemFull 0x531b490 (= old 0x531b120 lead): located and called from renderFirstPerson [V], but its argument list / which argument is the held-item render scale is NOT decoded [?]; per the notes it must be recovered from disassembly before any detour.
- Bare arm is skeletal, not an ItemInHand description: [I] conclusion from CE measurements on 1.26.60.05 (renderItem makes 0 calls for a bare hand); not re-measured on 1.26.62 (no live access).

CLOSES? YES — the pending part of the I2c line ("1.26.62 re-check") is proven by [V] rows above: renderFirstPerson 0x532b5a0, renderHands 0x530c700 (sole caller sub_4e0df90 at 0x4e0e459), drawArm 0x530a1b0 (5 xrefs: renderHands sites 0x530c9ec/0x530cd9c/0x530d3a9 plus renderArm sites 0x530b563/0x530c2c8), renderItem 0x531a580, renderArm 0x530ab10, renderItemFull 0x531b490 (old 0x531b120 lead), matrix-stack offsets ctx+0x18 / S+0x48 / S+0x50 / S+0x58 / S+0x60 / S+0x78 and the ring-top index math, drawArm arg1 = [ctx+0x10], clone 0x531b180 -> Item tag 6 -> extractor 0x6698e30 (sole caller renderItem, 2 sites), ItemInHandDescription ctor 0x668cb70 (size 0x180), applyToPose 0x617a100 (was 0x6179500), BobHurt 0x53a1320. Every quoted `0xRVA  instr` line was verified verbatim against the 1.26.62 exe (verify_oc clean, see check below). Residual [?]/[I] items are pre-existing note leads, not part of the pending line.

## TOOL REQUESTS

None (existing rdis/xref tooling sufficed; no helper scripts written).
