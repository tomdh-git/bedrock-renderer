#include "client/features/render/underui/UnderUI.h"
#include "client/features/render/underui/FramePlan.h"
#include "sdk/mc/client/gui/ScreenNames.h"
#include "client/features/render/underui/UnderGpu.h"
#include "client/features/render/tracker/CommandListTracker.h"
#include "client/features/render/lce/Renderer.h"
#include "client/features/render/chams/Renderer.h"
#include "client/features/render/underui/MenuBackground.h"
#include "client/features/hooks/hooks/render/SetupAndRenderHook.h"
#include "client/features/hooks/hooks/render/FrameFilterHook.h"
#include "client/core/diagnostics/Profiler.h"
#include "client/platform/time/Time.h"

namespace Render {



std::vector<UnderPass*> UnderUI::sPasses; // in the order they were added
std::atomic<bool> UnderUI::sPassesReady{false};
std::mutex UnderUI::sStatsMu;
UnderStats UnderUI::sStatsOut; // the last window's cost, for the debug UI's profiler

// ---- where the layers go ---------------------------------------------------------------------------------------------
void UnderUI::followStates(const std::vector<ListFacts>& f, const std::vector<char>& known, UINT from, UINT to) {
    for (UINT i = from; i < to; ++i)
        if (known[i])
            for (auto& [res, state] : f[i].transitions)
                UnderGpu::state[res] = state;
}


void UnderUI::add(UnderPass* pass) {
    sPasses.push_back(pass);
}

void UnderUI::markPassesReady() {
    sPassesReady.store(true, std::memory_order_release); // the last append (and every pass's setup) happened-before this
}

void UnderUI::poll(HWND foreground) {
    // The install has not finished: the passes do not exist yet (their polls touch modules and the game
    // global), and sPasses itself is still being appended to. inWorld keeps its menu default, which is
    // where an injection-time frame is anyway; the camera facts catch up on the first poll after the gate.
    if (!sPassesReady.load(std::memory_order_acquire))
        return;
    // In a world only once the game itself says so: a player exists while the loading screen is still up, and the sky and the item in hand
    // would start under it. The screen the game shows is the signal (a loading, saving or connecting screen is not the world), both ways. The game's own
    // pages (ui://..., the pause menu among them) are screens over the world like any other: a player and no loading screen is the world.
    ClientInstance* ci = ClientInstance::get();
    {
        bool live = false;
        if (ci && ci->getLocalPlayer() && !ci->isPreGame()) { // the game's own word for "no level": a player object can outlive a left server while its pages are still up
            const std::string name = ci->getScreenName();
            const bool loadingScreen = name.find("loading") != std::string::npos || name.find("progress") != std::string::npos;
            // a loading screen while already in the world (the pause menu's Settings has a short one) is not leaving it: only the join starts on one
            live = !name.empty() && name != ScreenNames::kStart && (!loadingScreen || UnderGpu::inWorld.load());
        }
        UnderGpu::inWorld.store(live);
    }

    bool projection = false;
    for (UnderPass* p : sPasses) {
        p->poll();
        projection |= p->needsProjection();
    }

    SetupAndRenderHook::advance(); // idempotent with ESP's call: the transform of the frame being presented
    const auto& t = SetupAndRenderHook::transform;
    UnderCamera c = UnderGpu::cameraOf(t);
    c.seq = SetupAndRenderHook::transformSeq;
    UnderGpu::setCamera(c);
    // The near and far plane, from the level renderer's projection matrix every frame (the far plane follows the render distance); the client
    // instance is searched for one only when that is not a projection.
    if (projection && !(c.valid && UnderGpu::setProjection(t.proj)) && UnderGpu::nearPlane.load() == 0.f)
        UnderGpu::discoverProjection(foreground);
}

double UnderUI::sCpuMs = 0;
double UnderUI::sSceneMs = 0; // what the layers cost, summed over the frames since the last report
UINT UnderUI::sFrames = 0;
ULONGLONG UnderUI::sNextLog = 0;

// A pass and where it goes in this frame: after list `after`.
struct UnderUI::Cut {
    int after;
    UnderPass* pass;
    UnderTarget target;
};

// One frame the game submits as `n` command lists. The steps run in the order UnderUI::execute calls them.
struct UnderUI::Frame {
    ID3D12CommandQueue* q;
    UINT n;
    ID3D12CommandList* const* lists;
    UnderUI::ExecFn run;
    // The frame's scratch, kept on the render thread across frames: resize() keeps the elements, assign() keeps the capacity, and each
    // ListFacts::reset() keeps the strings and vectors inside it, so a frame with the same number of lists allocates nothing here.
    static inline thread_local std::vector<ListFacts> f;
    static inline thread_local std::vector<char> known;
    static inline thread_local std::vector<char> on; // the passes that want this frame
    static inline thread_local std::vector<char> skip;
    static inline thread_local std::vector<Cut> cuts;
    bool any = false, hide = false;
    FramePlan plan;

