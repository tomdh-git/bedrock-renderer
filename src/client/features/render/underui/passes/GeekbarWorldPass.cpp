#include "client/features/render/underui/UnderGpuPrivate.h"
#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/geekbar/GeekbarFeed.h"
#include "client/features/render/geekbar/GeekbarVolume.h"
#include "client/features/render/chams/Renderer.h"
#include "sdk/csgo/materialsystem/shaderapidx11/EnvLight.h"

// The smoke is one density field, not a pile of sprites: the simulation's wisps are splatted into a 3D grid (GeekbarVolume::copyTo), the grid is uploaded to a 3D
// texture and a quarter-resolution pixel shader marches it (the density eroded by noise that belongs to the world and not to any wisp, lit by the sun through the
// cloud itself), against the scene's depth; the small picture is then blended over the game's target.
struct GeekbarVolumeGpu {
    static inline ID3D12RootSignature* marchRoot = nullptr;
    static inline ID3D12RootSignature* compRoot = nullptr;
    static inline ID3D12DescriptorHeap* heap = nullptr;
    static inline UINT step = 0;
    static inline UINT frame = 0;
    static inline UINT uploads = 0, uploaded = ~0u; // grids sent, and the version of the one in the texture
    static inline ID3D12PipelineState* marchPso = nullptr;
    static inline ID3D12PipelineState* compPso = nullptr;
    static inline DXGI_FORMAT compFormat = DXGI_FORMAT_UNKNOWN;
    static inline GpuPtr<ID3D12Resource> volume;  // the 3D texture
    static inline GpuPtr<ID3D12Resource> upload;  // kRing slots of the grid, each a placed footprint of the texture
    static inline uint8_t* mapped = nullptr;
    static inline GpuTexture low;                 // the quarter-resolution picture of the march
    static constexpr UINT kFrames = 32;
    static constexpr UINT kRing = 16;
    static constexpr UINT kN = GeekbarVolume::kN;
    static constexpr UINT kRowPitch = 256;        // D3D12_TEXTURE_DATA_PITCH_ALIGNMENT: a row is kN * 2 = 128 bytes
    static constexpr UINT kSlicePitch = kRowPitch * kN;
    static constexpr UINT64 kSlot = static_cast<UINT64>(kSlicePitch) * kN; // 1 MB: a multiple of 512, as a placed footprint needs
    static constexpr UINT kMarchConstants = 48;
    static constexpr UINT kCompConstants = 4;
    static constexpr UINT kDivide = 4;            // the march is drawn at 1/kDivide of the picture each way

    static UnderShaderDef resolveBlur();
    static UnderShaderDef resolve(const std::string& name) {
        if (name == "geekbar:blur")
            return resolveBlur();
        UnderShaderDef d;
        d.vsName = d.psName = name == "geekbar:vol" ? "geekbar_vol" : "geekbar_volcomp";
        d.vsSource = R"(
struct V { float4 p : SV_Position; };
V VS(uint id : SV_VertexID) {
    V o;
    float2 uv = float2((id << 1) & 2, id & 2);
    o.p = float4(uv * float2(2, -2) + float2(-1, 1), 0, 1);
    return o;
})";
        if (name == "geekbar:volcomp") {
            d.root = compRoot;
            d.blend = true;
            d.psSource = R"(
cbuffer C : register(b0) { float4 k; }   // k.xy: the size of the picture
Texture2D<float4> march : register(t0);
SamplerState smp : register(s0);
float4 PS(float4 p : SV_Position) : SV_Target {
    // The march is premultiplied (light already scaled by how much of the view the smoke covers) and is smoothed up by the sampler; the blend wants it straight.
    float4 v = march.SampleLevel(smp, p.xy / k.xy, 0);
    return float4(min(v.rgb / max(v.a, 0.004), 1.25), v.a);
})";
            return d;
        }
        d.root = marchRoot;
        d.psSource = R"(
