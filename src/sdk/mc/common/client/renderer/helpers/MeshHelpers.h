#pragma once
#include "sdk/Layout.h"
#include "client/core/diagnostics/Log.h"
#include "sdk/mc/client/renderer/SupplementaryFieldAutoGenerationMode.h"
#include "sdk/mc/client/renderer/Tessellator.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/MaterialPtr.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/Mesh.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h"
#include "sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h"
#include "sdk/mc/deps/minecraft_renderer/resources/ServerTexture.h"
// 6 overloads mirroring the game header. Addresses unproven (free functions,
// no Lite-proven sigs).
// OffscreenCaptureDescription is by-ref-only here, so a forward declaration suffices.

struct OffscreenCaptureDescription;
struct ScreenContext;

namespace MeshHelpers {

using TextureVariant =
    std::variant<std::monostate, mce::TexturePtr, mce::ClientTexture, mce::ServerTexture>;

inline void renderMeshImmediately(
    ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material,
    const OffscreenCaptureDescription& capture) {
    (void)screenContext;
    (void)tessellator;
    (void)material;
    (void)capture;
    sdkLogStub("MeshHelpers::renderMeshImmediately");
}

inline void renderMeshImmediately(
    ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material,
    const TextureVariant& texture,
    std::function<void(
        const ScreenContext&, const mce::Mesh&, const mce::MaterialPtr&, const TextureVariant&)>
        meshRenderOverride) {
    // Real submit: snapshot the tessellated MeshData (no game addr) and run
    // the caller override synchronously. The viewhands override queues it for
    // the present-3d flush (proven d3d11 ctx via imgui draw data, game queue).
    if (!tessellator.hasData())
        Logger::fatal("[meshhelpers] fatal: empty tessellator");
    if (!meshRenderOverride)
        Logger::fatal("[meshhelpers] fatal: null override");
    mce::Mesh mesh{};
    mesh.mMeshData = tessellator.meshSnapshot();
    if (!mesh.isValid())
        Logger::fatal("[meshhelpers] fatal: invalid mesh");
    meshRenderOverride(screenContext, mesh, material, texture);
}

inline void renderMeshImmediately(
    ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material,
    const TextureVariant& texture, const OffscreenCaptureDescription& capture) {
    (void)screenContext;
    (void)tessellator;
    (void)material;
    (void)texture;
    (void)capture;
    sdkLogStub("MeshHelpers::renderMeshImmediately");
}

inline void renderMeshImmediately(
    ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material,
    const mce::ClientTexture& texture, const OffscreenCaptureDescription& capture) {
    (void)screenContext;
    (void)tessellator;
    (void)material;
    (void)texture;
    (void)capture;
    sdkLogStub("MeshHelpers::renderMeshImmediately");
}

inline void renderMeshImmediately(
    ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material,
    std::initializer_list<std::reference_wrapper<const mce::TexturePtr>> textures,
    const OffscreenCaptureDescription& capture) {
    (void)screenContext;
    (void)tessellator;
    (void)material;
    (void)textures;
    (void)capture;
    sdkLogStub("MeshHelpers::renderMeshImmediately");
}

inline void renderMeshImmediately(
    ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material,
    const TextureVariant& texture, SupplementaryFieldAutoGenerationMode generationMode,
    const OffscreenCaptureDescription& capture) {
    (void)screenContext;
    (void)tessellator;
    (void)material;
    (void)texture;
    (void)generationMode;
    (void)capture;
    sdkLogStub("MeshHelpers::renderMeshImmediately");
}

} // namespace MeshHelpers
