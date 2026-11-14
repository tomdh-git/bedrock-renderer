#pragma once
// Facade over Options (the registry ClientInstance::getOptions()
// returns), for callers that think in IOptionRegistry terms. The calls and
// their vtable slots live in Options.
#include "sdk/mc/client/game/ClientInstance.h"
#include "sdk/mc/client/options/Options.h"

struct IOptionRegistry {
    static Options* get(ClientInstance* ci) { return ci->getOptions(); }
    static Option* getOption(Options* registry, OptionID id) { return registry->getOption(id); }
    static bool loadFile(void* registry, const char* filePath) {
        static_cast<Options*>(registry)->loadFile(filePath);
        return true;
    }
};
