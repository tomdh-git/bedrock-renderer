#pragma once

// The shaders UnderUI can draw: full-screen pixel shaders written as `float3 Shade(uv, p, dir, t)` in resources/shaders (baked into the DLL),
// completed with the shared prelude (constants, hashes, noise) and pixel shader entry. Menu backgrounds replace the main menu's panorama;
// skies replace the sky in a world.
struct UnderShaders {
    struct Entry {
        const char* key;  // the resource name
        const char* name; // what the player sees
        bool cheap = false; // costs next to nothing: always drawn at the full size of the screen
    };
    static const std::vector<Entry>& menu();
    static const std::vector<Entry>& sky();
    static std::string source(const char* key); // prelude + shader + entry, ready for D3DCompile
    static std::string preludeSource();          // the prelude alone (it holds the vertex shader)
    static std::string compositeSource();        // the pass that puts the lower resolution sky onto the game's target
    static std::string fogSource();              // one slice of the distance fog
    static std::string blurSource();             // the motion blur (its own vertex and pixel shader)
    static std::string chamsSource();            // the chams over the finished scene (its own vertex and pixel shader)
    static std::string nameTagBlurSource();      // smears the game's nametags with the camera's turn (after they are drawn)
    static std::string espMaskSource();          // puts the blurred scene back where the game's entities are (the ESP under the actors)
};
