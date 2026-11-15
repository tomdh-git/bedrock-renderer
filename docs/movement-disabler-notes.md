# Movement disabler research notes

2026-11-03

## Goal

Hover 4 blocks above ground without kick and without desync. Once hover is proven, generalize to fly/speed/strafe.

## What the video shows

- First phase: player rises ~4 blocks, prints "0.0000" (probably mPosDelta.y or vertical velocity), stays in the air
- Waits 15 seconds — no kick. 15s may be max server delay-kick window
- After that, flies straight (vanilla-looking fly)
- Regular 20-tick timer, not a timer cheat
- Can also speed, strafe, take no velocity — all with the same method
- Note: "9300 hold time, 3 to hold, works 99%, one rare kick scenario" — this is from our Velocity developer (less reliable), NOT the SolsticeLite developer who made the working bypass in the video. Trust SolsticeLite patterns over this config.

## What we know about server checks

- **CorrectPlayerMovePrediction is NOT used** on this server (user confirmed)
- Server uses **MovePlayer** for teleports/resets (confirmed from CSV: reset=2 at dimension/spawn transitions)
- Server validates **PlayerAuthInput positions** — specifically the rate of position change between ticks
- Server has a **NetworkStackLatency (Ping) timeout** — unresponsive clients get kicked
- Severity tiers: gradual impossible movement = kick, instant teleport-like jump = ban

## Test results (2026-11-03 session)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| Ramp | Local velY ramp, PAIP carries honest position | **Kicked** | Server sees position climbing impossibly, detects via PAIP |
| Pin | High-gain snap to target, PAIP carries honest position | **Banned** | Instant large Y change treated as teleport hack (worse severity) |
| VelocityHold | Constant upward velY, PAIP carries honest position | **Kicked** | Sustained impossible upward velocity detected |
| Packet | Rewrites PAIP to pinned (anchor+4) position, zeros mPosDelta | **Desync** | Server doesn't kick for consistent stationary claim, but game state diverges |

**Key insight**: Packet mode survived (no kick) because the outgoing PAIP reports a consistent position. But it desynced because:
1. The first PAIP after enable jumps 4 blocks instantly (anchor → anchor+4)
2. Incoming MovePlayer corrections may be fighting the local position pin
3. No correction suppression — server may send resets that the client applies

## SolsticeLite patterns (same developer as the bypass)

Key observations from Disabler.cpp/TestModule.cpp:

1. **Timestamp shift, not just packet hold**: `onSendImmediateEvent` shifts outgoing Ping timestamps backward by `mDelay` ms. This is lower-level than holding packets — the response goes immediately but the server thinks it's from `mDelay` ms ago
2. **Flareon mode uses both**: timestamp shift on ALL pings + hold specific pings paired with knockback
3. **mTeleported flag**: When MovePlayer arrives, sets `mTeleported = true`. Next outgoing PAIP resets all damage state. The teleport is accepted, not cancelled
4. **MoveVectorFix**: Rewrites `mMove` in PAIP to match actual movement direction — enables sprint-in-any-direction
5. **No CorrectPlayerMovePrediction handling** at all in SolsticeLite either
6. **`-0.0784` magic number**: Standard MC gravity per tick (0.08 * 0.98). Used as "On Ground Spoof" for mPosDelta.y — makes server think player is falling at normal gravity
7. **RunUpdateCycleEvent cancel**: During knockback processing, cancels the game's update cycle to prevent applying velocity mid-computation (the "netskip")

## What to test next

### Hypothesis

The Packet desync was caused by (a) the instant 4-block jump in the first PAIP and (b) no incoming MovePlayer suppression. Fix both → hover works.

### New modes to implement

1. **Glide** — Gradual PAIP Y ramp (0.1 blocks/tick for 40 ticks = 4 blocks over 2s), then hold. Reports matching mPosDelta during ascent, zero during hold. Cancels incoming MovePlayer for local player. No latency hold.

2. **GlideCloaked** — Same as Glide + holds incoming Pings with rolling release every 3s (max age 9s). Tests whether adding the latency cloak prevents kicks that Glide alone might get.

### Test order

1. Enable Glide, hover for 30s. Report: kick/ban/desync/success + time.
2. If Glide desyncs: enable GlideCloaked, hover for 30s. Report same.
3. If kicked: note time-to-kick, check CSV for MovePlayer/correction packets before the kick.

## Test results (round 2)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| Glide | Gradual 0.1/tick Y ramp, mPosDelta.y=0.1, cancel MovePlayer | **Kick** | Gradual upward movement still detected |
| GlideCloaked | Same + held pings (3s rolling, 9s max) | **Ban** (= double kick, same severity) | Latency hold made it worse — delayed timeout accumulated more flags |

**Key insight**: Packet mode (instant pin, mPosDelta=0, no MovePlayer hook) survived with no kick. Glide was kicked. Three variables changed between them:
1. Position ramp: instant vs gradual
2. mPosDelta.y: 0 vs 0.1
3. MovePlayer: not hooked vs cancelled

