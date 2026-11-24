#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

// sub_bc66c50: Frame renderer lambda (size 0x11e, 1.26.62.01).
// Layout constants below are taken from the disassembly of
// [0xbc66c50, 0xbc66d6e); every offset is a register+immediate address seen in the
// function, tagged [V]. The function touches no game struct with a known SDK name:
// fields are accessed by raw offset from the `self` argument and from the element
// base at [self+0x13D18], so the layout is asserted here rather than borrowed.

namespace native {

// 0xebdbf10: jmp qword ptr [0xF9A7B10]  (import thunk forwarder, target loader-resolved) [V]
// 0xebdbf20: jmp qword ptr [0xF9A7B28]  (import thunk forwarder, target loader-resolved) [V]
// Tiny forwarders: forward-declared here (namespace native) and called directly from
// the lifted body, exactly like the original `call 0xEBDBF10` / `call 0xEBDBF20`.
extern "C" void sub_ebdbf10(void* ctx);
extern "C" void sub_ebdbf20(void* ctx);

} // namespace native

namespace native::bgfx {

// self-relative offsets (self = rcx at entry)
static constexpr std::uint32_t kSelfOff_0x180 = 0x180;   // &self[0x180]: address passed to thunk calls (lea, no load) [V]
static constexpr std::uint32_t kSelfOff_0x13D18 = 0x13D18; // self+0x13D18: element-array base pointer (qword R) [V]
static constexpr std::uint32_t kSelfOff_0x13D20 = 0x13D20; // self+0x13D20: u16 header pointer (qword R) [V]
static constexpr std::uint32_t kSelfOff_0x1CFD0C8 = 0x1CFD0C8; // self+0x1CFD0C8: qword argument to the os call (qword R) [V]
static constexpr std::uintptr_t kSelfFootprintSize = 0x1CFD0C8 + 8ull;

// u16 header at [self+0x13D20]
static constexpr std::uint32_t kHdrOffCount = 0x0000;   // hdr+0: u16 incremented by 1 each call [V]
static constexpr std::uint32_t kHdrOffLimit = 0x0002;   // hdr+2: u16 limit compared against count [V]
// hdr+4: u16 entries[]; hdr[2+count] read as pick; hdr[2+limit+pick] written with count [V]

// element layout at [self+0x13D18] + pick * kElemStride
static constexpr std::uint32_t kElemStride = 0x700;     // element stride (imul rbx,rdi,0x700) [V]
static constexpr std::uint32_t kElemOff_0x0000 = 0x0000; // elem+0x0000: qword W (self+0x1CFD0C8), then R (vtable chain base) [V]
static constexpr std::uint32_t kElemOff_0x688 = 0x688;   // elem+0x688: byte W = pick & 0xFF [V]
static constexpr std::uint32_t kElemOff_0x68C = 0x68C;   // elem+0x68C: qword W = 0 [V]
static constexpr std::uint32_t kElemOff_0x694 = 0x694;   // elem+0x694: qword W = 0 [V]
static constexpr std::uint32_t kElemOff_0x6AC = 0x6AC;   // elem+0x6AC: byte W = pick & 0xFF [V]
static constexpr std::uint32_t kElemOff_0x6F0 = 0x6F0;   // elem+0x6F0: qword W = boundary result [V]

// miscellaneous immediates seen in the function
static constexpr std::uint32_t kVtblChainOff = 0xDC57E0; // qword R at [elem[0] + 0xDC57E0] [V]
static constexpr std::uint32_t kPickSentinel = 0xFFFF;   // pick == 0xFFFF -> early exit [V]
static constexpr std::uint32_t kGlobalRva = 0x128767C8;  // dword R: index into gs:[0x58] pointer array [V]
static constexpr std::uint32_t kTlsOff = 0x58;           // gs:[0x58] qword R [V]
static constexpr std::uint32_t kTagBgfx = 0x78666762;    // dword compared at [ptr + 0x2D4C] = "bgfx" [V]

// Element mirror for static layout checks; only the touched offsets are members.
struct ElemLayout {
    std::uintptr_t field_0x0000;                                 // +0x0000
    std::uint8_t pad_0x0008[kElemOff_0x688 - 0x0008];            // -> 0x688
    std::uint8_t field_0x688;                                    // +0x688
    std::uint8_t pad_0x689[kElemOff_0x68C - 0x689];              // -> 0x68C
    std::uint64_t field_0x68C;                                   // +0x68C
    std::uint64_t field_0x694;                                   // +0x694
    std::uint8_t pad_0x69C[kElemOff_0x6AC - 0x69C];              // -> 0x6AC
    std::uint8_t field_0x6AC;                                    // +0x6AC
    std::uint8_t pad_0x6AD[kElemOff_0x6F0 - 0x6AD];              // -> 0x6F0
    std::uint64_t field_0x6F0;                                   // +0x6F0
    std::uint8_t pad_0x6F8[kElemStride - 0x6F8];                 // -> 0x700
};
static_assert(offsetof(ElemLayout, field_0x0000) == kElemOff_0x0000, "bc66c50: element field at +0x0000");
static_assert(offsetof(ElemLayout, field_0x688) == kElemOff_0x688, "bc66c50: element field at +0x688");
static_assert(offsetof(ElemLayout, field_0x68C) == kElemOff_0x68C, "bc66c50: element field at +0x68C");
static_assert(offsetof(ElemLayout, field_0x694) == kElemOff_0x694, "bc66c50: element field at +0x694");
static_assert(offsetof(ElemLayout, field_0x6AC) == kElemOff_0x6AC, "bc66c50: element field at +0x6AC");
static_assert(offsetof(ElemLayout, field_0x6F0) == kElemOff_0x6F0, "bc66c50: element field at +0x6F0");
static_assert(sizeof(ElemLayout) == kElemStride, "bc66c50: element size equals 0x700 stride");

// uint32_t sub_bc66c50(void* self /*rcx*/); returns element base (rax), self[0x13D18]
// (fast path) or nullptr (early exits). Footprint covers the self-relative region
// [0, 0x1CFD0C8+8); element stores at [self+0x13D18]+pick*0x700 and the
// vtable-chain store have dynamic targets (V2 gap, whole-frame V3 covers).
native::Footprint sub_bc66c50_footprint(void* self);
void* sub_bc66c50(void* self);

} // namespace native::bgfx
