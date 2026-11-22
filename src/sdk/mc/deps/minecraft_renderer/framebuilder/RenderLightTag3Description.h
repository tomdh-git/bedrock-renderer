#pragma once
// RenderLightTag3Description (Light group tag 3 = LightPoint [I tag per descriptions.md R6]). Light visitor
// 0x6640d80 case 0x66410a0 reads the description (in rsi): scalars +0x00 qword, +0x08 qword, +0x10 dword,
// +0x14 qword, +0x1C dword, +0x20 byte, +0x28 qword, +0x30 word [V]; six slices at +0x38 + k*0x20 (k = 0..5),
// each {weak_ptr pointer, weak_ptr control block (the case does `lock inc [ctrl+0xC]` = weak-count inc [V]), vec4}
// [V]; then qword +0xF8 and dword +0x100 [V]. Last read ends at +0x104, so sizeof 0x108 [V extent + align 8].
// Field meanings are [-]: no instruction or string names them.

namespace mce::framebuilder {

struct RenderLightTag3Description {
    struct Slice {
        void* mObject;        // +0x00 [V] slice pointer read (slice k: `0x66410fd  mov r8,[rsi+0x38]` for k=0)
        void* mControlBlock;  // +0x08 [V] slice control block (`0x66410f4  mov rdx,[rsi+0x40]` k=0;
                              // `0x66410fd  lock inc dword ptr [rdx+0xC]` = weak-count inc [V])
        float mVec[4];        // +0x10 [V] `0x6641117  movups xmm5,[rsi+0x48]` k=0
    };
    float  mValue00;          // +0x00 [V] `0x664127e  movss xmm5,[rsi]`
    uint8_t mPad04[4];
    float  mValue08[2];       // +0x08 [V] `0x6641287  movsd xmm7,[rsi+8]`
    float  mValue10;          // +0x10 [V] `0x6641279  movss xmm4,[rsi+0x10]`
    float  mValue14[2];       // +0x14 [V] `0x66410a0  movsd xmm0,[rsi+0x14]`
    float  mValue1C;          // +0x1C [V] `0x66410c0  movss xmm0,[rsi+0x1C]`
    uint8_t mByte20;          // +0x20 [V] `0x6641282  movzx r8d,byte ptr [rsi+0x20]`
    uint8_t mPad21[7];
    uint64_t mValue28;        // +0x28 [V] `0x66410e2  mov rcx,[rsi+0x28]`
    uint16_t mValue30;        // +0x30 [V] `0x66410de  movzx eax,word ptr [rsi+0x30]`
    uint8_t mPad32[6];
    Slice mSlices[6];         // +0x38 .. +0x117 [V] (six slices, stride 0x20)
    uint32_t mValueF8[2];     // +0xF8 [V] `0x66410a5  movsd xmm3,[rsi+0xF8]`
    float  mValue100;         // +0x100 [V] `0x66410c9  movss xmm5,[rsi+0x100]`
    uint8_t mPad104[4];
};
static_assert(sizeof(RenderLightTag3Description) == 0x108);
static_assert(sizeof(RenderLightTag3Description::Slice) == 0x20);
static_assert(offsetof(RenderLightTag3Description, mValue28) == 0x28);
static_assert(offsetof(RenderLightTag3Description, mValue30) == 0x30);
static_assert(offsetof(RenderLightTag3Description, mSlices) == 0x38);
static_assert(offsetof(RenderLightTag3Description, mValueF8) == 0xF8);
static_assert(offsetof(RenderLightTag3Description, mValue100) == 0x100);

} // namespace mce::framebuilder
