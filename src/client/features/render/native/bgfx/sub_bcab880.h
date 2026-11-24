#pragma once

#include "client/features/render/native/Lift.h"

#include <atomic>
#include <cstddef>
#include <cstdint>

// Layout model for the argument of sub 0xbcab880 ("group insert UI", region bgfx).
// Every offset below is read from the disassembly of [0xbcab880, 0xbcab8ea)
// and is asserted here. The function touches no other game memory; its two
// calls indirect through data slot 0xF99FFA0 (stored value 0x14eea6040 =
// image base 0x140000000 + 0xeea6040 = sub_eea6040, class vendor, listed in
// docs/data/native_boundary.tsv).
//
//   GroupEntry (the rcx argument at entry):
//     +0x00  uiObject  object whose +0x18 is read (mov rax,[rax+0x18] at 0xbcab89a)
//     +0x08  refCnt   refcounted object (strong +0x08, weak +0x0C, vptr +0x00)
//   RefCnt:
//     +0x00  vptr     read twice as dead loads ([rc2] then [[rc2]] / [[rc2]+8])
//     +0x08  strong   lock inc (0xbcab88f), lock dec (0xbcab8a6)
//     +0x0C  weak     lock dec (0xbcab8bb)
//   The object reached via uiObject->next (+0x18): its +0x00 feeds the return
//   value (setne al at 0xbcab8e0: AL = (that qword != 0)) [V].

namespace native::bgfx {

struct UiObject {
    char pad[0x18];
    void* next;   // +0x18: read at 0xbcab89a; *next read at 0xbcab89e
};
static_assert(offsetof(UiObject, next) == 0x18, "bcab880: UiObject::next at +0x18");
static_assert(sizeof(UiObject) == 0x20, "bcab880: UiObject is 0x20 bytes");

struct RefCnt {
    void* vptr;                              // +0x00
    std::atomic<uint32_t> strong;            // +0x08  lock inc / lock dec
    std::atomic<uint32_t> weak;              // +0x0C  lock dec
};
static_assert(offsetof(RefCnt, vptr) == 0x00, "bcab880: RefCnt::vptr at +0x00");
static_assert(offsetof(RefCnt, strong) == 0x08, "bcab880: RefCnt::strong at +0x08");
static_assert(offsetof(RefCnt, weak) == 0x0C, "bcab880: RefCnt::weak at +0x0C");
static_assert(sizeof(RefCnt) == 0x10, "bcab880: RefCnt is 0x10 bytes");

struct GroupEntry {
    UiObject* uiObject;   // +0x00  mov rax,[rcx] at 0xbcab893
    RefCnt* refCnt;       // +0x08  mov rax,[rcx+8] at 0xbcab886 and 0xbcab896
};
static_assert(offsetof(GroupEntry, uiObject) == 0x00, "bcab880: GroupEntry::uiObject at +0x00");
static_assert(offsetof(GroupEntry, refCnt) == 0x08, "bcab880: GroupEntry::refCnt at +0x08");
static_assert(sizeof(GroupEntry) == 0x10, "bcab880: GroupEntry is 0x10 bytes");

// x64 Microsoft ABI: rcx = entry (GroupEntry*), return in AL =
// (*(uintptr_t*)*(UiObject**)(entry->uiObject + 0x18) != 0).
// No other argument register is read; no stack arguments. [V]
bool sub_bcab880(GroupEntry* entry);

// Footprint of sub 0xbcab880: the GroupEntry argument and, when present, its
// refCnt object (strong/weak atomics at +0x08/+0x0C are written by the
// original). The boundary thunk's own writes are served from the differential
// tape and are not declared here. [V]
native::Footprint sub_bcab880_footprint(GroupEntry* entry);

} // namespace native::bgfx
