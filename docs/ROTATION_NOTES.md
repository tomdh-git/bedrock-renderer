# Client-side vs server-side rotation: notes and test plan

Working notes (1.26.62.01). Tool: `tools/rdis` (`rdis <exe> -c "fn 0x...; xr 0x..."`; `comp <FullTypeName>` finds users of an ECS component, its hash is the FNV-1a 32 of the entt type name).

## Code in the tree

| Part | File | Role |
|---|---|---|
| `ServerRotation` | `core/game/ServerRotation.*` | what the server sees: modules call `set()` each tick; `PacketHook` writes it into the outgoing PlayerAuthInput after every module's PacketOut handler |
| `LocalRotation` (kg's method) | `core/game/LocalRotation.*` | the local model: around the original `ActorRenderDispatcher::render` of the local player it swaps pitch, head, body, actor yaw (+ prev) components and the draw's `rot` argument, then restores them |
| vtable hooks | `ActorHook.*` | `getInterpolatedBodyRot/HeadRot/BodyYaw` of the local player answer `LocalRotation::visualYaw` |
| render hook | `ActorRenderDispatcherHook.cpp` | `beginDraw` / `endDraw` around the original |
| trigger | Test Module, "Rotation test" | `Server Rotation` + `Yaw Offset` (+ `Show On Model`); Disabler 2 Jump Rotate (not registered) |

## How to test kg's method (user)

Third person, Test Module on, `Server Rotation` on, `Yaw Offset` 90. Mouse-look around.

1. `Show On Model` OFF: does the model follow the real rotation, or turn 90 degrees away?
   - follows real: packet writes do not reach the client model.
   - turns away: something carries the sent rotation back to the client (record whether head, body, or both, and whether the camera or movement direction changes).
2. `Show On Model` ON: does the model turn to real + 90? Check head, body and pitch separately. Janky signs: flicker, snap back, body not following the head, a one-frame lag, the model showing the real rotation in some frames.
3. First person: is the hand/view affected? (it should not be.)
4. Walk with it on: does movement direction stay on the real rotation? (the camera and aim must stay real.)

Results (fill in):

| Test | Result |
|---|---|
| 1 model, Show off | |
| 2 head / body / pitch, Show on | |
| 3 first person | |
| 4 movement | |

## Findings from the disassembly

- `ActorRenderDispatcher::render` 3-arg wrapper (`sub_594fbe0`) builds the `rot` argument by interpolating the ActorRotationComponent (cur at +0/+4 = pitch, yaw; prev at +8/+0xC) of the actor with the partial tick. The component pointer is cached in the actor at `+0x250`.
- The 6-arg render (`sub_594c5c0`, hooked) copies pos and `rot` into its render params ([rbp-0x20], [rbp-0x14]) and reads `[entity+0x250]` again itself. So the model's rotation inputs are the ActorRotationComponent (real rotation, the camera's), not anything from the packet. That is why `LocalRotation` swaps the components AND the `rot` argument.
- `ClientInputUpdateSystemInternal` (Levi header): rotation components are Read only.
- Mouse look is `CameraDirectLookSystemUtil::_handleLookInput` (`sub_6eec630`, called from the system tick `sub_9b5090`): it writes `MinecraftCamera::CameraDirectLookComponent` (pitch +4, yaw +8, limits +0xC/+0x10), not the ActorRotationComponent. So the actor rotation is derived from the camera somewhere (not found yet).
- Solstice: `Interface` swapped pitch/head/body around the render (that part was commented out); Aura wrote the packet only, plus its Strafe mode wrote the real ActorRotationComponent at render time (which also moves the player: the "orbit" effect). Packet-only writes need a movefix because the client keeps moving on the real rotation.
- kg's tree: server rotation = direct packet writes; local rotation = GameRotation swap + a write to the real MobBodyRotationComponent (dropped here) + vtable hooks; no evidence he saw it work.
- `MinecraftSim` offsets: CI+0x1C8 proven, render sim +0xF0 proven (same function as +0xE8 on 1.26.51), game sim +0xE8 inferred.

## Open questions

1. Who writes ActorRotationComponent on the client (camera sync, server corrections, replay)? Does anything copy a SENT rotation back?
2. Where is the PlayerAuthInput built (fields at packet +0x30 mRot, +0x44 head, +0x5C analog, +0x64 move, +0x80 raw, +0x88 input bits)? Searches by field offset hit many constructors; try the send path (`LoopbackPacketSender` vtable slot 4 callers) instead.
3. Does the local model's pose come only from the render params, or also from the animation (ActorAnimationControllerPlayer applyToPose, Solstice sig) reading the head/body components?
