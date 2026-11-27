#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_5a4c4f0, reverse-engineered from the disassembly
// of [0x5a4c4f0, 0x5a4c5f8), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Slot object (a0 in RCX/RSI, a1 in RDI) — 0x2C bytes, all accesses covered
#pragma pack(push, 1)
struct Slot {
    void** vtable;             // +0x00: vtable pointer (R/W)
    void* object;              // +0x08: RefCountedObject* (R/W)
    void* field10;             // +0x10: auxiliary pointer (R/W)
    std::uint64_t data18[2];   // +0x18: 16-byte data block (R/W, movups)
    std::uint32_t field28;     // +0x28: state/refcount (R/W)
};
#pragma pack(pop)

// Global manager object at data_1233e1b0 (0x1233E1B0) — only vtable accessed
#pragma pack(push, 1)
struct GlobalManager {
    void** vtable;             // +0x00: vtable pointer (R)
};
#pragma pack(pop)

// VTable slot 2 (+0x10) signature: returns uint32_t, takes (GlobalManager*, uint32_t)
// Called via boundary thunk sub_eea6040 (data_f99ffa0) with RAX preloaded.
using GlobalVTable2Fn = std::uint32_t (*)(GlobalManager*, std::uint32_t);

// VTable slot 0 signature: void (RefCountedObject*) — destructor/release
using RefCountedVTable0Fn = void (*)(void*);

// Static asserts for Slot
static_assert(offsetof(Slot, vtable) == 0x00, "Slot::vtable offset");
static_assert(offsetof(Slot, object) == 0x08, "Slot::object offset");
static_assert(offsetof(Slot, field10) == 0x10, "Slot::field10 offset");
static_assert(offsetof(Slot, data18) == 0x18, "Slot::data18 offset");
static_assert(offsetof(Slot, field28) == 0x28, "Slot::field28 offset");
static_assert(sizeof(Slot) >= 0x2C, "Slot sizeof lower bound");

// Static asserts for GlobalManager
static_assert(offsetof(GlobalManager, vtable) == 0x00, "GlobalManager::vtable offset");
static_assert(sizeof(GlobalManager) >= 0x08, "GlobalManager sizeof lower bound");

// Absolute address of the global manager pointer (data_1233e1b0)
inline GlobalManager* get_global_manager() {
    return *reinterpret_cast<GlobalManager**>(0x1233E1B0);
}

// Scaffold per-base-register structs (kept for liftcheck layout assertions)
// These mirror the actual memory layouts accessed through each register base.

// Base RCX: initially a0 (Slot*), then global manager (GlobalManager*)
// Offsets accessed: +0x0 (vtable), +0x8 (object), +0x10 (field10), +0x17/0x18 (data18), +0x28 (field28)
// and when RCX=global: +0x0 (vtable), +0x10 (vtable[2])
#pragma pack(push, 1)
struct sub_5a4c4f0_rcx {
    void** f0;                 // +0x00: vtable pointer (R/W)
    void* f8[2];               // +0x08: object, field10 (R/W)
    std::uint64_t f18[2];      // +0x18: data18 (R/W)
    std::uint32_t f28;         // +0x28: field28 (R/W)
};
#pragma pack(pop)

// Base RDX: a1 (Slot*) — offsets +0x0, +0x8, +0x10, +0x18, +0x28
#pragma pack(push, 1)
struct sub_5a4c4f0_rdx {
    void** f0;                 // +0x00: vtable pointer (R/W)
    void* f8;                  // +0x08: object (R/W)
    void* f10;                 // +0x10: field10 (R/W)
    std::uint64_t f18[2];      // +0x18: data18 (R/W)
    std::uint32_t f28;         // +0x28: field28 (R/W)
};
#pragma pack(pop)

// Base RAX: used as &a0+0x8 (reads f8[0]), &a0+0x18 (writes f18, f28), and global vtable
#pragma pack(push, 1)
struct sub_5a4c4f0_rax {
    void* f0[2];               // +0x00: when RAX=&a0+8, reads object; when RAX=vtable, reads vtable[0],vtable[2]
    void* f10;                 // +0x10: when RAX=&a0+8, field10; when RAX=&a0+18, field28
};
#pragma pack(pop)

// Base RSP: stack frame, only +0x30 accessed
#pragma pack(push, 1)
struct sub_5a4c4f0_rsp {
    std::uint8_t pad0x00[0x30];
    std::uint8_t f30;          // +0x30: stack cookie / frame marker
};
#pragma pack(pop)

// Static asserts for scaffold per-base-register structs
static_assert(offsetof(sub_5a4c4f0_rcx, f0) == 0x0, "sub_0x5a4c4f0 rcx+0x0 field");
static_assert(offsetof(sub_5a4c4f0_rcx, f8) == 0x8, "sub_0x5a4c4f0 rcx+0x8 field");
static_assert(offsetof(sub_5a4c4f0_rcx, f18) == 0x18, "sub_0x5a4c4f0 rcx+0x18 field");
static_assert(offsetof(sub_5a4c4f0_rcx, f28) == 0x28, "sub_0x5a4c4f0 rcx+0x28 field");
static_assert(sizeof(sub_5a4c4f0_rcx) >= 0x2c, "sub_0x5a4c4f0 rcx sizeof lower bound");

static_assert(offsetof(sub_5a4c4f0_rdx, f0) == 0x0, "sub_0x5a4c4f0 rdx+0x0 field");
static_assert(offsetof(sub_5a4c4f0_rdx, f8) == 0x8, "sub_0x5a4c4f0 rdx+0x8 field");
static_assert(offsetof(sub_5a4c4f0_rdx, f10) == 0x10, "sub_0x5a4c4f0 rdx+0x10 field");
static_assert(offsetof(sub_5a4c4f0_rdx, f18) == 0x18, "sub_0x5a4c4f0 rdx+0x18 field");
static_assert(offsetof(sub_5a4c4f0_rdx, f28) == 0x28, "sub_0x5a4c4f0 rdx+0x28 field");
static_assert(sizeof(sub_5a4c4f0_rdx) >= 0x2c, "sub_0x5a4c4f0 rdx sizeof lower bound");

static_assert(offsetof(sub_5a4c4f0_rax, f0) == 0x0, "sub_0x5a4c4f0 rax+0x0 field");
static_assert(offsetof(sub_5a4c4f0_rax, f10) == 0x10, "sub_0x5a4c4f0 rax+0x10 field");
static_assert(sizeof(sub_5a4c4f0_rax) >= 0x18, "sub_0x5a4c4f0 rax sizeof lower bound");

static_assert(offsetof(sub_5a4c4f0_rsp, f30) == 0x30, "sub_0x5a4c4f0 rsp+0x30 field");
static_assert(sizeof(sub_5a4c4f0_rsp) >= 0x31, "sub_0x5a4c4f0 rsp sizeof lower bound");

// Function signature: x64 Microsoft ABI, RCX = a0, RDX = a1, returns a0 in RAX
Slot* sub_5a4c4f0(Slot* a0, Slot* a1);

} // namespace native::helpers