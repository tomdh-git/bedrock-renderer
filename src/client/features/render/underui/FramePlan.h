#pragma once
#include "client/features/render/underui/UnderTypes.h"
#include "client/features/render/tracker/CommandListTracker.h"

// Where UnderUI's layers go in one frame: the cuts between the lists the game submits, found from what each list did (ListFacts). A cut is an index:
// the layer is recorded after that list. Regular rendering and Vibrant Visuals lay their frames out differently; this knows both.
struct FramePlan {
    int b1 = -1, b2 = -1;   // regular: the depth-only clear that starts the UI; Vibrant Visuals: the tonemap composite
    int scene = -1;         // split after this list: over the 3D scene, under the UI
    UnderTarget sceneTarget;
    int sky = -1;           // split after this list: the sky
    UnderTarget skyTarget;
    int fog = -1;           // split after this list: the distance fog (once the world is drawn)
    UnderTarget fogTarget;
    int actorBefore = -1;   // split after this list: the world as it is before the game draws its entities
    int actorAfter = -1;    // split after this list: the entities are drawn
    UnderTarget actorTarget;
    int entityBefore = -1;  // split after this list: before ANY list with an entity draw (regular rendering; the local player's or not)
    UnderTarget entityTarget;
    int entityAfter = -1;   // split after this list: after the last list with an entity draw (the pair of entityBefore)
    int post = -1;          // split after this list: post-processing of the finished 3D scene (its depth, and the game's motion vectors, still readable)
    UnderTarget postTarget;
    int nameTagAfter = -1;  // the index of the last list that draws a nametag: the cut after it (the nametags are on the screen) is where the nametag blur goes
    int nameTag = -1;       // the index of the first list that draws a nametag; the Fog and Post cuts move before it, so the nametags are drawn after our passes (they stay sharp over the blur)

    static FramePlan analyze(UINT n, const std::vector<ListFacts>& f, const std::vector<char>& known);
    static DXGI_FORMAT formatOf(uintptr_t res); // the format of a resource (UNKNOWN for none)

private:
    struct Analysis;
};
