#pragma once
// RenderDragon frame-graph generator data of 1.26.62.01, decoded statically from BgfxContext::endFrame 0xC270460, the generator 0xC273420, the dispatcher 0xE9002E0 and the
// IntraFrameAllocator helpers 0xA78940 / 0xA79700 (docs/progress/bgfx-d3d12-dragon.md C4a, C4b, C7b). Nothing here is compiled against the game; every offset is an
// instruction-level reading. [V] = read from the disassembly, [I] = inferred from use.

namespace dragon {

// ---- DragonFrameResources (C4a) -------------------------------------------------------------------------------------------------------------------------------------------
// The object endFrame receives by reference lives inside the frame owner at +0x268 (0x67CA3BB: edx = 0x268, add rdx, [rsi+0x10]). The dispatcher 0xE9002E0 receives it as
// args+0x20 and touches ONLY the vector below. Correction to BGFX_MAP 6cx: +0x298 is the vector's LAST (the push cursor), +0x2A0 its END (capacity), the FIRST is +0x290.
struct DragonFrameResourcesOffsets {
    static constexpr size_t kTasksFirst = 0x290; // [V] 0xE900827 (sub rsi,[rdi+0x290]) and 0xE900913
    static constexpr size_t kTasksLast = 0x298;  // [V] 0xE9004AA..0xE9004C5 (cmp r15,[rdi+0x2A0]; store; add [rdi+0x298],0x10)
    static constexpr size_t kTasksEnd = 0x2A0;   // [V]
    static constexpr size_t kTaskElementSize = 0x10; // [V] {Task*, shared_ptr control block*}
    static constexpr size_t kInOwner = 0x268;    // [V] offset of the whole object inside the frame owner
};

// ---- IntraFrameAllocator (C4b) --------------------------------------------------------------------------------------------------------------------------------------------
// IntraFrameAllocator { Arena** or Arena* at +0x00 } : [[IFA]] is the Arena handed to allocate() (0xC277FC2: rax=[rbp+0x3288]=IFA, rcx=[rax]).
// allocate(arena, out*, size, align) = 0xA78940. It tries the page list under the arena lock (mode word +0x90 == 0 or 1, lock +0x88), bump-allocates from a page with
// 0xA79700 and returns an engaged std::optional<ArenaBlock> in *out (flag at +0x30, so the optional is 0x38 bytes).
struct ArenaBlock {                // [V] built at 0xA79832..0xA79846
    void* pageMemory;              // +0x00 [page+0x00] the page's memory base (shared with the page)
    void* pageControl;             // +0x08 [page+0x08] shared_ptr control block of the page (strong count at +8, weak at +0xC); null when not refcounted
    uint64_t address;              // +0x10 the aligned bump address (r10)
    uint64_t size;                 // +0x18 requested size (r8)
    uint64_t padding;              // +0x20 aligned address minus the old cursor
    uint64_t pageId;               // +0x28 [page+0x88] (also stored to page+0x90 with page+0x98 = 1)
};
struct ArenaAllocResult {          // std::optional<ArenaBlock>
    ArenaBlock block;              // +0x00
    bool engaged;                  // +0x30
};
static_assert(sizeof(ArenaBlock) == 0x30);
static_assert(offsetof(ArenaAllocResult, engaged) == 0x30);

// Page = what 0xA79700 bumps. Two independent regions, each {size, start, cursor}; a request of `size` bytes with alignment `a` succeeds in region 1 first, then region 2.
struct ArenaPageOffsets {
    static constexpr size_t kMemory = 0x00;        // [V]
    static constexpr size_t kControl = 0x08;       // [V]
    static constexpr size_t kBytesInUse = 0x40;    // [V] lock add by (padding + size)
    static constexpr size_t kRegion1Size = 0x48;   // [V]
    static constexpr size_t kRegion1Start = 0x50;  // [V] limit = start + size
    static constexpr size_t kRegion1Cursor = 0x58; // [V] lock cmpxchg
    static constexpr size_t kRegion2Size = 0x60;   // [V]
    static constexpr size_t kRegion2Start = 0x68;  // [V]
    static constexpr size_t kRegion2Cursor = 0x70; // [V]
    static constexpr size_t kBytesInUse2 = 0x78;   // [V] lock add (same amount as +0x40)
    static constexpr size_t kAllocCount = 0x80;    // [V] lock inc word
    static constexpr size_t kPageId = 0x88;        // [V]
    static constexpr size_t kLastId = 0x90;        // [V] written with kPageId, flag +0x98 = 1
    static constexpr size_t kLastIdValid = 0x98;   // [V]
};
// Arena (the object whose vector of pages 0xA79120 walks) [V reads, I roles]: +0x08 refcount (lock inc), +0x18 total bytes handed out (lock add), +0x28/+0x30 and
// +0x40/+0x48 two vectors of pages (first/last) walked by 0xA79120, +0x88 lock word, +0x90 mode u32.
struct ArenaOffsets {
    static constexpr size_t kRefCount = 0x08;
    static constexpr size_t kBytesOut = 0x18;
    static constexpr size_t kVecAFirst = 0x28; // [I] 8-byte elements
    static constexpr size_t kVecALast = 0x30;
    static constexpr size_t kVecBFirst = 0x40; // [I] 16-byte elements {Page*, control}
    static constexpr size_t kVecBLast = 0x48;
    static constexpr size_t kLock = 0x88;
    static constexpr size_t kMode = 0x90;
};

// ---- Frame-graph generator records (C7b) ----------------------------------------------------------------------------------------------------------------------------------
// Declared pass descriptor (the object [declaredEntry+8] points at; read in the per-pass loop 0xC277F10..0xC2793FE). Declared entries are 0x10 bytes {u64 key, PassDesc*}.
struct PassDescOffsets {
    static constexpr size_t kEnabled = 0x00;        // [V] byte, read 0xC2780CA..: value used when kHasEnabled
    static constexpr size_t kHasEnabled = 0x01;     // [V] byte (optional<bool> engaged flag)
    static constexpr size_t kU16 = 0x02;            // [V] u16, copied to the generated entry (+0x20) when kU16Engaged
    static constexpr size_t kU16Engaged = 0x04;     // [V] byte
    static constexpr size_t kSlots = 0x28;          // [V] 16 slots x 0x20 = 0x200 bytes, slot type byte at +0x18 (0..4, jump table at 0xC2782A9)
    static constexpr size_t kSlotStride = 0x20;
    static constexpr size_t kSlotCount = 16;
    static constexpr size_t kSlotMode = 0x228;      // [V] byte: 0 = use the 16 slots (loop at 0xC278260), 1 = vector form (copy of +0x28..+0x30), else unreachable (0x1A2800)
    static constexpr size_t kSlotModeEngaged = 0x230; // [V] byte
    static constexpr size_t kResources = 0x238;     // [V] vector of 0x28-byte records, key u64 at +0x20 (looked up in the resolved-resource map [rbp+0x3468])
    static constexpr size_t kBindings = 0x250;      // [V] vector of 0x38-byte binding records, kind byte at +0x30 (1, 2, 3)
    static constexpr size_t kUses = 0x268;          // [V] vector of 0x20-byte records, kind byte at +0x18 (1 or 2)
    static constexpr size_t kAccesses = 0x280;      // [V] vector of 0x30-byte records, kind byte at +0x28 (4 expected; others take the error exit 0xC2791D2)
};

// The three per-pass output vectors built on the generator's stack (rbp+0x3330, +0x3348, +0x3360) and moved into the generated entry:
struct GeneratedEntryOffsets {                      // generated Entry, stride 0x80 [V 0xC279236..0xC2793E4]
    static constexpr size_t kTask = 0x00;           // [V] shared_ptr<Task>.ptr   (from the pass tree node +0x28)
    static constexpr size_t kTaskControl = 0x08;    // [V] shared_ptr<Task>.ctrl  (node +0x30)
    static constexpr size_t kTaskInfo = 0x10;       // [V] 16 bytes = result of task->vtbl[2](out*) (0xC278E6E..0xC278E9A) [I: {ptr, kind} per Tasks.h]
    static constexpr size_t kPassFlags = 0x20;      // [V] 0x0C bytes: u16 value (+0x20), engaged byte (+0x22), u64 packed mask|dword (+0x24)
    static constexpr size_t kBindingVec = 0x30;     // [V] vector of 0x28-byte records {u64 key, shared_ptr resource (ptr, ctrl), u64 a, u32 b, u8 flag0, u8 flag1}
    static constexpr size_t kUseVec = 0x48;         // [V] vector of 0x20-byte records {u64 key, shared_ptr resource (ptr, ctrl), u8 flag (=1)}  (6cz said 24 bytes: wrong, imul/sar in 0xC27FCC0 is /32)
    static constexpr size_t kAccessVec = 0x60;      // [V] vector of 0x20-byte records {u64 key, shared_ptr resource (ptr, ctrl), u32 value}
    static constexpr size_t kSortKey = 0x78;        // [V] u64, 0 at creation, set by the names-vector ordering stage (6eo)
};
static constexpr size_t kGeneratedEntrySize = 0x80;
static constexpr size_t kBindingRecordSize = 0x28;
static constexpr size_t kUseRecordSize = 0x20;
static constexpr size_t kAccessRecordSize = 0x20;

struct BindingRecord { // [V] built at 0xC27840x..0xC278650
    uint64_t key;      // +0x00 declared key
    void* resource;    // +0x08
    void* control;     // +0x10 shared_ptr control block (strong count at +8)
    uint64_t a;        // +0x18 (source +0x08; copied as qword 0x1FD8 and re-copied at +0x1E)
    uint32_t b;        // +0x20 (source +0x10)
    uint8_t flag0;     // +0x24 (byte from source +0x28, or +0x20 for the kind-3 form; 0 for the kind-1 form's second byte)
    uint8_t flag1;     // +0x25 (source +0x21 for kind 3, else 0)
    uint8_t pad[2];    // +0x26
};
struct UseRecord {
    uint64_t key;      // +0x00
    void* resource;    // +0x08
    void* control;     // +0x10
    uint8_t flag;      // +0x18 always 1 here
    uint8_t pad[7];
};
struct AccessRecord {
    uint64_t key;      // +0x00 ([r15] of the 0x30 source record)
    void* resource;    // +0x08 (resolved through the 0x28-byte resource record, tree-node kind 2)
    void* control;     // +0x10
    uint32_t value;    // +0x18 ([r15+8] of the source record)
    uint32_t pad;
};
static_assert(sizeof(BindingRecord) == kBindingRecordSize);
static_assert(sizeof(UseRecord) == kUseRecordSize);
static_assert(sizeof(AccessRecord) == kAccessRecordSize);

} // namespace dragon
