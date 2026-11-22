#include "client/features/render/underui/passes/SkyShared.h"
#include "client/platform/time/Time.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/features/render/underui/MenuBackground.h"

SkyImpl::SkyGpu SkyImpl::g;
SkyImpl::PsoCache SkyImpl::psoCache;
Render::PassSettings<SkyImpl::SkySettings> SkyImpl::sSettings;
std::atomic<float> SkyImpl::sSkyTarget {0.f};
std::atomic<float> SkyImpl::sRamp {0.f};
std::atomic<uint32_t> SkyImpl::sThemeA {0};
std::atomic<uint32_t> SkyImpl::sThemeB {0};
thread_local uint32_t SkyImpl::sFrameThemeA = 0;
thread_local uint32_t SkyImpl::sFrameThemeB = 0;
thread_local float SkyImpl::sFrameNear = 0.f;
thread_local float SkyImpl::sFrameFar = 0.f;
double SkyImpl::sFrameSeconds = 0;
SkyImpl::Bake SkyImpl::bake;
bool SkyImpl::sMenuTable = false;

// A hash of a lattice point, 0..1.
float SkyImpl::latticeHash(float x, float y) {
    auto frac1 = [](float v) { return v - std::floor(v); };
    float a = frac1(x * 0.1031f), b = frac1(y * 0.1031f), c = frac1(x * 0.1031f);
    const float d = a * (b + 33.33f) + b * (c + 33.33f) + c * (a + 33.33f);
    a += d; b += d; c += d;
    return frac1((a + b) * c);
}

// The two noise lattices: a two channel one (the second channel is the first, shifted) and a one channel one.
void SkyImpl::fillLattices(std::vector<uint8_t>& lat3, std::vector<uint8_t>& lat2) {
    constexpr UINT N = kNoiseSize;
    lat3.assign(N * N * 2, 0);
    lat2.assign(N * N, 0);
    for (UINT y = 0; y < N; ++y)
        for (UINT x = 0; x < N; ++x) {
            lat3[(y * N + x) * 2] = static_cast<uint8_t>(latticeHash(static_cast<float>(x), static_cast<float>(y) + 300.f) * 255.f + 0.5f);
            lat2[y * N + x] = static_cast<uint8_t>(latticeHash(static_cast<float>(x), static_cast<float>(y)) * 255.f + 0.5f);
        }
    for (UINT y = 0; y < N; ++y)
        for (UINT x = 0; x < N; ++x)
            lat3[(y * N + x) * 2 + 1] = lat3[(((y + 17) % N) * N + ((x + 37) % N)) * 2];
}

