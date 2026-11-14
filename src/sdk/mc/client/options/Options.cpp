#include "sdk/mc/client/options/Options.h"
#include "sdk/Layout.h"
#include "sdk/OffsetProvider.h"
#include "sdk/mc/deps/core/string/GameString.h"
#include "client/core/diagnostics/Log.h"

Option* Options::getOption(OptionID id) {
    Option* out = nullptr;
    callVirtualVoid(OffsetProvider::Options_getOption, this, &out, id);
    return out;
}

// The game's loadFile takes its own (Release STL) string and may free or replace its buffer.
void Options::loadFile(const char* path) {
    GameString str = GameString::make(path);
    callVirtualVoid(OffsetProvider::Options_loadFile, this, &str);
}

bool Options::isFirstPerson() {
    int mode = getOption(OptionID::Perspective)->getInt();
    BS_CHECK(mode >= 0 && mode <= 2); // anything else means the option id is wrong
    return mode == 0;
}
