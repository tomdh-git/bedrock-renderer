// MaterialInstance::initFromMaterial chunk 2 header
// LIFT 0xbcc7f20 size 0x7421 1.26.62.01 MaterialInstance::initFromMaterial

#pragma once

#include <cstdint>
#include <cstddef>

// Forward declarations for callees in the lift set
namespace native {
    struct MaterialInstance;
    struct Material;
    struct UniformBlock;

    // Callees (forward declarations with exact ABI signatures)
    void* sub_eea6040(void* allocator, size_t size);                                    // 0xeea6040 - allocator
    void sub_eec73f0();                                                                  // 0xeec73f0
    void sub_e935700(void* ptr, size_t size);                                           // 0xe935700
    void* sub_9bc830(size_t size);                                                      // 0x9bc830
    void sub_eec6de0(void* dst, const void* src, size_t count);                         // 0xeec6de0
    void sub_eec6ec0(void* dst, const void* src, size_t count);                         // 0xeec6ec0
    void sub_bcd7310(void* rcx, void* rdx, void* r8);                                   // 0xbcd7310
    void sub_eec6ec0(void* dst, const void* src, size_t count);                         // 0xeec6ec0 (dup)
    void sub_a0850(void* rcx, int edx, void* r9);                                       // 0xa0850
    void sub_bcd7480(void* rcx, void* rdx, void* r8);                                   // 0xbcd7480
    void sub_1eac280(void* rcx, void* rdx, void* r8);                                   // 0x1eac280
    void sub_56d56a0(void* rcx, void* rdx, void* r8);                                   // 0x56d56a0
    void sub_bcd71a0(void* rcx, void* rdx, void* r8);                                   // 0xbcd71a0
    void sub_bcd7040(void* rcx, void* rdx, void* r8);                                   // 0xbcd7040
    void sub_6b31510(void* rcx, void* rdx, void* r8);                                   // 0x6b31510
    void sub_5679db0(void* rcx, void* rdx, void* r8);                                   // 0x5679db0 (UniformBlock::setUniform)

    // Boundary callees (via native::boundary)
    // None in this chunk that are not in lift set

    // Chunk 2 state struct (matches stack frame layout for 0xbcc9718..0xbccaf16)
    struct Chunk2State {
        // Stack frame base (rbp)
        uintptr_t rbp;

        // Preserved registers across chunk
        MaterialInstance* this_ptr;   // [rbp+0x270] = rsi at entry
        const Material* m;            // rdx at entry

        // Key stack slots used in this chunk
        uint64_t slot_1A0;            // [rbp+0x1A0]
        uint64_t slot_1A8;            // [rbp+0x1A8]
        uint64_t slot_1B0;            // [rbp+0x1B0]
        uint64_t slot_1B8;            // [rbp+0x1B8]
        uint64_t slot_1C0;            // [rbp+0x1C0]
        uint64_t slot_1C8;            // [rbp+0x1C8]
        uint64_t slot_1D0;            // [rbp+0x1D0]
        uint64_t slot_1E0;            // [rbp+0x1E0]
        uint64_t slot_1E8;            // [rbp+0x1E8]
        uint64_t slot_1F0;            // [rbp+0x1F0]
        uint64_t slot_200;            // [rbp+0x200]
        uint64_t slot_208;            // [rbp+0x208]
        uint32_t slot_210;            // [rbp+0x210]
        uint8_t  slot_214;            // [rbp+0x214]
        uint32_t slot_218;            // [rbp+0x218]
        uint64_t slot_228;            // [rbp+0x228]
        uint64_t slot_230;            // [rbp+0x230]
        uint16_t slot_238;            // [rbp+0x238]
        uint8_t  slot_23A;            // [rbp+0x23A]
        uint64_t slot_258;            // [rbp+0x258]
        uint64_t slot_260;            // [rbp+0x260]
        uint64_t slot_268;            // [rbp+0x268]
        uint64_t slot_E0;             // [rbp+0xE0]
        uint64_t slot_120;            // [rbp+0x120]
        uint64_t slot_128;            // [rbp+0x128]
        uint16_t slot_A0;             // [rbp+0xA0]
        uint8_t  slot_A2;             // [rbp+0xA2]
        uint16_t slot_C8;             // [rbp+0xC8]
        uint8_t  slot_CA;             // [rbp+0xCA]
        uint16_t slot_7C;             // [rbp+0x7C]
        uint32_t slot_80;             // [rbp+0x80]
        uint8_t  slot_84;             // [rbp+0x84]
        uint16_t slot_44;             // [rbp+0x44]
        uint32_t slot_48;             // [rbp+0x48]
        uint8_t  slot_4C;             // [rbp+0x4C]
        int32_t  slot_m38;            // [rbp-0x38]
        uint8_t  slot_m28;            // [rbp-0x28]

