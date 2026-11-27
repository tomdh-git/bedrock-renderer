#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_c2625e0, reverse-engineered from the disassembly
// of [0xc2625e0, 0xc262710), Minecraft Windows 1.26.62.01. [proven] offsets and
// widths come straight from the instruction operands; field NAMES and MEANINGS are
// [open]. One struct per base register that is dereferenced (rcx/rdx/r8/r14/rax/rbp/rsp/rsi).
//
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.

// Forward declaration: r14 is the refcounted target object loaded from rdx+0x8.
struct sub_c2625e0_r14;

// Base register rcx: allocator interface object loaded from [0x01233E1A8].
//   0xc262653  mov rcx,[0x01233E1A8]
//   0xc26265a  mov rax,[rcx]           R +0x0 8B (dead; result overwritten by the call)
#pragma pack(push, 1)
struct sub_c2625e0_rcx {
    void* f0;   // +0x00: void* R  (0xc26265a)
};
#pragma pack(pop)

// Base register rdx: argument a1.
//   0xc262622  mov r14,[rdx]           R +0x00 8B
//   0xc262609  mov rax,[rdx+0x8]       R +0x08 8B  (refcounted-target pointer)
//   0xc262612  lock inc dword [rax+8]  RW +0x08 4B of the *pointee*
//   0xc262616  mov rax,[rdx+0x8]       R +0x08 8B
#pragma pack(push, 1)
struct sub_c2625e0_rdx {
    void* f0;               // +0x00: void* R  (0xc262622)
    sub_c2625e0_r14* f8;    // +0x08: pointer R  (0xc262609, 0xc262616)
};
#pragma pack(pop)

// Base register r8: argument a2.
//   0xc262625  mov rbx,[r8]            R +0x00 8B
#pragma pack(push, 1)
struct sub_c2625e0_r8 {
    void* f0;   // +0x00: void* R  (0xc262625)
};
#pragma pack(pop)

// Base register r14: refcounted target object (a1->f8).
//   0xc2626c7  mov rax,[r14]           R +0x00 8B  (vtable pointer, slot 0)
//   0xc2626c0  lock dec dword [r14+8]  RW +0x08 4B
//   0xc2626dd  mov rax,[r14]           R +0x00 8B  (vtable pointer, slot 1)
//   0xc2626d6  lock dec dword [r14+0xC] RW +0x0C 4B
#pragma pack(push, 1)
struct sub_c2625e0_r14 {
    void* f0;               // +0x00: void* R  vtable (0xc2626c7, 0xc2626dd)
    std::uint32_t f8;       // +0x08: std::uint32_t RW  (0xc2626c0)
    std::uint32_t fc;       // +0x0C: std::uint32_t RW  (0xc2626d6)
};
#pragma pack(pop)

// Base register rax/rdi: allocated 0x58-byte object.
//   0xc26268e  mov [rdi],rax           W +0x00 8B   vtable = 0x00EFFC850
//   0xc262683  mov [rdi+8],rax         W +0x08 8B   = 0x100000001
//   0xc262698  mov [rdi+0x10],r15      W +0x10 8B   = 0x00F478480
//   0xc26269c  mov [rdi+0x18],r14      W +0x18 8B   = a1->f0
//   0xc2626a4  mov [rdi+0x20],r14      W +0x20 8B   = a1->f8 (reloaded)
//   0xc2626a8  mov [rdi+0x28],rbx      W +0x28 8B   = a2->f0
//   0xc2626ac  mov [rdi+0x48],rax      W +0x48 8B   = object + 0x10
//   0xc2626b0  mov byte [rdi+0x50],1   W +0x50 1B
#pragma pack(push, 1)
struct sub_c2625e0_rax {
    void* f0;               // +0x00: void* W  vtable
    std::uint64_t f8;       // +0x08: std::uint64_t W
    void* f10;              // +0x10: void* W
    void* f18;              // +0x18: void* W
    void* f20;              // +0x20: void* W
    void* f28;              // +0x28: void* W
    std::uint8_t pad0x30[0x18];   // +0x30..+0x47 padding (no observed access)
    void* f48;              // +0x48: void* W
    std::uint8_t f50;       // +0x50: std::uint8_t W
};
#pragma pack(pop)

// Base register rbp: frame pointer (rbp = rsp + 0x80).
//   0xc26261e  mov [rbp],rdx           W +0x00 8B   (saved a1)
//   0xc26263b  mov [rbp+8],rax         W +0x08 8B   (saved a1->f8)
//   0xc2626a0  mov r14,[rbp+8]         R +0x08 8B
//   0xc2625f7  mov qword [rbp+0x10],-2 W +0x10 8B   (EH state scratch)
#pragma pack(push, 1)
struct sub_c2625e0_rbp {
    void* f0;               // +0x00: void* W  saved a1
    void* f8;               // +0x08: void* RW saved a1->f8
    std::uint64_t f10;      // +0x10: std::uint64_t W
};
#pragma pack(pop)

// Base register rsp: stack frame.
//   0xc2625ef  lea rbp,[rsp+0x80]      R +0x80 address (frame base)
#pragma pack(push, 1)
struct sub_c2625e0_rsp {
    std::uint8_t pad0x00[0x80];   // +0x00..+0x7f padding (no observed access)
    std::uint8_t f80;             // +0x80: std::uint8_t R
};
#pragma pack(pop)

