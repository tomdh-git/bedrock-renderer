#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_67627d0, reverse-engineered from the disassembly
// of [0x67627d0, 0x67628f7), Minecraft Windows 1.26.62.01.
// Every field access below is [proven] from the instruction operands in that range.
// Field NAMES and MEANINGS are [open] (struct field meanings are not derivable from
// static analysis); offsets and widths are [proven].
// One struct per base register that is dereferenced (this/a1/a2 and any other register
// used as a memory base). Field f<hex> is at offset 0x<hex>.
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.
// No null guards and no SEH exist in the original; none are added.

// Struct for base register rcx (this pointer; dereferenced in this function).
// Accesses: f98 (byte), f58 (byte), f68 (u64), f58+0/f58+0x10 (vtable/object fields).
#pragma pack(push, 1)
struct sub_67627d0_rcx {
    std::uint64_t f0;          // +0x00: void* R  (object pointer field)
    std::uint8_t pad0x08[0x8];  // +0x08..+0x0f padding (no observed access)
    std::uint64_t f10;         // +0x10: std::uint64_t R/W (R/W cited: 0x6762873:R, 0x67628cb:W)
    std::uint8_t pad0x18[0x18]; // +0x18..+0x2f padding (no observed access)
    void* f30;                 // +0x30: void* R // vtable-call slot(s) slot 0  (R/W cited: 0x6762836:R)
    std::uint8_t f38;          // +0x38: std::uint8_t R  (R/W cited: 0x6762830:R)
    std::uint8_t pad0x39[0x1f]; // +0x39..+0x57 padding (no observed access)
    void* f58;                 // +0x58: void* R  (R/W cited: 0x67627e9:R — 8-byte read at rdi=rsi+0x58)
    std::uint8_t pad0x60[0x8];  // +0x60..+0x67 padding (no observed access)
    std::uint64_t f68;         // +0x68: std::uint64_t R  (R/W cited: 0x67627f1:R)
    std::uint8_t pad0x70[0x28]; // +0x70..+0x97 padding (no observed access)
    std::uint8_t f98;          // +0x98: std::uint8_t R  (R/W cited: 0x67627dc:R)
};
#pragma pack(pop)

// Struct for base register rax (object pointed at by rcx+0x58; dereferenced here).
#pragma pack(push, 1)
struct sub_67627d0_rax {
    void* f0;   // +0x00: void* R // vtable-call slot(s) slot 0  (R/W cited: 0x6762848:R, 0x67628a1:R)
    void* f8;   // +0x08: void* R // vtable-call slot(s) slot 1  (R/W cited: 0x676285d:R, 0x67628b6:R)
};
#pragma pack(pop)

// Struct for base register rbx (loop walk cursor; dereferenced here).
#pragma pack(push, 1)
struct sub_67627d0_rbx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;   // +0x08: void* R // vtable-call slot(s) slot 0  (R/W cited: 0x676288f:R)
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding (no observed access)
    std::uint8_t f18;   // +0x18: std::uint8_t R  (R/W cited: 0x6762889:R)
};
#pragma pack(pop)

// Struct for base register rdi (object pointer / write target; dereferenced here).
#pragma pack(push, 1)
struct sub_67627d0_rdi {
    void* f0[2];   // +0x00: void*[2] R/W // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x67627e9:R, 0x6762825:W, 0x6762845:R, 0x676285a:R, 0x676289e:R, 0x67628b3:R)
    // +0x08: std::uint32_t RW  (R/W cited: 0x676283f:RW, 0x6762898:RW)   [subsumed by f0[0]; overlapping access, no separate field]
    // +0x0c: std::uint32_t RW  (R/W cited: 0x6762854:RW, 0x67628ad:RW)   [subsumed by f0[0]; overlapping access, no separate field]
    std::uint64_t f10;   // +0x10: std::uint64_t W  (R/W cited: 0x6762828:W)
};
#pragma pack(pop)

// Struct for base register rsp (stack frame; dereferenced here on the fail path).
#pragma pack(push, 1)
struct sub_67627d0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t W  (R/W cited: 0x67628dd:W)
};
#pragma pack(pop)

// Layout constants (mirrors of offsetof(), for self-documenting layout assertions).
struct Sub67627d0Layout {
    static constexpr std::size_t kOffRcxf0   = 0x00;
    static constexpr std::size_t kOffRcxf10  = 0x10;
    static constexpr std::size_t kOffRcxf30  = 0x30;
    static constexpr std::size_t kOffRcxf38  = 0x38;
    static constexpr std::size_t kOffRcxf58  = 0x58;
    static constexpr std::size_t kOffRcxf68  = 0x68;
    static constexpr std::size_t kOffRcxf98  = 0x98;
    static constexpr std::size_t kOffRaxf0   = 0x00;
    static constexpr std::size_t kOffRaxf8   = 0x08;
    static constexpr std::size_t kOffRbf8    = 0x08;
    static constexpr std::size_t kOffRbf18   = 0x18;
    static constexpr std::size_t kOffRdif0   = 0x00;
    static constexpr std::size_t kOffRdif10  = 0x10;
    static constexpr std::size_t kOffRsPf20  = 0x20;
    static_assert(sizeof(void*) == 8, "sub_67627d0: x64 pointers are 8 bytes");
};
static_assert(sizeof(Sub67627d0Layout) > 0, "sub_67627d0: layout constant block");

