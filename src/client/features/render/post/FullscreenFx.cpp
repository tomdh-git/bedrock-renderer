#include "client/features/render/post/FullscreenFx.h"
#include "client/features/render/backend/D3D12Util.h"

const char* FullscreenFx::kVS = R"(
struct VSOut { float4 pos : SV_Position; float2 uv : TEXCOORD0; };
VSOut main(uint id : SV_VertexID) {
    VSOut o;
    float2 p = float2((id << 1) & 2, id & 2);
    o.pos = float4(p * float2(2.0, -2.0) + float2(-1.0, 1.0), 0.0, 1.0);
    o.uv = p;
    return o;
})";

// Dual filter (Bjorge): a centre tap and the four diagonals, every tap already a bilinear mix of four texels.
const char* FullscreenFx::kGlowDown = R"(
cbuffer C : register(b0) { float2 texel; float gain; float pad; };
Texture2D src : register(t0);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float4 c = src.Sample(lin, uv) * 4.0;
    c += src.Sample(lin, uv + float2(-texel.x, -texel.y));
    c += src.Sample(lin, uv + float2( texel.x, -texel.y));
    c += src.Sample(lin, uv + float2(-texel.x,  texel.y));
    c += src.Sample(lin, uv + float2( texel.x,  texel.y));
    return c * 0.125;
})";
const char* FullscreenFx::kGlowUp = R"(
cbuffer C : register(b0) { float2 texel; float gain; float pad; };
Texture2D src : register(t0);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float2 h = texel * 0.5;
    float4 c = src.Sample(lin, uv + float2(-2.0 * h.x, 0.0));
    c += src.Sample(lin, uv + float2(-h.x,  h.y)) * 2.0;
    c += src.Sample(lin, uv + float2(0.0,  2.0 * h.y));
    c += src.Sample(lin, uv + float2( h.x,  h.y)) * 2.0;
    c += src.Sample(lin, uv + float2( 2.0 * h.x, 0.0));
    c += src.Sample(lin, uv + float2( h.x, -h.y)) * 2.0;
    c += src.Sample(lin, uv + float2(0.0, -2.0 * h.y));
    c += src.Sample(lin, uv + float2(-h.x, -h.y)) * 2.0;
    return c * (gain / 12.0);
})";

// A blurred level is a few texels across on screen: plain bilinear shows its grid as bands (the slope changes at every texel). The cubic B-spline (four
// bilinear taps) is smooth to the second derivative, and a little triangular noise keeps the 8-bit result from stepping.
const char* FullscreenFx::kSmooth = R"(
float4 SampleSmooth(Texture2D t, SamplerState s, float2 uv, float2 texel) {
    float2 size = 1.0 / texel;
    float2 p = uv * size - 0.5;
    float2 f = frac(p);
    float2 c = floor(p) + 0.5;
    float2 f2 = f * f, f3 = f2 * f;
    float2 w0 = (1.0 - f) * (1.0 - f) * (1.0 - f) / 6.0;
    float2 w1 = (3.0 * f3 - 6.0 * f2 + 4.0) / 6.0;
    float2 w2 = (-3.0 * f3 + 3.0 * f2 + 3.0 * f + 1.0) / 6.0;
    float2 w3 = f3 / 6.0;
    float2 g0 = w0 + w1, g1 = w2 + w3;
    float2 o0 = (c + (w1 / g0 - 1.0)) * texel;
    float2 o1 = (c + (w3 / g1 + 1.0)) * texel;
    return g0.y * (g0.x * t.SampleLevel(s, float2(o0.x, o0.y), 0) + g1.x * t.SampleLevel(s, float2(o1.x, o0.y), 0))
         + g1.y * (g0.x * t.SampleLevel(s, float2(o0.x, o1.y), 0) + g1.x * t.SampleLevel(s, float2(o1.x, o1.y), 0));
}
float Dither(float2 pos) {
    float2 q = frac(pos * float2(0.06711056, 0.00583715));
    float a = frac(52.9829189 * frac(dot(q, float2(1.0, 1.0))));
    float b = frac(a * 43758.5453 + dot(pos, float2(0.7548776, 0.5698403)));
    return (a + b - 1.0) / 255.0; // triangular, one level either way
}
)";