The latency cloak on GlideCloaked made things worse, not better. The server accumulated movement violations while pings were held, then flagged twice on release.

### Next test: single-variable isolation from Packet baseline

1. **PacketCancel** — Instant pin + mPosDelta=0 + cancel MovePlayer. Isolates MovePlayer cancellation.
2. **GlideZeroDelta** — Gradual ramp + cancel MovePlayer + mPosDelta=(0,0,0). Isolates whether the 0.1 delta caused the kick.
3. **GlideGravity** — Gradual ramp + cancel MovePlayer + mPosDelta.y=-0.0784f. Tests SolsticeLite's "on ground spoof" approach.

## Test results (round 3 — single-variable isolation)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| PktCancel | Instant pin + mPosDelta=0 + cancel MovePlayer | **Desync** (no kick) | MovePlayer cancel is NOT the problem — same result as Packet |
| GlideZD | Gradual ramp + cancel MovePlayer + mPosDelta=0 | **Kick** | mPosDelta value doesn't matter — server ignores it |
| GlideGrav | Gradual ramp + cancel MovePlayer + mPosDelta=-0.0784 | **Kick** | Gravity spoof in delta doesn't help either |

**Confirmed:**
- The server checks **mPos change between consecutive PAIPs**, not mPosDelta.
- A consistent stationary position claim (even wrong) = no kick. A gradually changing position that defies physics = kick.
- MovePlayer cancellation has no effect on kick/no-kick.
- mPosDelta.y value has no effect on kick/no-kick (0, 0.1, -0.0784 all same result).

**Next direction:** Fix the desync in Packet mode. The instant pin survives anti-cheat — we just need the server to accept our claimed position.

## Test results (round 4 — desync fix attempts)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| PktHold | Instant pin + hold pings 2s then release | **Desync** | Latency spike doesn't help the server accept the position |
| PktStep | Claim ground 40 ticks then jump to target | **Desync** | Timing of the jump doesn't matter either |

Both desync the same as base Packet. The desync isn't caused by the instant jump timing or latency. It's more fundamental.

**Key discovery from SolsticeLite source (TestModule.cpp Fly mode):**
- When MovePlayer setback arrives, SolsticeLite sends a PAIP with `HANDLED_TELEPORT` flag + the server's position to acknowledge it
- SolsticeLite does NOT cancel MovePlayer — it accepts the teleport, then acknowledges it
- The server likely requires teleport acknowledgment before it updates its authoritative position
- Without `HANDLED_TELEPORT`, the server keeps the player at its own position = desync

### Round 5: HANDLED_TELEPORT acknowledgment

**PacketAck** — Ack with HANDLED_TELEPORT at our TARGET position.
**PacketAck2** — Ack with HANDLED_TELEPORT at the SERVER's position (MovePlayer.mPos), then resume target next tick. This mirrors SolsticeLite's exact pattern: `acceptNigga->mPos = mpp->mPos`.

## Test results (round 5 — HANDLED_TELEPORT ack)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| PktAck | Instant pin + ack MovePlayer with HANDLED_TELEPORT at OUR target Y | **Desync** | Acking at the wrong position doesn't help — server ignores the ack if position doesn't match |
| PktAck2 | Instant pin + ack at SERVER's Y, then resume target next tick | **Kick** | The position jump from ack-at-server-Y to next-PAIP-at-target-Y triggers the same kick |

**Key insight**: HANDLED_TELEPORT alone doesn't solve desync. PktAck2's kick confirms: ANY position change between consecutive PAIPs triggers kick. The server's anti-cheat rule is absolute for position deltas.

**Fundamental problem identified**: PAIP-only position rewriting cannot achieve both no-kick AND no-desync. The server:
1. Kicks for any position change between consecutive PAIPs (rules out gradual movement)
2. Ignores position claims that don't match its authoritative state (causes desync for instant pin)
3. The HANDLED_TELEPORT flag doesn't override either check

SolsticeLite uses a completely different approach: Disabler (latency/timestamp manipulation) + Fly (actual game physics movement + batch PAIP flush). The disabler provides a window where the server delays its anti-cheat checks.

## Round 6: Two new theories

**NoPin** — Same PAIP rewrite as Packet (claim target Y, delta=0) but do NOT pin local state. Game engine moves player normally (stays on ground). Tests whether the desync was caused by us fighting the engine's position vs. just the PAIP lie. Cancel MovePlayer.

**BatchFly** — SolsticeLite-style: give player upward velocity (actual physics jump), cancel ALL outgoing PAIPs during flight (store positions), on disable flush all stored PAIPs with Y set to ground level + 2 extra at +2.0f. Tests the batch-send approach. Cancel MovePlayer during flight.

Note: video shows ~1 block hover, not 4. Testing at 4 blocks first (our constant), can reduce later.

