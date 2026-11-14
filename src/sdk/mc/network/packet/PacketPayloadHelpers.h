#pragma once

inline uint64_t readActorRuntimeId(const std::byte* data) {
    uint64_t value = 0;
    std::memcpy(&value, data, sizeof(value));
    return value;
}

inline void writeActorRuntimeId(std::byte* data, uint64_t value) {
    std::memcpy(data, &value, sizeof(value));
}

inline uint64_t readCreateTime(const std::byte* data) {
    uint64_t value = 0;
    std::memcpy(&value, data, sizeof(value));
    return value;
}

inline void writeCreateTime(std::byte* data, uint64_t value) {
    std::memcpy(data, &value, sizeof(value));
}
