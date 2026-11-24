// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1 (part 1/7)
#pragma once

#include <cstdint>
#include <cstddef>

// Forward declarations for callees (lift set)
namespace native {
    // vendor thunk via data_f99ffa0 (0xeea6040) - boundary:vendor
    using Thunk_eea6040_t = void(*)(void* rcx, uint32_t edx, void* r8, void* r9, void* stack_rsp20);
    extern Thunk_eea6040_t g_thunk_eea6040;

    // lift callees (forward declared)
    void sub_e82d960(void* rcx, void* rdx, uint32_t r8d, void* r9);
    void sub_ebce390(void* rcx, void* rdx, uint32_t r8d);
    void sub_e82dcc0(void* rcx, uint32_t r8d);
    void sub_ebd1560(void* rcx);
    void sub_e82de90(void* rcx, void* rdx, void* r8);
    void sub_e935700(void* rcx);
    void sub_e835b50(void* rcx, uint32_t edx);
    void sub_eec6ed0(void* rcx, uint32_t r8d, uint32_t edx); // boundary:crt
    void sub_e820500(void* rcx, void* rdx, void* r8, void* r9); // lift
    void sub_e83ace0(void* rcx, ...); // lift
    void sub_e82306e(...);
    void sub_e823066(...);
    void sub_e827c85(...);
    void sub_e82d4c4(...);
}

// Chunk state for 0xe824af1..0xe826261
// Live registers at entry: rbx, rbp, r12-r15, rsi, rdi, xmm6-xmm15
// Stack frame: 0xE238 bytes, rbp = rsp + 0x80, rbx = rsp (after alignment)
struct ChunkState_e824af1_part1 {
    // Stack slots relative to rbx (rsp after alignment)
    // Offsets from dossier
    void* job_context;              // [rbx+0xA0]  - saved rcx (a0)
    void* saved_r8;                 // [rbx+0x168] - saved r8 (a2)
    void* saved_r9;                 // [rbx+0x3A8] - saved r9 (a3)
    uint32_t loop_index;            // [rbx+0xF0]
    uint32_t loop_limit;            // [rbx+0x150]
    void* item_array_base;          // [rbx+0x1C0]
    void* second_ptr_limit;         // [rbx+0x110]
    void* output_buffer;            // [rbx+0xB8]
    void* output_index_array;       // [rbx+0x2C0]
    void* per_item_structs_base;    // [rbx+0x3A0]
    void* resource_table;           // [rbx+0x90]
    void* simd_constant_table_base; // [rbx+0x90A0]
    uint16_t saved_word_e174;       // [rbx+0xE174]
    uint16_t loaded_word_5f0;       // [rbx+0x5F0]
    uint64_t const_neg_100000000;   // [rbx+0x4C0] = -0x100000000
    __m128 xmm_scratch_4e0;         // [rbx+0x4E0] zeroed
    __m128 xmm_scratch_4f0;         // [rbx+0x4F0] zeroed
    __m128 copied_data_efc6ae0;     // [rbx+0x504]
    uint32_t initialized_1_514;     // [rbx+0x514] = 1
    uint64_t const_1ffff00000000;   // [rbx+0x518] = 0x1FFFF00000000
    uint16_t const_ffff_520;        // [rbx+0x520] = 0xFFFF
    uint8_t zeroed_522;             // [rbx+0x522] = 0
    uint16_t const_ff00_523;        // [rbx+0x523] = 0xFF00
    uint32_t const_7fffffff_528;    // [rbx+0x528] = 0x7FFFFFFF
    uint64_t zeroed_52c;            // [rbx+0x52C] = 0
    int64_t const_neg1_534;         // [rbx+0x534] = -1
    void* buffer_start_678;         // [rbx+0x678]
    void* buffer_end_680;           // [rbx+0x680]
    void* saved_ptr_688;            // [rbx+0x688]
    uint32_t val_690;               // [rbx+0x690] = 0xFFFFFFFF / 0x3F003E
    __m128 copied_consts_794[7];    // [rbx+0x794..0x804] from data_f441720..data_f441790
    uint32_t const_3f003e_814;      // [rbx+0x814] = 0x3F003E
    void* computed_per_item_addr;   // [rbx+0x90A8]
    uint64_t zeroed_20;             // [rbx+0x20] shadow space
    uint32_t zeroed_28;             // [rbx+0x28] shadow space

