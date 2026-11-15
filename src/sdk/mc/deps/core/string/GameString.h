#pragma once

// std::string as the game (Release STL) lays it out: 32 bytes, {union{char buf[16]; char* ptr;}, size, cap}.
// Our Debug STL has a different layout, so anything the game reads or writes as a std::string uses this.
// A heap buffer comes from the game's own allocator (ucrtbase malloc), because the game frees or replaces it.
// Releases memory the game allocated (its CRT heap, not ours: a Debug CRT free() on it aborts).
void gameFree(void* p);
void* gameMalloc(size_t n); // the game's own heap: memory the game will free must come from here

struct GameString {
    union {
        char buf[16];
        char* ptr;
    };
    size_t size = 0;
    size_t cap = 15;

    static GameString make(std::string_view text);
    void assign(std::string_view text); // replaces the content; the old heap buffer goes back to the game heap
    const char* data() const { return cap > 15 ? ptr : buf; }
    std::string_view view() const { return {data(), size}; }
};
static_assert(sizeof(GameString) == 32);