// The glow, composited with the picture under it in view: a dark or mid picture is lit (a screen: the hot core whitens), a bright one is tinted towards a
// deeper tone of the glow's colour (light cannot be added to white), and in between the two mix by the picture's brightness.
const char* FullscreenFx::kGlowAdaptive = R"(
cbuffer C : register(b0) { float2 texel; float gain; float pad; };
Texture2D src : register(t0);
Texture2D back : register(t1);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float3 l = max(SampleSmooth(src, lin, uv, texel).rgb, 0.0) * gain;
    float m = max(l.r, max(l.g, l.b));
    float a = 1.0 - exp(-m * 0.9);
    float3 bg = back.Load(int3(pos.xy, 0)).rgb;
    if (a < 0.002)
        return float4(bg, 1.0);
    float3 hue = l / max(m, 1e-4);
    hue = saturate(lerp(float3(dot(hue, float3(0.3, 0.59, 0.11)).xxx), hue, 1.3));
    float3 lit = 1.0 - (1.0 - bg) * (1.0 - saturate(hue * a * 0.55));
    float3 deep = lerp(bg, hue * 0.8, a * 0.32);
    float lumBg = dot(bg, float3(0.2126, 0.7152, 0.0722));
    float t = smoothstep(0.45, 0.8, lumBg);
    return float4(lerp(lit, deep, t) + Dither(pos.xy), 1.0);
})";
const char* FullscreenFx::kShadowComp = R"(
cbuffer C : register(b0) { float2 texel; float gain; float pad; };
Texture2D src : register(t0);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float a = saturate(SampleSmooth(src, lin, uv, texel).r * gain); // the shadow target holds its coverage in one channel
    return float4(0.0, 0.0, 0.0, a < 0.0005 ? 0.0 : saturate(a * 0.7 + Dither(pos.xy))); // dark only where the shadow is dense, fading out softly
})";
const char* FullscreenFx::kBlurDown = R"(
cbuffer C : register(b0) { float2 texel; float2 dir; float alpha; float radius; float2 pad; };
Texture2D src : register(t0);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float4 c = src.Sample(lin, uv + float2(-texel.x, -texel.y))
             + src.Sample(lin, uv + float2( texel.x, -texel.y))
             + src.Sample(lin, uv + float2(-texel.x,  texel.y))
             + src.Sample(lin, uv + float2( texel.x,  texel.y));
    return c * 0.25;
})";
const char* FullscreenFx::kBlur = R"(
cbuffer C : register(b0) { float2 texel; float2 dir; float alpha; float radius; float2 pad; };
Texture2D src : register(t0);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float2 d = dir * texel * radius;
    float4 c = src.Sample(lin, uv) * 0.2270270270;
    float2 o1 = d * 1.3846153846;
    float2 o2 = d * 3.2307692308;
    c += src.Sample(lin, uv + o1) * 0.3162162162;
    c += src.Sample(lin, uv - o1) * 0.3162162162;
    c += src.Sample(lin, uv + o2) * 0.0702702703;
    c += src.Sample(lin, uv - o2) * 0.0702702703;
    return c;
})";
const char* FullscreenFx::kBlurComp = R"(
cbuffer C : register(b0) { float2 texel; float2 dir; float alpha; float radius; float2 pad; };
Texture2D src : register(t0);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    return float4(src.Sample(lin, uv).rgb, alpha);
})";
// A shockwave through the picture (the boot screen's slam): the picture is pushed outward at a ring that travels out from `center` and drawn in behind it, the whole screen
// is moved by `shake`, and a coarse grid of blocks rattles where the ring is, so what the picture holds (the buttons) seems to be jolted, not only the picture.
// Distances are in units of the screen's height.
const char* FullscreenFx::kShock = R"(
cbuffer C : register(b0) { float since; float amp; float speed; float aspect; float2 shake; float full; float pad; };
Texture2D snap : register(t0);
Texture2D cover : register(t1);
SamplerState lin : register(s0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    // the wave: the impact is at the middle at `since` = 0 and it travels at `speed`; a point at distance d is moved from `since` = d / speed on, by a decaying sine, fainter
    // the further it has spread (the same energy over a longer front)
    float2 d = (uv - 0.5) * float2(aspect, 1.0);
    float dist = length(d);
    float2 dir = d / max(dist, 1e-4);
    float tau = since - dist / speed;
    float on = since > 0.0 ? smoothstep(0.0, 0.04, tau) : 0.0;
    float w = sin(37.7 * tau) * exp(-5.0 * max(tau, 0.0)) * amp * on * rsqrt(1.0 + dist * 6.0);
    float2 cell = floor(pos.xy / 64.0);
    float h = frac(sin(dot(cell, float2(12.9898, 78.233))) * 43758.5453);
    float h2 = frac(h * 91.3458);
    float2 rattle = (float2(h, h2) - 0.5) * abs(w) * 1.2; // the blocks of the picture are jolted where the wave is
    float2 st = uv - (dir * w + rattle) / float2(aspect, 1.0) + shake;
    float c = full > 0.5 ? 1.0 : cover.Sample(lin, uv).r;
    return float4(snap.Sample(lin, st).rgb, c);
})";
FullscreenFx::Pipelines FullscreenFx::f;
ID3DBlob* FullscreenFx::compileMain(const char* src, const char* name, const char* target) {
    ID3DBlob *code = nullptr, *err = nullptr;
    const HRESULT hr = D3DCompile(src, strlen(src), name, nullptr, nullptr, "main", target, D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &code, &err);
    if (FAILED(hr))
        Logger::fatal("[d3d12fx] shader {} failed: {}", name, err ? static_cast<const char*>(err->GetBufferPointer()) : "?");
    if (err)
        err->Release();
    return code;
}

