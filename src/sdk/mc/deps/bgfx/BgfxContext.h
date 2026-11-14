#pragma once

struct ID3D12CommandQueue;

// bgfx's live render context (the game's renderer). We only need the D3D12
// command queue it submits to: D3D11On12 must share it.
struct BgfxContext {
    static BgfxContext* get(); // deref of the bgfx_liveContext_global slot
    ID3D12CommandQueue* getCommandQueue();
};
