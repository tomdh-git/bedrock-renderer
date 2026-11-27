#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// State layout for sub_bb67fd0, reverse-engineered from the disassembly
// of [0xbb67fd0, 0xbb680bf), Minecraft Windows 1.26.62.01.
// Offsets and widths come straight from the instruction operands.
// Field names and meanings are reverse-engineered decisions (see
// docs/functions/bb67fd0.md ## DECISIONS); the listing alone does not
// determine them.

// Base register RCX ("self" / state object, argument 1).
// Observed: +0x00 W at 0xbb67ff2 (movups [rcx], zeroed), +0x08 R/W write cursor
// (0xbb68017/0xbb68031/0xbb6805a/0xbb6806a/0xbb6808e/0xbb6809e), +0x10 R/W
// write limit (0xbb67ff5 W, 0xbb68035/0xbb6805e/0xbb68092 R).
struct SubBb67fd0State {
    void* buffer;   // +0x00: zeroed at 0xbb67ff2; never read in this function
    void* cur;      // +0x08: next write destination (8-byte granular, advanced by 0x10)
    void* end;      // +0x10: one-past-end write limit
};

// Base register RDX (argument 2): a range of 16-byte chunks.
// Observed: +0x20 R at 0xbb67ffd (range begin), +0x28 R at 0xbb68001 (range end).
struct SubBb67fd0SrcRange {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f: no observed access
    const std::uint8_t* begin;    // +0x20: first 16-byte chunk
    const std::uint8_t* end;      // +0x28: one-past-last 16-byte chunk
};

// Base registers R8/R9 (arguments 3/4, copied into RDI/RSI in the prologue).
// Observed: +0x130 R as a 16-byte chunk (movups after add r8/rsi,0x130),
//           +0x140 R flag byte (cmp byte, 0 at 0xbb68046; cmp byte, 1 at 0xbb6807a).
struct SubBb67fd0Block {
    std::uint8_t pad0x00[0x130];   // +0x00..+0x12f: no observed access
    std::uint8_t data[16];         // +0x130: 16-byte chunk copied into the state stream
    std::uint8_t flag;             // +0x140: flag byte
};

// sub_1197a0 (0x1197a0): boundary candidate (docs/data/native_boundary_candidates.tsv);
// not in the lift set and no statically recorded signature. This function calls it at
// 0xbb6803e, 0xbb68074 and 0xbb680a8 with RCX = state, RDX = state->cur, R8 = pointer
// to a 16-byte chunk and R9 = argument 3 (a3); RAX is never read after the call.
extern "C" void sub_1197a0(SubBb67fd0State* state, std::uint8_t* cur,
                           const std::uint8_t* chunk16, SubBb67fd0Block* ctx);

// sub_bb67fd0 (0xbb67fd0, size 0xef): x64 Microsoft ABI.
//   RCX = self (SubBb67fd0State*), RDX = src range (SubBb67fd0SrcRange*),
//   R8 = block a2 (SubBb67fd0Block*), R9 = block a3 (SubBb67fd0Block*).
//   Returns RAX = self. Copies 16-byte chunks from the src range into the
//   state stream [cur, end), flushing through sub_1197a0 whenever the stream
//   is full, then optionally copies the 16-byte chunk at a2+0x130 when
//   a2->flag != 0 and the chunk at a3+0x130 when a3->flag == 1.
SubBb67fd0State* sub_bb67fd0(SubBb67fd0State* self, SubBb67fd0SrcRange* src,
                             SubBb67fd0Block* a2, SubBb67fd0Block* a3);

static_assert(offsetof(SubBb67fd0State, buffer) == 0x0, "sub_bb67fd0 state+0x00 field");
static_assert(offsetof(SubBb67fd0State, cur) == 0x8, "sub_bb67fd0 state+0x08 field");
static_assert(offsetof(SubBb67fd0State, end) == 0x10, "sub_bb67fd0 state+0x10 field");
static_assert(sizeof(SubBb67fd0State) == 0x18, "sub_bb67fd0 state size");
static_assert(offsetof(SubBb67fd0SrcRange, begin) == 0x20, "sub_bb67fd0 src+0x20 field");
static_assert(offsetof(SubBb67fd0SrcRange, end) == 0x28, "sub_bb67fd0 src+0x28 field");
static_assert(sizeof(SubBb67fd0SrcRange) == 0x30, "sub_bb67fd0 src size");
static_assert(offsetof(SubBb67fd0Block, data) == 0x130, "sub_bb67fd0 block+0x130 field");
static_assert(offsetof(SubBb67fd0Block, flag) == 0x140, "sub_bb67fd0 block+0x140 field");
static_assert(sizeof(SubBb67fd0Block) == 0x141, "sub_bb67fd0 block size");

} // namespace native::helpers
