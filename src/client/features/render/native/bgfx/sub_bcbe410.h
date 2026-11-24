#pragma once
#include <cstddef>

static_assert(sizeof(void*) == 8, "x64 ABI");

namespace native {
void sub_eec5ae0(void* p);
}

namespace native::bgfx {
void sub_bcbe410(void);
} // namespace native::bgfx