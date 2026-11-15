# test1.json config analysis

2026-11-03 · `%APPDATA%\BlueySenseV2\configs\test1.json` (version 1) · captured during random input, not a designed experiment; backup at `%APPDATA%\BlueySenseV2\configs\backups\test1_20261103_195619.json`.

## TL;DR

`test1.json` is a four-variable confound: Fly in `Hover`, `Anchor Outgoing Pos`, `Zero Outgoing Move`, and `Hold Latency` at 9300 ms all run at once. If `Set Anchor` was pressed at any point, the client moves locally while every outgoing `PlayerAuthInput` reports a pinned position, so the server never sees the player move and no result from this session can be attributed to movement code. It also tests zero inbound cancellation: `Cancel Set Motion` and `Cancel Move Player` are both false, so inbound `SetActorMotion`/`MovePlayer` handling was never exercised. Phase 0 already shows the server does not correct ordinary position, which inverts the order this config implies.

## What is enabled

Movement-relevant modules:

| Module | Settings | Effect while enabled |
|---|---|---|
| `fly` (bind 70) | Mode `Hover`, Speed 0.5, Vertical Speed 0.5, Stop On Disable true | `onEnable` captures `mHoverY = state->mPos.y`; `onUpdate` writes `mVelocity.x/z` from WASD × 0.5, pins `mPos.y = mHoverY`, and forces `mVelocity.y = 0` |
| `test_module` | Log Incoming/Outgoing/State true, `State Interval` 0.5, `Hold Latency` true, `Auto Release Ms` 9300, `Anchor Outgoing Pos` true, `Zero Outgoing Move` true, `Lift Amount` 4; `Cancel Set Motion`, `Cancel Move Player`, `Cancel Prediction`, `Freeze Position`, `Hover Y`, `Cancel Outgoing Auth Input` all false; `Set Anchor`, `Lift Now`, `Release Held`, `Reset` serialize as `null` | Rewrites outgoing `PlayerAuthInput` (anchor and/or zero move), holds inbound `Ping`, logs packets and state |
| `velocity` | Mode `Flareon`, Horizontal 100, Vertical 100, Hold Time 9300, Velos To Hold 3, Timer Reset true, Replay Knockback false | Disabled; settings are inert |

Disabled movement modules whose settings persist but do nothing here: `speed` (Static 0.5), `sprint` (Always, 5 ticks), `movefix` (Input + Fix Input Flags + Sprint Any Direction + Only When Moving), `fast_stop` (On Ground), `disabler`.

Enabled non-movement modules: `anti_bot` (Mode Custom; Hitbox, Player, Invisible, PlayerList checks true, Name false), `reach`, `esp`, `ambience`, `interface`, `lce_graphics`, `motion_blur`, `viewhands`, `device_spoofer`, `array_list`.

For a movement run these should all be off. `anti_bot` and `reach` emit combat packets and rotate/aim on their own, which interleaves unrelated traffic with the movement stream. The visual modules add render hooks, frame-time variance, and log noise, and `array_list`/`interface` add UI work on the same frame budget. None of them help answer a position or latency question.

## The four-variable confound

### Fly, mode `Hover`

`Fly::onEnable` pins the hover plane at the enable-time Y, and `Fly::onUpdate` overwrites horizontal velocity every tick from the WASD vector at 0.5 while forcing vertical velocity to zero. The client's own position therefore changes under normal movement input, but Y is constant and Y velocity is always zero. Outgoing auth input carries a fabricated-but-moving position, and any external observer sees a player gliding at a fixed height.

### `Anchor Outgoing Pos`

`TestModule::onPacketOut` rewrites `PlayerAuthInput` to `mPos = mAnchor` and `mPosDelta = 0` only when `anchorOutgoingPos && mAnchorValid`. `mAnchorValid` becomes true only through the `Set Anchor` button or through TestModule's own Freeze/Hover modes, and both of those modes are false in this config. Unless `Set Anchor` was physically pressed during the session, this setting is inert. The JSON cannot record whether it was, because the button settings serialize as `null`.

### `Zero Outgoing Move`

Independently of the anchor branch, `onPacketOut` zeroes `mMove` when `zeroOutgoingMove` is set. This strips the input vector from every outgoing auth input while leaving the client's internal position untouched. If the anchor is also active, the packet is a zero-vector, fixed-position claim; if it is not, the packet is a zero-vector claim with a moving position.

### `Hold Latency` at 9300 ms

`onPacketIn` cancels inbound `Ping` (`NetworkStackLatency`), stores its `createTime`, and re-sends it after `Auto Release Ms`. At 9300 ms this is a per-packet 9.3 s stall that releases in a burst, not steady-state latency. Any server-side correction or kick that depends on ping ordering is shifted by that amount, and the burst makes the timestamp distribution non-uniform.

### Interactions

- Fly + Anchor: the client diverges from the server's view, but the server sees a pinned position and zero delta, so divergence grows without any server-visible movement.
- Fly + Zero Move: the local position changes while every packet reports a zero input vector.
- Anchor + Zero Move: the server sees a completely frozen player, position and input both constant.
- Hold Latency: corrections, if any, arrive 9.3 s late and in a burst, so timing cannot be attributed to the movement change.
- All four: no clean signal. A kick, a correction, or silence cannot be attributed to any one variable.

## Why this config cannot answer the real questions

