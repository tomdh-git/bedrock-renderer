#pragma once
#include "client/core/gpu/Gpu.h"

// D3D12 one-liners the render code shares.
struct D3D12Util {
    template <typename T>
    static void release(T*& p) {
        if (p) {
            p->Release();
            p = nullptr;
        }
    }

    static D3D12_RESOURCE_BARRIER transition(ID3D12Resource* r, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) {
        D3D12_RESOURCE_BARRIER b{};
        b.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        b.Transition = {r, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, from, to};
        return b;
    }

    // A linear-filtered static sampler at register `reg` (clamped or wrapping), visible to the pixel shader.
    static D3D12_STATIC_SAMPLER_DESC linearSampler(D3D12_TEXTURE_ADDRESS_MODE mode = D3D12_TEXTURE_ADDRESS_MODE_CLAMP, UINT reg = 0) {
        D3D12_STATIC_SAMPLER_DESC ss{};
        ss.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
        ss.AddressU = ss.AddressV = ss.AddressW = mode;
        ss.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
        ss.MaxLOD = D3D12_FLOAT32_MAX;
        ss.ShaderRegister = reg;
        ss.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
        return ss;
    }

    // A root signature from its description (serialised, created, the blob released).
    static ID3D12RootSignature* createRootSignature(ID3D12Device* dev, const D3D12_ROOT_SIGNATURE_DESC& desc) {
        ID3DBlob *blob = nullptr, *err = nullptr;
        BS_CHECK_HR(D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, &blob, &err));
        ID3D12RootSignature* root = nullptr;
        BS_CHECK_HR(dev->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&root)));
        blob->Release();
        return root;
    }
};
