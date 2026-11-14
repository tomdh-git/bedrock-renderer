#pragma once

// Reading a chunk's blocks straight from its sub chunks' palettes, a whole sub chunk at a time, instead of one BlockSource::getBlock (a virtual call, a chunk lookup and a
// palette read) per block. A sub chunk's block storage hands out the Block of a cell by its index (the palette lookup is inside it): 4096 cells, one call each.
//
//   LevelChunk::mSubChunks (a vector of SubChunk, 0x68 bytes each)  ->  SubChunk::mBlocksReadPtr[0]  ->  SubChunkStorage<Block>, whose virtual slot 3 is
//   getElement(index) with index = (x * 16 + z) * 16 + y, the three of them 0..15 inside the sub chunk.
//
// Layout facts: the vector's place and the SubChunk's fields come from the LeviLamina 26.60 headers (static_assert'ed in LevelChunk.h and below); the storage's virtual slot
// is from the game's own SubChunkBlockStorage (dtor, isUniform, isPaletteUniform, getElement) and is NOT in any header. selfTest compares the whole thing with getBlock on the
// live game, so a build where any of it moved is found out on the first use and not trusted.
struct Block;
struct BlockSource;
struct LevelChunk;

struct ChunkBlocks {
    static constexpr size_t kSubChunkSize = 0x68;     // sizeof(SubChunk): the stride of LevelChunk::mSubChunks
    static constexpr size_t kBlocksReadPtr = 0x30;    // SubChunk::mBlocksReadPtr[0] (the standard layer)
    static constexpr int kGetElementSlot = 3;         // SubChunkStorage<Block>: ~, isUniform, isPaletteUniform, getElement

    // The chunk at the chunk coordinates: BlockSource keeps the last chunk it read (mLastChunkDirectPtr), so one getBlock inside the chunk brings it up. The chunk's own
    // position is checked against the one asked for; nullptr when that chunk is not loaded.
    static LevelChunk* chunk(BlockSource* source, int chunkX, int chunkZ, int probeY);
    static int subChunkCount(LevelChunk* chunk);
    // The block storage of the sub chunk at this index in the chunk's vector (0 is the world's lowest), nullptr when the chunk has no such sub chunk or it has no blocks.
    static void* storage(LevelChunk* chunk, int index);
    // The block of one cell of a sub chunk's storage: x, y, z inside it (0..15).
    static const Block* element(void* storage, int x, int y, int z);

    // Whether the above reads the same blocks as getBlock does, at the player's own place. Wrong: it does not (nothing here is to be used). Inconclusive: it agrees, but
    // there was only one kind of block around to compare (all air), so it is asked again later. Once per world, cheap.
    enum class Verdict { Right, Wrong, Inconclusive };
    static Verdict selfTest(BlockSource* source, int playerX, int playerY, int playerZ);
};
