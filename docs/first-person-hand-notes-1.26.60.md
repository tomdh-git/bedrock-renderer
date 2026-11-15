# First-person hand and held-item rendering (1.26.60.05)

RVAs are for Minecraft.Windows.exe 1.26.60.05. Everything here is from static disassembly plus the runtime observations noted. Not all of it is verified; each item says how sure it is.

## Call chain of the first-person hand (verified by disassembly and logs)

- Caller (`0x4e0e...`): `BobHurt` (0x53a0fb0, hurt shake only) -> `0x4e0f610` -> `ItemInHandRenderer::renderFirstPerson` (0x532b230) -> pop the matrix stack -> `renderHands` (0x530c390, exactly one caller, args: this, ctx, ?, actor, float and ptr on the stack).
- `renderFirstPerson` draws held items through `ItemInHandRenderer::renderItem` (0x531a210; this, ctx, X, object, flags on the stack). With a bare hand it makes **0 `renderItem` calls** (measured: "0 renderItem calls, mode 0x21" every frame while the hand was bare).
- `renderHands` draws the arm through `drawArm` (0x5309e40; arg1 is `ctx + 0x10`, then geometry, a {geometry, shared_ptr} pair, `this + 0x780`, and three stack args). It has three call sites in `renderHands` (0x530c67c, 0x530ca2c, 0x530d039), picked by the arm model (0x7f0 / 0x7e0) and flags. `drawArm` also has two callers outside `renderHands` (0x530b1f3, 0x530bf58).
- Matrix stack top: `ctx[+0x28] -> [+0x18]` is the stack; ring pointer +0x48, capacity +0x50, first +0x58, count +0x60; the top element points at 16 floats (column-major; loaded flat into an XMFLOAT4X4 it is the row-vector form). For `drawArm`, `ctx = arg1 - 0x10`.

## The item-size finding (0x531b120) - keep this, it is a lead for chams and item rendering

