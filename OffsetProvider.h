#pragma once

// Every game offset and vtable index, in one place. SDK classes read these instead of carrying magic numbers; the
// comment says how each one was proven. Build 1.26.51 gdk 6764.
//   vtable indices : "CI vtable" etc.
//   members        : byte offsets from the object start
// 1.26.62.01 (2026-11-04): full re-proof pass - zero value changes (pure relocation patch; see docs/offsets-1.26.62-todo.md)
#define DEFINE_FIELD(name, value) static constexpr auto name = value;

struct OffsetProvider {
    DEFINE_FIELD(Actor_mSupplies, 0x5E0); // Actor -> PlayerInventory*
    DEFINE_FIELD(PlayerInventory_mSelectedSlot, 0x10);
    DEFINE_FIELD(PlayerInventory_mContainer, 0xB8); // PlayerInventory -> Container*
    DEFINE_FIELD(Container_getItem, 7); // Container vtable: (this, int slot) -> ItemStack const&
    DEFINE_FIELD(ItemStack_mItem, 0x8);   // ItemStackBase: vptr, then WeakPtr<Item> (LeviLamina 26.60 layout: mItem 0x8, mUserData 0x10, mBlock 0x18, mAuxValue 0x20, mCount 0x22)
    DEFINE_FIELD(ItemStack_mBlock, 0x18); // Block const*
    DEFINE_FIELD(ItemStack_mCount, 0x22); // uint8
    DEFINE_FIELD(Item_mName, 0xD8);       // Item -> mRawNameId (HashedString at 0xD0: hash, then the std::string); LeviLamina 26.60 layout summed field by field
    DEFINE_FIELD(BlockSource_getBlock, 2); // BlockSource vtable: (this, BlockPos) -> Block const&
    DEFINE_FIELD(Block_mLegacy, 0x68); // Block -> BlockLegacy*
    DEFINE_FIELD(BlockLegacy_mBlockId, 0x17E); // BlockLegacy: uint16 id
    DEFINE_FIELD(Actor_vBodyRot, 13);      // Actor vtable: getInterpolatedBodyRot(float)  (byte offset 0x68)
    DEFINE_FIELD(Actor_vHeadRot, 14);      // getInterpolatedHeadRot(float)  (0x70)
    DEFINE_FIELD(Actor_vBodyYaw, 15);      // getInterpolatedBodyYaw(float)  (0x78)
    DEFINE_FIELD(Actor_vBaseTick, 25);     // baseTick()
    DEFINE_FIELD(Actor_vShadowRadius, 34); // getShadowRadius()  (0x110)
    DEFINE_FIELD(Actor_vBrightness, 37);   // getBrightness(float, IConstBlockSource const&): the light level at the entity
    DEFINE_FIELD(Actor_mGameMode, 0xAC8); // Actor -> GameMode*
    DEFINE_FIELD(Actor_swing, 109); // Actor vtable: swing(source, hand)
    DEFINE_FIELD(GameMode_startDestroyBlock, 1); // GameMode vtable
    DEFINE_FIELD(GameMode_destroyBlock, 2);
    DEFINE_FIELD(GameMode_continueDestroyBlock, 3);
    DEFINE_FIELD(GameMode_stopDestroyBlock, 4);
    DEFINE_FIELD(GameMode_attack, 15);
    DEFINE_FIELD(GameMode_buildBlock, 6); // GameMode vtable: (this, BlockPos const&, uchar face, uchar hand, bool); startBuildBlock (slot 5) calls it through [vtable+0x30] (1.26.62 @ 0x376b1f0)
    DEFINE_FIELD(Level_getRuntimeActorList, 325); // Level vtable: (this, std::vector<Actor*>* out)
    DEFINE_FIELD(Level_getPlayerList, 319); // Level vtable: the player list (unordered_map<UUID, PlayerListEntry>*)
    DEFINE_FIELD(Actor_mLevel, 0x200); // Actor -> Level*
    DEFINE_FIELD(Level_getHitResult, 335); // Level vtable: returns the HitResult* the crosshair ray fills (tiny getter mov rax,[rcx+0x1F0]; slot 336 is the liquid HitResult, 0x88 further)
    // 1.26.60.05 PORT (all values below re-proven against the 1.26.60.05 binary with tools in the session scratchpad; see docs/offsets-1.26.60-todo.md):
    // Actor/Player members moved +0x28 (aligned vtable getters), ClientInstance members +0x20 / +0x18, MinecraftGame +0x10 / +0x60, LevelRendererPlayer camera + projection -8.
    DEFINE_FIELD(ClientInstance_getLocalPlayer, 30); // CI vtable (1.26.51: 31)
    DEFINE_FIELD(ClientInstance_mMinecraftSim, 0x1C8); // CI -> MinecraftSim*: CODE-PROVEN on 1.26.62.01: CI vtable slot 78 is mov rax,[rcx+0x1C8]; ret and the IClientInstance forwarders (slots 80..108) call through it (Solstice 1.26.51: 0x1B0)
    DEFINE_FIELD(MinecraftSim_mGameSim, 0xE8);   // MinecraftSim -> the game clock: 0xE0 in Solstice 1.26.51, +8 like the render clock below; not read directly, setTicksPerSecond checks the value is a tick rate before writing
    DEFINE_FIELD(MinecraftSim_mRenderSim, 0xF0); // MinecraftSim -> the render clock: CODE-PROVEN, the renderer function that read [sim+0xE8] on 1.26.51 (sig 48 8B 80 ? ? ? ? F3 0F 10 50) reads [sim+0xF0] on 1.26.62.01
    DEFINE_FIELD(ClientInstance_getRegion, 29); // IClientInstance::getRegion vtable idx (next to getLocalPlayer: same weak-ref prologue) (1.26.51: 30)
    DEFINE_FIELD(ClientInstance_getOptions, 172); // CI vtable
    DEFINE_FIELD(ClientInstance_getPacketSender, 290); // CI vtable: mov rax,[rcx+1D0h] in the binary (declared 280: drifted by 13 here)
    DEFINE_FIELD(ClientInstance_getUser, 177); // (1.26.51: 179) CI vtable: returns &CI[+0xE00] (a pointer wrapper whose first field is the Social::User*), 0 when there is no user (CODE-PROVEN: sub 0x5dc2910)
    DEFINE_FIELD(User_mGamertag, 0x520); // Social::UserImpl std::string; CODE-PROVEN: the vtable-44 getter (sub 0x84f50) copies it
    DEFINE_FIELD(ClientInstance_getScreenName, 243); // CI vtable, (this, string& out)
    DEFINE_FIELD(ClientInstance_grabMouse, 306); // (1.26.51: 310) CI vtable; impl == sig "ClientInstance::grabMouse" (checked at runtime)
    DEFINE_FIELD(ClientInstance_setDisableInput, 305); // CI vtable: setDisableInput(bool) (same prologue shape as grab/release next to it)
    DEFINE_FIELD(ClientInstance_releaseMouse, 307); // (1.26.51: 311) CI vtable; impl == sig "ClientInstance::releaseMouse" (checked at runtime)
    DEFINE_FIELD(ClientInstance_mGuiData, 0x668); // CODE-PROVEN: CI-vtable[217] getGuiData impl is mov rdi,[rcx+0x650]
    DEFINE_FIELD(ClientInstance_mLevelRenderer, 0x1E0); // CODE-PROVEN: the getLevelRenderer chain fn reads [rcx+0x1E0] first (see LevelRenderer_mRendererPlayer below); CI vtable slot 185 tiny getter is mov rax,[rcx+0x1E0]
    DEFINE_FIELD(ClientInstance_mViewMatrix, 0x438); // world view mat4 (ClientInstance::getViewMatrix)
    DEFINE_FIELD(LevelRendererPlayer_mCameraPos, 0x9C4);
    DEFINE_FIELD(LevelRendererPlayer_mFovX, 0xF50);      // the projection scale in x
    DEFINE_FIELD(LevelRendererPlayer_mFovY, 0xF64);      // the projection scale in y
    DEFINE_FIELD(LevelRendererPlayer_mProjection, 0xF50); // the whole projection mat4: mFovX / mFovY are its [0] and [5] (0x14 apart), [10] [11] [14] hold the depth mapping
    DEFINE_FIELD(LevelRenderer_mRendererPlayer, 0x480); // CODE-PROVEN: the chain fn does mov rax,[rcx+0x1E0]; mov rax,[rax+0x480]; mov rax,[rax+0xA70] (1.26.60 @ 0x65b13d0, 1.26.62 @ 0x65b1fd0)
    DEFINE_FIELD(Actor_mEntityContext, 0x8); // first member after the vptr
    DEFINE_FIELD(Actor_mBuiltInComponents, 0x240); // CODE-PROVEN; mStateVectorComponent is the first 8B
    DEFINE_FIELD(Actor_mActorDefinitionPtr, 0x2F0); // LeviLamina 26.60 Actor layout (same layout as mBuiltInComponents 0x240 above): { ActorDefinitionGroup*, ActorDefinition* }; not yet confirmed live
    DEFINE_FIELD(ActorDefinition_mIdentifier, 0x408); // ActorDefinition: mDescription (1024 bytes) then IdentifierDescription { vptr, std::string mId }; the string is at +0x408; not yet confirmed live
    DEFINE_FIELD(GameCore_mPlatform, 0x8); // GameCore -> Platform
    DEFINE_FIELD(Platform_mGameHolder, 0x118); // Platform -> holder
    DEFINE_FIELD(GameHolder_mMinecraftGame, 0x48); // holder -> MinecraftGame
    DEFINE_FIELD(MinecraftGame_mClientMap, 0x9d0); // 1.26.60: was 0x970 (same-size map walkers 0x81e230/0x81e2e0 -> 0x8bce40/0x8bcef0); std::map<uint8_t, ClientInterface>; find(0) -> shared_ptr<ClientInstance>
    DEFINE_FIELD(MinecraftGame_mPackManager, 0x228); // CODE-PROVEN: MinecraftGame vtable[76] getResourcePackManager is mov rax,[rcx+0x228] (vtable @ 0xF091B70 -> 0xF092B50, getter 0x8bc9e0 -> 0x8bc9c0); read it off the real MinecraftGame (the _update argument)
    // ResourcePackManager: proven by the _composeFullStack/setStack code of each build (1.26.60: listeners 0xF8, mInitializing 0x178, mutex 0x180).
    DEFINE_FIELD(ResourcePackManager_mLevelStack, 0x130); // 1.26.60: members re-read from _composeFullStack (0x17cc040) and composeFullStack (0x17cc1e0); the SIG "composeFullStack" is the one-argument _composeFullStack (1.26.51: 0x98)
    DEFINE_FIELD(ResourcePackManager_mGlobalStack, 0x138); // (1.26.51: 0xA0)
    DEFINE_FIELD(ResourcePackManager_mFullStack, 0x58); // (1.26.51: 0xB8)
    DEFINE_FIELD(ResourcePackManager_mPendingRestack, 0x179); // setStack does or [mgr+0xE9],changed; _update restacks when it is 1
    DEFINE_FIELD(ResourcePackManager_mUseGlobalPackStack, 0x17A); // composeFullStack reads it; cleared in a world, set again outside
    DEFINE_FIELD(GeneralSettingsScreenController_mReloadTexturePacksOnExit, 0xD61); // CODE-PROVEN: the exit handler (applyOnExit) tests cmp byte [this+0xD61],1 before applying the pack stack
    DEFINE_FIELD(MinecraftGame_mMouseGrabbed, 0x1F8); // reads true while the game owns the cursor (confirmed live in-world; 0x1E0 was a dead-pattern literal)
    DEFINE_FIELD(bgfx_RendererContextD3D12_mCommandQueue, 0xCC9268); // mov rdx,[rcx+0xCC9268] in BgfxContext::liveContext's sig site (1.26.51: 0xCC9260, @RVA 0xDFA097C); 1.26.60 shift +8 found by the byte diff, untested in game
    // The game's own key bindings (ported from Solstice-Updated, build 1.26.51): ClientInstance -> input handler ->
    // mapping factory -> KeyboardRemappingLayout. Read-only; the keys themselves still reach the game.
    DEFINE_FIELD(ClientInstance_getInputHandler, 299);            // CI vtable: getInputHandler()
    DEFINE_FIELD(ClientInputHandler_mMappingFactory, 0x48);       // ClientInputHandler -> ClientInputMappingFactory*
    DEFINE_FIELD(ClientInputMappingFactory_mKeyboardRemappingLayout, 0x110); // -> KeyboardRemappingLayout*; 1.26.51 value, not read on 1.26.60 (ClientInstance::getKeyboardSettings finds the member at runtime)
    // JSON UI (LeviLamina 26.51 layouts, checked against the real game): ScreenView -> VisualTree -> UIControl tree. PROVEN 1.26.60: ScreenView::setupAndRender (old 0x4838f90 / new 0x4cb3260) uses [this+0x40/0x50] and the controller vtable calls (+0x10, +0x18) at the aligned places; tree flags +0x4c/+0xd3/+0x10/+0x58/+0x60/+0xb0..0xc0 and control +0x18/+0x98/+0xa0 are identical in the aligned callees (0.98-1.00 similarity). Only the ScreenView members above 0x370 moved (+0x20).
    DEFINE_FIELD(ScreenView_mController, 0x40);   // ScreenView -> ScreenController*
    DEFINE_FIELD(ScreenView_mVisualTree, 0x50);   // ScreenView -> VisualTree*
    DEFINE_FIELD(VisualTree_mRoot, 0x8);          // VisualTree -> root UIControl*
    DEFINE_FIELD(VisualTree_mDirty, 0x48);        // VisualTree: dirty flags (set to 0xF, the layout is measured again)
    DEFINE_FIELD(UIControl_mPos, 0x10);           // x, y
    DEFINE_FIELD(UIControl_mBits, 0x18);          // bit 2..3: visibility, bit 4: in the tree
    DEFINE_FIELD(UIControl_mName, 0x20);          // std::string
    DEFINE_FIELD(UIControl_mSize, 0x48);          // width, height
    DEFINE_FIELD(UIControl_mAlpha, 0x60);
    DEFINE_FIELD(UIControl_mChildren, 0x98);      // std::vector<shared_ptr<UIControl>> (begin, end)
    DEFINE_FIELD(ScreenController_vHandleEvent, 3); // ScreenController vtable: int handleEvent(ScreenEvent&)
    DEFINE_FIELD(Option_mValue, 0x18); // IntOption dword; HideHand/Gamma
    DEFINE_FIELD(Options_getOption, 1); // IOptionsReader::get(OptionID) vtable idx
    DEFINE_FIELD(Options_loadFile, 18); // registry file load vtable idx

};

#undef DEFINE_FIELD