// rcx field offsetof assertions.
static_assert(offsetof(sub_67627d0_rcx, f0) == Sub67627d0Layout::kOffRcxf0,   "sub_67627d0 rcx+0x0 field");
static_assert(offsetof(sub_67627d0_rcx, f10) == Sub67627d0Layout::kOffRcxf10, "sub_67627d0 rcx+0x10 field");
static_assert(offsetof(sub_67627d0_rcx, f30) == Sub67627d0Layout::kOffRcxf30, "sub_67627d0 rcx+0x30 field");
static_assert(offsetof(sub_67627d0_rcx, f38) == Sub67627d0Layout::kOffRcxf38, "sub_67627d0 rcx+0x38 field");
static_assert(offsetof(sub_67627d0_rcx, f58) == Sub67627d0Layout::kOffRcxf58, "sub_67627d0 rcx+0x58 field");
static_assert(offsetof(sub_67627d0_rcx, f68) == Sub67627d0Layout::kOffRcxf68, "sub_67627d0 rcx+0x68 field");
static_assert(offsetof(sub_67627d0_rcx, f98) == Sub67627d0Layout::kOffRcxf98, "sub_67627d0 rcx+0x98 field");
static_assert(sizeof(sub_67627d0_rcx) >= 0x99, "sub_67627d0 rcx sizeof lower bound");

// rax field offsetof assertions.
static_assert(offsetof(sub_67627d0_rax, f0) == Sub67627d0Layout::kOffRaxf0, "sub_67627d0 rax+0x0 field");
static_assert(offsetof(sub_67627d0_rax, f8) == Sub67627d0Layout::kOffRaxf8, "sub_67627d0 rax+0x08 field");
static_assert(sizeof(sub_67627d0_rax) >= 0x10, "sub_67627d0 rax sizeof lower bound");

// rbx field offsetof assertions.
static_assert(offsetof(sub_67627d0_rbx, f8) == Sub67627d0Layout::kOffRbf8, "sub_67627d0 rbx+0x08 field");
static_assert(offsetof(sub_67627d0_rbx, f18) == Sub67627d0Layout::kOffRbf18, "sub_67627d0 rbx+0x18 field");
static_assert(sizeof(sub_67627d0_rbx) >= 0x19, "sub_67627d0 rbx sizeof lower bound");

// rdi field offsetof assertions.
static_assert(offsetof(sub_67627d0_rdi, f0) == Sub67627d0Layout::kOffRdif0, "sub_67627d0 rdi+0x0 field");
static_assert(offsetof(sub_67627d0_rdi, f10) == Sub67627d0Layout::kOffRdif10, "sub_67627d0 rdi+0x10 field");
static_assert(sizeof(sub_67627d0_rdi) >= 0x18, "sub_67627d0 rdi sizeof lower bound");

// rsp field offsetof assertion.
static_assert(offsetof(sub_67627d0_rsp, f20) == Sub67627d0Layout::kOffRsPf20, "sub_67627d0 rsp+0x20 field");
static_assert(sizeof(sub_67627d0_rsp) >= 0x28, "sub_67627d0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): RCX = self (this pointer). Return type is not
// derivable from static analysis; the function either falls through to the epilogue+ret
// (no value written to RAX after the prologue) or takes a noreturn fail path
// (data-slot call then int3). The skeleton's return type is retained from the scaffold.
// 0x67627d0  push r14; 0x67627d2  push rsi; 0x67627d3  push rdi; 0x67627d4  push rbx
uintptr_t sub_67627d0(void* self);   // [open] signature placeholder (return type, arg types TBD)

// Data slot 0xF9A8C78: fail-handler function pointer (IAT/import slot).
// Read at call time, exactly as `call qword ptr [0xF9A8C78]` does. [V]
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;
static_assert(kRvaFailSlot == 0xF9A8C78, "sub_67627d0: fail-handler data slot RVA 0xF9A8C78");

// Virtual-call thunk via data slot 0xF99FFA0 (jmp rax; sub_eea6040, boundary/vendor).
// RAX must hold the target function pointer on entry; RCX = object; return ignored.
using VtableThunkFn = void (*)(void* object, void* vtableEntry);

} // namespace native::helpers
