#include "client/features/render/underui/MenuBackground.h"
#include "client/features/settings/preferences/Preferences.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/platform/filesystem/Files.h"

static std::atomic<int> sIndex{-1}; // -1: not read yet
static std::atomic<ULONGLONG> sChanged{0};

int MenuBackground::count() {
    return static_cast<int>(UnderShaders::menu().size()) + 1;
}

int MenuBackground::index() {
    int i = sIndex.load();
    if (i >= 0)
        return i;
    const int v = Preferences::Store::menuBackground(1, count()); // 0 is the game's panorama, 1.. are UnderShaders::menu(); the first shader by default
    sIndex.store(v);
    return v;
}

const char* MenuBackground::name(int i) {
    const auto& menu = UnderShaders::menu();
    if (i <= 0 || menu.empty())
        return "Game panorama";
    return menu[std::min(static_cast<size_t>(i), menu.size()) - 1].name;
}

void MenuBackground::next() {
    // The panorama and every shader, round-robin (a lone shader toggles it; an empty list stays on the panorama: (i + 1) % 1 == 0).
    const int v = (index() + 1) % count();
    sIndex.store(v);
    sChanged.store(Platform::Time::millis());
    Preferences::Store::setMenuBackground(v);
}

float MenuBackground::caption() {
    ULONGLONG at = sChanged.load();
    if (!at)
        return 0.f;
    float age = static_cast<float>(Platform::Time::millis() - at) / 1000.f;
    return age < 1.4f ? 1.f : UiMath::clamp01(1.f - (age - 1.4f) / 0.5f);
}