    void readFacts() {
        for (UINT i = 0; i < n; ++i)
            known[i] = CommandListTracker::facts(lists[i], f[i]);
        rememberLists();
    }

    // A list is told by the pipeline states it uses, which are the same objects in every frame: what a frame's draws look like (the sun and the moon are in the
    // list only while they are in view, a star list is one big draw) can say "the sun and moon list" in one frame and "something else" in the next. So every frame
    // with draws is a vote, by those objects, and a list that has been told the same way most of the time stays that way.
    struct Votes {
        uint16_t bodies = 0, notBodies = 0, cube = 0, notCube = 0;
    };

    static int8_t decide(uint16_t yes, uint16_t no) {
        if (yes + no < 6)
            return -1; // too few frames to tell
        if (yes >= 3 * no)
            return 1;
        if (no >= 3 * yes)
            return 0;
        return -1;
    }

    void rememberLists() {
        static std::unordered_map<uint64_t, Votes> sVotes;
        for (UINT i = 0; i < n; ++i) {
            ListFacts& l = f[i];
            if (!known[i] || l.draws == 0 || !l.psoFirst)
                continue;
            const uint64_t key = static_cast<uint64_t>(l.psoFirst) * 0x9E3779B97F4A7C15ull ^ static_cast<uint64_t>(l.psoLast) * 0xC2B2AE3D27D4EB4Full ^ (CommandListTracker::isSwapchain(l) ? 1ull : 0ull);
            Votes& v = sVotes[key];
            (l.rawSkyBodies() ? v.bodies : v.notBodies)++;
            (l.rawSkyCube() ? v.cube : v.notCube)++;
            if (v.bodies + v.notBodies > 400) { // old frames fade
                v.bodies /= 2; v.notBodies /= 2;
            }
            if (v.cube + v.notCube > 400) {
                v.cube /= 2; v.notCube /= 2;
            }
            l.stickyBodies = decide(v.bodies, v.notBodies);
            l.stickyCube = decide(v.cube, v.notCube);
        }
    }

    void askPasses() {
        bool wantDepth = false;
        for (size_t i = 0; i < sPasses.size(); ++i) {
            on[i] = sPasses[i]->wanted();
            any |= on[i] != 0;
            hide |= sPasses[i]->hidesSkyBodies();
        }
        for (size_t i = 0; i < sPasses.size(); ++i)
            wantDepth |= on[i] && sPasses[i]->needsDepth();
        // Which depth buffer the game's swapchain pass draws into is switched at that pass's depth clear, and the lists of a frame are recorded on several threads:
        // a switch while a frame is being recorded can leave some of its lists on the game's buffer and the rest on ours (entities and nametags drawn through the
        // terrain for a frame), and a pass that wants the depth on the frame it comes on finds a buffer nothing has been drawn into yet. Passes come and go with what
        // is on screen (the smoke, a blur only while the camera moves), so the want is held: once any pass has wanted the depth it stays ours for ten seconds after
        // the last one that did, and a pass that comes back within that time finds this frame's depth. Drawing into our buffer costs the game nothing.
        static ULONGLONG sDepthHeldUntil = 0;
        const ULONGLONG nowMs = Platform::Time::millis();
        if (wantDepth)
            sDepthHeldUntil = nowMs + 10000;
        UnderGpu::ownDepthWanted.store(wantDepth || nowMs < sDepthHeldUntil);
    }

