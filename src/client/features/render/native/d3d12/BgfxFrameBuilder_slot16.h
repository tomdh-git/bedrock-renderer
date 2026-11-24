#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe8764f0 (size 0x105, 1.26.62.01).
// BgfxFrameBuilder slot 16: reads a 4-byte length prefix from an std::istream
// (via virtual read()), then reads that many bytes into the output buffer,
// advancing the end pointer by the length. Returns true iff both reads
// succeeded and the second read returned the full length. All paths perform
// the /GS cookie check before returning.
//
//   rcx = stream (std::istream* or compatible), rdx = out (3-qword struct:
//   begin, end, capacity at offsets 0, 8, 16).
//
// Global data slots [V]:
static constexpr std::uintptr_t kGblCookie        = 0x1230A0C0u; // mov rax,[0x1230A0C0]  /GS stack cookie
static constexpr std::uintptr_t kIstreamReadSlot  = 0xF9A7480u;  // call qword ptr [0xF9A7480] (istream::read vtable slot)
static constexpr std::uintptr_t kExceptObj        = 0xF08E738u;  // lea rax,[0xF08E738]     exception object address
static constexpr std::uintptr_t kExceptTypeInfo   = 0xFB3B080u;  // lea rdx,[0xFB3B080]     exception type_info

// out struct fields [V]:
static constexpr std::size_t kOutBegin   = 0x00; // R: begin pointer
static constexpr std::size_t kOutEnd     = 0x08; // R/W: end pointer
static constexpr std::size_t kOutCapacity = 0x10; // R: capacity pointer

static_assert(kOutEnd - kOutBegin == 0x08, "e8764f0: end follows begin");
static_assert(kOutCapacity - kOutEnd == 0x08, "e8764f0: capacity follows end");

// 0xEEC6D80: exception throw helper (lift set, native_functions.tsv row 0xeec6d80).
// Forward-declared here per the lift-callee hard rule; lifted by its own unit.
// Call site 0xe8765e2: rcx=&exceptionObjAddr, rdx=typeInfoAddr. Does not return.
extern "C" void sub_eec6d80(void** exceptionObjPtr, const void* typeInfo);

} // namespace native
