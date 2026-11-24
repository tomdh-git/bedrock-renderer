#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bc76380: D3D12 submit RTX override (size 0x107, 1.26.62.01).
// Layout constants for the lifted body, taken from the disassembly of
// [0xbc76380, 0xbc76487). The function touches no game struct: it reads/writes
// only the record slot pointer at slot+0x0 and its own stack frame
// (rsp+0x20 record pointer, rsp+0x28 record length u32, rsp+0x34 4-byte copy
// destination, rsp+0x38 stack-cookie slot). Offsets below mirror that frame. [V]

namespace native::bgfx {

// Stack record as built at rsp+0x20: { char* ptr @ +0x0, uint32_t len @ +0x8 }.
struct Bc76380Record {
    char* ptr;   // +0x00  rsp+0x20
    uint32_t len;// +0x08  rsp+0x28
};
static_assert(offsetof(Bc76380Record, ptr) == 0x00, "bc76380: record pointer at +0x0");
static_assert(offsetof(Bc76380Record, len) == 0x08, "bc76380: record length at +0x8");

// Stack-frame offsets used by sub 0xbc76380 (relative to rsp after the 0x40 prologue).
static constexpr uint32_t kBc76380RecordOffset = 0x20;   // &record, rsp+0x20
static constexpr uint32_t kBc76380RecordLenOffset = 0x28;// record.len, rsp+0x28
static constexpr uint32_t kBc76380DestOffset = 0x34;     // copy destination, rsp+0x34 (4 bytes)
static constexpr uint32_t kBc76380CookieOffset = 0x38;   // cookie slot, rsp+0x38
static constexpr uint32_t kBc76380MaxDiff = 0x2;         // accepted char offset <= 2 (cmp rax,2 / jg)
static constexpr uint32_t kBc76380StrlenMax = 0x7FFFFFFF;// strlen cap passed by the original
static constexpr uintptr_t kBc76380DefaultPtr = 0xF847A07;// default record pointer (data_f847a07)
static_assert(kBc76380RecordOffset == 0x20, "bc76380: record offset");
static_assert(kBc76380RecordLenOffset == 0x28, "bc76380: record length offset");
static_assert(kBc76380DestOffset == 0x34, "bc76380: copy destination offset");
static_assert(kBc76380CookieOffset == 0x38, "bc76380: cookie slot offset");
static_assert(kBc76380MaxDiff == 0x2, "bc76380: max accepted diff");

// uint32_t sub_bc76380(uint64_t* slot /*rcx*/, uint32_t ch /*rdx*/, uint32_t flags /*r8d*/, uint32_t /*r9 unused*/);
// Return value in eax/edi (= flags, or the result of the indirect call on the accepted path).
// r9 at entry is never read by the original.
uint32_t sub_bc76380(uint64_t* slot, uint32_t ch, uint32_t flags, uint32_t unused);

} // namespace native::bgfx
