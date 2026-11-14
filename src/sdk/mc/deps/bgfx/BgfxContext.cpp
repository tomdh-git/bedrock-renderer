#include "sdk/mc/deps/bgfx/BgfxContext.h"
#include "sdk/OffsetProvider.h"
#include "sdk/SigManager.h"

BgfxContext* BgfxContext::get() {
    return *reinterpret_cast<BgfxContext**>(SIG("BgfxContext::liveContext"));
}

ID3D12CommandQueue* BgfxContext::getCommandQueue() {
    return *reinterpret_cast<ID3D12CommandQueue**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::bgfx_RendererContextD3D12_mCommandQueue);
}
