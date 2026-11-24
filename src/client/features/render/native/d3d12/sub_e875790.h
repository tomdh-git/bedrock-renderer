#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Lift callees of sub_e875790 (boundary lift set):
//   0xeec5850 = MSVCP140!std::_Xlength_error (throws length_error)
//   0xe935700 = game deallocator (jmp 0x392960, reads allocator global)
extern "C" void sub_eec5850(std::uintptr_t a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);
extern "C" void sub_e935700(std::uintptr_t a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);

} // namespace native

namespace native::d3d12 {

// LIFT 0xe875790 size 0x8e4 1.26.62.01 BgfxFrameBuilder slot 16
// MSVC std::unordered_map<std::string, mapped(0x18)>::try_emplace/operator[].
// rcx = map*, rdx = out {Node* node; bool inserted;}, r8 = key std::string*, r9 = mapped value ptr (0x18 bytes).

// Map layout (this, rcx)
constexpr std::size_t kMapMaxLoadFactor = 0x00;   // float _MaxBprime
constexpr std::size_t kMapMyhead        = 0x08;   // Node* sentinel
constexpr std::size_t kMapMysize        = 0x10;   // size_t element count
constexpr std::size_t kMapVecFirst      = 0x18;   // bucket array base (Node* pairs, idx<<4)
constexpr std::size_t kMapVecLast       = 0x20;
constexpr std::size_t kMapVecEnd        = 0x28;
constexpr std::size_t kMapMask          = 0x30;   // bucket count - 1
constexpr std::size_t kMapBucketCount   = 0x38;   // size_t bucket count

// Node layout (0x48 bytes)
constexpr std::size_t kNodeSize         = 0x48;
constexpr std::size_t kNodePrev         = 0x00;   // Node*
constexpr std::size_t kNodeNext         = 0x08;   // Node*
constexpr std::size_t kNodeKey          = 0x10;   // std::string (0x20 bytes; SSO if cap<0x10)
constexpr std::size_t kNodeKeySizeOff   = 0x20;   // key.size (within string, offset 0x10)
constexpr std::size_t kNodeKeyCapOff    = 0x28;   // key.cap
constexpr std::size_t kNodeValue        = 0x30;   // mapped value (0x18 bytes)

// bucket slot: {Node* _Next @+0, Node* _Prev @+8}, stride 0x10
constexpr std::size_t kBucketStride     = 0x10;

// CRT intrinsics this function calls
//   0xeec6eb0 = VCRUNTIME140!memcmp  (4 call sites)
//   0xeec73f0 = ceilf                (1 call site)
// Boundary / data-slot calls:
//   0x9bc830            operator new / _callnewh fallback (3 sites)
//   0xe935700           dealloc (1 site)
//   0xeec5850           _Xlength_error (2 sites)
//   [0xF99FFA0]         vendor alloc (sub_eea6040) (2 sites)
//   [0xF9A8C78]         _invoke_watson (1 site, invalid bucket count)
static constexpr std::uintptr_t kDataSlot_F99FFA0 = 0xF99FFA0;
static constexpr std::uintptr_t kDataSlot_F9A8C78 = 0xF9A8C78;

static_assert(kNodeKey + 0x20 == kNodeValue, "node key/value boundary");
static_assert(kNodeSize == 0x48, "node size");
static_assert(kBucketStride == 0x10, "bucket stride");

struct Node {
    void* prev;   // +0x00
    void* next;   // +0x08
    // +0x10 std::string key (0x20 bytes)
    char  key_buf[0x20]; // placeholder for layout only
    char  value[0x18];   // +0x30
};

struct Map {
    float    maxLoad;     // +0x00
    Node*    myhead;      // +0x08
    std::size_t size;     // +0x10
    void*    vecFirst;    // +0x18
    void*    vecLast;     // +0x20
    void*    vecEnd;      // +0x28
    std::size_t mask;     // +0x30
    std::size_t bucketCount; // +0x38
};

static_assert(sizeof(Map) >= 0x40, "map size");

// Signature (x64 MS ABI): void sub_e875790(Map* this, Out* out, void* keyStr, void* valuePtr)
struct Out { void* node; unsigned char inserted; };

void sub_e875790(Map* self, Out* out, void* key, void* value);

} // namespace native::d3d12
