#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/hooks/Hook.h"
#include "client/features/render/rewrite/RewriteProbe.h"
#include "client/platform/time/Time.h"
#include "sdk/GameVersion.h"
#include "sdk/SigManager.h"

static std::vector<RewriteEntry*>& rwEntryList() {
    static std::vector<RewriteEntry*> sList; // function-local: the registrars in other translation units run in no fixed order
    return sList;
}

static std::mutex& rwListMutex() {
    static std::mutex sMutex;
    return sMutex;
}

RewriteReg::RewriteReg(RewriteEntry& entry) {
    RewriteRegistry::record(entry);
}

void RewriteRegistry::record(RewriteEntry& entry) {
    std::lock_guard<std::mutex> lock(rwListMutex());
    rwEntryList().push_back(&entry);
}

std::vector<RewriteEntry*> RewriteRegistry::entries() {
    std::lock_guard<std::mutex> lock(rwListMutex());
    return rwEntryList();
}

RewriteEntry* RewriteRegistry::find(const char* name) {
    for (RewriteEntry* e : entries())
        if (std::strcmp(e->name, name) == 0)
            return e;
    return nullptr;
}

uintptr_t RewriteRegistry::imageBase() {
    return reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
}

const char* RewriteRegistry::modeName(RewriteMode mode) {
    switch (mode) {
    case RewriteMode::Off: return "off";
    case RewriteMode::Shadow: return "shadow";
    case RewriteMode::On: return "on";
    case RewriteMode::Verify: return "verify";
    }
    Logger::fatal("[rewrite] bad mode value {}", static_cast<int>(mode));
}

static RewriteMode rwParseMode(std::string_view text, std::string_view entry) {
    if (text == "off")
        return RewriteMode::Off;
    if (text == "shadow")
        return RewriteMode::Shadow;
    if (text == "on")
        return RewriteMode::On;
    if (text == "verify")
        return RewriteMode::Verify;
    Logger::fatal("[rewrite] BS_REWRITE: '{}' is not a mode for '{}' (off, shadow, on, verify)", text, entry);
}

void RewriteRegistry::install(RewriteEntry& entry) {
    if (entry.target)
        return;
    GameVersion::Info info;
    const GameVersion::Status status = GameVersion::preflight(&info);
    if (status != GameVersion::Status::Ok)
        Logger::fatal("[rewrite] {}: game version check is {}; a rewrite is only installed on the build its layout was verified on", entry.name, GameVersion::statusName(status));
    const uintptr_t target = SigManager::get(entry.sig);
    if (!target)
        Logger::fatal("[rewrite] {}: sig '{}' did not resolve", entry.name, entry.sig);
    if (entry.knownRva && info.build == kExpectedBuild && target != imageBase() + entry.knownRva)
        Logger::fatal("[rewrite] {}: sig '{}' resolved to rva {:#x}, expected {:#x} on this build (an identical twin function?)", entry.name, entry.sig, target - imageBase(), entry.knownRva);
    if (!entry.hosted) {
        entry.hook = HookTable::add(std::make_unique<Detour>(std::string("Rewrite::") + entry.name, target, entry.detour));
        BS_CHECK(entry.hook != nullptr);
        entry.hook->enable();
        BS_CHECK(entry.hook->enabled());
    }
    entry.target = target;
    Logger::info("[rewrite] {} installed at rva {:#x}{}", entry.name, target - imageBase(), entry.hosted ? " (hosted: the existing detour calls dispatch)" : "");
}

bool RewriteRegistry::setMode(const char* name, RewriteMode mode) {
    RewriteEntry* entry = find(name);
    if (!entry)
        return false;
    if (mode != RewriteMode::Off)
        install(*entry);
    entry->mode.store(static_cast<uint8_t>(mode), std::memory_order_relaxed);
    Logger::info("[rewrite] {} mode {}", entry->name, modeName(mode));
    return true;
}

void RewriteRegistry::init() {
    RewriteProbe::initFromEnvironment();
    char text[2048];
    const DWORD length = GetEnvironmentVariableA("BS_REWRITE", text, sizeof(text));
    if (length == 0)
        return;
    if (length >= sizeof(text))
        Logger::fatal("[rewrite] BS_REWRITE is longer than {} characters", sizeof(text) - 1);
    std::string_view rest(text, length);
    while (!rest.empty()) {
        const size_t comma = rest.find(',');
        std::string_view item = rest.substr(0, comma);
        rest = comma == std::string_view::npos ? std::string_view() : rest.substr(comma + 1);
        while (!item.empty() && item.front() == ' ')
            item.remove_prefix(1);
        while (!item.empty() && item.back() == ' ')
            item.remove_suffix(1);
        if (item.empty())
            continue;
        const size_t eq = item.rfind('=');
        if (eq == std::string_view::npos)
            Logger::fatal("[rewrite] BS_REWRITE item '{}' is not name=mode", item);
        const std::string name(item.substr(0, eq));
        const RewriteMode mode = rwParseMode(item.substr(eq + 1), name);
        if (!setMode(name.c_str(), mode))
            Logger::fatal("[rewrite] BS_REWRITE names '{}', which is not a registered rewrite", name);
    }
}

static double rwNsPerCall(uint64_t ticks, uint64_t calls) {
    return calls ? Platform::Time::toMs(ticks) * 1.0e6 / static_cast<double>(calls) : 0.0;
}

void RewriteRegistry::report() {
    for (RewriteEntry* e : entries()) {
        const uint64_t calls = e->calls.load(std::memory_order_relaxed);
        if (!calls)
            continue;
        const uint64_t evaluated = e->evaluated.load(std::memory_order_relaxed);
        Logger::info("[rewrite] {} mode {}: {} calls, {} evaluated, {} divergences, {} skipped; original {:.1f} ns, rewrite {:.1f} ns per timed call", e->name, modeName(e->current()), calls, evaluated,
            e->divergences.load(std::memory_order_relaxed), e->skipped.load(std::memory_order_relaxed), rwNsPerCall(e->ticksOriginal.load(std::memory_order_relaxed), evaluated ? evaluated : calls),
            rwNsPerCall(e->ticksRewrite.load(std::memory_order_relaxed), evaluated ? evaluated : calls));
    }
}
