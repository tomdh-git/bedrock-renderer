#pragma once
#include "client/features/render/tracker/MatRole.h"

// The game's materials by their shaders. Every pipeline state the game creates uses shader blobs that are byte for byte inside one of the
// data/renderer/materials/*.material.bin files next to the executable, and the files are named for what they draw (SunMoon, Stars, Sky, RenderChunk, Actor...):
// the hash of a blob tells exactly what a draw is. Loaded once at startup (about 160 small files).
struct MaterialIndex {
    static void load();                       // idempotent; logs how many shader blobs it indexed
    static void loadAsync();                  // overlap the cold disk scan with independent startup work; load() joins before hooks need it
    static MatRole roleOf(uint32_t shaderHash); // Unknown when the hash is in no material
    static bool loaded();

private:
    static void loadImpl();
    static std::unordered_map<uint32_t, MatRole> sRoles;
    static std::atomic<bool> sLoaded;
    static bool starts(const std::string& s, const char* p);
    static MatRole roleOfName(const std::string& n);
    static bool loadCache(const std::string& path, uint64_t key);
    static void saveCache(const std::string& path, uint64_t key);
    static void indexFile(const std::string& data, MatRole role);
};
