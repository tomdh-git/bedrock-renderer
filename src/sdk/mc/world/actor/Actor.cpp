#include "sdk/mc/world/actor/Actor.h"
#include "sdk/mc/deps/ecs/gamerefs_entity/EntityContext.h"
#include "client/core/threading/ThreadContract.h"
#include "sdk/mc/world/actor/BuiltInActorComponents.h"
#include "sdk/mc/deps/vanilla_components/AABBShapeComponent.h"
#include "sdk/mc/deps/vanilla_components/ActorDataFlagComponent.h"
#include "sdk/mc/deps/vanilla_components/OnGroundFlagComponent.h"
#include "sdk/mc/deps/vanilla_components/ActorTypeComponent.h"
#include "sdk/mc/entity/components/IsDeadFlagComponent.h"
#include "sdk/mc/world/gamemode/GameMode.h"
#include "sdk/mc/deps/vanilla_components/AttributesComponent.h"
#include "sdk/mc/deps/vanilla_components/RuntimeIDComponent.h"
#include "sdk/Layout.h"
#include "sdk/mc/client/game/ClientInstance.h"
#include "sdk/mc/network/MinecraftPackets.h"
#include "sdk/mc/world/Container.h"
#include "sdk/mc/world/item/ItemStack.h"
#include "sdk/mc/world/phys/HitResult.h"
#include "sdk/SigManager.h"
#include "sdk/mc/network/LoopbackPacketSender.h"
#include "sdk/mc/network/packet/MobEquipmentPacket.h"
#include "sdk/mc/deps/core/string/GameString.h"
#include "sdk/OffsetProvider.h"

// ActorSwingSource: Build 0, Mine 1, Interact 2, Attack 3 ... (the game's enum; only Attack is used here)
enum class ActorSwingSource : uint8_t { None = 0, Build = 1, Mine = 2, Interact = 3, Attack = 4 };

EntityContext& Actor::getEntityContext() {
    return *reinterpret_cast<EntityContext*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mEntityContext);
}

StateVectorComponent* Actor::getStateVectorComponent() {
    return *reinterpret_cast<StateVectorComponent**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mBuiltInComponents);
}

ActorRotationComponent* Actor::getActorRotationComponent() {
    auto* components = reinterpret_cast<BuiltInActorComponents*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mBuiltInComponents);
    return components->mActorRotationComponent;
}

AttributesComponent* Actor::getAttributesComponent() {
    return getEntityContext().tryGetComponent<AttributesComponent>();
}

AttributeInstance* Actor::getAttribute(int id) {
    AttributesComponent* ac = getAttributesComponent();
    return ac ? ac->mBaseAttributeMap.getInstance(static_cast<unsigned int>(id)) : nullptr;
}

Vec3* Actor::getPos() {
    return &getStateVectorComponent()->mPos;
}

float Actor::getHealth() {
    AttributeInstance* a = getAttribute(Health);
    return a ? a->mCurrentValue : 0.0f;
}

int64_t Actor::getRuntimeID() {
    RuntimeIDComponent* c = getEntityContext().tryGetComponent<RuntimeIDComponent>();
    BS_CHECK(c);
    return c->mRuntimeID;
}

Vec2 Actor::getHitboxSize() {
    AABBShapeComponent* c = getEntityContext().tryGetComponent<AABBShapeComponent>();
    BS_CHECK(c);
    return c->mBBDim;
}

bool Actor::isInvisible() {
    const ActorDataFlagComponent* c = getEntityContext().tryGetComponent<ActorDataFlagComponent>();
    BS_CHECK(c);
    return reinterpret_cast<const std::bitset<119>*>(c)->test(5);
}

bool Actor::isOnGround() {
    return getEntityContext().tryGetComponent<OnGroundFlagComponent>() != nullptr;
}

void Actor::setStatusFlag(int flag, bool value) {
    ActorDataFlagComponent* c = getEntityContext().tryGetComponent<ActorDataFlagComponent>();
    BS_CHECK(c);
    reinterpret_cast<std::bitset<119>*>(c)->set(static_cast<size_t>(flag), value);
}

void Actor::jumpFromGround() {
    using Fn = void (*)(Actor*);
    reinterpret_cast<Fn>(SIG("SimulatedPlayer::simulateJump"))(this);
}

// Actor::getNameTag(this) returns a reference to the game's std::string (found by sig).
std::string_view Actor::getNameTagView() {
    using Fn = const GameString* (*)(Actor*);
    return reinterpret_cast<Fn>(SIG("Actor::getNameTag"))(this)->view();
}

std::string Actor::getNameTag() {
    return std::string(getNameTagView());
}

// The actor's ActorDefinitionPtr holds the definition the entity was made from; its identifier is a Release std::string read in place (never copied through our STL).
std::string_view Actor::getDefinitionIdentifier() {
    const uintptr_t definition = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mActorDefinitionPtr + sizeof(void*));
    if (!definition) // an actor made without a definition (no entity id to speak of)
        return {};
    return reinterpret_cast<const GameString*>(definition + OffsetProvider::ActorDefinition_mIdentifier)->view();
}