    // Live registers at chunk entry
    void* rbx;  // frame base
    void* rbp;  // rsp + 0x80
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    void* rsi;  // draw item list base (from rdx)
    void* rdi;  // loop counter / index
    // xmm6-xmm15 preserved (not modeled here)

    // Arguments at parent entry (sub_e821120)
    void* a0_job_context;  // rcx
    void* a1_draw_items;   // rdx
    void* a2_saved_r8;     // r8
    void* a3_saved_r9;     // r9
};

// Layout constants with static_asserts
namespace layout_e824af1_part1 {
    constexpr size_t JOB_CONTEXT_OFF = 0xA0;
    constexpr size_t SAVED_R8_OFF = 0x168;
    constexpr size_t SAVED_R9_OFF = 0x3A8;
    constexpr size_t LOOP_INDEX_OFF = 0xF0;
    constexpr size_t LOOP_LIMIT_OFF = 0x150;
    constexpr size_t ITEM_ARRAY_BASE_OFF = 0x1C0;
    constexpr size_t SECOND_PTR_LIMIT_OFF = 0x110;
    constexpr size_t OUTPUT_BUFFER_OFF = 0xB8;
    constexpr size_t OUTPUT_INDEX_ARRAY_OFF = 0x2C0;
    constexpr size_t PER_ITEM_STRUCTS_BASE_OFF = 0x3A0;
    constexpr size_t RESOURCE_TABLE_OFF = 0x90;
    constexpr size_t SIMD_CONST_TABLE_BASE_OFF = 0x90A0;
    constexpr size_t SAVED_WORD_E174_OFF = 0xE174;
    constexpr size_t LOADED_WORD_5F0_OFF = 0x5F0;
    constexpr size_t CONST_NEG_100000000_OFF = 0x4C0;
    constexpr size_t XMM_SCRATCH_4E0_OFF = 0x4E0;
    constexpr size_t XMM_SCRATCH_4F0_OFF = 0x4F0;
    constexpr size_t COPIED_DATA_EFC6AE0_OFF = 0x504;
    constexpr size_t INITIALIZED_1_514_OFF = 0x514;
    constexpr size_t CONST_1FFFF00000000_OFF = 0x518;
    constexpr size_t CONST_FFFF_520_OFF = 0x520;
    constexpr size_t ZEROED_522_OFF = 0x522;
    constexpr size_t CONST_FF00_523_OFF = 0x523;
    constexpr size_t CONST_7FFFFFFF_528_OFF = 0x528;
    constexpr size_t ZEROED_52C_OFF = 0x52C;
    constexpr size_t CONST_NEG1_534_OFF = 0x534;
    constexpr size_t BUFFER_START_678_OFF = 0x678;
    constexpr size_t BUFFER_END_680_OFF = 0x680;
    constexpr size_t SAVED_PTR_688_OFF = 0x688;
    constexpr size_t VAL_690_OFF = 0x690;
    constexpr size_t COPIED_CONSTS_794_OFF = 0x794;
    constexpr size_t CONST_3F003E_814_OFF = 0x814;
    constexpr size_t COMPUTED_PER_ITEM_ADDR_OFF = 0x90A8;
    constexpr size_t ZEROED_20_OFF = 0x20;
    constexpr size_t ZEROED_28_OFF = 0x28;

    // Stack frame size
    constexpr size_t STACK_FRAME_SIZE = 0xE238;
    constexpr size_t RBP_OFFSET_FROM_RSP = 0x80;

