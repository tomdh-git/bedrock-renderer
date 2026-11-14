#pragma once

struct BlockPos {
    int x = 0;
    int y = 0;
    int z = 0;
};
static_assert(sizeof(BlockPos) == 12);
