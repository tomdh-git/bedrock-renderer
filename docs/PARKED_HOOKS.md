# Parked hooks

These hooks were removed on 2026-10-18 because nothing in `src` consumed their events, and every hook is a signature that can die on a game update.
Their ideas, signatures and detour shapes are kept here so any of them can be brought back in a few minutes.
Git history also keeps the original files: they are in the commit just before the one that added this document.

## How to bring one back

1. Add the signature below to `src/sdk/Sigs.json` at the stated path, with `"priority": "high"`.
2. Add the event header under the matching domain in `src/client/core/event/events/{game,network,render,ui}/`.
3. Add the detour to a hook group under `src/client/features/hooks/hooks/{game,render,input,network,resources}/` (see `README.md` there) and register it in `HookManager::init`.
4. Run `python tools/sigs/sigs.py` (checks that every `SIG("...")` is present) and, with a game exe, `python tools/sigs/audit.py <exe>`.

Signatures were valid for game build 1.26.51 (gdk 6764). Re-check them before reuse.


## ChatHook: Outgoing chat

### `ClientInstanceScreenModel::sendChatMessage`

Fires when the local player sends a chat line. Listeners could edit or cancel the text.

Idea: Chat commands with a prefix, an outgoing translator, slash-command aliases, a send rate limit.

Signature path in `Sigs.json`: `mc/client/gui/screens/models/ClientInstanceScreenModel/sendChatMessage`

```json
{"priority": "high", "sigs": ["@1 E8 ?? ?? ?? ?? 3C ?? 75 ?? 48 8B 8E ?? ?? ?? ?? 48 C7 45 ?? ?? ?? ?? ?? 48 8B 01 48 8B 40 ?? 48 8D 55 ?? FF 15 ?? ?? ?? ?? 48 8B 4D"]}
```

Detour as it was:

```cpp
void* ChatHook::sendChat(void* screenModel, std::string& message) {
    auto holder = nes::make_holder<ChatEvent>(message);
    Eventing::dispatcher().trigger(holder);
    if (holder->isCancelled())
        return nullptr;
    return mSendChat->getOriginal<&sendChat>()(screenModel, message);
}
```

Event:

```cpp
struct ChatEvent : CancelableEvent {
    std::string& message;
    explicit ChatEvent(std::string& m) : message(m) {}
};
```


## ContainerScreenHook: Open container screen tick

### `ContainerScreenController::tick`

Runs once per tick while a container screen (chest, inventory) is open, before the game ticks it.

Idea: Inventory helpers: sorting, quick-move, slot hover previews.

Signature path in `Sigs.json`: `mc/client/gui/screens/controllers/ContainerScreenController/tick`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 0F 29 75 ?? 48 C7 45 ?? ?? ?? ?? ?? 48 89 CE 48 8D B9 ?? ?? ?? ?? C6 45"]}
```

Detour as it was:

```cpp
uint32_t ContainerScreenHook::tick(void* controller) {
    Eventing::trigger<ContainerScreenTickEvent>(controller);
    return mTick->getOriginal<&tick>()(controller);
}
```

Event:

```cpp
struct ContainerScreenTickEvent : Event {
    void* controller;
    explicit ContainerScreenTickEvent(void* c) : controller(c) {}
};
```


## RenderControllerHook: Entity overlay color

### `RenderController::getOverlayColor`

Runs after the original, so listeners saw and could rewrite the hurt-flash color of an entity. The entity pointer sits at `OffsetProvider::RenderControllerEntity_mActor` (0x38) of the `entity` argument; that constant was removed with this hook.

Idea: Custom hit-flash color. Community note (ambient, 2026): it only works for first person and the paper doll, because third-person entities use the data-driven renderer, so verify before relying on it.

Signature path in `Sigs.json`: `mc/client/renderer/controller/RenderController/getOverlayColor`

```json
{"priority": "high", "sigs": ["@1 E8 ?? ?? ?? ?? 0F 11 7D ?? 4C 89 F9"]}
```

Detour as it was:

```cpp
mce::Color* RenderControllerHook::overlayColor(void* self, mce::Color* out, void* entity) {
    mOverlayColor->getOriginal<&overlayColor>()(self, out, entity);
    Eventing::trigger<OverlayColorEvent>(*out, *reinterpret_cast<Actor**>(reinterpret_cast<uintptr_t>(entity) + OffsetProvider::RenderControllerEntity_mActor));
    return out;
}
```

Event:

```cpp
#include "sdk/mc/world/actor/Actor.h"

