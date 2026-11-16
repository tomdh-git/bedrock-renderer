#pragma once

// U-D5d: Crack description clone 0x539fff0 (Item group tag 5).
// Layout verified from stores into the stack-built description at rbp+0x60 inside
// sub_539fff0 (docs/progress/oc_U-D5d.md, all offsets [V] stores; size past +0x24 [I]).
// Mirrors src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h::RenderCrackDescription.

namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

// RenderCrackDescription (Item group tag 5), one per crack overlay, built on the stack by 0x539fff0.
// Field offsets are the clone's stores [V]; the size past +0x24 is not proven [I].
struct RenderCrackDescription {
    const void* mMesh;           // +0x00 the crack entry's mesh (entry +0x00); stored at 0x53a0499
    SharedRef mTexture;          // +0x08 the crack material's texture, converted by 0x4dfb570 (stored via callee at 0x53a04a8)
    const void* mCameraRecord;   // +0x18 pointer to the newest camera record of the extraction ring (stored at 0x53a04b2)
    uint8_t mStage;              // +0x20 destroy stage (entry +0x18); stored at 0x53a04b6
    uint8_t mPad21;
    uint16_t mFlags;             // +0x22 context byte +0x74, widened; stored at 0x53a04bd
    uint8_t mPad24[4];
};
static_assert(offsetof(RenderCrackDescription, mTexture) == 0x08);
static_assert(offsetof(RenderCrackDescription, mCameraRecord) == 0x18);
static_assert(offsetof(RenderCrackDescription, mStage) == 0x20);
static_assert(offsetof(RenderCrackDescription, mFlags) == 0x22);

}
