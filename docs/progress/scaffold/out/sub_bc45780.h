#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the object passed to sub_bc45780 in rcx (this), reverse-engineered from the
// disassembly of [0xbc45780, 0xbc4595a), Minecraft Windows 1.26.62.01.
// Every [reg+off] access listed below is a [V] fact (cited by instruction).
// Field names, field meanings, the 'this' register, the full struct layout and
// sizeof are [open] decisions: see docs/functions/bc45780.md '## DECISIONS'.
// This header is a scaffold placeholder: replace with the real derived layout.

struct sub_bc45780_state {
    // placeholder layout: real offsets/field names TBD (see dossier ## DECISIONS)
    std::uint8_t pad[0x1009];   // covers observed accesses up to +0x1008
};

// Observed [reg+off] memory accesses ([V] from rdis dis of [0xbc45780, 0xbc4595a)).
static constexpr std::size_t off_0x10 = 0x10;   // 0xbc45872  movups xmm1,[rdx+0x10]
static constexpr std::size_t off_0x18 = 0x18;   // 0xbc4580c  mov r9,[rax+0x18]
static constexpr std::size_t off_0x20 = 0x20;   // 0xbc4578b  mov rsi,[rcx+0x20]
static constexpr std::size_t off_0x28 = 0x28;   // 0xbc457d1  mov rax,[rcx+0x28]
static constexpr std::size_t off_0x30 = 0x30;   // 0xbc4587d  mov r9,[rdx+0x30]
static constexpr std::size_t off_0x38 = 0x38;   // 0xbc45894  movups [rax+0x38],xmm0
static constexpr std::size_t off_0x40 = 0x40;   // 0xbc45798  mov rax,[rcx+0x40]
static constexpr std::size_t off_0x48 = 0x48;   // 0xbc45890  movups [rax+0x48],xmm0
static constexpr std::size_t off_0x50 = 0x50;   // 0xbc458b0  mov qword ptr [rdx+0x50],0xF
static constexpr std::size_t off_0x58 = 0x58;   // 0xbc458c6  mov r9d,[rdx+0x58]
static constexpr std::size_t off_0x5c = 0x5c;   // 0xbc458bc  movzx r9d,word ptr [rdx+0x5C]
static constexpr std::size_t off_0x60 = 0x60;   // 0xbc457f2  mov rax,[rcx+0x60]
static constexpr std::size_t off_0x70 = 0x70;   // 0xbc458ce  mov r9,[rdx+0x70]
static constexpr std::size_t off_0x78 = 0x78;   // 0xbc457a7  movzx r8d,byte ptr [rdx+0x78]
static constexpr std::size_t off_0x1008 = 0x1008;   // 0xbc4590e  mov qword ptr [rax+0x1008],0

static_assert(off_0x10 == 0x10, "sub_0xbc45780 accesses self+0x10");
static_assert(off_0x18 == 0x18, "sub_0xbc45780 accesses self+0x18");
static_assert(off_0x20 == 0x20, "sub_0xbc45780 accesses self+0x20");
static_assert(off_0x28 == 0x28, "sub_0xbc45780 accesses self+0x28");
static_assert(off_0x30 == 0x30, "sub_0xbc45780 accesses self+0x30");
static_assert(off_0x38 == 0x38, "sub_0xbc45780 accesses self+0x38");
static_assert(off_0x40 == 0x40, "sub_0xbc45780 accesses self+0x40");
static_assert(off_0x48 == 0x48, "sub_0xbc45780 accesses self+0x48");
static_assert(off_0x50 == 0x50, "sub_0xbc45780 accesses self+0x50");
static_assert(off_0x58 == 0x58, "sub_0xbc45780 accesses self+0x58");
static_assert(off_0x5c == 0x5c, "sub_0xbc45780 accesses self+0x5c");
static_assert(off_0x60 == 0x60, "sub_0xbc45780 accesses self+0x60");
static_assert(off_0x70 == 0x70, "sub_0xbc45780 accesses self+0x70");
static_assert(off_0x78 == 0x78, "sub_0xbc45780 accesses self+0x78");
static_assert(off_0x1008 == 0x1008, "sub_0xbc45780 accesses self+0x1008");

static_assert(true, "sub_0xbc45780: replace with real offsetof/sizeof asserts for every struct read/written");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xbc45780  push r15; 0xbc45782  push r14; 0xbc45784  push rsi; 0xbc45785  push rdi
uintptr_t sub_bc45780(sub_bc45780_state* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::bgfx