struct OverlayColorEvent : Event {
    mce::Color& color;
    Actor* actor;
    OverlayColorEvent(mce::Color& c, Actor* a) : color(c), actor(a) {}
};
```


## UiHook: Tooltips and incoming chat

### `HoverTextRenderer::render`

Cancelable. Runs before the game draws a hover tooltip.

Idea: Replace or suppress tooltips (item info, durability).

Signature path in `Sigs.json`: `mc/client/gui/controls/renderers/HoverTextRenderer/render`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 56 57 53 48 81 EC 78 01 00 00 48 8D AC 24 ?? ?? ?? ?? 44 0F 29 85 ?? ?? ?? ?? 0F 29 BD ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? FE FF FF FF 48 83 79 ?? 00"]}
```

Detour as it was:

```cpp
void UiHook::hoverText(void* self, void* renderContext, void* clientInstance, Vec4* aabb, int pass) {
    auto holder = nes::make_holder<HoverTextEvent>(self);
    Eventing::dispatcher().trigger(holder);
    if (!holder->isCancelled())
        mHoverText->getOriginal<&hoverText>()(self, renderContext, clientInstance, aabb, pass);
}
```

Event:

```cpp
struct HoverTextEvent : CancelableEvent {
    void* renderer;
    explicit HoverTextEvent(void* r) : renderer(r) {}
};
```

### `GuiData::addMessage`

Cancelable. Runs when a chat message is added to the on-screen chat.

Idea: Filtering, timestamps, regex highlights, translation, a searchable log.

Signature path in `Sigs.json`: `mc/client/gui/GuiData/addMessage`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 78 04 00 00 48 8D AC 24 80 00 00 00 48 C7 85 F0 03 00 00 FE FF FF FF 44 89 85 B8 02 00 00 48 89 95 B8 03 00 00 48 89 CE 48 8B 89 98 00 00 00"]}
```

Detour as it was:

```cpp
void UiHook::addMessage(void* guiData, void* messageConfig, unsigned int profanityContext) {
    auto holder = nes::make_holder<AddMessageEvent>(guiData, messageConfig);
    Eventing::dispatcher().trigger(holder);
    if (!holder->isCancelled())
        mAddMessage->getOriginal<&addMessage>()(guiData, messageConfig, profanityContext);
}
```

Event:

```cpp
struct AddMessageEvent : CancelableEvent {
    void* guiData;
    void* messageConfig;
    AddMessageEvent(void* g, void* c) : guiData(g), messageConfig(c) {}
};
```


## LevelRendererHook: World render callbacks

### `LevelRenderer::renderLevel`

Runs after the game has rendered the world, with the level renderer and the `ScreenContext`. The classic place for 3D drawing through the game tessellator (vertex = world position minus camera position).

Idea: World-space lines and boxes, waypoints.

Signature path in `Sigs.json`: `mc/client/renderer/game/LevelRenderer/renderLevel`

```json
{"priority": "high", "sigs": ["@1 E8 ?? ?? ?? ?? 45 31 E4 48 83 BE", "55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 44 0F 29 AD ?? ?? ?? ?? 44 0F 29 A5 ?? ?? ?? ?? 44 0F 29 9D ?? ?? ?? ?? 44 0F 29 95 ?? ?? ?? ?? 44 0F 29 8D ?? ?? ?? ?? 44 0F 29 85 ?? ?? ?? ?? 0F 29 BD ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 4D 89 C6 48 89 D6"]}
```

Detour as it was:

```cpp
void LevelRendererHook::renderLevel(void* levelRenderer, void* screenContext, void* unk) {
    mRenderLevel->getOriginal<&renderLevel>()(levelRenderer, screenContext, unk);
    Eventing::trigger<RenderLevelEvent>(levelRenderer, screenContext);
}
```

Event:

```cpp
struct RenderLevelEvent : Event {
    void* levelRenderer;
    void* screenContext;
    RenderLevelEvent(void* l, void* s) : levelRenderer(l), screenContext(s) {}
};
```

### `LevelRendererPlayer::renderOutlineSelection`

Cancelable. Runs before the game draws the block selection outline.

Idea: Custom block outline, thickness or color.

Signature path in `Sigs.json`: `mc/client/renderer/game/LevelRendererPlayer/renderOutlineSelection`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 44 0F 29 95 ?? ?? ?? ?? 44 0F 29 8D ?? ?? ?? ?? 44 0F 29 85 ?? ?? ?? ?? 0F 29 BD ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 4C 89 CB 4D 89 C7"]}
```

