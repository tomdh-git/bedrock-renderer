#pragma once
#include <cstddef>
#include <cstdint>
namespace native::bgfx {
struct sub_bc34f70_state { char pad[16]; };
static_assert(offsetof(native::bgfx::sub_bc34f70_state, pad) == 0, "x");
uintptr_t sub_bc34f70(sub_bc34f70_state* self);
} // namespace