## Test results (round 6 — batch approach)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| NoPin | PAIP rewrite to target, NO local state pin, cancel MovePlayer | **Desync** | Desync isn't from engine fighting; it's from the server's authoritative position diverging |
| BatchFly | Real physics jump, cancel all PAIPs, flush at ground Y on disable | **Works while active** (no kick, no desync, can interact). Kick on disable or after too long | Cancelling PAIPs entirely = server freezes at last position = no desync. Flush sends malformed synthetic PAIPs (zeroed fields). Duration kick = server PAIP starvation timeout |

**BREAKTHROUGH**: BatchFly proves cancelling PAIPs keeps server position frozen while allowing real client movement. Two problems remain:
1. **Disable kick**: Flush sends synthetic PAIPs with zeroed mClientTick, mInputMode etc. → "unrecognized input" (not anti-cheat)
2. **Duration kick**: Server times out after receiving no PAIPs for too long

### Round 6b: Fix both issues

**BatchNoFlush** — Same as BatchFly but NO flush on disable. Just drops stored PAIPs and lets next natural PAIP go through. Tests if flush is the disable-kick cause.

**BatchAlive** — Cancel most PAIPs but let one through every 20 ticks, rewritten to anchor (ground) position. No flush on disable. Tests if keepalive PAIPs prevent the duration timeout.

## Test results (round 6b)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| BatNoFlush | Cancel all PAIPs, no flush on disable | Worked first time, then kicked on subsequent disables. Desynced block mining while up (menus worked because they're client-side) | Position jump on PAIP resume (client at height, server at ground) triggers kick. "Menu click" was a false positive for desync test |
| BatAlive | Keepalive PAIP every 20 ticks at ground pos | **Banned** | Sparse PAIPs (1/sec vs normal 20/sec) look extremely suspicious to anti-cheat |

**Key insights:**
- Cancelling ALL PAIPs is better than sparse keepalives — silence is less suspicious than abnormal rate
- Block mining while hovering IS desynced (server position at ground) — menu clicks are client-side only
- The kick on disable is from the position jump when PAIPs resume: server sees jump from ground to midair
- BatchNoFlush's intermittent success suggests the kick might be delayed/accumulated — sometimes the first violation is silent-flagged

### Round 7: Two theories

**BatchGround** — Cancel PAIPs during hover, on disable teleport player back to anchor position before PAIPs resume. Tests: if we return to the server's known position, no position jump → no kick. Confirms the position-jump-on-resume theory.

**BatchTimer** — Cancel PAIPs for 10 seconds, then start sending PAIPs at the player's real position (no rewrite). Tests: does the server reset position tracking after a PAIP gap? The video showed ~15s wait before moving — maybe the server "forgets" the old baseline and accepts the new position. If this works, we've found the timer window.

## Test results (round 7)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| BatGround | Cancel PAIPs, snap to anchor on disable | First test ambiguous (block/slab clip), then kick on flat ground | Server flags during PAIP gap regardless; snap-back doesn't prevent kick |
| BatTimer | Cancel PAIPs 10s, then resume at real pos | **Kick at ~10s** | ~10s is server PAIP starvation timeout. NO position reset after gap — server remembers last position |

**Critical finding**: Server PAIP starvation timeout is ~10s. The server does NOT reset position tracking after a PAIP gap. Cancelling PAIPs is a dead end for anything longer than a few seconds.

**New direction**: We need to SEND PAIPs (not cancel them). Going back to what partially worked:
- Packet mode (constant PAIP at target): no kick, but desync
- The video shows only ~1 block hover, not 4
- The "timer" aspect is likely **ping timestamp manipulation** — SolsticeLite Disabler shifts outgoing ping timestamps to inflate server-calculated RTT, making the server more tolerant of position drift

### Round 8: Ping hold + reduced height

**Packet1** — Same as Packet but only +1 block instead of +4. Tests if 1-block drift avoids desync (lower threshold might be accepted by server).

**PingHover** — Hold incoming pings for 10s + constant PAIP at +1 block + pin local state. After 10s, release all pings. The held pings inflate server-calculated RTT, potentially making the 1-block position drift acceptable. This mimics SolsticeLite's core mechanism: Disabler (ping hold → inflated RTT) + Fly (position claim).

## Test results (round 8)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| Packet1 | Constant PAIP at +1 block (instead of +4) | **Desync** | Height doesn't matter — server rejects ANY position claim that disagrees with its physics |
| PingHover | Constant PAIP at +1 + hold pings 10s | **Desync** | Holding pings doesn't make server accept wrong position claims |

**Critical realization**: The server runs its own physics simulation using PAIP INPUT data (movement keys, jump, rotation), NOT the claimed position. The server validates its calculated position against the PAIP's claimed position. If they disagree → server keeps its own position → desync. No amount of ping manipulation fixes a position claim the server's physics doesn't agree with.

### Round 9: Timestamp shift + PAIP cancellation

**ShiftFly** — SolsticeLite's actual Disabler mechanism: on incoming Pings, cancel auto-response, immediately echo with createTime shifted backward by 15s. Server calculates RTT = real_RTT + 15s → thinks we're very laggy. ALSO cancel all outgoing PAIPs (like BatchFly). The inflated RTT should extend the PAIP starvation timeout (base ~10s) past the hover duration. Player moves with real physics (jump). On disable: stop cancelling, let natural PAIPs resume.

