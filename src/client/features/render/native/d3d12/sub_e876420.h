#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe876420 (size 0xc5, 1.26.62.01).
// BgfxFrameBuilder slot 16: reads 1 byte through a guarded indirect-call slot,
// optionally writes 0x100 to the destination buffer and re-queries the slot,
// returns true on success. Every offset below is an instruction [reg+off] seen
// in the listing [V].

// Read-only data / globals referenced by the function [V].
static constexpr std::uintptr_t kGblCookie  = 0x1230A0C0u; // mov rax,[0x1230A0C0]  (/GS stack cookie)
static constexpr std::uintptr_t kSlotAddr   = 0xF9A7480u;  // call qword ptr [0xF9A7480] (indirect copy slot)
static constexpr std::uintptr_t kErrFilePtr = 0xF08E738u;  // lea rax,[0xF08E738]   (error record file ptr)
static constexpr std::uintptr_t kErrDataPtr = 0xFB3B080u;  // lea rdx,[0xFB3B080]   (error record data ptr)

// Stack error record layout (zeroed at [rsp+0x30..0x3F], ptr at [rsp+0x28]) [V].
struct E876420ErrorRecord {
    void* file;                  // +0x00 = 0xF08E738
    std::uint8_t payload[0x10];  // +0x08..0x17 zeroed (16 bytes)
};
static_assert(sizeof(E876420ErrorRecord) == 0x18, "e876420: error record footprint 0x18");
static_assert(offsetof(E876420ErrorRecord, file) == 0x00, "e876420: error record file at +0x00");

// Forward declaration for lift-set callee (0xeec6d80, native_boundary.tsv class 'lift').
// Called at 0xe8764d2 with rcx = &errorRecord, rdx = 0xFB3B080.
extern "C" void sub_eec6d80(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// x64 Microsoft ABI: rcx = obj (BgfxFrameBuilder*), rdx = dst (void* buffer).
// Return: bool in al (true when the byte query said 1, or the byte was not 1;
// when the byte is 1, true iff the follow-up slot call returned status == 1).
extern "C" bool sub_e876420(void* obj, void* dst);

} // namespace native