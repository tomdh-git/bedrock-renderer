#pragma once
// GraphicsTasks scheduler object of 1.26.62.01 (constructor 0xC25B1A0, docs/progress/bgfx-d3d12-dragon.md C3a). [V] = read from the disassembly, [I] = inferred.
// The five task queues are moodycamel::ConcurrentQueue<Task64> (constructor 0x1D2C10 initialises one with capacity 0x400); the layout below is the instruction-level
// reading of that constructor and matches the stock library's member order and sizes.

namespace dragon {

static constexpr uintptr_t kQueueCtorRva = 0x1D2C10;       // [V] (queue*, capacity) -> queue*
static constexpr uintptr_t kSchedulerCtorRva = 0xC25B1A0;  // [V]
static constexpr size_t kQueueObjectSize = 0x268;          // [V] make_shared block = 0x278 (control block 0x10 + object)
static constexpr size_t kQueueInitialCapacity = 0x400;     // [V] argument handed by the scheduler constructor, five times
static constexpr size_t kQueueBlockSize = 32;              // [V] elements per block (shr 5 of the capacity)
static constexpr size_t kQueueElementSize = 64;            // [V] (0x848 block stride - 0x48 header) / 32
static constexpr size_t kQueueInitialBlocks = kQueueInitialCapacity / kQueueBlockSize; // [V] 32 blocks of 0x848 allocated up front

struct QueueOffsets {
    static constexpr size_t kProducerListTail = 0x00;           // [V] 0
    static constexpr size_t kProducerCount = 0x08;              // [V] u32
    static constexpr size_t kInitialBlockPoolIndex = 0x10;      // [V]
    static constexpr size_t kInitialBlockPool = 0x18;           // [V] Block* (array), set at the end of the ctor
    static constexpr size_t kInitialBlockPoolSize = 0x20;       // [V] ceil(capacity / 32)
    static constexpr size_t kFreeListHead = 0x28;               // [V]
    static constexpr size_t kImplicitProducerHash = 0x30;       // [V] pointer to kInitialImplicitProducerHash (+0x40)
    static constexpr size_t kImplicitProducerHashCount = 0x38;  // [V]
    static constexpr size_t kInitialHashCapacity = 0x40;        // [V] 0x20
    static constexpr size_t kInitialHashEntries = 0x48;         // [V] pointer to +0x58
    static constexpr size_t kInitialHashPrev = 0x50;            // [V] 0
    static constexpr size_t kInitialHashStorage = 0x58;         // [V] 32 entries x 0x10 {u32 id (zeroed), pointer value}, ends at 0x258
    static constexpr size_t kInitialHashEntryStride = 0x10;
    static constexpr size_t kAfterHash = 0x258;                 // [V] 0x250 16 bytes zero, 0x258/0x260 u32 zero (resize flag / consumer ids) [I]
};
static_assert(QueueOffsets::kInitialHashStorage + 32 * QueueOffsets::kInitialHashEntryStride == QueueOffsets::kAfterHash);

// One block of the initial pool (stride 0x848): 32 task records, then the block header. [V offsets, I names (stock moodycamel::Block)]
struct QueueBlockOffsets {
    static constexpr size_t kElements = 0x000;          // 32 x 64
    static constexpr size_t kNext = 0x800;              // [I] zeroed
    static constexpr size_t kElementsCompletelyDequeued = 0x808; // [I]
    static constexpr size_t kEmptyFlags = 0x810;        // [I] 32 bytes zeroed (explicit-block counter mode off)
    static constexpr size_t kFreeListRefs = 0x830;      // [V] u32 zero
    static constexpr size_t kFreeListNext = 0x838;      // [V] u64 zero
    static constexpr size_t kDynamicallyAllocated = 0x840; // [V] byte: 1 in the block constructor, rewritten to 0 for the initial pool (0x1D30C0..0x1D30E5)
    static constexpr size_t kSize = 0x848;
};
static_assert(QueueBlockOffsets::kElements + kQueueBlockSize * kQueueElementSize == QueueBlockOffsets::kNext);

// Scheduler object, fields as read in the constructor (progress file C3a): five shared_ptr<Queue> {object*, control*} at +0x38/+0x48/+0x58/+0x68/+0x78, scheduler core at +0xA8
// (constructed by 0x7709C0 with "GraphicsTasks Scheduler", priority 0x3C), shared groups at +0x118 ("GraphicsTasks Group") and +0x128 ("GraphicsTasks Parallel Group").
struct SchedulerOffsets {
    static constexpr size_t kOwner = 0x10;
    static constexpr size_t kWorkers = 0x18;     // vector<u64> first/last/end
    static constexpr size_t kQueues = 0x38;      // 5 x {Queue*, control*}
    static constexpr size_t kQueueStride = 0x10;
    static constexpr size_t kCore = 0xA8;
    static constexpr size_t kGroup = 0x118;
    static constexpr size_t kParallelGroup = 0x128;
    static constexpr size_t kPendingCount = 0x148;
};

} // namespace dragon
