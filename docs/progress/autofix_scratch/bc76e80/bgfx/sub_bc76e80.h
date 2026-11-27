#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

// sub_bc76e80: bgfx destroy-queue drain / notify (size 0x36f, 1.26.62.01).

// Every layout constant below is taken from the disassembly of

// [0xbc76e80, 0xbc771ef) and asserted here so the header cannot drift from the exe. [V]

//

// The queue object (the rcx 'this' argument):

//   +0x00 uint64_t*  begin   record-array start  (P)

//   +0x08 uint64_t*  end     record-array end    (Q)

//   +0x10 uint64_t*  cap     record-array capacity end (C)

//   +0x18 int64_t    count   decremented once per drained entry

//   +0x20 void**     buckets bucket-array start  (A)

//   +0x28 void**     buckets end                 (B); nbuckets = (B - A) >> 3

//

// Queue record: 16-byte { uint64_t key @0x00, uint64_t value @0x08 }, stride 0x10.

// Hash-chain entry node (heap-allocated, freed through the data-slot thunk):

//   { uint64_t key @0x00, uint64_t value @0x08, entry* next @0x10, entry* prev @0x18 }.


namespace native::bgfx {

struct Bc76e80Queue {
    uint64_t* begin;     // +0x00  P

    uint64_t* end;       // +0x08  Q

    uint64_t* cap;       // +0x10  C

    int64_t count;       // +0x18

    void** buckets;      // +0x20  A

    void** bucketsEnd;   // +0x28  B

};
static_assert(offsetof(Bc76e80Queue, begin) == 0x00, "bc76e80: queue begin at +0x00");
static_assert(offsetof(Bc76e80Queue, end) == 0x08, "bc76e80: queue end at +0x08");
static_assert(offsetof(Bc76e80Queue, cap) == 0x10, "bc76e80: queue cap at +0x10");
static_assert(offsetof(Bc76e80Queue, count) == 0x18, "bc76e80: queue count at +0x18");
static_assert(offsetof(Bc76e80Queue, buckets) == 0x20, "bc76e80: queue buckets at +0x20");
static_assert(offsetof(Bc76e80Queue, bucketsEnd) == 0x28, "bc76e80: queue bucketsEnd at +0x28");
static_assert(sizeof(Bc76e80Queue) == 0x30, "bc76e80: queue size 0x30");

struct Bc76e80Record {
    uint64_t key;   // +0x00

    uint64_t value; // +0x08

};
static_assert(offsetof(Bc76e80Record, key) == 0x00, "bc76e80: record key at +0x00");
static_assert(offsetof(Bc76e80Record, value) == 0x08, "bc76e80: record value at +0x08");
static_assert(sizeof(Bc76e80Record) == 0x10, "bc76e80: record stride 0x10");

struct Bc76e80Entry {
    uint64_t key;               // +0x00

    uint64_t value;             // +0x08

    Bc76e80Entry* next;         // +0x10

    Bc76e80Entry* prev;         // +0x18

};
static_assert(offsetof(Bc76e80Entry, key) == 0x00, "bc76e80: entry key at +0x00");
static_assert(offsetof(Bc76e80Entry, value) == 0x08, "bc76e80: entry value at +0x08");
static_assert(offsetof(Bc76e80Entry, next) == 0x10, "bc76e80: entry next at +0x10");
static_assert(offsetof(Bc76e80Entry, prev) == 0x18, "bc76e80: entry prev at +0x18");
static_assert(sizeof(Bc76e80Entry) == 0x20, "bc76e80: entry size 0x20");

static constexpr uint64_t kBc76e80HashMul = 0x1003FULL;          // imul reg,0x1003F [V]

static constexpr uint64_t kBc76e80HashMix = 0x1007E0F81ULL;      // mov r10,imm64 at 0xbc76f0c [V]

static constexpr uintptr_t kBc76e80AllocatorGlobalRva = 0x12ADF800; // mov rdx,[0x12ADF800] [V]

static constexpr uintptr_t kBc76e80ThunkSlotRva = 0xF99FFA0;     // call [0xF99FFA0] [V]

static constexpr std::size_t kBc76e80RecordStride = 0x10;        // shr/sar ...,4 / shl ...,4 [V]

static constexpr std::size_t kBc76e80BucketStride = 8;           // shr r8,3 [V]


// void sub_bc76e80(Bc76e80Queue* queue /*rcx*/, uint64_t key /*rdx*/);

// The original leaves rax = the bucket sentinel (key not found) or the thunk result

// (key found and drained); all four in-exe callers ignore the return value, so the

// lift returns void: identical observable behaviour at every call site.

//   0xbc66eb8  call 0xBC76E80   0xbc670ce  call 0xBC76E80   0xbc6fe68  call 0xBC76E80   0xbc70885  call 0xBC76E80  [V xref]

void sub_bc76e80(Bc76e80Queue* queue, uint64_t key);

} // namespace native::bgfx

