#pragma once

// The rewritten functions of Q2 (BGFX_MAP 12c step 1), as plain C++ over the game's own memory. Each one is the reversed source of its dossier (docs/functions/*.md) written
// against raw offsets; the offsets are static_assert-ed against the SDK headers where one exists. Nothing here touches the registry: the detours that put them in front of the game
// are in the Rewrite*.cpp next to this header, and none is installed unless its mode is set (RewriteRegistry).

// Hashes shared by the rewrites. The game folds every uniform and every cache key with FNV-1a 64 and boost's hash_combine (the 64-bit golden-ratio constant truncated to 32 bits), and
// hashes uniform values with XXH64 (0x19932C0, constants and structure read in full; the port below reproduces the published test vectors of XXH64).
struct RewriteHash {
    static constexpr uint64_t kFnvBasis = 0xCBF29CE484222325ull;
    static constexpr uint64_t kFnvPrime = 0x100000001B3ull;

    static uint64_t fnv1a(const uint8_t* bytes, size_t count, uint64_t hash = kFnvBasis) {
        for (size_t i = 0; i < count; ++i)
            hash = (hash ^ bytes[i]) * kFnvPrime;
        return hash;
    }
    // h ^ (x + 0x9E3779B9 + (h << 6) + (h >> 2))
    static uint64_t combine(uint64_t h, uint64_t x) { return h ^ (x + 0x9E3779B9ull + (h << 6) + (h >> 2)); }

    static constexpr uint64_t kP1 = 0x9E3779B185EBCA87ull, kP2 = 0xC2B2AE3D27D4EB4Full, kP3 = 0x165667B19E3779F9ull, kP4 = 0x85EBCA77C2B2AE63ull, kP5 = 0x27D4EB2F165667C5ull;
    static uint64_t xxRound(uint64_t acc, uint64_t input) { return _rotl64(acc + input * kP2, 31) * kP1; }
    static uint64_t xxMerge(uint64_t acc, uint64_t value) { return (acc ^ xxRound(0, value)) * kP1 + kP4; }
    static uint64_t xxh64(const void* data, size_t length, uint64_t seed) {
        const uint8_t* p = static_cast<const uint8_t*>(data);
        const uint8_t* const end = p + length;
        uint64_t h;
        if (length >= 32) {
            uint64_t v1 = seed + kP1 + kP2, v2 = seed + kP2, v3 = seed, v4 = seed - kP1;
            do {
                uint64_t w[4];
                std::memcpy(w, p, 32);
                v1 = xxRound(v1, w[0]);
                v2 = xxRound(v2, w[1]);
                v3 = xxRound(v3, w[2]);
                v4 = xxRound(v4, w[3]);
                p += 32;
            } while (p + 32 <= end);
            h = _rotl64(v1, 1) + _rotl64(v2, 7) + _rotl64(v3, 12) + _rotl64(v4, 18);
            h = xxMerge(h, v1);
            h = xxMerge(h, v2);
            h = xxMerge(h, v3);
            h = xxMerge(h, v4);
        } else {
            h = seed + kP5;
        }
        h += length;
        while (p + 8 <= end) {
            uint64_t w;
            std::memcpy(&w, p, 8);
            h ^= xxRound(0, w);
            h = _rotl64(h, 27) * kP1 + kP4;
            p += 8;
        }
        if (p + 4 <= end) {
            uint32_t w;
            std::memcpy(&w, p, 4);
            h ^= static_cast<uint64_t>(w) * kP1;
            h = _rotl64(h, 23) * kP2 + kP3;
            p += 4;
        }
        while (p < end) {
            h ^= *p++ * kP5;
            h = _rotl64(h, 11) * kP1;
        }
        h ^= h >> 33;
        h *= kP2;
        h ^= h >> 29;
        h *= kP3;
        h ^= h >> 32;
        return h;
    }

