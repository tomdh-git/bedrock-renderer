#pragma once
#include "sdk/mc/deps/core/math/Matrix.h"

struct LocalPlayer;
struct LoopbackPacketSender;
struct GuiData;
struct LevelRenderer;
struct MinecraftSim;
struct Options;
class KeyboardRemappingLayout;
namespace Social { struct User; }

// IClientInstance + game/render/gui virtuals (getLocalPlayer 31, getRegion 30,
// game/render/gui virtuals (getLocalPlayer 31, getRegion 30, getOptions 174,
// getLevelRenderer 187, getGuiData 217, getScreenName 246, getMinecraftGame
// 79, grab/releaseMouse 310/311, getMouseGrabbed 147). Data members are
// blobs with no proven layout; proven offsets
// below are the ONLY direct reads (CODE-PROVEN: 0x418 view mat4 member_at,
// 0x650 guiData via vtable[217] mov, 0x1C0 renderer via vtable[187] mov).
// Rest is TODO stubs, null-guarded, no invented offsets.
struct ClientInstance {
    static ClientInstance* get(); // MinecraftGame::get()->getPrimaryClientInstance(); null before the game has booted
    LocalPlayer* getLocalPlayer();
    void* getRegion(); // vtable 30: the local player's BlockSource (null while no world is loaded)
    Matrix getViewMatrix(); // CI+0x418 world view mat4 (direct deref)
    GuiData* getGuiData(); // CI+0x650
    LevelRenderer* getLevelRenderer(); // CI+0x1C0
    Options* getOptions(); // vtable 174
    Social::User* getUser(); // vtable 179: the signed-in account; null while the game has none
    LoopbackPacketSender* getPacketSender(); // vtable 293
    MinecraftSim* getMinecraftSim(); // CI member: the game and render clocks
    void setDisableInput(bool disable); // vtable 309: the game ignores keyboard/mouse/gamepad input while true
    void grabMouse();      // vtable 310: game takes the cursor
    void releaseMouse();   // vtable 311: game gives the cursor up
    bool cursorCallsMatchSigs(); // vtable[310]/[311] are the sig-found grab/release entries
    // The camera's projection matrix inside the instance, found by its shape (a perspective matrix: zeros around the diagonal, the aspect between the
    // first two scales, -1 or 1 in [11]); null when no member looks like it. The instance has no proven layout for it on this build.
    const float* findProjectionMatrix(float aspect);
    bool isPreGame(); // the game's own answer: true in the menus, false once a level is running
    bool isInWorldHud();// a world is joined and no game screen is over the HUD
    std::string getScreenName(bool fresh = false); // vtable 246, ABI-safe read (see .cpp); read at most every 250 ms unless `fresh`
    KeyboardRemappingLayout* getKeyboardSettings(); // vtable 303 -> input handler -> mapping factory -> the layout; null on any step
    // TODO: getRegion(30)/getCamera(204)/getLevel/getBlockSource
    // /getMinecraftGame(79)/getMouseGrabbed
    // (147)/playUi(146)/requestLeaveGame(15) when a caller needs them; each
    // needs a proven offset or vtable slot first.
};
