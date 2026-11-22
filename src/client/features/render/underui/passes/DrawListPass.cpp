#include "client/features/render/underui/passes/Passes.h"
#include "client/features/render/Renderer.h"
#include "sdk/csgo/game/client/c_baseviewmodel/ViewModelRenderer.h"

// What is on ImGui's background draw list (and the item in hand) goes under the game's UI: always, whenever the renderer is up. The foreground list,
// the Click GUI and the rest are drawn over everything by Renderer at Present; UnderUI never touches them.
class DrawListPass : public Render::UnderPass {
public:
    Layer layer() const override { return Layer::Scene; }
    const char* name() const override { return "background draw list, item in hand"; }
    bool wanted() override { return Render::Renderer::ready(); }
    void record(ID3D12CommandQueue* q, UnderExec run, const UnderTarget& tg) override { Render::Renderer::underUiPass(tg.rt, q, run); }
};

// (The list under the actors is drawn by UnderActorsPass.cpp.)
void DrawListPasses::install() {
    static DrawListPass pass;
    Render::UnderUI::add(&pass);
}
