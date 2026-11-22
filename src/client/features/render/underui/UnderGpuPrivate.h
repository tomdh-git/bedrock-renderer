#pragma once
#include "client/features/render/underui/UnderGpu.h"
#include "client/platform/filesystem/Files.h"
#include "sdk/mc/client/game/ClientInstance.h"

// ---- state private to this file (a struct: the build is unity, names in anonymous namespaces would meet those of other files) ------------------

struct UnderGpuPrivate {
    static inline ID3D12DescriptorHeap* rtvHeap = nullptr; // the game's target
    static inline ID3D12DescriptorHeap* dsvHeap = nullptr;
    static inline ID3D12CommandAllocator* alloc[UnderGpu::kRing] = {};
    static inline ID3D12Fence* fence = nullptr;
    static inline HANDLE event = nullptr;
    static inline UINT64 value = 0;
    static inline UINT64 allocValue[UnderGpu::kRing] = {};
    static inline UINT frame = 0;
    static inline UINT rtvStep = 0;
    static inline ID3D12QueryHeap* qHeap = nullptr;
    static inline ID3D12Resource* qBuf = nullptr;
    static inline const UINT64* qData = nullptr;
    static inline UINT64 freq = 0;
    struct Pair {
        UINT64 fence = 0;
        int timer = 0;
        int bands = 1;
        bool pending = false;
    };
    static inline Pair pairs[UnderGpu::kPairs];
    static inline int nextPair = 0;

    using PsoKey = std::tuple<std::string, int, UINT, int>; // (shader name, target format, samples, depth format or 0)
    struct Builder {
        std::mutex mu;
        std::condition_variable cv;
        std::map<PsoKey, ID3D12PipelineState*> pso;
        std::set<PsoKey> requested;
        std::deque<PsoKey> jobs;
        std::map<std::string, ID3DBlob*> blobs; // worker only
        std::vector<std::pair<std::string, UnderGpu::Resolver>> resolvers;
        bool stop = false;
        HANDLE worker = nullptr; // a raw handle: a std::thread still joinable when the game exits would abort() in its static destructor
    };
    static inline Builder bld;

    static inline std::mutex camMu;
    static inline UnderCamera cam;

    static uint64_t fnv64(const std::string& s) {
        uint64_t h = 1469598103934665603ull;
        for (unsigned char c : s)
            h = (h ^ c) * 1099511628211ull;
        return h;
    }

    // Compiles `src` (or reads the result of an earlier compile from %APPDATA%\BlueySenseV2\shadercache: the heavy shaders take a second to build).
    static ID3DBlob* compile(const std::string& src, const char* name, const char* entry, const char* target) {
        const std::string cacheDir = Platform::Paths::blueyDir() + "shadercache\\";
        Platform::Files::makeDirs(cacheDir);
        const std::string file = fmt::format("{}{}_{}_{:016x}.dxbc", cacheDir, name, entry, fnv64(src + target));
        ID3DBlob* code = nullptr;
        std::wstring wfile(file.begin(), file.end());
        if (SUCCEEDED(D3DReadFileToBlob(wfile.c_str(), &code)) && code)
            return code;
        ULONGLONG t0 = Platform::Time::millis();
        ID3DBlob* errors = nullptr;
        HRESULT hr = D3DCompile(src.data(), src.size(), name, nullptr, nullptr, entry, target, D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &code, &errors);
        if (FAILED(hr))
            Logger::fatal("[underui] shader {} ({}) failed: {}", name, entry, errors ? static_cast<const char*>(errors->GetBufferPointer()) : "?");
        UnderGpu::release(errors);
        D3DWriteBlobToFile(code, wfile.c_str(), TRUE);
        return code;
    }

    static ID3DBlob* blob(const std::string& key, const std::string& src, const std::string& name, const char* entry, const char* target) {
        ID3DBlob*& b = bld.blobs[key];
        if (!b)
            b = compile(src, name.c_str(), entry, target);
        return b;
    }

