// LIFT 0xbc61e20 size 0x215 1.26.62.01 bgfx::Frame::sort
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/Frame_sort.h"

#include <cstddef>
#include <cstdint>

static_assert(0x14700 == 0x14700);
static_assert(0x94700 == 0x94700);

extern "C" void sub_bc62040(void* keys, void* tempKeys, void* values, void* tempValues, uint32_t count);
extern "C" void sub_bc62bc0(void* keys, void* tempKeys, uint32_t count);
extern "C" void sub_e951550(void* cookie);

// 0xbc61e20  push rsi
// 0xbc61f67  call 0xBC62040
// 0xbc6201f  jmp 0xBC62BC0
// 0xbc6202f  call 0xE951550
// 0xbc61e21  push rdi
// 0xbc61e22  sub rsp,0x238
// 0xbc61f67  call 0xBC62040
// 0xbc6201f  jmp 0xBC62BC0
// 0xbc6202f  call 0xE951550

namespace native::bgfx {

void Frame_sort(void* self) {
    // 0xbc61e20..0xbc61e3e
    uint16_t viewRemap[256];
    // 0xbc61e40..0xbc61e7a
    for (uint32_t idx = 0; i < 256; idx += 4) {
        uint16_t v0 = *reinterpret_cast<const uint16_t*>(static_cast<const uint8_t*>(self) + 0x0 + idx*2);
        viewRemap[v0] = static_cast<uint16_t>(i);
        uint16_t v1 = *reinterpret_cast<const uint16_t*>(static_cast<const uint8_t*>(self) + 0x0 + (idx+1)*2);
        viewRemap[v1] = static_cast<uint16_t>(i+1);
        uint16_t v2 = *reinterpret_cast<const uint16_t*>(static_cast<const uint8_t*>(self) + 0x0 + (idx+2)*2);
        viewRemap[v2] = static_cast<uint16_t>(i+2);
        uint16_t v3 = *reinterpret_cast<const uint16_t*>(static_cast<const uint8_t*>(self) + 0x0 + (idx+3)*2);
        viewRemap[v3] = static_cast<uint16_t>(i+3);
    }

    // 0xbc61e7c..0xbc61f3a
    uint32_t numItems = *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(self) + 0xDC57E8);
    for (uint32_t idx = 0; idx + 1 < numItems; idx += 2) {
        uint64_t k0 = reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(self) + 0x14700)[idx];
        uint8_t view0 = static_cast<uint8_t>(k0 >> 54);
        k0 = (k0 & 0xC03FFFFFFFFFFFFFull) | (static_cast<uint64_t>(viewRemap[view0]) << 54);
        reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(self) + 0x14700)[idx] = k0;

        uint64_t k1 = reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(self) + 0x14700)[idx+1];
        uint8_t view1 = static_cast<uint8_t>(k1 >> 54);
        k1 = (k1 & 0xC03FFFFFFFFFFFFFull) | (static_cast<uint64_t>(viewRemap[view1]) << 54);
        reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(self) + 0x14700)[idx+1] = k1;
    }
    if (numItems & 1) {
        uint32_t idx = numItems - 1;
        uint64_t k = reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(self) + 0x14700)[idx];
        uint8_t view = static_cast<uint8_t>(k >> 54);
        k = (k & 0xC03FFFFFFFFFFFFFull) | (static_cast<uint64_t>(viewRemap[view]) << 54);
        reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(self) + 0x14700)[idx] = k;
    }

    // 0xbc61f3a..0xbc61f67  call 0xbc62040
    void* ctx = *reinterpret_cast<void**>(0x12AE1748);
    void* tempKeys = static_cast<uint8_t*>(ctx) + 0x1CFD0D0;
    void* tempValues = static_cast<uint8_t*>(ctx) + 0x1D7D0C8;
    void* sortValues = static_cast<uint8_t*>(self) + 0x94700;
    void* sortKeys = static_cast<uint8_t*>(self) + 0x14700;
    sub_bc62040(sortKeys, tempKeys, sortValues, tempValues, numItems);

    // 0xbc61f6c..0xbc61fdf
    uint16_t numBlit = *reinterpret_cast<uint16_t*>(static_cast<uint8_t*>(self) + 0xDC57EC);
    uint32_t n = numBlit;
    for (uint32_t idx = 0; idx + 1 < n; idx += 2) {
        uint8_t* b0 = static_cast<uint8_t*>(self) + 0x934778 + idx*4 + 3;
        *b0 = static_cast<uint8_t>(viewRemap[*b0]);
        uint8_t* b1 = static_cast<uint8_t*>(self) + 0x934778 + (idx+1)*4 + 3;
        *b1 = static_cast<uint8_t>(viewRemap[*b1]);
    }
    if (n & 1) {
        uint8_t* b = static_cast<uint8_t*>(self) + 0x934778 + (n-1)*4 + 3;
        *b = static_cast<uint8_t>(viewRemap[*b]);
    }

    // 0xbc61fe6..0xbc6201f  jmp 0xbc62bc0
    void* blitKeys = static_cast<uint8_t*>(self) + 0x934778;
    sub_bc62bc0(blitKeys, tempKeys, numBlit);

    // 0xbc62024..0xbc62034  __security_check_cookie failure path
    // 0xbc62024  mov rcx,[rsp+0x230]
    // 0xbc6202c  xor rcx,rsp
    // 0xbc6202f  call 0xE951550
    sub_e951550(reinterpret_cast<void*>(0));
}

static native::Footprint Frame_sort_footprint(void* self) {
    return { { self, 0xDC57ED } };
}

LIFT_FN(Frame_sort, "bgfx::Frame::sort", 0xbc61e20, Frame_sort, Frame_sort_footprint);

} // namespace native::bgfx
