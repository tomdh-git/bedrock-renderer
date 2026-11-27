#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_3cf43f0, reverse-engineered from the disassembly
// of [0x3cf43f0, 0x3cf44ed), Minecraft Windows 1.26.62.01. Offsets and widths
// come straight from the instruction operands ([proven]); field names below are
// the semantics decided by the lift author.
// One struct per base register that is dereferenced. Field f<hex> is at offset
// 0x<hex>. The struct is packed (#pragma pack(1)) so every declared field sits
// exactly at its observed offset and offsetof() matches it. The real object may
// have compiler-inserted alignment padding, so sizeof is a lower bound.

// Object pointed to by rcx/a0 (dereferenced at 0x3cf4409:R f0, 0x3cf4415:R f8,
// 0x3cf4479:R f0, 0x3cf447c:R f10, 0x3cf44ac:W f0, 0x3cf44b6:W f8,
// 0x3cf44c1:W f10).
// f0 = buffer base pointer, f8 = end pointer (base + count*0x40),
// f10 = limit/current pointer (base + count*0x40, updated in place).
#pragma pack(push, 1)
struct sub_3cf43f0_rcx {
    void* buffer;   // +0x00: void* R/W — buffer base pointer
    std::uint64_t end;   // +0x08: std::uint64_t R/W — end pointer
    std::uint64_t limit; // +0x10: std::uint64_t R/W — limit/current pointer
};
#pragma pack(pop)

// Each 0x40-byte entry walked by r15 (dereferenced at 0x3cf4425:W f10,
// 0x3cf442d:W f18, 0x3cf4435:W f0 byte, 0x3cf4442:R f18, 0x3cf444c:R f0).
// f0 = entry data pointer, f10 = size, f18 = capacity.
#pragma pack(push, 1)
struct sub_3cf43f0_r15 {
    void* data;   // +0x00: void* R/W — entry data pointer
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    std::uint64_t size;   // +0x10: std::uint64_t W — entry size
    std::uint64_t capacity; // +0x18: std::uint64_t R/W — entry capacity
};
#pragma pack(pop)

// Stack slot written at 0x3cf44d3:W (rsp+0x20) — block 15 error path.
#pragma pack(push, 1)
struct sub_3cf43f0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t W
};
#pragma pack(pop)

// Spurious descscan2 entry: no [rax+off] memory access occurs in this function.
// Kept so every descscan2 base register has a declared layout.
#pragma pack(push, 1)
struct sub_3cf43f0_rax {
    std::uint8_t pad0x00[0x1];
    std::uint8_t f1;   // +0x01: std::uint8_t — no actual [rax+1] access in listing
};
#pragma pack(pop)

static_assert(offsetof(sub_3cf43f0_rcx, buffer) == 0x0, "sub_0x3cf43f0 rcx+0x0 field");
static_assert(offsetof(sub_3cf43f0_rcx, end) == 0x8, "sub_0x3cf43f0 rcx+0x8 field");
static_assert(offsetof(sub_3cf43f0_rcx, limit) == 0x10, "sub_0x3cf43f0 rcx+0x10 field");
static_assert(sizeof(sub_3cf43f0_rcx) >= 0x18, "sub_0x3cf43f0 rcx sizeof lower bound");

static_assert(offsetof(sub_3cf43f0_r15, data) == 0x0, "sub_0x3cf43f0 r15+0x0 field");
static_assert(offsetof(sub_3cf43f0_r15, size) == 0x10, "sub_0x3cf43f0 r15+0x10 field");
static_assert(offsetof(sub_3cf43f0_r15, capacity) == 0x18, "sub_0x3cf43f0 r15+0x18 field");
static_assert(sizeof(sub_3cf43f0_r15) >= 0x20, "sub_0x3cf43f0 r15 sizeof lower bound");

static_assert(offsetof(sub_3cf43f0_rsp, f20) == 0x20, "sub_0x3cf43f0 rsp+0x20 field");
static_assert(sizeof(sub_3cf43f0_rsp) >= 0x28, "sub_0x3cf43f0 rsp sizeof lower bound");

static_assert(offsetof(sub_3cf43f0_rax, f1) == 0x1, "sub_0x3cf43f0 rax+0x1 field");
static_assert(sizeof(sub_3cf43f0_rax) >= 0x2, "sub_0x3cf43f0 rax sizeof lower bound");

// Signature (x64 Microsoft ABI). rcx=a0 (object ptr), rdx=new buffer base,
// r8=count1, r9=count2. Return value is the last sub_e935700 result, or 0 on
// the early-exit path where the original leaves RAX undefined.
uintptr_t sub_3cf43f0(void* a0, void* newBuf, uint64_t count1, uint64_t count2);

} // namespace native::helpers
