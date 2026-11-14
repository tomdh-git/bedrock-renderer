#include "sdk/mc/client/renderer/game/ItemInHandRenderer.h"
#include "sdk/Layout.h"

namespace {
alignas(void*) unsigned char gDeadItemRenderCall[sizeof(void*)]{};
const ItemRenderCall& deadRenderCall() {
    return *reinterpret_cast<const ItemRenderCall*>(&gDeadItemRenderCall);
}
} // namespace

const mce::MaterialPtr* ItemInHandRenderer::itemMaterial() const {
    static mce::MaterialPtr sNullMat{};
    return &sNullMat;
}

void ItemInHandRenderer::renderFirstPerson(
    BaseActorRenderContext& renderContext, const Matrix& prevProj, ItemContextFlags itemFlags) {
    (void)renderContext;
    (void)prevProj;
    (void)itemFlags;
    sdkLogStub("ItemInHandRenderer::renderFirstPerson");
}

void ItemInHandRenderer::renderItem(
    BaseActorRenderContext& renderContext, Actor& entity, const ItemStack& item,
    bool posAndRotSetByJSON, ItemContextFlags itemFlags, bool useMatrixAsIs,
    bool renderingMainHand) {
    (void)renderContext;
    (void)entity;
    (void)item;
    (void)posAndRotSetByJSON;
    (void)itemFlags;
    (void)useMatrixAsIs;
    (void)renderingMainHand;
    sdkLogStub("ItemInHandRenderer::renderItem");
}

void ItemInHandRenderer::renderItemNew(
    BaseActorRenderContext& renderContext, Actor& entity, const ItemStack& item,
    ItemContextFlags itemFlags, Brightness lightEmission) {
    (void)renderContext;
    (void)entity;
    (void)item;
    (void)itemFlags;
    (void)lightEmission;
    sdkLogStub("ItemInHandRenderer::renderItemNew");
}

void ItemInHandRenderer::renderOffhandItem(
    BaseActorRenderContext& renderContext, Player& player, ItemContextFlags itemFlags) {
    (void)renderContext;
    (void)player;
    (void)itemFlags;
    sdkLogStub("ItemInHandRenderer::renderOffhandItem");
}

void ItemInHandRenderer::renderObject(
    BaseActorRenderContext& renderContext, const ItemRenderCall& renderObject,
    const dragon::RenderMetadata& renderMetadata, ItemContextFlags itemFlags) {
    (void)renderContext;
    (void)renderObject;
    (void)renderMetadata;
    (void)itemFlags;
    sdkLogStub("ItemInHandRenderer::renderObject");
}

void ItemInHandRenderer::tessellateAtFrame(
    BaseActorRenderContext& renderContext, Mob* mob, const ItemStack& item, int frame) {
    (void)renderContext;
    (void)mob;
    (void)item;
    (void)frame;
    sdkLogStub("ItemInHandRenderer::tessellateAtFrame");
}

void ItemInHandRenderer::clearRenderObjects() {
    sdkLogStub("ItemInHandRenderer::clearRenderObjects");
}

const ItemRenderCall& ItemInHandRenderer::getRenderCallAtFrame(
    BaseActorRenderContext& renderContext, const ItemStack& item, int frame) {
    (void)renderContext;
    (void)item;
    (void)frame;
    sdkLogStub("ItemInHandRenderer::getRenderCallAtFrame");
    return deadRenderCall();
}

ItemRenderCall& ItemInHandRenderer::rebuildItem(
    BaseActorRenderContext& renderContext, Mob* mob, const ItemStack& item, int fallbackFrame) {
    (void)renderContext;
    (void)mob;
    (void)item;
    (void)fallbackFrame;
    sdkLogStub("ItemInHandRenderer::rebuildItem");
    return const_cast<ItemRenderCall&>(deadRenderCall());
}

ItemRenderCall* ItemInHandRenderer::getRenderCall(
    Mob* mob, const ItemStack& itemInstance, int fallbackFrame) {
    (void)mob;
    (void)itemInstance;
    (void)fallbackFrame;
    sdkLogStub("ItemInHandRenderer::getRenderCall");
    return nullptr;
}

