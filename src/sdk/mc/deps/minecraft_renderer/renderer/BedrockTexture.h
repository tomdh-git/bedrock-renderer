#pragma once
// Three shared_ptr<BedrockTextureData> members (16B x 3). Data contents
// unproven; shared_ptrs keep the stated 48B size. Ctors need game; omitted
// (stub-only carrier).
class BedrockTexture {
public:
    std::shared_ptr<void> mBedrockTextureData;
    std::shared_ptr<void> mBedrockMERSTextureData;
    std::shared_ptr<void> mBedrockNormalTextureData;
};
static_assert(sizeof(BedrockTexture) == 48);