    void makePlan() {
        if ((any || hide) && n >= 4)
            plan = FramePlan::analyze(n, f, known);
        // Diagnosing a menu without its shader: one line each time the facts that decide it change.
        bool skyWanted = false;
        for (size_t i = 0; i < sPasses.size(); ++i)
            skyWanted |= on[i] && sPasses[i]->layer() == UnderPass::Layer::Sky;
        // The facts are packed into one number and compared every frame; the line is only formatted when they change.
        static uint64_t sPrev = ~0ull;
        static int sLines = 0;
        if ((any || hide) && n >= 4 && sLines < 30) { // full frames only: the short ones (UI alone) are not the world's picture and alternate with them
            const bool inWorld = UnderGpu::inWorld.load(), skyCut = plan.sky >= 0, builderHooked = FrameFilterHook::active();
            const int menuBackground = MenuBackground::index();
            const uint64_t now = (static_cast<uint64_t>(static_cast<uint32_t>(menuBackground)) << 8) | (inWorld ? 1u : 0u) | (skyWanted ? 2u : 0u) | (any ? 4u : 0u) | (hide ? 8u : 0u) |
                                 (skyCut ? 16u : 0u) | (builderHooked ? 32u : 0u);
            if (now != sPrev) {
                sPrev = now;
                ++sLines;
                Logger::info("[underui] menu shader state: inWorld {} menuBackground {} skyPassWanted {} anyPass {} hide {} skyCutFound {} frameBuilderHooked {}", inWorld, menuBackground, skyWanted,
                             any, hide, skyCut, builderHooked);
            }
        }
    }

    // The sun, the moon, the stars and a texture pack's sky box are left out of the frame by the frame builder hook (SkyPass tells it which): they are not in the frame at all.
    // There is no fallback that guesses lists by their shape; a hook that does not work is reported, once, so it gets fixed.
    void findSkipped() {
        bool skyWanted = false;
        for (size_t i = 0; i < sPasses.size(); ++i)
            skyWanted |= on[i] && sPasses[i]->layer() == UnderPass::Layer::Sky;
        static bool sReported = false;
        if ((hide || skyWanted) && n >= 4 && UnderGpu::inWorld.load() && !FrameFilterHook::active() && !sReported) {
            sReported = true;
            Logger::error("[underui] the frame builder hook is not active: the sky bodies are not being removed from the frame");
        }
    }

    void replayBarriers(const ListFacts& l) {
        if (l.barriers.empty())
            return;
        UnderGpu::ensure(q);
        UnderGpu::beginList(nullptr);
        UnderGpu::list->ResourceBarrier(static_cast<UINT>(l.barriers.size()), l.barriers.data());
        UnderGpu::submit(q, run);
    }

    // Lists [from, to), without the skipped ones, submitted in runs.
    void runRange(UINT from, UINT to) {
        if (to > skip.size() || to > n)
            Logger::error("[underui] runRange {}..{}: {} lists in this frame, skip has {}, f has {}, known {}, cuts {} (thread {})", from, to, n, skip.size(), f.size(), known.size(), cuts.size(),
                          GetCurrentThreadId());
        UINT i = from;
        while (i < to) {
            if (skip[i]) {
                replayBarriers(f[i]);
                ++i;
                continue;
            }
            UINT j = i;
            while (j < to && !skip[j])
                ++j;
            {
                BS_PROFILE("underui", "game lists: ExecuteCommandLists");
                run(q, j - i, lists + i);
            }
            i = j;
        }
    }

