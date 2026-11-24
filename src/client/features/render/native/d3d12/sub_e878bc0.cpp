// LIFT 0xe878bc0 size 0xba 1.26.62.01 sub_e878bc0
#include "sub_e878bc0.h"

#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "client/features/render/native/Lift.h"

namespace native {
namespace d3d12 {

// Verbatim call/jmp instructions from the disassembly of [0xe878bc0, 0xe878c7a):
//   0xe878be5  call 0x1F5EF50          boundary::sub_1f5ef50 (stl boundary, native_boundary.tsv)
//   0xe878bf3  call 0xE935700          native::sub_e935700 (lift callee; jmp 0x392960)
//   0xe878c2d  call 0xE935700          native::sub_e935700 (lift callee)
//   0xe878c54  jmp 0xE935700            native::sub_e935700 (tail call)
//   0xe878c73  call qword ptr [0xF9A8C78]  IAT slot of _invoke_watson, noreturn
#if 0
0xe878be5  call 0x1F5EF50
0xe878bf3  call 0xE935700
0xe878c2d  call 0xE935700
0xe878c54  jmp 0xE935700
0xe878c73  call qword ptr [0xF9A8C78]
#endif

static native::Footprint sub_e878bc0_footprint(void* a0)
{
    // Direct writes of this function: the 24-byte zero region [sub + 0x20, sub + 0x38).
    native::Footprint fp;
    if (void* sub = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(a0) + kOffA0Sub))
        fp.push_back({static_cast<std::uint8_t*>(sub) + 0x20, 0x18});
    return fp;
}

void sub_e878bc0(void* a0)
{
    void* sub = nullptr;
    void* container = nullptr;
    void* buf = nullptr;
    void* end = nullptr;
    uintptr_t remaining = 0;

    // 0xe878bc0..0xe878be5: prologue (push rsi/rdi, sub rsp, 0x28);
    //   sub = [a0 + 0x8]; if (sub == 0) goto loc_e878c59 (epilogue + ret)
    sub = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(a0) + kOffA0Sub);
    if (sub == nullptr) {
        return;
    }

    // 0xe878bd3..0xe878be5: container = [sub + 0x38];
    //   boundary::sub_1f5ef50(container, container, [container + 0x8])  (rcx, rdx, r8)
    container = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(sub) + kOffSubContainer);
    boundary::sub_1f5ef50(container, container,
                          *reinterpret_cast<void**>(static_cast<std::uint8_t*>(container) +
                                                    kOffContainer8));

    // 0xe878bea..0xe878bf3: sub_e935700(container, 0x50)
    native::sub_e935700(container, 0x50ULL);

    // 0xe878bf8..0xe878bff: buf = [sub + 0x20]; if (buf == 0) goto loc_e878c40
    buf = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(sub) + kOffSubBuf);
    if (buf != nullptr) {
        // 0xe878c01..0xe878c20: end = [sub + 0x30]; remaining = end - buf;
        //   if (remaining < 0x1000) goto loc_e878c29 (skip block-header check)
        end = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(sub) + kOffSubEnd);
        remaining = reinterpret_cast<uintptr_t>(end) - reinterpret_cast<uintptr_t>(buf);
        if (remaining >= 0x1000ULL) {
            // 0xe878c11..0xe878c26: blockHdr = [buf - 8];
            //   blockSize = (buf - 8) - blockHdr; if (blockSize >= 0x20) goto loc_e878c60
            void* blockHdr = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(buf) - 8);
            uintptr_t blockSize =
                (reinterpret_cast<uintptr_t>(buf) - 8) - reinterpret_cast<uintptr_t>(blockHdr);
            if (blockSize >= 0x20ULL) {
                // loc_e878c60..0xe878c7a: heap corruption -> call qword ptr [0xF9A8C78]
                // (_invoke_watson via IAT slot 0xF9A8C78, VA 0x14F9A8C78 at image base 0x140000000;
                // all five arguments zeroed; noreturn - int3 padding follows at 0xe878c79..0xe878c7f)
                uintptr_t watsonSlot =
                    *reinterpret_cast<uintptr_t*>(0x140000000ULL + 0xF9A8C78);
                reinterpret_cast<void(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*,
                                                unsigned int, uintptr_t)>(
                    watsonSlot)(nullptr, nullptr, nullptr, 0, 0);
                // noreturn: control never continues past this call
            }
            buf = blockHdr;
            remaining += 0x27ULL;
        }
        // loc_e878c29..0xe878c38: sub_e935700(buf, remaining);
        //   then zero [sub + 0x20 .. sub + 0x30) and [sub + 0x30]
        native::sub_e935700(buf, remaining);
        *reinterpret_cast<uint64_t*>(static_cast<std::uint8_t*>(sub) + kOffSubBuf) = 0;
        *reinterpret_cast<uint64_t*>(static_cast<std::uint8_t*>(sub) + kOffSubBuf + 8) = 0;
        *reinterpret_cast<uint64_t*>(static_cast<std::uint8_t*>(sub) + kOffSubEnd) = 0;
    }

    // loc_e878c40..0xe878c54: sub = [a0 + 0x8]; if (sub == 0) goto loc_e878c59 (ret);
    //   else tail jump to sub_e935700(sub, 0x48)
    sub = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(a0) + kOffA0Sub);
    if (sub == nullptr) {
        return;
    }
    return native::sub_e935700(sub, 0x48ULL); // 0xe878c54 jmp 0xE935700 (tail call)
}

LIFT_FN(sub_e878bc0, "sub_e878bc0", 0xe878bc0, sub_e878bc0, sub_e878bc0_footprint);

} // namespace d3d12
} // namespace native