// The blend state of one mode: how the shader's output meets what is already in the target.
void FullscreenFx::setBlend(D3D12_RENDER_TARGET_BLEND_DESC& rt, FullscreenFx::Blend blend) {
    rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    rt.LogicOp = D3D12_LOGIC_OP_NOOP;
    rt.BlendOp = D3D12_BLEND_OP_ADD;
    rt.BlendOpAlpha = D3D12_BLEND_OP_ADD;
    rt.SrcBlend = D3D12_BLEND_ONE;
    rt.DestBlend = D3D12_BLEND_ZERO;
    rt.SrcBlendAlpha = D3D12_BLEND_ONE;
    rt.DestBlendAlpha = D3D12_BLEND_ZERO;
    switch (blend) {
    case FullscreenFx::Opaque: break;
    case FullscreenFx::Add:
        rt.BlendEnable = TRUE;
        rt.DestBlend = D3D12_BLEND_ONE;
        rt.DestBlendAlpha = D3D12_BLEND_ONE;
        break;
    case FullscreenFx::Shade: // result = dst * (1 - a): the shadow darkens what is under it; the alpha channel is left alone
        rt.BlendEnable = TRUE;
        rt.SrcBlend = D3D12_BLEND_ZERO;
        rt.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
        rt.SrcBlendAlpha = D3D12_BLEND_ZERO;
        rt.DestBlendAlpha = D3D12_BLEND_ONE;
        rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_RED | D3D12_COLOR_WRITE_ENABLE_GREEN | D3D12_COLOR_WRITE_ENABLE_BLUE;
        break;
    case FullscreenFx::Alpha:
        rt.BlendEnable = TRUE;
        rt.SrcBlend = D3D12_BLEND_SRC_ALPHA;
        rt.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
        rt.SrcBlendAlpha = D3D12_BLEND_ONE;
        rt.DestBlendAlpha = D3D12_BLEND_ZERO;
        break;
    }
}
ID3D12PipelineState* FullscreenFx::pipeline(FullscreenFx::Shader shader, FullscreenFx::Blend blend, DXGI_FORMAT format) {
    const auto key = std::make_tuple(static_cast<int>(shader), static_cast<int>(blend), static_cast<int>(format));
    auto it = f.pso.find(key);
    if (it != f.pso.end())
        return it->second;
    D3D12_GRAPHICS_PIPELINE_STATE_DESC d{};
    d.pRootSignature = f.root;
    d.VS = {f.vs->GetBufferPointer(), f.vs->GetBufferSize()};
    d.PS = {f.ps[shader]->GetBufferPointer(), f.ps[shader]->GetBufferSize()};
    setBlend(d.BlendState.RenderTarget[0], blend);
    d.SampleMask = UINT_MAX;
    d.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    d.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    d.RasterizerState.DepthClipEnable = TRUE;
    d.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    d.NumRenderTargets = 1;
    d.RTVFormats[0] = format;
    d.SampleDesc.Count = 1;
    ID3D12PipelineState* pso = nullptr;
    BS_CHECK_HR(OverlayBackend::device()->CreateGraphicsPipelineState(&d, IID_PPV_ARGS(&pso)));
    f.pso[key] = pso;
    return pso;
}


