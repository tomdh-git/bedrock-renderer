#pragma once

// std::shared_ptr / std::weak_ptr as the game lays them out: object pointer, then the control block.
template <typename T>
struct GameSharedPtr {
    T* ptr;
    void* control;
};
static_assert(sizeof(GameSharedPtr<int>) == 16);
