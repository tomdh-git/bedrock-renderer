#pragma once
// RenderUIMeshDescription (UI group tag 2). Constructor 0x668c3c0 (rcx = destination, [rsi] = description) writes every
// byte [V]: qwords +0x00/+0x08/+0x10; four zeroed shared-ref pairs +0x18..+0x57 (movups at +0x18/+0x28/+0x38/+0x48);
// count qword +0x58 = 0; qwords +0x60/+0x68; float +0x70; qword +0x78; bytes +0x80..+0x85; word +0x86;
// variant storage +0x88..+0x9F (kind-dependent: kind 0 writes u64 at +0x88, zeroes shared-ref pair at +0x90,
// qword at +0x98; kind 1 heap-copies via 0xF99FFA0); tag byte +0xA0 = 0xFF [V]. End 0xA1, so sizeof 0xA8 [V].
// Field meanings are [-]: no instruction or string names them.

namespace mce::framebuilder {

struct RenderUIMeshDescription {
    uint64_t mValue00;         // +0x00 [V] `0x668c42f  mov [rsi],rcx`
    uint64_t mValue08;         // +0x08 [V] `0x668c432  mov [rsi+8],r8`
    uint64_t mValue10;         // +0x10 [V] `0x668c436  mov [rsi+0x10],rax`
    uint8_t mRefs[4][0x10];    // +0x18..+0x57 [V] four zeroed shared-ref pairs:
                               // `0x668c445  movups [rsi+0x18],xmm1` `0x668c449  movups [rsi+0x28],xmm1`
                               // `0x668c44d  movups [rsi+0x38],xmm1` `0x668c451  movups [rsi+0x48],xmm1`
    uint64_t mRefCount;        // +0x58 [V] `0x668c455  mov qword ptr [rsi+0x58],0`
    uint64_t mValue60;         // +0x60 [V] `0x668c45d  mov [rsi+0x60],r13`
    uint64_t mValue68;         // +0x68 [V] `0x668c461  mov [rsi+0x68],r12`
    float  mValue70;           // +0x70 [V] `0x668c465  movss [rsi+0x70],xmm0`
    uint64_t mValue78;         // +0x78 [V] `0x668c46a  mov [rsi+0x78],r15`
    uint8_t mFlags80[6];       // +0x80..+0x85 [V] `0x668c46e  mov [rsi+0x80],r14b` ... `0x668c49e  mov [rsi+0x85],al`
    uint16_t mValue86;         // +0x86 [V] `0x668c4a7  mov [rsi+0x86],ax`
    uint8_t mVariantStorage88[0x18]; // +0x88 [V kind-dependent] `0x668c4e2  mov [rsi+0x88],rax`,
                                       // `0x668c4f3  movups [rsi+0x90],xmm0`, `0x668c515  mov [rsi+0x98],rax`
    uint8_t mVariantTag;       // +0xA0 [V] `0x668c4b9  mov byte ptr [rsi+0xA0],0xFF` (0xFF = empty)
    uint8_t mPadA1[7];
};
static_assert(sizeof(RenderUIMeshDescription) == 0xA8);
static_assert(offsetof(RenderUIMeshDescription, mRefs) == 0x18);
static_assert(offsetof(RenderUIMeshDescription, mRefCount) == 0x58);
static_assert(offsetof(RenderUIMeshDescription, mValue60) == 0x60);
static_assert(offsetof(RenderUIMeshDescription, mValue70) == 0x70);
static_assert(offsetof(RenderUIMeshDescription, mValue78) == 0x78);
static_assert(offsetof(RenderUIMeshDescription, mFlags80) == 0x80);
static_assert(offsetof(RenderUIMeshDescription, mValue86) == 0x86);
static_assert(offsetof(RenderUIMeshDescription, mVariantStorage88) == 0x88);
static_assert(offsetof(RenderUIMeshDescription, mVariantTag) == 0xA0);

} // namespace mce::framebuilder