    static_assert(JOB_CONTEXT_OFF == 0xA0);
    static_assert(SAVED_R8_OFF == 0x168);
    static_assert(SAVED_R9_OFF == 0x3A8);
    static_assert(LOOP_INDEX_OFF == 0xF0);
    static_assert(LOOP_LIMIT_OFF == 0x150);
    static_assert(ITEM_ARRAY_BASE_OFF == 0x1C0);
    static_assert(SECOND_PTR_LIMIT_OFF == 0x110);
    static_assert(OUTPUT_BUFFER_OFF == 0xB8);
    static_assert(OUTPUT_INDEX_ARRAY_OFF == 0x2C0);
    static_assert(PER_ITEM_STRUCTS_BASE_OFF == 0x3A0);
    static_assert(RESOURCE_TABLE_OFF == 0x90);
    static_assert(SIMD_CONST_TABLE_BASE_OFF == 0x90A0);
    static_assert(SAVED_WORD_E174_OFF == 0xE174);
    static_assert(LOADED_WORD_5F0_OFF == 0x5F0);
    static_assert(CONST_NEG_100000000_OFF == 0x4C0);
    static_assert(XMM_SCRATCH_4E0_OFF == 0x4E0);
    static_assert(XMM_SCRATCH_4F0_OFF == 0x4F0);
    static_assert(COPIED_DATA_EFC6AE0_OFF == 0x504);
    static_assert(INITIALIZED_1_514_OFF == 0x514);
    static_assert(CONST_1FFFF00000000_OFF == 0x518);
    static_assert(CONST_FFFF_520_OFF == 0x520);
    static_assert(ZEROED_522_OFF == 0x522);
    static_assert(CONST_FF00_523_OFF == 0x523);
    static_assert(CONST_7FFFFFFF_528_OFF == 0x528);
    static_assert(ZEROED_52C_OFF == 0x52C);
    static_assert(CONST_NEG1_534_OFF == 0x534);
    static_assert(BUFFER_START_678_OFF == 0x678);
    static_assert(BUFFER_END_680_OFF == 0x680);
    static_assert(SAVED_PTR_688_OFF == 0x688);
    static_assert(VAL_690_OFF == 0x690);
    static_assert(COPIED_CONSTS_794_OFF == 0x794);
    static_assert(CONST_3F003E_814_OFF == 0x814);
    static_assert(COMPUTED_PER_ITEM_ADDR_OFF == 0x90A8);
    static_assert(ZEROED_20_OFF == 0x20);
    static_assert(ZEROED_28_OFF == 0x28);
    static_assert(STACK_FRAME_SIZE == 0xE238);
    static_assert(RBP_OFFSET_FROM_RSP == 0x80);
}

// Data references (RIP-relative addresses from disassembly)
namespace data_e824af1_part1 {
    // data_f99ffa0 = pointer to sub_eea6040 (vendor thunk)
    extern uint64_t* const data_f99ffa0;
    // data_12bb4910
    extern void* const data_12bb4910;
    // data_f4ee7d0 (jump table)
    extern int32_t const data_f4ee7d0;
    // data_12ae0d80
    extern uint32_t const data_12ae0d80;
    // data_12adfa53
    extern uint8_t const data_12adfa53;
    // data_efc6ae0 (copied to [rbx+0x504])
    extern __m128 const data_efc6ae0;
    // data_f441720..data_f441790 (copied to [rbx+0x794..0x804])
    extern __m128 const data_f441720[7];
}

// Chunk entry function
// Called from sub_e821120 switch case 8 at 0xe8230c6
// Signature matches x64 Microsoft ABI with this in rcx for methods, but this is a free function chunk
// The chunk is entered with registers as documented in ChunkState_e824af1_part1
extern "C" void sub_e824af1_chunk_0(ChunkState_e824af1_part1* state);

// Registry entry via LIFT_FN
#define LIFT_FN_e824af1_chunk_0 LIFT_FN(sub_e824af1_chunk_0, "sub_e824af1", 0xe824af1, 0x89f2, NativeMode::Shadow)

#endif // sub_e824af1_part1_h