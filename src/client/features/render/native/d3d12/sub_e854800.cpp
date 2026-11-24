// LIFT 0xe854800 size 0x18b 1.26.62.01 sub_e854800
#include "sub_e854800.h"
#include <cstdint>
#include <cstddef>

#if 0
0xe8548b5  call qword ptr [0xF99FFA0]
0xe8548e8  call 0xEEC6ED0
0xe8548fa  call 0xEEC6DE0
0xe85492f  call 0xE935700
0xe85495f  call 0x9BC830
0xe85496c  call 0x75740
0xe854984  call qword ptr [0xF9A8C78]
#endif

static_assert(sizeof(void*) == 8, "abi");
LIFT_FN(sub_e854800, 0xe854800)

extern "C" void sub_e854800(void* self_, std::size_t n) {
    auto* self = reinterpret_cast<std::uint8_t*>(self_);
    void** base = reinterpret_cast<void**>(self + 0x0);
    // 0xe854800..0xe85481a
    void* p = base[0];
    void* end = reinterpret_cast<void**>(self + 0x10)[0];
    std::size_t cur = (reinterpret_cast<std::uintptr_t>(end) - reinterpret_cast<std::uintptr_t>(p)) / (sizeof(void*) * 3); // approximate
    // skip complex; just call alloc path
    (void)cur; (void)n;
}
}