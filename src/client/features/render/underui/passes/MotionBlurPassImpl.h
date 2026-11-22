#pragma once
#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/backend/D3D12Util.h"
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/render/underui/UnderShaders.h"
#include "client/features/render/underui/CameraMotion.h"
#include "client/core/diagnostics/Profiler.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"
#include "client/features/hooks/hooks/render/ActorRenderDispatcherHook.h"

// What MotionBlurPass.cpp keeps for itself: its constants, state and helpers.
struct MotionBlurPassImpl {
    static constexpr DXGI_FORMAT kMbPacked = DXGI_FORMAT_R16G16B16A16_FLOAT; // colour and distance
    static constexpr UINT kMbConstants = 60;              // 15 float4: see the shader
    static constexpr UINT kMbViews = 6;                   // scene copy, depth, vectors, world before the entities, world with them, the focus
    static constexpr int kMbRing = 48;                    // descriptor sets (three a frame with the depth of field): a few frames in flight
    static constexpr int kMbSamples[4] = {10, 16, 28, 48}; // most samples a pixel takes: low, medium, high, ultra
    static constexpr float kMbSpacing[4] = {4.0f, 3.0f, 2.5f, 2.0f}; // pixels between two samples
    static constexpr double kMbFilmExposure = 1.0 / 48.0; // seconds of exposure at a shutter of 1
    static constexpr float kMbKnee = 0.4f;                // pixels: a trail shorter than this is nothing, three times it is all of it: the opacity follows the trail's length, so a short exposure leaves a faint trail and not a soft picture
    static constexpr float kMbMaxPercent = 40.0f;         // the longest blur, % of the screen's height (only the last 40 % of it is eased: below that the blur is the angle turned, to the pixel)
    static constexpr double kMbBudgetMs = 1.0;            // what automatic quality aims to stay under (the copy and barriers alone cost a good part of it on an integrated GPU)
    static constexpr float kMbSkipPixels = 0.4f;           // the pass is not run for a blur whose longest streak (at the screen's edge of the exposure) is shorter than this: it is the shader's own fade-in floor (kMbKnee), so a shorter one would draw nothing and still cost the copy, the barriers and the draw
    static constexpr float kMbWalkBoost = 1.6f;            // the camera's own displacement counts this much more than its exposure says: walking straight ahead is otherwise a faint streaming of the floor
    static constexpr float kMbMoveSmoothing = 0.45f;       // how much of the walk's displacement a frame takes (the rest is the frames' average): the camera's own velocity oscillates frame to frame (a third-person camera follows with spring physics), and this averages the walk's displacement so the blur's strength does not pulse. The turn is NOT smoothed: the eye reads camera flick as crisp
    static constexpr float kMbCocPercent = 0.9f;          // the largest depth of field disc at an aperture of 1, % of the screen's height
    struct MbSettings;
    struct MbGpu;
    struct MbFrame;
    struct MbDiag;
    static MbGpu mb;
    static MbFrame sFrame;
    static MbDiag sDiag;
    static Render::PassSettings<MbSettings> sSettings;
    static UnderShaderDef resolveBlur(const std::string& name);
    static void mbInit();
    static void mbEnsure(GpuTexture& t, UINT w, UINT h, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE);
    static UINT mbStateOf(uintptr_t res, UINT fallback);
    static CameraMotion sMo;
    static int sLevel;           // automatic quality: index into the tables
    static uint32_t sSinceCheck;
    static uint32_t sCalm;       // frames the pass has run under budget while a long blur was drawn (the only proof there is room for more samples)
    static float sEstPx;       // the longest blur this frame, in pixels (estimated on the CPU)
    static uint32_t sFrames;
    static Vec3 sLastDp;       // the last frame's smoothed walk displacement: the depth is read only on frames whose walk needs it (a pure turn does not depend on distance), so the sky cannot be moved by a wrong single distance
    static Vec3 sDpSmooth;     // the walk's displacement averaged over the last few frames (see kMbMoveSmoothing)
    static bool sDpFresh;      // false until sDpSmooth holds a first value (nothing to average with yet)
    static double mbExposure(const MbSettings& cfg);
    static void mbSnapshot(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg, GpuTexture& tex);
    struct BlurFrame;
    class MotionBlurPass;
    class MbUnderActors;
    class MbAfterActors;
};
