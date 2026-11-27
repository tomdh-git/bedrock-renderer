#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// State layout for sub_2b96970, reverse-engineered from the disassembly
// of [0x2b96970, 0x2b96a70), Minecraft Windows 1.26.62.01.
// Offsets and widths come straight from instruction operands; each field
// is cited with the instruction RVA that reads or writes it.

// Struct for base register rcx/rsi (output object; rsi = rcx set at 0x2b96976).
// Fields are written at +0x0 (0x2b96a24), +0x8 (0x2b96a2b), +0x10 (0x2b96a2f),
// +0x18 (0x2b96979 and 0x2b96a32).
#pragma pack(push, 1)
struct sub_2b96970_rcx {
    void* data;            // +0x00: void* W  (0x2b96a24: mov [rsi],rax)
    void* next;            // +0x08: void* W  (0x2b96a2b: mov [rsi+8],rax)
    std::uint32_t handle;  // +0x10: std::uint32_t W  (0x2b96a2f: mov [rsi+0x10],ecx)
    std::uint8_t pad0x14[0x4];   // +0x14..+0x17 padding (no observed access)
    std::uint8_t valid;    // +0x18: std::uint8_t W  (0x2b96979: mov byte [rcx+0x18],0; 0x2b96a32: mov byte [rsi+0x18],1)
};
#pragma pack(pop)

// Struct for base register rdx (input object).
// Fields read at +0x0 (0x2b969b4), +0x8 (0x2b9697d, 0x2b969b7), +0x10 (0x2b9698f, 0x2b969c0).
#pragma pack(push, 1)
struct sub_2b96970_rdx {
    void* array_obj;       // +0x00: void* R  (0x2b969b4: mov rax,[rdx])
    void* refcounted;      // +0x08: void* R  (0x2b9697d: mov rcx,[rdx+8]; 0x2b969b7: mov rdi,[rdx+8])
    std::uint32_t handle;  // +0x10: std::uint32_t R  (0x2b9698f: and eax,[rdx+0x10]; 0x2b969c0: mov ecx,[rdx+0x10])
};
#pragma pack(pop)

// Struct for base register rax (array object; rax = rdx->f0 set at 0x2b969b4).
// Fields read at +0x110 (0x2b969d2), +0x118 (0x2b969d9), +0x150 (0x2b96a1b).
#pragma pack(push, 1)
struct sub_2b96970_rax {
    std::uint8_t pad0x0[0x110];   // +0x00..+0x10f padding (no observed access)
    void* base;             // +0x110: void* R  (0x2b969d2: mov r9,[rax+0x110])
    void* end;              // +0x118: void* R  (0x2b969d9: mov r10,[rax+0x118])
    std::uint8_t pad0x120[0x30];   // +0x120..+0x14f padding (no observed access)
    std::uint32_t limit;    // +0x150: std::uint32_t R  (0x2b96a1b: cmp [rax+0x150],rdx)
};
#pragma pack(pop)

// Struct for base register rdi (refcounted object; rdi = rdx->f8 set at 0x2b969b7;
// same object rcx points to after 0x2b9697d).
// Fields: +0x0 (0x2b96a41, 0x2b96a56), +0x8 (0x2b9699d, 0x2b969ac, 0x2b96a3b), +0xC (0x2b96a50).
#pragma pack(push, 1)
struct sub_2b96970_rdi {
    void* vfptr;           // +0x00: void* R  (0x2b96a41: mov rax,[rdi]; 0x2b96a56: mov rax,[rdi])
    std::uint32_t refcount;  // +0x08: std::uint32_t RW  (0x2b9699d: mov eax,[rcx+8]; 0x2b969ac: lock cmpxchg [rcx+8],r8d; 0x2b96a3b: lock dec [rdi+8])
    std::uint32_t count0xC;  // +0x0C: std::uint32_t RW  (0x2b96a50: lock dec [rdi+0xC])
};
#pragma pack(pop)

static_assert(offsetof(sub_2b96970_rcx, data) == 0x0, "sub_0x2b96970 rcx+0x0 field");
static_assert(offsetof(sub_2b96970_rcx, next) == 0x8, "sub_0x2b96970 rcx+0x8 field");
static_assert(offsetof(sub_2b96970_rcx, handle) == 0x10, "sub_0x2b96970 rcx+0x10 field");
static_assert(offsetof(sub_2b96970_rcx, valid) == 0x18, "sub_0x2b96970 rcx+0x18 field");
static_assert(sizeof(sub_2b96970_rcx) >= 0x19, "sub_0x2b96970 rcx sizeof lower bound");

static_assert(offsetof(sub_2b96970_rdx, array_obj) == 0x0, "sub_0x2b96970 rdx+0x0 field");
static_assert(offsetof(sub_2b96970_rdx, refcounted) == 0x8, "sub_0x2b96970 rdx+0x8 field");
static_assert(offsetof(sub_2b96970_rdx, handle) == 0x10, "sub_0x2b96970 rdx+0x10 field");
static_assert(sizeof(sub_2b96970_rdx) >= 0x14, "sub_0x2b96970 rdx sizeof lower bound");

static_assert(offsetof(sub_2b96970_rax, base) == 0x110, "sub_0x2b96970 rax+0x110 field");
static_assert(offsetof(sub_2b96970_rax, end) == 0x118, "sub_0x2b96970 rax+0x118 field");
static_assert(offsetof(sub_2b96970_rax, limit) == 0x150, "sub_0x2b96970 rax+0x150 field");
static_assert(sizeof(sub_2b96970_rax) >= 0x154, "sub_0x2b96970 rax sizeof lower bound");

static_assert(offsetof(sub_2b96970_rdi, vfptr) == 0x0, "sub_0x2b96970 rdi+0x0 field");
static_assert(offsetof(sub_2b96970_rdi, refcount) == 0x8, "sub_0x2b96970 rdi+0x8 field");
static_assert(offsetof(sub_2b96970_rdi, count0xC) == 0xc, "sub_0x2b96970 rdi+0xc field");
static_assert(sizeof(sub_2b96970_rdi) >= 0x10, "sub_0x2b96970 rdi sizeof lower bound");

// Signature (x64 Microsoft ABI): rcx = output object, rdx = input object, returns output object pointer.
// 0x2b96970  push rsi; 0x2b96971  push rdi; 0x2b96972  sub rsp,0x28; 0x2b96976  mov rsi,rcx
void* sub_2b96970(void* a0, void* a1);

} // namespace native::helpers
