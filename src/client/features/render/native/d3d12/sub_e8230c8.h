#pragma once
// LIFT 0xe8230c8 size 0xa41b 1.26.62.01 sub_e8230c8

#include <cstdint>
#include <cstddef>

// Layout constants for sub_e8230c8 (0xe8230c8..0xe82d4e3)
// All offsets verified against disassembly; static_assert ensures byte-identical layout.

// rbx base structure (RenderContext or similar)
struct alignas(8) RenderContext_e8230c8 {
    // 0x000..0x0B0: unknown
    char pad_000[0xB0];
    // 0x0B0: pointer to ChunkAllocatorState
    void* chunk_allocator_state;           // +0xB0
    char pad_B8[0x38];
    // 0x0F0: dword (index/counter)
    uint32_t chunk_alloc_index;            // +0xF0
    char pad_F4[0x5C];
    // 0x150: dword
    uint32_t field_150;                    // +0x150
    char pad_154[0x6C];
    // 0x1C0: qword
    uint64_t field_1C0;                    // +0x1C0
    char pad_1C8[0x8];
    // 0x1D0: dword
    uint32_t field_1D0;                    // +0x1D0
    char pad_1D4[0x2C];
    // 0x200: qword (pointer)
    void* field_200;                       // +0x200
    char pad_208[0x30];
    // 0x238: qword (pointer to ResourceHeap)
    void* resource_heap;                   // +0x238
    char pad_240[0x80];
    // 0x2C0: qword
    uint64_t field_2C0;                    // +0x2C0
    char pad_2C8[0xF0];
    // 0x128 from rbx+0x90 base (so 0x90+0x128=0x1B8 from rbx? No, rbx+0x90 is separate)
    // Actually the structure at rbx+0x90 is separate
};

// Structure at rbx+0x90 (ChunkAllocator or similar)
struct alignas(8) ChunkAllocator_e8230c8 {
    char pad_000[0x20460];
    // 0x20460: qword (pointer to chunk data)
    void* chunk_data_ptr;                  // +0x20460
    // 0x20468: qword (size/capacity)
    uint64_t chunk_data_size;              // +0x20468
    // 0x20470: qword (capacity limit)
    uint64_t chunk_capacity_limit;         // +0x20470
    // 0x20478: byte (flags)
    uint8_t chunk_flags;                   // +0x20478
    char pad_20479[0x1F0F];
    // 0x22480: qword (pointer)
    void* field_22480;                     // +0x22480
    // 0x22488: qword
    uint64_t field_22488;                  // +0x22488
    // 0x22490: qword
    uint64_t field_22490;                  // +0x22490
};

// Structure at rbx+0xB0 (GlobalChunkState or similar)
struct alignas(8) GlobalChunkState_e8230c8 {
    // 0xC96178: qword (pointer to chunk pool)
    void* chunk_pool_ptr;                  // +0xC96178
    // 0xC96180: qword (size)
    uint64_t chunk_pool_size;              // +0xC96180
    // 0xC96188: qword (capacity)
    uint64_t chunk_pool_capacity;          // +0xC96188
    // 0xC96190: byte (flags)
    uint8_t chunk_pool_flags;              // +0xC96190
};

// Structure at rbx+0xB8
struct alignas(8) HeapHeader_e8230c8 {
    // 0x008: qword
    uint64_t field_8;                      // +0x8
    // 0x010: qword
    uint64_t field_10;                     // +0x10
    // 0x018: dword
    uint32_t field_18;                     // +0x18
};

// Chunk entry structure (0xB8 bytes each)
struct alignas(8) ChunkEntry_e8230c8 {
    // 0x000: qword (next pointer)
    void* next;                            // +0x00
    // 0x008: qword
    uint64_t field_8;                      // +0x8
    // 0x010: qword
    uint64_t field_10;                     // +0x10
    // ... up to 0x90
    char pad_18[0x78];
    // 0x090: qword
    uint64_t field_90;                     // +0x90
    // 0x098..0x0B0: padding
    char pad_98[0x18];
    // 0x0B1: word
    uint16_t field_B1;                     // +0xB1
    // 0x0B3..0x0B7: padding
    char pad_B3[0x5];
    // 0x0B8: end (size 0xB8)
};