    // bx::HashMurmur2A (seed 0) over a buffer whose length is a multiple of 4: the case the bind block hash is (0x514 bytes). Same mixing as the inlined begin/add/end of
    // Encoder::submit (docs/functions/bc60740.md): mmix per 32-bit word, then mmix of the (empty) tail and of the byte count, then the final avalanche.
    static uint32_t murmur2a(const void* data, size_t size) {
        constexpr uint32_t kM = 0x5BD1E995u;
        uint32_t h = 0;
        const uint32_t* words = static_cast<const uint32_t*>(data);
        for (size_t i = 0; i < size / 4; ++i) {
            uint32_t k = words[i] * kM;
            k ^= k >> 24;
            k *= kM;
            h = h * kM ^ k;
        }
        uint32_t tail = 0;
        tail *= kM; // the empty tail still passes through mmix
        tail ^= tail >> 24;
        tail *= kM;
        h = h * kM ^ tail;
        uint32_t s = static_cast<uint32_t>(size) * kM;
        s ^= s >> 24;
        s *= kM;
        h = h * kM ^ s;
        h ^= h >> 13;
        h *= kM;
        h ^= h >> 15;
        return h;
    }
};

// Q2f: 0xAA6580, out = B * A in the game's row layout (see RewriteMath.cpp).
struct RewriteMath {
    static float* mat4Multiply(float* out, const float* a, const float* b);
};

// Q2a: 0x5679DB0, writes one uniform (an array of vec4) into a material instance's CPU-side uniform block and folds it into the block's running hash (docs/functions/5679db0.md).
struct RewriteUniform {
    struct Span {
        uint64_t count;   // number of vec4
        const void* data; // count * 16 bytes
    };
    static constexpr uintptr_t kBlockSize = 0x20;  // u64 size of the data area
    static constexpr uintptr_t kBlockData = 0x28;  // u8* data area
    static constexpr uintptr_t kBlockSlots = 0x30; // u8* slot table, 16-byte entries
    static constexpr uintptr_t kBlockHash = 0x70;  // u64 running hash
    static constexpr uintptr_t kSlotOffset = 0x08; // u16 byte offset into the data area
    static constexpr uintptr_t kSlotDirty = 0x0C;  // u8
    static constexpr size_t kSlotStride = 16;

    // The running hash after writing `bytes` (the value) to `slot`, from the hash before it.
    static uint64_t hashAfter(uint64_t before, uint16_t slot, const void* value, size_t bytes);
    static void setVec4Array(uint8_t* block, const uint16_t* slot, const Span* value);
};

// Q2b: 0x675E440 ResourceCache::get, the hit path (docs/functions/675e440.md): a key that is cached, not stale and already loaded returns its holder. Everything else is the game's.
struct RewriteResourceCache {
    struct Key {
        uint64_t lo;
        uint64_t hi;
    };
    // Layout of the cache object (dossier "Layout of this"): two MSVC hash containers laid out the same way, entries at +0x00 and the stale-key set at +0x40.
    static constexpr uintptr_t kEntries = 0x00;
    static constexpr uintptr_t kStale = 0x40;
    static constexpr uintptr_t kSentinel = 0x08; // container-relative: list head node pointer
    static constexpr uintptr_t kBuckets = 0x18;  // container-relative: bucket array, 16 bytes {first, last} per bucket
    static constexpr uintptr_t kMask = 0x30;     // container-relative: bucket mask
    static constexpr uintptr_t kMutex = 0x98;    // std::recursive_mutex of the game's CRT
    static constexpr uintptr_t kNodePrev = 0x08;
    static constexpr uintptr_t kNodeKey = 0x10;
    static constexpr uintptr_t kNodeHolder = 0x20; // shared_ptr<Holder>: pointer
    static constexpr uintptr_t kNodeControl = 0x28; // shared_ptr<Holder>: control block (use count at +8)
    static constexpr uintptr_t kNodeUsed = 0x30;    // u8, set on every get
    static constexpr uintptr_t kResourceRequested = 0x10; // Holder->resource (first qword) -> u8 requested

    struct Hit {
        uint8_t* node = nullptr;
        uint8_t* holder = nullptr;
        uint8_t* control = nullptr;
    };
    static uint64_t hashOf(const Key& key);
    static uint8_t* findNode(const uint8_t* cache, uintptr_t container, const Key& key);
    // The cache's lock must be held. True when key is cached, not stale and its resource is loaded.
    static bool lookup(const uint8_t* cache, const Key& key, Hit& hit);
    // On mode's fast path: lock, lookup, on a hit mark the entry used and copy the holder into out (two qwords {pointer, control block}, use count incremented), unlock.
    static bool fastGet(uint8_t* cache, uint64_t* out, const Key& key);

    using MutexFn = int (*)(void* mutex); // the game's _Mtx_lock / _Mtx_unlock
    static MutexFn lockFn();
    static MutexFn unlockFn();
};

