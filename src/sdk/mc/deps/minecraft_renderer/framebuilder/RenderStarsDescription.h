#pragma once
// RenderStarsDescription (Sky group tag 6), Stars clone 0x5369b30 + insert 0x536e193.
// Size 0x60 [I] (aligned end of the last read at +0x5A, then pad to 0x60).
// Field-level [V] marks an offset touched by a verified clone store; [I] = inferred, not individually confirmed.
// Evidence RVAs verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderStarsDescription {
    const void* mMesh;                // +0x00 [V] `0x536e006  mov rax,[rdi+0x700]` (clone loads mesh ptr)
    uint8_t mPad08[0x58 - 0x08];      // +0x08..+0x57 [I] block (+0x08 block, +0x18 matrix per clone narrative)
    uint16_t mFlags;                  // +0x58 [I] flags (clone narrative)
    uint8_t mByte5A;                  // +0x5A [V] `0x536e112  mov [rbp+0x14A],al` (byte store)
    uint8_t mPad5B[5];                // +0x5B padding (tail to reach 0x60)
};
static_assert(sizeof(RenderStarsDescription) == 0x60);
static_assert(offsetof(RenderStarsDescription, mMesh) == 0x00);
static_assert(offsetof(RenderStarsDescription, mByte5A) == 0x5A);

} // namespace mce::framebuilder
