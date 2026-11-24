#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe804590 (size 0x2a6, 1.26.62.01).
// The object (rcx/this) is a string->handle open-addressing map:
//   +0x00 (unknown/pad)
//   +0x04 u32 count
//   +0x08 u32 hashes[1024]
//   +0x1008 u16 bitmap[1024]  (0xFFFF = empty bucket)
//   +0x1808 u16 slots[]         (indexed by 16-bit handle di)
// Every offset below is an instruction [reg+off] seen in the listing [V].
//
// Globals read by the function:
//   [0x1230A0C0]  /GS stack cookie (kGblCookie)
//   [0xF847A07]   default NUL-terminated string used when the input string is empty/null (kDefaultString)

// ---- global data slots [V] ----
static constexpr std::uintptr_t kGblCookie     = 0x1230A0C0u; // mov rax,[0x1230A0C0]   /GS cookie
static constexpr std::uintptr_t kDefaultString = 0xF847A07u;  // lea rdx,[0xF847A07]    default string

// ---- object (rcx) fields [V] ----
static constexpr std::size_t kObjCount   = 0x04;   // u32 count                    (R/W 0xe804695/0xe80469c/0xe80476a/0xe8047f1/0xe8046de)
static constexpr std::size_t kObjHashes  = 0x08;   // u32 hash slots[1024]         (R/W 0xe80466f/0xe8046d0/0xe804700/0xe80472b/0xe80478f/0xe8047cb)
static constexpr std::size_t kObjBitmap  = 0x1008; // u16 bitmap[1024], 0xFFFF=empty (R/W 0xe804663/0xe80468a/0xe8046ae/0xe804760/0xe804783/0xe8047c3/0xe8047e8)
static constexpr std::size_t kObjSlots   = 0x1808; // u16 slots[] indexed by handle di (W 0xe8047f7)

// ---- hash table geometry [V] ----
static constexpr std::size_t kBucketCount = 1024;          // bitmap/hashes entries
static constexpr std::uint32_t kBucketMask = 0x3FFu;       // and r9d,0x3FF / and r14d,0x3FF / and r8d,0x3FF
static constexpr std::uint16_t kEmptyBitmap = 0xFFFFu;     // empty bucket sentinel
static constexpr std::uint16_t kNoHandle = 0xFFFFu;        // di == 0xFFFF means "no handle"

// ---- MurmurHash2A mixer constants [V] ----
static constexpr std::uint32_t kMurmurMul   = 0x5BD1E995u; // imul ... 0x5BD1E995
static constexpr std::uint32_t kIdealMul1   = 0x5EBCA77u;  // imul ebp,ebx,0x5EBCA77
static constexpr std::uint32_t kIdealMul2   = 0x1B1u;      // imul ebp,0x1B1

// ---- layout assertion probe struct [V] ----
struct StringHandleMapProbe {
    std::uint8_t  pad00[4];          // +0x00
    std::uint32_t count;             // +0x04
    std::uint32_t hashes[1024];      // +0x08  (0x08 + 0x1000 == 0x1008)
    std::uint16_t bitmap[1024];      // +0x1008 (0x1008 + 0x800 == 0x1808)
    std::uint16_t slots[1];          // +0x1808
};
static_assert(offsetof(StringHandleMapProbe, count) == 0x04, "e804590: count @0x04");
static_assert(offsetof(StringHandleMapProbe, hashes) == 0x08, "e804590: hashes @0x08");
static_assert(offsetof(StringHandleMapProbe, bitmap) == 0x1008, "e804590: bitmap @0x1008");
static_assert(offsetof(StringHandleMapProbe, slots) == 0x1808, "e804590: slots @0x1808");

// ---- callees ----
// sub_bc76610 (0xbc76610, bx::HashMurmur2A::add, lift set): void add(void* self, const void* data, uint32_t len)
extern "C" void sub_bc76610(void* self, const void* data, std::uint32_t len);
// sub_ebce5e0 (0xebce5e0, lift set): uint32_t strnlen-like(const char* s, uint32_t maxlen)
extern "C" std::uint32_t sub_ebce5e0(const char* s, std::uint32_t maxlen);

// 0xe804590 size 0x2a6 1.26.62.01 sub_e804590
// x64 Microsoft ABI: rcx=self(map), edx=handle(di), r8=input string.
// Returns uint16_t* = &self->slots[di] (after setting slots[di]=di).
extern "C" std::uint16_t* sub_e804590(void* self, std::uint32_t edx, const char* str);

} // namespace native
