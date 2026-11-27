#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// sub_45e860 state layouts, reverse-engineered from the disassembly of
// [0x45e860, 0x45e962), Minecraft Windows 1.26.62.01. Offsets and widths come
// straight from the instruction operands; field names are meaningful choices
// based on the observed access patterns. One struct per base register that is
// dereferenced. Packed so offsetof() matches the observed offsets exactly.
// sizeof is a lower bound (the real object may have compiler-inserted padding
// beyond the last observed field).

// Base register rcx/rbx = self pointer. Offset 0x10 is a node pointer (R at 0x45e8a9).
#pragma pack(push, 1)
struct sub_45e860_self {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    void* node;                   // +0x10: node object pointer (R at 0x45e8a9)
};
#pragma pack(pop)

// Base register rax = node pointer (self->node).
// +0x40 refcount: lock inc qword at 0x45e8b5 (atomic).
// +0x48 total: lock add qword at 0x45e8ba (atomic).
// +0x50 counter: lock inc qword at 0x45e8df via rax+0x50 (atomic).
#pragma pack(push, 1)
struct sub_45e860_node {
    std::uint8_t pad0x00[0x8];       // +0x00..+0x07 padding (no observed access)
    void* link;                      // +0x08: pointer (R at 0x45e8ef)
    std::uint8_t pad0x10[0x30];      // +0x10..+0x3f padding (no observed access)
    std::uint64_t refcount;          // +0x40: atomic counter (RW at 0x45e8b5)
    std::uint64_t total;             // +0x48: atomic accumulator (RW at 0x45e8ba)
    std::uint64_t counter;           // +0x50: atomic counter (RW at 0x45e8df)
};
#pragma pack(pop)

// Base register rdx = output object.
// +0x00..0x0f data0: W via movups at 0x45e90f
// +0x10..0x1f data1: W via movups at 0x45e916
// +0x20..0x2f data2: W via movups at 0x45e929
// +0x30..0x3f data3: W via movups at 0x45e935
// +0x40 flag: byte W at 0x45e904
#pragma pack(push, 1)
struct sub_45e860_out {
    std::uint64_t data0[2];   // +0x00: W at 0x45e90f
    std::uint64_t data1[2];   // +0x10: W at 0x45e916
    std::uint64_t data2[2];   // +0x20: W at 0x45e929
    std::uint64_t data3[2];   // +0x30: W at 0x45e935
    std::uint8_t flag;        // +0x40: W at 0x45e904
};
#pragma pack(pop)

// Base register r8 = atomic counter target (either node->counter or data_128d0a50[0]).
#pragma pack(push, 1)
struct sub_45e860_counter {
    std::uint64_t value;   // +0x00: RW at 0x45e8df
};
#pragma pack(pop)

// Stack frame overlay (rbp = rsp + 0x80):
//   [rbp-0x60..0x21]  data block (64 bytes, written by sub_45e9b0)
//   [rbp-0x20]        flag1 (byte, written by sub_45e5c0 via [rdx-8])
//   [rbp-0x18]        mutex (qword, written by sub_45e5c0 via rdx)
//   [rbp-0x10]        flag2 (byte, read but never written in this function)
#pragma pack(push, 1)
struct sub_45e860_stack {
    std::uint8_t data_block[0x40];   // +0x00  = [rbp-0x60], 64 bytes
    std::uint8_t flag1;               // +0x40  = [rbp-0x20]
    std::uint8_t pad0x41[0x7];        // +0x41..+0x47
    void* mutex;                      // +0x48  = [rbp-0x18]
    std::uint8_t flag2;               // +0x50  = [rbp-0x10]
};
#pragma pack(pop)

static_assert(offsetof(sub_45e860_self, node) == 0x10, "sub_45e860 self+0x10 node field");
static_assert(sizeof(sub_45e860_self) >= 0x18, "sub_45e860 self sizeof lower bound");

static_assert(offsetof(sub_45e860_node, link) == 0x8, "sub_45e860 node+0x8 link field");
static_assert(offsetof(sub_45e860_node, refcount) == 0x40, "sub_45e860 node+0x40 refcount field");
static_assert(offsetof(sub_45e860_node, total) == 0x48, "sub_45e860 node+0x48 total field");
static_assert(offsetof(sub_45e860_node, counter) == 0x50, "sub_45e860 node+0x50 counter field");
static_assert(sizeof(sub_45e860_node) >= 0x51, "sub_45e860 node sizeof lower bound");

static_assert(offsetof(sub_45e860_out, data0) == 0x0, "sub_45e860 out+0x0 data0 field");
static_assert(offsetof(sub_45e860_out, data1) == 0x10, "sub_45e860 out+0x10 data1 field");
static_assert(offsetof(sub_45e860_out, data2) == 0x20, "sub_45e860 out+0x20 data2 field");
static_assert(offsetof(sub_45e860_out, data3) == 0x30, "sub_45e860 out+0x30 data3 field");
static_assert(offsetof(sub_45e860_out, flag) == 0x40, "sub_45e860 out+0x40 flag field");
static_assert(sizeof(sub_45e860_out) >= 0x41, "sub_45e860 out sizeof lower bound");

static_assert(offsetof(sub_45e860_counter, value) == 0x0, "sub_45e860 counter+0x0 value field");
static_assert(sizeof(sub_45e860_counter) >= 0x8, "sub_45e860 counter sizeof lower bound");

static_assert(offsetof(sub_45e860_stack, data_block) == 0x0, "sub_45e860 stack+0x0 data_block field");
static_assert(offsetof(sub_45e860_stack, flag1) == 0x40, "sub_45e860 stack+0x40 flag1 field");
static_assert(offsetof(sub_45e860_stack, mutex) == 0x48, "sub_45e860 stack+0x48 mutex field");
static_assert(offsetof(sub_45e860_stack, flag2) == 0x50, "sub_45e860 stack+0x50 flag2 field");
static_assert(sizeof(sub_45e860_stack) >= 0x51, "sub_45e860 stack sizeof lower bound");

// Callees outside the lift set. Signatures are derived from the call sites in
// the listing (register contents at each `call`). These have no lifted header
// and are not boundary functions; they are linked directly to the game code.
void sub_45e5c0(void* self, void* mutex_out, std::uint8_t init_flag);
void sub_45e9b0(void* self, void* data_out, void* a2, void* a3);
void sub_443a80(void* a1, void* a2, void* a3);

// Global data arrays referenced via RIP-relative addressing in the listing.
extern std::uint64_t data_128d0a50[];
extern std::uint64_t data_128d0a38[];

// x64 Microsoft ABI: RCX=self, RDX=out, R8=a2, R9=a3; returns RAX=out (the out pointer).
void* sub_45e860(void* self, void* out, void* a2, void* a3);

} // namespace native::helpers
