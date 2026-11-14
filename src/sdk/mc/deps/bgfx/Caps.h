#pragma once


namespace bgfx {

// bgfx::Caps of 1.26.62.01: globals in .data (rva), read by the caps dump at 0x660ecd0 (strings "homogenousDepth", "maxDrawCalls", ...). Values are from a live read on an AMD 760M iGPU.
struct CapsGlobals {
    static constexpr uintptr_t kSupported = 0x12adfa50;       // u64 flag bits, see CapsFlag
    static constexpr uintptr_t kHomogeneousDepth = 0x12adfc88; // u8 (0)
    static constexpr uintptr_t kOriginBottomLeft = 0x12adfc89; // u8 (0)
    static constexpr uintptr_t kNumGpus = 0x12adfc8a;          // u8 (2)
    static constexpr uintptr_t kFpEpsilon = 0x12adfc94;        // float (1e-5)
    static constexpr uintptr_t kLimits = 0x12ae0d58;           // u32[27], order of CapsLimit
};

enum class CapsLimit : unsigned { // live: 65535 1024 16384 2048 256 128 8 2048 4096 65535 65 0 64 4 0xFFFFFFFF 4096 4096 4096 4096 512 256 10 6291456 2097152 32768 32768 1024
    MaxDrawCalls, MaxBlits, MaxTextureSize, MaxTextureLayers, MaxViews, MaxFrameBuffers, MaxFbAttachments, MaxPrograms, MaxShaders, MaxTextures, MaxTextureSamplers, MaxComputeBindings,
    MaxVertexDecls, MaxVertexStreams, MaxVertexCount, MaxIndexBuffers, MaxVertexBuffers, MaxDynamicIndexBuffers, MaxDynamicVertexBuffers, MaxUniforms, MaxOcclusionQueries, MaxEncoders,
    TransientVbSize, TransientIbSize, MaxAccelerationStructures, AvgAccelerationStructureSize, MaxComputeWorkGroupInvocations,
};

// Bit positions in the supported word. 0x100000000 and above are Mojang's additions to bgfx.
enum class CapsFlag : unsigned {
    AlphaToCoverage = 0,
    BlendIndependent = 1,
    Compute = 2,
    ConservativeRaster = 3,
    DrawIndirect = 4,
    FragmentDepth = 5,
    FragmentOrdering = 6,
    GraphicsDebugger = 7,
    HiDPI = 8,
    Index32 = 10,
    Instancing = 11,
    OcclusionQuery = 12,
    RendererMultithreaded = 13,
    SwapChain = 14,
    Texture2DArray = 15,
    Texture3D = 16,
    TextureBlit = 17,
    TextureCompareLequal = 19,
    TextureCubeArray = 20,
    TextureDirectAccess = 21,
    TextureReadBack = 22,
    VertexAttribHalf = 23,
    VertexAttribUint10 = 24,
    VertexId = 25,
    HDR10 = 26,
    StructuredBuffers = 27,
    VertexAttribSint8 = 28,
    VertexAttribUint16 = 29,
    DepthBias = 30,
    RayTracing = 31,
    Upscaling = 32,
    NoFragmentShader = 33,
    BufferBindOffset = 34,
    RangedResource = 35,
    DynamicTextureHandles = 36,
    GpuTimer = 37,
};

} // namespace bgfx
