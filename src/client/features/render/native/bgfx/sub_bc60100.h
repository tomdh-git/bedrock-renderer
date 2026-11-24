#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Stack descriptor built by sub_0xbc60100 at [rsp+0x28]/[rsp+0x30] (ptr/len) and
// [rsp+0x38]/[rsp+0x40] (ptr/len); passed by pointer to sub_ebce570.
// Offsets [V] from the disassembly of [0xbc60100, 0xbc60731), Minecraft Windows 1.26.62.01.
struct StrDesc {
    const char* ptr;   // +0x00
    uint32_t len;      // +0x08
};

// Lift-set callees of sub_0xbc60100 (docs/data/native_boundary.tsv, class lift, called x16
// and x15 respectively). Forward-declared here per the lift convention (name sub_<rva>,
// namespace native); each is called as plain C++ and lifted by its own unit.
// sub_ebce5e0(s = rcx, maxlen = edx) -> eax: bounded length of s (strnlen-like, 0 if s is null).
uint32_t sub_ebce5e0(const char* s, uint32_t maxlen);
// sub_ebce570(desc0 = &rcx, desc1 = &rdx, maxlen = r8d) -> eax: 0 iff the two descriptors'
// strings are equal (bounded strcmp-like semantics; result is *desc0.ptr - *desc1.ptr on
// the first differing byte, otherwise the length comparison).
int sub_ebce570(const StrDesc* a0, const StrDesc* a1, uint32_t maxlen);

static_assert(offsetof(StrDesc, ptr) == 0x00, "sub_0xbc60100: descriptor ptr at +0x00");
static_assert(offsetof(StrDesc, len) == 0x08, "sub_0xbc60100: descriptor len at +0x08");
static_assert(sizeof(StrDesc) == 0x10, "sub_0xbc60100: descriptor size 0x10");

} // namespace native

namespace native::bgfx {

// sub_0xbc60100(name = rcx) -> eax (int): index of name in the fixed 14-entry uniform-name
// table at RVA 0xF4418C0 (indices 0..13), or 14 when not found; a null name returns 14.
// The table entries are the literals u_viewRect, u_viewTexel, u_view, u_invView, u_proj,
// u_invProj, u_viewProj, u_invViewProj, u_prevViewProj, u_model, u_modelView,
// u_modelViewProj, u_prevWorldPosOffset, u_alphaRef4 in that order ([V]: index per match
// target at 0xbc606a7..0xbc606f8; table pointer count 14 [V: cmp rsi,0xE at 0xbc601c2]).
// Minecraft Windows 1.26.62.01, [0xbc60100, 0xbc60731), size 0x631, depth 1, D0.
int sub_bc60100(const char* name);

} // namespace native::bgfx
