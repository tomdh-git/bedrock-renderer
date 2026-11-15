#include "sdk/mc/client/game/ClientInstance.h"
#include "client/core/diagnostics/Log.h"
#include "sdk/mc/client/gui/ScreenNames.h"
#include "sdk/mc/client/game/MinecraftGame.h"
#include "sdk/mc/client/player/LocalPlayer.h"
#include "sdk/mc/client/gui/GuiData.h"
#include "sdk/mc/client/social/User.h"
#include "sdk/mc/client/renderer/game/LevelRenderer.h"
#include "sdk/mc/client/input/KeyboardRemappingLayout.h"
#include "sdk/OffsetProvider.h"
#include "sdk/SigManager.h"
#include "sdk/Layout.h"

ClientInstance* ClientInstance::get() {
    return MinecraftGame::get()->getPrimaryClientInstance();
}

LocalPlayer* ClientInstance::getLocalPlayer() {
    return callVirtual<LocalPlayer*>(OffsetProvider::ClientInstance_getLocalPlayer, this);
}

void* ClientInstance::getRegion() {
    return callVirtual<void*>(OffsetProvider::ClientInstance_getRegion, this);
}

Matrix ClientInstance::getViewMatrix() {
    return *reinterpret_cast<Matrix*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::ClientInstance_mViewMatrix);
}

GuiData* ClientInstance::getGuiData() {
    return *reinterpret_cast<GuiData**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::ClientInstance_mGuiData);
}

LevelRenderer* ClientInstance::getLevelRenderer() {
    return *reinterpret_cast<LevelRenderer**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::ClientInstance_mLevelRenderer);
}

LoopbackPacketSender* ClientInstance::getPacketSender() {
    return callVirtual<LoopbackPacketSender*>(OffsetProvider::ClientInstance_getPacketSender, this);
}

MinecraftSim* ClientInstance::getMinecraftSim() {
    return *reinterpret_cast<MinecraftSim**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::ClientInstance_mMinecraftSim);
}

Social::User* ClientInstance::getUser() {
    void** wrapper = callVirtual<void**>(OffsetProvider::ClientInstance_getUser, this);
    return wrapper ? static_cast<Social::User*>(*wrapper) : nullptr;
}

Options* ClientInstance::getOptions() {
    return callVirtual<Options*>(OffsetProvider::ClientInstance_getOptions, this);
}

void ClientInstance::setDisableInput(bool disable) {
    callVirtualVoid(OffsetProvider::ClientInstance_setDisableInput, this, disable);
}

void ClientInstance::grabMouse() {
    callVirtualVoid(OffsetProvider::ClientInstance_grabMouse, this);
}

void ClientInstance::releaseMouse() {
    callVirtualVoid(OffsetProvider::ClientInstance_releaseMouse, this);
}

bool ClientInstance::cursorCallsMatchSigs() {
    void** slots = *reinterpret_cast<void***>(this);
    return slots[OffsetProvider::ClientInstance_grabMouse] == reinterpret_cast<void*>(SIG("ClientInstance::grabMouse")) &&
           slots[OffsetProvider::ClientInstance_releaseMouse] == reinterpret_cast<void*>(SIG("ClientInstance::releaseMouse"));
}

// The game constructs the result string itself, in ITS Release-STL layout.
// Never hand it a std::string of ours (Debug layout differs: the OptionSync
// crash), so it writes into a raw 32-byte MSVC release layout instead.
// Throttled + cached: a name longer than 15 chars lives in a game heap block
// we cannot safely free from here, so we query a few times a second, not per
// frame (render thread only).
std::string ClientInstance::getScreenName(bool fresh) {
    struct GameString {
        union { char buf[16]; char* ptr; };
        size_t size;
        size_t cap;
    };
    static std::string cached;
    static ULONGLONG nextAt = 0;
    static std::mutex lock; // asked from the game thread and the render thread: the cached string is one object
    std::lock_guard<std::mutex> guard(lock);
    ULONGLONG now = GetTickCount64();
    if (!fresh && now < nextAt)
        return cached;
    nextAt = now + 250;
    GameString gs{};
    callVirtualVoid(OffsetProvider::ClientInstance_getScreenName, this, &gs);
    cached.assign(gs.cap > 15 ? gs.ptr : gs.buf, gs.size);
    return cached;
}

