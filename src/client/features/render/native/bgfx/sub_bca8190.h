#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// sub_e935700 (0xE935700): lift-classified callee (docs/data/native_boundary.tsv: lift).
// It is a 5-byte tail-jump thunk to sub_392960; the target reads only its rcx argument, so the ABI
// signature is one pointer argument and a void return. Forward-declared here per the lift rule for
// lift-classified callees (rule 66 of docs/OPENCODE_BRIEF.md); it is lifted by its own unit and
// linked at the milestone gate.
void sub_e935700(void* ptr);

} // namespace native

namespace native::bgfx {

// Layout of the object passed in rcx to sub_0xbca8190 ("frame-graph builder", VV).
// Every offset below is [V] from the disassembly of [0xbca8190, 0xbca82c5).
// Offsets 0x00/0x80 are SSO slot overlays: a heap pointer when the matching capacity field is >= 0x10,
// otherwise inline bytes; the binary reads them as pointers and also writes the first inline byte.
struct VvFrameGraphBuilderState {
    union {                              // +0x00  slot A: heap pointer, or inline SSO bytes
        uint64_t mPtrA;
        uint8_t mInlineA[0x10];
    };
    uint64_t mSizeA;                     // +0x10
    uint64_t mCapA;                      // +0x18  >= 0x10 => slot A is heap-allocated
    uint8_t mPad20[0x8];                 // +0x20
    void* mRefObject;                    // +0x28  ref-counted object: released here, the field itself is not cleared
    uint8_t mPad30[0x8];                 // +0x30
    uint8_t mInlineObject[0x38];         // +0x38  inline object; its address is compared against mObject
    void* mObject;                       // +0x70  released object; may be &mInlineObject
    union {                              // +0x80  slot B: heap pointer, or inline SSO bytes
        uint64_t mPtrB;
        uint8_t mInlineB[0x10];
    };
    uint64_t mSizeB;                     // +0x90
    uint64_t mCapB;                      // +0x98  >= 0x10 => slot B is heap-allocated
};
static_assert(offsetof(VvFrameGraphBuilderState, mPtrA) == 0x00, "sub_bca8190 reads/writes slot A pointer at +0x00");
static_assert(offsetof(VvFrameGraphBuilderState, mSizeA) == 0x10, "sub_bca8190 writes +0x10");
static_assert(offsetof(VvFrameGraphBuilderState, mCapA) == 0x18, "sub_bca8190 branches on +0x18 and writes +0x18");
static_assert(offsetof(VvFrameGraphBuilderState, mRefObject) == 0x28, "sub_bca8190 reads/writes +0x28");
static_assert(offsetof(VvFrameGraphBuilderState, mInlineObject) == 0x38, "sub_bca8190 takes the address of +0x38");
static_assert(offsetof(VvFrameGraphBuilderState, mObject) == 0x70, "sub_bca8190 reads/writes +0x70");
static_assert(offsetof(VvFrameGraphBuilderState, mPtrB) == 0x80, "sub_bca8190 reads/writes slot B pointer at +0x80");
static_assert(offsetof(VvFrameGraphBuilderState, mSizeB) == 0x90, "sub_bca8190 writes +0x90");
static_assert(offsetof(VvFrameGraphBuilderState, mCapB) == 0x98, "sub_bca8190 branches on +0x98 and writes +0x98");
static_assert(sizeof(VvFrameGraphBuilderState) >= 0xA0, "sub_bca8190 touches up to +0x9F");

// sub_bca8190(void* self = rcx) -> void. Resets both SSO slots and releases the two held objects.
void sub_bca8190(VvFrameGraphBuilderState* self);

} // namespace native::bgfx
