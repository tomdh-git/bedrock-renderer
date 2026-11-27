#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the object passed to sub_bc34f70 in rcx (this), reverse-engineered from the
// disassembly of [0xbc34f70, 0xbc35083), Minecraft Windows 1.26.62.01.
// Every [reg+off] access listed below is a [V] fact (cited by instruction).
// Field names, field meanings, the 'this' register, the full struct layout and
// sizeof are [open] decisions: see docs/functions/bc34f70.md '## DECISIONS'.
// This header is a scaffold placeholder: replace with the real derived layout.

struct sub_bc34f70_state {
    // placeholder layout: real offsets/field names TBD (see dossier ## DECISIONS)
    std::uint8_t pad[0x3a1];   // covers observed accesses up to +0x3a0
};

// Observed [reg+off] memory accesses ([V] from rdis dis of [0xbc34f70, 0xbc35083)).
static constexpr std::size_t off_0x10 = 0x10;   // 0xbc35004  mov qword ptr [rdi+0x10],0
static constexpr std::size_t off_0x18 = 0x18;   // 0xbc35015  mov rax,[rsi+0x18]
static constexpr std::size_t off_0x20 = 0x20;   // 0xbc34f95  mov rax,[rax+0x20]
static constexpr std::size_t off_0x2e8 = 0x2e8;   // 0xbc34fbf  lea rdi,[rsi+0x2E8]
static constexpr std::size_t off_0x2f8 = 0x2f8;   // 0xbc34fce  mov rdx,[rsi+0x2F8]
static constexpr std::size_t off_0x328 = 0x328;   // 0xbc34fb6  cmp byte ptr [rsi+0x328],1
static constexpr std::size_t off_0x330 = 0x330;   // 0xbc34faa  lea rcx,[rsi+0x330]
static constexpr std::size_t off_0x368 = 0x368;   // 0xbc34f85  lea rax,[rsi+0x368]
static constexpr std::size_t off_0x3a0 = 0x3a0;   // 0xbc34f79  mov rcx,[rcx+0x3A0]

static_assert(off_0x10 == 0x10, "sub_0xbc34f70 accesses self+0x10");
static_assert(off_0x18 == 0x18, "sub_0xbc34f70 accesses self+0x18");
static_assert(off_0x20 == 0x20, "sub_0xbc34f70 accesses self+0x20");
static_assert(off_0x2e8 == 0x2e8, "sub_0xbc34f70 accesses self+0x2e8");
static_assert(off_0x2f8 == 0x2f8, "sub_0xbc34f70 accesses self+0x2f8");
static_assert(off_0x328 == 0x328, "sub_0xbc34f70 accesses self+0x328");
static_assert(off_0x330 == 0x330, "sub_0xbc34f70 accesses self+0x330");
static_assert(off_0x368 == 0x368, "sub_0xbc34f70 accesses self+0x368");
static_assert(off_0x3a0 == 0x3a0, "sub_0xbc34f70 accesses self+0x3a0");

static_assert(true, "sub_0xbc34f70: replace with real offsetof/sizeof asserts for every struct read/written");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xbc34f70  push rsi; 0xbc34f71  push rdi; 0xbc34f72  sub rsp,0x28; 0xbc34f76  mov rsi,rcx
uintptr_t sub_bc34f70(sub_bc34f70_state* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::bgfx
