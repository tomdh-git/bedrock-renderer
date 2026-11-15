# OffsetProvider port to 1.26.60.05: what is proven and what is open

`src/sdk/OffsetProvider.h` was proven on 1.26.51.01. Everything below marked **proven** was re-read from the 1.26.60.05 binary. Levi's 26.60 header is NOT a source: its virtual counts and member layouts are not updated (it still says getLocalPlayer 31, Actor::mLevel 0x1D0).

## Method (scripts were in the session scratchpad: valign.py, vtscan.py, leas.py)

1. Vtable starts without RTTI: the game has no RTTI for Actor/Level/ClientInstance/etc. A vtable start is the `lea reg,[rip+X]` target (constructors store it) that lies on a run of `.text` pointers in `.rdata`. This reproduced the known ClientInstance vtable (old 0xe9731b0, new 0xf2b9330) exactly.
2. Anchors: a sig'd function that sits in the vtable (`grabMouse` -> ClientInstance, `MultiPlayerLevel::_subTick` -> Level, `getDestroyRate`'s caller -> GameMode, `Options::getHideHand` -> Options, a `mov rax,[rcx+0x218]` tiny getter at idx 76 -> MinecraftGame). The Actor family (77 vtables share the base slots) was found by clustering on slot 13.
3. Slots were aligned old -> new by instruction-mnemonic fingerprints (difflib), then displacement changes of aligned tiny getters give the member shifts.

## Vtable indices

| Entry | 1.26.51 | 1.26.60 |
|---|---|---|
| ClientInstance getLocalPlayer / getRegion / getOptions / getUser / getPacketSender / getInputHandler / getScreenName / setDisableInput / grabMouse / releaseMouse | 31 / 30 / 174 / 179 / 293 / 303 / 246 / 309 / 310 / 311 | 30 / 29 / 172 / 177 / 290 / 299 / 243 / 305 / 306 / 307 (setDisableInput inferred from the -4 shift) |
| Actor vBodyRot, vHeadRot, vBodyYaw, vBaseTick, vShadowRadius, vBrightness, swing | 13, 14, 15, 25, 34, 37, 109 | unchanged |
| GameMode start/destroy/continue/stop/attack | 1, 2, 3, 4, 15 | unchanged |
| Level getPlayerList / getRuntimeActorList | 319 / 325 | unchanged |
| Options getOption / loadFile | 1 / 18 | unchanged |
| BlockSource getBlock, Container getItem | 2, 7 | unchanged (neighbours align; container histogram 0x38 30 -> 32) |

## Members

| Entry | 1.26.51 | 1.26.60 | Proof |
|---|---|---|---|
| Actor mLevel / mBuiltInComponents / mSupplies | 0x1D8 / 0x218 / 0x5B8 | 0x200 / 0x240 / 0x5E0 | aligned Actor-family getters, uniform +0x28 |
| Actor mGameMode | 0xAA0 | 0xAC8 | the +0x28 shift, plus the "vcall after load" histogram of the two loads matches (0x80 x9, 0x20 x5) while 0xAA0 in the new exe does not |
| PlayerInventory mContainer, mSelectedSlot | 0xB8, 0x10 | unchanged | aligned getter chain |
| Block mLegacy, BlockLegacy mBlockId | 0x68, 0x17E | unchanged | load-pattern counts |
| ClientInstance mGuiData / mLevelRenderer | 0x650 / 0x1C0 | 0x668 / 0x1E0 | getGuiData body, aligned getter |
| ClientInstance mViewMatrix | 0x420 | 0x438 | **inferred** (the whole 0x2c8..0x6d8 zone is +0x18); not proven by code |
| LevelRenderer mRendererPlayer | 0x468 | 0x480 | camera-distance function, old 0x47dcda0 / new 0x5340b70 |
| LevelRendererPlayer mCameraPos / projection (FovX, FovY) | 0x9CC / 0xF58 (0xF6C) | 0x9C4 / 0xF50 (0xF64) | same functions; projection from the 2452-byte function 0x46cfe60 / 0x53b3290 (31 loads shift -8) |
| MinecraftGame mClientMap / mPackManager / mMouseGrabbed | 0x970 / 0x218 / 0x1E8 | 0x9D0 / 0x228 / 0x1F8 | three aligned getters for the map, `movzx eax,[rcx+0x1f8]` for the grab flag |
| std::map node: ClientInstance pointer | node+0x30 | node+0x38 | the game's own walker at 0x8bce40 |
| Social::UserImpl gamertag string / getter | 0x358 / sig 0x84f50 | 0x520 / sig 0xfb3070 | getter at slot 43 of the matching vtable (was slot 44), sibling spacing 0x28 both |
| bgfx RendererContextD3D12 mCommandQueue | 0xCC9260 | 0xCC9268 | byte diff of the sig site |
| Option mValue (0x18), Options value reads | unchanged | unchanged | getHideHand body identical |