void ItemInHandRenderer::applyDefaultItemTransforms(
    MatrixStack::MatrixStackRef& worldMatrix, const ItemStack& item, bool isInHandItem,
    const BlockType* blockType, BlockShape blockShape, const ItemRenderCall* renderObjectCall,
    float heldItemScale, bool posAndRotSetByJSON) {
    (void)worldMatrix;
    (void)item;
    (void)isInHandItem;
    (void)blockType;
    (void)blockShape;
    (void)renderObjectCall;
    (void)heldItemScale;
    (void)posAndRotSetByJSON;
    sdkLogStub("ItemInHandRenderer::applyDefaultItemTransforms");
}

void ItemInHandRenderer::pushSparklerParticles(
    BaseActorRenderContext& renderContext, const ItemStack& item, Level& level) {
    (void)renderContext;
    (void)item;
    (void)level;
    sdkLogStub("ItemInHandRenderer::pushSparklerParticles");
}

void ItemInHandRenderer::renderBannerBlockItem(
    BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
    const ItemStack& item, Actor& entity, Brightness lightEmission,
    const std::optional<Vec3>& lightEmissionColor, float frameAlpha, float scale) const {
    (void)renderContext;
    (void)renderMetadata;
    (void)item;
    (void)entity;
    (void)lightEmission;
    (void)lightEmissionColor;
    (void)frameAlpha;
    (void)scale;
    sdkLogStub("ItemInHandRenderer::renderBannerBlockItem");
}

void ItemInHandRenderer::renderChestBlockItem(
    BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
    const BlockType* blockType, Actor& entity, bool isInHandItem) const {
    (void)renderContext;
    (void)renderMetadata;
    (void)blockType;
    (void)entity;
    (void)isInHandItem;
    sdkLogStub("ItemInHandRenderer::renderChestBlockItem");
}

void ItemInHandRenderer::renderConduitBlockItem(
    BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata, Actor& entity,
    Brightness lightEmission, const std::optional<Vec3>& lightEmissionColor,
    float frameAlpha) const {
    (void)renderContext;
    (void)renderMetadata;
    (void)entity;
    (void)lightEmission;
    (void)lightEmissionColor;
    (void)frameAlpha;
    sdkLogStub("ItemInHandRenderer::renderConduitBlockItem");
}

void ItemInHandRenderer::renderCopperGolemStatueBlockItem(
    BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
    const ItemStack& item, Actor& entity, bool isFirstPerson, bool isInHandItem) const {
    (void)renderContext;
    (void)renderMetadata;
    (void)item;
    (void)entity;
    (void)isFirstPerson;
    (void)isInHandItem;
    sdkLogStub("ItemInHandRenderer::renderCopperGolemStatueBlockItem");
}

void ItemInHandRenderer::renderDecoratedPotBlockItem(
    BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
    const ItemStack& item, Actor& entity, bool isFirstPerson) const {
    (void)renderContext;
    (void)renderMetadata;
    (void)item;
    (void)entity;
    (void)isFirstPerson;
    sdkLogStub("ItemInHandRenderer::renderDecoratedPotBlockItem");
}

void ItemInHandRenderer::renderFishingRod(
    BaseActorRenderContext& renderContext, const ItemStack& item, Actor& entity) const {
    (void)renderContext;
    (void)item;
    (void)entity;
    sdkLogStub("ItemInHandRenderer::renderFishingRod");
}

void ItemInHandRenderer::renderGlowstickBlockItem(
    BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
    const ItemStack& item, Actor& entity, Brightness lightEmission,
    const std::optional<Vec3>& lightEmissionColor, float frameAlpha, ItemContextFlags itemFlags,
    float scale) {
    (void)renderContext;
    (void)renderMetadata;
    (void)item;
    (void)entity;
    (void)lightEmission;
    (void)lightEmissionColor;
    (void)frameAlpha;
    (void)itemFlags;
    (void)scale;
    sdkLogStub("ItemInHandRenderer::renderGlowstickBlockItem");
}

