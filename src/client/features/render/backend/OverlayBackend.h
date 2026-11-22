#pragma once
#include "client/features/render/underui/UnderTypes.h"

// The renderer's D3D12 core, with no D3D11 device, no 11on12, no wrapped buffers: command lists of its own submitted on the game's queue (at Present, or in the
// middle of the game's frame), the ImGui renderer (ImGui's backends are D3D11/D3D12 files and the repo only has the D3D11 one), and what the other passes
// (glow, blur, the item in hand, the GIF) need: upload memory for constants and vertices, shader visible descriptors for one list, textures, render targets.
struct OverlayBackend {
    struct Cmd {
        ID3D12GraphicsCommandList* list = nullptr;
        int slot = -1;
    };

    static bool init(IDXGISwapChain* sc, ID3D12CommandQueue* queue); // against this swapchain's buffers and format
    static void shutdown();                                          // waits for the GPU, releases everything (the buffers, the textures)
    static bool ready();

    static ID3D12Device* device();
    static DXGI_FORMAT backFormat();                                 // the swapchain's format
    static UINT bufferCount();
    static int bufferIndexOf(uintptr_t resource);                    // which swapchain buffer a D3D12 resource is, -1 if none
    static ID3D12Resource* buffer(UINT index);                       // identity, no reference is taken: use it within the frame
    static D3D12_CPU_DESCRIPTOR_HANDLE bufferRtv(UINT index);

    static Cmd begin(const char* what = "list");                                              // the next slot, waited for and reset, heaps set
    static void stamp(Cmd& cmd, const char* stage);                                          // profiling: the GPU time since the previous stamp (or the start) is reported as `stage`
    static void submit(Cmd& cmd, ID3D12CommandQueue* queue, UnderExec run);

    // Memory that lives as long as the list: `size` bytes of upload memory (its GPU address in `va`), and `count` shader visible descriptors (the
    // index of the first; write them with CreateShaderResourceView at srvCpu(i), bind them at srvGpu(i)).
    // A buffer in upload memory holding a copy of `data` (the caller releases it).
    static ID3D12Resource* createUploadBuffer(const void* data, size_t size);
    static void* upload(Cmd& cmd, size_t size, size_t align, D3D12_GPU_VIRTUAL_ADDRESS* va);
    static UINT srvs(Cmd& cmd, UINT count);
    static D3D12_CPU_DESCRIPTOR_HANDLE srvCpu(UINT index);
    static D3D12_GPU_DESCRIPTOR_HANDLE srvGpu(UINT index);

    // Render target and depth views of the passes' own textures, from the free ones of their heaps.
    static UINT allocRtv();
    static void freeRtv(UINT index);
    static D3D12_CPU_DESCRIPTOR_HANDLE rtvCpu(UINT index);
    static UINT allocDsv();
    static void freeDsv(UINT index);
    static D3D12_CPU_DESCRIPTOR_HANDLE dsvCpu(UINT index);

    // A texture made now from pixels in memory (one mip; a block compressed format takes its rows as block rows): uploaded and waited for.
    static ID3D12Resource* createTexture(const void* pixels, UINT width, UINT height, DXGI_FORMAT format, UINT rowPitch);
    // A texture ImGui can draw (AddImage): a descriptor of its own and the id to draw it with; the id goes back with unregisterTexture.
    static ImTextureID registerTexture(ID3D12Resource* resource);
    static void unregisterTexture(ImTextureID id);
    // A swapchain buffer moved from the state `cur` to `to` (and `cur` updated), if it is not already there.
    static void moveBuffer(Cmd& cmd, UINT index, D3D12_RESOURCE_STATES& cur, D3D12_RESOURCE_STATES to);
    static void retire(ID3D12Resource* resource);                    // released once the GPU has passed everything submitted so far
    static void waitIdle();

    // One ImGui pass into `rtv` (a target of `format`, widthPx x heightPx), recorded in `cmd`.
    static void drawImGui(Cmd& cmd, ImDrawData* data, D3D12_CPU_DESCRIPTOR_HANDLE rtv, DXGI_FORMAT format, float widthPx, float heightPx);
    // A whole pass into swapchain buffer `index` (in `state`, left in it), submitted at once.
    static void draw(ID3D12CommandQueue* queue, UnderExec run, ImDrawData* data, UINT index, D3D12_RESOURCE_STATES state);
};