## Re-proven in the second pass (all gates removed, everything is on again)

- **JSON UI tree**: ScreenView mController 0x40 / mVisualTree 0x50 are used by the same instructions in `ScreenView::setupAndRender` (old 0x4838f90 / new 0x4cb3260) at the aligned places; the controller vtable calls (+0x10, +0x18 = handleEvent slot 3) are identical. Tree flags +0x4c / +0xd3 / +0x10 / +0x58 / +0x60 / +0xb0..0xc0 and control members +0x18 / +0x98 / +0xa0 (children, 16-byte stride) are identical in the aligned callees (similarity 0.98-1.00). Only ScreenView members above 0x370 moved (+0x20). mRoot (+8), mName (0x20), mSize, mAlpha are covered by the same unchanged layout but have no instruction of their own that proves them; StartScreen checks the root's name against the start screen before it touches anything.
- **Input mapping**: the CI getInputHandler slot (303 -> 299) returns an object whose +0x48 is read in the same aligned code of both builds. The factory's layout member could not be proven statically, so `ClientInstance::getKeyboardSettings` finds it at runtime once (a pointer in factory+0x100..0x140 whose target holds a vector of 0x40-byte binds named `key.*`) and logs `[input] the keyboard layout is at factory+0x...`.
- **Resource pack manager** (members re-read from `_composeFullStack` 0x17cc040, `composeFullStack` 0x17cc1e0 and `setStack` 0x17cabd0): level 0x130, global 0x138, treatment 0x140, base 0x148, full stack 0x58, listeners 0xF8, mInitializing 0x178, mPendingRestack 0x179, mUseGlobalPackStack 0x17A, mutex 0x180.
- **Sigs** (all 41 live, audit.py): `ResourcePackManager::composeFullStack` (the one-argument `_composeFullStack`) 0x17cc040, `setStack` 0x17cabd0, `ResourcePacksScreenController::setGlobalStack` 0x51ef8f0 (gate `jne` now at +0xB5), `applyOnExit` 0x51efc20, `bindingA` 0x50d00b0, `bindingB` 0x5154780, `canMove` 0x515b660, `canMoveUp` 0x515baa0, `canMoveDown` 0x515bc70, `bindingC` 0x515f000 (all matched to the old functions by instruction similarity 0.80-0.99). `bindingD` is dropped: its counterpart no longer calls isPreGame. The pack screen's edit-path callers were re-found as applyOnExit-relative ranges (0x522CFF0, 0x52357C0, 0x5237CF0); the fourth (old 0x4EED190, a 179-byte forwarder) has no counterpart.
- **PackColor**: `loadResource` (wrapper 0x17c4600 -> inner 0x17c2540) keeps the same call convention; the old hang was most likely the game-heap corruption fixed with the game-allocator strings, so loading is back on (a 4 s watchdog still guards it).
- **FrameBuilder insert** slot 0x350 -> 0x370 (sky / weather filters).
- Config: no change needed. `ConfigManager::applyConfig` already applies the defaults first and the file on top (missing settings keep their defaults, unknown ones are ignored), a file from a newer version is read but never written, and every write keeps the old content in `configsackups`.

## Still unproven in game

Checked statically against the 1.26.60.05 exe (CI vtable at RVA 0xf2b9330, anchored on the live grabMouse/releaseMouse slots 306/307): getLocalPlayer 30 / getOptions 172 (a getter of [CI+0xE00]) / mLevelRenderer 0x1E0 (slot 185 `mov rax,[rcx+0x1e0]`) / mGuiData 0x668 (slot 215 getGuiData body) / setDisableInput 305 (takes a bool in edx, stores it with `mov byte [rax+0xBE],bl`) are all code-proven. mViewMatrix 0x438 has no trivial getter to prove it by, but the in-game layout check in ViewmodelSway (transposed reading err 1.48 against the camera origin, the other reading 22.3) shows the block is a real view matrix. All 42 sigs live and unique (tools/sigs/audit.py; BobHurt uses its second pattern). Struct-based members (components, AABBShapeComponent, etc. from the generated headers) were not re-checked. Nothing here has been run in game yet beyond inject + world join.