cbuffer C : register(b0) {
    float4 camPos;   // xyz, the near plane
    float4 camRight; // xyz, the screen scale in x
    float4 camUp;    // xyz, the screen scale in y
    float4 camFwd;   // xyz, the far plane
    float4 boxMin;   // the box the cloud fills (world), w: 1 when the game's depth is reversed
    float4 boxMax;   // w: seconds
    float4 vol;      // the grid's corner (world), w: its size
    float4 sunDir;   // toward the sun (world), w: how much of it reaches the cloud
    float4 sunCol;   // rgb of the sun, w: the ambient light of the place
    float4 size;     // the march's picture, then the whole picture
    float4 tune;     // x: opacity per metre of full density, y: steps, z: the divide
    float4 jet;      // the way the breath was blown
};
Texture2D<float> sceneDepth : register(t0);
Texture3D<float2> volTex : register(t1);
SamplerState lin : register(s0);

float linearDepth(float z) {
    float n = camPos.w, f = camFwd.w;
    if (boxMin.w > 0.5) z = 1.0 - z;
    return z >= 0.99999 ? 4096.0 : n * f / (f - z * (f - n));
}
float hash13(float3 p) {
    p = frac(p * 0.1031);
    p += dot(p, p.zyx + 31.32);
    return frac((p.x + p.y) * p.z);
}
float vn3(float3 x) {
    float3 i = floor(x), f = frac(x);
    f = f * f * (3.0 - 2.0 * f);
    float a = lerp(lerp(hash13(i), hash13(i + float3(1, 0, 0)), f.x), lerp(hash13(i + float3(0, 1, 0)), hash13(i + float3(1, 1, 0)), f.x), f.y);
    float b = lerp(lerp(hash13(i + float3(0, 0, 1)), hash13(i + float3(1, 0, 1)), f.x), lerp(hash13(i + float3(0, 1, 1)), hash13(i + float3(1, 1, 1)), f.x), f.y);
    return lerp(a, b, f.z);
}
float4 PS(float4 p : SV_Position) : SV_Target {
    float2 uv = p.xy / size.xy;
    float3 dir = camFwd.xyz + camRight.xyz * ((uv.x * 2.0 - 1.0) / camRight.w) + camUp.xyz * ((1.0 - 2.0 * uv.y) / camUp.w); // z of it is 1: t is the distance in front of the camera
    // The scene's depth, the nearest of the corners of this pixel's block: the smoke never covers something nearer, even at the edge of an object (a little may be
    // missing there instead).
    int2 base = int2(p.xy - 0.5) * (int)tune.z;
    int2 hi = int2(size.zw) - 1;
    int2 reach = (int)tune.z - 1;
    float sceneZ = min(min(linearDepth(sceneDepth.Load(int3(min(base, hi), 0))), linearDepth(sceneDepth.Load(int3(min(base + int2(reach.x, 0), hi), 0)))),
                       min(linearDepth(sceneDepth.Load(int3(min(base + int2(0, reach.y), hi), 0))), linearDepth(sceneDepth.Load(int3(min(base + reach, hi), 0)))));
    float3 d = dir;
    d = float3(abs(d.x) < 1e-5 ? 1e-5 : d.x, abs(d.y) < 1e-5 ? 1e-5 : d.y, abs(d.z) < 1e-5 ? 1e-5 : d.z);
    float3 inv = 1.0 / d;
    float3 t0 = (boxMin.xyz - camPos.xyz) * inv, t1 = (boxMax.xyz - camPos.xyz) * inv;
    float3 tlo = min(t0, t1), thi = max(t0, t1);
    float tN = max(max(tlo.x, tlo.y), max(tlo.z, camPos.w));
    float tF = min(min(thi.x, thi.y), min(thi.z, sceneZ));
    if (tF <= tN)
        return float4(0, 0, 0, 0);
    float steps = tune.y;
    float dt = (tF - tN) / steps;
    float ds = dt * length(dir);
    float t = tN + dt * 0.5;
    float3 ndir = normalize(dir);
    float cosT = dot(ndir, sunDir.xyz);      // toward the sun: forward scattering
    float pf = (1.0 - 0.3025) / pow(1.0 + 0.3025 - 1.1 * cosT, 1.5);
    float phase = lerp(1.0, pf, 0.2);
    float time = boxMax.w;
    float3 colour = 0;
    float trans = 1.0;
    [loop] for (int i = 0; i < (int)steps; ++i) {
        float3 wp = camPos.xyz + dir * t;
        float3 uvw = (wp - vol.xyz) / vol.w;
        float2 v = volTex.SampleLevel(lin, uvw, 0);
        if (v.x > 0.015) {
            float dens = v.x * 2.0;
            float young = saturate(v.y / max(v.x, 0.008));
            // The smoke is the smooth density looked up through a warped position (two scales of vector noise fixed in the world and stretched along the breath while the
            // vapour is fresh), so the soft blobs are sheared and curled into tendrils and sheets. Thin strands (the ridges of a noise, raised to a power) are laid in the
            // warped density, and a little of the body is kept under them; fresh vapour is warped less and has more body, old vapour is mostly strands.
            float S = 1.0 + 0.8 * young;
            float3 drift = float3(0.0, -time * 0.05, 0.0) + time * float3(0.05, 0.02, 0.04);
            float3 q1 = wp * 4.0 + drift * 4.0, q2 = wp * 11.0 + drift * 8.0, q3 = wp * 24.0 + drift * 10.0;
            q1 -= jet.xyz * (dot(q1, jet.xyz) * (1.0 - 1.0 / S));
            q2 -= jet.xyz * (dot(q2, jet.xyz) * (1.0 - 1.0 / S));
            q3 -= jet.xyz * (dot(q3, jet.xyz) * (1.0 - 1.0 / S));
            float3 v1 = float3(vn3(q1), vn3(q1 + 17.3), vn3(q1 + 41.1)) - 0.5;
            float3 v2 = float3(vn3(q2), vn3(q2 + 17.3), vn3(q2 + 41.1)) - 0.5;
            float3 wpw = wp + v1 * (0.2 * (1.0 - 0.45 * young)) + v2 * (0.08 * (1.0 - 0.3 * young));
            float dens2 = volTex.SampleLevel(lin, (wpw - vol.xyz) / vol.w, 0).x * 2.0;
            float n = vn3(q3);
            float lo = lerp(0.1, 0.03, young);
            float soft = smoothstep(lo, lo + 0.5, dens2);
            float3 qs = wpw * 10.0 + drift * 6.0;
            qs -= jet.xyz * (dot(qs, jet.xyz) * (1.0 - 1.0 / S));
            float sa = 1.0 - abs(2.0 * vn3(qs) - 1.0), sb = 1.0 - abs(2.0 * vn3(qs * 1.7 + 9.1) - 1.0);
            float strands = pow(sa, 5.0) * 0.9 + pow(sa * sb, 3.0) * 0.8;
            float env = saturate(dens2 * 1.2);
            float e = saturate(soft * lerp(0.1, 0.3, young) * (0.7 + 0.6 * n) + strands * env);
            float sigma = e * tune.x * (1.0 + 0.6 * young) * smoothstep(0.1, 0.7, t); // smoke right at the camera thins out instead of filling the screen
            if (sigma > 0.002) {
                // The sun through the rest of the cloud: three taps toward it.
                float3 toSun = sunDir.xyz / vol.w;
                float s1 = volTex.SampleLevel(lin, uvw + toSun * 0.12, 0).x, s2 = volTex.SampleLevel(lin, uvw + toSun * 0.30, 0).x, s3 = volTex.SampleLevel(lin, uvw + toSun * 0.60, 0).x;
                float shadow = exp(-(s1 * 0.12 + s2 * 0.18 + s3 * 0.30) * 2.0 * 9.0);
                float3 lit = (sunCol.w * float3(0.9, 0.95, 1.0) + sunCol.rgb * sunDir.w * (0.35 + 0.65 * shadow) * phase) * 1.15; // vapour scatters strongly: it is white, and a shaded part is only grey
                float3 albedo = lerp(float3(0.90, 0.92, 0.96), float3(1.0, 1.0, 1.0), saturate(n * 1.5));
                float a = 1.0 - exp(-sigma * ds);
                colour += trans * a * albedo * lit;
                trans *= 1.0 - a;
                if (trans < 0.03)
                    break;
            }
        }
        t += dt;
    }
    return float4(colour, 1.0 - trans);
})";
        return d;
    }

    static void init() {
        if (marchRoot)
            return;
        D3D12_STATIC_SAMPLER_DESC ss = D3D12Util::linearSampler();
        {
            D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 2, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
            D3D12_ROOT_PARAMETER params[2]{};
            params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
            params[0].Constants = {0, 0, kMarchConstants};
            params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
            params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
            params[1].DescriptorTable = {1, &range};
            params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
            D3D12_ROOT_SIGNATURE_DESC desc{2, params, 1, &ss, D3D12_ROOT_SIGNATURE_FLAG_NONE};
            marchRoot = D3D12Util::createRootSignature(UnderGpu::dev, desc);
        }
        {
            D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
            D3D12_ROOT_PARAMETER params[2]{};
            params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
            params[0].Constants = {0, 0, kCompConstants};
            params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
            params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
            params[1].DescriptorTable = {1, &range};
            params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
            D3D12_ROOT_SIGNATURE_DESC desc{2, params, 1, &ss, D3D12_ROOT_SIGNATURE_FLAG_NONE};
            compRoot = D3D12Util::createRootSignature(UnderGpu::dev, desc);
        }
        heap = GpuUtil::createDescriptorHeap(UnderGpu::dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kFrames * 3, true);
        step = UnderGpu::dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        const D3D12_RESOURCE_DESC vd{D3D12_RESOURCE_DIMENSION_TEXTURE3D, 0, kN, kN, kN, 1, DXGI_FORMAT_R8G8_UNORM, {1, 0}, D3D12_TEXTURE_LAYOUT_UNKNOWN, D3D12_RESOURCE_FLAG_NONE};
        volume = GpuUtil::createResource(UnderGpu::dev, D3D12_HEAP_TYPE_DEFAULT, vd, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        upload = GpuUtil::createBuffer(UnderGpu::dev, kSlot * kRing);
        BS_CHECK_HR(upload->Map(0, nullptr, reinterpret_cast<void**>(&mapped)));
    }
};

