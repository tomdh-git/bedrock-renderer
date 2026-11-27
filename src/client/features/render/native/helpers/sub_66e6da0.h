#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_66e6da0, reverse-engineered from the disassembly
// of [0x66e6da0, 0x66e6ebb), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
//
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// rcx/self is copied to rsi and returned; only self+8 is used (as the dest for sub_67d0ff0).
#pragma pack(push, 1)
struct sub_66e6da0_rcx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    std::uint8_t f8;   // // +0x08: std::uint8_t R  (R/W cited: 0x66e6e1c:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// a1: a refcounted-object handle. f0@0 is copied to the stack src object; f8@8 is the
// refcounted referent whose strong refcount (+0x8) is addrefed/released.
#pragma pack(push, 1)
struct sub_66e6da0_rdx {
    void* f0;   // // +0x00: void* R  (R/W cited: 0x66e6dd5:R)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e6dc0:R, 0x66e6dcd:R)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
// a2: a refcounted-object handle. f0@0/f8@8 copied to the stack src object; f8@8's referent
// is addrefed; f10@0x10 (16 bytes) and f20@0x20 copied to the stack src object.
#pragma pack(push, 1)
struct sub_66e6da0_r8 {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e6dfc:R)
    void* f8;   // // +0x08: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e6de7:R, 0x66e6df4:R)
    std::uint64_t f10[2];   // // +0x10: std::uint64_t[2] R  (R/W cited: 0x66e6e09:R)
    void* f20;   // // +0x20: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e6e13:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The refcounted referent pointed to by a1->f8 / a2->f8: f0@0 is the vtable pointer, f8@8 is
// the strong refcount (lock inc/dec).
#pragma pack(push, 1)
struct sub_66e6da0_rax {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e6e38:R, 0x66e6e6d:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t RW  (R/W cited: 0x66e6dc9:RW, 0x66e6df0:RW, 0x66e6e4d:R, 0x66e6e82:R)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// The refcounted referent: f0@0 vtable pointer, f8@8 strong refcount, fc@0xc secondary refcount.
// vfptr[0] = *(void**)f0 is the destructor, vfptr[1] = *(void**)(f0+8) is the deallocator,
// both invoked through the sub_eea6040 (jmp rax) vendor thunk at data slot 0xF99FFA0.
#pragma pack(push, 1)
struct sub_66e6da0_rdi {
    void* f0;   // // +0x00: void* R // vtable-call slot(s) slot 0,slot 1  (R/W cited: 0x66e6e35:R, 0x66e6e4a:R, 0x66e6e6a:R, 0x66e6e7f:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t RW  (R/W cited: 0x66e6e2f:RW, 0x66e6e64:RW)
    std::uint32_t fc;   // // +0x0c: std::uint32_t RW  (R/W cited: 0x66e6e44:RW, 0x66e6e79:RW)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// Stack slots of this frame. +0x20..+0x50 hold the sub_67d0ff0_rdx src object built from a1/a2;
// +0x60 holds the stack cookie value __security_cookie ^ rsp.
#pragma pack(push, 1)
struct sub_66e6da0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint8_t f20;   // // +0x20: std::uint8_t R/W  (R/W cited: 0x66e6dbb:W, 0x66e6dd8:W, 0x66e6e20:R)
    std::uint8_t pad0x21[0x7];   // +0x21..+0x27 padding (no observed access)
    void* f28;   // // +0x28: void* R/W // vtable-call slot(s) slot 0  (R/W cited: 0x66e6ddd:W, 0x66e6e5a:R)
    std::uint8_t f30;   // // +0x30: std::uint8_t W  (R/W cited: 0x66e6de2:W, 0x66e6dff:W)
    std::uint8_t pad0x31[0x7];   // +0x31..+0x37 padding (no observed access)
    std::uint8_t f38;   // // +0x38: std::uint8_t W  (R/W cited: 0x66e6e04:W)
    std::uint8_t pad0x39[0x7];   // +0x39..+0x3f padding (no observed access)
    std::uint8_t f40;   // // +0x40: std::uint8_t W  (R/W cited: 0x66e6e0e:W)
    std::uint8_t pad0x41[0xf];   // +0x41..+0x4f padding (no observed access)
    std::uint8_t f50;   // // +0x50: std::uint8_t W  (R/W cited: 0x66e6e17:W)
    std::uint8_t pad0x51[0xf];   // +0x51..+0x5f padding (no observed access)
    std::uint64_t f60;   // // +0x60: std::uint64_t R/W  (R/W cited: 0x66e6db3:W, 0x66e6e8f:R, 0x66e6ead:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_66e6da0_rcx, f8) == 0x8, "sub_0x66e6da0 rcx+0x8 field");
static_assert(sizeof(sub_66e6da0_rcx) >= 0x9, "sub_0x66e6da0 rcx sizeof lower bound");

static_assert(offsetof(sub_66e6da0_rdx, f0) == 0x0, "sub_0x66e6da0 rdx+0x0 field");
static_assert(offsetof(sub_66e6da0_rdx, f8) == 0x8, "sub_0x66e6da0 rdx+0x8 field");
static_assert(sizeof(sub_66e6da0_rdx) >= 0x10, "sub_0x66e6da0 rdx sizeof lower bound");

static_assert(offsetof(sub_66e6da0_r8, f0) == 0x0, "sub_0x66e6da0 r8+0x0 field");
static_assert(offsetof(sub_66e6da0_r8, f8) == 0x8, "sub_0x66e6da0 r8+0x8 field");
static_assert(offsetof(sub_66e6da0_r8, f10) == 0x10, "sub_0x66e6da0 r8+0x10 field");
static_assert(offsetof(sub_66e6da0_r8, f20) == 0x20, "sub_0x66e6da0 r8+0x20 field");
static_assert(sizeof(sub_66e6da0_r8) >= 0x28, "sub_0x66e6da0 r8 sizeof lower bound");

static_assert(offsetof(sub_66e6da0_rax, f0) == 0x0, "sub_0x66e6da0 rax+0x0 field");
static_assert(offsetof(sub_66e6da0_rax, f8) == 0x8, "sub_0x66e6da0 rax+0x8 field");
static_assert(sizeof(sub_66e6da0_rax) >= 0xc, "sub_0x66e6da0 rax sizeof lower bound");

static_assert(offsetof(sub_66e6da0_rdi, f0) == 0x0, "sub_0x66e6da0 rdi+0x0 field");
static_assert(offsetof(sub_66e6da0_rdi, f8) == 0x8, "sub_0x66e6da0 rdi+0x8 field");
static_assert(offsetof(sub_66e6da0_rdi, fc) == 0xc, "sub_0x66e6da0 rdi+0xc field");
static_assert(sizeof(sub_66e6da0_rdi) >= 0x10, "sub_0x66e6da0 rdi sizeof lower bound");

static_assert(offsetof(sub_66e6da0_rsp, f20) == 0x20, "sub_0x66e6da0 rsp+0x20 field");
static_assert(offsetof(sub_66e6da0_rsp, f28) == 0x28, "sub_0x66e6da0 rsp+0x28 field");
static_assert(offsetof(sub_66e6da0_rsp, f30) == 0x30, "sub_0x66e6da0 rsp+0x30 field");
static_assert(offsetof(sub_66e6da0_rsp, f38) == 0x38, "sub_0x66e6da0 rsp+0x38 field");
static_assert(offsetof(sub_66e6da0_rsp, f40) == 0x40, "sub_0x66e6da0 rsp+0x40 field");
static_assert(offsetof(sub_66e6da0_rsp, f50) == 0x50, "sub_0x66e6da0 rsp+0x50 field");
static_assert(offsetof(sub_66e6da0_rsp, f60) == 0x60, "sub_0x66e6da0 rsp+0x60 field");
static_assert(sizeof(sub_66e6da0_rsp) >= 0x68, "sub_0x66e6da0 rsp sizeof lower bound");

// Stack cookie global (MSVC __security_cookie), read via absolute address [0x1230A0C0].
extern "C" std::uintptr_t __security_cookie;

// x64 Microsoft ABI: rcx = self (returned unchanged), rdx = a1 handle, r8 = a2 handle.
// Returns self (rax = rsi = rcx). On stack-cookie mismatch calls sub_e951550 (__report_gsfailure,
// noreturn). Builds a sub_67d0ff0_rdx src object on the stack from a1/a2 fields and copies it
// into self+8 (a sub_67d0ff0_rcx) via sub_67d0ff0, addrefing a1->f8/a2->f8 referents around it.
void* sub_66e6da0(void* self, sub_66e6da0_rdx* a1, sub_66e6da0_r8* a2);

} // namespace native::helpers
