#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Object addressed by *a0 on entry to sub_6622590.
// Only the offsets the function touches are declared; the rest is padding.
// Reverse-engineered from [0x6622590, 0x6622602), Minecraft Windows 1.26.62.01.
struct ScopeCounter {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0F: not touched by the function
    std::uint16_t count0x10;      // +0x10: 16-bit counter, interlocked increment (RW, lock inc, 0x66225be)
    std::uint8_t flag0x12;        // +0x12: flag byte, bit 0 is the return value (R, 0x66225c3)
};

// Read-only globals used by the function (absolute addresses, same image base as the exe).
static constexpr uintptr_t kAddrScopeSeq = 0x0129C13C0ULL;   // dword scope sequence (R, 0x662259d / re-read at 0x66225df)
static constexpr uintptr_t kAddrTlsIndex = 0x0128767C8ULL;   // dword TLS slot index (R, 0x66225a3)
static constexpr uintptr_t kAddrFailureFn = 0x004E05030ULL;  // value passed to sub_e935740 when scope begin fails (lea, 0x66225e8)

// Callees: all three are `os` boundary functions in docs/data/native_boundary.tsv,
// called through boundary:: wrappers (no Sigs.json symbols exist for them).
namespace boundary {
void sub_e935740(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_e938cb0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_e938d70(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
} // namespace boundary

static_assert(offsetof(ScopeCounter, count0x10) == 0x10,
              "sub_6622590: object+0x10 is the interlocked 16-bit counter (W, 0x66225be)");
static_assert(offsetof(ScopeCounter, flag0x12) == 0x12,
              "sub_6622590: object+0x12 is the flag byte whose bit 0 is returned (R, 0x66225c3)");

// Exact x64 Microsoft ABI mirror of the original function.
// RCX = a0: address of a pointer to the ScopeCounter object ([a0] is the object).
// Return: AL = (*a0)->flag0x12 & 1 (0 or 1). Returns 0 when *a0 == nullptr.
bool sub_6622590(void** a0);

} // namespace native