Theory: BatchFly worked for ~10s because the PAIP starvation timeout is ~10s. With ShiftFly inflating RTT by 15s, the timeout should extend to ~25s — enough for the hover + vanilla fly phase from the video.

## Test results (round 9)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| ShiftFly | Ping timestamp shift -15s + cancel all PAIPs + physics jump | First disable: no kick. Second disable: **kick** | Ambiguous — could be silent flag on first, kick on accumulated second. Or shift works but needs refinement |

**Note**: Same pattern as BatchNoFlush (first disable OK, second kicks). The "first success" is likely a silent flag — server accumulates violations and kicks on the second occurrence within a window.

### Round 10: Warmup phase

**ShiftFly2** — Two-phase approach:
- Phase 1 (0-5s): Shift ping timestamps but keep sending PAIPs normally. Server registers inflated RTT. Player stays on ground.
- Phase 2 (5s+): Start cancelling PAIPs + physics jump. Server now has high RTT registered, so its starvation timeout should be extended.

This tests whether the server needs time to register the inflated RTT before PAIP cancellation becomes safe. The video showed the guy waiting before moving — this could be the warmup.

Watch for: does the first disable still silent-flag? If so, the ping shift isn't helping and we need a fundamentally different approach.

## Test results (round 10)

| Fly Mode | What it does | Result | What it tells us |
|---|---|---|---|
| ShiftFly2 | 5s warmup (shift pings, PAIPs flow) then cancel | First disable: no kick. Second disable: **kick** | Same silent-flag pattern — ping timestamp shift at packet level doesn't help |

**Key finding**: Our packet-level ping shift doesn't work. SolsticeLite's Disabler shifts at the raw network byte level (SendImmediateEvent), which is fundamentally different from our approach (cancel + re-echo at packet API level). The server may detect the difference.

### SolsticeLite re-read findings (critical)

**SolsticeLite Fly is NOT a sustained hover — it's a hop-by-hop cycle:**
1. First 2 ticks: set Noai flag, cancel PAIPs
2. On ground: `jumpFromGround()`, record Y
3. First time in air: double jump (velocity.y = 0.42f), set `hasPrev`
4. While `hasPrev && !extraHopping`: cancel PAIPs, store positions
5. Flush: send stored positions at ground Y (removeAllInputData, mClientTick=0, mMove={0,1}, Y with tiny offset)
6. 2 extra packets at +2.0f with mMove={0,0}
7. Wait for server MovePlayer setback
8. Ack with HANDLED_TELEPORT at server position
9. Jump again → cycle

**SolsticeLite Disabler timestamp shift uses SendImmediateEvent** — raw byte manipulation AFTER serialization, not packet-level API. We'd need a network-layer hook to replicate this.

### Round 11: HopFly (hop-by-hop cycle)

**HopFly** — Implements SolsticeLite's actual fly pattern:
- Phase INIT (2 ticks): Let PAIPs through with mMove cleared (no movement input)
- Phase JUMP: Set velocity.y = 0.42f, let PAIP through with START_JUMPING flag
- Phase AIR: Cancel PAIPs, store them. Let physics run (gravity).
- Phase FLUSH (after 6s): Send all stored PAIPs at ground Y using SolsticeLite format (cleared input data, mClientTick=0, mMove={0,1}, Y with tiny descending offset) + 2 extra at +2.0f
- Phase WAIT_SETBACK: Wait for server MovePlayer, then ack with HANDLED_TELEPORT at server pos
- Cycle back to JUMP