Detour as it was:

```cpp
void LevelRendererHook::outlineSelection(void* self, void* screenContext, void* block, void* region, BlockPos pos) {
    auto holder = nes::make_holder<OutlineSelectionEvent>(pos);
    Eventing::dispatcher().trigger(holder);
    if (!holder->isCancelled())
        mOutlineSelection->getOriginal<&outlineSelection>()(self, screenContext, block, region, pos);
}
```

Event:

```cpp
struct OutlineSelectionEvent : CancelableEvent {
    BlockPos pos;
    explicit OutlineSelectionEvent(const BlockPos& p) : pos(p) {}
};
```

### `LevelRendererPlayer::bobHurt`

Cancelable. Runs before the damage camera shake matrix is applied.

Idea: Reduced or no hurt camera shake (accessibility).

Signature path in `Sigs.json`: `mc/client/renderer/game/LevelRendererPlayer/bobHurt`

```json
{"priority": "high", "sigs": ["56 57 55 53 48 81 EC ?? ?? ?? ?? 44 0F 29 84 24 ?? ?? ?? ?? 0F 29 BC 24 ?? ?? ?? ?? 0F 29 B4 24 ?? ?? ?? ?? 0F 28 F2"]}
```

Detour as it was:

```cpp
void LevelRendererHook::bobHurt(void* self, Matrix* matrix, float a) {
    auto holder = nes::make_holder<BobHurtEvent>(self, matrix);
    Eventing::dispatcher().trigger(holder);
    if (!holder->isCancelled())
        mBobHurt->getOriginal<&bobHurt>()(self, matrix, a);
}
```

Event:

```cpp
struct BobHurtEvent : CancelableEvent {
    void* renderer;
    Matrix* matrix;
    BobHurtEvent(void* r, Matrix* m) : renderer(r), matrix(m) {}
};
```


## ActorRenderHook: Per-actor draw details

### `ItemRenderer::render`

Runs before the game draws an item (held, dropped).

Idea: Item scale, dropped-item styling.

Signature path in `Sigs.json`: `mc/client/renderer/actor/ItemRenderer/render`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 44 0F 29 9D ?? ?? ?? ?? 44 0F 29 95 ?? ?? ?? ?? 44 0F 29 4D ?? 44 0F 29 45 ?? 0F 29 7D ?? 0F 29 75 ?? 48 C7 45 ?? ?? ?? ?? ?? ?? ?? ?? 48 85 F6"]}
```

Detour as it was:

```cpp
void ActorRenderHook::itemRender(void* self, void* renderContext, void* actorRenderData) {
    Eventing::trigger<ItemRendererEvent>(self, renderContext, actorRenderData);
    mItemRender->getOriginal<&itemRender>()(self, renderContext, actorRenderData);
}
```

Event:

```cpp
struct ItemRendererEvent : Event {
    void* renderer;
    void* renderContext;
    void* actorRenderData;
    ItemRendererEvent(void* r, void* c, void* d) : renderer(r), renderContext(c), actorRenderData(d) {}
};
```

### `ActorShaderManager::setupShaderParameters`

Cancelable. Runs before the game fills the per-actor shader constants (overlay, change colors, glint color). The corpus notes that in current builds much of the data-driven renderer is inlined here.

Idea: Per-actor tint, custom glint, hit flash.

Signature path in `Sigs.json`: `mc/client/renderer/ActorShaderManager/setupShaderParameters`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 44 0F 29 BD ?? ?? ?? ?? 44 0F 29 B5 ?? ?? ?? ?? 44 0F 29 AD ?? ?? ?? ?? 44 0F 29 A5 ?? ?? ?? ?? 44 0F 29 9D ?? ?? ?? ?? 44 0F 29 95 ?? ?? ?? ?? 44 0F 29 8D ?? ?? ?? ?? 44 0F 29 85 ?? ?? ?? ?? 0F 29 BD ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 4D 89 CE 4C 89 C3 48 89 95 ?? ?? ?? ?? F3 44 0F 10 B5"]}
```

