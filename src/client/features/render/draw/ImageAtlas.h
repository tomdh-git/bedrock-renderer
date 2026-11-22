#pragma once

// Equally sized pictures packed into ONE texture, so drawing one is a lookup: no file, no decode, no texture per picture (avatars, icons).
// The pixels are kept in memory (device independent: they survive the renderer's resets); the texture is built on the render thread, at most every
// 300 ms while pictures are being added.
class ImageAtlas {
public:
    explicit ImageAtlas(int cell) : mCell(cell) {}

    void add(const std::string& id, std::vector<uint8_t> rgba); // any thread: cell x cell straight RGBA, replacing a picture with that id
    bool has(const std::string& id) const;
    // Render thread: the atlas texture and this picture's rectangle in it; false while the id has no picture.
    bool get(const std::string& id, ImTextureID& tex, ImVec2& uv0, ImVec2& uv1);
    void releaseTexture(); // the renderer's device generation ends: the texture goes, the pixels stay

private:
    int mCell;
    mutable std::mutex mMu;
    std::map<std::string, std::vector<uint8_t>> mPixels;
    ID3D12Resource* mTexture = nullptr;
    ImTextureID mTextureId = 0;
    std::map<std::string, int> mCellOf;
    int mCols = 1, mRows = 1;
    size_t mBuiltCount = 0;
    double mBuiltAt = -1.0;
};
