#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Lift callee (class lift, auto-unresolved->lift in docs/data/native_boundary.tsv).
// sub_eec6eb0: memcmp-style compare. rcx=s1, rdx=s2, r8=n, returns int (0 == equal).
extern "C" int sub_eec6eb0(const void* s1, const void* s2, std::size_t n);

} // namespace native

namespace native::d3d12 {

// LIFT 0xe87b920 size 0x1e0 1.26.62.01 sub_e87b920
//
// String (0x20 bytes), SSO when size < 0x10 (data = address of the string object):
//   +0x00 data (uintptr: heap ptr non-SSO / object address SSO)
//   +0x08 pad (SSO buffer high half / capacity, unused by this function)
//   +0x10 length (uint64)
//   +0x18 size (uint64)
constexpr std::size_t kStrDataOff   = 0x00;
constexpr std::size_t kStrLengthOff = 0x10;
constexpr std::size_t kStrSizeOff   = 0x18;

// Hash map (this = rcx):
//   +0x08 sentinel (Node*)
//   +0x18 bucket array (uintptr_t*, stride 0x10 per slot: {chainEnd@0, head@8})
//   +0x30 mask (uint64)
constexpr std::size_t kMapSentinelOff   = 0x08;
constexpr std::size_t kMapBucketArrayOff = 0x18;
constexpr std::size_t kMapMaskOff       = 0x30;
constexpr std::size_t kBucketStride     = 0x10;
constexpr std::size_t kBucketChainEndOff = 0x00;
constexpr std::size_t kBucketHeadOff    = 0x08;

// Node:
//   +0x00 reserved (unused)
//   +0x08 next (Node*)
//   +0x10 key Str (data@0x10, pad@0x18, length@0x20, size@0x28)
//   +0x30 vecData (Str*)
//   +0x38 vecEnd (Str*)
constexpr std::size_t kNodeNextOff        = 0x08;
constexpr std::size_t kNodeKeyDataOff     = 0x10;
constexpr std::size_t kNodeKeyLengthOff   = 0x20;
constexpr std::size_t kNodeKeySizeOff     = 0x28;
constexpr std::size_t kNodeVecDataOff     = 0x30;
constexpr std::size_t kNodeVecEndOff      = 0x38;

static_assert(kStrLengthOff - kStrDataOff == 0x10, "str length offset");
static_assert(kStrSizeOff - kStrLengthOff == 0x08, "str size offset");
static_assert(kMapMaskOff - kMapBucketArrayOff == 0x18, "map mask offset");
static_assert(kBucketStride == 0x10, "bucket stride");
static_assert(kNodeKeyLengthOff - kNodeKeyDataOff == 0x10, "node key length offset");
static_assert(kNodeKeySizeOff - kNodeKeyLengthOff == 0x08, "node key size offset");
static_assert(kNodeVecDataOff - kNodeKeySizeOff == 0x08, "node vecData offset");
static_assert(kNodeVecEndOff - kNodeVecDataOff == 0x08, "node vecEnd offset");

struct Str {
    uintptr_t data;    // +0x00
    uintptr_t pad08;   // +0x08
    uint64_t  length;  // +0x10
    uint64_t  size;    // +0x18
};

struct Node {
    void*   reserved00;   // +0x00
    Node*   next;         // +0x08
    uintptr_t keyData;    // +0x10
    uintptr_t keyPad18;   // +0x18
    uint64_t  keyLength;  // +0x20
    uint64_t  keySize;    // +0x28
    Str*    vecData;      // +0x30
    Str*    vecEnd;       // +0x38
};

struct Map {
    void*       reserved00;    // +0x00
    Node*       sentinel;      // +0x08
    void*       reserved10;    // +0x10
    uintptr_t*  bucketArray;   // +0x18
    uint64_t    reserved20;    // +0x20
    uint64_t    reserved28;    // +0x28
    uint64_t    mask;          // +0x30
};

static_assert(offsetof(Str, data)   == 0x00, "str data");
static_assert(offsetof(Str, length) == 0x10, "str length");
static_assert(offsetof(Str, size)   == 0x18, "str size");
static_assert(sizeof(Str) == 0x20, "str sizeof");
static_assert(offsetof(Map, sentinel)    == 0x08, "map sentinel");
static_assert(offsetof(Map, bucketArray) == 0x18, "map bucketArray");
static_assert(offsetof(Map, mask)        == 0x30, "map mask");
static_assert(offsetof(Node, next)       == 0x08, "node next");
static_assert(offsetof(Node, keyData)    == 0x10, "node keyData");
static_assert(offsetof(Node, keyLength)  == 0x20, "node keyLength");
static_assert(offsetof(Node, keySize)    == 0x28, "node keySize");
static_assert(offsetof(Node, vecData)    == 0x30, "node vecData");
static_assert(offsetof(Node, vecEnd)     == 0x38, "node vecEnd");
static_assert(sizeof(Node) == 0x40, "node sizeof");

// Signature (x64 MS ABI): bool sub_e87b920(Map* map, const Str* key, const Str* query)
bool sub_e87b920(Map* map, const Str* key, const Str* query);

} // namespace native::d3d12
