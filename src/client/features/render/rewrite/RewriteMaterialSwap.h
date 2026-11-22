#pragma once



// Q?: L7h material swap hook. The item visitor's tag-7 handler (0x6646dc2, docs/BGFX_MAP.md 6cj)
// builds the pass-name string_view ("CracksBlockEntity", 0x6646e6c, length 0x11) and calls the
// pass-name resolver ResourceCache::get 0x675E440 with it (call site 0x6646eab; this = frameCtx+0x68
// at 0x6646e5c). MaterialSwap holds the fixed, thread-safe replacement table (pass-name hash ->
// replacement name) consulted by the rewrite detour in RewriteMaterialSwap.cpp.
//
// The detour hashes the pass-name view with FNV-1, basis 0xCBF29CE484222325 (resolver basis at
// 0x675e4c6 = RewriteHash::kFnvBasis), so a name registered with set() and a detour-time view hash
// alike. The per-item material identity is that view: it is the 5th argument of get(),
// a pointer to a {ptr, size} string_view passed on the stack at [rsp+0x20] (0x6646e98), with
// {ptr, size} stored at [rbp+0x5A0]/[rbp+0x5A8] (0x6646e73/0x6646e7a).
//
// No allocation in the hot path: lookup only reads the static table (mutex protected, no malloc).
struct PassName {
    const char* ptr;   // string_view pointer
    size_t size;       // string_view size in bytes; layout mirrors the game's string_view {ptr, size}
};

struct MaterialSwap {
    static constexpr size_t kMaxEntries = 16;    // fixed table, no allocation in the hot path
    static constexpr size_t kMaxReplacement = 64;

    // One registered replacement: FNV-1a hash of the pass name -> replacement bytes. Looked up
    // by the detour on every resolver call carrying a matching pass-name view.
    struct Entry {
        uint64_t nameHash = 0;
        char replacement[kMaxReplacement] = {};
        uint8_t replacementSize = 0;
        bool used = false;
    };

    // Registers a replacement for the pass name. Fails fast (Logger::fatal) on a null or empty
    // name, a replacement of length 0 or >= kMaxReplacement, or a full table.
    static void set(const char* passName, const char* replacement);
    // Removes every registered replacement.
    static void clear();
    // True, with out[0..outSize) filled with the replacement bytes, when a swap exists for the
    // pass-name view. No allocation; the table is read under its mutex.
    static bool lookup(const char* ptr, size_t size, char out[kMaxReplacement], size_t& outSize);
    // True when the MaterialSwap entry's mode is On (BS_REWRITE="MaterialSwap=on"). Queried by the
    // hosted detour in RewriteResourceCache.cpp before each original call. Off = pass-through;
    // Verify is not applicable to a hosted entry — it has no detour of its own and nothing to
    // compare (ResourceCache::get is impure, see RewriteMaterialSwap.cpp).
    static bool swapEnabled();

private:
    static Entry sTable[kMaxEntries];
    static std::mutex sMutex;
};
