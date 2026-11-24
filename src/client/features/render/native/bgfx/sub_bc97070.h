#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// 0xe935700 (size 0x5, docs/data/native_functions.tsv: class `lift`, depth 0) = `jmp 0x392960`,
// a tiny forwarder lifted by its own unit. Forward-declared here with its exact ABI signature
// (name sub_<rva>, namespace native) and called directly like any lifted function; not a
// boundary wrapper (docs/OPENCODE_BRIEF.md rule 66). The exe calls it with rcx = first u64
// argument, rdx = second; the return register is dead at the call sites of this unit.
void sub_e935700(std::uintptr_t a1, std::uintptr_t a2);

} // namespace native

namespace native::bgfx {

// Layout of the frame-graph builder object passed in rcx (this), reverse-engineered from the
// disassembly of [0xbc97070, 0xbc971a5). Only the offsets sub_bc97070 reads or writes are
// declared; everything between them is padding. Verified against the disassembly:
//
//   string 1 at +0x00: data pointer +0x00, size +0x10, capacity +0x18
//   refcounted object pointer +0x30; interface pointer +0x70
//   string 2 at +0x80: data pointer +0x80, size +0x90, capacity +0x98
//
// Each string is heap-allocated when its capacity >= 0x10 (SSO otherwise; the inline buffer
// starts at the data-pointer field itself).
struct VvFrameGraphBuilder {
    std::uintptr_t mBlock00;          // +0x00  string 1: heap pointer or inline-buffer start
    std::uint8_t mPad08[0x8];         // +0x08
    std::uintptr_t mBlock10;          // +0x10  string 1: size
    std::uintptr_t mBlock18;          // +0x18  string 1: capacity
    std::uint8_t mPad20[0x10];        // +0x20
    std::uintptr_t mBlock30;          // +0x30  pointer to the refcounted object
    std::uint8_t mPad38[0x38];        // +0x38  compared as &self + 0x38, never dereferenced
    std::uintptr_t mBlock70;          // +0x70  interface pointer, released through vtable slot 4
    std::uint8_t mPad78[0x8];         // +0x78
    std::uintptr_t mBlock80;          // +0x80  string 2: heap pointer or inline-buffer start
    std::uint8_t mPad88[0x8];         // 0x88
    std::uintptr_t mBlock90;          // +0x90  string 2: size
    std::uintptr_t mBlock98;          // +0x98  string 2: capacity
};                                    // sizeof == 0xA0

static_assert(offsetof(VvFrameGraphBuilder, mBlock00) == 0x00, "bc97070: string 1 data pointer at +0x00");
static_assert(offsetof(VvFrameGraphBuilder, mBlock10) == 0x10, "bc97070: string 1 size at +0x10");
static_assert(offsetof(VvFrameGraphBuilder, mBlock18) == 0x18, "bc97070: string 1 capacity at +0x18");
static_assert(offsetof(VvFrameGraphBuilder, mBlock30) == 0x30, "bc97070: refcounted object pointer at +0x30");
static_assert(offsetof(VvFrameGraphBuilder, mBlock70) == 0x70, "bc97070: interface pointer at +0x70");
static_assert(offsetof(VvFrameGraphBuilder, mBlock80) == 0x80, "bc97070: string 2 data pointer at +0x80");
static_assert(offsetof(VvFrameGraphBuilder, mBlock90) == 0x90, "bc97070: string 2 size at +0x90");
static_assert(offsetof(VvFrameGraphBuilder, mBlock98) == 0x98, "bc97070: string 2 capacity at +0x98");
static_assert(sizeof(VvFrameGraphBuilder) == 0xA0, "bc97070: object size");

// The refcounted object pointed at by VvFrameGraphBuilder::mBlock30. Touched fields: vptr +0x00,
// strong +0x08 (lock dec on release), weak +0x0C (lock dec after destroy). Virtual slot 0 =
// destroy (run when strong reaches 0), slot 1 = dealloc (run when weak reaches 0); both are
// invoked through the CFG-thunk data slot [0xF99FFA0] = sub_eea6040 (`jmp rax`: rax holds the
// vtable entry at call time), so there is no static callee target.
struct Bc97070RefCounted {
    void* vptr;                    // +0x00
    std::uint32_t strong;          // +0x08  lock dec on release
    std::uint32_t weak;            // +0x0C  lock dec after destroy
};

static_assert(offsetof(Bc97070RefCounted, vptr) == 0x00, "bc97070: refcounted vptr at +0x00");
static_assert(offsetof(Bc97070RefCounted, strong) == 0x08, "bc97070: refcounted strong at +0x08");
static_assert(offsetof(Bc97070RefCounted, weak) == 0x0C, "bc97070: refcounted weak at +0x0C");
static_assert(sizeof(Bc97070RefCounted) == 0x10, "bc97070: refcounted object size");

// sub_bc97070(VvFrameGraphBuilder* self = rcx) -> void, Minecraft Windows 1.26.62.01.
// Returns void: no instruction of the range writes rax with a defined value, so the return
// register is dead at ret (rdis sum: rax = '?' at 0xbc9718a).
void sub_bc97070(VvFrameGraphBuilder* self);

} // namespace native::bgfx
