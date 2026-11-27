#pragma once
#include <cstddef>
#include <cstdint>
#include <intrin.h>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"
#include "client/features/render/native/Lift.h"

// sub_9bd3c0 (0x9bd3c0, size 0x82, 1.26.62.01):
// Guard function that checks a global counter against a TLS slot limit.
// If the check passes, calls sub_9bd230(&g_128d7fc0, a0->field0) and returns its result.
// If the check fails, runs an error sequence: calls sub_e938cb0(&g_128d8040); if g_128d8040
// becomes != -1, retries the normal path; otherwise calls sub_9bde00(), then
// sub_e935740(&sub_9bdf00), then sub_e938d70(&g_128d8040), then retries normal path.
// All paths ultimately call sub_9bd230 and return its RAX.
//
// Reads: [a0+0x0] (dword), g_128d8040 (dword), g_128767c8 (dword, TLS index),
// g_128d7fc0 (dword, address taken), TLS[g_128767c8]+4 (dword).
// Writes: none directly; g_128d8040 written by boundary callees.
// Calls: sub_9bd230 (unresolved), sub_9bde00 (unresolved),
// sub_e938cb0 (boundary os), sub_e935740 (boundary os), sub_e938d70 (boundary os).
// x64 Microsoft ABI: argument in RCX, return in RAX.

struct sub_9bd3c0Layout {
    // ABI
    static_assert(sizeof(void*) == 8, "sub_9bd3c0: x64 ABI, pointer-sized address space");
    // Argument layout: a0 points to an object with a dword at offset 0
    static constexpr std::size_t kArgField0Offset = 0x0;
    static_assert(kArgField0Offset == 0x0, "sub_9bd3c0: arg field0 at +0x0");
    // Global RVAs (relative to image base)
    static constexpr std::uintptr_t kG128D8040Rva = 0x128D8040;  // dword
    static constexpr std::uintptr_t kG128767C8Rva = 0x128767C8;  // dword (TLS index)
    static constexpr std::uintptr_t kG128D7FC0Rva = 0x128D7FC0;  // dword
    static constexpr std::uintptr_t kSub9BDF00Rva = 0x9BDF00;    // function address
};

// Boundary callees (os class, docs/data/native_boundary.tsv) - declared at global scope
// to avoid nested-namespace lookup issues; referenced inside native:: via ::
::native::Boundary<void, void*> sub_e938cb0("sub_e938cb0");   // 0xE938CB0: called with &g_128d8040
::native::Boundary<void, void*> sub_e935740("sub_e935740");   // 0xE935740: called with &sub_9bdf00
::native::Boundary<void, void*> sub_e938d70("sub_e938d70");   // 0xE938D70: called with &g_128d8040

namespace native {

// Unresolved callees (neither in lift set nor native_boundary.tsv; native_boundary_candidates.tsv: '?')
// Forward-declared with ABI derived from call sites; documented in oc_U-EX7.9bd3c0.md ## UNRESOLVED CALL
extern "C" std::uintptr_t sub_9bd230(void* global_ptr, std::uint32_t value);  // 0x9BD230
extern "C" void sub_9bde00(void);                                               // 0x9BDE00

// Bring boundary objects into native namespace for unqualified calls
using ::sub_e938cb0;
using ::sub_e935740;
using ::sub_e938d70;

// sub_9bd3c0 (0x9bd3c0, 0x82 bytes, 1.26.62.01): argument `a0` in RCX, returns RAX.
std::uintptr_t sub_9bd3c0(void* a0);

} // namespace native