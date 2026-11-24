#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// bx::HashMurmur2A state fields touched by bx::HashMurmur2A::add (0xbc76610).
// Offsets and access directions confirmed [V] from the disassembly of
// [0xbc76610, 0xbc767ec):
//   +0x00 uint32_t m_hash      running hash      read  0xbc7662b  written 0xbc766a4/0xbc76721/0xbc767cd
//   +0x04 uint32_t m_tail      assembled tail    read  0xbc7662e  written 0xbc76673/0xbc7679c
//   +0x08 uint32_t m_nbytesInTail # bytes in tail, 0..3  read 0xbc76632 written 0xbc76679/0xbc767a2
//   +0x0C uint32_t m_nbytes    total bytes read  0xbc7661e (add [rax+0xC],r8d)
// No other member is read or written by the function. The class may have further
// members (e.g. the seed) that add does not touch; they are not part of this layout.
struct HashMurmur2A {
    uint32_t m_hash;           // +0x00
    uint32_t m_tail;           // +0x04
    uint32_t m_nbytesInTail;   // +0x08
    uint32_t m_nbytes;         // +0x0C
};

static_assert(offsetof(HashMurmur2A, m_hash) == 0x00, "HashMurmur2A::m_hash must be at +0x00");
static_assert(offsetof(HashMurmur2A, m_tail) == 0x04, "HashMurmur2A::m_tail must be at +0x04");
static_assert(offsetof(HashMurmur2A, m_nbytesInTail) == 0x08,
              "HashMurmur2A::m_nbytesInTail must be at +0x08");
static_assert(offsetof(HashMurmur2A, m_nbytes) == 0x0C, "HashMurmur2A::m_nbytes must be at +0x0C");
static_assert(sizeof(HashMurmur2A) == 0x10, "HashMurmur2A state must be 0x10 bytes");

// void bx::HashMurmur2A::add(const void* data, uint32_t len)
// x64 ABI: this = rcx (self), data = rdx, len = r8d. The 4th x64 argument (r9)
// is never read by the original. No return value is written: the epilogue
// (0xbc767df  pop rbx / 0xbc767e0  pop rsi / 0xbc767e1  ret) leaves eax holding
// the entry value of rax (= this); callers do not use a return value.
extern "C" void HashMurmur2A_add(HashMurmur2A* self, const void* data, uint32_t len);

} // namespace native::bgfx