// The blur of the view while the device is drawn on: a copy of the finished scene is read by a wide disc of taps and the result written back over it (the hand, the
// device and the interface are drawn after this layer and stay sharp).
struct GeekbarBlurGpu {
    static inline ID3D12RootSignature* root = nullptr;
    static inline ID3D12DescriptorHeap* heap = nullptr;
    static inline UINT step = 0;
    static inline UINT slot = 0;
    static inline ID3D12PipelineState* pso = nullptr;
    static inline DXGI_FORMAT psoFormat = DXGI_FORMAT_UNKNOWN;
    static inline GpuTexture copy;
    static constexpr UINT kRing = 16;
    static constexpr UINT kConstants = 4;

    static void init() {
        if (root)
            return;
        D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
        D3D12_ROOT_PARAMETER params[2]{};
        params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
        params[0].Constants = {0, 0, kConstants};
        params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
        params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        params[1].DescriptorTable = {1, &range};
        params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
        D3D12_STATIC_SAMPLER_DESC ss = D3D12Util::linearSampler();
        D3D12_ROOT_SIGNATURE_DESC desc{2, params, 1, &ss, D3D12_ROOT_SIGNATURE_FLAG_NONE};
        root = D3D12Util::createRootSignature(UnderGpu::dev, desc);
        heap = GpuUtil::createDescriptorHeap(UnderGpu::dev, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kRing, true);
        step = UnderGpu::dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    }
};

