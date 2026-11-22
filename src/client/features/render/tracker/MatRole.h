#pragma once

// What a draw of the game's renderer is, by the material its shaders come from (MaterialIndex): told exactly, not guessed from the shape of a list. Unknown: the
// pipeline state was made before the hooks were in (or its shaders are in no material of the game).
enum class MatRole : uint8_t {
    Unknown,
    Sky,      // the sky dome (Sky, EndSky)
    SunMoon,  // the sun and the moon
    Stars,
    Clouds,
    Weather,  // rain and snow
    Terrain,  // the world's chunks (RenderChunk, TextureShiftRenderChunk): opaque, cut-out and translucent
    Entity,   // mobs, players, armour, banners (the Actor and Entity materials)
    HeldItem, // the item in hand
    Particle,
    Cubemap,  // a sky box / panorama (Cubemap, LegacyCubemap)
    Manager,
    NameTag,  // the names over the players' heads (Nametag): 3D text drawn into the scene, before the UI
    Other,    // a known material that none of the above is, or one whose shader blob several materials with different roles share
    Count
};

constexpr int kMatRoles = static_cast<int>(MatRole::Count);

inline const char* matRoleName(MatRole r) {
    static const char* const kNames[kMatRoles] = {"unknown", "sky", "sun/moon", "stars", "clouds", "weather", "terrain", "entity", "held item", "particle", "cubemap", "ui", "nametag", "other"};
    return kNames[static_cast<int>(r)];
}
