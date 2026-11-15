#pragma once
// u32 filesystem + path string + two u64 hashes. Total unstated, so no assert.
class ResourceLocation {
public:
    uint32_t mFileSystem = 0;
    std::string mPath;
    uint64_t mPathHash = 0;
    uint64_t mFullHash = 0;
    bool empty() const {
        return mPath.empty();
    }
};
