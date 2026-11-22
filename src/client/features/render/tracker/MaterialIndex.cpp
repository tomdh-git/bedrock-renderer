#include "client/features/render/tracker/MaterialIndex.h"
#include "client/platform/text/StringUtils.h"
#include "client/platform/filesystem/Files.h"

std::unordered_map<uint32_t, MatRole> MaterialIndex::sRoles;
std::atomic<bool> MaterialIndex::sLoaded{false};
static std::once_flag sLoadOnce;
static std::mutex sWorkerMu;
static std::thread sWorker;
bool MaterialIndex::starts(const std::string& s, const char* p) {
    return s.rfind(p, 0) == 0;
}

// The role of a material by its file's name (without .material.bin).
MatRole MaterialIndex::roleOfName(const std::string& n) {
    if (n == "Sky" || n == "EndSky" || n == "EndSkyForwardPBR")
        return MatRole::Sky;
    if (starts(n, "SunMoon"))
        return MatRole::SunMoon;
    if (starts(n, "Stars"))
        return MatRole::Stars;
    if (starts(n, "Clouds"))
        return MatRole::Clouds;
    if (starts(n, "Weather"))
        return MatRole::Weather;
    if (starts(n, "RenderChunk") || starts(n, "TextureShiftRenderChunk"))
        return MatRole::Terrain;
    if (starts(n, "Actor") || n == "Entity")
        return MatRole::Entity;
    if (starts(n, "ItemInHand"))
        return MatRole::HeldItem;
    if (starts(n, "Particle") || n == "FlameBillboard")
        return MatRole::Particle;
    if (n == "Cubemap" || starts(n, "LegacyCubemap"))
        return MatRole::Cubemap;
    if (starts(n, "Nametag"))
        return MatRole::NameTag;
    if (starts(n, "UI") || starts(n, "Gameface") || n == "ImGui" || n == "MinecraftColor")
        return MatRole::Manager;
    return MatRole::Other;
}

// Every DXBC container in the file: the signature, and the total size at offset 24.
void MaterialIndex::indexFile(const std::string& data, MatRole role) {
    const size_t n = data.size();
    for (size_t i = 0; i + 32 <= n; ++i) {
        if (data[i] != 'D' || data[i + 1] != 'X' || data[i + 2] != 'B' || data[i + 3] != 'C')
            continue;
        uint32_t size = 0, chunks = 0;
        memcpy(&size, &data[i + 24], 4);
        memcpy(&chunks, &data[i + 28], 4);
        if (size < 64 || size > (8u << 20) || i + size > n || chunks == 0 || chunks > 64)
            continue;
        const uint32_t hash = Platform::Str::fnv1a(&data[i], size);
        auto [it, fresh] = sRoles.emplace(hash, role);
        if (!fresh && it->second != role)
            it->second = MatRole::Other; // shared by materials of different roles (a full-screen vertex shader, say): says nothing
        i += size - 1;
    }
}


// Hashing every shader blob of every material (60 MB) took 2.5 s in a debug build and sat in front of the first Present. The result only depends on the
// material files, so it is kept on disk keyed by their names and sizes: a game update changes one of them and the next inject rebuilds it.
static constexpr char kIndexMagic[8] = {'B', 'S', 'M', 'I', '1', 0, 0, 0};
struct IndexEntry {
    uint32_t hash;
    uint8_t role;
};

static uint64_t materialsKey(const std::string& dir, const std::vector<std::wstring>& files) {
    uint64_t key = 1469598103934665603ull;
    auto mix = [&key](uint64_t v) { key = (key ^ v) * 1099511628211ull; };
    for (const std::wstring& file : files) {
        const std::string name = Platform::Str::narrow(file);
        mix(Platform::Str::fnv1a(name));
        mix(Platform::Files::size(dir + name));
    }
    return key;
}