// Copies the upload buffer's bytes at `offset` into the texture.
void SkyImpl::copyLattice(ID3D12Resource* upload, ID3D12Resource* tex, UINT64 offset, DXGI_FORMAT format, UINT pitch) {
    D3D12_TEXTURE_COPY_LOCATION dst{};
    dst.pResource = tex;
    dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    D3D12_TEXTURE_COPY_LOCATION src{};
    src.pResource = upload;
    src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    src.PlacedFootprint = {offset, {format, kNoiseSize, kNoiseSize, 1, pitch}};
    UnderGpu::list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
}
void SkyImpl::makeNoise(ID3D12CommandQueue* q, Render::UnderUI::ExecFn run) {
    std::vector<uint8_t> lat3, lat2;
    fillLattices(lat3, lat2);
    GpuPtr<ID3D12Resource> upload = GpuUtil::createBuffer(UnderGpu::dev, lat3.size() + lat2.size()); // released when this function ends, after the GPU is idle
    uint8_t* mapped = nullptr;
    BS_CHECK_HR(upload->Map(0, nullptr, reinterpret_cast<void**>(&mapped)));
    memcpy(mapped, lat3.data(), lat3.size());
    memcpy(mapped + lat3.size(), lat2.data(), lat2.size());
    upload->Unmap(0, nullptr);

    g.lat3 = GpuUtil::createTexture(UnderGpu::dev, kNoiseSize, kNoiseSize, DXGI_FORMAT_R8G8_UNORM, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_COPY_DEST);
    g.lat2 = GpuUtil::createTexture(UnderGpu::dev, kNoiseSize, kNoiseSize, DXGI_FORMAT_R8_UNORM, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_COPY_DEST);
    UnderGpu::beginList(nullptr);
    copyLattice(upload, g.lat3, 0, DXGI_FORMAT_R8G8_UNORM, kNoiseSize * 2);
    copyLattice(upload, g.lat2, lat3.size(), DXGI_FORMAT_R8_UNORM, kNoiseSize);
    const D3D12_RESOURCE_BARRIER to[2] = {D3D12Util::transition(g.lat3, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE),
                                          D3D12Util::transition(g.lat2, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)};
    UnderGpu::list->ResourceBarrier(2, to);
    UnderGpu::submit(q, run);
    UnderGpu::waitIdle(); // once, at the start: the upload buffer may go
    UnderGpu::dev->CreateShaderResourceView(g.lat3, nullptr, srvAt(kNoiseAt));
    UnderGpu::dev->CreateShaderResourceView(g.lat2, nullptr, srvAt(kNoiseAt + 1));
}
SkyImpl::SkyPick SkyImpl::currentPick(const SkySettings& s) {
    SkyPick p;
    p.gain = s.gain;
    const bool inWorldNow = UnderGpu::inWorld.load();
    // 0 balanced (the menu picture at 0.7, brought up with a sharp filter; the sky map as fine as an ordinary screen needs), 1 native, 2 low
    p.envScale = s.resolution == 1 ? 1.3f : s.resolution == 2 ? 0.75f : 1.0f;
    p.scale = s.resolution == 1 ? 1.0f : s.resolution == 2 ? 0.5f : 0.7f;
    (void)inWorldNow;
    if (UnderGpu::inWorld.load()) {
        if (s.skyOn) {
            p.key = UnderShaders::sky()[static_cast<size_t>(std::clamp(s.style, 0, static_cast<int>(UnderShaders::sky().size()) - 1))].key;
            p.theme = s.theme;
        }
    } else if (int m = MenuBackground::index(); m > 0) {
        p.key = UnderShaders::menu()[static_cast<size_t>(m) - 1].key;
        p.theme = true; // the menu backgrounds are the client's: always its colors
        p.menu = true;
        if (UnderShaders::menu()[static_cast<size_t>(m) - 1].cheap)
            p.scale = 1.0f; // nothing to save
        else
            p.interleave = true;
        p.interval = 0.034f;
    }
    return p;
}
float SkyImpl::skySeconds() {
    static const ULONGLONG t0 = Platform::Time::millis();
    return static_cast<float>(Platform::Time::millis() - t0) / 1000.0f;
}

// ---- the menu background and the sky ----------------------------------------------------------------------------------
//
// The menu background is a picture the size of the game's target (native), drawn whole every frame: its motion is the point of it.
void SkyImpl::skyConstants(float* c, const SkyPick& pick, float w, float h, bool hdr, const UnderCamera& cam, bool composite, bool envBake) {
    auto channel = [](uint32_t v, int shift) { return static_cast<float>((v >> shift) & 255) / 255.0f; };
    const uint32_t ta = sFrameThemeA, tb = sFrameThemeB; // this frame's copies: every draw of the frame sees the same pair
    const float fade = UiMath::clamp01(static_cast<float>(Platform::Time::millis() - bake.fadeStart) / (kFadeSeconds * 1000.0f));
    const float ramp = UiMath::smoothstep(sRamp.load()); // smoothstep: the intensity eases in and out
    float k[kConstants + 1] = {
        w, h, skySeconds(), hdr ? pick.gain : 1.0f,
        cam.right[0], cam.right[1], cam.right[2], cam.fov[0],
        cam.up[0], cam.up[1], cam.up[2], cam.fov[1],
        cam.fwd[0], cam.fwd[1], cam.fwd[2], cam.valid ? 1.0f : 0.0f,
        channel(ta, 0), channel(ta, 8), channel(ta, 16), pick.theme ? 1.0f : 0.0f,
        channel(tb, 0), channel(tb, 8), channel(tb, 16), hdr ? 1.0f : 0.0f,
        0.f, 0.f, 0.f, 1.f,                                           // E: the fog's slice (set per slice)
        0.f, 0.f, 0.f, 0.f,                                           // F: (unused)
        0.f, 0.f, 0.f, 0.f,                                           // G: (unused)
        0.f, 0.f, 0.f, composite && !pick.menu ? 1.0f : 0.0f,         // H: w = 1: the pictures are environment maps
        0.f, 0.f, 0.f, 0.f,                                           // I: (unused)
        0.f, 0.f, 0.f, 0.f,                                           // J: (unused)
        0.f, 0.f, 0.f, bake.phase,                                    // K: w = the crossfade
        composite ? ramp * (pick.menu ? 1.0f : fade) : 1.0f, 1.f, envBake ? 1.0f : 0.0f, 0.f, // L: opacity, margin, drawing the environment map
        -12345.f};                                                    // the end marker: the list above must be exactly kConstants long
    BS_CHECK(k[kConstants] == -12345.f);
    memcpy(c, k, sizeof(float) * kConstants);
}
D3D12_CPU_DESCRIPTOR_HANDLE SkyImpl::skyRtv(int i) { return GpuUtil::cpuAt(g.skyRtvHeap, static_cast<UINT>(i), g.rtvStep); }
D3D12_CPU_DESCRIPTOR_HANDLE SkyImpl::srvAt(UINT i) { return GpuUtil::cpuAt(g.srvHeap, i, g.srvStep); }
ID3D12Resource* SkyImpl::skyMakeTarget(UINT w, UINT h, DXGI_FORMAT format) {
    const D3D12_CLEAR_VALUE cv{format, {0.f, 0.f, 0.f, 1.f}};
    return GpuUtil::createTexture(UnderGpu::dev, w, h, format, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &cv);
}