    // The cut a layer has in this frame, if it has one.
    bool cutFor(UnderPass::Layer layer, int& after, UnderTarget& target) const {
        switch (layer) {
        case UnderPass::Layer::Sky: after = plan.sky; target = plan.skyTarget; return plan.sky >= 0;
        case UnderPass::Layer::Fog: after = plan.fog; target = plan.fogTarget; return plan.fog >= 0 && plan.fogTarget.depth;
        case UnderPass::Layer::UnderActors: after = plan.actorBefore; target = plan.actorTarget; return plan.actorBefore >= 0;
        case UnderPass::Layer::AfterActors: after = plan.actorAfter; target = plan.actorTarget; return plan.actorBefore >= 0;
        case UnderPass::Layer::PostScene: after = plan.post; target = plan.postTarget; return plan.post >= 0;
        case UnderPass::Layer::Scene: after = plan.scene; target = plan.sceneTarget; return plan.scene >= 0;
        case UnderPass::Layer::UnderEntities: after = plan.entityBefore; target = plan.entityTarget; return plan.entityBefore >= 0;
        case UnderPass::Layer::AfterNameTags: after = plan.nameTagAfter; target = plan.postTarget; return plan.nameTagAfter >= 0 && plan.post >= 0 && plan.nameTagAfter > plan.post;
        case UnderPass::Layer::AfterEntities: after = plan.entityAfter; target = plan.entityTarget; return plan.entityBefore >= 0 && plan.entityAfter >= 0;
        }
        return false;
    }

    // Passes at the same cut run in this order: the two pictures of the entities (before, after) must be taken around the entity lists and nothing of ours, so the fog,
    // which changes the pixels of the terrain inside the player's box, comes after the second one.
    static int orderAtCut(UnderPass::Layer layer) {
        switch (layer) {
        case UnderPass::Layer::Sky: return 0;
        case UnderPass::Layer::UnderActors: return 1;
        case UnderPass::Layer::UnderEntities: return 2; // after the blur's picture of the world without the actors: our list is not in it
        case UnderPass::Layer::AfterActors: return 3;
        case UnderPass::Layer::AfterEntities: return 3; // before the fog too: the second picture is of the entities and nothing of ours
        case UnderPass::Layer::Fog: return 4;
        case UnderPass::Layer::PostScene: return 5;
        case UnderPass::Layer::AfterNameTags: return 6;
        case UnderPass::Layer::Scene: return 7;
        }
        return 7;
    }

    // Where each wanted pass goes, in the order they run: by list, then by layer.
    void placePasses() {
        for (size_t i = 0; i < sPasses.size(); ++i) {
            int after = -1;
            UnderTarget target;
            if (on[i] && cutFor(sPasses[i]->layer(), after, target))
                cuts.push_back({after, sPasses[i], target});
        }
        std::stable_sort(cuts.begin(), cuts.end(), [](const Cut& a, const Cut& b) {
            return a.after != b.after ? a.after < b.after : orderAtCut(a.pass->layer()) < orderAtCut(b.pass->layer());
        });
    }

    void record(const Cut& c) {
        BS_CHECK(c.target.rt);
        if (c.pass->layer() != UnderPass::Layer::Scene)
            return c.pass->record(q, run, c.target);
        const uint64_t t0 = Platform::Time::ticks();
        c.pass->record(q, run, c.target);
        sSceneMs += Platform::Time::msSince(t0);
    }

