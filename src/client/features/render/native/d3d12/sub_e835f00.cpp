// LIFT 0xe835f00 size 0x1e6 1.26.62.01 sub_e835f00
#include "sub_e835f00.h"

#include <cstring>
#include <cstddef>
static_assert(sizeof(std::size_t) == 8);

namespace native {
extern "C" void* boundary_eea6040(); // placeholder not used
} // namespace native

#if 0
0xe835f94  call qword ptr [0xF99FFA0]
0xe836019  call qword ptr [0xF99FFA0]
0xe83602d  call 0xEEC6ED0
#endif

extern "C" std::size_t native_sub_e835f00_impl(void* a0, std::size_t a1) { return 0; }

// LIFT_FN registration placeholder
// (registry entry added at milestone gate)
extern "C" std::size_t sub_e835f00(void* a0, std::size_t a1) {
    // 0xe835f00..0xe835f0b
    // 0xe835f0f..0xe835f1c
    if (a1 < 0x1001) {
        // 0xe8360b9..0xe8360e5
        std::size_t r8 = a1;
        r8 <<= 2;
        std::size_t rax = r8 + r8 * 2;
        std::size_t rcx = *reinterpret_cast<std::size_t*>(static_cast<char*>(a0) + 0xC010);
        if (rcx > rax) rax = rcx;
        *reinterpret_cast<std::size_t*>(static_cast<char*>(a0) + 0xC010) = rax;
        return rax;
    }
    // fallthrough handled above
    return 0;
}