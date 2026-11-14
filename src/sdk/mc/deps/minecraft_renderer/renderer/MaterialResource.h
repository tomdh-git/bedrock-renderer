#pragma once

// Layout of what ResourceCache::get (0x675e440) returns for a material name, 1.26.62.01 (static [V], live-uncaptured).
// Chain: name + defines -> ResourceCache::get -> shared_ptr<Holder> -> Resource -> MaterialSlot -> MaterialInstance*.
// Sources: docs/functions/675e440.md, bcbf730.md (Resource, 0x30 make_shared block), e86b730.md (slot fill), group-visitor use at 0x66e76db..0x66e7746
// (`mov r14,[rax]` = Resource*, `cmp byte [r14+0x10],1` = ready, `mov rcx,[rax]; mov rax,[rcx+0x18]; mov r15,[rax]` = MaterialInstance*).
namespace mce::material {

struct MaterialInstanceOpaque; // 0x470 bytes, ctor 0xbcd1be0 (docs/functions/bcd1be0.md)

// the 0x18-byte block Resource+0x18 points to; filled by the material load 0xe86b730
struct MaterialSlot {
    MaterialInstanceOpaque* mInstance; // +0x00 (0xe86b730 deletes the old one with 0xe86c820 and stores the new)
    std::shared_ptr<void> mMaterial;   // +0x08/+0x10 shared_ptr<Material> from the material repository 0xc2919d0 (Material = 0x190 bytes)
};
static_assert(sizeof(MaterialSlot) == 0x18);
static_assert(offsetof(MaterialSlot, mInstance) == 0x00 && offsetof(MaterialSlot, mMaterial) == 0x08);

// 0x20 bytes inside a 0x30 make_shared block (control vtable rva 0xF44BEB0), created by loadAsync 0xbcbf730 before the job runs
struct Resource {
    uint64_t mReserved0;       // +0x00
    uint64_t mReserved8;       // +0x08
    uint8_t mRequested;        // +0x10 set to 1 by loadAsync on return; the cache's and the visitors' "ready" test
    uint8_t mPad11[7];
    MaterialSlot* mSlot;       // +0x18 heap block, zeroed at creation; null until the job ran
};
static_assert(sizeof(Resource) == 0x20);
static_assert(offsetof(Resource, mRequested) == 0x10 && offsetof(Resource, mSlot) == 0x18);

// ResourceCache::get returns shared_ptr<Holder>; Holder is a 0x10 payload of a 0x20 make_shared block (ctrl vtable rva 0xF09AA70) and is itself a shared_ptr<Resource>
struct Holder {
    std::shared_ptr<Resource> mResource; // +0x00/+0x08
};
static_assert(sizeof(Holder) == 0x10);

// LoadRequest (0x78 bytes) as built by 0x567d050: name, defines map; the {request, bool reloaded} pair puts the bool at +0x78.
inline constexpr size_t kLoadRequestSize = 0x78;
inline constexpr size_t kLoadRequestNameOffset = 0x00;    // std::string
inline constexpr size_t kLoadRequestDefinesOffset = 0x20; // unordered_map<string,string> (list +0x20/+0x28, size +0x30)
inline constexpr size_t kLoadRequestReloadedOffset = 0x78;
static_assert(sizeof(std::string_view) == 16);

// ResourceCache (this of 0x675e440)
struct ResourceCacheLayout {
    static constexpr size_t kEntries = 0x00;      // unordered_map<Key16, Entry>
    static constexpr size_t kStaleKeys = 0x40;    // unordered_set<Key16>
    static constexpr size_t kRetired = 0x80;      // vector<shared_ptr<Holder>>
    static constexpr size_t kMutex = 0x98;        // recursive_mutex
    static constexpr size_t kMutexOwnerCount = 0xE4;
};
static_assert(ResourceCacheLayout::kMutexOwnerCount == ResourceCacheLayout::kMutex + 0x4C);

} // namespace mce::material
