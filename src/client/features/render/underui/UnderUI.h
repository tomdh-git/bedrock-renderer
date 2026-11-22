#pragma once

#include "client/features/render/underui/UnderTypes.h"

struct ListFacts;

namespace Render {



// A pass's settings as the render thread sees them. The module's own settings belong to the UI and the Present thread; poll() publishes a copy once a frame
// (`publish(module->enabled, Cfg{...})`) and wanted()/record() read it with get() / on(), whole, under the lock.
template <typename Cfg>
class PassSettings {
public:
    void publish(bool on, const Cfg& cfg) {
        std::lock_guard<std::mutex> lk(mMutex);
        mOn = on;
        mCfg = cfg;
    }
    Cfg get() const {
        std::lock_guard<std::mutex> lk(mMutex);
        return mCfg;
    }
    bool on() const {
        std::lock_guard<std::mutex> lk(mMutex);
        return mOn;
    }

private:
    mutable std::mutex mMutex;
    bool mOn = false;
    Cfg mCfg{};
};

// Something drawn into the game's frame at one of UnderUI's layers (passes/: the sky and the fog, the motion blur, the ImGui background list).
// UnderUI decides WHERE (the cut between two of the game's lists, the resource states there); a pass decides WHAT, and records its own list
// into the queue through `run`. Passes are added once at startup (UnderPasses::install) and live as long as the DLL.
struct UnderPass {
    // Order matters: passes at the same cut go in this order.
    enum class Layer {
        Sky = 0,       // over the cleared frame / the game's own sky, under all world geometry
        Fog = 1,       // the end of the world: over the terrain, while the scene's depth is still there
        UnderActors = 2, // just before the game draws its entities: the screen is the world without them (regular rendering, where they have lists of their own)
        AfterActors = 3, // just after the last of those lists: the entities are on the screen
        PostScene = 4,   // over the finished 3D scene, its depth (and the game's motion vectors) still readable: post-processing
        Scene = 5,       // over the 3D scene, under the game's UI
        UnderEntities = 6, // before the FIRST list that draws any entity at all (UnderActors goes around the local player's lists when the game records those apart, for the blur): everything
                           // entity-shaped that is drawn after it covers what is drawn here, with its own silhouette. Regular rendering only.
        AfterEntities = 7, // after the LAST list that draws any entity (before the cut of the finished scene): the pair of UnderEntities, the entities are on the screen. Regular rendering only.
        AfterNameTags = 8, // after the LAST list that draws a nametag (the game draws them after the finished scene, over the blur): the nametags are on the screen, on the finished scene's target
    };
    virtual ~UnderPass() = default;
    virtual Layer layer() const = 0;
    virtual const char* name() const = 0;
    virtual void poll() {}                                // Present thread, once a frame: read settings
    virtual bool wanted() { return false; }                // render thread, per frame: cut this layer into the frame
    // Present thread, per frame, before the next frame is recorded: may this pass want a cut (or hide something) while its published settings say so? Cheap and
    // side-effect free: it is what turns the command-list tracker on. Conservative by design (true costs a tracked frame, false would lose one).
    virtual bool tracking() const { return false; }
    virtual bool needsProjection() const { return false; } // the pass wants the frame's near and far plane
    virtual bool needsDepth() const { return false; }      // the pass reads the scene's depth: the engine finds it even when the game's view of it is unknown
    virtual bool hidesSkyBodies() const { return false; }  // the sun and the moon of the game's own sky are not submitted
    virtual void record(ID3D12CommandQueue* queue, UnderExec run, const UnderTarget& target) = 0;
    virtual void report(UnderStats&) {}                    // every few seconds: the pass's numbers (and a line in the log if it has something to say)
    virtual void dropTargets() {}                          // before the game resizes its buffers: no list of ours may still reference them
    virtual void shutdown() {}                             // release the pass's D3D12 objects
};

// Draws our own passes into the game's frame in layers, in every render mode.
struct UnderUI {
    using ExecFn = UnderExec;
    static void add(UnderPass* pass);   // the install (UnderPasses::install) appends here
    static void markPassesReady();      // the install finished: poll/execute may read the pass list from here on
    static void poll(HWND foreground);               // Present thread: passes' settings, the camera of the frame, keys
    static void execute(ID3D12CommandQueue* queue, UINT n, ID3D12CommandList* const* lists, ExecFn run); // render thread
    static void stopBuilder();                       // eject, first thing: the background shader builder ends (nothing of ours may be inside the DLL)
    static void shutdown();                          // release our D3D12 objects
    static void dropTargets();                       // before the game resizes its buffers: our last list no longer references them
    using Stats = UnderStats;
    static bool worldReady();                        // a world is on screen (not its loading screen): the sky and the item in hand start here
    static Stats stats();                            // what the last few seconds cost (the same numbers the log prints)

private:
    static std::vector<UnderPass*> sPasses; // in the order they were added
    // The install thread appends sPasses while the present/render threads are already inside poll/execute
    // (the hooks go live before the install): closed gate, no touch. markPassesReady's release pairs
    // with the acquire loads, so a pass the gate lets through is fully constructed, with its shaders.
    static std::atomic<bool> sPassesReady;
    static std::mutex sStatsMu;
    static UnderStats sStatsOut; // the last window's cost, for the debug UI's profiler
    static void followStates(const std::vector<ListFacts>& f, const std::vector<char>& known, UINT from, UINT to);
    static double sCpuMs;
    static double sSceneMs; // what the layers cost, summed over the frames since the last report
    static UINT sFrames;
    static ULONGLONG sNextLog;
    struct Cut;
    struct Frame;
    static void reportCosts(uint64_t t0, UINT n);
};

} // namespace Render
