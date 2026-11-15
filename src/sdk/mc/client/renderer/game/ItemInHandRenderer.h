#pragma once
#include "sdk/mc/deps/core/math/Vec.h"
#include "sdk/mc/deps/core/math/Matrix.h"
#include "sdk/mc/deps/minecraft_renderer/game/ItemContextFlags.h"
#include "sdk/mc/deps/minecraft_renderer/renderer/Mesh.h"
#include "sdk/mc/world/item/ItemStack.h"
// Public method set mirrors the game header. Body unproven (no proven member
// offsets; ItemInHandRenderer::renderItem sig explicitly UNPROVEN in
// Lite SigManager). Base is ActorShaderManager; render methods are direct
// MCAPI calls (no vtable slots).
// Ctor/dtor/thunks/$statics omitted (construction is game-side only).

struct Actor;
struct BaseActorRenderContext;
struct Block;
struct BlockTessellator;
struct BlockType;
struct IClientInstance;
struct ItemRenderCall;
struct Level;
struct Mob;
struct Player;
struct Tessellator;
struct TextureTessellator;
struct Brightness {}; // Opaque carrier (by-value stub param only)
enum class BlockShape : int {}; // Values unknown; complete type, no invented enumerators

namespace MatrixStack {
struct MatrixStackRef;
}
namespace Bedrock {
namespace PubSub {
template <typename Signature>
struct Connector;
struct Subscription;
} // namespace PubSub
} // namespace Bedrock
namespace mce {
namespace framebuilder {
struct FrameLightingModelCapabilities;
}
} // namespace mce

struct ItemInHandRenderer {
    // Counted vtable (from ActorShaderManager): 0 = dtor (overridden here),
    // 1 = _getOverlayColor (inherited, not overridden). No new virtuals declared.
    static constexpr int VTable_Dtor = 0;
    static constexpr int VTable_OverlayColor = 1;
    static constexpr int VTable_BaseCount = 2;

    // mMatItem slot; offset unproven, no Lite proof.
    const mce::MaterialPtr* itemMaterial() const;

    void renderFirstPerson(BaseActorRenderContext& renderContext, const Matrix& prevProj, ItemContextFlags itemFlags);
    void renderItem(
        BaseActorRenderContext& renderContext, Actor& entity, const ItemStack& item,
        bool posAndRotSetByJSON, ItemContextFlags itemFlags, bool useMatrixAsIs, bool renderingMainHand);
    void renderItemNew(
        BaseActorRenderContext& renderContext, Actor& entity, const ItemStack& item,
        ItemContextFlags itemFlags, Brightness lightEmission);
    void renderOffhandItem(BaseActorRenderContext& renderContext, Player& player, ItemContextFlags itemFlags);
    void renderObject(
        BaseActorRenderContext& renderContext, const ItemRenderCall& renderObject,
        const dragon::RenderMetadata& renderMetadata, ItemContextFlags itemFlags);
    void tessellateAtFrame(
        BaseActorRenderContext& renderContext, Mob* mob, const ItemStack& item, int frame);
    void clearRenderObjects();
    const ItemRenderCall& getRenderCallAtFrame(
        BaseActorRenderContext& renderContext, const ItemStack& item, int frame);
    ItemRenderCall& rebuildItem(
        BaseActorRenderContext& renderContext, Mob* mob, const ItemStack& item, int fallbackFrame);
    ItemRenderCall* getRenderCall(Mob* mob, const ItemStack& itemInstance, int fallbackFrame);
    void applyDefaultItemTransforms(
        MatrixStack::MatrixStackRef& worldMatrix, const ItemStack& item, bool isInHandItem,
        const BlockType* blockType, BlockShape blockShape, const ItemRenderCall* renderObjectCall,
        float heldItemScale, bool posAndRotSetByJSON);
    void pushSparklerParticles(
        BaseActorRenderContext& renderContext, const ItemStack& item, Level& level);
    void renderBannerBlockItem(
        BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
        const ItemStack& item, Actor& entity, Brightness lightEmission,
        const std::optional<Vec3>& lightEmissionColor, float frameAlpha, float scale) const;
    void renderChestBlockItem(
        BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
        const BlockType* blockType, Actor& entity, bool isInHandItem) const;
    void renderConduitBlockItem(
        BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata, Actor& entity,
        Brightness lightEmission, const std::optional<Vec3>& lightEmissionColor,
        float frameAlpha) const;
    void renderCopperGolemStatueBlockItem(
        BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
        const ItemStack& item, Actor& entity, bool isFirstPerson, bool isInHandItem) const;
    void renderDecoratedPotBlockItem(
        BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
        const ItemStack& item, Actor& entity, bool isFirstPerson) const;
    void renderFishingRod(
        BaseActorRenderContext& renderContext, const ItemStack& item, Actor& entity) const;
    void renderGlowstickBlockItem(
        BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
        const ItemStack& item, Actor& entity, Brightness lightEmission,
        const std::optional<Vec3>& lightEmissionColor, float frameAlpha, ItemContextFlags itemFlags,
        float scale);
    void renderMiniMapHand(BaseActorRenderContext& renderContext, Player& player, bool inOffhand);
    void renderPhotoMapItem(
        BaseActorRenderContext& renderContext, Player& player, float frameAlpha, bool isMainHand);
    void renderShulkerBoxBlockItem(
        BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
        const ItemStack& item, Actor& entity, Brightness lightEmission,
        const std::optional<Vec3>& lightEmissionColor, float frameAlpha) const;
    void tessellateBlockItem(
        Tessellator& tessellator, BlockTessellator& t, const Block& block,
        const mce::framebuilder::FrameLightingModelCapabilities& lightingModelCaps);
    void transformWorldMatrixFromJson(
        MatrixStack::MatrixStackRef& worldMatrix, const ItemStack& item, bool isMainHand,
        ItemContextFlags itemFlags, float textureScale);
    void registerPauseManagerCallback(Bedrock::PubSub::Connector<void(bool)>& connector);

    static bool areNotMatchingChemistrySticks(ItemStack& itemBefore, const ItemStack& itemAfter);
    static dragon::RenderMetadata createRenderMetadata(
        const BaseActorRenderContext& renderContext, const Actor& entity, const ItemStack& item,
        bool isPaperDoll);
    static void tessellateTextureItem(
        BaseActorRenderContext& renderContext, TextureTessellator& textureTessellator, Mob* mob,
        const ItemStack& item, int fallbackFrame, unsigned short& heightOut,
        unsigned short& widthOut);
    static bool canTessellateAsBlockItem(const ItemStack& item);
};
