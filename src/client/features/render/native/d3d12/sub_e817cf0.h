#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Callee sub_ebce430 (0xebce430). Two-instruction forwarder:
//   0xebce430  movzx edx,dl
//   0xebce432  jmp 0xEEC6ED0
// i.e. it forwards (rcx, zero-extended dl, r8) to sub_eec6ed0 (class crt in
// docs/data/native_boundary.tsv). At the call site of 0xe817cf0 it is invoked as
// (rcx = newBuf, dl = 0, r8 = size) => a zero-fill (memset) of `size` bytes.
// It is a tiny forwarder: forward-declared here and called through its native
// symbol (per the lift rules a forwarder is a normal lift item, not a blocker).
extern "C" void sub_ebce430(void* rcx, unsigned char dl, std::size_t r8);

// Callee sub_e804590 (0xe804590). Real function (size 0x2a6, L2 d3d12 D0,
// "entry-indirect"), reached by a tail `jmp` from 0xe817cf0 with:
//   rcx = this + 0xC9AA98, rdx = zero-extended handle, r8 = arg4 (64-bit).
// It is in NEITHER docs/data/native_functions.tsv NOR docs/data/native_boundary.tsv,
// so it is reported as an UNRESOLVED CALL by the progress result; it is still
// forward-declared here (namespace native) so this translation unit is complete and
// the call is emitted with the exact ABI the disassembly shows. Its own unit must
// register it (native_checklist_gen.py --add 0xe804590) before link.
extern "C" void sub_e804590(void* rcx, std::uint16_t edx, std::uint64_t r8);

} // namespace native

namespace native::d3d12 {

// LIFT 0xe817cf0 size 0x15a 1.26.62.01 sub_e817cf0
//
// RendererContextD3D12 base slot 42 (vtbl_f4ed2d0#42 / vtbl_f4eee80#42).
// this = RendererContextD3D12* (rcx). For each context pointer in
// this->m_contexts (a vector of 8-byte pointers at this+0x19F60 .. this+0x19F68),
// it reallocates the per-context buffer pointer at context + handle*8 + 0x1250
// (release old, allocate a zero-filled buffer of 16-byte-rounded size), then
// tail-calls sub_e804590(this + 0xC9AA98, handle, arg4).
//
// Layout / global offsets (every displacement below is proven by the cited range).
constexpr std::uintptr_t kContextBeginOff    = 0x19F60;   // mov r12,[rcx+0x19F60]      context vector begin
constexpr std::uintptr_t kContextEndOff      = 0x19F68;   // mov r13,[rcx+0x19F68]      context vector end
constexpr std::uintptr_t kContextStride      = 8;         // add r12,8                   elements are 8-byte pointers
constexpr std::uintptr_t kBufArrayOff        = 0x1250;    // mov [rbx+rbp*8+0x1250],r15  per-context buffer ptr array
constexpr std::uintptr_t kTailThisOff        = 0xC9AA98;  // add rcx,0xC9AA98           this' passed to sub_e804590
constexpr std::uintptr_t kAllocatorGlobalRva = 0x12ADF800;// mov rcx,[0x12ADF800]        allocator object pointer (data_12adf800)
constexpr std::uintptr_t kSizeTableRva       = 0xF441930; // lea rax,[0xF441930]         u32 size table (data_f441930)
constexpr std::uintptr_t kIndCallSlotRva     = 0xF99FFA0; // call qword ptr [0xF99FFA0]  data-slot call -> sub_eea6040
constexpr std::uint32_t  kSizeRoundAdd       = 0xF;       // add r14d,0xF
constexpr std::uint32_t  kSizeAlignMask      = 0xFFFFFFF0;// and r14d,0xFFFFFFF0           round up to 16

static_assert(kContextEndOff == kContextBeginOff + kContextStride, "context begin/end are adjacent 8-byte pointers");
static_assert((kSizeAlignMask & 0xF) == 0, "size mask clears the low 4 bits (16-byte alignment)");
static_assert((kSizeRoundAdd + 1) == (~kSizeAlignMask + 1), "round-up-16 constant (add 0xF then and ~0xF)");

// The lifted function: exact x64 Microsoft ABI.
//   rcx  = this (RendererContextD3D12*)
//   dx   = handle          (stored [rsp+0x36], later read as ebp)
//   r8d  = formatOrType    (movsxd -> signed index into the u32 size table)
//   r9w  = countOrStrideMul(zero-extended multiplier)
//   stack= arg4            (5th arg, forwarded unchanged to sub_e804590 as r8)
// Returns void (the epilog is the tail jmp into sub_e804590).
extern "C" void sub_e817cf0(void* a0, std::uint16_t a1, std::int32_t a2, std::uint16_t a3, std::uint64_t a4);

} // namespace native::d3d12