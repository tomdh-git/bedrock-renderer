#pragma once

// Every game offset and vtable index, in one place. SDK classes read these instead of carrying magic numbers; the
// comment says how each one was proven. Build 1.26.51 gdk 6764.
//   vtable indices : "CI vtable" etc.
//   members        : byte offsets from the object start
// 1.26.62.01 (2026-11-04): full re-proof pass - zero value changes (pure relocation patch; see docs/offsets-1.26.62-todo.md)
#define DEFINE_FIELD(name, value) static constexpr auto name = value;

struct OffsetProvider {
    DEFINE_FIELD(ClientInstance_getLocalPlayer, 30); // CI vtable (1.26.51: 31)
    DEFINE_FIELD(ClientInstance_mMinecraftSim, 0x1C8); // CI -> MinecraftSim*: CODE-PROVEN on 1.26.62.01: CI vtable slot 78 is mov rax,[rcx+0x1C8]; ret and the IClientInstance forwarders (slots 80..108) call through it (Solstice 1.26.51: 0x1B0)
    DEFINE_FIELD(MinecraftSim_mGameSim, 0xE8);   // MinecraftSim -> the game clock: 0xE0 in Solstice 1.26.51, +8 like the render clock below; not read directly, setTicksPerSecond checks the value is a tick rate before writing
    DEFINE_FIELD(MinecraftSim_mRenderSim, 0xF0); // MinecraftSim -> the render clock: CODE-PROVEN, the renderer function that read [sim+0xE8] on 1.26.51 (sig 48 8B 80 ? ? ? ? F3 0F 10 50) reads [sim+0xF0] on 1.26.62.01
    DEFINE_FIELD(ClientInstance_getRegion, 29); // IClientInstance::getRegion vtable idx (next to getLocalPlayer: same weak-ref prologue) (1.26.51: 30)
    DEFINE_FIELD(ClientInstance_getOptions, 172); // CI vtable
    DEFINE_FIELD(ClientInstance_getPacketSender, 290); // CI vtable: mov rax,[rcx+1D0h] in the binary (declared 280: drifted by 13 here)
    DEFINE_FIELD(ClientInstance_getUser, 177); // (1.26.51: 179) CI vtable: returns &CI[+0xE00] (a pointer wrapper whose first field is the Social::User*), 0 when there is no user (CODE-PROVEN: sub 0x5dc2910)
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
    DEFINE_FIELD(MinecraftGame_mClientMap, 0x9d0); // 1.26.60: was 0x970 (same-size map walkers 0x81e230/0x81e2e0 -> 0x8bce40/0x8bcef0); std::map<uint8_t, ClientInterface>; find(0) -> shared_ptr<ClientInstance>
    DEFINE_FIELD(MinecraftGame_mMouseGrabbed, 0x1F8); // reads true while the game owns the cursor (confirmed live in-world; 0x1E0 was a dead-pattern literal)
    DEFINE_FIELD(bgfx_RendererContextD3D12_mCommandQueue, 0xCC9268); // mov rdx,[rcx+0xCC9268] in BgfxContext::liveContext's sig site (1.26.51: 0xCC9260, @RVA 0xDFA097C); 1.26.60 shift +8 found by the byte diff, untested in game
    DEFINE_FIELD(ClientInstance_getInputHandler, 299);            // CI vtable: getInputHandler()
    DEFINE_FIELD(ClientInputHandler_mMappingFactory, 0x48);       // ClientInputHandler -> ClientInputMappingFactory*
};

#undef DEFINE_FIELD