        // XMM registers spilled to stack
        // xmm6 = [data_eee6700] (constant 1.0f)
        // xmm7 = zero
        // xmm8..xmm15 used for vector constants

        // General purpose registers tracked across blocks
        uint64_t r12, r13, r14, r15;
        uint64_t rbx, rsi, rdi;
    };

    // MaterialInstance field offsets (from dossier)
    struct MaterialInstanceLayout {
        static constexpr size_t kName = 0x128;
        static constexpr size_t kUniformBlock = 0x170;
        static constexpr size_t kUniformListContainer = 0x328;
        static constexpr size_t kUniformList = 0x330;
        static constexpr size_t kFlagsTable = 0x2A8;
        static constexpr size_t kVariantArray = 0x370;
        static constexpr size_t kHashTablePtr = 0x3B0;
        static constexpr size_t kHashTableEnd = 0x3B8;
        static constexpr size_t kHashTableCapacity = 0x3C0;
        static constexpr size_t kHashTableSize = 0x3C8;
        static constexpr size_t kHashTableMask = 0x3D0;
        static constexpr size_t kHashTableEntries = 0x3D8;
        static constexpr size_t kHashTableCount = 0x3E0;
        static constexpr size_t kPassRecords1 = 0x3F0;
        static constexpr size_t kPassRecords2 = 0x428;
        static constexpr size_t kPassRecords3 = 0x440;
        static constexpr size_t kPassRecords4 = 0x458;
        static constexpr size_t kPassRecords5 = 0x460;
    };

    // Material field offsets
    struct MaterialLayout {
        static constexpr size_t kName = 0x40;
        static constexpr size_t kBufferDefs = 0x110;
    };

    // UniformNode field offsets (from dossier)
    struct UniformNodeLayout {
        static constexpr size_t kName = 0x10;
        static constexpr size_t kDefaultVec4 = 0x34;
        static constexpr size_t kHasDefaultVec4 = 0x44;
        static constexpr size_t kHasDefaultMat3 = 0x58;
        static constexpr size_t kDefaultMat3 = 0x34; // +0x24 bytes
        static constexpr size_t kHasDefaultMat4 = 0x74;
        static constexpr size_t kDefaultMat4 = 0x34; // +0x40 bytes
        static constexpr size_t kType = 0x7C; // 1=vec4, 2=mat3, 3=mat4
    };

    // Layout assertions (verified against SDK headers)
    static_assert(sizeof(void*) == 8, "64-bit pointers required");
    static_assert(alignof(max_align_t) >= 16, "SSE alignment required");

    // Chunk entry point
    void MaterialInstance_initFromMaterial_chunk2(MaterialInstance* this_ptr, const Material* m, Chunk2State& state);

    // Registry entry for lift framework
    // LIFT_FN(0xbcc7f20, MaterialInstance_initFromMaterial_chunk2, "MaterialInstance::initFromMaterial", KnownRva::bcc7f20, Mode::Shadow);

} // namespace native