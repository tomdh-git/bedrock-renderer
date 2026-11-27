#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_336380 (0x336380, size 0x97, 1.26.62.01):
//   x64 Microsoft ABI: RCX = a1, RDX = a2, R8 = a3, R9 = a4, return EAX (std::int32_t).
//   Negative call results are converted to -1 (mov eax,0xFFFFFFFF; cmovns eax,ecx).
//   Reads: stack cookie global [0x1230A0C0] (twice), sub_aa3c0 result rax = 0x128C1588,
//   [0x128C1588] (dereferenced), indirect call slot [0xF9A8B20] (read at call time).
//   Writes: stack frame slots only ([rsp+0x20], [rsp+0x28], [rsp+0x38], [rsp+0x40], [rsp+0x88]).
//   Calls: 0xAA3C0 sub_aa3c0 (unresolved callee - not in the lift set and not a boundary function;
//   its known constant effect rax = 0x128C1588 is substituted), qword [0xF9A8B20] (indirect),
//   0xE951550 (crt boundary, cookie-failure path only, noreturn).
// No game struct/fields are touched: all accesses are stack slots and global data slots.
struct sub_336380Layout {
    static constexpr std::uintptr_t kFrameSize = 0x48;            // sub rsp,0x48
    static constexpr std::uintptr_t kArg5Slot = 0x20;             // [rsp+0x20] = 0 (5th arg of the indirect call)
    static constexpr std::uintptr_t kArg6Slot = 0x28;             // [rsp+0x28] = r14 = &a4 slot (6th arg)
    static constexpr std::uintptr_t kR14CopySlot = 0x38;          // [rsp+0x38] = r14 copy (dead store)
    static constexpr std::uintptr_t kCookieSlot = 0x40;           // [rsp+0x40] = [0x1230A0C0] ^ rsp
    static constexpr std::uintptr_t kSpilledA4Slot = 0x88;        // [rsp+0x88] = r9 = a4
    static constexpr std::uintptr_t kGblCookieRva = 0x1230A0C0;   // data_1230a0c0: /GS stack cookie global
    static constexpr std::uintptr_t kData128c1588Rva = 0x128C1588;  // data_128c1588: sub_aa3c0 returns its address
    static constexpr std::uintptr_t kDispatchSlotRva = 0xF9A8B20; // data_f9a8b20: indirect call target slot
    static constexpr std::uintptr_t kTagBit = 2;                  // or rcx,2
    static constexpr std::int32_t kNegativeResult = -1;           // mov eax,0xFFFFFFFF / cmovns: negatives -> -1
    static_assert(kFrameSize == 0x48, "sub_336380: stack frame is 0x48 bytes");
    static_assert(kArg5Slot == 0x20, "sub_336380: 5th-arg slot at [rsp+0x20]");
    static_assert(kArg6Slot == 0x28, "sub_336380: 6th-arg slot at [rsp+0x28]");
    static_assert(kR14CopySlot == 0x38, "sub_336380: r14 copy slot at [rsp+0x38]");
    static_assert(kCookieSlot == 0x40, "sub_336380: cookie slot at [rsp+0x40]");
    static_assert(kSpilledA4Slot == 0x88, "sub_336380: spilled a4 slot at [rsp+0x88]");
    static_assert(kGblCookieRva == 0x1230A0C0, "sub_336380: stack cookie global at 0x1230A0C0");
    static_assert(kData128c1588Rva == 0x128C1588, "sub_336380: data_128c1588 at 0x128C1588");
    static_assert(kDispatchSlotRva == 0xF9A8B20, "sub_336380: indirect call slot at 0xF9A8B20");
    static_assert(kTagBit == 2, "sub_336380: tag bit is 2");
    static_assert(kNegativeResult == -1, "sub_336380: negative results become -1");
};

namespace native {

// sub_e951550 (0xE951550, crt boundary, docs/data/native_boundary.tsv line 467): /GS cookie-failure
// routine (__report_gsfailure-style). Called with RCX = decoded cookie; noreturn on mismatch.
Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// sub_aa3c0 (0xAA3C0, size 0x8, 1.26.62.01): `lea rax,[0x128C1588]; ret` — returns the
// address of data_128c1588. Classified `lift` in docs/data/native_functions.tsv (line 15)
// and docs/data/native_boundary.tsv (line 529): NOT a blocker per hard rule #66.
// Forward-declared here; will be lifted by its own unit and linked at the milestone gate.
// Called from sub_336380 at `0x3363b6  call 0xAA3C0`.
std::uintptr_t sub_aa3c0();

// sub_336380 (0x336380, 0x97 bytes, 1.26.62.01): `a1` in RCX, `a2` in RDX, `a3` in R8, `a4` in R9,
// returns EAX (std::int32_t; negatives converted to -1). See sub_336380.cpp for the instruction
// ranges each statement implements.
std::int32_t sub_336380(void* a1, void* a2, void* a3, void* a4);

} // namespace native
