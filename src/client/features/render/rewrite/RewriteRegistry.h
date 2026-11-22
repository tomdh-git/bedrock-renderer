#pragma once
#include "client/features/hooks/Detour.h"
#include "client/core/diagnostics/Profiler.h"

// The rewrite registry (docs/BGFX_MAP.md section 12, R1): one entry per game function we reimplement. An entry names the function by its Sigs.json symbol, holds the
// detour that replaces it and the trampoline to the original, and has a mode that can be switched at run time. NOTHING is enabled by default: with no mode set, no detour is
// installed at all and the game runs untouched.
//
//   Off     the original runs (an installed detour forwards at the cost of one atomic read)
//   Shadow  the original runs and its effects are what the game keeps; the rewrite is evaluated on the same inputs, outputs are compared, a divergence is counted and logged
//   Verify  as Shadow, but the first divergence ends the process loudly (fail fast, no fallback): the mode that proves a rewrite
//   On      only the rewrite runs; the original is never called
//
// Modes are set from the environment (BS_REWRITE="Math::mat4Multiply=verify,Frame::sort=shadow") when RewriteRegistry::init() runs, or by setMode() from a debug UI. The thread
// model of every rewritten function is in RewriteOwnership.h; a rewrite must keep its function's contract.
enum class RewriteMode : uint8_t { Off, Shadow, On, Verify };

struct RewriteEntry {
    const char* name;      // "Math::mat4Multiply": the registry's key and the profiler row
    const char* sig;       // Sigs.json symbol that resolves the function (SigManager::get); the lead adds the entries listed in docs/progress/rewrite-program.md
    uintptr_t knownRva;    // 1.26.62.01: the resolved address must be exactly this on that build (a twin function with an identical body would match a short pattern)
    void* detour;          // the C++ detour, same signature and calling convention as the game's function; null for a hosted entry
    bool hosted;           // the function is already hooked by another detour (Encoder::submit is RenderMark::submit): no detour of ours, the host calls dispatch

    std::atomic<uint8_t> mode{static_cast<uint8_t>(RewriteMode::Off)};
    Detour* hook = nullptr;
    uintptr_t target = 0; // absolute address once installed

    std::atomic<uint64_t> calls{0};       // entries into the detour while installed (any mode)
    std::atomic<uint64_t> evaluated{0};   // calls whose rewrite output was produced and compared (Shadow / Verify)
    std::atomic<uint64_t> divergences{0}; // compared and different (Shadow: counted; Verify never gets here, it ends the process)
    std::atomic<uint64_t> skipped{0};     // Shadow/Verify calls that could not be compared and ran the original only; each kind of skip is a named counter of the function
    std::atomic<uint64_t> ticksOriginal{0};
    std::atomic<uint64_t> ticksRewrite{0};
    std::atomic<Profiler::Id> profileId{-1};

    RewriteEntry(const char* n, const char* s, uintptr_t rva, void* fn, bool host = false) : name(n), sig(s), knownRva(rva), detour(fn), hosted(host) {}
    RewriteEntry(const RewriteEntry&) = delete;
    RewriteEntry& operator=(const RewriteEntry&) = delete;

    RewriteMode current() const { return static_cast<RewriteMode>(mode.load(std::memory_order_relaxed)); }
    // The trampoline, typed like the detour: entry.original<&myDetour>().
    template <auto Fn>
    auto original() const {
        return hook->getOriginal<Fn>();
    }
};

// A static registrar, like HookReg: records the entry before main (touches nothing of the game).
struct RewriteReg {
    explicit RewriteReg(RewriteEntry& entry);
};

struct RewriteRegistry {
    static void record(RewriteEntry& entry); // static init only
    // After HookManager::init (sigs resolved, MinHook up): reads BS_REWRITE and installs the detour of every entry whose mode is not Off. Fatal on an unknown name or mode.
    static void init();
    // Switches an entry. The first non-Off mode installs its detour (late detour, enabled at once). Returns false for an unknown name.
    static bool setMode(const char* name, RewriteMode mode);
    static RewriteEntry* find(const char* name);
    static std::vector<RewriteEntry*> entries();
    static const char* modeName(RewriteMode mode);
    // One log line per entry that has run: calls, evaluated, divergences, skipped, average ns per call of the original and of the rewrite.
    static void report();

    // Resolves the target (fatal when the sig does not resolve, when the build is not the expected one or when knownRva disagrees), creates the detour and enables it.
    static void install(RewriteEntry& entry);

    static uintptr_t imageBase();
};

// RAII: add the elapsed ticks to a counter of the entry and, while the profiler window is open, to its row ("rewrite", name).
struct RewriteTimed {
    RewriteEntry& entry;
    std::atomic<uint64_t>& sink;
    const uint64_t t0;
    RewriteTimed(RewriteEntry& e, std::atomic<uint64_t>& s) : entry(e), sink(s), t0(Profiler::now()) {}
    ~RewriteTimed() {
        const uint64_t dt = Profiler::now() - t0;
        sink.fetch_add(dt, std::memory_order_relaxed);
        if (Profiler::collecting())
            Profiler::add(Profiler::lazyId(entry.profileId, "rewrite", entry.name), dt);
    }
};

// While a verify/shadow run is in progress on this thread, a nested call to any rewritten function runs the original (the harness must not compare inside a comparison).
struct RewriteBusy {
    static inline thread_local int depth = 0;
    struct Scope {
        Scope() { ++depth; }
        ~Scope() { --depth; }
    };
};
