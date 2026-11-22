#include "client/features/render/underui/FramePlan.h"
#include "client/core/diagnostics/Profiler.h"

DXGI_FORMAT FramePlan::formatOf(uintptr_t res) {
    return res ? reinterpret_cast<ID3D12Resource*>(res)->GetDesc().Format : DXGI_FORMAT_UNKNOWN;
}

// One analysis of a frame's lists. Each step finds one cut; they run in the order FramePlan::analyze calls them.
struct FramePlan::Analysis {
    UINT n;
    const std::vector<ListFacts>& f;
    const std::vector<char>& known;
    FramePlan p;
    int split = -1; // the later of the two UI boundaries (b1, b2), when a UI is drawn after it

    bool swap(UINT i) const { return known[i] && CommandListTracker::isSwapchain(f[i]); }
    uintptr_t targetOf(int i) const { return f[i].rtRes ? f[i].rtRes : CommandListTracker::frameTarget(); }

    // Scene: the later of the last swapchain depth-only clear and the last single full-screen draw into the swapchain.
    void findScene() {
        for (UINT i = 0; i < n; ++i) {
            if (!swap(i))
                continue;
            if (f[i].depthClear && !f[i].colorClear && f[i].draws == 0)
                p.b1 = static_cast<int>(i);
            if (f[i].draws == 1 && f[i].quad)
                p.b2 = static_cast<int>(i);
        }
        split = std::max(p.b1, p.b2);
        bool uiAfter = false;
        for (int i = split + 1; split >= 0 && i < static_cast<int>(n); ++i)
            if (swap(i) && f[i].draws > 0)
                uiAfter = true;
        if (uiAfter) {
            p.scene = split;
            p.sceneTarget.rt = swap(split) && f[split].rtRes ? f[split].rtRes : CommandListTracker::frameTarget();
        }
    }

    // The game paints the frame into the swapchain; after its first color clear, the lists are the frame. -1 when there is no clear (Vibrant Visuals).
    int firstColorClear() const {
        for (UINT i = 0; i < n; ++i)
            if (swap(i) && f[i].colorClear)
                return static_cast<int>(i);
        return -1;
    }

    // Sky, regular rendering: the first list that draws after the clear is the sky (in the main menu: the panorama cube). Everything after it is drawn over it.
    void findRegularSky(int clear) {
        for (UINT i = clear + 1; i < n; ++i) {
            if (!swap(i) || f[i].draws == 0)
                continue;
            // A screen with no background of its own (loading and saving screens) has the UI as its first drawing list:
            // that is not a sky. The sky comes before the UI boundary; with no boundary in sight, only a list of a draw or two.
            const bool beforeUi = split >= 0 ? static_cast<int>(i) < split : f[i].draws <= 2;
            if (!beforeUi)
                return;
            // The first list already writes depth: it is the world, and the game drew no sky of its own (Simple and Fancy graphics with the sky box left out
            // for the shader sky). Ours goes right after the clear, under the world; after this list it would paint over every block.
            if (f[i].writeDraws > 0) {
                p.sky = clear;
                p.skyTarget.rt = targetOf(clear);
                return;
            }
            p.sky = static_cast<int>(i);
            p.skyTarget.rt = targetOf(i);
            extendSkyRun(i);
            return;
        }
    }

    // A texture pack's sky is drawn by more lists after the dome (a skybox, more sky bodies): everything before the world's own geometry is sky.
    // The world writes depth; the sky does not. Our pass goes after the last list of the run, so none of them is drawn over it.
    void extendSkyRun(UINT first) {
        for (UINT k = first + 1; k < n && (split >= 0 ? static_cast<int>(k) < split : true); ++k) {
            // The sun, moon and stars are not part of the run: they are drawn over our sky. (Whether the game's list for them has draws depends on
            // where the camera looks; taking them into the run moved the cut with it, and the sky covered them or not frame by frame.)
            if (!swap(k) || f[k].draws == 0 || f[k].skyBodies() || f[k].writeDraws > 0 || f[k].unknownDraws > 0 || f[k].colorClear || f[k].depthClear)
                return;
            p.sky = static_cast<int>(k);
            p.skyTarget.rt = targetOf(k);
        }
    }

    // The nametags: the game draws the names over the players' heads into the scene, in lists of their own, before the UI (by their Nametag material, so a list
    // that holds one draw of it is one). Our Fog and Post passes move before the first of those lists, so the nametags are drawn after them and stay sharp.
    // -1 when the frame has none. `split` bounds the scan: the lists before the two UI boundaries, where the world and its nametags are.
    void findNameTags() {
        const int limit = split >= 0 ? std::min(split, static_cast<int>(n) - 1) : static_cast<int>(n) - 1;
        int first = -1, last = -1, lists = 0;
        for (int i = 0; i <= limit; ++i)
            if (known[i] && f[i].roleDraws[static_cast<int>(MatRole::NameTag)] > 0) {
                if (first < 0)
                    first = i;
                last = i;
                ++lists;
            }
        p.nameTag = first;
        p.nameTagAfter = last;
    }