UnderShaderDef GeekbarVolumeGpu::resolveBlur() {
    UnderShaderDef d;
    d.root = GeekbarBlurGpu::root;
    d.vsName = "geekbar_blur";
    d.psName = "geekbar_blur";
    d.vsSource = R"(
struct V { float4 p : SV_Position; };
V VS(uint id : SV_VertexID) {
    V o;
    float2 uv = float2((id << 1) & 2, id & 2);
    o.p = float4(uv * float2(2, -2) + float2(-1, 1), 0, 1);
    return o;
})";
    d.psSource = R"(
cbuffer C : register(b0) { float4 k; };   // k.x: radius in pixels, k.y/k.z: the size of the picture
Texture2D<float4> scene : register(t0);
SamplerState smp : register(s0);
float4 PS(float4 p : SV_Position) : SV_Target {
    float2 uv = p.xy / k.yz;
    float2 px = 1.0 / k.yz;
    float4 acc = scene.SampleLevel(smp, uv, 0);
    float total = 1.0;
    // A disc of taps on a golden-angle spiral: even, with no streaks, and the same cost whatever the radius.
    [unroll] for (int i = 0; i < 40; ++i) {
        float r = sqrt((i + 0.5) / 40.0) * k.x;
        float a = i * 2.39996323;
        float w = 1.0 - 0.5 * (r / max(k.x, 1.0));
        acc += scene.SampleLevel(smp, uv + float2(cos(a), sin(a)) * r * px, 0) * w;
        total += w;
    }
    return acc / total;
})";
    return d;
}

