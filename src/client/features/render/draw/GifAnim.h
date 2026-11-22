#pragma once

struct GifAnim {
    static inline ID3D12Resource* res12 = nullptr;         // the strip's texture
    static inline ImTextureID texId = 0;                   // what ImGui draws it with
    static inline std::string loadedKey;
    static inline int frames = 16;
    static inline float frameDt = 0.04f;
    static inline float t = 0.f;
    static inline size_t idx = 0;
    static inline int imgW = 0, imgH = 0;

    static void clear();

    // Decodes a baked strip straight from DLL memory (no image files on disk).
    static bool ensure(const uint8_t* data, size_t size, const char* key);
    static void finish(UINT w, UINT h, const char* key);

    static void update(float dt);

    static void draw(ImDrawList* d, ImVec2 pos, float h, int alpha);

    static void shutdown();
};