    // Source alpha over the target when the shader asks for it (the composites and the fog); otherwise the pass overwrites.
    static void setBlend(D3D12_RENDER_TARGET_BLEND_DESC& rt, bool enable) {
        rt.BlendEnable = enable;
        rt.SrcBlend = D3D12_BLEND_SRC_ALPHA;
        rt.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
        rt.BlendOp = D3D12_BLEND_OP_ADD;
        rt.SrcBlendAlpha = D3D12_BLEND_ZERO;
        rt.DestBlendAlpha = D3D12_BLEND_ONE;
        rt.BlendOpAlpha = D3D12_BLEND_OP_ADD;
        rt.LogicOp = D3D12_LOGIC_OP_NOOP;
        rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    }

    // Depth is tested against the scene's, read only: the sky only where the scene's depth is still the far plane; the fog only behind a slice.
    static void setDepth(D3D12_GRAPHICS_PIPELINE_STATE_DESC& d, bool test, DXGI_FORMAT depth) {
        d.DepthStencilState.DepthEnable = test && depth != DXGI_FORMAT_UNKNOWN;
        d.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
        d.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
        d.DepthStencilState.StencilEnable = FALSE;
        d.DepthStencilState.FrontFace = {D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS};
        d.DepthStencilState.BackFace = d.DepthStencilState.FrontFace;
        d.DSVFormat = test ? depth : DXGI_FORMAT_UNKNOWN;
    }

    // The resolver registered for the name's prefix (it runs on the worker; read-only here).
    static UnderGpu::Resolver resolverFor(const std::string& name) {
        UnderGpu::Resolver resolver = nullptr;
        for (auto& [prefix, fn] : bld.resolvers)
            if (name.rfind(prefix, 0) == 0)
                resolver = fn;
        BS_CHECK(resolver);
        return resolver;
    }

    static ID3D12PipelineState* build(const PsoKey& k) {
        const DXGI_FORMAT format = static_cast<DXGI_FORMAT>(std::get<1>(k));
        const UINT samples = std::get<2>(k);
        const DXGI_FORMAT depth = static_cast<DXGI_FORMAT>(std::get<3>(k));
        const UnderShaderDef def = resolverFor(std::get<0>(k))(std::get<0>(k));
        BS_CHECK(def.root);
        ID3DBlob* vs = blob(def.vsName + ":vs", def.vsSource, def.vsName, "VS", "vs_5_0");
        ID3DBlob* ps = blob(def.psName + ":ps", def.psSource, def.psName, "PS", "ps_5_0");
        D3D12_GRAPHICS_PIPELINE_STATE_DESC d{};
        d.pRootSignature = def.root;
        d.VS = {vs->GetBufferPointer(), vs->GetBufferSize()};
        d.PS = {ps->GetBufferPointer(), ps->GetBufferSize()};
        setBlend(d.BlendState.RenderTarget[0], def.blend);
        d.SampleMask = UINT_MAX;
        d.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
        d.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
        d.RasterizerState.DepthClipEnable = TRUE;
        setDepth(d, def.depth, depth);
        d.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        d.NumRenderTargets = 1;
        d.RTVFormats[0] = format;
        d.SampleDesc.Count = samples;
        ID3D12PipelineState* pso = nullptr;
        BS_CHECK_HR(UnderGpu::dev->CreateGraphicsPipelineState(&d, IID_PPV_ARGS(&pso)));
        return pso;
    }

    static void work() {
        for (;;) {
            PsoKey k;
            {
                std::unique_lock<std::mutex> lk(bld.mu);
                bld.cv.wait(lk, [] { return bld.stop || !bld.jobs.empty(); });
                if (bld.stop)
                    return;
                k = bld.jobs.front();
                bld.jobs.pop_front();
            }
            ULONGLONG t0 = Platform::Time::millis();
            ID3D12PipelineState* pso = build(k);
            std::lock_guard<std::mutex> lk(bld.mu);
            bld.pso[k] = pso;
        }
    }

    static void request(const PsoKey& k, bool front) { // bld.mu held
        if (bld.stop || !bld.requested.insert(k).second)
            return;
        if (front)
            bld.jobs.push_front(k);
        else
            bld.jobs.push_back(k);
        bld.cv.notify_one();
    }
};
