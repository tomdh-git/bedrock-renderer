#include "sdk/mc/client/input/GameKeys.h"
#include "sdk/mc/client/input/KeyboardRemappingLayout.h"
#include "sdk/mc/client/game/ClientInstance.h"
#include "client/platform/input/Input.h"

// The layout behind the game's controls screen, or null while the game has none (booting, no input handler yet).
static KeyboardRemappingLayout* keyboardLayout() {
    ClientInstance* ci = ClientInstance::get();
    return ci ? ci->getKeyboardSettings() : nullptr;
}

int GameKeys::hotbar(int slot) {
    if (slot < 0 || slot > 8)
        return -1;
    KeyboardRemappingLayout* layout = keyboardLayout();
    return layout ? (*layout)["key.hotbar." + std::to_string(slot + 1)] : -1;
}

int GameKeys::swapOffhand() {
    KeyboardRemappingLayout* layout = keyboardLayout();
    return layout ? (*layout)["key.swapOffhand"] : -1;
}

bool GameKeys::hotbarSwitchPressed() {
    KeyboardRemappingLayout* layout = keyboardLayout();
    if (!layout)
        return false;
    for (int i = 1; i <= 9; i++) {
        const int vk = (*layout)["key.hotbar." + std::to_string(i)];
        if (vk > 0 && Platform::Input::keyPressed(vk))
            return true;
    }
    const int offhand = (*layout)["key.swapOffhand"];
    return offhand > 0 && Platform::Input::keyPressed(offhand);
}