bool ClientInstance::isPreGame() {
    return reinterpret_cast<bool (*)(ClientInstance*)>(SIG("ClientInstance::isPreGame"))(this);
}

bool ClientInstance::isInWorldHud() {
    return getLocalPlayer() && ScreenNames::isHud(getScreenName());
}

// The game's own key bindings (Settings -> Controls). The chain is ported from Solstice-Updated, build 1.26.51; a null
// on any step means the game has no keyboard layout right now, not an error.
// 1.26.60: handler -> factory (+0x48) is the same in the aligned code of both builds, but the factory's member offset could not be proven statically, so the layout
// is found once by what it is: a pointer in the factory whose target holds a vector of 0x40-byte binds named "key.*".
static bool readable(const void* p, size_t n) {
    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(p, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)))
        return false;
    return reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize >= reinterpret_cast<uintptr_t>(p) + n;
}

static bool looksLikeLayout(const void* layout) {
    if (!layout || !readable(layout, 0x40))
        return false;
    const auto* v = reinterpret_cast<const uint8_t* const*>(reinterpret_cast<uintptr_t>(layout) + 0x8); // mKeyTypeA: begin, end, cap
    const uint8_t* begin = v[0];
    const uint8_t* end = v[1];
    if (!begin || end <= begin || (end - begin) % 0x40 != 0 || (end - begin) / 0x40 > 1024 || !readable(begin, 0x40))
        return false;
    const size_t size = *reinterpret_cast<const size_t*>(begin + 0x10), cap = *reinterpret_cast<const size_t*>(begin + 0x18);
    if (size < 5 || size > 64 || cap < size)
        return false;
    const char* name = cap >= 16 ? *reinterpret_cast<const char* const*>(begin) : reinterpret_cast<const char*>(begin);
    return readable(name, size) && memcmp(name, "key.", 4) == 0;
}

KeyboardRemappingLayout* ClientInstance::getKeyboardSettings() {
    void* handler = callVirtual<void*>(OffsetProvider::ClientInstance_getInputHandler, this);
    if (!handler)
        return nullptr;
    void* factory = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(handler) + OffsetProvider::ClientInputHandler_mMappingFactory);
    if (!factory)
        return nullptr;
    static size_t found = 0;
    if (found)
        return *reinterpret_cast<KeyboardRemappingLayout**>(reinterpret_cast<uintptr_t>(factory) + found);
    for (size_t off = 0x100; off <= 0x140; off += 8) {
        void* candidate = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(factory) + off);
        if (looksLikeLayout(candidate)) {
            found = off;
            Logger::info("[input] the keyboard layout is at factory+{:#x} (1.26.51: 0x110)", off);
            return static_cast<KeyboardRemappingLayout*>(candidate);
        }
    }
    return nullptr; // the player's binds are not loaded yet; asked again next time
}

const float* ClientInstance::findProjectionMatrix(float aspect) {
    constexpr size_t kFrom = 0x200, kTo = 0x900; // the span of the instance searched
    const auto base = reinterpret_cast<uintptr_t>(this);
    for (size_t off = kFrom; off < kTo; off += 4) {
        MEMORY_BASIC_INFORMATION mbi{};
        if (!VirtualQuery(reinterpret_cast<void*>(base + off), &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)))
            continue;
        if (reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize < base + off + 64)
            continue;
        const float* m = reinterpret_cast<const float*>(base + off);
        auto near0 = [](float v) { return fabsf(v) < 1e-5f; };
        if (!(m[0] > 0.2f && m[0] < 30.f && m[5] > 0.2f && m[5] < 60.f && fabsf(m[5] / m[0] - aspect) < aspect * 0.03f))
            continue;
        if (!(near0(m[1]) && near0(m[2]) && near0(m[3]) && near0(m[4]) && near0(m[6]) && near0(m[7]) && near0(m[8]) && near0(m[9]) && near0(m[12]) && near0(m[13]) && near0(m[15])))
            continue;
        if (fabsf(fabsf(m[11]) - 1.0f) < 1e-4f)
            return m;
    }
    return nullptr;
}
