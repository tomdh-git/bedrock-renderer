#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// sub_0xbc6e1e0 (Scene/HUD view-setup task), Minecraft Windows 1.26.62.01,
// [0xbc6e1e0, 0xbc6e357), size 0x177, depth 4, D0.
// Offsets and constants [V] from the disassembly; see docs/functions/bc6e1e0.md.

// The `this`-like object passed in rcx: +0x00 pointer to the render object,
// +0x6AC byte index into the entry-pointer array [V].
struct ViewContext {
    void* objectBase;                       // +0x00 [V]: mov rax,[rcx] at 0xbc6e20d
    std::byte pad_0x08[0x6A4];              // +0x08 .. +0x6AB
    uint8_t entryIndex;                     // +0x6AC [V]: movzx r12d,byte ptr [rcx+0x6AC] at 0xbc6e217
};
static_assert(offsetof(ViewContext, objectBase) == 0x00, "sub_0xbc6e1e0: ViewContext objectBase at +0x00");
static_assert(offsetof(ViewContext, entryIndex) == 0x6AC, "sub_0xbc6e1e0: ViewContext entryIndex at +0x6AC");

// Dynamic entry block pointed at by arrayBase[entryIndex]:
//   capacity@0x00, size@0x04, payload begins at +0x08. The block may be
//   reallocated (its pointer is stored back into the array); only the header
//   offsets are stable [V].
struct ViewEntry {
    uint32_t capacity;   // +0x00 [V]: mov ebp,[rbx] at 0xbc6e223; mov [rax],ebp at 0xbc6e28a
    uint32_t size;       // +0x04 [V]: mov eax,[rbx+4] at 0xbc6e225; add [rbx+4],r14d at 0xbc6e320
    uint8_t payload;     // +0x08 [V]: payload base for writes at entry+8+size
};
static_assert(offsetof(ViewEntry, capacity) == 0x00, "sub_0xbc6e1e0: ViewEntry capacity at +0x00");
static_assert(offsetof(ViewEntry, size) == 0x04, "sub_0xbc6e1e0: ViewEntry size at +0x04");
static_assert(offsetof(ViewEntry, payload) == 0x08, "sub_0xbc6e1e0: ViewEntry payload at +0x08");

// [renderObject + 0xDC57E0] holds the base of the entry-pointer array (8-byte entries) [V]
constexpr std::ptrdiff_t kRenderObject_entryArrayPtr = 0xDC57E0;

// Exact x64 Microsoft ABI signature of sub_0xbc6e1e0:
//   rcx = ctx (ViewContext*), edx = arg2 (uint32_t), r8 = arg3 (uint16_t in low bits),
//   r9 = arg4 (void* source pointer), home slot [rsp+0x28] = arg5 (uint16_t);
//   return eax = new entry size (uint32_t).
uint32_t sub_bc6e1e0(ViewContext* ctx, uint32_t arg2, uint16_t arg3, void* arg4, uint16_t arg5);

} // namespace native::bgfx
