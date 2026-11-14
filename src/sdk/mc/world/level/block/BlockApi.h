#pragma once
#include "sdk/OffsetProvider.h"
#include "sdk/mc/deps/core/math/BlockPos.h"
#include "sdk/Layout.h"

// Reading blocks: a BlockSource (the local player's, ClientInstance::getRegion) answers getBlock through its vtable; a Block
// points at its BlockLegacy, which holds the numeric block id (0 = air).
struct Block;
struct BlockSource;

struct BlockApi {
    static Block* getBlock(BlockSource* source, const BlockPos& pos) {
        return callVirtual<Block*>(OffsetProvider::BlockSource_getBlock, source, pos);
    }
    static uint16_t id(const Block* block) {
        const uint8_t* legacy = *reinterpret_cast<const uint8_t* const*>(reinterpret_cast<const uint8_t*>(block) + OffsetProvider::Block_mLegacy);
        return *reinterpret_cast<const uint16_t*>(legacy + OffsetProvider::BlockLegacy_mBlockId);
    }
    static bool isAir(const Block* block) { return id(block) == 0; }
};
