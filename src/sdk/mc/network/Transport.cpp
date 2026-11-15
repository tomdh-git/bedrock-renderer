#include "sdk/mc/network/Transport.h"
#include "client/core/diagnostics/Log.h"

namespace {

wchar_t lowerAscii(wchar_t c) { return c >= L'A' && c <= L'Z' ? c + (L'a' - L'A') : c; }

// Case-insensitive substring test on a null-terminated wide name; module names are ASCII in practice.
bool nameHas(const wchar_t* name, const wchar_t* needle) {
    for (const wchar_t* at = name; *at; ++at) {
        const wchar_t* h = at;
        const wchar_t* n = needle;
        while (*h && *n && lowerAscii(*h) == lowerAscii(*n)) {
            ++h;
            ++n;
        }
        if (!*n)
            return true;
    }
    return false;
}

// Both transports are compiled into the game image on this build, so this lights up only when one ships (or loads)
// as its own module; an empty scan is reported as "probe unavailable", never guessed.
Transport::Kind scanModules() {
    HANDLE snapshot = INVALID_HANDLE_VALUE;
    for (int attempt = 0; attempt < 3 && snapshot == INVALID_HANDLE_VALUE; ++attempt)
        snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0); // can transiently fail with ERROR_BAD_LENGTH: retry
    if (snapshot == INVALID_HANDLE_VALUE)
        return Transport::Kind::Unknown;
    MODULEENTRY32W module{};
    module.dwSize = sizeof(module);
    Transport::Kind found = Transport::Kind::Unknown;
    if (Module32FirstW(snapshot, &module)) {
        do {
            if (nameHas(module.szModule, L"raknet")) {
                found = Transport::Kind::RakNet;
                break;
            }
            if (nameHas(module.szModule, L"nethernet")) {
                found = Transport::Kind::NetherNet;
                break;
            }
        } while (Module32NextW(snapshot, &module));
    }
    CloseHandle(snapshot);
    return found;
}

} // namespace

Transport::Kind Transport::detect() {
    static std::atomic<int> sCached{0}; // 0 = not probed yet, else (int)Kind + 1
    int cached = sCached.load(std::memory_order_acquire);
    if (cached)
        return static_cast<Kind>(cached - 1);
    const Kind found = scanModules();
    sCached.store(static_cast<int>(found) + 1, std::memory_order_release);
    static std::atomic<bool> sLogged{false};
    if (!sLogged.exchange(true, std::memory_order_acq_rel)) {
        if (found == Kind::Unknown)
            Logger::warn("[net] transport: unknown (probe unavailable)");
        else
            Logger::info("[net] transport: {}", name(found));
    }
    return found;
}

const char* Transport::name(Kind kind) {
    switch (kind) {
    case Kind::RakNet:
        return "RakNet";
    case Kind::NetherNet:
        return "NetherNet";
    default:
        return "Unknown";
    }
}
