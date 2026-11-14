#pragma once
#include "sdk/mc/deps/core/math/Vec.h"

struct StateVectorComponent;
struct ActorRotationComponent;
struct AttributesComponent;
struct AttributeInstance;

struct EntityContext;
struct Container;
struct HitResult;

struct Actor {
    EntityContext& getEntityContext();
    StateVectorComponent* getStateVectorComponent(); // 0x240 via BuiltInActorComponents (Lite Actor.cpp:46-52)
    ActorRotationComponent* getActorRotationComponent(); // the built-in rotation component (pitch at mRot.x, yaw at mRot.y, degrees)
    AttributesComponent* getAttributesComponent();
    AttributeInstance* getAttribute(int id); // null-guarded; nullptr until wired (Lite Actor.cpp:439-447)
    Vec3* getPos();
    float getHealth(); // 0 until wired (Lite Actor.cpp:413-417)
    bool isPlayer();
    struct AABB { Vec3 min, max; };
    AABB getAABB();                       // the actor's bounding box in the world
    std::vector<Actor*> getLevelActors(); // every actor of the level (the game's runtime actor list)
    void forEachLevelActor(void (*visitor)(Actor*, void*), void* context); // visits the game's list in place; no per-frame copy
    struct GameMode* getGameMode();
    void swing(uint8_t source = 4); // an arm swing (animation and packet); 4 = attack, 2 = mining
    bool canSee(Actor* other);    // line of sight to the other actor's body
    bool isDead();
    int getSelectedSlot();                  // the hotbar slot the client holds
    void setSelectedSlot(int slot);         // client side only
    Container* getInventory();              // the player's inventory slots (PlayerInventory -> Container)
    void sendEquipment(int slot);           // tells the server this actor holds that hotbar slot (a MobEquipment packet), without changing the client's slot
    HitResult* getHitResult();              // the level's crosshair ray result; the game reads it when it builds a block
    float getAbsorption();
    int64_t getRuntimeID(); // the id packets name this actor by
    Vec2 getHitboxSize();   // width, height (AABBShapeComponent)
    bool isInvisible();     // ActorDataFlagComponent status flag 5
    bool isOnGround();      // OnGroundFlagComponent presence check
    void setStatusFlag(int flag, bool value); // ActorDataFlagComponent bitset write
    void jumpFromGround();  // SimulatedPlayer::simulateJump — full game jump with velocity, flags, everything
    std::string getNameTag(); // the actor's name tag text ("" when it has none)
    std::string_view getNameTagView(); // the same text in the game's own string, not copied: valid on the game thread until the game changes the tag
    std::string_view getDefinitionIdentifier(); // the entity's definition id ("hivesky:death_crate", "minecraft:player"); empty for an actor with no definition. Valid while the actor lives
    std::vector<std::string> getPlayerListNames(); // the names in the level's player list (the real players)
};
