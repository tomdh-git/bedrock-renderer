#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_56b84e0, reverse-engineered from the disassembly
// of [0x56b84e0, 0x56b85f6), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced as an object base.
// Field f<hex> is at offset 0x<hex>. The struct is packed (#pragma pack(1)) so every
// declared field sits exactly at its observed offset and offsetof() matches it. The real
// object may have compiler-inserted alignment padding, so sizeof is a lower bound.

// Struct for base register rcx (the `self` / FrameBuilder object, copied to rsi).
// Dereferenced via 8-byte stores at +0x00, +0x08 and +0x10.
// (R/W cited: 0x56b857f:W, 0x56b8582:W, 0x56b8589:W, 0x56b85bf:W)
#pragma pack(push, 1)
struct sub_56b84e0_rcx {
    void* buffer;      // +0x00: void* W   start of the allocated frame buffer   (0x56b857f:W)
    void* bufferEnd;   // +0x08: void* W   end/current pointer                    (0x56b8582:W, 0x56b85bf:W)
    void* frameEnd;    // +0x10: void* W   end = start + count*0x248              (0x56b8589:W)
};
#pragma pack(pop)

// Struct for base register r8 (source cursor cell). Dereferenced at +0x00.
// (R cited: 0x56b8594:R)
#pragma pack(push, 1)
struct sub_56b84e0_r8 {
    void* current;   // +0x00: void* R  current source pointer
};
#pragma pack(pop)

// Struct for base register r9 (source end cell). Dereferenced at +0x00.
// (R cited: 0x56b8591:R)
#pragma pack(push, 1)
struct sub_56b84e0_r9 {
    void* end;   // +0x00: void* R  source end pointer
};
#pragma pack(pop)

// Struct for base register rax when it holds the heap object (read via [rax] then [rax+8]).
// Dereferenced at +0x00 (vtable pointer) and +0x08 (vtable slot 1 = allocator).
// (R cited: 0x56b8536:R, 0x56b8539:R, 0x56b8567:R, 0x56b856a:R)
#pragma pack(push, 1)
struct sub_56b84e0_rax {
    void* vtable;      // +0x00: void* R  heap vtable pointer        (0x56b8536:R, 0x56b8567:R)
    void* allocFunc;   // +0x08: void* R  vtable slot 1 = alloc func (0x56b8539:R, 0x56b856a:R)
};
#pragma pack(pop)

// Note: r14, rsp and rbp are NOT dereferenced as object bases in this function
// (their uses are register arithmetic / frame-pointer stack slots), so they have
// no state struct here. r14 holds count*0x248; rbp is the frame pointer.

static_assert(offsetof(sub_56b84e0_rcx, buffer) == 0x0, "sub_0x56b84e0 rcx+0x0 field");
static_assert(offsetof(sub_56b84e0_rcx, bufferEnd) == 0x8, "sub_0x56b84e0 rcx+0x8 field");
static_assert(offsetof(sub_56b84e0_rcx, frameEnd) == 0x10, "sub_0x56b84e0 rcx+0x10 field");
static_assert(sizeof(sub_56b84e0_rcx) >= 0x18, "sub_0x56b84e0 rcx sizeof lower bound");

static_assert(offsetof(sub_56b84e0_r8, current) == 0x0, "sub_0x56b84e0 r8+0x0 field");
static_assert(sizeof(sub_56b84e0_r8) >= 0x8, "sub_0x56b84e0 r8 sizeof lower bound");

static_assert(offsetof(sub_56b84e0_r9, end) == 0x0, "sub_0x56b84e0 r9+0x0 field");
static_assert(sizeof(sub_56b84e0_r9) >= 0x8, "sub_0x56b84e0 r9 sizeof lower bound");

static_assert(offsetof(sub_56b84e0_rax, vtable) == 0x0, "sub_0x56b84e0 rax+0x0 field");
static_assert(offsetof(sub_56b84e0_rax, allocFunc) == 0x8, "sub_0x56b84e0 rax+0x8 field");
static_assert(sizeof(sub_56b84e0_rax) >= 0x10, "sub_0x56b84e0 rax sizeof lower bound");

// External callees used by this function (all native symbols / boundary functions).
// sub_eea6040 is a vendor thunk ([data_f99ffa0]) that tail-jumps to rax (vtable[1]);
// the allocator is therefore invoked through the heap vtable slot directly.
extern "C" void* sub_75b60();                                    // boundary=stl, noreturn ("vector too long")
extern "C" void sub_8da480(void* dest, const void* src);         // copies a 0x248-byte struct
extern "C" void sub_9bc830(uint64_t size);                       // boundary=alloc, noreturn (alloc failure report)

// Signature (x64 Microsoft ABI):
//   rcx = self (FrameBuilder*), rdx = count, r8 = source-cursor cell, r9 = source-end cell
//   return = rax (value left by the copy loop, i.e. end - 0x248 on the success path)
uintptr_t sub_56b84e0(void* self, uint64_t count,
                      sub_56b84e0_r8* srcCur, sub_56b84e0_r9* srcEnd);

} // namespace native::helpers
