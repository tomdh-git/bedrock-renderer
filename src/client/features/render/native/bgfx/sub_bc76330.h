#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_ebce5e0(s = rcx, maxlen = edx) -> eax: bounded string length of s, capped at
// maxlen (strnlen-like; returns 0 when s is null). Confirmed at the head of the
// function (test rcx,rcx / xor eax,eax on the null path) and by every existing lift
// that calls it with (ptr, 0x7FFFFFFF). Class lift (docs/data/native_boundary.tsv
// line 504); called as plain C++ and lifted by its own unit. Forward-declared here
// per the lift convention (name sub_<rva>, namespace native).
uint32_t sub_ebce5e0(const char* s, uint32_t maxlen);

} // namespace native

namespace native::bgfx {

// Layout of the state object initialized by sub_0xbc76330 at [rcx]. Only the fields
// the function reads/writes are named; +0x0c is never accessed by this function.
// Offsets [V] from the disassembly of [0xbc76330, 0xbc7637a), Minecraft Windows
// 1.26.62.01.
struct Bc76330State {
    const char* name;            // +0x00  W: = empty-string data at RVA 0xF847A07,
                                 //        then = arg->name on the success path
    std::uint32_t nameLen;       // +0x08  W: = 0, then = sub_ebce5e0 result
    std::uint32_t reserved0x0c;  // +0x0c  not read or written by this function
    std::uint32_t flag;          // +0x10  R/W: init guard read at entry, then = seed
};

// Layout of the argument object at [r8]. Offsets [V] from the disassembly.
struct Bc76330Arg {
    const char* name;   // +0x00  R: passed to sub_ebce5e0, stored into state on success
    std::uint32_t maxLen; // +0x08  R: passed to sub_ebce5e0
};

static_assert(offsetof(Bc76330State, name) == 0x00, "bc76330: state name at +0x00");
static_assert(offsetof(Bc76330State, nameLen) == 0x08, "bc76330: state nameLen at +0x08");
static_assert(offsetof(Bc76330State, reserved0x0c) == 0x0c, "bc76330: state reserved at +0x0c");
static_assert(offsetof(Bc76330State, flag) == 0x10, "bc76330: state flag at +0x10");
static_assert(offsetof(Bc76330Arg, name) == 0x00, "bc76330: arg name at +0x00");
static_assert(offsetof(Bc76330Arg, maxLen) == 0x08, "bc76330: arg maxLen at +0x08");

// sub_0xbc76330(state = rcx, seed = edx, arg = r8) -> eax (int): init-guard helper
// for the bgfx "VV frame-graph builder" path. If state->flag != 0 it returns at once
// (eax undefined). Otherwise state->flag = seed; state->name = empty string;
// state->nameLen = 0; then, when arg->name != 0, state->nameLen = sub_ebce5e0(
// arg->name, arg->maxLen) and, on a non-zero length, state->name = arg->name;
// returns the length on the success path.
// Minecraft Windows 1.26.62.01, [0xbc76330, 0xbc7637a), size 0x4a, depth 7, D0, leaf.
int sub_bc76330(Bc76330State* state, std::uint32_t seed, const Bc76330Arg* arg);

} // namespace native::bgfx