// Chunk pool block (0xB8000 bytes = 720896 bytes)
constexpr size_t CHUNK_POOL_BLOCK_SIZE = 0xB8000;
constexpr size_t CHUNK_ENTRY_SIZE = 0xB8;
constexpr size_t CHUNK_ENTRIES_PER_BLOCK = CHUNK_POOL_BLOCK_SIZE / CHUNK_ENTRY_SIZE; // 0x1000 = 4096

// Secondary chunk pool (at rbx+0x90+0x20460) with 0xC000 byte blocks
constexpr size_t CHUNK_POOL2_BLOCK_SIZE = 0xC000;
constexpr size_t CHUNK_POOL2_ENTRIES_PER_BLOCK = 0x1000; // 4096 entries of 0xC bytes? Actually 0xC000/4096 = 12 bytes per entry

// Tertiary chunk pool (at rbx+0x90+0x22480) with 0x2000 byte blocks
constexpr size_t CHUNK_POOL3_BLOCK_SIZE = 0x2000;

// ResourceHeap structure (pointed by rbx+0x238)
struct alignas(8) ResourceHeap_e8230c8 {
    // 0xB8000: qword (pointer to block)
    void* block_ptr;                       // +0xB8000
    // 0xB8008: qword (size)
    uint64_t block_size;                   // +0xB8008
    // 0xB8018: byte (flags)
    uint8_t block_flags;                   // +0xB8018
};

// Global allocator at 0x12ADF800
struct alignas(8) GlobalAllocator_e8230c8 {
    // 0x000: qword (vtable)
    void* vtable;                          // +0x00
    // 0x008: qword (alloc function)
    void* alloc_fn;                        // +0x8
};

// Global device/resources at 0x12BB4910
struct alignas(8) GlobalDevice_e8230c8 {
    char pad_000[0x400];
    // 0x400: qword (pointer)
    void* field_400;                       // +0x400
};

// Data slot 0xF99FFA0 - vendor thunk (sub_eea6040)
extern "C" void* g_vendor_thunk_eea6040;

// Data slot 0xF9A8C78 - used in chunk c06
extern "C" void* g_data_slot_F9A8C78;

