# Modules

A module is a `struct X : Module` that declares its settings as member handles and subscribes to events with `ON`. Settings register themselves into `Module::settings` through `Module::building` while the module is constructed.

```cpp
struct Sprint : Module {
    using Self = Sprint;
    Sprint() : Module("Sprint", ModuleCategory::Movement) {}
    const char* tooltip() const override { return "Always sprinting"; }

    Toggle boost{"Boost", true};
    Slider speed{"Speed", 0.5f, 1.5f, 1.f};
    ON(GameUpdateEvent, onUpdate);   // declares void onUpdate(GameUpdateEvent&)

    void onUpdate(GameUpdateEvent&); // defined in the .cpp
};
```

Categories: Combat, Visuals, Movement, Player, Other.

## Add a module

1. Create the header under `features/modules/<category>/`.
2. Register it with `reg<X>()` in that category's `Register.cpp`. It then appears in the Click GUI.
3. Add settings as members, and subscribe with `ON(Event, handler)`.
4. `onEnable`/`onDisable` add and remove manual listeners; `onInit` runs once after registration, for listeners that must run while the module is off.

## Settings handles

| Handle | Setting type | Notes |
|---|---|---|
| `Toggle` | Bool | On/off. |
| `Choice` | Enum | Options vector, selected index. |
| `Slider` | Number | min, max, value, step (typing is exact). |
| `RangeSlider` | Range | Lower and upper value inside a range. |
| `KeyBind` | Bind | Virtual-key code, 0 = unbound. |
| `ColorPick` | Color | 32-bit color. |
| `Heading` | Section | Layout divider. |

## Config

Each persisted module's state is JSON keyed by a stable module ID derived from the display name (lowercase, non-alphanumeric runs become `_`, trailing `_` trimmed). Loading also accepts the legacy display name as a fallback, so existing configs keep working. A module has three persist flags (`persist`, `persistEnabled`, `persistSettings`). An unknown module or setting in a file is preserved and written back.

## Health

- A module declares `Requirement` handles as members, for capabilities such as `Capability::Render` or `Capability::PacketIn`. Hooks and systems publish capability status.
- A module whose requirements are unmet is greyed out in the Click GUI, skipped by key binds, the ArrayList, and config auto-enable, and shows the reason in a tooltip.
- When a capability returns, the module becomes available again and resumes if it was enabled before it went unavailable.
- Optional hook detours degrade (the capability stays off, the rest of the client keeps running) instead of aborting startup; critical hooks (`HOOK_REQUIRED`) stay fatal.
- Add a capability: a hook or system publishes it, a module requires it, and the UI greys the module automatically.
