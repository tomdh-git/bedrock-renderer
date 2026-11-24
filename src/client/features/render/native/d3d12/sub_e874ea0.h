#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe874ea0 (size 0x7b, 1.26.62.01).
// BgfxFrameBuilder slot 16: copies 2 bytes from a source buffer into the builder object
// via a guarded indirect-call slot, returns true on success (status == 2).
// Every offset below is an instruction [reg+off] seen in the listing [V].

// Read-only data / globals referenced by the function [V].
static constexpr std::uintptr_t kGblCookie     = 0x1230A0C0u; // mov rax,[0x1230A0C0]  (/GS stack cookie)
static constexpr std::uintptr_t kSlotAddr      = 0xF9A7480u;  // call qword ptr [0xF9A7480] (indirect copy slot)
static constexpr std::uintptr_t kErrFilePtr    = 0xF08E738u;  // lea rax,[0xF08E738]   (error record file ptr)
static constexpr std::uintptr_t kErrDataPtr    = 0xFB3B080u;  // lea rdx,[0xFB3B080]   (error record data ptr)

// Stack error record layout (zeroed at [rsp+0x30..0x3F], ptr at [rsp+0x28]) [V].
struct E874EA0ErrorRecord {
    void* file;                  // +0x00 = 0xF08E738
    std::uint8_t payload[0x10];  // +0x08..0x17 zeroed (16 bytes)
};
static_assert(sizeof(E874EA0ErrorRecord) == 0x18, "e874ea0: error record footprint 0x18");
static_assert(offsetof(E874EA0ErrorRecord, file) == 0x00, "e874ea0: error record file at +0x00");

// Forward declaration for lift-set callee (0xeec6d80, native_boundary.tsv class 'lift').
// Called at 0xe874f08 with rcx = &errorRecord, rdx = 0xFB3B080.
extern "C" void sub_eec6d80(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// x64 Microsoft ABI: rcx = obj (BgfxFrameBuilder*), rdx = dst (void* buffer).
// Return: bool in al (true if copied exactly 2 bytes, i.e. status == 2).
extern "C" bool sub_e874ea0(void* obj, void* dst);

} // namespace native