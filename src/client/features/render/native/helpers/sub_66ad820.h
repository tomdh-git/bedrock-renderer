#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e935700 (0xe935700): lift-set callee, a tail jump to sub_392960. Forward-declared here and
// called directly through its native symbol (brief rule 66: a lift callee is never called through
// a boundary wrapper). ABI recovered from sub_392960's disassembly: the single argument arrives
// in RCX (0x392972 mov rdx,rcx), the result leaves in RAX; sub_392960 ignores RDX and reads no
// stack argument. docs/data/native_functions.tsv: 0x392960 size 0x35, boundary row class 'lift'.
void* sub_e935700(void* a0);

} // namespace native

namespace native::helpers {

// Calls 0x66ad88d/0x66ad8a3/0x66ad8d7 go through data slot [0xF99FFA0] (pack: [data_f99ffa0] =
// sub_eea6040, vendor thunk); they are emitted as slot reads at call time, so sub_eea6040 itself
// is not declared here.

// Layout of the object passed in rcx (this), reverse-engineered from the disassembly of
// [0x66ad820, 0x66ad946), Minecraft Windows 1.26.62.01. Only the offsets read or written by the
// function are declared; everything between them is padding. #pragma pack(1) keeps every declared
// field at its observed offset so offsetof() matches; sizeof is a lower bound, not an exact size.
//
//   +0x08 mBlock08  heap-buffer pointer (freed via sub_e935700; zeroed with mBlock10/mBlock18)
//   +0x10 mBlock10  written by the 16-byte zero store at +0x08
//   +0x18 mBlock18  heap-buffer end pointer; size = mBlock18 - mBlock08; zeroed
//   +0x28 mBlock28  refcounted-object pointer (released)
//   +0x38 mBlock38  refcounted-object pointer (released)
//   +0x48 mBlock48  heap-buffer pointer (freed via sub_e935700; zeroed with mBlock50/mBlock58)
//   +0x50 mBlock50  written by the 16-byte zero store at +0x48
//   +0x58 mBlock58  heap-buffer end pointer; size = mBlock58 - mBlock48; zeroed
//
// mBlock48/mBlock58 and mBlock08/mBlock18 are independent heap buffers. mBlock28/mBlock38 point
// at refcounted objects (see sub_66ad820_refcounted below).
#pragma pack(push, 1)
struct sub_66ad820_state {
    std::uint8_t pad0x00[0x8];     // +0x00..+0x07 (no observed access)
    void* mBlock08;                // +0x08  R: 0x66ad8dd  W: 0x66ad91a (movups 16 bytes)
    std::uintptr_t mBlock10;       // +0x10  W: 0x66ad91a (movups 16 bytes)
    std::uintptr_t mBlock18;       // +0x18  R: 0x66ad8e6  W: 0x66ad91d
    std::uint8_t pad0x20[0x8];     // +0x20..+0x27 (no observed access)
    void* mBlock28;                // +0x28  R: 0x66ad8a9
    std::uint8_t pad0x30[0x8];     // +0x30..+0x37 (no observed access)
    void* mBlock38;                // +0x38  R: 0x66ad875
    std::uint8_t pad0x40[0x8];     // +0x40..+0x47 (no observed access)
    void* mBlock48;                // +0x48  R: 0x66ad829 (mov+test), 0x66ad85e (lea)  W: 0x66ad86a
    std::uintptr_t mBlock50;       // +0x50  W: 0x66ad86a (movups 16 bytes)
    std::uintptr_t mBlock58;       // +0x58  R: 0x66ad832  W: 0x66ad86d
};
#pragma pack(pop)

static_assert(offsetof(sub_66ad820_state, mBlock08) == 0x08, "sub_66ad820 mBlock08 at +0x08");
static_assert(offsetof(sub_66ad820_state, mBlock10) == 0x10, "sub_66ad820 mBlock10 at +0x10");
static_assert(offsetof(sub_66ad820_state, mBlock18) == 0x18, "sub_66ad820 mBlock18 at +0x18");
static_assert(offsetof(sub_66ad820_state, mBlock28) == 0x28, "sub_66ad820 mBlock28 at +0x28");
static_assert(offsetof(sub_66ad820_state, mBlock38) == 0x38, "sub_66ad820 mBlock38 at +0x38");
static_assert(offsetof(sub_66ad820_state, mBlock48) == 0x48, "sub_66ad820 mBlock48 at +0x48");
static_assert(offsetof(sub_66ad820_state, mBlock50) == 0x50, "sub_66ad820 mBlock50 at +0x50");
static_assert(offsetof(sub_66ad820_state, mBlock58) == 0x58, "sub_66ad820 mBlock58 at +0x58");
static_assert(sizeof(sub_66ad820_state) >= 0x60, "sub_66ad820 sizeof lower bound");

// Refcounted object pointed at by mBlock28/mBlock38.
// +0x00 vptr (dead reads before the thunk calls), +0x08 strong (lock dec), +0x0C weak (lock dec).
// When strong reaches 0, slot 0 is invoked through data slot [0xF99FFA0]; when weak then reaches
// 0, slot 1 is invoked through the same slot. [data_f99ffa0] = sub_eea6040 (vendor thunk).
#pragma pack(push, 1)
struct sub_66ad820_refcounted {
    void* vptr;                    // +0x00  R: 0x66ad884/0x66ad899/0x66ad8b8/0x66ad8cd (dead)
    std::uint32_t strong;          // +0x08  RW: 0x66ad87e/0x66ad8b2 (lock dec)
    std::uint32_t weak;            // +0x0C  RW: 0x66ad893/0x66ad8c7 (lock dec)
};
#pragma pack(pop)

static_assert(offsetof(sub_66ad820_refcounted, vptr) == 0x00, "sub_66ad820 refcounted vptr at +0x00");
static_assert(offsetof(sub_66ad820_refcounted, strong) == 0x08, "sub_66ad820 refcounted strong at +0x08");
static_assert(offsetof(sub_66ad820_refcounted, weak) == 0x0C, "sub_66ad820 refcounted weak at +0x0C");
static_assert(sizeof(sub_66ad820_refcounted) == 0x10, "sub_66ad820 refcounted sizeof");

// Signature (x64 Microsoft ABI): rcx = self (0x66ad826 mov rsi,rcx). Returns void: rax is written
// only by dead vtable reads (0x66ad884/0x66ad887/0x66ad899/0x66ad8cd) and by sub_e935700, whose
// result is never read, so rax is dead at ret (0x66ad92b). No null guards or SEH beyond the
// original: the validation-failure path calls data slot [0xF9A8C78] and never returns.
void sub_66ad820(sub_66ad820_state* self);

} // namespace native::helpers
