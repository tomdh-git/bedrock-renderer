#include "client/features/render/underui/UnderGpuPrivate.h"
#include "client/platform/process/Process.h"

// ---- pipelines -------------------------------------------------------------------------------------------------------------

void UnderGpu::addShaders(const char* prefix, Resolver resolver) {
    UnderGpuPrivate::bld.resolvers.emplace_back(prefix, resolver);
}

ID3D12PipelineState* UnderGpu::pipeline(const std::string& name, DXGI_FORMAT format, UINT samples, DXGI_FORMAT depth) {
    using P = UnderGpuPrivate;
    const P::PsoKey k = std::make_tuple(name, static_cast<int>(format), samples, static_cast<int>(depth));
    std::lock_guard<std::mutex> lk(P::bld.mu);
    auto it = P::bld.pso.find(k);
    if (it != P::bld.pso.end())
        return it->second;
    P::request(k, true);
    return nullptr;
}

void UnderGpu::warm(const std::string& name, DXGI_FORMAT format, UINT samples, DXGI_FORMAT depth) {
    using P = UnderGpuPrivate;
    std::lock_guard<std::mutex> lk(P::bld.mu);
    P::request(std::make_tuple(name, static_cast<int>(format), samples, static_cast<int>(depth)), false);
}

void UnderGpu::startBuilder() {
    using P = UnderGpuPrivate;
    {
        std::lock_guard<std::mutex> lk(P::bld.mu);
        if (P::bld.worker)
            return;
        P::bld.stop = false;
    }
    P::bld.worker = Platform::Threads::start([](LPVOID) -> DWORD { UnderGpuPrivate::work(); return 0; }, nullptr, true);
}

void UnderGpu::stopBuilder() {
    using P = UnderGpuPrivate;
    {
        std::lock_guard<std::mutex> lk(P::bld.mu);
        P::bld.stop = true;
        P::bld.jobs.clear();
        P::bld.cv.notify_all();
    }
    Platform::Threads::join(P::bld.worker);
}
