#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67577c0, reverse-engineered from the disassembly
// of [0x67577c0, 0x67578cf), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
//
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.

// Struct for base register rcx (the 'this' / BgfxFrameBuilder pointer) [proven base, [open] name/meaning]
// Dereferenced: +0x00 (release-list head node), +0x18 (single callback target),
// +0x28 (chain list head, f238/f240), +0x30 (simple chain head, f10).
//   0x67577d8  mov rdi,[rcx]                R +0x0  (release list head)
//   0x6757832  mov rdx,[rsi+0x30]           R +0x30 (simple chain head)   [rsi == rcx == self]
//   0x6757863  mov rdx,[rsi+0x28]           R +0x28 (chain list head)
//   0x675786c  mov rdx,[rsi+0x18]           R +0x18 (single callback target)
#pragma pack(push, 1)
struct sub_67577c0_rcx {
    void* firstNode;    // // +0x00: void* R  head of node-release list  (R/W cited: 0x67577d8:R)
    std::uint8_t pad0x08[0x10];   // +0x08..+0x17 padding (no observed access)
    void* singleTarget; // // +0x18: void* R  single callback target     (R/W cited: 0x675786c:R)
    std::uint8_t pad0x20[0x8];   // +0x20..+0x27 padding (no observed access)
    void* chainList;    // // +0x28: void* R  chain list head            (R/W cited: 0x6757863:R)
    void* simpleChain;  // // +0x30: void* R  simple chain head          (R/W cited: 0x6757832:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// rax holds vfptr pointers and temporary values.
//   0x67577e0  mov rax,[rdi]      R +0x0  (node vfptr)
//   0x67577e3  mov rax,[rax]      R +0x0  (vfptr slot 0)
//   0x67577f8  mov rax,[rcx]      R +0x0  (global object vfptr)
//   0x67577fb  mov rax,[rax+0x10] R +0x10 (vfptr slot 2)
//   0x6757829  mov [rax],0        W +0x0  (null out node->f18 target)
#pragma pack(push, 1)
struct sub_67577c0_rax {
    void* vfptr;    // // +0x00: void* R/RW/W  vfptr pointer / vfptr slot reads  (R/W cited: 0x67577dd:RW, 0x67577e0:R, 0x67577e3:R, 0x67577f8:R, 0x6757829:W)
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    void* vfptrSlot2;   // // +0x10: void* R  vfptr slot 2  (R/W cited: 0x67577fb:R, 0x6757853:R, 0x675787f:R, 0x67578c2:R)
};
#pragma pack(pop)

// Struct for base register rbp (dereferenced in this function) [proven base, [open] name/meaning]
// rbp is the frame pointer, written at prologue only.
//   0x67577cd  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE  W +0x0
#pragma pack(push, 1)
struct sub_67577c0_rbp {
    std::uint64_t frameCookie;   // // +0x00: std::uint64_t W  stack frame cookie (R/W cited: 0x67577cd:W)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// rbx holds the next-node pointer (computed as node->f8 - 8, or 0 if node->f8 == 0).
//   0x6757811  mov rcx,[rdi+8]      R +0x8   (rbx aliases rdi as a node pointer)
//   0x6757815  mov rax,[rdi+0x18]   R +0x18  (null-out target)
//   0x67578a8  mov rdi,[rdx+0x238]  R +0x238 (chain next, when rbx used as chain node)
//   0x67578af  cmp byte [rdx+0x240],1 R +0x240 (flag byte)
#pragma pack(push, 1)
struct sub_67577c0_rbx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* nextRaw;    // // +0x08: void* R  node->f8, raw next-pointer field  (R/W cited: 0x6757811:R)
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    void* nullOut;    // // +0x18: void* R  node->f18, pointer to null out  (R/W cited: 0x6757815:R)
    std::uint8_t pad0x20[0x218];   // +0x20..+0x237 padding (no observed access)
    void* chainNext;  // // +0x238: void* R  chain-list next node  (R/W cited: 0x67578a8:R)
    std::uint8_t flag;    // // +0x240: std::uint8_t R  chain flag byte  (R/W cited: 0x67578af:R)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// rdi is the current node in the release loop, and a chain node in the second loop.
//   0x67577e0  mov rax,[rdi]        R +0x0  (node vfptr)
//   0x6757840  mov rdi,[rdx+0x10]   R +0x10 (rdi as chain node -> f10)
#pragma pack(push, 1)
struct sub_67577c0_rdi {
    void* vfptr;    // // +0x00: void* R  node vfptr  (R/W cited: 0x67577e0:R, 0x67577f8:R, 0x6757850:R, 0x675787c:R, 0x67578bf:R)
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding (no observed access)
    void* chainNext;   // // +0x10: void* R  chain next (f10)  (R/W cited: 0x6757840:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// rsp+0x20 is the frame pointer slot (address of rbp).
//   0x67577c8  lea rbp,[rsp+0x20]   R +0x20
#pragma pack(push, 1)
struct sub_67577c0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint8_t framePtrSlot;   // // +0x20: std::uint8_t R  (R/W cited: 0x67577c8:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_67577c0_rcx, firstNode) == 0x0, "sub_0x67577c0 rcx+0x0 field");
static_assert(offsetof(sub_67577c0_rcx, singleTarget) == 0x18, "sub_0x67577c0 rcx+0x18 field");
static_assert(offsetof(sub_67577c0_rcx, chainList) == 0x28, "sub_0x67577c0 rcx+0x28 field");
static_assert(offsetof(sub_67577c0_rcx, simpleChain) == 0x30, "sub_0x67577c0 rcx+0x30 field");
static_assert(sizeof(sub_67577c0_rcx) >= 0x38, "sub_0x67577c0 rcx sizeof lower bound");

static_assert(offsetof(sub_67577c0_rax, vfptr) == 0x0, "sub_0x67577c0 rax+0x0 field");
static_assert(offsetof(sub_67577c0_rax, vfptrSlot2) == 0x10, "sub_0x67577c0 rax+0x10 field");
static_assert(sizeof(sub_67577c0_rax) >= 0x18, "sub_0x67577c0 rax sizeof lower bound");

static_assert(offsetof(sub_67577c0_rbp, frameCookie) == 0x0, "sub_0x67577c0 rbp+0x0 field");
static_assert(sizeof(sub_67577c0_rbp) >= 0x8, "sub_0x67577c0 rbp sizeof lower bound");

static_assert(offsetof(sub_67577c0_rbx, nextRaw) == 0x8, "sub_0x67577c0 rbx+0x8 field");
static_assert(offsetof(sub_67577c0_rbx, nullOut) == 0x18, "sub_0x67577c0 rbx+0x18 field");
static_assert(offsetof(sub_67577c0_rbx, chainNext) == 0x238, "sub_0x67577c0 rbx+0x238 field");
static_assert(offsetof(sub_67577c0_rbx, flag) == 0x240, "sub_0x67577c0 rbx+0x240 field");
static_assert(sizeof(sub_67577c0_rbx) >= 0x241, "sub_0x67577c0 rbx sizeof lower bound");

static_assert(offsetof(sub_67577c0_rdi, vfptr) == 0x0, "sub_0x67577c0 rdi+0x0 field");
static_assert(offsetof(sub_67577c0_rdi, chainNext) == 0x10, "sub_0x67577c0 rdi+0x10 field");
static_assert(sizeof(sub_67577c0_rdi) >= 0x18, "sub_0x67577c0 rdi sizeof lower bound");

static_assert(offsetof(sub_67577c0_rsp, framePtrSlot) == 0x20, "sub_0x67577c0 rsp+0x20 field");
static_assert(sizeof(sub_67577c0_rsp) >= 0x21, "sub_0x67577c0 rsp sizeof lower bound");

// Game-image data slot [0x1233E1A8] holds a pointer to an interface object (the allocator).
// Its vfptr slot 2 (offset 0x10) is the callback invoked on each released/chained node.
// VA = imageBase + 0x1233E1A8.

// Signature (x64 Microsoft ABI) - [proven] from the prologue: rcx is the 'this' pointer
// (BgfxFrameBuilder*, copied to rsi at 0x67577d5). Return value is don't-care (endFrame
// does not explicitly set RAX on any exit path); 0 is returned.
// 0x67577c0  push rbp; 0x67577c1  push rsi; 0x67577c2  push rdi; 0x67577c3  push rbx
uintptr_t sub_67577c0(void* self);   // 'this' = self (rcx), return value don't-care

} // namespace native::helpers