    // The game's lists up to each cut, then the pass of that cut; the rest of the lists last.
    void submit() {
        UINT cursor = 0;
        for (const Cut& c : cuts) {
            const UINT upto = static_cast<UINT>(c.after) + 1;
            if (upto > n)
                Logger::error("[underui] cut after list {} of {} lists (layer {}): plan sky {} fog {} actors {}..{} entities {} post {} scene {}", c.after, n, static_cast<int>(c.pass->layer()),
                              plan.sky, plan.fog, plan.actorBefore, plan.actorAfter, plan.entityBefore, plan.post, plan.scene);
            if (upto > cursor) {
                runRange(cursor, upto);
                followStates(f, known, cursor, upto);
                cursor = upto;
            }
            record(c);
        }
        if (cursor < n) {
            runRange(cursor, n);
            followStates(f, known, cursor, n);
        }
    }
};

// What this costs, every few seconds, for frames that are a whole game frame.
void UnderUI::reportCosts(uint64_t t0, UINT n) {
    if (n < 8)
        return;
    sCpuMs += Platform::Time::msSince(t0);
    ++sFrames;
    const ULONGLONG now = Platform::Time::millis();
    if (now < sNextLog)
        return;
    UnderStats st;
    st.cpuMs = sCpuMs / sFrames;
    st.sceneMs = sSceneMs / sFrames;
    for (UnderPass* p : sPasses)
        p->report(st);
    {
        std::lock_guard<std::mutex> lk(sStatsMu);
        sStatsOut = st;
    }
    sNextLog = now + 5000;
    sCpuMs = sSceneMs = 0;
    sFrames = 0;
    UnderGpu::takeWindow();
}


void UnderUI::execute(ID3D12CommandQueue* q, UINT n, ID3D12CommandList* const* lists, ExecFn run) {
    // The install has not finished: nothing of ours may run in the frame, and sPasses is still being
    // appended to — the game's lists are submitted whole, exactly as they arrived.
    if (!sPassesReady.load(std::memory_order_acquire)) {
        run(q, n, lists);
        return;
    }
    // Our own immediate uploads (a texture made while a pass records, such as the first frame of a newly loaded viewhands model) execute a list on this same hooked queue
    // from inside this function: that call is not a game frame, and sizing the per-frame vectors for it would cut them short under the frame that is still being submitted.
    static thread_local bool tInside = false;
    if (tInside) {
        run(q, n, lists);
        return;
    }
    tInside = true;
    struct Leave { ~Leave() { tInside = false; } } leave;
    BS_PROFILE("underui", "execute (render thread, ours)");
    const uint64_t t0 = Platform::Time::ticks();
    Frame frame{q, n, lists, run};
    {
        BS_PROFILE("underui", "scratch reset");
        Frame::f.resize(n);
        for (auto& l : Frame::f)
            l.reset();
        Frame::known.assign(n, 0);
        Frame::on.assign(sPasses.size(), 0);
        Frame::skip.assign(n, 0);
        Frame::cuts.clear();
        frame.any = frame.hide = false;
        frame.plan = FramePlan{};
    }
    {
        BS_PROFILE("underui", "read command-list facts");
        frame.readFacts();
    }
    {
        BS_PROFILE("underui", "select wanted passes");
        frame.askPasses();
    }
    {
        BS_PROFILE("underui", "analyze frame plan");
        frame.makePlan();
    }
    {
        BS_PROFILE("underui", "find lists to skip");
        frame.findSkipped();
    }
    {
        BS_PROFILE("underui", "place render passes");
        frame.placePasses();
    }
    {
        BS_PROFILE("underui", "submit lists and record passes");
        frame.submit();
    }
    reportCosts(t0, n);
}

bool UnderUI::worldReady() {
    return UnderGpu::inWorld.load();
}

void UnderUI::stopBuilder() {
    UnderGpu::stopBuilder();
}

UnderUI::Stats UnderUI::stats() {
    std::lock_guard<std::mutex> lk(sStatsMu);
    return sStatsOut;
}

void UnderUI::dropTargets() {
    // A resize can land while the install is still appending: no pass has recorded yet (execute submits
    // the game's lists whole), so there is nothing of theirs to drop.
    if (sPassesReady.load(std::memory_order_acquire))
        for (UnderPass* p : sPasses)
            p->dropTargets();
    CommandListTracker::forgetOwnDepth();
    UnderGpu::dropOwnDepth();
    UnderGpu::dropTargets();
}

void UnderUI::shutdown() {
    UnderGpu::ownDepthWanted.store(false);
    CommandListTracker::forgetOwnDepth();
    UnderGpu::dropOwnDepth();
    UnderGpu::stopBuilder();
    UnderGpu::waitIdle();
    for (UnderPass* p : sPasses)
        p->shutdown();
    UnderGpu::shutdown();
}

} // namespace Render
