#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the out object passed in RCX (a0) to sub_67c07e0. Only offsets the
// function touches are declared; the rest is padding. Reverse-engineered from
// the disassembly of [0x67c07e0, 0x67c08cd), Minecraft Windows 1.26.62.01.
//   W a0+0x0 = a1 (0x67c0887)
//   W a0+0x8 = allocated record (0x67c088a)
struct Slot17Out {
    void* field0;   // +0x0: written with a1
    void* field8;   // +0x8: written with the allocated record pointer
};

// Layout of the refcounted object passed in R8 (a2) to sub_67c07e0.
//   R a2+0x0  -> record+0x10 (0x67c0807)
//   R a2+0x8  -> record+0x18 (0x67c080e); zeroed at 0x67c0816 so the later
//                release test at 0x67c0892 always sees 0 (release block dead)
//   R a2+0x10 -> record+0x20 (0x67c081e)
//   W a2+0x0..0xF = 0 (0x67c0816)
struct Slot17RefCounted {
    void* field0;          // +0x0
    void* field8;          // +0x8
    void* field10;         // +0x10
    std::uint32_t refcount;  // +0xC (declared for layout; release block is dead so not read)
    std::uint8_t pad0x10[0x20 - 0x10];
};

// Layout of the 0x30-byte record allocated by sub_67c07e0.
//   W rec+0x0  = [0xF2BE950]  (0x67c0874)
//   W rec+0x8  = 0x100000001  (0x67c0869)
//   W rec+0x10 = a2+0x0       (0x67c0877)
//   W rec+0x18 = a2+0x8       (0x67c087b)
//   W rec+0x20 = a2+0x10      (0x67c087f)
//   W rec+0x28 = a1           (0x67c0883)
struct Slot17Record {
    void* field0;          // +0x0: pointer read from rodata 0xF2BE950
    std::uint64_t field8;  // +0x8: 0x100000001
    void* field10;         // +0x10
    void* field18;         // +0x18
    void* field20;         // +0x20
    void* field28;         // +0x28
}; // sizeof == 0x30

static_assert(offsetof(Slot17Out, field0) == 0x00,
              "sub_67c07e0: a0+0x0 is written with a1");
static_assert(offsetof(Slot17Out, field8) == 0x08,
              "sub_67c07e0: a0+0x8 is written with the allocated record");
static_assert(offsetof(Slot17RefCounted, field0) == 0x00,
              "sub_67c07e0: a2+0x0 is read then written zero");
static_assert(offsetof(Slot17RefCounted, field8) == 0x08,
              "sub_67c07e0: a2+0x8 is read then written zero (release test sees 0)");
static_assert(offsetof(Slot17RefCounted, field10) == 0x10,
              "sub_67c07e0: a2+0x10 is read");
static_assert(offsetof(Slot17Record, field0) == 0x00,
              "sub_67c07e0: record+0x0 is written with [0xF2BE950]");
static_assert(offsetof(Slot17Record, field8) == 0x08,
              "sub_67c07e0: record+0x8 is written with 0x100000001");
static_assert(offsetof(Slot17Record, field10) == 0x10,
              "sub_67c07e0: record+0x10 is written with a2+0x0");
static_assert(offsetof(Slot17Record, field18) == 0x18,
              "sub_67c07e0: record+0x18 is written with a2+0x8");
static_assert(offsetof(Slot17Record, field20) == 0x20,
              "sub_67c07e0: record+0x20 is written with a2+0x10");
static_assert(offsetof(Slot17Record, field28) == 0x28,
              "sub_67c07e0: record+0x28 is written with a1");
static_assert(sizeof(Slot17Record) == 0x30,
              "sub_67c07e0: the allocation is exactly 0x30 bytes");

// Exact x64 Microsoft ABI mirror of the original: RCX = a0 (out), RDX = a1,
// R8 = a2, return RAX = a0.
void* sub_67c07e0(Slot17Out* a0, void* a1, Slot17RefCounted* a2);

} // namespace native