    // The fog goes at the end of the world: after the last list before the depth clear that starts the UI, while the scene's depth is still there.
    // The depth is the game's view of it when we saw that created, else the buffer of ours the swapchain pass draws into while a pass wants the depth.
    void findRegularFogAndPost() {
        const uintptr_t ds = p.b1 > 0 ? f[p.b1].dsRes : 0;
        if (p.b1 <= 0 || !swap(p.b1))
            return;
        if (ds) {
            p.fog = p.post = p.b1 - 1;
            p.fogTarget = p.postTarget = {targetOf(p.b1), ds};
        } else {
            // Post-processing does not need the depth: the game's depth view may predate our hooks (then it is unknown), the cut is still the same list.
            p.post = p.b1 - 1;
            p.postTarget = {targetOf(p.b1), 0};
        }
        // The nametags are drawn after the world and before the UI: both cuts move before the first of their lists (the scene's depth is still there at that
        // earlier list), so the nametags are drawn after our passes and stay sharp.
        if (p.nameTag >= 0 && p.nameTag <= p.b1 - 1 && p.nameTag - 1 >= 0) {
            p.fog = p.post = p.nameTag - 1;
        }
        placeFogBeforeTranslucent();
    }

    // Translucent terrain (leaves, water, glass) writes no depth: at the end of the frame the depth under it is whatever lies behind, so a fog laid over it
    // by depth would haze the near leaf as if it were far. The fog goes before the first such list instead, onto the opaque world; the translucent layers
    // are drawn over it with the game's own fog on them.
    void placeFogBeforeTranslucent() {
        if (p.fog < 0)
            return;
        for (int i = std::max(p.sky, 0) + 1; i < p.fog; ++i)
            if (known[i] && swap(i) && f[i].terrainBlendDraws > 0) {
                p.fog = i - 1;
                return;
            }
    }

    // The entities: the game draws them in lists of their own, and every shader of such a list is one of the Actor materials. The first of those lists and the
    // last before the cut are where "the world without the actors" and "the actors drawn" are: what is between the two pictures is the actors.
    void findActors() {
        if (p.post < 0)
            return;
        // The local player's own draws, when the game records them while it renders that entity (ListFacts::playerDraws): the cuts go around those lists only, so
        // what changes between the two pictures is the player and nothing else. Failing that, around every list of entities.
        int first = -1, last = -1;
        bool playerLists = false;
        for (int pass = 0; pass < 2 && first < 0; ++pass)
            for (int i = 0; i <= p.post; ++i)
                if (swap(i) && (pass == 0 ? f[i].playerDraws > 0 : f[i].actorDraws > 0)) { // a list with any entity draw: the second layers of a skin (jacket, hat, armor) can share one with other draws
                    playerLists = pass == 0;
                    if (first < 0)
                        first = i;
                    last = i;
                }
        if (first > 0) {
            p.actorBefore = first - 1;
            p.actorAfter = last;
            p.actorTarget.rt = p.postTarget.rt;
        }
        // The first list of any entity (the player's or anyone's, the held item too): what is cut in before it is under every entity of the frame.
        // The last list of any entity: the pair of that cut. What changed on the screen between the two is what the entities drew.
        int firstEntity = -1, lastEntity = -1;
        for (int i = 0; i <= p.post; ++i)
            if (swap(i) && (f[i].actorDraws > 0 || f[i].playerDraws > 0)) {
                if (firstEntity < 0)
                    firstEntity = i;
                lastEntity = i;
            }
        if (firstEntity > 0) {
            p.entityBefore = firstEntity - 1;
            p.entityAfter = lastEntity;
            p.entityTarget.rt = p.postTarget.rt;
        }
    }

