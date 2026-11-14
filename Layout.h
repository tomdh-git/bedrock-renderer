#pragma once

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define CLASS_FIELD(type, name, offset) \
    AS_FIELD(type, name, get##name); \
    type get##name() const { return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); } \
    void set##name(type v) const { *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset) = std::move(v); }

template <typename Ret, typename... Args>
inline Ret callVirtual(int index, void* self, Args... args) {
    static_assert(std::is_trivially_copyable_v<Ret> && sizeof(Ret) <= sizeof(void*),
                  "callVirtual: Win64 returns these through a hidden sret pointer; use callVirtualRet");
    uintptr_t vt = *reinterpret_cast<uintptr_t*>(self);
    uintptr_t fn = *reinterpret_cast<uintptr_t*>(vt + static_cast<uintptr_t>(index) * sizeof(void*));
    using Fn = Ret(__thiscall*)(void*, Args...);
    return reinterpret_cast<Fn>(fn)(self, args...);
}

// A Win64 member returning a class by value gets the return buffer as the hidden first argument (before `this`),
// and hands the buffer pointer back in RAX; the function is typed that way here.
template <typename Ret, typename... Args>
inline Ret* callVirtualRet(int index, void* self, Ret* out, Args... args) {
    static_assert(!std::is_trivially_copyable_v<Ret> || sizeof(Ret) > sizeof(void*),
                  "callVirtualRet is only for returns that need a hidden sret pointer; use callVirtual");
    uintptr_t vt = *reinterpret_cast<uintptr_t*>(self);
    uintptr_t fn = *reinterpret_cast<uintptr_t*>(vt + static_cast<uintptr_t>(index) * sizeof(void*));
    using Fn = Ret*(__thiscall*)(Ret*, void*, Args...);
    return reinterpret_cast<Fn>(fn)(out, self, args...);
}

template <typename... Args>
inline void callVirtualVoid(int index, void* self, Args... args) {
    uintptr_t vt = *reinterpret_cast<uintptr_t*>(self);
    uintptr_t fn = *reinterpret_cast<uintptr_t*>(vt + static_cast<uintptr_t>(index) * sizeof(void*));
    using Fn = void(__thiscall*)(void*, Args...);
    reinterpret_cast<Fn>(fn)(self, args...);
}

// Unproven SDK stubs: validated null/default + debugger log. No caching, no game addresses.
inline void sdkLogStub(const char* where) {
    if (!where)
        return;
    OutputDebugStringA("[BlueySDK] stub: ");
    OutputDebugStringA(where);
    OutputDebugStringA("\n");
}
