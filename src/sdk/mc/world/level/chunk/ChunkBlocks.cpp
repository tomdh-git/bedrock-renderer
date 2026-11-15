#include "sdk/mc/world/level/chunk/ChunkBlocks.h"
#include "client/core/diagnostics/Log.h"
#include "sdk/Layout.h"
#include "sdk/mc/world/level/BlockSource.h"
#include "sdk/mc/world/level/block/BlockApi.h"
#include "sdk/mc/world/level/chunk/LevelChunk.h"

LevelChunk* ChunkBlocks::chunk(BlockSource* source, int chunkX, int chunkZ, int probeY) {
    BlockApi::getBlock(source, BlockPos{chunkX * 16, probeY, chunkZ * 16});
    LevelChunk* c = source->mLastChunkDirectPtr;
    if (!c)
        return nullptr;
    const int32_t* position = reinterpret_cast<const int32_t*>(reinterpret_cast<const uint8_t*>(c) + offsetof(LevelChunk, mPosition));
    return position[0] == chunkX && position[1] == chunkZ ? c : nullptr;
}

int ChunkBlocks::subChunkCount(LevelChunk* c) {
    const size_t bytes = static_cast<size_t>(c->mSubChunks.last - c->mSubChunks.first);
    return static_cast<int>(bytes / kSubChunkSize);
}

void* ChunkBlocks::storage(LevelChunk* c, int index) {
    if (index < 0 || index >= subChunkCount(c))
        return nullptr;
    const uint8_t* subChunk = reinterpret_cast<const uint8_t*>(c->mSubChunks.first) + static_cast<size_t>(index) * kSubChunkSize;
    return *reinterpret_cast<void* const*>(subChunk + kBlocksReadPtr);
}

const Block* ChunkBlocks::element(void* storage, int x, int y, int z) {
    return callVirtual<const Block*>(kGetElementSlot, storage, static_cast<uint16_t>((x * 16 + z) * 16 + y));
}

ChunkBlocks::Verdict ChunkBlocks::selfTest(BlockSource* source, int playerX, int playerY, int playerZ) {
    const int chunkX = playerX >> 4, chunkZ = playerZ >> 4;
    LevelChunk* c = chunk(source, chunkX, chunkZ, playerY);
    if (!c) {
        Logger::warn("[chunkblocks] the player's own chunk could not be found through the block source's last-chunk cache: the slow block scan is used");
        return Verdict::Wrong;
    }
    const size_t bytes = static_cast<size_t>(c->mSubChunks.last - c->mSubChunks.first);
    if (bytes == 0 || bytes % kSubChunkSize != 0) {
        Logger::warn("[chunkblocks] the chunk's sub chunk vector holds {:#x} bytes, not a multiple of {:#x}: the slow block scan is used", bytes, kSubChunkSize);
        return Verdict::Wrong;
    }
    // The player's sub chunk and the two next to it: all air would match by luck whatever the index order is, so the cells have to hold more than one kind of block.
    const int minHeight = source->mMinHeight;
    const int middle = (playerY - minHeight) >> 4;
    std::unordered_set<const Block*> kinds;
    int compared = 0, equal = 0;
    for (int index = middle - 1; index <= middle + 1; ++index) {
        void* blocks = storage(c, index);
        if (!blocks)
            continue;
        const int baseY = minHeight + index * 16;
        for (int i = 0; i < 64; ++i) {
            const int x = (i * 5) & 15, z = (i * 7) & 15, y = (i * 3) & 15;
            const Block* fast = element(blocks, x, y, z);
            const Block* slow = BlockApi::getBlock(source, BlockPos{chunkX * 16 + x, baseY + y, chunkZ * 16 + z});
            kinds.insert(slow);
            ++compared;
            equal += fast == slow;
        }
    }
    if (compared == 0) {
        Logger::warn("[chunkblocks] no block storage in the player's sub chunks (index {}): the slow block scan is used", middle);
        return Verdict::Wrong;
    }
    if (equal != compared) {
        Logger::warn("[chunkblocks] the palette read differs from getBlock in {} of {} cells: the slow block scan is used", compared - equal, compared);
        return Verdict::Wrong;
    }
    if (kinds.size() < 2)
        return Verdict::Inconclusive; // nothing but one block around: asked again later
    Logger::info("[chunkblocks] the palette read matches getBlock ({} cells, {} kinds of block, {} sub chunks in the chunk, lowest block {}): the fast block scan is used", compared, kinds.size(),
                 bytes / kSubChunkSize, minHeight);
    return Verdict::Right;
}
