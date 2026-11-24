#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub 0xbca7c80 — VV frame-graph builder (bgfx), size 0x391, 1.26.62.01.
// Range: [0xbca7c80, 0xbca8011) [V] (docs/data/native_functions.tsv line 2).
//
// x64 Microsoft ABI:
//   rcx = a0 (Str* — small-string object, reset by this function)
//   rdx = a1 (Str* — small-string object, reset by this function)
//   Returns via tail call to 0xE935700 (free) on the dealloc path, or ret with rax=0
//   (0xBCA7DCC xor eax,eax) on the small-string path [V].
//
// Callee table [V]:
//   0xEEC6EC0 = memcpy(dst, src, count) — class lift in docs/data/native_boundary.tsv
//     line 512 (auto-unresolved->lift); declared here as sub_eec6ec0 and called directly.
//   0xE935700 = free(ptr, size) — class lift in native_boundary.tsv line 505
//     (auto-unresolved->lift); declared here as sub_e935700 and called directly (incl. tail call).
//   0x9BC830  = alloc-failure handler — class alloc boundary (native_boundary.tsv line 149);
//     entered through native::Boundary<void, std::uintptr_t> sub_9bc830.
//   0x75720   = stl error/terminate path — class stl boundary (native_boundary.tsv line 3);
//     entered through native::Boundary<void> sub_75720.
//   [0xF99FFA0] = vendor allocator thunk (slot) — sub_eea6040 via loader-resolved slot
//     (native_boundary.tsv line 506); read from the slot at call time (hard rule 69).
//   [0xF9A8C78] = terminate slot — read from the slot at call time (hard rule 69), then int3.
//
// Data slots / globals (addresses are RVAs resolved through imageBase()) [V]:
//   0x1233E1A8  allocator vtable pointer (rcx = *it before each slot alloc)
//   0x12AE2210..0x12AE2270  published state block (0x68 bytes: tag, dword 1, movups q0/q1,
//     movups size/cap, 0x800000008, dword 1, final q0/q1, a0.size, final size) [V].
//
// Operand layout (small-string object, size 0x20) [V]:
//   +0x00  char buf[0x10]   (inline buffer; holds a heap pointer in buf[0..7] when cap >= 0x10)
//   +0x10  std::uint64_t size
//   +0x18  std::uint64_t cap
struct Str {
    char buf[0x10];          // +0x00
    std::uint64_t size;      // +0x10
    std::uint64_t cap;       // +0x18
};
static_assert(offsetof(Str, buf) == 0x00, "sub_bca7c80: Str::buf at +0x00");
static_assert(offsetof(Str, size) == 0x10, "sub_bca7c80: Str::size at +0x10");
static_assert(offsetof(Str, cap) == 0x18, "sub_bca7c80: Str::cap at +0x18");
static_assert(sizeof(Str) == 0x20, "sub_bca7c80: Str is 0x20 bytes");

// Published state block layout (at imageBase() + 0x12AE2210) [V].
struct PublishBlock {
    std::uint64_t tag;       // +0x00  0x12AE2210
    std::uint32_t one1;      // +0x08  0x12AE2218
    std::uint64_t dataQ0;    // +0x10  0x12AE2220
    std::uint64_t dataQ1;    // +0x18  0x12AE2228
    std::uint64_t size;      // +0x20  0x12AE2230
    std::uint64_t cap;       // +0x28  0x12AE2238
    // +0x30..+0x37 not written by this function
    std::uint64_t flags;     // +0x38  0x12AE2248
    std::uint32_t one2;      // +0x40  0x12AE2250
    std::uint64_t finalQ0;   // +0x48  0x12AE2258
    std::uint64_t finalQ1;   // +0x50  0x12AE2260
    std::uint64_t a0size;    // +0x58  0x12AE2268
    std::uint64_t finalSize; // +0x60  0x12AE2270
};
static_assert(offsetof(PublishBlock, tag) == 0x00, "sub_bca7c80: PublishBlock::tag at +0x00");
static_assert(offsetof(PublishBlock, one1) == 0x08, "sub_bca7c80: PublishBlock::one1 at +0x08");
static_assert(offsetof(PublishBlock, dataQ0) == 0x10, "sub_bca7c80: PublishBlock::dataQ0 at +0x10");
static_assert(offsetof(PublishBlock, dataQ1) == 0x18, "sub_bca7c80: PublishBlock::dataQ1 at +0x18");
static_assert(offsetof(PublishBlock, size) == 0x20, "sub_bca7c80: PublishBlock::size at +0x20");
static_assert(offsetof(PublishBlock, cap) == 0x28, "sub_bca7c80: PublishBlock::cap at +0x28");
static_assert(offsetof(PublishBlock, flags) == 0x38, "sub_bca7c80: PublishBlock::flags at +0x38");
static_assert(offsetof(PublishBlock, one2) == 0x40, "sub_bca7c80: PublishBlock::one2 at +0x40");
static_assert(offsetof(PublishBlock, finalQ0) == 0x48, "sub_bca7c80: PublishBlock::finalQ0 at +0x48");
static_assert(offsetof(PublishBlock, finalQ1) == 0x50, "sub_bca7c80: PublishBlock::finalQ1 at +0x50");
static_assert(offsetof(PublishBlock, a0size) == 0x58, "sub_bca7c80: PublishBlock::a0size at +0x58");
static_assert(offsetof(PublishBlock, finalSize) == 0x60, "sub_bca7c80: PublishBlock::finalSize at +0x60");
static_assert(sizeof(PublishBlock) == 0x68, "sub_bca7c80: PublishBlock is 0x68 bytes");

// Lift callees (class lift in native_boundary.tsv): forward-declared with the exact x64 ABI
// signature seen at the call sites and called directly (hard rule 66).
void* sub_eec6ec0(void* dst, const void* src, std::size_t count);   // 0xEEC6EC0 memcpy(dst,src,count)
void  sub_e935700(void* ptr, std::size_t size);                     // 0xE935700 free(ptr,size)

// Boundary callees (native::Boundary, resolved through Sigs.json).
native::Boundary<void, std::uintptr_t> sub_9bc830("sub_9bc830");   // 0x9BC830 alloc-failure handler
native::Boundary<void>                 sub_75720("sub_75720");     // 0x75720 stl error path

// Data-slot RVAs (documented; calls go through the slot read at call time, hard rule 69).
static constexpr std::uintptr_t kRvaHeapIface   = 0x1233E1A8;   // [0x1233E1A8] allocator vtable
static constexpr std::uintptr_t kRvaAllocSlot   = 0xF99FFA0;    // call qword ptr [0xF99FFA0]
static constexpr std::uintptr_t kRvaTermSlot    = 0xF9A8C78;    // call qword ptr [0xF9A8C78]
static constexpr std::uintptr_t kRvaPublishBlock= 0x12AE2210;    // [0x12AE2210]..[0x12AE2270]

// Lifted function.
void sub_bca7c80(Str* a0, Str* a1);

// Footprint: publishes the 0x68-byte state block at imageBase()+0x12AE2210 plus the two
// operand objects (each 0x20 bytes: buf[0], size, cap). The heap buffers allocated inside
// (r14) are dynamic and cannot be named statically; their writes are covered by the lifted
// callees' own footprints (sub_eec6ec0 writes count bytes at r14).
std::size_t sub_bca7c80_footprint(Str* a0, Str* a1);

} // namespace native
