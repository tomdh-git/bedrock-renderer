#pragma once

namespace bgfx {

// The 65-slot RendererContextI virtual table of 1.26.62.01 (docs/BGFX_MAP.md 6f). The live object is the "Direct3D 12 RTX" subclass; the base D3D12 class is its parent.
struct RendererContextSlots {
    static constexpr uintptr_t kBaseD3D12Vtable = 0xF4ED2D0; // rva
    static constexpr uintptr_t kRtxVtable = 0xF4EEE80;       // rva (the live object's vtable)
    static constexpr size_t kSlotCount = 65;
    static constexpr size_t kRendererName = 4;    // [V]
    static constexpr size_t kCreateShader = 22;   // [V] "Unknown shader format %x."
    static constexpr size_t kSubmit = 50;         // [V] base 0xe82e230; RTX override 0xe83d440 wraps it
    static constexpr size_t kInit = 58;           // [V] base 0xe807ff0 ("d3d12.dll"); RTX override 0xe83e200
    static constexpr size_t kRtxSkinning = 63;    // [V] RTX only, 0xe83f1d0 ("GPU skinning Vertices of Actor")
    static constexpr size_t kRtxSuperSampling = 64; // [V] RTX only, 0xe8403d0 (DLSS / "SuperSampling.*")
    static constexpr uintptr_t slotOffset(size_t slot) { return slot * sizeof(void*); }
};

} // namespace bgfx
