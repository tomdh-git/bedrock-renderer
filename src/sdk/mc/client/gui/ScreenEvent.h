#pragma once
#include "sdk/OffsetProvider.h"

// A ScreenEvent as the game hands it to ScreenController::handleEvent (vtable slot OffsetProvider::ScreenController_vHandleEvent). Only the button
// event is described: type +0 (1 = ButtonEvent), then ButtonScreenEventData at +8. The id of a button is the FNV-1a 32 hash of its name (see
// StringUtils Str::fnv1a), a click is sent as the same event the screen makes from button.menu_select.
struct ButtonScreenEvent {
    static constexpr size_t kSize = 96;
    static constexpr int kType = 1;

    static bool isButton(const uint8_t* ev) { return *reinterpret_cast<const int*>(ev) == kType; }
    static uint32_t buttonId(const uint8_t* ev) { return *reinterpret_cast<const uint32_t*>(ev + 8); }
    static bool isPress(const uint8_t* ev) { return ev[17] == 1; } // the new state

    // The event of a click on `buttonId`, sent from `fromId` (button.menu_select): previous state 2, state 1, handle deselection and selection, the
    // property bag (none), the cursor, interacted, input mode 1; scope 0, local.
    static void makeClick(uint8_t (&ev)[kSize], uint32_t buttonId, uint32_t fromId) {
        memset(ev, 0, kSize);
        *reinterpret_cast<int*>(ev) = kType;
        *reinterpret_cast<uint32_t*>(ev + 8) = buttonId;
        *reinterpret_cast<uint32_t*>(ev + 12) = fromId;
        ev[16] = 2;
        ev[17] = 1;
        ev[18] = 1;
        ev[19] = 1;
        ev[8 + 32] = 1; // interacted
        *reinterpret_cast<int*>(ev + 8 + 36) = 1;
        ev[49] = 1; // local event
    }

    // ScreenController::handleEvent on a live controller.
    static int send(void* controller, void* ev) {
        return (*reinterpret_cast<int (***)(void*, void*)>(controller))[OffsetProvider::ScreenController_vHandleEvent](controller, ev);
    }
};
