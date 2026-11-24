#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/bgfx/sub_bc60f10.h"
#include "client/features/render/rewrite/RewriteRegistry.h"

namespace native {

// Layout of the embedded slab allocator reversed from sub_bc79a60 (0xbc79a60, size 0x46f).
// The callee's `this` is the frame-graph builder object at +0x1DF3460; the allocator itself
// starts there. Every offset below is read or written by that function [V]; instruction
// cites for every use are in sub_bc79a60.cpp. The name "Slab" is a working name (no symbol
// in evidence) — only the offsets and sizes are claimed.
//
//   +0x0000..+0x3FFF inline 4-byte slots (u16 stamp + u16 next link)
//   +0x4000  void* blockHead   header block of the block chain
//   +0x4008  u64  cursor      next byte offset to hand out
//   +0x4010  u64  limit       high-water byte offset
//   +0x4018  u16  count       slots handed out
struct Slab {
    std::uint8_t slot[0x4000];   // +0x0000 inline slot array
    void* blockHead;             // +0x4000 header block of the chain
    std::uint64_t cursor;        // +0x4008
    std::uint64_t limit;         // +0x4010
    std::uint16_t count;         // +0x4018
};

// Slab header block: the first allocation of the chain (0x18 bytes, zeroed at creation).
//   +0x0000 head block (pointer), +0x0008 tail block (pointer), +0x0010 total bytes committed.
struct SlabHeader {
    void* headBlock;     // +0x0000
    void* tailBlock;     // +0x0008
    std::uint64_t totalBytes;  // +0x0010
};                       // sizeof == 0x18

// Chain block: 0x4008-byte allocation; payload slots at +0x0000..+0x3FFF,
// forward link at +0x4000 (last 8 bytes of the allocation).
struct SlabChainBlock {
    std::uint8_t payload[0x4000];
    void* nextBlock;     // +0x4000
};                       // sizeof == 0x4008

static_assert(offsetof(Slab, blockHead) == 0x4000, "Slab::blockHead must be at +0x4000");
static_assert(offsetof(Slab, cursor) == 0x4008, "Slab::cursor must be at +0x4008");
static_assert(offsetof(Slab, limit) == 0x4010, "Slab::limit must be at +0x4010");
static_assert(offsetof(Slab, count) == 0x4018, "Slab::count must be at +0x4018");
static_assert(offsetof(SlabHeader, headBlock) == 0x00, "SlabHeader::headBlock must be at +0x0000");
static_assert(offsetof(SlabHeader, tailBlock) == 0x08, "SlabHeader::tailBlock must be at +0x0008");
static_assert(offsetof(SlabHeader, totalBytes) == 0x10, "SlabHeader::totalBytes must be at +0x0010");
static_assert(sizeof(SlabHeader) == 0x18, "SlabHeader must be 0x18 bytes");
static_assert(offsetof(SlabChainBlock, nextBlock) == 0x4000, "SlabChainBlock::nextBlock must be at +0x4000");
static_assert(sizeof(SlabChainBlock) == 0x4008, "SlabChainBlock must be 0x4008 bytes");

// Accessors mirroring the exact field reads/writes of 0xbc79a60.
inline void*& slabHeadBlock(void* header) { return *reinterpret_cast<void**>(header); }                // header +0x0000  [V 0xbc79c5e/0xbc79e15: mov rdx,[rdx]]
inline void*& slabTailBlock(void* header) { return *reinterpret_cast<void**>(static_cast<char*>(header) + 0x0008); }  // header +0x0008  [V 0xbc79b31]
inline std::uint64_t& slabTotalBytes(void* header) { return *reinterpret_cast<std::uint64_t*>(static_cast<char*>(header) + 0x0010); }  // header +0x0010  [V 0xbc79b24]
inline void*& blockLink(void* block) { return *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000); }  // block +0x4000  [V 0xbc79ca0/0xbc79e50/0xbc79cc0/0xbc79e70]

// Allocator handle from image slot [0x12ADF800] and its realloc vtable slot 1 — exactly the
// sequence 0xbc79ad9  mov rcx,[0x12ADF800] / 0xbc79ae0  mov rax,[rcx] / 0xbc79ae3  mov rax,[rax+8]
// (same at 0xbc79b60-0xbc79b6a). Reuses the sub_bc60f10.h shim: g_allocator() reads the slot,
// allocatorRealloc() loads vtable slot 1. The indirect call through data slot [0xF99FFA0] (sub_eea6040,
// a `jmp rax` thunk; docs/data/native_boundary.tsv line 506) tail-calls it, so invoking the
// function pointer directly with the same arguments is identical [V hard rule 69].
inline AllocatorI* slabAllocator() { return g_allocator(); }
inline ReallocFn slabRealloc(AllocatorI* alloc) { return allocatorRealloc(alloc); }

// realloc file-name string: slot [0xF7CC762] "NOFILE" [V 0xbc79ae7/0xbc79b6e lea rdx,[0xF7CC762]].
extern const char kSlabReallocFile[];

// Lifted function: 0xbc79a60, size 0x46f, returns the new cursor in rax (callers observe ax as a
// u16 handle [V 0xbc73853/0xbc745e8]). x64 ABI: rcx = slab (Slab*), no other arguments,
// no stack arguments read. No null guards, no SEH (the original has none).
extern "C" std::uint64_t sub_bc79a60(Slab* slab);

} // namespace native
