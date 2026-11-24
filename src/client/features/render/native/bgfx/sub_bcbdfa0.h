#pragma once
#include <cstddef>

static_assert(sizeof(void*) == 8, "x64 ABI");

namespace native {
void sub_eec7570(const void* p); // strlen-ish helper used when len == -1
}

namespace native::bgfx {
void sub_bcbe410(); // assert/error path ("invalid bitset char")

// Signature: sub_bcbdfa0(void* out, const char* str, size_t len, char c4, char c5) -> void*
void* sub_bcbdfa0(void* out, const char* str, std::size_t len, char c4, char c5);
} // namespace native::bgfx