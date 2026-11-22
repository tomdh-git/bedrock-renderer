#pragma once

// Which background the main menu shows: 0 is the game's own panorama, 1.. are UnderShaders::menu(). The choice is kept between runs
// (preferences.json). The button beside the config button cycles it.
struct MenuBackground {
    static int count();             // choices, the game's panorama included
    static int index();
    static const char* name(int i);
    static void next();             // cycles, saves, and starts the name caption
    static float caption();         // 1 right after a change, fading to 0: the caption's opacity
};
