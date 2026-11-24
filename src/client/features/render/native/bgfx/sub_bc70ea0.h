#pragma once
#include <cstddef>
#include <cstdint>

#include <cstddef>

namespace native {

static_assert(sizeof(void*) == 8, "x64");

constexpr std::uintptr_t kSlotF99FFA0 = 0xF99FFA0;

void sub_ebdbf10(void* lock);
void sub_ebdbf20(void* lock);

// forward decls (lift callees)
struct State_bc70ca0;
void sub_bc70ca0(State_bc70ca0* state, std::uint16_t* out, std::uint32_t arg2, std::uint32_t arg3, std::uint16_t arg4);
struct RenderContext_bc70ff0;
void sub_bc70ff0(RenderContext_bc70ff0* ctx, std::uint16_t dx, std::uint32_t d32, std::uint64_t q64);

std::uint16_t* sub_bc70ea0(void* ctx, std::uint16_t* out, void* info, std::uint32_t arg, std::uint16_t arg4);

} // namespace native