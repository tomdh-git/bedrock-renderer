#pragma once
// RenderUITextDescription (UI group tag 3), built by ctor 0x668c750
// (docs/progress/uitext_ctor_668c750.txt, docs/functions/668c750.md). Every field below is written by that constructor [V].
// Size 0x60 [I] (aligned end, from Descriptions.h; ctor writes up to +0x58 then 7 tail pad bytes).


namespace mce::framebuilder {

// Reference-counted pointer as the game stores it: object ptr + control block (strong count at ctrl+8).
struct SharedRef {
    void* mPtr;
    void* mCtrl;
};
static_assert(sizeof(SharedRef) == 0x10);

struct RenderUITextDescription {
    const void* mSource;           // +0x00 [V] `0x668c794  mov [rcx],rdx`
    const void* mField08;          // +0x08 [V] `0x668c797  mov [rcx+8],r9`
    SharedRef mTexture;            // +0x10 [V] `0x668c7a6  call 0x4DFB570` (converts r8 to SharedRef at [rcx+0x10] after add rcx,0x10)
    const void* mField20;          // +0x20 [V] `0x668c7ab  mov [rsi+0x20],r13`
    const void* mField28;          // +0x28 [V] `0x668c7af  mov [rsi+0x28],r12`
    const void* mField30;          // +0x30 [V] `0x668c7b3  mov [rsi+0x30],r15`
    uint16_t mFlags;               // +0x38 [V] `0x668c7ba  mov [rsi+0x38],ax` (word from [rdi])
    uint8_t mByte3A;               // +0x3A [V] `0x668c7be  mov [rsi+0x3a],bl`
    char pad3B[5];                 // +0x03B padding (no ctor store; gap before mVariantPayload at +0x040)
    uint8_t mVariantPayload[0x18]; // +0x040 [V] `0x668c7e7  mov [rsi+0x40],rax` (kind 0: u64 from [r14]) `0x668c80b  mov [rax],rcx` (+0x48 SharedRef ctrl from [r14+8]) `0x668c811  mov [rsi+0x50],rax` (+0x50 from [r14+0x10]); kind 1+: 0x20-byte heap copy via 0xF99FFA0 alloc
    uint8_t mVariantIndex;         // +0x058 [V] `0x668c7c1  mov byte ptr [rsi+0x58],0xff` `0x668c89e  mov [rsi+0x58],bl`
    char pad59[7];                 // +0x059 padding (no ctor store; tail to reach 0x60)
};
static_assert(sizeof(RenderUITextDescription) == 0x60);
static_assert(offsetof(RenderUITextDescription, mTexture) == 0x10);
static_assert(offsetof(RenderUITextDescription, mFlags) == 0x38);
static_assert(offsetof(RenderUITextDescription, mVariantIndex) == 0x58);

} // namespace mce::framebuilder