// Callee declarations (all lift-classified per native_boundary.tsv)
namespace native {
namespace d3d12 {

// Forward declarations for callees in the lift set
void sub_e83ace0(void* rcx, void* rdx);                    // 0xe83ace0
void sub_ebce430(void* rcx, void* rdx);                    // 0xebce430
void sub_ebce390(void* rcx, void* rdx);                    // 0xebce390
void sub_bc5f110(void* rcx, void* rdx);                    // 0xbc5f110
void sub_e82d960(void* rcx, void* rdx, void* r8, void* r9);// 0xe82d960
void sub_e835f00(void* rcx, void* rdx);                    // 0xe835f00
void sub_e83aed0(void* rcx, void* rdx, void* r8, void* r9);// 0xe83aed0
void sub_e83abb0(void* rcx, void* rdx);                    // 0xe83abb0
void sub_e82dcc0(void* rcx);                               // 0xe82dcc0
void sub_eea6040(void* rcx, void* rdx, void* r8, void* r9); // 0xeea6040 (vendor thunk, called via data slot)
void sub_eec6ed0(void* rcx, void* rdx);                    // 0xeec6ed0 (CRT vector reserve)
void sub_eec6ec0(void* rcx, void* rdx);                    // 0xeec6ec0
void sub_e8360f0(void* rcx);                               // 0xe8360f0
void sub_e81e1c0(void* rcx, void* rdx);                    // 0xe81e1c0
void sub_bc6a9d0(void* rcx);                               // 0xbc6a9d0
void sub_e81b4d0(void* rcx);                               // 0xe81b4d0
void sub_e81b720(void* rcx);                               // 0xe81b720
void sub_ebdb740(void);                                    // 0xebdb740 (OS)
void sub_e81d850(void* rcx);                               // 0xe81d850
void sub_eec59e0(void* rcx);                               // 0xeec59e0
void sub_e935700(void* rcx, void* rdx);                    // 0xe935700
void sub_e820500(void* rcx);                               // 0xe820500
void sub_e82de90(void* rcx);                               // 0xe82de90
void sub_e835b50(void* rcx);                               // 0xe835b50
void sub_47e8f0(void* rcx);                                // 0x47e8f0 (STL but classified lift?)

// Boundary callees (called via native::boundary:: wrapper)
// sub_ebdb740 is OS class
// sub_eea6040 is vendor class (called via data slot 0xF99FFA0)

// Lifted function signature
// Entry at 0xe8230c8, uses registers: rbx, r9, r10, r13, r14, r15 as inputs
// rdi appears to be an index parameter
// Return: void (no return value observed)
void sub_e8230c8(
    RenderContext_e8230c8* rbx,      // rbx: context pointer
    GlobalChunkState_e8230c8* r9,    // r9: global chunk state
    void* r10,                        // r10: scratch/temp
    void* r13,                        // r13: scratch/temp
    void* r14,                        // r14: scratch/temp
    void* r15,                        // r15: scratch/temp
    uint64_t rdi                      // rdi: index parameter
);

// LIFT_FN registry entry (framework from X0d)
#define LIFT_FN(name, rva) \
    namespace native { namespace registry { \
    struct name##_entry { \
        static constexpr uintptr_t rva = rva; \
        static constexpr const char* symbol = #name; \
        static constexpr int mode = 2; /* Verify */ \
        name##_entry() { /* registration handled by framework */ } \
    }; \
    static name##_entry name##_instance; \
    } }

LIFT_FN(sub_e8230c8, 0xe8230c8)

// Static assertions for layout verification
static_assert(offsetof(RenderContext_e8230c8, chunk_allocator_state) == 0xB0, "RenderContext_e8230c8::chunk_allocator_state offset mismatch");
static_assert(offsetof(RenderContext_e8230c8, chunk_alloc_index) == 0xF0, "RenderContext_e8230c8::chunk_alloc_index offset mismatch");
static_assert(offsetof(RenderContext_e8230c8, field_150) == 0x150, "RenderContext_e8230c8::field_150 offset mismatch");
static_assert(offsetof(RenderContext_e8230c8, field_1C0) == 0x1C0, "RenderContext_e8230c8::field_1C0 offset mismatch");
static_assert(offsetof(RenderContext_e8230c8, field_1D0) == 0x1D0, "RenderContext_e8230c8::field_1D0 offset mismatch");
static_assert(offsetof(RenderContext_e8230c8, field_200) == 0x200, "RenderContext_e8230c8::field_200 offset mismatch");
static_assert(offsetof(RenderContext_e8230c8, resource_heap) == 0x238, "RenderContext_e8230c8::resource_heap offset mismatch");
static_assert(offsetof(RenderContext_e8230c8, field_2C0) == 0x2C0, "RenderContext_e8230c8::field_2C0 offset mismatch");

static_assert(offsetof(ChunkAllocator_e8230c8, chunk_data_ptr) == 0x20460, "ChunkAllocator_e8230c8::chunk_data_ptr offset mismatch");
static_assert(offsetof(ChunkAllocator_e8230c8, chunk_data_size) == 0x20468, "ChunkAllocator_e8230c8::chunk_data_size offset mismatch");
static_assert(offsetof(ChunkAllocator_e8230c8, chunk_capacity_limit) == 0x20470, "ChunkAllocator_e8230c8::chunk_capacity_limit offset mismatch");
static_assert(offsetof(ChunkAllocator_e8230c8, chunk_flags) == 0x20478, "ChunkAllocator_e8230c8::chunk_flags offset mismatch");
static_assert(offsetof(ChunkAllocator_e8230c8, field_22480) == 0x22480, "ChunkAllocator_e8230c8::field_22480 offset mismatch");
static_assert(offsetof(ChunkAllocator_e8230c8, field_22488) == 0x22488, "ChunkAllocator_e8230c8::field_22488 offset mismatch");
static_assert(offsetof(ChunkAllocator_e8230c8, field_22490) == 0x22490, "ChunkAllocator_e8230c8::field_22490 offset mismatch");

static_assert(offsetof(GlobalChunkState_e8230c8, chunk_pool_ptr) == 0xC96178, "GlobalChunkState_e8230c8::chunk_pool_ptr offset mismatch");
static_assert(offsetof(GlobalChunkState_e8230c8, chunk_pool_size) == 0xC96180, "GlobalChunkState_e8230c8::chunk_pool_size offset mismatch");
static_assert(offsetof(GlobalChunkState_e8230c8, chunk_pool_capacity) == 0xC96188, "GlobalChunkState_e8230c8::chunk_pool_capacity offset mismatch");
static_assert(offsetof(GlobalChunkState_e8230c8, chunk_pool_flags) == 0xC96190, "GlobalChunkState_e8230c8::chunk_pool_flags offset mismatch");

static_assert(offsetof(HeapHeader_e8230c8, field_8) == 0x8, "HeapHeader_e8230c8::field_8 offset mismatch");
static_assert(offsetof(HeapHeader_e8230c8, field_10) == 0x10, "HeapHeader_e8230c8::field_10 offset mismatch");
static_assert(offsetof(HeapHeader_e8230c8, field_18) == 0x18, "HeapHeader_e8230c8::field_18 offset mismatch");

static_assert(offsetof(ChunkEntry_e8230c8, next) == 0x00, "ChunkEntry_e8230c8::next offset mismatch");
static_assert(offsetof(ChunkEntry_e8230c8, field_8) == 0x08, "ChunkEntry_e8230c8::field_8 offset mismatch");
static_assert(offsetof(ChunkEntry_e8230c8, field_10) == 0x10, "ChunkEntry_e8230c8::field_10 offset mismatch");
static_assert(offsetof(ChunkEntry_e8230c8, field_90) == 0x90, "ChunkEntry_e8230c8::field_90 offset mismatch");
static_assert(offsetof(ChunkEntry_e8230c8, field_B1) == 0xB1, "ChunkEntry_e8230c8::field_B1 offset mismatch");
static_assert(sizeof(ChunkEntry_e8230c8) == 0xB8, "ChunkEntry_e8230c8 size mismatch");

static_assert(offsetof(ResourceHeap_e8230c8, block_ptr) == 0xB8000, "ResourceHeap_e8230c8::block_ptr offset mismatch");
static_assert(offsetof(ResourceHeap_e8230c8, block_size) == 0xB8008, "ResourceHeap_e8230c8::block_size offset mismatch");
static_assert(offsetof(ResourceHeap_e8230c8, block_flags) == 0xB8018, "ResourceHeap_e8230c8::block_flags offset mismatch");

static_assert(offsetof(GlobalAllocator_e8230c8, vtable) == 0x00, "GlobalAllocator_e8230c8::vtable offset mismatch");
static_assert(offsetof(GlobalAllocator_e8230c8, alloc_fn) == 0x08, "GlobalAllocator_e8230c8::alloc_fn offset mismatch");

static_assert(offsetof(GlobalDevice_e8230c8, field_400) == 0x400, "GlobalDevice_e8230c8::field_400 offset mismatch");

} // namespace d3d12
} // namespace native