Detour as it was:

```cpp
void ActorRenderHook::shaderParameters(void* screenContext, void* actorRenderContext, Actor* entity, Vec4* overlay, Vec4* changeColor, Vec4* changeColor2, Vec4* glintColor,
    float uvOffset1, float uvOffset2, float uvRot1, float uvRot2, Vec2* glintUvScale, Vec4* uvAnim, float brightness, uint8_t lightEmission, void* lightEmissionColor) {
    auto holder = nes::make_holder<SetupShaderParameterEvent>(screenContext, actorRenderContext, entity, overlay, changeColor, changeColor2, glintColor);
    Eventing::dispatcher().trigger(holder);
    if (!holder->isCancelled())
        mShaderParameters->getOriginal<&shaderParameters>()(screenContext, actorRenderContext, entity, overlay, changeColor, changeColor2, glintColor,
            uvOffset1, uvOffset2, uvRot1, uvRot2, glintUvScale, uvAnim, brightness, lightEmission, lightEmissionColor);
}
```

Event:

```cpp
#include "sdk/mc/world/actor/Actor.h"

struct SetupShaderParameterEvent : CancelableEvent {
    void* screenContext;
    void* actorRenderContext;
    Actor* entity;
    Vec4* overlay;
    Vec4* changeColor;
    Vec4* changeColor2;
    Vec4* glintColor;
    SetupShaderParameterEvent(void* sc, void* ctx, Actor* e, Vec4* o, Vec4* c1, Vec4* c2, Vec4* g)
        : screenContext(sc), actorRenderContext(ctx), entity(e), overlay(o), changeColor(c1), changeColor2(c2), glintColor(g) {}
};
```

### `BaseActorRenderer::renderText`

Cancelable. Runs before the game draws a nametag text.

Idea: Hide or restyle nametags, add health text.

Signature path in `Sigs.json`: `mc/client/renderer/BaseActorRenderer/renderText`

```json
{"priority": "high", "sigs": ["@1 E8 ?? ?? ?? ?? 49 81 C7 ?? ?? ?? ?? 4D 39 E7 75 ?? 48 83 C4"]}
```

Detour as it was:

```cpp
void ActorRenderHook::nametag(void* screenContext, void* viewData, GameString* tag, void* font, void* mesh) {
    auto holder = nes::make_holder<NametagRenderEvent>(tag);
    Eventing::dispatcher().trigger(holder);
    if (!holder->isCancelled())
        mNametag->getOriginal<&nametag>()(screenContext, viewData, tag, font, mesh);
}
```

Event:

```cpp
struct NametagRenderEvent : CancelableEvent {
    GameString* tag; // the text about to be drawn
    explicit NametagRenderEvent(GameString* t) : tag(t) {}
};
```


## ItemInHandHook: First-person hand gate

### `ItemInHandRenderer::renderFirstPerson`

Cancelable. Runs before the first-person hand and item are drawn; a listener could cancel it to hide the hand. Hand hiding today goes through `HideHandEvent` in `OptionsHook`.

Idea: Viewmodel replacement, hiding the hand per condition.

