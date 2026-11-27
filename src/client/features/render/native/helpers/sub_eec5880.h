#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_eec5880 (0xeec5880, size 0x6, 1.26.62.01): the whole function is one instruction,
//   0xeec5880  jmp qword ptr [0xF9A7918]     ; [data_f9a7918]
// an indirect tail jump through data slot 0xF9A7918 (.rdata, file off 0xf9a6318). The
// slot holds import-by-name RVA 0xF9AC050: hint 14, name 'K32GetProcessMemoryInfo'
// (kernel32) [V: PE import table read, slot RVA 0xF9A7918 -> import-by-name RVA
// 0xF9AC050 -> hint 14, name K32GetProcessMemoryInfo]. At runtime the loader fills the
// slot with that function's address, so the jmp is a tail call to
//   BOOL WINAPI K32GetProcessMemoryInfo(HANDLE hProcess, PPROCESS_MEMORY_COUNTERS ppsmemCounters, DWORD cb)
// RCX = hProcess, RDX = ppsmemCounters (pointer to a 0x50-byte buffer at every call
// site), R8D = cb = 0x50; all are forwarded unchanged, the BOOL return in EAX
// propagates to the caller, and control never returns here. No memory is read or
// written by the instruction itself beyond the 8-byte slot load.
//
// This function reads no struct fields and writes none: there are no layout offsets to
// assert. The x64 ABI contract is asserted below.
//
// Real Win32 types mapped to C++: BOOL = int, HANDLE = void*, PPROCESS_MEMORY_COUNTERS
// = void*, DWORD = unsigned int (x64 Microsoft ABI).
extern "C" int K32GetProcessMemoryInfo(void* hProcess, void* ppsmemCounters, unsigned int cb);

struct sub_eec5880Layout {
    static_assert(sizeof(void*) == 8, "sub_eec5880: x64 ABI, pointer-sized address space");
    using Fn = int (__cdecl*)(void*, void*, unsigned int);
    static_assert(sizeof(Fn) == 8, "sub_eec5880: x64 function pointer is 8 bytes");
};

namespace native {

// Signature of sub_eec5880 itself: identical to the target (tail forwarder, no register
// shuffling). x64 Microsoft ABI: hProcess in RCX, ppsmemCounters in RDX, cb in R8D;
// int (BOOL) result in EAX. R9 and the XMM registers are forwarded implicitly by the
// original's tail jump; no call site sets R9 before calling and none reads it after.
int sub_eec5880(void* hProcess, void* ppsmemCounters, unsigned int cb);

} // namespace native