class GeekbarBlurPass final : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::PostScene; }
    const char* name() const override { return "Geekbar hold blur"; }
    bool wanted() override { return GeekbarFeed::blurAmount.load(std::memory_order_acquire) > 0.01f; }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        const float amount = GeekbarFeed::blurAmount.load(std::memory_order_acquire);
        if (amount <= 0.01f || !tg.rt)
            return;
        UnderGpu::ensure(q);
        auto* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
        const D3D12_RESOURCE_DESC rd = rt->GetDesc();
        if (rd.SampleDesc.Count != 1)
            return;
        GeekbarBlurGpu::init();
        if (!GeekbarBlurGpu::pso || GeekbarBlurGpu::psoFormat != rd.Format) {
            GeekbarBlurGpu::pso = UnderGpu::pipeline("geekbar:blur", rd.Format, 1, DXGI_FORMAT_UNKNOWN);
            GeekbarBlurGpu::psoFormat = rd.Format;
        }
        if (!GeekbarBlurGpu::pso)
            return;
        if (!GeekbarBlurGpu::copy.matches(static_cast<UINT>(rd.Width), rd.Height, rd.Format)) {
            UnderGpu::waitIdle();
            GeekbarBlurGpu::copy.create(UnderGpu::dev, static_cast<UINT>(rd.Width), rd.Height, rd.Format, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        }
        constexpr UINT kSrv = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, kRtv = D3D12_RESOURCE_STATE_RENDER_TARGET;
        const auto found = UnderGpu::state.find(tg.rt);
        const UINT have = found == UnderGpu::state.end() ? kRtv : found->second;
        const bool toSource = !(have & D3D12_RESOURCE_STATE_COPY_SOURCE);
        const UINT now = toSource ? D3D12_RESOURCE_STATE_COPY_SOURCE : have;
        ID3D12Resource* copy = GeekbarBlurGpu::copy.res;
        UnderGpu::beginList(GeekbarBlurGpu::pso);
        D3D12_RESOURCE_BARRIER pre[2];
        UINT nPre = 0;
        if (toSource)
            pre[nPre++] = UnderGpu::transition(rt, have, D3D12_RESOURCE_STATE_COPY_SOURCE);
        pre[nPre++] = UnderGpu::transition(copy, kSrv, D3D12_RESOURCE_STATE_COPY_DEST);
        UnderGpu::list->ResourceBarrier(nPre, pre);
        UnderGpu::list->CopyResource(copy, rt);
        const D3D12_RESOURCE_BARRIER mid[2] = {UnderGpu::transition(copy, D3D12_RESOURCE_STATE_COPY_DEST, kSrv), UnderGpu::transition(rt, now, kRtv)};
        UnderGpu::list->ResourceBarrier(2, mid);
        ID3D12DescriptorHeap* heaps[] = {GeekbarBlurGpu::heap};
        UnderGpu::list->SetDescriptorHeaps(1, heaps);
        UnderGpu::list->SetGraphicsRootSignature(GeekbarBlurGpu::root);
        const UINT at = GeekbarBlurGpu::slot++ % GeekbarBlurGpu::kRing;
        D3D12_CPU_DESCRIPTOR_HANDLE cpu = GeekbarBlurGpu::heap->GetCPUDescriptorHandleForHeapStart();
        cpu.ptr += static_cast<SIZE_T>(at) * GeekbarBlurGpu::step;
        UnderGpu::dev->CreateShaderResourceView(copy, nullptr, cpu);
        D3D12_GPU_DESCRIPTOR_HANDLE gpu = GeekbarBlurGpu::heap->GetGPUDescriptorHandleForHeapStart();
        gpu.ptr += static_cast<UINT64>(at) * GeekbarBlurGpu::step;
        const float width = static_cast<float>(rd.Width), height = static_cast<float>(rd.Height);
        const float c[GeekbarBlurGpu::kConstants] = {amount * height * 0.022f, width, height, 0.f};
        UnderGpu::list->SetGraphicsRoot32BitConstants(0, GeekbarBlurGpu::kConstants, c, 0);
        UnderGpu::list->SetGraphicsRootDescriptorTable(1, gpu);
        UnderGpu::list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        const D3D12_CPU_DESCRIPTOR_HANDLE rtv = UnderGpu::rtvFor(rt);
        UnderGpu::list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
        const D3D12_VIEWPORT vp{0, 0, width, height, 0, 1};
        const D3D12_RECT sr{0, 0, static_cast<LONG>(rd.Width), static_cast<LONG>(rd.Height)};
        UnderGpu::list->RSSetViewports(1, &vp);
        UnderGpu::list->RSSetScissorRects(1, &sr);
        UnderGpu::list->DrawInstanced(3, 1, 0, 0);
        if (have != kRtv) {
            const D3D12_RESOURCE_BARRIER post = UnderGpu::transition(rt, kRtv, have);
            UnderGpu::list->ResourceBarrier(1, &post);
        }
        UnderGpu::submit(q, run);
    }
    void shutdown() override {
        UnderGpu::waitIdle();
        GeekbarBlurGpu::copy.reset();
        UnderGpu::release(GeekbarBlurGpu::pso);
        UnderGpu::release(GeekbarBlurGpu::root);
        UnderGpu::release(GeekbarBlurGpu::heap);
        GeekbarBlurGpu::psoFormat = DXGI_FORMAT_UNKNOWN;
        GeekbarBlurGpu::step = 0;
    }
};

