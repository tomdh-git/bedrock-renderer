#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe81b3b0 (size 0x118, 1.26.62.01).
// This is RendererContextD3D12 base slot 7 ("set/replace the current frame id"):
// it queries an id from a sub-object, stores it at self+0x30, and then walks a
// 0x88-stride array of per-pass records [self+0x00, self+0x08) notifying each one
// either with the fresh id (when id != -1 and id-1 < count) or with -1 (when id == -1).
// Every offset below is an instruction [reg+off] seen in the listing [V].

// One element of the [begin, end) array walked by both loops. Stride is 0x88.
//   +0x38  void* notify   ([p+0x38]); when non-null it receives one virtual call.
struct E81b3b0Element {
    std::uint8_t pad0[0x38];
    void*        notify;        // +0x38
    std::uint8_t pad1[0x88 - 0x40];
};
static_assert(sizeof(E81b3b0Element) == 0x88, "e81b3b0: element stride is 0x88 (add r14/rbx,0x88)");
static_assert(offsetof(E81b3b0Element, notify) == 0x38, "e81b3b0: notify at +0x38");

// The context object (self / rcx). Only the fields 0xe81b3b0 touches are named:
//   +0x00  void* begin    self->begin   (mov r14/rbx,[rdi])
//   +0x08  void* end      self->end     (mov r15/r14,[rdi+8])
//   +0x18  void* idSource self->obj    (mov rcx,[rcx+0x18]) -> vtable[0x40] returns the id
//   +0x28  u64   count    self->count   (cmp rax,[rdi+0x28])
//   +0x30  u64   id       self->id      (mov [rdi+0x30],rax, written; mov rax,[rdi+0x30], read in loop A)
struct E81b3b0Context {
    void*        begin;        // +0x00
    void*        end;          // +0x08
    std::uint8_t pad0[0x18 - 0x10]; // +0x10..0x18
    void*        idSource;     // +0x18
    std::uint8_t pad1[0x28 - 0x20]; // +0x20..0x28
    std::uint64_t count;       // +0x28
    std::uint64_t id;          // +0x30
};
static_assert(offsetof(E81b3b0Context, begin) == 0x00, "e81b3b0: begin at +0x00");
static_assert(offsetof(E81b3b0Context, end) == 0x08, "e81b3b0: end at +0x08");
static_assert(offsetof(E81b3b0Context, idSource) == 0x18, "e81b3b0: idSource at +0x18");
static_assert(offsetof(E81b3b0Context, count) == 0x28, "e81b3b0: count at +0x28");
static_assert(offsetof(E81b3b0Context, id) == 0x30, "e81b3b0: id at +0x30");
static_assert(sizeof(E81b3b0Context) == 0x38, "e81b3b0: context footprint touched up to +0x38");

// Read-only data / globals referenced by the function [V].
static constexpr std::uintptr_t kGblCookie     = 0x1230A0C0u; // mov rax,[0x1230A0C0]  (/GS stack cookie)
static constexpr std::uintptr_t kGuardSlot     = 0xF99FFA0u;  // call qword ptr [0xF99FFA0] (jmp rax thunk sub_eea6040)

// vtable byte offsets read before each guarded call (slot index = offset / 8) [V].
static constexpr std::uintptr_t kVslotGetId     = 0x40u; // 0xe81b3d4 mov rax,[rax+0x40]  -> slot 8 (returns the id)
static constexpr std::uintptr_t kVslotNotifyOne = 0x10u; // 0xe81b429/0xe81b475 mov rax,[rax+0x10] -> slot 2 (per-element notify)
static_assert(kVslotGetId     / 8 == 0x08u, "e81b3b0: vtable slot 0x40 = index 8");
static_assert(kVslotNotifyOne / 8 == 0x02u, "e81b3b0: vtable slot 0x10 = index 2");

// x64 Microsoft ABI: rcx = self (context). Return: bool = (id != -1) (setne al). [V]
extern "C" bool sub_e81b3b0(void* self);

} // namespace native