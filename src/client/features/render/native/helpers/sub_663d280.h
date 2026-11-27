#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_663d280, reverse-engineered from the disassembly
// of [0x663d280, 0x663d376), Minecraft Windows 1.26.62.01. Offsets and widths
// are proven from instruction operands; field names and meanings are inferred
// from the access pattern (release flag, refcounted object with vfptr/refcount/count0xC).
// One struct per base register that is dereferenced (rdx=self, rax=vfptr,
// rdi=refcounted object). Field f<hex> is at offset 0x<hex>; names have been
// given semantic meaning where the access pattern justifies it.

#pragma pack(push, 1)
struct sub_663d280_rdx {
    std::uint8_t pad0x00[0x50];   // +0x00..+0x4f padding (no observed access)
    void* obj50;                  // +0x50: void* R  // refcounted object released when flag58
    std::uint8_t flag58;          // +0x58: std::uint8_t R/W  // release flag (1 = pending release)
    std::uint8_t pad0x59[0xf];    // +0x59..+0x67 padding (no observed access)
    void* obj68;                  // +0x68: void* R  // refcounted object released when flag70
    std::uint8_t flag70;          // +0x70: std::uint8_t R/W  // release flag (1 = pending release)
    std::uint8_t pad0x71[0xf];    // +0x71..+0x7f padding (no observed access)
    void* obj80;                  // +0x80: void* R  // refcounted object released when flag88
    std::uint8_t flag88;          // +0x88: std::uint8_t R/W  // release flag (1 = pending release)
    std::uint8_t pad0x89[0x7];    // +0x89..+0x8f padding (no observed access)
    std::uint64_t field90;        // +0x90: std::uint64_t W  // cleared to 0 at function exit
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_663d280_rax {
    void* slot0;   // +0x00: void* R  // vtable entry 0, called as destructor via sub_eea6040
    void* slot8;   // +0x08: void* R  // vtable entry 1, called as operator delete via sub_eea6040
};
#pragma pack(pop)

#pragma pack(push, 1)
struct sub_663d280_rdi {
    void* vfptr;          // +0x00: void* R  // vtable pointer of the refcounted object
    std::uint32_t refcount;  // +0x08: std::uint32_t RW  // lock inc/dec reference count
    std::uint32_t count0xC;  // +0x0c: std::uint32_t RW  // lock dec secondary count
};
#pragma pack(pop)

static_assert(offsetof(sub_663d280_rdx, obj50) == 0x50, "sub_0x663d280 rdx+0x50 field");
static_assert(offsetof(sub_663d280_rdx, flag58) == 0x58, "sub_0x663d280 rdx+0x58 field");
static_assert(offsetof(sub_663d280_rdx, obj68) == 0x68, "sub_0x663d280 rdx+0x68 field");
static_assert(offsetof(sub_663d280_rdx, flag70) == 0x70, "sub_0x663d280 rdx+0x70 field");
static_assert(offsetof(sub_663d280_rdx, obj80) == 0x80, "sub_0x663d280 rdx+0x80 field");
static_assert(offsetof(sub_663d280_rdx, flag88) == 0x88, "sub_0x663d280 rdx+0x88 field");
static_assert(offsetof(sub_663d280_rdx, field90) == 0x90, "sub_0x663d280 rdx+0x90 field");
static_assert(sizeof(sub_663d280_rdx) >= 0x98, "sub_0x663d280 rdx sizeof lower bound");

static_assert(offsetof(sub_663d280_rax, slot0) == 0x0, "sub_0x663d280 rax+0x0 field");
static_assert(offsetof(sub_663d280_rax, slot8) == 0x8, "sub_0x663d280 rax+0x8 field");
static_assert(sizeof(sub_663d280_rax) >= 0x10, "sub_0x663d280 rax sizeof lower bound");

static_assert(offsetof(sub_663d280_rdi, vfptr) == 0x0, "sub_0x663d280 rdi+0x0 field");
static_assert(offsetof(sub_663d280_rdi, refcount) == 0x8, "sub_0x663d280 rdi+0x8 field");
static_assert(offsetof(sub_663d280_rdi, count0xC) == 0xc, "sub_0x663d280 rdi+0xc field");
static_assert(sizeof(sub_663d280_rdi) >= 0x10, "sub_0x663d280 rdi sizeof lower bound");

// Signature (x64 Microsoft ABI). The object base is read from RDX
// (0x663d286 mov rsi,rdx), i.e. it is the second parameter; RCX (first
// parameter, a1) is never read. Return value is not explicitly set by the
// original, so the lift returns 0.
uintptr_t sub_663d280(void* a1, void* self);

} // namespace native::helpers