void FullscreenFx::init() {
    if (f.ready)
        return;
    ID3D12Device* dev = OverlayBackend::device();
    D3D12_DESCRIPTOR_RANGE range{D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 2, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND};
    D3D12_ROOT_PARAMETER params[2]{};
    params[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    params[0].Constants = {0, 0, 8};
    params[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    params[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    params[1].DescriptorTable = {1, &range};
    params[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    const D3D12_STATIC_SAMPLER_DESC ss = D3D12Util::linearSampler();
    D3D12_ROOT_SIGNATURE_DESC rd{2, params, 1, &ss, D3D12_ROOT_SIGNATURE_FLAG_NONE};
    f.root = D3D12Util::createRootSignature(dev, rd);
    f.vs = compileMain(kVS, "fx_vs", "vs_5_0");
    const std::string withSmooth[2] = {std::string(kSmooth) + kGlowAdaptive, std::string(kSmooth) + kShadowComp};
    const char* sources[ShaderCount] = {kGlowDown, kGlowUp, withSmooth[0].c_str(), withSmooth[1].c_str(), kBlurDown, kBlur, kBlurComp, kShock};
    const char* names[ShaderCount] = {"glow_down", "glow_up", "glow_adaptive", "shadow_comp", "blur_down", "blur", "blur_comp", "shock"};
    for (int i = 0; i < ShaderCount; ++i)
        f.ps[i] = compileMain(sources[i], names[i], "ps_5_0");
    f.ready = true;
}

void FullscreenFx::shutdown() {
    if (!f.ready)
        return;
    for (auto& [k, pso] : f.pso)
        pso->Release();
    f.pso.clear();
    for (auto& p : f.ps)
        if (p) {
            p->Release();
            p = nullptr;
        }
    if (f.vs) {
        f.vs->Release();
        f.vs = nullptr;
    }
    if (f.root) {
        f.root->Release();
        f.root = nullptr;
    }
    f.ready = false;
}

void FullscreenFx::makeTarget(Target& t, UINT w, UINT h, DXGI_FORMAT format) {
    freeTarget(t);
    D3D12_HEAP_PROPERTIES hp{D3D12_HEAP_TYPE_DEFAULT};
    D3D12_RESOURCE_DESC rd{D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0, w, h, 1, 1, format, {1, 0}, D3D12_TEXTURE_LAYOUT_UNKNOWN, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET};
    D3D12_CLEAR_VALUE cv{format, {0.f, 0.f, 0.f, 0.f}};
    BS_CHECK_HR(OverlayBackend::device()->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &cv, IID_PPV_ARGS(&t.res)));
    t.rtv = OverlayBackend::allocRtv();
    OverlayBackend::device()->CreateRenderTargetView(t.res, nullptr, OverlayBackend::rtvCpu(t.rtv));
    t.w = w;
    t.h = h;
    t.format = format;
    t.state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
}

void FullscreenFx::freeTarget(Target& t) {
    if (!t.res)
        return;
    OverlayBackend::retire(t.res);
    if (t.rtv)
        OverlayBackend::freeRtv(t.rtv);
    t = Target{};
}

void FullscreenFx::toState(OverlayBackend::Cmd& cmd, Target& t, D3D12_RESOURCE_STATES to) {
    if (t.state == to)
        return;
    const D3D12_RESOURCE_BARRIER b = D3D12Util::transition(t.res, t.state, to);
    cmd.list->ResourceBarrier(1, &b);
    t.state = to;
}

void FullscreenFx::ensureCopy(Target& copy, UINT w, UINT h, DXGI_FORMAT format) {
    if (copy.res && copy.w == w && copy.h == h && copy.format == format)
        return;
    freeTarget(copy);
    D3D12_HEAP_PROPERTIES hp{D3D12_HEAP_TYPE_DEFAULT};
    D3D12_RESOURCE_DESC rd{D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0, w, h, 1, 1, format, {1, 0}, D3D12_TEXTURE_LAYOUT_UNKNOWN, D3D12_RESOURCE_FLAG_NONE};
    BS_CHECK_HR(OverlayBackend::device()->CreateCommittedResource(&hp, D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, nullptr, IID_PPV_ARGS(&copy.res)));
    copy.w = w;
    copy.h = h;
    copy.format = format;
    copy.state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
}

void FullscreenFx::pass(OverlayBackend::Cmd& cmd, Shader shader, Blend blend, ID3D12Resource* a, ID3D12Resource* b, D3D12_CPU_DESCRIPTOR_HANDLE rtv, DXGI_FORMAT rtvFormat, UINT w, UINT h,
    const float constants[8], const D3D12_RECT* scissor) {
    ID3D12Device* dev = OverlayBackend::device();
    const UINT first = OverlayBackend::srvs(cmd, 2);
    D3D12_CPU_DESCRIPTOR_HANDLE c0 = OverlayBackend::srvCpu(first), c1 = OverlayBackend::srvCpu(first + 1);
    dev->CreateShaderResourceView(a, nullptr, c0);
    dev->CreateShaderResourceView(b ? b : a, nullptr, c1);
    ID3D12GraphicsCommandList* list = cmd.list;
    list->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
    D3D12_VIEWPORT vp{0.f, 0.f, static_cast<float>(w), static_cast<float>(h), 0.f, 1.f};
    D3D12_RECT sr = scissor ? *scissor : D3D12_RECT{0, 0, static_cast<LONG>(w), static_cast<LONG>(h)};
    list->RSSetViewports(1, &vp);
    list->RSSetScissorRects(1, &sr);
    list->SetPipelineState(pipeline(shader, blend, rtvFormat));
    list->SetGraphicsRootSignature(f.root);
    list->SetGraphicsRoot32BitConstants(0, 8, constants, 0);
    list->SetGraphicsRootDescriptorTable(1, OverlayBackend::srvGpu(first));
    list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    const float factor[4] = {0, 0, 0, 0};
    list->OMSetBlendFactor(factor);
    list->DrawInstanced(3, 1, 0, 0);
}