    // Sky, Vibrant Visuals: the scene is lit in an HDR target; the sky (the panorama in the menu) is the first depth tested
    // draw into it, right after a stencil-only clear of the scene's depth. Our pass goes after that list, depth tested
    // against the scene's depth, so only the pixels nothing was drawn on change. In a world that first draw is the sun or the moon: the
    void findVibrantSky() {
        for (UINT s = 0; s < n; ++s) {
            if (!known[s] || f[s].clearFlags != D3D12_CLEAR_FLAG_STENCIL || f[s].draws != 0 || f[s].colorClear)
                continue;
            for (UINT d = s + 1; d < n; ++d) {
                if (!known[d] || f[d].draws == 0)
                    continue;
                if (f[d].rtRes && f[d].dsRes && FramePlan::formatOf(f[d].rtRes) == DXGI_FORMAT_R11G11B10_FLOAT) {
                    if (split >= 0 && static_cast<int>(d) > split)
                        break; // after the composite: not the scene's sky
                    p.sky = static_cast<int>(f[d].skyBodies() ? s : d);
                    p.skyTarget = {f[d].rtRes, f[d].dsRes};
                    p.fog = p.sky;
                    p.fogTarget = p.skyTarget;
                }
                break;
            }
        }
    }

    // The geometry prepass draws into three targets at the screen's size (a packed material, the colour, and a float16 one holding the normal in xy and the
    // motion vector in zw), against the scene's depth. -1 when this is not a Vibrant Visuals frame.
    int findPrepass() const {
        int prepass = -1;
        for (UINT i = 0; i < n; ++i)
            if (known[i] && f[i].rtCount >= 3 && f[i].dsRes && FramePlan::formatOf(f[i].rtAll[0]) == DXGI_FORMAT_R16G16B16A16_UINT && FramePlan::formatOf(f[i].rtAll[2]) == DXGI_FORMAT_R16G16B16A16_FLOAT)
                prepass = static_cast<int>(i);
        return prepass;
    }

    // Post-processing, Vibrant Visuals: the finished scene is the last full size HDR list before the composite into the swapchain (after the bloom):
    // that is where the blur goes, reading the depth and the vectors.
    void findVibrantPost() {
        const int prepass = findPrepass();
        if (prepass < 0)
            return;
        const D3D12_RESOURCE_DESC mv = reinterpret_cast<ID3D12Resource*>(f[prepass].rtAll[2])->GetDesc();
        const UINT limit = split > prepass ? static_cast<UINT>(split) : n;
        for (UINT i = static_cast<UINT>(prepass) + 1; i < limit; ++i) {
            if (!known[i] || f[i].draws == 0 || !f[i].rtRes || FramePlan::formatOf(f[i].rtRes) != DXGI_FORMAT_R11G11B10_FLOAT)
                continue;
            const D3D12_RESOURCE_DESC rd = reinterpret_cast<ID3D12Resource*>(f[i].rtRes)->GetDesc();
            if (rd.Width != mv.Width || rd.Height != mv.Height)
                continue; // the bloom's smaller targets
            p.post = static_cast<int>(i);
            p.postTarget = {f[i].rtRes, f[prepass].dsRes, f[prepass].rtAll[2]};
        }
        // The nametags are drawn after the finished scene: the post cut moves before the first of their lists (the scene's depth and vectors are still there at
        // that earlier list), so the nametags are drawn after our blur and stay sharp. The entity snapshots below follow the moved cut.
        if (p.post >= 0 && p.nameTag >= 0 && p.nameTag <= p.post && p.nameTag - 1 >= 0) {
            p.post = p.nameTag - 1;
        }
        if (p.post >= 0)
            findVibrantActors(f[prepass].rtAll[2]);
    }

    // The entities, Vibrant Visuals: they are drawn into the prepass (the lit scene does not exist yet), so the lists are the ones that draw into its vector target
    // and the two pictures are of that target: the pixels the entities wrote differ between them.
    void findVibrantActors(uintptr_t vectors) {
        int first = -1, last = -1;
        bool playerLists = false;
        for (int pass = 0; pass < 2 && first < 0; ++pass)
            for (int i = 0; i < p.post; ++i)
                if (known[i] && f[i].rtCount >= 3 && f[i].rtAll[2] == vectors && (pass == 0 ? f[i].playerDraws > 0 : f[i].actorDraws > 0)) {
                    playerLists = pass == 0;
                    if (first < 0)
                        first = i;
                    last = i;
                }
        if (first > 0) {
            p.actorBefore = first - 1;
            p.actorAfter = last;
            p.actorTarget.rt = vectors;
        }
    }

};


FramePlan FramePlan::analyze(UINT n, const std::vector<ListFacts>& f, const std::vector<char>& known) {
    Analysis a{n, f, known};
    a.findScene();
    a.findNameTags(); // the Fog and Post cuts have to know where the nametags begin
    if (const int clear = a.firstColorClear(); clear >= 0) { // regular rendering
        a.findRegularSky(clear);
        a.findRegularFogAndPost();
        a.findActors();
        return a.p;
    }
    a.findVibrantSky(); // Vibrant Visuals
    a.findVibrantPost();
    return a.p;
}
