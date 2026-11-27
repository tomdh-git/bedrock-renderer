#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_66982a0, reverse-engineered from the disassembly
// of [0x66982a0, 0x66983ab), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are assigned from usage patterns.
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (the 'this' pointer) [proven base]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.
#pragma pack(push, 1)
struct sub_66982a0_rcx {
    void* vtable;                    // +0x00: vtable pointer (R: 0x669835b, 0x6698370)
    struct RefCounted* next;         // +0x08: pointer to next RefCounted in chain (R: 0x669834c, RW: 0x6698355)
    // +0x0c: refcount (RW: 0x669836a) - overlaps with next, accessed as dword at +0xc
    std::uint8_t pad0x10[0x8];       // +0x10..+0x17 padding (no observed access)
    struct RefCounted* resource1;    // +0x18: first managed resource (R: 0x6698318)
    std::uint8_t pad0x20[0x208];     // +0x20..+0x227 padding (no observed access)
    void* buffer;                    // +0x228: dynamic buffer pointer (R: 0x66982c3, W: 0x6698311)
    std::uint8_t pad0x230[0x8];      // +0x230..+0x237 padding (no observed access)
    std::uint64_t buffer_size;       // +0x238: buffer size / capacity (W: 0x66982fb)
    std::uint64_t buffer_capacity;   // +0x240: buffer capacity (R: 0x66982b6, W: 0x6698306)
    std::uint8_t initialized;        // +0x248: initialization flag (R: 0x66982a6)
};
#pragma pack(pop)

// RefCounted object layout (referenced at rcx+0x18 and rcx+0x08)
#pragma pack(push, 1)
struct RefCounted {
    void* vtable;                    // +0x00: vtable (R: 0x6698327, 0x669833c, 0x669835b, 0x6698370)
    std::uint32_t strong_refs;       // +0x08: strong reference count (RW: 0x6698321, 0x6698355)
    std::uint32_t weak_refs;         // +0x0c: weak reference count (RW: 0x6698336, 0x669836a)
};
#pragma pack(pop)

// Struct for base register rsp (stack frame) [proven base]
#pragma pack(push, 1)
struct sub_66982a0_rsp {
    std::uint8_t pad0x00[0x20];      // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;               // +0x20: error handler arg (W: 0x6698391)
};
#pragma pack(pop)

static_assert(offsetof(sub_66982a0_rcx, vtable) == 0x0, "sub_0x66982a0 rcx+0x0 field");
static_assert(offsetof(sub_66982a0_rcx, next) == 0x8, "sub_0x66982a0 rcx+0x8 field");
static_assert(offsetof(sub_66982a0_rcx, resource1) == 0x18, "sub_0x66982a0 rcx+0x18 field");
static_assert(offsetof(sub_66982a0_rcx, buffer) == 0x228, "sub_0x66982a0 rcx+0x228 field");
static_assert(offsetof(sub_66982a0_rcx, buffer_size) == 0x238, "sub_0x66982a0 rcx+0x238 field");
static_assert(offsetof(sub_66982a0_rcx, buffer_capacity) == 0x240, "sub_0x66982a0 rcx+0x240 field");
static_assert(offsetof(sub_66982a0_rcx, initialized) == 0x248, "sub_0x66982a0 rcx+0x248 field");
static_assert(sizeof(sub_66982a0_rcx) >= 0x249, "sub_0x66982a0 rcx sizeof lower bound");

static_assert(offsetof(RefCounted, vtable) == 0x0, "RefCounted vtable field");
static_assert(offsetof(RefCounted, strong_refs) == 0x8, "RefCounted strong_refs field");
static_assert(offsetof(RefCounted, weak_refs) == 0xc, "RefCounted weak_refs field");
static_assert(sizeof(RefCounted) >= 0x10, "RefCounted sizeof lower bound");

static_assert(offsetof(sub_66982a0_rsp, f20) == 0x20, "sub_0x66982a0 rsp+0x20 field");
static_assert(sizeof(sub_66982a0_rsp) >= 0x28, "sub_0x66982a0 rsp sizeof lower bound");

// Forward declarations for callees
extern "C" void sub_e935700(void* ptr, std::uint64_t new_size, void* old_ptr, void* allocator);
using VtableDtor0 = void(__fastcall*)(RefCounted*);
using VtableDtor1 = void(__fastcall*)(RefCounted*);
using ErrorHandler = void(__fastcall*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t);

// Signature (x64 Microsoft ABI): sub_66982a0(rcx=this)
// Returns: void (tail calls or returns 0)
void sub_66982a0(sub_66982a0_rcx* self);

} // namespace native::helpers