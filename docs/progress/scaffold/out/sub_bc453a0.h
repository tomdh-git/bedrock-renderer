#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the object passed to sub_bc453a0 in rcx (this), reverse-engineered from the
// disassembly of [0xbc453a0, 0xbc45779), Minecraft Windows 1.26.62.01.
// Every [reg+off] access listed below is a [V] fact (cited by instruction).
// Field names, field meanings, the 'this' register, the full struct layout and
// sizeof are [open] decisions: see docs/functions/bc453a0.md '## DECISIONS'.
// This header is a scaffold placeholder: replace with the real derived layout.

struct sub_bc453a0_state {
    // placeholder layout: real offsets/field names TBD (see dossier ## DECISIONS)
    std::uint8_t pad[0x259];   // covers observed accesses up to +0x258
};

// Observed [reg+off] memory accesses ([V] from rdis dis of [0xbc453a0, 0xbc45779)).
static constexpr std::size_t off_0x10 = 0x10;   // 0xbc4541f  mov rax,[rax+0x10]
static constexpr std::size_t off_0x18 = 0x18;   // 0xbc454d2  lea rax,[rdi+0x18]
static constexpr std::size_t off_0x28 = 0x28;   // 0xbc45676  movups [r14+0x28],xmm0
static constexpr std::size_t off_0x2c = 0x2c;   // 0xbc45428  mov [rsp+0x2C],r11d
static constexpr std::size_t off_0x30 = 0x30;   // 0xbc453df  mov rdi,[rbx+0x30]
static constexpr std::size_t off_0x38 = 0x38;   // 0xbc45433  lock xadd [rbx+0x38],r12
static constexpr std::size_t off_0x48 = 0x48;   // 0xbc45626  cmp byte ptr [r14+0x48],0
static constexpr std::size_t off_0x50 = 0x50;   // 0xbc45685  mov [r14+0x50],rbx
static constexpr std::size_t off_0x58 = 0x58;   // 0xbc45693  mov qword ptr [r14+0x58],0x20
static constexpr std::size_t off_0x60 = 0x60;   // 0xbc4569b  mov qword ptr [r14+0x60],0
static constexpr std::size_t off_0x68 = 0x68;   // 0xbc456d6  lea rcx,[r14+0x68]
static constexpr std::size_t off_0x70 = 0x70;   // 0xbc456e5  mov [r14+0x70],r14
static constexpr std::size_t off_0x258 = 0x258;   // 0xbc45464  xchg [rbx+0x258],eax

static_assert(off_0x10 == 0x10, "sub_0xbc453a0 accesses self+0x10");
static_assert(off_0x18 == 0x18, "sub_0xbc453a0 accesses self+0x18");
static_assert(off_0x28 == 0x28, "sub_0xbc453a0 accesses self+0x28");
static_assert(off_0x2c == 0x2c, "sub_0xbc453a0 accesses self+0x2c");
static_assert(off_0x30 == 0x30, "sub_0xbc453a0 accesses self+0x30");
static_assert(off_0x38 == 0x38, "sub_0xbc453a0 accesses self+0x38");
static_assert(off_0x48 == 0x48, "sub_0xbc453a0 accesses self+0x48");
static_assert(off_0x50 == 0x50, "sub_0xbc453a0 accesses self+0x50");
static_assert(off_0x58 == 0x58, "sub_0xbc453a0 accesses self+0x58");
static_assert(off_0x60 == 0x60, "sub_0xbc453a0 accesses self+0x60");
static_assert(off_0x68 == 0x68, "sub_0xbc453a0 accesses self+0x68");
static_assert(off_0x70 == 0x70, "sub_0xbc453a0 accesses self+0x70");
static_assert(off_0x258 == 0x258, "sub_0xbc453a0 accesses self+0x258");

static_assert(true, "sub_0xbc453a0: replace with real offsetof/sizeof asserts for every struct read/written");

// Signature (x64 Microsoft ABI) - [open]: exact argument and return types are not
// derivable from static analysis; the first instructions of the prologue are cited.
// 0xbc453a0  push r15; 0xbc453a2  push r14; 0xbc453a4  push r13; 0xbc453a6  push r12
uintptr_t sub_bc453a0(sub_bc453a0_state* self);   // [open] signature placeholder (return type, arg types TBD)

} // namespace native::bgfx
