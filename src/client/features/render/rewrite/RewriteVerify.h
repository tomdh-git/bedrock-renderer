#pragma once
#include "client/features/render/rewrite/RewriteRegistry.h"

// The shadow/verify harness (BGFX_MAP 12b R2). A rewrite is compared against the original on the SAME inputs, in one of two shapes:
//
//   pure     the function writes only through its output pointers: the original and the rewrite each write their own buffer, the buffers are compared.
//   in place the function changes memory it is also given (a uniform block, a Frame, an encoder): the inputs it reads are copied BEFORE the call, the original runs on the real object,
//            and the rewrite computes the expected result from the copies (a pure plan); the live memory is then compared with the expectation. The rewrite never writes game memory
//            in Shadow / Verify, so there is nothing to restore.
//
// A function whose inputs cannot be replayed (the call frees memory, takes a lock another thread can race on, depends on a counter other threads advance) does not snapshot: it
// counts the call in entry.skipped and runs the original, and says in its own comment which condition causes that. Divergence is never answered with a fallback.
struct RewriteVerify {
    static bool same(const void* a, const void* b, size_t size) { return std::memcmp(a, b, size) == 0; }

    // Index of the first differing byte, or size when equal.
    static size_t firstDifference(const void* a, const void* b, size_t size) {
        const uint8_t* x = static_cast<const uint8_t*>(a);
        const uint8_t* y = static_cast<const uint8_t*>(b);
        for (size_t i = 0; i < size; ++i)
            if (x[i] != y[i])
                return i;
        return size;
    }

    static std::string hexWindow(const void* data, size_t size, size_t at) {
        const size_t begin = at >= 8 ? at - 8 : 0;
        const size_t end = std::min(size, at + 24);
        std::string text;
        for (size_t i = begin; i < end; ++i)
            text += fmt::format("{:02x}{}", static_cast<const uint8_t*>(data)[i], i + 1 == at ? "|" : " ");
        return text;
    }

    // Compares one named output. Equal: returns. Different: Shadow counts and logs the first 16, Verify ends the process with the offset and a hex window of both.
    static void compare(RewriteEntry& entry, RewriteMode mode, const char* what, const void* original, const void* rewrite, size_t size) {
        const size_t at = firstDifference(original, rewrite, size);
        if (at == size)
            return;
        const uint64_t count = entry.divergences.fetch_add(1, std::memory_order_relaxed) + 1;
        if (mode == RewriteMode::Verify)
            Logger::fatal("[rewrite] {} DIVERGED in {} at byte {} of {}\n  original: {}\n  rewrite : {}", entry.name, what, at, size, hexWindow(original, size, at), hexWindow(rewrite, size, at));
        if (count <= 16)
            Logger::error("[rewrite] {} diverged in {} at byte {} of {} (#{})\n  original: {}\n  rewrite : {}", entry.name, what, at, size, count, hexWindow(original, size, at), hexWindow(rewrite, size, at));
    }

    template <typename T>
    static void compareValue(RewriteEntry& entry, RewriteMode mode, const char* what, const T& original, const T& rewrite) {
        static_assert(std::is_trivially_copyable_v<T>);
        compare(entry, mode, what, &original, &rewrite, sizeof(T));
    }
};
