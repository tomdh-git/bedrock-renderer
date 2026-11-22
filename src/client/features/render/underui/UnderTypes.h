#pragma once

// The small types UnderUI's callers share. Kept apart from UnderUI.h (the pass interface, edited often) so that a header that only needs a
// target or an exec pointer does not drag every file that includes it into a rebuild when UnderPass changes.
struct ID3D12CommandQueue;
struct ID3D12CommandList;

using UnderExec = void (*)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*);

// What the last few seconds cost, filled by the engine and the passes (the same numbers the log prints).
struct UnderStats {
    double gpuShaderMs = 0, gpuCompositeMs = 0, gpuFogMs = 0, gpuBlurMs = 0, fullMs = 0, cpuMs = 0, sceneMs = 0;
    int bands = 1, resolution = 0, blurSamples = 0, blurQuality = 0;
    float blurLongestStreakPx = 0.f;
    const char* mode = "off";
};

// The game's target for a layer: the render target the lists before the cut drew to and, when the layer needs the scene's depth, that depth buffer.
struct UnderTarget {
    uintptr_t rt = 0;
    uintptr_t depth = 0; // non-zero: the scene's depth is still in this resource at the cut
    uintptr_t aux = 0;   // non-zero: the game's motion vector buffer (Vibrant Visuals: the zw of its prepass's third target)
};
