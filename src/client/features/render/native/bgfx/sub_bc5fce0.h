#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xbc5fce0 (size 0x41d, 1.26.62.01).
// Every offset below is an instruction [reg+off] / immediate seen in the listing [V].

// a3 (third argument, r8): parameter block.
//   +0x00  u16 data[rc*cc]   element array (accessed linearly as data[cc*row + col])
//   +0x0C  u16 cc            column count
//   +0x0E  u16 rc            row count
//   +0x10  u8  flag          constant-select byte
struct Bc5fce0Params {
    std::uint16_t data[6];   // +0x00..0x0B  array header (real size rc*cc elements)
    std::uint16_t cc;        // +0x0C  column count, bounds the col loop (edi)
    std::uint16_t rc;        // +0x0E  row count, bounds the row loop (ebx)
    std::uint8_t  flag;      // +0x10  selects the xmm6/xmm7/xmm8 constant set
};
static_assert(offsetof(Bc5fce0Params, cc) == 0x0C, "bc5fce0: Params::cc at +0x0C");
static_assert(offsetof(Bc5fce0Params, rc) == 0x0E, "bc5fce0: Params::rc at +0x0E");
static_assert(offsetof(Bc5fce0Params, flag) == 0x10, "bc5fce0: Params::flag at +0x10");

// a2 (second argument, rdx): context block.
//   +0x08  void* sinkPtr   *(sinkPtr)   = destination base (r15)
//   +0x10  void* vtxBase   *(vtxBase)   = vertex buffer base (r12)
struct Bc5fce0Ctx {
    std::uint8_t  pad0[0x08];
    void*         sinkPtr;   // +0x08
    std::uint8_t  pad1[0x08];
    void*         vtxBase;   // +0x10
};
static_assert(offsetof(Bc5fce0Ctx, sinkPtr) == 0x08, "bc5fce0: Ctx::sinkPtr at +0x08");
static_assert(offsetof(Bc5fce0Ctx, vtxBase) == 0x10, "bc5fce0: Ctx::vtxBase at +0x10");

// Vertex record written per element, stride 0xC:
//   +0x00 u16 = r14d (vertex counter)
//   +0x02 u16[4] = r14d lanes + k12 lanes (paddw, wraparound)
//   +0x0A u16 = r14d
// k12 = 4 u16 lanes loaded by movq from 0xF441410 at 0xbc5fde0.

// 0x70-byte block built at [rsp+0x40]..[rsp+0xAC] and copied (0x70 bytes)
// to *r15 by the call at 0xbc5fffc (block[i] = [rsp+0x40+i*4]).
union Bc5fce0Block {
    float f[28];
    std::uint32_t w[28];
};

// Read-only data addresses referenced by the function [V].
static constexpr std::uintptr_t kGblCookie = 0x1230A0C0u;    // stack cookie global ([0x1230A0C0])
static constexpr std::uintptr_t kData_ef3f000 = 0xEF3F000u;  // C0
static constexpr std::uintptr_t kData_eec8060 = 0xEEC8060u;  // C2
static constexpr std::uintptr_t kData_f085aa8 = 0xF085AA8u;  // C1
static constexpr std::uintptr_t kData_efc13a4 = 0xEFC13A4u;  // C3 (xmm9)
static constexpr std::uintptr_t kData_f2cc750 = 0xF2CC750u;  // xmm10
static constexpr std::uintptr_t kData_f441400 = 0xF441400u;  // xmm11
static constexpr std::uintptr_t kData_f441410 = 0xF441410u;  // k12 lanes (movq xmm12)
static constexpr std::uintptr_t kData_f441880 = 0xF441880u;  // u32 table T[16]
static_assert(kData_ef3f000 == 0xEF3F000u, "bc5fce0: data address");
static_assert(kData_eec8060 == 0xEEC8060u, "bc5fce0: data address");
static_assert(kData_f085aa8 == 0xF085AA8u, "bc5fce0: data address");
static_assert(kData_efc13a4 == 0xEFC13A4u, "bc5fce0: data address");
static_assert(kData_f2cc750 == 0xF2CC750u, "bc5fce0: data address");
static_assert(kData_f441400 == 0xF441400u, "bc5fce0: data address");
static_assert(kData_f441410 == 0xF441410u, "bc5fce0: data address");
static_assert(kData_f441880 == 0xF441880u, "bc5fce0: data address");

// vfptr slots read before the two indirect calls (byte offsets in the vtable) [V].
static constexpr std::uintptr_t kVslotCall1 = 0x198u;  // 0xbc5fda3  mov rax,[rax+0x198] -> index 0x33
static constexpr std::uintptr_t kVslotCall2 = 0x1A0u;  // 0xbc5fdfd  mov rax,[rax+0x1A0] -> index 0x34
static_assert(kVslotCall1 / 8 == 0x33u, "bc5fce0: vslot 0x198 = index 0x33");
static_assert(kVslotCall2 / 8 == 0x34u, "bc5fce0: vslot 0x1A0 = index 0x34");

// Loop and frame constants [V].
static constexpr std::uint32_t kElemCap = 0x1800u;  // ebp cap (cmp ebp,0x1800)
static constexpr std::uint32_t kRowDone = 0x17FFu;  // ebp > 0x17FF -> cap path
static constexpr std::uint32_t kBlockSize = 0x70u;  // memcpy size at 0xbc5fffc
static constexpr std::uint32_t kVtxStride = 0xCu;  // add r12,0xC
static constexpr std::uint32_t kCookieSlotOff = 0xB8u;  // [rsp+0xB8] cookie slot

// x64 Microsoft ABI: rcx = a1 (object with vfptr), rdx = a2 (context), r8 = a3 (params).
// Return: void (eax is never set before ret; the original returns garbage) [V].
extern "C" void sub_bc5fce0(void* a1, void* a2, void* a3);

} // namespace native
