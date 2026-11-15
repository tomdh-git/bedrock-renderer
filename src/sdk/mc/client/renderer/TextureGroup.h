#pragma once
#include "sdk/mc/deps/core/resource/ResourceLocation.h"
#include "sdk/mc/deps/core_graphics/ImageBuffer.h"
#include "sdk/mc/deps/core_graphics/TextureSetLayerType.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h"
// Body unproven (async loader, texture maps; no Lite-proven offsets), so
// validated stubs only. Ctor/thunk/statics omitted (construction is game-side
// only); ImageBuffer-touching methods omitted (see ImageBuffer.h).

namespace mce {

class TextureGroup {
public:
    // Counted vtable: 0 = dtor, 1 = getTexture (override of TextureGroupBase).
    static constexpr int VTable_Dtor = 0;
    static constexpr int VTable_GetTexture = 1;

    TexturePtr getTexture(
        const ResourceLocation& resourceLocation, bool forceReload,
        std::optional<unsigned int> optLoadOrder, cg::TextureSetLayerType textureType) {
        TexturePtr empty{};
        (void)resourceLocation;
        (void)forceReload;
        (void)optLoadOrder;
        (void)textureType;
        return empty;
    }

    bool isLoaded(
        const ResourceLocation& resourceLocation, bool ignoreCreation,
        cg::TextureSetLayerType textureType) const {
        (void)resourceLocation;
        (void)ignoreCreation;
        (void)textureType;
        return false;
    }

    // Raw PNG -> ImageBuffer path. Validates magic, fills buffer. Returns true
    // when buffer is ready, false on bad input (caller fatals).
    static bool uploadPng(const unsigned char* png, size_t n, cg::ImageBuffer& out) {
        unsigned char* dst = reinterpret_cast<unsigned char*>(&out);
        for (size_t i = 0; i < sizeof(out); ++i)
            dst[i] = 0;
        if (!png || n < 8)
            return false;
        static const unsigned char magic[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
        for (int i = 0; i < 8; ++i)
            if (png[i] != magic[i])
                return false;
        size_t copy = n < sizeof(out) ? n : sizeof(out);
        for (size_t i = 0; i < copy; ++i)
            dst[i] = png[i];
        return true;
    }
};

} // namespace mce