// Q2c: Frame::sort (0xBC61E20) with the radix sort of 0xBC62040 and the blit sort 0xBC62BC0 (docs/functions/bc61e20.md; the sorts were read for this file: stock bx::radixSort, 11-bit digits,
// six passes over the 64-bit key, stable, ascending, the keys and the u16 values permuted together, an already sorted input left alone).
struct RewriteFrame {
    static constexpr size_t kMaxItems = 65535;
    // The core on arbitrary arrays: remaps the view id (bits 54..61) of every key through the inverse of viewRemap[256], stable-sorts keys and values together by the full key,
    // remaps the view (the top byte) of every blit key and sorts them. Scratch is internal (one sort at a time).
    static void sortArrays(const uint16_t* viewRemap, uint64_t* keys, uint16_t* values, uint32_t itemCount, uint32_t* blitKeys, uint32_t blitCount);
    static void sort(uint8_t* frame);
};

// Q2d: Encoder::submit (0xBC60740, docs/functions/bc60740.md) for the draws that carry no side table. The outputs of one call are computed as a plan (pure) and applied to the Frame.
struct RewriteEncoder {
    static constexpr size_t kSpan = 0x6AE; // bytes of the encoder the function reads or writes: [0, kSpan)
    static constexpr size_t kBindCopy = 0x518;
    static constexpr size_t kHeaderSize = 0x80;

    struct Plan {
        uint64_t key;
        uint8_t header[kHeaderSize];
        uint8_t bind[kBindCopy];
        uint8_t encoderAfter[kSpan];
    };
    // Inputs the original reads from outside the encoder.
    struct Inputs {
        uint32_t idx;       // the render item slot the draw got
        uint32_t seq;       // the view's sequence counter value the draw got (mode 1)
        uint32_t uniformPos; // UniformBuffer::pos of the encoder's uniform buffer
        uint8_t viewMode;   // the view's sort mode byte
    };
    // Pure: encoderBefore (kSpan bytes, the encoder as the call found it) and the call's arguments -> what the call writes.
    static void plan(const uint8_t* encoderBefore, uint16_t view, uint16_t program, uint16_t occlusionQuery, uint32_t depth, uint8_t preserve, const Inputs& in, Plan& out);

    using SubmitFn = void (*)(uint8_t* encoder, uint32_t view, uint32_t program, uint32_t query, uint32_t depth, uint8_t preserve);
    // The submit as the game's code is hooked by RenderMarkHook (RenderMark::submit is the same function), the host's detour hands its trampoline here instead of calling it.
    // Shared with discard (RewriteDiscard.cpp). clearDrawState: the draw state and the 65 bindings back to their defaults. commitSideTable / clearSideTable: 0xBC60F10 and the loop that
    // empties a side table, both through the game's allocator.
    static void discard(uint8_t* encoder); // 0xBC60D10, RewriteDiscard.cpp
    static void clearDrawState(uint8_t* encoder);
    static void commitSideTable(uint8_t* frame, uint32_t idx, const uint8_t* src);
    static void clearSideTable(uint8_t* table);
    static void dispatch(SubmitFn original, uint8_t* encoder, uint32_t view, uint32_t program, uint32_t query, uint32_t depth, uint8_t preserve);
    static void submit(uint8_t* encoder, uint16_t view, uint16_t program, uint16_t occlusionQuery, uint32_t depth, uint8_t preserve, SubmitFn original);
};

// Q3d: the Light tag 5 (ServerGraphicsOverrideParameters) description is 44 unordered_set<u16> of 0x40 bytes; the game deep-copies them every frame (0x67B6300 converter, copy helper
// 0x67B7810, docs/progress/descriptions.md R7). RewriteLightCache.cpp keeps a content hash per set and tells the caller whether the whole description changed since the last frame.
struct RewriteLightOverride {
    static constexpr size_t kSets = 44;
    static constexpr size_t kSetSize = 0x40;
    static constexpr uintptr_t kSetSizeField = 0x10;    // u64 element count
    static constexpr uintptr_t kSentinelField = 0x08;    // list head node pointer
    static constexpr uintptr_t kNodeNext = 0x00;
    static constexpr uintptr_t kNodeKey = 0x10;         // u16 key in a 0x18-byte node
    // Order-independent content hash of one set (the sets are unordered: the same ids in a different node order are the same set).
    static uint64_t hashSet(const uint8_t* set);
    // Content hash of the whole description (all 44 sets).
    static uint64_t hashDescription(const uint8_t* description);
};