// The three environment maps (10 bits a channel: finer than the 8 the screen shows, half the size of float16). True when they were (re)made.
bool SkyImpl::ensureEnv(UINT w, UINT h) {
    if (g.tex[0] && g.skyW == w && g.skyH == h)
        return false;
    UnderGpu::waitIdle();
    for (auto& t : g.tex)
        t.reset();
    for (int i = 0; i < 3; ++i) {
        g.tex[i] = skyMakeTarget(w, h, DXGI_FORMAT_R10G10B10A2_UNORM);
        UnderGpu::dev->CreateRenderTargetView(g.tex[i], nullptr, skyRtv(i));
    }
    const int slot[11] = {0, 1, 2, 0, 1, 0, 0, 1, 1, 2, 2}; // (previous, current) pairs in a row; then each map twice (previous = current)
    for (UINT i = 0; i < 11; ++i)
        UnderGpu::dev->CreateShaderResourceView(g.tex[slot[i]], nullptr, srvAt(i));
    g.skyW = w;
    g.skyH = h;
    return true;
}
bool SkyImpl::ensureMenu(UINT w, UINT h) {
    if (g.menuTex && g.menuW == w && g.menuH == h)
        return false;
    UnderGpu::waitIdle();
    g.menuTex = skyMakeTarget(w, h, DXGI_FORMAT_R16G16B16A16_FLOAT);
    g.menuClear = true;
    UnderGpu::dev->CreateRenderTargetView(g.menuTex, nullptr, skyRtv(3));
    UnderGpu::dev->CreateShaderResourceView(g.menuTex, nullptr, srvAt(kMenuAt));
    UnderGpu::dev->CreateShaderResourceView(g.menuTex, nullptr, srvAt(kMenuAt + 1));
    g.menuW = w;
    g.menuH = h;
    return true;
}

// Where in the heap the (previous, current) pair of pictures starts.
UINT SkyImpl::tableStart() {
    if (sMenuTable)
        return kMenuAt;
    return bake.p == bake.c ? 5u + 2u * static_cast<UINT>(bake.p) : static_cast<UINT>(bake.p);
}
void SkyImpl::bindTable() {
    ID3D12DescriptorHeap* heaps[] = {g.srvHeap.get()};
    UnderGpu::list->SetDescriptorHeaps(1, heaps);
    UnderGpu::list->SetGraphicsRootSignature(g.root.get());
    UnderGpu::list->SetGraphicsRootDescriptorTable(1, GpuUtil::gpuAt(g.srvHeap, tableStart(), g.srvStep));
    UnderGpu::list->SetGraphicsRootDescriptorTable(2, GpuUtil::gpuAt(g.srvHeap, kNoiseAt, g.srvStep));
    UnderGpu::list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
void SkyImpl::frameClock() {
    static double sLast = 0;
    const double now = Platform::Time::seconds();
    if (sLast > 0) {
        const double dt = now - sLast;
        if (dt < 0.25) {
            sFrameSeconds = sFrameSeconds == 0 ? dt : sFrameSeconds + (dt - sFrameSeconds) * 0.05;
            const float target = sSkyTarget.load();
            const float step = static_cast<float>(dt) / kRampSeconds;
            const float ramp = sRamp.load();
            sRamp.store(target > ramp ? std::min(target, ramp + step) : std::max(target, ramp - step));
        }
    }
    sLast = now;
}

// The main menu's background: the shader whole, at the size of the game's target, every frame, onto the target.
UINT SkyImpl::envWidth(UINT screenHeight, float scale) {
    // finer than the screen's angular resolution at ordinary fields of view: the map is longitude / latitude, twice as wide as tall
    return std::clamp<UINT>(static_cast<UINT>(std::lround(screenHeight * scale * 3.8 / 64.0)) * 64, 1024, 8192);
}

