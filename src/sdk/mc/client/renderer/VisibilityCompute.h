#pragma once

// Cave-visibility compute for one 16x16x16 sub-chunk (1.26.62.01): fn 0x791f170 (docs/functions/791f170.md), called by 0x6b0c4c0.
// Layouts are read from the disassembly of 0x791f170 and 0x6b0c4c0 (docs/progress/ext-culling-visitor.md, H1b). Pure documentation
// types: nothing in the client dereferences game memory through them yet.
namespace mc::visibility {

// Argument 1 of 0x791f170 (rcx -> rsi): the result object filled by the compute.
struct ComputeResult {
    uint8_t  valid;        // +0x00: 1 at start; 0 when a neighbour sample says the section is incomplete
    uint8_t  hasNeighbour; // +0x01: return value of 0x7918580(&state.pos, chunkSource)
    uint32_t faceBytesLo;  // +0x02: face bytes 0..3 (unaligned in the game)
    uint16_t faceBytesHi;  // +0x06: face bytes 4..5
    uint8_t  allAir;       // +0x08: dil, 1 = every voxel was the air block
    uint8_t  pad9[7];
    void*    chunkSource;  // +0x10: vcall +0x148 = getChunk(x>>4, z>>4)
};
#pragma pack(push, 1)
struct FaceBytes { uint8_t b[6]; }; // six 6-bit rows; row i never has bit i (masks 0x3e,0x3d,0x3b,0x37,0x2f,0x1f)
#pragma pack(pop)
static_assert(offsetof(ComputeResult, valid) == 0x00);
static_assert(offsetof(ComputeResult, hasNeighbour) == 0x01);
static_assert(offsetof(ComputeResult, allAir) == 0x08);
static_assert(offsetof(ComputeResult, chunkSource) == 0x10);
static_assert(sizeof(FaceBytes) == 6);

// Argument 2 (rdx -> rbx): the visibility state; the section origin is read at +0x14/+0x18/+0x1c (s32 block coords).
constexpr size_t kStateOriginX = 0x14, kStateOriginY = 0x18, kStateOriginZ = 0x1c;
constexpr size_t kStateFaceBytes = 0x38, kStateDirty = 0x3e; // written by 0x6b0c4c0 / compared by 0x6b0c570

// Thread-local scratch (TLS slot index at rva 0x12ac..[rip+0xaf5754c-relative]; pointer S): occupancy grid used by 0x6b1ba90.
constexpr size_t kScratchFloodGrid  = 0x19f0; // grid object handed to 0x6b1ba90
constexpr size_t kScratchOriginX    = 0x1a28; // = kScratchFloodGrid + 0x38
constexpr size_t kScratchOriginY    = 0x1a2c;
constexpr size_t kScratchOriginZ    = 0x1a30;
constexpr size_t kScratchRemaining  = 0x1a34; // starts 0x1000, minus 1 per opaque voxel
constexpr size_t kScratchVoxels     = 0x1a38; // 0x1000 bytes, index ((x&0xff)<<8)|(y<<4)|z, written at grid+0x48 in 0x791f504
constexpr size_t kGridVoxelsOffset  = 0x48;   // from kScratchFloodGrid
static_assert(kScratchFloodGrid + kGridVoxelsOffset == 0x1a38);
static_assert(kScratchFloodGrid + 0x44 == kScratchRemaining);

// Block flag read per voxel: Block+0xA3 == 1 means opaque (visibility blocking).
constexpr size_t kBlockOpaqueFlag = 0xA3;
// Sub-chunk record: stride 0x68 in the chunk array at chunk+0x1C8, Y check byte at +0x61, block array object at +0x30.
constexpr size_t kChunkSubChunkArray = 0x1C8, kSubChunkStride = 0x68, kSubChunkYByte = 0x61, kSubChunkBlocks = 0x30;
constexpr uint16_t kSectionSentinel = 0xF800;

} // namespace mc::visibility
