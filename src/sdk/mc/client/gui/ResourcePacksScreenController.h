#pragma once
#include "sdk/SigManager.h"

// The resource pack screen's controller. Its buttons are bound to lambdas that answer false whenever ClientInstance::isPreGame() is false, i.e.
// in a world; the sizes of those lambdas (1.26.60.05; matched to the 1.26.51 ones by instruction similarity, 0.8-0.87) tell a caller of isPreGame() from inside one of them.
struct ResourcePacksScreenController {
    // True when `returnAddress` lies inside one of ResourcePacksScreenController::_registerBindings' binding lambdas, or inside one of the
    // pack screen's in-world edit-path callers (the click handlers and the editability query): in a world those ask isPreGame too.
    static bool isBindingLambda(uintptr_t returnAddress) {
        static const struct {
            uintptr_t address;
            size_t size;
        } lambdas[] = {
            {SIG("ResourcePacksScreenController::bindingA"), 0x173},    {SIG("ResourcePacksScreenController::bindingB"), 0x16e},
            {SIG("ResourcePacksScreenController::canMove"), 0x11d},     {SIG("ResourcePacksScreenController::canMoveUp"), 0x1ce},
            {SIG("ResourcePacksScreenController::canMoveDown"), 0x1ce}, {SIG("ResourcePacksScreenController::bindingC"), 0xe2},
            {SIG("ResourcePacksScreenController::applyOnExit"), 0x103},
        };
        for (const auto& l : lambdas)
            if (returnAddress >= l.address && returnAddress < l.address + l.size)
                return true;
        return isEditPath(returnAddress);
    }

    // The pack screen's in-world edit path: 1.26.51.01 had four callers asking isPreGame, and the 0x4EFEFC0 one forwards the real answer into
    // the editability query, which is why the screen's model never mutates and the exit handler's gate never passes without a yes. 1.26.60.05:
    // three of them were found (0x522CFF0 = old 0x4EF5C80, 0x52357C0 = old 0x4EFEFC0, 0x5237CF0 = old 0x4F01900, similarity 0.9 / 0.75 / 0.75); the
    // fourth (old 0x4EED190, a 179-byte forwarder) has no counterpart. Rebasing them by applyOnExit's actual address keeps them together.
    static bool isEditPath(uintptr_t returnAddress) {
        static const struct { uintptr_t offset; size_t size; } ranges[] = {
            {0x522CFF0 - 0x51EFC20, 0x58A}, {0x52357C0 - 0x51EFC20, 0x78}, {0x5237CF0 - 0x51EFC20, 0x16C},
        };
        const uintptr_t base = editPathAnchor();
        for (const auto& r : ranges)
            if (returnAddress >= base + r.offset && returnAddress < base + r.offset + r.size)
                return true;
        return false;
    }

    // Resolved on first use: a header cannot run SIG at static-init time, so the edit-path ranges wait for their first caller.
    static uintptr_t editPathAnchor() {
        static const uintptr_t a = SIG("ResourcePacksScreenController::applyOnExit") - 0x51EFC20;
        return a;
    }
};
