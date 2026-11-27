#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e935700 (0xe935700, size 0x5, docs/data/native_functions.tsv: class `lift`, depth 0)
// = `jmp 0x392960`, a tiny forwarder lifted by its own unit.
// Forward-declared here with its exact ABI signature (name sub_<rva>, namespace native) and
// called directly like any lifted function; not a boundary wrapper.
// The exe calls it with rcx = first u64 argument, rdx = second u64 argument; the return
// register is dead at the call sites of this unit (sub_392960 only reads RCX and ignores RDX).
void sub_e935700(std::uintptr_t a1, std::uintptr_t a2);

} // namespace native

namespace native::helpers {

// Layout of the object passed in rcx (this), reverse-engineered from the disassembly of
// [0x130ee0, 0x130fdb). Only the offsets this function reads or writes are declared;
// everything between them is padding. Verified against the disassembly:
//
//   +0x00: heap buffer start pointer (read: 0x130efb, 0x130f65; written: 0x130f98)
//   +0x08: heap buffer end pointer   (read: 0x130f07; written: 0x130fa2)
//   +0x10: heap buffer cap/end ptr   (read: 0x130f68; written: 0x130fad)
//
// The buffer holds 0x10-stride elements; each element's +0x08 is a pointer to a
// refcounted object (see sub_130ee0_refcounted below).
struct sub_130ee0_state {
    std::uintptr_t f0;    // +0x00  heap buffer start pointer
    std::uintptr_t f8;    // +0x08  heap buffer end pointer
    std::uintptr_t f10;   // +0x10  heap buffer cap/end pointer
};                       // sizeof == 0x18

static_assert(offsetof(sub_130ee0_state, f0) == 0x00, "130ee0: state f0 at +0x00");
static_assert(offsetof(sub_130ee0_state, f8) == 0x08, "130ee0: state f8 at +0x08");
static_assert(offsetof(sub_130ee0_state, f10) == 0x10, "130ee0: state f10 at +0x10");
static_assert(sizeof(sub_130ee0_state) == 0x18, "130ee0: state size");

// Layout of the refcounted object pointed at by each 0x10-stride element's +0x08.
// Touched fields: vptr +0x00, strong +0x08 (lock dec on release), weak +0x0C (lock dec
// after destroy). Virtual slot 0 = destroy (run when strong reaches 0), slot 1 = dealloc
// (run when weak reaches 0); both are invoked through the CFG-thunk data slot
// [0xF99FFA0] (`jmp rax`: rax holds the vtable entry at call time), so there is no static
// callee target.
struct sub_130ee0_refcounted {
    void* vptr;                    // +0x00
    std::uint32_t strong;          // +0x08  lock dec on release
    std::uint32_t weak;            // +0x0C  lock dec after destroy
};

static_assert(offsetof(sub_130ee0_refcounted, vptr) == 0x00, "130ee0: refcounted vptr at +0x00");
static_assert(offsetof(sub_130ee0_refcounted, strong) == 0x08, "130ee0: refcounted strong at +0x08");
static_assert(offsetof(sub_130ee0_refcounted, weak) == 0x0c, "130ee0: refcounted weak at +0x0c");
static_assert(sizeof(sub_130ee0_refcounted) == 0x10, "130ee0: refcounted object size");

// sub_130ee0(sub_130ee0_state* self = rcx, std::uintptr_t arg2 = rdx,
//            std::uintptr_t arg3 = r8, std::uintptr_t arg4 = r9) -> void.
// Returns void: no instruction of [0x130ee0, 0x130fdb) writes rax with a defined value,
// so the return register is dead at ret (confirmed by rdis: rax = '?' at every exit).
void sub_130ee0(sub_130ee0_state* self, std::uintptr_t arg2, std::uintptr_t arg3, std::uintptr_t arg4);

} // namespace native::helpers
