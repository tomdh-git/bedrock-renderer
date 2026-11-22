#pragma once
#include "client/features/render/tracker/MatRole.h"

struct IDXGISwapChain;
struct ID3D12CommandList;
struct ID3D12CommandQueue;

// What the hooks know about one recorded command list (always collected; the UnderUI layer decides with it).
struct ListFacts {
    uintptr_t rtRes = 0;      // resource of the first render target bound (0: its view predates the injection)
    uintptr_t rtHandle = 0;   // that render target view's descriptor handle
    uintptr_t rtAll[8] = {};  // resources of every render target of that first bind (0: unknown)
    uint8_t rtCount = 0;
    bool colorClear = false;
    bool depthClear = false;
    bool acquired = false;    // transitions a swapchain buffer PRESENT -> RENDER_TARGET
    bool flatPso = false;     // the pipeline state in force: depth test off, no blending
    uint32_t draws = 0;
    uint32_t firstElements = 0;
    bool quad = false;        // the first draw is 6 elements, not with a pipeline state known to be anything but flat (a full-screen pass)
    bool psoKnown = false;    // the pipeline state in force was created after we hooked, so its properties are known
    bool blendPso = false;    // the state of the last draw blends
    bool flatBlendPso = false; // the state in force: depth test off and blending (drawn over the scene whatever is in front of it: the game's through-wall nametags)
    bool celPso = false;      // that state is one of the sky bodies' (sun and moon, or stars): depth tested, no depth write, blended source-alpha/one or inv-dest-colour/one
    bool posUvPso = false;    // the state in force takes vertices of (position, uv) and nothing else: what a face of a sky box is drawn with
    bool writePso = false;    // the state in force is depth tested AND writes depth (world geometry)
    bool actorPso = false;    // the state in force takes skinned meshes (vertices with bone indices): entities, armor, the item in hand
    uint32_t blendDraws = 0;  // draws made with a state that blends (translucent geometry: water, glass, particles)
    uint32_t flatBlendDraws = 0; // draws made with such a state
    uint32_t actorDraws = 0;  // draws made with such a state
    uint32_t playerDraws = 0; // draws recorded while the game was rendering the local player (ActorRenderDispatcher::render of that entity, on the recording thread)
    uint32_t writeDraws = 0;  // draws made with such a state
    uint32_t terrainBlendDraws = 0; // terrain draws with a blending state (leaves, water, glass: no depth written)
    uint32_t cubeDraws = 0;   // draws of a single 6-element quad, depth tested without writing depth, vertices (position, uv): a face of a sky box
    uint32_t unknownDraws = 0; // draws made with a state we never saw created
    MatRole curRole = MatRole::Unknown;      // what the state in force is (by its shaders' material; Unknown for a state we never saw created)
    uint32_t roleDraws[kMatRoles] = {};      // draws by what they are: told exactly from the material, not from the shape of the list
    uint32_t bodyDraws = 0;   // draws made with such a state
    uint32_t totalElements = 0, maxElements = 0; // vertices/indices drawn by the list, in all and in its largest draw
    uint32_t sixDraws = 0;    // draws of a single 6-element quad with a state we never saw created (could be the sun or the moon)
    uintptr_t psoFirst = 0, psoLast = 0; // the first and the last pipeline state the list set: the same objects in every frame (what the list is, whatever it draws this time)
    // What this list was found to be over many frames (UnderUI keeps the votes by the pipeline states above): -1 not decided yet, 0 no, 1 yes. A list that holds
    // the sun and the moon in one direction and nothing in another is the same list.
    int8_t stickyBodies = -1, stickyCube = -1;
    // Every draw is a face of a sky box (a texture pack's sky): by the Cubemap materials; failing that (a state we never saw created) by the shape, six quads.
    bool rawSkyCube() const { return draws > 0 && draws <= 6 && roleDraws[static_cast<int>(MatRole::Cubemap)] + cubeDraws == draws; }
    // Every draw of the list is the sun, the moon or the stars: by their materials; failing that, by the shape (a state we never saw created: a lone 6-element quad).
    bool rawSkyBodies() const { return draws > 0 && roleDraws[static_cast<int>(MatRole::SunMoon)] + roleDraws[static_cast<int>(MatRole::Stars)] + bodyDraws + sixDraws == draws; }
    bool skyCube() const { return stickyCube >= 0 ? stickyCube == 1 : rawSkyCube(); }
    bool skyBodies() const { return stickyBodies >= 0 ? stickyBodies == 1 : rawSkyBodies(); }
    uint32_t roleCount(MatRole r) const { return roleDraws[static_cast<int>(r)]; }
    uintptr_t dsRes = 0;      // resource of the depth view bound with the first render target (0: none or unknown)
    uint32_t clearFlags = 0;  // D3D12_CLEAR_FLAG bits of the depth/stencil clears (1 depth, 2 stencil)
    std::vector<std::pair<uintptr_t, uint32_t>> transitions; // resource -> state after, in recording order
    std::vector<D3D12_RESOURCE_BARRIER> barriers;            // the transition barriers themselves, as recorded: a list that is left out has them replayed in its place

    // Back to the state a freshly constructed ListFacts has, keeping every container's capacity: facts() hands the previous frame's
    // facts back to the tracker's map and the next recording fills them again.
    void reset() {
        rtRes = 0;
        rtHandle = 0;
        for (auto& r : rtAll)
            r = 0;
        rtCount = 0;
        colorClear = false;
        depthClear = false;
        acquired = false;
        flatPso = false;
        draws = 0;
        firstElements = 0;
        quad = false;
        psoKnown = false;
        blendPso = false;
        flatBlendPso = false;
        celPso = false;
        posUvPso = false;
        writePso = false;
        actorPso = false;
        blendDraws = 0;
        flatBlendDraws = 0;
        actorDraws = 0;
        playerDraws = 0;
        writeDraws = 0;
        terrainBlendDraws = 0;
        cubeDraws = 0;
        unknownDraws = 0;
        curRole = MatRole::Unknown;
        for (auto& r : roleDraws)
            r = 0;
        bodyDraws = 0;
        totalElements = 0;
        maxElements = 0;
        sixDraws = 0;
        psoFirst = 0;
        psoLast = 0;
        stickyBodies = -1;
        stickyCube = -1;
        dsRes = 0;
        clearFlags = 0;
        transitions.clear();
        barriers.clear();
    }
};

// What the game's renderer does on the GPU queue, watched through the D3D12 objects themselves (device view creation, command list recording,
// queue submission): it needs nothing from the game's bgfx internals and sees every render mode the same way. UnderUI decides from the
// per-list facts which of the game's lists is the sky, the scene, the HUD.
struct CommandListTracker {
    static void init();                   // dummy D3D12 objects -> vtable detours (HookManager time)
    static void shutdown();               // remove the detours (D3DHook::shutdown)
    static bool facts(ID3D12CommandList* list, ListFacts& out);
    static void forgetOwnDepth();         // the swapchain was resized: the depth view learned and our depth buffer are the old one's
    static bool isSwapchain(const ListFacts& f);
    static uintptr_t frameTarget();
    static void onPresent(IDXGISwapChain* sc); // Present detour, before our own overlay draws: the swapchain buffers, the profiler frame, UnderUI polling
};
