#pragma once
#include "sdk/mc/deps/core/math/Vec.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/MaterialPtr.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/MeshData.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h"
#include "sdk/mc/deps/minecraft_renderer/resources/BufferResourceService.h"
#include "sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h"
#include "sdk/mc/deps/minecraft_renderer/resources/ServerTexture.h"
// mMeshData slot is real; buffer/attribute tail and IndexBufferContainer
// base are unproven, omitted.
// Ctors/dtor-thunks omitted (construction is game-side only).

namespace dragon {
struct RenderMetadata {}; // Opaque carrier (by-value stub param/return only)
namespace mesh {
struct Mesh {}; // Opaque carrier (by-value stub return only)
} // namespace mesh
} // namespace dragon

struct OffscreenCaptureDescription; // by-ref stub param only, never touched

namespace mce {
class MeshContext;
struct IndexBufferContainer;
struct VertexLayout;

class Mesh {
public:
    using Index = unsigned int;
    using TextureVariant =
        std::variant<std::monostate, TexturePtr, ClientTexture, ServerTexture>; // TextureList element

    MeshData mMeshData; // mMeshData slot; tail members unproven, omitted

    const std::vector<Vec3>* positions() const {
        return mMeshData.positions();
    }
    const std::vector<Vec4>* normals() const {
        return mMeshData.normals();
    }
    const std::vector<unsigned int>* indices() const {
        return mMeshData.indices();
    }
    const std::vector<unsigned int>* colors() const {
        return mMeshData.colors();
    }
    const std::vector<Vec2>* uvs(unsigned int channel) const {
        return mMeshData.uvs(channel);
    }

    bool isValid() const {
        return !mMeshData.mPositions.empty() && !mMeshData.mIndices.empty();
    }
    bool areBuffersValid() const {
        return false;
    }
    std::span<const unsigned char> getRawData() const {
        return {};
    }
    void load(BufferResourceService&) {}
    void reset() {}
    void generateHALData(const VertexLayout*, bool) {}
    void prepareAsEmptyData(const VertexLayout&) {}
    void prepareRenderData(const VertexLayout&) {}
    void renderMesh(
        MeshContext&, const MaterialPtr&, const TextureVariant&, unsigned int, unsigned int,
        const OffscreenCaptureDescription&, const IndexBufferContainer*) const {}
    void renderMesh(
        MeshContext&, const MaterialPtr&, std::span<const ClientTexture*> textures, unsigned int,
        unsigned int, const OffscreenCaptureDescription&, const IndexBufferContainer*) const {
        (void)textures;
    }
    void renderMesh(
        MeshContext&, const ::dragon::RenderMetadata&, const MaterialPtr&, const TextureVariant&,
        unsigned int, unsigned int, const IndexBufferContainer*) const {}
    operator ::dragon::mesh::Mesh() const {
        return ::dragon::mesh::Mesh{};
    }
};

} // namespace mce