- Inbound cancellation is untested. `onPacketIn` only cancels `SetActorMotion`/`MovePlayer` for the local runtime ID, and both toggles are false, so the inbound path is a pure pass-through.
- The anchor may be inert. `mAnchorValid` requires a button press that the JSON does not record; `Set Anchor` and the other buttons serialize as `null`.
- `State Interval` has a unit mismatch. The UI stores a float, but `onUpdate` does `static_cast<uint64_t>(stateInterval.value())`; 0.5 casts to 0 and is then clamped to 1 tick. The file logs roughly every tick, not every 0.5 s.
- Combat modules are enabled. `anti_bot` and `reach` add packets and target changes that are not part of the movement hypothesis.
- Incoming rows carry no local-runtime filter, and state rows do not record runtime at all, so local and remote traffic cannot be separated after the fact.
- `PacketHook::need` includes `KeepAlive` (id 0), for which `MinecraftPackets::createPacket` returns null; the hook logs and skips. This is log noise, not a crash.

## What the combination suggests

Read as a stack rather than as four settings, this config accidentally encodes the full "move locally, then hide it" sequence in one shot: Fly supplies local movement, `Zero Outgoing Move` strips the input proof, `Anchor Outgoing Pos` pins the reported position, and `Hold Latency` delays any response. That is the end state of an evasion stack, not a probe of one layer.

Phase 0 contradicts the premise the stack assumes. Across `testmodule_20261103_195216.csv` there are exactly four local `MovePlayer` packets, all `PositionMode reset=2` teleports at dimension, round, or respawn transitions (ticks 32288, 34926, 44995, 45452), and zero `CorrectPlayerMovePrediction` packets. Local `SetActorMotion` appears only at those transitions plus a Y=0.4 launch sequence. ChangeDimension spawn Y is consistently 1.77 above the following teleport target. The server therefore appears client-authoritative on position and uses `MovePlayer` only as a teleport channel; it is not correcting ordinary movement.

The correct scientific order is the reverse of what this config tests: prove raw movement is accepted first, then add hiding layers one at a time and measure when the server's behaviour changes. Within Fly, `Hover` is the safer first probe than `Position` because it pins only Y and leaves horizontal movement and input vector intact, so a horizontal correction or kick is still attributable.

## What to add to the Test Module

1. Filter incoming logging to the local runtime ID, with an explicit toggle for "all entities".
2. Write the runtime ID on every state row, plus an `is_local` flag, so post-processing can split local from remote.
3. Remove `KeepAlive` from `PacketHook::need`; there is nothing to log and the null packet only produces noise.
4. Log `MovePlayer` with `PositionMode` and a cause tag, annotating teleport versus correction in the row itself.
5. Log `mAnchorValid` and the anchor value on every anchored outgoing `PlayerAuthInput`, so an inert anchor is visible in the log instead of inferred.
6. Fix the `State Interval` unit mismatch, either by storing milliseconds as an integer or by rounding the float to ticks before clamping; document the unit in the setting name.
7. Log ping hold and release timestamps, and a per-packet held duration, so the 9.3 s stall is measurable rather than assumed.
8. Log `PlayerAuthInput` `mPos` against local state `mPos` per packet, so divergence is a recorded column.
9. Add a one-click `Solo`/baseline toggle that clears anchor, zero-move, and hold in a single action, to guarantee a known-clean starting state.

## What to test next

Each step is one variable. Run steps in order and do not advance until the previous step has a clean measurement. For every step, record: local `MovePlayer` count and `reset` value, `CorrectPlayerMovePrediction` count, local `SetActorMotion` count and payload, time to first correction or kick, and client position versus outgoing `PlayerAuthInput` position divergence.

0. Clean baseline: movement modules off, `anti_bot` and `reach` off, logging only. Confirm the Phase 0 picture reproduces.
1. `Fly` mode `Velocity` at 0.5, then 1.0, then 2.0, for 5 s each at roughly 4 blocks of travel.
2. `Fly` mode `Hover` for 15 s, then 30 s. Measure whether duration alone changes the response.
3. `Fly` mode `Position`, horizontal only, to separate position claims from velocity claims.
4. `Anchor Outgoing Pos` alone, after pressing `Set Anchor`. This is the first test that can distinguish an active anchor from an inert one.
5. `Anchor` + `Zero Outgoing Move`, no latency hold.
6. `Hold Latency` alone at 500, 2000, and 9300 ms. Measure the release burst and its effect on corrections.
7. Only then stack combinations, one addition at a time.
8. Inbound test: take a hit while hovering with `Cancel Set Motion` off, then repeat with it on. This is the only step that exercises `onPacketIn` cancellation.
9. Respawn with `Cancel Move Player` ON to prove the teleport dependency identified in Phase 0.

## Open questions

- Was `Set Anchor` actually pressed at any point in this session? If not, the anchor variable was never active.
- What independent server-side view exists, such as a second account or a replay, to confirm whether the player appeared frozen?
- What is the real ping-timeout threshold on this server? The 9300 ms hold is an assumption until that number is known.

## Files referenced

| File | Role |
|---|---|
| `%APPDATA%\BlueySenseV2\configs\test1.json` | Config under analysis, version 1 |
| `%APPDATA%\BlueySenseV2\configs\backups\test1_20261103_195619.json` | Backup of the same config |
| `testmodule_20261103_195216.csv` | Phase 0 packet capture |
| `TestModule.cpp` | Anchoring, zero-move, ping hold, state logging |
| `Fly.cpp` | Hover/Y capture, velocity, stop-on-disable |
| `PacketHook.cpp` | Hook need list, including `KeepAlive` |
| `docs\test1-config-analysis.md` | This note |
