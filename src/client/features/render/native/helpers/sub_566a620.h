#pragma once
#include <cstddef>
#include <cstdint>

namespace native {
void sub_e935700(std::uintptr_t a1, std::uintptr_t a2);
}

namespace native::helpers {

// Refcounted object pointed at by sub_566a620_state::mRefCountedA / mRefCountedB.
// Touched fields: vptr +0x00, strong +0x08 (lock dec on release), weak +0x0C
// (lock dec after destroy). Virtual slot 0 = destroy (run when strong reaches 0),
// slot 1 = dealloc (run when weak reaches 0); both are invoked through the
// CFG-thunk data slot [0xF99FFA0] = sub_eea6040 (`jmp rax`), so there is no
// static callee target.
struct RefCountedObject {
    void* vptr;                    // +0x00
    std::uint32_t strong;          // +0x08  lock dec on release
    std::uint32_t weak;            // +0x0C  lock dec after destroy
};

static_assert(offsetof(RefCountedObject, vptr) == 0x00, "566a620: refcounted vptr at +0x00");
static_assert(offsetof(RefCountedObject, strong) == 0x08, "566a620: refcounted strong at +0x08");
static_assert(offsetof(RefCountedObject, weak) == 0x0C, "566a620: refcounted weak at +0x0C");
static_assert(sizeof(RefCountedObject) == 0x10, "566a620: refcounted object size");

// Layout of the object passed in rcx (this), reverse-engineered from the
// disassembly of [0x566a620, 0x566a712). Only the offsets read or written are
// declared; everything between them is padding.
//
//   +0x08: refcounted object released second (mRefCountedB)
//   +0x18: refcounted object released first (mRefCountedA)
//   +0x28: heap buffer pointer (mData)
//   +0x38: heap buffer end pointer (mDataEnd); size = mDataEnd - mData
//   +0x40: flag byte (must be 1 to proceed)
struct sub_566a620_state {
    std::uint8_t mPad00[0x8];       // +0x00
    void* mRefCountedB;             // +0x08 refcounted object, released second
    std::uint8_t mPad10[0x8];       // +0x10
    void* mRefCountedA;             // +0x18 refcounted object, released first
    std::uint8_t mPad20[0x8];       // +0x20
    void* mData;                    // +0x28 heap buffer pointer
    std::uint8_t mPad30[0x8];       // +0x30
    std::uintptr_t mDataEnd;        // +0x38 heap buffer end pointer
    std::uint8_t mFlag;             // +0x40 flag byte
};

static_assert(offsetof(sub_566a620_state, mRefCountedB) == 0x08, "566a620: mRefCountedB at +0x08");
static_assert(offsetof(sub_566a620_state, mRefCountedA) == 0x18, "566a620: mRefCountedA at +0x18");
static_assert(offsetof(sub_566a620_state, mData) == 0x28, "566a620: mData at +0x28");
static_assert(offsetof(sub_566a620_state, mDataEnd) == 0x38, "566a620: mDataEnd at +0x38");
static_assert(offsetof(sub_566a620_state, mFlag) == 0x40, "566a620: mFlag at +0x40");
static_assert(sizeof(sub_566a620_state) >= 0x41, "566a620: state sizeof lower bound");

// sub_566a620(self = rcx) -> void, Minecraft Windows 1.26.62.01.
// Returns void: rax is dead at ret on all non-tail-call paths; the tail-call
// path transfers control to mRefCountedB->vptr[1](mRefCountedB) via the
// [0xF99FFA0] thunk and its return value is not observed by this function.
void sub_566a620(sub_566a620_state* self);

} // namespace native::helpers