void ItemInHandRenderer::renderMiniMapHand(
    BaseActorRenderContext& renderContext, Player& player, bool inOffhand) {
    (void)renderContext;
    (void)player;
    (void)inOffhand;
    sdkLogStub("ItemInHandRenderer::renderMiniMapHand");
}

void ItemInHandRenderer::renderPhotoMapItem(
    BaseActorRenderContext& renderContext, Player& player, float frameAlpha, bool isMainHand) {
    (void)renderContext;
    (void)player;
    (void)frameAlpha;
    (void)isMainHand;
    sdkLogStub("ItemInHandRenderer::renderPhotoMapItem");
}

void ItemInHandRenderer::renderShulkerBoxBlockItem(
    BaseActorRenderContext& renderContext, dragon::RenderMetadata renderMetadata,
    const ItemStack& item, Actor& entity, Brightness lightEmission,
    const std::optional<Vec3>& lightEmissionColor, float frameAlpha) const {
    (void)renderContext;
    (void)renderMetadata;
    (void)item;
    (void)entity;
    (void)lightEmission;
    (void)lightEmissionColor;
    (void)frameAlpha;
    sdkLogStub("ItemInHandRenderer::renderShulkerBoxBlockItem");
}

void ItemInHandRenderer::tessellateBlockItem(
    Tessellator& tessellator, BlockTessellator& t, const Block& block,
    const mce::framebuilder::FrameLightingModelCapabilities& lightingModelCaps) {
    (void)tessellator;
    (void)t;
    (void)block;
    (void)lightingModelCaps;
    sdkLogStub("ItemInHandRenderer::tessellateBlockItem");
}

void ItemInHandRenderer::transformWorldMatrixFromJson(
    MatrixStack::MatrixStackRef& worldMatrix, const ItemStack& item, bool isMainHand,
    ItemContextFlags itemFlags, float textureScale) {
    (void)worldMatrix;
    (void)item;
    (void)isMainHand;
    (void)itemFlags;
    (void)textureScale;
    sdkLogStub("ItemInHandRenderer::transformWorldMatrixFromJson");
}

void ItemInHandRenderer::registerPauseManagerCallback(
    Bedrock::PubSub::Connector<void(bool)>& connector) {
    (void)connector;
    sdkLogStub("ItemInHandRenderer::registerPauseManagerCallback");
}

bool ItemInHandRenderer::areNotMatchingChemistrySticks(
    ItemStack& itemBefore, const ItemStack& itemAfter) {
    (void)itemBefore;
    (void)itemAfter;
    sdkLogStub("ItemInHandRenderer::areNotMatchingChemistrySticks");
    return false;
}

dragon::RenderMetadata ItemInHandRenderer::createRenderMetadata(
    const BaseActorRenderContext& renderContext, const Actor& entity, const ItemStack& item,
    bool isPaperDoll) {
    (void)renderContext;
    (void)entity;
    (void)item;
    (void)isPaperDoll;
    sdkLogStub("ItemInHandRenderer::createRenderMetadata");
    return dragon::RenderMetadata{};
}

void ItemInHandRenderer::tessellateTextureItem(
    BaseActorRenderContext& renderContext, TextureTessellator& textureTessellator, Mob* mob,
    const ItemStack& item, int fallbackFrame, unsigned short& heightOut,
    unsigned short& widthOut) {
    heightOut = 0;
    widthOut = 0;
    (void)renderContext;
    (void)textureTessellator;
    (void)mob;
    (void)item;
    (void)fallbackFrame;
    sdkLogStub("ItemInHandRenderer::tessellateTextureItem");
}

bool ItemInHandRenderer::canTessellateAsBlockItem(const ItemStack& item) {
    (void)item;
    sdkLogStub("ItemInHandRenderer::canTessellateAsBlockItem");
    return false;
}
