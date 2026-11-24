#pragma once
// LIFT 0xe879c60 size 0x24b 1.26.62.01 sub_e879c60

#include <cstddef>
#include <cstdint>

namespace native {

// ------------------------------------------------------------------
// Layout constants used by sub_e879c60 [V from disassembly 0xe879c60..0xe879eab]
// The function is read-only: it walks a hash set / bucket chain and
// compares keys. It writes nothing and returns a bool in al/eax.
// ------------------------------------------------------------------

// Key object (a1+0x8 -> * = K). Fields read:
//   +0x00: self-pointer, compared against the +0x8 pointer (sentinel test)
//   +0x10: key data pointer (heap)  [used when +0x28 cap >= 0x10]
//   +0x20: key size
//   +0x28: key capacity (0x10 = SSO threshold)
//   +0x30: key data pointer 2 (heap) [used when node +0x48 cap >= 0x10]
//   +0x40: key length 2
//   +0x48: key capacity 2
static constexpr std::uintptr_t kKeyObjSelf       = 0x00u;
static constexpr std::uintptr_t kKeyObjData       = 0x10u;
static constexpr std::uintptr_t kKeyObjSize       = 0x20u;
static constexpr std::uintptr_t kKeyObjCap        = 0x28u;
static constexpr std::uintptr_t kKeyObjData2      = 0x30u;
static constexpr std::uintptr_t kKeyObjLen2       = 0x40u;
static constexpr std::uintptr_t kKeyObjCap2       = 0x48u;

struct KeyObj {
    void*     self;      // +0x00
    uint8_t   pad08[0x10 - 0x08];
    void*     data;      // +0x10
    uint8_t   pad18[0x20 - 0x18];
    uint64_t  size;      // +0x20
    uint64_t  cap;       // +0x28
    void*     data2;     // +0x30
    uint8_t   pad38[0x40 - 0x38];
    uint64_t  len2;      // +0x40
    uint64_t  cap2;      // +0x48
};
static_assert(sizeof(KeyObj) == 0x50, "e879c60: KeyObj size");
static_assert(offsetof(KeyObj, self) == 0x00, "e879c60: KeyObj self offset");
static_assert(offsetof(KeyObj, data) == 0x10, "e879c60: KeyObj data offset");
static_assert(offsetof(KeyObj, size) == 0x20, "e879c60: KeyObj size offset");
static_assert(offsetof(KeyObj, cap) == 0x28, "e879c60: KeyObj cap offset");
static_assert(offsetof(KeyObj, data2) == 0x30, "e879c60: KeyObj data2 offset");
static_assert(offsetof(KeyObj, len2) == 0x40, "e879c60: KeyObj len2 offset");
static_assert(offsetof(KeyObj, cap2) == 0x48, "e879c60: KeyObj cap2 offset");

// Bucket chain node. Fields read:
//   +0x08: next pointer
//   +0x10: data pointer (heap)  [used when +0x28 cap >= 0x10]
//   +0x20: size
//   +0x28: cap (0x10 = SSO threshold)
//   +0x30: data pointer 2 (heap) [used when +0x48 cap >= 0x10]
//   +0x40: length 2
//   +0x48: cap 2
static constexpr std::uintptr_t kNodeNext   = 0x08u;
static constexpr std::uintptr_t kNodeData   = 0x10u;
static constexpr std::uintptr_t kNodeSize   = 0x20u;
static constexpr std::uintptr_t kNodeCap    = 0x28u;
static constexpr std::uintptr_t kNodeData2  = 0x30u;
static constexpr std::uintptr_t kNodeLen2   = 0x40u;
static constexpr std::uintptr_t kNodeCap2   = 0x48u;

struct HashNode {
    uint8_t   pad00[0x08];
    void*     next;      // +0x08
    uint8_t   pad10[0x10 - 0x08];
    void*     data;      // +0x10
    uint8_t   pad18[0x20 - 0x18];
    uint64_t  size;      // +0x20
    uint64_t  cap;       // +0x28
    void*     data2;     // +0x30
    uint8_t   pad38[0x40 - 0x38];
    uint64_t  len2;      // +0x40
    uint64_t  cap2;      // +0x48
};
static_assert(sizeof(HashNode) == 0x50, "e879c60: HashNode size");
static_assert(offsetof(HashNode, next) == 0x08, "e879c60: HashNode next offset");
static_assert(offsetof(HashNode, data) == 0x10, "e879c60: HashNode data offset");
static_assert(offsetof(HashNode, size) == 0x20, "e879c60: HashNode size offset");
static_assert(offsetof(HashNode, cap) == 0x28, "e879c60: HashNode cap offset");
static_assert(offsetof(HashNode, data2) == 0x30, "e879c60: HashNode data2 offset");
static_assert(offsetof(HashNode, len2) == 0x40, "e879c60: HashNode len2 offset");
static_assert(offsetof(HashNode, cap2) == 0x48, "e879c60: HashNode cap2 offset");

// Container (a0 = rcx). Fields read:
//   +0x10: sentinel/end node
//   +0x20: bucket array base
//   +0x38: count
static constexpr std::uintptr_t kContainerSentinel = 0x10u;
static constexpr std::uintptr_t kContainerBucket   = 0x20u;
static constexpr std::uintptr_t kContainerCount    = 0x38u;

struct Container {
    uint8_t   pad00[0x10];
    void*     sentinel;   // +0x10
    uint8_t   pad18[0x20 - 0x18];
    void*     bucketBase; // +0x20
    uint8_t   pad28[0x38 - 0x28];
    uint64_t  count;      // +0x38
};

// Bucket slot: two pointers at [bucketBase + idx] and [bucketBase + idx + 8]
// where idx = (hash & count) << 4.  (idx is a byte offset = bucket*16.)

// FNV-1a constants [V from disassembly]
static constexpr uint64_t kFnvPrime  = 0x100000001B3ULL;
static constexpr uint64_t kFnvBasis  = 0xCBF29CE484222325ULL;
static constexpr uint64_t kBucketMask = 0xBF29CE4842223250ULL;

// ------------------------------------------------------------------
// Callee forward declaration (lift set signature).
// sub_eec6eb0 is referenced by sub_e879c60 (2 calls) but is not yet in
// native_boundary.tsv / native_functions.tsv, so it is forward-declared
// here and called directly; it will be lifted by its own unit.
//   rcx = dataA, rdx = dataB, r8 = count
//   returns: comparison in eax (0 == equal)
// ------------------------------------------------------------------
extern "C" int sub_eec6eb0(const void* dataA, const void* dataB, std::size_t count);

// ------------------------------------------------------------------
// Function signature: x64 Microsoft ABI
//   rcx = a0 (container)
//   rdx = a1 (pointer to pointer; *a1+0x8 is the key object)
//   returns: al/eax = bool (1 == match / sentinel, 0 == no match)
// ------------------------------------------------------------------
extern "C" bool sub_e879c60(void* a0_container, void* a1_keyPtr);

} // namespace native