// Base register rsi: self out-pair (RCX argument).
//   0xc2626b4  mov [rsi],rax           W +0x00 8B   payload pointer
//   0xc2626b7  mov [rsi+8],rdi         W +0x08 8B   object pointer
#pragma pack(push, 1)
struct sub_c2625e0_rsi {
    void* f0;   // +0x00: void* W  payload pointer (object + 0x10)
    void* f8;   // +0x08: void* W  allocated object pointer
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c2625e0_rcx, f0) == 0x0, "sub_c2625e0: rcx f0 at +0x0");
static_assert(sizeof(sub_c2625e0_rcx) >= 0x8, "sub_c2625e0: rcx sizeof lower bound");

static_assert(offsetof(sub_c2625e0_rdx, f0) == 0x0, "sub_c2625e0: rdx f0 at +0x0");
static_assert(offsetof(sub_c2625e0_rdx, f8) == 0x8, "sub_c2625e0: rdx f8 at +0x8");
static_assert(sizeof(sub_c2625e0_rdx) >= 0x10, "sub_c2625e0: rdx sizeof lower bound");

static_assert(offsetof(sub_c2625e0_r8, f0) == 0x0, "sub_c2625e0: r8 f0 at +0x0");
static_assert(sizeof(sub_c2625e0_r8) >= 0x8, "sub_c2625e0: r8 sizeof lower bound");

static_assert(offsetof(sub_c2625e0_r14, f0) == 0x0, "sub_c2625e0: r14 f0 at +0x0");
static_assert(offsetof(sub_c2625e0_r14, f8) == 0x8, "sub_c2625e0: r14 f8 at +0x8");
static_assert(offsetof(sub_c2625e0_r14, fc) == 0xc, "sub_c2625e0: r14 fc at +0xc");
static_assert(sizeof(sub_c2625e0_r14) >= 0x10, "sub_c2625e0: r14 sizeof lower bound");

static_assert(offsetof(sub_c2625e0_rax, f0) == 0x0, "sub_c2625e0: rax f0 at +0x0");
static_assert(offsetof(sub_c2625e0_rax, f8) == 0x8, "sub_c2625e0: rax f8 at +0x8");
static_assert(offsetof(sub_c2625e0_rax, f10) == 0x10, "sub_c2625e0: rax f10 at +0x10");
static_assert(offsetof(sub_c2625e0_rax, f18) == 0x18, "sub_c2625e0: rax f18 at +0x18");
static_assert(offsetof(sub_c2625e0_rax, f20) == 0x20, "sub_c2625e0: rax f20 at +0x20");
static_assert(offsetof(sub_c2625e0_rax, f28) == 0x28, "sub_c2625e0: rax f28 at +0x28");
static_assert(offsetof(sub_c2625e0_rax, f48) == 0x48, "sub_c2625e0: rax f48 at +0x48");
static_assert(offsetof(sub_c2625e0_rax, f50) == 0x50, "sub_c2625e0: rax f50 at +0x50");
static_assert(sizeof(sub_c2625e0_rax) >= 0x51, "sub_c2625e0: rax sizeof lower bound");

static_assert(offsetof(sub_c2625e0_rbp, f0) == 0x0, "sub_c2625e0: rbp f0 at +0x0");
static_assert(offsetof(sub_c2625e0_rbp, f8) == 0x8, "sub_c2625e0: rbp f8 at +0x8");
static_assert(offsetof(sub_c2625e0_rbp, f10) == 0x10, "sub_c2625e0: rbp f10 at +0x10");
static_assert(sizeof(sub_c2625e0_rbp) >= 0x18, "sub_c2625e0: rbp sizeof lower bound");

static_assert(offsetof(sub_c2625e0_rsp, f80) == 0x80, "sub_c2625e0: rsp f80 at +0x80");
static_assert(sizeof(sub_c2625e0_rsp) >= 0x81, "sub_c2625e0: rsp sizeof lower bound");

static_assert(offsetof(sub_c2625e0_rsi, f0) == 0x0, "sub_c2625e0: rsi f0 at +0x0");
static_assert(offsetof(sub_c2625e0_rsi, f8) == 0x8, "sub_c2625e0: rsi f8 at +0x8");
static_assert(sizeof(sub_c2625e0_rsi) >= 0x10, "sub_c2625e0: rsi sizeof lower bound");

// Game-image absolute addresses referenced by the listing:
//   0x00F478480 : pointer value stored at allocated object +0x10   (0xc26262c / 0xc262698)
//   0x00EFFC850 : vtable pointer stored at allocated object +0x00   (0xc262687 / 0xc26268e)
//   0x01233E1A8 : allocator interface pointer                      (0xc262653)
//   0x00F99FFA0 : IAT slot holding sub_eea6040 (RCX = interface, RDX = size)
//   0x009BC830  : fallback allocator (RCX = 0x58)                  (0xc262705)

// Signature (x64 Microsoft ABI):
//   RCX = self   (out-pair: [self] = payload pointer, [self+8] = allocated object)
//   RDX = a1     (sub_c2625e0_rdx*: +0x0 vtable, +0x8 refcounted-target pointer)
//   R8  = a2     (sub_c2625e0_r8*: +0x0 user pointer)
//   Return: RAX = self
// Calls: sub_eea6040 (via IAT slot 0x00F99FFA0), sub_9bc830, and vtable slots 0/1
// of the refcounted target object. All calls target boundary functions; none are
// in the lift set, so no native lifted symbols are referenced.
uintptr_t sub_c2625e0(void* self, sub_c2625e0_rdx* a1, sub_c2625e0_r8* a2);

} // namespace native::helpers
