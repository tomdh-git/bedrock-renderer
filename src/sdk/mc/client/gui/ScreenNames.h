#pragma once

// The names of the game's screens as ClientInstance::getScreenName and the UI tree's root controls report them (JSON UI file names).
namespace ScreenNames {
inline constexpr const char* kHud = "hud_screen";                 // the world, with nothing over it
inline constexpr const char* kHudCrosshair = "hud_crosshair_screen"; // the same, as 1.26.60 reports it
inline constexpr const char* kStart = "start_screen";             // the main menu
inline constexpr const char* kPauseMarker = "pause";              // part of the name of the pause menu's screens
inline constexpr const char* kSettings = "controls_and_settings"; // part of the name of the settings screens (screen_world_controls_and_settings[_fullscreen], screen_controls_and_settings)
inline bool isSettings(const std::string& name) { return name.find(kSettings) != std::string::npos; }
inline bool isHud(const std::string& name) { return name == kHud || name == kHudCrosshair; }
} // namespace ScreenNames
