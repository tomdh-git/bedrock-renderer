#pragma once
#include "client/features/hooks/hooks/render/FrameFilterHook.h"

// Diagnostics only: the calling chain of the place it is called from, as the exe's rvas (with the rva of the function each return address is in, so a chain reads as a
// list of functions). Frames outside the exe (the d3d12 runtime, the driver) show as "ext". Used to find which of the game's functions sit between an actor's insert and
// its draw, and which create its pipeline state, for the bgfx-level chams.
namespace Diag {

inline std::string stack(int skip, int frames = 14) {
    void* at[32] = {};
    const USHORT n = CaptureStackBackTrace(static_cast<DWORD>(skip + 1), static_cast<DWORD>(frames < 32 ? frames : 32), at, nullptr);
    const auto base = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
    std::string out;
    for (USHORT i = 0; i < n; ++i) {
        const auto a = reinterpret_cast<uintptr_t>(at[i]);
        if (a < base || a >= base + 0x10000000) {
            out += " ext";
            continue;
        }
        uintptr_t b = 0, e = 0;
        if (FrameFilterHook::ffFunctionOf(a, b, e))
            out += fmt::format(" {:#x}(fn {:#x}+{:#x})", a - base, b - base, a - b);
        else
            out += fmt::format(" {:#x}", a - base);
    }
    return out;
}

// Logs at most `limit` times per `slot` (a small id of the call site), counted from the start.
inline bool first(int slot, int limit) {
    static std::atomic<int> sCount[64];
    return sCount[slot & 63].fetch_add(1, std::memory_order_relaxed) < limit;
}

} // namespace Diag
