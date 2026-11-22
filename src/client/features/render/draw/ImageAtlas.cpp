#include "client/features/render/draw/ImageAtlas.h"
#include "client/features/render/backend/OverlayBackend.h"

void ImageAtlas::add(const std::string& id, std::vector<uint8_t> rgba) {
    BS_CHECK(rgba.size() == static_cast<size_t>(mCell) * mCell * 4);
    std::lock_guard lk(mMu);
    mPixels[id] = std::move(rgba);
}

bool ImageAtlas::has(const std::string& id) const {
    std::lock_guard lk(mMu);
    return mPixels.count(id) != 0;
}

bool ImageAtlas::get(const std::string& id, ImTextureID& tex, ImVec2& uv0, ImVec2& uv1) {
    if (!OverlayBackend::ready())
        return false;
    const double now = ImGui::GetTime();
    std::lock_guard lk(mMu);
    // rebuild when pictures were added, but not more often than every 300 ms (a first run adds them one by one)
    if ((mPixels.size() != mBuiltCount || (!mTexture && !mPixels.empty())) && (mBuiltAt < 0.0 || now - mBuiltAt > 0.3)) {
        const int n = static_cast<int>(mPixels.size());
        mCols = std::max(1, static_cast<int>(std::ceil(std::sqrt(static_cast<double>(n)))));
        mRows = (n + mCols - 1) / mCols;
        const UINT W = mCols * mCell, H = mRows * mCell;
        std::vector<uint8_t> atlas(static_cast<size_t>(W) * H * 4, 0);
        std::map<std::string, int> cells;
        int i = 0;
        for (const auto& [key, px] : mPixels) {
            const int cx = i % mCols, cy = i / mCols;
            for (int y = 0; y < mCell; ++y)
                memcpy(&atlas[(static_cast<size_t>(cy * mCell + y) * W + static_cast<size_t>(cx) * mCell) * 4], &px[static_cast<size_t>(y) * mCell * 4], static_cast<size_t>(mCell) * 4);
            cells[key] = i++;
        }
        ID3D12Resource* fresh = OverlayBackend::createTexture(atlas.data(), W, H, DXGI_FORMAT_R8G8B8A8_UNORM, W * 4);
        const ImTextureID freshId = OverlayBackend::registerTexture(fresh);
        releaseTexture();
        mTexture = fresh;
        mTextureId = freshId;
        mCellOf = std::move(cells);
        mBuiltCount = mPixels.size();
        mBuiltAt = now;
    }
    const auto it = mCellOf.find(id);
    if (!mTexture || it == mCellOf.end())
        return false;
    const int cx = it->second % mCols, cy = it->second / mCols;
    const float inset = 0.5f / static_cast<float>(mCols * mCell); // half a texel: a neighbour's edge never bleeds in
    tex = mTextureId;
    uv0 = ImVec2(static_cast<float>(cx) / mCols + inset, static_cast<float>(cy) / mRows + inset);
    uv1 = ImVec2(static_cast<float>(cx + 1) / mCols - inset, static_cast<float>(cy + 1) / mRows - inset);
    return true;
}

void ImageAtlas::releaseTexture() {
    if (mTexture) {
        OverlayBackend::unregisterTexture(mTextureId);
        OverlayBackend::retire(mTexture);
    }
    mTexture = nullptr;
    mTextureId = 0;
    mCellOf.clear();
    mBuiltCount = 0;
    mBuiltAt = -1.0;
}
