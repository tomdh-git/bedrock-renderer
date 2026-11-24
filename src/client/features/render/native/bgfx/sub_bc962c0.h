#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Refcounted object referenced at this+0x28 and this+0x68, touched by sub_bc962c0.
// Layout observed in the disassembly of [0xbc962c0, 0xbc963ef):
//   obj+0x00  vtable pointer       (read for virtual slots 0/1/4 via jmp-rax thunk [0xF99FFA0])
//   obj+0x08  strong refcount u32  (lock dec dword)
//   obj+0x0C  weak   refcount u32  (lock dec dword)
//   vtable[0] = destructor, vtable[1] = deallocator (called when the corresponding count hits 0)
//   vtable[4]   = release-style entry called on the object at +0x68
// Layout beyond +0x10 is unknown and not touched by this function.
struct RefObj {
    void* vptr;               // +0x00
    std::uint32_t strong;     // +0x08
    std::uint32_t weak;       // +0x0C
};
static_assert(offsetof(RefObj, vptr) == 0x00, "sub_bc962c0 reads obj+0x00 as vtable pointer");
static_assert(offsetof(RefObj, strong) == 0x08, "sub_bc962c0 lock-dec obj+0x08 (strong refcount)");
static_assert(offsetof(RefObj, weak) == 0x0C, "sub_bc962c0 lock-dec obj+0x0C (weak refcount)");

// Layout of the object passed in rcx ("this"), reverse-engineered from the
// disassembly of [0xbc962c0, 0xbc963ef), Minecraft Windows 1.26.62.01.
// Two inline buffers with 16-byte small-buffer storage plus a size/capacity pair:
//   buffer A: data byte[16] @+0x00, size u64 @+0x10, capacity u64 @+0x18
//   buffer B: data byte[16] @+0x78, size u64 @+0x88, capacity u64 @+0x90
// plus two refcounted object pointers @+0x28 (object B) and @+0x68 (object C).
// Only offsets the function reads or writes are declared; the rest is padding.
struct sub_bc962c0_state {
    void* field_0x00;               // +0x00  buffer A data pointer (heap); low byte written 0
    uint8_t pad_0x08[8];            // +0x08  untouched by this function
    std::uint64_t field_0x10;       // +0x10  buffer A size (written 0)
    std::uint64_t field_0x18;       // +0x18  buffer A capacity (read; written 0xF)
    RefObj* field_0x28;             // +0x28  refcounted object B (released via vtable[0],[1]);
                                    //        NOT cleared after release (dangling pointer left)
    uint8_t pad_0x30[0x38];         // +0x30..+0x67 untouched (&self+0x30 appears only in a
                                    //        dead comparator whose result is never read)
    RefObj* field_0x68;             // +0x68  refcounted object C (vtable[4] called); cleared to 0
    void* field_0x78;               // +0x78  buffer B data pointer (heap); low byte written 0
    std::uint64_t field_0x88;       // +0x88  buffer B size (written 0)
    std::uint64_t field_0x90;       // +0x90  buffer B capacity (read; written 0xF)
};                                  // sizeof == 0x98

static_assert(offsetof(sub_bc962c0_state, field_0x00) == 0x00, "sub_bc962c0 reads/writes this+0x00 (buffer A data)");
static_assert(offsetof(sub_bc962c0_state, field_0x10) == 0x10, "sub_bc962c0 writes this+0x10 (buffer A size)");
static_assert(offsetof(sub_bc962c0_state, field_0x18) == 0x18, "sub_bc962c0 reads/writes this+0x18 (buffer A capacity)");
static_assert(offsetof(sub_bc962c0_state, field_0x28) == 0x28, "sub_bc962c0 reads this+0x28 (object B pointer)");
static_assert(offsetof(sub_bc962c0_state, field_0x68) == 0x68, "sub_bc962c0 reads/writes this+0x68 (object C pointer)");
static_assert(offsetof(sub_bc962c0_state, field_0x78) == 0x78, "sub_bc962c0 reads/writes this+0x78 (buffer B data)");
static_assert(offsetof(sub_bc962c0_state, field_0x88) == 0x88, "sub_bc962c0 writes this+0x88 (buffer B size)");
static_assert(offsetof(sub_bc962c0_state, field_0x90) == 0x90, "sub_bc962c0 reads/writes this+0x90 (buffer B capacity)");
static_assert(sizeof(sub_bc962c0_state) == 0x98, "sub_bc962c0 object size");

// 0xe935700: lift-set callee (class lift in docs/data/native_boundary.tsv).
// 5-byte forwarder: 0xe935700  jmp 0x392960  [V: rdis dis 0xe935700].
// Called here with rcx = pointer argument, rdx = size argument; only rcx is observed
// meaningful by the callee (sub_392960 moves rcx->rdx, then tests the original rcx).
// Forward-declared with the exact arguments the caller sets; native symbol sub_e935700.
extern "C" uintptr_t sub_e935700(uint64_t a0, uint64_t a1);

// sub_bc962c0(sub_bc962c0_state* self = rcx) -> void.
// Frame-graph builder (1.26.62.01): tears down two inline buffers and two refcounted
// objects, then resets both buffers to small empty state (size 0, capacity 0xF).
// See docs/functions/bc962c0.md for the full phase-by-phase reversal.
void sub_bc962c0(sub_bc962c0_state* self);

} // namespace native::bgfx