bool MaterialIndex::loadCache(const std::string& path, uint64_t key) {
    std::string data;
    if (!Platform::Files::read(path, data, 16u << 20) || data.size() < 20 || memcmp(data.data(), kIndexMagic, 8) != 0)
        return false;
    uint64_t stored = 0;
    uint32_t count = 0;
    memcpy(&stored, &data[8], 8);
    memcpy(&count, &data[16], 4);
    if (stored != key || data.size() != 20 + static_cast<size_t>(count) * sizeof(IndexEntry))
        return false;
    sRoles.reserve(count);
    for (uint32_t i = 0; i < count; ++i) {
        IndexEntry e;
        memcpy(&e, &data[20 + i * sizeof(IndexEntry)], sizeof(e));
        sRoles.emplace(e.hash, static_cast<MatRole>(e.role));
    }
    return true;
}

void MaterialIndex::saveCache(const std::string& path, uint64_t key) {
    std::string out(kIndexMagic, 8);
    const uint32_t count = static_cast<uint32_t>(sRoles.size());
    out.append(reinterpret_cast<const char*>(&key), 8);
    out.append(reinterpret_cast<const char*>(&count), 4);
    for (const auto& [h, r] : sRoles) {
        IndexEntry e{h, static_cast<uint8_t>(r)};
        out.append(reinterpret_cast<const char*>(&e), sizeof(e));
    }
    Platform::Files::write(path, out);
}

void MaterialIndex::loadImpl() {
    const std::string dir = Platform::Paths::gameDir() + "data\\renderer\\materials\\";
    const std::string ext = ".material.bin";
    const std::vector<std::wstring> files = Platform::Files::list(Platform::Str::widen(dir), L"*.material.bin");
    const uint64_t key = materialsKey(dir, files);
    const std::string cache = Platform::Paths::blueyDir() + "materialindex.bin";
    const bool cached = loadCache(cache, key);
    if (!cached) {
        for (const std::wstring& file : files) {
            const std::string name = Platform::Str::narrow(file);
            std::string data;
            Platform::Files::read(dir + name, data, 64u << 20);
            indexFile(data, roleOfName(name.substr(0, name.size() - ext.size())));
        }
        saveCache(cache, key);
    }
    size_t perRole[kMatRoles] = {};
    for (const auto& [h, r] : sRoles)
        ++perRole[static_cast<int>(r)];
    Logger::info("[materials] {} material files in {}: {} shader blobs indexed{} (sun/moon {}, stars {}, sky {}, terrain {}, entity {})", files.size(), dir, sRoles.size(),
                 cached ? " from the cache" : "", perRole[static_cast<int>(MatRole::SunMoon)], perRole[static_cast<int>(MatRole::Stars)], perRole[static_cast<int>(MatRole::Sky)],
                 perRole[static_cast<int>(MatRole::Terrain)], perRole[static_cast<int>(MatRole::Entity)]);
    MaterialIndex::sLoaded.store(true, std::memory_order_release);
}

void MaterialIndex::loadAsync() {
    std::lock_guard<std::mutex> lock(sWorkerMu);
    if (sLoaded.load(std::memory_order_acquire) || sWorker.joinable())
        return;
    try {
        sWorker = std::thread([] {
            try {
                std::call_once(sLoadOnce, &MaterialIndex::loadImpl);
            } catch (const std::exception& e) {
                Logger::error("[materials] background index failed: {}", e.what());
            } catch (...) {
                Logger::error("[materials] background index failed with an unknown error");
            }
        });
    } catch (const std::exception& e) {
        Logger::warn("[materials] could not start background index: {} (will load synchronously before tracker hooks)", e.what());
    }
}

void MaterialIndex::load() {
    std::call_once(sLoadOnce, &MaterialIndex::loadImpl); // if the worker failed, retry synchronously before any tracker callback can run
    std::thread worker;
    {
        std::lock_guard<std::mutex> lock(sWorkerMu);
        if (sWorker.joinable())
            worker = std::move(sWorker);
    }
    if (worker.joinable())
        worker.join();
}

MatRole MaterialIndex::roleOf(uint32_t shaderHash) {
    auto it = sRoles.find(shaderHash);
    return it == sRoles.end() ? MatRole::Unknown : it->second;
}

bool MaterialIndex::loaded() {
    return sLoaded.load(std::memory_order_acquire);
}