class GeekbarWorldPass final : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::PostScene; }
    const char* name() const override { return "depth-tested Geekbar smoke"; }
    // The smoke stays in the air whether or not the device is out (the module clears it when it is switched off).
    bool wanted() override { return GeekbarFeed::smokeCount() != 0; }
    bool tracking() const override { return GeekbarFeed::smokeCount() != 0; }
    bool needsProjection() const override { return true; }
    bool needsDepth() const override { return true; }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override {
        using G = GeekbarVolumeGpu;
        if (GeekbarFeed::smokeCount() == 0 || !tg.rt || !tg.depth || UnderGpu::nearPlane.load() <= 0.f || UnderGpu::farPlane.load() <= UnderGpu::nearPlane.load())
            return;
        const UnderCamera cam = UnderGpu::camera();
        if (!cam.valid)
            return;
        G::init();
        auto* rt = reinterpret_cast<ID3D12Resource*>(tg.rt);
        const D3D12_RESOURCE_DESC rd = rt->GetDesc();
        if (rd.SampleDesc.Count != 1)
            return;
        if (!G::marchPso)
            G::marchPso = UnderGpu::pipeline("geekbar:vol", DXGI_FORMAT_R8G8B8A8_UNORM, 1, DXGI_FORMAT_UNKNOWN);
        if (!G::compPso || G::compFormat != rd.Format) {
            G::compPso = UnderGpu::pipeline("geekbar:volcomp", rd.Format, 1, DXGI_FORMAT_UNKNOWN);
            G::compFormat = rd.Format;
        }
        if (!G::marchPso || !G::compPso)
            return;
        UnderGpu::ReadableDepth depth;
        if (!UnderGpu::readableDepth(reinterpret_cast<ID3D12Resource*>(tg.depth), depth))
            return;
        // The grid, into this frame's slot of the upload buffer.
        GeekbarVolume::Info info;
        if (!GeekbarVolume::info(info))
            return;
        const bool upload = info.version != G::uploaded; // the texture keeps the grid: it is sent only when the simulation made a new one
        const UINT ring = G::uploads % G::kRing;
        if (upload) {
            if (!GeekbarVolume::copyTo(G::mapped + static_cast<size_t>(ring) * G::kSlot, G::kRowPitch, G::kSlicePitch, info))
                return;
            G::uploaded = info.version;
            ++G::uploads;
        }
        const UINT width = static_cast<UINT>(rd.Width), height = rd.Height;
        const UINT lowW = (width + G::kDivide - 1) / G::kDivide, lowH = (height + G::kDivide - 1) / G::kDivide;
        if (!G::low.matches(lowW, lowH, DXGI_FORMAT_R8G8B8A8_UNORM)) {
            UnderGpu::waitIdle();
            const D3D12_CLEAR_VALUE clear{DXGI_FORMAT_R8G8B8A8_UNORM, {0.f, 0.f, 0.f, 0.f}};
            G::low.create(UnderGpu::dev, lowW, lowH, DXGI_FORMAT_R8G8B8A8_UNORM, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &clear);
        }
        constexpr UINT kSrv = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, kRtv = D3D12_RESOURCE_STATE_RENDER_TARGET, kCopy = D3D12_RESOURCE_STATE_COPY_DEST;
        UnderGpu::beginList(G::marchPso);
        UnderGpu::recordDepthCopy(depth);
        // The grid up to the texture.
        if (upload) {
        const D3D12_RESOURCE_BARRIER toCopy = UnderGpu::transition(G::volume, kSrv, kCopy);
        UnderGpu::list->ResourceBarrier(1, &toCopy);
        D3D12_TEXTURE_COPY_LOCATION dstLoc{}, srcLoc{};
        dstLoc.pResource = G::volume;
        dstLoc.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        srcLoc.pResource = G::upload;
        srcLoc.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        srcLoc.PlacedFootprint.Offset = static_cast<UINT64>(ring) * G::kSlot;
        srcLoc.PlacedFootprint.Footprint = {DXGI_FORMAT_R8G8_UNORM, G::kN, G::kN, G::kN, G::kRowPitch};
        UnderGpu::list->CopyTextureRegion(&dstLoc, 0, 0, 0, &srcLoc, nullptr);
        const D3D12_RESOURCE_BARRIER fromCopy = UnderGpu::transition(G::volume, kCopy, kSrv);
        UnderGpu::list->ResourceBarrier(1, &fromCopy);
        }
        // This frame's three descriptors: the scene's depth, the grid, the march's picture.
        const UINT slot = (G::frame++ % G::kFrames) * 3;
        D3D12_SHADER_RESOURCE_VIEW_DESC sd{};
        sd.Format = depth.view;
        sd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        sd.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        sd.Texture2D.MipLevels = 1;
        UnderGpu::dev->CreateShaderResourceView(depth.res, &sd, GpuUtil::cpuAt(G::heap, slot, G::step));
        UnderGpu::dev->CreateShaderResourceView(G::volume, nullptr, GpuUtil::cpuAt(G::heap, slot + 1, G::step));
        UnderGpu::dev->CreateShaderResourceView(G::low.res, nullptr, GpuUtil::cpuAt(G::heap, slot + 2, G::step));
        ID3D12DescriptorHeap* heaps[] = {G::heap};
        UnderGpu::list->SetDescriptorHeaps(1, heaps);
        UnderGpu::list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        // The light of the world: the sun by day (warm low on the horizon), the moon at night (dim and blue); the ambient from how bright the player's place is (caves and
        // night are dark, torches and daylight bright).
        float sunWorld[3];
        EnvLight::sunDirectionWorld(sunWorld);
        const float elevation = EnvLight::sunElevation();
        const float day = std::clamp((elevation + 0.1f) / 0.35f, 0.f, 1.f);
        const float horizon = 1.f - std::clamp(std::fabs(elevation) / 0.35f, 0.f, 1.f);
        const float sunK = (0.25f + 0.75f * day) * 0.9f;
        const float sunColor[3] = {(0.55f + 0.45f * day) * (1.f + 0.1f * horizon), (0.62f + 0.34f * day) * (1.f - 0.18f * horizon), (0.95f - 0.05f * day) * (1.f - 0.45f * horizon * day)};
        const float ambient = 0.30f + 0.55f * EnvLight::brightness();
        const float reversed = ChamsRenderer::reversedDepth() ? 1.f : 0.f;
        const float c[G::kMarchConstants] = {cam.pos[0], cam.pos[1], cam.pos[2], UnderGpu::nearPlane.load(),
                                             cam.right[0], cam.right[1], cam.right[2], cam.fov[0],
                                             cam.up[0], cam.up[1], cam.up[2], cam.fov[1],
                                             cam.fwd[0], cam.fwd[1], cam.fwd[2], UnderGpu::farPlane.load(),
                                             info.boxMin.x, info.boxMin.y, info.boxMin.z, reversed,
                                             info.boxMax.x, info.boxMax.y, info.boxMax.z, static_cast<float>(std::fmod(Platform::Time::seconds(), 1000.0)),
                                             info.origin.x, info.origin.y, info.origin.z, info.span,
                                             sunWorld[0], sunWorld[1], sunWorld[2], sunK * info.sky,
                                             sunColor[0], sunColor[1], sunColor[2], ambient,
                                             static_cast<float>(lowW), static_cast<float>(lowH), static_cast<float>(width), static_cast<float>(height),
                                             8.f, 36.f, static_cast<float>(G::kDivide), 0.f,
                                             info.jet.x, info.jet.y, info.jet.z, 0.f};
        // The march, into the small picture.
        const D3D12_RESOURCE_BARRIER toRt = UnderGpu::transition(G::low.res, kSrv, kRtv);
        UnderGpu::list->ResourceBarrier(1, &toRt);
        UnderGpu::list->SetGraphicsRootSignature(G::marchRoot);
        UnderGpu::list->SetGraphicsRoot32BitConstants(0, G::kMarchConstants, c, 0);
        UnderGpu::list->SetGraphicsRootDescriptorTable(1, GpuUtil::gpuAt(G::heap, slot, G::step));
        const D3D12_CPU_DESCRIPTOR_HANDLE lowRtv = UnderGpu::rtvFor(G::low.res);
        UnderGpu::list->OMSetRenderTargets(1, &lowRtv, FALSE, nullptr);
        const float none[4] = {0.f, 0.f, 0.f, 0.f};
        UnderGpu::list->ClearRenderTargetView(lowRtv, none, 0, nullptr);
        const D3D12_VIEWPORT lowVp{0, 0, static_cast<float>(lowW), static_cast<float>(lowH), 0, 1};
        const D3D12_RECT lowSr{0, 0, static_cast<LONG>(lowW), static_cast<LONG>(lowH)};
        UnderGpu::list->RSSetViewports(1, &lowVp);
        UnderGpu::list->RSSetScissorRects(1, &lowSr);
        UnderGpu::list->DrawInstanced(3, 1, 0, 0);
        const D3D12_RESOURCE_BARRIER toSrv = UnderGpu::transition(G::low.res, kRtv, kSrv);
        UnderGpu::list->ResourceBarrier(1, &toSrv);
        // The picture over the game's target (its view is made after the small one's: they share a slot of the view heap).
        UnderGpu::Bound b = UnderGpu::prepareTarget(UnderTarget{tg.rt, 0, 0});
        UnderGpu::list->SetPipelineState(G::compPso);
        UnderGpu::list->SetGraphicsRootSignature(G::compRoot);
        if (!b.before.empty())
            UnderGpu::list->ResourceBarrier(static_cast<UINT>(b.before.size()), b.before.data());
        UnderGpu::bindAndSize(b);
        const float cc[G::kCompConstants] = {static_cast<float>(width), static_cast<float>(height), 0.f, 0.f};
        UnderGpu::list->SetGraphicsRoot32BitConstants(0, G::kCompConstants, cc, 0);
        UnderGpu::list->SetGraphicsRootDescriptorTable(1, GpuUtil::gpuAt(G::heap, slot + 2, G::step));
        UnderGpu::list->DrawInstanced(3, 1, 0, 0);
        if (!b.after.empty())
            UnderGpu::list->ResourceBarrier(static_cast<UINT>(b.after.size()), b.after.data());
        UnderGpu::submit(q, run);
    }
    void shutdown() override {
        using G = GeekbarVolumeGpu;
        UnderGpu::waitIdle();
        if (G::upload && G::mapped)
            G::upload->Unmap(0, nullptr);
        G::mapped = nullptr;
        G::upload.reset();
        G::volume.reset();
        G::low.reset();
        G::marchPso = nullptr; // the builder owns the pipelines
        G::compPso = nullptr;
        UnderGpu::release(G::marchRoot);
        UnderGpu::release(G::compRoot);
        UnderGpu::release(G::heap);
        G::compFormat = DXGI_FORMAT_UNKNOWN;
        G::step = 0;
        G::frame = 0;
        G::uploads = 0;
        G::uploaded = ~0u;
    }
};

void GeekbarWorldPasses::install() {
    UnderGpu::addShaders("geekbar:", &GeekbarVolumeGpu::resolve);
    static GeekbarBlurPass blur; // before the smoke: the smoke is not blurred
    Render::UnderUI::add(&blur);
    static GeekbarWorldPass pass;
    Render::UnderUI::add(&pass);
}
