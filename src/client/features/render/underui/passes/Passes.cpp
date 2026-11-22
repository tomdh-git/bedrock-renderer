#include "client/features/render/underui/passes/Passes.h"

void UnderPasses::install() {
    SkyPasses::install();
    MotionBlurPasses::install();
    GeekbarWorldPasses::install();
    UnderActorsPasses::install(); // before the chams: same layer, the ESP parts go on the blurred scene first
    ChamsPasses::install();
    NameTagBlurPasses::install(); // after the scene's blur and the chams (same cut, later): the picture without the tags has both in it
    DrawListPasses::install();
    Render::UnderUI::markPassesReady(); // the shader resolvers and the pass list are complete: the gate opens
}
