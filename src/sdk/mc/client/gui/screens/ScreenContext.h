#pragma once
#include "sdk/Layout.h"
#include "sdk/mc/client/gui/screens/UIScreenContext.h"
// Member order: UIScreenContext base (xm/ym/a) + MeshContext base (omitted) +
// frameBufferObject, viewport, guiData, clock, tessellator, minecraftGraphics,
// profanityContext, frameDiscardContext, isCapturingPanorama, commandListQueue,
// frameAllocator. Ctor/dtor-thunks omitted (game-side only).
// Offsets unproven; all accessors below are TODO stubs,
// null-guarded defaults, no invented offsets, no garbage reads.
struct Tessellator;
struct GuiData;

struct ScreenContext : UIScreenContext {
    Tessellator* getTessellator() {
        sdkLogStub("ScreenContext::getTessellator");
        return nullptr;
    }
    GuiData* getGuiData() {
        sdkLogStub("ScreenContext::getGuiData");
        return nullptr;
    }
    // TODO: picks in member order when a caller needs them, each with a proven
    // offset first: frameBufferObject, viewport, clock, minecraftGraphics,
    // profanityContext, frameDiscardContext, panorama flag, commandQueue,
    // frameAllocator.
};