Signature path in `Sigs.json`: `mc/client/renderer/game/ItemInHandRenderer/renderFirstPerson`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 18 02 00 00 48 8D AC 24 80 00 00 00 44 0F 29 BD 80 01 00 00 44 0F 29 B5 70 01 00 00 44 0F 29 AD 60 01 00 00 44 0F 29 A5 50 01 00 00 44 0F 29 9D 40 01 00 00 44 0F 29 95 30 01 00 00 44 0F 29 8D 20 01 00 00 44 0F 29 85 10 01 00 00 0F 29 BD 00 01 00 00 0F 29 B5 F0 00 00 00 48 C7 85 E8 00 00 00 FE FF FF FF 44 88 4D 7F"]}
```

Detour as it was:

```cpp
void ItemInHandHook::renderFirstPersonDetour(ItemInHandRenderer* self, BaseActorRenderContext* ctx, const Matrix* prev, ItemContextFlags flags) {
    auto holder = nes::make_holder<RenderItemInHandEvent>(self, nullptr, nullptr, true);
    Eventing::dispatcher().trigger(holder);
    if (holder->isCancelled())
        return;
    mFirstPerson->getOriginal<&renderFirstPersonDetour>()(self, ctx, prev, flags);
}
```

Event:

```cpp
// Hand render gate: hooks dispatch, modules cancel.
struct RenderItemInHandEvent : CancelableEvent {
    void* renderer = nullptr;
    void* entity = nullptr;
    const void* item = nullptr;
    bool firstPerson = false;
    RenderItemInHandEvent() = default;
    RenderItemInHandEvent(void* r, void* e, const void* i, bool fp)
        : renderer(r), entity(e), item(i), firstPerson(fp) {}
};
```


## NetworkHook (3 of 4 detours; ConnectionRequest::create stays): RakNet

### `RakPeer::GetAveragePing`

Runs after the original; reports the RakNet average ping.

Idea: Ping readout. Add lowest, variance and loss for a fuller network panel.

Signature path in `Sigs.json`: `mc/deps/raknet/RakPeer/GetAveragePing`

```json
{"priority": "high", "sigs": ["48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 31 E0 48 89 84 24 ?? ?? ?? ?? 4C 8B 02 4C 3B 05 ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 0F B7 42 ?? 44 0F B7 82 ?? ?? ?? ?? 44 0F B7 8A ?? ?? ?? ?? 66 89 44 24 ?? 0F 10 42 ?? 0F 10 4A ?? 0F 10 52 ?? 0F 10 5A ?? 0F 11 44 24 ?? 0F 11 4C 24 ?? 0F 11 54 24 ?? 0F 11 5C 24 ?? 0F 10 42 ?? 0F 11 44 24 ?? 0F 10 42 ?? 0F 11 44 24 ?? 0F 10 42 ?? 0F 11 84 24 ?? ?? ?? ?? 0F 10 82 ?? ?? ?? ?? 0F 11 84 24 ?? ?? ?? ?? 66 44 89 8C 24 ?? ?? ?? ?? 66 44 89 84 24 ?? ?? ?? ?? 48 8D 54 24 ?? 45 31 C0 45 31 C9 E8 ?? ?? ?? ?? BA"]}
```

Detour as it was:

```cpp
int NetworkHook::averagePing(void* peer, char* guid) {
    int ping = mAveragePing->getOriginal<&averagePing>()(peer, guid);
    Eventing::trigger<AveragePingEvent>(ping);
    return ping;
}
```

Event:

```cpp
struct AveragePingEvent : Event {
    int ping;
    explicit AveragePingEvent(int p) : ping(p) {}
};
```

### `RakNet::RakPeer_runUpdateCycle`

Cancelable. Runs on every RakNet update cycle (a network thread, called constantly).

Idea: Network-thread heartbeat for a diagnostic. Never allocate or log in it.

Signature path in `Sigs.json`: `mc/deps/raknet/RakNet/RakPeer_runUpdateCycle`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 B8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 29 C4 48 8D AC 24 ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 48 89 95 ?? ?? ?? ?? 49 89 CF"]}
```

Detour as it was:

```cpp
bool NetworkHook::updateCycle(void* peer, void* a2) {
    auto holder = nes::make_holder<RunUpdateCycleEvent>(peer);
    Eventing::dispatcher().trigger(holder);
    if (holder->isCancelled())
        return false;
    return mUpdateCycle->getOriginal<&updateCycle>()(peer, a2);
}
```

