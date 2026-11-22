#include "client/features/render/draw/GifAnim.h"
#include "client/features/render/backend/OverlayBackend.h"
#include "client/platform/image/Image.h"

void GifAnim::clear() {
    if (res12) {
        OverlayBackend::unregisterTexture(texId);
        OverlayBackend::retire(res12);
        res12 = nullptr;
    }
    texId = 0;
    loadedKey.clear();
    idx = 0;
    t = 0.f;
    imgW = imgH = 0;
}

void GifAnim::finish(UINT w, UINT h, const char* key) {
    imgW = (int)w;
    imgH = (int)h;
    frames = imgW >= imgH ? imgW / (imgH > 0 ? imgH : 1) : 1;
    if (frames < 1)
        frames = 1;
    loadedKey = key;
}

bool GifAnim::ensure(const uint8_t* data, size_t size, const char* key) {
    if (!data || size == 0 || !key || !key[0] || !OverlayBackend::ready())
        return false;
    if (res12 && loadedKey == key)
        return true;
    clear();
    Platform::Image img;
    if (!Platform::ImageDecoder::decode(data, size, img))
        return false;
    res12 = OverlayBackend::createTexture(img.rgba.data(), img.width, img.height, DXGI_FORMAT_R8G8B8A8_UNORM, img.width * 4);
    texId = OverlayBackend::registerTexture(res12);
    finish(img.width, img.height, key);
    return true;
}

void GifAnim::update(float dt) {
    if (frames < 2 || dt <= 0.f)
        return;
    t += dt;
    int guard = 0;
    while (t >= frameDt && guard++ < 64) {
        t -= frameDt;
        idx = (idx + 1) % (size_t)frames;
    }
}

void GifAnim::draw(ImDrawList* d, ImVec2 pos, float h, int alpha) {
    if (!texId || imgW <= 0 || imgH <= 0 || frames < 1)
        return;
    float cellW = (float)imgW / (float)frames;
    float w = h * cellW / (float)imgH;
    float u0 = (float)idx / (float)frames;
    float u1 = (float)(idx + 1) / (float)frames;
    d->AddImage(texId, pos, ImVec2(pos.x + w, pos.y + h), ImVec2(u0, 0), ImVec2(u1, 1), IM_COL32(255, 255, 255, alpha));
}

void GifAnim::shutdown() {
    clear();
}
