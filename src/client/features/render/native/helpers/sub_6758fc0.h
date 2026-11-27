#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// sub_6758fc0 == BgfxFrameBuilder::endFrame (Minecraft Windows 1.26.62.01),
// disassembly [0x6758fc0, 0x67590bf). x64 Microsoft ABI: RCX = this (self); result in RAX.
//
// Packed views over the dereferenced bases. Offsets are [proven] from the instruction
// operands of [0x6758fc0, 0x67590bf); field names and meanings are [derived] from how
// each field is used. Offsets are never moved. sizeof is a lower bound: the real
// objects may have compiler-inserted alignment padding.

// The object passed in RCX (copied to RSI at 0x6758fce).
//   +0x08 heap   void*  R   0x6758fd1 mov rcx,[rcx+8]   /   0x6759052 mov rcx,[rsi+8]
//   +0x10 count  u64   R   0x6759056 mov rax,[rsi+0x10]  (entries are 0x140 bytes)
//   +0x18 first  void*  R   0x6758fde mov rdi,[rsi+0x18]  (entry cursor)
//   +0x20 last   void*  R   0x6758fe2 mov rbx,[rsi+0x20]  (end sentinel)
#pragma pack(push, 1)
struct sub_6758fc0_this {
    std::uint8_t pad0x00[0x8];
    void* heap;          // +0x08  [R]
    std::uint64_t count; // +0x10  [R]
    void* first;         // +0x18  [R]
    void* last;          // +0x20  [R]
};
#pragma pack(pop)

// One entry of the entry array (base register RDI); entries are 0x140 bytes apart.
//   +0xE8 block   void*   R   0x6759016 lea r14,[rdi+0xE8] / 0x675901d mov rcx,[r14]
//   +0xF8 block_end void* R   0x6759025 mov rdx,[rdi+0xF8]
//   +0x100 flag   u8     R   0x675900d cmp byte ptr [rdi+0x100],1
#pragma pack(push, 1)
struct sub_6758fc0_entry {
    std::uint8_t pad0x00[0xe8];
    void* block;         // +0xe8  [R]
    std::uint8_t pad0xf0[0x8];   // +0xf0..+0xf7
    void* block_end;     // +0xf8  [R]
    std::uint8_t flag;   // +0x100 [R]
};
#pragma pack(pop)

// Object pointed to by entry+0xE8 (base register R14 = RDI + 0xE8).
//   +0x00 block   void*  R/W  0x675901d:R   /   0x6758ff5:W  (movups [r14], xmm6==0)
//   +0x08 pad0x08 void*  W    0x6758ff5:W  (movups [r14], xmm6==0, high qword)
//   +0x10 limit   u64   W    0x6758ff9 mov qword ptr [r14+0x10],0
#pragma pack(push, 1)
struct sub_6758fc0_handle {
    void* block;         // +0x00  [R/W]
    void* pad0x08;       // +0x08  [W]
    std::uint64_t limit; // +0x10 [W]
};
#pragma pack(pop)

// Stack slots (base register RSP).
//   +0x20 home   u64   W   0x67590a5 mov qword ptr [rsp+0x20],0  (dead home-slot store)
//   +0x30 xmm6   u8[16] R/W 0x6758fc9:W / 0x6759083:R / 0x6759096:R  (callee-saved slot)
#pragma pack(push, 1)
struct sub_6758fc0_stack {
    std::uint8_t pad0x00[0x20];
    std::uint64_t home;          // +0x20  [W]
    std::uint8_t pad0x28[0x8];
    std::uint8_t xmm6[16];       // +0x30  [R/W]
};
#pragma pack(pop)

// Data slot used by the corruption path: 0x67590b8 call qword ptr [0xF9A8C78].
struct sub_6758fc0Layout {
    static_assert(sizeof(void*) == 8, "sub_6758fc0: pointer-sized fields (x64)");
    static constexpr std::uintptr_t kFailSlotRva = 0xF9A8C78;  // call qword ptr [0xF9A8C78]
    static_assert(kFailSlotRva == 0xF9A8C78, "sub_6758fc0: fail data slot RVA 0xF9A8C78");
};

static_assert(offsetof(sub_6758fc0_this, heap) == 0x8, "sub_6758fc0 this+0x8 heap");
static_assert(offsetof(sub_6758fc0_this, count) == 0x10, "sub_6758fc0 this+0x10 count");
static_assert(offsetof(sub_6758fc0_this, first) == 0x18, "sub_6758fc0 this+0x18 first");
static_assert(offsetof(sub_6758fc0_this, last) == 0x20, "sub_6758fc0 this+0x20 last");
static_assert(sizeof(sub_6758fc0_this) >= 0x28, "sub_6758fc0_this sizeof lower bound");

static_assert(offsetof(sub_6758fc0_entry, block) == 0xe8, "sub_6758fc0 entry+0xe8 block");
static_assert(offsetof(sub_6758fc0_entry, block_end) == 0xf8, "sub_6758fc0 entry+0xf8 block_end");
static_assert(offsetof(sub_6758fc0_entry, flag) == 0x100, "sub_6758fc0 entry+0x100 flag");
static_assert(sizeof(sub_6758fc0_entry) >= 0x101, "sub_6758fc0_entry sizeof lower bound");

static_assert(offsetof(sub_6758fc0_handle, block) == 0x0, "sub_6758fc0 handle+0x0 block");
static_assert(offsetof(sub_6758fc0_handle, pad0x08) == 0x8, "sub_6758fc0 handle+0x8 pad0x08");
static_assert(offsetof(sub_6758fc0_handle, limit) == 0x10, "sub_6758fc0 handle+0x10 limit");
static_assert(sizeof(sub_6758fc0_handle) >= 0x18, "sub_6758fc0_handle sizeof lower bound");

static_assert(offsetof(sub_6758fc0_stack, home) == 0x20, "sub_6758fc0 stack+0x20 home");
static_assert(offsetof(sub_6758fc0_stack, xmm6) == 0x30, "sub_6758fc0 stack+0x30 xmm6");
static_assert(sizeof(sub_6758fc0_stack) >= 0x40, "sub_6758fc0_stack sizeof lower bound");

// Signature (x64 Microsoft ABI) [decided]: RCX = this (self); RAX = result of the tail
// call to native::sub_e935700 on every returning path. On the early-exit path
// (0x6759096, *(self+0x8) == 0) the original never writes RAX, so its value is whatever
// the caller left in RAX at entry and is not specified by this function; the lift
// returns nullptr on that path.
void* sub_6758fc0(void* self);

} // namespace native::helpers
