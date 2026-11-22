#include "client/features/render/underui/UnderShaders.h"
#include "client/platform/resources/Resources.h"

static std::string text(const char* key) {
    auto it = Platform::ResourceLoader::Resources.find(key);
    BS_CHECK(it != Platform::ResourceLoader::Resources.end());
    return std::string(it->second.data(), it->second.size());
}

const std::vector<UnderShaders::Entry>& UnderShaders::menu() {
    static const std::vector<Entry> list = {
        {"menu_colorbends", "Color Bends", true},
    };
    return list;
}

const std::vector<UnderShaders::Entry>& UnderShaders::sky() {
    static const std::vector<Entry> list = {
        {"sky_aurora", "Aurora"},
        {"sky_liquid", "Liquid"},
        {"sky_auroraliquid", "Aurora Liquid"},
    };
    return list;
}

std::string UnderShaders::preludeSource() {
    return text("sh_common");
}

std::string UnderShaders::source(const char* key) {
    return text("sh_common") + "\n" + text(key) + "\n" + text("sh_ps");
}

std::string UnderShaders::compositeSource() {
    return text("sh_common") + "\n" + text("sh_composite");
}

std::string UnderShaders::fogSource() {
    return text("sh_common") + "\n" + text("sh_fog");
}

std::string UnderShaders::blurSource() {
    return text("sh_motionblur");
}

std::string UnderShaders::chamsSource() {
    return text("sh_chams");
}

std::string UnderShaders::nameTagBlurSource() {
    return text("sh_ntblur");
}

std::string UnderShaders::espMaskSource() {
    return text("sh_espmask");
}