Differences from SolsticeLite: no Noai flag (we don't have it), no jumpFromGround() (we set velocity directly), timer-based flush (6s) instead of landing detection.

### Round 12: SilentFly (zero synthetic packets)

**SilentFly** — Sidesteps the malformed synthetic packet bug entirely:
- **Phase SILENT_AIR (6s)**: Freeze/cancel all outgoing PAIPs during air time (server remains stationary at last confirmed ground state).
- **Phase SILENT_RESUME**: Snap player back to ground `mAnchor` before un-muting outgoing PAIPs, preventing instant midair position-jump kicks.
- **Correction Handling**: Intercept incoming `MovePlayer` corrections and acknowledge them via `HANDLED_TELEPORT` on the very next natural client-generated PAIP.
- **Result**: Banned on second disable. Silent starvation flag accumulates during silence; second occurrence triggers ban.

## Test results (round 13 — physics & delta probes)

| Fly Mode | What it does | Result | Deep analysis |
|---|---|---|---|
| GravHover | Simulated jump (vel=0.42, grav=-0.0784) | **Kick**, rapid up/down teleports | Setback loop. In code, `pos <= baseY` immediately triggered jump in same tick without ever spending a tick on ground. Server flagged illegal air-jump. |
| MicroStep | Y += 0.005/tick | Lifted fine briefly, then **Kick** (up/down teleports) | Server has ~0.05-0.1 block distance tolerance. Once cumulative error passed threshold, setback loop began. |
| DeltaMis | Simulated jump with forced `mPosDelta = 0` | **Ban**, full desync | Absolute mathematical contradiction (`mPos - prevPos = 0.42` vs `delta = 0`). Server caught packet fabrication. |
| DesyncCycle | 4s hover + 500ms ground snap/ack | **Full desync**, rapid teleports | Cancelling setbacks during hover corrupted server position tracking; 500ms ack window could not recover state. |
| VelOnly | `vel.y = 0.0784`, honest pos, delta forced 0.0784 | **Kick**, was smooth until kick | **100% smooth for 756ms (15 ticks)**! Zero jitter/setbacks because pos wasn't pinned. Kicked after 15 ticks because `mPos` was stationary while `mPosDelta` claimed +0.0784. |
| TickSkip | Skip 3 ticks, send on 4th matching physics | **Kick**, rapid teleports | Server advances physics on its own 20Hz clock; 3-tick gap caused simulation divergence. |
| GravScale | Jump with weaker gravity (-0.06 vs -0.0784) | Rapid teleports, desync | 23% deviation exceeded server trajectory tolerance within 3 ticks. |

## Core insights: what makes the server accept vs reject

1. **The Zero-Contradiction Law**:
   `payload.mPosDelta` MUST EQUAL `payload.mPos - mPosPrev`. Any discrepancy is flagged immediately (15 ticks for slow mismatch, instant ban for 0.42 jump mismatch).

2. **Why "teleporting up/down" (jitter) happens**:
   Whenever a mode forces `mPos` that deviates from server physics, the server fires `MovePlayer` setbacks. Cancelling `MovePlayer` in `onPacketIn` does NOT stop the server; the server refuses subsequent PAIPs until `HANDLED_TELEPORT` is acknowledged. The client and server fight at 20Hz until kick.

3. **Why VelOnly was smooth**:
   VelOnly did NOT pin position; the client game engine integrated naturally. If delta is made honest (`delta = 0` when `pos - prevPos = 0`), there is NO packet contradiction!

4. **1-Block Hover Physics**:
   In vanilla Minecraft, a jump naturally reaches an apex of ~1.1 blocks above ground at tick 6 where vertical velocity is `0.0000`. Hovering ~1 block is physically adjacent to a jump apex.

## Round 14: Breadth & depth test suite (all at 1 block hover)

All modes now use `kHoverHeight = 1.0f` and maintain 100% honest `mPosDelta`.

| Mode | Hypothesis (How to make server accept it) | Mechanism |
|---|---|---|
| **VelHonest** | Hover at +1 block without delta contradiction. | `state->mPos.y = mAnchor.y + 1.0f`, `mPosDelta = (0,0,0)`. Measures true baseline server air-time threshold. |
| **MicroGlide** | Sub-threshold falling avoids zero-velocity hover check. | Descends at `-0.015f`/tick (~3.3s/block). Honest delta. Tests if any downward velocity passes the fly check. |
| **BounceHover** | True vanilla jump cycle with 2 ground ticks. | 2 ticks on ground (`vel=0, onGround`) -> jump (`0.42f, START_JUMPING`) -> natural gravity fall -> land -> repeat. 100% legal vanilla jumping. |
| **ApexExtend** | Hold jump apex at +1.1 blocks before falling. | Vanilla jump -> at apex (tick 6, vel~0), hold for 5 ticks (250ms) -> fall naturally -> land 2 ticks -> jump. Tests apex deadzone tolerance. |
| **PulseHover** | Duty-cycle breaks consecutive air-time accumulator. | 8 ticks hover (vel=0) -> 3 ticks drop (-0.0784) -> 3 ticks recover (+0.0784). Honest deltas. Clears violation buffer before threshold. |
| **ColSpoof** | Server respects client `VERTICAL_COLLISION` flag. | Hover at +1 block, sets bit 50 (`VERTICAL_COLLISION`). Tests if server treats player as resting on a solid block. |
| **GlideSpoof** | Server activates Elytra physics branch. | Hover at +1 block, sets bit 32 (`START_GLIDING`). Tests if gliding state relaxes vertical velocity checks. |
| **SwimSpoof** | Server activates water buoyancy physics. | Hover at +1 block, sets bit 29 (`START_SWIMMING`) and bit 7 (`AUTO_JUMPING_IN_WATER`). |
| **ClimbSpoof** | Server activates scaffolding/ladder climbing physics. | Hover at +1 block, sets bit 0 (`ASCEND`), bit 21 (`ASCEND_BLOCK`), bit 5 (`CHANGE_HEIGHT`). |
| **SneakHold** | Server sneak ledge-clamp prevents gravity expectation. | Hover at +1 block, sets bit 8 (`SNEAKING`), bit 9 (`SNEAK_DOWN`), bit 24 (`PERSIST_SNEAK`). |
| **AckSurf** | Surfs server setbacks cleanly without jitter. | Hover at +1 block. When `MovePlayer` arrives: accepts server position, sends `HANDLED_TELEPORT`, next tick launches legal jump (`0.42f`). |
| **PingStall** | Ping buffering delays server movement check execution. | Hover at +1 block, holds incoming `NetworkStackLatency` for 3000ms, then releases. |

## Round 15 — real 44-48 + probe modes

**The previous 44-48 results were Ramp aliases and are invalid.** RakDisabler, NativeHop, ApexGlide, CleanAckHop and AirBuffer had state variables but no behaviour branches, so every test of those five actually ran the default Ramp velocity loop. They are now implemented as distinct state machines and never fall through to Ramp.

### Correction handling change

Every mode from 44 to 65 now **accepts** the server's `MovePlayer` instead of cancelling it:

- `Fly::applyServerCorrection(pos, reset)` writes `state->mPos`/`mPosPrev`, zeroes velocity, stores `mServerY`/`mServerPos`, increments `mCorrectionCount`, timestamps the correction and logs `[fly] correction serverY ... reset ... claimedY ... elapsed ...ms`.
- The next outgoing PAIP sets `PlayerAuthInputData::HANDLED_TELEPORT` (0x25, present in the SDK) and carries `mServerPos` with zero delta. No SDK bit was missing.
- Modes 44/65 freeze outgoing PAIPs, so any correction during the freeze is stored and acknowledged by the first resume PAIP.
- Existing intentionally-cancelling modes (Packet/PacketCancel/PacketHold/Ack/Ack2, Batch/Shift families, Glide family and the old probe modes) keep their old cancel behaviour.
- Each new mode also logs once per second: `[fly] mode {} y {} velY {} target {} corrections {}`.

All new modes (44-65) use the existing 1-block target (`kHoverHeight = 1.0f`).

### Modes and hypotheses

| # | Mode | Hypothesis |
|---|---|---|
| 44 | RakDisabler | 5 s PAIP freeze, then resume at the server's own Y: the disable/resume kick comes from flushing hover-position PAIPs, not from the silence. |
| 45 | NativeHop | A legal jump arc plus a 3-tick apex hold is accepted; landing resets the server's air-time counter. |
| 46 | ApexGlide | Glide is a legal slow-fall; setting `START_GLIDING` and a downward pitch at the apex may be accepted for a 2 s descent. |
| 47 | CleanAckHop | Accepting and acking the server teleport, then jumping from its position, avoids the cancel/teleport fight. |
| 48 | AirBuffer | A 3-PAIP (~150 ms) gap at the apex pauses the air-time/flag timer without hitting starvation. |
| 49 | JumpHold100 | A 100 ms apex pin isolates a short hold threshold from ascent. |
| 50 | JumpHold250 | As above, 250 ms. |
| 51 | JumpHold500 | As above, 500 ms. |
| 52 | JumpHold750 | As above, 750 ms. |
| 53 | JumpHold1000 | As above, 1000 ms. |
| 54 | Drift001 | Position tolerance: claiming the server correction Y + 0.02 blocks/s should survive; correction near +0.001 means tolerance ~0. |
| 55 | Drift005 | Claim + 0.1 blocks/s: measures a mid-range position tolerance. |
| 56 | Drift01 | Claim + 0.2 blocks/s: measures a wider position tolerance. |
| 57 | AckThenJump | A legal jump from the server's corrected position, with the teleport acked, is accepted. |
| 58 | AckThenHold | Same as 57 plus a 500 ms apex pin, to test hold tolerance from a clean base. |
| 59 | HopCycle | Repeated legal jumps with 2 ground ticks reset the air-time flag; no apex hold. |
| 60 | HopCycleApex | Same as 59 plus a 3-tick (60 ms) apex hold with no position pin. |
| 61 | CollisionStand | `VERTICAL_COLLISION` (0x32) + `HORIZONTAL_COLLISION` (0x31) make the server treat +1 as standing on a block. |
| 62 | GlideBit | A jump into a legal glide slow-fall is accepted when the glider item is not required. |
| 63 | ClientTickZero | `mClientTick = 0` skips the server's movement validation for that PAIP. |
| 64 | Rate10 | Halving the PAIP rate widens interpolation/tolerance. |
| 65 | BatchResume | The 44 pattern without waiting indefinitely: 5 s freeze, then 1 s of PAIPs at the server Y, then disable. |

### Suggested test order

1. `JumpHold500`
2. `JumpHold250` / `JumpHold750`
3. `Drift005`
4. `AckThenJump`
5. `HopCycleApex`
6. `CollisionStand`
7. `BatchResume`
8. Real 44-48 (`RakDisabler`, `NativeHop`, `ApexGlide`, `CleanAckHop`, `AirBuffer`)

For each run record kick/ban/desync + time, the once-per-second `[fly] mode ...` lines, and every `[fly] correction ...` line. Compare the correction Y against the claimed Y to read the server's tolerance directly.

## Round 16 — timing, ack, and reset probes

The collision/input-bit spoofs (`ColSpoof`, `SwimSpoof`, `ClimbSpoof`, `SneakHold`, `CollisionStand`, `GlideBit`) are now **controls, not the main path**. The server recomputes collision and water/climb/sneak state from its own world, so those bits only produce a correction/desync; they do not make +1 block legal. Round 16 moves to the parts that have not been isolated yet: the correction/teleport state machine, PAIP tick/timing, flag-reset actions, and tracking suppression.

All modes 66-77 pin at +1 block (`kHoverHeight = 1.0f`), accept every local `MovePlayer` through `applyServerCorrection`, and acknowledge it on the next outgoing PAIP with `HANDLED_TELEPORT` (0x25). None of them cancel the local correction.

| # | Mode | Hypothesis | Mechanism |
|---|---|---|---|
| 66 | Rate5 | A 5 Hz PAIP stream widens the server's interpolation/tolerance window without hitting the ~10 s starvation timeout. | Send 1 of every 4 PAIPs; pin +1, `mPosDelta = 0`. |
| 67 | TickSkew3 | Advancing `mClientTick` by 3 per PAIP makes the server's tick accounting drift in our favour. | `mFakeTick` seeded from the first PAIP, +3 per PAIP. |
| 68 | TickJump100 | A one-off +100 tick jump resets/skips the server's movement-validation window. | First PAIP adds 100 to `mFakeTick`, then +1 per PAIP. |
| 69 | TickDup | Repeating a tick for two PAIPs (without cloning the packet) makes the server treat the pair as one movement step. | Same `mClientTick` twice, then increment and repeat. |
| 70 | TickRewind | A far-past `mClientTick` (100000 and falling) sidesteps the current-tick validation branch. | `mFakeTick` starts at 100000, decrements by 1 per PAIP. |
| 71 | AckDelay500 | Holding the `HANDLED_TELEPORT` ack for 500 ms makes the server re-evaluate the correction before we resume. | First correction applied, then PAIPs echo `mServerPos` with no ack for 500 ms; ack, jump, 3-tick apex, fall. |
| 72 | AckDelay1000 | As 71 with a 1000 ms hold, to find the ack-timeout boundary. | Same state machine, 1000 ms wait. |
| 73 | TeleportHold | A 2000 ms hold keeps the correction pending long enough for the server to reset its own tracking. | Same state machine, 2000 ms wait; later corrections update `mServerPos` but keep the deadline unless `reset != 0`. |
| 74 | ActionReset | A legal `PlayerAction` (start/stop sprint) resets the server's movement/air-time flag state. | Every 500 ms send `PlayerActionPacket` with `StartSprinting`/`StopSprinting`. |
| 75 | PingReset | A periodic fresh latency ping resets the server's timing/stall accumulation. | Every 500 ms `PacketHook::echoLatency(now)`. |
| 76 | LandReset | A brief real ground contact resets the server's air-time flag even if the hover resumes immediately. | 500 ms pinned +1, 100 ms unpinned drop (or until `pos.y <= anchor.y + 0.05`), repeat. |
| 77 | VehicleBit | The server skips player movement validation while the client claims a predicted vehicle. | `IN_CLIENT_PREDICTED_IN_VEHICLE` every PAIP, jump bits cleared. |

### SDK gaps and fallbacks

- `PlayerActionPacket`, `PlayerActionPacketPayload`, and `PlayerActionType` all exist in the SDK, so `ActionReset` sends the real packet (runtime id from `LocalPlayer::getRuntimeID()`); no input-bit fallback was needed.
- `PlayerAuthInputData` has `IN_CLIENT_PREDICTED_IN_VEHICLE` (0x2D) but **no `CLIENT_PREDICTED_VEHICLE`**. `VehicleBit` logs a warning at enable and falls back to `START_GLIDING` (0x20) for the second bit.
- All new modes reuse the existing `applyServerCorrection` / `mNeedAck` / `mServerPos` / `mServerY` / `mLastCorrectionMs` / `mCorrectionCount` state from 44-65.

### Suggested test order

1. `Rate5`
2. `TickDup` / `TickSkew3`
3. `AckDelay500` → `AckDelay1000` → `TeleportHold`
4. `LandReset`
5. `ActionReset` / `PingReset`
6. `VehicleBit`
7. `TickJump100` / `TickRewind`

Record kick/ban/desync + time, the once-per-second `[fly] mode ...` line, every `[fly] correction ...` line, and (for 71-73) the elapsed time between the first correction and the ack.

## Round 17 — ground detection fix and SafeHop

### Live results that motivated this round

| Mode | Live result | Conclusion |
|---|---|---|
| `JumpHold100` (49) | **Accepted** — no corrections, no kick | A legal jump + 100 ms apex hold + real landing is the accepted method |
| `JumpHold250` (50) | More flags, kick after a few tries | The per-jump apex-hold budget is ~100 ms (2 ticks at 20 Hz) |
| `NativeHop` (45) | Works on flat ground; jumps midair after walking off a block, gets corrected and kicked | Legal jumps are accepted; the old ground check (`mAnchor.y`) is the bug |
| `HopCycle` (59) | Works standing still; kicks while sprinting | Same ground bug plus air-time accumulation while moving |
| `HopCycleApex` (60) | No corrections, kicks after ~2 s "in air" | Never lands because the ground check is wrong |
| `Drift001` (54) | Kicked after 1-2 s even at 0.02 b/s | Any changing claimed position is flagged; a constant +1 offset is only corrected |
| `ClientTickZero`, `Rate10`, `Rate5`, `TickSkew3`, `TickJump100`, `TickDup`, `TickRewind`, `AckDelay500`, `TeleportHold`, `ActionReset`, `PingReset`, `LandReset`, `BatchResume` | Lagback or kick | Tick/rate/ack/action/ping/position-pin resets are disproven |
| `AckThenJump` (57), `AckThenHold` (58) | "Do nothing" | They waited for a correction but never claimed +1, so no correction arrived |
| `RakDisabler` (44) | Freeze works, resume cycles then kicks | A freeze/resume probe, not a hover |
| `AirBuffer` (48) | Kicks after the first full jump | PAIP gaps at the apex are detected |
| `ApexGlide` (46), `CleanAckHop` (47) | Confounded by midair enable/toggle | Not reliable evidence |

**Conclusion:** continuous hover is disproven. The only accepted vertical method is a **legal jump + at most 100 ms apex hold + a real landing**, repeated. Modes 78-80 test that cycle under progressively less restricted horizontal conditions instead of adding more tick/rate/ack probes.

### Shared ground-detection algorithm

Modes 45, 59, 60, 78, 79 and 80 now share one state machine in `Fly::updateGroundHop` with state
`mGroundY`, `mGroundTicks`, `mGrounded`, `mHopPhase` (`GH_GROUND` / `GH_AIR` / `GH_HOLD` / `GH_FALL`),
`mApexY` and `mHoldStartMs`. It never uses the enable-time anchor as the ground height.

- **GROUND:** `still = |velocity.y| <= 0.01`. After 2 consecutive still updates, `mGroundY = pos.y`
  and `mGrounded = true`, so stepping up/down updates the ground after two ticks. Any unstable update
  clears the counter and `mGrounded`. Walking off a block (negative velocity or a drop below
  `mGroundY`) transitions to FALL; no midair jump is issued.
- **Jump:** only from GROUND with `mGrounded`. Sets `velocity.y = 0.42`, requests the jump input bits
  for that outgoing PAIP, then enters AIR. X/Z are never pinned.
- **AIR:** at `velocity.y <= 0 && pos.y >= mGroundY + 0.8`, records `mApexY` and enters HOLD
  (NativeHop, HopCycleApex, SafeHop*) or FALL (HopCycle, which has no hold).
- **HOLD:** for 100 ms pins only Y (`pos.y = mPosPrev.y = mApexY`, `velocity.y = 0`) and rewrites the
  outgoing PAIP's Y to `mApexY` with `mPosDelta.y = 0`. Horizontal position and delta stay untouched.
- **FALL:** no position writes. A landing is `pos.y <= mGroundY + 0.05` with the engine's velocity
  back near zero; then `mGroundY = pos.y`, `mGroundTicks = 0`, back to GROUND.
- **Correction:** every hop mode accepts local `MovePlayer` through `applyServerCorrection`, sets
  `mNeedAck`, and acknowledges on the next PAIP. A correction while airborne resets the machine to
  GROUND at the server's Y so the next cycle starts from a real surface.
- Logging: `[fly] hop phase {} groundY {} posY {} velY {} grounded {}` once per second, plus one line
  on every jump and every landing.

### New modes (78-80)

| # | Mode | Purpose |
|---|---|---|
| 78 | `SafeHop` | Flat ground, standing still. Same legal hop as above, 2-tick apex hold, dynamic ground Y. Establishes the clean baseline. |
| 79 | `SafeHopMove` | Same hop with normal horizontal movement (no sprint). Isolates whether moving while hopping causes corrections. |
| 80 | `SafeHopSprint` | Same as `SafeHopMove` with sprint allowed. Run last to isolate the sprint kick. |

Modes 57/58 now pin at `mTargetY` in `AH_WAIT` (position, previous position and delta), so the server
actually sends the correction. On the first local `MovePlayer` they apply/ack it and jump; if none
arrives within 1000 ms they log and jump anyway.

### Test order

1. `SafeHop` on flat ground, standing still, 30 s.
2. Same while walking off a block onto lower ground: it must fall, update `mGroundY`, and resume.
3. `SafeHopMove` (walk, no sprint), 30 s.
4. `SafeHopSprint`, 30 s.
5. Re-run `NativeHop` / `HopCycle` / `HopCycleApex` to confirm the ground fix on the old probes.

Record kick/ban/desync + time, the `[fly] hop phase ...` lines, and every `[fly] correction ...`
line. A correction means the server rejected the claimed position; no correction and no kick across
the full run is the success condition.