Event:

```cpp
struct RunUpdateCycleEvent : CancelableEvent {
    void* peer;
    explicit RunUpdateCycleEvent(void* p) : peer(p) {}
};
```

### `RakNet::RakPeer_sendImmediate`

Cancelable. Runs before every raw send; `send[0]` is the RakNet packet id.

Idea: Read-only packet logging for debugging.

Signature path in `Sigs.json`: `mc/deps/raknet/RakNet/RakPeer_sendImmediate`

```json
{"priority": "high", "sigs": ["41 57 41 56 41 55 41 54 56 57 55 53 48 81 EC ?? ?? ?? ?? 44 89 CF 44 89 C3"]}
```

Detour as it was:

```cpp
uint64_t NetworkHook::sendImmediate(uint64_t a1, char* send, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7, uint64_t a8, uint64_t a9, uint64_t a10) {
    auto holder = nes::make_holder<SendImmediateEvent>(send);
    Eventing::dispatcher().trigger(holder);
    if (holder->isCancelled())
        return 0;
    return mSendImmediate->getOriginal<&sendImmediate>()(a1, send, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
```

Event:

```cpp
struct SendImmediateEvent : CancelableEvent {
    char* send; // send[0] is the RakNet packet id
    explicit SendImmediateEvent(char* s) : send(s) {}
};
```


## PlayerHook (2 of 3 detours; Item::getSwingDuration stays): Local player

### `Actor::attack`

Runs when the local player attacks a target (the detour filters on `self == local player`).

Idea: Hit counter, combo display, hit sound.

Signature path in `Sigs.json`: `mc/world/actor/Actor/attack`

```json
{"priority": "high", "sigs": ["55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 4D 89 CF 4D 89 C6 48 89 D6 48 89 CF 41 8B 80"]}
```

Detour as it was:

```cpp
void* PlayerHook::attack(Actor* self, void* ret, Actor* target, void* cause, void* a4) {
    if (reinterpret_cast<void*>(self) == reinterpret_cast<void*>(ClientInstance::get()->getLocalPlayer()))
        Eventing::trigger<AttackEvent>(target);
    return mAttack->getOriginal<&attack>()(self, ret, target, cause, a4);
}
```

Event:

```cpp
#include "sdk/mc/world/actor/Actor.h"

struct AttackEvent : Event {
    Actor* target;
    explicit AttackEvent(Actor* t) : target(t) {}
};
```

### `LocalPlayer::applyTurnDelta`

Runs before mouse look is applied; listeners could edit the delta (`Vec2&`).

Idea: Sensitivity curve, smoothing, zoom, cinematic camera.

Signature path in `Sigs.json`: `mc/client/player/LocalPlayer/applyTurnDelta`

```json
{"priority": "high", "sigs": ["55 41 56 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 44 0F 29 5D ?? 44 0F 29 55 ?? 44 0F 29 4D ?? 44 0F 29 45 ?? 0F 29 7D ?? 0F 29 75 ?? 48 C7 45 ?? ?? ?? ?? ?? 48 89 D7 48 89 CE 48 8B 89"]}
```

Detour as it was:

```cpp
void PlayerHook::turnDelta(void* self, Vec2& delta) {
    Eventing::trigger<TurnDeltaEvent>(delta);
    mTurnDelta->getOriginal<&turnDelta>()(self, delta);
}
```

Event:

```cpp
struct TurnDeltaEvent : Event {
    Vec2& delta;
    explicit TurnDeltaEvent(Vec2& d) : delta(d) {}
};
```


## Other removals

- `BoneRenderEvent`: declared but never triggered by any hook. Removed.
- Events that still have a hook but no listener (`GammaEvent`, `PerspectiveEvent`, `BlockChangedEvent`, `ShadowRadiusEvent`, `InterpolatedRotEvent`, `LevelTickEvent`, `PacketPostOutEvent`) were kept for now, because their hooks also do other work. They are candidates for the skip-dispatch-when-no-listener change.
