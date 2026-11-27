#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "client/features/render/native/Lift.h"
#include "sdk/SigManager.h"

// sub_ed35e10 (0xed35e10, size 0x49, 1.26.62.01): fills a 0x48-byte stack buffer with
// K32GetProcessMemoryInfo(GetCurrentProcess(), &buffer, 0x48) and returns the qword at
// buffer+0x10 (PROCESS_MEMORY_COUNTERS.WorkingSetSize by SDK layout; the code itself
// proves an 8-byte read at buffer+0x10, the struct identity is [I]).
//
// Whole function [0xed35e10, 0xed35e59), straight line, no branches:
//   0xed35e10  sub rsp,0x88                              ; 0x88-byte stack frame
//   0xed35e17  mov rax,[0x1230A0C0]     ; [data_1230a0c0] stack-cookie global
//   0xed35e1e  xor rax,rsp
//   0xed35e21  mov [rsp+0x70],rax       ; cookie slot
//   0xed35e26  call qword ptr [0xF9A6FD8]  ; [data_f9a6fd8] GetCurrentProcess() via import data slot (rule 68)
//   0xed35e2c  mov r8d,0x48             ; cb = 0x48
//   0xed35e32  lea rdx,[rsp+0x20]       ; ppc = &buffer
//   0xed35e37  mov rcx,rax              ; hProcess = GetCurrentProcess() result
//   0xed35e3a  call 0xEEC5880           ; -> sub_eec5880: K32GetProcessMemoryInfo via its import thunk
//   0xed35e3f  mov rax,[rsp+0x30]       ; rax = buffer+0x10
//   0xed35e44  mov rcx,[rsp+0x70]
//   0xed35e49  xor rcx,rsp
//   0xed35e4c  call 0xE951550           ; -> sub_e951550: stack-cookie check (crt boundary)
//   0xed35e51  add rsp,0x88
//   0xed35e58  ret
//
// Stack frame (observed): PROCESS_MEMORY_COUNTERS buffer at rsp+0x20 (0x48 bytes),
// cookie slot at rsp+0x70; nothing else is stored to or loaded from the frame.
// No argument register is read; the return value (RAX) is buffer+0x10.
// Data addresses below are RVAs; VA = RewriteRegistry::imageBase() + rva.

struct sub_ed35e10Layout {
    static_assert(sizeof(void*) == 8, "sub_ed35e10: x64 ABI, pointer-sized address space");
    // Stack frame layout of the original [0xed35e10, 0xed35e59).
    static constexpr std::uintptr_t kStackFrameSize = 0x88ull;   // sub rsp,0x88 at 0xed35e10
    static constexpr std::uintptr_t kStackBufferOffset = 0x20ull; // buffer at rsp+0x20
    static constexpr std::uintptr_t kStackBufferSize = 0x48ull;   // mov r8d,0x48 at 0xed35e2c
    static constexpr std::uintptr_t kWorkingSetSizeOffset = 0x10ull; // qword read at buffer+0x10: mov rax,[rsp+0x30] at 0xed35e3f
    static constexpr std::uintptr_t kStackCookieOffset = 0x70ull; // mov [rsp+0x70],rax at 0xed35e21
    static constexpr std::uintptr_t kCookieGlobalRva = 0x1230A0C0ull; // [data_1230a0c0] read at 0xed35e17
    static constexpr std::uintptr_t kGetCurrentProcessSlotRva = 0xF9A6FD8ull; // [data_f9a6fd8] called at 0xed35e26
    static_assert(kStackFrameSize == 0x88ull, "sub_ed35e10: frame is 0x88 bytes");
    static_assert(kStackBufferOffset == 0x20ull, "sub_ed35e10: buffer at rsp+0x20");
    static_assert(kStackBufferSize == 0x48ull, "sub_ed35e10: buffer is 0x48 bytes");
    static_assert(kWorkingSetSizeOffset == 0x10ull, "sub_ed35e10: result qword at buffer+0x10");
    static_assert(kStackCookieOffset == 0x70ull, "sub_ed35e10: cookie slot at rsp+0x70");
};

namespace native {

// sub_eec5880 (0xeec5880, size 0x6, 1.26.62.01): lift-set callee
// (docs/data/native_functions.tsv size 0x6; docs/data/native_boundary.tsv line 526: `0xeec5880 lift`).
// Whole function: `0xeec5880  jmp qword ptr [0xF9A7918]` (rule 66: forward-declared here and called
// through its native symbol; never a boundary wrapper). Tail-forwards rcx/rdx/r8 to the address in
// import data slot 0xF9A7918 (slot verified [V] via `rdis str "K32GetProcessMemoryInfo"`: string
// "K32GetProcessMemoryInfo" at 0xF9AC052, slot -> import-by-name RVA 0xF9AC050); BOOL result in EAX/RAX.
int sub_eec5880(void* hProcess, void* ppsmemCounters, std::uint32_t cb);

// sub_e951550 (0xe951550, crt boundary, docs/data/native_boundary.tsv line 467): stack-cookie check.
// Compares its argument against global [data_1230a0c0] (0x1230A0C0); returns on match, otherwise
// transfers to sub_e98e3c0 (process termination, fail fast like the original /GS check).
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// sub_ed35e10 (0xed35e10, size 0x49, 1.26.62.01): argument registers are not read; result in RAX.
// x64 Microsoft ABI. Pure: no writes outside its own stack frame, return value only.
// See sub_ed35e10.cpp for the instruction-by-instruction reversal.
std::uintptr_t sub_ed35e10(void);

} // namespace native