- `0x531b120` (this, ctx, r8, r9, plus stack arguments up to at least +0x38 and probably float arguments) is called hundreds of times a second: it is the world-wide held-item render, for **our own and other players' items**. Its neighbours in the class: 0x531a210 `renderItem`, 0x531eb50 (builds the render object from the item stack and a hash), 0x5316c40 / 0x531ef30 / 0x531f010 (matrix setup), 0x5324250 and 0x53249f0 (other hand paths, not reached while the bare arm is drawn).
- A temporary pass-through detour on it declared as 6 pointer arguments made **every held item, ours and other players', render hugely oversized** (screenshot in the session, items as large as blocks). The function reads more than 6 arguments (stack arguments and/or floats), so the detour handed it wrong values, and the visible effect is the item's size. Conclusion (not verified which argument): one of its arguments, probably a float on the stack, is the item's render scale. Changing it from a correct detour should resize items in hand globally, including other players'.
- Uses to follow up: (1) chams on held items: this is the one place that sees every held item of every player, with the matrix on the stack at that moment (`stack top translation` logged while probing: own items near [0.8, -2.5, 0.4] with scale ~0.15, other players' far away, e.g. [-41, 3.7, -52]); (2) native replacement of a held item's mesh or size; (3) general item-in-hand rendering control. To detour it correctly, recover its exact signature from the disassembly first (`python rdisasm.py 0x531b120 ...` in the scratch tools) - do not forward it with a guessed argument list again.

## Geekbar: what the device follows

- The device is carried by the arm: top of the matrix stack at the `drawArm` call made inside `renderHands` (hooks `renderHands` and `drawArm`, `GeekbarHandHook.cpp`). Rest is measured once (when the hand is out and idle) and kept; the device is not drawn until then (no fallback).
- `renderItem` is not the arm's path (see above); using it for the device only gave a matrix at the very start of a take-out, while the real item was still in hand.
- Dead end: the entry matrix of `renderFirstPerson` (BobHurt's output) misses the motion the game applies inside, and is not the arm's final matrix.

## Live findings with Cheat Engine (bare hand, device out; 1.26.60.05)

Method: the CE MCP bridge (named pipe `\.\pipe\CE_MCP_Bridge_v99`, `open_process` first after a CE restart) with non-breaking hardware execute breakpoints on call sites, 4 at a time, about a second each, counting hits. Hit logs are capped at 100.

- `renderFirstPerson` arg 2 is a pointer to a local struct on the stack, not the render context; the struct holds the context pointers (the stack-top reader on it worked). `renderHands` arg 2 is a real context (`[ctx+0x18]` = S, whose stack object at S+0x40 has the ring at +0x48; S itself has a second, shallower stack with the ring at +0x08).
- Bare hand: `renderItem` is not called from `renderFirstPerson` (it is called ~50 times a second from other callers, the other players), `drawArm` 0x5309e40, 0x5324250 and 0x53249f0 are never called, and in `renderHands` the flow reaches `0xb9d8f0` at 0x530ca71 and then jumps to the epilogue (0x530ca79 `jne 0x530d03e`): `renderHands` draws nothing in this state.
- In `renderFirstPerson` the call sites that run are the preamble up to 0x532c447, the indirect call at 0x532c5b6 and the matrix push at 0x532ea8b, then it returns: nothing is drawn from it either.
- No description is inserted inside either function (tag counts from the FrameFilter insert hook, any thread).
- So the visible bare arm is not drawn by the item-in-hand renderer at all. It is most likely the local player's own actor model, drawn through the actor render path in first person (its matrix is the view bob matrix `BobHurt` works on, plus the arm bone's animation, swing included). Next step: find that draw (ActorRenderDispatcher for the local player, the transform block of the bgfx submit of its mesh parts; see bluey-chams-selection-re notes for the pass/submit RVAs, which are from an older build and must be re-derived).
- Stack-slot leftovers: the ring slots above the current top keep last frame's matrices; slot 4 of the 0x40 stack held a scale-0.0375 item matrix (translation about -0.76 -0.55 -0.51) that varied smoothly with bob.

## The arm function (static, then confirmed by hit counts)

- The view model render (the caller of BobHurt, one function around 0x4e0e100) does, in order: BobHurt, the item hand (0x4e0f610 -> renderFirstPerson), pops the matrix stack, `renderHands` (0x530c390), then pushes a matrix, fills the top with a transform computed by 0xab49b0 from the previous top, asks 0xa9f0b0 (a component of the local player) for the arm object and, when there is one, calls **0x530a7a0** (this, ctx, actor, float in xmm3, arm component on the stack). Single caller. 0x530a7a0 is a big animation state machine on `[ctx+0xb0]` (swing, equip flags at +0x168..+0x2a0) and is called every frame the hand is shown (19-20 hits in 2 s with the device out).
- Its two `drawArm` (0x5309e40) call sites (0x530b1f3, 0x530bf58) are not reached with a bare hand, so the arm is drawn by indirect calls inside it (not traced) or later from the state it sets up; the matrix on the stack at its entry is the arm's base matrix with bob, hurt, our pose and rise in it. Not yet known: whether the swing is in that matrix or only in the animation state / bones.
- Sig for 0x530a7a0: `ItemInHandRenderer::renderArm` in Sigs.json.
- Measured live (log, 60 s of walking and swinging): the matrix at its entry never changes (translation [0 0 -0.05], scale 0.7586). Dead end for placing the device.

## The arm's real pose: skeleton animation (static, then partly checked)

- The first-person bob and swing are not matrix work on the view model. OpenSunstead's `ItemInHandRenderer::swingRotate` (a rotate call inside our `renderFirstPerson`) works on a matrix that is discarded when that function returns; the visible bare arm is skeletal. The pose is written by `ActorAnimationControllerPlayer::applyToPose(ApplyAnimationContext const&, RenderParams&, unordered_map<SkeletalHierarchyIndex, vector<BoneOrientation>>&, float)` into the bone map.
- `BoneOrientation` is 0xe8 bytes (LeviLamina 26.60 headers): +0x00 parent bone, +0x04 parent hierarchy, +0x08 HashedString name (hash first), +0x38 mMatrix (64 bytes, the bone's final matrix), +0x78 mTransform (pos, rot degrees, scale), +0x9c mDefaultTransform, +0xc0 unique_ptr, +0xc8 expression, +0xd8 pivot. `rightarm` hash `0x1156c640da03acc9`, `leftarm` `0x85b2751de4a68588` (what renderFirstPerson's bone loop at 0x532ba2d compares; that loop walks the model's template bones, which stay identity - not the pose).
- 1.26.60.05 `applyToPose` = RVA 0x6179500 (found by similarity against the 1.26.51 function `0x1e6d180` that the old Solstice sig matches in 1.26.44-1.26.51; 0.87, next best 0.54). Its fields: this+0x60 current state index, +0x68 next, +0x78 state players, args rdx = apply context, r8 = RenderParams (mActor at +0x40 by the header, to be confirmed), r9 = bone map, float on the stack. Sig: `ActorAnimationControllerPlayer::applyToPose` in Sigs.json, hooked in GeekbarHandHook.cpp (logs `[pose]` lines for the local player; the device is not placed from it yet).
- CE note: stack-pointer registers come back truncated to 32 bits from its breakpoints; only heap pointers can be followed.