// The level's player list is the game's std::unordered_map<UUID, PlayerListEntry> (MSVC Release layout): a node list at the start
// of the map (sentinel node pointer, size); each node is { next, prev, UUID key (16), PlayerListEntry } and the entry's name
// (a std::string) sits 0x18 into the entry (id 8 + uuid 16).
std::vector<std::string> Actor::getPlayerListNames() {
    void* level = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mLevel);
    const auto* map = callVirtual<const uint8_t*>(OffsetProvider::Level_getPlayerList, level);
    const uint8_t* sentinel = *reinterpret_cast<const uint8_t* const*>(map + 8); // the traits object (empty, padded to 8) comes first
    const size_t count = *reinterpret_cast<const size_t*>(map + 0x10);
    BS_CHECK(count < 4096);
    std::vector<std::string> names;
    const uint8_t* node = *reinterpret_cast<const uint8_t* const*>(sentinel);
    for (size_t i = 0; i < count && node != sentinel; i++, node = *reinterpret_cast<const uint8_t* const*>(node))
        names.emplace_back(reinterpret_cast<const GameString*>(node + 0x10 + 0x10 + 0x18)->view());
    return names;
}

bool Actor::isPlayer() {
    // An actor the level lists while it is being spawned or removed has no type component yet (or any more): that is not a player, not a broken state.
    ActorTypeComponent* c = getEntityContext().tryGetComponent<ActorTypeComponent>();
    return c && c->mType == ActorType::Player;
}

Actor::AABB Actor::getAABB() {
    AABBShapeComponent* c = getEntityContext().tryGetComponent<AABBShapeComponent>();
    BS_CHECK(c);
    AABB box;
    memcpy(&box, c->mAABB, sizeof(box)); // the component starts with the box: min xyz, max xyz
    return box;
}

// Level::getRuntimeActorList fills a std::vector<Actor*> in the game's Release layout; its buffer is the game's (freed with the
// game's allocator), so the pointers are copied out and the buffer is released here.
std::vector<Actor*> Actor::getLevelActors() {
    std::vector<Actor*> actors;
    forEachLevelActor([](Actor* actor, void* context) { static_cast<std::vector<Actor*>*>(context)->push_back(actor); }, &actors);
    return actors;
}

void Actor::forEachLevelActor(void (*visitor)(Actor*, void*), void* context) {
    BS_CHECK(visitor);
    ThreadContract::warnIfNotGame("actor list read"); // warn-only: visual modules read the list on the render thread
    void* level = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mLevel);
    GameVector<Actor*> out{};
    callVirtual<GameVector<Actor*>*>(OffsetProvider::Level_getRuntimeActorList, level, &out);
    struct ReleaseActors {
        Actor** first;
        ~ReleaseActors() { gameFree(first); }
    } release{out.first};
    for (Actor** actor = out.first; actor && actor < out.last; ++actor)
        visitor(*actor, context);
}

GameMode* Actor::getGameMode() {
    return *reinterpret_cast<GameMode**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mGameMode);
}

void Actor::swing(uint8_t source) {
    callVirtualVoid(OffsetProvider::Actor_swing, this, source, static_cast<uint8_t>(0));
}

bool Actor::canSee(Actor* other) {
    // The other actor's body position (GetCollisionShapeActorProxy::getFeetAttachPos with the body location), then a line of sight to it.
    using FeetFn = Vec3* (*)(Actor*, Vec3*, int, float);
    using SeeFn = bool (*)(Actor*, Vec3&, int);
    Vec3 body;
    reinterpret_cast<FeetFn>(SIG("GetCollisionShapeActorProxy::getFeetAttachPos"))(other, &body, 1, 0.f);
    return reinterpret_cast<SeeFn>(SIG("Actor::canSee"))(this, body, 0);
}

bool Actor::isDead() {
    return getEntityContext().tryGetComponent<IsDeadFlagComponent>() != nullptr;
}

int Actor::getSelectedSlot() {
    return *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mSupplies) + OffsetProvider::PlayerInventory_mSelectedSlot);
}

void Actor::setSelectedSlot(int slot) {
    *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mSupplies) + OffsetProvider::PlayerInventory_mSelectedSlot) = slot;
}

Container* Actor::getInventory() {
    const uintptr_t supplies = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mSupplies);
    return *reinterpret_cast<Container**>(supplies + OffsetProvider::PlayerInventory_mContainer);
}

void Actor::sendEquipment(int slot) {
    std::shared_ptr<Packet> packet = MinecraftPackets::createPacket(MinecraftPacketIds::PlayerEquipment);
    MobEquipmentPacketPayload& payload = static_cast<MobEquipmentPacket*>(packet.get())->mBaseMobEquipmentPacketPayload;
    const int64_t runtimeId = getRuntimeID();
    std::memcpy(payload.mRuntimeId, &runtimeId, sizeof(runtimeId));
    std::memset(&payload.mItem, 0, sizeof(payload.mItem));
    using DescriptorCtor = void (*)(NetworkItemStackDescriptor*, ItemStack*);
    reinterpret_cast<DescriptorCtor>(SIG("NetworkItemStackDescriptor::ctor"))(&payload.mItem, getInventory()->getItem(slot));
    payload.mSlot = slot;
    payload.mSelectedSlot = slot;
    payload.mContainerId = ContainerID::Inventory;
    callVirtualVoid(LoopbackPacketSender::vSendToServer, ClientInstance::get()->getPacketSender(), packet.get());
}

HitResult* Actor::getHitResult() {
    void* level = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(this) + OffsetProvider::Actor_mLevel);
    return callVirtual<HitResult*>(OffsetProvider::Level_getHitResult, level);
}

float Actor::getAbsorption() {
    AttributeInstance* a = getAttribute(Absorption);
    return a ? a->mCurrentValue : 0.f;
}
