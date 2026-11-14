#include "sdk/mc/deps/core/string/GameString.h"
#include "client/core/diagnostics/Log.h"
#include "sdk/SigManager.h"

// The game's global allocator object (vtable slot 1 allocate(this, size), slot 2 release(this, ptr)); every std::string / std::vector buffer the game owns comes from
// and goes back to it. 1.26.60: it is not guaranteed to be ucrtbase malloc/free, so it is used directly. The global's address is read from the rip-relative
// `mov rcx,[g]; mov rax,[rcx]; mov rax,[rax+8]` that the game's own string copy (User::getGamertag, found by sig) opens its allocation with.
static void* allocatorObject() {
    static void* obj = [] {
        const uint8_t* fn = reinterpret_cast<const uint8_t*>(SIG("User::getGamertag"));
        for (size_t i = 0; i + 14 < 0x200; i++) {
            if (fn[i] == 0x48 && fn[i + 1] == 0x8B && fn[i + 2] == 0x0D && fn[i + 7] == 0x48 && fn[i + 8] == 0x8B && fn[i + 9] == 0x01 && fn[i + 10] == 0x48 && fn[i + 11] == 0x8B &&
                fn[i + 12] == 0x40 && fn[i + 13] == 0x08) {
                int32_t rel;
                memcpy(&rel, fn + i + 3, 4);
                void* o = *reinterpret_cast<void* const*>(fn + i + 7 + rel);
                BS_CHECK(o);
                return o;
            }
        }
        BS_CHECK(false);
        return static_cast<void*>(nullptr);
    }();
    return obj;
}

void* gameMalloc(size_t n) {
    void* a = allocatorObject();
    using Alloc = void* (*)(void*, size_t);
    void* p = (*reinterpret_cast<Alloc* const*>(a))[1](a, n);
    BS_CHECK(p);
    return p;
}

void gameFree(void* p) {
    if (!p)
        return;
    void* a = allocatorObject();
    using Release = void (*)(void*, void*);
    (*reinterpret_cast<Release* const*>(a))[2](a, p);
}

void GameString::assign(std::string_view text) {
    if (text.size() <= cap) { // fits the buffer the game owns: write in place, like std::string::assign, so the game heap is never touched (1.26.60: freeing the game's buffer corrupted the heap)
        char* dst = cap > 15 ? ptr : buf;
        memmove(dst, text.data(), text.size());
        dst[text.size()] = 0;
        size = text.size();
        return;
    }
    GameString fresh = make(text);
    if (cap > 15)
        gameFree(ptr);
    *this = fresh;
}

GameString GameString::make(std::string_view text) {
    GameString s{};
    s.size = text.size();
    if (text.size() < 16) {
        memcpy(s.buf, text.data(), text.size());
        s.buf[text.size()] = 0;
        s.cap = 15;
    } else {
        BS_CHECK(text.size() < 4096); // larger blocks use MSVC's aligned-allocation header, which this does not write
        s.ptr = static_cast<char*>(gameMalloc(text.size() + 1));
        memcpy(s.ptr, text.data(), text.size());
        s.ptr[text.size()] = 0;
        s.cap = text.size();
    }
    return s;
}
