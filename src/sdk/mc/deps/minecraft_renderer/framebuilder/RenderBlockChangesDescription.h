#pragma once
// RenderBlockChangesDescription (Item group tag 9). Item visitor 0x6646980 tag-9 case 0x6646bc6 reads the description
// (in rdi): movups +0x00 (16 bytes) and movsd +0x10 (8 bytes) [V], then copies a 0x18-byte element into the pass vector
// at pass+0x98 (`0x6646c75  movups [r12],xmm7`; `0x6646c7a  movlps [r12+0x10],xmm6`;
// `0x6646c80  add qword ptr [rsi+0x98],0x18`) [V]. Producer/slot for tag 9 not located [open]. Size 0x18 [V]. Field
// meanings are [-].

namespace mce::framebuilder {

struct RenderBlockChangesDescription {
    float  mVec00[4];   // +0x00 [V] `0x6646bc6  movups xmm7,[rdi]`
    uint64_t mQword10;  // +0x10 [V] `0x6646bc9  movsd xmm6,[rdi+0x10]`
};
static_assert(sizeof(RenderBlockChangesDescription) == 0x18);
static_assert(offsetof(RenderBlockChangesDescription, mQword10) == 0x10);

} // namespace mce::framebuilder
