#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// GuardedPagedArray<0x540>: the RenderBind storage array embedded in the Frame at +0x8B4700.
// Layout [V] from the disassembly of [0xbc7a7c0, 0xbc7a99c), Minecraft Windows 1.26.62.01.
// Only the fields touched by GuardedPagedArray_ensure are declared; bytes between +0x34 and
// +0x73 are not touched by this function and are modelled as pad.
struct GuardedPagedArray {
    uint8_t*  base;             // +0x00  base of the reserved record range (record i at base + i*0x540)
    uint32_t  maxCount;         // +0x08  maximum record count
    uint8_t   pad_0x0c[4];      // +0x0c
    uint64_t  reservedBytes;    // +0x10  reserved range size (commit ceiling)
    uint64_t  zeroedCount;      // +0x18  records already zero-initialised
    uint64_t  committedBytes;   // +0x20  committed range size
    uint8_t   lock[0x4C];       // +0x28  mutex object (opaque; &lock passed to sub_eec59f0/sub_eec5a10)
    uint32_t  commitGuard;      // +0x74  0x7FFFFFFF = commit already in progress (double-lock sentinel)
};
static_assert(offsetof(GuardedPagedArray, base) == 0x00, "GuardedPagedArray_ensure: base at +0x00");
static_assert(offsetof(GuardedPagedArray, maxCount) == 0x08, "GuardedPagedArray_ensure: maxCount at +0x08");
static_assert(offsetof(GuardedPagedArray, reservedBytes) == 0x10, "GuardedPagedArray_ensure: reservedBytes at +0x10");
static_assert(offsetof(GuardedPagedArray, zeroedCount) == 0x18, "GuardedPagedArray_ensure: zeroedCount at +0x18");
static_assert(offsetof(GuardedPagedArray, committedBytes) == 0x20, "GuardedPagedArray_ensure: committedBytes at +0x20");
static_assert(offsetof(GuardedPagedArray, lock) == 0x28, "GuardedPagedArray_ensure: lock at +0x28");
static_assert(offsetof(GuardedPagedArray, commitGuard) == 0x74, "GuardedPagedArray_ensure: commitGuard at +0x74");
static_assert(sizeof(GuardedPagedArray) >= 0x78, "GuardedPagedArray_ensure: size covers +0x74");

// IAT forwarders reached by direct call (hard rule 69: a jmp-to-another-function thunk is a
// normal lift item, forward-declared here and called like any lifted function).
// Verified at the call site [V]: rcx = mutex pointer; sub_eec59f0 returns eax (tested for 0);
// sub_eec5a10's return is unused; sub_eec5a00 takes ecx = 5 or 6 and the original follows it
// with int3 (0xbc7a99b). Their import targets are loader-resolved and not statically visible.
extern "C" int32_t sub_eec59f0(void* mtx);            // 0xeec59f0: jmp qword ptr [0xF9A75A8]
extern "C" void sub_eec5a10(void* mtx);               // 0xeec5a10: jmp qword ptr [0xF9A75B8]
extern "C" void sub_eec5a00(uint32_t code);           // 0xeec5a00: jmp qword ptr [0xF9A72F0]

} // namespace native

namespace native::bgfx {

// GuardedPagedArray<0x540>::ensure(idx): commit and zero the RenderBind storage so record idx
// is usable. Called by the four Encoder::submit forms right before they copy the bind block.
// Lifted from [0xbc7a7c0, 0xbc7a99c) (size 0x1dc), Minecraft Windows 1.26.62.01.
// Calls: sub_eec59f0 (lock), sub_3afbe0 (stl assert report), sub_eec6ed0 (crt memset),
// sub_eec5a10 (unlock), plus interface calls through CFG-thunk data slot [0xF99FFA0] and the
// fail-fast import through data slot [0xF9A8CB0].
void GuardedPagedArray_ensure(GuardedPagedArray* self, uint32_t idx);

} // namespace native::bgfx
